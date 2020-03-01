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

#ifndef _QUESTDB_SQL_H_
#define _QUESTDB_SQL_H_

#include "../int_quest.h"

// プロトタイプ宣言
bool questdb_sql_init(void);
int  questdb_sql_sync(void);
bool  questdb_sql_delete(int char_id);
const struct quest *questdb_sql_load(int char_id);
bool  questdb_sql_save(struct quest *q2);
void questdb_sql_final(void);
int questdb_sql_config_read_sub(const char *w1,const char *w2);

// エイリアス
#define questdb_init   questdb_sql_init
#define questdb_sync   questdb_sql_sync
#define questdb_delete questdb_sql_delete
#define questdb_load   questdb_sql_load
#define questdb_save   questdb_sql_save
#define questdb_final  questdb_sql_final
#define questdb_config_read_sub questdb_sql_config_read_sub

#endif /* _QUESTDB_SQL_H_ */
