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

#include "../int_storage.h"
#include "petdb_txt.h"
#include "guilddb_txt.h"
#include "storagedb_txt.h"

static struct dbt *storage_db = NULL;

// ファイル名のデフォルト
static char storage_txt[1024] = "save/storage.txt";
static char guild_storage_txt[1024] = "save/g_storage.txt";

#ifdef TXT_JOURNAL
static int storage_journal_enable = 1;
static struct journal storage_journal;
static char storage_journal_file[1024] = "./save/storage.journal";
static int storage_journal_cache = 1000;
static int guild_storage_journal_enable = 1;
static struct journal guild_storage_journal;
static char guild_storage_journal_file[1024] = "./save/g_storage.journal";
static int guild_storage_journal_cache = 1000;
#endif

/*==========================================
 * 設定ファイルの読込
 *------------------------------------------
 */
int storagedb_txt_config_read_sub(const char* w1,const char* w2)
{
	if(strcmpi(w1,"storage_txt")==0){
		strncpy(storage_txt, w2, sizeof(storage_txt) - 1);
	}
	else if(strcmpi(w1,"guild_storage_txt")==0){
		strncpy(guild_storage_txt, w2, sizeof(guild_storage_txt) - 1);
	}
#ifdef TXT_JOURNAL
	else if(strcmpi(w1,"storage_journal_enable")==0){
		storage_journal_enable = atoi( w2 );
	}
	else if(strcmpi(w1,"storage_journal_file")==0){
		strncpy( storage_journal_file, w2, sizeof(storage_journal_file) - 1 );
	}
	else if(strcmpi(w1,"storage_journal_cache_interval")==0){
		storage_journal_cache = atoi( w2 );
	}
	else if(strcmpi(w1,"guild_storage_journal_enable")==0){
		guild_storage_journal_enable = atoi( w2 );
	}
	else if(strcmpi(w1,"guild_storage_journal_file")==0){
		strncpy( guild_storage_journal_file, w2, sizeof(guild_storage_journal_file) - 1 );
	}
	else if(strcmpi(w1,"guild_storage_journal_cache_interval")==0){
		guild_storage_journal_cache = atoi( w2 );
	}
#endif
	else {
		return 0;
	}

	return 1;
}

/*==========================================
 * 倉庫データを文字列へ変換
 *------------------------------------------
 */
static int storage_tostr(char *str, struct storage *p)
{
	int i, f = 0;
	char *str_p = str;

	nullpo_retr(1, p);

	str_p += sprintf(str_p, "%d,%d\t", p->account_id, p->storage_amount);

	for(i = 0; i < MAX_STORAGE; i++) {
		if(p->store_item[i].nameid && p->store_item[i].amount) {
			str_p += sprintf(str_p, "%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u,%d ",
				p->store_item[i].id,p->store_item[i].nameid,p->store_item[i].amount,p->store_item[i].equip,
				p->store_item[i].identify,p->store_item[i].refine,p->store_item[i].attribute,
				p->store_item[i].card[0],p->store_item[i].card[1],p->store_item[i].card[2],p->store_item[i].card[3],
				p->store_item[i].opt[0].id,p->store_item[i].opt[0].val,p->store_item[i].opt[1].id,p->store_item[i].opt[1].val,p->store_item[i].opt[2].id,p->store_item[i].opt[2].val,
				p->store_item[i].opt[3].id,p->store_item[i].opt[3].val,p->store_item[i].opt[4].id,p->store_item[i].opt[4].val,
				p->store_item[i].limit,p->store_item[i].private_);
			f++;
		}
	}
	*(str_p++) = '\t';

	*str_p = '\0';
	if(!f)
		str[0] = 0;

	return 0;
}

/*==========================================
 * 倉庫データを文字列から変換
 *------------------------------------------
 */
