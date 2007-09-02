
#define _INT_MERC_C_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mmo.h"
#include "socket.h"
#include "db.h"
#include "lock.h"
#include "malloc.h"
#include "journal.h"
#include "utils.h"

#include "char.h"
#include "inter.h"
#include "int_merc.h"

static struct dbt *merc_db = NULL;

#ifdef TXT_ONLY

static char merc_txt[1024]="save/mercenary.txt";
static int merc_newid = 100;

#ifdef TXT_JOURNAL
static int merc_journal_enable = 1;
static struct journal merc_journal;
static char merc_journal_file[1024]="./save/mercenary.journal";
static int merc_journal_cache = 1000;
#endif

void merc_txt_config_read_sub(const char* w1,const char *w2)
{
	if(strcmpi(w1,"merc_txt")==0){
		strncpy(merc_txt, w2, sizeof(merc_txt) - 1);
	}
#ifdef TXT_JOURNAL
	else if(strcmpi(w1,"merc_journal_enable")==0){
		merc_journal_enable = atoi( w2 );
	}
	else if(strcmpi(w1,"merc_journal_file")==0){
		strncpy( merc_journal_file, w2, sizeof(merc_journal_file) - 1 );
	}
	else if(strcmpi(w1,"merc_journal_cache_interval")==0){
		merc_journal_cache = atoi( w2 );
	}
#endif
}

static int merc_tostr(char *str,struct mmo_mercstatus *m)
{
	int i;
	char *str_p = str;
	unsigned short sk_lv;

	if(!m) return 0;

	str_p += sprintf(str,"%d,%d,%s\t%d,%d\t%d,%d,%d,%d,%d\t%d,%d,%d,%d,%d,%d\t%d,%u",
		m->merc_id,m->class_,m->name,
		m->account_id,m->char_id,
		m->base_level,m->max_hp,m->hp,m->max_sp,m->sp,
		m->str,m->agi,m->vit,m->int_,m->dex,m->luk,
		m->kill_count,m->limit);

	*(str_p++)='\t';

	for(i=0;i<MAX_MERCSKILL;i++) {
		if(m->skill[i].id && m->skill[i].flag!=1){
			sk_lv = (m->skill[i].flag==0)? m->skill[i].lv: m->skill[i].flag-2;
			str_p += sprintf(str_p,"%d,%d ",m->skill[i].id,sk_lv);
		}
	}
	*(str_p++)='\t';

	*str_p='\0';
	return 0;
}

static int merc_fromstr(char *str,struct mmo_mercstatus *m)
{
	int i,s,next,set,len;
	int tmp_int[17];
	char tmp_str[256];

	if(!m) return 0;

	memset(m,0,sizeof(struct mmo_mercstatus));

	//printf("sscanf merc main info\n");
	s=sscanf(str,"%d,%d,%255[^\t]\t%d,%d\t%d,%d,%d,%d,%d\t%d,%d,%d,%d,%d,%d\t%d,%u%n",
		&tmp_int[0],&tmp_int[1],tmp_str,
		&tmp_int[2],&tmp_int[3],
		&tmp_int[4],&tmp_int[5],&tmp_int[6],&tmp_int[7],&tmp_int[8],
		&tmp_int[9],&tmp_int[10],&tmp_int[11],&tmp_int[12],&tmp_int[13],&tmp_int[14],
		&tmp_int[15],&tmp_int[16],&next);

	if(s!=18)
		return 1;

	m->merc_id      = tmp_int[0];
	m->class_       = tmp_int[1];
	strncpy(m->name,tmp_str,24);
	m->name[23] = '\0';	// force \0 terminal
	m->account_id   = tmp_int[2];
	m->char_id      = tmp_int[3];
	m->base_level   = tmp_int[4];
	m->max_hp       = tmp_int[5];
	m->hp           = tmp_int[6];
	m->max_sp       = tmp_int[7];
	m->sp           = tmp_int[8];
	m->str          = tmp_int[9];
	m->agi          = tmp_int[10];
	m->vit          = tmp_int[11];
	m->int_         = tmp_int[12];
	m->dex          = tmp_int[13];
	m->luk          = tmp_int[14];
	m->kill_count   = tmp_int[15];
	m->limit        = (unsigned int)tmp_int[16];
	m->option       = 0;

	if(str[next]=='\n' || str[next]=='\r')
		return 1;	// スキル情報なし

	next++;
	for(i=0;str[next] && str[next]!='\t';i++){
		int n;
		set=sscanf(str+next,"%d,%d%n",
			&tmp_int[0],&tmp_int[1],&len);
		if(set!=2)
			return 0;
		n = tmp_int[0]-MERC_SKILLID;
		if(n >= 0 && n < MAX_MERCSKILL) {
			m->skill[n].id = tmp_int[0];
			m->skill[n].lv = tmp_int[1];
		} else {
			printf("merc_fromstr: invaild skill id: %d\n", tmp_int[0]);
		}
		next+=len;
		if(str[next]==' ')
			next++;
	}
	return 0;
}

