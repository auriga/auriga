/*
 * Copyright (C) 2002-2007  Auriga
 *
 * This file is part of Auriga.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#define _INT_HOM_C_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mmo.h"
#include "socket.h"
#include "db.h"
#include "lock.h"
#include "malloc.h"
#include "journal.h"
#include "sqldbs.h"

#include "char.h"
#include "inter.h"
#include "int_homun.h"

static struct dbt *homun_db = NULL;

#ifdef TXT_ONLY

static char homun_txt[1024]="save/homun.txt";
static int homun_newid = 100;

#ifdef TXT_JOURNAL
static int homun_journal_enable = 1;
static struct journal homun_journal;
static char homun_journal_file[1024]="./save/homun.journal";
static int homun_journal_cache = 1000;
#endif

void homun_txt_config_read_sub(const char* w1,const char *w2)
{
	if(strcmpi(w1,"homun_txt")==0){
		strncpy(homun_txt, w2, sizeof(homun_txt) - 1);
	}
#ifdef TXT_JOURNAL
	else if(strcmpi(w1,"homun_journal_enable")==0){
		homun_journal_enable = atoi( w2 );
	}
	else if(strcmpi(w1,"homun_journal_file")==0){
		strncpy( homun_journal_file, w2, sizeof(homun_journal_file) - 1 );
	}
	else if(strcmpi(w1,"homun_journal_cache_interval")==0){
		homun_journal_cache = atoi( w2 );
	}
#endif
}

static int homun_tostr(char *str,struct mmo_homunstatus *h)
{
	int i;
	char *str_p = str;
	unsigned short sk_lv;

	if(!h) return 0;

	if(h->hungry < 0)
		h->hungry = 0;
	else if(h->hungry > 100)
		h->hungry = 100;
	if(h->intimate < 0)
		h->intimate = 0;
	else if(h->intimate > 100000)
		h->intimate = 100000;

	str_p += sprintf(str,"%d,%d,%s\t%d,%d\t%d,%d,%d,%d,%d,%d\t%d,%d,%d,%d,%d,%d\t%d,%d,%d,%d,%d,%d\t%d,%d\t%d,%d,%d,%d,%d",
		h->homun_id,h->class_,h->name,
		h->account_id,h->char_id,
		h->base_level,h->base_exp,h->max_hp,h->hp,h->max_sp,h->sp,
		h->str,h->agi,h->vit,h->int_,h->dex,h->luk,
		h->f_str,h->f_agi,h->f_vit,h->f_int,h->f_dex,h->f_luk,
		h->status_point,h->skill_point,
		h->equip,h->intimate,h->hungry,h->rename_flag,h->incubate);

	*(str_p++)='\t';

	for(i=0;i<MAX_HOMSKILL;i++) {
		if(h->skill[i].id && h->skill[i].flag!=1){
			sk_lv = (h->skill[i].flag==0)? h->skill[i].lv: h->skill[i].flag-2;
			str_p += sprintf(str_p,"%d,%d ",h->skill[i].id,sk_lv);
		}
	}
	*(str_p++)='\t';

	*str_p='\0';
	return 0;
}

static int homun_fromstr(char *str,struct mmo_homunstatus *h)
{
	int i,s,next,set,len;
	int tmp_int[29];
	char tmp_str[256];

	if(!h) return 0;

	memset(h,0,sizeof(struct mmo_homunstatus));

	// Auriga-0594以降の形式
	s=sscanf(str,"%d,%d,%255[^\t]\t%d,%d\t%d,%d,%d,%d,%d,%d\t%d,%d,%d,%d,%d,%d\t%d,%d,%d,%d,%d,%d\t%d,%d\t%d,%d,%d,%d,%d%n",
		&tmp_int[0],&tmp_int[1],tmp_str,
		&tmp_int[2],&tmp_int[3],
		&tmp_int[4],&tmp_int[5],&tmp_int[6],&tmp_int[7],&tmp_int[8],&tmp_int[9],
		&tmp_int[10],&tmp_int[11],&tmp_int[12],&tmp_int[13],&tmp_int[14],&tmp_int[15],
		&tmp_int[16],&tmp_int[17],&tmp_int[18],&tmp_int[19],&tmp_int[20],&tmp_int[21],
		&tmp_int[22],&tmp_int[23],
		&tmp_int[24],&tmp_int[25],&tmp_int[26],&tmp_int[27],&tmp_int[28],&next
	);

	if(s!=30) {
		tmp_int[16] = 0;	// f_str
		tmp_int[17] = 0;	// f_agi
		tmp_int[18] = 0;	// f_vit
		tmp_int[19] = 0;	// f_int
		tmp_int[20] = 0;	// f_dex
		tmp_int[21] = 0;	// f_luk
		s=sscanf(str,"%d,%d,%255[^\t]\t%d,%d\t%d,%d,%d,%d,%d,%d\t%d,%d,%d,%d,%d,%d\t%d,%d\t%d,%d,%d,%d,%d%n",
			&tmp_int[0],&tmp_int[1],tmp_str,
			&tmp_int[2],&tmp_int[3],
			&tmp_int[4],&tmp_int[5],&tmp_int[6],&tmp_int[7],&tmp_int[8],&tmp_int[9],
			&tmp_int[10],&tmp_int[11],&tmp_int[12],&tmp_int[13],&tmp_int[14],&tmp_int[15],
			&tmp_int[22],&tmp_int[23],
			&tmp_int[24],&tmp_int[25],&tmp_int[26],&tmp_int[27],&tmp_int[28],&next
		);

		if(s!=24)
			return 1;
	}

	h->homun_id     = tmp_int[0];
	h->class_       = tmp_int[1];
	strncpy(h->name,tmp_str,24);
	h->name[23] = '\0';	// force \0 terminal
	h->account_id   = tmp_int[2];
	h->char_id      = tmp_int[3];
	h->base_level   = tmp_int[4];
	h->base_exp     = tmp_int[5];
	h->max_hp       = tmp_int[6];
	h->hp           = tmp_int[7];
	h->max_sp       = tmp_int[8];
	h->sp           = tmp_int[9];
	h->str          = tmp_int[10];
	h->agi          = tmp_int[11];
	h->vit          = tmp_int[12];
	h->int_         = tmp_int[13];
	h->dex          = tmp_int[14];
	h->luk          = tmp_int[15];
	h->f_str        = tmp_int[16];
	h->f_agi        = tmp_int[17];
	h->f_vit        = tmp_int[18];
	h->f_int        = tmp_int[19];
	h->f_dex        = tmp_int[20];
	h->f_luk        = tmp_int[21];
	h->status_point = tmp_int[22];
	h->skill_point  = tmp_int[23];
	h->equip        = tmp_int[24];
	h->intimate     = tmp_int[25];
	h->hungry       = tmp_int[26];
	h->rename_flag  = tmp_int[27];
	h->incubate     = tmp_int[28];
	h->option       = 0;

	if(h->hungry < 0)
		h->hungry = 0;
	else if(h->hungry > 100)
		h->hungry = 100;
	if(h->intimate < 0)
		h->intimate = 0;
	else if(h->intimate > 100000)
		h->intimate = 100000;

	if(str[next]=='\n' || str[next]=='\r')
		return 1;	// スキル情報なし

	next++;
	for(i=0;str[next] && str[next]!='\t';i++){
		int n;
		set=sscanf(str+next,"%d,%d%n",
			&tmp_int[0],&tmp_int[1],&len);
		if(set!=2)
			return 0;
		n = tmp_int[0]-HOM_SKILLID;
		if(n >= 0 && n < MAX_HOMSKILL) {
			h->skill[n].id = tmp_int[0];
			h->skill[n].lv = tmp_int[1];
		} else {
			printf("homun_fromstr: invaild skill id: %d\n", tmp_int[0]);
		}
		next+=len;
		if(str[next]==' ')
			next++;
	}
	return 0;
}

#ifdef TXT_JOURNAL
// ==========================================
// ホムデータのジャーナルのロールフォワード用コールバック関数
// ------------------------------------------
int homun_journal_rollforward( int key, void* buf, int flag )
{
	struct mmo_homunstatus* h = (struct mmo_homunstatus *)numdb_search( homun_db, key );

	// 念のためチェック
	if( flag == JOURNAL_FLAG_WRITE && key != ((struct mmo_homunstatus*)buf)->homun_id )
	{
		printf("int_homun: journal: key != homun_id !\n");
		return 0;
	}

	// データの置き換え
	if( h )
	{
		if( flag == JOURNAL_FLAG_DELETE ) {
			numdb_erase(homun_db, key);
			aFree(h);
		} else {
			memcpy( h, buf, sizeof(struct mmo_homunstatus) );
		}
		return 1;
	}

	// 追加
	if( flag != JOURNAL_FLAG_DELETE )
	{
		h = (struct mmo_homunstatus*) aCalloc( 1, sizeof( struct mmo_homunstatus ) );
		memcpy( h, buf, sizeof(struct mmo_homunstatus) );
		numdb_insert( homun_db, key, h );
		if( h->homun_id >= homun_newid)
			homun_newid=h->homun_id+1;
		return 1;
	}

	return 0;
}
int homun_txt_sync(void);
#endif

int homun_txt_init(void)
{
	char line[8192];
	struct mmo_homunstatus *h;
	FILE *fp;
	int c=0;

	homun_db=numdb_init();

	if( (fp=fopen(homun_txt,"r"))==NULL )
		return 1;
	while(fgets(line,sizeof(line),fp)){
		h=(struct mmo_homunstatus *)aCalloc(1,sizeof(struct mmo_homunstatus));
		if(homun_fromstr(line,h)==0 && h->homun_id>0){
			if( h->homun_id >= homun_newid)
				homun_newid=h->homun_id+1;
			numdb_insert(homun_db,h->homun_id,h);
		}else{
			printf("int_homun: broken data [%s] line %d\n",homun_txt,c);
			aFree(h);
		}
		c++;
	}
	fclose(fp);

#ifdef TXT_JOURNAL
	if( homun_journal_enable )
	{
		// ジャーナルデータのロールフォワード
		if( journal_load( &homun_journal, sizeof(struct mmo_homunstatus), homun_journal_file ) )
		{
			int c = journal_rollforward( &homun_journal, homun_journal_rollforward );

			printf("int_homun: journal: roll-forward (%d)\n", c );

			// ロールフォワードしたので、txt データを保存する ( journal も新規作成される)
			homun_txt_sync();
		}
		else
		{
			// ジャーナルを新規作成する
			journal_final( &homun_journal );
			journal_create( &homun_journal, sizeof(struct mmo_homunstatus), homun_journal_cache, homun_journal_file );
		}
	}
#endif

	return 0;
}

static int homun_txt_sync_sub(void *key,void *data,va_list ap)
{
	char line[8192];
	FILE *fp;

	homun_tostr(line,(struct mmo_homunstatus *)data);
	fp=va_arg(ap,FILE *);
	fprintf(fp,"%s" RETCODE,line);
	return 0;
}

int homun_txt_sync(void)
{
	FILE *fp;
	int lock;

	if( !homun_db )
		return 1;

	if( (fp=lock_fopen(homun_txt,&lock))==NULL ){
		printf("int_homun: cant write [%s] !!! data is lost !!!\n",homun_txt);
		return 1;
	}
	numdb_foreach(homun_db,homun_txt_sync_sub,fp);
	lock_fclose(fp,homun_txt,&lock);

#ifdef TXT_JOURNAL
	if( homun_journal_enable )
	{
		// コミットしたのでジャーナルを新規作成する
		journal_final( &homun_journal );
		journal_create( &homun_journal, sizeof(struct mmo_homunstatus), homun_journal_cache, homun_journal_file );
	}
#endif

	return 0;
}

int homun_txt_delete(int homun_id)
{
	struct mmo_homunstatus *p = (struct mmo_homunstatus *)numdb_search(homun_db,homun_id);

	if(p == NULL)
		return 1;

	numdb_erase(homun_db,homun_id);
	aFree(p);
	printf("homun_id: %d deleted\n",homun_id);

#ifdef TXT_JOURNAL
	if( homun_journal_enable )
		journal_write( &homun_journal, homun_id, NULL );
#endif

	return 0;
}

const struct mmo_homunstatus* homun_txt_load(int homun_id)
{
	return (const struct mmo_homunstatus *)numdb_search(homun_db,homun_id);
}

int homun_txt_save(struct mmo_homunstatus* p2)
{
	struct mmo_homunstatus* p1 = (struct mmo_homunstatus *)numdb_search(homun_db,p2->homun_id);

	if(p1 == NULL) {
		p1 = (struct mmo_homunstatus *)aMalloc(sizeof(struct mmo_homunstatus));
		numdb_insert(homun_db,p2->homun_id,p1);
	}
	memcpy(p1,p2,sizeof(struct mmo_homunstatus));

#ifdef TXT_JOURNAL
	if( homun_journal_enable )
		journal_write( &homun_journal, p1->homun_id, p1 );
#endif
	return 1;
}

int homun_txt_new(struct mmo_homunstatus *p2)
{
	struct mmo_homunstatus *p1 = (struct mmo_homunstatus *)aMalloc(sizeof(struct mmo_homunstatus));

	p2->homun_id = homun_newid++;
	memcpy(p1,p2,sizeof(struct mmo_homunstatus));
	numdb_insert(homun_db,p2->homun_id,p1);
	return 0;
}

static int homun_txt_final_sub(void *key,void *data,va_list ap)
{
	struct mmo_homunstatus *p = (struct mmo_homunstatus *)data;

	aFree(p);

	return 0;
}

void homun_txt_final(void)
{
	if(homun_db)
		numdb_final(homun_db,homun_txt_final_sub);

#ifdef TXT_JOURNAL
	if( homun_journal_enable )
	{
		journal_final( &homun_journal );
	}
#endif
}

#define homun_init   homun_txt_init
#define homun_sync   homun_txt_sync
#define homun_delete homun_txt_delete
#define homun_load   homun_txt_load
#define homun_save   homun_txt_save
#define homun_new    homun_txt_new
#define homun_final  homun_txt_final

#else /* TXT_ONLY */

