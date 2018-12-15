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

#ifndef _CHAR_H_
#define _CHAR_H_

#include "mmo.h"
#include "utils.h"

#define MAX_MAP_SERVERS 8
#define DEFAULT_AUTOSAVE_INTERVAL_CS 300*1000
#define MAX_CHAR_SLOT 12

struct mmo_map_server {
	unsigned long ip;
	unsigned short port;
	char tag[MAPSERVER_TAGNAME];
	int users;
	char *map;
	short map_num;
	short active;
};

struct mmo_chardata {
	struct mmo_charstatus st;
	struct registry reg;
};

struct char_session_data {
	int state;
	int account_id,login_id1,login_id2,sex;
	const struct mmo_chardata *found_char[MAX_CHAR_SLOT];
};

int compare_ranking_data(const void *a,const void *b);
int mapif_sendall(unsigned char *buf, size_t len);
int mapif_sendallwos(int fd, unsigned char *buf, size_t len);
int mapif_send(int fd, unsigned char *buf, size_t len);
void mapif_parse_CharConnectLimit(int fd);
int char_log(const char *fmt, ...);
int parse_char(int fd);

extern struct Ranking_Data ranking_data[MAX_RANKING][MAX_RANKER];
extern const char ranking_reg[MAX_RANKING][32];
extern int human_start_zeny;
extern int human_start_weapon;
extern int human_start_armor;
extern int doram_start_zeny;
extern int doram_start_weapon;
extern int doram_start_armor;
extern int check_status_polygon;
extern int max_char_slot;
extern struct point human_start_point;
extern struct point doram_start_point;
extern char unknown_char_name[24];
extern char GM_account_filename[1024];
extern char char_conf_filename[256];
extern char inter_conf_filename[256];

#ifdef TXT_ONLY
	#include "txt/chardb_txt.h"
	#include "txt/charlog_txt.h"
#else
	#include "sql/chardb_sql.h"
	#include "sql/charlog_sql.h"
#endif

#endif /* _CHAR_H_ */