#ifdef TXT_JOURNAL
// ==========================================
// 傭兵データのジャーナルのロールフォワード用コールバック関数
// ------------------------------------------
int merc_journal_rollforward( int key, void* buf, int flag )
{
	struct mmo_mercstatus* m = (struct mmo_mercstatus *)numdb_search( merc_db, key );

	// 念のためチェック
	if( flag == JOURNAL_FLAG_WRITE && key != ((struct mmo_mercstatus*)buf)->merc_id )
	{
		printf("int_merc: journal: key != merc_id !\n");
		return 0;
	}

	// データの置き換え
	if( m )
	{
		if( flag == JOURNAL_FLAG_DELETE ) {
			numdb_erase(merc_db, key);
			aFree(m);
		} else {
			memcpy( m, buf, sizeof(struct mmo_mercstatus) );
		}
		return 1;
	}

	// 追加
	if( flag != JOURNAL_FLAG_DELETE )
	{
		m = (struct mmo_mercstatus*) aCalloc( 1, sizeof( struct mmo_mercstatus ) );
		memcpy( m, buf, sizeof(struct mmo_mercstatus) );
		numdb_insert( merc_db, key, m );
		if( m->merc_id >= merc_newid)
			merc_newid=m->merc_id+1;
		return 1;
	}

	return 0;
}
int merc_txt_sync(void);
#endif

int merc_txt_init(void)
{
	char line[8192];
	struct mmo_mercstatus *m;
	FILE *fp;
	int c=0;

	merc_db=numdb_init();

	if( (fp=fopen(merc_txt,"r"))==NULL )
		return 1;
	while(fgets(line,sizeof(line),fp)){
		m=(struct mmo_mercstatus *)aCalloc(1,sizeof(struct mmo_mercstatus));
		if(merc_fromstr(line,m)==0 && m->merc_id>0){
			if( m->merc_id >= merc_newid)
				merc_newid=m->merc_id+1;
			numdb_insert(merc_db,m->merc_id,m);
		}else{
			printf("int_merc: broken data [%s] line %d\n",merc_txt,c);
			aFree(m);
		}
		c++;
	}
	fclose(fp);
	//printf("int_merc: %s read done (%d mercs)\n",merc_txt,c);

#ifdef TXT_JOURNAL
	if( merc_journal_enable )
	{
		// ジャーナルデータのロールフォワード
		if( journal_load( &merc_journal, sizeof(struct mmo_mercstatus), merc_journal_file ) )
		{
			int c = journal_rollforward( &merc_journal, merc_journal_rollforward );

			printf("int_merc: journal: roll-forward (%d)\n", c );

			// ロールフォワードしたので、txt データを保存する ( journal も新規作成される)
			merc_txt_sync();
		}
		else
		{
			// ジャーナルを新規作成する
			journal_final( &merc_journal );
			journal_create( &merc_journal, sizeof(struct mmo_mercstatus), merc_journal_cache, merc_journal_file );
		}
	}
#endif

	return 0;
}