int homun_sql_init(void)
{
	homun_db = numdb_init();
	return 0;
}

int homun_sql_sync(void)
{
	// nothing to do
	return 0;
}

int homun_sql_delete(int homun_id)
{
	struct mmo_homunstatus *p = (struct mmo_homunstatus *)numdb_search(homun_db,homun_id);

	if(p) {
		numdb_erase(homun_db,p->homun_id);
		aFree(p);
	}

	sqldbs_query(&mysql_handle, "DELETE FROM `" HOMUN_TABLE "` WHERE `homun_id`='%d'", homun_id);
	sqldbs_query(&mysql_handle, "DELETE FROM `" HOMUN_SKILL_TABLE "` WHERE `homun_id`='%d'", homun_id);

	return 0;
}

const struct mmo_homunstatus* homun_sql_load(int homun_id)
{
	int rc;
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;
	struct mmo_homunstatus *p = (struct mmo_homunstatus *)numdb_search(homun_db,homun_id);

	if(p && p->homun_id == homun_id) {
		return p;
	}
	if(p == NULL) {
		p = (struct mmo_homunstatus *)aMalloc(sizeof(struct mmo_homunstatus));
		numdb_insert(homun_db,homun_id,p);
	}
	memset(p, 0, sizeof(struct mmo_homunstatus));

	rc = sqldbs_query(
		&mysql_handle,
		"SELECT `class`,`name`,`account_id`,`char_id`,`base_level`,`base_exp`,"
		"`max_hp`,`hp`,`max_sp`,`sp`,`str`,`agi`,`vit`,`int`,`dex`,`luk`,"
		"`f_str`,`f_agi`,`f_vit`,`f_int`,`f_dex`,`f_luk`,"
		"`status_point`,`skill_point`,`equip`,`intimate`,`hungry`,`rename_flag`,`incubate` "
		"FROM `" HOMUN_TABLE "` WHERE `homun_id`='%d'",
		homun_id
	);
	if(rc) {
		p->homun_id = -1;
		return NULL;
	}

	sql_res = sqldbs_store_result(&mysql_handle);
	if (sql_res!=NULL && sqldbs_num_rows(sql_res)>0) {
		sql_row = sqldbs_fetch(sql_res);

		p->homun_id     = homun_id;
		p->class_       = atoi(sql_row[0]);
		strncpy(p->name,sql_row[1],24);
		p->name[23] = '\0';	// force \0 terminal
		p->account_id   = atoi(sql_row[2]);
		p->char_id      = atoi(sql_row[3]);
		p->base_level   = atoi(sql_row[4]);
		p->base_exp     = atoi(sql_row[5]);
		p->max_hp       = atoi(sql_row[6]);
		p->hp           = atoi(sql_row[7]);
		p->max_sp       = atoi(sql_row[8]);
		p->sp           = atoi(sql_row[9]);
		p->str          = atoi(sql_row[10]);
		p->agi          = atoi(sql_row[11]);
		p->vit          = atoi(sql_row[12]);
		p->int_         = atoi(sql_row[13]);
		p->dex          = atoi(sql_row[14]);
		p->luk          = atoi(sql_row[15]);
		p->f_str        = atoi(sql_row[16]);
		p->f_agi        = atoi(sql_row[17]);
		p->f_vit        = atoi(sql_row[18]);
		p->f_int        = atoi(sql_row[19]);
		p->f_dex        = atoi(sql_row[20]);
		p->f_luk        = atoi(sql_row[21]);
		p->status_point = atoi(sql_row[22]);
		p->skill_point  = atoi(sql_row[23]);
		p->equip        = atoi(sql_row[24]);
		p->intimate     = atoi(sql_row[25]);
		p->hungry       = atoi(sql_row[26]);
		p->rename_flag  = atoi(sql_row[27]);
		p->incubate     = atoi(sql_row[28]);
	} else {
		p->homun_id = -1;
		if( sql_res ) sqldbs_free_result(sql_res);
		return NULL;
	}
	sqldbs_free_result(sql_res);

	rc = sqldbs_query(&mysql_handle, "SELECT `id`,`lv` FROM `" HOMUN_SKILL_TABLE "` WHERE `homun_id`='%d'", homun_id);
	if(rc) {
		p->homun_id = -1;
		return NULL;
	}
	sql_res = sqldbs_store_result(&mysql_handle);
	if (sql_res!=NULL && sqldbs_num_rows(sql_res)>0) {
		int i;
		for(i=0;((sql_row = sqldbs_fetch(sql_res))&&i<MAX_HOMSKILL);i++){
			int id = atoi(sql_row[0]);
			if( id < HOM_SKILLID || id >= MAX_HOM_SKILLID ) {
				// DB操作して変なスキルを覚えさせられる可能性があるのでチェック
				printf("homun_sql_load: invaild skill id: %d\n", id);
			} else {
				p->skill[id-HOM_SKILLID].id = id;
				p->skill[id-HOM_SKILLID].lv = atoi(sql_row[1]);
			}
		}
	}
	sqldbs_free_result(sql_res);

	p->option = 0;
	if(p->hungry < 0)
		p->hungry = 0;
	else if(p->hungry > 100)
		p->hungry = 100;
	if(p->intimate < 0)
		p->intimate = 0;
	else if(p->intimate > 100000)
		p->intimate = 100000;

	return p;
}

