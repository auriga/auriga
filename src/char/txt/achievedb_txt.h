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

#ifndef _ACHIEVEDB_TXT_H_
#define _ACHIEVEDB_TXT_H_

#include "../int_achieve.h"

// プロトタイプ宣言
bool achievedb_txt_init(void);
int  achievedb_txt_sync(void);
bool  achievedb_txt_delete(int char_id);
const struct achieve *achievedb_txt_load(int char_id);
bool  achievedb_txt_save(struct achieve *a2);
void achievedb_txt_final(void);
int achievedb_txt_config_read_sub(const char *w1,const char *w2);

// エイリアス
#define achievedb_init   achievedb_txt_init
#define achievedb_sync   achievedb_txt_sync
#define achievedb_delete achievedb_txt_delete
#define achievedb_load   achievedb_txt_load
#define achievedb_save   achievedb_txt_save
#define achievedb_final  achievedb_txt_final
#define achievedb_config_read_sub achievedb_txt_config_read_sub

#endif /* _ACHIEVEDB_TXT_H_ */
