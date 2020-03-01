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
#include "elem.h"
#include "intif.h"
#include "map.h"
#include "path.h"
#include "mob.h"
#include "npc.h"
#include "pc.h"
#include "skill.h"
#include "status.h"
#include "storage.h"
#include "unit.h"

struct elem_db elem_db[MAX_ELEM_DB];

static struct elem_skill_tree_entry {
	int id;
	int max;
	short mode;
} elem_skill_tree[MAX_ELEM_DB][MAX_ELEMSKILL_TREE];

static int elem_count;

/*==========================================
 * 精霊DBの検索
 *------------------------------------------
 */
static int elem_search_index(int nameid)
{
	int i;

	for(i=0; i<elem_count; i++) {
		if(elem_db[i].class_ <= 0)
			continue;
		if(elem_db[i].class_ == nameid)
			return i;
	}
	return -1;
}

/*==========================================
 * 精霊DBを返す
 *------------------------------------------
 */
struct elem_db* elem_search_data(int nameid)
{
	int idx = elem_search_index(nameid);

	if(idx >= 0)
		return &elem_db[idx];

	return NULL;
}

/*==========================================
 * スキルツリー情報の検索
 *------------------------------------------
 */
static struct elem_skill_tree_entry* elem_search_skilltree(int class_, int skillid)
{
	int i;
	int min = -1;
	int max = MAX_ELEMSKILL_TREE;
	struct elem_skill_tree_entry *st;

	i = elem_search_index(class_);
	if(i < 0)
		return NULL;

	st = elem_skill_tree[i];

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
int elem_get_skilltree_max(int class_,int skillid)
{
	struct elem_skill_tree_entry *st;

	st = elem_search_skilltree(class_, skillid);
	if(st == NULL)
		return 0;

	return st->max;
}

/*==========================================
 * ロック解除
 *------------------------------------------
 */
static int elem_unlocktarget(struct elem_data *eld)
{
	nullpo_retr(0, eld);

	eld->target_id = 0;

	return 0;
}

/*==========================================
 * 召喚タイマー
 *------------------------------------------
 */
static int elem_summon_timer(int tid,unsigned int tick,int id,void *data)
{
	struct map_session_data *sd = map_id2sd(id);

	if(sd == NULL || sd->eld == NULL)
		return 1;

	if(sd->eld->limit_timer != tid) {
		if(battle_config.error_log)
			printf("elem_summon_timer %d != %d\n",sd->eld->limit_timer,tid);
		return 0;
	}
	sd->eld->limit_timer = -1;

	elem_delete_data(sd);

	return 0;
}

/*==========================================
 * 召喚タイマー削除
 *------------------------------------------
 */
int elem_summon_timer_delete(struct elem_data *eld)
{
	nullpo_retr(0, eld);

	if(eld->limit_timer != -1) {
		delete_timer(eld->limit_timer,elem_summon_timer);
		eld->limit_timer = -1;
	}

	return 0;
}

/*==========================================
 * 指定IDの存在場所への到達可能性
 *------------------------------------------
 */
static int elem_can_reach(struct elem_data *eld,struct block_list *bl,int range)
{
	struct walkpath_data wpd;

	nullpo_retr(0, eld);
	nullpo_retr(0, bl);

	if(eld->bl.m != bl-> m)	// 違うマップ
		return 0;

	if( range > 0 && range < path_distance(eld->bl.x,eld->bl.y,bl->x,bl->y) )	// 遠すぎる
		return 0;

	if( eld->bl.x == bl->x && eld->bl.y == bl->y )	// 同じマス
		return 1;

	if( eld->attackrange > 6 ) {
		// 攻撃可能な場合は遠距離攻撃、それ以外は移動を試みる
		if( path_search_long(NULL,eld->bl.m,eld->bl.x,eld->bl.y,bl->x,bl->y) )
			return 1;
	}

	// 障害物判定
	wpd.path_len = 0;
	wpd.path_pos = 0;
	if( !path_search(&wpd,eld->bl.m,eld->bl.x,eld->bl.y,bl->x,bl->y,0) && wpd.path_len <= AREA_SIZE )
		return 1;

	return 0;
}

/*==========================================
 * ターゲットのロックが可能かどうか
 *------------------------------------------
 */
static int elem_can_lock(struct elem_data *eld, struct block_list *bl)
{
	struct status_change *tsc;

	nullpo_retr(0, eld);

	if(bl == NULL || unit_isdead(bl))
		return 0;

	tsc  = status_get_sc(bl);

	if( tsc && (tsc->data[SC_TRICKDEAD].timer != -1 || tsc->data[SC_FORCEWALKING].timer != -1) )
		return 0;
	if( tsc && ((tsc->option&(OPTION_HIDE | OPTION_CLOAKING | OPTION_FOOTPRINT)) || tsc->data[SC_CAMOUFLAGE].timer != -1) &&
		(tsc->data[SC_CLOAKINGEXCEED].timer != -1 || tsc->data[SC_STEALTHFIELD].timer != -1)  )
		return 0;

	if(bl->type == BL_PC) {
		struct map_session_data *tsd = (struct map_session_data *)bl;
		if(tsd) {
			if( tsd->invincible_timer != -1 )
				return 0;
			if( pc_isinvisible(tsd) )
				return 0;
			if( tsd->state.gangsterparadise )
				return 0;
		}
	}
	return 1;
}

/*==========================================
 * 精霊策敵ルーティン
 *------------------------------------------
 */
static int elem_ai_sub_timer_search(struct block_list *bl,va_list ap)
{
	struct elem_data *eld = NULL;
	int count, dist, range;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, eld = va_arg(ap,struct elem_data *));

