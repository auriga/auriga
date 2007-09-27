// storage.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "db.h"
#include "malloc.h"
#include "nullpo.h"
#include "itemdb.h"
#include "clif.h"
#include "intif.h"
#include "pc.h"
#include "storage.h"
#include "guild.h"
#include "battle.h"
#include "chrif.h"

#ifdef MEMWATCH
#include "memwatch.h"
#endif

static struct dbt *storage_db;
static struct dbt *guild_storage_db;

/*==========================================
 * 倉庫内アイテムソート
 *------------------------------------------
 */
static int storage_comp_item_by_key(const void *_i1, const void *_i2)
{
	struct item *i1 = (struct item *)_i1;
	struct item *i2 = (struct item *)_i2;

	if(i1->id == 0 && i2->id != 0)
		return 1;
	if(i1->id != 0 && i2->id == 0)
		return -1;

	if(i1->id > i2->id)
		return 1;
	if(i1->id < i2->id)
		return -1;

	return 0;
}

static int storage_comp_item_by_nameid(const void *_i1, const void *_i2)
{
	struct item *i1=(struct item *)_i1;
	struct item *i2=(struct item *)_i2;

	if(i1->nameid == i2->nameid)
		return 0;
	if(!(i1->nameid) || !(i1->amount))
		return 1;
	if(!(i2->nameid) || !(i2->amount))
		return -1;

	return i1->nameid - i2->nameid;
}

static int storage_comp_item_by_type(const void *_i1, const void *_i2)
{
	struct item *i1 = (struct item *)_i1;
	struct item *i2 = (struct item *)_i2;
	struct item_data *data1, *data2;

	if(i1->nameid == 0 || i2->nameid == 0) {
		// 末尾に集めるので反転
		return i2->nameid - i1->nameid;
	}

	data1 = itemdb_search(i1->nameid);
	data2 = itemdb_search(i2->nameid);

	if(data1->type > data2->type)
		return 1;
	if(data1->type < data2->type)
		return -1;

	// 武器・防具ならLOCでソート
	if(data1->type == 4 || data1->type == 5) {
		if(data1->equip > data2->equip)
			return 1;
		if(data1->equip < data2->equip)
			return -1;
	}

	// 最後はアイテムIDでソート
	if(data1->nameid > data2->nameid)
		return 1;
	if(data1->nameid < data2->nameid)
		return -1;

	return 0;
}

static void storage_sortitem(struct item *item,int max,unsigned int *sortkey,int flag)
{
	int (*cmp)(const void *,const void *) = NULL;

	nullpo_retv(item);

	switch(flag) {
		case 1: cmp = storage_comp_item_by_key;    break;
		case 2: cmp = storage_comp_item_by_nameid; break;
		case 3: cmp = storage_comp_item_by_type;   break;
	}

	if(cmp) {
		int i;
		qsort(item, max, sizeof(struct item), cmp);

		// ソートキーのリナンバリング
		*sortkey = 0;
		for(i=0; i<max; i++) {
			if(item->nameid > 0)
				item->id = ++(*sortkey);
			else
				item->id = 0;
			item++;
		}
	}
	return;
}

/*==========================================
 * カプラ倉庫データベース
 *------------------------------------------
 */
static struct storage *account2storage(int account_id)
{
	struct storage *stor;

	stor = (struct storage *)numdb_search(storage_db,account_id);
	if(stor == NULL) {
		stor = (struct storage *)aCalloc(1,sizeof(struct storage));
		stor->account_id = account_id;
		numdb_insert(storage_db,stor->account_id,stor);
	}
	return stor;
}

/*==========================================
 * カプラ倉庫を削除
 *------------------------------------------
 */
void storage_delete(int account_id)
{
	struct storage *stor = (struct storage *)numdb_erase(storage_db,account_id);

	if(stor)
		aFree(stor);

	return;
}

/*==========================================
 * カプラ倉庫を開く
 *------------------------------------------
 */
