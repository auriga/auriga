#include <string.h>
#include <stdlib.h>

#include "mmo.h"
#include "socket.h"
#include "timer.h"
#include "db.h"
#include "lock.h"
#include "malloc.h"
#include "journal.h"
#include "utils.h"

#include "char.h"
#include "inter.h"
#include "int_party.h"
#include "int_guild.h"
#include "int_storage.h"
#include "int_pet.h"
#include "int_homun.h"
#include "int_mail.h"
#include "int_status.h"

#define WISDATA_TTL		(60*1000)	// Wisデータの生存時間(60秒)
#define WISDELLIST_MAX	128			// Wisデータ削除リストの要素数

char inter_log_filename[1024]="log/inter.log";

struct accreg {
	int account_id,reg_num;
	struct global_reg reg[ACCOUNT_REG_NUM];
};

static struct dbt *accreg_db=NULL;

// 送信パケット長リスト
int inter_send_packet_length[]={
	-1,-1,27, 0, -1, 0, 0, 0,  0, 0, 0, 0,  0, 0,  0, 0,	// 3800-
	-1, 7, 0, 0,  0, 0, 0, 0, -1,11,15, 7,  0, 0,  0, 0,	// 3810-
	35,-1,35,15, 34,53, 7,-1,  0, 0, 0, 0,  0, 0,  0, 0,	// 3820-
	10,-1,15, 0, 79,19, 7,-1,  0,-1,-1,-1, 14,67,186,-1,	// 3830-
	 9, 9,-1, 0,  0, 0, 0, 0,  7,-1,-1,-1, 11,-1, -1, 0,	// 3840-
	 0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0,  0, 0,	// 3850-
	 0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0,  0, 0,	// 3860-
	 0, 0, 0, 0,  0, 0, 0, 0, -1, 7, 0, 0,  0, 0,  0, 0,	// 3870-
	11,-1, 7, 3,  0, 0, 0, 0, -1, 7, 3, 0,  0, 0,  0, 0,	// 3880-
	31,51,51,-1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0,  0, 0,	// 3890-
};
// 受信パケット長リスト
int inter_recv_packet_length[]={
	-1,-1, 7, 0, -1, 6, 0, 0,  0, 0, 0, 0,  0, 0,  0, 0,	// 3000-
	 6,-1, 0, 0,  0, 0, 0, 0, 10,-1,14, 6,  0, 0,  0, 0,	// 3010-
	72, 6,52,14, 34,53, 6,-1, 34, 0, 0, 0,  0, 0,  0, 0,	// 3020-
	-1, 6,-1, 0, 55,19, 6,-1, 14,-1,-1,-1, 18,19,186,-1,	// 3030-
	 5, 9, 0, 0,  0, 0, 0, 0,  0, 6,-1,10, 10,10, -1, 0,	// 3040-
	 0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0,  0, 0,	// 3050-
	 0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0,  0, 0,	// 3060-
	 6, 0, 0, 0,  0, 0, 0, 0, 10,-1, 0, 0,  0, 0,  0, 0,	// 3070-
	48,14,-1, 6,  0, 0, 0, 0, -1,12,-1,12,  0, 0,  0, 0,	// 3080-
	31,51,51,-1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0,  0, 0,	// 3090-
};


struct WisData {
	int id,fd,count,len;
	unsigned long tick;
	unsigned char src[24],dst[24],msg[512];
};
static struct dbt * wis_db = NULL;
static int wis_dellist[WISDELLIST_MAX], wis_delnum;


// WISデータの生存チェック
int check_ttl_wisdata_sub(void *key,void *data,va_list ap)
{
	unsigned long tick;
	struct WisData *wd=(struct WisData *)data;
	tick=va_arg(ap,unsigned long);

	if( DIFF_TICK(tick,wd->tick)>WISDATA_TTL && wis_delnum< WISDELLIST_MAX ){
		wis_dellist[wis_delnum++]=wd->id;
	}
	return 0;
}
int check_ttl_wisdata(void)
{
	unsigned long tick=gettick();
	int i;

	do{
		wis_delnum=0;
		numdb_foreach( wis_db, check_ttl_wisdata_sub, tick );
		for(i=0;i<wis_delnum;i++){
			struct WisData *wd = (struct WisData *)numdb_search(wis_db,wis_dellist[i]);
			printf("inter: wis data id=%d time out : from %s to %s\n",
				wd->id,wd->src,wd->dst);
			numdb_erase(wis_db,wd->id);
			aFree(wd);
		}
	}while(wis_delnum>=WISDELLIST_MAX);
	return 0;
}

