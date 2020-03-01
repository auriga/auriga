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

#include "db.h"
#include "timer.h"
#include "socket.h"
#include "nullpo.h"
#include "malloc.h"
#include "utils.h"

#include "pc.h"
#include "map.h"
#include "path.h"
#include "intif.h"
#include "clif.h"
#include "chrif.h"
#include "pet.h"
#include "itemdb.h"
#include "battle.h"
#include "mob.h"
#include "npc.h"
#include "script.h"
#include "status.h"
#include "storage.h"
#include "unit.h"
#include "skill.h"
#include "achieve.h"

#define MIN_PETTHINKTIME 100

struct pet_db pet_db[MAX_PET_DB];
static int pet_count;

/*==========================================
 * ペットDBの検索
 *------------------------------------------
 */
static int pet_search_index(int key, int type)
{
	int i;

	for(i=0; i<pet_count; i++) {
		if(pet_db[i].class_ <= 0)
			continue;
		switch(type) {
			case PET_CLASS:
				if(pet_db[i].class_ == key)
					return i;
				break;
			case PET_CATCH:
				if(pet_db[i].itemID == key)
					return i;
				break;
			case PET_EGG:
				if(pet_db[i].EggID == key)
					return i;
				break;
			case PET_EQUIP:
				if(pet_db[i].AcceID == key)
					return i;
				break;
			case PET_FOOD:
				if(pet_db[i].FoodID == key)
					return i;
				break;
			default:
				return -1;
		}
	}
	return -1;
}

/*==========================================
 * ペットDBを返す
 *------------------------------------------
 */
struct pet_db* pet_search_data(int key, int type)
{
	int idx = pet_search_index(key, type);

	if(idx >= 0)
		return &pet_db[idx];

	return NULL;
}

/*==========================================
 *
 *------------------------------------------
 */
static int pet_performance_val(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	if(sd->pet.intimate > 900)
		return (sd->petDB->s_perfor > 0)? 4: 3;
	if(sd->pet.intimate > 750)
		return 2;

	return 1;
}

/*==========================================
 *
 *------------------------------------------
 */
int pet_hungry_val(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	if(sd->pet.hungry > 90)
		return 4;
	if(sd->pet.hungry > 75)
		return 3;
	if(sd->pet.hungry > 25)
		return 2;
	if(sd->pet.hungry > 10)
		return 1;

	return 0;
}

/*==========================================
 * ペットの攻撃対象決定
 *------------------------------------------
 */
int pet_target_check(struct map_session_data *sd,struct block_list *bl,int type)
{
	struct pet_data *pd;

	nullpo_retr(0, sd);
	nullpo_retr(0, pd = sd->pd);

	if(bl == NULL || bl->type != BL_MOB)
		return 0;

	if(sd->pet.intimate > 900 && sd->pet.hungry > 0 && pd->class_ != status_get_class(bl) &&
	   pd->ud.skilltimer == -1 && pd->ud.attacktimer == -1)
	{
		struct mob_data *md = (struct mob_data *)bl;
		int rate;

		if(md) {
			int mode = mobdb_search(pd->class_)->mode;
			int race = mobdb_search(pd->class_)->race;
			if(pd->bl.m != md->bl.m || md->bl.prev == NULL || path_distance(pd->bl.x,pd->bl.y,md->bl.x,md->bl.y) > 13)
				return 0;
			if(mobdb_search(pd->class_)->mexp <= 0 && !(mode&MD_BOSS) && (md->sc.option & (OPTION_HIDE | OPTION_CLOAKING) && race != RCT_INSECT && race != RCT_DEMON) )
				return 0;
		}
		if(!type) {
			rate = sd->petDB->attack_rate * (150 - (sd->pet.intimate - 1000)) / 100;
			if(battle_config.pet_support_rate != 100)
				rate = rate * battle_config.pet_support_rate / 100;
			if(sd->petDB->attack_rate > 0 && rate <= 0)
				rate = 1;
		} else {
			rate = sd->petDB->defence_attack_rate * (150 - (sd->pet.intimate - 1000)) / 100;
			if(battle_config.pet_support_rate != 100)
				rate = rate * battle_config.pet_support_rate / 100;
			if(sd->petDB->defence_attack_rate > 0 && rate <= 0)
				rate = 1;
		}
		if(atn_rand()%10000 < rate) {
			if(pd->target_id == 0 || atn_rand()%10000 < sd->petDB->change_target_rate) {
				pd->target_id = bl->id;
			}
		}
	}
	return 0;
}

/*==========================================
 * エサをあげる
 *------------------------------------------
 */
static int pet_food(struct map_session_data *sd)
{
	int i, t;

	nullpo_retr(1, sd);
	nullpo_retr(1, sd->pd);

	if(sd->petDB == NULL)
		return 1;
	i = pc_search_inventory(sd,sd->petDB->FoodID);
	if(i < 0) {
		clif_pet_food(sd,sd->petDB->FoodID,0);
		return 1;
	}
	pc_delitem(sd,i,1,0,0);
	t = sd->pet.intimate;

	if(sd->pet.hungry > 90) {
		sd->pet.intimate -= sd->petDB->r_full;
	} else {
		int k;

		if(battle_config.pet_friendly_rate != 100)
			k = sd->petDB->r_hungry * battle_config.pet_friendly_rate / 100;
		else
			k = sd->petDB->r_hungry;
		if(sd->pet.hungry > 75) {
			k /= 2;
			if(k <= 0)
				k = 1;
		}
		sd->pet.intimate += k;
	}
	if(sd->pet.intimate <= 0) {
		sd->pet.intimate = 0;
		if(battle_config.pet_status_support && t > 0) {
			if(sd->bl.prev != NULL)
				status_calc_pc(sd,0);
			else
				status_calc_pc(sd,2);
		}
	} else if(sd->pet.intimate > 1000) {
		sd->pet.intimate = 1000;
	}

	sd->pet.hungry += sd->petDB->fullness;
	if(sd->pet.hungry > 100)
		sd->pet.hungry = 100;

	clif_send_petdata(sd,2,sd->pet.hungry);
	clif_send_petdata(sd,1,sd->pet.intimate);
	clif_pet_food(sd,sd->petDB->FoodID,1);

	achieve_update_content(sd, ACH_PET_FRIEND, sd->pd->class_, sd->pet.intimate);

	return 0;
}