int storage_storageopen(struct map_session_data *sd)
{
	struct storage *stor;

	nullpo_retr(0, sd);

	if(sd->state.storage_flag == 1)
		return 0;	// 既にカプラ倉庫を開いている

	if((stor = (struct storage *)numdb_search(storage_db,sd->status.account_id)) != NULL) {
		if(stor->storage_status)
			return 1;
		stor->storage_status = 1;
	}

	if(sd->state.storage_flag == 2)
		storage_guild_storageclose(sd); // ギルド倉庫をすでに開いている場合閉じる

	if(stor != NULL) {
		sd->state.storage_flag = 1;
		clif_storageitemlist(sd,stor);
		clif_storageequiplist(sd,stor);
		clif_updatestorageamount(sd,stor);
	} else {
		intif_request_storage(sd->status.account_id);
	}
	return 0;
}

/*==========================================
 * カプラ倉庫データの受信
 *------------------------------------------
 */
int storage_storageload(int account_id, struct storage *s)
{
	struct map_session_data *sd;
	struct storage *stor;

	nullpo_retr(1, s);

	sd = map_id2sd(account_id);
	if(sd == NULL || sd->state.waitingdisconnect) {
		if(battle_config.error_log && sd == NULL)
			printf("storage_storageload: user not found %d\n", account_id);
		storage_delete(account_id);
		return 1;
	}

	// 既に倉庫を開いてないかチェック
	if(sd->state.storage_flag == 1)
		return 0;
	if(sd->state.storage_flag == 2)
		storage_guild_storageclose(sd);

	stor = account2storage(account_id);

	if(battle_config.save_log)
		printf("storageload: %d\n", account_id);

	memcpy(stor, s, sizeof(struct storage));
	storage_sortitem(stor->store_item, MAX_STORAGE, &stor->sortkey, battle_config.personal_storage_sort);
	stor->storage_status   = 1;
	sd->state.storage_flag = 1;
	clif_storageitemlist(sd,stor);
	clif_storageequiplist(sd,stor);
	clif_updatestorageamount(sd,stor);

	return 0;
}

/*==========================================
 * カプラ倉庫へアイテム追加
 *------------------------------------------
 */
static int storage_additem(struct map_session_data *sd,struct storage *stor,struct item *item_data,int amount)
{
	struct item_data *data;
	int i;

	nullpo_retr(1, sd);
	nullpo_retr(1, stor);
	nullpo_retr(1, item_data);

	if(item_data->nameid <= 0 || amount <= 0)
		return 1;

	nullpo_retr(1, data = itemdb_search(item_data->nameid));

	if(!itemdb_isequip2(data)) {
		// 装備品ではないので、既所有品なら個数のみ変化させる
		for(i=0; i<MAX_STORAGE; i++) {
			if(stor->store_item[i].nameid == item_data->nameid &&
			   stor->store_item[i].card[0] == item_data->card[0] &&
			   stor->store_item[i].card[1] == item_data->card[1] &&
			   stor->store_item[i].card[2] == item_data->card[2] &&
			   stor->store_item[i].card[3] == item_data->card[3])
			{
				if(stor->store_item[i].amount + amount > MAX_AMOUNT)
					return 1;
				stor->store_item[i].amount += amount;
				stor->dirty = 1;
				clif_storageitemadded(sd,stor,i,amount);
				return 0;
			}
		}
	} else if(amount != 1) {
		return 1;
	}

	// 装備品か未所有品だったので空き欄へ追加
	for(i=0; i<MAX_STORAGE; i++) {
		if(stor->store_item[i].nameid == 0) {
			memcpy(&stor->store_item[i],item_data,sizeof(stor->store_item[0]));
			stor->store_item[i].id     = ++stor->sortkey;
			stor->store_item[i].amount = amount;
			stor->storage_amount++;
			stor->dirty = 1;
			clif_storageitemadded(sd,stor,i,amount);
			clif_updatestorageamount(sd,stor);
			return 0;
		}
	}

	return 1;
}

/*==========================================
 * カプラ倉庫からアイテムを減らす
 *------------------------------------------
 */