//--------------------------------------------------------

#ifdef TXT_ONLY

char accreg_txt[1024]="save/accreg.txt";

#ifdef TXT_JOURNAL
static int accreg_journal_enable = 1;
static struct journal accreg_journal;
static char accreg_journal_file[1024]="./save/accreg.journal";
static int accreg_journal_cache = 1000;
#endif

// アカウント変数を文字列へ変換
int accreg_tostr(char *str,struct accreg *reg)
{
	int j;
	char *p=str;
	p+=sprintf(p,"%d\t",reg->account_id);
	for(j=0;j<reg->reg_num;j++){
		p+=sprintf(p,"%s,%d ",reg->reg[j].str,reg->reg[j].value);
	}
	return 0;
}
// アカウント変数を文字列から変換
int accreg_fromstr(const char *str,struct accreg *reg)
{
	int j,v,n;
	char buf[128];
	const char *p=str;
	if( sscanf(p,"%d\t%n",&reg->account_id,&n )!=1 || reg->account_id<=0)
		return 1;

	for(j=0,p+=n;j<ACCOUNT_REG_NUM;j++,p+=n){
		if( sscanf(p,"%[^,],%d%n",buf,&v,&n)!=2 )
			break;
		memcpy(reg->reg[j].str,buf,32);
		reg->reg[j].value=v;
		n++;
	}
	reg->reg_num=j;
	return 0;
}

#ifdef TXT_JOURNAL
// ==========================================
// アカウント変数のジャーナルのロールフォワード用コールバック関数
// ------------------------------------------
int accreg_journal_rollforward( int key, void* buf, int flag )
{
	struct accreg* reg = (struct accreg *)numdb_search( accreg_db, key );

	// 念のためチェック
	if( flag == JOURNAL_FLAG_WRITE && key != ((struct accreg*)buf)->account_id )
	{
		printf("inter: accreg_journal: key != account_id !\n");
		return 0;
	}

	// データの置き換え
	if( reg )
	{
		if( flag == JOURNAL_FLAG_DELETE ) {
			numdb_erase( accreg_db, key );
			aFree( reg );
		} else {
			memcpy( reg, buf, sizeof(struct accreg) );
		}
		return 1;
	}

	// 追加
	if( flag != JOURNAL_FLAG_DELETE )
	{
		reg = (struct accreg*) aCalloc( 1, sizeof( struct accreg ) );
		memcpy( reg, buf, sizeof(struct accreg) );
		numdb_insert( accreg_db, key, reg );
		return 1;
	}

	return 0;
}
int accreg_txt_sync(void);
#endif

