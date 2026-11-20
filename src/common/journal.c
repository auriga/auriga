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

#ifdef TXT_JOURNAL

#if !defined(_WIN32) && !defined(_POSIX_C_SOURCE)
#define _POSIX_C_SOURCE 200809L
#endif
#if defined(__APPLE__) && !defined(_DARWIN_C_SOURCE)
#define _DARWIN_C_SOURCE 1
#endif
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#include "journal.h"
#include "lock.h"
#include "malloc.h"
#include "timer.h"
#include "grfio.h"
#include "utils.h"

#ifndef WINDOWS
#	include <unistd.h>
#	include <sys/stat.h>
#	include <fcntl.h>
#	if defined(__linux__)
#		include <sys/xattr.h>
#	elif defined(__APPLE__)
#		include <sys/acl.h>
#	elif defined(__CYGWIN__) || defined(__FreeBSD__)
#		include <sys/acl.h>
#	endif
#endif

#define UNUSEDCHUNK_DEFAULT_QUEUESIZE	256		// キューの最小サイズ ( 2 の累乗であること )
#define CHUNKUNITSIZE 					4096	// チャンクの最小サイズ（多分ディスクのクラスタサイズにするといいと思われる）

//#define JOURNAL_DEBUG		// 定義すると、正常終了時にファイルを削除せずに別名にして残す
							// ".debug0" は終了の過程で出るゴミ、".debug1" は終了時のジャーナル


#define JOURNAL_IDENTIFIER	"AURIGA_JOURNAL20"	// 識別子（ファイル構造を変えたら、最後の数値を変えるべき）

/* Windowsのlongは32bitのため、ファイル位置だけ64bit APIを使う。 */
static int journal_seek(FILE *fp, uint64 offset, int origin)
{
#ifdef WINDOWS
	return _fseeki64(fp, (__int64)offset, origin);
#else
	if(offset > LONG_MAX)
		return -1;
	return fseek(fp, (long)offset, origin);
#endif
}

#ifdef JOURNAL_TELL_SOURCE
extern long long JOURNAL_TELL_SOURCE(FILE *fp);
#endif
static long long journal_tell(FILE *fp)
{
#ifdef JOURNAL_TELL_SOURCE
	return JOURNAL_TELL_SOURCE(fp);
#else
#ifdef WINDOWS
	return _ftelli64(fp);
#else
	return ftell(fp);
#endif
#endif
}

/* テスト時もUCRTのtime定義自体は変更しない。 */
#ifdef JOURNAL_TIME_SOURCE
extern time_t JOURNAL_TIME_SOURCE(time_t *result);
#else
#define JOURNAL_TIME_SOURCE time
#endif

#ifdef JOURNAL_READ_SOURCE
extern size_t JOURNAL_READ_SOURCE(void *buf, size_t size, size_t count, FILE *fp);
#else
#define JOURNAL_READ_SOURCE fread
#endif

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
	auriga_strlcpy( j->filename, filename, sizeof(j->filename) );
}

