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
#include <math.h>

#include "db.h"
#include "timer.h"
#include "socket.h"
#include "nullpo.h"
#include "malloc.h"
#include "utils.h"

#include "pc.h"
#include "map.h"
#include "intif.h"
#include "clif.h"
#include "chrif.h"
#include "homun.h"
#include "itemdb.h"
#include "battle.h"
#include "mob.h"
#include "npc.h"
#include "script.h"
#include "status.h"
#include "storage.h"
#include "unit.h"
#include "skill.h"

struct homun_db homun_db[MAX_HOMUN_DB];
struct random_homun_data embryo_data[MAX_HOMUN_DB];
int embryo_default = 6001;

static int homun_exp_table[6][MAX_LEVEL];

static struct homun_skill_tree_entry {
	int id;
	int max;
	struct {
		short id,lv;
	} need[5];
	unsigned short base_level;
	int intimate;
} homun_skill_tree[MAX_HOMUN_DB][MAX_HOMSKILL_TREE];

/*==========================================
 * スキルツリー情報の検索
 *------------------------------------------
 */
static struct homun_skill_tree_entry* homun_search_skilltree(int class_, int skillid)
{
	int min = -1;
	int max = MAX_HOMSKILL_TREE;
	struct homun_skill_tree_entry *st;

	st = homun_skill_tree[class_ - HOM_ID];

	// binary search
	while(max - min > 1) {
		int mid = (min + max) / 2;
		if(st[mid].id && st[mid].id == skillid)
			return &st[mid];

		// 0のときは大とみなす
		if(st[mid].id == 0 || st[mid].id > skillid)
			max = mid;
		else
			min = mid;
	}
	return NULL;
}

/*==========================================
 * スキルのMaxLvを返す
 *------------------------------------------
 */
int homun_get_skilltree_max(int class_,int skillid)
{
	struct homun_skill_tree_entry *st;

	st = homun_search_skilltree(class_, skillid);
	if(st == NULL)
		return 0;

	return st->max;
}

/*==========================================
 * 腹減り(エモーション)
 *------------------------------------------
 */
static int homun_hungry_cry(int tid,unsigned int tick,int id,void *data)
{
	struct map_session_data *sd = map_id2sd(id);

	if(sd == NULL || sd->hd == NULL)
		return 1;

	if(sd->hd->hungry_cry_timer != tid) {
		if(battle_config.error_log)
			printf("homun_hungry_cry_timer %d != %d\n",sd->hd->hungry_cry_timer,tid);
		return 0;
	}
	sd->hd->hungry_cry_timer = -1;
	clif_emotion(&sd->hd->bl,28);
	sd->hd->hungry_cry_timer = add_timer(tick+20*1000,homun_hungry_cry,sd->bl.id,NULL);

	return 0;
}

/*==========================================
 * エサをあげる
 *------------------------------------------
 */
static int homun_food(struct map_session_data *sd)
{
	int i,t,food,class_,emotion;

	nullpo_retr(1, sd);
	nullpo_retr(1, sd->hd);

	if(sd->status.homun_id == 0)
		return 1;

	class_ = sd->hd->status.class_ - HOM_ID;
	food   = homun_db[class_].FoodID;

	i = pc_search_inventory(sd,food);
	if(i < 0) {
		clif_hom_food(sd,food,0);
		return 1;
	}
	pc_delitem(sd,i,1,0,0);
	t = sd->hd->status.hungry;
	if(t > 90) {
		sd->hd->status.intimate -= 50*battle_config.homun_intimate_rate/100;
		sd->hd->intimate        -= 50*battle_config.homun_intimate_rate/100;
		emotion = 16;
	} else if(t > 75) {
		sd->hd->status.intimate -= 30*battle_config.homun_intimate_rate/100;
		sd->hd->intimate        -= 30*battle_config.homun_intimate_rate/100;
		emotion = 19;
	} else if(t > 25) {
		sd->hd->status.intimate += 80*battle_config.homun_intimate_rate/100;
		sd->hd->intimate        += 80*battle_config.homun_intimate_rate/100;
		emotion = 2;
	} else if(t > 10) {
		sd->hd->status.intimate += 100*battle_config.homun_intimate_rate/100;
		sd->hd->intimate        += 100*battle_config.homun_intimate_rate/100;
		emotion = 2;
	} else {
		sd->hd->status.intimate += 50*battle_config.homun_intimate_rate/100;
		sd->hd->intimate        += 50*battle_config.homun_intimate_rate/100;
		emotion = 2;
	}

	if(sd->hd->status.intimate <= 0)
		sd->hd->status.intimate = 0;
	if(sd->hd->status.intimate > 100000)
		sd->hd->status.intimate = 100000;
	if(sd->hd->intimate <= 0)
		sd->hd->intimate = 0;
	if(sd->hd->intimate > 100000)
		sd->hd->intimate = 100000;
	sd->hd->status.hungry += 10;
	if(sd->hd->status.hungry > 100)
		sd->hd->status.hungry = 100;

	if(sd->hd->hungry_cry_timer != -1) {
		delete_timer(sd->hd->hungry_cry_timer,homun_hungry_cry);
		sd->hd->hungry_cry_timer = -1;
	}

	clif_emotion(&sd->hd->bl,emotion);
	clif_send_homdata(sd,2,sd->hd->status.hungry);
	clif_send_homdata(sd,1,sd->hd->intimate/100);
	clif_send_homstatus(sd,0);
	clif_hom_food(sd,food,1);

	return 0;
}

/*==========================================
 * 腹減り
 *------------------------------------------
 */
static int homun_hungry(int tid,unsigned int tick,int id,void *data)
{
	struct map_session_data *sd = map_id2sd(id);
	int interval;

	if(sd == NULL)
		return 1;
	if(!sd->status.homun_id || !sd->hd)
		return 1;

	if(sd->hd->hungry_timer != tid) {
		if(battle_config.error_log)
			printf("homun_hungry_timer %d != %d\n",sd->hd->hungry_timer,tid);
		return 0;
	}
	sd->hd->hungry_timer = -1;

	sd->hd->status.hungry--;

	if(battle_config.enable_hom_autofeed > 0) {
		if(sd->hd->status.hungry <= 25 && 
			(battle_config.enable_hom_autofeed == 1 && sd->status.autofeed&2) || battle_config.enable_hom_autofeed >= 2
		) {
			homun_food(sd);
		}
	}

	if(sd->hd->status.hungry == 0) {
		sd->hd->status.hungry = 1;	// 0にはならない
	}
	if(sd->hd->status.hungry <= 10) {	// 10以下で減り始める(泣きエモを20秒に1回出すようになる)
		int f = 0;
		if(sd->hd->intimate == sd->hd->status.intimate)
			f = 1;
		sd->hd->status.intimate -= 20*battle_config.homun_intimate_rate/100;
		clif_emotion(&sd->hd->bl,28);
		clif_send_homdata(sd,1,sd->hd->intimate/100);
		if(sd->hd->status.intimate <= 0)
			sd->hd->status.intimate = 0;
		if(f)
			sd->hd->intimate = sd->hd->status.intimate;
		if(sd->hd->hungry_cry_timer == -1)
			sd->hd->hungry_cry_timer = add_timer(tick+20*1000,homun_hungry_cry,sd->bl.id,NULL);
	} else if(sd->hd->hungry_cry_timer != -1) {
		delete_timer(sd->hd->hungry_cry_timer,homun_hungry_cry);
		sd->hd->hungry_cry_timer = -1;
	}

	clif_send_homdata(sd,2,sd->hd->status.hungry);
	// 本鯖ではここでステータスを送らないが、送らないと"ホムが腹ぺこです！"が出ない
	clif_send_homstatus(sd,0);

	interval = 60*1000;
	sd->hd->hungry_timer = add_timer(tick+interval,homun_hungry,sd->bl.id,NULL);

	return 0;
}

