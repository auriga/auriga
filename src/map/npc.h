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

#ifndef _NPC_H_
#define _NPC_H_

#define WARP_CLASS 45
#define WARP_DEBUG_CLASS 722
#define INVISIBLE_CLASS 32767

int npc_event_dequeue(struct map_session_data *sd);
int npc_event(struct map_session_data *sd,const char *npcname);
int npc_touch_areanpc(struct map_session_data *sd,int m,int x,int y);
int npc_touch_areanpc2(struct mob_data *md,int m,int x,int y);
void npc_click(struct map_session_data *sd, int id);
void npc_scriptcont(struct map_session_data *sd, int id);
void npc_buysellsel(struct map_session_data *sd, int id, unsigned char type);
int npc_buylist(struct map_session_data *,int,unsigned short *);
int npc_selllist(struct map_session_data *,int,unsigned short *);
int npc_pointshop_buy(struct map_session_data *sd,int nameid,int amount);
int npc_pointshop_buylist(struct map_session_data *sd, int len, int count, const unsigned short *item_list);
int npc_set_mapflag(int m,const char *w3,const char *w4);
int npc_set_mapflag_sub(int m,const char *str,short flag);
int npc_globalmessage(const char *name,const char *mes);

int npc_enable(const char *name,int flag);
struct npc_data* npc_name2id(const char *name);

bool npc_isnear(struct block_list *bl);

int npc_get_new_npc_id(void);

void npc_addsrcfile(const char *);
void npc_delsrcfile(const char *);
int do_final_npc(void);
int do_init_npc(void);
int npc_event_do_oninit(void);

int npc_event_doall(const char *name);
int npc_event_doall_map(const char *name,int m);
int npc_event_doall_id(const char *name,int rid,int m);
int npc_event_do(const char *name);

int npc_timerevent_start(struct npc_data *nd);
int npc_timerevent_stop(struct npc_data *nd);
int npc_gettimerevent_tick(struct npc_data *nd);
int npc_settimerevent_tick(struct npc_data *nd,int newtimer);

int npc_timeout_start(struct map_session_data *sd);
int npc_timeout_stop(struct map_session_data *sd);
int npc_dynamicnpc_start(struct map_session_data *sd);
int npc_dynamicnpc_stop(struct map_session_data *sd);

// メモリアルダンジョン関連
int npc_addmdnpc(struct npc_data *src_nd, int m);
int npc_free(struct npc_data *nd);

#endif
