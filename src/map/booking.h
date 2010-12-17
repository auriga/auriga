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

#ifndef _BOOKING_H_
#define _BOOKING_H_

#include "map.h"

#define MAX_RESULT 10
#define MAX_BOOKING_MAPID 193
#define MAX_BOOKING_JOBID 64

void booking_searchcond(struct map_session_data *sd, int lv, int map, int job, int last_index, int result_count);
void booking_register(struct map_session_data *sd, int lv, int map, int *job);
void booking_update(struct map_session_data *sd, int *job);
void booking_delete(struct map_session_data *sd);
void do_final_booking(void);
void do_init_booking(void);

#endif
