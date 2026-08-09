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

#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>

#include "db.h"
#include "malloc.h"
#include "nullpo.h"
#include "timer.h"
#include "utils.h"

#include "pc.h"
#include "map.h"
#include "path.h"
#include "pet.h"
#include "homun.h"
#include "mob.h"
#include "clif.h"
#include "skill.h"
#include "itemdb.h"
#include "battle.h"
#include "status.h"
#include "status_calc_ctrl.h"
#include "status_internal.h"
#include "script.h"
#include "guild.h"
#include "unit.h"
#include "ranking.h"
#include "merc.h"
#include "elem.h"
#include "msg.h"
#include "bonus.h"
#include "date.h"

/* Split from status.c (Issue #57 PR2) */

static int status_calc_amotion_pc(struct map_session_data *sd);	// PC用amotion計算
static int status_calc_speed_pc(struct map_session_data *sd,int speed);	// PC用speed計算

/*==========================================
 * パラメータ計算
 * first==0の時、計算対象のパラメータが呼び出し前から
 * 変化した場合自動でsendするが、
 * 能動的に変化させたパラメータは自前でsendするように
 *------------------------------------------
 */

/* status_calc_pc phase helpers (Issue #57 PR1) - file-local only */
struct status_calc_pc_work {
	int first;
	int calclimit;
	int i, blv, calc_val, idx;
	int skill, wele, wele_, def_ele, refinedef;
	int pele, pdef_ele;
	int str, dstr, dex;
	int b_tigereye, b_endure, b_speedrate;
	int b_class;
};

static void status_calc_pc_phase_reset(struct map_session_data *sd, struct status_calc_pc_work *w);
static void status_calc_pc_phase_clear(struct map_session_data *sd);
static void status_calc_pc_phase_equip(struct map_session_data *sd, struct status_calc_pc_work *w);
static void status_calc_pc_phase_job(struct map_session_data *sd, struct status_calc_pc_work *w);
static void status_calc_pc_phase_sc_base(struct map_session_data *sd, struct status_calc_pc_work *w);
static void status_calc_pc_phase_derived(struct map_session_data *sd, struct status_calc_pc_work *w);
static void status_calc_pc_phase_sc_rest(struct map_session_data *sd, struct status_calc_pc_work *w);

static void status_calc_pc_phase_reset(struct map_session_data *sd, struct status_calc_pc_work *w)
{
	// 本来の計算開始(元のパラメータを更新しないのは、計算中に計算処理が呼ばれたときの
	// 反映分も新たに送信するため)。

	w->pele      = ELE_NEUTRAL;
	w->pdef_ele  = ELE_NEUTRAL;
	w->refinedef = 0;
	sd->view_class = sd->status.class_;
	if(pc_isdoram(sd))
		sd->race = RCT_PLAYER_DORAM;
	else
		sd->race = RCT_PLAYER_HUMAN;
	sd->ranker_weapon_bonus  = 0;
	sd->ranker_weapon_bonus_ = 0;
	sd->special_state.infinite_tigereye = 0;
	sd->special_state.infinite_endure   = 0;

	pc_calc_skilltree(sd);	// スキルツリーの計算

	sd->max_weight = job_db[sd->s_class.job].max_weight_base+sd->status.str*battle_config.str_weight;

	if(battle_config.baby_weight_rate != 100 && pc_isbaby(sd))
		sd->max_weight = sd->max_weight*battle_config.baby_weight_rate/100;
	else if(battle_config.upper_weight_rate != 100 && pc_isupper(sd))
		sd->max_weight = sd->max_weight*battle_config.upper_weight_rate/100;
	else if(battle_config.normal_weight_rate != 100)
		sd->max_weight = sd->max_weight*battle_config.normal_weight_rate/100;

	// ペコ騎乗時増えるよう移動
	if(pc_isriding(sd))	// ペコペコ・グリフォン
		sd->max_weight += battle_config.riding_weight;

	if(pc_isdragon(sd) && (w->skill =  pc_checkskill(sd,RK_DRAGONTRAINING)) > 0)	// ドラゴン騎乗かつドラゴントレーニング習得済み
		sd->max_weight += 5000 + 2000 * w->skill;

	if((w->skill = pc_checkskill(sd,MC_INCCARRY)) > 0)	// 所持量増加
		sd->max_weight += w->skill*2000;

	if((w->skill = pc_checkskill(sd,ALL_INCCARRAY)) > 0)	// 所持量増加R
		sd->max_weight += w->skill*2000;

	if((w->skill = pc_checkskill(sd,SG_KNOWLEDGE)) > 0)	// 太陽と月と星の知識
	{
	 	if(battle_config.check_knowlege_map) {	// 場所チェックを行なう
			if(sd->bl.m == sd->feel_index[0] || sd->bl.m == sd->feel_index[1] || sd->bl.m == sd->feel_index[2])
				sd->max_weight += sd->max_weight*w->skill/10;
		} else {
			sd->max_weight += sd->max_weight*w->skill/10;
		}
	}

	if(w->first&1) {
		sd->weight = 0;
		for(w->i=0; w->i<MAX_INVENTORY; w->i++) {
			if(sd->status.inventory[w->i].nameid == 0 || sd->inventory_data[w->i] == NULL)
				continue;
			sd->weight += sd->inventory_data[w->i]->weight*sd->status.inventory[w->i].amount;
		}
		sd->cart_max_weight = battle_config.max_cart_weight;
		if((w->skill = pc_checkskill(sd,GN_REMODELING_CART)) > 0)	// カート改造
			sd->cart_max_weight += w->skill*5000;
		sd->cart_weight     = 0;
		sd->cart_max_num    = MAX_CART;
		sd->cart_num        = 0;
		for(w->i=0; w->i<MAX_CART; w->i++) {
			if(sd->status.cart[w->i].nameid == 0)
				continue;
			sd->cart_weight += itemdb_weight(sd->status.cart[w->i].nameid)*sd->status.cart[w->i].amount;
			sd->cart_num++;
		}
	}
}

static void status_calc_pc_phase_clear(struct map_session_data *sd)
{
	memset(sd->paramb,0,sizeof(sd->paramb));
	memset(sd->parame,0,sizeof(sd->parame));
	sd->hit                 = 0;
	sd->flee                = 0;
	sd->flee2               = 0;
	sd->critical            = 0;
	sd->aspd                = 0;
	sd->watk                = 0;
	sd->def                 = 0;
	sd->mdef                = 0;
	sd->watk2               = 0;
	sd->def2                = 0;
	sd->mdef2               = 0;
	sd->status.max_hp       = 0;
	sd->status.max_sp       = 0;
	sd->range.attackrange   = 0;
	sd->range.attackrange_  = 0;
	sd->atk_ele             = ELE_NEUTRAL;
	sd->def_ele             = ELE_NEUTRAL;
	sd->star                = 0;
	sd->overrefine          = 0;
	sd->matk1               = 0;
	sd->matk2               = 0;
	sd->speed               = DEFAULT_WALK_SPEED;
	sd->hprate              = battle_config.hp_rate;
	sd->sprate              = battle_config.sp_rate;
	sd->castrate            = 100;
	sd->fixcastrate         = 0;
	sd->fixcastrate_        = 0;
	sd->dsprate             = 100;
	sd->base_atk            = 0;
	sd->status.max_ap       = 0;
	sd->patk                = 0;
	sd->smatk               = 0;
	sd->res                 = 0;
	sd->mres                = 0;
	sd->hplus               = 0;
	sd->crate               = 0;
#ifndef PRE_RENEWAL
	sd->plus_atk            = 0;
	sd->plus_matk           = 0;
#endif
	sd->arrow_atk           = 0;
	sd->arrow_ele           = ELE_NEUTRAL;
	sd->arrow_hit           = 0;
	sd->arrow_range         = 0;
	sd->nhealhp = sd->nhealsp = sd->nshealhp = sd->nshealsp = sd->nsshealhp = sd->nsshealsp = 0;
	memset(sd->addele,0,sizeof(sd->addele));
	memset(sd->addrace,0,sizeof(sd->addrace));
	memset(sd->addenemy,0,sizeof(sd->addenemy));
	memset(sd->addsize,0,sizeof(sd->addsize));
	memset(sd->addele_,0,sizeof(sd->addele_));
	memset(sd->addrace_,0,sizeof(sd->addrace_));
	memset(sd->addenemy_,0,sizeof(sd->addenemy_));
	memset(sd->addsize_,0,sizeof(sd->addsize_));
	memset(sd->subele,0,sizeof(sd->subele));
	memset(sd->subrace,0,sizeof(sd->subrace));
	memset(sd->subenemy,0,sizeof(sd->subenemy));
	memset(sd->addeff,0,sizeof(sd->addeff));
	memset(sd->addeff2,0,sizeof(sd->addeff2));
	memset(sd->reseff,0,sizeof(sd->reseff));
	memset(sd->addeff_range_flag,0,sizeof(sd->addeff));
	memset(&sd->special_state,0,sizeof(sd->special_state));
	memset(sd->weapon_coma_ele,0,sizeof(sd->weapon_coma_ele));
	memset(sd->weapon_coma_race,0,sizeof(sd->weapon_coma_race));
	memset(sd->weapon_coma_ele2,0,sizeof(sd->weapon_coma_ele2));
	memset(sd->weapon_coma_race2,0,sizeof(sd->weapon_coma_race2));
	memset(sd->weapon_atk,0,sizeof(sd->weapon_atk));
	memset(sd->weapon_atk_rate,0,sizeof(sd->weapon_atk_rate));
	memset(sd->auto_status_calc_pc,0,sizeof(sd->auto_status_calc_pc));
	memset(sd->eternal_status_change,0,sizeof(sd->eternal_status_change));

	sd->watk_       = 0;	// 二刀流用
	sd->watk_2      = 0;
	sd->atk_ele_    = ELE_NEUTRAL;
	sd->star_       = 0;
	sd->overrefine_ = 0;

	sd->aspd_add       = 0;
	sd->aspd_rate      = 0;
	sd->aspd_add_rate  = 0;
	sd->speed_rate     = 0;
	sd->speed_add_rate = 0;
	sd->hprecov_rate   = 100;
	sd->sprecov_rate   = 100;
	sd->critical_def   = 0;
	sd->double_rate    = 0;
	sd->near_attack_def_rate = sd->long_attack_def_rate = 0;
	sd->atk_rate = sd->matk_rate = sd->matk2_rate = 100;
	memset(sd->ignore_def_ele,0,sizeof(sd->ignore_def_ele));
	memset(sd->ignore_def_race,0,sizeof(sd->ignore_def_race));
	memset(sd->ignore_def_enemy,0,sizeof(sd->ignore_def_enemy));
	memset(sd->ignore_def_ele_,0,sizeof(sd->ignore_def_ele_));
	memset(sd->ignore_def_race_,0,sizeof(sd->ignore_def_race_));
	memset(sd->ignore_def_enemy_,0,sizeof(sd->ignore_def_enemy_));
	memset(sd->ignore_mdef_ele,0,sizeof(sd->ignore_mdef_ele));
	memset(sd->ignore_mdef_race,0,sizeof(sd->ignore_mdef_race));
	memset(sd->ignore_mdef_enemy,0,sizeof(sd->ignore_mdef_enemy));
	sd->arrow_cri = 0;
	sd->magic_def_rate = sd->misc_def_rate = 0;
	memset(sd->arrow_addele,0,sizeof(sd->arrow_addele));
	memset(sd->arrow_addrace,0,sizeof(sd->arrow_addrace));
	memset(sd->arrow_addenemy,0,sizeof(sd->arrow_addenemy));
	memset(sd->arrow_addsize,0,sizeof(sd->arrow_addsize));
	memset(sd->arrow_addeff,0,sizeof(sd->arrow_addeff));
	memset(sd->arrow_addeff2,0,sizeof(sd->arrow_addeff2));
	memset(sd->magic_addele,0,sizeof(sd->magic_addele));
	memset(sd->magic_addrace,0,sizeof(sd->magic_addrace));
	memset(sd->magic_addenemy,0,sizeof(sd->magic_addenemy));
	memset(sd->magic_addsize,0,sizeof(sd->magic_addsize));
	memset(sd->magic_addeff,0,sizeof(sd->magic_addeff));
	memset(sd->magic_subrace,0,sizeof(sd->magic_subrace));
	sd->perfect_hit = 0;
	sd->critical_rate = sd->hit_rate = sd->flee_rate = sd->flee2_rate = 100;
	sd->def_rate = sd->def2_rate = sd->mdef_rate = sd->mdef2_rate = 100;
	sd->def_ratio_atk_ele = sd->def_ratio_atk_race = sd->def_ratio_atk_enemy = 0;
	sd->def_ratio_atk_ele_ = sd->def_ratio_atk_race_ = sd->def_ratio_atk_enemy_ = 0;
	sd->get_zeny_num = sd->get_zeny_num2 = 0;
	sd->add_damage_class_count = sd->add_damage_class_count_ = sd->add_magic_damage_class_count = 0;
	sd->add_def_class_count = sd->add_mdef_class_count = 0;
	memset(sd->add_damage_classrate,0,sizeof(sd->add_damage_classrate));
	memset(sd->add_damage_classrate_,0,sizeof(sd->add_damage_classrate_));
	memset(sd->add_magic_damage_classrate,0,sizeof(sd->add_magic_damage_classrate));
	memset(sd->add_def_classrate,0,sizeof(sd->add_def_classrate));
	memset(sd->add_mdef_classrate,0,sizeof(sd->add_mdef_classrate));
	memset(&sd->add_drop,0,sizeof(sd->add_drop));
	sd->add_drop_count = 0;
	sd->sp_gain_value = 0;
	sd->hp_gain_value = 0;
	sd->double_add_rate = sd->perfect_hit_add = sd->get_zeny_add_num = sd->get_zeny_add_num2 = 0;
	sd->splash_range = sd->splash_add_range = 0;
	memset(&sd->hp_drain,0,sizeof(sd->hp_drain));
	memset(&sd->sp_drain,0,sizeof(sd->sp_drain));
	memset(&sd->hp_drain_,0,sizeof(sd->hp_drain_));
	memset(&sd->sp_drain_,0,sizeof(sd->sp_drain_));
	sd->short_weapon_damage_return = sd->long_weapon_damage_return = sd->magic_damage_return = sd->sub_return_damage = 0;
	sd->break_weapon_rate = sd->break_armor_rate = 0;
	sd->add_steal_rate    = 0;
	sd->unbreakable_equip = LOC_NOTHING;
	sd->critical_damage   = 0;
	sd->hp_recov_stop = sd->sp_recov_stop = 0;
	memset(sd->critical_race,0,sizeof(sd->critical_race));
	memset(sd->critical_race_rate,0,sizeof(sd->critical_race_rate));
	memset(sd->subsize,0,sizeof(sd->subsize));
	memset(sd->magic_subsize,0,sizeof(sd->magic_subsize));
	memset(sd->exp_rate,0,sizeof(sd->exp_rate));
	memset(sd->job_rate,0,sizeof(sd->job_rate));
	memset(sd->hp_drain_rate_race,0,sizeof(sd->hp_drain_rate_race));
	memset(sd->sp_drain_rate_race,0,sizeof(sd->sp_drain_rate_race));
	memset(sd->hp_drain_value_race,0,sizeof(sd->hp_drain_value_race));
	memset(sd->sp_drain_value_race,0,sizeof(sd->sp_drain_value_race));
	memset(sd->addreveff,0,sizeof(sd->addreveff));
	sd->addreveff_flag = 0;
	memset(sd->addgroup,0,sizeof(sd->addgroup));
	memset(sd->addgroup_,0,sizeof(sd->addgroup_));
	memset(sd->magic_addgroup,0,sizeof(sd->magic_addgroup));
	memset(sd->arrow_addgroup,0,sizeof(sd->arrow_addgroup));
	memset(sd->subgroup,0,sizeof(sd->subgroup));
	sd->hp_penalty_time  = 0;
	sd->hp_penalty_value = 0;
	sd->sp_penalty_time  = 0;
	sd->sp_penalty_value = 0;
	memset(sd->hp_penalty_unrig_value,0,sizeof(sd->hp_penalty_unrig_value));
	memset(sd->sp_penalty_unrig_value,0,sizeof(sd->sp_penalty_unrig_value));
	memset(sd->hp_rate_penalty_unrig,0,sizeof(sd->hp_rate_penalty_unrig));
	memset(sd->sp_rate_penalty_unrig,0,sizeof(sd->sp_rate_penalty_unrig));
	sd->mob_class_change_rate = 0;
	memset(&sd->skill_dmgup,0,sizeof(sd->skill_dmgup));
	memset(&sd->sub_skill_damage,0,sizeof(sd->sub_skill_damage));
	memset(&sd->skill_blow,0,sizeof(sd->skill_blow));
	memset(&sd->autospell,0,sizeof(sd->autospell));
	memset(&sd->itemheal_rate,0,sizeof(sd->itemheal_rate));
	memset(&sd->autoraise,0,sizeof(sd->autoraise));
	memset(&sd->hp_vanish,0,sizeof(sd->hp_vanish));
	memset(&sd->sp_vanish,0,sizeof(sd->sp_vanish));
	sd->bonus_damage      = 0;
	sd->curse_by_muramasa = 0;
	memset(sd->loss_equip_rate_when_die,0,sizeof(sd->loss_equip_rate_when_die));
	memset(sd->loss_equip_rate_when_attack,0,sizeof(sd->loss_equip_rate_when_attack));
	memset(sd->loss_equip_rate_when_hit,0,sizeof(sd->loss_equip_rate_when_hit));
	memset(sd->break_myequip_rate_when_attack,0,sizeof(sd->break_myequip_rate_when_attack));
	memset(sd->break_myequip_rate_when_hit,0,sizeof(sd->break_myequip_rate_when_hit));
	sd->loss_equip_flag = 0;
	sd->short_weapon_damege_rate = sd->long_weapon_damege_rate = 0;
	sd->range.add_attackrange = 0;
	sd->range.add_attackrange_rate = 100;
	sd->special_state.item_no_use = 0;
	sd->skill_delay_rate = 0;
	memset(&sd->fix_status,0,sizeof(sd->fix_status));
	memset(&sd->skill_fixcastrate,0,sizeof(sd->skill_fixcastrate));
	memset(&sd->skill_addcastrate,0,sizeof(sd->skill_addcastrate));
	memset(&sd->skill_healup,0,sizeof(sd->skill_healup));
	memset(&sd->activeitem,0,sizeof(sd->activeitem));
	memset(sd->def_eleenemy,0,sizeof(sd->def_eleenemy));
	memset(&sd->skill_addspcost,0,sizeof(sd->skill_addspcost));
	memset(&sd->skill_subhealup,0,sizeof(sd->skill_subhealup));
	memset(&sd->skill_addcast,0,sizeof(sd->skill_addcast));
	memset(&sd->skill_addfixcast,0,sizeof(sd->skill_addfixcast));
	memset(&sd->skill_cooldown,0,sizeof(sd->skill_cooldown));
	memset(&sd->skill_eleweapon_dmgup,0,sizeof(sd->skill_eleweapon_dmgup));
	memset(&sd->skill_elemagic_dmgup,0,sizeof(sd->skill_elemagic_dmgup));
	sd->hp_rate_penalty_time  = 0;
	sd->hp_rate_penalty_value = 0;
	sd->sp_rate_penalty_time  = 0;
	sd->sp_rate_penalty_value = 0;
}

static void status_calc_pc_phase_equip(struct map_session_data *sd, struct status_calc_pc_work *w)
{
	for(w->i=0; w->i<EQUIP_INDEX_MAX; w->i++) {
		if(w->i == EQUIP_INDEX_ARROW)
			continue;
		w->idx = sd->equip_index[w->i];
		current_equip_item_index = w->i;	// 部位チェック用
		if(w->idx < 0)
			continue;
		if(w->i == EQUIP_INDEX_RARM && sd->equip_index[EQUIP_INDEX_LARM] == w->idx)
			continue;
		if(w->i == EQUIP_INDEX_HEAD3 && sd->equip_index[EQUIP_INDEX_HEAD] == w->idx)
			continue;
		if(w->i == EQUIP_INDEX_HEAD2 && (sd->equip_index[EQUIP_INDEX_HEAD3] == w->idx || sd->equip_index[EQUIP_INDEX_HEAD] == w->idx))
			continue;
		if(w->i == EQUIP_INDEX_COSTUME_HEAD3 && sd->equip_index[EQUIP_INDEX_COSTUME_HEAD] == w->idx)
			continue;
		if(w->i == EQUIP_INDEX_COSTUME_HEAD2 && (sd->equip_index[EQUIP_INDEX_COSTUME_HEAD3] == w->idx || sd->equip_index[EQUIP_INDEX_COSTUME_HEAD] == w->idx))
			continue;

		if(sd->inventory_data[w->idx]) {
			if(itemdb_isweapon(sd->inventory_data[w->idx]->nameid)) {
				int j;
				if( !itemdb_isspecial(sd->status.inventory[w->idx].card[0]) ) {
					int c;
					for(j=0; j<4; j++) {	// カード
						if((c = sd->status.inventory[w->idx].card[j]) <= 0)
							continue;
						if(sd->inventory_data[w->idx]->slot < j && itemdb_cardtype(c) != 2)
							continue;
						current_equip_name_id = c;		// オートスペル(重複チェック用)
						if(w->i == EQUIP_INDEX_LARM && sd->status.inventory[w->idx].equip == LOC_LARM)
							sd->state.lr_flag = 1;
						if(w->calclimit == 2)
							run_script(itemdb_usescript(c),0,sd->bl.id,0);
						run_script(itemdb_equipscript(c),0,sd->bl.id,0);
						sd->state.lr_flag = 0;
					}
				}
				for(j=0; j<5; j++) {	// ランダムオプション
					if(sd->status.inventory[w->idx].opt[j].id <= 0)
						continue;
					if(w->i == EQUIP_INDEX_LARM && sd->status.inventory[w->idx].equip == LOC_LARM)
						sd->state.lr_flag = 1;
					bonus_randopt(sd, sd->status.inventory[w->idx].opt[j].id, sd->status.inventory[w->idx].opt[j].val);
					sd->state.lr_flag = 0;
				}
			}
			else if(itemdb_isarmor(sd->inventory_data[w->idx]->nameid)) { // 防具
				int j;
				if( !itemdb_isspecial(sd->status.inventory[w->idx].card[0]) ) {
					int c;
					for(j=0; j<4; j++) {	// カード
						if((c = sd->status.inventory[w->idx].card[j]) <= 0)
							continue;
						if(sd->inventory_data[w->idx]->slot < j && itemdb_cardtype(c) != 2)
							continue;
						current_equip_name_id = c;		// オートスペル(重複チェック用)
						if(w->calclimit == 2)
							run_script(itemdb_usescript(c),0,sd->bl.id,0);
						run_script(itemdb_equipscript(c),0,sd->bl.id,0);
					}
				}
				for(j=0; j<5; j++) {	// ランダムオプション
					if(sd->status.inventory[w->idx].opt[j].id <= 0)
						continue;
					bonus_randopt(sd, sd->status.inventory[w->idx].opt[j].id, sd->status.inventory[w->idx].opt[j].val);
				}
			}
		}
	}

	for(w->i = 0; w->i < sd->activeitem.count; w->i++)
	{
		if(sd->activeitem_timer[w->i] == -1)
			continue;
		if(sd->activeitem.id[w->i] != sd->activeitem_id2[w->i])
			continue;

		run_script(itemdb_bonusscript(sd->activeitem_id2[w->i]),0,sd->bl.id,0);
	}

	w->wele    = sd->atk_ele;
	w->wele_   = sd->atk_ele_;
	w->def_ele = sd->def_ele;
	if(battle_config.pet_status_support) {
		if(sd->status.pet_id > 0 && sd->petDB && sd->pet.intimate > 0) {
			run_script(sd->petDB->script,0,sd->bl.id,0);
		}
		w->pele        = sd->atk_ele;
		w->pdef_ele    = sd->def_ele;
		sd->atk_ele = sd->def_ele = ELE_NEUTRAL;
	}
	memcpy(sd->paramcard,sd->parame,sizeof(sd->paramcard));

	// 装備品によるステータス変化はここで実行
	for(w->i=0; w->i<EQUIP_INDEX_MAX; w->i++) {
		if(w->i == EQUIP_INDEX_ARROW)
			continue;
		w->idx = sd->equip_index[w->i];
		current_equip_item_index = w->i;	// 部位チェック用
		if(w->idx < 0)
			continue;
		if(w->i == EQUIP_INDEX_RARM && sd->equip_index[EQUIP_INDEX_LARM] == w->idx)
			continue;
		if(w->i == EQUIP_INDEX_HEAD3 && sd->equip_index[EQUIP_INDEX_HEAD] == w->idx)
			continue;
		if(w->i == EQUIP_INDEX_HEAD2 && (sd->equip_index[EQUIP_INDEX_HEAD3] == w->idx || sd->equip_index[EQUIP_INDEX_HEAD] == w->idx))
			continue;
		if(w->i == EQUIP_INDEX_COSTUME_HEAD3 && sd->equip_index[EQUIP_INDEX_COSTUME_HEAD] == w->idx)
			continue;
		if(w->i == EQUIP_INDEX_COSTUME_HEAD2 && (sd->equip_index[EQUIP_INDEX_COSTUME_HEAD3] == w->idx || sd->equip_index[EQUIP_INDEX_COSTUME_HEAD] == w->idx))
			continue;
		if(sd->inventory_data[w->idx]) {
			current_equip_name_id = sd->inventory_data[w->idx]->nameid;
			sd->matk1 += sd->inventory_data[w->idx]->matk;
#ifdef PRE_RENEWAL
			sd->matk2 += sd->inventory_data[w->idx]->matk;
#endif
			sd->def += sd->inventory_data[w->idx]->def;
			sd->mdef += sd->inventory_data[w->idx]->mdef;
			if(itemdb_isweapon(sd->inventory_data[w->idx]->nameid)) {
				int r,wlv = sd->inventory_data[w->idx]->wlv;
				if(w->i == EQUIP_INDEX_LARM && sd->status.inventory[w->idx].equip == LOC_LARM) {
					// 二刀流用データ入力
					sd->watk_ += sd->inventory_data[w->idx]->atk;
					if((r = sd->status.inventory[w->idx].refine) > 0)
						sd->watk_2 = refine_db[wlv].safety_bonus[r-1];	// 精錬攻撃力
#ifndef PRE_RENEWAL
					if(sd->status.weapon != WT_BOW && r > 0)	// 弓には精錬MATKボーナスがない
						sd->matk1 += refine_db[wlv].safety_bonus[r-1];
#endif
					if((r -= refine_db[wlv].limit) > 0)	// 過剰精錬ボーナス
						sd->overrefine_ = r*refine_db[wlv].over_bonus;

					if(sd->status.inventory[w->idx].card[0] == 0x00ff) {	// 製造武器
						sd->star_ = (sd->status.inventory[w->idx].card[1]>>8);	// 星のかけら
						if(sd->star_ == 15)
							sd->star_ = 40;
						w->wele_= sd->status.inventory[w->idx].card[1] & 0x0f;	// 属 性
						// ランキングボーナス
						if(ranking_get_id2rank(*((int *)(&sd->status.inventory[w->idx].card[2])), RK_BLACKSMITH))
							sd->ranker_weapon_bonus_ = battle_config.ranker_weapon_bonus;
					}
					sd->range.attackrange_ += sd->inventory_data[w->idx]->range;
					sd->state.lr_flag = 1;
					if(w->calclimit == 2)
						run_script(sd->inventory_data[w->idx]->use_script,0,sd->bl.id,0);
					run_script(sd->inventory_data[w->idx]->equip_script,0,sd->bl.id,0);
					sd->state.lr_flag = 0;
				} else {
					// 二刀流武器以外
					sd->watk  += sd->inventory_data[w->idx]->atk;
					if((r = sd->status.inventory[w->idx].refine) > 0)
						sd->watk2 += refine_db[wlv].safety_bonus[r-1];	// 精錬攻撃力
#ifndef PRE_RENEWAL
					if(sd->status.weapon != WT_BOW && r > 0)	// 弓には精錬MATKボーナスがない
						sd->matk1 += refine_db[wlv].safety_bonus[r-1];
#endif
					if((r -= refine_db[wlv].limit) > 0)	// 過剰精錬ボーナス
						sd->overrefine += r*refine_db[wlv].over_bonus;

					if(sd->status.inventory[w->idx].card[0] == 0x00ff) {	// 製造武器
						sd->star += (sd->status.inventory[w->idx].card[1]>>8);	// 星のかけら
						if(sd->star == 15)
							sd->star = 40;
						w->wele = sd->status.inventory[w->idx].card[1] & 0x0f;	// 属 性
						// ランキングボーナス
						if(ranking_get_id2rank(*((int *)(&sd->status.inventory[w->idx].card[2])),RK_BLACKSMITH))
							sd->ranker_weapon_bonus = battle_config.ranker_weapon_bonus;
					}
					sd->range.attackrange += sd->inventory_data[w->idx]->range;
					if(w->calclimit == 2)
						run_script(sd->inventory_data[w->idx]->use_script,0,sd->bl.id,0);
					run_script(sd->inventory_data[w->idx]->equip_script,0,sd->bl.id,0);
				}
			} else if(itemdb_isarmor(sd->inventory_data[w->idx]->nameid)) {
				sd->watk  += sd->inventory_data[w->idx]->atk;
				if(sd->status.inventory[w->idx].refine > 0)
					w->refinedef += refine_db[0].safety_bonus[sd->status.inventory[w->idx].refine - 1];
				if(w->calclimit == 2)
					run_script(sd->inventory_data[w->idx]->use_script,0,sd->bl.id,0);
				run_script(sd->inventory_data[w->idx]->equip_script,0,sd->bl.id,0);
			}
		}
	}

	if(sd->equip_index[EQUIP_INDEX_ARROW] >= 0) { // 矢
		w->idx = sd->equip_index[EQUIP_INDEX_ARROW];
		if(sd->inventory_data[w->idx]) {		// まだ属性が入っていない
			current_equip_name_id = sd->inventory_data[w->idx]->nameid;
			sd->state.lr_flag = 2;
			run_script(sd->inventory_data[w->idx]->equip_script,0,sd->bl.id,0);
			sd->state.lr_flag = 0;
			sd->arrow_atk += sd->inventory_data[w->idx]->atk;
		}
	}

	sd->def += (w->refinedef+50)/100;

	if(sd->range.attackrange < 1)  sd->range.attackrange  = 1;
	if(sd->range.attackrange_ < 1) sd->range.attackrange_ = 1;
	if(sd->range.attackrange < sd->range.attackrange_)
		sd->range.attackrange = sd->range.attackrange_;
	if(sd->status.weapon == WT_BOW)
		sd->range.attackrange += sd->arrow_range;
	if(w->wele > ELE_NEUTRAL)
		sd->atk_ele = w->wele;
	if(w->wele_ > ELE_NEUTRAL)
		sd->atk_ele_ = w->wele_;
	if(w->def_ele > ELE_NEUTRAL)
		sd->def_ele = w->def_ele;
	if(battle_config.pet_status_support) {
		if(w->pele > ELE_NEUTRAL && !sd->atk_ele)
			sd->atk_ele = w->pele;
		if(w->pdef_ele > ELE_NEUTRAL && !sd->def_ele)
			sd->def_ele = w->pdef_ele;
	}
	sd->double_rate += sd->double_add_rate;
	sd->perfect_hit += sd->perfect_hit_add;
	sd->get_zeny_num = (sd->get_zeny_num + sd->get_zeny_add_num > 100) ? 100 : (sd->get_zeny_num + sd->get_zeny_add_num);
	sd->get_zeny_num2 = (sd->get_zeny_num2 + sd->get_zeny_add_num2 > 100) ? 100 : (sd->get_zeny_num2 + sd->get_zeny_add_num2);
	sd->splash_range += sd->splash_add_range;

	// 武器ATKサイズ補正
	for(w->i=0; w->i<MAX_SIZE_FIX; w->i++) {
		sd->atkmods[w->i]  = atkmods[w->i][sd->weapontype1];	// 右手
		sd->atkmods_[w->i] = atkmods[w->i][sd->weapontype2];	// 左手
	}
}

