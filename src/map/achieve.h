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

#ifndef	_ACHIEVE_H_
#define	_ACHIEVE_H_

#include "map.h"

#define MAX_ACHIEVE_DB      100
#define MAX_ACHIEVE_NAME     24

enum achieve_types {
	ACH_NONE		= 0,

	ACH_KILL_MOB	= 1,
	ACH_USE_ITEM	= 2,
	ACH_QUEST		= 3,
	ACH_LEVEL		= 4,
	ACH_STATUS		= 5,
	ACH_ACHIEVE		= 6,
	ACH_ACHIEVE_RANK= 7,
	ACH_ADVENTURE	= 8,
	ACH_TAMING		= 9,
	ACH_PET_FRIEND	= 10,
	ACH_ADD_FRIEND	= 11,
	ACH_SPEND_ZENY	= 12,
	ACH_GET_ZENY	= 13,
	ACH_JOBCHANGE	= 14,

	ACH_MAX			= 15,
};

struct achieve_db {
	int nameid;
	char name[MAX_ACHIEVE_NAME];
	enum achieve_types type;
	int score;
	struct {
		int id;
		int count;
	} content[MAX_ACHIEVE_CONTENT];
	char num;
	int title;
	struct script_code *reward;
};

int achieve_search_mobid(int mob_id);
int achieve_search_itemid(int item_id);
int achieve_calc_level(struct map_session_data *sd, int score);
int achieve_update_content(struct map_session_data *sd, enum achieve_types type, int id, int num);
int achieve_check_reward(struct map_session_data *sd, int achieve_id);
int achieve_check_title(struct map_session_data *sd, int title_id);

bool achieve_insert_info(int achieveid, const char* name, enum achieve_types type, int score, int title, const char *reward);
bool achieve_insert_content(int achieveid, int nameid, int count);
bool achieve_insert_db_end(void);
bool achieve_insert_leveldb(int lv, int exp);

int do_init_achieve(void);
int do_final_achieve(void);

#endif	// _ACHIEVE_H_
