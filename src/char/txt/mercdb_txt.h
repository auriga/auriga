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

#ifndef _MERCDB_TXT_H_
#define _MERCDB_TXT_H_

#include "utils.h"

// プロトタイプ宣言
bool mercdb_txt_init(void);
int mercdb_txt_sync(void);
bool mercdb_txt_delete(int merc_id);
const struct mmo_mercstatus* mercdb_txt_load(int merc_id);
bool mercdb_txt_save(struct mmo_mercstatus* p2);
bool mercdb_txt_new(struct mmo_mercstatus *p);
void mercdb_txt_final(void);
int mercdb_txt_config_read_sub(const char* w1,const char *w2);

// エイリアス
#define mercdb_init   mercdb_txt_init
#define mercdb_sync   mercdb_txt_sync
#define mercdb_delete mercdb_txt_delete
#define mercdb_load   mercdb_txt_load
#define mercdb_save   mercdb_txt_save
#define mercdb_new    mercdb_txt_new
#define mercdb_final  mercdb_txt_final
#define mercdb_config_read_sub mercdb_txt_config_read_sub

#endif /* _MERCDB_TXT_H_ */