#define UPDATE_NUM(val,sql) \
	if(p1->val != p2->val) {\
		p += sprintf(p,"%c`"sql"` = '%d'",sep,p2->val); sep = ',';\
	}
#define UPDATE_STR(val,sql) \
	if(strcmp(p1->val,p2->val)) {\
		p += sprintf(p,"%c`"sql"` = '%s'",sep,strecpy(buf,p2->val)); sep = ',';\
	}

int homun_sql_save(struct mmo_homunstatus* p2)
{
	int  i;
	char sep, *p, buf[64];
	const struct mmo_homunstatus *p1 = homun_sql_load(p2->homun_id);

	if(p1 == NULL) return 0;

	sep = ' ';
	p = tmp_sql;
	strcpy(p, "UPDATE `" HOMUN_TABLE "` SET");
	p += strlen(p);

	UPDATE_NUM(class_      ,"class");
	UPDATE_STR(name        ,"name");
	UPDATE_NUM(account_id  ,"account_id");
	UPDATE_NUM(char_id     ,"char_id");
	UPDATE_NUM(base_level  ,"base_level");
	UPDATE_NUM(base_exp    ,"base_exp");
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
	UPDATE_NUM(f_str       ,"f_str");
	UPDATE_NUM(f_agi       ,"f_agi");
	UPDATE_NUM(f_vit       ,"f_vit");
	UPDATE_NUM(f_int       ,"f_int");
	UPDATE_NUM(f_dex       ,"f_dex");
	UPDATE_NUM(f_luk       ,"f_luk");
	UPDATE_NUM(status_point,"status_point");
	UPDATE_NUM(skill_point ,"skill_point");
	UPDATE_NUM(equip       ,"equip");
	UPDATE_NUM(intimate    ,"intimate");
	UPDATE_NUM(hungry      ,"hungry");
	UPDATE_NUM(rename_flag ,"rename_flag");
	UPDATE_NUM(incubate    ,"incubate");

	if(sep == ',') {
		sprintf(p," WHERE `homun_id` = '%d'",p2->homun_id);
		sqldbs_query(&mysql_handle, tmp_sql);
	}

	if(memcmp(p1->skill, p2->skill, sizeof(p1->skill)) ) {
		sqldbs_query(&mysql_handle, "DELETE FROM `" HOMUN_SKILL_TABLE "` WHERE `homun_id`='%d'", p2->homun_id);

		for(i=0;i<MAX_HOMSKILL;i++) {
			if(p2->skill[i].id && p2->skill[i].flag!=1){
				int lv = (p2->skill[i].flag==0)? p2->skill[i].lv: p2->skill[i].flag-2;
				sqldbs_query(
					&mysql_handle,
					"INSERT INTO `" HOMUN_SKILL_TABLE "` (`homun_id`,`id`,`lv`) VALUES ('%d','%d','%d')",
					p2->homun_id, p2->skill[i].id, lv
				);
			}
		}
	}

	{
		struct mmo_homunstatus *p3 = (struct mmo_homunstatus *)numdb_search(homun_db,p2->homun_id);
		if(p3)
			memcpy(p3,p2,sizeof(struct mmo_homunstatus));
	}
	return 1;
}

