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

#define _INT_MERC_C_

#include <stdio.h>
#include <stdlib.h>

#include "mmo.h"
#include "socket.h"

#include "int_merc.h"

int mapif_merc_info(int fd,int account_id,int char_id,const struct mmo_mercstatus *m,unsigned char flag)
{
	if(!m)
		return 0;

	WFIFOW(fd,0)=0x3870;
	WFIFOW(fd,2)=sizeof(struct mmo_mercstatus) + 13;
	WFIFOL(fd,4)=account_id;
	WFIFOL(fd,8)=char_id;
	WFIFOB(fd,12)=flag;
	memcpy(WFIFOP(fd,13),m,sizeof(struct mmo_mercstatus));
	WFIFOSET(fd,WFIFOW(fd,2));

	return 0;
}

int mapif_save_merc_ack(int fd,int account_id,int flag)
{
	WFIFOW(fd,0)=0x3871;
	WFIFOL(fd,2)=account_id;
	WFIFOB(fd,6)=flag;
	WFIFOSET(fd,7);

	return 0;
}

int mapif_delete_merc_ack(int fd,int flag)
{
	WFIFOW(fd,0)=0x3872;
	WFIFOB(fd,2)=flag;
	WFIFOSET(fd,3);

	return 0;
}

int mapif_create_merc(int fd,int account_id,int char_id,struct mmo_mercstatus *m)
{
	if(!m || account_id <= 0 || char_id <= 0)
		return 0;
	if(mercdb_new(m) == true) {
		mapif_merc_info(fd,account_id,char_id,m,1);
	}
	return 0;
}

int mapif_load_merc(int fd,int account_id,int char_id,int merc_id)
{
	const struct mmo_mercstatus *m = mercdb_load(merc_id);

	if(m!=NULL) {
		mapif_merc_info(fd,account_id,char_id,m,0);
	} else {
		printf("inter merc: data load error %d %d %d\n",account_id,char_id,merc_id);
	}
	return 0;
}

int mapif_save_merc(int fd,int account_id,struct mmo_mercstatus *data)
{
	if(!data || sizeof(struct mmo_mercstatus) != RFIFOW(fd,2) - 8) {
		printf("inter merc: data size error %lu %d\n",(unsigned long)sizeof(struct mmo_mercstatus),RFIFOW(fd,2)-8);
		return 0;
	}

	if(mercdb_load(data->merc_id)) {
		mercdb_save(data);
		mapif_save_merc_ack(fd,account_id,0);
	}

	return 0;
}

int mapif_delete_merc(int fd,int merc_id)
{
	mapif_delete_merc_ack(fd,mercdb_delete(merc_id));

	return 0;
}

//---------------------------------------------------------------------------------------
// 傭兵を新規作成
int mapif_parse_CreateMerc(int fd)
{
	int account_id = RFIFOL(fd,4);
	int char_id    = RFIFOL(fd,8);
	struct mmo_mercstatus m;

	memcpy(&m,RFIFOP(fd,12),sizeof(struct mmo_mercstatus));

	mapif_create_merc(fd,account_id,char_id,&m);
	return 0;
}

// 傭兵のデータ送信
int mapif_parse_LoadMerc(int fd)
{
	mapif_load_merc(fd,RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10));
	return 0;
}

// 傭兵のデータ受信＆保存
int mapif_parse_SaveMerc(int fd)
{
	mapif_save_merc(fd,RFIFOL(fd,4),(struct mmo_mercstatus *)RFIFOP(fd,8));
	return 0;
}

// 傭兵削除
int mapif_parse_DeleteMerc(int fd)
{
	mapif_delete_merc(fd,RFIFOL(fd,10));
	return 0;
}

// map server からの通信
// ・１パケットのみ解析すること
// ・パケット長データはinter.cにセットしておくこと
// ・パケット長チェックや、RFIFOSKIPは呼び出し元で行われるので行ってはならない
// ・エラーなら0(false)、そうでないなら1(true)をかえさなければならない
int inter_merc_parse_frommap(int fd)
{
	switch(RFIFOW(fd,0)){
	case 0x3070: mapif_parse_CreateMerc(fd); break;
	case 0x3071: mapif_parse_LoadMerc(fd);   break;
	case 0x3072: mapif_parse_SaveMerc(fd);   break;
	case 0x3073: mapif_parse_DeleteMerc(fd); break;
	default:
		return 0;
	}
	return 1;
}