	count = va_arg(ap,int);

	if( eld->bl.id == bl->id )
		return 0; // self

	dist = path_distance(eld->bl.x,eld->bl.y,bl->x,bl->y);

	// アクティブ
	range = (eld->sc.data[SC_BLIND].timer != -1 || eld->sc.data[SC_FOGWALLPENALTY].timer != -1)? 1: 10;

	// ターゲット射程内にいるなら、ロックする
	if(dist <= range && battle_check_target(&eld->bl,bl,BCT_ENEMY) >= 1 && elem_can_lock(eld,bl)) {
		// 射線チェック
		cell_t cell_flag = (eld->attackrange > 6 ? CELL_CHKWALL : CELL_CHKNOPASS);
		if( path_search_long_real(NULL,eld->bl.m,eld->bl.x,eld->bl.y,bl->x,bl->y,cell_flag) &&
		    elem_can_reach(eld,bl,range) &&
		    atn_rand()%1000 < 1000/(++count) )	// 範囲内PCで等確率にする
		{
			eld->target_id = bl->id;
		}
	}

	return 0;
}

/*==========================================
 * 精霊AI処理
 *------------------------------------------
 */
static int elem_ai_sub_timer(void *key,void *data,va_list ap)
{
	struct block_list *bl = (struct block_list *)data;
	struct elem_data *eld = NULL;
	struct map_session_data *msd = NULL;
	unsigned int tick = 0;
	int dist;

	nullpo_retr(0, bl);

	if(bl->type != BL_ELEM)
		return 0;
	if((eld = (struct elem_data *)bl) == NULL)
		return 0;
	if((msd = eld->msd) == NULL)
		return 0;

	tick = va_arg(ap,unsigned int);

	if(DIFF_TICK(tick,eld->last_thinktime) < MIN_ELEMTHINKTIME)
		return 0;

	eld->last_thinktime = tick;

	dist = unit_distance(&eld->bl,&msd->bl);
	if(dist > 12) {
		if(eld->target_id) {
			unit_stopattack(&eld->bl);
			elem_unlocktarget(eld);
		}
		if(eld->ud.walktimer != -1 && path_distance(eld->ud.to_x,eld->ud.to_y,msd->bl.x,msd->bl.y) <= MIN_ELEMDISTANCE)
			return 0;
		eld->speed = (msd->speed >> 1);
		if(eld->speed <= 0)
			eld->speed = 1;
		unit_calc_pos(&eld->bl,msd->bl.x,msd->bl.y,msd->dir,MIN_ELEMDISTANCE);
		unit_walktoxy(&eld->bl,eld->ud.to_x,eld->ud.to_y);

		return 0;
	}

	if(eld->status.mode == ELMODE_OFFENSIVE) {
		struct block_list *tbl = NULL;

		if(eld->target_id == 0) {
			int count = 0;
			map_foreachinarea(elem_ai_sub_timer_search,eld->bl.m,
							  msd->bl.x-AREA_SIZE,msd->bl.y-AREA_SIZE,
							  msd->bl.x+AREA_SIZE,msd->bl.y+AREA_SIZE,
							  BL_CHAR,eld,count);
		}

		if( eld->target_id <= 0 || (tbl = map_id2bl(eld->target_id)) == NULL ||
		    tbl->m != eld->bl.m || tbl->prev == NULL ||
		    (dist = path_distance(eld->bl.x,eld->bl.y,tbl->x,tbl->y)) >= AREA_SIZE )
		{
			// 対象が居ない / どこかに消えた / 視界外
			if(eld->target_id > 0) {
				elem_unlocktarget(eld);
				if(eld->ud.walktimer != -1)
					unit_stop_walking(&eld->bl,5);	// 歩行中なら停止
				return 0;
			}
		} else if(tbl->type & BL_CHAR) {
			if(!elem_can_lock(eld,tbl)) {
				// スキルなどによる策敵妨害判定
				elem_unlocktarget(eld);
			} else if(!battle_check_range(&eld->bl,tbl,eld->attackrange)) {
				// 攻撃範囲外なので移動
				if( !unit_can_move(&eld->bl) || unit_isrunning(&eld->bl) ) {	// 動けない状態にある
					// アンクル、蜘蛛の巣拘束中は強制待機
					if(eld->sc.data && (eld->sc.data[SC_ANKLE].timer != -1 || eld->sc.data[SC_SPIDERWEB].timer != -1 ||
					   eld->sc.data[SC_ELECTRICSHOCKER].timer != -1 || eld->sc.data[SC_MAGNETICFIELD].timer != -1 ||
					   eld->sc.data[SC_SITDOWN_FORCE].timer != -1 || eld->sc.data[SC_FALLENEMPIRE].timer != -1 ||
					   eld->sc.data[SC_NETHERWORLD].timer != -1 || eld->sc.data[SC_VACUUM_EXTREME].timer != -1 ||
					   eld->sc.data[SC_THORNS_TRAP].timer != -1 || eld->sc.data[SC_BANANA_BOMB].timer != -1))
						elem_unlocktarget(eld);
					return 0;
				}
				if(eld->ud.walktimer != -1 && path_distance(eld->ud.to_x,eld->ud.to_y,tbl->x,tbl->y) < 2)
					return 0; // 既に移動中
				if( !elem_can_reach(eld,tbl,AREA_SIZE) ) {
					elem_unlocktarget(eld);	// 移動できないのでタゲ解除（IWとか？）
				} else {
					// 追跡
					int dx, dy, ret, i = 0;
					do {
						if(i == 0) {
							// 最初はAEGISと同じ方法で検索
							dx = tbl->x - eld->bl.x;
							dy = tbl->y - eld->bl.y;
							if(dx < 0) dx++; else if(dx > 0) dx--;
							if(dy < 0) dy++; else if(dy > 0) dy--;
						} else {
							// だめならAthena式(ランダム)
							dx = tbl->x - eld->bl.x + atn_rand()%3 - 1;
							dy = tbl->y - eld->bl.y + atn_rand()%3 - 1;
						}
						ret = unit_walktoxy(&eld->bl,eld->bl.x+dx,eld->bl.y+dy);
						i++;
					} while(ret == 0 && i < 5);

					if(ret == 0) { // 移動不可能な所からの攻撃なら2歩下る
						if(dx < 0) dx = 2; else if(dx > 0) dx = -2;
						if(dy < 0) dy = 2; else if(dy > 0) dy = -2;
						unit_walktoxy(&eld->bl,eld->bl.x+dx,eld->bl.y+dy);
					}
				}
			} else {
				// 攻撃射程範囲内
				if(eld->ud.walktimer != -1)
					unit_stop_walking(&eld->bl,1);	// 歩行中なら停止
				if(eld->ud.attacktimer != -1 || eld->ud.canact_tick > tick)
					return 0; // 既に攻撃中
				unit_attack(&eld->bl, eld->target_id, 1);
			}
			return 0;
		}
	}

	if(dist > MAX_ELEMDISTANCE && eld->target_id == 0) {
		if(eld->ud.walktimer != -1 && path_distance(eld->ud.to_x,eld->ud.to_y,msd->bl.x,msd->bl.y) <= MIN_ELEMDISTANCE)
			return 0;
		eld->speed = msd->speed;
		unit_calc_pos(&eld->bl,msd->bl.x,msd->bl.y,msd->dir,MIN_ELEMDISTANCE);
		unit_walktoxy(&eld->bl,eld->ud.to_x,eld->ud.to_y);

		return 0;
	}

	return 0;
}

