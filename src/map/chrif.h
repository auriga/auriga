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

#ifndef _CHRIF_H_
#define _CHRIF_H_

void chrif_setuserid(const char*);
void chrif_setpasswd(const char*);
void chrif_sethost(const char*);
void chrif_setip(void);
void chrif_setport(unsigned short);
int chrif_parse(int fd);

int chrif_isconnect(void);

int chrif_authreq(struct map_session_data *);
int chrif_save(struct map_session_data*, int final);
int chrif_charselectreq(struct map_session_data *);

int chrif_changemapserver(struct map_session_data *sd,const char *name,int x,int y,unsigned long ip,unsigned short port);

void chrif_searchcharid(int char_id);
int chrif_changegm(int id,const char *pass,size_t len);
int chrif_changesex(int id,int sex);
int chrif_saveaccountreg2(struct map_session_data *sd);

int chrif_mapactive(int active);
int chrif_maintenance(int maintenance);
int chrif_chardisconnect(struct map_session_data *sd);

int chrif_reqdivorce(int char_id);

int chrif_friend_delete( struct map_session_data* sd, int account_id, int char_id );
int chrif_friend_online( struct map_session_data *sd, int flag );

int chrif_req_break_adoption(int char_id, const char *name);

int chrif_ranking_request(int fd);
int chrif_ranking_update(struct Ranking_Data *rd,int ranking_id,int rank);

int chrif_disconnect_sub(struct map_session_data* sd,va_list va);
int chrif_flush_fifo(void);
int do_final_chrif(void);
int do_init_chrif(void);

#endif