static int storage_fromstr(char *str, struct storage *p)
{
	int tmp_int[23];
	int set, next, len, i;

	nullpo_retr(1, p);

	set = sscanf(str, "%d,%d%n", &tmp_int[0], &tmp_int[1], &next);
	p->storage_amount = tmp_int[1];

	if(set != 2)
		return 1;
	if(str[next] == '\n' || str[next] == '\r')
		return 0;
	next++;
	for(i = 0; str[next] && str[next] != '\t'; i++){
		// Auriga-1369以降の形式
		set = sscanf(str + next, "%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u,%d%n",
			&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],
			&tmp_int[4],&tmp_int[5],&tmp_int[6],
			&tmp_int[7],&tmp_int[8],&tmp_int[9],&tmp_int[10],
			&tmp_int[11],&tmp_int[12],&tmp_int[13],&tmp_int[14],&tmp_int[15],&tmp_int[16],
			&tmp_int[17],&tmp_int[18],&tmp_int[19],&tmp_int[20],
			&tmp_int[21],&tmp_int[22],&len);

		if(set != 23)
		{
			// Auriga-0300以降の形式
			tmp_int[11] = 0;	// opt[0].id
			tmp_int[12] = 0;	// opt[0].val
			tmp_int[13] = 0;	// opt[1].id
			tmp_int[14] = 0;	// opt[1].val
			tmp_int[15] = 0;	// opt[2].id
			tmp_int[16] = 0;	// opt[2].val
			tmp_int[17] = 0;	// opt[3].id
			tmp_int[18] = 0;	// opt[3].val
			tmp_int[19] = 0;	// opt[4].id
			tmp_int[20] = 0;	// opt[4].val
			tmp_int[22] = 0;	// private
			set = sscanf(str + next, "%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u%n",
				&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],
				&tmp_int[4],&tmp_int[5],&tmp_int[6],
				&tmp_int[7],&tmp_int[8],&tmp_int[9],&tmp_int[10],
				&tmp_int[21],&len);
			if(set != 12) {
				tmp_int[21] = 0;	// limit
				set = sscanf(str + next, "%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d%n",
					&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],
					&tmp_int[4],&tmp_int[5],&tmp_int[6],
					&tmp_int[7],&tmp_int[8],&tmp_int[9],&tmp_int[10],&len);
				if(set != 11)
					return 1;
			}
		}
		if(i < MAX_STORAGE) {
			p->store_item[i].id         = (unsigned int)tmp_int[0];
			p->store_item[i].nameid     = tmp_int[1];
			p->store_item[i].amount     = tmp_int[2];
			p->store_item[i].equip      = (unsigned int)tmp_int[3];
			p->store_item[i].identify   = tmp_int[4];
			p->store_item[i].refine     = tmp_int[5];
			p->store_item[i].attribute  = tmp_int[6];
			p->store_item[i].card[0]    = tmp_int[7];
			p->store_item[i].card[1]    = tmp_int[8];
			p->store_item[i].card[2]    = tmp_int[9];
			p->store_item[i].card[3]    = tmp_int[10];
			p->store_item[i].opt[0].id  = tmp_int[11];
			p->store_item[i].opt[0].val = tmp_int[12];
			p->store_item[i].opt[1].id  = tmp_int[13];
			p->store_item[i].opt[1].val = tmp_int[14];
			p->store_item[i].opt[2].id  = tmp_int[15];
			p->store_item[i].opt[2].val = tmp_int[16];
			p->store_item[i].opt[3].id  = tmp_int[17];
			p->store_item[i].opt[3].val = tmp_int[18];
			p->store_item[i].opt[4].id  = tmp_int[19];
			p->store_item[i].opt[4].val = tmp_int[20];
			p->store_item[i].limit      = (unsigned int)tmp_int[21];
			p->store_item[i].private_   = tmp_int[22];
		}
		next += len;
		if(str[next] == ' ')
			next++;
	}
	return 0;
}

/*==========================================
 * アカウントIDから倉庫データをロード
 * （新規倉庫追加可能）
 *------------------------------------------
 */
