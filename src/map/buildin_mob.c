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
#include "pc.h"
#include "script.h"
#include "script_internal.h"
#include "mob.h"
#include "skill.h"
#include "status.h"
#include "unit.h"
#include "battle.h"

/* Split from script.c (Issue #61) */

/*==========================================
 * モンスター発生
 *------------------------------------------
 */
int buildin_monster(struct script_state *st)
{
	int mob_id,amount,m,x,y,guild_id=0,id;
	char *str,*mapname,*mobname;
	const char *event = "";
	struct mob_data *md;

	mapname = conv_str(st,& (st->stack->stack_data[st->start+2]));
	x       = conv_num(st,& (st->stack->stack_data[st->start+3]));
	y       = conv_num(st,& (st->stack->stack_data[st->start+4]));
	str     = conv_str(st,& (st->stack->stack_data[st->start+5]));
	mobname = conv_str(st,& (st->stack->stack_data[st->start+6]));

	if((mob_id = atoi(mobname)) == 0)
		mob_id = mobdb_searchname(mobname);
	if(mob_id >= 0 && !mobdb_exists(mob_id))
		return 0;

	amount = conv_num(st,& (st->stack->stack_data[st->start+7]));
	if(st->end > st->start+8) {
		event = conv_str(st,& (st->stack->stack_data[st->start+8]));
	}
	if(st->end > st->start+9) {	// Guild_ID入り
		guild_id = conv_num(st,& (st->stack->stack_data[st->start+9]));
	}

	if((m = script_mapname2mapid(st,mapname)) < 0)
		return 0;

	id = mob_once_spawn(map_id2sd(st->rid),m,x,y,str,mob_id,amount,event);

	if((md = map_id2md(id)) != NULL)
	{
		md->guardup_lv = 0;
		if(guild_id > 0) {
			struct guild *g = guild_search(guild_id);
			if(g) {
				// ガーディアンならギルドスキル適用
				md->guild_id   = guild_id;
				md->guardup_lv = guild_checkskill(g,GD_GUARDUP);
			}
		}

		// ランダム召還じゃないならドロップあり
		if(mob_id == -1) {
			if(md->mode&MD_BOSS) {	// 手抜きボス属性
				md->state.nodrop = battle_config.branch_boss_no_drop;
				md->state.noexp  = battle_config.branch_boss_no_exp;
				md->state.nomvp  = battle_config.branch_boss_no_mvp;
			} else {
				md->state.nodrop = battle_config.branch_mob_no_drop;
				md->state.noexp  = battle_config.branch_mob_no_exp;
				md->state.nomvp  = battle_config.branch_mob_no_mvp;
			}
		}
	}

	return 0;
}

/*==========================================
 * モンスター発生エリア指定
 *------------------------------------------
 */
int buildin_areamonster(struct script_state *st)
{
	int mob_id,amount,m,x0,y0,x1,y1;
	char *str,*mapname,*mobname;
	const char *event = "";

	mapname = conv_str(st,& (st->stack->stack_data[st->start+2]));
	x0      = conv_num(st,& (st->stack->stack_data[st->start+3]));
	y0      = conv_num(st,& (st->stack->stack_data[st->start+4]));
	x1      = conv_num(st,& (st->stack->stack_data[st->start+5]));
	y1      = conv_num(st,& (st->stack->stack_data[st->start+6]));
	str     = conv_str(st,& (st->stack->stack_data[st->start+7]));
	mobname = conv_str(st,& (st->stack->stack_data[st->start+8]));

	if((mob_id = atoi(mobname)) == 0)
		mob_id = mobdb_searchname(mobname);

	amount = conv_num(st,& (st->stack->stack_data[st->start+9]));
	if(st->end > st->start+10)
		event = conv_str(st,& (st->stack->stack_data[st->start+10]));

	m = script_mapname2mapid(st,mapname);
	if(m >= 0)
		mob_once_spawn_area(map_id2sd(st->rid), m, x0, y0, x1, y1, str, mob_id, amount, event);

	return 0;
}

