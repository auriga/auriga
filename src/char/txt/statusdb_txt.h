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

#ifndef _STATUSDB_TXT_H_
#define _STATUSDB_TXT_H_

#ifndef NO_SCDATA_SAVING

#include "utils.h"
#include "../int_status.h"

// プロトタイプ宣言
bool statusdb_txt_init(void);
int statusdb_txt_sync(void);
bool statusdb_txt_delete(int char_id);
struct scdata *statusdb_txt_load(int char_id);
bool statusdb_txt_save(struct scdata *sc2);
void statusdb_txt_final(void);
int statusdb_txt_config_read_sub(const char *w1, const char *w2);

// エイリアス
#define statusdb_init   statusdb_txt_init
#define statusdb_sync   statusdb_txt_sync
#define statusdb_delete statusdb_txt_delete
#define statusdb_load   statusdb_txt_load
#define statusdb_save   statusdb_txt_save
#define statusdb_final  statusdb_txt_final
#define statusdb_config_read_sub statusdb_txt_config_read_sub

#endif

#endif /* _STATUSDB_TXT_H_ */
