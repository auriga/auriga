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
#include "lock.h"
#include "malloc.h"
#include "journal.h"
#include "utils.h"
#include "nullpo.h"

#include "elemdb_txt.h"

static struct dbt *elem_db = NULL;

static char elem_txt[1024] = "save/elemental.txt";
static int elem_newid = 100;

#ifdef TXT_JOURNAL
static int elem_journal_enable = 1;
static struct journal elem_journal;
static char elem_journal_file[1024] = "./save/elemental.journal";
static int elem_journal_cache = 1000;
#endif

/*==========================================
 * 設定ファイル読込
 *------------------------------------------
 */
int elemdb_txt_config_read_sub(const char* w1,const char *w2)
{
	if(strcmpi(w1,"elem_txt")==0){
		strncpy(elem_txt, w2, sizeof(elem_txt) - 1);
	}
#ifdef TXT_JOURNAL
	else if(strcmpi(w1,"elem_journal_enable")==0){
		elem_journal_enable = atoi( w2 );
	}
	else if(strcmpi(w1,"elem_journal_file")==0){
		strncpy( elem_journal_file, w2, sizeof(elem_journal_file) - 1 );
	}
	else if(strcmpi(w1,"elem_journal_cache_interval")==0){
		elem_journal_cache = atoi( w2 );
	}
#endif
	else {
		return 0;
	}

	return 1;
}

/*==========================================
 * 精霊データを文字列へ変換
 *------------------------------------------
 */
static int elem_tostr(char *str, struct mmo_elemstatus *e)
{
	char *str_p = str;

	nullpo_retr(1, e);

	str_p += sprintf(str, "%d,%d\t%d,%d\t%d,%d,%d,%u",
		e->elem_id, e->class_, e->account_id, e->char_id, e->mode, e->hp,e->sp, e->limit);

	*(str_p++) = '\t';

	*str_p = '\0';
	return 0;
}

/*==========================================
 * 精霊データを文字列から変換
 *------------------------------------------
 */
static int elem_fromstr(char *str, struct mmo_elemstatus *e)
{
	int set;
	int tmp_int[8];

	nullpo_retr(1, e);

	memset(e, 0, sizeof(struct mmo_elemstatus));

	set = sscanf(str, "%d,%d\t%d,%d\t%d,%d,%d,%u",
		&tmp_int[0],&tmp_int[1],
		&tmp_int[2],&tmp_int[3],
		&tmp_int[4],&tmp_int[5],&tmp_int[6],&tmp_int[7]);

	if(set != 8)
		return 1;

	e->elem_id    = tmp_int[0];
	e->class_     = tmp_int[1];
	e->account_id = tmp_int[2];
	e->char_id    = tmp_int[3];
	e->mode       = tmp_int[4];
	e->hp         = tmp_int[5];
	e->sp         = tmp_int[6];
	e->limit      = (unsigned int)tmp_int[7];

	return 0;
}

#ifdef TXT_JOURNAL
// ==========================================
// 傭兵データのジャーナルのロールフォワード用コールバック関数
// ------------------------------------------
int elem_journal_rollforward( int key, void* buf, int flag )
{
	struct mmo_elemstatus* e = (struct mmo_elemstatus *)numdb_search( elem_db, key );

	// 念のためチェック
	if( flag == JOURNAL_FLAG_WRITE && key != ((struct mmo_elemstatus*)buf)->elem_id )
	{
		printf("int_elem: journal: key != elem_id !\n");
		return 0;
	}

	// データの置き換え
	if( e )
	{
		if( flag == JOURNAL_FLAG_DELETE ) {
			numdb_erase(elem_db, key);
			aFree(e);
		} else {
			memcpy( e, buf, sizeof(struct mmo_elemstatus) );
		}
		return 1;
	}

	// 追加
	if( flag != JOURNAL_FLAG_DELETE )
	{
		e = (struct mmo_elemstatus*) aCalloc( 1, sizeof( struct mmo_elemstatus ) );
		memcpy( e, buf, sizeof(struct mmo_elemstatus) );
		numdb_insert( elem_db, key, e );
		if( e->elem_id >= elem_newid)
			elem_newid = e->elem_id + 1;
		return 1;
	}

	return 0;
}
int elemdb_txt_sync(void);
#endif

/*==========================================
 * 精霊データファイルの読み込み
 *------------------------------------------
 */
