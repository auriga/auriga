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

#ifndef TXT_ONLY

#include <stdio.h>
#include <stdlib.h>

#include "mmo.h"
#include "db.h"
#include "malloc.h"
#include "sqldbs.h"
#include "utils.h"

#include "mercdb.h"
#include "int_merc.h"

static struct dbt *merc_db = NULL;

bool mercdb_sql_init(void)
{
	merc_db = numdb_init();
	return true;
}

int mercdb_sql_sync(void)
{
	// nothing to do
	return 0;
}

bool mercdb_sql_delete(int merc_id)
{
	struct mmo_mercstatus *p = (struct mmo_mercstatus *)numdb_search(merc_db,merc_id);
	bool result = false;

	// start transaction
	if( sqldbs_simplequery(&mysql_handle, "START TRANSACTION") == false )
		return result;

	// try
	do
	{
		// delete merc
		if( sqldbs_query(&mysql_handle, "DELETE FROM `" MERC_TABLE "` WHERE `merc_id`='%d'", merc_id) == false )
			break;

		// delete merc skill
		if( sqldbs_query(&mysql_handle, "DELETE FROM `" MERC_SKILL_TABLE "` WHERE `merc_id`='%d'", merc_id) == false )
			break;

		// success
		result = true;

		// cache delete
		if( p )
		{
			numdb_erase(merc_db,p->merc_id);
			aFree(p);
		}
	} while(0);

	// end transaction
	sqldbs_simplequery(&mysql_handle, ( result == true )? "COMMIT" : "ROLLBACK");

	return result;
}

const struct mmo_mercstatus* mercdb_sql_load(int merc_id)
{
	bool is_success;
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
	memset(p, 0, sizeof(struct mmo_mercstatus));

	is_success = sqldbs_query(
		&mysql_handle,
		"SELECT `class`,`name`,`account_id`,`char_id`,`base_level`,"
		"`max_hp`,`hp`,`max_sp`,`sp`,`str`,`agi`,`vit`,`int`,`dex`,`luk`,"
		"`kill_count`,`limit` "
		"FROM `" MERC_TABLE "` WHERE `merc_id`='%d'",
		merc_id
	);
	if(!is_success) {
		p->merc_id = -1;
		return NULL;
	}
	sql_res = sqldbs_store_result(&mysql_handle);
	if (sql_res!=NULL && sqldbs_num_rows(sql_res)>0) {
		sql_row = sqldbs_fetch(sql_res);

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
		if( sql_res ) sqldbs_free_result(sql_res);
		return NULL;
	}
	sqldbs_free_result(sql_res);

	is_success = sqldbs_query(&mysql_handle, "SELECT `id`,`lv` FROM `" MERC_SKILL_TABLE "` WHERE `merc_id`='%d'", merc_id);

	if(!is_success) {
		p->merc_id = -1;
		return NULL;
	}
	sql_res = sqldbs_store_result(&mysql_handle);
	if (sql_res!=NULL && sqldbs_num_rows(sql_res)>0) {
		int i;
		for(i=0;((sql_row = sqldbs_fetch(sql_res))&&i<MAX_MERCSKILL);i++){
			int id = atoi(sql_row[0]);
			if( id < MERC_SKILLID || id >= MERC_SKILLID + MAX_MERCSKILL ) {
				// DB操作して変なスキルを覚えさせられる可能性があるのでチェック
				printf("mercdb_sql_load: invaild skill id: %d\n", id);
			} else {
				p->skill[id-MERC_SKILLID].id = id;
				p->skill[id-MERC_SKILLID].lv = atoi(sql_row[1]);
			}
		}
	}
	sqldbs_free_result(sql_res);

	p->option = 0;

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

bool mercdb_sql_save(struct mmo_mercstatus* p2)
{
	int  i;
	char sep, *p, buf[64];
	const struct mmo_mercstatus *p1 = mercdb_sql_load(p2->merc_id);

	if(p1 == NULL)
		return false;

	sep = ' ';
	p = tmp_sql;
	strcpy(p, "UPDATE `" MERC_TABLE "` SET");
	p += strlen(p);

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
		sqldbs_query(&mysql_handle, tmp_sql);
	}

	if(memcmp(p1->skill, p2->skill, sizeof(p1->skill)) ) {
		sqldbs_query(&mysql_handle, "DELETE FROM `" MERC_SKILL_TABLE "` WHERE `merc_id`='%d'", p2->merc_id);

		for(i=0;i<MAX_MERCSKILL;i++) {
			if(p2->skill[i].id && p2->skill[i].flag!=1){
				int lv = (p2->skill[i].flag==0)? p2->skill[i].lv: p2->skill[i].flag-2;
				sqldbs_query(
					&mysql_handle,
					"INSERT INTO `" MERC_SKILL_TABLE "` (`merc_id`,`id`,`lv`) VALUES ('%d','%d','%d')",
					p2->merc_id, p2->skill[i].id, lv
				);
			}
		}
	}

	{
		struct mmo_mercstatus *p3 = (struct mmo_mercstatus *)numdb_search(merc_db,p2->merc_id);
		if(p3)
			memcpy(p3,p2,sizeof(struct mmo_mercstatus));
	}
	return true;
}

bool mercdb_sql_new(struct mmo_mercstatus *p)
{
	// 傭兵IDを読み出す
	int i;
	bool is_success;
	char t_name[64];
	struct mmo_mercstatus *p2;

	is_success = sqldbs_query(
		&mysql_handle,
		"INSERT INTO `" MERC_TABLE "` (`class`,`name`,`account_id`,`char_id`,`base_level`,"
		"`max_hp`,`hp`,`max_sp`,`sp`,`str`,`agi`,`vit`,`int`,`dex`,`luk`,"
		"`kill_count`,`limit`) "
		"VALUES ('%d', '%s', '%d', '%d',"
		"'%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d',"
		"'%d', '%u')",
		p->class_, strecpy(t_name, p->name), p->account_id, p->char_id,
		p->base_level, p->max_hp, p->hp, p->max_sp, p->sp, p->str, p->agi, p->vit, p->int_, p->dex, p->luk,
		p->kill_count, p->limit
	);
	if(!is_success)
	{
		p->merc_id = -1;
		return false;
	}

	p->merc_id = (int)sqldbs_insert_id(&mysql_handle);

	// skill
	for(i=0;i<MAX_MERCSKILL;i++) {
		if(p->skill[i].id && p->skill[i].flag!=1){
			int lv = (p->skill[i].flag==0)? p->skill[i].lv: p->skill[i].flag-2;
			sqldbs_query(&mysql_handle,
				"INSERT INTO `" MERC_SKILL_TABLE "` (`merc_id`,`id`,`lv`) VALUES ('%d','%d','%d')",
				p->merc_id, p->skill[i].id, lv
			);
		}
	}

	p2 = (struct mmo_mercstatus*)aMalloc( sizeof( struct mmo_mercstatus ) );
	memcpy( p2, p, sizeof( struct mmo_mercstatus ) );
	numdb_insert(merc_db,p->merc_id,p2);

	return true;
}

static int mercdb_sql_final_sub(void *key,void *data,va_list ap)
{
	struct mmo_mercstatus *p = (struct mmo_mercstatus *)data;

	aFree(p);

	return 0;
}

void mercdb_sql_final(void)
{
	if(merc_db)
		numdb_final(merc_db,mercdb_sql_final_sub);
}

void mercdb_sql_config_read_sub(const char* w1,const char *w2)
{
	// nothing to do
	return;
}

#endif
