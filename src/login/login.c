#define DUMP_UNKNOWN_PACKET	1

#include <sys/types.h>
#ifndef _WIN32
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <sys/ioctl.h>
	#include <unistd.h>
	#include <signal.h>
	#include <fcntl.h>
	#include <netdb.h>
	#include <arpa/inet.h>
	#include <sys/time.h>
#else
	#include <process.h>
	#include <winsock.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#include "core.h"
#include "socket.h"
#include "mmo.h"
#include "version.h"
#include "db.h"
#include "lock.h"
#include "malloc.h"
#include "timer.h"
#include "httpd.h"
#include "graph.h"
#include "journal.h"
#include "utils.h"

#include "login.h"

#ifdef PASSWORDENC
#include "md5calc.h"
#endif

#ifdef MEMWATCH
#include "memwatch.h"
#endif

static const char sex2str[] = "FMS";

static int server_num = 0;
static int new_account_flag = 0;
static int httpd_new_account_flag = 0;
static unsigned short login_port = 6900;
static char login_sip_str[16];
static unsigned long login_sip = 0;
static unsigned short login_sport = 0;
static int login_autosave_time = 600;

struct mmo_char_server server[MAX_CHAR_SERVERS];
static int server_fd[MAX_CHAR_SERVERS];
static int login_fd;
static int login_sfd;

static struct {
	int account_id;
	int login_id1,login_id2;
	unsigned long ip;
	unsigned int tick;
	int delflag, sex;
} auth_fifo[AUTH_FIFO_SIZE];

static int auth_fifo_pos = 0;

char login_conf_filename[256] = "conf/login_auriga.conf";

static char admin_pass[64]=""; // for account creation
static char ladmin_pass[64]=""; // for remote administration
static char login_log_filename[1024] = "log/login.log";
static int login_version = 0, login_type = 0;
static int detect_multiple_login = 1;

#ifdef TXT_JOURNAL
static int login_journal_enable = 1;
static struct journal login_journal;
static char login_journal_file[1024]="./save/account.journal";
static int login_journal_cache = 1000;
#endif

static char GM_account_filename[1024] = "conf/GM_account.txt";
static struct dbt *gm_account_db = NULL;

int login_log(char *fmt,...);
static int isGM(int account_id);
static int gm_account_db_final(void *key, void *data, va_list ap);

#ifdef TXT_ONLY

static char account_filename[1024] = "save/account.txt";
static int  auth_num=0,auth_max=0;
static int  account_id_count = START_ACCOUNT_NUM;
static struct mmo_account *auth_dat = NULL;

// アカウントIDからauth_datのインデックスを返す
static int login_id2idx(int account_id)
{
	int min = -1;
	int max = auth_num;

	// binary search
	while(max - min > 1) {
		int mid = (min + max) / 2;
		if(auth_dat[mid].account_id == account_id)
			return (auth_dat[mid].userid[0])? mid: -1;

		if(auth_dat[mid].account_id > account_id)
			max = mid;
		else
			min = mid;
	}
	return -1;
}

#ifdef TXT_JOURNAL
// ==========================================
// アカウントデータのジャーナルのロールフォワード用コールバック関数
// ------------------------------------------
int login_journal_rollforward( int key, void* buf, int flag )
{
	int idx = login_id2idx( key );

	// 念のためチェック
	if( flag == JOURNAL_FLAG_WRITE && key != ((struct mmo_account*)buf)->account_id )
	{
		printf("login_journal: key != account_id !\n");
		return 0;
	}

	// データの置き換え
	if( idx >= 0 )
	{
		if( flag == JOURNAL_FLAG_DELETE ) {
			memset( &auth_dat[idx], 0, sizeof(struct mmo_account) );
			auth_dat[idx].account_id = -1;
		} else {
			memcpy( &auth_dat[idx], buf, sizeof(struct mmo_account) );
		}
		return 1;
	}

	// 追加
	if( flag != JOURNAL_FLAG_DELETE )
	{
		if(auth_num>=auth_max)
		{
			// メモリが足りないなら拡張
			auth_max+=256;
			auth_dat = (struct mmo_account *)aRealloc(auth_dat,sizeof(auth_dat[0])*auth_max);
		}

		memcpy( &auth_dat[auth_num], buf, sizeof(struct mmo_account) );
		if(auth_dat[auth_num].account_id>=account_id_count)
			account_id_count=auth_dat[auth_num].account_id+1;
		auth_num++;
		return 1;
	}

	return 0;
}

void login_txt_sync(void);
#endif

int login_txt_init(void)
{
	// アカウントデータベースの読み込み
	FILE *fp;
	int i,n,account_id,logincount,state;
	char line[65536],*p,userid[256],pass[256],lastlogin[256],sex;

	if((fp=fopen(account_filename,"r"))==NULL)
		return 0;
	auth_max = 256;
	auth_dat = (struct mmo_account *)aCalloc(auth_max,sizeof(auth_dat[0]));

	while(fgets(line,65535,fp)!=NULL){
		p=line;
		n=-1;

		i=sscanf(line,"%d\t%255[^\t]\t%255[^\t]\t%255[^\t]\t%c\t%d\t%d\t%n",
			&account_id,userid,pass,lastlogin,&sex,&logincount,&state,&n);

		if(i < 5) {
			i = -1;
			if( sscanf(line,"%d\t%%newid%%%n",&account_id,&i) == 1 && i > 0 && (line[i] == '\n' || line[i] == '\r') ) {
				if(account_id > END_ACCOUNT_NUM+1) {	// newidは+1まで許可
					printf("reading %s error : invalid ID %d\n",account_filename,account_id);
					continue;
				}
				if(account_id > account_id_count)
					account_id_count=account_id;
			}
			continue;
		}

		if(account_id > END_ACCOUNT_NUM) {
			printf("reading %s error : invalid ID %d\n",account_filename,account_id);
			continue;
		}
		if(auth_num>=auth_max){
			auth_max += 256;
			auth_dat = (struct mmo_account *)aRealloc(auth_dat,sizeof(auth_dat[0])*auth_max);
		}
		auth_dat[auth_num].account_id=account_id;
		strncpy(auth_dat[auth_num].userid,userid,24);
		strncpy(auth_dat[auth_num].pass,pass,24);
		strncpy(auth_dat[auth_num].lastlogin,lastlogin,24);
		auth_dat[auth_num].sex = (sex == 'S' ? 2 : sex == 'M' ? 1 : 0);

		// force \0 terminal
		auth_dat[auth_num].userid[23]    = '\0';
		auth_dat[auth_num].pass[23]      = '\0';
		auth_dat[auth_num].lastlogin[23] = '\0';

		// データが足りないときの補完
		auth_dat[auth_num].logincount = (i >= 6)? logincount: 1;
		auth_dat[auth_num].state      = (i >= 7)? state: 0;

		// メールアドレスがあれば読み込む
		if(n > 0)
		{
			int n2=0;
			char mail[256] = "";
			if( sscanf( line + n, "%255[^\t]\t%n", mail, &n2 )==1 && strchr( mail, '@' ) )
			{
				if( strcmp( mail, "@" )==0 ) {
					auth_dat[auth_num].mail[0] = '\0';
				} else {
					strncpy( auth_dat[auth_num].mail, mail, 40 );
					auth_dat[auth_num].mail[39] = '\0';	// force \0 terminal
				}
				n = (n2>0)? n+n2 : 0;
			}
		}

		// 全ワールド共有アカウント変数 ( ## 変数 ) 読み込み
		if(n > 0) {
			int j,v;
			char str[256];
			for(j=0;j<ACCOUNT_REG2_NUM;j++){
				p+=n;
				if(sscanf(p,"%255[^\t,],%d%n",str,&v,&n)!=2)
					break;
				strncpy(auth_dat[auth_num].account_reg2[j].str,str,32);
				auth_dat[auth_num].account_reg2[j].str[31] = '\0';	// force \0 terminal
				auth_dat[auth_num].account_reg2[j].value   = v;
				if(p[n] != ' ')
					break;
				n++;
			}
			auth_dat[auth_num].account_reg2_num=j;
		} else {
			auth_dat[auth_num].account_reg2_num=0;
		}

		if(account_id>=account_id_count)
			account_id_count=account_id+1;

		if(auth_num > 0 && account_id < auth_dat[auth_num-1].account_id) {
			struct mmo_account tmp;
			int k = auth_num;

			// 何故かアカウントIDの昇順に並んでない場合は挿入ソートする
			while(--k > 0 && account_id < auth_dat[k-1].account_id);

			memcpy(&tmp, &auth_dat[auth_num], sizeof(auth_dat[0]));
			memmove(&auth_dat[k+1], &auth_dat[k], (auth_num-k)*sizeof(auth_dat[0]));
			memcpy(&auth_dat[k], &tmp, sizeof(auth_dat[0]));
		}
		auth_num++;
	}
	fclose(fp);

#ifdef TXT_JOURNAL
	if( login_journal_enable )
	{
		// ジャーナルデータのロールフォワード
		if( journal_load( &login_journal, sizeof(struct mmo_account), login_journal_file ) )
		{
			int c = journal_rollforward( &login_journal, login_journal_rollforward );

			printf("login_journal: roll-forward (%d)\n", c );

			// ロールフォワードしたので、txt データを保存する ( journal も新規作成される)
			login_txt_sync();
		}
		else
		{
			// ジャーナルを新規作成する
			journal_final( &login_journal );
			journal_create( &login_journal, sizeof(struct mmo_account), login_journal_cache, login_journal_file );
		}
	}
#endif

	return 0;
}

// アカウントデータベースの書き込み
void login_txt_sync(void)
{
	FILE *fp;
	int i,j,lock;

	if( !auth_dat )
		return;

	fp=lock_fopen(account_filename,&lock);
	if(fp==NULL)
		return;
	for(i=0;i<auth_num;i++){
		if(auth_dat[i].account_id<0)
			continue;
		if(!auth_dat[i].userid[0]) {
			// 削除されている
			continue;
		}

		fprintf(fp,"%d\t%s\t%s\t%s\t%c\t%d\t%d\t%s\t",auth_dat[i].account_id,
			auth_dat[i].userid,auth_dat[i].pass,auth_dat[i].lastlogin,
			sex2str[auth_dat[i].sex],
			auth_dat[i].logincount,auth_dat[i].state, (auth_dat[i].mail[0])? auth_dat[i].mail: "@" );

		for(j=0;j<auth_dat[i].account_reg2_num;j++){
			fprintf(fp,"%s,%d ",
				auth_dat[i].account_reg2[j].str,
				auth_dat[i].account_reg2[j].value);
		}
		fprintf(fp,RETCODE);
	}
	fprintf(fp,"%d\t%%newid%%" RETCODE,account_id_count);

	lock_fclose(fp,account_filename,&lock);

#ifdef TXT_JOURNAL
	if( login_journal_enable )
	{
		// コミットしたのでジャーナルを新規作成する
		journal_final( &login_journal );
		journal_create( &login_journal, sizeof(struct mmo_account), login_journal_cache, login_journal_file );
	}
#endif

}

