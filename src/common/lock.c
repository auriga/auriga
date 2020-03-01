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
#include <errno.h>

#include "lock.h"
#include "utils.h"

// 書き込みファイルの保護処理
// （書き込みが終わるまで、旧ファイルを保管しておく）

// 新しいファイルの書き込み開始
FILE* lock_fopen(const char* filename,int *info)
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
	return fopen(newfile,"w");
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
