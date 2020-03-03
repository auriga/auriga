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

#include "nullpo.h"
#include "malloc.h"

#include "map.h"
#include "quest.h"
#include "clif.h"
#include "chrif.h"
#include "intif.h"
#include "pc.h"
#include "achieve.h"

#define QUEST_KILLDB_SIZE 64

/* クエストデータベース */
static struct quest_db quest_db[MAX_QUEST_DB];

/* 討伐対象データベース */
static int *quest_killdb = NULL;
static int max_killdb_count = 0;

/*==========================================
 * クエストDBのデータを検索
 *------------------------------------------
 */
static int quest_search_db(int quest_id)
{
	int i;

	for(i = 0; i < MAX_QUEST_DB; i++) {
		if(quest_db[i].nameid == quest_id)
			return i;
	}

	return -1;
}

/*==========================================
 * クエストIDからインデックスを返す
 *------------------------------------------
 */
static int quest_search_index(struct map_session_data *sd, int quest_id)
{
	int i;

	nullpo_retr(-1, sd);

	for(i = 0; i < sd->questlist; i++) {
		if(sd->quest[i].nameid == quest_id)
			return i;
	}

	return -1;
}

/*==========================================
 * クエストIDから構造体を返す
 *------------------------------------------
 */
struct quest_data *quest_get_data(struct map_session_data *sd, int quest_id)
{
	int idx = quest_search_index(sd, quest_id);

	if(idx >= 0)
		return &sd->quest[idx];

	return NULL;
}

/*==========================================
 * 討伐対象かチェック
 *------------------------------------------
 */
static int quest_search_mobid_sub(const void *a, const void *b)
{
	int key   = *(int *)a;
	int value = *(int *)b;

	return (key > value)? 1: (key < value)? -1: 0;
}

int quest_search_mobid(int mob_id)
{
	int *ret;

	if(quest_killdb == NULL)
		return 0;

	ret = bsearch(&mob_id, quest_killdb, max_killdb_count, sizeof(int), quest_search_mobid_sub);

	return (ret)? 1: 0;
}

/*==========================================
 * クエストリスト追加
 *------------------------------------------
 */
int quest_addlist(struct map_session_data *sd, int quest_id)
{
	struct quest_data qd;
	int i, qid, idx;

	nullpo_retr(1, sd);

	qid = quest_search_db(quest_id);
	if(qid < 0)
		return 1;

	memset(&qd, 0, sizeof(struct quest_data));
	qd.nameid = quest_db[qid].nameid;
	if(quest_db[qid].limit) {
		if(quest_db[qid].limit_type == 0)
			qd.limit = (unsigned int)time(NULL) + quest_db[qid].limit;
		else {
			int time_today;
			time_t t;
			struct tm * lt;
			int next;

			t = time(NULL);
			lt = localtime(&t);
			if(quest_db[qid].limit_type == 1) {
				time_today = (lt->tm_hour) * 3600 + (lt->tm_min) * 60 + (lt->tm_sec);
				next = 86400;
			}
			else {
				time_today = (lt->tm_wday) * 86400 + (lt->tm_hour) * 3600 + (lt->tm_min) * 60 + (lt->tm_sec);
				next = 604800;
			}
			if(time_today < (int)((quest_db[qid].limit)%next))
				qd.limit = (unsigned int)(time(NULL) + quest_db[qid].limit - time_today);
			else
				qd.limit = (unsigned int)(time(NULL) + next + quest_db[qid].limit - time_today);
		}
	}
	for(i = 0; i < sizeof(qd.mob)/sizeof(qd.mob[0]); i++) {
		qd.mob[i].id  = quest_db[qid].mob[i].id;
		qd.mob[i].max = quest_db[qid].mob[i].count;
	}
	qd.state = 1;

	// 既にクエストを取得してるか検索
	if((idx = quest_search_index(sd, quest_id)) >= 0) {
		// 既にクエストリストにある場合は更新する
		memcpy(&sd->quest[idx], &qd, sizeof(struct quest_data));
	} else {
		if(sd->questlist >= MAX_QUESTLIST) {
			// 容量オーバー
			return 1;
		}
		memcpy(&sd->quest[sd->questlist], &qd, sizeof(struct quest_data));
		sd->questlist++;
	}
	achieve_update_content(sd, ACH_QUEST, qd.nameid, 1);

	clif_add_questlist(sd, quest_id);
#if PACKETVER >= 20150513
	clif_update_questcount2(sd, quest_id);
#else
	clif_update_questcount(sd, quest_id);
#endif
	intif_save_quest(sd);

	return 0;
}