static int merc_txt_sync_sub(void *key,void *data,va_list ap)
{
	char line[8192];
	FILE *fp;

	merc_tostr(line,(struct mmo_mercstatus *)data);
	fp=va_arg(ap,FILE *);
	fprintf(fp,"%s" RETCODE,line);
	return 0;
}

int merc_txt_sync(void)
{
	FILE *fp;
	int lock;

	if( !merc_db )
		return 1;

	if( (fp=lock_fopen(merc_txt,&lock))==NULL ){
		printf("int_merc: cant write [%s] !!! data is lost !!!\n",merc_txt);
		return 1;
	}
	numdb_foreach(merc_db,merc_txt_sync_sub,fp);
	lock_fclose(fp,merc_txt,&lock);
	//printf("int_merc: %s saved.\n",merc_txt);

#ifdef TXT_JOURNAL
	if( merc_journal_enable )
	{
		// コミットしたのでジャーナルを新規作成する
		journal_final( &merc_journal );
		journal_create( &merc_journal, sizeof(struct mmo_mercstatus), merc_journal_cache, merc_journal_file );
	}
#endif

	return 0;
}

int merc_txt_delete(int merc_id)
{
	struct mmo_mercstatus *p = (struct mmo_mercstatus *)numdb_search(merc_db,merc_id);

	if(p == NULL)
		return 1;

	numdb_erase(merc_db,merc_id);
	aFree(p);
	printf("merc_id: %d deleted\n",merc_id);

#ifdef TXT_JOURNAL
	if( merc_journal_enable )
		journal_write( &merc_journal, merc_id, NULL );
#endif

	return 0;
}

const struct mmo_mercstatus* merc_txt_load(int merc_id)
{
	return (const struct mmo_mercstatus *)numdb_search(merc_db,merc_id);
}

int merc_txt_save(struct mmo_mercstatus* p2)
{
	struct mmo_mercstatus* p1 = (struct mmo_mercstatus *)numdb_search(merc_db,p2->merc_id);

	if(p1 == NULL) {
		p1 = (struct mmo_mercstatus *)aMalloc(sizeof(struct mmo_mercstatus));
		numdb_insert(merc_db,p2->merc_id,p1);
	}
	memcpy(p1,p2,sizeof(struct mmo_mercstatus));

#ifdef TXT_JOURNAL
	if( merc_journal_enable )
		journal_write( &merc_journal, p1->merc_id, p1 );
#endif
	return 1;
}

int merc_txt_new(struct mmo_mercstatus *p2)
{
	struct mmo_mercstatus *p1 = (struct mmo_mercstatus *)aMalloc(sizeof(struct mmo_mercstatus));

	p2->merc_id = merc_newid++;
	memcpy(p1,p2,sizeof(struct mmo_mercstatus));
	numdb_insert(merc_db,p2->merc_id,p1);
	return 0;
}

static int merc_txt_final_sub(void *key,void *data,va_list ap)
{
	struct mmo_mercstatus *p = (struct mmo_mercstatus *)data;

	aFree(p);

	return 0;
}

void merc_txt_final(void)
{
	if(merc_db)
		numdb_final(merc_db,merc_txt_final_sub);

#ifdef TXT_JOURNAL
	if( merc_journal_enable )
	{
		journal_final( &merc_journal );
	}
#endif
}

#define merc_init   merc_txt_init
#define merc_sync   merc_txt_sync
#define merc_delete merc_txt_delete
#define merc_load   merc_txt_load
#define merc_save   merc_txt_save
#define merc_new    merc_txt_new
#define merc_final  merc_txt_final

#else /* TXT_ONLY */
static char merc_db_[256]      = "mercenary";
static char merc_skill_db[256] = "mercenary_skill";

int merc_sql_init(void)
{
	merc_db = numdb_init();
	return 0;
}

int merc_sql_sync(void)
{
	// nothing to do
	return 0;
}