static void status_calc_pc_phase_job(struct map_session_data *sd, struct status_calc_pc_work *w)
{
	// jobボーナス分
	for(w->i=0; w->i<sd->status.job_level && w->i<MAX_LEVEL; w->i++) {
		if(job_db[sd->s_class.job].bonus[sd->s_class.upper][w->i] & 0x01)
			sd->paramb[0]++;
		if(job_db[sd->s_class.job].bonus[sd->s_class.upper][w->i] & 0x02)
			sd->paramb[1]++;
		if(job_db[sd->s_class.job].bonus[sd->s_class.upper][w->i] & 0x04)
			sd->paramb[2]++;
		if(job_db[sd->s_class.job].bonus[sd->s_class.upper][w->i] & 0x08)
			sd->paramb[3]++;
		if(job_db[sd->s_class.job].bonus[sd->s_class.upper][w->i] & 0x10)
			sd->paramb[4]++;
		if(job_db[sd->s_class.job].bonus[sd->s_class.upper][w->i] & 0x20)
			sd->paramb[5]++;
		if(job_db[sd->s_class.job].bonus[sd->s_class.upper][w->i] & 0x040)
			sd->paramb[6]++;
		if(job_db[sd->s_class.job].bonus[sd->s_class.upper][w->i] & 0x080)
			sd->paramb[7]++;
		if(job_db[sd->s_class.job].bonus[sd->s_class.upper][w->i] & 0x100)
			sd->paramb[8]++;
		if(job_db[sd->s_class.job].bonus[sd->s_class.upper][w->i] & 0x200)
			sd->paramb[9]++;
		if(job_db[sd->s_class.job].bonus[sd->s_class.upper][w->i] & 0x400)
			sd->paramb[10]++;
		if(job_db[sd->s_class.job].bonus[sd->s_class.upper][w->i] & 0x800)
			sd->paramb[11]++;
	}

	if((w->skill = pc_checkskill(sd,AC_OWL)) > 0) {	// ふくろうの目
		sd->paramb[4] += w->skill;
	}
	if(pc_checkskill(sd,BS_HILTBINDING)) {	// ヒルトバインディング
		sd->paramb[0] += 1;
		// 本鯖未実装のためコメントアウト
		//sd->watk += 4;
	}
	if((w->skill = pc_checkskill(sd,SA_DRAGONOLOGY)) > 0) {	// ドラゴノロジー
		sd->paramb[3] += (w->skill+1)>>1;
	}
	if((w->skill = pc_checkskill(sd,RA_RESEARCHTRAP)) > 0) {	// トラップ研究
		sd->paramb[3] += w->skill;
	}
	if(pc_checkskill(sd,SU_POWEROFLAND) > 0) {	// 大地の力
		sd->paramb[3] += 7;
	}
	if((w->skill = pc_checkskill(sd,NW_GRENADE_MASTERY)) > 0) {	// グレネードマスタリー
		sd->paramb[10] += w->skill;
	}
	if((w->skill = pc_checkskill(sd,SOA_SOUL_MASTERY)) > 0) {	// 霊道術修練
		sd->paramb[9] += w->skill;
	}
#ifndef PRE_RENEWAL
	if((w->skill = pc_checkskill(sd,SG_STAR_BLESS)) > 0 && (battle_config.allow_skill_without_day || is_day_of_star())) {	// 星の祝福
		sd->paramb[0] += w->skill * 2;
		sd->paramb[1] += w->skill * 2;
		sd->paramb[2] += w->skill * 2;
		sd->paramb[3] += w->skill * 2;
		sd->paramb[4] += w->skill * 2;
		sd->paramb[5] += w->skill * 2;
	} else if((w->skill = pc_checkskill(sd,SG_SUN_BLESS)) > 0 && (battle_config.allow_skill_without_day || is_day_of_sun())) {	// 太陽の祝福
		sd->paramb[0] += w->skill * 2;
		sd->paramb[2] += w->skill * 2;
		sd->paramb[4] += w->skill * 2;
	} else if((w->skill = pc_checkskill(sd,SG_MOON_BLESS)) > 0 && (battle_config.allow_skill_without_day || is_day_of_moon())) {	// 月の祝福
		sd->paramb[1] += w->skill * 2;
		sd->paramb[3] += w->skill * 2;
		sd->paramb[5] += w->skill * 2;
	}
#endif

	// マーダラーボーナス
	if(battle_config.pk_murderer_point > 0) {
		int point = ranking_get_point(sd,RK_PK);
		if(point >= battle_config.pk_murderer_point * 4) {
			sd->paramb[0] += 5;
			sd->paramb[1] += 5;
			sd->paramb[2] += 5;
			sd->paramb[3] += 5;
			sd->paramb[4] += 5;
			sd->paramb[5] += 5;
			sd->atk_rate  += 10;
			sd->matk_rate += 10;
		} else if(point >= battle_config.pk_murderer_point) {
			sd->paramb[0] += 3;
			sd->paramb[1] += 3;
			sd->paramb[2] += 3;
			sd->paramb[3] += 3;
			sd->paramb[4] += 3;
			sd->paramb[5] += 3;
			sd->atk_rate  += 10;
			sd->matk_rate += 10;
		}
	}
	// 1度も死んでないJob70スパノビor拡張スパノビに+10
	if(((sd->s_class.job == PC_JOB_SNV && sd->status.job_level >= 70) || sd->s_class.job == PC_JOB_ESNV) && sd->status.die_counter == 0) {
		sd->paramb[0] += 10;
		sd->paramb[1] += 10;
		sd->paramb[2] += 10;
		sd->paramb[3] += 10;
		sd->paramb[4] += 10;
		sd->paramb[5] += 10;
	}

	// ギルドスキル
	if(battle_config.guild_hunting_skill_available)
	{
		struct guild *g = guild_search(sd->status.guild_id);	// ギルド取得
		struct map_session_data *gmsd = NULL;

		if(g)
			gmsd = guild_get_guildmaster_sd(g);

		// ギルド有 && マスター接続 && 自分!=マスター && 同じマップ
		if(g && gmsd && (battle_config.allow_me_guild_skill == 1 || gmsd != sd) && sd->bl.m == gmsd->bl.m)
		{
			if(battle_config.guild_skill_check_range) {	// 距離判定を行う
				int dx = abs(sd->bl.x - gmsd->bl.x);
				int dy = abs(sd->bl.y - gmsd->bl.y);
				int range;

				if(battle_config.guild_skill_effective_range > 0) {	// 同一距離で計算
					range = battle_config.guild_skill_effective_range;
					if(dx <= range && dy <= range) {
						sd->paramb[0] += guild_checkskill(g,GD_LEADERSHIP);	// w->str
						sd->paramb[1] += guild_checkskill(g,GD_SOULCOLD);	// agi
						sd->paramb[2] += guild_checkskill(g,GD_GLORYWOUNDS);	// vit
						sd->paramb[4] += guild_checkskill(g,GD_HAWKEYES);	// w->dex
						sd->under_the_influence_of_the_guild_skill = range+1;	// 0>で影響下,重なる場合もあるので+1
					} else {
						sd->under_the_influence_of_the_guild_skill = 0;
					}
				} else {	// 個別距離
					int min_range = 0x7fffffff;
					range = skill_get_range(GD_LEADERSHIP,guild_skill_get_lv(g,GD_LEADERSHIP));
					if(dx <= range && dy <= range) {
						sd->paramb[0] += guild_checkskill(g,GD_LEADERSHIP);	// w->str
						if(min_range > range) min_range = range;
					}
					range = skill_get_range(GD_SOULCOLD,guild_skill_get_lv(g,GD_SOULCOLD));
					if(dx <= range && dy <= range) {
						sd->paramb[1] += guild_checkskill(g,GD_SOULCOLD);	// agi
						if(min_range > range) min_range = range;
					}
					range = skill_get_range(GD_GLORYWOUNDS,guild_skill_get_lv(g,GD_GLORYWOUNDS));
					if(dx <= range && dy <= range) {
						sd->paramb[2] += guild_checkskill(g,GD_GLORYWOUNDS);	// vit
						if(min_range > range) min_range = range;
					}

					range = skill_get_range(GD_HAWKEYES,guild_skill_get_lv(g,GD_HAWKEYES));
					if(dx <= range && dy <= range) {
						sd->paramb[4] += guild_checkskill(g,GD_HAWKEYES);	// w->dex
						if(min_range > range) min_range = range;
					}
					if(min_range == 0x7fffffff)
						sd->under_the_influence_of_the_guild_skill = 0;
					else
						sd->under_the_influence_of_the_guild_skill = min_range+1;
				}
			} else {	// マップ全体
				sd->paramb[0] += guild_checkskill(g,GD_LEADERSHIP);	// w->str
				sd->paramb[1] += guild_checkskill(g,GD_SOULCOLD);	// agi
				sd->paramb[2] += guild_checkskill(g,GD_GLORYWOUNDS);	// vit
				sd->paramb[4] += guild_checkskill(g,GD_HAWKEYES);	// w->dex
				sd->under_the_influence_of_the_guild_skill = battle_config.guild_skill_effective_range+1;
			}
		} else {
			sd->under_the_influence_of_the_guild_skill = 0;
		}
	} else {	// マップが違ったり…無効だったり
		sd->under_the_influence_of_the_guild_skill = 0;
	}
}

