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

#ifndef _SQLDB_H_
#define _SQLDB_H_

#ifndef TXT_ONLY

#ifdef WINDOWS
	#include <winsock.h>
#else
	#include <sys/socket.h>
	#include <netinet/in.h>
#endif

#include <mysql.h>
#include "utils.h"
#include "db.h"

#ifdef _MSC_VER
#pragma comment(lib,"libmysql.lib")
#endif

struct sqldbs_handle {
	MYSQL handle;
	MYSQL_RES *result;
	struct linkdb_node *stmt_list;
	int transaction_count;
	char *tag;
};

struct sqldbs_stmt {
	struct sqldbs_handle *handle;
	MYSQL_STMT *stmt;
	MYSQL_BIND *params;
	MYSQL_BIND *columns;
	size_t max_params;
	size_t max_columns;
	bool bind_params;
	bool bind_columns;
	char *query;
};

extern struct sqldbs_handle mysql_handle;

// login
#define LOGIN_TABLE    "login"
#define LOGINLOG_TABLE "loginlog"
#define WORLDREG_TABLE "worldreg"

// char
#define CHAR_TABLE            "char_data"
#define FRIEND_TABLE          "friend"
#define CART_TABLE            "cart_inventory"
#define INVENTORY_TABLE       "inventory"
#define CHARLOG_TABLE         "charlog"
#define SKILL_TABLE           "skill"
#define MEMO_TABLE            "memo"
#define FEEL_TABLE            "feel_info"
#define HOTKEY_TABLE          "hotkey"
#define ELEM_TABLE            "elemental"
#define GUILD_TABLE           "guild"
#define GUILD_ALLIANCE_TABLE  "guild_alliance"
#define GUILD_CASTLE_TABLE    "guild_castle"
#define GUILD_EXPULSION_TABLE "guild_expulsion"
#define GUILD_MEMBER_TABLE    "guild_member"
#define GUILD_POSITION_TABLE  "guild_position"
#define GUILD_SKILL_TABLE     "guild_skill"
#define HOMUN_TABLE           "homunculus"
#define HOMUN_SKILL_TABLE     "homunculus_skill"
#define MAIL_TABLE            "mail"
#define MAIL_DATA_TABLE       "mail_data"
#define MERC_TABLE            "mercenary"
#define MERC_EMPLOY_TABLE     "mercenary_employ"
#define PARTY_TABLE           "party"
#define PET_TABLE             "pet"
#define QUEST_TABLE           "quest"
#define ACHIEVE_TABLE         "achieve"
#define SCDATA_TABLE          "status_change"
#define STORAGE_TABLE         "storage"
#define GUILD_STORAGE_TABLE   "guild_storage"
#define INTERLOG_TABLE        "interlog"
#define ACCOUNTREG_TABLE      "accountreg"
#define GLOBALREG_TABLE       "globalreg"

// map
#define MAPREG_TABLE "mapreg"

// プリペアドステートメント型サイズ変換用テーブル
enum {
	SQL_DATA_TYPE_NULL,
	SQL_DATA_TYPE_INT8,
	SQL_DATA_TYPE_INT16,
	SQL_DATA_TYPE_INT32,
	SQL_DATA_TYPE_INT64,
	SQL_DATA_TYPE_UINT8,
	SQL_DATA_TYPE_UINT16,
	SQL_DATA_TYPE_UINT32,
	SQL_DATA_TYPE_UINT64,
	SQL_DATA_TYPE_CHAR,
	SQL_DATA_TYPE_SHORT,
	SQL_DATA_TYPE_INT,
	SQL_DATA_TYPE_LONG,
	SQL_DATA_TYPE_LONGLONG,
	SQL_DATA_TYPE_UCHAR,
	SQL_DATA_TYPE_USHORT,
	SQL_DATA_TYPE_UINT,
	SQL_DATA_TYPE_ULONG,
	SQL_DATA_TYPE_ULONGLONG,
	SQL_DATA_TYPE_FLOAT,
	SQL_DATA_TYPE_DOUBLE,
	SQL_DATA_TYPE_STRING,
	SQL_DATA_TYPE_VAR_STRING,
	SQL_DATA_TYPE_ENUM
};

void sqldbs_set_default_handle(struct sqldbs_handle *hd);
char* strecpy(char* pt, const char* spt);
char* strecpy_(struct sqldbs_handle *hd, char* pt, const char* spt);

bool sqldbs_query(struct sqldbs_handle *hd, const char *query, ...);
bool sqldbs_simplequery(struct sqldbs_handle *hd, const char *query);
bool sqldbs_transaction_start(struct sqldbs_handle *hd);
bool sqldbs_commit(struct sqldbs_handle *hd);
bool sqldbs_rollback(struct sqldbs_handle *hd);
bool sqldbs_transaction_end(struct sqldbs_handle *hd, bool result);

char** sqldbs_fetch(struct sqldbs_handle *hd);
bool sqldbs_has_result(struct sqldbs_handle *hd);
int sqldbs_num_rows(struct sqldbs_handle *hd);
int sqldbs_num_fields(struct sqldbs_handle *hd);
void sqldbs_free_result(struct sqldbs_handle *hd);
int sqldbs_insert_id(struct sqldbs_handle *hd);
int sqldbs_affected_rows(struct sqldbs_handle *hd);

// prepared statement
struct sqldbs_stmt* sqldbs_stmt_init(struct sqldbs_handle *hd);
bool sqldbs_stmt_prepare(struct sqldbs_stmt *st, const char *query, ...);
bool sqldbs_stmt_simpleprepare(struct sqldbs_stmt *st, const char *query);
struct sqldbs_stmt* sqldbs_stmt_search(struct sqldbs_handle *hd, const char *query);
size_t sqldbs_stmt_param_count(struct sqldbs_stmt *st);
bool sqldbs_stmt_bind_param(struct sqldbs_stmt *st, size_t idx, int buffer_type, void *buffer, size_t buffer_length);
bool sqldbs_stmt_execute(struct sqldbs_stmt *st);
bool sqldbs_stmt_bind_column(struct sqldbs_stmt *st, size_t idx, int buffer_type, void *buffer, size_t buffer_length);
bool sqldbs_stmt_bind_result(struct sqldbs_stmt *st);
bool sqldbs_stmt_fetch(struct sqldbs_stmt *st);
int sqldbs_stmt_num_rows(struct sqldbs_stmt *st);
int sqldbs_stmt_field_count(struct sqldbs_stmt *st);
int sqldbs_stmt_insert_id(struct sqldbs_stmt *st);
int sqldbs_stmt_affected_rows(struct sqldbs_stmt *st);
void sqldbs_stmt_free_result(struct sqldbs_stmt *st);
void sqldbs_stmt_close(struct sqldbs_stmt *st);

// 接続
void sqldbs_close(struct sqldbs_handle *hd);
bool sqldbs_connect(struct sqldbs_handle *hd, const char *host, const char *user, const char *passwd,
	const char *db, unsigned short port, const char *charset, int keepalive, const char *tag);

#endif	// if TXT

#endif	// _SQLDB_H_
