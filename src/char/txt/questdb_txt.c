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
#include "lock.h"
#include "malloc.h"
#include "journal.h"
#include "nullpo.h"

#include "questdb_txt.h"

static char quest_txt[1024] = "save/quest.txt";
static struct dbt *quest_db = NULL;

#ifdef TXT_JOURNAL
static int quest_journal_enable = 1;
static struct journal quest_journal;
static char quest_journal_file[1024] = "./save/quest.journal";
static int quest_journal_cache = 1000;
#endif

/*==========================================
 * 設定ファイル読込
 *------------------------------------------
 */
int questdb_txt_config_read_sub(const char *w1, const char *w2)
{
	if(strcmpi(w1,"quest_txt")==0) {
		strncpy(quest_txt, w2, sizeof(quest_txt) - 1);
	}
#ifdef TXT_JOURNAL
	else if(strcmpi(w1,"quest_journal_enable")==0) {
		quest_journal_enable = atoi(w2);
	}
	else if(strcmpi(w1,"quest_journal_file")==0) {
		strncpy(quest_journal_file, w2, sizeof(quest_journal_file) - 1);
	}
	else if(strcmpi(w1,"quest_journal_cache_interval")==0) {
		quest_journal_cache = atoi(w2);
	}
#endif
	else {
		return 0;
	}

	return 1;
}

/*==========================================
 * クエストデータを文字列へ変換
 *------------------------------------------
 */
static int questdb_tostr(char *str, struct quest *q)
{
	int i;
	char *str_p = str;

	nullpo_retr(1, q);

	str_p += sprintf(str, "%d,%d\t", q->char_id, q->account_id);

	for(i = 0; i < q->count; i++) {
		str_p += sprintf(str_p, "%d,%d,%u,%d,%d,%d,%d,%d,%d,%d,%d,%d ",
			q->data[i].nameid,q->data[i].state,q->data[i].limit,
			q->data[i].mob[0].id,q->data[i].mob[0].max,q->data[i].mob[0].cnt,
			q->data[i].mob[1].id,q->data[i].mob[1].max,q->data[i].mob[1].cnt,
			q->data[i].mob[2].id,q->data[i].mob[2].max,q->data[i].mob[2].cnt);
	}
	*(str_p++) = '\t';

	*str_p = '\0';
	return 0;
}

/*==========================================
 * クエストデータを文字列から変換
 *------------------------------------------
 */
static int questdb_fromstr(char *str, struct quest *q)
{
	int i, next, set, len;
	int tmp_int[12];

	if(sscanf(str, "%d,%d%n", &q->char_id, &q->account_id, &next) != 2)
		return 1;

	if(q->account_id <= 0 || q->char_id <= 0)
		return 1;

	if(str[next] == '\n' || str[next] == '\r')
		return 1;	// account_idとchar_idだけの行は有り得ない
	next++;

	for(i = 0; str[next] && str[next] != '\t'; i++) {
		set = sscanf(str + next, "%d,%d,%u,%d,%d,%d,%d,%d,%d,%d,%d,%d%n",
			&tmp_int[0],&tmp_int[1],&tmp_int[2],
			&tmp_int[3],&tmp_int[4],&tmp_int[5],
			&tmp_int[6],&tmp_int[7],&tmp_int[8],
			&tmp_int[9],&tmp_int[10],&tmp_int[11],&len);

		if(set != 12)
			return 1;
		if(i < MAX_QUESTLIST) {
			q->data[i].nameid     = tmp_int[0];
			q->data[i].state      = (char)tmp_int[1];
			q->data[i].limit      = (unsigned int)tmp_int[2];
			q->data[i].mob[0].id  = (short)tmp_int[3];
			q->data[i].mob[0].max = (short)tmp_int[4];
			q->data[i].mob[0].cnt = (short)tmp_int[5];
			q->data[i].mob[1].id  = (short)tmp_int[6];
			q->data[i].mob[1].max = (short)tmp_int[7];
			q->data[i].mob[1].cnt = (short)tmp_int[8];
			q->data[i].mob[2].id  = (short)tmp_int[9];
			q->data[i].mob[2].max = (short)tmp_int[10];
			q->data[i].mob[2].cnt = (short)tmp_int[11];
		}
		next += len;
		if(str[next] == ' ')
			next++;
	}
	q->count = (i < MAX_QUESTLIST)? i: MAX_QUESTLIST;

	return 0;
}

#ifdef TXT_JOURNAL
// ----------------------------------------------------------
// クエストデータ用ジャーナルのロールフォワード用コールバック関数
// ----------------------------------------------------------
int quest_journal_rollforward( int key, void* buf, int flag )
{
	struct quest *q = (struct quest *)numdb_search( quest_db, key );

	// 念のためチェック
	if( flag == JOURNAL_FLAG_WRITE && key != ((struct quest *)buf)->char_id )
	{
		printf("int_quest: journal: key != char_id !\n");
		return 0;
	}

	// データの置き換え
	if( q )
	{
		if( flag == JOURNAL_FLAG_DELETE ) {
			numdb_erase(quest_db, key);
			aFree(q);
		} else {
			memcpy( q, buf, sizeof(struct quest) );
		}
		return 1;
	}

	// 追加
	if( flag != JOURNAL_FLAG_DELETE )
	{
		q = (struct quest *)aCalloc( 1, sizeof( struct quest ) );
		memcpy( q, buf, sizeof(struct quest) );
		numdb_insert( quest_db, key, q );
		return 1;
	}

	return 0;
}
int questdb_txt_sync(void);
#endif