static void status_calc_pc_phase_sc_base(struct map_session_data *sd, struct status_calc_pc_work *w)
{
	// ステータス変化による基本パラメータ補正
	if(sd->sc.count) {
		// 集中力向上
		if(sd->sc.data[SC_CONCENTRATE].timer != -1 && sd->sc.data[SC_QUAGMIRE].timer == -1) {
			sd->paramb[1] += (sd->status.agi+sd->paramb[1]+sd->parame[1]-sd->paramcard[1])*(2+sd->sc.data[SC_CONCENTRATE].val1)/100;
			sd->paramb[4] += (sd->status.dex+sd->paramb[4]+sd->parame[4]-sd->paramcard[4])*(2+sd->sc.data[SC_CONCENTRATE].val1)/100;
		}
		// ゴスペルALL+20
		if(sd->sc.data[SC_INCALLSTATUS].timer != -1) {
			sd->paramb[0] += sd->sc.data[SC_INCALLSTATUS].val1;
			sd->paramb[1] += sd->sc.data[SC_INCALLSTATUS].val1;
			sd->paramb[2] += sd->sc.data[SC_INCALLSTATUS].val1;
			sd->paramb[3] += sd->sc.data[SC_INCALLSTATUS].val1;
			sd->paramb[4] += sd->sc.data[SC_INCALLSTATUS].val1;
			sd->paramb[5] += sd->sc.data[SC_INCALLSTATUS].val1;
		}

		// 上位一次職の魂
		if(sd->sc.data[SC_HIGH].timer != -1) {
			if(sd->status.base_level < 60) {
				if(sd->status.str < sd->status.base_level-10)  sd->paramb[0] += sd->status.base_level-10 - sd->status.str;
				if(sd->status.agi < sd->status.base_level-10)  sd->paramb[1] += sd->status.base_level-10 - sd->status.agi;
				if(sd->status.vit < sd->status.base_level-10)  sd->paramb[2] += sd->status.base_level-10 - sd->status.vit;
				if(sd->status.int_ < sd->status.base_level-10) sd->paramb[3] += sd->status.base_level-10 - sd->status.int_;
				if(sd->status.dex < sd->status.base_level-10)  sd->paramb[4] += sd->status.base_level-10 - sd->status.dex;
				if(sd->status.luk < sd->status.base_level-10)  sd->paramb[5] += sd->status.base_level-10 - sd->status.luk;
			}
			else {
				if(sd->status.str < 50)  sd->paramb[0] += 50 - sd->status.str;
				if(sd->status.agi < 50)  sd->paramb[1] += 50 - sd->status.agi;
				if(sd->status.vit < 50)  sd->paramb[2] += 50 - sd->status.vit;
				if(sd->status.int_ < 50) sd->paramb[3] += 50 - sd->status.int_;
				if(sd->status.dex < 50)  sd->paramb[4] += 50 - sd->status.dex;
				if(sd->status.luk < 50)  sd->paramb[5] += 50 - sd->status.luk;
			}
		}

		// 食事用
		if(sd->sc.data[SC_MEAL_INCSTR2].timer != -1)
			sd->paramb[0] += sd->sc.data[SC_MEAL_INCSTR2].val1;
		else if(sd->sc.data[SC_MEAL_INCSTR].timer != -1)
			sd->paramb[0] += sd->sc.data[SC_MEAL_INCSTR].val1;
		if(sd->sc.data[SC_MEAL_INCAGI2].timer != -1)
			sd->paramb[1] += sd->sc.data[SC_MEAL_INCAGI2].val1;
		else if(sd->sc.data[SC_MEAL_INCAGI].timer != -1)
			sd->paramb[1] += sd->sc.data[SC_MEAL_INCAGI].val1;
		if(sd->sc.data[SC_MEAL_INCVIT2].timer != -1)
			sd->paramb[2] += sd->sc.data[SC_MEAL_INCVIT2].val1;
		else if(sd->sc.data[SC_MEAL_INCVIT].timer != -1)
			sd->paramb[2] += sd->sc.data[SC_MEAL_INCVIT].val1;
		if(sd->sc.data[SC_MEAL_INCINT2].timer != -1)
			sd->paramb[3] += sd->sc.data[SC_MEAL_INCINT2].val1;
		else if(sd->sc.data[SC_MEAL_INCINT].timer != -1)
			sd->paramb[3] += sd->sc.data[SC_MEAL_INCINT].val1;
		if(sd->sc.data[SC_MEAL_INCDEX2].timer != -1)
			sd->paramb[4] += sd->sc.data[SC_MEAL_INCDEX2].val1;
		else if(sd->sc.data[SC_MEAL_INCDEX].timer != -1)
			sd->paramb[4] += sd->sc.data[SC_MEAL_INCDEX].val1;
		if(sd->sc.data[SC_MEAL_INCLUK2].timer != -1)
			sd->paramb[5] += sd->sc.data[SC_MEAL_INCLUK2].val1;
		else if(sd->sc.data[SC_MEAL_INCLUK].timer != -1)
			sd->paramb[5] += sd->sc.data[SC_MEAL_INCLUK].val1;

		// タイリギのスパート状態 STR+10
		if(sd->sc.data[SC_SPURT].timer != -1)
			sd->paramb[0] += 10;

		// ギルドスキル 臨戦態勢
		if(sd->sc.data[SC_BATTLEORDER].timer != -1) {
			sd->paramb[0] += 5*sd->sc.data[SC_BATTLEORDER].val1;
			sd->paramb[3] += 5*sd->sc.data[SC_BATTLEORDER].val1;
			sd->paramb[4] += 5*sd->sc.data[SC_BATTLEORDER].val1;
		}

		if(sd->sc.data[SC_CHASEWALK_STR].timer != -1)
			sd->paramb[0] += sd->sc.data[SC_CHASEWALK_STR].val1;

		if(sd->sc.data[SC_INCREASEAGI].timer != -1)	// 速度増加
			sd->paramb[1] += 2+sd->sc.data[SC_INCREASEAGI].val1;

		if(sd->sc.data[SC_DECREASEAGI].timer != -1)	// 速度減少（オーバースキル仕様はAGI-50）
			sd->paramb[1] -= (sd->sc.data[SC_DECREASEAGI].val2)? 50: 2+sd->sc.data[SC_DECREASEAGI].val1;

		if(sd->sc.data[SC_ADORAMUS].timer != -1)	// アドラムス
			sd->paramb[1] -= 2+sd->sc.data[SC_ADORAMUS].val1;

		if(sd->sc.data[SC_ARCLOUSEDASH].timer != -1)	// アクラウスダッシュ
			sd->paramb[1] += sd->sc.data[SC_ARCLOUSEDASH].val2;

		if(sd->sc.data[SC_BLESSING].timer != -1) {	// ブレッシング
			sd->paramb[0] += sd->sc.data[SC_BLESSING].val1;
			sd->paramb[3] += sd->sc.data[SC_BLESSING].val1;
			sd->paramb[4] += sd->sc.data[SC_BLESSING].val1;
		}
		if(sd->sc.data[SC_NEN].timer != -1) {	// 念
			sd->paramb[0] += sd->sc.data[SC_NEN].val1;
			sd->paramb[3] += sd->sc.data[SC_NEN].val1;
		}
		if(sd->sc.data[SC_SUITON].timer != -1) {	// 水遁
			if(sd->sc.data[SC_SUITON].val3)
				sd->paramb[1] += sd->sc.data[SC_SUITON].val3;
		}

		if(sd->sc.data[SC_GLORIA].timer != -1)	// グロリア
			sd->paramb[5] += 30;

		if(sd->sc.data[SC_LOUD].timer != -1 && sd->sc.data[SC_QUAGMIRE].timer == -1)	// ラウドボイス
			sd->paramb[0] += 4;

		if(sd->sc.data[SC_TRUESIGHT].timer != -1) {	// トゥルーサイト
			sd->paramb[0] += 5;
			sd->paramb[1] += 5;
			sd->paramb[2] += 5;
			sd->paramb[3] += 5;
			sd->paramb[4] += 5;
			sd->paramb[5] += 5;
		}
		if(sd->sc.data[SC_INCREASING].timer != -1) { // インクリージングアキュラシー
			sd->paramb[1] += 4;
			sd->paramb[4] += 4;
		}

		// ディフェンス
		if(sd->sc.data[SC_DEFENCE].timer != -1)
			sd->paramb[2] += sd->sc.data[SC_DEFENCE].val1*2;

		if(sd->sc.data[SC_QUAGMIRE].timer != -1) {	// クァグマイア
			short subagi = 0;
			short subdex = 0;
#ifdef PRE_RENEWAL
			subagi = sd->status.agi * sd->sc.data[SC_QUAGMIRE].val1*10 / 100;
			subdex = sd->status.dex * sd->sc.data[SC_QUAGMIRE].val1*10 / 100;
#else
			subagi = (sd->status.agi/2 < sd->sc.data[SC_QUAGMIRE].val1*10) ? sd->status.agi/2 : sd->sc.data[SC_QUAGMIRE].val1*10;
			subdex = (sd->status.dex/2 < sd->sc.data[SC_QUAGMIRE].val1*10) ? sd->status.dex/2 : sd->sc.data[SC_QUAGMIRE].val1*10;
#endif
			if(map[sd->bl.m].flag.pvp || map[sd->bl.m].flag.gvg) {
				subagi /= 2;
				subdex /= 2;
			}
			sd->paramb[1] -= subagi;
			sd->paramb[4] -= subdex;
		}

		// マーシュオブアビス
		if(sd->sc.data[SC_MARSHOFABYSS].timer != -1) {
			sd->paramb[1] -= sd->status.agi * (sd->sc.data[SC_MARSHOFABYSS].val3 / 2) / 100;
			sd->paramb[4] -= sd->status.dex * (sd->sc.data[SC_MARSHOFABYSS].val3 / 2) / 100;
		}

		if(sd->sc.data[SC_MARIONETTE].timer != -1) {
			sd->paramb[0] -= sd->status.str/2;
			sd->paramb[1] -= sd->status.agi/2;
			sd->paramb[2] -= sd->status.vit/2;
			sd->paramb[3] -= sd->status.int_/2;
			sd->paramb[4] -= sd->status.dex/2;
			sd->paramb[5] -= sd->status.luk/2;
		}

		if(sd->sc.data[SC_MARIONETTE2].timer != -1)
		{
			struct map_session_data* ssd = map_id2sd(sd->sc.data[SC_MARIONETTE2].val2);
			if(ssd) {
				if(battle_config.marionette_type) {
					sd->paramb[0] += ssd->status.str/2;
					sd->paramb[1] += ssd->status.agi/2;
					sd->paramb[2] += ssd->status.vit/2;
					sd->paramb[3] += ssd->status.int_/2;
					sd->paramb[4] += ssd->status.dex/2;
					sd->paramb[5] += ssd->status.luk/2;
				} else if(map[sd->bl.m].flag.pk) {
					// ＰＫマップのMC制限
					// w->str
					if(sd->paramb[0]+sd->parame[0]+sd->status.str < battle_config.max_marionette_pk_str)
					{
						sd->paramb[0] += ssd->status.str/2;
						if(sd->paramb[0]+sd->parame[0]+sd->status.str > battle_config.max_marionette_pk_str)
							sd->paramb[0] = battle_config.max_marionette_pk_str - sd->status.str;
					}
					// agi
					if(sd->paramb[1]+sd->parame[1]+sd->status.agi < battle_config.max_marionette_pk_agi)
					{
						sd->paramb[1] += ssd->status.agi/2;
						if(sd->paramb[1]+sd->parame[1]+sd->status.agi > battle_config.max_marionette_pk_agi)
							sd->paramb[1] = battle_config.max_marionette_pk_agi - sd->status.agi;
					}
					// vit
					if(sd->paramb[2]+sd->parame[2]+sd->status.vit < battle_config.max_marionette_pk_vit)
					{
						sd->paramb[2] += ssd->status.vit/2;
						if(sd->paramb[2]+sd->parame[2]+sd->status.vit > battle_config.max_marionette_pk_vit)
							sd->paramb[2] = battle_config.max_marionette_pk_vit - sd->status.vit;
					}
					// int
					if(sd->paramb[3]+sd->parame[3]+sd->status.int_ < battle_config.max_marionette_pk_int)
					{
						sd->paramb[3] += ssd->status.int_/2;
						if(sd->paramb[3]+sd->parame[3]+sd->status.int_ > battle_config.max_marionette_pk_int)
							sd->paramb[3] = battle_config.max_marionette_pk_int - sd->status.int_;
					}
					// w->dex
					if(sd->paramb[4]+sd->parame[4]+sd->status.dex < battle_config.max_marionette_pk_dex)
					{
						sd->paramb[4] += ssd->status.dex/2;
						if(sd->paramb[4]+sd->parame[4]+sd->status.dex > battle_config.max_marionette_pk_dex)
							sd->paramb[4] = battle_config.max_marionette_pk_dex - sd->status.dex;
					}
					// luk
					if(sd->paramb[5]+sd->parame[5]+sd->status.luk < battle_config.max_marionette_pk_luk)
					{
						sd->paramb[5] += ssd->status.luk/2;
						if(sd->paramb[5]+sd->parame[5]+sd->status.luk > battle_config.max_marionette_pk_luk)
							sd->paramb[5] = battle_config.max_marionette_pk_luk - sd->status.luk;
					}
				} else if(map[sd->bl.m].flag.pvp) {
					// ＰＶＰマップのMC制限
					// w->str
					if(sd->paramb[0]+sd->parame[0]+sd->status.str < battle_config.max_marionette_pvp_str)
					{
						sd->paramb[0] += ssd->status.str/2;
						if(sd->paramb[0]+sd->parame[0]+sd->status.str > battle_config.max_marionette_pvp_str)
							sd->paramb[0] = battle_config.max_marionette_pvp_str - sd->status.str;
					}
					// agi
					if(sd->paramb[1]+sd->parame[1]+sd->status.agi < battle_config.max_marionette_pvp_agi)
					{
						sd->paramb[1] += ssd->status.agi/2;
						if(sd->paramb[1]+sd->parame[1]+sd->status.agi > battle_config.max_marionette_pvp_agi)
							sd->paramb[1] = battle_config.max_marionette_pvp_agi - sd->status.agi;
					}
					// vit
					if(sd->paramb[2]+sd->parame[2]+sd->status.vit < battle_config.max_marionette_pvp_vit)
					{
						sd->paramb[2] += ssd->status.vit/2;
						if(sd->paramb[2]+sd->parame[2]+sd->status.vit > battle_config.max_marionette_pvp_vit)
							sd->paramb[2] = battle_config.max_marionette_pvp_vit - sd->status.vit;
					}
					// int
					if(sd->paramb[3]+sd->parame[3]+sd->status.int_ < battle_config.max_marionette_pvp_int)
					{
						sd->paramb[3] += ssd->status.int_/2;
						if(sd->paramb[3]+sd->parame[3]+sd->status.int_ > battle_config.max_marionette_pvp_int)
							sd->paramb[3] = battle_config.max_marionette_pvp_int - sd->status.int_;
					}
					// w->dex
					if(sd->paramb[4]+sd->parame[4]+sd->status.dex < battle_config.max_marionette_pvp_dex)
					{
						sd->paramb[4] += ssd->status.dex/2;
						if(sd->paramb[4]+sd->parame[4]+sd->status.dex > battle_config.max_marionette_pvp_dex)
							sd->paramb[4] = battle_config.max_marionette_pvp_dex - sd->status.dex;
					}
					// luk
					if(sd->paramb[5]+sd->parame[5]+sd->status.luk < battle_config.max_marionette_pvp_luk)
					{
						sd->paramb[5] += ssd->status.luk/2;
						if(sd->paramb[5]+sd->parame[5]+sd->status.luk > battle_config.max_marionette_pvp_luk)
							sd->paramb[5] = battle_config.max_marionette_pvp_luk - sd->status.luk;
					}
				} else if(map[sd->bl.m].flag.gvg) {
					// ＧＶＧマップのMC制限
					// w->str
					if(sd->paramb[0]+sd->parame[0]+sd->status.str < battle_config.max_marionette_gvg_str)
					{
						sd->paramb[0] += ssd->status.str/2;
						if(sd->paramb[0]+sd->parame[0]+sd->status.str > battle_config.max_marionette_gvg_str)
							sd->paramb[0] = battle_config.max_marionette_gvg_str - sd->status.str;
					}
					// agi
					if(sd->paramb[1]+sd->parame[1]+sd->status.agi < battle_config.max_marionette_gvg_agi)
					{
						sd->paramb[1] += ssd->status.agi/2;
						if(sd->paramb[1]+sd->parame[1]+sd->status.agi > battle_config.max_marionette_gvg_agi)
							sd->paramb[1] = battle_config.max_marionette_gvg_agi - sd->status.agi;
					}
					// vit
					if(sd->paramb[2]+sd->parame[2]+sd->status.vit < battle_config.max_marionette_gvg_vit)
					{
						sd->paramb[2] += ssd->status.vit/2;
						if(sd->paramb[2]+sd->parame[2]+sd->status.vit > battle_config.max_marionette_gvg_vit)
							sd->paramb[2] = battle_config.max_marionette_gvg_vit - sd->status.vit;
					}
					// int
					if(sd->paramb[3]+sd->parame[3]+sd->status.int_ < battle_config.max_marionette_gvg_int)
					{
						sd->paramb[3] += ssd->status.int_/2;
						if(sd->paramb[3]+sd->parame[3]+sd->status.int_ > battle_config.max_marionette_gvg_int)
							sd->paramb[3] = battle_config.max_marionette_gvg_int - sd->status.int_;
					}
					// w->dex
					if(sd->paramb[4]+sd->parame[4]+sd->status.dex < battle_config.max_marionette_gvg_dex)
					{
						sd->paramb[4] += ssd->status.dex/2;
						if(sd->paramb[4]+sd->parame[4]+sd->status.dex > battle_config.max_marionette_gvg_dex)
							sd->paramb[4] = battle_config.max_marionette_gvg_dex - sd->status.dex;
					}
					// luk
					if(sd->paramb[5]+sd->parame[5]+sd->status.luk < battle_config.max_marionette_gvg_luk)
					{
						sd->paramb[5] += ssd->status.luk/2;
						if(sd->paramb[5]+sd->parame[5]+sd->status.luk > battle_config.max_marionette_gvg_luk)
							sd->paramb[5] = battle_config.max_marionette_gvg_luk - sd->status.luk;
					}
				} else {
					// 通常のMC制限
					// w->str
					if(sd->paramb[0]+sd->parame[0]+sd->status.str < battle_config.max_marionette_str)
					{
						sd->paramb[0] += ssd->status.str/2;
						if(sd->paramb[0]+sd->parame[0]+sd->status.str > battle_config.max_marionette_str)
							sd->paramb[0] = battle_config.max_marionette_str - sd->status.str;
					}
					// agi
					if(sd->paramb[1]+sd->parame[1]+sd->status.agi < battle_config.max_marionette_agi)
					{
						sd->paramb[1] += ssd->status.agi/2;
						if(sd->paramb[1]+sd->parame[1]+sd->status.agi > battle_config.max_marionette_agi)
							sd->paramb[1] = battle_config.max_marionette_agi - sd->status.agi;
					}
					// vit
					if(sd->paramb[2]+sd->parame[2]+sd->status.vit < battle_config.max_marionette_vit)
					{
						sd->paramb[2] += ssd->status.vit/2;
						if(sd->paramb[2]+sd->parame[2]+sd->status.vit > battle_config.max_marionette_vit)
							sd->paramb[2] = battle_config.max_marionette_vit - sd->status.vit;
					}
					// int
					if(sd->paramb[3]+sd->parame[3]+sd->status.int_ < battle_config.max_marionette_int)
					{
						sd->paramb[3] += ssd->status.int_/2;
						if(sd->paramb[3]+sd->parame[3]+sd->status.int_ > battle_config.max_marionette_int)
							sd->paramb[3] = battle_config.max_marionette_int - sd->status.int_;
					}
					// w->dex
					if(sd->paramb[4]+sd->parame[4]+sd->status.dex < battle_config.max_marionette_dex)
					{
						sd->paramb[4] += ssd->status.dex/2;
						if(sd->paramb[4]+sd->parame[4]+sd->status.dex > battle_config.max_marionette_dex)
							sd->paramb[4] = battle_config.max_marionette_dex - sd->status.dex;
					}
					// luk
					if(sd->paramb[5]+sd->parame[5]+sd->status.luk < battle_config.max_marionette_luk)
					{
						sd->paramb[5] += ssd->status.luk/2;
						if(sd->paramb[5]+sd->parame[5]+sd->status.luk > battle_config.max_marionette_luk)
							sd->paramb[5] = battle_config.max_marionette_luk - sd->status.luk;
					}
				}
			}
		}
		if(sd->sc.data[SC_WE_FEMALE].timer != -1) {	// あなたに尽くします
			if(sd->sc.data[SC_WE_FEMALE].val2 == 1) {
				// 自分は全て-1
				sd->paramb[0]--;
				sd->paramb[1]--;
				sd->paramb[2]--;
				sd->paramb[3]--;
				sd->paramb[4]--;
				sd->paramb[5]--;
			} else if(sd->sc.data[SC_WE_FEMALE].val2 == 2) {
				// 相手は全て+1
				sd->paramb[0]++;
				sd->paramb[1]++;
				sd->paramb[2]++;
				sd->paramb[3]++;
				sd->paramb[4]++;
				sd->paramb[5]++;
			}
		}
		if(sd->sc.data[SC_GIANTGROWTH].timer != -1)	// ジャイアントグロース
			sd->paramb[0] += 30;
		if(sd->sc.data[SC_LAUDAAGNUS].timer != -1)	// ラウダアグヌス
			sd->paramb[2] += sd->sc.data[SC_LAUDAAGNUS].val2;
		if(sd->sc.data[SC_LAUDARAMUS].timer != -1)	// ラウダラムス
			sd->paramb[5] += sd->sc.data[SC_LAUDARAMUS].val2;
		if(sd->sc.data[SC_INSPIRATION].timer != -1) {	// インスピレーション
			int param = sd->status.base_level / 10 + sd->status.job_level / 5;
			sd->paramb[0] += param;
			sd->paramb[1] += param;
			sd->paramb[2] += param;
			sd->paramb[3] += param;
			sd->paramb[4] += param;
			sd->paramb[5] += param;
		}
		if(sd->sc.data[SC_MANDRAGORA].timer != -1)	// ハウリングオブマンドラゴラ
			sd->paramb[3] -= sd->sc.data[SC_MANDRAGORA].val2;
		if(sd->sc.data[SC_BANANA_BOMB].timer != -1)		// バナナ爆弾
			sd->paramb[5] -= sd->paramb[5] * sd->sc.data[SC_BANANA_BOMB].val1 / 100;
		if(sd->sc.data[SC_SAVAGE_STEAK].timer != -1)			// サベージの丸焼き
			sd->paramb[0] += sd->sc.data[SC_SAVAGE_STEAK].val1;
		if(sd->sc.data[SC_DROCERA_HERB_STEAMED].timer != -1)	// ドロセラのハーブ煮
			sd->paramb[1] += sd->sc.data[SC_DROCERA_HERB_STEAMED].val1;
		if(sd->sc.data[SC_MINOR_BBQ].timer != -1)				// ミノタウロスの牛カルビ
			sd->paramb[2] += sd->sc.data[SC_MINOR_BBQ].val1;
		if(sd->sc.data[SC_COCKTAIL_WARG_BLOOD].timer != -1)		// カクテルウォーグブラッド
			sd->paramb[3] += sd->sc.data[SC_COCKTAIL_WARG_BLOOD].val1;
		if(sd->sc.data[SC_SIROMA_ICE_TEA].timer != -1)			// シロマアイスティー
			sd->paramb[4] += sd->sc.data[SC_SIROMA_ICE_TEA].val1;
		if(sd->sc.data[SC_PUTTI_TAILS_NOODLES].timer != -1)		// プティットのしっぽ麺
			sd->paramb[5] += sd->sc.data[SC_PUTTI_TAILS_NOODLES].val1;
		if(sd->sc.data[SC_STOMACHACHE].timer != -1) {		// 腹痛
			sd->paramb[0] -= sd->sc.data[SC_STOMACHACHE].val1;
			sd->paramb[1] -= sd->sc.data[SC_STOMACHACHE].val1;
			sd->paramb[2] -= sd->sc.data[SC_STOMACHACHE].val1;
			sd->paramb[3] -= sd->sc.data[SC_STOMACHACHE].val1;
			sd->paramb[4] -= sd->sc.data[SC_STOMACHACHE].val1;
			sd->paramb[5] -= sd->sc.data[SC_STOMACHACHE].val1;
		}
		if(sd->sc.data[SC_HARMONIZE].timer != -1) {	// ハーモナイズ
			sd->paramb[0] -= sd->sc.data[SC_HARMONIZE].val2;
			sd->paramb[1] -= sd->sc.data[SC_HARMONIZE].val2;
			sd->paramb[2] -= sd->sc.data[SC_HARMONIZE].val2;
			sd->paramb[3] -= sd->sc.data[SC_HARMONIZE].val2;
			sd->paramb[4] -= sd->sc.data[SC_HARMONIZE].val2;
			sd->paramb[5] -= sd->sc.data[SC_HARMONIZE].val2;
		}
		if(sd->sc.data[SC_KYOUGAKU].timer != -1) {	// 幻術 -驚愕-
			sd->paramb[0] -= sd->sc.data[SC_KYOUGAKU].val2;
			sd->paramb[1] -= sd->sc.data[SC_KYOUGAKU].val2;
			sd->paramb[2] -= sd->sc.data[SC_KYOUGAKU].val2;
			sd->paramb[3] -= sd->sc.data[SC_KYOUGAKU].val2;
			sd->paramb[4] -= sd->sc.data[SC_KYOUGAKU].val2;
			sd->paramb[5] -= sd->sc.data[SC_KYOUGAKU].val2;
		}
		if(sd->sc.data[SC_BEYOND_OF_WARCRY].timer != -1) {	// ビヨンドオブウォークライ
			sd->paramb[0] += sd->sc.data[SC_BEYOND_OF_WARCRY].val4;
		}
		if(sd->sc.data[SC_MELODYOFSINK].timer != -1) {	// メロディーオブシンク
			sd->paramb[3] -= sd->sc.data[SC_MELODYOFSINK].val4;
		}
		if(sd->sc.data[SC_ALL_STAT_DOWN].timer != -1) {	// オールステータスダウン
			sd->paramb[0] -= sd->sc.data[SC_ALL_STAT_DOWN].val2;
			sd->paramb[1] -= sd->sc.data[SC_ALL_STAT_DOWN].val2;
			sd->paramb[2] -= sd->sc.data[SC_ALL_STAT_DOWN].val2;
			sd->paramb[3] -= sd->sc.data[SC_ALL_STAT_DOWN].val2;
			sd->paramb[4] -= sd->sc.data[SC_ALL_STAT_DOWN].val2;
			sd->paramb[5] -= sd->sc.data[SC_ALL_STAT_DOWN].val2;
		}
		if(sd->sc.data[SC_FULL_THROTTLE].timer != -1) {	// フルスロットル
			sd->paramb[0] += sd->status.str  * sd->sc.data[SC_FULL_THROTTLE].val2 / 100;
			sd->paramb[1] += sd->status.agi  * sd->sc.data[SC_FULL_THROTTLE].val2 / 100;
			sd->paramb[2] += sd->status.vit  * sd->sc.data[SC_FULL_THROTTLE].val2 / 100;
			sd->paramb[3] += sd->status.int_ * sd->sc.data[SC_FULL_THROTTLE].val2 / 100;
			sd->paramb[4] += sd->status.dex  * sd->sc.data[SC_FULL_THROTTLE].val2 / 100;
			sd->paramb[5] += sd->status.luk  * sd->sc.data[SC_FULL_THROTTLE].val2 / 100;
		}
		if(sd->sc.data[SC_UNIVERSESTANCE].timer != -1) {	// 宇宙の構え
			int add = sd->sc.data[SC_UNIVERSESTANCE].val2;
			sd->paramb[0] += add;
			sd->paramb[1] += add;
			sd->paramb[2] += add;
			sd->paramb[3] += add;
			sd->paramb[4] += add;
			sd->paramb[5] += add;
		}
		// レリギオ
		if(sd->sc.data[SC_RELIGIO].timer != -1) {
			sd->paramb[7] += sd->sc.data[SC_RELIGIO].val2;
			sd->paramb[8] += sd->sc.data[SC_RELIGIO].val3;
			sd->paramb[9] += sd->sc.data[SC_RELIGIO].val4;
		}
		// ベネディクトゥム
		if(sd->sc.data[SC_BENEDICTUM].timer != -1) {
			sd->paramb[6] += sd->sc.data[SC_BENEDICTUM].val2;
			sd->paramb[10] += sd->sc.data[SC_BENEDICTUM].val3;
			sd->paramb[11] += sd->sc.data[SC_BENEDICTUM].val4;
		}
		// マリンフェスティバル
		if(sd->sc.data[SC_MARINE_FESTIVAL].timer != -1) {
			sd->paramb[6] += sd->sc.data[SC_MARINE_FESTIVAL].val2;
			sd->paramb[10] += sd->sc.data[SC_MARINE_FESTIVAL].val3;
			sd->paramb[11] += sd->sc.data[SC_MARINE_FESTIVAL].val4;
		}
		// サンドフェスティバル
		if(sd->sc.data[SC_SANDY_FESTIVAL].timer != -1) {
			sd->paramb[7] += sd->sc.data[SC_SANDY_FESTIVAL].val2;
			sd->paramb[8] += sd->sc.data[SC_SANDY_FESTIVAL].val3;
			sd->paramb[9] += sd->sc.data[SC_SANDY_FESTIVAL].val4;
		}
	}

	sd->paramc[0]  = sd->status.str  + sd->paramb[0]  + sd->parame[0];
	sd->paramc[1]  = sd->status.agi  + sd->paramb[1]  + sd->parame[1];
	sd->paramc[2]  = sd->status.vit  + sd->paramb[2]  + sd->parame[2];
	sd->paramc[3]  = sd->status.int_ + sd->paramb[3]  + sd->parame[3];
	sd->paramc[4]  = sd->status.dex  + sd->paramb[4]  + sd->parame[4];
	sd->paramc[5]  = sd->status.luk  + sd->paramb[5]  + sd->parame[5];
	sd->paramc[6]  = sd->status.pow  + sd->paramb[6]  + sd->parame[6];
	sd->paramc[7]  = sd->status.sta  + sd->paramb[7]  + sd->parame[7];
	sd->paramc[8]  = sd->status.wis  + sd->paramb[8]  + sd->parame[8];
	sd->paramc[9]  = sd->status.spl  + sd->paramb[9]  + sd->parame[9];
	sd->paramc[10] = sd->status.con  + sd->paramb[10] + sd->parame[10];
	sd->paramc[11] = sd->status.crt  + sd->paramb[11] + sd->parame[11];

	for(w->i=0; w->i<6; w->i++) {
		if(sd->paramc[w->i] < 0)
			sd->paramc[w->i] = 0;
	}
}

