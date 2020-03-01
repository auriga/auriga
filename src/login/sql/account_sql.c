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

#include "mmo.h"
#include "db.h"
#include "malloc.h"
#include "utils.h"
#include "sqldbs.h"
#include "nullpo.h"

#include "../login.h"
#include "account_sql.h"

struct sql_config {
	unsigned short login_server_port;
	char login_server_ip[32];
	char login_server_id[32];
	char login_server_pw[32];
	char login_server_db[32];
	char login_server_charset[32];
	int  login_server_keepalive;
};

static struct sql_config config;
static struct dbt *account_db = NULL;

/*==========================================
 * 設定ファイルのデフォルト設定
 *------------------------------------------
 */
void account_sql_set_default_configvalue(void)
{
	config.login_server_port = 3306;
	strncpy(config.login_server_ip, "127.0.0.1", sizeof(config.login_server_ip));
	strncpy(config.login_server_id, "ragnarok", sizeof(config.login_server_id));
	strncpy(config.login_server_pw, "ragnarok", sizeof(config.login_server_pw));
	strncpy(config.login_server_db, "ragnarok", sizeof(config.login_server_db));
	strncpy(config.login_server_charset, "", sizeof(config.login_server_charset));
	config.login_server_keepalive = 0;

	return;
}

/*==========================================
 * 設定ファイル読込
 *------------------------------------------
 */
int account_sql_config_read_sub(const char *w1, const char *w2)
{
	if( strcmpi(w1,"login_server_ip") == 0 )
		strncpy(config.login_server_ip, w2, sizeof(config.login_server_ip) - 1);
	else if( strcmpi(w1,"login_server_port") == 0 )
	{
		int n = atoi(w2);
		if( n < 1024 || n > 65535 )
		{
			printf("Warning: Invalid login_server_port value: %d. Set to 3306 (default).\n", n);
			config.login_server_port = 3306; // default
		}
		else
		{
			config.login_server_port = (unsigned short)n;
		}
	}
	else if( strcmpi(w1, "login_server_id") == 0 )
		strncpy(config.login_server_id, w2, sizeof(config.login_server_id) - 1);
	else if( strcmpi(w1, "login_server_pw") == 0 )
		strncpy(config.login_server_pw, w2, sizeof(config.login_server_pw) - 1);
	else if( strcmpi(w1, "login_server_db") == 0 )
		strncpy(config.login_server_db, w2, sizeof(config.login_server_db) - 1);
	else if( strcmpi(w1, "login_server_charset") == 0 )
		strncpy(config.login_server_charset, w2, sizeof(config.login_server_charset) - 1);
	else if( strcmpi(w1, "login_server_keepalive") == 0 )
		config.login_server_keepalive = atoi(w2);
	else
		return 0;

	return 1;
}

/*==========================================
 * 設定ファイルの警告
 *------------------------------------------
 */
void display_conf_warnings_sql(void)
{
	if( config.login_server_pw[0] == '\0' )
		printf("SQL SECURITY warning: login_server_pw is not defined (void).\n");
	else if( strcmp(config.login_server_pw, "ragnarok") == 0 )
		printf("SQL SECURITY warning: using default login_server_pw ('%s').\n", config.login_server_pw);

	return;
}

/*==========================================
 * 同期
 *------------------------------------------
 */
void account_sql_sync(void)
{
	// nothing to do
}

/*==========================================
 * アカウント削除
 *------------------------------------------
 */
bool account_sql_account_delete(int account_id)
{
	bool result = false;

	if( sqldbs_transaction_start(&mysql_handle) == false )
		return false;

	// try
	do
	{
		// delete account
		if( sqldbs_query(&mysql_handle, "DELETE FROM `" LOGIN_TABLE "` WHERE `account_id` = '%d'", account_id) == false )
			break;

		// delete worldreg
		if( sqldbs_query(&mysql_handle, "DELETE FROM `" WORLDREG_TABLE "` WHERE `account_id`='%d'", account_id) == false )
			break;

		// success
		result = true;

		{
			// cache delete
			struct mmo_account *ac = (struct mmo_account *)numdb_erase(account_db, account_id);
			if(ac) {
				aFree(ac);
			}
		}
	} while(0);

	sqldbs_transaction_end(&mysql_handle, result);

	return result;
}

