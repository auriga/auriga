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
#include <time.h>

#include "db.h"
#include "timer.h"
#include "socket.h"
#include "nullpo.h"
#include "malloc.h"
#include "utils.h"
#include "mmo.h"

#include "battle.h"
#include "clif.h"
#include "chrif.h"
#include "intif.h"
#include "map.h"
#include "merc.h"
#include "mob.h"
#include "npc.h"
#include "pc.h"
#include "skill.h"
#include "status.h"
#include "storage.h"
#include "unit.h"

struct merc_db merc_db[MAX_MERC_DB];

static struct merc_skill_tree_entry {
	int id;
	int max;
} merc_skill_tree[MAX_MERC_DB][MAX_MERCSKILL_TREE];

static int merc_count;

/*==========================================
 * 傭兵DBの検索
 *------------------------------------------
 */
static int merc_search_index(int nameid)
{
	int i;

	for(i=0; i<merc_count; i++) {
		if(merc_db[i].class_ <= 0)
			continue;
		if(merc_db[i].class_ == nameid)
			return i;
	}
	return -1;
}

/*==========================================
 * 傭兵DBを返す
 *------------------------------------------
 */
struct merc_db* merc_search_data(int nameid)
{
	int idx = merc_search_index(nameid);

	if(idx >= 0)
		return &merc_db[idx];

	return NULL;
}

/*==========================================
 * 傭兵種別の取得
 *------------------------------------------
 */
static int merc_get_type(int class_)
{
	if(class_ >= 6017 && class_ <= 6026)
		return 0;
	if(class_ >= 6027 && class_ <= 6036)
		return 1;
	if(class_ >= 6037 && class_ <= 6046)
		return 2;

	return -1;
}

/*==========================================
 * スキルツリー情報の検索
 *------------------------------------------
 */
static struct merc_skill_tree_entry* merc_search_skilltree(int class_, int skillid)
{
	int i;
	int min = -1;
	int max = MAX_MERCSKILL_TREE;
	struct merc_skill_tree_entry *st;

	i = merc_search_index(class_);
	if(i < 0)
		return NULL;

