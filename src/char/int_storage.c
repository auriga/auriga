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

#define _INT_STORAGE_C_

#include <string.h>
#include <stdlib.h>

#include "mmo.h"
#include "socket.h"
#include "db.h"
#include "lock.h"
#include "malloc.h"
#include "timer.h"
#include "journal.h"
#include "sqldbs.h"

#include "char.h"
#include "inter.h"
#include "int_storage.h"
#include "int_pet.h"
#include "int_guild.h"

static struct dbt *storage_db  = NULL;
static struct dbt *gstorage_db = NULL;

#ifdef TXT_ONLY

// ファイル名のデフォルト
static char storage_txt[1024]="save/storage.txt";
static char guild_storage_txt[1024]="save/g_storage.txt";

#ifdef TXT_JOURNAL
static int storage_journal_enable = 1;
static struct journal storage_journal;
static char storage_journal_file[1024]="./save/storage.journal";
static int storage_journal_cache = 1000;
static int guild_storage_journal_enable = 1;
static struct journal guild_storage_journal;
static char guild_storage_journal_file[1024]="./save/g_storage.journal";
static int guild_storage_journal_cache = 1000;
#endif

// ----------------------------------------------------------
// カプラ倉庫
// ----------------------------------------------------------

// 倉庫データを文字列に変換
static int storage_tostr(char *str,struct storage *p)
{
	int i,f=0;
	char *str_p = str;

	str_p += sprintf(str_p,"%d,%d\t",p->account_id,p->storage_amount);

	for(i=0;i<MAX_STORAGE;i++) {
		if(p->store_item[i].nameid && p->store_item[i].amount) {
			str_p += sprintf(str_p,"%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u ",
				p->store_item[i].id,p->store_item[i].nameid,p->store_item[i].amount,p->store_item[i].equip,
				p->store_item[i].identify,p->store_item[i].refine,p->store_item[i].attribute,
				p->store_item[i].card[0],p->store_item[i].card[1],p->store_item[i].card[2],p->store_item[i].card[3],
				p->store_item[i].limit);
			f++;
		}
	}
	*(str_p++)='\t';

	*str_p='\0';
	if(!f)
		str[0]=0;
	return 0;
}

// 文字列を倉庫データに変換
static int storage_fromstr(char *str,struct storage *p)
{
	int tmp_int[12];
	int set,next,len,i;

	set=sscanf(str,"%d,%d%n",&tmp_int[0],&tmp_int[1],&next);
	p->storage_amount=tmp_int[1];

	if(set!=2)
		return 1;
	if(str[next]=='\n' || str[next]=='\r')
		return 0;
	next++;
	for(i=0;str[next] && str[next]!='\t';i++){
		// Auriga-0300以降の形式
		set=sscanf(str+next,"%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u%n",
			&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],
			&tmp_int[4],&tmp_int[5],&tmp_int[6],
			&tmp_int[7],&tmp_int[8],&tmp_int[9],&tmp_int[10],&tmp_int[11],&len);
		if(set!=12) {
			tmp_int[11] = 0;	// limit
			set=sscanf(str+next,"%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d%n",
				&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],
				&tmp_int[4],&tmp_int[5],&tmp_int[6],
				&tmp_int[7],&tmp_int[8],&tmp_int[9],&tmp_int[10],&len);
			if(set!=11)
				return 1;
		}
		if(i < MAX_STORAGE) {
			p->store_item[i].id        = (unsigned int)tmp_int[0];
			p->store_item[i].nameid    = tmp_int[1];
			p->store_item[i].amount    = tmp_int[2];
			p->store_item[i].equip     = tmp_int[3];
			p->store_item[i].identify  = tmp_int[4];
			p->store_item[i].refine    = tmp_int[5];
			p->store_item[i].attribute = tmp_int[6];
			p->store_item[i].card[0]   = tmp_int[7];
			p->store_item[i].card[1]   = tmp_int[8];
			p->store_item[i].card[2]   = tmp_int[9];
			p->store_item[i].card[3]   = tmp_int[10];
			p->store_item[i].limit     = (unsigned int)tmp_int[11];
		}
		next+=len;
		if(str[next]==' ')
			next++;
	}
	return 0;
}

