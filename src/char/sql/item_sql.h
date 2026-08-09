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

#ifndef _ITEM_SQL_H_
#define _ITEM_SQL_H_

#ifndef TXT_ONLY

#include "mmo.h"

/* table selector for inventory / cart / storage / guild_storage */
enum {
	TABLE_NUM_INVENTORY,
	TABLE_NUM_CART,
	TABLE_NUM_STORAGE,
	TABLE_NUM_GUILD_STORAGE,
};

/* SELECT column list: id .. limit [, private] */
#define ITEM_SQL_COLUMNS \
	"`id`, `nameid`, `amount`, `equip`, `identify`, `refine`, `attribute`, " \
	"`card0`, `card1`, `card2`, `card3`, `opt0id`, `opt0val`, `opt1id`, `opt1val`, `opt2id`, `opt2val`, " \
	"`opt3id`, `opt3val`, `opt4id`, `opt4val`, `limit`"
#define ITEM_SQL_COLUMNS_PRIVATE ITEM_SQL_COLUMNS ", `private`"

int item_sql_loaditem(struct item *item, int max, int id, int tableswitch);
bool item_sql_saveitem(struct item *item, int max, int id, int tableswitch);

/* Map sql_row[0..] -> item. with_private: also read private_ from next column. */
void item_sql_loadrow(struct item *item, char **sql_row, int with_private);

#endif /* TXT_ONLY */

#endif /* _ITEM_SQL_H_ */
