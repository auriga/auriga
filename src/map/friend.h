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

#ifndef _FRIEND_H_
#define _FRIEND_H_

struct map_session_data;

void do_init_friend(void);
void do_final_friend(void);

int friend_add_request( struct map_session_data *sd, const char* name );
int friend_add_reply( struct map_session_data *sd, int account_id, int char_id, int flag );
int friend_del_request( struct map_session_data *sd, int account_id, int char_id );
int friend_del_from_otherserver( int account_id, int char_id, int account_id2, int char_id2 );

int friend_send_info( struct map_session_data *sd );
int friend_send_online( struct map_session_data *sd, int flag );
int friend_send_online_from_otherserver( int account_id, int char_id, int flag, int num, int* list );

#endif