static void status_calc_pc_phase_derived(struct map_session_data *sd, struct status_calc_pc_work *w)
{
	// BASEATK計算
	if( sd->status.weapon == WT_BOW ||
	    sd->status.weapon == WT_MUSICAL ||
	    sd->status.weapon == WT_WHIP ||
	    (sd->status.weapon >= WT_HANDGUN && sd->status.weapon <= WT_GRENADE) ) {
		w->str = sd->paramc[4];
		w->dex = sd->paramc[0];
	} else {
		w->str = sd->paramc[0];
		w->dex = sd->paramc[4];
	}
#ifdef PRE_RENEWAL
	w->dstr = w->str/10;

	sd->base_atk += w->str + w->dstr*w->dstr + w->dex/5 + sd->paramc[5]/5 + sd->paramc[6]*5;
	sd->matk1 += sd->paramc[3]+(sd->paramc[3]/5)*(sd->paramc[3]/5)+sd->paramc[9]*5;
	sd->matk2 += sd->paramc[3]+(sd->paramc[3]/7)*(sd->paramc[3]/7)+sd->paramc[9]*5;

	if(sd->matk1 < sd->matk2) {
		int temp = sd->matk2;
		sd->matk2 = sd->matk1;
		sd->matk1 = temp;
	}

	sd->hit      += sd->paramc[4] + sd->status.base_level + sd->paramc[10]*2;
	sd->flee     += sd->paramc[1] + sd->status.base_level + sd->paramc[10]*2;
	sd->def2     += sd->paramc[2];
	sd->mdef2    += sd->paramc[3];
	sd->flee2    += sd->paramc[5] + 10;
	sd->critical += sd->paramc[5] * 3 + 10;
#else
	w->dstr = sd->paramc[3]/7;

	sd->base_atk += (int)(w->str + w->dex/5. + sd->paramc[5]/3. + sd->paramc[6]*5);
	sd->matk2    += sd->paramc[3] + (w->dstr*w->dstr)/3 + sd->paramc[4]/5 + sd->paramc[5]/3 + sd->paramc[9]*5;

	sd->hit      += 175 + sd->paramc[4] + sd->paramc[5]/3 + sd->paramc[10]*2 + sd->status.base_level;
	sd->flee     += 100 + sd->paramc[1] + sd->paramc[5]/5 + sd->paramc[10]*2 + sd->status.base_level;
	sd->def2     += (int)(sd->paramc[2]/2. + sd->status.base_level/2. + sd->paramc[1]/5.);
	sd->mdef2    += (int)(sd->paramc[3] + sd->status.base_level/4. + sd->paramc[2]/5. + sd->paramc[4]/5.);
	if(pc_isdoram(sd))
		sd->flee2    += sd->paramc[5] * 120 / 100 + 10;
	else
		sd->flee2    += sd->paramc[5] + 10;
	sd->critical += sd->paramc[5] / 3 * 10 + 10;
#endif
	sd->patk     += sd->paramc[6]/3 + sd->paramc[10]/5;
	sd->smatk    += sd->paramc[9]/3 + sd->paramc[10]/5;
	sd->res      += sd->paramc[7] + (sd->paramc[7]/3*5);
	sd->mres     += sd->paramc[8] + (sd->paramc[8]/3*5);
	sd->hplus    += sd->paramc[11];
	sd->crate    += sd->paramc[11]/3;

	// アイテム補正
	if(sd->sc.count > 0) {
		if(sd->sc.data[SC_MEAL_INCATK].timer != -1)
			sd->base_atk += sd->sc.data[SC_MEAL_INCATK].val1;
		if(sd->sc.data[SC_MEAL_INCMATK].timer != -1) {
			sd->matk1 += sd->sc.data[SC_MEAL_INCMATK].val1;
			sd->matk2 += sd->sc.data[SC_MEAL_INCMATK].val1;
		}
		if(sd->sc.data[SC_MEAL_INCHIT].timer != -1)
			sd->hit += sd->sc.data[SC_MEAL_INCHIT].val1;
		if(sd->sc.data[SC_MEAL_INCFLEE].timer != -1)
			sd->flee += sd->sc.data[SC_MEAL_INCFLEE].val1;
		if(sd->sc.data[SC_MEAL_INCFLEE2].timer != -1)
			sd->flee2 += sd->sc.data[SC_MEAL_INCFLEE2].val1;
		if(sd->sc.data[SC_MEAL_INCCRITICAL].timer != -1)
			sd->critical += sd->sc.data[SC_MEAL_INCCRITICAL].val1*10;
		if(sd->sc.data[SC_MEAL_INCDEF].timer != -1)
			sd->def += sd->sc.data[SC_MEAL_INCDEF].val1;
		if(sd->sc.data[SC_MEAL_INCMDEF].timer != -1)
			sd->mdef += sd->sc.data[SC_MEAL_INCMDEF].val1;
		if(sd->sc.data[SC_MONSTER_TRANSFORM].timer != -1 && sd->sc.data[SC_MONSTER_TRANSFORM].val1 == 1109)
			sd->hit += 5;
	}

	if(sd->sc.data[SC_MADNESSCANCEL].timer != -1) {	// マッドネスキャンセラー
		sd->base_atk += 100;
	}
	if(sd->sc.data[SC_GATLINGFEVER].timer != -1) {	// ガトリングフィーバー
		sd->base_atk += 20+(sd->sc.data[SC_GATLINGFEVER].val1*10);
	}
	if(sd->sc.data[SC_VOLCANO].timer != -1
#ifdef PRE_RENEWAL
		&& sd->def_ele == ELE_FIRE
#endif
	) {	// ボルケーノ
		sd->base_atk += sd->sc.data[SC_VOLCANO].val3;
	}
#ifdef PRE_RENEWAL
	if(sd->sc.data[SC_DRUMBATTLE].timer != -1) {	// 戦太鼓の響き
		sd->base_atk += sd->sc.data[SC_DRUMBATTLE].val2;
		//w->idx = sd->equip_index[EQUIP_INDEX_LARM];
		// 左手には適用しない
		//if(w->idx >= 0 && sd->inventory_data[w->idx] && sd->inventory_data[w->idx]->type == ITEMTYPE_ARMOR)
		//	sd->watk_ += sd->sc.data[SC_DRUMBATTLE].val2;
	}
#endif

	if(sd->base_atk < 1)
		sd->base_atk = 1;
	if(sd->critical_rate != 100)
		sd->critical = (sd->critical*sd->critical_rate)/100;
	if(sd->critical < 10)
		sd->critical = 10;
	if(sd->hit_rate != 100)
		sd->hit = (sd->hit*sd->hit_rate)/100;
	if(sd->hit < 1) sd->hit = 1;
	if(sd->flee_rate != 100)
		sd->flee = (sd->flee*sd->flee_rate)/100;
	if(sd->flee < 1) sd->flee = 1;
	if(sd->flee2_rate != 100)
		sd->flee2 = (sd->flee2*sd->flee2_rate)/100;
	if(sd->flee2 < 10) sd->flee2 = 10;
	if(sd->def_rate != 100)
		sd->def = (sd->def*sd->def_rate)/100;
	if(sd->def2_rate != 100)
		sd->def2 = (sd->def2*sd->def2_rate)/100;
	if(sd->def2 < 1) sd->def2 = 1;
	if(sd->mdef_rate != 100)
		sd->mdef = (sd->mdef*sd->mdef_rate)/100;
	if(sd->mdef2_rate != 100)
		sd->mdef2 = (sd->mdef2*sd->mdef2_rate)/100;
	if(sd->mdef2 < 1) sd->mdef2 = 1;

	// シングルアクション
	if(sd->status.weapon >= WT_HANDGUN && sd->status.weapon <= WT_GRENADE && (w->skill = pc_checkskill(sd,GS_SINGLEACTION)) > 0)
	{
		sd->hit += w->skill*2;
	}
	// 太陽と月と星の悪魔
	if((w->skill = pc_checkskill(sd,SG_DEVIL)) > 0 && sd->status.job_level >= 50)
	{
		clif_status_load_id(sd,SI_DEVIL,1);
	}

	// 太陽と月と星の融合
	if(sd->sc.data[SC_FUSION].timer != -1)
	{
		sd->perfect_hit += 100;
	}

	if(sd->sc.data[SC_WEDDING].timer != -1)
		w->b_class = PC_CLASS_WE;
	else if(sd->sc.data[SC_SANTA].timer != -1)
		w->b_class = PC_CLASS_ST;
	else if(sd->sc.data[SC_SUMMER].timer != -1)
		w->b_class = PC_CLASS_SU;

	if((w->skill = pc_checkskill(sd,AC_VULTURE)) > 0) {	// ワシの目
		sd->hit += w->skill;
		if(sd->status.weapon == WT_BOW)
			sd->range.attackrange += w->skill;
	}
	if((w->skill = pc_checkskill(sd,GS_SNAKEEYE)) > 0) {	// スネークアイ
		if(sd->status.weapon >= WT_HANDGUN && sd->status.weapon <= WT_GRENADE)
		{
			sd->range.attackrange += w->skill;
			sd->hit += w->skill;
		}
	}
	if((w->skill = pc_checkskill(sd,SU_SOULATTACK)) > 0) {	// ソウルアタック
		sd->range.attackrange = 13;
	}
	if((w->skill = pc_checkskill(sd,BS_WEAPONRESEARCH)) > 0)	// 武器研究の命中率増加
		sd->hit += w->skill*2;
	if((sd->status.weapon == WT_DAGGER || sd->status.weapon == WT_1HSWORD) && ((w->skill = pc_checkskill(sd,GN_TRAINING_SWORD)) > 0))	// 剣修練の命中率増加
		sd->hit += w->skill*3;

	if((sd->status.weapon == WT_1HSWORD || sd->status.weapon == WT_1HSPEAR || sd->status.weapon == WT_2HSPEAR) && (w->skill = pc_checkskill(sd,IG_SPEAR_SWORD_M)) > 0) {		// 槍＆片手剣修練
		sd->hit += w->skill*10;
	}

	if((w->skill = pc_checkskill(sd,CR_TRUST)) > 0) { // フェイス
		sd->status.max_hp    += w->skill*200;
		sd->subele[ELE_HOLY] += w->skill*5;
	}

	if((w->skill = pc_checkskill(sd,BS_SKINTEMPER)) > 0) { // スキンテンパリング
		sd->subele[ELE_FIRE]    += w->skill*4;
		sd->subele[ELE_NEUTRAL] += w->skill*1;
	}

	if(pc_checkskill(sd,SU_SPRITEMABLE) > 0) {	// にゃん魂
		sd->status.max_hp += 2000;
		sd->status.max_sp += 200;
		clif_status_load_id(sd,SI_SPRITEMABLE,1);
	}
	if(pc_checkskill(sd,SU_POWEROFSEA) > 0) {	// 海の力
		sd->status.max_hp += 1000;
		sd->status.max_sp += 100;
		if(pc_checkskill_summoner(sd, SU_POWEROFSEA) >= 20) {
			sd->status.max_hp += 3000;
			sd->status.max_sp += 300;
		}
	}

	// bAtkRange2,bAtkRangeRate2の射程計算
	sd->range.attackrange  += sd->range.add_attackrange;
	sd->range.attackrange_ += sd->range.add_attackrange;
	sd->range.attackrange  = sd->range.attackrange  * sd->range.add_attackrange_rate / 100;
	sd->range.attackrange_ = sd->range.attackrange_ * sd->range.add_attackrange_rate / 100;
	if(sd->range.attackrange < 1)  sd->range.attackrange  = 1;
	if(sd->range.attackrange_ < 1) sd->range.attackrange_ = 1;
	if(sd->range.attackrange < sd->range.attackrange_)
		sd->range.attackrange = sd->range.attackrange_;

	w->blv = (sd->status.base_level > 0)? sd->status.base_level - 1: 0;

	// 最大HP計算
	w->calc_val = job_db[sd->s_class.job].hp_base[w->blv] * (100 + sd->paramc[2]) / 100;

	if(pc_isupper(sd))	// 転生職の場合最大HP25%UP
		sd->status.max_hp += w->calc_val * battle_config.upper_hp_rate / 100;
	else if(pc_isbaby(sd))	// 養子の場合最大HP70%
		sd->status.max_hp += w->calc_val * battle_config.baby_hp_rate / 100;
	else
		sd->status.max_hp += w->calc_val * battle_config.normal_hp_rate / 100;

	sd->status.max_hp += sd->parame[2] - sd->paramcard[2];

	if(sd->hprate != 100)
		sd->status.max_hp = sd->status.max_hp * sd->hprate / 100;

	if((w->skill = pc_checkskill(sd,NV_BREAKTHROUGH)) > 0)	// ブレイクスルー
		sd->status.max_hp += (w->skill<5)? w->skill*350: 2000;
	if((w->skill = pc_checkskill(sd,NV_TRANSCENDENCE)) > 0)	// トランセンデンス
		sd->status.max_hp += (w->skill<5)? w->skill*350: 2000;

	if(sd->sc.data[SC_VENOMBLEED].timer != -1) {	// ベナムブリード
		sd->status.max_hp -= (int)((atn_bignumber)sd->status.max_hp * sd->sc.data[SC_VENOMBLEED].val2 / 100);
	}
	if(sd->sc.data[SC__WEAKNESS].timer != -1) {	// マスカレード：ウィークネス
		sd->status.max_hp -= (int)((atn_bignumber)sd->status.max_hp * (sd->sc.data[SC__WEAKNESS].val1 * 10) / 100);
	}
	if(sd->sc.data[SC_BERSERK].timer != -1) {	// バーサーク
		sd->status.max_hp *= 3;
	}
	if(sd->sc.data[SC_INCMHP2].timer != -1) {
		sd->status.max_hp = (int)((atn_bignumber)sd->status.max_hp * (100 + sd->sc.data[SC_INCMHP2].val1) / 100);
	}
	if(sd->sc.data[SC_SUPPORT_HPSP].timer != -1) {
		sd->status.max_hp = (int)((atn_bignumber)sd->status.max_hp * (100 + sd->sc.data[SC_SUPPORT_HPSP].val1) / 100);
	}
	if(sd->sc.data[SC_EPICLESIS].timer != -1) {		// エピクレシス
		sd->status.max_hp = (int)((atn_bignumber)sd->status.max_hp * (100 + sd->sc.data[SC_EPICLESIS].val2) / 100);
	}
	if(sd->sc.data[SC_EQC].timer != -1)
		sd->status.max_hp -= (int)((atn_bignumber)sd->status.max_hp * sd->sc.data[SC_EQC].val3 / 100);
	if(sd->sc.data[SC_LUNARSTANCE].timer != -1) {		// 月の構え
		sd->status.max_hp = (int)((atn_bignumber)sd->status.max_hp * (100 + sd->sc.data[SC_LUNARSTANCE].val2) / 100);
	}

	// 最大SP計算
	w->calc_val = job_db[sd->s_class.job].sp_base[w->blv] * (100 + sd->paramc[3]) / 100 + (sd->parame[3] - sd->paramcard[3]);

	if(pc_isupper(sd))	// 転生職の場合最大SP125%
		sd->status.max_sp += w->calc_val * battle_config.upper_sp_rate / 100;
	else if(pc_isbaby(sd))	// 養子の場合最大SP70%
		sd->status.max_sp += w->calc_val * battle_config.baby_sp_rate / 100;
	else
		sd->status.max_sp += w->calc_val * battle_config.normal_sp_rate / 100;

	if(sd->sprate != 100)
		sd->status.max_sp = sd->status.max_sp * sd->sprate / 100;

	if((w->skill = pc_checkskill(sd,HP_MEDITATIO)) > 0) // メディタティオ
		sd->status.max_sp += sd->status.max_sp * w->skill / 100;
	if((w->skill = pc_checkskill(sd,HW_SOULDRAIN)) > 0) // ソウルドレイン
		sd->status.max_sp += sd->status.max_sp * 2 * w->skill / 100;
	if((w->skill = pc_checkskill(sd,SL_KAINA)) > 0)	// カイナ
		sd->status.max_sp += 30 * w->skill;
	if((w->skill = pc_checkskill(sd,RA_RESEARCHTRAP)) > 0)	// トラップ研究
		sd->status.max_sp += 200 + (w->skill*20);
	if((w->skill = pc_checkskill(sd,WM_LESSON)) > 0)	// レッスン
		sd->status.max_sp += w->skill * 30;
	if((w->skill = pc_checkskill(sd,NV_BREAKTHROUGH)) > 0)	// ブレイクスルー
		sd->status.max_sp += (w->skill<5)? w->skill*30: 200;
	if((w->skill = pc_checkskill(sd,NV_TRANSCENDENCE)) > 0)	// トランセンデンス
		sd->status.max_sp += (w->skill<5)? w->skill*30: 200;

	if(sd->sc.data[SC_INCMSP2].timer != -1) {
		sd->status.max_sp = (int)((atn_bignumber)sd->status.max_sp * (100 + sd->sc.data[SC_INCMSP2].val1) / 100);
	}
	if(sd->sc.data[SC_SUPPORT_HPSP].timer != -1) {
		sd->status.max_sp = (int)((atn_bignumber)sd->status.max_sp * (100 + sd->sc.data[SC_SUPPORT_HPSP].val1) / 100);
	}

	// 最大AP
	sd->status.max_ap = job_db[sd->s_class.job].max_ap;

	// SP消費
	if((w->skill = pc_checkskill(sd,HP_MANARECHARGE)) > 0) {	// マナリチャージ
		sd->dsprate -= w->skill * 4;
		if(sd->dsprate < 0)
			sd->dsprate = 0;
	}

	// 自然回復HP
	sd->nhealhp = 1 + (sd->paramc[2]/5) + (sd->status.max_hp/200);
	if((w->skill = pc_checkskill(sd,SM_RECOVERY)) > 0) {	// HP回復力向上
		sd->nshealhp = w->skill * 5 + sd->status.max_hp * w->skill / 500;
		if(sd->nshealhp > 0x7fff)
			sd->nshealhp = 0x7fff;
	}
	if((w->skill = pc_checkskill(sd,TK_HPTIME)) > 0) {	// 安らかな休息
		sd->regen.tk_hp = w->skill*30 + (sd->status.max_hp*w->skill/500);
		if(sd->regen.tk_hp > 0x7fff)
			sd->regen.tk_hp = 0x7fff;
	}
	if(sd->sc.data[SC_GENTLETOUCH_REVITALIZE].timer != -1) {	// 点穴 -活-
		sd->nhealhp += sd->nhealhp * (50 + sd->sc.data[SC_GENTLETOUCH_REVITALIZE].val1 * 30) / 100;
		if(sd->nhealhp > 0x7fff)
			sd->nhealhp = 0x7fff;
	}
	if(sd->sc.data[SC_EXTRACT_WHITE_POTION_Z].timer != -1) {	// 濃縮ホワイトポーションZ
		sd->nhealhp += sd->nhealhp * sd->sc.data[SC_EXTRACT_WHITE_POTION_Z].val1 / 100;
		if(sd->nhealhp > 0x7fff)
			sd->nhealhp = 0x7fff;
	}
	if(sd->sc.data[SC_BERSERK].timer != -1) {
		sd->nhealhp = 0;
	}
	// 自然回復SP
	sd->nhealsp = 1 + (sd->paramc[3]/6) + (sd->status.max_sp/100);
	if(sd->paramc[3] >= 120)
		sd->nhealsp += ((sd->paramc[3]-120)>>1) + 4;
	if((w->skill = pc_checkskill(sd,MG_SRECOVERY)) > 0) {	// SP回復力向上
		sd->nshealsp = w->skill*3 + (sd->status.max_sp*w->skill/500);
		if(sd->nshealsp > 0x7fff)
			sd->nshealsp = 0x7fff;
	}
	if((w->skill = pc_checkskill(sd,NJ_NINPOU)) > 0) {	// 忍法修練
		sd->nshealsp = w->skill*3 + (sd->status.max_sp*w->skill/500);
		if(sd->nshealsp > 0x7fff)
			sd->nshealsp = 0x7fff;
	}
	if((w->skill = pc_checkskill(sd,WM_LESSON)) > 0) {	// レッスン
		sd->nshealsp = 3 + w->skill * 3;
		if(sd->nshealsp > 0x7fff)
			sd->nshealsp = 0x7fff;
	}

	if((w->skill = pc_checkskill(sd,MO_SPIRITSRECOVERY)) > 0) {
		sd->nsshealhp = w->skill*4 + (sd->status.max_hp*w->skill/500);
		sd->nsshealsp = w->skill*2 + (sd->status.max_sp*w->skill/500);
		if(sd->nsshealhp > 0x7fff)
			sd->nsshealhp = 0x7fff;
		if(sd->nsshealsp > 0x7fff)
			sd->nsshealsp = 0x7fff;
	}
	if((w->skill = pc_checkskill(sd,TK_SPTIME)) > 0) { // 楽しい休息
		sd->regen.tk_sp = w->skill*3 + (sd->status.max_sp*w->skill/500);
		if(sd->regen.tk_sp > 0x7fff)
			sd->regen.tk_sp = 0x7fff;
	}
	if(sd->hprecov_rate != 100) {
		sd->nhealhp = sd->nhealhp*sd->hprecov_rate/100;
		if(sd->nhealhp < 1)
			sd->nhealhp = 1;
	}
	if(sd->sprecov_rate != 100) {
		sd->nhealsp = sd->nhealsp*sd->sprecov_rate/100;
		if(sd->nhealsp < 1)
			sd->nhealsp = 1;
	}
	if((w->skill = pc_checkskill(sd,HP_MEDITATIO)) > 0) {
		// メディタティオはSPRではなく自然回復にかかる
		sd->nhealsp += (sd->nhealsp)*3*w->skill/100;
		if(sd->nhealsp > 0x7fff)
			sd->nhealsp = 0x7fff;
	}
	if(sd->sc.data[SC_VITATA_500].timer != -1) {	// ビタタ500
		sd->nhealsp += sd->nhealsp * sd->sc.data[SC_VITATA_500].val1 / 100;
		if(sd->nhealsp > 0x7fff)
			sd->nhealsp = 0x7fff;
	}
	if(sd->sc.data[SC_REBOUND].timer != -1) {	// リバウンド
		sd->nhealhp = sd->nhealsp = 0;
	}

	// 魔法ダメージ増加
	if((w->skill = pc_checkskill(sd,CD_FIDUS_ANIMUS)) > 0) {		// フィドスアニムス
		const int add_list[10] = { 1,2,3,4,5,7,9,12,15,20 };
		if(w->skill > 10) w->skill = 10;
		sd->skill_elemagic_dmgup[ELE_HOLY] += add_list[w->skill-1];
	}
	if(sd->status.weapon == WT_BOOK && (w->skill = pc_checkskill(sd,EM_MAGIC_BOOK_M)) > 0) {		// 魔法本修練
		const int add_list[10] = { 1,2,3,4,5,8,11,14,17,20 };
		if(w->skill > 10) w->skill = 10;
		sd->skill_elemagic_dmgup[ELE_FIRE]  += add_list[w->skill-1];
		sd->skill_elemagic_dmgup[ELE_WATER] += add_list[w->skill-1];
		sd->skill_elemagic_dmgup[ELE_WIND]  += add_list[w->skill-1];
		sd->skill_elemagic_dmgup[ELE_EARTH] += add_list[w->skill-1];
	}

	// 種族特攻
	if(sd->status.weapon == WT_KNUCKLE && (w->skill = pc_checkskill(sd,IQ_WILL_OF_FAITH)) > 0) {		// 信仰の意志
		const int add_list[10] = { 1,2,3,4,5,7,9,11,15,20 };
		if(w->skill > 10) w->skill = 10;
		sd->addrace[RCT_UNDEAD] += add_list[w->skill-1];
		sd->addrace[RCT_DEMON] += add_list[w->skill-1];
	}

	// 種族耐性
	if((w->skill = pc_checkskill(sd,SA_DRAGONOLOGY)) > 0) {	// ドラゴノロジー
		w->skill = w->skill*4;
		sd->subrace[RCT_DRAGON]  += w->skill;
		sd->magic_subrace[RCT_DRAGON]  += w->skill;
	}

	// サイズ特攻
	if((sd->status.weapon == WT_MACE || sd->status.weapon == WT_BOOK) && (w->skill = pc_checkskill(sd,CD_MACE_BOOK_M)) > 0) {		// 鈍器＆本修練
		const int add_list[10] = { 1,2,3,4,5,7,9,11,15,20 };
		if(w->skill > 10) w->skill = 10;
		sd->addsize[0] += add_list[w->skill-1];
		sd->addsize[1] += add_list[w->skill-1];
		sd->addsize[2] += add_list[w->skill-1];
	}
	if((sd->status.weapon == WT_DAGGER || sd->status.weapon == WT_BOW) && (w->skill = pc_checkskill(sd,ABC_DAGGER_AND_BOW_M)) > 0) {		// 短剣＆弓修練
		const int add_list[10] = { 1,2,3,4,5,6,7,9,12,15 };
		if(w->skill > 10) w->skill = 10;
		sd->addsize[0] += add_list[w->skill-1];
		sd->addsize[1] += add_list[w->skill-1];
		sd->addsize[2] += add_list[w->skill-1];
	}

	// サイズ魔法特攻
	if((sd->status.weapon == WT_DAGGER || sd->status.weapon == WT_1HSWORD) && (w->skill = pc_checkskill(sd,ABC_MAGIC_SWORD_M)) > 0) {		// 魔法剣修練
		const int add_list[10] = { 1,2,3,4,5,7,9,11,13,15 };
		if(w->skill > 10) w->skill = 10;
		sd->magic_addsize[0] += add_list[w->skill-1];
		sd->magic_addsize[1] += add_list[w->skill-1];
		sd->magic_addsize[2] += add_list[w->skill-1];
	}

	// サイズ耐性
	if((sd->status.weapon == WT_2HSWORD || sd->status.weapon == WT_2HSPEAR || sd->status.weapon == WT_2HAXE) && (w->skill = pc_checkskill(sd,DK_TWOHANDDEF)) > 0) {		// ツーハンドディフェンディング
		sd->subsize[0] += w->skill;
		sd->subsize[1] += w->skill;
		sd->subsize[2] += w->skill;
	}
	if(sd->status.weapon == WT_2HAXE && (w->skill = pc_checkskill(sd,MT_TWOAXEDEF)) > 0) {		// ツーアックスディフェンディング
		sd->subsize[0] += w->skill;
		sd->subsize[1] += w->skill;
		sd->subsize[2] += w->skill;
	}

	// 種族設定
	if(pc_isdoram(sd)) {
		sd->critical_race[RCT_DEMIHUMAN] += 20;
		sd->subrace[RCT_DEMIHUMAN] -= 10;
	}
	else {
		sd->addrace[RCT_PLAYER_DORAM]  += 10;
		sd->addrace_[RCT_PLAYER_DORAM] += 10;
	}
	// Flee上昇
	if((w->skill = pc_checkskill(sd,TF_MISS)) > 0) {	// 回避率増加
		if(sd->s_class.job == PC_JOB_AS || sd->s_class.job == PC_JOB_RG || sd->s_class.job == PC_JOB_GC || sd->s_class.job == PC_JOB_SC)
			sd->flee += w->skill*4;
		else
			sd->flee += w->skill*3;
	}
	if((w->skill = pc_checkskill(sd,MO_DODGE)) > 0)	// 見切り
		sd->flee += (w->skill*3)>>1;
	if(sd->sc.count > 0) {
		if(sd->sc.data[SC_INCFLEE].timer != -1)
			sd->flee += sd->sc.data[SC_INCFLEE].val1;
		if(sd->sc.data[SC_INCFLEE2].timer != -1)
			sd->flee += sd->sc.data[SC_INCFLEE2].val1;
		if(sd->sc.data[SC_GROOMING].timer != -1)	// グルーミング
			sd->flee += sd->sc.data[SC_GROOMING].val2;
	}
	if(pc_isdoram(sd) && pc_checkskill(sd,SU_POWEROFLIFE) > 0) {	// 生命の力
		sd->hit += 50;
		sd->flee += 50;
		sd->critical += 200;
	}
	if((w->skill = pc_checkskill(sd,SHC_SHADOW_SENSE)) > 0) {		// シャドウセンス
		const int add_fleelist[10] = { 10,20,30,40,50,60,70,85,100,150 };
		if(w->skill > 10) w->skill = 10;
		sd->flee += add_fleelist[w->skill-1];
		if(sd->weapontype1 == WT_DAGGER) {
			const int add_crilist[10] = { 2,4,6,8,10,12,14,20,30,50 };
			sd->critical += add_crilist[w->skill-1];
		} else if(sd->status.weapon == WT_KATAR) {
			const int add_crilist[10] = { 1,2,3,4,5,6,7,10,15,25 };
			sd->critical += add_crilist[w->skill-1];
		}
	}
	// Def
	if(pc_isgear(sd) && (w->skill = pc_checkskill(sd,NC_MAINFRAME)) > 0) {		// 魔導ギア＆メインフレーム改造
		if(w->skill == 1)
			sd->def += 4;
		else
			sd->def += (w->skill*4) - 1;
	}

	// P.Atk
	if((sd->status.weapon == WT_BOW || sd->status.weapon == WT_MUSICAL || sd->status.weapon == WT_WHIP) && (w->skill = pc_checkskill(sd,TR_STAGE_MANNER)) > 0) {		// ステージマナー
		const int add_manner_list[5] = { 1,3,5,10,15 };
		if(w->skill > 5) w->skill = 5;
		sd->patk  += add_manner_list[w->skill-1];
		sd->smatk += add_manner_list[w->skill-1];
	}
	if((sd->status.weapon >= WT_HANDGUN && sd->status.weapon <= WT_GRENADE) && (w->skill = pc_checkskill(sd,NW_P_F_I)) > 0) {		// P.F.I
		sd->patk += w->skill;
	}
	if((w->skill = pc_checkskill(sd,SH_MYSTICAL_CREATURE_MASTERY)) > 0) {		// スピリットマスタリー
		sd->patk  += w->skill + ((w->skill >= 10)? 5: (w->skill >= 9)? 3: 0);
		sd->smatk += w->skill + ((w->skill >= 10)? 5: (w->skill >= 9)? 3: 0);
	}
	if((w->skill = pc_checkskill(sd,HN_SELFSTUDY_TATICS)) > 0) {		// 独学 -戦闘学-
		const int add_list[10] = { 1,2,3,4,5,6,7,9,12,15 };
		if(w->skill > 10) w->skill = 10;
		sd->patk += add_list[w->skill-1];
	}
	if((w->skill = pc_checkskill(sd,SKE_WAR_BOOK_MASTERY)) > 0) {		// 兵法修練
		const int add_hit_list[10]  = { 3, 6, 9,12,15,20,25,30,40,50 };
		const int add_patk_list[10] = { 1, 2, 3, 4, 5, 7, 9,11,13,15 };
		if(w->skill > 10) w->skill = 10;
		sd->hit  += add_hit_list[w->skill-1];
		sd->patk += add_patk_list[w->skill-1];
	}

	// S.Matk
	if(sd->status.weapon == WT_2HSTAFF && (w->skill = pc_checkskill(sd,AG_TWOHANDSTAFF)) > 0) {		// 両手杖修練
		const int add_2hstaff_list[10] = { 1,3,5,8,11,14,17,21,25,30 };
		if(w->skill > 10) w->skill = 10;
		sd->smatk += add_2hstaff_list[w->skill-1];
	}
	if((w->skill = pc_checkskill(sd,SOA_TALISMAN_MASTERY)) > 0) {		// 護符修練
		sd->smatk += w->skill;
	}
	if((w->skill = pc_checkskill(sd,HN_SELFSTUDY_SOCERY)) > 0) {		// 独学 -魔導学-
		const int add_list[10] = { 1,2,3,4,5,6,7,9,12,15 };
		if(w->skill > 10) w->skill = 10;
		sd->smatk += add_list[w->skill-1];
	}

	// Res
	if(sd->status.shield > 0 && (w->skill = pc_checkskill(sd,IG_SHIELD_MASTERY)) > 0) {		// 盾修練
		sd->res += w->skill*10;
	}

#ifdef PRE_RENEWAL
	// MATK乗算処理(杖補正以外)
	if(sd->matk_rate != 100) {
		sd->matk1 = sd->matk1 * sd->matk_rate / 100;
		sd->matk2 = sd->matk2 * sd->matk_rate / 100;
	}
#endif
	// amotionの計算
	sd->amotion = status_calc_amotion_pc(sd);
	sd->aspd = sd->amotion<<1;
	// speedの計算
	sd->speed = status_calc_speed_pc(sd,sd->speed);
}

