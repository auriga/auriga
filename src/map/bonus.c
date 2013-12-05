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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "timer.h"
#include "db.h"
#include "nullpo.h"
#include "malloc.h"
#include "utils.h"

#include "map.h"
#include "bonus.h"
#include "battle.h"
#include "status.h"
#include "itemdb.h"
#include "mob.h"
#include "clif.h"
#include "skill.h"
#include "pc.h"
#include "unit.h"

/*==========================================
 * オートスペル
 *------------------------------------------
 */
static int bonus_add_autospell(struct map_session_data* sd,int skillid,int skillid2,int skilllv,int rate, unsigned int flag)
{
	nullpo_retr(0, sd);

	if(!battle_config.allow_same_autospell) {
		int i;
		for(i=0; i<sd->autospell.count; i++) {
			if(sd->autospell.card_id[i] == current_equip_name_id &&
			   sd->autospell.skill[i] == skillid &&
			   sd->autospell.id[i] == skillid2 &&
			   sd->autospell.lv[i] == skilllv &&
			   sd->autospell.rate[i] == rate &&
			   sd->autospell.flag[i] == flag)
				return 0;
		}
	}

	// 一杯
	if(sd->autospell.count == MAX_BONUS_AUTOSPELL)
		return 0;

	// 後ろに追加
	sd->autospell.skill[sd->autospell.count]   = skillid;
	sd->autospell.id[sd->autospell.count]      = skillid2;
	sd->autospell.lv[sd->autospell.count]      = skilllv;
	sd->autospell.rate[sd->autospell.count]    = rate;
	sd->autospell.flag[sd->autospell.count]    = flag;
	sd->autospell.card_id[sd->autospell.count] = current_equip_name_id;
	sd->autospell.count++;

	return 0;
}

/*==========================================
 * アイテムボーナスオートスペル
 *  mode : 攻撃時1 反撃2
 *------------------------------------------
 */
static int bonus_use_autospell(struct map_session_data *sd,struct block_list *bl,int skillid,int skilllv,int rate,unsigned int asflag,unsigned int tick,int flag)
{
	struct block_list *target;
	int f=0,sp=0;

	nullpo_retr(0, sd);
	nullpo_retr(0, bl);

	// オートスペルが使えない状態異常中
	// ロキ内で、ロキ内アイテム オートスペルが許可されていない
	if(!battle_config.roki_item_autospell && sd->sc.data[SC_ROKISWEIL].timer != -1)
		return 0;

	// いつの間にか自分もしくは攻撃対象が死んでいた
	if(unit_isdead(&sd->bl) || unit_isdead(bl))
		return 0;

	// 発動判定
	if(skillid <= 0 || skilllv <= 0)
		return 0;

	// 遠距離物理半減
	if(asflag&EAS_LONG) {
		if(atn_rand()%10000 > (rate/2))
			return 0;
	} else {
		if(atn_rand()%10000 > rate)
			return 0;
	}

	// スペル対象
	// 指定あるがいらないな
	//if(asflag&EAS_TARGET)
	//	target = bl;	// 相手
	//else
	if(asflag&EAS_SELF)
		target = &sd->bl;	// 自分
	else if(asflag&EAS_TARGET_RAND && atn_rand()%100 < 50)
		target = &sd->bl;	// 自分
	else
		target = bl;		// 相手

	// レベル調整
	if(asflag & (EAS_USEMAX | EAS_USEBETTER)) {
		int lv;
		if(battle_config.allow_cloneskill_at_autospell)
			lv = pc_checkskill(sd,skillid);
		else
			lv = pc_checkskill2(sd,skillid);

		if(asflag&EAS_USEMAX && lv && lv == pc_get_skilltree_max(&sd->s_class,skillid)) {
			// Maxがある場合のみ
			skilllv = lv;
		} else if(asflag&EAS_USEBETTER && lv > skilllv) {
			// 現状以上のレベルがある場合のみ
			skilllv = lv;
		}
	}

	// レベルの変動
	if(asflag&EAS_FLUCT) {	// レベル変動 武器ＡＳ用
		int j = atn_rand()%100;
		if (j >= 50) skilllv -= 2;
		else if(j >= 15) skilllv--;
		if(skilllv < 1) skilllv = 1;
	} else if(asflag&EAS_RANDOM && skilllv > 0) {	// 1〜指定までのランダム
		skilllv = atn_rand()%skilllv+1;
	}

	// SP消費
	sp = skill_get_sp(skillid,skilllv);
	if(asflag&EAS_NOSP)
		sp = 0;
	else if(asflag&EAS_SPCOST1)
		sp = sp*2/3;
	else if(asflag&EAS_SPCOST2)
		sp = sp/2;
	else if(asflag&EAS_SPCOST3)
		sp = sp*3/2;

	// SPが足りない！
	if(sd->status.sp < sp)
		return 0;

	if(battle_config.bonus_autospell_delay_enable) {
		int delay = skill_delayfix(&sd->bl, skillid, skilllv);
		sd->ud.canact_tick = tick + delay;
	}

	// 実行
	if(skillid == AL_TELEPORT && skilllv == 1) {	// Lv1テレポはダイアログ表示なしで即座に飛ばす
		f = pc_randomwarp(sd,3);
	} else if(skill_get_inf(skillid) & INF_GROUND) {	// 場所
		f = skill_castend_pos2(&sd->bl,target->x,target->y,skillid,skilllv,tick,flag);
	} else {
		switch( skill_get_nk(skillid)&3 ) {
			case 0:	// 通常
			case 2:	// 吹き飛ばし
				f = skill_castend_damage_id(&sd->bl,target,skillid,skilllv,tick,flag);
				break;
			case 1:	// 支援系
				if( (skillid == AL_HEAL || (skillid == ALL_RESURRECTION && target->type != BL_PC)) &&
				    battle_check_undead(status_get_race(target),status_get_element(target)) )
					f = skill_castend_damage_id(&sd->bl,target,skillid,skilllv,tick,flag);
				else
					f = skill_castend_nodamage_id(&sd->bl,target,skillid,skilllv,tick,flag);
				break;
		}
	}
	if(!f)
		pc_heal(sd,0,-sp);

	/* スキル使用で発動するオートスペル,アクティブアイテム */
	bonus_skillautospell(&sd->bl,target,skillid,tick,0);
	bonus_activeitemskill_start(sd,skillid,tick);

	return 1;	// 成功
}

int bonus_autospell(struct block_list *src,struct block_list *bl,unsigned int mode,unsigned int tick,int flag)
{
	int i;
	static int lock = 0;
	struct map_session_data *sd = NULL;

	nullpo_retr(0, src);
	nullpo_retr(0, bl);

	if(src->type != BL_PC || lock++)
		return 0;

	nullpo_retr(0, sd = (struct map_session_data *)src);

	for(i=0;i<sd->autospell.count;i++)
	{
		// スキル使用時に発動するオートスペルは弾く
		if(sd->autospell.skill[i] != 0)
			continue;

		if(!(mode&EAS_SHORT) && !(mode&EAS_LONG) && !(mode&EAS_MAGIC) && !(mode&EAS_MISC))
			mode += EAS_SHORT|EAS_LONG;
		if(!(sd->autospell.flag[i]&EAS_SHORT) && !(sd->autospell.flag[i]&EAS_LONG) &&
		   !(sd->autospell.flag[i]&EAS_MAGIC) && !(sd->autospell.flag[i]&EAS_MISC))
			sd->autospell.flag[i] += EAS_SHORT|EAS_LONG;
		if(mode&EAS_SHORT && !(sd->autospell.flag[i]&EAS_SHORT))
			continue;
		if(mode&EAS_LONG && !(sd->autospell.flag[i]&EAS_LONG))
			continue;
		if(mode&EAS_MAGIC && !(sd->autospell.flag[i]&EAS_MAGIC))
			continue;
		if(mode&EAS_MISC && !(sd->autospell.flag[i]&EAS_MISC))
			continue;

		if(!(mode&EAS_ATTACK) && !(mode&EAS_REVENGE))
			mode += EAS_ATTACK;
		if(!(sd->autospell.flag[i]&EAS_ATTACK) && !(sd->autospell.flag[i]&EAS_REVENGE))
			sd->autospell.flag[i] += EAS_ATTACK;
		if(mode&EAS_REVENGE && !(sd->autospell.flag[i]&EAS_REVENGE))
			continue;
		if(mode&EAS_ATTACK && sd->autospell.flag[i]&EAS_REVENGE)
			continue;

		if(!(mode&EAS_NORMAL) && !(mode&EAS_SKILL))
			mode += EAS_NORMAL;
		if(!(sd->autospell.flag[i]&EAS_NORMAL) && !(sd->autospell.flag[i]&EAS_SKILL))
			sd->autospell.flag[i] += EAS_NORMAL;
		if(mode&EAS_NORMAL && !(sd->autospell.flag[i]&EAS_NORMAL))
			continue;
		if(mode&EAS_SKILL && !(sd->autospell.flag[i]&EAS_SKILL))
			continue;

		if(bonus_use_autospell(
			sd,bl,sd->autospell.id[i],sd->autospell.lv[i],
			sd->autospell.rate[i],sd->autospell.flag[i],tick,flag) )
		{
			// オートスペルはどれか一度しか発動しない
			if(battle_config.once_autospell)
				break;
		}
	}
	lock = 0;

	return 1;
}