/*==========================================
 * アカウントIDからアカウント情報をロード
 *------------------------------------------
 */
const struct mmo_account* account_sql_account_load_num(int account_id)
{
	struct mmo_account *ac = NULL;
	char **sql_row;

	if( account_id > END_ACCOUNT_NUM )
	{
		printf("account_sql_account_load_num :  ID is over END_ACCOUNT_NUM %d\n", END_ACCOUNT_NUM);
		return NULL;
	}

	ac = (struct mmo_account *)numdb_search(account_db, account_id);
	if( ac && ac->account_id == account_id )	// 既にキャッシュが存在する
		return ac;

	// basic information
	if( sqldbs_query(&mysql_handle, "SELECT `userid`,`user_pass`,`lastlogin`,`logincount`,`sex`,`state`,`email`,`birthdate` FROM `" LOGIN_TABLE "` WHERE `account_id` = '%d'", account_id) == false )
		return NULL;

	sql_row = sqldbs_fetch(&mysql_handle);
	if( !sql_row )
	{
		// 未登録
		sqldbs_free_result(&mysql_handle);
		return NULL;
	}

	if( ac == NULL )
	{
		ac = (struct mmo_account *)aMalloc(sizeof(struct mmo_account));
		numdb_insert(account_db, account_id, ac);
	}
	memset(ac, 0, sizeof(struct mmo_account));

	ac->account_id = account_id;
	strncpy(ac->userid, sql_row[0], 24);
	strncpy(ac->pass, sql_row[1], 24);
	strncpy(ac->lastlogin ,sql_row[2], 24);
	ac->logincount = atoi(sql_row[3]);
	ac->sex        = sql_row[4][0];
	ac->state      = atoi(sql_row[5]);
	strncpy(ac->mail, sql_row[6], 40);
	strncpy(ac->birth, sql_row[7], 7);

	sqldbs_free_result(&mysql_handle);

	// global reg
	ac->account_reg2_num = 0;
	if(sqldbs_query(&mysql_handle, "SELECT `reg`,`value` FROM `" WORLDREG_TABLE "` WHERE `account_id`='%d'", account_id))
	{
		while((sql_row = sqldbs_fetch(&mysql_handle))) {
			strncpy(ac->account_reg2[ac->account_reg2_num].str, sql_row[0], 32);
			ac->account_reg2[ac->account_reg2_num].value = atoi(sql_row[1]);
			if(++ac->account_reg2_num >= ACCOUNT_REG2_NUM)
				break;
		}
	}
	sqldbs_free_result(&mysql_handle);

	return ac;
}

/*==========================================
 * アカウント名からアカウント情報をロード
 *------------------------------------------
 */
const struct mmo_account* account_sql_account_load_str(const char *account_id)
{
	char buf[256];

	if(!account_id[0])
		return NULL;

	if(sqldbs_query(&mysql_handle, "SELECT `account_id` FROM `" LOGIN_TABLE "` WHERE `userid` = '%s'", strecpy(buf, account_id)))
	{
		int id_num = -1;
		char **sql_row = sqldbs_fetch(&mysql_handle);

		if(sql_row) {
			id_num = atoi(sql_row[0]);
		}
		sqldbs_free_result(&mysql_handle);

		if(id_num >= 0)
			return account_sql_account_load_num(id_num);
	}
	return NULL;
}

/*==========================================
 * Indexからアカウント情報をロード
 *------------------------------------------
 */
const struct mmo_account* account_sql_account_load_idx(int idx)
{
	if(idx < 0)
		return NULL;

	if(sqldbs_query(&mysql_handle, "SELECT `account_id` FROM `" LOGIN_TABLE "` ORDER BY `account_id` ASC LIMIT %d,1", idx))
	{
		int id_num = -1;
		char **sql_row = sqldbs_fetch(&mysql_handle);

		if(sql_row) {
			id_num  = atoi(sql_row[0]);
		}
		sqldbs_free_result(&mysql_handle);

		if(id_num >= 0)
			return account_sql_account_load_num(id_num);
	}
	return NULL;
}

