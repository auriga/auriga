/*
	int_mail.c
	struct mail		store : 現在保存されているメールの件数
					rates : 今まで送られてきたメールの総数
 */

#include <stdio.h>
#include <time.h>

#include "mmo.h"
#include "socket.h"
#include "db.h"
#include "lock.h"
#include "malloc.h"
#include "utils.h"

#include "char.h"
#include "inter.h"
#include "int_mail.h"

static struct dbt *mail_db;

void mail_free(struct mail_data *md[MAIL_STORE_MAX],int store);

#ifdef TXT_ONLY

static char mail_dir[1024]="save/mail_data/";
static char mail_txt[1024]="save/mail.txt";

int mail_txt_store_mail(int char_id,struct mail_data *md)
{
	char filename[1024];
	FILE *fp;
	unsigned int i;

	if(!md) return 0;

	sprintf(filename,"%s%d.txt",mail_dir,char_id);
	fp=fopen(filename,"a");

	fprintf(fp,"%u,%d\t%s\t%s\t%s\t%d\t%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\t%u\t%u\t",
		md->mail_num, md->read, md->char_name, md->receive_name, md->title, md->zeny,
		md->item.id, md->item.nameid, md->item.amount, md->item.equip,
		md->item.identify, md->item.refine, md->item.attribute,
		md->item.card[0], md->item.card[1], md->item.card[2], md->item.card[3],
		md->times,md->body_size);
	for(i=0;i<md->body_size;i++){
		fprintf(fp,"%02X",RBUFB(md->body,i));
	}
	fprintf(fp,"\n");
	fclose(fp);
	return 0;
}
int mail_txt_save_mail(int char_id,int i,int store,struct mail_data *md[MAIL_STORE_MAX])
{
	char filename[1024];
	FILE *fp;
	unsigned int j;
	int n=-1;

	if(!md) return 0;

	sprintf(filename,"%s%d.txt",mail_dir,char_id);
	fp=fopen(filename,"w");

	while(n+1<store && md[n+1]){
		n++;
		fprintf(fp,"%u,%d\t%s\t%s\t%s\t%d\t%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\t%u\t%u\t",
			md[n]->mail_num, md[n]->read, md[n]->char_name, md[n]->receive_name, md[n]->title, md[n]->zeny,
			md[n]->item.id, md[n]->item.nameid, md[n]->item.amount, md[n]->item.equip,
			md[n]->item.identify, md[n]->item.refine, md[n]->item.attribute,
			md[n]->item.card[0], md[n]->item.card[1], md[n]->item.card[2], md[n]->item.card[3],
			md[n]->times, md[n]->body_size);
		for(j=0;j<md[n]->body_size;j++){
			fprintf(fp,"%02X",RBUFB(md[n]->body,j));
		}
		fprintf(fp,"\n");
	}
	if(n!=store-1 && md[n]){	// 数に相違あり？
		const struct mail *m;
		struct mail m2;
		m = mail_load(char_id);
		if(m){
			memcpy(&m2,m,sizeof(struct mail));
			if( m2.rates < md[n]->mail_num )
				m2.rates = md[n]->mail_num;
			if( m2.store != n+1 )
				m2.store = n+1;
			mail_save(&m2);
		}
	}
	fclose(fp);
	return 0;
}
int mail_txt_read_mail(int char_id,int store,struct mail_data *md[MAIL_STORE_MAX])
{
	int i=-1,j;
	int tmp_int[17];
	char tmp_char[4][1024];
	char line[65536];
	char filename[1024];
	FILE *fp;

	sprintf(filename,"%s%d.txt",mail_dir,char_id);
	if((fp=fopen(filename,"r"))!=NULL){
		unsigned int n;
		char *p;
		while(i+1<store && fgets(line,65535,fp) && i+1<MAIL_STORE_MAX){
			n=sscanf(line,"%u,%d\t%[^\t]\t%[^\t]\t%[^\t]\t%d\t%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\t%d\t%d\t%[^\n]",
				&tmp_int[0],&tmp_int[1],tmp_char[0],tmp_char[1],tmp_char[2],&tmp_int[2],
				&tmp_int[3],&tmp_int[4],&tmp_int[5],&tmp_int[6],&tmp_int[7],&tmp_int[8],&tmp_int[9],&tmp_int[10],&tmp_int[11],&tmp_int[12],&tmp_int[13],
				&tmp_int[14],&tmp_int[15],tmp_char[3]);
			if(n==20){
				i++;
				md[i]=(struct mail_data *)aCalloc(1,sizeof(struct mail_data));
				md[i]->mail_num = (unsigned int)tmp_int[0];
				md[i]->read     = tmp_int[1];
				memcpy(md[i]->char_name,tmp_char[0],24);
				memcpy(md[i]->receive_name,tmp_char[1],24);
				memcpy(md[i]->title,tmp_char[2],40);
				md[i]->zeny           = tmp_int[2];
				md[i]->item.id        = tmp_int[3];
				md[i]->item.nameid    = tmp_int[4];
				md[i]->item.amount    = tmp_int[5];
				md[i]->item.equip     = tmp_int[6];
				md[i]->item.identify  = tmp_int[7];
				md[i]->item.refine    = tmp_int[8];
				md[i]->item.attribute = tmp_int[9];
				md[i]->item.card[0]   = tmp_int[10];
				md[i]->item.card[1]   = tmp_int[11];
				md[i]->item.card[2]   = tmp_int[12];
				md[i]->item.card[3]   = tmp_int[13];
				md[i]->times          = (unsigned int)tmp_int[14];
				md[i]->body_size      = (unsigned int)tmp_int[15];
				for(n = 0,p = tmp_char[3]; n < md[i]->body_size; n++){
					sscanf(p,"%2x",&tmp_int[16]);
					WBUFB(md[i]->body,n) = tmp_int[16];
					p += 2;
				}
			}else{
				printf("mail_data broken %d %d\n",char_id,store);
			}
		}
	}
	fclose(fp);

	// バッファオーバーフローしないように残りをNULLで埋める
	j = i;
	while(j+1<MAIL_STORE_MAX)
		md[++j] = NULL;

	if(i!=store-1 && md[i]){	// 数に相違あり？
		const struct mail *m;
		struct mail m2;
		m = mail_load(char_id);
		if(m){
			memcpy(&m2,m,sizeof(struct mail));
			if( i > 0 && m2.rates < md[i]->mail_num )
				m2.rates = md[i]->mail_num;
			if( m2.store != i+1 )
				m2.store = i+1;
			mail_save(&m2);
		}
	}
	return 0;
}