// アカウント変数の読み込み
int accreg_txt_init(void)
{
	char line[8192];
	FILE *fp;
	int c=0;
	struct accreg *reg;

	accreg_db=numdb_init();

	if( (fp=fopen(accreg_txt,"r"))==NULL )
		return 1;
	while(fgets(line,sizeof(line),fp)){

		reg=(struct accreg *)aCalloc(1,sizeof(struct accreg));
		if(accreg_fromstr(line,reg)==0 && reg->account_id>0){
			numdb_insert(accreg_db,reg->account_id,reg);
		}else{
			printf("inter: accreg: broken data [%s] line %d\n",accreg_txt,c);
			aFree(reg);
		}
		c++;
	}
	fclose(fp);
//	printf("inter: %s read done (%d)\n",accreg_txt,c);

#ifdef TXT_JOURNAL
	if( accreg_journal_enable )
	{
		// ジャーナルデータのロールフォワード
		if( journal_load( &accreg_journal, sizeof(struct accreg), accreg_journal_file ) )
		{
			int c = journal_rollforward( &accreg_journal, accreg_journal_rollforward );

			printf("inter: accreg_journal: roll-forward (%d)\n", c );

			// ロールフォワードしたので、txt データを保存する ( journal も新規作成される)
			accreg_txt_sync();
		}
		else
		{
			// ジャーナルを新規作成する
			journal_final( &accreg_journal );
			journal_create( &accreg_journal, sizeof(struct accreg), accreg_journal_cache, accreg_journal_file );
		}
	}
#endif

	return 0;

}
// アカウント変数のセーブ用
int accreg_txt_sync_sub(void *key,void *data,va_list ap)
{
	char line[8192];
	FILE *fp;
	struct accreg *reg=(struct accreg *)data;
	if(reg->reg_num>0){
		accreg_tostr(line,reg);
		fp=va_arg(ap,FILE *);
		fprintf(fp,"%s" RETCODE,line);
	}
	return 0;
}

// アカウント変数のセーブ
int accreg_txt_sync(void)
{
	FILE *fp;
	int  lock;

	if( !accreg_db )
		return 1;

	if( (fp=lock_fopen(accreg_txt,&lock))==NULL ){
		printf("int_accreg: cant write [%s] !!! data is lost !!!\n",accreg_txt);
		return 1;
	}
	numdb_foreach(accreg_db,accreg_txt_sync_sub,fp);
	lock_fclose(fp,accreg_txt,&lock);
//	printf("inter: %s saved.\n",accreg_txt);

#ifdef TXT_JOURNAL
	if( accreg_journal_enable )
	{
		// コミットしたのでジャーナルを新規作成する
		journal_final( &accreg_journal );
		journal_create( &accreg_journal, sizeof(struct accreg), accreg_journal_cache, accreg_journal_file );
	}
#endif

	return 0;
}

void accreg_txt_config_read_sub(const char *w1,const char *w2) {
	if(strcmpi(w1,"accreg_txt")==0){
		strncpy(accreg_txt,w2,sizeof(accreg_txt));
	}
#ifdef TXT_JOURNAL
	else if(strcmpi(w1,"accreg_journal_enable")==0){
		accreg_journal_enable = atoi( w2 );
	}
	else if(strcmpi(w1,"accreg_journal_file")==0){
		strncpy( accreg_journal_file, w2, sizeof(accreg_journal_file) );
	}
	else if(strcmpi(w1,"accreg_journal_cache_interval")==0){
		accreg_journal_cache = atoi( w2 );
	}
#endif
}

const struct accreg* accreg_txt_load(int account_id) {
	return (const struct accreg* )numdb_search(accreg_db,account_id);
}

void accreg_txt_save(struct accreg* reg2) {
	struct accreg* reg1 = (struct accreg *)numdb_search(accreg_db,reg2->account_id);
	if(reg1 == NULL) {
		reg1 = (struct accreg *)aMalloc(sizeof(struct accreg));
		numdb_insert(accreg_db,reg2->account_id,reg1);
	}
	memcpy(reg1,reg2,sizeof(struct accreg));

#ifdef TXT_JOURNAL
	if( accreg_journal_enable )
		journal_write( &accreg_journal, reg2->account_id, reg2 );
#endif
}

static int accreg_txt_final_sub(void *key,void *data,va_list ap)
{
	struct accreg *reg = (struct accreg *)data;

	aFree(reg);

	return 0;
}

void accreg_txt_final(void) {
	if(accreg_db)
		numdb_final(accreg_db,accreg_txt_final_sub);

#ifdef TXT_JOURNAL
	if( accreg_journal_enable )
	{
		journal_final( &accreg_journal );
	}
#endif
}

#define accreg_load  accreg_txt_load
#define accreg_save  accreg_txt_save
#define accreg_init  accreg_txt_init
#define accreg_sync  accreg_txt_sync
#define accreg_final accreg_txt_final
#define accreg_config_read_sub accreg_txt_config_read_sub

#else /* TXT_ONLY */

