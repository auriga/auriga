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
#include "lock.h"
#include "utils.h"

#include "map.h"
#include "chrif.h"
#include "clif.h"
#include "intif.h"
#include "atcommand.h"
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

#define PVP_CALCRANK_INTERVAL 1000	// PVP順位計算の間隔

static int exp_table[16][MAX_LEVEL];

// 属性テーブル
int attr_fix_table[MAX_ELE_LEVEL][ELE_MAX][ELE_MAX];

// JOB TABLE
//        NV,SW,MG,AC,AL,MC,TF,KN,PR,WZ,BS,HT,AS,KNp,CR,MO,SA,RG,AM,BA,DC,CRp,  ,SNV,TK,SG,SG2,SL,GS,NJ,DK,DC
int max_job_table[3][32] = {
	{ 10,50,50,50,50,50,50,50,50,50,50,50,50, 50,50,50,50,50,50,50,50, 50, 1, 99,50,50, 50,50,70,70,70,70 }, // 通常
	{ 10,50,50,50,50,50,50,70,70,70,70,70,70, 70,70,70,70,70,70,70,70, 70, 1, 99,50,50, 50,50,70,70,70,70 }, // 転生
	{ 10,50,50,50,50,50,50,50,50,50,50,50,50, 50,50,50,50,50,50,50,50, 50, 1, 99,50,50, 50,50,70,70,70,70 }, // 養子
};

static unsigned int equip_pos[11] = { 0x0080,0x0008,0x0040,0x0004,0x0001,0x0200,0x0100,0x0010,0x0020,0x0002,0x8000 };

static char GM_account_filename[1024] = "conf/GM_account.txt";
static struct dbt *gm_account_db = NULL;

static struct skill_tree_entry {
	int id;
	int max;
	struct {
		short id,lv;
	} need[5];
	unsigned short base_level;
	unsigned short job_level;
	short class_level;	// 再振り時の不正防止　ノビ:0 一次:1 二次:2
} skill_tree[3][MAX_PC_CLASS][MAX_SKILL_TREE];

static int dummy_gm_account = 0;

#define MOTD_LINE_SIZE 32
static char motd_text[MOTD_LINE_SIZE][256];

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
void pc_set_gm_account_fname(char *str)
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

	nullpo_retr(0, sd);

	if(!unit_isdead(&sd->bl) && (sd->sc.opt1 || sd->sc.opt2))
		return 1;
	if(sd->ud.skilltimer != -1)
		return 1;
	if(DIFF_TICK(tick, sd->ud.canact_tick) < 0)
		return 1;
	if(unit_counttargeted(&sd->bl,0) > 0)
		return 1;
	if(unit_isrunning(&sd->bl))
		return 1;
	if(sd->sc.data[SC_MARIONETTE].timer != -1)
		return 1;
	if(sd->sc.data[SC_DANCING].timer != -1 && sd->sc.data[SC_DANCING].val4) {
		struct skill_unit_group *sg = (struct skill_unit_group *)sd->sc.data[SC_DANCING].val2;
		if(sg && sg->src_id == sd->bl.id)
			return 1;
	}

	return 0;
}

/*==========================================
 * 無敵時間タイマー
 *------------------------------------------
 */
static int pc_invincible_timer(int tid,unsigned int tick,int id,int data)
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
	sd->invincible_timer = add_timer(gettick()+val,pc_invincible_timer,sd->bl.id,0);

	return 0;
}

/*==========================================
 * 無敵時間タイマー削除
 *------------------------------------------
 */
int pc_delinvincibletimer(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	if(sd->invincible_timer != -1) {
		delete_timer(sd->invincible_timer,pc_invincible_timer);
		sd->invincible_timer = -1;
		skill_unit_move(&sd->bl,gettick(),1);
	}

	return 0;
}

/*==========================================
 * 気球タイマー
 *------------------------------------------
 */
static int pc_spiritball_timer(int tid,unsigned int tick,int id,int data)
{
	struct map_session_data *sd = map_id2sd(id);
	int i;

	if(sd == NULL)
		return 1;

	if(sd->spirit_timer[0] != tid) {
		if(battle_config.error_log)
			printf("spirit_timer %d != %d\n",sd->spirit_timer[0],tid);
		return 0;
	}
	sd->spirit_timer[0] = -1;
	for(i=1; i<sd->spiritball; i++) {
		sd->spirit_timer[i-1] = sd->spirit_timer[i];
		sd->spirit_timer[i] = -1;
	}
	sd->spiritball--;
	if(sd->spiritball < 0)
		sd->spiritball = 0;
	clif_spiritball(sd);

	return 0;
}

/*==========================================
 * 気球タイマーセット
 *------------------------------------------
 */
int pc_addspiritball(struct map_session_data *sd,int interval,int max)
{
	nullpo_retr(0, sd);

	if(max > MAX_SKILL_LEVEL)
		max = MAX_SKILL_LEVEL;
	if(sd->spiritball < 0)
		sd->spiritball = 0;

	if(sd->spiritball >= max) {
		int i;
		if(sd->spirit_timer[0] != -1) {
			delete_timer(sd->spirit_timer[0],pc_spiritball_timer);
			sd->spirit_timer[0] = -1;
		}
		for(i=1; i<max; i++) {
			sd->spirit_timer[i-1] = sd->spirit_timer[i];
			sd->spirit_timer[i] = -1;
		}
	} else {
		sd->spiritball++;
	}

	sd->spirit_timer[sd->spiritball-1] = add_timer(gettick()+interval+sd->spiritball,pc_spiritball_timer,sd->bl.id,0);
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

	if(sd->spiritball <= 0) {
		sd->spiritball = 0;
		return 0;
	}

	if(count > sd->spiritball)
		count = sd->spiritball;
	sd->spiritball -= count;
	if(count > MAX_SKILL_LEVEL)
		count = MAX_SKILL_LEVEL;

	for(i=0; i<count; i++) {
		if(sd->spirit_timer[i] != -1) {
			delete_timer(sd->spirit_timer[i],pc_spiritball_timer);
			sd->spirit_timer[i] = -1;
		}
	}
	for(i=count; i<MAX_SKILL_LEVEL; i++) {
		sd->spirit_timer[i-count] = sd->spirit_timer[i];
		sd->spirit_timer[i] = -1;
	}

	if(!type)
		clif_spiritball(sd);

	return 0;
}

/*==========================================
 * コインタイマー
 *-----------------------------------------
 */
