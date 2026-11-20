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

#if !defined(_WIN32) && !defined(_POSIX_C_SOURCE)
#define _POSIX_C_SOURCE 200809L
#endif
#include <stdio.h>
#include <errno.h>
#if defined(_WIN32) || defined(WINDOWS)
#include <windows.h>
#else
#include <unistd.h>
#include <fcntl.h>
#endif

#include "lock.h"
#include "utils.h"

// 書き込みファイルの保護処理
// （書き込みが終わるまで、旧ファイルを保管しておく）

// 新しいファイルの書き込み開始
static FILE *lock_fopen_mode(const char *filename, int *info, const char *mode)
{
	char newfile[2048];
	FILE *fp;
	int  no = 0;

	// 安全なファイル名を得る（手抜き）
	do {
		snprintf(newfile, sizeof(newfile), "%s_%04d.tmp", filename, ++no);
	} while( (fp = fopen(newfile,"r")) && (fclose(fp), no < 9999) );

	if(no >= 9999)
		return NULL;

	*info = no;
	return fopen(newfile, mode);
}

FILE *lock_fopen(const char *filename, int *info)
{
	return lock_fopen_mode(filename, info, "w");
}

FILE *lock_fopen_binary(const char *filename, int *info)
{
#if defined(_WIN32) || defined(WINDOWS)
	return lock_fopen_mode(filename, info, "w+b");
#else
	char temporary[2048];
	int number;
	/* journalには認証情報も入るため、作成時から他ユーザーへ公開しない。 */
	for(number = 1; number < 9999; number++) {
		int fd, error;
		FILE *fp;
		snprintf(temporary, sizeof(temporary), "%s_%04d.tmp", filename, number);
		fd = open(temporary, O_CREAT | O_EXCL | O_RDWR, 0600);
		if(fd < 0) {
			if(errno == EEXIST) continue;
			return NULL;
		}
		fp = fdopen(fd, "w+b");
		if(!fp) {
			error = errno;
			close(fd);
			remove(temporary);
			errno = error;
			return NULL;
		}
		*info = number;
		return fp;
	}
	return NULL;
#endif
}

// 旧ファイルを削除＆新ファイルをリネーム
int lock_fclose(FILE *fp,const char* filename,int *info)
{
	int  ret = 0;
	char newfile[2048];

	if(fp != NULL) {
		ret = fclose(fp);
		snprintf(newfile, sizeof(newfile), "%s_%04d.tmp", filename, *info);
		if(remove(filename) == 0 || errno == ENOENT) {
			// このタイミングで落ちると最悪。
			rename(newfile,filename);
		}
		return ret;
	}
	return 1;
}

/* 元ファイルを先に削除せず、完成した一時ファイルへ置き換える。 */
int lock_fclose_checked(FILE *fp, const char *filename, int *info)
{
	char temporary[2048];
	int failed;
	if(!fp)
		return 1;
	snprintf(temporary, sizeof(temporary), "%s_%04d.tmp", filename, *info);
	failed = ferror(fp) != 0;
	if(fflush(fp) != 0)
		failed = 1;
	if(fclose(fp) != 0)
		failed = 1;
	if(!failed) {
#if defined(_WIN32) || defined(WINDOWS)
		failed = !MoveFileExA(temporary, filename, MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH);
#else
		failed = rename(temporary, filename) != 0;
#endif
	}
	if(failed) {
		printf("lock: cannot replace [%s]; original file retained\n", filename);
		remove(temporary);
	}
	return failed;
}