static bool elemdb_txt_read(void)
{
	FILE *fp;
	bool ret = true;

	elem_db = numdb_init();

	if((fp = fopen(elem_txt, "r")) == NULL) {
		printf("elemdb_txt_read: open [%s] failed !\n", elem_txt);
		ret = false;
	} else {
		int count = 0;
		char line[8192];

		while(fgets(line, sizeof(line), fp)) {
			struct mmo_elemstatus *e = (struct mmo_elemstatus *)aCalloc(1, sizeof(struct mmo_elemstatus));
			if(elem_fromstr(line, e) == 0 && e->elem_id > 0) {
				if(e->elem_id >= elem_newid)
					elem_newid = e->elem_id + 1;
				numdb_insert(elem_db, e->elem_id, e);
			} else {
				printf("int_elem: broken data [%s] line %d\n", elem_txt, count);
				aFree(e);
			}
			count++;
		}
		fclose(fp);
	}

#ifdef TXT_JOURNAL
	if( elem_journal_enable )
	{
		// ジャーナルデータのロールフォワード
		if( journal_load( &elem_journal, sizeof(struct mmo_elemstatus), elem_journal_file ) )
		{
			int c = journal_rollforward( &elem_journal, elem_journal_rollforward );

			printf("int_elem: journal: roll-forward (%d)\n", c );

			// ロールフォワードしたので、txt データを保存する ( journal も新規作成される)
			elemdb_txt_sync();
		}
		else
		{
			// ジャーナルを新規作成する
			journal_final( &elem_journal );
			journal_create( &elem_journal, sizeof(struct mmo_elemstatus), elem_journal_cache, elem_journal_file );
		}
	}
#endif

	return ret;
}

/*==========================================
 * 同期
 *------------------------------------------
 */
static int elemdb_txt_sync_sub(void *key,void *data,va_list ap)
{
	char line[8192];
	FILE *fp;

	elem_tostr(line, (struct mmo_elemstatus *)data);
	fp = va_arg(ap, FILE *);
	fprintf(fp, "%s" NEWLINE, line);
	return 0;
}

int elemdb_txt_sync(void)
{
	FILE *fp;
	int lock;

	if( !elem_db )
		return 1;

	if( (fp = lock_fopen(elem_txt, &lock)) == NULL ) {
		printf("elemdb_txt_sync: can't write [%s] !!! data is lost !!!\n", elem_txt);
		return 1;
	}
	numdb_foreach(elem_db, elemdb_txt_sync_sub, fp);
	lock_fclose(fp, elem_txt, &lock);

#ifdef TXT_JOURNAL
	if( elem_journal_enable )
	{
		// コミットしたのでジャーナルを新規作成する
		journal_final( &elem_journal );
		journal_create( &elem_journal, sizeof(struct mmo_elemstatus), elem_journal_cache, elem_journal_file );
	}
#endif

	return 0;
}

/*==========================================
 * 精霊削除
 *------------------------------------------
 */
bool elemdb_txt_delete(int elem_id)
{
	struct mmo_elemstatus *p = (struct mmo_elemstatus *)numdb_search(elem_db, elem_id);

	if(p == NULL)
		return false;

	numdb_erase(elem_db, elem_id);
	aFree(p);
	printf("elem_id: %d deleted\n", elem_id);

#ifdef TXT_JOURNAL
	if( elem_journal_enable )
		journal_write( &elem_journal, elem_id, NULL );
#endif

	return true;
}

/*==========================================
 * 精霊IDから精霊データをロード
 *------------------------------------------
 */
const struct mmo_elemstatus* elemdb_txt_load(int elem_id)
{
	return (const struct mmo_elemstatus *)numdb_search(elem_db, elem_id);
}

/*==========================================
 * セーブ
 *------------------------------------------
 */
bool elemdb_txt_save(struct mmo_elemstatus *p2)
{
	struct mmo_elemstatus *p1;

	nullpo_retr(false, p2);

	p1 = (struct mmo_elemstatus *)numdb_search(elem_db, p2->elem_id);
	if(p1 == NULL) {
		p1 = (struct mmo_elemstatus *)aMalloc(sizeof(struct mmo_elemstatus));
		numdb_insert(elem_db, p2->elem_id, p1);
	}
	memcpy(p1, p2, sizeof(struct mmo_elemstatus));

#ifdef TXT_JOURNAL
	if( elem_journal_enable )
		journal_write( &elem_journal, p1->elem_id, p1 );
#endif
	return true;
}

/*==========================================
 * 精霊作成
 *------------------------------------------
 */
bool elemdb_txt_new(struct mmo_elemstatus *p2)
{
	struct mmo_elemstatus *p1;

	nullpo_retr(false, p2);

	p1 = (struct mmo_elemstatus *)aMalloc(sizeof(struct mmo_elemstatus));
	p2->elem_id = elem_newid++;

	memcpy(p1, p2, sizeof(struct mmo_elemstatus));
	numdb_insert(elem_db, p2->elem_id, p1);
	return true;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
static int elemdb_txt_final_sub(void *key, void *data, va_list ap)
{
	struct mmo_elemstatus *p = (struct mmo_elemstatus *)data;

	aFree(p);

	return 0;
}

void elemdb_txt_final(void)
{
	if(elem_db)
		numdb_final(elem_db, elemdb_txt_final_sub);

#ifdef TXT_JOURNAL
	if( elem_journal_enable )
	{
		journal_final( &elem_journal );
	}
#endif
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
bool elemdb_txt_init(void)
{
	return elemdb_txt_read();
}
