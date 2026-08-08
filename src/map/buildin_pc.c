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
#include "bonus.h"
#include "script.h"
#include "script_internal.h"
#include "skill.h"
#include "status.h"
#include "unit.h"
#include "battle.h"
#include "guild.h"
#include "chrif.h"
#include "intif.h"

/* Split from script.c (Issue #61) */

/*==========================================
 *
 *------------------------------------------
 */
int buildin_heal(struct script_state *st)
{
	int hp,sp;

	hp=conv_num(st,& (st->stack->stack_data[st->start+2]));
	sp=conv_num(st,& (st->stack->stack_data[st->start+3]));

	pc_heal(script_rid2sd(st),hp,sp,0,0);
	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int buildin_itemheal(struct script_state *st)
{
	int hp,sp;

	hp=conv_num(st,& (st->stack->stack_data[st->start+2]));
	sp=conv_num(st,& (st->stack->stack_data[st->start+3]));

	pc_itemheal(script_rid2sd(st),hp,sp);
	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int buildin_percentheal(struct script_state *st)
{
	int hp,sp;

	hp=conv_num(st,& (st->stack->stack_data[st->start+2]));
	sp=conv_num(st,& (st->stack->stack_data[st->start+3]));

	pc_percentheal(script_rid2sd(st),hp,sp);
	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int buildin_jobchange(struct script_state *st)
{
	int job, upper=-1;

	job=conv_num(st,& (st->stack->stack_data[st->start+2]));
	if( st->end>st->start+3 )
		upper=conv_num(st,& (st->stack->stack_data[st->start+3]));

	if(job >= 0 && job < PC_JOB_MAX)
		pc_jobchange(script_rid2sd(st),job, upper);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int buildin_setlook(struct script_state *st)
{
	int type,val;

	type=conv_num(st,& (st->stack->stack_data[st->start+2]));
	val=conv_num(st,& (st->stack->stack_data[st->start+3]));

	pc_changelook(script_rid2sd(st),type,val);

	return 0;
}

/*==========================================
 * 見た目のパラメータを返す
 *   n：1,髪型、2,武器、3,頭上段、4,頭中段、5,頭下段、6,髪色、7,服色、8,盾、13,服装
 *------------------------------------------
 */
int buildin_getlook(struct script_state *st)
{
	int type,val= -1;
	struct map_session_data *sd=script_rid2sd(st);
	type=conv_num(st,& (st->stack->stack_data[st->start+2]));

	if(sd==NULL){
		push_val(st->stack,C_INT,-1);
		return 0;
	}
	switch(type){
		case LOOK_HAIR:
			val=sd->status.hair;
			break;
		case LOOK_WEAPON:
			val=sd->status.weapon;
			break;
		case LOOK_HEAD_BOTTOM:
			val=sd->status.head_bottom;
			break;
		case LOOK_HEAD_TOP:
			val=sd->status.head_top;
			break;
		case LOOK_HEAD_MID:
			val=sd->status.head_mid;
			break;
		case LOOK_HAIR_COLOR:
			val=sd->status.hair_color;
			break;
		case LOOK_CLOTHES_COLOR:
			val=sd->status.clothes_color;
			break;
		case LOOK_SHIELD:
			val=sd->status.shield;
			break;
		case LOOK_SHOES:
			break;
		case LOOK_BODY2:
			val=sd->status.style;
			break;
	}
	push_val(st->stack,C_INT,val);
	return 0;
}


/*==========================================
 * キャラ関係のパラメータ取得
 *------------------------------------------
 */
int buildin_readparam(struct script_state *st)
{
	int type;
	struct map_session_data *sd;

	type=conv_num(st,& (st->stack->stack_data[st->start+2]));
	if( st->end>st->start+3 )
		sd=map_nick2sd(conv_str(st,& (st->stack->stack_data[st->start+3])));
	else
		sd=script_rid2sd(st);

	if(sd==NULL){
		push_val(st->stack,C_INT,-1);
		return 0;
	}

	push_val(st->stack,C_INT,pc_readparam(sd,type));

	return 0;
}


/*==========================================
 *
 *------------------------------------------
 */
int buildin_statusup(struct script_state *st)
{
	unsigned short type;

	type = (unsigned short)conv_num(st, &(st->stack->stack_data[st->start+2]));
	pc_statusup(script_rid2sd(st),type,1);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int buildin_statusup2(struct script_state *st)
{
	int type,val;

	type = conv_num(st,& (st->stack->stack_data[st->start+2]));
	val  = conv_num(st,& (st->stack->stack_data[st->start+3]));
	pc_statusup2(script_rid2sd(st),type,val);

	return 0;
}

/*==========================================
 * 装備品による能力値ボーナス
 *------------------------------------------
 */
int buildin_bonus(struct script_state *st)
{
	int type,val;

	type = conv_num(st,& (st->stack->stack_data[st->start+2]));
	val  = conv_num(st,& (st->stack->stack_data[st->start+3]));

	bonus_param1(script_rid2sd(st),type,val);
	return 0;
}

/*==========================================
 * 装備品による能力値ボーナス2
 *------------------------------------------
 */
int buildin_bonus2(struct script_state *st)
{
	int type,type2,val;

	type  = conv_num(st,& (st->stack->stack_data[st->start+2]));

	switch(type) {
	case SP_ADD_SKILL_DAMAGE_RATE:
	case SP_SUB_SKILL_DAMAGE_RATE:
	case SP_ADD_SKILL_BLOW:
	case SP_ADD_CAST_RATE:
	case SP_ADD_FIX_CAST_RATE:
	case SP_ADD_CAST_TIME:
	case SP_ADD_COOL_DOWN:
	case SP_ADD_SKILL_HEAL_RATE:
	case SP_ADD_SKILL_SUBHEAL_RATE:
	case SP_ADD_SP_COST:
		{
			struct script_data *data;
			data = &(st->stack->stack_data[st->start+3]);
			get_val(st,data);
			if(isstr(data)) {
				type2 = skill_get_name2id(conv_str(st,data));
			} else {
				type2 = conv_num(st,data);
			}
		}
		break;
	default:
		type2 = conv_num(st,& (st->stack->stack_data[st->start+3]));
		break;
	}

	val   = conv_num(st,& (st->stack->stack_data[st->start+4]));

	bonus_param2(script_rid2sd(st),type,type2,val);
	return 0;
}

/*==========================================
 * 装備品による能力値ボーナス3
 *------------------------------------------
 */
int buildin_bonus3(struct script_state *st)
{
	int type,type2,type3,val;

	type  = conv_num(st,& (st->stack->stack_data[st->start+2]));

	switch(type) {
	case SP_AUTOSPELL:
	case SP_AUTOSPELL2:
	case SP_AUTOSELFSPELL:
	case SP_AUTOSELFSPELL2:
	case SP_REVAUTOSPELL:
	case SP_REVAUTOSPELL2:
	case SP_REVAUTOSELFSPELL:
	case SP_REVAUTOSELFSPELL2:
	case SP_ADDEFFSKILL:
		{
			struct script_data *data;
			data = &(st->stack->stack_data[st->start+3]);
			get_val(st,data);
			if(isstr(data)) {
				type2 = skill_get_name2id(conv_str(st,data));
			} else {
				type2 = conv_num(st,data);
			}
		}
		break;
	default:
		type2 = conv_num(st,& (st->stack->stack_data[st->start+3]));
		break;
	}
	type3 = conv_num(st,& (st->stack->stack_data[st->start+4]));
	val   = conv_num(st,& (st->stack->stack_data[st->start+5]));

	bonus_param3(script_rid2sd(st),type,type2,type3,val);
	return 0;
}

/*==========================================
 * 装備品による能力値ボーナス4
 *------------------------------------------
 */
int buildin_bonus4(struct script_state *st)
{
	int type,type2,type3,type4;
	unsigned int val;

	type  = conv_num(st,& (st->stack->stack_data[st->start+2]));

	switch(type) {
	case SP_AUTOSPELL:
	case SP_SKILLAUTOSPELL:
	case SP_SKILLAUTOSPELL2:
	case SP_SKILLAUTOSELFSPELL:
	case SP_SKILLAUTOSELFSPELL2:
	case SP_AUTOACTIVE_SKILL:
		{
			struct script_data *data;
			data = &(st->stack->stack_data[st->start+3]);
			get_val(st,data);
			if(isstr(data)) {
				type2 = skill_get_name2id(conv_str(st,data));
			} else {
				type2 = conv_num(st,data);
			}
		}
		break;
	default:
		type2 = conv_num(st,& (st->stack->stack_data[st->start+3]));
		break;
	}
	switch(type) {
	case SP_SKILLAUTOSPELL:
	case SP_SKILLAUTOSPELL2:
	case SP_SKILLAUTOSELFSPELL:
	case SP_SKILLAUTOSELFSPELL2:
		{
			struct script_data *data;
			data = &(st->stack->stack_data[st->start+4]);
			get_val(st,data);
			if(isstr(data)) {
				type3 = skill_get_name2id(conv_str(st,data));
			} else {
				type3 = conv_num(st,data);
			}
		}
		break;
	default:
		type3 = conv_num(st,& (st->stack->stack_data[st->start+4]));
		break;
	}
	type4 = conv_num(st,& (st->stack->stack_data[st->start+5]));
	val   = (unsigned int)conv_num(st,& (st->stack->stack_data[st->start+6]));

	bonus_param4(script_rid2sd(st),type,type2,type3,type4,val);
	return 0;
}

/*==========================================
 * スキル取得
 *------------------------------------------
 */
int buildin_skill(struct script_state *st)
{
	int id,level,flag=1;
	struct script_data *data;

	data = &(st->stack->stack_data[st->start+2]);
	get_val(st,data);
	if( isstr(data) ) {
		id = skill_get_name2id(conv_str(st,data));
	} else {
		id = conv_num(st,data);
	}
	level = conv_num(st,& (st->stack->stack_data[st->start+3]));
	if(st->end > st->start+4)
		flag = conv_num(st,&(st->stack->stack_data[st->start+4]) );

	pc_skill(script_rid2sd(st),id,level,flag);
	return 0;
}


/*==========================================
 * スキルレベル取得
 *------------------------------------------
 */
int buildin_getskilllv(struct script_state *st)
{
	int id;
	struct script_data *data;

	data = &(st->stack->stack_data[st->start+2]);
	get_val(st,data);
	if( isstr(data) ) {
		id = skill_get_name2id(conv_str(st,data));
	} else {
		id = conv_num(st,data);
	}

	push_val(st->stack,C_INT, pc_checkskill2( script_rid2sd(st) ,id) );
	return 0;
}

/*==========================================
 * getgdskilllv(Guild_ID, Skill_ID);
 *------------------------------------------
 */
int buildin_getgdskilllv(struct script_state *st)
{
	int guild_id=conv_num(st,& (st->stack->stack_data[st->start+2]));
	int skill_id=conv_num(st,& (st->stack->stack_data[st->start+3]));
	struct guild *g=guild_search(guild_id);

	push_val(st->stack,C_INT, (g==NULL)? -1: guild_checkskill(g,skill_id) );
	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int buildin_basicskillcheck(struct script_state *st)
{
	push_val(st->stack,C_INT,battle_config.basic_skill_check);
	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int buildin_getgmlevel(struct script_state *st)
{
	push_val(st->stack,C_INT, pc_isGM(script_rid2sd(st)));
	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int buildin_end(struct script_state *st)
{
	st->state = END;
	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int buildin_checkoption(struct script_state *st)
{
	unsigned int type;
	struct map_session_data *sd = script_rid2sd(st);

	type=(unsigned int)conv_num(st,& (st->stack->stack_data[st->start+2]));

	if(sd && sd->sc.option & type){
		push_val(st->stack,C_INT,1);
	} else {
		push_val(st->stack,C_INT,0);
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int buildin_setoption(struct script_state *st)
{
	unsigned int type;

	type = (unsigned int)conv_num(st,& (st->stack->stack_data[st->start+2]));
	pc_setoption(script_rid2sd(st),type);

	return 0;
}

/*==========================================
 * カートを付ける
 *------------------------------------------
 */
int buildin_setcart(struct script_state *st)
{
	pc_setcart( script_rid2sd(st),1 );
	return 0;
}

/*==========================================
 * 鷹を付ける
 *------------------------------------------
 */
int buildin_setfalcon(struct script_state *st)
{
	pc_setfalcon( script_rid2sd(st) );
	return 0;
}

/*==========================================
 * ペコペコ乗り
 *------------------------------------------
 */
int buildin_setriding(struct script_state *st)
{
	pc_setriding( script_rid2sd(st) );
	return 0;
}

/*==========================================
 * ドラゴン騎乗
 *------------------------------------------
 */
int buildin_setdragon(struct script_state *st)
{
	int type = 0;

	if( st->end > st->start+2 )
		type = conv_num(st,& (st->stack->stack_data[st->start+2]));

	pc_setdragon( script_rid2sd(st), type );
	return 0;
}

/*==========================================
 * 魔導ギア騎乗
 *------------------------------------------
 */
int buildin_setgear(struct script_state *st)
{
	pc_setgear( script_rid2sd(st) );
	return 0;
}

/*==========================================
 * 座る
 *------------------------------------------
 */
int buildin_sit(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);

	if(unit_isdead(&sd->bl))
		return 0;
	if(!pc_issit(sd)) {
		pc_setsit(sd);
		clif_sitting(&sd->bl, 1);
		skill_sit(sd,1);	// ギャングスターパラダイスおよびテコン休息設定
	}
	return 0;
}

/*==========================================
 * 立つ
 *------------------------------------------
 */
int buildin_stand(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);

	if(unit_isdead(&sd->bl))
		return 0;
	if(pc_issit(sd)) {
		pc_setstand(sd);
		clif_sitting(&sd->bl, 0);
		skill_sit(sd,0);	// ギャングスターパラダイスおよびテコン休息解除
	}
	return 0;
}

/*==========================================
 * 状態異常にかかる
 *------------------------------------------
 */
int buildin_sc_start(struct script_state *st)
{
	struct block_list *bl;
	int type,tick,val1;

	type=conv_num(st,& (st->stack->stack_data[st->start+2]));
	tick=conv_num(st,& (st->stack->stack_data[st->start+3]));
	val1=conv_num(st,& (st->stack->stack_data[st->start+4]));
	if( st->end>st->start+5 )	// 指定したキャラを状態異常にする
		bl = map_id2bl(conv_num(st,& (st->stack->stack_data[st->start+5])));
	else
		bl = map_id2bl(st->rid);

	if(bl && bl->type == BL_PC) {
		struct map_session_data *sd = (struct map_session_data *)bl;
		if(sd && sd->state.potionpitcher_flag)
			bl = map_id2bl(sd->ud.skilltarget);
	}
	if(bl && !unit_isdead(bl) && status_change_rate(bl,type,10000,0) > 0)
		status_change_start(bl,type,val1,0,0,0,tick,0);
	return 0;
}

/*==========================================
 * 状態異常にかかる(確率指定)
 *------------------------------------------
 */
int buildin_sc_start2(struct script_state *st)
{
	struct block_list *bl;
	int type,tick,val1,per;

	type=conv_num(st,& (st->stack->stack_data[st->start+2]));
	tick=conv_num(st,& (st->stack->stack_data[st->start+3]));
	val1=conv_num(st,& (st->stack->stack_data[st->start+4]));
	per=conv_num(st,& (st->stack->stack_data[st->start+5]));
	if( st->end>st->start+6 )	// 指定したキャラを状態異常にする
		bl = map_id2bl(conv_num(st,& (st->stack->stack_data[st->start+6])));
	else
		bl = map_id2bl(st->rid);

	if(bl && bl->type == BL_PC) {
		struct map_session_data *sd = (struct map_session_data *)bl;
		if(sd && sd->state.potionpitcher_flag)
			bl = map_id2bl(sd->ud.skilltarget);
	}
	if(bl && !unit_isdead(bl) && atn_rand() % 10000 < status_change_rate(bl,type,per,0))
		status_change_start(bl,type,val1,0,0,0,tick,0);
	return 0;
}

/*==========================================
 * 状態異常にかかる(再計算なし)
 *------------------------------------------
 */
int buildin_sc_starte(struct script_state *st)
{
	struct block_list *bl;
	int type,tick,val1;

	type=conv_num(st,& (st->stack->stack_data[st->start+2]));
	tick=conv_num(st,& (st->stack->stack_data[st->start+3]));
	val1=conv_num(st,& (st->stack->stack_data[st->start+4]));
	if( st->end>st->start+5 )	// 指定したキャラを状態異常にする
		bl = map_id2bl(conv_num(st,& (st->stack->stack_data[st->start+5])));
	else
		bl = map_id2bl(st->rid);

	if(bl && bl->type == BL_PC) {
		struct map_session_data *sd = (struct map_session_data *)bl;
		if(sd && sd->state.potionpitcher_flag)
			bl = map_id2bl(sd->ud.skilltarget);
	}
	if(bl && !unit_isdead(bl) && status_change_rate(bl,type,10000,0) > 0)
		status_change_start(bl,type,val1,0,0,0,tick,4);
	return 0;
}

/*==========================================
 * 状態異常にかかる(詳細)
 *------------------------------------------
 */
int buildin_sc_start3(struct script_state *st)
{
	struct block_list *bl;
	int type,tick,val1,val2,val3,val4,flag;

	type=conv_num(st,& (st->stack->stack_data[st->start+2]));
	val1=conv_num(st,& (st->stack->stack_data[st->start+3]));
	val2=conv_num(st,& (st->stack->stack_data[st->start+4]));
	val3=conv_num(st,& (st->stack->stack_data[st->start+5]));
	val4=conv_num(st,& (st->stack->stack_data[st->start+6]));
	tick=conv_num(st,& (st->stack->stack_data[st->start+7]));
	flag=conv_num(st,& (st->stack->stack_data[st->start+8]));
	if( st->end>st->start+9 )	// 指定したキャラを状態異常にする
		bl = map_id2bl(conv_num(st,& (st->stack->stack_data[st->start+9])));
	else
		bl = map_id2bl(st->rid);

	if(bl && bl->type == BL_PC) {
		struct map_session_data *sd = (struct map_session_data *)bl;
		if(sd && sd->state.potionpitcher_flag)
			bl = map_id2bl(sd->ud.skilltarget);
	}
	if(bl && !unit_isdead(bl)) {
		if(flag&8 || status_change_rate(bl,type,10000,0) > 0)
			status_change_start(bl,type,val1,val2,val3,val4,tick,flag);
	}
	return 0;
}

/*==========================================
 * 状態異常が直る
 *------------------------------------------
 */
int buildin_sc_end(struct script_state *st)
{
	struct block_list *bl;
	int type;

	type=conv_num(st,& (st->stack->stack_data[st->start+2]));
	if( st->end>st->start+3 )	// 指定したキャラの状態異常を解除する
		bl = map_id2bl(conv_num(st,& (st->stack->stack_data[st->start+3])));
	else
		bl = map_id2bl(st->rid);

	if(bl && bl->type == BL_PC) {
		struct map_session_data *sd = (struct map_session_data *)bl;
		if(sd && sd->state.potionpitcher_flag)
			bl = map_id2bl(sd->ud.skilltarget);
	}
	if(bl) {
		if(type == SC_DANCING) {
			skill_stop_dancing(bl,0);
		} else {
			if(type == SC_BASILICA)
				skill_basilica_cancel(bl);
			status_change_end(bl,type,-1);
		}
	}
	return 0;
}

/*==========================================
 * 状態異常中かどうか返す
 *------------------------------------------
 */
int buildin_sc_ison(struct script_state *st)
{
	struct block_list *bl = map_id2bl(st->rid);
	int type;

	type = conv_num(st,& (st->stack->stack_data[st->start+2]));

	if(type < 0 || type >= MAX_STATUSCHANGE) {
		printf("buildin_sc_ison: invaild type %d\n", type);
		push_val(st->stack,C_INT,0);
		return 0;
	}

	if(bl && bl->type == BL_PC) {
		struct map_session_data *sd = (struct map_session_data *)bl;
		if(sd && sd->state.potionpitcher_flag)
			bl = map_id2bl(sd->ud.skilltarget);
	}
	if(bl) {
		struct status_change *sc = status_get_sc(bl);
		if(sc && sc->data[type].timer != -1) {
			push_val(st->stack,C_INT,1);
			return 0;
		}
	}
	push_val(st->stack,C_INT,0);
	return 0;
}

/*==========================================
 * 状態異常耐性を計算した確率を返す
 *------------------------------------------
 */
int buildin_getscrate(struct script_state *st)
{
	struct block_list *bl;
	int type,rate=0;

	type=conv_num(st,& (st->stack->stack_data[st->start+2]));
	rate=conv_num(st,& (st->stack->stack_data[st->start+3]));
	if( st->end>st->start+4 )	// 指定したキャラの耐性を計算する
		bl = map_id2bl(conv_num(st,& (st->stack->stack_data[st->start+6])));
	else
		bl = map_id2bl(st->rid);

	if(bl)
		rate = status_change_rate(bl,type,rate,0);

	push_val(st->stack,C_INT,rate);

	return 0;
}

/*==========================================
 * ステータスリセット
 *------------------------------------------
 */
int buildin_resetstatus(struct script_state *st)
{
	int flag = 0;

	if(st->end > st->start+2)
		flag = conv_num(st,& (st->stack->stack_data[st->start+2]));

	pc_resetstatus(script_rid2sd(st), flag);
	return 0;
}

/*==========================================
 * スキルリセット
 *------------------------------------------
 */
int buildin_resetskill(struct script_state *st)
{
	int flag = 0;

	if(st->end > st->start+2)
		flag = conv_num(st,& (st->stack->stack_data[st->start+2]));

	pc_resetskill(script_rid2sd(st), flag);
	return 0;
}

/*==========================================
 * 見た目の職業変更
 *------------------------------------------
 */
int buildin_changebase(struct script_state *st)
{
	struct map_session_data *sd;
	int job, upper = -1, vclass;

	job = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if( st->end>st->start+3 )
		upper = conv_num(st,& (st->stack->stack_data[st->start+3]));

	if( st->end>st->start+4 )
		sd=map_id2sd(conv_num(st,& (st->stack->stack_data[st->start+4])));
	else
		sd=script_rid2sd(st);

	if(sd == NULL)
		return 0;

	if(upper < 0)
		upper = sd->s_class.upper;

	vclass = pc_calc_class_job(job, upper);

	if(vclass == PC_CLASS_WE && !battle_config.wedding_modifydisplay)
		return 0;

	//if(vclass == PC_CLASS_WE || vclass == PC_CLASS_ST || vclass == PC_CLASS_SU)
	//	pc_unequipitem(sd,sd->equip_index[EQUIP_INDEX_RARM],1);	// 装備外し

	sd->view_class = vclass;
	clif_changelook(&sd->bl, LOOK_BASE, vclass);
#if PACKETVER > 20080102
	clif_skillinfoblock(sd);
#endif
	return 0;
}

/*==========================================
 * 性別変換
 *------------------------------------------
 */
int buildin_changesex(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);

	nullpo_retr(0, sd);

	if(sd->sex==SEX_FEMALE){
		sd->sex=SEX_MALE;
		if(sd->s_class.job == PC_JOB_DC || sd->s_class.job == PC_JOB_WA || sd->s_class.job == PC_JOB_OB)
			sd->status.class_ -= 1;
	} else {
		sd->sex=SEX_FEMALE;
		if(sd->s_class.job == PC_JOB_BA || sd->s_class.job == PC_JOB_MI || sd->s_class.job == PC_JOB_KG)
			sd->status.class_ += 1;
	}
	chrif_changesex(sd->status.account_id,sd->sex);
	chrif_save(sd,0);
	return 0;
}

/*==========================================
 * サーバー上の全員を全回復(蘇生+HP/SP全回復)
 *------------------------------------------
 */
int buildin_recovery(struct script_state *st)
{
	struct map_session_data *sd;
	int i;

	for(i=0; i<fd_max; i++) {
		if(session[i] && (sd = (struct map_session_data *)session[i]->session_data) && sd->state.auth) {
			sd->status.hp = sd->status.max_hp;
			sd->status.sp = sd->status.max_sp;
			clif_updatestatus(sd, SP_HP);
			clif_updatestatus(sd, SP_SP);
			if(unit_isdead(&sd->bl)) {
				pc_setstand(sd);
				clif_resurrection(&sd->bl, 1);
			}
		}
	}
	return 0;
}

/*==========================================
 * Checkcart [Valaris]
 *------------------------------------------
 */
int buildin_checkcart(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);

	push_val(st->stack,C_INT,(pc_iscarton(sd)) ? 1 : 0);

	return 0;
}

/*==========================================
 * checkfalcon [Valaris]
 *------------------------------------------
 */
int buildin_checkfalcon(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);

	push_val(st->stack,C_INT,(pc_isfalcon(sd)) ? 1 : 0);

	return 0;
}

/*==========================================
 * Checkriding [Valaris]
 *------------------------------------------
 */
int buildin_checkriding(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);

	push_val(st->stack,C_INT,(pc_isriding(sd)) ? 1 : 0);

	return 0;
}

/*==========================================
 * ドラゴンに騎乗しているかどうか
 *------------------------------------------
 */
int buildin_checkdragon(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);

	push_val(st->stack,C_INT,(pc_isdragon(sd)) ? 1 : 0);

	return 0;
}

/*==========================================
 * 魔導ギアに騎乗しているかどうか
 *------------------------------------------
 */
int buildin_checkgear(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);

	push_val(st->stack,C_INT,(pc_isgear(sd)) ? 1 : 0);

	return 0;
}

/*==========================================
 * ウォーグを召喚または騎乗しているかどうか
 *------------------------------------------
 */
int buildin_checkwolf(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int type = 0, val = 0;

	if(st->end > st->start+2)
		type = conv_num(st,& (st->stack->stack_data[st->start+2]));

	switch(type) {
	case 1:		// 召喚のみチェック
		val = pc_iswolf(sd)? 1 : 0;
		break;
	case 2:		// 騎乗のみチェック
		val = pc_iswolfmount(sd)? 1 : 0;
		break;
	default:	// 両方チェック
		val = (pc_iswolf(sd) || pc_iswolfmount(sd))? 1 : 0;
		break;
	}

	push_val(st->stack,C_INT,val);

	return 0;
}

/*==========================================
 * 座っているかどうか
 *------------------------------------------
 */
int buildin_checksit(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);

	push_val(st->stack,C_INT,(pc_issit(sd)) ? 1 : 0);

	return 0;
}

/*==========================================
 * 死亡しているかどうか
 *------------------------------------------
 */
int buildin_checkdead(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);

	push_val(st->stack,C_INT,(sd && unit_isdead(&sd->bl)) ? 1 : 0);

	return 0;
}

/*==========================================
 * 詠唱しているかどうか
 *------------------------------------------
 */
int buildin_checkcasting(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);

	push_val(st->stack,C_INT,(sd && sd->ud.skilltimer != -1) ? 1 : 0);

	return 0;
}