const struct storage* storagedb_txt_load(int account_id)
{
	struct storage *s = (struct storage *)numdb_search(storage_db, account_id);

	if(s == NULL) {
		s = (struct storage *)aCalloc(1, sizeof(struct storage));
		s->account_id = account_id;
		numdb_insert(storage_db, s->account_id, s);
	}
	return s;
}

/*==========================================
 * 倉庫データのセーブ
 *------------------------------------------
 */
bool storagedb_txt_save(struct storage *s2)
{
	struct storage *s1;

	nullpo_retr(false, s2);

	s1 = (struct storage *)numdb_search(storage_db, s2->account_id);
	if(s1 == NULL) {
		s1 = (struct storage *)aCalloc(1, sizeof(struct storage));
		s1->account_id = s2->account_id;
		numdb_insert(storage_db, s2->account_id, s1);
	}
	memcpy(s1, s2, sizeof(struct storage));
#ifdef TXT_JOURNAL
	if( storage_journal_enable )
		journal_write( &storage_journal, s1->account_id, s1 );
#endif
	return true;
}

/*==========================================
 * 倉庫データの同期
 *------------------------------------------
 */
static int storagedb_txt_sync_sub(void *key, void *data, va_list ap)
{
	char line[65536];
	FILE *fp;

	storage_tostr(line, (struct storage *)data);
	fp = va_arg(ap, FILE *);
	if(*line)
		fprintf(fp, "%s" NEWLINE, line);

	return 0;
}

int storagedb_txt_sync(void)
{
	FILE *fp;
	int lock;

	if( !storage_db )
		return 1;

	if( (fp = lock_fopen(storage_txt, &lock)) == NULL ) {
		printf("storagedb_txt_sync: can't write [%s] !!! data is lost !!!\n", storage_txt);
		return 1;
	}
	numdb_foreach(storage_db, storagedb_txt_sync_sub, fp);
	lock_fclose(fp, storage_txt, &lock);

#ifdef TXT_JOURNAL
	if( storage_journal_enable )
	{
		// コミットしたのでジャーナルを新規作成する
		journal_final( &storage_journal );
		journal_create( &storage_journal, sizeof(struct storage), storage_journal_cache, storage_journal_file );
	}
#endif
	return 0;
}

/*==========================================
 * 倉庫データ削除
 *------------------------------------------
 */
bool storagedb_txt_delete(int account_id)
{
	struct storage *s = (struct storage *)numdb_search(storage_db, account_id);

	if(s) {
		int i;
		for(i = 0; i < s->storage_amount; i++) {
			// ペット削除
			if(s->store_item[i].card[0] == (short)0xff00)
				petdb_delete(*((int *)(&s->store_item[i].card[1])));
		}
		numdb_erase(storage_db, account_id);
		aFree(s);
#ifdef TXT_JOURNAL
		if( storage_journal_enable )
			journal_write( &storage_journal, account_id, NULL );
#endif
	}
	return true;
}

/*==========================================
 * ギルド倉庫データを文字列へ変換
 *------------------------------------------
 */
static int gstorage_tostr(char *str, struct guild_storage *p)
{
	int i, f = 0;
	char *str_p = str;

	nullpo_retr(1, p);

	str_p += sprintf(str, "%d,%d\t", p->guild_id, p->storage_amount);

	for(i = 0; i < MAX_GUILD_STORAGE; i++) {
		if(p->store_item[i].nameid && p->store_item[i].amount) {
			str_p += sprintf(str_p, "%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u,%d ",
				p->store_item[i].id,p->store_item[i].nameid,p->store_item[i].amount,p->store_item[i].equip,
				p->store_item[i].identify,p->store_item[i].refine,p->store_item[i].attribute,
				p->store_item[i].card[0],p->store_item[i].card[1],p->store_item[i].card[2],p->store_item[i].card[3],
				p->store_item[i].opt[0].id,p->store_item[i].opt[0].val,p->store_item[i].opt[1].id,p->store_item[i].opt[1].val,p->store_item[i].opt[2].id,p->store_item[i].opt[2].val,
				p->store_item[i].opt[3].id,p->store_item[i].opt[3].val,p->store_item[i].opt[4].id,p->store_item[i].opt[4].val,
				p->store_item[i].limit,p->store_item[i].private_);
			f++;
		}
	}
	*(str_p++) = '\t';

	*str_p = '\0';
	if(!f)
		str[0] = 0;

	return 0;
}

