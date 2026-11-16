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

#ifndef _SEARCHSTORE_H_
#define _SEARCHSTORE_H_

#include "map.h"

enum e_searchstore_failure {
	SSI_FAILED_NOTHING_SEARCH_ITEM = 0,
	SSI_FAILED_OVER_MAXCOUNT,
	SSI_FAILED_SEARCH_CNT,
	SSI_FAILED_LIMIT_SEARCH_TIME,
	SSI_FAILED_SSILIST_CLICK_TO_OPEN_STORE,
};

enum e_searchstore_searchtype {
	SEARCHTYPE_VENDING = 0,
	SEARCHTYPE_BUYING_STORE,
};

enum e_searchstore_effecttype {
	SEARCHSTORE_EFFECT_NORMAL = 0,
	SEARCHSTORE_EFFECT_REMOTE,
	SEARCHSTORE_EFFECT_MAX
};

int searchstore_open(struct map_session_data *sd, unsigned short uses, unsigned char effect, short mapid);
void searchstore_query(struct map_session_data *sd, unsigned char type, unsigned int min_price, unsigned int max_price,
	const int *itemlist, int item_count, const int *cardlist, int card_count);
int searchstore_querynext(struct map_session_data *sd);
void searchstore_next(struct map_session_data *sd);
void searchstore_clear(struct map_session_data *sd);
void searchstore_close(struct map_session_data *sd);
void searchstore_click(struct map_session_data *sd, int account_id, unsigned int store_id, int nameid);
int searchstore_queryremote(struct map_session_data *sd, struct map_session_data *pl_sd, unsigned char type);
void searchstore_clearremote(struct map_session_data *sd);

#endif /* _SEARCHSTORE_H_ */
