#ifndef _STORAGE_H_
#define _STORAGE_H_

#include "mmo.h"

void storage_delete(int account_id);
int storage_storageopen(struct map_session_data *sd);
int storage_storageload(int account_id, struct storage *s);
void storage_storageadd(struct map_session_data *sd, int idx, int amount);
void storage_storageget(struct map_session_data *sd, int idx, int amount);
void storage_storageaddfromcart(struct map_session_data *sd, int idx, int amount);
void storage_storagegettocart(struct map_session_data *sd, int idx, int amount);
void storage_storageclose(struct map_session_data *sd);
void storage_storage_save(struct map_session_data *sd);

void storage_guild_delete(int guild_id);
int storage_guild_storageopen(struct map_session_data *sd);
int storage_guild_storageload(int account_id, int guild_id, struct guild_storage *s);
void storage_guild_storageadd(struct map_session_data *sd, int idx, int amount);
void storage_guild_storageget(struct map_session_data *sd, int idx, int amount);
void storage_guild_storageaddfromcart(struct map_session_data *sd, int idx, int amount);
void storage_guild_storagegettocart(struct map_session_data *sd, int idx, int amount);
void storage_guild_storageclose(struct map_session_data *sd);
void storage_guild_storagesave(struct map_session_data *sd);

void do_init_storage(void);
void do_final_storage(void);
void storage_clear_cache(void);

#endif
