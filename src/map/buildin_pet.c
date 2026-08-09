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
#include <time.h>

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
#include "script.h"
#include "script_internal.h"
#include "pet.h"
#include "homun.h"
#include "merc.h"
#include "mob.h"
#include "intif.h"
#include "status.h"
#include "unit.h"

/* Split from script.c (Issue #61) */

/*==========================================
 * NPCでペット作る
 *------------------------------------------
 */
int buildin_makepet(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	struct pet_db *db;
	int id;

	id = conv_num(st,& (st->stack->stack_data[st->start+2]));

	db = pet_search_data(id, PET_CLASS);

	if(!db)
		db = pet_search_data(id, PET_EGG);
	if(db && sd) {
		sd->catch_target_class = db->class_;
		intif_create_pet(
			sd->status.account_id, sd->status.char_id, db->class_, mobdb_search(db->class_)->lv,
			db->EggID, 0, db->intimate, 100, 0, 1, db->jname
		);
	}

	return 0;
}

/*==========================================
 * 捕獲アイテム使用
 *------------------------------------------
 */
int buildin_catchpet(struct script_state *st)
{
	int pet_id = conv_num(st,& (st->stack->stack_data[st->start+2]));

	pet_catch_process1(script_rid2sd(st),pet_id);
	return 0;
}

/*==========================================
 * 携帯卵孵化機使用
 *------------------------------------------
 */
int buildin_birthpet(struct script_state *st)
{
	clif_sendegg( script_rid2sd(st) );
	return 0;
}

/*==========================================
 * 孵化させて連れ歩いているペットの情報取得
 * 0:pet_id 1:pet_class 2:pet_name
 * 3:friendly 4:hungry
 *------------------------------------------
 */
int buildin_getpetinfo(struct script_state *st)
{
	struct map_session_data *sd=script_rid2sd(st);
	int type=conv_num(st,& (st->stack->stack_data[st->start+2]));

	if(sd && sd->status.pet_id){
		switch(type){
			case 0:
				push_val(st->stack,C_INT,sd->status.pet_id);
				break;
			case 1:
				if(sd->pet.class_)
					push_val(st->stack,C_INT,sd->pet.class_);
				else
					push_val(st->stack,C_INT,0);
				break;
			case 2:
				if(sd->pet.name[0])
					push_str(st->stack,C_STR,(unsigned char *)aStrdup(sd->pet.name));
				else
					push_str(st->stack,C_CONSTSTR,"");
				break;
			case 3:
				push_val(st->stack,C_INT,sd->pet.intimate);
				break;
			case 4:
				push_val(st->stack,C_INT,sd->pet.hungry);
				break;
			default:
				push_val(st->stack,C_INT,0);
				break;
		}
	}else{
		push_val(st->stack,C_INT,0);
	}
	return 0;
}

/*==========================================
 * 連れ歩いているホムンクルスの情報取得
 * 0:homun_id 1:homun_base_lv 2:homun_name
 * 3:friendly 4:hungry 5:homun_class
 *------------------------------------------
 */
int buildin_gethomuninfo(struct script_state *st)
{
	struct map_session_data *sd=script_rid2sd(st);
	int type=conv_num(st,& (st->stack->stack_data[st->start+2]));

	if(sd && sd->status.homun_id){
		switch(type){
			case 0:
				push_val(st->stack,C_INT,sd->status.homun_id);
				break;
			case 1:
				if(sd->hd && sd->hd->status.base_level)
					push_val(st->stack,C_INT,sd->hd->status.base_level);
				else
					push_val(st->stack,C_INT,0);
				break;
			case 2:
				if(sd->hd && sd->hd->status.name[0])
					push_str(st->stack,C_STR,(unsigned char *)aStrdup(sd->hd->status.name));
				else
					push_str(st->stack,C_CONSTSTR,"");
				break;
			case 3:
				if( sd->hd )
					push_val(st->stack,C_INT,sd->hd->intimate);
				else
					push_val(st->stack,C_INT,0);
				break;
			case 4:
				if( sd->hd )
					push_val(st->stack,C_INT,sd->hd->status.hungry);
				else
					push_val(st->stack,C_INT,0);
				break;
			case 5:
				if( sd->hd )
					push_val(st->stack,C_INT,sd->hd->status.class_);
				else
					push_val(st->stack,C_INT,0);
				break;
			default:
				push_val(st->stack,C_INT,0);
				break;
		}
	}else{
		push_val(st->stack,C_INT,0);
	}
	return 0;
}