/*==========================================
 * 腹減り
 *------------------------------------------
 */
static int pet_hungry_timer(int tid,unsigned int tick,int id,void *data)
{
	struct map_session_data *sd = map_id2sd(id);
	int interval, t;

	if(sd == NULL)
		return 1;

	if(!sd->status.pet_id || !sd->pd || !sd->petDB)
		return 1;

	if(sd->pd->hungry_timer != tid) {
		if(battle_config.error_log)
			printf("pet_hungry_timer %d != %d\n",sd->pd->hungry_timer,tid);
		return 0;
	}
	sd->pd->hungry_timer = -1;
	sd->pet.hungry--;

	if(battle_config.enable_pet_autofeed > 0) {
		if(sd->pet.hungry <= 25 && 
			(battle_config.enable_pet_autofeed == 1 && sd->status.autofeed&1) || battle_config.enable_pet_autofeed >= 2
		) {
			pet_food(sd);
		}
	}

	t = sd->pet.intimate;

	if(sd->pet.hungry < 0) {
		if(sd->pd->target_id > 0)
			unit_stopattack(&sd->pd->bl);
		sd->pet.hungry = 0;
		sd->pet.intimate -= battle_config.pet_hungry_friendly_decrease;
		if(sd->pet.intimate <= 0) {
			sd->pet.intimate = 0;
			if(battle_config.pet_status_support && t > 0) {
				if(sd->bl.prev != NULL)
					status_calc_pc(sd,0);
				else
					status_calc_pc(sd,2);
			}
		}
		clif_send_petdata(sd,1,sd->pet.intimate);
	}
	clif_send_petdata(sd,2,sd->pet.hungry);

	if(battle_config.pet_hungry_delay_rate != 100)
		interval = sd->petDB->hungry_delay * battle_config.pet_hungry_delay_rate / 100;
	else
		interval = sd->petDB->hungry_delay;
	if(interval <= 0)
		interval = 1;
	sd->pd->hungry_timer = add_timer(tick+interval,pet_hungry_timer,sd->bl.id,NULL);

	return 0;
}

/*==========================================
 * 腹減りタイマー削除
 *------------------------------------------
 */
