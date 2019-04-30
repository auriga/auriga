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

#ifndef _PC_H_
#define _PC_H_

#include "utils.h"
#include "map.h"

#define MAX_SKILL_TREE 100

enum {
	LOOK_BASE = 0,
	LOOK_HAIR,
	LOOK_WEAPON,
	LOOK_HEAD_BOTTOM,
	LOOK_HEAD_TOP,
	LOOK_HEAD_MID,
	LOOK_HAIR_COLOR,
	LOOK_CLOTHES_COLOR,
	LOOK_SHIELD,
	LOOK_SHOES,
	LOOK_BODY,
	LOOK_FLOOR,
	LOOK_ROBE,
	LOOK_BODY2,
};

#define pc_setdead(sd) ((sd)->state.dead_sit = 1)
#define pc_issit(sd) ((sd)->state.dead_sit == 2)
#define pc_setdir(sd,b,h) ((sd)->dir = (char)(b) ,(sd)->head_dir = (char)(h) )

#define pc_ishiding(sd) (((sd)->sc.option&(OPTION_HIDE | OPTION_CLOAKING | OPTION_FOOTPRINT)) || (sd)->sc.data[SC_CAMOUFLAGE].timer != -1)
#define pc_iscloaking(sd)   (!((sd)->sc.option&OPTION_FOOTPRINT) && ((sd)->sc.option&OPTION_CLOAKING))
#define pc_ischasewalk(sd)  (((sd)->sc.option&OPTION_FOOTPRINT) && ((sd)->sc.option&OPTION_CLOAKING))

#if PACKETVER < 20120201
	#define pc_iscarton(sd) ((sd)->sc.option&OPTION_CARTMASK)
#else
	#define pc_iscarton(sd) ((sd)->sc.data[SC_ON_PUSH_CART].timer != -1)
#endif
#define pc_isfalcon(sd) ((sd)->sc.option&OPTION_FALCON)
#define pc_isriding(sd) ((sd)->sc.option&OPTION_PECO)
#define pc_isinvisible(sd) ((sd)->sc.option&OPTION_SPECIALHIDING)
#define pc_isdragon(sd) ((sd)->sc.option&OPTION_DRAGONMASK)
#define pc_iswolf(sd) ((sd)->sc.option&OPTION_WUG)
#define pc_iswolfmount(sd) ((sd)->sc.option&OPTION_WUGRIDER)
#define pc_isgear(sd) ((sd)->sc.option&OPTION_MADOGEAR)

int pc_is50overweight(struct map_session_data *sd);
int pc_is90overweight(struct map_session_data *sd);

extern int attr_fix_table[MAX_ELE_LEVEL][ELE_MAX][ELE_MAX];
extern int max_job_table[PC_UPPER_MAX][PC_JOB_MAX];

int pc_get_skilltree_max(struct pc_base_job *bj,int skillid);

void pc_set_gm_account_fname(const char *str);
int pc_isGM(struct map_session_data *sd);
int pc_numisGM(int account_id);
int pc_get_gm_account_dummy(void);
int pc_isquitable(struct map_session_data *sd);

int pc_setrestartvalue(struct map_session_data *sd,int type);
int pc_makesavestatus(struct map_session_data *);
void pc_setnewpc(struct map_session_data*,int,int,int,int,int);
int pc_authok(int,struct mmo_charstatus *st,struct registry *reg);
int pc_authfail(int);

int pc_equippoint(struct map_session_data *sd,int n);

int pc_checkskill(struct map_session_data *sd,int skill_id);
int pc_checkskill2(struct map_session_data *sd,int skill_id);
int pc_checkequip(struct map_session_data *sd,int pos);

int pc_setpos(struct map_session_data*,const char*,int,int,int);
int pc_setsavepoint(struct map_session_data*,const char*,int,int);
int pc_randomwarp(struct map_session_data *sd,int type);
void pc_memo(struct map_session_data *sd, int i);

int pc_clearitemlimit(struct map_session_data *sd);
int pc_checkadditem(struct map_session_data*,int,int);
int pc_inventoryblank(struct map_session_data*);
int pc_search_inventory(struct map_session_data *sd,int item_id);
int pc_payzeny(struct map_session_data*,int);
int pc_additem(struct map_session_data*,struct item*,int);
int pc_getzeny(struct map_session_data*,int);
int pc_lossequipitem(struct map_session_data *sd,int pos,int type);
void pc_delitem(struct map_session_data*, int n, int amount, int type, short dtype);
int pc_checkitem(struct map_session_data*);

int pc_cart_additem(struct map_session_data *sd,struct item *item_data,int amount);
int pc_cart_delitem(struct map_session_data *sd,int n,int amount,int type);
void pc_putitemtocart(struct map_session_data *sd, int idx, int amount);
void pc_getitemfromcart(struct map_session_data *sd, int idx, int amount);
int pc_cartitem_amount(struct map_session_data *sd,int idx,int amount);

