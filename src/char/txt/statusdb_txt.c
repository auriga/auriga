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

#ifndef NO_SCDATA_SAVING

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mmo.h"
#include "db.h"
#include "lock.h"
#include "malloc.h"
#include "journal.h"
#include "utils.h"
#include "nullpo.h"

#include "statusdb_txt.h"

static char scdata_txt[1024] = "save/scdata.txt";
static struct dbt *scdata_db = NULL;

#ifdef TXT_JOURNAL
static int status_journal_enable = 1;
static struct journal status_journal;
static char status_journal_file[1024] = "./save/scdata.journal";
static int status_journal_cache = 1000;
#endif

/*==========================================
 * 設定ファイルの読み込み
 *------------------------------------------
 */
int statusdb_txt_config_read_sub(const char *w1, const char *w2)
{
	if(strcmpi(w1,"status_txt")==0) {
		strncpy(scdata_txt, w2, sizeof(scdata_txt) - 1);
	}
#ifdef TXT_JOURNAL
	else if(strcmpi(w1,"status_journal_enable")==0) {
		status_journal_enable = atoi(w2);
	}
	else if(strcmpi(w1,"status_journal_file")==0) {
		strncpy(status_journal_file, w2, sizeof(status_journal_file) - 1);
	}
	else if(strcmpi(w1,"status_journal_cache_interval")==0) {
		status_journal_cache = atoi(w2);
	}
#endif
	else {
		return 0;
	}

	return 1;
}

/*==========================================
 * ステータスデータを文字列へ変換
 *------------------------------------------
 */
static int status_tostr(char *str, struct scdata *sc)
{
	int i;
	char *str_p = str;

	nullpo_retr(1, sc);

	str_p += sprintf(str,"%d,%d\t",sc->char_id, sc->account_id);

	for(i = 0; i < sc->count; i++) {
		str_p += sprintf(str_p, "%d,%d,%d,%d,%d,%d ",
			sc->data[i].type, sc->data[i].val1, sc->data[i].val2, sc->data[i].val3, sc->data[i].val4, sc->data[i].tick);
	}
	*(str_p++) = '\t';

	*str_p = '\0';
	return 0;
}

/*==========================================
 * ステータスデータを文字列から変換
 *------------------------------------------
 */
static int status_fromstr(char *str, struct scdata *sc)
{
	int i, next, set, len;
	int tmp_int[6];

	nullpo_retr(1, sc);

	if(sscanf(str, "%d,%d%n", &sc->char_id, &sc->account_id, &next) != 2)
		return 1;

	if(sc->account_id <= 0 || sc->char_id <= 0)
		return 1;

	if(str[next] == '\n' || str[next] == '\r')
		return 1;	// account_idとchar_idだけの行は有り得ない
	next++;

	for(i = 0; str[next] && str[next] != '\t'; i++) {
		set = sscanf(str + next, "%d,%d,%d,%d,%d,%d%n",
			&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],&tmp_int[4],&tmp_int[5],&len);
		if(set != 6)
			return 1;
		if(i < MAX_STATUSCHANGE && tmp_int[0] >= 0 && tmp_int[0] < MAX_STATUSCHANGE) {
			sc->data[i].type = (short)tmp_int[0];
			sc->data[i].val1 = tmp_int[1];
			sc->data[i].val2 = tmp_int[2];
			sc->data[i].val3 = tmp_int[3];
			sc->data[i].val4 = tmp_int[4];
			sc->data[i].tick = tmp_int[5];
		}
		next += len;
		if(str[next] == ' ')
			next++;
	}
	sc->count = (i < MAX_STATUSCHANGE)? i: MAX_STATUSCHANGE;

	return 0;
}

#ifdef TXT_JOURNAL
// ==========================================
// ステータス異常データのジャーナルのロールフォワード用コールバック関数
// ------------------------------------------
int status_journal_rollforward( int key, void* buf, int flag )
{
	struct scdata *sc = (struct scdata *)numdb_search( scdata_db, key );

	// 念のためチェック
	if( flag == JOURNAL_FLAG_WRITE && key != ((struct scdata *)buf)->char_id )
	{
		printf("int_status: journal: key != char_id !\n");
		return 0;
	}

	// データの置き換え
	if( sc )
	{
		if( flag == JOURNAL_FLAG_DELETE ) {
			numdb_erase(scdata_db, key);
			aFree(sc);
		} else {
			memcpy( sc, buf, sizeof(struct scdata) );
		}
		return 1;
	}

	// 追加
	if( flag != JOURNAL_FLAG_DELETE )
	{
		sc = (struct scdata *)aCalloc( 1, sizeof( struct scdata ) );
		memcpy( sc, buf, sizeof(struct scdata) );
		numdb_insert( scdata_db, key, sc );
		return 1;
	}

	return 0;
}
int statusdb_txt_sync(void);
#endif

/*==========================================
 * ステータスデータファイルの読み込み
 *------------------------------------------
 */
