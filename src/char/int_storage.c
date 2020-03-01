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

#define _INT_STORAGE_C_

#include <string.h>
#include <stdlib.h>

#include "socket.h"
#include "db.h"
#include "malloc.h"
#include "timer.h"

#include "char.h"
#include "int_storage.h"

struct dbt *gstorage_db = NULL;

// 倉庫データの送信
int mapif_load_storage(int fd,int account_id)
{
	const struct storage *s = storagedb_load(account_id);

	WFIFOW(fd,0)=0x3810;
	WFIFOW(fd,2)=sizeof(struct storage)+8;
	WFIFOL(fd,4)=account_id;
	memcpy(WFIFOP(fd,8),s,sizeof(struct storage));
	WFIFOSET(fd,WFIFOW(fd,2));
	return 0;
}

// 倉庫データ保存完了送信
int mapif_save_storage_ack(int fd,int account_id)
{
	WFIFOW(fd,0)=0x3811;
	WFIFOL(fd,2)=account_id;
	WFIFOB(fd,6)=0;
	WFIFOSET(fd,7);
	return 0;
}

// ギルド倉庫データの送信
int mapif_load_guild_storage(int fd,int account_id,int guild_id)
{
	const struct guild_storage *gs = gstoragedb_load(guild_id);

	WFIFOW(fd,0)=0x3818;
	if(gs) {
		WFIFORESERVE( fd, sizeof(struct guild_storage)+12 );
		WFIFOW(fd,2)=sizeof(struct guild_storage)+12;
		WFIFOL(fd,4)=account_id;
		WFIFOL(fd,8)=guild_id;
		memcpy(WFIFOP(fd,12),gs,sizeof(struct guild_storage));
	} else {
		WFIFOW(fd,2)=12;
		WFIFOL(fd,4)=account_id;
		WFIFOL(fd,8)=0;
	}
	WFIFOSET(fd,WFIFOW(fd,2));

	return 0;
}
// ギルド倉庫データ保存完了送信
int mapif_save_guild_storage_ack(int fd, int account_id, int guild_id, bool fail)
{
	WFIFOW(fd,0)=0x3819;
	WFIFOL(fd,2)=account_id;
	WFIFOL(fd,6)=guild_id;
	WFIFOB(fd,10)=fail;
	WFIFOSET(fd,11);
	return 0;
}

// ギルド倉庫ロック要求返答
int mapif_trylock_guild_storage_ack(int fd,int account_id,int guild_id,int npc_id,char flag)
{
	WFIFOW(fd,0)  = 0x381a;
	WFIFOL(fd,2)  = account_id;
	WFIFOL(fd,6)  = guild_id;
	WFIFOL(fd,10) = npc_id;
	WFIFOB(fd,14) = flag;
	WFIFOSET(fd,15);
	return 0;
}

// ギルド倉庫ロック解除返答
int mapif_unlock_guild_storage_ack(int fd,int guild_id,char succeed)
{
	WFIFOW(fd,0) = 0x381b;
	WFIFOL(fd,2) = guild_id;
	WFIFOB(fd,6) = succeed;
	WFIFOSET(fd,7);
	return 0;
}

// ギルド倉庫デッドロックチェック
int mapif_checklock_guild_storage(int guild_id)
{
	unsigned char buf[6];

	WBUFW(buf,0) = 0x381c;
	WBUFL(buf,2) = guild_id;
	mapif_sendall(buf,6);
	return 0;
}

//---------------------------------------------------------
// map serverからの通信

// 倉庫データ要求受信
int mapif_parse_LoadStorage(int fd)
{
	mapif_load_storage(fd,RFIFOL(fd,2));
	return 0;
}

// 倉庫データ受信＆保存
int mapif_parse_SaveStorage(int fd)
{
	int account_id=RFIFOL(fd,4);
	int len=RFIFOW(fd,2);

	if(sizeof(struct storage)!=len-8){
		printf("inter storage: data size error %lu %d\n",(unsigned long)sizeof(struct storage),len-8);
	} else {
		storagedb_save((struct storage *)RFIFOP(fd,8));
		mapif_save_storage_ack(fd,account_id);
	}
	return 0;
}

// ギルド倉庫データ要求受信
int mapif_parse_LoadGuildStorage(int fd)
{
	mapif_load_guild_storage(fd,RFIFOL(fd,2),RFIFOL(fd,6));
	return 0;
}