const struct mmo_account* login_txt_account_load_num(int account_id)
{
	int idx = login_id2idx(account_id);

	return (idx >= 0) ? &auth_dat[idx] : NULL;
}

const struct mmo_account* login_txt_account_load_str(const char *account_id)
{
	int x;

	if( !account_id[0] )
		return NULL;
	for(x=0;x<auth_num;x++){
		if(auth_dat[x].userid[0] && !strncmp(auth_dat[x].userid,account_id,24)) {
			return &auth_dat[x];
		}
	}
	return NULL;
}

const struct mmo_account* login_txt_account_load_idx(int idx)
{
	return (idx >= 0 && idx < auth_num) ? &auth_dat[idx] : NULL;
}

int login_txt_account_save(struct mmo_account *account)
{
	int idx = login_id2idx(account->account_id);

	if(idx >= 0) {
		memcpy(&auth_dat[idx],account,sizeof(struct mmo_account));
#ifdef TXT_JOURNAL
		if( login_journal_enable )
			journal_write( &login_journal, account->account_id, account );
#endif
		return 1;
	}
	return 0;
}

// アカウント削除
int login_txt_account_delete(int account_id)
{
	int idx = login_id2idx(account_id);

	if(idx >= 0) {
		memset(&auth_dat[idx],0,sizeof(struct mmo_account));
		auth_dat[idx].account_id = account_id;	// アカウントIDは維持
#ifdef TXT_JOURNAL
		if( login_journal_enable )
			journal_write( &login_journal, account_id, NULL );
#endif
		return 1;
	}
	return 0;
}

// アカウント作成
int login_txt_account_new(struct mmo_account* account,const char *tmpstr)
{
	int j,i=auth_num,c;

	login_log("auth new %s %s %s",tmpstr,account->userid,account->pass);

	if(!account->userid[0]) {
		// 空文字は弾く
		return 0;
	}
	for(j=0;j<24 && (c=account->userid[j]);j++){
		if(c<0x20 || c==0x7f)
			return 0;
	}

	// force \0 terminal
	account->userid[23] = '\0';
	account->pass[23]   = '\0';
	account->mail[39]   = '\0';

	if(login_txt_account_load_str(account->userid)) {
		// 同じアカウントが既に存在
		return 0;
	}
	if(auth_num>=auth_max){
		auth_max += 256;
		auth_dat = (struct mmo_account *)aRealloc(auth_dat,sizeof(auth_dat[0])*auth_max);
	}
	while(isGM(account_id_count) > 0)
		account_id_count++;
	if(account_id_count > END_ACCOUNT_NUM) {
		// 利用可能なID上限を超えた
		printf("account_new : ID is over END_ACCOUNT_NUM %d\n",END_ACCOUNT_NUM);
		return 0;
	}
	auth_dat[i].account_id = account_id_count++;
	auth_dat[i].sex        = account->sex;
	auth_dat[i].logincount = 0;
	auth_dat[i].state      = 0;
	strncpy(auth_dat[i].userid,account->userid,24);
	strncpy(auth_dat[i].pass  ,account->pass  ,24);
	strncpy(auth_dat[i].mail  ,account->mail  ,40);
	strcpy(auth_dat[i].lastlogin,"-");
	auth_dat[i].account_reg2_num = 0;
	auth_num++;
#ifdef TXT_JOURNAL
	if( login_journal_enable )
		journal_write( &login_journal, auth_dat[i].account_id, &auth_dat[i] );
#endif
	return 1;
}

void login_txt_final(void)
{
	if(auth_dat)
		aFree(auth_dat);
	if(gm_account_db)
		numdb_final(gm_account_db,gm_account_db_final);

#ifdef TXT_JOURNAL
	if( login_journal_enable )
	{
		journal_final( &login_journal );
	}
#endif
}

int login_txt_config_read_sub(const char* w1,const char* w2)
{
	if(strcmpi(w1,"account_filename")==0){
		strncpy(account_filename,w2,sizeof(account_filename) - 1);
	}
#ifdef TXT_JOURNAL
	else if(strcmpi(w1,"account_journal_enable")==0){
		login_journal_enable = atoi( w2 );
	}
	else if(strcmpi(w1,"account_journal_file")==0){
		strncpy( login_journal_file, w2, sizeof(login_journal_file) - 1 );
	}
	else if(strcmpi(w1,"account_journal_cache_interval")==0){
		login_journal_cache = atoi( w2 );
	}
#endif
	return 0;
}

#define login_init             login_txt_init
#define login_sync             login_txt_sync
#define login_final            login_txt_final
#define login_config_read_sub  login_txt_config_read_sub
#define account_new            login_txt_account_new
#define account_save           login_txt_account_save
#define account_delete         login_txt_account_delete
#define account_load_num       login_txt_account_load_num
#define account_load_str       login_txt_account_load_str
#define account_load_idx       login_txt_account_load_idx

#else /* TXT_ONLY */

unsigned short login_server_port = 3306;
char login_server_ip[32]      = "127.0.0.1";
char login_server_id[32]      = "ragnarok";
char login_server_pw[32]      = "ragnarok";
char login_server_db[32]      = "ragnarok";
char login_server_charset[32] = "";
char login_db[256]    = "login";
char loginlog_db[256] = "loginlog";
char reg_db[256]      = "global_reg_value";

// added to help out custom login tables, without having to recompile
// source so options are kept in the login_auriga.conf or the inter_auriga.conf
char login_db_account_id[256] = "account_id";
char login_db_userid[256]     = "userid";
char login_db_user_pass[256]  = "user_pass";
char login_db_level[256]      = "level";

static struct dbt *account_db;

int login_sql_init(void)
{
	// DB connection start
	mysql_init(&mysql_handle);
	printf("Connecting Database Server");
	if(login_server_charset[0]) {
		printf(" (charset: %s)",login_server_charset);
	}
	printf("...\n");

	if (!mysql_real_connect(&mysql_handle, login_server_ip, login_server_id, login_server_pw,
	    login_server_db, login_server_port, (char *)NULL, 0)) {
		// pointer check
		printf("%s\n", mysql_error(&mysql_handle));
		exit(1);
	} else {
		printf("connect success!\n");
	}
	if(login_server_charset[0]) {
		sprintf(tmp_sql,"SET NAMES %s",login_server_charset);
		if (mysql_query(&mysql_handle, tmp_sql)) {
			printf("DB server Error (charset)- %s\n", mysql_error(&mysql_handle));
		}
	}

	sprintf(
		tmp_sql, "INSERT DELAYED INTO `%s`(`time`,`log`) "
		"VALUES (NOW(), 'lserver 100 login server started')", loginlog_db
	);

	// query
	if (mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error - %s\n", mysql_error(&mysql_handle));
	}

	account_db = numdb_init();

	return 0;
}

static int account_db_final(void *key,void *data,va_list ap)
{
	struct mmo_account *p = (struct mmo_account *)data;

	aFree(p);

	return 0;
}

void login_sql_final(void)
{
	// set log.
	sprintf(
		tmp_sql,"INSERT DELAYED INTO `%s`(`time`,`log`) VALUES "
		"(NOW(), 'lserver 100 login server shutdown')",loginlog_db
	);

	// query
	if (mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error - %s\n", mysql_error(&mysql_handle));
	}

	mysql_close(&mysql_handle);
	printf("close DB connect....\n");

	numdb_final(account_db,account_db_final);
	if(gm_account_db)
		numdb_final(gm_account_db,gm_account_db_final);
}

void login_sql_sync(void)
{
	// nothing to do
}

int login_sql_config_read_sub(const char* w1,const char* w2)
{
	if(strcmpi(w1,"login_server_ip")==0){
		strncpy(login_server_ip, w2, sizeof(login_server_ip) - 1);
	}
	else if(strcmpi(w1,"login_server_port")==0){
		int n = atoi(w2);
		if (n < 1024 || n > 65535) {
			printf("Warning: Invalid login_server_port value: %d. Set to 3306 (default).\n", n);
			login_server_port = 3306; // default
		} else {
			login_server_port = (unsigned short)n;
		}
	}
	else if(strcmpi(w1,"login_server_id")==0){
		strncpy(login_server_id, w2, sizeof(login_server_id) - 1);
	}
	else if(strcmpi(w1,"login_server_pw")==0){
		strncpy(login_server_pw, w2, sizeof(login_server_pw) - 1);
	}
	else if(strcmpi(w1,"login_server_db")==0){
		strncpy(login_server_db, w2, sizeof(login_server_db) - 1);
	}
	else if(strcmpi(w1,"login_server_charset")==0){
		strncpy(login_server_charset, w2, sizeof(login_server_charset) - 1);
	}

	return 0;
}

int login_sql_account_delete(int account_id)
{
	struct mmo_account *ac = (struct mmo_account *)numdb_erase(account_db, account_id);

	if(ac)
		aFree(ac);

	sprintf(tmp_sql,"DELETE FROM `%s` WHERE `%s` = '%d'",login_db,login_db_account_id,account_id);
	if(mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (delete `%s`)- %s\n", login_db, mysql_error(&mysql_handle));
	}
	sprintf(tmp_sql,"DELETE FROM `%s` WHERE `type`='1' AND `account_id`='%d'", reg_db, account_id);
	if(mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (delete `%s`)- %s\n", reg_db, mysql_error(&mysql_handle));
	}
	return 0;
}