static bool statusdb_txt_read(void)
{
	FILE *fp;
	bool ret = true;

	scdata_db = numdb_init();

	if((fp = fopen(scdata_txt, "r")) == NULL) {
		printf("statusdb_txt_read: open [%s] failed !\n", scdata_txt);
		ret = false;
	} else {
		int count = 0;
		char line[8192];

		while(fgets(line, sizeof(line), fp)) {
			struct scdata *sc = (struct scdata *)aCalloc(1, sizeof(struct scdata));
			if(status_fromstr(line, sc) == 0) {
				numdb_insert(scdata_db, sc->char_id, sc);
			} else {
				printf("int_status: broken data [%s] line %d\n", scdata_txt, count);
				aFree(sc);
			}
			count++;
		}
		fclose(fp);
		//printf("int_status: %s read done (%d status)\n",scdata_txt,c);
	}

#ifdef TXT_JOURNAL
	if( status_journal_enable )
	{
		// ジャーナルデータのロールフォワード
		if( journal_load( &status_journal, sizeof(struct scdata), status_journal_file ) )
		{
			int c = journal_rollforward( &status_journal, status_journal_rollforward );

			printf("int_status: journal: roll-forward (%d)\n", c );

			// ロールフォワードしたので、txt データを保存する ( journal も新規作成される)
			statusdb_txt_sync();
		}
		else
		{
			// ジャーナルを新規作成する
			journal_final( &status_journal );
			journal_create( &status_journal, sizeof(struct scdata), status_journal_cache, status_journal_file );
		}
	}
#endif

	return ret;
}

/*==========================================
 * 同期
 *------------------------------------------
 */
static int statusdb_txt_sync_sub(void *key, void *data, va_list ap)
{
	char line[8192];
	FILE *fp;
	struct scdata *sc = (struct scdata *)data;

	// countが0のときは書き込みしない
	if(sc && sc->count > 0) {
		status_tostr(line, sc);
		fp = va_arg(ap, FILE *);
		fprintf(fp, "%s" NEWLINE, line);
	}
	return 0;
}

int statusdb_txt_sync(void)
{
	FILE *fp;
	int lock;

	if( !scdata_db )
		return 1;

	if( (fp = lock_fopen(scdata_txt, &lock)) == NULL ) {
		printf("statusdb_txt_sync: can't write [%s] !!! data is lost !!!\n", scdata_txt);
		return 1;
	}
	numdb_foreach(scdata_db, statusdb_txt_sync_sub, fp);
	lock_fclose(fp, scdata_txt, &lock);

#ifdef TXT_JOURNAL
	if( status_journal_enable )
	{
		// コミットしたのでジャーナルを新規作成する
		journal_final( &status_journal );
		journal_create( &status_journal, sizeof(struct scdata), status_journal_cache, status_journal_file );
	}
#endif

	return 0;
}

/*==========================================
 * ステータスデータ削除
 *------------------------------------------
 */
bool statusdb_txt_delete(int char_id)
{
	struct scdata *sc = (struct scdata *)numdb_search(scdata_db, char_id);

	if(sc == NULL)
		return false;

	numdb_erase(scdata_db, char_id);
	aFree(sc);

#ifdef TXT_JOURNAL
	if( status_journal_enable )
		journal_write( &status_journal, char_id, NULL );
#endif

	return true;
}

/*==========================================
 * キャラIDからステータスデータをロード
 * 負荷軽減を優先してconstを付けない
 *------------------------------------------
 */
struct scdata *statusdb_txt_load(int char_id)
{
	return (struct scdata *)numdb_search(scdata_db, char_id);
}

/*==========================================
 * セーブ
 *------------------------------------------
 */
bool statusdb_txt_save(struct scdata *sc2)
{
	struct scdata *sc1;

	nullpo_retr(false, sc2);

	sc1 = (struct scdata *)numdb_search(scdata_db,sc2->char_id);
	if(sc1 == NULL) {
		sc1 = (struct scdata *)aCalloc(1, sizeof(struct scdata));
		numdb_insert(scdata_db, sc2->char_id, sc1);
		sc1->account_id = sc2->account_id;
		sc1->char_id    = sc2->char_id;
	}

	// データが共に0個ならコピーしない
	if(sc1->count > 0 || sc2->count > 0)
		memcpy(sc1, sc2, sizeof(struct scdata));

#ifdef TXT_JOURNAL
	if( status_journal_enable )
		journal_write( &status_journal, sc1->char_id, sc1 );
#endif
	return true;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
static int statusdb_txt_final_sub(void *key, void *data, va_list ap)
{
	struct scdata *sc = (struct scdata *)data;

	aFree(sc);

	return 0;
}

void statusdb_txt_final(void)
{
	if(scdata_db)
		numdb_final(scdata_db, statusdb_txt_final_sub);

#ifdef TXT_JOURNAL
	if( status_journal_enable )
	{
		journal_final( &status_journal );
	}
#endif
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
bool statusdb_txt_init(void)
{
	return statusdb_txt_read();
}

#endif