static void status_calc_pc_phase_sc_rest(struct map_session_data *sd, struct status_calc_pc_work *w)
{
	// スキルやステータス異常による残りのパラメータ補正
	if((w->skill = pc_checkskill(sd,NV_BREAKTHROUGH)) > 0) {	// ブレイクスルー
#ifdef PRE_RENEWAL
		sd->watk += (w->skill<5)? w->skill*15: 100;
#else
		sd->plus_atk += (w->skill<5)? w->skill*15: 100;
#endif
	}
	if((w->skill = pc_checkskill(sd,NV_TRANSCENDENCE)) > 0) {	// トランセンデンス
#ifdef PRE_RENEWAL
		sd->matk1 += (w->skill<5)? w->skill*15: 100;
		sd->matk2 += (w->skill<5)? w->skill*15: 100;
#else
		sd->plus_matk += (w->skill<5)? w->skill*15: 100;
#endif
	}
	if(sd->sc.count > 0) {
		// 太陽の安楽 DEF増加
		if(sd->sc.data[SC_SUN_COMFORT].timer != -1)
			sd->def2 += (sd->status.base_level + sd->status.dex + sd->status.luk)/2;
			//sd->def += (sd->status.base_level + sd->status.dex + sd->status.luk + sd->paramb[4] + sd->paramb[5])/10;

		// 月の安楽
		if(sd->sc.data[SC_MOON_COMFORT].timer != -1 && (sd->bl.m == sd->feel_index[1] || sd->sc.data[SC_MIRACLE].timer != -1))
			sd->flee += (sd->status.base_level + sd->status.dex + sd->status.luk)/10;
			//sd->flee += (sd->status.base_level + sd->status.dex + sd->status.luk + sd->paramb[4] + sd->paramb[5])/10;

		// クローズコンファイン
		if(sd->sc.data[SC_CLOSECONFINE].timer != -1)
			sd->flee += 10;

		// ATK/DEF変化形
		if(sd->sc.data[SC_ANGELUS].timer != -1) {	// エンジェラス
#ifdef PRE_RENEWAL
			sd->def2 = sd->def2*(110+5*sd->sc.data[SC_ANGELUS].val1)/100;
#else
			sd->def2 = sd->def2+sd->paramc[2]/2*(100+5*sd->sc.data[SC_ANGELUS].val1)/100;
#endif
		}
#ifdef PRE_RENEWAL
		if(sd->sc.data[SC_IMPOSITIO].timer != -1) {// イムポシティオマヌス
			sd->watk += sd->sc.data[SC_IMPOSITIO].val1*5;
			// 左手には適用しない
			//w->idx = sd->equip_index[EQUIP_INDEX_LARM];
			//if(w->idx >= 0 && sd->inventory_data[w->idx] && sd->inventory_data[w->idx]->type == ITEMTYPE_ARMOR)
			//	sd->watk_ += sd->sc.data[SC_IMPOSITIO].val1*5;
		}
#endif
		if(sd->sc.data[SC__BLOODYLUST].timer != -1) {	// ブラッディラスト
			sd->def2 = sd->def2*(100 - 55) / 100;
#ifdef PRE_RENEWAL
			sd->base_atk = sd->base_atk*(100 + 32) / 100;
			sd->watk = sd->watk*(100 + 32) / 100;
#endif
			// 左手には適用しない
			//w->idx = sd->equip_index[EQUIP_INDEX_LARM];
			//if(w->idx >= 0 && sd->inventory_data[w->idx] && sd->inventory_data[w->idx]->type == ITEMTYPE_ARMOR)
			//	sd->watk_ = sd->watk_*(100+32)/100;
		}
		else if(sd->sc.data[SC_PROVOKE].timer != -1) {	// プロボック
			sd->def2 = sd->def2*(100 - 5 - 5 * sd->sc.data[SC_PROVOKE].val1) / 100;
#ifdef PRE_RENEWAL
			sd->base_atk = sd->base_atk*(100 + 2 + 3 * sd->sc.data[SC_PROVOKE].val1) / 100;
			sd->watk = sd->watk*(100 + 2 + 3 * sd->sc.data[SC_PROVOKE].val1) / 100;
#endif
			// 左手には適用しない
			//w->idx = sd->equip_index[EQUIP_INDEX_LARM];
			//if(w->idx >= 0 && sd->inventory_data[w->idx] && sd->inventory_data[w->idx]->type == ITEMTYPE_ARMOR)
			//	sd->watk_ = sd->watk_*(100+2+3*sd->sc.data[SC_PROVOKE].val1)/100;
		}
		if(sd->sc.data[SC_POISON].timer != -1)	// 毒状態
			sd->def2 = sd->def2*75/100;

		// 運命のタロットカード
		if(sd->sc.data[SC_THE_MAGICIAN].timer != -1) {
			// ATK半減
			sd->base_atk = sd->base_atk * 50/100;
			sd->watk = sd->watk * 50/100;
			w->idx = sd->equip_index[EQUIP_INDEX_LARM];
			if(w->idx >= 0 && sd->inventory_data[w->idx] && itemdb_isweapon(sd->inventory_data[w->idx]->nameid))
				sd->watk_ = sd->watk_ * 50/100;
		}
		if(sd->sc.data[SC_STRENGTH].timer != -1) {
			// MATK半減
			sd->matk1 = sd->matk1*50/100;
			sd->matk2 = sd->matk2*50/100;
		}
		if(sd->sc.data[SC_THE_DEVIL].timer != -1) {
			// ATK半減、MATK半減
			sd->base_atk = sd->base_atk * 50/100;
			sd->watk = sd->watk * 50/100;
			w->idx = sd->equip_index[EQUIP_INDEX_LARM];
			if(w->idx >= 0 && sd->inventory_data[w->idx] && itemdb_isweapon(sd->inventory_data[w->idx]->nameid)) {
				sd->watk_ = sd->watk_ * 50/100;
			}
			sd->matk1 = sd->matk1*50/100;
			sd->matk2 = sd->matk2*50/100;
		}
		if(sd->sc.data[SC_THE_SUN].timer != -1) {
			// ATK、MATK、回避、命中、防御力が全て20%ずつ下落する
			sd->base_atk = sd->base_atk * 80/100;
			sd->watk = sd->watk * 80/100;
			w->idx = sd->equip_index[EQUIP_INDEX_LARM];
			if(w->idx >= 0 && sd->inventory_data[w->idx] && itemdb_isweapon(sd->inventory_data[w->idx]->nameid)) {
				sd->watk_ = sd->watk_ * 80/100;
			}
			sd->matk1 = sd->matk1*80/100;
			sd->matk2 = sd->matk2*80/100;
			sd->flee  = sd->flee * 80/100;
			sd->hit   = sd->hit * 80/100;

			sd->def  = sd->def * 80/100;
			sd->def2 = sd->def2 * 80/100;
		}

		if(sd->sc.data[SC_DRUMBATTLE].timer != -1) {	// 戦太鼓の響き
			sd->def  += sd->sc.data[SC_DRUMBATTLE].val3;
		}
#ifdef PRE_RENEWAL
		if(sd->sc.data[SC_NIBELUNGEN].timer != -1) {	// ニーベルングの指輪
			w->idx = sd->equip_index[EQUIP_INDEX_RARM];
			if(w->idx >= 0 && sd->inventory_data[w->idx] && sd->inventory_data[w->idx]->wlv >= 4)
				sd->watk += sd->sc.data[SC_NIBELUNGEN].val2;
			// 左手には適用しない
			//w->idx = sd->equip_index[EQUIP_INDEX_LARM];
			//if(w->idx >= 0 && sd->inventory_data[w->idx] && sd->inventory_data[w->idx]->wlv >= 4)
			//	sd->watk_ += sd->sc.data[SC_NIBELUNGEN].val2;
		}

		if(sd->sc.data[SC_INCATK2].timer != -1) {
			sd->watk = sd->watk*(100+sd->sc.data[SC_INCATK2].val1)/100;
		}
#endif

		if(sd->sc.data[SC_SIGNUMCRUCIS].timer != -1)
			sd->def = sd->def * (100 - sd->sc.data[SC_SIGNUMCRUCIS].val2)/100;
		if(sd->sc.data[SC_ETERNALCHAOS].timer != -1)	// エターナルカオス
			sd->def2 = 0;

		if(sd->sc.data[SC_CONCENTRATION].timer != -1) {	// コンセントレーション
#ifdef PRE_RENEWAL
			sd->base_atk = sd->base_atk * (100 + 5*sd->sc.data[SC_CONCENTRATION].val1)/100;
			sd->watk = sd->watk * (100 + 5*sd->sc.data[SC_CONCENTRATION].val1)/100;
			w->idx = sd->equip_index[EQUIP_INDEX_LARM];
			if(w->idx >= 0 && sd->inventory_data[w->idx] && itemdb_isweapon(sd->inventory_data[w->idx]->nameid))
				sd->watk_ = sd->watk_ * (100 + 5*sd->sc.data[SC_CONCENTRATION].val1)/100;
#endif
			sd->def = sd->def * (100 - 5*sd->sc.data[SC_CONCENTRATION].val1)/100;
			sd->def2 = sd->def2 * (100 - 5*sd->sc.data[SC_CONCENTRATION].val1)/100;
		}

		if(sd->sc.data[SC_INCATK].timer != -1) {	// ATK上昇 (神酒用)
			sd->watk += sd->sc.data[SC_INCATK].val1;
		}
		if(sd->sc.data[SC_ATKPOTION].timer != -1) {	// ATK上昇
#ifdef PRE_RENEWAL
			sd->watk += sd->sc.data[SC_ATKPOTION].val1;
#else
			sd->plus_atk += sd->sc.data[SC_ATKPOTION].val1;
#endif
		}
		if(sd->sc.data[SC_ALMIGHTY].timer != -1) {	// ATK上昇 (食事用)
#ifdef PRE_RENEWAL
			sd->watk += sd->sc.data[SC_ALMIGHTY].val1;
#else
			sd->plus_atk += sd->sc.data[SC_ALMIGHTY].val1;
#endif
		}
		if(sd->sc.data[SC_INCMATK].timer != -1) {	// MATK上昇 (神秘の草用)
			sd->matk1 += sd->sc.data[SC_INCMATK].val1;
			sd->matk2 += sd->sc.data[SC_INCMATK].val1;
		}
		if(sd->sc.data[SC_MATKPOTION].timer != -1) {	// MATK上昇
#ifdef PRE_RENEWAL
			sd->matk1 += sd->sc.data[SC_MATKPOTION].val1;
			sd->matk2 += sd->sc.data[SC_MATKPOTION].val1;
#else
			sd->plus_matk += sd->sc.data[SC_MATKPOTION].val1;
#endif
		}
		if(sd->sc.data[SC_ALMIGHTY].timer != -1) {	// MATK上昇 (食事用)
#ifdef PRE_RENEWAL
			sd->matk1 += sd->sc.data[SC_ALMIGHTY].val2;
			sd->matk2 += sd->sc.data[SC_ALMIGHTY].val2;
#else
			sd->plus_matk += sd->sc.data[SC_ALMIGHTY].val2;
#endif
		}
		if(sd->sc.data[SC_MINDBREAKER].timer != -1) {
#ifdef PRE_RENEWAL
			sd->matk1 += (sd->matk1*20*sd->sc.data[SC_MINDBREAKER].val1)/100;
			sd->matk2 += (sd->matk2*20*sd->sc.data[SC_MINDBREAKER].val1)/100;
#endif
			sd->mdef2 -= (sd->mdef2*12*sd->sc.data[SC_MINDBREAKER].val1)/100;
		}
		// MATK上昇 (モンスター変身のマルドゥーク、バンシー用)
		if(sd->sc.data[SC_MONSTER_TRANSFORM].timer != -1 && (sd->sc.data[SC_MONSTER_TRANSFORM].val1 == 1140 || sd->sc.data[SC_MONSTER_TRANSFORM].val1 == 1867)) {
			sd->matk1 += 25;
			sd->matk2 += 25;
		}
		if(sd->sc.data[SC_CHATTERING].timer != -1) {
			sd->base_atk += sd->sc.data[SC_CHATTERING].val2;
#ifdef PRE_RENEWAL
			sd->matk1 += sd->sc.data[SC_CHATTERING].val2;
#endif
			sd->matk2 += sd->sc.data[SC_CHATTERING].val2;
		}
		// クライマックスハリケーン
		if(sd->sc.data[SC_CLIMAX_DES_HU].timer != -1) {
#ifdef PRE_RENEWAL
			sd->matk1 += sd->sc.data[SC_CLIMAX_DES_HU].val2;
			sd->matk2 += sd->sc.data[SC_CLIMAX_DES_HU].val2;
#else
			sd->plus_matk += sd->sc.data[SC_CLIMAX_DES_HU].val2;
#endif
			sd->skill_elemagic_dmgup[ELE_WIND] += sd->sc.data[SC_CLIMAX_DES_HU].val3;
		}
		if(sd->sc.data[SC_ENDURE].timer != -1) {
			sd->mdef += sd->sc.data[SC_ENDURE].val1;
		}
		// クライマックスインパクト
		if(sd->sc.data[SC_CLIMAX_CRYIMP].timer != -1) {
#ifdef PRE_RENEWAL
			sd->def2 += sd->sc.data[SC_CLIMAX_CRYIMP].val2;
			sd->mdef2 += sd->sc.data[SC_CLIMAX_CRYIMP].val3;
#else
			sd->def += sd->sc.data[SC_CLIMAX_CRYIMP].val2;
			sd->mdef += sd->sc.data[SC_CLIMAX_CRYIMP].val3;
#endif
			sd->skill_elemagic_dmgup[ELE_WATER] += sd->sc.data[SC_CLIMAX_CRYIMP].val4;
			sd->subele[ELE_WATER] += sd->sc.data[SC_CLIMAX_CRYIMP].val4;
		}

		if(sd->sc.data[SC_ANALYZE].timer != -1) {	// アナライズ
			sd->def2  -= (sd->def2 * 14 * sd->sc.data[SC_ANALYZE].val1) / 100;
			sd->mdef2 -= (sd->mdef2 * 14 * sd->sc.data[SC_ANALYZE].val1) / 100;
		}
		if(sd->sc.data[SC_NEUTRALBARRIER].timer != -1) {	// ニュートラルバリアー
			sd->def2  += (sd->def2 * (10 + 5 * sd->sc.data[SC_NEUTRALBARRIER].val1)) / 100;
			sd->mdef2 += (sd->mdef2 * (10 + 5 * sd->sc.data[SC_NEUTRALBARRIER].val1)) / 100;
		}
		if(sd->sc.data[SC_SUNSTANCE].timer != -1) {	// 太陽の構え
			sd->watk += sd->watk * sd->sc.data[SC_SUNSTANCE].val2 / 100;
		}

		// HIT/FLEE変化系
#ifdef PRE_RENEWAL
		if(sd->sc.data[SC_WHISTLE].timer != -1) {  // 口笛
			sd->flee += sd->sc.data[SC_WHISTLE].val1 + sd->sc.data[SC_WHISTLE].val2 + sd->sc.data[SC_WHISTLE].val3;
		} else if(sd->sc.data[SC_WHISTLE_].timer != -1) {  // 口笛
			sd->flee += sd->sc.data[SC_WHISTLE_].val1 + sd->sc.data[SC_WHISTLE_].val2 + sd->sc.data[SC_WHISTLE_].val3;
		}
#else
		if(sd->sc.data[SC_WHISTLE].timer != -1) {  // 口笛
			sd->flee += sd->sc.data[SC_WHISTLE].val1*3 + sd->sc.data[SC_WHISTLE].val2 + sd->sc.data[SC_WHISTLE].val3;
		} else if(sd->sc.data[SC_WHISTLE_].timer != -1) {  // 口笛
			sd->flee += sd->sc.data[SC_WHISTLE_].val1*3 + sd->sc.data[SC_WHISTLE_].val2 + sd->sc.data[SC_WHISTLE_].val3;
		}
#endif

#ifdef PRE_RENEWAL
		if(sd->sc.data[SC_HUMMING].timer != -1) {  // ハミング
			sd->hit += 10+sd->sc.data[SC_HUMMING].val1*2+sd->sc.data[SC_HUMMING].val2+sd->sc.data[SC_HUMMING].val3;
		} else if(sd->sc.data[SC_HUMMING_].timer != -1) {  // ハミング
			sd->hit += 10+sd->sc.data[SC_HUMMING_].val1*2+sd->sc.data[SC_HUMMING_].val2+sd->sc.data[SC_HUMMING_].val3;
		}
#else
		if(sd->sc.data[SC_HUMMING].timer != -1) {  // ハミング
			sd->hit += 20+sd->sc.data[SC_HUMMING].val1*2+sd->sc.data[SC_HUMMING].val2+sd->sc.data[SC_HUMMING].val3;
		} else if(sd->sc.data[SC_HUMMING_].timer != -1) {  // ハミング
			sd->hit += 20+sd->sc.data[SC_HUMMING_].val1*2+sd->sc.data[SC_HUMMING_].val2+sd->sc.data[SC_HUMMING_].val3;
		}
#endif

		if(sd->sc.data[SC_VIOLENTGALE].timer != -1
#ifdef PRE_RENEWAL
			&& sd->def_ele == ELE_WIND
#endif
		) {	// バイオレントゲイル
			sd->flee += sd->flee*sd->sc.data[SC_VIOLENTGALE].val3/100;
		}
		if(sd->sc.data[SC_BLIND].timer != -1) {	// 暗黒
			sd->hit  -= sd->hit*25/100;
			sd->flee -= sd->flee*25/100;
		}
		if(sd->sc.data[SC_WINDWALK].timer != -1)	// ウィンドウォーク
			sd->flee += sd->sc.data[SC_WINDWALK].val2;
		if(sd->sc.data[SC_SPIDERWEB].timer != -1)	// スパイダーウェブ
			sd->flee -= 50;
		if(sd->sc.data[SC_TRUESIGHT].timer != -1)	// トゥルーサイト
			sd->hit += 3*(sd->sc.data[SC_TRUESIGHT].val1);
		if(sd->sc.data[SC_CONCENTRATION].timer != -1)	// コンセントレーション
			sd->hit += 10*(sd->sc.data[SC_CONCENTRATION].val1);
		if(sd->sc.data[SC_INCHIT].timer != -1)
			sd->hit += sd->sc.data[SC_INCHIT].val1;
		if(sd->sc.data[SC_INCHIT2].timer != -1)
			sd->hit = sd->hit * (100+sd->sc.data[SC_INCHIT2].val1)/100;
		if(sd->sc.data[SC_BERSERK].timer != -1)
			sd->flee -= sd->flee*50/100;
		if(sd->sc.data[SC_INCFLEE].timer != -1)	// 速度強化
			sd->flee += sd->flee*(sd->sc.data[SC_INCFLEE].val2)/100;
		if(sd->sc.data[SC_HALLUCINATIONWALK].timer != -1)	// ハルシネーションウォーク
			sd->flee += sd->sc.data[SC_HALLUCINATIONWALK].val1 * 50;
		if(sd->sc.data[SC_INFRAREDSCAN].timer != -1)	// インフラレッドスキャン
			sd->flee -= sd->flee*30/100;
#ifndef PRE_RENEWAL
		if(sd->sc.data[SC_SPEARQUICKEN].timer != -1)   // スピアクイッケン
			sd->flee += 2*(sd->sc.data[SC_SPEARQUICKEN].val1);
#endif
		if(sd->sc.data[SC_C_MARKER].timer != -1)  // クリムゾンマーカー
			sd->flee -= sd->sc.data[SC_C_MARKER].val1 * 10;
		if(sd->sc.data[SC_HEAT_BARREL].timer != -1)  // ヒートバレル
			sd->hit -= sd->sc.data[SC_HEAT_BARREL].val4;

		// ガンスリンガースキル
		if(sd->sc.data[SC_FLING].timer != -1) {		// フライング
			sd->def = sd->def * (100 - 5*sd->sc.data[SC_FLING].val2)/100;
		}
		if(sd->sc.data[SC_ADJUSTMENT].timer != -1) {	// アジャストメント
			sd->hit  -= 30;
			sd->flee += 30;
		}
		if(sd->sc.data[SC_INCREASING].timer != -1) {	// インクリージングアキュラシー
			sd->hit += 20;
		}
		if(sd->sc.data[SC_GATLINGFEVER].timer != -1) {	// ガトリングフィーバー
			sd->flee -= sd->sc.data[SC_GATLINGFEVER].val1*5;
		}
		if(sd->sc.data[SC_VOLCANIC_ASH].timer != -1) 	// 火山灰
			sd->hit -= sd->hit * sd->sc.data[SC_VOLCANIC_ASH].val2 / 100;

#ifdef PRE_RENEWAL
		// ストーンスキン
		if(sd->sc.data[SC_STONESKIN].timer != -1) {
			sd->def  = sd->def  * (100 + 20 * sd->sc.data[SC_STONESKIN].val1) / 100;
			sd->mdef = sd->mdef * (100 - 20 * sd->sc.data[SC_STONESKIN].val1) / 100;
		}
		// アンチマジック
		if(sd->sc.data[SC_ANTIMAGIC].timer != -1) {
			sd->def  = sd->def  * (100 - 20 * sd->sc.data[SC_ANTIMAGIC].val1) / 100;
			sd->mdef = sd->mdef * (100 + 20 * sd->sc.data[SC_ANTIMAGIC].val1) / 100;
		}
#endif

		// 耐性
		if(sd->sc.data[SC_RESISTWATER].timer != -1)
			sd->subele[ELE_WATER] += sd->sc.data[SC_RESISTWATER].val1;
		if(sd->sc.data[SC_RESISTGROUND].timer != -1)
			sd->subele[ELE_EARTH] += sd->sc.data[SC_RESISTGROUND].val1;
		if(sd->sc.data[SC_RESISTFIRE].timer != -1)
			sd->subele[ELE_FIRE] += sd->sc.data[SC_RESISTFIRE].val1;
		if(sd->sc.data[SC_RESISTWIND].timer != -1)
			sd->subele[ELE_WIND] += sd->sc.data[SC_RESISTWIND].val1;
		if(sd->sc.data[SC_RESISTPOISON].timer != -1)
			sd->subele[ELE_POISON] += sd->sc.data[SC_RESISTPOISON].val1;
		if(sd->sc.data[SC_RESISTHOLY].timer != -1)
			sd->subele[ELE_HOLY] += sd->sc.data[SC_RESISTHOLY].val1;
		if(sd->sc.data[SC_RESISTDARK].timer != -1)
			sd->subele[ELE_DARK] += sd->sc.data[SC_RESISTDARK].val1;
		if(sd->sc.data[SC_RESISTTELEKINESIS].timer != -1)
			sd->subele[ELE_GHOST] += sd->sc.data[SC_RESISTTELEKINESIS].val1;
		if(sd->sc.data[SC_RESISTUNDEAD].timer != -1)
			sd->subele[ELE_UNDEAD] += sd->sc.data[SC_RESISTUNDEAD].val1;

		// 耐性
		if(sd->sc.data[SC_RESISTALL].timer != -1) {
			for(w->i=ELE_WATER; w->i<ELE_MAX; w->i++)
				sd->subele[w->i] += sd->sc.data[SC_RESISTALL].val1;	// 全てに耐性増加
		}
		// 不死身のジークフリード
		if(sd->sc.data[SC_SIEGFRIED].timer != -1) {
			for(w->i=ELE_WATER; w->i<ELE_MAX; w->i++)
				sd->subele[w->i] += sd->sc.data[SC_SIEGFRIED].val2;	// 全てに耐性増加
		}
		// プロヴィデンス
		if(sd->sc.data[SC_PROVIDENCE].timer != -1) {
			sd->subele[ELE_HOLY]   += sd->sc.data[SC_PROVIDENCE].val2;	// 対聖属性
			sd->subrace[RCT_DEMON] += sd->sc.data[SC_PROVIDENCE].val2;	// 対悪魔
		}

		// 獄炎呪
		if(sd->sc.data[SC_BURNT].timer != -1) {
			sd->subele[ELE_FIRE]       -= sd->sc.data[SC_BURNT].val1 * 20;
			sd->def_eleenemy[ELE_FIRE] -= sd->sc.data[SC_BURNT].val1 * 20;
		}

		// その他
		if(sd->sc.data[SC_BERSERK].timer != -1) {	// バーサーク
			sd->def   = 0;
			sd->def2  = 0;
			sd->mdef  = 0;
			sd->mdef2 = 0;
		}
		if(sd->sc.data[SC_JOINTBEAT].timer != -1) {	// ジョイントビート
			switch (sd->sc.data[SC_JOINTBEAT].val4) {
				case 0:		// 足首
					break;
				case 1:		// 手首
					break;
				case 2:		// 膝
					break;
				case 3:		// 肩
					sd->def2 -= (sd->def2 * 50)/100;
					break;
				case 4:		// 腰
					sd->def2     -= (sd->def2 * 25)/100;
					sd->base_atk -= (sd->base_atk * 25)/100;
					break;
				case 5:		// 首
					sd->critical_def -= (sd->critical_def * 50)/100;
					break;
			}
		}
		if(sd->sc.data[SC_APPLEIDUN].timer != -1) {	// イドゥンの林檎
			sd->status.max_hp += ((5+sd->sc.data[SC_APPLEIDUN].val1*2+sd->sc.data[SC_APPLEIDUN].val2
						+sd->sc.data[SC_APPLEIDUN].val3/10) * sd->status.max_hp)/100;

		} else if(sd->sc.data[SC_APPLEIDUN_].timer != -1) {	// イドゥンの林檎
			sd->status.max_hp += ((5+sd->sc.data[SC_APPLEIDUN_].val1*2+sd->sc.data[SC_APPLEIDUN_].val2
						+sd->sc.data[SC_APPLEIDUN_].val3/10) * sd->status.max_hp)/100;
		}

		if(sd->sc.data[SC_DELUGE].timer != -1
#ifdef PRE_RENEWAL
			&& sd->def_ele == ELE_WATER
#endif
		) {	// デリュージ
			sd->status.max_hp += sd->status.max_hp*sd->sc.data[SC_DELUGE].val3/100;
		}
		if(sd->sc.data[SC_SERVICE4U].timer != -1) {	// サービスフォーユー
			sd->status.max_sp += sd->status.max_sp*(15+sd->sc.data[SC_SERVICE4U].val1+sd->sc.data[SC_SERVICE4U].val2
						+sd->sc.data[SC_SERVICE4U].val3)/100;
			sd->dsprate -= 20+sd->sc.data[SC_SERVICE4U].val1*3+sd->sc.data[SC_SERVICE4U].val2+sd->sc.data[SC_SERVICE4U].val3;
			if(sd->dsprate < 0)
				sd->dsprate = 0;
		} else if(sd->sc.data[SC_SERVICE4U_].timer != -1) {	// サービスフォーユー
			sd->status.max_sp += sd->status.max_sp*(15+sd->sc.data[SC_SERVICE4U_].val1+sd->sc.data[SC_SERVICE4U_].val2
						+sd->sc.data[SC_SERVICE4U_].val3)/100;
			sd->dsprate -= 20+sd->sc.data[SC_SERVICE4U_].val1*3+sd->sc.data[SC_SERVICE4U_].val2+sd->sc.data[SC_SERVICE4U_].val3;
			if(sd->dsprate < 0)
				sd->dsprate = 0;
		}

		if(sd->sc.data[SC_FORTUNE].timer != -1) {	// 幸運のキス
			sd->critical += (10+sd->sc.data[SC_FORTUNE].val1+sd->sc.data[SC_FORTUNE].val2+sd->sc.data[SC_FORTUNE].val3)*10;
		} else if(sd->sc.data[SC_FORTUNE_].timer != -1) {	// 幸運のキス
			sd->critical += (10+sd->sc.data[SC_FORTUNE_].val1+sd->sc.data[SC_FORTUNE_].val2+sd->sc.data[SC_FORTUNE_].val3)*10;
		}

		if(sd->sc.data[SC_EXPLOSIONSPIRITS].timer != -1) {	// 爆裂波動
			if(sd->s_class.job == PC_JOB_SNV || sd->s_class.job == PC_JOB_ESNV)
				sd->critical += sd->sc.data[SC_EXPLOSIONSPIRITS].val1*100;
			else
				sd->critical += sd->sc.data[SC_EXPLOSIONSPIRITS].val2;
		}

#ifdef PRE_RENEWAL
		if(sd->sc.data[SC_STEELBODY].timer != -1) {	// 金剛
			sd->def = 90;
			sd->mdef = 90;
		}
#endif
		if(sd->sc.data[SC_ENCPOISON].timer != -1)
			sd->addeff[4] += sd->sc.data[SC_ENCPOISON].val2;
		if(sd->sc.data[SC_TRUESIGHT].timer != -1)	// トゥルーサイト
			sd->critical += 10*(sd->sc.data[SC_TRUESIGHT].val1);
#ifndef PRE_RENEWAL
		if(sd->sc.data[SC_SPEARQUICKEN].timer != -1)   // スピアクイッケン
			sd->critical += 30*(sd->sc.data[SC_SPEARQUICKEN].val1);
#endif

		/*
		if(sd->sc.data[SC_VOLCANO].timer != -1)	// エンチャントポイズン(属性はbattle.cで)
			sd->addeff[2] += sd->sc.data[SC_VOLCANO].val2;	// % of granting
		if(sd->sc.data[SC_DELUGE].timer != -1)	// エンチャントポイズン(属性はbattle.cで)
			sd->addeff[0] += sd->sc.data[SC_DELUGE].val2;	// % of granting
		*/

		// ファイティングスピリット
		if(sd->sc.data[SC_FIGHTINGSPIRIT].timer != -1) {
#ifdef PRE_RENEWAL
			sd->base_atk += sd->sc.data[SC_FIGHTINGSPIRIT].val2;
#else
			sd->plus_atk += sd->sc.data[SC_FIGHTINGSPIRIT].val2;
#endif
		}
		// 恐怖
		if(sd->sc.data[SC_FEAR].timer != -1) {
			sd->hit  = sd->hit * 80/100;
			sd->flee = sd->flee * 80/100;
		}
		// インビジビリティ
		if(sd->sc.data[SC__INVISIBILITY].timer != -1) {
			sd->critical += sd->critical * (sd->sc.data[SC__INVISIBILITY].val1 * 20) / 100;
		}
		// マスカレード：エナベーション
		if(sd->sc.data[SC__ENERVATION].timer != -1) {
			sd->base_atk -= sd->base_atk * (20 + sd->sc.data[SC__ENERVATION].val1 * 10) / 100;
			sd->watk -= sd->watk * (20 + sd->sc.data[SC__ENERVATION].val1 * 10) / 100;
		}
		// マスカレード：グルーミー
		if(sd->sc.data[SC__GROOMY].timer != -1) {
			sd->hit -= sd->hit * (sd->sc.data[SC__GROOMY].val1 * 20) / 100;
		}
		// マスカレード：レイジネス
		if(sd->sc.data[SC__LAZINESS].timer != -1) {
			sd->flee -= sd->flee*10/100;
		}
		// マスカレード：アンラッキー
		if(sd->sc.data[SC__UNLUCKY].timer != -1) {
			sd->critical -= sd->critical * (sd->sc.data[SC__UNLUCKY].val1 * 10) / 100;
			sd->flee2 -= sd->sc.data[SC__UNLUCKY].val1 * 10;
		}
		// シールドスペル(DEF)
		if(sd->sc.data[SC_SHIELDSPELL_DEF].timer != -1 && sd->sc.data[SC_SHIELDSPELL_DEF].val2 == 2) {
#ifdef PRE_RENEWAL
			sd->base_atk += sd->sc.data[SC_SHIELDSPELL_DEF].val3;
#else
			sd->plus_atk += sd->sc.data[SC_SHIELDSPELL_DEF].val3;
#endif
		}
		// シールドスペル(精錬)
		if(sd->sc.data[SC_SHIELDSPELL_REF].timer != -1 && sd->sc.data[SC_SHIELDSPELL_REF].val2 == 2) {
#ifdef PRE_RENEWAL
			sd->def2 += sd->sc.data[SC_SHIELDSPELL_REF].val3;
#else
			sd->def += sd->sc.data[SC_SHIELDSPELL_REF].val3;
#endif
		}
		// フォースオブバンガード
		if(sd->sc.data[SC_FORCEOFVANGUARD].timer != -1) {
			sd->status.max_hp += (sd->status.max_hp * sd->sc.data[SC_FORCEOFVANGUARD].val1 * 3) / 100;
		}
		// プレスティージ
		if(sd->sc.data[SC_PRESTIGE].timer != -1) {
#ifdef PRE_RENEWAL
			sd->def2 += sd->sc.data[SC_PRESTIGE].val2;
#else
			sd->def += sd->sc.data[SC_PRESTIGE].val2;
#endif
		}
		// バンディング
		if(sd->sc.data[SC_BANDING].timer != -1 && sd->sc.data[SC_BANDING].val2 > 1) {
#ifdef PRE_RENEWAL
			sd->base_atk += (10 + sd->sc.data[SC_BANDING].val1 * 10) * sd->sc.data[SC_BANDING].val2;
			sd->def2 += (5 + sd->sc.data[SC_BANDING].val1) * sd->sc.data[SC_BANDING].val2;
#else
			sd->plus_atk += (10 + sd->sc.data[SC_BANDING].val1 * 10) * sd->sc.data[SC_BANDING].val2;
			sd->def += (5 + sd->sc.data[SC_BANDING].val1) * sd->sc.data[SC_BANDING].val2;
#endif
		}
		// アースドライブ
		if(sd->sc.data[SC_EARTHDRIVE].timer != -1) {
			sd->def -= sd->def * 25 / 100;
		}
		// インスピレーション
		if(sd->sc.data[SC_INSPIRATION].timer != -1) {
			sd->status.max_hp += (600 + sd->status.max_hp / 20) * sd->sc.data[SC_INSPIRATION].val1;
#ifdef PRE_RENEWAL
			sd->base_atk += sd->sc.data[SC_INSPIRATION].val1 * 40 + sd->status.job_level * 3;
#else
			sd->plus_atk += sd->sc.data[SC_INSPIRATION].val1 * 40 + sd->status.job_level * 3;
#endif
			sd->hit += 25 + sd->sc.data[SC_INSPIRATION].val1 * 5;
		}
		// 潜竜昇天
		if(sd->sc.data[SC_RAISINGDRAGON].timer != -1) {
			sd->status.max_hp += sd->status.max_hp * sd->sc.data[SC_RAISINGDRAGON].val3 / 100;
			sd->status.max_sp += sd->status.max_sp * sd->sc.data[SC_RAISINGDRAGON].val3 / 100;
		}
		// 点穴 -反-
		if(sd->sc.data[SC_GENTLETOUCH_CHANGE].timer != -1) {
			sd->status.max_hp -= sd->status.max_hp * (sd->sc.data[SC_GENTLETOUCH_CHANGE].val1 * 2) / 100;
		}
		// 点穴 -活-
		if(sd->sc.data[SC_GENTLETOUCH_REVITALIZE].timer != -1) {
			sd->status.max_hp += sd->status.max_hp * (sd->sc.data[SC_GENTLETOUCH_REVITALIZE].val1 * 3) / 100;
		}
		// フリッグの歌
		if(sd->sc.data[SC_FRIGG_SONG].timer != -1) {
			sd->status.max_hp += sd->sc.data[SC_FRIGG_SONG].val3 * sd->status.max_hp / 100;
		}
		// メランコリー
		if(sd->sc.data[SC_GLOOMYDAY].timer != -1) {
			sd->flee -= sd->sc.data[SC_GLOOMYDAY].val1 * 5 + 20;
		}
		// レーラズの露
		if(sd->sc.data[SC_LERADS_DEW].timer != -1) {
			sd->status.max_hp += sd->sc.data[SC_LERADS_DEW].val1 * 200 + sd->sc.data[SC_LERADS_DEW].val4 * 300;
		}
		// ビヨンドオブウォークライ
		if(sd->sc.data[SC_BEYOND_OF_WARCRY].timer != -1) {
			sd->status.max_hp -= sd->sc.data[SC_BEYOND_OF_WARCRY].val3 * sd->status.max_hp / 100;
			sd->critical += sd->sc.data[SC_BEYOND_OF_WARCRY].val4 * 10;
		}
		// フライデーナイトフィーバー
		if(sd->sc.data[SC_SATURDAY_NIGHT_FEVER].timer != -1) {
			sd->watk += 100 * sd->sc.data[SC_SATURDAY_NIGHT_FEVER].val1;
			sd->def -= sd->def * (10 + 10 * sd->sc.data[SC_SATURDAY_NIGHT_FEVER].val1) / 100;
			sd->flee -= sd->flee * (40 + 10 * sd->sc.data[SC_SATURDAY_NIGHT_FEVER].val1) / 100;
		}
		// ストライキング
		if(sd->sc.data[SC_STRIKING].timer != -1) {
			sd->critical += 10 * sd->sc.data[SC_STRIKING].val1;
		}
		// オーディンの力
		if(sd->sc.data[SC_ODINS_POWER].timer != -1) {
#ifdef PRE_RENEWAL
			sd->watk += 60 + 10 * sd->sc.data[SC_ODINS_POWER].val1;
			sd->matk1 += 60 + 10 * sd->sc.data[SC_ODINS_POWER].val1;
			sd->matk2 += 60 + 10 * sd->sc.data[SC_ODINS_POWER].val1;
#else
			sd->plus_atk += 60 + 10 * sd->sc.data[SC_ODINS_POWER].val1;
			sd->plus_matk += 60 + 10 * sd->sc.data[SC_ODINS_POWER].val1;
#endif
			sd->def -= 10 + 10 * sd->sc.data[SC_ODINS_POWER].val1;
			sd->mdef -= 10 + 10 * sd->sc.data[SC_ODINS_POWER].val1;
		}
		// ファイアーエクスパンション(煙幕)
		if(sd->sc.data[SC_FIRE_EXPANSION_SMOKE_POWDER].timer != -1) {
			sd->flee += sd->flee * sd->sc.data[SC_FIRE_EXPANSION_SMOKE_POWDER].val3 / 100;
		}
		// ファイアーエクスパンション(催涙)
		if(sd->sc.data[SC_FIRE_EXPANSION_TEAR_GAS].timer != -1) {
			sd->hit -= sd->hit * sd->sc.data[SC_FIRE_EXPANSION_TEAR_GAS].val2 / 100;
			sd->flee -= sd->flee * sd->sc.data[SC_FIRE_EXPANSION_TEAR_GAS].val2 / 100;
		}
		// HP増加ポーション
		if(sd->sc.data[SC_PROMOTE_HEALTH_RESERCH].timer != -1) {
			sd->status.max_hp += 500 + sd->sc.data[SC_PROMOTE_HEALTH_RESERCH].val1 * 1000 + 4 / 3 * sd->status.base_level;
		}
		// SP増加ポーション
		if(sd->sc.data[SC_ENERGY_DRINK_RESERCH].timer != -1) {
			sd->status.max_sp += sd->status.max_sp * ((sd->sc.data[SC_ENERGY_DRINK_RESERCH].val1 * 5) - 5 + sd->status.base_level / 10) / 100;
		}
		// ビタタ500
		if(sd->sc.data[SC_VITATA_500].timer != -1) {
			sd->status.max_sp += sd->status.max_sp * sd->sc.data[SC_VITATA_500].val2 / 100;
		}
		// ファイアークローク
		if(sd->sc.data[SC_FIRE_CLOAK].timer != -1) {
			sd->subele[ELE_FIRE] += sd->sc.data[SC_FIRE_CLOAK].val2;
			sd->subele[ELE_WATER] -= sd->sc.data[SC_FIRE_CLOAK].val3;
		}
		// ウォータードロップ
		if(sd->sc.data[SC_WATER_DROP].timer != -1) {
			sd->subele[ELE_WATER] += sd->sc.data[SC_WATER_DROP].val2;
			sd->subele[ELE_WIND] -= sd->sc.data[SC_WATER_DROP].val3;
		}
		// ウィンドステップ
		if(sd->sc.data[SC_WIND_STEP].timer != -1) {
			sd->flee += sd->sc.data[SC_WIND_STEP].val2;
		}
		// ウィンドカーテン
		if(sd->sc.data[SC_WIND_CURTAIN].timer != -1) {
			sd->subele[ELE_WIND] += sd->sc.data[SC_WIND_CURTAIN].val2;
			sd->subele[ELE_EARTH] -= sd->sc.data[SC_WIND_CURTAIN].val3;
		}
		// ソリッドスキン
		if(sd->sc.data[SC_SOLID_SKIN].timer != -1) {
			sd->def += sd->def * sd->sc.data[SC_SOLID_SKIN].val2 / 100;
			sd->status.max_hp += sd->status.max_hp * sd->sc.data[SC_SOLID_SKIN].val3 / 100;
		}
		// ストーンシールド
		if(sd->sc.data[SC_STONE_SHIELD].timer != -1) {
			sd->subele[ELE_EARTH] += sd->sc.data[SC_STONE_SHIELD].val2;
			sd->subele[ELE_FIRE] -= sd->sc.data[SC_STONE_SHIELD].val3;
		}
		// パイロテクニック
		if(sd->sc.data[SC_PYROTECHNIC].timer != -1) {
			sd->watk += sd->sc.data[SC_PYROTECHNIC].val2;
		}
		// ヒーター
		if(sd->sc.data[SC_HEATER].timer != -1) {
			sd->watk += sd->sc.data[SC_HEATER].val2;
		}
		// トロピック
		if(sd->sc.data[SC_TROPIC].timer != -1) {
			sd->watk += sd->sc.data[SC_TROPIC].val2;
		}
		// アクアプレイ
		if(sd->sc.data[SC_AQUAPLAY].timer != -1) {
			sd->matk1 += sd->sc.data[SC_AQUAPLAY].val2;
			sd->matk2 += sd->sc.data[SC_AQUAPLAY].val2;
		}
		// クーラー
		if(sd->sc.data[SC_COOLER].timer != -1) {
			sd->matk1 += sd->sc.data[SC_COOLER].val2;
			sd->matk2 += sd->sc.data[SC_COOLER].val2;
		}
		// クールエアー
		if(sd->sc.data[SC_CHILLY_AIR].timer != -1) {
			sd->matk1 += sd->sc.data[SC_CHILLY_AIR].val2;
			sd->matk2 += sd->sc.data[SC_CHILLY_AIR].val2;
		}
		// ペトロジー
		if(sd->sc.data[SC_PETROLOGY].timer != -1) {
			sd->status.max_hp += sd->status.max_hp * sd->sc.data[SC_PETROLOGY].val2 / 100;
		}
		// カースドソイル
		if(sd->sc.data[SC_CURSED_SOIL].timer != -1) {
			sd->status.max_hp += sd->status.max_hp * sd->sc.data[SC_CURSED_SOIL].val2 / 100;
		}
		// アップヘイバル
		if(sd->sc.data[SC_UPHEAVAL].timer != -1) {
			sd->status.max_hp += sd->status.max_hp * sd->sc.data[SC_UPHEAVAL].val2 / 100;
		}
		// 十六夜
		if(sd->sc.data[SC_IZAYOI].timer != -1) {
#ifdef PRE_RENEWAL
			sd->matk1 += sd->sc.data[SC_IZAYOI].val2;
			sd->matk2 += sd->sc.data[SC_IZAYOI].val2;
#else
			sd->plus_matk += sd->sc.data[SC_IZAYOI].val2;
#endif
		}
		// 幻術 -分身-
		if(sd->sc.data[SC_KAGEMUSYA].timer != -1) {
			sd->skill_dmgup.id[sd->skill_dmgup.count] = KO_BAKURETSU;
			sd->skill_dmgup.rate[sd->skill_dmgup.count] = sd->sc.data[SC_KAGEMUSYA].val2;
			sd->skill_dmgup.count++;
			sd->skill_dmgup.id[sd->skill_dmgup.count] = KO_HAPPOKUNAI;
			sd->skill_dmgup.rate[sd->skill_dmgup.count] = sd->sc.data[SC_KAGEMUSYA].val2;
			sd->skill_dmgup.count++;
			sd->skill_dmgup.id[sd->skill_dmgup.count] = KO_JYUMONJIKIRI;
			sd->skill_dmgup.rate[sd->skill_dmgup.count] = sd->sc.data[SC_KAGEMUSYA].val2;
			sd->skill_dmgup.count++;
			sd->skill_dmgup.id[sd->skill_dmgup.count] = KO_HUUMARANKA;
			sd->skill_dmgup.rate[sd->skill_dmgup.count] = sd->sc.data[SC_KAGEMUSYA].val2;
			sd->skill_dmgup.count++;
		}
		// 幻術 -残月-
		if(sd->sc.data[SC_ZANGETSU].timer != -1) {
#ifdef PRE_RENEWAL
			sd->base_atk += sd->sc.data[SC_ZANGETSU].val2;
			sd->matk1 += sd->sc.data[SC_ZANGETSU].val3;
			sd->matk2 += sd->sc.data[SC_ZANGETSU].val3;
#else
			sd->plus_atk += sd->sc.data[SC_ZANGETSU].val2;
			sd->plus_matk += sd->sc.data[SC_ZANGETSU].val3;
#endif
		}
		// アンリミット
		if(sd->sc.data[SC_UNLIMIT].timer != -1) {
			sd->def = sd->def2 = sd->mdef = sd->mdef2 = 1;
		}
		// イリュージョンドーピング
		if(sd->sc.data[SC_ILLUSIONDOPING].timer != -1) {
			sd->hit -= 50;
		}
		// ニャングラス
		if(sd->sc.data[SC_NYANGGRASS].timer != -1) {
			sd->def = sd->mdef = 0;
		}
		// 警戒
		if(sd->sc.data[SC_HISS].timer != -1 && sd->sc.data[SC_HISS].val1 > 0) {
			sd->flee2 += sd->sc.data[SC_HISS].val2;
		}
		// イヌハッカシャワー
		if(sd->sc.data[SC_CATNIPPOWDER].timer != -1) {
			sd->watk -= sd->watk * sd->sc.data[SC_CATNIPPOWDER].val2 / 100;
			sd->matk1 -= sd->matk1 * sd->sc.data[SC_CATNIPPOWDER].val2 / 100;
			sd->nhealhp += sd->nhealhp * sd->sc.data[SC_CATNIPPOWDER].val3 / 100;
			if(sd->nhealhp > 0x7fff)
				sd->nhealhp = 0x7fff;
			sd->nhealsp += sd->nhealsp * sd->sc.data[SC_CATNIPPOWDER].val3 / 100;
			if(sd->nhealsp > 0x7fff)
				sd->nhealsp = 0x7fff;
		}
		// 影の魂
		if(sd->sc.data[SC_SOULSHADOW].timer != -1) {
			sd->critical += sd->sc.data[SC_SOULSHADOW].val2;
		}
		// 妖精の魂
		if(sd->sc.data[SC_SOULFAIRY].timer != -1) {
#ifdef PRE_RENEWAL
			sd->matk1 += sd->sc.data[SC_SOULFAIRY].val2;
			sd->matk2 += sd->sc.data[SC_SOULFAIRY].val2;
#else
			sd->plus_matk += sd->sc.data[SC_SOULFAIRY].val2;
#endif
		}
		// 鷹の魂
		if(sd->sc.data[SC_SOULFALCON].timer != -1) {
#ifdef PRE_RENEWAL
			sd->watk += sd->sc.data[SC_SOULFALCON].val2;
#else
			sd->plus_atk += sd->sc.data[SC_SOULFALCON].val2;
#endif
			sd->hit += sd->sc.data[SC_SOULFALCON].val3;
		}
		// ゴーレムの魂
		if(sd->sc.data[SC_SOULGOLEM].timer != -1) {
#ifdef PRE_RENEWAL
			sd->def2 += sd->sc.data[SC_SOULGOLEM].val2;
			sd->mdef2 += sd->sc.data[SC_SOULGOLEM].val3;
#else
			sd->def += sd->sc.data[SC_SOULGOLEM].val2;
			sd->mdef += sd->sc.data[SC_SOULGOLEM].val3;
#endif
		}
		// オーバードブースト
		if(sd->sc.data[SC_OVERED_BOOST].timer != -1) {
			sd->flee = sd->sc.data[SC_OVERED_BOOST].val3;
			sd->aspd = sd->sc.data[SC_OVERED_BOOST].val4;
			sd->amotion = sd->aspd>>1;
		}
		// E.Q.C
		if(sd->sc.data[SC_EQC].timer != -1) {
			sd->watk -= sd->watk * sd->sc.data[SC_EQC].val4 / 100;
			sd->def2 -= sd->def2 * sd->sc.data[SC_EQC].val4 / 100;
		}
		// パイロクラスティック
		if(sd->sc.data[SC_PYROCLASTIC].timer != -1) {
			sd->watk += sd->sc.data[SC_PYROCLASTIC].val2;
		}
		// デッドリープロジェクション
		if(sd->sc.data[SC_DEADLY_DEFEASANCE].timer != -1) {
			sd->special_state.no_magic_damage = 0;
		}
		// 強靭な信念
		if(sd->sc.data[SC_POWERFUL_FAITH].timer != -1) {
#ifdef PRE_RENEWAL
			sd->watk += sd->sc.data[SC_POWERFUL_FAITH].val2;
#else
			sd->plus_atk += sd->sc.data[SC_POWERFUL_FAITH].val2;
#endif
			sd->patk += sd->sc.data[SC_POWERFUL_FAITH].val3;
		}
		// 堅固な信念
		if(sd->sc.data[SC_FIRM_FAITH].timer != -1) {
			sd->status.max_hp += sd->status.max_hp * sd->sc.data[SC_FIRM_FAITH].val2 / 100;
			sd->res += sd->sc.data[SC_FIRM_FAITH].val3;
		}
		// 忠実な信念
		if(sd->sc.data[SC_SINCERE_FAITH].timer != -1) {
			sd->perfect_hit += sd->sc.data[SC_SINCERE_FAITH].val3;
		}
		// ガードスタンス
		if(sd->sc.data[SC_GUARD_STANCE].timer != -1) {
#ifdef PRE_RENEWAL
			sd->def2 += sd->sc.data[SC_GUARD_STANCE].val2;
			sd->watk -= sd->sc.data[SC_GUARD_STANCE].val3;
#else
			sd->def += sd->sc.data[SC_GUARD_STANCE].val2;
			sd->plus_atk -= sd->sc.data[SC_GUARD_STANCE].val3;
#endif
		}
		// アタックスタンス
		if(sd->sc.data[SC_ATTACK_STANCE].timer != -1) {
			sd->patk += sd->sc.data[SC_ATTACK_STANCE].val2;
			sd->smatk += sd->sc.data[SC_ATTACK_STANCE].val2;
#ifdef PRE_RENEWAL
			sd->def2 -= sd->sc.data[SC_ATTACK_STANCE].val3;
#else
			sd->def -= sd->sc.data[SC_ATTACK_STANCE].val3;
#endif
		}
		// ホーリーシールド
		if(sd->sc.data[SC_HOLY_S].timer != -1) {
			sd->skill_elemagic_dmgup[ELE_HOLY] += sd->sc.data[SC_HOLY_S].val2;
			sd->subele[ELE_DARK] += sd->sc.data[SC_HOLY_S].val3;
			sd->subele[ELE_UNDEAD] += sd->sc.data[SC_HOLY_S].val3;
		}
		// プレセンスアキエース
		if(sd->sc.data[SC_PRE_ACIES].timer != -1) {
			sd->crate += sd->sc.data[SC_PRE_ACIES].val2;
		}
		// コンペテンティア
		if(sd->sc.data[SC_COMPETENTIA].timer != -1) {
			sd->patk += sd->sc.data[SC_COMPETENTIA].val2;
			sd->smatk += sd->sc.data[SC_COMPETENTIA].val3;
		}
		// ラッシュ
		if(sd->sc.data[SC_RUSH_QUAKE2].timer != -1) {
			sd->short_weapon_damege_rate += sd->sc.data[SC_RUSH_QUAKE2].val2;
			sd->long_weapon_damege_rate += sd->sc.data[SC_RUSH_QUAKE2].val2;
		}
		// 防御装置有効化
		if(sd->sc.data[SC_D_MACHINE].timer != -1) {
#ifdef PRE_RENEWAL
			sd->def2 += sd->sc.data[SC_D_MACHINE].val2;
#else
			sd->def += sd->sc.data[SC_D_MACHINE].val2;
#endif
			sd->res += sd->sc.data[SC_D_MACHINE].val3;
		}
		// アビススレイヤー
		if(sd->sc.data[SC_ABYSS_SLAYER].timer != -1) {
			sd->patk += sd->sc.data[SC_ABYSS_SLAYER].val2;
			sd->smatk += sd->sc.data[SC_ABYSS_SLAYER].val2;
			sd->hit += sd->sc.data[SC_ABYSS_SLAYER].val3;
		}
		// ヘルダスティ
		if(sd->sc.data[SC_BO_HELL_DUSTY].timer != -1) {
			sd->addrace[RCT_FORMLESS] += sd->sc.data[SC_BO_HELL_DUSTY].val2;
			sd->addrace[RCT_PLANT] += sd->sc.data[SC_BO_HELL_DUSTY].val2;
			sd->long_weapon_damege_rate += sd->sc.data[SC_BO_HELL_DUSTY].val3;
		}
		// ミスティックシンフォニー
		if(sd->sc.data[SC_MYSTIC_SYMPHONY].timer != -1) {
			sd->skill_dmgup.id[sd->skill_dmgup.count] = TR_SOUNDBLEND;
			sd->skill_dmgup.rate[sd->skill_dmgup.count] = sd->sc.data[SC_MYSTIC_SYMPHONY].val2;
			sd->skill_dmgup.count++;
			sd->skill_dmgup.id[sd->skill_dmgup.count] = TR_RHYTHMSHOOTING;
			sd->skill_dmgup.rate[sd->skill_dmgup.count] = sd->sc.data[SC_MYSTIC_SYMPHONY].val2;
			sd->skill_dmgup.count++;
			sd->skill_dmgup.id[sd->skill_dmgup.count] = TR_ROSEBLOSSOM;
			sd->skill_dmgup.rate[sd->skill_dmgup.count] = sd->sc.data[SC_MYSTIC_SYMPHONY].val2;
			sd->skill_dmgup.count++;
			sd->skill_dmgup.id[sd->skill_dmgup.count] = TR_ROSEBLOSSOM_ATK;
			sd->skill_dmgup.rate[sd->skill_dmgup.count] = sd->sc.data[SC_MYSTIC_SYMPHONY].val2;
			sd->skill_dmgup.count++;
		}
		// ゲフェニアノクターン
		if(sd->sc.data[SC_GEF_NOCTURN].timer != -1) {
			sd->mres -= sd->sc.data[SC_GEF_NOCTURN].val3;
		}
		// 鉱員のラプソディ
		if(sd->sc.data[SC_AIN_RHAPSODY].timer != -1) {
			sd->res -= sd->sc.data[SC_AIN_RHAPSODY].val3;
		}
		// ミュージカルインタールード
		if(sd->sc.data[SC_MUSICAL_INTERLUDE].timer != -1) {
			sd->res += sd->sc.data[SC_MUSICAL_INTERLUDE].val3;
		}
		// 夕焼けのセレナーデ
		if(sd->sc.data[SC_JAWAII_SERENADE].timer != -1) {
			sd->smatk += sd->sc.data[SC_JAWAII_SERENADE].val3;
		}
		// プロンテラマーチ
		if(sd->sc.data[SC_PRON_MARCH].timer != -1) {
			sd->patk += sd->sc.data[SC_PRON_MARCH].val3;
		}
		// スペルエンチャンティング
		if(sd->sc.data[SC_SPELL_ENCHANTING].timer != -1) {
			sd->smatk += sd->sc.data[SC_SPELL_ENCHANTING].val2;
		}
		// サモンアルドール
		if(sd->sc.data[SC_SUMMON_ELEMENTAL_ARDOR].timer != -1) {
			sd->skill_elemagic_dmgup[ELE_FIRE] += sd->sc.data[SC_SUMMON_ELEMENTAL_ARDOR].val2;
		}
		// サモンディルビオ
		if(sd->sc.data[SC_SUMMON_ELEMENTAL_DILUVIO].timer != -1) {
			sd->skill_elemagic_dmgup[ELE_WATER] += sd->sc.data[SC_SUMMON_ELEMENTAL_DILUVIO].val2;
		}
		// サモンプロセラ
		if(sd->sc.data[SC_SUMMON_ELEMENTAL_PROCELLA].timer != -1) {
			sd->skill_elemagic_dmgup[ELE_WIND] += sd->sc.data[SC_SUMMON_ELEMENTAL_PROCELLA].val2;
		}
		// サモンテレモトゥス
		if(sd->sc.data[SC_SUMMON_ELEMENTAL_TERREMOTUS].timer != -1) {
			sd->skill_elemagic_dmgup[ELE_EARTH] += sd->sc.data[SC_SUMMON_ELEMENTAL_TERREMOTUS].val2;
		}
		// サモンサーペンス
		if(sd->sc.data[SC_SUMMON_ELEMENTAL_SERPENS].timer != -1) {
			sd->skill_elemagic_dmgup[ELE_POISON] += sd->sc.data[SC_SUMMON_ELEMENTAL_SERPENS].val2;
		}
		// フレイムテクニック
		if(sd->sc.data[SC_FLAMETECHNIC].timer != -1) {
			sd->skill_dmgup.id[sd->skill_dmgup.count] = MG_FIREBOLT;
			sd->skill_dmgup.rate[sd->skill_dmgup.count] = sd->sc.data[SC_FLAMETECHNIC].val2;
			sd->skill_dmgup.count++;
		}
		// コールドフォース
		if(sd->sc.data[SC_COLD_FORCE].timer != -1) {
			sd->skill_dmgup.id[sd->skill_dmgup.count] = MG_COLDBOLT;
			sd->skill_dmgup.rate[sd->skill_dmgup.count] = sd->sc.data[SC_COLD_FORCE].val2;
			sd->skill_dmgup.count++;
		}
		// グレイスブリーズ
		if(sd->sc.data[SC_GRACE_BREEZE].timer != -1) {
			sd->skill_dmgup.id[sd->skill_dmgup.count] = MG_LIGHTNINGBOLT;
			sd->skill_dmgup.rate[sd->skill_dmgup.count] = sd->sc.data[SC_GRACE_BREEZE].val2;
			sd->skill_dmgup.count++;
		}
		// アースケア
		if(sd->sc.data[SC_EARTH_CARE].timer != -1) {
			sd->skill_dmgup.id[sd->skill_dmgup.count] = WZ_EARTHSPIKE;
			sd->skill_dmgup.rate[sd->skill_dmgup.count] = sd->sc.data[SC_EARTH_CARE].val2;
			sd->skill_dmgup.count++;
		}
		// ディープポイズニング
		if(sd->sc.data[SC_DEEP_POISONING].timer != -1) {
			sd->skill_dmgup.id[sd->skill_dmgup.count] = SO_CLOUD_KILL;
			sd->skill_dmgup.rate[sd->skill_dmgup.count] = sd->sc.data[SC_DEEP_POISONING].val2;
			sd->skill_dmgup.count++;
		}
		// フレイムアーマー
		if(sd->sc.data[SC_FLAMEARMOR].timer != -1) {
			sd->subele[ELE_FIRE] += sd->sc.data[SC_FLAMEARMOR].val2;
		}
		// クリスタルアーマー
		if(sd->sc.data[SC_CRYSTAL_ARMOR].timer != -1) {
			sd->subele[ELE_WATER] += sd->sc.data[SC_CRYSTAL_ARMOR].val2;
		}
		// アイズオブストーム
		if(sd->sc.data[SC_EYES_OF_STORM].timer != -1) {
			sd->subele[ELE_WIND] += sd->sc.data[SC_EYES_OF_STORM].val2;
		}
		// ストロングプロテクション
		if(sd->sc.data[SC_STRONG_PROTECTION].timer != -1) {
			sd->subele[ELE_EARTH] += sd->sc.data[SC_STRONG_PROTECTION].val2;
		}
		// ポイズンシールド
		if(sd->sc.data[SC_POISON_SHIELD].timer != -1) {
			sd->subele[ELE_POISON] += sd->sc.data[SC_POISON_SHIELD].val2;
		}
		// インテンシブエイム
		if(sd->sc.data[SC_INTENSIVE_AIM].timer != -1) {
#ifdef PRE_RENEWAL
			sd->watk += sd->sc.data[SC_INTENSIVE_AIM].val2;
#else
			sd->plus_atk += sd->sc.data[SC_INTENSIVE_AIM].val2;
#endif
			sd->hit += sd->sc.data[SC_INTENSIVE_AIM].val3;
			sd->critical += sd->sc.data[SC_INTENSIVE_AIM].val4 * 10;
		}
		// ヒドゥンカード
		if(sd->sc.data[SC_HIDDEN_CARD].timer != -1) {
			sd->patk += sd->sc.data[SC_HIDDEN_CARD].val2;
			sd->long_weapon_damege_rate += sd->sc.data[SC_HIDDEN_CARD].val3;
		}
		// 武士符
		if(sd->sc.data[SC_TALISMAN_OF_WARRIOR].timer != -1) {
			sd->patk += sd->sc.data[SC_TALISMAN_OF_WARRIOR].val2;
		}
		// 法師符
		if(sd->sc.data[SC_TALISMAN_OF_MAGICIAN].timer != -1) {
			sd->smatk += sd->sc.data[SC_TALISMAN_OF_MAGICIAN].val2;
		}
		// 五行符
		if(sd->sc.data[SC_TALISMAN_OF_FIVE_ELEMENTS].timer != -1) {
			sd->addele[ELE_FIRE]  += sd->sc.data[SC_TALISMAN_OF_FIVE_ELEMENTS].val2;
			sd->addele[ELE_WATER] += sd->sc.data[SC_TALISMAN_OF_FIVE_ELEMENTS].val2;
			sd->addele[ELE_WIND]  += sd->sc.data[SC_TALISMAN_OF_FIVE_ELEMENTS].val2;
			sd->addele[ELE_EARTH] += sd->sc.data[SC_TALISMAN_OF_FIVE_ELEMENTS].val2;
			sd->magic_addele[ELE_FIRE]  += sd->sc.data[SC_TALISMAN_OF_FIVE_ELEMENTS].val2;
			sd->magic_addele[ELE_WATER] += sd->sc.data[SC_TALISMAN_OF_FIVE_ELEMENTS].val2;
			sd->magic_addele[ELE_WIND]  += sd->sc.data[SC_TALISMAN_OF_FIVE_ELEMENTS].val2;
			sd->magic_addele[ELE_EARTH] += sd->sc.data[SC_TALISMAN_OF_FIVE_ELEMENTS].val2;
		}
		// 四方五行陣
		if(sd->sc.data[SC_T_FIVETH_GOD].timer != -1) {
			sd->smatk += sd->sc.data[SC_T_FIVETH_GOD].val2;
		}
		// 天地神霊
		if(sd->sc.data[SC_HEAVEN_AND_EARTH].timer != -1) {
			sd->short_weapon_damege_rate += sd->sc.data[SC_HEAVEN_AND_EARTH].val2;
			sd->long_weapon_damege_rate += sd->sc.data[SC_HEAVEN_AND_EARTH].val2;
			for(w->i = 0; w->i < ELE_MAX; w->i++) {
				sd->magic_addele[w->i] += sd->sc.data[SC_HEAVEN_AND_EARTH].val2;
			}
		}
		// 三霊一体
		if(sd->sc.data[SC_TEMPORARY_COMMUNION].timer != -1) {
			sd->patk += sd->sc.data[SC_TEMPORARY_COMMUNION].val2;
			sd->smatk += sd->sc.data[SC_TEMPORARY_COMMUNION].val3;
			sd->hplus += sd->sc.data[SC_TEMPORARY_COMMUNION].val4;
		}
		// にゃんブレッシング
		if(sd->sc.data[SC_BLESSING_OF_M_CREATURES].timer != -1) {
			sd->patk += sd->sc.data[SC_BLESSING_OF_M_CREATURES].val2;
			sd->smatk += sd->sc.data[SC_BLESSING_OF_M_CREATURES].val3;
		}
		// 漆黒
		if(sd->sc.data[SC_HANDICAPSTATE_DEEPBLIND].timer != -1) {
			sd->flee = 0;
			sd->flee2 = 0;
		}
		// 無気力
		if(sd->sc.data[SC_HANDICAPSTATE_LASSITUDE].timer != -1) {
			sd->critical = 0;
		}
		// 急冷
		if(sd->sc.data[SC_HANDICAPSTATE_FROSTBITE].timer != -1) {
			sd->def -= sd->def * sd->sc.data[SC_HANDICAPSTATE_FROSTBITE].val2 / 100;
			sd->def2 -= sd->def2 * sd->sc.data[SC_HANDICAPSTATE_FROSTBITE].val2 / 100;
			sd->mdef -= sd->mdef * sd->sc.data[SC_HANDICAPSTATE_FROSTBITE].val2 / 100;
			sd->mdef2 -= sd->mdef2 * sd->sc.data[SC_HANDICAPSTATE_FROSTBITE].val2 / 100;
		}
		// 結晶化
		if(sd->sc.data[SC_HANDICAPSTATE_CRYSTALLIZATION].timer != -1) {
			sd->mdef = 0;
			sd->mdef2 = 0;
		}
		// 不幸
		if(sd->sc.data[SC_HANDICAPSTATE_MISFORTUNE].timer != -1) {
			sd->hit = 0;
		}
		// 強毒
		if(sd->sc.data[SC_HANDICAPSTATE_DEADLYPOISON].timer != -1) {
			sd->def = 0;
			sd->def2 = 0;
		}
	}

	// 影狼・朧の球体
	if(sd->elementball.num >= MAX_ELEMENTBALL) {
		if(sd->elementball.ele == ELE_FIRE) {			/* 火符：炎天 */
			sd->addele[ELE_EARTH] += 30;
		}
		else if(sd->elementball.ele == ELE_WATER) {		/* 氷符：吹雪 */
			sd->addele[ELE_FIRE] += 30;
		}
		else if(sd->elementball.ele == ELE_WIND) {		/* 風符：青嵐 */
			sd->addele[ELE_WATER] += 30;
		}
		else if(sd->elementball.ele == ELE_EARTH) {		/* 土符：剛塊 */
			sd->addele[ELE_WIND] += 30;
		}
	}

	// テコンランカーボーナス
	if(sd->status.class_ == PC_CLASS_TK && sd->status.base_level >= 90 && ranking_get_pc_rank(sd,RK_TAEKWON) > 0)
	{
		sd->status.max_hp *= 3;
		sd->status.max_sp *= 3;
	}

#ifdef PRE_RENEWAL
	// 土符：剛塊
	if(sd->elementball.num && sd->elementball.ele == ELE_EARTH) {
		sd->watk += sd->watk * sd->elementball.num * 10 / 100;
	}
#endif
	// ソウルエナジー
	if(sd->soulenergy.num > 0) {
#ifdef PRE_RENEWAL
		sd->matk1 += sd->soulenergy.num * 3;
		sd->matk2 += sd->soulenergy.num * 3;
#else
		sd->plus_matk += sd->soulenergy.num * 3;
#endif
	}

	// MATK乗算処理(杖補正)
	if(sd->matk2_rate != 100) {
		sd->matk1 = sd->matk1 * sd->matk2_rate / 100;
		sd->matk2 = sd->matk2 * sd->matk2_rate / 100;
	}

	// ステータス固定
	if(sd->fix_status.max_hp > 0) {
		sd->status.max_hp = sd->fix_status.max_hp;
	}
	if(sd->fix_status.max_sp > 0) {
		sd->status.max_sp = sd->fix_status.max_sp;
	}
	if(sd->fix_status.atk > 0) {
		sd->base_atk = sd->fix_status.atk;
		sd->watk = sd->watk2 = 0;
	}
	if(sd->fix_status.matk > 0) {
		sd->matk1 = sd->matk2 = sd->fix_status.matk;
		// MATK乗算処理(固定値*(杖補正+杖補正以外))
#ifdef PRE_RENEWAL
		if(sd->matk_rate != 100 || sd->matk2_rate != 100) {
			sd->matk1 = sd->matk1 * (sd->matk_rate + sd->matk2_rate - 100) / 100;
			sd->matk2 = sd->matk2 * (sd->matk_rate + sd->matk2_rate - 100) / 100;
		}
#else
		if(sd->matk2_rate != 100) {
			sd->matk1 = sd->matk1 * sd->matk2_rate / 100;
			sd->matk2 = sd->matk2 * sd->matk2_rate / 100;
		}
#endif
	}
	if(sd->fix_status.def > 0 && sd->fix_status.def <= 100) {
		sd->def = sd->fix_status.def;
	}
	if(sd->fix_status.mdef > 0 && sd->fix_status.mdef <= 100) {
		sd->mdef = sd->fix_status.mdef;
	}
	if(sd->fix_status.hit > 0) {
		sd->hit = sd->fix_status.hit;
	}
	if(sd->fix_status.critical > 0) {
		sd->critical = 10 * sd->fix_status.critical;
	}
	if(sd->fix_status.flee > 0) {
		sd->flee = sd->fix_status.flee;
	}

	if((pc_is3rdclass(sd) || pc_is4thclass(sd)) && sd->aspd < battle_config.third_max_aspd) {
		sd->aspd = battle_config.third_max_aspd;
		sd->amotion = sd->aspd>>1;
	}
	else if(sd->s_class.job == PC_JOB_ESNV && sd->aspd < battle_config.esnv_max_aspd) {
		sd->aspd = battle_config.esnv_max_aspd;
		sd->amotion = sd->aspd>>1;
	}
	else if((sd->s_class.job == PC_JOB_KG || sd->s_class.job == PC_JOB_OB) && sd->aspd < battle_config.ko_max_aspd) {
		sd->aspd = battle_config.ko_max_aspd;
		sd->amotion = sd->aspd>>1;
	}
	else if(sd->s_class.job == PC_JOB_RL && sd->aspd < battle_config.rl_max_aspd) {
		sd->aspd = battle_config.rl_max_aspd;
		sd->amotion = sd->aspd>>1;
	}
	else if(sd->s_class.job == PC_JOB_SUM && sd->aspd < battle_config.sum_max_aspd) {
		sd->aspd = battle_config.sum_max_aspd;
		sd->amotion = sd->aspd>>1;
	}
	else if(!pc_is3rdclass(sd) && sd->aspd < battle_config.max_aspd) {
		sd->aspd = battle_config.max_aspd;
		sd->amotion = sd->aspd>>1;
	}

	if(battle_config.min_lv100_aspdfix && sd->status.base_level < 100 && sd->aspd < battle_config.max_aspd) {
		sd->aspd = battle_config.max_aspd;
		sd->amotion = sd->aspd>>1;
	}

	if(map[sd->bl.m].flag.pk) {
		if(sd->aspd < battle_config.pk_max_aspd) {
			sd->aspd = battle_config.pk_max_aspd;
			sd->amotion = sd->aspd>>1;
		}
	}
	if(map[sd->bl.m].flag.gvg) {
		if(sd->aspd < battle_config.gvg_max_aspd) {
			sd->aspd = battle_config.gvg_max_aspd;
			sd->amotion = sd->aspd>>1;
		}
	}
	if(map[sd->bl.m].flag.pvp) {
		if(sd->aspd < battle_config.pvp_max_aspd) {
			sd->aspd = battle_config.pvp_max_aspd;
			sd->amotion = sd->aspd>>1;
		}
	}
	sd->dmotion = 800-sd->paramc[1]*4;
	if(sd->dmotion < 400)
		sd->dmotion = 400;

	// MATK最低値保障
#ifdef PRE_RENEWAL
	if(sd->matk1 < 1)
	 	sd->matk1 = 1;
#else
	if(sd->matk1 < 1)
	 	sd->matk1 = 0;
#endif
	if(sd->matk2 < 1)
		sd->matk2 = 1;

	if(sd->status.max_hp > battle_config.max_hp)
		sd->status.max_hp = battle_config.max_hp;
	if(sd->status.max_sp > battle_config.max_sp)
		sd->status.max_sp = battle_config.max_sp;

	if(sd->status.max_hp <= 0)
		sd->status.max_hp = 1;
	if(sd->status.max_sp <= 0)
		sd->status.max_sp = 1;
	if(sd->status.max_ap <= 0)
		sd->status.max_ap = 0;

	if(sd->status.hp > sd->status.max_hp)
		sd->status.hp = sd->status.max_hp;
	if(sd->status.sp > sd->status.max_sp)
		sd->status.sp = sd->status.max_sp;
	if(sd->status.ap > sd->status.max_ap)
		sd->status.ap = sd->status.max_ap;

	// bTigereyeがなくなっていたらパケット送って元に戻す
	if(w->b_tigereye == 1 && sd->special_state.infinite_tigereye == 0 && sd->sc.data[SC_TIGEREYE].timer == -1)
		clif_status_load_id(sd,SI_TIGEREYE,0);

	// bInfiniteEndureがなくなっていたらパケットを送って元に戻す
	if(w->b_endure == 1 && sd->special_state.infinite_endure == 0)
		clif_status_load_id(sd,SI_ENDURE,0);
	// bSpeedRateがなくなっていたらパケットを送って元に戻す
	if(w->b_speedrate != 0 && sd->speed_rate == 0)
		clif_status_load_id(sd,SI_MOVHASTE_INFINITY,0);
	else if(w->b_speedrate < sd->speed_rate)
		clif_status_load_id(sd,SI_MOVHASTE_INFINITY,1);
}