/*==========================================
 * モンスター削除
 *------------------------------------------
 */
static int buildin_killmonster_sub(struct block_list *bl,va_list ap)
{
	struct mob_data *md = NULL;
	char *event=va_arg(ap,char *);
	int allflag=va_arg(ap,int);

	nullpo_retr(0, bl);
	nullpo_retr(0, md = (struct mob_data *)bl);

	if(!allflag) {
		if(strcmp(event,md->npc_event) == 0)
			unit_remove_map(bl,1,0);
	} else {
		if(md->spawndelay1 == -1 && md->spawndelay2 == -1)
			unit_remove_map(bl,1,0);
	}
	return 0;
}

int buildin_killmonster(struct script_state *st)
{
	char *mapname,*event;
	int m,allflag=0;

	mapname=conv_str(st,& (st->stack->stack_data[st->start+2]));
	event=conv_str(st,& (st->stack->stack_data[st->start+3]));

	if((m = script_mapname2mapid(st,mapname)) < 0)
		return 0;

	if(strcmp(event,"All")==0)
		allflag = 1;
	map_foreachinarea(buildin_killmonster_sub,
		m,0,0,map[m].xs,map[m].ys,BL_MOB, event ,allflag);
	return 0;
}

/*==========================================
 * MAP内モンスター全削除
 *------------------------------------------
 */
static int buildin_killmonsterall_sub(struct block_list *bl,va_list ap)
{
	unit_remove_map(bl,1,0);
	return 0;
}

int buildin_killmonsterall(struct script_state *st)
{
	char *mapname;
	int m;

	mapname=conv_str(st,& (st->stack->stack_data[st->start+2]));

	m = script_mapname2mapid(st,mapname);
	if(m >= 0)
		map_foreachinarea(buildin_killmonsterall_sub,m,0,0,map[m].xs,map[m].ys,BL_MOB);
	return 0;
}

/*==========================================
 * モンスター削除エリア指定
 *------------------------------------------
 */
int buildin_areakillmonster(struct script_state *st)
{
	char *mapname;
	int m,x0,y0,x1,y1;

	mapname=conv_str(st,& (st->stack->stack_data[st->start+2]));
	x0=conv_num(st,& (st->stack->stack_data[st->start+3]));
	y0=conv_num(st,& (st->stack->stack_data[st->start+4]));
	x1=conv_num(st,& (st->stack->stack_data[st->start+5]));
	y1=conv_num(st,& (st->stack->stack_data[st->start+6]));

	m = script_mapname2mapid(st,mapname);
	if(m >= 0)
		map_foreachinarea(buildin_killmonsterall_sub,m,x0,y0,x1,y1,BL_MOB);
	return 0;
}

/*==========================================
 * マップ指定mob数取得
 *------------------------------------------
 */
static int buildin_getmapmobs_sub(struct block_list *bl,va_list ap)
{
	struct mob_data *md;
	char *event = va_arg(ap,char *);
	int mob_id = va_arg(ap,int);

	nullpo_retr(0, bl);
	nullpo_retr(0, md = (struct mob_data *)bl);

	// 倒されてる
	if (md->hp <= 0)
		return 0;

	// イベントなし、MobIDの指定なし
	if (!event && !mob_id)
		return 1;

	// 対象イベント
	if(event && strcmp(event,((struct mob_data *)bl)->npc_event) == 0)
		return 1;

	// 対象MobID
	if (mob_id == ((struct mob_data*)bl)->class_)
		return 1;

	return 0;
}

int buildin_getmapmobs(struct script_state *st)
{
	char *str, *event = NULL;
	int m, count = 0, mob_id = 0;

	str=conv_str(st,& (st->stack->stack_data[st->start+2]));
	if(st->end > st->start+3)
	{
		struct script_data *data;
		data = &(st->stack->stack_data[st->start+3]);
		get_val(st,data);

		if( isstr(data) )
			event = conv_str(st,data);
		else
			mob_id = conv_num(st,data);
	}

	m = script_mapname2mapid(st,str);
	if(m < 0)
	{
		push_val(st->stack,C_INT,-1);
		return 0;
	}
	count = map_foreachinarea(buildin_getmapmobs_sub, m, 0, 0, map[m].xs, map[m].ys, BL_MOB, event, mob_id);
	push_val(st->stack,C_INT,count);
	return 0;
}

