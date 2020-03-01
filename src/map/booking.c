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
#include <time.h>

#include "db.h"
#include "malloc.h"
#include "nullpo.h"

#include "battle.h"
#include "booking.h"
#include "clif.h"
#include "map.h"
#include "party.h"

// 1ページの最大検索数
#define MAX_RESULT 10

// 最大MAPID
#define MAX_BOOKING_MAPID 193

// 最大JOBID
#define MAX_BOOKING_JOBID 64

static struct dbt *booking_db = NULL;
static int booking_mapid[MAX_BOOKING_MAPID];
static int booking_jobid[MAX_BOOKING_JOBID];
static unsigned int booking_id = 0;

/*==========================================
 * MAPIDが有効かチェック
 *
 * @note private
 * @param map クライアントから受信したMapID
 * @return 有効であれば1 無効であれば0
 *------------------------------------------
 */
static int booking_search_mapid(int map)
{
	int min = -1;
	int max = MAX_BOOKING_MAPID;

	if(map < 0)
		return 0;

	// binary search
	while(max - min > 1) {
		int mid = (min + max) / 2;
		if(booking_mapid[mid] == map)
			return 1;

		if(booking_mapid[mid] > map)
			max = mid;
		else
			min = mid;
	}
	return 0;
}

/*==========================================
 * JOBIDが有効かチェック
 *
 * @note private
 * @param job クライアントから受信したJobID
 * @return 有効であれば1
 *         無効であれば0
 *------------------------------------------
 */
static int booking_search_jobid(int job)
{
	int min = -1;
	int max = MAX_BOOKING_JOBID;

	if(job <= 0)
		return 0;

	// binary search
	while(max - min > 1) {
		int mid = (min + max) / 2;
		if(booking_jobid[mid] == job)
			return 1;

		if(booking_jobid[mid] > job)
			max = mid;
		else
			min = mid;
	}
	return 0;
}

/*==========================================
 * 該当IDのブッキングリスト検索
 *
 * @note private
 * @param booking_id 検索対象パーティーブッキングID
 * @return booking_dbに格納されているbooking_data構造体
 *         見つからなければNULL
 *------------------------------------------
 */
static struct booking_data *booking_search(unsigned int booking_id)
{
	return (struct booking_data *)numdb_search(booking_db,booking_id);
}

/*==========================================
 * 条件でブッキングリスト検索(旧仕様)
 *
 * @note private
 * @param key booking_searchcond_subでは未使用
 * @param data booking_dbに格納されているbooking_data構造体
 * @param ap 可変長引数
 *           lv :検索条件のレベル
 *           map:検索条件のマップ
 *           job:検索条件の職業
 *           last_index:検索ページのインデックス末尾
 *           result_count:最大検索試行回数
 *           count:検索数カウンタ
 *           booking_data:検索結果格納用booking_data構造体
 * @return 検索が終了すれば0
 *         検索を中断したのなら1
 *------------------------------------------
 */
static int booking_searchcond_sub(void *key, void *data, va_list ap)
{
	struct booking_data *bd = (struct booking_data *)data;
	int lv  = va_arg(ap,int);
	int map = va_arg(ap,int);
	int job = va_arg(ap,int);
	unsigned int last_index = va_arg(ap,unsigned int);
	int result_count = va_arg(ap,int);
	int *count       = va_arg(ap,int *);
	struct booking_data **list = va_arg(ap,struct booking_data **);

	if(lv > 0 && (bd->lv < lv - battle_config.party_booking_lv || bd->lv > lv))	// Lvが条件と合わない
		return 0;

	if(bd->id < last_index)	// last_indexより低いなら無視
		return 0;

	if((*count) >= result_count)	// result_countまでで検索終了
		return 1;

	if(map == 0) {	// 募集MAPが無条件
		if(job == 0xffff) {
			list[(*count)++] = bd;
		} else {
			int i;
			for(i=0; i<6; i++) {
				if(bd->job[i] == job) {
					list[(*count)++] = bd;
					break;
				}
			}
		}
	} else if(job == 0xffff) {	// 募集職業が指定無し
		if(bd->map == map)
			list[(*count)++] = bd;
	}

	return 0;
}