int merc_sql_delete(int merc_id)
{
	struct mmo_mercstatus *p = (struct mmo_mercstatus *)numdb_search(merc_db,merc_id);

	if(p) {
		numdb_erase(merc_db,p->merc_id);
		aFree(p);
	}
	// printf("Request del  merc  (%6d)[",merc_id);
	sprintf(tmp_sql,"DELETE FROM `%s` WHERE `merc_id`='%d'",merc_db_, merc_id);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (delete `%s`)- %s\n", merc_db_, mysql_error(&mysql_handle) );
	}
	sprintf(tmp_sql,"DELETE FROM `%s` WHERE `merc_id`='%d'",merc_skill_db, merc_id);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (delete `%s`)- %s\n", merc_skill_db, mysql_error(&mysql_handle) );
	}
	// printf("]\n");
	return 0;
}

const struct mmo_mercstatus* merc_sql_load(int merc_id)
{
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;
	struct mmo_mercstatus *p = (struct mmo_mercstatus *)numdb_search(merc_db,merc_id);

	if(p && p->merc_id == merc_id) {
		return p;
	}
	if(p == NULL) {
		p = (struct mmo_mercstatus *)aMalloc(sizeof(struct mmo_mercstatus));
		numdb_insert(merc_db,merc_id,p);
	}

	// printf("Request load merc  (%6d)[",merc_id);
	memset(p, 0, sizeof(struct mmo_mercstatus));

	// `mercenary` (`merc_id`, `class`,`name`,`account_id`,`char_id`,`base_level`,
	//	`max_hp`,`hp`,`max_sp`,`sp`,`str`,`agi`,`vit`,`int`,`dex`,`luk`,
	//	`kill_count`,`limit`)
	sprintf(
		tmp_sql,
		"SELECT `class`,`name`,`account_id`,`char_id`,`base_level`,"
		"`max_hp`,`hp`,`max_sp`,`sp`,`str`,`agi`,`vit`,`int`,`dex`,`luk`,"
		"`kill_count`,`limit` "
		"FROM `%s` WHERE `merc_id`='%d'",
		merc_db_, merc_id
	);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (select `%s`)- %s\n", merc_db_, mysql_error(&mysql_handle) );
		p->merc_id = -1;
		return NULL;
	}
	sql_res = mysql_store_result(&mysql_handle);
	if (sql_res!=NULL && mysql_num_rows(sql_res)>0) {
		sql_row = mysql_fetch_row(sql_res);

		p->merc_id      = merc_id;
		p->class_       = atoi(sql_row[0]);
		strncpy(p->name,sql_row[1],24);
		p->name[23] = '\0';	// force \0 terminal
		p->account_id   = atoi(sql_row[2]);
		p->char_id      = atoi(sql_row[3]);
		p->base_level   = atoi(sql_row[4]);
		p->max_hp       = atoi(sql_row[5]);
		p->hp           = atoi(sql_row[6]);
		p->max_sp       = atoi(sql_row[7]);
		p->sp           = atoi(sql_row[8]);
		p->str          = atoi(sql_row[9]);
		p->agi          = atoi(sql_row[10]);
		p->vit          = atoi(sql_row[11]);
		p->int_         = atoi(sql_row[12]);
		p->dex          = atoi(sql_row[13]);
		p->luk          = atoi(sql_row[14]);
		p->kill_count   = atoi(sql_row[15]);
		p->limit        = (unsigned int)atoi(sql_row[16]);
	} else {
		p->merc_id = -1;
		if( sql_res ) mysql_free_result(sql_res);
		return NULL;
	}
	mysql_free_result(sql_res);

	sprintf(
		tmp_sql,"SELECT `id`,`lv` FROM `%s` WHERE `merc_id`='%d'",
		merc_skill_db, merc_id
	);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (select `%s`)- %s\n", merc_skill_db, mysql_error(&mysql_handle) );
		p->merc_id = -1;
		return NULL;
	}
	sql_res = mysql_store_result(&mysql_handle);
	if (sql_res!=NULL && mysql_num_rows(sql_res)>0) {
		int i;
		for(i=0;((sql_row = mysql_fetch_row(sql_res))&&i<MAX_MERCSKILL);i++){
			int id = atoi(sql_row[0]);
			if( id < MERC_SKILLID || id >= MERC_SKILLID + MAX_MERCSKILL ) {
				// DB操作して変なスキルを覚えさせられる可能性があるのでチェック
				printf("merc_sql_load: invaild skill id: %d\n", id);
			} else {
				p->skill[id-MERC_SKILLID].id = id;
				p->skill[id-MERC_SKILLID].lv = atoi(sql_row[1]);
			}
		}
	}
	mysql_free_result(sql_res);

	p->option = 0;

	 //printf("]\n");
	return p;
}

