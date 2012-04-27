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

#include <stdio.h>
#include <stdlib.h>

#include "mmo.h"
#include "db.h"
#include "malloc.h"
#include "sqldbs.h"
#include "utils.h"

#include "elemdb_sql.h"

static struct dbt *elem_db = NULL;

bool elemdb_sql_init(void)
{
	elem_db = numdb_init();
	return true;
}

int elemdb_sql_sync(void)
{
	// nothing to do
	return 0;
}

bool elemdb_sql_delete(int elem_id)
{
	struct mmo_elemstatus *p = (struct mmo_elemstatus *)numdb_search(elem_db,elem_id);
	bool result = false;

	// start transaction
	if( sqldbs_simplequery(&mysql_handle, "START TRANSACTION") == false )
		return result;

	// try
	do
	{
		// delete elem
		if( sqldbs_query(&mysql_handle, "DELETE FROM `" ELEM_TABLE "` WHERE `elem_id`='%d'", elem_id) == false )
			break;

		// success
		result = true;

		// cache delete
		if( p )
		{
			numdb_erase(elem_db,p->elem_id);
			aFree(p);
		}
	} while(0);

	// end transaction
	sqldbs_simplequery(&mysql_handle, ( result == true )? "COMMIT" : "ROLLBACK");

	return result;
}

const struct mmo_elemstatus* elemdb_sql_load(int elem_id)
{
	bool is_success;
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;
	struct mmo_elemstatus *p = (struct mmo_elemstatus *)numdb_search(elem_db,elem_id);

	if(p && p->elem_id == elem_id) {
		return p;
	}
	if(p == NULL) {
		p = (struct mmo_elemstatus *)aMalloc(sizeof(struct mmo_elemstatus));
		numdb_insert(elem_db,elem_id,p);
	}
	memset(p, 0, sizeof(struct mmo_elemstatus));

	is_success = sqldbs_query(
		&mysql_handle,
		"SELECT `class`,`account_id`,`char_id`,"
		"`mode`,`hp`,`sp`,`limit` "
		"FROM `" ELEM_TABLE "` WHERE `elem_id`='%d'",
		elem_id
	);
	if(!is_success) {
		p->elem_id = -1;
		return NULL;
	}
	sql_res = sqldbs_store_result(&mysql_handle);
	if (sql_res!=NULL && sqldbs_num_rows(sql_res)>0) {
		sql_row = sqldbs_fetch(sql_res);

		p->elem_id      = elem_id;
		p->class_       = atoi(sql_row[0]);
		p->account_id   = atoi(sql_row[1]);
		p->char_id      = atoi(sql_row[2]);
		p->mode         = atoi(sql_row[3]);
		p->hp           = atoi(sql_row[4]);
		p->sp           = atoi(sql_row[5]);
		p->limit        = (unsigned int)atoi(sql_row[6]);
	} else {
		p->elem_id = -1;
		if( sql_res ) sqldbs_free_result(sql_res);
		return NULL;
	}
	sqldbs_free_result(sql_res);

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

bool elemdb_sql_save(struct mmo_elemstatus* p2)
{
	char sep, *p;
	const struct mmo_elemstatus *p1 = elemdb_sql_load(p2->elem_id);

	if(p1 == NULL)
		return false;

	sep = ' ';
	p = tmp_sql;
	strcpy(p, "UPDATE `" ELEM_TABLE "` SET");
	p += strlen(p);

	UPDATE_NUM(class_      ,"class");
	UPDATE_NUM(account_id  ,"account_id");
	UPDATE_NUM(char_id     ,"char_id");
	UPDATE_NUM(mode        ,"mode");
	UPDATE_NUM(hp          ,"hp");
	UPDATE_NUM(sp          ,"sp");
	UPDATE_UNUM(limit      ,"limit");

	if(sep == ',') {
		sprintf(p," WHERE `elem_id` = '%d'",p2->elem_id);
		sqldbs_query(&mysql_handle, tmp_sql);
	}

	{
		struct mmo_elemstatus *p3 = (struct mmo_elemstatus *)numdb_search(elem_db,p2->elem_id);
		if(p3)
			memcpy(p3,p2,sizeof(struct mmo_elemstatus));
	}
	return true;
}

bool elemdb_sql_new(struct mmo_elemstatus *p)
{
	// 精霊IDを読み出す
	bool is_success;
	struct mmo_elemstatus *p2;

	is_success = sqldbs_query(
		&mysql_handle,
		"INSERT INTO `" ELEM_TABLE "` (`class`,`account_id`,`char_id`,"
		"`mode`,`hp`,`sp`,`limit`) "
		"VALUES ('%d', '%d', '%d',"
		"'%d', '%d', '%d', '%u')",
		p->class_, p->account_id, p->char_id,
		p->mode, p->hp, p->sp, p->limit
	);
	if(!is_success)
	{
		p->elem_id = -1;
		return false;
	}

	p->elem_id = (int)sqldbs_insert_id(&mysql_handle);

	p2 = (struct mmo_elemstatus*)aMalloc( sizeof( struct mmo_elemstatus ) );
	memcpy( p2, p, sizeof( struct mmo_elemstatus ) );
	numdb_insert(elem_db,p->elem_id,p2);

	return true;
}

static int elemdb_sql_final_sub(void *key,void *data,va_list ap)
{
	struct mmo_elemstatus *p = (struct mmo_elemstatus *)data;

	aFree(p);

	return 0;
}

void elemdb_sql_final(void)
{
	if(elem_db)
		numdb_final(elem_db,elemdb_sql_final_sub);
}

int elemdb_sql_config_read_sub(const char* w1,const char *w2)
{
	return 0;
}