int status_calc_pc(struct map_session_data* sd,int first)
{
	// Note: snapshot locals only here; recalc body is in phase helpers (Issue #57 PR1).
	int b_speed,b_max_hp,b_max_sp,b_hp,b_sp,b_weight,b_max_weight,b_paramb[12],b_paramc[12],b_hit,b_flee;
	int b_aspd,b_watk,b_def,b_watk2,b_def2,b_flee2,b_critical,b_attackrange,b_matk1,b_matk2,b_mdef,b_mdef2,b_class;
	int b_base_atk;
	int b_watk_,b_watk_2;
	int b_tigereye, b_endure, b_speedrate;
	int b_max_ap,b_ap,b_patk,b_smatk,b_res,b_mres,b_hplus,b_crate;
	struct skill b_skill[MAX_PCSKILL];
	int i;
	struct status_calc_pc_work w;
#ifndef PRE_RENEWAL
	int b_plus_atk,b_plus_matk;
#endif

	nullpo_retr(0, sd);

	/* L_RECALC contract (Issue #57):
	 * - stop_status_calc_pc > 0: defer (call_while_stopping++)
	 * - nested status_calc_pc while process!=0: return; finish path will recalc
	 * - snapshot b_* is taken once before the recalc loop
	 * - calclimit starts at 2 (first pass runs use-script)
	 */
	{
		int ctrl = status_calc_pc_ctrl_begin(
			&sd->stop_status_calc_pc,
			&sd->call_status_calc_pc_while_stopping,
			&sd->status_calc_pc_process);
		if(ctrl != STATUS_CALC_PC_CTRL_RUN)
			return 0;
	}

	// 以前の状態の保存
	b_speed      = sd->speed;
	b_max_hp     = sd->status.max_hp;
	b_max_sp     = sd->status.max_sp;
	b_max_ap     = sd->status.max_ap;
	b_hp         = sd->status.hp;
	b_sp         = sd->status.sp;
	b_ap         = sd->status.ap;
	b_weight     = sd->weight;
	b_max_weight = sd->max_weight;
	memcpy(b_paramb, &sd->paramb, sizeof(b_paramb));
	memcpy(b_paramc, &sd->paramc, sizeof(b_paramc));
	memcpy(b_skill, &sd->status.skill, sizeof(b_skill));
	b_hit         = sd->hit;
	b_flee        = sd->flee;
	b_aspd        = sd->aspd;
	b_watk        = sd->watk;
	b_def         = sd->def;
	b_watk2       = sd->watk2;
	b_def2        = sd->def2;
	b_flee2       = sd->flee2;
	b_critical    = sd->critical;
	b_attackrange = sd->range.attackrange;
	b_matk1       = sd->matk1;
	b_matk2       = sd->matk2;
	b_mdef        = sd->mdef;
	b_mdef2       = sd->mdef2;
	b_class       = sd->view_class;
	b_base_atk    = sd->base_atk;
	b_tigereye    = sd->special_state.infinite_tigereye;
	b_endure      = sd->special_state.infinite_endure;
	b_speedrate   = sd->speed_rate;
	b_watk_       = sd->watk_;
	b_watk_2      = sd->watk_2;
	b_patk        = sd->patk;
	b_smatk       = sd->smatk;
	b_res         = sd->res;
	b_mres        = sd->mres;
	b_hplus       = sd->hplus;
	b_crate       = sd->crate;
#ifndef PRE_RENEWAL
	b_plus_atk    = sd->plus_atk;
	b_plus_matk   = sd->plus_matk;
#endif

	memset(&w, 0, sizeof(w));
	w.first = first;
	w.calclimit = STATUS_CALC_PC_CALCLIMIT_INIT; // first pass includes use script
	w.b_tigereye = b_tigereye;
	w.b_endure = b_endure;
	w.b_speedrate = b_speedrate;
	w.b_class = b_class;
	do {
		/* phase: reset / clear / equip / job / sc_base / derived / sc_rest */
		status_calc_pc_phase_reset(sd, &w);
		status_calc_pc_phase_clear(sd);
		status_calc_pc_phase_equip(sd, &w);
		status_calc_pc_phase_job(sd, &w);
		status_calc_pc_phase_sc_base(sd, &w);
		status_calc_pc_phase_derived(sd, &w);
		status_calc_pc_phase_sc_rest(sd, &w);

		/* end of one calc body pass - may loop for L_RECALC */
		{
			int fin = status_calc_pc_ctrl_finish(&sd->status_calc_pc_process, &w.calclimit);
			if(fin > 0)
				continue; /* recalc */
			if(fin < 0)
				printf("status_calc_pc: infinity loop!\n");
			break;
		}
	} while(1);

	if(first&4)
		return 0;
	if(first&3) {
		clif_updatestatus(sd,SP_SPEED);
		clif_updatestatus(sd,SP_MAXHP);
		clif_updatestatus(sd,SP_MAXSP);
		clif_updatestatus(sd,SP_MAXAP);
		if(first&1) {
			clif_updatestatus(sd,SP_HP);
			clif_updatestatus(sd,SP_SP);
			clif_updatestatus(sd,SP_AP);
		}
		return 0;
	}

	if(w.b_class != sd->view_class) {
		clif_changelook(&sd->bl,LOOK_BASE,sd->view_class);
#if PACKETVER < 4
		clif_changelook(&sd->bl,LOOK_WEAPON,sd->status.weapon);
		clif_changelook(&sd->bl,LOOK_SHIELD,sd->status.shield);
#else
		clif_changelook(&sd->bl,LOOK_WEAPON,0);
#endif
	}

	if( memcmp(b_skill,sd->status.skill,sizeof(sd->status.skill)) || b_attackrange != sd->range.attackrange ) {
		int type;
		for(i=0; i<MAX_PCSKILL; i++) {
			// カードスキルをロストしたとき即時発動型なら状態異常を解除
			if(b_skill[i].flag == 1 && b_skill[i].lv > 0 && sd->status.skill[i].lv <= 0 && skill_get_inf(i) & INF_SELF) {
				type = GetSkillStatusChangeTable(i);
				if(type >= 0 && sd->sc.data[type].timer != -1)
					status_change_end(&sd->bl, type, -1);
			}
		}
		clif_skillinfoblock(sd);	// スキル送信
	}

	if(b_speed != sd->speed) {
		sd->ud.state.change_speed = 1;
		clif_updatestatus(sd,SP_SPEED);
	}
	if(b_weight != sd->weight)
		clif_updatestatus(sd,SP_WEIGHT);
	if(b_max_weight != sd->max_weight) {
		clif_updatestatus(sd,SP_MAXWEIGHT);
		pc_checkweighticon(sd);
	}

	for(i=0; i<12; i++) {
		if(b_paramb[i] + b_paramc[i] != sd->paramb[i] + sd->paramc[i]) {
			if(i < 6)
				clif_updatestatus(sd,SP_STR+i);
			else
				clif_updatestatus(sd,SP_POW+i-6);
		}
	}

	if(b_hit != sd->hit)
		clif_updatestatus(sd,SP_HIT);
	if(b_flee != sd->flee)
		clif_updatestatus(sd,SP_FLEE1);
	if(b_aspd != sd->aspd)
		clif_updatestatus(sd,SP_ASPD);
#ifdef PRE_RENEWAL
	if(b_watk != sd->watk || b_watk_ != sd->watk_ || b_base_atk != sd->base_atk)
		clif_updatestatus(sd,SP_ATK1);
	if(b_def != sd->def)
		clif_updatestatus(sd,SP_DEF1);
	if(b_watk2 != sd->watk2 || b_watk_2 != sd->watk_2)
		clif_updatestatus(sd,SP_ATK2);
	if(b_def2 != sd->def2)
		clif_updatestatus(sd,SP_DEF2);
#else
	if(b_base_atk != sd->base_atk)
		clif_updatestatus(sd,SP_ATK1);
	if(b_def2 != sd->def2)
		clif_updatestatus(sd,SP_DEF1);
	if(b_watk != sd->watk || b_watk_ != sd->watk_ || b_watk2 != sd->watk2 || b_watk_2 != sd->watk_2 || b_plus_atk != sd->plus_atk)
		clif_updatestatus(sd,SP_ATK2);
	if(b_def != sd->def)
		clif_updatestatus(sd,SP_DEF2);
#endif
	if(b_flee2 != sd->flee2)
		clif_updatestatus(sd,SP_FLEE2);
	if(b_critical != sd->critical)
		clif_updatestatus(sd,SP_CRITICAL);
#ifdef PRE_RENEWAL
	if(b_matk1 != sd->matk1)
		clif_updatestatus(sd,SP_MATK1);
#else
	if(b_matk1 != sd->matk1 || b_plus_matk != sd->plus_matk)
		clif_updatestatus(sd,SP_MATK1);
#endif
	if(b_matk2 != sd->matk2)
		clif_updatestatus(sd,SP_MATK2);
#ifdef PRE_RENEWAL
	if(b_mdef != sd->mdef)
		clif_updatestatus(sd,SP_MDEF1);
	if(b_mdef2 != sd->mdef2)
		clif_updatestatus(sd,SP_MDEF2);
#else
	if(b_mdef2 != sd->mdef2)
		clif_updatestatus(sd,SP_MDEF1);
	if(b_mdef != sd->mdef)
		clif_updatestatus(sd,SP_MDEF2);
#endif
	if(b_patk != sd->patk)
		clif_updatestatus(sd,SP_PATK);
	if(b_smatk != sd->smatk)
		clif_updatestatus(sd,SP_SMATK);
	if(b_res != sd->res)
		clif_updatestatus(sd,SP_RES);
	if(b_mres != sd->mres)
		clif_updatestatus(sd,SP_MRES);
	if(b_hplus != sd->hplus)
		clif_updatestatus(sd,SP_HPLUS);
	if(b_crate != sd->crate)
		clif_updatestatus(sd,SP_CRATE);
	if(b_attackrange != sd->range.attackrange)
		clif_updatestatus(sd,SP_ATTACKRANGE);
	if(b_max_hp != sd->status.max_hp)
		clif_updatestatus(sd,SP_MAXHP);
	if(b_max_sp != sd->status.max_sp)
		clif_updatestatus(sd,SP_MAXSP);
	if(b_hp != sd->status.hp)
		clif_updatestatus(sd,SP_HP);
	if(b_sp != sd->status.sp)
		clif_updatestatus(sd,SP_SP);
	if(b_ap != sd->status.ap)
		clif_updatestatus(sd,SP_AP);
	/*
	if(before.cart_num != before.cart_num || before.cart_max_num != before.cart_max_num ||
		before.cart_weight != before.cart_weight || before.cart_max_weight != before.cart_max_weight )
		clif_updatestatus(sd,SP_CARTINFO);
	*/

	if( sd->sc.data[SC_AUTOBERSERK].timer != -1 &&
	    sd->status.hp < sd->status.max_hp>>2 &&
	    (sd->sc.data[SC_PROVOKE].timer == -1 || sd->sc.data[SC_PROVOKE].val2 == 0) &&
	    !unit_isdead(&sd->bl) )
	{
		// オートバーサーク発動
		status_change_start(&sd->bl,SC_PROVOKE,10,1,0,0,0,0);
	}

	return 0;
}