#define UPDATE_NUM(val,sql) \
	if(p1->val != p2->val) {\
		p += sprintf(p,"%c`"sql"` = '%d'",sep,p2->val); sep = ',';\
	}
#define UPDATE_UNUM(val,sql) \
	if(p1->val != p2->val) {\
		p += sprintf(p,"%c`"sql"` = '%u'",sep,p2->val); sep = ',';\
	}
#define UPDATE_STR(val,sql) \
	if(strcmp(p1->val,p2->val)) {\
		p += sprintf(p,"%c`"sql"` = '%s'",sep,strecpy(buf,p2->val)); sep = ',';\
	}

int merc_sql_save(struct mmo_mercstatus* p2)
{
	// `mercenary` (`merc_id`, `class`,`name`,`account_id`,`char_id`,`base_level`,
	//	`max_hp`,`hp`,`max_sp`,`sp`,`str`,`agi`,`vit`,`int`,`dex`,`luk`,
	//	`kill_count`,`limit`)
	int  i;
	char sep, *p, buf[64];
	const struct mmo_mercstatus *p1 = merc_sql_load(p2->merc_id);

	if(p1 == NULL) return 0;

	// printf("Request save merc  (%6d)[",p2->merc_id);
	sep = ' ';
	// basic information
	p =  tmp_sql;
	p += sprintf(p,"UPDATE `%s` SET",merc_db_);
	UPDATE_NUM(class_      ,"class");
	UPDATE_STR(name        ,"name");
	UPDATE_NUM(account_id  ,"account_id");
	UPDATE_NUM(char_id     ,"char_id");
	UPDATE_NUM(base_level  ,"base_level");
	UPDATE_NUM(max_hp      ,"max_hp");
	UPDATE_NUM(hp          ,"hp");
	UPDATE_NUM(max_sp      ,"max_sp");
	UPDATE_NUM(sp          ,"sp");
	UPDATE_NUM(str         ,"str");
	UPDATE_NUM(agi         ,"agi");
	UPDATE_NUM(vit         ,"vit");
	UPDATE_NUM(int_        ,"int");
	UPDATE_NUM(dex         ,"dex");
	UPDATE_NUM(luk         ,"luk");
	UPDATE_NUM(kill_count  ,"kill_count");
	UPDATE_UNUM(limit      ,"limit");

	if(sep == ',') {
		sprintf(p," WHERE `merc_id` = '%d'",p2->merc_id);
		if (mysql_query(&mysql_handle, tmp_sql)) {
			printf("DB server Error (update `%s`)- %s\n", merc_db_, mysql_error(&mysql_handle));
		}
		// printf("basic ");
	}

	if(memcmp(p1->skill, p2->skill, sizeof(p1->skill)) ) {
		sprintf(tmp_sql,"DELETE FROM `%s` WHERE `merc_id`='%d'",merc_skill_db,p2->merc_id);
		if(mysql_query(&mysql_handle, tmp_sql) ) {
			printf("DB server Error (delete `%s`)- %s\n", merc_skill_db, mysql_error(&mysql_handle) );
		}
		p  = tmp_sql;
		p += sprintf(tmp_sql, "INSERT INTO `%s` (`merc_id`,`id`,`lv`) VALUES", merc_skill_db);
		sep = ' ';
		for(i=0;i<MAX_MERCSKILL;i++) {
			if(p2->skill[i].id && p2->skill[i].flag!=1){
				int lv = (p2->skill[i].flag==0)? p2->skill[i].lv: p2->skill[i].flag-2;
				p += sprintf(p,"%c('%d','%d','%d')", sep,p2->merc_id,p2->skill[i].id,lv);
				sep = ',';
			}
		}
		if(sep == ',') {
			if(mysql_query(&mysql_handle, tmp_sql) ) {
				printf("DB server Error (insert `%s`)- %s\n", merc_skill_db, mysql_error(&mysql_handle) );
			}
		}
		// printf("skill ");
	}
	// printf("]\n");
	{
		struct mmo_mercstatus *p3 = (struct mmo_mercstatus *)numdb_search(merc_db,p2->merc_id);
		if(p3)
			memcpy(p3,p2,sizeof(struct mmo_mercstatus));
	}
	return 1;
}