int homun_sql_new(struct mmo_homunstatus *p)
{
	// ホムIDを読み出す
	int i, rc;
	char t_name[64];
	struct mmo_homunstatus *p2;

	rc = sqldbs_query(
		&mysql_handle,
		"INSERT INTO `" HOMUN_TABLE "` (`class`,`name`,`account_id`,`char_id`,`base_level`,`base_exp`,"
		"`max_hp`,`hp`,`max_sp`,`sp`,`str`,`agi`,`vit`,`int`,`dex`,`luk`,"
		"`f_str`,`f_agi`,`f_vit`,`f_int`,`f_dex`,`f_luk`,"
		"`status_point`,`skill_point`,`equip`,`intimate`,`hungry`,`rename_flag`,`incubate`) "
		"VALUES ('%d', '%s', '%d', '%d',"
		"'%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d',"
		"'%d', '%d', '%d', '%d', '%d', '%d',"
		"'%d', '%d', '%d', '%d', '%d', '%d', '%d')",
		p->class_, strecpy(t_name, p->name), p->account_id, p->char_id, p->base_level,
		p->base_exp, p->max_hp, p->hp, p->max_sp, p->sp, p->str, p->agi, p->vit, p->int_, p->dex, p->luk,
		p->f_str, p->f_agi, p->f_vit, p->f_int, p->f_dex, p->f_luk,
		p->status_point, p->skill_point, p->equip, p->intimate,
		p->hungry, p->rename_flag, p->incubate
	);
	if(rc){
		p->homun_id = -1;
		return 1;
	}

	p->homun_id = (int)sqldbs_insert_id(&mysql_handle);

	for(i=0;i<MAX_HOMSKILL;i++) {
		if(p->skill[i].id && p->skill[i].flag!=1){
			int lv = (p->skill[i].flag==0)? p->skill[i].lv: p->skill[i].flag-2;
			sqldbs_query(
				&mysql_handle,
				"INSERT INTO `" HOMUN_SKILL_TABLE "` (`homun_id`,`id`,`lv`) VALUES ('%d','%d','%d')",
				p->homun_id, p->skill[i].id, lv
			);
		}
	}

	p2 = (struct mmo_homunstatus*)aMalloc( sizeof( struct mmo_homunstatus ) );
	memcpy( p2, p, sizeof( struct mmo_homunstatus ) );
	numdb_insert(homun_db,p->homun_id,p2);

	return 0;
}

