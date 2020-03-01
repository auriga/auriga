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
#include "lock.h"
#include "malloc.h"
#include "journal.h"
#include "utils.h"
#include "nullpo.h"

#include "homundb_txt.h"

static struct dbt *homun_db = NULL;

static char homun_txt[1024] = "save/homun.txt";
static int homun_newid = 100;

#ifdef TXT_JOURNAL
static int homun_journal_enable = 1;
static struct journal homun_journal;
static char homun_journal_file[1024] = "./save/homun.journal";
static int homun_journal_cache = 1000;
#endif

/*==========================================
 * 設定ファイルの読込
 *------------------------------------------
 */
int homundb_txt_config_read_sub(const char* w1,const char *w2)
{
	if(strcmpi(w1,"homun_txt")==0){
		strncpy(homun_txt, w2, sizeof(homun_txt) - 1);
	}
#ifdef TXT_JOURNAL
	else if(strcmpi(w1,"homun_journal_enable")==0){
		homun_journal_enable = atoi( w2 );
	}
	else if(strcmpi(w1,"homun_journal_file")==0){
		strncpy( homun_journal_file, w2, sizeof(homun_journal_file) - 1 );
	}
	else if(strcmpi(w1,"homun_journal_cache_interval")==0){
		homun_journal_cache = atoi( w2 );
	}
#endif
	else {
		return 0;
	}

	return 1;
}

/*==========================================
 * ホムデータを文字列へ変換
 *------------------------------------------
 */
static int homun_tostr(char *str, struct mmo_homunstatus *h)
{
	int i;
	char *str_p = str;
	unsigned short sk_lv;

	nullpo_retr(1, h);

	if(h->hungry < 0)
		h->hungry = 0;
	else if(h->hungry > 100)
		h->hungry = 100;
	if(h->intimate < 0)
		h->intimate = 0;
	else if(h->intimate > 100000)
		h->intimate = 100000;

	str_p += sprintf(str, "%d,%d,%s\t%d,%d\t%d,%d,%d,%d,%d,%d\t%d,%d,%d,%d,%d,%d\t%d,%d,%d,%d,%d,%d\t%d,%d\t%d,%d,%d,%d,%d",
		h->homun_id,h->class_,h->name,
		h->account_id,h->char_id,
		h->base_level,h->base_exp,h->max_hp,h->hp,h->max_sp,h->sp,
		h->str,h->agi,h->vit,h->int_,h->dex,h->luk,
		h->f_str,h->f_agi,h->f_vit,h->f_int,h->f_dex,h->f_luk,
		h->status_point,h->skill_point,
		h->equip,h->intimate,h->hungry,h->rename_flag,h->incubate);

	*(str_p++) = '\t';

	for( i= 0; i < MAX_HOMSKILL; i++) {
		if(h->skill[i].id && h->skill[i].flag != 1) {
			sk_lv = (h->skill[i].flag == 0)? h->skill[i].lv: h->skill[i].flag - 2;
			str_p += sprintf(str_p, "%d,%d ", h->skill[i].id, sk_lv);
		}
	}
	*(str_p++) = '\t';

	*str_p = '\0';
	return 0;
}

/*==========================================
 * ホムデータを文字列から変換
 *------------------------------------------
 */