/*==========================================
 * 精霊AIタイマー
 *------------------------------------------
 */
static int elem_ai_timer(int tid,unsigned int tick,int id,void *data)
{
	map_foreachiddb(elem_ai_sub_timer,tick);

	return 0;
}

/*==========================================
 * 各ステ計算
 *------------------------------------------
 */
int elem_calc_status(struct elem_data *eld)
{
	struct elem_db *db;
	int aspd_rate=100,speed_rate=100,atk_rate=100,matk_rate=100,hp_rate=100,sp_rate=100;
	int flee_rate=100,def_rate=100,mdef_rate=100,critical_rate=100,hit_rate=100;

	nullpo_retr(1, eld);

	db = elem_search_data(eld->status.class_);
	if(db == NULL)
		return 1;

	eld->atk1     = db->atk1;
	eld->atk2     = db->atk2;
	eld->matk1    = 0;
	eld->matk2    = 0;
	eld->hit      = 0;
	eld->flee     = 0;
	eld->def      = db->def;
	eld->mdef     = db->mdef;
	eld->critical = 0;
	eld->max_hp   = db->max_hp;
	eld->max_sp   = db->max_sp;
	eld->str      = db->str;
	eld->agi      = db->agi;
	eld->vit      = db->vit;
	eld->dex      = db->dex;
	eld->int_     = db->int_;
	eld->luk      = db->luk;
	if(eld->msd)
		eld->speed = status_get_speed(&eld->msd->bl);
	else
		eld->speed = db->speed;
	eld->adelay   = db->adelay;
	eld->amotion  = db->amotion;
	eld->dmotion  = db->dmotion;
	eld->nhealhp  = 0;
	eld->nhealsp  = 0;
	eld->hprecov_rate = 100;
	eld->sprecov_rate = 100;

	// ステータス変化による基本パラメータ補正
	if(eld->sc.count > 0)
	{
		int sc_speed_rate = 100;

		if(eld->sc.data[SC_INCREASEAGI].timer != -1 && sc_speed_rate > 75)	// 速度増加による移動速度増加
			sc_speed_rate = 75;

		eld->speed = eld->speed * sc_speed_rate / 100;

		if(eld->sc.data[SC_DECREASEAGI].timer != -1) {		// 速度減少(agiはbattle.cで)
			if(eld->sc.data[SC_DEFENDER].timer == -1) {	// ディフェンダー時は速度低下しない
				eld->speed = eld->speed *((eld->sc.data[SC_DECREASEAGI].val1 > 5)? 150: 133)/100;
			}
		}

		// ゴスペルALL+20
		if(eld->sc.data[SC_INCALLSTATUS].timer != -1) {
			eld->str  += eld->sc.data[SC_INCALLSTATUS].val1;
			eld->agi  += eld->sc.data[SC_INCALLSTATUS].val1;
			eld->vit  += eld->sc.data[SC_INCALLSTATUS].val1;
			eld->int_ += eld->sc.data[SC_INCALLSTATUS].val1;
			eld->dex  += eld->sc.data[SC_INCALLSTATUS].val1;
			eld->luk  += eld->sc.data[SC_INCALLSTATUS].val1;
		}

		if(eld->sc.data[SC_INCREASEAGI].timer != -1)	// 速度増加
			eld->agi += 2+eld->sc.data[SC_INCREASEAGI].val1;

		if(eld->sc.data[SC_DECREASEAGI].timer != -1)	// 速度減少(agiはbattle.cで)
			eld->agi -= 2+eld->sc.data[SC_DECREASEAGI].val1;

		if(eld->sc.data[SC_BLESSING].timer != -1) {	// ブレッシング
			eld->str  += eld->sc.data[SC_BLESSING].val1;
			eld->dex  += eld->sc.data[SC_BLESSING].val1;
			eld->int_ += eld->sc.data[SC_BLESSING].val1;
		}
		if(eld->sc.data[SC_SUITON].timer != -1) {	// 水遁
			if(eld->sc.data[SC_SUITON].val3)
				eld->agi += eld->sc.data[SC_SUITON].val3;
			if(eld->sc.data[SC_SUITON].val4)
				eld->speed = eld->speed*2;
		}

		if(eld->sc.data[SC_GLORIA].timer != -1)	// グロリア
			eld->luk += 30;

		if(eld->sc.data[SC_QUAGMIRE].timer != -1) {	// クァグマイア
			short subagi = 0;
			short subdex = 0;
			subagi = (eld->agi/2 < eld->sc.data[SC_QUAGMIRE].val1*10) ? eld->agi/2 : eld->sc.data[SC_QUAGMIRE].val1*10;
			subdex = (eld->dex/2 < eld->sc.data[SC_QUAGMIRE].val1*10) ? eld->dex/2 : eld->sc.data[SC_QUAGMIRE].val1*10;
			if(map[eld->bl.m].flag.pvp || map[eld->bl.m].flag.gvg) {
				subagi /= 2;
				subdex /= 2;
			}
			eld->speed = eld->speed*5/3;
			eld->agi -= subagi;
			eld->dex -= subdex;
		}

		if(eld->sc.data[SC_TIDAL_WEAPON_OPTION].timer != -1)	// タイダルウェポン(精霊)
			atk_rate += eld->sc.data[SC_TIDAL_WEAPON_OPTION].val2;
	}

	// エレメンタルシンパシー
	if(eld->msd) {
		int skill = pc_checkskill(eld->msd,SO_EL_SYMPATHY);
		eld->max_hp += 500 * skill;
		eld->max_sp += 50 * skill;
		eld->atk1 += 25 * skill;
		eld->atk2 += 25 * skill;
	}

	eld->matk1    += eld->int_+(eld->int_/ 5) * (eld->int_/ 5);
	eld->matk2    += eld->int_+(eld->int_/ 7) * (eld->int_/ 7);
	eld->hit      += eld->dex + eld->base_level;
	eld->flee     += eld->agi + eld->base_level;
	eld->critical += eld->luk * 3 + 10;

	// 補正
	if(atk_rate != 100) {
		eld->atk1 = eld->atk1*atk_rate/100;
		eld->atk2 = eld->atk2*atk_rate/100;
	}
	if(matk_rate != 100) {
		eld->matk1 = eld->matk1*matk_rate/100;
		eld->matk2 = eld->matk2*matk_rate/100;
	}
	if(hit_rate != 100)
		eld->hit = eld->hit*hit_rate/100;
	if(flee_rate != 100)
		eld->flee = eld->flee*flee_rate/100;
	if(def_rate != 100)
		eld->def = eld->def*def_rate/100;
	if(mdef_rate != 100)
		eld->mdef = eld->mdef*mdef_rate/100;
	if(critical_rate != 100)
		eld->critical = eld->critical*critical_rate/100;
	if(hp_rate != 100)
		eld->max_hp = eld->max_hp*hp_rate/100;
	if(sp_rate != 100)
		eld->max_sp = eld->max_sp*sp_rate/100;
	if(aspd_rate != 100)
		eld->amotion = eld->amotion*aspd_rate/100;
	if(speed_rate != 100)
		eld->speed = eld->speed*speed_rate/100;

	if(eld->max_hp <= 0)
		eld->max_hp = 1;
	if(eld->max_sp <= 0)
		eld->max_sp = 1;

	// 自然回復
	eld->nhealhp = (int)(((atn_bignumber)eld->max_hp * eld->vit / 10000 + 1) * 6);
	eld->nhealsp = (int)(((atn_bignumber)eld->max_sp * (eld->int_ + 10) / 750) + 1);
	if(eld->hprecov_rate != 100)
		eld->nhealhp = eld->nhealhp*eld->hprecov_rate/100;
	if(eld->sprecov_rate != 100)
		eld->nhealsp = eld->nhealsp*eld->sprecov_rate/100;

	if( eld->sc.data[SC_AUTOBERSERK].timer != -1 &&
	    eld->status.hp < eld->max_hp>>2 &&
	    (eld->sc.data[SC_PROVOKE].timer == -1 || eld->sc.data[SC_PROVOKE].val2 == 0) &&
	    !unit_isdead(&eld->bl) )
	{
		// オートバーサーク発動
		status_change_start(&eld->bl,SC_PROVOKE,10,1,0,0,0,0);
	}

	return 0;
}