const struct mmo_account* login_sql_account_load_num(int account_id)
{
	struct mmo_account *ac = NULL;
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;

	if(account_id > END_ACCOUNT_NUM) {
		printf("login_sql_account_load_num :  ID is over END_ACCOUNT_NUM %d\n",END_ACCOUNT_NUM);
		return NULL;
	}

	ac = (struct mmo_account *)numdb_search(account_db, account_id);
	if(ac && ac->account_id == account_id) {
		// 既にキャッシュが存在する
		return ac;
	}

	// basic information
	sprintf(
		tmp_sql,
		"SELECT `%s`,`%s`,`lastlogin`,`logincount`,`sex`,`state`,`email` FROM `%s` WHERE `%s` = '%d'",
		login_db_userid,login_db_user_pass,login_db,login_db_account_id,account_id
	);
	if (mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (select `%s`)- %s\n", login_db, mysql_error(&mysql_handle));
	}
	sql_res = mysql_store_result(&mysql_handle);
	if (!sql_res) {
		printf("login_sql_account_load_num: DB result error ! \n");
		return NULL;
	}
	sql_row = mysql_fetch_row(sql_res);
	if (!sql_row) {
		// 未登録
		mysql_free_result(sql_res);
		return NULL;
	}

	if(ac == NULL) {
		ac = (struct mmo_account *)aMalloc(sizeof(struct mmo_account));
		numdb_insert(account_db,account_id,ac);
	}
	memset(ac,0,sizeof(struct mmo_account));

	ac->account_id = account_id;
	strncpy(ac->userid, sql_row[0], 24);
	strncpy(ac->pass, sql_row[1], 24);
	strncpy(ac->lastlogin ,sql_row[2], 24);
	ac->logincount = atoi(sql_row[3]);
	ac->sex        = sql_row[4][0];
	ac->state      = atoi(sql_row[5]);
	strncpy(ac->mail, sql_row[6], 40);
	mysql_free_result(sql_res);
	ac->sex = (ac->sex == 'S' ? 2 : ac->sex == 'M' ? 1 : 0);

	// force \0 terminal
	ac->userid[23]    = '\0';
	ac->pass[23]      = '\0';
	ac->lastlogin[23] = '\0';
	ac->mail[39]      = '\0';

	// global reg
	ac->account_reg2_num = 0;
	sprintf(tmp_sql, "SELECT `str`,`value` FROM `%s` WHERE `type`='1' AND `account_id`='%d'", reg_db, account_id);
	if (mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (select `%s`)- %s\n", reg_db, mysql_error(&mysql_handle));
	}
	sql_res = mysql_store_result(&mysql_handle);
	if (sql_res) {
		while( (sql_row = mysql_fetch_row(sql_res)) ) {
			strncpy(ac->account_reg2[ac->account_reg2_num].str,sql_row[0],32);
			ac->account_reg2[ac->account_reg2_num].str[31] = '\0';	// force \0 terminal
			ac->account_reg2[ac->account_reg2_num].value   = atoi(sql_row[1]);
			if(++ac->account_reg2_num >= ACCOUNT_REG2_NUM)
				break;
		}
	}
	mysql_free_result(sql_res);
	return ac;
}

const struct mmo_account* login_sql_account_load_str(const char *account_id)
{
	int id_num = -1;
	char buf[256];
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;

	if( !account_id[0] ) return NULL;
	sprintf(
		tmp_sql,"SELECT `%s`,`%s` FROM `%s` WHERE `%s` = '%s'",
		login_db_account_id,login_db_userid,login_db,login_db_userid,strecpy(buf,account_id)
	);
	if (mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (select `%s`)- %s\n", login_db, mysql_error(&mysql_handle));
	}
	sql_res = mysql_store_result(&mysql_handle);
	if (sql_res) {
		while( (sql_row = mysql_fetch_row(sql_res)) ) {
			if(strncmp(account_id, sql_row[1], 24) == 0) {
				id_num = atoi(sql_row[0]);
				break;
			}
		}
		mysql_free_result(sql_res);
	}
	if(id_num >= 0) {
		return login_sql_account_load_num(id_num);
	}
	return NULL;
}

const struct mmo_account* login_sql_account_load_idx(int idx)
{
	int id_num = -1;
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;

	if(idx < 0) return NULL;
	sprintf(
		tmp_sql,"SELECT `%s` FROM `%s` ORDER BY `%s` ASC LIMIT %d,1",
		login_db_account_id,login_db,login_db_account_id,idx
	);
	if (mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (select `%s`)- %s\n", login_db, mysql_error(&mysql_handle));
	}
	sql_res = mysql_store_result(&mysql_handle);
	if (sql_res) {
		sql_row = mysql_fetch_row(sql_res);
		if(sql_row) {
			id_num  = atoi(sql_row[0]);
		}
	}
	mysql_free_result(sql_res);
	if(id_num >= 0) {
		return login_sql_account_load_num(id_num);
	}
	return NULL;
}

int login_sql_account_save(struct mmo_account *ac2)
{
	char *p;
	char buf[256];
	const struct mmo_account *ac1;
	char sep = ' ';

	// アカウントの存在確認
	ac1 = login_sql_account_load_num(ac2->account_id);
	if(ac1 == NULL) return 0;

	// basic information
	p  = tmp_sql;
	p += sprintf(p,"UPDATE `%s` SET",login_db);

	// userid
	if(strcmp(ac1->userid,ac2->userid)) {
		p += sprintf(p,"%c`%s` = '%s'",sep,login_db_userid,strecpy(buf,ac2->userid));
		sep = ',';
	}

	// user_pass
	if(strcmp(ac1->pass,ac2->pass)) {
		p += sprintf(p,"%c`%s` = '%s'",sep,login_db_user_pass,strecpy(buf,ac2->pass));
		sep = ',';
	}

	// lastlogin
	if(strcmp(ac1->lastlogin,ac2->lastlogin)) {
		p += sprintf(p,"%c`lastlogin` = '%s'",sep,strecpy(buf,ac2->lastlogin));
		sep = ',';
	}

	// last_ip
	if(strcmp(ac1->lastip,ac2->lastip)) {
		p += sprintf(p,"%c`last_ip` = '%s'",sep,strecpy(buf,ac2->lastip));
		sep = ',';
	}

	// sex
	if(ac1->sex != ac2->sex) {
		p += sprintf(p,"%c`sex` = '%c'",sep,sex2str[ac2->sex]);
		sep = ',';
	}

	// logincount
	if(ac1->logincount != ac2->logincount) {
		p += sprintf(p,"%c`logincount` = '%d'",sep,ac2->logincount);
		sep = ',';
	}

	// state
	if(ac1->state != ac2->state) {
		p += sprintf(p,"%c`state` = '%d'",sep,ac2->state);
		sep = ',';
	}

	// mail
	if(strcmp(ac1->mail, ac2->mail)) {
		p += sprintf(p,"%c`email` = '%s'",sep,strecpy(buf,ac2->mail));
		sep = ',';
	}

	if(sep == ',') {
		sprintf(p," WHERE `%s` = '%d'",login_db_account_id,ac2->account_id);
		if (mysql_query(&mysql_handle, tmp_sql)) {
			printf("DB server Error (update `%s`)- %s\n", login_db, mysql_error(&mysql_handle));
		}
	}

	// account reg
	if(
		ac1->account_reg2_num != ac2->account_reg2_num ||
		memcmp(ac1->account_reg2,ac2->account_reg2,sizeof(ac1->account_reg2[0])*ac1->account_reg2_num)
	) {
		int i;
		sprintf(tmp_sql,"DELETE FROM `%s` WHERE `type`='1' AND `account_id`='%d'", reg_db, ac2->account_id);
		if(mysql_query(&mysql_handle, tmp_sql)) {
			printf("DB server Error (delete `%s`)- %s\n", reg_db, mysql_error(&mysql_handle));
		}
		for(i = 0;i < ac2->account_reg2_num ; i++) {
			sprintf(
				tmp_sql,
				"INSERT INTO `%s` (`type`, `account_id`, `str`, `value`) "
				"VALUES ( 1 , '%d' , '%s' , '%d')",
				reg_db, ac2->account_id,
				strecpy(buf,ac2->account_reg2[i].str),ac2->account_reg2[i].value
			);
			if(mysql_query(&mysql_handle, tmp_sql)) {
				printf("DB server Error (insert `%s`)- %s\n", reg_db, mysql_error(&mysql_handle));
			}
		}
	}

	{
		struct mmo_account *ac3 = (struct mmo_account *)numdb_search(account_db, ac2->account_id);
		if(ac3)
			memcpy(ac3, ac2, sizeof(struct mmo_account));
	}

	return 0;
}

int login_sql_account_new(struct mmo_account* account,const char *tmpstr)
{
	int j,c;
	char buf1[256],buf2[256],buf3[256];

	login_log("auth new %s %s %s",tmpstr,account->userid,account->pass);

	for(j=0;j<24 && (c=account->userid[j]);j++){
		if(c<0x20 || c==0x7f)
			return 0;
	}

	// force \0 terminal
	account->userid[23] = '\0';
	account->pass[23]   = '\0';
	account->mail[39]   = '\0';

	if(login_sql_account_load_str(account->userid)) {
		// 同じアカウントが既に存在
		return 0;
	}
	sprintf(
		tmp_sql,
		"INSERT INTO `%s` (`%s`,`%s`,`lastlogin`,`sex`,`logincount`,`%s`,`state`,`email`) "
		"VALUES('%s','%s',NOW(),'%c','0','0','0','%s')",
		login_db,login_db_userid,login_db_user_pass,login_db_level,
		strecpy(buf1,account->userid),strecpy(buf2,account->pass),
		sex2str[account->sex],strecpy(buf3,account->mail)
	);
	if(mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (insert `%s`)- %s\n", login_db, mysql_error(&mysql_handle));
	}
	return 1;
}

#define login_init            login_sql_init
#define login_sync            login_sql_sync
#define login_final           login_sql_final
#define login_config_read_sub login_sql_config_read_sub
#define account_new           login_sql_account_new
#define account_save          login_sql_account_save
#define account_delete        login_sql_account_delete
#define account_load_num      login_sql_account_load_num
#define account_load_str      login_sql_account_load_str
#define account_load_idx      login_sql_account_load_idx

#endif /* TXT_ONLY */

static void read_gm_account(void)
{
	char line[8192];
	struct gm_account *p;
	FILE *fp;
	int i, c, l;
	int account_id, level;
	int range, start_range, end_range;

	gm_account_db = numdb_init();

	if ((fp = fopen(GM_account_filename, "r")) == NULL) {
		printf("File not found: %s.\n", GM_account_filename);
		return;
	}

	line[sizeof(line)-1] = '\0';
	c = 0;
	l = 0;
	while(fgets(line, sizeof(line)-1, fp)) {
		l++;
		if ((line[0] == '/' && line[1] == '/') || line[0] == '\0' || line[0] == '\n' || line[0] == '\r')
			continue;

		if ((range = sscanf(line, "%d%*[-~]%d %d", &start_range, &end_range, &level)) == 3 ||
		    (range = sscanf(line, "%d%*[-~]%d:%d", &start_range, &end_range, &level)) == 3 ||
		    (range = sscanf(line, "%d %d", &start_range, &level)) == 2 ||
		    (range = sscanf(line, "%d:%d", &start_range, &level)) == 2 ||
		    (range = sscanf(line, "%d: %d", &start_range, &level)) == 2) {
			if (level <= 0) {
				printf("gm_account [%s]: invalid GM level [%ds] line %d\n", GM_account_filename, level, l);
			} else {
				if (level > 99)
					level = 99;
				if (range == 2) {
					end_range = start_range;
				} else if (end_range < start_range) {
					i = end_range;
					end_range = start_range;
					start_range = i;
				}
				for (account_id = start_range; account_id <= end_range; account_id++) {
					if ((p = (struct gm_account *)numdb_search(gm_account_db, account_id)) == NULL) {
						p = (struct gm_account *)aCalloc(1, sizeof(struct gm_account));
						numdb_insert(gm_account_db, account_id, p);
					}
					p->account_id = account_id;
					p->level = level;
					c++;
				}
			}
		} else {
			printf("gm_account: broken data [%s] line %d\n", GM_account_filename, l);
		}
	}
	fclose(fp);
	printf("gm_account: %s read done (%d gm account ID)\n", GM_account_filename, c);

	return;
}

