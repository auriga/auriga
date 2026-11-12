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

#ifndef _PET_H_
#define _PET_H_

#define MAX_PET_DB	256

struct pet_db {
	short class_;
	char name[24],jname[24];
	int itemID;
	short EggID;
	short AcceID;
	int FoodID;
	int fullness;
	int hungry_delay;
	int r_hungry;
	int r_full;
	int die;
	int capture;
	int speed;
	short intimate;
	char s_perfor;
	int talk_convert_class;
	int attack_rate;
	int defence_attack_rate;
	int change_target_rate;
	struct script_code *script;
};

enum e_pet_evolution_result {
	PET_EVOL_FAIL_UNKNOWN = 0,
	PET_EVOL_FAIL_NOTEXIST_CALLPET = 1,
	PET_EVOL_FAIL_NOT_PETEGG = 2,
	PET_EVOL_FAIL_RECIPE = 3,
	PET_EVOL_FAIL_MATERIAL = 4,
	PET_EVOL_FAIL_RG_FAMILIAR = 5,
	PET_EVOL_SUCCESS = 6,
};

enum {
	PET_CLASS,
	PET_CATCH,
	PET_EGG,
	PET_EQUIP,
	PET_FOOD,
};

struct pet_db* pet_search_data(int key, int type);
int pet_hungry_val(struct map_session_data *sd);
int pet_target_check(struct map_session_data *sd,struct block_list *bl,int type);
int pet_hungry_timer_delete(struct pet_data *pd);
int pet_recv_petdata(int account_id,struct s_pet *p,int flag);
int pet_select_egg(struct map_session_data *sd,short egg_index);
int pet_catch_process1(struct map_session_data *sd,int target_class);
int pet_catch_process2(struct map_session_data *sd,int target_id);
int pet_get_egg(int account_id,int pet_id,int flag);
int pet_egg_search(struct map_session_data *sd, int pet_id);
int pet_is_hatched_egg(const struct item *item);
int pet_return_egg(struct map_session_data *sd);
int pet_return_egg_nodrop(struct map_session_data *sd);
void pet_nopet_update(struct map_session_data *sd);
void pet_mapflag_update(int m);
int pet_menu(struct map_session_data *sd,int menunum);
int pet_change_name(struct map_session_data *sd,const char *name);
void pet_equipitem(struct map_session_data *sd, int idx);
void pet_evolution(struct map_session_data *sd, int egg_id);
int pet_lootitem_drop(struct pet_data *pd,struct map_session_data *sd);
int pet_lootitem_free(struct pet_data *pd);
int pet_skill_support_timer(int tid,unsigned int tick,int id,void *data);
int do_init_pet(void);
int do_final_pet(void);

int read_petdb(void);

#endif