static int homun_sql_final_sub(void *key,void *data,va_list ap)
{
	struct mmo_homunstatus *p = (struct mmo_homunstatus *)data;

	aFree(p);

	return 0;
}

void homun_sql_final(void)
{
	if(homun_db)
		numdb_final(homun_db,homun_sql_final_sub);
}

void homun_sql_config_read_sub(const char* w1,const char *w2)
{
	// nothing to do
	return;
}

#define homun_init   homun_sql_init
#define homun_sync   homun_sql_sync
#define homun_delete homun_sql_delete
#define homun_load   homun_sql_load
#define homun_save   homun_sql_save
#define homun_new    homun_sql_new
#define homun_final  homun_sql_final

#endif

int mapif_hom_info(int fd,int account_id,int char_id,const struct mmo_homunstatus *h,unsigned char flag)
{
	if(!h)
		return 0;

	WFIFOW(fd,0)=0x3888;
	WFIFOW(fd,2)=sizeof(struct mmo_homunstatus) + 13;
	WFIFOL(fd,4)=account_id;
	WFIFOL(fd,8)=char_id;
	WFIFOB(fd,12)=flag;
	memcpy(WFIFOP(fd,13),h,sizeof(struct mmo_homunstatus));
	WFIFOSET(fd,WFIFOW(fd,2));

	return 0;
}