/*==========================================
 * クエストリスト更新
 *------------------------------------------
 */
int quest_updatelist(struct map_session_data *sd, int old_id, int new_id)
{
	struct quest_data qd;
	int i, qid, old_idx, new_idx;

	nullpo_retr(1, sd);

	qid = quest_search_db(new_id);
	if(qid < 0)
		return 1;

	// クエストを取得してるか検索
	old_idx = quest_search_index(sd, old_id);
	new_idx = quest_search_index(sd, new_id);

	if(old_idx >= 0) {
		if(new_idx >= 0) {
			// 新クエストが既にクエストリストにある場合は旧クエストを削除するだけ
			quest_dellist(sd, old_id);
			return 0;
		}
	} else {
		if(new_idx >= 0) {
			// 新クエストが既にクエストリストにある場合は何もしない
			return 0;
		}
		if(sd->questlist >= MAX_QUESTLIST) {
			// 容量オーバー
			return 1;
		}
	}

	memset(&qd, 0, sizeof(struct quest_data));
	qd.nameid = quest_db[qid].nameid;
	if(quest_db[qid].limit) {
		if(quest_db[qid].limit_type == 0)
			qd.limit = (unsigned int)time(NULL) + quest_db[qid].limit;
		else {
			int time_today;
			time_t t;
			struct tm * lt;
			int next;

			t = time(NULL);
			lt = localtime(&t);
			if(quest_db[qid].limit_type == 1) {
				time_today = (lt->tm_hour) * 3600 + (lt->tm_min) * 60 + (lt->tm_sec);
				next = 86400;
			}
			else {
				time_today = (lt->tm_wday) * 86400 + (lt->tm_hour) * 3600 + (lt->tm_min) * 60 + (lt->tm_sec);
				next = 604800;
			}
			if(time_today < (int)((quest_db[qid].limit)%next))
				qd.limit = (unsigned int)(time(NULL) + quest_db[qid].limit - time_today);
			else
				qd.limit = (unsigned int)(time(NULL) + next + quest_db[qid].limit - time_today);
		}
	}
	for(i = 0; i < sizeof(qd.mob)/sizeof(qd.mob[0]); i++) {
		qd.mob[i].id  = quest_db[qid].mob[i].id;
		qd.mob[i].max = quest_db[qid].mob[i].count;
	}
	qd.state = 1;

	if(old_idx >= 0) {
		// 旧クエストを取得してる場合は上書きで更新する
		memcpy(&sd->quest[old_idx], &qd, sizeof(struct quest_data));
		clif_del_questlist(sd, old_id);
	} else {
		memcpy(&sd->quest[sd->questlist], &qd, sizeof(struct quest_data));
		sd->questlist++;
	}
	achieve_update_content(sd, ACH_QUEST, qd.nameid, 1);

	clif_add_questlist(sd, new_id);
#if PACKETVER >= 20150513
	clif_update_questcount2(sd, new_id);
#else
	clif_update_questcount(sd, new_id);
#endif
	intif_save_quest(sd);

	return 0;
}

/*==========================================
 * クエストリスト削除
 *------------------------------------------
 */
int quest_dellist(struct map_session_data *sd, int quest_id)
{
	int idx;

	nullpo_retr(1, sd);

	idx = quest_search_index(sd, quest_id);
	if(idx >= MAX_QUESTLIST || idx < 0)
		return 1;

	sd->questlist--;
	memmove(&sd->quest[idx],&sd->quest[idx+1],sizeof(struct quest_data) * (sd->questlist - idx));
	memset(&sd->quest[sd->questlist], 0, sizeof(struct quest_data));

	clif_del_questlist(sd, quest_id);
	intif_save_quest(sd);

	return 0;
}