int homun_hungry_timer_delete(struct homun_data *hd)
{
	nullpo_retr(0, hd);

	if(hd->hungry_timer != -1) {
		delete_timer(hd->hungry_timer,homun_hungry);
		hd->hungry_timer = -1;
	}
	if(hd->hungry_cry_timer != -1) {
		delete_timer(hd->hungry_cry_timer,homun_hungry_cry);
		hd->hungry_cry_timer = -1;
	}

	return 0;
}

/*==========================================
 * 上昇ステ計算
 *------------------------------------------
 */
int homun_upstatus(struct mmo_homunstatus *hd)
{
	int class_;
	int grow_hp,grow_sp;
	short grow_str,grow_agi,grow_vit,grow_int,grow_dex,grow_luk;

	nullpo_retr(1, hd);

	class_ = hd->class_ - HOM_ID;

	grow_hp = homun_db[class_].grow_max.hp - homun_db[class_].grow_min.hp + 1;
	hd->max_hp += homun_db[class_].grow_min.hp + atn_rand()%grow_hp;
	grow_sp = homun_db[class_].grow_max.sp - homun_db[class_].grow_min.sp + 1;
	hd->max_sp += homun_db[class_].grow_min.sp + atn_rand()%grow_sp;

	//各ステータスは前回アップ時の端数分を加算して計算
	grow_str = homun_db[class_].grow_max.str - homun_db[class_].grow_min.str + 1;
	grow_str = homun_db[class_].grow_min.str + atn_rand()%grow_str;
	hd->str += (grow_str + hd->f_str) / 10;
	hd->f_str = (grow_str + hd->f_str) % 10;

	grow_agi = homun_db[class_].grow_max.agi - homun_db[class_].grow_min.agi + 1;
	grow_agi = homun_db[class_].grow_min.agi + atn_rand()%grow_agi;
	hd->agi += (grow_agi + hd->f_agi) / 10;
	hd->f_agi = (grow_agi + hd->f_agi) % 10;

	grow_vit = homun_db[class_].grow_max.vit - homun_db[class_].grow_min.vit + 1;
	grow_vit = homun_db[class_].grow_min.vit + atn_rand()%grow_vit;
	hd->vit += (grow_vit + hd->f_vit) / 10;
	hd->f_vit = (grow_vit + hd->f_vit) % 10;

	grow_int = homun_db[class_].grow_max.int_ - homun_db[class_].grow_min.int_ + 1;
	grow_int = homun_db[class_].grow_min.int_ + atn_rand()%grow_int;
	hd->int_ += (grow_int + hd->f_int) / 10;
	hd->f_int = (grow_int + hd->f_int) % 10;

	grow_dex = homun_db[class_].grow_max.dex - homun_db[class_].grow_min.dex + 1;
	grow_dex = homun_db[class_].grow_min.dex + atn_rand()%grow_dex;
	hd->dex += (grow_dex + hd->f_dex) / 10;
	hd->f_dex = (grow_dex + hd->f_dex) % 10;

	grow_luk = homun_db[class_].grow_max.luk - homun_db[class_].grow_min.luk + 1;
	grow_luk = homun_db[class_].grow_min.luk + atn_rand()%grow_luk;
	hd->luk += (grow_luk + hd->f_luk) / 10;
	hd->f_luk = (grow_luk + hd->f_luk) % 10;

	return 0;
}

/*==========================================
 * 各ステ計算
 *------------------------------------------
 */
int homun_calc_status(struct homun_data *hd)
{
	int blv,aspd_k,lv;
	double aspd;
	int aspd_rate=100,speed_rate=100,atk_rate=100,matk_rate=100,hp_rate=100,sp_rate=100;
	int flee_rate=100,def_rate=100,mdef_rate=100,critical_rate=100,hit_rate=100;

	nullpo_retr(1, hd);

	hd->atk      = 0;
	hd->matk     = 0;
	hd->hit      = 0;
	hd->flee     = 0;
	hd->def      = 0;
	hd->mdef     = 0;
	hd->critical = 0;
	hd->max_hp   = hd->status.max_hp;
	hd->max_sp   = hd->status.max_sp;
	hd->str      = hd->status.str;
	hd->agi      = hd->status.agi;
	hd->vit      = hd->status.vit;
	hd->dex      = hd->status.dex;
	hd->int_     = hd->status.int_;
	hd->luk      = hd->status.luk;
	hd->speed    = DEFAULT_WALK_SPEED;
	hd->nhealhp  = 0;
	hd->nhealsp  = 0;
	hd->hprecov_rate = 100;
	hd->sprecov_rate = 100;

	// チェンジインストラクション
	if((lv = homun_checkskill(hd,HVAN_INSTRUCT)) > 0)
	{
		hd->str  += lv - ((lv % 3 == 2)? 1 : 0);
		hd->int_ += lv - ((lv % 3 == 0)? 1 : 0);
	}
	// 脳手術
	if((lv = homun_checkskill(hd,HLIF_BRAIN)) > 0)
	{
		sp_rate += lv;
		hd->sprecov_rate += lv*3;
	}
	// アダマンティウムスキン
	if((lv = homun_checkskill(hd,HAMI_SKIN)) > 0)
	{
		hp_rate += lv*2;
		hd->def += lv*4;
		hd->hprecov_rate += lv*5;
	}
	// ステータス変化による基本パラメータ補正ホムスキル
	if(hd->sc.count > 0)
	{
		// 緊急回避
		if(hd->sc.data[SC_AVOID].timer != -1)
			speed_rate -= hd->sc.data[SC_AVOID].val1*10;
		// メンタルチェンジ
		if(hd->sc.data[SC_CHANGE].timer != -1) {
			hd->vit  += 30 * hd->sc.data[SC_CHANGE].val1;
			hd->int_ += 20 * hd->sc.data[SC_CHANGE].val1;
		}
		// ブラッドラスト
		if(hd->sc.data[SC_BLOODLUST].timer != -1)
			atk_rate += hd->sc.data[SC_BLOODLUST].val1*10+20;
		// フリットムーブ
		if(hd->sc.data[SC_FLEET].timer != -1) {
			aspd_rate -= hd->sc.data[SC_FLEET].val1*3;
			atk_rate  += 5+hd->sc.data[SC_FLEET].val1*5;
		}

		// ステータス変化による基本パラメータ補正
		if(battle_config.allow_homun_status_change)
		{
			// ゴスペルALL+20
			if(hd->sc.data[SC_INCALLSTATUS].timer != -1) {
				hd->str  += hd->sc.data[SC_INCALLSTATUS].val1;
				hd->agi  += hd->sc.data[SC_INCALLSTATUS].val1;
				hd->vit  += hd->sc.data[SC_INCALLSTATUS].val1;
				hd->int_ += hd->sc.data[SC_INCALLSTATUS].val1;
				hd->dex  += hd->sc.data[SC_INCALLSTATUS].val1;
				hd->luk  += hd->sc.data[SC_INCALLSTATUS].val1;
			}

			if(hd->sc.data[SC_INCREASEAGI].timer != -1)	// 速度増加
				hd->agi += 2+hd->sc.data[SC_INCREASEAGI].val1;

			if(hd->sc.data[SC_DECREASEAGI].timer != -1)	// 速度減少(agiはbattle.cで)
				hd->agi -= 2+hd->sc.data[SC_DECREASEAGI].val1;

			if(hd->sc.data[SC_BLESSING].timer != -1) {	// ブレッシング
				hd->str  += hd->sc.data[SC_BLESSING].val1;
				hd->dex  += hd->sc.data[SC_BLESSING].val1;
				hd->int_ += hd->sc.data[SC_BLESSING].val1;
			}
			if(hd->sc.data[SC_SUITON].timer != -1) {	// 水遁
				if(hd->sc.data[SC_SUITON].val3)
					hd->agi += hd->sc.data[SC_SUITON].val3;
				if(hd->sc.data[SC_SUITON].val4)
					hd->speed = hd->speed*2;
			}

			if(hd->sc.data[SC_GLORIA].timer != -1)	// グロリア
				hd->luk += 30;

			if(hd->sc.data[SC_QUAGMIRE].timer != -1) {	// クァグマイア
				short subagi = 0;
				short subdex = 0;
				subagi = (hd->status.agi/2 < hd->sc.data[SC_QUAGMIRE].val1*10) ? hd->status.agi/2 : hd->sc.data[SC_QUAGMIRE].val1*10;
				subdex = (hd->status.dex/2 < hd->sc.data[SC_QUAGMIRE].val1*10) ? hd->status.dex/2 : hd->sc.data[SC_QUAGMIRE].val1*10;
				if(map[hd->bl.m].flag.pvp || map[hd->bl.m].flag.gvg) {
					subagi /= 2;
					subdex /= 2;
				}
				hd->speed = hd->speed*5/3;
				hd->agi -= subagi;
				hd->dex -= subdex;
			}
		}
	}

	blv    = hd->status.base_level;
	aspd_k = homun_db[hd->status.class_-HOM_ID].aspd_k;

#ifdef PRE_RENEWAL
	hd->atk      += hd->str * 2 + blv + (hd->str / 10) * (hd->str / 10);
	hd->matk     += hd->int_+(hd->int_/ 5) * (hd->int_/ 5);
	hd->hit      += hd->dex + blv;
	hd->flee     += hd->agi + blv;
	hd->def      += hd->vit + hd->vit / 5 + blv / 10;
	hd->mdef     += hd->int_/ 5 + blv / 10;
	hd->critical += hd->luk / 3 + 1;
#else
	hd->atk      += (hd->str + hd->dex + hd->luk) / 3 + blv / 10;
	hd->matk     += hd->int_ + (hd->int_ + hd->dex + hd->luk) + blv / 10 * 2;
	hd->hit      += hd->dex + blv + 150;
	hd->flee     += hd->agi + blv + blv / 10;
	hd->def      += (hd->vit + blv / 10) * 2 + (hd->agi + blv / 10) / 2 + blv / 2;
	hd->mdef     += hd->int_/ 5 + blv / 10;
	hd->critical += hd->luk / 3 + 1;
#endif

	aspd = aspd_k - aspd_k * hd->dex / 1000 - (aspd_k * hd->agi / 250);

	// ディフェンス
	if(hd->sc.data[SC_DEFENCE].timer != -1)
		hd->def += hd->sc.data[SC_DEFENCE].val1*2;
	// オーバードスピード
	if(hd->sc.data[SC_SPEED].timer != -1)
		hd->flee = hd->flee + 10 + hd->sc.data[SC_SPEED].val1*10;
	// 補正
	if(atk_rate != 100)
		hd->atk = hd->atk*atk_rate/100;
	if(matk_rate != 100)
		hd->matk = hd->matk*matk_rate/100;
	if(hit_rate != 100)
		hd->hit = hd->hit*hit_rate/100;
	if(flee_rate != 100)
		hd->flee = hd->flee*flee_rate/100;
	if(def_rate != 100)
		hd->def = hd->def*def_rate/100;
	if(mdef_rate != 100)
		hd->mdef = hd->mdef*mdef_rate/100;
	if(critical_rate != 100)
		hd->critical = hd->critical*critical_rate/100;
	if(hp_rate != 100)
		hd->max_hp = hd->max_hp*hp_rate/100;
	if(sp_rate != 100)
		hd->max_sp = hd->max_sp*sp_rate/100;
	if(aspd_rate != 100)
		aspd = aspd*aspd_rate/100;
	if(speed_rate != 100)
		hd->speed = hd->speed*speed_rate/100;

	if(hd->max_hp <= 0)
		hd->max_hp = 1;	// mhp 0 だとクライアントエラー
	if(hd->max_sp <= 0)
		hd->max_sp = 1;

	// ASPD
	hd->aspd = (int)ceil(aspd);

	// 自然回復
	hd->nhealhp = hd->max_hp/100 + hd->vit/5 + 2;
	hd->nhealsp = (hd->int_/6)+(hd->max_sp/100)+1;
	if(hd->int_ >= 120)
		hd->nhealsp += ((hd->int_-120)>>1) + 4;
	if(hd->hprecov_rate != 100)
		hd->nhealhp = hd->nhealhp*hd->hprecov_rate/100;
	if(hd->sprecov_rate != 100)
		hd->nhealsp = hd->nhealsp*hd->sprecov_rate/100;

	homun_calc_skilltree(hd);

	return 0;
}