/*==========================================
 * 条件でブッキングリスト検索(新仕様)
 *
 * @note private
 * @param key 未使用
 * @param data booking_dbに格納されているbooking_data構造体
 * @param ap 可変長引数
 *           lv :検索条件のレベル
 *           result_count:最大検索試行回数
 *           count:検索数カウンタ
 *           booking_data:検索結果格納用booking_data構造体
 * @return 検索が終了すれば0
 *         検索を中断したのなら1
 *------------------------------------------
 */
static int booking_searchcond_sub2(void *key, void *data, va_list ap)
{
	struct booking_data *bd = (struct booking_data *)data;
	int lv  = va_arg(ap,int);
	int result_count = va_arg(ap,int);
	int *count       = va_arg(ap,int *);
	struct booking_data **list = va_arg(ap,struct booking_data **);

	if(lv > 0 && (bd->lv < lv - battle_config.party_booking_lv || bd->lv > lv))	// Lvが条件と合わない
		return 0;

	if((*count) >= result_count)	// result_countまでで検索終了
		return 1;

	list[(*count)++] = bd;

	return 0;
}

/*==========================================
 * 該当IDのブッキングリスト検索(旧仕様)
 *
 * @note public
 * @param lv 検索対象のレベル
 * @param map 検索対象のマップ
 * @param job 検索対象の職業
 * @param last_index 検索ページのインデックス末尾
 * @param result_count 最大検索試行回数
 *------------------------------------------
 */
void booking_searchcond(struct map_session_data *sd, int lv, int map, int job, unsigned int last_index, int result_count)
{
	int flag;
	int count=0;
	struct booking_data *list[MAX_RESULT];	// result_countに最大検索数が格納されているが、値がどんな時に変わるのか(0xaしか送られてこない)不明なので、不正対策のためとりあえず定数を用意

	nullpo_retv(sd);

	if(lv > MAX_LEVEL || lv < 0)	// レベルが不正
		return;
	if(!booking_search_mapid(map))	// 有効なMAPIDではない
		return;
	if(!booking_search_jobid(job))	// 有効なJOBIDではない
		return;

	memset(list,0,sizeof(list));

	flag = numdb_foreach(booking_db,booking_searchcond_sub,lv,map,job,last_index,MAX_RESULT,&count,&list);
	clif_searchbookingack(sd,list,count,flag);

	return;
}

/*==========================================
 * 該当IDのブッキングリスト検索(新仕様)
 *
 * @note public
 * @param lv 検索対象のレベル
 *------------------------------------------
 */
void booking_searchcond2(struct map_session_data *sd, int lv)
{
	int flag;
	int count=0;
	struct booking_data *list[MAX_RESULT];	// TODO:暫定的なので仕様が分かり次第修正する

	nullpo_retv(sd);

	if(lv > MAX_LEVEL || lv < 0)	// レベルが不正
		return;

	memset(list,0,sizeof(list));

	flag = numdb_foreach(booking_db,booking_searchcond_sub2,lv,MAX_RESULT,&count,&list);
	clif_searchbookingack(sd,list,count,flag);

	return;
}

/*==========================================
 * パーティーブッキング登録(旧仕様)
 *
 * @note public
 * @param sd 登録要求者
 * @param lv 募集レベル
 * @param map 募集マップ
 * @param job 募集職業
 *------------------------------------------
 */
void booking_register(struct map_session_data *sd, int lv, int map, int *job)
{
	struct booking_data *bd;
	int i;

	nullpo_retv(sd);

	if(sd->booking_id > 0)	// 既に登録中
		return;
	if(lv > MAX_LEVEL || lv < 0)	// レベルが不正
		return;
	if(!booking_search_mapid(map))	// 有効なMAPIDではない
		return;
	for(i=0; i<6; i++) {
		if(!booking_search_jobid(job[i]))	// 有効なJOBIDではない
			return;
	}

	// PTブッキングリストに登録
	bd = (struct booking_data *)aCalloc(1,sizeof(struct booking_data));
	bd->id = ++booking_id;
	numdb_insert(booking_db,booking_id,bd);
	memcpy(bd->name,sd->status.name,24);
	bd->time = (unsigned int)time(NULL);
	bd->lv = lv;
	bd->map = map;

	for(i=0; i<6; i++) {
		if(job[i] != 0xffff)
			bd->job[i] = job[i];
		else
			bd->job[i] = -1;
	}

	sd->booking_id = bd->id;

	// 応答パケット送信
	clif_bookingregack(sd,0);
	clif_insertbookinglist(sd,bd);

	return;
}

