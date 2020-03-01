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

#ifndef TXT_ONLY

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "utils.h"
#include "db.h"
#include "timer.h"
#include "sqldbs.h"
#include "malloc.h"
#include "nullpo.h"

struct sqldbs_handle mysql_handle;
static struct sqldbs_handle *default_handle = &mysql_handle;

/*==========================================
 * デフォルトのハンドラを設定
 *------------------------------------------
 */
void sqldbs_set_default_handle(struct sqldbs_handle *hd)
{
	default_handle = hd;
}

/*==========================================
 * 特殊文字のエスケープ
 *------------------------------------------
 */
char* strecpy(char* pt, const char* spt)
{
	mysql_real_escape_string(&default_handle->handle, pt, spt, (unsigned long)strlen(spt));

	return pt;
}

char* strecpy_(struct sqldbs_handle *hd, char* pt, const char* spt)
{
	nullpo_retr(pt, hd);

	mysql_real_escape_string(&hd->handle, pt, spt, (unsigned long)strlen(spt));

	return pt;
}

/*==========================================
 * クエリ発行
 *------------------------------------------
 */
bool sqldbs_query(struct sqldbs_handle *hd, const char *query, ...)
{
	char sql[65536];
	int n;
	va_list ap;

	nullpo_retr(false, hd);

	va_start(ap, query);
	n = vsnprintf(sql, sizeof(sql) - 1, query, ap);
	va_end(ap);

	if(n < 0 || n >= sizeof(sql) - 1) {
		printf("sqldbs_query: too long query!");
		return false;
	}

	return sqldbs_simplequery(hd, sql);
}

/*==========================================
 * 単純なクエリ発行
 *------------------------------------------
 */
bool sqldbs_simplequery(struct sqldbs_handle *hd, const char *query)
{
	nullpo_retr(false, hd);

	sqldbs_free_result(hd);

	if( mysql_query(&hd->handle, query) )
	{
		printf("DB server Error - %s\n  %s\n\n", mysql_error(&hd->handle), query);
		return false;
	}
	hd->result = mysql_store_result(&hd->handle);

	if( mysql_errno(&hd->handle) != 0 )
	{
		printf("DB server Error - %s\n  %s\n\n", mysql_error(&hd->handle), query);
		return false;
	}

	return true;
}

/*==========================================
 * トランザクションの開始
 *------------------------------------------
 */
bool sqldbs_transaction_start(struct sqldbs_handle *hd)
{
	nullpo_retr(false, hd);

	if(hd->transaction_count < 0) {
		hd->transaction_count = 0;
	}
	if(hd->transaction_count++ > 0) {
		// transaction is nested
		return true;
	}

	return sqldbs_simplequery(hd, "START TRANSACTION");
}

/*==========================================
 * コミット
 *------------------------------------------
 */
bool sqldbs_commit(struct sqldbs_handle *hd)
{
	nullpo_retr(false, hd);

	if(--hd->transaction_count > 0) {
		// transaction is nested
		return true;
	}
	if(hd->transaction_count < 0) {
		hd->transaction_count = 0;
	}

	return sqldbs_simplequery(hd, "COMMIT");
}

/*==========================================
 * ロールバック
 *------------------------------------------
 */
bool sqldbs_rollback(struct sqldbs_handle *hd)
{
	nullpo_retr(false, hd);

	if(--hd->transaction_count > 0) {
		// transaction is nested
		return true;
	}
	if(hd->transaction_count < 0) {
		hd->transaction_count = 0;
	}

	return sqldbs_simplequery(hd, "ROLLBACK");
}

/*==========================================
 * トランザクションの終了
 * COMMIT or ROLLBACK
 *------------------------------------------
 */
bool sqldbs_transaction_end(struct sqldbs_handle *hd, bool result)
{
	if(result)
		return sqldbs_commit(hd);

	return sqldbs_rollback(hd);
}

/*==========================================
 * 結果セットがあるかどうか
 *------------------------------------------
 */
bool sqldbs_has_result(struct sqldbs_handle *hd)
{
	nullpo_retr(false, hd);

	return (hd->result)? true: false;
}

/*==========================================
 * 結果セットの次レコードを取得
 *------------------------------------------
 */
char** sqldbs_fetch(struct sqldbs_handle *hd)
{
	nullpo_retr(false, hd);

	// defined as typedef char **MYSQL_ROW in mysql.h
	return (hd->result)? (char **)mysql_fetch_row(hd->result): NULL;
}

/*==========================================
 * 結果セットの行数を返す
 *------------------------------------------
 */
