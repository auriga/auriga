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

#ifndef _LOGINLOG_TXT_H_
#define _LOGINLOG_TXT_H_

// プロトタイプ宣言
int loginlog_log_txt(const char *fmt, ...);
int loginlog_config_read_txt(const char *str, const char *str2);

// エイリアス
#define loginlog_log loginlog_log_txt
#define loginlog_config_read loginlog_config_read_txt

#endif /* _LOGINLOG_TXT_H_ */
