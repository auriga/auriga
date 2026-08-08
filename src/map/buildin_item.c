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
#include <stdarg.h>
#include <time.h>

#include "db.h"
#include "timer.h"
#include "malloc.h"
#include "mmo.h"
#include "nullpo.h"
#include "utils.h"

#include "map.h"
#include "clif.h"
#include "itemdb.h"
#include "pc.h"
#include "script.h"
#include "script_internal.h"
#include "storage.h"
#include "mob.h"
#include "npc.h"
#include "pet.h"
#include "intif.h"
#include "skill.h"
#include "battle.h"
#include "status.h"
#include "unit.h"

/* Split from script.c (Issue #61) */

/*==========================================
 * カードのイラストを表示する
 *------------------------------------------
 */
int buildin_cutincard(struct script_state *st)
{
	int itemid = conv_num(st,& (st->stack->stack_data[st->start+2]));

	clif_cutin(script_rid2sd(st),itemdb_search(itemid)->cardillustname,4);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int buildin_countitem(struct script_state *st)
{
	int nameid = 0, count = 0;
	struct map_session_data *sd = script_rid2sd(st);
	struct script_data *data;

	data = &(st->stack->stack_data[st->start+2]);
	get_val(st,data);
	if( isstr(data) ) {
		const char *name = conv_str(st,data);
		struct item_data *item_data = itemdb_searchname(name);
		if(item_data)
			nameid = item_data->nameid;
	} else {
		nameid = conv_num(st,data);
	}

	if(sd && nameid > 0) {
		int i;
		for(i=0; i<MAX_INVENTORY; i++) {
			if(sd->status.inventory[i].nameid == nameid)
				count += sd->status.inventory[i].amount;
		}
	}
	push_val(st->stack,C_INT,count);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int buildin_countcartitem(struct script_state *st)
{
	int nameid = 0, count = 0;
	struct map_session_data *sd = script_rid2sd(st);
	struct script_data *data;

	data = &(st->stack->stack_data[st->start+2]);
	get_val(st,data);
	if( isstr(data) ) {
		const char *name = conv_str(st,data);
		struct item_data *item_data = itemdb_searchname(name);
		if(item_data)
			nameid = item_data->nameid;
	} else {
		nameid = conv_num(st,data);
	}

	if(sd && nameid > 0) {
		int i;
		for(i=0; i<MAX_CART; i++) {
			if(sd->status.cart[i].nameid == nameid)
				count += sd->status.cart[i].amount;
		}
	}
	push_val(st->stack,C_INT,count);

	return 0;
}

/*==========================================
 * 重量チェック
 *------------------------------------------
 */
int buildin_checkweight(struct script_state *st)
{
	int nameid=0, amount;
	struct map_session_data *sd = script_rid2sd(st);
	struct script_data *data;

	data = &(st->stack->stack_data[st->start+2]);
	get_val(st,data);
	if( isstr(data) ) {
		const char *name = conv_str(st,data);
		struct item_data *item_data = itemdb_searchname(name);
		if(item_data)
			nameid = item_data->nameid;
	} else {
		nameid = conv_num(st,data);
	}

	amount = conv_num(st,& (st->stack->stack_data[st->start+3]));

	if(sd && nameid > 0) {
		if(amount <= MAX_AMOUNT &&
		   itemdb_weight(nameid)*amount + sd->weight <= sd->max_weight &&
		   pc_search_inventory(sd,0) >= 0)
		{
			push_val(st->stack,C_INT,1);
			return 0;
		}
	}
	push_val(st->stack,C_INT,0);
	return 0;
}

/*==========================================
 * インベントリの空き数チェック
 *------------------------------------------
 */
int buildin_checkitemblank(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int amount = 0;

	if(sd)
		amount = pc_inventoryblank(sd);

	push_val(st->stack,C_INT,amount);
	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int buildin_getitem(struct script_state *st)
{
	int nameid=0, flag=0, ret=0, i=0, amount;
	struct map_session_data *sd;
	struct script_data *data;
	struct item item_tmp;
	bool preview = false;

	sd = script_rid2sd(st);

	data = &(st->stack->stack_data[st->start+2]);
	get_val(st,data);
	if( isstr(data) ) {
		const char *name = conv_str(st,data);
		struct item_data *item_data = itemdb_searchname(name);
		if(item_data)
			nameid = item_data->nameid;
	} else {
		nameid = conv_num(st,data);
	}

	amount = conv_num(st,& (st->stack->stack_data[st->start+3]));
	if(st->end > st->start+4)	// 鑑定した状態で渡すかどうか
		flag = (conv_num(st,& (st->stack->stack_data[st->start+4])) == 0)? 1: 0;
	if(st->end > st->start+5)	// アイテムを指定したIDに渡す
		sd = map_id2sd(conv_num(st,& (st->stack->stack_data[st->start+5])));
	if(sd == NULL)			// アイテムを渡す相手がいなかったらお帰り
		return 0;
	if(st->end > st->start+6)
		preview = conv_num(st,& (st->stack->stack_data[st->start+6]));

	do {
		memset(&item_tmp,0,sizeof(item_tmp));

		if(nameid < 0)		// ランダム
			item_tmp.nameid = itemdb_searchrandomid(-nameid);
		else
			item_tmp.nameid = nameid;

		if(!itemdb_exists(item_tmp.nameid))
			break;

		if(!flag || battle_config.itemidentify)
			item_tmp.identify = 1;
		else
			item_tmp.identify = !itemdb_isequip3(item_tmp.nameid);

		if((ret = pc_additem(sd,&item_tmp,(nameid < 0)? 1: amount,preview))) {
			clif_additem(sd,0,0,ret);
			if(!pc_candrop(sd,item_tmp.nameid))
				map_addflooritem(&item_tmp,(nameid < 0)? 1: amount,sd->bl.m,sd->bl.x,sd->bl.y,0,0,0,0);
		}
	} while(nameid < 0 && ++i < amount);	// ランダム系はアイテムの再抽選

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int buildin_getitem2(struct script_state *st)
{
	int nameid=0, ret=0, i=0, amount;
	int iden,ref,attr,c1,c2,c3,c4;
	unsigned int limit=0;
	struct map_session_data *sd;
	struct script_data *data;
	struct item_data *item_data;
	struct item item_tmp;
	bool preview = false;

	sd = script_rid2sd(st);

	data = &(st->stack->stack_data[st->start+2]);
	get_val(st,data);
	if( isstr(data) ) {
		const char *name = conv_str(st,data);
		struct item_data *item_data = itemdb_searchname(name);
		if(item_data)
			nameid = item_data->nameid;
	} else {
		nameid = conv_num(st,data);
	}

	amount = conv_num(st,& (st->stack->stack_data[st->start+3]));
	iden   = conv_num(st,& (st->stack->stack_data[st->start+4]));
	ref    = conv_num(st,& (st->stack->stack_data[st->start+5]));
	attr   = conv_num(st,& (st->stack->stack_data[st->start+6]));
	c1     = conv_num(st,& (st->stack->stack_data[st->start+7]));
	c2     = conv_num(st,& (st->stack->stack_data[st->start+8]));
	c3     = conv_num(st,& (st->stack->stack_data[st->start+9]));
	c4     = conv_num(st,& (st->stack->stack_data[st->start+10]));
	if(st->end > st->start+11)
		limit = (unsigned int)conv_num(st,& (st->stack->stack_data[st->start+11]));
	if(st->end > st->start+12)	// アイテムを指定したIDに渡す
		sd = map_id2sd(conv_num(st,& (st->stack->stack_data[st->start+12])));
	if(sd == NULL)			// アイテムを渡す相手がいなかったらお帰り
		return 0;
	if(st->end > st->start+13)
		preview = conv_num(st,& (st->stack->stack_data[st->start+13]));

	do {
		memset(&item_tmp,0,sizeof(item_tmp));

		if(nameid < 0)		// ランダム
			item_tmp.nameid = itemdb_searchrandomid(-nameid);
		else
			item_tmp.nameid = nameid;

		if(!itemdb_exists(item_tmp.nameid))
			break;

		item_data = itemdb_search(item_tmp.nameid);

		if(itemdb_isarmor(item_data->nameid) || itemdb_isweapon(item_data->nameid)) {
			if(ref > MAX_REFINE)
				ref = MAX_REFINE;
		} else if(item_data->flag.pet_egg) {
			iden = 1;
			ref = 0;
		} else {
			iden = 1;
			ref = attr = 0;
		}

		if(iden || battle_config.itemidentify)
			item_tmp.identify = 1;
		else
			item_tmp.identify = !itemdb_isequip3(item_tmp.nameid);

		item_tmp.refine    = ref;
		item_tmp.attribute = attr;
		item_tmp.card[0]   = c1;
		item_tmp.card[1]   = c2;
		item_tmp.card[2]   = c3;
		item_tmp.card[3]   = c4;
		item_tmp.limit     = (limit > 0)? (unsigned int)time(NULL) + limit: 0;

		if((ret = pc_additem(sd,&item_tmp,(nameid < 0)? 1: amount,preview))) {
			clif_additem(sd,0,0,ret);
			if(!pc_candrop(sd,item_tmp.nameid))
				map_addflooritem(&item_tmp,(nameid < 0)? 1: amount,sd->bl.m,sd->bl.x,sd->bl.y,0,0,0,0);
		}
	} while(nameid < 0 && ++i < amount);	// ランダム系はアイテムの再抽選

	return 0;
}

/*==========================================
 * オプション付きアイテムの取得
 *------------------------------------------
 */
int buildin_getoptitem(struct script_state *st)
{
	int nameid=0, ret=0, i=0, key=0;
	int iden,ref,attr,c1,c2,c3,c4;
	unsigned int limit=0;
	struct map_session_data *sd;
	struct script_data *data;
	struct item_data *item_data;
	struct item item_tmp;
	struct randopt_item_data ro;
	bool preview = false;

	sd = script_rid2sd(st);

	data = &(st->stack->stack_data[st->start+2]);
	get_val(st,data);
	if( isstr(data) ) {
		const char *name = conv_str(st,data);
		struct item_data *item_data = itemdb_searchname(name);
		if(item_data)
			nameid = item_data->nameid;
	} else {
		nameid = conv_num(st,data);
	}

	iden   = conv_num(st,& (st->stack->stack_data[st->start+3]));
	ref    = conv_num(st,& (st->stack->stack_data[st->start+4]));
	attr   = conv_num(st,& (st->stack->stack_data[st->start+5]));
	c1     = conv_num(st,& (st->stack->stack_data[st->start+6]));
	c2     = conv_num(st,& (st->stack->stack_data[st->start+7]));
	c3     = conv_num(st,& (st->stack->stack_data[st->start+8]));
	c4     = conv_num(st,& (st->stack->stack_data[st->start+9]));
	key    = conv_num(st,& (st->stack->stack_data[st->start+10]));
	if(st->end > st->start+11)
		limit = (unsigned int)conv_num(st,& (st->stack->stack_data[st->start+11]));
	if(st->end > st->start+12)	// アイテムを指定したIDに渡す
		sd = map_id2sd(conv_num(st,& (st->stack->stack_data[st->start+12])));
	if(st->end > st->start+13)
		preview = conv_num(st,& (st->stack->stack_data[st->start+13]));

	if(sd) {
		memset(&item_tmp,0,sizeof(item_tmp));

		if(nameid < 0)		// ランダム
			item_tmp.nameid = itemdb_searchrandomid(-nameid);
		else
			item_tmp.nameid = nameid;

		if(!itemdb_exists(item_tmp.nameid))
			return 0;

		item_data = itemdb_search(item_tmp.nameid);

		if(ref > MAX_REFINE)
			ref = MAX_REFINE;

		if(iden || battle_config.itemidentify)
			item_tmp.identify = 1;
		else
			item_tmp.identify = !itemdb_isequip3(item_tmp.nameid);

		item_tmp.refine    = ref;
		item_tmp.attribute = attr;
		item_tmp.card[0]   = c1;
		item_tmp.card[1]   = c2;
		item_tmp.card[2]   = c3;
		item_tmp.card[3]   = c4;
		item_tmp.limit     = (limit > 0)? (unsigned int)time(NULL) + limit: 0;

		ro = itemdb_randopt_data(1, key);
		if(ro.nameid) {
			int slot = 0;
			int rate = 0;
			for(i = 0; i < sizeof(ro.opt) / sizeof(ro.opt[0]); i++) {
				if(ro.opt[i].slot != slot)
					rate = 0;
				slot = ro.opt[i].slot;
				if(item_tmp.opt[slot].id > 0)
					continue;
				rate += ro.opt[i].rate;
				if(rate >= atn_rand()%10000) {
					item_tmp.opt[slot].id = ro.opt[i].optid;
					if(ro.opt[i].optval_plus)
						item_tmp.opt[slot].val = ro.opt[i].optval_min + (atn_rand() % ((ro.opt[i].optval_max - ro.opt[i].optval_min) / ro.opt[i].optval_plus + 1)) * ro.opt[i].optval_plus;
					else if(ro.opt[i].optval_min != ro.opt[i].optval_max)
						item_tmp.opt[slot].val = ro.opt[i].optval_min + atn_rand() % (ro.opt[i].optval_max - ro.opt[i].optval_min + 1);
					else
						item_tmp.opt[slot].val = ro.opt[i].optval_min;
					rate = 0;
				}
			}
			for(i = 0; i < 5-1; i++) {
				if(item_tmp.opt[i].id == 0) {
					int j;
					for(j = i+1; j < 5; j++) {
						if(item_tmp.opt[j].id != 0) {
							item_tmp.opt[i].id = item_tmp.opt[j].id;
							item_tmp.opt[i].val = item_tmp.opt[j].val;
							item_tmp.opt[j].id = 0;
							item_tmp.opt[j].val = 0;
							break;
						}
					}
				}
			}
			if((ret = pc_additem(sd,&item_tmp,1,preview))) {
				clif_additem(sd,0,0,ret);
				if(!pc_candrop(sd,item_tmp.nameid))
					map_addflooritem(&item_tmp,1,sd->bl.m,sd->bl.x,sd->bl.y,0,0,0,0);
			}
		}
	}

	return 0;
}

/*==========================================
 * 指定idxのアイテムを表示する
 *------------------------------------------
 */
int buildin_itempreview(struct script_state *st)
{
	short idx;
	struct map_session_data *sd = script_rid2sd(st);

	nullpo_retr(0, sd);

	idx   = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if(idx >= 0 && idx < MAX_INVENTORY)
		clif_item_preview(sd, idx);

	return 0;
}

/*==========================================
 * 指定IDのアイテムを削除する
 *------------------------------------------
 */
int buildin_delitem(struct script_state *st)
{
	int nameid=0,amount,i;
	int skip_egg = 0;
	struct map_session_data *sd = script_rid2sd(st);
	struct script_data *data;

	nullpo_retr(0, sd);

	data = &(st->stack->stack_data[st->start+2]);
	get_val(st,data);
	if( isstr(data) ) {
		const char *name = conv_str(st,data);
		struct item_data *item_data = itemdb_searchname(name);
		if(item_data)
			nameid = item_data->nameid;
	} else {
		nameid = conv_num(st,data);
	}
	if(nameid <= 0)
		return 0;

	amount = conv_num(st,& (st->stack->stack_data[st->start+3]));
	if(st->end > st->start+4)
		skip_egg = conv_num(st,& (st->stack->stack_data[st->start+4]));

	for(i=0; i<MAX_INVENTORY; i++) {
		if(sd->status.inventory[i].nameid == nameid) {
			if(!skip_egg &&
			   sd->inventory_data[i]->flag.pet_egg &&
			   sd->status.inventory[i].amount > 0 &&
			   sd->status.inventory[i].card[0] == (int)0xff00 &&
			   pet_search_data(nameid, PET_EGG) != NULL)
			{
				intif_delete_petdata(*((int *)(&sd->status.inventory[i].card[1])));
			}

			if(sd->status.inventory[i].amount >= amount) {
				pc_delitem(sd,i,amount,0,0);
				break;
			} else {
				amount -= sd->status.inventory[i].amount;
				pc_delitem(sd,i,sd->status.inventory[i].amount,0,0);
			}
		}
	}

	return 0;
}

/*==========================================
 * 指定IDのアイテムをカートから削除する
 *------------------------------------------
 */
int buildin_delcartitem(struct script_state *st)
{
	int nameid=0,amount,i;
	int skip_egg = 0;
	struct map_session_data *sd = script_rid2sd(st);
	struct script_data *data;

	nullpo_retr(0, sd);

	data = &(st->stack->stack_data[st->start+2]);
	get_val(st,data);
	if( isstr(data) ) {
		const char *name = conv_str(st,data);
		struct item_data *item_data = itemdb_searchname(name);
		if(item_data)
			nameid = item_data->nameid;
	} else {
		nameid = conv_num(st,data);
	}
	if(nameid <= 0)
		return 0;

	amount = conv_num(st,& (st->stack->stack_data[st->start+3]));
	if(st->end > st->start+4)
		skip_egg = conv_num(st,& (st->stack->stack_data[st->start+4]));

	for(i=0; i<MAX_CART; i++) {
		if(sd->status.cart[i].nameid == nameid) {
			if(!skip_egg &&
			   itemdb_search(nameid)->flag.pet_egg &&
			   sd->status.cart[i].amount > 0 &&
			   sd->status.cart[i].card[0] == (int)0xff00 &&
			   pet_search_data(nameid, PET_EGG) != NULL)
			{
				intif_delete_petdata(*((int *)(&sd->status.cart[i].card[1])));
			}

			if(sd->status.cart[i].amount >= amount) {
				pc_cart_delitem(sd,i,amount,!pc_iscarton(sd));
				break;
			} else {
				amount -= sd->status.cart[i].amount;
				pc_cart_delitem(sd,i,sd->status.cart[i].amount,!pc_iscarton(sd));
			}
		}
	}

	return 0;
}

/*==========================================
 * index番目のアイテムを削除する
 *------------------------------------------
 */
int buildin_delitem2(struct script_state *st)
{
	int idx,amount;
	int skip_egg = 0;
	struct map_session_data *sd = script_rid2sd(st);

	nullpo_retr(0, sd);

	idx = conv_num(st,& (st->stack->stack_data[st->start+2]));
	amount = conv_num(st,& (st->stack->stack_data[st->start+3]));
	if(st->end > st->start+4)
		skip_egg = conv_num(st,& (st->stack->stack_data[st->start+4]));

	if(idx < 0 || idx >= MAX_INVENTORY || amount <= 0)
		return 0;

	if(!skip_egg &&
	   sd->status.inventory[idx].nameid > 0 &&
	   sd->inventory_data[idx]->flag.pet_egg &&
	   sd->status.inventory[idx].amount > 0 &&
	   sd->status.inventory[idx].card[0] == (int)0xff00 &&
	   pet_search_data(sd->status.inventory[idx].nameid, PET_EGG) != NULL)
	{
		intif_delete_petdata(*((int *)(&sd->status.inventory[idx].card[1])));
	}

	if(sd->status.inventory[idx].amount >= amount)
		pc_delitem(sd,idx,amount,0,0);
	else
		pc_delitem(sd,idx,sd->status.inventory[idx].amount,0,0);

	return 0;
}

/*==========================================
 * index番目のアイテムをカートから削除する
 *------------------------------------------
 */
int buildin_delcartitem2(struct script_state *st)
{
	int idx,amount;
	int skip_egg = 0;
	struct map_session_data *sd = script_rid2sd(st);

	nullpo_retr(0, sd);

	idx = conv_num(st,& (st->stack->stack_data[st->start+2]));
	amount = conv_num(st,& (st->stack->stack_data[st->start+3]));
	if(st->end > st->start+4)
		skip_egg = conv_num(st,& (st->stack->stack_data[st->start+4]));

	if(idx < 0 || idx >= MAX_CART || amount <= 0)
		return 0;

	if(!skip_egg &&
	   sd->status.cart[idx].nameid > 0 &&
	   itemdb_search(sd->status.cart[idx].nameid)->flag.pet_egg &&
	   sd->status.cart[idx].amount > 0 &&
	   sd->status.cart[idx].card[0] == (int)0xff00 &&
	   pet_search_data(sd->status.cart[idx].nameid, PET_EGG) != NULL)
	{
		intif_delete_petdata(*((int *)(&sd->status.cart[idx].card[1])));
	}

	if(sd->status.cart[idx].amount >= amount)
		pc_cart_delitem(sd,idx,amount,!pc_iscarton(sd));
	else
		pc_cart_delitem(sd,idx,sd->status.cart[idx].amount,!pc_iscarton(sd));

	return 0;
}

/*==========================================
 * キャラ関係の装備取得
 *------------------------------------------
 */
int buildin_equippeditem(struct script_state *st)
{
	int id;
	struct map_session_data *sd;

	id=conv_num(st,& (st->stack->stack_data[st->start+2]));
	if( st->end>st->start+3 )
		sd=map_nick2sd(conv_str(st,& (st->stack->stack_data[st->start+3])));
	else
		sd=script_rid2sd(st);

	if(sd==NULL){
		push_val(st->stack,C_INT,0);
		return 0;
	}

	push_val(st->stack,C_INT,pc_equippeditem(sd,id));

	return 0;
}

// pc.cのequip_posと順番が異なることに注意
const unsigned int equip_pos[EQUIP_INDEX_MAX] = {
	LOC_HEAD2,
	LOC_BODY,
	LOC_LARM,
	LOC_RARM,
	LOC_ROBE,
	LOC_SHOES,
	LOC_RACCESSORY,
	LOC_LACCESSORY,
	LOC_HEAD3,
	LOC_HEAD,
	LOC_ARROW,
	LOC_COSTUME_HEAD2,
	LOC_COSTUME_HEAD3,
	LOC_COSTUME_HEAD,
	LOC_COSTUME_ROBE,
	LOC_COSTUME_FLOOR,
	LOC_ARMOR_SHADOW,
	LOC_WEAPON_SHADOW,
	LOC_SHIELD_SHADOW,
	LOC_SHOES_SHADOW,
	LOC_RACCESSORY_SHADOW,
	LOC_LACCESSORY_SHADOW
};

/*==========================================
 * 指定位置の装備品のIDを取得
 *------------------------------------------
 */
int buildin_getequipid(struct script_state *st)
{
	int num, i = -1;
	struct map_session_data *sd = script_rid2sd(st);

	num = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if(num > 0 && num <= EQUIP_INDEX_MAX)
		i = pc_checkequip(sd,equip_pos[num-1]);

	if(i >= 0) {
		if(sd->inventory_data[i]) {
			push_val(st->stack,C_INT,sd->inventory_data[i]->nameid);
			return 0;
		}
	}
	push_val(st->stack,C_INT,0);
	return 0;
}

/*==========================================
 * 装備名文字列（精錬メニュー用）
 *------------------------------------------
 */
int buildin_getequipname(struct script_state *st)
{
	int num = conv_num(st,& (st->stack->stack_data[st->start+2]));

	if(num > 0 && num <= EQUIP_INDEX_MAX) {
		struct map_session_data *sd = script_rid2sd(st);
		int i = pc_checkequip(sd,equip_pos[num-1]);
		char *buf;

		if(i >= 0 && sd->inventory_data[i]) {
			buf = (char *)aStrdup(sd->inventory_data[i]->jname);
		} else {
			int last = sizeof(refine_posword) / sizeof(refine_posword[0]);
			buf = (char *)aMalloc(sizeof(refine_posword[0]) * 2 + 4);
			sprintf(buf,"%s-[%s]",refine_posword[num-1],refine_posword[last-1]);
		}
		push_str(st->stack,C_STR,buf);
	} else {
		push_str(st->stack,C_CONSTSTR,"");
	}

	return 0;
}

/*==========================================
 * 装備チェック
 *------------------------------------------
 */
int buildin_getequipisequiped(struct script_state *st)
{
	int num, i = -1;
	struct map_session_data *sd;

	num=conv_num(st,& (st->stack->stack_data[st->start+2]));
	sd=script_rid2sd(st);

	if(num > 0 && num <= EQUIP_INDEX_MAX)
		i=pc_checkequip(sd,equip_pos[num-1]);
	if(i >= 0){
		push_val(st->stack,C_INT,1);
	}else{
		push_val(st->stack,C_INT,0);
	}

	return 0;
}

/*==========================================
 * 装備品精錬可能チェック
 *------------------------------------------
 */
int buildin_getequipisenableref(struct script_state *st)
{
	int num, i = -1;
	struct map_session_data *sd;

	num=conv_num(st,& (st->stack->stack_data[st->start+2]));
	sd=script_rid2sd(st);

	if(num > 0 && num <= EQUIP_INDEX_MAX)
		i=pc_checkequip(sd,equip_pos[num-1]);
	if(i >= 0 && sd->inventory_data[i] && sd->inventory_data[i]->refine != 0)
		push_val(st->stack,C_INT,1);
	else
		push_val(st->stack,C_INT,0);

	return 0;
}

/*==========================================
 * 装備品鑑定チェック
 *------------------------------------------
 */
int buildin_getequipisidentify(struct script_state *st)
{
	int num, i = -1;
	struct map_session_data *sd;

	num=conv_num(st,& (st->stack->stack_data[st->start+2]));
	sd=script_rid2sd(st);
	if(num > 0 && num <= EQUIP_INDEX_MAX)
		i=pc_checkequip(sd,equip_pos[num-1]);
	if(i >= 0)
		push_val(st->stack,C_INT,sd->status.inventory[i].identify);
	else
		push_val(st->stack,C_INT,0);

	return 0;
}

/*==========================================
 * 装備品精錬度
 *------------------------------------------
 */
int buildin_getequiprefinerycnt(struct script_state *st)
{
	int num = 0, i = -1;
	struct map_session_data *sd;

	if(st->end>st->start+2)
		num = conv_num(st,& (st->stack->stack_data[st->start+2]));

	sd=script_rid2sd(st);
	if(num > 0 && num <= EQUIP_INDEX_MAX)
		i=pc_checkequip(sd,equip_pos[num-1]);
	else
		i=sd->equip_index[current_equip_item_index];
	if(i >= 0)
		push_val(st->stack,C_INT,sd->status.inventory[i].refine);
	else
		push_val(st->stack,C_INT,0);

	return 0;
}

/*==========================================
 * 装備品武器LV
 *------------------------------------------
 */
int buildin_getequipweaponlv(struct script_state *st)
{
	int num, i = - 1;
	struct map_session_data *sd;

	num=conv_num(st,& (st->stack->stack_data[st->start+2]));
	sd=script_rid2sd(st);
	if(num > 0 && num <= EQUIP_INDEX_MAX)
		i=pc_checkequip(sd,equip_pos[num-1]);
	if(i >= 0 && sd->inventory_data[i])
		push_val(st->stack,C_INT,sd->inventory_data[i]->wlv);
	else
		push_val(st->stack,C_INT,0);

	return 0;
}

/*==========================================
 * 装備品精錬成功率
 *------------------------------------------
 */
int buildin_getequippercentrefinery(struct script_state *st)
{
	int num, i = -1;
	struct map_session_data *sd;

	num=conv_num(st,& (st->stack->stack_data[st->start+2]));
	sd=script_rid2sd(st);
	if(num > 0 && num <= EQUIP_INDEX_MAX)
		i=pc_checkequip(sd,equip_pos[num-1]);
	if(i >= 0)
		push_val(st->stack,C_INT,status_percentrefinery(sd,&sd->status.inventory[i]));
	else
		push_val(st->stack,C_INT,0);

	return 0;
}

/*==========================================
 * 装備品を削除する
 *------------------------------------------
 */
int buildin_delequip(struct script_state *st)
{
	struct map_session_data *sd=script_rid2sd(st);
	int i,num = -1;

	nullpo_retr(0, sd);

	if(st->end>st->start+2)
		num = conv_num(st,& (st->stack->stack_data[st->start+2]));

	if(num > 0 && num <= EQUIP_INDEX_MAX) {
		i = pc_checkequip(sd,equip_pos[num-1]);
		if(i >= 0)
			pc_delitem(sd,i,1,0,0);
	} else {
		for(i=0;i<EQUIP_INDEX_MAX;i++) {
			if(sd->equip_index[i] >= 0)
				pc_delitem(sd,sd->equip_index[i],1,0,0);
		}
	}
	return 0;
}

/*==========================================
 * 精錬成功
 *------------------------------------------
 */
int buildin_successrefitem(struct script_state *st)
{
	int num, i = -1;
	struct map_session_data *sd;

	num=conv_num(st,& (st->stack->stack_data[st->start+2]));
	sd=script_rid2sd(st);

	if(num > 0 && num <= EQUIP_INDEX_MAX)
		i=pc_checkequip(sd,equip_pos[num-1]);
	if(i >= 0) {
		int ep=sd->status.inventory[i].equip;
		pc_unequipitem(sd,i,1);
		skill_success_weaponrefine(sd,i);
		pc_equipitem(sd,i,ep);
	}

	return 0;
}

/*==========================================
 * 精錬失敗
 *------------------------------------------
 */
int buildin_failedrefitem(struct script_state *st)
{
	int num, i = -1;
	struct map_session_data *sd;

	num=conv_num(st,& (st->stack->stack_data[st->start+2]));
	sd=script_rid2sd(st);

	if(num > 0 && num <= EQUIP_INDEX_MAX)
		i=pc_checkequip(sd,equip_pos[num-1]);
	if(i >= 0)
		skill_fail_weaponrefine(sd,i);

	return 0;
}

/*==========================================
 * 精錬失敗
 *------------------------------------------
 */
int buildin_downrefitem(struct script_state *st)
{
	int num, cnt = 1, i = -1;
	struct map_session_data *sd;

	num=conv_num(st,& (st->stack->stack_data[st->start+2]));
	if(st->end > st->start+3)
		cnt=conv_num(st,& (st->stack->stack_data[st->start+3]));
	sd=script_rid2sd(st);

	if(num > 0 && num <= EQUIP_INDEX_MAX)
		i=pc_checkequip(sd,equip_pos[num-1]);
	if(i >= 0) {
		int ep=sd->status.inventory[i].equip;
		pc_unequipitem(sd,i,1);
		sd->status.inventory[i].refine -= cnt;
		if(sd->status.inventory[i].refine > MAX_REFINE)
			sd->status.inventory[i].refine = MAX_REFINE;
		if(sd->status.inventory[i].refine < 0)
			sd->status.inventory[i].refine = 0;

		clif_refine(sd->fd,2,i,sd->status.inventory[i].refine);
		clif_misceffect(&sd->bl,2);
		pc_equipitem(sd,i,ep);
	}

	return 0;
}

/*==========================================
 * 装備品の装備位置
 *------------------------------------------
 */
int buildin_getequippos(struct script_state *st)
{
	struct map_session_data *sd;
	int pos = 0, idx, i;

	sd  = script_rid2sd(st);
	idx = sd->equip_index[current_equip_item_index];
	if(sd->status.inventory[idx].equip) {
		for(i=0;i<EQUIP_INDEX_MAX;i++) {
			if(sd->status.inventory[idx].equip & equip_pos[i]) {
				pos = i + 1;
				break;
			}
		}
	}
	push_val(st->stack,C_INT,pos);

    return 0;
}

/*==========================================
 * アイテムによるスキル発動
 *------------------------------------------
 */
int buildin_itemskill(struct script_state *st)
{
	int id,lv,flag = 0;
	char *str;
	struct map_session_data *sd = script_rid2sd(st);
	struct script_data *data;

	nullpo_retr(0, sd);

	data = &(st->stack->stack_data[st->start+2]);
	get_val(st,data);
	if( isstr(data) ) {
		id = skill_get_name2id(conv_str(st,data));
	} else {
		id = conv_num(st,data);
	}
	lv  = conv_num(st,& (st->stack->stack_data[st->start+3]));
	str = conv_str(st,& (st->stack->stack_data[st->start+4]));
	if(st->end > st->start+5)
		flag = conv_num(st,& (st->stack->stack_data[st->start+5]));

	// 詠唱中にスキルアイテムは使用できない
	if(sd->ud.skilltimer != -1)
		return 0;

	sd->skill_item.id   = id;
	sd->skill_item.lv   = lv;
	sd->skill_item.flag = (flag)? 1: 0;
	clif_item_skill(sd,id,lv,str);

	return 0;
}

/*==========================================
 * アイテム作成
 *------------------------------------------
 */
int buildin_produce(struct script_state *st)
{
	struct map_session_data *sd=script_rid2sd(st);

	nullpo_retr(0, sd);

	if(sd->skill_menu.id == 0) {
		int trigger= conv_num(st,& (st->stack->stack_data[st->start+2]));
		clif_skill_produce_mix_list(sd,trigger,1,1);
	}
	return 0;
}

/*==========================================
 * カードの数を得る
 *------------------------------------------
 */
int buildin_getequipcardcnt(struct script_state *st)
{
	int num, i = -1;
	struct map_session_data *sd;

	num=conv_num(st,& (st->stack->stack_data[st->start+2]));
	sd=script_rid2sd(st);

	if(num > 0 && num <= EQUIP_INDEX_MAX)
		i=pc_checkequip(sd,equip_pos[num-1]);

	if(i >= 0) {
		int n,c=0;
		if(itemdb_isspecial(sd->status.inventory[i].card[0])){ // 製造・名前入りはカードなし
			push_val(st->stack,C_INT,0);
			return 0;
		}
		for(n=0; n<sd->inventory_data[i]->slot; n++) {
			int card_id = sd->status.inventory[i].card[n];
			if(card_id > 0 && itemdb_type(card_id) == ITEMTYPE_CARD)
				c++;
		}
		push_val(st->stack,C_INT,c);
		return 0;
	}
	push_val(st->stack,C_INT,0);
	return 0;
}

/*=================================================================
 * カード取り外し
 * type=0: 両方損失、1:カード損失、2:武具損失、3:損失無し、4:成功
 *-----------------------------------------------------------------
 */
static int removecards_sub(struct map_session_data *sd,int i,int typefail,int pos,bool preview)
{
	struct item item_tmp;
	int j,n,flag,removed_flag=0;
	int card_set[4] = { 0,0,0,0 };

	nullpo_retr(0, sd);

	if(i < 0 || i >= MAX_INVENTORY)
		return 0;
	if(itemdb_isspecial(sd->status.inventory[i].card[0]))	// 製造・名前入りは処理しない
		return 0;

	if(pos < 0)
		return 0;

	for(n=0,j=0; n < 4; n++) {
		int card_id = sd->status.inventory[i].card[n];
		if(card_id <= 0 || itemdb_type(card_id) != ITEMTYPE_CARD)
			continue;
		if((pos == 0 || pos-1 == n) && itemdb_cardtype(card_id) != 2) {	// 指定ポジションと一致かつhiddenではない場合
			removed_flag = 1;
			if(typefail == 2 || typefail == 4) {	// カード返却
				memset(&item_tmp, 0, sizeof(item_tmp));
				item_tmp.nameid = card_id;
				item_tmp.identify = 1;
				if( (flag = pc_additem(sd,&item_tmp,1,preview)) ) {	// 持てないならドロップ
					clif_additem(sd,0,0,flag);
					map_addflooritem(&item_tmp,1,sd->bl.m,sd->bl.x,sd->bl.y,0,0,0,0);
				}
			}
		} else {
			if(itemdb_cardtype(card_id) == 2)
				card_set[n] = card_id;	// 取り外し対象外のカードを保存
			else
				card_set[j++] = card_id;	// 取り外し対象外のカードを保存
		}
	}

	if(removed_flag) {
		if(typefail == 0 || typefail == 2) {		// 武具損失して終了
			pc_delitem(sd,i,1,0,2);
		}
		else if(typefail == 1 || typefail == 4) {	// 指定カードを取り除いたアイテム取得
			flag = 0;
			memset(&item_tmp, 0, sizeof(item_tmp));
			item_tmp.nameid    = sd->status.inventory[i].nameid;
			item_tmp.identify  = 1;
			item_tmp.refine    = sd->status.inventory[i].refine;
			item_tmp.attribute = sd->status.inventory[i].attribute;
			memcpy(&item_tmp.card, &card_set, sizeof(card_set));
			pc_delitem(sd,i,1,0,0);
			if( (flag=pc_additem(sd,&item_tmp,1,preview)) ) {	// 持てないならドロップ
				clif_additem(sd,0,0,flag);
				map_addflooritem(&item_tmp,1,sd->bl.m,sd->bl.x,sd->bl.y,0,0,0,0);
			}
		}
		return 1;	// 処理完了
	}
	return 0;
}

/*==========================================
 * カード取り外し成功
 *------------------------------------------
 */
int buildin_successremovecards(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int i=-1,num,pos=0;
	bool preview = false;

	nullpo_retr(0, sd);

	num = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if(num > 0 && num <= EQUIP_INDEX_MAX)
		i = pc_checkequip(sd,equip_pos[num-1]);

	if(st->end > st->start+3) {
		pos = conv_num(st,& (st->stack->stack_data[st->start+3]));
	}

	if(st->end > st->start+4) {
		preview = conv_num(st,& (st->stack->stack_data[st->start+4]));
	}

	if(removecards_sub(sd, i, 4, pos, preview)) {	// failtype=4とする
		// 成功エフェクト
		clif_misceffect2(&sd->bl,154);
	}
	return 0;
}

/*==========================================
 * カード取り外し失敗
 *------------------------------------------
 */
int buildin_failedremovecards(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int i=-1,num,typefail,pos=0;
	bool preview = false;

	nullpo_retr(0, sd);

	num = conv_num(st,& (st->stack->stack_data[st->start+2]));
	typefail = conv_num(st,& (st->stack->stack_data[st->start+3]));

	if(st->end > st->start+4)
		preview = conv_num(st,& (st->stack->stack_data[st->start+4]));

	if(typefail < 0 || typefail > 3)
		return 0;

	if(num > 0 && num <= EQUIP_INDEX_MAX)
		i = pc_checkequip(sd,equip_pos[num-1]);

	if(st->end > st->start+4)
		pos = conv_num(st,& (st->stack->stack_data[st->start+4]));

	if(removecards_sub(sd, i, typefail, pos, preview)) {
		// 失敗エフェクト
		clif_misceffect2(&sd->bl,155);
	}
	return 0;
}

/*==========================================
 * IDからItem名
 *------------------------------------------
 */
int buildin_getitemname(struct script_state *st)
{
	int item_id;
	struct item_data *item;

	item_id = conv_num(st,& (st->stack->stack_data[st->start+2]));

	item = itemdb_exists(item_id);
	if(item)
		push_str(st->stack,C_STR,(unsigned char *)aStrdup(item->jname));
	else
		push_str(st->stack,C_CONSTSTR,"");

	return 0;
}

/*==========================================
 * PCの所持品情報読み取り
 *------------------------------------------
 */
int buildin_getinventorylist(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int i,j=0;

	if(sd == NULL)
		return 0;

	for(i=0; i<MAX_INVENTORY && j<128; i++) {
		if(sd->status.inventory[i].nameid > 0 && sd->status.inventory[i].amount > 0) {
			pc_setreg(sd,add_str("@inventorylist_index")+(j<<24),i);
			pc_setreg(sd,add_str("@inventorylist_id")+(j<<24),sd->status.inventory[i].nameid);
			pc_setreg(sd,add_str("@inventorylist_amount")+(j<<24),sd->status.inventory[i].amount);
			pc_setreg(sd,add_str("@inventorylist_equip")+(j<<24),sd->status.inventory[i].equip);
			pc_setreg(sd,add_str("@inventorylist_refine")+(j<<24),sd->status.inventory[i].refine);
			pc_setreg(sd,add_str("@inventorylist_identify")+(j<<24),sd->status.inventory[i].identify);
			pc_setreg(sd,add_str("@inventorylist_attribute")+(j<<24),sd->status.inventory[i].attribute);
			pc_setreg(sd,add_str("@inventorylist_card1")+(j<<24),sd->status.inventory[i].card[0]);
			pc_setreg(sd,add_str("@inventorylist_card2")+(j<<24),sd->status.inventory[i].card[1]);
			pc_setreg(sd,add_str("@inventorylist_card3")+(j<<24),sd->status.inventory[i].card[2]);
			pc_setreg(sd,add_str("@inventorylist_card4")+(j<<24),sd->status.inventory[i].card[3]);
			pc_setreg(sd,add_str("@inventorylist_limit")+(j<<24),sd->status.inventory[i].limit);
			j++;
		}
	}
	pc_setreg(sd,add_str("@inventorylist_count"),j);
	return 0;
}

/*==========================================
 * PCのカート内所持品情報読み取り
 *------------------------------------------
 */
int buildin_getcartlist(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int i,j=0;

	if(sd == NULL)
		return 0;

	for(i=0; i<MAX_CART && j<128; i++) {
		if(sd->status.cart[i].nameid > 0 && sd->status.cart[i].amount > 0) {
			pc_setreg(sd,add_str("@cartlist_index")+(j<<24),i);
			pc_setreg(sd,add_str("@cartlist_id")+(j<<24),sd->status.cart[i].nameid);
			pc_setreg(sd,add_str("@cartlist_amount")+(j<<24),sd->status.cart[i].amount);
			pc_setreg(sd,add_str("@cartlist_refine")+(j<<24),sd->status.cart[i].refine);
			pc_setreg(sd,add_str("@cartlist_identify")+(j<<24),sd->status.cart[i].identify);
			pc_setreg(sd,add_str("@cartlist_attribute")+(j<<24),sd->status.cart[i].attribute);
			pc_setreg(sd,add_str("@cartlist_card1")+(j<<24),sd->status.cart[i].card[0]);
			pc_setreg(sd,add_str("@cartlist_card2")+(j<<24),sd->status.cart[i].card[1]);
			pc_setreg(sd,add_str("@cartlist_card3")+(j<<24),sd->status.cart[i].card[2]);
			pc_setreg(sd,add_str("@cartlist_card4")+(j<<24),sd->status.cart[i].card[3]);
			pc_setreg(sd,add_str("@cartlist_limit")+(j<<24),sd->status.cart[i].limit);
			j++;
		}
	}
	pc_setreg(sd,add_str("@cartlist_count"),j);
	return 0;
}

/*==========================================
 * アイテムの全削除
 *------------------------------------------
 */
int buildin_clearitem(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int i;

	if(sd == NULL)
		return 0;
	for (i=0; i<MAX_INVENTORY; i++) {
		if (sd->status.inventory[i].amount) {
			if (sd->status.inventory[i].card[0] == (int)0xff00)
				intif_delete_petdata(*((int *)(&sd->status.inventory[i].card[1])));
			pc_delitem(sd, i, sd->status.inventory[i].amount, 0, 0);
		}
	}
	return 0;
}

/*==========================================
 * カート内アイテムの全削除
 *------------------------------------------
 */
int buildin_clearcartitem(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int i;

	if(sd == NULL)
		return 0;
	for (i=0; i<MAX_CART; i++) {
		if (sd->status.cart[i].amount) {
			if (sd->status.cart[i].card[0] == (int)0xff00)
				intif_delete_petdata(*((int *)(&sd->status.cart[i].card[1])));
			pc_cart_delitem(sd, i, sd->status.cart[i].amount, !pc_iscarton(sd));
		}
	}
	return 0;
}

/*==========================================
 * 修理可能アイテムを数える
 *------------------------------------------
 */
int buildin_getrepairableitemcount(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int c = 0;

	if(sd) {
		int i;
		for(i=0;i<MAX_INVENTORY;i++) {
			if(sd->status.inventory[i].nameid > 0 && sd->status.inventory[i].amount > 0 && sd->status.inventory[i].attribute){
				c++;
			}
		}
	}
	push_val(st->stack,C_INT,c);
	return 0;
}

/*==========================================
 * 修理可能アイテムを修理する
 *------------------------------------------
 */
int buildin_repairitem(struct script_state *st)
{
	struct map_session_data *sd=script_rid2sd(st);

	if(sd) {
		int i, c = 0;

		for(i=0;i<MAX_INVENTORY;i++) {
			if(sd->status.inventory[i].nameid > 0 && sd->status.inventory[i].amount > 0 && sd->status.inventory[i].attribute){
				sd->status.inventory[i].attribute = 0;
				c++;
			}
		}
		if(c > 0) {
			clif_itemlist(sd);
			clif_equiplist(sd);
		}
	}
	return 0;
}

/*==========================================
 * 指定IDのカードを付けた武具がないか検査(あったら1,無ければ0を返す)
 *------------------------------------------
 */
int buildin_checkequipedcard(struct script_state *st)
{
	struct map_session_data *sd=script_rid2sd(st);
	int c;

	c=conv_num(st,& (st->stack->stack_data[st->start+2]));

	if(sd){
		int n,i;
		for(i=0;i<MAX_INVENTORY;i++){
			if(sd->status.inventory[i].nameid > 0 && sd->status.inventory[i].amount){
				if(itemdb_isspecial(sd->status.inventory[i].card[0]))
					continue;
				for(n=0;n<4;n++){
					if(sd->status.inventory[i].card[n]==c){
						push_val(st->stack,C_INT,1);
						return 0;
					}
				}
			}
		}
	}
	push_val(st->stack,C_INT,0);
	return 0;
}

/*==========================================
 * 武装解除
 *------------------------------------------
 */
int buildin_unequip(struct script_state *st)
{
	struct map_session_data *sd=script_rid2sd(st);
	int i,num = -1;

	nullpo_retr(0, sd);

	if( st->end>st->start+2 )
		num = conv_num(st,& (st->stack->stack_data[st->start+2]));

	if( num > 0 && num <= EQUIP_INDEX_MAX ) {
		i = pc_checkequip(sd,equip_pos[num-1]);
		if(i >= 0)
			pc_unequipitem(sd,i,0);
	} else {
		int max = EQUIP_INDEX_MAX;
		if(num == -3)
			max = EQUIP_INDEX_ARMOR_SHADOW;
		else if(num == -2)
			max = EQUIP_INDEX_COSTUME_HEAD;
		for(i=0;i<max;i++) {
			if(sd->equip_index[i] >= 0 )
				pc_unequipitem(sd,sd->equip_index[i],0);
		}
	}
	return 0;
}

/*==========================================
 * アイテム使用許可
 *------------------------------------------
 */
int buildin_allowuseitem(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int i = 0;

	nullpo_retr(0, sd);

	if(st->end > st->start+2) {
		struct script_data *data = &(st->stack->stack_data[st->start+2]);

		get_val(st,data);
		if( isstr(data) ) {
			const char *name = conv_str(st,data);
			struct item_data *item_data = itemdb_searchname(name);
			if(item_data)
				i = item_data->nameid;
			else
				i = -1;
		} else {
			i = conv_num(st,data);
		}
	}
	sd->npc_allowuseitem = i;
	return 0;
}

/*==========================================
 * アイテム使用時、使ったアイテムのIDや製作者IDを返す
 * usediteminfo flag; 0=使用アイテムID 1=製作者ID
 *------------------------------------------
 */
int buildin_usediteminfo(struct script_state *st)
{
	struct map_session_data *sd;
	int flag=conv_num(st,& (st->stack->stack_data[st->start+2]));
	int ret;

	if((sd=script_rid2sd(st))==NULL){
		push_val(st->stack,C_INT,-1);
		return -1;
	}
	if(flag==0)
		ret = sd->use_itemid;
	else
		ret = sd->use_nameditem;
	push_val(st->stack,C_INT,ret);
	return 0;
}

/*==========================================
 * アイテム名からIDを取得
 *------------------------------------------
 */
int buildin_getitemid(struct script_state *st)
{
	struct item_data *item_data;
	char *item_name = conv_str(st,& (st->stack->stack_data[st->start+2]));

	item_data = itemdb_searchname(item_name);

	push_val(st->stack,C_INT,(item_data ? item_data->nameid: -1));
	return 0;
}

/*==========================================
 * アイテムドロップ
 *------------------------------------------
 */
int buildin_dropitem(struct script_state *st)
{
	int nameid=0, flag=0, amount;
	int x,y,m,tick;
	unsigned int limit = 0;
	char *str;
	struct script_data *data;

	str = conv_str(st,& (st->stack->stack_data[st->start+2]));
	x   = conv_num(st,& (st->stack->stack_data[st->start+3]));
	y   = conv_num(st,& (st->stack->stack_data[st->start+4]));

	data = &(st->stack->stack_data[st->start+5]);
	get_val(st,data);
	if(isstr(data)) {
		const char *name = conv_str(st,data);
		struct item_data *item_data = itemdb_searchname(name);
		if(item_data)
			nameid = item_data->nameid;
	} else {
		nameid = conv_num(st,data);
	}

	amount = conv_num(st,& (st->stack->stack_data[st->start+6]));
	tick   = conv_num(st,& (st->stack->stack_data[st->start+7]));
	if(st->end > st->start+8)
		limit = (unsigned int)conv_num(st,& (st->stack->stack_data[st->start+8]));

	m = script_mapname2mapid(st,str);
	if(m < 0)
		return 0;

	if(nameid < 0) {
		nameid = itemdb_searchrandomid(-nameid);
		flag   = 1;
	}

	if(nameid > 0) {
		struct item item_tmp;
		memset(&item_tmp,0,sizeof(item_tmp));
		item_tmp.nameid = nameid;
		if(!flag)
			item_tmp.identify = 1;
		else
			item_tmp.identify = !itemdb_isequip3(nameid);

		item_tmp.limit = (limit > 0)? (unsigned int)time(NULL) + limit: 0;
		battle_config.flooritem_lifetime += tick;
		map_addflooritem(&item_tmp,amount,m,x,y,0,0,0,0);
		battle_config.flooritem_lifetime -= tick;
	}

	return 0;
}

/*==========================================
 * アイテムドロップ
 *------------------------------------------
 */
int buildin_dropitem2(struct script_state *st)
{
	int nameid=0, i=0, amount;
	int x,y,m,tick;
	int iden,ref,attr,c1,c2,c3,c4;
	unsigned int limit = 0;
	char *str;
	struct script_data *data;
	struct item_data *item_data;
	struct item item_tmp;

	str = conv_str(st,& (st->stack->stack_data[st->start+2]));
	x   = conv_num(st,& (st->stack->stack_data[st->start+3]));
	y   = conv_num(st,& (st->stack->stack_data[st->start+4]));

	data = &(st->stack->stack_data[st->start+5]);
	get_val(st,data);
	if(isstr(data)) {
		const char *name = conv_str(st,data);
		struct item_data *item_data = itemdb_searchname(name);
		if(item_data)
			nameid = item_data->nameid;
	} else {
		nameid = conv_num(st,data);
	}

	amount = conv_num(st,& (st->stack->stack_data[st->start+6]));
	tick   = conv_num(st,& (st->stack->stack_data[st->start+7]));
	iden   = conv_num(st,& (st->stack->stack_data[st->start+8]));
	ref    = conv_num(st,& (st->stack->stack_data[st->start+9]));
	attr   = conv_num(st,& (st->stack->stack_data[st->start+10]));
	c1     = conv_num(st,& (st->stack->stack_data[st->start+11]));
	c2     = conv_num(st,& (st->stack->stack_data[st->start+12]));
	c3     = conv_num(st,& (st->stack->stack_data[st->start+13]));
	c4     = conv_num(st,& (st->stack->stack_data[st->start+14]));
	if(st->end > st->start+15)
		limit = (unsigned int)conv_num(st,& (st->stack->stack_data[st->start+15]));

	m = script_mapname2mapid(st,str);
	if(m < 0)
		return 0;

	do {
		memset(&item_tmp,0,sizeof(item_tmp));

		if(nameid < 0)		// ランダム
			item_tmp.nameid = itemdb_searchrandomid(-nameid);
		else
			item_tmp.nameid = nameid;

		if(!itemdb_exists(item_tmp.nameid))
			break;

		item_data = itemdb_search(item_tmp.nameid);

		if(itemdb_isarmor(item_data->nameid) || itemdb_isweapon(item_data->nameid)) {
			if(ref > MAX_REFINE)
				ref = MAX_REFINE;
		} else if(item_data->flag.pet_egg) {
			iden = 1;
			ref = 0;
		} else {
			iden = 1;
			ref = attr = 0;
		}

		if(iden || battle_config.itemidentify)
			item_tmp.identify = 1;
		else
			item_tmp.identify = !itemdb_isequip3(item_tmp.nameid);

		item_tmp.refine    = ref;
		item_tmp.attribute = attr;
		item_tmp.card[0]   = c1;
		item_tmp.card[1]   = c2;
		item_tmp.card[2]   = c3;
		item_tmp.card[3]   = c4;
		item_tmp.limit     = (limit > 0)? (unsigned int)time(NULL) + limit: 0;

		battle_config.flooritem_lifetime += tick;
		map_addflooritem(&item_tmp,amount,m,x,y,0,0,0,0);
		battle_config.flooritem_lifetime -= tick;
	} while(nameid < 0 && ++i < amount);	// ランダム系はアイテムの再抽選

	return 0;
}

/*==========================================
 * アイテムデータ取得
 *------------------------------------------
 */
int buildin_getiteminfo(struct script_state *st)
{
	int num, val = -1;
	char *str = NULL;
	struct script_data *data;
	struct item_data *item = NULL;

	data = &(st->stack->stack_data[st->start+2]);
	get_val(st,data);
	if( isstr(data) ) {
		const char *name = conv_str(st,data);
		item = itemdb_searchname(name);
	} else {
		int nameid = conv_num(st,data);
		item = itemdb_exists(nameid);
	}
	num = conv_num(st,& (st->stack->stack_data[st->start+3]));

	if(item) {
		switch(num) {
			case 0:  val = item->nameid;           break;
			case 1:  str = item->name;             break;
			case 2:  str = item->jname;            break;
			case 3:  val = item->type;             break;
			case 4:  val = item->value_buy;        break;
			case 5:  val = item->value_sell;       break;
			case 6:  val = item->weight;           break;
			case 7:  val = item->atk;              break;
			case 8:  val = item->def;              break;
			case 9:  val = item->range;            break;
			case 10: val = item->slot;             break;
			case 11: val = item->class_;           break;
			case 12: val = item->sex;              break;
			case 13: val = item->equip;            break;
			case 14: val = item->wlv;              break;
			case 15: val = item->elv;              break;
			case 16: val = item->look;             break;
			case 17: val = item->refine;           break;
			case 18: val = item->upper;            break;
			case 19: val = item->zone;             break;
			case 20: val = item->flag.dropable;    break;
			case 21: val = item->flag.storageable; break;
			case 22: val = item->flag.cartable;    break;
			case 23: val = item->delay;            break;
			case 24: val = item->flag.available;   break;
			case 25: val = item->flag.value_notdc; break;
			case 26: val = item->flag.value_notoc; break;
			case 27: val = item->group;            break;
			case 28: val = item->arrow_type;       break;
			case 29: str = item->cardillustname;   break;
			case 30: val = item->flag.buyingable;  break;
			case 31: val = item->flag.nonconsume;  break;
			case 32: val = item->flag.sellable;    break;
			case 33: val = item->flag.guildstorageable; break;
		}
	}
	if(str)
		push_str(st->stack,C_STR,(unsigned char *)aStrdup(str));
	else
		push_val(st->stack,C_INT,val);
	return 0;
}

/*==========================================
 * アイテムが活性化状態か
 *------------------------------------------
 */
int buildin_checkactiveitem(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int id, flag = 0;

	if(st->end > st->start+2)
		id = conv_num(st,& (st->stack->stack_data[st->start+2]));
	else
		id = current_equip_name_id;

	if(sd) {
		int i;
		for(i = 0; i < sd->activeitem.count; i++) {
			if(sd->activeitem_id2[i] == id && sd->activeitem_timer[i] != -1) {
				flag |= sd->activeitem.flag[i];
			}
		}
	}
	push_val(st->stack,C_INT,flag);

	return 0;
}

/*==========================================
 * 装備の指定スロットのカード取得
 *------------------------------------------
 */
int buildin_getequipcardid(struct script_state *st)
{
	int num, pos, i = -1;
	struct map_session_data *sd;

	num = conv_num(st,& (st->stack->stack_data[st->start+2]));
	pos = conv_num(st,& (st->stack->stack_data[st->start+3]));
	sd  = script_rid2sd(st);

	if(num > 0 && num <= EQUIP_INDEX_MAX)
		i=pc_checkequip(sd,equip_pos[num-1]);
	if(pos < 0 || pos >= 4)
		pos = 0;

	if(i >= 0) {
		int card_id;
		if(itemdb_isspecial(sd->status.inventory[i].card[0])){ // 製造・名前入りはカードなし
			push_val(st->stack,C_INT,0);
			return 0;
		}
		card_id = sd->status.inventory[i].card[pos];
		if(card_id > 0 && itemdb_type(card_id) == ITEMTYPE_CARD) {
			push_val(st->stack,C_INT,card_id);
			return 0;
		}
	}
	push_val(st->stack,C_INT,0);
	return 0;
}

/*==========================================
 * 装備の指定スロットのカード付与
 *------------------------------------------
 */
int buildin_setequipcardid(struct script_state *st)
{
	int num, pos, card_id, i = -1;
	int flag = 0;
	struct map_session_data *sd;

	num = conv_num(st,& (st->stack->stack_data[st->start+2]));
	pos = conv_num(st,& (st->stack->stack_data[st->start+3]));
	card_id = conv_num(st,& (st->stack->stack_data[st->start+4]));
	if(st->end > st->start+5)
		flag = conv_num(st,& (st->stack->stack_data[st->start+5]));
	sd  = script_rid2sd(st);

	if(num > 0 && num <= EQUIP_INDEX_MAX)
		i=pc_checkequip(sd,equip_pos[num-1]);
	if(pos < 0 || pos >= 4)
		pos = 0;

	if(i >= 0) {
		int ep=sd->status.inventory[i].equip;
		if(itemdb_isspecial(sd->status.inventory[i].card[0])) // 製造・名前入りは不可
			return 0;
		if(card_id && itemdb_type(card_id) != ITEMTYPE_CARD) // カードタイプ以外は不可
			return 0;

		pc_unequipitem(sd,i,0);
		sd->status.inventory[i].card[pos] = card_id;

		if(flag & 4)
			sd->status.inventory[i].refine = 0;
		if(flag & 2)
			clif_item_preview(sd,i);
		clif_equiplist(sd);
		if(flag & 1)
			pc_equipitem(sd,i,ep);
	}
	return 0;
}