static int isGM(int account_id)
{
	struct gm_account *p;

	if (gm_account_db == NULL)
		return 0;
	p = (struct gm_account *)numdb_search(gm_account_db, account_id);
	if (p == NULL)
		return 0;

	return p->level;
}

static int gm_account_db_final(void *key, void *data, va_list ap)
{
	struct gm_account *p = (struct gm_account *)data;

	aFree(p);

	return 0;
}

int login_log(char *fmt,...)
{
#ifdef TXT_ONLY
	FILE *logfp;
	va_list ap;

	va_start(ap,fmt);

	logfp=fopen(login_log_filename,"a");
	if(logfp){
		vfprintf(logfp,fmt,ap);
		fprintf(logfp,RETCODE);
		fclose(logfp);
	}

	va_end(ap);
#else
	char log[256], buf[512];
	va_list ap;

	va_start(ap,fmt);

	(void) vsnprintf(log,256,fmt,ap);
	va_end(ap);

	sprintf(
		tmp_sql,"INSERT INTO `%s` (`time`,`log`) VALUES (NOW(),'%s')",
		loginlog_db, strecpy(buf,log)
	);
	if(mysql_query(&mysql_handle, tmp_sql) ){
		printf("DB server Error (insert `%s`)- %s\n", loginlog_db, mysql_error(&mysql_handle) );
	}
#endif
	return 0;
}

// 認証
int mmo_auth(struct login_session_data* sd)
{
	char tmpstr[24];
	int len,newaccount=0;
	const struct mmo_account *ac;
	int encpasswdok=0;

	if(!sd)
		return 1;

#ifdef _WIN32
	{
		time_t time_;
		time(&time_);
		strftime(tmpstr,24,"%Y-%m-%d %H:%M:%S",localtime(&time_));
		sprintf(tmpstr+19,".%03d",0);
	}
#else
	{
		struct timeval tv;
		gettimeofday(&tv,NULL);
		strftime(tmpstr,24,"%Y-%m-%d %H:%M:%S",localtime(&(tv.tv_sec)));
		sprintf(tmpstr+19,".%03d",(int)tv.tv_usec/1000);
	}
#endif

	len = strlen(sd->userid) - 2;
	if (len >= 4 && len <= 21 && // to avoid invalid length (min 4 char for account name, max 23 including _F/_M)
	    sd->passwdenc == 0 && sd->userid[len] == '_' &&
	    (sd->userid[len+1] == 'F' || sd->userid[len+1] == 'M') &&
	    new_account_flag != 0) {
		// 新規アカウント作成
		char *adm_pass=strchr(sd->pass,'@');
		if(adm_pass==NULL)
			adm_pass="";
		else
			adm_pass++;

		if(strcmp(adm_pass,admin_pass)==0) {
			if(adm_pass[0])
				*(adm_pass-1)=0;

			newaccount=1;
			sd->userid[len]=0;
		} else {
			sd->userid[0]=0;
		}
	}

	ac = account_load_str(sd->userid);
	if(!ac){
		// アカウントが見つからない
		if(newaccount == 0){
			// 新規作成以外
			login_log("auth failed no account %s %s %d %s",tmpstr,sd->userid,newaccount,(sd->passwdenc == 0)? sd->pass: "");
		} else {
			// 新規作成
			struct mmo_account ac2;
			memset( &ac2, 0, sizeof(ac2) );
			memcpy(ac2.userid,sd->userid,24);
			memcpy(ac2.pass  ,sd->pass  ,24);
			ac2.sex = (sd->userid[len+1] == 'M')? 1: 0;
			if( !account_new(&ac2,tmpstr) ){
				// 作成失敗
				login_log("auth new failed %s %s %d %s",tmpstr,sd->userid,newaccount,sd->pass);
			}
		}
		return 0;
	}
	if(sd->passwdenc > 0){
		int j = sd->passwdenc;
		char md5str[192],md5bin[32];

		if(!sd->md5keylen){
			login_log("md5key not created %s %s",tmpstr,sd->userid);
			return 1;
		}
		if(j==4)
		{
			HMAC_MD5_Binary( ac->pass, strlen(ac->pass), sd->md5key, sd->md5keylen, md5bin );
			encpasswdok = ( memcmp( sd->pass, md5bin, 16) == 0);
		}
		else if(j<=3)
		{
			if(j>2) j=1;
			do {
				if(j==1) {
					snprintf(md5str, sizeof(md5str), "%s%s", sd->md5key, ac->pass);
				} else if(j==2) {
					snprintf(md5str, sizeof(md5str), "%s%s", ac->pass, sd->md5key);
				} else {
					md5str[0] = 0;
				}
				MD5_String2binary(md5str,md5bin);
				encpasswdok = ( memcmp( sd->pass, md5bin, 16) == 0);
			} while(j<2 && !encpasswdok && (j++) != sd->passwdenc);
		}
//		printf("key[%s] md5 [%s] ",md5key,md5);
//		printf("client [%s] accountpass [%s]\n",account->passwd,auth_dat[i].pass);
		if(!encpasswdok) {
			// 認証失敗
			char logbuf[1024],*p=logbuf;
			int j;
			p+=sprintf(p,"auth failed pass error %s %s enc=%d recv[",tmpstr,sd->userid,sd->passwdenc);
			for(j=0;j<16;j++)
				p+=sprintf(p,"%02x",((unsigned char *)sd->pass)[j]);
			p+=sprintf(p,"] calc[");
			for(j=0;j<16;j++)
				p+=sprintf(p,"%02x",((unsigned char *)md5bin)[j]);
			p+=sprintf(p,"] keylen=%d %d", sd->md5keylen, newaccount);
			login_log(logbuf);
			return 1;
		}
	} else if(strcmp(sd->pass,ac->pass) || newaccount) {
		// 認証失敗
		login_log("auth failed pass error %s %s %s %d",tmpstr,sd->userid,sd->pass,newaccount);
		return 1;
	}
	if(ac->state){
		login_log("auth banned account %s %s %s %d",tmpstr,sd->userid,ac->pass,ac->state);
		switch(ac->state) {
			case 1: return 2;
			case 2: return 3;
			case 3: return 4;
		}
		return 2;
	}
	// 認証成功
	login_log("auth ok %s %s new=%d",tmpstr,ac->userid,newaccount);
	{
		struct mmo_account ac2;
		memcpy(&ac2,ac,sizeof(struct mmo_account));
		memcpy(ac2.lastlogin,tmpstr,24);
		ac2.logincount++;
		memcpy(ac2.lastip,sd->lastip,16);
		account_save(&ac2);

		// session data 初期化
		sd->account_id = ac->account_id;
		sd->login_id1  = atn_rand();
		sd->login_id2  = atn_rand();
		sd->sex        = ac->sex;
		memcpy(sd->lastlogin,tmpstr,24);
	}
	return -1;	// 認証OK
}

// 自分以外の全てのcharサーバーにデータ送信（送信したchar鯖の数を返す）
int charif_sendallwos(int sfd,unsigned char *buf,unsigned int len)
{
	int i,c;
	for(i=0,c=0;i<MAX_CHAR_SERVERS;i++){
		int fd;
		if((fd=server_fd[i])>0 && fd!=sfd){
			memcpy(WFIFOP(fd,0),buf,len);
			WFIFOSET(fd,len);
			c++;
		}
	}
	return c;
}

// authfifoの比較
static int cmp_authfifo(int i,int account_id,int login_id1,int login_id2,unsigned long ip)
{
	if( auth_fifo[i].account_id == account_id && auth_fifo[i].login_id1 == login_id1 )
		return 1;

#ifdef CMP_AUTHFIFO_LOGIN2
	//printf("cmp_authfifo: id2 check %d %x %x = %08x %08x %08x\n",i,auth_fifo[i].login_id2,login_id2,
	//	auth_fifo[i].account_id,auth_fifo[i].login_id1,auth_fifo[i].login_id2);
	if( auth_fifo[i].login_id2 == login_id2 && login_id2 != 0 )
		return 1;
#endif

#ifdef CMP_AUTHFIFO_IP
	//printf("cmp_authfifo: ip check %d %x %x = %08x %08x %08x\n",i,auth_fifo[i].ip,ip,
	//	auth_fifo[i].account_id,auth_fifo[i].login_id1,auth_fifo[i].login_id2);
	if( auth_fifo[i].ip == ip && ip != 0 && ip != 0xffffffff)
		return 1;
#endif
	return 0;
}

int parse_char_disconnect(int fd)
{
	int i;

	for(i=0;i<MAX_CHAR_SERVERS;i++)
		if(server_fd[i]==fd)
			server_fd[i]=-1;
	close(fd);
	delete_session(fd);

	return 0;
}

