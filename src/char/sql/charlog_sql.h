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

#ifndef _CHARLOG_SQL_H_
#define _CHARLOG_SQL_H_

// プロトタイプ宣言
int charlog_log_sql(const char *fmt, ...);
int charlog_config_read_sql(const char *str, const char *str2);

// エイリアス
#define charlog_log charlog_log_sql
#define charlog_config_read charlog_config_read_sql

#endif /* _CHARLOG_SQL_H_ */