static char interlog_db[256] = "interlog";

int accreg_sql_init(void) {
	accreg_db = numdb_init();
	return 0;
}

int accreg_sql_sync(void)
{
	// nothing to do
	return 0;
}

void accreg_sql_config_read_sub(const char *w1,const char *w2) {
	// nothing to do
}

void accreg_sql_save(struct accreg *reg) {
	int j;
	char temp_str[64];
	char *p = tmp_sql;
	char sep = ' ';

	//`global_reg_value` (`type`, `account_id`, `char_id`, `str`, `value`)
	sprintf(tmp_sql,"DELETE FROM `%s` WHERE `type`=2 AND `account_id`='%d'",reg_db, reg->account_id);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (delete `%s`)- %s\n", reg_db, mysql_error(&mysql_handle) );
	}

	if (reg->reg_num<=0)
		return;

	p += sprintf(p, "INSERT INTO `%s` (`type`, `account_id`, `str`, `value`) VALUES", reg_db);
	for(j=0;j<reg->reg_num;j++){
		if(reg->reg[j].str != NULL){
			p += sprintf(p, "%c(2,'%d', '%s','%d')", reg->account_id,strecpy(temp_str,reg->reg[j].str), reg->reg[j].value);
			sep = ',';
		}
	}
	if(sep == ',') {
		if(mysql_query(&mysql_handle, tmp_sql) ) {
			printf("DB server Error (insert `%s`)- %s\n", reg_db, mysql_error(&mysql_handle) );
		}
	}
}

const struct accreg* accreg_sql_load(int account_id) {
	int j=0;
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;
	struct accreg *reg = (struct accreg *)numdb_search(accreg_db,account_id);
	if(reg == NULL) {
		reg = (struct accreg *)aMalloc(sizeof(struct accreg));
		numdb_insert(accreg_db,account_id,reg);
	}
	memset(reg, 0, sizeof(struct accreg));
	reg->account_id=account_id;

	//`global_reg_value` (`type`, `account_id`, `char_id`, `str`, `value`)
	sprintf (tmp_sql, "SELECT `str`, `value` FROM `%s` WHERE `type`=2 AND `account_id`='%d'",reg_db, reg->account_id);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (select `%s`)- %s\n", reg_db, mysql_error(&mysql_handle) );
	}
	sql_res = mysql_store_result(&mysql_handle);

	if (sql_res) {
		for(j=0;(sql_row = mysql_fetch_row(sql_res));j++){
			memcpy(reg->reg[j].str, sql_row[0],32);
			reg->reg[j].value = atoi(sql_row[1]);
		}
		mysql_free_result(sql_res);
	}
	reg->reg_num=j;
	return reg;
}

static int accreg_sql_final_sub(void *key,void *data,va_list ap)
{
	struct accreg *reg = (struct accreg *)data;

	aFree(reg);

	return 0;
}

void accreg_sql_final(void) {
	if(accreg_db)
		numdb_final(accreg_db,accreg_sql_final_sub);
}

#define accreg_load  accreg_sql_load
#define accreg_save  accreg_sql_save
#define accreg_init  accreg_sql_init
#define accreg_sync  accreg_sql_sync
#define accreg_final accreg_sql_final
#define accreg_config_read_sub accreg_sql_config_read_sub

#endif /* TXT_ONLY */

//--------------------------------------------------------

/*==========================================
 * 設定ファイルを読み込む
 *------------------------------------------
 */
int inter_config_read(const char *cfgName)
{
	int i;
	char line[1024],w1[1024],w2[1024];
	FILE *fp;

	fp=fopen(cfgName,"r");
	if(fp==NULL){
		printf("file not found: %s\n",cfgName);
		return 1;
	}
	while(fgets(line,1020,fp)){
		i=sscanf(line,"%[^:]: %[^\r\n]",w1,w2);
		if(i!=2)
			continue;

		if(strcmpi(w1,"inter_log_filename")==0){
			strncpy(inter_log_filename,w2,1024);
		}
		else if(strcmpi(w1,"import")==0){
			inter_config_read(w2);
		}
		else {
			accreg_config_read_sub(w1,w2);
			pet_config_read_sub(w1,w2);
			storage_config_read_sub(w1,w2);
			party_config_read(w1,w2);
			guild_config_read(w1,w2);
			mail_config_read_sub(w1,w2);
			homun_config_read_sub(w1,w2);
			status_config_read_sub(w1,w2);
		}
	}
	fclose(fp);

	return 0;
}