/*==========================================
 * セーブ
 *------------------------------------------
 */
bool account_sql_account_save(struct mmo_account *ac2)
{
	const struct mmo_account *ac1;
	struct sqldbs_stmt *st;
	bool result = false;

	nullpo_retr(false, ac2);

	// アカウントの存在確認
	if( (ac1 = account_sql_account_load_num(ac2->account_id)) == NULL )
		return false;

	// init
	st = sqldbs_stmt_init(&mysql_handle);
	if(st == NULL)
		return false;

	if( sqldbs_transaction_start(&mysql_handle) == false )
		return false;

	// try
	do
	{
		// basic information
		if( sqldbs_stmt_prepare(st, "UPDATE `" LOGIN_TABLE "` SET `userid`=?,`user_pass`=?,`lastlogin`=?,`last_ip`=?,`sex`=?,`logincount`=?,`state`=?,`email`=?,`birthdate`=? WHERE `account_id` = '%d'", ac2->account_id) == false )
			break;

		// bind
		sqldbs_stmt_bind_param(st, 0, SQL_DATA_TYPE_VAR_STRING, ac2->userid,      strlen(ac2->userid)   );
		sqldbs_stmt_bind_param(st, 1, SQL_DATA_TYPE_VAR_STRING, ac2->pass,        strlen(ac2->pass)     );
		sqldbs_stmt_bind_param(st, 2, SQL_DATA_TYPE_STRING,     ac2->lastlogin,   strlen(ac2->lastlogin));
		sqldbs_stmt_bind_param(st, 3, SQL_DATA_TYPE_VAR_STRING, ac2->lastip,      strlen(ac2->lastip)   );
		sqldbs_stmt_bind_param(st, 4, SQL_DATA_TYPE_STRING,     &ac2->sex,        1                     );
		sqldbs_stmt_bind_param(st, 5, SQL_DATA_TYPE_INT,        &ac2->logincount, 0                     );
		sqldbs_stmt_bind_param(st, 6, SQL_DATA_TYPE_INT,        &ac2->state,      0                     );
		sqldbs_stmt_bind_param(st, 7, SQL_DATA_TYPE_VAR_STRING, ac2->mail,        strlen(ac2->mail)     );
		sqldbs_stmt_bind_param(st, 8, SQL_DATA_TYPE_STRING,     ac2->birth,       strlen(ac2->birth)    );

		// execute
		if( sqldbs_stmt_execute(st) == false )
			break;

		// account reg
		if( ac1->account_reg2_num != ac2->account_reg2_num || memcmp(ac1->account_reg2, ac2->account_reg2, sizeof(ac1->account_reg2[0]) * ac1->account_reg2_num) )
		{
			int i = 0;

			if( sqldbs_query(&mysql_handle, "DELETE FROM `" WORLDREG_TABLE "` WHERE `account_id`='%d'", ac2->account_id) == false )
				break;
			if( sqldbs_stmt_prepare(st, "INSERT INTO `" WORLDREG_TABLE "` (`account_id`, `reg`, `value`) VALUES ('%d', ?, ?);",ac2->account_id) == false )
				break;

			for(i = 0; i < ac2->account_reg2_num; i++)
			{
				sqldbs_stmt_bind_param(st, 0, SQL_DATA_TYPE_VAR_STRING, ac2->account_reg2[i].str, strlen(ac2->account_reg2[i].str));
				sqldbs_stmt_bind_param(st, 1, SQL_DATA_TYPE_INT, &ac2->account_reg2[i].value, 0);
				if( sqldbs_stmt_execute(st) == false )
					break;
			}
			if(i != ac2->account_reg2_num)
				break;
		}

		// success
		result = true;

		// cache copy
		{
			struct mmo_account *ac3 = (struct mmo_account *)numdb_search(account_db, ac2->account_id);
			if(ac3)
				memcpy(ac3, ac2, sizeof(struct mmo_account));
		}
	} while(0);

	sqldbs_stmt_close(st);
	sqldbs_transaction_end(&mysql_handle, result);

	return result;
}

