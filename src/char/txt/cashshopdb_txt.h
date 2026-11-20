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

#ifndef _CASHSHOPDB_TXT_H_
#define _CASHSHOPDB_TXT_H_

#include "utils.h"
#include "cashshop_data.h"

bool cashshopdb_txt_init(void);
void cashshopdb_txt_final(void);
int cashshopdb_txt_sync(void);
int cashshopdb_txt_config_read(const char *key, const char *value);
bool cashshopdb_txt_load(int account_id, struct cashshop_account_count *rows, int count);
bool cashshopdb_txt_save(int account_id, const struct cashshop_account_count *rows, int count);

#define cashshopdb_init cashshopdb_txt_init
#define cashshopdb_final cashshopdb_txt_final
#define cashshopdb_sync cashshopdb_txt_sync
#define cashshopdb_config_read cashshopdb_txt_config_read
#define cashshopdb_load cashshopdb_txt_load
#define cashshopdb_save cashshopdb_txt_save

#endif /* _CASHSHOPDB_TXT_H_ */