/*==========================================
 * 各ステ再計算
 *------------------------------------------
 */
int homun_recalc_status(struct homun_data *hd)
{
	int lv,class_;

	nullpo_retr(1, hd);

	class_ = hd->status.class_ - HOM_ID;
	hd->status.max_hp = hd->status.hp = homun_db[class_].hp;
	hd->status.max_sp = hd->status.sp = homun_db[class_].sp;
	hd->status.str  = homun_db[class_].str;
	hd->status.agi  = homun_db[class_].agi;
	hd->status.vit  = homun_db[class_].vit;
	hd->status.int_ = homun_db[class_].int_;
	hd->status.dex  = homun_db[class_].dex;
	hd->status.luk  = homun_db[class_].luk;
	hd->status.f_str = 0;
	hd->status.f_agi = 0;
	hd->status.f_vit = 0;
	hd->status.f_int = 0;
	hd->status.f_dex = 0;
	hd->status.f_luk = 0;

	for(lv=1; lv<hd->status.base_level; lv++)
	{
		homun_upstatus(&hd->status);	// ステアップ計算
		homun_calc_status(hd);		// ステータス計算
	}
	return 0;
}

/*==========================================
 * ホムンクルスIDを取得
 *------------------------------------------
 */
static int homun_get_create_homunid(void)
{
	int i = 0, j;

	while(i++ < MAX_HOMUN_DB*2) {
		j = atn_rand() % MAX_HOMUN_DB;
		if(atn_rand()%1000000 < embryo_data[j].per)
			return embryo_data[j].homunid;
	}
	return embryo_default;
}

/*==========================================
 * ホムンクルス新規作成
 *------------------------------------------
 */
int homun_create_hom(struct map_session_data *sd,int homunid)
{
	struct mmo_homunstatus hd;
	int class_ = homunid - HOM_ID;	// 作成されるホムの選定方法不明

	nullpo_retr(1, sd);

	memset(&hd, 0, sizeof(hd));

	memcpy(hd.name,homun_db[class_].jname,24);
	hd.class_       = class_ + HOM_ID;
	hd.account_id   = sd->status.account_id;
	hd.char_id      = sd->status.char_id;
	hd.base_level   = homun_db[class_].base_level;
	hd.base_exp     = 0;
	hd.max_hp       = 1;
	hd.max_sp       = 0;
	hd.status_point = 0;
	hd.skill_point  = homun_db[class_].skillpoint;	// 初期スキルポイント導入するかも…成長しないホム用

	//各ステータスアップ時の端数保存用
	hd.f_str = 0;
	hd.f_agi = 0;
	hd.f_vit = 0;
	hd.f_int = 0;
	hd.f_dex = 0;
	hd.f_luk = 0;

	// 初期ステータスをDBから埋め込み
	hd.max_hp = homun_db[class_].hp;
	hd.max_sp = homun_db[class_].sp;
	hd.str    = homun_db[class_].str;
	hd.agi    = homun_db[class_].agi;
	hd.vit    = homun_db[class_].vit;
	hd.int_   = homun_db[class_].int_;
	hd.dex    = homun_db[class_].dex;
	hd.luk    = homun_db[class_].luk;

	hd.hp = hd.max_hp;
	hd.sp = hd.max_sp;

	hd.intimate    = 2000;	// 親密度 2000/100000
	hd.hungry      = 50;	// 満腹度 50/100
	hd.incubate    = 0;
	hd.rename_flag = 0;

	if(battle_config.save_homun_temporal_intimate)
		pc_setglobalreg(sd,"HOM_TEMP_INTIMATE",hd.intimate);

	sd->state.homun_creating = 1;
	intif_create_hom(sd->status.account_id,sd->status.char_id,&hd);

	return 0;
}

static int homun_natural_heal_hp(int tid,unsigned int tick,int id,void *data);
static int homun_natural_heal_sp(int tid,unsigned int tick,int id,void *data);

/*==========================================
 *
 *------------------------------------------
 */
