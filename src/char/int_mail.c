
#define _INT_MAIL_C_

#include <stdio.h>
#include <stdlib.h>
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
#include "int_pet.h"

static struct dbt *mail_db = NULL;

#ifdef TXT_ONLY

static char mail_dir[1024]="save/mail_data/";
static char mail_txt[1024]="save/mail.txt";

int mail_txt_store_mail(int char_id,struct mail_data *md)
{
	char filename[1056];
	FILE *fp;
	unsigned int i;

	if(!md) return 1;

	sprintf(filename,"%s%d.txt",mail_dir,char_id);
	fp = fopen(filename,"a");

	if(fp == NULL) {
		printf("int_mail: can't write [%s] !!! data is lost !!!\n", filename);
		return 1;
	}

	fprintf(fp,"%u,%d\t%s\t%s\t%s\t%d\t%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u\t%u\t%u\t",
		md->mail_num, md->read, md->char_name, md->receive_name, md->title, md->zeny,
		md->item.id, md->item.nameid, md->item.amount, md->item.equip,
		md->item.identify, md->item.refine, md->item.attribute,
		md->item.card[0], md->item.card[1], md->item.card[2], md->item.card[3], md->item.limit,
		md->times,md->body_size);
	for(i=0; i<md->body_size; i++) {
		fprintf(fp,"%02X",(unsigned char)(md->body[i]));
	}
	fprintf(fp,RETCODE);
	fclose(fp);

	return 0;
}

int mail_txt_save_mail(int char_id,int i,int store,struct mail_data md[MAIL_STORE_MAX])
{
	char filename[1056];
	FILE *fp;
	unsigned int j;
	int n = 0, lock;

	if(!md) return 1;

	sprintf(filename,"%s%d.txt",mail_dir,char_id);
	fp = lock_fopen(filename, &lock);

	if(fp == NULL) {
		printf("int_mail: can't write [%s] !!! data is lost !!!\n", filename);
		return 1;
	}

	while(n < store) {
		fprintf(fp,"%u,%d\t%s\t%s\t%s\t%d\t%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u\t%u\t%u\t",
			md[n].mail_num, md[n].read, md[n].char_name, md[n].receive_name, md[n].title, md[n].zeny,
			md[n].item.id, md[n].item.nameid, md[n].item.amount, md[n].item.equip,
			md[n].item.identify, md[n].item.refine, md[n].item.attribute,
			md[n].item.card[0], md[n].item.card[1], md[n].item.card[2], md[n].item.card[3], md[n].item.limit,
			md[n].times, md[n].body_size);
		for(j=0; j<md[n].body_size; j++) {
			fprintf(fp,"%02X",(unsigned char)(md[n].body[j]));
		}
		fprintf(fp,RETCODE);
		n++;
	}
	lock_fclose(fp, filename, &lock);

	return 0;
}