int mail_txt_deletemail(int char_id,unsigned int mail_num,const struct mail *m)
{
	struct mail m2;
	struct mail_data *md[MAIL_STORE_MAX];
	int i,j,hit=0;

	if(!m)
		return 1;

	mail_read_mail(char_id,m->store,md);
	for(i=j=0; md[i] != NULL && i < m->store; i++){
		if(md[i]->mail_num != mail_num)
			memcpy(md[j++],md[i],sizeof(struct mail_data));
		else
			hit=1;
	}
	if(!hit) {
		mail_free(md,m->store);
		return 1;
	}
	mail_save_mail(char_id,-1,m->store-1,md);

	mail_free(md,m->store);

	memcpy(&m2,m,sizeof(struct mail));
	if(m2.store > 0)
		m2.store--;
	mail_save(&m2);

	return 0;
}
static int mail_tostr(char *str,struct mail *m)
{
	int len;

	if(!m)
		return 1;

	len=sprintf(str,"%d,%d,%u,%d",
		m->char_id,m->account_id,m->rates,m->store);

	return 0;
}

static int mail_fromstr(char *str,struct mail *m)
{
	int s;
	int tmp_int[4];

	s=sscanf(str,"%d,%d,%u,%d",&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3]);

	if(s!=4) {
		memset(m,0,sizeof(struct mail));
		return 1;
	}

	m->char_id= tmp_int[0];
	m->account_id = tmp_int[1];
	m->rates = (unsigned int)tmp_int[2];
	m->store = tmp_int[3];

	return 0;
}
int mail_txt_init(void)
{
	char line[8192];
	struct mail *md;
	FILE *fp;
	int c=0;

	mail_db = numdb_init();

	if((fp=fopen(mail_txt,"r"))==NULL){
		printf("cant't read : %s\n",mail_txt);
		return 1;
	}
	while(fgets(line,sizeof(line),fp)){
		md=(struct mail *)aCalloc(1,sizeof(struct mail));
		if(mail_fromstr(line,md)==0 && md->char_id > 0){
			numdb_insert(mail_db,md->char_id,md);
		}
		else{
			printf("int_mail: broken data [%s] line %d\n",mail_txt,c);
			aFree(md);
		}
		c++;
	}
	fclose(fp);
	printf("%s init %d\n",mail_txt,c);
	return 0;
}
static int mail_sync_sub(void *key,void *data,va_list ap)
{
	char line[8192];
	FILE *fp;
	mail_tostr(line,(struct mail *)data);
	fp=va_arg(ap,FILE *);
	fprintf(fp,"%s" RETCODE,line);
	return 0;
}