int parse_fromchar(int fd)
{
	int i,id;

	for(id=0; id<MAX_CHAR_SERVERS; id++) {
		if(server_fd[id] == fd)
			break;
	}
	if(id >= MAX_CHAR_SERVERS)
		session[fd]->eof = 1;

	while(RFIFOREST(fd) >= 2) {
		switch(RFIFOW(fd,0)) {

		case 0x2712:	// キャラクター鯖へのログイン認証
			if(RFIFOREST(fd)<23)
				return 0;
			for(i=0; i<AUTH_FIFO_SIZE; i++) {
				if( cmp_authfifo(i,RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10),RFIFOL(fd,15)) &&
				    auth_fifo[i].sex == RFIFOB(fd,14) &&
				    !auth_fifo[i].delflag )
				{
					auth_fifo[i].delflag = 1;
					break;
				}
			}

			if(i >= AUTH_FIFO_SIZE) {
				WFIFOW(fd,0)=0x2713;
				WFIFOL(fd,2)=RFIFOL(fd,2);
				WFIFOB(fd,6)=1;
				WFIFOSET(fd,15);
				//printf("auth_fifo search error! account_id = %d\n",RFIFOL(fd,2));
			} else {
				int p,j;
				const struct mmo_account *ac = account_load_num(auth_fifo[i].account_id);
				// account_reg送信
				if(ac) {
					WFIFOW(fd,0) = 0x2729;
					WFIFOL(fd,4) = ac->account_id;
					for(p=8,j=0; j < ac->account_reg2_num; p+=36,j++) {
						memcpy(WFIFOP(fd,p),ac->account_reg2[j].str,32);
						WFIFOL(fd,p+32) = ac->account_reg2[j].value;
					}
					WFIFOW(fd,2) = p;
					WFIFOSET(fd,p);
//					printf("account_reg2 send : login->char (auth fifo)\n");
				}

				WFIFOW(fd,0)=0x2713;
				WFIFOL(fd,2)=RFIFOL(fd,2);
				WFIFOB(fd,6)=0;
				WFIFOL(fd,7)=auth_fifo[i].account_id;
				WFIFOL(fd,11)=auth_fifo[i].login_id1;
				WFIFOSET(fd,15);
			}
			RFIFOSKIP(fd,23);
			break;

		case 0x2714:	// ワールドのユーザー数通知
			//printf("set users %s : %d\n",server[id].name,RFIFOL(fd,2));
			server[id].users=RFIFOL(fd,2);
			RFIFOSKIP(fd,6);
			break;
		case 0x2715:	// メールアドレス認証
			if(RFIFOREST(fd)<50)
				return 0;
			{
#ifdef AC_MAIL
				const struct mmo_account *ac = account_load_num(RFIFOL(fd,2));
				//printf("login 0x2715 mail[%s:%s]\n",ac->mail,RFIFOP(fd,10));
				WFIFOB(fd,10)=(ac && strcmp(ac->mail,RFIFOP(fd,10))==0)?0:1;
#else
				WFIFOB(fd,10)=0;
#endif
				WFIFOW(fd, 0)=0x2716;
				WFIFOL(fd, 2)=RFIFOL(fd,2);
				WFIFOL(fd, 6)=RFIFOL(fd,6);
				WFIFOSET(fd,11);
				RFIFOSKIP(fd,50);
			}
			return 0;

		case 0x2720:
			// GMになりたーい
			// SQL 化が面倒なのでとりあえず保留
			WFIFOW(fd,0)=0x2721;
			WFIFOL(fd,2)=RFIFOL(fd,4);
			WFIFOL(fd,6)=RFIFOL(fd,4);
			WFIFOSET(fd,10);
			RFIFOSKIP(fd,RFIFOW(fd,2));
			return 0;

		case 0x2722:	// changesex
			if(RFIFOREST(fd)<4 || RFIFOREST(fd)<RFIFOW(fd,2))
				return 0;
			{
				const struct mmo_account *ac = account_load_num(RFIFOL(fd,4));
				if(ac) {
					struct mmo_account ac2;
					memcpy(&ac2,ac,sizeof(struct mmo_account));
					ac2.sex = RFIFOB(fd,8);
					account_save(&ac2);
				}
				WFIFOW(fd,0) = 0x2723;
				WFIFOL(fd,2) = RFIFOL(fd,4);
				WFIFOB(fd,6) = RFIFOB(fd,8);
				WFIFOSET(fd,7);
				RFIFOSKIP(fd,RFIFOW(fd,2));
			}
			return 0;

		case 0x2728:	// save account_reg
			if(RFIFOREST(fd)<4 || RFIFOREST(fd)<RFIFOW(fd,2))
				return 0;
			{
				int p,j;
				const struct mmo_account *ac = account_load_num(RFIFOL(fd,4));
				if(ac) {
					unsigned char buf[ACCOUNT_REG2_NUM*36+16];
					struct mmo_account ac2;
					memcpy(&ac2,ac,sizeof(struct mmo_account));
					for(p=8,j=0;p<RFIFOW(fd,2) && j<ACCOUNT_REG2_NUM;p+=36,j++){
						strncpy(ac2.account_reg2[j].str,RFIFOP(fd,p),32);
						ac2.account_reg2[j].str[31] = '\0';	// force \0 terminal
						ac2.account_reg2[j].value   = RFIFOL(fd,p+32);
					}
					ac2.account_reg2_num = j;
					account_save(&ac2);

					// 他のサーバーへポスト（同垢ログインがなければ送らなくていい）
					memcpy(WBUFP(buf,0),RFIFOP(fd,0),RFIFOW(fd,2));
					WBUFW(buf,0)=0x2729;
					charif_sendallwos(fd,buf,WBUFW(buf,2));
				}
				RFIFOSKIP(fd,RFIFOW(fd,2));
				//printf("login: save account_reg (from char)\n");
			}
			break;

		case 0x272b:	// charサーバメンテナンス状態
			if(RFIFOREST(fd)<3)
				return 0;
			server[id].maintenance=RFIFOB(fd,2);
			// charサーバに応答
			WFIFOW(fd,0)=0x272c;
			WFIFOB(fd,2)=server[id].maintenance;
			WFIFOSET(fd,3);

			RFIFOSKIP(fd,3);
			break;

		default:
			printf("login: unknown packet %x! (from char).\n",RFIFOW(fd,0));
			close(fd);
			session[fd]->eof=1;
			return 0;
		}
	}
	return 0;
}

int parse_admin_disconnect(int fd)
{
	int i;

	for(i=0;i<MAX_CHAR_SERVERS;i++)
		if(server_fd[i]==fd)
			server_fd[i]=-1;
	close(fd);
	delete_session(fd);
	return 0;
}

int parse_admin(int fd)
{
	int i;

	while(RFIFOREST(fd)>=2){
		switch(RFIFOW(fd,0)){
		case 0x7530:	// Auriga情報取得
			WFIFOW(fd,0)=0x7531;
			WFIFOB(fd,2)=AURIGA_MAJOR_VERSION;
			WFIFOB(fd,3)=AURIGA_MINOR_VERSION;
			WFIFOW(fd,4)=AURIGA_REVISION;
			WFIFOB(fd,6)=AURIGA_RELEASE_FLAG;
			WFIFOB(fd,7)=AURIGA_OFFICIAL_FLAG;
			WFIFOB(fd,8)=AURIGA_SERVER_LOGIN;
			WFIFOB(fd,9)=AURIGA_MOD_VERSION;
			WFIFOSET(fd,10);
			RFIFOSKIP(fd,2);
			break;

		case 0x7532:	// 接続の切断(defaultと処理は一緒だが明示的にするため)
			RFIFOSKIP(fd,2);
			close(fd);
			session[fd]->eof=1;
			return 0;

		case 0x7920:
			if(RFIFOREST(fd)<11)
				return 0;
			{
				// アカウントリスト
				int st  = RFIFOL(fd,2);
				int ed  = RFIFOL(fd,6);
				int len = 4;
				const struct mmo_account* ac;
				if(st<0)st=0;
				if(ed>END_ACCOUNT_NUM || ed<st || ed<=0) ed=END_ACCOUNT_NUM;
				i = 0;
				do
				{
					WFIFOW(fd,0)=0x7921;
					len = 4;
					while( (ac = account_load_idx(i++) ) && len<=65000 ) {
						WFIFORESERVE(fd,len+61);
						if(ac->account_id >= st && ac->account_id <= ed){
							WFIFOL(fd,len   ) = ac->account_id;
							memcpy(WFIFOP(fd,len+4),ac->userid,24);
							WFIFOB(fd,len+28) = ac->sex;
							WFIFOL(fd,len+53) = ac->logincount;
							WFIFOL(fd,len+57) = ac->state;
							len+=61;
						}
					}
					WFIFOW(fd,2)=len;
					WFIFOSET(fd,len);
				}while( len>65000 );
				RFIFOSKIP(fd,11);
			}
			break;

		case 0x7930:
			if(RFIFOREST(fd)<4 || RFIFOREST(fd)<RFIFOW(fd,2))
				return 0;
			if (RFIFOW(fd,2) != 53 && RFIFOW(fd,2) != 93) {
				RFIFOSKIP(fd,RFIFOW(fd,2));
				return 0;
			}
			{
				// アカウント作成
				struct mmo_account ma;
				memset( &ma, 0, sizeof(ma) );
				memcpy(ma.userid,RFIFOP(fd, 4),24);
				memcpy(ma.pass,RFIFOP(fd,28),24);
				ma.sex = (RFIFOB(fd,52) == 'M')? 1: 0;
				if( RFIFOW(fd,2) > 53 )
					memcpy(ma.mail,RFIFOP(fd,53),40);
				WFIFOW(fd,0) = 0x7931;
				WFIFOW(fd,2) = 0;
				memcpy(WFIFOP(fd,4),RFIFOP(fd,4),24);
				if( !account_new(&ma,"( ladmin )") ) {
					WFIFOW(fd,2)=1;
				}
				WFIFOSET(fd,28);
				RFIFOSKIP(fd,RFIFOW(fd,2));
			}
			break;

		case 0x7932:
			// アカウント削除
			if(RFIFOREST(fd)<4 || RFIFOREST(fd)<RFIFOW(fd,2))
				return 0;
			if (RFIFOW(fd,2) != 28) {
				RFIFOSKIP(fd,RFIFOW(fd,2));
				return 0;
			}
			{
				char userid[24];
				const struct mmo_account *ac;
				memcpy(userid, RFIFOP(fd,4), 24);
				userid[23] = '\0';	// force \0 terminal
				ac = account_load_str(userid);
				WFIFOW(fd,0) = 0x7933;
				WFIFOW(fd,2) = 1;
				memcpy(WFIFOP(fd,4),RFIFOP(fd,4),24);
				if(ac) {
					// キャラサーバーへ削除通知
					unsigned char buf[8];
					WBUFW(buf,0) = 0x272a;
					WBUFL(buf,2) = ac->account_id;
					charif_sendallwos(-1,buf,6);
					WFIFOW(fd,2) = 0;
					account_delete(ac->account_id);
				}
				WFIFOSET(fd,28);
				RFIFOSKIP(fd,RFIFOW(fd,2));
			}
			break;

		case 0x7934:
			// パスワード変更
			if(RFIFOREST(fd)<4 || RFIFOREST(fd)<RFIFOW(fd,2))
				return 0;
			if (RFIFOW(fd,2) != 52) {
				RFIFOSKIP(fd,RFIFOW(fd,2));
				return 0;
			}
			{
				char userid[24];
				const struct mmo_account *ac;
				memcpy(userid, RFIFOP(fd,4), 24);
				userid[23] = '\0';	// force \0 terminal
				ac = account_load_str(userid);
				WFIFOW(fd,0)=0x7935;
				WFIFOW(fd,2)=1;
				memcpy(WFIFOP(fd,4),RFIFOP(fd,4),24);
				if(ac) {
					struct mmo_account ac2;
					memcpy(&ac2,ac,sizeof(struct mmo_account));
					strncpy(ac2.pass,RFIFOP(fd,28),24);
					ac2.pass[23] = '\0';	// force \0 terminal
					account_save(&ac2);
					WFIFOW(fd,2)=0;
				}
				WFIFOSET(fd,28);
				RFIFOSKIP(fd,RFIFOW(fd,2));
			}
			break;

		case 0x7936:
			// バン状態変更
			if(RFIFOREST(fd)<4 || RFIFOREST(fd)<RFIFOW(fd,2))
				return 0;
			if (RFIFOW(fd,2) != 32) {
				RFIFOSKIP(fd,RFIFOW(fd,2));
				return 0;
			}
			{
				char userid[24];
				const struct mmo_account *ac;
				memcpy(userid, RFIFOP(fd,4), 24);
				userid[23] = '\0';	// force \0 terminal
				ac = account_load_str(userid);
				WFIFOW(fd, 0) = 0x7937;
				WFIFOW(fd, 2) = 1;
				WFIFOL(fd,28) = 0;
				memcpy(WFIFOP(fd,4),RFIFOP(fd,4),24);
				if(ac) {
					struct mmo_account ac2;
					memcpy(&ac2,ac,sizeof(struct mmo_account));
					ac2.state=RFIFOL(fd,28);
					account_save(&ac2);
					WFIFOW(fd, 2) = 0;
					WFIFOL(fd,28) = ac2.state;
				}
				WFIFOSET(fd,32);
				RFIFOSKIP(fd,RFIFOW(fd,2));
			}
			break;

		case 0x7938:
			// information about servers
			server_num = 0;
			for(i = 0; i < MAX_CHAR_SERVERS; i++) { // max number of char-servers (and account_id values: 0 to max-1)
				if (server_fd[i] >= 0) {
					WFIFOL(fd,4 + server_num * 32     ) = server[i].ip;
					WFIFOW(fd,4 + server_num * 32 +  4) = server[i].port;
					strncpy(WFIFOP(fd,4 + server_num * 32 + 6), server[i].name, 20);
					WFIFOW(fd,4 + server_num * 32 + 26) = server[i].users;
					WFIFOW(fd,4 + server_num * 32 + 28) = server[i].maintenance;
					WFIFOW(fd,4 + server_num * 32 + 30) = server[i].new_;
					server_num++;
				}
			}
			WFIFOW(fd,0) = 0x7939;
			WFIFOW(fd,2) = 4 + 32 * server_num;
			WFIFOSET(fd, 4 + 32 * server_num);

			RFIFOSKIP(fd,2);
			break;

		case 0x793a:
			// request to test a password
			if(RFIFOREST(fd) < 50)
				return 0;
			{
				char userid[24];
				const struct mmo_account *ac;
				memcpy(userid, RFIFOP(fd,2), 24);
				userid[23] = '\0';	// force \0 terminal
				ac = account_load_str(userid);
				WFIFOW(fd, 0) = 0x793b;
				WFIFOW(fd, 2) = 1;
				memcpy(WFIFOP(fd,4), RFIFOP(fd,2), 24);
				if(ac) {
					if(memcmp(ac->pass, RFIFOP(fd,26), 24) == 0) {
						WFIFOW(fd, 2) = 0;
					}
				}
				WFIFOSET(fd,28);
				RFIFOSKIP(fd,50);
			}
			break;

		case 0x793c:
			// request to obtain complete information about an account. (by name)
			if(RFIFOREST(fd) < 26)
				return 0;
			{
				char userid[24];
				const struct mmo_account *ac;
				memcpy(userid, RFIFOP(fd,2), 24);
				userid[23] = '\0';	// force \0 terminal
				ac = account_load_str(userid);
				memset(WFIFOP(fd,0), 0, 120);
				WFIFOW(fd, 0) = 0x793e;
				WFIFOW(fd, 2) = 1;
				memcpy(WFIFOP(fd,9), RFIFOP(fd,2), 24);
				if(ac) {
					WFIFOW(fd, 2) = 0;
					WFIFOL(fd, 4) = ac->account_id;
					WFIFOB(fd, 8) = isGM(ac->account_id);
					//memcpy(WFIFOP(fd, 9), ac->userid, 24);
					WFIFOB(fd,33) = ac->sex;
					WFIFOL(fd,34) = ac->logincount;
					WFIFOW(fd,38) = ac->state;
					memcpy(WFIFOP(fd,40), ac->lastip, 16);
					memcpy(WFIFOP(fd,56), ac->lastlogin, 24);
					memcpy(WFIFOP(fd,80), ac->mail, 40);
				}
				WFIFOSET(fd,120);
				RFIFOSKIP(fd,26);
			}
			break;

		case 0x793d:
			// request to obtain complete information about an account. (by id)
			if(RFIFOREST(fd) < 6)
				return 0;
			{
				const struct mmo_account *ac = account_load_num(RFIFOL(fd,2));
				memset(WFIFOP(fd,0), 0, 120);
				WFIFOW(fd, 0) = 0x793e;
				WFIFOW(fd, 2) = 1;
				WFIFOL(fd, 4) = RFIFOL(fd,2);
				if(ac) {
					WFIFOW(fd, 2) = 0;
					//WFIFOL(fd, 4) = ac->account_id;
					WFIFOB(fd, 8) = isGM(ac->account_id);
					memcpy(WFIFOP(fd, 9), ac->userid, 24);
					WFIFOB(fd,33) = ac->sex;
					WFIFOL(fd,34) = ac->logincount;
					WFIFOW(fd,38) = ac->state;
					memcpy(WFIFOP(fd,40), ac->lastip, 16);
					memcpy(WFIFOP(fd,56), ac->lastlogin, 24);
					memcpy(WFIFOP(fd,80), ac->mail, 40);
				}
				WFIFOSET(fd,120);
				RFIFOSKIP(fd,6);
			}
			break;

		default:
			close(fd);
			session[fd]->eof=1;
			return 0;
		}
	}

	return 0;
}