int mail_txt_read_mail(int char_id,const struct mail *m,struct mail_data md[MAIL_STORE_MAX])
{
	int s, i = 0, lines = 0;
	int tmp_int[17];
	char tmp_str[4][1024];
	char line[65536], filename[1056];
	FILE *fp;

	if(m == NULL)
		return 1;

	sprintf(filename,"%s%d.txt",mail_dir,char_id);
	if((fp = fopen(filename,"r")) != NULL) {
		while(fgets(line,sizeof(line),fp) && i < MAIL_STORE_MAX) {
			unsigned int n;
			char *p;
			lines++;

			// Auriga-0300以降の形式
			s = sscanf(line,"%u,%d\t%1023[^\t]\t%1023[^\t]\t%1023[^\t]\t%d\t%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u\t%u\t%u\t%1023[^\r\n]",
				&tmp_int[0],&tmp_int[1],tmp_str[0],tmp_str[1],tmp_str[2],&tmp_int[2],
				&tmp_int[3],&tmp_int[4],&tmp_int[5],&tmp_int[6],&tmp_int[7],&tmp_int[8],&tmp_int[9],&tmp_int[10],&tmp_int[11],&tmp_int[12],&tmp_int[13],
				&tmp_int[14],&tmp_int[15],&tmp_int[16],tmp_str[3]);
			if(s != 21) {
				tmp_int[14] = 0;	// limit
				s = sscanf(line,"%u,%d\t%1023[^\t]\t%1023[^\t]\t%1023[^\t]\t%d\t%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\t%u\t%u\t%1023[^\r\n]",
					&tmp_int[0],&tmp_int[1],tmp_str[0],tmp_str[1],tmp_str[2],&tmp_int[2],
					&tmp_int[3],&tmp_int[4],&tmp_int[5],&tmp_int[6],&tmp_int[7],&tmp_int[8],&tmp_int[9],&tmp_int[10],&tmp_int[11],&tmp_int[12],&tmp_int[13],
					&tmp_int[15],&tmp_int[16],tmp_str[3]);
				if(s != 20) {
					printf("mail_data broken %d line %d\n",char_id,lines);
					continue;
				}
			}
			md[i].mail_num = (unsigned int)tmp_int[0];
			md[i].read     = tmp_int[1];
			memcpy(md[i].char_name,tmp_str[0],24);
			memcpy(md[i].receive_name,tmp_str[1],24);
			memcpy(md[i].title,tmp_str[2],40);
			md[i].zeny           = tmp_int[2];
			md[i].item.id        = (unsigned int)tmp_int[3];
			md[i].item.nameid    = tmp_int[4];
			md[i].item.amount    = tmp_int[5];
			md[i].item.equip     = tmp_int[6];
			md[i].item.identify  = tmp_int[7];
			md[i].item.refine    = tmp_int[8];
			md[i].item.attribute = tmp_int[9];
			md[i].item.card[0]   = tmp_int[10];
			md[i].item.card[1]   = tmp_int[11];
			md[i].item.card[2]   = tmp_int[12];
			md[i].item.card[3]   = tmp_int[13];
			md[i].item.limit     = (unsigned int)tmp_int[14];
			md[i].times          = (unsigned int)tmp_int[15];
			md[i].body_size      = (unsigned int)tmp_int[16];

			// force \0 terminal
			md[i].char_name[23]    = '\0';
			md[i].receive_name[23] = '\0';
			md[i].title[39]        = '\0';

			if(md[i].body_size > sizeof(md[i].body)) {
				printf("mail_read_mail: %d invalid body size %d line %d\n", char_id, md[i].body_size, lines);
				md[i].body_size = sizeof(md[i].body);
			}
			for(n = 0, p = tmp_str[3]; n < md[i].body_size && p[0] && p[1]; n++, p += 2) {
				int c = 0;
				sscanf(p,"%2x",&c);
				WBUFB(md[i].body,n) = c;
			}
			md[i].body_size = n;
			i++;
		}
		fclose(fp);
	}

	if(i != m->store) {	// 数に相違あり？
		struct mail m2;
		printf("mail_read_mail: %d stored number mismatch!! (%d != %d)\n", char_id, i, m->store);
		memcpy(&m2,m,sizeof(struct mail));
		if(i > 0 && m2.rates < md[i-1].mail_num) {
			m2.rates = md[i-1].mail_num;
		}
		m2.store = i;
		mail_txt_save(&m2);
	}

	return 0;
}

int mail_txt_deletemail(int char_id,unsigned int mail_num,const struct mail *m)
{
	struct mail m2;
	struct mail_data md[MAIL_STORE_MAX];
	int i;

	if(!m)
		return 1;

	memset(md, 0, sizeof(md));
	mail_txt_read_mail(char_id, m, md);

	for(i = 0; i < m->store; i++) {
		if(md[i].mail_num == mail_num) {
			if((md[i].item.nameid > 0 && md[i].item.amount > 0) || md[i].zeny > 0) {
				// 添付アイテム・Zenyがあるとメール削除できない（anti hacker）
				return 1;
			}
			break;
		}
	}
	if(i >= m->store)
		return 1;

	if(i+1 < m->store) {
		memmove(&md[i], &md[i+1], sizeof(struct mail_data) * (m->store-i-1));
	}
	mail_txt_save_mail(char_id,-1,m->store-1,md);

	memcpy(&m2,m,sizeof(struct mail));
	m2.store--;
	mail_txt_save(&m2);

	return 0;
}