/*==========================================
 * pet attack skills [Valaris] //Rewritten by [Skotlex]
 *------------------------------------------
 */
int buildin_petskillattack(struct script_state *st)
{
	struct pet_data *pd;
	struct map_session_data *sd = script_rid2sd(st);

	if(sd == NULL || sd->pd == NULL)
		return 0;

	pd = sd->pd;
	if(pd->a_skill == NULL)
		pd->a_skill = (struct pet_skill_attack *)aCalloc(1, sizeof(struct pet_skill_attack));

	pd->a_skill->id = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if(pd->a_skill->id == -1) {
		// remove pet skills
		aFree(pd->a_skill);
		pd->a_skill = NULL;
	} else {
		pd->a_skill->lv        = conv_num(st,& (st->stack->stack_data[st->start+3]));
		pd->a_skill->rate      = conv_num(st,& (st->stack->stack_data[st->start+4]));
		pd->a_skill->bonusrate = conv_num(st,& (st->stack->stack_data[st->start+5]));
		pd->a_skill->div_      = 0;
	}
	return 0;
}

/*==========================================
 * pet support skills [Skotlex]
 *------------------------------------------
 */
int buildin_petskillsupport(struct script_state *st)
{
	struct pet_data *pd;
	struct map_session_data *sd = script_rid2sd(st);

	if(sd == NULL || sd->pd == NULL)
		return 0;

	pd = sd->pd;
	if(pd->s_skill) {	// Clear previous skill
		if(pd->s_skill->timer != -1)
			delete_timer(pd->s_skill->timer, pet_skill_support_timer);
	} else {		// init memory
		pd->s_skill = (struct pet_skill_support *)aCalloc(1, sizeof(struct pet_skill_support));
	}

	pd->s_skill->id = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if(pd->s_skill->id == -1) {
		// remove pet skills
		aFree(pd->s_skill);
		pd->s_skill = NULL;
	} else {
		pd->s_skill->lv    = conv_num(st,& (st->stack->stack_data[st->start+3]));
		pd->s_skill->delay = conv_num(st,& (st->stack->stack_data[st->start+4]));
		pd->s_skill->hp    = conv_num(st,& (st->stack->stack_data[st->start+5]));
		pd->s_skill->sp    = conv_num(st,& (st->stack->stack_data[st->start+6]));

		pd->s_skill->timer = add_timer(gettick()+pd->s_skill->delay*1000, pet_skill_support_timer ,sd->bl.id, NULL);
	}
	return 0;
}

/*==========================================
 * ペットのルートタイプの変更
 *------------------------------------------
 */
int buildin_changepettype(struct script_state *st)
{
	struct map_session_data *sd;
	int type = conv_num(st,& (st->stack->stack_data[st->start+2]));

	sd = script_rid2sd(st);

	if(sd && sd->status.pet_id) {
		if(sd->pd) {
			if(type > 2 || type < 0)
				type = 0;
			sd->pd->loottype = (short)type;
		}
	}
	return 0;
}

/*==========================================
 * ホムンクルス削除
 *------------------------------------------
 */
int buildin_homundel(struct script_state *st)
{
	homun_delete_data( script_rid2sd(st) );
	return 0;
}

/*==========================================
 * ホムンクルスリネーム
 *------------------------------------------
 */
int buildin_homunrename(struct script_state *st)
{
	char *homname;
	int flag=0;
	struct map_session_data *sd = script_rid2sd(st);

	homname	= conv_str(st,& (st->stack->stack_data[st->start+2]));
	if( st->end > st->start+3 ){
		flag = conv_num(st,& (st->stack->stack_data[st->start+3]));
	}

	if(sd && sd->hd) {
		if(flag == 0 && sd->hd->status.rename_flag == 0) {
			// 変更前の状態に戻す
			flag = 1;
		}
		sd->hd->status.rename_flag = 0;
		homun_change_name(sd,homname);

		// 変更可能にする
		if(flag == 1)
			sd->hd->status.rename_flag = 0;
	}
	return 0;
}

