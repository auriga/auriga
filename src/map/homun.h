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

#ifndef _HOMUN_H_
#define _HOMUN_H_

#include "map.h"

#define HOM_NATURAL_HEAL_HP_INTERVAL 2000
#define HOM_NATURAL_HEAL_SP_INTERVAL 4000

#define MAX_HOMSKILL_TREE 16

struct homun_status {
	int hp,sp;
	short str,agi,vit,int_,dex,luk;
};

struct homun_db {
	short class_;
	unsigned short base_level;
	char name[24],jname[24];
	//int hp,sp,hp_kmax,hp_kmin,sp_kmax,sp_kmin;
	int hp,sp;
	int str,agi,vit,int_,dex,luk;
	//int base;
	//int str_k,agi_k,vit_k,int_k,dex_k,luk_k;
	struct homun_status grow_min,grow_max,evo_min,evo_max;
	short AcceID;
	short FoodID;
	short aspd_k;
	short view_class,size,race;
	int element,evo_class;
	short exp_table;
	short skillpoint;
	struct script_code *script;
};
extern struct homun_db homun_db[MAX_HOMUN_DB];

struct random_homun_data {
	int homunid;
	int per;
};

int homun_get_skilltree_max(int class_,int skillid);

int homun_hungry_timer_delete(struct homun_data *hd);

int homun_menu(struct map_session_data *sd,int menunum);
int homun_change_name(struct map_session_data *sd,const char *name);
int homun_return_master(struct map_session_data *sd);

int homun_callhom(struct map_session_data *sd);
int homun_recv_homdata(int account_id,int char_id,struct mmo_homunstatus *p,int flag);
int homun_return_embryo(struct map_session_data *sd);
int homun_revive(struct map_session_data *sd,int skilllv);
int homun_change_class( struct map_session_data *sd, int class_ );

int homun_checkskill(struct homun_data *hd,int skill_id);
void homun_skillup(struct map_session_data *sd, int skill_num);
int homun_calc_skilltree(struct homun_data *hd);
int homun_gainexp(struct homun_data *hd,struct mob_data *md,atn_bignumber base_exp,atn_bignumber job_exp);
int homun_nextbaseexp(struct homun_data *hd);
int homun_calc_status(struct homun_data *hd);
int homun_upstatus(struct mmo_homunstatus *hd);

int homun_damage(struct block_list *src,struct homun_data *hd,int damage);

int homun_heal(struct homun_data *hd,int hp,int sp);
int homun_natural_heal_timer_delete(struct homun_data *hd);
int homun_create_hom(struct map_session_data *sd,int homunid);
int homun_recalc_status(struct homun_data *hd);
int homun_delete_data(struct map_session_data *sd);
int homun_save_data(struct map_session_data *sd);

int homun_isalive(struct map_session_data *sd);

int do_init_homun(void);
int do_final_homun(void);

void homun_reload(void);

#endif
