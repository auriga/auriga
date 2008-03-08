/*
 * Copyright (C) 2002-2007  Auriga
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

#ifndef TXT_ONLY

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "utils.h"
#include "sqldbs.h"

MYSQL mysql_handle;
char tmp_sql[65535];

/*==========================================
 * 特殊文字のエスケープ
 *------------------------------------------
 */
char* strecpy(char* pt, const char* spt)
{
	mysql_real_escape_string(&mysql_handle, pt, spt, strlen(spt));

	return pt;
}

/*==========================================
 * クエリ発行
 *------------------------------------------
 */
int sqldbs_query(MYSQL *handle, const char *query, ...)
{
	char sql[65535];
	va_list ap;

	va_start(ap, query);
	vsprintf(sql, query, ap);
	va_end(ap);

	if(mysql_query(handle, sql)) {
		char command[64] = "";
		sscanf(sql, "%63[A-Za-z_]", command);
		printf("DB server Error (%s)- %s\n", command, mysql_error(handle));
		return 1;
	}
	return 0;
}

/*==========================================
 * 結果セット取得
 *------------------------------------------
 */
MYSQL_RES* sqldbs_store_result(MYSQL *handle)
{
	return mysql_store_result(handle);
}

/*==========================================
 * 結果セットの次レコードを取得
 *------------------------------------------
 */
MYSQL_ROW sqldbs_fetch(MYSQL_RES *res)
{
	return (res)? mysql_fetch_row(res): NULL;
}

/*==========================================
 * 結果セットの行数を返す
 *------------------------------------------
 */
int sqldbs_num_rows(MYSQL_RES *res)
{
	return (res)? (int)mysql_num_rows(res): -1;
}

/*==========================================
 * 結果セットの列数を返す
 *------------------------------------------
 */
int sqldbs_num_fields(MYSQL_RES *res)
{
	return (res)? (int)mysql_num_fields(res): -1;
}

/*==========================================
 * 結果セット解放
 *------------------------------------------
 */
void sqldbs_free_result(MYSQL_RES *res)
{
	if(res)
		mysql_free_result(res);
}

/*==========================================
 * AUTO_INCREMENTの生成値を返す
 *------------------------------------------
 */
int sqldbs_insert_id(MYSQL *handle)
{
	return (int)mysql_insert_id(handle);
}

/*==========================================
 * 変更された行数を返す
 *------------------------------------------
 */
int sqldbs_affected_rows(MYSQL *handle)
{
	return (int)mysql_affected_rows(handle);
}

/*==========================================
 * 切断
 *------------------------------------------
 */
void sqldbs_close(MYSQL *handle)
{
	mysql_close(handle);
	printf("close DB connect....\n");
}

/*==========================================
 * 接続
 *------------------------------------------
 */
int sqldbs_connect(MYSQL *handle, const char *host, const char *user, const char *passwd,
	const char *db, unsigned short port, const char *charset)
{
	if(handle == NULL)
		return 1;

	if(mysql_init(handle) == NULL) {
		printf("Database Server Out of Memory\n");
		return 1;
	}

	printf("Connecting Database Server");
	if(charset && *charset) {
		mysql_options(handle, MYSQL_SET_CHARSET_NAME, charset);
		printf(" (charset: %s)", charset);
	}
	printf("...\n");

	if(!mysql_real_connect(handle, host, user, passwd, db, port, NULL, 0)) {
		printf("%s\n", mysql_error(handle));
		return 1;
	}
	printf("connect success! MySQL Server version %s\n", mysql_get_server_info(handle));

	return 0;
}

#endif /* ifndef TXT_ONLY */