/*==========================================
 * PCのamotionを計算して返す
 * 戻りは整数で1以上
 *------------------------------------------
 */
static int status_calc_amotion_pc(struct map_session_data *sd)
{
	double base_amotion;
	double amotion   = 0;
	int ferver_bonus = 0;
	int comfort_bonus= 0;
	int haste_val1   = 0;
	int haste_val2   = 0;
	int slow_val     = 0;
	int bonus_rate   = 0;
	int bonus_add    = 0;
	int skilllv;
	int tmp;
	char berserk_flag  = 0;
	int heatbarrel   = 0;
#ifndef PRE_RENEWAL
	double base_penalty   = 100;
#endif

	nullpo_retr(0, sd);

	/* ASPD固定ボーナス */
	if(sd->fix_status.aspd) {
		int fix_aspd = 2000 - sd->fix_status.aspd*10;
		return (fix_aspd < 100)? 100:fix_aspd;
	}

#ifdef PRE_RENEWAL
	/* 基本ASPDの計算 */
	if(sd->status.weapon < WT_MAX)	// 片手の場合は値をそのまま取得
		base_amotion = job_db[sd->s_class.job].aspd_base[sd->status.weapon];
	else	// 2刀の場合は2刀用の計算を行う
		base_amotion = (job_db[sd->s_class.job].aspd_base[sd->weapontype1] + job_db[sd->s_class.job].aspd_base[sd->weapontype2]) * 140 / 200;

	/* 基本ASPDに各パラメータのボーナスを適用 */
	if(pc_isriding(sd))	// 騎兵修練
		base_amotion = base_amotion - 1000 * (50+10*pc_checkskill(sd,KN_CAVALIERMASTERY)) / 100 - (base_amotion * sd->paramc[4] / 1000) - (base_amotion * sd->paramc[1] / 250) + 1000;
	else if(pc_isdragon(sd))	// ドラゴントレーニング
		base_amotion = base_amotion - 1000 * (75+5*pc_checkskill(sd,RK_DRAGONTRAINING)) / 100 - (base_amotion * sd->paramc[4] / 1000) - (base_amotion * sd->paramc[1] / 250) + 1000;
	else	// 騎乗していない
		base_amotion = base_amotion - (base_amotion * sd->paramc[4] / 1000) - (base_amotion * sd->paramc[1] / 250);
#else
	/* 基本ASPDの計算 */
	if(sd->status.weapon < WT_MAX) {	// 片手の場合は値をそのまま取得
		base_amotion = (2000 - job_db[sd->s_class.job].aspd_base[sd->status.weapon]) / 10;
		if(base_amotion > 144)
			base_penalty = (100-(base_amotion-144)*2);
		else
			base_penalty = 100;
	} else {	// 2刀の場合は2刀用の計算を行う
		base_amotion = (2000 - job_db[sd->s_class.job].aspd_base[sd->weapontype1]) / 10;
		base_amotion = base_amotion + (((2000 - job_db[sd->s_class.job].aspd_base[sd->weapontype2]) / 10) - 194) / 4;
	}

	/* 基本ASPDに各パラメータのボーナスを適用 */
	if(sd->status.weapon < WT_MAX){
		if( sd->status.weapon == WT_BOW ||
		    sd->status.weapon == WT_MUSICAL ||
		    sd->status.weapon == WT_WHIP ||
		    (sd->status.weapon >= WT_HANDGUN && sd->status.weapon <= WT_GRENADE) )
			base_amotion = (int)(200-(200-(base_amotion + sqrt(sd->paramc[1]*(10-1/(float)400) + sd->paramc[4]*9/(float)49) * base_penalty/100)));
		else
			base_amotion = (int)(200-(200-(base_amotion + sqrt(sd->paramc[1]*(10+10/(float)111) + sd->paramc[4]*9/(float)49) * base_penalty/100)));
	} else {
		base_amotion = (int)(200-(200-(base_amotion + sqrt(sd->paramc[1]*(10-1/(float)400) + sd->paramc[4]*9/(float)49)*1.05)));
	}
	base_amotion = (2000-base_amotion*10);
#endif

	/* 盾ペナルティの加算 */
	if(sd->equip_index[EQUIP_INDEX_LARM] >= 0 && sd->inventory_data[sd->equip_index[EQUIP_INDEX_LARM]] && itemdb_isarmor(sd->inventory_data[sd->equip_index[EQUIP_INDEX_LARM]]->nameid) && job_db[sd->s_class.job].aspd_base[WT_MAX] != 0)
		base_amotion += job_db[sd->s_class.job].aspd_base[WT_MAX];

	if(sd->sc.count > 0) {
		// ヒートバレル
		if(sd->sc.data[SC_HEAT_BARREL].timer != -1)
			heatbarrel -= sd->sc.data[SC_HEAT_BARREL].val1 * 10;
	}

#ifdef PRE_RENEWAL
	/* ボーナスADD_ASPDの計算 */
	amotion = base_amotion + sd->aspd_add + heatbarrel;
#else
	amotion = base_amotion;
#endif

	/* amotionが変化する状態異常の計算 */
	if(sd->sc.count > 0) {
		/* amotionが増加するステータスの計算 */

		// 私を忘れないで
		if(sd->sc.data[SC_DONTFORGETME].timer != -1) {
			slow_val = sd->sc.data[SC_DONTFORGETME].val1;
		}

		// 金剛
		if(sd->sc.data[SC_STEELBODY].timer != -1) {
			if(slow_val < 25)
				slow_val = 25;
		}

		// ジョイントビート
		if(sd->sc.data[SC_JOINTBEAT].timer != -1) {
			switch (sd->sc.data[SC_JOINTBEAT].val4) {
				case 1:		// 手首
					if(slow_val < 25)
						slow_val = 25;
					break;
				case 2:		// 膝
					if(slow_val < 10)
						slow_val = 10;
					break;
			}
		}

		// グラビテーションフィールド
		if(sd->sc.data[SC_GRAVITATION].timer != -1) {
			int penalty = sd->sc.data[SC_GRAVITATION].val1*5;
			if(slow_val < penalty)
				slow_val = penalty;
		}

		// 私を縛らないで
		if(sd->sc.data[SC_DANCING].timer != -1 && sd->sc.data[SC_BARDDANCER].timer == -1) {
			if(sd->sc.data[SC_LONGINGFREEDOM].timer != -1) {
				if(sd->sc.data[SC_LONGINGFREEDOM].val1 < 5) {
					int penalty = 50 - 10 * sd->sc.data[SC_LONGINGFREEDOM].val1;
					if(slow_val < penalty)
						slow_val = penalty;
				}
			}
		}

		// ハルシネーションウォーク(ペナルティ)
		if(sd->sc.data[SC_HALLUCINATIONWALK_POSTDELAY].timer != -1) {
			if(slow_val < 50)
				slow_val = 50;
		}

		// パラライズ
		if(sd->sc.data[SC_PARALIZE].timer != -1) {
			if(slow_val < 10)
				slow_val = 10;
		}

		// フロストミスティ
		if(sd->sc.data[SC_FROSTMISTY].timer != -1) {
			if(slow_val < 15)
				slow_val = 15;
		}

		// ボディペインティング
		if(sd->sc.data[SC__BODYPAINT].timer != -1) {
			if(slow_val < 25)
				slow_val = 25;
		}

		// インビジビリティ
		if(sd->sc.data[SC__INVISIBILITY].timer != -1) {
			int penalty = 50 - 10 * sd->sc.data[SC__INVISIBILITY].val1;
			if(slow_val < penalty)
				slow_val = penalty;
		}

		// マスカレード：グルーミー
		if(sd->sc.data[SC__GROOMY].timer != -1) {
			int penalty = 20 + 10 * sd->sc.data[SC__GROOMY].val1;
			if(slow_val < penalty)
				slow_val = penalty;
		}

		// アースドライブ
		if(sd->sc.data[SC_EARTHDRIVE].timer != -1) {
			if(slow_val < 25)
				slow_val = 25;
		}

		// メランコリー
		if(sd->sc.data[SC_GLOOMYDAY].timer != -1) {
			int penalty = 15 + 5 * sd->sc.data[SC_GLOOMYDAY].val1;
			if(slow_val < penalty)
				slow_val = penalty;
		}

		// メロン爆弾
		if(sd->sc.data[SC_MELON_BOMB].timer != -1) {
			int penalty = sd->sc.data[SC_MELON_BOMB].val1;
			if(slow_val < penalty)
				slow_val = penalty;
		}

		// ペインキラー
		if(sd->sc.data[SC_PAIN_KILLER].timer != -1) {
			int penalty = sd->sc.data[SC_PAIN_KILLER].val1 * 10;
			if(slow_val < penalty)
				slow_val = penalty;
		}

		/* amotionが減少するステータスの計算1 */

		// 増速ポーション
		if(sd->sc.data[tmp = SC_SPEEDPOTION2].timer != -1 || sd->sc.data[tmp = SC_SPEEDPOTION1].timer != -1 || sd->sc.data[tmp = SC_SPEEDPOTION0].timer != -1)
			haste_val1 = sd->sc.data[tmp].val2;

		// 濃縮サラマインジュース
		if(sd->sc.data[SC_EXTRACT_SALAMINE_JUICE].timer != -1)
			haste_val1 += sd->sc.data[SC_EXTRACT_SALAMINE_JUICE].val1;

		/* amotionが減少するステータスの計算2 */

		// ツーハンドクィッケン
		if(sd->sc.data[SC_TWOHANDQUICKEN].timer != -1)
			haste_val2 = sd->sc.data[SC_TWOHANDQUICKEN].val2;

		// スピアクィッケン
		if(sd->sc.data[SC_SPEARQUICKEN].timer != -1) {
			if(haste_val2 < sd->sc.data[SC_SPEARQUICKEN].val2)
				haste_val2 = sd->sc.data[SC_SPEARQUICKEN].val2;
		}

		// ワンハンドクィッケン
		if(sd->sc.data[SC_ONEHAND].timer != -1) {
			if(haste_val2 < 30)
				haste_val2 = 30;
		}

		// アドレナリンラッシュ
		if(sd->sc.data[SC_ADRENALINE].timer != -1) {
			int bonus;
			if(sd->sc.data[SC_ADRENALINE].val2 || !battle_config.party_skill_penalty)
				bonus = 30;
			else
				bonus = 25;
			if(haste_val2 < bonus)
				haste_val2 = bonus;
		}

		// アドレナリンラッシュ2
		if(sd->sc.data[SC_ADRENALINE2].timer != -1) {
			int bonus;
			if(sd->sc.data[SC_ADRENALINE2].val2 || !battle_config.party_skill_penalty)
				bonus = 30;
			else
				bonus = 25;
			if(haste_val2 < bonus)
				haste_val2 = bonus;
		}

		// 夕陽のアサシンクロス
		if(sd->sc.data[SC_ASSNCROS].timer != -1) {
			int bonus = sd->sc.data[SC_ASSNCROS].val2;
			if(haste_val2 < bonus)
				haste_val2 = bonus;
		}
		else if(sd->sc.data[SC_ASSNCROS_].timer != -1) {
			int bonus = sd->sc.data[SC_ASSNCROS_].val2;
			if(haste_val2 < bonus)
				haste_val2 = bonus;
		}

		// 星の安楽
		if(sd->sc.data[SC_STAR_COMFORT].timer != -1) {
			comfort_bonus = (sd->status.base_level + sd->status.dex + sd->status.luk)/10;
			if(haste_val2 < comfort_bonus)
				haste_val2 = comfort_bonus;
		}

		// ガトリングフィーバー
		if(sd->sc.data[SC_GATLINGFEVER].timer != -1) {
#ifdef PRE_RENEWAL
			ferver_bonus = sd->sc.data[SC_GATLINGFEVER].val1*2;
#else
			ferver_bonus = sd->sc.data[SC_GATLINGFEVER].val1;
#endif
			if(haste_val2 < ferver_bonus)
				haste_val2 = ferver_bonus;
		}

		// マッドネスキャンセラー
		if(sd->sc.data[SC_MADNESSCANCEL].timer != -1) {
			int bonus = 20+ferver_bonus;
			if(haste_val2 < bonus)
				haste_val2 = bonus;
		}

		// 点穴 -反-
		if(sd->sc.data[SC_GENTLETOUCH_CHANGE].timer != -1) {
			int bonus = sd->sc.data[SC_GENTLETOUCH_CHANGE].val4;
			if(haste_val2 < bonus)
				haste_val2 = bonus;
		}

		// スイングダンス
		if(sd->sc.data[SC_SWING].timer != -1) {
			int bonus = sd->sc.data[SC_SWING].val4;
			if(haste_val2 < bonus)
				haste_val2 = bonus;
		}

		// ダンスウィズウォーグ
		if(sd->sc.data[SC_DANCE_WITH_WUG].timer != -1) {
			int bonus = 2 + sd->sc.data[SC_DANCE_WITH_WUG].val4;
			if(haste_val2 < bonus)
				haste_val2 = bonus;
		}
		// 星の構え
		if(sd->sc.data[SC_STARSTANCE].timer != -1)
			haste_val1 += sd->sc.data[SC_STARSTANCE].val2;

		/* その他 */

		// バーサーク
#ifdef PRE_RENEWAL
		if(sd->sc.data[SC_BERSERK].timer != -1)
			berserk_flag = 1;
#else
		if(sd->sc.data[SC_BERSERK].timer != -1 && sd->sc.data[SC_TWOHANDQUICKEN].timer == -1)
			berserk_flag = 1;
#endif

		// ディフェンダー
		if(sd->sc.data[SC_DEFENDER].timer != -1)
			bonus_add += sd->sc.data[SC_DEFENDER].val3;

		// ファイティングスピリット
		if(sd->sc.data[SC_FIGHTINGSPIRIT].timer != -1)
			bonus_add -= sd->sc.data[SC_FIGHTINGSPIRIT].val3;

		// ガスト
		if(sd->sc.data[SC_GUST].timer != -1)
			bonus_add -= sd->sc.data[SC_GUST].val2;

		// ブラスト
		if(sd->sc.data[SC_BLAST].timer != -1)
			bonus_add -= sd->sc.data[SC_BLAST].val2;

		// ワイルドストーム
		if(sd->sc.data[SC_WILD_STORM].timer != -1)
			bonus_add -= sd->sc.data[SC_WILD_STORM].val2;

		// モンスター変身デビルチ
		if(sd->sc.data[SC_MONSTER_TRANSFORM].timer != -1 && sd->sc.data[SC_MONSTER_TRANSFORM].val1 == 1109)
			bonus_add -= -10;

		// 影の魂
		if(sd->sc.data[SC_SOULSHADOW].timer != -1)
			bonus_add -= sd->sc.data[SC_SOULSHADOW].val3;

		// 忠実な信念
		if(sd->sc.data[SC_SINCERE_FAITH].timer != -1)
			bonus_add -= sd->sc.data[SC_SINCERE_FAITH].val2;

		// 静寂
		if(sd->sc.data[SC_HANDICAPSTATE_DEEPSILENCE].timer != -1)
			bonus_add += sd->sc.data[SC_HANDICAPSTATE_DEEPSILENCE].val2;
	}

	/* 太陽と月と星の悪魔 */
	if((skilllv = pc_checkskill(sd,SG_DEVIL)) > 0 && sd->status.job_level >= 50) {
		int bonus = skilllv*3 + comfort_bonus;
		if(haste_val2 < bonus)
			haste_val2 = bonus;
	}

	/* slow_valとhaste_val1とhaste_val2を加算する */
	bonus_rate = slow_val - haste_val1 - haste_val2;

#ifdef PRE_RENEWAL
	/* bonus_rateにアイテムのボーナスを加算する */
	if(sd->aspd_add_rate != 0 || sd->aspd_rate != 0) {
		sd->aspd_rate += sd->aspd_add_rate;
		bonus_rate -= sd->aspd_rate;
	}
#endif

	/* バーサーク */
	if(berserk_flag)
		bonus_rate -= 30;

	/* フリーキャスト */
	if(sd->ud.skilltimer != -1 && (skilllv = pc_checkskill(sd,SA_FREECAST)) > 0)
		bonus_rate += 5 * (10 - skilllv);

	/* bonus_rateの計算 */
	if(bonus_rate != 0)
		amotion = amotion * (bonus_rate+100) / 100;

	/* アドバンスドブック */
	if(sd->weapontype1 == WT_BOOK && (skilllv = pc_checkskill(sd,SA_ADVANCEDBOOK)) > 0)
		amotion -= amotion * (skilllv+1) / 2 / 100;

	/* シングルアクション */
	if(sd->status.weapon >= WT_HANDGUN && sd->status.weapon <= WT_GRENADE && (skilllv = pc_checkskill(sd,GS_SINGLEACTION)) > 0)
		amotion -= amotion * (skilllv+1) / 2 / 100;

	/* bonus_addの加算 */
	if(bonus_add != 0)
		amotion += bonus_add;

#ifndef PRE_RENEWAL
	if(pc_isriding(sd))	// 騎兵修練
		amotion = amotion * (150-10*pc_checkskill(sd,KN_CAVALIERMASTERY)) / 100;
	else if(pc_isdragon(sd))	// ドラゴントレーニング
		amotion = amotion * (125-5*pc_checkskill(sd,RK_DRAGONTRAINING)) / 100;

	/* アイテムのボーナスを加算する */
	if(sd->aspd_add_rate != 0 || sd->aspd_rate != 0) {
		sd->aspd_rate += sd->aspd_add_rate;
		amotion = amotion * (100-sd->aspd_rate) / 100;
	}

	/* ボーナスADD_ASPDの計算 */
	amotion += sd->aspd_add + heatbarrel;
#endif

	/* 小数切り上げ */
	amotion = ceil(amotion);

	return (amotion < 1)? 1:(int)amotion;
}

