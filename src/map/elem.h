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

#ifndef _ELEM_H_
#define _ELEM_H_

#include "map.h"

#define MIN_ELEMTHINKTIME 100
#define MIN_ELEMDISTANCE 2
#define MAX_ELEMDISTANCE 6

#define ELEM_NATURAL_HEAL_HP_INTERVAL 8000
#define ELEM_NATURAL_HEAL_SP_INTERVAL 6000

#define MAX_ELEMSKILL_TREE 16

enum {
	ELMODE_WAIT = 0,
	ELMODE_PASSIVE,
	ELMODE_DEFENSIVE,
	ELMODE_OFFENSIVE,
};

enum {
	ELEMID_EL_AGNI_S		= 2114,		// アグニ(小型)
	ELEMID_EL_AGNI_M		= 2115,		// アグニ(中型)
	ELEMID_EL_AGNI_L		= 2116,		// アグニ(大型)
	ELEMID_EL_AQUA_S		= 2117,		// アクア(小型)
	ELEMID_EL_AQUA_M		= 2118,		// アクア(中型)
	ELEMID_EL_AQUA_L		= 2119,		// アクア(大型)
	ELEMID_EL_VENTUS_S		= 2120,		// ベントス(小型)
	ELEMID_EL_VENTUS_M		= 2121,		// ベントス(中型)
	ELEMID_EL_VENTUS_L		= 2122,		// ベントス(大型)
	ELEMID_EL_TERA_S		= 2123,		// テラ(小型)
	ELEMID_EL_TERA_M		= 2124,		// テラ(中型)
	ELEMID_EL_TERA_L		= 2125,		// テラ(大型)
	ELEMID_EM_DILUVIO		= 20816,	// ディルビオ
	ELEMID_EM_ARDOR			= 20817,	// アルドール
	ELEMID_EM_PROCELLA		= 20818,	// プロセラ
	ELEMID_EM_TERREMOTUS	= 20819,	// テレモトゥス
	ELEMID_EM_SERPENS		= 20820,	// サーペンス
};

struct elem_db {
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

#define elem_is4thclass(eld) ((eld)->status.class_ >= ELEMID_EM_DILUVIO && (eld)->status.class_ <= ELEMID_EM_SERPENS)

struct elem_db* elem_search_data(int nameid);
int elem_get_skilltree_max(int class_,int skillid);

int elem_create_data(struct map_session_data *sd, int class_, unsigned int limit);
int elem_recv_elemdata(int account_id,int char_id,struct mmo_elemstatus *p,int flag);
int elem_delete_data(struct map_session_data *sd);
int elem_save_data(struct map_session_data *sd);

int elem_calc_status(struct elem_data *eld);
int elem_checkskill(struct elem_data *eld,int skill_id);
int elem_change_mode(struct elem_data *eld, int mode);
int elem_skilluse(struct elem_data *eld, struct block_list *bl, int mode);
int elem_gainexp(struct elem_data *eld,struct mob_data *md,atn_bignumber base_exp,atn_bignumber job_exp);
int elem_damage(struct block_list *src,struct elem_data *eld,int damage);
int elem_heal(struct elem_data *eld,int hp,int sp);

int elem_natural_heal_timer_delete(struct elem_data *eld);
int elem_summon_timer_delete(struct elem_data *eld);

void elem_reload(void);
int do_init_elem(void);
int do_final_elem(void);

#endif
