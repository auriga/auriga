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
#include "unit.h"
#include "skill.h"

#ifdef MEMWATCH
#include "memwatch.h"
#endif

#define MIN_PETTHINKTIME 100

struct pet_db pet_db[MAX_PET_DB];
static int pet_count;

static int pet_performance_val(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	if(sd->pet.intimate > 900)
		return (sd->petDB->s_perfor > 0)? 4:3;
	else if(sd->pet.intimate > 750)
		return 2;
	else
		return 1;
}

int pet_hungry_val(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	if(sd->pet.hungry > 90)
		return 4;
	else if(sd->pet.hungry > 75)
		return 3;
	else if(sd->pet.hungry > 25)
		return 2;
	else if(sd->pet.hungry > 10)
		return 1;
	else
		return 0;
}

static int pet_calc_pos(struct pet_data *pd,int tx,int ty,int dir)
{
	int x,y,dx,dy;
	int i,j=0,k;

	nullpo_retr(0, pd);

	pd->ud.to_x = tx;
	pd->ud.to_y = ty;

	if(dir >= 0 && dir < 8) {
		dx = -dirx[dir]*2;
		dy = -diry[dir]*2;
		x = tx + dx;
		y = ty + dy;
		if(!(j=unit_can_reach(&pd->bl,x,y))) {
			if(dx > 0) x--;
			else if(dx < 0) x++;
			if(dy > 0) y--;
			else if(dy < 0) y++;
			if(!(j=unit_can_reach(&pd->bl,x,y))) {
				for(i=0;i<12;i++) {
					k = atn_rand()%8;
					dx = -dirx[k]*2;
					dy = -diry[k]*2;
					x = tx + dx;
					y = ty + dy;
					if((j=unit_can_reach(&pd->bl,x,y)))
						break;
					else {
						if(dx > 0) x--;
						else if(dx < 0) x++;
						if(dy > 0) y--;
						else if(dy < 0) y++;
						if((j=unit_can_reach(&pd->bl,x,y)))
							break;
					}
				}
				if(!j) {
					x = tx;
					y = ty;
					if(!unit_can_reach(&pd->bl,x,y))
						return 1;
				}
			}
		}
	}
	else
		return 1;

	pd->ud.to_x = x;
	pd->ud.to_y = y;
	return 0;
}

int pet_target_check(struct map_session_data *sd,struct block_list *bl,int type)
{
	struct pet_data *pd;
	struct mob_data *md;
	int rate,mode,race;

	nullpo_retr(0, sd);

	pd = sd->pd;

	if(bl && pd && bl->type == BL_MOB && sd->pet.intimate > 900 && sd->pet.hungry > 0 && pd->class != status_get_class(bl) &&
	   pd->ud.skilltimer == -1 && pd->ud.attacktimer == -1) {
		mode=mob_db[pd->class].mode;
		race=mob_db[pd->class].race;
		md=(struct mob_data *)bl;
		if(md) {
			if(pd->bl.m != md->bl.m || md->bl.prev == NULL ||
				unit_distance(pd->bl.x,pd->bl.y,md->bl.x,md->bl.y) > 13)
				return 0;
			if(mob_db[pd->class].mexp <= 0 && !(mode&0x20) && (md->option & 0x06 && race!=4 && race!=6) )
				return 0;
		}
		if(!type) {
			rate = sd->petDB->attack_rate;
			rate = rate * (150 - (sd->pet.intimate - 1000))/100;
			if(battle_config.pet_support_rate != 100)
				rate = rate*battle_config.pet_support_rate/100;
			if(sd->petDB->attack_rate > 0 && rate <= 0)
				rate = 1;
		}
		else {
			rate = sd->petDB->defence_attack_rate;
			rate = rate * (150 - (sd->pet.intimate - 1000))/100;
			if(battle_config.pet_support_rate != 100)
				rate = rate*battle_config.pet_support_rate/100;
			if(sd->petDB->defence_attack_rate > 0 && rate <= 0)
				rate = 1;
		}
		if( atn_rand()%10000 < rate ) {
			if(pd->target_id == 0 || atn_rand()%10000 < sd->petDB->change_target_rate){
				pd->target_id = bl->id;
			}
		}
	}
	return 0;
}

static int pet_hungry(int tid,unsigned int tick,int id,int data)
{
	struct map_session_data *sd;
	int interval,t;

	sd=map_id2sd(id);
	if(sd==NULL)
		return 1;

	if(sd->pet_hungry_timer != tid){
		if(battle_config.error_log)
			printf("pet_hungry_timer %d != %d\n",sd->pet_hungry_timer,tid);
		return 0;
	}
	sd->pet_hungry_timer = -1;
	if(!sd->status.pet_id || !sd->pd || !sd->petDB)
		return 1;

	sd->pet.hungry--;
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
		interval = (sd->petDB->hungry_delay*battle_config.pet_hungry_delay_rate)/100;
	else
		interval = sd->petDB->hungry_delay;
	if(interval <= 0)
		interval = 1;
	sd->pet_hungry_timer = add_timer(tick+interval,pet_hungry,sd->bl.id,0);

	return 0;
}

