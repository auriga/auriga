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

#ifndef _ITEMDB_H_
#define _ITEMDB_H_

#include "map.h"

#define MAX_RANDITEM	10000

struct item_data {
	int nameid;
	char name[48];
	char jname[48];
	char cardillustname[64];
	int value_buy;
	int value_sell;
	int type;
	unsigned int class_;
	int sex;
	int equip;
	int weight;
	int atk;
	int def;
	int range;
	int slot;
	int look;
	int elv;
	int wlv;
	int refine;
	struct script_code *use_script;
	struct script_code *equip_script;
	struct {
		unsigned available : 1;
		unsigned value_notdc : 1;
		unsigned value_notoc : 1;
		unsigned dropable : 1;
		unsigned storageable : 1;
		unsigned cartable : 1;
	} flag;
	int view_id;
	int group;
	int delay;
	int upper; 	//0:all(7に強制変換) 1:転生前 2:転生 4:養子
	int zone;	//0:制限無 1:normal 2:pvp 4:gvg 8:pk 16:turbo 32:noteleport 64:noreturn 128:nobranch
	int arrow_type;
};

struct random_item_data {
	int nameid[MAX_RANDITEM];
	int separate[MAX_RANDITEM];
	int entry;
};

struct item_data* itemdb_searchname(const char *name);
struct item_data* itemdb_search(int nameid);
struct item_data* itemdb_exists(int nameid);

#define itemdb_jname(n)       itemdb_search(n)->jname
#define itemdb_type(n)        itemdb_search(n)->type
#define itemdb_atk(n)         itemdb_search(n)->atk
#define itemdb_def(n)         itemdb_search(n)->def
#define itemdb_look(n)        itemdb_search(n)->look
#define itemdb_weight(n)      itemdb_search(n)->weight
#define itemdb_equip(n)       itemdb_search(n)->equip
#define itemdb_usescript(n)   itemdb_search(n)->use_script
#define itemdb_equipscript(n) itemdb_search(n)->equip_script
#define itemdb_wlv(n)         itemdb_search(n)->wlv
#define itemdb_range(n)       itemdb_search(n)->range
#define itemdb_slot(n)        itemdb_search(n)->slot
#define itemdb_value_buy(n)   itemdb_search(n)->value_buy
#define itemdb_value_sell(n)  itemdb_search(n)->value_sell
#define itemdb_value_notdc(n) itemdb_search(n)->flag.value_notdc
#define itemdb_value_notoc(n) itemdb_search(n)->flag.value_notoc

#define	itemdb_available(n) (itemdb_exists(n) && itemdb_search(n)->flag.available)
#define	itemdb_viewid(n)    (itemdb_search(n)->view_id)
#define	itemdb_group(n)     (itemdb_search(n)->group)

#define itemdb_isspecial(n) ((n) == 0x00ff || (n) == 0x00fe || (n) == (short)0xff00)

int itemdb_searchrandomid(int type);

int itemdb_isequip(int);
int itemdb_isequip2(struct item_data *);
int itemdb_isequip3(int);
int itemdb_iscartable(int nameid);
int itemdb_isstorageable(int nameid);
int itemdb_isdropable(int nameid);

int itemdb_idsearch(const int fd, const char *str, int (*func)(void*, void*, va_list));

void itemdb_reload(void);
void do_final_itemdb(void);
int do_init_itemdb(void);

#endif
