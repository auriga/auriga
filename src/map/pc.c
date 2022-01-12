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
#include <ctype.h>
#include <time.h>

#include "timer.h"
#include "db.h"
#include "nullpo.h"
#include "malloc.h"
#include "lock.h"
#include "utils.h"

#include "map.h"
#include "path.h"
#include "chrif.h"
#include "clif.h"
#include "intif.h"
#include "msg.h"
#include "pc.h"
#include "npc.h"
#include "mob.h"
#include "pet.h"
#include "homun.h"
#include "itemdb.h"
#include "script.h"
#include "battle.h"
#include "skill.h"
#include "party.h"
#include "guild.h"
#include "chat.h"
#include "trade.h"
#include "storage.h"
#include "vending.h"
#include "status.h"
#include "socket.h"
#include "friend.h"
#include "date.h"
#include "unit.h"
#include "ranking.h"
#include "merc.h"
#include "buyingstore.h"
#include "elem.h"
#include "achieve.h"
#include "memorial.h"

#define PVP_CALCRANK_INTERVAL 1000	// PVP順位計算の間隔

static atn_bignumber exp_table[22][MAX_LEVEL];

// 属性テーブル
int attr_fix_table[MAX_ELE_LEVEL][ELE_MAX][ELE_MAX];

// JOB TABLE
//    NV,SM,MG,AC,AL,MC,TF,KN,PR,WZ,BS,HT,AS,CR,MO,SA,RG,AM,BA,DC,SNV,TK,SG,SL,GS,NJ,MB,DK,DA,RK,WL,RA,AB,NC,GC,LG,SO,MI,WA,SR,GN,SC,ESNV,KG,OB,RB,SU
int max_job_table[PC_UPPER_MAX][PC_JOB_MAX] = {
	{ 10,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,99,50,50,50,70,70,50,50,50,60,60,60,60,60,60,60,60,60,60,60,60,60,50,60,60,60,50 }, // 通常
	{ 10,50,50,50,50,50,50,70,70,70,70,70,70,70,70,70,70,70,70,70,99,50,50,50,70,70,50,50,50,60,60,60,60,60,60,60,60,60,60,60,60,60,50,60,60,60,50 }, // 転生
	{ 10,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,99,50,50,50,70,70,50,50,50,60,60,60,60,60,60,60,60,60,60,60,60,60,50,60,60,60,50 }, // 養子
};

static const unsigned int equip_pos[EQUIP_INDEX_MAX] = {
	LOC_LACCESSORY,
	LOC_RACCESSORY,
	LOC_SHOES,
	LOC_ROBE,
	LOC_HEAD,
	LOC_HEAD3,
	LOC_HEAD2,
	LOC_BODY,
	LOC_LARM,
	LOC_RARM,
	LOC_ARROW,
	LOC_COSTUME_HEAD,
	LOC_COSTUME_HEAD3,
	LOC_COSTUME_HEAD2,
	LOC_COSTUME_ROBE,
	LOC_COSTUME_FLOOR,
	LOC_ARMOR_SHADOW,
	LOC_WEAPON_SHADOW,
	LOC_SHIELD_SHADOW,
	LOC_SHOES_SHADOW,
	LOC_RACCESSORY_SHADOW,
	LOC_LACCESSORY_SHADOW
};

static char GM_account_filename[1024] = "conf/GM_account.txt";
static struct dbt *gm_account_db = NULL;

static struct skill_tree_entry {
	int id;
	int max;
	struct {
		short id,lv;
	} need[6];
	unsigned short base_level;
	unsigned short job_level;
	short class_level;	// 再振り時の不正防止　ノビ:0 一次:1 二次:2 三次:3
} skill_tree[PC_UPPER_MAX][PC_JOB_MAX][MAX_SKILL_TREE];

static int dummy_gm_account = 0;

/*==========================================
 * ローカルプロトタイプ宣言 (必要な物のみ)
 *------------------------------------------
 */
static int pc_dead(struct block_list *src,struct map_session_data *sd);
static int pc_nightmare_drop(struct map_session_data *sd,short flag);
static int pc_equiplookall(struct map_session_data *sd);
static int pc_checkitemlimit(struct map_session_data *sd, int idx, unsigned int tick, unsigned int now, int first);
static int pc_setitemlimit(struct map_session_data *sd);


/*==========================================
 * スキルツリー情報の検索
 *------------------------------------------
 */
static struct skill_tree_entry* pc_search_skilltree(struct pc_base_job *bj, int skillid)
{
	int min = -1;
	int max = MAX_SKILL_TREE;
	struct skill_tree_entry *st;

	nullpo_retr(NULL, bj);

	st = skill_tree[bj->upper][bj->job];

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
int pc_get_skilltree_max(struct pc_base_job *bj,int skillid)
{
	struct skill_tree_entry *st;

	st = pc_search_skilltree(bj, skillid);
	if(st == NULL)
		return 0;

	return st->max;
}

/*==========================================
 * GM関連
 *------------------------------------------
 */
void pc_set_gm_account_fname(const char *str)
{
	strncpy(GM_account_filename,str,sizeof(GM_account_filename)-1);
}

int pc_isGM(struct map_session_data *sd)
{
	struct gm_account *p;

	nullpo_retr(0, sd);

	if( (p = (struct gm_account *)numdb_search(gm_account_db,sd->status.account_id)) == NULL )
		return 0;
	return p->level;
}

int pc_numisGM(int account_id)
{
	struct gm_account *p;

	if( (p = (struct gm_account *)numdb_search(gm_account_db,account_id)) == NULL )
		return 0;
	return p->level;
}

int pc_get_gm_account_dummy(void)
{
	return dummy_gm_account;
}

/*==========================================
 * PCが終了できるかどうかの判定
 *------------------------------------------
 */
int pc_isquitable(struct map_session_data *sd)
{
	unsigned int tick = gettick();

	nullpo_retr(1, sd);

	if(!unit_isdead(&sd->bl) && (sd->sc.opt1 || (sd->sc.opt2 & ~OPT2_ANGELUS)))
		return 0;
	if(sd->ud.skilltimer != -1)
		return 0;
	if(DIFF_TICK(tick, sd->ud.canact_tick) < 0)
		return 0;
	if(unit_counttargeted(&sd->bl,0) > 0)
		return 0;
	if(unit_isrunning(&sd->bl))
		return 0;
	if(sd->sc.data[SC_MARIONETTE].timer != -1)
		return 0;
	if(sd->sc.data[SC_DANCING].timer != -1 && sd->sc.data[SC_DANCING].val4) {
		struct skill_unit_group *sg = map_id2sg(sd->sc.data[SC_DANCING].val2);
		if(sg && sg->src_id == sd->bl.id)
			return 0;
	}

	return 1;
}

/*==========================================
 * 無敵時間タイマー
 *------------------------------------------
 */
static int pc_invincible_timer(int tid,unsigned int tick,int id,void *data)
{
	struct map_session_data *sd = map_id2sd(id);

	if(sd == NULL)
		return 1;

	if(sd->invincible_timer != tid) {
		if(battle_config.error_log)
			printf("invincible_timer %d != %d\n",sd->invincible_timer,tid);
		return 0;
	}
	sd->invincible_timer = -1;
	skill_unit_move(&sd->bl,tick,1);

	return 0;
}

/*==========================================
 * 無敵時間タイマーセット
 *------------------------------------------
 */
int pc_setinvincibletimer(struct map_session_data *sd,int val)
{
	nullpo_retr(0, sd);

	if(sd->invincible_timer != -1)
		delete_timer(sd->invincible_timer,pc_invincible_timer);
	sd->invincible_timer = add_timer(gettick()+val,pc_invincible_timer,sd->bl.id,NULL);

	return 0;
}

/*==========================================
 * 無敵時間タイマー削除
 *------------------------------------------
 */
int pc_delinvincibletimer(struct map_session_data *sd, int flag)
{
	nullpo_retr(0, sd);

	if(sd->invincible_timer != -1) {
		delete_timer(sd->invincible_timer,pc_invincible_timer);
		sd->invincible_timer = -1;
		if(flag)
			skill_unit_move(&sd->bl,gettick(),1);
	}

	return 0;
}

/*==========================================
 * 気球タイマー
 *------------------------------------------
 */
static int pc_spiritball_timer(int tid,unsigned int tick,int id,void *data)
{
	struct map_session_data *sd = map_id2sd(id);
	int i;

	if(sd == NULL)
		return 1;

	if(sd->spiritball.timer[0] != tid) {
		if(battle_config.error_log)
			printf("spirit_timer %d != %d\n",sd->spiritball.timer[0],tid);
		return 0;
	}
	sd->spiritball.timer[0] = -1;
	for(i=1; i<sd->spiritball.num; i++) {
		sd->spiritball.timer[i-1] = sd->spiritball.timer[i];
		sd->spiritball.timer[i] = -1;
	}
	sd->spiritball.num--;
	if(sd->spiritball.num < 0)
		sd->spiritball.num = 0;
	clif_spiritball(sd);

	return 0;
}

/*==========================================
 * 気球タイマーセット
 *------------------------------------------
 */
int pc_addspiritball(struct map_session_data *sd,int interval,int num)
{
	int max = skill_get_max(MO_CALLSPIRITS);

	nullpo_retr(0, sd);

	/* 職業がモンクと修羅の場合 */
	if(sd->s_class.job == PC_JOB_MO || sd->s_class.job == PC_JOB_SR)
		max = pc_checkskill(sd,MO_CALLSPIRITS);		// 気功の習得レベルが最大数

	/* 潜龍昇天 */
	if(sd->sc.data[SC_RAISINGDRAGON].timer != -1)
		max += sd->sc.data[SC_RAISINGDRAGON].val1;

	if(max > MAX_SPIRITBALL)
		max = MAX_SPIRITBALL;

	if(sd->spiritball.num < 0)
		sd->spiritball.num = 0;

	if(max > 0) {
		int i, j;
		unsigned int tick = gettick();
		for(i = num; i > 0; i--) {
			if(sd->spiritball.num >= max) {
				if(sd->spiritball.timer[0] != -1) {
					delete_timer(sd->spiritball.timer[0],pc_spiritball_timer);
					sd->spiritball.timer[0] = -1;
				}
				for(j = 1; j < max; j++) {
					sd->spiritball.timer[j-1] = sd->spiritball.timer[j];
					sd->spiritball.timer[j] = -1;
				}
			} else {
				sd->spiritball.num++;
			}
			sd->spiritball.timer[sd->spiritball.num-1] = add_timer(tick+interval+sd->spiritball.num,pc_spiritball_timer,sd->bl.id,NULL);
		}
	}
	clif_spiritball(sd);

	return 0;
}

/*==========================================
 * 気球タイマー削除
 *------------------------------------------
 */
int pc_delspiritball(struct map_session_data *sd,int count,int type)
{
	int i;

	nullpo_retr(0, sd);

	if(sd->spiritball.num <= 0) {
		sd->spiritball.num = 0;
		return 0;
	}

	if(count > sd->spiritball.num)
		count = sd->spiritball.num;
	sd->spiritball.num -= count;
	if(count > MAX_SPIRITBALL)
		count = MAX_SPIRITBALL;

	for(i=0; i<count; i++) {
		if(sd->spiritball.timer[i] != -1) {
			delete_timer(sd->spiritball.timer[i],pc_spiritball_timer);
			sd->spiritball.timer[i] = -1;
		}
	}
	for(i=count; i<MAX_SPIRITBALL; i++) {
		sd->spiritball.timer[i-count] = sd->spiritball.timer[i];
		sd->spiritball.timer[i] = -1;
	}

	if(!type)
		clif_spiritball(sd);

	return 0;
}

/*==========================================
 * コインタイマー
 *-----------------------------------------
 */
static int pc_coin_timer(int tid,unsigned int tick,int id,void *data)
{
	struct map_session_data *sd = map_id2sd(id);
	int i;

	if(sd == NULL)
		return 1;

	if(sd->coin.timer[0] != tid) {
		if(battle_config.error_log)
			printf("coin_timer %d != %d\n",sd->coin.timer[0],tid);
		return 0;
	}
	sd->coin.timer[0] = -1;
	for(i=1; i<sd->coin.num; i++) {
		sd->coin.timer[i-1] = sd->coin.timer[i];
		sd->coin.timer[i] = -1;
	}
	sd->coin.num--;
	if(sd->coin.num < 0)
		sd->coin.num = 0;
	clif_coin(sd);

	return 0;
}

/*==========================================
 * コインタイマーセット
 *-----------------------------------------
 */
int pc_addcoin(struct map_session_data *sd,int interval,int max)
{
	nullpo_retr(0, sd);

	if(max > MAX_SPIRITBALL)
		max = MAX_SPIRITBALL;
	if(sd->coin.num < 0)
		sd->coin.num = 0;

	if(max > 0) {
		unsigned int tick = gettick();
		if(sd->coin.num >= max) {
			int i;
			if(sd->coin.timer[0] != -1) {
				delete_timer(sd->coin.timer[0],pc_coin_timer);
				sd->coin.timer[0] = -1;
			}
			for(i=1; i<max; i++) {
				sd->coin.timer[i-1] = sd->coin.timer[i];
				sd->coin.timer[i] = -1;
			}
		} else {
			sd->coin.num++;
		}
		sd->coin.timer[sd->coin.num-1] = add_timer(tick+interval+sd->coin.num,pc_coin_timer,sd->bl.id,NULL);
	}
	clif_coin(sd);

	return 0;
}

/*==========================================
 * コインタイマー削除
 *-----------------------------------------
 */
int pc_delcoin(struct map_session_data *sd,int count,int type)
{
	int i;

	nullpo_retr(0, sd);

	if(sd->coin.num <= 0) {
		sd->coin.num = 0;
		return 0;
	}

	if(count > sd->coin.num)
		count = sd->coin.num;
	sd->coin.num -= count;
	if(count > MAX_SPIRITBALL)
		count = MAX_SPIRITBALL;

	for(i=0; i<count; i++) {
		if(sd->coin.timer[i] != -1) {
			delete_timer(sd->coin.timer[i],pc_coin_timer);
			sd->coin.timer[i] = -1;
		}
	}
	for(i=count; i<MAX_SPIRITBALL; i++) {
		sd->coin.timer[i-count] = sd->coin.timer[i];
		sd->coin.timer[i] = -1;
	}

	if(!type)
		clif_coin(sd);

	return 0;
}

/*==========================================
 * 影狼・朧の球体タイマー
 *-----------------------------------------
 */
static int pc_elementball_timer(int tid, unsigned int tick, int id, void *data)
{
	struct map_session_data *sd = map_id2sd(id);
	int i;

	if( sd == NULL )
		return 1;

	// 不正なタイマーID
	if( sd->elementball.timer[0] != tid )
	{
		if(battle_config.error_log)
			printf("elementball_timer %d != %d\n",sd->elementball.timer[0],tid);
		return 0;
	}

	// 球体のタイマークリア
	sd->elementball.timer[0] = -1;
	for( i = 1; i < sd->elementball.num; i++ )
	{
		sd->elementball.timer[i-1] = sd->elementball.timer[i];
		sd->elementball.timer[i] = -1;
	}

	// 球体の数を減らす
	sd->elementball.num--;
	if(sd->elementball.num < 0)
		sd->elementball.num = 0;

	// 属性値クリア
	if(!sd->elementball.num)
		sd->elementball.ele = ELE_NEUTRAL;

#ifdef PRE_RENEWAL
	// 土属性ならatkが減少するためステータスを計算させる
	if(sd->elementball.ele == ELE_EARTH)
		status_calc_pc(sd,0);
#endif

	// パケット送信
	clif_elementball(sd);

	return 0;
}

/*==========================================
 * 影狼・朧の球体セット
 *-----------------------------------------
 */
int pc_addelementball(struct map_session_data *sd, int interval, int max, short ele)
{
	nullpo_retr(0, sd);

	// 最大値チェック
	if(max > MAX_ELEMENTBALL)
		max = MAX_ELEMENTBALL;

	// 負数チェック
	if(sd->elementball.num < 0)
		sd->elementball.num = 0;

	if( max > 0 )
	{
		unsigned int tick = gettick();
		if( sd->elementball.num >= max ) {
			int i;
			if( sd->elementball.timer[0] != -1 )
			{
				delete_timer(sd->elementball.timer[0],pc_elementball_timer);
				sd->elementball.timer[0] = -1;
			}
			for( i = 1; i < max; i++ )
			{
				sd->elementball.timer[i-1] = sd->elementball.timer[i];
				sd->elementball.timer[i] = -1;
			}
		} else {
			sd->elementball.num++;
		}
		sd->elementball.timer[sd->elementball.num-1] = add_timer(tick+interval+sd->elementball.num,pc_elementball_timer,sd->bl.id,NULL);
		sd->elementball.ele = ele;
	}

#ifdef PRE_RENEWAL
	// 土属性ならatkが向上するためステータスを計算させる
	if(ele == ELE_EARTH)
		status_calc_pc(sd,0);
#endif

	// パケット送信
	clif_elementball(sd);

	return 0;
}

/*==========================================
 * 影狼・朧のタイマー削除
 *-----------------------------------------
 */
int pc_delelementball(struct map_session_data *sd, int count, int type)
{
	int i;

	nullpo_retr(0, sd);

	// 負数チェック
	if( sd->elementball.num <= 0 )
	{
		sd->elementball.num = 0;
		sd->elementball.ele = ELE_NEUTRAL;
		return 0;
	}

	// 削除数のチェック
	if(count > sd->elementball.num)
		count = sd->elementball.num;

	sd->elementball.num -= count;

	if(count > MAX_ELEMENTBALL)
		count = MAX_ELEMENTBALL;

	for( i = 0; i < count; i++ )
	{
		if( sd->elementball.timer[i] != -1 )
		{
			delete_timer(sd->elementball.timer[i],pc_elementball_timer);
			sd->elementball.timer[i] = -1;
		}
	}

	for( i = count; i < MAX_ELEMENTBALL; i++ )
	{
		sd->elementball.timer[i-count] = sd->elementball.timer[i];
		sd->elementball.timer[i] = -1;
	}

	// 土属性ならdefとatkが変動するためステータスを計算させる
	if(sd->elementball.ele == ELE_EARTH)
		status_calc_pc(sd,0);

	// 属性値クリア
	if(sd->elementball.num < 1)
		sd->elementball.ele = ELE_NEUTRAL;

	if(!type)
		clif_elementball(sd);

	return 0;
}

/*==========================================
 * Expペナルティ
 *   type&1 : 経験値更新
 *   type&2 : レディムプティオ
 *------------------------------------------
 */
int pc_exp_penalty(struct map_session_data *sd, struct map_session_data *ssd, int per, int type)
{
	atn_bignumber loss_base = 0, loss_job = 0;
	int idx,loss = 0;

	nullpo_retr(0, sd);

	if(!(type&2)) {
		if(map[sd->bl.m].flag.nopenalty)
			return 0;
		if(sd->sc.data[SC_BABY].timer != -1)
			return 0;
		if(sd->sc.data[SC_LIFEINSURANCE].timer != -1) {
			if(--sd->sc.data[SC_LIFEINSURANCE].val1 <= 0)
				status_change_end(&sd->bl,SC_LIFEINSURANCE,-1);
			return 0;
		}
	}
	if(sd->s_class.job == PC_JOB_NV || map[sd->bl.m].flag.gvg)
		return 0;

	idx = pc_search_inventory(sd, 6413);	// 身代わりの護符

	// レディムプティオのペナルティの場合、オーラならば現在の取得経験値から差し引く
	if(battle_config.death_penalty_base > 0) {
		atn_bignumber nextbase;
		if( battle_config.death_penalty_type&2 && ((nextbase = pc_nextbaseexp(sd)) > 0 || !(type&2)) ) {
			loss_base = nextbase;
		} else {
			loss_base = sd->status.base_exp;
		}
		loss_base = loss_base * battle_config.death_penalty_base / 10000 * per / 100;

		if(loss_base) {
			if(idx < 0) {
				sd->status.base_exp -= (int)loss_base;
				if(sd->status.base_exp < 0)
					sd->status.base_exp = 0;
				if(type&1)
					clif_updatestatus(sd,SP_BASEEXP);
			} else
				loss++;
		}
	}

	if(battle_config.death_penalty_job > 0) {
		atn_bignumber nextjob;
		if( battle_config.death_penalty_type&2 && ((nextjob = pc_nextjobexp(sd)) > 0 || !(type&2)) ) {
			loss_job = nextjob;
		} else {
			loss_job = sd->status.job_exp;
		}
		loss_job = loss_job * battle_config.death_penalty_job / 10000 * per / 100;

		if(loss_job) {
			if(idx < 0) {
				sd->status.job_exp -= (int)loss_job;
				if(sd->status.job_exp < 0)
					sd->status.job_exp = 0;
				if(type&1)
					clif_updatestatus(sd,SP_JOBEXP);
			} else
				loss++;
		}
	}

	if(loss) {
		pc_delitem(sd,idx,1,0,1);
		clif_msgstringtable(sd,0x729);	// 身代わりの護符が自動消費されました。
	}

	if(ssd) {
		// PK仕様、PKマップで攻撃が人間かつ自分でない(GXなどの対策)
		if(map[sd->bl.m].flag.pk && sd->bl.id != ssd->bl.id && ranking_get_point(ssd,RK_PK) >= battle_config.pk_murderer_point) {
			if(loss_base > 0 || loss_job > 0)
				pc_gainexp(ssd,NULL,loss_base,loss_job,0);
		}
	}
	return 1;
}

/*==========================================
 * リスタート時のデータセット
 *------------------------------------------
 */
int pc_setrestartvalue(struct map_session_data *sd,int type)
{
	nullpo_retr(0, sd);

	if(sd->special_state.restart_full_recover) {	// オシリスカード
		sd->status.hp = sd->status.max_hp;
		sd->status.sp = sd->status.max_sp;
	} else {
		if(sd->s_class.job != PC_JOB_NV) {	// ノビは既に死亡直後でHP補正済み
			if(battle_config.restart_hp_rate <= 0) {
				sd->status.hp = 1;
			} else {
				sd->status.hp = sd->status.max_hp * battle_config.restart_hp_rate /100;
				if(sd->status.hp <= 0)
					sd->status.hp = 1;
			}
		}
		if(battle_config.restart_sp_rate > 0) {
			int sp = sd->status.max_sp * battle_config.restart_sp_rate /100;
			if(sd->status.sp < sp)
				sd->status.sp = sp;
		}
	}
	if(type&1) {
		clif_updatestatus(sd,SP_HP);
		clif_updatestatus(sd,SP_SP);
	}
	if(type&2) {
		if(!(battle_config.death_penalty_type&1))	// デスペナ
			pc_exp_penalty(sd, NULL, 100, type&1);

		if(!map[sd->bl.m].flag.nozenypenalty) {
			atn_bignumber zeny_penalty;
			zeny_penalty = (atn_bignumber)battle_config.zeny_penalty + ((atn_bignumber)sd->status.base_level * (atn_bignumber)battle_config.zeny_penalty_by_lvl);
			if(battle_config.zeny_penalty_percent > 0)
				zeny_penalty = zeny_penalty + ((atn_bignumber)sd->status.zeny * (atn_bignumber)battle_config.zeny_penalty_percent / 10000);
			if(zeny_penalty >= 1) {
				if(zeny_penalty >= (atn_bignumber)sd->status.zeny)
					sd->status.zeny = 0;
				else
					sd->status.zeny -= (int)zeny_penalty;
				if(type & 1)
					clif_updatestatus(sd, SP_ZENY);
			}
		}
	}

	return 0;
}

/*==========================================
 * saveに必要なステータス修正を行なう
 *------------------------------------------
 */
int pc_makesavestatus(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	// 服の色は色々弊害が多いので保存対象にはしない
	if(!battle_config.save_clothcolor)
		sd->status.clothes_color = 0;

	// 死亡状態だったのでhpを1、位置をセーブ場所に変更
	if(unit_isdead(&sd->bl)) {
		pc_setrestartvalue(sd,0);
		memcpy(&sd->status.last_point,&sd->status.save_point,sizeof(sd->status.last_point));
	} else {
		memcpy(sd->status.last_point.map,sd->mapname,24);
		sd->status.last_point.x = sd->bl.x;
		sd->status.last_point.y = sd->bl.y;
	}

	// セーブ禁止マップだったので指定位置に移動
	if(map[sd->bl.m].flag.nosave) {
		struct map_data *m = &map[sd->bl.m];
		if(strcmp(m->save.map,"SavePoint") == 0)
			memcpy(&sd->status.last_point,&sd->status.save_point,sizeof(sd->status.last_point));
		else
			memcpy(&sd->status.last_point,&m->save,sizeof(sd->status.last_point));
	}
	// メモリアルダンジョンに居るので、位置をセーブ場所に変更
	else if(map[sd->bl.m].memorial_id) {
		memcpy(&sd->status.last_point,&sd->status.save_point,sizeof(sd->status.last_point));
	}

	// アルケミの連続成功数保存
	if(battle_config.save_am_pharmacy_success && (sd->am_pharmacy_success > 0 || ranking_get_point(sd,RK_ALCHEMIST) > 0))
		pc_setglobalreg(sd,"PC_PHARMACY_SUCCESS_COUNT",sd->am_pharmacy_success);

	// ランキングポイントの保存
	if(battle_config.save_all_ranking_point_when_logout)
		ranking_setglobalreg_all(sd);

	// クローンスキル保存
	if(sd->skill_clone.id || sd->skill_clone.lv) {
		pc_setglobalreg(sd,"PC_CLONESKILL_ID",sd->skill_clone.id);
		pc_setglobalreg(sd,"PC_CLONESKILL_LV",sd->skill_clone.lv);
	}

	// リプロデュース保存
	if(sd->skill_reproduce.id || sd->skill_reproduce.lv) {
		pc_setglobalreg(sd,"PC_REPRODUCE_ID",sd->skill_reproduce.id);
		pc_setglobalreg(sd,"PC_REPRODUCE_LV",sd->skill_reproduce.lv);
	}

	// キラー情報保存
	if(battle_config.save_pckiller_type) {
		pc_setglobalreg(sd,"PC_KILL_CHAR",sd->kill.char_id);
		pc_setglobalreg(sd,"PC_KILLED_CHAR",sd->kill.merderer_char_id);
	}

	// ショップポイント保存
	pc_setglobalreg(sd,"PC_SHOP_POINT",sd->shop_point);

	// 預金保存
	pc_setaccountreg(sd,"#PC_DEPOSIT",sd->deposit);

	// マナーポイントがプラスだった場合0に
	if(sd->status.manner > 0)
		sd->status.manner = 0;

	// optionのコピー
	sd->status.option = sd->sc.option;

	return 0;
}

/*==========================================
 * 座る
 *------------------------------------------
 */
void pc_setsit(struct map_session_data *sd)
{
	nullpo_retv(sd);

	sd->state.dead_sit = 2;
	clif_status_load_id(sd,SI_SIT,1);
}

/*==========================================
 * 立ち上がる
 *------------------------------------------
 */
void pc_setstand(struct map_session_data *sd)
{
	nullpo_retv(sd);

	if(sd->sc.data[SC_TENSIONRELAX].timer != -1)
		status_change_end(&sd->bl,SC_TENSIONRELAX,-1);

	sd->state.dead_sit = 0;
	clif_status_load_id(sd,SI_SIT,0);
}

/*==========================================
 * セーブポイントの保存
 *------------------------------------------
 */
int pc_setsavepoint(struct map_session_data *sd,const char *mapname,int x,int y)
{
	nullpo_retr(0, sd);

	strncpy(sd->status.save_point.map,mapname,24);
	sd->status.save_point.map[23] = '\0';	// force \0 terminal
	sd->status.save_point.x = x;
	sd->status.save_point.y = y;

	return 0;
}

/*==========================================
 * 接続時の初期化
 *------------------------------------------
 */
void pc_setnewpc(struct map_session_data *sd,int account_id,int char_id,int login_id1,int client_tick,int sex)
{
	nullpo_retv(sd);

	sd->bl.id       = account_id;
	sd->char_id     = char_id;
	sd->login_id1   = login_id1;
	sd->client_tick = client_tick;
	sd->sex         = sex;
	sd->state.auth  = 0;
	sd->bl.type     = BL_PC;
	sd->status_calc_pc_process  = 0;
	sd->state.waitingdisconnect = 0;

	return;
}

/*==========================================
 * 装備箇所を返す
 *------------------------------------------
 */
int pc_equippoint(struct map_session_data *sd,int n)
{
	int ep = LOC_NOTHING;

	nullpo_retr(LOC_NOTHING, sd);

	if(sd->inventory_data[n]) {
		int look = sd->inventory_data[n]->look;
		ep = sd->inventory_data[n]->equip;
		if(look == WT_DAGGER || look == WT_1HSWORD || look == WT_1HAXE) {
			if(ep == LOC_RARM && (pc_checkskill(sd,AS_LEFT) > 0 || sd->s_class.job == PC_JOB_AS || sd->s_class.job == PC_JOB_GC || 
				pc_checkskill(sd,KO_LEFT) > 0 || sd->s_class.job == PC_JOB_KG || sd->s_class.job == PC_JOB_OB))
				return LOC_RARM | LOC_LARM;
		}
	}

	return ep;
}

/*==========================================
 * 武器タイプを計算
 *------------------------------------------
 */
static int pc_calcweapontype(struct map_session_data *sd)
{
	short right, left;

	nullpo_retr(0, sd);

	right = sd->weapontype1;
	left  = sd->weapontype2;

	if(right != WT_FIST && left == WT_FIST)			// 右手武器のみ
		sd->status.weapon = right;
	else if(right == WT_FIST && left != WT_FIST)		// 左手武器のみ
		sd->status.weapon = left;
	else if(right == WT_DAGGER && left == WT_DAGGER)	// 双短剣
		sd->status.weapon = WT_DOUBLE_DD;
	else if(right == WT_1HSWORD && left == WT_1HSWORD)	// 双片手剣
		sd->status.weapon = WT_DOUBLE_SS;
	else if(right == WT_1HAXE && left == WT_1HAXE)		// 双片手斧
		sd->status.weapon = WT_DOUBLE_AA;
	else if( (right == WT_DAGGER && left == WT_1HSWORD) || (right == WT_1HSWORD && left == WT_DAGGER) )	// 短剣-片手剣
		sd->status.weapon = WT_DOUBLE_DS;
	else if( (right == WT_DAGGER && left == WT_1HAXE) || (right == WT_1HAXE && left == WT_DAGGER) )		// 短剣-片手斧
		sd->status.weapon = WT_DOUBLE_DA;
	else if( (right == WT_1HSWORD && left == WT_1HAXE) || (right == WT_1HAXE && left == WT_1HSWORD) )	// 片手剣-片手斧
		sd->status.weapon = WT_DOUBLE_SA;
	else
		sd->status.weapon = right;

	return 0;
}

/*==========================================
 * クラスIDから職業値のビットを返す
 *------------------------------------------
 */
unsigned int pc_get_job_bit(int job)
{
	unsigned int bit = 0;

	// 職業値をdbの職業値に合わせて設定
	switch(job) {
		case PC_JOB_NV:		// ノービス
			bit = 0x00000001;
			break;
		case PC_JOB_SM:		// ソードマン
			bit = 0x00000002;
			break;
		case PC_JOB_MG:		// マジシャン
			bit = 0x00000004;
			break;
		case PC_JOB_AC:		// アーチャー
			bit = 0x00000008;
			break;
		case PC_JOB_AL:		// アコライト
		case PC_JOB_MB:		// キョンシー（暫定）
			bit = 0x00000010;
			break;
		case PC_JOB_MC:		// マーチャント
			bit = 0x00000020;
			break;
		case PC_JOB_TF:		// シーフ
			bit = 0x00000040;
			break;
		case PC_JOB_KN:		// ナイト
		case PC_JOB_DK:		// デスナイト（暫定）
		case PC_JOB_RK:		// ルーンナイト（暫定）
			bit = 0x00000080;
			break;
		case PC_JOB_PR:		// プリースト
		case PC_JOB_AB:		// アークビショップ（暫定）
			bit = 0x00000100;
			break;
		case PC_JOB_WZ:		// ウィザード
		case PC_JOB_WL:		// ウォーロック（暫定）
			bit = 0x00000200;
			break;
		case PC_JOB_BS:		// ブラックスミス
		case PC_JOB_NC:		// メカニック（暫定）
			bit = 0x00000400;
			break;
		case PC_JOB_HT:		// ハンター
		case PC_JOB_RA:		// レンジャー（暫定）
			bit = 0x00000800;
			break;
		case PC_JOB_AS:		// アサシン
		case PC_JOB_GC:		// ギロチンクロス（暫定）
			bit = 0x00001000;
			break;
		case PC_JOB_CR:		// クルセイダー
		case PC_JOB_LG:		// ロイヤルガード（暫定）
			bit = 0x00004000;
			break;
		case PC_JOB_MO:		// モンク
		case PC_JOB_SR:		// 修羅（暫定）
			bit = 0x00008000;
			break;
		case PC_JOB_SA:		// セージ
		case PC_JOB_SO:		// ソーサラー（暫定）
			bit = 0x00010000;
			break;
		case PC_JOB_RG:		// ローグ
		case PC_JOB_SC:		// シャドウチェイサー（暫定）
			bit = 0x00020000;
			break;
		case PC_JOB_AM:		// アルケミスト
		case PC_JOB_DA:		// ダークコレクター（暫定）
		case PC_JOB_GN:		// ジェネティック（暫定）
			bit = 0x00040000;
			break;
		case PC_JOB_BA:		// バード
		case PC_JOB_MI:		// ミンストレル（暫定）
			bit = 0x00080000;
			break;
		case PC_JOB_DC:		// ダンサー
		case PC_JOB_WA:		// ワンダラー（暫定）
			bit = 0x00100000;
			break;
		case PC_JOB_SNV:	// スーパーノービス
		case PC_JOB_ESNV:	// 拡張スーパーノービス
			bit = 0x00800000;
			break;
		case PC_JOB_TK:		// テコンキッド
			bit = 0x01000000;
			break;
		case PC_JOB_SG:		// 拳聖
			bit = 0x02000000;
			break;
		case PC_JOB_SL:		// ソウルリンカー
			bit = 0x08000000;
			break;
		case PC_JOB_GS:		// ガンスリンガー
		case PC_JOB_RL:		// リベリオン（暫定）
			bit = 0x10000000;
			break;
		case PC_JOB_NJ:		// 忍者
		case PC_JOB_KG:		// 影狼（暫定）
		case PC_JOB_OB:		// 朧（暫定）
			bit = 0x20000000;
			break;
		case PC_JOB_SUM:		// サモナー（暫定）
			bit = 0x40000000;
			break;
	}

	return bit;
}

/*==========================================
 * 禁止されているアイテムかどうか
 *------------------------------------------
 */
static int pc_check_prohibition(struct map_session_data *sd, int zone)
{
	int m, ban = 0;

	nullpo_retr(1, sd);

	if(zone <= 0)
		return 0;

	m = sd->bl.m;

	if(map[m].flag.turbo && zone&16)
		ban = 1;
	else if(map[m].flag.noteleport && zone&32)
		ban = 1;
	else if(map[m].flag.noreturn && zone&64)
		ban = 1;
	else if(map[m].flag.nobranch && zone&128)
		ban = 1;
	else if(map[m].flag.normal && zone&1)
		ban = 1;
	else if(map[m].flag.pvp && zone&2)
		ban = 1;
	else if(map[m].flag.gvg && zone&4)
		ban = 1;
	else if(map[m].flag.pk && zone&8)
		ban = 1;
	else if(map[m].flag.nopenalty && zone&256)
		ban = 1;
	else if(!map[m].flag.nopenalty && zone&512)
		ban = 1;

	if(ban) {
		// テレポ禁止区域で使用不可のアイテムならメッセージ出す
		if(zone&32)
			clif_skill_teleportmessage(sd,0);
		if(zone&128)
			clif_msgstringtable(sd, 0x743);	// このマップでは召喚アイテムを使用できません。
		return 1;
	}

	return 0;
}

/*==========================================
 * 装備可能かどうか
 *------------------------------------------
 */
static int pc_isequip(struct map_session_data *sd,int n)
{
	struct item_data *item, *card_data;
	int i;
	int card_id;

	nullpo_retr(0, sd);

	item = sd->inventory_data[n];

	if(battle_config.gm_allequip > 0 && pc_isGM(sd) >= battle_config.gm_allequip)
		return 1;

	if(item == NULL)
		return 0;

	// キャスティング中
	//if(sd->state.casting) return 0;

	// スパノビの魂
	if(sd->sc.data[SC_SUPERNOVICE].timer != -1) {
		if(item->equip & LOC_RARM && sd->status.base_level >= 96)
		{
			if(sd->sc.data[SC_STRIPWEAPON].timer != -1)
				return 0;
			if(item->wlv >= 4 && itemdb_isweapon(item->nameid))
			{
				// Lv4の武器を許可
				switch(item->look) {
					case WT_DAGGER:
					case WT_1HSWORD:
					case WT_1HAXE:
					case WT_MACE:
					case WT_STAFF:
						return 1;
				}
			}
		}
		// 頭関係
		if(sd->status.base_level >= 90)
		{
			// 一応レベル制限チェック
			if(item->elv > 0 && sd->status.base_level < item->elv)
				return -1;
			// 頭でストリップなら失敗
			if(item->equip & LOC_HEAD2 && sd->sc.data[SC_STRIPHELM].timer != -1)
				return 0;
			// 頭なら成功
			// 頭上段
			if(item->equip & LOC_HEAD2)
				return 1;
			// 頭中段
			if(item->equip & LOC_HEAD3)
				return 1;
			// 頭下段
			if(item->equip & LOC_HEAD)
				return 1;
		}
	}
	if(battle_config.equip_sex) {
		if(item->sex != SEX_SERVER && sd->sex != item->sex)
			return 0;
	}
	if(item->elv > 0 && sd->status.base_level < item->elv)
		return -1;

	if((pc_get_job_bit(sd->s_class.job) & item->class_) == 0)
		return 0;

	if(item->upper) {
		if(((1<<sd->s_class.upper)&item->upper) == 0)
			return 0;
	}

	if(item->zone && pc_check_prohibition(sd,item->zone))
		return 0;

	// カードが使用禁止品でないかチェック
	for(i=0; i<item->slot; i++) {
		if((card_id = sd->status.inventory[n].card[i]) == 0)
			break;
		// 製造武器、製造アイテム除外
		if(i == 0 && (card_id == 254 || card_id == 255) )
			break;
		card_data = itemdb_search(card_id);
		if(card_data == NULL)
			return 0;
		if(card_data->zone && pc_check_prohibition(sd,card_data->zone))
			return 0;
	}

	if(unit_iscasting(&sd->bl) && battle_config.casting_penalty_type)
	{
		if(battle_config.casting_penalty_type == 1) {		// 武器と矢
			if(item->equip & LOC_RARM)
				return 0;
			if(item->equip & LOC_ARROW)
				return 0;
		} else if(battle_config.casting_penalty_type == 2) {	// 個別
			if(item->equip & LOC_RARM && battle_config.casting_penalty_weapon)
				return 0;
			if(item->equip & LOC_LARM && battle_config.casting_penalty_shield)
				return 0;
			if(item->equip & LOC_BODY && battle_config.casting_penalty_armor)
				return 0;
			if(item->equip & LOC_HEAD_TMB && battle_config.casting_penalty_helm)
				return 0;
			if(item->equip & LOC_ROBE && battle_config.casting_penalty_robe)
				return 0;
			if(item->equip & LOC_SHOES && battle_config.casting_penalty_shoes)
				return 0;
			if(item->equip & LOC_RLACCESSORY && battle_config.casting_penalty_acce)
				return 0;
			if(item->equip & LOC_ARROW && battle_config.casting_penalty_arrow)
				return 0;
			return 0;
		} else if(battle_config.casting_penalty_type == 3) {	// 全て
			return 0;
		}
	}

	if(sd->sc.data[SC_STRIPWEAPON].timer != -1 && item->equip & LOC_RARM)
		return 0;
	if(sd->sc.data[SC_STRIPSHIELD].timer != -1 && item->equip & LOC_LARM && !itemdb_isweapon(item->nameid))
		return 0;
	if(sd->sc.data[SC_STRIPARMOR].timer != -1 && item->equip & LOC_BODY)
		return 0;
	if(sd->sc.data[SC_STRIPHELM].timer != -1 && item->equip & LOC_HEAD2)
		return 0;
	if(sd->sc.data[SC__STRIPACCESSARY].timer != -1 && item->equip & LOC_RLACCESSORY)
		return 0;
	if(sd->sc.data[SC__WEAKNESS].timer != -1 && item->equip & LOC_RLARM)
		return 0;
	if(sd->sc.data[SC_PYROCLASTIC].timer != -1 && item->equip & LOC_RARM)
		return 0;

	return 1;
}

/*==========================================
 * session idに問題無し
 * char鯖から送られてきたステータスを設定
 *------------------------------------------
 */
int pc_authok(int id,struct mmo_charstatus *st,struct registry *reg)
{
	struct map_session_data *sd = map_id2sd(id);
	int i,lv;
	unsigned int tick = gettick();

	if(sd == NULL)
		return 1;
	if(sd->new_fd) {
		// ニ重login状態だったので、両方落す
		clif_authfail_fd(sd->fd,2);
		if(sd->new_fd > 0) {
			struct map_session_data *new_sd = NULL;
			if(session[sd->new_fd] && (new_sd = (struct map_session_data *)session[sd->new_fd]->session_data) && new_sd->bl.id == id) {
				clif_authfail_fd(sd->new_fd,2);
			}
		}
		return 1;
	}
	memcpy(&sd->status,st,sizeof(*st));
	memcpy(&sd->save_reg,reg,sizeof(*reg));

	if(sd->status.char_id != sd->char_id) {
		clif_authfail_fd(sd->fd,0);
		return 1;
	}

	session[sd->fd]->auth = 1;	// 認証終了を socket.c に伝える

	memset(&sd->state,0,sizeof(sd->state));

	// 基本的な初期化
	sd->state.connect_new = 1;
	sd->bl.prev = sd->bl.next = NULL;
	sd->weapontype1 = sd->weapontype2 = WT_FIST;
	sd->view_class = sd->status.class_;
	sd->s_class = pc_calc_base_job(sd->status.class_);

	sd->speed = DEFAULT_WALK_SPEED;
	sd->dir = 0;
	sd->head_dir = 0;
	sd->state.auth = 1;
	sd->skill_item.id = -1;
	sd->skill_item.lv = -1;
	sd->skill_item.flag = 0;
	sd->invincible_timer = -1;
	sd->view_size = 0;
	sd->booking_id = 0;
	sd->npc_idle_timer = -1;
	sd->npc_idle_tick = tick;
	sd->npc_dynamic_timer = -1;
	sd->npc_dynamic_tick = tick;
	sd->npc_dynamic_id = 0;
	memset(&sd->cloaked_npc,0,sizeof(sd->cloaked_npc));

	sd->trade.partner = 0;

	sd->deposit = 0;

	memset(&sd->regen,0,sizeof(sd->regen));

	// 気功・コイン・影狼、朧の球体初期化
	sd->spiritball.num = 0;
	sd->spiritball.old = 0;
	sd->coin.num = 0;
	sd->elementball.num = 0;
	sd->elementball.ele = ELE_NEUTRAL;

	for(i=0; i<MAX_SPIRITBALL; i++) {
		sd->spiritball.timer[i] = -1;
		sd->coin.timer[i]   = -1;
	}

	for(i=0; i<MAX_ELEMENTBALL; i++) {
		sd->elementball.timer[i] = -1;
	}

	for(i=0; i<MAX_ACTIVEITEM; i++) {
		sd->activeitem_timer[i] = -1;
		sd->activeitem_id2[i] = 0;
	}

	for(i=0; i<MAX_SKILL_DB; i++) {
		sd->skillstatictimer[i] = tick;
		sd->skillcooldown[i] = tick;
	}
	memset(&sd->itemcooldown,0,sizeof(sd->itemcooldown));

	sd->state.autoloot = (battle_config.item_auto_get)? 1: 0;

	for(i=0; i<5; i++) {
		sd->dev.val1[i] = 0;
		sd->dev.val2[i] = 0;
	}

	sd->item_delay_tick                = tick;
	sd->anti_hacker.emotion_delay_tick = tick;
	sd->anti_hacker.drop_delay_tick    = tick;
	sd->anti_hacker.drop_delay_count   = 0;

#if PACKETVER >= 20150513
	memset(&sd->hatEffect,0,sizeof(sd->hatEffect));
#endif

	unit_dataset(&sd->bl);

	// アカウント変数の送信要求
	intif_request_accountreg(sd);

	// クエストリストの送信要求
	intif_request_quest(sd->status.account_id,sd->status.char_id);

	// 実績リストの送信要求
	intif_request_achieve(sd->status.account_id,sd->status.char_id);

	// ペット初期化
	sd->petDB = NULL;
	sd->pd = NULL;
	memset(&sd->pet,0,sizeof(struct s_pet));

	// ホム初期化
	sd->hd = NULL;
	memset(&sd->hom,0,sizeof(struct mmo_homunstatus));

	// 傭兵初期化
	sd->mcd = NULL;

	// 精霊初期化
	sd->eld = NULL;

#ifdef DYNAMIC_SC_DATA
	// ダミー挿入
	sd->sc.data = dummy_sc_data;
#else
	// ステータス異常の初期化
	for(i=0; i<MAX_STATUSCHANGE; i++) {
		sd->sc.data[i].timer = -1;
		sd->sc.data[i].val1  = 0;
		sd->sc.data[i].val2  = 0;
		sd->sc.data[i].val3  = 0;
		sd->sc.data[i].val4  = 0;
	}
#endif

	sd->sc.count = 0;
	sd->sc.opt1  = OPT1_NORMAL;
	sd->sc.opt2  = OPT2_NORMAL;
	sd->sc.opt3  = OPT3_NORMAL;

	sd->status.option &= OPTION_MASK;
	sd->sc.option = sd->status.option;	// optionはscに移して使う

	// アイテムチェックは必ずステータス異常の初期化後に行う
	sd->state.inventory_dirty = 1;
	sd->state.cart_dirty = 1;
	sd->inventory_timer = NULL;
	pc_checkitem(sd);
	pc_setitemlimit(sd);

	// マナーポイントがプラスだった場合0に
	if(battle_config.nomanner_mode && sd->status.manner > 0)
		sd->status.manner = 0;

	// パーティー関係の初期化
	sd->party_invite = 0;
	sd->party_x      = -1;
	sd->party_y      = -1;
	sd->party_hp     = -1;

	// ギルド関係の初期化
	sd->guild_invite   = 0;
	sd->guild_alliance = 0;
	sd->guild_x        = -1;
	sd->guild_y        = -1;

	// 友達関係の初期化
	sd->friend_invite = 0;

	sd->adopt_invite = 0;

	// イベント関係の初期化
	memset(sd->eventqueue,0,sizeof(sd->eventqueue));
	for(i=0; i<MAX_EVENTTIMER; i++)
		sd->eventtimer[i] = -1;

	// 位置の設定
	if(pc_setpos(sd, sd->status.last_point.map, sd->status.last_point.x, sd->status.last_point.y, 0)) {
		// 失敗したので接続を切断する
		clif_authfail_fd(sd->fd,0);
		session[sd->fd]->auth = 0;
		return 1;
	}

	// ペット、ホム、傭兵、精霊データ要求
	if(sd->status.pet_id > 0)
		intif_request_petdata(sd->status.account_id,sd->status.char_id,sd->status.pet_id);
	if(sd->status.homun_id > 0)
		intif_request_homdata(sd->status.account_id,sd->status.char_id,sd->status.homun_id);
	if(sd->status.merc_id > 0)
		intif_request_mercdata(sd->status.account_id,sd->status.char_id,sd->status.merc_id);
	if(sd->status.elem_id > 0)
		intif_request_elemdata(sd->status.account_id,sd->status.char_id,sd->status.elem_id);

	// パーティ、ギルドデータの要求
	if( sd->status.party_id > 0 && party_search(sd->status.party_id) == NULL )
		party_request_info(sd->status.party_id);
	if( sd->status.guild_id > 0 && guild_search(sd->status.guild_id) == NULL )
		guild_request_info(sd->status.guild_id);

	// パートナーの名前要求
	if( sd->status.partner_id > 0 && map_charid2nick(sd->status.partner_id) == NULL )
		chrif_searchcharid(sd->status.partner_id);

	// pvpの設定
	sd->pvp_rank  = 0;
	sd->pvp_point = 0;
	sd->pvp_timer = -1;

	// 通知
	clif_authok(sd);
	map_addnickdb(sd);
	map_addchariddb(sd->status.char_id,sd->status.name,sd->status.account_id,clif_getip(),clif_getport());

	// テコンミッションターゲットのスクリプト変数からの読み出しとsdへのセット
	sd->tk_mission_target = pc_readglobalreg(sd,"PC_MISSION_TARGET");

	// ランキング用ポイントのスクリプト変数からの読み出しとsdへのセット
	ranking_readreg(sd);

	// ファーマシー連続成功カウンタ 起動時0に
	if(battle_config.save_am_pharmacy_success)
		sd->am_pharmacy_success = pc_readglobalreg(sd,"PC_PHARMACY_SUCCESS_COUNT");
	else
		sd->am_pharmacy_success = 0;

	// 太陽と月と星の感情
	for(i=0; i<3; i++) {
		if(!battle_config.save_feel_map)
			sd->status.feel_map[i][0] = '\0';
		if(sd->status.feel_map[i][0])
			sd->feel_index[i] = map_mapname2mapid(sd->status.feel_map[i]);
		else
			sd->feel_index[i] = -1;
	}

	// 太陽と月と星の憎しみ
	if(battle_config.save_hate_mob) {
		// なかった場合０になるので-1 保存も+1すること
		sd->hate_mob[0] = pc_readglobalreg(sd,"PC_HATE_MOB_SUN")  - 1;
		sd->hate_mob[1] = pc_readglobalreg(sd,"PC_HATE_MOB_MOON") - 1;
		sd->hate_mob[2] = pc_readglobalreg(sd,"PC_HATE_MOB_STAR") - 1;
	} else {
		sd->hate_mob[0] = -1;
		sd->hate_mob[1] = -1;
		sd->hate_mob[2] = -1;
	}

	// キラー
	if(battle_config.save_pckiller_type) {
		sd->kill.char_id   = pc_readglobalreg(sd,"PC_KILL_CHAR");
		sd->kill.merderer_char_id = pc_readglobalreg(sd,"PC_KILLED_CHAR");
	} else {
		memset(&sd->kill,0,sizeof(sd->kill));
	}

	// ショップポイント
	sd->shop_point = pc_readglobalreg(sd,"PC_SHOP_POINT");

	// ステータス初期計算など
	status_calc_pc(sd,1);

	// クローンスキルの初期化
	if((lv = pc_checkskill2(sd,RG_PLAGIARISM)) > 0) {
		sd->skill_clone.id = pc_readglobalreg(sd,"PC_CLONESKILL_ID");
		sd->skill_clone.lv = pc_readglobalreg(sd,"PC_CLONESKILL_LV");
		if(sd->skill_clone.id > 0 && sd->skill_clone.lv > lv)	// 念のためレベルチェック
			sd->skill_clone.lv = lv;
	} else {
		memset(&sd->skill_clone,0,sizeof(sd->skill_clone));
	}

	// リプロデュースの初期化
	if((lv = pc_checkskill2(sd,SC_REPRODUCE)) > 0) {
		sd->skill_reproduce.id = pc_readglobalreg(sd,"PC_REPRODUCE_ID");
		sd->skill_reproduce.lv = pc_readglobalreg(sd,"PC_REPRODUCE_LV");
		if(sd->skill_reproduce.id > 0 && sd->skill_reproduce.lv > lv)	// 念のためレベルチェック
			sd->skill_reproduce.lv = lv;
	} else {
		sd->skill_reproduce.id = 0;
		sd->skill_reproduce.lv = 0;
	}

	// MailData
	sd->mail_append.index  = -1;
	sd->mail_append.amount = 0;
	sd->mail_append.zeny   = 0;

	// ホットキーセット
	sd->hotkey_set = 0;
	memset(&sd->hotkey_rotate,0,sizeof(sd->hotkey_rotate));

	// 同盟チャットのon
	sd->state.alliance_message = 0;

	// Message of the Dayの送信
	msg_send_motd(sd);

	return 0;
}

/*==========================================
 * session idに問題ありなので後始末
 *------------------------------------------
 */
int pc_authfail(int id)
{
	struct map_session_data *sd = map_id2sd(id);

	if(sd == NULL)
		return 1;
	if(sd->new_fd) {
		// ニ重login状態だったので、新しい接続のみ落す
		clif_authfail_fd(sd->new_fd,0);

		sd->new_fd = 0;
		return 0;
	}
	clif_authfail_fd(sd->fd,0);
	return 0;
}

/*==========================================
 * スキルポイントを計算
 *------------------------------------------
 */
static int pc_calc_skillpoint(struct map_session_data* sd)
{
	int i,skill,skill_point = 0;

	nullpo_retr(0, sd);

	for(i=1; i<MAX_PCSKILL; i++) {
		if((skill = pc_checkskill2(sd,i)) > 0) {
			if(!(skill_get_inf2(i)&INF2_QUEST) || battle_config.quest_skill_learn) {
				if(!sd->status.skill[i].flag)
					skill_point += skill;
				else if(sd->status.skill[i].flag > 2) {
					skill_point += (sd->status.skill[i].flag - 2);
				}
			}
		}
	}

	return skill_point;
}

/*==========================================
 * 覚えられるスキルの計算
 *------------------------------------------
 */
int pc_calc_skilltree(struct map_session_data *sd)
{
	int i, c, s;
	int tk_ranker_bonus = 0;

	nullpo_retr(0, sd);

	if(sd->status.class_ == PC_CLASS_TK &&
	   pc_checkskill2(sd,TK_MISSION) > 0 &&
	   sd->status.base_level >= 90 &&
	   sd->status.skill_point == 0 &&
	   ranking_get_pc_rank(sd,RK_TAEKWON) > 0)
	{
		tk_ranker_bonus = 1;
	}

	c = sd->s_class.job;
	s = sd->s_class.upper;

	if(battle_config.skillup_limit) {
		int skill_point = pc_calc_skillpoint(sd);
		if(skill_point < 9) {
			c = 0;
		} else if(sd->status.skill_point >= sd->status.job_level && skill_point < 58 && c > PC_JOB_TF) {
			switch(c) {
				case PC_JOB_KN:
				case PC_JOB_CR:
				case PC_JOB_RK:
				case PC_JOB_LG:
					c = PC_JOB_SM;
					break;
				case PC_JOB_PR:
				case PC_JOB_MO:
				case PC_JOB_AB:
				case PC_JOB_SR:
					c = PC_JOB_AL;
					break;
				case PC_JOB_WZ:
				case PC_JOB_SA:
				case PC_JOB_WL:
				case PC_JOB_SO:
					c = PC_JOB_MG;
					break;
				case PC_JOB_BS:
				case PC_JOB_AM:
				case PC_JOB_NC:
				case PC_JOB_GN:
					c = PC_JOB_MC;
					break;
				case PC_JOB_HT:
				case PC_JOB_BA:
				case PC_JOB_DC:
				case PC_JOB_RA:
				case PC_JOB_MI:
				case PC_JOB_WA:
					c = PC_JOB_AC;
					break;
				case PC_JOB_AS:
				case PC_JOB_RG:
				case PC_JOB_GC:
				case PC_JOB_SC:
					c = PC_JOB_TF;
					break;
				case PC_JOB_SG:
				case PC_JOB_SL:
					c = PC_JOB_TK;
					break;
				case PC_JOB_KG:
				case PC_JOB_OB:
					c = PC_JOB_NJ;
					break;
				case PC_JOB_RL:
					c = PC_JOB_GS;
					break;
				default:
					break;
			}
		}
	}

	for(i=0; i<MAX_PCSKILL; i++) {
		sd->status.skill[i].id = 0;
		if(sd->status.skill[i].flag) {		// cardスキルなら
			sd->status.skill[i].lv   = (sd->status.skill[i].flag == 1)? 0: sd->status.skill[i].flag-2;	// 本当のlvに
			sd->status.skill[i].flag = 0;	// flagは0にしておく
		}
	}
	if(battle_config.gm_allskill > 0 && pc_isGM(sd) >= battle_config.gm_allskill) {
		// 全てのスキル
		for(i=1; i<158; i++)
			sd->status.skill[i].id = i;
		for(i=210; i<291; i++)
			sd->status.skill[i].id = i;
		if(battle_config.gm_allskill_addabra) { // アブラカタブラ専用スキル
			for(i=291; i<304; i++)
				sd->status.skill[i].id = i;
		}
		// 結婚スキルとトマホーク除外
		for(i=304; i<331; i++)
			sd->status.skill[i].id = i;
		// 養子スキル除外
		for(i=355; i<408; i++)
			sd->status.skill[i].id = i;
		for(i=411; i<473; i++)
			sd->status.skill[i].id = i;
		for(i=475; i<545; i++)
			sd->status.skill[i].id = i;
#ifdef CLASS_MB
		for(i=545; i<653; i++)
			sd->status.skill[i].id = i;
#endif
		for(i=1001; i<1020; i++)
			sd->status.skill[i].id = i;
	} else {
		// 通常の計算
		int id, flag;
		do {
			flag = 0;
			for(i=0; (id = skill_tree[s][c][i].id) > 0; i++) {
				if(sd->status.skill[id].id > 0)
					continue;
				if(!battle_config.skillfree && !tk_ranker_bonus) {
					int j, fail = 0;
					for(j=0; j<6 && skill_tree[s][c][i].need[j].id > 0; j++) {
						if(pc_checkskill2(sd,skill_tree[s][c][i].need[j].id) < skill_tree[s][c][i].need[j].lv) {
							fail = 1;
							break;
						}
					}
					if(fail)
						continue;
					if(sd->status.base_level < skill_tree[s][c][i].base_level ||
					   sd->status.job_level < skill_tree[s][c][i].job_level)
						continue;
				}
				sd->status.skill[id].id = id;
				flag = 1;
			}
		} while(flag);
	}
	// 子持ち
	if(sd->status.baby_id > 0)
	{
		sd->status.skill[WE_CALLBABY].id   = WE_CALLBABY;
		sd->status.skill[WE_CALLBABY].lv   = 1;
		sd->status.skill[WE_CALLBABY].flag = 1;
	}

	// 養子 親が居ないと覚えない
	if(sd->status.parent_id[0] > 0 || sd->status.parent_id[1] > 0)
	{
		sd->status.skill[WE_BABY].id   = WE_BABY;
		sd->status.skill[WE_BABY].lv   = 1;
		sd->status.skill[WE_BABY].flag = 1;
		sd->status.skill[WE_CALLPARENT].id   = WE_CALLPARENT;
		sd->status.skill[WE_CALLPARENT].lv   = 1;
		sd->status.skill[WE_CALLPARENT].flag = 1;
	}

	// 埋め込み
	// アルケミストの魂
	if(sd->sc.data[SC_ALCHEMIST].timer != -1)
	{
		if(pc_checkskill(sd,AM_PHARMACY) == 10)
		{
			if(pc_checkskill(sd,AM_TWILIGHT1) == 0)	// カードスキル扱い
			{
				sd->status.skill[AM_TWILIGHT1].id   = AM_TWILIGHT1;
				sd->status.skill[AM_TWILIGHT1].lv   = 1;
				sd->status.skill[AM_TWILIGHT1].flag = 1;
			}
			if(pc_checkskill(sd,AM_TWILIGHT2) == 0)	// カードスキル扱い
			{
				sd->status.skill[AM_TWILIGHT2].id   = AM_TWILIGHT2;
				sd->status.skill[AM_TWILIGHT2].lv   = 1;
				sd->status.skill[AM_TWILIGHT2].flag = 1;
			}
			if(pc_checkskill(sd,AM_TWILIGHT3) == 0)	// カードスキル扱い
			{
				sd->status.skill[AM_TWILIGHT3].id   = AM_TWILIGHT3;
				sd->status.skill[AM_TWILIGHT3].lv   = 1;
				sd->status.skill[AM_TWILIGHT3].flag = 1;
			}
#ifdef CLASS_MB
			if(pc_checkskill(sd,AM_TWILIGHT4) == 0)	// カードスキル扱い
			{
				sd->status.skill[AM_TWILIGHT4].id   = AM_TWILIGHT4;
				sd->status.skill[AM_TWILIGHT4].lv   = 1;
				sd->status.skill[AM_TWILIGHT4].flag = 1;
			}
#endif
		}

		if(pc_checkskill(sd,AM_BERSERKPITCHER) == 0)	// カードスキル扱い
		{
			sd->status.skill[AM_BERSERKPITCHER].id   = AM_BERSERKPITCHER;
			sd->status.skill[AM_BERSERKPITCHER].lv   = 1;
			sd->status.skill[AM_BERSERKPITCHER].flag = 1;
		}
	}
	// ナイトの魂
	if(sd->sc.data[SC_KNIGHT].timer != -1)
	{
		if(pc_checkskill(sd,KN_TWOHANDQUICKEN) == 10)
		{
			if(pc_checkskill(sd,KN_ONEHAND) == 0)	// カードスキル扱い
			{
				sd->status.skill[KN_ONEHAND].id   = KN_ONEHAND;
				sd->status.skill[KN_ONEHAND].lv   = 1;
				sd->status.skill[KN_ONEHAND].flag = 1;
			}
		}
	}
	// ブラックスミスの魂
	if(sd->sc.data[SC_BLACKSMITH].timer != -1)
	{
		if(pc_checkskill(sd,BS_ADRENALINE) == 5)
		{
			if(pc_checkskill(sd,BS_ADRENALINE2) == 0)	// カードスキル扱い
			{
				sd->status.skill[BS_ADRENALINE2].id   = BS_ADRENALINE2;
				sd->status.skill[BS_ADRENALINE2].lv   = 1;
				sd->status.skill[BS_ADRENALINE2].flag = 1;
			}
		}
	}
	// ハンターの魂
	if(sd->sc.data[SC_HUNTER].timer != -1)
	{
		if(pc_checkskill(sd,AC_DOUBLE) == 10)
		{
			if(pc_checkskill(sd,HT_POWER) == 0)	// カードスキル扱い
			{
				sd->status.skill[HT_POWER].id   = HT_POWER;
				sd->status.skill[HT_POWER].lv   = 1;
				sd->status.skill[HT_POWER].flag = 1;
			}
		}

	}

	// バードとダンサーの魂
	if(sd->sc.data[SC_BARDDANCER].timer != -1)
	{
		int lv;
		if((lv = pc_checkskill(sd,BA_WHISTLE)) > 0) {
			if(pc_checkskill(sd,DC_HUMMING) == 0)	// カードスキル扱い
			{
				sd->status.skill[DC_HUMMING].id   = DC_HUMMING;
				sd->status.skill[DC_HUMMING].lv   = lv;
				sd->status.skill[DC_HUMMING].flag = 1;
			}
		} else if((lv = pc_checkskill(sd,DC_HUMMING)) > 0) {
			if(pc_checkskill(sd,BA_WHISTLE) == 0)	// カードスキル扱い
			{
				sd->status.skill[BA_WHISTLE].id   = BA_WHISTLE;
				sd->status.skill[BA_WHISTLE].lv   = lv;
				sd->status.skill[BA_WHISTLE].flag = 1;
			}
		}

		if((lv = pc_checkskill(sd,BA_ASSASSINCROSS)) > 0) {
			if(pc_checkskill(sd,DC_DONTFORGETME) == 0)	// カードスキル扱い
			{
				sd->status.skill[DC_DONTFORGETME].id   =DC_DONTFORGETME;
				sd->status.skill[DC_DONTFORGETME].lv   = lv;
				sd->status.skill[DC_DONTFORGETME].flag = 1;
			}
		} else if((lv = pc_checkskill(sd,DC_DONTFORGETME)) > 0) {
			if(pc_checkskill(sd,BA_ASSASSINCROSS) == 0)	// カードスキル扱い
			{
				sd->status.skill[BA_ASSASSINCROSS].id   = BA_ASSASSINCROSS;
				sd->status.skill[BA_ASSASSINCROSS].lv   = lv;
				sd->status.skill[BA_ASSASSINCROSS].flag = 1;
			}
		}

		if((lv = pc_checkskill(sd,BA_POEMBRAGI)) > 0) {
			if(pc_checkskill(sd,DC_FORTUNEKISS) == 0)	// カードスキル扱い
			{
				sd->status.skill[DC_FORTUNEKISS].id   = DC_FORTUNEKISS;
				sd->status.skill[DC_FORTUNEKISS].lv   = lv;
				sd->status.skill[DC_FORTUNEKISS].flag = 1;
			}

		} else if((lv = pc_checkskill(sd,DC_FORTUNEKISS)) > 0) {
			if(pc_checkskill(sd,BA_POEMBRAGI) == 0)		// カードスキル扱い
			{
				sd->status.skill[BA_POEMBRAGI].id   = BA_POEMBRAGI;
				sd->status.skill[BA_POEMBRAGI].lv   = lv;
				sd->status.skill[BA_POEMBRAGI].flag = 1;
			}

		}

		if((lv = pc_checkskill(sd,BA_APPLEIDUN)) > 0) {
			if(pc_checkskill(sd,DC_SERVICEFORYOU) == 0)	// カードスキル扱い
			{
				sd->status.skill[DC_SERVICEFORYOU].id   = DC_SERVICEFORYOU;
				sd->status.skill[DC_SERVICEFORYOU].lv   = lv;
				sd->status.skill[DC_SERVICEFORYOU].flag = 1;
			}
		} else if((lv = pc_checkskill(sd,DC_SERVICEFORYOU)) > 0) {
			if(pc_checkskill(sd,BA_APPLEIDUN) == 0)		// カードスキル扱い
			{
				sd->status.skill[BA_APPLEIDUN].id   = BA_APPLEIDUN;
				sd->status.skill[BA_APPLEIDUN].lv   = lv;
				sd->status.skill[BA_APPLEIDUN].flag = 1;
			}
		}
	}

	// テコンランカーボーナス
	if(sd->status.class_ == PC_CLASS_TK && sd->status.base_level >= 90 && ranking_get_pc_rank(sd,RK_TAEKWON) > 0)
	{
		for(i = 411; i <= 426; i++) {
			pc_skill(sd,i,skill_get_max(i),1);
		}

		// テコンミッションも追加する
		pc_skill(sd,TK_MISSION,skill_get_max(TK_MISSION),1);
	}

	return 0;
}

/*==========================================
 * 重量が50%を越えているか
 *------------------------------------------
 */
int pc_is50overweight(struct map_session_data *sd)
{
	int rate = 50;

	nullpo_retr(0, sd);

	// 自然回復しなくなる重量設定に合わせる
	if(rate != battle_config.natural_heal_weight_rate)
		rate = battle_config.natural_heal_weight_rate;

	return (sd->weight * 100 / sd->max_weight >= rate);
}

/*==========================================
 * 重量が90%を越えているか
 *------------------------------------------
 */
int pc_is90overweight(struct map_session_data *sd)
{
	int rate = 90;

	nullpo_retr(0, sd);

	// 自然回復しなくなる重量設定が90%以上ならそれに合わせる
	if(rate < battle_config.natural_heal_weight_rate)
		rate = battle_config.natural_heal_weight_rate;

	return (sd->weight * 100 / sd->max_weight >= rate);
}

/*==========================================
 * 重量アイコンの確認
 *------------------------------------------
 */
int pc_checkweighticon(struct map_session_data *sd)
{
	unsigned int flag;

	nullpo_retr(0, sd);

	flag = (pc_is90overweight(sd)) ? 2 : (pc_is50overweight(sd)) ? 1 : 0;

	if(battle_config.natural_heal_weight_rate_icon && flag != 2) {
		flag = (sd->weight * 100 / sd->max_weight >= battle_config.natural_heal_weight_rate) ? 1 : 0;
	}

	// 変化しないので終了
	if(flag == sd->state.icon_weight)
		return 0;

	if(sd->state.icon_weight == 1)
		clif_status_load_id(sd,SI_WEIGHT50,0);
	else if(sd->state.icon_weight == 2)
		clif_status_load_id(sd,SI_WEIGHT90,0);

	if(flag == 1)
		clif_status_load_id(sd,SI_WEIGHT50,1);
	else if(flag == 2)
		clif_status_load_id(sd,SI_WEIGHT90,1);

	sd->state.icon_weight = flag;

	return 0;
}

/*==========================================
 * スクリプトによるスキル取得
 *------------------------------------------
 */
int pc_skill(struct map_session_data *sd,int id,int level,int flag)
{
	nullpo_retr(0, sd);

	if(level > MAX_SKILL_LEVEL) {
		if(battle_config.error_log)
			printf("support card skill only!\n");
		return 0;
	}
	if(!flag && (sd->status.skill[id].id == id || level == 0)) {	// クエスト取得ならここで条件を確認して送信する
		sd->status.skill[id].lv = level;
		status_calc_pc(sd,0);
		clif_skillinfoblock(sd);
	}
	else if(sd->status.skill[id].lv < level) {	// 覚えられるがlvが小さいなら
		if(sd->status.skill[id].id == id) {
			sd->status.skill[id].flag = sd->status.skill[id].lv+2;	// lvを記憶
		} else {
			sd->status.skill[id].id   = id;
			sd->status.skill[id].flag = 1;	// cardスキルとする
		}
		sd->status.skill[id].lv = level;
	}

	return 0;
}

/*==========================================
 * カード挿入
 *------------------------------------------
 */
void pc_insert_card(struct map_session_data *sd, int idx_card, int idx_equip)
{
	nullpo_retv(sd);

	// idx_cardは既にチェック済み
	if(idx_equip >= 0 && idx_equip < MAX_INVENTORY && sd->inventory_data[idx_card]) {
		int i;
		int nameid = sd->status.inventory[idx_equip].nameid;
		int cardid = sd->status.inventory[idx_card].nameid;
		int ep     = sd->inventory_data[idx_card]->equip;

		if( nameid <= 0 ||
		    cardid <= 0 ||
		    sd->inventory_data[idx_equip] == NULL ||
		    (!itemdb_isarmor(sd->inventory_data[idx_equip]->nameid) && !itemdb_isweapon(sd->inventory_data[idx_equip]->nameid)) ||	// 装備じゃない
		    sd->status.inventory[idx_equip].identify == 0 ||						// 未鑑定
		    itemdb_isspecial(sd->status.inventory[idx_equip].card[0]) ||				// 製造武器・名前入り・ペット
		    (sd->inventory_data[idx_equip]->equip & ep) == 0 ||						// 装備個所違い
		    (itemdb_isweapon(sd->inventory_data[idx_equip]->nameid) && ep == LOC_LARM) ||					// 両手武器と盾カード
		    (sd->inventory_data[idx_card]->type != ITEMTYPE_CARD) ||						// Prevent Hack [Ancyker]
		    sd->status.inventory[idx_equip].equip ||
		    itemdb_cardtype(sd->inventory_data[idx_card]->nameid) == 2 )	// hidden
		{
			clif_insert_card(sd, idx_equip, idx_card, 1);	// flag: 1=fail, 0:success
			return;
		}
		for(i=0; i<sd->inventory_data[idx_equip]->slot; i++) {
			if(sd->status.inventory[idx_equip].card[i] == 0) {
				// 複数の同一カードが許可されているかチェック
				if(!itemdb_cardtype(sd->inventory_data[idx_card]->nameid)) {
					int j;
					for(j=0; j<i; j++) {
						if(sd->status.inventory[idx_equip].card[j] == cardid) {
							clif_insert_card(sd, idx_equip, idx_card, 1);	// flag: 1=fail, 0:success
							return;
						}
					}
				}
				// 空きスロットがあったので差し込む
				sd->status.inventory[idx_equip].card[i] = cardid;

				// カードは減らす
				clif_insert_card(sd, idx_equip, idx_card, 0);	// flag: 1=fail, 0:success
				pc_delitem(sd,idx_card,1,1,0);
				return;
			}
		}
	} else {
		clif_insert_card(sd, idx_equip, idx_card, 1);	// flag: 1=fail, 0:success
	}

	return;
}

/*==========================================
 * スキルによる買い値修正
 * sdがNULLのときは最安値を返す
 *------------------------------------------
 */
int pc_modifybuyvalue(struct map_session_data *sd,int orig_value)
{
	int skill, val = orig_value;
	int rate1 = 0, rate2 = 0;

	// ディスカウント
	skill = (sd)? pc_checkskill(sd, MC_DISCOUNT): skill_get_max(MC_DISCOUNT);
	if(skill > 0)
		rate1 = 5 + skill * 2 - ((skill >= 10)? 1: 0);

	// コンパルションディスカウント
	skill = (sd)? pc_checkskill(sd, RG_COMPULSION): skill_get_max(RG_COMPULSION);
	if(skill > 0)
		rate2 = 5 + skill * 4;

	if(rate1 < rate2)
		rate1 = rate2;
	if(rate1)
		val = (int)((atn_bignumber)orig_value * (100 - rate1) / 100);

	if(val < 0) val = 0;
	if(orig_value > 0 && val < 1) val = 1;

	return val;
}

/*==========================================
 * スキルによる売り値修正
 * sdがNULLのときは最高値を返す
 *------------------------------------------
 */
int pc_modifysellvalue(struct map_session_data *sd,int orig_value)
{
	int skill, val = orig_value;
	int rate = 0;

	// オーバーチャージ
	skill = (sd)? pc_checkskill(sd, MC_OVERCHARGE): skill_get_max(MC_OVERCHARGE);
	if(skill > 0)
		rate = 5 + skill * 2 - ((skill >= 10)? 1: 0);

	// マーダラーボーナス
	if(battle_config.pk_murderer_point > 0) {
		if(sd == NULL || ranking_get_point(sd,RK_PK) >= battle_config.pk_murderer_point)
			rate += 10;
	}
	if(rate)
		val = (int)((atn_bignumber)orig_value * (100 + rate) / 100);

	if(val < 0) val = 0;
	if(orig_value > 0 && val < 1) val = 1;

	return val;
}

/*==========================================
 * アイテムを買った時に、新しいアイテム欄を使うか、
 * 3万個制限にかかるか確認
 *------------------------------------------
 */
int pc_checkadditem(struct map_session_data *sd,int nameid,int amount)
{
	int i;

	nullpo_retr(ADDITEM_OVERAMOUNT, sd);

	if(itemdb_isequip(nameid))
		return ADDITEM_NEW;

	for(i=0; i<MAX_INVENTORY; i++) {
		if(sd->status.inventory[i].nameid == nameid) {
			if(sd->status.inventory[i].amount+amount > MAX_AMOUNT)
				return ADDITEM_OVERAMOUNT;
			return ADDITEM_EXIST;
		}
	}

	if(amount > MAX_AMOUNT)
		return ADDITEM_OVERAMOUNT;
	return ADDITEM_NEW;
}

/*==========================================
 * 空きアイテム欄の個数
 *------------------------------------------
 */
int pc_inventoryblank(struct map_session_data *sd)
{
	int i,b = 0;

	nullpo_retr(0, sd);

	for(i=0; i<MAX_INVENTORY; i++) {
		if(sd->status.inventory[i].nameid == 0)
			b++;
	}

	return b;
}

/*==========================================
 * お金を払う
 *------------------------------------------
 */
int pc_payzeny(struct map_session_data *sd,int zeny)
{
	nullpo_retr(0, sd);

	if(sd->status.zeny < zeny)
		return 1;
	sd->status.zeny -= zeny;
	clif_updatestatus(sd,SP_ZENY);

	return 0;
}

/*==========================================
 * お金を得る
 *------------------------------------------
 */
int pc_getzeny(struct map_session_data *sd,int zeny)
{
	nullpo_retr(0, sd);

	if(sd->status.zeny > MAX_ZENY - zeny) {
		zeny = 0;
		sd->status.zeny = MAX_ZENY;
	}
	sd->status.zeny += zeny;
	clif_updatestatus(sd,SP_ZENY);

	achieve_update_content(sd, ACH_GET_ZENY, SP_ZENY, sd->status.zeny);

	return 0;
}

/*==========================================
 * アイテムを探して、インデックスを返す
 *------------------------------------------
 */
int pc_search_inventory(struct map_session_data *sd,int item_id)
{
	int i;

	nullpo_retr(-1, sd);

	for(i=0; i<MAX_INVENTORY; i++) {
		if(sd->status.inventory[i].nameid == item_id &&
		   (sd->status.inventory[i].amount > 0 || item_id == 0))
			return i;
	}

	return -1;
}

/*==========================================
 * アイテム使用期限タイマー
 *------------------------------------------
 */
static int pc_itemlimit_timer(int tid, unsigned int tick, int id, void *data)
{
	struct map_session_data *sd = map_id2sd(id);
	struct linkdb_node *node;
	unsigned int now;

	if(sd == NULL)
		return 0;

	now  = (unsigned int)time(NULL);
	node = sd->inventory_timer;

	while(node) {
		if(tid == PTR2INT(node->data)) {
			tid = pc_checkitemlimit(sd, PTR2INT(node->key), tick, now, 0);
			if(tid >= 0) {
				node->data = INT2PTR(tid);
			}
			return 0;
		}
		node = node->next;
	}

	printf("pc_itemlimit_timer: %d not found!!\n", tid);
	return 0;
}

/*==========================================
 * アイテム使用期限のチェック
 *------------------------------------------
 */
static int pc_checkitemlimit(struct map_session_data *sd, int idx, unsigned int tick, unsigned int now, int first)
{
	nullpo_retr(0, sd);

	if(idx < 0 || idx >= MAX_INVENTORY)
		return -1;

	if(sd->status.inventory[idx].limit > now) {
		// まだ時間になってないのでタイマーを継続する
		unsigned int diff = sd->status.inventory[idx].limit - now;
		if(diff > 3600)
			diff = 3600;
		return add_timer(tick + diff * 1000, pc_itemlimit_timer, sd->bl.id, NULL);
	}

	// 時間切れにより削除
	if(sd->status.inventory[idx].card[0] == (int)0xff00) {
		intif_delete_petdata(*((int *)(&sd->status.inventory[idx].card[1])));
	}
	if(first) {
		sd->status.inventory[idx].limit = 0;
		pc_delitem(sd, idx, sd->status.inventory[idx].amount, 3, 0);
	} else {
		char output[256];
		struct item_data *data = sd->inventory_data[idx];

#if PACKETVER >= 20070711
		if(itemdb_isequip2(data)) {
			// 強化装備アイテムの削除
			pc_delitem(sd, idx, sd->status.inventory[idx].amount, 1, 0);
			clif_delitem_timeout(sd, idx, ((data->view_id > 0)? data->view_id: data->nameid));
			return -1;
		}
#endif
		// 通常アイテムの使用期限切れ削除
		pc_delitem(sd, idx, sd->status.inventory[idx].amount, 0, 0);
		snprintf(output, sizeof(output), msg_txt(187), ((data->view_id > 0)? itemdb_jname(data->view_id): data->jname));
		clif_disp_onlyself(sd->fd, output);

		// 搭乗用の手綱が削除される場合はSC_ALL_RIDINGを解除する
		if(data->nameid == 12622)
			status_change_end(&sd->bl,SC_ALL_RIDING,-1);

		// フォントアイテムの削除時はフォントを初期化する
		if((data->nameid >= 12287 && data->nameid <= 12289) ||
		   (data->nameid >= 12304 && data->nameid <= 12309))
			sd->status.font = 0;
	}

	return -1;
}

/*==========================================
 * アイテム使用期限のセット
 *------------------------------------------
 */
static int pc_setitemlimit(struct map_session_data *sd)
{
	int i,j;
	unsigned int now  = (unsigned int)time(NULL);
	unsigned int tick = gettick();

	nullpo_retr(0, sd);

	for(i = 0,j = 0; i < MAX_INVENTORY && j < sd->inventory_num; i++) {
		if(sd->status.inventory[i].nameid <= 0)
			continue;
		j++;
		if(sd->status.inventory[i].limit > 0) {
			int tid = pc_checkitemlimit(sd, i, tick, now, 1);
			if(tid >= 0)
				linkdb_insert(&sd->inventory_timer, INT2PTR(i), INT2PTR(tid));
		}
	}

	return 0;
}

/*==========================================
 * アイテム使用期限の全消去
 *------------------------------------------
 */
int pc_clearitemlimit(struct map_session_data *sd)
{
	struct linkdb_node *node;

	nullpo_retr(0, sd);

	node = sd->inventory_timer;
	while(node) {
		delete_timer(PTR2INT(node->data), pc_itemlimit_timer);
		node = node->next;
	}
	linkdb_final(&sd->inventory_timer);

	return 0;
}

/*==========================================
 * アイテム追加。個数のみitem構造体の数字を無視
 *------------------------------------------
 */
int pc_additem(struct map_session_data *sd,struct item *item_data,int amount)
{
	struct item_data *data;
	int i,w;

	nullpo_retr(1, sd);
	nullpo_retr(1, item_data);

	if(item_data->nameid <= 0 || amount <= 0)
		return 1;

	data = itemdb_search(item_data->nameid);
	if((w = data->weight * amount) + sd->weight > sd->max_weight)
		return 2;

	if(!itemdb_isequip2(data)) {
		// 装備品ではないので、既所有品なら個数のみ変化させる
		for(i=0; i<MAX_INVENTORY; i++) {
			if(sd->status.inventory[i].nameid  == item_data->nameid  &&
			   sd->status.inventory[i].card[0] == item_data->card[0] &&
			   sd->status.inventory[i].card[1] == item_data->card[1] &&
			   sd->status.inventory[i].card[2] == item_data->card[2] &&
			   sd->status.inventory[i].card[3] == item_data->card[3] &&
			   sd->status.inventory[i].limit   == item_data->limit)
			{
				if(sd->status.inventory[i].amount + amount > MAX_AMOUNT)
					return 5;
				sd->status.inventory[i].amount += amount;
				sd->weight += w;
				clif_additem(sd,i,amount,0);
				clif_updatestatus(sd,SP_WEIGHT);
				return 0;
			}
		}
	}

	// 装備品か未所有品だったので空き欄へ追加
	i = pc_search_inventory(sd,0);
	if(i < 0)
		return 4;

	memcpy(&sd->status.inventory[i],item_data,sizeof(sd->status.inventory[0]));
	if(itemdb_isequip2(data)) {
		sd->status.inventory[i].amount = 1;
		amount = 1;
	} else {
		sd->status.inventory[i].amount = amount;
	}
	sd->state.inventory_dirty  = 1;
	sd->status.inventory[i].id = ++sd->inventory_sortkey;
	sd->inventory_data[i]      = data;
	sd->weight += w;
	sd->inventory_num++;
	clif_additem(sd,i,amount,0);
	clif_updatestatus(sd,SP_WEIGHT);

	if(sd->status.inventory[i].limit > 0) {
		int tid = pc_checkitemlimit(sd, i, gettick(), (unsigned int)time(NULL), 0);
		if(tid >= 0)
			linkdb_insert(&sd->inventory_timer, INT2PTR(i), INT2PTR(tid));
	}

	return 0;
}

/*==========================================
 * 装備アイテムを消去
 *------------------------------------------
 */
int pc_lossequipitem(struct map_session_data *sd,int pos,int type)
{
	int n;

	nullpo_retr(1, sd);

	n = sd->equip_index[pos];
	pc_unequipitem(sd,n,type);
	pc_delitem(sd,n,1,type,0);
	return 0;
}

/*==========================================
 * アイテムを減らす
 *------------------------------------------
 */
void pc_delitem(struct map_session_data *sd, int n, int amount, int type, short dtype)
{
	nullpo_retv(sd);

	if(sd->status.inventory[n].nameid == 0 || amount <= 0 || sd->status.inventory[n].amount < amount || sd->inventory_data[n] == NULL)
		return;

	sd->status.inventory[n].amount -= amount;
	sd->weight -= sd->inventory_data[n]->weight*amount;
	if(sd->status.inventory[n].amount <= 0) {
		if(sd->status.inventory[n].equip) {
			pc_unequipitem(sd,n,0);
		}
		if(sd->status.inventory[n].limit > 0) {
			int tid = PTR2INT(linkdb_erase(&sd->inventory_timer, INT2PTR(n)));
			if(tid >= 0)
				delete_timer(tid, pc_itemlimit_timer);
		}
		memset(&sd->status.inventory[n],0,sizeof(sd->status.inventory[0]));
		sd->inventory_num--;
		sd->inventory_data[n] = NULL;
	}
	if(!(type&1))
		clif_delitem(sd,dtype,n,amount);
	if(!(type&2))
		clif_updatestatus(sd,SP_WEIGHT);

	return;
}

/*==========================================
 * アイテムを落す
 *------------------------------------------
 */
int pc_dropitem(struct map_session_data *sd, int n, int amount)
{
	nullpo_retr(0, sd);

	if(n < 0 || n >= MAX_INVENTORY)
		return 0;
	if(amount <= 0)
		return 0;

	if(sd->status.inventory[n].nameid <= 0 || sd->status.inventory[n].amount < amount)
		return 0;

	if(itemdb_isdropable(sd->status.inventory[n].nameid) == 0)
		return 0;
	if(pc_candrop(sd,sd->status.inventory[n].nameid))
		return 0;

	if(map_addflooritem(&sd->status.inventory[n],amount,sd->bl.m,sd->bl.x,sd->bl.y,0,0,0,0)) {
		pc_delitem(sd,n,amount,0,0);
		return 1;
	}
	return 0;
}

/*==========================================
 * アイテムを拾う処理本体
 *------------------------------------------
 */
void pc_takeitem_sub(struct party *p, struct map_session_data *sd, struct flooritem_data *fitem)
{
	int flag;
	unsigned int tick = gettick();
	struct map_session_data *first_sd = NULL, *second_sd = NULL, *third_sd = NULL;

	nullpo_retv(sd);
	nullpo_retv(fitem);

	if(fitem->first_get_id > 0 && fitem->first_get_id != sd->bl.id) {
		first_sd = map_id2sd(fitem->first_get_id);
		if(tick < fitem->first_get_tick) {
			if( p && p->item&1 &&
			    first_sd && first_sd->status.party_id > 0 && first_sd->status.party_id == sd->status.party_id ) {
				;	// PT共有設定で同一PTならOK
			} else {
				clif_additem(sd,0,0,6);
				return;
			}
		}
		else if(fitem->second_get_id > 0 && fitem->second_get_id != sd->bl.id) {
			second_sd = map_id2sd(fitem->second_get_id);
			if(tick < fitem->second_get_tick) {
				if( p && p->item&1 &&
				    ((first_sd && first_sd->status.party_id > 0 && first_sd->status.party_id == sd->status.party_id) ||
				    (second_sd && second_sd->status.party_id > 0 && second_sd->status.party_id == sd->status.party_id)) ) {
					;	// PT共有設定で同一PTならOK
				} else {
					clif_additem(sd,0,0,6);
					return;
				}
			}
			else if(fitem->third_get_id > 0 && fitem->third_get_id != sd->bl.id) {
				third_sd = map_id2sd(fitem->third_get_id);
				if(tick < fitem->third_get_tick) {
					if( p && p->item&1 &&
					    ((first_sd && first_sd->status.party_id > 0 && first_sd->status.party_id == sd->status.party_id) ||
					    (second_sd && second_sd->status.party_id > 0 && second_sd->status.party_id == sd->status.party_id) ||
					    (third_sd && third_sd->status.party_id > 0 && third_sd->status.party_id == sd->status.party_id)) ) {
						;	// PT共有設定で同一PTならOK
					} else {
						clif_additem(sd,0,0,6);
						return;
					}
				}
			}
		}
	}
	if((flag = party_loot_share(p,sd,&fitem->item_data,fitem->first_get_id))) {
		// 重量overで取得失敗
		clif_additem(sd,0,0,flag);
	} else {
		// 取得成功
		unit_stopattack(&sd->bl);
		clif_takeitem(&sd->bl,fitem->bl.id);
		map_clearflooritem(fitem->bl.id);
	}
	return;
}

/*==========================================
 * アイテムを拾う
 *------------------------------------------
 */
void pc_takeitem(struct map_session_data *sd, struct flooritem_data *fitem)
{
	struct party *p = NULL;

	nullpo_retv(sd);
	nullpo_retv(fitem);

	if(path_distance(fitem->bl.x,fitem->bl.y,sd->bl.x,sd->bl.y) > 2)
		return;	// 距離が遠い

	if(sd->status.party_id > 0)
		p = party_search(sd->status.party_id);

	pc_takeitem_sub(p, sd, fitem);
	return;
}

/*==========================================
 * アイテム使用可能かどうか
 *------------------------------------------
 */
static int pc_isUseitem(struct map_session_data *sd,int n)
{
	struct item_data *item;

	nullpo_retr(0, sd);

	item = sd->inventory_data[n];

	if(item == NULL)
		return 0;
	if(item->type != ITEMTYPE_HEAL && item->type != ITEMTYPE_SPECIAL && item->type != ITEMTYPE_CASH_POINT_ITEM)
		return 0;

	if(item->sex != SEX_SERVER && sd->sex != item->sex)
		return 0;
	if(item->elv > 0 && sd->status.base_level < item->elv)
		return -1;

	if((pc_get_job_bit(sd->s_class.job) & item->class_) == 0)
		return 0;

	if(item->upper) {
		if(((1<<sd->s_class.upper)&item->upper) == 0)
			return 0;
	}

	if(item->zone && pc_check_prohibition(sd,item->zone))
		return 0;

	return 1;
}

/*==========================================
 * アイテムを使う
 *------------------------------------------
 */
void pc_useitem(struct map_session_data *sd, int n)
{
	int nameid,amount;
	struct item_data *item;
	int flag;

	nullpo_retv(sd);

	if(n < 0 || n >= MAX_INVENTORY)
		return;

	item   = sd->inventory_data[n];
	nameid = sd->status.inventory[n].nameid;
	amount = sd->status.inventory[n].amount;
	flag   = pc_isUseitem(sd,n);

	if(nameid <= 0 || amount <= 0 || flag <= 0) {
		clif_useitemack(sd,n,0,0);
		if(flag < 0)
			clif_msgstringtable(sd, 0x6ee);	// アイテムを使用できるレベルに達していません。
		return;
	}

	if(item->cooldown > 0) {
		unsigned int tick = gettick();
		int i,j = -1;
		for(i=0;i<MAX_ITEMCOOLDOWN;i++) {
			// 同一IDのidxか未使用idxを探す
			if(sd->itemcooldown[i].nameid == nameid || sd->itemcooldown[i].nameid == 0)
				break;
			// 使用済みのうちクールタイム切れがあれば控える
			if(DIFF_TICK(sd->itemcooldown[i].time, tick) <= 0) {
				j = i;
			}
		}
		// アイテムクールタイムリストがいっぱい
		if(i == MAX_ITEMCOOLDOWN) {
			// かつクールタイム切れがない
			if(j < 0) {
				clif_useitemack(sd,n,0,0);
				return;
			}
			// クールタイム切れidxに差し替える
			i = j;
		}
		// 同一IDならクールタイムチェック
		if(sd->itemcooldown[i].nameid == nameid) {
			int delay = DIFF_TICK(sd->itemcooldown[i].time, tick) / 1000;
			if(delay > 0) {
				clif_useitemack(sd,n,0,0);
				clif_msgstringtable3(sd, 0x746, delay + 1);	// %d 秒後に使用できます。
				return;
			}
		}
		else {	// 未使用idxかクールタイムidxならnameidを入れ替える
			sd->itemcooldown[i].nameid = nameid;
		}
		sd->itemcooldown[i].time = tick + item->cooldown;
	}

	sd->use_itemid = nameid;
	if(sd->status.inventory[n].card[0] == 0x00fe)
		sd->use_nameditem = *((int *)(&sd->status.inventory[n].card[2]));
	else
		sd->use_nameditem = 0;

	if(battle_config.item_res)
	{
		// nonconsumeフラグが真ならアイテムを消費しない
		if(itemdb_isnonconsume(nameid))
		{
			clif_useitemack(sd,n,amount,1);
		}
		// 楽しい状態なら確率的にアーススパイクスクロールの消費無し
		else if(sd->sc.data[SC_HAPPY].timer != -1 && (nameid == 686 || nameid == 687) &&
		   sd->status.sp >= 10 && atn_rand()%100 >= 11 - sd->sc.data[SC_HAPPY].val1)
		{
			sd->status.sp -= 10;
			clif_updatestatus(sd,SP_SP);
			clif_useitemack(sd,n,amount,1);
		}
		else
		{
			clif_useitemack(sd,n,amount-1,1);
			pc_delitem(sd,n,1,1,0);
		}
	}
	else
	{
		clif_useitemack(sd,n,amount,1);
	}

	// 実績使用ターゲット
	if(achieve_search_itemid(nameid))
		achieve_update_content(sd, ACH_USE_ITEM, nameid, 1);

	if(item) {
		if(item->use_script)
			run_script(item->use_script,0,sd->bl.id,0);
		if(item->delay)
			sd->item_delay_tick = gettick() + item->delay;
	}

	return;
}

/*==========================================
 * カートアイテム追加。個数のみitem構造体の数字を無視
 *------------------------------------------
 */
int pc_cart_additem(struct map_session_data *sd,struct item *item_data,int amount)
{
	struct item_data *data;
	int i,w;

	nullpo_retr(1, sd);
	nullpo_retr(1, item_data);

	if(item_data->nameid <= 0 || amount <= 0)
		return 1;
	if((data = itemdb_search(item_data->nameid)) == NULL)
		return 1;

	if((w = data->weight*amount) + sd->cart_weight > sd->cart_max_weight)
		return 1;

	i = MAX_CART;
	if(!itemdb_isequip2(data)) {
		// 装備品ではないので、既所有品なら個数のみ変化させる
		for(i=0; i<MAX_CART; i++) {
			if(sd->status.cart[i].nameid  == item_data->nameid  &&
			   sd->status.cart[i].card[0] == item_data->card[0] &&
			   sd->status.cart[i].card[1] == item_data->card[1] &&
			   sd->status.cart[i].card[2] == item_data->card[2] &&
			   sd->status.cart[i].card[3] == item_data->card[3] &&
			   sd->status.cart[i].limit   == item_data->limit)
			{
				if(sd->status.cart[i].amount+amount > MAX_AMOUNT)
					return 1;
				sd->status.cart[i].amount += amount;
				clif_cart_additem(sd, i, amount);
				break;
			}
		}
	}
	if(i >= MAX_CART) {
		// 装備品か未所有品だったので空き欄へ追加
		for(i=0; i<MAX_CART; i++) {
			if(sd->status.cart[i].nameid == 0) {
				memcpy(&sd->status.cart[i],item_data,sizeof(sd->status.cart[0]));
				if(itemdb_isequip2(data)) {
					sd->status.cart[i].amount = 1;
					amount = 1;
				} else {
					sd->status.cart[i].amount = amount;
				}
				sd->cart_num++;
				sd->state.cart_dirty = 1;
				sd->status.cart[i].id = ++sd->cart_sortkey;
				clif_cart_additem(sd, i, amount);
				break;
			}
		}
		if(i >= MAX_CART)
			return 1;
	}
	sd->cart_weight += w;
	clif_updatestatus(sd,SP_CARTINFO);

	return 0;
}

/*==========================================
 * カートアイテムを減らす
 *------------------------------------------
 */
int pc_cart_delitem(struct map_session_data *sd,int n,int amount,int type)
{
	nullpo_retr(1, sd);

	if(sd->status.cart[n].nameid == 0 || sd->status.cart[n].amount < amount)
		return 1;

	sd->status.cart[n].amount -= amount;
	sd->cart_weight -= itemdb_weight(sd->status.cart[n].nameid)*amount;
	if(sd->status.cart[n].amount <= 0) {
		memset(&sd->status.cart[n],0,sizeof(sd->status.cart[0]));
		sd->cart_num--;
		sd->status.cart[n].id = 0;
	}
	if(!type) {
		clif_cart_delitem(sd,n,amount);
		clif_updatestatus(sd,SP_CARTINFO);
	}

	return 0;
}

/*==========================================
 * カートへアイテム移動
 *------------------------------------------
 */
void pc_putitemtocart(struct map_session_data *sd, int idx, int amount)
{
	struct item *item_data;

	nullpo_retv(sd);

	if(idx < 0 || idx >= MAX_INVENTORY)
		return;

	item_data = &sd->status.inventory[idx];
	if(item_data->nameid == 0 || item_data->amount < amount)
		return;

	if(itemdb_isdropable(sd->status.inventory[idx].nameid) == 0)
		return;
	if(pc_candrop(sd,sd->status.inventory[idx].nameid))
		return;

	if(pc_cart_additem(sd, item_data, amount) == 0)
		pc_delitem(sd, idx, amount, 0, 5);

	return;
}

/*==========================================
 * カート内のアイテム数確認(個数の差分を返す)
 *------------------------------------------
 */
int pc_cartitem_amount(struct map_session_data *sd,int idx,int amount)
{
	struct item *item_data;

	nullpo_retr(-1, sd);
	nullpo_retr(-1, item_data = &sd->status.cart[idx]);

	if(item_data->nameid == 0 || item_data->amount <= 0)
		return -1;

	return item_data->amount - amount;
}

/*==========================================
 * カートからアイテム移動
 *------------------------------------------
 */
void pc_getitemfromcart(struct map_session_data *sd, int idx, int amount)
{
	struct item *item_data;
	int flag;

	nullpo_retv(sd);

	if(idx < 0 || idx >= MAX_CART)
		return;

	item_data = &sd->status.cart[idx];
	if(item_data->nameid == 0 || item_data->amount < amount)
		return;

	if((flag = pc_additem(sd, item_data, amount)) == 0) {
		pc_cart_delitem(sd, idx, amount, 0);
		return;
	}
	clif_cart_delitem(sd,idx,amount);
	clif_additem(sd,0,0,flag);
	clif_cart_additem(sd,idx,amount);

	return;
}

/*==========================================
 * アイテム鑑定
 *------------------------------------------
 */
void pc_item_identify(struct map_session_data *sd, int idx)
{
	unsigned char flag = 1;

	nullpo_retv(sd);

	if(idx < 0 || idx >= MAX_INVENTORY)
		return;

	if(sd->status.inventory[idx].nameid > 0 && sd->status.inventory[idx].identify == 0) {
		flag = 0;
		sd->status.inventory[idx].identify = 1;
	}
	clif_item_identified(sd,idx,flag);

	return;
}

/*==========================================
 * スティル品公開
 *------------------------------------------
 */
static int pc_show_steal(struct block_list *bl,va_list ap)
{
	struct map_session_data *sd;
	struct item_data *item = NULL;
	int type, fd = -1;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, sd = va_arg(ap,struct map_session_data *));

	if(bl->type == BL_PC) {
		struct map_session_data *dsd = (struct map_session_data *)bl;
		if(dsd)
			fd = dsd->fd;
	}
	if(fd < 0)
		return 0;

	item = va_arg(ap,struct item_data *);
	type = va_arg(ap,int);

	if(!type) {
		if(item == NULL)
			msg_output(fd, msg_txt(136), sd->status.name);	// %sがUnknown_Itemをスティールしました
		else
			msg_output(fd, msg_txt(137), sd->status.name, item->jname);	// %sが%sをスティールしました
	} else {
		msg_output(fd, msg_txt(138), sd->status.name);	// %sは重量オーバーによりアイテムを取得できませんでした
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int pc_steal_item(struct map_session_data *sd,struct mob_data *md)
{
	int skill,rate,itemid,flag;
	struct mobdb_data *id;

	nullpo_retr(0, sd);
	nullpo_retr(0, md);

	id = mobdb_search(md->class_);

	if(battle_config.item_rate <= 0 || md->state.steal_flag)
		return 0;
	if(id->mexp > 0 || id->mode&MD_BOSS)
		return 0;
	if(md->sc.data[SC_STONE].timer != -1 || md->sc.data[SC_FREEZE].timer != -1)
		return 0;

	skill = (sd->paramc[4] - id->dex)/2 + pc_checkskill(sd,TF_STEAL) * 6 + 4;
	if(skill > 0) {
		int i;
		for(i=0; i<ITEM_DROP_COUNT-1; i++) {
			itemid = id->dropitem[i].nameid;
			if(itemid > 0 && itemdb_type(itemid) != ITEMTYPE_CARD) {
				if(id->dropitem[i].p <= 0)
					continue;
				rate = id->dropitem[i].p * skill * battle_config.steal_rate / 10000 + 1;
				if(rate > 0 && sd->add_steal_rate > 0)
					rate = rate * sd->add_steal_rate / 100;

				if(battle_config.battle_log)
					printf("skill=%d, mob base=%d, rate=%d, bc.rate=%d, add=%d\n",
						skill, id->dropitem[i].p, rate, battle_config.steal_rate, sd->add_steal_rate );

				if(atn_rand()%10000 < rate) {
					struct item tmp_item;
					memset(&tmp_item,0,sizeof(tmp_item));
					tmp_item.nameid = itemid;
					tmp_item.amount = 1;
					tmp_item.identify = !itemdb_isequip3(itemid);
					if(battle_config.itemidentify)
						tmp_item.identify = 1;
					flag = pc_additem(sd,&tmp_item,1);
					if(battle_config.show_steal_in_same_party)
						party_foreachsamemap(pc_show_steal,sd,PT_AREA_SIZE,sd,itemdb_exists(tmp_item.nameid),0);
					if(flag) {
						if(battle_config.show_steal_in_same_party)
							party_foreachsamemap(pc_show_steal,sd,PT_AREA_SIZE,sd,itemdb_exists(tmp_item.nameid),1);
						clif_additem(sd,0,0,flag);
					}
					md->state.steal_flag = 1;
					return 1;
				}
			}
		}
	}
	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int pc_steal_coin(struct map_session_data *sd,struct mob_data *md)
{
	int rate,skilllv,lv;

	nullpo_retr(0, sd);
	nullpo_retr(0, md);

	if(md->state.steal_coin_flag)
		return 0;
	if(md->sc.data[SC_STONE].timer != -1 || md->sc.data[SC_FREEZE].timer != -1)
		return 0;

	lv = mobdb_search(md->class_)->lv;
	skilllv = pc_checkskill(sd,RG_STEALCOIN);
	rate  = skilllv*10 + (sd->status.base_level - lv)*2 + (sd->paramc[4] + sd->paramc[5])/2;

	if(atn_rand()%1000 < rate) {
		int max = 10 * lv;
		int min = 8 * lv;
		int range = max - min + 1;
		int rnd = atn_rand()%range+min;
		int zeny = lv * skilllv / 10 + rnd;
		pc_getzeny(sd,zeny);
		md->state.steal_coin_flag = 1;
		return 1;
	}

	return 0;
}

/*==========================================
 * PCの位置設定
 *------------------------------------------
 */
int pc_setpos(struct map_session_data *sd,const char *mapname,int x,int y,int clrtype)
{
	int m, i, move_flag = 0;

	nullpo_retr(1, sd);

	// 座っていたら立ち上がる
	if(pc_issit(sd)) {
		pc_setstand(sd);
		skill_sit(sd,0);
	}

	// 死んでいたら立ち上がる
	if(unit_isdead(&sd->bl)) {
		pc_setstand(sd);
		pc_setrestartvalue(sd,3);
	}

	m = map_mapname2mapid(mapname);
	if(m < 0) {
		unsigned long ip;
		unsigned short port;
		if(map_mapname2ipport(mapname,&ip,&port) == 0) {
			// 違うマップサーバーに割り当てられているマップに移動
			if( sd->pd ) {
				pet_lootitem_drop(sd->pd,sd);
				unit_free(&sd->pd->bl, 0);
			}
			if( sd->hd ) {
				if(battle_config.save_homun_temporal_intimate)
					pc_setglobalreg(sd,"HOM_TEMP_INTIMATE",sd->hd->intimate);
				unit_free(&sd->hd->bl, 0);
			}
			if( sd->mcd ) {
				unit_free(&sd->mcd->bl, 0);
			}
			if( sd->eld ) {
				unit_free(&sd->eld->bl, 0);
			}
			unit_free(&sd->bl,clrtype);
			strncpy(sd->status.last_point.map,mapname,24);
			sd->status.last_point.x = x;
			sd->status.last_point.y = y;
			chrif_save(sd, 3);
			sd->state.waitingdisconnect = 1;
			return 0;
		}
		return 1;
	}

	// スタック判定
	if(x < 0 || x >= map[m].xs || y < 0 || y >= map[m].ys)
		x = y = 0;
	if((x == 0 && y == 0) || map_getcell(m,x,y,CELL_CHKNOPASS)) {
		int i = 0;
		if(x || y) {
			if(battle_config.error_log)
				printf("stacked %s (%d,%d)\n", map[m].name, x, y);
		}
		do {
			x = atn_rand()%(map[m].xs-2)+1;
			y = atn_rand()%(map[m].ys-2)+1;
		} while(map_getcell(m,x,y,CELL_CHKNOPASS) && (i++) < 1000);
		if(i >= 1000) {
			if(battle_config.error_log)
				printf("pc_setpos: not found free cell in %s!!\n", map[m].name);
			return 1;
		}
	}

	if(m == sd->bl.m) {
		// 同じマップなのでダンスユニット引き継ぎ
		sd->ud.to_x = x;
		sd->ud.to_y = y;
		skill_stop_dancing(&sd->bl, 2);	// 移動先にユニットを移動するかどうかの判断もする
	} else {
		// 違うマップなのでダンスユニット削除
		skill_stop_dancing(&sd->bl, 1);

		// 太陽・月・星の安楽効果削除
		if(sd->sc.data[SC_SUN_COMFORT].timer != -1)
			status_change_end(&sd->bl, SC_SUN_COMFORT, -1);
		if(sd->sc.data[SC_MOON_COMFORT].timer != -1)
			status_change_end(&sd->bl, SC_MOON_COMFORT, -1);
		if(sd->sc.data[SC_STAR_COMFORT].timer != -1)
			status_change_end(&sd->bl, SC_STAR_COMFORT, -1);

		// 凸面鏡の効果削除
		if(sd->sc.data[SC_BOSSMAPINFO].timer != -1)
			status_change_end(&sd->bl, SC_BOSSMAPINFO, -1);
		// メモリアルダンジョンのユーザー数チェック
		if(map[m].memorial_id != map[sd->bl.m].memorial_id) {
			// メモリアルダンジョンのユーザー数追加
			if(map[m].memorial_id)
				memorial_addusers(map[m].memorial_id);
			// メモリアルダンジョンのユーザー数削除
			if(map[sd->bl.m].memorial_id)
				memorial_delusers(map[sd->bl.m].memorial_id);
		}
	}
	status_change_hidden_end(&sd->bl);

	// 温もりユニット削除
	if(sd->sc.data[SC_WARM].timer != -1)
		status_change_end(&sd->bl, SC_WARM, -1);
	// ニュートラルバリアー削除
	if(sd->sc.data[SC_NEUTRALBARRIER_USER].timer != -1)
		status_change_end(&sd->bl, SC_NEUTRALBARRIER_USER, -1);
	// ステルスフィールド削除
	if(sd->sc.data[SC_STEALTHFIELD_USER].timer != -1)
		status_change_end(&sd->bl, SC_STEALTHFIELD_USER, -1);
	// バンディング削除
	if(sd->sc.data[SC_BANDING].timer != -1)
		status_change_end(&sd->bl, SC_BANDING, -1);
	// ディボーション削除(献身対象者)
	if(sd->sc.data[SC_DEVOTION].timer != -1)
		status_change_end(&sd->bl, SC_DEVOTION, -1);
	// ディボーション削除(献身者)
	for(i=0; i<5; i++) {
		if(sd->dev.val1[i]) {
			status_change_end(map_id2bl(sd->dev.val1[i]),SC_DEVOTION,-1);
			sd->dev.val1[i] = sd->dev.val2[i] = 0;
		}
	}

	if(sd->bl.prev != NULL) {
		if(m != sd->bl.m) {
			move_flag = 1;	// 新規ログインでなくて違うMAPへ移動ならflagオン
		}
		unit_remove_map(&sd->bl, clrtype&0xffff, !move_flag);
		if(sd->status.pet_id > 0 && sd->pd) {
			if(sd->pd->bl.m != m && sd->pet.intimate <= 0) {
				unit_free(&sd->pd->bl, 0);
				sd->status.pet_id = 0;
				sd->pd = NULL;
				sd->petDB = NULL;
				if(battle_config.pet_status_support)
					status_calc_pc(sd,2);
			}
			else if(sd->pet.intimate > 0) {
				unit_remove_map(&sd->pd->bl, clrtype&0xffff, !move_flag);
			}
		}
		if(sd->status.homun_id > 0 && sd->hd) {
			unit_remove_map(&sd->hd->bl, clrtype&0xffff, !move_flag);
		}
		if(sd->status.merc_id > 0 && sd->mcd) {
			unit_remove_map(&sd->mcd->bl, clrtype&0xffff, !move_flag);
		}
		if(sd->status.elem_id > 0 && sd->eld) {
			unit_remove_map(&sd->eld->bl, clrtype&0xffff, !move_flag);
		}
		clif_changemap(sd,map[m].name,x,y);
	}

	// OnPCMapOutイベント
	if(move_flag && battle_config.pc_mapout_script)
		npc_event_doall_id("OnPCMapOut",sd->bl.id,sd->bl.m);

	strncpy(sd->mapname,mapname,24);
	sd->bl.m = m;
	sd->bl.x = x;
	sd->bl.y = y;

	if(map[sd->bl.m].flag.gvg) {
		// 攻城戦時にモンスター変身を解除させるか
		if(battle_config.disable_transform_when_gvg) {
			if(sd->sc.data[SC_MONSTER_TRANSFORM].timer != -1)
				status_change_end(&sd->bl, SC_MONSTER_TRANSFORM, -1);
		}
		// 攻城戦時にコスチュームアイテムを解除させるか
		if(battle_config.disable_costume_when_gvg) {
			for(i = EQUIP_INDEX_COSTUME_HEAD; i < EQUIP_INDEX_MAX; i++) {
				if(sd->equip_index[i] >= 0 && pc_isequip(sd,sd->equip_index[i]) <= 0)
					pc_unequipitem(sd,sd->equip_index[i],1);	// 装備外し
			}
		}
		if(sd->sc.data[SC_SUPPORT_HPSP].timer != -1)			// サポート魔法(HPSP増加)
			status_change_end(&sd->bl, SC_SUPPORT_HPSP, -1);
		if(sd->sc.data[SC_SUPPORT_SPEED].timer != -1)			// サポート魔法(移動速度増加)
			status_change_end(&sd->bl, SC_SUPPORT_SPEED, -1);
	}

	// ペットの移動
	if(sd->status.pet_id > 0 && sd->pd && sd->pet.intimate > 0) {
		sd->pd->bl.m = m;
		sd->pd->bl.x = sd->pd->ud.to_x = x;
		sd->pd->bl.y = sd->pd->ud.to_y = y;
		sd->pd->dir  = sd->dir;
	}
	// ホムの移動
	if(sd->status.homun_id > 0 && sd->hd) {
		sd->hd->bl.m = m;
		sd->hd->bl.x = sd->hd->ud.to_x = x;
		sd->hd->bl.y = sd->hd->ud.to_y = y;
		sd->hd->dir  = sd->dir;
	}
	// 傭兵の移動
	if(sd->status.merc_id > 0 && sd->mcd) {
		sd->mcd->bl.m = m;
		sd->mcd->bl.x = sd->mcd->ud.to_x = x;
		sd->mcd->bl.y = sd->mcd->ud.to_y = y;
		sd->mcd->dir  = sd->dir;
	}
	// 精霊の移動
	if(sd->status.elem_id > 0 && sd->eld) {
		sd->eld->bl.m = m;
		sd->eld->bl.x = sd->eld->ud.to_x = x;
		sd->eld->bl.y = sd->eld->ud.to_y = y;
		sd->eld->dir  = sd->dir;
	}

	// OnPCMoveMapイベント
	if(move_flag && battle_config.pc_movemap_script)
		npc_event_doall_id("OnPCMoveMap",sd->bl.id,sd->bl.m);

	// ブロック登録とspawnは clif_parse_LoadEndAck で行う

	return 0;
}

/*==========================================
 * ギルドスキルの有効チェック
 * 変化があればステータスの再計算
 *------------------------------------------
 */
static int pc_check_guild_skill_effective_range_sub(struct guild *g,struct map_session_data *gmsd,struct map_session_data *member)
{
	int dx, dy, range;

	nullpo_retr(0, g);
	nullpo_retr(0, gmsd);
	nullpo_retr(0, member);

	dx = abs(gmsd->bl.x - member->bl.x);
	dy = abs(gmsd->bl.y - member->bl.y);

	if(battle_config.guild_skill_effective_range > 0) {	// スキルを同一距離判定する
		range = battle_config.guild_skill_effective_range;
		if(dx <= range && dy <= range) {	// 範囲内
			if(member->under_the_influence_of_the_guild_skill == 0)	// 効果外だった
				return 1;
		} else {				// 範囲外
			if(member->under_the_influence_of_the_guild_skill > 0)	// 効果内だった
				return 1;
		}
	} else {						// スキルを個別に距離判定する
		int min_range = 0x7fffffff;
		range = skill_get_range(GD_LEADERSHIP,guild_skill_get_lv(g,GD_LEADERSHIP));
		if(guild_skill_get_lv(g,GD_LEADERSHIP) > 0 && dx <= range && dy <= range) {
			if(min_range > range)
				min_range = range;
		}
		range = skill_get_range(GD_SOULCOLD,guild_skill_get_lv(g,GD_SOULCOLD));
		if(guild_skill_get_lv(g,GD_SOULCOLD) > 0 && dx <= range && dy <= range) {
			if(min_range > range)
				min_range = range;
		}
		range = skill_get_range(GD_GLORYWOUNDS,guild_skill_get_lv(g,GD_GLORYWOUNDS));
		if(guild_skill_get_lv(g,GD_GLORYWOUNDS) > 0 && dx <= range && dy <= range) {
			if(min_range > range)
				min_range = range;
		}
		range = skill_get_range(GD_HAWKEYES,guild_skill_get_lv(g,GD_HAWKEYES));
		if(guild_skill_get_lv(g,GD_HAWKEYES) > 0 && dx <= range && dy <= range) {
			if(min_range > range)
				min_range = range;
		}

		if(min_range == 0x7fffffff) {	// 効果範囲外
			if(member->under_the_influence_of_the_guild_skill > 0)	// 前は効果範囲内だった
				return 1;
		} else {			// 効果範囲内
			if(member->under_the_influence_of_the_guild_skill == 0)	// 前は範囲外だった
				return 1;
			if((min_range+1) != member->under_the_influence_of_the_guild_skill)
				// 前は範囲内で今回距離が変わった->幾つか効果変動
				return 1;
		}
	}
	return 0;
}

int pc_check_guild_skill_effective_range(struct map_session_data *sd)
{
	struct map_session_data *gmsd = NULL;
	struct guild *g = NULL;

	nullpo_retr(0, sd);

	// ギルドに入っていない
	if(sd->status.guild_id == 0)
		return 0;
	// ギルドスキルが無効
	if(!battle_config.guild_hunting_skill_available)
		return 0;

	// ギルド取得できなかった
	if((g = guild_search(sd->status.guild_id)) == NULL)
		return 0;

	// マスター接続していない
	if((gmsd = g->member[0].sd) == NULL) {
		// 効果範囲内だった
		if(sd->under_the_influence_of_the_guild_skill > 0)
			status_calc_pc(sd,0);
		return 0;
	}

	// スキル１以上
	if( pc_checkskill(gmsd,GD_LEADERSHIP) > 0 ||
	    pc_checkskill(gmsd,GD_SOULCOLD) > 0 ||
	    pc_checkskill(gmsd,GD_GLORYWOUNDS) > 0 ||
	    pc_checkskill(gmsd,GD_HAWKEYES) > 0 )
	{
		if(sd == gmsd) {	// 自分がギルマス
			int i;
			if(battle_config.allow_me_guild_skill && sd->under_the_influence_of_the_guild_skill == 0)
				status_calc_pc(sd,0);

			// スキル距離判定
			for(i = 1; i < g->max_member; i++) {
				struct map_session_data *member = g->member[i].sd;
				if(member == NULL)	// メンバー接続なし
					continue;

				if(member->bl.m != gmsd->bl.m) {	// マップが違う
					if(member->under_the_influence_of_the_guild_skill > 0)	// 前回は効果範囲内だった
						status_calc_pc(member,0);
				} else if(pc_check_guild_skill_effective_range_sub(g, gmsd, member)) {
					status_calc_pc(member,0);
				}
			}
		} else {	// ギルメン
			if(sd->bl.m != gmsd->bl.m) {	// マップが違う
				if(sd->under_the_influence_of_the_guild_skill > 0)	// 前回は効果範囲内だった
					status_calc_pc(sd,0);
			} else if(pc_check_guild_skill_effective_range_sub(g, gmsd, sd)) {
				status_calc_pc(sd,0);
			}
		}
	}
	return 1;
}

/*==========================================
 * PCのランダムワープ
 *------------------------------------------
 */
int pc_randomwarp(struct map_session_data *sd,int type)
{
	int m, x, y;
	int i = 0;

	nullpo_retr(0, sd);

	m = sd->bl.m;

	if(map[m].flag.noteleport)	// テレポート禁止
		return 0;

	do {
		x = atn_rand()%(map[m].xs-2)+1;
		y = atn_rand()%(map[m].ys-2)+1;
	} while( map_getcell(m,x,y,CELL_CHKNOPASS) && (i++) < 1000 );

	if(i < 1000) {
		pc_setpos(sd,map[m].name,x,y,type);
		return 1;
	}

	return 0;
}


/*==========================================
 * 現在位置のメモ
 *------------------------------------------
 */
void pc_memo(struct map_session_data *sd,int i)
{
	int skill, j;

	nullpo_retv(sd);

	if(map[sd->bl.m].flag.nomemo) {
		clif_skill_teleportmessage(sd,1);
		return;
	}

	skill = pc_checkskill(sd, AL_WARP);
	if (skill < 1) {
		clif_skill_memo(sd, 2); // 00: success to take memo., 01: insuffisant skill level., 02: You don't know warp skill.
		return;
	}

	if (skill < 2 || (i != -1 && (i < 0 || i >= MAX_PORTAL_MEMO))) {
		clif_skill_memo(sd,1);
		return;
	}

	for(j = 0; j < MAX_PORTAL_MEMO; j++) {
		if(strcmp(sd->status.memo_point[j].map,map[sd->bl.m].name) == 0) {
			i = j;
			break;
		}
	}

	if(i == -1) {
		i = skill - 3;
		if(i > MAX_PORTAL_MEMO - 2)
			i = MAX_PORTAL_MEMO;
		for( ; i >= 0; i--) {
			memcpy(&sd->status.memo_point[i+1],&sd->status.memo_point[i],sizeof(struct point));
		}
		i = 0;
	}

	strncpy(sd->status.memo_point[i].map,map[sd->bl.m].name,24);
	sd->status.memo_point[i].map[23] = '\0';	// force \0 terminal
	sd->status.memo_point[i].x       = sd->bl.x;
	sd->status.memo_point[i].y       = sd->bl.y;

	clif_skill_memo(sd,0);

	return;
}

/*==========================================
 * 駆け足要求
 *------------------------------------------
 */
int pc_runtodir(struct map_session_data *sd)
{
	int i,to_x,to_y,dir_x,dir_y;

	nullpo_retr(0, sd);

	to_x  = sd->bl.x;
	to_y  = sd->bl.y;
	dir_x = dirx[(int)sd->dir];
	dir_y = diry[(int)sd->dir];

	for(i=0; i<AREA_SIZE; i++) {
		if(!map_getcell(sd->bl.m,to_x+dir_x,to_y+dir_y,CELL_CHKPASS))
			break;

		// 次のセルへ１歩で移動可能でない、もしくはPC,MOB,NPCが居たら
		if(map_getcell(sd->bl.m,to_x+dir_x,to_y+dir_y,CELL_CHKNOPASS) ||
		   map_getcell(sd->bl.m,to_x      ,to_y+dir_y,CELL_CHKNOPASS) ||
		   map_getcell(sd->bl.m,to_x+dir_x,to_y      ,CELL_CHKNOPASS) ||
		   map_count_oncell(sd->bl.m,to_x+dir_x,to_y+dir_y,BL_PC|BL_MOB|BL_NPC) > 0)
			break;

		to_x += dir_x;
		to_y += dir_y;
	}

	// 進めない場合駆け足終了
	if(to_x == sd->bl.x && to_y == sd->bl.y) {
		if(sd->sc.data[SC_RUN].timer != -1) {
			int dir = sd->dir;
			int head_dir = sd->head_dir;

			// 初回呼び出し時で一歩も動けないときはノックバックしない
			if(sd->sc.data[SC_RUN].val4 > 0)
				skill_blown(&sd->bl,&sd->bl,skill_get_blewcount(TK_RUN,sd->sc.data[SC_RUN].val1)|SAB_NODAMAGE);
			status_change_end(&sd->bl,SC_RUN,-1);
			clif_status_change(&sd->bl,SI_RUN_STOP,1,0,0,0,0);
			pc_setdir(sd, dir, head_dir);
		}
		if(sd->sc.data[SC_WUGDASH].timer != -1) {
			if(pc_checkskill(sd,RA_WUGSTRIKE))
				skill_castend_damage_id(&sd->bl,&sd->bl,RA_WUGDASH,sd->sc.data[SC_WUGDASH].val1,gettick(),0);
			status_change_end(&sd->bl,SC_WUGDASH,-1);
			pc_setdir(sd, sd->dir, sd->head_dir);
		}
	} else {
		unit_walktoxy( &sd->bl, to_x, to_y);
	}

	return 1;
}

/*==========================================
 * スキルの検索 所有していた場合Lvが返る
 *------------------------------------------
 */
int pc_checkskill(struct map_session_data *sd,int skill_id)
{
	if(sd == NULL)
		return 0;

	if(skill_id >= GUILD_SKILLID) {
		struct guild *g;
		if(sd->status.guild_id > 0 && (g = guild_search(sd->status.guild_id)) != NULL)
			return guild_checkskill(g,skill_id);
		return 0;
	}

	if(skill_id < 0 || skill_id >= MAX_PCSKILL)
		return 0;

	if(sd->skill_clone.id > 0 && skill_id == sd->skill_clone.id)
		return (sd->skill_clone.lv > sd->status.skill[skill_id].lv ? sd->skill_clone.lv : sd->status.skill[skill_id].lv);

	if(sd->skill_reproduce.id > 0 && skill_id == sd->skill_reproduce.id)
		return (sd->skill_reproduce.lv > sd->status.skill[skill_id].lv ? sd->skill_reproduce.lv : sd->status.skill[skill_id].lv);

	if(sd->status.skill[skill_id].id == skill_id)
	{
		if(sd->status.class_ == PC_CLASS_TK &&
		   sd->status.skill[skill_id].flag == 0 &&
		   pc_checkskill2(sd,TK_MISSION) > 0 &&
		   sd->status.base_level >= 90 &&
		   sd->status.skill_point == 0 &&
		   ranking_get_pc_rank(sd,RK_TAEKWON)) {
			return pc_get_skilltree_max(&sd->s_class,skill_id);
		} else {
			return sd->status.skill[skill_id].lv;
		}
	}

	return 0;
}

/*==========================================
 * スキルの検索 所有していた場合Lvが返る
 *------------------------------------------
 */
int pc_checkskill2(struct map_session_data *sd,int skill_id)
{
	if(sd == NULL)
		return 0;

	if(skill_id >= GUILD_SKILLID) {
		struct guild *g;
		if(sd->status.guild_id > 0 && (g = guild_search(sd->status.guild_id)) != NULL)
			return guild_checkskill(g,skill_id);
		return 0;
	}

	if(skill_id < 0 || skill_id >= MAX_PCSKILL)
		return 0;

	if(sd->status.skill[skill_id].id == skill_id)
		return sd->status.skill[skill_id].lv;

	return 0;
}

/*==========================================
 * スキルの検索 所有していた場合Lvが返る
 *------------------------------------------
 */
int pc_checkskill_summoner(struct map_session_data *sd, int skill_id) {
	int count = 0;

	if(sd == NULL)
		return 0;

	switch(skill_id) {
	case SU_POWEROFSEA:
		count = pc_checkskill(sd, SU_TUNABELLY) + pc_checkskill(sd, SU_TUNAPARTY) + pc_checkskill(sd, SU_BUNCHOFSHRIMP) + pc_checkskill(sd, SU_FRESHSHRIMP) +
			pc_checkskill(sd, SU_GROOMING) + pc_checkskill(sd, SU_PURRING) + pc_checkskill(sd, SU_SHRIMPARTY);
		break;
	case SU_POWEROFLAND:
		count = pc_checkskill(sd, SU_SV_STEMSPEAR) + pc_checkskill(sd, SU_CN_POWDERING) + pc_checkskill(sd, SU_CN_METEOR) + pc_checkskill(sd, SU_SV_ROOTTWIST) +
			pc_checkskill(sd, SU_CHATTERING) + pc_checkskill(sd, SU_MEOWMEOW) + pc_checkskill(sd, SU_NYANGGRASS);
		break;
	case SU_POWEROFLIFE:
		count = pc_checkskill(sd, SU_SCAROFTAROU) + pc_checkskill(sd, SU_PICKYPECK) + pc_checkskill(sd, SU_ARCLOUSEDASH) + pc_checkskill(sd, SU_LUNATICCARROTBEAT) +
			pc_checkskill(sd, SU_HISS) + pc_checkskill(sd, SU_POWEROFFLOCK) + pc_checkskill(sd, SU_SVG_SPIRIT);
		break;
	}

	return count;
}

/*==========================================
 * 武器変更によるスキルの継続チェック
 *------------------------------------------
 */
static int pc_checkallowskill(struct map_session_data *sd)
{
	int i, weapon;
	unsigned mask = 0;
	const int skill_list[] = {
		KN_TWOHANDQUICKEN,
		KN_ONEHAND,
#ifdef PRE_RENEWAL
		LK_AURABLADE,
		LK_CONCENTRATION,
#endif
		LK_PARRYING,
		CR_SPEARQUICKEN,
		BS_ADRENALINE,
		BS_ADRENALINE2,
		GS_GATLINGFEVER,
		RK_ENCHANTBLADE,
		GC_POISONINGWEAPON,
		AB_EXPIATIO,
		RA_FEARBREEZE,
	};

	nullpo_retr(0, sd);

	if( sd->sc.count <= 0 )
		return 0;

	weapon = sd->status.weapon;
	if(sd->status.weapon >= WT_MAX)
		weapon -= WT_DOUBLE_DD + WT_MAX;

	mask = 1 << weapon;

	// 武器が合わないならステータス異常を解除
	for(i=0; i < sizeof(skill_list)/sizeof(skill_list[0]); i++) {
		int type = GetSkillStatusChangeTable(skill_list[i]);
		if( type >= 0 && sd->sc.data[type].timer != -1 ) {
			if( !(skill_get_weapontype(skill_list[i]) & mask) )
				status_change_end(&sd->bl, type, -1);
		}
	}

	if( sd->sc.data[SC_DANCING].timer != -1 ) {
		if( !(skill_get_weapontype(sd->sc.data[SC_DANCING].val1) & mask) )
			skill_stop_dancing(&sd->bl,0);	// 演奏解除
	}
	if( sd->sc.data[SC_SPURT].timer != -1 && (sd->weapontype1 != WT_FIST || sd->weapontype2 != WT_FIST) ) {
		status_change_end(&sd->bl,SC_SPURT,-1);	// 駆け足STR
	}
#ifndef PRE_RENEWAL
	if( sd->sc.data[SC_AURABLADE].timer != -1) {	// オーラブレード
		status_change_end(&sd->bl,SC_AURABLADE,-1);
	}
	if( sd->sc.data[SC_CONCENTRATION].timer != -1) {	// コンセントレーション
		status_change_end(&sd->bl,SC_CONCENTRATION,-1);
	}
	if( sd->sc.data[SC_TENSIONRELAX].timer != -1) {	// テンションリラックス
		status_change_end(&sd->bl,SC_TENSIONRELAX,-1);
	}
	if( sd->sc.data[SC_OVERTHRUSTMAX].timer != -1) {	// オーバートラストマックス
		status_change_end(&sd->bl,SC_OVERTHRUSTMAX,-1);
	}
#endif
	if( sd->sc.data[SC_HEAT_BARREL].timer != -1) {	// ヒートバレル
		status_change_end(&sd->bl,SC_HEAT_BARREL,-1);
	}
	if( sd->sc.data[SC_P_ALTER].timer != -1) {	// プラチナムアルター
		status_change_end(&sd->bl,SC_P_ALTER,-1);
	}

	if(sd->status.shield <= 0) {
		if(sd->sc.data[SC_AUTOGUARD].timer != -1) {		// オートガード
			status_change_end(&sd->bl,SC_AUTOGUARD,-1);
		}
		if(sd->sc.data[SC_DEFENDER].timer != -1) {		// ディフェンダー
			status_change_end(&sd->bl,SC_DEFENDER,-1);
		}
		if(sd->sc.data[SC_REFLECTSHIELD].timer != -1) {		// リフレクトシールド
			status_change_end(&sd->bl,SC_REFLECTSHIELD,-1);
		}
		if(sd->sc.data[SC_REFLECTDAMAGE].timer != -1) {		// リフレクトダメージ
			status_change_end(&sd->bl,SC_REFLECTDAMAGE,-1);
		}
		if(sd->sc.data[SC_SHIELDSPELL_DEF].timer != -1) {		// シールドスペル(DEF)
			status_change_end(&sd->bl,SC_SHIELDSPELL_DEF,-1);
		}
		if(sd->sc.data[SC_SHIELDSPELL_MDEF].timer != -1) {		// シールドスペル(MDEF)
			status_change_end(&sd->bl,SC_SHIELDSPELL_MDEF,-1);
		}
		if(sd->sc.data[SC_SHIELDSPELL_REF].timer != -1) {		// シールドスペル(精錬)
			status_change_end(&sd->bl,SC_SHIELDSPELL_REF,-1);
		}
	}
	return 0;
}

/*==========================================
 * 装備品のチェック
 *------------------------------------------
 */
int pc_checkequip(struct map_session_data *sd,int pos)
{
	int i;

	nullpo_retr(-1, sd);

	for(i=0; i<EQUIP_INDEX_MAX; i++) {
		if(pos & equip_pos[i])
			return sd->equip_index[i];
	}

	return -1;
}

/*==========================================
 * 転生職や養子職の元の職業を返す
 *------------------------------------------
 */
struct pc_base_job pc_calc_base_job(int b_class)
{
	struct pc_base_job bj;

	memset(&bj, 0, sizeof(bj));

	switch(b_class) {
		case PC_CLASS_NV:
		case PC_CLASS_SM:
		case PC_CLASS_MG:
		case PC_CLASS_AC:
		case PC_CLASS_AL:
		case PC_CLASS_MC:
		case PC_CLASS_TF:
		case PC_CLASS_KN:
		case PC_CLASS_PR:
		case PC_CLASS_WZ:
		case PC_CLASS_BS:
		case PC_CLASS_HT:
		case PC_CLASS_AS:
			bj.job   = b_class;
			bj.upper = PC_UPPER_NORMAL;
			break;
		case PC_CLASS_KN2:
			bj.job   = PC_JOB_KN;
			bj.upper = PC_UPPER_NORMAL;
			break;
		case PC_CLASS_CR:
		case PC_CLASS_MO:
		case PC_CLASS_SA:
		case PC_CLASS_RG:
		case PC_CLASS_AM:
		case PC_CLASS_BA:
		case PC_CLASS_DC:
			bj.job   = b_class - PC_CLASS_CR + PC_JOB_CR;
			bj.upper = PC_UPPER_NORMAL;
			break;
		case PC_CLASS_CR2:
			bj.job   = PC_JOB_CR;
			bj.upper = PC_UPPER_NORMAL;
			break;
		case PC_CLASS_SNV:
			bj.job   = PC_JOB_SNV;
			bj.upper = PC_UPPER_NORMAL;
			break;
		case PC_CLASS_ESNV:
			bj.job   = PC_JOB_ESNV;
			bj.upper = PC_UPPER_NORMAL;
			break;
		case PC_CLASS_GS:
			bj.job   = PC_JOB_GS;
			bj.upper = PC_UPPER_NORMAL;
			break;
		case PC_CLASS_NJ:
			bj.job   = PC_JOB_NJ;
			bj.upper = PC_UPPER_NORMAL;
			break;
		case PC_CLASS_NV_H:
		case PC_CLASS_SM_H:
		case PC_CLASS_MG_H:
		case PC_CLASS_AC_H:
		case PC_CLASS_AL_H:
		case PC_CLASS_MC_H:
		case PC_CLASS_TF_H:
		case PC_CLASS_KN_H:
		case PC_CLASS_PR_H:
		case PC_CLASS_WZ_H:
		case PC_CLASS_BS_H:
		case PC_CLASS_HT_H:
		case PC_CLASS_AS_H:
			bj.job   = b_class - PC_CLASS_NV_H;
			bj.upper = PC_UPPER_HIGH;
			break;
		case PC_CLASS_KN2_H:
			bj.job   = PC_JOB_KN;
			bj.upper = PC_UPPER_HIGH;
			break;
		case PC_CLASS_CR_H:
		case PC_CLASS_MO_H:
		case PC_CLASS_SA_H:
		case PC_CLASS_RG_H:
		case PC_CLASS_AM_H:
		case PC_CLASS_BA_H:
		case PC_CLASS_DC_H:
			bj.job   = b_class - PC_CLASS_CR_H + PC_JOB_CR;
			bj.upper = PC_UPPER_HIGH;
			break;
		case PC_CLASS_CR2_H:
			bj.job   = PC_JOB_CR;
			bj.upper = PC_UPPER_HIGH;
			break;
		case PC_CLASS_NV_B:
		case PC_CLASS_SM_B:
		case PC_CLASS_MG_B:
		case PC_CLASS_AC_B:
		case PC_CLASS_AL_B:
		case PC_CLASS_MC_B:
		case PC_CLASS_TF_B:
		case PC_CLASS_KN_B:
		case PC_CLASS_PR_B:
		case PC_CLASS_WZ_B:
		case PC_CLASS_BS_B:
		case PC_CLASS_HT_B:
		case PC_CLASS_AS_B:
			bj.job   = b_class - PC_CLASS_NV_B;
			bj.upper = PC_UPPER_BABY;
			break;
		case PC_CLASS_KN2_B:
			bj.job   = PC_JOB_KN;
			bj.upper = PC_UPPER_BABY;
			break;
		case PC_CLASS_CR_B:
		case PC_CLASS_MO_B:
		case PC_CLASS_SA_B:
		case PC_CLASS_RG_B:
		case PC_CLASS_AM_B:
		case PC_CLASS_BA_B:
		case PC_CLASS_DC_B:
			bj.job   = b_class - PC_CLASS_CR_B + PC_JOB_CR;
			bj.upper = PC_UPPER_BABY;
			break;
		case PC_CLASS_CR2_B:
			bj.job   = PC_JOB_CR;
			bj.upper = PC_UPPER_BABY;
			break;
		case PC_CLASS_SNV_B:
			bj.job   = PC_JOB_SNV;
			bj.upper = PC_UPPER_BABY;
			break;
		case PC_CLASS_ESNV_B:
			bj.job   = PC_JOB_ESNV;
			bj.upper = PC_UPPER_BABY;
			break;
		case PC_CLASS_TK:
			bj.job   = PC_JOB_TK;
			bj.upper = PC_UPPER_NORMAL;
			break;
		case PC_CLASS_SG:
		case PC_CLASS_SG2:
			bj.job   = PC_JOB_SG;
			bj.upper = PC_UPPER_NORMAL;
			break;
		case PC_CLASS_SL:
			bj.job   = PC_JOB_SL;
			bj.upper = PC_UPPER_NORMAL;
			break;
		case PC_CLASS_MB:
			bj.job   = PC_JOB_MB;
			bj.upper = PC_UPPER_NORMAL;
			break;
		case PC_CLASS_DK:
			bj.job   = PC_JOB_DK;
			bj.upper = PC_UPPER_NORMAL;
			break;
		case PC_CLASS_DA:
			bj.job   = PC_JOB_DA;
			bj.upper = PC_UPPER_NORMAL;
			break;
		case PC_CLASS_RK:
		case PC_CLASS_WL:
		case PC_CLASS_RA:
		case PC_CLASS_AB:
		case PC_CLASS_NC:
		case PC_CLASS_GC:
			bj.job   = b_class - PC_CLASS_RK + PC_JOB_RK;
			bj.upper = PC_UPPER_NORMAL;
			break;
		case PC_CLASS_RK_H:
		case PC_CLASS_WL_H:
		case PC_CLASS_RA_H:
		case PC_CLASS_AB_H:
		case PC_CLASS_NC_H:
		case PC_CLASS_GC_H:
			bj.job   = b_class - PC_CLASS_RK_H + PC_JOB_RK;
			bj.upper = PC_UPPER_HIGH;
			break;
		case PC_CLASS_RK_B:
		case PC_CLASS_WL_B:
		case PC_CLASS_RA_B:
		case PC_CLASS_AB_B:
		case PC_CLASS_NC_B:
		case PC_CLASS_GC_B:
			bj.job   = b_class - PC_CLASS_RK_B + PC_JOB_RK;
			bj.upper = PC_UPPER_BABY;
			break;
		case PC_CLASS_LG:
		case PC_CLASS_SO:
		case PC_CLASS_MI:
		case PC_CLASS_WA:
		case PC_CLASS_SR:
		case PC_CLASS_GN:
		case PC_CLASS_SC:
			bj.job   = b_class - PC_CLASS_LG + PC_JOB_LG;
			bj.upper = PC_UPPER_NORMAL;
			break;
		case PC_CLASS_LG_H:
		case PC_CLASS_SO_H:
		case PC_CLASS_MI_H:
		case PC_CLASS_WA_H:
		case PC_CLASS_SR_H:
		case PC_CLASS_GN_H:
		case PC_CLASS_SC_H:
			bj.job   = b_class - PC_CLASS_LG_H + PC_JOB_LG;
			bj.upper = PC_UPPER_HIGH;
			break;
		case PC_CLASS_LG_B:
		case PC_CLASS_SO_B:
		case PC_CLASS_MI_B:
		case PC_CLASS_WA_B:
		case PC_CLASS_SR_B:
		case PC_CLASS_GN_B:
		case PC_CLASS_SC_B:
			bj.job   = b_class - PC_CLASS_LG_B + PC_JOB_LG;
			bj.upper = PC_UPPER_BABY;
			break;
		case PC_CLASS_RK2:
		case PC_CLASS_RK3:
		case PC_CLASS_RK4:
		case PC_CLASS_RK5:
		case PC_CLASS_RK6:
			bj.job   = PC_JOB_RK;
			bj.upper = PC_UPPER_NORMAL;
			break;
		case PC_CLASS_RK2_H:
		case PC_CLASS_RK3_H:
		case PC_CLASS_RK4_H:
		case PC_CLASS_RK5_H:
		case PC_CLASS_RK6_H:
			bj.job   = PC_JOB_RK;
			bj.upper = PC_UPPER_HIGH;
			break;
		case PC_CLASS_RK2_B:
			bj.job   = PC_JOB_RK;
			bj.upper = PC_UPPER_BABY;
			break;
		case PC_CLASS_LG2:
			bj.job   = PC_JOB_LG;
			bj.upper = PC_UPPER_NORMAL;
			break;
		case PC_CLASS_LG2_H:
			bj.job   = PC_JOB_LG;
			bj.upper = PC_UPPER_HIGH;
			break;
		case PC_CLASS_LG2_B:
			bj.job   = PC_JOB_LG;
			bj.upper = PC_UPPER_BABY;
			break;
		case PC_CLASS_RA2:
			bj.job   = PC_JOB_RA;
			bj.upper = PC_UPPER_NORMAL;
			break;
		case PC_CLASS_RA2_H:
			bj.job   = PC_JOB_RA;
			bj.upper = PC_UPPER_HIGH;
			break;
		case PC_CLASS_RA2_B:
			bj.job   = PC_JOB_RA;
			bj.upper = PC_UPPER_BABY;
			break;
		case PC_CLASS_NC2:
			bj.job   = PC_JOB_NC;
			bj.upper = PC_UPPER_NORMAL;
			break;
		case PC_CLASS_NC2_H:
			bj.job   = PC_JOB_NC;
			bj.upper = PC_UPPER_HIGH;
			break;
		case PC_CLASS_NC2_B:
			bj.job   = PC_JOB_NC;
			bj.upper = PC_UPPER_BABY;
			break;
		case PC_CLASS_KG:
			bj.job   = PC_JOB_KG;
			bj.upper = PC_UPPER_NORMAL;
			break;
		case PC_CLASS_OB:
			bj.job   = PC_JOB_OB;
			bj.upper = PC_UPPER_NORMAL;
			break;
		case PC_CLASS_RL:
			bj.job   = PC_JOB_RL;
			bj.upper = PC_UPPER_NORMAL;
			break;
		case PC_CLASS_SUM:
			bj.job   = PC_JOB_SUM;
			bj.upper = PC_UPPER_NORMAL;
			break;
		default:
			bj.job   = PC_JOB_NV;
			bj.upper = PC_UPPER_NORMAL;
			break;
	}

	return bj;
}

/*==========================================
 * 元の職業からクラスIDを返す
 *------------------------------------------
 */
int pc_calc_class_job(int job, int upper)
{
	int class_ = 0;

	switch(job) {
		case PC_JOB_NV:
		case PC_JOB_SM:
		case PC_JOB_MG:
		case PC_JOB_AC:
		case PC_JOB_AL:
		case PC_JOB_MC:
		case PC_JOB_TF:
		case PC_JOB_KN:
		case PC_JOB_PR:
		case PC_JOB_WZ:
		case PC_JOB_BS:
		case PC_JOB_HT:
		case PC_JOB_AS:
			if(upper == PC_UPPER_HIGH)
				class_ = job + PC_CLASS_NV_H;
			else if(upper == PC_UPPER_BABY)
				class_ = job + PC_CLASS_NV_B;
			else
				class_ = job;
			break;
		case PC_JOB_CR:
		case PC_JOB_MO:
		case PC_JOB_SA:
		case PC_JOB_RG:
		case PC_JOB_AM:
		case PC_JOB_BA:
		case PC_JOB_DC:
			if(upper == PC_UPPER_HIGH)
				class_ = job - PC_JOB_CR + PC_CLASS_CR_H;
			else if(upper == PC_UPPER_BABY)
				class_ = job - PC_JOB_CR + PC_CLASS_CR_B;
			else
				class_ = job - PC_JOB_CR + PC_CLASS_CR;
			break;
		case PC_JOB_SNV:
			if(upper == PC_UPPER_BABY)
				class_ = PC_CLASS_SNV_B;
			else
				class_ = PC_CLASS_SNV;
			break;
		case PC_JOB_ESNV:
			if(upper == PC_UPPER_BABY)
				class_ = PC_CLASS_ESNV_B;
			else
				class_ = PC_CLASS_ESNV;
			break;
		case PC_JOB_TK:
			class_ = PC_CLASS_TK;
			break;
		case PC_JOB_SG:
			class_ = PC_CLASS_SG;
			break;
		case PC_JOB_SL:
			class_ = PC_CLASS_SL;
			break;
		case PC_JOB_GS:
			class_ = PC_CLASS_GS;
			break;
		case PC_JOB_NJ:
			class_ = PC_CLASS_NJ;
			break;
		case PC_JOB_MB:
			class_ = PC_CLASS_MB;
			break;
		case PC_JOB_DK:
			class_ = PC_CLASS_DK;
			break;
		case PC_JOB_DA:
			class_ = PC_CLASS_DA;
			break;
		case PC_JOB_RK:
		case PC_JOB_WL:
		case PC_JOB_RA:
		case PC_JOB_AB:
		case PC_JOB_NC:
		case PC_JOB_GC:
			if(upper == PC_UPPER_HIGH)
				class_ = job - PC_JOB_RK + PC_CLASS_RK_H;
			else if(upper == PC_UPPER_BABY)
				class_ = job - PC_JOB_RK + PC_CLASS_RK_B;
			else
				class_ = job - PC_JOB_RK + PC_CLASS_RK;
			break;
		case PC_JOB_LG:
		case PC_JOB_SO:
		case PC_JOB_MI:
		case PC_JOB_WA:
		case PC_JOB_SR:
		case PC_JOB_GN:
		case PC_JOB_SC:
			if(upper == PC_UPPER_HIGH)
				class_ = job - PC_JOB_LG + PC_CLASS_LG_H;
			else if(upper == PC_UPPER_BABY)
				class_ = job - PC_JOB_LG + PC_CLASS_LG_B;
			else
				class_ = job - PC_JOB_LG + PC_CLASS_LG;
			break;
		case PC_JOB_KG:
			class_ = PC_CLASS_KG;
			break;
		case PC_JOB_OB:
			class_ = PC_CLASS_OB;
			break;
		case PC_JOB_RL:
			class_ = PC_CLASS_RL;
			break;
		case PC_JOB_SUM:
			class_ = PC_CLASS_SUM;
			break;
	}

	return class_;
}

/*==========================================
 * クラスIDから元の職業を返す
 *------------------------------------------
 */
int pc_calc_job_class(int class_)
{
	int job = 0;

	switch(class_){
		case PC_CLASS_NV:
		case PC_CLASS_NV_H:
		case PC_CLASS_NV_B:
			job = PC_JOB_NV;
			break;
		case PC_CLASS_SM:
		case PC_CLASS_SM_H:
		case PC_CLASS_SM_B:
			job = PC_JOB_SM;
			break;
		case PC_CLASS_MG:
		case PC_CLASS_MG_H:
		case PC_CLASS_MG_B:
			job = PC_JOB_MG;
			break;
		case PC_CLASS_AC:
		case PC_CLASS_AC_H:
		case PC_CLASS_AC_B:
			job = PC_JOB_AC;
			break;
		case PC_CLASS_AL:
		case PC_CLASS_AL_H:
		case PC_CLASS_AL_B:
			job = PC_JOB_AL;
			break;
		case PC_CLASS_MC:
		case PC_CLASS_MC_H:
		case PC_CLASS_MC_B:
			job = PC_JOB_MC;
			break;
		case PC_CLASS_TF:
		case PC_CLASS_TF_H:
		case PC_CLASS_TF_B:
			job = PC_JOB_TF;
			break;
		case PC_CLASS_KN:
		case PC_CLASS_KN2:
		case PC_CLASS_KN_H:
		case PC_CLASS_KN2_H:
		case PC_CLASS_KN_B:
		case PC_CLASS_KN2_B:
			job = PC_JOB_KN;
			break;
		case PC_CLASS_PR:
		case PC_CLASS_PR_H:
		case PC_CLASS_PR_B:
			job = PC_JOB_PR;
			break;
		case PC_CLASS_WZ:
		case PC_CLASS_WZ_H:
		case PC_CLASS_WZ_B:
			job = PC_JOB_WZ;
			break;
		case PC_CLASS_BS:
		case PC_CLASS_BS_H:
		case PC_CLASS_BS_B:
			job = PC_JOB_BS;
			break;
		case PC_CLASS_HT:
		case PC_CLASS_HT_H:
		case PC_CLASS_HT_B:
			job = PC_JOB_HT;
			break;
		case PC_CLASS_AS:
		case PC_CLASS_AS_H:
		case PC_CLASS_AS_B:
			job = PC_JOB_AS;
			break;
		case PC_CLASS_CR:
		case PC_CLASS_CR2:
		case PC_CLASS_CR_H:
		case PC_CLASS_CR2_H:
		case PC_CLASS_CR_B:
		case PC_CLASS_CR2_B:
			job = PC_JOB_CR;
			break;
		case PC_CLASS_MO:
		case PC_CLASS_MO_H:
		case PC_CLASS_MO_B:
			job = PC_JOB_MO;
			break;
		case PC_CLASS_SA:
		case PC_CLASS_SA_H:
		case PC_CLASS_SA_B:
			job = PC_JOB_SA;
			break;
		case PC_CLASS_RG:
		case PC_CLASS_RG_H:
		case PC_CLASS_RG_B:
			job = PC_JOB_RG;
			break;
		case PC_CLASS_AM:
		case PC_CLASS_AM_H:
		case PC_CLASS_AM_B:
			job = PC_JOB_AM;
			break;
		case PC_CLASS_BA:
		case PC_CLASS_BA_H:
		case PC_CLASS_BA_B:
			job = PC_JOB_BA;
			break;
		case PC_CLASS_DC:
		case PC_CLASS_DC_H:
		case PC_CLASS_DC_B:
			job = PC_JOB_DC;
			break;
		case PC_CLASS_SNV:
		case PC_CLASS_SNV_B:
			job = PC_JOB_SNV;
			break;
		case PC_CLASS_ESNV:
		case PC_CLASS_ESNV_B:
			job = PC_JOB_ESNV;
			break;
		case PC_CLASS_TK:
			job = PC_JOB_TK;
			break;
		case PC_CLASS_SG:
		case PC_CLASS_SG2:
			job = PC_JOB_SG;
			break;
		case PC_CLASS_SL:
			job = PC_JOB_SL;
			break;
		case PC_CLASS_GS:
			job = PC_JOB_GS;
			break;
		case PC_CLASS_NJ:
			job = PC_JOB_NJ;
			break;
		case PC_CLASS_MB:
			job = PC_JOB_MB;
			break;
		case PC_CLASS_DK:
			job = PC_JOB_DK;
			break;
		case PC_CLASS_DA:
			job = PC_JOB_DA;
			break;
		case PC_CLASS_RK:
		case PC_CLASS_RK2:
		case PC_CLASS_RK3:
		case PC_CLASS_RK4:
		case PC_CLASS_RK5:
		case PC_CLASS_RK6:
		case PC_CLASS_RK_H:
		case PC_CLASS_RK2_H:
		case PC_CLASS_RK3_H:
		case PC_CLASS_RK4_H:
		case PC_CLASS_RK5_H:
		case PC_CLASS_RK6_H:
		case PC_CLASS_RK_B:
		case PC_CLASS_RK2_B:
			job = PC_JOB_RK;
			break;
		case PC_CLASS_WL:
		case PC_CLASS_WL_H:
		case PC_CLASS_WL_B:
			job = PC_JOB_WL;
			break;
		case PC_CLASS_RA:
		case PC_CLASS_RA2:
		case PC_CLASS_RA_H:
		case PC_CLASS_RA2_H:
		case PC_CLASS_RA_B:
		case PC_CLASS_RA2_B:
			job = PC_JOB_RA;
			break;
		case PC_CLASS_AB:
		case PC_CLASS_AB_H:
		case PC_CLASS_AB_B:
			job = PC_JOB_AB;
			break;
		case PC_CLASS_NC:
		case PC_CLASS_NC2:
		case PC_CLASS_NC_H:
		case PC_CLASS_NC2_H:
		case PC_CLASS_NC_B:
		case PC_CLASS_NC2_B:
			job = PC_JOB_NC;
			break;
		case PC_CLASS_GC:
		case PC_CLASS_GC_H:
		case PC_CLASS_GC_B:
			job = PC_JOB_GC;
			break;
		case PC_CLASS_LG:
		case PC_CLASS_LG2:
		case PC_CLASS_LG_H:
		case PC_CLASS_LG2_H:
		case PC_CLASS_LG_B:
		case PC_CLASS_LG2_B:
			job = PC_JOB_LG;
			break;
		case PC_CLASS_SO:
		case PC_CLASS_SO_H:
		case PC_CLASS_SO_B:
			job = PC_JOB_SO;
			break;
		case PC_CLASS_MI:
		case PC_CLASS_MI_H:
		case PC_CLASS_MI_B:
			job = PC_JOB_MI;
			break;
		case PC_CLASS_WA:
		case PC_CLASS_WA_H:
		case PC_CLASS_WA_B:
			job = PC_JOB_WA;
			break;
		case PC_CLASS_SR:
		case PC_CLASS_SR_H:
		case PC_CLASS_SR_B:
			job = PC_JOB_SR;
			break;
		case PC_CLASS_GN:
		case PC_CLASS_GN_H:
		case PC_CLASS_GN_B:
			job = PC_JOB_GN;
			break;
		case PC_CLASS_SC:
		case PC_CLASS_SC_H:
		case PC_CLASS_SC_B:
			job = PC_JOB_SC;
			break;
		case PC_CLASS_KG:
			job = PC_JOB_KG;
			break;
		case PC_CLASS_OB:
			job = PC_JOB_OB;
			break;
		case PC_CLASS_RL:
			job = PC_JOB_RL;
			break;
		case PC_CLASS_SUM:
			job = PC_JOB_SUM;
			break;
	}

	return job;
}

/*==========================================
 * 前職業Class取得
 *------------------------------------------
 */
int pc_get_base_class(int class_, int type)
{
	/* 転生・養子から元の職業へ変換 */
	switch(class_) {
		case PC_CLASS_NV:
		case PC_CLASS_NV_H:
		case PC_CLASS_NV_B:
			class_ = PC_CLASS_NV;
			break;
		case PC_CLASS_SM:
		case PC_CLASS_SM_H:
		case PC_CLASS_SM_B:
			class_ = PC_CLASS_SM;
			break;
		case PC_CLASS_MG:
		case PC_CLASS_MG_H:
		case PC_CLASS_MG_B:
			class_ = PC_CLASS_MG;
			break;
		case PC_CLASS_AC:
		case PC_CLASS_AC_H:
		case PC_CLASS_AC_B:
			class_ = PC_CLASS_AC;
			break;
		case PC_CLASS_AL:
		case PC_CLASS_AL_H:
		case PC_CLASS_AL_B:
			class_ = PC_CLASS_AL;
			break;
		case PC_CLASS_MC:
		case PC_CLASS_MC_H:
		case PC_CLASS_MC_B:
			class_ = PC_CLASS_MC;
			break;
		case PC_CLASS_TF:
		case PC_CLASS_TF_H:
		case PC_CLASS_TF_B:
			class_ = PC_CLASS_TF;
			break;
		case PC_CLASS_KN:
		case PC_CLASS_KN2:
		case PC_CLASS_KN_H:
		case PC_CLASS_KN2_H:
		case PC_CLASS_KN_B:
		case PC_CLASS_KN2_B:
			class_ = PC_CLASS_KN;
			break;
		case PC_CLASS_PR:
		case PC_CLASS_PR_H:
		case PC_CLASS_PR_B:
			class_ = PC_CLASS_PR;
			break;
		case PC_CLASS_WZ:
		case PC_CLASS_WZ_H:
		case PC_CLASS_WZ_B:
			class_ = PC_CLASS_WZ;
			break;
		case PC_CLASS_BS:
		case PC_CLASS_BS_H:
		case PC_CLASS_BS_B:
			class_ = PC_CLASS_BS;
			break;
		case PC_CLASS_HT:
		case PC_CLASS_HT_H:
		case PC_CLASS_HT_B:
			class_ = PC_CLASS_HT;
			break;
		case PC_CLASS_AS:
		case PC_CLASS_AS_H:
		case PC_CLASS_AS_B:
			class_ = PC_CLASS_AS;
			break;
		case PC_CLASS_CR:
		case PC_CLASS_CR2:
		case PC_CLASS_CR_H:
		case PC_CLASS_CR2_H:
		case PC_CLASS_CR_B:
		case PC_CLASS_CR2_B:
			class_ = PC_CLASS_CR;
			break;
		case PC_CLASS_MO:
		case PC_CLASS_MO_H:
		case PC_CLASS_MO_B:
			class_ = PC_CLASS_MO;
			break;
		case PC_CLASS_SA:
		case PC_CLASS_SA_H:
		case PC_CLASS_SA_B:
			class_ = PC_CLASS_SA;
			break;
		case PC_CLASS_RG:
		case PC_CLASS_RG_H:
		case PC_CLASS_RG_B:
			class_ = PC_CLASS_RG;
			break;
		case PC_CLASS_AM:
		case PC_CLASS_AM_H:
		case PC_CLASS_AM_B:
			class_ = PC_CLASS_AM;
			break;
		case PC_CLASS_BA:
		case PC_CLASS_BA_H:
		case PC_CLASS_BA_B:
			class_ = PC_CLASS_BA;
			break;
		case PC_CLASS_DC:
		case PC_CLASS_DC_H:
		case PC_CLASS_DC_B:
			class_ = PC_CLASS_DC;
			break;
		case PC_CLASS_SNV:
		case PC_CLASS_SNV_B:
		case PC_CLASS_ESNV:
		case PC_CLASS_ESNV_B:
			class_ = PC_CLASS_SNV;
			break;
		case PC_CLASS_SG:
		case PC_CLASS_SG2:
			class_ = PC_CLASS_SG;
			break;
		case PC_CLASS_RK:
		case PC_CLASS_RK2:
		case PC_CLASS_RK3:
		case PC_CLASS_RK4:
		case PC_CLASS_RK5:
		case PC_CLASS_RK6:
		case PC_CLASS_RK_H:
		case PC_CLASS_RK2_H:
		case PC_CLASS_RK3_H:
		case PC_CLASS_RK4_H:
		case PC_CLASS_RK5_H:
		case PC_CLASS_RK6_H:
		case PC_CLASS_RK_B:
		case PC_CLASS_RK2_B:
			class_ = PC_CLASS_RK;
			break;
		case PC_CLASS_WL:
		case PC_CLASS_WL_H:
		case PC_CLASS_WL_B:
			class_ = PC_CLASS_WL;
			break;
		case PC_CLASS_RA:
		case PC_CLASS_RA2:
		case PC_CLASS_RA_H:
		case PC_CLASS_RA2_H:
		case PC_CLASS_RA_B:
		case PC_CLASS_RA2_B:
			class_ = PC_CLASS_RA;
			break;
		case PC_CLASS_AB:
		case PC_CLASS_AB_H:
		case PC_CLASS_AB_B:
			class_ = PC_CLASS_AB;
			break;
		case PC_CLASS_NC:
		case PC_CLASS_NC2:
		case PC_CLASS_NC_H:
		case PC_CLASS_NC2_H:
		case PC_CLASS_NC_B:
		case PC_CLASS_NC2_B:
			class_ = PC_CLASS_NC;
			break;
		case PC_CLASS_GC:
		case PC_CLASS_GC_H:
		case PC_CLASS_GC_B:
			class_ = PC_CLASS_GC;
			break;
		case PC_CLASS_LG:
		case PC_CLASS_LG2:
		case PC_CLASS_LG_H:
		case PC_CLASS_LG2_H:
		case PC_CLASS_LG_B:
		case PC_CLASS_LG2_B:
			class_ = PC_CLASS_LG;
			break;
		case PC_CLASS_SO:
		case PC_CLASS_SO_H:
		case PC_CLASS_SO_B:
			class_ = PC_CLASS_SO;
			break;
		case PC_CLASS_MI:
		case PC_CLASS_MI_H:
		case PC_CLASS_MI_B:
			class_ = PC_CLASS_MI;
			break;
		case PC_CLASS_WA:
		case PC_CLASS_WA_H:
		case PC_CLASS_WA_B:
			class_ = PC_CLASS_WA;
			break;
		case PC_CLASS_SR:
		case PC_CLASS_SR_H:
		case PC_CLASS_SR_B:
			class_ = PC_CLASS_SR;
			break;
		case PC_CLASS_GN:
		case PC_CLASS_GN_H:
		case PC_CLASS_GN_B:
			class_ = PC_CLASS_GN;
			break;
		case PC_CLASS_SC:
		case PC_CLASS_SC_H:
		case PC_CLASS_SC_B:
			class_ = PC_CLASS_SC;
			break;
	}

	if(type < 3) {
		/* 3次職から2次職に変換 */
		switch(class_){
			case PC_CLASS_RK:
				class_ = PC_CLASS_KN;
				break;
			case PC_CLASS_WL:
				class_ = PC_CLASS_WZ;
				break;
			case PC_CLASS_RA:
				class_ = PC_CLASS_HT;
				break;
			case PC_CLASS_AB:
				class_ = PC_CLASS_PR;
				break;
			case PC_CLASS_NC:
				class_ = PC_CLASS_BS;
				break;
			case PC_CLASS_GC:
				class_ = PC_CLASS_AS;
				break;
			case PC_CLASS_LG:
				class_ = PC_CLASS_CR;
				break;
			case PC_CLASS_SO:
				class_ = PC_CLASS_SA;
				break;
			case PC_CLASS_MI:
				class_ = PC_CLASS_BA;
				break;
			case PC_CLASS_WA:
				class_ = PC_CLASS_DC;
				break;
			case PC_CLASS_SR:
				class_ = PC_CLASS_MO;
				break;
			case PC_CLASS_GN:
				class_ = PC_CLASS_AM;
				break;
			case PC_CLASS_SC:
				class_ = PC_CLASS_RG;
				break;
		}
	}

	if(type < 2) {
		/* 2次職から1次職に変換 */
		switch(class_){
		case PC_CLASS_KN:
		case PC_CLASS_CR:
			class_ = PC_CLASS_SM;
			break;
		case PC_CLASS_PR:
		case PC_CLASS_MO:
			class_ = PC_CLASS_AL;
			break;
		case PC_CLASS_WZ:
		case PC_CLASS_SA:
			class_ = PC_CLASS_MG;
			break;
		case PC_CLASS_BS:
		case PC_CLASS_AM:
			class_ = PC_CLASS_MC;
			break;
		case PC_CLASS_HT:
		case PC_CLASS_BA:
		case PC_CLASS_DC:
			class_ = PC_CLASS_AC;
			break;
		case PC_CLASS_AS:
		case PC_CLASS_RG:
			class_ = PC_CLASS_TF;
			break;
		case PC_CLASS_SG:
		case PC_CLASS_SL:
			class_ = PC_CLASS_TK;
			break;
		case PC_CLASS_DK:
		case PC_CLASS_DA:
			class_ = PC_CLASS_MB;
			break;
		case PC_CLASS_KG:
		case PC_CLASS_OB:
			class_ = PC_CLASS_NJ;
			break;
		case PC_CLASS_RL:
			class_ = PC_CLASS_GS;
			break;
		}
	}

	return class_;
}

/*==========================================
 * Baseレベルアップ
 *------------------------------------------
 */
static int pc_checkbaselevelup(struct map_session_data *sd)
{
	atn_bignumber next;

	nullpo_retr(0, sd);

	next = pc_nextbaseexp(sd);

	if(sd->status.base_exp >= next && next > 0) {
		// base側レベルアップ処理
		sd->status.base_exp -= next;
		sd->status.base_level++;
		if(sd->status.base_level >= 151 && battle_config.get_status_point_over_lv100)
			sd->status.status_point += (sd->status.base_level+45 ) / 7;
		else if(sd->status.base_level >= 100 && battle_config.get_status_point_over_lv100)
			sd->status.status_point += (sd->status.base_level+129 ) / 10;
		else
			sd->status.status_point += (sd->status.base_level+14) / 5;
		clif_updatestatus(sd,SP_STATUSPOINT);
		clif_updatestatus(sd,SP_BASELEVEL);
		clif_updatestatus(sd,SP_NEXTBASEEXP);

		status_calc_pc_stop_begin(&sd->bl);

		status_calc_pc(sd,0);
		pc_heal(sd,sd->status.max_hp,sd->status.max_sp);

		// スパノビはキリエ、イムポ、マニピ、グロ、サフラがかかる
		if(sd->s_class.job == PC_JOB_SNV || sd->s_class.job == PC_JOB_ESNV) {
			status_change_start(&sd->bl,SC_KYRIE,10,0,0,0,120000,0);
			status_change_start(&sd->bl,SC_IMPOSITIO,5,0,0,0,120000,0);
			status_change_start(&sd->bl,SC_MAGNIFICAT,5,0,0,0,120000,0);
			status_change_start(&sd->bl,SC_GLORIA,5,0,0,0,120000,0);
			status_change_start(&sd->bl,SC_SUFFRAGIUM,3,0,0,0,120000,0);
			clif_misceffect(&sd->bl,7);	// スパノビ天使
		}
		else if(sd->s_class.job >= PC_JOB_TK && sd->s_class.job <= PC_JOB_SL) {
			status_change_start(&sd->bl,SC_BLESSING,10,0,0,0,600000,0);
			status_change_start(&sd->bl,SC_INCREASEAGI,10,0,0,0,600000,0);
			clif_misceffect(&sd->bl,9);	// テコン系天使
		}
		else {
			clif_misceffect(&sd->bl,0);
		}

		status_calc_pc_stop_end(&sd->bl);

		// レベルアップしたのでパーティー情報を更新する（公平範囲チェック）
		party_send_movemap(sd);

		achieve_update_content(sd, ACH_LEVEL, SP_BASELEVEL, sd->status.base_level);
		return 1;
	}

	return 0;
}

/*==========================================
 * Jobレベルアップ
 *------------------------------------------
 */
static int pc_checkjoblevelup(struct map_session_data *sd)
{
	atn_bignumber next;

	nullpo_retr(0, sd);

	next = pc_nextjobexp(sd);

	if(sd->status.job_exp >= next && next > 0) {
		// job側レベルアップ処理
		sd->status.job_exp -= next;
		sd->status.job_level++;
		clif_updatestatus(sd,SP_JOBLEVEL);
		clif_updatestatus(sd,SP_NEXTJOBEXP);
		sd->status.skill_point++;
		clif_updatestatus(sd,SP_SKILLPOINT);
		status_calc_pc(sd,0);
		if(sd->status.class_ == PC_CLASS_SNV || sd->status.class_ == PC_CLASS_SNV_B || sd->status.class_ == PC_CLASS_ESNV || sd->status.class_ == PC_CLASS_ESNV_B)
			clif_misceffect(&sd->bl,8);
		else
			clif_misceffect(&sd->bl,1);
		achieve_update_content(sd, ACH_LEVEL, SP_JOBLEVEL, sd->status.job_level);
		return 1;
	}

	return 0;
}

/*==========================================
 * 経験値取得
 *------------------------------------------
 */
int pc_gainexp(struct map_session_data *sd, struct mob_data *md, atn_bignumber base_exp, atn_bignumber job_exp, short quest)
{
	int base_rate = 100;
	int job_rate = 100;

	nullpo_retr(0, sd);

	if (sd->bl.prev == NULL || unit_isdead(&sd->bl))
		return 0;

	if (md) {
		int race_id = status_get_race(&md->bl);

		base_exp = base_exp * (100 + sd->exp_rate[race_id]) / 100;
		job_exp  = job_exp  * (100 + sd->job_rate[race_id]) / 100;

		if (md->sc.data[SC_RICHMANKIM].timer != -1) {
			base_exp = base_exp * (125 + md->sc.data[SC_RICHMANKIM].val1 * 11) / 100;
			job_exp  = job_exp  * (125 + md->sc.data[SC_RICHMANKIM].val1 * 11) / 100;
		}
	}
	if (sd->sc.data[SC_MEAL_INCEXP].timer != -1) {
		base_exp = base_exp * sd->sc.data[SC_MEAL_INCEXP].val1 / 100;
	}
	if (sd->sc.data[SC_MEAL_INCJOB].timer != -1) {
		job_exp  = job_exp  * sd->sc.data[SC_MEAL_INCJOB].val1 / 100;
	}
	if (sd->sc.data[SC_COMBATHAN].timer != -1) {
		base_rate += sd->sc.data[SC_COMBATHAN].val1;
		job_rate  += sd->sc.data[SC_COMBATHAN].val1;
	}
	if (sd->sc.data[SC_JOB_COMBATHAN].timer != -1) {
		job_rate  += sd->sc.data[SC_JOB_COMBATHAN].val1;
	}
	if (sd->sc.data[SC_SUPPORT_EXP].timer != -1) {
		base_rate += sd->sc.data[SC_SUPPORT_EXP].val1;
		job_rate  += sd->sc.data[SC_SUPPORT_EXP].val1;
	}
	if (sd->sc.data[SC_JP_EVENT04].timer != -1 && status_get_race(&md->bl) == RCT_FISH) {
		base_rate += sd->sc.data[SC_JP_EVENT04].val1;
		job_rate  += sd->sc.data[SC_JP_EVENT04].val1;
	}

	if (base_rate != 100)
		base_exp = base_exp * base_rate / 100;
	if (job_rate != 100)
		job_exp  = job_exp  * job_rate / 100;

	// マーダラーボーナス
	if(battle_config.pk_murderer_point > 0) {
		if(ranking_get_point(sd,RK_PK) >= battle_config.pk_murderer_point) {
			base_exp *= 2;
			job_exp  *= 2;
		}
	}

	if (sd->status.guild_id > 0) {	// ギルドに上納
		base_exp -= guild_payexp(sd, base_exp);
		if (base_exp < 0)
			base_exp = 0;
	}

	if (battle_config.disp_experience && (base_exp || job_exp)) {
#if PACKETVER < 20091104
		char output[128];
		int bexp = (base_exp > 0x7fffffff)? 0x7fffffff: (int)base_exp;
		int jexp = (job_exp  > 0x7fffffff)? 0x7fffffff: (int)job_exp;
		snprintf(output, sizeof output, msg_txt(131), bexp, jexp);
		clif_disp_onlyself(sd->fd, output);
#else
		if(base_exp) {
#if PACKETVER < 20170830
			clif_dispexp(sd,(base_exp > 0x7fffffff)? 0x7fffffff: base_exp,1,quest);
#else
			clif_dispexp(sd,base_exp,1,quest);
#endif
		}
		if(job_exp) {
#if PACKETVER < 20170830
			clif_dispexp(sd,(job_exp > 0x7fffffff)? 0x7fffffff: job_exp,2,quest);
#else
			clif_dispexp(sd,job_exp,2,quest);
#endif
		}
#endif
	}

	//------------- Base ----------------
	if (base_exp > 0) {
		atn_bignumber next = pc_nextbaseexp(sd);
		int per = battle_config.next_exp_limit;

		if (next > 0) {
			if (per <= 0) {
				// 本鯖仕様の取得経験値上限
				atn_bignumber limit_exp = next * 2 - sd->status.base_exp - 1;
				if(base_exp > limit_exp)
					base_exp = limit_exp;
			}
			while(next > 0 && base_exp + sd->status.base_exp >= next) {	// LvUP
				if (battle_config.next_exp_limit > 0) {
					int rate = (int)(100 - (atn_bignumber)sd->status.base_exp * 100 / next);
					if (per < rate)
						break;
					per -= rate;
				}
				base_exp = base_exp + sd->status.base_exp - next;
				sd->status.base_exp = next;
				pc_checkbaselevelup(sd);
				next = pc_nextbaseexp(sd);
			}
		}
		if (next > 0 && battle_config.next_exp_limit > 0 && (base_exp * 100 / next) > per)
			sd->status.base_exp = next * per / 100;
#ifndef PRE_RENEWAL
		else if (next == 0 && base_exp + sd->status.base_exp > 99999999)
			sd->status.base_exp = 99999999;
#endif
		else
			sd->status.base_exp += base_exp;

		if (sd->status.base_exp < 0)
			sd->status.base_exp = 0;
		pc_checkbaselevelup(sd);
		clif_updatestatus(sd, SP_BASEEXP);
	}

	//------------- Job ----------------
	if (job_exp > 0) {
		atn_bignumber next = pc_nextjobexp(sd);
		int per = battle_config.next_exp_limit;

		if (next > 0) {
			if (per <= 0) {
				// 本鯖仕様の取得経験値上限
				atn_bignumber limit_exp = next * 2 - sd->status.job_exp - 1;
				if (job_exp > limit_exp)
					job_exp = limit_exp;
			}
			while(next > 0 && job_exp + sd->status.job_exp >= next) {	// LvUP
				if (battle_config.next_exp_limit > 0) {
					int rate = (int)(100 - (atn_bignumber)sd->status.job_exp * 100 / next);
					if (per < rate)
						break;
					per -= rate;
				}
				job_exp = job_exp + sd->status.job_exp - next;
				sd->status.job_exp = next;
				pc_checkjoblevelup(sd);
				next = pc_nextjobexp(sd);
			}
		}
		if (next > 0 && battle_config.next_exp_limit > 0 && (job_exp * 100 / next) > per)
			sd->status.job_exp = next * per / 100;
#ifndef PRE_RENEWAL
		else if (next == 0 && job_exp + sd->status.job_exp > 99999999)
			sd->status.job_exp = 99999999;
#endif
		else
			sd->status.job_exp += job_exp;

		if (sd->status.job_exp < 0)
			sd->status.job_exp = 0;
		pc_checkjoblevelup(sd);
		clif_updatestatus(sd, SP_JOBEXP);
	}

	return 0;
}

/*==========================================
 * base level側必要経験値計算
 *------------------------------------------
 */
atn_bignumber pc_nextbaseexp(struct map_session_data *sd)
{
	int table;

	nullpo_retr(0, sd);

	if(sd->status.base_level >= MAX_LEVEL || sd->status.base_level <= 0)
		return 0;

	switch(sd->status.class_) {
		case PC_CLASS_NV:	// ノービス
		case PC_CLASS_NV_B:	// 養子ノービス
			table = 0;
			break;
		case PC_CLASS_SM:	// ソードマン
		case PC_CLASS_MG:	// マジシャン
		case PC_CLASS_AC:	// アーチャー
		case PC_CLASS_AL:	// アコライト
		case PC_CLASS_MC:	// マーチャント
		case PC_CLASS_TF:	// シーフ
		case PC_CLASS_SM_B:	// 養子ソードマン
		case PC_CLASS_MG_B:	// 養子マジシャン
		case PC_CLASS_AC_B:	// 養子アーチャー
		case PC_CLASS_AL_B:	// 養子アコライト
		case PC_CLASS_MC_B:	// 養子マーチャント
		case PC_CLASS_TF_B:	// 養子シーフ
		case PC_CLASS_TK:	// テコンキッド
		case PC_CLASS_MB:	// キョンシー
			table = 1;
			break;
		case PC_CLASS_KN:	// ナイト
		case PC_CLASS_PR:	// プリースト
		case PC_CLASS_WZ:	// ウィザード
		case PC_CLASS_BS:	// ブラックスミス
		case PC_CLASS_HT:	// ハンター
		case PC_CLASS_AS:	// アサシン
		case PC_CLASS_KN2:	// ナイト(騎乗)
		case PC_CLASS_CR:	// クルセイダー
		case PC_CLASS_MO:	// モンク
		case PC_CLASS_SA:	// セージ
		case PC_CLASS_RG:	// ローグ
		case PC_CLASS_AM:	// アルケミスト
		case PC_CLASS_BA:	// バード
		case PC_CLASS_DC:	// ダンサー
		case PC_CLASS_CR2:	// クルセイダー(騎乗)
		case PC_CLASS_KN_B:	// 養子ナイト
		case PC_CLASS_PR_B:	// 養子プリースト
		case PC_CLASS_WZ_B:	// 養子ウィザード
		case PC_CLASS_BS_B:	// 養子ブラックスミス
		case PC_CLASS_HT_B:	// 養子ハンター
		case PC_CLASS_AS_B:	// 養子アサシン
		case PC_CLASS_KN2_B:	// 養子ナイト(騎乗)
		case PC_CLASS_CR_B:	// 養子クルセイダー
		case PC_CLASS_MO_B:	// 養子モンク
		case PC_CLASS_SA_B:	// 養子セージ
		case PC_CLASS_RG_B:	// 養子ローグ
		case PC_CLASS_AM_B:	// 養子アルケミスト
		case PC_CLASS_BA_B:	// 養子バード
		case PC_CLASS_DC_B:	// 養子ダンサー
		case PC_CLASS_CR2_B:	// 養子クルセイダー(騎乗)
		case PC_CLASS_SG:	// 拳聖
		case PC_CLASS_SG2:	// 拳聖(融合)
		case PC_CLASS_SL:	// ソウルリンカー
		case PC_CLASS_DK:	// デスナイト
		case PC_CLASS_DA:	// ダークコレクター
			table = 2;
			break;
		case PC_CLASS_SNV:	// スーパーノービス
		case PC_CLASS_GS:	// ガンスリンガー
		case PC_CLASS_NJ:	// 忍者
		case PC_CLASS_SNV_B:	// 養子スーパーノービス
			table = 3;
			break;
		case PC_CLASS_NV_H:	// 転生ノービス
			table = 4;
			break;
		case PC_CLASS_SM_H:	// 転生ソードマン
		case PC_CLASS_MG_H:	// 転生マジシャン
		case PC_CLASS_AC_H:	// 転生アーチャー
		case PC_CLASS_AL_H:	// 転生アコライト
		case PC_CLASS_MC_H:	// 転生マーチャント
		case PC_CLASS_TF_H:	// 転生シーフ
			table = 5;
			break;
		case PC_CLASS_KN_H:	// ロードナイト
		case PC_CLASS_PR_H:	// ハイプリースト
		case PC_CLASS_WZ_H:	// ハイウィザード
		case PC_CLASS_BS_H:	// ホワイトスミス
		case PC_CLASS_HT_H:	// スナイパー
		case PC_CLASS_AS_H:	// アサシンクロス
		case PC_CLASS_KN2_H:	// ロードナイト(騎乗)
		case PC_CLASS_CR_H:	// パラディン
		case PC_CLASS_MO_H:	// チャンピオン
		case PC_CLASS_SA_H:	// プロフェッサー
		case PC_CLASS_RG_H:	// チェイサー
		case PC_CLASS_AM_H:	// クリエイター
		case PC_CLASS_BA_H:	// クラウン
		case PC_CLASS_DC_H:	// ジプシー
		case PC_CLASS_CR2_H:	// パラディン(騎乗)
			table = 6;
			break;
		case PC_CLASS_RK:	// ルーンナイト
		case PC_CLASS_WL:	// ウォーロック
		case PC_CLASS_RA:	// レンジャー
		case PC_CLASS_AB:	// アークビショップ
		case PC_CLASS_NC:	// メカニック
		case PC_CLASS_GC:	// ギロチンクロス
		case PC_CLASS_LG:	// ロイヤルガード
		case PC_CLASS_SO:	// ソーサラー
		case PC_CLASS_MI:	// ミンストレル
		case PC_CLASS_WA:	// ワンダラー
		case PC_CLASS_SR:	// 修羅
		case PC_CLASS_GN:	// ジェネティック
		case PC_CLASS_SC:	// シャドウチェイサー
		case PC_CLASS_RK2:	// ルーンナイト(騎乗)
		case PC_CLASS_LG2:	// ロイヤルガード(騎乗)
		case PC_CLASS_RA2:	// レンジャー(騎乗)
		case PC_CLASS_NC2:	// メカニック(騎乗)
		case PC_CLASS_RK3:	// ルーンナイト(騎乗)
		case PC_CLASS_RK4:	// ルーンナイト(騎乗)
		case PC_CLASS_RK5:	// ルーンナイト(騎乗)
		case PC_CLASS_RK6:	// ルーンナイト(騎乗)
		case PC_CLASS_RK_B:	// 養子ルーンナイト
		case PC_CLASS_WL_B:	// 養子ウォーロック
		case PC_CLASS_RA_B:	// 養子レンジャー
		case PC_CLASS_AB_B:	// 養子アークビショップ
		case PC_CLASS_NC_B:	// 養子メカニック
		case PC_CLASS_GC_B:	// 養子ギロチンクロス
		case PC_CLASS_LG_B:	// 養子ロイヤルガード
		case PC_CLASS_SO_B:	// 養子ソーサラー
		case PC_CLASS_MI_B:	// 養子ミンストレル
		case PC_CLASS_WA_B:	// 養子ワンダラー
		case PC_CLASS_SR_B:	// 養子修羅
		case PC_CLASS_GN_B:	// 養子ジェネティック
		case PC_CLASS_SC_B:	// 養子シャドウチェイサー
		case PC_CLASS_RK2_B:	// 養子ルーンナイト(騎乗)
		case PC_CLASS_LG2_B:	// 養子ロイヤルガード(騎乗)
		case PC_CLASS_RA2_B:	// 養子レンジャー(騎乗)
		case PC_CLASS_NC2_B:	// 養子メカニック(騎乗)
		case PC_CLASS_KG:	// 影狼
		case PC_CLASS_OB:	// 朧
		case PC_CLASS_RL:	// リベリオン
			table = 7;
			break;
		case PC_CLASS_RK_H:	// 転生ルーンナイト
		case PC_CLASS_WL_H:	// 転生ウォーロック
		case PC_CLASS_RA_H:	// 転生レンジャー
		case PC_CLASS_AB_H:	// 転生アークビショップ
		case PC_CLASS_NC_H:	// 転生メカニック
		case PC_CLASS_GC_H:	// 転生ギロチンクロス
		case PC_CLASS_LG_H:	// 転生ロイヤルガード
		case PC_CLASS_SO_H:	// 転生ソーサラー
		case PC_CLASS_MI_H:	// 転生ミンストレル
		case PC_CLASS_WA_H:	// 転生ワンダラー
		case PC_CLASS_SR_H:	// 転生修羅
		case PC_CLASS_GN_H:	// 転生ジェネティック
		case PC_CLASS_SC_H:	// 転生シャドウチェイサー
		case PC_CLASS_RK2_H:	// 転生ルーンナイト(騎乗)
		case PC_CLASS_LG2_H:	// 転生ロイヤルガード(騎乗)
		case PC_CLASS_RA2_H:	// 転生レンジャー(騎乗)
		case PC_CLASS_NC2_H:	// 転生メカニック(騎乗)
		case PC_CLASS_RK3_H:	// 転生ルーンナイト(騎乗)
		case PC_CLASS_RK4_H:	// 転生ルーンナイト(騎乗)
		case PC_CLASS_RK5_H:	// 転生ルーンナイト(騎乗)
		case PC_CLASS_RK6_H:	// 転生ルーンナイト(騎乗)
		case PC_CLASS_SUM:	// サモナー
		case PC_CLASS_SUM_B:	// 養子サモナー
			table = 8;
			break;
		case PC_CLASS_ESNV:	// 拡張スーパーノービス
		case PC_CLASS_ESNV_B:	// 養子拡張スーパーノービス
			table = 9;
			break;
		default:	// それ以外
			table = 1;
			break;
	}

	return exp_table[table][sd->status.base_level-1];
}

/*==========================================
 * job level側必要経験値計算
 *------------------------------------------
 */
atn_bignumber pc_nextjobexp(struct map_session_data *sd)
{
	int table;

	nullpo_retr(0, sd);

	if(sd->status.job_level >= MAX_LEVEL || sd->status.job_level <= 0)
		return 0;

	switch(sd->status.class_) {
		case PC_CLASS_NV:	// ノービス
		case PC_CLASS_NV_B:	// 養子ノービス
			table = 10;
			break;
		case PC_CLASS_SM:	// ソードマン
		case PC_CLASS_MG:	// マジシャン
		case PC_CLASS_AC:	// アーチャー
		case PC_CLASS_AL:	// アコライト
		case PC_CLASS_MC:	// マーチャント
		case PC_CLASS_TF:	// シーフ
		case PC_CLASS_SM_B:	// 養子ソードマン
		case PC_CLASS_MG_B:	// 養子マジシャン
		case PC_CLASS_AC_B:	// 養子アーチャー
		case PC_CLASS_AL_B:	// 養子アコライト
		case PC_CLASS_MC_B:	// 養子マーチャント
		case PC_CLASS_TF_B:	// 養子シーフ
		case PC_CLASS_TK:	// テコンキッド
		case PC_CLASS_MB:	// キョンシー
			table = 11;
			break;
		case PC_CLASS_KN:	// ナイト
		case PC_CLASS_PR:	// プリースト
		case PC_CLASS_WZ:	// ウィザード
		case PC_CLASS_BS:	// ブラックスミス
		case PC_CLASS_HT:	// ハンター
		case PC_CLASS_AS:	// アサシン
		case PC_CLASS_KN2:	// ナイト(騎乗)
		case PC_CLASS_CR:	// クルセイダー
		case PC_CLASS_MO:	// モンク
		case PC_CLASS_SA:	// セージ
		case PC_CLASS_RG:	// ローグ
		case PC_CLASS_AM:	// アルケミスト
		case PC_CLASS_BA:	// バード
		case PC_CLASS_DC:	// ダンサー
		case PC_CLASS_CR2:	// クルセイダー(騎乗)
		case PC_CLASS_KN_B:	// 養子ナイト
		case PC_CLASS_PR_B:	// 養子プリースト
		case PC_CLASS_WZ_B:	// 養子ウィザード
		case PC_CLASS_BS_B:	// 養子ブラックスミス
		case PC_CLASS_HT_B:	// 養子ハンター
		case PC_CLASS_AS_B:	// 養子アサシン
		case PC_CLASS_KN2_B:	// 養子ナイト(騎乗)
		case PC_CLASS_CR_B:	// 養子クルセイダー
		case PC_CLASS_MO_B:	// 養子モンク
		case PC_CLASS_SA_B:	// 養子セージ
		case PC_CLASS_RG_B:	// 養子ローグ
		case PC_CLASS_AM_B:	// 養子アルケミスト
		case PC_CLASS_BA_B:	// 養子バード
		case PC_CLASS_DC_B:	// 養子ダンサー
		case PC_CLASS_CR2_B:	// 養子クルセイダー(騎乗)
		case PC_CLASS_SL:	// ソウルリンカー
		case PC_CLASS_DK:	// デスナイト
		case PC_CLASS_DA:	// ダークコレクター
			table = 12;
			break;
		case PC_CLASS_SNV:	// スーパーノービス
		case PC_CLASS_SNV_B:	// 養子スーパーノービス
			table = 13;
			break;
		case PC_CLASS_NV_H:	// 転生ノービス
			table = 14;
			break;
		case PC_CLASS_SM_H:	// 転生ソードマン
		case PC_CLASS_MG_H:	// 転生マジシャン
		case PC_CLASS_AC_H:	// 転生アーチャー
		case PC_CLASS_AL_H:	// 転生アコライト
		case PC_CLASS_MC_H:	// 転生マーチャント
		case PC_CLASS_TF_H:	// 転生シーフ
			table = 15;
			break;
		case PC_CLASS_KN_H:	// ロードナイト
		case PC_CLASS_PR_H:	// ハイプリースト
		case PC_CLASS_WZ_H:	// ハイウィザード
		case PC_CLASS_BS_H:	// ホワイトスミス
		case PC_CLASS_HT_H:	// スナイパー
		case PC_CLASS_AS_H:	// アサシンクロス
		case PC_CLASS_KN2_H:	// ロードナイト(騎乗)
		case PC_CLASS_CR_H:	// パラディン
		case PC_CLASS_MO_H:	// チャンピオン
		case PC_CLASS_SA_H:	// プロフェッサー
		case PC_CLASS_RG_H:	// チェイサー
		case PC_CLASS_AM_H:	// クリエイター
		case PC_CLASS_BA_H:	// クラウン
		case PC_CLASS_DC_H:	// ジプシー
		case PC_CLASS_CR2_H:	// パラディン(騎乗)
			table = 16;
			break;
		case PC_CLASS_SG:	// 拳聖
		case PC_CLASS_SG2:	// 拳聖(融合)
			table = 17;
			break;
		case PC_CLASS_GS:	// ガンスリンガー
		case PC_CLASS_NJ:	// 忍者
			table = 18;
			break;
		case PC_CLASS_RK:	// ルーンナイト
		case PC_CLASS_WL:	// ウォーロック
		case PC_CLASS_RA:	// レンジャー
		case PC_CLASS_AB:	// アークビショップ
		case PC_CLASS_NC:	// メカニック
		case PC_CLASS_GC:	// ギロチンクロス
		case PC_CLASS_LG:	// ロイヤルガード
		case PC_CLASS_SO:	// ソーサラー
		case PC_CLASS_MI:	// ミンストレル
		case PC_CLASS_WA:	// ワンダラー
		case PC_CLASS_SR:	// 修羅
		case PC_CLASS_GN:	// ジェネティック
		case PC_CLASS_SC:	// シャドウチェイサー
		case PC_CLASS_RK2:	// ルーンナイト(騎乗)
		case PC_CLASS_LG2:	// ロイヤルガード(騎乗)
		case PC_CLASS_RA2:	// レンジャー(騎乗)
		case PC_CLASS_NC2:	// メカニック(騎乗)
		case PC_CLASS_RK3:	// ルーンナイト(騎乗)
		case PC_CLASS_RK4:	// ルーンナイト(騎乗)
		case PC_CLASS_RK5:	// ルーンナイト(騎乗)
		case PC_CLASS_RK6:	// ルーンナイト(騎乗)
		case PC_CLASS_RK_B:	// 養子ルーンナイト
		case PC_CLASS_WL_B:	// 養子ウォーロック
		case PC_CLASS_RA_B:	// 養子レンジャー
		case PC_CLASS_AB_B:	// 養子アークビショップ
		case PC_CLASS_NC_B:	// 養子メカニック
		case PC_CLASS_GC_B:	// 養子ギロチンクロス
		case PC_CLASS_LG_B:	// 養子ロイヤルガード
		case PC_CLASS_SO_B:	// 養子ソーサラー
		case PC_CLASS_MI_B:	// 養子ミンストレル
		case PC_CLASS_WA_B:	// 養子ワンダラー
		case PC_CLASS_SR_B:	// 養子修羅
		case PC_CLASS_GN_B:	// 養子ジェネティック
		case PC_CLASS_SC_B:	// 養子シャドウチェイサー
		case PC_CLASS_RK2_B:	// 養子ルーンナイト(騎乗)
		case PC_CLASS_LG2_B:	// 養子ロイヤルガード(騎乗)
		case PC_CLASS_RA2_B:	// 養子レンジャー(騎乗)
		case PC_CLASS_NC2_B:	// 養子メカニック(騎乗)
		case PC_CLASS_KG:	// 影狼
		case PC_CLASS_OB:	// 朧
		case PC_CLASS_RL:	// リベリオン
			table = 19;
			break;
		case PC_CLASS_RK_H:	// 転生ルーンナイト
		case PC_CLASS_WL_H:	// 転生ウォーロック
		case PC_CLASS_RA_H:	// 転生レンジャー
		case PC_CLASS_AB_H:	// 転生アークビショップ
		case PC_CLASS_NC_H:	// 転生メカニック
		case PC_CLASS_GC_H:	// 転生ギロチンクロス
		case PC_CLASS_LG_H:	// 転生ロイヤルガード
		case PC_CLASS_SO_H:	// 転生ソーサラー
		case PC_CLASS_MI_H:	// 転生ミンストレル
		case PC_CLASS_WA_H:	// 転生ワンダラー
		case PC_CLASS_SR_H:	// 転生修羅
		case PC_CLASS_GN_H:	// 転生ジェネティック
		case PC_CLASS_SC_H:	// 転生シャドウチェイサー
		case PC_CLASS_RK2_H:	// 転生ルーンナイト(騎乗)
		case PC_CLASS_LG2_H:	// 転生ロイヤルガード(騎乗)
		case PC_CLASS_RA2_H:	// 転生レンジャー(騎乗)
		case PC_CLASS_NC2_H:	// 転生メカニック(騎乗)
		case PC_CLASS_RK3_H:	// 転生ルーンナイト(騎乗)
		case PC_CLASS_RK4_H:	// 転生ルーンナイト(騎乗)
		case PC_CLASS_RK5_H:	// 転生ルーンナイト(騎乗)
		case PC_CLASS_RK6_H:	// 転生ルーンナイト(騎乗)
		case PC_CLASS_ESNV:	// 拡張スーパーノービス
		case PC_CLASS_ESNV_B:	// 養子拡張スーパーノービス
			table = 20;
			break;
		case PC_CLASS_SUM:	// サモナー
		case PC_CLASS_SUM_B:	// 養子サモナー
			table = 21;
			break;
		default:
			table = 11;
			break;
	}

	return exp_table[table][sd->status.job_level-1];
}

/*==========================================
 * 必要ステータスポイント計算
 *------------------------------------------
 */
int pc_need_status_point(struct map_session_data *sd,int type)
{
	int val = -1;

	nullpo_retr(-1, sd);

	switch(type) {
		case SP_STR: val = sd->status.str;  break;
		case SP_AGI: val = sd->status.agi;  break;
		case SP_VIT: val = sd->status.vit;  break;
		case SP_INT: val = sd->status.int_; break;
		case SP_DEX: val = sd->status.dex;  break;
		case SP_LUK: val = sd->status.luk;  break;
	}

	if(pc_is3rdclass(sd)) {
		if(pc_isbaby(sd) && val >= battle_config.third_baby_status_max)
			return 0;
		else if(val >= battle_config.third_status_max)
			return 0;
	} else if(sd->status.class_ == PC_CLASS_ESNV) {
		if(pc_isbaby(sd) && val >= battle_config.esnv_baby_status_max)
			return 0;
		else if(val >= battle_config.esnv_status_max)
			return 0;
	} else if(sd->status.class_ == PC_CLASS_KG || sd->status.class_ == PC_CLASS_OB) {
			if(val >= battle_config.ko_status_max)
				return 0;
	} else if(sd->status.class_ == PC_CLASS_RL) {
			if(val >= battle_config.rl_status_max)
				return 0;
	} else if(sd->status.class_ == PC_CLASS_SUM) {
			if(val >= battle_config.sum_status_max)
				return 0;
	} else {
		if(pc_isbaby(sd) && val >= battle_config.baby_status_max)
			return 0;
		else if(val >= battle_config.max_parameter)
			return 0;
	}

	if(val < 0)
		val = -1;
	else if(val < 100)
		val = (val + 9) / 10 + 1;
	else if(battle_config.new_statusup_calc)
		val = 16 + (val / 5 - 20) * 4;
	else
		val = (val + 9) / 10 + 1;

	return val;
}

/*==========================================
 * 能力値成長
 *------------------------------------------
 */
void pc_statusup(struct map_session_data *sd, unsigned short type, int num)
{
	int need, status_point;
	int val = 0, max = 0;
	short *param = NULL;

	nullpo_retv(sd);

	if(type < SP_STR || type > SP_LUK || num <= 0) {
		clif_statusupack(sd,type,0,0);
		return;
	}

	need = pc_need_status_point(sd,type);
	if(need < 0 || need > sd->status.status_point) {
		clif_statusupack(sd,type,0,0);
		return;
	}

	switch(type) {
		case SP_STR:
			param = &sd->status.str;
			break;
		case SP_AGI:
			param = &sd->status.agi;
			break;
		case SP_VIT:
			param = &sd->status.vit;
			break;
		case SP_INT:
			param = &sd->status.int_;
			break;
		case SP_DEX:
			param = &sd->status.dex;
			break;
		case SP_LUK:
			param = &sd->status.luk;
			break;
		default:
			clif_statusupack(sd,type,0,0);
			return;
	}

	if(pc_is3rdclass(sd) && pc_isbaby(sd))
		max = battle_config.third_baby_status_max;
	else if(pc_is3rdclass(sd))
		max = battle_config.third_status_max;
	else if(sd->status.class_ == PC_CLASS_ESNV && pc_isbaby(sd))
		max = battle_config.esnv_baby_status_max;
	else if(sd->status.class_ == PC_CLASS_ESNV)
		max = battle_config.esnv_status_max;
	else if(sd->status.class_ == PC_CLASS_KG || sd->status.class_ == PC_CLASS_OB)
		max = battle_config.ko_status_max;
	else if(sd->status.class_ == PC_CLASS_RL)
		max = battle_config.rl_status_max;
	else if(sd->status.class_ == PC_CLASS_SUM)
		max = battle_config.sum_status_max;
	else if(pc_isbaby(sd))
		max = battle_config.baby_status_max;
	else
		max = battle_config.max_parameter;

	if((*param) >= max) {
		clif_statusupack(sd,type,0,0);
		return;
	}

	val = (*param);
	if(max > val + num)
		max = val + num;

	status_point = sd->status.status_point;

	while(max > val && status_point > 0) {
		int point;
		if(val < 100)
			point = (val + 9) / 10 + 1;
		else if(battle_config.new_statusup_calc)
			point = 16 + (val / 5 - 20) * 4;
		else
			point = (val + 9) / 10 + 1;
		if(status_point < point)
			break;
		val++;
		status_point -= point;
	}

	(*param) = val;
	sd->status.status_point = status_point;
	if(need != pc_need_status_point(sd,type)) {
		clif_updatestatus(sd,type-SP_STR+SP_USTR);
	}

	clif_updatestatus(sd,SP_STATUSPOINT);
	clif_updatestatus(sd,type);
	status_calc_pc(sd,0);
	clif_statusupack(sd,type,1,val);

	achieve_update_content(sd, ACH_STATUS, type, val);

	return;
}

/*==========================================
 * 能力値成長
 *------------------------------------------
 */
int pc_statusup2(struct map_session_data *sd,int type,int val)
{
	nullpo_retr(0, sd);

	switch(type) {
		case SP_STR:
			if(sd->status.str + val >= battle_config.max_parameter)
				val = battle_config.max_parameter;
			else if(sd->status.str + val < 1)
				val = 1;
			else
				val += sd->status.str;
			sd->status.str = val;
			break;
		case SP_AGI:
			if(sd->status.agi + val >= battle_config.max_parameter)
				val = battle_config.max_parameter;
			else if(sd->status.agi + val < 1)
				val = 1;
			else
				val += sd->status.agi;
			sd->status.agi = val;
			break;
		case SP_VIT:
			if(sd->status.vit + val >= battle_config.max_parameter)
				val = battle_config.max_parameter;
			else if(sd->status.vit + val < 1)
				val = 1;
			else
				val += sd->status.vit;
			sd->status.vit = val;
			break;
		case SP_INT:
			if(sd->status.int_ + val >= battle_config.max_parameter)
				val = battle_config.max_parameter;
			else if(sd->status.int_ + val < 1)
				val = 1;
			else
				val += sd->status.int_;
			sd->status.int_ = val;
			break;
		case SP_DEX:
			if(sd->status.dex + val >= battle_config.max_parameter)
				val = battle_config.max_parameter;
			else if(sd->status.dex + val < 1)
				val = 1;
			else
				val += sd->status.dex;
			sd->status.dex = val;
			break;
		case SP_LUK:
			if(sd->status.luk + val >= battle_config.max_parameter)
				val = battle_config.max_parameter;
			else if(sd->status.luk + val < 1)
				val = 1;
			else
				val = sd->status.luk + val;
			sd->status.luk = val;
			break;
		default:
			clif_statusupack(sd,type,0,0);
			return 1;
	}
	clif_updatestatus(sd,type-SP_STR+SP_USTR);
	clif_updatestatus(sd,type);
	status_calc_pc(sd,0);
	clif_statusupack(sd,type,1,val);

	achieve_update_content(sd, ACH_STATUS, type, val);

	return 0;
}

/*==========================================
 * スキル取得可能かどうか
 *------------------------------------------
 */
static int pc_check_skillup(struct map_session_data *sd,int skill_num)
{
	int skill_point,up_level;
	struct skill_tree_entry *st;

	nullpo_retr(0, sd);

	st = pc_search_skilltree(&sd->s_class, skill_num);
	if(st == NULL)
		return 0;

	skill_point = pc_calc_skillpoint(sd);

	if(skill_point < 9 || pc_isdoram(sd))
		up_level = 0;
	else if(sd->status.skill_point >= sd->status.job_level && skill_point < 58 && (pc_is2ndclass(sd) || pc_is3rdclass(sd)))
		up_level = 1;
	else if(pc_is2ndclass(sd))
		up_level = 2;
	else
		up_level = 3;

	return (st->class_level <= up_level);
}

/*==========================================
 * スキルポイント割り振り
 *------------------------------------------
 */
void pc_skillup(struct map_session_data *sd, int skill_num)
{
	nullpo_retv(sd);

	if(skill_num < 0 || skill_num >= MAX_PCSKILL)
		return;

	if(battle_config.skillup_type && !pc_check_skillup(sd,skill_num))
	{
		clif_skillup(sd,skill_num);
		clif_updatestatus(sd,SP_SKILLPOINT);
		clif_skillinfoblock(sd);
		return;
	}

	if( sd->status.skill_point > 0 &&
	    sd->status.skill[skill_num].id != 0 &&
		sd->status.skill[skill_num].flag == 0 &&
	    sd->status.skill[skill_num].lv < pc_get_skilltree_max(&sd->s_class,skill_num) )
	{
		sd->status.skill[skill_num].lv++;
		sd->status.skill_point--;
		status_calc_pc(sd,0);
		clif_skillup(sd,skill_num);
		clif_updatestatus(sd,SP_SKILLPOINT);
		if(skill_num == GN_REMODELING_CART)
			clif_updatestatus(sd,SP_CARTINFO);
#if PACKETVER < 20071128
		clif_skillinfoblock(sd);
#endif
	}

	return;
}

/*==========================================
 * /allskill
 *------------------------------------------
 */
int pc_allskillup(struct map_session_data *sd,int flag)
{
	int i;

	for(i=0; i<MAX_PCSKILL; i++) {
		sd->status.skill[i].id = 0;
		if(sd->status.skill[i].flag) {	// cardスキルなら、
			sd->status.skill[i].lv   = (sd->status.skill[i].flag == 1)? 0: sd->status.skill[i].flag-2;	// 本当のlvに
			sd->status.skill[i].flag = 0;	// flagは0にしておく
		}
	}

	if(battle_config.gm_allskill > 0 && pc_isGM(sd) >= battle_config.gm_allskill) {
		// 全てのスキル
		for(i = 1; i <= MAX_PCSKILL; i++) {
			// NPCスキルは除外
			if(skill_get_inf2(i)&INF2_NPC)
				continue;
			// 太陽と月と星の悪魔は除外（ペナルティの永続暗闇がきついので）
			if(i == SG_DEVIL)
				continue;
			// アブラカタブラ専用スキルは設定値により取得判定
			if(i >= 291 && i <= 303 && !battle_config.gm_allskill_addabra)
				continue;
			sd->status.skill[i].lv = skill_get_max(i);
		}
	} else {
		int id;
		for(i=0; (id = skill_tree[sd->s_class.upper][sd->s_class.job][i].id) > 0; i++) {
			if(id == SG_DEVIL)	// ここで除外処理
				continue;
			// flagがあるならクエストスキルも取得する
			if(skill_get_inf2(id)&INF2_QUEST && !flag && !battle_config.quest_skill_learn)
				continue;
			sd->status.skill[id].id = id;
			sd->status.skill[id].lv = skill_tree[sd->s_class.upper][sd->s_class.job][i].max;
		}
	}
	status_calc_pc(sd,0);

	// status_calc_pc() 内でパケット送信されない場合があるのでここでもう一度送信する必要がある
	clif_skillinfoblock(sd);

	return 0;
}

/*==========================================
 * /resetstate
 *------------------------------------------
 */
#define roundsp(a)	((a-96)/5)
#define sumsp(a)	((a)*((a-2)/10+2) - 5*((a-2)/10)*((a-2)/10) - 6*((a-2)/10) -2)
#define newsumsp(a)	((roundsp(a)*4+12)*(a-100)-((roundsp(a)-2)*(roundsp(a)-1)*10+(roundsp(a)-1)*20))

void pc_resetstate(struct map_session_data* sd)
{
	int add = 0;
	int param[6];
	int i;

	nullpo_retv(sd);

	param[0] = sd->status.str;
	param[1] = sd->status.agi;
	param[2] = sd->status.vit;
	param[3] = sd->status.int_;
	param[4] = sd->status.dex;
	param[5] = sd->status.luk;

	for(i = 0; i < 6; i++) {
		if(battle_config.new_statusup_calc && param[i] > 100) {
			add += newsumsp(param[i]);
			param[i] = 100;
		}
		add += sumsp(param[i]);
	}

	sd->status.status_point += add;

	clif_updatestatus(sd,SP_STATUSPOINT);

	sd->status.str  = 1;
	sd->status.agi  = 1;
	sd->status.vit  = 1;
	sd->status.int_ = 1;
	sd->status.dex  = 1;
	sd->status.luk  = 1;

	clif_updatestatus(sd,SP_STR);
	clif_updatestatus(sd,SP_AGI);
	clif_updatestatus(sd,SP_VIT);
	clif_updatestatus(sd,SP_INT);
	clif_updatestatus(sd,SP_DEX);
	clif_updatestatus(sd,SP_LUK);

	clif_updatestatus(sd,SP_USTR);
	clif_updatestatus(sd,SP_UAGI);
	clif_updatestatus(sd,SP_UVIT);
	clif_updatestatus(sd,SP_UINT);
	clif_updatestatus(sd,SP_UDEX);
	clif_updatestatus(sd,SP_ULUK);

	status_calc_pc(sd,0);

	return;
}

/*==========================================
 * /resetskill
 *------------------------------------------
 */
void pc_resetskill(struct map_session_data* sd, int flag)
{
	int i,skill;

	nullpo_retv(sd);

	if(flag < 0)
		flag = battle_config.quest_skill_reset;

	for(i=1; i<MAX_PCSKILL; i++) {
		if((skill = pc_checkskill2(sd,i)) > 0) {
			if(!(skill_get_inf2(i)&INF2_QUEST) || battle_config.quest_skill_learn) {
				if(!sd->status.skill[i].flag) {
					sd->status.skill_point += skill;
				} else if(sd->status.skill[i].flag > 2) {
					sd->status.skill_point += (sd->status.skill[i].flag - 2);
				}
				sd->status.skill[i].lv = 0;
			}
			else if(flag) {
				// クエストスキルもリセットする
				sd->status.skill[i].lv = 0;
			}
			sd->status.skill[i].flag = 0;
		} else {
			sd->status.skill[i].lv = 0;
		}
	}
	sd->skill_clone.id = 0;
	sd->skill_clone.lv = 0;
	sd->skill_reproduce.id = 0;
	sd->skill_reproduce.lv = 0;
	clif_updatestatus(sd,SP_SKILLPOINT);
	clif_skillinfoblock(sd);
	status_calc_pc(sd,0);

	return;
}

/*==========================================
 * PCにダメージを与える
 *------------------------------------------
 */
int pc_damage(struct block_list *src,struct map_session_data *sd,int damage)
{
	int i;

	nullpo_retr(0, sd);

	// 既に死んでいたら無効
	if(unit_isdead(&sd->bl))
		return 0;
	// 座ってたら立ち上がる
	if(pc_issit(sd) && sd->sc.data[SC_SITDOWN_FORCE].timer == -1 && sd->sc.data[SC_BANANA_BOMB].timer == -1) {
		pc_setstand(sd);
		skill_sit(sd,0);
	}

	// 詠唱バー表示中だったら中断
	if(sd->progressbar.npc_id)
		clif_progressbar_abort(sd);

	// 歩いていたら足を止める
	if(((sd->sc.data[SC_ENDURE].timer == -1 && sd->sc.data[SC_BERSERK].timer == -1 && !sd->special_state.infinite_endure) || map[sd->bl.m].flag.gvg) && !unit_isrunning(&sd->bl))
		unit_stop_walking(&sd->bl,battle_config.pc_hit_stop_type);

	// 演奏/ダンスの中断
	if(damage > sd->status.max_hp>>2)
		skill_stop_dancing(&sd->bl,0);

	if(damage > 0 && sd->sc.data[SC_GRAVITATION_USER].timer != -1)
		status_change_end(&sd->bl, SC_GRAVITATION_USER, -1);

	// 先制された場合は共闘参加
	if(src && src->type == BL_MOB)
		battle_join_struggle((struct mob_data *)src, &sd->bl);

	sd->status.hp -= damage;
	if(sd->status.pet_id > 0 && sd->pd && sd->petDB && battle_config.pet_damage_support)
		pet_target_check(sd,src,1);

	// ハイド状態を解除
	status_change_hidden_end(&sd->bl);

	// 敵の攻撃を受けると一定確率で装備が壊れる
	if(sd->loss_equip_flag&0x1000 && damage > 0) {	// 魔法でも壊れる
		for(i=0; i<EQUIP_INDEX_MAX; i++) {
			if(atn_rand()%10000 < sd->break_myequip_rate_when_hit[i])
				pc_break_equip2(sd,i);
		}
	}

	// 敵の攻撃を受けると一定確率で装備が消滅
	if(sd->loss_equip_flag&0x0020 && damage > 0) {
		for(i=0; i<EQUIP_INDEX_MAX; i++) {
			if(atn_rand()%10000 < sd->loss_equip_rate_when_hit[i])
				pc_lossequipitem(sd,i,0);
		}
	}

	if(sd->status.hp > 0) {
		// まだ生きているならHP更新
		clif_updatestatus(sd,SP_HP);

		if( sd->sc.data[SC_AUTOBERSERK].timer != -1 &&
		    sd->status.hp < sd->status.max_hp>>2 &&
		    (sd->sc.data[SC_PROVOKE].timer == -1 || sd->sc.data[SC_PROVOKE].val2 == 0) )
		{
			// オートバーサーク発動
			status_change_start(&sd->bl,SC_PROVOKE,10,1,0,0,0,0);
		}
		return 0;
	}

	// スパノビがHP0になったとき、Exp99.0%以上かLv100状態ならばHPが全回復して金剛状態になる
	if((sd->s_class.job == PC_JOB_SNV || sd->s_class.job == PC_JOB_ESNV) && !sd->state.snovice_dead_flag) {
		atn_bignumber next = pc_nextbaseexp(sd);
		if( (next > 0 && sd->status.base_exp * 1000 / next >= 990) ||
		    (next <= 0 && sd->status.base_exp >= battle_config.snovice_maxexp_border) )
		{
			sd->status.hp = sd->status.max_hp;
			clif_updatestatus(sd,SP_HP);
			clif_skill_nodamage(&sd->bl,&sd->bl,MO_STEELBODY,5,1);
			status_change_start(&sd->bl,SC_STEELBODY,5,0,0,0,skill_get_time(MO_STEELBODY,5),0);
			sd->state.snovice_dead_flag = 1;
			return 0;
		}
	}

	// 死亡処理
	pc_dead(src, sd);

	return 0;
}

/*==========================================
 * pcの死亡処理
 *------------------------------------------
 */
static int pc_dead(struct block_list *src,struct map_session_data *sd)
{
	int i, kaizel_lv = 0;
	struct map_session_data *ssd = NULL;

	nullpo_retr(0, sd);

	if(src && src->type == BL_PC)
		ssd = (struct map_session_data *)src;

	// OnPCDieイベント
	if(battle_config.pc_die_script)
		npc_event_doall_id("OnPCDie",sd->bl.id,sd->bl.m);

	// キラー情報更新およびOnPCKillイベント
	if(ssd && ssd != sd) {
		if(battle_config.save_pckiller_type) {
			if( (battle_config.save_pckiller_type & 1 && map[sd->bl.m].flag.pvp) ||
			    (battle_config.save_pckiller_type & 2 && map[sd->bl.m].flag.gvg) ||
			    (battle_config.save_pckiller_type & 4 && map[sd->bl.m].flag.pk) )
			{
				ssd->kill.char_id  = sd->status.char_id;		// 自分が殺した相手のキャラID
				sd->kill.merderer_char_id = ssd->status.char_id;	// 自分を殺した相手のキャラID
				clif_update_temper(ssd);
				clif_update_temper(sd);
			}
		}
		if(battle_config.pc_kill_script)
			npc_event_doall_id("OnPCKill",sd->bl.id,sd->bl.m);
	}

	// カイゼル
	if(sd->sc.data[SC_KAIZEL].timer != -1) {
		kaizel_lv = sd->sc.data[SC_KAIZEL].val1;	// ステータス異常が解除される前にスキルLvを保存
		if(kaizel_lv > 10)
			kaizel_lv = 10;
	}

	// アイテム消滅
	if(sd->loss_equip_flag&0x0001) {
		for(i=0; i<EQUIP_INDEX_MAX; i++) {
			if(atn_rand()%10000 < sd->loss_equip_rate_when_die[i])
				pc_lossequipitem(sd,i,0);
		}
	}

	// 自動蘇生
	if(atn_rand()%10000 < sd->autoraise.rate)
	{
		// 判りにくいのでリザのエフェクト
		clif_skill_nodamage(&sd->bl,&sd->bl,ALL_RESURRECTION,4,1);

		// HPSP回復
		sd->status.hp = sd->status.max_hp * sd->autoraise.hp_per/100;
		if(sd->status.hp < 1)
			sd->status.hp = 1;
		if(sd->status.hp > sd->status.max_hp)
			sd->status.hp = sd->status.max_hp;
		clif_updatestatus(sd,SP_HP);

		if(sd->autoraise.flag) {
			sd->status.sp = sd->status.max_sp * sd->autoraise.sp_per/100;
			if(sd->status.sp < 0)
				sd->status.sp = 0;
			if(sd->status.sp > sd->status.max_sp)
				sd->status.sp = sd->status.max_sp;
			clif_updatestatus(sd,SP_SP);
		}
		return 0;
	}

	sd->status.hp = 0;

	if(sd->state.store == STORE_TYPE_VENDING)
		vending_closevending(sd);
	if(sd->state.store == STORE_TYPE_BUYINGSTORE)
		buyingstore_close(sd);

	if(pc_isgear(sd))		// 魔導ギアを解除
		pc_setoption(sd, (sd->sc.option & ~OPTION_MADOGEAR));

	pc_delspiritball(sd,sd->spiritball.num,0);
	pc_delcoin(sd,sd->coin.num,0);
	pc_delelementball(sd,sd->elementball.num,0);

	if(sd->status.pet_id > 0 && sd->pd && sd->petDB) {
		sd->pet.intimate -= sd->petDB->die;
		if(sd->pet.intimate < 0)
			sd->pet.intimate = 0;
		clif_send_petdata(sd,1,sd->pet.intimate);
	}
	if(sd->status.merc_id > 0 && sd->mcd) {
		//clif_disp_onlyself(sd->fd, msg_txt(191));	// 傭兵が逃走しました。
		clif_msgstringtable(sd, 0x4f5);
		merc_delete_data(sd);
	}
	if(sd->status.homun_id > 0 && sd->hd) {
		// 再生の光
		if(sd->sc.data[SC_LIGHT_OF_REGENE].timer != -1) {
			homun_damage(NULL, sd->hd, status_get_max_hp(&sd->hd->bl));
		}
	}

	unit_stop_walking(&sd->bl,0);
	unit_skillcastcancel(&sd->bl,0);	// 詠唱の中止
	skill_stop_dancing(&sd->bl, 0);
	clif_clearchar_area(&sd->bl,1);
	skill_unit_move(&sd->bl,gettick(),0);
	if(sd->sc.data[SC_BLADESTOP].timer != -1)		// 白刃は事前に解除
		status_change_end(&sd->bl,SC_BLADESTOP,-1);
	if(sd->sc.data[SC_CLOSECONFINE].timer != -1)	// クローズコンファインは事前に解除
		status_change_end(&sd->bl,SC_CLOSECONFINE,-1);
	if(sd->sc.data[SC_STOP].timer != -1)
		status_change_end(&sd->bl,SC_STOP,-1);
	if(sd->sc.data[SC_CURSEDCIRCLE_USER].timer != -1)
		status_change_end(&sd->bl,SC_CURSEDCIRCLE_USER,-1);
	if(sd->sc.data[SC_CURSEDCIRCLE].timer != -1)
		status_change_end(&sd->bl,SC_CURSEDCIRCLE,-1);
	sd->status.die_counter++;	// 死にカウンター書き込み
	status_change_release(&sd->bl,0x01);	// ステータス異常を解除する

	pc_setdead(sd);

	if(sd->s_class.job == PC_JOB_NV) {
		if(battle_config.restart_hp_rate <= 50)		// ノビでレート50以下は半分回復
			sd->status.hp = sd->status.max_hp / 2;
		else
			sd->status.hp = sd->status.max_hp * battle_config.restart_hp_rate / 100;
	}

	clif_updatestatus(sd,SP_HP);
	status_calc_pc(sd,0);

	// ドクロドロップ
	if(battle_config.bone_drop == 2 || (battle_config.bone_drop == 1 && map[sd->bl.m].flag.pvp) || (battle_config.bone_drop == 3 && map[sd->bl.m].flag.pk))
	{
		struct item item_tmp;
		memset(&item_tmp,0,sizeof(item_tmp));
		if(battle_config.bone_drop_itemid)
			item_tmp.nameid = battle_config.bone_drop_itemid;
		else
			item_tmp.nameid = 7005;
		item_tmp.identify = 1;
		item_tmp.card[0]  = 0x00fe;
		item_tmp.card[1]  = 0;
		*((int *)(&item_tmp.card[2])) = sd->status.char_id;	// キャラID
		map_addflooritem(&item_tmp,1,sd->bl.m,sd->bl.x,sd->bl.y,0,0,0,0);
	}

	for(i=0; i<5; i++) {
		if(sd->dev.val1[i]) {
			status_change_end(map_id2bl(sd->dev.val1[i]),SC_DEVOTION,-1);
			sd->dev.val1[i] = sd->dev.val2[i] = 0;
		}
	}

	// シャドウフォーム終了
	if(sd->shadowform_id) {
		status_change_end(map_id2bl(sd->shadowform_id),SC__SHADOWFORM,-1);
		sd->shadowform_id = 0;
	}

	// 死亡直後にデスペナルティを発生させる場合
	if(battle_config.death_penalty_type&1)
		pc_exp_penalty(sd, ssd, 100, 1);

	// PK
	if(map[sd->bl.m].flag.pk) {
		// ランキング計算
		/*
		if(!map[sd->bl.m].flag.pk_nocalcrank) {
			sd->pvp_point -= 5;
			if(ssd)
				ssd->pvp_point++;
		}
		*/
		// ナイトメアモードアイテムドロップ
		if(ssd && ssd != sd && map[sd->bl.m].flag.pk_nightmaredrop) {
			pc_nightmare_drop(sd,MF_PK_NIGHTMAREDROP);
			pc_setdead(sd);
		}
		if(ssd && ssd != sd) {
			// 被虐殺者
			ranking_gain_point(sd,RK_PK,-5);
			ranking_setglobalreg(sd,RK_PK);
			ranking_update(sd,RK_PK);
			// 虐殺者
			ranking_gain_point(ssd,RK_PK,1);
			ranking_setglobalreg(ssd,RK_PK);	// MOBなど更新回数が多い場合は定期的に更新
			ranking_update(ssd,RK_PK);		// MOBなど更新回数が多い場合は定期的に更新
			status_change_start(&ssd->bl,SC_PK_PENALTY,0,0,0,0,battle_config.pk_penalty_time,0);
		}
	}
	// PvP
	if(map[sd->bl.m].flag.pvp) {
		// ランキング計算
		if(!map[sd->bl.m].flag.pvp_nocalcrank) {
			sd->pvp_point -= 5;
			if(ssd)
				ssd->pvp_point++;
		}
		// ナイトメアモードアイテムドロップ
		if(map[sd->bl.m].flag.pvp_nightmaredrop) {
			pc_nightmare_drop(sd,MF_PVP_NIGHTMAREDROP);
			pc_setdead(sd);
		}

		/*
		// ランキングサンプル
		if(ssd) {
			ranking_gain_point(ssd,RK_PVP,1);
			ranking_setglobalreg(ssd,RK_PVP);	// MOBなど更新回数が多い場合は定期的に更新
			ranking_update(ssd,RK_PVP);		// MOBなど更新回数が多い場合は定期的に更新

			// 死んだ場合ポイントを減らすなら
			//if(ranking_get_point(sd,RK_PVP) > =1) {
			//	ranking_gain_point(sd,RK_PVP,-1);
			//	ranking_setglobalreg(sd,RK_PVP);	// MOBなど更新回数が多い場合は定期的に更新
			//	ranking_update(sd,RK_PVP);		// MOBなど更新回数が多い場合は定期的に更新
			//}
		}
		*/
	}
	// GvG
	if(map[sd->bl.m].flag.gvg) {
		// ナイトメアモードアイテムドロップ
		if(map[sd->bl.m].flag.gvg_nightmaredrop) {
			pc_nightmare_drop(sd,MF_GVG_NIGHTMAREDROP);
		}
	}

	if((map[sd->bl.m].flag.pvp && sd->pvp_point < 0) || map[sd->bl.m].flag.gvg || map[sd->bl.m].flag.norevive) {
		// 強制送還
		sd->pvp_point = 0;
		pc_setpos(sd,sd->status.save_point.map,sd->status.save_point.x,sd->status.save_point.y,0);
	}
	else if(kaizel_lv > 0) {
		// 全ての処理が完了してからカイゼルによる復活
		pc_setstand(sd);
		clif_skill_nodamage(&sd->bl,&sd->bl,ALL_RESURRECTION,4,1);
		// オシリスカード
		if(sd->special_state.restart_full_recover) {
			sd->status.hp = sd->status.max_hp;
			sd->status.sp = sd->status.max_sp;
			clif_updatestatus(sd,SP_SP);
		} else {
			sd->status.hp = sd->status.max_hp * kaizel_lv / 10;
		}
		clif_updatestatus(sd,SP_HP);
		clif_resurrection(&sd->bl,1);
		clif_skill_nodamage(&sd->bl,&sd->bl,PR_KYRIE,kaizel_lv,1);
		status_change_start(&sd->bl,SC_KYRIE,kaizel_lv,0,0,0,2000,0);
		if(battle_config.pc_invincible_time > 0)
			pc_setinvincibletimer(sd,battle_config.pc_invincible_time);
	}

	return 0;
}

/*==========================================
 * ナイトメアモードのアイテムドロップ
 *------------------------------------------
 */
static int pc_nightmare_drop(struct map_session_data *sd,short flag)
{
	int i;

	nullpo_retr(0, sd);

	for(i=0; i<MAX_DROP_PER_MAP; i++) {
		int itemid, type, per, j;
		int idx = -1, count = 0;

		// アイテムIDが0のときは末尾なので終了
		if((itemid = map[sd->bl.m].drop_list[i].drop_id) == 0)
			break;
		// マップフラグ番号が合わない
		if(flag != map[sd->bl.m].drop_list[i].drop_flag)
			continue;

		type = map[sd->bl.m].drop_list[i].drop_type;
		per  = map[sd->bl.m].drop_list[i].drop_per;

		if(type < 1 || type > 3 || per <= 0)
			continue;

		for(j=0; j<MAX_INVENTORY; j++) {
			if(sd->status.inventory[j].nameid <= 0 || sd->status.inventory[j].amount <= 0)
				continue;

			// type=1,2は装備チェック、type=3なら無条件で許可
			if( (type == 1 && sd->status.inventory[j].equip) ||
			    (type == 2 && !sd->status.inventory[j].equip) )
				continue;

			// IDがある場合、IDが一致していて確率OKならドロップ処理へ
			if(itemid > 0 && itemid == sd->status.inventory[j].nameid && atn_rand()%10000 < per) {
				idx = j;
				break;
			}
			// IDが負の場合、ランダムに対象を選択する（確率はまだ計算しない）
			if(itemid < 0 && atn_rand()%(++count) == 0) {
				idx = j;
			}
		}

		if(idx >= 0 && (itemid > 0 || atn_rand()%10000 < per)) {	// IDが負の場合に限りここで確率計算する
			// ドロップ処理
			if(sd->status.inventory[idx].equip)
				pc_unequipitem(sd,idx,0);
			pc_dropitem(sd,idx,1);
		}
	}
	return 0;
}

/*==========================================
 * script用PCステータス読み出し
 *------------------------------------------
 */
int pc_readparam(struct map_session_data *sd,int type)
{
	int val = 0;

	nullpo_retr(0, sd);

	switch(type) {
	case SP_SKILLPOINT:
		val = sd->status.skill_point;
		break;
	case SP_STATUSPOINT:
		val = sd->status.status_point;
		break;
	case SP_ZENY:
		val = sd->status.zeny;
		break;
	case SP_BASELEVEL:
		val = sd->status.base_level;
		break;
	case SP_JOBLEVEL:
		val = sd->status.job_level;
		break;
	case SP_CLASS:
		val = sd->status.class_;
		break;
	case SP_JOB:
		val = sd->s_class.job;
		break;
	case SP_UPPER:
		val = sd->s_class.upper;
		break;
	case SP_SEX:
		val = sd->sex;
		break;
	case SP_WEIGHT:
		val = sd->weight;
		break;
	case SP_MAXWEIGHT:
		val = sd->max_weight;
		break;
	case SP_BASEEXP:
		val = (sd->status.base_exp > 0x7fffffff)? 0x7fffffff: (int)sd->status.base_exp;
		break;
	case SP_JOBEXP:
		val = (sd->status.job_exp > 0x7fffffff)? 0x7fffffff: (int)sd->status.job_exp;
		break;
	case SP_NEXTBASEEXP:
		val = (pc_nextbaseexp(sd) > 0x7fffffff)? 0x7fffffff: (int)pc_nextbaseexp(sd);
		break;
	case SP_NEXTJOBEXP:
		val = (pc_nextjobexp(sd) > 0x7fffffff)? 0x7fffffff: (int)pc_nextjobexp(sd);
		break;
	case SP_HP:
		val = sd->status.hp;
		break;
	case SP_MAXHP:
		val = sd->status.max_hp;
		break;
	case SP_SP:
		val = sd->status.sp;
		break;
	case SP_MAXSP:
		val = sd->status.max_sp;
		break;
	case SP_PARTNER:
		val = sd->status.partner_id;
		break;
	case SP_CART:
#if PACKETVER < 20120201
		val = sd->sc.option&OPTION_CARTMASK;
#else
		if(sd->sc.data[SC_ON_PUSH_CART].timer != -1)
			val = sd->sc.data[SC_ON_PUSH_CART].val1;
#endif
		break;
	case SP_STR:
		val = sd->status.str;
		break;
	case SP_AGI:
		val = sd->status.agi;
		break;
	case SP_VIT:
		val = sd->status.vit;
		break;
	case SP_INT:
		val = sd->status.int_;
		break;
	case SP_DEX:
		val = sd->status.dex;
		break;
	case SP_LUK:
		val = sd->status.luk;
		break;
	case SP_SPEED:
		val = sd->speed;
		break;
	case SP_ATK1:
		val = sd->watk;
		break;
	case SP_ATK2:
		val = sd->watk2;
		break;
	case SP_MATK1:
		val = sd->matk1;
		break;
	case SP_MATK2:
		val = sd->matk2;
		break;
	case SP_DEF1:
		val = sd->def;
		break;
	case SP_DEF2:
		val = sd->def2;
		break;
	case SP_MDEF1:
		val = sd->mdef;
		break;
	case SP_MDEF2:
		val = sd->mdef2;
		break;
	case SP_HIT:
		val = sd->hit;
		break;
	case SP_FLEE1:
		val = sd->flee;
		break;
	case SP_FLEE2:
		val = sd->flee2;
		break;
	case SP_CRITICAL:
		val = sd->critical;
		break;
	case SP_ASPD:
		val = sd->aspd;
		break;
	case SP_DIE_COUNTER:
		val = sd->status.die_counter;
		break;
	// グローバル変数保存タイプ
	case SP_CLONESKILL_ID:
		val = sd->skill_clone.id;
		break;
	case SP_CLONESKILL_LV:
		val = sd->skill_clone.lv;
		break;
	case SP_BS_POINT:
		val = sd->ranking_point[RK_BLACKSMITH];
		break;
	case SP_AM_POINT:
		val = sd->ranking_point[RK_ALCHEMIST];
		break;
	case SP_TK_POINT:
		val = sd->ranking_point[RK_TAEKWON];
		break;
	case SP_PK_POINT:
		val = sd->ranking_point[RK_PK];
		break;
	case SP_MISSON_TARGET:
		val = sd->tk_mission_target;
		break;
	case SP_HATE_SUN:
		val = sd->hate_mob[0];
		break;
	case SP_HATE_MOON:
		val = sd->hate_mob[1];
		break;
	case SP_HATE_STAR:
		val = sd->hate_mob[2];
		break;
	case SP_HOM_INTIMATE:
		if(sd->hd)
			val = sd->hd->intimate;
		break;
	case SP_PHARMACY_SUCCESS:
		val = sd->am_pharmacy_success;
		break;
	case SP_KILL_CHAR:
		val = sd->kill.char_id;
		break;
	case SP_KILLED_CHAR:
		val = sd->kill.merderer_char_id;
		break;
	case SP_SHOP_POINT:
		val = sd->shop_point;
		break;
	case SP_REPRODUCE_ID:
		val = sd->skill_reproduce.id;
		break;
	case SP_REPRODUCE_LV:
		val = sd->skill_reproduce.lv;
		break;
	// アカウント変数保存タイプ
	case SP_DEPOSIT:
		val = sd->deposit;
		break;
	}

	return val;
}

/*==========================================
 * script用PCステータス設定
 *------------------------------------------
 */
int pc_setparam(struct map_session_data *sd,int type,int val)
{
	nullpo_retr(0, sd);

	switch(type) {
	case SP_BASELEVEL:
		if(val > sd->status.base_level) {
			int i;
			for(i = 1; i <= (val - sd->status.base_level); i++)
				sd->status.status_point += (sd->status.base_level + i + 14) / 5;
		}
		sd->status.base_level = val;
		sd->status.base_exp = 0;
		clif_updatestatus(sd, SP_BASELEVEL);
		clif_updatestatus(sd, SP_NEXTBASEEXP);
		clif_updatestatus(sd, SP_STATUSPOINT);
		clif_updatestatus(sd, SP_BASEEXP);
		status_calc_pc(sd, 0);
		pc_heal(sd, sd->status.max_hp, sd->status.max_sp);
		break;
	case SP_JOBLEVEL:
		if(val > 0) {
			if(val >= sd->status.job_level) {
				int up_level = max_job_table[sd->s_class.upper][sd->s_class.job];
				if(val > up_level)
					val = up_level;
				sd->status.skill_point += (val-sd->status.job_level);
				sd->status.job_level = val;
				sd->status.job_exp = 0;
				clif_updatestatus(sd, SP_JOBLEVEL);
				clif_updatestatus(sd, SP_NEXTJOBEXP);
				clif_updatestatus(sd, SP_JOBEXP);
				clif_updatestatus(sd, SP_SKILLPOINT);
				status_calc_pc(sd, 0);
				clif_misceffect(&sd->bl, 1);
			} else {
				sd->status.job_level = val;
				sd->status.job_exp = 0;
				clif_updatestatus(sd, SP_JOBLEVEL);
				clif_updatestatus(sd, SP_NEXTJOBEXP);
				clif_updatestatus(sd, SP_JOBEXP);
				status_calc_pc(sd, 0);
			}
			clif_updatestatus(sd,type);
		}
		break;
	case SP_SKILLPOINT:
		sd->status.skill_point = val;
		break;
	case SP_STATUSPOINT:
		sd->status.status_point = val;
		break;
	case SP_ZENY:
		if(val <= MAX_ZENY) {
			// MAX_ZENY 以下なら代入
			sd->status.zeny = val;
		} else {
			if(sd->status.zeny > val) {
				// Zeny が減少しているなら代入
				sd->status.zeny = val;
			} else if(sd->status.zeny <= MAX_ZENY) {
				// Zeny が増加していて、現在の値がMAX_ZENY 以下ならMAX_ZENY
				sd->status.zeny = MAX_ZENY;
			} else {
				// Zeny が増加していて、現在の値がMAX_ZENY より下なら増加分を無視
				;
			}
		}
		break;
	case SP_BASEEXP:
		sd->status.base_exp = val;
		if(sd->status.base_exp < 0)
			sd->status.base_exp = 0;
		while(pc_checkbaselevelup(sd));
		break;
	case SP_JOBEXP:
		sd->status.job_exp = val;
		if(sd->status.job_exp < 0)
			sd->status.job_exp = 0;
		while(pc_checkjoblevelup(sd));
		break;

	// paramだがupdatestatus出来ないもの
	case SP_CLASS:
	case SP_SEX:
	case SP_UPPER:
	case SP_PARTNER:
	case SP_CART:
		return 0;
	case SP_DIE_COUNTER:
		sd->status.die_counter = val;
		status_calc_pc(sd,0);
		return 0;

	// グローバル変数保存タイプ
	case SP_CLONESKILL_ID:
		sd->skill_clone.id = val;
		pc_setglobalreg(sd,"PC_CLONESKILL_ID",val);
		clif_skillinfoblock(sd);
		return 0;
	case SP_CLONESKILL_LV:
		sd->skill_clone.lv = val;
		pc_setglobalreg(sd,"PC_CLONESKILL_LV",val);
		clif_skillinfoblock(sd);
		return 0;
	case SP_BS_POINT:
		ranking_gain_point(sd,RK_BLACKSMITH,val - sd->ranking_point[RK_BLACKSMITH]);
		ranking_setglobalreg(sd,RK_BLACKSMITH);
		ranking_update(sd,RK_BLACKSMITH);
		return 0;
	case SP_AM_POINT:
		ranking_gain_point(sd,RK_ALCHEMIST,val - sd->ranking_point[RK_ALCHEMIST]);
		ranking_setglobalreg(sd,RK_ALCHEMIST);
		ranking_update(sd,RK_ALCHEMIST);
		return 0;
	case SP_TK_POINT:
		ranking_gain_point(sd,RK_TAEKWON,val - sd->ranking_point[RK_TAEKWON]);
		ranking_setglobalreg(sd,RK_TAEKWON);
		ranking_update(sd,RK_TAEKWON);
		return 0;
	case SP_PK_POINT:
		ranking_gain_point(sd,RK_PK,val - sd->ranking_point[RK_PK]);
		ranking_setglobalreg(sd,RK_PK);
		ranking_update(sd,RK_PK);
		return 0;
	case SP_MISSON_TARGET:
		sd->tk_mission_target = val;
		pc_setglobalreg(sd,"PC_MISSION_TARGET",val);
		clif_mission_mob(sd,sd->tk_mission_target,ranking_get_point(sd,RK_TAEKWON)%100);
		return 0;
	case SP_HATE_SUN:
		sd->hate_mob[0] = val;
		pc_setglobalreg(sd,"PC_HATE_MOB_SUN",val+1);
		clif_hate_mob(sd,1,val);
		return 0;
	case SP_HATE_MOON:
		sd->hate_mob[1] = val;
		pc_setglobalreg(sd,"PC_HATE_MOB_MOON",val+1);
		clif_hate_mob(sd,2,val);
		return 0;
	case SP_HATE_STAR:
		sd->hate_mob[2] = val;
		pc_setglobalreg(sd,"PC_HATE_MOB_STAR",val+1);
		clif_hate_mob(sd,3,val);
		return 0;
	case SP_HOM_INTIMATE:
		if(sd->hd) {
			sd->hd->intimate = val;
			pc_setglobalreg(sd,"HOM_TEMP_INTIMATE",val);
			if(sd->hd->status.intimate < sd->hd->intimate)
				sd->hd->intimate = sd->hd->status.intimate;
			clif_send_homdata(sd->hd->msd,1,sd->hd->intimate/100);
		}
		return 0;
	case SP_PHARMACY_SUCCESS:
		sd->am_pharmacy_success = val;
		pc_setglobalreg(sd,"PC_PHARMACY_SUCCESS_COUNT",val);
		return 0;
	case SP_KILL_CHAR:
		sd->kill.char_id = val;
		pc_setglobalreg(sd,"PC_KILL_CHAR",val);
		clif_update_temper(sd);
		return 0;
	case SP_KILLED_CHAR:
		sd->kill.merderer_char_id = val;
		pc_setglobalreg(sd,"PC_KILLED_CHAR",val);
		clif_update_temper(sd);
		return 0;
	case SP_SHOP_POINT:
		sd->shop_point = val;
		pc_setglobalreg(sd,"PC_SHOP_POINT",val);
		return 0;
	case SP_REPRODUCE_ID:
		sd->skill_reproduce.id = val;
		pc_setglobalreg(sd,"PC_REPRODUCE_ID",val);
		clif_skillinfoblock(sd);
		return 0;
	case SP_REPRODUCE_LV:
		sd->skill_reproduce.lv = val;
		pc_setglobalreg(sd,"PC_REPRODUCE_LV",val);
		clif_skillinfoblock(sd);
		return 0;
	// アカウント変数保存タイプ
	case SP_DEPOSIT:
		sd->deposit = val;
		pc_setaccountreg(sd,"#PC_DEPOSIT",val);
		return 0;
	}

	clif_updatestatus(sd,type);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
static int pc_checkoverhp(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	if(sd->status.hp == sd->status.max_hp)
		return 1;
	if(sd->status.hp > sd->status.max_hp) {
		sd->status.hp = sd->status.max_hp;
		clif_updatestatus(sd,SP_HP);
		return 2;
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
static int pc_checkoversp(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	if(sd->status.sp == sd->status.max_sp)
		return 1;
	if(sd->status.sp > sd->status.max_sp) {
		sd->status.sp = sd->status.max_sp;
		clif_updatestatus(sd,SP_SP);
		return 2;
	}

	return 0;
}

/*==========================================
 * HP/SP回復
 *------------------------------------------
 */
int pc_heal(struct map_session_data *sd,int hp,int sp)
{
	nullpo_retr(0, sd);

	if(pc_checkoverhp(sd) && hp > 0)
		hp = 0;

	if(pc_checkoversp(sd) && sp > 0)
		sp = 0;

	// バーサーク中は回復させない
	if(sd->sc.data[SC_BERSERK].timer != -1) {
		if(hp > 0)
			hp = 0;
	}

	if(hp+sd->status.hp > sd->status.max_hp)
		hp = sd->status.max_hp - sd->status.hp;
	if(sp+sd->status.sp > sd->status.max_sp)
		sp = sd->status.max_sp - sd->status.sp;
	sd->status.hp += hp;
	if(sd->status.hp <= 0) {
		sd->status.hp = 0;
		pc_damage(NULL,sd,1);
		hp = 0;
	}
	sd->status.sp += sp;
	if(sd->status.sp <= 0)
		sd->status.sp = 0;
	if(hp) {
		clif_updatestatus(sd,SP_HP);
		if(sd->status.party_id > 0 && party_search(sd->status.party_id))
			clif_party_hp(sd);
	}
	if(sp)
		clif_updatestatus(sd,SP_SP);

	return hp + sp;
}

/*==========================================
 * アイテムによるHP/SP回復
 *------------------------------------------
 */
int pc_itemheal(struct map_session_data *sd,int hp,int sp)
{
	int bonus;

	nullpo_retr(0, sd);

	if(sd->state.potionpitcher_flag) {
		sd->potion.hp = hp;
		sd->potion.sp = sp;
		return 0;
	}

	if(pc_checkoverhp(sd) && hp > 0)
		hp = 0;

	if(pc_checkoversp(sd) && sp > 0)
		sp = 0;

	if(hp > 0) {
		bonus = (sd->paramc[2]<<1) + 100 + pc_checkskill(sd,SM_RECOVERY)*10;
		if(bonus != 100)
			hp = hp * bonus / 100;
		bonus = 100;
		if(pc_checkskill(sd,AM_LEARNINGPOTION) > 0)
			bonus += pc_checkskill(sd,AM_LEARNINGPOTION)*5;
		// card
		if(sd->itemheal_rate[itemdb_group(sd->use_itemid)])
			bonus += sd->itemheal_rate[itemdb_group(sd->use_itemid)];
		if(bonus != 100)
			hp = hp * bonus / 100;
		if(sd->use_nameditem && ranking_get_id2rank(sd->use_nameditem,RK_ALCHEMIST))
		{
			if (sd->sc.data[SC_ROGUE].timer != -1)
				hp = hp * battle_config.ranker_potion_bonus_rogue / 100;
			else
				hp = hp * battle_config.ranker_potion_bonus / 100;
		}
		if(sd->sc.data[SC_ISHA].timer != -1)		// バイタリティアクティベーション
			hp = hp * 150 / 100;
		if(sd->sc.data[SC_CRITICALWOUND].timer != -1)
			hp = hp * (100 - sd->sc.data[SC_CRITICALWOUND].val1 * 10) / 100;
		if(sd->sc.data[SC_DEATHHURT].timer != -1)	// デスハート
			hp = hp * (100 - sd->sc.data[SC_DEATHHURT].val2) / 100;
#ifndef PRE_RENEWAL
		if(sd->sc.data[SC_FUSION].timer != -1)	// 太陽と月と星の融合
			hp = hp * 25 / 100;
#endif
	}
	if(sp > 0) {
		bonus = (sd->paramc[3]<<1) + 100 + pc_checkskill(sd,MG_SRECOVERY)*10;
		if(bonus != 100)
			sp = sp * bonus / 100;
		bonus = 100;
		if(pc_checkskill(sd,AM_LEARNINGPOTION) > 0)
			bonus += pc_checkskill(sd,AM_LEARNINGPOTION)*5;
		// card
		if(sd->itemheal_rate[itemdb_group(sd->use_itemid)])
			bonus += sd->itemheal_rate[itemdb_group(sd->use_itemid)];
		if(bonus != 100)
			sp = sp * bonus / 100;
		if(sd->use_nameditem && ranking_get_id2rank(sd->use_nameditem,RK_ALCHEMIST))
		{
			if (sd->sc.data[SC_ROGUE].timer != -1)
				sp = sp * battle_config.ranker_potion_bonus_rogue / 100;
			else
				sp = sp * battle_config.ranker_potion_bonus / 100;
		}
		if(sd->sc.data[SC_ISHA].timer != -1)		// バイタリティアクティベーション
			sp = sp * 50 / 100;
	}
	if(hp+sd->status.hp > sd->status.max_hp)
		hp = sd->status.max_hp - sd->status.hp;
	if(sp+sd->status.sp > sd->status.max_sp)
		sp = sd->status.max_sp - sd->status.sp;
	sd->status.hp += hp;
	if(sd->status.hp <= 0) {
		sd->status.hp = 0;
		pc_damage(NULL,sd,1);
		hp = 0;
	}
	sd->status.sp += sp;
	if(sd->status.sp <= 0)
		sd->status.sp = 0;
	if(hp)
		clif_updatestatus(sd,SP_HP);
	if(sp)
		clif_updatestatus(sd,SP_SP);

	return 0;
}

/*==========================================
 * 比率によるHP/SP回復
 *------------------------------------------
 */
int pc_percentheal(struct map_session_data *sd,int hp,int sp)
{
	nullpo_retr(0, sd);

	if(sd->state.potionpitcher_flag) {
		sd->potion.hp_per = hp;
		sd->potion.sp_per = sp;
		return 0;
	}

	if(pc_checkoverhp(sd) && hp > 0)
		hp = 0;

	if(pc_checkoversp(sd) && sp > 0)
		sp = 0;

	if(hp) {
		if(hp >= 100) {
			sd->status.hp = sd->status.max_hp;
		}
		else if(hp <= -100) {
			sd->status.hp = 0;
			pc_damage(NULL,sd,1);
		}
		else {
			sd->status.hp += sd->status.max_hp*hp/100;
			if(sd->status.hp > sd->status.max_hp)
				sd->status.hp = sd->status.max_hp;
			if(sd->status.hp <= 0)
				sd->status.hp = 1;
		}
	}
	if(sp) {
		if(sp >= 100) {
			sd->status.sp = sd->status.max_sp;
		}
		else if(sp <= -100) {
			sd->status.sp = 0;
		}
		else {
			sd->status.sp += sd->status.max_sp*sp/100;
			if(sd->status.sp > sd->status.max_sp)
				sd->status.sp = sd->status.max_sp;
			if(sd->status.sp < 0)
				sd->status.sp = 0;
		}
	}
	if(hp)
		clif_updatestatus(sd,SP_HP);
	if(sp)
		clif_updatestatus(sd,SP_SP);

	return 0;
}

/*==========================================
 * 職変更
 * 引数	job 職業 PC_JOB_NV <= job < PC_JOB_MAX
 *      upper 通常 0, 転生 1, 養子 2, そのまま -1
 *------------------------------------------
 */
int pc_jobchange(struct map_session_data *sd,int job, int upper)
{
	int i;
	int b_class = 0;
	int joblv_nochange = 0;

	nullpo_retr(0, sd);

	if(job >= PC_JOB_MAX)
		return 1;

	// サモナーと他職業は相互に転職不可
	if((sd->s_class.job != PC_JOB_SUM && job == PC_JOB_SUM) || (sd->s_class.job == PC_JOB_SUM && job != PC_JOB_SUM))
		return 1;

	// 転生・養子なしの職業
	if(job >= PC_JOB_TK && job <= PC_JOB_DA)
		upper = PC_UPPER_NORMAL;

	// スパノビ、拡張スパノビで転生指定の場合
	if((job == PC_JOB_SNV || job == PC_JOB_ESNV) && upper == PC_UPPER_HIGH)
		upper = PC_UPPER_NORMAL;

	// 養子<->転生前の場合JOB1にしない
	if(sd->s_class.job == job &&
	  ((sd->s_class.upper == PC_UPPER_NORMAL && upper == PC_UPPER_BABY) ||
	  (sd->s_class.upper == PC_UPPER_BABY && upper == PC_UPPER_NORMAL))) {
		joblv_nochange = 1;
	}

	if(battle_config.enable_upper_class == 0) {	// confで無効になっていたらupper=0
		upper = PC_UPPER_NORMAL;
	}

	if(upper < 0)		// 現在転生かどうかを判断する
		upper = sd->s_class.upper;

	b_class = pc_calc_class_job(job, upper);

	if((sd->sex == SEX_FEMALE && job == PC_JOB_BA) || (sd->sex == SEX_MALE && job == PC_JOB_DC) ||
	   (sd->sex == SEX_FEMALE && job == PC_JOB_MI) || (sd->sex == SEX_MALE && job == PC_JOB_WA) ||
	   sd->status.class_ == b_class)	// SEX_FEMALEはバードになれない、SEX_MALEはダンサーになれない
		return 1;

	if((sd->sex == SEX_FEMALE && job == PC_JOB_KG) || (sd->sex == SEX_MALE && job == PC_JOB_OB) ||
	   sd->status.class_ == b_class)	// SEX_FEMALEは影狼になれない、SEX_MALEは朧になれない
		return 1;

	sd->status.class_ = sd->view_class = b_class;

	// 元職業を再設定
	sd->s_class = pc_calc_base_job(sd->status.class_);

	if(joblv_nochange == 0)
	{
		sd->status.job_level = 1;
		sd->status.job_exp   = 0;
	}
	clif_updatestatus(sd,SP_JOBLEVEL);
	clif_updatestatus(sd,SP_JOBEXP);
	clif_updatestatus(sd,SP_NEXTJOBEXP);

	status_calc_pc_stop_begin(&sd->bl);
	for(i=0; i<EQUIP_INDEX_MAX; i++) {
		if(sd->equip_index[i] >= 0 && pc_isequip(sd,sd->equip_index[i]) <= 0)
			pc_unequipitem(sd,sd->equip_index[i],1);	// 装備外し
	}
	status_calc_pc_stop_end(&sd->bl);

	clif_changelook(&sd->bl,LOOK_BASE,sd->view_class);

	if(sd->status.manner < 0)
		clif_changestatus(&sd->bl,SP_MANNER,sd->status.manner);

	status_calc_pc(sd,0);
	pc_checkallowskill(sd);
	pc_equiplookall(sd);
	clif_equiplist(sd);
	clif_skillinfoblock(sd);

	achieve_update_content(sd, ACH_JOBCHANGE, sd->status.class_, 1);

	return 0;
}

/*==========================================
 * 全装備品の見た目変更
 *------------------------------------------
 */
static int pc_equiplookall(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

#if PACKETVER < 4
	clif_changelook(&sd->bl,LOOK_WEAPON,sd->status.weapon);
	clif_changelook(&sd->bl,LOOK_SHIELD,sd->status.shield);
#else
	clif_changelook(&sd->bl,LOOK_WEAPON,0);
	clif_changelook(&sd->bl,LOOK_SHOES,0);
#endif
	clif_changelook(&sd->bl,LOOK_HEAD_BOTTOM,sd->status.head_bottom);
	clif_changelook(&sd->bl,LOOK_HEAD_TOP,sd->status.head_top);
	clif_changelook(&sd->bl,LOOK_HEAD_MID,sd->status.head_mid);
	clif_changelook(&sd->bl,LOOK_ROBE,sd->status.robe);

	return 0;
}

/*==========================================
 * 見た目変更
 *------------------------------------------
 */
int pc_changelook(struct map_session_data *sd,int type,int val)
{
	nullpo_retr(0, sd);

	switch(type) {
	case LOOK_HAIR:
		if(val < 0 || val >= MAX_HAIR_STYLE)
			return 0;
		sd->status.hair = val;
		break;
	case LOOK_WEAPON:
		sd->status.weapon = val;
		break;
	case LOOK_HEAD_BOTTOM:
		sd->status.head_bottom = val;
		break;
	case LOOK_HEAD_TOP:
		sd->status.head_top = val;
		break;
	case LOOK_HEAD_MID:
		sd->status.head_mid = val;
		break;
	case LOOK_HAIR_COLOR:
		if(val < 0 || val >= MAX_HAIR_COLOR)
			return 0;
		sd->status.hair_color = val;
		break;
	case LOOK_CLOTHES_COLOR:
		if(val < 0 || val >= MAX_CLOTH_COLOR)
			return 0;
		if(sd->sc.data[SC_BUNSINJYUTSU].timer != -1)	// 影分身中は強制的に0
			val = 0;
		sd->status.clothes_color = val;
		break;
	case LOOK_SHIELD:
		sd->status.shield = val;
		break;
	case LOOK_SHOES:
		break;
	case LOOK_ROBE:
		sd->status.robe = val;
		break;
	case LOOK_BODY2:
		sd->status.style = val;
		break;
	}
	clif_changelook(&sd->bl,type,val);

	if(type == LOOK_CLOTHES_COLOR && sd->status.clothes_color == 0)
		clif_changelook(&sd->bl,LOOK_BASE,sd->view_class);

	return 0;
}

/*==========================================
 * 付属品(鷹,ペコ,カート)設定
 *------------------------------------------
 */
void pc_setoption(struct map_session_data *sd, unsigned int type)
{
	nullpo_retv(sd);

	if( ((type&OPTION_MADOGEAR) || pc_isgear(sd)) && pc_iscarton(sd) )
		type |= (sd->sc.option&OPTION_CARTMASK) | OPTION_PUSHCART;

	if( (type&OPTION_FALCON) && !pc_isfalcon(sd) ) {
		clif_status_load_id(sd,SI_FALCON,1);
	}
	else if( !(type&OPTION_FALCON) && pc_isfalcon(sd) ) {
		clif_status_load_id(sd,SI_FALCON,0);
	}

	if( ((type&OPTION_PECO) && !pc_isriding(sd)) || ((type&OPTION_DRAGONMASK) && !pc_isdragon(sd)) ) {
		clif_status_load_id(sd,SI_RIDING,1);
	}
	else if( !(type&OPTION_PECO) && pc_isriding(sd) && !(type&OPTION_DRAGONMASK) ) {
		clif_status_load_id(sd,SI_RIDING,0);
	}
	else if( !(type&OPTION_DRAGONMASK) && pc_isdragon(sd) && !(type&OPTION_PECO) ) {
		clif_status_load_id(sd,SI_RIDING,0);
	}

	if( (type&OPTION_WUGRIDER) && !pc_iswolfmount(sd) ) {
		clif_status_load_id(sd,SI_WUGRIDER,1);
	}
	else if( !(type&OPTION_WUGRIDER) && pc_iswolfmount(sd) ) {
		clif_status_load_id(sd,SI_WUGRIDER,0);
	}

	if( (type&OPTION_CARTMASK) && !pc_iscarton(sd) ) {
#if PACKETVER >= 20120201
		sd->sc.option = type;
		clif_changeoption(&sd->bl);

		// オプション値からカートタイプを変換する
		switch(type) {
			case OPTION_PUSHCART:
				type = CART_TYPE_NORMAL;
				break;
			case OPTION_PUSHCART2:
				type = CART_TYPE_LEVEL40;
				break;
			case OPTION_PUSHCART3:
				type = CART_TYPE_LEVEL65;
				break;
			case OPTION_PUSHCART4:
				type = CART_TYPE_LEVEL80;
				break;
			case OPTION_PUSHCART5:
				type = CART_TYPE_LEVEL90;
				break;
		}
#endif
		status_change_start(&sd->bl,SC_ON_PUSH_CART,type,1,0,0,9999,0);
#if PACKETVER > 20080102
		clif_skillinfoblock(sd);
#endif
		return;
	}
	else if( !(type&OPTION_CARTMASK) && pc_iscarton(sd) ) {
		sd->sc.option = type;
		clif_changeoption(&sd->bl);
		status_change_end(&sd->bl,SC_ON_PUSH_CART,-1);
#if PACKETVER > 20080102
		clif_skillinfoblock(sd);
#endif
		return;
	}

	sd->sc.option = type;
	clif_changeoption(&sd->bl);
	status_calc_pc(sd,0);
#if PACKETVER > 20080102
	clif_skillinfoblock(sd);
#endif
	return;
}

/*==========================================
 * カート設定
 *------------------------------------------
 */
void pc_setcart(struct map_session_data *sd, unsigned short type)
{
	static struct {
		const unsigned int opt;
		const unsigned short level;
	} cart[] =
	{
#if PACKETVER < 20120201
		// 古いクライアントではオプション値で管理
		{ OPTION_NOTHING,  0 },
		{ OPTION_PUSHCART,  0 },
		{ OPTION_PUSHCART2, 40 },
		{ OPTION_PUSHCART3, 65 },
		{ OPTION_PUSHCART4, 80 },
		{ OPTION_PUSHCART5, 90 },
#else
		// 新しいクライアントでは状態異常のval1で管理
		{ CART_TYPE_NOTHING,  0 },
		{ CART_TYPE_NORMAL,   0 },
		{ CART_TYPE_LEVEL40,  40 },
		{ CART_TYPE_LEVEL65,  65 },
		{ CART_TYPE_LEVEL80,  80 },
		{ CART_TYPE_LEVEL90,  90 },
		{ CART_TYPE_LEVEL101, 101 },
		{ CART_TYPE_LEVEL111, 111 },
		{ CART_TYPE_LEVEL121, 121 },
		{ CART_TYPE_LEVEL131, 131 },
#endif
	};

	nullpo_retv(sd);

	if(type >= sizeof(cart) / sizeof(cart[0]))	// unsigned short: don't check 'type < 0'
		return;

	if(pc_checkskill(sd,MC_PUSHCART) > 0) {	// プッシュカートスキル所持
		if(sd->status.base_level > cart[type].level) {
			// suppress actual cart; conserv other options
			if( pc_iscarton(sd) ) {
				status_change_start(&sd->bl,SC_ON_PUSH_CART,cart[type].opt,0,0,0,9999,0);
			} else {
				status_change_start(&sd->bl,SC_ON_PUSH_CART,cart[type].opt,1,0,0,9999,0);
			}
		}
	}

	return;
}

/*==========================================
 * 鷹設定
 *------------------------------------------
 */
int pc_setfalcon(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	if(pc_checkskill(sd,HT_FALCON) > 0) {	// ファルコンマスタリースキル所持
		pc_setoption(sd,OPTION_FALCON);
	}
	return 0;
}

/*==========================================
 * ペコペコ設定
 *------------------------------------------
 */
int pc_setriding(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	if(pc_checkskill(sd,KN_RIDING) > 0) { // ライディングスキル所持
		pc_setoption(sd,OPTION_PECO);
	}
	return 0;
}

/*==========================================
 * ドラゴン設定
 *------------------------------------------
 */
int pc_setdragon(struct map_session_data *sd, int type)
{
	nullpo_retr(0, sd);

	if(pc_checkskill(sd,RK_DRAGONTRAINING) > 0) { // ドラゴントレーニングスキル所持
		if(type > 0 && type < 5)
			pc_setoption(sd,OPTION_DRAGON2 << (type-1));
		else
			pc_setoption(sd,OPTION_DRAGON);
	}
	return 0;
}

/*==========================================
 * 魔導ギア設定
 *------------------------------------------
 */
int pc_setgear(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	if(pc_checkskill(sd,NC_MADOLICENCE) > 0) { // 魔導ギアライセンススキル所持
		pc_setoption(sd,OPTION_MADOGEAR);
	}
	return 0;
}

/*==========================================
 * GMのアイテムドロップ可否判定
 *------------------------------------------
 */
int pc_candrop(struct map_session_data *sd,int item_id)
{
	int lv;

	nullpo_retr(1, sd);

	lv = pc_isGM(sd);

	return (lv > 0 && lv < battle_config.gm_can_drop_lv);
}

/*==========================================
 * script用変数の値を読む
 *------------------------------------------
 */
int pc_readreg(struct map_session_data *sd,int reg)
{
	int i;

	nullpo_retr(0, sd);

	for(i=0; i<sd->reg_num; i++) {
		if(sd->reg[i].index == reg)
			return sd->reg[i].data;
	}
	return 0;
}

/*==========================================
 * script用変数の値を設定
 *------------------------------------------
 */
int pc_setreg(struct map_session_data *sd,int reg,int val)
{
	int i;

	nullpo_retr(0, sd);

	for(i = 0; i < sd->reg_num; i++) {
		if(sd->reg[i].index == reg) {
			sd->reg[i].data = val;
			return 0;
		}
	}
	sd->reg_num++;
	sd->reg = (struct script_reg *)aRealloc(sd->reg, sizeof(*(sd->reg)) * sd->reg_num);
	sd->reg[i].index = reg;
	sd->reg[i].data = val;

	return 0;
}

/*==========================================
 * script用文字列変数の値を読む
 *------------------------------------------
 */
char *pc_readregstr(struct map_session_data *sd, int reg)
{
	int i;

	nullpo_retr(0, sd);

	for(i = 0; i < sd->regstr_num; i++) {
		if(sd->regstr[i].index == reg)
			return sd->regstr[i].data;
	}
	return NULL;
}

/*==========================================
 * script用文字列変数の値を設定
 *------------------------------------------
 */
int pc_setregstr(struct map_session_data *sd, int reg, const char *str)
{
	int i;
	size_t size = sizeof(sd->regstr[0].data);
	struct script_regstr *p;

	nullpo_retr(0, sd);

	if(strlen(str) >= size - 1) {
		printf("pc_setregstr: string too long! %lu >= %lu\n", (unsigned long)strlen(str), (unsigned long)(size - 1));
		return 0;
	}

	for(i = 0; i < sd->regstr_num; i++) {
		if(sd->regstr[i].index == reg) {
			strncpy(sd->regstr[i].data, str, size);
			return 0;
		}
	}

	// strが同一のregstr配列上に存在している可能性があるので
	// reallocせずに先にstrをコピーしてからfreeする
	p = (struct script_regstr *)aMalloc(sizeof(sd->regstr[0]) * (sd->regstr_num + 1));
	memcpy(p, sd->regstr, sizeof(sd->regstr[0]) * sd->regstr_num);
	p[i].index = reg;
	strncpy(p[i].data, str, size);
	sd->regstr_num++;

	aFree(sd->regstr);
	sd->regstr = p;

	return 0;
}

/*==========================================
 * script用グローバル変数の値を読む
 *------------------------------------------
 */
int pc_readregistry(struct map_session_data *sd, const char *reg, int type)
{
	int i, num = 0;
	struct global_reg *gr = NULL;

	nullpo_retr(0, sd);

	switch(type) {
		case 3:
			// グローバル変数
			gr  = sd->save_reg.global;
			num = sd->save_reg.global_num;
			break;
		case 2:
			// #変数
			gr  = sd->save_reg.account;
			num = sd->save_reg.account_num;
			break;
		case 1:
			// ##変数
			gr  = sd->save_reg.account2;
			num = sd->save_reg.account2_num;
			break;
		default:
			return 0;
	}

	for(i = 0; i < num; i++) {
		if(strcmpi(gr[i].str, reg) == 0)
			return gr[i].value;
	}
	return 0;
}

/*==========================================
 * グローバル変数をdirty状態にする
 *------------------------------------------
 */
static int pc_setreg_dirty(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	sd->state.reg_dirty = 1;

	return 0;
}

/*==========================================
 * script用グローバル変数の値を設定
 *------------------------------------------
 */
int pc_setregistry(struct map_session_data *sd, const char *reg, int val, int type)
{
	int i, max = 0;
	int *num = NULL;
	int (*func)(struct map_session_data *) = NULL;
	struct global_reg *gr = NULL;

	nullpo_retr(0, sd);

	switch(type) {
		case 3:
			// グローバル変数
			gr   = sd->save_reg.global;
			num  = &sd->save_reg.global_num;
			max  = GLOBAL_REG_NUM;
			func = pc_setreg_dirty;
			break;
		case 2:
			// #変数
			gr   = sd->save_reg.account;
			num  = &sd->save_reg.account_num;
			max  = ACCOUNT_REG_NUM;
			func = intif_saveaccountreg;
			break;
		case 1:
			// ##変数
			gr   = sd->save_reg.account2;
			num  = &sd->save_reg.account2_num;
			max  = ACCOUNT_REG2_NUM;
			func = chrif_saveaccountreg2;
			break;
		default:
			return 0;
	}

	if(val == 0) {
		// delete registry
		for(i = 0; i < *num; i++) {
			if(strcmpi(gr[i].str, reg) == 0) {
				gr[i] = gr[(*num) - 1];
				(*num)--;
				func(sd);
				break;
			}
		}
		return 0;
	}
	for(i = 0; i < *num; i++) {
		if(strcmpi(gr[i].str, reg) == 0) {
			// replace registry
			if(gr[i].value != val) {
				gr[i].value = val;
				func(sd);
			}
			return 0;
		}
	}
	if(*num < max) {
		// add registry
		strncpy(gr[i].str, reg, sizeof(gr[i].str));
		gr[i].str[sizeof(gr[i].str) - 1] = '\0';	// force \0 terminal
		gr[i].value = val;
		(*num)++;
		func(sd);
		return 0;
	}
	if(battle_config.error_log)
		printf("pc_setregistry : couldn't set %s to char_id %d (MAX = %d)\n", reg, sd->status.char_id, max);

	return 1;
}

/*==========================================
 * イベントタイマー処理
 *------------------------------------------
 */
static int pc_eventtimer(int tid,unsigned int tick,int id,void *data)
{
	struct map_session_data *sd = map_id2sd(id);
	char *p = (char *)data;
	int i;

	if(sd == NULL)
		return 0;

	for(i=0; i<MAX_EVENTTIMER; i++) {
		if(sd->eventtimer[i] == tid) {
			sd->eventtimer[i] = -1;
			npc_event(sd,p);
			break;
		}
	}
	aFree(p);
	if(i == MAX_EVENTTIMER) {
		if(battle_config.error_log)
			printf("pc_eventtimer: no such event timer\n");
	}

	return 0;
}

/*==========================================
 * イベントタイマー追加
 *------------------------------------------
 */
int pc_addeventtimer(struct map_session_data *sd,int tick,const char *name)
{
	int i;

	nullpo_retr(0, sd);

	for(i=0; i<MAX_EVENTTIMER; i++) {
		if(sd->eventtimer[i] == -1)
			break;
	}
	if(i < MAX_EVENTTIMER) {
		char *evname = (char *)aStrdup(name);
		sd->eventtimer[i] = add_timer(gettick()+tick,pc_eventtimer,sd->bl.id,evname);
	} else {
		if(battle_config.error_log)
			printf("pc_addtimer: event timer is full !\n");
	}

	return 0;
}

/*==========================================
 * イベントタイマー削除
 *------------------------------------------
 */
int pc_deleventtimer(struct map_session_data *sd,const char *name)
{
	int i;

	nullpo_retr(0, sd);

	for(i=0; i<MAX_EVENTTIMER; i++) {
		if(sd->eventtimer[i] != -1) {
			char *p = (char *)(get_timer(sd->eventtimer[i])->data);
			if(strcmp(p, name) == 0) {
				delete_timer(sd->eventtimer[i],pc_eventtimer);
				sd->eventtimer[i] = -1;
				aFree(p);
				break;
			}
		}
	}
	return 0;
}

/*==========================================
 * イベントタイマーカウント値追加
 *------------------------------------------
 */
int pc_addeventtimercount(struct map_session_data *sd,const char *name,int tick)
{
	int i;

	nullpo_retr(0, sd);

	for(i=0; i<MAX_EVENTTIMER; i++) {
		if(sd->eventtimer[i] != -1) {
			char *p = (char *)(get_timer(sd->eventtimer[i])->data);
			if(strcmp(p, name) == 0) {
				addtick_timer(sd->eventtimer[i],tick);
				break;
			}
		}
	}
	return 0;
}

/*==========================================
 * イベントタイマー残り時間取得
 *------------------------------------------
 */
int pc_geteventtimerdiff(struct map_session_data *sd,const char *name)
{
	int i;
	struct TimerData *td;

	nullpo_retr(-1, sd);

	for(i=0; i<MAX_EVENTTIMER; i++) {
		if(sd->eventtimer[i] != -1) {
			td = get_timer(sd->eventtimer[i]);
			if(strcmp((char *)(td->data), name) == 0) {
				int diff = DIFF_TICK(td->tick, gettick());
				return (diff > 0)? diff: 0;
			}
		}
	}
	return -1;
}

/*==========================================
 * イベントタイマー全削除
 *------------------------------------------
 */
int pc_cleareventtimer(struct map_session_data *sd)
{
	int i;

	nullpo_retr(0, sd);

	for(i=0; i<MAX_EVENTTIMER; i++) {
		if(sd->eventtimer[i] != -1) {
			char *p = (char *)(get_timer(sd->eventtimer[i])->data);
			delete_timer(sd->eventtimer[i],pc_eventtimer);
			aFree(p);
			sd->eventtimer[i] = -1;
		}
	}
	return 0;
}

/*==========================================
 * コスチュームを反映する
 *------------------------------------------
 */
void pc_costumelook(struct map_session_data *sd)
{
	int i = -1, head_low = 0, head_mid = 0, head_top = 0, robe = 0;

	nullpo_retv(sd);

	head_low = sd->status.head_bottom;
	head_mid = sd->status.head_mid;
	head_top = sd->status.head_top;
	robe = sd->status.robe;

	sd->status.head_bottom = sd->status.head_mid = sd->status.head_top = sd->status.robe = 0;

	if((i = sd->equip_index[EQUIP_INDEX_HEAD]) >= 0) {
		if(sd->inventory_data[i])
			sd->status.head_bottom = sd->inventory_data[i]->look;
		else
			sd->status.head_bottom = 0;
	}
	if((i = sd->equip_index[EQUIP_INDEX_HEAD2]) >= 0) {
		if(sd->inventory_data[i])
			sd->status.head_top = sd->inventory_data[i]->look;
		else
			sd->status.head_top = 0;
	}
	if((i = sd->equip_index[EQUIP_INDEX_HEAD3]) >= 0) {
		if(sd->inventory_data[i])
			sd->status.head_mid = sd->inventory_data[i]->look;
		else
			sd->status.head_mid = 0;
	}
	if((i = sd->equip_index[EQUIP_INDEX_ROBE]) >= 0) {
		if(sd->inventory_data[i])
			sd->status.robe = sd->inventory_data[i]->look;
		else
			sd->status.robe = 0;
	}
	if(!map[sd->bl.m].flag.nocostume) {
		if((i = sd->equip_index[EQUIP_INDEX_COSTUME_HEAD]) >= 0) {
			if(sd->inventory_data[i])
				sd->status.head_bottom = sd->inventory_data[i]->look;
			else
				sd->status.head_bottom = 0;
		}
		if((i = sd->equip_index[EQUIP_INDEX_COSTUME_HEAD2]) >= 0) {
			if(sd->inventory_data[i])
				sd->status.head_top = sd->inventory_data[i]->look;
			else
				sd->status.head_top = 0;
		}
		if((i = sd->equip_index[EQUIP_INDEX_COSTUME_HEAD3]) >= 0) {
			if(sd->inventory_data[i])
				sd->status.head_mid = sd->inventory_data[i]->look;
			else
				sd->status.head_mid = 0;
		}
		if((i = sd->equip_index[EQUIP_INDEX_COSTUME_ROBE]) >= 0) {
			if(sd->inventory_data[i])
				sd->status.robe = sd->inventory_data[i]->look;
			else
				sd->status.robe = 0;
		}
		if((i = sd->equip_index[EQUIP_INDEX_COSTUME_FLOOR]) >= 0) {
			if(sd->inventory_data[i])
				clif_changelook(&sd->bl,LOOK_FLOOR,sd->inventory_data[i]->look);
		}
	}
	if(head_low != sd->status.head_bottom)
		clif_changelook(&sd->bl,LOOK_HEAD_BOTTOM,sd->status.head_bottom);
	if(head_top != sd->status.head_top)
		clif_changelook(&sd->bl,LOOK_HEAD_TOP,sd->status.head_top);
	if(head_mid != sd->status.head_mid)
		clif_changelook(&sd->bl,LOOK_HEAD_MID,sd->status.head_mid);
	if(robe != sd->status.robe)
		clif_changelook(&sd->bl,LOOK_ROBE,sd->status.robe);
}

/*==========================================
 * アイテムを装備する
 *------------------------------------------
 */
void pc_equipitem(struct map_session_data *sd, int n, int pos)
{
	int i,nameid;
	struct item_data *id;
	int flag;

	nullpo_retv(sd);
	nullpo_retv(id = sd->inventory_data[n]);

	nameid = sd->status.inventory[n].nameid;
	pos    = pc_equippoint(sd,n);
	flag   = pc_isequip(sd,n);

	if(battle_config.battle_log)
		printf("equip %d(%d) %x:%x\n",nameid,n,id->equip,pos);
	if(flag <= 0 || !pos) {
		clif_equipitemack(sd,n,0,0);	// fail
		if(flag < 0)
			clif_msgstringtable(sd, 0x6ed);	// アイテムを装備できるレベルに達していません。
		return;
	}
	if(pos == LOC_RLACCESSORY) {	// アクセサリ用例外処理
		int epor = LOC_NOTHING;
		if(sd->equip_index[EQUIP_INDEX_LACCESSORY] >= 0)
			epor |= sd->status.inventory[sd->equip_index[EQUIP_INDEX_LACCESSORY]].equip;
		if(sd->equip_index[EQUIP_INDEX_RACCESSORY] >= 0)
			epor |= sd->status.inventory[sd->equip_index[EQUIP_INDEX_RACCESSORY]].equip;
		epor &= LOC_RLACCESSORY;
		pos = (epor == LOC_RACCESSORY) ? LOC_LACCESSORY : LOC_RACCESSORY;
	}

	// 二刀流処理
	if( pos == LOC_RLARM && 	// 一応、装備要求箇所が二刀流武器かチェックする
	    id->equip == LOC_RARM &&	// 単手武器
	    (pc_checkskill(sd, AS_LEFT) > 0 || sd->s_class.job == PC_JOB_AS || sd->s_class.job == PC_JOB_GC ||
	     pc_checkskill(sd, KO_LEFT) > 0 || sd->s_class.job == PC_JOB_KG || sd->s_class.job == PC_JOB_OB) ) // 左手修錬有
	{
		int tpos = 0;
		if(sd->equip_index[EQUIP_INDEX_LARM] >= 0)
			tpos |= sd->status.inventory[sd->equip_index[EQUIP_INDEX_LARM]].equip;
		if(sd->equip_index[EQUIP_INDEX_RARM] >= 0)
			tpos |= sd->status.inventory[sd->equip_index[EQUIP_INDEX_RARM]].equip;
		tpos &= LOC_RARM;
		pos = (tpos == LOC_RARM) ? LOC_LARM : LOC_RARM;
	}

	for(i=0; i<EQUIP_INDEX_MAX; i++) {
		if(sd->equip_index[i] >= 0 && sd->status.inventory[sd->equip_index[i]].equip & pos) {
			pc_unequipitem(sd,sd->equip_index[i],1);
		}
	}
	// 弓矢装備
	if(pos == LOC_ARROW) {
		clif_arrowequip(sd,n);
		clif_arrow_fail(sd,3);	// 装備できました
	} else {
		clif_equipitemack(sd,n,pos,1);
	}

	for(i=0; i<EQUIP_INDEX_MAX; i++) {
		if(pos & equip_pos[i])
			sd->equip_index[i] = n;
	}
	sd->status.inventory[n].equip = pos;

	if(sd->status.inventory[n].equip & LOC_RARM) {
		if(sd->inventory_data[n])
			sd->weapontype1 = sd->inventory_data[n]->look;
		else
			sd->weapontype1 = WT_FIST;
		pc_calcweapontype(sd);
		clif_changelook(&sd->bl,LOOK_WEAPON,sd->status.weapon);
	}
	if(sd->status.inventory[n].equip & LOC_LARM) {
		if(sd->inventory_data[n]) {
			if(itemdb_isweapon(sd->inventory_data[n]->nameid)) {
				sd->status.shield = 0;
				if(sd->status.inventory[n].equip == LOC_LARM)
					sd->weapontype2 = sd->inventory_data[n]->look;
				else
					sd->weapontype2 = WT_FIST;
			}
			else if(itemdb_isarmor(sd->inventory_data[n]->nameid)) {
				sd->status.shield = sd->inventory_data[n]->look;
				sd->weapontype2 = WT_FIST;
			}
		} else {
			sd->status.shield = 0;
			sd->weapontype2 = WT_FIST;
		}
		pc_calcweapontype(sd);
		clif_changelook(&sd->bl,LOOK_SHIELD,sd->status.shield);
	}
	if(sd->status.inventory[n].equip & LOC_HEAD) {
		if(sd->equip_index[EQUIP_INDEX_COSTUME_HEAD] < 0) {
			if(sd->inventory_data[n])
				sd->status.head_bottom = sd->inventory_data[n]->look;
			else
				sd->status.head_bottom = 0;
			clif_changelook(&sd->bl,LOOK_HEAD_BOTTOM,sd->status.head_bottom);
		}
	}
	if(sd->status.inventory[n].equip & LOC_COSTUME_HEAD && !map[sd->bl.m].flag.nocostume) {
		if(sd->inventory_data[n])
			sd->status.head_bottom = sd->inventory_data[n]->look;
		else
			sd->status.head_bottom = 0;
		clif_changelook(&sd->bl,LOOK_HEAD_BOTTOM,sd->inventory_data[n]->look);
	}
	if(sd->status.inventory[n].equip & LOC_HEAD2) {
		if(sd->equip_index[EQUIP_INDEX_COSTUME_HEAD2] < 0) {
			if(sd->inventory_data[n])
				sd->status.head_top = sd->inventory_data[n]->look;
			else
				sd->status.head_top = 0;
			clif_changelook(&sd->bl,LOOK_HEAD_TOP,sd->status.head_top);
		}
	}
	if(sd->status.inventory[n].equip & LOC_COSTUME_HEAD2 && !map[sd->bl.m].flag.nocostume) {
		if(sd->inventory_data[n])
			sd->status.head_top = sd->inventory_data[n]->look;
		else
			sd->status.head_top = 0;
		clif_changelook(&sd->bl,LOOK_HEAD_TOP,sd->inventory_data[n]->look);
	}
	if(sd->status.inventory[n].equip & LOC_HEAD3) {
		if(sd->equip_index[EQUIP_INDEX_COSTUME_HEAD3] < 0) {
			if(sd->inventory_data[n])
				sd->status.head_mid = sd->inventory_data[n]->look;
			else
				sd->status.head_mid = 0;
			clif_changelook(&sd->bl,LOOK_HEAD_MID,sd->status.head_mid);
		}
	}
	if(sd->status.inventory[n].equip & LOC_COSTUME_HEAD3 && !map[sd->bl.m].flag.nocostume) {
		if(sd->inventory_data[n])
			sd->status.head_mid = sd->inventory_data[n]->look;
		else
			sd->status.head_mid = 0;
		clif_changelook(&sd->bl,LOOK_HEAD_MID,sd->inventory_data[n]->look);
	}
	if(sd->status.inventory[n].equip & LOC_SHOES)
		clif_changelook(&sd->bl,LOOK_SHOES,0);
	if(sd->status.inventory[n].equip & LOC_ROBE) {
		if(sd->equip_index[EQUIP_INDEX_COSTUME_ROBE] < 0) {
			if(sd->inventory_data[n])
				sd->status.robe = sd->inventory_data[n]->look;
			else
				sd->status.robe = 0;
			clif_changelook(&sd->bl,LOOK_ROBE,sd->status.robe);
		}
	}
	if(sd->status.inventory[n].equip & LOC_COSTUME_ROBE && !map[sd->bl.m].flag.nocostume) {
		if(sd->inventory_data[n])
			sd->status.robe = sd->inventory_data[n]->look;
		else
			sd->status.robe = 0;
		clif_changelook(&sd->bl,LOOK_ROBE,sd->inventory_data[n]->look);
	}
	if(sd->status.inventory[n].equip & LOC_COSTUME_FLOOR && !map[sd->bl.m].flag.nocostume) {
		if(sd->inventory_data[n])
			clif_changelook(&sd->bl,LOOK_FLOOR,sd->inventory_data[n]->look);
	}

	pc_checkallowskill(sd);	// 装備品でスキルか解除されるかチェック
	status_calc_pc(sd,0);
#if PACKETVER > 20080102
	clif_skillinfoblock(sd);
#endif
	if(sd->sc.data[SC_SIGNUMCRUCIS].timer != -1 && !battle_check_undead(RCT_HUMAN,sd->def_ele))
		status_change_end(&sd->bl,SC_SIGNUMCRUCIS,-1);

	return;
}

/*==========================================
 * 装備した物を外す
 *------------------------------------------
 */
void pc_unequipitem(struct map_session_data *sd, int n, int type)
{
	int hp = 0, sp = 0;

	nullpo_retv(sd);

	// キャスティング中 ストリップと破壊時が分からないので当分未実装
	//if(sd->state.casting) return 0;

	if(n < 0 || n >= MAX_INVENTORY)
		return;
	if(sd->sc.data[SC_PYROCLASTIC].timer != -1 && sd->inventory_data[n]->equip & LOC_RARM)
		return;

	if(battle_config.battle_log)
		printf("unequip %d %x:%x\n",n,pc_equippoint(sd,n),sd->status.inventory[n].equip);
	if(sd->status.inventory[n].equip) {
		int i;
		for(i=0; i<EQUIP_INDEX_MAX; i++) {
			if(sd->status.inventory[n].equip & equip_pos[i])
			{
				sd->equip_index[i] = -1;

				// 装備を外すとHP/SPのペナルティ処理
				if(sd->hp_penalty_unrig_value[i] > 0) {
					hp += sd->hp_penalty_unrig_value[i];
					sd->hp_penalty_unrig_value[i] = 0;
				}
				if(sd->sp_penalty_unrig_value[i] > 0) {
					sp += sd->sp_penalty_unrig_value[i];
					sd->sp_penalty_unrig_value[i] = 0;
				}
				if(sd->hp_rate_penalty_unrig[i] > 0) {
					hp += sd->status.max_hp*sd->hp_rate_penalty_unrig[i]/100;
					sd->hp_rate_penalty_unrig[i] = 0;
				}
				if(sd->sp_rate_penalty_unrig[i] > 0) {
					sp += sd->status.max_sp*sd->sp_rate_penalty_unrig[i]/100;
					sd->sp_rate_penalty_unrig[i] = 0;
				}
			}
		}
		if(sd->inventory_data[n]->unequip_script)
			run_script(sd->inventory_data[n]->unequip_script,0,sd->bl.id,0);
		if(!itemdb_isspecial(sd->status.inventory[n].card[0])) {
			int c;
			for(i=0; i<4; i++) {
				if((c = sd->status.inventory[n].card[i]) <= 0)
					continue;

				if(itemdb_unequipscript(c))
					run_script(itemdb_unequipscript(c),0,sd->bl.id,0);
			}
		}
		if(sd->status.inventory[n].equip & LOC_RARM) {
			sd->weapontype1 = WT_FIST;
			sd->status.weapon = sd->weapontype2;
			pc_calcweapontype(sd);
			clif_changelook(&sd->bl,LOOK_WEAPON,sd->status.weapon);
		}
		if(sd->status.inventory[n].equip & LOC_LARM) {
			sd->weapontype2 = WT_FIST;
			sd->status.shield = 0;
			pc_calcweapontype(sd);
			clif_changelook(&sd->bl,LOOK_SHIELD,sd->status.shield);
		}
		if(sd->status.inventory[n].equip & LOC_HEAD) {
			if(sd->equip_index[EQUIP_INDEX_COSTUME_HEAD] < 0) {
				sd->status.head_bottom = 0;
				clif_changelook(&sd->bl,LOOK_HEAD_BOTTOM,sd->status.head_bottom);
			}
		}
		if(sd->status.inventory[n].equip & LOC_COSTUME_HEAD && !map[sd->bl.m].flag.nocostume) {
			if(sd->equip_index[EQUIP_INDEX_HEAD] < 0) {
				sd->status.head_bottom = 0;
				clif_changelook(&sd->bl,LOOK_HEAD_BOTTOM,sd->status.head_bottom);
			} else {
				if(sd->inventory_data[sd->equip_index[EQUIP_INDEX_HEAD]]) {
					sd->status.head_bottom = sd->inventory_data[sd->equip_index[EQUIP_INDEX_HEAD]]->look;
					clif_changelook(&sd->bl,LOOK_HEAD_BOTTOM,sd->status.head_bottom);
				}
			}
		}
		if(sd->status.inventory[n].equip & LOC_HEAD2) {
			if(sd->equip_index[EQUIP_INDEX_COSTUME_HEAD2] < 0) {
				sd->status.head_top = 0;
				clif_changelook(&sd->bl,LOOK_HEAD_TOP,sd->status.head_top);
			}
		}
		if(sd->status.inventory[n].equip & LOC_COSTUME_HEAD2 && !map[sd->bl.m].flag.nocostume) {
			if(sd->equip_index[EQUIP_INDEX_HEAD2] < 0) {
				sd->status.head_top = 0;
				clif_changelook(&sd->bl,LOOK_HEAD_TOP,sd->status.head_top);
			} else {
				if(sd->inventory_data[sd->equip_index[EQUIP_INDEX_HEAD2]]) {
					sd->status.head_top = sd->inventory_data[sd->equip_index[EQUIP_INDEX_HEAD2]]->look;
					clif_changelook(&sd->bl,LOOK_HEAD_TOP,sd->status.head_top);
				}
			}
		}
		if(sd->status.inventory[n].equip & LOC_HEAD3) {
			if(sd->equip_index[EQUIP_INDEX_COSTUME_HEAD3] < 0) {
				sd->status.head_mid = 0;
				clif_changelook(&sd->bl,LOOK_HEAD_MID,sd->status.head_mid);
			}
		}
		if(sd->status.inventory[n].equip & LOC_COSTUME_HEAD3 && !map[sd->bl.m].flag.nocostume) {
			if(sd->equip_index[EQUIP_INDEX_HEAD3] < 0) {
				sd->status.head_mid = 0;
				clif_changelook(&sd->bl,LOOK_HEAD_MID,sd->status.head_mid);
			} else {
				if(sd->inventory_data[sd->equip_index[EQUIP_INDEX_HEAD3]]) {
					sd->status.head_mid = sd->inventory_data[sd->equip_index[EQUIP_INDEX_HEAD3]]->look;
					clif_changelook(&sd->bl,LOOK_HEAD_MID,sd->status.head_mid);
				}
			}
		}
		if(sd->status.inventory[n].equip & LOC_SHOES)
			clif_changelook(&sd->bl,LOOK_SHOES,0);
		if(sd->status.inventory[n].equip & LOC_ROBE) {
			if(sd->equip_index[EQUIP_INDEX_COSTUME_ROBE] < 0) {
				sd->status.robe = 0;
				clif_changelook(&sd->bl,LOOK_ROBE,sd->status.robe);
			}
		}
		if(sd->status.inventory[n].equip & LOC_COSTUME_ROBE && !map[sd->bl.m].flag.nocostume) {
			if(sd->equip_index[EQUIP_INDEX_ROBE] < 0) {
				sd->status.robe = 0;
				clif_changelook(&sd->bl,LOOK_ROBE,sd->status.robe);
			} else {
				if(sd->inventory_data[sd->equip_index[EQUIP_INDEX_ROBE]]) {
					sd->status.robe = sd->inventory_data[sd->equip_index[EQUIP_INDEX_ROBE]]->look;
					clif_changelook(&sd->bl,LOOK_ROBE,sd->status.robe);
				}
			}
		}
		if(sd->status.inventory[n].equip & LOC_COSTUME_FLOOR && !map[sd->bl.m].flag.nocostume) {
			clif_changelook(&sd->bl,LOOK_FLOOR,0);
		}

		clif_unequipitemack(sd,n,sd->status.inventory[n].equip,1);
		sd->state.inventory_dirty = 1;
		sd->status.inventory[n].id = ++sd->inventory_sortkey;	// インベントリに新規登録
		sd->status.inventory[n].equip = LOC_NOTHING;
		if(!type)
			pc_checkallowskill(sd);
		if(sd->weapontype1 == WT_FIST && sd->weapontype2 == WT_FIST)
			status_enchant_elemental_end(&sd->bl,SC_SEVENWIND);  // 暖かい風以外は武器持ち誓えで属性付与解除
	} else {
		clif_unequipitemack(sd,n,0,0);
	}
	if(!type) {
		status_calc_pc(sd,0);
		if(sd->sc.data[SC_SIGNUMCRUCIS].timer != -1 && !battle_check_undead(RCT_HUMAN,sd->def_ele))
			status_change_end(&sd->bl,SC_SIGNUMCRUCIS,-1);
	}

	if(hp) {
		if(sd->status.hp > hp) {
			pc_heal(sd,-hp,0);
		} else {
			if(!battle_config.death_by_unrig_penalty) {
				// 一旦HPが0になり、すぐに1に回復する
				sd->status.hp = 0;
				clif_updatestatus(sd,SP_HP);
				pc_heal(sd,1,0);
			} else {
				pc_heal(sd,-sd->status.hp,0);
			}
		}
	}
	if(sp) {
		if(sd->status.sp > sp)
			sd->status.sp -= sp;
		else
			sd->status.sp = 0;
		clif_updatestatus(sd,SP_SP);
	}

	return;
}

/*==========================================
 * 装備している個数を返す
 *------------------------------------------
 */
int pc_equippeditem(struct map_session_data *sd,int id)
{
	int i, j, idx, n = 0;

	nullpo_retr(0, sd);

	for(i=0; i<EQUIP_INDEX_MAX; i++) {
		if(i == EQUIP_INDEX_ARROW)
			continue;
		idx = sd->equip_index[i];
		if(idx < 0)
			continue;
		if(i == EQUIP_INDEX_RARM && sd->equip_index[EQUIP_INDEX_LARM] == idx)
			continue;
		if(i == EQUIP_INDEX_HEAD3 && sd->equip_index[EQUIP_INDEX_HEAD] == idx)
			continue;
		if(i == EQUIP_INDEX_HEAD2 && (sd->equip_index[EQUIP_INDEX_HEAD3] == idx || sd->equip_index[EQUIP_INDEX_HEAD] == idx))
			continue;

		if(sd->inventory_data[idx]) {
			if(sd->status.inventory[idx].nameid == id)
				n++;

			for(j=0; j<4; j++) {	// カード
				if(sd->status.inventory[idx].card[j] == id)
					n++;
			}
		}
	}

	return n;
}

/*==========================================
 * アイテムソート
 *------------------------------------------
 */
static int pc_comp_item(const void *_i1, const void *_i2)
{
	struct item *i1 = (struct item *)_i1;
	struct item *i2 = (struct item *)_i2;

	// idが0なら末尾に集める
	if(i1->id == 0 && i2->id != 0)
		return 1;
	if(i1->id != 0 && i2->id == 0)
		return -1;

	if(i1->id > i2->id)
		return 1;
	if(i1->id < i2->id)
		return -1;

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
static int pc_setequipindex(struct map_session_data *sd)
{
	int i,j,k;

	nullpo_retr(0, sd);

	for(i=0; i<EQUIP_INDEX_MAX; i++)
		sd->equip_index[i] = -1;

	for(i=0,k=0; i<MAX_INVENTORY && k<sd->inventory_num; i++) {
		if(sd->status.inventory[i].nameid <= 0)
			continue;
		k++;
		if(!sd->status.inventory[i].equip)
			continue;

		for(j=0; j<EQUIP_INDEX_MAX; j++) {
			if(sd->status.inventory[i].equip & equip_pos[j])
				sd->equip_index[j] = i;
		}
		if(sd->status.inventory[i].equip & LOC_RARM) {
			if(sd->inventory_data[i])
				sd->weapontype1 = sd->inventory_data[i]->look;
			else
				sd->weapontype1 = WT_FIST;
		}
		if(sd->status.inventory[i].equip & LOC_LARM) {
			if(sd->inventory_data[i] && itemdb_isweapon(sd->inventory_data[i]->nameid) && sd->status.inventory[i].equip == LOC_LARM)
				sd->weapontype2 = sd->inventory_data[i]->look;
			else
				sd->weapontype2 = WT_FIST;
		}
	}
	pc_calcweapontype(sd);

	return 0;
}

/*==========================================
 * アイテムのindex番号を詰めたり
 * 装備品の装備可能チェックを行なう
 *------------------------------------------
 */
int pc_checkitem(struct map_session_data *sd)
{
	int i,itemid,calc_flag = 0;

	nullpo_retr(0, sd);

	if(battle_config.item_check) {
		// イベントリ内の不正チェック
		for(i=0; i<MAX_INVENTORY; i++) {
			if( (itemid = sd->status.inventory[i].nameid) == 0 )
				continue;
			if( itemdb_available(itemid) )
				continue;
			if( battle_config.error_log )
				printf("illegal item id %d in %d[%s] inventory.\n",itemid,sd->bl.id,sd->status.name);
			if( sd->status.inventory[i].card[0] == (int)0xff00 )
				intif_delete_petdata(*((int *)(&sd->status.inventory[i].card[1])));
			pc_delitem(sd,i,sd->status.inventory[i].amount,3,0);
		}
		// カート内の不正チェック
		for(i=0; i<MAX_CART; i++) {
			if( (itemid = sd->status.cart[i].nameid) == 0 )
				continue;
			if( itemdb_available(itemid) )
				continue;
			if( battle_config.error_log )
				printf("illegal item id %d in %d[%s] cart.\n",itemid,sd->bl.id,sd->status.name);
			if( sd->status.cart[i].card[0] == (int)0xff00 )
				intif_delete_petdata(*((int *)(&sd->status.cart[i].card[1])));
			pc_cart_delitem(sd,i,sd->status.cart[i].amount,1);
		}
	}

	// 変更があったらid順にソートする
	if(sd->state.inventory_dirty) {
		if(sd->inventory_timer) {
			// 使用期限のあるアイテムなら一時的にkeyをidに変えておく
			struct linkdb_node *node = sd->inventory_timer;
			while(node) {
				node->key = UINT2PTR(sd->status.inventory[PTR2INT(node->key)].id);
				node = node->next;
			}
		}
		qsort(sd->status.inventory, MAX_INVENTORY, sizeof(struct item), pc_comp_item);
		sd->state.inventory_dirty = 0;
		sd->inventory_sortkey = 0;
		sd->inventory_num = 0;

		if(sd->inventory_timer) {
			// 使用期限のあるアイテムならidをサーチしてインデックスを再設定
			struct linkdb_node *node = sd->inventory_timer;
			while(node) {
				for(i = 0; i < MAX_INVENTORY; i++) {
					if(sd->status.inventory[i].id == PTR2UINT(node->key)) {
						node->key = INT2PTR(i);
						break;
					}
				}
				if(i >= MAX_INVENTORY) {
					// 何故かインデックスを復元できなかったのでソケット切断する
					if(battle_config.error_log)
						printf("pc_checkitem: broken limit data %d\n", PTR2INT(node->data));
					close(sd->fd);
					return 0;
				}
				node = node->next;
			}
		}
		for(i = 0; i < MAX_INVENTORY; i++) {
			itemid = sd->status.inventory[i].nameid;
			if(itemid > 0) {
				sd->status.inventory[i].id = ++sd->inventory_sortkey;
				if(!sd->inventory_data[i] || sd->inventory_data[i]->nameid != itemid) {
					// 位置が変わったのでデータベースを再設定
					sd->inventory_data[i] = itemdb_search(itemid);
				}
				sd->inventory_num++;
			} else {
				sd->status.inventory[i].id = 0;
				sd->inventory_data[i] = NULL;
			}
		}
	}
	if(sd->state.cart_dirty) {
		qsort(sd->status.cart, MAX_CART, sizeof(struct item), pc_comp_item);
		sd->state.cart_dirty = 0;
		sd->cart_sortkey = 0;

		for(i = 0; i < MAX_CART; i++) {
			itemid = sd->status.cart[i].nameid;
			if(itemid > 0)
				sd->status.cart[i].id = ++sd->cart_sortkey;
			else
				sd->status.cart[i].id = 0;
		}
	}

	// 装備位置チェック
	for(i = 0; i < MAX_INVENTORY; i++)
	{
		if(sd->status.inventory[i].nameid == 0)
			continue;
		if(sd->status.inventory[i].equip & ~pc_equippoint(sd,i)) {
			sd->status.inventory[i].equip = LOC_NOTHING;
			calc_flag = 1;
		}
		// 装備制限チェック
		nullpo_retr(0, sd->inventory_data[i]);
		if(sd->status.inventory[i].equip) {
			if(pc_isequip(sd, i) <= 0) {
				sd->status.inventory[i].equip = LOC_NOTHING;
				calc_flag = 1;
			}
		}
	}

	pc_setequipindex(sd);
	if(calc_flag)
		status_calc_pc(sd,2);

	return 0;
}

/*==========================================
 * PVP順位計算用(foreachinarea)
 *------------------------------------------
 */
static int pc_calc_pvprank_sub(struct block_list *bl,va_list ap)
{
	struct map_session_data *sd1 = NULL, *sd2 = NULL;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, sd1 = (struct map_session_data *)bl);
	nullpo_retr(0, sd2 = va_arg(ap,struct map_session_data *));

	if(sd1->pvp_point > sd2->pvp_point)
		sd2->pvp_rank++;

	return 0;
}

/*==========================================
 * PVP順位計算
 *------------------------------------------
 */
int pc_calc_pvprank(struct map_session_data *sd)
{
	int old;
	struct map_data *m;

	nullpo_retr(0, sd);
	nullpo_retr(0, m = &map[sd->bl.m]);

	old = sd->pvp_rank;

	if( !m->flag.pvp )
		return 0;
	sd->pvp_rank = 1;
	map_foreachinarea(pc_calc_pvprank_sub,sd->bl.m,0,0,m->xs,m->ys,BL_PC,sd);

	if(old != sd->pvp_rank || sd->pvp_lastusers != m->users) {
		sd->pvp_lastusers = m->users;
		clif_pvpset(sd,sd->pvp_rank,sd->pvp_lastusers,0);
	}

	return sd->pvp_rank;
}

/*==========================================
 * PVP順位計算(timer)
 *------------------------------------------
 */
int pc_calc_pvprank_timer(int tid,unsigned int tick,int id,void *data)
{
	struct map_session_data *sd = map_id2sd(id);

	if(sd == NULL)
		return 0;

	sd->pvp_timer = -1;
	if(pc_calc_pvprank(sd) > 0)
		sd->pvp_timer = add_timer(gettick()+PVP_CALCRANK_INTERVAL,pc_calc_pvprank_timer,id,data);
	return 0;
}

/*==========================================
 * sdは結婚しているか(既婚の場合は相方のchar_idを返す)
 *------------------------------------------
 */
int pc_ismarried(struct map_session_data *sd)
{
	nullpo_retr(-1, sd);

	return (sd->status.partner_id > 0)? sd->status.partner_id: 0;
}

/*==========================================
 * sdがdstsdと結婚(dstsd→sdの結婚処理も同時に行う)
 *------------------------------------------
 */
int pc_marriage(struct map_session_data *sd,struct map_session_data *dstsd)
{
	nullpo_retr(-1, sd);
	nullpo_retr(-1, dstsd);

	if(sd->status.partner_id > 0 || dstsd->status.partner_id > 0)
		return -1;

	sd->status.partner_id    = dstsd->status.char_id;
	dstsd->status.partner_id = sd->status.char_id;
	return 0;
}

/*==========================================
 * sdがPCと養子縁組
 *------------------------------------------
 */
int pc_adoption(struct map_session_data* sd,struct map_session_data *parent)
{
	struct map_session_data *parent2;

	if(sd == NULL || parent ==NULL)
		return 0;

	parent2 = pc_get_partner(parent);
	if(parent2)
		return pc_adoption_sub(sd,parent,parent2);

	return 0;
}

/*==========================================
 * sdがpapa mamaと養子縁組
 *------------------------------------------
 */
int pc_adoption_sub(struct map_session_data* sd,struct map_session_data *papa,struct map_session_data *mama)
{
	nullpo_retr(0, sd);

	if(pc_check_adopt_condition(sd, papa, mama, 0)) {
		sd->status.parent_id[0] = papa->status.char_id;
		sd->status.parent_id[1] = mama->status.char_id;
		papa->status.baby_id = sd->status.char_id;
		mama->status.baby_id = sd->status.char_id;

		pc_jobchange(sd,sd->s_class.job,2);

		// 親はWE_BABYを取得するためにスキルツリー再計算
		status_calc_pc(papa,0);
		status_calc_pc(mama,0);
		return 1;
	}
	return 0;
}

/*==========================================
 * 養子縁組条件のチェック
 *------------------------------------------
 */
int pc_check_adopt_condition(struct map_session_data *dstsd, struct map_session_data *sd, struct map_session_data *psd, short flag)
{
	if(dstsd == NULL || sd ==NULL || psd == NULL)
		return 0;

	if(dstsd->status.partner_id > 0) {
		clif_baby_req_fail(sd,2);
		return 0;
	}
	if(dstsd->status.parent_id[0] > 0 || dstsd->status.parent_id[1] > 0)
		return 0;

	if(sd->status.baby_id > 0 || psd->status.baby_id > 0) {
		clif_baby_req_fail(sd,0);
		return 0;
	}
	if(sd->status.partner_id != psd->status.char_id || psd->status.partner_id != sd->status.char_id)
		return 0;

	// 養子チェック
	if(dstsd->s_class.upper != PC_UPPER_NORMAL || (dstsd->s_class.job >= PC_JOB_TK && dstsd->s_class.job <= PC_JOB_DA))
		return 0;
	// パーティー同じマップに３人
	if(party_check_same_map_member_count(dstsd) != 2)
		return 0;

	if(flag) {	// 養子メニューからの場合は詳細にチェック
		int itemid = 0;
		if(dstsd->adopt_invite > 0)
			return 0;
		if(sd->status.base_level < 70 || psd->status.base_level < 70) {
			clif_baby_req_fail(sd,1);
			return 0;
		}

		itemid = (sd->sex == SEX_FEMALE)? WEDDING_RING_F: WEDDING_RING_M;
		if(pc_equippeditem(sd,itemid) < 1)
			return 0;
		itemid = (psd->sex == SEX_FEMALE)? WEDDING_RING_F: WEDDING_RING_M;
		if(pc_equippeditem(psd,itemid) < 1)
			return 0;
	}
	return 1;
}

/*==========================================
 * 養子要請の返答
 *------------------------------------------
 */
void pc_adopt_reply(struct map_session_data *sd,int src_id,int p_id,short flag)
{
	int id;

	nullpo_retv(sd);

	id = sd->adopt_invite;
	sd->adopt_invite = 0;

	if(id == 0 || (id != src_id && id != p_id))
		return;

	if(flag)
		pc_adoption_sub(sd, map_id2sd(src_id), map_id2sd(p_id));
	return;
}

/*==========================================
 * 養子解体処理
 *------------------------------------------
 */
int pc_break_adoption(struct map_session_data *sd)
{
	int b_id, p1_id, p2_id;
	struct map_session_data *baby, *p1, *p2;
	char output[100];

	nullpo_retr(0, sd);

	if(sd->status.baby_id <= 0 && sd->status.parent_id[0] <= 0 && sd->status.parent_id[1] <= 0)
		return 0;

	// %sさんの要望により、養子関係が破棄されました
	snprintf(output, sizeof(output), msg_txt(174), sd->status.name);

	// sdの家族情報を抽出
	if(pc_isbaby(sd)) {
		b_id  = sd->status.char_id;
		p1_id = sd->status.parent_id[0];
		p2_id = sd->status.parent_id[1];

		baby = sd;
		p1   = map_charid2sd(p1_id);
		p2   = map_charid2sd(p2_id);
	} else {
		b_id  = sd->status.baby_id;
		p1_id = sd->status.partner_id;
		p2_id = sd->status.char_id;

		baby = map_charid2sd(b_id);
		p1   = map_charid2sd(p1_id);
		p2   = sd;
	}

	// 解体処理の実行、見つからなければchar鯖に依頼
	if(baby) {		// 子供の離縁
		baby->status.parent_id[0] = 0;
		baby->status.parent_id[1] = 0;
		pc_jobchange(baby,baby->s_class.job,0);
		clif_disp_onlyself(baby->fd, output);
		chrif_save(baby,0);
	} else if(b_id > 0) {
		chrif_req_break_adoption(b_id, sd->status.name);
		chrif_searchcharid(b_id);
	}

	if(p1) {		// 親の離縁
		p1->status.baby_id = 0;
		status_calc_pc(p1,0);	// WE_BABYを破棄するためにスキルツリー再計算
		clif_disp_onlyself(p1->fd, output);
		chrif_save(p1,0);
	} else if(p1_id > 0) {
		chrif_req_break_adoption(p1_id, sd->status.name);
		chrif_searchcharid(p1_id);
	}

	if(p2) {		// もう一人の親の離縁
		p2->status.baby_id = 0;
		status_calc_pc(p2,0);
		clif_disp_onlyself(p2->fd, output);
		chrif_save(p2,0);
	} else if(p2_id > 0) {
		chrif_req_break_adoption(p2_id, sd->status.name);
		chrif_searchcharid(p2_id);
	}

	return 1;
}

/*==========================================
 * sdが離婚(相手はsd->status.partner_idに依る)
 * 相手も同時に離婚・結婚指輪自動剥奪
 *------------------------------------------
 */
int pc_divorce(struct map_session_data *sd)
{
	struct map_session_data *p_sd = NULL;
	int i;

	nullpo_retr(-1, sd);

	if(!pc_ismarried(sd))
		return -1;

	// 相方の離婚処理
	if((p_sd = pc_get_partner(sd)) != NULL) {
		if(p_sd->status.partner_id != sd->status.char_id || sd->status.partner_id != p_sd->status.char_id) {
			printf("pc_divorce: Illegal partner_id sd=%d p_sd=%d\n",sd->status.partner_id,p_sd->status.partner_id);
			return -1;
		}
		p_sd->status.partner_id = 0;
		for(i=0; i<MAX_INVENTORY; i++) {
			if(p_sd->status.inventory[i].nameid == WEDDING_RING_M || p_sd->status.inventory[i].nameid == WEDDING_RING_F) {
				pc_delitem(p_sd,i,1,0,0);
				break;
			}
		}
		clif_divorced(p_sd, sd->status.name);
	} else {
		// 相方が見つからない場合はchar鯖に処理を依頼する
		chrif_reqdivorce(sd->status.partner_id);
		chrif_searchcharid(sd->status.partner_id);	// 名前データ呼び出し
	}

	// 離婚
	sd->status.partner_id = 0;
	for(i=0; i<MAX_INVENTORY; i++) {
		if(sd->status.inventory[i].nameid == WEDDING_RING_M || sd->status.inventory[i].nameid == WEDDING_RING_F) {
			pc_delitem(sd,i,1,0,0);
			break;
		}
	}
	if(p_sd && p_sd->status.name[0])
		clif_divorced(sd, p_sd->status.name);
	else
		clif_divorced(sd, "");

	chrif_save(sd, 0);

	return 0;
}

/*==========================================
 * sdの相方のmap_session_dataを返す
 *------------------------------------------
 */
struct map_session_data *pc_get_partner(struct map_session_data *sd)
{
	nullpo_retr(NULL, sd);

	if(!pc_ismarried(sd))
		return NULL;

	return map_charid2sd(sd->status.partner_id);
}

/*==========================================
 * 装備破壊
 *------------------------------------------
 */
int pc_break_equip(struct map_session_data *sd, int where)
{
	int i;

	nullpo_retr(-1, sd);

	if(sd->unbreakable_equip & where)
		return 0;

	switch(where) {
		case LOC_RARM:
			if((sd->weapontype1 >= WT_1HAXE && sd->weapontype1 <= WT_STAFF) || sd->weapontype1 == WT_BOOK || sd->weapontype1 == WT_2HSTAFF)
				return 0;
			if(sd->sc.data[SC_CP_WEAPON].timer != -1)
				return 0;
			break;
		case LOC_BODY:
			if(sd->sc.data[SC_CP_ARMOR].timer != -1)
				return 0;
			break;
		case LOC_LARM:
			if(sd->equip_index[EQUIP_INDEX_LARM] >= 0 && itemdb_isweapon(sd->inventory_data[sd->equip_index[EQUIP_INDEX_LARM]]->nameid))	// 左手が武器なら
				return 0;
			if(sd->sc.data[SC_CP_SHIELD].timer != -1)
				return 0;
			break;
		case LOC_HEAD2:
			if(sd->sc.data[SC_CP_HELM].timer != -1)
				return 0;
			break;
		default:
			return 0;
	}

	for(i=0; i<MAX_INVENTORY; i++) {
		if(sd->status.inventory[i].equip & where) {
			sd->status.inventory[i].attribute = 1;
			pc_unequipitem(sd,i,0);
			break;
		}
	}
	clif_break_equip(sd,where);
	clif_itemlist(sd);
	clif_equiplist(sd);

	return 0;
}

/*==========================================
 * 装備破壊 部位
 *------------------------------------------
 */
int pc_break_equip2(struct map_session_data *sd,int where)
{
	int idx;

	nullpo_retr(-1, sd);

	switch(where) {
		case EQUIP_INDEX_LACCESSORY: // アクセサリ左
		case EQUIP_INDEX_RACCESSORY:	// アクセサリ右
		case EQUIP_INDEX_SHOES: // 靴
		case EQUIP_INDEX_ROBE:	// 肩
			break;
		case EQUIP_INDEX_HEAD:	// 頭下段
		case EQUIP_INDEX_HEAD3:	// 頭中段
		case EQUIP_INDEX_HEAD2:	// 頭上段
			if(sd->unbreakable_equip & LOC_HEAD2)
				return 0;
			if(sd->sc.data[SC_CP_HELM].timer != -1)
				return 0;
			break;
		case EQUIP_INDEX_BODY:	// 体
			if(sd->unbreakable_equip & LOC_BODY)
				return 0;
			if(sd->sc.data[SC_CP_ARMOR].timer != -1)
				return 0;
			break;
		case EQUIP_INDEX_LARM:	// 左手
			if(sd->equip_index[EQUIP_INDEX_LARM] >= 0 && itemdb_isweapon(sd->inventory_data[sd->equip_index[EQUIP_INDEX_LARM]]->nameid)) {	// 武器
				if(sd->unbreakable_equip & LOC_RARM)
					return 0;
				if(sd->sc.data[SC_CP_WEAPON].timer != -1)
					return 0;
			} else {	// 盾
				if(sd->unbreakable_equip & LOC_LARM)
					return 0;
				if(sd->sc.data[SC_CP_SHIELD].timer != -1)
					return 0;
			}
			break;
		case EQUIP_INDEX_RARM:	// 右手
			if(sd->unbreakable_equip & LOC_RARM)
				return 0;
			if(sd->sc.data[SC_CP_WEAPON].timer != -1)
				return 0;
			break;
		case EQUIP_INDEX_ARROW: // 矢
			break;
		default:
			return -1;
	}
	if((idx = sd->equip_index[where]) >= 0 && sd->status.inventory[idx].equip) {
		sd->status.inventory[idx].attribute = 1;
		pc_unequipitem(sd,idx,0);
	}

	clif_break_equip(sd,where);
	clif_itemlist(sd);
	clif_equiplist(sd);

	return 0;
}

/*==========================================
 * 装備アップグレード
 *------------------------------------------
 */
int pc_upgrade_item(struct map_session_data *sd, int nameid, int idx)
{
	struct item *item_data;
	struct item_data *item;
	int i, del_idx;
	int table = 0;

	nullpo_retr(1, sd);

	if(idx < 0 || idx >= MAX_INVENTORY)
		return 1;

	del_idx = pc_search_inventory(sd,nameid);
	if(del_idx < 0 || del_idx >= MAX_INVENTORY || sd->inventory_data[del_idx] == NULL || sd->status.inventory[del_idx].amount < 1)
		return 1;
	if(sd->status.inventory[idx].equip)
		return 1;

	item_data = &sd->status.inventory[idx];
	item = sd->inventory_data[idx];
	if(item_data->nameid == 0)
		return 1;

	for(i = 0; i < MAX_UPGRADE_LIST; i++) {
		if(item->upgrade[i].nameid == nameid) {
			table = item->upgrade[i].table;
			break;
		}
	}
	if(i >= MAX_UPGRADE_LIST)
		return 1;

	if((!itemdb_isweapon(item_data->nameid) && !itemdb_isarmor(item_data->nameid)) ||	// 装備品じゃない
		sd->status.inventory[idx].identify == 0)	// 未鑑定
		return 1;

	if(table) {
		struct randopt_item_data ro = itemdb_randopt_data(1, table);
		if(ro.nameid) {
			int slot = 0;
			int rate = 0;
			for(i = 0; i < 5; i++) {
				item_data->opt[i].id = 0;
				item_data->opt[i].val = 0;
			}
			for(i = 0; i < sizeof(ro.opt) / sizeof(ro.opt[0]); i++) {
				if(ro.opt[i].slot != slot)
					rate = 0;
				slot = ro.opt[i].slot;
				if(item_data->opt[slot].id > 0)
					continue;
				rate += ro.opt[i].rate;
				if(rate >= atn_rand()%10000) {
					item_data->opt[slot].id = ro.opt[i].optid;
					if(ro.opt[i].optval_plus)
						item_data->opt[slot].val = ro.opt[i].optval_min + (atn_rand() % ((ro.opt[i].optval_max - ro.opt[i].optval_min) / ro.opt[i].optval_plus + 1)) * ro.opt[i].optval_plus;
					else if(ro.opt[i].optval_min != ro.opt[i].optval_max)
						item_data->opt[slot].val = ro.opt[i].optval_min + atn_rand() % (ro.opt[i].optval_max - ro.opt[i].optval_min + 1);
					else
						item_data->opt[slot].val = ro.opt[i].optval_min;
					rate = 0;
				}
			}
			for(i = 0; i < 5-1; i++) {
				if(item_data->opt[i].id == 0) {
					int j;
					for(j = i+1; j < 5; j++) {
						if(item_data->opt[j].id != 0) {
							item_data->opt[i].id = item_data->opt[j].id;
							item_data->opt[i].val = item_data->opt[j].val;
							item_data->opt[j].id = 0;
							item_data->opt[j].val = 0;
							break;
						}
					}
				}
			}
		}
	}
	pc_delitem(sd, del_idx, 1, 0, 0);
	clif_item_preview(sd, idx);

	return 0;
}

/*==========================================
 * 自然回復物
 *------------------------------------------
 */
static unsigned int natural_heal_tick, natural_heal_prev_tick;
static int natural_heal_diff_tick;

/*==========================================
 * HP回復インターバル計算
 *------------------------------------------
 */
static int pc_hpheal(struct map_session_data *sd)
{
	int a;

	nullpo_retr(0, sd);

	// 自然回復停止
	if(sd->hp_recov_stop)
		return 0;

	a = natural_heal_diff_tick;
	if(pc_issit(sd))
		a += a;
	if(sd->sc.data[SC_REGENERATION].timer != -1) {
		switch(sd->sc.data[SC_REGENERATION].val1)
		{
			case 1:
			case 2:
				a += a;
				break;
			case 3:
				a *= 3;
				break;
		}
	}

	return a;
}

/*==========================================
 * SP回復インターバル計算
 *------------------------------------------
 */
static int pc_spheal(struct map_session_data *sd)
{
	int a;

	nullpo_retr(0, sd);

	// 自然回復停止
	if(sd->sp_recov_stop)
		return 0;

	a = natural_heal_diff_tick;
	if(pc_issit(sd))
		a += a;
	if(sd->sc.data[SC_MAGNIFICAT].timer != -1)	// マグニフィカート
		a += a;
	else if(sd->sc.data[SC_SHIELDSPELL_MDEF].timer != -1)	// シールドスペル
		a += a;
	if(sd->sc.data[SC_REGENERATION].timer != -1) {
		switch(sd->sc.data[SC_REGENERATION].val1)
		{
			case 2:
				a += a;
				break;
			case 3:
				a *= 3;
				break;
		}
	}

	return a;
}

/*==========================================
 * HP回復処理
 *------------------------------------------
 */
static int pc_natural_heal_hp(struct map_session_data *sd)
{
	int bhp;
	int inc_num,bonus,hp_flag;

	nullpo_retr(0, sd);

	if(pc_checkoverhp(sd)) {
		sd->regen.hp = sd->regen.hptick = 0;
		return 0;
	}

	bhp = sd->status.hp;
	hp_flag = ((pc_checkskill(sd,SM_MOVINGRECOVERY) > 0 || sd->sc.data[SC_GENTLETOUCH_REVITALIZE].timer != -1) && sd->ud.walktimer != -1);

	if(sd->ud.walktimer == -1) {
		inc_num = pc_hpheal(sd);
		if(sd->sc.data[SC_TENSIONRELAX].timer != -1) {	// テンションリラックス
			sd->regen.hp += 2*inc_num;
			sd->regen.hptick += 3*natural_heal_diff_tick;
		} else {
			sd->regen.hp += inc_num;
			sd->regen.hptick += natural_heal_diff_tick;
		}
	} else if(hp_flag) {
		inc_num = pc_hpheal(sd);
		sd->regen.hp += inc_num;
		sd->regen.hptick = 0;
	} else {
		sd->regen.hp = sd->regen.hptick = 0;
		return 0;
	}

	if(sd->regen.hp >= battle_config.natural_healhp_interval) {
		bonus = sd->nhealhp;
		if(hp_flag) {
			bonus >>= 2;
			if(bonus <= 0)
				bonus = 1;
		}
		while(sd->regen.hp >= battle_config.natural_healhp_interval) {
			sd->regen.hp -= battle_config.natural_healhp_interval;
			if(sd->status.hp + bonus <= sd->status.max_hp) {
				sd->status.hp += bonus;
			} else {
				sd->status.hp = sd->status.max_hp;
				sd->regen.hp = sd->regen.hptick = 0;
			}
		}
	}
	if(bhp != sd->status.hp)
		clif_updatestatus(sd,SP_HP);

	if(sd->nshealhp > 0) {
		if(sd->regen.hptick >= battle_config.natural_heal_skill_interval && sd->status.hp < sd->status.max_hp) {
			bonus = sd->nshealhp;
			while(sd->regen.hptick >= battle_config.natural_heal_skill_interval) {
				sd->regen.hptick -= battle_config.natural_heal_skill_interval;
				if(sd->status.hp + bonus <= sd->status.max_hp) {
					sd->status.hp += bonus;
				} else {
					bonus = sd->status.max_hp - sd->status.hp;
					sd->status.hp = sd->status.max_hp;
					sd->regen.hp = sd->regen.hptick = 0;
				}
				clif_heal(sd->fd,SP_HP,bonus);
			}
		}
	} else {
		sd->regen.hptick = 0;
	}

	return 0;
}

/*==========================================
 * SP回復処理
 *------------------------------------------
 */
static int pc_natural_heal_sp(struct map_session_data *sd)
{
	int bsp;
	int inc_num,bonus;

	nullpo_retr(0, sd);

	if(pc_checkoversp(sd)) {
		sd->regen.sp = sd->regen.sptick = 0;
		return 0;
	}

	bsp = sd->status.sp;

	inc_num = pc_spheal(sd);
	if((sd->s_class.job == PC_JOB_SNV || sd->s_class.job == PC_JOB_ESNV) || sd->sc.data[SC_EXPLOSIONSPIRITS].timer == -1 || sd->sc.data[SC_MONK].timer != -1)
		sd->regen.sp += inc_num;
#ifndef PRE_RENEWAL
	else if(sd->sc.data[SC_EXPLOSIONSPIRITS].timer != -1)
		sd->regen.sp += inc_num / 2;	// 爆裂波動状態はSP自然回復速度が50%
#endif
	if(sd->sc.data[SC_DANCING].timer != -1) {		// ダンス状態ではSPが回復しない
		sd->regen.sp = 0;
		if(pc_checkskill(sd,WM_LESSON) == 0) {		// レッスン習得済みならレッスン効果のみ有効
			sd->regen.sptick = 0;
		}
	}

	if(sd->ud.walktimer == -1)
		sd->regen.sptick += natural_heal_diff_tick;
	else
		sd->regen.sptick = 0;

	if(sd->regen.sp >= battle_config.natural_healsp_interval) {
		bonus = sd->nhealsp;
		while(sd->regen.sp >= battle_config.natural_healsp_interval) {
			sd->regen.sp -= battle_config.natural_healsp_interval;
			if(sd->status.sp + bonus <= sd->status.max_sp) {
				sd->status.sp += bonus;
			} else {
				sd->status.sp = sd->status.max_sp;
				sd->regen.sp = sd->regen.sptick = 0;
			}
		}
	}

	if(bsp != sd->status.sp)
		clif_updatestatus(sd,SP_SP);

	if(sd->nshealsp > 0) {
		if(sd->regen.sptick >= battle_config.natural_heal_skill_interval && sd->status.sp < sd->status.max_sp) {
			bonus = sd->nshealsp;
			if(sd->state.sn_doridori && sd->s_class.job == 23) {
				bonus *= 2;
			}
			sd->state.sn_doridori = 0;
			while(sd->regen.sptick >= battle_config.natural_heal_skill_interval) {
				sd->regen.sptick -= battle_config.natural_heal_skill_interval;
				if(sd->status.sp + bonus <= sd->status.max_sp) {
					sd->status.sp += bonus;
				} else {
					bonus = sd->status.max_sp - sd->status.sp;
					sd->status.sp = sd->status.max_sp;
					sd->regen.sp = sd->regen.sptick = 0;
				}
				clif_heal(sd->fd,SP_SP,bonus);
			}
		}
	} else {
		sd->regen.sptick = 0;
	}

	return 0;
}

/*==========================================
 * 息吹によるHP自然回復
 *------------------------------------------
 */
static int pc_spirit_heal_hp(struct map_session_data *sd)
{
	int interval = battle_config.natural_heal_skill_interval;

	nullpo_retr(0, sd);

	if(pc_checkoverhp(sd)) {
		sd->regen.spirithptick = 0;
		return 0;
	}

	sd->regen.spirithptick += natural_heal_diff_tick;

	if(sd->weight*100/sd->max_weight >= battle_config.natural_heal_weight_rate)
		interval += interval;

	if(sd->regen.spirithptick >= interval) {
		int bonus_hp = sd->nsshealhp;
		while(sd->regen.spirithptick >= interval) {
			if(pc_issit(sd)) {
				sd->regen.spirithptick -= interval;
				if(sd->status.hp < sd->status.max_hp) {
					if(sd->status.hp + bonus_hp <= sd->status.max_hp) {
						sd->status.hp += bonus_hp;
					} else {
						bonus_hp = sd->status.max_hp - sd->status.hp;
						sd->status.hp = sd->status.max_hp;
					}
					clif_heal(sd->fd,SP_HP,bonus_hp);
					sd->regen.spirithptick = 0;
				}
			} else {
				sd->regen.spirithptick -= natural_heal_diff_tick;
				break;
			}
		}
	}

	return 0;
}

/*==========================================
 * 息吹によるSP自然回復
 *------------------------------------------
 */
static int pc_spirit_heal_sp(struct map_session_data *sd)
{
	int interval = battle_config.natural_heal_skill_interval;

	nullpo_retr(0, sd);

	if(pc_checkoversp(sd)) {
		sd->regen.spiritsptick = 0;
		return 0;
	}

	sd->regen.spiritsptick += natural_heal_diff_tick;

	if(sd->weight*100/sd->max_weight >= battle_config.natural_heal_weight_rate)
		interval += interval;

	if(sd->regen.spiritsptick >= interval) {
		int bonus_sp = sd->nsshealsp;
		while(sd->regen.spiritsptick >= interval) {
			if(pc_issit(sd)) {
				sd->regen.spiritsptick -= interval;
				if(sd->status.sp < sd->status.max_sp) {
					if(sd->status.sp + bonus_sp <= sd->status.max_sp) {
						sd->status.sp += bonus_sp;
					} else {
						bonus_sp = sd->status.max_sp - sd->status.sp;
						sd->status.sp = sd->status.max_sp;
					}
					clif_heal(sd->fd,SP_SP,bonus_sp);
					sd->regen.spiritsptick = 0;
				}
			} else {
				sd->regen.spiritsptick -= natural_heal_diff_tick;
				break;
			}
		}
	}

	return 0;
}

/*==========================================
 * 安らかな休息によるHP自然回復
 *------------------------------------------
 */
static int pc_rest_heal_hp(struct map_session_data *sd)
{
	int interval = battle_config.natural_heal_skill_interval;

	nullpo_retr(0, sd);

	if(pc_checkoverhp(sd)) {
		sd->regen.resthptick = 0;
		return 0;
	}

	sd->regen.resthptick += natural_heal_diff_tick;

	//if(sd->weight*100/sd->max_weight >= battle_config.natural_heal_weight_rate)
	//	interval += interval;

	if(sd->regen.resthptick >= interval) {
		int bonus_hp = sd->regen.tk_hp;

		if(sd->state.tk_doridori_hp) {
			bonus_hp += 30;
		}
		sd->state.tk_doridori_hp = 0;

		while(sd->regen.resthptick >= interval) {
			if(pc_issit(sd)) {
				sd->regen.resthptick -= interval;
				if(sd->status.hp < sd->status.max_hp) {
					if(sd->status.hp + bonus_hp <= sd->status.max_hp) {
						sd->status.hp += bonus_hp;
					} else {
						bonus_hp = sd->status.max_hp - sd->status.hp;
						sd->status.hp = sd->status.max_hp;
					}
					clif_heal(sd->fd,SP_HP,bonus_hp);
					sd->regen.resthptick = 0;
				}
			} else {
				sd->regen.resthptick -= natural_heal_diff_tick;
				break;
			}
		}
	}

	return 0;
}

/*==========================================
 * 楽しい休息によるSP自然回復
 *------------------------------------------
 */
static int pc_rest_heal_sp(struct map_session_data *sd)
{
	int interval = battle_config.natural_heal_skill_interval;

	nullpo_retr(0, sd);

	if(pc_checkoversp(sd)) {
		sd->regen.restsptick = 0;
		return 0;
	}

	sd->regen.restsptick += natural_heal_diff_tick;

	//if(sd->weight*100/sd->max_weight >= battle_config.natural_heal_weight_rate)
	//	interval += interval;

	if(sd->regen.restsptick >= interval) {
		int bonus_sp = sd->regen.tk_sp;
		int skilllv;

		if(sd->state.tk_doridori_sp) {
			bonus_sp += 3;
			status_change_start(&sd->bl,SC_HAPPY,pc_checkskill(sd,TK_SPTIME),0,0,0,1800000,0);
			if(atn_rand()%10000 < battle_config.sg_angel_rate) {	// 太陽と月と星の天使
				int i;
				for(i = 0; i < 3; i++) {
					sd->feel_index[i] = -1;
					sd->hate_mob[i]   = -1;
				}
				memset(sd->status.feel_map, 0, sizeof(sd->status.feel_map));
				pc_setglobalreg(sd,"PC_HATE_MOB_SUN",0);
				pc_setglobalreg(sd,"PC_HATE_MOB_MOON",0);
				pc_setglobalreg(sd,"PC_HATE_MOB_STAR",0);
				clif_angel_message(sd);
			}
		}
		sd->state.tk_doridori_sp = 0;

		if((skilllv = pc_checkskill(sd,SL_KAINA)) > 0)
			bonus_sp += bonus_sp*(30+10*skilllv)/100;

		while(sd->regen.restsptick >= interval) {
			if(pc_issit(sd)) {
				sd->regen.restsptick -= interval;
				if(sd->status.sp < sd->status.max_sp) {
					if(sd->status.sp + bonus_sp <= sd->status.max_sp) {
						sd->status.sp += bonus_sp;
					} else {
						bonus_sp = sd->status.max_sp - sd->status.sp;
						sd->status.sp = sd->status.max_sp;
					}
					clif_heal(sd->fd,SP_SP,bonus_sp);
					sd->regen.restsptick = 0;
				}
			} else {
				sd->regen.restsptick -= natural_heal_diff_tick;
				break;
			}
		}
	}

	return 0;
}

/*==========================================
 * HP/SPの自然減少ペナルティ
 *------------------------------------------
 */
static int pc_bleeding(struct map_session_data *sd)
{
	int hp = 0, sp = 0;

	nullpo_retr(0, sd);

	if (sd->hp_penalty_value != 0) {
		sd->hp_penalty_tick += natural_heal_diff_tick;
		if (sd->hp_penalty_tick >= sd->hp_penalty_time) {
			do {
				hp += sd->hp_penalty_value;
				sd->hp_penalty_tick -= sd->hp_penalty_time;
			} while (sd->hp_penalty_tick >= sd->hp_penalty_time);
			sd->hp_penalty_tick = 0;
		}
	}

	if (sd->sp_penalty_value != 0) {
		sd->sp_penalty_tick += natural_heal_diff_tick;
		if (sd->sp_penalty_tick >= sd->sp_penalty_time) {
			do {
				sp += sd->sp_penalty_value;
				sd->sp_penalty_tick -= sd->sp_penalty_time;
			} while (sd->sp_penalty_tick >= sd->sp_penalty_time);
			sd->sp_penalty_tick = 0;
		}
	}

	if (sd->hp_rate_penalty_value != 0) {
		sd->hp_rate_penalty_tick += natural_heal_diff_tick;
		if (sd->hp_rate_penalty_tick >= sd->hp_rate_penalty_time) {
			do {
				hp += sd->status.max_hp * sd->hp_rate_penalty_value / 100;
				sd->hp_rate_penalty_tick -= sd->hp_rate_penalty_time;
			} while (sd->hp_rate_penalty_tick >= sd->hp_rate_penalty_time);
			sd->hp_rate_penalty_tick = 0;
		}
	}

	if (sd->sp_rate_penalty_value != 0) {
		sd->sp_rate_penalty_tick += natural_heal_diff_tick;
		if (sd->sp_rate_penalty_tick >= sd->sp_rate_penalty_time) {
			do {
				sp += sd->status.max_sp * sd->sp_rate_penalty_value / 100;
				sd->sp_rate_penalty_tick -= sd->sp_rate_penalty_time;
			} while (sd->sp_rate_penalty_tick >= sd->sp_rate_penalty_time);
			sd->sp_rate_penalty_tick = 0;
		}
	}

	if(hp) {
		if(sd->status.hp > hp) {
			pc_heal(sd,-hp,0);
		} else {
			sd->status.hp = 0;
			clif_updatestatus(sd,SP_HP);
		}
	}
	if(sp) {
		if(sd->status.sp > sp) {
			pc_heal(sd,0,-sp);
		} else {
			sd->status.sp = 0;
			clif_updatestatus(sd,SP_SP);
		}
	}

	return 0;
}

/*==========================================
 * HP/SP 自然回復 各クライアント
 *------------------------------------------
 */
static int pc_natural_heal_sub(struct map_session_data *sd,va_list ap)
{
	nullpo_retr(0, sd);

	if( (battle_config.natural_heal_weight_rate > 100 || sd->weight*100/sd->max_weight < battle_config.natural_heal_weight_rate) &&
	    !unit_isdead(&sd->bl) &&
	    !pc_ishiding(sd) &&
	    sd->sc.data[SC_POISON].timer == -1 &&	// 毒状態ではHPが回復しない
	    sd->sc.data[SC_BLEED].timer == -1 &&	// 出血状態ではHPが回復しない
	    sd->sc.data[SC_TRICKDEAD].timer == -1 &&	// 死んだふり状態ではHPが回復しない
	    sd->sc.data[SC_GOSPEL].timer == -1 &&	// ゴスペル状態ではHPが回復しない
	    sd->sc.data[SC_BERSERK].timer == -1 &&	// バーサーク状態ではHPが回復しない
	    sd->sc.data[SC_MAGICMUSHROOM].timer == -1 &&	// マジックマッシュルーム状態ではHPが回復しない
	    sd->sc.data[SC_PYREXIA].timer == -1 &&	// パイレックシア状態ではHPが回復しない
	    sd->sc.data[SC_LEECHEND].timer == -1 &&	// リーチエンド状態ではHPが回復しない
	    sd->sc.data[SC_INSPIRATION].timer == -1 &&	// インスピレーション状態はHPが回復しない
	    sd->sc.data[SC_RAISINGDRAGON].timer == -1 &&	// 潜竜昇天状態はHPが回復しない
	    sd->sc.data[SC_SATURDAY_NIGHT_FEVER].timer == -1 &&	// フライデーナイトフィーバー状態ではHPが回復しない
	    sd->sc.data[SC_DIAMONDDUST].timer == -1 &&	//ダイヤモンドダスト状態ではHPが回復しない
	    sd->sc.data[SC_NATURAL_HEAL_STOP].timer == -1 )
	{
		pc_natural_heal_hp(sd);
		if( sd->sc.data[SC_MAXIMIZEPOWER].timer == -1 &&	// マキシマイズパワー状態ではSPが回復しない
		    sd->sc.data[SC_EXTREMITYFIST].timer == -1 &&	// 阿修羅状態ではSPが回復しない
		    sd->sc.data[SC_BERSERK].timer == -1 &&		// バーサーク状態ではSPが回復しない
		    sd->sc.data[SC_ISHA].timer == -1 &&		// バイタリティアクティベーション状態ではSPが回復しない
		    sd->sc.data[SC_WEAPONBLOCKING].timer == -1 &&		// ウェポンブロッキング状態ではSPが回復しない
		    sd->sc.data[SC_TOXIN].timer == -1 &&	// トキシン状態ではSPが回復しない
		    sd->sc.data[SC_OBLIVIONCURSE].timer == -1 &&		// オブリビオンカース状態ではSPが回復しない
		    sd->sc.data[SC_ELECTRICSHOCKER].timer == -1 &&	// エレクトリックショッカー状態ではSPが回復しない
		    sd->sc.data[SC_CAMOUFLAGE].timer == -1 &&		// カモフラージュ状態ではSPが回復しない
		    sd->sc.data[SC_MAGNETICFIELD].timer == -1 &&	// マグネティックフィールド状態ではSPが回復しない
		    sd->sc.data[SC_STEALTHFIELD_USER].timer == -1 &&	// ステルスフィールド(使用者)はSPが回復しない
		    sd->sc.data[SC__REPRODUCE].timer == -1 &&	// リプロデュース状態はSPが回復しない
		    sd->sc.data[SC__SHADOWFORM].timer == -1 &&	// シャドウフォーム状態はSPが回復しない
		    sd->sc.data[SC__INVISIBILITY].timer == -1 &&	// インビジビリティ状態はSPが回復しない
		    sd->sc.data[SC_SIRCLEOFNATURE].timer == -1 &&	// 循環する自然の音状態はSPが回復しない
		    sd->sc.data[SC_SUMMON_ELEM].timer == -1 &&	// サモンエレメンタル状態はSPが回復しない
#ifndef PRE_RENEWAL
		    sd->sc.data[SC_FUSION].timer == -1 &&	// 太陽と月と星の融合状態はSPが回復しない
#endif
		    sd->sc.data[SC_NATURAL_HEAL_STOP].timer == -1 )
			pc_natural_heal_sp(sd);
	} else {
		sd->regen.hp = sd->regen.hptick = 0;
		sd->regen.sp = sd->regen.sptick = 0;
	}
	if(pc_checkskill(sd,MO_SPIRITSRECOVERY) > 0 && !pc_ishiding(sd) && sd->sc.data[SC_POISON].timer == -1) {
		pc_spirit_heal_hp(sd);
		pc_spirit_heal_sp(sd);
	} else {
		sd->regen.spirithptick = 0;
		sd->regen.spiritsptick = 0;
	}

	// 安らかな休息
	if(pc_checkskill(sd,TK_HPTIME) > 0 && sd->state.taekwonrest && sd->sc.data[SC_POISON].timer == -1)
		pc_rest_heal_hp(sd);
	else
		sd->regen.resthptick = 0;

	// 楽しい休息
	if(pc_checkskill(sd,TK_SPTIME) > 0 && sd->state.taekwonrest && sd->sc.data[SC_POISON].timer == -1)
		pc_rest_heal_sp(sd);
	else
		sd->regen.restsptick = 0;

	if (sd->hp_penalty_value != 0 || sd->sp_penalty_value != 0 || sd->hp_rate_penalty_value != 0 || sd->sp_rate_penalty_value != 0)
		pc_bleeding(sd);
	else
		sd->hp_penalty_tick = sd->sp_penalty_tick = sd->hp_rate_penalty_tick = sd->sp_rate_penalty_tick = 0;

	return 0;
}

/*==========================================
 * HP/SP自然回復 (interval timer関数)
 *------------------------------------------
 */
static int pc_natural_heal(int tid,unsigned int tick,int id,void *data)
{
	natural_heal_tick = tick;
	natural_heal_diff_tick = DIFF_TICK(natural_heal_tick,natural_heal_prev_tick);
	clif_foreachclient(pc_natural_heal_sub);

	natural_heal_prev_tick = tick;
	return 0;
}

/*==========================================
 * 自動セーブ 各クライアント
 *------------------------------------------
 */
static int last_save_fd, save_flag;

static int pc_autosave_sub(struct map_session_data *sd,va_list ap)
{
	nullpo_retr(0, sd);

	if(save_flag == 0 && sd->fd > last_save_fd && sd->state.auth && !sd->state.connect_new && !sd->state.waitingdisconnect) {
		intif_save_scdata(sd);

		if(sd->questlist)
			intif_save_quest(sd);
		if(sd->achievelist)
			intif_save_achieve(sd);
		if(sd->status.pet_id > 0 && sd->pd)
			intif_save_petdata(sd->status.account_id,&sd->pet);
		if(sd->status.homun_id > 0 && sd->hd)
			homun_save_data(sd);
		if(sd->status.merc_id > 0 && sd->mcd)
			merc_save_data(sd);
		if(sd->status.elem_id > 0 && sd->eld)
			elem_save_data(sd);
		chrif_save(sd,0);
		if(sd->state.storage_flag == 2)
			storage_guild_storagesave(sd);
		else if(sd->state.storage_flag == 1)
			storage_storage_save(sd);
		save_flag = 1;
		last_save_fd = sd->fd;
	}

	return 1;
}

/*==========================================
 * 自動セーブ (timer関数)
 *------------------------------------------
 */
static int pc_autosave(int tid,unsigned int tick,int id,void *data)
{
	int interval, users;

	save_flag = 0;
	users = clif_foreachclient(pc_autosave_sub);
	if(save_flag == 0)
		last_save_fd = 0;

	interval = autosave_interval/(users+1);
	if(interval <= 200)
		interval = 200;
	if(agit_flag == 1)	// GvG中はインターバルを長く取ることでラグを緩和する
		interval = interval * autosave_gvg_rate / 100;

	add_timer(gettick()+interval,pc_autosave,0,NULL);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
static int gm_account_db_final(void *key,void *data,va_list ap)
{
	struct gm_account *p = (struct gm_account *)data;

	aFree(p);

	return 0;
}

void pc_read_gm_account(void)
{
	char line[8192];
	struct gm_account *p;
	FILE *fp;
	int c, l;
	int account_id, level;
	int i;
	int range, start_range, end_range;

	if (gm_account_db)
		numdb_clear(gm_account_db, gm_account_db_final);
	else
		gm_account_db = numdb_init();

	if ((fp = fopen(GM_account_filename, "r")) == NULL) {
		printf("pc_read_gm_account: open [%s] failed !\n", GM_account_filename);
		return;
	}

	line[sizeof(line)-1] = '\0';
	c = 0;
	l = 0;
	while(fgets(line, sizeof(line)-1, fp)) {
		l++;
		if ((line[0] == '/' && line[1] == '/') || line[0] == '\0' || line[0] == '\n' || line[0] == '\r')
			continue;

		if ((range = sscanf(line, "%d%*[-~]%d %d", &start_range, &end_range, &level)) == 3 ||
		    (range = sscanf(line, "%d%*[-~]%d:%d", &start_range, &end_range, &level)) == 3 ||
		    (range = sscanf(line, "%d %d", &start_range, &level)) == 2 ||
		    (range = sscanf(line, "%d:%d", &start_range, &level)) == 2 ||
		    (range = sscanf(line, "%d: %d", &start_range, &level)) == 2) {
			if (level <= 0) {
				printf("gm_account [%s]: invalid GM level [%ds] line %d\n", GM_account_filename, level, l);
			} else {
				if (level > 99)
					level = 99;
				if (range == 2)
					end_range = start_range;
				else if (end_range < start_range) {
					i = end_range;
					end_range = start_range;
					start_range = i;
				}
				for (account_id = start_range; account_id <= end_range; account_id++) {
					if ((p = (struct gm_account *)numdb_search(gm_account_db, account_id)) == NULL) {
						p = (struct gm_account *)aCalloc(1, sizeof(struct gm_account));
						numdb_insert(gm_account_db, account_id, p);
					}
					p->account_id = account_id;
					p->level = level;
					c++;
					if (dummy_gm_account == 0)
						dummy_gm_account = account_id;	// ダミー用のGMアカウントを設定
				}
			}
		} else {
			printf("gm_account: broken data [%s] line %d\n", GM_account_filename, l);
		}
	}
	fclose(fp);
	//printf("read %s done (%d gm account ID)\n", GM_account_filename, c);

	return;
}

//
// 初期化物
//
/*==========================================
 * 設定ファイル読み込む
 * exp.txt 必要経験値
 * skill_tree.txt 各職毎のスキルツリー
 * attr_fix.txt 属性修正テーブル
 *------------------------------------------
 */
int pc_readdb(void)
{
	int i,j,k,m;
	FILE *fp;
	char line[1024],*p;
	const char *filename;
	const char *filename2[] = {
		"db/skill_tree.txt",
#ifdef PRE_RENEWAL
		"db/pre/skill_tree_pre.txt",
#endif
		"db/addon/skill_tree_add.txt"
	};

	// 必要経験値読み込み
	filename = "db/exp.txt";
	memset(exp_table, 0, sizeof(exp_table));
	fp = fopen(filename, "r");
	if(fp == NULL) {
		printf("pc_readdb: open [%s] failed !\n", filename);
		return 1;
	}
	i = 0;
	while(fgets(line,1020,fp)) {
		atn_bignumber bn,b1,b2,b3,b4,b5,b6,b7,b8,b9,jn,j1,j2,j3,j4,j5,j6,j7,j8,j9,j10,j11;
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0] == '/' && line[1] == '/')
			continue;
		if(sscanf(line, "%" BIGNUMSCANCODE ",%" BIGNUMSCANCODE ",%" BIGNUMSCANCODE ",%" BIGNUMSCANCODE ",%" BIGNUMSCANCODE ","
						"%" BIGNUMSCANCODE ",%" BIGNUMSCANCODE ",%" BIGNUMSCANCODE ",%" BIGNUMSCANCODE ",%" BIGNUMSCANCODE ","
						"%" BIGNUMSCANCODE ",%" BIGNUMSCANCODE ",%" BIGNUMSCANCODE ",%" BIGNUMSCANCODE ",%" BIGNUMSCANCODE ","
						"%" BIGNUMSCANCODE ",%" BIGNUMSCANCODE ",%" BIGNUMSCANCODE ",%" BIGNUMSCANCODE ",%" BIGNUMSCANCODE ",%" BIGNUMSCANCODE ",%" BIGNUMSCANCODE,
						&bn,&b1,&b2,&b3,&b4,&b5,&b6,&b7,&b8,&b9,&jn,&j1,&j2,&j3,&j4,&j5,&j6,&j7,&j8,&j9,&j10,&j11
		) != 22)
			continue;
		exp_table[0][i]  = bn;
		exp_table[1][i]  = b1;
		exp_table[2][i]  = b2;
		exp_table[3][i]  = b3;
		exp_table[4][i]  = b4;
		exp_table[5][i]  = b5;
		exp_table[6][i]  = b6;
		exp_table[7][i]  = b7;
		exp_table[8][i]  = b8;
		exp_table[9][i]  = b9;
		exp_table[10][i] = jn;
		exp_table[11][i] = j1;
		exp_table[12][i] = j2;
		exp_table[13][i] = j3;
		exp_table[14][i] = j4;
		exp_table[15][i] = j5;
		exp_table[16][i] = j6;
		exp_table[17][i] = j7;
		exp_table[18][i] = j8;
		exp_table[19][i] = j9;
		exp_table[20][i] = j10;
		exp_table[21][i] = j11;
		i++;
		if(i >= MAX_LEVEL)
			break;
	}
	fclose(fp);
	printf("read %s done\n", filename);

	// スキルツリー
	memset(skill_tree,0,sizeof(skill_tree));
	for(m = 0; m < sizeof(filename2)/sizeof(filename2[0]); m++) {
		int lineno = 0;
		fp = fopen(filename2[m], "r");
		if(fp == NULL) {
			printf("pc_readdb: open [%s] failed !\n", filename2[m]);
			break;
		}
		while(fgets(line,1020,fp)) {
			char *split[19];
			int upper = 0,skillid;
			struct skill_tree_entry *st;
			int diff=0;

			lineno++;
			if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
				continue;
			if(line[0]=='/' && line[1]=='/')
				continue;
			for(j=0,p=line;j<19 && p;j++) {
				split[j]=p;
				p=strchr(p,',');
				if(p) *p++=0;
			}
			upper = atoi(split[0]);
			if(upper == PC_UPPER_HIGH && battle_config.enable_upper_class == 0)	// confで無効になっていたら
				continue;
			if(upper < 0 || upper >= PC_UPPER_MAX)
				continue;

			i = atoi(split[1]);
			if(i < 0 || i >= PC_JOB_MAX)
				continue;

			if( strcmp(split[2],"clear") == 0 ) {
				memset(skill_tree[upper][i],0,sizeof(skill_tree[0][0]));
				continue;
			}

			if( j != 17 ) {
				if( j != 19 ) {
					printf("skill_tree: invalid param count(%d) line %d\n", j, lineno);
					continue;
				}
				diff = 1;
			}

			skillid = atoi(split[2]);
			if(skillid < 0 || skillid >= MAX_PCSKILL)
				continue;

			st = skill_tree[upper][i];
			for(j=0; st[j].id && st[j].id != skillid; j++);

			if(j >= MAX_SKILL_TREE-1) {
				// 末尾はアンカーとして0にしておく必要がある
				printf("pc_readdb: skill ID %d is over max tree %d!!\n", skillid, MAX_SKILL_TREE);
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
			st[j].max = atoi(split[3]);

			if(st[j].max > skill_get_max(skillid))
				st[j].max = skill_get_max(skillid);

			for(k=0; k<5+diff; k++) {
				st[j].need[k].id = atoi(split[k*2+4]);
				st[j].need[k].lv = atoi(split[k*2+5]);
			}
			if(diff) diff++;
			st[j].base_level  = atoi(split[14+diff]);
			st[j].job_level   = atoi(split[15+diff]);
			st[j].class_level = atoi(split[16+diff]);
		}
		fclose(fp);
		printf("read %s done\n", filename2[m]);
	}
	if(battle_config.baby_copy_skilltree) {
		// 養子のスキルツリーを通常職と同一にする場合
		memcpy(&skill_tree[PC_UPPER_BABY], &skill_tree[PC_UPPER_NORMAL], sizeof(skill_tree[PC_UPPER_NORMAL]));
	}

	// 属性修正テーブル
	for(i=0; i<MAX_ELE_LEVEL; i++) {
		for(j=0; j<ELE_MAX; j++) {
			for(k=0; k<ELE_MAX; k++)
				attr_fix_table[i][j][k] = 100;
		}
	}

#ifdef PRE_RENEWAL
	filename = "db/pre/attr_fix_pre.txt";
#else
	filename = "db/attr_fix.txt";
#endif
	fp = fopen(filename, "r");
	if(fp == NULL) {
		printf("pc_readdb: open [%s] failed !\n", filename);
		return 1;
	}
	while(fgets(line,1020,fp)) {
		char *split[10];
		int lv,n;
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0]=='/' && line[1]=='/')
			continue;
		for(j=0,p=line;j<2 && p;j++) {
			split[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		if(j < 2)
			continue;
		lv = atoi(split[0]);
		n  = atoi(split[1]);

		for(i=0; i<n; ) {
			if( !fgets(line,1020,fp) )
				break;
			if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
				continue;
			if(line[0] == '/' && line[1] == '/')
				continue;

			for(j=0,p=line;j<n && p;j++) {
				while(*p==' ' && *p>0)
					p++;

				if(lv <= 0 || lv > MAX_ELE_LEVEL || i >= ELE_MAX || j >= ELE_MAX)
					break;
				attr_fix_table[lv-1][i][j] = atoi(p);
				if(battle_config.attr_recover == 0 && attr_fix_table[lv-1][i][j] < 0)
					attr_fix_table[lv-1][i][j] = 0;
				p=strchr(p,',');
				if(p) *p++=0;
			}
			i++;
		}
	}
	fclose(fp);
	printf("read %s done\n",filename);

	return 0;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
int do_final_pc(void)
{
	if (gm_account_db) {
		numdb_final(gm_account_db, gm_account_db_final);
		gm_account_db = NULL;
	}

	return 0;
}

/*==========================================
 * pc関係初期化
 *------------------------------------------
 */
int do_init_pc(void)
{
	unsigned int tick = gettick();

	printf("PC_JOB_MAX:%d\n",PC_JOB_MAX);

	pc_readdb();
	pc_read_gm_account();

	add_timer_func_list(pc_natural_heal);
	add_timer_func_list(pc_invincible_timer);
	add_timer_func_list(pc_eventtimer);
	add_timer_func_list(pc_calc_pvprank_timer);
	add_timer_func_list(pc_autosave);
	add_timer_func_list(pc_spiritball_timer);
	add_timer_func_list(pc_coin_timer);
	add_timer_func_list(pc_itemlimit_timer);

	natural_heal_prev_tick = tick + NATURAL_HEAL_INTERVAL;
	add_timer_interval(natural_heal_prev_tick,pc_natural_heal,0,NULL,NATURAL_HEAL_INTERVAL);

	add_timer(tick+autosave_interval,pc_autosave,0,NULL);

	return 0;
}