static int homun_data_init(struct map_session_data *sd)
{
	struct homun_data *hd;
	int i,class_;
	unsigned int tick = gettick();

	nullpo_retr(1, sd);
	nullpo_retr(1, hd = sd->hd);

	memcpy(&sd->hd->status, &sd->hom, sizeof(struct mmo_homunstatus));

	class_ = sd->hd->status.class_ - HOM_ID;

	hd->bl.m    = sd->bl.m;
	hd->bl.prev = hd->bl.next = NULL;
	hd->bl.x    = hd->ud.to_x = sd->bl.x;
	hd->bl.y    = hd->ud.to_y = sd->bl.y;
	unit_calc_pos(&hd->bl,sd->bl.x,sd->bl.y,sd->dir,2);
	hd->bl.x             = hd->ud.to_x;
	hd->bl.y             = hd->ud.to_y;
	hd->bl.id            = npc_get_new_npc_id();
	hd->dir              = sd->dir;
	hd->speed            = status_get_speed(&sd->bl);	// 歩行速度は、コール時の主人のspeedになる
	hd->bl.type          = BL_HOM;
	hd->target_id        = 0;
	hd->attackable       = 1;	// これを0にすると、クライアントから攻撃パケットを出さなくなる
	hd->limits_to_growth = 0;
	hd->msd              = sd;
	hd->view_class       = homun_db[class_].view_class;

	for(i=0; i<MAX_HOMSKILL; i++)
		hd->skillstatictimer[i] = tick;

	unit_dataset(&hd->bl);

	// 親密度
	if(battle_config.save_homun_temporal_intimate) {
		hd->intimate = pc_readglobalreg(sd,"HOM_TEMP_INTIMATE");
		if(hd->intimate == 0)	// 旧互換
			hd->intimate = hd->status.intimate;
	} else {
		hd->intimate = hd->status.intimate;
	}

#ifdef DYNAMIC_SC_DATA
	// ダミー挿入
	hd->sc.data = dummy_sc_data;
#else
	// ステータス異常の初期化
	for(i=0; i<MAX_STATUSCHANGE; i++) {
		hd->sc.data[i].timer = -1;
		hd->sc.data[i].val1  = 0;
		hd->sc.data[i].val2  = 0;
		hd->sc.data[i].val3  = 0;
		hd->sc.data[i].val4  = 0;
	}
#endif

	hd->sc.count = 0;
	hd->sc.opt1  = OPT1_NORMAL;
	hd->sc.opt2  = OPT2_NORMAL;
	hd->sc.opt3  = OPT3_NORMAL;

	hd->status.option &= OPTION_MASK;
	hd->sc.option = hd->status.option;	// optionはscに移して使う

	homun_calc_status(hd);			// ステータス計算
	map_addiddb(&hd->bl);

	hd->natural_heal_hp = add_timer(tick+HOM_NATURAL_HEAL_HP_INTERVAL,homun_natural_heal_hp,hd->bl.id,NULL);
	hd->natural_heal_sp = add_timer(tick+HOM_NATURAL_HEAL_SP_INTERVAL,homun_natural_heal_sp,hd->bl.id,NULL);
	hd->hungry_timer    = add_timer(tick+60*1000,homun_hungry,sd->bl.id,NULL);
	if(hd->status.hungry < 10)
		hd->hungry_cry_timer = add_timer(tick+20*1000,homun_hungry_cry,sd->bl.id,NULL);
	else
		hd->hungry_cry_timer = -1;
	hd->view_size = 0;

	return 0;
}

/*==========================================
 * コールホムンクルス
 *------------------------------------------
 */
int homun_callhom(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	if(sd->hd)
		return 0;

	if(sd->status.homun_id > 0 && sd->status.homun_id == sd->hom.homun_id) {
		// 作成済みなら、出す
		sd->hd = (struct homun_data *)aCalloc(1,sizeof(struct homun_data));

		if(!homun_data_init(sd) && sd->bl.prev != NULL)
		{
			if(sd->hd->status.hp <= 0) {	// 死亡
				clif_skill_fail(sd,AM_CALLHOMUN,0,0,0);
				unit_free(&sd->hd->bl,0);
				return 0;
			}
			map_addblock(&sd->hd->bl);
			mob_ai_hard_spawn( &sd->hd->bl, 1 );
			clif_spawnhom(sd->hd);
			clif_send_homdata(sd,0,0);
			clif_send_homstatus(sd,1);
			clif_send_homstatus(sd,0);
			clif_homskillinfoblock(sd);
			sd->hd->status.incubate = 1;
			homun_save_data(sd);
			skill_unit_move(&sd->hd->bl,gettick(),1);
		}
	} else if(sd->status.homun_id <= 0 && sd->state.homun_creating == 0) {
		// 初誕生なら、データ作成
		int idx = pc_search_inventory(sd,7142);	// エンブリオ所持を確認
		sd->status.homun_id = 0;
		if(idx < 0) {
			clif_skill_fail(sd,AM_CALLHOMUN,0,0,0);
			return 0;
		}
		pc_delitem(sd,idx,1,0,1);	// エンブリオ消去
		//if(atn_rand()%100<80)		// 成功率不明?
		homun_create_hom(sd,homun_get_create_homunid());
	}

	return 1;
}

/*==========================================
 * interからホムのデータ受信
 *------------------------------------------
 */
int homun_recv_homdata(int account_id,int char_id,struct mmo_homunstatus *p,int flag)
{
	struct map_session_data *sd;

	nullpo_retr(0, p);

	sd = map_id2sd(account_id);

	if(sd == NULL || sd->status.char_id != char_id || (!pc_checkskill(sd, AM_CALLHOMUN) && sd->status.homun_id == 0))
	{
		// コールホムンクルス未習得かつ未所持で無視(転生やリセットなど)
		if(flag) {
			// 新規作成時ならホムデータを削除する
			intif_delete_homdata(account_id,char_id,p->homun_id);
		}
		if(sd)
			sd->state.homun_creating = 0;
		return 0;
	}

	if(sd->status.homun_id > 0) {
		memcpy(&sd->hom,p,sizeof(struct mmo_homunstatus));
		// 生命倫理未習得時格納
		if(!pc_checkskill(sd, AM_BIOETHICS))
			sd->hom.incubate = 0;
		if(sd->hom.incubate && sd->hom.hp > 0)
		{
			if(homun_callhom(sd))
				clif_homskillinfoblock(sd);
		}
	} else if(sd->status.homun_id <= 0 && !sd->hd) {	// ホム新規作成
		memcpy(&sd->hom,p,sizeof(struct mmo_homunstatus));
		sd->status.homun_id = sd->hom.homun_id;
		homun_callhom(sd);
	}
	sd->state.homun_creating = 0;

	return 0;
}

/*==========================================
 * 安息	...エンブリオはインベントリには戻らない
 *------------------------------------------
 */
int homun_return_embryo(struct map_session_data *sd)
{
	struct homun_data *hd;

	nullpo_retr(0, sd);
	nullpo_retr(0, hd = sd->hd);

	if(sd->status.homun_id > 0) {
		// 親密度保存
		if(battle_config.save_homun_temporal_intimate)
			pc_setglobalreg(sd,"HOM_TEMP_INTIMATE",hd->intimate);
		hd->status.incubate = 0;
		homun_save_data(sd);
		unit_free(&hd->bl,0);
	}
	return 0;
}

/*==========================================
 * リザホム
 *------------------------------------------
 */
int homun_revive(struct map_session_data *sd,int skilllv)
{
	nullpo_retr(0, sd);

	if(sd->status.homun_id > 0 && sd->status.homun_id == sd->hom.homun_id) {
		if(sd->hom.hp > 0) {
			clif_skill_fail(sd,AM_RESURRECTHOMUN,0,0,0);
			return 0;
		}
	} else {
		clif_skill_fail(sd,AM_RESURRECTHOMUN,0,0,0);
		return 0;
	}
	// 蘇生時HP = 死亡時HP（≦0）+ MAXHP * (Skill Lv * 0.2)
	sd->hom.hp = sd->hom.hp + sd->hom.max_hp * skilllv / 5;
	if(sd->hom.max_hp < sd->hom.hp)
		sd->hom.hp = sd->hom.max_hp;
	homun_callhom(sd);

	return 0;
}

