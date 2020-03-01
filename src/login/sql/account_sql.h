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

#ifndef _ACCOUNT_SQL_H_
#define _ACCOUNT_SQL_H_

#include "mmo.h"
#include "utils.h"

#include "../login.h"

// プロトタイプ宣言
bool account_sql_init(void);
void account_sql_final(void);
void account_sql_sync(void);
void account_sql_set_default_configvalue(void);
int account_sql_config_read_sub(const char *w1,const char *w2);
bool account_sql_account_delete(int account_id);
const struct mmo_account* account_sql_account_load_num(int account_id);
const struct mmo_account* account_sql_account_load_str(const char *account_id);
const struct mmo_account* account_sql_account_load_idx(int idx);
bool account_sql_account_save(struct mmo_account *ac2);
bool account_sql_account_new(struct mmo_account* account,const char *tmpstr);
void display_conf_warnings_sql(void);

// エイリアス
#define login_init            account_sql_init
#define login_sync            account_sql_sync
#define login_final           account_sql_final
#define login_config_set_defaultvalue_sub account_sql_set_default_configvalue
#define login_config_read_sub account_sql_config_read_sub
#define account_new           account_sql_account_new
#define account_save          account_sql_account_save
#define account_delete        account_sql_account_delete
#define account_load_num      account_sql_account_load_num
#define account_load_str      account_sql_account_load_str
#define account_load_idx      account_sql_account_load_idx
#define display_conf_warnings2 display_conf_warnings_sql

#endif /* _ACCOUNT_SQL_H_ */
