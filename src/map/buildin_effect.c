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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "db.h"
#include "socket.h"
#include "timer.h"
#include "malloc.h"
#include "mmo.h"
#include "nullpo.h"
#include "utils.h"

#include "map.h"
#include "clif.h"
#include "pc.h"
#include "npc.h"
#include "script.h"
#include "script_internal.h"

/* Split from script.c (Issue #61) */

/*==========================================
 * NPCから発生するエフェクト
 *------------------------------------------
 */
int buildin_misceffect(struct script_state *st)
{
	struct npc_data *nd;
	int type, flag = 0;

	type = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if(st->end > st->start+3)
		nd = npc_name2id(conv_str(st,& (st->stack->stack_data[st->start+3])));
	else
		nd = map_id2nd(st->oid);
	if( st->end > st->start+4 )
		flag = conv_num(st,& (st->stack->stack_data[st->start+4]));

	if(nd) {
		if(flag) {
			struct map_session_data *sd = map_id2sd(st->rid);
			if(sd)
				clif_misceffect3(sd->fd,nd->bl.id,type);
		}
		else
			clif_misceffect2(&nd->bl,type);
	} else {
		struct block_list *bl = map_id2bl(st->rid);
		if(bl) {
			if(flag && bl->type == BL_PC)
				clif_misceffect3(((struct map_session_data *)bl)->fd,bl->id,type);
			else
				clif_misceffect2(bl,type);
		}
	}
	return 0;
}

/*==========================================
 * エリア内のPCに発生するエフェクト
 *------------------------------------------
 */
static int buildin_misceffect_sub(struct block_list *bl,va_list ap)
{
	struct map_session_data *sd;
	int type = va_arg(ap,int);

	nullpo_retr(0, bl);
	nullpo_retr(0, sd = (struct map_session_data *)bl);

	clif_misceffect3(sd->fd, sd->bl.id, type);
	return 0;
}

int buildin_areamisceffect(struct script_state *st)
{
	char *str;
	int type,m,x0,y0,x1,y1;

	str  = conv_str(st,& (st->stack->stack_data[st->start+2]));
	x0   = conv_num(st,& (st->stack->stack_data[st->start+3]));
	y0   = conv_num(st,& (st->stack->stack_data[st->start+4]));
	x1   = conv_num(st,& (st->stack->stack_data[st->start+5]));
	y1   = conv_num(st,& (st->stack->stack_data[st->start+6]));
	type = conv_num(st,& (st->stack->stack_data[st->start+7]));

	m = script_mapname2mapid(st,str);
	if(m >= 0)
		map_foreachinarea(buildin_misceffect_sub,m,x0,y0,x1,y1,BL_PC,type);
	return 0;
}

/*==========================================
 * サウンドエフェクト
 *------------------------------------------
 */
int buildin_soundeffect(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	char *name;
	int type, interval = 0;

	name = conv_str(st,& (st->stack->stack_data[st->start+2]));
	type = conv_num(st,& (st->stack->stack_data[st->start+3]));
	if(st->end > st->start+4)
		interval = conv_num(st,& (st->stack->stack_data[st->start+4]));

	if(sd) {
		if(st->oid)
			clif_soundeffect(sd,map_id2bl(st->oid),name,type,interval);
		else
			clif_soundeffect(sd,&sd->bl,name,type,interval);
	}
	return 0;
}

/*==========================================
 * 範囲指定サウンドエフェクト
 *------------------------------------------
 */
static int buildin_soundeffect_sub(struct block_list *bl,va_list ap)
{
	struct map_session_data *sd;
	char *name   = va_arg(ap,char *);
	int type     = va_arg(ap,int);
	int interval = va_arg(ap,int);

	nullpo_retr(0, bl);
	nullpo_retr(0, sd = (struct map_session_data *)bl);

	clif_soundeffect(sd,bl,name,type,interval);

	return 0;
}

int buildin_areasoundeffect(struct script_state *st)
{
	char *name,*str;
	int type,m,x0,y0,x1,y1;
	int interval = 0;

	str  = conv_str(st,& (st->stack->stack_data[st->start+2]));
	x0   = conv_num(st,& (st->stack->stack_data[st->start+3]));
	y0   = conv_num(st,& (st->stack->stack_data[st->start+4]));
	x1   = conv_num(st,& (st->stack->stack_data[st->start+5]));
	y1   = conv_num(st,& (st->stack->stack_data[st->start+6]));
	name = conv_str(st,& (st->stack->stack_data[st->start+7]));
	type = conv_num(st,& (st->stack->stack_data[st->start+8]));
	if(st->end > st->start+9)
		interval = conv_num(st,& (st->stack->stack_data[st->start+9]));

	m = script_mapname2mapid(st,str);
	if(m >= 0)
		map_foreachinarea(buildin_soundeffect_sub,m,x0,y0,x1,y1,BL_PC,name,type,interval);
	return 0;
}

/*==========================================
 * NPCから発生するエフェクト除去
 *------------------------------------------
 */
int buildin_delmisceffect(struct script_state *st)
{
	struct npc_data *nd;
	int type, flag = 0;

	type = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if(st->end > st->start+3)
		nd = npc_name2id(conv_str(st,& (st->stack->stack_data[st->start+3])));
	else
		nd = map_id2nd(st->oid);
	if( st->end > st->start+4 )
		flag = conv_num(st,& (st->stack->stack_data[st->start+4]));

	if(nd) {
		if(flag) {
			struct map_session_data *sd = map_id2sd(st->rid);
			if(sd)
				clif_remove_misceffect3(sd->fd,nd->bl.id,type);
		}
		else
			clif_remove_misceffect2(&nd->bl,type);
	} else {
		struct block_list *bl = map_id2bl(st->rid);
		if(bl) {
			if(flag && bl->type == BL_PC)
				clif_remove_misceffect3(((struct map_session_data *)bl)->fd,bl->id,type);
			else
				clif_remove_misceffect2(bl,type);
		}
	}
	return 0;
}

/*==========================================
 * ミュージックエフェクト
 *------------------------------------------
 */
int buildin_musiceffect(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	char *name = conv_str(st,& (st->stack->stack_data[st->start+2]));

	if(sd)
		clif_musiceffect(sd,name);

	return 0;
}

/*==========================================
 * 範囲指定ミュージックエフェクト
 *------------------------------------------
 */
static int buildin_musiceffect_sub(struct block_list *bl,va_list ap)
{
	struct map_session_data *sd;
	char *name = va_arg(ap,char *);

	nullpo_retr(0, bl);
	nullpo_retr(0, sd = (struct map_session_data *)bl);

	clif_musiceffect(sd,name);

	return 0;
}

int buildin_areamusiceffect(struct script_state *st)
{
	char *name,*str;
	int m,x0,y0,x1,y1;

	str  = conv_str(st,& (st->stack->stack_data[st->start+2]));
	x0   = conv_num(st,& (st->stack->stack_data[st->start+3]));
	y0   = conv_num(st,& (st->stack->stack_data[st->start+4]));
	x1   = conv_num(st,& (st->stack->stack_data[st->start+5]));
	y1   = conv_num(st,& (st->stack->stack_data[st->start+6]));
	name = conv_str(st,& (st->stack->stack_data[st->start+7]));

	m = script_mapname2mapid(st,str);
	if(m >= 0)
		map_foreachinarea(buildin_musiceffect_sub,m,x0,y0,x1,y1,BL_PC,name);
	return 0;
}