int merc_sql_new(struct mmo_mercstatus *p)
{
	// 傭兵IDを読み出す
	int i;
	char t_name[64], sep, *buf;
	struct mmo_mercstatus *p2;

	// printf("Request make merc  (------)[");
	sprintf(
		tmp_sql,
		"INSERT INTO `%s` (`class`,`name`,`account_id`,`char_id`,`base_level`,"
		"`max_hp`,`hp`,`max_sp`,`sp`,`str`,`agi`,`vit`,`int`,`dex`,`luk`,"
		"`kill_count`,`limit`) "
		"VALUES ('%d', '%s', '%d', '%d',"
		"'%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d',"
		"'%d', '%u')",
		merc_db_, p->class_, strecpy(t_name, p->name), p->account_id, p->char_id,
		p->base_level, p->max_hp, p->hp, p->max_sp, p->sp, p->str, p->agi, p->vit, p->int_, p->dex, p->luk,
		p->kill_count, p->limit
	);
	if(mysql_query(&mysql_handle, tmp_sql)){
		printf("failed (insert `%s`), SQL error: %s\n", merc_db_, mysql_error(&mysql_handle));
		aFree(p);
		return 1;
	}

	p->merc_id = (int)mysql_insert_id(&mysql_handle);

	// skill
	buf  = tmp_sql;
	buf += sprintf(tmp_sql, "INSERT INTO `%s` (`merc_id`,`id`,`lv`) VALUES", merc_skill_db);
	sep = ' ';
	for(i=0;i<MAX_MERCSKILL;i++) {
		if(p->skill[i].id && p->skill[i].flag!=1){
			int lv = (p->skill[i].flag==0)? p->skill[i].lv: p->skill[i].flag-2;
			buf += sprintf(buf,"%c('%d','%d','%d')", sep,p->merc_id,p->skill[i].id,lv);
			sep = ',';
		}
	}
	if(sep == ',') {
		if(mysql_query(&mysql_handle, tmp_sql) ) {
			printf("DB server Error (insert `%s`)- %s\n", merc_skill_db, mysql_error(&mysql_handle) );
		}
	}

	p2 = (struct mmo_mercstatus*)aMalloc( sizeof( struct mmo_mercstatus ) );
	memcpy( p2, p, sizeof( struct mmo_mercstatus ) );
	numdb_insert(merc_db,p->merc_id,p2);

	return 0;
}

static int merc_sql_final_sub(void *key,void *data,va_list ap)
{
	struct mmo_mercstatus *p = (struct mmo_mercstatus *)data;

	aFree(p);

	return 0;
}

void merc_sql_final(void)
{
	if(merc_db)
		numdb_final(merc_db,merc_sql_final_sub);
}

void merc_sql_config_read_sub(const char* w1,const char *w2)
{
	// nothing to do
	return;
}

#define merc_init   merc_sql_init
#define merc_sync   merc_sql_sync
#define merc_delete merc_sql_delete
#define merc_load   merc_sql_load
#define merc_save   merc_sql_save
#define merc_new    merc_sql_new
#define merc_final  merc_sql_final

#endif