int mail_txt_sync(void) {
	FILE *fp;
	int lock;
	if( (fp=lock_fopen(mail_txt,&lock))==NULL ){
		printf("int_mail: cant write [%s] !!! data is lost !!!\n",mail_txt);
		return 1;
	}
	numdb_foreach(mail_db,mail_sync_sub,fp);
	lock_fclose(fp,mail_txt,&lock);
	return 0;
}

const struct mail* mail_load(int char_id) {
	return (const struct mail *)numdb_search(mail_db,char_id);
}

int mail_txt_save(struct mail* m2) {
	struct mail *m1 = (struct mail *)numdb_search(mail_db,m2->char_id);
	if(m1 == NULL) {
		m1 = (struct mail *)aCalloc(1,sizeof(struct mail));
		numdb_insert(mail_db,m1,m2->char_id);
	}
	memcpy(m1,m2,sizeof(struct mail));
	return 1;
}

int mail_txt_new(int account_id,int char_id) {
	struct mail *m = (struct mail *)aMalloc(sizeof(struct mail));
	m->account_id = account_id;
	m->char_id = char_id;
	m->rates = 1;
	m->store = 1;
	numdb_insert(mail_db,char_id,m);
	return 0;
}

static int mail_final_sub(void *key,void *data,va_list ap)
{
	struct mail *md = (struct mail *)data;
	aFree(md);
	return 0;
}

void mail_txt_final(void)
{
	if(mail_db)
		numdb_final(mail_db,mail_final_sub);
}

void mail_txt_config_read_sub(const char *w1, const char *w2)
{
	if(strcmpi(w1,"mail_txt")==0) {
		strncpy(mail_txt, w2, sizeof(mail_txt));
	}
	if(strcmpi(w1,"mail_dir")==0) {
		strncpy(mail_dir, w2, sizeof(mail_dir));
	}
	return;
}

#define mail_store_mail mail_txt_store_mail
#define mail_save_mail  mail_txt_save_mail
#define mail_read_mail  mail_txt_read_mail
#define mail_deletemail mail_txt_deletemail
#define mail_init       mail_txt_init
#define mail_sync       mail_txt_sync
#define mail_delete     mail_txt_delete
#define mail_load       mail_txt_load
#define mail_save       mail_txt_save
#define mail_new        mail_txt_new
#define mail_final      mail_txt_final

#else /* TXT_ONLY */

static char mail_db_[256]  = "mail";
static char mail_data[256] = "mail_data";

