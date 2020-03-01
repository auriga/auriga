/*
 * Copyright (C) 2002-2020  Auriga
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
#include "nullpo.h"

#include "elemdb_sql.h"

static struct dbt *elem_db = NULL;

/*==========================================
 * 設定ファイル読込
 *------------------------------------------
 */
int elemdb_sql_config_read_sub(const char* w1,const char *w2)
{
	return 0;
}

/*==========================================
 * 同期
 *------------------------------------------
 */
int elemdb_sql_sync(void)
{
	// nothing to do
	return 0;
}

/*==========================================
 * 精霊削除
 *------------------------------------------
 */
bool elemdb_sql_delete(int elem_id)
{
	bool result = false;

	if( sqldbs_transaction_start(&mysql_handle) == false )
		return result;

	// try
	do
	{
		// delete elem
		if( sqldbs_query(&mysql_handle, "DELETE FROM `" ELEM_TABLE "` WHERE `elem_id`='%d'", elem_id) == false )
			break;

		// success
		result = true;

		{
			// cache delete
			struct mmo_elemstatus *p = (struct mmo_elemstatus *)numdb_erase(elem_db, elem_id);
			if(p) {
				aFree(p);
			}
		}
	} while(0);

	sqldbs_transaction_end(&mysql_handle, result);

	return result;
}

/*==========================================
 * 精霊IDから精霊データをロード
 *------------------------------------------
 */
const struct mmo_elemstatus* elemdb_sql_load(int elem_id)
{
	char **sql_row;
	struct mmo_elemstatus *p = (struct mmo_elemstatus *)numdb_search(elem_db, elem_id);

	if(p && p->elem_id == elem_id) {
		return p;
	}
	if(p == NULL) {
		p = (struct mmo_elemstatus *)aMalloc(sizeof(struct mmo_elemstatus));
		numdb_insert(elem_db,elem_id,p);
	}
	memset(p, 0, sizeof(struct mmo_elemstatus));

	if( sqldbs_query(&mysql_handle,	"SELECT `class`,`account_id`,`char_id`,`mode`,`hp`,`sp`,`limit` FROM `" ELEM_TABLE "` WHERE `elem_id`='%d'", elem_id) == false )
	{
		p->elem_id = -1;
		return NULL;
	}

	if((sql_row = sqldbs_fetch(&mysql_handle)) != NULL) {
		p->elem_id    = elem_id;
		p->class_     = atoi(sql_row[0]);
		p->account_id = atoi(sql_row[1]);
		p->char_id    = atoi(sql_row[2]);
		p->mode       = atoi(sql_row[3]);
		p->hp         = atoi(sql_row[4]);
		p->sp         = atoi(sql_row[5]);
		p->limit      = (unsigned int)atoi(sql_row[6]);
	} else {
		p->elem_id = -1;
		p = NULL;
	}
	sqldbs_free_result(&mysql_handle);

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

/*==========================================
 * セーブ
 *------------------------------------------
 */
bool elemdb_sql_save(struct mmo_elemstatus *p2)
{
	const struct mmo_elemstatus *p1;
	char sep = ' ';
	char tmp_sql[65536];
	char *p = tmp_sql;
	bool result = false;

	nullpo_retr(false, p2);

	p1 = elemdb_sql_load(p2->elem_id);
	if(p1 == NULL)
		return false;

	strcpy(p, "UPDATE `" ELEM_TABLE "` SET");
	p += strlen(p);

	UPDATE_NUM(class_     ,"class");
	UPDATE_NUM(account_id ,"account_id");
	UPDATE_NUM(char_id    ,"char_id");
	UPDATE_NUM(mode       ,"mode");
	UPDATE_NUM(hp         ,"hp");
	UPDATE_NUM(sp         ,"sp");
	UPDATE_UNUM(limit     ,"limit");

	if( sqldbs_transaction_start(&mysql_handle) == false )
		return false;

	// try
	do {
		if(sep == ',') {
			sprintf(p, " WHERE `elem_id` = '%d'",p2->elem_id);
			if( sqldbs_simplequery(&mysql_handle, tmp_sql) == false )
				break;
		}

		// success
		result = true;

		{
			// cache copy
			struct mmo_elemstatus *p3 = (struct mmo_elemstatus *)numdb_search(elem_db, p2->elem_id);
			if(p3)
				memcpy(p3, p2, sizeof(struct mmo_elemstatus));
		}
	} while(0);

	sqldbs_transaction_end(&mysql_handle, result);

	return result;
}

/*==========================================
 * 精霊作成
 *------------------------------------------
 */
bool elemdb_sql_new(struct mmo_elemstatus *p)
{
	bool result = false;
	struct mmo_elemstatus *p2;

	nullpo_retr(false, p);

	result = sqldbs_query(&mysql_handle,
		"INSERT INTO `" ELEM_TABLE "` (`class`,`account_id`,`char_id`,`mode`,`hp`,`sp`,`limit`) "
		"VALUES ('%d', '%d', '%d', '%d', '%d', '%d', '%u')",
		p->class_, p->account_id, p->char_id, p->mode, p->hp, p->sp, p->limit
	);
	if(result == false) {
		p->elem_id = -1;
		return false;
	}

	p->elem_id = (int)sqldbs_insert_id(&mysql_handle);

	p2 = (struct mmo_elemstatus*)aMalloc(sizeof(struct mmo_elemstatus));
	memcpy(p2, p, sizeof(struct mmo_elemstatus));
	numdb_insert(elem_db, p->elem_id, p2);

	return true;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
static int elemdb_sql_final_sub(void *key, void *data, va_list ap)
{
	struct mmo_elemstatus *p = (struct mmo_elemstatus *)data;

	aFree(p);

	return 0;
}

void elemdb_sql_final(void)
{
	if(elem_db)
		numdb_final(elem_db, elemdb_sql_final_sub);
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
bool elemdb_sql_init(void)
{
	elem_db = numdb_init();
	return true;
}