int mapif_save_hom_ack(int fd,int account_id,int flag)
{
	WFIFOW(fd,0)=0x3889;
	WFIFOL(fd,2)=account_id;
	WFIFOB(fd,6)=flag;
	WFIFOSET(fd,7);

	return 0;
}

int mapif_delete_hom_ack(int fd,int flag)
{
	WFIFOW(fd,0)=0x388a;
	WFIFOB(fd,2)=flag;
	WFIFOSET(fd,3);

	return 0;
}

int mapif_create_hom(int fd,int account_id,int char_id,struct mmo_homunstatus *h)
{
	if(!h || account_id <= 0 || char_id <= 0)
		return 0;
	if(homun_new(h) == 0) {
		mapif_hom_info(fd,account_id,char_id,h,1);
	}
	return 0;
}

int mapif_load_hom(int fd,int account_id,int char_id,int homun_id)
{
	const struct mmo_homunstatus *h = homun_load(homun_id);

	if(h!=NULL) {
		mapif_hom_info(fd,account_id,char_id,h,0);
	} else {
		printf("inter hom: data load error %d %d %d\n",account_id,char_id,homun_id);
	}
	return 0;
}

int mapif_save_hom(int fd,int account_id,struct mmo_homunstatus *data)
{
	if(!data || sizeof(struct mmo_homunstatus) != RFIFOW(fd,2) - 8) {
		printf("inter hom: data size error %d %d\n",sizeof(struct mmo_homunstatus),RFIFOW(fd,2)-8);
		return 0;
	}

	if(homun_load(data->homun_id)) {
		if(data->hungry < 0)
			data->hungry = 0;
		else if(data->hungry > 100)
			data->hungry = 100;
		if(data->intimate < 0)
			data->intimate = 0;
		else if(data->intimate > 100000)
			data->intimate = 100000;
		homun_save(data);
		mapif_save_hom_ack(fd,account_id,0);
	}

	return 0;
}