int mail_sql_store_mail(int char_id,struct mail_data *md)
{
	unsigned int i;
	char buf[3][256], body_data[1024];
	char *p;

	if(!md)
		return 0;

	for(i=0, p=body_data; i<md->body_size; i++) {
		p += sprintf(p,"%02X",RBUFB(md->body,i));
	}

	sprintf(
		tmp_sql,
		"INSERT INTO `%s` (`char_id`, `number`, `read`, `send_name`, `receive_name`, `title`, "
		"`times`, `size`, `body`, `zeny`, "
		"`id`, `nameid`, `amount`, `equip`, `identify`, `refine`, `attribute`, "
		"`card0`, `card1`, `card2`, `card3`) "
		"VALUES ('%d','%u','%d','%s','%s','%s','%u','%u','%s','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d')",
		mail_data, char_id, md->mail_num, md->read, strecpy(buf[0],md->char_name), strecpy(buf[1],md->receive_name), strecpy(buf[2],md->title),
		md->times, md->body_size, body_data, md->zeny,
		md->item.id, md->item.nameid, md->item.amount, md->item.equip, md->item.identify, md->item.refine, md->item.attribute,
		md->item.card[0], md->item.card[1], md->item.card[2], md->item.card[3]
	);
	if(mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (insert `%s`)- %s\n", mail_data, mysql_error(&mysql_handle));
	}

	return 0;
}

int mail_sql_save_mail(int char_id,int i,int store,struct mail_data *md[MAIL_STORE_MAX])
{
	int n;

	if(!md || i < 0 || i >= MAIL_STORE_MAX)
		return 0;

	for(n=-1; n+1<store && md[n+1]; n++);
	if(n!=store-1 && md[n]){	// 数に相違あり？
		const struct mail *m;
		struct mail m2;
		m = mail_load(char_id);
		if(m){
			memcpy(&m2,m,sizeof(struct mail));
			if( m2.rates < md[n]->mail_num )
				m2.rates = md[n]->mail_num;
			if( m2.store != n+1 )
				m2.store = n+1;
			mail_save(&m2);
		}
	}
	if(!md[i])
		return 0;

	// readもしくはzeny,itemデータを更新するだけでよい
	sprintf(
		tmp_sql,
		"UPDATE `%s` SET `read` = '%d', `zeny` = '%d', "
		"`id` = '%d', `nameid` = '%d', `amount` = '%d', `equip` = '%d', `identify` = '%d', `refine` = '%d', `attribute` = '%d', "
		"`card0` = '%d', `card1` = '%d', `card2` = '%d', `card3` = '%d' "
		"WHERE `char_id` = '%d' AND `number` = '%u'",
		mail_data, md[i]->read, md[i]->zeny,
		md[i]->item.id, md[i]->item.nameid, md[i]->item.amount, md[i]->item.equip, md[i]->item.identify, md[i]->item.refine, md[i]->item.attribute,
		md[i]->item.card[0], md[i]->item.card[1], md[i]->item.card[2], md[i]->item.card[3],
		char_id, md[i]->mail_num
	);
	if(mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error - %s\n", mysql_error(&mysql_handle));
	}

	return 0;
}
int mail_sql_read_mail(int char_id,int store,struct mail_data *md[MAIL_STORE_MAX])
{
	int i=-1,j;
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;

	sprintf(tmp_sql, "SELECT * FROM `%s` WHERE `char_id` = '%d' ORDER BY `number`", mail_data, char_id);

	if(mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error - (select `%s`)- %s\n", mail_data, mysql_error(&mysql_handle));
	}
	sql_res = mysql_store_result(&mysql_handle);

	if(sql_res && mysql_num_rows(sql_res) > 0) {
		// 0       1      2    3         4            5
		// char_id number read send_name receive_name title
		// 6     7    8    9
		// times size body zeny
		// 10 11     12     13    14       15     16
		// id nameid amount equip identify refine attribute
		// 17    18    19    20
		// card0 card1 card2 card3
		while(i+1<store && (sql_row = mysql_fetch_row(sql_res)) && i+1<MAIL_STORE_MAX) {
			unsigned int n;
			int tmp_int;
			char *p;
			i++;
			md[i]=(struct mail_data *)aCalloc(1,sizeof(struct mail_data));
			md[i]->mail_num = (unsigned int)atoi(sql_row[1]);
			md[i]->read     = atoi(sql_row[2]);
			memcpy(md[i]->char_name, sql_row[3] ,24);
			memcpy(md[i]->receive_name, sql_row[4], 24);
			memcpy(md[i]->title, sql_row[5], 40);
			md[i]->times     = (unsigned int)atoi(sql_row[6]);
			md[i]->body_size = (unsigned int)atoi(sql_row[7]);

			for(n = 0,p = sql_row[8]; n < md[i]->body_size; n++) {
				sscanf(p,"%2x",&tmp_int);
				WBUFB(md[i]->body,n) = tmp_int;
				p += 2;
			}

			md[i]->zeny           = atoi(sql_row[9]);
			md[i]->item.id        = atoi(sql_row[10]);
			md[i]->item.nameid    = atoi(sql_row[11]);
			md[i]->item.amount    = atoi(sql_row[12]);
			md[i]->item.equip     = atoi(sql_row[13]);
			md[i]->item.identify  = atoi(sql_row[14]);
			md[i]->item.refine    = atoi(sql_row[15]);
			md[i]->item.attribute = atoi(sql_row[16]);
			md[i]->item.card[0]   = atoi(sql_row[17]);
			md[i]->item.card[1]   = atoi(sql_row[18]);
			md[i]->item.card[2]   = atoi(sql_row[19]);
			md[i]->item.card[3]   = atoi(sql_row[20]);
		}
	}
	if(sql_res)
		mysql_free_result(sql_res);

	// バッファオーバーフローしないように残りをNULLで埋める
	j = i;
	while(j+1<MAIL_STORE_MAX)
		md[++j] = NULL;

	if(i!=store-1 && md[i]){	// 数に相違あり？
		const struct mail *m;
		struct mail m2;
		m = mail_load(char_id);
		if(m){
			memcpy(&m2,m,sizeof(struct mail));
			if( i > 0 && m2.rates < md[i]->mail_num )
				m2.rates = md[i]->mail_num;
			if( m2.store != i+1 )
				m2.store = i+1;
			mail_save(&m2);
		}
	}
	return 0;
}