//--------------------------------------------------------
// ログ書き出し

#ifdef TXT_ONLY

int inter_log(char *fmt,...)
{
	FILE *logfp;
	va_list ap;
	va_start(ap,fmt);

	logfp=fopen(inter_log_filename,"a");
	if(logfp){
		vfprintf(logfp,fmt,ap);
		fprintf(logfp,RETCODE);
		fclose(logfp);
	}
	va_end(ap);
	return 0;
}

#else /* TXT_ONLY */

int inter_log(char *fmt,...)
{
	char log[256], buf[512];
	va_list ap;

	va_start(ap,fmt);

	(void) vsnprintf(log,256,fmt,ap);
	va_end(ap);

	sprintf(tmp_sql,"INSERT INTO `%s` (`time`,`log`) VALUES (NOW(),'%s')", interlog_db, strecpy(buf,log));

	if(mysql_query(&mysql_handle, tmp_sql) ){
		printf("DB server Error (insert `%s`)- %s\n", interlog_db, mysql_error(&mysql_handle) );
	}

	return 0;
}

#endif /* TXT_ONLY */

//--------------------------------------------------------

// セーブ
int inter_sync()
{
	status_sync();
	pet_sync();
	homun_sync();
	party_sync();
	guild_sync();
	accreg_sync();
	storage_sync();
	gstorage_sync();
	mail_sync();

	return 0;
}

// 初期化
int inter_init(const char *file)
{
	inter_config_read(file);

	wis_db = numdb_init();

	status_init();
	pet_init();
	homun_init();
	party_init();
	guild_init();
	accreg_init();
	storage_init();
	mail_init();

	return 0;
}

// マップサーバー接続
int inter_mapif_init(int fd)
{
	inter_guild_mapif_init(fd);
	return 0;
}

//--------------------------------------------------------

// GMメッセージ送信
int mapif_GMmessage(unsigned char *mes,int len,unsigned long color)
{
	unsigned char *buf = (unsigned char*)aMalloc(len);
	WBUFW(buf,0) = 0x3800;
	WBUFW(buf,2) = len;
	WBUFL(buf,4) = color;
	memcpy(WBUFP(buf,8), mes, len-8);
	mapif_sendall(buf,len);
	//printf("inter server: GM:%d %s\n", len, mes);
	aFree(buf);
	return 0;
}

// Wis送信
int mapif_wis_message(struct WisData *wd)
{
	unsigned char buf[1024];
	WBUFW(buf, 0)=0x3801;
	WBUFW(buf, 2)=8 + 48 +wd->len;
	WBUFL(buf, 4)=wd->id;
	memcpy(WBUFP(buf, 8),wd->src,24);
	memcpy(WBUFP(buf,32),wd->dst,24);
	memcpy(WBUFP(buf,56),wd->msg,wd->len);
	wd->count = mapif_sendall(buf,WBUFW(buf,2));

	return 0;
}
// Wis送信結果
int mapif_wis_end(struct WisData *wd,int flag)
{
	unsigned char buf[32];

	WBUFW(buf, 0)=0x3802;
	memcpy(WBUFP(buf, 2),wd->src,24);
	WBUFB(buf,26)=flag;
	mapif_send(wd->fd,buf,27);
//	printf("inter server wis_end %d\n",flag);
	return 0;
}