/*==========================================
 * ギルド倉庫データを文字列から変換
 *------------------------------------------
 */
static int gstorage_fromstr(char *str, struct guild_storage *p)
{
	int tmp_int[23];
	int set, next, len, i;

	nullpo_retr(1, p);

	set = sscanf(str, "%d,%d%n", &tmp_int[0], &tmp_int[1], &next);
	p->storage_amount = tmp_int[1];

	if(set != 2)
		return 1;
	if(str[next] == '\n' || str[next] == '\r')
		return 0;
	next++;
	for(i = 0; str[next] && str[next] != '\t'; i++) {
		// Auriga-1369以降の形式
		set = sscanf(str + next, "%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u,%d%n",
			&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],
			&tmp_int[4],&tmp_int[5],&tmp_int[6],
			&tmp_int[7],&tmp_int[8],&tmp_int[9],&tmp_int[10],
			&tmp_int[11],&tmp_int[12],&tmp_int[13],&tmp_int[14],&tmp_int[15],&tmp_int[16],
			&tmp_int[17],&tmp_int[18],&tmp_int[19],&tmp_int[20],
			&tmp_int[21],&tmp_int[22],&len);

		if(set != 23)
		{
			// Auriga-0300以降の形式
			tmp_int[11] = 0;	// opt[0].id
			tmp_int[12] = 0;	// opt[0].val
			tmp_int[13] = 0;	// opt[1].id
			tmp_int[14] = 0;	// opt[1].val
			tmp_int[15] = 0;	// opt[2].id
			tmp_int[16] = 0;	// opt[2].val
			tmp_int[17] = 0;	// opt[3].id
			tmp_int[18] = 0;	// opt[3].val
			tmp_int[19] = 0;	// opt[4].id
			tmp_int[20] = 0;	// opt[4].val
			tmp_int[22] = 0;	// private
			set = sscanf(str + next, "%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u%n",
				&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],
				&tmp_int[4],&tmp_int[5],&tmp_int[6],
				&tmp_int[7],&tmp_int[8],&tmp_int[9],&tmp_int[10],
				&tmp_int[21],&len);
			if(set != 12) {
				tmp_int[21] = 0;	// limit
				set = sscanf(str + next, "%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d%n",
					&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],
					&tmp_int[4],&tmp_int[5],&tmp_int[6],
					&tmp_int[7],&tmp_int[8],&tmp_int[9],&tmp_int[10],&len);
				if(set != 11)
					return 1;
			}
		}
		if(i < MAX_GUILD_STORAGE) {
			p->store_item[i].id         = (unsigned int)tmp_int[0];
			p->store_item[i].nameid     = tmp_int[1];
			p->store_item[i].amount     = tmp_int[2];
			p->store_item[i].equip      = (unsigned int)tmp_int[3];
			p->store_item[i].identify   = tmp_int[4];
			p->store_item[i].refine     = tmp_int[5];
			p->store_item[i].attribute  = tmp_int[6];
			p->store_item[i].card[0]    = tmp_int[7];
			p->store_item[i].card[1]    = tmp_int[8];
			p->store_item[i].card[2]    = tmp_int[9];
			p->store_item[i].card[3]    = tmp_int[10];
			p->store_item[i].opt[0].id  = tmp_int[11];
			p->store_item[i].opt[0].val = tmp_int[12];
			p->store_item[i].opt[1].id  = tmp_int[13];
			p->store_item[i].opt[1].val = tmp_int[14];
			p->store_item[i].opt[2].id  = tmp_int[15];
			p->store_item[i].opt[2].val = tmp_int[16];
			p->store_item[i].opt[3].id  = tmp_int[17];
			p->store_item[i].opt[3].val = tmp_int[18];
			p->store_item[i].opt[4].id  = tmp_int[19];
			p->store_item[i].opt[4].val = tmp_int[20];
			p->store_item[i].limit      = (unsigned int)tmp_int[21];
			p->store_item[i].private_   = tmp_int[22];
		}
		next += len;
		if(str[next] == ' ')
			next++;
	}
	return 0;
}