/*==========================================
 * クエストリスト状態変更
 *------------------------------------------
 */
int quest_update_status(struct map_session_data *sd, int quest_id, char state)
{
	int idx;

	nullpo_retr(1, sd);

	idx = quest_search_index(sd, quest_id);
	if(idx < 0 || idx > sd->questlist)
		return -1;

	sd->quest[idx].state = state;

	if(state < 2)
		return state;

	clif_del_questlist(sd, quest_id);
	intif_save_quest(sd);

	return 0;
}

int quest_killcount_sub(struct block_list *tbl, va_list ap)
{
	struct map_session_data *sd;
	int mob_id, party_id;

	nullpo_retr(0, tbl);
	nullpo_retr(0, sd = (struct map_session_data *)tbl);

	party_id = va_arg(ap,int);
	mob_id = va_arg(ap,int);

	if(!sd->questlist)
		return 0;
	if(sd->status.party_id != party_id)
		return 0;

	quest_killcount(sd, mob_id);

	return 1;
}

/*==========================================
 * クエストリスト討伐数更新
 *------------------------------------------
 */
int quest_killcount(struct map_session_data *sd, int mob_id)
{
	struct quest_data *qd;
	int i, j;

	nullpo_retr(1, sd);

	for(i = 0; i < sd->questlist; i++) {
		qd = &sd->quest[i];
		if(qd->nameid > 0) {
			int qid;
			for(j = 0; j < sizeof(qd->mob)/sizeof(qd->mob[0]); j++) {
				if(qd->mob[j].id == mob_id && qd->mob[j].count < qd->mob[j].max) {
					qd->mob[j].count++;
					clif_update_questcount(sd, qd->nameid);
				}
			}
			qid = quest_search_db(qd->nameid);   // qid取得
			if(qid < 0)      // qidがみつからなかったのでここまで
				continue;

			for(j = 0; j < sizeof(quest_db[qid].drop)/sizeof(quest_db[qid].drop[0]); j++) {
				if(quest_db[qid].drop[j].id != mob_id)
					continue;
				if(atn_rand()%10000 < quest_db[qid].drop[j].p) {
					int flag;
					struct item tmp_item;

					memset(&tmp_item, 0, sizeof(tmp_item));
					tmp_item.nameid = quest_db[qid].drop[j].nameid;
					tmp_item.amount = 1;
					tmp_item.identify = 1;
					if((flag = pc_additem(sd, &tmp_item, tmp_item.amount))) {
						clif_additem(sd, 0, 0, flag);
					}
				}
			}
		}
	}

	return 0;
}

/*==========================================
 * 討伐データベースのソート
 *------------------------------------------
 */
static int quest_sort_id(const void *_i1, const void *_i2)
{
	int i1 = *((int *)_i1);
	int i2 = *((int *)_i2);

	return (i1 > i2)? 1 : (i1 < i2)? -1 : 0;
}

/*==========================================
 * クエスト設定ファイル読み込み
 * quest_db.txt クエストデータ
 *------------------------------------------
 */