int bonus_skillautospell(struct block_list *src,struct block_list *bl,int skillid,unsigned int tick,int flag)
{
	int i;
	struct map_session_data *sd = NULL;

	nullpo_retr(0, src);
	nullpo_retr(0, bl);

	if(src->type != BL_PC)
		return 0;

	nullpo_retr(0, sd = (struct map_session_data *)src);

	for(i=0;i<sd->autospell.count;i++)
	{
		// スキルで発動するオートスペルのチェック
		if(sd->autospell.skill[i] != skillid)
			continue;

		if(bonus_use_autospell(
			sd,bl,sd->autospell.id[i],sd->autospell.lv[i],
			sd->autospell.rate[i],sd->autospell.flag[i],tick,flag) )
		{
			// オートスペルはどれか一度しか発動しない
			if(battle_config.once_autospell)
				break;
		}
	}

	return 1;
}

/*==========================================
 * アクティブアイテム登録
 *------------------------------------------
 */
int bonus_activeitem(struct map_session_data* sd,int skillid,int id,short rate,unsigned int tick,unsigned int flag)
{
	nullpo_retr(0, sd);

	// 一杯
	if(sd->activeitem.count >= MAX_ACTIVEITEM)
		return 0;

	// 同じIDが登録されているか
	if(!battle_config.allow_same_activeitem) {
		int i;
		for(i = 0; i < sd->activeitem.count; i++) {
			if(sd->activeitem.id[i] == id && sd->activeitem.skill[i] == skillid)
				return 0;
		}
	}

	// 後ろに追加
	sd->activeitem.skill[sd->activeitem.count] = skillid;
	sd->activeitem.id[sd->activeitem.count]    = id;
	sd->activeitem.rate[sd->activeitem.count]  = rate;
	sd->activeitem.tick[sd->activeitem.count]  = tick;
	sd->activeitem.flag[sd->activeitem.count]  = flag;
	sd->activeitem.count++;

	return 1;
}

/*==========================================
 * アクティブアイテムタイマー
 *------------------------------------------
 */
static int bonus_activeitem_timer(int tid,unsigned int tick,int id,void *data)
{
	struct map_session_data *sd = map_id2sd(id);
	int i;

	if(sd == NULL)
		return 0;

	for(i = 0; i < MAX_ACTIVEITEM; i++) {
		if(sd->activeitem_timer[i] == tid) {
			if(sd->sc.data[SC_ACTIVE_MONSTER_TRANSFORM].timer != -1 &&
			   sd->sc.data[SC_ACTIVE_MONSTER_TRANSFORM].val2 == sd->activeitem_id2[i])	// アクティブモンスター変身
				status_change_end(&sd->bl, SC_ACTIVE_MONSTER_TRANSFORM, -1);
			sd->activeitem_timer[i] = -1;
			sd->activeitem_id2[i] = 0;
			status_calc_pc(sd,0);
			return 1;
		}
	}

	return 0;
}

/*==========================================
 * アクティブアイテム開始
 *------------------------------------------
 */
int bonus_activeitem_start(struct map_session_data* sd,unsigned int mode,unsigned int tick)
{
	int i, flag = 0;
	static int lock = 0;

	nullpo_retr(0, sd);

	if(lock++)
		return 0;

	for(i=0;i<sd->activeitem.count;i++)
	{
		// スキル使用時に発動するアクティブアイテムは弾く
		if(sd->activeitem.skill[i] != 0)
			continue;

		if(!(mode&EAS_SHORT) && !(mode&EAS_LONG) && !(mode&EAS_MAGIC) && !(mode&EAS_MISC))
			mode |= EAS_SHORT|EAS_LONG;
		if(!(sd->activeitem.flag[i]&EAS_SHORT) && !(sd->activeitem.flag[i]&EAS_LONG) &&
		   !(sd->activeitem.flag[i]&EAS_MAGIC) && !(sd->activeitem.flag[i]&EAS_MISC))
			sd->activeitem.flag[i] |= EAS_SHORT|EAS_LONG;
		if(mode&EAS_SHORT && !(sd->activeitem.flag[i]&EAS_SHORT))
			continue;
		if(mode&EAS_LONG && !(sd->activeitem.flag[i]&EAS_LONG))
			continue;
		if(mode&EAS_MAGIC && !(sd->activeitem.flag[i]&EAS_MAGIC))
			continue;
		if(mode&EAS_MISC && !(sd->activeitem.flag[i]&EAS_MISC))
			continue;

		if(!(mode&EAS_ATTACK) && !(mode&EAS_REVENGE))
			mode |= EAS_ATTACK;
		if(!(sd->activeitem.flag[i]&EAS_ATTACK) && !(sd->activeitem.flag[i]&EAS_REVENGE))
			sd->activeitem.flag[i] |= EAS_ATTACK;
		if(mode&EAS_REVENGE && !(sd->activeitem.flag[i]&EAS_REVENGE))
			continue;
		if(mode&EAS_ATTACK && sd->activeitem.flag[i]&EAS_REVENGE)
			continue;

		if(!(mode&EAS_NORMAL) && !(mode&EAS_SKILL))
			mode |= EAS_NORMAL;
		if(!(sd->activeitem.flag[i]&EAS_NORMAL) && !(sd->activeitem.flag[i]&EAS_SKILL))
			sd->activeitem.flag[i] |= EAS_NORMAL;
		if(mode&EAS_NORMAL && !(sd->activeitem.flag[i]&EAS_NORMAL))
			continue;
		if(mode&EAS_SKILL && !(sd->activeitem.flag[i]&EAS_SKILL))
			continue;

		if(atn_rand()%10000 > sd->activeitem.rate[i])
			continue;

		// 既に発動中の場合は時間を上書き
		if(sd->activeitem_timer[i] != -1) {
			sd->activeitem_timer[i] = add_timer(tick + sd->activeitem.tick[i], bonus_activeitem_timer, sd->bl.id, NULL);
		// 発動
		} else {
			sd->activeitem_id2[i]   = sd->activeitem.id[i];
			sd->activeitem_timer[i] = add_timer(tick + sd->activeitem.tick[i], bonus_activeitem_timer, sd->bl.id, NULL);
			flag = 1;
		}
	}
	if(flag)
		status_calc_pc(sd,0);
	lock = 0;

	return 1;
}

/*==========================================
 * スキル使用で発動するアクティブアイテムの開始
 *------------------------------------------
 */
int bonus_activeitemskill_start(struct map_session_data* sd,int skillid,unsigned int tick)
{
	int i, flag = 0;
	static int lock = 0;

	nullpo_retr(0, sd);

	if(lock++)
		return 0;

	for(i=0;i<sd->activeitem.count;i++)
	{
		// スキルで発動するオートスペルのチェック
		if(sd->activeitem.skill[i] != skillid)
			continue;

		if(atn_rand()%10000 > sd->activeitem.rate[i])
			continue;

		// 既に発動中の場合は時間を上書き
		if(sd->activeitem_timer[i] != -1) {
			sd->activeitem_timer[i] = add_timer(tick + sd->activeitem.tick[i], bonus_activeitem_timer, sd->bl.id, NULL);
		// 発動
		} else {
			sd->activeitem_id2[i]   = sd->activeitem.id[i];
			sd->activeitem_timer[i] = add_timer(tick + sd->activeitem.tick[i], bonus_activeitem_timer, sd->bl.id, NULL);
			flag = 1;
		}
	}
	if(flag)
		status_calc_pc(sd,0);
	lock = 0;

	return 1;
}