/*==========================================
 * ギルドIDからギルド倉庫データを取得
 *------------------------------------------
 */
const struct guild_storage *gstoragedb_txt_load(int guild_id)
{
	struct guild_storage *gs = NULL;

	if(guilddb_load_num(guild_id) != NULL) {
		gs = (struct guild_storage *)numdb_search(gstorage_db, guild_id);
		if(gs == NULL) {
			gs = (struct guild_storage *)aCalloc(1, sizeof(struct guild_storage));
			gs->guild_id = guild_id;
			gs->last_fd  = -1;
			numdb_insert(gstorage_db, gs->guild_id, gs);
		}
	}
	return gs;
}

/*==========================================
 * ギルド倉庫データのセーブ
 *------------------------------------------
 */
bool gstoragedb_txt_save(struct guild_storage *gs2, int easy)
{
	struct guild_storage *gs1;

	nullpo_retr(false, gs2);

	gs1 = (struct guild_storage *)numdb_search(gstorage_db,gs2->guild_id);
	if(gs1 == NULL) {
		gs1 = (struct guild_storage *)aCalloc(1, sizeof(struct guild_storage));
		gs1->guild_id = gs2->guild_id;
		gs1->last_fd  = -1;
		numdb_insert(gstorage_db, gs1->guild_id, gs1);
	}
	memcpy(gs1, gs2, sizeof(struct guild_storage));
#ifdef TXT_JOURNAL
	if( storage_journal_enable )
		journal_write( &storage_journal, gs1->guild_id, gs1 );
#endif
	return true;
}

/*==========================================
 * ギルド倉庫データの同期
 *------------------------------------------
 */
static int gstoragedb_txt_sync_sub(void *key, void *data, va_list ap)
{
	char line[65536];
	FILE *fp;
	struct guild_storage *gs = (struct guild_storage *)data;

	if(guilddb_load_num(gs->guild_id) != NULL) {
		gstorage_tostr(line, gs);
		fp = va_arg(ap, FILE *);
		if(*line)
			fprintf(fp, "%s" NEWLINE, line);
	}
	return 0;
}

int gstoragedb_txt_sync(void)
{
	FILE *fp;
	int lock;

	if( !gstorage_db )
		return 1;

	if( (fp = lock_fopen(guild_storage_txt, &lock)) == NULL ) {
		printf("gstoragedb_txt_sync: can't write [%s] !!! data is lost !!!\n", guild_storage_txt);
		return 1;
	}
	numdb_foreach(gstorage_db, gstoragedb_txt_sync_sub, fp);
	lock_fclose(fp, guild_storage_txt, &lock);

#ifdef TXT_JOURNAL
	if( guild_storage_journal_enable )
	{
		// コミットしたのでジャーナルを新規作成する
		journal_final( &guild_storage_journal );
		journal_create( &guild_storage_journal, sizeof(struct guild_storage),
						 guild_storage_journal_cache, guild_storage_journal_file );
	}
#endif
	return 0;
}

/*==========================================
 * ギルド倉庫データ削除
 *------------------------------------------
 */