int mail_sql_deletemail(int char_id,unsigned int mail_num,const struct mail *m)
{
	struct mail m2;

	if(!m)
		return 1;

	sprintf(tmp_sql, "DELETE FROM `%s` WHERE `char_id` = '%d' AND `number` = '%u'", mail_data, char_id, mail_num);
	if(mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error - %s\n", mysql_error(&mysql_handle));
	}

	if(mysql_affected_rows(&mysql_handle) <= 0)
		return 1;

	memcpy(&m2,m,sizeof(struct mail));
	if(m2.store > 0)
		m2.store--;
	mail_save(&m2);

	return 0;
}

int mail_sql_init(void)
{
	mail_db = numdb_init();
	return 0;
}

int mail_sql_sync(void) {
	// nothing to do
	return 0;
}

const struct mail* mail_sql_load(int char_id)
{
	struct mail *m = (struct mail *)numdb_search(mail_db,char_id);
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;

	if(m && m->char_id == char_id) {
		// 既にキャッシュが存在する
		return m;
	}
	if(m == NULL) {
		m = (struct mail *)aMalloc(sizeof(struct mail));
		numdb_insert(mail_db,char_id,m);
	}
	memset(m, 0, sizeof(struct mail));

	m->char_id = char_id;

	//`mail` (`char_id`, `account_id`, `rates`, `store`)
	sprintf(
		tmp_sql,
		"SELECT `char_id`, `account_id`, `rates`, `store`"
		"FROM `%s` WHERE `char_id` = '%d'",
		mail_db_, char_id
	);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (select `%s`)- %s\n", mail_db_, mysql_error(&mysql_handle) );
		m->char_id = -1;
		return NULL;
	}
	sql_res = mysql_store_result(&mysql_handle);

	if(sql_res && mysql_num_rows(sql_res) > 0) {
		sql_row = mysql_fetch_row(sql_res);
		if(sql_row == NULL) {
			printf("mail - failed\n");
			m->char_id = -1;
			mysql_free_result(sql_res);
			return NULL;
		}
		m->account_id = atoi(sql_row[1]);
		m->rates      = (unsigned int)atoi(sql_row[2]);
		m->store      = atoi(sql_row[3]);

		mysql_free_result(sql_res);
	} else {
		// 見つからなくても正常
		if(sql_res)
			mysql_free_result(sql_res);
		return NULL;
	}

	return m;
}

