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
#include <stdlib.h>
#include <string.h>

#include "db.h"
#include "malloc.h"
#include "utils.h"
#include "sqldbs.h"

#include "mapreg_sql.h"
#include "../script.h"

static struct dbt *mapreg_db;
static struct dbt *mapregstr_db;

static unsigned short map_server_port = 3306;
static char map_server_ip[32]      = "127.0.0.1";
static char map_server_id[32]      = "ragnarok";
static char map_server_pw[32]      = "ragnarok";
static char map_server_db[32]      = "ragnarok";
static char map_server_charset[32] = "";
static int  map_server_keepalive   = 0;

/*==========================================
 * 設定ファイル読込
 *------------------------------------------
 */
int mapreg_sql_config_read_sub(const char *w1, const char *w2)
{
	if(strcmpi(w1,"map_server_ip") == 0) {
		strncpy(map_server_ip, w2, sizeof(map_server_ip) - 1);
	}
	else if(strcmpi(w1,"map_server_port") == 0) {
		map_server_port = (unsigned short)atoi(w2);
	}
	else if(strcmpi(w1,"map_server_id") == 0) {
		strncpy(map_server_id, w2, sizeof(map_server_id) - 1);
	}
	else if(strcmpi(w1,"map_server_pw") == 0) {
		strncpy(map_server_pw, w2, sizeof(map_server_pw) - 1);
	}
	else if(strcmpi(w1,"map_server_db") == 0) {
		strncpy(map_server_db, w2, sizeof(map_server_db) - 1);
	}
	else if(strcmpi(w1,"map_server_charset") == 0) {
		strncpy(map_server_charset, w2, sizeof(map_server_charset) - 1);
	}
	else if(strcmpi(w1,"map_server_keepalive") == 0) {
		map_server_keepalive = atoi(w2);
	}
	else {
		return 0;
	}

	return 1;
}

/*==========================================
 * マップ変数の取得
 *------------------------------------------
 */
int mapreg_sql_getreg(int num)
{
	return PTR2INT(numdb_search(mapreg_db, num));
}

/*==========================================
 * マップ変数の変更
 *------------------------------------------
 */
bool mapreg_sql_setreg(int num, int val, int eternal)
{
	bool result = true;

	if(val != 0)
		numdb_insert(mapreg_db, num, INT2PTR(val));
	else
		numdb_erase(mapreg_db, num);

	if(eternal) {
		const char *name = script_get_str(num);
		int idx = num >> 24;
		char buf1[64], buf2[1024];

		if(val != 0) {
			result = sqldbs_query(&mysql_handle,
				"INSERT INTO `" MAPREG_TABLE "` (`server_tag`, `reg`, `index`, `value`) VALUES ('%s', '%s', '%d', '%d')"
				"ON DUPLICATE KEY UPDATE `value` = '%d'",
				strecpy(buf1, map_server_tag), strecpy(buf2, name), idx, val, val
			);
		} else {
			result = sqldbs_query(&mysql_handle,
				"DELETE FROM `" MAPREG_TABLE "` WHERE `server_tag` = '%s' AND `reg` = '%s' AND `index` = '%d'",
				strecpy(buf1, map_server_tag), strecpy(buf2, name), idx
			);
		}
	}

	return result;
}

/*==========================================
 * 文字列型マップ変数の取得
 *------------------------------------------
 */
char* mapreg_sql_getregstr(int num)
{
	return (char *)numdb_search(mapregstr_db, num);
}

/*==========================================
 * 文字列型マップ変数の変更
 *------------------------------------------
 */
bool mapreg_sql_setregstr(int num, const char *str, int eternal)
{
	char *old_str = NULL;
	bool result = true;

	if(str && *str)
		old_str = (char *)numdb_insert(mapregstr_db, num, aStrdup(str));
	else
		old_str = (char *)numdb_erase(mapregstr_db, num);

	if(old_str)
		aFree(old_str);

	if(eternal) {
		const char *name = script_get_str(num);
		int idx = num >> 24;
		char buf1[64], buf2[1024];

		if(str && *str) {
			char buf3[4096];

			strecpy(buf3, str);
			result = sqldbs_query(&mysql_handle,
				"INSERT INTO `" MAPREG_TABLE "` (`server_tag`, `reg`, `index`, `value`) VALUES ('%s', '%s', '%d', '%s')"
				"ON DUPLICATE KEY UPDATE `value` = '%s'",
				strecpy(buf1, map_server_tag), strecpy(buf2, name), idx, buf3, buf3
			);
		} else {
			result = sqldbs_query(&mysql_handle,
				"DELETE FROM `" MAPREG_TABLE "` WHERE `server_tag` = '%s' AND `reg` = '%s' AND `index` = '%d'",
				strecpy(buf1, map_server_tag), strecpy(buf2, name), idx
			);
		}
	}

	return result;
}

/*==========================================
 * 永続的マップ変数の読み込み
 *------------------------------------------
 */
static int mapreg_sql_load(void)
{
	char buf[64];
	bool result = false;

	result = sqldbs_query(&mysql_handle, "SELECT `reg`,`index`,`value` FROM `" MAPREG_TABLE "` WHERE `server_tag` = '%s'", strecpy(buf, map_server_tag));
	if(result) {
		int i, s;
		char name[256];
		char **sql_row;

		while((sql_row = sqldbs_fetch(&mysql_handle)) != NULL) {
			i = atoi(sql_row[1]);
			if(i < 0 || i >= 128)
				continue;
			strncpy(name, sql_row[0], 256);
			name[255] = '\0';	// force \0 terminal
			s = script_add_str(name);

			if(name[strlen(name) - 1] == '$') {
				mapreg_setregstr((i << 24) | s, sql_row[2], 0);
			} else {
				mapreg_setreg((i << 24) | s, atoi(sql_row[2]), 0);
			}
		}
		sqldbs_free_result(&mysql_handle);
	}
	return 0;
}

/*==========================================
 * 永続的マップ変数の自動セーブ
 *------------------------------------------
 */
int mapreg_sql_autosave(void)
{
	// nothing to do

	return 0;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
static int mapreg_sql_strdb_final(void *key, void *data, va_list ap)
{
	aFree(data);

	return 0;
}

int mapreg_sql_final(void)
{
	if(mapreg_db)
		numdb_final(mapreg_db, NULL);
	if(mapregstr_db)
		numdb_final(mapregstr_db, mapreg_sql_strdb_final);

	sqldbs_close(&mysql_handle);

	return 0;
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
bool mapreg_sql_init(void)
{
	// DB connection initialized
	int is_connect;

	is_connect = sqldbs_connect(&mysql_handle, map_server_ip, map_server_id, map_server_pw, map_server_db, map_server_port, map_server_charset, map_server_keepalive, "MAP");
	if( is_connect == false )
		return false;

	mapreg_db    = numdb_init();
	mapregstr_db = numdb_init();
	mapreg_sql_load();

	return true;
}
