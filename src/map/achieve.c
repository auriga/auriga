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
#include <time.h>

#include "db.h"
#include "timer.h"
#include "socket.h"
#include "nullpo.h"
#include "malloc.h"
#include "utils.h"
#include "mmo.h"

#include "achieve.h"
#include "map.h"
#include "clif.h"
#include "intif.h"

#define MAX_ACHIEVE_LEVEL 20
#define ACHIEVE_EXPANDDB_SIZE 16

/* 実績データベース */
struct achieve_db achieve_db[MAX_ACHIEVE_DB];

/* 実績EXPテーブルデータベース */
static int achieve_exp_table[MAX_ACHIEVE_LEVEL];

/* 討伐対象データベース */
static int *achieve_killdb = NULL;
static int max_killdb_count = 0;
static int insert_killdb_size = 0;

/* 使用対象データベース */
static int *achieve_usedb = NULL;
static int max_usedb_count = 0;
static int insert_usedb_size = 0;

static int achieve_count;

/*==========================================
 * 実績DBのデータを検索
 *------------------------------------------
 */
static int achieve_search_db(int id)
{
	int i;

	for(i = 0; i < achieve_count; i++) {
		if(achieve_db[i].nameid == id)
			return i;
	}

	return -1;
}

/*==========================================
 *
 *------------------------------------------
 */
static int achieve_search_id_sub(const void *a, const void *b)
{
	int key   = *(int *)a;
	int value = *(int *)b;

	return (key > value)? 1: (key < value)? -1: 0;
}

/*==========================================
 * 討伐対象かチェック
 *------------------------------------------
 */
int achieve_search_mobid(int mob_id)
{
	int *ret;

	if(achieve_killdb == NULL)
		return 0;

	ret = bsearch(&mob_id, achieve_killdb, max_killdb_count, sizeof(int), achieve_search_id_sub);

	return (ret)? 1: 0;
}

/*==========================================
 * 使用対象かチェック
 *------------------------------------------
 */
int achieve_search_itemid(int item_id)
{
	int *ret;

	if(achieve_usedb == NULL)
		return 0;

	ret = bsearch(&item_id, achieve_usedb, max_usedb_count, sizeof(int), achieve_search_id_sub);

	return (ret)? 1: 0;
}

/*==========================================
 * 実績スコア計算
 *------------------------------------------
 */
int achieve_calc_level(struct map_session_data *sd, int score)
{
	int i, idx, p = 0;
	int level = 1;

	nullpo_retr(0, sd);

	if(score < 0) {
		for(i = 0; i < sd->achievelist; i++) {
			if(sd->achieve[i].comp_date > 0)
				continue;
			idx = achieve_search_db(sd->achieve[i].nameid);
			if(idx >= 0)
				p += achieve_db[idx].score;
		}
	}
	else
		p = score;

	sd->as.score = p;

	for(i = 0; i < MAX_ACHIEVE_LEVEL; i++) {
		if(p < achieve_exp_table[i] || achieve_exp_table[i] == 0)
			break;
		p -= achieve_exp_table[i];
		level++;
	}

	sd->as.level   = level;
	sd->as.current = p;
	sd->as.next    = achieve_exp_table[i];

	return 0;
}

/*==========================================
 * 実績レベルチェック
 *------------------------------------------
 */
static int achieve_check_level(struct map_session_data *sd, int achieve_id)
{
	nullpo_retr(0, sd);

	achieve_calc_level(sd, -1);

	if(sd->as.current + achieve_db[achieve_id].score >= sd->as.next) {
		achieve_update_content(sd, ACH_ACHIEVE_RANK, sd->as.level+1, 1);
	}
	return 0;
}

/*==========================================
 * 実績完了チェック
 *------------------------------------------
 */
static int achieve_check_complete(struct map_session_data *sd, int achieve_id, int idx)
{
	int i;
	bool flag = true;

	nullpo_retr(0, sd);

	for(i = 0; i < achieve_db[achieve_id].num; i++) {
		if(achieve_db[achieve_id].content[i].count && sd->achieve[idx].count[i] < achieve_db[achieve_id].content[i].count) {
			flag = false;
			break;
		}
	}
	// コンプリートした
	if(flag) {
		achieve_check_level(sd, achieve_id);
		sd->achieve[idx].comp_date = (unsigned int)time(NULL);
		achieve_update_content(sd, ACH_ACHIEVE, sd->achieve[idx].nameid, 1);
	}
	intif_save_achieve(sd);
	return 0;
}

/*==========================================
 * 実績アップデート
 *------------------------------------------
 */
