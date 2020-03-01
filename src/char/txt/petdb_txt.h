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

#ifndef _PETDB_TXT_H_
#define _PETDB_TXT_H_

#include "utils.h"

// プロトタイプ宣言
bool petdb_txt_init(void);
int petdb_txt_sync(void);
bool petdb_txt_delete(int pet_id);
const struct s_pet* petdb_txt_load(int pet_id);
bool petdb_txt_save(struct s_pet* p2);
bool petdb_txt_new(struct s_pet *p);
void petdb_txt_final(void);
int petdb_txt_config_read_sub(const char* w1,const char *w2);

// エイリアス
#define petdb_init   petdb_txt_init
#define petdb_sync   petdb_txt_sync
#define petdb_delete petdb_txt_delete
#define petdb_load   petdb_txt_load
#define petdb_save   petdb_txt_save
#define petdb_new    petdb_txt_new
#define petdb_final  petdb_txt_final
#define petdb_config_read_sub petdb_txt_config_read_sub

#endif /* _PETDB_TXT_H_ */