/*==========================================
 * 装備品による能力等のボーナス設定１
 *------------------------------------------
 */
int bonus_param1(struct map_session_data *sd,int type,int val)
{
	nullpo_retr(0, sd);

	switch(type) {
	case SP_STR:
	case SP_AGI:
	case SP_VIT:
	case SP_INT:
	case SP_DEX:
	case SP_LUK:
		if(sd->state.lr_flag != 2)
			sd->parame[type-SP_STR] += val;
		break;
	case SP_ATK1:
		if(!sd->state.lr_flag)
			sd->watk += val;
		else if(sd->state.lr_flag == 1)
			sd->watk_ += val;
		break;
	case SP_ATK2:
		if(!sd->state.lr_flag)
			sd->watk2 += val;
		else if(sd->state.lr_flag == 1)
			sd->watk_2 += val;
		break;
	case SP_BASE_ATK:
		if(sd->state.lr_flag != 2)
#ifdef PRE_RENEWAL
			sd->base_atk += val;
#else
			sd->plus_atk += val;
#endif
		break;
	case SP_MATK1:
		if(sd->state.lr_flag != 2)
			sd->matk1 += val;
		break;
	case SP_MATK2:
		if(sd->state.lr_flag != 2)
			sd->matk2 += val;
		break;
	case SP_MATK:
		if(sd->state.lr_flag != 2) {
#ifdef PRE_RENEWAL
			sd->matk1 += val;
			sd->matk2 += val;
#else
			sd->plus_matk += val;
#endif
		}
		break;
	case SP_DEF1:
		if(sd->state.lr_flag != 2)
			sd->def += val;
		break;
	case SP_MDEF1:
		if(sd->state.lr_flag != 2)
			sd->mdef += val;
		break;
	case SP_MDEF2:
		if(sd->state.lr_flag != 2)
			sd->mdef2 += val;
		break;
	case SP_HIT:
		if(sd->state.lr_flag != 2)
			sd->hit += val;
		else
			sd->arrow_hit += val;
		break;
	case SP_FLEE1:
		if(sd->state.lr_flag != 2)
			sd->flee += val;
		break;
	case SP_FLEE2:
		if(sd->state.lr_flag != 2)
			sd->flee2 += val*10;
		break;
	case SP_CRITICAL:
		if(sd->state.lr_flag != 2)
			sd->critical += val*10;
		else
			sd->arrow_cri += val*10;
		break;
	case SP_ATKELE:
		if(!sd->state.lr_flag)
			sd->atk_ele = val;
		else if(sd->state.lr_flag == 1)
			sd->atk_ele_ = val;
		else if(sd->state.lr_flag == 2)
			sd->arrow_ele = val;
		break;
	case SP_DEFELE:
		if(sd->state.lr_flag != 2)
			sd->def_ele = val;
		break;
	case SP_MAXHP:
		if(sd->state.lr_flag != 2)
			sd->status.max_hp += val;
		break;
	case SP_MAXSP:
		if(sd->state.lr_flag != 2)
			sd->status.max_sp += val;
		break;
	case SP_CASTRATE:
		if(sd->state.lr_flag != 2)
			sd->castrate += val;
		break;
	case SP_MAXHPRATE:
		if(sd->state.lr_flag != 2)
			sd->hprate += val;
		break;
	case SP_MAXSPRATE:
		if(sd->state.lr_flag != 2)
			sd->sprate += val;
		break;
	case SP_SPRATE:
		if(sd->state.lr_flag != 2)
			sd->dsprate += val;
		break;
	case SP_ATTACKRANGE:
		if(!sd->state.lr_flag)
			sd->range.attackrange += val;
		else if(sd->state.lr_flag == 1)
			sd->range.attackrange_ += val;
		else if(sd->state.lr_flag == 2)
			sd->arrow_range += val;
		break;
	case SP_ATTACKRANGE_RATE:
		if(!sd->state.lr_flag)
			sd->range.attackrange = sd->range.attackrange * val / 100;
		else if(sd->state.lr_flag == 1)
			sd->range.attackrange_ = sd->range.attackrange_ * val / 100;
		else if(sd->state.lr_flag == 2)
			sd->arrow_range = sd->arrow_range * val / 100;
		break;
	case SP_ATTACKRANGE2:
		sd->range.add_attackrange += val;
		break;
	case SP_ATTACKRANGE_RATE2:
		sd->range.add_attackrange_rate = (sd->range.add_attackrange_rate * val)/100;
		break;
	case SP_ADD_SPEED:
		if(sd->state.lr_flag != 2)
			sd->speed -= val*10;
		break;
	case SP_SPEED_RATE:
		if(sd->state.lr_flag != 2) {
			if(sd->speed_rate < val) {
				sd->speed_rate = val;
				//clif_status_load_id(sd,SI_MOVHASTE_INFINITY,1);
			}
		}
		break;
	case SP_SPEED_ADDRATE:
		if(sd->state.lr_flag != 2)
			sd->speed_add_rate += val;
		break;
	case SP_ASPD:
		if(sd->state.lr_flag != 2)
			sd->aspd_add -= val*10;
		break;
	case SP_ASPD_RATE:
		if(sd->state.lr_flag != 2) {
			if(sd->aspd_rate < val)
				sd->aspd_rate = val;
		}
		break;
	case SP_ASPD_ADDRATE:
		if(sd->state.lr_flag != 2)
			sd->aspd_add_rate += val;
		break;
	case SP_HP_RECOV_RATE:
		if(sd->state.lr_flag != 2)
			sd->hprecov_rate += val;
		break;
	case SP_SP_RECOV_RATE:
		if(sd->state.lr_flag != 2)
			sd->sprecov_rate += val;
		break;
	case SP_CRITICAL_DEF:
		if(sd->state.lr_flag != 2)
			sd->critical_def += val;
		break;
	case SP_NEAR_ATK_DEF:
		if(sd->state.lr_flag != 2)
			sd->near_attack_def_rate += val;
		break;
	case SP_LONG_ATK_DEF:
		if(sd->state.lr_flag != 2)
			sd->long_attack_def_rate += val;
		break;
	case SP_DOUBLE_RATE:
		if(sd->state.lr_flag != 2 && sd->double_rate < val)
			sd->double_rate = val;
		break;
	case SP_DOUBLE_ADD_RATE:
		if(sd->state.lr_flag != 2)
			sd->double_add_rate += val;
		break;
	case SP_MATK_RATE:
		if(sd->state.lr_flag != 2)
			sd->matk_rate += val;
		break;
	case SP_ATK_RATE:
		if(sd->state.lr_flag != 2)
			sd->atk_rate += val;
		break;
	case SP_MAGIC_ATK_DEF:
		if(sd->state.lr_flag != 2)
			sd->magic_def_rate += val;
		break;
	case SP_MISC_ATK_DEF:
		if(sd->state.lr_flag != 2)
			sd->misc_def_rate += val;
		break;
	case SP_PERFECT_HIT_RATE:
		if(sd->state.lr_flag != 2 && sd->perfect_hit < val)
			sd->perfect_hit = val;
		break;
	case SP_PERFECT_HIT_ADD_RATE:
		if(sd->state.lr_flag != 2)
			sd->perfect_hit_add += val;
		break;
	case SP_CRITICAL_RATE:
		if(sd->state.lr_flag != 2)
			sd->critical_rate += val;
		break;
	case SP_GET_ZENY_NUM:
		if(sd->state.lr_flag != 2 && sd->get_zeny_num < val)
			sd->get_zeny_num = val;
		break;
	case SP_ADD_GET_ZENY_NUM:
		if(sd->state.lr_flag != 2)
			sd->get_zeny_add_num += val;
		break;
	case SP_GET_ZENY_NUM2:
		if(sd->state.lr_flag != 2 && sd->get_zeny_num2 < val)
			sd->get_zeny_num2 = val;
		break;
	case SP_ADD_GET_ZENY_NUM2:
		if(sd->state.lr_flag != 2)
			sd->get_zeny_add_num2 += val;
		break;
	case SP_DEF_RATIO_ATK_ELE:
		if(!sd->state.lr_flag)
			sd->def_ratio_atk_ele |= 1<<val;
		else if(sd->state.lr_flag == 1)
			sd->def_ratio_atk_ele_ |= 1<<val;
		break;
	case SP_DEF_RATIO_ATK_RACE:
		if(!sd->state.lr_flag)
			sd->def_ratio_atk_race |= 1<<val;
		else if(sd->state.lr_flag == 1)
			sd->def_ratio_atk_race_ |= 1<<val;
		break;
	case SP_DEF_RATIO_ATK_ENEMY:
		if(!sd->state.lr_flag)
			sd->def_ratio_atk_enemy |= 1<<val;
		else if(sd->state.lr_flag == 1)
			sd->def_ratio_atk_enemy_ |= 1<<val;
		break;
	case SP_HIT_RATE:
		if(sd->state.lr_flag != 2)
			sd->hit_rate += val;
		break;
	case SP_FLEE_RATE:
		if(sd->state.lr_flag != 2)
			sd->flee_rate += val;
		break;
	case SP_FLEE2_RATE:
		if(sd->state.lr_flag != 2)
			sd->flee2_rate += val;
		break;
	case SP_DEF_RATE:
		if(sd->state.lr_flag != 2)
			sd->def_rate += val;
		break;
	case SP_DEF2_RATE:
		if(sd->state.lr_flag != 2)
			sd->def2_rate += val;
		break;
	case SP_MDEF_RATE:
		if(sd->state.lr_flag != 2)
			sd->mdef_rate += val;
		break;
	case SP_MDEF2_RATE:
		if(sd->state.lr_flag != 2)
			sd->mdef2_rate += val;
		break;
	case SP_RESTART_FULL_RECORVER:
		if(sd->state.lr_flag != 2)
			sd->special_state.restart_full_recover = 1;
		break;
	case SP_NO_CASTCANCEL:
		if(sd->state.lr_flag != 2)
			sd->special_state.no_castcancel = 1;
		break;
	case SP_NO_CASTCANCEL2:
		if(sd->state.lr_flag != 2)
			sd->special_state.no_castcancel2 = 1;
		break;
	case SP_NO_SIZEFIX:
		if(sd->state.lr_flag != 2)
			sd->special_state.no_sizefix = 1;
		break;
	case SP_NO_MAGIC_DAMAGE:
		if(sd->state.lr_flag != 2)
			sd->special_state.no_magic_damage = 1;
		break;
	case SP_NO_WEAPON_DAMAGE:
		if(sd->state.lr_flag != 2)
			sd->special_state.no_weapon_damage = 1;
		break;
	case SP_NO_GEMSTONE:
		if(sd->state.lr_flag != 2)
			sd->special_state.no_gemstone = 1;
		break;
	case SP_INFINITE_ENDURE:
		if(sd->state.lr_flag != 2) {
			sd->special_state.infinite_endure = 1;
			clif_status_load_id(sd, SI_ENDURE, 1);
		}
		break;
	case SP_UNBREAKABLE_WEAPON:
		if(sd->state.lr_flag != 2)
			sd->unbreakable_equip |= LOC_RARM;
		break;
	case SP_UNBREAKABLE_ARMOR:
		if(sd->state.lr_flag != 2)
			sd->unbreakable_equip |= LOC_BODY;
		break;
	case SP_UNBREAKABLE_HELM:
		if(sd->state.lr_flag != 2)
			sd->unbreakable_equip |= LOC_HEAD2;
		break;
	case SP_UNBREAKABLE_SHIELD:
		if(sd->state.lr_flag != 2)
			sd->unbreakable_equip |= LOC_LARM;
		break;
	case SP_SP_GAIN_VALUE:
		if(!sd->state.lr_flag)
			sd->sp_gain_value += val;
		break;
	case SP_HP_GAIN_VALUE:
		if(!sd->state.lr_flag)
			sd->hp_gain_value += val;
		break;
	case SP_SPLASH_RANGE:
		if(sd->state.lr_flag != 2 && sd->splash_range < val)
			sd->splash_range = val;
		break;
	case SP_SPLASH_ADD_RANGE:
		if(sd->state.lr_flag != 2)
			sd->splash_add_range += val;
		break;
	case SP_SHORT_WEAPON_DAMAGE_RETURN:
		if(sd->state.lr_flag != 2)
			sd->short_weapon_damage_return += val;
		break;
	case SP_LONG_WEAPON_DAMAGE_RETURN:
		if(sd->state.lr_flag != 2)
			sd->long_weapon_damage_return += val;
		break;
	case SP_BREAK_WEAPON_RATE:
		if(sd->state.lr_flag != 2)
			sd->break_weapon_rate += val;
		break;
	case SP_BREAK_ARMOR_RATE:
		if(sd->state.lr_flag != 2)
			sd->break_armor_rate += val;
		break;
	case SP_ADD_STEAL_RATE:
		if(sd->state.lr_flag != 2)
			sd->add_steal_rate += val;
		break;
	case SP_CRITICAL_DAMAGE:
		if(sd->state.lr_flag != 2)
			sd->critical_damage += val;
		break;
	case SP_HP_RECOV_STOP:
		if(sd->state.lr_flag != 2)
			sd->hp_recov_stop = 1;
		break;
	case SP_SP_RECOV_STOP:
		if(sd->state.lr_flag != 2)
			sd->sp_recov_stop = 1;
		break;
	case SP_BONUS_DAMAGE:
		if(sd->state.lr_flag != 2)
			sd->bonus_damage += val;
		break;
	case SP_HP_PENALTY_UNRIG:
		if(sd->state.lr_flag != 2)
			sd->hp_penalty_unrig_value[current_equip_item_index] += val;
		break;
	case SP_SP_PENALTY_UNRIG:
		if(sd->state.lr_flag != 2)
			sd->sp_penalty_unrig_value[current_equip_item_index] += val;
		break;
	case SP_HP_RATE_PENALTY_UNRIG:
		if(sd->state.lr_flag != 2)
			sd->hp_rate_penalty_unrig[current_equip_item_index] += val;
		break;
	case SP_SP_RATE_PENALTY_UNRIG:
		if(sd->state.lr_flag != 2)
			sd->sp_rate_penalty_unrig[current_equip_item_index] += val;
		break;
	case SP_MOB_CLASS_CHANGE:
		sd->mob_class_change_rate += val;
		break;
	case SP_CURSE_BY_MURAMASA:
		if(sd->state.lr_flag != 2)
			sd->curse_by_muramasa += val;
		break;
	case SP_LOSS_EQUIP_WHEN_DIE:
		if(sd->state.lr_flag != 2) {
			sd->loss_equip_rate_when_die[current_equip_item_index] += val;
			sd->loss_equip_flag |= 0x0001;
		}
		break;
	case SP_LOSS_EQUIP_WHEN_ATTACK:
		if(sd->state.lr_flag != 2) {
			sd->loss_equip_rate_when_attack[current_equip_item_index] += val;
			sd->loss_equip_flag |= 0x0010;
		}
		break;
	case SP_LOSS_EQUIP_WHEN_HIT:
		if(sd->state.lr_flag != 2) {
			sd->loss_equip_rate_when_hit[current_equip_item_index] += val;
			sd->loss_equip_flag |= 0x0020;
		}
		break;
	case SP_BREAK_MYEQUIP_WHEN_ATTACK:
		if(sd->state.lr_flag != 2) {
			sd->break_myequip_rate_when_attack[current_equip_item_index] += val;
			sd->loss_equip_flag |= 0x0100;
		}
		break;
	case SP_BREAK_MYEQUIP_WHEN_HIT:
		if(sd->state.lr_flag != 2) {
			sd->break_myequip_rate_when_hit[current_equip_item_index] += val;
			sd->loss_equip_flag |= 0x1000;
		}
		break;
	case SP_MAGIC_DAMAGE_RETURN:
		if(sd->state.lr_flag != 2)
			sd->magic_damage_return += val;
		break;
	case SP_ADD_SHORT_WEAPON_DAMAGE:
		if(sd->state.lr_flag != 2)
			sd->short_weapon_damege_rate += val;
		break;
	case SP_ADD_LONG_WEAPON_DAMAGE:
		if(sd->state.lr_flag != 2)
			sd->long_weapon_damege_rate += val;
		break;
	case SP_RACE:
		if(val >= 0 && val < RCT_ALL) {
			sd->race = val;
		}
		break;
	case SP_TIGEREYE:
		sd->special_state.infinite_tigereye = 1;
		clif_status_load_id(sd, SI_TIGEREYE, 1);
		break;
	case SP_AUTO_STATUS_CALC_PC:
		if(val >= 0 && val < MAX_STATUSCHANGE)
			sd->auto_status_calc_pc[val] = 1;
		break;
	case SP_ITEM_NO_USE:
		sd->special_state.item_no_use = 1;
		break;
	case SP_FIX_DAMAGE:
		if(val >= 0) {
			sd->special_state.fix_damage = 1;
			sd->fix_damage = val;
		}
		break;
	case SP_SKILL_DELAY_RATE:
		sd->skill_delay_rate += val;
		break;
	case SP_NO_KNOCKBACK:
		sd->special_state.no_knockback = 1;
		break;
	case SP_FIX_MAXHP:
		sd->fix_status.max_hp = val;
		break;
	case SP_FIX_MAXSP:
		sd->fix_status.max_sp = val;
		break;
	case SP_FIX_BASEATK:
		sd->fix_status.atk = val;
		break;
	case SP_FIX_MATK:
		sd->fix_status.matk = val;
		break;
	case SP_FIX_DEF:
		sd->fix_status.def = val;
		break;
	case SP_FIX_MDEF:
		sd->fix_status.mdef = val;
		break;
	case SP_FIX_HIT:
		sd->fix_status.hit = val;
		break;
	case SP_FIX_CRITICAL:
		sd->fix_status.critical = val;
		break;
	case SP_FIX_FLEE:
		sd->fix_status.flee = val;
		break;
	case SP_FIX_ASPD:
		sd->fix_status.aspd = val;
		break;
	case SP_FIX_SPEED:
		sd->fix_status.speed = val;
		break;
	case SP_MATK2_RATE:
		if(sd->state.lr_flag != 2)
			sd->matk2_rate += val;
		break;
	default:
		if(battle_config.error_log)
			printf("pc_bonus: unknown type %d %d !\n",type,val);
		break;
	}
	return 0;
}

