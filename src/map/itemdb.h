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

#define MAX_RAND_ITEM_TYPE		20
#define MAX_RAND_ITEM_ENTRY		1000
#define MAX_RAND_ITEM_AMOUNT	10000

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
		unsigned pet_egg : 1;
		unsigned pet_acce : 1;
		unsigned buyingable : 1;
	} flag;
	int view_id;
	int group;
	int delay;
	int upper; 	//0:all(7に強制変換) 1:転生前 2:転生 4:養子
	int zone;	//0:制限無 1:normal 2:pvp 4:gvg 8:pk 16:turbo 32:noteleport 64:noreturn 128:nobranch
	int arrow_type;
};

struct random_item_data {
	struct {
		int nameid;
		int qty;
	} data[MAX_RAND_ITEM_ENTRY];
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
int itemdb_isweapon(int nameid);
int itemdb_isarmor(int nameid);
int itemdb_iscartable(int nameid);
int itemdb_isstorageable(int nameid);
int itemdb_isdropable(int nameid);
int itemdb_isbuyingable(int nameid);

int itemdb_idsearch(const int fd, const char *str, int (*func)(void*, void*, va_list));

void itemdb_reload(void);
void do_final_itemdb(void);
int do_init_itemdb(void);

// item_type
enum {
	ITEMTYPE_HEAL = 0,
	ITEMTYPE_SCHANGE,
	ITEMTYPE_SPECIAL,
	ITEMTYPE_EVENT,
	ITEMTYPE_ARMOR,
	ITEMTYPE_WEAPON,
	ITEMTYPE_CARD,
	ITEMTYPE_QUEST,
	ITEMTYPE_BOW,
	ITEMTYPE_BOTHHAND,
	ITEMTYPE_ARROW,
	ITEMTYPE_ARMORTM,
	ITEMTYPE_ARMORTB,
	ITEMTYPE_ARMORMB,
	ITEMTYPE_ARMORTMB,
	ITEMTYPE_GUN,
	ITEMTYPE_AMMO,
	ITEMTYPE_THROWWEAPON,
	ITEMTYPE_CASH_POINT_ITEM,
	ITEMTYPE_CANNONBALL,
	ITEMTYPE_COSTUME,
};

// 装備箇所
enum {
	LOC_NOTHING				= 0x0,
	LOC_HEAD				= 0x1,	// 頭下段
	LOC_RARM				= 0x2,	// 右手
	LOC_ROBE				= 0x4,	// 肩
	LOC_RACCESSORY			= 0x8,	// アクセサリ右
	LOC_BODY				= 0x10,	// 体
	LOC_LARM				= 0x20,	// 左手
	LOC_RLARM				= 0x22,	// 両手
	LOC_SHOES				= 0x40,	// 靴
	LOC_LACCESSORY			= 0x80,	// アクセサリ左
	LOC_RLACCESSORY			= 0x88,	// アクセサリ右左
	LOC_HEAD2				= 0x100,	// 頭上段
	LOC_HEAD_TB				= 0x101,	// 頭上下段
	LOC_HEAD3				= 0x200,	// 頭中段
	LOC_HEAD_MB				= 0x201,	// 頭中下段
	LOC_HEAD_TM				= 0x300,	// 頭上中段
	LOC_HEAD_TMB			= 0x301,	// 頭上中下段
	LOC_ARROW				= 0x8000,	// 矢・弾丸・苦無・手裏剣・キャノンボール
	LOC_COSTUME_HEAD2		= 0x400,	// コスチューム上段
	LOC_COSTUME_HEAD3		= 0x800,	// コスチューム中段
	LOC_COSTUME_HEAD_TM		= 0xC00,	// コスチューム上中段
	LOC_COSTUME_HEAD		= 0x1000,	// コスチューム下段
	LOC_COSTUME_ROBE		= 0x2000,	// コスチューム肩
	LOC_COSTUME_HEAD_TB		= 0x1400,	// コスチューム上下段
	LOC_COSTUME_HEAD_MB		= 0x1800,	// コスチューム中下段
	LOC_COSTUME_HEAD_TMB	= 0x1C00	// コスチューム上中下段
};

#endif
