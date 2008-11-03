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

#ifdef _MSC_VER
#pragma comment(lib,"libmysql.lib")
#endif

extern MYSQL mysql_handle;
extern char tmp_sql[65535];

// login
#define LOGIN_TABLE    "login"
#define LOGINLOG_TABLE "loginlog"
#define REG_TABLE      "global_reg_value"

// char
#define CHAR_TABLE            "char"
#define FRIEND_TABLE          "friend"
#define CART_TABLE            "cart_inventory"
#define INVENTORY_TABLE       "inventory"
#define CHARLOG_TABLE         "charlog"
#define SKILL_TABLE           "skill"
#define MEMO_TABLE            "memo"
#define FEEL_TABLE            "feel_info"
#define HOTKEY_TABLE          "hotkey"
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
#define MERC_SKILL_TABLE      "mercenary_skill"
#define PARTY_TABLE           "party"
#define PET_TABLE             "pet"
#define SCDATA_TABLE          "status_change"
#define STORAGE_TABLE         "storage"
#define GUILD_STORAGE_TABLE   "guild_storage"
#define INTERLOG_TABLE        "interlog"

// map
#define MAPREG_TABLE "mapreg"

char* strecpy(char* pt, const char* spt);

int sqldbs_query(MYSQL *handle, const char *query, ...);
MYSQL_RES* sqldbs_store_result(MYSQL *handle);
MYSQL_ROW sqldbs_fetch(MYSQL_RES *res);
int sqldbs_num_rows(MYSQL_RES *res);
int sqldbs_num_fields(MYSQL_RES *res);
void sqldbs_free_result(MYSQL_RES *res);
int sqldbs_insert_id(MYSQL *handle);
int sqldbs_affected_rows(MYSQL *handle);
void sqldbs_close(MYSQL *handle);
int sqldbs_connect(MYSQL *handle, const char *host, const char *user, const char *passwd,
	const char *db, unsigned short port, const char *charset);

#endif	// if TXT

#endif	// _SQLDB_H_