static void storage_delitem(struct map_session_data *sd,struct storage *stor,int n,int amount)
{
	nullpo_retv(sd);
	nullpo_retv(stor);

	if(stor->store_item[n].nameid == 0 || stor->store_item[n].amount < amount)
		return;

	stor->store_item[n].amount -= amount;
	if(stor->store_item[n].amount <= 0) {
		memset(&stor->store_item[n],0,sizeof(stor->store_item[0]));
		stor->store_item[n].id = 0;
		stor->storage_amount--;
		clif_updatestorageamount(sd,stor);
	}
	stor->dirty = 1;
	clif_storageitemremoved(sd,n,amount);

	return;
}

/*==========================================
 * カプラ倉庫へ入れる
 *------------------------------------------
 */
void storage_storageadd(struct map_session_data *sd, int idx, int amount)
{
	struct storage *stor;

	nullpo_retv(sd);
	nullpo_retv(stor = (struct storage *)numdb_search(storage_db,sd->status.account_id));

	if(!stor->storage_status)
		return;
	if(idx < 0 || idx >= MAX_INVENTORY)
		return;
	if(itemdb_isstorageable(sd->status.inventory[idx].nameid) == 0)
		return;
	if(amount < 1 || amount > sd->status.inventory[idx].amount)
		return;

	if(storage_additem(sd, stor, &sd->status.inventory[idx], amount) == 0)
		pc_delitem(sd, idx, amount, 0);

	return;
}

/*==========================================
 * カプラ倉庫から出す
 *------------------------------------------
 */
void storage_storageget(struct map_session_data *sd, int idx, int amount)
{
	struct storage *stor;
	int flag;

	nullpo_retv(sd);
	nullpo_retv(stor = (struct storage *)numdb_search(storage_db,sd->status.account_id));

	if(!stor->storage_status)
		return;
	if(idx < 0 || idx >= MAX_STORAGE)
		return;
	if(amount < 1 || amount > stor->store_item[idx].amount)
		return;

	if((flag = pc_additem(sd, &stor->store_item[idx], amount)) == 0)
		storage_delitem(sd, stor, idx, amount);
	else
		clif_additem(sd,0,0,flag);

	return;
}

/*==========================================
 * カプラ倉庫へカートから入れる
 *------------------------------------------
 */
void storage_storageaddfromcart(struct map_session_data *sd, int idx, int amount)
{
	struct storage *stor;

	nullpo_retv(sd);
	nullpo_retv(stor = (struct storage *)numdb_search(storage_db,sd->status.account_id));

	if(!stor->storage_status)
		return;
	if(idx < 0 || idx >= MAX_CART)
		return;
	if(itemdb_isstorageable(sd->status.cart[idx].nameid) == 0)
		return;
	if(amount < 1 || amount > sd->status.cart[idx].amount)
		return;

	if(storage_additem(sd, stor, &sd->status.cart[idx], amount) == 0)
		pc_cart_delitem(sd, idx, amount, 0);

	return;
}

/*==========================================
 * カプラ倉庫からカートへ出す
 *------------------------------------------
 */
void storage_storagegettocart(struct map_session_data *sd, int idx, int amount)
{
	struct storage *stor;

	nullpo_retv(sd);
	nullpo_retv(stor = (struct storage *)numdb_search(storage_db,sd->status.account_id));

	if(!stor->storage_status)
		return;
	if(idx < 0 || idx >= MAX_STORAGE)
		return;
	if(itemdb_iscartable(stor->store_item[idx].nameid) == 0)	// カートへ出せるかチェック
		return;
	if(amount < 1 || amount > stor->store_item[idx].amount)
		return;

	if(pc_cart_additem(sd, &stor->store_item[idx], amount) == 0)
		storage_delitem(sd, stor, idx, amount);

	return;
}

/*==========================================
 * カプラ倉庫を閉じて保存
 *------------------------------------------
 */
void storage_storageclose(struct map_session_data *sd)
{
	struct storage *stor;

	nullpo_retv(sd);
	nullpo_retv(stor = (struct storage *)numdb_search(storage_db,sd->status.account_id));

	if(stor->dirty) {
		storage_sortitem(stor->store_item, MAX_STORAGE, &stor->sortkey, battle_config.personal_storage_sort);
		intif_send_storage(stor);
		if(battle_config.save_player_when_storage_closed) {
			chrif_save(sd,0);
		}
		stor->dirty = 0;
	}
	stor->storage_status   = 0;
	sd->state.storage_flag = 0;
	clif_storageclose(sd);

	return;
}

