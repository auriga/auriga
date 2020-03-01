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

#include "achievedb_txt.h"

static char achieve_txt[1024] = "save/achieve.txt";
static struct dbt *achieve_db = NULL;

#ifdef TXT_JOURNAL
static int achieve_journal_enable = 1;
static struct journal achieve_journal;
static char achieve_journal_file[1024] = "./save/achieve.journal";
static int achieve_journal_cache = 1000;
#endif

/*==========================================
 * 設定ファイル読込
 *------------------------------------------
 */
int achievedb_txt_config_read_sub(const char *w1, const char *w2)
{
	if(strcmpi(w1,"achieve_txt")==0) {
		strncpy(achieve_txt, w2, sizeof(achieve_txt) - 1);
	}
#ifdef TXT_JOURNAL
	else if(strcmpi(w1,"achieve_journal_enable")==0) {
		achieve_journal_enable = atoi(w2);
	}
	else if(strcmpi(w1,"achieve_journal_file")==0) {
		strncpy(achieve_journal_file, w2, sizeof(achieve_journal_file) - 1);
	}
	else if(strcmpi(w1,"achieve_journal_cache_interval")==0) {
		achieve_journal_cache = atoi(w2);
	}
#endif
	else {
		return 0;
	}

	return 1;
}

/*==========================================
 * 実績データを文字列へ変換
 *------------------------------------------
 */
static int achievedb_tostr(char *str, struct achieve *a)
{
	int i;
	char *str_p = str;

	nullpo_retr(1, a);

	str_p += sprintf(str, "%d,%d\t", a->char_id, a->account_id);

	for(i = 0; i < a->count; i++) {
		str_p += sprintf(str_p, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u,%d ",
			a->data[i].nameid,
			a->data[i].count[0],a->data[i].count[1],a->data[i].count[2],
			a->data[i].count[3],a->data[i].count[4],a->data[i].count[5],
			a->data[i].count[6],a->data[i].count[7],a->data[i].count[8],a->data[i].count[9],
			a->data[i].comp_date,a->data[i].reward);
	}
	*(str_p++) = '\t';

	*str_p = '\0';
	return 0;
}

/*==========================================
 * 実績データを文字列から変換
 *------------------------------------------
 */
static int achievedb_fromstr(char *str, struct achieve *a)
{
	int i, next, set, len;
	int tmp_int[13];

	if(sscanf(str, "%d,%d%n", &a->char_id, &a->account_id, &next) != 2)
		return 1;

	if(a->account_id <= 0 || a->char_id <= 0)
		return 1;

	if(str[next] == '\n' || str[next] == '\r')
		return 1;	// account_idとchar_idだけの行は有り得ない
	next++;

	for(i = 0; str[next] && str[next] != '\t'; i++) {
		set = sscanf(str + next, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u,%d%n",
			&tmp_int[0],&tmp_int[1],&tmp_int[2],
			&tmp_int[3],&tmp_int[4],&tmp_int[5],
			&tmp_int[6],&tmp_int[7],&tmp_int[8],
			&tmp_int[9],&tmp_int[10],&tmp_int[11],
			&tmp_int[12],&len);

		if(set != 13)
			return 1;
		if(i < MAX_ACHIEVELIST) {
			a->data[i].nameid    = tmp_int[0];
			a->data[i].count[0]  = tmp_int[1];
			a->data[i].count[1]  = tmp_int[2];
			a->data[i].count[2]  = tmp_int[3];
			a->data[i].count[3]  = tmp_int[4];
			a->data[i].count[4]  = tmp_int[5];
			a->data[i].count[5]  = tmp_int[6];
			a->data[i].count[6]  = tmp_int[7];
			a->data[i].count[7]  = tmp_int[8];
			a->data[i].count[8]  = tmp_int[9];
			a->data[i].count[9]  = tmp_int[10];
			a->data[i].comp_date = (unsigned int)tmp_int[11];
			a->data[i].reward    = (char)tmp_int[12];
		}
		next += len;
		if(str[next] == ' ')
			next++;
	}
	a->count = (i < MAX_ACHIEVELIST)? i: MAX_ACHIEVELIST;

	return 0;
}

#ifdef TXT_JOURNAL
// ----------------------------------------------------------
// 実績データ用ジャーナルのロールフォワード用コールバック関数
// ----------------------------------------------------------
int achieve_journal_rollforward( int key, void* buf, int flag )
{
	struct achieve *a = (struct achieve *)numdb_search( achieve_db, key );

	// 念のためチェック
	if( flag == JOURNAL_FLAG_WRITE && key != ((struct achieve *)buf)->char_id )
	{
		printf("int_achieve: journal: key != char_id !\n");
		return 0;
	}

	// データの置き換え
	if( a )
	{
		if( flag == JOURNAL_FLAG_DELETE ) {
			numdb_erase(achieve_db, key);
			aFree(a);
		} else {
			memcpy( a, buf, sizeof(struct achieve) );
		}
		return 1;
	}

	// 追加
	if( flag != JOURNAL_FLAG_DELETE )
	{
		a = (struct achieve *)aCalloc( 1, sizeof( struct achieve ) );
		memcpy( a, buf, sizeof(struct achieve) );
		numdb_insert( achieve_db, key, a );
		return 1;
	}

	return 0;
}
int achievedb_txt_sync(void);
#endif

