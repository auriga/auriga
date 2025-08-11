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

#define PVP_CALCRANK_INTERVAL 1000	// PVP���ʌv�Z�̊Ԋu
#define MAX_EXP_TABLE	18		// �o���l�e�[�u���ő吔�iexp.txt�̗񐔂ɍ��킹��j
#define MAX_SKILL_NEED	9		// �X�L���c���[�̗v���X�L���ő吔�iskill_tree.txt�j

static atn_bignumber exp_table[MAX_EXP_TABLE][MAX_LEVEL];

int stpoint_table[MAX_LEVEL];
int tstpoint_table[MAX_LEVEL];

// �����e�[�u��
int attr_fix_table[MAX_ELE_LEVEL][ELE_MAX][ELE_MAX];

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
	unsigned short base_level;
	unsigned short job_level;
	short class_level;	// �ĐU�莞�̕s���h�~�@�m�r:0 �ꎟ:1 ��:2 �O��:3
	short upper;
	struct {
		short id,lv;
	} need[MAX_SKILL_NEED];
} skill_tree[PC_JOB_MAX][MAX_SKILL_TREE];

static int dummy_gm_account = 0;

/*==========================================
 * ���[�J���v���g�^�C�v�錾 (�K�v�ȕ��̂�)
 *------------------------------------------
 */
static int pc_dead(struct block_list *src,struct map_session_data *sd);
static int pc_nightmare_drop(struct map_session_data *sd,short flag);
static int pc_equiplookall(struct map_session_data *sd);
static int pc_checkitemlimit(struct map_session_data *sd, int idx, unsigned int tick, unsigned int now, int first);
static int pc_setitemlimit(struct map_session_data *sd);
static int pc_calc_needskillpoint(struct map_session_data *sd, int class_level);


/*==========================================
 * �X�L���c���[���̌���
 *------------------------------------------
 */
static struct skill_tree_entry* pc_search_skilltree(struct pc_base_job *bj, int skillid)
{
	int min = -1;
	int max = MAX_SKILL_TREE;
	struct skill_tree_entry *st;

	nullpo_retr(NULL, bj);

	st = skill_tree[bj->job];

	// binary search
	while(max - min > 1) {
		int mid = (min + max) / 2;
		if(st[mid].id && st[mid].id == skillid)
			return &st[mid];

		// 0�̂Ƃ��͑�Ƃ݂Ȃ�
		if(st[mid].id == 0 || st[mid].id > skillid)
			max = mid;
		else
			min = mid;
	}
	return NULL;
}

/*==========================================
 * �X�L����MaxLv��Ԃ�
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
 * GM�֘A
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
 * PC���I���ł��邩�ǂ����̔���
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
 * ���G���ԃ^�C�}�[
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
 * ���G���ԃ^�C�}�[�Z�b�g
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
 * ���G���ԃ^�C�}�[�폜
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
 * �C���^�C�}�[
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
 * �C���^�C�}�[�Z�b�g
 *------------------------------------------
 */