/*==========================================
 * PCのspeedを計算して返す
 * 戻りは整数で1以上
 *------------------------------------------
 */
static int status_calc_speed_pc(struct map_session_data *sd, int speed)
{
	int bonus_rate;
	int speed_rate;
	int haste_val1 = 0;
	int haste_val2 = 0;
	int slow_val   = 0;
	int skilllv    = 0;
	char defender_flag = 0;
	char walkspeed_flag = 0;

	nullpo_retr(0, sd);

	if(sd->fix_status.speed > MIN_WALK_SPEED && sd->fix_status.speed <= MAX_WALK_SPEED)	// SPEED固定
		return sd->fix_status.speed;
	if(sd->ud.skilltimer != -1 && pc_checkskill(sd,SA_FREECAST) > 0)	// フリーキャスト状態なら移動速度固定
		return sd->speed * (175 - 5 * pc_checkskill(sd,SA_FREECAST)) / 100;
	if(sd->sc.data[SC_STEELBODY].timer != -1)	// 金剛は移動速度固定
		return 200;
	if(sd->ud.skilltimer != -1 && sd->ud.skillid == LG_EXEEDBREAK)		// イクシードブレイクの詠唱中
		return (150 - 10 * sd->ud.skilllv);
	if(sd->sc.data[SC_FULL_THROTTLE].timer != -1)		// フルスロットル中
		return 50;

	/* speedが変化するステータスの計算 */
	if(sd->sc.count > 0) {
		/* speedが増加するステータスの計算 */

		// トンネルドライブ
		if(sd->sc.data[SC_HIDING].timer != -1 && pc_checkskill(sd,RG_TUNNELDRIVE) > 0) {
			slow_val = 120 - 6 * pc_checkskill(sd,RG_TUNNELDRIVE);
		// チェイスウォーク(魂状態)
		} else if(sd->sc.data[SC_CHASEWALK].timer != -1 && sd->sc.data[SC_ROGUE].timer != -1) {
			slow_val = -40;
		} else {
			// 速度減少
			if(sd->sc.data[SC_DECREASEAGI].timer != -1)
				slow_val = 25;

			// 私を縛らないで
			if(sd->sc.data[SC_LONGINGFREEDOM].timer != -1) {
				int penalty = 50 - 10 * sd->sc.data[SC_LONGINGFREEDOM].val1;
				if(slow_val < penalty)
					slow_val = penalty;
			// 踊り/演奏
			} else if(sd->sc.data[SC_DANCING].timer != -1) {
				int penalty = 500 - (40 + 10 * (sd->sc.data[SC_BARDDANCER].timer != -1)) * pc_checkskill(sd,((sd->sex == SEX_MALE)? BA_MUSICALLESSON: DC_DANCINGLESSON));
				if(slow_val < penalty)
					slow_val = penalty;
			}

			// クァグマイア
			if(sd->sc.data[SC_QUAGMIRE].timer != -1) {
				if(slow_val < 50)
					slow_val = 50;
			}

			// 私を忘れないで
			if(sd->sc.data[SC_DONTFORGETME].timer != -1) {
				if(slow_val < sd->sc.data[SC_DONTFORGETME].val2)
					slow_val = sd->sc.data[SC_DONTFORGETME].val2;
			}
			else if(sd->sc.data[SC_DONTFORGETME_].timer != -1) {
				if(slow_val < sd->sc.data[SC_DONTFORGETME_].val2)
					slow_val = sd->sc.data[SC_DONTFORGETME_].val2;
			}

			// 呪い
			if(sd->sc.data[SC_CURSE].timer != -1) {
				if(slow_val < 300)
					slow_val = 300;
			}

			// チェイスウォーク(通常)
			if(sd->sc.data[SC_CHASEWALK].timer != -1 && sd->sc.data[SC_ROGUE].timer == -1) {
				int penalty = 35 - 5 * sd->sc.data[SC_CHASEWALK].val1;
				if(slow_val < penalty)
					slow_val = penalty;
			}

			// マーシュオブアビス
			if(sd->sc.data[SC_MARSHOFABYSS].timer != -1) {
				if(slow_val < sd->sc.data[SC_MARSHOFABYSS].val2)
					slow_val = sd->sc.data[SC_MARSHOFABYSS].val2;
			}

			// ハルシネーションウォーク(ペナルティ)
			if(sd->sc.data[SC_HALLUCINATIONWALK_POSTDELAY].timer != -1) {
				if(slow_val < 100)
					slow_val = 100;
			}

			// カモフラージュ
			if(sd->sc.data[SC_CAMOUFLAGE].timer != -1 && sd->sc.data[SC_CAMOUFLAGE].val1 > 2) {
				int penalty = 25 * (5 - sd->sc.data[SC_CAMOUFLAGE].val1);
				if(slow_val < penalty)
					slow_val = penalty;
			}

			// ステルスフィールド(使用者)
			if(sd->sc.data[SC_STEALTHFIELD_MASTER].timer != -1) {
				if(slow_val < 20)
					slow_val = 20;
			}

			// グラビテーションフィールド
			if(battle_config.player_gravitation_type && sd->sc.data[SC_GRAVITATION].timer != -1) {
				int penalty = sd->sc.data[SC_GRAVITATION].val1 * 5;
				if(slow_val < penalty)
					slow_val = penalty;
			}

			// 結婚衣装
			if(sd->sc.data[SC_WEDDING].timer != -1) {
				if(slow_val < 100)
					slow_val = 100;
			}

			// ジョイントビート
			if(sd->sc.data[SC_JOINTBEAT].timer != -1) {
				int penalty = 0;
				switch (sd->sc.data[SC_JOINTBEAT].val4) {
				case 0:	// 足首
					penalty = 50;
					break;
				case 2:	// 膝
					penalty = 30;
					break;
				}
				if(slow_val < penalty)
					slow_val = penalty;
			}

			// クローキング(平地移動)
			if(sd->sc.data[SC_CLOAKING].timer != -1) {
				int i;
				int check = 1;
				for(i=0; i<8; i++) {
					if(map_getcell(sd->bl.m,sd->bl.x+dirx[i],sd->bl.y+diry[i],CELL_CHKNOPASS)) {
						check = 0;
						break;
					}
				}
				if(check) {
					int penalty = (sd->sc.data[SC_CLOAKING].val1 < 3)? 300:30 - 3 * sd->sc.data[SC_CLOAKING].val1;
					if(slow_val < penalty)
						slow_val = penalty;
				}
			}

			// 移動速度低下(アイテム)
			if(sd->sc.data[SC_SLOWPOTION].timer != -1) {
				if(slow_val < 100)
					slow_val = 100;
			}

			// ガトリングフィーバー
			if(sd->sc.data[SC_GATLINGFEVER].timer != -1) {
				if(slow_val < 100)
					slow_val = 100;
			}

			// 水遁
			if(sd->sc.data[SC_SUITON].timer != -1) {
				if(sd->sc.data[SC_SUITON].val4) {
					if(slow_val < 50)
						slow_val = 50;
				}
			}

			// フロストミスティ
			if(sd->sc.data[SC_FROSTMISTY].timer != -1) {
				if(slow_val < 50)
					slow_val = 50;
			}

			// マスカレード：レイジネス
			if(sd->sc.data[SC__LAZINESS].timer != -1) {
				if(slow_val < 10)
					slow_val = 10;
			}

			// マスカレード：グルーミー
			if(sd->sc.data[SC__GROOMY].timer != -1) {
				int penalty = 5 + 5 * sd->sc.data[SC__GROOMY].val1;
				if(slow_val < penalty)
					slow_val = penalty;
			}

			// メロン爆弾
			if(sd->sc.data[SC_MELON_BOMB].timer != -1) {
				int penalty = sd->sc.data[SC_MELON_BOMB].val1;
				if(slow_val < penalty)
					slow_val = penalty;
			}

			// バインドトラップ
			if(sd->sc.data[SC_B_TRAP].timer != -1) {
				int penalty = sd->sc.data[SC_B_TRAP].val3;
				if(slow_val < penalty)
					slow_val = penalty;
			}
			// 重力調節
			if(sd->sc.data[SC_CREATINGSTAR].timer != -1){
				if( slow_val < 10 ){
					slow_val = 10;
				}
			}

			// リバウンド
			if(sd->sc.data[SC_REBOUND].timer != -1) {
				if(slow_val < 25)
					slow_val = 25;
			}

			// シールドチェーンラッシュ
			if(sd->sc.data[SC_SHIELDCHAINRUSH].timer != -1) {
				int penalty = sd->sc.data[SC_SHIELDCHAINRUSH].val3;
				if(slow_val < penalty)
					slow_val = penalty;
			}

			// グラウンドグラビテーション
			if(sd->sc.data[SC_GROUNDGRAVITY].timer != -1) {
				int penalty = sd->sc.data[SC_GROUNDGRAVITY].val3;
				if(slow_val < penalty)
					slow_val = penalty;
			}
		}

		/* speedが減少するステータス計算1 */

		// スピードポーション
		if(sd->sc.data[SC_SPEEDUP1].timer != -1)
			haste_val1 = 50;

		// 速度増加
		if(sd->sc.data[SC_INCREASEAGI].timer != -1) {
			if(haste_val1 < 25)
				haste_val1 = 25;
		}

		// サポート魔法(移動速度増加)
		if(sd->sc.data[SC_SUPPORT_SPEED].timer != -1) {
			if(haste_val1 < 25)
				haste_val1 = 25;
		}

		// ウインドウォーク
		if(sd->sc.data[SC_WINDWALK].timer != -1) {
			int bonus = 2 * sd->sc.data[SC_WINDWALK].val1;
			if(haste_val1 < bonus)
				haste_val1 = bonus;
		}

		// カートブースト
		if(sd->sc.data[SC_CARTBOOST].timer != -1) {
			if(haste_val1 < 20)
				haste_val1 = 20;
		}

		// クローキング(壁沿い移動)
		if(sd->sc.data[SC_CLOAKING].timer != -1) {
			int i;
			int check = 1;
			for(i=0; i<8; i++) {
				if(map_getcell(sd->bl.m,sd->bl.x+dirx[i],sd->bl.y+diry[i],CELL_CHKNOPASS)) {
					check = 0;
					break;
				}
			}
			if(!check) {
				int bonus = (sd->sc.data[SC_CLOAKING].val1 >= 10)? 25 : 3 * sd->sc.data[SC_CLOAKING].val1 - 3;
				if(haste_val1 < bonus)
					haste_val1 = bonus;
			}
		}

		// クローキングエクシード
		if(sd->sc.data[SC_CLOAKINGEXCEED].timer != -1) {
			int bonus = sd->sc.data[SC_CLOAKINGEXCEED].val1 * 10;
			if(haste_val1 < bonus)
				haste_val1 = bonus;
		}

		// バーサーク
		if(sd->sc.data[SC_BERSERK].timer != -1) {
			if(haste_val1 < 25)
				haste_val1 = 25;
		}

		// タイリギ
		if(sd->sc.data[SC_RUN].timer != -1) {
			if(haste_val1 < 55)
				haste_val1 = 55;
		}

		// 緊急回避
		if(sd->sc.data[SC_AVOID].timer != -1) {
			int bonus = 10 * sd->sc.data[SC_AVOID].val1;
			if(haste_val1 < bonus)
				haste_val1 = bonus;
		}

		// ウルフダッシュ
		if(sd->sc.data[SC_WUGDASH].timer != -1) {
			if(haste_val2 < 50)
				haste_val2 = 50;
		}

		// アクセラレーション
		if(sd->sc.data[SC_ACCELERATION].timer != -1) {
			if(haste_val2 < 25)
				haste_val2 = 25;
		}

		// スイングダンス
		if(sd->sc.data[SC_SWING].timer != -1) {
			if(haste_val1 < 25)
				haste_val1 = 25;
		}

		// カートブースト
		if(sd->sc.data[SC_GN_CARTBOOST].timer != -1) {
			int bonus = 25 + ((sd->sc.data[SC_GN_CARTBOOST].val1 + 1) / 2) * 25;
			if(haste_val1 < bonus)
				haste_val1 = bonus;
		}

		// 移動速度増加(アイテム)
		if(sd->sc.data[SC_SPEEDUP0].timer != -1) {
			if(haste_val1 < 25)
				haste_val1 = 25;
		}

		// ウィンドステップ
		if(sd->sc.data[SC_WIND_STEP].timer != -1) {
			int bonus = sd->sc.data[SC_WIND_STEP].val3;
			if(haste_val1 < bonus)
				haste_val1 = bonus;
		}

		// チャタリング
		if(sd->sc.data[SC_CHATTERING].timer != -1) {
			int bonus = sd->sc.data[SC_CHATTERING].val3;
			if(haste_val1 < bonus)
				haste_val1 = bonus;
		}

		// アクラウスダッシュ
		if(sd->sc.data[SC_ARCLOUSEDASH].timer != -1) {
			if(haste_val1 < 25)
				haste_val1 = 25;
		}

		// 警戒
		if(sd->sc.data[SC_HISS].timer != -1 && sd->sc.data[SC_HISS].val4 > 0) {
			if(haste_val1 < sd->sc.data[SC_HISS].val3)
				haste_val1 = sd->sc.data[SC_HISS].val3;
		}

		// 夕焼けのセレナーデ
		if(sd->sc.data[SC_JAWAII_SERENADE].timer != -1) {
			int bonus = sd->sc.data[SC_JAWAII_SERENADE].val4;
			if(haste_val1 < bonus)
				haste_val1 = bonus;
		}

		// プロンテラマーチ
		if(sd->sc.data[SC_PRON_MARCH].timer != -1) {
			int bonus = sd->sc.data[SC_PRON_MARCH].val3;
			if(haste_val1 < bonus)
				haste_val1 = bonus;
		}

		// 影隠れ
		if(sd->sc.data[SC_SHADOW_CLOCK].timer != -1) {
			int bonus = sd->sc.data[SC_SHADOW_CLOCK].val3;
			if(haste_val1 < bonus)
				haste_val1 = bonus;
		}

		/* speedが減少するステータス計算2 */

		// 融合
		if(sd->sc.data[SC_FUSION].timer != -1)
			haste_val2 = 25;

		/* その他 */

		// ディフェンダー
		if(sd->sc.data[SC_DEFENDER].timer != -1)
			defender_flag = 1;

		// WALKSPEED
		if(sd->sc.data[SC_WALKSPEED].timer != -1 && sd->sc.data[SC_WALKSPEED].val1 > 0)
			walkspeed_flag = 1;
	}

	// 回避率増加
	if((sd->s_class.job == PC_JOB_AS || sd->s_class.job == PC_JOB_GC) && (skilllv = pc_checkskill(sd,TF_MISS)) > 0) {
		if(haste_val1 < skilllv)
			haste_val1 = skilllv;
	}

	// アイテムボーナス
	speed_rate = sd->speed_rate + sd->speed_add_rate;
	if(speed_rate != 0) {
		if(haste_val1 < speed_rate)
			haste_val1 = speed_rate;
	}

	/* 騎乗 */

	// ペコ
	if(pc_isriding(sd)) {
		if(haste_val2 < 25)
			haste_val2 = 25;
	}

	// ドラゴン
	if(pc_isdragon(sd)) {
		if(haste_val2 < 25)
			haste_val2 = 25;
	}

	// ウルフ
	if(pc_iswolfmount(sd)) {
		int bonus = 15 + 5 * pc_checkskill(sd,RA_WUGRIDER);
		if(haste_val2 < bonus)
			haste_val2 = bonus;
	}

	// 騎乗システム
	if(sd->sc.data[SC_ALL_RIDING].timer != -1) {
		if(haste_val2 < 25)
			haste_val2 = 25;
	}

	/* bonus_rateの最低値を設定 */
	bonus_rate = slow_val - haste_val1 - haste_val2;
	if(bonus_rate < -60)
		bonus_rate = -60;

	/* speedの最終計算 */
	if(pc_iscarton(sd))	// カート
		speed += speed * (50 - 5 * pc_checkskill(sd,MC_PUSHCART)) / 100;
	if(pc_isgear(sd))	// 魔導ギア搭乗
		speed += speed * (5 - pc_checkskill(sd,NC_MADOLICENCE)) / 10;
	if(bonus_rate != 0)	// bonus_rate
		speed = speed * (bonus_rate+100) / 100;
	if(defender_flag && speed < 200)	// ディフェンダー
		speed = 200;
	if(walkspeed_flag)	// スクリプト用ステータス
		speed = speed * 100 / sd->sc.data[SC_WALKSPEED].val1;

	/* 最低値、最大値を設定する */
	if(speed < MIN_WALK_SPEED)
		speed = MIN_WALK_SPEED;
	if(speed > MAX_WALK_SPEED)
		speed = MAX_WALK_SPEED;

	return speed;
}

