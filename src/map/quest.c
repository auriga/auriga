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
#include <string.h>
#include <time.h>

#include "nullpo.h"

#include "map.h"
#include "quest.h"
#include "clif.h"
#include "chrif.h"
#include "intif.h"
#include "pc.h"

/* クエストデータベース */
struct quest_db quest_db[MAX_QUEST_DB];

/*==========================================
 * クエストDBのデータを検索
 *------------------------------------------
 */
int quest_search_db(int quest_id)
{
	int i;

	for(i=0; i < MAX_QUEST_DB; i++) {
		if(quest_db[i].nameid == quest_id)
			return i;
	}

	return -1;
}

/*==========================================
 * クエストIDからインデックスを返す
 *------------------------------------------
 */
int quest_search_index(struct map_session_data *sd, int quest_id)
{
	int i;

	nullpo_retr(-1, sd);

	for(i=0; i < sd->questlist; i++) {
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
 * クエストリスト追加
 *------------------------------------------
 */
int quest_addlist(struct map_session_data *sd, int quest_id)
{
	struct quest_data qd;
	int i, qid, idx;

	nullpo_retr(1, sd);

	if(sd->questlist >= MAX_QUESTLIST)
		return 1;

	qid = quest_search_db(quest_id);
	if(qid < 0)
		return 1;

	memset(&qd, 0, sizeof(struct quest_data));
	qd.nameid = quest_db[qid].nameid;
	if(quest_db[qid].limit)
		qd.limit = (unsigned int)time(NULL) + quest_db[qid].limit;
	for(i = 0; i < 3; i++) {
		qd.mob[i].id  = quest_db[qid].mob[i].id;
		qd.mob[i].max = quest_db[qid].mob[i].count;
	}
	qd.state = 1;

	// 既にクエストを取得してるか検索
	if((idx = quest_search_index(sd, quest_id)) >= 0) {
		// 既にクエストリストにある場合は更新する
		memcpy(&sd->quest[idx], &qd, sizeof(struct quest_data));
	}
	else {
		memcpy(&sd->quest[sd->questlist], &qd, sizeof(struct quest_data));
		sd->questlist++;
	}

	clif_add_questlist(sd, quest_id);
	clif_questlist(sd);
	clif_questlist_info(sd);
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
	int i, qid, idx;

	nullpo_retr(1, sd);

	if(sd->questlist >= MAX_QUESTLIST)
		return 1;

	qid = quest_search_db(new_id);
	if(qid < 0)
		return 1;

	memset(&qd, 0, sizeof(struct quest_data));
	qd.nameid = quest_db[qid].nameid;
	if(quest_db[qid].limit)
		qd.limit = (unsigned int)time(NULL) + quest_db[qid].limit;
	for(i = 0; i < 3; i++) {
		qd.mob[i].id  = quest_db[qid].mob[i].id;
		qd.mob[i].max = quest_db[qid].mob[i].count;
	}
	qd.state = 1;

	// 旧クエストを取得してるか検索
	if((idx = quest_search_index(sd, old_id)) >= 0) {
		// 上書きで更新する
		memcpy(&sd->quest[idx], &qd, sizeof(struct quest_data));
	} else {
		memcpy(&sd->quest[sd->questlist], &qd, sizeof(struct quest_data));
		sd->questlist++;
	}

	clif_add_questlist(sd, new_id);
	clif_questlist(sd);
	clif_questlist_info(sd);
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
	clif_questlist(sd);
	clif_questlist_info(sd);
	intif_save_quest(sd);

	return 0;
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
			for(j = 0; j < 3; j++) {
				if(qd->mob[j].id == mob_id && qd->mob[j].count < qd->mob[j].max) {
					qd->mob[j].count++;
					clif_update_questcount(sd, qd->nameid);
				}
			}
		}
	}

	return 0;
}

/*==========================================
 * クエスト設定ファイル読み込み
 * quest_db.txt クエストデータ
 *------------------------------------------
 */
static int quest_readdb(void)
{
	int i,j;
	FILE *fp;
	char line[1024],*p;

	memset(&quest_db, 0, sizeof(quest_db));

	fp=fopen("db/quest_db.txt","r");
	if(fp==NULL){
		printf("can't read db/quest_db.txt\n");
		return 1;
	}
	i=0;
	while(fgets(line,1020,fp)){
		char *split[9];
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0]=='/' && line[1]=='/')
			continue;
		memset(split,0,sizeof(split));
		for(j=0,p=line;j<9 && p;j++){
			split[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		if(j < 9)
			continue;
		if(i < 0 || i >= MAX_QUEST_DB)
			continue;

		quest_db[i].nameid = atoi(split[0]);
		quest_db[i].limit  = atoi(split[2]);
		for(j = 0; j < 3; j++) {
			quest_db[i].mob[j].id    = (short)atoi(split[3+j*2]);
			quest_db[i].mob[j].count = (short)atoi(split[4+j*2]);
		}

		if(++i >= MAX_QUEST_DB)
			break;
	}
	fclose(fp);
	printf("read db/quest_db.txt done (count=%d)\n",i);

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
 * クエスト初期化処理
 *------------------------------------------
 */
int do_init_quest(void)
{
	quest_readdb();

	return 0;
}
