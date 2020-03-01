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

#ifndef _ELEMDB_TXT_H_
#define _ELEMDB_TXT_H_

#include "utils.h"

// プロトタイプ宣言
bool elemdb_txt_init(void);
int elemdb_txt_sync(void);
bool elemdb_txt_delete(int elem_id);
const struct mmo_elemstatus* elemdb_txt_load(int elem_id);
bool elemdb_txt_save(struct mmo_elemstatus* p2);
bool elemdb_txt_new(struct mmo_elemstatus *p);
void elemdb_txt_final(void);
int elemdb_txt_config_read_sub(const char* w1,const char *w2);

// エイリアス
#define elemdb_init   elemdb_txt_init
#define elemdb_sync   elemdb_txt_sync
#define elemdb_delete elemdb_txt_delete
#define elemdb_load   elemdb_txt_load
#define elemdb_save   elemdb_txt_save
#define elemdb_new    elemdb_txt_new
#define elemdb_final  elemdb_txt_final
#define elemdb_config_read_sub elemdb_txt_config_read_sub

#endif /* _ELEMDB_TXT_H_ */