int pet_hungry_timer_delete(struct pet_data *pd)
{
	nullpo_retr(0, pd);

	if(pd->hungry_timer != -1) {
		delete_timer(pd->hungry_timer,pet_hungry_timer);
		pd->hungry_timer = -1;
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
static int pet_data_init(struct map_session_data *sd)
{
	struct pet_data *pd;
	struct pet_db *db;
	int interval;
	unsigned int tick = gettick();

	nullpo_retr(1, sd);

	if(sd->pd)
		return 1;

	if(sd->status.account_id != sd->pet.account_id || sd->status.char_id != sd->pet.char_id || sd->status.pet_id != sd->pet.pet_id) {
		sd->status.pet_id = 0;
		return 1;
	}

	db = pet_search_data(sd->pet.class_, PET_CLASS);
	if(db == NULL) {
		sd->status.pet_id = 0;
		return 1;
	}
	sd->petDB = db;
	sd->pd = pd = (struct pet_data *)aCalloc(1,sizeof(struct pet_data));

	pd->bl.m    = sd->bl.m;
	pd->bl.prev = pd->bl.next = NULL;
	pd->bl.x    = pd->ud.to_x = sd->bl.x;
	pd->bl.y    = pd->ud.to_y = sd->bl.y;
	unit_calc_pos(&pd->bl,sd->bl.x,sd->bl.y,sd->dir,2);
	pd->bl.x  = pd->ud.to_x;
	pd->bl.y  = pd->ud.to_y;
	pd->bl.id = npc_get_new_npc_id();
	memcpy(pd->name,sd->pet.name,24);
	pd->class_ = sd->pet.class_;
	pd->equip  = sd->pet.equip;
	pd->dir    = sd->dir;
	if(battle_config.pet_speed_is_same_as_pc == 1)
		pd->speed = status_get_speed(&sd->bl);
	else
		pd->speed = sd->petDB->speed;
	pd->bl.type         = BL_PET;
	pd->target_id       = 0;
	pd->move_fail_count = 0;
	pd->next_walktime   = tick;
	pd->last_thinktime  = tick;
	pd->msd             = sd;

	unit_dataset(&pd->bl);
	map_addiddb(&pd->bl);

	if(battle_config.pet_hungry_delay_rate != 100)
		interval = sd->petDB->hungry_delay * battle_config.pet_hungry_delay_rate / 100;
	else
		interval = sd->petDB->hungry_delay;
	if(interval <= 0)
		interval = 1;
	pd->hungry_timer = add_timer(tick+interval,pet_hungry_timer,sd->bl.id,NULL);
	pd->lootitem = (struct item *)aCalloc(LOOTITEM_SIZE,sizeof(struct item));
	pd->loottype = (!battle_config.pet_lootitem)? 0: battle_config.petowneditem;
	pd->lootitem_count  = 0;
	pd->lootitem_weight = 0;
	pd->lootitem_timer  = tick;
	pd->view_size       = mobdb_search(pd->class_)->view_size;

	return 0;
}

/*==========================================
 * 孵化
 *------------------------------------------
 */
static int pet_birth_process(struct map_session_data *sd)
{
	nullpo_retr(1, sd);

	if(sd->status.pet_id && sd->pet.incubate == 1) {
		sd->status.pet_id = 0;
		return 1;
	}

	sd->pet.incubate   = 0;
	sd->pet.account_id = sd->status.account_id;
	sd->pet.char_id    = sd->status.char_id;
	sd->status.pet_id  = sd->pet.pet_id;

	if(pet_data_init(sd)) {
		sd->status.pet_id  = 0;
		sd->pet.incubate   = 1;
		sd->pet.account_id = 0;
		sd->pet.char_id    = 0;
		return 1;
	}

	intif_save_petdata(sd->status.account_id,&sd->pet);
	chrif_save(sd,0);
	if(sd->state.storage_flag == 1)
		storage_storage_save(sd);

	map_addblock(&sd->pd->bl);
	clif_spawnpet(sd->pd);
	clif_send_petdata(sd,0,0);
#if PACKETVER >= 20180704
	clif_send_petdata(sd,6,1);
#endif
	clif_send_pethair(sd);
	clif_pet_equip(sd->pd,sd->pet.equip);
	clif_send_petstatus(sd);

	return 0;
}

/*==========================================
 * interから情報取得
 *------------------------------------------
 */
int pet_recv_petdata(int account_id,struct s_pet *p,int flag)
{
	struct map_session_data *sd = map_id2sd(account_id);

	if(sd == NULL)
		return 1;
	if(flag == 1) {
		sd->status.pet_id = 0;
		return 1;
	}
	memcpy(&sd->pet,p,sizeof(struct s_pet));
	if(sd->pet.incubate == 1) {
		pet_birth_process(sd);
	} else {
		pet_data_init(sd);
		if(sd->pd && sd->bl.prev != NULL) {
			map_addblock(&sd->pd->bl);
			clif_spawnpet(sd->pd);
			clif_send_petdata(sd,0,0);
			clif_send_pethair(sd);
			//clif_pet_equip(sd->pd,sd->pet.equip);
			clif_send_petstatus(sd);
		}
	}
	if(battle_config.pet_status_support && sd->pet.intimate > 0) {
		if(sd->bl.prev != NULL)
			status_calc_pc(sd,0);
		else
			status_calc_pc(sd,2);
	}

	return 0;
}

/*==========================================
 * ペットの卵を選択
 *------------------------------------------
 */
int pet_select_egg(struct map_session_data *sd,short egg_index)
{
	nullpo_retr(0, sd);

	if(egg_index < 0 || egg_index >= MAX_INVENTORY)
		return 0;

	if(sd->status.inventory[egg_index].card[0] == (short)0xff00) {
		intif_request_petdata(sd->status.account_id,sd->status.char_id,*((int *)&sd->status.inventory[egg_index].card[1]));
	} else {
		if(battle_config.error_log)
			printf("wrong egg item inventory %d\n",egg_index);
	}
	pc_delitem(sd,egg_index,1,0,0);

	return 0;
}

/*==========================================
 * 捕獲要求
 *------------------------------------------
 */
int pet_catch_process1(struct map_session_data *sd,int target_class)
{
	nullpo_retr(0, sd);

	sd->catch_target_class = target_class;
	clif_catch_process(sd);

	return 0;
}

/*==========================================
 * ルーレット
 *------------------------------------------
 */
int pet_catch_process2(struct map_session_data *sd,int target_id)
{
	struct mob_data *md;
	struct pet_db *db;
	int pet_catch_rate;

	nullpo_retr(1, sd);

	md = map_id2md(target_id);
	if(md == NULL || md->bl.prev == NULL) {
		clif_pet_rulet(sd,0);
		return 1;
	}

	// target_idによる敵→卵判定
	db = pet_search_data(md->class_,PET_CLASS);
	if(db == NULL || sd->catch_target_class != md->class_) {
		clif_pet_rulet(sd,0);
		return 1;
	}

	pet_catch_rate = (db->capture + (sd->status.base_level - mobdb_search(md->class_)->lv) * 30 + sd->paramc[5] * 20) * (200 - md->hp * 100 / mobdb_search(md->class_)->max_hp) / 100;
	if(pet_catch_rate < 1)
		pet_catch_rate = 1;
	if(battle_config.pet_catch_rate != 100)
		pet_catch_rate = pet_catch_rate * battle_config.pet_catch_rate / 100;

	if(atn_rand()%10000 < pet_catch_rate) {
		// 成功
		unit_remove_map(&md->bl,0,0);
		clif_pet_rulet(sd,1);
		intif_create_pet(
			sd->status.account_id,sd->status.char_id,db->class_,mobdb_search(db->class_)->lv,
			db->EggID,0,db->intimate,100,0,1,md->name
		);
	} else {
		// 失敗
		clif_pet_rulet(sd,0);
	}

	return 0;
}

/*==========================================
 * 捕獲成功
 *------------------------------------------
 */
int pet_get_egg(int account_id,int pet_id,int flag)
{
	struct map_session_data *sd;
	struct pet_db *db;

	if(flag)
		return 0;

	sd = map_id2sd(account_id);
	if(sd == NULL)
		return 1;

	db = pet_search_data(sd->catch_target_class,PET_CLASS);
	if(db) {
		struct item tmp_item;
		int ret;

		memset(&tmp_item,0,sizeof(tmp_item));
		tmp_item.nameid   = db->EggID;
		tmp_item.identify = 1;
		tmp_item.card[0]  = (short)0xff00;
		*((int *)(&tmp_item.card[1])) = pet_id;
		tmp_item.card[3]  = sd->pet.rename_flag;

		if((ret = pc_additem(sd,&tmp_item,1))) {
			clif_additem(sd,0,0,ret);
			map_addflooritem(&tmp_item,1,sd->bl.m,sd->bl.x,sd->bl.y,0,0,0,0);
		}
		achieve_update_content(sd, ACH_TAMING, sd->catch_target_class, 1);
	} else {
		intif_delete_petdata(pet_id);
	}

	return 0;
}

/*==========================================
 * パフォーマンス
 *------------------------------------------
 */
static int pet_performance(struct map_session_data *sd)
{
	struct pet_data *pd;
	int perform = 0;
	unsigned int tick = gettick();

	nullpo_retr(0, sd);
	nullpo_retr(0, pd = sd->pd);

	unit_stop_walking(&pd->bl,1);
	pd->ud.canmove_tick = tick + 2000;

	perform = pet_performance_val(sd);
	if(perform > 0) {
		clif_pet_performance(&pd->bl, atn_rand() % perform + 1);
	}

	// ルートしたItemを落とさせる
	pet_lootitem_drop(pd,NULL);

	return 0;
}

/*==========================================
 * 卵に戻す
 *------------------------------------------
 */
int pet_return_egg(struct map_session_data *sd)
{
	struct item tmp_item;
	int flag;

	nullpo_retr(0, sd);
	nullpo_retr(0, sd->pd);

	if(sd->status.pet_id <= 0)
		return 0;

	// ルートしたItemを落とさせる
	pet_lootitem_drop(sd->pd,sd);
	unit_free(&sd->pd->bl,0);
	sd->status.pet_id = 0;
	sd->pd = NULL;

	if(sd->petDB == NULL)
		return 1;
	sd->pet.incubate = 1;

	memset(&tmp_item,0,sizeof(tmp_item));
	tmp_item.nameid   = sd->petDB->EggID;
	tmp_item.identify = 1;
	tmp_item.card[0]  = (short)0xff00;
	*((int *)(&tmp_item.card[1])) = sd->pet.pet_id;
	tmp_item.card[3]  = sd->pet.rename_flag;

	if((flag = pc_additem(sd,&tmp_item,1))) {
		clif_additem(sd,0,0,flag);
		map_addflooritem(&tmp_item,1,sd->bl.m,sd->bl.x,sd->bl.y,0,0,0,0);
	}
	if(battle_config.pet_status_support && sd->pet.intimate > 0) {
		if(sd->bl.prev != NULL)
			status_calc_pc(sd,0);
		else
			status_calc_pc(sd,2);
	}

#if PACKETVER >= 20180704
	clif_inventoryStart(sd, 0, "");
	clif_itemlist(sd);
	clif_equiplist(sd);
	clif_inventoryEnd(sd, 0);
	clif_send_petdata(sd, 6, 0);
#endif

	intif_save_petdata(sd->status.account_id,&sd->pet);
	chrif_save(sd,0);
	if(sd->state.storage_flag == 1)
		storage_storage_save(sd);

	sd->petDB = NULL;

	return 0;
}

/*==========================================
 * 装備していたものを外す
 *------------------------------------------
 */
static int pet_unequipitem(struct map_session_data *sd)
{
	struct item tmp_item;
	int nameid, flag;

	nullpo_retr(1, sd);
	nullpo_retr(1, sd->pd);

	if(sd->petDB == NULL)
		return 1;
	if(sd->pet.equip == 0)
		return 1;

	nameid = sd->pet.equip;
	sd->pet.equip = 0;
	sd->pd->equip = 0;
	clif_pet_equip(sd->pd,0);

	memset(&tmp_item,0,sizeof(tmp_item));
	tmp_item.nameid   = nameid;
	tmp_item.identify = 1;

	if((flag = pc_additem(sd,&tmp_item,1))) {
		clif_additem(sd,0,0,flag);
		map_addflooritem(&tmp_item,1,sd->bl.m,sd->bl.x,sd->bl.y,0,0,0,0);
	}

	return 0;
}

/*==========================================
 * ペットのメニューの応答
 *------------------------------------------
 */
int pet_menu(struct map_session_data *sd,int menunum)
{
	nullpo_retr(0, sd);

	if(sd->pd == NULL)
		return 0;

	switch(menunum) {
		case 0:
			clif_send_petstatus(sd);
			break;
		case 1:
			pet_food(sd);
			break;
		case 2:
			pet_performance(sd);
			break;
		case 3:
			pet_return_egg(sd);
			break;
		case 4:
			pet_unequipitem(sd);
			break;
	}
	return 0;
}

/*==========================================
 * アイテムを装備する
 *------------------------------------------
 */
void pet_equipitem(struct map_session_data *sd, int idx)
{
	int nameid;

	nullpo_retv(sd);

	nameid = sd->status.inventory[idx].nameid;

	if(sd->petDB == NULL || sd->petDB->AcceID == 0 || nameid != sd->petDB->AcceID || sd->pet.equip != 0) {
		clif_equipitemack(sd,0,0,0);
	} else {
		pc_delitem(sd, idx, 1, 0, 0);
		sd->pet.equip = sd->pd->equip = nameid;
		clif_pet_equip(sd->pd,nameid);
	}

	return;
}

/*==========================================
 * 名前の変更
 *------------------------------------------
 */
int pet_change_name(struct map_session_data *sd,const char *name)
{
	int i;

	nullpo_retr(1, sd);

	if(sd->pet.rename_flag == 1 && battle_config.pet_rename == 0)
		return 1;
	if(sd->pd == NULL)
		return 1;

	for(i=0; i<24 && name[i]; i++) {
		if( !(name[i]&0xe0) || name[i] == 0x7f )
			return 1;
	}

	unit_stop_walking(&sd->pd->bl,1);
	strncpy(sd->pet.name,name,24);
	strncpy(sd->pd->name,name,24);
	sd->pet.name[23] = '\0';
	sd->pd->name[23] = '\0';
	clif_clearchar_area(&sd->pd->bl,0);
	clif_spawnpet(sd->pd);
	clif_send_petdata(sd,0,0);
	clif_send_pethair(sd);
	sd->pet.rename_flag = 1;
	clif_pet_equip(sd->pd,sd->pet.equip);
	clif_send_petstatus(sd);

	return 0;
}

/*==========================================
 * ランダム歩行
 *------------------------------------------
 */
static int pet_randomwalk(struct pet_data *pd,unsigned int tick)
{
	const int retrycount = 20;
	int speed;

	nullpo_retr(0, pd);

	speed = status_get_speed(&pd->bl);

	if(DIFF_TICK(pd->next_walktime,tick) < 0) {
		int i, c = 0;
		int d = 12 - pd->move_fail_count;

		if(d < 5) d = 5;

		for(i=0; i<retrycount; i++) {
			int r = atn_rand();
			int x = pd->bl.x + r%(d*2+1) - d;
			int y = pd->bl.y + r/(d*2+1)%(d*2+1) - d;

			if(map_getcell(pd->bl.m,x,y,CELL_CHKPASS) && unit_walktoxy(&pd->bl,x,y)) {
				pd->move_fail_count = 0;
				break;
			}
			if(i+1 >= retrycount) {
				pd->move_fail_count++;
				if(pd->move_fail_count > 1000) {
					if(battle_config.error_log)
						printf("PET cant move. hold position %d, class = %d\n",pd->bl.id,pd->class_);
					pd->move_fail_count = 0;
					pd->ud.canmove_tick = gettick() + 60000;
					return 0;
				}
			}
		}
		for(i=0; i<pd->ud.walkpath.path_len; i++) {
			if(pd->ud.walkpath.path[i] & 1)
				c += speed*14/10;
			else
				c += speed;
		}
		pd->next_walktime = tick + atn_rand()%3000 + 3000 + c;
		return 1;
	}
	return 0;
}

/*==========================================
 * ロック解除
 *------------------------------------------
 */
static int pet_unlocktarget(struct pet_data *pd)
{
	nullpo_retr(0, pd);

	pd->target_id = 0;

	return 0;
}

/*==========================================
 * ルートアイテムのサーチ
 *------------------------------------------
 */
static int pet_ai_sub_hard_lootsearch(struct block_list *bl,va_list ap)
{
	struct pet_data *pd;
	struct flooritem_data *fitem;
	int *itc;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, pd  = va_arg(ap,struct pet_data *));
	nullpo_retr(0, itc = va_arg(ap,int *));
	nullpo_retr(0, fitem = (struct flooritem_data *)bl);

	if(fitem->first_get_id > 0) {
		struct map_session_data *sd = map_id2sd(fitem->first_get_id);
		if(sd && sd->pd != pd) {
			// ルート権無し
			return 0;
		}
	}
	if(pd->lootitem_weight + itemdb_weight(fitem->item_data.nameid) * fitem->item_data.amount > battle_config.pet_weight) {
		// 重量オーバー
		return 0;
	}

	if( unit_can_reach(&pd->bl,bl->x,bl->y) && atn_rand()%1000 < 1000/(++(*itc)) ) {	// 範囲内で等確率にする
		pd->target_id = bl->id;
	}

	return 0;
}

/*==========================================
 * ペットAI
 *------------------------------------------
 */
static int pet_ai_sub_hard(struct pet_data *pd,unsigned int tick)
{
	struct map_session_data *sd = NULL;
	const int loot_range = 3;	// ルートに行く射程範囲
	int dist;

	nullpo_retr(0, pd);

	sd = pd->msd;

	if(pd->bl.prev == NULL || sd == NULL || sd->bl.prev == NULL)
		return 0;

	if(DIFF_TICK(tick,pd->last_thinktime) < MIN_PETTHINKTIME)
		return 0;
	if(pd->ud.attacktimer != -1 || pd->ud.skilltimer != -1 || pd->bl.m != sd->bl.m)
		return 0;
	// 歩行中は３歩ごとにAI処理を行う
	if(pd->ud.walktimer != -1 && pd->ud.walkpath.path_pos <= 2)
		return 0;
	pd->last_thinktime = tick;

	if(unit_isdead(&sd->bl)) {
		// 主人が死亡しているなら攻撃止め
		if(pd->target_id > 0) {
			unit_stopattack(&pd->bl);
			pet_unlocktarget(pd);
		}
	}

	if(sd->pet.intimate <= 0) {
		if(battle_config.pet_leave) {	// 新密度0で即刻消えるか
			unit_free(&sd->pd->bl,0);
			sd->status.pet_id = 0;
			sd->pd = NULL;
			chrif_save(sd,0);
			if(sd->state.storage_flag == 1)
				storage_storage_save(sd);
		} else {
			if(battle_config.pet_speed_is_same_as_pc == 1)
				pd->speed = status_get_speed(&sd->bl);
			else
				pd->speed = sd->petDB->speed;
			if(pd->ud.attacktimer != -1)
				unit_stopattack(&pd->bl);
			pet_randomwalk(pd,tick);
		}
		return 0;
	}

	dist = path_distance(sd->bl.x,sd->bl.y,pd->bl.x,pd->bl.y);
	if(dist > 12 || (pd->target_id > 0 && dist > 9)) {
		if(pd->target_id > 0) {
			unit_stopattack(&pd->bl);
			pet_unlocktarget(pd);
		}
		if(pd->ud.walktimer != -1 && path_distance(pd->ud.to_x,pd->ud.to_y,sd->bl.x,sd->bl.y) < 3)
			return 0;
		pd->speed = (sd->speed >> 1);
		if(pd->speed <= 0)
			pd->speed = 1;
		unit_calc_pos(&pd->bl,sd->bl.x,sd->bl.y,sd->dir,2);
		if(!unit_walktoxy(&pd->bl,pd->ud.to_x,pd->ud.to_y))
			pet_randomwalk(pd,tick);
		return 0;
	}

	// ペットによるルート
	if(battle_config.pet_lootitem) {
		if( pd->target_id <= 0 &&
		    (!battle_config.pet_loot_type || pd->lootitem_count < LOOTITEM_SIZE) &&
		    pd->loottype > 0 &&
		    DIFF_TICK(tick,pd->lootitem_timer) > 0 &&
		    pd->lootitem )
		{
			int count = 0;
			map_foreachinarea(
				pet_ai_sub_hard_lootsearch,
				pd->bl.m,pd->bl.x-loot_range,pd->bl.y-loot_range,pd->bl.x+loot_range,pd->bl.y+loot_range,
				BL_ITEM,pd,&count
			);
		}
	}

	if(pd->target_id > MAX_FLOORITEM) {
		int mode = mobdb_search(pd->class_)->mode;
		int race = mobdb_search(pd->class_)->race;
		struct mob_data *md = map_id2md(pd->target_id);

		if(md == NULL || pd->bl.m != md->bl.m || md->bl.prev == NULL ||
		   path_distance(pd->bl.x,pd->bl.y,md->bl.x,md->bl.y) > 13) {
			pet_unlocktarget(pd);
		} else if(mobdb_search(pd->class_)->mexp <= 0 && !(mode&MD_BOSS) && (md->sc.option & (OPTION_HIDE | OPTION_CLOAKING) && race != RCT_INSECT && race != RCT_DEMON)) {
			pet_unlocktarget(pd);
		} else if(!battle_check_range(&pd->bl,&md->bl,mobdb_search(pd->class_)->range)) {
			if(pd->ud.walktimer != -1 && path_distance(pd->ud.to_x,pd->ud.to_y,md->bl.x,md->bl.y) < 2)
				return 0;
			if(!unit_can_reach(&pd->bl,md->bl.x,md->bl.y)) {
				pet_unlocktarget(pd);
			} else {
				int dx, dy, ret, i = 0;

				if(battle_config.pet_speed_is_same_as_pc == 1)
					pd->speed = status_get_speed(&sd->bl);
				else
					pd->speed = sd->petDB->speed;
				do {
					if(i == 0) {
						// 最初はAEGISと同じ方法で検索
						dx = md->bl.x - pd->bl.x;
						dy = md->bl.y - pd->bl.y;
						if(dx < 0) dx++; else if(dx > 0) dx--;
						if(dy < 0) dy++; else if(dy > 0) dy--;
					} else {
						// だめならAthena式(ランダム)
						dx = md->bl.x - pd->bl.x + atn_rand()%3 - 1;
						dy = md->bl.y - pd->bl.y + atn_rand()%3 - 1;
					}
					ret = unit_walktoxy(&pd->bl,pd->bl.x+dx,pd->bl.y+dy);
					i++;
				} while(ret == 0 && i < 5);

				if(ret == 0) { // 移動不可能な所からの攻撃なら2歩下る
					if(dx < 0) dx = 2; else if(dx > 0) dx = -2;
					if(dy < 0) dy = 2; else if(dy > 0) dy = -2;
					unit_walktoxy(&pd->bl,pd->bl.x+dx,pd->bl.y+dy);
				}
			}
		} else {
			if(pd->ud.walktimer != -1)
				unit_stop_walking(&pd->bl,1);
			if(pd->ud.attacktimer != -1)
				return 0;
			if(pd->a_skill && atn_rand()%100 < pd->a_skill->rate + pd->msd->pet.intimate * pd->a_skill->bonusrate / 1000) {
				if(skill_get_inf(pd->a_skill->id) & INF_GROUND) {
					// 場所指定
					unit_skilluse_pos( &pd->bl, md->bl.x, md->bl.y, pd->a_skill->id, pd->a_skill->lv);
				} else {
					// ID指定
					unit_skilluse_id(&pd->bl, pd->target_id, pd->a_skill->id, pd->a_skill->lv);
				}
			} else if(battle_config.pet_attack_support) {
				unit_attack(&pd->bl, pd->target_id, 0);
			}
		}
	}
	else if(pd->target_id > 0) {	// ルート処理
		struct block_list *bl_item = map_id2bl(pd->target_id);

		if(bl_item == NULL || bl_item->type != BL_ITEM || bl_item->m != pd->bl.m ||
		   (dist = path_distance(pd->bl.x,pd->bl.y,bl_item->x,bl_item->y)) > loot_range) {
			 // 遠すぎるかアイテムがなくなった
			pet_unlocktarget(pd);
		} else if(dist > 0) {
			int dx, dy;
			if(pd->ud.walktimer != -1 && (DIFF_TICK(pd->next_walktime,tick) < 0 || path_distance(pd->ud.to_x,pd->ud.to_y,bl_item->x,bl_item->y) <= 0))
				return 0; // 既に移動中

			pd->next_walktime = tick + 500;
			dx = bl_item->x - pd->bl.x;
			dy = bl_item->y - pd->bl.y;
			if(battle_config.pet_speed_is_same_as_pc == 1)
				pd->speed = status_get_speed(&sd->bl);
			else
				pd->speed = sd->petDB->speed;

			unit_walktoxy(&pd->bl,pd->bl.x+dx,pd->bl.y+dy);
		} else {
			// アイテムまでたどり着いた
			struct flooritem_data *fitem = (struct flooritem_data *)bl_item;

			if(pd->ud.attacktimer != -1)
				return 0; // 攻撃中
			if(pd->ud.walktimer != -1)	// 歩行中なら停止
				unit_stop_walking(&pd->bl,1);
			if(pd->loottype == 1) {		// ペット自身が所有する場合
				if(pd->lootitem_count < LOOTITEM_SIZE) {
					memcpy(&pd->lootitem[pd->lootitem_count++],&fitem->item_data,sizeof(pd->lootitem[0]));
					pd->lootitem_weight += itemdb_weight(fitem->item_data.nameid) * fitem->item_data.amount;
				}
				else if(battle_config.pet_loot_type) {
					pet_unlocktarget(pd);
					return 0;
				}
				else {
					if(pd->lootitem[0].card[0] == (short)0xff00)
						intif_delete_petdata(*((int *)(&pd->lootitem[0].card[1])));
					pd->lootitem_weight -= itemdb_weight(pd->lootitem[LOOTITEM_SIZE-1].nameid) * pd->lootitem[LOOTITEM_SIZE-1].amount;
					pd->lootitem_weight += itemdb_weight(fitem->item_data.nameid) * fitem->item_data.amount;
					memmove(&pd->lootitem[0],&pd->lootitem[1],sizeof(pd->lootitem[0])*(LOOTITEM_SIZE-1));
					memcpy(&pd->lootitem[LOOTITEM_SIZE-1],&fitem->item_data,sizeof(pd->lootitem[0]));
				}
			} else if(pd->loottype == 2) {	// ペットが拾った瞬間に飼い主へ
				if(pc_additem(pd->msd,&fitem->item_data,fitem->item_data.amount)) {
					pet_unlocktarget(pd);
					return 0;
				}
			} else {
				return 0;
			}
			if(mob_is_pcview(pd->class_)) {
				int delay = tick + status_get_amotion(&pd->bl);
				clif_takeitem(&pd->bl,fitem->bl.id);
				pd->ud.canact_tick  = delay;
				pd->ud.canmove_tick = delay;
			}
			map_clearflooritem(bl_item->id);
			pet_unlocktarget(pd);
		}
	}
	else {
		// 待機時、適当に歩き回る
		/*
		if(pc_issit(sd)) {
			if(dist < 5 && path_distance(pd->ud.to_x,pd->ud.to_y,sd->bl.x,sd->bl.y) < 5) {
				if(!unit_walktoxy(&pd->bl,pd->ud.to_x,pd->ud.to_y))
					pet_randomwalk(pd,tick);
				return 0;
			}
			if(!(atn_rand()%100))
				pet_randomwalk(pd,tick);
			return 0;
		}
		*/
		if(dist <= 3 || (pd->ud.walktimer != -1 && path_distance(pd->ud.to_x,pd->ud.to_y,sd->bl.x,sd->bl.y) < 3))
			return 0;
		if(battle_config.pet_speed_is_same_as_pc == 1)
			pd->speed = status_get_speed(&sd->bl);
		else
			pd->speed = sd->petDB->speed;
		unit_calc_pos(&pd->bl,sd->bl.x,sd->bl.y,sd->dir,2);
		if(!unit_walktoxy(&pd->bl,pd->ud.to_x,pd->ud.to_y))
			pet_randomwalk(pd,tick);
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
static int pet_ai_sub_foreachclient(struct map_session_data *sd,va_list ap)
{
	unsigned int tick;

	nullpo_retr(0, sd);
	nullpo_retr(0, ap);

	tick = va_arg(ap,unsigned int);
	if(sd->status.pet_id && sd->pd && sd->petDB)
		pet_ai_sub_hard(sd->pd,tick);

	return 0;
}

static int pet_ai_hard(int tid,unsigned int tick,int id,void *data)
{
	clif_foreachclient(pet_ai_sub_foreachclient,tick);

	return 0;
}

/*==========================================
 * delay付きitem drop (timer関数)
 *------------------------------------------
 */
static int pet_delay_item_drop2(int tid,unsigned int tick,int id,void *data)
{
	struct delay_item_drop2 *ditem;

	ditem = (struct delay_item_drop2 *)data;

	// ペットの卵ならドロップディレイキューからpopする
	if(ditem->item_data.card[0] == (short)0xff00) {
		struct delay_item_drop2 *p = map_pop_delayitem_que();
		if(p != ditem)
			printf("pet_delay_item_drop2: que pop error!!\n");
	}

	map_addflooritem(
		&ditem->item_data,ditem->item_data.amount,ditem->m,ditem->x,ditem->y,
		ditem->first_id,ditem->second_id,ditem->third_id,0
	);
	aFree(ditem);

	return 0;
}

/*==========================================
 * ルートアイテムのドロップ
 *------------------------------------------
 */
int pet_lootitem_drop(struct pet_data *pd,struct map_session_data *sd)
{
	int i, flag = 0;
	unsigned int tick;

	nullpo_retr(0, pd);

	if(pd->lootitem == NULL)
		return 0;

	tick = gettick();
	for(i=0; i<pd->lootitem_count; i++) {
		if(sd) {
			struct item *item_data = &pd->lootitem[i];

			// 落とさないで直接PCのItem欄へ
			if((flag = pc_additem(sd,item_data,item_data->amount))) {
				clif_additem(sd,0,0,flag);
				map_addflooritem(item_data,item_data->amount,pd->bl.m,pd->bl.x,pd->bl.y,0,0,0,0);
			}
		} else {
			struct delay_item_drop2 *ditem;

			ditem = (struct delay_item_drop2 *)aCalloc(1,sizeof(struct delay_item_drop2));
			memcpy(&ditem->item_data,&pd->lootitem[i],sizeof(pd->lootitem[0]));
			ditem->m = pd->bl.m;
			ditem->x = pd->bl.x;
			ditem->y = pd->bl.y;
			ditem->first_id  = 0;
			ditem->second_id = 0;
			ditem->third_id  = 0;
			ditem->next      = NULL;

			if(ditem->item_data.card[0] == (short)0xff00) {
				// ペットの卵はドロップディレイキューに保存する
				map_push_delayitem_que(ditem);
				add_timer(tick+540,pet_delay_item_drop2,0,ditem);
			} else {
				add_timer2(tick+540+i,pet_delay_item_drop2,0,ditem);
			}
		}
	}
	memset(pd->lootitem,0,LOOTITEM_SIZE * sizeof(struct item));
	pd->lootitem_count  = 0;
	pd->lootitem_weight = 0;
	pd->lootitem_timer  = tick + 10000;	// 10*1000msの間拾わない

	return 1;
}

/*==========================================
 *
 *------------------------------------------
 */
int pet_lootitem_free(struct pet_data *pd)
{
	nullpo_retr(0, pd);

	if(pd->lootitem) {
		int i;
		for(i=0; i<pd->lootitem_count; i++) {
			if(pd->lootitem[i].card[0] == (short)0xff00)
				intif_delete_petdata(*((int *)(&pd->lootitem[i].card[1])));
		}
		aFree(pd->lootitem);
	}
	return 0;
}

/*==========================================
 * ペットスキル
 *------------------------------------------
 */
int pet_skill_support_timer(int tid,unsigned int tick,int id,void *data)
{
	struct map_session_data *sd = map_id2sd(id);
	struct pet_data *pd;
	int rate = 100;

	if(sd == NULL || (pd = sd->pd) == NULL)
		return 1;

	if(pd->s_skill == NULL || pd->s_skill->timer != tid) {
		if(battle_config.error_log) {
			if(pd->s_skill)
				printf("pet_skill_support_timer %d != %d\n",pd->s_skill->timer,tid);
			else
				printf("pet_skill_support_timer called with no support skill defined (tid=%d)\n",tid);
		}
		return 0;
	}

	if( unit_isdead(&sd->bl) || pd->ud.walktimer != -1 || pd->ud.skilltimer != -1 ||
	    (rate = sd->status.sp*100/sd->status.max_sp) > pd->s_skill->sp ||
	    (rate = sd->status.hp*100/sd->status.max_hp) > pd->s_skill->hp )
	{
		// Wait (how long? 1 sec for every 10% of remaining)
		if(rate < 10)
			rate = 10;
		pd->s_skill->timer = add_timer(gettick()+rate*100,pet_skill_support_timer,sd->bl.id,NULL);
		return 0;
	}

	if(skill_get_inf(pd->s_skill->id) & INF_GROUND) {
		// 場所指定
		unit_skilluse_pos( &pd->bl, sd->bl.x, sd->bl.y, pd->s_skill->id, pd->s_skill->lv);
	} else {
		// ID指定
		unit_skilluse_id(&pd->bl, sd->bl.id, pd->s_skill->id, pd->s_skill->lv);
	}

	pd->s_skill->timer = add_timer(tick+pd->s_skill->delay*1000,pet_skill_support_timer,sd->bl.id,NULL);

	return 0;
}

/*==========================================
 * ペットデータ読み込み
 *------------------------------------------
 */
int read_petdb(void)
{
	FILE *fp;
	char line[4096];
	int i, j, k;
	int lines, count = 0;
	struct script_code *script = NULL;
	const char *filename[] = { "db/pet_db.txt","db/addon/pet_db_add.txt" };

	for(i = 0; i < 2; i++) {
		fp = fopen(filename[i], "r");
		if(fp == NULL) {
			if(i > 0)
				continue;
			printf("read_petdb: open [%s] failed !\n", filename[i]);
			return -1;
		}
		lines=count=0;
		while(fgets(line,sizeof(line),fp)){
			int nameid;
			char *str[20],*p,*np;
			lines++;

			if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
				continue;
			if(line[0] == '/' && line[1] == '/')
				continue;

			for(j=0,p=line;j<20;j++){
				if((np=strchr(p,','))!=NULL){
					str[j]=p;
					*np=0;
					p=np+1;
				} else {
					str[j]=p;
					p+=strlen(p);
				}
			}

			if(pet_count >= MAX_PET_DB)
				break;

			nameid = atoi(str[0]);
			if(nameid <= 0 || !mobdb_exists(nameid))
				continue;

			k = pet_search_index(nameid, PET_CLASS);
			j = (k >= 0)? k: pet_count;

			pet_db[j].class_       = nameid;
			strncpy(pet_db[j].name,str[1],24);
			strncpy(pet_db[j].jname,str[2],24);
			pet_db[j].itemID       = atoi(str[3]);
			pet_db[j].EggID        = atoi(str[4]);
			pet_db[j].AcceID       = atoi(str[5]);
			pet_db[j].FoodID       = atoi(str[6]);
			pet_db[j].fullness     = atoi(str[7]);
			pet_db[j].hungry_delay = atoi(str[8]) * 1000;
			pet_db[j].r_hungry     = atoi(str[9]);
			if(pet_db[j].r_hungry <= 0)
				pet_db[j].r_hungry = 1;
			pet_db[j].r_full              = atoi(str[10]);
			pet_db[j].intimate            = atoi(str[11]);
			pet_db[j].die                 = atoi(str[12]);
			pet_db[j].capture             = atoi(str[13]);
			pet_db[j].speed               = atoi(str[14]);
			pet_db[j].s_perfor            = (char)atoi(str[15]);
			pet_db[j].talk_convert_class  = atoi(str[16]);
			pet_db[j].attack_rate         = atoi(str[17]);
			pet_db[j].defence_attack_rate = atoi(str[18]);
			pet_db[j].change_target_rate  = atoi(str[19]);

			// force \0 terminal
			pet_db[j].name[23]  = '\0';
			pet_db[j].jname[23] = '\0';

			// ペットの卵のアイテムIDにpet_eggフラグをセットする
			itemdb_search(pet_db[j].EggID)->flag.pet_egg = 1;

			// ペットのアクセサリーのアイテムIDにpet_acceフラグをセットする
			itemdb_search(pet_db[j].AcceID)->flag.pet_acce = 1;

			if(k < 0)
				pet_count++;
			count++;

			if((np = strchr(p,'{')) == NULL)
				continue;

			if(!parse_script_line_end(np, filename[i], lines))
				continue;

			if(pet_db[j].script) {
				script_free_code(pet_db[j].script);
			}
			script = parse_script(np, filename[i], lines);
			pet_db[j].script = (script_is_error(script))? NULL: script;
		}
		fclose(fp);
		printf("read %s done (count=%d)\n", filename[i], count);
	}
	return 0;
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
int do_init_pet(void)
{
	unsigned int tick = gettick();

	// 初回のみでリロード時はデータベースをクリアしない
	memset(pet_db,0,sizeof(pet_db));
	pet_count = 0;

	read_petdb();

	add_timer_func_list(pet_hungry_timer);
	add_timer_func_list(pet_ai_hard);
	add_timer_func_list(pet_delay_item_drop2);
	add_timer_func_list(pet_skill_support_timer);

	add_timer_interval(tick+MIN_PETTHINKTIME,pet_ai_hard,0,NULL,MIN_PETTHINKTIME);

	return 0;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
int do_final_pet(void)
{
	int i;

	for(i = 0; i < pet_count; i++) {
		if(pet_db[i].script) {
			script_free_code(pet_db[i].script);
		}
	}
	return 0;
}
