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

#include "db.h"
#include "malloc.h"
#include "utils.h"
#include "lock.h"
#include "journal.h"

#include "mapreg_txt.h"
#include "../script.h"

static struct dbt *mapreg_db;
static struct dbt *mapregstr_db;
int mapreg_dirty = 0;

char mapreg_txt[256] = "save/mapreg.txt";

#ifdef TXT_JOURNAL
static int mapreg_journal_enable = 1;
static struct journal mapreg_journal;
static char mapreg_journal_file[1024] = "./save/mapreg.journal";
static int mapreg_journal_cache = 1000;

struct mapreg_data {
	char name[256];
	int idx;
	char value[2048];
};
#endif

/*==========================================
 * 設定ファイル読み込み
 *------------------------------------------
 */
int mapreg_txt_config_read_sub(const char *w1, const char *w2)
{
	if(strcmpi(w1,"mapreg_txt") == 0) {
		strncpy(mapreg_txt, w2, sizeof(mapreg_txt) - 1);
		mapreg_txt[sizeof(mapreg_txt) - 1] = '\0';
	}
#ifdef TXT_JOURNAL
	else if(strcmpi(w1,"mapreg_journal_enable") == 0) {
		mapreg_journal_enable = atoi(w2);
	}
	else if(strcmpi(w1,"mapreg_journal_file") == 0) {
		strncpy(mapreg_journal_file, w2, sizeof(mapreg_journal_file) - 1);
	}
	else if(strcmpi(w1,"mapreg_journal_cache_interval") == 0) {
		mapreg_journal_cache = atoi(w2);
	}
#endif
	else {
		return 0;
	}

	return 1;
}

/*==========================================
 * マップ変数の取得
 *------------------------------------------
 */
int mapreg_txt_getreg(int num)
{
	return PTR2INT(numdb_search(mapreg_db, num));
}

/*==========================================
 * マップ変数の変更
 *------------------------------------------
 */
bool mapreg_txt_setreg(int num, int val, int eternal)
{
	if(val != 0)
		numdb_insert(mapreg_db, num, INT2PTR(val));
	else
		numdb_erase(mapreg_db, num);

	if(eternal) {
		mapreg_dirty = 1;

#ifdef TXT_JOURNAL
		if( mapreg_journal_enable ) {
			if(val != 0) {
				struct mapreg_data data;

				strncpy(data.name, script_get_str(num), sizeof(data.name) - 1);
				data.name[sizeof(data.name) - 1] = '\0';
				data.idx = num >> 24;
				sprintf(data.value, "%d", val);

				journal_write( &mapreg_journal, num, &data );
			} else {
				journal_write( &mapreg_journal, num, NULL );
			}
		}
#endif
	}

	return true;
}

/*==========================================
 * 文字列型マップ変数の取得
 *------------------------------------------
 */
char* mapreg_txt_getregstr(int num)
{
	return (char *)numdb_search(mapregstr_db, num);
}

/*==========================================
 * 文字列型マップ変数の変更
 *------------------------------------------
 */
bool mapreg_txt_setregstr(int num, const char *str, int eternal)
{
	char *old_str = NULL;

	if(str && *str)
		old_str = (char *)numdb_insert(mapregstr_db, num, aStrdup(str));
	else
		old_str = (char *)numdb_erase(mapregstr_db, num);

	if(old_str)
		aFree(old_str);

	if(eternal) {
		mapreg_dirty = 1;

#ifdef TXT_JOURNAL
		if( mapreg_journal_enable ) {
			if(str && *str) {
				struct mapreg_data data;

				strncpy(data.name, script_get_str(num), sizeof(data.name) - 1);
				data.name[sizeof(data.name) - 1] = '\0';
				data.idx = num >> 24;
				strncpy(data.value, str, sizeof(data.value) - 1);
				data.value[sizeof(data.value) - 1] = '\0';

				journal_write( &mapreg_journal, num, &data );
			} else {
				journal_write( &mapreg_journal, num, NULL );
			}
		}
#endif
	}

	return true;
}

#ifdef TXT_JOURNAL
// ==========================================
// 永続的マップ変数のジャーナルのロールフォワード用コールバック関数
// ------------------------------------------
int mapreg_journal_rollforward( int key, void* buf, int flag )
{
	const char *name = script_get_str(key);
	char postfix = name[strlen(name) - 1];
	struct mapreg_data *data = (struct mapreg_data *)buf;
	void* value = NULL;

	if( postfix == '$' )
		value = mapreg_getregstr( key );
	else
		value = INT2PTR( mapreg_getreg( key ) );

	// 念のためチェック
	if( flag == JOURNAL_FLAG_WRITE && ((key >> 24) != data->idx || strcmp(name, data->name) != 0) )
	{
		printf("inter: mapreg_journal: key != variable name or index !\n");
		return 0;
	}

	// データの置き換え
	if( value )
	{
		if( flag == JOURNAL_FLAG_DELETE ) {
			if( postfix == '$' )
				mapreg_setregstr( key, NULL, 0 );
			else
				mapreg_setreg( key, 0, 0 );
		} else {
			if( postfix == '$' )
				mapreg_setregstr( key, data->value, 0 );
			else
				mapreg_setreg( key, atoi(data->value), 0);
		}
		return 1;
	}

	// 追加
	if( flag != JOURNAL_FLAG_DELETE )
	{
		if( postfix == '$' )
			mapreg_setregstr( key, data->value, 0 );
		else
			mapreg_setreg( key, atoi(data->value), 0 );

		return 1;
	}

	return 0;
}