bool gstoragedb_txt_delete(int guild_id)
{
	struct guild_storage *gs = (struct guild_storage *)numdb_search(gstorage_db,guild_id);

	if(gs) {
		int i;
		for(i = 0; i < gs->storage_amount; i++) {
			// ペット削除
			if(gs->store_item[i].card[0] == (short)0xff00)
				petdb_delete(*((int *)(&gs->store_item[i].card[1])));
		}
		numdb_erase(gstorage_db, guild_id);
		aFree(gs);
#ifdef TXT_JOURNAL
		if( guild_storage_journal_enable )
			journal_write( &guild_storage_journal, guild_id, NULL );
#endif
	}
	return true;
}

#ifdef TXT_JOURNAL
// ==========================================
// 倉庫データのジャーナルのロールフォワード用コールバック関数
// ------------------------------------------
int storage_journal_rollforward( int key, void* buf, int flag )
{
	struct storage* s = (struct storage *)numdb_search( storage_db, key );

	// 念のためチェック
	if( flag == JOURNAL_FLAG_WRITE && key != ((struct storage*)buf)->account_id )
	{
		printf("int_storage: storage_journal: key != account_id !\n");
		return 0;
	}

	// データの置き換え
	if( s )
	{
		if( flag == JOURNAL_FLAG_DELETE ) {
			numdb_erase( storage_db, key );
			aFree( s );
		} else {
			memcpy( s, buf, sizeof(struct storage) );
		}
		return 1;
	}

	// 追加
	if( flag != JOURNAL_FLAG_DELETE )
	{
		s = (struct storage*)aCalloc( 1, sizeof( struct storage ) );
		memcpy( s, buf, sizeof(struct storage) );
		numdb_insert( storage_db, key, s );
		return 1;
	}

	return 0;
}
int storagedb_txt_sync(void);

// ==========================================
// ギルド倉庫のジャーナルのロールフォワード用コールバック関数
// ------------------------------------------
int guild_storage_journal_rollforward( int key, void* buf, int flag )
{
	struct guild_storage* gs = (struct guild_storage *)numdb_search( gstorage_db, key );

	// 念のためチェック
	if( flag == JOURNAL_FLAG_WRITE && key != ((struct guild_storage*)buf)->guild_id )
	{
		printf("int_storage: guild_storage_journal: key != guild_id !\n");
		return 0;
	}

	// データの置き換え
	if( gs )
	{
		if( flag == JOURNAL_FLAG_DELETE ) {
			numdb_erase( gstorage_db, key );
			aFree( gs );
		} else {
			memcpy( gs, buf, sizeof(struct guild_storage) );
		}
		return 1;
	}

	// 追加
	if( flag != JOURNAL_FLAG_DELETE )
	{
		gs = (struct guild_storage*)aCalloc( 1, sizeof( struct guild_storage ) );
		memcpy( gs, buf, sizeof(struct guild_storage) );
		numdb_insert( gstorage_db, key, gs );
		return 1;
	}

	return 0;
}
int gstoragedb_txt_sync(void);
#endif

/*==========================================
 * 倉庫データファイルの読み込み
 *------------------------------------------
 */
static bool storagedb_txt_read(void)
{
	FILE *fp;
	bool ret = true;

	storage_db = numdb_init();

	fp = fopen(storage_txt, "r");
	if(fp == NULL) {
		printf("storagedb_txt_read: open [%s] failed !\n", storage_txt);
		ret = false;
	} else {
		int count = 0, tmp_int;
		char line[65536];

		while(fgets(line, sizeof(line) - 1, fp)) {
			struct storage *s;
			if(sscanf(line, "%d", &tmp_int) < 1)
				continue;
			s = (struct storage *)aCalloc(1, sizeof(struct storage));
			s->account_id = tmp_int;
			if(s->account_id > 0 && storage_fromstr(line, s) == 0) {
				numdb_insert(storage_db, s->account_id, s);
			} else {
				printf("int_storage: broken data [%s] line %d\n", storage_txt, count);
				aFree(s);
			}
			count++;
		}
		fclose(fp);
	}

#ifdef TXT_JOURNAL
	if( storage_journal_enable )
	{
		// ジャーナルデータのロールフォワード
		if( journal_load( &storage_journal, sizeof(struct storage), storage_journal_file ) )
		{
			int c = journal_rollforward( &storage_journal, storage_journal_rollforward );

			printf("int_storage: storage_journal: roll-forward (%d)\n", c );

			// ロールフォワードしたので、txt データを保存する ( journal も新規作成される)
			storagedb_txt_sync();
		}
		else
		{
			// ジャーナルを新規作成する
			journal_final( &storage_journal );
			journal_create( &storage_journal, sizeof(struct storage), storage_journal_cache, storage_journal_file );
		}
	}
#endif

	return ret;
}

