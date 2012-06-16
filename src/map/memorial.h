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

#ifndef _MEMORIAL_H_
#define _MEMORIAL_H_

#include "map.h"

#define MAX_MEMORIAL_DB			10		// メモリアルダンジョンDB最大数
#define MAX_MEMORIAL_MAP		500		// 最大生成数
#define MAX_MEMORIAL_SEGMAP		10		// 最大分割マップ数

enum {
	MDERR_NOERROR = 0,
	MDERR_EXISTS,
	MDERR_PERMISSION,
	MDERR_RESERVED,
	MDERR_ERROR,
};

struct memorial_db {
	short memorial_id;
	char name[61];
	int limit;
	struct {
		char mapname[24];
		short x, y;
	} enter;
	char mapname[MAX_MEMORIAL_SEGMAP][24];
};
struct memorial_db memorial_db[MAX_MEMORIAL_DB];

int memorial_create(const char *memorial_name, int party_id);
int memorial_enter(struct map_session_data *sd, const char *memorial_name);

int do_init_memorial(void);
int do_final_memorial(void);

#endif