int parse_login_disconnect(int fd)
{
	int i;

	for(i=0;i<MAX_CHAR_SERVERS;i++)
		if(server_fd[i]==fd)
	server_fd[i]=-1;
	close(fd);
	delete_session(fd);
	return 0;
}

int parse_login(int fd)
{
	struct login_session_data *sd;

	if(session[fd]->session_data == NULL) {
		session[fd]->session_data = aCalloc(1,sizeof(struct login_session_data));
	}
	sd = (struct login_session_data *)session[fd]->session_data;

	while(RFIFOREST(fd)>=2){
		int cmd = RFIFOW(fd,0);
		if(cmd < 0x7530) {
			if(cmd == 0x64 || cmd == 0x01dd || cmd == 0x027c || cmd == 0x0277)
				printf("parse_login : %d %3d 0x%04x %-24s\n",fd,RFIFOREST(fd),cmd,(char*)RFIFOP(fd,6));
			else
				printf("parse_login : %d %3d 0x%04x\n",fd,RFIFOREST(fd),cmd);
		}

		switch(cmd) {
		case 0x204:		// 2004-06-22暗号化ragexe対応
			if(RFIFOREST(fd)<18)
				return 0;
			RFIFOSKIP(fd,18);
			break;
		case 0x200:		// クライアントでaccountオプション使用時の謎パケットへの対応
			if(RFIFOREST(fd)<26)
				return 0;
			RFIFOSKIP(fd,26);
			break;
		case 0x258:		// 2005-12-14 nProtect関係 Part 1
			memset(WFIFOP(fd,0),0,18);
			WFIFOW(fd,0)=0x0227;
			WFIFOSET(fd,18);
			RFIFOSKIP(fd,2);
			break;
		case 0x228:		// 2005-12-14 nProtect関係 Part 2
			if(RFIFOREST(fd)<18)
				return 0;
			WFIFOW(fd,0)=0x0259;
			WFIFOB(fd,2)=1;
			WFIFOSET(fd,3);
			RFIFOSKIP(fd,18);
			break;

		case 0x0064:	// クライアントログイン要求
		case 0x01dd:	// 暗号化ログイン要求
		case 0x0277:	// クライアントログイン要求？
		case 0x027c:	// 暗号化ログイン要求
		case 0x02b0:	// クライアントログイン要求（langtype=0）
		{
			int length = 0, result = -1;
			int enc_flag;

			switch(cmd) {
				case 0x0064: length = 55; break;
				case 0x01dd: length = 47; break;
				case 0x0277: length = 84; break;
				case 0x027c: length = 60; break;
				case 0x02b0: length = 85; break;
			}
			if(length == 0 || RFIFOREST(fd) < length)
				return 0;

			enc_flag = (cmd == 0x1dd || cmd == 0x27c);

			memcpy(sd->userid,RFIFOP(fd,6),24);
			sd->userid[23] = '\0';
			if(enc_flag) {
				memcpy(sd->pass, RFIFOP(fd,30), 16);
				sd->pass[16] = '\0';	// binary data
			} else {
				memcpy(sd->pass, RFIFOP(fd,30), 24);
				sd->pass[23] = '\0';
			}

			{
				unsigned char *p = (unsigned char *)&session[fd]->client_addr.sin_addr;
				sprintf(sd->lastip,"%d.%d.%d.%d",p[0],p[1],p[2],p[3]);
				login_log("client connection request %s from %s", sd->userid, sd->lastip);
			}

			if( login_version > 0 && login_version != RFIFOL(fd,2) )	// 規定外のバージョンからの接続を拒否
				result = 5;
			if( login_type > 0 && login_type != ((enc_flag)? RFIFOB(fd,46): RFIFOB(fd,54)) )	// 規定外のタイプからの接続を拒否
				result = 5;
			if( strlen(sd->userid) < 4 )	// IDが4字未満を拒否
				result = 3;
			if( !enc_flag && strlen(sd->pass) < 4 ) // 暗号化PASSはmd5符号なので \0 が含まれる可能性有り
				result = 3;
#ifdef PASSWORDENC
			sd->passwdenc = (enc_flag)? PASSWORDENC: 0;
#else
			sd->passwdenc = 0;
#endif
			if(result == -1) {
				result = mmo_auth(sd);
			}
			if(result == -1) {
				int i;
				if(detect_multiple_login) {
					int c = 0;
					unsigned char buf[8];

					// 全charサーバへ同一アカウントの切断要求
					WBUFW(buf,0) = 0x2730;
					WBUFL(buf,2) = sd->account_id;
					charif_sendallwos(-1,buf,6);

					for(i=0; i<AUTH_FIFO_SIZE; i++) {
						if(auth_fifo[i].account_id == sd->account_id && !auth_fifo[i].delflag) {
							auth_fifo[i].delflag = 1;
							c++;
						}
					}
					if(c > 0) {
						// 二重ログインの可能性があるので認証失敗にする
						WFIFOW(fd,0) = 0x81;
						WFIFOB(fd,2) = 8;
						WFIFOSET(fd,3);
						RFIFOSKIP(fd,length);
						break;
					}
				}
				server_num = 0;
				for(i=0; i<MAX_CHAR_SERVERS; i++) {
					if(server_fd[i] >= 0) {
						WFIFOL(fd,47+server_num*32)   = server[i].ip;
						WFIFOW(fd,47+server_num*32+4) = server[i].port;
						memcpy(WFIFOP(fd,47+server_num*32+6), server[i].name, 20);
						WFIFOW(fd,47+server_num*32+26) = server[i].users;
						WFIFOW(fd,47+server_num*32+28) = server[i].maintenance;
						WFIFOW(fd,47+server_num*32+30) = server[i].new_;
						server_num++;
					}
				}
				WFIFOW(fd, 0) = 0x69;
				WFIFOW(fd, 2) = 47+32*server_num;
				WFIFOL(fd, 4) = sd->login_id1;
				WFIFOL(fd, 8) = sd->account_id;
				WFIFOL(fd,12) = sd->login_id2;
				WFIFOL(fd,16) = 0;
				memcpy(WFIFOP(fd,20),sd->lastlogin,24);
				WFIFOB(fd,46) = sd->sex;
				WFIFOSET(fd,47+32*server_num);

				for(i=0; i<AUTH_FIFO_SIZE; i++) {
					if( cmp_authfifo(i,sd->account_id,sd->login_id1,sd->login_id2,session[fd]->client_addr.sin_addr.s_addr) &&
					    auth_fifo[i].sex == sd->sex &&
					    !auth_fifo[i].delflag )
					{
						auth_fifo[i].delflag = 1;
						break;
					}
				}
				if(auth_fifo_pos >= AUTH_FIFO_SIZE) {
					auth_fifo_pos = 0;
				}
				auth_fifo[auth_fifo_pos].account_id = sd->account_id;
				auth_fifo[auth_fifo_pos].login_id1  = sd->login_id1;
				auth_fifo[auth_fifo_pos].login_id2  = sd->login_id2;
				auth_fifo[auth_fifo_pos].sex        = sd->sex;
				auth_fifo[auth_fifo_pos].delflag    = 0;
				auth_fifo[auth_fifo_pos].tick       = gettick();
				auth_fifo[auth_fifo_pos].ip         = session[fd]->client_addr.sin_addr.s_addr;
				auth_fifo_pos++;

				session[fd]->auth = 1; // 認証終了を socket.c に伝える
			} else {
				memset(WFIFOP(fd,0),0,23);
				WFIFOW(fd,0) = 0x6a;
				WFIFOB(fd,2) = result;
				WFIFOSET(fd,23);
			}
			RFIFOSKIP(fd,length);
		}
			break;

		case 0x01db:	// 暗号化Key送信要求
		case 0x272d:	// Charの暗号化ログイン要求
		case 0x791a:	// 管理パケットで暗号化key要求
		{
			int i;

			RFIFOSKIP(fd, 2);
			if(sd->md5keylen){
				printf("login: illegal md5key request.");
				close(fd);
				session[fd]->eof=1;
				return 0;
			}
			// 暗号化用のチャレンジ生成
			sd->md5keylen = atn_rand()%(sizeof(sd->md5key)/4)+(sizeof(sd->md5key)-sizeof(sd->md5key)/4);
			for(i=0;i<sd->md5keylen;i++) {
				sd->md5key[i] = atn_rand()%255+1;
			}
			sd->md5key[i] = 0;

			WFIFOW(fd,0)= (cmd == 0x272d) ? 0x272e : 0x01dc;
			WFIFOW(fd,2)=4+sd->md5keylen;
			memcpy(WFIFOP(fd,4),sd->md5key,sd->md5keylen);
			WFIFOSET(fd,WFIFOW(fd,2));
			break;
		}

		case 0x2710:	// Charサーバー接続要求
		case 0x272f:	// Charサーバー接続要求(暗号化ログイン)
			if(RFIFOREST(fd)<84)
				return 0;
			if( login_sport != 0 && login_port != login_sport && session[fd]->server_port != login_sport ) {
				printf("server login failed: connected port %d\n", session[fd]->server_port);
				RFIFOSKIP(fd,84);
				session[fd]->eof = 1;
				return 0;
			}
			{
				unsigned char *p = (unsigned char *)&session[fd]->client_addr.sin_addr;
				sprintf(sd->lastip,"%d.%d.%d.%d",p[0],p[1],p[2],p[3]);
				login_log(
					"server connection request %s @ %d.%d.%d.%d:%d (%s)",
					RFIFOP(fd,60),RFIFOB(fd,54),RFIFOB(fd,55),RFIFOB(fd,56),RFIFOB(fd,57),
					RFIFOW(fd,58),sd->lastip
				);
			}
			memcpy( sd->userid, RFIFOP(fd, 2), 24 );
			memcpy( sd->pass, RFIFOP(fd, 26), sd->md5keylen ? 16 : 24 );
			sd->passwdenc = sd->md5keylen ? RFIFOL(fd,46) : 0;

			if(mmo_auth(sd) == -1 && sd->sex == 2 && sd->account_id<MAX_CHAR_SERVERS && server_fd[sd->account_id]<0){
				server[sd->account_id].ip=RFIFOL(fd,54);
				server[sd->account_id].port=RFIFOW(fd,58);
				memcpy(server[sd->account_id].name,RFIFOP(fd,60),20);
				server[sd->account_id].users=0;
				server[sd->account_id].maintenance=RFIFOW(fd,80);
				server[sd->account_id].new_=RFIFOW(fd,82);
				server_fd[sd->account_id]=fd;
				WFIFOW(fd,0)=0x2711;
				WFIFOB(fd,2)=0;
				WFIFOSET(fd,3);
				session[fd]->func_parse    = parse_fromchar;
				session[fd]->func_destruct = parse_char_disconnect;
				realloc_fifo(fd, RFIFOSIZE_SERVERLINK, WFIFOSIZE_SERVERLINK);
				session[fd]->auth = -1; // 認証終了を socket.c に伝える
			} else {
				WFIFOW(fd,0)=0x2711;
				WFIFOB(fd,2)=3;
				WFIFOSET(fd,3);
			}
			RFIFOSKIP(fd,84);
			return 0;

		case 0x7530:	// Auriga情報取得
			WFIFOW(fd,0)=0x7531;
			WFIFOB(fd,2)=AURIGA_MAJOR_VERSION;
			WFIFOB(fd,3)=AURIGA_MINOR_VERSION;
			WFIFOW(fd,4)=AURIGA_REVISION;
			WFIFOB(fd,6)=AURIGA_RELEASE_FLAG;
			WFIFOB(fd,7)=AURIGA_OFFICIAL_FLAG;
			WFIFOB(fd,8)=AURIGA_SERVER_LOGIN;
			WFIFOB(fd,9)=AURIGA_MOD_VERSION;
			WFIFOSET(fd,10);
			RFIFOSKIP(fd,2);
			break;
		case 0x7532:	// 接続の切断(defaultと処理は一緒だが明示的にするため)
			RFIFOSKIP(fd,2);
			close(fd);
			session[fd]->eof=1;
			return 0;

		case 0x7918:	// 管理モードログイン
			{
				struct login_session_data *ld = (struct login_session_data *)session[fd]->session_data;
				if (RFIFOREST(fd) < 6 || RFIFOREST(fd)<RFIFOW(fd,2) || RFIFOREST(fd) < ((RFIFOW(fd,4) == 0) ? 30 : 22))
					return 0;
				if (RFIFOW(fd,2) != ((RFIFOW(fd,4) == 0) ? 30 : 22)) {
					printf("server login failed: invalid length %d\n", (int)RFIFOW(fd,2));
					session[fd]->eof = 1;
					return 0;
				}
				if( login_sport != 0 && login_port != login_sport && session[fd]->server_port != login_sport ) {
					printf("server login failed: connected port %d\n", session[fd]->server_port);
					RFIFOSKIP(fd,RFIFOW(fd,2));
					session[fd]->eof = 1;
					return 0;
				}
				WFIFOW(fd,0)=0x7919;
				WFIFOB(fd,2)=1;

				if(RFIFOW(fd,4)==0){	// プレーン
					if(strcmp(RFIFOP(fd,6),ladmin_pass)==0){
						WFIFOB(fd,2)=0;
						session[fd]->func_parse=parse_admin;
						session[fd]->func_destruct = parse_admin_disconnect;
						session[fd]->auth = -1; // 認証終了を socket.c に伝える
					}
				}else{					// 暗号化
					if(!ld){
						printf("login: md5key not created for admin login\n");
					}else{
						char md5str[192]="",md5bin[32];
						if(RFIFOW(fd,4)==1){
							strncpy(md5str,ld->md5key,sizeof(md5str)-sizeof(ladmin_pass)-1);
							strcat(md5str,ladmin_pass);
						}else if(RFIFOW(fd,4)==2){
							strncpy(md5str,ladmin_pass,sizeof(md5str)-sizeof(ld->md5key)-1);
							strcat(md5str,ld->md5key);
						};
						MD5_String2binary(md5str,md5bin);
						if(memcmp(md5bin,RFIFOP(fd,6),16)==0){
							WFIFOB(fd,2)=0;
							session[fd]->func_parse=parse_admin;
							session[fd]->func_destruct = parse_admin_disconnect;
							session[fd]->auth = -1; // 認証終了を socket.c に伝える
						}
					}
				}
				WFIFOSET(fd,3);
				RFIFOSKIP(fd,RFIFOW(fd,2));
			}
			break;

		default:
#ifdef DUMP_UNKNOWN_PACKET
			hex_dump(stdout, RFIFOP(fd,0), RFIFOREST(fd));
			printf("\n");
#endif
			close(fd);
			session[fd]->eof=1;
			return 0;
		}
	}
	return 0;
}

