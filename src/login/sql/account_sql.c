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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mmo.h"
#include "db.h"
#include "malloc.h"
#include "utils.h"
#include "sqldbs.h"

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
static struct dbt *account_db;

bool account_sql_init(void)
{
	MYSQL_RES* sql_res;
	bool is_connect;
	const char *delayed = "";

	// DB connection start
	is_connect = sqldbs_connect(&mysql_handle,config.login_server_ip, config.login_server_id, config.login_server_pw, config.login_server_db, config.login_server_port, config.login_server_charset, config.login_server_keepalive);

	// DB connection error
	if( is_connect == false )
		return false;

	// support DELAYED ?
	sqldbs_query(&mysql_handle,
		"SELECT 1 FROM information_schema.tables WHERE table_schema = (SELECT database()) AND table_name = '" LOGINLOG_TABLE "' "
		"AND engine IN ('MyISAM', 'MEMORY', 'ARCHIVE', 'BLACKHOLE')"
	);

	sql_res = sqldbs_store_result(&mysql_handle);
	if(sql_res) {
		if(sqldbs_num_rows(sql_res) > 0) {
			delayed = "DELAYED";
		}
		sqldbs_free_result(sql_res);
	}

	// log write
	sqldbs_query(&mysql_handle, "INSERT %s INTO `" LOGINLOG_TABLE "` (`time`,`log`) VALUES (NOW(), 'lserver 100 login server started')", delayed);

	// create account_db
	account_db = numdb_init();

	return true;
}

static int account_db_final(void *key, void *data, va_list ap)
{
	struct mmo_account *p = (struct mmo_account *)data;

	aFree(p);

	return 0;
}

void account_sql_final(void)
{
	MYSQL_RES* sql_res;
	const char *delayed = "";

	// support DELAYED ?
	sqldbs_query(&mysql_handle,
		"SELECT 1 FROM information_schema.tables WHERE table_schema = (SELECT database()) AND table_name = '" LOGINLOG_TABLE "' "
		"AND engine IN ('MyISAM', 'MEMORY', 'ARCHIVE', 'BLACKHOLE')"
	);

	sql_res = sqldbs_store_result(&mysql_handle);
	if(sql_res) {
		if(sqldbs_num_rows(sql_res) > 0) {
			delayed = "DELAYED";
		}
		sqldbs_free_result(sql_res);
	}

	// set log
	sqldbs_query(&mysql_handle, "INSERT %s INTO `" LOGINLOG_TABLE "` (`time`,`log`) VALUES (NOW(), 'lserver 100 login server shutdown')", delayed);

	// close Connection
	sqldbs_close(&mysql_handle);

	// free account_db
	numdb_final(account_db,account_db_final);
}

void account_sql_sync(void)
{
	// nothing to do
}

void account_sql_set_default_configvalue(void)
{
	config.login_server_port = 3306;
	strncpy(config.login_server_ip,"127.0.0.1",sizeof(config.login_server_ip));
	strncpy(config.login_server_id,"ragnarok",sizeof(config.login_server_id));
	strncpy(config.login_server_pw,"ragnarok",sizeof(config.login_server_pw));
	strncpy(config.login_server_db,"ragnarok",sizeof(config.login_server_db));
	strncpy(config.login_server_charset,"",sizeof(config.login_server_charset));
	config.login_server_keepalive = 0;

	return;
}

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

bool account_sql_account_delete(int account_id)
{
	bool result = false;
	struct mmo_account *ac = (struct mmo_account *)numdb_erase(account_db, account_id);

	if( ac )
		aFree(ac);

	// start transaction
	if( sqldbs_simplequery(&mysql_handle, "START TRANSACTION") == false )
		return result;

	// try
	do
	{
		// delete account
		if( sqldbs_query(&mysql_handle, "DELETE FROM `" LOGIN_TABLE "` WHERE `account_id` = '%d'", account_id) == false)
			break;

		// delete worldreg
		if( sqldbs_query(&mysql_handle, "DELETE FROM `" WORLDREG_TABLE "` WHERE `account_id`='%d'", account_id) == false)
			break;

		// success
		result = true;
	} while(0);

	// end transaction
	sqldbs_simplequery(&mysql_handle, ( result == true )? "COMMIT" : "ROLLBACK");

	return result;
}

