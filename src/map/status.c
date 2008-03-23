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
#include "pet.h"
#include "homun.h"
#include "mob.h"
#include "clif.h"
#include "skill.h"
#include "itemdb.h"
#include "battle.h"
#include "status.h"
#include "script.h"
#include "guild.h"
#include "unit.h"
#include "ranking.h"
#include "merc.h"

static struct job_db {
	int max_weight_base;
	int hp_base[MAX_LEVEL];
	int sp_base[MAX_LEVEL];
	int bonus[3][MAX_LEVEL];
	int aspd_base[WT_MAX];
} job_db[MAX_PC_CLASS];

static int atkmods[MAX_SIZE_FIX][WT_MAX];	// 武器ATKサイズ修正(size_fix.txt)

static struct refine_db {
	int safety_bonus;
	int over_bonus;
	int limit;
	int per[MAX_REFINE];
} refine_db[MAX_WEAPON_LEVEL+1];

int current_equip_item_index;	// ステータス計算用
int current_equip_card_id;
static char race_name[11][5] = {{"無形"},{"不死"},{"動物"},{"植物"},{"昆虫"},{""},{"魚貝"},{"悪魔"},{"人間"},{"天使"},{"竜"}};

#ifdef DYNAMIC_SC_DATA
struct status_change_data dummy_sc_data[MAX_STATUSCHANGE];
#endif

static struct scdata_db scdata_db[MAX_STATUSCHANGE];	// ステータス異常データベース

static int StatusIconChangeTable[MAX_STATUSCHANGE] = {
	/* 0- */
	SI_PROVOKE,SI_ENDURE,SI_TWOHANDQUICKEN,SI_CONCENTRATE,SI_BLANK,SI_CLOAKING,SI_ENCPOISON,SI_POISONREACT,SI_QUAGMIRE,SI_ANGELUS,
	/* 10- */
	SI_BLESSING,SI_SIGNUMCRUCIS,SI_INCREASEAGI,SI_DECREASEAGI,SI_SLOWPOISON,SI_IMPOSITIO,SI_SUFFRAGIUM,SI_ASPERSIO,SI_BENEDICTIO,SI_KYRIE,
	/* 20- */
	SI_MAGNIFICAT,SI_GLORIA,SI_AETERNA,SI_ADRENALINE,SI_WEAPONPERFECTION,SI_OVERTHRUST,SI_MAXIMIZEPOWER,SI_BLANK,SI_BLANK,SI_TRICKDEAD,
	/* 30- */
	SI_LOUD,SI_ENERGYCOAT,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_SPEEDPOTION0,SI_SPEEDPOTION1,SI_SPEEDPOTION2,
	/* 40- */
	SI_SPEEDPOTION3,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,
	/* 50- */
	SI_STRIPWEAPON,SI_STRIPSHIELD,SI_STRIPARMOR,SI_STRIPHELM,SI_CP_WEAPON,SI_CP_SHIELD,SI_CP_ARMOR,SI_CP_HELM,SI_AUTOGUARD,SI_REFLECTSHIELD,
	/* 60- */
	SI_DEVOTION,SI_PROVIDENCE,SI_DEFENDER,SI_BLANK,SI_BLANK,SI_AUTOSPELL,SI_BLANK,SI_BLANK,SI_SPEARQUICKEN,SI_BLANK,
	/* 70- */
	SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,
	/* 80- */
	SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_EXPLOSIONSPIRITS,SI_STEELBODY,SI_BLANK,SI_COMBO,
	/* 90- */
	SI_FLAMELAUNCHER,SI_FROSTWEAPON,SI_LIGHTNINGLOADER,SI_SEISMICWEAPON,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,
	/* 100- */
	SI_BLANK,SI_BLANK,SI_WE_FEMALE,SI_AURABLADE,SI_PARRYING,SI_CONCENTRATION,SI_TENSIONRELAX,SI_BERSERK,SI_BLANK,SI_BLANK,
	/* 110- */
	SI_ASSUMPTIO,SI_BLANK,SI_BLANK,SI_MAGICPOWER,SI_EDP,SI_TRUESIGHT,SI_WINDWALK,SI_MELTDOWN,SI_CARTBOOST,SI_CHASEWALK,
	/* 120- */
	SI_REJECTSWORD,SI_MARIONETTE,SI_MARIONETTE2,SI_BLANK,SI_HEADCRUSH,SI_JOINTBEAT,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,
	/* 130- */
	SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_HEADCRUSH,SI_BLANK,SI_BLANK,
	/* 140- */
	SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,
	/* 150- */
	SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,
	/* 160- */
	SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,
	/* 170- */
	SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,
	/* 180- */
	SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,
	/* 190- */
	SI_BLANK,SI_MAGNUM,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,
	/* 200- */
	SI_BLANK,SI_PRESERVE,SI_OVERTHRUSTMAX,SI_CHASEWALK_STR,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,
	/* 210- */
	SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,
	/* 220- */
	SI_TAROTCARD,SI_TAROTCARD,SI_TAROTCARD,SI_TAROTCARD,SI_MEAL_INCSTR,SI_MEAL_INCAGI,SI_MEAL_INCVIT,SI_MEAL_INCINT,SI_MEAL_INCDEX,SI_MEAL_INCLUK,
	/* 230- */
	SI_RUN,SI_SPURT,SI_BLANK,SI_DODGE,SI_BLANK,SI_BLANK,SI_BLANK,SI_WARM,SI_BLANK,SI_BLANK,
	/* 240- */
	SI_SUN_COMFORT,SI_MOON_COMFORT,SI_STAR_COMFORT,SI_BLANK,SI_SOULLINK,SI_SOULLINK,SI_SOULLINK,SI_SOULLINK,SI_SOULLINK,SI_SOULLINK,
	/* 250- */
	SI_SOULLINK,SI_SOULLINK,SI_SOULLINK,SI_SOULLINK,SI_SOULLINK,SI_SOULLINK,SI_SOULLINK,SI_SOULLINK,SI_SOULLINK,SI_SOULLINK,
	/* 260- */
	SI_SOULLINK,SI_SOULLINK,SI_SOULLINK,SI_SOULLINK,SI_KAIZEL,SI_KAAHI,SI_KAUPE,SI_KAITE,SI_SMA,SI_BLANK,
	/* 270- */
	SI_BLANK,SI_BLANK,SI_ONEHAND,SI_READYSTORM,SI_READYDOWN,SI_READYTURN,SI_READYCOUNTER,SI_BLANK,SI_AUTOBERSERK,SI_BLANK,
	/* 280- */
	SI_DOUBLECASTING,SI_ELEMENTFIELD,SI_DARKELEMENT,SI_ATTENELEMENT,SI_MIRACLE,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BABY,
	/* 290- */
	SI_BLANK,SI_SHRINK,SI_CLOSECONFINE,SI_SIGHTBLASTER,SI_BLANK,SI_MEAL_INCHIT,SI_MEAL_INCFLEE,SI_BLANK,SI_MEAL_INCCRITICAL,SI_BLANK,
	/* 300- */
	SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,
	/* 310- */
	SI_BLANK,SI_BLANK,SI_UNDEAD,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,
	/* 320- */
	SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,
	/* 330- */
	SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_TIGEREYE,SI_BLANK,SI_BLANK,
	/* 340- */
	SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_STOP,SI_BLANK,SI_BLANK,SI_BLANK,SI_MADNESSCANCEL,SI_ADJUSTMENT,
	/* 350- */
	SI_INCREASING,SI_BLANK,SI_GATLINGFEVER,SI_BLANK,SI_BLANK,SI_UTSUSEMI,SI_BUNSINJYUTSU,SI_BLANK,SI_NEN,SI_BLANK,
	/* 360- */
	SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_ADRENALINE2,SI_BLANK,SI_BLANK,SI_COMBATHAN,SI_LIFEINSURANCE,
	/* 370- */
	SI_ITEMDROPRATE,SI_BOSSMAPINFO,SI_MEAL_INCSTR2,SI_MEAL_INCAGI2,SI_MEAL_INCVIT2,SI_MEAL_INCDEX2,SI_MEAL_INCINT2,SI_MEAL_INCLUK2,SI_SLOWCAST,SI_CRITICALWOUND,
	/* 380- */
	SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_HAPPY,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,SI_BLANK,
};

/*==========================================
 * 過剰精錬ボーナス
 *------------------------------------------
 */
int status_get_overrefine_bonus(int lv)
{
	if(lv >= 0 && lv <= MAX_WEAPON_LEVEL)
		return refine_db[lv].over_bonus;
	return 0;
}

/*==========================================
 * 精錬成功率
 *------------------------------------------
 */
int status_percentrefinery(struct map_session_data *sd,struct item *item)
{
	int percent;

	nullpo_retr(0, item);

	if(item->refine < 0 || item->refine >= MAX_REFINE)	// 値がエラーもしくは既に最大値なら0%
		return 0;

	percent = refine_db[itemdb_wlv(item->nameid)].per[(int)item->refine];

	percent += pc_checkskill(sd,BS_WEAPONRESEARCH);	// 武器研究スキル所持

	// 確率の有効範囲チェック
	if(percent > 100) {
		percent = 100;
	}
	if(percent < 0) {
		percent = 0;
	}

	return percent;
}

/*==========================================
 * 精錬成功率 万分率
 *------------------------------------------
 */
int status_percentrefinery_weaponrefine(struct map_session_data *sd,struct item *item)
{
	int percent;
	int joblv;

	nullpo_retr(0, sd);
	nullpo_retr(0, item);

	if(item->refine < 0 || item->refine >= MAX_REFINE)	// 値がエラーもしくは既に最大値なら0%
		return 0;

	joblv = sd->status.job_level > 70? 70 : sd->status.job_level;
	percent = refine_db[itemdb_wlv(item->nameid)].per[(int)item->refine]*100 + (joblv - 50)*50;

	if(battle_config.allow_weaponrearch_to_weaponrefine)
		percent += pc_checkskill(sd,BS_WEAPONRESEARCH)*100;	// 武器研究スキル所持

	// 確率の有効範囲チェック
	if(percent > 10000) {
		percent = 10000;
	}
	if(percent < 0) {
		percent = 0;
	}

	return percent;
}

/*==========================================
 * セーブ可能なステータス異常かどうか
 *------------------------------------------
 */
int status_can_save(int type)
{
	if(type >= 0 && type < MAX_STATUSCHANGE) {
		if(scdata_db[type].save > 0)
			return 1;
	}
	return 0;
}

/*==========================================
 * diableなステータス異常かどうか
 *------------------------------------------
 */
int status_is_disable(int type,int mask)
{
	if(type >= 0 && type < MAX_STATUSCHANGE) {
		if(scdata_db[type].disable & mask)
			return 1;
	}
	return 0;
}

/*==========================================
 * パラメータ計算
 * first==0の時、計算対象のパラメータが呼び出し前から
 * 変化した場合自動でsendするが、
 * 能動的に変化させたパラメータは自前でsendするように
 *------------------------------------------
 */
