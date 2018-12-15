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

#ifdef TXT_JOURNAL

#include <string.h>
#include <stdlib.h>

#include "journal.h"
#include "malloc.h"
#include "timer.h"
#include "grfio.h"

#ifndef WINDOWS
#	include <unistd.h>
#endif

#define UNUSEDCHUNK_DEFAULT_QUEUESIZE	256		// キューの最小サイズ ( 2 の累乗であること )
#define CHUNKUNITSIZE 					4096	// チャンクの最小サイズ（多分ディスクのクラスタサイズにするといいと思われる）

//#define JOURNAL_DEBUG		// 定義すると、正常終了時にファイルを削除せずに別名にして残す
							// ".debug0" は終了の過程で出るゴミ、".debug1" は終了時のジャーナル


#define JOURNAL_IDENTIFIER	"AURIGA_JOURNAL19"	// 識別子（ファイル構造を変えたら、最後の数値を変えるべき）

static int journal_first = 1;

static int journal_flush_timer( int tid, unsigned int tick, int id, void *data );

// ==========================================
// ジャーナルの初期化( load と共通部分)
// ------------------------------------------
static void journal_init_( struct journal* j, size_t datasize, const char* filename )
{
	if( journal_first ) {
		grfio_load_zlib();
		journal_first = 0;
	}
	memset( j, 0, sizeof( struct journal ) );
	j->db = numdb_init();
	j->datasize = datasize;
	j->chunksize = ( (datasize + sizeof(struct journal_header) + CHUNKUNITSIZE-1 ) / CHUNKUNITSIZE ) * CHUNKUNITSIZE;
	j->nextchunk = 1;
	j->unusedchunk_read = j->unusedchunk_write = 0;
	j->unusedchunk_size = 0;
	j->unusedchunk_queue = NULL;
	j->cache_timer = -1;
	j->mode = 0;
	strncpy( j->filename, filename, sizeof(j->filename)-1 );
}

// ==========================================
// ジャーナルの初期化
// ------------------------------------------
void journal_create( struct journal* j, size_t datasize, int cache_interval, const char* filename )
{
	static int first = 1;

	// 最初なら関数名登録
	if( first )
	{
		first = 0;
		add_timer_func_list( journal_flush_timer );
	}

	journal_init_( j, datasize, filename );

	// ファイルヘッダの設定
	memcpy( j->fhd.identifier, JOURNAL_IDENTIFIER, sizeof(j->fhd.identifier) );
	j->fhd.datasize = (unsigned int)datasize;

	// ファイルを作ってヘッダ書き込み
	if( ( j->fp = fopen( filename, "w+b" ) ) == NULL )
	{
		printf("journal: fopen [%s]: failed\n", filename );
		exit(1);
	}
	fwrite( &j->fhd, sizeof(j->fhd), 1, j->fp );

	// キャッシュするならタイマー設定
	if( cache_interval > 0)
	{
		j->cache_timer = add_timer_interval( gettick()+ atn_rand()%cache_interval + cache_interval,
											 journal_flush_timer, 0, j, cache_interval);
	}
}

// ==========================================
// ジャーナルの未使用エリアを追加
// ------------------------------------------
static void journal_push_free( struct journal *j, int pos )
{
	// キューのメモリがないなら確保する
	if( j->unusedchunk_size==0 )
	{
		j->unusedchunk_size = UNUSEDCHUNK_DEFAULT_QUEUESIZE;
		j->unusedchunk_queue = (int *)aCalloc( sizeof(int), UNUSEDCHUNK_DEFAULT_QUEUESIZE );
	}

	// キューに登録
	j->unusedchunk_queue[ j->unusedchunk_write ++ ] = pos;
	j->unusedchunk_write %= j->unusedchunk_size;

	if( j->unusedchunk_read == j->unusedchunk_write )
	{
		// キューがいっぱいになったので拡張する ( キュー内部の順番は入れ替わってもよい )
		int* p = (int *)aCalloc( sizeof(int), j->unusedchunk_size*2 );
		memcpy( p, j->unusedchunk_queue, sizeof(int)*j->unusedchunk_size );
		aFree( j->unusedchunk_queue );
		j->unusedchunk_read  = 0;
		j->unusedchunk_write = j->unusedchunk_size;
		j->unusedchunk_size *= 2;
		j->unusedchunk_queue = p;

		printf("journal: unused-chunk-queue size expanded (%d, [%s]).\n", j->unusedchunk_size, j->filename );
	}
}

// ==========================================
// ジャーナルのデータのデストラクタ
// ------------------------------------------
static void journal_final_dtor( struct journal_data* dat )
{
	if( dat->buf ){
		aFree(dat->buf);
		dat->buf = NULL;
	}
	aFree( dat );
}

// ==========================================
// ジャーナルのデータの終了処理(db_foreach)
// ------------------------------------------
static int journal_final_sub( void* key, void* data, va_list ap )
{
	journal_final_dtor( (struct journal_data*)data );
	return 0;
}