/*==========================================
 * ホム削除
 *------------------------------------------
 */
int homun_delete_data(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	if(sd->status.homun_id > 0 && sd->hd) {
		// 親密度保存
		if(battle_config.save_homun_temporal_intimate)
			pc_setglobalreg(sd,"HOM_TEMP_INTIMATE",2000);	// 初期値に
		unit_free(&sd->hd->bl,0);
		intif_delete_homdata(sd->status.account_id,sd->status.char_id,sd->status.homun_id);
		sd->status.homun_id = 0;
		memset(&sd->hom,0,sizeof(struct mmo_homunstatus));
		chrif_save(sd,0);
		if(sd->state.storage_flag == 1)
			storage_storage_save(sd);
	}
	return 0;
}

/*==========================================
 * ホムのメニューの応答
 *------------------------------------------
 */
int homun_menu(struct map_session_data *sd,int menunum)
{
	nullpo_retr(0, sd);

	if(!sd->hd)
		return 0;

	switch(menunum) {
		case 0:
			clif_send_homstatus(sd,0);
			break;
		case 1:
			homun_food(sd);
			break;
		case 2:
			homun_delete_data(sd);
			break;
	}
	return 0;
}

/*==========================================
 * 待機命令などで、主人の下へ移動
 *------------------------------------------
 */
int homun_return_master(struct map_session_data *sd)
{
	struct homun_data *hd;

	nullpo_retr(0, sd);
	nullpo_retr(0, hd = sd->hd);

	unit_calc_pos(&hd->bl,sd->bl.x,sd->bl.y,sd->dir,2);
	unit_walktoxy(&hd->bl,hd->ud.to_x,hd->ud.to_y);
	return 0;
}

/*==========================================
 * 名前の変更
 *------------------------------------------
 */
int homun_change_name(struct map_session_data *sd,const char *name)
{
	int i;

	nullpo_retr(1, sd);

	if(!sd->hd)
		return 1;
	if(sd->hd->status.rename_flag == 1 && battle_config.homun_rename == 0)
		return 1;

	for(i=0; i<24 && name[i]; i++) {
		if( !(name[i]&0xe0) || name[i]==0x7f )
			return 1;
	}

	unit_stop_walking(&sd->hd->bl,1);
	strncpy(sd->hd->status.name,name,24);
	sd->hd->status.name[23] = '\0';	// force \0 terminal
	homun_save_data(sd);
	clif_clearchar_area(&sd->hd->bl,0);
	clif_spawnhom(sd->hd);
	clif_send_homstatus(sd,1);
	clif_send_homstatus(sd,0);
	sd->hd->status.rename_flag = 1;
	clif_send_homstatus(sd,0);

	return 0;
}

/*==========================================
 * classを変更
 * class == -1 でホムを進化させる
 * class == 0 にすると、進化後のclassに変更
 * （進化するわけではない==ステ上昇はなどはなし）
 *------------------------------------------
 */
int homun_change_class( struct map_session_data *sd, int class_ )
{
	int new_class = 0;

	nullpo_retr(1, sd);

	if( !sd->hd )
		return 1;

	// use evolved class
	if( class_ <= 0 )
		new_class = homun_db[sd->hd->status.class_ - HOM_ID].evo_class;
	else
		new_class = class_;

	// validation
	if( new_class < HOM_ID || new_class >= HOM_ID + MAX_HOMUN_DB )
		return 1;

	// evolution mode
	if( class_ == -1 )
	{
		class_ = sd->hd->status.class_ - HOM_ID;

		// change intimate to 19
		sd->hd->intimate = 1900;

		// 進化ステータスUP
		sd->hd->status.max_hp += homun_db[class_].evo_min.hp + atn_rand()%(homun_db[class_].evo_max.hp - homun_db[class_].evo_min.hp + 1);
		sd->hd->status.max_sp += homun_db[class_].evo_min.sp + atn_rand()%(homun_db[class_].evo_max.sp - homun_db[class_].evo_min.sp + 1);
		sd->hd->status.str += homun_db[class_].evo_min.str + atn_rand()%(homun_db[class_].evo_max.str - homun_db[class_].evo_min.str + 1);
		sd->hd->status.agi += homun_db[class_].evo_min.agi + atn_rand()%(homun_db[class_].evo_max.agi - homun_db[class_].evo_min.agi + 1);
		sd->hd->status.vit += homun_db[class_].evo_min.vit + atn_rand()%(homun_db[class_].evo_max.vit - homun_db[class_].evo_min.vit + 1);
		sd->hd->status.int_ += homun_db[class_].evo_min.int_ + atn_rand()%(homun_db[class_].evo_max.int_ - homun_db[class_].evo_min.int_ + 1);
		sd->hd->status.dex += homun_db[class_].evo_min.dex + atn_rand()%(homun_db[class_].evo_max.dex - homun_db[class_].evo_min.dex + 1);
		sd->hd->status.luk += homun_db[class_].evo_min.luk + atn_rand()%(homun_db[class_].evo_max.luk - homun_db[class_].evo_min.luk + 1);
	}

	// change class
	sd->hd->status.class_ = new_class;
	sd->hd->view_class = homun_db[ new_class - HOM_ID ].view_class;

	homun_return_embryo( sd );
	homun_callhom( sd );

	return 0;
}

/*==========================================
 * スキルの検索 所有していた場合Lvが返る
 *------------------------------------------
 */
int homun_checkskill(struct homun_data *hd,int skill_id)
{
	if(hd == NULL)
		return 0;
	if(skill_id >= HOM_SKILLID)
		skill_id -= HOM_SKILLID;

	if(skill_id >= MAX_HOMSKILL)
		return 0;
	if(hd->status.skill[skill_id].id == skill_id + HOM_SKILLID)
		return hd->status.skill[skill_id].lv;

	return 0;
}

/*==========================================
 * スキルポイント割り振り
 *------------------------------------------
 */
void homun_skillup(struct map_session_data *sd, int skill_num)
{
	struct homun_data *hd;
	int skillid;

	nullpo_retv(sd);
	nullpo_retv(hd = sd->hd);

	skillid = skill_num - HOM_SKILLID;
	if(skillid < 0 || skillid >= HOM_SKILLID)
		return;

	if( hd->status.skill_point > 0 &&
	    hd->status.skill[skillid].id != 0 &&
	    hd->status.skill[skillid].lv < homun_get_skilltree_max(hd->status.class_,skill_num) )
	{
		hd->status.skill[skillid].lv++;
		hd->status.skill_point--;
		homun_calc_skilltree(hd);
		clif_homskillup(sd,skill_num);
		clif_send_homstatus(hd->msd,0);
		clif_homskillinfoblock(hd->msd);
	}

	return;
}

/*==========================================
 * 覚えられるスキルの計算
 *------------------------------------------
 */
int homun_calc_skilltree(struct homun_data *hd)
{
	int i, id, c, flag;

	nullpo_retr(0, hd);

	c = hd->status.class_ - HOM_ID;

	for(i=0; i<MAX_HOMSKILL; i++) {
		hd->status.skill[i].id = 0;
		if(hd->status.skill[i].flag) {		// cardスキルなら
			hd->status.skill[i].lv   = (hd->status.skill[i].flag == 1)? 0: hd->status.skill[i].flag-2;	// 本当のlvに
			hd->status.skill[i].flag = 0;	// flagは0にしておく
		}
	}

	do {
		flag = 0;
		for(i=0; (id = homun_skill_tree[c][i].id) > 0; i++) {
			id -= HOM_SKILLID;
			if(hd->status.skill[id].id > 0)
				continue;
			if(!battle_config.skillfree) {
				int j, fail = 0;
				for(j=0; j<5 && homun_skill_tree[c][i].need[j].id > 0; j++) {
					if(homun_checkskill(hd,homun_skill_tree[c][i].need[j].id) < homun_skill_tree[c][i].need[j].lv) {
						fail = 1;
						break;
					}
				}
				if(fail)
					continue;
				if(hd->status.base_level < homun_skill_tree[c][i].base_level ||
				   hd->status.intimate < homun_skill_tree[c][j].intimate)
					continue;
			}
			hd->status.skill[id].id = id + HOM_SKILLID;
			flag = 1;
		}
	} while(flag);

	return 0;
}

