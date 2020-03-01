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

#define _INT_ELEM_C_

#include <stdio.h>
#include <stdlib.h>

#include "mmo.h"
#include "socket.h"

#include "int_elem.h"

int mapif_elem_info(int fd,int account_id,int char_id,const struct mmo_elemstatus *e,unsigned char flag)
{
	if(!e)
		return 0;

	WFIFOW(fd,0)=0x387c;
	WFIFOW(fd,2)=sizeof(struct mmo_elemstatus) + 13;
	WFIFOL(fd,4)=account_id;
	WFIFOL(fd,8)=char_id;
	WFIFOB(fd,12)=flag;
	memcpy(WFIFOP(fd,13),e,sizeof(struct mmo_elemstatus));
	WFIFOSET(fd,WFIFOW(fd,2));

	return 0;
}

int mapif_save_elem_ack(int fd,int account_id,int flag)
{
	WFIFOW(fd,0)=0x387d;
	WFIFOL(fd,2)=account_id;
	WFIFOB(fd,6)=flag;
	WFIFOSET(fd,7);

	return 0;
}

int mapif_delete_elem_ack(int fd,int flag)
{
	WFIFOW(fd,0)=0x387e;
	WFIFOB(fd,2)=flag;
	WFIFOSET(fd,3);

	return 0;
}

int mapif_create_elem(int fd,int account_id,int char_id,struct mmo_elemstatus *e)
{
	if(!e || account_id <= 0 || char_id <= 0)
		return 0;
	if(elemdb_new(e) == true) {
		mapif_elem_info(fd,account_id,char_id,e,1);
	}
	return 0;
}

int mapif_load_elem(int fd,int account_id,int char_id,int elem_id)
{
	const struct mmo_elemstatus *e = elemdb_load(elem_id);

	if(e!=NULL) {
		mapif_elem_info(fd,account_id,char_id,e,0);
	} else {
		printf("inter elem: data load error %d %d %d\n",account_id,char_id,elem_id);
	}
	return 0;
}

int mapif_save_elem(int fd,int account_id,struct mmo_elemstatus *data)
{
	if(!data || sizeof(struct mmo_elemstatus) != RFIFOW(fd,2) - 8) {
		printf("inter elem: data size error %lu %d\n",(unsigned long)sizeof(struct mmo_elemstatus),RFIFOW(fd,2)-8);
		return 0;
	}

	if(elemdb_load(data->elem_id)) {
		elemdb_save(data);
		mapif_save_elem_ack(fd,account_id,0);
	}

	return 0;
}

int mapif_delete_elem(int fd,int elem_id)
{
	mapif_delete_elem_ack(fd,elemdb_delete(elem_id));

	return 0;
}

//---------------------------------------------------------------------------------------
// 傭兵を新規作成
int mapif_parse_CreateElem(int fd)
{
	int account_id = RFIFOL(fd,4);
	int char_id    = RFIFOL(fd,8);
	struct mmo_elemstatus e;

	memcpy(&e,RFIFOP(fd,12),sizeof(struct mmo_elemstatus));

	mapif_create_elem(fd,account_id,char_id,&e);
	return 0;
}

// 精霊のデータ送信
int mapif_parse_LoadElem(int fd)
{
	mapif_load_elem(fd,RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10));
	return 0;
}

// 精霊のデータ受信＆保存
int mapif_parse_SaveElem(int fd)
{
	mapif_save_elem(fd,RFIFOL(fd,4),(struct mmo_elemstatus *)RFIFOP(fd,8));
	return 0;
}

// 精霊削除
int mapif_parse_DeleteElem(int fd)
{
	mapif_delete_elem(fd,RFIFOL(fd,10));
	return 0;
}

// map server からの通信
// ・１パケットのみ解析すること
// ・パケット長データはinter.cにセットしておくこと
// ・パケット長チェックや、RFIFOSKIPは呼び出し元で行われるので行ってはならない
// ・エラーなら0(false)、そうでないなら1(true)をかえさなければならない
int inter_elem_parse_frommap(int fd)
{
	switch(RFIFOW(fd,0)){
	case 0x307c: mapif_parse_CreateElem(fd); break;
	case 0x307d: mapif_parse_LoadElem(fd);   break;
	case 0x307e: mapif_parse_SaveElem(fd);   break;
	case 0x307f: mapif_parse_DeleteElem(fd); break;
	default:
		return 0;
	}
	return 1;
}