int mail_sql_save(struct mail* m2)
{
	const struct mail *m1 = mail_sql_load(m2->char_id);

	if(m1 == NULL || m1->char_id != m2->char_id)
		return 0;

	sprintf(tmp_sql, "DELETE FROM `%s` WHERE `char_id`='%d'", mail_db_, m2->char_id);
	if (mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (delete `%s`)- %s\n", mail_db_, mysql_error(&mysql_handle));
	}

	// `mail` (`char_id`, `account_id`, `rates`, `store`)
	sprintf(
		tmp_sql, "INSERT INTO `%s` (`char_id`, `account_id`, `rates`, `store`) VALUES ('%d','%d','%u','%d')",
		mail_db_, m2->char_id, m2->account_id, m2->rates, m2->store
	);
	if(mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (insert `%s`)- %s\n", mail_db_, mysql_error(&mysql_handle));
	}

	{
		struct mail *m3 = (struct mail *)numdb_search(mail_db,m2->char_id);
		if(m3)
			memcpy(m3,m2,sizeof(struct mail));
	}
	return 1;
}

int mail_sql_new(int account_id,int char_id)
{
	struct mail *m = (struct mail *)numdb_search(mail_db,char_id);

	// mail_load() でmail_dbに登録したあと呼ばれるはずだが念のため
	if(m == NULL) {
		m = (struct mail *)aMalloc(sizeof(struct mail));
		numdb_insert(mail_db,char_id,m);
	}

	m->account_id = account_id;
	m->char_id = char_id;
	m->rates = 1;
	m->store = 1;

	sprintf(
		tmp_sql, "INSERT INTO `%s` (`char_id`, `account_id`, `rates`, `store`) VALUES ('%d','%d','%u','%d')",
		mail_db_, m->char_id, m->account_id, m->rates, m->store
	);
	if(mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (insert `%s`)- %s\n", mail_db_, mysql_error(&mysql_handle));
	}

	return 0;
}

static int mail_final_sub(void *key,void *data,va_list ap)
{
	struct mail *md = (struct mail *)data;
	aFree(md);
	return 0;
}

void mail_sql_final(void)
{
	if(mail_db)
		numdb_final(mail_db,mail_final_sub);
}

void mail_sql_config_read_sub(const char *w1, const char *w2)
{
	// nothing to do
	return;
}

#define mail_store_mail mail_sql_store_mail
#define mail_save_mail  mail_sql_save_mail
#define mail_read_mail  mail_sql_read_mail
#define mail_deletemail mail_sql_deletemail
#define mail_init       mail_sql_init
#define mail_sync       mail_sql_sync
#define mail_delete     mail_sql_delete
#define mail_load       mail_sql_load
#define mail_save       mail_sql_save
#define mail_new        mail_sql_new
#define mail_final      mail_sql_final

#endif /* TXT_ONLY */

