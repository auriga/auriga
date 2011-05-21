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

#include <stdlib.h>
#include <string.h>

#include "mmo.h"
#include "db.h"
#include "malloc.h"
#include "utils.h"
#include "sqldbs.h"

#include "../inter.h"
#include "accregdb_sql.h"

static struct dbt *accreg_db = NULL;

bool accregdb_sql_init(void)
{
	accreg_db = numdb_init();
	return true;
}

int accregdb_sql_sync(void)
{
	// nothing to do
	return 0;
}

int accregdb_sql_config_read_sub(const char *w1,const char *w2)
{
	return 0;
}

void accregdb_sql_save(struct accreg *reg)
{
	bool result = false;
	MYSQL_STMT *stmt;
	int j = 0;

	// start transaction
	if( sqldbs_simplequery(&mysql_handle, "START TRANSACTION") == false )
		return;

	// init
	stmt = sqldbs_stmt_init(&mysql_handle);

	// try
	do
	{
		// delete reg
		if( sqldbs_query(&mysql_handle, "DELETE FROM `" ACCOUNTREG_TABLE "` WHERE `account_id`='%d'", reg->account_id) == false )
			break;

		// prepare
		if( sqldbs_stmt_prepare(stmt,"INSERT INTO `" ACCOUNTREG_TABLE "` (`account_id`, `reg`, `value`) VALUES ('%d' , ? , ?)",reg->account_id) == false )
			break;

		// insert val
		for( j = 0; j < reg->reg_num; j++ )
		{
			if(reg->reg[j].str[0] && reg->reg[j].value != 0)
			{
				MYSQL_BIND bind[2];
				sqldbs_stmt_bind_param(&bind[0],SQL_DATA_TYPE_VAR_STRING,(void *)reg->reg[j].str,strlen(reg->reg[j].str),0,0);
				sqldbs_stmt_bind_param(&bind[1],SQL_DATA_TYPE_INT,INT2PTR(&reg->reg[j].value),0,0,0);
				if( sqldbs_stmt_execute(stmt,bind) == false )
					break;
			}
		}

		// success
		if( j == 0 )
		{
			result = true;
			break;
		}

		// fail
		if( j < reg->reg_num )
			break;

		// success
		result = true;
	} while(0);

	// free
	sqldbs_stmt_close(stmt);

	// end transaction
	sqldbs_simplequery(&mysql_handle, ( result == true )? "COMMIT" : "ROLLBACK");

	return;
}

const struct accreg* accregdb_sql_load(int account_id)
{
	int j=0;
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;
	struct accreg *reg = (struct accreg *)numdb_search(accreg_db,account_id);

	if( reg == NULL )
	{
		reg = (struct accreg *)aMalloc(sizeof(struct accreg));
		numdb_insert(accreg_db,account_id,reg);
	}
	memset(reg, 0, sizeof(struct accreg));
	reg->account_id = account_id;

	sqldbs_query(&mysql_handle, "SELECT `reg`, `value` FROM `" ACCOUNTREG_TABLE "` WHERE `account_id`='%d'", reg->account_id);

	sql_res = sqldbs_store_result(&mysql_handle);

	if( sql_res )
	{
		for( j = 0; (sql_row = sqldbs_fetch(sql_res)); j++ )
		{
			strncpy(reg->reg[j].str, sql_row[0],32);
			reg->reg[j].str[31] = '\0';	// force \0 terminal
			reg->reg[j].value   = atoi(sql_row[1]);
		}
		sqldbs_free_result(sql_res);
	}
	reg->reg_num = j;

	return reg;
}

static int accregdb_sql_final_sub(void *key,void *data,va_list ap)
{
	struct accreg *reg = (struct accreg *)data;

	aFree(reg);

	return 0;
}

void accregdb_sql_final(void)
{
	if(accreg_db)
		numdb_final(accreg_db,accregdb_sql_final_sub);
}
