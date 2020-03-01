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

#ifndef _BOOKING_H_
#define _BOOKING_H_

#include "map.h"

// 旧仕様のパーティーブッキング
void booking_searchcond(struct map_session_data *sd, int lv, int map, int job, unsigned int last_index, int result_count);
void booking_register(struct map_session_data *sd, int lv, int map, int *job);
void booking_update(struct map_session_data *sd, int *job);

// 新仕様のパーティーブッキング
void booking_searchcond2(struct map_session_data *sd, int lv);
void booking_register2(struct map_session_data *sd, int lv, const char *memo);
void booking_update2(struct map_session_data *sd, const char *memo);

// 新旧仕様の共通関数
void booking_delete(struct map_session_data *sd);

// パーティーブッキングデータの処理用
void do_final_booking(void);
void do_init_booking(void);

#endif