// アカウントから倉庫データインデックスを得る（新規倉庫追加可能）
const struct storage* storage_txt_load(int account_id)
{
	struct storage *s = (struct storage *)numdb_search(storage_db,account_id);

	if(s == NULL) {
		s = (struct storage *)aCalloc(1,sizeof(struct storage));
		s->account_id = account_id;
		numdb_insert(storage_db,s->account_id,s);
	}
	return s;
}

int storage_txt_save(struct storage *s2)
{
	struct storage *s1 = (struct storage *)numdb_search(storage_db,s2->account_id);

	if(s1 == NULL) {
		s1 = (struct storage *)aCalloc(1,sizeof(struct storage));
		s1->account_id = s2->account_id;
		numdb_insert(storage_db,s2->account_id,s1);
	}
	memcpy(s1,s2,sizeof(struct storage));
#ifdef TXT_JOURNAL
	if( storage_journal_enable )
		journal_write( &storage_journal, s1->account_id, s1 );
#endif
	return 1;
}

static int storage_txt_sync_sub(void *key,void *data,va_list ap)
{
	char line[65536];
	FILE *fp;

	storage_tostr(line,(struct storage *)data);
	fp=va_arg(ap,FILE *);
	if(*line)
		fprintf(fp,"%s" RETCODE,line);
	return 0;
}

// 倉庫データを書き込み
int storage_txt_sync(void)
{
	FILE *fp;
	int lock;

	if( !storage_db )
		return 1;

	if( (fp=lock_fopen(storage_txt,&lock))==NULL ){
		printf("int_storage: cant write [%s] !!! data is lost !!!\n",storage_txt);
		return 1;
	}
	numdb_foreach(storage_db,storage_txt_sync_sub,fp);
	lock_fclose(fp,storage_txt,&lock);
	//printf("int_storage: %s saved.\n",storage_txt);

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

// 倉庫データ削除
int storage_txt_delete(int account_id)
{
	struct storage *s = (struct storage *)numdb_search(storage_db,account_id);

	if(s) {
		int i;
		for(i=0;i<s->storage_amount;i++){
			if(s->store_item[i].card[0] == (short)0xff00)
				pet_delete(*((long *)(&s->store_item[i].card[1])));
		}
		numdb_erase(storage_db,account_id);
		aFree(s);
#ifdef TXT_JOURNAL
		if( storage_journal_enable )
			journal_write( &storage_journal, account_id, NULL );
#endif
	}
	return 0;
}

static int storage_db_final(void *key,void *data,va_list ap)
{
	struct storage *s = (struct storage *)data;

	aFree(s);

	return 0;
}

void storage_txt_final(void)
{
	if(storage_db)
		numdb_final(storage_db,storage_db_final);

#ifdef TXT_JOURNAL
	if( storage_journal_enable )
	{
		journal_final( &storage_journal );
	}
#endif
}

// ----------------------------------------------------------
// ギルド倉庫
// ----------------------------------------------------------

static int gstorage_tostr(char *str,struct guild_storage *p)
{
	int i,f=0;
	char *str_p = str;

	str_p+=sprintf(str,"%d,%d\t",p->guild_id,p->storage_amount);

	for(i=0;i<MAX_GUILD_STORAGE;i++) {
		if(p->store_item[i].nameid && p->store_item[i].amount) {
			str_p += sprintf(str_p,"%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u ",
				p->store_item[i].id,p->store_item[i].nameid,p->store_item[i].amount,p->store_item[i].equip,
				p->store_item[i].identify,p->store_item[i].refine,p->store_item[i].attribute,
				p->store_item[i].card[0],p->store_item[i].card[1],p->store_item[i].card[2],p->store_item[i].card[3],
				p->store_item[i].limit);
			f++;
		}
	}
	*(str_p++)='\t';

	*str_p='\0';
	if(!f)
		str[0]=0;
	return 0;
}

static int gstorage_fromstr(char *str,struct guild_storage *p)
{
	int tmp_int[12];
	int set,next,len,i;

	set=sscanf(str,"%d,%d%n",&tmp_int[0],&tmp_int[1],&next);
	p->storage_amount=tmp_int[1];

	if(set!=2)
		return 1;
	if(str[next]=='\n' || str[next]=='\r')
		return 0;
	next++;
	for(i=0;str[next] && str[next]!='\t';i++){
		// Auriga-0300以降の形式
		set=sscanf(str+next,"%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u%n",
			&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],
			&tmp_int[4],&tmp_int[5],&tmp_int[6],
			&tmp_int[7],&tmp_int[8],&tmp_int[9],&tmp_int[10],&tmp_int[11],&len);
		if(set!=12) {
			tmp_int[11] = 0;	// limit
			set=sscanf(str+next,"%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d%n",
				&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],
				&tmp_int[4],&tmp_int[5],&tmp_int[6],
				&tmp_int[7],&tmp_int[8],&tmp_int[9],&tmp_int[10],&len);
			if(set!=11)
				return 1;
		}
		if(i < MAX_GUILD_STORAGE) {
			p->store_item[i].id        = (unsigned int)tmp_int[0];
			p->store_item[i].nameid    = tmp_int[1];
			p->store_item[i].amount    = tmp_int[2];
			p->store_item[i].equip     = tmp_int[3];
			p->store_item[i].identify  = tmp_int[4];
			p->store_item[i].refine    = tmp_int[5];
			p->store_item[i].attribute = tmp_int[6];
			p->store_item[i].card[0]   = tmp_int[7];
			p->store_item[i].card[1]   = tmp_int[8];
			p->store_item[i].card[2]   = tmp_int[9];
			p->store_item[i].card[3]   = tmp_int[10];
			p->store_item[i].limit     = (unsigned int)tmp_int[11];
		}
		next+=len;
		if(str[next]==' ')
			next++;
	}
	return 0;
}