/*==========================================
 * カプラ倉庫の保存
 *------------------------------------------
 */
void storage_storage_save(struct map_session_data *sd)
{
	struct storage *stor;

	nullpo_retv(sd);

	stor = (struct storage *)numdb_search(storage_db,sd->status.account_id);
	if(stor && stor->dirty) {
		intif_send_storage(stor);
		stor->dirty = 0;
	}

	return;
}


/*==========================================
 * ギルド倉庫データベース
 *------------------------------------------
 */
static struct guild_storage *guild2storage(int guild_id)
{
	struct guild_storage *gs = NULL;

	if(guild_search(guild_id) != NULL) {
		gs = (struct guild_storage *)numdb_search(guild_storage_db,guild_id);
		if(gs == NULL) {
			gs = (struct guild_storage *)aCalloc(1,sizeof(struct guild_storage));
			gs->guild_id = guild_id;
			numdb_insert(guild_storage_db,gs->guild_id,gs);
		}
	}

	return gs;
}

/*==========================================
 * ギルド倉庫を削除
 *------------------------------------------
 */
void storage_guild_delete(int guild_id)
{
	struct guild_storage *gstor = (struct guild_storage *)numdb_erase(guild_storage_db,guild_id);

	if(gstor)
		aFree(gstor);

	return;
}

/*==========================================
 * ギルド倉庫を開く
 *------------------------------------------
 */
int storage_guild_storageopen(struct map_session_data *sd)
{
	struct guild_storage *gstor;

	nullpo_retr(0, sd);

	if(sd->status.guild_id <= 0)
		return 2;
	if(sd->state.storage_flag == 2)
		return 3;	// 既にギルド倉庫を開いている

	if(sd->state.storage_flag == 1)
		storage_storageclose(sd); // カプラ倉庫をすでに開いている場合閉じる

	if((gstor = (struct guild_storage *)numdb_search(guild_storage_db,sd->status.guild_id)) != NULL) {
		gstor->storage_status  = 1;
		sd->state.storage_flag = 2;
		clif_guildstorageitemlist(sd,gstor);
		clif_guildstorageequiplist(sd,gstor);
		clif_updateguildstorageamount(sd,gstor);
	} else {
		intif_request_guild_storage(sd->status.account_id,sd->status.guild_id);
	}

	return 0;
}

/*==========================================
 * ギルド倉庫データの受信
 *------------------------------------------
 */
int storage_guild_storageload(int account_id, int guild_id, struct guild_storage *s)
{
	struct map_session_data *sd;
	struct guild_storage *gstor;

	nullpo_retr(1, s);

	if(guild_id <= 0)
		return 0;

	sd = map_id2sd(account_id);
	if(sd == NULL || sd->state.waitingdisconnect) {
		if(battle_config.error_log && sd == NULL)
			printf("storage_guild_storageload: user not found %d\n", account_id);
		intif_unlock_guild_storage(guild_id);
		return 1;
	}

	// 既に倉庫を開いてないかチェック
	if(sd->state.storage_flag == 2)
		return 0;
	if(sd->state.storage_flag == 1)
		storage_storageclose(sd);

	gstor = guild2storage(guild_id);
	if(!gstor) {
		if(battle_config.error_log)
			printf("storage_guild_storageload: error guild_id %d not exist\n", guild_id);
		return 1;
	}

	if(battle_config.save_log)
		printf("guild_storageload: %d\n", account_id);

	memcpy(gstor, s, sizeof(struct guild_storage));
	storage_sortitem(gstor->store_item, MAX_GUILD_STORAGE, &gstor->sortkey, battle_config.guild_storage_sort);
	gstor->storage_status  = 1;
	sd->state.storage_flag = 2;
	clif_guildstorageitemlist(sd,gstor);
	clif_guildstorageequiplist(sd,gstor);
	clif_updateguildstorageamount(sd,gstor);

	return 0;
}

/*==========================================
 * ギルド倉庫へアイテム追加
 *------------------------------------------
 */