int mapif_delete_hom(int fd,int homun_id)
{
	mapif_delete_hom_ack(fd,homun_delete(homun_id));

	return 0;
}

//---------------------------------------------------------------------------------------
// ホムを新規作成
int mapif_parse_CreateHom(int fd)
{
	int account_id = RFIFOL(fd,4);
	int char_id    = RFIFOL(fd,8);
	struct mmo_homunstatus h;

	memcpy(&h,RFIFOP(fd,12),sizeof(struct mmo_homunstatus));

	mapif_create_hom(fd,account_id,char_id,&h);
	return 0;
}

// ホムのデータ送信
int mapif_parse_LoadHom(int fd)
{
	mapif_load_hom(fd,RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10));
	return 0;
}

// ホムのデータ受信＆保存
int mapif_parse_SaveHom(int fd)
{
	mapif_save_hom(fd,RFIFOL(fd,4),(struct mmo_homunstatus *)RFIFOP(fd,8));
	return 0;
}

// ホム削除
int mapif_parse_DeleteHom(int fd)
{
	mapif_delete_hom(fd,RFIFOL(fd,10));
	return 0;
}

// map server からの通信
// ・１パケットのみ解析すること
// ・パケット長データはinter.cにセットしておくこと
// ・パケット長チェックや、RFIFOSKIPは呼び出し元で行われるので行ってはならない
// ・エラーなら0(false)、そうでないなら1(true)をかえさなければならない
int inter_hom_parse_frommap(int fd)
{
	switch(RFIFOW(fd,0)){
	case 0x3088: mapif_parse_CreateHom(fd); break;
	case 0x3089: mapif_parse_LoadHom(fd); break;
	case 0x308a: mapif_parse_SaveHom(fd); break;
	case 0x308b: mapif_parse_DeleteHom(fd); break;
	default:
		return 0;
	}
	return 1;
}