static void login_config_read(const char *cfgName)
{
	struct hostent *h = NULL;
	char line[1024], w1[1024], w2[1024];
	FILE *fp;

	fp = fopen(cfgName, "r");
	if (fp == NULL) {
		printf("file not found: %s\n", cfgName);
		return;
	}

	while(fgets(line, sizeof(line) - 1, fp)) {
		if (line[0] == '/' && line[1] == '/')
			continue;

		if (sscanf(line, "%[^:]: %[^\r\n]", w1, w2) != 2)
			continue;

		if (strcmpi(w1, "admin_pass") == 0) {
			strncpy(admin_pass, w2, sizeof(admin_pass) -1);
			admin_pass[sizeof(admin_pass) - 1] = '\0';
		} else if (strcmpi(w1, "new_account") == 0) {
			new_account_flag = atoi(w2);
		} else if (strcmpi(w1, "gm_account_filename") == 0) {
			strncpy(GM_account_filename, w2, sizeof(GM_account_filename) - 1);
			GM_account_filename[sizeof(GM_account_filename) - 1] = '\0';
		} else if (strcmpi(w1, "login_port") == 0) {
			int n = atoi(w2);
			if (n < 1024 || n > 65535) {
				printf("Warning: Invalid login_port value: %d. Set to 6900 (default).\n", n);
				login_port = 6900; // default
			} else {
				login_port = (unsigned short)n;
			}
		} else if (strcmpi(w1, "listen_ip") == 0) {
			unsigned long ip_result;
			h = gethostbyname(w2);
			if (h != NULL)
				sprintf(w2, "%d.%d.%d.%d", (unsigned char)h->h_addr[0], (unsigned char)h->h_addr[1], (unsigned char)h->h_addr[2], (unsigned char)h->h_addr[3]);
			if ((ip_result = inet_addr(w2)) == INADDR_NONE) // not always -1
				printf("login_config_read: Invalid listen_ip value: %s.\n", w2);
			else
				listen_ip = ip_result;
		} else if (strcmpi(w1, "login_sip") == 0) {
			memcpy(login_sip_str, w2, 16);
			login_sip = inet_addr(login_sip_str);
		} else if (strcmpi(w1, "login_sport") == 0) {
			int n = atoi(w2);
			if (n < 1024 || n > 65535) {
				printf("Warning: Invalid login_sport value: %d. Set to 0 (default=disable).\n", n);
				login_sport = 0; // default
			} else {
				login_sport = (unsigned short)n;
			}
		} else if (strcmpi(w1, "login_version") == 0) {
			login_version = atoi(w2);
		} else if (strcmpi(w1, "login_type") == 0) {
			login_type = atoi(w2);
		} else if (strcmpi(w1, "autosave_time") == 0) {
			login_autosave_time = atoi(w2);
		} else if (strcmpi(w1, "login_log_filename") == 0) {
			strncpy(login_log_filename, w2, sizeof(login_log_filename) - 1);
			login_log_filename[sizeof(login_log_filename) - 1] = '\0';
		} else if (strcmpi(w1, "ladmin_pass") == 0) {
			strncpy(ladmin_pass, w2, sizeof(ladmin_pass) -1);
			ladmin_pass[sizeof(ladmin_pass) - 1] = '\0';
		} else if (strcmpi(w1, "detect_multiple_login") == 0) {
			detect_multiple_login = atoi(w2);
		} else if (strcmpi(w1, "httpd_enable")==0){
			socket_enable_httpd(atoi(w2));
		} else if (strcmpi(w1, "httpd_document_root") == 0) {
			httpd_set_document_root(w2);
		} else if (strcmpi(w1, "httpd_new_account") == 0) {
			httpd_new_account_flag = atoi(w2);
		} else if (strcmpi(w1, "httpd_log_filename") == 0) {
			httpd_set_logfile(w2);
		} else if (strcmpi(w1, "httpd_config") == 0) {
			httpd_config_read(w2);
		} else if (strcmpi(w1, "import") == 0) {
			login_config_read(w2);
		} else {
			login_config_read_sub(w1, w2);
		}
	}
	fclose(fp);

	return;
}