static int homun_fromstr(char *str, struct mmo_homunstatus *h)
{
	int i, s, next, len;
	int tmp_int[29];
	char tmp_str[256];

	nullpo_retr(1, h);

	memset(h, 0, sizeof(struct mmo_homunstatus));

	// Auriga-0594以降の形式
	s = sscanf(str, "%d,%d,%255[^\t]\t%d,%d\t%d,%d,%d,%d,%d,%d\t%d,%d,%d,%d,%d,%d\t%d,%d,%d,%d,%d,%d\t%d,%d\t%d,%d,%d,%d,%d%n",
		&tmp_int[0],&tmp_int[1],tmp_str,
		&tmp_int[2],&tmp_int[3],
		&tmp_int[4],&tmp_int[5],&tmp_int[6],&tmp_int[7],&tmp_int[8],&tmp_int[9],
		&tmp_int[10],&tmp_int[11],&tmp_int[12],&tmp_int[13],&tmp_int[14],&tmp_int[15],
		&tmp_int[16],&tmp_int[17],&tmp_int[18],&tmp_int[19],&tmp_int[20],&tmp_int[21],
		&tmp_int[22],&tmp_int[23],
		&tmp_int[24],&tmp_int[25],&tmp_int[26],&tmp_int[27],&tmp_int[28],&next
	);

	if(s != 30) {
		tmp_int[16] = 0;	// f_str
		tmp_int[17] = 0;	// f_agi
		tmp_int[18] = 0;	// f_vit
		tmp_int[19] = 0;	// f_int
		tmp_int[20] = 0;	// f_dex
		tmp_int[21] = 0;	// f_luk
		s = sscanf(str, "%d,%d,%255[^\t]\t%d,%d\t%d,%d,%d,%d,%d,%d\t%d,%d,%d,%d,%d,%d\t%d,%d\t%d,%d,%d,%d,%d%n",
			&tmp_int[0],&tmp_int[1],tmp_str,
			&tmp_int[2],&tmp_int[3],
			&tmp_int[4],&tmp_int[5],&tmp_int[6],&tmp_int[7],&tmp_int[8],&tmp_int[9],
			&tmp_int[10],&tmp_int[11],&tmp_int[12],&tmp_int[13],&tmp_int[14],&tmp_int[15],
			&tmp_int[22],&tmp_int[23],
			&tmp_int[24],&tmp_int[25],&tmp_int[26],&tmp_int[27],&tmp_int[28],&next
		);

		if(s != 24)
			return 1;
	}

	h->homun_id     = tmp_int[0];
	h->class_       = tmp_int[1];
	strncpy(h->name, tmp_str, 24);
	h->name[23] = '\0';	// force \0 terminal
	h->account_id   = tmp_int[2];
	h->char_id      = tmp_int[3];
	h->base_level   = tmp_int[4];
	h->base_exp     = tmp_int[5];
	h->max_hp       = tmp_int[6];
	h->hp           = tmp_int[7];
	h->max_sp       = tmp_int[8];
	h->sp           = tmp_int[9];
	h->str          = tmp_int[10];
	h->agi          = tmp_int[11];
	h->vit          = tmp_int[12];
	h->int_         = tmp_int[13];
	h->dex          = tmp_int[14];
	h->luk          = tmp_int[15];
	h->f_str        = tmp_int[16];
	h->f_agi        = tmp_int[17];
	h->f_vit        = tmp_int[18];
	h->f_int        = tmp_int[19];
	h->f_dex        = tmp_int[20];
	h->f_luk        = tmp_int[21];
	h->status_point = tmp_int[22];
	h->skill_point  = tmp_int[23];
	h->equip        = tmp_int[24];
	h->intimate     = tmp_int[25];
	h->hungry       = tmp_int[26];
	h->rename_flag  = tmp_int[27];
	h->incubate     = tmp_int[28];
	h->option       = 0;

	if(h->hungry < 0)
		h->hungry = 0;
	else if(h->hungry > 100)
		h->hungry = 100;
	if(h->intimate < 0)
		h->intimate = 0;
	else if(h->intimate > 100000)
		h->intimate = 100000;

	if(str[next] == '\n' || str[next] == '\r')
		return 1;	// スキル情報なし

	next++;
	for(i = 0; str[next] && str[next] != '\t'; i++) {
		int n;
		if(sscanf(str + next, "%d,%d%n", &tmp_int[0], &tmp_int[1], &len) != 2)
			return 0;

		n = tmp_int[0] - HOM_SKILLID;
		if(n >= 0 && n < MAX_HOMSKILL) {
			h->skill[n].id = tmp_int[0];
			h->skill[n].lv = tmp_int[1];
		} else {
			printf("homun_fromstr: invaild skill id: %d\n", tmp_int[0]);
		}
		next += len;
		if(str[next] == ' ')
			next++;
	}
	return 0;
}

#ifdef TXT_JOURNAL
// ==========================================
// ホムデータのジャーナルのロールフォワード用コールバック関数
// ------------------------------------------
int homun_journal_rollforward( int key, void* buf, int flag )
{
	struct mmo_homunstatus* h = (struct mmo_homunstatus *)numdb_search( homun_db, key );

	// 念のためチェック
	if( flag == JOURNAL_FLAG_WRITE && key != ((struct mmo_homunstatus*)buf)->homun_id )
	{
		printf("int_homun: journal: key != homun_id !\n");
		return 0;
	}

	// データの置き換え
	if( h )
	{
		if( flag == JOURNAL_FLAG_DELETE ) {
			numdb_erase(homun_db, key);
			aFree(h);
		} else {
			memcpy( h, buf, sizeof(struct mmo_homunstatus) );
		}
		return 1;
	}

	// 追加
	if( flag != JOURNAL_FLAG_DELETE )
	{
		h = (struct mmo_homunstatus*) aCalloc( 1, sizeof( struct mmo_homunstatus ) );
		memcpy( h, buf, sizeof(struct mmo_homunstatus) );
		numdb_insert( homun_db, key, h );
		if( h->homun_id >= homun_newid)
			homun_newid=h->homun_id+1;
		return 1;
	}

	return 0;
}
int homundb_txt_sync(void);
#endif

/*==========================================
 * ホムデータファイルの読み込み
 *------------------------------------------
 */