/*==========================================
 * クエストデータファイルの読み込み
 *------------------------------------------
 */
static bool questdb_txt_read(void)
{
	FILE *fp;
	bool ret = true;

	quest_db = numdb_init();

	if((fp = fopen(quest_txt, "r")) == NULL) {
		printf("questdb_txt_read: open [%s] failed !\n", quest_txt);
		ret = false;
	} else {
		int count = 0;
		char line[8192];

		while(fgets(line, sizeof(line), fp)) {
			struct quest *q = (struct quest *)aCalloc(1, sizeof(struct quest));
			if(questdb_fromstr(line, q) == 0) {
				numdb_insert(quest_db, q->char_id, q);
			} else {
				printf("int_quest: broken data [%s] line %d\n", quest_txt, count);
				aFree(q);
			}
			count++;
		}
		fclose(fp);
		//printf("int_quest: %s read done (%d quest)\n",quest_txt,c);
	}

#ifdef TXT_JOURNAL
	if( quest_journal_enable )
	{
		// ジャーナルデータのロールフォワード
		if( journal_load( &quest_journal, sizeof(struct quest), quest_journal_file ) )
		{
			int c = journal_rollforward( &quest_journal, quest_journal_rollforward );

			printf("int_quest: journal: roll-forward (%d)\n", c );

			// ロールフォワードしたので、txt データを保存する ( journal も新規作成される)
			questdb_txt_sync();
		}
		else
		{
			// ジャーナルを新規作成する
			journal_final( &quest_journal );
			journal_create( &quest_journal, sizeof(struct quest), quest_journal_cache, quest_journal_file );
		}
	}
#endif

	return ret;
}

/*==========================================
 * 同期
 *------------------------------------------
 */
static int questdb_txt_sync_sub(void *key, void *data, va_list ap)
{
	char line[8192];
	FILE *fp;
	struct quest *q = (struct quest *)data;

	// countが0のときは書き込みしない
	if(q && q->count > 0) {
		questdb_tostr(line, q);
		fp = va_arg(ap, FILE *);
		fprintf(fp, "%s" NEWLINE, line);
	}
	return 0;
}

int questdb_txt_sync(void)
{
	FILE *fp;
	int lock;

	if( !quest_db )
		return 1;

	if( (fp = lock_fopen(quest_txt, &lock)) == NULL ) {
		printf("questdb_txt_sync: can't write [%s] !!! data is lost !!!\n", quest_txt);
		return 1;
	}
	numdb_foreach(quest_db, questdb_txt_sync_sub, fp);
	lock_fclose(fp, quest_txt, &lock);

#ifdef TXT_JOURNAL
	if( quest_journal_enable )
	{
		// コミットしたのでジャーナルを新規作成する
		journal_final( &quest_journal );
		journal_create( &quest_journal, sizeof(struct quest), quest_journal_cache, quest_journal_file );
	}
#endif

	return 0;
}

/*==========================================
 * クエストデータ削除
 *------------------------------------------
 */
bool questdb_txt_delete(int char_id)
{
	struct quest *q = (struct quest *)numdb_search(quest_db, char_id);

	if(q == NULL)
		return false;

	numdb_erase(quest_db, char_id);
	aFree(q);

#ifdef TXT_JOURNAL
	if( quest_journal_enable )
		journal_write( &quest_journal, char_id, NULL );
#endif

	return true;
}

/*==========================================
 * キャラIDからクエストデータを取得
 *------------------------------------------
 */
const struct quest *questdb_txt_load(int char_id)
{
	return (struct quest *)numdb_search(quest_db, char_id);
}

/*==========================================
 * セーブ
 *------------------------------------------
 */
bool questdb_txt_save(struct quest *q2)
{
	struct quest *q1;

	nullpo_retr(false, q2);

	q1 = (struct quest *)numdb_search(quest_db, q2->char_id);
	if(q1 == NULL) {
		q1 = (struct quest *)aCalloc(1,sizeof(struct quest));
		numdb_insert(quest_db, q2->char_id, q1);
		q1->account_id = q2->account_id;
		q1->char_id    = q2->char_id;
	}

	// データが共に0個ならコピーしない
	if(q1->count > 0 || q2->count > 0)
		memcpy(q1, q2, sizeof(struct quest));

#ifdef TXT_JOURNAL
	if( quest_journal_enable )
		journal_write( &quest_journal, q1->char_id, q1 );
#endif
	return true;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
static int questdb_txt_final_sub(void *key, void *data, va_list ap)
{
	struct quest *q = (struct quest *)data;

	aFree(q);

	return 0;
}

void questdb_txt_final(void)
{
	if(quest_db)
		numdb_final(quest_db, questdb_txt_final_sub);

#ifdef TXT_JOURNAL
	if( quest_journal_enable )
	{
		journal_final( &quest_journal );
	}
#endif
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
bool questdb_txt_init(void)
{
	return questdb_txt_read();
}
