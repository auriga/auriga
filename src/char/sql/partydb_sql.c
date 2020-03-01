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
#include <string.h>

#include "mmo.h"
#include "db.h"
#include "malloc.h"
#include "sqldbs.h"
#include "utils.h"
#include "nullpo.h"

#include "partydb_sql.h"

static struct dbt *party_db = NULL;

/*==========================================
 * 設定ファイルの読込
 *------------------------------------------
 */
int partydb_sql_config_read_sub(const char *w1,const char *w2)
{
	return 0;
}

/*==========================================
 * 同期
 *------------------------------------------
 */
int partydb_sql_sync(void)
{
	// nothing to do
	return 0;
}

/*==========================================
 * パーティ名からパーティデータをロード
 *------------------------------------------
 */
const struct party* partydb_sql_load_str(const char *str)
{
	char buf[256];

	if(sqldbs_query(&mysql_handle, "SELECT `party_id` FROM `" PARTY_TABLE "` WHERE `name` = '%s'", strecpy(buf, str)))
	{
		int id_num = -1;
		char **sql_row = sqldbs_fetch(&mysql_handle);

		if(sql_row) {
			id_num = atoi(sql_row[0]);
		}
		sqldbs_free_result(&mysql_handle);

		if(id_num >= 0)
			return partydb_sql_load_num(id_num);
	}
	return NULL;
}

/*==========================================
 * パーティIDからパーティデータをロード
 *------------------------------------------
 */
const struct party* partydb_sql_load_num(int party_id)
{
	int i, leader_id = 0;
	bool result = false;
	char **sql_row;
	struct party *p = (struct party *)numdb_search(party_db, party_id);

	if(p && p->party_id == party_id) {
		return p;
	}
	if(p == NULL) {
		p = (struct party *)aMalloc(sizeof(struct party));
		numdb_insert(party_db,party_id,p);
	}
	memset(p, 0, sizeof(struct party));

	result = sqldbs_query(&mysql_handle, "SELECT `name`,`exp`,`item`,`leader_id` FROM `" PARTY_TABLE "` WHERE `party_id`='%d'", party_id);
	if(result == false) {
		p->party_id = -1;
		return NULL;
	}

	if((sql_row = sqldbs_fetch(&mysql_handle)) != NULL) {
		p->party_id = party_id;
		strncpy(p->name, sql_row[0], 24);
		p->name[23] = '\0';	// force \0 terminal
		p->exp      = atoi(sql_row[1]);
		p->item     = atoi(sql_row[2]);
		leader_id   = atoi(sql_row[3]);
	} else {
		sqldbs_free_result(&mysql_handle);
		p->party_id = -1;
		return NULL;
	}
	sqldbs_free_result(&mysql_handle);

	// Load members
	result = sqldbs_query(&mysql_handle, "SELECT `account_id`,`char_id`,`name` FROM `" CHAR_TABLE "` WHERE `party_id`='%d'", party_id);
	if(result == false) {
		p->party_id = -1;
		return NULL;
	}

	for(i = 0; (sql_row = sqldbs_fetch(&mysql_handle)); i++) {
		struct party_member *m = &p->member[i];
		m->account_id = atoi(sql_row[0]);
		m->char_id    = atoi(sql_row[1]);
		m->leader     = (m->account_id == leader_id) ? 1 : 0;
		strncpy(m->name, sql_row[2], 24);
		m->name[23] = '\0';	// force \0 terminal
	}
	sqldbs_free_result(&mysql_handle);

	return p;
}

/*==========================================
 * セーブ
 *------------------------------------------
 */
bool partydb_sql_save(struct party *p2)
{
	const struct party *p1;
	bool result = true;

	nullpo_retr(false, p2);

	p1 = partydb_sql_load_num(p2->party_id);
	if(p1 == NULL)
		return false;

	if(strcmp(p1->name, p2->name) || p1->exp != p2->exp || p1->item != p2->item) {
		char t_name[64];

		result = sqldbs_query(&mysql_handle,
			"UPDATE `" PARTY_TABLE "` SET `name`='%s', `exp`='%d', `item`='%d' WHERE `party_id`='%d'",
			strecpy(t_name, p2->name), p2->exp, p2->item, p2->party_id
		);
		if(result == false)
			return false;
	}

	{
		// cache copy
		struct party *p3 = (struct party *)numdb_search(party_db, p2->party_id);
		if(p3)
			memcpy(p3, p2, sizeof(struct party));
	}
	return result;
}

/*==========================================
 * パーティ削除
 *------------------------------------------
 */
bool partydb_sql_delete(int party_id)
{
	struct party *p;

	if( sqldbs_query(&mysql_handle, "DELETE FROM `" PARTY_TABLE "` WHERE `party_id`='%d'", party_id) == false )
		return false;

	p = (struct party *)numdb_erase(party_db, party_id);
	if(p) {
		aFree(p);
	}
	return true;
}

/*==========================================
 * パーティ作成
 *------------------------------------------
 */
bool partydb_sql_new(struct party *p)
{
	int i, leader_id = -1;
	bool result = false;
	char t_name[64];
	char **sql_row;

	for(i = 0; i < MAX_PARTY; i++) {
		if(p->member[i].account_id > 0 && p->member[i].leader) {
			leader_id = p->member[i].account_id;
			break;
		}
	}
	if(leader_id < 0)
		return false;

	result = sqldbs_query(&mysql_handle, "SELECT MAX(`party_id`) FROM `" PARTY_TABLE "`");
	if(result == false)
		return false;

	sql_row = sqldbs_fetch(&mysql_handle);
	if(sql_row[0]) {
		p->party_id = atoi(sql_row[0]) + 1;
	} else {
		p->party_id = 100;
	}
	sqldbs_free_result(&mysql_handle);

	// DBに挿入
	result = sqldbs_query(&mysql_handle,
		"INSERT INTO `" PARTY_TABLE "` (`party_id`, `name`, `exp`, `item`, `leader_id`) "
		"VALUES ('%d','%s', '%d', '%d', '%d')",
		p->party_id, strecpy(t_name, p->name), p->exp, p->item,leader_id
	);
	if(result == false)
		return false;

	numdb_insert(party_db, p->party_id, p);
	return true;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
static int partydb_sql_final_sub(void *key, void *data, va_list ap)
{
	struct party *p = (struct party *)data;

	aFree(p);

	return 0;
}

void partydb_sql_final(void)
{
	numdb_final(party_db, partydb_sql_final_sub);
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
bool partydb_sql_init(void)
{
	party_db = numdb_init();
	return true;
}
