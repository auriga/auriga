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

#ifndef _GUILD_H_
#define _GUILD_H_

#include "mmo.h"

struct map_session_data;
struct mob_data;
struct guild;
struct guild_member;
struct guild_position;

int guild_check_alliance(int guild_id1, int guild_id2, int flag);

int guild_skill_get_inf(int id);
int guild_skill_get_sp(int id,int lv);
int guild_skill_get_range(int id,int lv);
int guild_skill_get_lv(struct guild *g,int id);

void guild_skillmax_load(int len, int *maxlv);
int guild_get_skilltree_max(int id);
int guild_checkskill(struct guild *g,int id);

void do_init_guild(void);
struct guild *guild_search(int guild_id);
struct guild *guild_searchname(const char *str);
struct guild_castle *guild_castle_search(int gcid);

struct guild_castle *guild_mapname2gc(const char *mapname);
struct guild_castle *guild_mapid2gc(int m);

struct map_session_data *guild_get_guildmaster_sd(struct guild *g);

struct map_session_data *guild_getavailablesd(struct guild *g);
int guild_getindex(struct guild *g,int account_id,int char_id);
int guild_getposition(struct map_session_data *sd,struct guild *g);
atn_bignumber guild_payexp(struct map_session_data *sd,atn_bignumber exp);


void guild_create(struct map_session_data *sd,const char *name);
void guild_created(int account_id, int guild_id);
void guild_request_info(int guild_id);
void guild_npc_request_info(int guild_id,const char *ev);
void guild_recv_noinfo(int guild_id);
void guild_recv_info(struct guild *sg);
void guild_invite(struct map_session_data *sd, int account_id);
void guild_reply_invite(struct map_session_data *sd, int guild_id, unsigned char flag);
void guild_member_added(int guild_id, int account_id, int char_id, unsigned char flag);
void guild_leave(struct map_session_data *sd, int guild_id,
	int account_id, int char_id, const char *mes);
void guild_explusion(struct map_session_data *sd, int guild_id,
	int account_id, int char_id, const char *mes);
void guild_member_leaved(int guild_id, int account_id, int char_id, unsigned char flag,
	const char *name, const char *mes);
void guild_skillup(struct map_session_data *sd, int skill_num, int level, int flag);
void guild_reqalliance(struct map_session_data *sd, int account_id);
void guild_reply_reqalliance(struct map_session_data *sd, int account_id, int flag);
int guild_alliance(int guild_id1,int guild_id2,int account_id1,int account_id2);
void guild_allianceack(int guild_id1, int guild_id2, int account_id1, int account_id2,
	unsigned char flag, const char *name1, const char *name2);
void guild_delalliance(struct map_session_data *sd, int guild_id, int flag);
void guild_opposition(struct map_session_data *sd, int char_id);

void guild_send_memberinfoshort(struct map_session_data *sd, unsigned char online);
void guild_recv_memberinfoshort(int guild_id, int account_id, int char_id, unsigned char online, int lv, int class_);
void guild_change_memberposition(int guild_id, int account_id, int char_id, int idx);
void guild_memberposition_changed(struct guild *g, int idx, int pos);
void guild_change_position(int guild_id, int idx, int mode, int exp_mode, const char *name);
void guild_position_changed(int guild_id, int idx, struct guild_position *p);
void guild_change_notice(int guild_id, const char *mes1, const char *mes2);
void guild_notice_changed(int guild_id, const char *mes1, const char *mes2);
void guild_change_emblem(int guild_id, unsigned int len, const char *data);
void guild_emblem_changed(int len, int guild_id, int emblem_id, const char *data);
void guild_send_message(struct map_session_data *sd, const char *mes, size_t len);
void guild_recv_message(int guild_id, int account_id, const char *mes, size_t len);
void guild_skillupack(int guild_id, int skill_num, int account_id,int flag);
void guild_broken(int guild_id, unsigned char flag);
void guild_break(struct map_session_data *sd, const char *name);

void guild_castledataload(int castle_id, int idx);
void guild_addcastleinfoevent(int castle_id, int idx, const char *name);
void guild_castledataloadack(int castle_id, int idx, int value);
void guild_castledatasave(int castle_id, int idx, int value);
void guild_castledatasaveack(int castle_id, int idx, int value);
void guild_castlealldataload(int len, struct guild_castle *gc);

void guild_agit_start(void);
void guild_agit_end(void);
void guild_agit_break(struct mob_data *md);

void guild_getexp(struct map_session_data *sd,int exp);
void guild_flush_expcache(void);

void do_final_guild(void);

#endif