	st = merc_skill_tree[i];

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
int merc_get_skilltree_max(int class_,int skillid)
{
	struct merc_skill_tree_entry *st;

	st = merc_search_skilltree(class_, skillid);
	if(st == NULL)
		return 0;

	return st->max;
}

/*==========================================
 * 雇用期限タイマー
 *------------------------------------------
 */
static int merc_employ_timer(int tid,unsigned int tick,int id,void *data)
{
	struct map_session_data *sd = map_id2sd(id);

	if(sd == NULL || sd->mcd == NULL)
		return 1;

	if(sd->mcd->limit_timer != tid) {
		if(battle_config.error_log)
			printf("merc_employ_timer %d != %d\n",sd->mcd->limit_timer,tid);
		return 0;
	}
	sd->mcd->limit_timer = -1;

	// 名声値+1
	merc_set_fame(sd, sd->mcd->status.class_, 1);

	clif_msgstringtable(sd, 0x4f2);	// 傭兵使用時間が完了しました。
	merc_delete_data(sd);

	return 0;
}

/*==========================================
 * 雇用期限タイマー削除
 *------------------------------------------
 */
int merc_employ_timer_delete(struct merc_data *mcd)
{
	nullpo_retr(0, mcd);

	if(mcd->limit_timer != -1) {
		delete_timer(mcd->limit_timer,merc_employ_timer);
		mcd->limit_timer = -1;
	}

	return 0;
}

/*==========================================
 * 各ステ計算
 *------------------------------------------
 */
int merc_calc_status(struct merc_data *mcd)
{
	struct merc_db *db;
	int aspd_rate=100,speed_rate=100,atk_rate=100,matk_rate=100,hp_rate=100,sp_rate=100;
	int flee_rate=100,def_rate=100,mdef_rate=100,critical_rate=100,hit_rate=100;

	nullpo_retr(1, mcd);

	db = merc_search_data(mcd->status.class_);
	if(db == NULL)
		return 1;

	mcd->atk1     = db->atk1;
	mcd->atk2     = db->atk2;
	mcd->matk1    = 0;
	mcd->matk2    = 0;
	mcd->hit      = 0;
	mcd->flee     = 0;
	mcd->def      = db->def;
	mcd->mdef     = db->mdef;
	mcd->critical = 0;
	mcd->max_hp   = db->max_hp;
	mcd->max_sp   = db->max_sp;
	mcd->str      = db->str;
	mcd->agi      = db->agi;
	mcd->vit      = db->vit;
	mcd->dex      = db->dex;
	mcd->int_     = db->int_;
	mcd->luk      = db->luk;
	if(mcd->msd)
		mcd->speed = status_get_speed(&mcd->msd->bl);
	else
		mcd->speed = db->speed;
	mcd->amotion  = db->amotion;
	mcd->nhealhp  = 0;
	mcd->nhealsp  = 0;
	mcd->hprecov_rate = 100;
	mcd->sprecov_rate = 100;

	// ステータス変化による基本パラメータ補正
	if(mcd->sc.count > 0)
	{
		int sc_speed_rate = 100;

		if(mcd->sc.data[SC_INCREASEAGI].timer != -1 && sc_speed_rate > 75)	// 速度増加による移動速度増加
			sc_speed_rate = 75;
		if(mcd->sc.data[SC_BERSERK].timer != -1 && sc_speed_rate > 75)	// バーサークによる移動速度増加
			sc_speed_rate = 75;

		mcd->speed = mcd->speed * sc_speed_rate / 100;

		if(mcd->sc.data[SC_DECREASEAGI].timer != -1) {		// 速度減少(agiはbattle.cで)
			if(mcd->sc.data[SC_DEFENDER].timer == -1) {	// ディフェンダー時は速度低下しない
				mcd->speed = mcd->speed *((mcd->sc.data[SC_DECREASEAGI].val1 > 5)? 150: 133)/100;
			}
		}

		if(mcd->sc.data[SC_MER_FLEE].timer != -1)	// 傭兵ボーナス(FLEE)
			mcd->flee += mcd->sc.data[SC_MER_FLEE].val2;
		if(mcd->sc.data[SC_MER_ATK].timer != -1) {	// 傭兵ボーナス(ATK)
			mcd->atk1 += mcd->sc.data[SC_MER_ATK].val2;
			mcd->atk2 += mcd->sc.data[SC_MER_ATK].val2;
		}
		if(mcd->sc.data[SC_MER_HP].timer != -1)	// 傭兵ボーナス(HP)
			hp_rate += mcd->sc.data[SC_MER_HP].val2;
		if(mcd->sc.data[SC_MER_SP].timer != -1)	// 傭兵ボーナス(SP)
			sp_rate += mcd->sc.data[SC_MER_SP].val2;
		if(mcd->sc.data[SC_MER_HIT].timer != -1)	// 傭兵ボーナス(HIT)
			mcd->hit += mcd->sc.data[SC_MER_HIT].val2;

		// ゴスペルALL+20
		if(mcd->sc.data[SC_INCALLSTATUS].timer != -1) {
			mcd->str  += mcd->sc.data[SC_INCALLSTATUS].val1;
			mcd->agi  += mcd->sc.data[SC_INCALLSTATUS].val1;
			mcd->vit  += mcd->sc.data[SC_INCALLSTATUS].val1;
			mcd->int_ += mcd->sc.data[SC_INCALLSTATUS].val1;
			mcd->dex  += mcd->sc.data[SC_INCALLSTATUS].val1;
			mcd->luk  += mcd->sc.data[SC_INCALLSTATUS].val1;
		}

		if(mcd->sc.data[SC_INCREASEAGI].timer != -1)	// 速度増加
			mcd->agi += 2+mcd->sc.data[SC_INCREASEAGI].val1;

		if(mcd->sc.data[SC_DECREASEAGI].timer != -1)	// 速度減少(agiはbattle.cで)
			mcd->agi -= 2+mcd->sc.data[SC_DECREASEAGI].val1;

		if(mcd->sc.data[SC_BLESSING].timer != -1) {	// ブレッシング
			mcd->str  += mcd->sc.data[SC_BLESSING].val1;
			mcd->dex  += mcd->sc.data[SC_BLESSING].val1;
			mcd->int_ += mcd->sc.data[SC_BLESSING].val1;
		}
		if(mcd->sc.data[SC_SUITON].timer != -1) {	// 水遁
			if(mcd->sc.data[SC_SUITON].val3)
				mcd->agi += mcd->sc.data[SC_SUITON].val3;
			if(mcd->sc.data[SC_SUITON].val4)
				mcd->speed = mcd->speed*2;
		}

		if(mcd->sc.data[SC_GLORIA].timer != -1)	// グロリア
			mcd->luk += 30;

		if(mcd->sc.data[SC_QUAGMIRE].timer != -1) {	// クァグマイア
			short subagi = 0;
			short subdex = 0;
			subagi = (mcd->agi/2 < mcd->sc.data[SC_QUAGMIRE].val1*10) ? mcd->agi/2 : mcd->sc.data[SC_QUAGMIRE].val1*10;
			subdex = (mcd->dex/2 < mcd->sc.data[SC_QUAGMIRE].val1*10) ? mcd->dex/2 : mcd->sc.data[SC_QUAGMIRE].val1*10;
			if(map[mcd->bl.m].flag.pvp || map[mcd->bl.m].flag.gvg) {
				subagi /= 2;
				subdex /= 2;
			}
			mcd->speed = mcd->speed*5/3;
			mcd->agi -= subagi;
			mcd->dex -= subdex;
		}

		if(mcd->sc.data[SC_BERSERK].timer != -1) {	// バーサーク
			def_rate  = 0;
			mdef_rate = 0;
			aspd_rate -= 30;
			mcd->flee -= mcd->flee * 50 / 100;
			mcd->max_hp = mcd->max_hp * 3;
		}

		if(mcd->sc.data[SC_DEFENDER].timer != -1) {	// ディフェンダー
			mcd->amotion += (25 - mcd->sc.data[SC_DEFENDER].val1*5);
			mcd->speed = (mcd->speed * (155 - mcd->sc.data[SC_DEFENDER].val1*5)) / 100;
		}

		// ウェポンクイッケン
		if(mcd->sc.data[SC_WEAPONQUICKEN].timer != -1 &&
		   mcd->sc.data[SC_QUAGMIRE].timer == -1 &&
		   mcd->sc.data[SC_DONTFORGETME].timer == -1 &&
		   mcd->sc.data[SC_DECREASEAGI].timer == -1)
			aspd_rate -= 30;
	}

	mcd->matk1    += mcd->int_+(mcd->int_/ 5) * (mcd->int_/ 5);
	mcd->matk2    += mcd->int_+(mcd->int_/ 7) * (mcd->int_/ 7);
	mcd->hit      += mcd->dex + mcd->base_level;
	mcd->flee     += mcd->agi + mcd->base_level;
	mcd->critical += mcd->luk * 3 + 10;

	// 補正
	if(atk_rate != 100) {
		mcd->atk1 = mcd->atk1*atk_rate/100;
		mcd->atk2 = mcd->atk2*atk_rate/100;
	}
	if(matk_rate != 100) {
		mcd->matk1 = mcd->matk1*matk_rate/100;
		mcd->matk2 = mcd->matk2*matk_rate/100;
	}
	if(hit_rate != 100)
		mcd->hit = mcd->hit*hit_rate/100;
	if(flee_rate != 100)
		mcd->flee = mcd->flee*flee_rate/100;
	if(def_rate != 100)
		mcd->def = mcd->def*def_rate/100;
	if(mdef_rate != 100)
		mcd->mdef = mcd->mdef*mdef_rate/100;
	if(critical_rate != 100)
		mcd->critical = mcd->critical*critical_rate/100;
	if(hp_rate != 100)
		mcd->max_hp = mcd->max_hp*hp_rate/100;
	if(sp_rate != 100)
		mcd->max_sp = mcd->max_sp*sp_rate/100;
	if(aspd_rate != 100)
		mcd->amotion = mcd->amotion*aspd_rate/100;
	if(speed_rate != 100)
		mcd->speed = mcd->speed*speed_rate/100;

	if(mcd->max_hp <= 0)
		mcd->max_hp = 1;
	if(mcd->max_sp <= 0)
		mcd->max_sp = 1;

	// 自然回復
	mcd->nhealhp = (int)(((atn_bignumber)mcd->max_hp * mcd->vit / 10000 + 1) * 6);
	mcd->nhealsp = (int)(((atn_bignumber)mcd->max_sp * (mcd->int_ + 10) / 750) + 1);
	if(mcd->hprecov_rate != 100)
		mcd->nhealhp = mcd->nhealhp*mcd->hprecov_rate/100;
	if(mcd->sprecov_rate != 100)
		mcd->nhealsp = mcd->nhealsp*mcd->sprecov_rate/100;

	if( mcd->sc.data[SC_AUTOBERSERK].timer != -1 &&
	    mcd->status.hp < mcd->max_hp>>2 &&
	    (mcd->sc.data[SC_PROVOKE].timer == -1 || mcd->sc.data[SC_PROVOKE].val2 == 0) &&
	    !unit_isdead(&mcd->bl) )
	{
		// オートバーサーク発動
		status_change_start(&mcd->bl,SC_PROVOKE,10,1,0,0,0,0);
	}

	return 0;
}

/*==========================================
 * 傭兵召喚
 *------------------------------------------
 */
int merc_callmerc(struct map_session_data *sd,int class_, unsigned int limit)
{
	struct mmo_mercstatus st;
	struct merc_db *db;

	nullpo_retr(0, sd);

	if(sd->status.merc_id > 0 || sd->mcd)	// 既に召喚中
		return 0;
	if(sd->state.merc_creating)
		return 0;

	db = merc_search_data(class_);
	if(db == NULL)
		return 0;

	memset(&st, 0, sizeof(st));

	st.class_     = class_;
	st.account_id = sd->status.account_id;
	st.char_id    = sd->status.char_id;
	st.hp = db->max_hp;
	st.sp = db->max_sp;
	st.limit  = limit + (unsigned int)time(NULL);

	sd->state.merc_creating = 1;
	intif_create_merc(sd->status.account_id,sd->status.char_id,&st);

	// 召喚回数+1
	merc_set_call(sd, class_, 1);

	return 1;
}

static int merc_natural_heal_hp(int tid,unsigned int tick,int id,void *data);
static int merc_natural_heal_sp(int tid,unsigned int tick,int id,void *data);

/*==========================================
 *
 *------------------------------------------
 */
static int merc_data_init(struct map_session_data *sd)
{
	struct merc_data *mcd;
	int i, class_, id;
	unsigned int tick = gettick();
	unsigned int now  = (unsigned int)time(NULL);
	unsigned int diff;

	nullpo_retr(1, sd);
	nullpo_retr(1, mcd = sd->mcd);

	class_ = merc_search_index(sd->mcd->status.class_);
	if(class_ < 0)
		return 1;

	mcd->bl.prev = mcd->bl.next = NULL;
	mcd->bl.id   = npc_get_new_npc_id();
	mcd->bl.m    = sd->bl.m;
	mcd->bl.x    = mcd->ud.to_x = sd->bl.x;
	mcd->bl.y    = mcd->ud.to_y = sd->bl.y;
	unit_calc_pos(&mcd->bl,sd->bl.x,sd->bl.y,sd->dir,2);
	mcd->bl.x    = mcd->ud.to_x;
	mcd->bl.y    = mcd->ud.to_y;
	mcd->bl.type = BL_MERC;
	memcpy(mcd->name, merc_db[class_].jname , 24);
	mcd->dir         = sd->dir;
	mcd->speed       = status_get_speed(&sd->bl);	// 歩行速度は、コール時の主人のspeedになる
	mcd->target_id   = 0;
	mcd->msd         = sd;
	mcd->view_class  = sd->mcd->status.class_;
	mcd->base_level  = merc_db[class_].lv;
	mcd->attackrange = merc_db[class_].range;

	// スキル取得
	for(i = 0; (id = merc_skill_tree[class_][i].id) > 0; i++) {
		id -= MERC_SKILLID;
		mcd->skill[id].id = id + MERC_SKILLID;
		mcd->skill[id].lv = merc_skill_tree[class_][i].max;
		mcd->skillstatictimer[i] = tick;
	}

	unit_dataset(&mcd->bl);

#ifdef DYNAMIC_SC_DATA
	// ダミー挿入
	mcd->sc.data = dummy_sc_data;
#else
	// ステータス異常の初期化
	for(i=0; i<MAX_STATUSCHANGE; i++) {
		mcd->sc.data[i].timer = -1;
		mcd->sc.data[i].val1  = 0;
		mcd->sc.data[i].val2  = 0;
		mcd->sc.data[i].val3  = 0;
		mcd->sc.data[i].val4  = 0;
	}
#endif

	mcd->sc.count = 0;
	mcd->sc.opt1  = OPT1_NORMAL;
	mcd->sc.opt2  = OPT2_NORMAL;
	mcd->sc.opt3  = OPT3_NORMAL;

	merc_calc_status(mcd);			// ステータス計算
	map_addiddb(&mcd->bl);

	mcd->natural_heal_hp = add_timer(tick+MERC_NATURAL_HEAL_HP_INTERVAL,merc_natural_heal_hp,mcd->bl.id,NULL);
	mcd->natural_heal_sp = add_timer(tick+MERC_NATURAL_HEAL_SP_INTERVAL,merc_natural_heal_sp,mcd->bl.id,NULL);

	if(mcd->status.limit > now)
		diff = (mcd->status.limit - now) * 1000;
	else
		diff = 1;
	mcd->limit_timer = add_timer(tick+diff,merc_employ_timer,sd->bl.id,NULL);

	mcd->view_size = 0;

	return 0;
}

/*==========================================
 * interから傭兵のデータ受信
 *------------------------------------------
 */
int merc_recv_mercdata(int account_id,int char_id,struct mmo_mercstatus *p,int flag)
{
	struct map_session_data *sd;

	nullpo_retr(0, p);

	sd = map_id2sd(account_id);

	if(sd == NULL || sd->status.char_id != char_id || (sd->status.merc_id && sd->status.merc_id != p->merc_id))
	{
		if(flag) {
			// 新規作成時なら傭兵データを削除する
			intif_delete_mercdata(account_id,char_id,p->merc_id);
		}
		if(sd)
			sd->state.merc_creating = 0;
		return 0;
	}

	if(sd->mcd == NULL) {
		sd->mcd = (struct merc_data *)aCalloc(1,sizeof(struct merc_data));
		memcpy(&sd->mcd->status, p, sizeof(struct mmo_mercstatus));

		if(sd->status.merc_id <= 0)
			sd->status.merc_id = p->merc_id;

		if(!merc_data_init(sd) && sd->bl.prev != NULL)
		{
			if(sd->mcd->status.hp <= 0) {	// 死亡
				merc_delete_data(sd);
				sd->state.merc_creating = 0;
				return 0;
			}
			map_addblock(&sd->mcd->bl);
			mob_ai_hard_spawn( &sd->mcd->bl, 1 );
			clif_spawnmerc(sd->mcd);
			clif_send_mercstatus(sd);
			clif_mercskillinfoblock(sd);
			merc_save_data(sd);
			skill_unit_move(&sd->mcd->bl,gettick(),1);
		}
	}
	sd->state.merc_creating = 0;

	return 0;
}

/*==========================================
 * 傭兵削除
 *------------------------------------------
 */
int merc_delete_data(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	if(sd->status.merc_id > 0 && sd->mcd) {
		unit_free(&sd->mcd->bl,0);
		intif_delete_mercdata(sd->status.account_id,sd->status.char_id,sd->status.merc_id);
		sd->status.merc_id = 0;
		chrif_save(sd,0);
		if(sd->state.storage_flag == 1)
			storage_storage_save(sd);
	}

	return 0;
}

/*==========================================
 * 傭兵メニューの応答
 *------------------------------------------
 */
int merc_menu(struct map_session_data *sd, int menunum)
{
	nullpo_retr(0, sd);

	if(!sd->mcd)
		return 0;

	switch(menunum) {
		case 1:
			clif_send_mercstatus(sd);
			clif_mercskillinfoblock(sd);
			break;
		case 2:
			clif_msgstringtable(sd, 0x4f4);	// 傭兵が解雇されました。
			merc_delete_data(sd);
			break;
	}
	return 0;
}

/*==========================================
 * 待機命令などで、主人の下へ移動
 *------------------------------------------
 */
int merc_return_master(struct map_session_data *sd)
{
	struct merc_data *mcd;

	nullpo_retr(0, sd);
	nullpo_retr(0, mcd = sd->mcd);

	unit_calc_pos(&mcd->bl,sd->bl.x,sd->bl.y,sd->dir,2);
	unit_walktoxy(&mcd->bl,mcd->ud.to_x,mcd->ud.to_y);
	return 0;
}

/*==========================================
 * スキルの検索 所有していた場合Lvが返る
 *------------------------------------------
 */
int merc_checkskill(struct merc_data *mcd,int skill_id)
{
	if(mcd == NULL)
		return 0;
	if(skill_id >= MERC_SKILLID)
		skill_id -= MERC_SKILLID;

	if(skill_id >= MAX_MERCSKILL)
		return 0;
	if(mcd->skill[skill_id].id == skill_id + MERC_SKILLID)
		return mcd->skill[skill_id].lv;

	return 0;
}

/*==========================================
 * 名声値の取得
 *------------------------------------------
 */
int merc_get_fame(struct map_session_data *sd, int class_)
{
	int type = merc_get_type(class_);

	nullpo_retr(0, sd);

	if(type < 0 || type > MAX_MERC_TYPE)
		return 0;

	return sd->status.merc_fame[type];
}

/*==========================================
 * 名声値の増減
 *------------------------------------------
 */
int merc_set_fame(struct map_session_data *sd, int class_, int val)
{
	int type = merc_get_type(class_);

	nullpo_retr(0, sd);

	if(type < 0 || type > MAX_MERC_TYPE)
		return 0;

	sd->status.merc_fame[type] += val;
	if(sd->status.merc_fame[type] < 0)
		sd->status.merc_fame[type] = 0;

	clif_mercupdatestatus(sd, SP_MERC_FAME);

	return 0;
}

/*==========================================
 * 召喚回数の取得
 *------------------------------------------
 */
int merc_get_call(struct map_session_data *sd, int class_)
{
	int type = merc_get_type(class_);

	nullpo_retr(0, sd);

	if(type < 0 || type > MAX_MERC_TYPE)
		return 0;

	return sd->status.merc_call[type];
}

/*==========================================
 * 召喚回数の増減
 *------------------------------------------
 */
int merc_set_call(struct map_session_data *sd, int class_, int val)
{
	int type = merc_get_type(class_);

	nullpo_retr(0, sd);

	if(type < 0 || type > MAX_MERC_TYPE)
		return 0;

	sd->status.merc_call[type] += val;
	if(sd->status.merc_call[type] < 0)
		sd->status.merc_call[type] = 0;

	return 0;
}

/*==========================================
 * キルカウントの増加
 *------------------------------------------
 */
int merc_killcount(struct merc_data *mcd, unsigned short lv)
{
	static const int type[] = { SC_MER_FLEE, SC_MER_ATK, SC_MER_HP, SC_MER_SP, SC_MER_HIT };

	nullpo_retr(0, mcd);

	// 相手のレベルが自分のレベルの1/2以上か？
	if(lv >= mcd->base_level / 2) {
		mcd->status.kill_count++;

		// キルカウント50毎に名声値+1、キルカウントボーナス
		if(mcd->status.kill_count % 50 == 0) {
			merc_set_fame(mcd->msd, mcd->status.class_, 1);
			status_change_start(&mcd->bl,type[atn_rand()%(sizeof(type)/sizeof(type[0]))],atn_rand()%5+1,0,0,0,600000,0);
		}

		if(mcd->msd)
			clif_mercupdatestatus(mcd->msd, SP_MERC_KILLCOUNT);
	}

	return 0;
}

/*==========================================
 * 経験値取得
 *------------------------------------------
 */
int merc_gainexp(struct merc_data *mcd,struct mob_data *md,atn_bignumber base_exp,atn_bignumber job_exp)
{
	nullpo_retr(0, mcd);

	if(mcd->bl.prev == NULL || unit_isdead(&mcd->bl))
		return 0;

	if(md && md->sc.data[SC_RICHMANKIM].timer != -1) {
		base_exp = base_exp * (125 + md->sc.data[SC_RICHMANKIM].val1*11)/100;
		job_exp  = job_exp  * (125 + md->sc.data[SC_RICHMANKIM].val1*11)/100;
	}

	if(mcd->msd) {	// 主人へ指定倍の経験値
		atn_bignumber mbexp = 0, mjexp = 0;
		if(battle_config.master_get_merc_base_exp)
			mbexp = base_exp * battle_config.master_get_merc_base_exp / 100;
		if(battle_config.master_get_merc_job_exp)
			mjexp = job_exp  * battle_config.master_get_merc_job_exp / 100;

		if(mbexp || mjexp)
			pc_gainexp(mcd->msd,md,mbexp,mjexp,0);
	}

	return 0;
}

/*==========================================
 * mcdにdamageのダメージ
 *------------------------------------------
 */
int merc_damage(struct block_list *src,struct merc_data *mcd,int damage)
{
	struct map_session_data *sd = NULL;

	nullpo_retr(0, mcd);
	nullpo_retr(0, sd = mcd->msd);

	// 既に死んでいたら無効
	if(unit_isdead(&mcd->bl))
		return 0;

	// 歩いていたら足を止める
	if((mcd->sc.data[SC_ENDURE].timer == -1 && mcd->sc.data[SC_BERSERK].timer == -1) || map[mcd->bl.m].flag.gvg)
		unit_stop_walking(&mcd->bl,battle_config.pc_hit_stop_type);

	if(damage > 0 && mcd->sc.data[SC_GRAVITATION_USER].timer != -1)
		status_change_end(&mcd->bl, SC_GRAVITATION_USER, -1);

	if(mcd->bl.prev == NULL) {
		if(battle_config.error_log)
			printf("merc_damage : BlockError!!\n");
		return 0;
	}

	if(mcd->status.hp > mcd->max_hp)
		mcd->status.hp = mcd->max_hp;

	// over kill分は丸める
	if(damage > mcd->status.hp)
		damage = mcd->status.hp;

	mcd->status.hp -= damage;

	// ハイド状態を解除
	status_change_hidden_end(&mcd->bl);

	clif_mercupdatestatus(sd,SP_HP);

	// 死亡していた
	if(mcd->status.hp <= 0) {
		// スキルユニットからの離脱
		mcd->status.hp = 1;
		skill_unit_move(&mcd->bl,gettick(),0);
		mcd->status.hp = 0;

		// 名声値-1
		merc_set_fame(sd, mcd->status.class_, -1);

		clif_msgstringtable(sd, 0x4f3);	// 傭兵が倒れました。
		merc_delete_data(sd);
	} else {
		if( mcd->sc.data[SC_AUTOBERSERK].timer != -1 &&
		    mcd->status.hp < mcd->max_hp>>2 &&
		    (mcd->sc.data[SC_PROVOKE].timer == -1 || mcd->sc.data[SC_PROVOKE].val2 == 0) )
		{
			// オートバーサーク発動
			status_change_start(&mcd->bl,SC_PROVOKE,10,1,0,0,0,0);
		}
	}

	return 0;
}

/*==========================================
 * HP/SP回復
 *------------------------------------------
 */
int merc_heal(struct merc_data *mcd,int hp,int sp)
{
	nullpo_retr(0, mcd);

	// バーサーク中は回復させない
	if(mcd->sc.data[SC_BERSERK].timer != -1) {
		if(sp > 0)
			sp = 0;
		if(hp > 0)
			hp = 0;
	}

	if(hp + mcd->status.hp > mcd->max_hp)
		hp = mcd->max_hp - mcd->status.hp;
	if(sp + mcd->status.sp > mcd->max_sp)
		sp = mcd->max_sp - mcd->status.sp;
	mcd->status.hp += hp;
	if(mcd->status.hp <= 0) {
		mcd->status.hp = 0;
		merc_damage(NULL,mcd,1);
		hp = 0;
	}
	mcd->status.sp += sp;
	if(mcd->status.sp <= 0)
		mcd->status.sp = 0;
	if(mcd->msd) {
		if(hp)
			clif_mercupdatestatus(mcd->msd,SP_HP);
		if(sp)
			clif_mercupdatestatus(mcd->msd,SP_SP);
	}

	return hp + sp;
}

/*==========================================
 * 自然回復物
 *------------------------------------------
 */
static int merc_natural_heal_hp(int tid,unsigned int tick,int id,void *data)
{
	struct merc_data *mcd = map_id2mcd(id);
	int bhp;

	nullpo_retr(0, mcd);

	if(mcd->natural_heal_hp != tid) {
		if(battle_config.error_log)
			printf("merc_natural_heal_hp %d != %d\n",mcd->natural_heal_hp,tid);
		return 0;
	}
	mcd->natural_heal_hp = -1;

	bhp = mcd->status.hp;

	if(mcd->ud.walktimer == -1) {
		mcd->status.hp += mcd->nhealhp;
		if(mcd->status.hp > mcd->max_hp)
			mcd->status.hp = mcd->max_hp;
		if(bhp != mcd->status.hp && mcd->msd)
			clif_mercupdatestatus(mcd->msd,SP_HP);
	}
	mcd->natural_heal_hp = add_timer(tick+MERC_NATURAL_HEAL_HP_INTERVAL,merc_natural_heal_hp,mcd->bl.id,NULL);

	return 0;
}

static int merc_natural_heal_sp(int tid,unsigned int tick,int id,void *data)
{
	struct merc_data *mcd = map_id2mcd(id);
	int bsp;

	nullpo_retr(0, mcd);

	if(mcd->natural_heal_sp != tid) {
		if(battle_config.error_log)
			printf("merc_natural_heal_sp %d != %d\n",mcd->natural_heal_sp,tid);
		return 0;
	}
	mcd->natural_heal_sp = -1;

	bsp = mcd->status.sp;

	if(mcd->ud.walktimer == -1) {
		mcd->status.sp += mcd->nhealsp;
		if(mcd->status.sp > mcd->max_sp)
			mcd->status.sp = mcd->max_sp;
		if(bsp != mcd->status.sp && mcd->msd)
			clif_mercupdatestatus(mcd->msd,SP_SP);
	}
	mcd->natural_heal_sp = add_timer(tick+MERC_NATURAL_HEAL_SP_INTERVAL,merc_natural_heal_sp,mcd->bl.id,NULL);

	return 0;
}

int merc_natural_heal_timer_delete(struct merc_data *mcd)
{
	nullpo_retr(0, mcd);

	if(mcd->natural_heal_hp != -1) {
		delete_timer(mcd->natural_heal_hp,merc_natural_heal_hp);
		mcd->natural_heal_hp = -1;
	}
	if(mcd->natural_heal_sp != -1) {
		delete_timer(mcd->natural_heal_sp,merc_natural_heal_sp);
		mcd->natural_heal_sp = -1;
	}

	return 0;
}

/*==========================================
 * 傭兵のデータをセーブ
 *------------------------------------------
 */
int merc_save_data(struct map_session_data *sd)
{
	struct merc_data *mcd;

	nullpo_retr(0, sd);
	nullpo_retr(0, mcd = sd->mcd);

	intif_save_mercdata(sd->status.account_id,&sd->mcd->status);

	return 0;
}

//
// 初期化物
//
/*==========================================
 * 傭兵初期ステータスデータ読み込み
 *------------------------------------------
 */
static int read_merc_db(void)
{
	FILE *fp;
	char line[4096];
	int i, j, k;
	int lines, count = 0;
	struct script_code *script = NULL;
	const char *filename[] = { "db/merc_db.txt", "db/addon/merc_db_add.txt" };

	// DB情報の初期化
	for(i=0; i<MAX_MERC_DB; i++) {
		if(merc_db[i].script)
			script_free_code(merc_db[i].script);
	}
	memset(merc_db, 0, sizeof(merc_db));
	merc_count = 0;

	for(i = 0; i < 2; i++) {
		fp = fopen(filename[i], "r");
		if(fp == NULL) {
			if(i > 0)
				continue;
			printf("read_merc_db: open [%s] failed !\n", filename[i]);
			return -1;
		}
		lines=count=0;
		while(fgets(line,sizeof(line),fp)){
			int nameid;
			char *str[24],*p,*np;
			lines++;

			if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
				continue;
			if(line[0] == '/' && line[1] == '/')
				continue;

			for(j=0,p=line;j<24;j++){
				if((np=strchr(p,','))!=NULL){
					str[j]=p;
					*np=0;
					p=np+1;
				} else {
					str[j]=p;
					p+=strlen(p);
				}
			}

			if(merc_count >= MAX_MERC_DB)
				break;

			nameid = atoi(str[0]);

			if(nameid <= 0)
				continue;

			k = merc_search_index(nameid);
			j = (k >= 0)? k: merc_count;

			merc_db[j].class_  = nameid;
			strncpy(merc_db[j].name,str[1],24);
			strncpy(merc_db[j].jname,str[2],24);
			merc_db[j].lv      = atoi(str[3]);
			merc_db[j].max_hp  = atoi(str[4]);
			merc_db[j].max_sp  = atoi(str[5]);
			merc_db[j].range   = atoi(str[6]);
			merc_db[j].atk1    = atoi(str[7]);
			merc_db[j].atk2    = atoi(str[8]);
			merc_db[j].def     = atoi(str[9]);
			merc_db[j].mdef    = atoi(str[10]);
			merc_db[j].str     = atoi(str[11]);
			merc_db[j].agi     = atoi(str[12]);
			merc_db[j].vit     = atoi(str[13]);
			merc_db[j].int_    = atoi(str[14]);
			merc_db[j].dex     = atoi(str[15]);
			merc_db[j].luk     = atoi(str[16]);
			merc_db[j].size    = atoi(str[17]);
			merc_db[j].race    = atoi(str[18]);
			merc_db[j].element = atoi(str[19]);
			merc_db[j].speed   = atoi(str[20]);
			merc_db[j].adelay  = atoi(str[21]);
			merc_db[j].amotion = atoi(str[22]);
			merc_db[j].dmotion = atoi(str[23]);

			// force \0 terminal
			merc_db[j].name[23]  = '\0';
			merc_db[j].jname[23] = '\0';

			if(k < 0)
				merc_count++;
			count++;

			if((np = strchr(p, '{')) == NULL)
				continue;

			if(!parse_script_line_end(np, filename[i], lines))
				continue;

			if(merc_db[j].script) {
				script_free_code(merc_db[j].script);
			}
			script = parse_script(np, filename[i], lines);
			merc_db[j].script = (script_is_error(script))? NULL: script;
		}
		fclose(fp);
		printf("read %s done (count=%d)\n", filename[i], count);
	}
	return 0;
}

/*==========================================
 * 傭兵スキルデータ読み込み
 *------------------------------------------
 */
static int read_merc_skilldb(void)
{
	int i,j,class_=0;
	FILE *fp;
	char line[1024],*p;
	const char *filename = "db/merc_skill_tree.txt";

	// スキルツリー
	memset(merc_skill_tree,0,sizeof(merc_skill_tree));
	fp = fopen(filename, "r");
	if(fp == NULL){
		printf("read_merc_skilldb: open [%s] failed !\n", filename);
		return 1;
	}
	while(fgets(line,1020,fp)){
		int skillid;
		char *split[3];
		struct merc_skill_tree_entry *st;

		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0]=='/' && line[1]=='/')
			continue;
		for(j=0,p=line;j<3 && p;j++){
			split[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		if(j < 3)
			continue;
		class_ = atoi(split[0]);
		i = merc_search_index(class_);
		if(i < 0)
			continue;

		skillid = atoi(split[1]);
		if(skillid < MERC_SKILLID || skillid >= MAX_MERC_SKILLID)
			continue;

		st = merc_skill_tree[i];
		for(j=0; st[j].id && st[j].id != skillid; j++);

		if(j >= MAX_MERCSKILL_TREE - 1) {
			// 末尾はアンカーとして0にしておく必要がある
			printf("read_merc_skilldb: skill (%d) is over max tree %d!!\n", skillid, MAX_MERCSKILL_TREE);
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
	}
	fclose(fp);
	printf("read %s done\n", filename);

	return 0;
}

/*==========================================
 * 傭兵DBのリロード
 *------------------------------------------
 */
void merc_reload(void)
{
	read_merc_db();
	read_merc_skilldb();
}

/*==========================================
 * 初期化処理
 *------------------------------------------
 */
int do_init_merc(void)
{
	read_merc_db();
	read_merc_skilldb();

	add_timer_func_list(merc_natural_heal_hp);
	add_timer_func_list(merc_natural_heal_sp);
	add_timer_func_list(merc_employ_timer);

	return 0;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
int do_final_merc(void)
{
	int i;

	for(i = 0; i < merc_count; i++) {
		if(merc_db[i].script) {
			script_free_code(merc_db[i].script);
		}
	}
	return 0;
}