static int storage_guild_additem(struct map_session_data *sd,struct guild_storage *stor,struct item *item_data,int amount)
{
	struct item_data *data;
	int i;

	nullpo_retr(1, sd);
	nullpo_retr(1, stor);
	nullpo_retr(1, item_data);

	if(item_data->nameid <= 0 || amount <= 0)
		return 1;

	nullpo_retr(1, data = itemdb_search(item_data->nameid));

	if(!itemdb_isequip2(data)) {
		// 装備品ではないので、既所有品なら個数のみ変化させる
		for(i=0; i<MAX_GUILD_STORAGE; i++) {
			if(stor->store_item[i].nameid == item_data->nameid &&
			   stor->store_item[i].card[0] == item_data->card[0] &&
			   stor->store_item[i].card[1] == item_data->card[1] &&
			   stor->store_item[i].card[2] == item_data->card[2] &&
			   stor->store_item[i].card[3] == item_data->card[3])
			{
				if(stor->store_item[i].amount + amount > MAX_AMOUNT)
					return 1;
				stor->store_item[i].amount += amount;
				stor->dirty = 1;
				clif_guildstorageitemadded(sd,stor,i,amount);
				return 0;
			}
		}
	} else if(amount != 1) {
		return 1;
	}

	// 装備品か未所有品だったので空き欄へ追加
	for(i=0; i<MAX_GUILD_STORAGE; i++) {
		if(stor->store_item[i].nameid == 0) {
			memcpy(&stor->store_item[i],item_data,sizeof(stor->store_item[0]));
			stor->store_item[i].id     = ++stor->sortkey;
			stor->store_item[i].amount = amount;
			stor->storage_amount++;
			stor->dirty = 1;
			clif_guildstorageitemadded(sd,stor,i,amount);
			clif_updateguildstorageamount(sd,stor);
			return 0;
		}
	}

	return 1;
}

/*==========================================
 * ギルド倉庫からアイテムを減らす
 *------------------------------------------
 */
static void storage_guild_delitem(struct map_session_data *sd,struct guild_storage *stor,int n,int amount)
{
	nullpo_retv(sd);
	nullpo_retv(stor);

	if(stor->store_item[n].nameid == 0 || stor->store_item[n].amount < amount)
		return;

	stor->store_item[n].amount -= amount;
	if(stor->store_item[n].amount == 0) {
		memset(&stor->store_item[n],0,sizeof(stor->store_item[0]));
		stor->store_item[n].id = 0;
		stor->storage_amount--;
		clif_updateguildstorageamount(sd,stor);
	}
	stor->dirty = 1;
	clif_storageitemremoved(sd,n,amount);

	return;
}

/*==========================================
 * ギルド倉庫へ入れる
 *------------------------------------------
 */
void storage_guild_storageadd(struct map_session_data *sd, int idx, int amount)
{
	struct guild_storage *stor;

	nullpo_retv(sd);

	if((stor = (struct guild_storage *)numdb_search(guild_storage_db,sd->status.guild_id)) == NULL)
		return;
	if(!stor->storage_status)
		return;
	if(idx < 0 || idx >= MAX_INVENTORY)
		return;
	if(itemdb_isstorageable(sd->status.inventory[idx].nameid) == 0)
		return;
	if(amount < 1 || amount > sd->status.inventory[idx].amount)
		return;

	if(storage_guild_additem(sd, stor, &sd->status.inventory[idx], amount) == 0)
		pc_delitem(sd, idx, amount, 0);

	return;
}

/*==========================================
 * ギルド倉庫から出す
 *------------------------------------------
 */
void storage_guild_storageget(struct map_session_data *sd, int idx, int amount)
{
	struct guild_storage *stor;
	int flag;

	nullpo_retv(sd);

	if((stor = (struct guild_storage *)numdb_search(guild_storage_db,sd->status.guild_id)) == NULL)
		return;
	if(!stor->storage_status)
		return;
	if(idx < 0 || idx >= MAX_GUILD_STORAGE)
		return;
	if(amount < 1 || amount > stor->store_item[idx].amount)
		return;

	if((flag = pc_additem(sd,&stor->store_item[idx],amount)) == 0)
		storage_guild_delitem(sd, stor, idx, amount);
	else
		clif_additem(sd,0,0,flag);

	return;
}