/*==========================================
 * 精霊召喚
 *------------------------------------------
 */
int elem_create_data(struct map_session_data *sd,int class_, unsigned int limit)
{
	struct mmo_elemstatus st;
	struct elem_db *db;
	int skill;

	nullpo_retr(1, sd);

	if(sd->status.elem_id > 0 || sd->eld)	// 既に召喚中
		return 1;
	if(sd->state.elem_creating)
		return 1;

	db = elem_search_data(class_);
	if(db == NULL)
		return 1;

	skill = pc_checkskill(sd,SO_EL_SYMPATHY);

	memset(&st, 0, sizeof(st));

	st.class_     = class_;
	st.account_id = sd->status.account_id;
	st.char_id    = sd->status.char_id;
	st.mode  = ELMODE_WAIT;
	st.hp    = db->max_hp + 500 * skill;
	st.sp    = db->max_sp + 50 * skill;
	st.limit = limit + (unsigned int)time(NULL);

	sd->state.elem_creating = 1;
	intif_create_elem(sd->status.account_id,sd->status.char_id,&st);

	return 0;
}

static int elem_natural_heal_hp(int tid,unsigned int tick,int id,void *data);
static int elem_natural_heal_sp(int tid,unsigned int tick,int id,void *data);

/*==========================================
 *
 *------------------------------------------
 */
