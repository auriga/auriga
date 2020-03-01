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

#include <stdlib.h>
#include <string.h>

#include "mmo.h"
#include "db.h"
#include "lock.h"
#include "malloc.h"
#include "journal.h"
#include "utils.h"
#include "nullpo.h"

#include "../inter.h"
#include "accregdb_txt.h"

static struct dbt *accreg_db = NULL;

static char accreg_txt[1024] = "save/accreg.txt";

#ifdef TXT_JOURNAL
static int accreg_journal_enable = 1;
static struct journal accreg_journal;
static char accreg_journal_file[1024] = "./save/accreg.journal";
static int accreg_journal_cache = 1000;
#endif

/*==========================================
 * 設定ファイル読込
 *------------------------------------------
 */
int accregdb_txt_config_read_sub(const char *w1,const char *w2)
{
	if(strcmpi(w1,"accreg_txt")==0){
		strncpy(accreg_txt, w2, sizeof(accreg_txt) - 1);
	}
#ifdef TXT_JOURNAL
	else if(strcmpi(w1,"accreg_journal_enable")==0){
		accreg_journal_enable = atoi( w2 );
	}
	else if(strcmpi(w1,"accreg_journal_file")==0){
		strncpy( accreg_journal_file, w2, sizeof(accreg_journal_file) - 1 );
	}
	else if(strcmpi(w1,"accreg_journal_cache_interval")==0){
		accreg_journal_cache = atoi( w2 );
	}
#endif
	else {
		return 0;
	}

	return 1;
}

/*==========================================
 * アカウント変数を文字列へ変換
 *------------------------------------------
 */
static int accregdb_tostr(char *str, struct accreg *reg)
{
	int j;
	char *p = str;

	nullpo_retr(1, reg);

	p += sprintf(p, "%d\t", reg->account_id);
	for(j = 0; j < reg->reg_num; j++) {
		if(reg->reg[j].str[0] && reg->reg[j].value != 0)
			p += sprintf(p, "%s,%d ", reg->reg[j].str, reg->reg[j].value);
	}
	return 0;
}

/*==========================================
 * アカウント変数を文字列から変換
 *------------------------------------------
 */
static int accregdb_fromstr(const char *str, struct accreg *reg)
{
	int j, v, n;
	char buf[256];
	const char *p = str;

	nullpo_retr(1, reg);

	if( sscanf(p, "%d\t%n", &reg->account_id, &n) != 1 || reg->account_id <= 0 )
		return 1;

	for(j = 0, p += n; j < ACCOUNT_REG_NUM; j++, p += n) {
		if( sscanf(p,"%255[^,],%d%n",buf,&v,&n) != 2 )
			break;
		strncpy(reg->reg[j].str, buf, 32);
		reg->reg[j].str[31] = '\0';	// force \0 terminal
		reg->reg[j].value   = v;
		if(p[n] != ' ')
			break;
		n++;
	}
	reg->reg_num = j;
	return 0;
}

#ifdef TXT_JOURNAL
// ==========================================
// アカウント変数のジャーナルのロールフォワード用コールバック関数
// ------------------------------------------
int accregdb_journal_rollforward( int key, void* buf, int flag )
{
	struct accreg* reg = (struct accreg *)numdb_search( accreg_db, key );

	// 念のためチェック
	if( flag == JOURNAL_FLAG_WRITE && key != ((struct accreg*)buf)->account_id )
	{
		printf("inter: accreg_journal: key != account_id !\n");
		return 0;
	}

	// データの置き換え
	if( reg )
	{
		if( flag == JOURNAL_FLAG_DELETE ) {
			numdb_erase( accreg_db, key );
			aFree( reg );
		} else {
			memcpy( reg, buf, sizeof(struct accreg) );
		}
		return 1;
	}

	// 追加
	if( flag != JOURNAL_FLAG_DELETE )
	{
		reg = (struct accreg*) aCalloc( 1, sizeof( struct accreg ) );
		memcpy( reg, buf, sizeof(struct accreg) );
		numdb_insert( accreg_db, key, reg );
		return 1;
	}

	return 0;
}
int accregdb_txt_sync(void);
#endif

/*==========================================
 * アカウント変数の読み込み
 *------------------------------------------
 */