// === DISPLAY CONFIGURATION WARNINGS ===
// ======================================
static void display_conf_warnings(void)
{
	if (login_autosave_time < 10) {
		printf("Warning: Invalid login_autosave_time value: %d. Set to 600 (default).\n", login_autosave_time);
		login_autosave_time = 600;
	}

	if (login_version < 0 && login_version != -1) { // conserv -1 for old configuration
		printf("Warning: Invalid login_version value %d. Set to 0 (default=disable).\n", login_version);
		login_version = 0;
	}

	if (login_type < 0 && login_type != -1) { // conserv -1 for old configuration
		printf("Warning: Invalid login_type value %d. Set to 0 (default=disable).\n", login_type);
		login_type = 0;
	}

	if (new_account_flag != 0) {
		if (admin_pass[0] == '\0') {
			printf("Information: admin_pass is not defined (void)\n");
			printf("-> creation of accounts is possible with _F and _M without password.\n");
		} else if (strcmp(admin_pass, "admin") == 0) {
			printf("SECURITY warning: using default admin_pass ('%s').\n", admin_pass);
		}
	}

	if (ladmin_pass[0] == '\0') {
		printf("SECURITY warning: ladmin_pass is not defined (void).\n");
	} else if (strcmp(ladmin_pass, "admin") == 0) {
		printf("SECURITY warning: using default ladmin_pass ('%s').\n", ladmin_pass);
	}

#ifdef TXT_ONLY
	// nothing to check in TXT?
#else /* TXT_ONLY */
	if (login_server_pw[0] == '\0') {
		printf("SQL SECURITY warning: login_server_pw is not defined (void).\n");
	} else if (strcmp(login_server_pw, "ragnarok") == 0) {
		printf("SQL SECURITY warning: using default login_server_pw ('%s').\n", login_server_pw);
	}
#endif /* else TXT_ONLY */

	return;
}

int login_sync_timer(int tid, unsigned int tick, int id,int data)
{
	login_sync();

	return 0;
}

// for httpd support

static double login_users(void)
{
	int i;
	int users = 0;

	for(i=0;i<MAX_CHAR_SERVERS;i++) {
		if(server_fd[i] > 0) {
			users += server[i].users;
		}
	}

	return (double)users;
}

static void login_httpd_account(struct httpd_session_data *sd,const char* url)
{
	char* userid     = httpd_get_value(sd,"userid");
	int   userid_len = strlen(userid);
	char* passwd     = httpd_get_value(sd,"passwd");
	int   passwd_len = strlen(passwd);
	char* gender     = httpd_get_value(sd,"gender");
	char* check      = httpd_get_value(sd,"check");
	const char* msg  = "";
	int   i;

	do {
		if(httpd_get_method(sd) != HTTPD_METHOD_POST) {
			// POST以外お断り
			msg = "Illegal request."; break;
		}
		if(!httpd_new_account_flag) {
			msg = "Now stopping to create accounts on httpd."; break;
		}
		if(userid_len < 4 || userid_len > 23) {
			msg = "Please input UserID 4-23 bytes."; break;
		}
		for(i = 0; i < userid_len; i++) {
			if(!isalnum((unsigned char)userid[i])) break;
		}
		if(i != userid_len) {
			msg = "Illegal character found in UserID."; break;
		}

		if(check[0]) {	// ID のチェックは userid だけでいい
			if(account_load_str(userid) == NULL) {
				msg = "OK : You can use UserID.";
			} else {
				msg = "NG : UserID is already used.";
			}
			break;
		}

		if(passwd_len < 4 || passwd_len > 23) {
			msg = "Please input Password 4-23 bytes."; break;
		}
		for(i = 0; i < passwd_len; i++) {
			if(!isalnum((unsigned char)passwd[i])) break;
		}
		if(i != passwd_len) {
			msg = "Illegal character found in Password."; break;
		}
		if(gender[0] != 'm' && gender[0] != 'f') {
			msg = "Gender error."; break;
		}

		if(!check[0]) {
			struct mmo_account ma;
			char   buf[32];
			memset(&ma,0,sizeof(ma));
			strncpy(ma.userid,userid,24);
			strncpy(ma.pass  ,passwd,24);
			ma.sex = (gender[0] == 'm')? 1: 0;
			strncpy(ma.mail  ,"@"   ,40); // 暫定
			sprintf(buf,"( httpd %08lx )",httpd_get_ip(sd));
			if( !account_new(&ma,buf) ) {
				msg = "Account creation failed.";
			} else {
				msg = "Account successfully created.";
			}
		}
	} while(0);

	// HTTP/1.1で返すとアカウントを連続して作成する馬鹿がいそうなので、
	// あえてHTTP/1.0扱いしている。
	httpd_send_head(sd,200,"text/plain",-1);
	httpd_send_data(sd,strlen(msg),msg);

	aFree(userid);
	aFree(passwd);
	aFree(gender);
	aFree(check);

	return;
}

void login_socket_ctrl_panel_func(int fd,char* usage,char* user,char* status)
{
	struct socket_data *sd = session[fd];
	struct login_session_data *ld = (struct login_session_data *)sd->session_data;

	strcpy( usage,
		( sd->func_parse == parse_login )? "login user" :
		( sd->func_parse == parse_admin )? "administration" :
		( sd->func_parse == parse_fromchar)? "char server" : "unknown" );

	if( sd->func_parse == parse_fromchar && sd->auth )
	{
		int id;
		for(id=0;id<MAX_CHAR_SERVERS;id++)
			if(server_fd[id]==fd)
				break;
		if( id<MAX_CHAR_SERVERS )
			sprintf( user, "%s (%s)", ld->userid, server[id].name );
	}
	else if( sd->func_parse == parse_login && sd->auth )
	{
		sprintf( user, "%s (%d)", ld->userid, (int)ld->account_id );
	}
}

int login_httpd_auth_func( struct httpd_access* a, struct httpd_session_data* sd, const char *userid, char *passwd )
{
	const struct mmo_account *acc;
	const char *p;

	p = memchr(userid, '\0', 24);
	if( p == NULL )	// 24文字以上はありえない
		return 0;

	acc = account_load_str( userid );
	if( !acc )
		return 0;

	strcpy( passwd, acc->pass );
	return 1;
}

void do_pre_final(void)
{
	// nothing to do
	return;
}

void do_final(void)
{
	int i;

	login_sync();
	login_final();
	exit_dbn();

	for(i=0;i<MAX_CHAR_SERVERS;i++){
		int fd;
		if((fd=server_fd[i])>0){
			delete_session(fd);
		}
	}
	delete_session(login_fd);
	if(login_sport != 0 && login_port != login_sport)
		delete_session(login_sfd);
	do_final_timer();
}

int do_init(int argc,char **argv)
{
	int i;

	printf("Auriga Login Server [%s] v%d.%d.%d mod%d\n",
#ifdef TXT_ONLY
		"TXT",
#else
		"SQL",
#endif
		AURIGA_MAJOR_VERSION,AURIGA_MINOR_VERSION,AURIGA_REVISION,
		AURIGA_MOD_VERSION
	);

	for(i = 1; i < argc - 1; i += 2) {
		if(strcmp(argv[i], "--login_config") == 0 || strcmp(argv[i], "--login-config") == 0) {
			strncpy(login_conf_filename, argv[i+1], sizeof(login_conf_filename));
			login_conf_filename[sizeof(login_conf_filename)-1] = '\0';
		}
		else {
			printf("illegal command line argument %s !!\n", argv[i]);
			exit(1);
		}
	}

	login_config_read(login_conf_filename);
	display_conf_warnings();

	for(i=0;i<AUTH_FIFO_SIZE;i++){
		auth_fifo[i].delflag=1;
	}
	for(i=0;i<MAX_CHAR_SERVERS;i++){
		server_fd[i]=-1;
	}
	login_fd = make_listen_port(login_port, listen_ip);
	if (login_sport != 0 && login_port != login_sport)
		login_sfd = make_listen_port(login_sport, login_sip);
	login_init();
	read_gm_account();
	set_defaultparse(parse_login);
	set_sock_destruct(parse_login_disconnect);
	socket_set_httpd_page_connection_func( login_socket_ctrl_panel_func );

	add_timer_func_list(login_sync_timer,"login_sync_timer");
	add_timer_interval(gettick()+10*1000,login_sync_timer,0,0,login_autosave_time*1000);

	// for httpd support
	do_init_httpd();
	do_init_graph();
	graph_add_sensor("Login Users",60*1000,login_users);
	graph_add_sensor("Uptime(days)",60*1000,uptime);
	graph_add_sensor("Memory Usage(KB)",60*1000,memmgr_usage);
	httpd_pages("/account",login_httpd_account);
	httpd_default_page(httpd_send_file);
	httpd_set_auth_func( 1, login_httpd_auth_func );

	return 0;
}