static int elem_data_init(struct map_session_data *sd)
{
	struct elem_data *eld;
	int i, class_, id;
	unsigned int tick = gettick();
	unsigned int now  = (unsigned int)time(NULL);
	unsigned int diff;

	nullpo_retr(1, sd);
	nullpo_retr(1, eld = sd->eld);

	class_ = elem_search_index(sd->eld->status.class_);
	if(class_ < 0)
		return 1;

	eld->bl.prev = eld->bl.next = NULL;
	eld->bl.id   = npc_get_new_npc_id();
	eld->bl.m    = sd->bl.m;
	eld->bl.x    = eld->ud.to_x = sd->bl.x;
	eld->bl.y    = eld->ud.to_y = sd->bl.y;
	eld->bl.type = BL_ELEM;
	memcpy(eld->name, elem_db[class_].jname , 24);
	eld->dir         = sd->dir;
	eld->speed       = status_get_speed(&sd->bl);	// 歩行速度は、コール時の主人のspeedになる
	eld->target_id   = 0;
	eld->msd         = sd;
	eld->view_class  = sd->eld->status.class_;
	eld->base_level  = elem_db[class_].lv;
	eld->attackrange = elem_db[class_].range;
	eld->last_thinktime = tick;

	// スキル取得
	for(i = 0; (id = elem_skill_tree[class_][i].id) > 0; i++) {
		id -= ELEM_SKILLID;
		eld->skill[id].id = id + ELEM_SKILLID;
		eld->skill[id].lv = elem_skill_tree[class_][i].max;
		eld->skillstatictimer[i] = tick;
	}

	unit_dataset(&eld->bl);

#ifdef DYNAMIC_SC_DATA
	// ダミー挿入
	eld->sc.data = dummy_sc_data;
#else
	// ステータス異常の初期化
	for(i=0; i<MAX_STATUSCHANGE; i++) {
		eld->sc.data[i].timer = -1;
		eld->sc.data[i].val1  = 0;
		eld->sc.data[i].val2  = 0;
		eld->sc.data[i].val3  = 0;
		eld->sc.data[i].val4  = 0;
	}
#endif

	eld->sc.count = 0;
	eld->sc.opt1  = OPT1_NORMAL;
	eld->sc.opt2  = OPT2_NORMAL;
	eld->sc.opt3  = OPT3_NORMAL;

	elem_calc_status(eld);			// ステータス計算
	map_addiddb(&eld->bl);

	eld->natural_heal_hp = (eld->status.mode == ELMODE_WAIT)? add_timer(tick+ELEM_NATURAL_HEAL_HP_INTERVAL,elem_natural_heal_hp,eld->bl.id,NULL): -1;
	eld->natural_heal_sp = (eld->status.mode == ELMODE_WAIT)? add_timer(tick+ELEM_NATURAL_HEAL_SP_INTERVAL,elem_natural_heal_sp,eld->bl.id,NULL): -1;

	if(eld->status.limit > now)
		diff = (eld->status.limit - now) * 1000;
	else
		diff = 1;
	eld->limit_timer = add_timer(tick+diff,elem_summon_timer,sd->bl.id,NULL);

	eld->view_size = 0;

	return 0;
}

/*==========================================
 * interから精霊のデータ受信
 *------------------------------------------
 */
int elem_recv_elemdata(int account_id,int char_id,struct mmo_elemstatus *p,int flag)
{
	struct map_session_data *sd;

	nullpo_retr(0, p);

	sd = map_id2sd(account_id);

	if(sd == NULL || sd->status.char_id != char_id || (sd->status.elem_id && sd->status.elem_id != p->elem_id))
	{
		if(flag) {
			// 新規作成時なら精霊データを削除する
			intif_delete_elemdata(account_id,char_id,p->elem_id);
		}
		if(sd)
			sd->state.elem_creating = 0;
		return 0;
	}

	if(sd->eld == NULL) {
		sd->eld = (struct elem_data *)aCalloc(1,sizeof(struct elem_data));
		memcpy(&sd->eld->status, p, sizeof(struct mmo_elemstatus));

		if(sd->status.elem_id <= 0)
			sd->status.elem_id = p->elem_id;

		if(!elem_data_init(sd) && sd->bl.prev != NULL)
		{
			if(sd->eld->status.hp <= 0) {	// 死亡
				elem_delete_data(sd);
				sd->state.elem_creating = 0;
				return 0;
			}
			map_addblock(&sd->eld->bl);
			mob_ai_hard_spawn( &sd->eld->bl, 1 );
			clif_spawnelem(sd->eld);
			clif_send_elemstatus(sd);
			elem_save_data(sd);
			skill_unit_move(&sd->eld->bl,gettick(),1);
		}
	}
	sd->state.elem_creating = 0;

	return 0;
}

