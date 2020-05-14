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

#ifndef _MEMORIAL_H_
#define _MEMORIAL_H_

#include "map.h"

#define MAX_MEMORIAL_DATA		50		// メモリアルダンジョン最大登録数
#define MAX_MEMORIAL_SEGMAP		8		// メモリアルダンジョン最大分割マップ数

enum {
	MDCREATE_NOERROR = 0,
	MDCREATE_EXISTS,
	MDCREATE_PERMISSION,
	MDCREATE_RESERVED,
	MDCREATE_ERROR
};

enum {
	MDENTER_NOERROR = 0,
	MDENTER_NOPARTY,
	MDENTER_NOCREATE,
	MDENTER_ERROR
};

enum {
	MDSTATE_FREE = 0,
	MDSTATE_IDLE,
	MDSTATE_BUSY
};

struct memorial_data {
	short type;
	int state;
	int party_id;
	unsigned int keep_limit;
	int keep_timer;
	unsigned int idle_limit;
	int idle_timer;
	int users;
	struct {
		int m;
		int src_m;
	} map[MAX_MEMORIAL_SEGMAP];
};

int memorial_search_party(int id);

int memorial_create(const char *memorial_name, int party_id);
int memorial_delete(int memorial_id);
int memorial_enter(struct map_session_data *sd, const char *memorial_name);
int memorial_reqinfo(struct map_session_data *sd, int memorial_id);
int memorial_openstate(struct map_session_data *sd, const char *memorial_name);
int memorial_addusers(int memorial_id);
int memorial_delusers(int memorial_id);
int memorial_mapname2mapid(const char *name, int memorial_id);

int do_init_memorial(void);
int do_final_memorial(void);

#endif