void pc_takeitem(struct map_session_data*, struct flooritem_data*);
void pc_takeitem_sub(struct party *p, struct map_session_data *sd, struct flooritem_data *fitem);
int pc_dropitem(struct map_session_data*, int, int);

int pc_checkweighticon(struct map_session_data *sd);

int pc_skill(struct map_session_data*,int,int,int);

void pc_insert_card(struct map_session_data *sd, int idx_card, int idx_equip);

void pc_item_identify(struct map_session_data *sd, int idx);
int pc_steal_item(struct map_session_data *sd,struct mob_data *md);
int pc_steal_coin(struct map_session_data *sd,struct mob_data *md);

int pc_modifybuyvalue(struct map_session_data*,int);
int pc_modifysellvalue(struct map_session_data*,int);

int pc_gainexp(struct map_session_data*,struct mob_data*,atn_bignumber,atn_bignumber, short quest);
int pc_exp_penalty(struct map_session_data *sd, struct map_session_data *ssd, int per, int type);
int pc_nextbaseexp(struct map_session_data *);
int pc_nextjobexp(struct map_session_data *);
int pc_need_status_point(struct map_session_data *,int);
void pc_statusup(struct map_session_data *sd, unsigned short type,int num);
int pc_statusup2(struct map_session_data*,int,int);
void pc_skillup(struct map_session_data *sd, int skill_num);
int pc_allskillup(struct map_session_data* sd,int flag);
void pc_resetstate(struct map_session_data* sd);
void pc_resetskill(struct map_session_data* sd, int flag);
void pc_equipitem(struct map_session_data*, int n, int pos);
void pc_unequipitem(struct map_session_data*, int n, int type);
int pc_equippeditem(struct map_session_data *sd,int id);
void pc_useitem(struct map_session_data*, int n);

int pc_damage(struct block_list *,struct map_session_data*,int);
int pc_heal(struct map_session_data *,int,int);
int pc_itemheal(struct map_session_data *sd,int hp,int sp);
int pc_percentheal(struct map_session_data *sd,int,int);
int pc_jobchange(struct map_session_data *,int, int);
void pc_setoption(struct map_session_data *sd, unsigned int type);
void pc_setcart(struct map_session_data *sd, unsigned short type);
int pc_setfalcon(struct map_session_data *sd);
int pc_setriding(struct map_session_data *sd);
int pc_setdragon(struct map_session_data *sd, int type);
int pc_setgear(struct map_session_data *sd);
int pc_changelook(struct map_session_data *,int,int);

int pc_readparam(struct map_session_data*,int);
int pc_setparam(struct map_session_data*,int,int);
int pc_readreg(struct map_session_data*,int);
int pc_setreg(struct map_session_data*,int,int);
char *pc_readregstr(struct map_session_data *sd,int reg);
int pc_setregstr(struct map_session_data *sd,int reg,const char *str);

int pc_readregistry(struct map_session_data *sd, const char *reg, int type);
int pc_setregistry(struct map_session_data *sd, const char *reg, int val, int type);
#define pc_readglobalreg(sd,reg) pc_readregistry(sd,reg,3)
#define pc_setglobalreg(sd,reg,val) pc_setregistry(sd,reg,val,3)
#define pc_readaccountreg(sd,reg) pc_readregistry(sd,reg,2)
#define pc_setaccountreg(sd,reg,val) pc_setregistry(sd,reg,val,2)
#define pc_readaccountreg2(sd,reg) pc_readregistry(sd,reg,1)
#define pc_setaccountreg2(sd,reg,val) pc_setregistry(sd,reg,val,1)

int pc_addeventtimer(struct map_session_data *sd,int tick,const char *name);
int pc_deleventtimer(struct map_session_data *sd,const char *name);
int pc_cleareventtimer(struct map_session_data *sd);
int pc_addeventtimercount(struct map_session_data *sd,const char *name,int tick);
int pc_geteventtimerdiff(struct map_session_data *sd,const char *name);

int pc_calc_pvprank(struct map_session_data *sd);
int pc_calc_pvprank_timer(int tid,unsigned int tick,int id,void *data);

int pc_ismarried(struct map_session_data *sd);
int pc_marriage(struct map_session_data *sd,struct map_session_data *dstsd);
int pc_divorce(struct map_session_data *sd);
struct map_session_data *pc_get_partner(struct map_session_data *sd);