int mapif_merc_info(int fd,int account_id,int char_id,const struct mmo_mercstatus *m,unsigned char flag)
{
	if(!m)
		return 0;

	WFIFOW(fd,0)=0x3870;
	WFIFOW(fd,2)=sizeof(struct mmo_mercstatus) + 13;
	WFIFOL(fd,4)=account_id;
	WFIFOL(fd,8)=char_id;
	WFIFOB(fd,12)=flag;
	memcpy(WFIFOP(fd,13),m,sizeof(struct mmo_mercstatus));
	WFIFOSET(fd,WFIFOW(fd,2));

	return 0;
}

int mapif_save_merc_ack(int fd,int account_id,int flag)
{
	WFIFOW(fd,0)=0x3871;
	WFIFOL(fd,2)=account_id;
	WFIFOB(fd,6)=flag;
	WFIFOSET(fd,7);

	return 0;
}

int mapif_delete_merc_ack(int fd,int flag)
{
	WFIFOW(fd,0)=0x3872;
	WFIFOB(fd,2)=flag;
	WFIFOSET(fd,3);

	return 0;
}

int mapif_create_merc(int fd,int account_id,int char_id,struct mmo_mercstatus *m)
{
	if(!m || account_id <= 0 || char_id <= 0)
		return 0;
	if(merc_new(m) == 0) {
		mapif_merc_info(fd,account_id,char_id,m,1);
	}
	return 0;
}

int mapif_load_merc(int fd,int account_id,int char_id,int merc_id)
{
	const struct mmo_mercstatus *m = merc_load(merc_id);

	if(m!=NULL) {
		mapif_merc_info(fd,account_id,char_id,m,0);
	} else {
		printf("inter merc: data load error %d %d %d\n",account_id,char_id,merc_id);
	}
	return 0;
}

int mapif_save_merc(int fd,int account_id,struct mmo_mercstatus *data)
{
	if(!data || sizeof(struct mmo_mercstatus) != RFIFOW(fd,2) - 8) {
		printf("inter merc: data size error %d %d\n",sizeof(struct mmo_mercstatus),RFIFOW(fd,2)-8);
		return 0;
	}

	if(merc_load(data->merc_id)) {
		merc_save(data);
		mapif_save_merc_ack(fd,account_id,0);
	}

	return 0;
}

int mapif_delete_merc(int fd,int merc_id)
{
	mapif_delete_merc_ack(fd,merc_delete(merc_id));

	return 0;
}

//---------------------------------------------------------------------------------------
// 傭兵を新規作成
int mapif_parse_CreateMerc(int fd)
{
	int account_id = RFIFOL(fd,4);
	int char_id    = RFIFOL(fd,8);
	struct mmo_mercstatus m;

	memcpy(&m,RFIFOP(fd,12),sizeof(struct mmo_mercstatus));

	mapif_create_merc(fd,account_id,char_id,&m);
	return 0;
}

// 傭兵のデータ送信
int mapif_parse_LoadMerc(int fd)
{
	mapif_load_merc(fd,RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10));
	return 0;
}

// 傭兵のデータ受信＆保存
int mapif_parse_SaveMerc(int fd)
{
	mapif_save_merc(fd,RFIFOL(fd,4),(struct mmo_mercstatus *)RFIFOP(fd,8));
	return 0;
}

// 傭兵削除
int mapif_parse_DeleteMerc(int fd)
{
	mapif_delete_merc(fd,RFIFOL(fd,10));
	return 0;
}

// map server からの通信
// ・１パケットのみ解析すること
// ・パケット長データはinter.cにセットしておくこと
// ・パケット長チェックや、RFIFOSKIPは呼び出し元で行われるので行ってはならない
// ・エラーなら0(false)、そうでないなら1(true)をかえさなければならない
int inter_merc_parse_frommap(int fd)
{
	switch(RFIFOW(fd,0)){
	case 0x3070: mapif_parse_CreateMerc(fd); break;
	case 0x3071: mapif_parse_LoadMerc(fd);   break;
	case 0x3072: mapif_parse_SaveMerc(fd);   break;
	case 0x3073: mapif_parse_DeleteMerc(fd); break;
	default:
		return 0;
	}
	return 1;
}