/*==========================================
 * ホムンクルス進化
 *------------------------------------------
 */
int buildin_homunevolution(struct script_state *st)
{
	homun_change_class(script_rid2sd(st), -1);
	return 0;
}

/*==========================================
 * エンブリオ変異
 *------------------------------------------
 */
int buildin_morphembryo(struct script_state *st)
{
	homun_morphembryo(script_rid2sd(st));
	return 0;
}

/*==========================================
 * ホムンクルス変異
 *------------------------------------------
 */
int buildin_homunmutation(struct script_state *st)
{
	int id = conv_num(st,& (st->stack->stack_data[st->start+2]));

	homun_mutation(script_rid2sd(st), id);
	return 0;
}

/*==========================================
 * 傭兵作成
 *------------------------------------------
 */
int buildin_makemerc(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int merc_id;
	unsigned int limit;

	nullpo_retr(0, sd);

	merc_id = conv_num(st,& (st->stack->stack_data[st->start+2]));
	limit   = (unsigned int)conv_num(st,& (st->stack->stack_data[st->start+3]));

	merc_callmerc(sd,merc_id,limit);

	return 0;
}

/*==========================================
 * 傭兵を解雇する
 *------------------------------------------
 */
int buildin_delmerc(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);

	nullpo_retr(0, sd);

	merc_menu(sd,2);

	return 0;
}

/*==========================================
 * 連れ歩いている傭兵の情報取得
 * 0:merc_id 1:merc_class_lv 2:fame
 * 3:call_count 4:kill_count 5:lifetime
 *------------------------------------------
 */
int buildin_getmercinfo(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int type = conv_num(st,& (st->stack->stack_data[st->start+2]));

	if(sd && sd->status.merc_id > 0 && sd->mcd){
		switch(type){
			case 0:
				push_val(st->stack,C_INT,sd->status.merc_id);
				break;
			case 1:
				push_val(st->stack,C_INT,sd->mcd->status.class_);
				break;
			case 2:
				push_val(st->stack,C_INT,merc_get_fame(sd,sd->mcd->status.class_));
				break;
			case 3:
				push_val(st->stack,C_INT,merc_get_call(sd,sd->mcd->status.class_));
				break;
			case 4:
				push_val(st->stack,C_INT,sd->mcd->status.kill_count);
				break;
			case 5:
				{
					unsigned int diff;
					unsigned int now  = (unsigned int)time(NULL);
					if(sd->mcd->status.limit > now)
						diff = (sd->mcd->status.limit - now) * 1000;
					else
						diff = 1;
					push_val(st->stack,C_INT,diff);
				}
				break;
			default:
				push_val(st->stack,C_INT,0);
				break;
		}
	}
	else {
		push_val(st->stack,C_INT,0);
	}
	return 0;
}

/*==========================================
 * 傭兵回復
 *------------------------------------------
 */
int buildin_mercheal(struct script_state *st)
{
	int hp,sp;
	struct map_session_data *sd = script_rid2sd(st);

	nullpo_retr(0, sd);
	nullpo_retr(0, sd->mcd);

	hp = conv_num(st,& (st->stack->stack_data[st->start+2]));
	sp = conv_num(st,& (st->stack->stack_data[st->start+3]));

	merc_heal(sd->mcd,hp,sp);
	return 0;
}

/*==========================================
 * 傭兵状態変化
 *------------------------------------------
 */
int buildin_mercsc_start(struct script_state *st)
{
	int type, tick, val1;
	struct map_session_data *sd = script_rid2sd(st);

	nullpo_retr(0, sd);
	nullpo_retr(0, sd->mcd);

	type = conv_num(st,& (st->stack->stack_data[st->start+2]));
	tick = conv_num(st,& (st->stack->stack_data[st->start+3]));
	val1 = conv_num(st,& (st->stack->stack_data[st->start+4]));

	if(!unit_isdead(&sd->mcd->bl) && status_change_rate(&sd->mcd->bl,type,10000,0) > 0)
		status_change_start(&sd->mcd->bl,type,val1,0,0,0,tick,0);
	return 0;
}
