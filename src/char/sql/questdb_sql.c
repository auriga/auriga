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

#include "questdb_sql.h"

static struct dbt *quest_db = NULL;

// ----------------------------------------------------------
// クエストデータ読み込み
// ----------------------------------------------------------
bool questdb_sql_init(void)
{
	quest_db = numdb_init();
	return true;
}

// ----------------------------------------------------------
// クエストデータ書き込み
// ----------------------------------------------------------
int questdb_sql_sync(void)
{
	// nothing to do
	return 0;
}

// ----------------------------------------------------------
// クエストデータ削除
// ----------------------------------------------------------
int questdb_sql_delete(int char_id)
{
	struct quest *q = (struct quest *)numdb_search(quest_db,char_id);

	if(q && q->char_id == char_id) {
		numdb_erase(quest_db,char_id);
		aFree(q);
	}
	sqldbs_query(&mysql_handle, "DELETE FROM `" QUEST_TABLE "` WHERE `char_id`='%d'", char_id);

	return 0;
}

// ----------------------------------------------------------
// キャラIDからクエストデータのインデックス取得
// ----------------------------------------------------------
const struct quest *questdb_sql_load(int char_id)
{
	int i=0;
	bool is_success;
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;
	struct quest *q = (struct quest *)numdb_search(quest_db,char_id);

	if(q && q->char_id == char_id) {
		// 既にキャッシュが存在する
		return q;
	}
	if(q == NULL) {
		q = (struct quest *)aMalloc(sizeof(struct quest));
		numdb_insert(quest_db,char_id,q);
	}
	memset(q, 0, sizeof(struct quest));

	q->char_id = char_id;

	is_success = sqldbs_query(
		&mysql_handle,
		"SELECT `account_id`, `nameid`, `state`, `limit`, "
				"`mobid1`, `mobmax1`, `mobcnt1`, "
				"`mobid2`, `mobmax2`, `mobcnt2`, "
				"`mobid3`, `mobmax3`, `mobcnt3` "
		"FROM `" QUEST_TABLE "` WHERE `char_id`='%d'",
		char_id
	);
	if(!is_success) {
		q->char_id = -1;
		return NULL;
	}
	sql_res = sqldbs_store_result(&mysql_handle);

	if(sql_res && sqldbs_num_rows(sql_res) > 0) {
		for(i=0; (sql_row = sqldbs_fetch(sql_res)) && i<MAX_QUESTLIST; i++) {
			if(q->account_id == 0) {
				q->account_id = atoi(sql_row[0]);
			}
			q->data[i].nameid     = atoi(sql_row[1]);
			q->data[i].state      = (char)atoi(sql_row[2]);
			q->data[i].limit      = (unsigned int)atoi(sql_row[3]);
			q->data[i].mob[0].id  = (short)atoi(sql_row[4]);
			q->data[i].mob[0].max = (short)atoi(sql_row[5]);
			q->data[i].mob[0].cnt = (short)atoi(sql_row[6]);
			q->data[i].mob[1].id  = (short)atoi(sql_row[7]);
			q->data[i].mob[1].max = (short)atoi(sql_row[8]);
			q->data[i].mob[1].cnt = (short)atoi(sql_row[9]);
			q->data[i].mob[2].id  = (short)atoi(sql_row[10]);
			q->data[i].mob[2].max = (short)atoi(sql_row[11]);
			q->data[i].mob[2].cnt = (short)atoi(sql_row[12]);
		}
		q->count = (i < MAX_QUESTLIST)? i: MAX_QUESTLIST;

		sqldbs_free_result(sql_res);
	} else {
		// 見つからなくても正常
		if(sql_res)
			sqldbs_free_result(sql_res);
		return NULL;
	}

	return q;
}

// ----------------------------------------------------------
// クエストデータ保存
// ----------------------------------------------------------
int questdb_sql_save(struct quest *q2)
{
	const struct quest *q1 = questdb_sql_load(q2->char_id);
	int i;

	if(q1 != NULL && q1->count <= 0) {
		if(q2->count <= 0)	// データが共に0個なので何もしない
			return 0;
	} else {
		// データサーバ側にデータがあるときだけ削除クエリを発行
		sqldbs_query(&mysql_handle, "DELETE FROM `" QUEST_TABLE "` WHERE `char_id`='%d'", q2->char_id);
	}

	for(i=0; i<q2->count; i++) {
		sqldbs_query(
			&mysql_handle,
			"INSERT INTO `" QUEST_TABLE "` (`char_id`, `account_id`, `nameid`, `state`, `limit`, "
											"`mobid1`, `mobmax1`, `mobcnt1`, "
											"`mobid2`, `mobmax2`, `mobcnt2`, "
											"`mobid3`, `mobmax3`, `mobcnt3`) "
			"VALUES ('%d','%d','%d','%d','%u', "
					 "'%d','%d','%d', "
					 "'%d','%d','%d', "
					 "'%d','%d','%d')",
			q2->char_id, q2->account_id, q2->data[i].nameid, q2->data[i].state, q2->data[i].limit,
			q2->data[i].mob[0].id, q2->data[i].mob[0].max, q2->data[i].mob[0].cnt,
			q2->data[i].mob[1].id, q2->data[i].mob[1].max, q2->data[i].mob[1].cnt,
			q2->data[i].mob[2].id, q2->data[i].mob[2].max, q2->data[i].mob[2].cnt
		);
	}

	{
		struct quest *q3 = (struct quest *)numdb_search(quest_db,q2->char_id);
		if(q3)
			memcpy(q3,q2,sizeof(struct quest));
	}

	return 0;
}

// ----------------------------------------------------------
// クエストデータ最終処理
// ----------------------------------------------------------
static int questdb_sql_final_sub(void *key, void *data, va_list ap)
{
	struct quest *q = (struct quest *)data;

	aFree(q);

	return 0;
}

void questdb_sql_final(void)
{
	if(quest_db)
		numdb_final(quest_db,questdb_sql_final_sub);
}

// ----------------------------------------------------------
// クエストデータ設定読み込み
// ----------------------------------------------------------
int questdb_sql_config_read_sub(const char *w1, const char *w2)
{
	return 0;
}
