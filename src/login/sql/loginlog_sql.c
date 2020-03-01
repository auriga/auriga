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

#include <stdio.h>

#include "utils.h"
#include "sqldbs.h"

#include "loginlog_sql.h"

/*==========================================
 * ログ記録
 *------------------------------------------
 */
int loginlog_log_sql(const char *fmt, ...)
{
	char msg[256], buf[512];
	va_list ap;

	va_start(ap, fmt);
	vsnprintf(msg, sizeof(msg), fmt, ap);
	va_end(ap);

	sqldbs_query(&mysql_handle, "INSERT INTO `" LOGINLOG_TABLE "` (`time`,`log`) VALUES (NOW(),'%s')", strecpy(buf, msg));

	return 0;
}

/*==========================================
 * 設定ファイル読込
 *------------------------------------------
 */
int loginlog_config_read_sql(const char *str, const char *str2)
{
	return 0;
}
