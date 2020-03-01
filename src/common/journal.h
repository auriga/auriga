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

#ifndef _JOURNAL_H_
#define _JOURNAL_H_

#include <stdio.h>
#include <time.h>

#include "db.h"

struct journal_fileheader
{
	char identifier[16];
	unsigned int datasize;
};

enum JOURNAL_FLAG
{
	JOURNAL_FLAG_WRITE=0,
	JOURNAL_FLAG_DELETE=1,
};

struct journal_header {
	unsigned long crc32;
	unsigned int tick;
	time_t timestamp;
	int key, flag;
};

struct journal_data
{
	int idx, flag;
	unsigned int tick;
	time_t timestamp;
	void *buf;
};

struct journal
{
	FILE* fp;
	struct journal_fileheader fhd;
	int mode;
	int cache_timer;
	size_t datasize;
	size_t chunksize;
	size_t nextchunk;
	int unusedchunk_read;
	int unusedchunk_write;
	int* unusedchunk_queue;
	int unusedchunk_size;
	char filename[1024];
	struct dbt *db;
};


// ジャーナルを閉じる
//  journal_create, journal_load したら必ず呼ぶ必要がある
void journal_final( struct journal* j );

// ジャーナルを新規作成する(書き込みモードで開く)
//   このデータに対する操作は journal_write, journal_flush, journal_final のみ許可される
void journal_create( struct journal* j, size_t datasize, int cache_interval, const char* filename );

// 既存のジャーナルをロールフォワード専用の読み込みモードで開く
//   このデータに対する操作は journal_rollforward, journal_final のみ許可される
//   ロールフォワードが終わったら final して開放する必要がある。
int journal_load_with_convert( struct journal* j, size_t datasize, const char* filename, void(*func)( struct journal_header *jhd, void *buf ) );
#define journal_load(j, datasize, filename) journal_load_with_convert(j, datasize, filename, NULL)


// データの書き込み ( journal_create 後のみ )
//   key: 識別用のキー（ユニークであること）
//   data: 保存する実データ, NULL でデータの削除
int journal_write( struct journal* j, int key, const void* data );

// キャッシュのフラッシュ ( journal_create 後のみ )
int journal_flush( struct journal* j );


// ロールフォワード用の関数 ( journal_load 後のみ )
//   ジャーナルの全データに対して func で設定したコールバック関数を呼び出す
//   ロールフォワード用のコールバック関数のパラメータは以下のとおり
//   key: journal_write で設定した key (ユニーク)
//   buf: journal_write で設定した data
//   flag: journal_write で data に NULL が指定されていると JOURNAL_FLAG_DELETE,
//         それ以外では JOURNAL_FLAG_WRITE が設定されている。
int journal_rollforward( struct journal* j, int(*func)( int key, void* buf, int flag ) );


//const char* journal_get( struct journal* j, int key, int* flag );
//int journal_delete( struct journal* j, int key );

#endif