int search_petDB_index(int key,int type)
{
	int i;

	for(i=0;i<pet_count;i++) {
		if(pet_db[i].class <= 0)
			continue;
		switch(type) {
			case PET_CLASS:
				if(pet_db[i].class == key)
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

int pet_hungry_timer_delete(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	if(sd->pet_hungry_timer != -1) {
		delete_timer(sd->pet_hungry_timer,pet_hungry);
		sd->pet_hungry_timer = -1;
	}

	return 0;
}

struct delay_item_drop {
	int m,x,y;
	int nameid,amount;
	struct map_session_data *first_sd,*second_sd,*third_sd;
};

struct delay_item_drop2 {
	int m,x,y;
	struct item item_data;
	struct map_session_data *first_sd,*second_sd,*third_sd;
};

int pet_performance(struct map_session_data *sd)
{
	struct pet_data *pd;

	nullpo_retr(0, sd);
	if((pd=sd->pd)==NULL)
		return 0;

	unit_stop_walking(&pd->bl,1);
	pd->ud.canmove_tick = gettick() + 2000;
	clif_pet_performance(&pd->bl,atn_rand()%pet_performance_val(sd) + 1);
	// ルートしたItemを落とさせる
	pet_lootitem_drop(pd,NULL);

	return 0;
}

int pet_return_egg(struct map_session_data *sd)
{
	struct item tmp_item;
	int flag;

	nullpo_retr(0, sd);

	if(sd->status.pet_id && sd->pd) {
		// ルートしたItemを落とさせる
		pet_lootitem_drop(sd->pd,sd);
		unit_free(&sd->pd->bl,0);
		sd->status.pet_id = 0;
		sd->pd = NULL;

		if(sd->petDB == NULL)
			return 1;
		sd->pet.incubate = 1;
		memset(&tmp_item,0,sizeof(tmp_item));
		tmp_item.nameid = sd->petDB->EggID;
		tmp_item.identify = 1;
		tmp_item.card[0] = (short)0xff00;
		*((long *)(&tmp_item.card[1])) = sd->pet.pet_id;
		tmp_item.card[3] = sd->pet.rename_flag;
		if((flag = pc_additem(sd,&tmp_item,1))) {
			clif_additem(sd,0,0,flag);
			map_addflooritem(&tmp_item,1,sd->bl.m,sd->bl.x,sd->bl.y,NULL,NULL,NULL,0);
		}
		if(battle_config.pet_status_support && sd->pet.intimate > 0) {
			if(sd->bl.prev != NULL)
				status_calc_pc(sd,0);
			else
				status_calc_pc(sd,2);
		}

		intif_save_petdata(sd->status.account_id,&sd->pet);
		pc_makesavestatus(sd);
		chrif_save(sd);
		storage_storage_save(sd);

		sd->petDB = NULL;
	}

	return 0;
}

int pet_data_init(struct map_session_data *sd)
{
	struct pet_data *pd;
	int i,interval;

	nullpo_retr(1, sd);

	if(sd->status.account_id != sd->pet.account_id || sd->status.char_id != sd->pet.char_id ||
		sd->status.pet_id != sd->pet.pet_id) {
		sd->status.pet_id = 0;
		return 1;
	}

	i = search_petDB_index(sd->pet.class,PET_CLASS);
	if(i < 0) {
		sd->status.pet_id = 0;
		return 1;
	}
	sd->petDB = &pet_db[i];
	sd->pd = pd = (struct pet_data *)aCalloc(1,sizeof(struct pet_data));

	pd->bl.m = sd->bl.m;
	pd->bl.prev = pd->bl.next = NULL;
	pd->bl.x = pd->ud.to_x = sd->bl.x;
	pd->bl.y = pd->ud.to_y = sd->bl.y;
	pet_calc_pos(pd,sd->bl.x,sd->bl.y,sd->dir);
	pd->bl.x = pd->ud.to_x;
	pd->bl.y = pd->ud.to_y;
	pd->bl.id = npc_get_new_npc_id();
	memcpy(pd->name,sd->pet.name,24);
	pd->class = sd->pet.class;
	pd->equip = sd->pet.equip;
	pd->dir = sd->dir;
	if(battle_config.pet_speed_is_same_as_pc == 1)
		pd->speed = status_get_speed(&sd->bl);
	else
		pd->speed = sd->petDB->speed;
	pd->bl.subtype = MONS;
	pd->bl.type = BL_PET;
	memset(&pd->state,0,sizeof(pd->state));
	pd->target_id = 0;
	pd->move_fail_count = 0;
	pd->next_walktime = pd->last_thinktime = gettick();
	pd->msd = sd;

	unit_dataset( &pd->bl );
	map_addiddb(&pd->bl);

	if(sd->pet_hungry_timer != -1)
		pet_hungry_timer_delete(sd);
	if(battle_config.pet_hungry_delay_rate != 100)
		interval = (sd->petDB->hungry_delay*battle_config.pet_hungry_delay_rate)/100;
	else
		interval = sd->petDB->hungry_delay;
	if(interval <= 0)
		interval = 1;
	sd->pet_hungry_timer = add_timer(gettick()+interval,pet_hungry,sd->bl.id,0);
	pd->lootitem=(struct item *)aCalloc(LOOTITEM_SIZE,sizeof(struct item));
	pd->loottype=(!battle_config.pet_lootitem)?0:battle_config.petowneditem;
	pd->lootitem_count = 0;
	pd->lootitem_weight = 0;
	pd->lootitem_timer = gettick();
	pd->view_size = mob_db[pd->class].view_size;

	return 0;
}

int pet_birth_process(struct map_session_data *sd)
{
	nullpo_retr(1, sd);

	if(sd->status.pet_id && sd->pet.incubate == 1) {
		sd->status.pet_id = 0;
		return 1;
	}

	sd->pet.incubate = 0;
	sd->pet.account_id = sd->status.account_id;
	sd->pet.char_id = sd->status.char_id;
	sd->status.pet_id = sd->pet.pet_id;
	if(pet_data_init(sd)) {
		sd->status.pet_id = 0;
		sd->pet.incubate = 1;
		sd->pet.account_id = 0;
		sd->pet.char_id = 0;
		return 1;
	}

	intif_save_petdata(sd->status.account_id,&sd->pet);
	pc_makesavestatus(sd);
	chrif_save(sd);
	storage_storage_save(sd);
	map_addblock(&sd->pd->bl);

	sd->pd->view_size = mob_db[sd->pd->class].view_size;
	clif_spawnpet(sd->pd);
	clif_send_petdata(sd,0,0);
	clif_send_petdata(sd,5,0x14);
	clif_pet_equip(sd->pd,sd->pet.equip);
	clif_send_petstatus(sd);

	return 0;
}

int pet_recv_petdata(int account_id,struct s_pet *p,int flag)
{
	struct map_session_data *sd;

	sd = map_id2sd(account_id);
	if(sd == NULL)
		return 1;
	if(flag == 1) {
		sd->status.pet_id = 0;
		return 1;
	}
	memcpy(&sd->pet,p,sizeof(struct s_pet));
	if(sd->pet.incubate == 1)
		pet_birth_process(sd);
	else {
		pet_data_init(sd);
		if(sd->pd && sd->bl.prev != NULL) {
			map_addblock(&sd->pd->bl);
			clif_spawnpet(sd->pd);
			clif_send_petdata(sd,0,0);
			clif_send_petdata(sd,5,0x14);
//			clif_pet_equip(sd->pd,sd->pet.equip);
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

int pet_select_egg(struct map_session_data *sd,short egg_index)
{
	nullpo_retr(0, sd);

	if(sd->status.inventory[egg_index].card[0] == (short)0xff00)
		intif_request_petdata(sd->status.account_id,sd->status.char_id,*((long *)&sd->status.inventory[egg_index].card[1]));
	else {
		if(battle_config.error_log)
			printf("wrong egg item inventory %d\n",egg_index);
	}
	pc_delitem(sd,egg_index,1,0);

	return 0;
}

int pet_catch_process1(struct map_session_data *sd,int target_class)
{
	nullpo_retr(0, sd);

	sd->catch_target_class = target_class;
	clif_catch_process(sd);

	return 0;
}

int pet_catch_process2(struct map_session_data *sd,int target_id)
{
	struct mob_data *md;
	int i,pet_catch_rate;

	nullpo_retr(1, sd);

	md = map_id2md(target_id);
	if(!md){
		clif_pet_rulet(sd,0);
		return 1;
	}

	i = search_petDB_index(md->class,PET_CLASS);
	if(md == NULL || md->bl.type != BL_MOB || md->bl.prev == NULL || i < 0 || sd->catch_target_class != md->class) {
		clif_pet_rulet(sd,0);
		return 1;
	}

	//target_idによる敵→卵判定
//	if(battle_config.etc_log)
//		printf("mob_id = %d, mob_class = %d\n",md->bl.id,md->class);
		//成功の場合
	pet_catch_rate = (pet_db[i].capture + (sd->status.base_level - mob_db[md->class].lv)*30 + sd->paramc[5]*20)*(200 - md->hp*100/mob_db[md->class].max_hp)/100;
	if(pet_catch_rate < 1) pet_catch_rate = 1;
	if(battle_config.pet_catch_rate != 100)
		pet_catch_rate = (pet_catch_rate*battle_config.pet_catch_rate)/100;

	if(rand()%10000 < pet_catch_rate) {
		unit_remove_map(&md->bl,0);
		clif_pet_rulet(sd,1);
//		if(battle_config.etc_log)
//			printf("rulet success %d\n",target_id);
		intif_create_pet(sd->status.account_id,sd->status.char_id,pet_db[i].class,mob_db[pet_db[i].class].lv,
			pet_db[i].EggID,0,pet_db[i].intimate,100,0,1,md->name);
	}
	else
		clif_pet_rulet(sd,0);

	return 0;
}

int pet_get_egg(int account_id,int pet_id,int flag)
{
	struct map_session_data *sd;
	struct item tmp_item;
	int i,ret;

	if(!flag) {
		sd = map_id2sd(account_id);
		if(sd == NULL)
			return 1;

		i = search_petDB_index(sd->catch_target_class,PET_CLASS);
		if(i >= 0) {
			memset(&tmp_item,0,sizeof(tmp_item));
			tmp_item.nameid = pet_db[i].EggID;
			tmp_item.identify = 1;
			tmp_item.card[0] = (short)0xff00;
			*((long *)(&tmp_item.card[1])) = pet_id;
			tmp_item.card[3] = sd->pet.rename_flag;
			if((ret = pc_additem(sd,&tmp_item,1))) {
				clif_additem(sd,0,0,ret);
				map_addflooritem(&tmp_item,1,sd->bl.m,sd->bl.x,sd->bl.y,NULL,NULL,NULL,0);
			}
		}
		else
			intif_delete_petdata(pet_id);
	}

	return 0;
}

int pet_menu(struct map_session_data *sd,int menunum)
{
	nullpo_retr(0, sd);

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

int pet_change_name(struct map_session_data *sd,char *name)
{
	int i;

	nullpo_retr(1, sd);

	if(sd->pet.rename_flag == 1 && battle_config.pet_rename == 0)
		return 1;

	for(i=0;i<24 && name[i];i++){
		if( !(name[i]&0xe0) || name[i]==0x7f)
			return 1;
	}

	if(sd->pd == NULL)
		return 1;

	unit_stop_walking(&sd->pd->bl,1);
	memcpy(sd->pet.name,name,24);
	memcpy(sd->pd->name,name,24);
	clif_clearchar_area(&sd->pd->bl,0);
	clif_spawnpet(sd->pd);
	clif_send_petdata(sd,0,0);
	clif_send_petdata(sd,5,0x14);
	sd->pet.rename_flag = 1;
	clif_pet_equip(sd->pd,sd->pet.equip);
	clif_send_petstatus(sd);

	return 0;
}

void pet_equipitem(struct map_session_data *sd, int idx)
{
	int nameid;

	nullpo_retv(sd);

	nameid = sd->status.inventory[idx].nameid;
	if(sd->petDB == NULL)
		return;
	if(sd->petDB->AcceID == 0 || nameid != sd->petDB->AcceID || sd->pet.equip != 0) {
		clif_equipitemack(sd,0,0,0);
		return;
	}
	else {
		pc_delitem(sd, idx, 1, 0);
		sd->pet.equip = sd->pd->equip = nameid;
		clif_pet_equip(sd->pd,nameid);
	}

	return;
}

int pet_unequipitem(struct map_session_data *sd)
{
	struct item tmp_item;
	int nameid,flag;

	nullpo_retr(1, sd);

	if(sd->petDB == NULL)
		return 1;
	if(sd->pet.equip == 0)
		return 1;

	nameid = sd->pet.equip;
	sd->pet.equip = sd->pd->equip = 0;
	clif_pet_equip(sd->pd,0);
	memset(&tmp_item,0,sizeof(tmp_item));
	tmp_item.nameid = nameid;
	tmp_item.identify = 1;
	if((flag = pc_additem(sd,&tmp_item,1))) {
		clif_additem(sd,0,0,flag);
		map_addflooritem(&tmp_item,1,sd->bl.m,sd->bl.x,sd->bl.y,NULL,NULL,NULL,0);
	}

	return 0;
}

int pet_food(struct map_session_data *sd)
{
	int i,k,t;

	nullpo_retr(1, sd);
	nullpo_retr(1, sd->pd);

	if(sd->petDB == NULL)
		return 1;
	i=pc_search_inventory(sd,sd->petDB->FoodID);
	if(i < 0) {
		clif_pet_food(sd,sd->petDB->FoodID,0);
		return 1;
	}
	pc_delitem(sd,i,1,0);
	t = sd->pet.intimate;
	if(sd->pet.hungry > 90)
		sd->pet.intimate -= sd->petDB->r_full;
	else if(sd->pet.hungry > 75) {
		if(battle_config.pet_friendly_rate != 100)
			k = (sd->petDB->r_hungry * battle_config.pet_friendly_rate)/100;
		else
			k = sd->petDB->r_hungry;
		k = k >> 1;
		if(k <= 0)
			k = 1;
		sd->pet.intimate += k;
	}
	else {
		if(battle_config.pet_friendly_rate != 100)
			k = (sd->petDB->r_hungry * battle_config.pet_friendly_rate)/100;
		else
			k = sd->petDB->r_hungry;
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
	}
	else if(sd->pet.intimate > 1000)
		sd->pet.intimate = 1000;
	sd->pet.hungry += sd->petDB->fullness;
	if(sd->pet.hungry > 100)
		sd->pet.hungry = 100;

	clif_send_petdata(sd,2,sd->pet.hungry);
	clif_send_petdata(sd,1,sd->pet.intimate);
	clif_pet_food(sd,sd->petDB->FoodID,1);

	return 0;
}

static int pet_randomwalk(struct pet_data *pd,int tick)
{
	const int retrycount=20;
	int speed;

	nullpo_retr(0, pd);

	speed = status_get_speed(&pd->bl);

	if(DIFF_TICK(pd->next_walktime,tick) < 0){
		int i,x,y,c,d=12-pd->move_fail_count;
		if(d<5) d=5;
		for(i=0;i<retrycount;i++){
			int r=atn_rand();
			x=pd->bl.x+r%(d*2+1)-d;
			y=pd->bl.y+r/(d*2+1)%(d*2+1)-d;
			if((map_getcell(pd->bl.m,x,y,CELL_CHKPASS))&&( unit_walktoxy(&pd->bl,x,y)==0)){
				pd->move_fail_count=0;
				break;
			}
			if(i+1>=retrycount){
				pd->move_fail_count++;
				if(pd->move_fail_count>1000){
					if(battle_config.error_log)
						printf("PET cant move. hold position %d, class = %d\n",pd->bl.id,pd->class);
					pd->move_fail_count=0;
					pd->ud.canmove_tick = gettick() + 60000;
					return 0;
				}
			}
		}
		for(i=c=0;i<pd->ud.walkpath.path_len;i++){
			if(pd->ud.walkpath.path[i]&1)
				c+=speed*14/10;
			else
				c+=speed;
		}
		pd->next_walktime = tick+atn_rand()%3000+3000+c;

		return 1;
	}
	return 0;
}

static int pet_unlocktarget(struct pet_data *pd)
{
	nullpo_retr(0, pd);

	pd->target_id=0;

	return 0;
}

static int pet_ai_sub_hard_lootsearch(struct block_list *bl,va_list ap)
{
	struct pet_data* pd;
	int dist,*itc;
	const int range=3;	// 拾いに行く射程範囲

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, pd=va_arg(ap,struct pet_data *));
	nullpo_retr(0, itc=va_arg(ap,int *));

	if(!pd->target_id && bl->type == BL_ITEM){
		struct flooritem_data *fitem = (struct flooritem_data *)bl;
		struct map_session_data *sd = NULL;
		// ルート権無し
		if(fitem && fitem->first_get_id>0)
			sd = map_id2sd(fitem->first_get_id);
		// 重量オーバー
		if((pd->lootitem_weight + (itemdb_search(fitem->item_data.nameid))->weight * fitem->item_data.amount) > battle_config.pet_weight)
			return 0;

		if(!pd->lootitem || (pd->lootitem_count >= LOOTITEM_SIZE) || (sd && sd->pd != pd))
			return 0;
		if(bl->m == pd->bl.m && (dist=unit_distance(pd->bl.x,pd->bl.y,bl->x,bl->y))<range){
			if( unit_can_reach(&pd->bl,bl->x,bl->y)		// 到達可能性判定
				 && atn_rand()%1000<1000/(++(*itc)) ){	// 範囲内PCで等確率にする
				pd->target_id=bl->id;
			}
		}
	}
	return 0;
}

static int pet_ai_sub_hard(struct pet_data *pd,unsigned int tick)
{
	struct map_session_data *sd = NULL;
	struct mob_data *md = NULL;
	int dist,i=0,dx,dy;

	nullpo_retr(0, pd);

	sd = pd->msd;

	if(pd->bl.prev == NULL || sd == NULL || sd->bl.prev == NULL)
		return 0;

	if(DIFF_TICK(tick,pd->last_thinktime) < MIN_PETTHINKTIME)
		return 0;
	if(pd->ud.attacktimer != -1 || pd->ud.skilltimer != -1 || pd->bl.m != sd->bl.m)
		return 0;
	// 歩行中は３歩ごとにAI処理を行う
	if( pd->ud.walktimer != -1 && pd->ud.walkpath.path_pos <= 2)
		return 0;
	pd->last_thinktime=tick;

	// ペットによるルート
	if(!pd->target_id && pd->lootitem_count < LOOTITEM_SIZE &&
		battle_config.pet_lootitem && pd->loottype>0 && DIFF_TICK(gettick(),pd->lootitem_timer)>0)
		map_foreachinarea(pet_ai_sub_hard_lootsearch,pd->bl.m,
						  pd->bl.x-AREA_SIZE*2,pd->bl.y-AREA_SIZE*2,
						  pd->bl.x+AREA_SIZE*2,pd->bl.y+AREA_SIZE*2,
						  BL_ITEM,pd,&i);

	if(sd->pet.intimate > 0) {
		dist = unit_distance(sd->bl.x,sd->bl.y,pd->bl.x,pd->bl.y);
		if(dist > 12) {
			if(pd->target_id > 0)
				pet_unlocktarget(pd);
			if(pd->ud.walktimer != -1 && unit_distance(pd->ud.to_x,pd->ud.to_y,sd->bl.x,sd->bl.y) < 3)
				return 0;
			pd->speed = (sd->speed>>1);
			if(pd->speed <= 0)
				pd->speed = 1;
			pet_calc_pos(pd,sd->bl.x,sd->bl.y,sd->dir);
			if(unit_walktoxy(&pd->bl,pd->ud.to_x,pd->ud.to_y))
				pet_randomwalk(pd,tick);
		}
		else if(pd->target_id  > MAX_FLOORITEM) {
			int mode=mob_db[pd->class].mode;
			int race=mob_db[pd->class].race;
			md = map_id2md(pd->target_id);
			if(md == NULL || pd->bl.m != md->bl.m || md->bl.prev == NULL ||
				unit_distance(pd->bl.x,pd->bl.y,md->bl.x,md->bl.y) > 13)
				pet_unlocktarget(pd);
			else if(mob_db[pd->class].mexp <= 0 && !(mode&0x20) && (md->option & 0x06 && race!=4 && race!=6) )
				pet_unlocktarget(pd);
			else if(!battle_check_range(&pd->bl,&md->bl,mob_db[pd->class].range)){
				if(pd->ud.walktimer != -1 && unit_distance(pd->ud.to_x,pd->ud.to_y,md->bl.x,md->bl.y) < 2)
					return 0;
				if( !unit_can_reach(&pd->bl,md->bl.x,md->bl.y))
					pet_unlocktarget(pd);
				else {
					int ret;
					i=0;
					if(battle_config.pet_speed_is_same_as_pc == 1)
						pd->speed = status_get_speed(&sd->bl);
					else
						pd->speed = sd->petDB->speed;
					do {
						if(i==0) {	// 最初はAEGISと同じ方法で検索
							dx=md->bl.x - pd->bl.x;
							dy=md->bl.y - pd->bl.y;
							if(dx<0) dx++;
							else if(dx>0) dx--;
							if(dy<0) dy++;
							else if(dy>0) dy--;
						}
						else {	// だめならAthena式(ランダム)
							dx=md->bl.x - pd->bl.x + rand()%3 - 1;
							dy=md->bl.y - pd->bl.y + rand()%3 - 1;
						}
						ret=unit_walktoxy(&pd->bl,pd->bl.x+dx,pd->bl.y+dy);
						i++;
					} while(ret && i<5);

					if(ret) { // 移動不可能な所からの攻撃なら2歩下る
						if(dx<0) dx=2;
						else if(dx>0) dx=-2;
						if(dy<0) dy=2;
						else if(dy>0) dy=-2;
						unit_walktoxy(&pd->bl,pd->bl.x+dx,pd->bl.y+dy);
					}
				}
			}
			else {
				if(pd->ud.walktimer != -1)
					unit_stop_walking(&pd->bl,1);
				if(pd->ud.attacktimer != -1)
					return 0;
				if ( /*battle_config.pet_status_support && */
					pd->a_skill &&
					/* (!battle_config.pet_equip_required || pd->equip > 0) && */
					(rand()%100 < (pd->a_skill->rate +pd->msd->pet.intimate*pd->a_skill->bonusrate/1000))
				) {
					if( skill_get_inf( pd->a_skill->id ) & 2 ) {
						// 場所指定
						unit_skilluse_pos( &pd->bl, md->bl.x, md->bl.y, pd->a_skill->id, pd->a_skill->lv);
					} else {
						// ID指定
						unit_skilluse_id(&pd->bl, pd->target_id, pd->a_skill->id, pd->a_skill->lv);
					}
				} else if(battle_config.pet_attack_support) {
					unit_attack( &pd->bl, pd->target_id, 0);
				}
			}
		}
		else if(pd->target_id > 0){	// ルート処理
			const int range=3;	// ルートに行く射程範囲
			struct block_list *bl_item = map_id2bl(pd->target_id);

			if(bl_item == NULL || bl_item->type != BL_ITEM ||bl_item->m != pd->bl.m ||
				 (dist=unit_distance(pd->bl.x,pd->bl.y,bl_item->x,bl_item->y))>=range){
				 // 遠すぎるかアイテムがなくなった
 				pet_unlocktarget(pd);
			}
			else if(dist){
				if(pd->ud.walktimer!=-1 && (DIFF_TICK(pd->next_walktime,tick)<0 || unit_distance(pd->ud.to_x,pd->ud.to_y,bl_item->x,bl_item->y) <= 0))
					return 0; // 既に移動中

				pd->next_walktime=tick+500;
				dx=bl_item->x - pd->bl.x;
				dy=bl_item->y - pd->bl.y;
				if(battle_config.pet_speed_is_same_as_pc == 1)
					pd->speed = status_get_speed(&sd->bl);
				else
					pd->speed = sd->petDB->speed;

				unit_walktoxy(&pd->bl,pd->bl.x+dx,pd->bl.y+dy);
			}
			else{	// アイテムまでたどり着いた
				struct flooritem_data *fitem = (struct flooritem_data *)bl_item;

				if(pd->ud.attacktimer != -1)
					return 0; // 攻撃中
				if(pd->ud.walktimer != -1)	// 歩行中なら停止
					unit_stop_walking(&pd->bl,1);
				if(pd->loottype==1){					// ペット自身が所有する場合
					if(pd->lootitem_count < LOOTITEM_SIZE){
						memcpy(&pd->lootitem[pd->lootitem_count++],&fitem->item_data,sizeof(pd->lootitem[0]));
						pd->lootitem_weight += itemdb_search(fitem->item_data.nameid)->weight*fitem->item_data.amount;
					}
					else if(pd->lootitem_count >= LOOTITEM_SIZE) {
						pet_unlocktarget(pd);
						return 0;
					}
					else {
						if(pd->lootitem[0].card[0] == (short)0xff00)
							intif_delete_petdata(*((long *)(&pd->lootitem[0].card[1])));
						for(i=0;i<LOOTITEM_SIZE-1;i++)
							memcpy(&pd->lootitem[i],&pd->lootitem[i+1],sizeof(pd->lootitem[0]));
						memcpy(&pd->lootitem[LOOTITEM_SIZE-1],&fitem->item_data,sizeof(pd->lootitem[0]));
					}
				}else if(pd->loottype==2){					// ペットが拾った瞬間に飼い主へ
					if(pc_additem(pd->msd,&fitem->item_data,fitem->item_data.amount)){
						pet_unlocktarget(pd);
						return 0;
					}
				}else
					return 0;
				map_clearflooritem(bl_item->id);
				pet_unlocktarget(pd);
			}
		}
		else {
			// 待機時、適当に歩き回る
/*			if(pc_issit(sd)){
				if(dist < 5 && unit_distance(pd->ud.to_x,pd->ud.to_y,sd->bl.x,sd->bl.y) < 5){
					if(unit_walktoxy(&pd->bl,pd->ud.to_x,pd->ud.to_y))
						pet_randomwalk(pd,tick);
					return 0;
				}
				if(!atn_rand()%100)
					pet_randomwalk(pd,tick);
				return 0;
			}
*/
			if(dist <= 3 || (pd->ud.walktimer != -1 && unit_distance(pd->ud.to_x,pd->ud.to_y,sd->bl.x,sd->bl.y) < 3))
				return 0;
			if(battle_config.pet_speed_is_same_as_pc == 1)
				pd->speed = status_get_speed(&sd->bl);
			else
				pd->speed = sd->petDB->speed;
			pet_calc_pos(pd,sd->bl.x,sd->bl.y,sd->dir);
			if(unit_walktoxy(&pd->bl,pd->ud.to_x,pd->ud.to_y))
				pet_randomwalk(pd,tick);
		}
	}
	else {
		if(battle_config.pet_leave){	// 新密度0で即刻消えるか
			unit_free(&sd->pd->bl,0);
			sd->status.pet_id = 0;
			sd->pd = NULL;
			intif_delete_petdata(sd->pet.pet_id);
			pc_makesavestatus(sd);
			chrif_save(sd);
			storage_storage_save(sd);
		}else{
			if(battle_config.pet_speed_is_same_as_pc == 1)
				pd->speed = status_get_speed(&sd->bl);
			else
				pd->speed = sd->petDB->speed;
			if(pd->ud.attacktimer != -1)
				unit_stopattack(&pd->bl);
			pet_randomwalk(pd,tick);
		}
	}

	return 0;
}

static int pet_ai_sub_foreachclient(struct map_session_data *sd,va_list ap)
{
	unsigned int tick;

	nullpo_retr(0, sd);
	nullpo_retr(0, ap);

	tick=va_arg(ap,unsigned int);
	if(sd->status.pet_id && sd->pd && sd->petDB)
		pet_ai_sub_hard(sd->pd,tick);

	return 0;
}

static int pet_ai_hard(int tid,unsigned int tick,int id,int data)
{
	clif_foreachclient(pet_ai_sub_foreachclient,tick);

	return 0;
}

int pet_lootitem_drop(struct pet_data *pd,struct map_session_data *sd)
{
	int i,flag=0;

	if(pd){
		if(pd->lootitem) {
			for(i=0;i<pd->lootitem_count;i++) {
				struct delay_item_drop2 *ditem;

				ditem=(struct delay_item_drop2 *)aCalloc(1,sizeof(struct delay_item_drop2));
				memcpy(&ditem->item_data,&pd->lootitem[i],sizeof(pd->lootitem[0]));
				ditem->m = pd->bl.m;
				ditem->x = pd->bl.x;
				ditem->y = pd->bl.y;
				ditem->first_sd = 0;
				ditem->second_sd = 0;
				ditem->third_sd = 0;
				// 落とさないで直接PCのItem欄へ
				if(sd){
					if((flag = pc_additem(sd,&ditem->item_data,ditem->item_data.amount))){
						clif_additem(sd,0,0,flag);
						map_addflooritem(&ditem->item_data,ditem->item_data.amount,ditem->m,ditem->x,ditem->y,&ditem->first_sd->bl,&ditem->second_sd->bl,&ditem->third_sd->bl,0);
					}
					free(ditem);
				}
				else
					add_timer2(gettick()+540+i,pet_delay_item_drop2,(int)ditem,0,TIMER_FREE_ID);
			}
			memset(pd->lootitem,0,LOOTITEM_SIZE * sizeof(struct item));
			pd->lootitem_count = 0;
			pd->lootitem_weight = 0;
			pd->lootitem_timer = gettick()+10000;	//	10*1000msの間拾わない
		}
	}
	return 1;
}

int pet_delay_item_drop2(int tid,unsigned int tick,int id,int data)
{
	struct delay_item_drop2 *ditem;

	ditem=(struct delay_item_drop2 *)id;

	map_addflooritem(&ditem->item_data,ditem->item_data.amount,ditem->m,ditem->x,ditem->y,&ditem->first_sd->bl,&ditem->second_sd->bl,&ditem->third_sd->bl,0);

	free(ditem);
	return 0;
}

/*==========================================
 * pet support skills [Skotlex]
 *------------------------------------------
 */
int pet_skill_support_timer(int tid,unsigned int tick,int id,int data)
{
	struct map_session_data *sd = map_id2sd(id);
	struct pet_data *pd;
	short rate = 100;

	if(sd==NULL || sd->pd == NULL)
		return 1;

	pd=sd->pd;

	if(pd->s_skill == NULL || pd->s_skill->timer != tid) {
		if(battle_config.error_log)
		{
			if (pd->s_skill)
				printf("pet_skill_support_timer %d != %d\n",pd->s_skill->timer,tid);
			else
				printf("pet_skill_support_timer called with no support skill defined (tid=%d)\n",tid);
		}
		return 0;
	}

	if( unit_isdead(&sd->bl) || pd->ud.walktimer != -1 || pd->ud.skilltimer != -1 ||
		(rate = sd->status.sp*100/sd->status.max_sp) > pd->s_skill->sp ||
		(rate = sd->status.hp*100/sd->status.max_hp) > pd->s_skill->hp
	) {  //Wait (how long? 1 sec for every 10% of remaining)
		pd->s_skill->timer=add_timer(gettick()+(rate>10?rate:10)*100,pet_skill_support_timer,sd->bl.id,0);
		return 0;
	}

	if( skill_get_inf( pd->s_skill->id ) & 2 ) {
		// 場所指定
		unit_skilluse_pos( &pd->bl, sd->bl.x, sd->bl.y, pd->s_skill->id, pd->s_skill->lv);
	} else {
		// ID指定
		unit_skilluse_id(&pd->bl, sd->bl.id, pd->s_skill->id, pd->s_skill->lv);
	}

	pd->s_skill->timer=add_timer(tick+pd->s_skill->delay*1000,pet_skill_support_timer,sd->bl.id,0);

	return 0;
}

/*==========================================
 *ペットデータ読み込み
 *------------------------------------------
 */
int read_petdb()
{
	FILE *fp;
	char line[1024];
	int i,j=0,k;
	int lines;
	struct script_code *script = NULL;
	char *filename[]={"db/pet_db.txt","db/addon/pet_db_add.txt"};

	// DB情報の初期化
	for(i=0; i<pet_count; i++) {
		if(pet_db[i].script)
			script_free_code(pet_db[i].script);
	}
	memset(pet_db,0,sizeof(pet_db));
	pet_count = 0;

	for(i=0;i<2;i++){
		fp=fopen(filename[i],"r");
		if(fp==NULL){
			if(i>0)
				continue;
			printf("can't read %s\n",filename[i]);
			return -1;
		}
		lines = 0;
		while(fgets(line,1020,fp)){
			int nameid,i;
			char *str[32],*p,*np;
			lines++;

			if(line[0] == '/' && line[1] == '/')
				continue;

			for(i=0,p=line;i<20;i++){
				if((np=strchr(p,','))!=NULL){
					str[i]=p;
					*np=0;
					p=np+1;
				} else {
					str[i]=p;
					p+=strlen(p);
				}
			}

			nameid=atoi(str[0]);
			if(nameid<=0 || nameid>=MOB_ID_MAX)
				continue;

			if(pet_count >= MAX_PET_DB)
				break;
			k = search_petDB_index(nameid, PET_CLASS);
			j = (k>=0)? k: pet_count;
			//printf("j %d: k %d\n",j,k);

			//MobID,Name,JName,ItemID,EggID,AcceID,FoodID,"Fullness (1回の餌での満腹度増加率%)","HungryDeray (/min)","R_Hungry (空腹時餌やり親密度増加率%)","R_Full (とても満腹時餌やり親密度減少率%)","Intimate (捕獲時親密度%)","Die (死亡時親密度減少率%)","Capture (捕獲率%)",(Name)
			pet_db[j].class = nameid;
			memcpy(pet_db[j].name,str[1],24);
			memcpy(pet_db[j].jname,str[2],24);
			pet_db[j].itemID=atoi(str[3]);
			pet_db[j].EggID=atoi(str[4]);
			pet_db[j].AcceID=atoi(str[5]);
			pet_db[j].FoodID=atoi(str[6]);
			pet_db[j].fullness=atoi(str[7]);
			pet_db[j].hungry_delay=atoi(str[8])*1000;
			pet_db[j].r_hungry=atoi(str[9]);
			if(pet_db[j].r_hungry <= 0)
				pet_db[j].r_hungry=1;
			pet_db[j].r_full=atoi(str[10]);
			pet_db[j].intimate=atoi(str[11]);
			pet_db[j].die=atoi(str[12]);
			pet_db[j].capture=atoi(str[13]);
			pet_db[j].speed=atoi(str[14]);
			pet_db[j].s_perfor=(char)atoi(str[15]);
			pet_db[j].talk_convert_class=atoi(str[16]);
			pet_db[j].attack_rate=atoi(str[17]);
			pet_db[j].defence_attack_rate=atoi(str[18]);
			pet_db[j].change_target_rate=atoi(str[19]);

			if((np=strchr(p,'{'))==NULL)
				continue;

			if(pet_db[j].script)
				script_free_code(pet_db[j].script);
			script = parse_script(np,filename[i],lines);

			pet_db[j].script = (script != &error_code)? script: NULL;
			if(k<0)
				pet_count++;
		}
		fclose(fp);
		printf("read %s done (count=%d)\n",filename[i],pet_count);
	}
	return 0;
}

/*==========================================
 * スキル関係初期化処理
 *------------------------------------------
 */
int do_init_pet(void)
{
	read_petdb();

	add_timer_func_list(pet_hungry,"pet_hungry");
	add_timer_func_list(pet_ai_hard,"pet_ai_hard");
	add_timer_interval(gettick()+MIN_PETTHINKTIME,pet_ai_hard,0,0,MIN_PETTHINKTIME);

	return 0;
}

int do_final_pet(void) {
	int i;
	for(i = 0;i < pet_count; i++) {
		if(pet_db[i].script) {
			script_free_code(pet_db[i].script);
		}
	}
	return 0;
}
