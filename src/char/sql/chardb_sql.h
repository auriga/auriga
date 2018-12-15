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

#ifndef _CHARDB_SQL_H_
#define _CHARDB_SQL_H_

#include "mmo.h"
#include "utils.h"
#include "../char.h"

// 更新定義
enum {
	TABLE_NUM_INVENTORY,
	TABLE_NUM_CART,
	TABLE_NUM_STORAGE,
	TABLE_NUM_GUILD_STORAGE,
};

// プロトタイプ宣言
int chardb_sql_loaditem(struct item *item, int max, int id, int tableswitch);
bool chardb_sql_saveitem(struct item *item, int max, int id, int tableswitch);
const struct mmo_chardata* chardb_sql_make(int account_id, const unsigned char *name, short str, short agi, short vit, short int_, short dex, short luk, short hair_color, short hair, short job, char sex, unsigned char slot, int *flag);
bool chardb_sql_init(void);
void chardb_sql_sync(void);
const struct mmo_chardata* chardb_sql_load(int char_id);
bool chardb_sql_save_reg(int account_id,int char_id,int num,struct global_reg *reg);
bool chardb_sql_save(struct mmo_charstatus *st2);
void chardb_sql_final(void);
int chardb_sql_load_all(struct char_session_data* sd,int account_id);
bool chardb_sql_delete_sub(int char_id);
bool chardb_sql_build_ranking(void);
const struct mmo_chardata* chardb_sql_nick2chardata(const char *char_name);
int chardb_sql_config_read_sub(const char* w1,const char* w2);
bool chardb_sql_set_online(int char_id, bool is_online);

// エイリアス
#define chardb_make            chardb_sql_make
#define chardb_init            chardb_sql_init
#define chardb_sync            chardb_sql_sync
#define chardb_load            chardb_sql_load
#define chardb_save_reg        chardb_sql_save_reg
#define chardb_save            chardb_sql_save
#define chardb_final           chardb_sql_final
#define chardb_load_all        chardb_sql_load_all
#define chardb_delete_sub      chardb_sql_delete_sub
#define chardb_build_ranking   chardb_sql_build_ranking
#define chardb_nick2chardata   chardb_sql_nick2chardata
#define chardb_config_read_sub chardb_sql_config_read_sub
#define chardb_set_online(id)  chardb_sql_set_online((id),true)
#define chardb_set_offline(id) chardb_sql_set_online((id),false)
#define chardb_build_ranking   chardb_sql_build_ranking

#endif /* _CHARDB_SQL_H_ */