// ==========================================
// ジャーナルの初期化
// ------------------------------------------
#ifndef WINDOWS
/* modeのグループ欄はACLマスクの場合があるため、ACLも引き継ぐ。 */
static int journal_copy_acl(const char *source, int destination, mode_t mode)
{
#if defined(__linux__)
	const char *attribute = "system.posix_acl_access";
	if(source) {
		ssize_t nfs_acl = getxattr(source, "system.nfs4_acl", NULL, 0);
		if(nfs_acl >= 0 || (errno != ENODATA && errno != ENOTSUP))
			return 0;
	}
	{
		ssize_t nfs_acl = fgetxattr(destination, "system.nfs4_acl", NULL, 0);
		if(nfs_acl >= 0 || (errno != ENODATA && errno != ENOTSUP))
			return 0;
	}
	if(source) {
		ssize_t length = getxattr(source, attribute, NULL, 0);
		if(length >= 0) {
			void *value;
			int result;
			if(length == 0) return 0;
			value = aMalloc((size_t)length);
			result = getxattr(source, attribute, value, (size_t)length) == length &&
			         fsetxattr(destination, attribute, value, (size_t)length, 0) == 0;
			aFree(value);
			return result;
		}
		if(errno != ENODATA)
			return 0;
	}
	/* 元にACLがない場合だけ、継承ACLを除去してからmodeを設定する。 */
	if(fremovexattr(destination, attribute) != 0 && errno != ENODATA)
		return 0;
	return fchmod(destination, mode) == 0;
#elif defined(__APPLE__)
	acl_t acl = NULL;
	int result;
	if(source) {
		filesec_t security = filesec_init();
		struct stat info;
		int fd;
		if(!security) return 0;
		fd = open(source, O_RDONLY);
		if(fd < 0) { filesec_free(security); return 0; }
		result = fstatx_np(fd, &info, security) == 0;
		if(result && filesec_get_property(security, FILESEC_ACL, &acl) != 0 && errno != ENOENT)
			result = 0;
		filesec_free(security);
		if(close(fd) != 0) result = 0;
		if(!result) { if(acl) acl_free(acl); return 0; }
	}
	if(!acl) acl = acl_init(0);
	if(!acl) return 0;
	result = acl_set_fd(destination, acl) == 0;
	acl_free(acl);
	return result && fchmod(destination, mode) == 0;
#elif defined(__CYGWIN__) || defined(__FreeBSD__)
#if defined(__FreeBSD__) && !defined(_PC_ACL_NFS4)
	/* 定数が非公開でも既存のジャーナルのビルドを妨げない。 */
	return 0;
#else
#ifdef __FreeBSD__
	/* 原子的作成のNFSv4 ACL対応は今回の対象外。従来APIには影響しない。 */
	if(fpathconf(destination, _PC_ACL_NFS4) != 0)
		return 0;
#endif
	(void)mode;
	acl_t acl = source ? acl_get_file(source, ACL_TYPE_ACCESS) : acl_from_text("u::rw-,g::---,o::---");
	int result;
	if(!acl) return 0;
	result = acl_set_fd(destination, acl) == 0;
	acl_free(acl);
	return result;
#endif
#else
	/* ACLを確認できない環境で、既存のアクセス制限を広げない。 */
	return 0;
#endif
}
#endif

static int journal_create_internal(struct journal *j, size_t datasize, int cache_interval, const char *filename, int atomic)
{
	static int first = 1;
	int lock;
	char temporary[2048];
#ifndef WINDOWS
	struct stat previous;
	int had_file = 0;
#endif

	// 最初なら関数名登録
	if( first )
	{
		first = 0;
		add_timer_func_list( journal_flush_timer );
	}

	journal_init_( j, datasize, filename );
	j->atomic_create = atomic;
#ifndef WINDOWS
	if(atomic) {
		had_file = lstat(filename, &previous) == 0;
		if((had_file && S_ISLNK(previous.st_mode)) || (!had_file && errno != ENOENT)) {
			printf("journal: cannot replace journal path [%s]\n", filename);
			j->io_error = 1;
			return 0;
		}
	}
#endif

	// ファイルヘッダの設定
	memcpy( j->fhd.identifier, JOURNAL_IDENTIFIER, sizeof(j->fhd.identifier) );
	j->fhd.datasize = (unsigned int)datasize;

	if(atomic) {
		/* 完成した新世代ヘッダだけを正式名へ切り替える。 */
		j->fp = lock_fopen_binary(filename, &lock);
		if(!j->fp) {
			printf("journal: temporary file creation failed [%s]\n", filename);
			j->io_error = 1;
			return 0;
		}
		snprintf(temporary, sizeof(temporary), "%s_%04d.tmp", filename, lock);
		if(fwrite(&j->fhd, sizeof(j->fhd), 1, j->fp) != 1 || fflush(j->fp) != 0) {
			printf("journal: header write failed [%s]\n", filename);
			j->io_error = 1;
			fclose(j->fp);
			j->fp = NULL;
			remove(temporary);
			return 0;
		}
#ifndef WINDOWS
		if(had_file) {
			struct stat temporary_stat;
			int fd = fileno(j->fp), failed = fstat(fd, &temporary_stat) != 0;
			if(!failed && (temporary_stat.st_uid != previous.st_uid || temporary_stat.st_gid != previous.st_gid))
				failed = fchown(fd, previous.st_uid, previous.st_gid) != 0;
			if(failed) {
				j->io_error = 1;
				fclose(j->fp);
				j->fp = NULL;
				remove(temporary);
				return 0;
			}
		}
#endif
#ifndef WINDOWS
		if(!journal_copy_acl(had_file ? filename : NULL, fileno(j->fp), had_file ? previous.st_mode & 0777 : 0600)) {
			printf("journal: cannot preserve ACL [%s]\n", filename);
			j->io_error = 1;
			fclose(j->fp);
			j->fp = NULL;
			remove(temporary);
			return 0;
		}
#endif
		{
			FILE *fp = j->fp;
			j->fp = NULL;
			if(lock_fclose_checked(fp, filename, &lock) != 0) {
				j->io_error = 1;
				return 0;
			}
		}
		j->fp = fopen(filename, "r+b");
		if(!j->fp) {
			j->io_error = 1;
			return 0;
		}

	} else {
		/* 従来のジャーナルは実体・ACL等を変えない直接作成を維持する。 */
		j->fp = fopen(filename, "w+b");
		if(!j->fp) {
			printf("journal: fopen [%s]: failed\n", filename);
			j->io_error = 1;
			return 0;
		}
		if(fwrite(&j->fhd, sizeof(j->fhd), 1, j->fp) != 1 || fflush(j->fp) != 0) {
			printf("journal: header write failed [%s]\n", filename);
			j->io_error = 1;
			fclose(j->fp);
			j->fp = NULL;
			return 0;
		}
	}

	// キャッシュするならタイマー設定
	if( cache_interval > 0)
	{
		j->cache_timer = add_timer_interval( gettick()+ atn_rand()%cache_interval + cache_interval,
											 journal_flush_timer, 0, j, cache_interval);
	}
	return 1;
}

