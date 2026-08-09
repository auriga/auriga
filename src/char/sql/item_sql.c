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
#include <string.h>

#include "mmo.h"
#include "sqldbs.h"
#include "nullpo.h"

#include "item_sql.h"

/*==========================================
 * Map one SQL row to struct item
 *------------------------------------------
 */
void item_sql_loadrow(struct item *item, char **sql_row, int with_private)
{
	nullpo_retv(item);
	nullpo_retv(sql_row);

	item->id         = (unsigned int)atoi(sql_row[0]);
	item->nameid     = atoi(sql_row[1]);
	item->amount     = atoi(sql_row[2]);
	item->equip      = (unsigned int)atoi(sql_row[3]);
	item->identify   = atoi(sql_row[4]);
	item->refine     = atoi(sql_row[5]);
	item->attribute  = atoi(sql_row[6]);
	item->card[0]    = atoi(sql_row[7]);
	item->card[1]    = atoi(sql_row[8]);
	item->card[2]    = atoi(sql_row[9]);
	item->card[3]    = atoi(sql_row[10]);
	item->opt[0].id  = atoi(sql_row[11]);
	item->opt[0].val = atoi(sql_row[12]);
	item->opt[1].id  = atoi(sql_row[13]);
	item->opt[1].val = atoi(sql_row[14]);
	item->opt[2].id  = atoi(sql_row[15]);
	item->opt[2].val = atoi(sql_row[16]);
	item->opt[3].id  = atoi(sql_row[17]);
	item->opt[3].val = atoi(sql_row[18]);
	item->opt[4].id  = atoi(sql_row[19]);
	item->opt[4].val = atoi(sql_row[20]);
	item->limit      = (unsigned int)atoi(sql_row[21]);
	if(with_private)
		item->private_ = atoi(sql_row[22]);
	else
		item->private_ = 0;
}

/*==========================================
 * Common item load (inventory/cart/storage)
 *------------------------------------------
 */
int item_sql_loaditem(struct item *item, int max, int id, int tableswitch)
{
	int i = 0;
	const char *tablename;
	const char *selectoption;
	char **sql_row;
	bool result = false;

	nullpo_retr(-1, item);

	memset(item, 0, sizeof(struct item) * max);

	switch (tableswitch) {
	case TABLE_NUM_INVENTORY:
		tablename    = INVENTORY_TABLE;
		selectoption = "char_id";
		break;
	case TABLE_NUM_CART:
		tablename    = CART_TABLE;
		selectoption = "char_id";
		break;
	case TABLE_NUM_STORAGE:
		tablename    = STORAGE_TABLE;
		selectoption = "account_id";
		break;
	case TABLE_NUM_GUILD_STORAGE:
		tablename    = GUILD_STORAGE_TABLE;
		selectoption = "guild_id";
		break;
	default:
		printf("Invalid table name!\n");
		return -1;
	}

	result = sqldbs_query(&mysql_handle,
		"SELECT " ITEM_SQL_COLUMNS_PRIVATE " FROM `%s` WHERE `%s`='%d'",
		tablename, selectoption, id
	);
	if(result == false)
		return -1;

	for(i = 0; (sql_row = sqldbs_fetch(&mysql_handle)) && i < max; i++) {
		item_sql_loadrow(&item[i], sql_row, 1);
	}
	sqldbs_free_result(&mysql_handle);

	return i;
}

/*==========================================
 * Common item save (inventory/cart/storage)
 *------------------------------------------
 */
bool item_sql_saveitem(struct item *item, int max, int id, int tableswitch)
{
	const char *tablename;
	const char *selectoption;
	char *p, tmp_sql[65536 * 2];
	char sep = ' ';
	bool result = false;

	nullpo_retr(false, item);

	switch (tableswitch) {
	case TABLE_NUM_INVENTORY:
		tablename    = INVENTORY_TABLE;
		selectoption = "char_id";
		break;
	case TABLE_NUM_CART:
		tablename    = CART_TABLE;
		selectoption = "char_id";
		break;
	case TABLE_NUM_STORAGE:
		tablename    = STORAGE_TABLE;
		selectoption = "account_id";
		break;
	case TABLE_NUM_GUILD_STORAGE:
		tablename    = GUILD_STORAGE_TABLE;
		selectoption = "guild_id";
		break;
	default:
		printf("Invalid table name!\n");
		return false;
	}

	if( sqldbs_transaction_start(&mysql_handle) == false )
		return false;

	/* try */
	do
	{
		int i;

		/* delete */
		if( sqldbs_query(&mysql_handle, "DELETE FROM `%s` WHERE `%s`='%d'", tablename, selectoption, id) == false)
			break;

		p  = tmp_sql;
		p += sprintf(
			p,"INSERT INTO `%s`(`id`, `%s`, `nameid`, `amount`, `equip`, `identify`, `refine`, "
			"`attribute`, `card0`, `card1`, `card2`, `card3`, `opt0id`, `opt0val`, `opt1id`, `opt1val`, `opt2id`, `opt2val`, "
			"`opt3id`, `opt3val`, `opt4id`, `opt4val`, `limit`, `private`) VALUES",tablename,selectoption
		);

		for(i = 0; i < max; i++) {
			if(item[i].nameid) {
				p += sprintf(
					p,"%c('%u','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%u',%d)",
					sep,item[i].id,id,item[i].nameid,item[i].amount,item[i].equip,item[i].identify,
					item[i].refine,item[i].attribute,item[i].card[0],item[i].card[1],item[i].card[2],item[i].card[3],
					item[i].opt[0].id,item[i].opt[0].val,item[i].opt[1].id,item[i].opt[1].val,item[i].opt[2].id,item[i].opt[2].val,
					item[i].opt[3].id,item[i].opt[3].val,item[i].opt[4].id,item[i].opt[4].val,item[i].limit,item[i].private_
				);
				sep = ',';
			}
		}

		if(sep == ',') {
			if( sqldbs_simplequery(&mysql_handle, tmp_sql) == false )
				break;
		}

		/* success */
		result = true;
	} while(0);

	sqldbs_transaction_end(&mysql_handle, result);

	return result;
}

#endif /* TXT_ONLY */
