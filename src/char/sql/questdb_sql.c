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

#include "questdb_sql.h"

static struct dbt *quest_db = NULL;

/*==========================================
 * 設定ファイル読込
 *------------------------------------------
 */
int questdb_sql_config_read_sub(const char *w1, const char *w2)
{
	return 0;
}

/*==========================================
 * 同期
 *------------------------------------------
 */
int questdb_sql_sync(void)
{
	// nothing to do
	return 0;
}

/*==========================================
 * クエストデータ削除
 *------------------------------------------
 */
bool questdb_sql_delete(int char_id)
{
	struct quest *q;

	if( sqldbs_query(&mysql_handle, "DELETE FROM `" QUEST_TABLE "` WHERE `char_id`='%d'", char_id) == false )
		return false;

	q = (struct quest *)numdb_search(quest_db, char_id);

	if(q && q->char_id == char_id) {
		numdb_erase(quest_db, char_id);
		aFree(q);
	}
	return true;
}

/*==========================================
 * キャラIDからクエストデータを取得
 *------------------------------------------
 */
const struct quest *questdb_sql_load(int char_id)
{
	bool result = false;
	struct quest *q = (struct quest *)numdb_search(quest_db, char_id);

	if(q && q->char_id == char_id) {
		// 既にキャッシュが存在する
		return q;
	}
	if(q == NULL) {
		q = (struct quest *)aMalloc(sizeof(struct quest));
		numdb_insert(quest_db, char_id, q);
	}
	memset(q, 0, sizeof(struct quest));

	q->char_id = char_id;

	result = sqldbs_query(&mysql_handle,
		"SELECT `account_id`,`nameid`,`state`,`limit`,`mobid1`,`mobmax1`,`mobcnt1`,`mobid2`,`mobmax2`,`mobcnt2`,`mobid3`,`mobmax3`,`mobcnt3` "
		"FROM `" QUEST_TABLE "` WHERE `char_id`='%d'", char_id
	);
	if(result == false) {
		q->char_id = -1;
		return NULL;
	}

	if(sqldbs_num_rows(&mysql_handle) > 0) {
		int i;
		char **sql_row;

		for(i = 0; (sql_row = sqldbs_fetch(&mysql_handle)) && i < MAX_QUESTLIST; i++) {
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
	} else {
		// 見つからなくても正常
		q = NULL;
	}
	sqldbs_free_result(&mysql_handle);

	return q;
}

/*==========================================
 * セーブ
 *------------------------------------------
 */
bool questdb_sql_save(struct quest *q2)
{
	const struct quest *q1;
	bool result = false;

	nullpo_retr(false, q2);

	q1 = questdb_sql_load(q2->char_id);

	if(q1 && q1->count <= 0 && q2->count <= 0) {
		// データが共に0個なので何もしない
		return true;
	}

	if( sqldbs_transaction_start(&mysql_handle) == false )
		return false;

	// try
	do {
		int i;

		if(q1 == NULL || q1->count > 0) {
			// データサーバ側にデータがあるときだけ削除クエリを発行
			if( sqldbs_query(&mysql_handle, "DELETE FROM `" QUEST_TABLE "` WHERE `char_id`='%d'", q2->char_id) == false )
				break;
		}

		for(i = 0; i < q2->count; i++) {
			if( sqldbs_query(&mysql_handle,
				"INSERT INTO `" QUEST_TABLE "` (`char_id`, `account_id`, `nameid`, `state`, `limit`, `mobid1`, `mobmax1`, `mobcnt1`, "
				"`mobid2`, `mobmax2`, `mobcnt2`, `mobid3`, `mobmax3`, `mobcnt3`) "
				"VALUES ('%d','%d','%d','%d','%u','%d','%d','%d','%d','%d','%d','%d','%d','%d')",
				q2->char_id, q2->account_id, q2->data[i].nameid, q2->data[i].state, q2->data[i].limit,
				q2->data[i].mob[0].id, q2->data[i].mob[0].max, q2->data[i].mob[0].cnt,
				q2->data[i].mob[1].id, q2->data[i].mob[1].max, q2->data[i].mob[1].cnt,
				q2->data[i].mob[2].id, q2->data[i].mob[2].max, q2->data[i].mob[2].cnt
			) == false )
				break;
		}
		if(i != q2->count)
			break;

		// success
		result = true;

		{
			// cache copy
			struct quest *q3 = (struct quest *)numdb_search(quest_db, q2->char_id);
			if(q3)
				memcpy(q3, q2, sizeof(struct quest));
		}
	} while(0);

	sqldbs_transaction_end(&mysql_handle, result);

	return result;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
static int questdb_sql_final_sub(void *key, void *data, va_list ap)
{
	struct quest *q = (struct quest *)data;

	aFree(q);

	return 0;
}

void questdb_sql_final(void)
{
	if(quest_db)
		numdb_final(quest_db, questdb_sql_final_sub);
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
bool questdb_sql_init(void)
{
	quest_db = numdb_init();
	return true;
}