/*==========================================
 * 装備品による能力等のボーナス設定２
 *------------------------------------------
 */
int bonus_param2(struct map_session_data *sd,int type,int type2,int val)
{
	int i;

	nullpo_retr(0, sd);

	switch(type) {
	case SP_ADDELE:
		if(type2 < 0 || type2 >= ELE_MAX)
			break;
		if(!sd->state.lr_flag)
			sd->addele[type2] += val;
		else if(sd->state.lr_flag == 1)
			sd->addele_[type2] += val;
		else if(sd->state.lr_flag == 2)
			sd->arrow_addele[type2] += val;
		break;
	case SP_ADDRACE:
		if(type2 < 0 || type2 >= RCT_MAX)
			break;
		if(!sd->state.lr_flag)
			sd->addrace[type2] += val;
		else if(sd->state.lr_flag == 1)
			sd->addrace_[type2] += val;
		else if(sd->state.lr_flag == 2)
			sd->arrow_addrace[type2] += val;
		break;
	case SP_ADDENEMY:
		if(type2 < 0 || type2 >= EMY_MAX)
			break;
		if(!sd->state.lr_flag)
			sd->addenemy[type2] += val;
		else if(sd->state.lr_flag == 1)
			sd->addenemy_[type2] += val;
		else if(sd->state.lr_flag == 2)
			sd->arrow_addenemy[type2] += val;
		break;
	case SP_ADDSIZE:
		if(type2 < 0 || type2 >= MAX_SIZE_FIX)
			break;
		if(!sd->state.lr_flag)
			sd->addsize[type2] += val;
		else if(sd->state.lr_flag == 1)
			sd->addsize_[type2] += val;
		else if(sd->state.lr_flag == 2)
			sd->arrow_addsize[type2] += val;
		break;
	case SP_SUBELE:
		if(type2 < 0 || type2 >= ELE_MAX)
			break;
		if(sd->state.lr_flag != 2)
			sd->subele[type2] += val;
		break;
	case SP_SUBRACE:
		if(type2 < 0 || type2 >= RCT_MAX)
			break;
		if(sd->state.lr_flag != 2)
			sd->subrace[type2] += val;
		break;
	case SP_SUBENEMY:
		if(type2 < 0 || type2 >= EMY_MAX)
			break;
		if(sd->state.lr_flag != 2)
			sd->subenemy[type2] += val;
		break;
	case SP_ADDEFF:
	case SP_ADDEFFSHORT:
	case SP_ADDEFFLONG:
		if(type2 < 0 || type2 >= MAX_EFF_TYPE)
			break;
		if(sd->state.lr_flag != 2)
			sd->addeff[type2] += val;
		else
			sd->arrow_addeff[type2] += val;
		if(type == SP_ADDEFF)
			sd->addeff_range_flag[type2] = 0;
		if(type == SP_ADDEFFSHORT)
			sd->addeff_range_flag[type2] = 1;
		if(type == SP_ADDEFFLONG)
			sd->addeff_range_flag[type2] = 2;
		break;
	case SP_ADDEFF2:
		if(type2 < 0 || type2 >= MAX_EFF_TYPE)
			break;
		if(sd->state.lr_flag != 2)
			sd->addeff2[type2] += val;
		else
			sd->arrow_addeff2[type2] += val;
		break;
	case SP_RESEFF:
		if(type2 < 0 || type2 >= MAX_EFF_TYPE)
			break;
		if(sd->state.lr_flag != 2)
			sd->reseff[type2] += val;
		break;
	case SP_MAGIC_ADDELE:
		if(type2 < 0 || type2 >= ELE_MAX)
			break;
		if(sd->state.lr_flag != 2)
			sd->magic_addele[type2] += val;
		break;
	case SP_MAGIC_ADDRACE:
		if(type2 < 0 || type2 >= RCT_MAX)
			break;
		if(sd->state.lr_flag != 2)
			sd->magic_addrace[type2] += val;
		break;
	case SP_MAGIC_ADDENEMY:
		if(type2 < 0 || type2 >= EMY_MAX)
			break;
		if(sd->state.lr_flag != 2)
			sd->magic_addenemy[type2] += val;
		break;
	case SP_ADDEFFMAGIC:
		if(type2 < 0 || type2 >= MAX_EFF_TYPE)
			break;
		if(sd->state.lr_flag != 2)
			sd->magic_addeff[type2] += val;
		break;
	case SP_MAGIC_SUBRACE:
		if(type2 < 0 || type2 >= RCT_MAX)
			break;
		if(sd->state.lr_flag != 2)
			sd->magic_subrace[type2] += val;
		break;
	case SP_ADD_DAMAGE_CLASS:
		if(!sd->state.lr_flag) {
			for(i=0; i<sd->add_damage_class_count; i++) {
				if(sd->add_damage_classid[i] == type2) {
					sd->add_damage_classrate[i] += val;
					break;
				}
			}
			if(i >= sd->add_damage_class_count && sd->add_damage_class_count < MAX_BONUS_CLASS) {
				sd->add_damage_classid[sd->add_damage_class_count] = type2;
				sd->add_damage_classrate[sd->add_damage_class_count] += val;
				sd->add_damage_class_count++;
			}
		}
		else if(sd->state.lr_flag == 1) {
			for(i=0; i<sd->add_damage_class_count_; i++) {
				if(sd->add_damage_classid_[i] == type2) {
					sd->add_damage_classrate_[i] += val;
					break;
				}
			}
			if(i >= sd->add_damage_class_count_ && sd->add_damage_class_count_ < MAX_BONUS_CLASS) {
				sd->add_damage_classid_[sd->add_damage_class_count_] = type2;
				sd->add_damage_classrate_[sd->add_damage_class_count_] += val;
				sd->add_damage_class_count_++;
			}
		}
		break;
	case SP_ADD_MAGIC_DAMAGE_CLASS:
		if(sd->state.lr_flag != 2) {
			for(i=0; i<sd->add_magic_damage_class_count; i++) {
				if(sd->add_magic_damage_classid[i] == type2) {
					sd->add_magic_damage_classrate[i] += val;
					break;
				}
			}
			if(i >= sd->add_magic_damage_class_count && sd->add_magic_damage_class_count < MAX_BONUS_CLASS) {
				sd->add_magic_damage_classid[sd->add_magic_damage_class_count] = type2;
				sd->add_magic_damage_classrate[sd->add_magic_damage_class_count] += val;
				sd->add_magic_damage_class_count++;
			}
		}
		break;
	case SP_ADD_DEF_CLASS:
		if(sd->state.lr_flag != 2) {
			for(i=0; i<sd->add_def_class_count; i++) {
				if(sd->add_def_classid[i] == type2) {
					sd->add_def_classrate[i] += val;
					break;
				}
			}
			if(i >= sd->add_def_class_count && sd->add_def_class_count < MAX_BONUS_CLASS) {
				sd->add_def_classid[sd->add_def_class_count] = type2;
				sd->add_def_classrate[sd->add_def_class_count] += val;
				sd->add_def_class_count++;
			}
		}
		break;
	case SP_ADD_MDEF_CLASS:
		if(sd->state.lr_flag != 2) {
			for(i=0; i<sd->add_mdef_class_count; i++) {
				if(sd->add_mdef_classid[i] == type2) {
					sd->add_mdef_classrate[i] += val;
					break;
				}
			}
			if(i >= sd->add_mdef_class_count && sd->add_mdef_class_count < MAX_BONUS_CLASS) {
				sd->add_mdef_classid[sd->add_mdef_class_count] = type2;
				sd->add_mdef_classrate[sd->add_mdef_class_count] += val;
				sd->add_mdef_class_count++;
			}
		}
		break;
	case SP_HP_DRAIN_RATE:
		if(!sd->state.lr_flag) {
			sd->hp_drain.p_rate += type2;
			sd->hp_drain.per += val;
		}
		else if(sd->state.lr_flag == 1) {
			sd->hp_drain_.p_rate += type2;
			sd->hp_drain_.per += val;
		}
		break;
	case SP_HP_DRAIN_VALUE:
		if(!sd->state.lr_flag) {
			sd->hp_drain.v_rate += type2;
			sd->hp_drain.value += val;
		}
		else if(sd->state.lr_flag == 1) {
			sd->hp_drain_.v_rate += type2;
			sd->hp_drain_.value += val;
		}
		break;
	case SP_SP_DRAIN_RATE:
		if(!sd->state.lr_flag) {
			sd->sp_drain.p_rate += type2;
			sd->sp_drain.per += val;
		}
		else if(sd->state.lr_flag == 1) {
			sd->sp_drain_.p_rate += type2;
			sd->sp_drain_.per += val;
		}
		break;
	case SP_SP_DRAIN_VALUE:
		if(!sd->state.lr_flag) {
			sd->sp_drain.v_rate += type2;
			sd->sp_drain.value += val;
		}
		else if(sd->state.lr_flag == 1) {
			sd->sp_drain_.v_rate += type2;
			sd->sp_drain_.value += val;
		}
		break;
	case SP_WEAPON_COMA_ELE:
		if(type2 < 0 || type2 >= ELE_MAX)
			break;
		if(sd->state.lr_flag != 2)
			sd->weapon_coma_ele[type2] += val;
		break;
	case SP_WEAPON_COMA_RACE:
		if(type2 < 0 || type2 >= RCT_MAX)
			break;
		if(sd->state.lr_flag != 2)
			sd->weapon_coma_race[type2] += val;
		break;
	case SP_WEAPON_COMA_ELE2:
		if(type2 < 0 || type2 >= ELE_MAX)
			break;
		if(sd->state.lr_flag != 2)
			sd->weapon_coma_ele2[type2] += val;
		break;
	case SP_WEAPON_COMA_RACE2:
		if(type2 < 0 || type2 >= RCT_MAX)
			break;
		if(sd->state.lr_flag != 2)
			sd->weapon_coma_race2[type2] += val;
		break;
	case SP_WEAPON_ATK:
		if(type2 < 0 || type2 >= WT_MAX)
			break;
		if(sd->state.lr_flag != 2)
			sd->weapon_atk[type2] += val;
		break;
	case SP_WEAPON_ATK_RATE:
		if(type2 < 0 || type2 >= WT_MAX)
			break;
		if(sd->state.lr_flag != 2)
			sd->weapon_atk_rate[type2] += val;
		break;
	case SP_CRITICALRACE:
		if(type2 == RCT_ALL) {
			for(i=0; i<RCT_ALL; i++) {
				sd->critical_race[i] += val*10;
			}
		} else if(type2 >= 0 && type2 < RCT_ALL) {
			sd->critical_race[type2] += val*10;
		}
		break;
	case SP_CRITICALRACERATE:
		if(type2 == RCT_ALL) {
			for(i=0; i<RCT_ALL; i++) {
				sd->critical_race_rate[i] += val*10;
			}
		} else if(type2 >= 0 && type2 < RCT_ALL) {
			sd->critical_race_rate[type2] += val*10;
		}
		break;
	case SP_ADDREVEFF:
		if(type2 >= 0 || type2 < MAX_EFF_TYPE) {
			sd->addreveff[type2] += val;
			sd->addreveff_flag = 1;
		}
		break;
	case SP_SUB_SIZE:
		if(type2 >= 0 && type2 < MAX_SIZE_FIX)
			sd->subsize[type2] += val;
		break;
	case SP_MAGIC_SUB_SIZE:
		if(type2 >= 0 && type2 < MAX_SIZE_FIX)
			sd->magic_subsize[type2] += val;
		break;
	case SP_EXP_RATE:
		if(type2 == RCT_ALL) {
			for(i=0; i<RCT_ALL; i++) {
				sd->exp_rate[i] += val;
			}
		} else if(type2 >= 0 && type2 < RCT_ALL) {
			sd->exp_rate[type2] += val;
		}
		break;
	case SP_JOB_RATE:
		if(type2 == RCT_ALL) {
			for(i=0; i<RCT_ALL; i++) {
				sd->job_rate[i] += val;
			}
		} else if(type2 >= 0 && type2 < RCT_ALL) {
				sd->job_rate[type2] += val;
		}
		break;
	case SP_ADD_SKILL_DAMAGE_RATE:
		// update
		for(i=0; i<sd->skill_dmgup.count; i++)
		{
			if(sd->skill_dmgup.id[i] == type2)
			{
				sd->skill_dmgup.rate[i] += val;
				return 0;
			}
		}
		// full
		if(sd->skill_dmgup.count == MAX_SKILL_DAMAGE_UP)
			break;
		// add
		sd->skill_dmgup.id[sd->skill_dmgup.count] = type2;
		sd->skill_dmgup.rate[sd->skill_dmgup.count] = val;
		sd->skill_dmgup.count++;
		break;
	case SP_ADD_GROUP:
		if(type2 < 0 || type2 >= MAX_MOBGROUP)
			break;
		if(!sd->state.lr_flag)
			sd->addgroup[type2] += val;
		else if(sd->state.lr_flag == 1)
			sd->addgroup_[type2] += val;
		else if(sd->state.lr_flag == 2)
			sd->arrow_addgroup[type2] += val;
		break;
	case SP_SUB_GROUP:
		if(type2 < 0 || type2 >= MAX_MOBGROUP)
			break;
		sd->subgroup[type2] += val;
		break;
	case SP_HP_PENALTY_TIME:
		sd->hp_penalty_time = type2;
		sd->hp_penalty_value = val;
		break;
	case SP_SP_PENALTY_TIME:
		sd->sp_penalty_time = type2;
		sd->sp_penalty_value = val;
		break;
	case SP_ADD_SKILL_BLOW:
		// update
		for(i=0; i<sd->skill_blow.count; i++)
		{
			if(sd->skill_blow.id[i] == type2)
			{
				if(sd->skill_blow.grid[i] < val)
					sd->skill_blow.grid[i] = val;
				return 0;
			}
		}
		// full
		if(sd->skill_blow.count == MAX_SKILL_BLOW)
			break;
		// add
		sd->skill_blow.id[sd->skill_blow.count] = type2;
		sd->skill_blow.grid[sd->skill_blow.count] = val;
		sd->skill_blow.count++;
		break;
	case SP_ADD_ITEMHEAL_RATE_GROUP:
		if(type2 < 0 || type2 >= MAX_ITEMGROUP)
			break;
		sd->itemheal_rate[type2] += val;
		break;
	case SP_HPVANISH:
		sd->hp_vanish.rate += type2;
		sd->hp_vanish.per  += val;
		break;
	case SP_SPVANISH:
		sd->sp_vanish.rate += type2;
		sd->sp_vanish.per  += val;
		break;
	case SP_RAISE:
		sd->autoraise.hp_per = val;
		sd->autoraise.sp_per = 0;
		sd->autoraise.rate   = type2;
		sd->autoraise.flag   = 0;
		break;
	case SP_ETERNAL_STATUS_CHANGE:
		if(type2 >= 0 && type2 < MAX_STATUSCHANGE)
		{
			if(val > 0 && val <= 30000)
				sd->eternal_status_change[type2] = val;
			else sd->eternal_status_change[type2] = 1000;
		}
		break;
	case SP_FIXCASTRATE:
		if(!val) {
			if(sd->fixcastrate < -(type2))
				sd->fixcastrate = -(type2);
		} else {
			sd->fixcastrate_ += -(type2);
		}
		break;
	case SP_ADD_FIX_CAST_RATE:
		// update
		for(i=0; i<sd->skill_fixcastrate.count; i++)
		{
			if(sd->skill_fixcastrate.id[i] == type2)
			{
				sd->skill_fixcastrate.rate[i] += val;
				return 0;
			}
		}
		// full
		if(sd->skill_fixcastrate.count == MAX_SKILL_FIXCASTRATE)
			break;
		// add
		sd->skill_fixcastrate.id[sd->skill_fixcastrate.count] = type2;
		sd->skill_fixcastrate.rate[sd->skill_fixcastrate.count] = val;
		sd->skill_fixcastrate.count++;
		break;
	case SP_ADD_CAST_RATE:
		//update
		for(i=0; i<sd->skill_addcastrate.count; i++)
		{
			if(sd->skill_addcastrate.id[i] == type2)
			{
				sd->skill_addcastrate.rate[i] += val;
				return 0;
			}
		}
		//full
		if(sd->skill_addcastrate.count == MAX_SKILL_ADDCASTRATE)
			break;
		//add
		sd->skill_addcastrate.id[sd->skill_addcastrate.count] = type2;
		sd->skill_addcastrate.rate[sd->skill_addcastrate.count] = val;
		sd->skill_addcastrate.count++;
		break;
	case SP_ADD_CAST_TIME:
		// update
		for(i=0; i<sd->skill_addcast.count; i++)
		{
			if(sd->skill_addcast.id[i] == type2)
			{
				sd->skill_addcast.time[i] += val;
				return 0;
			}
		}
		// full
		if(sd->skill_addcast.count == MAX_SKILL_ADDCASTTIME)
			break;
		// add
		sd->skill_addcast.id[sd->skill_addcast.count] = type2;
		sd->skill_addcast.time[sd->skill_addcast.count] = val;
		sd->skill_addcast.count++;
		break;
	case SP_ADD_COOL_DOWN:
		// update
		for(i=0; i<sd->skill_cooldown.count; i++)
		{
			if(sd->skill_cooldown.id[i] == type2)
			{
				sd->skill_cooldown.time[i] += val;
				return 0;
			}
		}
		// full
		if(sd->skill_cooldown.count == MAX_SKILL_ADDCOOLDOWN)
			break;
		// add
		sd->skill_cooldown.id[sd->skill_cooldown.count] = type2;
		sd->skill_cooldown.time[sd->skill_cooldown.count] = val;
		sd->skill_cooldown.count++;
		break;
	case SP_ADD_SKILL_HEAL_RATE:
		// update
		for(i=0; i<sd->skill_healup.count; i++)
		{
			if(sd->skill_healup.id[i] == type2)
			{
				sd->skill_healup.rate[i] += val;
				return 0;
			}
		}
		// full
		if(sd->skill_healup.count == MAX_SKILL_HEAL_UP)
			break;
		// add
		sd->skill_healup.id[sd->skill_healup.count] = type2;
		sd->skill_healup.rate[sd->skill_healup.count] = val;
		sd->skill_healup.count++;
		break;
	case SP_ADD_SKILL_SUBHEAL_RATE:
		// update
		for(i=0; i<sd->skill_subhealup.count; i++)
		{
			if(sd->skill_subhealup.id[i] == type2)
			{
				sd->skill_subhealup.rate[i] += val;
				return 0;
			}
		}
		// full
		if(sd->skill_subhealup.count == MAX_SKILL_HEAL_UP)
			break;
		// add
		sd->skill_subhealup.id[sd->skill_subhealup.count] = type2;
		sd->skill_subhealup.rate[sd->skill_subhealup.count] = val;
		sd->skill_subhealup.count++;
		break;
	case SP_ADD_SP_COST:
		//update
		for(i=0; i<sd->skill_addspcost.count; i++)
		{
			if(sd->skill_addspcost.id[i] == type2)
			{
				sd->skill_addspcost.rate[i] += val;
				return 0;
			}
		}
		//full
		if(sd->skill_addspcost.count == MAX_SKILL_ADDSPCOST)
			break;
		//add
		sd->skill_addspcost.id[sd->skill_addspcost.count] = type2;
		sd->skill_addspcost.rate[sd->skill_addspcost.count] = val;
		sd->skill_addspcost.count++;
		break;
	case SP_IGNORE_DEF_ELE:
		if(type2 < 0 || type2 >= ELE_MAX)
			break;
		if(!sd->state.lr_flag)
			sd->ignore_def_ele[type2] += val;
		else if(sd->state.lr_flag == 1)
			sd->ignore_def_ele_[type2] += val;
		break;
	case SP_IGNORE_DEF_RACE:
		if(type2 < 0 || type2 >= RCT_MAX)
			break;
		if(!sd->state.lr_flag)
			sd->ignore_def_race[type2] += val;
		else if(sd->state.lr_flag == 1)
			sd->ignore_def_race_[type2] += val;
		break;
	case SP_IGNORE_DEF_ENEMY:
		if(type2 < 0 || type2 >= EMY_MAX)
			break;
		if(!sd->state.lr_flag)
			sd->ignore_def_enemy[type2] += val;
		else if(sd->state.lr_flag == 1)
			sd->ignore_def_enemy_[type2] += val;
		break;
	case SP_IGNORE_MDEF_ELE:
		if(type2 < 0 || type2 >= ELE_MAX)
			break;
		if(sd->state.lr_flag != 2)
			sd->ignore_mdef_ele[type2] += val;
		break;
	case SP_IGNORE_MDEF_RACE:
		if(type2 < 0 || type2 >= RCT_MAX)
			break;
		if(sd->state.lr_flag != 2)
			sd->ignore_mdef_race[type2] += val;
		break;
	case SP_IGNORE_MDEF_ENEMY:
		if(type2 < 0 || type2 >= EMY_MAX)
			break;
		if(sd->state.lr_flag != 2)
			sd->ignore_mdef_enemy[type2] += val;
		break;
	case SP_DEF_ELEENEMY:
		if(type2 < 0 || type2 >= ELE_MAX)
			break;
		if(sd->state.lr_flag != 2)
			sd->def_eleenemy[type2] += val;
		break;
	case SP_ADD_ELEWEAPONDAMAGE_RATE:
		if(type2 < 0 || type2 >= ELE_MAX)
			break;
		if(sd->state.lr_flag != 2)
			sd->skill_eleweapon_dmgup[type2] += val;
		break;
	case SP_ADD_ELEMAGICDAMAGE_RATE:
		if(type2 < 0 || type2 >= ELE_MAX)
			break;
		if(sd->state.lr_flag != 2)
			sd->skill_elemagic_dmgup[type2] += val;
		break;
	default:
		if(battle_config.error_log)
			printf("pc_bonus2: unknown type %d %d %d!\n",type,type2,val);
		break;
	}

	return 0;
}

