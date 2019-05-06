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

#ifndef _PARTY_H_
#define _PARTY_H_

#include <stdarg.h>

#include "mmo.h"

struct party;
struct map_session_data;
struct mob_data;
struct block_list;

void do_init_party(void);
void do_final_party(void);
struct party *party_search(int party_id);
struct party* party_searchname(const char *str);

void party_create(struct map_session_data *sd, const char *name, int item, int item2);
void party_created(int account_id, unsigned char fail, int party_id, const char *name);
void party_request_info(int party_id);
void party_invite(struct map_session_data *sd, struct map_session_data *tsd);
void party_recv_noinfo(int party_id);
void party_recv_info(struct party *sp);
void party_reply_invite(struct map_session_data *sd, int account_id, int flag);
void party_member_added(int party_id, int account_id, int char_id, unsigned char flag);
void party_removemember(struct map_session_data *sd, int account_id, const char *name);
void party_leave(struct map_session_data *sd);
void party_member_leaved(int party_id, int account_id, int char_id);
void party_broken(int party_id);
void party_changeoption(struct map_session_data *sd, int exp, int item);
void party_optionchanged(int party_id, int account_id, unsigned char exp, unsigned char item, int flag);
void party_recv_movemap(int party_id, int account_id, int char_id, const char *mapname, unsigned char online, unsigned short lv, unsigned short class_);

void party_send_movemap(struct map_session_data *sd);
void party_send_logout(struct map_session_data *sd);

int party_check_same_map_member_count(struct map_session_data *sd);

void party_send_message(struct map_session_data *sd, const char *mes, size_t len);
void party_recv_message(int party_id, int account_id, const char *mes, size_t len);

int party_send_hp_check(struct block_list *bl,va_list ap);

void party_exp_share(struct party *p, struct mob_data *md, atn_bignumber base_exp, atn_bignumber job_exp);
int party_loot_share(struct party *p, struct map_session_data *sd, struct item *item_data, int first);
void party_equip_window(struct map_session_data *sd, int account_id);
void party_changeleader(struct map_session_data *sd, int id);
void party_leaderchanged(int party_id, int old_accont_id, int account_id);

int party_foreachsamemap(int (*func)(struct block_list *,va_list),struct map_session_data *sd,int range,...);

struct map_session_data *party_getavailablesd(struct party *p);

#endif
