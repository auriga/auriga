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

#define _INT_HOM_C_

#include <stdio.h>
#include <stdlib.h>

#include "mmo.h"
#include "socket.h"

#include "int_homun.h"

int mapif_hom_info(int fd,int account_id,int char_id,const struct mmo_homunstatus *h,unsigned char flag)
{
	if(!h)
		return 0;

	WFIFOW(fd,0)=0x3888;
	WFIFOW(fd,2)=sizeof(struct mmo_homunstatus) + 13;
	WFIFOL(fd,4)=account_id;
	WFIFOL(fd,8)=char_id;
	WFIFOB(fd,12)=flag;
	memcpy(WFIFOP(fd,13),h,sizeof(struct mmo_homunstatus));
	WFIFOSET(fd,WFIFOW(fd,2));

	return 0;
}

int mapif_save_hom_ack(int fd,int account_id,int flag)
{
	WFIFOW(fd,0)=0x3889;
	WFIFOL(fd,2)=account_id;
	WFIFOB(fd,6)=flag;
	WFIFOSET(fd,7);

	return 0;
}

int mapif_delete_hom_ack(int fd, bool flag)
{
	WFIFOW(fd,0)=0x388a;
	WFIFOB(fd,2)=flag;
	WFIFOSET(fd,3);

	return 0;
}

int mapif_create_hom(int fd,int account_id,int char_id,struct mmo_homunstatus *h)
{
	if(!h || account_id <= 0 || char_id <= 0)
		return 0;
	if(homundb_new(h) == true)
		mapif_hom_info(fd,account_id,char_id,h,1);

	return 0;
}

int mapif_load_hom(int fd,int account_id,int char_id,int homun_id)
{
	const struct mmo_homunstatus *h = homundb_load(homun_id);

	if(h!=NULL) {
		mapif_hom_info(fd,account_id,char_id,h,0);
	} else {
		printf("inter hom: data load error %d %d %d\n",account_id,char_id,homun_id);
	}
	return 0;
}

int mapif_save_hom(int fd,int account_id,struct mmo_homunstatus *data)
{
	if(!data || sizeof(struct mmo_homunstatus) != RFIFOW(fd,2) - 8) {
		printf("inter hom: data size error %lu %d\n",(unsigned long)sizeof(struct mmo_homunstatus),RFIFOW(fd,2)-8);
		return 0;
	}

	if(homundb_load(data->homun_id)) {
		if(data->hungry < 0)
			data->hungry = 0;
		else if(data->hungry > 100)
			data->hungry = 100;
		if(data->intimate < 0)
			data->intimate = 0;
		else if(data->intimate > 100000)
			data->intimate = 100000;
		homundb_save(data);
		mapif_save_hom_ack(fd,account_id,0);
	}

	return 0;
}

int mapif_delete_hom(int fd,int homun_id)
{
	mapif_delete_hom_ack(fd,homundb_delete(homun_id));

	return 0;
}

//---------------------------------------------------------------------------------------
// ホムを新規作成
int mapif_parse_CreateHom(int fd)
{
	int account_id = RFIFOL(fd,4);
	int char_id    = RFIFOL(fd,8);
	struct mmo_homunstatus h;

	memcpy(&h,RFIFOP(fd,12),sizeof(struct mmo_homunstatus));

	mapif_create_hom(fd,account_id,char_id,&h);
	return 0;
}

// ホムのデータ送信
int mapif_parse_LoadHom(int fd)
{
	mapif_load_hom(fd,RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10));
	return 0;
}

// ホムのデータ受信＆保存
int mapif_parse_SaveHom(int fd)
{
	mapif_save_hom(fd,RFIFOL(fd,4),(struct mmo_homunstatus *)RFIFOP(fd,8));
	return 0;
}

// ホム削除
int mapif_parse_DeleteHom(int fd)
{
	mapif_delete_hom(fd,RFIFOL(fd,10));
	return 0;
}

// map server からの通信
// ・１パケットのみ解析すること
// ・パケット長データはinter.cにセットしておくこと
// ・パケット長チェックや、RFIFOSKIPは呼び出し元で行われるので行ってはならない
// ・エラーなら0(false)、そうでないなら1(true)をかえさなければならない
int inter_hom_parse_frommap(int fd)
{
	switch(RFIFOW(fd,0)){
	case 0x3088: mapif_parse_CreateHom(fd); break;
	case 0x3089: mapif_parse_LoadHom(fd); break;
	case 0x308a: mapif_parse_SaveHom(fd); break;
	case 0x308b: mapif_parse_DeleteHom(fd); break;
	default:
		return 0;
	}
	return 1;
}