int sqldbs_num_rows(struct sqldbs_handle *hd)
{
	nullpo_retr(-1, hd);

	return (hd->result)? (int)mysql_num_rows(hd->result): -1;
}

/*==========================================
 * 結果セットの列数を返す
 *------------------------------------------
 */
int sqldbs_num_fields(struct sqldbs_handle *hd)
{
	nullpo_retr(-1, hd);

	return (hd->result)? (int)mysql_num_fields(hd->result): -1;
}

/*==========================================
 * AUTO_INCREMENTの生成値を返す
 *------------------------------------------
 */
int sqldbs_insert_id(struct sqldbs_handle *hd)
{
	nullpo_retr(-1, hd);

	return (int)mysql_insert_id(&hd->handle);
}

/*==========================================
 * 変更された行数を返す
 *------------------------------------------
 */
int sqldbs_affected_rows(struct sqldbs_handle *hd)
{
	nullpo_retr(-1, hd);

	return (int)mysql_affected_rows(&hd->handle);
}

/*==========================================
 * 結果セット解放
 *------------------------------------------
 */
void sqldbs_free_result(struct sqldbs_handle *hd)
{
	nullpo_retv(hd);

	if(hd->result) {
		mysql_free_result(hd->result);
		hd->result = NULL;
	}
}

/*==========================================
 * MYSQL_STMTのinit
 *------------------------------------------
 */
struct sqldbs_stmt* sqldbs_stmt_init(struct sqldbs_handle *hd)
{
	struct sqldbs_stmt *st;

	nullpo_retr(NULL, hd);

	st = (struct sqldbs_stmt *)aCalloc(1, sizeof(struct sqldbs_stmt));

	if( (st->stmt = mysql_stmt_init(&hd->handle)) == NULL ) {
		printf("DB server Error - %s\n", mysql_error(&hd->handle));
		aFree(st);
		return NULL;
	}

	st->handle = hd;
	st->bind_params  = false;
	st->bind_columns = false;

	// stmtをリストとして保存しておく
	linkdb_insert(&hd->stmt_list, st, st);

	return st;
}

/*==========================================
 * プリペアドステートメントのクエリ準備
 *------------------------------------------
 */
bool sqldbs_stmt_prepare(struct sqldbs_stmt *st, const char *query, ...)
{
	char sql[65536];
	int n;
	va_list ap;

	nullpo_retr(false, st);

	va_start(ap, query);
	n = vsnprintf(sql, sizeof(sql) - 1, query, ap);
	va_end(ap);

	if(n < 0 || n >= sizeof(sql) - 1) {
		printf("sqldbs_query: too long query!");
		return false;
	}

	return sqldbs_stmt_simpleprepare(st, sql);
}

/*==========================================
 * 単純なプリペアドステートメントのクエリ準備
 *------------------------------------------
 */
bool sqldbs_stmt_simpleprepare(struct sqldbs_stmt *st, const char *query)
{
	nullpo_retr(false, st);

	// 初期化
	st->bind_params  = false;
	st->bind_columns = false;

	if(st->query) {
		aFree(st->query);
	}
	st->query = (char *)aStrdup(query);

	if( mysql_stmt_prepare(st->stmt, query, (unsigned long)strlen(query)) )
	{
		printf("DB server Error - %s\n  %s\n\n", mysql_stmt_error(st->stmt), query);
		return false;
	}

	return true;
}

/*==========================================
 * クエリから作成済みのstmtを検索する
 *------------------------------------------
 */
struct sqldbs_stmt* sqldbs_stmt_search(struct sqldbs_handle *hd, const char *query)
{
	nullpo_retr(NULL, hd);

	if(hd->stmt_list) {
		struct linkdb_node *node = hd->stmt_list;
		while(node) {
			struct sqldbs_stmt *st = (struct sqldbs_stmt *)node->key;

			if(st->query && strcmp(st->query, query) == 0) {
				return st;
			}
			node = node->next;
		}
	}

	return NULL;
}

/*==========================================
 * 数値型のサイズからMYSQL_TYPEを返す
 *------------------------------------------
 */
static enum enum_field_types sqldbs_num2datatype(size_t size)
{
	switch(size)
	{
		case 4:
			return MYSQL_TYPE_LONG;
		case 8:
			return MYSQL_TYPE_LONGLONG;
	}

	printf("sqldbs_num2datatype: Unsupported integer size %lu\n", (unsigned long)size);
	return MYSQL_TYPE_NULL;
}

/*==========================================
 * MYSQL_BINDにパラメータをセット
 *------------------------------------------
 */
