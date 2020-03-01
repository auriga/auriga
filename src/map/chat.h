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

#ifndef _CHAT_H_
#define _CHAT_H_

#include "map.h"

void chat_createchat(struct map_session_data *sd, unsigned short limit, unsigned char pub, const char* pass, const char* title, int titlelen);
void chat_joinchat(struct map_session_data *sd, int chatid, const char* pass);
int chat_leavechat(struct map_session_data *sd, unsigned char flag);
void chat_changechatowner(struct map_session_data *sd, const char *nextownername);
void chat_changechatstatus(struct map_session_data *sd, unsigned short limit, unsigned char pub, const char* pass, const char* title, int titlelen);
void chat_kickchat(struct map_session_data *sd, const char *kickusername);

int chat_createnpcchat(
	struct npc_data *nd,int limit,int pub,int trigger,const char* title,int titlelen,const char *ev,
	int zeny,int lowlv,int highlv,unsigned int job,int upper);
int chat_deletenpcchat(struct npc_data *nd);
int chat_enableevent(struct chat_data *cd);
int chat_disableevent(struct chat_data *cd);
int chat_npckickall(struct chat_data *cd);

#endif