/*==========================================
 * ステータス再計算
 *------------------------------------------
 */
int buildin_recalcstatus(struct script_state *st)
{
	struct map_session_data *sd;

	if( st->end>st->start+2 )
		sd = map_id2sd(conv_num(st,& (st->stack->stack_data[st->start+2])));
	else
		sd = script_rid2sd(st);

	if(sd)
		status_calc_pc(sd,0);
	return 0;
}

/*==========================================
 * 状態異常中のパラメーターを返す
 *------------------------------------------
 */
int buildin_sc_onparam(struct script_state *st)
{
	struct block_list *bl = map_id2bl(st->rid);
	int type,num;

	type = conv_num(st,& (st->stack->stack_data[st->start+2]));
	num  = conv_num(st,& (st->stack->stack_data[st->start+3]));

	if(type < 0 || type >= MAX_STATUSCHANGE) {
		printf("buildin_sc_onparam: invaild type %d\n", type);
		push_val(st->stack,C_INT,0);
		return 0;
	}

	if(bl && bl->type == BL_PC) {
		struct map_session_data *sd = (struct map_session_data *)bl;
		if(sd && sd->state.potionpitcher_flag)
			bl = map_id2bl(sd->ud.skilltarget);
	}
	if(bl) {
		struct status_change *sc = status_get_sc(bl);
		if(sc && sc->data[type].timer != -1) {
			switch(num) {
			case 1:
				push_val(st->stack,C_INT,sc->data[type].val1);
				break;
			case 2:
				push_val(st->stack,C_INT,sc->data[type].val2);
				break;
			case 3:
				push_val(st->stack,C_INT,sc->data[type].val3);
				break;
			case 4:
				push_val(st->stack,C_INT,sc->data[type].val4);
				break;
			default:
				{
					struct TimerData *td = get_timer(sc->data[type].timer);

					if(td == NULL || td->func != status_change_timer || DIFF_TICK(td->tick,gettick()) < 0)
						push_val(st->stack,C_INT,0);
					else
						push_val(st->stack,C_INT,DIFF_TICK(td->tick,gettick()));
				}
				break;
			}
			return 0;
		}
	}
	push_val(st->stack,C_INT,0);
	return 0;
}