/*==========================================
 * ギルド倉庫へカートから入れる
 *------------------------------------------
 */
void storage_guild_storageaddfromcart(struct map_session_data *sd, int idx, int amount)
{
	struct guild_storage *stor;

	nullpo_retv(sd);

	if((stor = (struct guild_storage *)numdb_search(guild_storage_db,sd->status.guild_id)) == NULL)
		return;
	if(!stor->storage_status)
		return;
	if(idx < 0 || idx >= MAX_CART)
		return;
	if(itemdb_isstorageable(sd->status.cart[idx].nameid) == 0)
		return;
	if(amount < 1 || amount > sd->status.cart[idx].amount)
		return;

	if(storage_guild_additem(sd, stor, &sd->status.cart[idx], amount) == 0)
		pc_cart_delitem(sd, idx, amount, 0);

	return;
}

/*==========================================
 * ギルド倉庫からカートへ出す
 *------------------------------------------
 */
void storage_guild_storagegettocart(struct map_session_data *sd, int idx, int amount)
{
	struct guild_storage *stor;

	nullpo_retv(sd);

	if((stor = (struct guild_storage *)numdb_search(guild_storage_db,sd->status.guild_id)) == NULL)
		return;
	if(!stor->storage_status)
		return;
	if(idx < 0 || idx >= MAX_GUILD_STORAGE)
		return;
	if(itemdb_iscartable(stor->store_item[idx].nameid) == 0)	// カートへ出せるかチェック
		return;
	if(amount < 1 || amount > stor->store_item[idx].amount)
		return;

	if(pc_cart_additem(sd, &stor->store_item[idx], amount) == 0)
		storage_guild_delitem(sd, stor, idx, amount);

	return;
}

/*==========================================
 * ギルド倉庫を閉じて保存
 *------------------------------------------
 */
void storage_guild_storageclose(struct map_session_data *sd)
{
	struct guild_storage *stor;

	nullpo_retv(sd);
	nullpo_retv(stor = (struct guild_storage *)numdb_search(guild_storage_db,sd->status.guild_id));

	if(stor->dirty) {
		storage_sortitem(stor->store_item, MAX_GUILD_STORAGE, &stor->sortkey, battle_config.guild_storage_sort);
		intif_send_guild_storage(sd->status.account_id,stor);
		if(battle_config.save_player_when_storage_closed) {
			chrif_save(sd,0);
		}
		stor->dirty = 0;
	}
	stor->storage_status   = 0;
	sd->state.storage_flag = 0;
	clif_storageclose(sd);
	intif_unlock_guild_storage(sd->status.guild_id);

	return;
}

/*==========================================
 * ギルド倉庫の保存
 *------------------------------------------
 */
void storage_guild_storagesave(struct map_session_data *sd)
{
	struct guild_storage *stor;

	nullpo_retv(sd);

	stor = (struct guild_storage *)numdb_search(guild_storage_db,sd->status.guild_id);
	if(stor && stor->dirty) {
		intif_send_guild_storage(sd->status.account_id,stor);
		stor->dirty = 0;
	}

	return;
}


/*==========================================
 *
 *------------------------------------------
 */
static int storage_db_final(void *key,void *data,va_list ap)
{
	aFree(data);
	return 0;
}

static int guild_storage_db_final(void *key,void *data,va_list ap)
{
	aFree(data);
	return 0;
}

/*==========================================
 * キャッシュのクリア
 *------------------------------------------
 */
void storage_clear_cache(void)
{
	if(storage_db)
		numdb_clear(storage_db,storage_db_final);
	if(guild_storage_db)
		numdb_clear(guild_storage_db,guild_storage_db_final);

	return;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
void do_final_storage(void)
{
	if(storage_db) {
		numdb_final(storage_db,storage_db_final);
		storage_db = NULL;
	}
	if(guild_storage_db) {
		numdb_final(guild_storage_db,guild_storage_db_final);
		guild_storage_db = NULL;
	}

	return;
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
void do_init_storage(void)
{
	storage_db = numdb_init();
	guild_storage_db = numdb_init();

	return;
}
