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

#ifndef _CASHSHOP_H_
#define _CASHSHOP_H_

struct map_session_data;

#define CASHSHOP_TAB_MAX 9
#define CASHSHOP_ITEM_MAX 256

enum cashshop_buy_result {
	CASHSHOP_RESULT_SUCCESS = 0,
	CASHSHOP_RESULT_ERROR_SYSTEM = 1,
	CASHSHOP_RESULT_ERROR_SHORTTAGE_CASH = 2,
	CASHSHOP_RESULT_ERROR_UNKNOWN_ITEM = 3,
	CASHSHOP_RESULT_ERROR_INVENTORY_WEIGHT = 4,
	CASHSHOP_RESULT_ERROR_INVENTORY_ITEMCNT = 5,
	CASHSHOP_RESULT_ERROR_PC_STATE = 6,
	CASHSHOP_RESULT_ERROR_UNKNOWN = 11
};

struct cashshop_item {
	short tab;
	int nameid;
	int price;
	unsigned int start_date;	/* YYYYMMDD、0は開始日指定なし */
	unsigned int end_date;		/* YYYYMMDD、0は終了日指定なし */
};

int cashshop_item_count(void);
const struct cashshop_item *cashshop_item_at(int index);
int cashshop_item_available(const struct cashshop_item *it);
int cashshop_find_price(int tab, int nameid);
int cashshop_buy(struct map_session_data *sd, unsigned int kafra_points, int count, const unsigned char *item_list);

void cashshop_clear(void);
int cashshop_insert(int tab, int nameid, int price, unsigned int start_date, unsigned int end_date);

int do_init_cashshop(void);
void do_final_cashshop(void);

#endif /* _CASHSHOP_H_ */