static void sqldbs_stmt_bind_datatype(MYSQL_BIND *bind, int buffer_type, void *buffer, size_t buffer_length, unsigned long *length, char *is_null)
{
	nullpo_retv(bind);

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
 * ステートメントのパラメータ数を取得
 *------------------------------------------
 */
size_t sqldbs_stmt_param_count(struct sqldbs_stmt *st)
{
	nullpo_retr(0, st);

	return (size_t)mysql_stmt_param_count(st->stmt);
}

/*==========================================
 * MYSQL_BINDにパラメータをセット
 *------------------------------------------
 */
bool sqldbs_stmt_bind_param(struct sqldbs_stmt *st, size_t idx, int buffer_type, void *buffer, size_t buffer_length)
{
	nullpo_retr(false, st);

	if(st->bind_params == false) {
		size_t i, count;

		// MYSQL_BINDの用意
		count = sqldbs_stmt_param_count(st);
		if(st->max_params < count) {
			st->max_params = count;
			st->params = (MYSQL_BIND *)aRealloc(st->params, sizeof(MYSQL_BIND) * count);
		}
		memset(st->params, 0, count * sizeof(MYSQL_BIND));
		for(i = 0; i < count; i++) {
			st->params[i].buffer_type = MYSQL_TYPE_NULL;
		}
	}

	if(idx >= st->max_params)
		return false;

	sqldbs_stmt_bind_datatype(st->params + idx, buffer_type, buffer, buffer_length, NULL, NULL);
	st->bind_params = true;

	return true;
}

/*==========================================
 * プリペアドステートメントの実行
 *------------------------------------------
 */
bool sqldbs_stmt_execute(struct sqldbs_stmt *st)
{
	nullpo_retr(false, st);

	if( (st->bind_params && mysql_stmt_bind_param(st->stmt, st->params)) || mysql_stmt_execute(st->stmt) )
	{
		printf("DB server Error - %s\n  %s\n\n", mysql_stmt_error(st->stmt), st->query);
		return false;
	}

	if( mysql_stmt_store_result(st->stmt) )
	{
		printf("DB server Error - %s\n  %s\n\n", mysql_stmt_error(st->stmt), st->query);
		return false;
	}

	return true;
}

/*==========================================
 * MYSQL_BINDにステートメント結果をセット
 *------------------------------------------
 */
bool sqldbs_stmt_bind_column(struct sqldbs_stmt *st, size_t idx, int buffer_type, void *buffer, size_t buffer_length)
{
	nullpo_retr(false, st);

	if(st->bind_columns == false) {
		size_t i, cols;

		// MYSQL_BINDの用意
		cols = sqldbs_stmt_field_count(st);
		if(st->max_columns < cols) {
			st->max_columns = cols;
			st->columns = (MYSQL_BIND *)aRealloc(st->columns, sizeof(MYSQL_BIND) * cols);
		}
		memset(st->columns, 0, cols * sizeof(MYSQL_BIND));
		for(i = 0; i < cols; i++) {
			st->columns[i].buffer_type = MYSQL_TYPE_NULL;
		}
	}

	if(idx >= st->max_columns)
		return false;

	sqldbs_stmt_bind_datatype(st->columns + idx, buffer_type, buffer, buffer_length, NULL, NULL);
	st->bind_columns = true;

	return true;
}

/*==========================================
 * ステートメント結果セットのバインド
 *------------------------------------------
 */
bool sqldbs_stmt_bind_result(struct sqldbs_stmt *st)
{
	nullpo_retr(false, st);

	if( st->bind_columns && mysql_stmt_bind_result(st->stmt, st->columns) )
	{
		printf("DB server Error - %s\n  %s\n\n", mysql_stmt_error(st->stmt), st->query);
		return false;
	}

	return true;
}

/*==========================================
 * ステートメント結果セットの次レコードを取得
 *------------------------------------------
 */
bool sqldbs_stmt_fetch(struct sqldbs_stmt *st)
{
	int ret = 0;
	const char *msg = NULL;

	nullpo_retr(false, st);

	ret = mysql_stmt_fetch(st->stmt);

	switch(ret) {
		case 0:
			return true;
		case MYSQL_NO_DATA:
			return false;
		case MYSQL_DATA_TRUNCATED:
			msg = "data truncated";
			break;
		default:
			msg = mysql_stmt_error(st->stmt);
			break;
	}
	if(msg) {
		printf("DB server Error - %s\n  %s\n\n", msg, st->query);
	}

	return false;
}

/*==========================================
 * ステートメント結果セットの行数を返す
 *------------------------------------------
 */
int sqldbs_stmt_num_rows(struct sqldbs_stmt *st)
{
	nullpo_retr(-1, st);

	return (int)mysql_stmt_num_rows(st->stmt);
}

/*==========================================
 * ステートメント結果の列数を返す
 *------------------------------------------
 */
int sqldbs_stmt_field_count(struct sqldbs_stmt *st)
{
	nullpo_retr(-1, st);

	return (int)mysql_stmt_field_count(st->stmt);
}

/*==========================================
 * ステートメントのAUTO_INCREMENTの生成値を返す
 *------------------------------------------
 */
int sqldbs_stmt_insert_id(struct sqldbs_stmt *st)
{
	nullpo_retr(-1, st);

	return (int)mysql_stmt_insert_id(st->stmt);
}

/*==========================================
 * ステートメント変更された行数を返す
 *------------------------------------------
 */
int sqldbs_stmt_affected_rows(struct sqldbs_stmt *st)
{
	nullpo_retr(-1, st);

	return (int)mysql_stmt_affected_rows(st->stmt);
}

/*==========================================
 * ステートメント結果セット解放
 *------------------------------------------
 */
void sqldbs_stmt_free_result(struct sqldbs_stmt *st)
{
	nullpo_retv(st);

	mysql_stmt_free_result(st->stmt);
}

/*==========================================
 * ステートメントのclose
 *------------------------------------------
 */
void sqldbs_stmt_close(struct sqldbs_stmt *st)
{
	nullpo_retv(st);

	sqldbs_stmt_free_result(st);
	mysql_stmt_close(st->stmt);

	if(st->handle)
		linkdb_erase(&st->handle->stmt_list, st);

	if(st->params) {
		aFree(st->params);
	}
	if(st->columns) {
		aFree(st->columns);
	}
	if(st->query) {
		aFree(st->query);
	}
	aFree(st);

	return;
}

/*==========================================
 * Keepaliveタイマー
 * 定期的にpingを発行してタイムアウトを抑制
 *------------------------------------------
 */
static int sqldbs_keepalive_timer(int tid, unsigned int tick, int id, void *data)
{
	struct sqldbs_handle *hd = (struct sqldbs_handle *)data;

	if(hd)
		mysql_ping(&hd->handle);

	return 0;
}

/*==========================================
 * 切断
 *------------------------------------------
 */
void sqldbs_close(struct sqldbs_handle *hd)
{
	nullpo_retv(hd);

	printf("Closing DabaseServer ");
	if(hd->tag) {
		printf("[%s] ", hd->tag);
	}
	printf("... ");

	if(hd->stmt_list) {
		struct linkdb_node *node = hd->stmt_list;

		while(node) {
			struct sqldbs_stmt *st = (struct sqldbs_stmt *)node->key;

			// sqldbs_stmt_close() 内で linkdb_erase() されないためにNULLにしておく
			st->handle = NULL;

			sqldbs_stmt_close(st);
			node = node->next;
		}
		linkdb_final(&hd->stmt_list);
	}

	mysql_close(&hd->handle);
	printf(" OK\n");

	if(hd->tag) {
		aFree(hd->tag);
		hd->tag = NULL;
	}
}

/*==========================================
 * 接続
 *------------------------------------------
 */
bool sqldbs_connect(struct sqldbs_handle *hd, const char *host, const char *user, const char *passwd,
	const char *db, unsigned short port, const char *charset, int keepalive, const char *tag)
{
	if(hd == NULL)
		return false;

	hd->result = NULL;
	hd->transaction_count = 0;
	hd->tag = NULL;

	if(mysql_init(&hd->handle) == NULL) {
		printf("Database Server Out of Memory\n");
		return false;
	}

	printf("Connecting Database Server -> %s@%s:%d/%s", user, host, port, db);
	if(charset && *charset) {
		mysql_options(&hd->handle, MYSQL_SET_CHARSET_NAME, charset);
		printf(" (charset: %s)", charset);
	}
	printf("\n  ... ");

	if(!mysql_real_connect(&hd->handle, host, user, passwd, db, port, NULL, 0)) {
		printf("%s\n", mysql_error(&hd->handle));
		return false;
	}
	printf("connect success!\n");

	if(charset && *charset) {
		sqldbs_query(hd, "SET NAMES %s", charset);
	}

	printf("MySQL Server version %s\n", mysql_get_server_info(&hd->handle));

	if(keepalive > 0) {
		add_timer_func_list(sqldbs_keepalive_timer);
		add_timer_interval(gettick() + keepalive * 1000, sqldbs_keepalive_timer, 0, hd, keepalive * 1000);
		printf("MySQL keepalive timer set: interval = %d (sec)\n", keepalive);
	}

	if(tag)
		hd->tag = (char *)aStrdup(tag);

	return true;
}

#endif /* ifndef TXT_ONLY */