// ==========================================
// ジャーナルの終了処理
// ------------------------------------------
void journal_final( struct journal* j )
{
	if( journal_first )
	{
		// ジャーナルは一度も初期化されてないので何もしない
		return;
	}

	// キャッシュフラッシュ用のタイマー削除
	if( j->cache_timer != -1 )
	{
		delete_timer( j->cache_timer, journal_flush_timer );
		j->cache_timer = -1;
	}

	// 作成モードならフラッシュ
	if( j->mode==0 && j->db && j->fp )
	{
		journal_flush( j );
	}

	// ファイルを閉じる
	if( j->fp )
	{
		fclose( j->fp );
		j->fp = NULL;
	}

	// データ破棄
	if( j->db ){
		numdb_final( j->db, journal_final_sub );
		j->db=NULL;
	}

	// 空きキューの削除
	if( j->unusedchunk_queue )
	{
		aFree( j->unusedchunk_queue );
		j->unusedchunk_queue = NULL;
		j->unusedchunk_size = 0;
	}

	// ファイルの削除
	if( j->mode==0 && j->filename[0] )
#ifdef JOURNAL_DEBUG
	{
		char newname[1040], newname2[1040];
		sprintf( newname,"%s.debug1", j->filename );
		sprintf( newname2,"%s.debug0", j->filename );
		//unlink( newname );
		remove( newname );
		rename( newname2, newname );
		rename( j->filename, newname2 );
	}
#else
		//unlink( j->filename );
		remove( j->filename );
#endif
}

// ==========================================
// ジャーナルへ書き込み(ジャーナルのキャッシュへ書き込み)
// ------------------------------------------
int journal_write( struct journal* j, int key, const void* data )
{
	struct journal_data* dat;

	if( !j->db )
	{
		printf("journal_write: error: journal not ready\n");
		return 0;
	}

	dat = (struct journal_data*)numdb_search( j->db, key );

	// ジャーナルデータの登録
	if( !dat )
	{
		dat = (struct journal_data *)aCalloc( 1,sizeof(struct journal_data ) );
		numdb_insert( j->db, key, dat );
		dat->idx = -1;
	}

	// キャッシュ用のメモリ確保
	if( !dat->buf )
	{
		dat->buf = aCalloc( 1, j->datasize );
	}

	// データの書き換えか削除か
	if( data )
	{
		memcpy( dat->buf, data, j->datasize );
		dat->flag = JOURNAL_FLAG_WRITE;
	}
	else
	{
		memset( dat->buf, 0, j->datasize );
		dat->flag = JOURNAL_FLAG_DELETE;
	}

	// キャッシュしないならすぐにファイルに書き込む
	if( j->cache_timer==-1 )
	{
		journal_flush( j );
	}

	return 1;
}

// ==========================================
// ジャーナルへ書き込み(ジャーナルのキャッシュからファイルへの書き込み)
// ------------------------------------------
static int journal_flush_sub( void* key, void* data, va_list ap )
{
	struct journal* j = va_arg( ap, struct journal * );
	unsigned int tick = va_arg( ap, unsigned int );
	time_t timestamp  = va_arg( ap, time_t );
	struct journal_data* dat = (struct journal_data*)data;
	struct journal_header jhd;
	int old_idx = dat->idx;

	// キャッシュデータはないので飛ばす
	if( !dat->buf )
	{
		return 0;
	}

	// ファイル中の位置を強制的に置き換えるのは、このデータの書き込み中に
	// 問題が起こった時に、以前の書き込みデータを生かせるようにする為です。
	if( j->unusedchunk_read != j->unusedchunk_write )
	{
		// 空きチャンクから取り出す
		dat->idx = j->unusedchunk_queue[ j->unusedchunk_read ++ ];
		j->unusedchunk_read %= j->unusedchunk_size;
	}
	else
	{
		// 空きがないので新しく作る
		dat->idx = (int)( j->nextchunk ++ );
	}

	// ジャーナル書き込み用のヘッダ設定
	jhd.key = PTR2INT(key);
	jhd.timestamp = timestamp;
	jhd.tick = tick;
	jhd.flag = dat->flag;
	jhd.crc32 = grfio_crc32( (const unsigned char *)dat->buf, (unsigned int)j->datasize );

	// データ書き込み
	fseek( j->fp, (long)(dat->idx * j->chunksize), SEEK_SET );
	if( fwrite( &jhd, sizeof(jhd), 1, j->fp )==0 ||
		fwrite( dat->buf, j->datasize, 1, j->fp )==0 )
	{
		printf("journal: file write error! key=%d\n", jhd.key );
		return 0;
	}

	// 書き込んだのでキャッシュデータはもういらない
	aFree( dat->buf );
	dat->buf = NULL;

	if( old_idx != -1 )
	{
		journal_push_free( j, old_idx );
	}

	return 1;
}

// ==========================================
// ジャーナルの全キャッシュをファイルへ書き込む
// ------------------------------------------
int journal_flush( struct journal* j )
{
	if( j->db && j->fp )
		numdb_foreach( j->db, journal_flush_sub, j, gettick(), time(NULL) );

	if( j->fp )
		fflush( j->fp );
	return 0;
}