const struct guild_storage *gstorage_txt_load(int guild_id)
{
	struct guild_storage *gs = NULL;

	if(guild_load_num(guild_id) != NULL) {
		gs = (struct guild_storage *)numdb_search(gstorage_db,guild_id);
		if(gs == NULL) {
			gs = (struct guild_storage *)aCalloc(1,sizeof(struct guild_storage));
			gs->guild_id = guild_id;
			gs->last_fd  = -1;
			numdb_insert(gstorage_db,gs->guild_id,gs);
		}
	}
	return gs;
}

int gstorage_txt_save(struct guild_storage *gs2, int easy)
{
	struct guild_storage *gs1 = (struct guild_storage *)numdb_search(gstorage_db,gs2->guild_id);

	if(gs1 == NULL) {
		gs1 = (struct guild_storage *)aCalloc(1,sizeof(struct guild_storage));
		gs1->guild_id = gs2->guild_id;
		gs1->last_fd  = -1;
		numdb_insert(gstorage_db,gs1->guild_id,gs1);
	}
	memcpy(gs1,gs2,sizeof(struct guild_storage));
#ifdef TXT_JOURNAL
	if( storage_journal_enable )
		journal_write( &storage_journal, gs1->guild_id, gs1 );
#endif
	return 1;
}

static int gstorage_txt_sync_sub(void *key,void *data,va_list ap)
{
	char line[65536];
	FILE *fp;
	struct guild_storage *gs = (struct guild_storage *)data;

	if(guild_load_num(gs->guild_id) != NULL) {
		gstorage_tostr(line,gs);
		fp=va_arg(ap,FILE *);
		if(*line)
			fprintf(fp,"%s" RETCODE,line);
	}
	return 0;
}

