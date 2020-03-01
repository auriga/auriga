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

#ifndef _MERC_H_
#define _MERC_H_

#include "map.h"

#define MERC_NATURAL_HEAL_HP_INTERVAL 8000
#define MERC_NATURAL_HEAL_SP_INTERVAL 6000

#define MAX_MERCSKILL_TREE 16

struct merc_db {
	short class_;
	char name[24],jname[24];
	unsigned short lv;
	int max_hp,max_sp;
	int atk1,atk2;
	int def,mdef;
	int str,agi,vit,int_,dex,luk;
	short size,race;
	int element;
	int range;
	int speed,adelay,amotion,dmotion;
	struct script_code *script;
};

struct merc_db* merc_search_data(int nameid);
int merc_get_skilltree_max(int class_,int skillid);

int merc_callmerc(struct map_session_data *sd, int class_, unsigned int limit);
int merc_recv_mercdata(int account_id,int char_id,struct mmo_mercstatus *p,int flag);
int merc_delete_data(struct map_session_data *sd);
int merc_menu(struct map_session_data *sd, int menunum);
int merc_return_master(struct map_session_data *sd);
int merc_save_data(struct map_session_data *sd);

int merc_calc_status(struct merc_data *mcd);
int merc_checkskill(struct merc_data *mcd,int skill_id);

int merc_get_fame(struct map_session_data *sd, int class_);
int merc_set_fame(struct map_session_data *sd, int class_, int val);
int merc_get_call(struct map_session_data *sd, int class_);
int merc_set_call(struct map_session_data *sd, int class_, int val);

int merc_killcount(struct merc_data *mcd,unsigned short lv);
int merc_gainexp(struct merc_data *mcd,struct mob_data *md,atn_bignumber base_exp,atn_bignumber job_exp);
int merc_damage(struct block_list *src,struct merc_data *mcd,int damage);
int merc_heal(struct merc_data *mcd,int hp,int sp);

int merc_natural_heal_timer_delete(struct merc_data *mcd);
int merc_employ_timer_delete(struct merc_data *mcd);

void merc_reload(void);
int do_init_merc(void);
int do_final_merc(void);

#endif
