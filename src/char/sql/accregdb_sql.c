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

#include <stdlib.h>
#include <string.h>

#include "mmo.h"
#include "db.h"
#include "malloc.h"
#include "utils.h"
#include "sqldbs.h"
#include "nullpo.h"

#include "../inter.h"
#include "accregdb_sql.h"

static struct dbt *accreg_db = NULL;

/*==========================================
 * 設定ファイル読込
 *------------------------------------------
 */
int accregdb_sql_config_read_sub(const char *w1,const char *w2)
{
	return 0;
}

/*==========================================
 * 同期
 *------------------------------------------
 */
int accregdb_sql_sync(void)
{
	// nothing to do
	return 0;
}

/*==========================================
 * セーブ
 *------------------------------------------
 */
bool accregdb_sql_save(struct accreg *reg)
{
	bool result = false;
	struct sqldbs_stmt *st;

	nullpo_retr(false, reg);

	// init
	st = sqldbs_stmt_init(&mysql_handle);
	if(st == NULL)
		return false;

	if( sqldbs_transaction_start(&mysql_handle) == false )
		return false;

	// try
	do
	{
		int j;

		// delete reg
		if( sqldbs_query(&mysql_handle, "DELETE FROM `" ACCOUNTREG_TABLE "` WHERE `account_id`='%d'", reg->account_id) == false )
			break;

		// prepare
		if( sqldbs_stmt_prepare(st, "INSERT INTO `" ACCOUNTREG_TABLE "` (`account_id`, `reg`, `value`) VALUES ('%d' , ? , ?)", reg->account_id) == false )
			break;

		// insert val
		for(j = 0; j < reg->reg_num; j++) {
			if(reg->reg[j].str[0] && reg->reg[j].value != 0)
			{
				sqldbs_stmt_bind_param(st, 0, SQL_DATA_TYPE_VAR_STRING, reg->reg[j].str, strlen(reg->reg[j].str));
				sqldbs_stmt_bind_param(st, 1, SQL_DATA_TYPE_INT, &reg->reg[j].value, 0);

				if( sqldbs_stmt_execute(st) == false )
					break;
			}
		}
		if(j != reg->reg_num)
			break;

		// success
		result = true;
	} while(0);

	sqldbs_transaction_end(&mysql_handle, result);
	sqldbs_stmt_close(st);

	return result;
}

/*==========================================
 * アカウント変数のロード
 *------------------------------------------
 */
const struct accreg* accregdb_sql_load(int account_id)
{
	int j = 0;
	char **sql_row;
	struct accreg *reg = (struct accreg *)numdb_search(accreg_db, account_id);

	if(reg == NULL) {
		reg = (struct accreg *)aMalloc(sizeof(struct accreg));
		numdb_insert(accreg_db, account_id,reg);
	}
	memset(reg, 0, sizeof(struct accreg));
	reg->account_id = account_id;

	if( sqldbs_query(&mysql_handle, "SELECT `reg`, `value` FROM `" ACCOUNTREG_TABLE "` WHERE `account_id`='%d'", reg->account_id) == false )
		return NULL;

	for(j = 0; (sql_row = sqldbs_fetch(&mysql_handle)); j++)
	{
		strncpy(reg->reg[j].str, sql_row[0], 32);
		reg->reg[j].str[31] = '\0';	// force \0 terminal
		reg->reg[j].value   = atoi(sql_row[1]);
	}
	sqldbs_free_result(&mysql_handle);

	reg->reg_num = j;

	return reg;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
static int accregdb_sql_final_sub(void *key, void *data, va_list ap)
{
	struct accreg *reg = (struct accreg *)data;

	aFree(reg);

	return 0;
}

void accregdb_sql_final(void)
{
	if(accreg_db)
		numdb_final(accreg_db, accregdb_sql_final_sub);
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
bool accregdb_sql_init(void)
{
	accreg_db = numdb_init();
	return true;
}