/*==========================================
 * 精霊削除
 *------------------------------------------
 */
int elem_delete_data(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	if(sd->status.elem_id > 0 && sd->eld) {
		status_change_elemclear(&sd->bl);
		unit_free(&sd->eld->bl,0);
		intif_delete_elemdata(sd->status.account_id,sd->status.char_id,sd->status.elem_id);
		sd->status.elem_id = 0;
		chrif_save(sd,0);
		if(sd->state.storage_flag == 1)
			storage_storage_save(sd);
	}

	return 0;
}

/*==========================================
 * スキルの検索 所有していた場合Lvが返る
 *------------------------------------------
 */
int elem_checkskill(struct elem_data *eld,int skill_id)
{
	if(eld == NULL)
		return 0;
	if(skill_id >= ELEM_SKILLID)
		skill_id -= ELEM_SKILLID;

	if(skill_id >= MAX_ELEMSKILL)
		return 0;
	if(eld->skill[skill_id].id == skill_id + ELEM_SKILLID)
		return eld->skill[skill_id].lv;

	return 0;
}

/*==========================================
 * 精霊モード変更
 *------------------------------------------
 */
int elem_change_mode(struct elem_data *eld, int mode)
{
	nullpo_retr(1, eld);

	if(mode < ELMODE_WAIT || mode > ELMODE_OFFENSIVE)
		return 1;

	elem_unlocktarget(eld);

	// 精霊のステータス変化を終了
	status_change_elemclear(&eld->bl);
	if(eld->msd)
		status_change_elemclear(&eld->msd->bl);

	// 指定されたモードが現モードと同じであれば待機モード
	if(eld->status.mode == mode)
		eld->status.mode = ELMODE_WAIT;
	else
		eld->status.mode = mode;

	// 待機モードに変更するときは自然回復タイマー開始
	if(eld->status.mode == ELMODE_WAIT) {
		unsigned tick = gettick();

		if(eld->natural_heal_hp == -1)
			eld->natural_heal_hp = add_timer(tick+ELEM_NATURAL_HEAL_HP_INTERVAL,elem_natural_heal_hp,eld->bl.id,NULL);
		if(eld->natural_heal_sp == -1)
			eld->natural_heal_sp = add_timer(tick+ELEM_NATURAL_HEAL_SP_INTERVAL,elem_natural_heal_sp,eld->bl.id,NULL);
	}
	else if(eld->natural_heal_hp != -1 || eld->natural_heal_sp != -1)
		elem_natural_heal_timer_delete(eld);

	// 支援モードか防御モードに変更するときはスキル使用
	if(eld->status.mode == ELMODE_PASSIVE || eld->status.mode == ELMODE_DEFENSIVE)
		elem_skilluse(eld,&eld->bl,eld->status.mode);

	return 0;
}

/*==========================================
 * 精霊スキル使用
 *------------------------------------------
 */
int elem_skilluse(struct elem_data *eld, struct block_list *bl, int mode)
{
	struct elem_skill_tree_entry *st;
	int idx, i;
	short skillid = 0, skilllv = 0;

	nullpo_retr(1, eld);
	nullpo_retr(1, bl);

	idx = elem_search_index(eld->status.class_);
	if(idx < 0)
		return 1;

	st = elem_skill_tree[idx];

	for(i = 0; i < MAX_ELEMSKILL_TREE; i++) {
		if(st[i].mode == mode) {
			skillid = st[i].id;
			skilllv = st[i].max;
			break;
		}
	}

	if(skillid > 0) {
		if(unit_skilluse_id(&eld->bl,bl->id,skillid,skilllv) == 0)
			clif_emotion(&eld->bl,9);
	}

	return 0;
}

/*==========================================
 * 経験値取得
 *------------------------------------------
 */
int elem_gainexp(struct elem_data *eld,struct mob_data *md,atn_bignumber base_exp,atn_bignumber job_exp)
{
	nullpo_retr(0, eld);

	if(eld->bl.prev == NULL || unit_isdead(&eld->bl))
		return 0;

	if(md && md->sc.data[SC_RICHMANKIM].timer != -1) {
		base_exp = base_exp * (125 + md->sc.data[SC_RICHMANKIM].val1*11)/100;
		job_exp  = job_exp  * (125 + md->sc.data[SC_RICHMANKIM].val1*11)/100;
	}

	if(eld->msd) {
		pc_gainexp(eld->msd,md,base_exp,job_exp,0);
	}

	return 0;
}

/*==========================================
 * eldにdamageのダメージ
 *------------------------------------------
 */