int status_calc_pc(struct map_session_data* sd,int first)
{
	// 注意：ここでは変数の宣言のみにとどめ、初期化はL_RECALCの後にやること。
	int b_speed,b_max_hp,b_max_sp,b_hp,b_sp,b_weight,b_max_weight,b_paramb[6],b_parame[6],b_hit,b_flee;
	int b_aspd,b_watk,b_def,b_watk2,b_def2,b_flee2,b_critical,b_attackrange,b_matk1,b_matk2,b_mdef,b_mdef2,b_class;
	int b_base_atk;
	int b_tigereye;
	struct skill b_skill[MAX_SKILL];
	int i,blv,calc_val,idx;
	int skill,aspd_rate,wele,wele_,def_ele,refinedef;
	int pele,pdef_ele;
	int str,dstr,dex;
	int calclimit = 2; // 初回はuse script込みで実行

	nullpo_retr(0, sd);

	if(sd->stop_status_calc_pc)
	{
		sd->call_status_calc_pc_while_stopping++;
		return 0;
	}

	sd->call_status_calc_pc_while_stopping = 0;

	// status_calc_pc の処理中にstatus_calc_pcが呼び出されると最初に計算している
	// 値が狂う可能性がある。また、この関数が呼ばれるということは、キャラの状態が
	// 変化していることを暗示しているので、計算結果を捨てて再計算しなければいけない。
	// 関数の終了時点で呼び出しがあれば、L_RECALCに飛ばすようにする。
	if( sd->status_calc_pc_process++ ) return 0;

	// 以前の状態の保存
	b_speed      = sd->speed;
	b_max_hp     = sd->status.max_hp;
	b_max_sp     = sd->status.max_sp;
	b_hp         = sd->status.hp;
	b_sp         = sd->status.sp;
	b_weight     = sd->weight;
	b_max_weight = sd->max_weight;
	memcpy(b_paramb, &sd->paramb, sizeof(b_paramb));
	memcpy(b_parame, &sd->paramc, sizeof(b_parame));
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
	b_attackrange = sd->attackrange;
	b_matk1       = sd->matk1;
	b_matk2       = sd->matk2;
	b_mdef        = sd->mdef;
	b_mdef2       = sd->mdef2;
	b_class       = sd->view_class;
	b_base_atk    = sd->base_atk;
	b_tigereye    = sd->special_state.infinite_tigereye;

L_RECALC:
	// 本来の計算開始(元のパラメータを更新しないのは、計算中に計算処理が呼ばれたときの
	// 反映分も新たに送信するため)。

	pele      = 0;
	pdef_ele  = 0;
	refinedef = 0;
	sd->view_class = sd->status.class_;
	if(sd->view_class == PC_CLASS_GS || sd->view_class == PC_CLASS_NJ)
		sd->view_class -= 4;

	sd->race = RCT_HUMAN;
	sd->ranker_weapon_bonus  = 0;
	sd->ranker_weapon_bonus_ = 0;
	sd->special_state.infinite_tigereye = 0;

	pc_calc_skilltree(sd);	// スキルツリーの計算

	sd->max_weight = job_db[sd->s_class.job].max_weight_base+sd->status.str*300;

	if(battle_config.baby_weight_rate != 100 && pc_isbaby(sd))
		sd->max_weight = sd->max_weight*battle_config.baby_weight_rate/100;


	// ペコ騎乗時増えるよう移動
	if((skill = pc_checkskill(sd,MC_INCCARRY)) > 0)	// 所持量増加
		sd->max_weight += skill*2000;

	if((skill = pc_checkskill(sd,SG_KNOWLEDGE)) > 0)	// 太陽と月と星の知識
	{
		if(battle_config.check_knowlege_map) {	// 場所チェックを行なう
			if(sd->bl.m == sd->feel_index[0] || sd->bl.m == sd->feel_index[1] || sd->bl.m == sd->feel_index[2])
				sd->max_weight += sd->max_weight*skill/10;
		} else {
			sd->max_weight += sd->max_weight*skill/10;
		}
	}

	if(first&1) {
		sd->weight = 0;
		for(i=0; i<MAX_INVENTORY; i++) {
			if(sd->status.inventory[i].nameid == 0 || sd->inventory_data[i] == NULL)
				continue;
			sd->weight += sd->inventory_data[i]->weight*sd->status.inventory[i].amount;
		}
		sd->cart_max_weight = battle_config.max_cart_weight;
		sd->cart_weight     = 0;
		sd->cart_max_num    = MAX_CART;
		sd->cart_num        = 0;
		for(i=0; i<MAX_CART; i++) {
			if(sd->status.cart[i].nameid == 0)
				continue;
			sd->cart_weight += itemdb_weight(sd->status.cart[i].nameid)*sd->status.cart[i].amount;
			sd->cart_num++;
		}
	}

	memset(sd->paramb,0,sizeof(sd->paramb));
	memset(sd->parame,0,sizeof(sd->parame));
	sd->hit           = 0;
	sd->flee          = 0;
	sd->flee2         = 0;
	sd->critical      = 0;
	sd->aspd          = 0;
	sd->watk          = 0;
	sd->def           = 0;
	sd->mdef          = 0;
	sd->watk2         = 0;
	sd->def2          = 0;
	sd->mdef2         = 0;
	sd->status.max_hp = 0;
	sd->status.max_sp = 0;
	sd->attackrange   = 0;
	sd->attackrange_  = 0;
	sd->atk_ele       = 0;
	sd->def_ele       = 0;
	sd->star          = 0;
	sd->overrefine    = 0;
	sd->matk1         = 0;
	sd->matk2         = 0;
	sd->speed         = DEFAULT_WALK_SPEED;
	sd->hprate        = battle_config.hp_rate;
	sd->sprate        = battle_config.sp_rate;
	sd->castrate      = 100;
	sd->dsprate       = 100;
	sd->base_atk      = 0;
	sd->arrow_atk     = 0;
	sd->arrow_ele     = 0;
	sd->arrow_hit     = 0;
	sd->arrow_range   = 0;
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
	sd->atk_ele_    = 0;
	sd->star_       = 0;
	sd->overrefine_ = 0;

	sd->aspd_rate    = 100;
	sd->speed_rate   = 100;
	sd->hprecov_rate = 100;
	sd->sprecov_rate = 100;
	sd->critical_def = 0;
	sd->double_rate  = 0;
	sd->near_attack_def_rate = sd->long_attack_def_rate = 0;
	sd->atk_rate = sd->matk_rate = 100;
	sd->ignore_def_ele = sd->ignore_def_race = sd->ignore_def_enemy = 0;
	sd->ignore_def_ele_ = sd->ignore_def_race_ = sd->ignore_def_enemy_ = 0;
	sd->ignore_mdef_ele = sd->ignore_mdef_race = sd->ignore_mdef_enemy = 0;
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
	memset(sd->magic_subrace,0,sizeof(sd->magic_subrace));
	sd->perfect_hit = 0;
	sd->critical_rate = sd->hit_rate = sd->flee_rate = sd->flee2_rate = 100;
	sd->def_rate = sd->def2_rate = sd->mdef_rate = sd->mdef2_rate = 100;
	sd->def_ratio_atk_ele = sd->def_ratio_atk_race = sd->def_ratio_atk_enemy = 0;
	sd->def_ratio_atk_ele_ = sd->def_ratio_atk_race_ = sd->def_ratio_atk_enemy_ = 0;
	sd->get_zeny_num = sd->get_zeny_num2 = 0;
	sd->add_damage_class_count = sd->add_damage_class_count_ = sd->add_magic_damage_class_count = 0;
	sd->add_def_class_count = sd->add_mdef_class_count = 0;
	sd->monster_drop_item_count = 0;
	memset(sd->add_damage_classrate,0,sizeof(sd->add_damage_classrate));
	memset(sd->add_damage_classrate_,0,sizeof(sd->add_damage_classrate_));
	memset(sd->add_magic_damage_classrate,0,sizeof(sd->add_magic_damage_classrate));
	memset(sd->add_def_classrate,0,sizeof(sd->add_def_classrate));
	memset(sd->add_mdef_classrate,0,sizeof(sd->add_mdef_classrate));
	memset(sd->monster_drop_race,0,sizeof(sd->monster_drop_race));
	memset(sd->monster_drop_itemrate,0,sizeof(sd->monster_drop_itemrate));
	sd->sp_gain_value = 0;
	sd->hp_gain_value = 0;
	sd->speed_add_rate = sd->aspd_add_rate = 100;
	sd->double_add_rate = sd->perfect_hit_add = sd->get_zeny_add_num = sd->get_zeny_add_num2 = 0;
	sd->splash_range = sd->splash_add_range = 0;
	memset(&sd->hp_drain,0,sizeof(sd->hp_drain));
	memset(&sd->sp_drain,0,sizeof(sd->sp_drain));
	memset(&sd->hp_drain_,0,sizeof(sd->hp_drain_));
	memset(&sd->sp_drain_,0,sizeof(sd->sp_drain_));
	sd->short_weapon_damage_return = sd->long_weapon_damage_return = sd->magic_damage_return = 0;
	sd->break_weapon_rate = sd->break_armor_rate = 0;
	sd->add_steal_rate    = 0;
	sd->unbreakable_equip = 0;
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
	memset(&sd->skill_blow,0,sizeof(sd->skill_blow));
	memset(&sd->autospell,0,sizeof(sd->autospell));
	memset(&sd->itemheal_rate,0,sizeof(sd->itemheal_rate));
	memset(&sd->autoraise,0,sizeof(sd->autoraise));
	sd->hp_vanish_rate    = 0;
	sd->hp_vanish_per     = 0;
	sd->sp_vanish_rate    = 0;
	sd->sp_vanish_per     = 0;
	sd->bonus_damage      = 0;
	sd->curse_by_muramasa = 0;
	memset(sd->loss_equip_rate_when_die,0,sizeof(sd->loss_equip_rate_when_die));
	memset(sd->loss_equip_rate_when_attack,0,sizeof(sd->loss_equip_rate_when_attack));
	memset(sd->loss_equip_rate_when_hit,0,sizeof(sd->loss_equip_rate_when_hit));
	memset(sd->break_myequip_rate_when_attack,0,sizeof(sd->break_myequip_rate_when_attack));
	memset(sd->break_myequip_rate_when_hit,0,sizeof(sd->break_myequip_rate_when_hit));
	sd->loss_equip_flag = 0;
	sd->short_weapon_damege_rate = sd->long_weapon_damege_rate = 0;
	sd->add_attackrange = 0;
	sd->add_attackrange_rate = 100;
	sd->special_state.item_no_use = 0;
	sd->skill_delay_rate = 0;
	memset(&sd->fix_status,0,sizeof(sd->fix_status));
	memset(&sd->skill_fixcastrate,0,sizeof(sd->skill_fixcastrate));
	memset(&sd->skill_healup,0,sizeof(sd->skill_healup));

	for(i=0; i<10; i++) {
		idx = sd->equip_index[i];
		current_equip_item_index = i;	// 部位チェック用
		if(idx < 0)
			continue;
		if(i == 9 && sd->equip_index[8] == idx)
			continue;
		if(i == 5 && sd->equip_index[4] == idx)
			continue;
		if(i == 6 && (sd->equip_index[5] == idx || sd->equip_index[4] == idx))
			continue;

		if(sd->inventory_data[idx]) {
			if(sd->inventory_data[idx]->type == 4) {
				if( !itemdb_isspecial(sd->status.inventory[idx].card[0]) ) {
					int j;
					for(j=0; j<sd->inventory_data[idx]->slot; j++) {	// カード
						int c = sd->status.inventory[idx].card[j];
						current_equip_card_id = c;		// オートスペル(重複チェック用)
						if(c > 0) {
							if(i == 8 && sd->status.inventory[idx].equip == 0x20)
								sd->state.lr_flag = 1;
							if(calclimit == 2)
								run_script(itemdb_usescript(c),0,sd->bl.id,0);
							run_script(itemdb_equipscript(c),0,sd->bl.id,0);
							sd->state.lr_flag = 0;
						}
					}
				}
			}
			else if(sd->inventory_data[idx]->type == 5) { // 防具
				if( !itemdb_isspecial(sd->status.inventory[idx].card[0]) ) {
					int j;
					for(j=0; j<sd->inventory_data[idx]->slot; j++) {	// カード
						int c = sd->status.inventory[idx].card[j];
						current_equip_card_id = c;		// オートスペル(重複チェック用)
						if(c > 0) {
							if(calclimit == 2)
								run_script(itemdb_usescript(c),0,sd->bl.id,0);
							run_script(itemdb_equipscript(c),0,sd->bl.id,0);
						}
					}
				}
			}
		}
	}

	wele    = sd->atk_ele;
	wele_   = sd->atk_ele_;
	def_ele = sd->def_ele;
	if(battle_config.pet_status_support) {
		if(sd->status.pet_id > 0 && sd->petDB && sd->pet.intimate > 0) {
			run_script(sd->petDB->script,0,sd->bl.id,0);
		}
		pele        = sd->atk_ele;
		pdef_ele    = sd->def_ele;
		sd->atk_ele = sd->def_ele = 0;
	}
	memcpy(sd->paramcard,sd->parame,sizeof(sd->paramcard));

	// 装備品によるステータス変化はここで実行
	for(i=0; i<10; i++) {
		idx = sd->equip_index[i];
		current_equip_item_index = i;	// 部位チェック用
		current_equip_card_id = idx;	// オートスペル(重複チェック用)
		if(idx < 0)
			continue;
		if(i == 9 && sd->equip_index[8] == idx)
			continue;
		if(i == 5 && sd->equip_index[4] == idx)
			continue;
		if(i == 6 && (sd->equip_index[5] == idx || sd->equip_index[4] == idx))
			continue;
		if(sd->inventory_data[idx]) {
			sd->def += sd->inventory_data[idx]->def;
			if(sd->inventory_data[idx]->type == 4) {
				int r,wlv = sd->inventory_data[idx]->wlv;
				if(i == 8 && sd->status.inventory[idx].equip == 0x20) {
					// 二刀流用データ入力
					sd->watk_ += sd->inventory_data[idx]->atk;
					sd->watk_2 = (r = sd->status.inventory[idx].refine) * refine_db[wlv].safety_bonus;	// 精錬攻撃力
					if((r -= refine_db[wlv].limit) > 0)	// 過剰精錬ボーナス
						sd->overrefine_ = r*refine_db[wlv].over_bonus;

					if(sd->status.inventory[idx].card[0] == 0x00ff) {	// 製造武器
						sd->star_ = (sd->status.inventory[idx].card[1]>>8);	// 星のかけら
						if(sd->star_ == 15)
							sd->star_ = 40;
						wele_= sd->status.inventory[idx].card[1] & 0x0f;	// 属 性
						// ランキングボーナス
						if(ranking_get_id2rank(*((unsigned long *)(&sd->status.inventory[idx].card[2])), RK_BLACKSMITH))
							sd->ranker_weapon_bonus_ = 10;
					}
					sd->attackrange_ += sd->inventory_data[idx]->range;
					sd->state.lr_flag = 1;
					if(calclimit == 2)
						run_script(sd->inventory_data[idx]->use_script,0,sd->bl.id,0);
					run_script(sd->inventory_data[idx]->equip_script,0,sd->bl.id,0);
					sd->state.lr_flag = 0;
				} else {
					// 二刀流武器以外
					sd->watk  += sd->inventory_data[idx]->atk;
					sd->watk2 += (r = sd->status.inventory[idx].refine) * refine_db[wlv].safety_bonus;	// 精錬攻撃力
					if((r -= refine_db[wlv].limit) > 0)	// 過剰精錬ボーナス
						sd->overrefine += r*refine_db[wlv].over_bonus;

					if(sd->status.inventory[idx].card[0] == 0x00ff) {	// 製造武器
						sd->star += (sd->status.inventory[idx].card[1]>>8);	// 星のかけら
						if(sd->star == 15)
							sd->star = 40;
						wele = sd->status.inventory[idx].card[1] & 0x0f;	// 属 性
						// ランキングボーナス
						if(ranking_get_id2rank(*((unsigned long *)(&sd->status.inventory[idx].card[2])),RK_BLACKSMITH))
							sd->ranker_weapon_bonus = 10;
					}
					sd->attackrange += sd->inventory_data[idx]->range;
					if(calclimit == 2)
						run_script(sd->inventory_data[idx]->use_script,0,sd->bl.id,0);
					run_script(sd->inventory_data[idx]->equip_script,0,sd->bl.id,0);
				}
			} else if(sd->inventory_data[idx]->type == 5) {
				sd->watk  += sd->inventory_data[idx]->atk;
				refinedef += sd->status.inventory[idx].refine*refine_db[0].safety_bonus;
				if(calclimit == 2)
					run_script(sd->inventory_data[idx]->use_script,0,sd->bl.id,0);
				run_script(sd->inventory_data[idx]->equip_script,0,sd->bl.id,0);
			}
		}
	}

	if(sd->equip_index[10] >= 0) { // 矢
		idx = sd->equip_index[10];
		if(sd->inventory_data[idx]) {		// まだ属性が入っていない
			sd->state.lr_flag = 2;
			if(calclimit == 2)
				run_script(sd->inventory_data[idx]->use_script,0,sd->bl.id,0);
			run_script(sd->inventory_data[idx]->equip_script,0,sd->bl.id,0);
			sd->state.lr_flag = 0;
			sd->arrow_atk += sd->inventory_data[idx]->atk;
		}
	}

	sd->def += (refinedef+50)/100;

	if(sd->attackrange < 1)  sd->attackrange  = 1;
	if(sd->attackrange_ < 1) sd->attackrange_ = 1;
	if(sd->attackrange < sd->attackrange_)
		sd->attackrange = sd->attackrange_;
	if(sd->status.weapon == WT_BOW)
		sd->attackrange += sd->arrow_range;
	if(wele > 0)
		sd->atk_ele = wele;
	if(wele_ > 0)
		sd->atk_ele_ = wele_;
	if(def_ele > 0)
		sd->def_ele = def_ele;
	if(battle_config.pet_status_support) {
		if(pele > 0 && !sd->atk_ele)
			sd->atk_ele = pele;
		if(pdef_ele > 0 && !sd->def_ele)
			sd->def_ele = pdef_ele;
	}
	sd->double_rate += sd->double_add_rate;
	sd->perfect_hit += sd->perfect_hit_add;
	sd->get_zeny_num = (sd->get_zeny_num + sd->get_zeny_add_num > 100) ? 100 : (sd->get_zeny_num + sd->get_zeny_add_num);
	sd->get_zeny_num2 = (sd->get_zeny_num2 + sd->get_zeny_add_num2 > 100) ? 100 : (sd->get_zeny_num2 + sd->get_zeny_add_num2);
	sd->splash_range += sd->splash_add_range;
	if(sd->speed_add_rate != 100)
		sd->speed_rate += sd->speed_add_rate - 100;
	if(sd->aspd_add_rate != 100)
		sd->aspd_rate += sd->aspd_add_rate - 100;

	// 武器ATKサイズ補正
	for(i=0; i<MAX_SIZE_FIX; i++) {
		sd->atkmods[i]  = atkmods[i][sd->weapontype1];	// 右手
		sd->atkmods_[i] = atkmods[i][sd->weapontype2];	// 左手
	}

	// jobボーナス分
	for(i=0; i<sd->status.job_level && i<MAX_LEVEL; i++) {
		if(job_db[sd->s_class.job].bonus[sd->s_class.upper][i])
			sd->paramb[job_db[sd->s_class.job].bonus[sd->s_class.upper][i]-1]++;
	}

	if((skill = pc_checkskill(sd,AC_OWL)) > 0) {	// ふくろうの目
		sd->paramb[4] += skill;
	}
	if(pc_checkskill(sd,BS_HILTBINDING)) {	// ヒルトバインディング
		sd->paramb[0] += 1;
		sd->watk += 4;
	}
	if((skill = pc_checkskill(sd,SA_DRAGONOLOGY)) > 0) {	// ドラゴノロジー
		sd->paramb[3] += (skill+1)>>1;
	}

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
	// 1度も死んでないJob70スパノビに+10
	if(sd->s_class.job == 23 && sd->status.die_counter == 0 && sd->status.job_level >= 70) {
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
			int dx,dy,range;

			if(battle_config.guild_skill_check_range) {	// 距離判定を行う
				dx = abs(sd->bl.x - gmsd->bl.x);
				dy = abs(sd->bl.y - gmsd->bl.y);
				if(battle_config.guild_skill_effective_range > 0) {	// 同一距離で計算
					range = battle_config.guild_skill_effective_range;
					if(dx <= range && dy <= range) {
						sd->paramb[0] += guild_checkskill(g,GD_LEADERSHIP);	// str
						sd->paramb[1] += guild_checkskill(g,GD_SOULCOLD);	// agi
						sd->paramb[2] += guild_checkskill(g,GD_GLORYWOUNDS);	// vit
						sd->paramb[4] += guild_checkskill(g,GD_HAWKEYES);	// dex
						sd->under_the_influence_of_the_guild_skill = range+1;	// 0>で影響下,重なる場合もあるので+1
					} else {
						sd->under_the_influence_of_the_guild_skill = 0;
					}
				} else {	// 個別距離
					int min_range = 0x7fffffff;
					range = skill_get_range(GD_LEADERSHIP,guild_skill_get_lv(g,GD_LEADERSHIP));
					if(dx <= range && dy <= range) {
						sd->paramb[0] += guild_checkskill(g,GD_LEADERSHIP);	// str
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
						sd->paramb[4] += guild_checkskill(g,GD_HAWKEYES);	// dex
						if(min_range > range) min_range = range;
					}
					if(min_range == 0x7fffffff)
						sd->under_the_influence_of_the_guild_skill = 0;
					else
						sd->under_the_influence_of_the_guild_skill = min_range+1;
				}
			} else {	// マップ全体
				sd->paramb[0] += guild_checkskill(g,GD_LEADERSHIP);	// str
				sd->paramb[1] += guild_checkskill(g,GD_SOULCOLD);	// agi
				sd->paramb[2] += guild_checkskill(g,GD_GLORYWOUNDS);	// vit
				sd->paramb[4] += guild_checkskill(g,GD_HAWKEYES);	// dex
				sd->under_the_influence_of_the_guild_skill = battle_config.guild_skill_effective_range+1;
			}
		} else {
			sd->under_the_influence_of_the_guild_skill = 0;
		}
	} else {	// マップが違ったり…無効だったり
		sd->under_the_influence_of_the_guild_skill = 0;
	}

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
		// 謎なのでLV/10増加
		if(sd->sc.data[SC_HIGH].timer != -1)
		{
			sd->paramb[0] += sd->status.base_level/10;
			sd->paramb[1] += sd->status.base_level/10;
			sd->paramb[2] += sd->status.base_level/10;
			sd->paramb[3] += sd->status.base_level/10;
			sd->paramb[4] += sd->status.base_level/10;
			sd->paramb[5] += sd->status.base_level/10;
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

		if(sd->sc.data[SC_DECREASEAGI].timer != -1)	// 速度減少(agiはbattle.cで)
			sd->paramb[1] -= 2+sd->sc.data[SC_DECREASEAGI].val1;

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
			if(sd->sc.data[SC_SUITON].val4)
				sd->speed = sd->speed*2;
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
		if(sd->sc.data[SC_INCREASING].timer != -1) { // インクリーシングアキュアラシー
			sd->paramb[1] += 4;
			sd->paramb[4] += 4;
		}

		// ディフェンス
		if(sd->sc.data[SC_DEFENCE].timer != -1)
			sd->paramb[2] += sd->sc.data[SC_DEFENCE].val1*2;

		if(sd->sc.data[SC_QUAGMIRE].timer != -1) {	// クァグマイア
			short subagi = 0;
			short subdex = 0;
			subagi = (sd->status.agi/2 < sd->sc.data[SC_QUAGMIRE].val1*10) ? sd->status.agi/2 : sd->sc.data[SC_QUAGMIRE].val1*10;
			subdex = (sd->status.dex/2 < sd->sc.data[SC_QUAGMIRE].val1*10) ? sd->status.dex/2 : sd->sc.data[SC_QUAGMIRE].val1*10;
			if(map[sd->bl.m].flag.pvp || map[sd->bl.m].flag.gvg) {
				subagi /= 2;
				subdex /= 2;
			}
			sd->speed = sd->speed*4/3;
			sd->paramb[1] -= subagi;
			sd->paramb[4] -= subdex;
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
					// str
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
					// dex
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
					// str
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
					// dex
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
					// str
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
					// dex
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
					// str
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
					// dex
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
	}

	sd->paramc[0] = sd->status.str  + sd->paramb[0] + sd->parame[0];
	sd->paramc[1] = sd->status.agi  + sd->paramb[1] + sd->parame[1];
	sd->paramc[2] = sd->status.vit  + sd->paramb[2] + sd->parame[2];
	sd->paramc[3] = sd->status.int_ + sd->paramb[3] + sd->parame[3];
	sd->paramc[4] = sd->status.dex  + sd->paramb[4] + sd->parame[4];
	sd->paramc[5] = sd->status.luk  + sd->paramb[5] + sd->parame[5];

	for(i=0; i<6; i++) {
		if(sd->paramc[i] < 0)
			sd->paramc[i] = 0;
	}

	// BASEATK計算
	if( sd->status.weapon == WT_BOW ||
	    sd->status.weapon == WT_MUSICAL ||
	    sd->status.weapon == WT_WHIP ||
	    (sd->status.weapon >= WT_HANDGUN && sd->status.weapon <= WT_GRENADE) ) {
		str = sd->paramc[4];
		dex = sd->paramc[0];
	} else {
		str = sd->paramc[0];
		dex = sd->paramc[4];
	}
	dstr = str/10;

	sd->base_atk += str + dstr*dstr + dex/5 + sd->paramc[5]/5;
	sd->matk1 += sd->paramc[3]+(sd->paramc[3]/5)*(sd->paramc[3]/5);
	sd->matk2 += sd->paramc[3]+(sd->paramc[3]/7)*(sd->paramc[3]/7);

	if(sd->matk1 < sd->matk2) {
		int temp = sd->matk2;
		sd->matk2 = sd->matk1;
		sd->matk1 = temp;
	}

	sd->hit      += sd->paramc[4] + sd->status.base_level;
	sd->flee     += sd->paramc[1] + sd->status.base_level;
	sd->def2     += sd->paramc[2];
	sd->mdef2    += sd->paramc[3];
	sd->flee2    += sd->paramc[5] + 10;
	sd->critical += sd->paramc[5] * 3 + 10;

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
	}

	if(sd->sc.data[SC_MADNESSCANCEL].timer != -1) {	// マッドネスキャンセラー
		sd->base_atk += 100;
	}
	if(sd->sc.data[SC_GATLINGFEVER].timer != -1) {	// ガトリングフィーバー
		sd->base_atk += 30+(sd->sc.data[SC_GATLINGFEVER].val1*10);
	}
	if(sd->sc.data[SC_VOLCANO].timer != -1 && sd->def_ele == ELE_FIRE) {	// ボルケーノ
		sd->base_atk += sd->sc.data[SC_VOLCANO].val3;
	}
	if(sd->sc.data[SC_DRUMBATTLE].timer != -1) {	// 戦太鼓の響き
		sd->base_atk += sd->sc.data[SC_DRUMBATTLE].val2;
		//idx = sd->equip_index[8];
		// 左手には適用しない
		//if(idx >= 0 && sd->inventory_data[idx] && sd->inventory_data[idx]->type == 4)
		//	sd->watk_ += sd->sc.data[SC_DRUMBATTLE].val2;
	}

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
	if(sd->def < 0) sd->def = 0;
	if(sd->def2_rate != 100)
		sd->def2 = (sd->def2*sd->def2_rate)/100;
	if(sd->def2 < 1) sd->def2 = 1;
	if(sd->mdef_rate != 100)
		sd->mdef = (sd->mdef*sd->mdef_rate)/100;
	if(sd->mdef < 0) sd->mdef = 0;
	if(sd->mdef2_rate != 100)
		sd->mdef2 = (sd->mdef2*sd->mdef2_rate)/100;
	if(sd->mdef2 < 1) sd->mdef2 = 1;

	// 二刀流 ASPD 修正
	if(sd->status.weapon <= WT_HUUMA)
		sd->aspd += job_db[sd->s_class.job].aspd_base[sd->status.weapon]-(sd->paramc[1]*4+sd->paramc[4])*job_db[sd->s_class.job].aspd_base[sd->status.weapon]/1000;
	else
		sd->aspd += (
			(job_db[sd->s_class.job].aspd_base[sd->weapontype1]-(sd->paramc[1]*4+sd->paramc[4])*job_db[sd->s_class.job].aspd_base[sd->weapontype1]/1000) +
			(job_db[sd->s_class.job].aspd_base[sd->weapontype2]-(sd->paramc[1]*4+sd->paramc[4])*job_db[sd->s_class.job].aspd_base[sd->weapontype2]/1000)
			) * 140 / 200;

	aspd_rate = sd->aspd_rate;

	// 攻撃速度増加

	// アドバンスドブック
	if(sd->weapontype1 == WT_BOOK && (skill = pc_checkskill(sd,SA_ADVANCEDBOOK)) > 0)
	{
		aspd_rate -= skill/2;
	}
	// シングルアクション
	if(sd->status.weapon >= WT_HANDGUN && sd->status.weapon <= WT_GRENADE && (skill = pc_checkskill(sd,GS_SINGLEACTION)) > 0)
	{
		aspd_rate -= skill/2;
		sd->hit += skill*2;
	}
	// 太陽と月と星の悪魔
	if((skill = pc_checkskill(sd,SG_DEVIL)) > 0 && sd->status.job_level >= 50)
	{
		aspd_rate -= skill*3;
		clif_status_load(sd,SI_DEVIL,1);
	}

	// 太陽と月と星の融合
	if(sd && sd->sc.data[SC_FUSION].timer != -1)
	{
		aspd_rate -= 20;
		sd->perfect_hit += 100;
	}

	if(sd) {
		if(sd->sc.data[SC_SANTA].timer != -1)
			sd->view_class = 26;
		else if(sd->sc.data[SC_SUMMER].timer != -1)
			sd->view_class = 27;
	}

	if((skill = pc_checkskill(sd,AC_VULTURE)) > 0) {	// ワシの目
		sd->hit += skill;
		if(sd->status.weapon == WT_BOW)
			sd->attackrange += skill;
	}
	if((skill = pc_checkskill(sd,GS_SNAKEEYE)) > 0) {	// スネークアイ
		if(sd->status.weapon >= WT_HANDGUN && sd->status.weapon <= WT_GRENADE)
		{
			sd->attackrange += skill;
			sd->hit += skill;
		}
	}
	if((skill = pc_checkskill(sd,BS_WEAPONRESEARCH)) > 0)	// 武器研究の命中率増加
		sd->hit += skill*2;

	if(sd->sc.option&2 && (skill = pc_checkskill(sd,RG_TUNNELDRIVE)) > 0)	// トンネルドライブ
		sd->speed += (12*DEFAULT_WALK_SPEED - skill*90) / 10;

	if(sd->s_class.job == 12 && (skill = pc_checkskill(sd,TF_MISS)) > 0)	// アサシン系の回避率上昇による移動速度増加
		sd->speed -= sd->speed * skill / 100;

	if(pc_iscarton(sd) && (skill = pc_checkskill(sd,MC_PUSHCART)) > 0) {	// カートによる速度低下
		sd->speed += (10-skill) * DEFAULT_WALK_SPEED / 10;
	} else if(pc_isriding(sd)) {					// ペコペコ乗りによる速度増加
		sd->max_weight += battle_config.riding_weight;		// Weight+α(初期設定は0)10000で本鯖;
		if(sd->sc.data[SC_DEFENDER].timer == -1)		// ディフェンダー時は速度増加しない
			sd->speed -= DEFAULT_WALK_SPEED / 4;
	}

	if(sd->sc.count > 0) {
		int sc_speed_rate = 100;
		if(sd->sc.data[SC_AVOID].timer != -1)				// 緊急回避
			sc_speed_rate -= sd->sc.data[SC_AVOID].val1*10;
		if(sd->sc.data[SC_INCREASEAGI].timer != -1 && sc_speed_rate > 75)	// 速度増加による移動速度増加
			sc_speed_rate = 75;
		if(sd->sc.data[SC_RUN].timer != -1 && sc_speed_rate > 50)		// 駆け足による移動速度増加
			sc_speed_rate = 50;
		if(sd->sc.data[SC_BERSERK].timer != -1 && sc_speed_rate > 75)	// バーサークによる移動速度増加
			sc_speed_rate = 75;
		if(sd->sc.data[SC_CARTBOOST].timer != -1 && sc_speed_rate > 80)	// カートブーストによる移動速度増加
			sc_speed_rate = 80;
		if(sd->sc.data[SC_FUSION].timer != -1 && sc_speed_rate > 75)	// 太陽と月と星の融合による移動速度増加
			sc_speed_rate = 75;
		if(sd->sc.data[SC_WINDWALK].timer != -1 && sc_speed_rate > 100-(sd->sc.data[SC_WINDWALK].val1*2))	// ウィンドウォークによる移動速度増加
			sc_speed_rate = 100-(sd->sc.data[SC_WINDWALK].val1*2);

		sd->speed = sd->speed*sc_speed_rate/100;

		if(sd->sc.data[SC_CLOAKING].timer != -1)	// クローキングによる速度変化
		{
			int check = 1;
			for(i=0; i<8; i++) {
				if(map_getcell(sd->bl.m,sd->bl.x+dirx[i],sd->bl.y+diry[i],CELL_CHKNOPASS)) {
					check = 0;
					break;
				}
			}
			if(check) {
				// 平地移動速度
				sd->speed += sd->speed * (30-sd->sc.data[SC_CLOAKING].val1*3) / 100;
			} else {
				// 壁沿い移動速度
				int rate = (sd->sc.data[SC_CLOAKING].val1 -1)*3;
				if(rate > 25)
					rate = 25;
				sd->speed -= sd->speed * rate / 100;
			}
		}

		if(sd->sc.data[SC_CHASEWALK].timer != -1)	// チェイスウォークによる速度変化
		{
			if(sd->sc.data[SC_ROGUE].timer == -1)
				sd->speed += sd->speed*(35 - (5*sd->sc.data[SC_CHASEWALK].val1))/100;
		}

		if(sd->sc.data[SC_DECREASEAGI].timer != -1) {		// 速度減少(agiはbattle.cで)
			if(sd->sc.data[SC_DEFENDER].timer == -1) {	// ディフェンダー時は速度低下しない
				sd->speed = sd->speed *((sd->sc.data[SC_DECREASEAGI].val1 > 5)? 150: 133)/100;
			}
		}

		if(sd->sc.data[SC_WEDDING].timer != -1)	// 結婚中は歩くのが遅い
			sd->speed = 2*DEFAULT_WALK_SPEED;
	}

	if(sd->s_class.job == 23 && sd->status.base_level >= 99)
	{
		if(pc_isupper(sd))
			sd->status.max_hp += 2000*(100 + sd->paramc[2])/100 * battle_config.upper_hp_rate/100;
		else if(pc_isbaby(sd))	// 養子の場合最大HP70%
			sd->status.max_hp += 2000*(100 + sd->paramc[2])/100 * battle_config.baby_hp_rate/100;
		else
			sd->status.max_hp += 2000*(100 + sd->paramc[2])/100 * battle_config.normal_hp_rate/100;
	}

	if((skill = pc_checkskill(sd,CR_TRUST)) > 0) { // フェイス
		sd->status.max_hp    += skill*200;
		sd->subele[ELE_HOLY] += skill*5;
	}

	if((skill = pc_checkskill(sd,BS_SKINTEMPER)) > 0) { // スキンテンパリング
		sd->subele[ELE_FIRE]    += skill*4;
		sd->subele[ELE_NEUTRAL] += skill*1;
	}

	// bAtkRange2,bAtkRangeRate2の射程計算
	sd->attackrange  += sd->add_attackrange;
	sd->attackrange_ += sd->add_attackrange;
	sd->attackrange  = sd->attackrange  * sd->add_attackrange_rate / 100;
	sd->attackrange_ = sd->attackrange_ * sd->add_attackrange_rate / 100;
	if(sd->attackrange < 1)  sd->attackrange  = 1;
	if(sd->attackrange_ < 1) sd->attackrange_ = 1;
	if(sd->attackrange < sd->attackrange_)
		sd->attackrange = sd->attackrange_;

	blv = (sd->status.base_level > 0)? sd->status.base_level - 1: 0;

	// 最大HP計算
	calc_val = job_db[sd->s_class.job].hp_base[blv] * (100 + sd->paramc[2]) / 100 + (sd->parame[2] - sd->paramcard[2]);

	if(pc_isupper(sd))	// 転生職の場合最大HP25%UP
		sd->status.max_hp += calc_val * battle_config.upper_hp_rate / 100;
	else if(pc_isbaby(sd))	// 養子の場合最大HP70%
		sd->status.max_hp += calc_val * battle_config.baby_hp_rate / 100;
	else
		sd->status.max_hp += calc_val * battle_config.normal_hp_rate / 100;

	if(sd->hprate != 100)
		sd->status.max_hp = sd->status.max_hp * sd->hprate / 100;

	if(sd->sc.data[SC_BERSERK].timer != -1) {	// バーサーク
		sd->status.max_hp *= 3;
	}
	if(sd->sc.data[SC_INCMHP2].timer != -1) {
		sd->status.max_hp *= (100 + sd->sc.data[SC_INCMHP2].val1) / 100;
	}

	// 最大SP計算
	calc_val = job_db[sd->s_class.job].sp_base[blv] * (100 + sd->paramc[3]) / 100 + (sd->parame[3] - sd->paramcard[3]);

	if(pc_isupper(sd))	// 転生職の場合最大SP125%
		sd->status.max_sp += calc_val * battle_config.upper_sp_rate / 100;
	else if(pc_isbaby(sd))	// 養子の場合最大SP70%
		sd->status.max_sp += calc_val * battle_config.baby_sp_rate / 100;
	else
		sd->status.max_sp += calc_val * battle_config.normal_sp_rate / 100;

	if(sd->sprate != 100)
		sd->status.max_sp = sd->status.max_sp * sd->sprate / 100;

	if((skill = pc_checkskill(sd,HP_MEDITATIO)) > 0) // メディタティオ
		sd->status.max_sp += sd->status.max_sp * skill / 100;
	if((skill = pc_checkskill(sd,HW_SOULDRAIN)) > 0) // ソウルドレイン
		sd->status.max_sp += sd->status.max_sp * 2 * skill / 100;
	if((skill = pc_checkskill(sd,SL_KAINA)) > 0)	// カイナ
		sd->status.max_sp += 30 * skill;

	if(sd->sc.data[SC_INCMSP2].timer != -1) {
		sd->status.max_sp *= (100 + sd->sc.data[SC_INCMSP2].val1) / 100;
	}

	// 自然回復HP
	sd->nhealhp = 1 + (sd->paramc[2]/5) + (sd->status.max_hp/200);
	if((skill = pc_checkskill(sd,SM_RECOVERY)) > 0) {	// HP回復力向上
		sd->nshealhp = skill*5 + (sd->status.max_hp*skill/500);
		if(sd->nshealhp > 0x7fff)
			sd->nshealhp = 0x7fff;
	}
	if((skill = pc_checkskill(sd,TK_HPTIME)) > 0) {	// 安らかな休息
		sd->tk_nhealhp = skill*30 + (sd->status.max_hp*skill/500);
		if(sd->tk_nhealhp > 0x7fff)
			sd->tk_nhealhp = 0x7fff;
	}
	if(sd->sc.data[SC_BERSERK].timer != -1) {
		sd->nhealhp = 0;
	}
	// 自然回復SP
	sd->nhealsp = 1 + (sd->paramc[3]/6) + (sd->status.max_sp/100);
	if(sd->paramc[3] >= 120)
		sd->nhealsp += ((sd->paramc[3]-120)>>1) + 4;
	if((skill = pc_checkskill(sd,MG_SRECOVERY)) > 0) {	// SP回復力向上
		sd->nshealsp = skill*3 + (sd->status.max_sp*skill/500);
		if(sd->nshealsp > 0x7fff)
			sd->nshealsp = 0x7fff;
	}
	if((skill = pc_checkskill(sd,NJ_NINPOU)) > 0) {	// 忍法修練
		sd->nshealsp = skill*3 + (sd->status.max_sp*skill/500);
		if(sd->nshealsp > 0x7fff)
			sd->nshealsp = 0x7fff;
	}

	if((skill = pc_checkskill(sd,MO_SPIRITSRECOVERY)) > 0) {
		sd->nsshealhp = skill*4 + (sd->status.max_hp*skill/500);
		sd->nsshealsp = skill*2 + (sd->status.max_sp*skill/500);
		if(sd->nsshealhp > 0x7fff)
			sd->nsshealhp = 0x7fff;
		if(sd->nsshealsp > 0x7fff)
			sd->nsshealsp = 0x7fff;
	}
	if((skill = pc_checkskill(sd,TK_SPTIME)) > 0) { // 楽しい休息
		sd->tk_nhealsp = skill*3 + (sd->status.max_sp*skill/500);
		if(sd->tk_nhealsp > 0x7fff)
			sd->tk_nhealsp = 0x7fff;
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
	if((skill = pc_checkskill(sd,HP_MEDITATIO)) > 0) {
		// メディタティオはSPRではなく自然回復にかかる
		sd->nhealsp += (sd->nhealsp)*3*skill/100;
		if(sd->nhealsp > 0x7fff)
			sd->nhealsp = 0x7fff;
	}

	// 種族耐性（これでいいの？ ディバインプロテクションと同じ処理がいるかも）
	if((skill = pc_checkskill(sd,SA_DRAGONOLOGY)) > 0) {	// ドラゴノロジー
		skill = skill*4;
		sd->addrace[RCT_DRAGON]  += skill;
		sd->addrace_[RCT_DRAGON] += skill;
		sd->subrace[RCT_DRAGON]  += skill;
	}
	// Flee上昇
	if((skill = pc_checkskill(sd,TF_MISS)) > 0) {	// 回避率増加
		if(sd->s_class.job == 12 || sd->s_class.job == 17)
			sd->flee += skill*4;
		else
			sd->flee += skill*3;
	}
	if((skill = pc_checkskill(sd,MO_DODGE)) > 0)	// 見切り
		sd->flee += (skill*3)>>1;
	if(sd->sc.count > 0) {
		if(sd->sc.data[SC_INCFLEE].timer != -1)
			sd->flee += sd->sc.data[SC_INCFLEE].val1;
		if(sd->sc.data[SC_INCFLEE2].timer != -1)
			sd->flee += sd->sc.data[SC_INCFLEE2].val1;
	}

	// スキルやステータス異常による残りのパラメータ補正
	if(sd->sc.count > 0) {
		// 太陽の安楽 DEF増加
		if(sd->sc.data[SC_SUN_COMFORT].timer != -1 && sd->bl.m == sd->feel_index[0])
			sd->def2 += (sd->status.base_level + sd->status.dex + sd->status.luk)/2;
			//sd->def += (sd->status.base_level + sd->status.dex + sd->status.luk + sd->paramb[4] + sd->paramb[5])/10;

		// 月の安楽
		if(sd->sc.data[SC_MOON_COMFORT].timer != -1 && sd->bl.m == sd->feel_index[1])
			sd->flee += (sd->status.base_level + sd->status.dex + sd->status.luk)/10;
			//sd->flee += (sd->status.base_level + sd->status.dex + sd->status.luk + sd->paramb[4] + sd->paramb[5])/10;

		// 星の安楽
		if(sd->sc.data[SC_STAR_COMFORT].timer != -1 && sd->bl.m == sd->feel_index[2])
			aspd_rate -= (sd->status.base_level + sd->status.dex + sd->status.luk)/10;
			//aspd_rate += (sd->status.base_level + sd->status.dex + sd->status.luk + sd->paramb[0] + sd->paramb[4] + sd->paramb[5])/10;

		// クローズコンファイン
		if(sd->sc.data[SC_CLOSECONFINE].timer != -1)
			sd->flee += 10;

		// ATK/DEF変化形
		if(sd->sc.data[SC_ANGELUS].timer != -1)	// エンジェラス
			sd->def2 = sd->def2*(110+5*sd->sc.data[SC_ANGELUS].val1)/100;
		if(sd->sc.data[SC_IMPOSITIO].timer != -1) {// インポシティオマヌス
			sd->watk += sd->sc.data[SC_IMPOSITIO].val1*5;
			idx = sd->equip_index[8];
			// 左手には適用しない
			//if(idx >= 0 && sd->inventory_data[idx] && sd->inventory_data[idx]->type == 4)
			//	sd->watk_ += sd->sc.data[SC_IMPOSITIO].val1*5;
		}
		if(sd->sc.data[SC_PROVOKE].timer != -1) {	// プロボック
			sd->def2 = sd->def2*(100-6*sd->sc.data[SC_PROVOKE].val1)/100;
			sd->base_atk = sd->base_atk*(100+2*sd->sc.data[SC_PROVOKE].val1)/100;
			sd->watk = sd->watk*(100+2*sd->sc.data[SC_PROVOKE].val1)/100;
			idx = sd->equip_index[8];
			// 左手には適用しない
			//if(idx >= 0 && sd->inventory_data[idx] && sd->inventory_data[idx]->type == 4)
			//	sd->watk_ = sd->watk_*(100+2*sd->sc.data[SC_PROVOKE].val1)/100;
		}
		if(sd->sc.data[SC_POISON].timer != -1)	// 毒状態
			sd->def2 = sd->def2*75/100;

		// 運命のタロットカード
		if(sd->sc.data[SC_THE_MAGICIAN].timer != -1) {
			// ATK半減
			sd->base_atk = sd->base_atk * 50/100;
			sd->watk = sd->watk * 50/100;
			idx = sd->equip_index[8];
			if(idx >= 0 && sd->inventory_data[idx] && sd->inventory_data[idx]->type == 4)
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
			idx = sd->equip_index[8];
			if(idx >= 0 && sd->inventory_data[idx] && sd->inventory_data[idx]->type == 4) {
				sd->watk_ = sd->watk_ * 50/100;
			}
			sd->matk1 = sd->matk1*50/100;
			sd->matk2 = sd->matk2*50/100;
		}
		if(sd->sc.data[SC_THE_SUN].timer != -1) {
			// ATK、MATK、回避、命中、防御力が全て20%ずつ下落する
			sd->base_atk = sd->base_atk * 80/100;
			sd->watk = sd->watk * 80/100;
			idx = sd->equip_index[8];
			if(idx >= 0 && sd->inventory_data[idx] && sd->inventory_data[idx]->type == 4) {
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
		if(sd->sc.data[SC_NIBELUNGEN].timer != -1) {	// ニーベルングの指輪
			idx = sd->equip_index[9];
			if(idx >= 0 && sd->inventory_data[idx] && sd->inventory_data[idx]->wlv >= 4)
				sd->watk += sd->sc.data[SC_NIBELUNGEN].val2;
			//idx = sd->equip_index[8];
			// 左手には適用しない
			//if(idx >= 0 && sd->inventory_data[idx] && sd->inventory_data[idx]->wlv >= 4)
			//	sd->watk_ += sd->sc.data[SC_NIBELUNGEN].val2;
		}

		if(sd->sc.data[SC_INCATK2].timer != -1) {
			sd->watk = sd->watk*(100+sd->sc.data[SC_INCATK2].val1)/100;
		}

		if(sd->sc.data[SC_SIGNUMCRUCIS].timer != -1)
			sd->def = sd->def * (100 - sd->sc.data[SC_SIGNUMCRUCIS].val2)/100;
		if(sd->sc.data[SC_ETERNALCHAOS].timer != -1)	// エターナルカオス
			sd->def2 = 0;

		if(sd->sc.data[SC_CONCENTRATION].timer != -1) {	// コンセントレーション
			sd->base_atk = sd->base_atk * (100 + 5*sd->sc.data[SC_CONCENTRATION].val1)/100;
			sd->watk = sd->watk * (100 + 5*sd->sc.data[SC_CONCENTRATION].val1)/100;
			idx = sd->equip_index[8];
			if(idx >= 0 && sd->inventory_data[idx] && sd->inventory_data[idx]->type == 4)
				sd->watk_ = sd->watk_ * (100 + 5*sd->sc.data[SC_CONCENTRATION].val1)/100;
			sd->def = sd->def * (100 - 5*sd->sc.data[SC_CONCENTRATION].val1)/100;
			sd->def2 = sd->def2 * (100 - 5*sd->sc.data[SC_CONCENTRATION].val1)/100;
		}

		if(sd->sc.data[SC_INCATK].timer != -1) {	// ATK上昇 (神酒用)
			sd->watk += sd->sc.data[SC_INCATK].val1;
		}
		if(sd->sc.data[SC_INCMATK].timer != -1) {	// MATK上昇 (神秘の草用)
			sd->matk1 += sd->sc.data[SC_INCMATK].val1;
			sd->matk2 += sd->sc.data[SC_INCMATK].val1;
		}
		if(sd->sc.data[SC_MINDBREAKER].timer != -1) {
			sd->matk1 += (sd->matk1*20*sd->sc.data[SC_MINDBREAKER].val1)/100;
			sd->matk2 += (sd->matk2*20*sd->sc.data[SC_MINDBREAKER].val1)/100;
			sd->mdef2 -= (sd->mdef2*12*sd->sc.data[SC_MINDBREAKER].val1)/100;
		}
		if(sd->sc.data[SC_ENDURE].timer != -1) {
			sd->mdef += sd->sc.data[SC_ENDURE].val1;
		}

		// ASPD/移動速度変化系
		if(sd->sc.data[SC_TWOHANDQUICKEN].timer != -1 && sd->sc.data[SC_QUAGMIRE].timer == -1 && sd->sc.data[SC_DONTFORGETME].timer == -1 && sd->sc.data[SC_DECREASEAGI].timer == -1)	// 2HQ
			aspd_rate -= sd->sc.data[SC_TWOHANDQUICKEN].val2;

		if(sd->sc.data[SC_ONEHAND].timer != -1 && sd->sc.data[SC_QUAGMIRE].timer == -1 && sd->sc.data[SC_DONTFORGETME].timer == -1 && sd->sc.data[SC_DECREASEAGI].timer == -1)	// 1HQ
			aspd_rate -= 30;

		if(sd->sc.data[SC_ADRENALINE2].timer != -1 && sd->sc.data[SC_TWOHANDQUICKEN].timer == -1 && sd->sc.data[SC_ONEHAND].timer == -1 &&
			sd->sc.data[SC_QUAGMIRE].timer == -1 && sd->sc.data[SC_DONTFORGETME].timer == -1 && sd->sc.data[SC_DECREASEAGI].timer == -1) {	// アドレナリンラッシュ2
			if(sd->sc.data[SC_ADRENALINE2].val2 || !battle_config.party_skill_penalty)
				aspd_rate -= 30;
			else
				aspd_rate -= 25;
		}else if(sd->sc.data[SC_ADRENALINE].timer != -1 && sd->sc.data[SC_TWOHANDQUICKEN].timer == -1 && sd->sc.data[SC_ONEHAND].timer == -1 &&
			sd->sc.data[SC_QUAGMIRE].timer == -1 && sd->sc.data[SC_DONTFORGETME].timer == -1 && sd->sc.data[SC_DECREASEAGI].timer == -1) {	// アドレナリンラッシュ
			if(sd->sc.data[SC_ADRENALINE].val2 || !battle_config.party_skill_penalty)
				aspd_rate -= 30;
			else
				aspd_rate -= 25;
		}
		if(sd->sc.data[SC_SPEARQUICKEN].timer != -1 && sd->sc.data[SC_ADRENALINE].timer == -1 && sd->sc.data[SC_ADRENALINE2].timer == -1 &&
			sd->sc.data[SC_TWOHANDQUICKEN].timer == -1 && sd->sc.data[SC_ONEHAND].timer == -1 &&
			sd->sc.data[SC_QUAGMIRE].timer == -1 && sd->sc.data[SC_DONTFORGETME].timer == -1 && sd->sc.data[SC_DECREASEAGI].timer == -1)	// スピアクィッケン
			aspd_rate -= sd->sc.data[SC_SPEARQUICKEN].val2;

		if(sd->sc.data[SC_ASSNCROS].timer != -1 && // 夕陽のアサシンクロス
		   sd->sc.data[SC_TWOHANDQUICKEN].timer == -1 && sd->sc.data[SC_ONEHAND].timer == -1 &&
		   sd->sc.data[SC_ADRENALINE].timer == -1 && sd->sc.data[SC_ADRENALINE2].timer == -1 &&
		   sd->sc.data[SC_SPEARQUICKEN].timer == -1 && sd->sc.data[SC_DONTFORGETME].timer == -1 && sd->status.weapon != WT_BOW && !(sd->status.weapon >= WT_HANDGUN && sd->status.weapon <= WT_GRENADE))
				aspd_rate -= 5+sd->sc.data[SC_ASSNCROS].val1+sd->sc.data[SC_ASSNCROS].val2+sd->sc.data[SC_ASSNCROS].val3;
		else if(sd->sc.data[SC_ASSNCROS_].timer != -1 && // 夕陽のアサシンクロス
		        sd->sc.data[SC_TWOHANDQUICKEN].timer == -1 && sd->sc.data[SC_ONEHAND].timer == -1 &&
		        sd->sc.data[SC_ADRENALINE].timer == -1 && sd->sc.data[SC_ADRENALINE2].timer == -1 &&
		        sd->sc.data[SC_SPEARQUICKEN].timer == -1 && sd->sc.data[SC_DONTFORGETME].timer == -1 && sd->status.weapon != WT_BOW && !(sd->status.weapon >= WT_HANDGUN && sd->status.weapon <= WT_GRENADE))
				aspd_rate -= 5+sd->sc.data[SC_ASSNCROS_].val1+sd->sc.data[SC_ASSNCROS_].val2+sd->sc.data[SC_ASSNCROS_].val3;

		if(sd->sc.data[SC_DONTFORGETME].timer != -1) {		// 私を忘れないで
			aspd_rate += sd->sc.data[SC_DONTFORGETME].val1*3 + sd->sc.data[SC_DONTFORGETME].val2 + (sd->sc.data[SC_DONTFORGETME].val3>>16);
			sd->speed = sd->speed*(100+sd->sc.data[SC_DONTFORGETME].val1*2 + sd->sc.data[SC_DONTFORGETME].val2 + (sd->sc.data[SC_DONTFORGETME].val3&0xffff))/100;
		} else if(sd->sc.data[SC_DONTFORGETME_].timer != -1) {		// 私を忘れないで
			aspd_rate += sd->sc.data[SC_DONTFORGETME_].val1*3 + sd->sc.data[SC_DONTFORGETME_].val2 + (sd->sc.data[SC_DONTFORGETME_].val3>>16);
			sd->speed = sd->speed*(100+sd->sc.data[SC_DONTFORGETME_].val1*2 + sd->sc.data[SC_DONTFORGETME_].val2 + (sd->sc.data[SC_DONTFORGETME_].val3&0xffff))/100;
		}

		if(sd->sc.data[SC_GRAVITATION].timer != -1)
		{
			aspd_rate += sd->sc.data[SC_GRAVITATION].val1*5;
			if(battle_config.player_gravitation_type)
				sd->speed = sd->speed*(100+sd->sc.data[SC_GRAVITATION].val1*5)/100;

		}
		if(sd->sc.data[SC_BERSERK].timer != -1) {
			aspd_rate -= 30;
		}
		if(sd->sc.data[SC_POISONPOTION].timer != -1) {
			aspd_rate -= 25;
		}
		if(sd->sc.data[i = SC_SPEEDPOTION3].timer != -1 ||
		   sd->sc.data[i = SC_SPEEDPOTION2].timer != -1 ||
		   sd->sc.data[i = SC_SPEEDPOTION1].timer != -1 ||
		   sd->sc.data[i = SC_SPEEDPOTION0].timer != -1)	// 増速ポーション
			aspd_rate -= sd->sc.data[i].val2;

		// HIT/FLEE変化系
		if(sd->sc.data[SC_WHISTLE].timer != -1) {  // 口笛
			sd->flee  += sd->flee * (sd->sc.data[SC_WHISTLE].val1+sd->sc.data[SC_WHISTLE].val2+(sd->sc.data[SC_WHISTLE].val3>>16))/100;
			sd->flee2 += (sd->sc.data[SC_WHISTLE].val1+sd->sc.data[SC_WHISTLE].val2+(sd->sc.data[SC_WHISTLE].val3&0xffff)) * 10;
		} else if(sd->sc.data[SC_WHISTLE_].timer != -1) {  // 口笛
			sd->flee  += sd->flee * (sd->sc.data[SC_WHISTLE_].val1+sd->sc.data[SC_WHISTLE_].val2+(sd->sc.data[SC_WHISTLE_].val3>>16))/100;
			sd->flee2 += (sd->sc.data[SC_WHISTLE_].val1+sd->sc.data[SC_WHISTLE_].val2+(sd->sc.data[SC_WHISTLE_].val3&0xffff)) * 10;
		}

		if(sd->sc.data[SC_HUMMING].timer != -1) {  // ハミング
			sd->hit += (sd->sc.data[SC_HUMMING].val1*2+sd->sc.data[SC_HUMMING].val2+sd->sc.data[SC_HUMMING].val3) * sd->hit/100;
		} else if(sd->sc.data[SC_HUMMING_].timer != -1) {  // ハミング
			sd->hit += (sd->sc.data[SC_HUMMING_].val1*2+sd->sc.data[SC_HUMMING_].val2+sd->sc.data[SC_HUMMING_].val3) * sd->hit/100;
		}

		if(sd->sc.data[SC_VIOLENTGALE].timer != -1 && sd->def_ele == ELE_WIND) {	// バイオレントゲイル
			sd->flee += sd->flee*sd->sc.data[SC_VIOLENTGALE].val3/100;
		}
		if(sd->sc.data[SC_BLIND].timer != -1) {	// 暗黒
			sd->hit  -= sd->hit*25/100;
			sd->flee -= sd->flee*25/100;
		}
		if(sd->sc.data[SC_WINDWALK].timer != -1)	// ウィンドウォーク
			sd->flee += sd->flee*(sd->sc.data[SC_WINDWALK].val2)/100;
		if(sd->sc.data[SC_SPIDERWEB].timer != -1)	// スパイダーウェブ
			sd->flee -= sd->flee*50/100;
		if(sd->sc.data[SC_TRUESIGHT].timer != -1)	// トゥルーサイト
			sd->hit += 3*(sd->sc.data[SC_TRUESIGHT].val1);
		if(sd->sc.data[SC_CONCENTRATION].timer != -1)	// コンセントレーション
			sd->hit += 10*(sd->sc.data[SC_CONCENTRATION].val1);
		if(sd->sc.data[SC_INCHIT].timer != -1)
			sd->hit += sd->sc.data[SC_INCHIT].val1;
		if(sd->sc.data[SC_INCHIT2].timer != -1)
			sd->hit *= (100+sd->sc.data[SC_INCHIT2].val1)/100;
		if(sd->sc.data[SC_BERSERK].timer != -1)
			sd->flee -= sd->flee*50/100;
		if(sd->sc.data[SC_INCFLEE].timer != -1)	// 速度強化
			sd->flee += sd->flee*(sd->sc.data[SC_INCFLEE].val2)/100;

		// ガンスリンガースキル
		if(sd->sc.data[SC_FLING].timer != -1) {		// フライング
			sd->def = sd->def * (100 - 5*sd->sc.data[SC_FLING].val1)/100;
		}
		if(sd->sc.data[SC_MADNESSCANCEL].timer != -1) {	// マッドネスキャンセラー
			aspd_rate    -= 20;
		}
		if(sd->sc.data[SC_ADJUSTMENT].timer != -1) {	// アジャストメント
			sd->hit  -= 30;
			sd->flee += 30;
		}
		if(sd->sc.data[SC_INCREASING].timer != -1) {	// インクリーシングアキュアラシー
			sd->hit += 20;
		}
		if(sd->sc.data[SC_GATLINGFEVER].timer != -1) {	// ガトリングフィーバー
			aspd_rate    -= sd->sc.data[SC_GATLINGFEVER].val1*2;
			sd->flee     -= sd->sc.data[SC_GATLINGFEVER].val1*5;
			sd->speed    = (sd->speed * 135) / 100;
		}

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
			for(i=1; i<ELE_MAX; i++)
				sd->subele[i] += sd->sc.data[SC_RESISTALL].val1;	// 全てに耐性増加
		}
		// 不死身のジークフリード
		if(sd->sc.data[SC_SIEGFRIED].timer != -1) {
			for(i=1; i<ELE_MAX; i++)
				sd->subele[i] += sd->sc.data[SC_SIEGFRIED].val2;	// 全てに耐性増加
		}
		// プロヴィデンス
		if(sd->sc.data[SC_PROVIDENCE].timer != -1) {
			sd->subele[ELE_HOLY]   += sd->sc.data[SC_PROVIDENCE].val2;	// 対聖属性
			sd->subrace[RCT_DEMON] += sd->sc.data[SC_PROVIDENCE].val2;	// 対悪魔
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
					sd->speed += (sd->speed * 50)/100;
					break;
				case 1:		// 手首
					sd->aspd -= (sd->aspd * 25)/100;
					break;
				case 2:		// 膝
					sd->speed += (sd->speed * 30)/100;
					sd->aspd  -= (sd->aspd * 10)/100;
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
			sd->status.max_hp += ((5+sd->sc.data[SC_APPLEIDUN].val1*2+((sd->sc.data[SC_APPLEIDUN].val2+1)>>1)
						+sd->sc.data[SC_APPLEIDUN].val3/10) * sd->status.max_hp)/100;

		} else if(sd->sc.data[SC_APPLEIDUN_].timer != -1) {	// イドゥンの林檎
			sd->status.max_hp += ((5+sd->sc.data[SC_APPLEIDUN_].val1*2+((sd->sc.data[SC_APPLEIDUN_].val2+1)>>1)
						+sd->sc.data[SC_APPLEIDUN_].val3/10) * sd->status.max_hp)/100;
		}

		if(sd->sc.data[SC_DELUGE].timer != -1 && sd->def_ele == ELE_WATER) {	// デリュージ
			sd->status.max_hp += sd->status.max_hp*sd->sc.data[SC_DELUGE].val3/100;
		}
		if(sd->sc.data[SC_SERVICE4U].timer != -1) {	// サービスフォーユー
			sd->status.max_sp += sd->status.max_sp*(10+sd->sc.data[SC_SERVICE4U].val1+sd->sc.data[SC_SERVICE4U].val2
						+sd->sc.data[SC_SERVICE4U].val3)/100;
			sd->dsprate -= 10+sd->sc.data[SC_SERVICE4U].val1*3+sd->sc.data[SC_SERVICE4U].val2+sd->sc.data[SC_SERVICE4U].val3;
			if(sd->dsprate < 0)
				sd->dsprate = 0;
		} else if(sd->sc.data[SC_SERVICE4U_].timer != -1) {	// サービスフォーユー
			sd->status.max_sp += sd->status.max_sp*(10+sd->sc.data[SC_SERVICE4U_].val1+sd->sc.data[SC_SERVICE4U_].val2
						+sd->sc.data[SC_SERVICE4U_].val3)/100;
			sd->dsprate -= 10+sd->sc.data[SC_SERVICE4U_].val1*3+sd->sc.data[SC_SERVICE4U_].val2+sd->sc.data[SC_SERVICE4U_].val3;
			if(sd->dsprate < 0)
				sd->dsprate = 0;
		}

		if(sd->sc.data[SC_FORTUNE].timer != -1) {	// 幸運のキス
			sd->critical += (10+sd->sc.data[SC_FORTUNE].val1+sd->sc.data[SC_FORTUNE].val2+sd->sc.data[SC_FORTUNE].val3)*10;
		} else if(sd->sc.data[SC_FORTUNE_].timer != -1) {	// 幸運のキス
			sd->critical += (10+sd->sc.data[SC_FORTUNE_].val1+sd->sc.data[SC_FORTUNE_].val2+sd->sc.data[SC_FORTUNE_].val3)*10;
		}

		if(sd->sc.data[SC_EXPLOSIONSPIRITS].timer != -1) {	// 爆裂波動
			if(sd->s_class.job == 23)
				sd->critical += sd->sc.data[SC_EXPLOSIONSPIRITS].val1*100;
			else
				sd->critical += sd->sc.data[SC_EXPLOSIONSPIRITS].val2;
		}

		if(sd->sc.data[SC_STEELBODY].timer != -1) {	// 金剛
			sd->def = 90;
			sd->mdef = 90;
			aspd_rate += 25;
			sd->speed = (sd->speed * 135) / 100;
		}
		if(sd->sc.data[SC_DEFENDER].timer != -1) {	// ディフェンダー
			sd->aspd += (25 - sd->sc.data[SC_DEFENDER].val1*5);
			sd->speed = (sd->speed * (155 - sd->sc.data[SC_DEFENDER].val1*5)) / 100;
		}
		if(sd->sc.data[SC_ENCPOISON].timer != -1)
			sd->addeff[4] += sd->sc.data[SC_ENCPOISON].val2;

		if(sd->sc.data[SC_DANCING].timer != -1 && sd->sc.data[SC_BARDDANCER].timer == -1) // 踊り/演奏
		{
			if(sd->sc.data[SC_LONGINGFREEDOM].timer != -1) {
				if(sd->sc.data[SC_LONGINGFREEDOM].val1 < 5) {
					sd->speed = sd->speed * (200-20*sd->sc.data[SC_LONGINGFREEDOM].val1)/100;
					sd->aspd  = sd->aspd * (200-20*sd->sc.data[SC_LONGINGFREEDOM].val1)/100;
				}
			} else {
				int lesson_ba = pc_checkskill(sd,BA_MUSICALLESSON);
				int lesson_dc = pc_checkskill(sd,DC_DANCINGLESSON);
				sd->speed = sd->speed * (400-20*((lesson_ba > lesson_dc)? lesson_ba: lesson_dc))/100;
			}
		}

		if(sd->sc.data[SC_CURSE].timer != -1) {
			if(sd->sc.data[SC_DEFENDER].timer == -1)	// ディフェンダー時は呪いで速度低下しない
				sd->speed += 450;
		}
		if(sd->sc.data[SC_TRUESIGHT].timer != -1)	// トゥルーサイト
			sd->critical += 10*(sd->sc.data[SC_TRUESIGHT].val1);

		/*
		if(sd->sc.data[SC_VOLCANO].timer != -1)	// エンチャントポイズン(属性はbattle.cで)
			sd->addeff[2] += sd->sc.data[SC_VOLCANO].val2;	// % of granting
		if(sd->sc.data[SC_DELUGE].timer != -1)	// エンチャントポイズン(属性はbattle.cで)
			sd->addeff[0] += sd->sc.data[SC_DELUGE].val2;	// % of granting
		*/
	}
	// テコンランカーボーナス
	if(sd->status.class_ == PC_CLASS_TK && sd->status.base_level >= 90 && ranking_get_pc_rank(sd,RK_TAEKWON) > 0)
	{
		sd->status.max_hp *= 3;
		sd->status.max_sp *= 3;
	}

	if(sd->speed_rate != 100)
		sd->speed = sd->speed*sd->speed_rate/100;

	if(aspd_rate != 100)
		sd->aspd = sd->aspd*aspd_rate/100;
	if(pc_isriding(sd))							// 騎兵修練
		sd->aspd = sd->aspd*(100 + 10*(5 - pc_checkskill(sd,KN_CAVALIERMASTERY)))/ 100;

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
	if(sd->fix_status.aspd >= 10 && sd->fix_status.aspd <= 199) {
		sd->aspd = 2000 - sd->fix_status.aspd * 10;
	}
	if(sd->fix_status.speed > MIN_WALK_SPEED && sd->fix_status.speed <= MAX_WALK_SPEED) {
		sd->speed = sd->fix_status.speed;
	}

	if(sd->speed < 1)
		sd->speed = 1;
	if(sd->aspd < battle_config.max_aspd)
		sd->aspd = battle_config.max_aspd;

	if(map[sd->bl.m].flag.pk) {
		if(sd->aspd < battle_config.pk_max_aspd)
			sd->aspd = battle_config.pk_max_aspd;
	}
	if(map[sd->bl.m].flag.gvg) {
		if(sd->aspd < battle_config.gvg_max_aspd)
			sd->aspd = battle_config.gvg_max_aspd;
	}
	if(map[sd->bl.m].flag.pvp) {
		if(sd->aspd < battle_config.pvp_max_aspd)
			sd->aspd = battle_config.pvp_max_aspd;
	}
	sd->amotion = sd->aspd;
	sd->dmotion = 800-sd->paramc[1]*4;
	if(sd->dmotion < 400)
		sd->dmotion = 400;
	if(sd->ud.skilltimer != -1 && (skill = pc_checkskill(sd,SA_FREECAST)) > 0) {
		sd->prev_speed = sd->speed;
		sd->speed = sd->speed*(175 - skill*5)/100;
	}

	if(sd->matk_rate != 100) {
		sd->matk1 = sd->matk1*sd->matk_rate/100;
		sd->matk2 = sd->matk2*sd->matk_rate/100;
	}
	if(sd->matk1 < 1)
	 	sd->matk1 = 1;
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

	if(sd->status.hp > sd->status.max_hp)
		sd->status.hp = sd->status.max_hp;
	if(sd->status.sp > sd->status.max_sp)
		sd->status.sp = sd->status.max_sp;

	// bTigereyeがなくなっていたらパケット送って元に戻す
	if(b_tigereye == 1 && sd->special_state.infinite_tigereye == 0 && sd->sc.data[SC_TIGEREYE].timer == -1)
		clif_status_load(sd, SI_TIGEREYE, 0);

	// 計算処理ここまで
	if( sd->status_calc_pc_process > 1 ) {
		// この関数が再帰的に呼ばれたので、再計算する
		if( --calclimit ) {
			sd->status_calc_pc_process = 1;
			goto L_RECALC;
		} else {
			// 無限ループになったので計算打ち切り
			printf("status_calc_pc: infinity loop!\n");
		}
	}
	sd->status_calc_pc_process = 0;

	if(first&4)
		return 0;
	if(first&3) {
		clif_updatestatus(sd,SP_SPEED);
		clif_updatestatus(sd,SP_MAXHP);
		clif_updatestatus(sd,SP_MAXSP);
		if(first&1) {
			clif_updatestatus(sd,SP_HP);
			clif_updatestatus(sd,SP_SP);
		}
		return 0;
	}

	if(b_class != sd->view_class) {
		clif_changelook(&sd->bl,LOOK_BASE,sd->view_class);
#if PACKETVER < 4
		clif_changelook(&sd->bl,LOOK_WEAPON,sd->status.weapon);
		clif_changelook(&sd->bl,LOOK_SHIELD,sd->status.shield);
#else
		clif_changelook(&sd->bl,LOOK_WEAPON,0);
#endif
	}

	if( memcmp(b_skill,sd->status.skill,sizeof(sd->status.skill)) || b_attackrange != sd->attackrange ) {
		int type;
		for(i=0; i<MAX_SKILL; i++) {
			// カードスキルをロストしたとき即時発動型なら状態異常を解除
			if(b_skill[i].flag == 1 && b_skill[i].lv > 0 && sd->status.skill[i].lv <= 0 && skill_get_inf(i) & 0x04) {
				type = GetSkillStatusChangeTable(i);
				if(type >= 0 && sd->sc.data[type].timer != -1)
					status_change_end(&sd->bl, type, -1);
			}
		}
		clif_skillinfoblock(sd);	// スキル送信
	}

	if(b_speed != sd->speed)
		clif_updatestatus(sd,SP_SPEED);
	if(b_weight != sd->weight)
		clif_updatestatus(sd,SP_WEIGHT);
	if(b_max_weight != sd->max_weight) {
		clif_updatestatus(sd,SP_MAXWEIGHT);
		pc_checkweighticon(sd);
	}

	for(i=0; i<6; i++) {
		if(b_paramb[i] + b_parame[i] != sd->paramb[i] + sd->parame[i])
			clif_updatestatus(sd,SP_STR+i);
	}

	if(b_hit != sd->hit)
		clif_updatestatus(sd,SP_HIT);
	if(b_flee != sd->flee)
		clif_updatestatus(sd,SP_FLEE1);
	if(b_aspd != sd->aspd)
		clif_updatestatus(sd,SP_ASPD);
	if(b_watk != sd->watk || b_base_atk != sd->base_atk)
		clif_updatestatus(sd,SP_ATK1);
	if(b_def != sd->def)
		clif_updatestatus(sd,SP_DEF1);
	if(b_watk2 != sd->watk2)
		clif_updatestatus(sd,SP_ATK2);
	if(b_def2 != sd->def2)
		clif_updatestatus(sd,SP_DEF2);
	if(b_flee2 != sd->flee2)
		clif_updatestatus(sd,SP_FLEE2);
	if(b_critical != sd->critical)
		clif_updatestatus(sd,SP_CRITICAL);
	if(b_matk1 != sd->matk1)
		clif_updatestatus(sd,SP_MATK1);
	if(b_matk2 != sd->matk2)
		clif_updatestatus(sd,SP_MATK2);
	if(b_mdef != sd->mdef)
		clif_updatestatus(sd,SP_MDEF1);
	if(b_mdef2 != sd->mdef2)
		clif_updatestatus(sd,SP_MDEF2);
	if(b_attackrange != sd->attackrange)
		clif_updatestatus(sd,SP_ATTACKRANGE);
	if(b_max_hp != sd->status.max_hp)
		clif_updatestatus(sd,SP_MAXHP);
	if(b_max_sp != sd->status.max_sp)
		clif_updatestatus(sd,SP_MAXSP);
	if(b_hp != sd->status.hp)
		clif_updatestatus(sd,SP_HP);
	if(b_sp != sd->status.sp)
		clif_updatestatus(sd,SP_SP);
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
 * 対象のgroupを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_group(struct block_list *bl)
{
	nullpo_retr(0, bl);

	if(bl->type == BL_MOB && (struct mob_data *)bl)
		return mob_db[((struct mob_data *)bl)->class_].group_id;
	// PC PETは0（未設定)

	return 0;
}

/*==========================================
 * 対象のClassを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_class(struct block_list *bl)
{
	nullpo_retr(0, bl);

	if(bl->type == BL_MOB && (struct mob_data *)bl)
		return ((struct mob_data *)bl)->class_;
	else if(bl->type == BL_PC && (struct map_session_data *)bl)
		return ((struct map_session_data *)bl)->status.class_;
	else if(bl->type == BL_PET && (struct pet_data *)bl)
		return ((struct pet_data *)bl)->class_;
	else if(bl->type == BL_HOM && (struct homun_data *)bl)
		return ((struct homun_data *)bl)->status.class_;
	else if(bl->type == BL_MERC && (struct merc_data *)bl)
		return ((struct merc_data *)bl)->status.class_;

	return 0;
}

/*==========================================
 * 対象の方向を返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_dir(struct block_list *bl)
{
	nullpo_retr(0, bl);

	if(bl->type == BL_MOB && (struct mob_data *)bl)
		return ((struct mob_data *)bl)->dir;
	else if(bl->type == BL_PC && (struct map_session_data *)bl)
		return ((struct map_session_data *)bl)->dir;
	else if(bl->type == BL_PET && (struct pet_data *)bl)
		return ((struct pet_data *)bl)->dir;
	else if(bl->type == BL_HOM && (struct homun_data *)bl)
		return ((struct homun_data *)bl)->dir;
	else if(bl->type == BL_MERC && (struct merc_data *)bl)
		return ((struct merc_data *)bl)->dir;

	return 0;
}

/*==========================================
 * 対象のレベルを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_lv(struct block_list *bl)
{
	nullpo_retr(0, bl);

	if(bl->type == BL_MOB && (struct mob_data *)bl)
		return mob_db[((struct mob_data *)bl)->class_].lv;
	else if(bl->type == BL_PC && (struct map_session_data *)bl)
		return ((struct map_session_data *)bl)->status.base_level;
	else if(bl->type == BL_PET && (struct pet_data *)bl)
		return ((struct pet_data *)bl)->msd->pet.level;
	else if(bl->type == BL_HOM && (struct homun_data *)bl)
		return ((struct homun_data *)bl)->status.base_level;
	else if(bl->type == BL_MERC && (struct merc_data *)bl)
		return ((struct merc_data *)bl)->status.base_level;

	return 0;
}

/*==========================================
 * 対象の射程を返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_range(struct block_list *bl)
{
	nullpo_retr(0, bl);

	if(bl->type == BL_MOB && (struct mob_data *)bl)
		return mob_db[((struct mob_data *)bl)->class_].range;
	else if(bl->type == BL_PC && (struct map_session_data *)bl)
		return ((struct map_session_data *)bl)->attackrange;
	else if(bl->type == BL_PET && (struct pet_data *)bl)
		return mob_db[((struct pet_data *)bl)->class_].range;
	else if(bl->type == BL_HOM && (struct homun_data *)bl)
		return 2;//((struct homun_data *)bl)->attackrange;
	else if(bl->type == BL_MERC && (struct merc_data *)bl)
		return ((struct merc_data *)bl)->attackrange;

	return 0;
}

/*==========================================
 * 対象のHPを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_hp(struct block_list *bl)
{
	nullpo_retr(1, bl);

	if(bl->type == BL_MOB && (struct mob_data *)bl)
		return ((struct mob_data *)bl)->hp;
	else if(bl->type == BL_PC && (struct map_session_data *)bl)
		return ((struct map_session_data *)bl)->status.hp;
	else if(bl->type == BL_HOM && (struct homun_data *)bl)
		return ((struct homun_data *)bl)->status.hp;
	else if(bl->type == BL_MERC && (struct merc_data *)bl)
		return ((struct merc_data *)bl)->status.hp;

	return 1;
}

/*==========================================
 * 対象のSPを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_sp(struct block_list *bl)
{
	nullpo_retr(1, bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl)
		return ((struct map_session_data *)bl)->status.sp;
	else if(bl->type == BL_HOM && (struct homun_data *)bl)
		return ((struct homun_data *)bl)->status.sp;
	else if(bl->type == BL_MERC && (struct merc_data *)bl)
		return ((struct merc_data *)bl)->status.sp;

	return 0;
}

/*==========================================
 * 対象のMHPを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_max_hp(struct block_list *bl)
{
	int max_hp = 1;

	nullpo_retr(1, bl);

	if(bl->type == BL_PC && ((struct map_session_data *)bl)) {
		max_hp = ((struct map_session_data *)bl)->status.max_hp;
	} else if(bl->type == BL_HOM && ((struct homun_data *)bl)) {
		max_hp = ((struct homun_data *)bl)->max_hp;
	} else if(bl->type == BL_MERC && ((struct merc_data *)bl)) {
		max_hp = ((struct merc_data *)bl)->max_hp;
	} else {
		struct status_change *sc = status_get_sc(bl);

		if(bl->type == BL_MOB && ((struct mob_data*)bl)) {
			max_hp = mob_db[((struct mob_data*)bl)->class_].max_hp;
			if(mob_db[((struct mob_data*)bl)->class_].mexp > 0) {
				if(battle_config.mvp_hp_rate != 100) {
					atn_bignumber hp = (atn_bignumber)max_hp * battle_config.mvp_hp_rate / 100;
					max_hp = (hp > 0x7FFFFFFF ? 0x7FFFFFFF : (int)hp);
				}
			} else {
				if(battle_config.monster_hp_rate != 100)
					max_hp = (max_hp * battle_config.monster_hp_rate)/100;
			}
		} else if(bl->type == BL_PET && ((struct pet_data*)bl)) {
			max_hp = mob_db[((struct pet_data*)bl)->class_].max_hp;
			if(mob_db[((struct pet_data*)bl)->class_].mexp > 0) {
				if(battle_config.mvp_hp_rate != 100) {
					atn_bignumber hp = (atn_bignumber)max_hp * battle_config.mvp_hp_rate / 100;
					max_hp = (hp > 0x7FFFFFFF ? 0x7FFFFFFF : (int)hp);
				}
			} else {
				if(battle_config.monster_hp_rate != 100)
					max_hp = (max_hp * battle_config.monster_hp_rate)/100;
			}
		}
		if(sc) {
			if(sc->data[SC_APPLEIDUN].timer != -1)
				max_hp += ((5+sc->data[SC_APPLEIDUN].val1*2+((sc->data[SC_APPLEIDUN].val2+1)>>1)
						+sc->data[SC_APPLEIDUN].val3/10) * max_hp)/100;
		}
		if(max_hp < 1) max_hp = 1;
	}

	return max_hp;
}

/*==========================================
 * 対象のStrを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_str(struct block_list *bl)
{
	int str = 0;
	struct status_change *sc;

	nullpo_retr(0, bl);

	sc = status_get_sc(bl);
	if(bl->type == BL_MOB && ((struct mob_data *)bl))
		str = mob_db[((struct mob_data *)bl)->class_].str;
	else if(bl->type == BL_PC && ((struct map_session_data *)bl))
		return ((struct map_session_data *)bl)->paramc[0];
	else if(bl->type == BL_PET && ((struct pet_data *)bl))
		str = mob_db[((struct pet_data *)bl)->class_].str;
	else if(bl->type == BL_HOM && ((struct homun_data *)bl))
		str = ((struct homun_data *)bl)->status.str;
	else if(bl->type == BL_MERC && ((struct merc_data *)bl))
		str = ((struct merc_data *)bl)->status.str;

	if(sc && bl->type != BL_HOM) {
		if(sc->data[SC_LOUD].timer != -1 && sc->data[SC_QUAGMIRE].timer == -1 && bl->type != BL_PC)
			str += 4;
		if( sc->data[SC_BLESSING].timer != -1 && bl->type != BL_PC) {	// ブレッシング
			int race = status_get_race(bl);
			if(battle_check_undead(race,status_get_elem_type(bl)) || race == RCT_DEMON)
				str >>= 1;				// 悪魔/不死
			else
				str += sc->data[SC_BLESSING].val1;	// その他
		}
		if(sc->data[SC_TRUESIGHT].timer != -1 && bl->type != BL_PC)	// トゥルーサイト
			str += 5;
		if(sc->data[SC_CHASEWALK_STR].timer != -1)
			str += sc->data[SC_CHASEWALK_STR].val1;
	}
	if(str < 0) str = 0;
	return str;
}

/*==========================================
 * 対象のAgiを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_agi(struct block_list *bl)
{
	int agi = 0;
	struct status_change *sc;

	nullpo_retr(0, bl);

	sc = status_get_sc(bl);
	if(bl->type == BL_MOB && (struct mob_data *)bl)
		agi = mob_db[((struct mob_data *)bl)->class_].agi;
	else if(bl->type == BL_PC && (struct map_session_data *)bl)
		agi = ((struct map_session_data *)bl)->paramc[1];
	else if(bl->type == BL_PET && (struct pet_data *)bl)
		agi = mob_db[((struct pet_data *)bl)->class_].agi;
	else if(bl->type == BL_HOM && ((struct homun_data *)bl))
		agi = ((struct homun_data *)bl)->agi;
	else if(bl->type == BL_MERC && ((struct merc_data *)bl))
		agi = ((struct merc_data *)bl)->agi;

	if(sc && bl->type != BL_HOM) {
		if(sc->data[SC_INCFLEE].timer != -1 && bl->type != BL_PC)	// 速度強化
			agi *= 3;
		if(sc->data[SC_INCREASEAGI].timer != -1 && sc->data[SC_QUAGMIRE].timer == -1 && sc->data[SC_DONTFORGETME].timer == -1 && bl->type != BL_PC)	// 速度増加(PCはpc.cで)
			agi += 2+sc->data[SC_INCREASEAGI].val1;
		if(sc->data[SC_SUITON].timer != -1 && sc->data[SC_SUITON].val3 != 0 && bl->type != BL_PC)	// 水遁
			agi += sc->data[SC_SUITON].val3;
		if(sc->data[SC_CONCENTRATE].timer != -1 && sc->data[SC_QUAGMIRE].timer == -1 && bl->type != BL_PC)
			agi += agi*(2+sc->data[SC_CONCENTRATE].val1)/100;
		if(sc->data[SC_DECREASEAGI].timer != -1)	// 速度減少
			agi -= 2+sc->data[SC_DECREASEAGI].val1;
		if(sc->data[SC_QUAGMIRE].timer != -1)	// クァグマイア
			agi >>= 1;
		if(sc->data[SC_TRUESIGHT].timer != -1 && bl->type != BL_PC)	// トゥルーサイト
			agi += 5;
	}
	if(agi < 0) agi = 0;
	return agi;
}

/*==========================================
 * 対象のVitを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_vit(struct block_list *bl)
{
	int vit = 0;
	struct status_change *sc;

	nullpo_retr(0, bl);

	sc = status_get_sc(bl);
	if(bl->type == BL_MOB && (struct mob_data *)bl)
		vit = mob_db[((struct mob_data *)bl)->class_].vit;
	else if(bl->type == BL_PC && (struct map_session_data *)bl)
		vit = ((struct map_session_data *)bl)->paramc[2];
	else if(bl->type == BL_PET && (struct pet_data *)bl)
		vit = mob_db[((struct pet_data *)bl)->class_].vit;
	else if(bl->type == BL_HOM && ((struct homun_data *)bl))
		vit = ((struct homun_data *)bl)->vit;
	else if(bl->type == BL_MERC && ((struct merc_data *)bl))
		vit = ((struct merc_data *)bl)->vit;

	if(sc && bl->type != BL_HOM) {
		if(sc->data[SC_STRIPARMOR].timer != -1 && bl->type != BL_PC)
			vit = vit*60/100;
		if(sc->data[SC_TRUESIGHT].timer != -1 && bl->type != BL_PC)	// トゥルーサイト
			vit += 5;
	}

	if(vit < 0) vit = 0;
	return vit;
}

/*==========================================
 * 対象のIntを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_int(struct block_list *bl)
{
	int int_ = 0;
	struct status_change *sc;

	nullpo_retr(0, bl);

	sc = status_get_sc(bl);
	if(bl->type == BL_MOB && (struct mob_data *)bl)
		int_ = mob_db[((struct mob_data *)bl)->class_].int_;
	else if(bl->type == BL_PC && (struct map_session_data *)bl)
		int_ = ((struct map_session_data *)bl)->paramc[3];
	else if(bl->type == BL_PET && (struct pet_data *)bl)
		int_ = mob_db[((struct pet_data *)bl)->class_].int_;
	else if(bl->type == BL_HOM && ((struct homun_data *)bl))
		int_ = ((struct homun_data *)bl)->int_;
	else if(bl->type == BL_MERC && ((struct merc_data *)bl))
		int_ = ((struct merc_data *)bl)->int_;

	if(sc && bl->type != BL_HOM) {
		if(sc->data[SC_BLESSING].timer != -1 && bl->type != BL_PC) {	// ブレッシング
			int race = status_get_race(bl);
			if(battle_check_undead(race,status_get_elem_type(bl)) || race == RCT_DEMON)
				int_ >>= 1;	// 悪魔/不死
			else
				int_ += sc->data[SC_BLESSING].val1;	// その他
		}
		if(sc->data[SC_STRIPHELM].timer != -1 && bl->type != BL_PC)
			int_ = int_*90/100;
		if(sc->data[SC_TRUESIGHT].timer != -1 && bl->type != BL_PC)	// トゥルーサイト
			int_ += 5;
	}
	if(int_ < 0) int_ = 0;
	return int_;
}

/*==========================================
 * 対象のDexを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_dex(struct block_list *bl)
{
	int dex = 0;
	struct status_change *sc;

	nullpo_retr(0, bl);

	sc = status_get_sc(bl);
	if(bl->type == BL_MOB && (struct mob_data *)bl)
		dex = mob_db[((struct mob_data *)bl)->class_].dex;
	else if(bl->type == BL_PC && (struct map_session_data *)bl)
		dex = ((struct map_session_data *)bl)->paramc[4];
	else if(bl->type == BL_PET && (struct pet_data *)bl)
		dex = mob_db[((struct pet_data *)bl)->class_].dex;
	else if(bl->type == BL_HOM && ((struct homun_data *)bl))
		dex = ((struct homun_data *)bl)->dex;
	else if(bl->type == BL_MERC && ((struct merc_data *)bl))
		dex = ((struct merc_data *)bl)->dex;

	if(sc && bl->type != BL_HOM) {
		if(sc->data[SC_EXPLOSIONSPIRITS].timer != -1 && bl->type != BL_PC)
			dex *= 3;	// NPC爆裂波動
		if(sc->data[SC_CONCENTRATE].timer != -1 && sc->data[SC_QUAGMIRE].timer == -1 && bl->type != BL_PC)
			dex += dex*(2+sc->data[SC_CONCENTRATE].val1)/100;

		if(sc->data[SC_BLESSING].timer != -1 && bl->type != BL_PC) {	// ブレッシング
			int race = status_get_race(bl);
			if(battle_check_undead(race,status_get_elem_type(bl)) || race == RCT_DEMON)
				dex >>= 1;	// 悪魔/不死
			else
				dex += sc->data[SC_BLESSING].val1;	// その他
		}
		if(sc->data[SC_QUAGMIRE].timer != -1)	// クァグマイア
			dex >>= 1;
		if(sc->data[SC_TRUESIGHT].timer != -1 && bl->type != BL_PC)	// トゥルーサイト
			dex += 5;
	}
	if(dex < 0) dex = 0;
	return dex;
}

/*==========================================
 * 対象のLukを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_luk(struct block_list *bl)
{
	int luk = 0;
	struct status_change *sc;

	nullpo_retr(0, bl);

	sc = status_get_sc(bl);
	if(bl->type == BL_MOB && (struct mob_data *)bl)
		luk = mob_db[((struct mob_data *)bl)->class_].luk;
	else if(bl->type == BL_PC && (struct map_session_data *)bl)
		luk = ((struct map_session_data *)bl)->paramc[5];
	else if(bl->type == BL_PET && (struct pet_data *)bl)
		luk = mob_db[((struct pet_data *)bl)->class_].luk;
	else if(bl->type == BL_HOM && ((struct homun_data *)bl))
		luk = ((struct homun_data *)bl)->luk;
	else if(bl->type == BL_MERC && ((struct merc_data *)bl))
		luk = ((struct merc_data *)bl)->luk;

	if(sc && bl->type != BL_HOM) {
		if(sc->data[SC_GLORIA].timer != -1 && bl->type != BL_PC)	// グロリア(PCはpc.cで)
			luk += 30;
		if(sc->data[SC_CURSE].timer != -1 )		// 呪い
			luk = 0;
		if(sc->data[SC_TRUESIGHT].timer != -1 && bl->type != BL_PC)	// トゥルーサイト
			luk += 5;
	}
	if(luk < 0) luk = 0;
	return luk;
}

/*==========================================
 * 対象のFleeを返す
 * 戻りは整数で1以上
 *------------------------------------------
 */
int status_get_flee(struct block_list *bl)
{
	int flee = 1, target_count = 1;
	struct status_change *sc;

	nullpo_retr(1, bl);

	sc = status_get_sc(bl);
	if(bl->type == BL_PC && (struct map_session_data *)bl)
		flee = ((struct map_session_data *)bl)->flee;
	else if(bl->type == BL_HOM && ((struct homun_data *)bl))
		flee = ((struct homun_data *)bl)->flee;
	else if(bl->type == BL_MERC && ((struct merc_data *)bl))
		flee = ((struct merc_data *)bl)->flee;
	else
		flee = status_get_agi(bl) + status_get_lv(bl);

	if(sc && bl->type != BL_HOM) {
		if(sc->data[SC_WHISTLE].timer != -1 && bl->type != BL_PC)
			flee += flee*(sc->data[SC_WHISTLE].val1+sc->data[SC_WHISTLE].val2+(sc->data[SC_WHISTLE].val3>>16))/100;
		if(sc->data[SC_BLIND].timer != -1 && bl->type != BL_PC)
			flee -= flee*25/100;
		if(sc->data[SC_WINDWALK].timer != -1 && bl->type != BL_PC)		// ウィンドウォーク
			flee += flee*(sc->data[SC_WINDWALK].val2)/100;
		if(sc->data[SC_SPIDERWEB].timer != -1 && bl->type != BL_PC)	// スパイダーウェブ
			flee -= flee*50/100;
		if(sc->data[SC_THE_SUN].timer != -1 && bl->type != BL_PC)	// THE SUN
			flee = flee*80/100;
		if(sc->data[SC_GATLINGFEVER].timer != -1 && bl->type != BL_PC)	// ガトリングフィーバー
			flee -= sc->data[SC_GATLINGFEVER].val1*5;
		if(sc->data[SC_ADJUSTMENT].timer != -1 && bl->type != BL_PC)	// アジャストメント
			flee += 30;
	}

	// 回避率補正
	if(bl->type != BL_HOM)
		target_count = unit_counttargeted(bl,battle_config.agi_penalty_count_lv);

	if(battle_config.agi_penalty_type > 0 && target_count >= battle_config.agi_penalty_count) {
		// ペナルティ設定より対象が多い
		if(battle_config.agi_penalty_type == 1) {
			// 回避率がagi_penalty_num%ずつ減少
			int flee_rate = (target_count-(battle_config.agi_penalty_count-1)) * battle_config.agi_penalty_num;
			flee = flee * (100 - flee_rate) / 100;
		} else if(battle_config.agi_penalty_type == 2) {
			// 回避率がagi_penalty_num分減少
			flee -= (target_count - (battle_config.agi_penalty_count - 1))*battle_config.agi_penalty_num;
		}
	}
	// 対人MAPでの減少効果
	if(battle_config.gvg_flee_penalty & 1 && map[bl->m].flag.gvg) {
		flee = flee*(200 - battle_config.gvg_flee_rate)/100;	// 実際にGvGでFleeを減少
	}
	if(battle_config.gvg_flee_penalty & 2 && map[bl->m].flag.pvp) {
		flee = flee*(200 - battle_config.gvg_flee_rate)/100;	// 実際にPvPでFleeを減少
	}
	if(flee < 1) flee = 1;

	return flee;
}

/*==========================================
 * 対象のHitを返す
 * 戻りは整数で1以上
 *------------------------------------------
 */
int status_get_hit(struct block_list *bl)
{
	int hit = 1;

	nullpo_retr(1, bl);

	if(bl->type == BL_PC) {
		hit = ((struct map_session_data *)bl)->hit;
	} else if(bl->type == BL_HOM && ((struct homun_data *)bl)) {
		hit = ((struct homun_data *)bl)->hit;
	} else if(bl->type == BL_MERC && ((struct merc_data *)bl)) {
		hit = ((struct merc_data *)bl)->hit;
	} else {
		struct status_change *sc = status_get_sc(bl);

		hit = status_get_dex(bl) + status_get_lv(bl);
		if(sc) {
			if(sc->data[SC_HUMMING].timer != -1)
				hit += hit*(sc->data[SC_HUMMING].val1*2+sc->data[SC_HUMMING].val2 + sc->data[SC_HUMMING].val3)/100;
			if(sc->data[SC_TRUESIGHT].timer != -1)		// トゥルーサイト
				hit += 3*(sc->data[SC_TRUESIGHT].val1);
			if(sc->data[SC_CONCENTRATION].timer != -1)	// コンセントレーション
				hit += 10*(sc->data[SC_CONCENTRATION].val1);
			if(sc->data[SC_THE_SUN].timer != -1 && bl->type != BL_PC)
				hit = hit*80/100;
			if(sc->data[SC_ADJUSTMENT].timer != -1 && bl->type != BL_PC) // アジャストメント
				hit -= 30;
			if(sc->data[SC_INCREASING].timer != -1 && bl->type != BL_PC) // インクリーシングアキュアラシー
				hit += 20;
		}
		if(hit < 1) hit = 1;
	}
	return hit;
}

/*==========================================
 * 対象の完全回避を返す
 * 戻りは整数で1以上
 *------------------------------------------
 */
int status_get_flee2(struct block_list *bl)
{
	int flee2 = 1;
	struct status_change *sc;

	nullpo_retr(1, bl);

	sc = status_get_sc(bl);
	if(bl->type == BL_PC && (struct map_session_data *)bl) {
		flee2 = status_get_luk(bl) + 10;
		flee2 += ((struct map_session_data *)bl)->flee2 - (((struct map_session_data *)bl)->paramc[5] + 10);
	} else {
		flee2 = status_get_luk(bl)+1;
	}

	if(sc) {
		if(sc->data[SC_WHISTLE].timer != -1 && bl->type != BL_PC)
			flee2 += (sc->data[SC_WHISTLE].val1+sc->data[SC_WHISTLE].val2+(sc->data[SC_WHISTLE].val3&0xffff))*10;
	}
	if(flee2 < 1) flee2 = 1;
	return flee2;
}

/*==========================================
 * 対象のクリティカルを返す
 * 戻りは整数で1以上
 *------------------------------------------
 */
int status_get_critical(struct block_list *bl)
{
	int critical = 1;
	struct status_change *sc;

	nullpo_retr(1, bl);

	sc = status_get_sc(bl);
	if(bl->type == BL_PC && (struct map_session_data *)bl) {
		critical = status_get_luk(bl)*3 + 10;
		critical += ((struct map_session_data *)bl)->critical - ((((struct map_session_data *)bl)->paramc[5]*3) + 10);
	} else if(bl->type == BL_HOM && ((struct homun_data *)bl)) {
		critical = ((struct homun_data *)bl)->critical;
	} else if(bl->type == BL_MERC && ((struct merc_data *)bl)) {
		critical = ((struct merc_data *)bl)->critical;
	} else {
		critical = status_get_luk(bl)*3 + 1;
	}

	if(sc) {
		if(sc->data[SC_FORTUNE].timer != -1 && bl->type != BL_PC)
			critical += (10+sc->data[SC_FORTUNE].val1+sc->data[SC_FORTUNE].val2+sc->data[SC_FORTUNE].val3)*10;
		if(sc->data[SC_EXPLOSIONSPIRITS].timer != -1 && bl->type != BL_PC)
			critical += sc->data[SC_EXPLOSIONSPIRITS].val2;
		if(sc->data[SC_TRUESIGHT].timer != -1 && bl->type != BL_PC)	// トゥルーサイト
			critical += 10*sc->data[SC_TRUESIGHT].val1;
	}
	if(critical < 1) critical = 1;
	return critical;
}

/*==========================================
 * base_atkの取得
 * 戻りは整数で1以上
 *------------------------------------------
 */
int status_get_baseatk(struct block_list *bl)
{
	struct status_change *sc;
	int batk = 1;

	nullpo_retr(1, bl);

	sc = status_get_sc(bl);

	if(bl->type == BL_PC) {
		struct map_session_data *sd = (struct map_session_data *)bl;
		if(sd) {
			batk = sd->base_atk;	// 設定されているbase_atk
			batk += sd->weapon_atk[sd->status.weapon];
		}
	} else if(bl->type == BL_HOM && ((struct homun_data *)bl)) {
		batk = 1;
	} else if(bl->type == BL_MERC && ((struct merc_data *)bl)) {
		batk = 1;
	} else {	// それ以外なら
		int str, dstr;
		str  = status_get_str(bl);	// STR
		dstr = str/10;
		batk = dstr*dstr + str;	// base_atkを計算する
	}
	if(sc) {	// 状態異常あり
		if(sc->data[SC_PROVOKE].timer != -1 && bl->type != BL_PC)	// PCでプロボック(SM_PROVOKE)状態
			batk = batk*(100+2*sc->data[SC_PROVOKE].val1)/100;	// base_atk増加
		if(sc->data[SC_CURSE].timer != -1)	// 呪われていたら
			batk -= batk*25/100;	// base_atkが25%減少
		if(sc->data[SC_CONCENTRATION].timer != -1 && bl->type != BL_PC)	// コンセントレーション
			batk += batk*(5*sc->data[SC_CONCENTRATION].val1)/100;
		if(sc->data[SC_JOINTBEAT].timer != -1 && sc->data[SC_JOINTBEAT].val4 == 4)	// ジョイントビートで腰
			batk -= batk*25/100;
		if(sc->data[SC_MADNESSCANCEL].timer != -1 && bl->type != BL_PC)	// マッドネスキャンセラー
			batk += 100;
		if(sc->data[SC_THE_MAGICIAN].timer != -1)
			batk = batk*50/100;
		if(sc->data[SC_THE_DEVIL].timer != -1)
			batk = batk*50/100;
		if(sc->data[SC_THE_SUN].timer != -1)
			batk = batk*80/100;
		if(sc->data[SC_SKE].timer != -1 && bl->type == BL_MOB)	// エスク
			batk *= 4;
	}
	if(batk < 1) batk = 1;	// base_atkは最低でも1
	return batk;
}

/*==========================================
 * 対象のAtkを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_atk(struct block_list *bl)
{
	struct status_change *sc;
	int atk = 0;

	nullpo_retr(0, bl);

	sc = status_get_sc(bl);
	if(bl->type == BL_PC && (struct map_session_data *)bl) {
		atk = ((struct map_session_data*)bl)->watk;
	} else if(bl->type == BL_HOM && ((struct homun_data *)bl)) {
		atk = ((struct homun_data *)bl)->atk-((struct homun_data *)bl)->atk/10;
	} else if(bl->type == BL_MERC && ((struct merc_data *)bl)) {
		atk = ((struct merc_data *)bl)->atk-((struct merc_data *)bl)->atk/10;
	} else if(bl->type == BL_MOB) {
		struct mob_data *md = (struct mob_data *)bl;
		if(md) {
			int guardup_lv = md->guardup_lv;
			atk = mob_db[md->class_].atk1;
			if(guardup_lv > 0)
				atk += 1000*guardup_lv;
		}
	} else if(bl->type == BL_PET && (struct pet_data *)bl) {
		atk = mob_db[((struct pet_data*)bl)->class_].atk1;
	}

	if(sc) {
		if(sc->data[SC_PROVOKE].timer != -1 && bl->type != BL_PC)
			atk = atk*(100+2*sc->data[SC_PROVOKE].val1)/100;
		if(sc->data[SC_CURSE].timer != -1)
			atk -= atk*25/100;
		if(sc->data[SC_CONCENTRATION].timer != -1 && bl->type != BL_PC)	// コンセントレーション
			atk += atk*(5*sc->data[SC_CONCENTRATION].val1)/100;
		if(sc->data[SC_EXPLOSIONSPIRITS].timer != -1 && bl->type != BL_PC)	// NPC爆裂波動
			atk *= 3;
		if(sc->data[SC_STRIPWEAPON].timer != -1 && bl->type != BL_PC)
			atk -= atk*25/100;
		if(sc->data[SC_DISARM].timer != -1 && bl->type != BL_PC)		// ディスアーム
			atk -= atk*25/100;
		if(sc->data[SC_MADNESSCANCEL].timer != -1 && bl->type != BL_PC)	// マッドネスキャンセラー
			atk += 100;
		if(sc->data[SC_THE_MAGICIAN].timer != -1 && bl->type != BL_PC)
			atk = atk*50/100;
		if(sc->data[SC_THE_DEVIL].timer != -1 && bl->type != BL_PC)
			atk = atk*50/100;
		if(sc->data[SC_THE_SUN].timer != -1 && bl->type != BL_PC)
			atk = atk*80/100;
		if(sc->data[SC_SKE].timer != -1 && bl->type == BL_MOB)		// エスク
			atk *= 4;
	}
	if(atk < 0) atk = 0;
	return atk;
}

/*==========================================
 * 対象の左手Atkを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_atk_(struct block_list *bl)
{
	struct map_session_data *sd = NULL;

	nullpo_retr(0, bl);

	if(bl->type == BL_PC && (sd = (struct map_session_data *)bl)) {
		int atk = sd->watk_;

		if(sd->sc.data[SC_CURSE].timer != -1)
			atk -= atk*25/100;
		return atk;
	}
	return 0;
}

/*==========================================
 * 対象のAtk2を返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_atk2(struct block_list *bl)
{
	int atk2 = 0;

	nullpo_retr(0, bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl) {
		atk2 = ((struct map_session_data*)bl)->watk2;
	} else if(bl->type == BL_HOM && (struct homun_data *)bl) {
		atk2 = ((struct homun_data *)bl)->atk;
	} else if(bl->type == BL_MERC && (struct merc_data *)bl) {
		atk2 = ((struct merc_data *)bl)->atk;
	} else {
		struct status_change *sc = status_get_sc(bl);

		if(bl->type == BL_MOB) {
			struct mob_data *md = (struct mob_data *)bl;
			if(md) {
				int guardup_lv = md->guardup_lv;
				atk2 = mob_db[md->class_].atk2;
				if(guardup_lv > 0)
					atk2 += 1000*guardup_lv;
			}
		} else if(bl->type == BL_PET && (struct pet_data *)bl) {
			atk2 = mob_db[((struct pet_data*)bl)->class_].atk2;
		}
		if(sc) {
			if(sc->data[SC_IMPOSITIO].timer != -1)
				atk2 += sc->data[SC_IMPOSITIO].val1*5;
			if(sc->data[SC_PROVOKE].timer != -1)
				atk2 = atk2*(100+2*sc->data[SC_PROVOKE].val1)/100;
			if(sc->data[SC_CURSE].timer != -1)
				atk2 -= atk2*25/100;
			if(sc->data[SC_DRUMBATTLE].timer != -1)
				atk2 += sc->data[SC_DRUMBATTLE].val2;
			if(sc->data[SC_NIBELUNGEN].timer != -1 && (status_get_element(bl)/10) >= 8 )
				atk2 += sc->data[SC_NIBELUNGEN].val2;
			if(sc->data[SC_STRIPWEAPON].timer != -1)
				atk2 -= atk2*10/100;
			if(sc->data[SC_CONCENTRATION].timer != -1)	// コンセントレーション
				atk2 += atk2*(5*sc->data[SC_CONCENTRATION].val1)/100;
			if(sc->data[SC_EXPLOSIONSPIRITS].timer != -1 && bl->type != BL_PC)	// NPC爆裂波動
				atk2 *= 3;
			if(sc->data[SC_DISARM].timer != -1 && bl->type != BL_PC)		// ディスアーム
				atk2 -= atk2*25/100;
			if(sc->data[SC_MADNESSCANCEL].timer != -1 && bl->type != BL_PC)	// マッドネスキャンセラー
				atk2 += 100;
			if(sc->data[SC_THE_MAGICIAN].timer != -1 && bl->type != BL_PC)
				atk2 = atk2*50/100;
			if(sc->data[SC_THE_DEVIL].timer != -1 && bl->type != BL_PC)
				atk2 = atk2*50/100;
			if(sc->data[SC_THE_SUN].timer != -1 && bl->type != BL_PC)
				atk2 = atk2*80/100;
			if(sc->data[SC_SKE].timer != -1 && bl->type == BL_MOB)		// エスク
				atk2 *= 4;
		}
		if(atk2 < 0) atk2 = 0;
	}
	return atk2;
}

/*==========================================
 * 対象の左手Atk2を返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_atk_2(struct block_list *bl)
{
	nullpo_retr(0, bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl)
		return ((struct map_session_data*)bl)->watk_2;

	return 0;
}

/*==========================================
 * 対象のMAtk1を返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_matk1(struct block_list *bl)
{
	int matk1 = 0;

	nullpo_retr(0, bl);

	if (bl->type == BL_PC) {
		matk1 = ((struct map_session_data *)bl)->matk1;
	} else if (bl->type == BL_HOM) {
		matk1 = ((struct homun_data *)bl)->matk-((struct homun_data *)bl)->matk/10;
	} else if (bl->type == BL_MERC) {
		matk1 = ((struct merc_data *)bl)->matk-((struct merc_data *)bl)->matk/10;
	} else if (bl->type != BL_PET && bl->type != BL_MOB) {
		matk1 = 0;
	} else {
		struct status_change *sc = status_get_sc(bl);
		int int_ = status_get_int(bl);

		matk1 = int_+(int_/5)*(int_/5);

		// MOBのmax_sp値をMATK補正値で乗っ取る時
		if(battle_config.mob_take_over_sp == 1) {
			if(bl->type == BL_MOB) {
				int b_class = status_get_class(bl);		// 直接maxsp取得無理の為ムリヤリ
				if(mob_db[b_class].max_sp > 0) {		// 1以上の時のみ
					matk1 = matk1 * (mob_db[b_class].max_sp/100);
				}
			}
		}

		if(sc) {
			if(sc->data[SC_MINDBREAKER].timer != -1)
				matk1 += (matk1*20*sc->data[SC_MINDBREAKER].val1)/100;
			if(sc->data[SC_STRENGTH].timer != -1)
				matk1 = matk1*50/100;
			if(sc->data[SC_THE_DEVIL].timer != -1)
				matk1 = matk1*50/100;
			if(sc->data[SC_THE_SUN].timer != -1)
				matk1 = matk1*80/100;
		}
	}
	return matk1;
}

/*==========================================
 * 対象のMAtk2を返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_matk2(struct block_list *bl)
{
	int matk2 = 0;

	nullpo_retr(0, bl);

	if (bl->type == BL_PC) {
		matk2 = ((struct map_session_data *)bl)->matk2;
	} else if (bl->type == BL_HOM) {
		matk2 = ((struct homun_data *)bl)->matk;
	} else if (bl->type == BL_MERC) {
		matk2 = ((struct merc_data *)bl)->matk;
	} else if (bl->type != BL_PET && bl->type != BL_MOB) {
		matk2 = 0;
	} else {
		struct status_change *sc = status_get_sc(bl);
		int int_ = status_get_int(bl);

		matk2 = int_+(int_/7)*(int_/7);

		// MOBのmax_sp値をMATK補正値で乗っ取る時
		if(battle_config.mob_take_over_sp == 1) {
			if(bl->type == BL_MOB) {
				int b_class = status_get_class(bl);		// 直接maxsp取得無理の為ムリヤリ
				if(mob_db[b_class].max_sp > 0) {		// 1以上の時のみ
					matk2 = matk2 * (mob_db[b_class].max_sp/100);
				}
			}
		}

		if(sc) {
			if(sc->data[SC_MINDBREAKER].timer != -1)
				matk2 += (matk2*20*sc->data[SC_MINDBREAKER].val1)/100;
			if(sc->data[SC_STRENGTH].timer != -1)
				matk2 = matk2*50/100;
			if(sc->data[SC_THE_DEVIL].timer != -1)
				matk2 = matk2*50/100;
			if(sc->data[SC_THE_SUN].timer != -1)
				matk2 = matk2*80/100;
		}
	}
	return matk2;
}

/*==========================================
 * 対象のDefを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_def(struct block_list *bl)
{
	struct unit_data *ud= NULL;
	struct status_change *sc;
	int def;

	nullpo_retr(0, bl);

	ud = unit_bl2ud(bl);
	sc = status_get_sc(bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl) {
		def = ((struct map_session_data *)bl)->def;
	} else if(bl->type == BL_MOB && (struct mob_data *)bl) {
		def = mob_db[((struct mob_data *)bl)->class_].def;
	} else if(bl->type == BL_PET && (struct pet_data *)bl) {
		def = mob_db[((struct pet_data *)bl)->class_].def;
	} else {
		def = 0;
	}

	if(def < 1000000) {
		if(sc) {
			// キーピング時はDEF100
			if(sc->data[SC_KEEPING].timer != -1)
				def *= 2;
			// プロボック時は減算
			if(sc->data[SC_PROVOKE].timer != -1 && bl->type != BL_PC)
				def = (def*(100 - 6*sc->data[SC_PROVOKE].val1)+50)/100;
			// 戦太鼓の響き時は加算
			if(sc->data[SC_DRUMBATTLE].timer != -1 && bl->type != BL_PC)
				def += sc->data[SC_DRUMBATTLE].val3;
			// 毒にかかっている時は減算
			if(sc->data[SC_POISON].timer != -1 && bl->type != BL_PC)
				def = def*75/100;
			// ストリップシールド時は減算
			if(sc->data[SC_STRIPSHIELD].timer != -1 && bl->type != BL_PC)
				def = def*85/100;
			// シグナムクルシス時は減算
			if(sc->data[SC_SIGNUMCRUCIS].timer != -1 && bl->type != BL_PC)
				def = def * (100 - sc->data[SC_SIGNUMCRUCIS].val2)/100;
			// 永遠の混沌時はPC以外DEFが0になる
			if(sc->data[SC_ETERNALCHAOS].timer != -1 && bl->type != BL_PC)
				def = 0;
			// 凍結、石化時は右シフト
			if(sc->data[SC_FREEZE].timer != -1 || (sc->data[SC_STONE].timer != -1 && sc->data[SC_STONE].val2 == 0))
				def >>= 1;
			// コンセントレーション時は減算
			if( sc->data[SC_CONCENTRATION].timer != -1 && bl->type != BL_PC)
				def = def * (100 - 5*sc->data[SC_CONCENTRATION].val1) / 100;
			// NPCディフェンダー
			if(sc->data[SC_NPC_DEFENDER].timer != -1 && bl->type != BL_PC)
				def += 100;
			// THE SUN
			if(sc->data[SC_THE_SUN].timer != -1 && bl->type != BL_PC)
				def = def*80/100;
			// フライング
			if(sc->data[SC_FLING].timer != -1 && bl->type != BL_PC)
				def = def * (100 - 5*sc->data[SC_FLING].val1)/100;
			// エスク
			if(sc->data[SC_SKE].timer != -1 && bl->type == BL_MOB)
				def = def/2;
			// ストーンスキン
			if(sc->data[SC_STONESKIN].timer != -1 && bl->type != BL_PC)
				def = def * (100 + 20 * sc->data[SC_STONESKIN].val1) / 100;
			// アンチマジック
			if(sc->data[SC_ANTIMAGIC].timer != -1 && bl->type != BL_PC)
				def = def * (100 - 20 * sc->data[SC_ANTIMAGIC].val1) / 100;
		}
		// 詠唱中は詠唱時減算率に基づいて減算
		if(ud && ud->skilltimer != -1) {
			int def_rate = skill_get_castdef(ud->skillid);
			if(def_rate != 0)
				def = (def * (100 - def_rate))/100;
		}
	}
	if(def < 0) def = 0;
	return def;
}

/*==========================================
 * 対象のMDefを返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_mdef(struct block_list *bl)
{
	struct status_change *sc;
	int mdef = 0;

	nullpo_retr(0, bl);

	sc = status_get_sc(bl);
	if(bl->type == BL_PC && (struct map_session_data *)bl)
		mdef = ((struct map_session_data *)bl)->mdef;
	else if(bl->type == BL_MOB && (struct mob_data *)bl)
		mdef = mob_db[((struct mob_data *)bl)->class_].mdef;
	else if(bl->type == BL_HOM && (struct homun_data *)bl)
		mdef = ((struct homun_data *)bl)->mdef;
	else if(bl->type == BL_MERC && (struct merc_data *)bl)
		mdef = ((struct merc_data *)bl)->mdef;
	else if(bl->type == BL_PET && (struct pet_data *)bl)
		mdef = mob_db[((struct pet_data *)bl)->class_].mdef;

	if(mdef < 1000000) {
		if(sc) {
			// バリアー状態時はMDEF100
			if(sc->data[SC_BARRIER].timer != -1)
				mdef += 100;
			// 凍結、石化時は1.25倍
			if(sc->data[SC_FREEZE].timer != -1 || (sc->data[SC_STONE].timer != -1 && sc->data[SC_STONE].val2 == 0))
				mdef = mdef*125/100;
			// ストーンスキン
			if(sc->data[SC_STONESKIN].timer != -1 && bl->type != BL_PC)
				mdef = mdef * (100 - 20 * sc->data[SC_STONESKIN].val1) / 100;
			// アンチマジック
			if(sc->data[SC_ANTIMAGIC].timer != -1 && bl->type != BL_PC)
				mdef = mdef * (100 + 20 * sc->data[SC_ANTIMAGIC].val1) / 100;
		}
	}
	if(mdef < 0) mdef = 0;
	return mdef;
}

/*==========================================
 * 対象のDef2を返す
 * 戻りは整数で1以上
 *------------------------------------------
 */
int status_get_def2(struct block_list *bl)
{
	struct status_change *sc;
	int def2 = 1;

	nullpo_retr(1, bl);

	sc = status_get_sc(bl);
	if(bl->type == BL_PC && (struct map_session_data *)bl)
		def2 = ((struct map_session_data *)bl)->def2;
	else if(bl->type == BL_MOB && (struct mob_data *)bl)
		def2 = mob_db[((struct mob_data *)bl)->class_].vit;
	else if(bl->type == BL_PET && (struct pet_data *)bl)
		def2 = mob_db[((struct pet_data *)bl)->class_].vit;
	else if(bl->type == BL_HOM && (struct homun_data *)bl)
		def2 = ((struct homun_data *)bl)->def;
	else if(bl->type == BL_MERC && (struct merc_data *)bl)
		def2 = ((struct merc_data *)bl)->def;

	if(sc) {
		if(sc->data[SC_ANGELUS].timer != -1 && bl->type != BL_PC)
			def2 = def2*(110+5*sc->data[SC_ANGELUS].val1)/100;
		if(sc->data[SC_PROVOKE].timer != -1 && bl->type != BL_PC)
			def2 = (def2*(100 - 6*sc->data[SC_PROVOKE].val1)+50)/100;
		if(sc->data[SC_POISON].timer != -1 && bl->type != BL_PC)
			def2 = def2*75/100;
		// コンセントレーション時は減算
		if( sc->data[SC_CONCENTRATION].timer != -1 && bl->type != BL_PC)
			def2 = def2*(100 - 5*sc->data[SC_CONCENTRATION].val1)/100;
		// ジョイントビート時なら減算
		if(sc->data[SC_JOINTBEAT].timer != -1) {
			if(sc->data[SC_JOINTBEAT].val4 == 3)	// 肩
				def2 -= def2*50/100;
			if(sc->data[SC_JOINTBEAT].val4 == 4)	// 腰
				def2 -= def2*25/100;
		}
		// 永遠の混沌時はDEF2が0になる
		if(sc->data[SC_ETERNALCHAOS].timer != -1)
			def2 = 0;
		// THE SUN
		if(sc->data[SC_THE_SUN].timer != -1 && bl->type != BL_PC)
			def2 = def2*80/100;
		// エスカ
		if(sc->data[SC_SKA].timer != -1 && bl->type == BL_MOB)
			def2 += 90;
	}
	if(def2 < 1) def2 = 1;
	return def2;
}

/*==========================================
 * 対象のMDef2を返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int status_get_mdef2(struct block_list *bl)
{
	struct status_change *sc;
	int mdef2 = 0;

	nullpo_retr(0, bl);

	sc = status_get_sc(bl);

	if(bl->type == BL_MOB && (struct mob_data *)bl)
		mdef2 = mob_db[((struct mob_data *)bl)->class_].int_ + (mob_db[((struct mob_data *)bl)->class_].vit>>1);
	else if(bl->type == BL_PC && (struct map_session_data *)bl)
		mdef2 = ((struct map_session_data *)bl)->mdef2 + (((struct map_session_data *)bl)->paramc[2]>>1);
	else if(bl->type == BL_PET && (struct pet_data *)bl)
		mdef2 = mob_db[((struct pet_data *)bl)->class_].int_ + (mob_db[((struct pet_data *)bl)->class_].vit>>1);
	else if (bl->type == BL_HOM && (struct homun_data *)bl)
		mdef2 = ((struct homun_data *)bl)->mdef;
	else if (bl->type == BL_MERC && (struct merc_data *)bl)
		mdef2 = ((struct merc_data *)bl)->mdef;

	if(sc) {
		// エスカ
		if(sc->data[SC_SKA].timer != -1 && bl->type == BL_MOB)
			mdef2 = 90;
		// マインドブレイカー
		if(sc->data[SC_MINDBREAKER].timer != -1 && bl->type != BL_PC)
			mdef2 -= (mdef2*12*sc->data[SC_MINDBREAKER].val1)/100;
	}
	return mdef2;
}

/*==========================================
 * 対象のSpeed(移動速度)を返す
 * 戻りは整数で1以上
 * Speedは小さいほうが移動速度が速い
 *------------------------------------------
 */
int status_get_speed(struct block_list *bl)
{
	int speed = 1000;

	nullpo_retr(1000, bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl) {
		speed = ((struct map_session_data *)bl)->speed;
	} else if(bl->type == BL_HOM && (struct homun_data *)bl) {
		if(battle_config.homun_speed_is_same_as_pc)
			speed = ((struct homun_data *)bl)->msd->speed;
		else
			speed = ((struct homun_data *)bl)->speed;
	} else if(bl->type == BL_MERC && (struct merc_data *)bl) {
		if(battle_config.merc_speed_is_same_as_pc)
			speed = ((struct merc_data *)bl)->msd->speed;
		else
			speed = ((struct merc_data *)bl)->speed;
	} else {
		struct status_change *sc = status_get_sc(bl);

		if(bl->type == BL_MOB && (struct mob_data *)bl)
			speed = ((struct mob_data *)bl)->speed;
		else if(bl->type == BL_PET && (struct pet_data *)bl)
			speed = ((struct pet_data *)bl)->speed;

		if(sc) {
			// 金剛時は35%加算
			if(sc->data[SC_STEELBODY].timer != -1)
				speed = speed*135/100;
			// 速度増加時は25%減算(金剛時は無効)
			else if(sc->data[SC_INCREASEAGI].timer != -1)
				speed -= speed*25/100;
			// ウィンドウォーク時はLv*2%減算(速度増加時は無効)
			else if(sc->data[SC_WINDWALK].timer != -1)
				speed -= (speed*(sc->data[SC_WINDWALK].val1*2))/100;
			// 速度強化時は50%減算
			if(sc->data[SC_INCFLEE].timer != -1 && bl->type != BL_PC)
				speed -= speed*50/100;
			// 速度減少時は33〜50%加算
			if(sc->data[SC_DECREASEAGI].timer != -1 && sc->data[SC_DEFENDER].timer == -1)	// ディフェンダー時は加算無し
				speed = speed*((sc->data[SC_DECREASEAGI].val1 > 5)? 150: 133)/100;
			// クァグマイア時は1/3加算
			if(sc->data[SC_QUAGMIRE].timer != -1)
				speed = speed*4/3;
			// 私を忘れないで…時は加算
			if(sc->data[SC_DONTFORGETME].timer != -1)
				speed = speed*(100+sc->data[SC_DONTFORGETME].val1*2 + sc->data[SC_DONTFORGETME].val2 + (sc->data[SC_DONTFORGETME].val3&0xffff))/100;
			// ディフェンダー時は加算
			if(sc->data[SC_DEFENDER].timer != -1)
				speed = (speed * (155 - sc->data[SC_DEFENDER].val1*5)) / 100;
			// 踊り中は4倍遅い
			if(sc->data[SC_DANCING].timer != -1)
				speed *= 4;
			// ジョイントビート時なら加算
			if(sc->data[SC_JOINTBEAT].timer != -1) {
				if(sc->data[SC_JOINTBEAT].val4 == 0)	// 足首
					speed += speed*50/100;
				if(sc->data[SC_JOINTBEAT].val4 == 2)	// 膝
					speed += speed*30/100;
			}
			// エスウは4倍遅い
			if(sc->data[SC_SWOO].timer != -1)
				speed *= 4;
			// グラビテーションフィールド
			if(sc->data[SC_GRAVITATION].timer != -1 && battle_config.enemy_gravitation_type)
				speed = speed*(100+sc->data[SC_GRAVITATION].val1*5)/100;
			// 呪い時は450加算（ディフェンダー時は速度低下無し）
			if(sc->data[SC_CURSE].timer != -1) {
				if(sc->data[SC_DEFENDER].timer == -1)
					speed += 450;
			}
			if(sc->data[SC_SUITON].timer != -1 && sc->data[SC_SUITON].val4 == 1)	// 水遁
				speed *= 2;
			// ガトリングフィーバー
			if(sc->data[SC_GATLINGFEVER].timer != -1 )
				speed = speed*135/100;
			//if(sc->data[SC_CURSE].timer != -1)
			//	speed = speed + 450;
		}
		if(speed < 1) speed = 1;
	}

	return speed;
}

/*==========================================
 * 対象のaDelay(攻撃時ディレイ)を返す
 * aDelayは小さいほうが攻撃速度が速い
 *------------------------------------------
 */
int status_get_adelay(struct block_list *bl)
{
	int adelay = 4000;

	nullpo_retr(4000, bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl) {
		adelay = (((struct map_session_data *)bl)->aspd<<1);
	} else {
		struct status_change *sc = status_get_sc(bl);
		int aspd_rate = 100, i;

		if(bl->type == BL_MOB && (struct mob_data *)bl) {
			int guardup_lv = ((struct mob_data*)bl)->guardup_lv;
			adelay = mob_db[((struct mob_data *)bl)->class_].adelay;

			if(guardup_lv > 0)
				aspd_rate -= 5 + 5*guardup_lv;
		} else if(bl->type == BL_PET && (struct pet_data *)bl) {
			adelay = mob_db[((struct pet_data *)bl)->class_].adelay;
		} else if(bl->type == BL_HOM && (struct homun_data *)bl) {
			adelay = (((struct homun_data *)bl)->aspd<<1);
		} else if(bl->type == BL_MERC && (struct merc_data *)bl) {
			adelay = (((struct merc_data *)bl)->aspd<<1);
		}

		if(sc) {
			// ツーハンドクイッケン使用時でクァグマイアでも私を忘れないで…でもない時は3割減算
			if(sc->data[SC_TWOHANDQUICKEN].timer != -1 && sc->data[SC_QUAGMIRE].timer == -1 && sc->data[SC_DONTFORGETME].timer == -1)	// 2HQ
				aspd_rate -= sc->data[SC_TWOHANDQUICKEN].val2;
			// ワンハンドクイッケン使用時でクァグマイアでも私を忘れないで…でもない時は3割減算
			if(sc->data[SC_ONEHAND].timer != -1 && sc->data[SC_QUAGMIRE].timer == -1 && sc->data[SC_DONTFORGETME].timer == -1)	// 1HQ
				aspd_rate -= 30;
			// アドレナリンラッシュ使用時でツーハンドクイッケンでもクァグマイアでも私を忘れないで…でもない時は
			if(sc->data[SC_ADRENALINE2].timer != -1 && sc->data[SC_TWOHANDQUICKEN].timer == -1 && sc->data[SC_ONEHAND].timer == -1 &&
				sc->data[SC_QUAGMIRE].timer == -1 && sc->data[SC_DONTFORGETME].timer == -1) {
				// 使用者とパーティメンバーで格差が出る設定でなければ3割減算
				if(sc->data[SC_ADRENALINE2].val2 || !battle_config.party_skill_penalty)
					aspd_rate -= 30;
				// そうでなければ2.5割減算
				else
					aspd_rate -= 25;
			} else if(sc->data[SC_ADRENALINE].timer != -1 && sc->data[SC_TWOHANDQUICKEN].timer == -1 && sc->data[SC_ONEHAND].timer == -1 &&
				sc->data[SC_QUAGMIRE].timer == -1 && sc->data[SC_DONTFORGETME].timer == -1) {	// アドレナリンラッシュ
				// 使用者とパーティメンバーで格差が出る設定でなければ3割減算
				if(sc->data[SC_ADRENALINE].val2 || !battle_config.party_skill_penalty)
					aspd_rate -= 30;
				// そうでなければ2.5割減算
				else
					aspd_rate -= 25;
			}
			// スピアクィッケン時は減算
			if(sc->data[SC_SPEARQUICKEN].timer != -1 && sc->data[SC_ADRENALINE].timer == -1 && sc->data[SC_ADRENALINE2].timer == -1 &&
				sc->data[SC_TWOHANDQUICKEN].timer == -1 && sc->data[SC_ONEHAND].timer == -1 &&
				sc->data[SC_QUAGMIRE].timer == -1 && sc->data[SC_DONTFORGETME].timer == -1)
				aspd_rate -= sc->data[SC_SPEARQUICKEN].val2;
			// 夕日のアサシンクロス時は減算
			if(sc->data[SC_ASSNCROS].timer != -1 &&
				sc->data[SC_TWOHANDQUICKEN].timer == -1 && sc->data[SC_ONEHAND].timer == -1 &&
				sc->data[SC_ADRENALINE].timer == -1 && sc->data[SC_ADRENALINE2].timer == -1 && sc->data[SC_SPEARQUICKEN].timer == -1 &&
				sc->data[SC_DONTFORGETME].timer == -1)
				aspd_rate -= 5+sc->data[SC_ASSNCROS].val1+sc->data[SC_ASSNCROS].val2+sc->data[SC_ASSNCROS].val3;
			// 私を忘れないで…時は加算
			if(sc->data[SC_DONTFORGETME].timer != -1)
				aspd_rate += sc->data[SC_DONTFORGETME].val1*3 + sc->data[SC_DONTFORGETME].val2 + (sc->data[SC_DONTFORGETME].val3>>16);
			// 金剛時25%加算
			if(sc->data[SC_STEELBODY].timer != -1)
				aspd_rate += 25;
			// 毒薬の瓶使用時は減算
			if(sc->data[SC_POISONPOTION].timer != -1)
				aspd_rate -= 25;
			// 増速ポーション使用時は減算
			if(sc->data[i = SC_SPEEDPOTION2].timer != -1 || sc->data[i = SC_SPEEDPOTION1].timer != -1 || sc->data[i = SC_SPEEDPOTION0].timer != -1)
				aspd_rate -= sc->data[i].val2;
			// ディフェンダー時は加算aspd_rateに変更&マスター時加算0に
			if(sc->data[SC_DEFENDER].timer != -1)
				aspd_rate += (25 - sc->data[SC_DEFENDER].val1*5);
			// ジョイントビート時なら加算
			if(sc->data[SC_JOINTBEAT].timer != 1) {
				if(sc->data[SC_JOINTBEAT].val4 == 1)	// 手首
					aspd_rate += aspd_rate*25/100;
				if(sc->data[SC_JOINTBEAT].val4 == 2)	// 膝
					aspd_rate += aspd_rate*10/100;
			}
			// グラビテーション
			if(sc->data[SC_GRAVITATION].timer != -1)
				aspd_rate += sc->data[SC_GRAVITATION].val1*5;
			// ガトリングフィーバー
			if(sc->data[SC_GATLINGFEVER].timer != -1)
				aspd_rate -= sc->data[SC_GATLINGFEVER].val1*2;
		}

		if(aspd_rate != 100)
			adelay = adelay*aspd_rate/100;
		if(adelay < battle_config.monster_max_aspd<<1)
			adelay = battle_config.monster_max_aspd<<1;
	}
	return adelay;
}

/*==========================================
 * 対象のamotionを返す
 *------------------------------------------
 */
int status_get_amotion(struct block_list *bl)
{
	int amotion = 2000;

	nullpo_retr(2000, bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl) {
		amotion = ((struct map_session_data *)bl)->amotion;
	} else {
		struct status_change *sc = status_get_sc(bl);
		int aspd_rate = 100, i;

		if(bl->type == BL_MOB && (struct mob_data *)bl) {
			int guardup_lv = ((struct mob_data*)bl)->guardup_lv;
			amotion = mob_db[((struct mob_data *)bl)->class_].amotion;
			if(guardup_lv > 0)
				aspd_rate -= 5 + 5*guardup_lv;
		} else if(bl->type == BL_PET && (struct pet_data *)bl) {
			amotion = mob_db[((struct pet_data *)bl)->class_].amotion;
		} else if(bl->type == BL_HOM && (struct homun_data *)bl && ((struct homun_data *)bl)->msd) {
			amotion = ((struct homun_data *)bl)->aspd;
		} else if(bl->type == BL_MERC && (struct merc_data *)bl && ((struct merc_data *)bl)->msd) {
			amotion = ((struct merc_data *)bl)->aspd;
		}

		if(sc) {
			if(sc->data[SC_TWOHANDQUICKEN].timer != -1 && sc->data[SC_QUAGMIRE].timer == -1 && sc->data[SC_DONTFORGETME].timer == -1)	// 2HQ
				aspd_rate -= sc->data[SC_TWOHANDQUICKEN].val2;
			if(sc->data[SC_ONEHAND].timer != -1 && sc->data[SC_QUAGMIRE].timer == -1 && sc->data[SC_DONTFORGETME].timer == -1)	// 1HQ
				aspd_rate -= 30;

			if(sc->data[SC_ADRENALINE2].timer != -1 && sc->data[SC_TWOHANDQUICKEN].timer == -1 &&
				sc->data[SC_ONEHAND].timer == -1 && sc->data[SC_QUAGMIRE].timer == -1 && sc->data[SC_DONTFORGETME].timer == -1) {	// フルアドレナリンラッシ
				if(sc->data[SC_ADRENALINE2].val2 || !battle_config.party_skill_penalty)
					aspd_rate -= 30;
				else
					aspd_rate -= 25;
			}else if(sc->data[SC_ADRENALINE].timer != -1 && sc->data[SC_TWOHANDQUICKEN].timer == -1 &&
				sc->data[SC_ONEHAND].timer == -1 && sc->data[SC_QUAGMIRE].timer == -1 && sc->data[SC_DONTFORGETME].timer == -1) {	// アドレナリンラッシュ
				if(sc->data[SC_ADRENALINE].val2 || !battle_config.party_skill_penalty)
					aspd_rate -= 30;
				else
					aspd_rate -= 25;
			}
			if(sc->data[SC_SPEARQUICKEN].timer != -1 && sc->data[SC_ADRENALINE].timer == -1 && sc->data[SC_ADRENALINE2].timer == -1 &&
				sc->data[SC_TWOHANDQUICKEN].timer == -1 && sc->data[SC_ONEHAND].timer == -1 &&
				sc->data[SC_QUAGMIRE].timer == -1 && sc->data[SC_DONTFORGETME].timer == -1)	// スピアクィッケン
				aspd_rate -= sc->data[SC_SPEARQUICKEN].val2;
			if(sc->data[SC_ASSNCROS].timer != -1 && // 夕陽のアサシンクロス
				sc->data[SC_TWOHANDQUICKEN].timer == -1 && sc->data[SC_ONEHAND].timer == -1 &&
				sc->data[SC_ADRENALINE].timer == -1 && sc->data[SC_ADRENALINE2].timer == -1 && sc->data[SC_SPEARQUICKEN].timer == -1 &&
				sc->data[SC_DONTFORGETME].timer == -1)
				aspd_rate -= 5+sc->data[SC_ASSNCROS].val1+sc->data[SC_ASSNCROS].val2+sc->data[SC_ASSNCROS].val3;
			if(sc->data[SC_DONTFORGETME].timer != -1)		// 私を忘れないで
				aspd_rate += sc->data[SC_DONTFORGETME].val1*3 + sc->data[SC_DONTFORGETME].val2 + (sc->data[SC_DONTFORGETME].val3>>16);
			if(sc->data[SC_POISONPOTION].timer != -1)
				aspd_rate -= 25;
			if(sc->data[SC_STEELBODY].timer != -1)	// 金剛
				aspd_rate += 25;
			if(sc->data[i = SC_SPEEDPOTION2].timer != -1 || sc->data[i = SC_SPEEDPOTION1].timer != -1 || sc->data[i = SC_SPEEDPOTION0].timer != -1)
				aspd_rate -= sc->data[i].val2;
			// ディフェンダー時は加算ASPDに変更&マスター時加算0に
			if(sc->data[SC_DEFENDER].timer != -1)
				aspd_rate += (25 - sc->data[SC_DEFENDER].val1*5);
			// ジョイントビート時なら加算
			if(sc->data[SC_JOINTBEAT].timer != 1) {
				if(sc->data[SC_JOINTBEAT].val4 == 1)	// 手首
					aspd_rate += aspd_rate*25/100;
				if(sc->data[SC_JOINTBEAT].val4 == 2)	// 膝
					aspd_rate += aspd_rate*10/100;
			}
			if(sc->data[SC_GRAVITATION].timer != -1)
				aspd_rate += sc->data[SC_GRAVITATION].val1*5;
		}
		if(aspd_rate != 100)
			amotion = amotion*aspd_rate/100;
		if(amotion < battle_config.monster_max_aspd)
			amotion = battle_config.monster_max_aspd;
	}
	return amotion;
}

/*==========================================
 * 対象のdmotionを返す
 *------------------------------------------
 */
int status_get_dmotion(struct block_list *bl)
{
	int dmotion = 2000;

	nullpo_retr(2000, bl);

	if(bl->type == BL_MOB && (struct mob_data *)bl) {
		dmotion = mob_db[((struct mob_data *)bl)->class_].dmotion;
		if(battle_config.monster_damage_delay_rate != 100)
			dmotion = dmotion*battle_config.monster_damage_delay_rate/100;
	}
	else if(bl->type == BL_PC) {
		struct map_session_data *sd = (struct map_session_data *)bl;
		if(sd) {
			if(sd->sc.data[SC_ENDURE].timer != -1 && (!map[sd->bl.m].flag.gvg || sd->special_state.infinite_endure)) {
				dmotion = 0;
			} else {
				dmotion = sd->dmotion;
				if(battle_config.pc_damage_delay_rate != 100)
					dmotion = dmotion*battle_config.pc_damage_delay_rate/100;
			}
		}
	}
	else if(bl->type == BL_HOM && (struct homun_data *)bl && ((struct homun_data *)bl)->msd) {
		dmotion = 800 - ((struct homun_data *)bl)->status.agi*4;
		if(dmotion < 400)
			dmotion = 400;
	}
	else if(bl->type == BL_MERC && (struct merc_data *)bl && ((struct merc_data *)bl)->msd) {
		dmotion = 800 - ((struct merc_data *)bl)->status.agi*4;
		if(dmotion < 400)
			dmotion = 400;
	}
	else if(bl->type == BL_PET && (struct pet_data *)bl) {
		dmotion = mob_db[((struct pet_data *)bl)->class_].dmotion;
	}

	return dmotion;
}

/*==========================================
 * 対象の属性を返す
 *------------------------------------------
 */
int status_get_element(struct block_list *bl)
{
	int ret = 20;
	struct status_change *sc;

	nullpo_retr(ret, bl);

	sc = status_get_sc(bl);
	if(sc) {
		if(sc->data[SC_BENEDICTIO].timer != -1)		// 聖体降福
			ret = 20 + ELE_HOLY;
		if(sc->data[SC_ELEMENTWATER].timer != -1)	// 水
			ret = 20*sc->data[SC_ELEMENTWATER].val1 + ELE_WATER;
		if(sc->data[SC_ELEMENTGROUND].timer != -1)	// 土
			ret = 20*sc->data[SC_ELEMENTGROUND].val1 + ELE_EARTH;
		if(sc->data[SC_ELEMENTFIRE].timer != -1)		// 火
			ret = 20*sc->data[SC_ELEMENTFIRE].val1 + ELE_FIRE;
		if(sc->data[SC_ELEMENTWIND].timer != -1)		// 風
			ret = 20*sc->data[SC_ELEMENTWIND].val1 + ELE_WIND;
		if(sc->data[SC_ELEMENTPOISON].timer != -1)	// 毒
			ret = 20*sc->data[SC_ELEMENTPOISON].val1 + ELE_POISON;
		if(sc->data[SC_ELEMENTHOLY].timer != -1)		// 聖
			ret = 20*sc->data[SC_ELEMENTHOLY].val1 + ELE_HOLY;
		if(sc->data[SC_ELEMENTDARK].timer != -1)		// 闇
			ret = 20*sc->data[SC_ELEMENTDARK].val1 + ELE_DARK;
		if(sc->data[SC_ELEMENTELEKINESIS].timer != -1)	// 念
			ret = 20*sc->data[SC_ELEMENTELEKINESIS].val1 + ELE_GHOST;
		if(sc->data[SC_ELEMENTUNDEAD].timer != -1)	// 不死
			ret = 20*sc->data[SC_ELEMENTUNDEAD].val1 + ELE_UNDEAD;
		if(sc->data[SC_FREEZE].timer != -1)		// 凍結
			ret = 20 + ELE_WATER;
		if(sc->data[SC_STONE].timer != -1 && sc->data[SC_STONE].val2 == 0)
			ret = 20 + ELE_EARTH;

		if(ret != 20)
			return ret;
	}

	if(bl->type == BL_MOB && (struct mob_data *)bl)	// 10の位＝Lv*2、１の位＝属性
		ret = ((struct mob_data *)bl)->def_ele;
	else if(bl->type == BL_PC && (struct map_session_data *)bl)
		ret = 20+((struct map_session_data *)bl)->def_ele;	// 防御属性Lv1
	else if(bl->type == BL_PET && (struct pet_data *)bl)
		ret = mob_db[((struct pet_data *)bl)->class_].element;
	else if(bl->type == BL_HOM && (struct homun_data *)bl)
		ret = homun_db[((struct homun_data *)bl)->status.class_-HOM_ID].element;
	else if(bl->type == BL_MERC && (struct merc_data *)bl)
		ret = merc_db[((struct merc_data *)bl)->status.class_-MERC_ID].element;

	return ret;
}

/*==========================================
 * 対象の攻撃属性を返す
 *------------------------------------------
 */
int status_get_attack_element(struct block_list *bl)
{
	int ret = ELE_NEUTRAL;
	struct status_change *sc = NULL;

	nullpo_retr(ELE_NEUTRAL, bl);

	sc = status_get_sc(bl);
	if(bl->type == BL_MOB && (struct mob_data *)bl)
		ret = ELE_NEUTRAL;
	else if(bl->type == BL_PC && (struct map_session_data *)bl)
		ret = ((struct map_session_data *)bl)->atk_ele;
	else if(bl->type == BL_PET && (struct pet_data *)bl)
		ret = ELE_NEUTRAL;
	else if(bl->type == BL_HOM && (struct homun_data *)bl)
		ret = ELE_NONE;	// 無属性
	else if(bl->type == BL_MERC && (struct merc_data *)bl)
		ret = ELE_NONE;	// 無属性

	if(sc) {
		if(sc->data[SC_FROSTWEAPON].timer != -1)		// フロストウェポン
			ret = ELE_WATER;
		if(sc->data[SC_SEISMICWEAPON].timer != -1)	// サイズミックウェポン
			ret = ELE_EARTH;
		if(sc->data[SC_FLAMELAUNCHER].timer != -1)	// フレームランチャー
			ret = ELE_FIRE;
		if(sc->data[SC_LIGHTNINGLOADER].timer != -1)	// ライトニングローダー
			ret = ELE_WIND;
		if(sc->data[SC_ENCPOISON].timer != -1)		// エンチャントポイズン
			ret = ELE_POISON;
		if(sc->data[SC_ASPERSIO].timer != -1)		// アスペルシオ
			ret = ELE_HOLY;
		if(sc->data[SC_DARKELEMENT].timer != -1)		// 闇属性
			ret = ELE_DARK;
		if(sc->data[SC_ATTENELEMENT].timer != -1)	// 念属性
			ret = ELE_GHOST;
		if(sc->data[SC_UNDEADELEMENT].timer != -1)	// 不死属性
			ret = ELE_UNDEAD;
		if(sc->data[SC_SEVENWIND].timer != -1)		// 暖かい風
			ret = sc->data[SC_SEVENWIND].val3;
	}
	return ret;
}

/*==========================================
 * 対象の攻撃属性（左手）を返す
 *------------------------------------------
 */
int status_get_attack_element2(struct block_list *bl)
{
	nullpo_retr(ELE_NEUTRAL, bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl) {
		int ret = ((struct map_session_data *)bl)->atk_ele_;
		struct status_change *sc = status_get_sc(bl);

		if(sc) {
			if(sc->data[SC_FROSTWEAPON].timer != -1)		// フロストウェポン
				ret = ELE_WATER;
			if(sc->data[SC_SEISMICWEAPON].timer != -1)	// サイズミックウェポン
				ret = ELE_EARTH;
			if(sc->data[SC_FLAMELAUNCHER].timer != -1)	// フレームランチャー
				ret = ELE_FIRE;
			if(sc->data[SC_LIGHTNINGLOADER].timer != -1)	// ライトニングローダー
				ret = ELE_WIND;
			if(sc->data[SC_ENCPOISON].timer != -1)		// エンチャントポイズン
				ret = ELE_POISON;
			if(sc->data[SC_ASPERSIO].timer != -1)		// アスペルシオ
				ret = ELE_HOLY;
			if(sc->data[SC_DARKELEMENT].timer != -1)		// 闇属性
				ret = ELE_DARK;
			if(sc->data[SC_ATTENELEMENT].timer != -1)	// 念属性
				ret = ELE_GHOST;
			if(sc->data[SC_UNDEADELEMENT].timer != -1)	// 不死属性
				ret = ELE_UNDEAD;
			if(sc->data[SC_SEVENWIND].timer != -1)		// 暖かい風
				ret = sc->data[SC_SEVENWIND].val3;
		}
		return ret;
	}
	return ELE_NEUTRAL;
}

/*==========================================
 * 対象の武器属性を除いた攻撃属性を返す
 *------------------------------------------
 */
int status_get_attack_element_nw(struct block_list *bl)
{
	int ret = ELE_NEUTRAL;
	struct status_change *sc = NULL;

	nullpo_retr(ELE_NEUTRAL, bl);

	sc = status_get_sc(bl);

	if(bl->type == BL_HOM && (struct homun_data *)bl)
		ret = ELE_NONE;	// 無属性
	else if(bl->type == BL_MERC && (struct merc_data *)bl)
		ret = ELE_NONE;	// 無属性

	if(sc) {
		if(sc->data[SC_FROSTWEAPON].timer != -1)		// フロストウェポン
			ret = ELE_WATER;
		if(sc->data[SC_SEISMICWEAPON].timer != -1)	// サイズミックウェポン
			ret = ELE_EARTH;
		if(sc->data[SC_FLAMELAUNCHER].timer != -1)	// フレームランチャー
			ret = ELE_FIRE;
		if(sc->data[SC_LIGHTNINGLOADER].timer != -1)	// ライトニングローダー
			ret = ELE_WIND;
		if(sc->data[SC_ENCPOISON].timer != -1)		// エンチャントポイズン
			ret = ELE_POISON;
		if(sc->data[SC_ASPERSIO].timer != -1)		// アスペルシオ
			ret = ELE_HOLY;
		if(sc->data[SC_DARKELEMENT].timer != -1)		// 闇属性
			ret = ELE_DARK;
		if(sc->data[SC_ATTENELEMENT].timer != -1)	// 念属性
			ret = ELE_GHOST;
		if(sc->data[SC_UNDEADELEMENT].timer != -1)	// 不死属性
			ret = ELE_UNDEAD;
		if(sc->data[SC_SEVENWIND].timer != -1)		// 暖かい風
			ret = sc->data[SC_SEVENWIND].val3;
	}
	return ret;
}

/*==========================================
 * 対象のパーティIDを返す
 *------------------------------------------
 */
int status_get_party_id(struct block_list *bl)
{
	nullpo_retr(0, bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl) {
		return ((struct map_session_data *)bl)->status.party_id;
	}
	else if(bl->type == BL_MOB && (struct mob_data *)bl) {
		struct mob_data *md = (struct mob_data *)bl;
		return (md->master_id > 0)? -md->master_id: -md->bl.id;
	}
	else if(bl->type == BL_HOM && (struct homun_data *)bl) {
		//struct homun_data *hd = (struct homun_data *)bl;
		//return status_get_party_id(&hd->msd->bl);
		return 0;
	}
	else if(bl->type == BL_MERC && (struct merc_data *)bl) {
		//struct merc_data *mcd = (struct merc_data *)bl;
		//return status_get_party_id(&mcd->msd->bl);
		return 0;
	}
	else if(bl->type == BL_SKILL && (struct skill_unit *)bl) {
		return ((struct skill_unit *)bl)->group->party_id;
	}

	return 0;
}

/*==========================================
 * 対象のギルドIDを返す
 *------------------------------------------
 */
int status_get_guild_id(struct block_list *bl)
{
	nullpo_retr(0, bl);

	if(bl->type == BL_PC && (struct map_session_data *)bl) {
		return ((struct map_session_data *)bl)->status.guild_id;
	} else if(bl->type == BL_MOB && (struct mob_data *)bl) {
		return ((struct mob_data *)bl)->class_;
	} else if(bl->type == BL_HOM && (struct homun_data *)bl) {
		//struct homun_data *hd = (struct homun_data *)bl;
		//return status_get_guild_id(&hd->msd->bl);
		return 0;
	} else if(bl->type == BL_MERC && (struct merc_data *)bl) {
		//struct merc_data *mcd = (struct merc_data *)bl;
		//return status_get_guild_id(&mcd->msd->bl);
		return 0;
	} else if(bl->type == BL_SKILL && (struct skill_unit *)bl) {
		return ((struct skill_unit *)bl)->group->guild_id;
	}

	return 0;
}

/*==========================================
 * 対象の種族を返す
 *------------------------------------------
 */
int status_get_race(struct block_list *bl)
{
	int race;
	struct status_change *sc;

	nullpo_retr(RCT_FORMLESS, bl);

	if(bl->type == BL_MOB && (struct mob_data *)bl)
		race = mob_db[((struct mob_data *)bl)->class_].race;
	else if(bl->type == BL_PC && (struct map_session_data *)bl)
		race = ((struct map_session_data *)bl)->race;
	else if(bl->type == BL_PET && (struct pet_data *)bl)
		return mob_db[((struct pet_data *)bl)->class_].race;
	else if(bl->type == BL_HOM && (struct homun_data *)bl)
		return homun_db[((struct homun_data *)bl)->status.class_-HOM_ID].race;
	else if(bl->type == BL_MERC && (struct merc_data *)bl)
		return merc_db[((struct merc_data *)bl)->status.class_-MERC_ID].race;
	else
		return RCT_FORMLESS;

	sc = status_get_sc(bl);

	if(sc) {
		if(sc->data[SC_RACEUNKNOWN].timer != -1)	// 無形
			race = RCT_FORMLESS;
		if(sc->data[SC_RACEUNDEAD].timer != -1)	// 不死
			race = RCT_UNDEAD;
		if(sc->data[SC_RACEBEAST].timer != -1)	// 動物
			race = RCT_BRUTE;
		if(sc->data[SC_RACEPLANT].timer != -1)	// 植物
			race = RCT_PLANT;
		if(sc->data[SC_RACEINSECT].timer != -1)	// 昆虫
			race = RCT_INSECT;
		if(sc->data[SC_RACEFISH].timer != -1)	// 魚貝
			race = RCT_FISH;
		if(sc->data[SC_RACEDEVIL].timer != -1)	// 悪魔
			race = RCT_DEMON;
		if(sc->data[SC_RACEHUMAN].timer != -1)	// 人間
			race = RCT_HUMAN;
		if(sc->data[SC_RACEANGEL].timer != -1)	// 天使
			race = RCT_ANGEL;
		if(sc->data[SC_RACEDRAGON].timer != -1)	// 竜
			race = RCT_DRAGON;
	}

	return race;
}

/*==========================================
 * 対象のサイズを返す
 *------------------------------------------
 */
int status_get_size(struct block_list *bl)
{
	nullpo_retr(1, bl);

	if(bl->type == BL_MOB && (struct mob_data *)bl) {
		return mob_db[((struct mob_data *)bl)->class_].size;
	} else if(bl->type == BL_PC && (struct map_session_data *)bl) {
		if(pc_isbaby((struct map_session_data *)bl))
			return 0;
		else
			return 1;
	} else if(bl->type == BL_PET && (struct pet_data *)bl) {
		return mob_db[((struct pet_data *)bl)->class_].size;
	} else if(bl->type == BL_HOM && (struct homun_data *)bl) {
		return homun_db[((struct homun_data *)bl)->status.class_-HOM_ID].size;
	} else if(bl->type == BL_MERC && (struct merc_data *)bl) {
		return merc_db[((struct merc_data *)bl)->status.class_-MERC_ID].size;
	}

	return 1;
}

/*==========================================
 * 対象のモードを返す
 *------------------------------------------
 */
int status_get_mode(struct block_list *bl)
{
	nullpo_retr(0x01, bl);

	if(bl->type == BL_MOB) {
		struct mob_data* md = (struct mob_data*)bl;
		return (md->mode ? md->mode : mob_db[md->class_].mode);
	}
	else if(bl->type == BL_PET) {
		return mob_db[((struct pet_data *)bl)->class_].mode;
	}

	return 0x01;	// とりあえず動くということで1
}

/*==========================================
 * 対象のMVPExpを返す
 *------------------------------------------
 */
int status_get_mexp(struct block_list *bl)
{
	nullpo_retr(0, bl);

	if(bl->type == BL_MOB && (struct mob_data *)bl)
		return mob_db[((struct mob_data *)bl)->class_].mexp;
	else if(bl->type == BL_PET && (struct pet_data *)bl)
		return mob_db[((struct pet_data *)bl)->class_].mexp;

	return 0;
}

/*==========================================
 * 対象の敵タイプを返す
 *------------------------------------------
 */
int status_get_enemy_type(struct block_list *bl)
{
	nullpo_retr(0, bl);

	if( bl->type == BL_PC )
		return 1;
	else if( bl->type == BL_MOB && !(status_get_mode(bl)&0x20) )
		return 2;
	else if( bl->type == BL_HOM )
		return 3;
	else if( bl->type == BL_MERC )
		return 4;

	return 0;
}

/*==========================================
 * 対象の服色を返す
 *------------------------------------------
 */
short status_get_clothes_color(struct block_list *bl)
{
	short color = -1;

	nullpo_retr(-1, bl);

	if(bl->type == BL_PC) {
		color = ((struct map_session_data *)bl)->status.clothes_color;
	} else if(bl->type == BL_MOB || bl->type == BL_PET) {
		int id = status_get_class(bl);
		if(id >= 0 && mob_is_pcview(id))
			color = mob_get_clothes_color(id);
	}
	if(color >= 0 && color < MAX_CLOTH_COLOR)
		return color;

	return -1;
}

/*==========================================
 * StatusChangeの取得
 *------------------------------------------
 */
struct status_change *status_get_sc(struct block_list *bl)
{
	nullpo_retr(NULL, bl);

	if(bl->type == BL_MOB && (struct mob_data *)bl)
		return &((struct mob_data*)bl)->sc;
	if(bl->type == BL_PC && (struct map_session_data *)bl)
		return &((struct map_session_data*)bl)->sc;
	if(bl->type == BL_HOM && (struct homun_data *)bl)
		return &((struct homun_data*)bl)->sc;
	if(bl->type == BL_MERC && (struct merc_data *)bl)
		return &((struct merc_data*)bl)->sc;

	return NULL;
}

/*==========================================
 * 魔法無効かどうか
 *------------------------------------------
 */
int status_check_no_magic_damage(struct block_list *bl)
{
	nullpo_retr(0, bl);

	if(bl->type == BL_PC)
	{
		if(((struct map_session_data*)bl)->special_state.no_magic_damage)
			return 1;
	}
	return 0;
}

/*==========================================
 * ステータス異常データの動的確保
 *------------------------------------------
 */
#ifdef DYNAMIC_SC_DATA

int status_calloc_sc_data(struct status_change *sc)
{
	if(sc && sc->data == dummy_sc_data)
	{
		int i;
		sc->data = (struct status_change_data *)aCalloc(MAX_STATUSCHANGE, sizeof(struct status_change_data));
		for(i=0; i<MAX_STATUSCHANGE; i++) {
			sc->data[i].timer = -1;
			sc->data[i].val1  = 0;
			sc->data[i].val2  = 0;
			sc->data[i].val3  = 0;
			sc->data[i].val4  = 0;
		}
		sc->count = 0;
		return 1;	// calloced
	}

	return 0;
}

int status_free_sc_data(struct status_change *sc)
{
	if(sc && sc->data != dummy_sc_data)
	{
		map_freeblock(sc->data);
		sc->data  = dummy_sc_data;
		sc->count = 0;
	}

	return 0;
}

#endif

/*==========================================
 * ステータス異常開始
 *------------------------------------------
 */
int status_change_start(struct block_list *bl,int type,int val1,int val2,int val3,int val4,int tick,int flag)
{
	struct map_session_data *sd  = NULL;
	struct mob_data         *md  = NULL;
	struct homun_data       *hd  = NULL;
	struct merc_data        *mcd = NULL;
	struct status_change    *sc  = NULL;
	int opt_flag = 0, calc_flag = 0, race, mode, elem;
	int scdef = 0;

	nullpo_retr(0, bl);

	if(type < 0)
		return 0;

	sc = status_get_sc(bl);
	if(sc == NULL)
		return 0;

	if(bl->type == BL_HOM && !battle_config.allow_homun_status_change)
	{
		if(type < SC_AVOID || type > SC_SPEED)
			return 0;
	}

	race = status_get_race(bl);
	mode = status_get_mode(bl);
	elem = status_get_elem_type(bl);

	if(type == SC_AETERNA && (sc->data[SC_STONE].timer != -1 || sc->data[SC_FREEZE].timer != -1))
		return 0;

	// 特殊系
	if(type >= MAX_STATUSCHANGE) {
		switch(type) {
			case SC_SOUL:
				status_change_soulstart(bl,val1,val2,val3,val4,tick,flag);
				break;
			default:
				if(battle_config.error_log)
					printf("UnknownStatusChange [%d]\n", type);
				break;
		}
		return 0;
	}

	// ON/OFF
	switch(type) {
		case SC_AUTOBERSERK:
		case SC_READYSTORM:
		case SC_READYDOWN:
		case SC_READYTURN:
		case SC_READYCOUNTER:
		case SC_DODGE:
		case SC_FUSION:
			if(sc->data[type].timer != -1) {
				status_change_end(bl,type,-1);
				return 0;
			}
			break;
	}

	switch(type) {
		case SC_STONE:
		case SC_FREEZE:
			scdef = 3+status_get_mdef(bl)+status_get_luk(bl)/3;
			break;
		case SC_STUN:
		case SC_SILENCE:
		case SC_POISON:
		case SC_DPOISON:
		case SC_BLEED:	// 詳細不明なのでとりあえずここで
			scdef = 3+status_get_vit(bl)+status_get_luk(bl)/3;
			break;
		case SC_SLEEP:
		case SC_BLIND:
			scdef = 3+status_get_int(bl)+status_get_luk(bl)/3;
			break;
		case SC_CURSE:
			scdef = 3+status_get_luk(bl);
			break;
		case SC_CONFUSION:
		default:
			scdef = 0;
	}
	if(scdef) {
		if(sc->data[SC_STATUS_UNCHANGE].timer != -1) {
			if(status_is_disable(type,0x10))	// ゴスペルの全状態異常耐性中なら無効
				return 0;
		}
		if(sc->data[SC_SIEGFRIED].timer != -1) {		// ジークフリードの状態異常耐性
			scdef += 50;
		}
	}

	if(!(flag&8) && scdef >= 100)	// flagが+8なら完全耐性計算しない
		return 0;

	sd  = BL_DOWNCAST( BL_PC,   bl );
	md  = BL_DOWNCAST( BL_MOB,  bl );
	hd  = BL_DOWNCAST( BL_HOM,  bl );
	mcd = BL_DOWNCAST( BL_MERC, bl );

	if( sd ) {
		// アドレナリンラッシュの武器判定
		if( type == SC_ADRENALINE && !(skill_get_weapontype(BS_ADRENALINE)&(1<<sd->status.weapon)) )
			return 0;
		// フルアドレナリンラッシュの武器判定
		if( type == SC_ADRENALINE2 && !(skill_get_weapontype(BS_ADRENALINE2)&(1<<sd->status.weapon)) )
			return 0;
		if( SC_STONE <= type && type <= SC_BLEED ) {	/* カードによる耐性 */
			if( !(flag&8) && sd->reseff[type-SC_STONE] > 0 && atn_rand()%10000 < sd->reseff[type-SC_STONE] ) {
				if(battle_config.battle_log)
					printf("PC %d skill_sc_start: cardによる異常耐性発動\n",sd->bl.id);
				return 0;
			}
		}
	}

	// アンデッドは凍結・石化・出血無効
	if((race == RCT_UNDEAD || elem == ELE_UNDEAD) && !(flag&1) && (type == SC_STONE || type == SC_FREEZE || type == SC_BLEED))
		return 0;

	if((type == SC_ADRENALINE || type == SC_ADRENALINE2 || type == SC_WEAPONPERFECTION || type == SC_OVERTHRUST) &&
		sc->data[type].timer != -1 && sc->data[type].val2 && !val2)
		return 0;

	// ボス属性には無効(ただしカードによる効果は適用される)
	if( mode&0x20 && !(flag&1) && status_is_disable(type,0x01) ) {
		if(type == SC_BLESSING && !battle_check_undead(race,elem) && race != RCT_DEMON) {
			// ブレスは不死/悪魔でないなら効く
			;
		} else {
			return 0;
		}
	}

	// クァグマイア中は無効
	if(sc->data[SC_QUAGMIRE].timer != -1 && status_is_disable(type,0x02))
		return 0;
	// 私を忘れないで中は無効
	if(sc->data[SC_DONTFORGETME].timer != -1 && status_is_disable(type,0x04))
		return 0;
	// 速度減少中は無効
	if(sc->data[SC_DECREASEAGI].timer != -1 && status_is_disable(type,0x08))
		return 0;

	if(type == SC_STUN || type == SC_SLEEP)
		unit_stop_walking(bl,1);

	if(type == SC_BLESSING && (sd || (!battle_check_undead(race,elem) && race != RCT_DEMON))) {
		if(sc->data[SC_CURSE].timer != -1)
			status_change_end(bl,SC_CURSE,-1);
		if(sc->data[SC_STONE].timer != -1 && sc->data[SC_STONE].val2 == 0)
			status_change_end(bl,SC_STONE,-1);
	}

	if(sc->data[type].timer != -1) {	/* すでに同じ異常になっている場合タイマ解除 */
		if(sc->data[type].val1 > val1 && type != SC_COMBO && type != SC_DANCING && type != SC_DEVOTION &&
			type != SC_SPEEDPOTION0 && type != SC_SPEEDPOTION1 && type != SC_SPEEDPOTION2 && type != SC_SPEEDPOTION3 &&
			type != SC_DOUBLE && type != SC_TKCOMBO && type != SC_DODGE && type != SC_SPURT && type != SC_SEVENWIND)
			return 0;
		if((type >= SC_STUN && type <= SC_BLIND) || type == SC_DPOISON || type == SC_FOGWALLPENALTY || type == SC_FORCEWALKING)
			return 0;	/* 継ぎ足しができない状態異常である時は状態異常を行わない */
		if(type == SC_GRAFFITI || type == SC_SEVENWIND) {
			// 異常中にもう一度状態異常になった時に解除してから再度かかる
			status_change_end(bl,type,-1);
		} else {
			sc->count--;
			delete_timer(sc->data[type].timer, status_change_timer);
			sc->data[type].timer = -1;
#ifdef DYNAMIC_SC_DATA
			if(sc->count <= 0 && battle_config.free_sc_data_dynamically)
				status_free_sc_data(sc);
#endif
		}
	}

	switch(type) {	/* 異常の種類ごとの処理 */
		case SC_DOUBLE:				/* ダブルストレイフィング */
		case SC_SUFFRAGIUM:			/* サフラギム */
		case SC_MAGNIFICAT:			/* マグニフィカート */
		case SC_AETERNA:			/* エーテルナ */
		case SC_BASILICA:			/* バジリカ */
		case SC_TRICKDEAD:			/* 死んだふり */
		case SC_STRIPWEAPON:
		case SC_STRIPSHIELD:
		case SC_STRIPARMOR:
		case SC_STRIPHELM:
		case SC_CP_WEAPON:
		case SC_CP_SHIELD:
		case SC_CP_ARMOR:
		case SC_CP_HELM:
		case SC_DEVOTION:			/* ディボーション */
		case SC_COMBO:
		case SC_EXTREMITYFIST:			/* 阿修羅覇凰拳 */
		case SC_RICHMANKIM:
		case SC_ROKISWEIL:			/* ロキの叫び */
		case SC_INTOABYSS:			/* 深淵の中に */
		case SC_POEMBRAGI:			/* ブラギの詩 */
		case SC_ANKLE:				/* アンクル */
		case SC_MAGNUM:				/* マグナムブレイク */
		case SC_TIGERFIST:			/* 伏虎拳 */
		case SC_ENERGYCOAT:			/* エナジーコート */
		case SC_POEMBRAGI_:			/* ブラギの詩 */
		case SC_FOGWALLPENALTY:
		case SC_FOGWALL:
		case SC_REVERSEORCISH:
		case SC_GRAVITATION_USER:
		case SC_BLADESTOP_WAIT:			/* 白刃取り(待ち) */
		case SC_SAFETYWALL:			/* セーフティウォール */
		case SC_PNEUMA:				/* ニューマ */
		case SC_KEEPING:
		case SC_BARRIER:
		case SC_AURABLADE:			/* オーラブレード */
		case SC_HEADCRUSH:			/* ヘッドクラッシュ */
		case SC_MELTDOWN:			/* メルトダウン */
		case SC_SPLASHER:			/* ベナムスプラッシャー */
		case SC_GOSPEL:				/* ゴスペル */
		case SC_STATUS_UNCHANGE:		/* 全状態異常耐性 */
		case SC_INCDAMAGE:			/* 被ダメージ%上昇 */
		case SC_PRESERVE:			/* プリザーブ */
		case SC_REGENERATION:			/* 激励 */
		case SC_MEAL_INCEXP:
		case SC_MEAL_INCJOB:
		case SC_COMBATHAN:			/* 戦闘教範 */
		case SC_LIFEINSURANCE:			/* 生命保険証 */
		case SC_FORCEWALKING:
		case SC_TKCOMBO:			/* テコンコンボ */
		case SC_TRIPLEATTACK_RATE_UP:
		case SC_COUNTER_RATE_UP:
		case SC_WARM:				/* 温もり */
		case SC_KAIZEL:				/* カイゼル */
		case SC_KAAHI:				/* カアヒ */
		case SC_SMA:				/* エスマ */
		case SC_MIRACLE:			/* 太陽と月と星の奇跡 */
		case SC_ANGEL:				/* 太陽と月と星の天使 */
		case SC_BABY:				/* パパ、ママ、大好き */
		case SC_DODGE:
		case SC_DODGE_DELAY:
		case SC_DOUBLECASTING:			/* ダブルキャスティング */
		case SC_SHRINK:				/* シュリンク */
		case SC_WINKCHARM:			/* 魅惑のウィンク */
		case SC_TIGEREYE:
		case SC_PK_PENALTY:
		case SC_HERMODE:
		case SC_TATAMIGAESHI:			/* 畳返し */
		case SC_INVISIBLE:			/* インビジブル */
		case SC_NPC_DEFENDER:
		case SC_SLOWCAST:			/* スロウキャスト */
		case SC_CRITICALWOUND:			/* 致命傷 */
		case SC_MAGICMIRROR:			/* マジックミラー */
		case SC_ITEMDROPRATE:			/* バブルガム */
		case SC_HAPPY:				/* 楽しい状態 */
		case SC_NATURAL_HEAL_STOP:		/* 自然回復停止 */
			break;

		case SC_CONCENTRATE:			/* 集中力向上 */
		case SC_BLESSING:			/* ブレッシング */
		case SC_ANGELUS:			/* アンゼルス */
		case SC_RESISTWATER:
		case SC_RESISTGROUND:
		case SC_RESISTFIRE:
		case SC_RESISTWIND:
		case SC_RESISTPOISON:
		case SC_RESISTHOLY:
		case SC_RESISTDARK:
		case SC_RESISTTELEKINESIS:
		case SC_RESISTUNDEAD:
		case SC_RESISTALL:
		case SC_IMPOSITIO:			/* インポシティオマヌス */
		case SC_GLORIA:				/* グロリア */
		case SC_LOUD:				/* ラウドボイス */
		case SC_MINDBREAKER:			/* マインドブレーカー */
		case SC_ETERNALCHAOS:			/* エターナルカオス */
		case SC_WHISTLE:			/* 口笛 */
		case SC_ASSNCROS:			/* 夕陽のアサシンクロス */
		case SC_APPLEIDUN:			/* イドゥンの林檎 */
		case SC_SANTA:
		case SC_SUMMER:
		case SC_TRUESIGHT:			/* トゥルーサイト */
		case SC_SPIDERWEB:			/* スパイダーウェッブ */
		case SC_STEELBODY:			/* 金剛 */
		case SC_CONCENTRATION:			/* コンセントレーション */
		case SC_MARIONETTE:			/* マリオネットコントロール */
		case SC_MARIONETTE2:			/* マリオネットコントロール */
		case SC_WEDDING:			/* 結婚用(結婚衣裳になって歩くのが遅いとか) */
		case SC_HUMMING:			/* ハミング */
		case SC_FORTUNE:			/* 幸運のキス */
		case SC_SERVICE4U:			/* サービスフォーユー */
		case SC_WHISTLE_:			/* 口笛 */
		case SC_ASSNCROS_:			/* 夕陽のアサシンクロス */
		case SC_APPLEIDUN_:			/* イドゥンの林檎 */
		case SC_HUMMING_:			/* ハミング */
		case SC_DONTFORGETME_:			/* 私を忘れないで */
		case SC_FORTUNE_:			/* 幸運のキス */
		case SC_SERVICE4U_:			/* サービスフォーユー */
		case SC_GRAVITATION:			/* グラビテーションフィールド */
		case SC_INCATK:				/* ATK上昇 (神酒用) */
		case SC_INCMATK:			/* MATK上昇 (神秘の草用) */
		case SC_INCHIT:				/* HIT上昇 */
		case SC_INCFLEE:			/* FLEE上昇 */
		case SC_INCMHP2:			/* MHP%上昇 */
		case SC_INCMSP2:			/* MSP%上昇 */
		case SC_INCATK2:			/* ATK%上昇 */
		case SC_INCHIT2:			/* HIT%上昇 */
		case SC_INCFLEE2:			/* FLEE%上昇 */
		case SC_INCALLSTATUS:			/* 全ステータス＋20 */
		case SC_CHASEWALK_STR:			/* STR上昇 */
		case SC_BATTLEORDER:			/* 臨戦態勢 */
		case SC_THE_MAGICIAN:
		case SC_STRENGTH:
		case SC_THE_DEVIL:
		case SC_THE_SUN:
		case SC_SPURT:				/* 駆け足用STR */
		case SC_SUN_COMFORT:			/* 太陽の安楽 */
		case SC_MOON_COMFORT:			/* 月の安楽 */
		case SC_STAR_COMFORT:			/* 星の安楽 */
		case SC_FUSION:				/* 太陽と月と星の融合 */
		case SC_MEAL_INCHIT:	// 食事用
		case SC_MEAL_INCFLEE:
		case SC_MEAL_INCFLEE2:
		case SC_MEAL_INCCRITICAL:
		case SC_MEAL_INCDEF:
		case SC_MEAL_INCMDEF:
		case SC_MEAL_INCATK:
		case SC_MEAL_INCMATK:
		case SC_SKE:				/* エスク */
		case SC_SKA:				/* エスカ */
		case SC_CLOSECONFINE:			/* クローズコンファイン */
		case SC_STOP:				/* ホールドウェブ */
		case SC_DISARM:				/* ディスアーム */
		case SC_GATLINGFEVER:			/* ガトリングフィーバー */
		case SC_FLING:				/* フライング */
		case SC_MADNESSCANCEL:			/* マッドネスキャンセラー */
		case SC_ADJUSTMENT:			/* アジャストメント */
		case SC_INCREASING:			/* インクリージングアキュアラシー */
		case SC_FULLBUSTER:			/* フルバスター */
		case SC_NEN:				/* 念 */
		case SC_SUITON:				/* 水遁 */
		case SC_AVOID:				/* 緊急回避 */
		case SC_CHANGE:				/* メンタルチェンジ */
		case SC_DEFENCE:			/* ディフェンス */
		case SC_BLOODLUST:			/* ブラッドラスト */
		case SC_FLEET:				/* フリートムーブ */
		case SC_SPEED:				/* オーバードスピード */
		case SC_STONESKIN:			/* ストーンスキン */
		case SC_ANTIMAGIC:			/* アンチマジック */
		case SC_WEAPONQUICKEN:			/* ウェポンクイッケン */
		case SC_WE_FEMALE:			/* あなたに尽くします */
			calc_flag = 1;
			break;

		case SC_PROVOKE:			/* プロボック */
			calc_flag = 1;
			if(tick <= 0) tick = 1000;	/* (オートバーサーク) */
			break;
		case SC_ENDURE:				/* インデュア */
			if(tick <= 0) tick = 1000 * 60;
			calc_flag = 1;
			val2 = 7;	// 7回攻撃されたら解除
			if(sd && !map[bl->m].flag.gvg) {
				// 被ディボーション者もインデュアにする
				struct map_session_data *tsd;
				int i;
				for(i = 0; i < 5; i++) {
					if(sd->dev.val1[i] && (tsd = map_id2sd(sd->dev.val1[i])) != NULL)
						status_change_start(&tsd->bl,type,val1,0,0,0,skill_get_time(SM_ENDURE,val1),0);
				}
			}
			break;
		case SC_INCREASEAGI:		/* 速度増加 */
			calc_flag = 1;
			if(sc->data[SC_DECREASEAGI].timer != -1)
				status_change_end(bl,SC_DECREASEAGI,-1);
			break;
		case SC_DECREASEAGI:		/* 速度減少 */
			calc_flag = 1;
			if(sc->data[SC_INCREASEAGI].timer != -1)
				status_change_end(bl,SC_INCREASEAGI,-1);
			if(sc->data[SC_TWOHANDQUICKEN].timer != -1)
				status_change_end(bl,SC_TWOHANDQUICKEN,-1);
			if(sc->data[SC_SPEARQUICKEN].timer != -1)
				status_change_end(bl,SC_SPEARQUICKEN,-1);
			if(sc->data[SC_ADRENALINE].timer != -1)
				status_change_end(bl,SC_ADRENALINE,-1);
			break;
		case SC_SIGNUMCRUCIS:		/* シグナムクルシス */
			calc_flag = 1;
			val2 = 10 + val1*4;
			tick = 600*1000;
			clif_emotion(bl,4);
			break;
		case SC_SLOWPOISON:
			if (sc->data[SC_POISON].timer == -1 && sc->data[SC_DPOISON].timer == -1)
				return 0;
			break;
		case SC_ONEHAND:			/* 1HQ */
			if(sc->data[SC_SPEEDPOTION0].timer != -1)
				status_change_end(bl,SC_SPEEDPOTION0,-1);
			if(sc->data[SC_SPEEDPOTION1].timer != -1)
				status_change_end(bl,SC_SPEEDPOTION1,-1);
			if(sc->data[SC_SPEEDPOTION2].timer != -1)
				status_change_end(bl,SC_SPEEDPOTION2,-1);
			calc_flag = 1;
			break;
		case SC_ADRENALINE:			/* アドレナリンラッシュ */
			calc_flag = 1;
			if(sc->data[SC_ADRENALINE2].timer != -1)
				status_change_end(bl,SC_ADRENALINE2,-1);
			if(!(flag&2) && sd && pc_checkskill(sd,BS_HILTBINDING) > 0)
				tick += tick / 10;
			break;
		case SC_ADRENALINE2:			/* フルアドレナリンラッシュ */
			calc_flag = 1;
			if(sc->data[SC_ADRENALINE].timer != -1)
				status_change_end(bl,SC_ADRENALINE,-1);
			if(!(flag&2) && sd && pc_checkskill(sd,BS_HILTBINDING) > 0)
				tick += tick / 10;
			break;
		case SC_WEAPONPERFECTION:		/* ウェポンパーフェクション */
			if(!(flag&2) && sd && pc_checkskill(sd,BS_HILTBINDING) > 0)
				tick += tick / 10;
			break;
		case SC_OVERTHRUST:			/* オーバートラスト */
			if(sc->data[SC_OVERTHRUSTMAX].timer != -1)
				return 0;
			if(!(flag&2) && sd && pc_checkskill(sd,BS_HILTBINDING) > 0)
				tick += tick / 10;
			break;
		case SC_MAXIMIZEPOWER:		/* マキシマイズパワー */
			if(sd)
				tick = val2;	// SPが1減る時間
			else
				tick = 5000*val1;
			break;
		case SC_ENCPOISON:			/* エンチャントポイズン */
			calc_flag = 1;
			val2 = (((val1 - 1) / 2) + 3)*100;	// 毒付与確率
			status_enchant_elemental_end(bl,SC_ENCPOISON);
			break;
		case SC_EDP:			/* エンチャントデッドリーポイズン */
			val2 = val1 + 2;	// 猛毒付与確率(%)
			break;
		case SC_POISONREACT:	/* ポイズンリアクト */
			val2 = (val1 + 1) / 2;
			break;
		case SC_ASPERSIO:			/* アスペルシオ */
			status_enchant_elemental_end(bl,SC_ASPERSIO);
			break;
		case SC_BENEDICTIO:			/* 聖体 */
			status_enchant_armor_elemental_end(bl,SC_BENEDICTIO);
			break;
		case SC_ELEMENTWATER:		// 水
			status_enchant_armor_elemental_end(bl,SC_ELEMENTWATER);
			if(sd) {
				clif_displaymessage(sd->fd,"防具に水属性が付与されました。");
			}
			break;
		case SC_ELEMENTGROUND:		// 土
			status_enchant_armor_elemental_end(bl,SC_ELEMENTGROUND);
			if(sd) {
				clif_displaymessage(sd->fd,"防具に土属性が付与されました。");
			}
			break;
		case SC_ELEMENTFIRE:		// 火
			status_enchant_armor_elemental_end(bl,SC_ELEMENTFIRE);
			if(sd) {
				clif_displaymessage(sd->fd,"防具に火属性が付与されました。");
			}
			break;
		case SC_ELEMENTWIND:		// 風
			status_enchant_armor_elemental_end(bl,SC_ELEMENTWIND);
			if(sd) {
				clif_displaymessage(sd->fd,"防具に風属性が付与されました。");
			}
			break;
		case SC_ELEMENTHOLY:		// 光
			status_enchant_armor_elemental_end(bl,SC_ELEMENTHOLY);
			if(sd) {
				clif_displaymessage(sd->fd,"防具に聖属性が付与されました。");
			}
			break;
		case SC_ELEMENTDARK:		// 闇
			status_enchant_armor_elemental_end(bl,SC_ELEMENTDARK);
			if(sd) {
				clif_displaymessage(sd->fd,"防具に闇属性が付与されました。");
			}
			break;
		case SC_ELEMENTELEKINESIS:	// 念
			status_enchant_armor_elemental_end(bl,SC_ELEMENTELEKINESIS);
			if(sd) {
				clif_displaymessage(sd->fd,"防具に念属性が付与されました。");
			}
			break;
		case SC_ELEMENTPOISON:		// 毒
			status_enchant_armor_elemental_end(bl,SC_ELEMENTPOISON);
			if(sd) {
				clif_displaymessage(sd->fd,"防具に毒属性が付与されました。");
			}
			break;
		case SC_ELEMENTUNDEAD:		// 不死
			status_enchant_armor_elemental_end(bl,SC_ELEMENTUNDEAD);
			//if(sd) {
			//	clif_displaymessage(sd->fd,"防具に不死属性が付与されました。");
			//}
			break;
		case SC_RACEUNKNOWN:
		case SC_RACEUNDEAD:
		case SC_RACEBEAST:
		case SC_RACEPLANT:
		case SC_RACEINSECT:
		case SC_RACEFISH:
		case SC_RACEDEVIL:
		case SC_RACEHUMAN:
		case SC_RACEANGEL:
		case SC_RACEDRAGON:
			status_change_race_end(bl,type);
			if(sd) {
				char message[64];
				sprintf(message,"種族が%sになりました",race_name[type-SC_RACEUNKNOWN]);
				clif_displaymessage(sd->fd,message);
			}
			break;
		case SC_MAGICROD:
			val2 = val1*20;
			break;
		case SC_KYRIE:				/* キリエエレイソン */
			// アスムが掛かっていたら解除して
			if(sc->data[SC_ASSUMPTIO].timer != -1)
				status_change_end(bl,SC_ASSUMPTIO,-1);
			// キリエを掛ける
			val2 = (int)((atn_bignumber)status_get_max_hp(bl) * (val1 * 2 + 10) / 100);	// 耐久度
			val3 = val1 / 2 + 5;	// 回数
			break;
		case SC_QUAGMIRE:			/* クァグマイア */
			calc_flag = 1;
			if(sc->data[SC_CONCENTRATE].timer != -1)
				status_change_end(bl,SC_CONCENTRATE,-1);
			if(sc->data[SC_INCREASEAGI].timer != -1)
				status_change_end(bl,SC_INCREASEAGI,-1);
			if(sc->data[SC_TWOHANDQUICKEN].timer != -1)
				status_change_end(bl,SC_TWOHANDQUICKEN,-1);
			if(sc->data[SC_SPEARQUICKEN].timer != -1)
				status_change_end(bl,SC_SPEARQUICKEN,-1);
			if(sc->data[SC_ADRENALINE].timer != -1)
				status_change_end(bl,SC_ADRENALINE,-1);
			if(sc->data[SC_ADRENALINE2].timer != -1)
				status_change_end(bl,SC_ADRENALINE2,-1);
			if(sc->data[SC_LOUD].timer != -1)
				status_change_end(bl,SC_LOUD,-1);
			if(sc->data[SC_WINDWALK].timer != -1)
				status_change_end(bl,SC_WINDWALK,-1);
			if(sc->data[SC_CARTBOOST].timer != -1)
				status_change_end(bl,SC_CARTBOOST,-1);
			if(sc->data[SC_ONEHAND].timer != -1)
				status_change_end(bl,SC_ONEHAND,-1);
			break;
		case SC_MAGICPOWER:			/* 魔法力増幅 */
			val2 = 1;	// 一度だけ増幅
			break;
		case SC_SACRIFICE:			/* サクリファイス */
			val2 = 5;	// 5回の攻撃で有効
			break;
		case SC_FLAMELAUNCHER:		/* フレームランチャー */
		case SC_FROSTWEAPON:		/* フロストウェポン */
		case SC_LIGHTNINGLOADER:	/* ライトニングローダー */
		case SC_SEISMICWEAPON:		/* サイズミックウェポン */
		case SC_DARKELEMENT:		/* 闇属性 */
		case SC_ATTENELEMENT:		/* 念属性 */
		case SC_UNDEADELEMENT:		/* 不死属性 */
			status_enchant_elemental_end(bl,type);
			break;
		case SC_SEVENWIND:			/* 暖かい風 */
			status_enchant_elemental_end(bl,SC_ENCPOISON);	// エンチャントポイズンは重複してもよい？
			switch(val1) {
				case 1:  val2 = SI_SEISMICWEAPON;   val3 = ELE_EARTH; break;
				case 2:  val2 = SI_LIGHTNINGLOADER; val3 = ELE_WIND;  break;
				case 3:  val2 = SI_FROSTWEAPON;     val3 = ELE_WATER; break;
				case 4:  val2 = SI_FLAMELAUNCHER;   val3 = ELE_FIRE;  break;
				case 5:  val2 = SI_ATTENELEMENT;    val3 = ELE_GHOST; break;
				default: val2 = SI_DARKELEMENT;     val3 = ELE_DARK;  break;
			}
			if(sd) {
				clif_status_change(bl,val2,1);
			}
			break;
		case SC_PROVIDENCE:			/* プロヴィデンス */
			calc_flag = 1;
			val2 = val1*5;
			break;
		case SC_REFLECTSHIELD:
			val2 = 10+val1*3;
			if(sd) {
				// 被ディボーション者もリフレクトシールドにする
				struct map_session_data *tsd;
				int i;
				for(i = 0; i < 5; i++) {
					if(sd->dev.val1[i] && (tsd = map_id2sd(sd->dev.val1[i])) != NULL)
						status_change_start(&tsd->bl,type,val1,0,0,0,skill_get_time(CR_REFLECTSHIELD,val1),0);
				}
			}
			break;
		case SC_AUTOSPELL:			/* オートスペル */
			val4 = 5 + val1*2;
			break;
		case SC_VOLCANO:
			calc_flag = 1;
			val3 = val1*10;
			val4 = (val1 > 5)? 20: val1*(11-val1)/2 + 5;
			break;
		case SC_DELUGE:
			calc_flag = 1;
			val3 = (val1 > 5)? 15: val1*(11-val1)/2;
			val4 = (val1 > 5)? 20: val1*(11-val1)/2 + 5;
			break;
		case SC_VIOLENTGALE:
			calc_flag = 1;
			val3 = val1*3;
			val4 = (val1 > 5)? 20: val1*(11-val1)/2 + 5;
			break;
		case SC_TWOHANDQUICKEN:			/* 2HQ */
			calc_flag = 1;
			if(bl->type == BL_MOB && battle_config.monster_skill_over && val1 >= battle_config.monster_skill_over)
				val2 = 50;
			else
				val2 = 30;
			break;
		case SC_SPEARQUICKEN:		/* スピアクイッケン */
			calc_flag = 1;
			val2 = 20+val1;
			break;
		case SC_BLADESTOP:		/* 白刃取り */
			if(val2 == 2)
				clif_bladestop(map_id2bl(val3),val4,1);
			break;
		case SC_LULLABY:			/* 子守唄 */
			val2 = 11;
			break;
		case SC_DRUMBATTLE:			/* 戦太鼓の響き */
			calc_flag = 1;
			val2 = (val1+1)*25;
			val3 = (val1+1)*2;
			break;
		case SC_NIBELUNGEN:			/* ニーベルングの指輪 */
			calc_flag = 1;
			val2 = (val1+2)*25;
			break;
		case SC_SIEGFRIED:			/* 不死身のジークフリード */
			calc_flag = 1;
			val2 = 5 + val1*15;
			break;
		case SC_DISSONANCE:			/* 不協和音 */
			val2 = 10;
			break;
		case SC_UGLYDANCE:			/* 自分勝手なダンス */
			val2 = 10;
			break;
		case SC_DONTFORGETME:		/* 私を忘れないで */
			calc_flag = 1;
			if(sc->data[SC_INCREASEAGI].timer != -1)
				status_change_end(bl,SC_INCREASEAGI,-1);
			if(sc->data[SC_TWOHANDQUICKEN].timer != -1)
				status_change_end(bl,SC_TWOHANDQUICKEN,-1);
			if(sc->data[SC_SPEARQUICKEN].timer != -1)
				status_change_end(bl,SC_SPEARQUICKEN,-1);
			if(sc->data[SC_ADRENALINE].timer != -1)
				status_change_end(bl,SC_ADRENALINE,-1);
			if(sc->data[SC_ADRENALINE2].timer != -1)
				status_change_end(bl,SC_ADRENALINE2,-1);
			if(sc->data[SC_ASSNCROS].timer != -1)
				status_change_end(bl,SC_ASSNCROS,-1);
			if(sc->data[SC_WINDWALK].timer != -1)
				status_change_end(bl,SC_WINDWALK,-1);
			if(sc->data[SC_CARTBOOST].timer != -1)
				status_change_end(bl,SC_CARTBOOST,-1);
			if(sc->data[SC_ONEHAND].timer != -1)
				status_change_end(bl,SC_ONEHAND,-1);
			break;
		case SC_LONGINGFREEDOM:		/* 私を拘束しないで */
			calc_flag = 1;
			val3 = 1;
			tick = 1000;
			break;
		case SC_DANCING:			/* ダンス/演奏中 */
			calc_flag = 1;
			val3 = tick / 1000;
			tick = 1000;
			break;
		case SC_EXPLOSIONSPIRITS:	/* 爆裂波動 */
			calc_flag = 1;
			val2 = 75 + 25*val1;
			break;
		case SC_AUTOCOUNTER:
			val3 = 0;
			val4 = 0;
			break;
		case SC_POISONPOTION:		/* 毒薬の瓶 */
			calc_flag = 1;
			val2 = 25;
			break;
		case SC_SPEEDPOTION0:		/* 増速ポーション */
		case SC_SPEEDPOTION1:
		case SC_SPEEDPOTION2:
			if(type != SC_SPEEDPOTION0 && sc->data[SC_SPEEDPOTION0].timer != -1)
				status_change_end(bl,SC_SPEEDPOTION0,-1);
			if(type != SC_SPEEDPOTION1 && sc->data[SC_SPEEDPOTION1].timer != -1)
				status_change_end(bl,SC_SPEEDPOTION1,-1);
			if(type != SC_SPEEDPOTION2 && sc->data[SC_SPEEDPOTION2].timer != -1)
				status_change_end(bl,SC_SPEEDPOTION2,-1);
			if(sc->data[SC_SPEEDPOTION3].timer != -1)
				status_change_end(bl,SC_SPEEDPOTION3,-1);
			calc_flag = 1;
			val2 = 5*(2+type-SC_SPEEDPOTION0);
			break;
		case SC_SPEEDPOTION3: 		/* バーサークピッチャー */
			if(sc->data[SC_SPEEDPOTION0].timer != -1)
				status_change_end(bl,SC_SPEEDPOTION0,-1);
			if(sc->data[SC_SPEEDPOTION1].timer != -1)
				status_change_end(bl,SC_SPEEDPOTION1,-1);
			if(sc->data[SC_SPEEDPOTION2].timer != -1)
				status_change_end(bl,SC_SPEEDPOTION2,-1);
			calc_flag = 1;
			val2 = 20;
			break;
		case SC_NOCHAT:		/* チャット禁止状態 */
			{
				time_t timer;
				tick = 60000;
				if(!val2)
					val2 = (int)time(&timer);
				if(sd)
					clif_updatestatus(sd,SP_MANNER);	// ステータスをクライアントに送る
			}
			break;
		case SC_SELFDESTRUCTION:	/* 自爆 */
			tick = 100;
			break;

		/* option1 */
		case SC_STONE:				/* 石化 */
			if(!(flag&2)) {
				int sc_def = status_get_mdef(bl)*200;
				tick = tick - sc_def;
			}
			val3 = tick / 1000;
			if(val3 < 1)
				val3 = 1;
			tick = val4;
			if(tick < 1000)
				tick = 1000;
			val2 = 1;
			break;
		case SC_SLEEP:				/* 睡眠 */
			if(!(flag&2)) {
				tick = 30000;	// 睡眠はステータス耐性に関わらず30秒
			}
			break;
		case SC_FREEZE:				/* 凍結 */
			if(!(flag&2)) {
				int sc_def = 100 - status_get_mdef(bl);
				tick = tick * sc_def / 100;
			}
			break;
		case SC_STUN:				/* スタン（val2にミリ秒セット） */
			if(!(flag&2)) {
				int sc_def = 100 - (status_get_vit(bl) + status_get_luk(bl)/3);
				tick = tick * sc_def / 100;
			}
			break;
		/* option2 */
		case SC_DPOISON:			/* 猛毒 */
			{
				int mhp = status_get_max_hp(bl);
				int hp = status_get_hp(bl);
				// MHPの1/4以下にはならない
				if(hp > mhp>>2) {
					int diff = 0;
					if(sd)
						diff = mhp*10/100;
					else if(md)
						diff = mhp*15/100;
					if(hp - diff < mhp>>2)
						diff = hp - (mhp>>2);
					unit_heal(bl, -diff, 0);
				}
			}
			// fall through
		case SC_POISON:				/* 毒 */
			calc_flag = 1;
			if(!(flag&2)) {
				int sc_def = 100 - (status_get_vit(bl) + status_get_luk(bl)/5);
				tick = tick * sc_def / 100;
			}
			val3 = tick/1000;
			if(val3 < 1) val3 = 1;
			tick = 1000;
			break;
		case SC_SILENCE:			/* 沈黙 */
			skill_stop_dancing(bl,0);
			if (sc->data[SC_GOSPEL].timer != -1) {
				status_change_end(bl,SC_GOSPEL,-1);
				break;
			}
			if(!(flag&2)) {
				int sc_def = 100 - status_get_vit(bl);
				tick = tick * sc_def / 100;
			}
			break;
		case SC_BLIND:				/* 暗黒 */
			calc_flag = 1;
			if(!(flag&2)) {
				int sc_def = status_get_lv(bl)/10 + status_get_int(bl)/15;
				tick = 30000 - sc_def;
			}
			break;
		case SC_CURSE:				/* 呪い */
			calc_flag = 1;
			if(!(flag&2)) {
				int sc_def = 100 - status_get_vit(bl);
				tick = tick * sc_def / 100;
			}
			break;
		case SC_CONFUSION:			/* 混乱 */
			break;
		case SC_BLEED:				/* 出血 */
			if(!(flag&2)) {
				// 効果時間の詳細不明なのでとりあえず毒のものを使う
				int sc_def = 100 - (status_get_vit(bl) + status_get_luk(bl)/5);
				tick = tick * sc_def / 100;
			}
			val3 = (tick < 10000)? 1: tick/10000;
			tick = 10000;	// ダメージ発生は10sec毎
			break;

		/* option */
		case SC_HIDING:		/* ハイディング */
			calc_flag = 1;
			if(sd) {
				val2 = tick / 1000;		/* 持続時間 */
				tick = 1000;
			}
			break;
		case SC_CHASEWALK:		/* チェイスウォーク */
		case SC_CLOAKING:		/* クローキング */
			if(sd) {
				calc_flag = 1;
				tick = val2;
			} else {
				tick = 5000*val1;
			}
			break;
		case SC_SIGHTBLASTER:		/* サイトブラスター */
		case SC_SIGHT:			/* サイト */
		case SC_RUWACH:			/* ルアフ */
			val2 = tick/250;
			tick = 10;
			break;

		case SC_MODECHANGE:
			tick = 1200;
			break;
		case SC_AUTOGUARD:
			val2 = (val1 > 10)? 30: (22 - val1) * val1 / 4;
			if(sd) {
				// 被ディボーション者もオートガードにする
				struct map_session_data *tsd;
				int i;
				for(i = 0; i < 5; i++) {
					if(sd->dev.val1[i] && (tsd = map_id2sd(sd->dev.val1[i])) != NULL)
						status_change_start(&tsd->bl,type,val1,0,0,0,skill_get_time(CR_AUTOGUARD,val1),0);
				}
			}
			break;
		case SC_DEFENDER:
			calc_flag = 1;
			val2 = 5 + val1*15;
			if(sd) {
				// 被ディボーション者をディフェンダーLv1にする
				struct map_session_data *tsd;
				int i;
				for(i = 0; i < 5; i++) {
					if(sd->dev.val1[i] && (tsd = map_id2sd(sd->dev.val1[i])) != NULL)
						status_change_start(&tsd->bl,type,1,0,0,0,skill_get_time(CR_DEFENDER,1),0);
				}
			}
			break;
		case SC_HALLUCINATION:
			if(sd && !battle_config.hallucianation_off) {
				// onなのでアイコン表示
				clif_status_change(bl, SI_HALLUCINATION, 1);
			}
			break;
		case SC_TENSIONRELAX:	/* テンションリラックス */
			if(sd == NULL)
				return 0;
			tick = 10000;
			break;
		case SC_PARRYING:		/* パリイング */
			val2 = 20 + val1*3;
			break;
		case SC_JOINTBEAT:		/* ジョイントビート */
			calc_flag = 1;
			val4 = atn_rand()%6;
			if(val4 == 5) {
				// 首は強制的に出血付加
				status_change_start(bl,SC_BLEED,val1,0,0,0,skill_get_time2(LK_JOINTBEAT,val1),10);
			}
			if(!(flag&2)) {
				tick = tick - (status_get_agi(bl)/10 + status_get_luk(bl)/4)*1000;
			}
			break;
		case SC_WINDWALK:		/* ウインドウォーク */
			calc_flag = 1;
			val2 = val1 / 2;	// Flee上昇率
			break;
		case SC_BERSERK:		/* バーサーク */
			unit_heal(bl,0,-status_get_sp(bl));
			if(sd) {
				clif_status_change(bl,SI_INCREASEAGI,1);	// アイコン表示
			}
			tick = 1000;
			calc_flag = 1;
			break;
		case SC_ASSUMPTIO:		/* アスムプティオ */
			// キリエが掛かっていたら解除
			if(sc->data[SC_KYRIE].timer != -1)
				status_change_end(bl,SC_KYRIE,-1);
			// カイトが掛かっていたら解除
			if(sc->data[SC_KAITE].timer != -1)
				status_change_end(bl,SC_KAITE,-1);
			break;
		case SC_CARTBOOST:		/* カートブースト */
			calc_flag = 1;
			if(sc->data[SC_DECREASEAGI].timer != -1)
				status_change_end(bl,SC_DECREASEAGI,-1);
			break;
		case SC_REJECTSWORD:	/* リジェクトソード */
			val2 = 3; // 3回攻撃を跳ね返す
			break;
		case SC_MEMORIZE:		/* メモライズ */
			val2 = 5; // 5回詠唱を1/2にする
			break;
		case SC_GRAFFITI:		/* グラフィティ */
			{
				struct skill_unit_group *sg = skill_unitsetting(bl,RG_GRAFFITI,val1,val2,val3,0);
				if(sg)
					val4 = (int)sg;
			}
			break;
		case SC_OVERTHRUSTMAX:		/* オーバートラストマックス */
			if(sc->data[SC_OVERTHRUST].timer != -1)
				status_change_end(bl,SC_OVERTHRUST,-1);
			calc_flag = 1;
			break;

		case SC_MEAL_INCSTR:	// 食事用
		case SC_MEAL_INCAGI:
		case SC_MEAL_INCVIT:
		case SC_MEAL_INCINT:
		case SC_MEAL_INCDEX:
		case SC_MEAL_INCLUK:
			// 課金料理使用中は効果なし
			if(sc->data[type - SC_MEAL_INCSTR + SC_MEAL_INCSTR2].timer != -1)
				return 0;
			calc_flag = 1;
			break;
		case SC_MEAL_INCSTR2:	// 課金料理用
		case SC_MEAL_INCAGI2:
		case SC_MEAL_INCVIT2:
		case SC_MEAL_INCINT2:
		case SC_MEAL_INCDEX2:
		case SC_MEAL_INCLUK2:
			// 通常の食事とは重複しない
			if(sc->data[type - SC_MEAL_INCSTR2 + SC_MEAL_INCSTR].timer != -1)
				status_change_end(bl, type - SC_MEAL_INCSTR2 + SC_MEAL_INCSTR, -1);
			calc_flag = 1;
			break;
		case SC_ELEMENTFIELD:		/* 属性場 */
			tick = val2;
			break;
		case SC_RUN:			/* タイリギ */
			val4 = 0;
			calc_flag = 1;
			break;
		case SC_KAUPE:			/* カウプ */
			val2 = val1*33;
			if(val1 >= 3)
				val2 = 100;
			break;
		case SC_KAITE:			/* カイト */
			// アスムが掛かっていたら解除して
			if(sc->data[SC_ASSUMPTIO].timer != -1)
				status_change_end(bl,SC_ASSUMPTIO,-1);
			// 反射回数
			val2 = val1 / 5 + 1;
			break;
		case SC_SWOO:			/* エスウ */
			calc_flag = 1;
			if(status_get_mode(bl)&0x20)
				tick /= 5;
			break;
		case SC_MONK:			/* モンクの魂 */
		case SC_STAR:			/* ケンセイの魂 */
		case SC_SAGE:			/* セージの魂 */
		case SC_CRUSADER:		/* クルセイダーの魂 */
		case SC_WIZARD:			/* ウィザードの魂 */
		case SC_PRIEST:			/* プリーストの魂 */
		case SC_ROGUE:			/* ローグの魂 */
		case SC_ASSASIN:		/* アサシンの魂 */
		case SC_SOULLINKER:		/* ソウルリンカーの魂 */
		case SC_GUNNER:			/* ガンスリンガーの魂 */
		case SC_NINJA:			/* 忍者の魂 */
		case SC_DEATHKINGHT:		/* デスナイトの魂 */
		case SC_COLLECTOR:		/* コレクターの魂 */
			if(sd && battle_config.disp_job_soul_state_change)
				clif_disp_onlyself(sd->fd,"魂状態になりました");
			break;
		case SC_KNIGHT:			/* ナイトの魂 */
		case SC_ALCHEMIST:		/* アルケミストの魂 */
		case SC_BARDDANCER:		/* バードとダンサーの魂 */
		case SC_BLACKSMITH:		/* ブラックスミスの魂 */
		case SC_HUNTER:			/* ハンターの魂 */
		case SC_HIGH:			/* 一次上位職業の魂 */
			if(sd && battle_config.disp_job_soul_state_change)
				clif_disp_onlyself(sd->fd,"魂状態になりました");
			calc_flag = 1;
			break;
		case SC_SUPERNOVICE:		/* スーパーノービスの魂 */
			if(sd) {
				// 1%で死亡フラグ消す
				if(atn_rand()%10000 < battle_config.repeal_die_counter_rate) {
					sd->status.die_counter = 0;	// 死にカウンターリセット
					if(sd->status.job_level >= 70)
						clif_misceffect(&sd->bl,7);	// スパノビ天使
				}
				if(battle_config.disp_job_soul_state_change)
					clif_disp_onlyself(sd->fd,"魂状態になりました");
			}
			calc_flag = 1;
			break;
		case SC_AUTOBERSERK:
			if( status_get_hp(bl) < status_get_max_hp(bl) >> 2 &&
			    (sc->data[SC_PROVOKE].timer == -1 || sc->data[SC_PROVOKE].val2 == 0) )
			{
				// オートバーサーク発動
				status_change_start(&sd->bl,SC_PROVOKE,10,1,0,0,0,0);
			}
			tick = 600*1000;
			break;
		case SC_READYSTORM:
		case SC_READYDOWN:
		case SC_READYTURN:
		case SC_READYCOUNTER:
			tick = 600*1000;
			break;
		case SC_UTSUSEMI:		/* 空蝉 */
			val3 = (val1+1)/2;
			break;
		case SC_BUNSINJYUTSU:		/* 分身の術 */
			val3 = (val1+1)/2;
			if(sd) {
				val4 = sd->status.clothes_color;
				pc_changelook(sd, LOOK_CLOTHES_COLOR, 0);
			}
			break;
		case SC_BOSSMAPINFO:		/* 凸面鏡 */
			if(map[bl->m].mvpboss == NULL) {
				if(sd) {
					// 居ないのでメッセージを出して終了
					clif_bossmapinfo(sd, "", 0, 0, 0, 0);
				}
				tick = 0;
			}
			break;
		default:
			if(battle_config.error_log)
				printf("UnknownStatusChange [%d]\n", type);
			return 0;
	}

	if(tick <= 0)
		return 0;

	if(sd && StatusIconChangeTable[type] != SI_BLANK)
		clif_status_change(bl,StatusIconChangeTable[type],1);	// アイコン表示

	/* 凸面鏡はアイコン送信後に処理する */
	if(type == SC_BOSSMAPINFO) {
		struct mob_data *mmd = map[bl->m].mvpboss;
		if(sd && mmd) {
			if(mmd->bl.prev == NULL) {	// 再沸き待ち中
				int diff = DIFF_TICK(mmd->last_spawntime, gettick());
				if(diff < 0)
					diff = 0;
				clif_bossmapinfo(sd, mmd->name, 0, 0, diff, 3);
				val3 = -1;
				val4 = -1;
			} else {			// 出現中
				clif_bossmapinfo(sd, mmd->name, 0, 0, 0, 2);
				if(mmd->bl.m == bl->m) {
					clif_bossmapinfo(sd, "", mmd->bl.x, mmd->bl.y, 0, 1);
				}
				val3 = mmd->bl.m;
				val4 = mmd->bl.x + (mmd->bl.y << 16);
			}
		}
		val2 = tick / 1000;
		tick = 1000;
	}

	/* optionの変更 */
	switch(type) {
		// opt1
		case SC_STONE:
		case SC_FREEZE:
		case SC_STUN:
		case SC_SLEEP:
			unit_stopattack(bl);	// 攻撃停止
			skill_stop_dancing(bl,0);	// 演奏/ダンスの中断
			{
				// 同時に掛からないステータス異常を解除
				int i;
				for(i = SC_STONE; i <= SC_SLEEP; i++) {
					if(sc->data[i].timer != -1) {
						sc->count--;
						delete_timer(sc->data[i].timer, status_change_timer);
						sc->data[i].timer = -1;
					}
				}
			}
			if(type == SC_STONE)
				sc->opt1 = 6;
			else
				sc->opt1 = type - SC_STONE + 1;
			opt_flag = 1;
			break;
		// opt2
		case SC_POISON:
		case SC_CURSE:
		case SC_SILENCE:
		case SC_CONFUSION:
			sc->opt2 |= 1<<(type-SC_POISON);
			opt_flag = 1;
			break;
		case SC_FOGWALLPENALTY:
		case SC_BLIND:
			if(sc->data[SC_FOGWALLPENALTY].timer == -1) {
				sc->opt2 |= 0x00010;
				opt_flag = 1;
				if(md && !(flag&2))
					md->target_id = 0;
			}
			break;
		case SC_DPOISON:
			sc->opt2 |= 0x00080;
			opt_flag = 1;
			break;
		case SC_SIGNUMCRUCIS:
			sc->opt2 |= 0x00040;
			opt_flag = 1;
			break;
		// opt3
		case SC_ONEHAND:		/* 1HQ */
		case SC_TWOHANDQUICKEN:		/* 2HQ */
		case SC_SPEARQUICKEN:		/* スピアクイッケン */
		case SC_CONCENTRATION:		/* コンセントレーション */
		case SC_WEAPONQUICKEN:		/* ウェポンクイッケン */
			sc->opt3 |= 0x00001;
			opt_flag = 2;
			break;
		case SC_OVERTHRUST:		/* オーバートラスト */
		case SC_SWOO:			/* エスウ */
			sc->opt3 |= 0x00002;
			opt_flag = 2;
			break;
		case SC_ENERGYCOAT:		/* エナジーコート */
		case SC_SKE:			/* エスク */
			sc->opt3 |= 0x00004;
			opt_flag = 2;
			break;
		case SC_EXPLOSIONSPIRITS:	/* 爆裂波動 */
			sc->opt3 |= 0x00008;
			opt_flag = 2;
			break;
		case SC_STEELBODY:		/* 金剛 */
		case SC_SKA:			/* エスカ */
			sc->opt3 |= 0x00010;
			opt_flag = 2;
			break;
		case SC_BLADESTOP:		/* 白刃取り */
			sc->opt3 |= 0x00020;
			opt_flag = 2;
			break;
		case SC_BERSERK:		/* バーサーク */
			sc->opt3 |= 0x00080;
			opt_flag = 2;
			break;
		case SC_MARIONETTE:		/* マリオネットコントロール */
		case SC_MARIONETTE2:		/* マリオネットコントロール */
			sc->opt3 |= 0x00400;
			opt_flag = 2;
			break;
		case SC_ASSUMPTIO:		/* アスムプティオ */
			sc->opt3 |= 0x00800;
			clif_misceffect2(bl,375);
			opt_flag = 2;
			break;
		case SC_WARM:			/* 温もり */
			sc->opt3 |= 0x01000;
			opt_flag = 2;
			break;
		case SC_KAITE:
			sc->opt3 |= 0x02000;
			opt_flag = 2;
			break;
		case SC_MONK:			/* モンクの魂 */
		case SC_STAR:			/* ケンセイの魂 */
		case SC_SAGE:			/* セージの魂 */
		case SC_CRUSADER:		/* クルセイダーの魂 */
		case SC_WIZARD:			/* ウィザードの魂 */
		case SC_PRIEST:			/* プリーストの魂 */
		case SC_ROGUE:			/* ローグの魂 */
		case SC_ASSASIN:		/* アサシンの魂 */
		case SC_SOULLINKER:		/* ソウルリンカーの魂 */
		case SC_KNIGHT:			/* ナイトの魂 */
		case SC_ALCHEMIST:		/* アルケミストの魂 */
		case SC_BARDDANCER:		/* バードとダンサーの魂 */
		case SC_BLACKSMITH:		/* ブラックスミスの魂 */
		case SC_HUNTER:			/* ハンターの魂 */
		case SC_HIGH:			/* 一次上位職業の魂 */
		case SC_SUPERNOVICE:		/* スーパーノービスの魂 */
		case SC_GUNNER:			/* ガンスリンガーの魂 */
		case SC_NINJA:			/* 忍者の魂 */
		case SC_DEATHKINGHT:		/* デスナイトの魂 */
		case SC_COLLECTOR:		/* コレクターの魂 */
			sc->opt3 |= 0x08000;
			clif_misceffect2(bl,424);
			opt_flag = 2;
			break;
		// option
		case SC_SIGHT:
			sc->option |= 0x00001;
			opt_flag = 1;
			break;
		case SC_HIDING:
			if(sd && val3 == 0)	// 霞斬りでない通常のハイドならアイコン表示
				clif_status_change(bl,SI_HIDING,1);
			unit_stopattack(bl);
			sc->option |= 0x00002;
			opt_flag = 1;
			break;
		case SC_CLOAKING:
			unit_stopattack(bl);
			sc->option |= 0x00004;
			opt_flag = 1;
			break;
		case SC_INVISIBLE:
			unit_stopattack(bl);
			sc->option |= 0x00040;
			opt_flag = 1;
			break;
		case SC_REVERSEORCISH:
			sc->option |= 0x00800;
			opt_flag = 1;
			break;
		case SC_WEDDING:
			sc->option |= 0x01000;
			opt_flag = 1;
			break;
		case SC_RUWACH:
			sc->option |= 0x02000;
			opt_flag = 1;
			break;
		case SC_CHASEWALK:
			unit_stopattack(bl);
			sc->option |= 0x04004;
			opt_flag = 1;
			break;
		case SC_FUSION:
			sc->option |= 0x08000;
			opt_flag = 1;
			break;
	}

	/* optionの変更 */
	if(opt_flag == 1) {
		clif_changeoption(bl);
		clif_send_clothcolor(bl);
	} else if(opt_flag == 2) {
		clif_changeoption2(bl);
	}

#ifdef DYNAMIC_SC_DATA
	status_calloc_sc_data(sc);
#endif

	sc->count++;	/* ステータス異常の数 */

	sc->data[type].val1 = val1;
	sc->data[type].val2 = val2;
	sc->data[type].val3 = val3;
	sc->data[type].val4 = val4;
	/* タイマー設定 */
	sc->data[type].timer = add_timer(gettick() + tick, status_change_timer, bl->id, type);

	if(calc_flag) {
		// ステータス再計算
		if(sd) {
			if(!(flag&4))
				status_calc_pc(sd,0);
		} else if(hd) {
			homun_calc_status(hd);
			clif_send_homstatus(hd->msd,0);
		} else if(mcd) {
			merc_calc_status(mcd);
			clif_send_mercstatus(mcd->msd,0);
		}
	}
	// 計算後に走らせる
	switch(type) {
		case SC_RUN:
			// clif_skill_nodamage() は必ず clif_status_change() と clif_walkok() の間に呼び出す
			clif_skill_nodamage(bl,bl,TK_RUN,val1,1);
			if(sd) {
				pc_runtodir(sd);
			}
			break;
		case SC_FORCEWALKING:
			unit_forcewalktodir(bl,val4);
			break;
	}

	return 0;
}

/*==========================================
 * ステータス異常終了
 *------------------------------------------
 */
int status_change_end(struct block_list* bl, int type, int tid)
{
	struct map_session_data *sd  = NULL;
	struct mob_data         *md  = NULL;
	struct homun_data       *hd  = NULL;
	struct merc_data        *mcd = NULL;
	struct status_change    *sc  = NULL;
	int opt_flag = 0, calc_flag = 0;

	nullpo_retr(0, bl);
	nullpo_retr(0, sc = status_get_sc(bl));

	if(type < 0)
		return 0;

	if(type >= MAX_STATUSCHANGE) {
		switch(type) {
			case SC_RACECLEAR:
				status_change_race_end(bl,-1);
				break;
			case SC_RESISTCLEAR:
				status_change_resistclear(bl);
				break;
			case SC_SOUL:
			case SC_SOULCLEAR:
				status_change_soulclear(bl);
				break;
			default:
				if(battle_config.error_log)
					printf("UnknownStatusChangeEnd [%d]\n", type);
				break;
		}
		return 0;
	}

	if(sc->count <= 0 || sc->data[type].timer == -1)
		return 0;

	if(tid != -1 && sc->data[type].timer != tid)
		return 0;

	if(tid == -1)	/* タイマから呼ばれていないならタイマ削除をする */
		delete_timer(sc->data[type].timer,status_change_timer);

	/* 該当の異常を正常に戻す */
	sc->data[type].timer = -1;
	sc->count--;

	sd  = BL_DOWNCAST( BL_PC,   bl );
	md  = BL_DOWNCAST( BL_MOB,  bl );
	hd  = BL_DOWNCAST( BL_HOM,  bl );
	mcd = BL_DOWNCAST( BL_MERC, bl );

	switch(type) {	/* 異常の種類ごとの処理 */
		case SC_PROVOKE:			/* プロボック */
		case SC_CONCENTRATE:			/* 集中力向上 */
		case SC_BLESSING:			/* ブレッシング */
		case SC_ANGELUS:			/* アンゼルス */
		case SC_INCREASEAGI:			/* 速度上昇 */
		case SC_DECREASEAGI:			/* 速度減少 */
		case SC_SIGNUMCRUCIS:			/* シグナムクルシス */
		case SC_HIDING:
		case SC_CLOAKING:
		case SC_TWOHANDQUICKEN:			/* 2HQ */
		case SC_ONEHAND:			/* 1HQ */
		case SC_ADRENALINE:			/* アドレナリンラッシュ */
		case SC_ENCPOISON:			/* エンチャントポイズン */
		case SC_IMPOSITIO:			/* インポシティオマヌス */
		case SC_GLORIA:				/* グロリア */
		case SC_LOUD:				/* ラウドボイス */
		case SC_MINDBREAKER:			/* マインドブレーカー */
		case SC_QUAGMIRE:			/* クァグマイア */
		case SC_PROVIDENCE:			/* プロヴィデンス */
		case SC_SPEARQUICKEN:			/* スピアクイッケン */
		case SC_VOLCANO:
		case SC_DELUGE:
		case SC_VIOLENTGALE:
		case SC_ETERNALCHAOS:			/* エターナルカオス */
		case SC_DRUMBATTLE:			/* 戦太鼓の響き */
		case SC_NIBELUNGEN:			/* ニーベルングの指輪 */
		case SC_SIEGFRIED:			/* 不死身のジークフリード */
		case SC_EXPLOSIONSPIRITS:		/* 爆裂波動 */
		case SC_STEELBODY:			/* 金剛 */
		case SC_POISONPOTION:			/* 毒薬の瓶 */
		case SC_SPEEDPOTION0:			/* 増速ポーション */
		case SC_SPEEDPOTION1:
		case SC_SPEEDPOTION2:
		case SC_SPEEDPOTION3:
		case SC_BLADESTOP_WAIT:
		case SC_CONCENTRATION:			/* コンセントレーション */
		case SC_WINDWALK:			/* ウインドウォーク */
		case SC_TRUESIGHT:			/* トゥルーサイト */
		case SC_SPIDERWEB:			/* スパイダーウェッブ */
		case SC_CARTBOOST:			/* カートブースト */
		case SC_INCATK:				/* ATK上昇 (神酒用) */
		case SC_INCMATK:			/* MATK上昇 (神秘の草用) */
		case SC_WEDDING:			/* ウェディング */
		case SC_SANTA:
		case SC_SUMMER:
		case SC_INCALLSTATUS:
		case SC_INCHIT:
		case SC_INCFLEE:
		case SC_INCMHP2:
		case SC_INCMSP2:
		case SC_INCATK2:
		case SC_INCHIT2:
		case SC_INCFLEE2:
		case SC_OVERTHRUSTMAX:
		case SC_CHASEWALK:			/* チェイスウォーク */
		case SC_CHASEWALK_STR:
		case SC_BATTLEORDER:
		case SC_MEAL_INCSTR:	// 食事用
		case SC_MEAL_INCAGI:
		case SC_MEAL_INCVIT:
		case SC_MEAL_INCINT:
		case SC_MEAL_INCDEX:
		case SC_MEAL_INCLUK:
		case SC_MEAL_INCHIT:
		case SC_MEAL_INCFLEE:
		case SC_MEAL_INCFLEE2:
		case SC_MEAL_INCCRITICAL:
		case SC_MEAL_INCDEF:
		case SC_MEAL_INCMDEF:
		case SC_MEAL_INCATK:
		case SC_MEAL_INCMATK:
		case SC_MEAL_INCSTR2:	// 課金料理用
		case SC_MEAL_INCAGI2:
		case SC_MEAL_INCVIT2:
		case SC_MEAL_INCINT2:
		case SC_MEAL_INCDEX2:
		case SC_MEAL_INCLUK2:
		case SC_SPURT:
		case SC_SUN_COMFORT:			/* 太陽の安楽 */
		case SC_MOON_COMFORT:			/* 月の安楽 */
		case SC_STAR_COMFORT:			/* 星の安楽 */
		case SC_FUSION:				/* 太陽と月と星の融合 */
		case SC_ADRENALINE2:			/* フルアドレナリンラッシュ */
		case SC_RESISTWATER:
		case SC_RESISTGROUND:
		case SC_RESISTFIRE:
		case SC_RESISTWIND:
		case SC_RESISTPOISON:
		case SC_RESISTHOLY:
		case SC_RESISTDARK:
		case SC_RESISTTELEKINESIS:
		case SC_RESISTUNDEAD:
		case SC_RESISTALL:
		case SC_INVISIBLE:
		case SC_TIGEREYE:
		case SC_THE_MAGICIAN:
		case SC_STRENGTH:
		case SC_THE_DEVIL:
		case SC_THE_SUN:
		case SC_DISARM:				/* ディスアーム */
		case SC_GATLINGFEVER:			/* ガトリングフィーバー */
		case SC_FLING:				/* フライング */
		case SC_MADNESSCANCEL:			/* マッドネスキャンセラー */
		case SC_ADJUSTMENT:			/* アジャストメント */
		case SC_INCREASING:			/* インクリージングアキュアラシー */
		case SC_FULLBUSTER:			/* フルバスター */
		case SC_SUITON:				/* 水遁 */
		case SC_NEN:				/* 念 */
		case SC_AVOID:				/* 緊急回避 */
		case SC_CHANGE:				/* メンタルチェンジ */
		case SC_DEFENCE:			/* ディフェンス */
		case SC_BLOODLUST:			/* ブラッドラスト */
		case SC_FLEET:				/* フリートムーブ */
		case SC_SPEED:				/* オーバードスピード */
		case SC_STONESKIN:			/* ストーンスキン */
		case SC_ANTIMAGIC:			/* アンチマジック */
		case SC_WEAPONQUICKEN:			/* ウェポンクイッケン */
		case SC_WE_FEMALE:			/* あなたに尽くします */
			calc_flag = 1;
			break;
		case SC_ELEMENTWATER:		// 水
		case SC_ELEMENTGROUND:		// 土
		case SC_ELEMENTFIRE:		// 火
		case SC_ELEMENTWIND:		// 風
		case SC_ELEMENTHOLY:		// 光
		case SC_ELEMENTDARK:		// 闇
		case SC_ELEMENTELEKINESIS:	// 念
		case SC_ELEMENTPOISON:		// 毒
		//case SC_ELEMENTUNDEAD:	// 不死
			if(sd)
				clif_displaymessage(sd->fd,"防具の属性が元に戻りました");
			break;
		case SC_RACEUNKNOWN:
		case SC_RACEUNDEAD:
		case SC_RACEBEAST:
		case SC_RACEPLANT:
		case SC_RACEINSECT:
		case SC_RACEFISH:
		case SC_RACEDEVIL:
		case SC_RACEHUMAN:
		case SC_RACEANGEL:
		case SC_RACEDRAGON:
			if(sd)
				clif_displaymessage(sd->fd,"種族が元に戻りました");
			break;
		case SC_RUN:			/* タイリギ */
			unit_stop_walking(bl,0);
			calc_flag = 1;
			break;
		case SC_MONK:			/* モンクの魂 */
		case SC_STAR:			/* ケンセイの魂 */
		case SC_SAGE:			/* セージの魂 */
		case SC_CRUSADER:		/* クルセイダーの魂 */
		case SC_WIZARD:			/* ウィザードの魂 */
		case SC_PRIEST:			/* プリーストの魂 */
		case SC_ROGUE:			/* ローグの魂 */
		case SC_ASSASIN:		/* アサシンの魂 */
		case SC_SOULLINKER:		/* ソウルリンカーの魂 */
		case SC_SUPERNOVICE:		/* スーパーノービスの魂 */
		case SC_GUNNER:			/* ガンスリンガーの魂 */
		case SC_NINJA:			/* 忍者の魂 */
		case SC_DEATHKINGHT:		/* デスナイトの魂 */
		case SC_COLLECTOR:		/* コレクターの魂 */
			if(sd && battle_config.disp_job_soul_state_change)
				clif_disp_onlyself(sd->fd,"魂状態が終了しました");
			break;
		case SC_KNIGHT:			/* ナイトの魂 */
		case SC_ALCHEMIST:		/* アルケミストの魂 */
		case SC_BARDDANCER:		/* バードとダンサーの魂 */
		case SC_BLACKSMITH:		/* ブラックスミスの魂 */
		case SC_HUNTER:			/* ハンターの魂 */
		case SC_HIGH:			/* 一次上位職業の魂 */
			if(sd && battle_config.disp_job_soul_state_change)
				clif_disp_onlyself(sd->fd,"魂状態が終了しました");
			calc_flag = 1;
			break;
		case SC_POEMBRAGI:			/* ブラギ */
		case SC_WHISTLE:			/* 口笛 */
		case SC_ASSNCROS:			/* 夕陽のアサシンクロス */
		case SC_APPLEIDUN:			/* イドゥンの林檎 */
		case SC_HUMMING:			/* ハミング */
		case SC_DONTFORGETME:			/* 私を忘れないで */
		case SC_FORTUNE:			/* 幸運のキス */
		case SC_SERVICE4U:			/* サービスフォーユー */
			calc_flag = 1;
			// 踊り演奏持続セット
			if(sc->data[type + SC_WHISTLE_ - SC_WHISTLE].timer == -1)
				status_change_start(bl,type + SC_WHISTLE_ - SC_WHISTLE,sc->data[type].val1,
					sc->data[type].val2,sc->data[type].val3,sc->data[type].val4,battle_config.dance_and_play_duration,0);
			break;
		case SC_WHISTLE_:			/* 口笛 */
		case SC_ASSNCROS_:			/* 夕陽のアサシンクロス */
		case SC_APPLEIDUN_:			/* イドゥンの林檎 */
		case SC_HUMMING_:			/* ハミング */
		case SC_DONTFORGETME_:			/* 私を忘れないで */
		case SC_FORTUNE_:			/* 幸運のキス */
		case SC_SERVICE4U_:			/* サービスフォーユー */
		case SC_GRAVITATION:
			calc_flag = 1;
			break;
		case SC_MARIONETTE:			/* マリオネットコントロール (自分) */
		case SC_MARIONETTE2:			/* マリオネットコントロール (相手) */
			{
				struct block_list *tbl = map_id2bl(sc->data[type].val2);
				if(tbl) {
					struct status_change *tsc = status_get_sc(tbl);
					int tmp = (type == SC_MARIONETTE)? SC_MARIONETTE2: SC_MARIONETTE;
					// 相方がマリオネット状態ならいっしょに解除
					if(tsc && tsc->data[tmp].timer != -1)
						status_change_end(tbl, tmp, -1);
				}
			}
			calc_flag = 1;
			break;
		case SC_BERSERK:			/* バーサーク */
			calc_flag = 1;
			if(sd) {
				clif_status_change(bl,SI_INCREASEAGI,0);	// アイコン消去
				status_change_start(bl,SC_NATURAL_HEAL_STOP,0,0,0,0,skill_get_time2(LK_BERSERK,sc->data[type].val1),0);
			}
			break;
		case SC_HALLUCINATION:
			if(sd)
				clif_status_change(bl,SI_HALLUCINATION,0);	// アイコン消去
			break;

		case SC_ENDURE:				/* インデュア */
		case SC_DEFENDER:			/* ディフェンダー */
			calc_flag = 1;
			// fall through
		case SC_AUTOGUARD:			/* オートガード */
		case SC_REFLECTSHIELD:			/* リフレクトシールド */
			if(sd) {
				struct map_session_data *tsd;
				int i;
				// 被ディボーション者も解除する
				for(i = 0; i < 5; i++) {
					if(sd->dev.val1[i] && (tsd = map_id2sd(sd->dev.val1[i])) != NULL && tsd->sc.data[type].timer != -1)
						status_change_end(&tsd->bl, type, -1);
				}
			}
			break;

		case SC_DEVOTION:		/* ディボーション */
			{
				struct map_session_data *dsd = map_id2sd(sc->data[type].val1);

				sc->data[type].val1 = 0;
				sc->data[type].val2 = 0;

				if(sc->data[SC_AUTOGUARD].timer != -1)
					status_change_end(bl, SC_AUTOGUARD, -1);
				if(sc->data[SC_DEFENDER].timer != -1)
					status_change_end(bl, SC_DEFENDER, -1);
				if(sc->data[SC_REFLECTSHIELD].timer != -1)
					status_change_end(bl, SC_REFLECTSHIELD, -1);
				if(sc->data[SC_ENDURE].timer != -1)
					status_change_end(bl, SC_ENDURE, -1);
				if(dsd)
					skill_devotion(dsd);
			}
			break;
		case SC_BLADESTOP:
			{
				struct block_list *tbl = map_id2bl(sc->data[type].val4);
				if(tbl) {
					struct status_change *tsc = status_get_sc(tbl);
					// 片方が切れたので相手の白刃状態が切れてないのなら解除
					if(tsc && tsc->data[SC_BLADESTOP].timer != -1)
						status_change_end(tbl,SC_BLADESTOP,-1);
					if(sc->data[type].val2 == 2)
						clif_bladestop(map_id2bl(sc->data[type].val3),tbl->id,0);
				}
			}
			break;
		case SC_CLOSECONFINE:
		case SC_STOP:
			{
				struct block_list *tbl = map_id2bl(sc->data[type].val4);
				if(tbl) {
					struct status_change *tsc = status_get_sc(tbl);
					// 片方が切れたので相手が切れてないのなら解除
					if(tsc && tsc->data[type].timer != -1)
						status_change_end(tbl,type,-1);
				}
				calc_flag = 1;
			}
			break;
		case SC_DANCING:
			{
				struct map_session_data *dsd;
				// 月明りだけここでアイコン消去
				if(sc->data[type].val1 == CG_MOONLIT)
					clif_status_change(bl,SI_MOONLIT,0);	// アイコン消去

				if(sc->data[type].val4 && (dsd = map_id2sd(sc->data[type].val4))) {
					// 合奏で相手がいる場合相手のval4を0にする
					if(dsd->sc.data[type].timer != -1)
						dsd->sc.data[type].val4 = 0;
				}
				if(sc->data[SC_LONGINGFREEDOM].timer != -1)
					status_change_end(bl,SC_LONGINGFREEDOM,-1);
			}
			calc_flag = 1;
			break;
		case SC_GOSPEL:
		case SC_GRAFFITI:
		case SC_WARM:
		case SC_GRAVITATION_USER:
			{
				struct skill_unit_group *sg = (struct skill_unit_group *)sc->data[type].val4;	// val4がgroup_id
				sc->data[type].val4 = 0;
				if(sg)
					skill_delunitgroup(sg);
			}
			break;
		case SC_NOCHAT:			/* チャット禁止状態 */
			if(sd)
				clif_updatestatus(sd,SP_MANNER);
			break;
		case SC_SPLASHER:		/* ベナムスプラッシャー */
			{
				struct block_list *src = map_id2bl(sc->data[type].val3);
				if(src && tid != -1) {
					// 自分にダメージ＆周囲3*3にダメージ
					skill_castend_damage_id(src,bl,sc->data[type].val2,sc->data[type].val1,gettick(),0);
				}
			}
			break;
		case SC_ANKLE:
			{
				struct skill_unit_group *sg = (struct skill_unit_group *)sc->data[SC_ANKLE].val2;
				// skill_delunitgroupからstatus_change_end が呼ばれない為に、
				// 一端発動していない事にしてからグループ削除する。
				if(sg) {
					sg->val2 = 0;
					skill_delunitgroup(sg);
				}
			}
			break;
		case SC_SELFDESTRUCTION:	/* 自爆 */
			unit_stop_walking(bl,5);
			if(md) {
				md->mode &= ~0x1;
				md->state.special_mob_ai = 2;
			}
			break;
		case SC_BUNSINJYUTSU:	/* 分身の術 */
			if(sd) {
				int color = sc->data[SC_BUNSINJYUTSU].val4;
				if(color > 0)
					pc_changelook(sd, LOOK_CLOTHES_COLOR, color);
			}
			break;
		case SC_SEVENWIND:	/* 暖かい風 */
			if(sd)
				clif_status_change(bl,sc->data[type].val2,0);
			break;
		case SC_AUTOBERSERK:
			if(sc->data[SC_PROVOKE].timer != -1 && sc->data[SC_PROVOKE].val2 == 1) {
				status_change_end(bl,SC_PROVOKE,-1);
			}
			break;

		/* option1 */
		case SC_FREEZE:
			sc->data[type].val3 = 0;
			break;

		/* option2 */
		case SC_POISON:				/* 毒 */
		case SC_BLIND:				/* 暗黒 */
		case SC_CURSE:
			calc_flag = 1;
			break;
	}

	if(sd && StatusIconChangeTable[type] != SI_BLANK)
		clif_status_change(bl,StatusIconChangeTable[type],0);	// アイコン消去

	switch(type) {	/* 正常に戻るときなにか処理が必要 */
		// opt1
		case SC_STONE:
		case SC_FREEZE:
		case SC_STUN:
		case SC_SLEEP:
			sc->opt1 = 0;
			opt_flag = 1;
			break;
		// opt2
		case SC_POISON:
			sc->opt2 &= ~0x00001;
			opt_flag = 1;
			break;
		case SC_CURSE:
		case SC_SILENCE:
		case SC_CONFUSION:
			sc->opt2 &= ~(1<<(type-SC_POISON));
			opt_flag = 1;
			break;
		case SC_FOGWALLPENALTY:
			if(sc->data[SC_BLIND].timer == -1) {
				sc->opt2 &= ~0x00010;
				opt_flag = 1;
			}
			break;
		case SC_BLIND:
			if(sc->data[SC_FOGWALLPENALTY].timer == -1) {
				sc->opt2 &= ~0x00010;
				opt_flag = 1;
			}
			break;
		case SC_DPOISON:
			sc->opt2 &= ~0x00080;
			opt_flag = 1;
			break;
		case SC_SIGNUMCRUCIS:
			sc->opt2 &= ~0x00040;
			opt_flag = 1;
			break;
		// opt3
		case SC_ONEHAND:		/* 1HQ */
		case SC_TWOHANDQUICKEN:		/* 2HQ */
		case SC_SPEARQUICKEN:		/* スピアクイッケン */
		case SC_CONCENTRATION:		/* コンセントレーション */
		case SC_WEAPONQUICKEN:		/* ウェポンクイッケン */
			sc->opt3 &= ~0x00001;
			opt_flag = 2;
			break;
		case SC_OVERTHRUST:		/* オーバートラスト */
		case SC_SWOO:			/* エスウ */
			sc->opt3 &= ~0x00002;
			opt_flag = 2;
			break;
		case SC_ENERGYCOAT:		/* エナジーコート */
		case SC_SKE:			/* エスク */
			sc->opt3 &= ~0x00004;
			opt_flag = 2;
			break;
		case SC_EXPLOSIONSPIRITS:	/* 爆裂波動 */
			sc->opt3 &= ~0x00008;
			opt_flag = 2;
			break;
		case SC_STEELBODY:		/* 金剛 */
		case SC_SKA:			/* エスカ */
			sc->opt3 &= ~0x00010;
			opt_flag = 2;
			break;
		case SC_BLADESTOP:		/* 白刃取り */
			sc->opt3 &= ~0x00020;
			opt_flag = 2;
			break;
		case SC_BERSERK:		/* バーサーク */
			sc->opt3 &= ~0x00080;
			opt_flag = 2;
			break;
		case SC_MARIONETTE:		/* マリオネットコントロール */
		case SC_MARIONETTE2:		/* マリオネットコントロール */
			sc->opt3 &= ~0x00400;
			opt_flag = 2;
			break;
		case SC_ASSUMPTIO:		/* アスムプティオ */
			sc->opt3 &= ~0x00800;
			opt_flag = 2;
			break;
		case SC_WARM:			/* 温もり */
			sc->opt3 &= ~0x01000;
			opt_flag = 2;
			break;
		case SC_KAITE:			/* カイト */
			sc->opt3 &= ~0x02000;
			opt_flag = 2;
			break;
		case SC_MONK:			/* モンクの魂 */
		case SC_STAR:			/* ケンセイの魂 */
		case SC_SAGE:			/* セージの魂 */
		case SC_CRUSADER:		/* クルセイダーの魂 */
		case SC_WIZARD:			/* ウィザードの魂 */
		case SC_PRIEST:			/* プリーストの魂 */
		case SC_ROGUE:			/* ローグの魂 */
		case SC_ASSASIN:		/* アサシンの魂 */
		case SC_SOULLINKER:		/* ソウルリンカーの魂 */
		case SC_KNIGHT:			/* ナイトの魂 */
		case SC_ALCHEMIST:		/* アルケミストの魂 */
		case SC_BARDDANCER:		/* バードとダンサーの魂 */
		case SC_BLACKSMITH:		/* ブラックスミスの魂 */
		case SC_HUNTER:			/* ハンターの魂 */
		case SC_HIGH:			/* 一次上位職業の魂 */
		case SC_SUPERNOVICE:		/* スーパーノービスの魂 */
		case SC_GUNNER:			/* ガンスリンガーの魂 */
		case SC_NINJA:			/* 忍者の魂 */
		case SC_DEATHKINGHT:		/* デスナイトの魂 */
		case SC_COLLECTOR:		/* コレクターの魂 */
			sc->opt3 &= ~0x08000;
			opt_flag = 2;
			break;
		// option
		case SC_SIGHT:
			sc->option &= ~0x00001;
			opt_flag = 1;
			break;
		case SC_HIDING:
			// 霞斬りでない通常のハイドならアイコン消去
			if(sd && sc->data[type].val3 == 0)
				clif_status_change(bl,SI_HIDING,0);
			sc->option &= ~0x00002;
			opt_flag = 1;
			break;
		case SC_CLOAKING:
			sc->option &= ~0x00004;
			opt_flag = 1;
			break;
		case SC_INVISIBLE:
			sc->option &= ~0x00040;
			opt_flag = 1;
			break;
		case SC_REVERSEORCISH:
			sc->option &= ~0x00800;
			opt_flag = 1;
			break;
		case SC_WEDDING:		/* ウェディング */
			sc->option &= ~0x01000;
			opt_flag = 1;
			break;
		case SC_RUWACH:
			sc->option &= ~0x02000;
			opt_flag = 1;
			break;
		case SC_CHASEWALK:		/* チェイスウォーク */
			sc->option &= ~0x04004;
			opt_flag = 1;
			break;
		case SC_FUSION:
			sc->option &= ~0x08000;
			opt_flag = 1;
			break;
	}

	/* optionの変更 */
	if(opt_flag == 1) {
		clif_changeoption(bl);
		clif_send_clothcolor(bl);
	} else if(opt_flag == 2) {
		clif_changeoption2(bl);
	}

#ifdef DYNAMIC_SC_DATA
	if(sc->count <= 0 && battle_config.free_sc_data_dynamically)
		status_free_sc_data(sc);
#endif

	/* ステータス再計算 */
	if(sd) {
		if(calc_flag || sd->auto_status_calc_pc[type] == 1) {
			status_calc_pc(sd,0);
		}
	} else if(hd) {
		if(calc_flag) {
			homun_calc_status(hd);
			clif_send_homstatus(hd->msd,0);
		}
	} else if(mcd) {
		if(calc_flag) {
			merc_calc_status(mcd);
			clif_send_mercstatus(mcd->msd,0);
		}
	}

	return 0;
}

/*==========================================
 * ステータス再計算を一時停止する
 *------------------------------------------
 */
int status_calc_pc_stop_begin(struct block_list *bl)
{
	nullpo_retr(0, bl);

	if(bl->type == BL_PC)
		((struct map_session_data *)bl)->stop_status_calc_pc++;
	return 0;
}

/*==========================================
 * ステータス再計算を再開する
 *------------------------------------------
 */
int status_calc_pc_stop_end(struct block_list *bl)
{
	nullpo_retr(0, bl);

	if(bl->type == BL_PC) {
		struct map_session_data *sd = (struct map_session_data *)bl;
		sd->stop_status_calc_pc--;
		if(sd->stop_status_calc_pc == 0 && sd->call_status_calc_pc_while_stopping > 0)
			status_calc_pc(sd,0);
		if(sd->stop_status_calc_pc < 0) {
			printf("status_calc_pc_stop_endが不正に呼び出されています\n");
		}
	}
	return 0;
}

/*==========================================
 * ステータス異常開始タイマー
 *------------------------------------------
 */
static int status_pretimer(int tid, unsigned int tick, int id, int data)
{
	struct block_list *bl = map_id2bl(id);
	struct status_pretimer *stpt = NULL;
	struct unit_data *ud;

	if(bl == NULL)
		return 0;	// 該当IDがすでに消滅している

	nullpo_retr(0, ud = unit_bl2ud(bl));

	do {
		if(bl->prev == NULL)
			break;

		stpt = (struct status_pretimer*)data;
		stpt->timer = -1;

		if(linkdb_erase(&ud->statuspretimer, stpt) == NULL) {
			printf("status_pretimer: data lost !!\n");
			break;
		}

		if(stpt->target_id) {
			struct block_list *target = map_id2bl(stpt->target_id);
			if( target == NULL || bl->m != target->m || unit_isdead(bl) || unit_isdead(target) )
				break;
		} else {
			if(bl->m != stpt->m)
				break;
		}

		status_change_start(bl, stpt->type, stpt->val1, stpt->val2, stpt->val3, stpt->val4, stpt->tick, stpt->flag);
	} while(0);

	aFree(stpt);

	return 0;
}

/*==========================================
 * ステータス異常開始タイマーの削除
 *------------------------------------------
 */
int status_clearpretimer(struct block_list *bl)
{
	struct unit_data *ud;
	struct linkdb_node *node1, *node2;

	nullpo_retr(0, bl);
	nullpo_retr(0, ud = unit_bl2ud(bl));

	node1 = ud->statuspretimer;
	while(node1) {
		struct status_pretimer *stpt = (struct status_pretimer *)node1->data;
		if(stpt->timer != -1) {
			delete_timer(stpt->timer, status_pretimer);
		}
		node2 = node1->next;
		aFree(stpt);
		node1 = node2;
	}
	linkdb_final(&ud->statuspretimer);

	return 0;
}

/*==========================================
 * ステータス異常開始タイマーのセット
 *------------------------------------------
 */
int status_change_pretimer(struct block_list *bl,int type,int val1,int val2,int val3,int val4,int tick,int flag,int pre_tick)
{
	struct unit_data *ud;
	struct status_pretimer *stpt;

	nullpo_retr(1, bl);
	nullpo_retr(1, ud = unit_bl2ud(bl));

	stpt = (struct status_pretimer *)aCalloc(1, sizeof(struct status_pretimer));
	stpt->timer     = add_timer(pre_tick, status_pretimer, bl->id, (int)stpt);
	stpt->target_id = bl->id;
	stpt->m         = bl->m;
	stpt->type      = type;
	stpt->val1      = val1;
	stpt->val2      = val2;
	stpt->val3      = val3;
	stpt->val4      = val4;
	stpt->tick      = tick;
	stpt->flag      = flag;

	linkdb_insert(&ud->statuspretimer, stpt, stpt);

	return 0;
}

/*==========================================
 * ステータス異常終了タイマー
 *
 * ソースを修正する方への注意
 *
 * ・状態異常継続時には、add_timer() した直後にreturn すること
 * ・状態異常終了時には、関数の最後にあるstatus_change_end() の
 * 　呼び出し前に return しないこと
 *
 * この２点が守られていないと、他人の状態異常が勝手に解除されたり、
 * delete_timer errorが出てくるなどのバグが発生します。
 *------------------------------------------
 */
int status_change_timer(int tid, unsigned int tick, int id, int data)
{
	int type = data;
	struct block_list *bl;
	struct map_session_data *sd  = NULL;
	struct mob_data         *md  = NULL;
	struct homun_data       *hd  = NULL;
	struct merc_data        *mcd = NULL;
	struct status_change    *sc  = NULL;

	if(type < 0 || type >= MAX_STATUSCHANGE)
		return 0;

	if((bl = map_id2bl(id)) == NULL)
		return 0;	// 該当IDがすでに消滅しているというのはいかにもありそうなのでスルーしてみる

	nullpo_retr(0, sc = status_get_sc(bl));

	sd  = BL_DOWNCAST( BL_PC,   bl );
	md  = BL_DOWNCAST( BL_MOB,  bl );
	hd  = BL_DOWNCAST( BL_HOM,  bl );
	mcd = BL_DOWNCAST( BL_MERC, bl );

	if(sc->data[type].timer != tid) {
		if(battle_config.error_log)
			printf("status_change_timer %d != %d (type = %d)\n",tid,sc->data[type].timer,type);
		return 0;
	}

	switch(type) {	/* 特殊な処理になる場合 */
	case SC_MAXIMIZEPOWER:	/* マキシマイズパワー */
	case SC_CLOAKING:	/* クローキング */
	case SC_INVISIBLE:	/* インビジブル */
		if(sd) {
			if(sd->status.sp > 0) {	/* SP切れるまで持続 */
				sd->status.sp--;
				clif_updatestatus(sd,SP_SP);
				sc->data[type].timer = add_timer(	/* タイマー再設定 */
					sc->data[type].val2+tick, status_change_timer,
					bl->id, data);
				return 0;
			}
		}
		break;

	case SC_CHASEWALK:	/* チェイスウォーク */
		if(sd) {
			int sp = 10+sc->data[SC_CHASEWALK].val1*2;
			if(map[sd->bl.m].flag.gvg)
				sp *= 5;
			if(sd->status.sp > sp) {
				sd->status.sp -= sp;
				clif_updatestatus(sd,SP_SP);
				if((++sc->data[SC_CHASEWALK].val4) == 1) {
					// ローグの魂
					if(sc->data[SC_ROGUE].timer != -1)
						status_change_start(bl, SC_CHASEWALK_STR, 1<<(sc->data[SC_CHASEWALK].val1-1), 0, 0, 0, 300000, 0);
					else
						status_change_start(bl, SC_CHASEWALK_STR, 1<<(sc->data[SC_CHASEWALK].val1-1), 0, 0, 0, 30000, 0);
					status_calc_pc(sd, 0);
				}
				sc->data[type].timer = add_timer( /* タイマー再設定 */
					sc->data[type].val2+tick, status_change_timer, bl->id, data);
				return 0;
			}
		}
		break;

	case SC_HIDING:		/* ハイディング */
		if(sd) {		/* SPがあって、時間制限の間は持続 */
			if(sd->status.sp > 0 && (--sc->data[type].val2) > 0) {
				if(sc->data[type].val2 % (sc->data[type].val1+3) == 0) {
					sd->status.sp--;
					clif_updatestatus(sd,SP_SP);
				}
				sc->data[type].timer = add_timer(	/* タイマー再設定 */
					1000+tick, status_change_timer,
					bl->id, data);
				return 0;
			}
		}
		break;

	case SC_SIGHTBLASTER:
	case SC_SIGHT:		/* サイト */
	case SC_RUWACH:		/* ルアフ */
		{
			int range;
			if(type == SC_RUWACH)
				range = 2;
			else if(type == SC_SIGHTBLASTER)
				range = 3;
			else
				range = (sc->data[type].val4 == NPC_WIDESIGHT)? 5: 3;

			map_foreachinarea(status_change_timer_sub,
				bl->m, bl->x-range, bl->y-range, bl->x+range,bl->y+range, BL_CHAR,
				bl, type, sc->data[type].val1, tick);

			if((--sc->data[type].val2) > 0) {
				sc->data[type].timer = add_timer(	/* タイマー再設定 */
					250+tick, status_change_timer,
					bl->id, data);
				return 0;
			}
		}
		break;

	case SC_SIGNUMCRUCIS:		/* シグナムクルシス */
		{
			int race = status_get_race(bl);
			if(race == RCT_DEMON || battle_check_undead(race,status_get_elem_type(bl))) {
				sc->data[type].timer = add_timer(1000*600+tick, status_change_timer, bl->id, data);
				return 0;
			}
		}
		break;

	case SC_PROVOKE:	/* プロボック/オートバーサーク */
		if(sc->data[type].val2 != 0) {	/* オートバーサーク（１秒ごとにHPチェック） */
			if(status_get_hp(bl) > status_get_max_hp(bl)>>2)	/* 停止 */
				break;
			sc->data[type].timer = add_timer(1000+tick, status_change_timer, bl->id, data);
			return 0;
		}
		break;

	case SC_DISSONANCE:	/* 不協和音 */
		if((--sc->data[type].val2) > 0) {
			struct skill_unit *unit = map_id2su(sc->data[type].val4);
			struct block_list *src;
			if(!unit || !unit->group)
				break;
			src = map_id2bl(unit->group->src_id);
			if(!src)
				break;
			battle_skill_attack(BF_MISC,src,&unit->bl,bl,unit->group->skill_id,sc->data[type].val1,tick,0);
			sc->data[type].timer = add_timer(
				skill_get_time2(unit->group->skill_id,unit->group->skill_lv)+tick, status_change_timer,
				bl->id, data);
			return 0;
		}
		break;
	case SC_UGLYDANCE:	/* 自分勝手なダンス */
		if((--sc->data[type].val2) > 0) {
			struct skill_unit *unit = map_id2su(sc->data[type].val4);
			struct block_list *src;
			if(!unit || !unit->group)
				break;
			src = map_id2bl(unit->group->src_id);
			if(!src)
				break;
			skill_additional_effect(src,bl,unit->group->skill_id,sc->data[type].val1,0,tick);
			sc->data[type].timer = add_timer(
				skill_get_time2(unit->group->skill_id,unit->group->skill_lv)+tick, status_change_timer,
				bl->id, data);
			return 0;
		}
		break;

	case SC_LULLABY:	/* 子守唄 */
		if((--sc->data[type].val2) > 0) {
			struct skill_unit *unit = map_id2su(sc->data[type].val4);
			if(!unit || !unit->group || unit->group->src_id == bl->id)
				break;
			skill_additional_effect(bl,bl,unit->group->skill_id,sc->data[type].val1,BF_LONG|BF_SKILL|BF_MISC,tick);
			sc->data[type].timer = add_timer(
				skill_get_time(unit->group->skill_id,unit->group->skill_lv)/10+tick, status_change_timer,
				bl->id, data);
			return 0;
		}
		break;

	case SC_STONE:
		if(sc->data[type].val2 != 0) {
			sc->data[type].val2 = 0;
			sc->data[type].val4 = 0;
			unit_stop_walking(bl,1);
			sc->opt1 = 1;
			clif_changeoption(bl);
			clif_send_clothcolor(bl);
			sc->data[type].timer = add_timer(1000+tick, status_change_timer, bl->id, data);
			return 0;
		}
		if((--sc->data[type].val3) > 0) {
			int hp = status_get_max_hp(bl);
			if((++sc->data[type].val4)%5 == 0 && status_get_hp(bl) > hp>>2) {
				hp = (hp < 100)? 1: hp/100;
				unit_heal(bl,-hp,0);
			}
			sc->data[type].timer = add_timer(1000+tick, status_change_timer, bl->id, data);
			return 0;
		}
		break;
	case SC_POISON:
		if(sc->data[SC_SLOWPOISON].timer == -1 && (--sc->data[type].val3) > 0) {
			int hp    = status_get_hp(bl);
			int p_dmg = status_get_max_hp(bl);
			if(hp > p_dmg>>2) {		// 最大HPの25%以上
				p_dmg = 3 + p_dmg*3/200;
				if(p_dmg >= hp)
					p_dmg = hp-1;	// 毒では死なない
				unit_heal(bl, -p_dmg, 0);
			}
		}
		if(sc->data[type].val3 > 0) {
			sc->data[type].timer = add_timer(1000+tick, status_change_timer, bl->id, data);
			return 0;
		}
		break;
	case SC_DPOISON:
		if(sc->data[SC_SLOWPOISON].timer == -1 && (--sc->data[type].val3) > 0) {
			int hp = status_get_max_hp(bl);
			if(status_get_hp(bl) > hp>>2) {
				hp = 3 + hp/50;
				unit_heal(bl, -hp, 0);
			}
		}
		if(sc->data[type].val3 > 0) {
			sc->data[type].timer = add_timer(1000+tick, status_change_timer, bl->id, data);
			return 0;
		}
		break;
	case SC_BLEED:
		if(--sc->data[type].val3 > 0) {
			int dmg = atn_rand()%600 + 200;
			if(md) {
				// mobはHP50以下にならない
				md->hp = (md->hp - dmg < 50)? 50: md->hp - dmg;
			} else {
				unit_heal(bl, -dmg, 0);
			}
			if(!unit_isdead(bl)) {
				sc->data[type].timer = add_timer(10000+tick, status_change_timer, bl->id, data);
				return 0;
			}
		}
		break;
	case SC_TENSIONRELAX:	/* テンションリラックス */
		if(sd) {		/* SPがあって、HPが満タンでなければ継続 */
			if(sd->status.sp > 12 && sd->status.max_hp > sd->status.hp) {
				if(sc->data[type].val2 % (sc->data[type].val1+3) == 0) {
					sd->status.sp -= 12;
					clif_updatestatus(sd,SP_SP);
				}
				sc->data[type].timer = add_timer(	/* タイマー再設定 */
					10000+tick, status_change_timer,
					bl->id, data);
				return 0;
			}
			if(sd->status.max_hp <= sd->status.hp)
				status_change_end(&sd->bl,SC_TENSIONRELAX,-1);
		}
		break;

	/* 時間切れ無し？？ */
	case SC_AETERNA:
	case SC_TRICKDEAD:
	case SC_MAGICPOWER:		/* 魔法力増幅 */
	case SC_REJECTSWORD:		/* リジェクトソード */
	case SC_MEMORIZE:		/* メモライズ */
	case SC_SACRIFICE:		/* サクリファイス */
	case SC_READYSTORM:
	case SC_READYDOWN:
	case SC_READYTURN:
	case SC_READYCOUNTER:
	case SC_DODGE:
	case SC_AUTOBERSERK:
	case SC_RUN:
	case SC_MARIONETTE:
	case SC_MARIONETTE2:
		sc->data[type].timer = add_timer(1000 * 600 + tick, status_change_timer, bl->id, data);
		return 0;
	case SC_MODECHANGE:
		clif_emotion(bl,1);
		sc->data[type].timer = add_timer(1500 + tick, status_change_timer, bl->id, data);
		return 0;
	case SC_LONGINGFREEDOM:
		if(sd && sd->status.sp >= 3) {
			if(--sc->data[type].val3 <= 0)
			{
				sd->status.sp -= 3;
				clif_updatestatus(sd, SP_SP);
				sc->data[type].val3 = 3;
			}
			sc->data[type].timer = add_timer(1000 + tick, status_change_timer, bl->id, data);
			return 0;
		}
		break;
	case SC_DANCING:
		if(sd) {	// ダンススキルの時間SP消費
			int s = 0, cost = 1;
			if(sc->data[type].val1 == CG_HERMODE)
				cost = 5;
			if(sd->status.sp < cost) {
				skill_stop_dancing(&sd->bl,0);
			} else if(--sc->data[type].val3 > 0) {
				switch(sc->data[type].val1) {
				case BD_RICHMANKIM:			/* ニヨルドの宴 3秒にSP1 */
				case BD_DRUMBATTLEFIELD:		/* 戦太鼓の響き 3秒にSP1 */
				case BD_RINGNIBELUNGEN:			/* ニーベルングの指輪 3秒にSP1 */
				case BD_SIEGFRIED:			/* 不死身のジークフリード 3秒にSP1 */
				case BA_DISSONANCE:			/* 不協和音 3秒でSP1 */
				case BA_ASSASSINCROSS:			/* 夕陽のアサシンクロス 3秒でSP1 */
				case DC_UGLYDANCE:			/* 自分勝手なダンス 3秒でSP1 */
				case CG_LONGINGFREEDOM:
					s = 3;
					break;
				case BD_LULLABY:			/* 子守歌 4秒にSP1 */
				case BD_ETERNALCHAOS:			/* 永遠の混沌 4秒にSP1 */
				case BD_ROKISWEIL:			/* ロキの叫び 4秒にSP1 */
				case DC_FORTUNEKISS:			/* 幸運のキス 4秒でSP1 */
					s = 4;
					break;
				case BD_INTOABYSS:			/* 深淵の中に 5秒にSP1 */
				case BA_WHISTLE:			/* 口笛 5秒でSP1 */
				case DC_HUMMING:			/* ハミング 5秒でSP1 */
				case BA_POEMBRAGI:			/* ブラギの詩 5秒でSP1 */
				case DC_SERVICEFORYOU:			/* サービスフォーユー 5秒でSP1 */
				case CG_HERMODE:			/* ヘルモードの杖 */
					s = 5;
					break;
				case BA_APPLEIDUN:			/* イドゥンの林檎 6秒でSP1 */
					s = 6;
					break;
				case DC_DONTFORGETME:			/* 私を忘れないで… 10秒でSP1 */
				case CG_MOONLIT:			/* 月明りの下で 10秒でSP1？ */
					s = 10;
					break;
				}
				if(s && (sc->data[type].val3 % s) == 0) {
					sd->status.sp -= cost;
					clif_updatestatus(sd,SP_SP);
				}
				sc->data[type].timer = add_timer(	/* タイマー再設定 */
					1000+tick, status_change_timer,
					bl->id, data);
				return 0;
			}
		}
		break;
	case SC_BERSERK:		/* バーサーク */
		{
			int dmg = (int)((atn_bignumber)status_get_max_hp(bl) * 5 / 100);
			if(status_get_hp(bl) - dmg > 100) {
				if(sd) {
					sd->status.hp -= dmg;
					clif_updatestatus(sd,SP_HP);
				} else if(hd) {
					hd->status.hp -= dmg;
					clif_send_homstatus(hd->msd,0);
				} else if(mcd) {
					mcd->status.hp -= dmg;
					clif_send_mercstatus(mcd->msd,0);
				}
				sc->data[type].timer = add_timer(	/* タイマー再設定 */
					10000+tick, status_change_timer,
					bl->id, data);
				return 0;
			}
			if(sd)       sd->status.hp  = 100;
			else if(hd)  hd->status.hp  = 100;
			else if(mcd) mcd->status.hp = 100;
		}
		break;
	case SC_NOCHAT:			/* チャット禁止状態 */
		if(sd) {
			time_t timer;
			if(++sd->status.manner && time(&timer) < (sc->data[type].val2 - 60*sd->status.manner)) {	// 開始からstatus.manner分経ってないので継続
				clif_updatestatus(sd,SP_MANNER);
				sc->data[type].timer = add_timer(	/* タイマー再設定(60秒) */
					60000+tick, status_change_timer,
					bl->id, data);
				return 0;
			}
		}
		break;
	case SC_SELFDESTRUCTION:		/* 自爆 */
		if(md && unit_iscasting(&md->bl) && md->state.special_mob_ai > 2 && md->mode&0x1 && md->speed > 0) {
			md->speed -= 5;
			if(md->speed <= 0)
				md->speed = 1;
			md->dir = sc->data[type].val4;
			unit_walktodir(&md->bl,1);	// 速度が変わるので毎回呼び出す

			/* タイマー再設定 */
			sc->data[type].timer = add_timer(100+tick, status_change_timer, bl->id, data);
			return 0;
		}
		break;
	case SC_BOSSMAPINFO:			/* 凸面鏡 */
		if(sd && --sc->data[type].val2 > 0) {
			struct mob_data *mmd = map[sd->bl.m].mvpboss;
			if(mmd == NULL)
				break;
			if(mmd->bl.prev == NULL) {
				if(sc->data[type].val3 >= 0) {
					// 倒されたので次回の出現時間をアナウンスして終了
					int diff = DIFF_TICK(mmd->last_spawntime, gettick());
					if(diff < 0)
						diff = 0;
					clif_bossmapinfo(sd, mmd->name, 0, 0, diff, 3);
					break;
				}
			} else {
				if(sc->data[type].val3 < 0) {
					// 出現したのでアナウンス
					clif_bossmapinfo(sd, mmd->name, 0, 0, 0, 2);
				}
				if(sc->data[type].val3 != mmd->bl.m || sc->data[type].val4 != mmd->bl.x + (mmd->bl.y << 16)) {
					// 出現中で座標が変化しているのでミニMAPのドットを更新
					if(mmd->bl.m == sd->bl.m) {
						clif_bossmapinfo(sd, "", mmd->bl.x, mmd->bl.y, 0, 1);
					} else {
						clif_bossmapinfo(sd, "", -1, -1, 0, 1);
					}
					sc->data[type].val3 = mmd->bl.m;
					sc->data[type].val4 = mmd->bl.x + (mmd->bl.y << 16);
				}
			}
			/* タイマー再設定 */
			sc->data[type].timer = add_timer(1000+tick, status_change_timer, bl->id, data);
			return 0;
		}
		break;
	case SC_CHANGE:		/* メンタルチェンジ */
		unit_heal(bl, -status_get_hp(bl)+10, -status_get_sp(bl)+10);	// 時間切れのときのみHP,SPが10になる
		break;
	}

	if(sd && sd->eternal_status_change[type] > 0 && !unit_isdead(&sd->bl))
	{
		sc->data[type].timer = add_timer(	/* タイマー再設定 */
			sd->eternal_status_change[type]+tick, status_change_timer,
			bl->id, data);
		return 0;
	}

	return status_change_end(bl, type, tid);
}

/*==========================================
 * ステータス異常タイマー範囲処理
 *------------------------------------------
 */
int status_change_timer_sub(struct block_list *bl, va_list ap)
{
	struct block_list *src;
	struct status_change *sc;
	int type, skilllv;
	unsigned int tick;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, src = va_arg(ap,struct block_list*));

	type    = va_arg(ap,int);
	skilllv = va_arg(ap,int);
	tick    = va_arg(ap,unsigned int);

	if(!(bl->type & (BL_PC | BL_MOB | BL_MERC)))
		return 0;

	nullpo_retr(0, sc = status_get_sc(bl));

	switch( type ) {
	case SC_SIGHT:	/* サイト */
	case SC_CONCENTRATE:
		if(sc->option & 0x06) {
			status_change_end(bl, SC_HIDING, -1);
			status_change_end(bl, SC_CLOAKING, -1);
		}
		break;
	case SC_RUWACH:	/* ルアフ */
		if(sc->option & 0x06) {
			status_change_end(bl, SC_HIDING, -1);
			status_change_end(bl, SC_CLOAKING, -1);
			if(battle_check_target(src, bl, BCT_ENEMY) > 0)
				battle_skill_attack(BF_MAGIC,src,src,bl,AL_RUWACH,skilllv,tick,0);
		}
		break;
	case SC_SIGHTBLASTER:
		if(sc->option & 0x06) {
			status_change_end(bl, SC_HIDING, -1);
			status_change_end(bl, SC_CLOAKING, -1);
		}
		if(battle_check_target(src, bl, BCT_ENEMY) > 0 && !unit_isdead(bl)) {
			struct status_change *ssc;
			battle_skill_attack(BF_MAGIC,src,src,bl,WZ_SIGHTBLASTER,skilllv,tick,0);
			ssc = status_get_sc(src);
			if(ssc) {
				ssc->data[type].val2 = 0;
			}
			status_change_end(src,SC_SIGHTBLASTER,-1);
		}
		break;
	}
	return 0;
}

/*==========================================
 * ステータス異常全解除
 *------------------------------------------
 */
int status_change_clear(struct block_list *bl,int type)
{
	struct status_change *sc;
	int i;

	nullpo_retr(0, bl);
	nullpo_retr(0, sc = status_get_sc(bl));

#ifdef DYNAMIC_SC_DATA
	if(sc->data == dummy_sc_data)
		return 0;
#endif

	if(sc->count <= 0)
		return 0;

	status_calc_pc_stop_begin(bl);
	for(i = 0; i < MAX_STATUSCHANGE; i++) {
		if(i == SC_BABY && type == 0 && unit_isdead(bl))
			continue;

		/* 異常があるならタイマーを削除する */
		if(i == SC_DANCING) {
			skill_stop_dancing(bl,0);
		} else {
			if(i == SC_BASILICA)
				skill_basilica_cancel(bl);
			status_change_end(bl,i,-1);
		}
	}
	status_calc_pc_stop_end(bl);

	sc->opt1 = 0;
	sc->opt2 = 0;
	sc->opt3 = 0;
	sc->option &= OPTION_MASK;

	if(type != 1) {
		clif_changeoption(bl);
		clif_send_clothcolor(bl);
	}

	return 0;
}

/*==========================================
 * 特定条件下におけるステータス異常解除
 *------------------------------------------
 */
int status_change_release(struct block_list *bl,int mask)
{
	struct status_change *sc;
	int i;

	nullpo_retr(0, bl);
	nullpo_retr(0, sc = status_get_sc(bl));

#ifdef DYNAMIC_SC_DATA
	if(sc->data == dummy_sc_data)
		return 0;
#endif

	if(sc->count <= 0)
		return 0;

	status_calc_pc_stop_begin(bl);
	for(i = 0; i < MAX_STATUSCHANGE; i++) {
		// 異常があって且つフラグがあるならタイマーを削除
		if( (scdata_db[i].releasable & mask) && sc->data[i].timer != -1 ) {
			if(i == SC_DANCING) {
				skill_stop_dancing(bl,0);
			} else {
				if(i == SC_BASILICA)
					skill_basilica_cancel(bl);
				status_change_end(bl,i,-1);
			}
		}
	}
	status_calc_pc_stop_end(bl);

	return 0;
}

/*==========================================
 * ステータス異常(武器の属性)終了
 *------------------------------------------
 */
int status_enchant_elemental_end(struct block_list *bl,int type)
{
	struct status_change *sc;

	nullpo_retr(0, bl);
	nullpo_retr(0, sc = status_get_sc(bl));

	if( type != SC_ENCPOISON && sc->data[SC_ENCPOISON].timer != -1 )	/* エンチャントポイズン解除 */
		status_change_end(bl,SC_ENCPOISON,-1);
	if( type != SC_ASPERSIO && sc->data[SC_ASPERSIO].timer != -1 )	/* アスペルシオ解除 */
		status_change_end(bl,SC_ASPERSIO,-1);
	if( type != SC_FLAMELAUNCHER && sc->data[SC_FLAMELAUNCHER].timer != -1 )	/* フレイムランチャ解除 */
		status_change_end(bl,SC_FLAMELAUNCHER,-1);
	if( type != SC_FROSTWEAPON && sc->data[SC_FROSTWEAPON].timer != -1 )	/* フロストウェポン解除 */
		status_change_end(bl,SC_FROSTWEAPON,-1);
	if( type != SC_LIGHTNINGLOADER && sc->data[SC_LIGHTNINGLOADER].timer != -1 )	/* ライトニングローダー解除 */
		status_change_end(bl,SC_LIGHTNINGLOADER,-1);
	if( type != SC_SEISMICWEAPON && sc->data[SC_SEISMICWEAPON].timer != -1 )	/* サイスミックウェポン解除 */
		status_change_end(bl,SC_SEISMICWEAPON,-1);
	if( type != SC_DARKELEMENT && sc->data[SC_DARKELEMENT].timer != -1 )		// 闇
		status_change_end(bl,SC_DARKELEMENT,-1);
	if( type != SC_ATTENELEMENT && sc->data[SC_ATTENELEMENT].timer != -1 )	// 念
		status_change_end(bl,SC_ATTENELEMENT,-1);
	if( type != SC_UNDEADELEMENT && sc->data[SC_UNDEADELEMENT].timer != -1 )	// 不死
		status_change_end(bl,SC_UNDEADELEMENT,-1);
	if( type != SC_SEVENWIND && sc->data[SC_SEVENWIND].timer != -1 )		/* 暖かい風解除 */
		status_change_end(bl,SC_SEVENWIND,-1);

	return 0;
}

/*==========================================
 * ステータス異常(体の属性)終了
 *------------------------------------------
 */
int status_enchant_armor_elemental_end(struct block_list *bl,int type)
{
	struct status_change *sc;

	nullpo_retr(0, bl);
	nullpo_retr(0, sc = status_get_sc(bl));

	if( type != SC_BENEDICTIO && sc->data[SC_BENEDICTIO].timer != -1 )	// 聖体
		status_change_end(bl,SC_BENEDICTIO,-1);
	if( type != SC_ELEMENTWATER && sc->data[SC_ELEMENTWATER].timer != -1 )	// 水
		status_change_end(bl,SC_ELEMENTWATER,-1);
	if( type != SC_ELEMENTGROUND && sc->data[SC_ELEMENTGROUND].timer != -1 )	// 地
		status_change_end(bl,SC_ELEMENTGROUND,-1);
	if( type != SC_ELEMENTWIND && sc->data[SC_ELEMENTWIND].timer != -1 )		// 風
		status_change_end(bl,SC_ELEMENTWIND,-1);
	if( type != SC_ELEMENTFIRE && sc->data[SC_ELEMENTFIRE].timer != -1 )		// 火
		status_change_end(bl,SC_ELEMENTFIRE,-1);
	if( type != SC_ELEMENTHOLY && sc->data[SC_ELEMENTHOLY].timer != -1 )	// 光
		status_change_end(bl,SC_ELEMENTHOLY,-1);
	if( type != SC_ELEMENTDARK && sc->data[SC_ELEMENTDARK].timer != -1 )		// 闇
		status_change_end(bl,SC_ELEMENTDARK,-1);
	if( type != SC_ELEMENTELEKINESIS && sc->data[SC_ELEMENTELEKINESIS].timer != -1 )	// 念
		status_change_end(bl,SC_ELEMENTELEKINESIS,-1);
	if( type != SC_ELEMENTPOISON && sc->data[SC_ELEMENTPOISON].timer != -1 )	// 毒
		status_change_end(bl,SC_ELEMENTPOISON,-1);
	if( type != SC_ELEMENTUNDEAD && sc->data[SC_ELEMENTUNDEAD].timer != -1 )	// 不死
		status_change_end(bl,SC_ELEMENTUNDEAD,-1);

	return 0;
}

/*==========================================
 * ステータス異常(種族変更)終了
 *------------------------------------------
 */
int status_change_race_end(struct block_list *bl,int type)
{
	struct status_change *sc;

	nullpo_retr(0, bl);
	nullpo_retr(0, sc = status_get_sc(bl));

	if( type != SC_RACEUNDEAD && sc->data[SC_RACEUNDEAD].timer != -1 )
		status_change_end(bl,SC_RACEUNDEAD,-1);
	if( type != SC_RACEBEAST && sc->data[SC_RACEBEAST].timer != -1 )
		status_change_end(bl,SC_RACEBEAST,-1);
	if( type != SC_RACEPLANT && sc->data[SC_RACEPLANT].timer != -1 )
		status_change_end(bl,SC_RACEPLANT,-1);
	if( type != SC_RACEINSECT && sc->data[SC_RACEINSECT].timer != -1 )
		status_change_end(bl,SC_RACEINSECT,-1);
	if( type != SC_RACEFISH && sc->data[SC_RACEFISH].timer != -1 )
		status_change_end(bl,SC_RACEFISH,-1);
	if( type != SC_RACEDEVIL && sc->data[SC_RACEDEVIL].timer != -1 )
		status_change_end(bl,SC_RACEDEVIL,-1);
	if( type != SC_RACEHUMAN && sc->data[SC_RACEHUMAN].timer != -1 )
		status_change_end(bl,SC_RACEHUMAN,-1);
	if( type != SC_RACEANGEL && sc->data[SC_RACEANGEL].timer != -1 )
		status_change_end(bl,SC_RACEANGEL,-1);
	if( type != SC_RACEDRAGON && sc->data[SC_RACEDRAGON].timer != -1 )
		status_change_end(bl,SC_RACEDRAGON,-1);

	return 0;
}

/*==========================================
 * ステータス異常(種族変更)終了
 *------------------------------------------
 */
int status_change_resistclear(struct block_list *bl)
{
	struct status_change *sc;

	nullpo_retr(0, bl);
	nullpo_retr(0, sc = status_get_sc(bl));

	status_calc_pc_stop_begin(bl);

	if(sc->data[SC_RESISTWATER].timer != -1)
		status_change_end(bl,SC_RESISTWATER,-1);
	if(sc->data[SC_RESISTGROUND].timer != -1)
		status_change_end(bl,SC_RESISTGROUND,-1);
	if(sc->data[SC_RESISTFIRE].timer != -1)
		status_change_end(bl,SC_RESISTFIRE,-1);
	if(sc->data[SC_RESISTWIND].timer != -1)
		status_change_end(bl,SC_RESISTWIND,-1);
	if(sc->data[SC_RESISTPOISON].timer != -1)
		status_change_end(bl,SC_RESISTPOISON,-1);
	if(sc->data[SC_RESISTHOLY].timer != -1)
		status_change_end(bl,SC_RESISTHOLY,-1);
	if(sc->data[SC_RESISTDARK].timer != -1)
		status_change_end(bl,SC_RESISTDARK,-1);
	if(sc->data[SC_RESISTTELEKINESIS].timer != -1)
		status_change_end(bl,SC_RESISTTELEKINESIS,-1);
	if(sc->data[SC_RESISTUNDEAD].timer != -1)
		status_change_end(bl,SC_RESISTUNDEAD,-1);

	status_calc_pc_stop_end(bl);

	return 0;
}

/*==========================================
 * ステータス異常(魂)開始
 *------------------------------------------
 */
int status_change_soulstart(struct block_list *bl,int val1,int val2,int val3,int val4,int tick,int flag)
{
	int type = -1;
	struct map_session_data *sd;

	nullpo_retr(0, bl);

	if(bl->type != BL_PC || (sd = (struct map_session_data *)bl) == NULL)
		return 0;

	switch(sd->s_class.job) {
		case 15:
			type = SC_MONK;
			break;
		case 25:
			type = SC_STAR;
			break;
		case 16:
			type = SC_SAGE;
		 	break;
		case 14:
			type = SC_CRUSADER;
			break;
		case 9:
			type = SC_WIZARD;
			break;
		case 8:
			type = SC_PRIEST;
			break;
		case 17:
			type = SC_ROGUE;
			break;
		case 12:
			type = SC_ASSASIN;
			break;
		case 27:
			type = SC_SOULLINKER;
			break;
		case 7:
			type = SC_KNIGHT;
			break;
		case 18:
			type = SC_ALCHEMIST;
			break;
		case 19:
		case 20:
			type = SC_BARDDANCER;
			break;
		case 10:
			type = SC_BLACKSMITH;
			break;
		case 11:
			type = SC_HUNTER;
			break;
		case 23:
			type = SC_SUPERNOVICE;
			break;
		case 28:
			type = SC_GUNNER;
			break;
		case 29:
			type = SC_NINJA;
			break;
		case 30:
			type = SC_DEATHKINGHT;
			break;
		case 31:
			type = SC_COLLECTOR;
			break;
		default:
			if(sd->s_class.upper == 1 && sd->s_class.job >= 1 && sd->s_class.job <= 6)
				type = SC_HIGH;
			break;
	}
	if(type >= 0)
		status_change_start(bl,type,val1,val2,val3,val4,tick,flag);
	return 0;
}

/*==========================================
 * ステータス異常(魂)終了
 *------------------------------------------
 */
int status_change_soulclear(struct block_list *bl)
{
	struct status_change *sc;

	nullpo_retr(0, bl);
	nullpo_retr(0, sc = status_get_sc(bl));

	if(sc->data[SC_MONK].timer != -1)
		status_change_end(bl,SC_MONK,-1);
	if(sc->data[SC_STAR].timer != -1)
		status_change_end(bl,SC_STAR,-1);
	if(sc->data[SC_SAGE].timer != -1)
		status_change_end(bl,SC_SAGE,-1);
	if(sc->data[SC_CRUSADER].timer != -1)
		status_change_end(bl,SC_CRUSADER,-1);
	if(sc->data[SC_WIZARD].timer != -1)
		status_change_end(bl,SC_WIZARD,-1);
	if(sc->data[SC_PRIEST].timer != -1)
		status_change_end(bl,SC_PRIEST,-1);
	if(sc->data[SC_ROGUE].timer != -1)
		status_change_end(bl,SC_ROGUE,-1);
	if(sc->data[SC_ASSASIN].timer != -1)
		status_change_end(bl,SC_ASSASIN,-1);
	if(sc->data[SC_SOULLINKER].timer != -1)
		status_change_end(bl,SC_SOULLINKER,-1);
	if(sc->data[SC_KNIGHT].timer != -1)
		status_change_end(bl,SC_KNIGHT,-1);
	if(sc->data[SC_ALCHEMIST].timer != -1)
		status_change_end(bl,SC_ALCHEMIST,-1);
	if(sc->data[SC_BARDDANCER].timer != -1)
		status_change_end(bl,SC_BARDDANCER,-1);
	if(sc->data[SC_BLACKSMITH].timer != -1)
		status_change_end(bl,SC_BLACKSMITH,-1);
	if(sc->data[SC_HUNTER].timer != -1)
		status_change_end(bl,SC_HUNTER,-1);
	if(sc->data[SC_HIGH].timer != -1)
		status_change_end(bl,SC_HIGH,-1);
	if(sc->data[SC_SUPERNOVICE].timer != -1)
		status_change_end(bl,SC_SUPERNOVICE,-1);
	if(sc->data[SC_GUNNER].timer != -1)
		status_change_end(bl,SC_GUNNER,-1);
	if(sc->data[SC_NINJA].timer != -1)
		status_change_end(bl,SC_NINJA,-1);
	if(sc->data[SC_DEATHKINGHT].timer != -1)
		status_change_end(bl,SC_DEATHKINGHT,-1);
	if(sc->data[SC_COLLECTOR].timer != -1)
		status_change_end(bl,SC_COLLECTOR,-1);

	return 0;
}

/*==========================================
 * ステータス異常(凍結・石化・睡眠)終了
 *------------------------------------------
 */
int status_change_attacked_end(struct block_list *bl)
{
	struct status_change *sc;

	nullpo_retr(0, bl);
	nullpo_retr(0, sc = status_get_sc(bl));

	if(sc->data[SC_FREEZE].timer != -1)
		status_change_end(bl,SC_FREEZE,-1);
	if(sc->data[SC_STONE].timer != -1 && sc->data[SC_STONE].val2 == 0)
		status_change_end(bl,SC_STONE,-1);
	if(sc->data[SC_SLEEP].timer != -1)
		status_change_end(bl,SC_SLEEP,-1);

	return 0;
}

/*==========================================
 * ステータス異常(ハイド)終了
 *------------------------------------------
 */
int status_change_hidden_end(struct block_list *bl)
{
	struct status_change *sc;

	nullpo_retr(0, bl);

	sc = status_get_sc(bl);

	if(sc && sc->option > 0) {
		if(sc->option & 0x02)
			status_change_end(bl,SC_HIDING,-1);
		if((sc->option & 0x4004) == 4)
			status_change_end(bl,SC_CLOAKING,-1);
		if((sc->option & 0x4004) == 0x4004)
			status_change_end(bl,SC_CHASEWALK,-1);
	}
	return 0;
}

/*==========================================
 * ステータス異常(マップ離脱時)終了
 *------------------------------------------
 */
int status_change_removemap_end(struct block_list *bl)
{
	struct status_change *sc;

	nullpo_retr(0, bl);

	sc = status_get_sc(bl);
	if(sc == NULL || sc->count <= 0)
		return 0;

	status_calc_pc_stop_begin(bl);

	if(sc->data[SC_BLADESTOP].timer != -1)
		status_change_end(bl, SC_BLADESTOP, -1);
	if(sc->data[SC_GRAFFITI].timer != -1)
		status_change_end(bl, SC_GRAFFITI, -1);
	if(sc->data[SC_ANKLE].timer != -1)
		status_change_end(bl, SC_ANKLE, -1);
	if(sc->data[SC_GOSPEL].timer != -1)
		status_change_end(bl, SC_GOSPEL, -1);
	if(sc->data[SC_GRAVITATION_USER].timer != -1)
		status_change_end(bl, SC_GRAVITATION_USER, -1);
	if(sc->data[SC_TRICKDEAD].timer != -1)
		status_change_end(bl, SC_TRICKDEAD, -1);
	if(sc->data[SC_RUN].timer != -1)
		status_change_end(bl, SC_RUN, -1);
	if(sc->data[SC_MARIONETTE].timer != -1)
		status_change_end(bl, SC_MARIONETTE, -1);
	if(sc->data[SC_MARIONETTE2].timer != -1)
		status_change_end(bl, SC_MARIONETTE2, -1);
	if(sc->data[SC_BASILICA].timer != -1) {
		skill_basilica_cancel(bl);
		status_change_end(bl, SC_BASILICA, -1);
	}

	if(battle_config.homun_statuschange_reset) {
		if(sc->data[SC_AVOID].timer != -1)
			status_change_end(bl, SC_AVOID, -1);
		if(sc->data[SC_CHANGE].timer != -1)
			status_change_end(bl, SC_CHANGE, -1);
		if(sc->data[SC_DEFENCE].timer != -1)
			status_change_end(bl, SC_DEFENCE, -1);
		if(sc->data[SC_BLOODLUST].timer != -1)
			status_change_end(bl, SC_BLOODLUST, -1);
		if(sc->data[SC_FLEET].timer != -1)
			status_change_end(bl, SC_FLEET, -1);
		if(sc->data[SC_SPEED].timer != -1)
			status_change_end(bl, SC_SPEED, -1);
	}
	status_calc_pc_stop_end(bl);

	return 0;
}

/*==========================================
 * データベース読み込み
 *------------------------------------------
 */
int status_readdb(void) {
	int i,j,k;
	FILE *fp;
	char line[1024],*p;

	memset(&job_db, 0, sizeof(job_db));

	// JOB補正数値１
	fp=fopen("db/job_db1.txt","r");
	if(fp==NULL){
		printf("can't read db/job_db1.txt\n");
		return 1;
	}
	i=0;
	while(fgets(line,1020,fp)){
		char *split[WT_MAX+4];
		int hp_coefficient, sp_coefficient;

		if(line[0]=='/' && line[1]=='/')
			continue;
		memset(split,0,sizeof(split));
		for(j=0,p=line;j<WT_MAX+4 && p;j++){
			split[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		if(j < 4)
			continue;
		job_db[i].max_weight_base = atoi(split[0]);

		hp_coefficient = atoi(split[1]);
		if(hp_coefficient >= 0) {
			int hp_coefficient2 = atoi(split[2]);
			int sigma = 0;
			for(j = 1; j <= MAX_LEVEL; j++) {
				// 基本HP = 35 + BaseLevel * Job倍率 + Jobボーナス
				job_db[i].hp_base[j-1] = (3500 + j * hp_coefficient2 + sigma) / 100;
				sigma += hp_coefficient * (j + 1) + 50;
				sigma -= sigma % 100;
			}
		}

		sp_coefficient = atoi(split[3]);
		if(sp_coefficient >= 0) {
			for(j = 1; j < MAX_LEVEL; j++) {
				// 基本SP = 10 + BaseLevel * Job係数
				job_db[i].sp_base[j-1] = (1000 + j * sp_coefficient) / 100;
			}
		}

		for(j=0; j<WT_MAX && split[j+4]; j++) {
			job_db[i].aspd_base[j] = atoi(split[j+4]);
		}
		if(++i >= MAX_VALID_PC_CLASS)
			break;
	}
	fclose(fp);
	printf("read db/job_db1.txt done\n");

	// 基本HP個別設定
	fp=fopen("db/job_hp_db.txt","r");
	if(fp==NULL){
		printf("can't read db/job_hp_db.txt\n");
		return 1;
	}
	i=0;
	while(fgets(line,1020,fp)){
		if(line[0]=='/' && line[1]=='/')
			continue;
		for(j=0,p=line;j<MAX_VALID_PC_CLASS && p;j++){
			if(sscanf(p,"%d",&k) == 0)
				break;
			if(job_db[j].hp_base[i] == 0) {
				// job_db1.txtでHP未設定の場合のみ補完
				job_db[j].hp_base[i] = (k > 0)? k: 1;
			}
			p=strchr(p,',');
			if(p) *p++=0;
		}
		if(++i >= MAX_LEVEL)
			break;
	}
	fclose(fp);
	printf("read db/job_hp_db.txt done\n");

	// 基本SP個別設定
	fp=fopen("db/job_sp_db.txt","r");
	if(fp==NULL){
		printf("can't read db/job_sp_db.txt\n");
		return 1;
	}
	i=0;
	while(fgets(line,1020,fp)){
		if(line[0]=='/' && line[1]=='/')
			continue;
		for(j=0,p=line;j<MAX_VALID_PC_CLASS && p;j++){
			if(sscanf(p,"%d",&k) == 0)
				break;
			if(job_db[j].sp_base[i] == 0) {
				// job_db1.txtでSP未設定の場合のみ補完
				job_db[j].sp_base[i] = (k > 0)? k: 1;
			}
			p=strchr(p,',');
			if(p) *p++=0;
		}
		if(++i >= MAX_LEVEL)
			break;
	}
	fclose(fp);
	printf("read db/job_sp_db.txt done\n");

	// JOBボーナス
	fp=fopen("db/job_db2.txt","r");
	if(fp==NULL){
		printf("can't read db/job_db2.txt\n");
		return 1;
	}
	i=0;
	while(fgets(line,1020,fp)){
		if(line[0]=='/' && line[1]=='/')
			continue;
		for(j=0,p=line;j<MAX_LEVEL && p;j++){
			if(sscanf(p,"%d",&k)==0)
				break;
			job_db[i].bonus[0][j] = k;
			job_db[i].bonus[2][j] = k;	// 養子職のボーナスは分からないので仮
			p=strchr(p,',');
			if(p) p++;
		}
		if(++i >= MAX_VALID_PC_CLASS)
			break;
	}
	fclose(fp);
	printf("read db/job_db2.txt done\n");

	// JOBボーナス2 転生職用
	fp=fopen("db/job_db2-2.txt","r");
	if(fp==NULL){
		printf("can't read db/job_db2-2.txt\n");
		return 1;
	}
	i=0;
	while(fgets(line,1020,fp)){
		if(line[0]=='/' && line[1]=='/')
			continue;
		for(j=0,p=line;j<MAX_LEVEL && p;j++){
			if(sscanf(p,"%d",&k)==0)
				break;
			job_db[i].bonus[1][j] = k;
			p=strchr(p,',');
			if(p) p++;
		}
		if(++i >= MAX_VALID_PC_CLASS)
			break;
	}
	fclose(fp);
	printf("read db/job_db2-2.txt done\n");

	// 精錬データテーブル
	for(i=0; i<MAX_WEAPON_LEVEL+1; i++) {
		refine_db[i].safety_bonus = 0;
		refine_db[i].over_bonus   = 0;
		refine_db[i].limit        = MAX_REFINE;
		for(j=0; j<MAX_REFINE; j++)
			refine_db[i].per[j] = 0;
	}
	fp=fopen("db/refine_db.txt","r");
	if(fp==NULL){
		printf("can't read db/refine_db.txt\n");
		return 1;
	}
	i=0;
	while(fgets(line,1020,fp)){
		char *split[MAX_REFINE+3];
		if(line[0]=='/' && line[1]=='/')
			continue;
		if(atoi(line) <= 0)
			continue;
		memset(split,0,sizeof(split));
		for(j=0,p=line;j<MAX_REFINE+3 && p;j++){
			split[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		refine_db[i].safety_bonus = atoi(split[0]);	// 精錬ボーナス
		refine_db[i].over_bonus   = atoi(split[1]);	// 過剰精錬ボーナス
		refine_db[i].limit        = atoi(split[2]);	// 安全精錬限界
		for(j=0; j<MAX_REFINE && split[j+3]; j++) {
			refine_db[i].per[j] = atoi(split[j+3]);
		}
		if(++i > MAX_WEAPON_LEVEL)
			break;
	}
	fclose(fp);
		printf("read db/refine_db.txt done\n");

	// サイズ補正テーブル
	for(i=0; i<MAX_SIZE_FIX; i++) {
		for(j=0; j<WT_MAX; j++)
			atkmods[i][j] = 100;
	}
	fp=fopen("db/size_fix.txt","r");
	if(fp==NULL){
		printf("can't read db/size_fix.txt\n");
		return 1;
	}
	i=0;
	while(fgets(line,1020,fp)){
		char *split[WT_MAX];
		if(line[0]=='/' && line[1]=='/')
			continue;
		if(atoi(line) <= 0)
			continue;
		memset(split,0,sizeof(split));
		for(j=0,p=line;j<WT_MAX && p;j++){
			split[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		for(j=0; j<WT_MAX && split[j]; j++) {
			atkmods[i][j] = atoi(split[j]);
		}
		if(++i > MAX_SIZE_FIX)
			break;
	}
	fclose(fp);
	printf("read db/size_fix.txt done\n");

	// ステータス異常テーブル
	memset(&scdata_db, 0, sizeof(scdata_db));
	fp=fopen("db/scdata_db.txt","r");
	if(fp==NULL){
		printf("can't read db/scdata_db.txt\n");
		return 1;
	}
	i=0;
	while(fgets(line,1020,fp)){
		char *split[5];
		if(line[0] == '/' && line[1] == '/')
			continue;
		if(line[0] == '\r' || line[0] == '\n')
			continue;
		memset(split,0,sizeof(split));
		for(j=0,p=line;j<5 && p;j++){
			split[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		j = atoi(split[0]);
		if(j < 0 || j >= MAX_STATUSCHANGE)
			continue;
		scdata_db[j].save       = (short)atoi(split[2]);
		scdata_db[j].releasable = atoi(split[3]);
		scdata_db[j].disable    = atoi(split[4]);
		i++;
	}
	fclose(fp);
	printf("read db/scdata_db.txt done (count=%d)\n",i);

#ifdef DYNAMIC_SC_DATA
	for(i=0; i<MAX_STATUSCHANGE; i++) {
		dummy_sc_data[i].timer = -1;
		dummy_sc_data[i].val1  = 0;
		dummy_sc_data[i].val2  = 0;
		dummy_sc_data[i].val3  = 0;
		dummy_sc_data[i].val4  = 0;
	}
	printf("status_readdb: enable dynamic sc_data.\n");
#endif

	return 0;
}

/*==========================================
 * スキル関係初期化処理
 *------------------------------------------
 */
int do_init_status(void)
{
	status_readdb();

	add_timer_func_list(status_change_timer);
	add_timer_func_list(status_pretimer);

	return 0;
}