static bool homundb_txt_read(void)
{
	FILE *fp;
	bool ret = true;

	homun_db = numdb_init();

	if((fp = fopen(homun_txt, "r")) == NULL) {
		printf("homundb_txt_read: open [%s] failed !\n", homun_txt);
		ret = false;
	} else {
		int count = 0;
		char line[8192];

		while(fgets(line, sizeof(line), fp)) {
			struct mmo_homunstatus *h = (struct mmo_homunstatus *)aCalloc(1, sizeof(struct mmo_homunstatus));
			if(homun_fromstr(line, h) == 0 && h->homun_id > 0) {
				if(h->homun_id >= homun_newid)
					homun_newid = h->homun_id + 1;
				numdb_insert(homun_db, h->homun_id, h);
			} else {
				printf("int_homun: broken data [%s] line %d\n", homun_txt, count);
				aFree(h);
			}
			count++;
		}
		fclose(fp);
	}

#ifdef TXT_JOURNAL
	if( homun_journal_enable )
	{
		// ジャーナルデータのロールフォワード
		if( journal_load( &homun_journal, sizeof(struct mmo_homunstatus), homun_journal_file ) )
		{
			int c = journal_rollforward( &homun_journal, homun_journal_rollforward );

			printf("int_homun: journal: roll-forward (%d)\n", c );

			// ロールフォワードしたので、txt データを保存する ( journal も新規作成される)
			homundb_txt_sync();
		}
		else
		{
			// ジャーナルを新規作成する
			journal_final( &homun_journal );
			journal_create( &homun_journal, sizeof(struct mmo_homunstatus), homun_journal_cache, homun_journal_file );
		}
	}
#endif

	return ret;
}

/*==========================================
 * 同期
 *------------------------------------------
 */
static int homundb_txt_sync_sub(void *key, void *data, va_list ap)
{
	char line[8192];
	FILE *fp;

	homun_tostr(line, (struct mmo_homunstatus *)data);
	fp = va_arg(ap, FILE *);
	fprintf(fp, "%s" NEWLINE, line);

	return 0;
}

int homundb_txt_sync(void)
{
	FILE *fp;
	int lock;

	if( !homun_db )
		return 1;

	if( (fp = lock_fopen(homun_txt, &lock)) == NULL ) {
		printf("homundb_txt_sync: can't write [%s] !!! data is lost !!!\n", homun_txt);
		return 1;
	}
	numdb_foreach(homun_db, homundb_txt_sync_sub, fp);
	lock_fclose(fp, homun_txt, &lock);

#ifdef TXT_JOURNAL
	if( homun_journal_enable )
	{
		// コミットしたのでジャーナルを新規作成する
		journal_final( &homun_journal );
		journal_create( &homun_journal, sizeof(struct mmo_homunstatus), homun_journal_cache, homun_journal_file );
	}
#endif

	return 0;
}

/*==========================================
 * ホム削除
 *------------------------------------------
 */
bool homundb_txt_delete(int homun_id)
{
	struct mmo_homunstatus *p = (struct mmo_homunstatus *)numdb_search(homun_db, homun_id);

	if(p == NULL)
		return false;

	numdb_erase(homun_db, homun_id);
	aFree(p);
	printf("homun_id: %d deleted\n", homun_id);

#ifdef TXT_JOURNAL
	if( homun_journal_enable )
		journal_write( &homun_journal, homun_id, NULL );
#endif

	return true;
}

/*==========================================
 * ホムIDからホムデータをロード
 *------------------------------------------
 */
const struct mmo_homunstatus* homundb_txt_load(int homun_id)
{
	return (const struct mmo_homunstatus *)numdb_search(homun_db, homun_id);
}

/*==========================================
 * セーブ
 *------------------------------------------
 */
bool homundb_txt_save(struct mmo_homunstatus *p2)
{
	struct mmo_homunstatus* p1;

	nullpo_retr(false, p2);

	p1 = (struct mmo_homunstatus *)numdb_search(homun_db,p2->homun_id);
	if(p1 == NULL) {
		p1 = (struct mmo_homunstatus *)aMalloc(sizeof(struct mmo_homunstatus));
		numdb_insert(homun_db, p2->homun_id, p1);
	}
	memcpy(p1, p2, sizeof(struct mmo_homunstatus));

#ifdef TXT_JOURNAL
	if( homun_journal_enable )
		journal_write( &homun_journal, p1->homun_id, p1 );
#endif
	return true;
}

/*==========================================
 * ホム作成
 *------------------------------------------
 */
bool homundb_txt_new(struct mmo_homunstatus *p2)
{
	struct mmo_homunstatus *p1;

	nullpo_retr(false, p2);

	p1 = (struct mmo_homunstatus *)aMalloc(sizeof(struct mmo_homunstatus));
	p2->homun_id = homun_newid++;

	memcpy(p1, p2, sizeof(struct mmo_homunstatus));
	numdb_insert(homun_db, p2->homun_id, p1);

	return true;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
static int homundb_txt_final_sub(void *key, void *data, va_list ap)
{
	struct mmo_homunstatus *p = (struct mmo_homunstatus *)data;

	aFree(p);

	return 0;
}

void homundb_txt_final(void)
{
	if(homun_db)
		numdb_final(homun_db, homundb_txt_final_sub);

#ifdef TXT_JOURNAL
	if( homun_journal_enable )
	{
		journal_final( &homun_journal );
	}
#endif
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
bool homundb_txt_init(void)
{
	return homundb_txt_read();
}