int elem_damage(struct block_list *src,struct elem_data *eld,int damage)
{
	struct map_session_data *sd = NULL;

	nullpo_retr(0, eld);
	nullpo_retr(0, sd = eld->msd);

	// 既に死んでいたら無効
	if(unit_isdead(&eld->bl))
		return 0;

	// 歩いていたら足を止める
	if((eld->sc.data[SC_ENDURE].timer == -1 && eld->sc.data[SC_BERSERK].timer == -1) || map[eld->bl.m].flag.gvg)
		unit_stop_walking(&eld->bl,battle_config.pc_hit_stop_type);

	if(damage > 0 && eld->sc.data[SC_GRAVITATION_USER].timer != -1)
		status_change_end(&eld->bl, SC_GRAVITATION_USER, -1);

	if(eld->bl.prev == NULL) {
		if(battle_config.error_log)
			printf("elem_damage : BlockError!!\n");
		return 0;
	}

	if(eld->status.hp > eld->max_hp)
		eld->status.hp = eld->max_hp;

	// over kill分は丸める
	if(damage > eld->status.hp)
		damage = eld->status.hp;

	eld->status.hp -= damage;

	// ハイド状態を解除
	status_change_hidden_end(&eld->bl);

	clif_elemupdatestatus(sd,SP_HP);

	// 死亡していた
	if(eld->status.hp <= 0) {
		// スキルユニットからの離脱
		eld->status.hp = 1;
		skill_unit_move(&eld->bl,gettick(),0);
		eld->status.hp = 0;

		elem_delete_data(sd);
	} else {
		if( eld->sc.data[SC_AUTOBERSERK].timer != -1 &&
		    eld->status.hp < eld->max_hp>>2 &&
		    (eld->sc.data[SC_PROVOKE].timer == -1 || eld->sc.data[SC_PROVOKE].val2 == 0) )
		{
			// オートバーサーク発動
			status_change_start(&eld->bl,SC_PROVOKE,10,1,0,0,0,0);
		}
	}

	return 0;
}

/*==========================================
 * HP/SP回復
 *------------------------------------------
 */
int elem_heal(struct elem_data *eld,int hp,int sp)
{
	nullpo_retr(0, eld);

	if(hp + eld->status.hp > eld->max_hp)
		hp = eld->max_hp - eld->status.hp;
	if(sp + eld->status.sp > eld->max_sp)
		sp = eld->max_sp - eld->status.sp;
	eld->status.hp += hp;
	if(eld->status.hp <= 0) {
		eld->status.hp = 0;
		elem_damage(NULL,eld,1);
		hp = 0;
	}
	eld->status.sp += sp;
	if(eld->status.sp <= 0)
		eld->status.sp = 0;
	if(eld->msd) {
		if(hp)
			clif_elemupdatestatus(eld->msd,SP_HP);
		if(sp)
			clif_elemupdatestatus(eld->msd,SP_SP);
	}

	return hp + sp;
}

/*==========================================
 * 自然回復物
 *------------------------------------------
 */
static int elem_natural_heal_hp(int tid,unsigned int tick,int id,void *data)
{
	struct elem_data *eld = map_id2eld(id);
	int bhp;

	nullpo_retr(0, eld);

	if(eld->natural_heal_hp != tid) {
		if(battle_config.error_log)
			printf("elem_natural_heal_hp %d != %d\n",eld->natural_heal_hp,tid);
		return 0;
	}
	eld->natural_heal_hp = -1;

	bhp = eld->status.hp;

	if(eld->ud.walktimer == -1) {
		eld->status.hp += eld->nhealhp;
		if(eld->status.hp > eld->max_hp)
			eld->status.hp = eld->max_hp;
		if(bhp != eld->status.hp && eld->msd)
			clif_elemupdatestatus(eld->msd,SP_HP);
	}
	eld->natural_heal_hp = add_timer(tick+ELEM_NATURAL_HEAL_HP_INTERVAL,elem_natural_heal_hp,eld->bl.id,NULL);

	return 0;
}

static int elem_natural_heal_sp(int tid,unsigned int tick,int id,void *data)
{
	struct elem_data *eld = map_id2eld(id);
	int bsp;

	nullpo_retr(0, eld);

	if(eld->natural_heal_sp != tid) {
		if(battle_config.error_log)
			printf("elem_natural_heal_sp %d != %d\n",eld->natural_heal_sp,tid);
		return 0;
	}
	eld->natural_heal_sp = -1;

	bsp = eld->status.sp;

	if(eld->ud.walktimer == -1) {
		eld->status.sp += eld->nhealsp;
		if(eld->status.sp > eld->max_sp)
			eld->status.sp = eld->max_sp;
		if(bsp != eld->status.sp && eld->msd)
			clif_elemupdatestatus(eld->msd,SP_SP);
	}
	eld->natural_heal_sp = add_timer(tick+ELEM_NATURAL_HEAL_SP_INTERVAL,elem_natural_heal_sp,eld->bl.id,NULL);

	return 0;
}

int elem_natural_heal_timer_delete(struct elem_data *eld)
{
	nullpo_retr(0, eld);

	if(eld->natural_heal_hp != -1) {
		delete_timer(eld->natural_heal_hp,elem_natural_heal_hp);
		eld->natural_heal_hp = -1;
	}
	if(eld->natural_heal_sp != -1) {
		delete_timer(eld->natural_heal_sp,elem_natural_heal_sp);
		eld->natural_heal_sp = -1;
	}

	return 0;
}

/*==========================================
 * 精霊のデータをセーブ
 *------------------------------------------
 */
int elem_save_data(struct map_session_data *sd)
{
	struct elem_data *eld;

	nullpo_retr(0, sd);
	nullpo_retr(0, eld = sd->eld);

	intif_save_elemdata(sd->status.account_id,&sd->eld->status);

	return 0;
}

//
// 初期化物
//
/*==========================================
 * 精霊初期ステータスデータ読み込み
 *------------------------------------------
 */