int pc_adoption(struct map_session_data* sd,struct map_session_data *parent);
int pc_adoption_sub(struct map_session_data* sd,struct map_session_data *papa,struct map_session_data *mama);
int pc_check_adopt_condition(struct map_session_data *dstsd, struct map_session_data *sd, struct map_session_data *psd, short flag);
void pc_adopt_reply(struct map_session_data *sd,int src_id,int p_id,short flag);
int pc_break_adoption(struct map_session_data *sd);

int pc_break_equip(struct map_session_data *sd, int where);
int pc_break_equip2(struct map_session_data *sd, int where);

int pc_candrop(struct map_session_data *sd,int item_id);

void pc_setsit(struct map_session_data *sd);
void pc_setstand(struct map_session_data *sd);
int pc_calc_skilltree(struct map_session_data *sd);
int pc_check_guild_skill_effective_range(struct map_session_data *sd);

#define pc_isupper(sd) (((sd)->status.class_ >= PC_CLASS_NV_H && (sd)->status.class_ <= PC_CLASS_CR2_H) ||	\
						((sd)->status.class_ >= PC_CLASS_RK_H && (sd)->status.class_ <= PC_CLASS_GC_H) ||	\
						((sd)->status.class_ >= PC_CLASS_LG_H && (sd)->status.class_ <= PC_CLASS_SC_H) ||	\
						(sd)->status.class_ == PC_CLASS_RK2_H || (sd)->status.class_ == PC_CLASS_LG2_H ||	\
						(sd)->status.class_ == PC_CLASS_RA2_H || (sd)->status.class_ == PC_CLASS_NC2_H ||	\
						(sd)->status.class_ == PC_CLASS_RK3_H || (sd)->status.class_ == PC_CLASS_RK4_H ||	\
						(sd)->status.class_ == PC_CLASS_RK5_H || (sd)->status.class_ == PC_CLASS_RK6_H)

#define pc_isbaby(sd)  (((sd)->status.class_ >= PC_CLASS_NV_B && (sd)->status.class_ <= PC_CLASS_SNV_B) ||	\
						((sd)->status.class_ >= PC_CLASS_RK_B && (sd)->status.class_ <= PC_CLASS_NC2_B) || \
						(sd)->status.class_ == PC_CLASS_ESNV_B)

#define pc_is1stclass(sd) (((sd)->s_class.job >= PC_JOB_SM && (sd)->s_class.job <= PC_JOB_TF) ||	\
						   (sd)->s_class.job == PC_JOB_SNV || (sd)->s_class.job == PC_JOB_TK ||	\
						   (sd)->s_class.job == PC_JOB_GS || (sd)->s_class.job == PC_JOB_NJ ||		\
						   (sd)->s_class.job == PC_JOB_MB || (sd)->s_class.job == PC_JOB_ESNV)

#define pc_is2ndclass(sd) (((sd)->s_class.job >= PC_JOB_KN && (sd)->s_class.job <= PC_JOB_DC) ||	\
						   (sd)->s_class.job == PC_JOB_SG || (sd)->s_class.job == PC_JOB_SL ||		\
						   (sd)->s_class.job == PC_JOB_DK || (sd)->s_class.job == PC_JOB_DA ||	\
						   (sd)->s_class.job == PC_JOB_KG || (sd)->s_class.job == PC_JOB_OB ||	\
						   (sd)->s_class.job == PC_JOB_RB)

#define pc_is3rdclass(sd) ((sd)->s_class.job >= PC_JOB_RK && (sd)->s_class.job <= PC_JOB_SC)

#define pc_isdoram(sd) ((sd)->s_class.job == PC_JOB_SUM)

struct pc_base_job pc_calc_base_job(int b_class);
int pc_calc_class_job(int job,int upper);
int pc_calc_job_class(int class_);
int pc_get_base_class(int class_, int type);
unsigned int pc_get_job_bit(int job);

void pc_read_gm_account(void);
int pc_setinvincibletimer(struct map_session_data *sd,int);
int pc_delinvincibletimer(struct map_session_data *sd,int);
int pc_addspiritball(struct map_session_data *sd,int,int);
int pc_delspiritball(struct map_session_data *sd,int,int);
int pc_addcoin(struct map_session_data *sd,int,int);
int pc_delcoin(struct map_session_data *sd,int,int);
int pc_addelementball(struct map_session_data *sd, int interval, int max, short ele);
int pc_delelementball(struct map_session_data *sd, int count, int type);

int pc_runtodir(struct map_session_data *sd);

// DBçƒì«çûóp
int pc_readdb(void);

int do_final_pc(void);
int do_init_pc(void);

enum {
	ADDITEM_EXIST,
	ADDITEM_NEW,
	ADDITEM_OVERAMOUNT,
};

enum e_store_type
{
	STORE_TYPE_NONE			= 0,
	STORE_TYPE_VENDING		= 1,
	STORE_TYPE_BUYINGSTORE	= 2,
};

#endif