/*==========================================
 * レベルアップ
 *------------------------------------------
 */
static int homun_checkbaselevelup(struct homun_data *hd)
{
	int next = homun_nextbaseexp(hd);

	nullpo_retr(0, hd);

	if(hd->status.base_exp >= next && next > 0) {
		// base側レベルアップ処理
		hd->status.base_exp -= next;

		hd->status.base_level++;
		//hd->status.status_point += 15 + (hd->status.base_level+14)/3;	// 微調整してもうまくいかず・・・
		if(hd->status.base_level%3 == 0)	// 3レベル毎にSkillPoint加算
			hd->status.skill_point++;

		homun_upstatus(&hd->status);	// ステアップ計算
		homun_calc_status(hd);			// ステータス計算
		homun_heal(hd,hd->max_hp,hd->max_sp);
		clif_misceffect2(&hd->bl,568);
		if(hd->msd) {
			clif_send_homstatus(hd->msd,0);
			clif_homskillinfoblock(hd->msd);
		}
		return 1;
	}

	return 0;
}

/*==========================================
 * 経験値取得
 *------------------------------------------
 */
int homun_gainexp(struct homun_data *hd,struct mob_data *md,atn_bignumber base_exp,atn_bignumber job_exp)
{
	nullpo_retr(0, hd);

	if(hd->bl.prev == NULL || unit_isdead(&hd->bl))
		return 0;

	if(md && md->sc.data[SC_RICHMANKIM].timer != -1) {
		base_exp = base_exp * (125 + md->sc.data[SC_RICHMANKIM].val1*11)/100;
		job_exp  = job_exp  * (125 + md->sc.data[SC_RICHMANKIM].val1*11)/100;
	}

	if(hd->msd) {	// 主人へ指定倍の経験値
		atn_bignumber mbexp = 0, mjexp = 0;
		if(battle_config.master_get_homun_base_exp)
			mbexp = base_exp * battle_config.master_get_homun_base_exp / 100;
		if(battle_config.master_get_homun_job_exp)
			mjexp = job_exp  * battle_config.master_get_homun_job_exp / 100;

		if(mbexp || mjexp)
			pc_gainexp(hd->msd,md,mbexp,mjexp,0);
	}

	if(base_exp > 0) {
		atn_bignumber next = homun_nextbaseexp(hd);
		int per = battle_config.next_exp_limit;

		if(next > 0) {
			if(per <= 0) {
				// 本鯖仕様の取得経験値上限
				atn_bignumber limit_exp = next * 2 - hd->status.base_exp - 1;
				if(base_exp > limit_exp)
					base_exp = limit_exp;
			}
			while(next > 0 && base_exp + hd->status.base_exp >= next) {	// LvUP
				if(battle_config.next_exp_limit > 0) {
					int rate = (int)(100 - (atn_bignumber)hd->status.base_exp * 100 / next);
					if(per < rate)
						break;
					per -= rate;
				}
				base_exp = base_exp + hd->status.base_exp - next;
				hd->status.base_exp = (int)next;
				homun_checkbaselevelup(hd);
				next = homun_nextbaseexp(hd);
			}
		}
		if(next > 0 && battle_config.next_exp_limit > 0 && (base_exp * 100 / next) > per)
			hd->status.base_exp = (int)(next * per / 100);
		else if (base_exp + hd->status.base_exp > 0x7fffffff)
			hd->status.base_exp = 0x7fffffff;
		else
			hd->status.base_exp += (int)base_exp;

		if(hd->status.base_exp < 0)
			hd->status.base_exp = 0;
		homun_checkbaselevelup(hd);
		if(hd->msd)
			clif_send_homstatus(hd->msd,0);
	}

	return 0;
}

/*==========================================
 * base level側必要経験値計算
 *------------------------------------------
 */
int homun_nextbaseexp(struct homun_data *hd)
{
	int i;

	nullpo_retr(0, hd);

	if(hd->status.base_level >= MAX_LEVEL || hd->status.base_level <= 0)
		return 0;

	i = homun_db[hd->status.class_-HOM_ID].exp_table;
	/*
	if(hd->status.class_ >= 6001 && hd->status.class_ < 6005) i=0;		// 第一期ホム（4種）
	else if(hd->status.class_ >= 6005 && hd->status.class_ < 6009) i=1;	// 第二期ホム（4種）
	else if(hd->status.class_ >= 6009 && hd->status.class_ < 6013) i=2;	// 第一期ホム進化（4種）
	else if(hd->status.class_ >= 6013 && hd->status.class_ < 6017) i=3;	// 第二期ホム進化（4種）
	else  i=0;		// その他？
	*/
	return homun_exp_table[i][hd->status.base_level-1];
}

/*==========================================
 * hdにdamageのダメージ
 *------------------------------------------
 */
int homun_damage(struct block_list *src,struct homun_data *hd,int damage)
{
	struct map_session_data *sd = NULL;

	nullpo_retr(0, hd);
	nullpo_retr(0, sd = hd->msd);

	// 既に死んでいたら無効
	if(unit_isdead(&hd->bl))
		return 0;

	// 歩いていたら足を止める
	unit_stop_walking(&hd->bl,battle_config.pc_hit_stop_type);

	if(damage > 0 && hd->sc.data[SC_GRAVITATION_USER].timer != -1)
		status_change_end(&hd->bl, SC_GRAVITATION_USER, -1);

	if(hd->bl.prev == NULL) {
		if(battle_config.error_log)
			printf("homun_damage : BlockError!!\n");
		return 0;
	}

	if(hd->status.hp > hd->max_hp)
		hd->status.hp = hd->max_hp;

	// over kill分は丸める
	if(damage > hd->status.hp)
		damage = hd->status.hp;

	hd->status.hp -= damage;

	// ハイド状態を解除
	status_change_hidden_end(&hd->bl);

	clif_send_homstatus(sd,0);

	// 死亡していた
	if(hd->status.hp <= 0) {
		if(battle_config.save_homun_temporal_intimate)
			pc_setglobalreg(sd,"HOM_TEMP_INTIMATE",hd->intimate);
		// スキルユニットからの離脱
		hd->status.hp = 1;
		skill_unit_move(&hd->bl,gettick(),0);
		hd->status.hp = 0;

		hd->status.incubate = 0;
		unit_free(&hd->bl,1);
	}
	return 0;
}

/*==========================================
 * HP/SP回復
 *------------------------------------------
 */
int homun_heal(struct homun_data *hd,int hp,int sp)
{
	nullpo_retr(0, hd);

	// バーサーク中は回復させない
	if(hd->sc.data[SC_BERSERK].timer != -1) {
		if(sp > 0)
			sp = 0;
		if(hp > 0)
			hp = 0;
	}

	if(hp + hd->status.hp > hd->max_hp)
		hp = hd->max_hp - hd->status.hp;
	if(sp + hd->status.sp > hd->max_sp)
		sp = hd->max_sp - hd->status.sp;
	hd->status.hp += hp;
	if(hd->status.hp <= 0) {
		hd->status.hp = 0;
		homun_damage(NULL,hd,1);
		hp = 0;
	}
	hd->status.sp += sp;
	if(hd->status.sp <= 0)
		hd->status.sp = 0;
	if((hp || sp) && hd->msd)
		clif_send_homstatus(hd->msd,0);

	return hp + sp;
}

/*==========================================
 * sdが連れているホムンクルスは有効か
 *------------------------------------------
 */
int homun_isalive(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	if(sd->status.homun_id == 0 || sd->hd == NULL)	// ホムを持ってない
		return 0;
	if(sd->hd->status.hp <= 0)	// ホムが死んでる
		return 0;
	if(sd->hd->status.incubate == 0)	// ホムを出してない
		return 0;

	return 1;
}