static int read_elem_db(void)
{
	FILE *fp;
	char line[4096];
	int i, j, k;
	int lines, count = 0;
	struct script_code *script = NULL;
	const char *filename[] = { "db/elem_db.txt", "db/addon/elem_db_add.txt" };

	// DB情報の初期化
	for(i=0; i<MAX_ELEM_DB; i++) {
		if(elem_db[i].script)
			script_free_code(elem_db[i].script);
	}
	memset(elem_db, 0, sizeof(elem_db));
	elem_count = 0;

	for(i = 0; i < 2; i++ ){
		fp = fopen(filename[i], "r");
		if(fp == NULL) {
			if(i > 0)
				continue;
			printf("read_elem_db: open [%s] failed !\n", filename[i]);
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

			nameid = atoi(str[0]);

			if(nameid <= 0)
				continue;

			k = elem_search_index(nameid);
			j = (k >= 0)? k: elem_count;

			if(j >= MAX_ELEM_DB)
				continue;

			elem_db[j].class_  = nameid;
			strncpy(elem_db[j].name,str[1],24);
			strncpy(elem_db[j].jname,str[2],24);
			elem_db[j].lv      = atoi(str[3]);
			elem_db[j].max_hp  = atoi(str[4]);
			elem_db[j].max_sp  = atoi(str[5]);
			elem_db[j].range   = atoi(str[6]);
			elem_db[j].atk1    = atoi(str[7]);
			elem_db[j].atk2    = atoi(str[8]);
			elem_db[j].def     = atoi(str[9]);
			elem_db[j].mdef    = atoi(str[10]);
			elem_db[j].str     = atoi(str[11]);
			elem_db[j].agi     = atoi(str[12]);
			elem_db[j].vit     = atoi(str[13]);
			elem_db[j].int_    = atoi(str[14]);
			elem_db[j].dex     = atoi(str[15]);
			elem_db[j].luk     = atoi(str[16]);
			elem_db[j].size    = atoi(str[17]);
			elem_db[j].race    = atoi(str[18]);
			elem_db[j].element = atoi(str[19]);
			elem_db[j].speed   = atoi(str[20]);
			elem_db[j].adelay  = atoi(str[21]);
			elem_db[j].amotion = atoi(str[22]);
			elem_db[j].dmotion = atoi(str[23]);

			// force \0 terminal
			elem_db[j].name[23]  = '\0';
			elem_db[j].jname[23] = '\0';

			if(k < 0)
				elem_count++;
			count++;

			if((np = strchr(p, '{')) == NULL)
				continue;

			if(!parse_script_line_end(np, filename[i], lines))
				continue;

			if(elem_db[j].script) {
				script_free_code(elem_db[j].script);
			}
			script = parse_script(np, filename[i], lines);
			elem_db[j].script = (script_is_error(script))? NULL: script;
		}
		fclose(fp);
		printf("read %s done (count=%d)\n",filename[i],count);
	}
	return 0;
}

/*==========================================
 * 精霊スキルデータ読み込み
 *------------------------------------------
 */
static int read_elem_skilldb(void)
{
	int i, j, class_ = 0;
	FILE *fp;
	char line[1024], *p;
	const char *filename = "db/elem_skill_tree.txt";

	// スキルツリー
	memset(elem_skill_tree, 0, sizeof(elem_skill_tree));
	fp = fopen(filename, "r");
	if(fp == NULL) {
		printf("read_elem_skilldb: open [%s] failed !\n", filename);
		return 1;
	}
	while(fgets(line,1020,fp)){
		short mode;
		int skillid;
		char *split[4];
		struct elem_skill_tree_entry *st;

		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0]=='/' && line[1]=='/')
			continue;
		for(j=0,p=line;j<4 && p;j++){
			split[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		if(j < 4)
			continue;
		class_ = atoi(split[0]);
		i = elem_search_index(class_);
		if(i < 0)
			continue;

		mode = atoi(split[1]);
		if(mode < ELMODE_WAIT || mode > ELMODE_OFFENSIVE)
			continue;

		skillid = atoi(split[2]);
		if(skillid < ELEM_SKILLID || skillid >= MAX_ELEM_SKILLID)
			continue;

		st = elem_skill_tree[i];
		for(j=0; st[j].id && st[j].id != skillid; j++);

		if(j >= MAX_ELEMSKILL_TREE - 1) {
			// 末尾はアンカーとして0にしておく必要がある
			printf("read_elem_skilldb: skill (%d) is over max tree %d!!\n", skillid, MAX_ELEMSKILL_TREE);
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

		st[j].mode = mode;
		st[j].id   = skillid;
		st[j].max  = atoi(split[3]);

		if(st[j].max > skill_get_max(skillid))
			st[j].max = skill_get_max(skillid);
	}
	fclose(fp);
	printf("read %s done\n", filename);

	return 0;
}

/*==========================================
 * 精霊DBのリロード
 *------------------------------------------
 */
void elem_reload(void)
{
	read_elem_db();
	read_elem_skilldb();
}

/*==========================================
 * 初期化処理
 *------------------------------------------
 */
int do_init_elem(void)
{
	unsigned int tick = gettick();

	read_elem_db();
	read_elem_skilldb();

	add_timer_func_list(elem_natural_heal_hp);
	add_timer_func_list(elem_natural_heal_sp);
	add_timer_func_list(elem_summon_timer);
	add_timer_func_list(elem_ai_timer);

	add_timer_interval(tick+MIN_ELEMTHINKTIME,elem_ai_timer,0,NULL,MIN_ELEMTHINKTIME);

	return 0;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
int do_final_elem(void)
{
	int i;

	for(i = 0; i < elem_count; i++) {
		if(elem_db[i].script) {
			script_free_code(elem_db[i].script);
		}
	}
	return 0;
}
