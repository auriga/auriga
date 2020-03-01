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

#include "achievedb_sql.h"

static struct dbt *achieve_db = NULL;

/*==========================================
 * 設定ファイル読込
 *------------------------------------------
 */
int achievedb_sql_config_read_sub(const char *w1, const char *w2)
{
	return 0;
}

/*==========================================
 * 同期
 *------------------------------------------
 */
int achievedb_sql_sync(void)
{
	// nothing to do
	return 0;
}

/*==========================================
 * 実績データ削除
 *------------------------------------------
 */
bool achievedb_sql_delete(int char_id)
{
	struct achieve *a;

	if( sqldbs_query(&mysql_handle, "DELETE FROM `" ACHIEVE_TABLE "` WHERE `char_id`='%d'", char_id) == false )
		return false;

	a = (struct achieve *)numdb_search(achieve_db, char_id);

	if(a && a->char_id == char_id) {
		numdb_erase(achieve_db, char_id);
		aFree(a);
	}
	return true;
}

/*==========================================
 * キャラIDから実績データを取得
 *------------------------------------------
 */
const struct achieve *achievedb_sql_load(int char_id)
{
	bool result = false;
	struct achieve *a = (struct achieve *)numdb_search(achieve_db, char_id);

	if(a && a->char_id == char_id) {
		// 既にキャッシュが存在する
		return a;
	}
	if(a == NULL) {
		a = (struct achieve *)aMalloc(sizeof(struct achieve));
		numdb_insert(achieve_db, char_id, a);
	}
	memset(a, 0, sizeof(struct achieve));

	a->char_id = char_id;

	result = sqldbs_query(&mysql_handle,
		"SELECT `account_id`, `nameid`, "
		"`count1`, `count2`, `count3`, `count4`, `count5`, `count6`, `count7`, `count8`, `count9`, `count10`, `comp_date`, `reward` "
		"FROM `" ACHIEVE_TABLE "` WHERE `char_id`='%d'", char_id
	);
	if(result == false) {
		a->char_id = -1;
		return NULL;
	}

	if(sqldbs_num_rows(&mysql_handle) > 0) {
		int i;
		char **sql_row;

		for(i = 0; (sql_row = sqldbs_fetch(&mysql_handle)) && i < MAX_ACHIEVELIST; i++) {
			if(a->account_id == 0) {
				a->account_id = atoi(sql_row[0]);
			}
			a->data[i].nameid    = atoi(sql_row[1]);
			a->data[i].count[0]  = atoi(sql_row[2]);
			a->data[i].count[1]  = atoi(sql_row[3]);
			a->data[i].count[2]  = atoi(sql_row[4]);
			a->data[i].count[3]  = atoi(sql_row[5]);
			a->data[i].count[4]  = atoi(sql_row[6]);
			a->data[i].count[5]  = atoi(sql_row[7]);
			a->data[i].count[6]  = atoi(sql_row[8]);
			a->data[i].count[7]  = atoi(sql_row[9]);
			a->data[i].count[8]  = atoi(sql_row[10]);
			a->data[i].count[9]  = atoi(sql_row[11]);
			a->data[i].comp_date = (unsigned int)atoi(sql_row[12]);
			a->data[i].reward    = (char)atoi(sql_row[13]);
		}
		a->count = (i < MAX_ACHIEVELIST)? i: MAX_ACHIEVELIST;
	} else {
		// 見つからなくても正常
		a = NULL;
	}
	sqldbs_free_result(&mysql_handle);

	return a;
}

/*==========================================
 * 実績データをセーブ
 *------------------------------------------
 */
bool achievedb_sql_save(struct achieve *a2)
{
	const struct achieve *a1;
	bool result = false;

	nullpo_retr(false, a2);

	a1 = achievedb_sql_load(a2->char_id);

	if(a1 && a1->count <= 0 && a2->count <= 0) {
		// データが共に0個なので何もしない
		return true;
	}

	if( sqldbs_transaction_start(&mysql_handle) == false )
		return false;

	// try
	do {
		int i;

		if(a1 == NULL || a1->count > 0) {
			// データサーバ側にデータがあるときだけ削除クエリを発行
			if( sqldbs_query(&mysql_handle, "DELETE FROM `" ACHIEVE_TABLE "` WHERE `char_id`='%d'", a2->char_id) == false )
				break;
		}

		for(i = 0; i < a2->count; i++) {
			if( sqldbs_query(&mysql_handle,
				"INSERT INTO `" ACHIEVE_TABLE "` (`char_id`, `account_id`, `nameid`, "
				"`count1`, `count2`, `count3`, `count4`, `count5`, `count6`, `count7`, `count8`, `count9`, `count10`, "
				"`comp_date`, `reward`) "
				"VALUES ('%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%u','%d')",
				a2->char_id, a2->account_id, a2->data[i].nameid,
				a2->data[i].count[0], a2->data[i].count[1], a2->data[i].count[2], 
				a2->data[i].count[3], a2->data[i].count[4], a2->data[i].count[5], 
				a2->data[i].count[6], a2->data[i].count[7], a2->data[i].count[8], a2->data[i].count[9], 
				a2->data[i].comp_date, a2->data[i].reward
			) == false )
				break;
		}
		if(i != a2->count)
			break;

		// success
		result = true;

		{
			// cache copy
			struct achieve *a3 = (struct achieve *)numdb_search(achieve_db, a2->char_id);
			if(a3)
				memcpy(a3, a2, sizeof(struct achieve));
		}
	} while(0);

	sqldbs_transaction_end(&mysql_handle, result);

	return result;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
static int achievedb_sql_final_sub(void *key, void *data, va_list ap)
{
	struct achieve *a = (struct achieve *)data;

	aFree(a);

	return 0;
}

void achievedb_sql_final(void)
{
	if(achieve_db)
		numdb_final(achieve_db, achievedb_sql_final_sub);
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
bool achievedb_sql_init(void)
{
	achieve_db = numdb_init();
	return true;
}