static int pc_coin_timer(int tid,unsigned int tick,int id,int data)
{
	struct map_session_data *sd = map_id2sd(id);
	int i;

	if(sd == NULL)
		return 1;

	if(sd->coin_timer[0] != tid) {
		if(battle_config.error_log)
			printf("coin_timer %d != %d\n",sd->coin_timer[0],tid);
		return 0;
	}
	sd->coin_timer[0] = -1;
	for(i=1; i<sd->coin; i++) {
		sd->coin_timer[i-1] = sd->coin_timer[i];
		sd->coin_timer[i] = -1;
	}
	sd->coin--;
	if(sd->coin < 0)
		sd->coin = 0;
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

	if(max > MAX_SKILL_LEVEL)
		max = MAX_SKILL_LEVEL;
	if(sd->coin < 0)
		sd->coin = 0;

	if(sd->coin >= max) {
		int i;
		if(sd->coin_timer[0] != -1) {
			delete_timer(sd->coin_timer[0],pc_coin_timer);
			sd->coin_timer[0] = -1;
		}
		for(i=1; i<max; i++) {
			sd->coin_timer[i-1] = sd->coin_timer[i];
			sd->coin_timer[i] = -1;
		}
	} else {
		sd->coin++;
	}

	sd->coin_timer[sd->coin-1] = add_timer(gettick()+interval+sd->coin,pc_coin_timer,sd->bl.id,0);
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

	if(sd->coin <= 0) {
		sd->coin = 0;
		return 0;
	}

	if(count > sd->coin)
		count = sd->coin;
	sd->coin -= count;
	if(count > MAX_SKILL_LEVEL)
		count = MAX_SKILL_LEVEL;

	for(i=0; i<count; i++) {
		if(sd->coin_timer[i] != -1) {
			delete_timer(sd->coin_timer[i],pc_coin_timer);
			sd->coin_timer[i] = -1;
		}
	}
	for(i=count; i<MAX_SKILL_LEVEL; i++) {
		sd->coin_timer[i-count] = sd->coin_timer[i];
		sd->coin_timer[i] = -1;
	}

	if(!type)
		clif_coin(sd);

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
	if(sd->s_class.job == 0 || map[sd->bl.m].flag.gvg)
		return 0;

	// レディムプティオのペナルティの場合、オーラならば現在の取得経験値から差し引く
	if(battle_config.death_penalty_base > 0) {
		int nextbase;
		if( battle_config.death_penalty_type&2 && ((nextbase = pc_nextbaseexp(sd)) > 0 || !(type&2)) ) {
			loss_base = (atn_bignumber)nextbase;
		} else {
			loss_base = (atn_bignumber)sd->status.base_exp;
		}
		loss_base = loss_base * battle_config.death_penalty_base / 10000 * per / 100;

		if(loss_base) {
			sd->status.base_exp -= (int)loss_base;
			if(sd->status.base_exp < 0)
				sd->status.base_exp = 0;
			if(type&1)
				clif_updatestatus(sd,SP_BASEEXP);
		}
	}

	if(battle_config.death_penalty_job > 0) {
		int nextjob;
		if( battle_config.death_penalty_type&2 && ((nextjob = pc_nextjobexp(sd)) > 0 || !(type&2)) ) {
			loss_job = (atn_bignumber)nextjob;
		} else {
			loss_job = (atn_bignumber)sd->status.job_exp;
		}
		loss_job = loss_job * battle_config.death_penalty_job / 10000 * per / 100;

		if(loss_job) {
			sd->status.job_exp -= (int)loss_job;
			if(sd->status.job_exp < 0)
				sd->status.job_exp = 0;
			if(type&1)
				clif_updatestatus(sd,SP_JOBEXP);
		}
	}

	if(ssd) {
		// PK仕様、PKマップで攻撃が人間かつ自分でない(GXなどの対策)
		if(map[sd->bl.m].flag.pk && sd->bl.id != ssd->bl.id && ranking_get_point(ssd,RK_PK) >= battle_config.pk_murderer_point) {
			if(loss_base > 0 || loss_job > 0)
				pc_gainexp(ssd,NULL,loss_base,loss_job);
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
		if(sd->s_class.job != 0) {	// ノビは既に死亡直後でHP補正済み
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

	// アルケミの連続成功数保存
	if(battle_config.save_am_pharmacy_success && (sd->am_pharmacy_success > 0 || ranking_get_point(sd,RK_ALCHEMIST) > 0))
		pc_setglobalreg(sd,"PC_PHARMACY_SUCCESS_COUNT",sd->am_pharmacy_success);

	// ランキングポイントの保存
	if(battle_config.save_all_ranking_point_when_logout)
		ranking_setglobalreg_all(sd);

	// クローンスキル保存
	if(sd->cloneskill_id || sd->cloneskill_lv) {
		pc_setglobalreg(sd,"PC_CLONESKILL_ID",sd->cloneskill_id);
		pc_setglobalreg(sd,"PC_CLONESKILL_LV",sd->cloneskill_lv);
	}

	// キラー情報保存
	if(battle_config.save_pckiller_type) {
		pc_setglobalreg(sd,"PC_KILL_CHAR",sd->kill_charid);
		pc_setglobalreg(sd,"PC_KILLED_CHAR",sd->killed_charid);
	}

	// ショップポイント保存
	pc_setglobalreg(sd,"PC_SHOP_POINT",sd->shop_point);

	// マナーポイントがプラスだった場合0に
	if(sd->status.manner > 0)
		sd->status.manner = 0;

	// optionのコピー
	sd->status.option = sd->sc.option;

	return 0;
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
}

/*==========================================
 * セーブポイントの保存
 *------------------------------------------
 */
int pc_setsavepoint(struct map_session_data *sd,char *mapname,int x,int y)
{
	nullpo_retr(0, sd);

	strncpy(sd->status.save_point.map,mapname,24);
	sd->status.save_point.map[23] = '\0';	// force \0 terminal
	sd->status.save_point.x = x;
	sd->status.save_point.y = y;

	if(strcmp(sd->status.save_point.map,"SavePoint") != 0 && strstr(sd->status.save_point.map,".gat") == NULL) {
		if(strlen(sd->status.save_point.map) < 20)
			strcat(sd->status.save_point.map,".gat");
	}
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
	int ep = 0;

	nullpo_retr(0, sd);

	if(sd->inventory_data[n]) {
		int look = sd->inventory_data[n]->look;
		ep = sd->inventory_data[n]->equip;
		if(look == 1 || look == 2 || look == 6) {
			if(ep == 2 && (pc_checkskill(sd,AS_LEFT) > 0 || sd->s_class.job == 12))
				return 34;
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
	short card_id;

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
		if(item->equip & 0x0002 && sd->status.base_level >= 96)
		{
			if(sd->sc.data[SC_STRIPWEAPON].timer != -1)
				return 0;
			if(item->wlv >= 4 && item->type == 4)
			{
				// 片手剣 : 1100〜1149
				if(1100 <= item->nameid && item->nameid <= 1149)
					return 1;
				// 短剣   : 1200〜1249
				if(1200 <= item->nameid && item->nameid <= 1249)
					return 1;
				// 短剣   : 13000〜13049?
				if(13000 <= item->nameid && item->nameid <= 13049)
					return 1;
				// 片手斧 : 1300〜1349
				if(1300 <= item->nameid && item->nameid <= 1349)
					return 1;
				// 鈍器   : 1500〜1549
				if(1500 <= item->nameid && item->nameid <= 1549)
					return 1;
				// 杖     : 1600〜1649
				if(1600 <= item->nameid && item->nameid <= 1649)
					return 1;
			}
		}
		// 頭関係
		if(sd->status.base_level >= 90)
		{
			// 一応レベル制限チェック
			if(item->elv > 0 && sd->status.base_level < item->elv)
				return 0;
			// 頭でストリップなら失敗
			if(item->equip & 0x0100 && sd->sc.data[SC_STRIPHELM].timer != -1)
				return 0;
			// 頭なら成功
			// 頭上段
			if(item->equip & 0x0100)
				return 1;
			// 頭中段
			if(item->equip & 0x0200)
				return 1;
			// 頭下段
			if(item->equip & 0x0001)
				return 1;
		}
	}
	if(battle_config.equip_sex) {
		if(item->sex != 2 && sd->sex != item->sex)
			return 0;
	}
	if(item->elv > 0 && sd->status.base_level < item->elv)
		return 0;
	if(((1<<sd->s_class.job)&item->class_) == 0)
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
			if(item->equip & 0x0002)
				return 0;
			if(item->equip & 0x8000)
				return 0;
		} else if(battle_config.casting_penalty_type == 2) {	// 個別
			if(item->equip & 0x0002 && battle_config.casting_penalty_weapon)
				return 0;
			if(item->equip & 0x0020 && battle_config.casting_penalty_shield)
				return 0;
			if(item->equip & 0x0010 && battle_config.casting_penalty_armor)
				return 0;
			if(item->equip & 0x0301 && battle_config.casting_penalty_helm)
				return 0;
			if(item->equip & 0x0004 && battle_config.casting_penalty_robe)
				return 0;
			if(item->equip & 0x0040 && battle_config.casting_penalty_shoes)
				return 0;
			if(item->equip & 0x0088 && battle_config.casting_penalty_acce)
				return 0;
			if(item->equip & 0x8000 && battle_config.casting_penalty_arrow)
				return 0;
			return 0;
		} else if(battle_config.casting_penalty_type == 3) {	// 全て
			return 0;
		}
	}

	if(sd->sc.data[SC_STRIPWEAPON].timer != -1 && item->equip & 0x0002)
		return 0;
	if(sd->sc.data[SC_STRIPSHIELD].timer != -1 && item->equip & 0x0020 && item->type != 4)
		return 0;
	if(sd->sc.data[SC_STRIPARMOR].timer != -1 && item->equip & 0x0010)
		return 0;
	if(sd->sc.data[SC_STRIPHELM].timer != -1 && item->equip & 0x0100)
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
		if(session[sd->new_fd] && ((struct block_list*)session[sd->new_fd])->id == id) {
			clif_authfail_fd(sd->new_fd,2);
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
	sd->weapontype1 = sd->weapontype2 = 0;

	if(sd->status.class_ == PC_CLASS_GS || sd->status.class_ == PC_CLASS_NJ)
		sd->view_class = sd->status.class_ - 4;
	else
		sd->view_class = sd->status.class_;

	sd->s_class = pc_calc_base_job(sd->status.class_);

	sd->speed = DEFAULT_WALK_SPEED;
	sd->dir = 0;
	sd->head_dir = 0;
	sd->state.auth = 1;
	sd->skillitem = -1;
	sd->skillitemlv = -1;
	sd->skillitem_flag = 0;
	sd->invincible_timer = -1;
	sd->view_size = 0;

	sd->trade_partner = 0;

	sd->inchealhptick = 0;
	sd->inchealsptick = 0;
	sd->hp_sub = 0;
	sd->sp_sub = 0;
	sd->inchealspirithptick = 0;
	sd->inchealspiritsptick = 0;

	sd->inchealresthptick = 0;
	sd->inchealrestsptick = 0;

	sd->doridori_counter       = 0;
	sd->tk_doridori_counter_hp = 0;
	sd->tk_doridori_counter_sp = 0;

	sd->spiritball = 0;
	sd->repair_target = 0;

	for(i=0; i<MAX_SKILL_LEVEL; i++)
		sd->spirit_timer[i] = -1;

	for(i=0; i<MAX_SKILL_DB; i++)
		sd->skillstatictimer[i] = tick;

	sd->state.autoloot = (battle_config.item_auto_get)? 1: 0;

	for(i=0; i<5; i++) {
		sd->dev.val1[i] = 0;
		sd->dev.val2[i] = 0;
	}

	sd->emotion_delay_tick = tick;
	sd->item_delay_tick    = tick;
	sd->drop_delay_tick    = tick;
	sd->drop_delay_count   = 0;

	// アカウント変数の送信要求
	intif_request_accountreg(sd);

	// ペット初期化
	sd->petDB = NULL;
	sd->pd = NULL;
	memset(&sd->pet,0,sizeof(struct s_pet));

	// ホム初期化
	sd->hd = NULL;
	memset(&sd->hom,0,sizeof(struct mmo_homunstatus));

	// 傭兵初期化
	sd->mcd = NULL;

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
	sd->sc.opt1  = 0;
	sd->sc.opt2  = 0;
	sd->sc.opt3  = 0;

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

	// ペット、ホム、傭兵データ要求
	if(sd->status.pet_id > 0)
		intif_request_petdata(sd->status.account_id,sd->status.char_id,sd->status.pet_id);
	if(sd->status.homun_id > 0)
		intif_request_homdata(sd->status.account_id,sd->status.char_id,sd->status.homun_id);
	if(sd->status.merc_id > 0)
		intif_request_mercdata(sd->status.account_id,sd->status.char_id,sd->status.merc_id);

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

	unit_dataset(&sd->bl);

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
		sd->kill_charid   = pc_readglobalreg(sd,"PC_KILL_CHAR");
		sd->killed_charid = pc_readglobalreg(sd,"PC_KILLED_CHAR");
	} else {
		sd->kill_charid   = 0;
		sd->killed_charid = 0;
	}

	// ショップポイント
	sd->shop_point = pc_readglobalreg(sd,"PC_SHOP_POINT");

	// ステータス初期計算など
	status_calc_pc(sd,1);

	// クローンスキルの初期化
	if((lv = pc_checkskill2(sd,RG_PLAGIARISM)) > 0) {
		sd->cloneskill_id = pc_readglobalreg(sd,"PC_CLONESKILL_ID");
		sd->cloneskill_lv = pc_readglobalreg(sd,"PC_CLONESKILL_LV");
		if(sd->cloneskill_id > 0 && sd->cloneskill_lv > lv)	// 念のためレベルチェック
			sd->cloneskill_lv = lv;
	} else {
		sd->cloneskill_id = 0;
		sd->cloneskill_lv = 0;
	}

	// MailData
	sd->mail_append.index  = -1;
	sd->mail_append.amount = 0;
	sd->mail_append.zeny   = 0;

	// ホットキーセット
	sd->hotkey_set = 0;

	// Message of the Dayの送信
	for(i = 0; i < MOTD_LINE_SIZE && motd_text[i]; i++) {
		clif_displaymessage(sd->fd, motd_text[i]);
	}

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

	for(i=1; i<MAX_SKILL; i++) {
		if((skill = pc_checkskill2(sd,i)) > 0) {
			if(!(skill_get_inf2(i)&0x01) || battle_config.quest_skill_learn) {
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
		} else if(sd->status.skill_point >= sd->status.job_level && skill_point < 58 && c > 6) {
			switch(c) {
				case 7:
				case 14:
					c = 1;
					break;
				case 8:
				case 15:
					c = 4;
					break;
				case 9:
				case 16:
					c = 2;
					break;
				case 10:
				case 18:
					c = 5;
					break;
				case 11:
				case 19:
				case 20:
					c = 3;
					break;
				case 12:
				case 17:
					c = 6;
					break;
				case 25:
				case 26:
				case 27:
					c = 24;
					break;
				case 28:
				case 29:
					break;
			}
		}
	}

	for(i=0; i<MAX_SKILL; i++) {
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
		for(i=411; i<545; i++)
			sd->status.skill[i].id = i;
#ifdef CLASS_DKDC
		for(i=545; i<619; i++)
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
					for(j=0; j<5 && skill_tree[s][c][i].need[j].id > 0; j++) {
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
#ifdef CLASS_DKDC
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

	return 0;
}

/*==========================================
 * 重量アイコンの確認
 *------------------------------------------
 */
int pc_checkweighticon(struct map_session_data *sd)
{
	int flag;

	nullpo_retr(0, sd);

	flag = (pc_is90overweight(sd)) ? 2 : (pc_is50overweight(sd)) ? 1 : 0;

	if(battle_config.natural_heal_weight_rate_icon && flag != 2) {
		flag = (sd->weight * 100 / sd->max_weight >= battle_config.natural_heal_weight_rate) ? 1 : 0;
	}

	// 変化しないので終了
	if(flag == sd->state.icon_weight)
		return 0;

	if(sd->state.icon_weight == 1)
		clif_status_load(sd,SI_WEIGHT50,0);
	else if(sd->state.icon_weight == 2)
		clif_status_load(sd,SI_WEIGHT90,0);

	if(flag == 1)
		clif_status_load(sd,SI_WEIGHT50,1);
	else if(flag == 2)
		clif_status_load(sd,SI_WEIGHT90,1);

	sd->state.icon_weight = flag;

	return 0;
}

/*==========================================
 * オートスペル
 *------------------------------------------
 */
static int pc_bonus_autospell(struct map_session_data* sd,int skillid,int skilllv,int rate, unsigned long flag)
{
	nullpo_retr(0, sd);

	if(!battle_config.allow_same_autospell) {
		int i;
		for(i=0; i<sd->autospell.count; i++) {
			if(sd->autospell.card_id[i] == current_equip_card_id &&
			   sd->autospell.id[i] == skillid &&
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
	sd->autospell.id[sd->autospell.count]      = skillid;
	sd->autospell.lv[sd->autospell.count]      = skilllv;
	sd->autospell.rate[sd->autospell.count]    = rate;
	sd->autospell.flag[sd->autospell.count]    = flag;
	sd->autospell.card_id[sd->autospell.count] = current_equip_card_id;
	sd->autospell.count++;

	return 0;
}

/*==========================================
 * 装備品による能力等のボーナス設定１
 *------------------------------------------
 */
int pc_bonus(struct map_session_data *sd,int type,int val)
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
			sd->base_atk += val;
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
			sd->matk1 += val;
			sd->matk2 += val;
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
			sd->mdef += val;
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
			sd->attackrange += val;
		else if(sd->state.lr_flag == 1)
			sd->attackrange_ += val;
		else if(sd->state.lr_flag == 2)
			sd->arrow_range += val;
		break;
	case SP_ATTACKRANGE_RATE:
		if(!sd->state.lr_flag)
			sd->attackrange = sd->attackrange * val / 100;
		else if(sd->state.lr_flag == 1)
			sd->attackrange_ = sd->attackrange_ * val / 100;
		else if(sd->state.lr_flag == 2)
			sd->arrow_range = sd->arrow_range * val / 100;
		break;
	case SP_ATTACKRANGE2:
		sd->add_attackrange += val;
		break;
	case SP_ATTACKRANGE_RATE2:
		sd->add_attackrange_rate = (sd->add_attackrange_rate * val)/100;
		break;
	case SP_ADD_SPEED:
		if(sd->state.lr_flag != 2)
			sd->speed -= val;
		break;
	case SP_SPEED_RATE:
		if(sd->state.lr_flag != 2) {
			if(sd->speed_rate > 100-val)
				sd->speed_rate = 100-val;
		}
		break;
	case SP_SPEED_ADDRATE:
		if(sd->state.lr_flag != 2)
			sd->speed_add_rate = sd->speed_add_rate * (100-val)/100;
		break;
	case SP_ASPD:
		if(sd->state.lr_flag != 2)
			sd->aspd -= val*10;
		break;
	case SP_ASPD_RATE:
		if(sd->state.lr_flag != 2) {
			if(sd->aspd_rate > 100-val)
				sd->aspd_rate = 100-val;
		}
		break;
	case SP_ASPD_ADDRATE:
		if(sd->state.lr_flag != 2)
			sd->aspd_add_rate = sd->aspd_add_rate * (100-val)/100;
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
		if(sd->state.lr_flag == 0 && sd->double_rate < val)
			sd->double_rate = val;
		break;
	case SP_DOUBLE_ADD_RATE:
		if(sd->state.lr_flag == 0)
			sd->double_add_rate += val;
		break;
	case SP_MATK_RATE:
		if(sd->state.lr_flag != 2)
			sd->matk_rate += val;
		break;
	case SP_IGNORE_DEF_ELE:
		if(!sd->state.lr_flag)
			sd->ignore_def_ele |= 1<<val;
		else if(sd->state.lr_flag == 1)
			sd->ignore_def_ele_ |= 1<<val;
		break;
	case SP_IGNORE_DEF_RACE:
		if(!sd->state.lr_flag)
			sd->ignore_def_race |= 1<<val;
		else if(sd->state.lr_flag == 1)
			sd->ignore_def_race_ |= 1<<val;
		break;
	case SP_IGNORE_DEF_ENEMY:
		if(!sd->state.lr_flag)
			sd->ignore_def_enemy |= 1<<val;
		else if(sd->state.lr_flag == 1)
			sd->ignore_def_enemy_ |= 1<<val;
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
	case SP_IGNORE_MDEF_ELE:
		if(sd->state.lr_flag != 2)
			sd->ignore_mdef_ele |= 1<<val;
		break;
	case SP_IGNORE_MDEF_RACE:
		if(sd->state.lr_flag != 2)
			sd->ignore_mdef_race |= 1<<val;
		break;
	case SP_IGNORE_MDEF_ENEMY:
		if(sd->state.lr_flag != 2)
			sd->ignore_mdef_enemy |= 1<<val;
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
		if(sd->state.lr_flag != 2)
			sd->special_state.infinite_endure = 1;
		break;
	case SP_UNBREAKABLE_WEAPON:
		if(sd->state.lr_flag != 2)
			sd->unbreakable_equip |= EQP_WEAPON;
		break;
	case SP_UNBREAKABLE_ARMOR:
		if(sd->state.lr_flag != 2)
			sd->unbreakable_equip |= EQP_ARMOR;
		break;
	case SP_UNBREAKABLE_HELM:
		if(sd->state.lr_flag != 2)
			sd->unbreakable_equip |= EQP_HELM;
		break;
	case SP_UNBREAKABLE_SHIELD:
		if(sd->state.lr_flag != 2)
			sd->unbreakable_equip |= EQP_SHIELD;
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
		sd->race = val;
		break;
	case SP_TIGEREYE:
		sd->special_state.infinite_tigereye = 1;
		clif_status_load(sd, SI_TIGEREYE, 1);
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
int pc_bonus2(struct map_session_data *sd,int type,int type2,int val)
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
		if(!sd->state.lr_flag)
			sd->addrace[type2] += val;
		else if(sd->state.lr_flag == 1)
			sd->addrace_[type2] += val;
		else if(sd->state.lr_flag == 2)
			sd->arrow_addrace[type2] += val;
		break;
	case SP_ADDENEMY:
		if(!sd->state.lr_flag)
			sd->addenemy[type2] += val;
		else if(sd->state.lr_flag == 1)
			sd->addenemy_[type2] += val;
		else if(sd->state.lr_flag == 2)
			sd->arrow_addenemy[type2] += val;
		break;
	case SP_ADDSIZE:
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
		if(sd->state.lr_flag != 2)
			sd->subrace[type2] += val;
		break;
	case SP_SUBENEMY:
		if(sd->state.lr_flag != 2)
			sd->subenemy[type2] += val;
		break;
	case SP_ADDEFF:
	case SP_ADDEFFSHORT:
	case SP_ADDEFFLONG:
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
		if(sd->state.lr_flag != 2)
			sd->addeff2[type2] += val;
		else
			sd->arrow_addeff2[type2] += val;
		break;
	case SP_RESEFF:
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
		if(sd->state.lr_flag != 2)
			sd->magic_addrace[type2] += val;
		break;
	case SP_MAGIC_ADDENEMY:
		if(sd->state.lr_flag != 2)
			sd->magic_addenemy[type2] += val;
		break;
	case SP_MAGIC_SUBRACE:
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
			if(i >= sd->add_damage_class_count && sd->add_damage_class_count < 10) {
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
			if(i >= sd->add_damage_class_count_ && sd->add_damage_class_count_ < 10) {
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
			if(i >= sd->add_magic_damage_class_count && sd->add_magic_damage_class_count < 10) {
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
			if(i >= sd->add_def_class_count && sd->add_def_class_count < 10) {
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
			if(i >= sd->add_mdef_class_count && sd->add_mdef_class_count < 10) {
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
		if(sd->state.lr_flag != 2)
			sd->weapon_coma_race2[type2] += val;
		break;
	case SP_WEAPON_ATK:
		if(sd->state.lr_flag != 2)
			sd->weapon_atk[type2] += val;
		break;
	case SP_WEAPON_ATK_RATE:
		if(sd->state.lr_flag != 2)
			sd->weapon_atk_rate[type2] += val;
		break;
	case SP_CRITICALRACE:
		if(type2 == 10) {
			for(i=0; i<10; i++) {
				sd->critical_race[i] += val*10;
			}
		} else if(type2 >= 0 && type2 < 10) {
			sd->critical_race[type2] += val*10;
		}
		break;
	case SP_CRITICALRACERATE:
		if(type2 == 10) {
			for(i=0; i<10; i++) {
				sd->critical_race_rate[i] += val*10;
			}
		} else if(type2 >= 0 && type2 < 10) {
			sd->critical_race_rate[type2] += val*10;
		}
		break;
	case SP_ADDREVEFF:
		if(type2 >= 0 || type2 < 10) {
			sd->addreveff[type2] += val;
			sd->addreveff_flag = 1;
		}
		break;
	case SP_SUB_SIZE:
		if(type2 >= 0 && type2 < 3)
			sd->subsize[type2] += val;
		break;
	case SP_MAGIC_SUB_SIZE:
		if(type2 >= 0 && type2 < 3)
			sd->magic_subsize[type2] += val;
		break;
	case SP_EXP_RATE:
		if(type2 == 10) {
			for(i=0; i<10; i++) {
				sd->exp_rate[i] += val;
			}
		} else if(type2 >= 0 && type2 < 10) {
			sd->exp_rate[type2] += val;
		}
		break;
	case SP_JOB_RATE:
		if(type2 == 10) {
			for(i=0; i<10; i++) {
				sd->job_rate[i] += val;
			}
		} else if(type2 >= 0 && type2 < 10) {
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
		sd->hp_vanish_rate += type2;
		sd->hp_vanish_per  += val;
		break;
	case SP_SPVANISH:
		sd->sp_vanish_rate += type2;
		sd->sp_vanish_per  += val;
		break;
	case SP_RAISE:
		sd->autoraise.hp_per = val;
		sd->autoraise.sp_per = 0;
		sd->autoraise.rate   = type2;
		sd->autoraise.flag   = 0;
		break;
	case SP_BREAK_MYEQUIP_WHEN_ATTACK:
		sd->break_myequip_rate_when_attack[type2] += val;
		sd->loss_equip_flag |= 0x0100;
		break;
	case SP_BREAK_MYEQUIP_WHEN_HIT:
		sd->break_myequip_rate_when_hit[type2] += val;
		sd->loss_equip_flag |= 0x1000;
		break;
	case SP_ETERNAL_STATUS_CHANGE:
		if(type2 >= 0 && type2 < MAX_STATUSCHANGE)
		{
			if(val > 0 && val <= 30000)
				sd->eternal_status_change[type2] = val;
			else sd->eternal_status_change[type2] = 1000;
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
int pc_bonus3(struct map_session_data *sd,int type,int type2,int type3,int val)
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
			if(i >= sd->monster_drop_item_count && sd->monster_drop_item_count < 10) {
				sd->monster_drop_itemid[sd->monster_drop_item_count] = type2;
				sd->monster_drop_race[sd->monster_drop_item_count] |= 1<<type3;
				sd->monster_drop_itemrate[sd->monster_drop_item_count] = val;
				sd->monster_drop_item_count++;
			}
		}
		break;
	case SP_DEF_HP_DRAIN_VALUE:
		if(sd->state.lr_flag != 2) {;
			if(type2 == 10) {
				for(i=0; i<10; i++) {
					sd->hp_drain_rate_race[i]  += type3;
					sd->hp_drain_value_race[i] += val;
				}
			} else if(type2 >= 0 && type2 < 10) {
				sd->hp_drain_rate_race[type2]  += type3;
				sd->hp_drain_value_race[type2] += val;
			}
		}
		break;
	case SP_DEF_SP_DRAIN_VALUE:
		if(sd->state.lr_flag != 2) {
			if(type2 == 10) {
				for(i=0; i<10; i++) {
					sd->sp_drain_rate_race[i]  += type3;
					sd->sp_drain_value_race[i] += val;
				}
			} else if(type2 >= 0 && type2 < 10) {
				sd->sp_drain_rate_race[type2]  += type3;
				sd->sp_drain_value_race[type2] += val;

			}
		}
		break;
	case SP_AUTOSPELL:
		if(sd->state.lr_flag != 2)
			pc_bonus_autospell(sd,type2,type3,val,EAS_TARGET|EAS_SHORT|EAS_LONG|EAS_ATTACK|EAS_NOSP);
		break;
	case SP_AUTOSPELL2:
		if(sd->state.lr_flag != 2)
			pc_bonus_autospell(sd,type2,type3,val,EAS_TARGET|EAS_SHORT|EAS_LONG|EAS_ATTACK|EAS_USEMAX|EAS_NOSP);
		break;
	case SP_AUTOSELFSPELL:
		if(sd->state.lr_flag != 2)
			pc_bonus_autospell(sd,type2,type3,val,EAS_SELF|EAS_SHORT|EAS_LONG|EAS_ATTACK|EAS_NOSP);
		break;
	case SP_AUTOSELFSPELL2:
		if(sd->state.lr_flag != 2)
			pc_bonus_autospell(sd,type2,type3,val,EAS_SELF|EAS_SHORT|EAS_LONG|EAS_ATTACK|EAS_USEMAX|EAS_NOSP);
		break;
	case SP_REVAUTOSPELL:	// 反撃用オートスペル
		if(sd->state.lr_flag != 2)
			pc_bonus_autospell(sd,type2,type3,val,EAS_TARGET|EAS_SHORT|EAS_LONG|EAS_REVENGE|EAS_NOSP);
		break;
	case SP_REVAUTOSPELL2:
		if(sd->state.lr_flag != 2)
			pc_bonus_autospell(sd,type2,type3,val,EAS_TARGET|EAS_SHORT|EAS_LONG|EAS_REVENGE|EAS_USEMAX|EAS_NOSP);
		break;
	case SP_REVAUTOSELFSPELL:
		if(sd->state.lr_flag != 2)
			pc_bonus_autospell(sd,type2,type3,val,EAS_SELF|EAS_SHORT|EAS_LONG|EAS_REVENGE|EAS_NOSP);
		break;
	case SP_REVAUTOSELFSPELL2:
		if(sd->state.lr_flag != 2)
			pc_bonus_autospell(sd,type2,type3,val,EAS_SELF|EAS_SHORT|EAS_LONG|EAS_REVENGE|EAS_USEMAX|EAS_NOSP);
		break;
	case SP_RAISE:
		sd->autoraise.hp_per = type3;
		sd->autoraise.sp_per = val;
		sd->autoraise.rate   = type2;
		sd->autoraise.flag   = 1;
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
int pc_bonus4(struct map_session_data *sd,int type,int type2,int type3,int type4,unsigned long val)
{
	nullpo_retr(0, sd);

	switch(type) {
	case SP_AUTOSPELL:
		if(sd->state.lr_flag != 2)
			pc_bonus_autospell(sd,type2,type3,type4,val);
		break;
	default:
		if(battle_config.error_log)
			printf("pc_bonus4: unknown type %d %d %d %d %lu!\n",type,type2,type3,type4,val);
		break;
	}

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
		    (sd->inventory_data[idx_equip]->type != 4 && sd->inventory_data[idx_equip]->type != 5) ||	// 装備じゃない
		    sd->status.inventory[idx_equip].identify == 0 ||						// 未鑑定
		    itemdb_isspecial(sd->status.inventory[idx_equip].card[0]) ||				// 製造武器・名前入り・ペット
		    (sd->inventory_data[idx_equip]->equip & ep) == 0 ||						// 装備個所違い
		    (sd->inventory_data[idx_equip]->type == 4 && ep == 32) ||					// 両手武器と盾カード
		    (sd->inventory_data[idx_card]->type != 6) ||						// Prevent Hack [Ancyker]
		    sd->status.inventory[idx_equip].equip )
		{
			clif_insert_card(sd, idx_equip, idx_card, 1);	// flag: 1=fail, 0:success
			return;
		}
		for(i=0; i<sd->inventory_data[idx_equip]->slot; i++) {
			if(sd->status.inventory[idx_equip].card[i] == 0) {
				// 空きスロットがあったので差し込む
				sd->status.inventory[idx_equip].card[i] = cardid;

				// カードは減らす
				clif_insert_card(sd, idx_equip, idx_card, 0);	// flag: 1=fail, 0:success
				pc_delitem(sd,idx_card,1,1);
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
 *------------------------------------------
 */
int pc_modifybuyvalue(struct map_session_data *sd,int orig_value)
{
	int skill,val = orig_value;
	int rate1 = 0,rate2 = 0;

	if((skill = pc_checkskill(sd,MC_DISCOUNT)) > 0)		// ディスカウント
		rate1 = 5+skill*2-((skill == 10)? 1: 0);
	if((skill = pc_checkskill(sd,RG_COMPULSION)) > 0)	// コンパルションディスカウント
		rate2 = 5+skill*4;
	if(rate1 < rate2)
		rate1 = rate2;
	if(rate1)
		val = (int)((atn_bignumber)orig_value*(100-rate1)/100);

	if(val < 0) val = 0;
	if(orig_value > 0 && val < 1) val = 1;

	return val;
}

/*==========================================
 * スキルによる売り値修正
 *------------------------------------------
 */
int pc_modifysellvalue(struct map_session_data *sd,int orig_value)
{
	int skill,val = orig_value,rate = 0;

	if((skill = pc_checkskill(sd,MC_OVERCHARGE)) > 0)	// オーバーチャージ
		rate = 5+skill*2-((skill == 10)? 1: 0);
	// マーダラーボーナス
	if(ranking_get_point(sd,RK_PK) >= battle_config.pk_murderer_point)
		rate += 10;
	if(rate)
		val = (int)((atn_bignumber)orig_value*(100+rate)/100);

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

	nullpo_retr(0, sd);

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
static int pc_itemlimit_timer(int tid, unsigned int tick, int id, int data)
{
	struct map_session_data *sd = map_id2sd(id);
	struct linkdb_node *node;
	unsigned int now;

	if(sd == NULL)
		return 0;

	now  = (unsigned int)time(NULL);
	node = sd->inventory_timer;

	while(node) {
		if(tid == (int)node->data - 1) {
			tid = pc_checkitemlimit(sd, (int)node->key, tick, now, 0);
			if(tid > 0) {
				node->data = (void*)tid;
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
		return 0;

	if(sd->status.inventory[idx].limit > now) {
		// まだ時間になってないのでタイマーを継続する
		unsigned int diff = sd->status.inventory[idx].limit - now;
		if(diff > 3600)
			diff = 3600;
		return add_timer(tick + diff * 1000, pc_itemlimit_timer, sd->bl.id, 0) + 1;	// 0とNULLが被るので+1しておく
	}

	// 時間切れにより削除
	if(sd->status.inventory[idx].card[0] == (short)0xff00) {
		intif_delete_petdata(*((long *)(&sd->status.inventory[idx].card[1])));
	}
	if(first) {
		pc_delitem(sd, idx, sd->status.inventory[idx].amount, 3);
	} else {
		char output[256];
		struct item_data *data = sd->inventory_data[idx];

#if PACKETVER >= 9
		if(itemdb_isequip2(data)) {
			// 強化装備アイテムの削除
			pc_delitem(sd, idx, sd->status.inventory[idx].amount, 1);
			clif_delitem_timeout(sd, idx, ((data->view_id > 0)? data->view_id: data->nameid));
			return 0;
		}
#endif
		// 通常アイテムの使用期限切れ削除
		pc_delitem(sd, idx, sd->status.inventory[idx].amount, 0);
		snprintf(output, sizeof(output), msg_txt(187), ((data->view_id > 0)? itemdb_jname(data->view_id): data->jname));
		clif_disp_onlyself(sd->fd, output);
	}

	return 0;
}

/*==========================================
 * アイテム使用期限のセット
 *------------------------------------------
 */
static int pc_setitemlimit(struct map_session_data *sd)
{
	int i;
	unsigned int now  = (unsigned int)time(NULL);
	unsigned int tick = gettick();

	nullpo_retr(0, sd);

	for(i = 0; i < MAX_INVENTORY; i++) {
		if(sd->status.inventory[i].nameid > 0 && sd->status.inventory[i].limit > 0) {
			int tid = pc_checkitemlimit(sd, i, tick, now, 1);
			if(tid > 0)
				linkdb_insert(&sd->inventory_timer, (void*)i, (void*)tid);
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
		delete_timer((int)node->data - 1, pc_itemlimit_timer);
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
	clif_additem(sd,i,amount,0);
	clif_updatestatus(sd,SP_WEIGHT);

	if(sd->status.inventory[i].limit > 0) {
		int tid = pc_checkitemlimit(sd, i, gettick(), (unsigned int)time(NULL), 0);
		if(tid > 0)
			linkdb_insert(&sd->inventory_timer, (void*)i, (void*)tid);
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
	pc_delitem(sd,n,1,type);
	return 0;
}

/*==========================================
 * アイテムを減らす
 *------------------------------------------
 */
void pc_delitem(struct map_session_data *sd, int n, int amount, int type)
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
			int tid = (int)linkdb_erase(&sd->inventory_timer, (void*)n);
			if(tid > 0)
				delete_timer(tid - 1, pc_itemlimit_timer);
		}
		memset(&sd->status.inventory[n],0,sizeof(sd->status.inventory[0]));
		sd->inventory_data[n] = NULL;
	}
	if(!(type&1))
		clif_delitem(sd,n,amount);
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
		pc_delitem(sd,n,amount,0);
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

	if(unit_distance(fitem->bl.x,fitem->bl.y,sd->bl.x,sd->bl.y) > 2)
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
	if(item->type != 0 && item->type != 2 && item->type != 18)
		return 0;

	if(item->sex != 2 && sd->sex != item->sex)
		return 0;
	if(item->elv > 0 && sd->status.base_level < item->elv)
		return 0;
	if(((1<<sd->s_class.job)&item->class_) == 0)
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

	nullpo_retv(sd);

	if(n < 0 || n >= MAX_INVENTORY)
		return;

	item   = sd->inventory_data[n];
	nameid = sd->status.inventory[n].nameid;
	amount = sd->status.inventory[n].amount;

	if(nameid <= 0 || amount <= 0 || !pc_isUseitem(sd,n)) {
		clif_useitemack(sd,n,0,0);
		return;
	}
	sd->use_itemid = nameid;
	if(sd->status.inventory[n].card[0] == 0x00fe)
		sd->use_nameditem = *((unsigned long *)(&sd->status.inventory[n].card[2]));
	else
		sd->use_nameditem = 0;

	if(battle_config.item_res) {
		if(sd->sc.data[SC_HAPPY].timer != -1 &&
		   (nameid == 686 || nameid == 687) &&
		   sd->status.sp >= 10 &&
		   atn_rand()%100 >= 11 - sd->sc.data[SC_HAPPY].val1) {
			// 楽しい状態なら確率的にアーススパイクスクロールの消費無し
			sd->status.sp -= 10;
			clif_updatestatus(sd,SP_SP);
			clif_useitemack(sd,n,amount,1);
		} else {
			clif_useitemack(sd,n,amount-1,1);
			pc_delitem(sd,n,1,1);
		}
	} else {
		clif_useitemack(sd,n,amount,1);
	}

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
			   sd->status.cart[i].card[3] == item_data->card[3])
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
		pc_delitem(sd, idx, amount, 0);

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
	clif_additem(sd,0,0,flag);

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
	char output[200];
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
			snprintf(output, sizeof(output), msg_txt(136), sd->status.name);
		else
			snprintf(output, sizeof(output), msg_txt(137), sd->status.name, item->jname);
	} else {
		snprintf(output, sizeof(output), msg_txt(138), sd->status.name);
	}
	clif_displaymessage(fd, output);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int pc_steal_item(struct map_session_data *sd,struct mob_data *md)
{
	int i,skill,rate,itemid,flag;

	nullpo_retr(0, sd);
	nullpo_retr(0, md);

	if(battle_config.item_rate <= 0 || md->state.steal_flag)
		return 0;
	if(mob_db[md->class_].mexp > 0 || mob_db[md->class_].mode&0x20)
		return 0;
	if(md->sc.data[SC_STONE].timer != -1 || md->sc.data[SC_FREEZE].timer != -1)
		return 0;

	skill = (sd->paramc[4] - mob_db[md->class_].dex)/2 + pc_checkskill(sd,TF_STEAL) * 6 + 10;
	if(skill > 0) {
		for(i=0; i<ITEM_DROP_COUNT-1; i++) {
			itemid = mob_db[md->class_].dropitem[i].nameid;
			if(itemid > 0 && itemdb_type(itemid) != 6) {
				rate = mob_db[md->class_].dropitem[i].p * skill * battle_config.steal_rate / 10000 + 1;
				if(sd->add_steal_rate > 0)
					rate *= sd->add_steal_rate/100;

				if(battle_config.battle_log)
					printf("skill=%d, mob base=%d, rate=%d, bc.rate=%d, add=%d\n",
						skill, mob_db[md->class_].dropitem[i].p, rate, battle_config.steal_rate, sd->add_steal_rate );

				if(atn_rand()%10000 < rate) {
					struct item tmp_item;
					memset(&tmp_item,0,sizeof(tmp_item));
					tmp_item.nameid = itemid;
					tmp_item.amount = 1;
					tmp_item.identify = !itemdb_isequip3(itemid);
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
	int rate,skill;

	nullpo_retr(0, sd);
	nullpo_retr(0, md);

	if(md->state.steal_coin_flag)
		return 0;
	if(md->sc.data[SC_STONE].timer != -1 || md->sc.data[SC_FREEZE].timer != -1)
		return 0;

	skill = pc_checkskill(sd,RG_STEALCOIN)*10;
	rate  = skill + (sd->status.base_level - mob_db[md->class_].lv)*3 + sd->paramc[4]*2 + sd->paramc[5]*2;

	if(atn_rand()%1000 < rate) {
		pc_getzeny(sd,mob_db[md->class_].lv*10 + atn_rand()%100);
		md->state.steal_coin_flag = 1;
		return 1;
	}

	return 0;
}

/*==========================================
 * PCの位置設定
 *------------------------------------------
 */
int pc_setpos(struct map_session_data *sd,const char *mapname_org,int x,int y,int clrtype)
{
	char mapname[24];
	int m, move_flag = 0;

	nullpo_retr(1, sd);

	strncpy(mapname,mapname_org,16);
	mapname[16] = 0;
	if(strstr(mapname,".gat") == NULL && strlen(mapname) < 16) {
		strcat(mapname,".gat");
	}

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
			unit_free(&sd->bl,clrtype);
			memcpy(sd->status.last_point.map,mapname,24);
			sd->status.last_point.x = x;
			sd->status.last_point.y = y;
			chrif_save(sd, 1);
			chrif_changemapserver(sd,mapname,x,y,ip,port);
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
				printf("stacked (%d,%d)\n",x,y);
		}
		do {
			x = atn_rand()%(map[m].xs-2)+1;
			y = atn_rand()%(map[m].ys-2)+1;
		} while(map_getcell(m,x,y,CELL_CHKNOPASS) && (i++) < 1000);
		if(i >= 1000) {
			if(battle_config.error_log)
				printf("pc_setpos: not found free cell!!\n");
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
	}
	status_change_hidden_end(&sd->bl);

	// 温もりユニット削除
	if(sd->sc.data[SC_WARM].timer != -1)
		status_change_end(&sd->bl, SC_WARM, -1);

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
		clif_changemap(sd,map[m].name,x,y);
	}

	memcpy(sd->mapname,mapname,24);
	sd->bl.m = m;
	sd->bl.x = x;
	sd->bl.y = y;

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
			clif_status_change(&sd->bl,SI_RUN_STOP,1);
			pc_setdir(sd, dir, head_dir);
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

	if(skill_id < 0 || skill_id >= MAX_SKILL)
		return 0;

	if(sd->cloneskill_id > 0 && skill_id == sd->cloneskill_id)
		return (sd->cloneskill_lv > sd->status.skill[skill_id].lv ? sd->cloneskill_lv : sd->status.skill[skill_id].lv);

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

	if(skill_id < 0 || skill_id >= MAX_SKILL)
		return 0;

	if(sd->status.skill[skill_id].id == skill_id)
		return sd->status.skill[skill_id].lv;

	return 0;
}

/*==========================================
 * 武器変更によるスキルの継続チェック
 *------------------------------------------
 */
static int pc_checkallowskill(struct map_session_data *sd)
{
	int i, mask;
	const int skill_list[] = {
		KN_TWOHANDQUICKEN,
		KN_ONEHAND,
		LK_AURABLADE,
		LK_PARRYING,
		LK_CONCENTRATION,
		CR_SPEARQUICKEN,
		BS_ADRENALINE,
		BS_ADRENALINE2,
		GS_GATLINGFEVER,
	};

	nullpo_retr(0, sd);

	if( sd->sc.count <= 0 )
		return 0;

	mask = 1 << sd->status.weapon;

	// 武器が合わないならステータス異常を解除
	for(i=0; i < sizeof(skill_list)/sizeof(skill_list[0]); i++) {
		int type = SkillStatusChangeTable[skill_list[i]];
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

	for(i=0; i<11; i++) {
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

	if(b_class <= PC_CLASS_SNV || b_class == PC_CLASS_GS || b_class == PC_CLASS_NJ) {
		bj.job   = b_class;
		bj.upper = 0;
	}
	else if(b_class >= PC_CLASS_BASE2 && b_class < PC_CLASS_BASE3) {
		bj.job   = b_class - PC_CLASS_BASE2;
		bj.upper = 1;
	}
	else if(b_class >= PC_CLASS_BASE3 && b_class < PC_CLASS_SNV3) {
		bj.job   = b_class - PC_CLASS_BASE3;
		bj.upper = 2;
	}
	else if(b_class == PC_CLASS_SNV3) {
		bj.job   = 23;
		bj.upper = 2;
	}
	else if(b_class >= PC_CLASS_TK && b_class <= PC_CLASS_SL) {	// テコン〜
		bj.job   = 24 + b_class - PC_CLASS_TK;
		bj.upper = 0;
	}
	else if(b_class == PC_CLASS_DK || b_class == PC_CLASS_DC) {
		bj.job   = 30 + b_class - PC_CLASS_DK;
		bj.upper = 0;
	}

	if(battle_config.enable_upper_class == 0)	// confで無効になっていたらupper=0
		bj.upper = 0;

	if(bj.job == 0)
		bj.type = 0;
	else if(bj.job < 7 || bj.job == 24 || bj.job >= 28)
		bj.type = 1;
	else if(bj.job == 23)
		bj.type = 3;
	else
		bj.type = 2;

	return bj;
}

/*==========================================
 * 元の職業からクラスIDを返す
 *------------------------------------------
 */
int pc_calc_class_job(int job,int upper)
{
	if(job < 0 || job >= MAX_VALID_PC_CLASS)
		return 0;

	// upperに無関係な職
	if(job == 22 || job == 26)
		return job;
	if(job >= 24 && job <= 27)
		return job - 24 + PC_CLASS_TK;
	if(job == PC_CLASS_GS)
		return 24;
	if(job == PC_CLASS_NJ)
		return 25;
	if(job == 30)
		return PC_CLASS_DK;
	if(job == 31)
		return PC_CLASS_DC;

	// スパノビは養子か通常の2択
	if(job == PC_CLASS_SNV) {
		if(upper == 2)
			return PC_CLASS_SNV3;
		else
			return PC_CLASS_SNV;
	}

	if(upper == 0)
		return job;
	if(upper == 1)
		return job + PC_CLASS_BASE2;
	if(upper == 2)
		return job + PC_CLASS_BASE3;

	return 0;
}

/*==========================================
 * Baseレベルアップ
 *------------------------------------------
 */
static int pc_checkbaselevelup(struct map_session_data *sd)
{
	int next;

	nullpo_retr(0, sd);

	next = pc_nextbaseexp(sd);

	if(sd->status.base_exp >= next && next > 0) {
		// base側レベルアップ処理
		sd->status.base_exp -= next;
		sd->status.base_level++;
		sd->status.status_point += (sd->status.base_level+14) / 5;
		clif_updatestatus(sd,SP_STATUSPOINT);
		clif_updatestatus(sd,SP_BASELEVEL);
		clif_updatestatus(sd,SP_NEXTBASEEXP);

		status_calc_pc_stop_begin(&sd->bl);

		status_calc_pc(sd,0);
		pc_heal(sd,sd->status.max_hp,sd->status.max_sp);

		// スパノビはキリエ、イムポ、マニピ、グロ、サフラがかかる
		if(sd->s_class.job == 23) {
			status_change_start(&sd->bl,SkillStatusChangeTable[PR_KYRIE],10,0,0,0,120000,0);
			status_change_start(&sd->bl,SkillStatusChangeTable[PR_IMPOSITIO],5,0,0,0,120000,0);
			status_change_start(&sd->bl,SkillStatusChangeTable[PR_MAGNIFICAT],5,0,0,0,120000,0);
			status_change_start(&sd->bl,SkillStatusChangeTable[PR_GLORIA],5,0,0,0,120000,0);
			status_change_start(&sd->bl,SkillStatusChangeTable[PR_SUFFRAGIUM],3,0,0,0,120000,0);
			clif_misceffect(&sd->bl,7);	// スパノビ天使
		}
		else if(sd->s_class.job >= 24 && sd->s_class.job <= 27) {
			status_change_start(&sd->bl,SkillStatusChangeTable[AL_BLESSING],10,0,0,0,600000,0);
			status_change_start(&sd->bl,SkillStatusChangeTable[AL_INCAGI],10,0,0,0,600000,0);
			clif_misceffect(&sd->bl,9);	// テコン系天使
		}
		else {
			clif_misceffect(&sd->bl,0);
		}

		status_calc_pc_stop_end(&sd->bl);

		// レベルアップしたのでパーティー情報を更新する（公平範囲チェック）
		party_send_movemap(sd);
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
	int next;

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
		if(sd->status.class_ == 23)
			clif_misceffect(&sd->bl,8);
		else
			clif_misceffect(&sd->bl,1);
		return 1;
	}

	return 0;
}

/*==========================================
 * 経験値取得
 *------------------------------------------
 */
int pc_gainexp(struct map_session_data *sd, struct mob_data *md, atn_bignumber base_exp, atn_bignumber job_exp)
{
	nullpo_retr(0, sd);

	if (sd->bl.prev == NULL || unit_isdead(&sd->bl))
		return 0;

	if (md) {
		int race_id = status_get_race(&md->bl);
		int tk_exp_rate = 0;

		if (sd->sc.data[SC_MIRACLE].timer != -1) { // 太陽と月と星の奇跡
			tk_exp_rate = 20 * pc_checkskill(sd, SG_STAR_BLESS);
		} else {                                  // 太陽の祝福、月の祝福、星の祝福
			if ((battle_config.allow_skill_without_day || is_day_of_sun()) && md->class_ == sd->hate_mob[0])
				tk_exp_rate = 10 * pc_checkskill(sd, SG_SUN_BLESS);
			else if ((battle_config.allow_skill_without_day || is_day_of_moon()) && md->class_ == sd->hate_mob[1])
				tk_exp_rate = 10 * pc_checkskill(sd, SG_MOON_BLESS);
			else if ((battle_config.allow_skill_without_day || is_day_of_star()) && md->class_ == sd->hate_mob[2])
				tk_exp_rate = 20 * pc_checkskill(sd, SG_STAR_BLESS);
		}

		base_exp = base_exp * (100 + sd->exp_rate[race_id] + tk_exp_rate) / 100;
		job_exp  = job_exp  * (100 + sd->job_rate[race_id] + tk_exp_rate) / 100;

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
		base_exp = base_exp * sd->sc.data[SC_COMBATHAN].val1 / 100;
		job_exp  = job_exp  * sd->sc.data[SC_COMBATHAN].val1 / 100;
	}

	if (sd->status.guild_id > 0) {	// ギルドに上納
		base_exp -= guild_payexp(sd, base_exp);
		if (base_exp < 0)
			base_exp = 0;
	}

	if (battle_config.disp_experience && (base_exp || job_exp)) {
		char output[128];
		int bexp = (base_exp > 0x7fffffff)? 0x7fffffff: (int)base_exp;
		int jexp = (job_exp  > 0x7fffffff)? 0x7fffffff: (int)job_exp;
		snprintf(output, sizeof output, msg_txt(131), bexp, jexp);
		clif_disp_onlyself(sd->fd, output);
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
				sd->status.base_exp = (int)next;
				pc_checkbaselevelup(sd);
				next = pc_nextbaseexp(sd);
			}
		}
		if (next > 0 && battle_config.next_exp_limit > 0 && (base_exp * 100 / next) > per)
			sd->status.base_exp = (int)(next * per / 100);
		else if (base_exp + sd->status.base_exp > 0x7fffffff)
			sd->status.base_exp = 0x7fffffff;
		else
			sd->status.base_exp += (int)base_exp;

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
				sd->status.job_exp = (int)next;
				pc_checkjoblevelup(sd);
				next = pc_nextjobexp(sd);
			}
		}
		if (next > 0 && battle_config.next_exp_limit > 0 && (job_exp * 100 / next) > per)
			sd->status.job_exp = (int)(next * per / 100);
		else if (job_exp + sd->status.job_exp > 0x7fffffff)
			sd->status.job_exp = 0x7fffffff;
		else
			sd->status.job_exp += (int)job_exp;

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
int pc_nextbaseexp(struct map_session_data *sd)
{
	int i;

	nullpo_retr(0, sd);

	if(sd->status.base_level >= MAX_LEVEL || sd->status.base_level <= 0)
		return 0;

	if(sd->status.class_ == 0)                         i = 0;	// ノービス
	else if(sd->status.class_ <= 6)                    i = 1;	// 一次職
	else if(sd->status.class_ <= 22)                   i = 2;	// 二次職
	else if(sd->status.class_ == 23)                   i = 3;	// スーパーノービス
	else if(sd->status.class_ == PC_CLASS_GS)          i = 3;	// ガンスリンガー
	else if(sd->status.class_ == PC_CLASS_NJ)          i = 3;	// 忍者
	else if(sd->status.class_ == PC_CLASS_DK)          i = 3;	// デスナイト
	else if(sd->status.class_ == PC_CLASS_DC)          i = 3;	// ダークコレクター
	else if(sd->status.class_ == PC_CLASS_BASE2)       i = 4;	// 転生ノービス
	else if(sd->status.class_ <= PC_CLASS_BASE2 + 6)   i = 5;	// 転生一次職
	else if(sd->status.class_ <= PC_CLASS_BASE2 + 21)  i = 6;	// 転生二次職
	else if(sd->status.class_ == PC_CLASS_BASE3)       i = 0;	// 養子ノビ
	else if(sd->status.class_ <= PC_CLASS_BASE3 + 6)   i = 1;	// 養子一次
	else if(sd->status.class_ <= PC_CLASS_BASE3 + 21)  i = 2;	// 養子二次
	else if(sd->status.class_ == PC_CLASS_SNV3)        i = 3;	// 養子スパノビ
	else if(sd->status.class_ <= PC_CLASS_SL)          i = 1;	// 追加職 転生前の値
	else                                               i = 1;	// それ以外なら転生前

	return exp_table[i][sd->status.base_level-1];
}

/*==========================================
 * job level側必要経験値計算
 *------------------------------------------
 */
int pc_nextjobexp(struct map_session_data *sd)
{
	int i;

	nullpo_retr(0, sd);

	if(sd->status.job_level >= MAX_LEVEL || sd->status.job_level <= 0)
		return 0;

	if(sd->status.class_ == 0)                        i = 7;	// ノービス
	else if(sd->status.class_ <= 6)                   i = 8;	// 一次職
	else if(sd->status.class_ <= 22)                  i = 9;	// 二次職
	else if(sd->status.class_ == 23)                  i = 10;	// スーパーノービス
	else if(sd->status.class_ == PC_CLASS_GS)         i = 15;	// ガンスリンガー
	else if(sd->status.class_ == PC_CLASS_NJ)         i = 15;	// 忍者
	else if(sd->status.class_ == PC_CLASS_DK)         i = 15;	// デスナイト
	else if(sd->status.class_ == PC_CLASS_DC)         i = 15;	// ダークコレクター
	else if(sd->status.class_ == PC_CLASS_BASE2)      i = 11;	// 転生ノービス
	else if(sd->status.class_ <= PC_CLASS_BASE2 + 6)  i = 12;	// 転生一次職
	else if(sd->status.class_ <= PC_CLASS_BASE2 + 21) i = 13;	// 転生二次職
	else if(sd->status.class_ == PC_CLASS_BASE3)      i = 7;	// 養子ノビ
	else if(sd->status.class_ <= PC_CLASS_BASE3 + 6)  i = 8;	// 養子一次
	else if(sd->status.class_ <= PC_CLASS_BASE3 + 21) i = 9;	// 養子二次
	else if(sd->status.class_ == PC_CLASS_SNV3)       i = 10;	// 養子スパノビ
	else if(sd->status.class_ == PC_CLASS_TK)         i = 8;	// テコンキッド
	else if(sd->status.class_ <= PC_CLASS_SG2)        i = 14;	// 拳聖
	else if(sd->status.class_ == PC_CLASS_SL)         i = 9;	// ソウルリンカー
	else                                              i = 9;	// それ以外なら二次テーブル

	return exp_table[i][sd->status.job_level-1];
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

	return ((val < 0)? -1: (val+9)/10+1);
}

/*==========================================
 * 能力値成長
 *------------------------------------------
 */
void pc_statusup(struct map_session_data *sd, unsigned short type)
{
	int need, is_baby;
	int val = 0, max = 0;
	short *param = NULL;

	nullpo_retv(sd);

	need = pc_need_status_point(sd,type);
	if(type < SP_STR || type > SP_LUK || need < 0 || need > sd->status.status_point) {
		clif_statusupack(sd,type,0,0);
		return;
	}
	is_baby = pc_isbaby(sd);

	switch(type) {
		case SP_STR:
			param = &sd->status.str;
			max   = battle_config.max_parameter_str;
			break;
		case SP_AGI:
			param = &sd->status.agi;
			max   = battle_config.max_parameter_agi;
			break;
		case SP_VIT:
			param = &sd->status.vit;
			max   = battle_config.max_parameter_vit;
			break;
		case SP_INT:
			param = &sd->status.int_;
			max   = battle_config.max_parameter_int;
			break;
		case SP_DEX:
			param = &sd->status.dex;
			max   = battle_config.max_parameter_dex;
			break;
		case SP_LUK:
			param = &sd->status.luk;
			max   = battle_config.max_parameter_luk;
			break;
	}

	if(param == NULL || (*param) >= max || (is_baby && (*param) >= battle_config.baby_status_max)) {
		clif_statusupack(sd,type,0,0);
		return;
	}
	val = ++(*param);

	sd->status.status_point -= need;
	if(need != pc_need_status_point(sd,type)) {
		clif_updatestatus(sd,type-SP_STR+SP_USTR);
	}

	// if player have max in all stats, don't give status_point
	if ((sd->status.str  >= battle_config.max_parameter_str || (is_baby && sd->status.str  >= battle_config.baby_status_max)) &&
	    (sd->status.agi  >= battle_config.max_parameter_agi || (is_baby && sd->status.agi  >= battle_config.baby_status_max)) &&
	    (sd->status.vit  >= battle_config.max_parameter_vit || (is_baby && sd->status.vit  >= battle_config.baby_status_max)) &&
	    (sd->status.int_ >= battle_config.max_parameter_int || (is_baby && sd->status.int_ >= battle_config.baby_status_max)) &&
	    (sd->status.dex  >= battle_config.max_parameter_dex || (is_baby && sd->status.dex  >= battle_config.baby_status_max)) &&
	    (sd->status.luk  >= battle_config.max_parameter_luk || (is_baby && sd->status.luk  >= battle_config.baby_status_max)))
		sd->status.status_point = 0;

	clif_updatestatus(sd,SP_STATUSPOINT);
	clif_updatestatus(sd,type);
	status_calc_pc(sd,0);
	clif_statusupack(sd,type,1,val);

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

	if(skill_point < 9)
		up_level = 0;
	else if(sd->status.skill_point >= sd->status.job_level && skill_point < 58 && sd->s_class.job > 6)
		up_level = 1;
	else
		up_level = 2;

	return (st->class_level <= up_level);
}

/*==========================================
 * スキルポイント割り振り
 *------------------------------------------
 */
void pc_skillup(struct map_session_data *sd, int skill_num)
{
	nullpo_retv(sd);

	if(skill_num < 0 || skill_num >= MAX_SKILL)
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
	    sd->status.skill[skill_num].lv < pc_get_skilltree_max(&sd->s_class,skill_num) )
	{
		sd->status.skill[skill_num].lv++;
		sd->status.skill_point--;
		status_calc_pc(sd,0);
		clif_skillup(sd,skill_num);
		clif_updatestatus(sd,SP_SKILLPOINT);
		clif_skillinfoblock(sd);
	}

	return;
}

/*==========================================
 * /allskill
 *------------------------------------------
 */
int pc_allskillup(struct map_session_data *sd,int flag)
{
	int i,id;

	for(i=0; i<MAX_SKILL; i++) {
		sd->status.skill[i].id = 0;
		if(sd->status.skill[i].flag) {	// cardスキルなら、
			sd->status.skill[i].lv   = (sd->status.skill[i].flag == 1)? 0: sd->status.skill[i].flag-2;	// 本当のlvに
			sd->status.skill[i].flag = 0;	// flagは0にしておく
		}
	}

	if(battle_config.gm_allskill > 0 && pc_isGM(sd) >= battle_config.gm_allskill) {
		// 全てのスキル
		for(i=1; i<158; i++)
			sd->status.skill[i].lv = skill_get_max(i);
		for(i=210; i<291; i++)
			sd->status.skill[i].lv = skill_get_max(i);
		if(battle_config.gm_allskill_addabra) {
			for(i=291; i<304; i++)
				sd->status.skill[i].lv = skill_get_max(i);
		}
		for(i=304; i<MAX_SKILL; i++) {
			if(i != SG_DEVIL)	// 太陽と月と星の悪魔は除外（ペナルティの永続暗闇がきついので）
				sd->status.skill[i].lv = skill_get_max(i);
		}
	} else {
		for(i=0; (id = skill_tree[sd->s_class.upper][sd->s_class.job][i].id) > 0; i++) {
			if(id == SG_DEVIL)	// ここで除外処理
				continue;
			// flagがあるならクエストスキルも取得する
			if(skill_get_inf2(id)&0x01 && !flag && !battle_config.quest_skill_learn)
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
#define sumsp(a) ((a)*((a-2)/10+2) - 5*((a-2)/10)*((a-2)/10) - 6*((a-2)/10) -2)

void pc_resetstate(struct map_session_data* sd)
{
	int add = 0;

	nullpo_retv(sd);

	add += sumsp(sd->status.str);
	add += sumsp(sd->status.agi);
	add += sumsp(sd->status.vit);
	add += sumsp(sd->status.int_);
	add += sumsp(sd->status.dex);
	add += sumsp(sd->status.luk);
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

	for(i=1; i<MAX_SKILL; i++) {
		if((skill = pc_checkskill2(sd,i)) > 0) {
			if(!(skill_get_inf2(i)&0x01) || battle_config.quest_skill_learn) {
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
	sd->cloneskill_id = 0;
	sd->cloneskill_lv = 0;
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
	if(pc_issit(sd)) {
		pc_setstand(sd);
		skill_sit(sd,0);
	}

	// 歩いていたら足を止める
	if((sd->sc.data[SC_ENDURE].timer == -1 || map[sd->bl.m].flag.gvg) && sd->sc.data[SC_BERSERK].timer == -1 && !sd->special_state.infinite_endure && !unit_isrunning(&sd->bl))
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
		for(i=0; i<11; i++) {
			if(atn_rand()%10000 < sd->break_myequip_rate_when_hit[i])
				pc_break_equip2(sd,i);
		}
	}

	// 敵の攻撃を受けると一定確率で装備が消滅
	if(sd->loss_equip_flag&0x0020 && damage > 0) {
		for(i=0; i<11; i++) {
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
	if(sd->s_class.job == 23 && !sd->state.snovice_dead_flag) {
		int next = pc_nextbaseexp(sd);
		if( (next > 0 && (atn_bignumber)sd->status.base_exp * 1000 / next >= 990) ||
		    (next <= 0 && sd->status.base_exp >= battle_config.snovice_maxexp_border) )
		{
			sd->status.hp = sd->status.max_hp;
			clif_updatestatus(sd,SP_HP);
			clif_skill_nodamage(&sd->bl,&sd->bl,MO_STEELBODY,5,1);
			status_change_start(&sd->bl,SkillStatusChangeTable[MO_STEELBODY],5,0,0,0,skill_get_time(MO_STEELBODY,5),0);
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
				ssd->kill_charid  = sd->status.char_id;		// 自分が殺した相手のキャラID
				sd->killed_charid = ssd->status.char_id;	// 自分を殺した相手のキャラID
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
		for(i=0; i<11; i++) {
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

	if(sd->vender_id)
		vending_closevending(sd);

	if(sd->status.pet_id > 0 && sd->pd && sd->petDB) {
		sd->pet.intimate -= sd->petDB->die;
		if(sd->pet.intimate < 0)
			sd->pet.intimate = 0;
		clif_send_petdata(sd,1,sd->pet.intimate);
	}
	if(sd->status.merc_id > 0 && sd->mcd) {
		clif_disp_onlyself(sd->fd, msg_txt(191));	// 傭兵が逃走しました。
		merc_delete_data(sd);
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
	sd->status.die_counter++;	// 死にカウンター書き込み
	status_change_release(&sd->bl,0x01);	// ステータス異常を解除する

	pc_setdead(sd);

	if(sd->s_class.job == 0) {
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
		*((unsigned long *)(&item_tmp.card[2])) = sd->status.char_id;	// キャラID
		map_addflooritem(&item_tmp,1,sd->bl.m,sd->bl.x,sd->bl.y,0,0,0,0);
	}

	for(i=0; i<5; i++) {
		if(sd->dev.val1[i]) {
			status_change_end(map_id2bl(sd->dev.val1[i]),SC_DEVOTION,-1);
			sd->dev.val1[i] = sd->dev.val2[i] = 0;
		}
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
		sd->status.hp = sd->status.max_hp * kaizel_lv / 10;
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
		val = sd->status.base_exp;
		break;
	case SP_JOBEXP:
		val = sd->status.job_exp;
		break;
	case SP_NEXTBASEEXP:
		val = pc_nextbaseexp(sd);
		break;
	case SP_NEXTJOBEXP:
		val = pc_nextjobexp(sd);
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
		val = sd->sc.option&CART_MASK;
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
		val = sd->cloneskill_id;
		break;
	case SP_CLONESKILL_LV:
		val = sd->cloneskill_lv;
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
		val = sd->kill_charid;
		break;
	case SP_KILLED_CHAR:
		val = sd->killed_charid;
		break;
	case SP_SHOP_POINT:
		val = sd->shop_point;
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
		sd->cloneskill_id = val;
		pc_setglobalreg(sd,"PC_CLONESKILL_ID",val);
		clif_skillinfoblock(sd);
		return 0;
	case SP_CLONESKILL_LV:
		sd->cloneskill_lv = val;
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
		sd->kill_charid = val;
		pc_setglobalreg(sd,"PC_KILL_CHAR",val);
		clif_update_temper(sd);
		return 0;
	case SP_KILLED_CHAR:
		sd->killed_charid = val;
		pc_setglobalreg(sd,"PC_KILLED_CHAR",val);
		clif_update_temper(sd);
		return 0;
	case SP_SHOP_POINT:
		sd->shop_point = val;
		pc_setglobalreg(sd,"PC_SHOP_POINT",val);
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
		if(sp > 0)
			sp = 0;
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
		sd->potion_hp = hp;
		sd->potion_sp = sp;
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
		bonus = 100 + pc_checkskill(sd,AM_LEARNINGPOTION)*5;
		if(bonus != 100)
			hp = hp * bonus / 100;
		// card
		bonus = 100 + sd->itemheal_rate[itemdb_group(sd->use_itemid)];
		if(bonus != 100)
			hp = hp * bonus / 100;
		if(sd->use_nameditem && ranking_get_id2rank(sd->use_nameditem,RK_ALCHEMIST))
		{
			if(sd->sc.data[SC_ROGUE].timer != -1)
				hp = hp * 2;
			else
				hp = hp * 150 / 100;
		}
		if(sd->sc.data[SC_CRITICALWOUND].timer != -1)
			hp = hp * (100 - sd->sc.data[SC_CRITICALWOUND].val1 * 10) / 100;
	}
	if(sp > 0) {
		bonus = (sd->paramc[3]<<1) + 100 + pc_checkskill(sd,MG_SRECOVERY)*10;
		if(bonus != 100)
			sp = sp * bonus / 100;
		bonus = 100 + pc_checkskill(sd,AM_LEARNINGPOTION)*5;
		if(bonus != 100)
			sp = sp * bonus / 100;
		// card
		bonus = 100 + sd->itemheal_rate[itemdb_group(sd->use_itemid)];
		if(bonus != 100)
			sp  = sp * bonus / 100;
		if(sd->use_nameditem && ranking_get_id2rank(sd->use_nameditem,RK_ALCHEMIST))
		{
			if(sd->sc.data[SC_ROGUE].timer != -1)
				sp = sp * 2;
			else
				sp = sp * 150 / 100;
		}
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
		sd->potion_per_hp = hp;
		sd->potion_per_sp = sp;
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
 * 引数	job 職業 0〜23
 *      upper 通常 0, 転生 1, 養子 2, そのまま -1
 *------------------------------------------
 */
int pc_jobchange(struct map_session_data *sd,int job, int upper)
{
	int i;
	int b_class = 0;
	int joblv_nochange = 0;

	nullpo_retr(0, sd);

	if(job >= MAX_VALID_PC_CLASS)
		return 1;

	// テコン、ガンスリンガー、忍者
	if(job >= 24)
		upper = 0;

	// 養子<->転生前の場合JOB1にしない
	if(sd->s_class.upper != 1 && upper != 1 && sd->s_class.job == job)
		joblv_nochange = 1;

	if(battle_config.enable_upper_class == 0) {	// confで無効になっていたらupper=0
		upper = 0;
	}

	if(upper < 0)		// 現在転生かどうかを判断する
		upper = sd->s_class.upper;

	if(upper == 0) {	// 通常職ならjobそのまんま
		if(job >= 24 && job <= 27)
			b_class = job + PC_CLASS_BASE3 - 1;
		else if(job == 30)
			b_class = PC_CLASS_DK;
		else if(job == 31)
			b_class = PC_CLASS_DC;
		else
			b_class = job;
	} else if(upper == 1) {
		if(job >= PC_CLASS_SNV) {	// 転生にスパノビ以降は存在しないのでお断り
			return 1;
		} else {
			b_class = job + PC_CLASS_BASE2;
		}
	} else if(upper == 2) {		// 養子に結婚はないけどどうせ次で蹴られるからいいや
		b_class = (job >= 23)? (job + PC_CLASS_BASE3 - 1): (job + PC_CLASS_BASE3);
	} else {
		return 1;
	}

	if((sd->sex == 0 && job == 19) || (sd->sex == 1 && job == 20) ||
	   job == 13 || job == 21 || job == 22 || job == 26 ||
	   sd->status.class_ == b_class)	// ♀はバードになれない、♂はダンサーになれない、結婚衣裳もお断り
		return 1;

	sd->status.class_ = sd->view_class = b_class;
	if(sd->status.class_ == PC_CLASS_GS || sd->status.class_ == PC_CLASS_NJ)
		sd->view_class = sd->status.class_ - 4;

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

	for(i=0; i<11; i++) {
		if(sd->equip_index[i] >= 0 && !pc_isequip(sd,sd->equip_index[i]))
			pc_unequipitem(sd,sd->equip_index[i],1);	// 装備外し
	}

	clif_changelook(&sd->bl,LOOK_BASE,sd->view_class);
	clif_send_clothcolor(&sd->bl);

	if(sd->status.manner < 0)
		clif_changestatus(&sd->bl,SP_MANNER,sd->status.manner);

	status_calc_pc(sd,0);
	pc_checkallowskill(sd);
	pc_equiplookall(sd);
	clif_equiplist(sd);
	clif_skillinfoblock(sd);

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
	case LOOK_MOB:
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

	if( (type&0x0010) && !pc_isfalcon(sd) ) {
		clif_status_load(sd,SI_FALCON,1);
	}
	else if( !(type&0x0010) && pc_isfalcon(sd) ) {
		clif_status_load(sd,SI_FALCON,0);
	}

	if( (type&0x0020) && !pc_isriding(sd) ) {
		clif_status_load(sd,SI_RIDING,1);
	}
	else if( !(type&0x0020) && pc_isriding(sd) ) {
		clif_status_load(sd,SI_RIDING,0);
	}

	if( (type&CART_MASK) && !pc_iscarton(sd) ) {
		clif_cart_itemlist(sd);
		clif_cart_equiplist(sd);
		clif_updatestatus(sd,SP_CARTINFO);
	}
	else if( !(type&CART_MASK) && pc_iscarton(sd) ) {
		clif_cart_clear(sd);
	}

	sd->sc.option = type;
	clif_changeoption(&sd->bl);
	clif_send_clothcolor(&sd->bl);
	status_calc_pc(sd,0);

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
	} cart[] = {
		{ 0x0000,  0 },
		{ 0x0008,  0 },
		{ 0x0080, 40 },
		{ 0x0100, 65 },
		{ 0x0200, 80 },
		{ 0x0400, 90 },
	};

	nullpo_retv(sd);

	if(type >= sizeof(cart) / sizeof(cart[0]))	// unsigned short: don't check 'type < 0'
		return;

	if(pc_checkskill(sd,MC_PUSHCART) > 0) {	// プッシュカートスキル所持
		if(sd->status.base_level > cart[type].level) {
			// suppress actual cart; conserv other options
			pc_setoption(sd, (sd->sc.option & ~CART_MASK) | cart[type].opt);
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
		pc_setoption(sd,0x0010);
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
		pc_setoption(sd,0x0020);
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
char *pc_readregstr(struct map_session_data *sd,int reg)
{
	int i;

	nullpo_retr(0, sd);

	for(i=0; i<sd->regstr_num; i++) {
		if(sd->regstr[i].index == reg)
			return sd->regstr[i].data;
	}
	return NULL;
}

/*==========================================
 * script用文字列変数の値を設定
 *------------------------------------------
 */
int pc_setregstr(struct map_session_data *sd,int reg,char *str)
{
	int i;

	nullpo_retr(0, sd);

	if(strlen(str)+1 >= sizeof(sd->regstr[0].data)) {
		printf("pc_setregstr: string too long !\n");
		return 0;
	}

	for(i=0; i<sd->regstr_num; i++) {
		if(sd->regstr[i].index == reg) {
			strncpy(sd->regstr[i].data,str,256);
			return 0;
		}
	}
	sd->regstr_num++;
	sd->regstr = (struct script_regstr *)aRealloc(sd->regstr, sizeof(sd->regstr[0]) * sd->regstr_num);
	sd->regstr[i].index = reg;
	strncpy(sd->regstr[i].data,str,256);

	return 0;
}

/*==========================================
 * script用グローバル変数の値を読む
 *------------------------------------------
 */
int pc_readglobalreg(struct map_session_data *sd,const char *reg)
{
	int i;

	nullpo_retr(0, sd);

	for(i=0; i<sd->save_reg.global_num; i++) {
		if(strcmp(sd->save_reg.global[i].str,reg) == 0)
			return sd->save_reg.global[i].value;
	}
	return 0;
}

/*==========================================
 * script用グローバル変数の値を設定
 *------------------------------------------
 */
int pc_setglobalreg(struct map_session_data *sd,const char *reg,int val)
{
	int i;

	nullpo_retr(0, sd);

	if(val == 0) {
		for(i=0; i<sd->save_reg.global_num; i++) {
			if(strcmp(sd->save_reg.global[i].str,reg) == 0) {
				sd->save_reg.global[i] = sd->save_reg.global[sd->save_reg.global_num-1];
				sd->save_reg.global_num--;
				sd->state.reg_dirty = 1;
				break;
			}
		}
		return 0;
	}
	for(i=0; i<sd->save_reg.global_num; i++) {
		if(strcmp(sd->save_reg.global[i].str,reg) == 0) {
			if(sd->save_reg.global[i].value != val) {
				sd->save_reg.global[i].value = val;
				sd->state.reg_dirty = 1;
			}
			return 0;
		}
	}
	if(sd->save_reg.global_num < GLOBAL_REG_NUM) {
		strncpy(sd->save_reg.global[i].str,reg,32);
		sd->save_reg.global[i].str[31] = '\0';	// force \0 terminal
		sd->save_reg.global[i].value = val;
		sd->save_reg.global_num++;
		sd->state.reg_dirty = 1;
		return 0;
	}
	if(battle_config.error_log)
		printf("pc_setglobalreg : couldn't set %s (GLOBAL_REG_NUM = %d)\n", reg, GLOBAL_REG_NUM);

	return 1;
}

/*==========================================
 * script用アカウント変数の値を読む
 *------------------------------------------
 */
int pc_readaccountreg(struct map_session_data *sd,const char *reg)
{
	int i;

	nullpo_retr(0, sd);

	for(i=0; i<sd->save_reg.account_num; i++) {
		if(strcmp(sd->save_reg.account[i].str,reg) == 0)
			return sd->save_reg.account[i].value;
	}
	return 0;
}

/*==========================================
 * script用アカウント変数の値を設定
 *------------------------------------------
 */
int pc_setaccountreg(struct map_session_data *sd,const char *reg,int val)
{
	int i;

	nullpo_retr(0, sd);

	if(val == 0) {
		for(i=0; i<sd->save_reg.account_num; i++) {
			if(strcmp(sd->save_reg.account[i].str,reg) == 0) {
				sd->save_reg.account[i] = sd->save_reg.account[sd->save_reg.account_num-1];
				sd->save_reg.account_num--;
				break;
			}
		}
		intif_saveaccountreg(sd);
		return 0;
	}
	for(i=0; i<sd->save_reg.account_num; i++) {
		if(strcmp(sd->save_reg.account[i].str,reg) == 0) {
			sd->save_reg.account[i].value = val;
			intif_saveaccountreg(sd);
			return 0;
		}
	}
	if(sd->save_reg.account_num < ACCOUNT_REG_NUM) {
		strncpy(sd->save_reg.account[i].str,reg,32);
		sd->save_reg.account[i].str[31] = '\0';	// force \0 terminal
		sd->save_reg.account[i].value = val;
		sd->save_reg.account_num++;
		intif_saveaccountreg(sd);
		return 0;
	}
	if(battle_config.error_log)
		printf("pc_setaccountreg : couldn't set %s (ACCOUNT_REG_NUM = %d)\n", reg, ACCOUNT_REG_NUM);

	return 1;
}

/*==========================================
 * script用アカウント変数2の値を読む
 *------------------------------------------
 */
int pc_readaccountreg2(struct map_session_data *sd,const char *reg)
{
	int i;

	nullpo_retr(0, sd);

	for(i=0; i<sd->save_reg.account2_num; i++) {
		if(strcmp(sd->save_reg.account2[i].str,reg) == 0)
			return sd->save_reg.account2[i].value;
	}
	return 0;
}

/*==========================================
 * script用アカウント変数2の値を設定
 *------------------------------------------
 */
int pc_setaccountreg2(struct map_session_data *sd,const char *reg,int val)
{
	int i;

	nullpo_retr(1, sd);

	if(val == 0) {
		for(i=0; i<sd->save_reg.account2_num; i++) {
			if(strcmp(sd->save_reg.account2[i].str,reg) == 0) {
				sd->save_reg.account2[i] = sd->save_reg.account2[sd->save_reg.account2_num-1];
				sd->save_reg.account2_num--;
				break;
			}
		}
		chrif_saveaccountreg2(sd);
		return 0;
	}
	for(i=0; i<sd->save_reg.account2_num; i++) {
		if(strcmp(sd->save_reg.account2[i].str,reg) == 0) {
			sd->save_reg.account2[i].value = val;
			chrif_saveaccountreg2(sd);
			return 0;
		}
	}
	if(sd->save_reg.account2_num < ACCOUNT_REG2_NUM) {
		strncpy(sd->save_reg.account2[i].str,reg,32);
		sd->save_reg.account2[i].str[31] = '\0';	// force \0 terminal
		sd->save_reg.account2[i].value = val;
		sd->save_reg.account2_num++;
		chrif_saveaccountreg2(sd);
		return 0;
	}
	if(battle_config.error_log)
		printf("pc_setaccountreg2 : couldn't set %s (ACCOUNT_REG2_NUM = %d)\n", reg, ACCOUNT_REG2_NUM);

	return 1;
}

/*==========================================
 * イベントタイマー処理
 *------------------------------------------
 */
static int pc_eventtimer(int tid,unsigned int tick,int id,int data)
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
		sd->eventtimer[i] = add_timer(gettick()+tick,pc_eventtimer,sd->bl.id,(int)evname);
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
 * アイテムを装備する
 *------------------------------------------
 */
void pc_equipitem(struct map_session_data *sd, int n, int pos)
{
	int i,nameid;
	struct item_data *id;

	nullpo_retv(sd);
	nullpo_retv(id = sd->inventory_data[n]);

	nameid = sd->status.inventory[n].nameid;
	pos = pc_equippoint(sd,n);

	if(battle_config.battle_log)
		printf("equip %d(%d) %x:%x\n",nameid,n,id->equip,pos);
	if(!pc_isequip(sd,n) || !pos) {
		clif_equipitemack(sd,n,0,0);	// fail
		return;
	}
	if(pos == 0x88) {	// アクセサリ用例外処理
		int epor = 0;
		if(sd->equip_index[0] >= 0)
			epor |= sd->status.inventory[sd->equip_index[0]].equip;
		if(sd->equip_index[1] >= 0)
			epor |= sd->status.inventory[sd->equip_index[1]].equip;
		epor &= 0x88;
		pos = (epor == 0x08) ? 0x80 : 0x08;
	}

	// 二刀流処理
	if( pos == 0x22 && 	// 一応、装備要求箇所が二刀流武器かチェックする
	    id->equip == 2 &&	// 単手武器
	    (pc_checkskill(sd, AS_LEFT) > 0 || sd->s_class.job == 12) ) // 左手修錬有
	{
		int tpos = 0;
		if(sd->equip_index[8] >= 0)
			tpos |= sd->status.inventory[sd->equip_index[8]].equip;
		if(sd->equip_index[9] >= 0)
			tpos |= sd->status.inventory[sd->equip_index[9]].equip;
		tpos &= 0x02;
		pos = (tpos == 0x02) ? 0x20 : 0x02;
	}

	for(i=0; i<11; i++) {
		if(sd->equip_index[i] >= 0 && sd->status.inventory[sd->equip_index[i]].equip & pos) {
			pc_unequipitem(sd,sd->equip_index[i],1);
		}
	}
	// 弓矢装備
	if(pos == 0x8000) {
		clif_arrowequip(sd,n);
		clif_arrow_fail(sd,3);	// 装備できました
	} else {
		clif_equipitemack(sd,n,pos,1);
	}

	for(i=0; i<11; i++) {
		if(pos & equip_pos[i])
			sd->equip_index[i] = n;
	}
	sd->status.inventory[n].equip = pos;

	if(sd->status.inventory[n].equip & 0x0002) {
		if(sd->inventory_data[n])
			sd->weapontype1 = sd->inventory_data[n]->look;
		else
			sd->weapontype1 = WT_FIST;
		pc_calcweapontype(sd);
		clif_changelook(&sd->bl,LOOK_WEAPON,sd->status.weapon);
	}
	if(sd->status.inventory[n].equip & 0x0020) {
		if(sd->inventory_data[n]) {
			if(sd->inventory_data[n]->type == 4) {
				sd->status.shield = 0;
				if(sd->status.inventory[n].equip == 0x0020)
					sd->weapontype2 = sd->inventory_data[n]->look;
				else
					sd->weapontype2 = WT_FIST;
			}
			else if(sd->inventory_data[n]->type == 5) {
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
	if(sd->status.inventory[n].equip & 0x0001) {
		if(sd->inventory_data[n])
			sd->status.head_bottom = sd->inventory_data[n]->look;
		else
			sd->status.head_bottom = 0;
		clif_changelook(&sd->bl,LOOK_HEAD_BOTTOM,sd->status.head_bottom);
	}
	if(sd->status.inventory[n].equip & 0x0100) {
		if(sd->inventory_data[n])
			sd->status.head_top = sd->inventory_data[n]->look;
		else
			sd->status.head_top = 0;
		clif_changelook(&sd->bl,LOOK_HEAD_TOP,sd->status.head_top);
	}
	if(sd->status.inventory[n].equip & 0x0200) {
		if(sd->inventory_data[n])
			sd->status.head_mid = sd->inventory_data[n]->look;
		else
			sd->status.head_mid = 0;
		clif_changelook(&sd->bl,LOOK_HEAD_MID,sd->status.head_mid);
	}
	if(sd->status.inventory[n].equip & 0x0040)
		clif_changelook(&sd->bl,LOOK_SHOES,0);

	pc_checkallowskill(sd);	// 装備品でスキルか解除されるかチェック
	status_calc_pc(sd,0);

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

	if(battle_config.battle_log)
		printf("unequip %d %x:%x\n",n,pc_equippoint(sd,n),sd->status.inventory[n].equip);
	if(sd->status.inventory[n].equip) {
		int i;
		for(i=0; i<11; i++) {
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
				if(!battle_config.death_by_unrig_penalty) {
					if(sd->status.hp < hp)
						hp = sd->status.hp-1;
				}
			}
		}
		if(sd->status.inventory[n].equip & 0x0002) {
			sd->weapontype1 = WT_FIST;
			sd->status.weapon = sd->weapontype2;
			pc_calcweapontype(sd);
			clif_changelook(&sd->bl,LOOK_WEAPON,sd->status.weapon);
		}
		if(sd->status.inventory[n].equip & 0x0020) {
			sd->weapontype2 = WT_FIST;
			sd->status.shield = 0;
			pc_calcweapontype(sd);
			clif_changelook(&sd->bl,LOOK_SHIELD,sd->status.shield);
		}
		if(sd->status.inventory[n].equip & 0x0001) {
			sd->status.head_bottom = 0;
			clif_changelook(&sd->bl,LOOK_HEAD_BOTTOM,sd->status.head_bottom);
		}
		if(sd->status.inventory[n].equip & 0x0100) {
			sd->status.head_top = 0;
			clif_changelook(&sd->bl,LOOK_HEAD_TOP,sd->status.head_top);
		}
		if(sd->status.inventory[n].equip & 0x0200) {
			sd->status.head_mid = 0;
			clif_changelook(&sd->bl,LOOK_HEAD_MID,sd->status.head_mid);
		}
		if(sd->status.inventory[n].equip & 0x0040)
			clif_changelook(&sd->bl,LOOK_SHOES,0);

		clif_unequipitemack(sd,n,sd->status.inventory[n].equip,1);
		sd->state.inventory_dirty = 1;
		sd->status.inventory[n].id = ++sd->inventory_sortkey;	// インベントリに新規登録
		sd->status.inventory[n].equip = 0;
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

	if(hp || sp)
		pc_heal(sd,-hp,-sp);

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

	for(i=0; i<10; i++) {
		idx = sd->equip_index[i];
		if(idx < 0)
			continue;
		if(i == 9 && sd->equip_index[8] == idx)
			continue;
		if(i == 5 && sd->equip_index[4] == idx)
			continue;
		if(i == 6 && (sd->equip_index[5] == idx || sd->equip_index[4] == idx))
			continue;

		if(sd->inventory_data[idx]) {
			if(sd->status.inventory[idx].nameid == id)
				n++;

			for(j=0; j<sd->inventory_data[idx]->slot; j++) {	// カード
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
	int i,j;

	nullpo_retr(0, sd);

	for(i=0; i<11; i++)
		sd->equip_index[i] = -1;

	for(i=0; i<MAX_INVENTORY; i++) {
		if(sd->status.inventory[i].nameid <= 0)
			continue;
		if(!sd->status.inventory[i].equip)
			continue;

		for(j=0; j<11; j++) {
			if(sd->status.inventory[i].equip & equip_pos[j])
				sd->equip_index[j] = i;
		}
		if(sd->status.inventory[i].equip & 0x0002) {
			if(sd->inventory_data[i])
				sd->weapontype1 = sd->inventory_data[i]->look;
			else
				sd->weapontype1 = 0;
		}
		if(sd->status.inventory[i].equip & 0x0020) {
			if(sd->inventory_data[i] && sd->inventory_data[i]->type == 4 && sd->status.inventory[i].equip == 0x0020)
				sd->weapontype2 = sd->inventory_data[i]->look;
			else
				sd->weapontype2 = 0;
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
			if( sd->status.inventory[i].card[0] == (short)0xff00 )
				intif_delete_petdata(*((long *)(&sd->status.inventory[i].card[1])));
			pc_delitem(sd,i,sd->status.inventory[i].amount,3);
		}
		// カート内の不正チェック
		for(i=0; i<MAX_CART; i++) {
			if( (itemid = sd->status.cart[i].nameid) == 0 )
				continue;
			if( itemdb_available(itemid) )
				continue;
			if( battle_config.error_log )
				printf("illegal item id %d in %d[%s] cart.\n",itemid,sd->bl.id,sd->status.name);
			if( sd->status.cart[i].card[0] == (short)0xff00 )
				intif_delete_petdata(*((long *)(&sd->status.cart[i].card[1])));
			pc_cart_delitem(sd,i,sd->status.cart[i].amount,1);
		}
	}

	// 変更があったらid順にソートする
	if(sd->state.inventory_dirty) {
		if(sd->inventory_timer) {
			// 使用期限のあるアイテムなら一時的にkeyをidに変えておく
			struct linkdb_node *node = sd->inventory_timer;
			while(node) {
				node->key = (void*)sd->status.inventory[(int)node->key].id;
				node = node->next;
			}
		}
		qsort(sd->status.inventory, MAX_INVENTORY, sizeof(struct item), pc_comp_item);
		sd->state.inventory_dirty = 0;
		sd->inventory_sortkey = 0;

		if(sd->inventory_timer) {
			// 使用期限のあるアイテムならidをサーチしてインデックスを再設定
			struct linkdb_node *node = sd->inventory_timer;
			while(node) {
				for(i = 0; i < MAX_INVENTORY; i++) {
					if(sd->status.inventory[i].id == (unsigned int)node->key) {
						node->key = (void*)i;
						break;
					}
				}
				if(i >= MAX_INVENTORY) {
					// 何故かインデックスを復元できなかったのでソケット切断する
					if(battle_config.error_log)
						printf("pc_checkitem: broken limit data %u\n", (unsigned int)node->data);
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
			sd->status.inventory[i].equip = 0;
			calc_flag = 1;
		}
		// 装備制限チェック
		nullpo_retr(0, sd->inventory_data[i]);
		if(sd->status.inventory[i].equip) {
			if(!pc_isequip(sd, i)) {
				sd->status.inventory[i].equip = 0;
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
int pc_calc_pvprank_timer(int tid,unsigned int tick,int id,int data)
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
	if(dstsd->s_class.upper != 0 || dstsd->s_class.job == 22 || dstsd->s_class.job >= 24)
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

		itemid = (sd->sex == 0)? WEDDING_RING_F: WEDDING_RING_M;
		if(pc_equippeditem(sd,itemid) < 1)
			return 0;
		itemid = (psd->sex == 0)? WEDDING_RING_F: WEDDING_RING_M;
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
				pc_delitem(p_sd,i,1,0);
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
			pc_delitem(sd,i,1,0);
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
int pc_break_equip(struct map_session_data *sd, unsigned short where)
{
	int i;

	nullpo_retr(-1, sd);

	if(sd->unbreakable_equip & where)
		return 0;

	switch(where) {
		case EQP_WEAPON:
			if((sd->weapontype1 >= WT_1HAXE && sd->weapontype1 <= WT_STAFF) || sd->weapontype1 == WT_BOOK)
				return 0;
			if(sd->sc.data[SC_CP_WEAPON].timer != -1)
				return 0;
			break;
		case EQP_ARMOR:
			if(sd->sc.data[SC_CP_ARMOR].timer != -1)
				return 0;
			break;
		case EQP_SHIELD:
			if(sd->equip_index[8] >= 0 && sd->inventory_data[sd->equip_index[8]]->type == 4)	// 左手が武器なら
				return 0;
			if(sd->sc.data[SC_CP_SHIELD].timer != -1)
				return 0;
			break;
		case EQP_HELM:
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
		case 0: // アクセサリ左
		case 1:	// アクセサリ右
		case 2: // 靴
		case 3:	// 肩
			break;
		case 4:	// 頭下段
		case 5:	// 頭中段
		case 6:	// 頭上段
			if(sd->unbreakable_equip & EQP_HELM)
				return 0;
			if(sd->sc.data[SC_CP_HELM].timer != -1)
				return 0;
			break;
		case 7:	// 体
			if(sd->unbreakable_equip & EQP_ARMOR)
				return 0;
			if(sd->sc.data[SC_CP_ARMOR].timer != -1)
				return 0;
			break;
		case 8:	// 左手
			if(sd->equip_index[8] >= 0 && sd->inventory_data[sd->equip_index[8]]->type == 4) {	// 武器
				if(sd->unbreakable_equip & EQP_WEAPON)
					return 0;
				if(sd->sc.data[SC_CP_WEAPON].timer != -1)
					return 0;
			} else {	// 盾
				if(sd->unbreakable_equip & EQP_SHIELD)
					return 0;
				if(sd->sc.data[SC_CP_SHIELD].timer != -1)
					return 0;
			}
			break;
		case 9:	// 右手
			if(sd->unbreakable_equip & EQP_WEAPON)
				return 0;
			if(sd->sc.data[SC_CP_WEAPON].timer != -1)
				return 0;
			break;
		case 10: // 矢
			break;
		default:
			return -1;
	}
	if((idx = sd->equip_index[where]) >= 0 && sd->status.inventory[idx].equip) {
		sd->status.inventory[idx].attribute = 1;
		pc_unequipitem(sd,idx,0);
	}

	clif_itemlist(sd);
	clif_equiplist(sd);

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
		sd->hp_sub = sd->inchealhptick = 0;
		return 0;
	}

	bhp = sd->status.hp;
	hp_flag = (pc_checkskill(sd,SM_MOVINGRECOVERY) > 0 && sd->ud.walktimer != -1);

	if(sd->ud.walktimer == -1) {
		inc_num = pc_hpheal(sd);
		if(sd->sc.data[SC_TENSIONRELAX].timer != -1) {	// テンションリラックス
			sd->hp_sub += 2*inc_num;
			sd->inchealhptick += 3*natural_heal_diff_tick;
		} else {
			sd->hp_sub += inc_num;
			sd->inchealhptick += natural_heal_diff_tick;
		}
	} else if(hp_flag) {
		inc_num = pc_hpheal(sd);
		sd->hp_sub += inc_num;
		sd->inchealhptick = 0;
	} else {
		sd->hp_sub = sd->inchealhptick = 0;
		return 0;
	}

	if(sd->hp_sub >= battle_config.natural_healhp_interval) {
		bonus = sd->nhealhp;
		if(hp_flag) {
			bonus >>= 2;
			if(bonus <= 0)
				bonus = 1;
		}
		while(sd->hp_sub >= battle_config.natural_healhp_interval) {
			sd->hp_sub -= battle_config.natural_healhp_interval;
			if(sd->status.hp + bonus <= sd->status.max_hp) {
				sd->status.hp += bonus;
			} else {
				sd->status.hp = sd->status.max_hp;
				sd->hp_sub = sd->inchealhptick = 0;
			}
		}
	}
	if(bhp != sd->status.hp)
		clif_updatestatus(sd,SP_HP);

	if(sd->nshealhp > 0) {
		if(sd->inchealhptick >= battle_config.natural_heal_skill_interval && sd->status.hp < sd->status.max_hp) {
			bonus = sd->nshealhp;
			while(sd->inchealhptick >= battle_config.natural_heal_skill_interval) {
				sd->inchealhptick -= battle_config.natural_heal_skill_interval;
				if(sd->status.hp + bonus <= sd->status.max_hp) {
					sd->status.hp += bonus;
				} else {
					bonus = sd->status.max_hp - sd->status.hp;
					sd->status.hp = sd->status.max_hp;
					sd->hp_sub = sd->inchealhptick = 0;
				}
				clif_heal(sd->fd,SP_HP,bonus);
			}
		}
	} else {
		sd->inchealhptick = 0;
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
		sd->sp_sub = sd->inchealsptick = 0;
		return 0;
	}

	bsp = sd->status.sp;

	inc_num = pc_spheal(sd);
	if(sd->s_class.job == 23 || sd->sc.data[SC_EXPLOSIONSPIRITS].timer == -1 || sd->sc.data[SC_MONK].timer != -1)
		sd->sp_sub += inc_num;
	if(sd->ud.walktimer == -1)
		sd->inchealsptick += natural_heal_diff_tick;
	else
		sd->inchealsptick = 0;

	if(sd->sp_sub >= battle_config.natural_healsp_interval) {
		bonus = sd->nhealsp;
		while(sd->sp_sub >= battle_config.natural_healsp_interval) {
			sd->sp_sub -= battle_config.natural_healsp_interval;
			if(sd->status.sp + bonus <= sd->status.max_sp) {
				sd->status.sp += bonus;
			} else {
				sd->status.sp = sd->status.max_sp;
				sd->sp_sub = sd->inchealsptick = 0;
			}
		}
	}

	if(bsp != sd->status.sp)
		clif_updatestatus(sd,SP_SP);

	if(sd->nshealsp > 0) {
		if(sd->inchealsptick >= battle_config.natural_heal_skill_interval && sd->status.sp < sd->status.max_sp) {
			if(sd->doridori_counter && sd->s_class.job == 23)
				bonus = sd->nshealsp*2;
			else
				bonus = sd->nshealsp;
			sd->doridori_counter = 0;
			while(sd->inchealsptick >= battle_config.natural_heal_skill_interval) {
				sd->inchealsptick -= battle_config.natural_heal_skill_interval;
				if(sd->status.sp + bonus <= sd->status.max_sp) {
					sd->status.sp += bonus;
				} else {
					bonus = sd->status.max_sp - sd->status.sp;
					sd->status.sp = sd->status.max_sp;
					sd->sp_sub = sd->inchealsptick = 0;
				}
				clif_heal(sd->fd,SP_SP,bonus);
			}
		}
	} else {
		sd->inchealsptick = 0;
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
		sd->inchealspirithptick = 0;
		return 0;
	}

	sd->inchealspirithptick += natural_heal_diff_tick;

	if(sd->weight*100/sd->max_weight >= battle_config.natural_heal_weight_rate)
		interval += interval;

	if(sd->inchealspirithptick >= interval) {
		int bonus_hp = sd->nsshealhp;
		while(sd->inchealspirithptick >= interval) {
			if(pc_issit(sd)) {
				sd->inchealspirithptick -= interval;
				if(sd->status.hp < sd->status.max_hp) {
					if(sd->status.hp + bonus_hp <= sd->status.max_hp) {
						sd->status.hp += bonus_hp;
					} else {
						bonus_hp = sd->status.max_hp - sd->status.hp;
						sd->status.hp = sd->status.max_hp;
					}
					clif_heal(sd->fd,SP_HP,bonus_hp);
					sd->inchealspirithptick = 0;
				}
			} else {
				sd->inchealspirithptick -= natural_heal_diff_tick;
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
		sd->inchealspiritsptick = 0;
		return 0;
	}

	sd->inchealspiritsptick += natural_heal_diff_tick;

	if(sd->weight*100/sd->max_weight >= battle_config.natural_heal_weight_rate)
		interval += interval;

	if(sd->inchealspiritsptick >= interval) {
		int bonus_sp = sd->nsshealsp;
		while(sd->inchealspiritsptick >= interval) {
			if(pc_issit(sd)) {
				sd->inchealspiritsptick -= interval;
				if(sd->status.sp < sd->status.max_sp) {
					if(sd->status.sp + bonus_sp <= sd->status.max_sp) {
						sd->status.sp += bonus_sp;
					} else {
						bonus_sp = sd->status.max_sp - sd->status.sp;
						sd->status.sp = sd->status.max_sp;
					}
					clif_heal(sd->fd,SP_SP,bonus_sp);
					sd->inchealspiritsptick = 0;
				}
			} else {
				sd->inchealspiritsptick -= natural_heal_diff_tick;
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
		sd->inchealresthptick = 0;
		return 0;
	}

	sd->inchealresthptick += natural_heal_diff_tick;

	//if(sd->weight*100/sd->max_weight >= battle_config.natural_heal_weight_rate)
	//	interval += interval;

	if(sd->inchealresthptick >= interval) {
		int bonus_hp = sd->tk_nhealhp;

		if(sd->tk_doridori_counter_hp)
			bonus_hp += 30;
		sd->tk_doridori_counter_hp = 0;

		while(sd->inchealresthptick >= interval) {
			if(pc_issit(sd)) {
				sd->inchealresthptick -= interval;
				if(sd->status.hp < sd->status.max_hp) {
					if(sd->status.hp + bonus_hp <= sd->status.max_hp) {
						sd->status.hp += bonus_hp;
					} else {
						bonus_hp = sd->status.max_hp - sd->status.hp;
						sd->status.hp = sd->status.max_hp;
					}
					clif_heal(sd->fd,SP_HP,bonus_hp);
					sd->inchealresthptick = 0;
				}
			} else {
				sd->inchealresthptick -= natural_heal_diff_tick;
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
		sd->inchealrestsptick = 0;
		return 0;
	}

	sd->inchealrestsptick += natural_heal_diff_tick;

	//if(sd->weight*100/sd->max_weight >= battle_config.natural_heal_weight_rate)
	//	interval += interval;

	if(sd->inchealrestsptick >= interval) {
		int bonus_sp = sd->tk_nhealsp;
		int skilllv;

		if(sd->tk_doridori_counter_sp) {
			bonus_sp += 3;
			status_change_start(&sd->bl,SC_HAPPY,pc_checkskill(sd,TK_SPTIME),0,0,0,1800000,0);
			if((sd->status.class_==PC_CLASS_SG || sd->status.class_==PC_CLASS_SG2) && atn_rand()%10000 < battle_config.sg_angel_rate) {	// 太陽と月と星の天使
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
		sd->tk_doridori_counter_sp = 0;

		if((skilllv = pc_checkskill(sd,SL_KAINA)) > 0)
			bonus_sp += bonus_sp*(30+10*skilllv)/100;

		while(sd->inchealrestsptick >= interval) {
			if(pc_issit(sd)) {
				sd->inchealrestsptick -= interval;
				if(sd->status.sp < sd->status.max_sp) {
					if(sd->status.sp + bonus_sp <= sd->status.max_sp) {
						sd->status.sp += bonus_sp;
					} else {
						bonus_sp = sd->status.max_sp - sd->status.sp;
						sd->status.sp = sd->status.max_sp;
					}
					clif_heal(sd->fd,SP_SP,bonus_sp);
					sd->inchealrestsptick = 0;
				}
			} else {
				sd->inchealrestsptick -= natural_heal_diff_tick;
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

	if (sd->hp_penalty_value > 0) {
		sd->hp_penalty_tick += natural_heal_diff_tick;
		if (sd->hp_penalty_tick >= sd->hp_penalty_time) {
			do {
				hp += sd->hp_penalty_value;
				sd->hp_penalty_tick -= sd->hp_penalty_time;
			} while (sd->hp_penalty_tick >= sd->hp_penalty_time);
			sd->hp_penalty_tick = 0;
		}
	}

	if (sd->sp_penalty_value > 0) {
		sd->sp_penalty_tick += natural_heal_diff_tick;
		if (sd->sp_penalty_tick >= sd->sp_penalty_time) {
			do {
				sp += sd->sp_penalty_value;
				sd->sp_penalty_tick -= sd->sp_penalty_time;
			} while (sd->sp_penalty_tick >= sd->sp_penalty_time);
			sd->sp_penalty_tick = 0;
		}
	}

	if (hp > 0 || sp > 0)
		pc_heal(sd,-hp,-sp);

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
	    sd->sc.data[SC_BERSERK].timer == -1 )	// バーサーク状態ではHPが回復しない
	{
		pc_natural_heal_hp(sd);
		if( sd->sc.data[SC_MAXIMIZEPOWER].timer == -1 &&	// マキシマイズパワー状態ではSPが回復しない
		    sd->sc.data[SC_EXTREMITYFIST].timer == -1 &&	// 阿修羅状態ではSPが回復しない
		    sd->sc.data[SC_DANCING].timer == -1 &&		// ダンス状態ではSPが回復しない
		    sd->sc.data[SC_BERSERK].timer == -1 )		// バーサーク状態ではSPが回復しない
			pc_natural_heal_sp(sd);
	} else {
		sd->hp_sub = sd->inchealhptick = 0;
		sd->sp_sub = sd->inchealsptick = 0;
	}
	if(pc_checkskill(sd,MO_SPIRITSRECOVERY) > 0 && !pc_ishiding(sd) && sd->sc.data[SC_POISON].timer == -1) {
		pc_spirit_heal_hp(sd);
		pc_spirit_heal_sp(sd);
	} else {
		sd->inchealspirithptick = 0;
		sd->inchealspiritsptick = 0;
	}

	// 安らかな休息
	if(pc_checkskill(sd,TK_HPTIME) > 0 && sd->state.taekwonrest && sd->sc.data[SC_POISON].timer == -1)
		pc_rest_heal_hp(sd);
	else
		sd->inchealresthptick = 0;

	// 楽しい休息
	if(pc_checkskill(sd,TK_SPTIME) > 0 && sd->state.taekwonrest && sd->sc.data[SC_POISON].timer == -1)
		pc_rest_heal_sp(sd);
	else
		sd->inchealrestsptick = 0;

	if (sd->hp_penalty_value > 0 || sd->sp_penalty_value > 0)
		pc_bleeding(sd);
	else
		sd->hp_penalty_tick = sd->sp_penalty_tick = 0;

	return 0;
}

/*==========================================
 * HP/SP自然回復 (interval timer関数)
 *------------------------------------------
 */
static int pc_natural_heal(int tid,unsigned int tick,int id,int data)
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
	int *users = va_arg(ap,int *);

	nullpo_retr(0, sd);

	(*users)++;

	if(save_flag == 0 && sd->fd > last_save_fd && !sd->state.waitingdisconnect) {
		intif_save_scdata(sd);

		if(sd->status.pet_id > 0 && sd->pd)
			intif_save_petdata(sd->status.account_id,&sd->pet);
		if(sd->status.homun_id > 0 && sd->hd)
			homun_save_data(sd);
		if(sd->status.merc_id > 0 && sd->mcd)
			merc_save_data(sd);
		chrif_save(sd,0);
		if(sd->state.storage_flag == 2)
			storage_guild_storagesave(sd);
		else if(sd->state.storage_flag == 1)
			storage_storage_save(sd);
		save_flag = 1;
		last_save_fd = sd->fd;
	}

	return 0;
}

/*==========================================
 * 自動セーブ (timer関数)
 *------------------------------------------
 */
static int pc_autosave(int tid,unsigned int tick,int id,int data)
{
	int interval, users = 0;

	save_flag = 0;
	clif_foreachclient(pc_autosave_sub, &users);
	if(save_flag == 0)
		last_save_fd = 0;

	interval = autosave_interval/(users+1);
	if(interval <= 200)
		interval = 200;
	if(agit_flag == 1)	// GvG中はインターバルを長く取ることでラグを緩和する
		interval = interval * autosave_gvg_rate / 100;

	add_timer(gettick()+interval,pc_autosave,0,0);

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
		printf("File not found: %s.\n", GM_account_filename);
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
	int i,j,k;
	FILE *fp;
	char line[1024],*p;

	// 必要経験値読み込み
	memset(exp_table, 0, sizeof(exp_table));
	fp = fopen("db/exp.txt","r");
	if(fp == NULL) {
		printf("can't read db/exp.txt\n");
		return 1;
	}
	i = 0;
	while(fgets(line,1020,fp)) {
		int bn,b1,b2,b3,b4,b5,b6,jn,j1,j2,j3,j4,j5,j6,j7,j8;
		if(line[0] == '/' && line[1] == '/')
			continue;
		if(sscanf(line,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",&bn,&b1,&b2,&b3,&b4,&b5,&b6,&jn,&j1,&j2,&j3,&j4,&j5,&j6,&j7,&j8) != 16)
			continue;
		exp_table[0][i]  = bn;
		exp_table[1][i]  = b1;
		exp_table[2][i]  = b2;
		exp_table[3][i]  = b3;
		exp_table[4][i]  = b4;
		exp_table[5][i]  = b5;
		exp_table[6][i]  = b6;
		exp_table[7][i]  = jn;
		exp_table[8][i]  = j1;
		exp_table[9][i]  = j2;
		exp_table[10][i] = j3;
		exp_table[11][i] = j4;
		exp_table[12][i] = j5;
		exp_table[13][i] = j6;
		exp_table[14][i] = j7;
		exp_table[15][i] = j8;
		i++;
		if(i >= MAX_LEVEL)
			break;
	}
	fclose(fp);
	printf("read db/exp.txt done\n");

	// スキルツリー
	memset(skill_tree,0,sizeof(skill_tree));
	fp = fopen("db/skill_tree.txt","r");
	if(fp == NULL) {
		printf("can't read db/skill_tree.txt\n");
		return 1;
	}
	while(fgets(line,1020,fp)) {
		char *split[17];
		int upper = 0,skillid;
		struct skill_tree_entry *st;

		if(line[0]=='/' && line[1]=='/')
			continue;
		for(j=0,p=line;j<17 && p;j++) {
			split[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		if(j<17)
			continue;
		upper = atoi(split[0]);
		if(upper > 0 && battle_config.enable_upper_class == 0)	// confで無効になっていたら
			continue;
		if(upper < 0 || upper > 2)
			continue;

		i = atoi(split[1]);
		if(i < 0 || i >= MAX_PC_CLASS)
			continue;

		skillid = atoi(split[2]);
		if(skillid < 0 || skillid >= MAX_SKILL)
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

		for(k=0; k<5; k++) {
			st[j].need[k].id = atoi(split[k*2+4]);
			st[j].need[k].lv = atoi(split[k*2+5]);
		}
		st[j].base_level  = atoi(split[14]);
		st[j].job_level   = atoi(split[15]);
		st[j].class_level = atoi(split[16]);
	}
	fclose(fp);

	if(battle_config.baby_copy_skilltree) {
		// 養子のスキルツリーを通常職と同一にする場合
		memcpy(&skill_tree[2], &skill_tree[0], sizeof(skill_tree[0]));
	}
	printf("read db/skill_tree.txt done\n");

	// 属性修正テーブル
	for(i=0; i<MAX_ELE_LEVEL; i++) {
		for(j=0; j<ELE_MAX; j++) {
			for(k=0; k<ELE_MAX; k++)
				attr_fix_table[i][j][k] = 100;
		}
	}
	fp = fopen("db/attr_fix.txt","r");
	if(fp == NULL) {
		printf("can't read db/attr_fix.txt\n");
		return 1;
	}
	while(fgets(line,1020,fp)) {
		char *split[10];
		int lv,n;
		if(line[0]=='/' && line[1]=='/')
			continue;
		for(j=0,p=line;j<3 && p;j++) {
			split[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		lv = atoi(split[0]);
		n  = atoi(split[1]);

		for(i=0; i<n; ) {
			if( !fgets(line,1020,fp) )
				break;
			if(line[0]=='/' && line[1]=='/')
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
	printf("read db/attr_fix.txt done\n");

	return 0;
}

/*==========================================
 * Message of the Dayの読み込み
 *------------------------------------------
 */
int pc_read_motd(void)
{
	int i, ln = 0;
	char buf[256];
	FILE *fp;

	memset(motd_text, 0, sizeof(motd_text));

	if((fp = fopen(motd_txt, "r")) != NULL) {
		while(fgets(buf, sizeof(buf)-1, fp) != NULL) {
			for(i=0; buf[i]; i++) {
				if(buf[i] == '\r' || buf[i] == '\n') {
					if(i == 0) {
						buf[i++] = ' ';
					}
					buf[i] = '\0';
					break;
				}
			}
			strncpy(motd_text[ln], buf, 256);
			if(++ln >= MOTD_LINE_SIZE)
				break;
		}
		fclose(fp);
	}

	return 0;
}

/*==========================================
 * extra system
 *------------------------------------------
 */
static char extra_file_txt[1024] = "save/map_extra.txt"; // managed by software - must not be modified manually
static struct extra {
	int item_id; // -1: zeny, other: id item
	long quantity; // quantity of items or zeny
	char name[24]; // player name
} *extra_dat = NULL;
static int extra_num = 0;

static int pc_extra(int tid, unsigned int tick, int id, int data)
{
	FILE *fp;
	static int extra_file_readed = 0;
	int change_flag = 0; // must we rewrite extra file? (0: no, 1: yes)
	int lock, i;
	char line[1024], name[1024];
	int item_id;
	long quantity;
	struct map_session_data *pl_sd;
	struct item_data *item_data;
	char output[200];

	// do we use extra system?
	if (!battle_config.extra_system_flag)
		return 0;

	// if extra file not read, read it at first
	if (extra_file_readed == 0) {
		extra_file_readed = 1; // file readed.
		if ((fp = fopen(extra_file_txt, "r")) != NULL) {
			while(fgets(line, sizeof(line) - 1, fp) != NULL) {
				if ((line[0] == '/' && line[1] == '/') || line[0] == '\0' || line[0] == '\n' || line[0] == '\r')
					continue;
				// if line is valid
				if ((sscanf(line, "%d,%ld,%[^\r\n]", &item_id, &quantity, name) == 3 ||
				    sscanf(line, "%d\t%ld\t%[^\r\n]", &item_id, &quantity, name) == 3) &&
				    (item_id == -1 || (itemdb_exists(item_id) && (!battle_config.item_check || itemdb_available(item_id)))) && // zeny or valid items
				    quantity != 0 && // quantity
				    strlen(name) >= 4 && strlen(name) < 24) { // name
					// manage max quantity
					if (item_id == -1) {
						if (quantity > (long)MAX_ZENY) {
							quantity = (long)MAX_ZENY;
							// Invalid quantity -> file must be rewriten
							change_flag = 1;
						} else if (quantity < -((long)MAX_ZENY)) {
							quantity = -((long)MAX_ZENY);
							// Invalid quantity -> file must be rewriten
							change_flag = 1;
						}
					} else {
						if (quantity > (long)MAX_AMOUNT) {
							quantity = (long)MAX_AMOUNT;
							// Invalid quantity -> file must be rewriten
							change_flag = 1;
						} else if (quantity < -((long)MAX_AMOUNT)) {
							quantity = -((long)MAX_AMOUNT);
							// Invalid quantity -> file must be rewriten
							change_flag = 1;
						}
					}
					// add an index
					if (extra_num == 0) {
						extra_dat = (struct extra*)aCalloc(1, sizeof(struct extra));
					} else {
						extra_dat = (struct extra*)aRealloc(extra_dat, sizeof(struct extra) * (extra_num + 1));
						memset(&extra_dat[extra_num], 0, sizeof(struct extra));
					}
					extra_dat[extra_num].item_id = item_id;
					extra_dat[extra_num].quantity = quantity;
					strncpy(extra_dat[extra_num].name, name, 24);
					extra_num++;
				} else { // Invalid line -> file must be rewriten
					change_flag = 1;
				}
			}
			fclose(fp);
		} else {
			// file doesn't exist. Create it for explanation -> file must be rewriten
			change_flag = 1;
		}
	}

	// if extra_add_file can be readed and exists
	if ((fp = fopen(extra_add_file_txt, "r")) != NULL) {
		while(fgets(line, sizeof(line) - 1, fp) != NULL) {
			if ((line[0] == '/' && line[1] == '/') || line[0] == '\0' || line[0] == '\n' || line[0] == '\r')
				continue;
			// if line is valid
			if ((sscanf(line, "%d,%ld,%[^\r\n]", &item_id, &quantity, name) == 3 ||
			    sscanf(line, "%d\t%ld\t%[^\r\n]", &item_id, &quantity, name) == 3) &&
			    (item_id == -1 || (itemdb_exists(item_id) && (!battle_config.item_check || itemdb_available(item_id)))) && // zeny or valid items
			    quantity != 0 && // quantity
			    strlen(name) >= 4 && strlen(name) < 24) { // name
				// manage max quantity
				if (item_id == -1) {
					if (quantity > (long)MAX_ZENY)
						quantity = (long)MAX_ZENY;
					else if (quantity < -((long)MAX_ZENY))
						quantity = -((long)MAX_ZENY);
				} else {
					if (quantity > (long)MAX_AMOUNT)
						quantity = (long)MAX_AMOUNT;
					else if (quantity < -((long)MAX_AMOUNT))
						quantity = -((long)MAX_AMOUNT);
				}
				// add an index
				if (extra_num == 0) {
					extra_dat = (struct extra*)aCalloc(1, sizeof(struct extra));
				} else {
					extra_dat = (struct extra*)aRealloc(extra_dat, sizeof(struct extra) * (extra_num + 1));
					memset(&extra_dat[extra_num], 0, sizeof(struct extra));
				}
				extra_dat[extra_num].item_id = item_id;
				extra_dat[extra_num].quantity = quantity;
				strncpy(extra_dat[extra_num].name, name, 24);
				extra_num++;
				// new line -> files must be rewriten
				change_flag = 1;
			}
		}
		fclose(fp);
		// erase file
		remove(extra_add_file_txt);
	}

	// check players to give zenys or items
	for (i = 0; i < extra_num; i++) {
		if ((pl_sd = map_nick2sd(extra_dat[i].name)) != NULL) {
			item_id = extra_dat[i].item_id;
			quantity = extra_dat[i].quantity;

			// work on zenys
			if (item_id == -1) {
				// substract
				if (quantity < 0) {
					if ((long)pl_sd->status.zeny < -quantity)
						quantity = -((long)pl_sd->status.zeny);
					if (quantity < 0) {
						snprintf(output, sizeof output, msg_txt(149), -quantity); // Server (special action): you lost %ld zenys.
						clif_displaymessage(pl_sd->fd, output);
						pl_sd->status.zeny += quantity;
						clif_updatestatus(pl_sd, SP_ZENY);
						// line changed -> file must be rewriten
						extra_dat[i].quantity -= quantity;
						change_flag = 1;
					}
				// add
				} else {
					if (quantity > (long)(MAX_ZENY - pl_sd->status.zeny))
						quantity = (long)(MAX_ZENY - pl_sd->status.zeny);
					if (quantity > 0) {
						snprintf(output, sizeof output, msg_txt(150), quantity); // Server (special action): you gain %ld zenys.
						clif_displaymessage(pl_sd->fd, output);
						pl_sd->status.zeny += quantity;
						clif_updatestatus(pl_sd, SP_ZENY);
						// line changed -> file must be rewriten
						extra_dat[i].quantity -= quantity;
						change_flag = 1;
					}
				}

			// items -> check against item_id, because database can be reloaded.
			} else if ((item_data = itemdb_exists(item_id)) && (!battle_config.item_check || itemdb_available(item_id))) {
				int j;
				if (quantity < 0) { // remove items
					for (j = 0; j < MAX_INVENTORY; j++) {
						if (pl_sd->status.inventory[j].nameid == item_id && pl_sd->status.inventory[j].equip == 0) {
							if ((long)pl_sd->status.inventory[j].amount < -quantity)
								quantity = -((long)pl_sd->status.inventory[j].amount);
							if (quantity < 0) {
								if (pl_sd->status.inventory[i].card[0] == (short)0xff00)
									intif_delete_petdata(*((long *)(&pl_sd->status.inventory[i].card[1])));
								pc_delitem(pl_sd, j, -quantity, 0);
								snprintf(output, sizeof output, msg_txt(151), -quantity, item_data->jname); // Server (special action): you lost %ld %s.
								clif_displaymessage(pl_sd->fd, output);
								// line changed -> file must be rewriten
								extra_dat[i].quantity -= quantity;
								quantity = extra_dat[i].quantity; // to continue loop
								change_flag = 1;
							}
						}
					}
				} else { // add items
					int loop;
					struct item item_tmp;
					if ((long)item_data->weight * quantity > (long)(pl_sd->max_weight - pl_sd->weight)) {
						quantity = (long)((pl_sd->max_weight - pl_sd->weight) / item_data->weight);
						if (quantity <= 0)
							continue;
					}
					loop = 1;
					if (item_data->type == 4 || item_data->type == 5 ||
					    item_data->type == 7 || item_data->type == 8) {
						loop = (int)quantity;
						quantity = 1;
					}
					for(j = 0; j < loop; j++) {
						memset(&item_tmp, 0, sizeof(item_tmp));
						item_tmp.nameid = item_id;
						item_tmp.identify = 1;
						if (pc_additem(pl_sd, &item_tmp, quantity) == 0) { // item added
							snprintf(output, sizeof output, msg_txt(152), quantity, item_data->jname); // Server (special action): you obtain %ld %s.
							clif_displaymessage(pl_sd->fd, output);
							// line changed -> file must be rewriten
							extra_dat[i].quantity -= quantity;
							change_flag = 1;
						}
					}
				}

			} else {
				// invalid item_id -> file must be rewriten
				extra_dat[i].quantity = 0;
				change_flag = 1;
			}
		}
	}

	// If file changed?
	if (change_flag) {
		// remove void lines
		for (i = 0; i < extra_num; i++) {
			if (extra_dat[i].quantity == 0) {
				if (extra_num == 1) {
					aFree(extra_dat);
					extra_dat = NULL;
					extra_num--;
				} else {
					if (i != (extra_num - 1))
						memcpy(&extra_dat[i], &extra_dat[extra_num - 1], sizeof(struct extra));
					extra_num--;
					extra_dat = (struct extra*)aRealloc(extra_dat, sizeof(struct extra) * extra_num);
				}
				i--; // redo same index
			}
		}
		// write file
		if ((fp = lock_fopen(extra_file_txt, &lock)) != NULL) {
			fprintf(fp, "// このファイルの内容は変更しないでください！" RETCODE
			            "// MAPサーバによって自動的に管理されています" RETCODE
			            "// 追加したい場合は「%s」を利用してください" RETCODE
			            "//" RETCODE, extra_add_file_txt);
			for (i = 0; i < extra_num; i++)
				fprintf(fp,"%d,%ld,%s" RETCODE, extra_dat[i].item_id, extra_dat[i].quantity, extra_dat[i].name);
			lock_fclose(fp, extra_file_txt, &lock);
		}
	}

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

	if (extra_num > 0) {
		aFree(extra_dat);
		extra_dat = NULL;
		extra_num = 0;
	}

	return 0;
}

/*==========================================
 * pc関係初期化
 *------------------------------------------
 */
int do_init_pc(void)
{
	printf("MAX_VALID_PC_CLASS:%d\n",MAX_VALID_PC_CLASS);

	pc_readdb();
	pc_read_motd();
	pc_read_gm_account();

	add_timer_func_list(pc_natural_heal,"pc_natural_heal");
	add_timer_func_list(pc_invincible_timer,"pc_invincible_timer");
	add_timer_func_list(pc_eventtimer,"pc_eventtimer");
	add_timer_func_list(pc_calc_pvprank_timer,"pc_calc_pvprank_timer");
	add_timer_func_list(pc_autosave,"pc_autosave");
	add_timer_func_list(pc_spiritball_timer,"pc_spiritball_timer");
	add_timer_func_list(pc_coin_timer,"pc_coin_timer");
	add_timer_func_list(pc_extra,"pc_extra");
	add_timer_func_list(pc_itemlimit_timer,"pc_itemlimit_timer");

	natural_heal_prev_tick = gettick() + NATURAL_HEAL_INTERVAL;
	add_timer_interval(natural_heal_prev_tick,pc_natural_heal,0,0,NATURAL_HEAL_INTERVAL);

	add_timer(gettick()+autosave_interval,pc_autosave,0,0);
	add_timer_interval(gettick()+10000,pc_extra,0,0,60000);

	return 0;
}