/*==========================================
 * エリア指定mob数取得
 *------------------------------------------
 */
int buildin_getareamobs(struct script_state *st)
{
	char *str, *event = NULL;
	int m, x0, y0, x1, y1, count = 0, mob_id = 0;

	str=conv_str(st,& (st->stack->stack_data[st->start+2]));
	x0=conv_num(st,& (st->stack->stack_data[st->start+3]));
	y0=conv_num(st,& (st->stack->stack_data[st->start+4]));
	x1=conv_num(st,& (st->stack->stack_data[st->start+5]));
	y1=conv_num(st,& (st->stack->stack_data[st->start+6]));
	if (st->end > st->start + 7)
	{
		struct script_data *data;
		data = &(st->stack->stack_data[st->start + 7]);
		get_val(st, data);

		if (isstr(data))
			event = conv_str(st, data);
		else
			mob_id = conv_num(st, data);
	}

	m = script_mapname2mapid(st,str);
	if (m < 0)
	{
		push_val(st->stack,C_INT,-1);
		return 0;
	}
	count = map_foreachinarea(buildin_getmapmobs_sub, m, x0, y0, x1, y1, BL_MOB, event, mob_id);
	push_val(st->stack,C_INT,count);
	return 0;
}

/*==========================================
 * MOBのIDリスト取得
 *------------------------------------------
 */
static int buildin_getmapmoblist_sub(struct block_list *bl,va_list ap)
{
	struct mob_data *md;
	struct map_session_data *sd = va_arg(ap,struct map_session_data *);
	struct script_state *st = va_arg(ap,struct script_state *);
	int *count = va_arg(ap,int*);
	char *event = va_arg(ap,char *);
	int mob_id = va_arg(ap,int);

	nullpo_retr(0, bl);
	nullpo_retr(0, md = (struct mob_data *)bl);

	// 倒されてる
	if (md->hp <= 0)
		return 0;

	if(	(!event && !mob_id) ||	// イベントなし、MobIDの指定なし
		(event && strcmp(event,((struct mob_data *)bl)->npc_event) == 0) ||	// 対象イベント
		(mob_id == ((struct mob_data*)bl)->class_) ||	// 対象MobID
		(*count) < 128
	) {
		int num;
		char *name;

		num     = st->stack->stack_data[st->start+3].u.num;
		name    = get_str(num&0x00ffffff);
		set_reg(st,sd,num + ((*count)++<<24),name,INT2PTR(((struct mob_data *)bl)->bl.id),st->stack->stack_data[st->start+3].ref);
		return 1;
	}

	return 0;
}