const struct mmo_account* account_sql_account_load_num(int account_id)
{
	struct mmo_account *ac = NULL;
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;

	if( account_id > END_ACCOUNT_NUM )
	{
		printf("account_sql_account_load_num :  ID is over END_ACCOUNT_NUM %d\n", END_ACCOUNT_NUM);
		return NULL;
	}

	ac = (struct mmo_account *)numdb_search(account_db, account_id);
	if( ac && ac->account_id == account_id )	// 既にキャッシュが存在する
		return ac;

	// basic information
	sqldbs_query(&mysql_handle,"SELECT `userid`,`user_pass`,`lastlogin`,`logincount`,`sex`,`state`,`email`,`birthdate` FROM `" LOGIN_TABLE "` WHERE `account_id` = '%d'",account_id);

	sql_res = sqldbs_store_result(&mysql_handle);
	if( !sql_res )
	{
		printf("account_sql_account_load_num: DB result error ! \n");
		return NULL;
	}

	sql_row = sqldbs_fetch(sql_res);
	if( !sql_row )
	{
		// 未登録
		sqldbs_free_result(sql_res);
		return NULL;
	}

	if( ac == NULL )
	{
		ac = (struct mmo_account *)aMalloc(sizeof(struct mmo_account));
		numdb_insert(account_db,account_id,ac);
	}
	memset(ac,0,sizeof(struct mmo_account));

	ac->account_id = account_id;
	strncpy(ac->userid, sql_row[0], 24);
	strncpy(ac->pass, sql_row[1], 24);
	strncpy(ac->lastlogin ,sql_row[2], 24);
	ac->logincount = atoi(sql_row[3]);
	ac->sex        = sql_row[4][0];
	ac->state      = atoi(sql_row[5]);
	strncpy(ac->mail, sql_row[6], 40);
	strncpy(ac->birth, sql_row[7], 7);
	sqldbs_free_result(sql_res);

	// global reg
	ac->account_reg2_num = 0;
	sqldbs_query(&mysql_handle, "SELECT `reg`,`value` FROM `" WORLDREG_TABLE "` WHERE `account_id`='%d'", account_id);

	sql_res = sqldbs_store_result(&mysql_handle);
	if( sql_res )
	{
		while( (sql_row = sqldbs_fetch(sql_res)) )
		{
			strncpy(ac->account_reg2[ac->account_reg2_num].str,sql_row[0],32);
			ac->account_reg2[ac->account_reg2_num].value   = atoi(sql_row[1]);
			if(++ac->account_reg2_num >= ACCOUNT_REG2_NUM)
				break;
		}
	}
	sqldbs_free_result(sql_res);

	return ac;
}

const struct mmo_account* account_sql_account_load_str(const char *account_id)
{
	int id_num = -1;
	char buf[256];
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;

	if( !account_id[0] )
		return NULL;

	sqldbs_query(&mysql_handle, "SELECT `account_id` FROM `" LOGIN_TABLE "` WHERE `userid` = '%s'", strecpy(buf,account_id));

	sql_res = sqldbs_store_result(&mysql_handle);
	if( sql_res )
	{
		sql_row = sqldbs_fetch(sql_res);
		if(sql_row)
			id_num = atoi(sql_row[0]);
		sqldbs_free_result(sql_res);
	}

	if( id_num >= 0 )
		return account_sql_account_load_num(id_num);

	return NULL;
}

const struct mmo_account* account_sql_account_load_idx(int idx)
{
	int id_num = -1;
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;

	if( idx < 0 )
		return NULL;

	sqldbs_query(&mysql_handle, "SELECT `account_id` FROM `" LOGIN_TABLE "` ORDER BY `account_id` ASC LIMIT %d,1", idx);

	sql_res = sqldbs_store_result(&mysql_handle);
	if( sql_res )
	{
		sql_row = sqldbs_fetch(sql_res);
		if(sql_row)
			id_num  = atoi(sql_row[0]);
		sqldbs_free_result(sql_res);
	}

	if(id_num >= 0)
		return account_sql_account_load_num(id_num);

	return NULL;
}

