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

#ifndef _MERC_H_
#define _MERC_H_

#include "map.h"

#define MERC_NATURAL_HEAL_HP_INTERVAL 2000
#define MERC_NATURAL_HEAL_SP_INTERVAL 4000

#define MAX_MERCSKILL_TREE 16

struct merc_db {
	short class_;
	unsigned short base_level;
	char name[24],jname[24];
	int hp,sp,hp_kmax,hp_kmin,sp_kmax,sp_kmin;
	int str,agi,vit,int_,dex,luk;
	int base;
	int str_k,agi_k,vit_k,int_k,dex_k,luk_k;
	short aspd_k;
	short view_class,size,race;
	int element;
	int range;
	unsigned int limit;
	struct script_code *script;
};
extern struct merc_db merc_db[MAX_MERC_DB];

int merc_get_skilltree_max(int class_,int skillid);

int merc_callmerc(struct map_session_data *sd, int class_);
int merc_recv_mercdata(int account_id,int char_id,struct mmo_mercstatus *p,int flag);
int merc_delete_data(struct map_session_data *sd);
int merc_menu(struct map_session_data *sd, int menunum);
int merc_return_master(struct map_session_data *sd);
int merc_save_data(struct map_session_data *sd);

int merc_calc_status(struct merc_data *mcd);
int merc_checkskill(struct merc_data *mcd,int skill_id);
int merc_calc_skilltree(struct merc_data *mcd);

int merc_gainexp(struct merc_data *mcd,struct mob_data *md,atn_bignumber base_exp,atn_bignumber job_exp);
int merc_damage(struct block_list *src,struct merc_data *mcd,int damage);
int merc_heal(struct merc_data *mcd,int hp,int sp);

int merc_natural_heal_timer_delete(struct merc_data *mcd);
int merc_employ_timer_delete(struct merc_data *mcd);

int do_init_merc(void);
int do_final_merc(void);

#endif