int buildin_getmapmoblist(struct script_state *st)
{
	struct map_session_data *sd = NULL;
	int m, n = 0, mob_id = 0;
	char *mapname, *event = NULL;
	int num;
	char *name;
	char prefix, postfix;
	int count  = 0;

	mapname = conv_str(st,& (st->stack->stack_data[st->start+2]));
	m  = script_mapname2mapid(st,mapname);
	if(m < 0) {
		push_val(st->stack,C_INT,-1);
		return 0;
	}

	if( st->stack->stack_data[st->start+3].type != C_NAME ) {
		printf("buildin_getmapmoblist: param not name\n");
		push_val(st->stack,C_INT,-1);
		return 0;
	}
	num     = st->stack->stack_data[st->start+3].u.num;
	name    = get_str(num&0x00ffffff);
	prefix  = *name;
	postfix = name[strlen(name)-1];

	if(st->end > st->start+4)
	{
		struct script_data *data;
		data = &(st->stack->stack_data[st->start+4]);
		get_val(st,data);

		if( isstr(data) )
			event = conv_str(st,data);
		else
			mob_id = conv_num(st,data);
	}
	sd = (prefix != '$' && prefix != '\'')? script_rid2sd(st): NULL;

	n = map_foreachinarea(buildin_getmapmoblist_sub, m, 0, 0, map[m].xs, map[m].ys, BL_MOB, sd, st, &count, event, mob_id);
	push_val(st->stack,C_INT,n);
	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int buildin_summon(struct script_state *st)
{
	int class_, id;
	char *str;
	const char *event = "";
	struct map_session_data *sd = script_rid2sd(st);
	struct mob_data *md;
	unsigned int tick = gettick();

	if(sd == NULL)
		return 0;

	str    = conv_str(st,& (st->stack->stack_data[st->start+2]));
	class_ = conv_num(st,& (st->stack->stack_data[st->start+3]));
	if( st->end>st->start+4 )
		event = conv_str(st,& (st->stack->stack_data[st->start+4]));

	id = mob_once_spawn(sd, sd->bl.m, 0, 0, str, class_, 1, event);
	if((md = map_id2md(id)) != NULL) {
		md->state.special_mob_ai = MOB_AI_SUMMON;
		md->master_id   = sd->bl.id;
		md->mode        = mobdb_search(md->class_)->mode | MD_AGGRESSIVE;
		md->deletetimer = add_timer(tick+60000,mob_timer_delete,id,NULL);
		clif_misceffect2(&md->bl,344);
	}
	clif_skill_poseffect(&sd->bl,AM_CALLHOMUN,1,sd->bl.x,sd->bl.y,tick);

	return 0;
}

/*==========================================
 * ガーディアン召喚
 *------------------------------------------
 */
int buildin_callguardian(struct script_state *st)
{
	int i,mob_id,amount,m,x,y,index=0;
	char *str,*mapname,*mobname;
	const char *event = "";
	struct guild_castle *gc = NULL;
	struct guild *g = NULL;

	mapname = conv_str(st,& (st->stack->stack_data[st->start+2]));
	x       = conv_num(st,& (st->stack->stack_data[st->start+3]));
	y       = conv_num(st,& (st->stack->stack_data[st->start+4]));
	str     = conv_str(st,& (st->stack->stack_data[st->start+5]));
	mobname = conv_str(st,& (st->stack->stack_data[st->start+6]));

	if((mob_id = atoi(mobname)) == 0)
		mob_id = mobdb_searchname(mobname);
	if(mob_id >= 0 && !mobdb_exists(mob_id))
		return 0;

	amount = conv_num(st,& (st->stack->stack_data[st->start+7]));
	if(st->end > st->start+8) {
		event = conv_str(st,& (st->stack->stack_data[st->start+8]));
	}
	if(st->end > st->start+9) {	// ガーディアンindex
		index = conv_num(st,& (st->stack->stack_data[st->start+9]));
	}

	if((m = script_mapname2mapid(st,mapname)) < 0)
		return 0;

	gc = guild_mapid2gc(m);
	if(gc) {
		g = guild_search(gc->guild_id);
	}

	for(i = 0; i < amount; i++) {
		int id;
		struct mob_data *md;

		id = mob_once_spawn(map_id2sd(st->rid), m, x, y, str, mob_id, 1, event);

		if((md = map_id2md(id)) != NULL)
		{
			md->guardup_lv = 0;
			if(gc) {
				// 砦情報に書き込み
				if(index > 0 && index <= sizeof(gc->guardian) / sizeof(gc->guardian[0])) {
					gc->guardian[index-1].visible = 1;
					gc->guardian[index-1].id      = id;
					guild_castledatasave(gc->castle_id, index + 9, 1);
				}
				if(g) {
					md->guild_id   = g->guild_id;
					md->guardup_lv = guild_checkskill(g, GD_GUARDUP);
				} else {
					md->guild_id   = 1;	// ダミーのIDをセットしておく
				}
			}
		}
	}

	return 0;
}

/*==========================================
 * ガーディアンの情報取得
 *------------------------------------------
 */
int buildin_getguardianinfo(struct script_state *st)
{
	struct guild_castle *gc = NULL;
	int val = 0;
	char *str = NULL;
	char *mapname = conv_str(st,& (st->stack->stack_data[st->start+2]));
	int index     = conv_num(st,& (st->stack->stack_data[st->start+3]));
	int type      = conv_num(st,& (st->stack->stack_data[st->start+4]));

	if(strcmp(mapname,"this") == 0) {
		int m = script_mapname2mapid(st,mapname);
		if(m < 0) {
			if(type == 2)
				push_str(st->stack,C_CONSTSTR,"");
			else
				push_val(st->stack,C_INT,0);
			return 0;
		}
		gc = guild_mapid2gc(m);
	} else {
		gc = guild_mapname2gc(mapname);
	}

	if(gc && index > 0 && index <= sizeof(gc->guardian) / sizeof(gc->guardian[0])) {
		struct mob_data *md = map_id2md(gc->guardian[index-1].id);
		if(md != NULL) {
			switch(type) {
			case 0:		// ID
				val = md->bl.id;
				break;
			case 1:		// Class
				val = md->class_;
				break;
			case 2:		// Name
				str = (char*)aStrdup(md->name);
				break;
			case 3:		// HP
				val = status_get_hp(&md->bl);
				break;
			case 4:		// MaxHP
				val = status_get_max_hp(&md->bl);
				break;
			default:
				val = 0;
				break;
			}
		}
	}

	if(str)
		push_str(st->stack,C_STR,str);
	else
		push_val(st->stack,C_INT,val);

	return 0;
}

/*==========================================
 * IDからモンスター名
 *------------------------------------------
 */
int buildin_getmobname(struct script_state *st)
{
	int mob_class = conv_num(st,& (st->stack->stack_data[st->start+2]));

	if(!mobdb_exists(mob_class))
		push_str(st->stack,C_CONSTSTR,"");
	else
		push_str(st->stack,C_STR,(unsigned char *)aStrdup(mobdb_search(mob_class)->jname));

	return 0;
}

/*==========================================
 * アクティブモンスター変身
 *------------------------------------------
 */
int buildin_active_montransform(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int id, mob_class;

	mob_class = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if(st->end > st->start+3)
		id = conv_num(st,& (st->stack->stack_data[st->start+3]));
	else
		id = current_equip_name_id;

	if(sd) {
		int i;
		for(i = 0; i < sd->activeitem.count; i++) {
			if(sd->activeitem_id2[i] == id && sd->activeitem_timer[i] != -1) {
				if(!unit_isdead(&sd->bl) && status_change_rate(&sd->bl,SC_ACTIVE_MONSTER_TRANSFORM,10000,0) > 0)
					status_change_start(&sd->bl,SC_ACTIVE_MONSTER_TRANSFORM,mob_class,id,0,0,60000,0);
				return 0;
			}
		}
	}

	return 0;
}

/*==========================================
 * モンスター発生
 *------------------------------------------
 */
int buildin_callmonster(struct script_state *st)
{
	int mob_id,m,x,y,id;
	char *str,*mapname,*mobname;
	const char *event = "";
	struct mob_data *md;

	mapname = conv_str(st,& (st->stack->stack_data[st->start+2]));
	x       = conv_num(st,& (st->stack->stack_data[st->start+3]));
	y       = conv_num(st,& (st->stack->stack_data[st->start+4]));
	str     = conv_str(st,& (st->stack->stack_data[st->start+5]));
	mobname = conv_str(st,& (st->stack->stack_data[st->start+6]));

	if((mob_id = atoi(mobname)) == 0)
		mob_id = mobdb_searchname(mobname);
	if(mob_id >= 0 && !mobdb_exists(mob_id))
		return 0;

	if(st->end > st->start+7) {
		event = conv_str(st,& (st->stack->stack_data[st->start+7]));
	}

	if((m = script_mapname2mapid(st,mapname)) < 0)
		return 0;

	id = mob_once_spawn(map_id2sd(st->rid),m,x,y,str,mob_id,1,event);

	if((md = map_id2md(id)) != NULL)
	{
		// ランダム召還じゃないならドロップあり
		if(mob_id == -1) {
			if(md->mode&MD_BOSS) {	// 手抜きボス属性
				md->state.nodrop = battle_config.branch_boss_no_drop;
				md->state.noexp  = battle_config.branch_boss_no_exp;
				md->state.nomvp  = battle_config.branch_boss_no_mvp;
			} else {
				md->state.nodrop = battle_config.branch_mob_no_drop;
				md->state.noexp  = battle_config.branch_mob_no_exp;
				md->state.nomvp  = battle_config.branch_mob_no_mvp;
			}
		}
	}

	push_val(st->stack,C_INT,id);

	return 0;
}

/*==========================================
 * モンスター発生エリア指定
 *------------------------------------------
 */
int buildin_areacallmonster(struct script_state *st)
{
	int mob_id,m,x0,y0,x1,y1,id;
	char *str,*mapname,*mobname;
	const char *event = "";

	mapname = conv_str(st,& (st->stack->stack_data[st->start+2]));
	x0      = conv_num(st,& (st->stack->stack_data[st->start+3]));
	y0      = conv_num(st,& (st->stack->stack_data[st->start+4]));
	x1      = conv_num(st,& (st->stack->stack_data[st->start+5]));
	y1      = conv_num(st,& (st->stack->stack_data[st->start+6]));
	str     = conv_str(st,& (st->stack->stack_data[st->start+7]));
	mobname = conv_str(st,& (st->stack->stack_data[st->start+8]));

	if((mob_id = atoi(mobname)) == 0)
		mob_id = mobdb_searchname(mobname);
	if(mob_id >= 0 && !mobdb_exists(mob_id))
		return 0;

	if(st->end > st->start+9)
		event = conv_str(st,& (st->stack->stack_data[st->start+9]));

	m = script_mapname2mapid(st,mapname);
	if(m >= 0)
		id = mob_once_spawn_area(map_id2sd(st->rid), m, x0, y0, x1, y1, str, mob_id, 1, event);

	push_val(st->stack,C_INT,id);
	return 0;
}

/*==========================================
 * モンスター消去
 *------------------------------------------
 */
int buildin_removemonster(struct script_state *st)
{
	int id, clrtype = 1;
	struct block_list *bl;

	id = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if(st->end > st->start+3)
		clrtype = conv_num(st,& (st->stack->stack_data[st->start+3]));
	bl = map_id2bl(id);

	if(!bl || bl->type != BL_MOB || unit_remove_map(bl,clrtype,0))
		push_val(st->stack,C_INT,0);
	else
		push_val(st->stack,C_INT,1);

	return 0;
}

/*==========================================
 * モンスタースキル行使
 *------------------------------------------
 */
int buildin_mobuseskill(struct script_state *st)
{
	struct mob_data *md;
	struct block_list *tbl;
	int id,skillid,skilllv,casttime,cancel,emotion,talk,target;

	id       = conv_num(st,& (st->stack->stack_data[st->start+2]));
	skillid  = conv_num(st,& (st->stack->stack_data[st->start+3]));
	skilllv  = conv_num(st,& (st->stack->stack_data[st->start+4]));
	casttime = conv_num(st,& (st->stack->stack_data[st->start+5]));
	cancel   = conv_num(st,& (st->stack->stack_data[st->start+6]));
	emotion   = conv_num(st,& (st->stack->stack_data[st->start+7]));
	talk   = conv_num(st,& (st->stack->stack_data[st->start+8]));
	target   = conv_num(st,& (st->stack->stack_data[st->start+9]));

	if((md = map_id2md(id)) == NULL)
		return 0;
	if(skillid <= 0 || skilllv <= 0)
		return 0;

	switch(target) {
		case 0: tbl = map_id2bl(md->bl.id); break;
		case 1: tbl = map_id2bl(md->target_id); break;
		case 2: tbl = map_id2bl(md->master_id); break;
		default:tbl = mob_selecttarget(md, skill_get_fixed_range(&md->bl,skillid,skilllv)); break;
	}

	if(!tbl)
		return 0;

	if(casttime > 0 && md->ud.skilltimer != -1)
		unit_skillcastcancel(&md->bl,0);

	if(skill_get_inf(skillid) & INF_GROUND) {
		if(casttime <= 0)
			skill_castend_pos2(&md->bl, tbl->x, tbl->y, skillid, skilllv, gettick(), 0);
		else
			unit_skilluse_pos2(&md->bl, tbl->x, tbl->y, skillid, skilllv, casttime, cancel);
	}
	else
		unit_skilluse_id2(&md->bl, tbl->id, skillid, skilllv, casttime, cancel);

	if(emotion >= 0)
		clif_emotion(&md->bl, emotion);
	if(talk > 0)
		mob_talk(md, talk);

	return 0;
}

/*==========================================
 * モンスター設置スキル行使
 *------------------------------------------
 */
int buildin_mobuseskillpos(struct script_state *st)
{
	struct mob_data *md;
	int id,skillid,skilllv,x,y,casttime,cancel;

	id       = conv_num(st,& (st->stack->stack_data[st->start+2]));
	skillid  = conv_num(st,& (st->stack->stack_data[st->start+3]));
	skilllv  = conv_num(st,& (st->stack->stack_data[st->start+4]));
	x        = conv_num(st,& (st->stack->stack_data[st->start+5]));
	y        = conv_num(st,& (st->stack->stack_data[st->start+6]));
	casttime = conv_num(st,& (st->stack->stack_data[st->start+7]));
	cancel   = conv_num(st,& (st->stack->stack_data[st->start+8]));

	if((md = map_id2md(id)) == NULL)
		return 0;
	if(skillid <= 0 || skilllv <= 0)
		return 0;

	if(casttime > 0 && md->ud.skilltimer != -1)
		unit_skillcastcancel(&md->bl,0);

	if(skill_get_inf(skillid) & INF_GROUND) {
		if(casttime <= 0)
			skill_castend_pos2(&md->bl, x, y, skillid, skilllv, gettick(), 0);
		else
			unit_skilluse_pos2(&md->bl, x, y, skillid, skilllv, casttime, cancel);
	}

	return 0;
}

/*==========================================
 * 範囲指定モンスタースキル行使
 *------------------------------------------
 */
static int buildin_mobuseskill_sub(struct block_list *bl,va_list ap)
{
	struct mob_data *md;
	struct block_list *tbl;
	int mob_id   = va_arg(ap,int);
	int skillid  = va_arg(ap,int);
	int skilllv  = va_arg(ap,int);
	int casttime = va_arg(ap,int);
	int cancel   = va_arg(ap,int);
	int emotion   = va_arg(ap,int);
	int talk   = va_arg(ap,int);
	int target   = va_arg(ap,int);

	nullpo_retr(0, md = (struct mob_data *)bl);

	if(mob_id > 0 && md->class_ != mob_id)
		return 0;
	if(skillid <= 0 || skilllv <= 0)
		return 0;

	switch(target) {
		case 0:  tbl = map_id2bl(md->bl.id); break;
		case 1:  tbl = map_id2bl(md->target_id); break;
		case 2:  tbl = map_id2bl(md->master_id); break;
		default: tbl = mob_selecttarget(md, skill_get_fixed_range(&md->bl,skillid,skilllv)); break;
	}

	if(!tbl)
		return 0;

	if(casttime > 0 && md->ud.skilltimer != -1)
		unit_skillcastcancel(bl,0);

	if(skill_get_inf(skillid) & INF_GROUND) {
		if(casttime <= 0)
			skill_castend_pos2(&md->bl, tbl->x, tbl->y, skillid, skilllv, gettick(), 0);
		else
			unit_skilluse_pos2(&md->bl, tbl->x, tbl->y, skillid, skilllv, casttime, cancel);
	}
	else
		unit_skilluse_id2(&md->bl, tbl->id, skillid, skilllv, casttime, cancel);

	if(emotion >= 0)
		clif_emotion(&md->bl, emotion);
	if(talk > 0)
		mob_talk(md, talk);

	return 0;
}

int buildin_areamobuseskill(struct script_state *st)
{
	int mob_id,m,x0,y0,x1,y1;
	int skillid,skilllv,casttime,cancel,emotion,talk,target;
	char *mapname;

	mapname  = conv_str(st,& (st->stack->stack_data[st->start+2]));
	x0       = conv_num(st,& (st->stack->stack_data[st->start+3]));
	y0       = conv_num(st,& (st->stack->stack_data[st->start+4]));
	x1       = conv_num(st,& (st->stack->stack_data[st->start+5]));
	y1       = conv_num(st,& (st->stack->stack_data[st->start+6]));
	mob_id   = conv_num(st,& (st->stack->stack_data[st->start+7]));
	skillid  = conv_num(st,& (st->stack->stack_data[st->start+8]));
	skilllv  = conv_num(st,& (st->stack->stack_data[st->start+9]));
	casttime = conv_num(st,& (st->stack->stack_data[st->start+10]));
	cancel   = conv_num(st,& (st->stack->stack_data[st->start+11]));
	emotion   = conv_num(st,& (st->stack->stack_data[st->start+12]));
	talk   = conv_num(st,& (st->stack->stack_data[st->start+13]));
	target   = conv_num(st,& (st->stack->stack_data[st->start+14]));

	m = script_mapname2mapid(st,mapname);
	if(m >= 0)
		map_foreachinarea(buildin_mobuseskill_sub,m,x0,y0,x1,y1,BL_MOB,mob_id,skillid,skilllv,casttime,cancel,emotion,talk,target);
	return 0;
}

/*==========================================
 * モンスターのHP取得
 *------------------------------------------
 */
int buildin_getmobhp(struct script_state *st)
{
	struct mob_data *md;
	int id, hp;

	id = conv_num(st,& (st->stack->stack_data[st->start+2]));

	if((md = map_id2md(id)) == NULL) {
		push_val(st->stack,C_INT,-1);
		return 0;
	}
	// 死亡中
	if(md->bl.prev == NULL) {
		push_val(st->stack,C_INT,-1);
		return 0;
	}

	hp = md->hp;
	if(md->hp < 0)
		hp = 0;

	push_val(st->stack,C_INT,hp);
	return 0;
}

/*==========================================
 * モンスターのHP設定
 *------------------------------------------
 */
int buildin_setmobhp(struct script_state *st)
{
	struct mob_data *md;
	int id, max_hp, hp;

	id = conv_num(st,& (st->stack->stack_data[st->start+2]));
	hp = conv_num(st,& (st->stack->stack_data[st->start+3]));

	if((md = map_id2md(id)) == NULL)
		return 0;
	// 死亡中
	if(md->bl.prev == NULL || md->hp <= 0)
		return 0;

	max_hp = status_get_max_hp(&md->bl);

	// 最大HPを越えて設定できない
	if(hp > max_hp)
		hp = max_hp;
	// 殺害することはできない
	if(hp <= 0)
		hp = 1;
	md->hp = hp;

	return 0;
}

/*==========================================
 * ランダム系モンスターのID取得
 *------------------------------------------
 */
int buildin_getrandommob(struct script_state *st)
{
	int lv = MAX_LEVEL;
	int nameid = conv_num(st,& (st->stack->stack_data[st->start+2]));

	if( st->end > st->start+3 )
		lv = conv_num(st,& (st->stack->stack_data[st->start+3]));

	push_val(st->stack,C_INT,mobdb_searchrandomid(-nameid,lv));
	return 0;
}