// ==========================================
// 永続的マップ変数のジャーナルの変換関数
// ------------------------------------------
static void mapreg_journal_convert( struct journal_header *jhd, void *buf )
{
	struct mapreg_data *data = (struct mapreg_data *)buf;

	if(data) {
		int num = (data->idx << 24) | script_add_str(data->name);
		jhd->key = num;
	}
	return;
}

static int mapreg_txt_sync(void);
#endif

/*==========================================
 * 永続的マップ変数の読み込み
 *------------------------------------------
 */
static bool mapreg_txt_load(void)
{
	FILE *fp;
	bool ret = true;

	if((fp = fopen(mapreg_txt, "rt")) == NULL) {
		printf("mapreg_txt_load: open [%s] failed !\n", mapreg_txt);
		ret = false;
	} else {
		char line[2048];

		while(fgets(line, sizeof(line), fp)) {
			char buf[256];
			int n, v, s, i;

			if(sscanf(line, "%255[^,],%d\t%n", buf, &i, &n) != 2 &&
			   (i = 0, sscanf(line, "%255[^\t]\t%n", buf, &n) != 1))
				continue;

			if(i < 0 || i >= 128) {
				printf("%s: %s broken data !\n", mapreg_txt, buf);
				continue;
			}
			if(buf[strlen(buf) - 1] == '$') {
				char buf2[2048];
				if(sscanf(line + n, "%2047[^\n\r]", buf2) != 1) {
					printf("%s: %s broken data !\n", mapreg_txt, buf);
					continue;
				}
				s = script_add_str(buf);
				mapreg_setregstr((i << 24) | s, buf2, 0);
			} else {
				if(sscanf(line + n, "%d", &v) != 1) {
					printf("%s: %s broken data !\n", mapreg_txt, buf);
					continue;
				}
				s = script_add_str(buf);
				mapreg_setreg((i << 24) | s, v, 0);
			}
		}
		fclose(fp);
	}

#ifdef TXT_JOURNAL
	if( mapreg_journal_enable )
	{
		// ジャーナルデータのロールフォワード
		if( journal_load_with_convert( &mapreg_journal, sizeof(struct mapreg_data), mapreg_journal_file, mapreg_journal_convert ) )
		{
			int c = journal_rollforward( &mapreg_journal, mapreg_journal_rollforward );

			printf("map: mapreg_journal: roll-forward (%d)\n", c );

			// ロールフォワードしたので、txt データを保存する ( journal も新規作成される)
			mapreg_txt_sync();
		}
		else
		{
			// ジャーナルを新規作成する
			journal_final( &mapreg_journal );
			journal_create( &mapreg_journal, sizeof(struct mapreg_data), mapreg_journal_cache, mapreg_journal_file );
		}
	}
#endif

	return ret;
}

/*==========================================
 * 永続的マップ変数の書き込み
 *------------------------------------------
 */
static int mapreg_txt_sync_intsub(void *key, void *data, va_list ap)
{
	FILE *fp = va_arg(ap,FILE*);
	const char *name = script_get_str(PTR2INT(key));
	int idx = PTR2INT(key) >> 24;

	if(name[0] && name[1] != '@') {
		if(idx == 0)
			fprintf(fp,"%s\t%d" NEWLINE, name, PTR2INT(data));
		else
			fprintf(fp,"%s,%d\t%d" NEWLINE, name, idx, PTR2INT(data));
	}
	return 0;
}

static int mapreg_txt_sync_strsub(void *key, void *data, va_list ap)
{
	FILE *fp = va_arg(ap,FILE*);
	const char *name = script_get_str(PTR2INT(key));
	int idx = PTR2INT(key) >> 24;

	if(name[0] && name[1] != '@') {
		if(idx == 0)
			fprintf(fp,"%s\t%s" NEWLINE, name, (char *)data);
		else
			fprintf(fp,"%s,%d\t%s" NEWLINE, name, idx, (char *)data);
	}
	return 0;
}

static int mapreg_txt_sync(void)
{
	FILE *fp;
	int lock;

	if( (fp = lock_fopen(mapreg_txt, &lock)) == NULL ) {
		printf("mapreg_txt_sync: can't write [%s] !!! data is lost !!!\n", mapreg_txt);
		return -1;
	}

	numdb_foreach(mapreg_db, mapreg_txt_sync_intsub, fp);
	numdb_foreach(mapregstr_db, mapreg_txt_sync_strsub, fp);

	lock_fclose(fp, mapreg_txt, &lock);
	mapreg_dirty = 0;

#ifdef TXT_JOURNAL
	if( mapreg_journal_enable )
	{
		// コミットしたのでジャーナルを新規作成する
		journal_final( &mapreg_journal );
		journal_create( &mapreg_journal, sizeof(struct mapreg_data), mapreg_journal_cache, mapreg_journal_file );
	}
#endif

	return 0;
}

/*==========================================
 * 永続的マップ変数の自動セーブ
 *------------------------------------------
 */
int mapreg_txt_autosave(void)
{
	if(mapreg_dirty)
		mapreg_txt_sync();

	return 0;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
static int mapreg_txt_strdb_final(void *key, void *data, va_list ap)
{
	aFree(data);

	return 0;
}

int mapreg_txt_final(void)
{
	if(mapreg_dirty)
		mapreg_txt_sync();

	if(mapreg_db)
		numdb_final(mapreg_db, NULL);
	if(mapregstr_db)
		numdb_final(mapregstr_db, mapreg_txt_strdb_final);

#ifdef TXT_JOURNAL
	if( mapreg_journal_enable )
		journal_final( &mapreg_journal );
#endif

	return 0;
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
bool mapreg_txt_init(void)
{
	mapreg_db    = numdb_init();
	mapregstr_db = numdb_init();
	mapreg_txt_load();

	return true;
}
