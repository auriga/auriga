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
#include "guild.h"
#include "clif.h"
#include "itemdb.h"
#include "pc.h"
#include "script.h"
#include "script_internal.h"
#include "mob.h"
#include "npc.h"
#include "intif.h"
#include "battle.h"
#include "unit.h"

/* Split from script.c (Issue #61) */

/*==========================================
 *
 *------------------------------------------
 */
int script_warp(struct map_session_data *sd, const char *mapname, int x, int y)
{
	nullpo_retr(0, sd);

	if(strcmp(mapname, "Random") == 0) {
		pc_randomwarp(sd, 3);
	} else if(strcmp(mapname, "SavePoint") == 0) {
		pc_setpos(sd, sd->status.save_point.map, sd->status.save_point.x, sd->status.save_point.y, 3);
	} else {
		if(pc_setpos(sd, mapname, x, y, 0)) {
			// 失敗したので .gat を付けてリトライ
			char *str = (char *)aMalloc(strlen(mapname) + 5);
			memcpy(str, mapname, strlen(mapname) + 1);
			strcat(str, ".gat");
			pc_setpos(sd, str, x, y, 0);
			aFree(str);
		}
	}

	if(unit_isdead(&sd->bl)) {
		pc_setstand(sd);
		pc_setrestartvalue(sd, 3);
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int buildin_warp(struct script_state *st)
{
	int x,y;
	char *str;
	struct block_list *bl = map_id2bl(st->rid);

	nullpo_retr(0, bl);

	str=conv_str(st,& (st->stack->stack_data[st->start+2]));
	x=conv_num(st,& (st->stack->stack_data[st->start+3]));
	y=conv_num(st,& (st->stack->stack_data[st->start+4]));

	if(bl->type == BL_PC) {
		script_warp((struct map_session_data *)bl, str, x, y);
	} else if(bl->type == BL_MOB) {
		struct mob_data *md = (struct mob_data *)bl;

		if(strcmp(str, "Random") == 0) {
			mob_warp(md, -1, -1, -1, 3);
		} else {
			int m = map_mapname2mapid(str);
			if(m >= 0)
				mob_warp(md, m, x, y, 3);
		}
	}
	return 0;
}

/*==========================================
 * MAP指定ワープ
 *------------------------------------------
 */
static int buildin_mapwarp_sub(struct block_list *bl,va_list ap)
{
	int x,y;
	char *mapname;
	struct map_session_data *sd;

	nullpo_retr(0, bl);
	nullpo_retr(0, sd = (struct map_session_data *)bl);

	mapname = va_arg(ap, char *);
	x = va_arg(ap,int);
	y = va_arg(ap,int);

	script_warp(sd, mapname, x, y);

	return 0;
}

int buildin_mapwarp(struct script_state *st)
{
	int x,y,m;
	char *mapname, *str;

	mapname=conv_str(st,& (st->stack->stack_data[st->start+2]));
	str=conv_str(st,& (st->stack->stack_data[st->start+3]));
	x=conv_num(st,& (st->stack->stack_data[st->start+4]));
	y=conv_num(st,& (st->stack->stack_data[st->start+5]));

	m = script_mapname2mapid(st,mapname);
	if(m >= 0)
		map_foreachinarea(buildin_mapwarp_sub,m,0,0,map[m].xs,map[m].ys,BL_PC,str,x,y);
	return 0;
}

/*==========================================
 * エリア指定ワープ
 *------------------------------------------
 */
int buildin_areawarp(struct script_state *st)
{
	int x,y,m;
	char *mapname, *str;
	int x0,y0,x1,y1;

	mapname=conv_str(st,& (st->stack->stack_data[st->start+2]));
	x0=conv_num(st,& (st->stack->stack_data[st->start+3]));
	y0=conv_num(st,& (st->stack->stack_data[st->start+4]));
	x1=conv_num(st,& (st->stack->stack_data[st->start+5]));
	y1=conv_num(st,& (st->stack->stack_data[st->start+6]));
	str=conv_str(st,& (st->stack->stack_data[st->start+7]));
	x=conv_num(st,& (st->stack->stack_data[st->start+8]));
	y=conv_num(st,& (st->stack->stack_data[st->start+9]));

	m = script_mapname2mapid(st,mapname);
	if(m >= 0)
		map_foreachinarea(buildin_mapwarp_sub,m,x0,y0,x1,y1,BL_PC,str,x,y);
	return 0;
}

/*==========================================
 * セーブポイントの保存
 *------------------------------------------
 */
int buildin_savepoint(struct script_state *st)
{
	int x,y;
	char *str;

	str=conv_str(st,& (st->stack->stack_data[st->start+2]));
	x=conv_num(st,& (st->stack->stack_data[st->start+3]));
	y=conv_num(st,& (st->stack->stack_data[st->start+4]));
	pc_setsavepoint(script_rid2sd(st),str,x,y);
	return 0;
}

/*==========================================
 * 天の声アナウンス
 *------------------------------------------
 */
int buildin_announce(struct script_state *st)
{
	char *str = conv_str(st,& (st->stack->stack_data[st->start+2]));
	int flag  = conv_num(st,& (st->stack->stack_data[st->start+3]));
	size_t len;
	int color = 0;
	int type = 400;
	int size = 12;
	int align = 0;
	int pos_y = 0;

	if(st->end > st->start+4)
		color = conv_num(st,& (st->stack->stack_data[st->start+4]));
	if(st->end > st->start+5)
		type = conv_num(st,& (st->stack->stack_data[st->start+5]));
	if(st->end > st->start+6)
		size = conv_num(st,& (st->stack->stack_data[st->start+6]));
	if(st->end > st->start+7)
		align = conv_num(st,& (st->stack->stack_data[st->start+7]));
	if(st->end > st->start+8)
		pos_y = conv_num(st,& (st->stack->stack_data[st->start+8]));

	len = strlen(str)+1;

	if(flag&0x07) {
		struct block_list *bl = NULL;
		if(flag&0x08) {
			bl = map_id2bl(st->oid);
		} else {
			struct map_session_data *sd = script_rid2sd(st);
			if(sd)
				bl = &sd->bl;
		}
		if(bl == NULL)
			return 0;

		if(color)
			clif_announce(bl,str,len,(unsigned int)color,type,size,align,pos_y,flag);
		else
			clif_GMmessage(bl,str,len,flag);
	} else {
		if(color)
			intif_announce(str,len,(unsigned int)color,type,size,align,pos_y);
		else
			intif_GMmessage(str,len,flag);
	}
	return 0;
}

/*==========================================
 * 天の声アナウンス（特定マップ）
 *------------------------------------------
 */
static int buildin_mapannounce_sub(struct block_list *bl,va_list ap)
{
	char *str;
	size_t len;
	int color;
	int flag;
	int type,size,align,pos_y;

	nullpo_retr(0, bl);

	str   = va_arg(ap,char *);
	len   = va_arg(ap,size_t);
	flag  = va_arg(ap,int);
	color = va_arg(ap,int);
	type  = va_arg(ap,int);
	size  = va_arg(ap,int);
	align = va_arg(ap,int);
	pos_y = va_arg(ap,int);

	if(color)
		clif_announce(bl,str,len,(unsigned int)color,type,size,align,pos_y,flag|3);
	else
		clif_GMmessage(bl,str,len,flag|3);
	return 0;
}

int buildin_mapannounce(struct script_state *st)
{
	char *mapname,*str;
	int color = 0;
	int flag,m;
	int type = 400;
	int size = 12;
	int align = 0;
	int pos_y = 0;

	mapname=conv_str(st,& (st->stack->stack_data[st->start+2]));
	str=conv_str(st,& (st->stack->stack_data[st->start+3]));
	flag=conv_num(st,& (st->stack->stack_data[st->start+4]));
	if (st->end>st->start+5)
		color=conv_num(st,& (st->stack->stack_data[st->start+5]));
	if (st->end>st->start+6)
		type=conv_num(st,& (st->stack->stack_data[st->start+6]));
	if (st->end>st->start+7)
		size=conv_num(st,& (st->stack->stack_data[st->start+7]));
	if (st->end>st->start+8)
		align=conv_num(st,& (st->stack->stack_data[st->start+8]));
	if (st->end>st->start+9)
		pos_y=conv_num(st,& (st->stack->stack_data[st->start+9]));

	m = script_mapname2mapid(st,mapname);
	if(m >= 0)
		map_foreachinarea(buildin_mapannounce_sub,m,0,0,map[m].xs,map[m].ys,BL_PC,str,strlen(str)+1,flag&0x10,color,type,size,align,pos_y);
	return 0;
}

/*==========================================
 * 天の声アナウンス（特定エリア）
 *------------------------------------------
 */
int buildin_areaannounce(struct script_state *st)
{
	char *mapname,*str;
	int flag,m;
	int x0,y0,x1,y1;
	int color = 0;
	int type = 400;
	int size = 12;
	int align = 0;
	int pos_y = 0;

	mapname = conv_str(st,& (st->stack->stack_data[st->start+2]));
	x0      = conv_num(st,& (st->stack->stack_data[st->start+3]));
	y0      = conv_num(st,& (st->stack->stack_data[st->start+4]));
	x1      = conv_num(st,& (st->stack->stack_data[st->start+5]));
	y1      = conv_num(st,& (st->stack->stack_data[st->start+6]));
	str     = conv_str(st,& (st->stack->stack_data[st->start+7]));
	flag    = conv_num(st,& (st->stack->stack_data[st->start+8]));
	if (st->end>st->start+9)
		color = conv_num(st,& (st->stack->stack_data[st->start+9]));
	if (st->end>st->start+10)
		type = conv_num(st,& (st->stack->stack_data[st->start+10]));
	if (st->end>st->start+11)
		size = conv_num(st,& (st->stack->stack_data[st->start+11]));
	if (st->end>st->start+12)
		align = conv_num(st,& (st->stack->stack_data[st->start+12]));
	if (st->end>st->start+13)
		pos_y = conv_num(st,& (st->stack->stack_data[st->start+13]));

	m = script_mapname2mapid(st,mapname);
	if(m >= 0)
		map_foreachinarea(buildin_mapannounce_sub,m,x0,y0,x1,y1,BL_PC,str,strlen(str)+1,flag&0x10,color,type,size,align,pos_y);
	return 0;
}

/*==========================================
 * ユーザー数取得
 *------------------------------------------
 */
int buildin_getusers(struct script_state *st)
{
	int flag=conv_num(st,& (st->stack->stack_data[st->start+2]));
	int val = -1;

	switch(flag&0x07){
		case 0:
		{
			struct block_list *bl=map_id2bl( (flag&0x08)? st->oid: st->rid );
			if(bl)
				val=map[bl->m].users;
			break;
		}
		case 1:
			val=map_getusers();
			break;
	}
	push_val(st->stack,C_INT,val);
	return 0;
}

/*==========================================
 * 繋いでるユーザーの全員の名前取得
 *------------------------------------------
 */
int buildin_getusersname(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	struct map_session_data *pl_sd = NULL;
	int i=0,disp_num=1;

	nullpo_retr(0, sd);

	for (i=0;i<fd_max;i++) {
		if(session[i] && (pl_sd = (struct map_session_data *)session[i]->session_data) && pl_sd->state.auth){
			if( !(battle_config.hide_GM_session && pc_isGM(pl_sd)) ){
				if((disp_num++)%10==0)
					clif_scriptnext(sd,st->oid);
				clif_scriptmes(sd,st->oid,pl_sd->status.name);
			}
		}
	}
	return 0;
}

/*==========================================
 * マップ指定ユーザー数取得
 *------------------------------------------
 */
int buildin_getmapusers(struct script_state *st)
{
	char *str;
	int m;

	str=conv_str(st,& (st->stack->stack_data[st->start+2]));

	m = script_mapname2mapid(st,str);
	if(m < 0)
		push_val(st->stack,C_INT,-1);
	else
		push_val(st->stack,C_INT,map[m].users);
	return 0;
}

/*==========================================
 * エリア指定ユーザー数取得
 *------------------------------------------
 */
static int buildin_getareausers_sub(struct block_list *bl,va_list ap)
{
	return 1;
}

int buildin_getareausers(struct script_state *st)
{
	char *str;
	int m,x0,y0,x1,y1,users=0;

	str=conv_str(st,& (st->stack->stack_data[st->start+2]));
	x0=conv_num(st,& (st->stack->stack_data[st->start+3]));
	y0=conv_num(st,& (st->stack->stack_data[st->start+4]));
	x1=conv_num(st,& (st->stack->stack_data[st->start+5]));
	y1=conv_num(st,& (st->stack->stack_data[st->start+6]));

	m = script_mapname2mapid(st,str);
	if(m < 0) {
		push_val(st->stack,C_INT,-1);
		return 0;
	}
	users = map_foreachinarea(buildin_getareausers_sub,m,x0,y0,x1,y1,BL_PC);
	push_val(st->stack,C_INT,users);
	return 0;
}

/*==========================================
 * エリア指定ドロップアイテム数取得
 *------------------------------------------
 */
static int buildin_getareadropitem_sub(struct block_list *bl,va_list ap)
{
	int item=va_arg(ap,int);
	struct flooritem_data *fitem;

	nullpo_retr(0, bl);
	nullpo_retr(0, fitem = (struct flooritem_data *)bl);

	if(fitem->item_data.nameid == item)
		return fitem->item_data.amount;

	return 0;
}

int buildin_getareadropitem(struct script_state *st)
{
	char *str;
	int m,x0,y0,x1,y1,item=0,amount=0;
	struct script_data *data;

	str = conv_str(st,& (st->stack->stack_data[st->start+2]));
	x0  = conv_num(st,& (st->stack->stack_data[st->start+3]));
	y0  = conv_num(st,& (st->stack->stack_data[st->start+4]));
	x1  = conv_num(st,& (st->stack->stack_data[st->start+5]));
	y1  = conv_num(st,& (st->stack->stack_data[st->start+6]));

	data = &(st->stack->stack_data[st->start+7]);
	get_val(st,data);
	if( isstr(data) ) {
		const char *name = conv_str(st,data);
		struct item_data *item_data = itemdb_searchname(name);
		if(item_data)
			item = item_data->nameid;
	} else {
		item = conv_num(st,data);
	}

	m = script_mapname2mapid(st,str);
	if(m < 0) {
		push_val(st->stack,C_INT,-1);
		return 0;
	}
	if(item > 0) {
		amount = map_foreachinarea(buildin_getareadropitem_sub,m,x0,y0,x1,y1,BL_ITEM,item);
	}
	push_val(st->stack,C_INT,amount);

	return 0;
}

/*==========================================
 * マップフラグのindexからアドレスを返す
 *------------------------------------------
 */
static int* script_conv_mapflag(int m,int type)
{
	if(m < 0)
		return NULL;

	switch(type) {
		case MF_NOSAVE:             return &map[m].flag.nosave;
		case MF_NOMEMO:             return &map[m].flag.nomemo;
		case MF_NOTELEPORT:         return &map[m].flag.noteleport;
		case MF_NOPORTAL:           return &map[m].flag.noportal;
		case MF_NORETURN:           return &map[m].flag.noreturn;
		case MF_MONSTER_NOTELEPORT: return &map[m].flag.monster_noteleport;
		case MF_NOBRANCH:           return &map[m].flag.nobranch;
		case MF_NOPENALTY:          return &map[m].flag.nopenalty;
		case MF_PVP:                return &map[m].flag.pvp;
		case MF_PVP_NOPARTY:        return &map[m].flag.pvp_noparty;
		case MF_PVP_NOGUILD:        return &map[m].flag.pvp_noguild;
		case MF_PVP_NIGHTMAREDROP:  return &map[m].flag.pvp_nightmaredrop;
		case MF_PVP_NOCALCRANK:     return &map[m].flag.pvp_nocalcrank;
		case MF_GVG:                return &map[m].flag.gvg;
		case MF_GVG_NOPARTY:        return &map[m].flag.gvg_noparty;
		case MF_GVG_NIGHTMAREDROP:  return &map[m].flag.gvg_nightmaredrop;
		case MF_NOZENYPENALTY:      return &map[m].flag.nozenypenalty;
		case MF_NOTRADE:            return &map[m].flag.notrade;
		case MF_NOSKILL:            return &map[m].flag.noskill;
		case MF_NOABRA:             return &map[m].flag.noabra;
		case MF_NODROP:             return &map[m].flag.nodrop;
		case MF_SNOW:               return &map[m].flag.snow;
		case MF_FOG:                return &map[m].flag.fog;
		case MF_SAKURA:             return &map[m].flag.sakura;
		case MF_LEAVES:             return &map[m].flag.leaves;
		case MF_RAIN:               return &map[m].flag.rain;
		case MF_FIREWORKS:          return &map[m].flag.fireworks;
		case MF_CLOUD1:             return &map[m].flag.cloud1;
		case MF_CLOUD2:             return &map[m].flag.cloud2;
		case MF_CLOUD3:             return &map[m].flag.cloud3;
		case MF_BASEEXP_RATE:       return &map[m].flag.base_exp_rate;
		case MF_JOBEXP_RATE:        return &map[m].flag.job_exp_rate;
		case MF_PK:                 return &map[m].flag.pk;
		case MF_PK_NOPARTY:         return &map[m].flag.pk_noparty;
		case MF_PK_NOGUILD:         return &map[m].flag.pk_noguild;
		case MF_PK_NIGHTMAREDROP:   return &map[m].flag.pk_nightmaredrop;
		case MF_PK_NOCALCRANK:      return &map[m].flag.pk_nocalcrank;
		case MF_NOICEWALL:          return &map[m].flag.noicewall;
		case MF_TURBO:              return &map[m].flag.turbo;
		case MF_NOREVIVE:           return &map[m].flag.norevive;
		case MF_NOCOMMAND:          return &map[m].flag.nocommand;
		case MF_NOJUMP:             return &map[m].flag.nojump;
		case MF_NOCOSTUME:          return &map[m].flag.nocostume;
		case MF_TOWN:               return &map[m].flag.town;
		case MF_DAMAGE_RATE:        return &map[m].flag.damage_rate;
	}
	return NULL;
}

/*==========================================
 * マップフラグを設定する
 *------------------------------------------
 */
int buildin_setmapflag(struct script_state *st)
{
	char *mapname = conv_str(st,& (st->stack->stack_data[st->start+2]));
	int type = conv_num(st,& (st->stack->stack_data[st->start+3]));
	int m;
	int *flag;

	if((m = script_mapname2mapid(st,mapname)) < 0)
		return 0;
	flag = script_conv_mapflag(m, type);

	if(flag)
	{
		*flag = 1;
		switch (type) {		// 特殊処理が必要なマップフラグ
		case MF_NOSAVE:
			if(st->end > st->start+6) {
				char *str = conv_str(st,& (st->stack->stack_data[st->start+4]));
				int x     = conv_num(st,& (st->stack->stack_data[st->start+5]));
				int y     = conv_num(st,& (st->stack->stack_data[st->start+6]));
				strncpy(map[m].save.map, str, 16);
				map[m].save.map[15] = '\0';	// force \0 terminal
				map[m].save.x = x;
				map[m].save.y = y;
			}
			break;
		case MF_BASEEXP_RATE:
		case MF_JOBEXP_RATE:
		case MF_NOCOMMAND:
		case MF_DAMAGE_RATE:
			if(st->end > st->start+4) {
				*flag = conv_num(st,& (st->stack->stack_data[st->start+4]));
			}
			break;
		case MF_PVP_NIGHTMAREDROP:
		case MF_GVG_NIGHTMAREDROP:
		case MF_PK_NIGHTMAREDROP:
			if(st->end > st->start+6) {
				char buf[128];
				char *arg1 = conv_str(st,& (st->stack->stack_data[st->start+4]));
				char *arg2 = conv_str(st,& (st->stack->stack_data[st->start+5]));
				int  per   = conv_num(st,& (st->stack->stack_data[st->start+6]));
				snprintf(buf, sizeof(buf), "%s,%s,%d", arg1, arg2, per);
				npc_set_mapflag_sub(m, buf, type);
			}
			break;
		}
		map_field_setting();
	}
	return 0;
}

/*==========================================
 * マップフラグを削除する
 *------------------------------------------
 */
int buildin_removemapflag(struct script_state *st)
{
	char *mapname = conv_str(st,& (st->stack->stack_data[st->start+2]));
	int type = conv_num(st,& (st->stack->stack_data[st->start+3]));
	int m;
	int *flag;

	if((m = script_mapname2mapid(st,mapname)) < 0)
		return 0;
	flag = script_conv_mapflag(m, type);

	if(flag)
	{
		*flag = 0;
		switch (type) {		// 特殊処理が必要なマップフラグ
		case MF_PVP_NIGHTMAREDROP:
		case MF_GVG_NIGHTMAREDROP:
		case MF_PK_NIGHTMAREDROP:
			{
				int i,j;
				for(i=0; i<MAX_DROP_PER_MAP; i++) {	// 該当のドロップリストを削除して空きを詰める
					if(map[m].drop_list[i].drop_id == 0)
						break;
					if(map[m].drop_list[i].drop_flag != type)
						continue;
					for(j=i+1; j<MAX_DROP_PER_MAP && map[m].drop_list[j].drop_id != 0; j++);
					j--;
					if(i != j) {
						memcpy(&map[m].drop_list[i], &map[m].drop_list[j], sizeof(map[m].drop_list[0]));
					}
					memset(&map[m].drop_list[j], 0, sizeof(map[m].drop_list[0]));
					i--;
				}
			}
			break;
		}
		map_field_setting();
	}
	return 0;
}

/*==========================================
 * マップフラグのチェック
 *------------------------------------------
 */
int buildin_checkmapflag(struct script_state *st)
{
	char *mapname = conv_str(st,& (st->stack->stack_data[st->start+2]));
	int type = conv_num(st,& (st->stack->stack_data[st->start+3]));
	int m;
	int *flag;

	if((m = script_mapname2mapid(st,mapname)) < 0) {
		push_val(st->stack,C_INT,-1);
		return 0;
	}

	flag = script_conv_mapflag(m ,type);

	push_val(st->stack,C_INT,((flag)? *flag: -1));
	return 0;
}

/*==========================================
 * PvPオン
 *------------------------------------------
 */
int buildin_pvpon(struct script_state *st)
{
	char *str;
	int m;

	str = conv_str(st,& (st->stack->stack_data[st->start+2]));
	m = script_mapname2mapid(st,str);
	if(m >= 0 && !map[m].flag.pvp) {
		int i;
		struct map_session_data *pl_sd;
		unsigned int tick = gettick();

		map[m].flag.pvp = 1;
		clif_send0199(m,1);

		for(i=0; i<fd_max; i++) {	// 人数分ループ
			if(session[i] && (pl_sd = (struct map_session_data *)session[i]->session_data) && pl_sd->state.auth) {
				if(m == pl_sd->bl.m && pl_sd->pvp_timer == -1) {
					pl_sd->pvp_timer = add_timer(tick+200,pc_calc_pvprank_timer,pl_sd->bl.id,NULL);
					pl_sd->pvp_rank = 0;
					pl_sd->pvp_lastusers = 0;
					pl_sd->pvp_point = 5;
				}
			}
		}
		map_field_setting();
	}
	return 0;
}

/*==========================================
 * PvPオフ
 *------------------------------------------
 */
int buildin_pvpoff(struct script_state *st)
{
	char *str;
	int m;

	str = conv_str(st,& (st->stack->stack_data[st->start+2]));
	m = script_mapname2mapid(st,str);
	if(m >= 0 && map[m].flag.pvp) {
		int i;
		struct map_session_data *pl_sd;

		map[m].flag.pvp = 0;
		clif_send0199(m,0);

		for(i=0; i<fd_max; i++) {	// 人数分ループ
			if(session[i] && (pl_sd = (struct map_session_data *)session[i]->session_data) && pl_sd->state.auth) {
				if(m == pl_sd->bl.m) {
					clif_pvpset(pl_sd,0,0,2);
					if(pl_sd->pvp_timer != -1) {
						delete_timer(pl_sd->pvp_timer,pc_calc_pvprank_timer);
						pl_sd->pvp_timer = -1;
					}
				}
			}
		}
		map_field_setting();
	}

	return 0;
}

/*==========================================
 * GvGオン
 *------------------------------------------
 */
int buildin_gvgon(struct script_state *st)
{
	char *str;
	int m;

	str = conv_str(st,& (st->stack->stack_data[st->start+2]));
	m = script_mapname2mapid(st,str);
	if(m >= 0 && !map[m].flag.gvg) {
		map[m].flag.gvg = 1;
		clif_send0199(m,3);
		map_field_setting();
	}

	return 0;
}

/*==========================================
 * GvGオフ
 *------------------------------------------
 */
int buildin_gvgoff(struct script_state *st)
{
	char *str;
	int m;

	str = conv_str(st,& (st->stack->stack_data[st->start+2]));
	m = script_mapname2mapid(st,str);
	if(m >= 0 && map[m].flag.gvg) {
		map[m].flag.gvg = 0;
		clif_send0199(m,0);
		map_field_setting();
	}

	return 0;
}


/*==========================================
 * 特定対象を移動、攻城戦用
 *------------------------------------------
 */
static int buildin_maprespawnguildid_sub_pc(struct map_session_data *sd, va_list ap)
{
	int m    = va_arg(ap, int);
	int g_id = va_arg(ap, int);
	int flag = va_arg(ap, int);

	nullpo_retr(0, sd);

	if(sd->bl.m == m) {
		// ワープ中などでブロックリストから外れたPCも対象とするかどうか
		if(battle_config.maprespawnguildid_all_players || sd->bl.prev) {
			int match = (g_id > 0 && sd->status.guild_id == g_id);
			if( (flag&1 && match) || (flag&2 && !match) )
				pc_setpos(sd, sd->status.save_point.map, sd->status.save_point.x, sd->status.save_point.y, 3);
		}
	}

	return 0;
}

static int buildin_maprespawnguildid_sub_mob(struct block_list *bl, va_list ap)
{
	struct mob_data *md = NULL;

	nullpo_retr(0, bl);

	if(bl->type != BL_MOB || (md = (struct mob_data *)bl) == NULL)
		return 0;

	if(!md->guild_id)
		unit_remove_map(&md->bl, 1, 0);

	return 0;
}

int buildin_maprespawnguildid(struct script_state *st)
{
	char *mapname = conv_str(st,& (st->stack->stack_data[st->start+2]));
	int g_id      = conv_num(st,& (st->stack->stack_data[st->start+3]));
	int flag      = conv_num(st,& (st->stack->stack_data[st->start+4]));
	int m;

	m = script_mapname2mapid(st,mapname);
	if(m >= 0) {
		if(flag&3) {
			clif_foreachclient(buildin_maprespawnguildid_sub_pc, m, g_id, flag);
		}
		if(flag&4) {
			map_foreachinarea(buildin_maprespawnguildid_sub_mob, m, 0, 0, map[m].xs, map[m].ys, BL_MOB);
		}
	}
	return 0;
}

