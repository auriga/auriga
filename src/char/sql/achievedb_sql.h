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

#ifndef _ACHIEVEDB_SQL_H_
#define _ACHIEVEDB_SQL_H_

#include "../int_achieve.h"

// プロトタイプ宣言
bool achievedb_sql_init(void);
int  achievedb_sql_sync(void);
bool  achievedb_sql_delete(int char_id);
const struct achieve *achievedb_sql_load(int char_id);
bool  achievedb_sql_save(struct achieve *a2);
void achievedb_sql_final(void);
int achievedb_sql_config_read_sub(const char *w1,const char *w2);

// エイリアス
#define achievedb_init   achievedb_sql_init
#define achievedb_sync   achievedb_sql_sync
#define achievedb_delete achievedb_sql_delete
#define achievedb_load   achievedb_sql_load
#define achievedb_save   achievedb_sql_save
#define achievedb_final  achievedb_sql_final
#define achievedb_config_read_sub achievedb_sql_config_read_sub

#endif /* _ACHIEVEDB_SQL_H_ */