// ==========================================
// ジャーナルの全キャッシュをファイルへ書き込む(タイマー)
// ------------------------------------------
static int journal_flush_timer( int tid, unsigned int tick, int id, void *data )
{
	journal_flush( (struct journal* )data );
	return 0;
}

// ==========================================
// ジャーナルからデータを削除
// ------------------------------------------
int journal_delete( struct journal* j, int key )
{
	struct journal_data* dat = (struct journal_data*)numdb_search( j->db, key );

	if( dat )
	{
		journal_push_free( j, dat->idx );
		numdb_erase( j->db, key );
		journal_final_dtor( dat );
		return 1;
	}
	return 0;
}


// ==========================================
// ジャーナルから最新データの取得( commit に使用)
// ------------------------------------------
const char* journal_get( struct journal* j, int key, int* flag )
{
	struct journal_data* dat = (struct journal_data*)numdb_search( j->db, key );

	if( dat )
	{
		if( flag ) *flag = dat->flag;
		return (const char *)dat->buf;
	}
	return NULL;
}

// ==========================================
// ジャーナルの全キャッシュをファイルから読み込む
// ------------------------------------------
int journal_load_with_convert( struct journal* j, size_t datasize, const char* filename, void(*func)( struct journal_header *jhd, void *buf ) )
{
	struct journal_header jhd;
	int c,i;

	journal_init_( j, datasize, filename );

	// ファイルを読み込み用に開く
	if( ( j->fp = fopen( filename, "r+b" ) ) == NULL )
	{
		return 0;
	}

	j->mode = 1;	// 読み取りモードフラグ

	// ファイルが正しいかチェック
	fread( &j->fhd, 1, sizeof(j->fhd), j->fp );
	if( memcmp( j->fhd.identifier, JOURNAL_IDENTIFIER, sizeof(j->fhd.identifier) ) != 0 )
	{
		printf("journal: file version mismatch ! '%s' vs '%s' [%s]\n", j->fhd.identifier, JOURNAL_IDENTIFIER, filename);
		abort();
	}
	if( j->fhd.datasize != (unsigned int)datasize )
	{
		printf("journal: file datasize mismatch ! %u vs %u [%s]\n", j->fhd.datasize, (unsigned int)datasize, filename );
		abort();
	}

	// データの読み込みループ
	c = 0;
	for( i=1; fseek( j->fp, (long)(i*j->chunksize), SEEK_SET ), fread( &jhd, sizeof(jhd), 1, j->fp ) > 0; i++ )
	{
		struct journal_data *dat;
		unsigned char* buf = (unsigned char *)aCalloc( 1, datasize );

		// データ本体の読み込みと crc32 チェック
		if( fread( buf, datasize, 1, j->fp ) == 0 || grfio_crc32( buf, (unsigned int)datasize ) != jhd.crc32 )
		{
			printf("journal: file broken [%s], but continue...\n", filename );
			aFree( buf );
			continue;	// このデータが壊れてても他のデータは生きてると思われる
		}

		// 変換処理
		if( func )
			func( &jhd, buf );

		// 登録処理
		dat = (struct journal_data*)numdb_search( j->db, jhd.key );
		if( dat )
		{
			// すでにあるので置き換えが必要か調べる
			if( jhd.timestamp > dat->timestamp  &&  DIFF_TICK( jhd.tick, dat->tick ) > 0 )
			{
				// 置き換え
				journal_push_free( j, dat->idx );
				aFree( dat->buf );
				dat->buf = buf;
				dat->timestamp = jhd.timestamp;
				dat->tick = jhd.tick;
				dat->flag = jhd.flag;
				dat->idx  = i;
			}
			else
			{
				// 置き換えない
				aFree( buf );
			}
		}
		else
		{
			// 新しく登録
			dat = (struct journal_data*)aCalloc( 1, sizeof(struct journal_data) );
			dat->buf = buf;
			dat->timestamp = jhd.timestamp;
			dat->tick = jhd.tick;
			dat->flag = jhd.flag;
			dat->idx  = i;
			numdb_insert( j->db, jhd.key, dat );
			c++;
		}
	}
	return c;
}

// ==========================================
// ジャーナルのロールフォワード(foreach)
// ------------------------------------------
typedef int(* JOURNAL_ROLLFORWARD_CALLBACK )( int, void*, int );
static int journal_rollforward_sub( void* key, void* data, va_list ap )
{
	JOURNAL_ROLLFORWARD_CALLBACK func = (JOURNAL_ROLLFORWARD_CALLBACK)va_arg( ap, JOURNAL_ROLLFORWARD_CALLBACK );
	struct journal_data* dat = (struct journal_data*)data;
	int* c = va_arg( ap, int* );

	*c += func( PTR2INT(key), dat->buf, dat->flag );

	return 0;
}

// ==========================================
// ジャーナルのロールフォワード
// ------------------------------------------
int journal_rollforward( struct journal* j, int(*func)( int key, void* buf, int flag ) )
{
	int c = 0;

	numdb_foreach( j->db, journal_rollforward_sub, func, &c );
	return c;
}

#endif