bool account_sql_account_save(struct mmo_account *ac2)
{
	const struct mmo_account *ac1;
	MYSQL_STMT *stmt;
	MYSQL_BIND bind[9];
	bool result = false;
	bool is_regupdate = false;
	int i = 0;

	// アカウントの存在確認
	if( (ac1 = account_sql_account_load_num(ac2->account_id)) == NULL )
		return result;

	// start transaction
	if( sqldbs_simplequery(&mysql_handle,"START TRANSACTION") == false )
		return result;

	// init
	stmt = sqldbs_stmt_init(&mysql_handle);

	// try
	do
	{
		// basic information
		if( sqldbs_stmt_prepare(stmt,"UPDATE `" LOGIN_TABLE "` SET `userid`=?,`user_pass`=?,`lastlogin`=?,`last_ip`=?,`sex`=?,`logincount`=?,`state`=?,`email`=?,`birthdate`=? WHERE `account_id` = '%d'",ac2->account_id) == false )
			break;

		// bind
		sqldbs_stmt_bind_param(&bind[0],SQL_DATA_TYPE_VAR_STRING,(void *)ac2->userid,strlen(ac2->userid),0,0);
		sqldbs_stmt_bind_param(&bind[1],SQL_DATA_TYPE_VAR_STRING,(void *)ac2->pass,strlen(ac2->pass),0,0);
		sqldbs_stmt_bind_param(&bind[2],SQL_DATA_TYPE_STRING,(void *)ac2->lastlogin,strlen(ac2->lastlogin),0,0);
		sqldbs_stmt_bind_param(&bind[3],SQL_DATA_TYPE_VAR_STRING,(void *)ac2->lastip,strlen(ac2->lastip),0,0);
		sqldbs_stmt_bind_param(&bind[4],SQL_DATA_TYPE_STRING,(void *)&ac2->sex,1,0,0);
		sqldbs_stmt_bind_param(&bind[5],SQL_DATA_TYPE_INT,INT2PTR(&ac2->logincount),0,0,0);
		sqldbs_stmt_bind_param(&bind[6],SQL_DATA_TYPE_INT,INT2PTR(&ac2->state),0,0,0);
		sqldbs_stmt_bind_param(&bind[7],SQL_DATA_TYPE_VAR_STRING,(void *)ac2->mail,strlen(ac2->mail),0,0);
		sqldbs_stmt_bind_param(&bind[8],SQL_DATA_TYPE_STRING,(void *)ac2->birth,strlen(ac2->birth),0,0);

		// execute
		if( sqldbs_stmt_execute(stmt,bind) == false )
			break;

		// account reg
		if( ac1->account_reg2_num != ac2->account_reg2_num || memcmp(ac1->account_reg2,ac2->account_reg2,sizeof(ac1->account_reg2[0])*ac1->account_reg2_num) )
		{
			is_regupdate = true;
			if( sqldbs_query(&mysql_handle, "DELETE FROM `" WORLDREG_TABLE "` WHERE `account_id`='%d'", ac2->account_id) == false )
				break;
			if( sqldbs_stmt_prepare(stmt,"INSERT INTO `" WORLDREG_TABLE "` (`account_id`, `reg`, `value`) VALUES ('%d', ?, ?);",ac2->account_id) == false )
				break;
			for( i = 0; i < ac2->account_reg2_num; i++ )
			{
				MYSQL_BIND reg_bind[2];
				sqldbs_stmt_bind_param(&reg_bind[0],SQL_DATA_TYPE_VAR_STRING,(void *)ac2->account_reg2[i].str,strlen(ac2->account_reg2[i].str),0,0);
				sqldbs_stmt_bind_param(&reg_bind[1],SQL_DATA_TYPE_INT,INT2PTR(&ac2->account_reg2[i].value),0,0,0);
				if( sqldbs_stmt_execute(stmt,reg_bind) == false )
					break;
			}
		}

		// fail
		if( is_regupdate == true && i < ac2->account_reg2_num )
			break;

		// success
		result = true;

		// cache copy
		{
			struct mmo_account *ac3 = (struct mmo_account *)numdb_search(account_db, ac2->account_id);
			if( ac3 )
				memcpy(ac3, ac2, sizeof(struct mmo_account));
		}
	} while(0);

	// free
	sqldbs_stmt_close(stmt);

	// end transaction
	sqldbs_simplequery(&mysql_handle, ( result == true )? "COMMIT" : "ROLLBACK");

	return result;
}

bool account_sql_account_new(struct mmo_account *account, const char *tmpstr)
{
	MYSQL_STMT *stmt;
	MYSQL_BIND bind[5];

	loginlog_log("auth new %s %s %s",tmpstr,account->userid,account->pass);

	// force \0 terminal
	account->userid[23] = '\0';
	account->pass[23]   = '\0';
	account->mail[39]   = '\0';
	account->birth[6]   = '\0';

	if( account_sql_account_load_str(account->userid) )	// 同じアカウントが既に存在
		return false;

	// init
	stmt = sqldbs_stmt_init(&mysql_handle);

	// ステートメントの準備
	sqldbs_stmt_prepare(stmt,"INSERT INTO `" LOGIN_TABLE "` (`userid`,`user_pass`,`lastlogin`,`sex`,`logincount`,`level`,`state`,`email`,`birthdate`) VALUES(?,?,NOW(),?,'0','0','0',?,?)");

	// パラメータをbind
	sqldbs_stmt_bind_param(&bind[0],SQL_DATA_TYPE_VAR_STRING,(void *)account->userid,strlen(account->userid),0,0);
	sqldbs_stmt_bind_param(&bind[1],SQL_DATA_TYPE_VAR_STRING,(void *)account->pass,strlen(account->pass),0,0);
	sqldbs_stmt_bind_param(&bind[2],SQL_DATA_TYPE_STRING,(void *)&account->sex,1,0,0);
	sqldbs_stmt_bind_param(&bind[3],SQL_DATA_TYPE_VAR_STRING,(void *)account->mail,strlen(account->mail),0,0);
	sqldbs_stmt_bind_param(&bind[4],SQL_DATA_TYPE_STRING,(void *)account->birth,strlen(account->birth),0,0);

	// 実行
	sqldbs_stmt_execute(stmt,bind);

	// free
	sqldbs_stmt_close(stmt);

	return true;
}

void display_conf_warnings_sql(void)
{
	if( config.login_server_pw[0] == '\0' )
		printf("SQL SECURITY warning: login_server_pw is not defined (void).\n");
	else if( strcmp(config.login_server_pw, "ragnarok") == 0 )
		printf("SQL SECURITY warning: using default login_server_pw ('%s').\n", config.login_server_pw);

	return;
}
