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
	int pending_idx;
	int written;
	unsigned int tick;
	time_t timestamp;
	void *buf;
};

struct journal
{
	FILE* fp;
	struct journal_fileheader fhd;
	int mode;
	int io_error, load_error, strict_load;
	int atomic_create;
	int needs_sync;
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
/* cashshop向けの原子的作成。成功1、失敗0。従来のvoid APIの作成方式は変えない。 */
int journal_create_checked(struct journal *j, size_t datasize, int cache_interval, const char *filename);

// 既存のジャーナルをロールフォワード専用の読み込みモードで開く
//   このデータに対する操作は journal_rollforward, journal_final のみ許可される
//   ロールフォワードが終わったら final して開放する必要がある。
/* 復旧件数（空・不存在は0）、I/O失敗は-1。従来の破損レコード除外方針は維持する。 */
int journal_load_with_convert( struct journal* j, size_t datasize, const char* filename, void(*func)( struct journal_header *jhd, void *buf ) );
/* 復旧件数（空・不存在は0）、破損・読込み失敗は-1。失敗時は復旧しない。 */
int journal_load_checked(struct journal *j, size_t datasize, const char *filename);
/* 集約前の全レコードに適用。戻り値は集約後のキー件数で、コールバック件数ではない。
 * 失敗時はコールバックの結果を確定しないこと。 */
int journal_load_checked_with_convert(struct journal *j, size_t datasize, const char *filename,
	void (*convert)(struct journal_header *, void *));
#define journal_load(j, datasize, filename) journal_load_with_convert(j, datasize, filename, NULL)


// データの書き込み ( journal_create 後のみ )
//   key: 識別用のキー（ユニークであること）
//   data: 保存する実データ, NULL でデータの削除
/* 成功1、失敗0。キャッシュ有効時の成功はメモリへの受付を示す。 */
int journal_write( struct journal* j, int key, const void* data );

// キャッシュのフラッシュ ( journal_create 後のみ )
/* 成功0、失敗-1。書込み失敗後はファイルと未確定キャッシュを保持する。 */
int journal_flush( struct journal* j );

/* TXT保存前の確認。成功0、失敗-1。復旧中・初期化前は保存を許可する。 */
int journal_checkpoint(struct journal *j);


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

#ifdef TXT_JOURNAL
struct journal_config {
	int enable;
	char file[1024];
	int cache;
};

void journal_config_init(struct journal_config *cfg, int enable, const char *file, int cache);
int journal_config_read(struct journal_config *cfg, const char *prefix, const char *w1, const char *w2);

/* Returns 1 if roll-forward ran (caller should sync txt), 0 otherwise. */
int journal_setup(struct journal *j, const struct journal_config *cfg, size_t datasize,
	int (*rollforward)(int key, void *buf, int flag), const char *log_tag);
int journal_setup_with_convert(struct journal *j, const struct journal_config *cfg, size_t datasize,
	int (*rollforward)(int key, void *buf, int flag),
	void (*convert)(struct journal_header *jhd, void *buf), const char *log_tag);

/* Recreate empty journal after txt sync. */
void journal_recreate(struct journal *j, const struct journal_config *cfg, size_t datasize);
/* cashshop向け。TXT確定後に原子的作成へ切り替える。成功1、失敗0。 */
int journal_recreate_checked(struct journal *j, const struct journal_config *cfg, size_t datasize);

/* 初期化時のみ使用。復旧TXTの確定失敗時は起動を中断する。 */
void journal_require_ready(const struct journal *j, const struct journal_config *cfg);
#endif /* TXT_JOURNAL */

#endif