/*==========================================
 * ギルド倉庫データファイルの読み込み
 *------------------------------------------
 */
static bool gstoragedb_txt_read(void)
{
	FILE *fp;
	bool ret = true;

	gstorage_db = numdb_init();

	fp = fopen(guild_storage_txt, "r");
	if(fp == NULL) {
		printf("gstoragedb_txt_read: open [%s] failed !\n", guild_storage_txt);
		ret = false;
	} else {
		int count = 0, tmp_int;
		char line[65536];

		while(fgets(line, sizeof(line) - 1, fp)) {
			struct guild_storage *gs;
			if(sscanf(line, "%d", &tmp_int) < 1)
				continue;
			gs = (struct guild_storage *)aCalloc(1, sizeof(struct guild_storage));
			gs->guild_id = tmp_int;
			gs->last_fd  = -1;
			if(gs->guild_id > 0 && gstorage_fromstr(line, gs) == 0) {
				numdb_insert(gstorage_db, gs->guild_id, gs);
			} else {
				printf("int_storage: broken data [%s] line %d\n", guild_storage_txt, count);
				aFree(gs);
			}
			count++;
		}
		fclose(fp);
	}

#ifdef TXT_JOURNAL
	if( guild_storage_journal_enable )
	{
		// ジャーナルデータのロールフォワード
		if( journal_load( &guild_storage_journal, sizeof(struct guild_storage), guild_storage_journal_file ) )
		{
			int c = journal_rollforward( &guild_storage_journal, guild_storage_journal_rollforward );

			printf("int_storage: guild_storage_journal: roll-forward (%d)\n", c );

			// ロールフォワードしたので、txt データを保存する ( journal も新規作成される)
			gstoragedb_txt_sync();
		}
		else
		{
			// ジャーナルを新規作成する
			journal_final( &guild_storage_journal );
			journal_create( &guild_storage_journal, sizeof(struct guild_storage),
							 guild_storage_journal_cache, guild_storage_journal_file );
		}
	}
#endif

	return ret;
}

/*==========================================
 * 倉庫データの終了
 *------------------------------------------
 */
static int storage_db_final(void *key, void *data, va_list ap)
{
	struct storage *s = (struct storage *)data;

	aFree(s);

	return 0;
}

void storagedb_txt_final(void)
{
	if(storage_db)
		numdb_final(storage_db, storage_db_final);

#ifdef TXT_JOURNAL
	if( storage_journal_enable )
	{
		journal_final( &storage_journal );
	}
#endif
}

/*==========================================
 * ギルド倉庫データの終了
 *------------------------------------------
 */
static int gstorage_db_final(void *key, void *data, va_list ap)
{
	struct guild_storage *gs = (struct guild_storage *)data;

	aFree(gs);

	return 0;
}

void gstoragedb_txt_final(void)
{
	if(gstorage_db)
		numdb_final(gstorage_db, gstorage_db_final);

#ifdef TXT_JOURNAL
	if( guild_storage_journal_enable )
	{
		journal_final( &guild_storage_journal );
	}
#endif
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
bool storagedb_txt_init(void)
{
	bool result = false;

	result = storagedb_txt_read();

	return (gstoragedb_txt_read() && result)? true: false;
}