/*==========================================
 * 装備品による能力等のボーナス設定３
 *------------------------------------------
 */
int bonus_param3(struct map_session_data *sd,int type,int type2,int type3,int val)
{
	int i;

	nullpo_retr(0, sd);

	switch(type) {
	case SP_ADD_MONSTER_DROP_ITEM:
		if(sd->state.lr_flag != 2) {
			if(battle_config.dropitem_itemrate_fix == 1)
				val = mob_droprate_fix(&sd->bl,type2,val);
			else if(battle_config.dropitem_itemrate_fix > 1)
				val = val * battle_config.dropitem_itemrate_fix / 100;
			for(i=0; i<sd->monster_drop_item_count; i++) {
				if(sd->monster_drop_itemid[i] == type2) {
					sd->monster_drop_race[i] |= 1<<type3;
					if(sd->monster_drop_itemrate[i] < val)
						sd->monster_drop_itemrate[i] = val;
					break;
				}
			}
			if(i >= sd->monster_drop_item_count && sd->monster_drop_item_count < MAX_BONUS_ADDDROP) {
				sd->monster_drop_itemid[sd->monster_drop_item_count] = type2;
				sd->monster_drop_race[sd->monster_drop_item_count] |= 1<<type3;
				sd->monster_drop_itemrate[sd->monster_drop_item_count] = val;
				sd->monster_drop_item_count++;
			}
		}
		break;
	case SP_DEF_HP_DRAIN_VALUE:
		if(sd->state.lr_flag != 2) {;
			if(type2 == RCT_ALL) {
				for(i=0; i<RCT_ALL; i++) {
					sd->hp_drain_rate_race[i]  += type3;
					sd->hp_drain_value_race[i] += val;
				}
			} else if(type2 >= 0 && type2 < RCT_ALL) {
				sd->hp_drain_rate_race[type2]  += type3;
				sd->hp_drain_value_race[type2] += val;
			}
		}
		break;
	case SP_DEF_SP_DRAIN_VALUE:
		if(sd->state.lr_flag != 2) {
			if(type2 == RCT_ALL) {
				for(i=0; i<RCT_ALL; i++) {
					sd->sp_drain_rate_race[i]  += type3;
					sd->sp_drain_value_race[i] += val;
				}
			} else if(type2 >= 0 && type2 < RCT_ALL) {
				sd->sp_drain_rate_race[type2]  += type3;
				sd->sp_drain_value_race[type2] += val;
			}
		}
		break;
	case SP_AUTOSPELL:
		if(sd->state.lr_flag != 2)
			bonus_add_autospell(sd,0,type2,type3,val,EAS_TARGET|EAS_SHORT|EAS_LONG|EAS_ATTACK|EAS_NOSP);
		break;
	case SP_AUTOSPELL2:
		if(sd->state.lr_flag != 2)
			bonus_add_autospell(sd,0,type2,type3,val,EAS_TARGET|EAS_SHORT|EAS_LONG|EAS_ATTACK|EAS_USEMAX|EAS_NOSP);
		break;
	case SP_AUTOSELFSPELL:
		if(sd->state.lr_flag != 2)
			bonus_add_autospell(sd,0,type2,type3,val,EAS_SELF|EAS_SHORT|EAS_LONG|EAS_ATTACK|EAS_NOSP);
		break;
	case SP_AUTOSELFSPELL2:
		if(sd->state.lr_flag != 2)
			bonus_add_autospell(sd,0,type2,type3,val,EAS_SELF|EAS_SHORT|EAS_LONG|EAS_ATTACK|EAS_USEMAX|EAS_NOSP);
		break;
	case SP_REVAUTOSPELL:	// 反撃用オートスペル
		if(sd->state.lr_flag != 2)
			bonus_add_autospell(sd,0,type2,type3,val,EAS_TARGET|EAS_SHORT|EAS_LONG|EAS_REVENGE|EAS_NOSP);
		break;
	case SP_REVAUTOSPELL2:
		if(sd->state.lr_flag != 2)
			bonus_add_autospell(sd,0,type2,type3,val,EAS_TARGET|EAS_SHORT|EAS_LONG|EAS_REVENGE|EAS_USEMAX|EAS_NOSP);
		break;
	case SP_REVAUTOSELFSPELL:
		if(sd->state.lr_flag != 2)
			bonus_add_autospell(sd,0,type2,type3,val,EAS_SELF|EAS_SHORT|EAS_LONG|EAS_REVENGE|EAS_NOSP);
		break;
	case SP_REVAUTOSELFSPELL2:
		if(sd->state.lr_flag != 2)
			bonus_add_autospell(sd,0,type2,type3,val,EAS_SELF|EAS_SHORT|EAS_LONG|EAS_REVENGE|EAS_USEMAX|EAS_NOSP);
		break;
	case SP_AUTOACTIVE_WEAPON:
		if(sd->state.lr_flag != 2)
			bonus_activeitem(sd,0,type2,type3,val,EAS_SHORT|EAS_LONG|EAS_ATTACK);
		break;
	case SP_AUTOACTIVE_MAGIC:
		if(sd->state.lr_flag != 2)
			bonus_activeitem(sd,0,type2,type3,val,EAS_MAGIC);
		break;
	case SP_REVAUTOACTIVE_WEAPON:
		if(sd->state.lr_flag != 2)
			bonus_activeitem(sd,0,type2,type3,val,EAS_SHORT|EAS_LONG|EAS_REVENGE);
		break;
	case SP_REVAUTOACTIVE_MAGIC:
		if(sd->state.lr_flag != 2)
			bonus_activeitem(sd,0,type2,type3,val,EAS_MAGIC|EAS_REVENGE);
		break;
	case SP_RAISE:
		sd->autoraise.hp_per = type3;
		sd->autoraise.sp_per = val;
		sd->autoraise.rate   = type2;
		sd->autoraise.flag   = 1;
		break;
	case SP_ADDEFFSKILL:
		if(type3 < 0 || type3 >= MAX_EFF_TYPE)
			break;
		if(sd->state.lr_flag != 2) {
			// update
			for(i=0; i<sd->skill_addeff.count; i++)
			{
				if(sd->skill_addeff.id[i] == type2)
				{
					sd->skill_addeff.addeff[i][type3] += val;
					return 0;
				}
			}
			// full
			if(sd->skill_addeff.count == MAX_SKILL_ADDEFF)
				break;
			// add
			sd->skill_addeff.id[sd->skill_addeff.count] = type2;
			sd->skill_addeff.addeff[sd->skill_addeff.count][type3] = val;
			sd->skill_addeff.count++;
		}
		break;
	default:
		if(battle_config.error_log)
			printf("pc_bonus3: unknown type %d %d %d %d!\n",type,type2,type3,val);
		break;
	}

	return 0;
}

