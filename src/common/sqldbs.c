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
#include "timer.h"
#include "sqldbs.h"

MYSQL mysql_handle;
char tmp_sql[65535];

/*==========================================
 * 特殊文字のエスケープ
 *------------------------------------------
 */
char* strecpy(char* pt, const char* spt)
{
	mysql_real_escape_string(&mysql_handle, pt, spt, (unsigned long)strlen(spt));

	return pt;
}

char* strecpy_(MYSQL *handle, char* pt, const char* spt)
{
	mysql_real_escape_string(handle, pt, spt, (unsigned long)strlen(spt));

	return pt;
}

/*==========================================
 * クエリ発行
 *------------------------------------------
 */
bool sqldbs_query(MYSQL *handle, const char *query, ...)
{
	char sql[65535];
	va_list ap;

	va_start(ap, query);
	vsprintf(sql, query, ap);
	va_end(ap);

	if( mysql_query(handle, sql) )
	{
		char command[64] = "";
		sscanf(sql, "%63[A-Za-z_]", command);
		printf("DB server Error (%s)- %s\n", command, mysql_error(handle));
		return false;
	}
	return true;
}

/*==========================================
 * 単純なクエリ発行
 *------------------------------------------
 */
bool sqldbs_simplequery(MYSQL *handle, const char *query)
{
	if( mysql_query(handle, query) )
	{
		char command[64] = "";
		sscanf( query, "%63[A-Za-z_]", command );
		printf( "DB server Error (%s)- %s\n", command, mysql_error(handle) );
		return false;
	}

	return true;
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
 * MYSQL_STMTのinit
 *------------------------------------------
 */
MYSQL_STMT* sqldbs_stmt_init(MYSQL *handle)
{
	MYSQL_STMT *stmt;

	if( (stmt = mysql_stmt_init(&mysql_handle)) == NULL )
		printf("DB error - %s\n", mysql_error(&mysql_handle));

	return stmt;
}

/*==========================================
 * プリペアドステートメントのクエリ準備
 *------------------------------------------
 */
bool sqldbs_stmt_prepare(MYSQL_STMT *stmt, const char *query, ...)
{
	char sql[65535];
	va_list ap;

	va_start(ap, query);
	vsprintf(sql, query, ap);
	va_end(ap);

	if( mysql_stmt_prepare(stmt,sql,strlen(sql)) )
	{
		char command[64] = "";
		sscanf(sql, "%63[A-Za-z_]", command);
		printf("DB server Error (%s)- %s\n", command, mysql_stmt_error(stmt));
		return false;
	}

	return true;
}

/*==========================================
 * 数値型のサイズからMYSQL_TYPEを返す
 *------------------------------------------
 */
static int sqldbs_num2datatype(size_t size)
{
	switch(size)
	{
	case 4:
		return MYSQL_TYPE_LONG;
	case 8:
		return MYSQL_TYPE_LONGLONG;
	default:
		printf("Unsupported integer size %zd\n",size);
		return MYSQL_TYPE_NULL;
	}
}

/*==========================================
 * MYSQL_BINDにパラメータをセット
 *------------------------------------------
 */
void sqldbs_stmt_bind_param(MYSQL_BIND *bind, int buffer_type, void *buffer, size_t buffer_length, unsigned long *length, char *is_null)
{
	memset(bind, 0, sizeof(MYSQL_BIND));

	switch(buffer_type)
	{
	case SQL_DATA_TYPE_NULL:
		bind->buffer_type = MYSQL_TYPE_NULL;
		buffer_length = 0;
		break;
	case SQL_DATA_TYPE_UINT8: bind->is_unsigned = 1;
	case SQL_DATA_TYPE_INT8:
		bind->buffer_type = MYSQL_TYPE_TINY;
		buffer_length = 1;
		break;
	case SQL_DATA_TYPE_UINT16: bind->is_unsigned = 1;
	case SQL_DATA_TYPE_INT16:
		bind->buffer_type = MYSQL_TYPE_SHORT;
		buffer_length = 2;
		break;
	case SQL_DATA_TYPE_UINT32: bind->is_unsigned = 1;
	case SQL_DATA_TYPE_INT32:
		bind->buffer_type = MYSQL_TYPE_LONG;
		buffer_length = 4;
		break;
	case SQL_DATA_TYPE_UINT64: bind->is_unsigned = 1;
	case SQL_DATA_TYPE_INT64:
		bind->buffer_type = MYSQL_TYPE_LONGLONG;
		buffer_length = 8;
		break;
	case SQL_DATA_TYPE_UCHAR: bind->is_unsigned = 1;
	case SQL_DATA_TYPE_CHAR:
		bind->buffer_type = MYSQL_TYPE_TINY;
		buffer_length = 1;
		break;
	case SQL_DATA_TYPE_USHORT: bind->is_unsigned = 1;
	case SQL_DATA_TYPE_SHORT:
		bind->buffer_type = MYSQL_TYPE_SHORT;
		buffer_length = 2;
		break;
	case SQL_DATA_TYPE_UINT: bind->is_unsigned = 1;
	case SQL_DATA_TYPE_INT:
		bind->buffer_type = MYSQL_TYPE_LONG;
		buffer_length = 4;
		break;
	case SQL_DATA_TYPE_ULONG: bind->is_unsigned = 1;
	case SQL_DATA_TYPE_LONG:
		bind->buffer_type = sqldbs_num2datatype(sizeof(long));
		buffer_length = sizeof(long);
		break;
#ifndef __BORLANDC__
	case SQL_DATA_TYPE_ULONGLONG: bind->is_unsigned = 1;
	case SQL_DATA_TYPE_LONGLONG:
		bind->buffer_type = sqldbs_num2datatype(sizeof(long long));
		buffer_length = sizeof(long long);
		break;
#endif
	case SQL_DATA_TYPE_FLOAT:
		bind->buffer_type = MYSQL_TYPE_FLOAT;
		buffer_length = 4;
		break;
	case SQL_DATA_TYPE_DOUBLE:
		bind->buffer_type = MYSQL_TYPE_DOUBLE;
		buffer_length = 8;
		break;
	case SQL_DATA_TYPE_STRING:
		bind->buffer_type = MYSQL_TYPE_STRING;
		break;
	case SQL_DATA_TYPE_VAR_STRING:
		bind->buffer_type = MYSQL_TYPE_VAR_STRING;
		break;
	case SQL_DATA_TYPE_ENUM:
		bind->buffer_type = MYSQL_TYPE_ENUM;
		break;
	}
	bind->buffer = buffer;
	bind->buffer_length = (unsigned long)buffer_length;
	bind->length = length;
	bind->is_null = (my_bool *)is_null;

	return;
}

/*==========================================
 * プリペアドステートメントの実行
 *------------------------------------------
 */
bool sqldbs_stmt_execute(MYSQL_STMT *stmt, MYSQL_BIND *bind)
{
	if( mysql_stmt_bind_param(stmt,bind) || mysql_stmt_execute(stmt) )
	{
		printf("DB server Error %s\n", mysql_stmt_error(stmt));
		return false;
	}

	return true;
}

/*==========================================
 * ステートメントMYSQL_RESの取得
 *------------------------------------------
 */
MYSQL_RES* sqldbs_stmt_result_metadata(MYSQL_STMT *stmt)
{
	return mysql_stmt_result_metadata(stmt);
}

/*==========================================
 * ステートメント結果セット取得
 *------------------------------------------
 */
bool sqldbs_stmt_store_result(MYSQL_STMT *stmt)
{
	if( mysql_stmt_store_result(stmt) )
	{
		printf("DB server Error %s\n", mysql_stmt_error(stmt));
		return false;
	}

	return true;
}

/*==========================================
 * ステートメント結果セットの次レコードを取得
 *------------------------------------------
 */
bool sqldbs_stmt_fetch(MYSQL_STMT *stmt)
{
	return mysql_stmt_fetch(stmt);
}

/*==========================================
 * ステートメントのclose
 *------------------------------------------
 */
void sqldbs_stmt_close(MYSQL_STMT *stmt)
{
	mysql_stmt_close(stmt);

	return;
}

/*==========================================
 * Keepaliveタイマー
 * 定期的にpingを発行してタイムアウトを抑制
 *------------------------------------------
 */
static int sqldbs_keepalive_timer(int tid, unsigned int tick, int id, void *data)
{
	mysql_ping((MYSQL *)data);

	return 0;
}

/*==========================================
 * 切断
 *------------------------------------------
 */
void sqldbs_close(MYSQL *handle, const char *msg)
{
	printf("Closing DabaseServer %s ... ", (msg)? msg: "");
	mysql_close(handle);
	printf(" OK\n");
}

/*==========================================
 * 接続
 *------------------------------------------
 */
bool sqldbs_connect(MYSQL *handle, const char *host, const char *user, const char *passwd,
	const char *db, unsigned short port, const char *charset, int keepalive)
{
	if(handle == NULL)
		return false;

	if(mysql_init(handle) == NULL) {
		printf("Database Server Out of Memory\n");
		return false;
	}

	printf("Connecting Database Server -> %s@%s:%d/%s", user, host, port, db);
	if(charset && *charset) {
		mysql_options(handle, MYSQL_SET_CHARSET_NAME, charset);
		printf(" (charset: %s)", charset);
	}
	printf("\n  ... ");

	if(!mysql_real_connect(handle, host, user, passwd, db, port, NULL, 0)) {
		printf("%s\n", mysql_error(handle));
		return false;
	}
	printf("connect success!\n");

	if(charset && *charset) {
		sqldbs_query(handle, "SET NAMES %s", charset);
	}

	printf("MySQL Server version %s\n", mysql_get_server_info(handle));

	if(keepalive > 0) {
		add_timer_func_list(sqldbs_keepalive_timer);
		add_timer_interval(gettick() + keepalive * 1000, sqldbs_keepalive_timer, 0, handle, keepalive * 1000);
		printf("MySQL keepalive timer set: interval = %d (sec)\n", keepalive);
	}

	return true;
}

#endif /* ifndef TXT_ONLY */