// アカウント変数送信
int mapif_account_reg(int fd,unsigned char *src)
{
	int len = WBUFW(src,2);
	unsigned char *buf = (unsigned char *)aMalloc(len);

	memcpy(WBUFP(buf,0),src,len);
	WBUFW(buf, 0)=0x3804;
	mapif_sendallwos(fd,buf,WBUFW(buf,2));
	aFree(buf);
	return 0;
}
// アカウント変数要求返信
int mapif_account_reg_reply(int fd,int account_id)
{
	const struct accreg *reg = accreg_load(account_id);
	WFIFOW(fd,0)=0x3804;
	WFIFOL(fd,4)=account_id;
	if(reg==NULL){
		WFIFOW(fd,2)=8;
	}else{
		int j,p;
		for(j=0,p=8;j<reg->reg_num;j++,p+=36){
			memcpy(WFIFOP(fd,p),reg->reg[j].str,32);
			WFIFOL(fd,p+32)=reg->reg[j].value;
		}
		WFIFOW(fd,2)=p;
	}
	WFIFOSET(fd,WFIFOW(fd,2));
	return 0;
}

//--------------------------------------------------------

// GMメッセージ送信
int mapif_parse_GMmessage(int fd)
{
	mapif_GMmessage(RFIFOP(fd,8), RFIFOW(fd,2), RFIFOL(fd,4));
	return 0;
}


// Wis送信要求
int mapif_parse_WisRequest(int fd)
{
	struct WisData* wd;
	static int wisid=0;

	if( RFIFOW(fd,2)-52 >= sizeof(wd->msg) ){
		printf("inter: Wis message size too long.\n");
		return 0;
	}

	wd = (struct WisData *)aCalloc(1,sizeof(struct WisData));
	check_ttl_wisdata();

	wd->id = ++wisid;
	wd->fd = fd;
	wd->len= RFIFOW(fd,2)-52;
	memcpy(wd->src, RFIFOP(fd, 4), 24);
	memcpy(wd->dst, RFIFOP(fd,28), 24);
	memcpy(wd->msg, RFIFOP(fd,52), wd->len);
	wd->tick = gettick();
	numdb_insert(wis_db, wd->id, wd);
	mapif_wis_message(wd);

	return 0;
}

// Wis送信結果
int mapif_parse_WisReply(int fd)
{
	int id=RFIFOL(fd,2),flag=RFIFOB(fd,6);

	struct WisData *wd = (struct WisData *)numdb_search(wis_db, id);

	if(wd==NULL)
		return 0;	// タイムアウトしたかIDが存在しない

	if( (--wd->count)==0 || flag!=1){
		mapif_wis_end(wd,flag);
		numdb_erase(wis_db, id);
		aFree(wd);
	}
	return 0;
}

// アカウント変数保存要求
int mapif_parse_AccReg(int fd)
{
	int j,p;
	struct accreg reg;
	memset(&reg,0,sizeof(reg));

	reg.account_id = RFIFOL(fd,4);
	for(j=0,p=8;j<ACCOUNT_REG_NUM && p<RFIFOW(fd,2);j++,p+=36){
		memcpy(reg.reg[j].str,RFIFOP(fd,p),32);
		reg.reg[j].value=RFIFOL(fd,p+32);
	}
	reg.reg_num=j;

	accreg_save(&reg);
	mapif_account_reg(fd,RFIFOP(fd,0));	// 他のMAPサーバーに送信
	return 0;
}

// アカウント変数送信要求
int mapif_parse_AccRegRequest(int fd)
{
//	printf("mapif: accreg request\n");
	return mapif_account_reg_reply(fd,RFIFOL(fd,2));
}

/*==========================================
 * キャラクターの位置要求
 *------------------------------------------
 */
int mapif_parse_CharPosReq(int fd)
{
	unsigned char buf[40];
	WBUFW(buf,0)=0x3890;
	memcpy(WBUFP(buf,2),RFIFOP(fd,2),29);
	mapif_sendall(buf,31);
	//printf("mapif_parse_CharPosReq: %d %s\n",RFIFOL(fd,2),RFIFOP(fd,6));
	return 0;
}
/*==========================================
 * キャラクターの位置を要求者に通知
 *------------------------------------------
 */