/*==========================================
 * 自然回復物
 *------------------------------------------
 */
static int homun_natural_heal_hp(int tid,unsigned int tick,int id,void *data)
{
	struct homun_data *hd = map_id2hd(id);
	int bhp;

	nullpo_retr(0, hd);

	if(hd->natural_heal_hp != tid) {
		if(battle_config.error_log)
			printf("homun_natural_heal_hp %d != %d\n",hd->natural_heal_hp,tid);
		return 0;
	}
	hd->natural_heal_hp = -1;

	bhp = hd->status.hp;

	if(hd->ud.walktimer == -1) {
		hd->status.hp += hd->nhealhp;
		if(hd->status.hp > hd->max_hp)
			hd->status.hp = hd->max_hp;
		if(bhp != hd->status.hp && hd->msd)
			clif_send_homstatus(hd->msd,0);
	}
	hd->natural_heal_hp = add_timer(tick+HOM_NATURAL_HEAL_HP_INTERVAL,homun_natural_heal_hp,hd->bl.id,NULL);

	return 0;
}

static int homun_natural_heal_sp(int tid,unsigned int tick,int id,void *data)
{
	struct homun_data *hd = map_id2hd(id);
	int bsp;

	nullpo_retr(0, hd);

	if(hd->natural_heal_sp != tid) {
		if(battle_config.error_log)
			printf("homun_natural_heal_sp %d != %d\n",hd->natural_heal_sp,tid);
		return 0;
	}
	hd->natural_heal_sp = -1;

	bsp = hd->status.sp;

	if(hd->intimate < hd->status.intimate)
	{
		hd->intimate += battle_config.homun_temporal_intimate_resilience;
		if(hd->status.intimate < hd->intimate)
			hd->intimate = hd->status.intimate;
		clif_send_homdata(hd->msd,1,hd->intimate/100);
	}

	if(hd->ud.walktimer == -1) {
		hd->status.sp += hd->nhealsp;
		if(hd->status.sp > hd->max_sp)
			hd->status.sp = hd->max_sp;
		if(bsp != hd->status.sp && hd->msd)
			clif_send_homstatus(hd->msd,0);
	}
	hd->natural_heal_sp = add_timer(tick+HOM_NATURAL_HEAL_SP_INTERVAL,homun_natural_heal_sp,hd->bl.id,NULL);

	return 0;
}

int homun_natural_heal_timer_delete(struct homun_data *hd)
{
	nullpo_retr(0, hd);

	if(hd->natural_heal_hp != -1) {
		delete_timer(hd->natural_heal_hp,homun_natural_heal_hp);
		hd->natural_heal_hp = -1;
	}
	if(hd->natural_heal_sp != -1) {
		delete_timer(hd->natural_heal_sp,homun_natural_heal_sp);
		hd->natural_heal_sp = -1;
	}

	return 0;
}

/*==========================================
 * ホムのデータをセーブ
 *------------------------------------------
 */
int homun_save_data(struct map_session_data *sd)
{
	struct homun_data *hd;

	nullpo_retr(0, sd);
	nullpo_retr(0, hd = sd->hd);

	if(battle_config.save_homun_temporal_intimate)
		pc_setglobalreg(sd,"HOM_TEMP_INTIMATE",hd->intimate);

	// optionのコピー
	hd->status.option = hd->sc.option;

	memcpy(&sd->hom,&hd->status,sizeof(struct mmo_homunstatus));
	intif_save_homdata(sd->status.account_id,&sd->hd->status);

	return 0;
}

//
// 初期化物
//
/*==========================================
 * ホムンクルス初期ステータスデータ読み込み
 *------------------------------------------
 */
static int read_homundb(void)
{
	FILE *fp;
	char line[4096];
	int i, j;
	int lines, count = 0;
	int nameid;
	char *str[33],*p,*np;
	struct script_code *script = NULL;
	const char *filename[] = { "db/homun_db.txt", "db/addon/homun_db_add.txt" };
	const char *filename2;

	// DB情報の初期化
	for(i=0; i<MAX_HOMUN_DB; i++) {
		if(homun_db[i].script)
			script_free_code(homun_db[i].script);
	}
	memset(homun_db, 0, sizeof(homun_db));

	for(i = 0; i < 2; i++) {
		fp = fopen(filename[i], "r");
		if(fp == NULL) {
			if(i > 0)
				continue;
			printf("read_homundb: open [%s] failed !\n", filename[i]);
			return -1;
		}
		lines=count=0;
		while(fgets(line,sizeof(line),fp)){
			lines++;

			if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
				continue;
			if(line[0] == '/' && line[1] == '/')
				continue;

			for(j=0,p=line;j<32;j++){
				if((np=strchr(p,','))!=NULL){
					str[j]=p;
					*np=0;
					p=np+1;
				} else {
					str[j]=p;
					p+=strlen(p);
				}
			}

			nameid = atoi(str[0]);
			j = nameid - HOM_ID;

			if(j < 0 || j >= MAX_HOMUN_DB)
				continue;

			homun_db[j].class_     = nameid;
			homun_db[j].view_class = atoi(str[1]);
			strncpy(homun_db[j].name,str[2],24);
			strncpy(homun_db[j].jname,str[3],24);
			homun_db[j].base_level = atoi(str[4]);
			homun_db[j].AcceID     = atoi(str[5]);
			homun_db[j].FoodID     = atoi(str[6]);
			homun_db[j].hp         = atoi(str[7]);
			homun_db[j].sp         = atoi(str[8]);
			homun_db[j].str        = atoi(str[9]);
			homun_db[j].agi        = atoi(str[10]);
			homun_db[j].vit        = atoi(str[11]);
			homun_db[j].int_       = atoi(str[12]);
			homun_db[j].dex        = atoi(str[13]);
			homun_db[j].luk        = atoi(str[14]);

			//homun_db[j].base       = atoi(str[15]);
			//homun_db[j].hp_kmax    = atoi(str[16]);
			//homun_db[j].hp_kmin    = atoi(str[17]);
			//homun_db[j].sp_kmax    = atoi(str[18]);
			//homun_db[j].sp_kmin    = atoi(str[19]);
			//homun_db[j].str_k      = atoi(str[20]);
			//homun_db[j].agi_k      = atoi(str[21]);
			//homun_db[j].vit_k      = atoi(str[22]);
			//homun_db[j].int_k      = atoi(str[23]);
			//homun_db[j].dex_k      = atoi(str[24]);
			//homun_db[j].luk_k      = atoi(str[25]);
			homun_db[j].aspd_k     = atoi(str[26]);
			homun_db[j].size       = atoi(str[27]);
			homun_db[j].race       = atoi(str[28]);
			homun_db[j].element    = atoi(str[29]);
			homun_db[j].evo_class  = atoi(str[30]);
			homun_db[j].exp_table  = atoi(str[31]);
			homun_db[j].skillpoint = homun_db[j].base_level/3; // 予約 とりあえずベース/3

			// force \0 terminal
			homun_db[j].name[23]  = '\0';
			homun_db[j].jname[23] = '\0';

			count++;

			if((np = strchr(p, '{')) == NULL)
				continue;

			if(!parse_script_line_end(np, filename[i], lines))
				continue;

			if(homun_db[j].script) {
				script_free_code(homun_db[j].script);
			}
			script = parse_script(np, filename[i], lines);
			homun_db[j].script = (script_is_error(script))? NULL: script;
		}
		fclose(fp);
		printf("read %s done (count=%d)\n", filename[i], count);
	}

	filename2 = "db/homun_db2.txt";
	fp = fopen(filename2, "r");
	if(fp == NULL) {
		printf("read_homundb: open [%s] failed !\n", filename2);
		return -1;
	}
	lines=count=0;
	while(fgets(line,sizeof(line),fp)){
		lines++;

		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0] == '/' && line[1] == '/')
			continue;

		for(j=0,p=line;j<33;j++){
			if((np=strchr(p,','))!=NULL){
				str[j]=p;
				*np=0;
				p=np+1;
			} else {
				str[j]=p;
				p+=strlen(p);
			}
		}

		nameid = atoi(str[0]);
		j = nameid - HOM_ID;

		if(j < 0 || j >= MAX_HOMUN_DB || homun_db[j].class_ != nameid)
			continue;

		homun_db[j].grow_min.hp   = atoi(str[1]);
		homun_db[j].grow_max.hp   = atoi(str[2]);
		homun_db[j].grow_min.sp   = atoi(str[3]);
		homun_db[j].grow_max.sp   = atoi(str[4]);
		homun_db[j].grow_min.str  = atoi(str[5]);
		homun_db[j].grow_max.str  = atoi(str[6]);
		homun_db[j].grow_min.agi  = atoi(str[7]);
		homun_db[j].grow_max.agi  = atoi(str[8]);
		homun_db[j].grow_min.vit  = atoi(str[9]);
		homun_db[j].grow_max.vit  = atoi(str[10]);
		homun_db[j].grow_min.int_ = atoi(str[11]);
		homun_db[j].grow_max.int_ = atoi(str[12]);
		homun_db[j].grow_min.dex  = atoi(str[13]);
		homun_db[j].grow_max.dex  = atoi(str[14]);
		homun_db[j].grow_min.luk  = atoi(str[15]);
		homun_db[j].grow_max.luk  = atoi(str[16]);
		homun_db[j].evo_min.hp    = atoi(str[17]);
		homun_db[j].evo_max.hp    = atoi(str[18]);
		homun_db[j].evo_min.sp    = atoi(str[19]);
		homun_db[j].evo_max.sp    = atoi(str[20]);
		homun_db[j].evo_min.str   = atoi(str[21]);
		homun_db[j].evo_max.str   = atoi(str[22]);
		homun_db[j].evo_min.agi   = atoi(str[23]);
		homun_db[j].evo_max.agi   = atoi(str[24]);
		homun_db[j].evo_min.vit   = atoi(str[25]);
		homun_db[j].evo_max.vit   = atoi(str[26]);
		homun_db[j].evo_min.int_  = atoi(str[27]);
		homun_db[j].evo_max.int_  = atoi(str[28]);
		homun_db[j].evo_min.dex   = atoi(str[29]);
		homun_db[j].evo_max.dex   = atoi(str[30]);
		homun_db[j].evo_min.luk   = atoi(str[31]);
		homun_db[j].evo_max.luk   = atoi(str[32]);

		count++;
	}
	fclose(fp);
	printf("read %s done (count=%d)\n", filename2, count);

	return 0;
}