int achieve_update_content(struct map_session_data *sd, enum achieve_types type, int id, int num)
{
	int i, j, k, update_count[MAX_ACHIEVE_CONTENT];
	int flag = 0;
	bool ischange;

	nullpo_retr(0, sd);

	switch(type) {
	// key value 系
	case ACH_LEVEL:
	case ACH_STATUS:
	case ACH_ADD_FRIEND:
	case ACH_PET_FRIEND:
	case ACH_SPEND_ZENY:
	case ACH_GET_ZENY:
		flag |= 1;		// 固定値更新フラグ
		// fall through
	case ACH_KILL_MOB:
	case ACH_USE_ITEM:
	case ACH_QUEST:
	case ACH_ACHIEVE:
	case ACH_ACHIEVE_RANK:
	case ACH_ADVENTURE:
	case ACH_TAMING:
	case ACH_JOBCHANGE:
		for(i = 0; i < achieve_count; i++) {
			if(achieve_db[i].type != type)
				continue;

			memset(&update_count, 0, sizeof(update_count));
			ischange = false;

			for(j = 0; j < achieve_db[i].num; j++) {
				// 同じIDを更新する
				if(achieve_db[i].content[j].id == id) {
					update_count[j] += num;
					ischange = true;
				}
			}
			if(ischange) {
				for(k = 0; k < sd->achievelist; k++) {
					if(sd->achieve[k].nameid == achieve_db[i].nameid) {
						// 既に記録済みのID
						if(sd->achieve[k].comp_date > 0)		// クリア済み
							break;
						for(j = 0; j < achieve_db[i].num; j++) {
							if(sd->achieve[k].count[j] < achieve_db[i].content[j].id)
								if(flag & 1)	// 固定値で更新させる
									sd->achieve[k].count[j] = update_count[j];
								else
									sd->achieve[k].count[j] += update_count[j];
						}
						break;
					}
				}
				if(k == sd->achievelist && sd->achievelist < MAX_ACHIEVELIST) {
					// 検索したけどなかったら新規に追加
					sd->achieve[k].nameid = achieve_db[i].nameid;
					for(j = 0; j < achieve_db[i].num; j++)
						sd->achieve[k].count[j] += update_count[j];
					sd->achievelist++;
				}
				if(sd->achieve[k].comp_date == 0) {
					achieve_check_complete(sd, i, k);
					clif_send_achievement_update(sd, &sd->achieve[k]);
				}
			}
		}	// for(achieve_count) end
	}
	return 0;
}

/*==========================================
 * 報酬受け取りチェック
 *------------------------------------------
 */
int achieve_check_reward(struct map_session_data *sd, int achieve_id)
{
	int i, idx;

	nullpo_retr(1, sd);

	for(i = 0; i < sd->achievelist; i++) {
		if(sd->achieve[i].nameid != achieve_id)
			continue;
		if(sd->achieve[i].comp_date == 0)
			return 1;
		if(sd->achieve[i].reward > 0)
			return 1;

		sd->achieve[i].reward = 1;
		intif_save_achieve(sd);
		clif_send_achievement_update(sd, &sd->achieve[i]);

		idx = achieve_search_db(sd->achieve[i].nameid);
		if(idx >= 0 && achieve_db[idx].reward) {
			run_script(achieve_db[idx].reward,0,sd->bl.id,0);
		}
		return 0;
	}
	return 1;
}

/*==========================================
 * 称号変更チェック
 *------------------------------------------
 */
int achieve_check_title(struct map_session_data *sd, int title_id)
{
	int i, idx;

	nullpo_retr(1, sd);

	for(i = 0; i < sd->achievelist; i++) {
		if(sd->achieve[i].comp_date == 0)
			continue;
		if(sd->achieve[i].reward == 0)
			continue;
		idx = achieve_search_db(sd->achieve[i].nameid);
		if(idx < 0)
			continue;
		if(achieve_db[idx].title != title_id)
			continue;
		sd->status.title_id = title_id;
		return 0;
	}
	return 1;
}

/*==========================================
 * 実績討伐/使用データベースのソート
 *------------------------------------------
 */
static int achieve_sort_id(const void *_i1, const void *_i2)
{
	int i1 = *((int *)_i1);
	int i2 = *((int *)_i2);

	return (i1 > i2)? 1 : (i1 < i2)? -1 : 0;
}

/*==========================================
 * 実績DBの基礎登録
 *------------------------------------------
 */
bool achieve_insert_info(int achieveid, const char* name, enum achieve_types type, int score, int title, const char* reward)
{
	int i;
	char *p;
	struct script_code *script = NULL;

	if(achieveid < 0)
		return false;

	for(i = 0; i < achieve_count; i++) {
		if(achieve_db[i].nameid == achieveid || achieve_db[i].nameid == 0)
			break;
	}

	if(i == MAX_ACHIEVE_DB) {
		printf("\rachieve_insert_info: list over id: %d.\n", achieveid);
		return false;
	}

	if((p = strchr(reward, '{')) == NULL)
		return false;

	if(!parse_script_line_end(p, "db/achievement_db.lua", 1))
		return false;

	if(achieve_db[i].nameid == 0)
		achieve_count++;

	achieve_db[i].nameid = achieveid;
	strncpy(achieve_db[i].name,name,24);
	achieve_db[i].type = type;
	achieve_db[i].score = score;
	achieve_db[i].title = title;

	if(achieve_db[i].reward) {
		script_free_code(achieve_db[i].reward);
	}
	script = parse_script(p, "db/achievement_db.lua", 1);
	achieve_db[i].reward = (script_is_error(script))? NULL: script;

	printf("\rread db/achievement_db.lua done (count=%d)", achieve_count);
	return true;
}