static int mail_tostr(char *str,struct mail *m)
{
	if(!m)
		return 1;

	sprintf(str,"%d,%d,%u,%d",
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

	m->char_id    = tmp_int[0];
	m->account_id = tmp_int[1];
	m->rates      = (unsigned int)tmp_int[2];
	m->store      = tmp_int[3];

	return 0;
}

int mail_txt_init(void)
{
	char line[8192];
	struct mail *m;
	FILE *fp;
	int c=0;

	mail_db = numdb_init();

	if((fp=fopen(mail_txt,"r"))==NULL){
		printf("cant't read : %s\n",mail_txt);
		return 1;
	}
	while(fgets(line,sizeof(line),fp)){
		m=(struct mail *)aCalloc(1,sizeof(struct mail));
		if(mail_fromstr(line,m)==0 && m->char_id > 0) {
			numdb_insert(mail_db,m->char_id,m);
			if(m->store < 0 || m->store >= MAIL_STORE_MAX) {	// 値が異常なので補正する
				struct mail_data md[MAIL_STORE_MAX];
				memset(md, 0, sizeof(md));
				mail_txt_read_mail(m->char_id, m, md);
			}
		} else {
			printf("int_mail: broken data [%s] line %d\n",mail_txt,c);
			aFree(m);
		}
		c++;
	}
	fclose(fp);
	printf("%s init %d\n",mail_txt,c);

	return 0;
}

static int mail_txt_sync_sub(void *key,void *data,va_list ap)
{
	char line[8192];
	FILE *fp;

	mail_tostr(line,(struct mail *)data);
	fp=va_arg(ap,FILE *);
	fprintf(fp,"%s" RETCODE,line);

	return 0;
}

int mail_txt_sync(void)
{
	FILE *fp;
	int lock;

	if( (fp=lock_fopen(mail_txt,&lock))==NULL ){
		printf("int_mail: cant write [%s] !!! data is lost !!!\n",mail_txt);
		return 1;
	}
	numdb_foreach(mail_db,mail_txt_sync_sub,fp);
	lock_fclose(fp,mail_txt,&lock);

	return 0;
}

// キャラ削除時
int mail_txt_delete(int char_id)
{
	char filename[1056];
	struct mail *m = (struct mail *)numdb_search(mail_db,char_id);

	if(m) {
		struct mail_data md[MAIL_STORE_MAX];
		int i;

		memset(md, 0, sizeof(md));
		mail_txt_read_mail(char_id, m, md);

		for(i = 0; i < m->store; i++) {
			if(md[i].item.card[0] == (short)0xff00)
				pet_delete(*((long *)(&md[i].item.card[1])));
		}

		if(m->char_id == char_id) {
			numdb_erase(mail_db,char_id);
			aFree(m);
		}
	}
	sprintf(filename,"%s%d.txt",mail_dir,char_id);
	remove(filename);

	return 0;
}

const struct mail* mail_txt_load(int char_id)
{
	return (const struct mail *)numdb_search(mail_db,char_id);
}

int mail_txt_save(struct mail* m2)
{
	struct mail *m1 = (struct mail *)numdb_search(mail_db,m2->char_id);

	if(m1 == NULL) {
		m1 = (struct mail *)aCalloc(1,sizeof(struct mail));
		numdb_insert(mail_db,m1,m2->char_id);
	}
	memcpy(m1,m2,sizeof(struct mail));

	return 1;
}

int mail_txt_new(int account_id,int char_id)
{
	struct mail *m = (struct mail *)aMalloc(sizeof(struct mail));

	m->account_id = account_id;
	m->char_id = char_id;
	m->rates = 1;
	m->store = 1;
	numdb_insert(mail_db,char_id,m);

	return 0;
}

static int mail_txt_final_sub(void *key,void *data,va_list ap)
{
	struct mail *md = (struct mail *)data;

	aFree(md);

	return 0;
}

void mail_txt_final(void)
{
	if(mail_db)
		numdb_final(mail_db,mail_txt_final_sub);
}

void mail_txt_config_read_sub(const char *w1, const char *w2)
{
	if(strcmpi(w1,"mail_txt")==0) {
		strncpy(mail_txt, w2, sizeof(mail_txt) - 1);
	}
	if(strcmpi(w1,"mail_dir")==0) {
		strncpy(mail_dir, w2, sizeof(mail_dir) - 1);
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
	char buf[3][256];
	char *p;

	if(!md)
		return 0;

	p  = tmp_sql;
	p += sprintf(
		p,
		"INSERT INTO `%s` (`char_id`, `number`, `read`, `send_name`, `receive_name`, `title`, "
		"`times`, `size`, `body`, `zeny`, "
		"`id`, `nameid`, `amount`, `equip`, `identify`, `refine`, `attribute`, "
		"`card0`, `card1`, `card2`, `card3`, `limit`) "
		"VALUES ('%d','%u','%d','%s','%s','%s','%u','%u','",
		mail_data, char_id, md->mail_num, md->read, strecpy(buf[0],md->char_name), strecpy(buf[1],md->receive_name), strecpy(buf[2],md->title),
		md->times, md->body_size
	);

	// SELECT HEX()
	for(i=0; i<md->body_size; i++) {
		p += sprintf(p, "%02X", (unsigned char)(md->body[i]));
	}

	p += sprintf(
		p,
		"','%d','%u','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%u')",
		md->zeny, md->item.id, md->item.nameid, md->item.amount, md->item.equip, md->item.identify, md->item.refine, md->item.attribute,
		md->item.card[0], md->item.card[1], md->item.card[2], md->item.card[3], md->item.limit
	);
	if(mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (insert `%s`)- %s\n", mail_data, mysql_error(&mysql_handle));
	}

	return 0;
}

int mail_sql_save_mail(int char_id,int i,int store,struct mail_data md[MAIL_STORE_MAX])
{
	if(!md || i < 0 || i >= MAIL_STORE_MAX)
		return 0;

	// readもしくはzeny,itemデータを更新するだけでよい
	sprintf(
		tmp_sql,
		"UPDATE `%s` SET `read` = '%d', `zeny` = '%d', "
		"`id` = '%u', `nameid` = '%d', `amount` = '%d', `equip` = '%d', `identify` = '%d', `refine` = '%d', `attribute` = '%d', "
		"`card0` = '%d', `card1` = '%d', `card2` = '%d', `card3` = '%d', `limit` = '%u' "
		"WHERE `char_id` = '%d' AND `number` = '%u'",
		mail_data, md[i].read, md[i].zeny,
		md[i].item.id, md[i].item.nameid, md[i].item.amount, md[i].item.equip, md[i].item.identify, md[i].item.refine, md[i].item.attribute,
		md[i].item.card[0], md[i].item.card[1], md[i].item.card[2], md[i].item.card[3], md[i].item.limit,
		char_id, md[i].mail_num
	);
	if(mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (update `%s`)- %s\n", mail_data, mysql_error(&mysql_handle));
	}

	return 0;
}

int mail_sql_read_mail(int char_id,const struct mail *m,struct mail_data md[MAIL_STORE_MAX])
{
	int i = 0;
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;

	if(m == NULL)
		return 1;

	sprintf(tmp_sql, "SELECT "
		"`number`, `read`, `send_name`, `receive_name`, `title`, `times`, `size`, `body`, `zeny`,"
		"`id`, `nameid`, `amount`, `equip`, `identify`, `refine`, `attribute`"
		"`card0`, `card1`, `card2`, `card3`, `limit`"
		" FROM `%s` WHERE `char_id` = '%d' ORDER BY `number`", mail_data, char_id);

	if(mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error - (select `%s`)- %s\n", mail_data, mysql_error(&mysql_handle));
	}
	sql_res = mysql_store_result(&mysql_handle);

	if(sql_res && mysql_num_rows(sql_res) > 0) {
		while((sql_row = mysql_fetch_row(sql_res)) && i < MAIL_STORE_MAX) {
			unsigned int n;
			char *p;

			md[i].mail_num = (unsigned int)atoi(sql_row[0]);
			md[i].read     = atoi(sql_row[1]);
			strncpy(md[i].char_name, sql_row[2] ,24);
			strncpy(md[i].receive_name, sql_row[3], 24);
			strncpy(md[i].title, sql_row[4], 40);
			md[i].times     = (unsigned int)atoi(sql_row[5]);
			md[i].body_size = (unsigned int)atoi(sql_row[6]);

			// force \0 terminal
			md[i].char_name[23]    = '\0';
			md[i].receive_name[23] = '\0';
			md[i].title[39]        = '\0';

			if(md[i].body_size > sizeof(md[i].body)) {
				printf("mail_read_mail: %d invalid body size %d!!\n", char_id, md[i].body_size);
				md[i].body_size = sizeof(md[i].body);
			}

			// SELECT UNHEX()
			for(n = 0, p = sql_row[7]; n < md[i].body_size && p[0] && p[1]; n++, p += 2) {
				int c = 0;
				sscanf(p,"%2x",&c);
				WBUFB(md[i].body,n) = c;
			}
			md[i].body_size = n;

			md[i].zeny           = atoi(sql_row[8]);
			md[i].item.id        = (unsigned int)atoi(sql_row[9]);
			md[i].item.nameid    = atoi(sql_row[10]);
			md[i].item.amount    = atoi(sql_row[11]);
			md[i].item.equip     = atoi(sql_row[12]);
			md[i].item.identify  = atoi(sql_row[13]);
			md[i].item.refine    = atoi(sql_row[14]);
			md[i].item.attribute = atoi(sql_row[15]);
			md[i].item.card[0]   = atoi(sql_row[16]);
			md[i].item.card[1]   = atoi(sql_row[17]);
			md[i].item.card[2]   = atoi(sql_row[18]);
			md[i].item.card[3]   = atoi(sql_row[19]);
			md[i].item.limit     = (unsigned int)atoi(sql_row[20]);
			i++;
		}
	}
	if(sql_res)
		mysql_free_result(sql_res);

	if(i != m->store) {	// 数に相違あり？
		struct mail m2;
		printf("mail_read_mail: %d stored number mismatch!! (%d != %d)\n", char_id, i, m->store);
		memcpy(&m2,m,sizeof(struct mail));
		if(i > 0 && m2.rates < md[i-1].mail_num) {
			m2.rates = md[i-1].mail_num;
		}
		m2.store = i;
		mail_sql_save(&m2);
	}
	return 0;
}

int mail_sql_deletemail(int char_id,unsigned int mail_num,const struct mail *m)
{
	struct mail_data md[MAIL_STORE_MAX];
	struct mail m2;
	int i;

	if(!m)
		return 1;

	memset(md, 0, sizeof(md));
	mail_sql_read_mail(char_id, m, md);

	for(i = 0; i < m->store; i++) {
		if(md[i].mail_num == mail_num) {
			if((md[i].item.nameid > 0 && md[i].item.amount > 0) || md[i].zeny > 0) {
				// 添付アイテム・Zenyがあるとメール削除できない（anti hacker）
				return 1;
			}
			break;
		}
	}
	if(i >= m->store)
		return 1;

	sprintf(tmp_sql, "DELETE FROM `%s` WHERE `char_id` = '%d' AND `number` = '%u'", mail_data, char_id, mail_num);
	if(mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (delete `%s`)- %s\n", mail_data, mysql_error(&mysql_handle));
	}

	if(mysql_affected_rows(&mysql_handle) <= 0) {
		// 削除失敗
		return 1;
	}

	memcpy(&m2,m,sizeof(struct mail));
	m2.store--;
	mail_sql_save(&m2);

	return 0;
}

int mail_sql_init(void)
{
	mail_db = numdb_init();
	return 0;
}

int mail_sql_sync(void)
{
	// nothing to do
	return 0;
}

// キャラ削除時
int mail_sql_delete(int char_id)
{
	struct mail *m = (struct mail *)numdb_search(mail_db,char_id);

	if(m) {
		struct mail_data md[MAIL_STORE_MAX];
		int i;

		memset(md, 0, sizeof(md));
		mail_sql_read_mail(char_id, m, md);

		for(i = 0; i < m->store; i++) {
			if(md[i].item.card[0] == (short)0xff00)
				pet_delete(*((long *)(&md[i].item.card[1])));
		}
		if(m->char_id == char_id) {
			numdb_erase(mail_db,char_id);
			aFree(m);
		}
	}

	sprintf(tmp_sql, "DELETE FROM `%s` WHERE `char_id` = '%d'", mail_db_, char_id);
	if(mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (delete `%s`)- %s\n", mail_db_, mysql_error(&mysql_handle));
	}
	sprintf(tmp_sql, "DELETE FROM `%s` WHERE `char_id` = '%d'", mail_data, char_id);
	if(mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (delete `%s`)- %s\n", mail_data, mysql_error(&mysql_handle));
	}

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

	// `mail` (`char_id`, `account_id`, `rates`, `store`)
	sprintf(
		tmp_sql,
		"SELECT `account_id`, `rates`, `store`"
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
		m->account_id = atoi(sql_row[0]);
		m->rates      = (unsigned int)atoi(sql_row[1]);
		m->store      = atoi(sql_row[2]);

		if(m->store < 0 || m->store >= MAIL_STORE_MAX) {	// 値が異常なので補正する
			struct mail_data md[MAIL_STORE_MAX];
			memset(md, 0, sizeof(md));
			mail_sql_read_mail(m->char_id, m, md);
		}
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

static int mail_sql_final_sub(void *key,void *data,va_list ap)
{
	struct mail *md = (struct mail *)data;

	aFree(md);

	return 0;
}

void mail_sql_final(void)
{
	if(mail_db)
		numdb_final(mail_db,mail_sql_final_sub);
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

//------------------------------------------------------------------------
int mapif_mail_res(const int fd,int account,int flag)
{
	WFIFOW(fd,0)=0x3848;
	WFIFOL(fd,2)=account;
	WFIFOB(fd,6)=flag;
	WFIFOSET(fd,7);
	return 0;
}

int mapif_send_mailbox(int fd,const char *char_name,int store,struct mail_data md[MAIL_STORE_MAX])
{
	int i,size = sizeof(struct mail_data);

	if(md == NULL)
		return 0;

	WFIFOW(fd,0)=0x3849;
	WFIFOL(fd,4)=store;
	memcpy(WFIFOP(fd,8),char_name,24);
	for(i=0;i<store;i++)
		memcpy(WFIFOP(fd,32+i*size),&md[i],size);
	WFIFOW(fd,2)=32+i*size;
	WFIFOSET(fd,WFIFOW(fd,2));
	return 0;
}

int mapif_mail_newmail(int fd,struct mail_data *md)
{
	int size = sizeof(struct mail_data);

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
	WFIFOL(fd,8)=(md->zeny <= 0)? 0: md->zeny;
	memcpy(WFIFOP(fd,12),&md->item,size);
	WFIFOSET(fd,WFIFOW(fd,2));

	memset(&md->item,0,size);
	md->zeny=0;
	return 0;
}

int mapif_mail_checkok(int fd,int account,struct mail_data *md)
{
	int size = sizeof(struct mail_data);

	if(!md)
		return 1;

	WFIFOW(fd,0) = 0x384e;
	WFIFOW(fd,2) = 8+size;
	WFIFOL(fd,4) = account;
	memcpy(WFIFOP(fd,8),md,size);
	WFIFOSET(fd,WFIFOW(fd,2));
	return 0;
}

//--------------------------------------------------------
int mapif_parse_OpenMailBox(int fd)
{
	int char_id = RFIFOL(fd,2);
	const struct mmo_chardata *rd;
	const struct mail *m;
	struct mail_data md[MAIL_STORE_MAX];

	rd = char_load(char_id);

	if(rd == NULL)
		return 0;

	memset(md, 0, sizeof(md));

	m = mail_load(char_id);
	if(m) {
		mail_read_mail(char_id, m, md);
		mapif_send_mailbox(fd,rd->st.name,m->store,md);
	} else {
		mapif_send_mailbox(fd,rd->st.name,0,md);
	}
	return 0;
}

int mapif_parse_SendMail(int fd)
{
	const struct mmo_chardata *sd, *rd;
	const struct mail *m;
	struct mail_data md;

	if(!RFIFOP(fd,4))
		return 0;

	memcpy(&md,RFIFOP(fd,4),sizeof(struct mail_data));

	sd = char_nick2chardata(md.char_name);
	if(sd == NULL)
		return 0;

	rd = char_nick2chardata(md.receive_name);
	if(rd == NULL) {	// 受け取る人が存在しません
		mapif_mail_res(fd,sd->st.account_id,1);
		return 0;
	}
	if(sd->st.account_id == rd->st.account_id) {	// 同じアカウントには送れない
		mapif_mail_res(fd,sd->st.account_id,1);
		return 0;
	}

	// 保存だの何だの
	m = mail_load(rd->st.char_id);
	if(m) {
		struct mail m2;
		if(m->store >= MAIL_STORE_MAX) {
			// 最大受信数を越える場合は送信成功扱いにしておく？
			mapif_mail_res(fd,sd->st.account_id,0);
			return 0;
		}
		memcpy(&m2,m,sizeof(struct mail));
		m2.rates++;
		m2.store++;
		mail_save(&m2);
		md.mail_num = m2.rates;
	} else {
		mail_new(rd->st.account_id,rd->st.char_id);
		md.mail_num = 1;
	}
	mail_store_mail(rd->st.char_id,&md);	// 保存
	mapif_mail_res(fd,sd->st.account_id,0);	// 送信成功
	mapif_mail_newmail(fd,&md);		// 新着メール通知

	return 0;
}

int mapif_parse_DeleteMail(int fd)
{
	const struct mail *m = mail_load(RFIFOL(fd,2));
	int flag;

	if(!m)
		return 0;

	flag = mail_deletemail(m->char_id,RFIFOL(fd,6),m);
	mapif_mail_delmail(fd,m->account_id,RFIFOL(fd,6),flag);	// 結果送信
	return 0;
}

int mapif_parse_ReadMail(int fd)
{
	const struct mail *m;
	int char_id = RFIFOL(fd,2);
	unsigned int mail_num = RFIFOL(fd,6);

	if((m = mail_load(char_id)) == NULL)
		return 0;

	if(m->store > 0) {
		struct mail_data md[MAIL_STORE_MAX];
		int i;

		memset(md, 0, sizeof(md));
		mail_read_mail(char_id, m, md);

		for(i = 0; i < m->store; i++) {
			if(md[i].mail_num == mail_num) {
				mapif_mail_readmail(fd,&md[i]);
				if(!md[i].read) {
					md[i].read = 1;
					mail_save_mail(char_id,i,m->store,md);
					mapif_send_mailbox(fd,md[i].char_name,m->store,md);
				}
				break;
			}
		}
	}
	return 0;
}

int mapif_parse_GetAppend(int fd)
{
	const struct mail *m;
	int char_id = RFIFOL(fd,2);
	unsigned int mail_num = RFIFOL(fd,6);

	if((m = mail_load(char_id)) == NULL)
		return 0;

	if(m->store > 0) {
		struct mail_data md[MAIL_STORE_MAX];
		int i;

		memset(md, 0, sizeof(md));
		mail_read_mail(char_id, m, md);

		for(i = 0; i < m->store; i++) {
			if(md[i].mail_num == mail_num){
				if(!mapif_mail_getappend(fd,m->account_id,&md[i])) {
					mail_save_mail(char_id,i,m->store,md);
					mapif_mail_readmail(fd,&md[i]);
				}
				break;
			}
		}
	}
	return 0;
}

int mapif_parse_CheckMail(int fd)
{
	int send_id = RFIFOL(fd,4);
	struct mail_data *md = (struct mail_data *)RFIFOP(fd,8);
	const struct mmo_chardata *rd;

	if(md == NULL)
		return 0;

	rd = char_nick2chardata(md->receive_name);
	if(rd == NULL || rd->st.account_id == send_id) {
		// 受け取る人が存在しません
		mapif_mail_res(fd,send_id,1);
	} else {
		mapif_mail_checkok(fd,send_id,md);
	}

	return 0;
}

// map server からの通信
// ・１パケットのみ解析すること
// ・パケット長データはinter.cにセットしておくこと
// ・パケット長チェックや、RFIFOSKIPは呼び出し元で行われるので行ってはならない
// ・エラーなら0(false)、そうでないなら1(true)をかえさなければならない
int inter_mail_parse_frommap(int fd)
{
	switch(RFIFOW(fd,0)) {
	case 0x3049: mapif_parse_OpenMailBox(fd); break;
	case 0x304a: mapif_parse_SendMail(fd);    break;
	case 0x304b: mapif_parse_DeleteMail(fd);  break;
	case 0x304c: mapif_parse_ReadMail(fd);    break;
	case 0x304d: mapif_parse_GetAppend(fd);   break;
	case 0x304e: mapif_parse_CheckMail(fd);   break;
	default:
		return 0;
	}
	return 1;
}