/*==========================================
 * 装備品による能力等のボーナス設定４
 *------------------------------------------
 */
int bonus_param4(struct map_session_data *sd,int type,int type2,int type3,int type4,unsigned int val)
{
	nullpo_retr(0, sd);

	switch(type) {
	case SP_AUTOSPELL:
		if(sd->state.lr_flag != 2)
			bonus_add_autospell(sd,0,type2,type3,type4,val);
		break;
	case SP_AUTOACTIVE_ITEM:
		if(sd->state.lr_flag != 2)
			bonus_activeitem(sd,0,type2,type3,type4,val);
		break;
	case SP_SKILLAUTOSPELL:
		if(sd->state.lr_flag != 2)
			bonus_add_autospell(sd,type2,type3,type4,val,EAS_TARGET|EAS_SKILL|EAS_NOSP);
		break;
	case SP_SKILLAUTOSPELL2:
		if(sd->state.lr_flag != 2)
			bonus_add_autospell(sd,type2,type3,type4,val,EAS_TARGET|EAS_SKILL|EAS_USEMAX|EAS_NOSP);
		break;
	case SP_SKILLAUTOSELFSPELL:
		if(sd->state.lr_flag != 2)
			bonus_add_autospell(sd,type2,type3,type4,val,EAS_SELF|EAS_SKILL|EAS_NOSP);
		break;
	case SP_SKILLAUTOSELFSPELL2:
		if(sd->state.lr_flag != 2)
			bonus_add_autospell(sd,type2,type3,type4,val,EAS_SELF|EAS_SKILL|EAS_USEMAX|EAS_NOSP);
		break;
	case SP_AUTOACTIVE_SKILL:
		if(sd->state.lr_flag != 2)
			bonus_activeitem(sd,type2,type3,type4,val,EAS_SKILL|EAS_ATTACK);
		break;
	default:
		if(battle_config.error_log)
			printf("pc_bonus4: unknown type %d %d %d %d %u!\n",type,type2,type3,type4,val);
		break;
	}

	return 0;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
int do_final_bonus(void)
{
	return 0;
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
int do_init_bonus(void)
{
	add_timer_func_list(bonus_activeitem_timer);

	return 0;
}