/*==========================================
 * 実績DBのコンテンツ登録
 *------------------------------------------
 */
bool achieve_insert_content(int achieveid, int nameid, int count)
{
	int i;

	if(achieveid < 0)
		return false;

	for(i = 0; i < achieve_count; i++) {
		if(achieve_db[i].nameid == achieveid || achieve_db[i].nameid == 0)
			break;
	}

	if(i == MAX_ACHIEVE_DB) {
		printf("\rachieve_insert_content: list over id: %d.\n", achieveid);
		return false;
	}

	if(achieve_db[i].num == MAX_ACHIEVE_CONTENT) {
		printf("\rachieve_insert_content: list over id=%d, ID=%d\n", achieveid, nameid);
		return false;
	}

	if(achieve_db[i].nameid == 0)
		achieve_count++;

	achieve_db[i].nameid = achieveid;
	achieve_db[i].content[achieve_db[i].num].id = nameid;
	achieve_db[i].content[achieve_db[i].num].count = (count>1? count: 1);
	achieve_db[i].num++;

	if(nameid > 0) {
		int n;
		if(achieve_db[i].type == ACH_KILL_MOB) {
			for(n = 0; n < max_killdb_count; n++) {
				if(achieve_killdb[n] == nameid)
					break;
			}
			if(n == max_killdb_count) {
				// 新しく出現したMobIDなので討伐データベースに追加
				if(n >= insert_killdb_size) {
					insert_killdb_size += ACHIEVE_EXPANDDB_SIZE;
					achieve_killdb = (int *)aRealloc(achieve_killdb, sizeof(int) * insert_killdb_size);
					memset(achieve_killdb + (insert_killdb_size - ACHIEVE_EXPANDDB_SIZE), 0, sizeof(int) * ACHIEVE_EXPANDDB_SIZE);
				}
				achieve_killdb[n] = nameid;
				max_killdb_count++;
			}
		}
		else if(achieve_db[i].type == ACH_USE_ITEM) {
			for(n = 0; n < max_usedb_count; n++) {
				if(achieve_usedb[n] == nameid)
					break;
			}
			if(n == max_usedb_count) {
				// 新しく出現したItemIDなので使用データベースに追加
				if(n >= insert_usedb_size) {
					insert_usedb_size += ACHIEVE_EXPANDDB_SIZE;
					achieve_usedb = (int *)aRealloc(achieve_usedb, sizeof(int) * insert_usedb_size);
					memset(achieve_usedb + (insert_usedb_size - ACHIEVE_EXPANDDB_SIZE), 0, sizeof(int) * ACHIEVE_EXPANDDB_SIZE);
				}
				achieve_usedb[n] = nameid;
				max_usedb_count++;
			}
		}
	}

	printf("\rread db/achievement_db.lua done (count=%d)", achieve_count);
	return true;
}

/*==========================================
 * 実績DBのコンテンツ登録終了
 *------------------------------------------
 */
bool achieve_insert_db_end(void)
{
	// 討伐データベースのリサイズ
	achieve_killdb = (int *)aRealloc(achieve_killdb, sizeof(int) * max_killdb_count);
	// 討伐データベースのソート
	qsort(achieve_killdb, max_killdb_count, sizeof(int), achieve_sort_id);

	// 使用データベースのリサイズ
	achieve_usedb = (int *)aRealloc(achieve_usedb, sizeof(int) * max_usedb_count);
	// 使用データベースのソート
	qsort(achieve_usedb, max_usedb_count, sizeof(int), achieve_sort_id);

	return true;
}

/*==========================================
 * 実績DBの必要経験値登録
 *------------------------------------------
 */
bool achieve_insert_leveldb(int lv, int exp)
{
	if(lv < 1 || lv > MAX_ACHIEVE_LEVEL || exp < 1) {
		printf("\rachieve_insert_leveldb: list over lv: %d.\n", lv);
		return false;
	}

	achieve_exp_table[lv-1] = exp;

	printf("\rread db/achievement_level_db.lua done");
	return true;
}

/*==========================================
 * 実績初期化処理
 *------------------------------------------
 */
int do_init_achieve(void)
{
	memset(&achieve_db, 0, sizeof(achieve_db));
	memset(achieve_exp_table, 0, sizeof(achieve_exp_table));
	achieve_count = 0;

	return 0;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
int do_final_achieve(void)
{
	int i;

	if(achieve_killdb) {
		aFree(achieve_killdb);
		achieve_killdb = NULL;
		max_killdb_count = 0;
	}
	if(achieve_usedb) {
		aFree(achieve_usedb);
		achieve_usedb = NULL;
		max_usedb_count = 0;
	}
	for(i = 0; i < achieve_count; i++) {
		if(achieve_db[i].reward) {
			script_free_code(achieve_db[i].reward);
		}
	}
	return 0;
}