static int quest_readdb(void)
{
	int i, j, size = 0;
	FILE *fp;
	char line[1024],*p;
	const char *filename = "db/quest_db.txt";

	memset(&quest_db, 0, sizeof(quest_db));

	if(quest_killdb) {
		aFree(quest_killdb);
		quest_killdb = NULL;
		max_killdb_count = 0;
	}

	fp = fopen(filename, "r");
	if(fp == NULL) {
		printf("quest_readdb: open [%s] failed !\n", filename);
		return 1;
	}

	i=0;
	while(fgets(line,1020,fp)){
		char *split[18];
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0]=='/' && line[1]=='/')
			continue;
		memset(split,0,sizeof(split));
		for(j=0,p=line;j<18 && p;j++){
			split[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		if(j < 18)
			continue;
		if(i < 0 || i >= MAX_QUEST_DB)
			continue;

		quest_db[i].nameid = atoi(split[0]);

		if(strchr(split[2],':') == NULL) {
			quest_db[i].limit = atoi(split[2]);
			quest_db[i].limit_type = 0;
		}
		else {
			int week, day, hour, min;

			if(sscanf(split[2], "%d:%d:%d:%d", &week, &day, &hour, &min) == 4) {
				quest_db[i].limit = day * 604800 + week * 86400 + hour * 3600 + min * 60;
				quest_db[i].limit_type = 2;
			}
			else if(sscanf(split[2], "%d:%d:%d", &day, &hour, &min) == 3) {
				quest_db[i].limit = day * 86400 + hour * 3600 + min * 60;
				quest_db[i].limit_type = 1;
			}
			else if(sscanf(split[2], "%d:%d", &hour, &min) == 2) {
				quest_db[i].limit = hour * 3600 + min * 60;
				quest_db[i].limit_type = 1;
			}
		}

		for(j = 0; j < sizeof(quest_db[0].mob)/sizeof(quest_db[0].mob[0]); j++) {
			int mob_id = atoi(split[3+j*2]);
			quest_db[i].mob[j].id    = (short)mob_id;
			quest_db[i].mob[j].count = (short)atoi(split[4+j*2]);

			if(mob_id > 0) {
				int n;
				for(n = 0; n < max_killdb_count; n++) {
					if(quest_killdb[n] == mob_id)
						break;
				}
				if(n != max_killdb_count)
					continue;

				// 新しく出現したMobIDなので討伐データベースに追加
				if(n >= size) {
					size += QUEST_KILLDB_SIZE;
					quest_killdb = (int *)aRealloc(quest_killdb, sizeof(int) * size);
					memset(quest_killdb + (size - QUEST_KILLDB_SIZE), 0, sizeof(int) * QUEST_KILLDB_SIZE);
				}
				quest_killdb[n] = mob_id;
				max_killdb_count++;
			}
		}
		for(j = 0; j < sizeof(quest_db[0].drop)/sizeof(quest_db[0].drop[0]); j++) {
			int mob_id = atoi(split[9+j*3]);
			quest_db[i].drop[j].id     = (short)mob_id;
			quest_db[i].drop[j].nameid = atoi(split[10+j*3]);
			quest_db[i].drop[j].p      = atoi(split[11+j*3]);

			if(mob_id > 0) {
				int n;
				for(n = 0; n < max_killdb_count; n++) {
					if(quest_killdb[n] == mob_id)
						break;
				}
				if(n != max_killdb_count)
					continue;

				// 新しく出現したMobIDなので討伐データベースに追加
				if(n >= size) {
					size += QUEST_KILLDB_SIZE;
					quest_killdb = (int *)aRealloc(quest_killdb, sizeof(int) * size);
					memset(quest_killdb + (size - QUEST_KILLDB_SIZE), 0, sizeof(int) * QUEST_KILLDB_SIZE);
				}
				quest_killdb[n] = mob_id;
				max_killdb_count++;
			}
		}

		if(++i >= MAX_QUEST_DB)
			break;
	}

	// 討伐データベースのリサイズ
	quest_killdb = (int *)aRealloc(quest_killdb, sizeof(int) * max_killdb_count);

	// 討伐データベースのソート
	qsort(quest_killdb, max_killdb_count, sizeof(int), quest_sort_id);

	fclose(fp);
	printf("read %s done (count=%d)\n", filename, i);

	return 0;
}

/*==========================================
 * リロード
 *------------------------------------------
 */
void quest_reload(void)
{
	quest_readdb();
}

/*==========================================
 * 終了
 *------------------------------------------
 */
int do_final_quest(void)
{
	if(quest_killdb) {
		aFree(quest_killdb);
		quest_killdb = NULL;
		max_killdb_count = 0;
	}

	return 0;
}

/*==========================================
 * クエスト初期化処理
 *------------------------------------------
 */
int do_init_quest(void)
{
	quest_readdb();

	return 0;
}