int mapif_parse_CharPos(int fd)
{
	unsigned char buf[60];
	WBUFW(buf,0)=0x3891;
	memcpy(WBUFP(buf,2),RFIFOP(fd,2),49);
	mapif_sendall(buf,51);
	//printf("mapif_parse_CharPos: %d %s %s %d %d\n",RFIFOL(fd,2),RFIFOP(fd,6),RFIFOP(fd,31),RFIFOW(fd,47),RFIFOW(fd,49));
	return 0;
}
/*==========================================
 * キャラクターの移動要求
 *------------------------------------------
 */
int mapif_parse_CharMoveReq(int fd)
{
	unsigned char buf[60];
	WBUFW(buf,0)=0x3892;
	memcpy(WBUFP(buf,2),RFIFOP(fd,2),49);
	mapif_sendall(buf,51);
	//printf("mapif_parse_CharMoveReq: %d %s %s %d %d\n",RFIFOL(fd,2),RFIFOP(fd,6),RFIFOP(fd,31),RFIFOW(fd,47),RFIFOW(fd,49));
	return 0;
}
/*==========================================
 * 対象IDにメッセージを送信
 *------------------------------------------
 */
int mapif_parse_DisplayMessage(int fd)
{
	int len=RFIFOW(fd,2);
	unsigned char *buf = (unsigned char*)(len);

	WBUFW(buf,0)=0x3893;
	memcpy(WBUFP(buf,2),RFIFOP(fd,2),len-2);
	mapif_sendall(buf,len);
	aFree(buf);
	return 0;
}
//--------------------------------------------------------

// map server からの通信（１パケットのみ解析すること）
// エラーなら0(false)、処理できたなら1、
// パケット長が足りなければ2をかえさなければならない
int inter_parse_frommap(int fd)
{
	int cmd=RFIFOW(fd,0);
	int len=0;

	// inter鯖管轄かを調べる
	if(cmd<0x3000 || cmd>=0x3000+( sizeof(inter_recv_packet_length)/
		sizeof(inter_recv_packet_length[0]) ) )
		return 0;

	// パケット長を調べる
	if(	(len=inter_check_length(fd,inter_recv_packet_length[cmd-0x3000]))==0 )
		return 2;

	switch(cmd){
	case 0x3000: mapif_parse_GMmessage(fd); break;
	case 0x3001: mapif_parse_WisRequest(fd); break;
	case 0x3002: mapif_parse_WisReply(fd); break;
	case 0x3004: mapif_parse_AccReg(fd); break;
	case 0x3005: mapif_parse_AccRegRequest(fd); break;
	case 0x3090: mapif_parse_CharPosReq(fd); break;
	case 0x3091: mapif_parse_CharPos(fd); break;
	case 0x3092: mapif_parse_CharMoveReq(fd); break;
	case 0x3093: mapif_parse_DisplayMessage(fd); break;
	case 0x3070: mapif_parse_CharConnectLimit(fd); break;
	default:
		if( inter_party_parse_frommap(fd) )
			break;
		if( inter_guild_parse_frommap(fd) )
			break;
		if( inter_storage_parse_frommap(fd) )
			break;
		if( inter_pet_parse_frommap(fd) )
			break;
		if( inter_hom_parse_frommap(fd) )
			break;
		if( inter_mail_parse_frommap(fd) )
			break;
		if( inter_status_parse_frommap(fd) )
			break;
		return 0;
	}
	RFIFOSKIP(fd, len );
	return 1;
}

// RFIFOのパケット長確認
// 必要パケット長があればパケット長、まだ足りなければ0
int inter_check_length(int fd,int length)
{
	if(length==-1){	// 可変パケット長
		if(RFIFOREST(fd)<4)	// パケット長が未着
			return 0;
		length = RFIFOW(fd,2);
	}

	if(RFIFOREST(fd)<length)	// パケットが未着
		return 0;

	return length;
}

static int wis_db_final(void *key,void *data,va_list ap)
{
	struct WisData *wd = (struct WisData *)data;

	aFree(wd);

	return 0;
}

void do_final_inter(void)
{
	if(wis_db)
		numdb_final(wis_db,wis_db_final);

	accreg_final();

}
