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

#ifndef _STORAGEDB_TXT_H_
#define _STORAGEDB_TXT_H_

#include "mmo.h"
#include "utils.h"

// プロトタイプ宣言
bool storagedb_txt_init(void);
const struct storage* storagedb_txt_load(int account_id);
bool storagedb_txt_save(struct storage *s2);
int storagedb_txt_sync(void);
bool storagedb_txt_delete(int account_id);
void storagedb_txt_final(void);
int storagedb_txt_config_read_sub(const char* w1,const char* w2);
const struct guild_storage *gstoragedb_txt_load(int guild_id);
bool gstoragedb_txt_save(struct guild_storage *gs2, int easy);
int gstoragedb_txt_sync(void);
bool gstoragedb_txt_delete(int guild_id);
void gstoragedb_txt_final(void);

// エイリアス
#define storagedb_init   storagedb_txt_init
#define storagedb_load   storagedb_txt_load
#define storagedb_save   storagedb_txt_save
#define storagedb_sync   storagedb_txt_sync
#define storagedb_delete storagedb_txt_delete
#define storagedb_final  storagedb_txt_final
#define storagedb_config_read_sub storagedb_txt_config_read_sub

#define gstoragedb_load   gstoragedb_txt_load
#define gstoragedb_save   gstoragedb_txt_save
#define gstoragedb_sync   gstoragedb_txt_sync
#define gstoragedb_delete gstoragedb_txt_delete
#define gstoragedb_final  gstoragedb_txt_final

#endif /* _STORAGEDB_TXT_H_ */