//--------------------------------------------------------
void mail_free(struct mail_data *md[MAIL_STORE_MAX],int store)
{
	int i;
	for(i=0;i<store;i++) {
		if(md[i]!=NULL)
			aFree(md[i]);
		else
			break;
	}
}

//------------------------------------------------------------------------
int mapif_mail_res(const int fd,int account,int flag)
{
	WFIFOW(fd,0)=0x3848;
	WFIFOL(fd,2)=account;
	WFIFOB(fd,6)=flag;
	WFIFOSET(fd,7);
	return 0;
}
int mapif_send_mailbox(int fd,const char *char_name,int store,struct mail_data *md[MAIL_STORE_MAX])
{
	int i,size = sizeof(struct mail_data);
	WFIFOW(fd,0)=0x3849;
	WFIFOL(fd,4)=store;
	memcpy(WFIFOP(fd,8),char_name,24);
	for(i=0;i<store && md[i]!=NULL;i++)
		memcpy(WFIFOP(fd,32+i*size),md[i],size);
	WFIFOW(fd,2)=32+i*size;
	WFIFOSET(fd,WFIFOW(fd,2));
	return 0;
}
int mapif_mail_newmail(int fd,struct mail_data *md)
{
	int size=sizeof(struct mail_data);

	WFIFOW(fd,0)=0x384a;
	WFIFOW(fd,2)=4+size;
	memcpy(WFIFOP(fd,4),md,size);
	WFIFOSET(fd,WFIFOW(fd,2));
	return 0;
}
int mapif_mail_readmail(int fd,struct mail_data *md)
{
	int size = sizeof(struct mail_data);

	WFIFOW(fd,0)=0x384b;
	WFIFOW(fd,2)=4+size;
	memcpy(WFIFOP(fd,4),md,size);
	WFIFOSET(fd,WFIFOW(fd,2));
	return 0;
}
int mapif_mail_delmail(int fd,int account,unsigned int mail_num,int flag)
{
	WFIFOW(fd,0)=0x384c;
	WFIFOL(fd,2)=account;
	WFIFOL(fd,6)=mail_num;
	WFIFOB(fd,10)=flag;
	WFIFOSET(fd,11);
	return 0;
}
int mapif_mail_getappend(int fd,int account,struct mail_data *md)
{
	int size = sizeof(struct item);
	if(!md)
		return 1;
	if((md->item.nameid <= 0 || md->item.amount <= 0) && md->zeny <= 0)
		return 1;

	WFIFOW(fd,0)=0x384d;
	WFIFOW(fd,2)=12+size;
	WFIFOL(fd,4)=account;
	WFIFOL(fd,8)=(md->zeny <= 0)?0:md->zeny;
	memcpy(WFIFOP(fd,12),&md->item,size);
	WFIFOSET(fd,WFIFOW(fd,2));
	memset(&md->item,0,size);
	md->zeny=0;
	return 0;
}
//--------------------------------------------------------
int mapif_parse_OpenMailBox(int fd)
{
	int char_id=RFIFOL(fd,2);
	const struct mmo_chardata *rd;
	const struct mail *m;
	struct mail_data *md[MAIL_STORE_MAX];

	rd = char_load(char_id);

	if(rd==NULL)
		return 0;

	m = mail_load(char_id);
	if(m){
		mail_read_mail(char_id,m->store,md);
		mapif_send_mailbox(fd,rd->st.name,m->store,md);
		mail_free(md,m->store);
	}
	else
		mapif_send_mailbox(fd,rd->st.name,0,NULL);
	return 0;
}
int mapif_parse_SendMail(int fd)
{
	const struct mmo_chardata *sd,*rd;
	struct mail_data md;
	int char_id,receive_id;

	if(!RFIFOP(fd,4))
		return 0;

	memcpy(&md,RFIFOP(fd,4),sizeof(struct mail_data));

	char_id    = char_nick2id(md.char_name);
	receive_id = char_nick2id(md.receive_name);
	sd         = char_load(char_id);

	if(sd==NULL)
		return 0;

	if(receive_id < 0){		// 受け取る人が存在しません
		mapif_mail_res(fd,sd->st.account_id,1);
	}else{
		const struct mail *m;
		struct mail m2;

		rd = char_load(receive_id);
		if(rd==NULL) return 0;
		if(sd->st.account_id == rd->st.account_id){	// 同じアカウントには送れない
			mapif_mail_res(fd,sd->st.account_id,1);
			return 0;
		}
		// 保存だの何だの
		m = mail_load(receive_id);
		if(m){
			memcpy(&m2,m,sizeof(struct mail));
			m2.rates++;
			m2.store++;
			mail_save(&m2);
			md.mail_num = m2.rates;
		}else{
			mail_new(rd->st.account_id,rd->st.char_id);
			md.mail_num = 1;
		}
		mail_store_mail(receive_id,&md);				// 保存
		mapif_mail_res(fd,sd->st.account_id,0);			// 送信成功
		mapif_mail_newmail(fd,&md);		// 新着メール通知
	}
	return 0;
}
int mapif_parse_DeleteMail(int fd)
{
	const struct mail *m = mail_load(RFIFOL(fd,2));
	int flag;
	if(!m) return 0;
	flag = mail_deletemail(m->char_id,RFIFOL(fd,6),m);
	mapif_mail_delmail(fd,m->account_id,RFIFOL(fd,6),flag);	// 結果送信
	return 0;
}
int mapif_parse_ReadMail(int fd)
{
	const struct mail *m;
	struct mail_data *md[MAIL_STORE_MAX];
	int i=0,char_id=RFIFOL(fd,2),read=0;
	unsigned int mail_num=RFIFOL(fd,6);

	if((m = mail_load(char_id))==NULL)
		return 0;

	if(m->store > 0){
		mail_read_mail(char_id,m->store,md);
		for(i=0;md[i] != NULL && i < m->store;i++){
			if(md[i]->mail_num == mail_num){
				mapif_mail_readmail(fd,md[i]);
				if(!md[i]->read){
					md[i]->read=1;
					read=1;
				}
				break;
			}
		}
		if(read && md[i]){
			mail_save_mail(char_id,i,m->store,md);
			mapif_send_mailbox(fd,md[i]->char_name,m->store,md);
		}
		mail_free(md,m->store);
	}
	return 0;
}
int mapif_parse_GetAppend(int fd)
{
	const struct mail *m;
	struct mail_data *md[MAIL_STORE_MAX];
	int i=0,char_id=RFIFOL(fd,2);
	unsigned int mail_num=RFIFOL(fd,6);

	if((m = mail_load(char_id))==NULL)
		return 0;
	if(m->store > 0){
		mail_read_mail(char_id,m->store,md);
		for(i=0;md[i] != NULL && i < m->store;i++){
			if(md[i]->mail_num == mail_num){
				if(!mapif_mail_getappend(fd,m->account_id,md[i])){
					mail_save_mail(char_id,i,m->store,md);
					mapif_mail_readmail(fd,md[i]);
				}
				break;
			}
		}
	}
	mail_free(md,m->store);
	return 0;
}
// map server からの通信
// ・１パケットのみ解析すること
// ・パケット長データはinter.cにセットしておくこと
// ・パケット長チェックや、RFIFOSKIPは呼び出し元で行われるので行ってはならない
// ・エラーなら0(false)、そうでないなら1(true)をかえさなければならない
int inter_mail_parse_frommap(int fd)
{
	switch(RFIFOW(fd,0)){
	case 0x3048: mapif_parse_OpenMailBox(fd); break;
	case 0x3049: mapif_parse_SendMail(fd); break;
	case 0x304a: mapif_parse_DeleteMail(fd); break;
	case 0x304b: mapif_parse_ReadMail(fd); break;
	case 0x304c: mapif_parse_GetAppend(fd); break;
	default:
		return 0;
	}
	return 1;
}