/*==========================================
 * 実績データファイルの読み込み
 *------------------------------------------
 */
static bool achievedb_txt_read(void)
{
	FILE *fp;
	bool ret = true;

	achieve_db = numdb_init();

	if((fp = fopen(achieve_txt, "r")) == NULL) {
		printf("achievedb_txt_read: open [%s] failed !\n", achieve_txt);
		ret = false;
	} else {
		int count = 0;
		char line[8192];

		while(fgets(line, sizeof(line), fp)) {
			struct achieve *a = (struct achieve *)aCalloc(1, sizeof(struct achieve));
			if(achievedb_fromstr(line, a) == 0) {
				numdb_insert(achieve_db, a->char_id, a);
			} else {
				printf("int_achieve: broken data [%s] line %d\n", achieve_txt, count);
				aFree(a);
			}
			count++;
		}
		fclose(fp);
		//printf("int_achieve: %s read done (%d achieve)\n",achieve_txt,c);
	}

#ifdef TXT_JOURNAL
	if( achieve_journal_enable )
	{
		// ジャーナルデータのロールフォワード
		if( journal_load( &achieve_journal, sizeof(struct achieve), achieve_journal_file ) )
		{
			int c = journal_rollforward( &achieve_journal, achieve_journal_rollforward );

			printf("int_achieve: journal: roll-forward (%d)\n", c );

			// ロールフォワードしたので、txt データを保存する ( journal も新規作成される)
			achievedb_txt_sync();
		}
		else
		{
			// ジャーナルを新規作成する
			journal_final( &achieve_journal );
			journal_create( &achieve_journal, sizeof(struct achieve), achieve_journal_cache, achieve_journal_file );
		}
	}
#endif

	return ret;
}

/*==========================================
 * 同期
 *------------------------------------------
 */
static int achievedb_txt_sync_sub(void *key, void *data, va_list ap)
{
	char line[8192];
	FILE *fp;
	struct achieve *a = (struct achieve *)data;

	// countが0のときは書き込みしない
	if(a && a->count > 0) {
		achievedb_tostr(line, a);
		fp = va_arg(ap, FILE *);
		fprintf(fp, "%s" NEWLINE, line);
	}
	return 0;
}

int achievedb_txt_sync(void)
{
	FILE *fp;
	int lock;

	if( !achieve_db )
		return 1;

	if( (fp = lock_fopen(achieve_txt, &lock)) == NULL ) {
		printf("achievedb_txt_sync: can't write [%s] !!! data is lost !!!\n", achieve_txt);
		return 1;
	}
	numdb_foreach(achieve_db, achievedb_txt_sync_sub, fp);
	lock_fclose(fp, achieve_txt, &lock);

#ifdef TXT_JOURNAL
	if( achieve_journal_enable )
	{
		// コミットしたのでジャーナルを新規作成する
		journal_final( &achieve_journal );
		journal_create( &achieve_journal, sizeof(struct achieve), achieve_journal_cache, achieve_journal_file );
	}
#endif

	return 0;
}

/*==========================================
 * 実績データ削除
 *------------------------------------------
 */
bool achievedb_txt_delete(int char_id)
{
	struct achieve *a = (struct achieve *)numdb_search(achieve_db, char_id);

	if(a == NULL)
		return false;

	numdb_erase(achieve_db, char_id);
	aFree(a);

#ifdef TXT_JOURNAL
	if( achieve_journal_enable )
		journal_write( &achieve_journal, char_id, NULL );
#endif

	return true;
}

/*==========================================
 * キャラIDから実績データを取得
 *------------------------------------------
 */
const struct achieve *achievedb_txt_load(int char_id)
{
	return (struct achieve *)numdb_search(achieve_db, char_id);
}

/*==========================================
 * セーブ
 *------------------------------------------
 */
bool achievedb_txt_save(struct achieve *a2)
{
	struct achieve *a1;

	nullpo_retr(false, a2);

	a1 = (struct achieve *)numdb_search(achieve_db, a2->char_id);
	if(a1 == NULL) {
		a1 = (struct achieve *)aCalloc(1,sizeof(struct achieve));
		numdb_insert(achieve_db, a2->char_id, a1);
		a1->account_id = a2->account_id;
		a1->char_id    = a2->char_id;
	}

	// データが共に0個ならコピーしない
	if(a1->count > 0 || a2->count > 0)
		memcpy(a1, a2, sizeof(struct achieve));

#ifdef TXT_JOURNAL
	if( achieve_journal_enable )
		journal_write( &achieve_journal, a1->char_id, a1 );
#endif
	return true;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
static int achievedb_txt_final_sub(void *key, void *data, va_list ap)
{
	struct achieve *a = (struct achieve *)data;

	aFree(a);

	return 0;
}

void achievedb_txt_final(void)
{
	if(achieve_db)
		numdb_final(achieve_db, achievedb_txt_final_sub);

#ifdef TXT_JOURNAL
	if( achieve_journal_enable )
	{
		journal_final( &achieve_journal );
	}
#endif
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
bool achievedb_txt_init(void)
{
	return achievedb_txt_read();
}