// ギルド倉庫データ受信＆保存
int mapif_parse_SaveGuildStorage(int fd)
{
	int guild_id=RFIFOL(fd,8);
	int len=RFIFOW(fd,2);

	if(sizeof(struct guild_storage)!=len-12) {
		printf("inter guild_storage: data size error %lu %d\n",(unsigned long)sizeof(struct guild_storage),len-12);
	} else {
		bool is_success = gstoragedb_save((struct guild_storage *)RFIFOP(fd,12), 0);
		mapif_save_guild_storage_ack(fd,RFIFOL(fd,4),guild_id,!is_success);
	}
	return 0;
}

// ギルド倉庫ロック要求受信
int mapif_parse_TrylockGuildStorage(int fd)
{
	char flag = 0;
	int guild_id = RFIFOL(fd,6);
	const struct guild_storage *gs = gstoragedb_load(guild_id);

	if(gs && gs->storage_status == 0) {
		struct guild_storage gs2;
		memcpy(&gs2, gs, sizeof(gs2));
		gs2.storage_status = 1;
		flag = (gs2.last_fd == fd)? 1: 2;	// 前回とは違うMAPサーバからのアクセスならリロード(flag=2)
		gs2.last_fd = fd;
		gstoragedb_save(&gs2, 1);
	}
	mapif_trylock_guild_storage_ack(fd,RFIFOL(fd,2),guild_id,RFIFOL(fd,10),flag);

	return 0;
}

// ギルド倉庫ロック解除受信
int mapif_parse_UnlockGuildStorage(int fd)
{
	char succeed = 0;
	int guild_id = RFIFOL(fd,2);
	const struct guild_storage *gs = gstoragedb_load(guild_id);

	if(gs && gs->storage_status == 1) {
		struct guild_storage gs2;
		memcpy(&gs2, gs, sizeof(gs2));
		gs2.storage_status = 0;
		gstoragedb_save(&gs2, 1);
		succeed = 1;
	}
	mapif_unlock_guild_storage_ack(fd,guild_id,succeed);

	return 0;
}

// ギルド倉庫デッドロック解除受信
int mapif_parse_DeadlockGuildStorage(int fd)
{
	printf("guild_storage_deadlock_timer: storage deadlocked!! (%d)\n", RFIFOL(fd,2));

	// 通常のロック解除と同じ
	mapif_parse_UnlockGuildStorage(fd);

	return 0;
}

// ギルド倉庫デッドロック検出タイマー
static int guild_storage_deadlock_timer_sub(void *key, void *data, va_list ap)
{
	struct guild_storage *gs = (struct guild_storage *)data;

	if(gs && gs->storage_status == 1 && gs->last_fd >= 0)
		mapif_checklock_guild_storage(gs->guild_id);

	return 0;
}

int guild_storage_deadlock_timer(int tid, unsigned int tick, int id, void *data)
{
	numdb_foreach(gstorage_db, guild_storage_deadlock_timer_sub);

	return 0;
}

//---------------------------------------------------------
// map server からの通信
// ・１パケットのみ解析すること
// ・パケット長データはinter.cにセットしておくこと
// ・パケット長チェックや、RFIFOSKIPは呼び出し元で行われるので行ってはならない
// ・エラーなら0(false)、そうでないなら1(true)をかえさなければならない
int inter_storage_parse_frommap(int fd)
{
	switch(RFIFOW(fd,0)){
	case 0x3010: mapif_parse_LoadStorage(fd); break;
	case 0x3011: mapif_parse_SaveStorage(fd); break;
	case 0x3018: mapif_parse_LoadGuildStorage(fd); break;
	case 0x3019: mapif_parse_SaveGuildStorage(fd); break;
	case 0x301a: mapif_parse_TrylockGuildStorage(fd); break;
	case 0x301b: mapif_parse_UnlockGuildStorage(fd); break;
	case 0x301c: mapif_parse_DeadlockGuildStorage(fd); break;
	default:
		return 0;
	}
	return 1;
}

int inter_storage_init(void)
{
	unsigned int tick = gettick();

	add_timer_func_list(guild_storage_deadlock_timer);
	add_timer_interval(tick+1000, guild_storage_deadlock_timer, 0, NULL, 3600 * 1000);

	return 0;
}
