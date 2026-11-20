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

#ifndef _LOCK_H_
#define _LOCK_H_

FILE* lock_fopen(const char* filename,int *info);
/* バイナリの一時ファイルを開く。確定にはlock_fclose_checkedを使用する。 */
FILE *lock_fopen_binary(const char *filename, int *info);
int   lock_fclose(FILE *fp,const char* filename,int *info);

/* 成功0、失敗1。書込み・close・置換を確認し、失敗時は元ファイルを残す。 */
int lock_fclose_checked(FILE *fp, const char *filename, int *info);

#endif