int pc_addspiritball(struct map_session_data *sd,int interval,int num)
{
	int max = skill_get_max(MO_CALLSPIRITS);

	nullpo_retr(0, sd);

	/* �E�Ƃ������N�ƏC���̏ꍇ */
	if(sd->s_class.job == PC_JOB_MO || sd->s_class.job == PC_JOB_SR)
		max = pc_checkskill(sd,MO_CALLSPIRITS);		// �C���̏K�����x�����ő吔

	/* �������V */
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
 * �C���^�C�}�[�폜
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
 * �R�C���^�C�}�[
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
 * �R�C���^�C�}�[�Z�b�g
 *-----------------------------------------
 */
int pc_addcoin(struct map_session_data *sd,int interval,int max)
{
	nullpo_retr(0, sd);

	if(max > MAX_COIN)
		max = MAX_COIN;
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
 * �R�C���^�C�}�[�폜
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
	if(count > MAX_COIN)
		count = MAX_COIN;

	for(i=0; i<count; i++) {
		if(sd->coin.timer[i] != -1) {
			delete_timer(sd->coin.timer[i],pc_coin_timer);
			sd->coin.timer[i] = -1;
		}
	}
	for(i=count; i<MAX_COIN; i++) {
		sd->coin.timer[i-count] = sd->coin.timer[i];
		sd->coin.timer[i] = -1;
	}

	if(!type)
		clif_coin(sd);

	return 0;
}

/*==========================================
 * �e�T�E�O�̋��̃^�C�}�[
 *-----------------------------------------
 */
static int pc_elementball_timer(int tid, unsigned int tick, int id, void *data)
{
	struct map_session_data *sd = map_id2sd(id);
	int i;

	if( sd == NULL )
		return 1;

	// �s���ȃ^�C�}�[ID
	if( sd->elementball.timer[0] != tid )
	{
		if(battle_config.error_log)
			printf("elementball_timer %d != %d\n",sd->elementball.timer[0],tid);
		return 0;
	}

	// ���̂̃^�C�}�[�N���A
	sd->elementball.timer[0] = -1;
	for( i = 1; i < sd->elementball.num; i++ )
	{
		sd->elementball.timer[i-1] = sd->elementball.timer[i];
		sd->elementball.timer[i] = -1;
	}

	// ���̂̐������炷
	sd->elementball.num--;
	if(sd->elementball.num < 0)
		sd->elementball.num = 0;

	// �����l�N���A
	if(!sd->elementball.num)
		sd->elementball.ele = ELE_NEUTRAL;

#ifdef PRE_RENEWAL
	// �y�����Ȃ�atk���������邽�߃X�e�[�^�X���v�Z������
	if(sd->elementball.ele == ELE_EARTH)
		status_calc_pc(sd,0);
#endif

	// �p�P�b�g���M
	clif_elementball(sd);

	return 0;
}

/*==========================================
 * �e�T�E�O�̋��̃Z�b�g
 *-----------------------------------------
 */
int pc_addelementball(struct map_session_data *sd, int interval, int max, short ele)
{
	nullpo_retr(0, sd);

	// �ő�l�`�F�b�N
	if(max > MAX_ELEMENTBALL)
		max = MAX_ELEMENTBALL;

	// �����`�F�b�N
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
	// �y�����Ȃ�atk�����シ�邽�߃X�e�[�^�X���v�Z������
	if(ele == ELE_EARTH)
		status_calc_pc(sd,0);
#endif

	// �p�P�b�g���M
	clif_elementball(sd);

	return 0;
}

/*==========================================
 * �e�T�E�O�̃^�C�}�[�폜
 *-----------------------------------------
 */
int pc_delelementball(struct map_session_data *sd, int count, int type)
{
	int i;

	nullpo_retr(0, sd);

	// �����`�F�b�N
	if( sd->elementball.num <= 0 )
	{
		sd->elementball.num = 0;
		sd->elementball.ele = ELE_NEUTRAL;
		return 0;
	}

	// �폜���̃`�F�b�N
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

	// �y�����Ȃ�def��atk���ϓ����邽�߃X�e�[�^�X���v�Z������
	if(sd->elementball.ele == ELE_EARTH)
		status_calc_pc(sd,0);

	// �����l�N���A
	if(sd->elementball.num < 1)
		sd->elementball.ele = ELE_NEUTRAL;

	if(!type)
		clif_elementball(sd);

	return 0;
}

/*==========================================
 * �\�E���G�i�W�[�^�C�}�[
 *------------------------------------------
 */
static int pc_soulenergy_timer(int tid,unsigned int tick,int id,void *data)
{
	struct map_session_data *sd = map_id2sd(id);
	int i;

	if(sd == NULL)
		return 1;

	if(sd->soulenergy.timer[0] != tid) {
		if(battle_config.error_log)
			printf("soulenergy_timer %d != %d\n",sd->soulenergy.timer[0],tid);
		return 0;
	}
	sd->soulenergy.timer[0] = -1;
	for(i=1; i<sd->soulenergy.num; i++) {
		sd->soulenergy.timer[i-1] = sd->soulenergy.timer[i];
		sd->soulenergy.timer[i] = -1;
	}
	sd->soulenergy.num--;
	if(sd->soulenergy.num < 0)
		sd->soulenergy.num = 0;
	clif_soulenergy(sd);

	return 0;
}

/*==========================================
 * �\�E���G�i�W�[�ǉ�
 *------------------------------------------
 */
int pc_addsoulenergy(struct map_session_data *sd,int interval,int num)
{
	int max = 5;
	int before;

	nullpo_retr(0, sd);

	/* �\�E���G�i�W�[���� */
	max += pc_checkskill(sd,SP_SOULENERGY) * 3;

	if(max > MAX_SOULENERGY)
		max = MAX_SOULENERGY;

	if(sd->soulenergy.num < 0)
		sd->soulenergy.num = 0;

	before = sd->soulenergy.num;

	if(max > 0) {
		int i;
		unsigned int tick = gettick();
		for(i = num; i > 0; i--) {
			if(sd->soulenergy.num >= max) {
				// �ő吔�ɒB���Ă���ꍇ�͍X�V���Ȃ�
				break;
			}
			sd->soulenergy.num++;
			sd->soulenergy.timer[sd->soulenergy.num-1] = add_timer(tick+interval+sd->soulenergy.num,pc_soulenergy_timer,sd->bl.id,NULL);
		}
	}
	if(sd->soulenergy.num != before) {
		status_calc_pc(sd,0);
		clif_soulenergy(sd);
	}

	return 0;
}

/*==========================================
 * �\�E���G�i�W�[�폜
 *------------------------------------------
 */
int pc_delsoulenergy(struct map_session_data *sd,int count,int type)
{
	int i;

	nullpo_retr(0, sd);

	if(sd->soulenergy.num <= 0) {
		sd->soulenergy.num = 0;
		return 0;
	}

	if(count > sd->soulenergy.num)
		count = sd->soulenergy.num;
	sd->soulenergy.num -= count;
	if(count > MAX_SOULENERGY)
		count = MAX_SOULENERGY;

	for(i=0; i<count; i++) {
		if(sd->soulenergy.timer[i] != -1) {
			delete_timer(sd->soulenergy.timer[i],pc_soulenergy_timer);
			sd->soulenergy.timer[i] = -1;
		}
	}
	for(i=count; i<MAX_SOULENERGY; i++) {
		sd->soulenergy.timer[i-count] = sd->soulenergy.timer[i];
		sd->soulenergy.timer[i] = -1;
	}
	status_calc_pc(sd,0);

	if(!type)
		clif_soulenergy(sd);

	return 0;
}

/*==========================================
 * ���̃^�C�}�[
 *------------------------------------------
 */
static int pc_ball_timer(int tid,unsigned int tick,int id,void *data)
{
	struct map_session_data *sd = map_id2sd(id);
	int i;

	if(sd == NULL)
		return 1;

	if(sd->ball.timer[0] != tid) {
		if(battle_config.error_log)
			printf("ball_timer %d != %d\n",sd->ball.timer[0],tid);
		return 0;
	}
	sd->ball.timer[0] = -1;
	for(i=1; i<sd->ball.num; i++) {
		sd->ball.timer[i-1] = sd->ball.timer[i];
		sd->ball.timer[i] = -1;
	}
	sd->ball.num--;
	if(sd->ball.num < 0)
		sd->ball.num = 0;
	clif_ball(sd);

	return 0;
}

/*==========================================
 * ���̒ǉ�
 *------------------------------------------
 */
int pc_addball(struct map_session_data *sd,int interval,int num)
{
	int i;
	unsigned int tick = gettick();
	int before;

	nullpo_retr(0, sd);

	if(sd->ball.num < 0)
		sd->ball.num = 0;

	before = sd->ball.num;

	for(i = num; i > 0; i--) {
		if(sd->ball.num >= MAX_BALL) {
			// �ő吔�ɒB���Ă���ꍇ�͍X�V���Ȃ�
			break;
		}
		sd->ball.num++;
		sd->ball.timer[sd->ball.num-1] = add_timer(tick+interval+sd->ball.num,pc_ball_timer,sd->bl.id,NULL);
	}

	if(sd->ball.num != before) {
		clif_ball(sd);
	}

	return 0;
}

/*==========================================
 * ���̍폜
 *------------------------------------------
 */
int pc_delball(struct map_session_data *sd,int count,int type)
{
	int i;

	nullpo_retr(0, sd);

	if(sd->ball.num <= 0) {
		sd->ball.num = 0;
		return 0;
	}

	if(count > sd->ball.num)
		count = sd->ball.num;
	sd->ball.num -= count;
	if(count > MAX_BALL)
		count = MAX_BALL;

	for(i=0; i<count; i++) {
		if(sd->ball.timer[i] != -1) {
			delete_timer(sd->ball.timer[i],pc_ball_timer);
			sd->ball.timer[i] = -1;
		}
	}
	for(i=count; i<MAX_BALL; i++) {
		sd->ball.timer[i-count] = sd->ball.timer[i];
		sd->ball.timer[i] = -1;
	}

	if(!type)
		clif_ball(sd);

	return 0;
}

/*==========================================
 * Exp�y�i���e�B
 *   type&1 : �o���l�X�V
 *   type&2 : ���f�B���v�e�B�I
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

	idx = pc_search_inventory(sd, 6413);	// �g����̌아

	// ���f�B���v�e�B�I�̃y�i���e�B�̏ꍇ�A�I�[���Ȃ�Ό��݂̎擾�o���l���獷������
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
		clif_msgstringtable(sd,0x729);	// �g����̌아�����������܂����B
	}

	if(ssd) {
		// PK�d�l�APK�}�b�v�ōU�����l�Ԃ������łȂ�(GX�Ȃǂ̑΍�)
		if(map[sd->bl.m].flag.pk && sd->bl.id != ssd->bl.id && ranking_get_point(ssd,RK_PK) >= battle_config.pk_murderer_point) {
			if(loss_base > 0 || loss_job > 0)
				pc_gainexp(ssd,NULL,loss_base,loss_job,0);
		}
	}
	return 1;
}

/*==========================================
 * ���X�^�[�g���̃f�[�^�Z�b�g
 *------------------------------------------
 */
int pc_setrestartvalue(struct map_session_data *sd,int type)
{
	nullpo_retr(0, sd);

	if(sd->special_state.restart_full_recover) {	// �I�V���X�J�[�h
		sd->status.hp = sd->status.max_hp;
		sd->status.sp = sd->status.max_sp;
	} else {
		if(sd->s_class.job != PC_JOB_NV) {	// �m�r�͊��Ɏ��S�����HP�␳�ς�
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
		if(!(battle_config.death_penalty_type&1))	// �f�X�y�i
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
 * save�ɕK�v�ȃX�e�[�^�X�C�����s�Ȃ�
 *------------------------------------------
 */
int pc_makesavestatus(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	// ���̐F�͐F�X���Q�������̂ŕۑ��Ώۂɂ͂��Ȃ�
	if(!battle_config.save_clothcolor)
		sd->status.clothes_color = 0;

	// ���S��Ԃ������̂�hp��1�A�ʒu���Z�[�u�ꏊ�ɕύX
	if(unit_isdead(&sd->bl)) {
		pc_setrestartvalue(sd,0);
		memcpy(&sd->status.last_point,&sd->status.save_point,sizeof(sd->status.last_point));
	} else {
		memcpy(sd->status.last_point.map,sd->mapname,24);
		sd->status.last_point.x = sd->bl.x;
		sd->status.last_point.y = sd->bl.y;
	}

	// �Z�[�u�֎~�}�b�v�������̂Ŏw��ʒu�Ɉړ�
	if(map[sd->bl.m].flag.nosave) {
		struct map_data *m = &map[sd->bl.m];
		if(strcmp(m->save.map,"SavePoint") == 0)
			memcpy(&sd->status.last_point,&sd->status.save_point,sizeof(sd->status.last_point));
		else
			memcpy(&sd->status.last_point,&m->save,sizeof(sd->status.last_point));
	}
	// �������A���_���W�����ɋ���̂ŁA�ʒu���Z�[�u�ꏊ�ɕύX
	else if(map[sd->bl.m].memorial_id) {
		memcpy(&sd->status.last_point,&sd->status.save_point,sizeof(sd->status.last_point));
	}

	// �A���P�~�̘A���������ۑ�
	if(battle_config.save_am_pharmacy_success && (sd->am_pharmacy_success > 0 || ranking_get_point(sd,RK_ALCHEMIST) > 0))
		pc_setglobalreg(sd,"PC_PHARMACY_SUCCESS_COUNT",sd->am_pharmacy_success);

	// �����L���O�|�C���g�̕ۑ�
	if(battle_config.save_all_ranking_point_when_logout)
		ranking_setglobalreg_all(sd);

	// �N���[���X�L���ۑ�
	if(sd->skill_clone.id || sd->skill_clone.lv) {
		pc_setglobalreg(sd,"PC_CLONESKILL_ID",sd->skill_clone.id);
		pc_setglobalreg(sd,"PC_CLONESKILL_LV",sd->skill_clone.lv);
	}

	// ���v���f���[�X�ۑ�
	if(sd->skill_reproduce.id || sd->skill_reproduce.lv) {
		pc_setglobalreg(sd,"PC_REPRODUCE_ID",sd->skill_reproduce.id);
		pc_setglobalreg(sd,"PC_REPRODUCE_LV",sd->skill_reproduce.lv);
	}

	// �L���[���ۑ�
	if(battle_config.save_pckiller_type) {
		pc_setglobalreg(sd,"PC_KILL_CHAR",sd->kill.char_id);
		pc_setglobalreg(sd,"PC_KILLED_CHAR",sd->kill.merderer_char_id);
	}

	// �V���b�v�|�C���g�ۑ�
	pc_setglobalreg(sd,"PC_SHOP_POINT",sd->shop_point);

	// �a���ۑ�
	pc_setaccountreg(sd,"#PC_DEPOSIT",sd->deposit);

	// �}�i�[�|�C���g���v���X�������ꍇ0��
	if(sd->status.manner > 0)
		sd->status.manner = 0;

	// option�̃R�s�[
	sd->status.option = sd->sc.option;

	return 0;
}

/*==========================================
 * ����
 *------------------------------------------
 */
void pc_setsit(struct map_session_data *sd)
{
	nullpo_retv(sd);

	sd->state.dead_sit = 2;
	clif_status_load_id(sd,SI_SIT,1);
}

/*==========================================
 * �����オ��
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
 * �Z�[�u�|�C���g�̕ۑ�
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
 * �ڑ����̏�����
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
 * �����ӏ���Ԃ�
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
 * ����^�C�v���v�Z
 *------------------------------------------
 */
static int pc_calcweapontype(struct map_session_data *sd)
{
	short right, left;

	nullpo_retr(0, sd);

	right = sd->weapontype1;
	left  = sd->weapontype2;

	if(right != WT_FIST && left == WT_FIST)			// �E�蕐��̂�
		sd->status.weapon = right;
	else if(right == WT_FIST && left != WT_FIST)		// ���蕐��̂�
		sd->status.weapon = left;
	else if(right == WT_DAGGER && left == WT_DAGGER)	// �o�Z��
		sd->status.weapon = WT_DOUBLE_DD;
	else if(right == WT_1HSWORD && left == WT_1HSWORD)	// �o�Ў茕
		sd->status.weapon = WT_DOUBLE_SS;
	else if(right == WT_1HAXE && left == WT_1HAXE)		// �o�Ў蕀
		sd->status.weapon = WT_DOUBLE_AA;
	else if( (right == WT_DAGGER && left == WT_1HSWORD) || (right == WT_1HSWORD && left == WT_DAGGER) )	// �Z��-�Ў茕
		sd->status.weapon = WT_DOUBLE_DS;
	else if( (right == WT_DAGGER && left == WT_1HAXE) || (right == WT_1HAXE && left == WT_DAGGER) )		// �Z��-�Ў蕀
		sd->status.weapon = WT_DOUBLE_DA;
	else if( (right == WT_1HSWORD && left == WT_1HAXE) || (right == WT_1HAXE && left == WT_1HSWORD) )	// �Ў茕-�Ў蕀
		sd->status.weapon = WT_DOUBLE_SA;
	else
		sd->status.weapon = right;

	return 0;
}

/*==========================================
 * �N���XID����E�ƒl�̃r�b�g��Ԃ�
 *------------------------------------------
 */
unsigned int pc_get_job_bit(int job)
{
	unsigned int bit = 0;

	// �E�ƒl��db�̐E�ƒl�ɍ��킹�Đݒ�
	switch(job) {
		case PC_JOB_NV:		// �m�[�r�X
			bit = 0x00000001;
			break;
		case PC_JOB_SM:		// �\�[�h�}��
			bit = 0x00000002;
			break;
		case PC_JOB_MG:		// �}�W�V����
			bit = 0x00000004;
			break;
		case PC_JOB_AC:		// �A�[�`���[
			bit = 0x00000008;
			break;
		case PC_JOB_AL:		// �A�R���C�g
		case PC_JOB_MB:		// �L�����V�[�i�b��j
			bit = 0x00000010;
			break;
		case PC_JOB_MC:		// �}�[�`�����g
			bit = 0x00000020;
			break;
		case PC_JOB_TF:		// �V�[�t
			bit = 0x00000040;
			break;
		case PC_JOB_KN:		// �i�C�g
		case PC_JOB_DE:		// �f�X�i�C�g�i�b��j
		case PC_JOB_RK:		// ���[���i�C�g
		case PC_JOB_DK:		// �h���S���i�C�g
			bit = 0x00000080;
			break;
		case PC_JOB_PR:		// �v���[�X�g
		case PC_JOB_AB:		// �A�[�N�r�V���b�v
		case PC_JOB_CD:		// �J�[�f�B�i��
			bit = 0x00000100;
			break;
		case PC_JOB_WZ:		// �E�B�U�[�h
		case PC_JOB_WL:		// �E�H�[���b�N
		case PC_JOB_AG:		// �A�[�N���C�W
			bit = 0x00000200;
			break;
		case PC_JOB_BS:		// �u���b�N�X�~�X
		case PC_JOB_NC:		// ���J�j�b�N
		case PC_JOB_MT:		// �}�C�X�^�[
			bit = 0x00000400;
			break;
		case PC_JOB_HT:		// �n���^�[
		case PC_JOB_RA:		// �����W���[
		case PC_JOB_WH:		// �E�B���h�z�[�N
			bit = 0x00000800;
			break;
		case PC_JOB_AS:		// �A�T�V��
		case PC_JOB_GC:		// �M���`���N���X
		case PC_JOB_SHC:	// �V���h�E�N���X
			bit = 0x00001000;
			break;
		case PC_JOB_CR:		// �N���Z�C�_�[
		case PC_JOB_LG:		// ���C�����K�[�h
		case PC_JOB_IG:		// �C���y���A���K�[�h
			bit = 0x00004000;
			break;
		case PC_JOB_MO:		// �����N
		case PC_JOB_SR:		// �C��
		case PC_JOB_IQ:		// �C���N�C�W�^�[
			bit = 0x00008000;
			break;
		case PC_JOB_SA:		// �Z�[�W
		case PC_JOB_SO:		// �\�[�T���[
		case PC_JOB_EM:		// �G�������^���}�X�^�[
			bit = 0x00010000;
			break;
		case PC_JOB_RG:		// ���[�O
		case PC_JOB_SC:		// �V���h�E�`�F�C�T�[
		case PC_JOB_ABC:	// �A�r�X�`�F�C�T�[
			bit = 0x00020000;
			break;
		case PC_JOB_AM:		// �A���P�~�X�g
		case PC_JOB_DA:		// �_�[�N�R���N�^�[�i�b��j
		case PC_JOB_GN:		// �W�F�l�e�B�b�N
		case PC_JOB_BO:		// �o�C�I��
			bit = 0x00040000;
			break;
		case PC_JOB_BA:		// �o�[�h
		case PC_JOB_MI:		// �~���X�g����
		case PC_JOB_TRB:	// �g���o�h�D�[��
			bit = 0x00080000;
			break;
		case PC_JOB_DC:		// �_���T�[
		case PC_JOB_WA:		// �����_���[
		case PC_JOB_TRV:	// �g�����F�[��
			bit = 0x00100000;
			break;
		case PC_JOB_SNV:	// �X�[�p�[�m�[�r�X
		case PC_JOB_ESNV:	// �g���X�[�p�[�m�[�r�X
		case PC_JOB_HN:		// �n�C�p�[�m�[�r�X
			bit = 0x00800000;
			break;
		case PC_JOB_TK:		// �e�R���L�b�h
			bit = 0x01000000;
			break;
		case PC_JOB_SG:		// ����
		case PC_JOB_SJ:		// ����
		case PC_JOB_SKE:	// �V��
			bit = 0x02000000;
			break;
		case PC_JOB_SL:		// �\�E�������J�[
		case PC_JOB_SP:		// �\�E�����[�p�[
		case PC_JOB_SOA:	// �\�E���A�Z�e�B�b�N
			bit = 0x08000000;
			break;
		case PC_JOB_GS:		// �K���X�����K�[
		case PC_JOB_RL:		// ���x���I��
		case PC_JOB_NW:		// �i�C�g�E�H�b�`
			bit = 0x10000000;
			break;
		case PC_JOB_NJ:		// �E��
		case PC_JOB_KG:		// �e�T
		case PC_JOB_OB:		// �O
		case PC_JOB_SK:		// 凋C�O
		case PC_JOB_SN:		// �s�m��
			bit = 0x20000000;
			break;
		case PC_JOB_SUM:		// �T���i�[
		case PC_JOB_SH:			// �X�s���b�g�n���h���[
			bit = 0x40000000;
			break;
	}

	return bit;
}

/*==========================================
 * �֎~����Ă���A�C�e�����ǂ���
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
		// �e���|�֎~���Ŏg�p�s�̃A�C�e���Ȃ烁�b�Z�[�W�o��
		if(zone&32)
			clif_skill_teleportmessage(sd,0);
		if(zone&128)
			clif_msgstringtable(sd, 0x743);	// ���̃}�b�v�ł͏����A�C�e�����g�p�ł��܂���B
		return 1;
	}

	return 0;
}

/*==========================================
 * �����\���ǂ���
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

	// �L���X�e�B���O��
	//if(sd->state.casting) return 0;

	// �X�p�m�r�̍�
	if(sd->sc.data[SC_SUPERNOVICE].timer != -1) {
		if(item->equip & LOC_RARM && sd->status.base_level >= 96)
		{
			if(sd->sc.data[SC_STRIPWEAPON].timer != -1)
				return 0;
			if(item->wlv >= 4 && itemdb_isweapon(item->nameid))
			{
				// Lv4�̕��������
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
		// ���֌W
		if(sd->status.base_level >= 90)
		{
			// �ꉞ���x�������`�F�b�N
			if(item->elv > 0 && sd->status.base_level < item->elv)
				return -1;
			// ���ŃX�g���b�v�Ȃ玸�s
			if(item->equip & LOC_HEAD2 && sd->sc.data[SC_STRIPHELM].timer != -1)
				return 0;
			// ���Ȃ琬��
			// ����i
			if(item->equip & LOC_HEAD2)
				return 1;
			// �����i
			if(item->equip & LOC_HEAD3)
				return 1;
			// �����i
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

	// �J�[�h���g�p�֎~�i�łȂ����`�F�b�N
	for(i=0; i<item->slot; i++) {
		if((card_id = sd->status.inventory[n].card[i]) == 0)
			break;
		// ��������A�����A�C�e�����O
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
		if(battle_config.casting_penalty_type == 1) {		// ����Ɩ�
			if(item->equip & LOC_RARM)
				return 0;
			if(item->equip & LOC_ARROW)
				return 0;
		} else if(battle_config.casting_penalty_type == 2) {	// ��
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
		} else if(battle_config.casting_penalty_type == 3) {	// �S��
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
	if(sd->sc.data[SC_SHADOW_STRIP].timer != -1 && item->equip & LOC_SHADOW_ALL)
		return 0;

	return 1;
}

/*==========================================
 * session id�ɖ�薳��
 * char�I���瑗���Ă����X�e�[�^�X��ݒ�
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
		// �j�dlogin��Ԃ������̂ŁA��������
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

	session[sd->fd]->auth = 1;	// �F�؏I���� socket.c �ɓ`����

	memset(&sd->state,0,sizeof(sd->state));

	// ��{�I�ȏ�����
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

	// �C���E�R�C���E�e�T�A�O�̋��̏�����
	sd->spiritball.num = 0;
	sd->spiritball.old = 0;
	sd->coin.num = 0;
	sd->elementball.num = 0;
	sd->elementball.ele = ELE_NEUTRAL;

	for(i=0; i<MAX_SPIRITBALL; i++) {
		sd->spiritball.timer[i] = -1;
	}

	for(i=0; i<MAX_COIN; i++) {
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

	// �A�J�E���g�ϐ��̑��M�v��
	intif_request_accountreg(sd);

	// �N�G�X�g���X�g�̑��M�v��
	intif_request_quest(sd->status.account_id,sd->status.char_id);

	// ���у��X�g�̑��M�v��
	intif_request_achieve(sd->status.account_id,sd->status.char_id);

	// �y�b�g������
	sd->petDB = NULL;
	sd->pd = NULL;
	memset(&sd->pet,0,sizeof(struct s_pet));

	// �z��������
	sd->hd = NULL;
	memset(&sd->hom,0,sizeof(struct mmo_homunstatus));

	// �b��������
	sd->mcd = NULL;

	// ���쏉����
	sd->eld = NULL;

#ifdef DYNAMIC_SC_DATA
	// �_�~�[�}��
	sd->sc.data = dummy_sc_data;
#else
	// �X�e�[�^�X�ُ�̏�����
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
	sd->sc.option = sd->status.option;	// option��sc�Ɉڂ��Ďg��

	// �A�C�e���`�F�b�N�͕K���X�e�[�^�X�ُ�̏�������ɍs��
	sd->state.inventory_dirty = 1;
	sd->state.cart_dirty = 1;
	sd->inventory_timer = NULL;
	pc_checkitem(sd);
	pc_setitemlimit(sd);

	// �}�i�[�|�C���g���v���X�������ꍇ0��
	if(battle_config.nomanner_mode && sd->status.manner > 0)
		sd->status.manner = 0;

	// �p�[�e�B�[�֌W�̏�����
	sd->party_invite = 0;
	sd->party_x      = -1;
	sd->party_y      = -1;
	sd->party_hp     = -1;

	// �M���h�֌W�̏�����
	sd->guild_invite   = 0;
	sd->guild_alliance = 0;
	sd->guild_x        = -1;
	sd->guild_y        = -1;

	// �F�B�֌W�̏�����
	sd->friend_invite = 0;

	sd->adopt_invite = 0;

	// �C�x���g�֌W�̏�����
	memset(sd->eventqueue,0,sizeof(sd->eventqueue));
	for(i=0; i<MAX_EVENTTIMER; i++)
		sd->eventtimer[i] = -1;

	// �ʒu�̐ݒ�
	if(pc_setpos(sd, sd->status.last_point.map, sd->status.last_point.x, sd->status.last_point.y, 0)) {
		// ���s�����̂Őڑ���ؒf����
		clif_authfail_fd(sd->fd,0);
		session[sd->fd]->auth = 0;
		return 1;
	}

	// �y�b�g�A�z���A�b���A����f�[�^�v��
	if(sd->status.pet_id > 0)
		intif_request_petdata(sd->status.account_id,sd->status.char_id,sd->status.pet_id);
	if(sd->status.homun_id > 0)
		intif_request_homdata(sd->status.account_id,sd->status.char_id,sd->status.homun_id);
	if(sd->status.merc_id > 0)
		intif_request_mercdata(sd->status.account_id,sd->status.char_id,sd->status.merc_id);
	if(sd->status.elem_id > 0)
		intif_request_elemdata(sd->status.account_id,sd->status.char_id,sd->status.elem_id);

	// �p�[�e�B�A�M���h�f�[�^�̗v��
	if( sd->status.party_id > 0 && party_search(sd->status.party_id) == NULL )
		party_request_info(sd->status.party_id);
	if( sd->status.guild_id > 0 && guild_search(sd->status.guild_id) == NULL )
		guild_request_info(sd->status.guild_id);

	// �p�[�g�i�[�̖��O�v��
	if( sd->status.partner_id > 0 && map_charid2nick(sd->status.partner_id) == NULL )
		chrif_searchcharid(sd->status.partner_id);

	// pvp�̐ݒ�
	sd->pvp_rank  = 0;
	sd->pvp_point = 0;
	sd->pvp_timer = -1;

	// �ʒm
	clif_authok(sd);
	map_addnickdb(sd);
	map_addchariddb(sd->status.char_id,sd->status.name,sd->status.account_id,clif_getip(),clif_getport());

	// �e�R���~�b�V�����^�[�Q�b�g�̃X�N���v�g�ϐ�����̓ǂݏo����sd�ւ̃Z�b�g
	sd->tk_mission_target = pc_readglobalreg(sd,"PC_MISSION_TARGET");

	// �����L���O�p�|�C���g�̃X�N���v�g�ϐ�����̓ǂݏo����sd�ւ̃Z�b�g
	ranking_readreg(sd);

	// �t�@�[�}�V�[�A�������J�E���^ �N����0��
	if(battle_config.save_am_pharmacy_success)
		sd->am_pharmacy_success = pc_readglobalreg(sd,"PC_PHARMACY_SUCCESS_COUNT");
	else
		sd->am_pharmacy_success = 0;

	// ���z�ƌ��Ɛ��̊���
	for(i=0; i<3; i++) {
		if(!battle_config.save_feel_map)
			sd->status.feel_map[i][0] = '\0';
		if(sd->status.feel_map[i][0])
			sd->feel_index[i] = map_mapname2mapid(sd->status.feel_map[i]);
		else
			sd->feel_index[i] = -1;
	}

	// ���z�ƌ��Ɛ��̑�����
	if(battle_config.save_hate_mob) {
		// �Ȃ������ꍇ�O�ɂȂ�̂�-1 �ۑ���+1���邱��
		sd->hate_mob[0] = pc_readglobalreg(sd,"PC_HATE_MOB_SUN")  - 1;
		sd->hate_mob[1] = pc_readglobalreg(sd,"PC_HATE_MOB_MOON") - 1;
		sd->hate_mob[2] = pc_readglobalreg(sd,"PC_HATE_MOB_STAR") - 1;
	} else {
		sd->hate_mob[0] = -1;
		sd->hate_mob[1] = -1;
		sd->hate_mob[2] = -1;
	}

	// �L���[
	if(battle_config.save_pckiller_type) {
		sd->kill.char_id   = pc_readglobalreg(sd,"PC_KILL_CHAR");
		sd->kill.merderer_char_id = pc_readglobalreg(sd,"PC_KILLED_CHAR");
	} else {
		memset(&sd->kill,0,sizeof(sd->kill));
	}

	// �V���b�v�|�C���g
	sd->shop_point = pc_readglobalreg(sd,"PC_SHOP_POINT");

	// �X�e�[�^�X�����v�Z�Ȃ�
	status_calc_pc(sd,1);

	// �N���[���X�L���̏�����
	if((lv = pc_checkskill2(sd,RG_PLAGIARISM)) > 0) {
		sd->skill_clone.id = pc_readglobalreg(sd,"PC_CLONESKILL_ID");
		sd->skill_clone.lv = pc_readglobalreg(sd,"PC_CLONESKILL_LV");
		if(sd->skill_clone.id > 0 && sd->skill_clone.lv > lv)	// �O�̂��߃��x���`�F�b�N
			sd->skill_clone.lv = lv;
	} else {
		memset(&sd->skill_clone,0,sizeof(sd->skill_clone));
	}

	// ���v���f���[�X�̏�����
	if((lv = pc_checkskill2(sd,SC_REPRODUCE)) > 0) {
		sd->skill_reproduce.id = pc_readglobalreg(sd,"PC_REPRODUCE_ID");
		sd->skill_reproduce.lv = pc_readglobalreg(sd,"PC_REPRODUCE_LV");
		if(sd->skill_reproduce.id > 0 && sd->skill_reproduce.lv > lv)	// �O�̂��߃��x���`�F�b�N
			sd->skill_reproduce.lv = lv;
	} else {
		sd->skill_reproduce.id = 0;
		sd->skill_reproduce.lv = 0;
	}

	// MailData
	sd->mail_append.index  = -1;
	sd->mail_append.amount = 0;
	sd->mail_append.zeny   = 0;

	// �z�b�g�L�[�Z�b�g
	sd->hotkey_set = 0;
	memset(&sd->hotkey_rotate,0,sizeof(sd->hotkey_rotate));

	// �����`���b�g��on
	sd->state.alliance_message = 0;

	// Message of the Day�̑��M
	msg_send_motd(sd);

	return 0;
}

/*==========================================
 * session id�ɖ�肠��Ȃ̂Ō�n��
 *------------------------------------------
 */
int pc_authfail(int id)
{
	struct map_session_data *sd = map_id2sd(id);

	if(sd == NULL)
		return 1;
	if(sd->new_fd) {
		// �j�dlogin��Ԃ������̂ŁA�V�����ڑ��̂ݗ���
		clif_authfail_fd(sd->new_fd,0);

		sd->new_fd = 0;
		return 0;
	}
	clif_authfail_fd(sd->fd,0);
	return 0;
}

/*==========================================
 * �X�L���|�C���g���v�Z
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
 * ���݂̐E�Ƃ������E�����擾
 *  �߂�l= 0:�m�[�r�X
 *          1:�ꎟ�E�ATK�AGS�ANJ�ASNV�A�T���i�[
 *          2:�񎟐E�ASG�ASL�ARL�AKG�AOB�AESNV
 *          3:�O���E�ASE�ARE
 *          4:�l���E�A�g���l���E
 *------------------------------------------
 */
static int pc_get_classlevel(struct map_session_data *sd)
{
	int classlevel = 0;

	nullpo_retr(0, sd);

	if(pc_is1stclass(sd)) {
		classlevel = 1;
	} else if(pc_is2ndclass(sd)) {
		classlevel = 2;
	} else if(pc_is3rdclass(sd)) {
		classlevel = 3;
	} else if(pc_is4thclass(sd)) {
		classlevel = 4;
	}

	return classlevel;
}

/*==========================================
 * �o������X�L���̌v�Z
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
		if(!pc_isdoram(sd)) {		// �h�����n��ȊO
			if(skill_point < pc_calc_needskillpoint(sd,1)) {	// �ꎟ�E�X�L���K���s�i��{�X�L�����K���j�ł����
				c = PC_JOB_NV;			// �m�[�r�X����
			} else if( pc_get_classlevel(sd) > 1 && skill_point < pc_calc_needskillpoint(sd,2)) {	// �񎟐E�ȏ�ňꎟ�E�̃X�L���|�C���g�������ł����
				c = pc_get_base_job(c,1);	// �ꎟ�E����
			} else if( pc_get_classlevel(sd) > 2 && skill_point < pc_calc_needskillpoint(sd,3)) {	// �O���E�ȏ�ňꎟ�E/�񎟐E�̃X�L���|�C���g�������ł����
				c = pc_get_base_job(c,2);	// �񎟐E����
			} else if( pc_get_classlevel(sd) > 3 && skill_point < pc_calc_needskillpoint(sd,4)) {	// �O���E�ȏ�ňꎟ�E�`�O���E�̃X�L���|�C���g�������ł����
				c = pc_get_base_job(c,3);	// �O���E����
			}
		}
	}

	for(i=0; i<MAX_PCSKILL; i++) {
		sd->status.skill[i].id = 0;
		if(sd->status.skill[i].flag) {		// card�X�L���Ȃ�
			sd->status.skill[i].lv   = (sd->status.skill[i].flag == 1)? 0: sd->status.skill[i].flag-2;	// �{����lv��
			sd->status.skill[i].flag = 0;	// flag��0�ɂ��Ă���
		}
	}
	if(battle_config.gm_allskill > 0 && pc_isGM(sd) >= battle_config.gm_allskill) {
		// �S�ẴX�L��
		for(i=1; i<158; i++)
			sd->status.skill[i].id = i;
		for(i=210; i<291; i++)
			sd->status.skill[i].id = i;
		if(battle_config.gm_allskill_addabra) { // �A�u���J�^�u����p�X�L��
			for(i=291; i<304; i++)
				sd->status.skill[i].id = i;
		}
		// �����X�L���ƃg�}�z�[�N���O
		for(i=304; i<331; i++)
			sd->status.skill[i].id = i;
		// �{�q�X�L�����O
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
		// �ʏ�̌v�Z
		int id, flag;
		do {
			flag = 0;
			for(i=0; (id = skill_tree[c][i].id) > 0; i++) {
				if(sd->status.skill[id].id > 0)
					continue;
				if(!battle_config.skillfree && !tk_ranker_bonus) {
					int j, fail = 0;
					for(j=0; j<MAX_SKILL_NEED && skill_tree[c][i].need[j].id > 0; j++) {
						if(pc_checkskill2(sd,skill_tree[c][i].need[j].id) < skill_tree[c][i].need[j].lv) {
							fail = 1;
							break;
						}
					}
					if(fail)
						continue;
					if(sd->status.base_level < skill_tree[c][i].base_level ||
					   sd->status.job_level < skill_tree[c][i].job_level)
						continue;
					if(skill_tree[c][i].upper > 0 && sd->s_class.upper != skill_tree[c][i].upper)
						continue;
				}
				sd->status.skill[id].id = id;
				flag = 1;
			}
		} while(flag);
	}
	// �q����
	if(sd->status.baby_id > 0)
	{
		sd->status.skill[WE_CALLBABY].id   = WE_CALLBABY;
		sd->status.skill[WE_CALLBABY].lv   = 1;
		sd->status.skill[WE_CALLBABY].flag = 1;
	}

	// �{�q �e�����Ȃ��Ɗo���Ȃ�
	if(sd->status.parent_id[0] > 0 || sd->status.parent_id[1] > 0)
	{
		sd->status.skill[WE_BABY].id   = WE_BABY;
		sd->status.skill[WE_BABY].lv   = 1;
		sd->status.skill[WE_BABY].flag = 1;
		sd->status.skill[WE_CALLPARENT].id   = WE_CALLPARENT;
		sd->status.skill[WE_CALLPARENT].lv   = 1;
		sd->status.skill[WE_CALLPARENT].flag = 1;
	}

	// ���ߍ���
	// �A���P�~�X�g�̍�
	if(sd->sc.data[SC_ALCHEMIST].timer != -1)
	{
		if(pc_checkskill(sd,AM_PHARMACY) == 10)
		{
			if(pc_checkskill(sd,AM_TWILIGHT1) == 0)	// �J�[�h�X�L������
			{
				sd->status.skill[AM_TWILIGHT1].id   = AM_TWILIGHT1;
				sd->status.skill[AM_TWILIGHT1].lv   = 1;
				sd->status.skill[AM_TWILIGHT1].flag = 1;
			}
			if(pc_checkskill(sd,AM_TWILIGHT2) == 0)	// �J�[�h�X�L������
			{
				sd->status.skill[AM_TWILIGHT2].id   = AM_TWILIGHT2;
				sd->status.skill[AM_TWILIGHT2].lv   = 1;
				sd->status.skill[AM_TWILIGHT2].flag = 1;
			}
			if(pc_checkskill(sd,AM_TWILIGHT3) == 0)	// �J�[�h�X�L������
			{
				sd->status.skill[AM_TWILIGHT3].id   = AM_TWILIGHT3;
				sd->status.skill[AM_TWILIGHT3].lv   = 1;
				sd->status.skill[AM_TWILIGHT3].flag = 1;
			}
#ifdef CLASS_MB
			if(pc_checkskill(sd,AM_TWILIGHT4) == 0)	// �J�[�h�X�L������
			{
				sd->status.skill[AM_TWILIGHT4].id   = AM_TWILIGHT4;
				sd->status.skill[AM_TWILIGHT4].lv   = 1;
				sd->status.skill[AM_TWILIGHT4].flag = 1;
			}
#endif
		}

		if(pc_checkskill(sd,AM_BERSERKPITCHER) == 0)	// �J�[�h�X�L������
		{
			sd->status.skill[AM_BERSERKPITCHER].id   = AM_BERSERKPITCHER;
			sd->status.skill[AM_BERSERKPITCHER].lv   = 1;
			sd->status.skill[AM_BERSERKPITCHER].flag = 1;
		}
	}
	// �i�C�g�̍�
	if(sd->sc.data[SC_KNIGHT].timer != -1)
	{
		if(pc_checkskill(sd,KN_TWOHANDQUICKEN) == 10)
		{
			if(pc_checkskill(sd,KN_ONEHAND) == 0)	// �J�[�h�X�L������
			{
				sd->status.skill[KN_ONEHAND].id   = KN_ONEHAND;
				sd->status.skill[KN_ONEHAND].lv   = 1;
				sd->status.skill[KN_ONEHAND].flag = 1;
			}
		}
	}
	// �u���b�N�X�~�X�̍�
	if(sd->sc.data[SC_BLACKSMITH].timer != -1)
	{
		if(pc_checkskill(sd,BS_ADRENALINE) == 5)
		{
			if(pc_checkskill(sd,BS_ADRENALINE2) == 0)	// �J�[�h�X�L������
			{
				sd->status.skill[BS_ADRENALINE2].id   = BS_ADRENALINE2;
				sd->status.skill[BS_ADRENALINE2].lv   = 1;
				sd->status.skill[BS_ADRENALINE2].flag = 1;
			}
		}
	}
	// �n���^�[�̍�
	if(sd->sc.data[SC_HUNTER].timer != -1)
	{
		if(pc_checkskill(sd,AC_DOUBLE) == 10)
		{
			if(pc_checkskill(sd,HT_POWER) == 0)	// �J�[�h�X�L������
			{
				sd->status.skill[HT_POWER].id   = HT_POWER;
				sd->status.skill[HT_POWER].lv   = 1;
				sd->status.skill[HT_POWER].flag = 1;
			}
		}

	}

	// �o�[�h�ƃ_���T�[�̍�
	if(sd->sc.data[SC_BARDDANCER].timer != -1)
	{
		int lv;
		if((lv = pc_checkskill(sd,BA_WHISTLE)) > 0) {
			if(pc_checkskill(sd,DC_HUMMING) == 0)	// �J�[�h�X�L������
			{
				sd->status.skill[DC_HUMMING].id   = DC_HUMMING;
				sd->status.skill[DC_HUMMING].lv   = lv;
				sd->status.skill[DC_HUMMING].flag = 1;
			}
		} else if((lv = pc_checkskill(sd,DC_HUMMING)) > 0) {
			if(pc_checkskill(sd,BA_WHISTLE) == 0)	// �J�[�h�X�L������
			{
				sd->status.skill[BA_WHISTLE].id   = BA_WHISTLE;
				sd->status.skill[BA_WHISTLE].lv   = lv;
				sd->status.skill[BA_WHISTLE].flag = 1;
			}
		}

		if((lv = pc_checkskill(sd,BA_ASSASSINCROSS)) > 0) {
			if(pc_checkskill(sd,DC_DONTFORGETME) == 0)	// �J�[�h�X�L������
			{
				sd->status.skill[DC_DONTFORGETME].id   =DC_DONTFORGETME;
				sd->status.skill[DC_DONTFORGETME].lv   = lv;
				sd->status.skill[DC_DONTFORGETME].flag = 1;
			}
		} else if((lv = pc_checkskill(sd,DC_DONTFORGETME)) > 0) {
			if(pc_checkskill(sd,BA_ASSASSINCROSS) == 0)	// �J�[�h�X�L������
			{
				sd->status.skill[BA_ASSASSINCROSS].id   = BA_ASSASSINCROSS;
				sd->status.skill[BA_ASSASSINCROSS].lv   = lv;
				sd->status.skill[BA_ASSASSINCROSS].flag = 1;
			}
		}

		if((lv = pc_checkskill(sd,BA_POEMBRAGI)) > 0) {
			if(pc_checkskill(sd,DC_FORTUNEKISS) == 0)	// �J�[�h�X�L������
			{
				sd->status.skill[DC_FORTUNEKISS].id   = DC_FORTUNEKISS;
				sd->status.skill[DC_FORTUNEKISS].lv   = lv;
				sd->status.skill[DC_FORTUNEKISS].flag = 1;
			}

		} else if((lv = pc_checkskill(sd,DC_FORTUNEKISS)) > 0) {
			if(pc_checkskill(sd,BA_POEMBRAGI) == 0)		// �J�[�h�X�L������
			{
				sd->status.skill[BA_POEMBRAGI].id   = BA_POEMBRAGI;
				sd->status.skill[BA_POEMBRAGI].lv   = lv;
				sd->status.skill[BA_POEMBRAGI].flag = 1;
			}

		}

		if((lv = pc_checkskill(sd,BA_APPLEIDUN)) > 0) {
			if(pc_checkskill(sd,DC_SERVICEFORYOU) == 0)	// �J�[�h�X�L������
			{
				sd->status.skill[DC_SERVICEFORYOU].id   = DC_SERVICEFORYOU;
				sd->status.skill[DC_SERVICEFORYOU].lv   = lv;
				sd->status.skill[DC_SERVICEFORYOU].flag = 1;
			}
		} else if((lv = pc_checkskill(sd,DC_SERVICEFORYOU)) > 0) {
			if(pc_checkskill(sd,BA_APPLEIDUN) == 0)		// �J�[�h�X�L������
			{
				sd->status.skill[BA_APPLEIDUN].id   = BA_APPLEIDUN;
				sd->status.skill[BA_APPLEIDUN].lv   = lv;
				sd->status.skill[BA_APPLEIDUN].flag = 1;
			}
		}
	}

	// �e�R�������J�[�{�[�i�X
	if(sd->status.class_ == PC_CLASS_TK && sd->status.base_level >= 90 && ranking_get_pc_rank(sd,RK_TAEKWON) > 0)
	{
		for(i = 411; i <= 426; i++) {
			pc_skill(sd,i,skill_get_max(i),1);
		}

		// �e�R���~�b�V�������ǉ�����
		pc_skill(sd,TK_MISSION,skill_get_max(TK_MISSION),1);
	}

	return 0;
}

/*==========================================
 * �d�ʂ�50%���z���Ă��邩
 *------------------------------------------
 */
int pc_is50overweight(struct map_session_data *sd)
{
	int rate = 50;

	nullpo_retr(0, sd);

	// ���R�񕜂��Ȃ��Ȃ�d�ʐݒ�ɍ��킹��
	if(rate != battle_config.natural_heal_weight_rate)
		rate = battle_config.natural_heal_weight_rate;

	return (sd->weight * 100 / sd->max_weight >= rate);
}

/*==========================================
 * �d�ʂ�90%���z���Ă��邩
 *------------------------------------------
 */
int pc_is90overweight(struct map_session_data *sd)
{
	int rate = 90;

	nullpo_retr(0, sd);

	// ���R�񕜂��Ȃ��Ȃ�d�ʐݒ肪90%�ȏ�Ȃ炻��ɍ��킹��
	if(rate < battle_config.natural_heal_weight_rate)
		rate = battle_config.natural_heal_weight_rate;

	return (sd->weight * 100 / sd->max_weight >= rate);
}

/*==========================================
 * �d�ʃA�C�R���̊m�F
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

	// �ω����Ȃ��̂ŏI��
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
 * �X�N���v�g�ɂ��X�L���擾
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
	if(!flag && (sd->status.skill[id].id == id || level == 0)) {	// �N�G�X�g�擾�Ȃ炱���ŏ������m�F���đ��M����
		sd->status.skill[id].lv = level;
		status_calc_pc(sd,0);
		clif_skillinfoblock(sd);
	}
	else if(sd->status.skill[id].lv < level) {	// �o�����邪lv���������Ȃ�
		if(sd->status.skill[id].id == id) {
			sd->status.skill[id].flag = sd->status.skill[id].lv+2;	// lv���L��
		} else {
			sd->status.skill[id].id   = id;
			sd->status.skill[id].flag = 1;	// card�X�L���Ƃ���
		}
		sd->status.skill[id].lv = level;
	}

	return 0;
}

/*==========================================
 * �J�[�h�}��
 *------------------------------------------
 */
void pc_insert_card(struct map_session_data *sd, int idx_card, int idx_equip)
{
	nullpo_retv(sd);

	// idx_card�͊��Ƀ`�F�b�N�ς�
	if(idx_equip >= 0 && idx_equip < MAX_INVENTORY && sd->inventory_data[idx_card]) {
		int i;
		int nameid = sd->status.inventory[idx_equip].nameid;
		int cardid = sd->status.inventory[idx_card].nameid;
		int ep     = sd->inventory_data[idx_card]->equip;

		if( nameid <= 0 ||
		    cardid <= 0 ||
		    sd->inventory_data[idx_equip] == NULL ||
		    (!itemdb_isarmor(sd->inventory_data[idx_equip]->nameid) && !itemdb_isweapon(sd->inventory_data[idx_equip]->nameid)) ||	// ��������Ȃ�
		    sd->status.inventory[idx_equip].identify == 0 ||						// ���Ӓ�
		    itemdb_isspecial(sd->status.inventory[idx_equip].card[0]) ||				// ��������E���O����E�y�b�g
		    (sd->inventory_data[idx_equip]->equip & ep) == 0 ||						// �������Ⴂ
		    (itemdb_isweapon(sd->inventory_data[idx_equip]->nameid) && ep == LOC_LARM) ||					// ���蕐��Ə��J�[�h
		    (sd->inventory_data[idx_card]->type != ITEMTYPE_CARD) ||						// Prevent Hack [Ancyker]
		    sd->status.inventory[idx_equip].equip ||
		    itemdb_cardtype(sd->inventory_data[idx_card]->nameid) == 2 )	// hidden
		{
			clif_insert_card(sd, idx_equip, idx_card, 1);	// flag: 1=fail, 0:success
			return;
		}
		for(i=0; i<sd->inventory_data[idx_equip]->slot; i++) {
			if(sd->status.inventory[idx_equip].card[i] == 0) {
				// �����̓���J�[�h��������Ă��邩�`�F�b�N
				if(!itemdb_cardtype(sd->inventory_data[idx_card]->nameid)) {
					int j;
					for(j=0; j<i; j++) {
						if(sd->status.inventory[idx_equip].card[j] == cardid) {
							clif_insert_card(sd, idx_equip, idx_card, 1);	// flag: 1=fail, 0:success
							return;
						}
					}
				}
				// �󂫃X���b�g���������̂ō�������
				sd->status.inventory[idx_equip].card[i] = cardid;

				// �J�[�h�͌��炷
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
 * �X�L���ɂ�锃���l�C��
 * sd��NULL�̂Ƃ��͍ň��l��Ԃ�
 *------------------------------------------
 */
int pc_modifybuyvalue(struct map_session_data *sd,int orig_value)
{
	int skill, val = orig_value;
	int rate1 = 0, rate2 = 0;

	// �f�B�X�J�E���g
	skill = (sd)? pc_checkskill(sd, MC_DISCOUNT): skill_get_max(MC_DISCOUNT);
	if(skill > 0)
		rate1 = 5 + skill * 2 - ((skill >= 10)? 1: 0);

	// �R���p���V�����f�B�X�J�E���g
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
 * �X�L���ɂ�锄��l�C��
 * sd��NULL�̂Ƃ��͍ō��l��Ԃ�
 *------------------------------------------
 */
int pc_modifysellvalue(struct map_session_data *sd,int orig_value)
{
	int skill, val = orig_value;
	int rate = 0;

	// �I�[�o�[�`���[�W
	skill = (sd)? pc_checkskill(sd, MC_OVERCHARGE): skill_get_max(MC_OVERCHARGE);
	if(skill > 0)
		rate = 5 + skill * 2 - ((skill >= 10)? 1: 0);

	// �}�[�_���[�{�[�i�X
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
 * �A�C�e���𔃂������ɁA�V�����A�C�e�������g�����A
 * 3�������ɂ����邩�m�F
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
 * �󂫃A�C�e�����̌�
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
 * �����𕥂�
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
 * �����𓾂�
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
 * �A�C�e����T���āA�C���f�b�N�X��Ԃ�
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
 * �A�C�e���g�p�����^�C�}�[
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
 * �A�C�e���g�p�����̃`�F�b�N
 *------------------------------------------
 */
static int pc_checkitemlimit(struct map_session_data *sd, int idx, unsigned int tick, unsigned int now, int first)
{
	nullpo_retr(0, sd);

	if(idx < 0 || idx >= MAX_INVENTORY)
		return -1;

	if(sd->status.inventory[idx].limit > now) {
		// �܂����ԂɂȂ��ĂȂ��̂Ń^�C�}�[���p������
		unsigned int diff = sd->status.inventory[idx].limit - now;
		if(diff > 3600)
			diff = 3600;
		return add_timer(tick + diff * 1000, pc_itemlimit_timer, sd->bl.id, NULL);
	}

	// ���Ԑ؂�ɂ��폜
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
			// ���������A�C�e���̍폜
			pc_delitem(sd, idx, sd->status.inventory[idx].amount, 1, 0);
			clif_delitem_timeout(sd, idx, ((data->view_id > 0)? data->view_id: data->nameid));
			return -1;
		}
#endif
		// �ʏ�A�C�e���̎g�p�����؂�폜
		pc_delitem(sd, idx, sd->status.inventory[idx].amount, 0, 0);
		snprintf(output, sizeof(output), msg_txt(187), ((data->view_id > 0)? itemdb_jname(data->view_id): data->jname));
		clif_disp_onlyself(sd->fd, output);

		// ����p�̎�j���폜�����ꍇ��SC_ALL_RIDING����������
		if(data->nameid == 12622)
			status_change_end(&sd->bl,SC_ALL_RIDING,-1);

		// �t�H���g�A�C�e���̍폜���̓t�H���g������������
		if((data->nameid >= 12287 && data->nameid <= 12289) ||
		   (data->nameid >= 12304 && data->nameid <= 12309))
			sd->status.font = 0;
	}

	return -1;
}

/*==========================================
 * �A�C�e���g�p�����̃Z�b�g
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
 * �A�C�e���g�p�����̑S����
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
 * �A�C�e���ǉ��B���̂�item�\���̂̐����𖳎�
 *------------------------------------------
 */
int pc_additem(struct map_session_data *sd,struct item *item_data,int amount,bool flag)
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
		// �����i�ł͂Ȃ��̂ŁA�����L�i�Ȃ���̂ݕω�������
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
				if(flag)
					clif_item_preview(sd, (short)i);
				return 0;
			}
		}
	}

	// �����i�������L�i�������̂ŋ󂫗��֒ǉ�
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
	if(flag)
		clif_item_preview(sd, (short)i);

	if(sd->status.inventory[i].limit > 0) {
		int tid = pc_checkitemlimit(sd, i, gettick(), (unsigned int)time(NULL), 0);
		if(tid >= 0)
			linkdb_insert(&sd->inventory_timer, INT2PTR(i), INT2PTR(tid));
	}

	return 0;
}

/*==========================================
 * �����A�C�e��������
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
 * �A�C�e�������炷
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
 * �A�C�e���𗎂�
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
 * �A�C�e�����E�������{��
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
				;	// PT���L�ݒ�œ���PT�Ȃ�OK
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
					;	// PT���L�ݒ�œ���PT�Ȃ�OK
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
						;	// PT���L�ݒ�œ���PT�Ȃ�OK
					} else {
						clif_additem(sd,0,0,6);
						return;
					}
				}
			}
		}
	}
	if((flag = party_loot_share(p,sd,&fitem->item_data,fitem->first_get_id))) {
		// �d��over�Ŏ擾���s
		clif_additem(sd,0,0,flag);
	} else {
		// �擾����
		unit_stopattack(&sd->bl);
		clif_takeitem(&sd->bl,fitem->bl.id);
		map_clearflooritem(fitem->bl.id);
	}
	return;
}

/*==========================================
 * �A�C�e�����E��
 *------------------------------------------
 */
void pc_takeitem(struct map_session_data *sd, struct flooritem_data *fitem)
{
	struct party *p = NULL;

	nullpo_retv(sd);
	nullpo_retv(fitem);

	if(path_distance(fitem->bl.x,fitem->bl.y,sd->bl.x,sd->bl.y) > 2)
		return;	// ����������

	if(sd->status.party_id > 0)
		p = party_search(sd->status.party_id);

	pc_takeitem_sub(p, sd, fitem);
	return;
}

/*==========================================
 * �A�C�e���g�p�\���ǂ���
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
 * �A�C�e�����g��
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
			clif_msgstringtable(sd, 0x6ee);	// �A�C�e�����g�p�ł��郌�x���ɒB���Ă��܂���B
		return;
	}

	if(item->cooldown > 0) {
		unsigned int tick = gettick();
		int i,j = -1;
		for(i=0;i<MAX_ITEMCOOLDOWN;i++) {
			// ����ID��idx�����g�pidx��T��
			if(sd->itemcooldown[i].nameid == nameid || sd->itemcooldown[i].nameid == 0)
				break;
			// �g�p�ς݂̂����N�[���^�C���؂ꂪ����΍T����
			if(DIFF_TICK(sd->itemcooldown[i].time, tick) <= 0) {
				j = i;
			}
		}
		// �A�C�e���N�[���^�C�����X�g�������ς�
		if(i == MAX_ITEMCOOLDOWN) {
			// ���N�[���^�C���؂ꂪ�Ȃ�
			if(j < 0) {
				clif_useitemack(sd,n,0,0);
				return;
			}
			// �N�[���^�C���؂�idx�ɍ����ւ���
			i = j;
		}
		// ����ID�Ȃ�N�[���^�C���`�F�b�N
		if(sd->itemcooldown[i].nameid == nameid) {
			int delay = DIFF_TICK(sd->itemcooldown[i].time, tick) / 1000;
			if(delay > 0) {
				clif_useitemack(sd,n,0,0);
				clif_msgstringtable3(sd, 0x746, delay + 1);	// %d �b��Ɏg�p�ł��܂��B
				return;
			}
		}
		else {	// ���g�pidx���N�[���^�C��idx�Ȃ�nameid�����ւ���
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
		// nonconsume�t���O���^�Ȃ�A�C�e��������Ȃ�
		if(itemdb_isnonconsume(nameid))
		{
			clif_useitemack(sd,n,amount,1);
		}
		// �y������ԂȂ�m���I�ɃA�[�X�X�p�C�N�X�N���[���̏����
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

	// ���юg�p�^�[�Q�b�g
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
 * �J�[�g�A�C�e���ǉ��B���̂�item�\���̂̐����𖳎�
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
		// �����i�ł͂Ȃ��̂ŁA�����L�i�Ȃ���̂ݕω�������
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
		// �����i�������L�i�������̂ŋ󂫗��֒ǉ�
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
 * �J�[�g�A�C�e�������炷
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
 * �J�[�g�փA�C�e���ړ�
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
 * �J�[�g���̃A�C�e�����m�F(���̍�����Ԃ�)
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
 * �J�[�g����A�C�e���ړ�
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

	if((flag = pc_additem(sd, item_data, amount, false)) == 0) {
		pc_cart_delitem(sd, idx, amount, 0);
		return;
	}
	clif_cart_delitem(sd,idx,amount);
	clif_additem(sd,0,0,flag);
	clif_cart_additem(sd,idx,amount);

	return;
}

/*==========================================
 * �A�C�e���Ӓ�
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
 * �X�e�B���i���J
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
			msg_output(fd, msg_txt(136), sd->status.name);	// %s��Unknown_Item���X�e�B�[�����܂���
		else
			msg_output(fd, msg_txt(137), sd->status.name, item->jname);	// %s��%s���X�e�B�[�����܂���
	} else {
		msg_output(fd, msg_txt(138), sd->status.name);	// %s�͏d�ʃI�[�o�[�ɂ��A�C�e�����擾�ł��܂���ł���
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
					flag = pc_additem(sd,&tmp_item,1, false);
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
 * PC�̈ʒu�ݒ�
 *------------------------------------------
 */
int pc_setpos(struct map_session_data *sd,const char *mapname,int x,int y,int clrtype)
{
	int m, i, move_flag = 0;

	nullpo_retr(1, sd);

	// �����Ă����痧���オ��
	if(pc_issit(sd)) {
		pc_setstand(sd);
		skill_sit(sd,0);
	}

	// ����ł����痧���オ��
	if(unit_isdead(&sd->bl)) {
		pc_setstand(sd);
		pc_setrestartvalue(sd,3);
	}

	m = map_mapname2mapid(mapname);
	if(m < 0) {
		unsigned long ip;
		unsigned short port;
		if(map_mapname2ipport(mapname,&ip,&port) == 0) {
			// �Ⴄ�}�b�v�T�[�o�[�Ɋ��蓖�Ă��Ă���}�b�v�Ɉړ�
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

	// �X�^�b�N����
	if(x < 0 || x >= map[m].xs || y < 0 || y >= map[m].ys)
		x = y = 0;
	if((x == 0 && y == 0) || map_getcell(m,x,y,CELL_CHKNOPASS)) {
		i = 0;
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
		// �����}�b�v�Ȃ̂Ń_���X���j�b�g�����p��
		sd->ud.to_x = x;
		sd->ud.to_y = y;
		skill_stop_dancing(&sd->bl, 2);	// �ړ���Ƀ��j�b�g���ړ����邩�ǂ����̔��f������
	} else {
		// �Ⴄ�}�b�v�Ȃ̂Ń_���X���j�b�g�폜
		skill_stop_dancing(&sd->bl, 1);

		// ���z�E���E���̈��y���ʍ폜
		if(sd->sc.data[SC_SUN_COMFORT].timer != -1)
			status_change_end(&sd->bl, SC_SUN_COMFORT, -1);
		if(sd->sc.data[SC_MOON_COMFORT].timer != -1)
			status_change_end(&sd->bl, SC_MOON_COMFORT, -1);
		if(sd->sc.data[SC_STAR_COMFORT].timer != -1)
			status_change_end(&sd->bl, SC_STAR_COMFORT, -1);
		// �ʖʋ��̌��ʍ폜
		if(sd->sc.data[SC_BOSSMAPINFO].timer != -1)
			status_change_end(&sd->bl, SC_BOSSMAPINFO, -1);
		// �������A���_���W�����̃��[�U�[���`�F�b�N
		if(map[m].memorial_id != map[sd->bl.m].memorial_id) {
			// �������A���_���W�����̃��[�U�[���ǉ�
			if(map[m].memorial_id)
				memorial_addusers(map[m].memorial_id);
			// �������A���_���W�����̃��[�U�[���폜
			if(map[sd->bl.m].memorial_id)
				memorial_delusers(map[sd->bl.m].memorial_id);
		}
	}
	status_change_hidden_end(&sd->bl);

	// �����胆�j�b�g�폜
	if(sd->sc.data[SC_WARM].timer != -1)
		status_change_end(&sd->bl, SC_WARM, -1);
	// �j���[�g�����o���A�[�폜
	if(sd->sc.data[SC_NEUTRALBARRIER_MASTER].timer != -1)
		status_change_end(&sd->bl, SC_NEUTRALBARRIER_MASTER, -1);
	// �X�e���X�t�B�[���h�폜
	if(sd->sc.data[SC_STEALTHFIELD_MASTER].timer != -1)
		status_change_end(&sd->bl, SC_STEALTHFIELD_MASTER, -1);
	// �o���f�B���O�폜
	if(sd->sc.data[SC_BANDING].timer != -1)
		status_change_end(&sd->bl, SC_BANDING, -1);
	// �f�B�{�[�V�����폜(���g�Ώێ�)
	if(sd->sc.data[SC_DEVOTION].timer != -1)
		status_change_end(&sd->bl, SC_DEVOTION, -1);
	// �f�B�{�[�V�����폜(���g��)
	for(i=0; i<5; i++) {
		if(sd->dev.val1[i]) {
			status_change_end(map_id2bl(sd->dev.val1[i]),SC_DEVOTION,-1);
			sd->dev.val1[i] = sd->dev.val2[i] = 0;
		}
	}

	if(sd->bl.prev != NULL) {
		if(m != sd->bl.m) {
			move_flag = 1;	// �V�K���O�C���łȂ��ĈႤMAP�ֈړ��Ȃ�flag�I��
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

	// OnPCMapOut�C�x���g
	if(move_flag && battle_config.pc_mapout_script)
		npc_event_doall_id("OnPCMapOut",sd->bl.id,sd->bl.m);

	strncpy(sd->mapname,mapname,24);
	sd->bl.m = m;
	sd->bl.x = x;
	sd->bl.y = y;

	if(map[sd->bl.m].flag.gvg) {
		// �U��펞�Ƀ����X�^�[�ϐg�����������邩
		if(battle_config.disable_transform_when_gvg) {
			if(sd->sc.data[SC_MONSTER_TRANSFORM].timer != -1)
				status_change_end(&sd->bl, SC_MONSTER_TRANSFORM, -1);
		}
		// �U��펞�ɃR�X�`���[���A�C�e�������������邩
		if(battle_config.disable_costume_when_gvg) {
			for(i = EQUIP_INDEX_COSTUME_HEAD; i < EQUIP_INDEX_MAX; i++) {
				if(sd->equip_index[i] >= 0 && pc_isequip(sd,sd->equip_index[i]) <= 0)
					pc_unequipitem(sd,sd->equip_index[i],1);	// �����O��
			}
		}
		if(sd->sc.data[SC_SUPPORT_HPSP].timer != -1)			// �T�|�[�g���@(HPSP����)
			status_change_end(&sd->bl, SC_SUPPORT_HPSP, -1);
		if(sd->sc.data[SC_SUPPORT_SPEED].timer != -1)			// �T�|�[�g���@(�ړ����x����)
			status_change_end(&sd->bl, SC_SUPPORT_SPEED, -1);
	}

	// �y�b�g�̈ړ�
	if(sd->status.pet_id > 0 && sd->pd && sd->pet.intimate > 0) {
		sd->pd->bl.m = m;
		sd->pd->bl.x = sd->pd->ud.to_x = x;
		sd->pd->bl.y = sd->pd->ud.to_y = y;
		sd->pd->dir  = sd->dir;
	}
	// �z���̈ړ�
	if(sd->status.homun_id > 0 && sd->hd) {
		sd->hd->bl.m = m;
		sd->hd->bl.x = sd->hd->ud.to_x = x;
		sd->hd->bl.y = sd->hd->ud.to_y = y;
		sd->hd->dir  = sd->dir;
	}
	// �b���̈ړ�
	if(sd->status.merc_id > 0 && sd->mcd) {
		sd->mcd->bl.m = m;
		sd->mcd->bl.x = sd->mcd->ud.to_x = x;
		sd->mcd->bl.y = sd->mcd->ud.to_y = y;
		sd->mcd->dir  = sd->dir;
	}
	// ����̈ړ�
	if(sd->status.elem_id > 0 && sd->eld) {
		sd->eld->bl.m = m;
		sd->eld->bl.x = sd->eld->ud.to_x = x;
		sd->eld->bl.y = sd->eld->ud.to_y = y;
		sd->eld->dir  = sd->dir;
	}

	// OnPCMoveMap�C�x���g
	if(move_flag && battle_config.pc_movemap_script)
		npc_event_doall_id("OnPCMoveMap",sd->bl.id,sd->bl.m);

	// �u���b�N�o�^��spawn�� clif_parse_LoadEndAck �ōs��

	return 0;
}

/*==========================================
 * �M���h�X�L���̗L���`�F�b�N
 * �ω�������΃X�e�[�^�X�̍Čv�Z
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

	if(battle_config.guild_skill_effective_range > 0) {	// �X�L���𓯈ꋗ�����肷��
		range = battle_config.guild_skill_effective_range;
		if(dx <= range && dy <= range) {	// �͈͓�
			if(member->under_the_influence_of_the_guild_skill == 0)	// ���ʊO������
				return 1;
		} else {				// �͈͊O
			if(member->under_the_influence_of_the_guild_skill > 0)	// ���ʓ�������
				return 1;
		}
	} else {						// �X�L�����ʂɋ������肷��
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

		if(min_range == 0x7fffffff) {	// ���ʔ͈͊O
			if(member->under_the_influence_of_the_guild_skill > 0)	// �O�͌��ʔ͈͓�������
				return 1;
		} else {			// ���ʔ͈͓�
			if(member->under_the_influence_of_the_guild_skill == 0)	// �O�͔͈͊O������
				return 1;
			if((min_range+1) != member->under_the_influence_of_the_guild_skill)
				// �O�͔͈͓��ō��񋗗����ς����->������ʕϓ�
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

	// �M���h�ɓ����Ă��Ȃ�
	if(sd->status.guild_id == 0)
		return 0;
	// �M���h�X�L��������
	if(!battle_config.guild_hunting_skill_available)
		return 0;

	// �M���h�擾�ł��Ȃ�����
	if((g = guild_search(sd->status.guild_id)) == NULL)
		return 0;

	// �}�X�^�[�ڑ����Ă��Ȃ�
	if((gmsd = g->member[0].sd) == NULL) {
		// ���ʔ͈͓�������
		if(sd->under_the_influence_of_the_guild_skill > 0)
			status_calc_pc(sd,0);
		return 0;
	}

	// �X�L���P�ȏ�
	if( pc_checkskill(gmsd,GD_LEADERSHIP) > 0 ||
	    pc_checkskill(gmsd,GD_SOULCOLD) > 0 ||
	    pc_checkskill(gmsd,GD_GLORYWOUNDS) > 0 ||
	    pc_checkskill(gmsd,GD_HAWKEYES) > 0 )
	{
		if(sd == gmsd) {	// �������M���}�X
			int i;
			if(battle_config.allow_me_guild_skill && sd->under_the_influence_of_the_guild_skill == 0)
				status_calc_pc(sd,0);

			// �X�L����������
			for(i = 1; i < g->max_member; i++) {
				struct map_session_data *member = g->member[i].sd;
				if(member == NULL)	// �����o�[�ڑ��Ȃ�
					continue;

				if(member->bl.m != gmsd->bl.m) {	// �}�b�v���Ⴄ
					if(member->under_the_influence_of_the_guild_skill > 0)	// �O��͌��ʔ͈͓�������
						status_calc_pc(member,0);
				} else if(pc_check_guild_skill_effective_range_sub(g, gmsd, member)) {
					status_calc_pc(member,0);
				}
			}
		} else {	// �M������
			if(sd->bl.m != gmsd->bl.m) {	// �}�b�v���Ⴄ
				if(sd->under_the_influence_of_the_guild_skill > 0)	// �O��͌��ʔ͈͓�������
					status_calc_pc(sd,0);
			} else if(pc_check_guild_skill_effective_range_sub(g, gmsd, sd)) {
				status_calc_pc(sd,0);
			}
		}
	}
	return 1;
}

/*==========================================
 * PC�̃����_�����[�v
 *------------------------------------------
 */
int pc_randomwarp(struct map_session_data *sd,int type)
{
	int m, x, y;
	int i = 0;

	nullpo_retr(0, sd);

	m = sd->bl.m;

	if(map[m].flag.noteleport)	// �e���|�[�g�֎~
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
 * ���݈ʒu�̃���
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
 * �삯���v��
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

		// ���̃Z���ւP���ňړ��\�łȂ��A��������PC,MOB,NPC��������
		if(map_getcell(sd->bl.m,to_x+dir_x,to_y+dir_y,CELL_CHKNOPASS) ||
		   map_getcell(sd->bl.m,to_x      ,to_y+dir_y,CELL_CHKNOPASS) ||
		   map_getcell(sd->bl.m,to_x+dir_x,to_y      ,CELL_CHKNOPASS) ||
		   map_count_oncell(sd->bl.m,to_x+dir_x,to_y+dir_y,BL_PC|BL_MOB|BL_NPC) > 0)
			break;

		to_x += dir_x;
		to_y += dir_y;
	}

	// �i�߂Ȃ��ꍇ�삯���I��
	if(to_x == sd->bl.x && to_y == sd->bl.y) {
		if(sd->sc.data[SC_RUN].timer != -1) {
			int dir = sd->dir;
			int head_dir = sd->head_dir;

			// ����Ăяo�����ň���������Ȃ��Ƃ��̓m�b�N�o�b�N���Ȃ�
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
		}
	} else {
		unit_walktoxy( &sd->bl, to_x, to_y);
	}

	return 1;
}

/*==========================================
 * �X�L���̌��� ���L���Ă����ꍇLv���Ԃ�
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
 * �X�L���̌��� ���L���Ă����ꍇLv���Ԃ�
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
 * �X�L���̌��� ���L���Ă����ꍇLv���Ԃ�
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
 * ����ύX�ɂ��X�L���̌p���`�F�b�N
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
		DK_CHARGINGPIERCE,
		SHC_DANCING_KNIFE,
	};

	nullpo_retr(0, sd);

	if( sd->sc.count <= 0 )
		return 0;

	weapon = sd->status.weapon;
	if(sd->status.weapon >= WT_MAX)
		weapon -= WT_DOUBLE_DD + WT_MAX;

	mask = 1 << weapon;

	// ���킪����Ȃ��Ȃ�X�e�[�^�X�ُ������
	for(i=0; i < sizeof(skill_list)/sizeof(skill_list[0]); i++) {
		int type = GetSkillStatusChangeTable(skill_list[i]);
		if( type >= 0 && sd->sc.data[type].timer != -1 ) {
			if( !(skill_get_weapontype(skill_list[i]) & mask) )
				status_change_end(&sd->bl, type, -1);
		}
	}

	if( sd->sc.data[SC_DANCING].timer != -1 ) {
		if( !(skill_get_weapontype(sd->sc.data[SC_DANCING].val1) & mask) )
			skill_stop_dancing(&sd->bl,0);	// ���t����
	}
	if( sd->sc.data[SC_SPURT].timer != -1 && (sd->weapontype1 != WT_FIST || sd->weapontype2 != WT_FIST) ) {
		status_change_end(&sd->bl,SC_SPURT,-1);	// �삯��STR
	}
#ifndef PRE_RENEWAL
	if( sd->sc.data[SC_AURABLADE].timer != -1) {	// �I�[���u���[�h
		status_change_end(&sd->bl,SC_AURABLADE,-1);
	}
	if( sd->sc.data[SC_CONCENTRATION].timer != -1) {	// �R���Z���g���[�V����
		status_change_end(&sd->bl,SC_CONCENTRATION,-1);
	}
	if( sd->sc.data[SC_TENSIONRELAX].timer != -1) {	// �e���V���������b�N�X
		status_change_end(&sd->bl,SC_TENSIONRELAX,-1);
	}
	if( sd->sc.data[SC_OVERTHRUSTMAX].timer != -1) {	// �I�[�o�[�g���X�g�}�b�N�X
		status_change_end(&sd->bl,SC_OVERTHRUSTMAX,-1);
	}
#endif
	if( sd->sc.data[SC_CRUSHSTRIKE].timer != -1) {	// �N���b�V���X�g���C�N
		status_change_end(&sd->bl,SC_CRUSHSTRIKE,-1);
	}
	if( sd->sc.data[SC_POISONINGWEAPON].timer != -1) {	// �|�C�Y�j���O�E�F�|��
		status_change_end(&sd->bl,SC_POISONINGWEAPON,-1);
	}
	if( sd->sc.data[SC_FEARBREEZE].timer != -1) {	// �t�B�A�[�u���[�Y
		status_change_end(&sd->bl,SC_FEARBREEZE,-1);
	}
	if( sd->sc.data[SC_HEAT_BARREL].timer != -1) {	// �q�[�g�o����
		status_change_end(&sd->bl,SC_HEAT_BARREL,-1);
	}
	if( sd->sc.data[SC_P_ALTER].timer != -1) {	// �v���`�i���A���^�[
		status_change_end(&sd->bl,SC_P_ALTER,-1);
	}
	if( sd->sc.data[SC_SHADOW_WEAPON].timer != -1) {	// �G���`�����e�B���O�V���h�E
		status_change_end(&sd->bl,SC_SHADOW_WEAPON,-1);
	}

	if(sd->status.shield <= 0) {
		if(sd->sc.data[SC_AUTOGUARD].timer != -1) {		// �I�[�g�K�[�h
			status_change_end(&sd->bl,SC_AUTOGUARD,-1);
		}
		if(sd->sc.data[SC_DEFENDER].timer != -1) {		// �f�B�t�F���_�[
			status_change_end(&sd->bl,SC_DEFENDER,-1);
		}
		if(sd->sc.data[SC_REFLECTSHIELD].timer != -1) {		// ���t���N�g�V�[���h
			status_change_end(&sd->bl,SC_REFLECTSHIELD,-1);
		}
		if(sd->sc.data[SC_REFLECTDAMAGE].timer != -1) {		// ���t���N�g�_���[�W
			status_change_end(&sd->bl,SC_REFLECTDAMAGE,-1);
		}
		if(sd->sc.data[SC_SHIELDSPELL_DEF].timer != -1) {		// �V�[���h�X�y��(DEF)
			status_change_end(&sd->bl,SC_SHIELDSPELL_DEF,-1);
		}
		if(sd->sc.data[SC_SHIELDSPELL_MDEF].timer != -1) {		// �V�[���h�X�y��(MDEF)
			status_change_end(&sd->bl,SC_SHIELDSPELL_MDEF,-1);
		}
		if(sd->sc.data[SC_SHIELDSPELL_REF].timer != -1) {		// �V�[���h�X�y��(���B)
			status_change_end(&sd->bl,SC_SHIELDSPELL_REF,-1);
		}
		if(sd->sc.data[SC_GUARD_STANCE].timer != -1) {		// �K�[�h�X�^���X
			status_change_end(&sd->bl,SC_GUARD_STANCE,-1);
		}
		if(sd->sc.data[SC_HOLY_S].timer != -1) {		// �z�[���[�V�[���h
			status_change_end(&sd->bl,SC_HOLY_S,-1);
		}
	}
	return 0;
}

/*==========================================
 * �����i�̃`�F�b�N
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
 * �]���E��{�q�E�̌��̐E�Ƃ�Ԃ�
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
		case PC_CLASS_DE:
			bj.job   = PC_JOB_DE;
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
		case PC_CLASS_SJ:
		case PC_CLASS_SJ_B:
		case PC_CLASS_SJ2:
		case PC_CLASS_SJ2_B:
		case PC_CLASS_SJ3:
		case PC_CLASS_SJ3_B:
			bj.job   = PC_JOB_SJ;
			bj.upper = PC_UPPER_NORMAL;
			break;
		case PC_CLASS_SP:
		case PC_CLASS_SP_B:
		case PC_CLASS_SP2:
		case PC_CLASS_SP2_B:
			bj.job   = PC_JOB_SP;
			bj.upper = PC_UPPER_NORMAL;
			break;
		case PC_CLASS_DK:
		case PC_CLASS_DK2:
		case PC_CLASS_DK3:
			bj.job   = PC_JOB_DK;
			bj.upper = PC_UPPER_HIGH;
			break;
		case PC_CLASS_MT:
		case PC_CLASS_MT2:
		case PC_CLASS_MT3:
			bj.job   = PC_JOB_MT;
			bj.upper = PC_UPPER_HIGH;
			break;
		case PC_CLASS_SHC:
		case PC_CLASS_SHC2:
			bj.job   = PC_JOB_SHC;
			bj.upper = PC_UPPER_HIGH;
			break;
		case PC_CLASS_AG:
		case PC_CLASS_AG2:
			bj.job   = PC_JOB_AG;
			bj.upper = PC_UPPER_HIGH;
			break;
		case PC_CLASS_CD:
		case PC_CLASS_CD2:
			bj.job   = PC_JOB_CD;
			bj.upper = PC_UPPER_HIGH;
			break;
		case PC_CLASS_WH:
		case PC_CLASS_WH2:
		case PC_CLASS_WH3:
			bj.job   = PC_JOB_WH;
			bj.upper = PC_UPPER_HIGH;
			break;
		case PC_CLASS_IG:
		case PC_CLASS_IG2:
		case PC_CLASS_IG3:
			bj.job   = PC_JOB_IG;
			bj.upper = PC_UPPER_HIGH;
			break;
		case PC_CLASS_BO:
		case PC_CLASS_BO2:
			bj.job   = PC_JOB_BO;
			bj.upper = PC_UPPER_HIGH;
			break;
		case PC_CLASS_ABC:
		case PC_CLASS_ABC2:
			bj.job   = PC_JOB_ABC;
			bj.upper = PC_UPPER_HIGH;
			break;
		case PC_CLASS_EM:
		case PC_CLASS_EM2:
			bj.job   = PC_JOB_EM;
			bj.upper = PC_UPPER_HIGH;
			break;
		case PC_CLASS_IQ:
		case PC_CLASS_IQ2:
			bj.job   = PC_JOB_IQ;
			bj.upper = PC_UPPER_HIGH;
			break;
		case PC_CLASS_TRB:
		case PC_CLASS_TRB2:
			bj.job   = PC_JOB_TRB;
			bj.upper = PC_UPPER_HIGH;
			break;
		case PC_CLASS_TRV:
		case PC_CLASS_TRV2:
			bj.job   = PC_JOB_TRV;
			bj.upper = PC_UPPER_HIGH;
			break;
		case PC_CLASS_SKE:
		case PC_CLASS_SKE2:
		case PC_CLASS_SKE3:
			bj.job   = PC_JOB_SKE;
			bj.upper = PC_UPPER_NORMAL;
			break;
		case PC_CLASS_SOA:
		case PC_CLASS_SOA2:
			bj.job   = PC_JOB_SOA;
			bj.upper = PC_UPPER_NORMAL;
			break;
		case PC_CLASS_SK:
		case PC_CLASS_SK2:
			bj.job   = PC_JOB_SK;
			bj.upper = PC_UPPER_NORMAL;
			break;
		case PC_CLASS_SN:
		case PC_CLASS_SN2:
			bj.job   = PC_JOB_SN;
			bj.upper = PC_UPPER_NORMAL;
			break;
		case PC_CLASS_NW:
		case PC_CLASS_NW2:
			bj.job   = PC_JOB_NW;
			bj.upper = PC_UPPER_NORMAL;
			break;
		case PC_CLASS_HN:
		case PC_CLASS_HN2:
			bj.job   = PC_JOB_HN;
			bj.upper = PC_UPPER_NORMAL;
			break;
		case PC_CLASS_SH:
		case PC_CLASS_SH2:
			bj.job   = PC_JOB_SH;
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
 * ���̐E�Ƃ���N���XID��Ԃ�
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
		case PC_JOB_DE:
			class_ = PC_CLASS_DE;
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
		case PC_JOB_SJ:
			class_ = PC_CLASS_SJ;
			break;
		case PC_JOB_SP:
			class_ = PC_CLASS_SP;
			break;
		case PC_JOB_DK:
		case PC_JOB_MT:
		case PC_JOB_SHC:
		case PC_JOB_AG:
		case PC_JOB_CD:
		case PC_JOB_WH:
		case PC_JOB_IG:
		case PC_JOB_BO:
		case PC_JOB_ABC:
		case PC_JOB_EM:
		case PC_JOB_IQ:
		case PC_JOB_TRB:
		case PC_JOB_TRV:
			class_ = job - PC_JOB_DK + PC_CLASS_DK;
			break;
		case PC_JOB_SKE:
		case PC_JOB_SOA:
		case PC_JOB_SK:
		case PC_JOB_SN:
		case PC_JOB_NW:
		case PC_JOB_HN:
		case PC_JOB_SH:
			class_ = job - PC_JOB_SKE + PC_CLASS_SKE;
			break;
	}

	return class_;
}

/*==========================================
 * �N���XID���猳�̐E�Ƃ�Ԃ�
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
		case PC_CLASS_DE:
			job = PC_JOB_DE;
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
		case PC_CLASS_SJ:
		case PC_CLASS_SJ_B:
		case PC_CLASS_SJ2:
		case PC_CLASS_SJ2_B:
		case PC_CLASS_SJ3:
		case PC_CLASS_SJ3_B:
			job = PC_JOB_SJ;
			break;
		case PC_CLASS_SP:
		case PC_CLASS_SP_B:
		case PC_CLASS_SP2:
		case PC_CLASS_SP2_B:
			job = PC_JOB_SP;
			break;
		case PC_CLASS_DK:
		case PC_CLASS_DK2:
		case PC_CLASS_DK3:
			job = PC_JOB_DK;
			break;
		case PC_CLASS_MT:
		case PC_CLASS_MT2:
		case PC_CLASS_MT3:
			job = PC_JOB_MT;
			break;
		case PC_CLASS_SHC:
		case PC_CLASS_SHC2:
			job = PC_JOB_SHC;
			break;
		case PC_CLASS_AG:
		case PC_CLASS_AG2:
			job = PC_JOB_AG;
			break;
		case PC_CLASS_CD:
		case PC_CLASS_CD2:
			job = PC_JOB_CD;
			break;
		case PC_CLASS_WH:
		case PC_CLASS_WH2:
		case PC_CLASS_WH3:
			job = PC_JOB_WH;
			break;
		case PC_CLASS_IG:
		case PC_CLASS_IG2:
		case PC_CLASS_IG3:
			job = PC_JOB_IG;
			break;
		case PC_CLASS_BO:
		case PC_CLASS_BO2:
			job = PC_JOB_BO;
			break;
		case PC_CLASS_ABC:
		case PC_CLASS_ABC2:
			job = PC_JOB_ABC;
			break;
		case PC_CLASS_EM:
		case PC_CLASS_EM2:
			job = PC_JOB_EM;
			break;
		case PC_CLASS_IQ:
		case PC_CLASS_IQ2:
			job = PC_JOB_IQ;
			break;
		case PC_CLASS_TRB:
		case PC_CLASS_TRB2:
			job = PC_JOB_TRB;
			break;
		case PC_CLASS_TRV:
		case PC_CLASS_TRV2:
			job = PC_JOB_TRV;
			break;
		case PC_CLASS_SKE:
		case PC_CLASS_SKE2:
		case PC_CLASS_SKE3:
			job = PC_JOB_SKE;
			break;
		case PC_CLASS_SOA:
		case PC_CLASS_SOA2:
			job = PC_JOB_SOA;
			break;
		case PC_CLASS_SK:
		case PC_CLASS_SK2:
			job = PC_JOB_SK;
			break;
		case PC_CLASS_SN:
		case PC_CLASS_SN2:
			job = PC_JOB_SN;
			break;
		case PC_CLASS_NW:
		case PC_CLASS_NW2:
			job = PC_JOB_NW;
			break;
		case PC_CLASS_HN:
		case PC_CLASS_HN2:
			job = PC_JOB_HN;
			break;
		case PC_CLASS_SH:
		case PC_CLASS_SH2:
			job = PC_JOB_SH;
			break;
	}

	return job;
}

/*==========================================
 * �O�E��Class�擾
 *------------------------------------------
 */
int pc_get_base_class(int class_, int type)
{
	/* �]���E�{�q���猳�̐E�Ƃ֕ϊ� */
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
		case PC_CLASS_SJ:
		case PC_CLASS_SJ_B:
		case PC_CLASS_SJ2:
		case PC_CLASS_SJ2_B:
		case PC_CLASS_SJ3:
		case PC_CLASS_SJ3_B:
			class_ = PC_CLASS_SJ;
			break;
		case PC_CLASS_SP:
		case PC_CLASS_SP_B:
		case PC_CLASS_SP2:
		case PC_CLASS_SP2_B:
			class_ = PC_CLASS_SP;
			break;
		case PC_CLASS_DK:
		case PC_CLASS_DK2:
		case PC_CLASS_DK3:
			class_ = PC_CLASS_DK;
			break;
		case PC_CLASS_MT:
		case PC_CLASS_MT2:
		case PC_CLASS_MT3:
			class_ = PC_CLASS_MT;
			break;
		case PC_CLASS_SHC:
		case PC_CLASS_SHC2:
			class_ = PC_CLASS_SHC;
			break;
		case PC_CLASS_AG:
		case PC_CLASS_AG2:
			class_ = PC_CLASS_AG;
			break;
		case PC_CLASS_CD:
		case PC_CLASS_CD2:
			class_ = PC_CLASS_CD;
			break;
		case PC_CLASS_WH:
		case PC_CLASS_WH2:
		case PC_CLASS_WH3:
			class_ = PC_CLASS_WH;
			break;
		case PC_CLASS_IG:
		case PC_CLASS_IG2:
		case PC_CLASS_IG3:
			class_ = PC_CLASS_IG;
			break;
		case PC_CLASS_BO:
		case PC_CLASS_BO2:
			class_ = PC_CLASS_BO;
			break;
		case PC_CLASS_ABC:
		case PC_CLASS_ABC2:
			class_ = PC_CLASS_ABC;
			break;
		case PC_CLASS_EM:
		case PC_CLASS_EM2:
			class_ = PC_CLASS_EM;
			break;
		case PC_CLASS_IQ:
		case PC_CLASS_IQ2:
			class_ = PC_CLASS_IQ;
			break;
		case PC_CLASS_TRB:
		case PC_CLASS_TRB2:
			class_ = PC_CLASS_TRB;
			break;
		case PC_CLASS_TRV:
		case PC_CLASS_TRV2:
			class_ = PC_CLASS_TRV;
			break;
		case PC_CLASS_SKE:
		case PC_CLASS_SKE2:
		case PC_CLASS_SKE3:
			class_ = PC_CLASS_SKE;
			break;
		case PC_CLASS_SOA:
		case PC_CLASS_SOA2:
			class_ = PC_CLASS_SOA;
			break;
		case PC_CLASS_SK:
		case PC_CLASS_SK2:
			class_ = PC_CLASS_SK;
			break;
		case PC_CLASS_SN:
		case PC_CLASS_SN2:
			class_ = PC_CLASS_SN;
			break;
		case PC_CLASS_NW:
		case PC_CLASS_NW2:
			class_ = PC_CLASS_NW;
			break;
		case PC_CLASS_HN:
		case PC_CLASS_HN2:
			class_ = PC_CLASS_HN;
			break;
		case PC_CLASS_SH:
		case PC_CLASS_SH2:
			class_ = PC_CLASS_SH;
			break;
	}

	if(type < 4) {
		/* 4���E����3���E�ɕϊ� */
		switch(class_){
			case PC_CLASS_DK:
				class_ = PC_CLASS_RK;
				break;
			case PC_CLASS_MT:
				class_ = PC_CLASS_NC;
				break;
			case PC_CLASS_SHC:
				class_ = PC_CLASS_GC;
				break;
			case PC_CLASS_AG:
				class_ = PC_CLASS_WL;
				break;
			case PC_CLASS_CD:
				class_ = PC_CLASS_AB;
				break;
			case PC_CLASS_WH:
				class_ = PC_CLASS_RA;
				break;
			case PC_CLASS_IG:
				class_ = PC_CLASS_LG;
				break;
			case PC_CLASS_BO:
				class_ = PC_CLASS_GN;
				break;
			case PC_CLASS_ABC:
				class_ = PC_CLASS_SC;
				break;
			case PC_CLASS_EM:
				class_ = PC_CLASS_SO;
				break;
			case PC_CLASS_IQ:
				class_ = PC_CLASS_SR;
				break;
			case PC_CLASS_TRB:
				class_ = PC_CLASS_MI;
				break;
			case PC_CLASS_TRV:
				class_ = PC_CLASS_WA;
				break;
			case PC_CLASS_SKE:
				class_ = PC_CLASS_SJ;
				break;
			case PC_CLASS_SOA:
				class_ = PC_CLASS_SP;
				break;
		}
	}

	if(type < 3) {
		/* 3���E����2���E�ɕϊ� */
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
			case PC_CLASS_SJ:
				class_ = PC_CLASS_SG;
				break;
			case PC_CLASS_SP:
				class_ = PC_CLASS_SL;
				break;
			case PC_CLASS_SK:
				class_ = PC_CLASS_KG;
				break;
			case PC_CLASS_SN:
				class_ = PC_CLASS_OB;
				break;
			case PC_CLASS_NW:
				class_ = PC_CLASS_RL;
				break;
			case PC_CLASS_HN:
				class_ = PC_CLASS_ESNV;
				break;
		}
	}

	if(type < 2) {
		/* 2���E����1���E�ɕϊ� */
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
		case PC_CLASS_DE:
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
		case PC_CLASS_ESNV:
			class_ = PC_CLASS_SNV;
			break;
		case PC_CLASS_SH:
			class_ = PC_CLASS_SUM;
			break;
		}
	}

	return class_;
}

/*==========================================
 * Job����O�E�Ƃ�Job���擾
 *------------------------------------------
 */
int pc_get_base_job(int job, int type)
{
	/* 4���E����3���E�ɕϊ� */
	if(type < 4) {
		switch(job){
			case PC_JOB_DK:  job = PC_JOB_RK; break;		// �h���S���i�C�g -> ���[���i�C�g
			case PC_JOB_MT:  job = PC_JOB_NC; break;		// �}�C�X�^�[ -> ���J�j�b�N
			case PC_JOB_SHC: job = PC_JOB_GC; break;		// �V���h�E�N���X -> �M���`���N���X
			case PC_JOB_AG:  job = PC_JOB_WL; break;		// �A�[�N���C�W -> �E�H�[���b�N
			case PC_JOB_CD:  job = PC_JOB_AB; break;		// �J�[�f�B�i�� -> �A�[�N�r�V���b�v
			case PC_JOB_WH:  job = PC_JOB_RA; break;		// �E�B���h�z�[�N -> �����W���[
			case PC_JOB_IG:  job = PC_JOB_LG; break;		// �C���y���A���K�[�h -> ���C�����K�[�h
			case PC_JOB_BO:  job = PC_JOB_GN; break;		// �o�C�I�� -> �W�F�l�e�B�b�N
			case PC_JOB_ABC: job = PC_JOB_SC; break;		// �A�r�X�`�F�C�T�[ -> �V���h�E�`�F�C�T�[
			case PC_JOB_EM:  job = PC_JOB_SO; break;		// �G�������^���}�X�^�[ -> �\�[�T���[
			case PC_JOB_IQ:  job = PC_JOB_SR; break;		// �C���N�C�W�^�[ -> �C��
			case PC_JOB_TRB: job = PC_JOB_MI; break;		// �g���o�h�D�[�� -> �~���X�g����
			case PC_JOB_TRV: job = PC_JOB_WA; break;		// �g�����F�[�� -> �����_���[
			case PC_JOB_SKE: job = PC_JOB_SJ; break;		// �V�� -> ����
			case PC_JOB_SOA: job = PC_JOB_SP; break;		// �\�E���A�Z�e�B�b�N -> �\�E�����[�p�[
		}
	}

	/* 3���E����2���E�ɕϊ� */
	if(type < 3) {
		switch(job){
			case PC_JOB_RK: job = PC_JOB_KN; break;		// ���[���i�C�g -> �i�C�g
			case PC_JOB_WL: job = PC_JOB_WZ; break;		// �E�H�[���b�N -> �E�B�U�[�h
			case PC_JOB_RA: job = PC_JOB_HT; break;		// �����W���[ -> �n���^�[
			case PC_JOB_AB: job = PC_JOB_PR; break;		// �A�[�N�r�V���b�v -> �v���[�X�g
			case PC_JOB_NC: job = PC_JOB_BS; break;		// ���J�j�b�N -> �u���b�N�X�~�X
			case PC_JOB_GC: job = PC_JOB_AS; break;		// �M���`���N���X -> �A�T�V��
			case PC_JOB_LG: job = PC_JOB_CR; break;		// ���C�����K�[�h -> �N���Z�C�_�[
			case PC_JOB_SO: job = PC_JOB_SA; break;		// �\�[�T���[ -> �Z�[�W
			case PC_JOB_MI: job = PC_JOB_BA; break;		// �~���X�g���� -> �o�[�h
			case PC_JOB_WA: job = PC_JOB_DC; break;		// �����_���[ -> �_���T�[
			case PC_JOB_SR: job = PC_JOB_MO; break;		// �C�� -> �����N
			case PC_JOB_GN: job = PC_JOB_AM; break;		// �W�F�l�e�B�b�N -> �A���P�~�X�g
			case PC_JOB_SC: job = PC_JOB_RG; break;		// �V���h�E�`�F�C�T�[ -> ���[�O
			case PC_JOB_SJ: job = PC_JOB_SG; break;		// ���� -> ����
			case PC_JOB_SP: job = PC_JOB_SL; break;		// �\�E�����[�p�[ -> �\�E�������J�[
			case PC_JOB_SK: job = PC_JOB_KG; break;		// 凋C�O -> �e�T
			case PC_JOB_SN: job = PC_JOB_OB; break;		// �s�m�� -> �O
			case PC_JOB_NW: job = PC_JOB_RL; break;		// �i�C�g�E�H�b�` -> ���x���I��
			case PC_JOB_HN: job = PC_JOB_ESNV; break;	// �n�C�p�[�m�[�r�X -> �X�[�p�[�m�[�r�X(���E�˔j)
		}
	}

	/* 2���E����1���E�ɕϊ� */
	if(type < 2) {
		switch(job){
			case PC_JOB_KN: case PC_JOB_CR: job = PC_JOB_SM; break;		// �i�C�g/�N���Z�C�_�[ -> �\�[�h�}��
			case PC_JOB_PR: case PC_JOB_MO: job = PC_JOB_AL; break;		// �v���[�X�g/�����N -> �A�R���C�g
			case PC_JOB_WZ: case PC_JOB_SA: job = PC_JOB_MG; break; 	// �E�B�U�[�h/�Z�[�W -> �}�W�V����
			case PC_JOB_BS: case PC_JOB_AM: job = PC_JOB_MC; break;		// �u���b�N�X�~�X/�A���P�~�X�g -> �}�[�`�����g
			case PC_JOB_HT: case PC_JOB_BA: case PC_JOB_DC: job = PC_JOB_AC; break; 		// �n���^�[/�o�[�h/�_���T�[ -> �A�[�`���[
			case PC_JOB_AS: case PC_JOB_RG: job = PC_JOB_TF; break;		// �A�T�V��/���[�O -> �V�[�t
			case PC_JOB_SG: case PC_JOB_SL: job = PC_JOB_TK; break;		// ����/�\�E�������J�[ -> �e�R���L�b�h
			case PC_JOB_DE: case PC_JOB_DA: job = PC_JOB_MB; break;		// �f�X�i�C�g/�_�[�N�R���N�^�[ -> �L�����V�[
			case PC_JOB_ESNV: job = PC_JOB_SNV; break;		// �X�[�p�[�m�[�r�X(���E�˔j) -> �X�[�p�[�m�[�r�X
			case PC_JOB_KG: case PC_JOB_OB: job = PC_JOB_NJ; break;		// �e�T/�O -> �E��
			case PC_JOB_RL:   job = PC_JOB_GS;  break;		// ���x���I�� -> �K���X�����K�[
			case PC_JOB_SH:   job = PC_JOB_SUM; break;		// �X�s���b�g�n���h���[ -> �T���i�[
		}
	}

	return job;
}

/*==========================================
 * Base���x���A�b�v
 *------------------------------------------
 */
static int pc_checkbaselevelup(struct map_session_data *sd)
{
	atn_bignumber next;

	nullpo_retr(0, sd);

	next = pc_nextbaseexp(sd);

	if(sd->status.base_exp >= next && next > 0) {
		// base�����x���A�b�v����
		sd->status.base_exp -= next;
		sd->status.base_level++;
		sd->status.status_point += stpoint_table[sd->status.base_level-1];
		sd->status.tstatus_point += tstpoint_table[sd->status.base_level-1];
		clif_updatestatus(sd,SP_STATUSPOINT);
		clif_updatestatus(sd,SP_TSTATUSPOINT);
		clif_updatestatus(sd,SP_BASELEVEL);
		clif_updatestatus(sd,SP_NEXTBASEEXP);

		status_calc_pc_stop_begin(&sd->bl);

		status_calc_pc(sd,0);
		pc_heal(sd,sd->status.max_hp,sd->status.max_sp,0,0);

		// �X�p�m�r�̓L���G�A�C���|�A�}�j�s�A�O���A�T�t����������
		if(sd->s_class.job == PC_JOB_SNV || sd->s_class.job == PC_JOB_ESNV) {
			status_change_start(&sd->bl,SC_KYRIE,10,0,0,0,120000,0);
			status_change_start(&sd->bl,SC_IMPOSITIO,5,0,0,0,120000,0);
			status_change_start(&sd->bl,SC_MAGNIFICAT,5,0,0,0,120000,0);
			status_change_start(&sd->bl,SC_GLORIA,5,0,0,0,120000,0);
			status_change_start(&sd->bl,SC_SUFFRAGIUM,3,0,0,0,120000,0);
			clif_misceffect(&sd->bl,7);	// �X�p�m�r�V�g
		}
		else if(sd->s_class.job >= PC_JOB_TK && sd->s_class.job <= PC_JOB_SL) {
			status_change_start(&sd->bl,SC_BLESSING,10,0,0,0,600000,0);
			status_change_start(&sd->bl,SC_INCREASEAGI,10,0,0,0,600000,0);
			clif_misceffect(&sd->bl,9);	// �e�R���n�V�g
		}
		else {
			clif_misceffect(&sd->bl,0);
		}

		status_calc_pc_stop_end(&sd->bl);

		// ���x���A�b�v�����̂Ńp�[�e�B�[�����X�V����i�����͈̓`�F�b�N�j
		party_send_movemap(sd);

		achieve_update_content(sd, ACH_LEVEL, SP_BASELEVEL, sd->status.base_level);
		return 1;
	}

	return 0;
}

/*==========================================
 * Job���x���A�b�v
 *------------------------------------------
 */
static int pc_checkjoblevelup(struct map_session_data *sd)
{
	atn_bignumber next;

	nullpo_retr(0, sd);

	next = pc_nextjobexp(sd);

	if(sd->status.job_exp >= next && next > 0) {
		// job�����x���A�b�v����
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
 * �o���l�擾
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

	// �}�[�_���[�{�[�i�X
	if(battle_config.pk_murderer_point > 0) {
		if(ranking_get_point(sd,RK_PK) >= battle_config.pk_murderer_point) {
			base_exp *= 2;
			job_exp  *= 2;
		}
	}

	if (sd->status.guild_id > 0) {	// �M���h�ɏ�[
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
				// �{�I�d�l�̎擾�o���l���
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
				// �{�I�d�l�̎擾�o���l���
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
 * base level���K�v�o���l�v�Z
 *------------------------------------------
 */
atn_bignumber pc_nextbaseexp(struct map_session_data *sd)
{
	int table;

	nullpo_retr(0, sd);

	if(sd->status.base_level >= MAX_LEVEL || sd->status.base_level <= 0)
		return 0;

	table = job_db[sd->s_class.job].base_exp_table[sd->s_class.upper];

	if(table < 0 || table >= MAX_EXP_TABLE)
		table = 1;

	return exp_table[table][sd->status.base_level-1];
}

/*==========================================
 * job level���K�v�o���l�v�Z
 *------------------------------------------
 */
atn_bignumber pc_nextjobexp(struct map_session_data *sd)
{
	int table;

	nullpo_retr(0, sd);

	if(sd->status.job_level >= MAX_LEVEL || sd->status.job_level <= 0)
		return 0;

	table = job_db[sd->s_class.job].job_exp_table[sd->s_class.upper];

	if(table < 0 || table >= MAX_EXP_TABLE)
		table = 8;

	return exp_table[table][sd->status.job_level-1];
}

/*==========================================
 * �K�v�X�e�[�^�X�|�C���g�v�Z
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

	if(pc_is3rdclass(sd) || pc_is4thclass(sd)) {
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
 * �\�͒l����
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
	else if(pc_is3rdclass(sd) || pc_is4thclass(sd))
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
 * �\�͒l����
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
 * �K�v�����X�e�[�^�X�|�C���g�v�Z
 *------------------------------------------
 */
int pc_need_tstatus_point(struct map_session_data *sd,int type)
{
	int val = -1;

	nullpo_retr(-1, sd);

	switch(type) {
		case SP_POW:
			val = sd->status.pow;
			break;
		case SP_STA:
			val = sd->status.sta;
			break;
		case SP_WIS:
			val = sd->status.wis;
			break;
		case SP_SPL:
			val = sd->status.spl;
			break;
		case SP_CON:
			val = sd->status.con;
			break;
		case SP_CRT:
			val = sd->status.crt;
			break;
	}

	if(val >= battle_config.pc_tstatus_max)
		return 0;

	if(val < 0)
		val = -1;
	else
		val = 1;

	return val;
}

/*==========================================
 * �����X�e�[�^�X����
 *------------------------------------------
 */
void pc_tstatusup(struct map_session_data *sd, int type, int num)
{
	int need, tstatus_point;
	int val = 0;
	int max = battle_config.pc_tstatus_max;
	short *param = NULL;

	nullpo_retv(sd);

	if(type < SP_POW || type > SP_CRT || num <= 0) {
		clif_statusupack(sd,type,0,0);
		return;
	}

	need = pc_need_tstatus_point(sd,type);
	if(need < 0 || need > sd->status.tstatus_point) {
		clif_statusupack(sd,type,0,0);
		return;
	}

	switch(type) {
		case SP_POW:
			param = &sd->status.pow;
			break;
		case SP_STA:
			param = &sd->status.sta;
			break;
		case SP_WIS:
			param = &sd->status.wis;
			break;
		case SP_SPL:
			param = &sd->status.spl;
			break;
		case SP_CON:
			param = &sd->status.con;
			break;
		case SP_CRT:
			param = &sd->status.crt;
			break;
		default:
			clif_statusupack(sd,type,0,0);
			return;
	}

	if((*param) >= max) {
		clif_statusupack(sd,type,0,0);
		return;
	}

	val = (*param);
	if(max > val + num)
		max = val + num;

	tstatus_point = sd->status.tstatus_point;

	while(max > val && tstatus_point > 0) {
		val++;
		tstatus_point--;
	}

	(*param) = val;
	sd->status.tstatus_point = tstatus_point;
	if(need != pc_need_tstatus_point(sd,type)) {
		clif_updatestatus(sd,type-SP_POW+SP_UPOW);
	}

	clif_updatestatus(sd,SP_TSTATUSPOINT);
	clif_updatestatus(sd,type);
	status_calc_pc(sd,0);
	clif_statusupack(sd,type,1,val);

	achieve_update_content(sd, ACH_STATUS, type, val);

	return;
}

/*==========================================
 * �K�v�Ȏg�p�ς݃X�L���|�C���g���擾
 *------------------------------------------
 */
static int pc_calc_needskillpoint(struct map_session_data *sd, int class_level)
{
	int point = 0;
	int max = 0;

	nullpo_retr(0, sd);

	switch( class_level ) {
	case 0:		// �m�[�r�X�X�L��
		point = 0;	// �m�[�r�X�X�L���͕K�v�|�C���g0
		max = 0;
		break;
	case 1:		// �ꎟ�E�X�L��
		if(pc_isdoram(sd)) {		// �h�����n��
			point = 0;	// �h�����X�L���͕K�v�|�C���g0
			max = 0;
			break;
		} else {
			point = pc_readglobalreg(sd,"PC_USESKILLPOINT_0TH");
			max = battle_config.max_skillpoint_nv;
		}
		break;
	case 2:		// �񎟐E�X�L��
		point = pc_readglobalreg(sd,"PC_USESKILLPOINT_1ST");
		if(pc_isexclass(sd)) {		// �E�ҁE�K���X�����K�[�n��
			max = battle_config.max_skillpoint_ex1st;
		} else if(pc_issnovice(sd)) {		// �X�[�p�[�m�[�r�X�n��
			max = battle_config.max_skillpoint_snv;
		} else if(pc_isdoram(sd)) {		// �h�����n��
			max = battle_config.max_skillpoint_doram;
		} else {
			max = battle_config.max_skillpoint_1st;
		}
		break;
	case 3:		// �O���E�X�L��
		point = pc_readglobalreg(sd,"PC_USESKILLPOINT_2ND");
		if(pc_istaekwon(sd)) {		// �e�R���n��
			max = battle_config.max_skillpoint_tk2nd;
		} else if(pc_isexclass(sd)) {		// �E�ҁE�K���X�����K�[�n��
			max = battle_config.max_skillpoint_ex2nd;
		} else if(pc_issnovice(sd)) {		// �X�[�p�[�m�[�r�X�n��
			max = battle_config.max_skillpoint_esnv;
		} else if(pc_isupper(sd)) {			// �]���E
			max = battle_config.max_skillpoint_2nd;
		} else {
			max = battle_config.max_skillpoint_n2nd;
		}
		break;
	case 4:		// �l���E
		point = pc_readglobalreg(sd,"PC_USESKILLPOINT_3RD");
		if(pc_istaekwon(sd)) {		// �e�R���n��
			max = battle_config.max_skillpoint_tk3rd;
		} else if(pc_isupper(sd)) {			// �]���E
			max = battle_config.max_skillpoint_3rd;
		} else {
			max = battle_config.max_skillpoint_n3rd;
		}
		break;
	}

	// �]�E�L�^�������ꍇ �������� �]�E�L�^���ő�l�𒴂��Ă���ꍇ
	if(point == 0 && max > 0 || point > max) {
		point = max;
	}

	return point;
}

/*==========================================
 * �X�L���擾�\���ǂ���
 *------------------------------------------
 */
static int pc_check_skillup(struct map_session_data *sd,int skill_num)
{
	int skill_point,need_point;
	struct skill_tree_entry *st;
	char output[100];

	nullpo_retr(0, sd);

	st = pc_search_skilltree(&sd->s_class, skill_num);
	if(st == NULL)
		return 0;

	if(battle_config.skillup_limit) {
		// ���ݎg�p�ς݃X�L���|�C���g���擾
		skill_point = pc_calc_skillpoint(sd);
		
		// �K�v�Ȏg�p�ς݃X�L���|�C���g���擾
		need_point = pc_calc_needskillpoint(sd, st->class_level);

		// �K�v�Ȏg�p�ς݃X�L���|�C���g�ɒB���Ă��Ȃ����NG
		if(skill_point  < need_point) {
			// �X�L�������N���ƂɃ��b�Z�[�W�\��
			switch( st->class_level ){
			case 1:
				snprintf(output, sizeof(output), msg_txt(213), need_point - skill_point);		// ��{�X�L�� %d���グ�Ă��������B
				clif_disp_onlyself(sd->fd, output);
				break;
			case 2:
				clif_msgstringtable3(sd, 1566, need_point - skill_point);	// 1���E�X�L�� %d�������Əグ�Ă��������B
				break;
			case 3:
				clif_msgstringtable3(sd, 1567, need_point - skill_point);	// 1���܂���2���E�X�L�� %d���グ�Ă��������B
				break;
			case 4:
				clif_msgstringtable3(sd, 3690, need_point - skill_point);	// 1���A2���A3���E�X�L�� %d���グ�Ă��������B
				break;
			default:
				snprintf(output, sizeof(output), msg_txt(214), need_point - skill_point);		// ���ʐE�X�L�� %d���グ�Ă��������B
				clif_disp_onlyself(sd->fd, output);
				break;
			}
			return 0;
		}
	}

	return 1;
}

/*==========================================
 * �X�L���|�C���g����U��
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
		if(sd->status.skill[i].flag) {	// card�X�L���Ȃ�A
			sd->status.skill[i].lv   = (sd->status.skill[i].flag == 1)? 0: sd->status.skill[i].flag-2;	// �{����lv��
			sd->status.skill[i].flag = 0;	// flag��0�ɂ��Ă���
		}
	}

	if(battle_config.gm_allskill > 0 && pc_isGM(sd) >= battle_config.gm_allskill) {
		// �S�ẴX�L��
		for(i = 1; i <= MAX_PCSKILL; i++) {
			// NPC�X�L���͏��O
			if(skill_get_inf2(i)&INF2_NPC)
				continue;
			// ���z�ƌ��Ɛ��̈����͏��O�i�y�i���e�B�̉i���Èł������̂Łj
			// ����ɔ������z�ƌ��Ɛ��̏򉻂����O
			if((i == SG_DEVIL) || (i == SJ_PURIFY))
				continue;
			// �A�u���J�^�u����p�X�L���͐ݒ�l�ɂ��擾����
			if(i >= 291 && i <= 303 && !battle_config.gm_allskill_addabra)
				continue;
			sd->status.skill[i].lv = skill_get_max(i);
		}
	} else {
		int id;
		for(i=0; (id = skill_tree[sd->s_class.job][i].id) > 0; i++) {
			// ���z�ƌ��Ɛ��̈����͏��O�i�y�i���e�B�̉i���Èł������̂Łj
			// ����ɔ������z�ƌ��Ɛ��̏򉻂����O
			if((i == SG_DEVIL) || (i == SJ_PURIFY))
				continue;
			// �]������������X�L���͓]�������𔻒�
			if(skill_tree[sd->s_class.job][i].upper > 0 && sd->s_class.upper != skill_tree[sd->s_class.job][i].upper)
				continue;
			// flag������Ȃ�N�G�X�g�X�L�����擾����
			if(skill_get_inf2(id)&INF2_QUEST && !flag && !battle_config.quest_skill_learn)
				continue;
			sd->status.skill[id].id = id;
			sd->status.skill[id].lv = skill_tree[sd->s_class.job][i].max;
		}
	}
	status_calc_pc(sd,0);

	// status_calc_pc() ���Ńp�P�b�g���M����Ȃ��ꍇ������̂ł����ł�����x���M����K�v������
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

void pc_resetstatus(struct map_session_data* sd, int flag)
{
	int add = 0;
	int param[6];
	int i;

	nullpo_retv(sd);

	// ��{�X�e�[�^�X�̃��Z�b�g
	if(flag == 0 || flag&1) {
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
	}

	// �����X�e�[�^�X�̃��Z�b�g
	if(flag == 0 || flag&2) {
		sd->status.tstatus_point += sd->status.pow;
		sd->status.tstatus_point += sd->status.sta;
		sd->status.tstatus_point += sd->status.wis;
		sd->status.tstatus_point += sd->status.spl;
		sd->status.tstatus_point += sd->status.con;
		sd->status.tstatus_point += sd->status.crt;
		clif_updatestatus(sd,SP_TSTATUSPOINT);

		sd->status.pow = 0;
		clif_updatestatus(sd,SP_POW);
		clif_updatestatus(sd,SP_UPOW);

		sd->status.sta = 0;
		clif_updatestatus(sd,SP_STA);
		clif_updatestatus(sd,SP_USTA);

		sd->status.wis = 0;
		clif_updatestatus(sd,SP_WIS);
		clif_updatestatus(sd,SP_UWIS);

		sd->status.spl = 0;
		clif_updatestatus(sd,SP_SPL);
		clif_updatestatus(sd,SP_USPL);

		sd->status.con = 0;
		clif_updatestatus(sd,SP_CON);
		clif_updatestatus(sd,SP_UCON);

		sd->status.crt = 0;
		clif_updatestatus(sd,SP_CRT);
		clif_updatestatus(sd,SP_UCRT);
	}
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

	for(i=1; i<MAX_PCSKILL; i++) {
		if((skill = pc_checkskill2(sd,i)) > 0) {
			if(sd->status.skill[i].id == NV_BASIC && !(flag&2)) {
				// flag��2�ȊO�̏ꍇ�͊�{�X�L���̓��Z�b�g���Ȃ�
				continue;
			}
			else if(!(skill_get_inf2(i)&INF2_QUEST) || battle_config.quest_skill_learn) {
				if(!sd->status.skill[i].flag) {
					sd->status.skill_point += skill;
				} else if(sd->status.skill[i].flag > 2) {
					sd->status.skill_point += (sd->status.skill[i].flag - 2);
				}
				sd->status.skill[i].lv = 0;
			}
			else if(flag&1) {
				// flag��1�̏ꍇ�̓N�G�X�g�X�L�������Z�b�g����
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
 * PC�Ƀ_���[�W��^����
 *------------------------------------------
 */
int pc_damage(struct block_list *src,struct map_session_data *sd,int damage)
{
	int i;

	nullpo_retr(0, sd);

	// ���Ɏ���ł����疳��
	if(unit_isdead(&sd->bl))
		return 0;
	// �����Ă��痧���オ��
	if(pc_issit(sd) && sd->sc.data[SC_SITDOWN_FORCE].timer == -1 && sd->sc.data[SC_BANANA_BOMB].timer == -1) {
		pc_setstand(sd);
		skill_sit(sd,0);
	}

	// �r���o�[�\�����������璆�f
	if(sd->progressbar.npc_id) {
		clif_progressbar_abort(sd);
		clif_scriptclose(sd, sd->progressbar.npc_id);
	}

	// �����Ă����瑫���~�߂�
	if(((sd->sc.data[SC_ENDURE].timer == -1 && sd->sc.data[SC_BERSERK].timer == -1 && !sd->special_state.infinite_endure) || map[sd->bl.m].flag.gvg) && !unit_isrunning(&sd->bl))
		unit_stop_walking(&sd->bl,battle_config.pc_hit_stop_type);

	// ���t/�_���X�̒��f
	if(damage > sd->status.max_hp>>2)
		skill_stop_dancing(&sd->bl,0);

	if(damage > 0 && sd->sc.data[SC_GRAVITATION_USER].timer != -1)
		status_change_end(&sd->bl, SC_GRAVITATION_USER, -1);

	// �搧���ꂽ�ꍇ�͋����Q��
	if(src && src->type == BL_MOB)
		battle_join_struggle((struct mob_data *)src, &sd->bl);

	sd->status.hp -= damage;
	if(sd->status.pet_id > 0 && sd->pd && sd->petDB && battle_config.pet_damage_support)
		pet_target_check(sd,src,1);

	// �n�C�h��Ԃ�����
	status_change_hidden_end(&sd->bl);

	// �G�̍U�����󂯂�ƈ��m���ő���������
	if(sd->loss_equip_flag&0x1000 && damage > 0) {	// ���@�ł�����
		for(i=0; i<EQUIP_INDEX_MAX; i++) {
			if(atn_rand()%10000 < sd->break_myequip_rate_when_hit[i])
				pc_break_equip2(sd,i);
		}
	}

	// �G�̍U�����󂯂�ƈ��m���ő���������
	if(sd->loss_equip_flag&0x0020 && damage > 0) {
		for(i=0; i<EQUIP_INDEX_MAX; i++) {
			if(atn_rand()%10000 < sd->loss_equip_rate_when_hit[i])
				pc_lossequipitem(sd,i,0);
		}
	}

	if(sd->status.hp > 0) {
		// �܂������Ă���Ȃ�HP�X�V
		clif_updatestatus(sd,SP_HP);

		if( sd->sc.data[SC_AUTOBERSERK].timer != -1 &&
		    sd->status.hp < sd->status.max_hp>>2 &&
		    (sd->sc.data[SC_PROVOKE].timer == -1 || sd->sc.data[SC_PROVOKE].val2 == 0) )
		{
			// �I�[�g�o�[�T�[�N����
			status_change_start(&sd->bl,SC_PROVOKE,10,1,0,0,0,0);
		}
		return 0;
	}

	// �X�p�m�r��HP0�ɂȂ����Ƃ��AExp99.0%�ȏォLv100��ԂȂ��HP���S�񕜂��ċ�����ԂɂȂ�
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

	// ���S����
	pc_dead(src, sd);

	return 0;
}

/*==========================================
 * pc�̎��S����
 *------------------------------------------
 */
static int pc_dead(struct block_list *src,struct map_session_data *sd)
{
	int i, kaizel_lv = 0;
	struct map_session_data *ssd = NULL;

	nullpo_retr(0, sd);

	if(src && src->type == BL_PC)
		ssd = (struct map_session_data *)src;

	// OnPCDie�C�x���g
	if(battle_config.pc_die_script)
		npc_event_doall_id("OnPCDie",sd->bl.id,sd->bl.m);

	// �L���[���X�V�����OnPCKill�C�x���g
	if(ssd && ssd != sd) {
		if(battle_config.save_pckiller_type) {
			if( (battle_config.save_pckiller_type & 1 && map[sd->bl.m].flag.pvp) ||
			    (battle_config.save_pckiller_type & 2 && map[sd->bl.m].flag.gvg) ||
			    (battle_config.save_pckiller_type & 4 && map[sd->bl.m].flag.pk) )
			{
				ssd->kill.char_id  = sd->status.char_id;		// �������E��������̃L����ID
				sd->kill.merderer_char_id = ssd->status.char_id;	// �������E��������̃L����ID
				clif_update_temper(ssd);
				clif_update_temper(sd);
			}
		}
		if(battle_config.pc_kill_script)
			npc_event_doall_id("OnPCKill",sd->bl.id,sd->bl.m);
	}

	// �J�C�[��
	if(sd->sc.data[SC_KAIZEL].timer != -1) {
		kaizel_lv = sd->sc.data[SC_KAIZEL].val1;	// �X�e�[�^�X�ُ킪���������O�ɃX�L��Lv��ۑ�
		if(kaizel_lv > 10)
			kaizel_lv = 10;
	}

	// �A�C�e������
	if(sd->loss_equip_flag&0x0001) {
		for(i=0; i<EQUIP_INDEX_MAX; i++) {
			if(atn_rand()%10000 < sd->loss_equip_rate_when_die[i])
				pc_lossequipitem(sd,i,0);
		}
	}

	// �A���e�B���b�g�T�N���t�@�C�X
	if(sd->sc.data[SC_ULTIMATE_S].timer != -1) {
		clif_skill_nodamage(&sd->bl,&sd->bl,IG_ULTIMATE_SACRIFICE,-1,1);
		sd->status.hp = sd->status.max_hp;
		sd->status.sp = sd->status.max_sp;
		clif_updatestatus(sd,SP_HP);
		clif_updatestatus(sd,SP_SP);
		status_change_end(&sd->bl,SC_ULTIMATE_S,-1);
		return 0;
	}

	// �����h��
	if(atn_rand()%10000 < sd->autoraise.rate)
	{
		// ����ɂ����̂Ń��U�̃G�t�F�N�g
		clif_skill_nodamage(&sd->bl,&sd->bl,ALL_RESURRECTION,4,1);

		// HPSP��
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

	if(pc_isgear(sd))		// �����M�A������
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
		//clif_disp_onlyself(sd->fd, msg_txt(191));	// �b�����������܂����B
		clif_msgstringtable(sd, 0x4f5);
		merc_delete_data(sd);
	}
	if(sd->status.homun_id > 0 && sd->hd) {
		// �Đ��̌�
		if(sd->sc.data[SC_LIGHT_OF_REGENE].timer != -1) {
			homun_damage(NULL, sd->hd, status_get_max_hp(&sd->hd->bl));
		}
	}

	unit_stop_walking(&sd->bl,0);
	unit_skillcastcancel(&sd->bl,0);	// �r���̒��~
	skill_stop_dancing(&sd->bl, 0);
	clif_clearchar_area(&sd->bl,1);
	skill_unit_move(&sd->bl,gettick(),0);
	if(sd->sc.data[SC_BLADESTOP].timer != -1)		// ���n�͎��O�ɉ���
		status_change_end(&sd->bl,SC_BLADESTOP,-1);
	if(sd->sc.data[SC_CLOSECONFINE].timer != -1)	// �N���[�Y�R���t�@�C���͎��O�ɉ���
		status_change_end(&sd->bl,SC_CLOSECONFINE,-1);
	if(sd->sc.data[SC_STOP].timer != -1)
		status_change_end(&sd->bl,SC_STOP,-1);
	if(sd->sc.data[SC_CURSEDCIRCLE_USER].timer != -1)
		status_change_end(&sd->bl,SC_CURSEDCIRCLE_USER,-1);
	if(sd->sc.data[SC_CURSEDCIRCLE].timer != -1)
		status_change_end(&sd->bl,SC_CURSEDCIRCLE,-1);
	sd->status.die_counter++;	// ���ɃJ�E���^�[��������
	status_change_release(&sd->bl,0x01);	// �X�e�[�^�X�ُ����������

	pc_setdead(sd);

	if(sd->s_class.job == PC_JOB_NV) {
		if(battle_config.restart_hp_rate <= 50)		// �m�r�Ń��[�g50�ȉ��͔�����
			sd->status.hp = sd->status.max_hp / 2;
		else
			sd->status.hp = sd->status.max_hp * battle_config.restart_hp_rate / 100;
	}

	clif_updatestatus(sd,SP_HP);

	sd->status.ap = 0;
	clif_updatestatus(sd,SP_AP);

	status_calc_pc(sd,0);

	// �h�N���h���b�v
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
		*((int *)(&item_tmp.card[2])) = sd->status.char_id;	// �L����ID
		map_addflooritem(&item_tmp,1,sd->bl.m,sd->bl.x,sd->bl.y,0,0,0,0);
	}

	for(i=0; i<5; i++) {
		if(sd->dev.val1[i]) {
			status_change_end(map_id2bl(sd->dev.val1[i]),SC_DEVOTION,-1);
			sd->dev.val1[i] = sd->dev.val2[i] = 0;
		}
	}

	//���̈� ����
	for (i = 0; i < MAX_STELLAR_MARKS; i++) {
		if (sd->stellar_mark[i]) {
			struct map_session_data *smarksd = map_id2sd(sd->stellar_mark[i]);

			if (smarksd)
				status_change_end(&smarksd->bl, SC_FLASHKICK, -1);
			sd->stellar_mark[i] = 0;
		}
	}

	// �V���h�E�t�H�[���I��
	if(sd->shadowform_id) {
		status_change_end(map_id2bl(sd->shadowform_id),SC__SHADOWFORM,-1);
		sd->shadowform_id = 0;
	}

	// ���S����Ƀf�X�y�i���e�B�𔭐�������ꍇ
	if(battle_config.death_penalty_type&1)
		pc_exp_penalty(sd, ssd, 100, 1);

	// PK
	if(map[sd->bl.m].flag.pk) {
		// �����L���O�v�Z
		/*
		if(!map[sd->bl.m].flag.pk_nocalcrank) {
			sd->pvp_point -= 5;
			if(ssd)
				ssd->pvp_point++;
		}
		*/
		// �i�C�g���A���[�h�A�C�e���h���b�v
		if(ssd && ssd != sd && map[sd->bl.m].flag.pk_nightmaredrop) {
			pc_nightmare_drop(sd,MF_PK_NIGHTMAREDROP);
			pc_setdead(sd);
		}
		if(ssd && ssd != sd) {
			// ��s�E��
			ranking_gain_point(sd,RK_PK,-5);
			ranking_setglobalreg(sd,RK_PK);
			ranking_update(sd,RK_PK);
			// �s�E��
			ranking_gain_point(ssd,RK_PK,1);
			ranking_setglobalreg(ssd,RK_PK);	// MOB�ȂǍX�V�񐔂������ꍇ�͒���I�ɍX�V
			ranking_update(ssd,RK_PK);		// MOB�ȂǍX�V�񐔂������ꍇ�͒���I�ɍX�V
			status_change_start(&ssd->bl,SC_PK_PENALTY,0,0,0,0,battle_config.pk_penalty_time,0);
		}
	}
	// PvP
	if(map[sd->bl.m].flag.pvp) {
		// �����L���O�v�Z
		if(!map[sd->bl.m].flag.pvp_nocalcrank) {
			sd->pvp_point -= 5;
			if(ssd)
				ssd->pvp_point++;
		}
		// �i�C�g���A���[�h�A�C�e���h���b�v
		if(map[sd->bl.m].flag.pvp_nightmaredrop) {
			pc_nightmare_drop(sd,MF_PVP_NIGHTMAREDROP);
			pc_setdead(sd);
		}

		/*
		// �����L���O�T���v��
		if(ssd) {
			ranking_gain_point(ssd,RK_PVP,1);
			ranking_setglobalreg(ssd,RK_PVP);	// MOB�ȂǍX�V�񐔂������ꍇ�͒���I�ɍX�V
			ranking_update(ssd,RK_PVP);		// MOB�ȂǍX�V�񐔂������ꍇ�͒���I�ɍX�V

			// ���񂾏ꍇ�|�C���g�����炷�Ȃ�
			//if(ranking_get_point(sd,RK_PVP) > =1) {
			//	ranking_gain_point(sd,RK_PVP,-1);
			//	ranking_setglobalreg(sd,RK_PVP);	// MOB�ȂǍX�V�񐔂������ꍇ�͒���I�ɍX�V
			//	ranking_update(sd,RK_PVP);		// MOB�ȂǍX�V�񐔂������ꍇ�͒���I�ɍX�V
			//}
		}
		*/
	}
	// GvG
	if(map[sd->bl.m].flag.gvg) {
		// �i�C�g���A���[�h�A�C�e���h���b�v
		if(map[sd->bl.m].flag.gvg_nightmaredrop) {
			pc_nightmare_drop(sd,MF_GVG_NIGHTMAREDROP);
		}
	}

	if((map[sd->bl.m].flag.pvp && sd->pvp_point < 0) || map[sd->bl.m].flag.gvg || map[sd->bl.m].flag.norevive) {
		// ��������
		sd->pvp_point = 0;
		pc_setpos(sd,sd->status.save_point.map,sd->status.save_point.x,sd->status.save_point.y,0);
	}
	else if(kaizel_lv > 0) {
		// �S�Ă̏������������Ă���J�C�[���ɂ�镜��
		pc_setstand(sd);
		clif_skill_nodamage(&sd->bl,&sd->bl,ALL_RESURRECTION,4,1);
		// �I�V���X�J�[�h
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
 * �i�C�g���A���[�h�̃A�C�e���h���b�v
 *------------------------------------------
 */
static int pc_nightmare_drop(struct map_session_data *sd,short flag)
{
	int i;

	nullpo_retr(0, sd);

	for(i=0; i<MAX_DROP_PER_MAP; i++) {
		int itemid, type, per, j;
		int idx = -1, count = 0;

		// �A�C�e��ID��0�̂Ƃ��͖����Ȃ̂ŏI��
		if((itemid = map[sd->bl.m].drop_list[i].drop_id) == 0)
			break;
		// �}�b�v�t���O�ԍ�������Ȃ�
		if(flag != map[sd->bl.m].drop_list[i].drop_flag)
			continue;

		type = map[sd->bl.m].drop_list[i].drop_type;
		per  = map[sd->bl.m].drop_list[i].drop_per;

		if(type < 1 || type > 3 || per <= 0)
			continue;

		for(j=0; j<MAX_INVENTORY; j++) {
			if(sd->status.inventory[j].nameid <= 0 || sd->status.inventory[j].amount <= 0)
				continue;

			// type=1,2�͑����`�F�b�N�Atype=3�Ȃ疳�����ŋ���
			if( (type == 1 && sd->status.inventory[j].equip) ||
			    (type == 2 && !sd->status.inventory[j].equip) )
				continue;

			// ID������ꍇ�AID����v���Ă��Ċm��OK�Ȃ�h���b�v������
			if(itemid > 0 && itemid == sd->status.inventory[j].nameid && atn_rand()%10000 < per) {
				idx = j;
				break;
			}
			// ID�����̏ꍇ�A�����_���ɑΏۂ�I������i�m���͂܂��v�Z���Ȃ��j
			if(itemid < 0 && atn_rand()%(++count) == 0) {
				idx = j;
			}
		}

		if(idx >= 0 && (itemid > 0 || atn_rand()%10000 < per)) {	// ID�����̏ꍇ�Ɍ��肱���Ŋm���v�Z����
			// �h���b�v����
			if(sd->status.inventory[idx].equip)
				pc_unequipitem(sd,idx,0);
			pc_dropitem(sd,idx,1);
		}
	}
	return 0;
}

/*==========================================
 * script�pPC�X�e�[�^�X�ǂݏo��
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
	case SP_PSTR:
		val = sd->paramc[0];
		break;
	case SP_PAGI:
		val = sd->paramc[1];
		break;
	case SP_PVIT:
		val = sd->paramc[2];
		break;
	case SP_PINT:
		val = sd->paramc[3];
		break;
	case SP_PDEX:
		val = sd->paramc[4];
		break;
	case SP_PLUK:
		val = sd->paramc[5];
		break;
	// �O���[�o���ϐ��ۑ��^�C�v
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
	// �A�J�E���g�ϐ��ۑ��^�C�v
	case SP_DEPOSIT:
		val = sd->deposit;
		break;
	}

	return val;
}

/*==========================================
 * script�pPC�X�e�[�^�X�ݒ�
 *------------------------------------------
 */
int pc_setparam(struct map_session_data *sd,int type,int val)
{
	nullpo_retr(0, sd);

	switch(type) {
	case SP_BASELEVEL:
		if(val > sd->status.base_level) {
			int i;
			for(i = 1; i <= (val - sd->status.base_level); i++) {
				sd->status.status_point += stpoint_table[sd->status.base_level+i-1];
				sd->status.tstatus_point += tstpoint_table[sd->status.base_level+i-1];
			}
		}
		sd->status.base_level = val;
		sd->status.base_exp = 0;
		clif_updatestatus(sd, SP_BASELEVEL);
		clif_updatestatus(sd, SP_NEXTBASEEXP);
		clif_updatestatus(sd, SP_STATUSPOINT);
		clif_updatestatus(sd, SP_TSTATUSPOINT);
		clif_updatestatus(sd, SP_BASEEXP);
		status_calc_pc(sd, 0);
		pc_heal(sd, sd->status.max_hp, sd->status.max_sp,0,0);
		break;
	case SP_JOBLEVEL:
		if(val > 0) {
			if(val >= sd->status.job_level) {
				int up_level = job_db[sd->s_class.job].max_joblv[sd->s_class.upper];
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
			// MAX_ZENY �ȉ��Ȃ���
			sd->status.zeny = val;
		} else {
			if(sd->status.zeny > val) {
				// Zeny ���������Ă���Ȃ���
				sd->status.zeny = val;
			} else if(sd->status.zeny <= MAX_ZENY) {
				// Zeny ���������Ă��āA���݂̒l��MAX_ZENY �ȉ��Ȃ�MAX_ZENY
				sd->status.zeny = MAX_ZENY;
			} else {
				// Zeny ���������Ă��āA���݂̒l��MAX_ZENY ��艺�Ȃ瑝�����𖳎�
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

	// param����updatestatus�o���Ȃ�����
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

	// �O���[�o���ϐ��ۑ��^�C�v
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
	// �A�J�E���g�ϐ��ۑ��^�C�v
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
 *
 *------------------------------------------
 */
static int pc_checkoverap(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	if(sd->status.ap == sd->status.max_ap)
		return 1;
	if(sd->status.ap > sd->status.max_ap) {
		sd->status.ap = sd->status.max_ap;
		clif_updatestatus(sd,SP_AP);
		return 2;
	}

	return 0;
}

/*==========================================
 * HP/SP��
 * flag 0:�G�t�F�N�g���� 1:�G�t�F�N�g�L��
 *------------------------------------------
 */
int pc_heal(struct map_session_data *sd,int hp,int sp,int ap,int flag)
{
	nullpo_retr(0, sd);

	if(pc_checkoverhp(sd) && hp > 0)
		hp = 0;

	if(pc_checkoversp(sd) && sp > 0)
		sp = 0;

	if(pc_checkoverap(sd) && ap > 0)
		ap = 0;

	// �o�[�T�[�N���͉񕜂����Ȃ�
	if(sd->sc.data[SC_BERSERK].timer != -1) {
		if(hp > 0)
			hp = 0;
	}

	if(hp+sd->status.hp > sd->status.max_hp)
		hp = sd->status.max_hp - sd->status.hp;
	if(sp+sd->status.sp > sd->status.max_sp)
		sp = sd->status.max_sp - sd->status.sp;
	if(ap+sd->status.ap > sd->status.max_ap)
		ap = sd->status.max_ap - sd->status.ap;
	sd->status.hp += hp;
	if(sd->status.hp <= 0) {
		sd->status.hp = 0;
		pc_damage(NULL,sd,1);
		hp = 0;
	}
	sd->status.sp += sp;
	if(sd->status.sp <= 0)
		sd->status.sp = 0;
	sd->status.ap += ap;
	if(sd->status.ap <= 0)
		sd->status.ap = 0;
	if(hp) {
		if(hp > 0 && flag&1)
			clif_heal(sd->fd,SP_HP,hp);
		clif_updatestatus(sd,SP_HP);
		if(sd->status.party_id > 0 && party_search(sd->status.party_id))
			clif_party_hp(sd);
	}
	if(sp) {
		if(sp > 0 && flag&1)
			clif_heal(sd->fd,SP_SP,sp);
		clif_updatestatus(sd,SP_SP);
	}
	if(ap) {
		if(ap > 0 && flag&1)
			clif_heal(sd->fd,SP_AP,ap);
		clif_updatestatus(sd,SP_AP);
	}

	return hp + sp + ap;
}

/*==========================================
 * �A�C�e���ɂ��HP/SP��
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
		if(sd->sc.data[SC_VITALITYACTIVATION].timer != -1)	// �o�C�^���e�B�A�N�e�B�x�[�V����
			hp = hp * 150 / 100;
		if(sd->sc.data[SC_CRITICALWOUND].timer != -1)
			hp = hp * (100 - sd->sc.data[SC_CRITICALWOUND].val2) / 100;
		if(sd->sc.data[SC_DEATHHURT].timer != -1)	// �f�X�n�[�g
			hp = hp * (100 - sd->sc.data[SC_DEATHHURT].val2) / 100;
#ifndef PRE_RENEWAL
		if(sd->sc.data[SC_FUSION].timer != -1)	// ���z�ƌ��Ɛ��̗Z��
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
		if(sd->sc.data[SC_VITALITYACTIVATION].timer != -1)		// �o�C�^���e�B�A�N�e�B�x�[�V����
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
 * �䗦�ɂ��HP/SP��
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
 * �E�ύX
 * ����	job �E�� PC_JOB_NV <= job < PC_JOB_MAX
 *      upper �ʏ� 0, �]�� 1, �{�q 2, ���̂܂� -1
 *------------------------------------------
 */
int pc_jobchange(struct map_session_data *sd,int job, int upper)
{
	int i;
	int b_class = 0;
	int joblv_nochange = 0;
	int prev_classlevel;
	int skill_point;

	nullpo_retr(0, sd);

	if(job >= PC_JOB_MAX)
		return 1;

	// �h�����n�E�ƂƑ��E�Ƃ͑��݂ɓ]�E�s��
	if((pc_isdoram(sd) && (job != PC_JOB_SUM && job != PC_JOB_SH)) || (!pc_isdoram(sd) && (job == PC_JOB_SUM || job == PC_JOB_SH)))
		return 1;

	// �]���E�{�q�Ȃ��̐E��
	if(job >= PC_JOB_TK && job <= PC_JOB_DA)
		upper = PC_UPPER_NORMAL;

	// �X�p�m�r�A�g���X�p�m�r�œ]���w��̏ꍇ
	if((job == PC_JOB_SNV || job == PC_JOB_ESNV) && upper == PC_UPPER_HIGH)
		upper = PC_UPPER_NORMAL;

	// �{�q<->�]���O�̏ꍇJOB1�ɂ��Ȃ�
	if(sd->s_class.job == job &&
	  ((sd->s_class.upper == PC_UPPER_NORMAL && upper == PC_UPPER_BABY) ||
	  (sd->s_class.upper == PC_UPPER_BABY && upper == PC_UPPER_NORMAL))) {
		joblv_nochange = 1;
	}

	if(battle_config.enable_upper_class == 0) {	// conf�Ŗ����ɂȂ��Ă�����upper=0
		upper = PC_UPPER_NORMAL;
	}

	if(upper < 0)		// ���ݓ]�����ǂ����𔻒f����
		upper = sd->s_class.upper;

	b_class = pc_calc_class_job(job, upper);

	if((sd->sex == SEX_FEMALE && job == PC_JOB_BA) || (sd->sex == SEX_MALE && job == PC_JOB_DC) ||
	   (sd->sex == SEX_FEMALE && job == PC_JOB_MI) || (sd->sex == SEX_MALE && job == PC_JOB_WA) ||
	   (sd->sex == SEX_FEMALE && job == PC_JOB_TRB) || (sd->sex == SEX_MALE && job == PC_JOB_TRV) ||
	   sd->status.class_ == b_class)	// SEX_FEMALE�̓o�[�h�ɂȂ�Ȃ��ASEX_MALE�̓_���T�[�ɂȂ�Ȃ�
		return 1;

	if((sd->sex == SEX_FEMALE && job == PC_JOB_KG) || (sd->sex == SEX_MALE && job == PC_JOB_OB) ||
	   (sd->sex == SEX_FEMALE && job == PC_JOB_SK) || (sd->sex == SEX_MALE && job == PC_JOB_SN) ||
	   sd->status.class_ == b_class)	// SEX_FEMALE�͉e�T�ɂȂ�Ȃ��ASEX_MALE�͞O�ɂȂ�Ȃ�
		return 1;

	// �O�E�Ƃ̒i�K��ێ�
	prev_classlevel = pc_get_classlevel(sd);

	sd->status.class_ = sd->view_class = b_class;
	sd->status.style = 0;

	// ���E�Ƃ��Đݒ�
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
			pc_unequipitem(sd,sd->equip_index[i],1);	// �����O��
	}
	status_calc_pc_stop_end(&sd->bl);

	clif_changelook(&sd->bl,LOOK_BASE,sd->view_class);
	pc_changebodystyle(sd);

	if(sd->status.manner < 0)
		clif_changestatus(&sd->bl,SP_MANNER,sd->status.manner);

	// �O�E�Ƃ���i�K���i��ł���ꍇ
	if(pc_get_classlevel(sd) > prev_classlevel) {
		skill_point = pc_calc_skillpoint(sd);	// �g�p�ς݃X�L���|�C���g���擾
		switch(prev_classlevel) {
		case 0:
			pc_setglobalreg(sd,"PC_USESKILLPOINT_0TH",sd->status.skill_point + skill_point);
			break;
		case 1:
			pc_setglobalreg(sd,"PC_USESKILLPOINT_1ST",sd->status.skill_point + skill_point);
			break;
		case 2:
			pc_setglobalreg(sd,"PC_USESKILLPOINT_2ND",sd->status.skill_point + skill_point);
			break;
		case 3:
			pc_setglobalreg(sd,"PC_USESKILLPOINT_3RD",sd->status.skill_point + skill_point);
			break;
		}
		// 4���E�ɓ]�E���͓����X�e�[�^�X�|�C���g��t�^
		if(pc_get_classlevel(sd) == 4) {
			sd->status.tstatus_point += battle_config.fourth_jobchange_tstpoint;
			clif_updatestatus(sd,SP_TSTATUSPOINT);
		}
	}

	// �O�E�Ƃ���i�K���߂��Ă���ꍇ
	if(pc_get_classlevel(sd) < prev_classlevel) {
		switch(pc_get_classlevel(sd)) {
		case 0:
			pc_setglobalreg(sd,"PC_USESKILLPOINT_0TH",0);
			// fall through
		case 1:
			pc_setglobalreg(sd,"PC_USESKILLPOINT_1ST",0);
			// fall through
		case 2:
			pc_setglobalreg(sd,"PC_USESKILLPOINT_2ND",0);
			// fall through
		case 3:
			pc_setglobalreg(sd,"PC_USESKILLPOINT_3RD",0);
			break;
		}
	}

	status_calc_pc(sd,0);
	pc_checkallowskill(sd);
	pc_equiplookall(sd);
	clif_equiplist(sd);
	clif_skillinfoblock(sd);

	achieve_update_content(sd, ACH_JOBCHANGE, sd->status.class_, 1);

	return 0;
}

/*==========================================
 * �S�����i�̌����ڕύX
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
 * �����ڕύX
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
		if(sd->sc.data[SC_BUNSINJYUTSU].timer != -1)	// �e���g���͋����I��0
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
		pc_changebodystyle(sd);
		return 0;
	}
	clif_changelook(&sd->bl,type,val);

	if(type == LOOK_CLOTHES_COLOR && sd->status.clothes_color == 0)
		clif_changelook(&sd->bl,LOOK_BASE,sd->view_class);

	return 0;
}

/*==========================================
 * �t���i(��,�y�R,�J�[�g)�ݒ�
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

		// �I�v�V�����l����J�[�g�^�C�v��ϊ�����
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
 * �J�[�g�ݒ�
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
		// �Â��N���C�A���g�ł̓I�v�V�����l�ŊǗ�
		{ OPTION_NOTHING,  0 },
		{ OPTION_PUSHCART,  0 },
		{ OPTION_PUSHCART2, 40 },
		{ OPTION_PUSHCART3, 65 },
		{ OPTION_PUSHCART4, 80 },
		{ OPTION_PUSHCART5, 90 },
#else
		// �V�����N���C�A���g�ł͏�Ԉُ��val1�ŊǗ�
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

	if(pc_checkskill(sd,MC_PUSHCART) > 0) {	// �v�b�V���J�[�g�X�L������
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
 * ��ݒ�
 *------------------------------------------
 */
int pc_setfalcon(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	if(pc_checkskill(sd,HT_FALCON) > 0) {	// �t�@���R���}�X�^���[�X�L������
		pc_setoption(sd,OPTION_FALCON);
	}
	return 0;
}

/*==========================================
 * �y�R�y�R�ݒ�
 *------------------------------------------
 */
int pc_setriding(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	if(pc_checkskill(sd,KN_RIDING) > 0) { // ���C�f�B���O�X�L������
		pc_setoption(sd,OPTION_PECO);
	}
	return 0;
}

/*==========================================
 * �h���S���ݒ�
 *------------------------------------------
 */
int pc_setdragon(struct map_session_data *sd, int type)
{
	nullpo_retr(0, sd);

	if(pc_checkskill(sd,RK_DRAGONTRAINING) > 0) { // �h���S���g���[�j���O�X�L������
		if(type > 0 && type < 5)
			pc_setoption(sd,OPTION_DRAGON2 << (type-1));
		else
			pc_setoption(sd,OPTION_DRAGON);
	}
	return 0;
}

/*==========================================
 * �����M�A�ݒ�
 *------------------------------------------
 */
int pc_setgear(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	if(pc_checkskill(sd,NC_MADOLICENCE) > 0) { // �����M�A���C�Z���X�X�L������
		pc_setoption(sd,OPTION_MADOGEAR);
	}
	return 0;
}

/*==========================================
 * GM�̃A�C�e���h���b�v�۔���
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
 * script�p�ϐ��̒l��ǂ�
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
 * script�p�ϐ��̒l��ݒ�
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
 * script�p������ϐ��̒l��ǂ�
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
 * script�p������ϐ��̒l��ݒ�
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

	// str�������regstr�z���ɑ��݂��Ă���\��������̂�
	// realloc�����ɐ��str���R�s�[���Ă���free����
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
 * script�p�O���[�o���ϐ��̒l��ǂ�
 *------------------------------------------
 */
int pc_readregistry(struct map_session_data *sd, const char *reg, int type)
{
	int i, num = 0;
	struct global_reg *gr = NULL;

	nullpo_retr(0, sd);

	switch(type) {
		case 3:
			// �O���[�o���ϐ�
			gr  = sd->save_reg.global;
			num = sd->save_reg.global_num;
			break;
		case 2:
			// #�ϐ�
			gr  = sd->save_reg.account;
			num = sd->save_reg.account_num;
			break;
		case 1:
			// ##�ϐ�
			gr  = sd->save_reg.account2;
			num = sd->save_reg.account2_num;
			break;
		default:
			return 0;
	}

	for(i = 0; i < num; i++) {
		if(strcasecmp(gr[i].str, reg) == 0)
			return gr[i].value;
	}
	return 0;
}

/*==========================================
 * �O���[�o���ϐ���dirty��Ԃɂ���
 *------------------------------------------
 */
static int pc_setreg_dirty(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	sd->state.reg_dirty = 1;

	return 0;
}

/*==========================================
 * script�p�O���[�o���ϐ��̒l��ݒ�
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
			// �O���[�o���ϐ�
			gr   = sd->save_reg.global;
			num  = &sd->save_reg.global_num;
			max  = GLOBAL_REG_NUM;
			func = pc_setreg_dirty;
			break;
		case 2:
			// #�ϐ�
			gr   = sd->save_reg.account;
			num  = &sd->save_reg.account_num;
			max  = ACCOUNT_REG_NUM;
			func = intif_saveaccountreg;
			break;
		case 1:
			// ##�ϐ�
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
			if(strcasecmp(gr[i].str, reg) == 0) {
				gr[i] = gr[(*num) - 1];
				(*num)--;
				func(sd);
				break;
			}
		}
		return 0;
	}
	for(i = 0; i < *num; i++) {
		if(strcasecmp(gr[i].str, reg) == 0) {
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
 * �C�x���g�^�C�}�[����
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
 * �C�x���g�^�C�}�[�ǉ�
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
 * �C�x���g�^�C�}�[�폜
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
 * �C�x���g�^�C�}�[�J�E���g�l�ǉ�
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
 * �C�x���g�^�C�}�[�c�莞�Ԏ擾
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
 * �C�x���g�^�C�}�[�S�폜
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
 * �R�X�`���[���𔽉f����
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
 * �X�^�C���𔽉f����
 *------------------------------------------
 */
void pc_changebodystyle(struct map_session_data *sd)
{
	int style = 0;

	nullpo_retv(sd);

#if PACKETVER < 20231220
	style = sd->status.style;
#else
	if(sd->status.style > 0) {
		switch(sd->s_class.job) {
		case PC_JOB_RK: style = PC_CLASS_RK_2ND; break;
		case PC_JOB_WL: style = PC_CLASS_WL_2ND; break;
		case PC_JOB_RA: style = PC_CLASS_RA_2ND; break;
		case PC_JOB_AB: style = PC_CLASS_AB_2ND; break;
		case PC_JOB_NC: style = PC_CLASS_NC_2ND; break;
		case PC_JOB_GC: style = PC_CLASS_GC_2ND; break;
		case PC_JOB_LG: style = PC_CLASS_LG_2ND; break;
		case PC_JOB_SO: style = PC_CLASS_SO_2ND; break;
		case PC_JOB_MI: style = PC_CLASS_MI_2ND; break;
		case PC_JOB_WA: style = PC_CLASS_WA_2ND; break;
		case PC_JOB_SR: style = PC_CLASS_SR_2ND; break;
		case PC_JOB_GN: style = PC_CLASS_GN_2ND; break;
		case PC_JOB_SC: style = PC_CLASS_SC_2ND; break;
		default:
			style = sd->status.class_;
			break;
		}
	}
	else
		style = sd->status.class_;
#endif
	clif_changelook(&sd->bl,LOOK_BODY2,style);
}

/*==========================================
 * �A�C�e���𑕔�����
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
			clif_msgstringtable(sd, 0x6ed);	// �A�C�e���𑕔��ł��郌�x���ɒB���Ă��܂���B
		return;
	}
	if(pos == LOC_RLACCESSORY) {	// �A�N�Z�T���p��O����
		int epor = LOC_NOTHING;
		if(sd->equip_index[EQUIP_INDEX_LACCESSORY] >= 0)
			epor |= sd->status.inventory[sd->equip_index[EQUIP_INDEX_LACCESSORY]].equip;
		if(sd->equip_index[EQUIP_INDEX_RACCESSORY] >= 0)
			epor |= sd->status.inventory[sd->equip_index[EQUIP_INDEX_RACCESSORY]].equip;
		epor &= LOC_RLACCESSORY;
		pos = (epor == LOC_RACCESSORY) ? LOC_LACCESSORY : LOC_RACCESSORY;
	}

	// �񓁗�����
	if( pos == LOC_RLARM && 	// �ꉞ�A�����v���ӏ����񓁗����킩�`�F�b�N����
	    id->equip == LOC_RARM &&	// �P�蕐��
	    (pc_checkskill(sd, AS_LEFT) > 0 || sd->s_class.job == PC_JOB_AS || sd->s_class.job == PC_JOB_GC ||
	     pc_checkskill(sd, KO_LEFT) > 0 || sd->s_class.job == PC_JOB_KG || sd->s_class.job == PC_JOB_OB) ) // ����C�B�L
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
	// �|���
	if(pos == LOC_ARROW) {
		clif_arrowequip(sd,n);
		clif_arrow_fail(sd,3);	// �����ł��܂���
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

	pc_checkallowskill(sd);	// �����i�ŃX�L������������邩�`�F�b�N
	status_calc_pc(sd,0);
#if PACKETVER > 20080102
	clif_skillinfoblock(sd);
#endif
	if(sd->sc.data[SC_SIGNUMCRUCIS].timer != -1 && !battle_check_undead(RCT_DEMIHUMAN,sd->def_ele))
		status_change_end(&sd->bl,SC_SIGNUMCRUCIS,-1);

	return;
}

/*==========================================
 * �������������O��
 *------------------------------------------
 */
void pc_unequipitem(struct map_session_data *sd, int n, int type)
{
	int hp = 0, sp = 0;

	nullpo_retv(sd);

	// �L���X�e�B���O�� �X�g���b�v�Ɣj�󎞂�������Ȃ��̂œ���������
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

				// �������O����HP/SP�̃y�i���e�B����
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
		sd->status.inventory[n].id = ++sd->inventory_sortkey;	// �C���x���g���ɐV�K�o�^
		sd->status.inventory[n].equip = LOC_NOTHING;
		if(!type)
			pc_checkallowskill(sd);
		if(sd->weapontype1 == WT_FIST && sd->weapontype2 == WT_FIST)
			status_enchant_elemental_end(&sd->bl,SC_SEVENWIND);  // �g�������ȊO�͕��펝�������ő����t�^����
	} else {
		clif_unequipitemack(sd,n,0,0);
	}
	if(!type) {
		status_calc_pc(sd,0);
		if(sd->sc.data[SC_SIGNUMCRUCIS].timer != -1 && !battle_check_undead(RCT_DEMIHUMAN,sd->def_ele))
			status_change_end(&sd->bl,SC_SIGNUMCRUCIS,-1);
	}

	if(hp) {
		if(sd->status.hp > hp) {
			pc_heal(sd,-hp,0,0,0);
		} else {
			if(!battle_config.death_by_unrig_penalty) {
				// ��UHP��0�ɂȂ�A������1�ɉ񕜂���
				sd->status.hp = 0;
				clif_updatestatus(sd,SP_HP);
				pc_heal(sd,1,0,0,0);
			} else {
				pc_heal(sd,-sd->status.hp,0,0,0);
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
 * �������Ă������Ԃ�
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

			for(j=0; j<4; j++) {	// �J�[�h
				if(sd->status.inventory[idx].card[j] == id)
					n++;
			}
		}
	}

	return n;
}

/*==========================================
 * �A�C�e���\�[�g
 *------------------------------------------
 */
static int pc_comp_item(const void *_i1, const void *_i2)
{
	struct item *i1 = (struct item *)_i1;
	struct item *i2 = (struct item *)_i2;

	// id��0�Ȃ疖���ɏW�߂�
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
 * �A�C�e����index�ԍ����l�߂���
 * �����i�̑����\�`�F�b�N���s�Ȃ�
 *------------------------------------------
 */
int pc_checkitem(struct map_session_data *sd)
{
	int i,itemid,calc_flag = 0;

	nullpo_retr(0, sd);

	if(battle_config.item_check) {
		// �C�x���g�����̕s���`�F�b�N
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
		// �J�[�g���̕s���`�F�b�N
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

	// �ύX����������id���Ƀ\�[�g����
	if(sd->state.inventory_dirty) {
		if(sd->inventory_timer) {
			// �g�p�����̂���A�C�e���Ȃ�ꎞ�I��key��id�ɕς��Ă���
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
			// �g�p�����̂���A�C�e���Ȃ�id���T�[�`���ăC���f�b�N�X���Đݒ�
			struct linkdb_node *node = sd->inventory_timer;
			while(node) {
				for(i = 0; i < MAX_INVENTORY; i++) {
					if(sd->status.inventory[i].id == PTR2UINT(node->key)) {
						node->key = INT2PTR(i);
						break;
					}
				}
				if(i >= MAX_INVENTORY) {
					// ���̂��C���f�b�N�X�𕜌��ł��Ȃ������̂Ń\�P�b�g�ؒf����
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
					// �ʒu���ς�����̂Ńf�[�^�x�[�X���Đݒ�
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

	// �����ʒu�`�F�b�N
	for(i = 0; i < MAX_INVENTORY; i++)
	{
		if(sd->status.inventory[i].nameid == 0)
			continue;
		if(sd->status.inventory[i].equip & ~pc_equippoint(sd,i)) {
			sd->status.inventory[i].equip = LOC_NOTHING;
			calc_flag = 1;
		}
		// ���������`�F�b�N
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
 * PVP���ʌv�Z�p(foreachinarea)
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
 * PVP���ʌv�Z
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
 * PVP���ʌv�Z(timer)
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
 * sd�͌������Ă��邩(�����̏ꍇ�͑�����char_id��Ԃ�)
 *------------------------------------------
 */
int pc_ismarried(struct map_session_data *sd)
{
	nullpo_retr(-1, sd);

	return (sd->status.partner_id > 0)? sd->status.partner_id: 0;
}

/*==========================================
 * sd��dstsd�ƌ���(dstsd��sd�̌��������������ɍs��)
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
 * sd��PC�Ɨ{�q���g
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
 * sd��papa mama�Ɨ{�q���g
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

		// �e��WE_BABY���擾���邽�߂ɃX�L���c���[�Čv�Z
		status_calc_pc(papa,0);
		status_calc_pc(mama,0);
		return 1;
	}
	return 0;
}

/*==========================================
 * �{�q���g�����̃`�F�b�N
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

	// �{�q�`�F�b�N
	if(dstsd->s_class.upper != PC_UPPER_NORMAL || (dstsd->s_class.job >= PC_JOB_TK && dstsd->s_class.job <= PC_JOB_DA))
		return 0;
	// �p�[�e�B�[�����}�b�v�ɂR�l
	if(party_check_same_map_member_count(dstsd) != 2)
		return 0;

	if(flag) {	// �{�q���j���[����̏ꍇ�͏ڍׂɃ`�F�b�N
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
 * �{�q�v���̕ԓ�
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
 * �{�q��̏���
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

	// %s����̗v�]�ɂ��A�{�q�֌W���j������܂���
	snprintf(output, sizeof(output), msg_txt(174), sd->status.name);

	// sd�̉Ƒ����𒊏o
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

	// ��̏����̎��s�A������Ȃ����char�I�Ɉ˗�
	if(baby) {		// �q���̗���
		baby->status.parent_id[0] = 0;
		baby->status.parent_id[1] = 0;
		pc_jobchange(baby,baby->s_class.job,0);
		clif_disp_onlyself(baby->fd, output);
		chrif_save(baby,0);
	} else if(b_id > 0) {
		chrif_req_break_adoption(b_id, sd->status.name);
		chrif_searchcharid(b_id);
	}

	if(p1) {		// �e�̗���
		p1->status.baby_id = 0;
		status_calc_pc(p1,0);	// WE_BABY��j�����邽�߂ɃX�L���c���[�Čv�Z
		clif_disp_onlyself(p1->fd, output);
		chrif_save(p1,0);
	} else if(p1_id > 0) {
		chrif_req_break_adoption(p1_id, sd->status.name);
		chrif_searchcharid(p1_id);
	}

	if(p2) {		// ������l�̐e�̗���
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
 * sd������(�����sd->status.partner_id�Ɉ˂�)
 * ����������ɗ����E�����w�֎������D
 *------------------------------------------
 */
int pc_divorce(struct map_session_data *sd)
{
	struct map_session_data *p_sd = NULL;
	int i;

	nullpo_retr(-1, sd);

	if(!pc_ismarried(sd))
		return -1;

	// �����̗�������
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
		// ������������Ȃ��ꍇ��char�I�ɏ������˗�����
		chrif_reqdivorce(sd->status.partner_id);
		chrif_searchcharid(sd->status.partner_id);	// ���O�f�[�^�Ăяo��
	}

	// ����
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
 * sd�̑�����map_session_data��Ԃ�
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
 * �����j��
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
			if(sd->equip_index[EQUIP_INDEX_LARM] >= 0 && itemdb_isweapon(sd->inventory_data[sd->equip_index[EQUIP_INDEX_LARM]]->nameid))	// ���肪����Ȃ�
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
 * �����j�� ����
 *------------------------------------------
 */
int pc_break_equip2(struct map_session_data *sd,int where)
{
	int idx;

	nullpo_retr(-1, sd);

	switch(where) {
		case EQUIP_INDEX_LACCESSORY: // �A�N�Z�T����
		case EQUIP_INDEX_RACCESSORY:	// �A�N�Z�T���E
		case EQUIP_INDEX_SHOES: // �C
		case EQUIP_INDEX_ROBE:	// ��
			break;
		case EQUIP_INDEX_HEAD:	// �����i
		case EQUIP_INDEX_HEAD3:	// �����i
		case EQUIP_INDEX_HEAD2:	// ����i
			if(sd->unbreakable_equip & LOC_HEAD2)
				return 0;
			if(sd->sc.data[SC_CP_HELM].timer != -1)
				return 0;
			break;
		case EQUIP_INDEX_BODY:	// ��
			if(sd->unbreakable_equip & LOC_BODY)
				return 0;
			if(sd->sc.data[SC_CP_ARMOR].timer != -1)
				return 0;
			break;
		case EQUIP_INDEX_LARM:	// ����
			if(sd->equip_index[EQUIP_INDEX_LARM] >= 0 && itemdb_isweapon(sd->inventory_data[sd->equip_index[EQUIP_INDEX_LARM]]->nameid)) {	// ����
				if(sd->unbreakable_equip & LOC_RARM)
					return 0;
				if(sd->sc.data[SC_CP_WEAPON].timer != -1)
					return 0;
			} else {	// ��
				if(sd->unbreakable_equip & LOC_LARM)
					return 0;
				if(sd->sc.data[SC_CP_SHIELD].timer != -1)
					return 0;
			}
			break;
		case EQUIP_INDEX_RARM:	// �E��
			if(sd->unbreakable_equip & LOC_RARM)
				return 0;
			if(sd->sc.data[SC_CP_WEAPON].timer != -1)
				return 0;
			break;
		case EQUIP_INDEX_ARROW: // ��
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
 * �����A�b�v�O���[�h
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

	if((!itemdb_isweapon(item_data->nameid) && !itemdb_isarmor(item_data->nameid)) ||	// �����i����Ȃ�
		sd->status.inventory[idx].identify == 0)	// ���Ӓ�
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
 * ���R�񕜕�
 *------------------------------------------
 */
static unsigned int natural_heal_tick, natural_heal_prev_tick;
static int natural_heal_diff_tick;

/*==========================================
 * HP�񕜃C���^�[�o���v�Z
 *------------------------------------------
 */
static int pc_hpheal(struct map_session_data *sd)
{
	int a;

	nullpo_retr(0, sd);

	// ���R�񕜒�~
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
 * SP�񕜃C���^�[�o���v�Z
 *------------------------------------------
 */
static int pc_spheal(struct map_session_data *sd)
{
	int a;

	nullpo_retr(0, sd);

	// ���R�񕜒�~
	if(sd->sp_recov_stop)
		return 0;

	a = natural_heal_diff_tick;
	if(pc_issit(sd))
		a += a;
	if(sd->sc.data[SC_MAGNIFICAT].timer != -1)	// �}�O�j�t�B�J�[�g
		a += a;
	else if(sd->sc.data[SC_SHIELDSPELL_MDEF].timer != -1)	// �V�[���h�X�y��
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
 * HP�񕜏���
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
		if(sd->sc.data[SC_TENSIONRELAX].timer != -1) {	// �e���V���������b�N�X
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
 * SP�񕜏���
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
		sd->regen.sp += inc_num / 2;	// �����g����Ԃ�SP���R�񕜑��x��50%
#endif
	if(sd->sc.data[SC_DANCING].timer != -1) {		// �_���X��Ԃł�SP���񕜂��Ȃ�
		sd->regen.sp = 0;
		if(pc_checkskill(sd,WM_LESSON) == 0) {		// ���b�X���K���ς݂Ȃ烌�b�X�����ʂ̂ݗL��
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
 * �����ɂ��HP���R��
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
 * �����ɂ��SP���R��
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
 * ���炩�ȋx���ɂ��HP���R��
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
 * �y�����x���ɂ��SP���R��
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
			if(atn_rand()%10000 < battle_config.sg_angel_rate) {	// ���z�ƌ��Ɛ��̓V�g
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
 * HP/SP�̎��R�����y�i���e�B
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
			pc_heal(sd,-hp,0,0,0);
		} else {
			sd->status.hp = 0;
			clif_updatestatus(sd,SP_HP);
		}
	}
	if(sp) {
		if(sd->status.sp > sp) {
			pc_heal(sd,0,-sp,0,0);
		} else {
			sd->status.sp = 0;
			clif_updatestatus(sd,SP_SP);
		}
	}

	return 0;
}

/*==========================================
 * HP/SP ���R�� �e�N���C�A���g
 *------------------------------------------
 */
static int pc_natural_heal_sub(struct map_session_data *sd,va_list ap)
{
	nullpo_retr(0, sd);

	if( (battle_config.natural_heal_weight_rate > 100 || sd->weight*100/sd->max_weight < battle_config.natural_heal_weight_rate) &&
	    !unit_isdead(&sd->bl) &&
	    !pc_ishiding(sd) &&
	    sd->sc.data[SC_POISON].timer == -1 &&	// �ŏ�Ԃł�HP���񕜂��Ȃ�
	    sd->sc.data[SC_BLEED].timer == -1 &&	// �o����Ԃł�HP���񕜂��Ȃ�
	    sd->sc.data[SC_TRICKDEAD].timer == -1 &&	// ���񂾂ӂ��Ԃł�HP���񕜂��Ȃ�
	    sd->sc.data[SC_GOSPEL].timer == -1 &&	// �S�X�y����Ԃł�HP���񕜂��Ȃ�
	    sd->sc.data[SC_BERSERK].timer == -1 &&	// �o�[�T�[�N��Ԃł�HP���񕜂��Ȃ�
	    sd->sc.data[SC_MAGICMUSHROOM].timer == -1 &&	// �}�W�b�N�}�b�V�����[����Ԃł�HP���񕜂��Ȃ�
	    sd->sc.data[SC_PYREXIA].timer == -1 &&	// �p�C���b�N�V�A��Ԃł�HP���񕜂��Ȃ�
	    sd->sc.data[SC_LEECHEND].timer == -1 &&	// ���[�`�G���h��Ԃł�HP���񕜂��Ȃ�
	    sd->sc.data[SC_INSPIRATION].timer == -1 &&	// �C���X�s���[�V������Ԃ�HP���񕜂��Ȃ�
	    sd->sc.data[SC_RAISINGDRAGON].timer == -1 &&	// �������V��Ԃ�HP���񕜂��Ȃ�
	    sd->sc.data[SC_SATURDAY_NIGHT_FEVER].timer == -1 &&	// �t���C�f�[�i�C�g�t�B�[�o�[��Ԃł�HP���񕜂��Ȃ�
	    sd->sc.data[SC_DIAMONDDUST].timer == -1 &&	//�_�C�������h�_�X�g��Ԃł�HP���񕜂��Ȃ�
	    sd->sc.data[SC_NATURAL_HEAL_STOP].timer == -1 )
	{
		pc_natural_heal_hp(sd);
		if( sd->sc.data[SC_MAXIMIZEPOWER].timer == -1 &&	// �}�L�V�}�C�Y�p���[��Ԃł�SP���񕜂��Ȃ�
		    sd->sc.data[SC_EXTREMITYFIST].timer == -1 &&	// ���C����Ԃł�SP���񕜂��Ȃ�
		    sd->sc.data[SC_BERSERK].timer == -1 &&		// �o�[�T�[�N��Ԃł�SP���񕜂��Ȃ�
		    sd->sc.data[SC_VITALITYACTIVATION].timer == -1 &&	// �o�C�^���e�B�A�N�e�B�x�[�V������Ԃł�SP���񕜂��Ȃ�
		    sd->sc.data[SC_WEAPONBLOCKING].timer == -1 &&		// �E�F�|���u���b�L���O��Ԃł�SP���񕜂��Ȃ�
		    sd->sc.data[SC_TOXIN].timer == -1 &&	// �g�L�V����Ԃł�SP���񕜂��Ȃ�
		    sd->sc.data[SC_OBLIVIONCURSE].timer == -1 &&		// �I�u���r�I���J�[�X��Ԃł�SP���񕜂��Ȃ�
		    sd->sc.data[SC_ELECTRICSHOCKER].timer == -1 &&	// �G���N�g���b�N�V���b�J�[��Ԃł�SP���񕜂��Ȃ�
		    sd->sc.data[SC_CAMOUFLAGE].timer == -1 &&		// �J���t���[�W����Ԃł�SP���񕜂��Ȃ�
		    sd->sc.data[SC_MAGNETICFIELD].timer == -1 &&	// �}�O�l�e�B�b�N�t�B�[���h��Ԃł�SP���񕜂��Ȃ�
		    sd->sc.data[SC_STEALTHFIELD_MASTER].timer == -1 &&	// �X�e���X�t�B�[���h(�g�p��)��SP���񕜂��Ȃ�
		    sd->sc.data[SC__REPRODUCE].timer == -1 &&	// ���v���f���[�X��Ԃ�SP���񕜂��Ȃ�
		    sd->sc.data[SC__SHADOWFORM].timer == -1 &&	// �V���h�E�t�H�[����Ԃ�SP���񕜂��Ȃ�
		    sd->sc.data[SC__INVISIBILITY].timer == -1 &&	// �C���r�W�r���e�B��Ԃ�SP���񕜂��Ȃ�
		    sd->sc.data[SC_SIRCLEOFNATURE].timer == -1 &&	// �z���鎩�R�̉���Ԃ�SP���񕜂��Ȃ�
		    sd->sc.data[SC_SUMMON_ELEM].timer == -1 &&	// �T�����G�������^����Ԃ�SP���񕜂��Ȃ�
#ifndef PRE_RENEWAL
		    sd->sc.data[SC_FUSION].timer == -1 &&	// ���z�ƌ��Ɛ��̗Z����Ԃ�SP���񕜂��Ȃ�
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

	// ���炩�ȋx��
	if(pc_checkskill(sd,TK_HPTIME) > 0 && sd->state.taekwonrest && sd->sc.data[SC_POISON].timer == -1)
		pc_rest_heal_hp(sd);
	else
		sd->regen.resthptick = 0;

	// �y�����x��
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
 * HP/SP���R�� (interval timer�֐�)
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
 * �����Z�[�u �e�N���C�A���g
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
 * �����Z�[�u (timer�֐�)
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
	if(agit_flag == 1)	// GvG���̓C���^�[�o���𒷂���邱�ƂŃ��O���ɘa����
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
						dummy_gm_account = account_id;	// �_�~�[�p��GM�A�J�E���g��ݒ�
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
// ��������
//
/*==========================================
 * �ݒ�t�@�C���ǂݍ���
 * exp.txt �K�v�o���l
 * skill_tree.txt �e�E���̃X�L���c���[
 * attr_fix.txt �����C���e�[�u��
 *------------------------------------------
 */
int pc_readdb(void)
{
	int i,j,k,m,count;
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

	// �K�v�o���l�ǂݍ���
	filename = "db/exp.txt";
	memset(exp_table, 0, sizeof(exp_table));
	fp = fopen(filename, "r");
	if(fp == NULL) {
		printf("pc_readdb: open [%s] failed !\n", filename);
		return 1;
	}
	i = 0;
	while(fgets(line,1020,fp)) {
		atn_bignumber t[MAX_EXP_TABLE];
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0] == '/' && line[1] == '/')
			continue;
		if(sscanf(line, "%" BIGNUMSCANCODE ",%" BIGNUMSCANCODE ",%" BIGNUMSCANCODE ",%" BIGNUMSCANCODE ",%" BIGNUMSCANCODE ","
						"%" BIGNUMSCANCODE ",%" BIGNUMSCANCODE ",%" BIGNUMSCANCODE ",%" BIGNUMSCANCODE ",%" BIGNUMSCANCODE ","
						"%" BIGNUMSCANCODE ",%" BIGNUMSCANCODE ",%" BIGNUMSCANCODE ",%" BIGNUMSCANCODE ",%" BIGNUMSCANCODE ","
						"%" BIGNUMSCANCODE ",%" BIGNUMSCANCODE ",%" BIGNUMSCANCODE,
						&t[0],&t[1],&t[2],&t[3],&t[4],&t[5],&t[6],&t[7],&t[8],&t[9],&t[10],&t[11],&t[12],&t[13],&t[14],&t[15],&t[16],&t[17]
		) != MAX_EXP_TABLE)
			continue;
		for(j = 0; j < MAX_EXP_TABLE; j++) {
			exp_table[j][i]  = t[j];
		}
		i++;
		if(i >= MAX_LEVEL)
			break;
	}
	fclose(fp);
	printf("read %s done\n", filename);

	// �X�e�[�^�X�|�C���gDB
	filename = "db/pc_stpoint_db.txt";
	memset(stpoint_table, 0, sizeof(stpoint_table));
	fp = fopen(filename, "r");
	if(fp == NULL) {
		printf("pc_readdb: open [%s] failed !\n", filename);
		return 1;
	}
	i = 0;
	while(fgets(line,1020,fp)) {
		int stpoint,tstpoint;
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0] == '/' && line[1] == '/')
			continue;
		if(sscanf(line,"%d,%d",&stpoint,&tstpoint) != 2)
			continue;

		stpoint_table[i] = stpoint;
		tstpoint_table[i] = tstpoint;
		i++;
		if(i >= MAX_LEVEL)
			break;
	}
	fclose(fp);
	printf("read %s done\n", filename);

	// �X�L���c���[
	memset(skill_tree,0,sizeof(skill_tree));
	for(m = 0; m < sizeof(filename2)/sizeof(filename2[0]); m++) {
		int x,y;
		int lineno = 0;
		count = 0;
		fp = fopen(filename2[m], "r");
		if(fp == NULL) {
			printf("pc_readdb: open [%s] failed !\n", filename2[m]);
			break;
		}
		while(fgets(line,1020,fp)) {
			char *split[7+MAX_SKILL_NEED*2];
			int skillid;
			struct skill_tree_entry *st;

			lineno++;
			memset(split,0,sizeof(split));
			if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
				continue;
			if(line[0]=='/' && line[1]=='/')
				continue;
			for(j=0,p=line;j<7+MAX_SKILL_NEED*2 && p;j++) {
				split[j]=p;
				p=strchr(p,',');
				if(p) *p++=0;
			}

			i = atoi(split[0]);
			if(i < 0 || i >= PC_JOB_MAX)
				continue;

			if( strcmp(split[1],"clear") == 0 ) {
				memset(skill_tree[i],0,sizeof(skill_tree[0]));
				continue;
			}

			if( j < 7 ) {
				printf("skill_tree: invalid param count(%d) line %d\n", j, lineno);
				continue;
			}

			skillid = atoi(split[1]);
			if(skillid < 0 || skillid >= MAX_PCSKILL)
				continue;

			st = skill_tree[i];
			for(j=0; st[j].id && st[j].id != skillid; j++);

			if(j >= MAX_SKILL_TREE-1) {
				// �����̓A���J�[�Ƃ���0�ɂ��Ă����K�v������
				printf("pc_readdb: skill ID %d is over max tree %d!!\n", skillid, MAX_SKILL_TREE);
				continue;
			}
			if(j > 0 && skillid < st[j-1].id) {
				// �X�L��ID�̏����ɕ���łȂ��ꍇ
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

			st[j].base_level  = atoi(split[3]);
			st[j].job_level   = atoi(split[4]);
			st[j].class_level = atoi(split[5]);
			st[j].upper       = atoi(split[6]);

			for(x = 7, y = 0; split[x] && split[x + 1] && y < MAX_SKILL_NEED; x += 2, y++) {
				st[j].need[y].id = atoi(split[x]);
				st[j].need[y].lv = atoi(split[x + 1]);
			}
			count++;
		}
		fclose(fp);
		printf("read %s done (count=%d)\n", filename2[m], count);
	}

	// �����C���e�[�u��
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
 * �I��
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
 * pc�֌W������
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