/*==========================================
 * アカウント作成
 *------------------------------------------
 */
bool account_sql_account_new(struct mmo_account *account, const char *tmpstr)
{
	struct sqldbs_stmt *st;
	bool result = false;

	nullpo_retr(false, account);

	loginlog_log("auth new %s %s %s", tmpstr, account->userid, account->pass);

	// force \0 terminal
	account->userid[23] = '\0';
	account->pass[23]   = '\0';
	account->mail[39]   = '\0';
	account->birth[6]   = '\0';

	if( account_sql_account_load_str(account->userid) )	// 同じアカウントが既に存在
		return false;

	// init
	st = sqldbs_stmt_init(&mysql_handle);
	if(st == NULL)
		return false;

	if( sqldbs_transaction_start(&mysql_handle) == false )
		return false;

	do {
		// ステートメントの準備
		if( sqldbs_stmt_simpleprepare(st, "INSERT INTO `" LOGIN_TABLE "` (`userid`,`user_pass`,`lastlogin`,`sex`,`logincount`,`level`,`state`,`email`,`birthdate`) VALUES(?,?,NOW(),?,'0','0','0',?,?)") == false )
			return false;

		// パラメータをbind
		sqldbs_stmt_bind_param(st, 0, SQL_DATA_TYPE_VAR_STRING, account->userid, strlen(account->userid));
		sqldbs_stmt_bind_param(st, 1, SQL_DATA_TYPE_VAR_STRING, account->pass,   strlen(account->pass)  );
		sqldbs_stmt_bind_param(st, 2, SQL_DATA_TYPE_STRING,     &account->sex,   1                      );
		sqldbs_stmt_bind_param(st, 3, SQL_DATA_TYPE_VAR_STRING, account->mail,   strlen(account->mail)  );
		sqldbs_stmt_bind_param(st, 4, SQL_DATA_TYPE_STRING,     account->birth,  strlen(account->birth) );

		// 実行
		if( sqldbs_stmt_execute(st) == false )
			break;

		// success
		result = true;
	} while(0);

	sqldbs_stmt_close(st);
	sqldbs_transaction_end(&mysql_handle, result);

	return result;
}

/*==========================================
 * ログ保存
 *------------------------------------------
 */
static bool account_sql_log(bool is_start)
{
	bool result = false;

	// support DELAYED ?
	result = sqldbs_query(&mysql_handle,
		"SELECT 1 FROM information_schema.tables WHERE table_schema = (SELECT database()) AND table_name = '" LOGINLOG_TABLE "' "
		"AND engine IN ('MyISAM', 'MEMORY', 'ARCHIVE', 'BLACKHOLE')"
	);

	if(result) {
		bool is_delayed = false;

		if(sqldbs_num_rows(&mysql_handle) > 0) {
			is_delayed = true;
		}
		sqldbs_free_result(&mysql_handle);

		// log write
		result = sqldbs_query(&mysql_handle,
			"INSERT %s INTO `" LOGINLOG_TABLE "` (`time`,`log`) VALUES (NOW(), 'lserver 100 login server %s')",
			((is_delayed)? "DELAYED": ""), ((is_start)? "start": "shutdown")
		);
	}

	return result;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
static int account_db_final(void *key, void *data, va_list ap)
{
	struct mmo_account *p = (struct mmo_account *)data;

	aFree(p);

	return 0;
}

void account_sql_final(void)
{
	// set log
	account_sql_log(false);

	// free account_db
	numdb_final(account_db, account_db_final);

	// close Connection
	sqldbs_close(&mysql_handle);
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
bool account_sql_init(void)
{
	bool is_connect;

	// DB connection start
	is_connect = sqldbs_connect(&mysql_handle, config.login_server_ip, config.login_server_id, config.login_server_pw, config.login_server_db, config.login_server_port, config.login_server_charset, config.login_server_keepalive, "LOGIN");

	// DB connection error
	if( is_connect == false )
		return false;

	// create account_db
	account_db = numdb_init();

	return account_sql_log(true);
}