static bool accregdb_txt_read(void)
{
	FILE *fp;
	bool ret = true;

	accreg_db = numdb_init();

	if((fp = fopen(accreg_txt, "r")) == NULL) {
		printf("accregdb_txt_read: open [%s] failed !\n", accreg_txt);
		ret = false;
	} else {
		int count = 0;
		char line[8192];

		while(fgets(line, sizeof(line), fp)) {
			struct accreg *reg = (struct accreg *)aCalloc(1, sizeof(struct accreg));

			if(accregdb_fromstr(line, reg) == 0 && reg->account_id > 0) {
				numdb_insert(accreg_db, reg->account_id, reg);
			} else {
				printf("inter: accreg: broken data [%s] line %d\n", accreg_txt, count);
				aFree(reg);
			}
			count++;
		}
		fclose(fp);
	}

#ifdef TXT_JOURNAL
	if( accreg_journal_enable )
	{
		// ジャーナルデータのロールフォワード
		if( journal_load( &accreg_journal, sizeof(struct accreg), accreg_journal_file ) )
		{
			int c = journal_rollforward( &accreg_journal, accregdb_journal_rollforward );

			printf("inter: accreg_journal: roll-forward (%d)\n", c );

			// ロールフォワードしたので、txt データを保存する ( journal も新規作成される)
			accregdb_txt_sync();
		}
		else
		{
			// ジャーナルを新規作成する
			journal_final( &accreg_journal );
			journal_create( &accreg_journal, sizeof(struct accreg), accreg_journal_cache, accreg_journal_file );
		}
	}
#endif

	return ret;
}

/*==========================================
 * 同期
 *------------------------------------------
 */
static int accregdb_txt_sync_sub(void *key, void *data, va_list ap)
{
	char line[8192];
	FILE *fp;
	struct accreg *reg = (struct accreg *)data;

	if(reg->reg_num > 0) {
		accregdb_tostr(line, reg);
		fp = va_arg(ap, FILE *);
		fprintf(fp, "%s" NEWLINE, line);
	}
	return 0;
}

int accregdb_txt_sync(void)
{
	FILE *fp;
	int lock;

	if( !accreg_db )
		return 1;

	if( (fp = lock_fopen(accreg_txt, &lock)) == NULL ) {
		printf("accregdb_txt_sync: can't write [%s] !!! data is lost !!!\n", accreg_txt);
		return 1;
	}
	numdb_foreach(accreg_db, accregdb_txt_sync_sub, fp);
	lock_fclose(fp, accreg_txt, &lock);

#ifdef TXT_JOURNAL
	if( accreg_journal_enable )
	{
		// コミットしたのでジャーナルを新規作成する
		journal_final( &accreg_journal );
		journal_create( &accreg_journal, sizeof(struct accreg), accreg_journal_cache, accreg_journal_file );
	}
#endif

	return 0;
}

/*==========================================
 * アカウント変数のロード
 *------------------------------------------
 */
const struct accreg* accregdb_txt_load(int account_id)
{
	return (const struct accreg *)numdb_search(accreg_db, account_id);
}

/*==========================================
 * セーブ
 *------------------------------------------
 */
bool accregdb_txt_save(struct accreg *reg2)
{
	struct accreg* reg1;

	nullpo_retr(false, reg2);

	reg1 = (struct accreg *)numdb_search(accreg_db, reg2->account_id);
	if(reg1 == NULL) {
		reg1 = (struct accreg *)aMalloc(sizeof(struct accreg));
		numdb_insert(accreg_db, reg2->account_id, reg1);
	}
	memcpy(reg1, reg2, sizeof(struct accreg));

#ifdef TXT_JOURNAL
	if( accreg_journal_enable )
		journal_write( &accreg_journal, reg2->account_id, reg2 );
#endif

	return true;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
static int accregdb_txt_final_sub(void *key, void *data, va_list ap)
{
	struct accreg *reg = (struct accreg *)data;

	aFree(reg);

	return 0;
}

void accregdb_txt_final(void)
{
	if(accreg_db)
		numdb_final(accreg_db, accregdb_txt_final_sub);

#ifdef TXT_JOURNAL
	if( accreg_journal_enable )
		journal_final( &accreg_journal );
#endif
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
bool accregdb_txt_init(void)
{
	return accregdb_txt_read();
}