/*==========================================
 * パーティーブッキング登録(新仕様)
 *
 * @note public
 * @param sd 登録要求者
 * @param lv 募集レベル
 * @param memo 募集時のメッセージ
 *------------------------------------------
 */
void booking_register2(struct map_session_data *sd, int lv, const char *memo)
{
	struct booking_data *bd;
	struct party *party;
	int i;

	nullpo_retv(sd);

	// 登録要求者がパーティーリーダーかチェック
	if( (party = party_search(sd->status.party_id)) == NULL )
		return;
	for( i = 0; i < MAX_PARTY; i++ )
	{
		if( party->member[i].account_id == sd->status.account_id && party->member[i].char_id == sd->status.char_id)
		{
			if( party->member[i].leader == 0 )
			{
				clif_bookingregack(sd,1);
				return;
			}
		}
	}

	// 既に登録中
	if(sd->booking_id > 0) {
		clif_bookingregack(sd,2);
		return;
	}

	// レベルが不正
	if(lv > MAX_LEVEL || lv < 0) {
		clif_bookingregack(sd,1);
		return;
	}

	// PTブッキングリストに登録
	bd = (struct booking_data *)aCalloc(1,sizeof(struct booking_data));
	bd->id = ++booking_id;
	numdb_insert(booking_db,booking_id,bd);
	memcpy(bd->name,sd->status.name,24);
	bd->time = (unsigned int)time(NULL);
	bd->lv = lv;
	strncpy(bd->memo,memo,MAX_BOOKING_MEMO_LENGTH);
	bd->memo[MAX_BOOKING_MEMO_LENGTH-1] = '\0';

	sd->booking_id = bd->id;

	// 応答パケット送信
	clif_bookingregack(sd,0);
	clif_insertbookinglist(sd,bd);

	return;
}

/*==========================================
 * パーティーブッキング登録情報修正(旧仕様)
 *
 * @note public
 * @param sd 登録情報修正要求者
 * @param job 募集職業
 *------------------------------------------
 */
void booking_update(struct map_session_data *sd, int *job)
{
	struct booking_data *bd;
	int i;

	nullpo_retv(sd);

	bd = booking_search(sd->booking_id);
	if(bd == NULL)
		return;

	for(i=0; i<6; i++) {
		if(!booking_search_jobid(job[i]))	// 有効なJOBIDではない
			return;
		if(job[i] != 0xffff)
			bd->job[i] = job[i];
		else
			bd->job[i] = -1;
	}
	bd->time = (unsigned int)time(NULL);

	clif_updatebookinglist(sd,bd);

	return;
}

/*==========================================
 * パーティーブッキング登録情報修正(新仕様)
 *
 * @note public
 * @param sd 登録情報修正要求者
 * @param memo 募集時のメッセージ
 *------------------------------------------
 */
void booking_update2(struct map_session_data *sd, const char *memo)
{
	struct booking_data *bd;

	nullpo_retv(sd);

	// 自身の登録情報を検索
	bd = booking_search(sd->booking_id);
	if(bd == NULL)
		return;

	// 登録情報修正
	bd->time = (unsigned int)time(NULL);
	strncpy(bd->memo,memo,MAX_BOOKING_MEMO_LENGTH);
	bd->memo[MAX_BOOKING_MEMO_LENGTH-1] = '\0';

	clif_updatebookinglist(sd,bd);

	return;
}

/*==========================================
 * パーティーブッキングリスト削除(旧仕様)
 *
 * @note public
 * @param sd 登録情報削除要求者
 *------------------------------------------
 */