/*==========================================
 * 設定ファイル読み込む
 * exp.txt 必要経験値
 * homun_skill_tree.txt スキルツリー
 *------------------------------------------
 */
static int homun_readdb(void)
{
	int i,j,k,class_=0;
	FILE *fp;
	char line[1024],*p;
	const char *filename;

	// 必要経験値読み込み
	memset(homun_exp_table, 0, sizeof(homun_exp_table));
	filename = "db/exp_homun.txt";
	fp = fopen(filename, "r");
	if(fp == NULL) {
		printf("homun_readdb: open [%s] failed !\n", filename);
		return 1;
	}
	i=0;
	while(fgets(line,1020,fp)){
		int b0,b1,b2,b3,b4,b5;
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0]=='/' && line[1]=='/')
			continue;
		if(sscanf(line,"%d,%d,%d,%d,%d,%d",&b0,&b1,&b2,&b3,&b4,&b5) != 6)
			continue;
		homun_exp_table[0][i] = b0;
		homun_exp_table[1][i] = b1;
		homun_exp_table[2][i] = b2;
		homun_exp_table[3][i] = b3;
		homun_exp_table[4][i] = b4;
		homun_exp_table[5][i] = b5;
		i++;
		if(i > MAX_LEVEL)
			break;
	}
	fclose(fp);
	printf("read %s done\n", filename);

	// スキルツリー
	memset(homun_skill_tree,0,sizeof(homun_skill_tree));
	filename = "db/homun_skill_tree.txt";
	fp = fopen(filename, "r");
	if(fp == NULL) {
		printf("homun_readdb: open [%s] failed !\n", filename);
		return 1;
	}
	while(fgets(line,1020,fp)){
		int skillid;
		char *split[15];
		struct homun_skill_tree_entry *st;

		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0]=='/' && line[1]=='/')
			continue;
		for(j=0,p=line;j<15 && p;j++){
			split[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		if(j < 15)
			continue;
		class_ = atoi(split[0]);
		i = class_ - HOM_ID;
		if(i < 0 || i >= MAX_HOMUN_DB)
			continue;

		skillid = atoi(split[1]);
		if(skillid < HOM_SKILLID || skillid >= MAX_HOM_SKILLID)
			continue;

		st = homun_skill_tree[i];
		for(j=0; st[j].id && st[j].id != skillid; j++);

		if(j >= MAX_HOMSKILL_TREE - 1) {
			// 末尾はアンカーとして0にしておく必要がある
			printf("homun_readdb: skill (%d) is over max tree %d!!\n", skillid, MAX_HOMSKILL_TREE);
			continue;
		}
		if(j > 0 && skillid < st[j-1].id) {
			// スキルIDの昇順に並んでない場合
			int max = j;
			while(j > 0 && skillid < st[j-1].id) {
				j--;
			}
			memmove(&st[j+1], &st[j], (max-j)*sizeof(st[0]));
		}

		st[j].id  = skillid;
		st[j].max = atoi(split[2]);

		if(st[j].max > skill_get_max(skillid))
			st[j].max = skill_get_max(skillid);

		for(k=0; k<5; k++) {
			st[j].need[k].id = atoi(split[k*2+3]);
			st[j].need[k].lv = atoi(split[k*2+4]);
		}
		st[j].base_level = atoi(split[13]);
		st[j].intimate   = atoi(split[14]);
	}
	fclose(fp);
	printf("read %s done\n", filename);

	return 0;
}

/*==========================================
 * エンブリオデータの読み込み
 *------------------------------------------
 */
static int homun_read_embryodb(void)
{
	FILE *fp;
	char line[1024];
	int ln=0,count=0;
	int homunid,j;
	char *str[10],*p;
	const char *filename = "db/embryo_db.txt";

	// 読み込む度、初期化
	embryo_default = 6001;
	memset(embryo_data, 0, sizeof(embryo_data));

	if( (fp = fopen(filename, "r")) == NULL ) {
		printf("homun_read_embryodb: open [%s] failed !\n", filename);
		return 1;
	}

	while(fgets(line,1020,fp)){
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0]=='/' && line[1]=='/')
			continue;
		memset(str,0,sizeof(str));
		for(j=0,p=line;j<3 && p;j++){
			str[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}

		if(str[0] == NULL)
			continue;

		homunid = atoi(str[0]);
		if(homunid == 0) {
			if(str[2])
				embryo_default = atoi(str[2]);
			continue;
		}
		ln = homunid - HOM_ID;
		if(ln < 0 || ln >= MAX_HOMUN_DB)
			continue;
		if(str[2]) {
			embryo_data[ln].homunid = homunid;
			embryo_data[ln].per     = atoi(str[2]);
			count++;
		}
	}
	fclose(fp);
	printf("read %s done (count=%d)\n", filename, count);

	return 0;
}

/*==========================================
 * ホムDBのリロード
 *------------------------------------------
 */
void homun_reload(void)
{
	read_homundb();
	homun_readdb();
	homun_read_embryodb();
}

/*==========================================
 * 初期化処理
 *------------------------------------------
 */
int do_init_homun(void)
{
	read_homundb();
	homun_readdb();
	homun_read_embryodb();

	add_timer_func_list(homun_natural_heal_hp);
	add_timer_func_list(homun_natural_heal_sp);
	add_timer_func_list(homun_hungry);
	add_timer_func_list(homun_hungry_cry);

	return 0;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
int do_final_homun(void)
{
	int i;

	for(i = 0; i < MAX_HOMUN_DB; i++) {
		if(homun_db[i].script) {
			script_free_code(homun_db[i].script);
		}
	}
	return 0;
}