int journal_create_checked(struct journal *j, size_t size, int cache, const char *file)
{
	return journal_create_internal(j, size, cache, file, 1);
}

void journal_create(struct journal *j, size_t size, int cache, const char *file)
{
	if(!journal_create_internal(j, size, cache, file, 0))
		exit(1);
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
	/* TXT同期が失敗していた場合は、最終flushが成功しても復旧用に残す。 */
	int preserve = j->io_error || j->needs_sync;
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
		if(fclose(j->fp) != 0)
			j->io_error = 1;
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

#ifndef WINDOWS
	/* 稼働中にリンクへ差し替えられても、リンク自体は削除しない。 */
	{
		struct stat path_stat;
		if(j->atomic_create && j->filename[0] && lstat(j->filename, &path_stat) == 0 && S_ISLNK(path_stat.st_mode))
			preserve = 1;
	}
#endif
	// ファイルの削除
	if( j->mode==0 && !preserve && !j->io_error && j->filename[0] )
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

	if( !j->db || !j->fp || j->mode != 0 )
	{
		printf("journal_write: error: journal not ready\n");
		return 0;
	}

	dat = (struct journal_data*)numdb_search( j->db, key );
	j->needs_sync = 1;

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
	if( j->cache_timer==-1 || j->io_error )
	{
		return journal_flush(j) == 0;
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
	int target;

	// キャッシュデータはないので飛ばす
	if(!dat->buf || j->io_error)
		return 0;

	// ファイル中の位置を強制的に置き換えるのは、このデータの書き込み中に
	// 問題が起こった時に、以前の書き込みデータを生かせるようにする為です。
	if(dat->pending_idx > 0) {
		/* 再試行は未確定チャンクを使い、欠落領域を作らない。 */
		target = dat->pending_idx;
	}
	else if( j->unusedchunk_read != j->unusedchunk_write )
	{
		// 空きチャンクから取り出す
		target = j->unusedchunk_queue[ j->unusedchunk_read ++ ];
		j->unusedchunk_read %= j->unusedchunk_size;
	}
	else
	{
		// 空きがないので新しく作る
		if(j->nextchunk > INT_MAX || (uint64)j->nextchunk > (uint64)LLONG_MAX / j->chunksize) {
			j->io_error = 1;
			return 0;
		}
		target = (int)( j->nextchunk ++ );
	}

	dat->pending_idx = target;

	// ジャーナル書き込み用のヘッダ設定
	jhd.key = PTR2INT(key);
	/* 同一ミリ秒・時刻補正後でも同じキーの新旧を区別する。 */
	jhd.timestamp = timestamp < dat->timestamp ? dat->timestamp : timestamp;
	jhd.tick = tick;
	if(dat->written && DIFF_TICK(jhd.tick, dat->tick) <= 0)
		jhd.tick = dat->tick + 1;
	jhd.flag = dat->flag;
	jhd.crc32 = grfio_crc32( (const unsigned char *)dat->buf, (unsigned int)j->datasize );

	// データ書き込み
	if(journal_seek(j->fp, (uint64)target * j->chunksize, SEEK_SET) != 0 ||
	   fwrite( &jhd, sizeof(jhd), 1, j->fp )==0 ||
		fwrite( dat->buf, j->datasize, 1, j->fp )==0 )
	{
		printf("journal: file write error! key=%d\n", jhd.key );
		j->io_error = 1;
		return 0;
	}

	/* fflush成功までは旧チャンクとキャッシュを保持する。 */
	dat->timestamp = jhd.timestamp;
	dat->tick = jhd.tick;
	dat->written = 1;

	return 1;
}

// ==========================================
// ジャーナルの全キャッシュをファイルへ書き込む
// ------------------------------------------
static int journal_flush_commit(void *key, void *data, va_list ap)
{
	struct journal *j = va_arg(ap, struct journal *);
	struct journal_data *dat = (struct journal_data *)data;
	if(dat->pending_idx > 0) {
		if(dat->idx >= 0)
			journal_push_free(j, dat->idx);
		dat->idx = dat->pending_idx;
		dat->pending_idx = 0;
		aFree(dat->buf);
		dat->buf = NULL;
	}
	return 0;
}

int journal_flush( struct journal* j )
{
	if(!j || !j->db || !j->fp || j->mode != 0)
		return -1;
	/* キャッシュと旧チャンクを保ったまま、一時的なI/O障害から再試行する。 */
	clearerr(j->fp);
	j->io_error = 0;
	numdb_foreach(j->db, journal_flush_sub, j, gettick(), JOURNAL_TIME_SOURCE(NULL));
	if(fflush(j->fp) != 0 || ferror(j->fp))
		j->io_error = 1;
	if(j->io_error) {
		printf("journal: flush failed; preserving [%s]\n", j->filename);
		return -1;
	}
	numdb_foreach(j->db, journal_flush_commit, j);
	return 0;
}

/* TXT保存前に呼び、失敗済み履歴と新しいTXTの不整合を防ぐ。 */
int journal_checkpoint(struct journal *j)
{
	if(!j || (j->strict_load && j->load_error))
		return -1;
	/* 起動時の復旧・初期保存では書込み用ジャーナルがまだない。 */
	if(!j->fp)
		return j->io_error || j->needs_sync ? -1 : 0;
	if(j->mode != 0)
		return 0;
	return journal_flush(j);
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
static int journal_load_internal(struct journal *j, size_t datasize, const char *filename, void(*func)(struct journal_header *, void *), int strict)
{
	struct journal_header jhd;
	int c;
	size_t i;
	long long length;

	journal_init_( j, datasize, filename );
	j->mode = 1;
	j->strict_load = strict;
#ifndef WINDOWS
	{
		struct stat path_stat;
		if(strict && lstat(filename, &path_stat) == 0 && S_ISLNK(path_stat.st_mode)) {
			printf("journal: file symlink unsupported; use its real target [%s]\n", filename);
			j->io_error = j->load_error = 1;
			return -1;
		}
	}
#endif

	// ファイルを読み込み用に開く
	if( ( j->fp = fopen( filename, "r+b" ) ) == NULL )
	{
		if(errno != ENOENT) {
			j->load_error = 1;
			return -1;
		}
		return 0;
	}

	j->mode = 1;	// 読み取りモードフラグ

	// ファイルが正しいかチェック
	if(JOURNAL_READ_SOURCE(&j->fhd, 1, sizeof(j->fhd), j->fp) != sizeof(j->fhd)) {
		j->load_error = 1;
		if(strict)
			return -1;
		printf("journal: incomplete file header [%s]\n", filename);
		abort();
	}
	if( memcmp( j->fhd.identifier, JOURNAL_IDENTIFIER, sizeof(j->fhd.identifier) ) != 0 )
	{
		j->load_error = 1;
		if(strict) return -1;
		printf("journal: file version mismatch ! '%s' vs '%s' [%s]\n", j->fhd.identifier, JOURNAL_IDENTIFIER, filename);
		abort();
	}
	if( j->fhd.datasize != (unsigned int)datasize )
	{
		j->load_error = 1;
		if(strict) return -1;
		printf("journal: file datasize mismatch ! %u vs %u [%s]\n", j->fhd.datasize, (unsigned int)datasize, filename );
		abort();
	}

	if(journal_seek(j->fp, 0, SEEK_END) != 0 || (length = journal_tell(j->fp)) < 0) {
		j->load_error = 1;
		j->io_error = 1;
		return -1;
	}
	/* 正常な空ファイルと、ヘッダ後・レコード末尾の途切れを区別する。 */
	if(strict && (uint64)length != sizeof(j->fhd)) {
		uint64 payload = sizeof(jhd) + datasize;
		if((uint64)length < j->chunksize + payload ||
		   ((uint64)length - payload) % j->chunksize != 0) {
			j->load_error = 1;
			return -1;
		}
	}

	// データの読み込みループ
	c = 0;
	for(i = 1; ; i++) {
		size_t got;
		if((uint64)i * j->chunksize >= (uint64)length)
			break;
		if(i > INT_MAX || journal_seek(j->fp, (uint64)i * j->chunksize, SEEK_SET) != 0) {
			j->io_error = 1;
			j->load_error = 1;
			break;
		}
		/* 初めから途切れた末尾は従来APIでは除外し、読取り途中の縮小と区別する。 */
		if((uint64)length - (uint64)i * j->chunksize < sizeof(jhd)) {
			j->load_error = 1;
			break;
		}
		got = JOURNAL_READ_SOURCE(&jhd, 1, sizeof(jhd), j->fp);
		if(got != sizeof(jhd)) {
			j->io_error = 1;
			j->load_error = 1;
			break;
		}
		struct journal_data *dat;
		unsigned char* buf = (unsigned char *)aCalloc( 1, datasize );

		// データ本体の読み込みと crc32 チェック
		if( JOURNAL_READ_SOURCE( buf, datasize, 1, j->fp ) == 0 || grfio_crc32( buf, (unsigned int)datasize ) != jhd.crc32 ||
		   (strict && jhd.flag != JOURNAL_FLAG_WRITE && jhd.flag != JOURNAL_FLAG_DELETE) )
		{
			printf("journal: file broken [%s]%s\n", filename,
				strict ? "; recovery stopped" : ", but continue...");
			if(ferror(j->fp)) j->io_error = 1;
			aFree( buf );
			j->load_error = 1;
			if(strict) break;
			continue;	// このデータが壊れてても他のデータは生きてると思われる
		}

		if(strict && jhd.flag == JOURNAL_FLAG_DELETE) {
			size_t k;
			for(k = 0; k < datasize && buf[k] == 0; k++);
			if(k != datasize) {
				aFree(buf);
				j->load_error = 1;
				break;
			}
		}

		// 変換処理
		if( func )
			func( &jhd, buf );

		// 登録処理
		dat = (struct journal_data*)numdb_search( j->db, jhd.key );
		if( dat )
		{
			// すでにあるので置き換えが必要か調べる
			/* tickは同じ起動中の順序を示すため、時計の後退より優先する。 */
			if((difftime(jhd.timestamp, dat->timestamp) >= INT_MAX / 1000) ||
			   (difftime(dat->timestamp, jhd.timestamp) < INT_MAX / 1000 &&
			    (DIFF_TICK(jhd.tick, dat->tick) > 0 ||
			     (jhd.tick == dat->tick && jhd.timestamp > dat->timestamp))))
			{
				// 置き換え
				journal_push_free( j, dat->idx );
				aFree( dat->buf );
				dat->buf = buf;
				dat->timestamp = jhd.timestamp;
				dat->tick = jhd.tick;
				dat->flag = jhd.flag;
				dat->idx  = (int)i;
				dat->written = 1;
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
			dat->idx  = (int)i;
				dat->written = 1;
			numdb_insert( j->db, jhd.key, dat );
			c++;
		}
	}
	if(j->io_error || (strict && j->load_error)) {
		printf("journal: recovery refused [%s]\n", filename);
		return -1;
	}
	return c;
}

/* 従来APIは読めるレコードを復旧し、厳格APIは一部破損も失敗とする。 */
int journal_load_with_convert(struct journal *j, size_t size, const char *file,
	void(*convert)(struct journal_header *, void *))
{
	return journal_load_internal(j, size, file, convert, 0);
}

int journal_load_checked(struct journal *j, size_t size, const char *file)
{
	return journal_load_internal(j, size, file, NULL, 1);
}

/* 各レコードを集約前に検証・変換する。終了まで成功が確定しない点に注意。 */
int journal_load_checked_with_convert(struct journal *j, size_t size, const char *file,
	void (*convert)(struct journal_header *, void *))
{
	return journal_load_internal(j, size, file, convert, 1);
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

	if(j->strict_load && j->load_error)
		return -1;
	numdb_foreach( j->db, journal_rollforward_sub, func, &c );
	return c;
}

void journal_config_init(struct journal_config *cfg, int enable, const char *file, int cache)
{
	if(cfg == NULL)
		return;
	memset(cfg, 0, sizeof(*cfg));
	cfg->enable = enable;
	cfg->cache = cache;
	if(file)
		auriga_strlcpy(cfg->file, file, sizeof(cfg->file));
}

int journal_config_read(struct journal_config *cfg, const char *prefix, const char *w1, const char *w2)
{
	char key[128];

	if(cfg == NULL || prefix == NULL || w1 == NULL || w2 == NULL)
		return 0;

	snprintf(key, sizeof(key), "%s_enable", prefix);
	if(strcmpi(w1, key) == 0) {
		cfg->enable = atoi(w2);
		return 1;
	}
	snprintf(key, sizeof(key), "%s_file", prefix);
	if(strcmpi(w1, key) == 0) {
		auriga_strlcpy(cfg->file, w2, sizeof(cfg->file));
		return 1;
	}
	snprintf(key, sizeof(key), "%s_cache_interval", prefix);
	if(strcmpi(w1, key) == 0) {
		cfg->cache = atoi(w2);
		return 1;
	}
	return 0;
}

int journal_setup(struct journal *j, const struct journal_config *cfg, size_t datasize,
	int (*rollforward)(int key, void *buf, int flag), const char *log_tag)
{
	if(j == NULL || cfg == NULL || !cfg->enable)
		return 0;

	int loaded = journal_load(j, datasize, cfg->file);
	if(loaded < 0) {
		printf("journal: recovery I/O failed [%s]\n", cfg->file);
		abort();
	}
	if(loaded > 0) {
		int c = journal_rollforward(j, rollforward);
		printf("%s: roll-forward (%d)\n", log_tag ? log_tag : "journal", c);
		return 1;
	}

	journal_final(j);
	journal_create(j, datasize, cfg->cache, cfg->file);
	return 0;
}

int journal_setup_with_convert(struct journal *j, const struct journal_config *cfg, size_t datasize,
	int (*rollforward)(int key, void *buf, int flag),
	void (*convert)(struct journal_header *jhd, void *buf), const char *log_tag)
{
	if(j == NULL || cfg == NULL || !cfg->enable)
		return 0;

	int loaded = journal_load_with_convert(j, datasize, cfg->file, convert);
	if(loaded < 0) {
		printf("journal: recovery I/O failed [%s]\n", cfg->file);
		abort();
	}
	if(loaded > 0) {
		int c = journal_rollforward(j, rollforward);
		printf("%s: roll-forward (%d)\n", log_tag ? log_tag : "journal", c);
		return 1;
	}

	journal_final(j);
	journal_create(j, datasize, cfg->cache, cfg->file);
	return 0;
}

/* 復旧TXTを確定できないまま更新受付を開始しない。 */
void journal_require_ready(const struct journal *j, const struct journal_config *cfg)
{
	if(cfg->enable && (!j->fp || j->mode != 0 || j->io_error)) {
		printf("journal: writable generation not ready [%s]\n", cfg->file);
		abort();
	}
}

int journal_recreate_checked(struct journal *j, const struct journal_config *cfg, size_t datasize)
{
	if(j == NULL || cfg == NULL)
		return 0;
	if(!cfg->enable)
		return 1;
	if(j->io_error || (j->strict_load && j->load_error))
		return 0;
#ifndef WINDOWS
	{
		struct stat path_stat;
		if(lstat(cfg->file, &path_stat) == 0 && S_ISLNK(path_stat.st_mode)) {
			j->io_error = 1;
			return 0;
		}
	}
#endif
	j->needs_sync = 0;
	/* TXT確定済み。旧ファイルは置換まで残し、権限と所有者を引き継ぐ。 */
	j->mode = 1;
	journal_final(j);
	/* TXT確定済みなので、close失敗後も新しい書込み世代を開始できる。 */
	return journal_create_checked(j, datasize, cfg->cache, cfg->file);
}

void journal_recreate(struct journal *j, const struct journal_config *cfg, size_t datasize)
{
	if(j == NULL || cfg == NULL || !cfg->enable ||
	   j->io_error || (j->strict_load && j->load_error))
		return;
	/* 従来利用側は、従来の作成・終了経路を維持する。 */
	j->needs_sync = 0;
	journal_final(j);
	journal_create(j, datasize, cfg->cache, cfg->file);
}

#endif
