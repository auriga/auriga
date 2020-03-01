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

#ifndef _INT_GUILD_H_
#define _INT_GUILD_H_

#include "mmo.h"

extern int guild_exp[MAX_GUILDLEVEL];
extern struct dbt *guild_db;
extern struct guild_castle castle_db[MAX_GUILDCASTLE];

char* guild_decode_emblem(char *dst, const char *src, int len);

int guild_readdb(void);
int guild_config_read(const char *w1,const char* w2);
void guild_calc_skilltree(struct guild *g);
int guild_calcinfo(struct guild *g);

int mapif_guild_broken(int guild_id,int flag);
int inter_guild_parse_frommap(int fd);
int inter_guild_mapif_init(int fd);
int inter_guild_leave(int guild_id,int account_id,int char_id);

#ifdef TXT_ONLY
	#include "txt/guilddb_txt.h"
#else
	#include "sql/guilddb_sql.h"
#endif

#endif /* _INT_GUILD_H_ */