void booking_delete(struct map_session_data *sd)
{
	struct booking_data *bd;

	nullpo_retv(sd);

	bd = (struct booking_data *)numdb_erase(booking_db,sd->booking_id);
	if(bd) {
		clif_deletebookingack(sd,0);
		clif_deletebooking(sd,bd->id);
		aFree(bd);
		sd->booking_id = 0;
	}

	return;
}

/*==========================================
 * パーティーブッキングデータ読み込み
 *
 * @note private
 * @return 成功であれば1
 *         失敗であれば-1
 *------------------------------------------
 */
static int read_booking_db(void)
{
	FILE *fp;
	char line[1024];
	char *str=NULL;
	int count = 0;
	const char *filename;

	memset(booking_mapid, -1, sizeof(booking_mapid));

	filename = "db/booking_map_db.txt";
	fp = fopen(filename,"r");
	if(fp == NULL) {
		printf("read_booking_db: open [%s] failed !\n", filename);
		return -1;
	}

	while(fgets(line,sizeof(line),fp)) {
		int i, id;
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0] == '/' && line[1] == '/')
			continue;

		str=line;
		if(str == NULL)
			continue;

		id = atoi(str);
		for(i = 0; i < MAX_BOOKING_MAPID && booking_mapid[i] >= 0 && booking_mapid[i] != id; i++);
		if(i >= MAX_BOOKING_MAPID) {
			printf("read_booking_db: MAP ID %d is over max %d!!\n", id, MAX_BOOKING_MAPID);
			continue;
		}

		if(booking_mapid[i] != id)
			count++;

		if(i > 0 && id < booking_mapid[i-1]) {
			// MAPIDの昇順に並んでない場合
			int max = i;
			while(i > 0 && id < booking_mapid[i-1]) {
				i--;
			}
			memmove(&booking_mapid[i+1], &booking_mapid[i], (max-i)*sizeof(booking_mapid[0]));
		}
		booking_mapid[i] = id;
	}

	fclose(fp);
	printf("read %s done (count=%d)\n", filename, count);

	count = 0;
	memset(booking_jobid, 0, sizeof(booking_jobid));

	filename = "db/booking_job_db.txt";
	fp = fopen(filename, "r");
	if(fp==NULL) {
		printf("read_booking_db: open [%s] failed !\n", filename);
		return -1;
	}

	while(fgets(line,sizeof(line),fp)) {
		int i, id;
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0] == '/' && line[1] == '/')
			continue;

		str=line;
		if(str == NULL)
			continue;

		id = atoi(str);
		for(i = 0; i < MAX_BOOKING_JOBID && booking_jobid[i] > 0 && booking_jobid[i] != id; i++);
		if(i >= MAX_BOOKING_JOBID) {
			printf("read_booking_db: JOB ID %d is over max %d!!\n", id, MAX_BOOKING_JOBID);
			continue;
		}

		if(booking_jobid[i] != id)
			count++;

		if(i > 0 && id < booking_jobid[i-1]) {
			// JOBIDの昇順に並んでない場合
			int max = i;
			while(i > 0 && id < booking_jobid[i-1]) {
				i--;
			}
			memmove(&booking_jobid[i+1], &booking_jobid[i], (max-i)*sizeof(booking_jobid[0]));
		}
		booking_jobid[i] = id;
	}

	fclose(fp);
	printf("read %s done (count=%d)\n", filename, count);

	return 0;
}

/*==========================================
 * 終了
 *
 * @note private
 * @param key 未使用
 * @aram data メモリ解放するデータ
 * @param ap 未使用
 * @return 常に0を返却
 *------------------------------------------
 */
static int booking_db_final(void *key, void *data, va_list ap)
{
	aFree(data);

	return 0;
}

void do_final_booking(void)
{
	if(booking_db)
		numdb_final(booking_db,booking_db_final);

	return;
}

/*==========================================
 * 初期化
 *
 * @note private
 *------------------------------------------
 */
void do_init_booking(void)
{
	booking_db = numdb_init();
	read_booking_db();

	return;
}