// 倉庫データを書き込む
int gstorage_txt_sync(void)
{
	FILE *fp;
	int  lock;

	if( !gstorage_db )
		return 1;

	if( (fp=lock_fopen(guild_storage_txt,&lock))==NULL ){
		printf("int_storage: cant write [%s] !!! data is lost !!!\n",guild_storage_txt);
		return 1;
	}
	numdb_foreach(gstorage_db,gstorage_txt_sync_sub,fp);
	lock_fclose(fp,guild_storage_txt,&lock);
	//printf("int_storage: %s saved.\n",guild_storage_txt);

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

// ギルド倉庫データ削除
int gstorage_txt_delete(int guild_id)
{
	struct guild_storage *gs = (struct guild_storage *)numdb_search(gstorage_db,guild_id);

	if(gs) {
		int i;
		for(i=0;i<gs->storage_amount;i++){
			if(gs->store_item[i].card[0] == (short)0xff00)
				pet_delete(*((long *)(&gs->store_item[i].card[1])));
		}
		numdb_erase(gstorage_db,guild_id);
		aFree(gs);
#ifdef TXT_JOURNAL
		if( guild_storage_journal_enable )
			journal_write( &guild_storage_journal, guild_id, NULL );
#endif
	}
	return 0;
}

static int gstorage_db_final(void *key,void *data,va_list ap)
{
	struct guild_storage *gs = (struct guild_storage *)data;

	aFree(gs);

	return 0;
}

void gstorage_txt_final(void)
{
	if(gstorage_db)
		numdb_final(gstorage_db,gstorage_db_final);

#ifdef TXT_JOURNAL
	if( guild_storage_journal_enable )
	{
		journal_final( &guild_storage_journal );
	}
#endif
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

#endif

// 倉庫データを読み込む
int storage_txt_init(void)
{
	char line[65536];
	int c=0,tmp_int;
	struct storage *s;
	struct guild_storage *gs;
	FILE *fp;

	storage_db = numdb_init();

	fp=fopen(storage_txt,"r");
	if(fp==NULL){
		printf("cant't read : %s\n",storage_txt);
		return 1;
	}
	while(fgets(line,65535,fp)){
		if(sscanf(line,"%d",&tmp_int) < 1)
			continue;
		s = (struct storage *)aCalloc(1,sizeof(struct storage));
		s->account_id = tmp_int;
		if(s->account_id > 0 && storage_fromstr(line,s) == 0) {
			numdb_insert(storage_db,s->account_id,s);
		} else {
			printf("int_storage: broken data [%s] line %d\n",storage_txt,c);
			aFree(s);
		}
		c++;
	}
	fclose(fp);

#ifdef TXT_JOURNAL
	if( storage_journal_enable )
	{
		// ジャーナルデータのロールフォワード
		if( journal_load( &storage_journal, sizeof(struct storage), storage_journal_file ) )
		{
			int c = journal_rollforward( &storage_journal, storage_journal_rollforward );

			printf("int_storage: storage_journal: roll-forward (%d)\n", c );

			// ロールフォワードしたので、txt データを保存する ( journal も新規作成される)
			storage_txt_sync();
		}
		else
		{
			// ジャーナルを新規作成する
			journal_final( &storage_journal );
			journal_create( &storage_journal, sizeof(struct storage), storage_journal_cache, storage_journal_file );
		}
	}
#endif

	c = 0;
	gstorage_db = numdb_init();

	fp=fopen(guild_storage_txt,"r");
	if(fp==NULL){
		printf("cant't read : %s\n",guild_storage_txt);
		return 1;
	}
	while(fgets(line,65535,fp)){
		if(sscanf(line,"%d",&tmp_int) < 1)
			continue;
		gs = (struct guild_storage *)aCalloc(1,sizeof(struct guild_storage));
		gs->guild_id = tmp_int;
		gs->last_fd  = -1;
		if(gs->guild_id > 0 && gstorage_fromstr(line,gs) == 0) {
			numdb_insert(gstorage_db,gs->guild_id,gs);
		} else {
			printf("int_storage: broken data [%s] line %d\n",guild_storage_txt,c);
			aFree(gs);
		}
		c++;
	}
	fclose(fp);

#ifdef TXT_JOURNAL
	if( guild_storage_journal_enable )
	{
		// ジャーナルデータのロールフォワード
		if( journal_load( &guild_storage_journal, sizeof(struct guild_storage), guild_storage_journal_file ) )
		{
			int c = journal_rollforward( &guild_storage_journal, guild_storage_journal_rollforward );

			printf("int_storage: guild_storage_journal: roll-forward (%d)\n", c );

			// ロールフォワードしたので、txt データを保存する ( journal も新規作成される)
			gstorage_txt_sync();
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

	return 0;
}

void storage_txt_config_read_sub(const char* w1,const char* w2)
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
}

#define storage_init   storage_txt_init
#define storage_load   storage_txt_load
#define storage_save   storage_txt_save
#define storage_sync   storage_txt_sync
#define storage_delete storage_txt_delete
#define storage_final  storage_txt_final

#define gstorage_load   gstorage_txt_load
#define gstorage_save   gstorage_txt_save
#define gstorage_sync   gstorage_txt_sync
#define gstorage_delete gstorage_txt_delete
#define gstorage_final  gstorage_txt_final

#else /* TXT_ONLY */

int storage_sql_init(void)
{
	storage_db  = numdb_init();
	gstorage_db = numdb_init();
	return 0;
}

const struct storage* storage_sql_load(int account_id)
{
	struct storage *s = (struct storage *)numdb_search(storage_db,account_id);

	if(s == NULL) {
		s = (struct storage *)aCalloc(1,sizeof(struct storage));
		s->account_id = account_id;
		numdb_insert(storage_db,s->account_id,s);
		s->storage_amount = char_sql_loaditem(s->store_item,MAX_STORAGE,account_id,TABLE_NUM_STORAGE);
	}
	return s;
}

int storage_sql_save(struct storage *s2)
{
	const struct storage *s1 = storage_sql_load(s2->account_id);

	if(memcmp(s1,s2,sizeof(struct storage))) {
		struct storage *s3 = (struct storage *)numdb_search(storage_db, s2->account_id);
		char_sql_saveitem(s2->store_item,MAX_STORAGE,s2->account_id,TABLE_NUM_STORAGE);
		if(s3)
			memcpy(s3, s2, sizeof(struct storage));
	}
	return 1;
}

int storage_sql_sync(void)
{
	// nothing to do
	return 0;
}

int storage_sql_delete(int account_id)
{
	const struct storage *s = storage_sql_load(account_id);
	struct storage *s2;

	// ペット削除
	if(s) {
		int i;
		for(i=0;i<s->storage_amount;i++){
			if(s->store_item[i].card[0] == (short)0xff00)
				pet_delete(*((long *)(&s->store_item[i].card[1])));
		}
	}

	// delete
	sqldbs_query(&mysql_handle, "DELETE FROM `" STORAGE_TABLE "` WHERE `account_id`='%d'", account_id);

	s2 = (struct storage *)numdb_search(storage_db, account_id);
	if(s2) {
		numdb_erase(storage_db, account_id);
		aFree(s2);
	}
	return 1;
}

static int storage_db_final(void *key,void *data,va_list ap)
{
	struct storage *s = (struct storage *)data;

	aFree(s);

	return 0;
}

void storage_sql_final(void)
{
	if(storage_db)
		numdb_final(storage_db,storage_db_final);
}

const struct guild_storage *gstorage_sql_load(int guild_id)
{
	struct guild_storage *s = (struct guild_storage *)numdb_search(gstorage_db,guild_id);

	if(s == NULL) {
		s = (struct guild_storage *)aCalloc(1,sizeof(struct guild_storage));
		s->guild_id = guild_id;
		s->last_fd  = -1;
		numdb_insert(gstorage_db,s->guild_id,s);
		s->storage_amount = char_sql_loaditem(s->store_item,MAX_GUILD_STORAGE,guild_id,TABLE_NUM_GUILD_STORAGE);
	}
	return s;
}

int gstorage_sql_save(struct guild_storage *gs2, int easy)
{
	const struct guild_storage *gs1 = gstorage_sql_load(gs2->guild_id);

	if(memcmp(gs1,gs2,sizeof(struct guild_storage))) {
		struct guild_storage *gs3 = (struct guild_storage*)numdb_search( gstorage_db, gs2->guild_id );
		if(!easy) {
			char_sql_saveitem(gs2->store_item,MAX_GUILD_STORAGE,gs2->guild_id,TABLE_NUM_GUILD_STORAGE);
		}
		if(gs3)
			memcpy(gs3, gs2, sizeof(struct guild_storage));
	}
	return 1;
}

int gstorage_sql_sync(void)
{
	// nothing to do
	return 0;
}

int gstorage_sql_delete(int guild_id)
{
	const struct guild_storage *s = gstorage_sql_load(guild_id);
	struct guild_storage *s2;

	// ペット削除
	if(s) {
		int i;
		for(i=0;i<s->storage_amount;i++){
			if(s->store_item[i].card[0] == (short)0xff00)
				pet_delete(*((long *)(&s->store_item[i].card[1])));
		}
	}

	// delete
	sqldbs_query(&mysql_handle, "DELETE FROM `" GUILD_STORAGE_TABLE "` WHERE `guild_id`='%d'", guild_id);

	s2 = (struct guild_storage*)numdb_search( gstorage_db, guild_id );
	if(s2) {
		numdb_erase( gstorage_db, guild_id );
		aFree( s2 );
	}
	return 1;
}

static int gstorage_db_final(void *key,void *data,va_list ap)
{
	struct guild_storage *gs = (struct guild_storage *)data;

	aFree(gs);

	return 0;
}

void gstorage_sql_final(void)
{
	if(gstorage_db)
		numdb_final(gstorage_db,gstorage_db_final);
}

void storage_sql_config_read_sub(const char* w1,const char* w2)
{
	// nothing to do
}

#define storage_init   storage_sql_init
#define storage_load   storage_sql_load
#define storage_save   storage_sql_save
#define storage_sync   storage_sql_sync
#define storage_delete storage_sql_delete
#define storage_final  storage_sql_final

#define gstorage_load   gstorage_sql_load
#define gstorage_save   gstorage_sql_save
#define gstorage_sync   gstorage_sql_sync
#define gstorage_delete gstorage_sql_delete
#define gstorage_final  gstorage_sql_final

#endif

// 倉庫データの送信
int mapif_load_storage(int fd,int account_id)
{
	const struct storage *s = storage_load(account_id);

	WFIFOW(fd,0)=0x3810;
	WFIFOW(fd,2)=sizeof(struct storage)+8;
	WFIFOL(fd,4)=account_id;
	memcpy(WFIFOP(fd,8),s,sizeof(struct storage));
	WFIFOSET(fd,WFIFOW(fd,2));
	return 0;
}

// 倉庫データ保存完了送信
int mapif_save_storage_ack(int fd,int account_id)
{
	WFIFOW(fd,0)=0x3811;
	WFIFOL(fd,2)=account_id;
	WFIFOB(fd,6)=0;
	WFIFOSET(fd,7);
	return 0;
}

// ギルド倉庫データの送信
int mapif_load_guild_storage(int fd,int account_id,int guild_id)
{
	const struct guild_storage *gs = gstorage_load(guild_id);

	WFIFOW(fd,0)=0x3818;
	if(gs) {
		WFIFORESERVE( fd, sizeof(struct guild_storage)+12 );
		WFIFOW(fd,2)=sizeof(struct guild_storage)+12;
		WFIFOL(fd,4)=account_id;
		WFIFOL(fd,8)=guild_id;
		memcpy(WFIFOP(fd,12),gs,sizeof(struct guild_storage));
	} else {
		WFIFOW(fd,2)=12;
		WFIFOL(fd,4)=account_id;
		WFIFOL(fd,8)=0;
	}
	WFIFOSET(fd,WFIFOW(fd,2));

	return 0;
}
// ギルド倉庫データ保存完了送信
int mapif_save_guild_storage_ack(int fd,int account_id,int guild_id,int fail)
{
	WFIFOW(fd,0)=0x3819;
	WFIFOL(fd,2)=account_id;
	WFIFOL(fd,6)=guild_id;
	WFIFOB(fd,10)=fail;
	WFIFOSET(fd,11);
	return 0;
}

// ギルド倉庫ロック要求返答
int mapif_trylock_guild_storage_ack(int fd,int account_id,int guild_id,int npc_id,char flag)
{
	WFIFOW(fd,0)  = 0x381a;
	WFIFOL(fd,2)  = account_id;
	WFIFOL(fd,6)  = guild_id;
	WFIFOL(fd,10) = npc_id;
	WFIFOB(fd,14) = flag;
	WFIFOSET(fd,15);
	return 0;
}

// ギルド倉庫ロック解除返答
int mapif_unlock_guild_storage_ack(int fd,int guild_id,char succeed)
{
	WFIFOW(fd,0) = 0x381b;
	WFIFOL(fd,2) = guild_id;
	WFIFOB(fd,6) = succeed;
	WFIFOSET(fd,7);
	return 0;
}

// ギルド倉庫デッドロックチェック
int mapif_checklock_guild_storage(int fd,int guild_id)
{
	WFIFOW(fd,0) = 0x381c;
	WFIFOL(fd,2) = guild_id;
	WFIFOSET(fd,6);
	return 0;
}

//---------------------------------------------------------
// map serverからの通信

// 倉庫データ要求受信
int mapif_parse_LoadStorage(int fd)
{
	mapif_load_storage(fd,RFIFOL(fd,2));
	return 0;
}

// 倉庫データ受信＆保存
int mapif_parse_SaveStorage(int fd)
{
	int account_id=RFIFOL(fd,4);
	int len=RFIFOW(fd,2);

	if(sizeof(struct storage)!=len-8){
		printf("inter storage: data size error %d %d\n",sizeof(struct storage),len-8);
	} else {
		storage_save((struct storage *)RFIFOP(fd,8));
		mapif_save_storage_ack(fd,account_id);
	}
	return 0;
}

// ギルド倉庫データ要求受信
int mapif_parse_LoadGuildStorage(int fd)
{
	mapif_load_guild_storage(fd,RFIFOL(fd,2),RFIFOL(fd,6));
	return 0;
}

// ギルド倉庫データ受信＆保存
int mapif_parse_SaveGuildStorage(int fd)
{
	int guild_id=RFIFOL(fd,8);
	int len=RFIFOW(fd,2);

	if(sizeof(struct guild_storage)!=len-12) {
		printf("inter guild_storage: data size error %d %d\n",sizeof(struct guild_storage),len-12);
	} else {
		int ret = gstorage_save((struct guild_storage *)RFIFOP(fd,12), 0);
		mapif_save_guild_storage_ack(fd,RFIFOL(fd,4),guild_id,!ret);
	}
	return 0;
}

// ギルド倉庫ロック要求受信
int mapif_parse_TrylockGuildStorage(int fd)
{
	char flag = 0;
	int guild_id = RFIFOL(fd,6);
	const struct guild_storage *gs = gstorage_load(guild_id);

	if(gs && gs->storage_status == 0) {
		struct guild_storage gs2;
		memcpy(&gs2, gs, sizeof(gs2));
		gs2.storage_status = 1;
		flag = (gs2.last_fd == fd)? 1: 2;	// 前回とは違うMAPサーバからのアクセスならリロード(flag=2)
		gs2.last_fd = fd;
		gstorage_save(&gs2, 1);
	}
	mapif_trylock_guild_storage_ack(fd,RFIFOL(fd,2),guild_id,RFIFOL(fd,10),flag);

	return 0;
}

// ギルド倉庫ロック解除受信
int mapif_parse_UnlockGuildStorage(int fd)
{
	char succeed = 0;
	int guild_id = RFIFOL(fd,2);
	const struct guild_storage *gs = gstorage_load(guild_id);

	if(gs && gs->storage_status == 1) {
		struct guild_storage gs2;
		memcpy(&gs2, gs, sizeof(gs2));
		gs2.storage_status = 0;
		gstorage_save(&gs2, 1);
		succeed = 1;
	}
	mapif_unlock_guild_storage_ack(fd,guild_id,succeed);

	return 0;
}

// ギルド倉庫デッドロック解除受信
int mapif_parse_DeadlockGuildStorage(int fd)
{
	printf("guild_storage_deadlock_timer: storage deadlocked!! (%d)\n", RFIFOL(fd,2));

	// 通常のロック解除と同じ
	mapif_parse_UnlockGuildStorage(fd);

	return 0;
}

// ギルド倉庫デッドロック検出タイマー
static int guild_storage_deadlock_timer_sub(void *key, void *data, va_list ap)
{
	struct guild_storage *gs = (struct guild_storage *)data;

	if(gs && gs->storage_status == 1 && gs->last_fd >= 0)
		mapif_checklock_guild_storage(gs->last_fd, gs->guild_id);

	return 0;
}

int guild_storage_deadlock_timer(int tid, unsigned int tick, int id, int data)
{
	numdb_foreach(gstorage_db, guild_storage_deadlock_timer_sub);

	return 0;
}

//---------------------------------------------------------
// map server からの通信
// ・１パケットのみ解析すること
// ・パケット長データはinter.cにセットしておくこと
// ・パケット長チェックや、RFIFOSKIPは呼び出し元で行われるので行ってはならない
// ・エラーなら0(false)、そうでないなら1(true)をかえさなければならない
int inter_storage_parse_frommap(int fd)
{
	switch(RFIFOW(fd,0)){
	case 0x3010: mapif_parse_LoadStorage(fd); break;
	case 0x3011: mapif_parse_SaveStorage(fd); break;
	case 0x3018: mapif_parse_LoadGuildStorage(fd); break;
	case 0x3019: mapif_parse_SaveGuildStorage(fd); break;
	case 0x301a: mapif_parse_TrylockGuildStorage(fd); break;
	case 0x301b: mapif_parse_UnlockGuildStorage(fd); break;
	case 0x301c: mapif_parse_DeadlockGuildStorage(fd); break;
	default:
		return 0;
	}
	return 1;
}

int inter_storage_init(void)
{
	add_timer_interval(gettick()+1000, guild_storage_deadlock_timer, 0, 0, 3600 * 1000);

	return 0;
}
