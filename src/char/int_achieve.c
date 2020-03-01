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

#define _INT_ACHIEVE_C_

#include <stdio.h>

#include "mmo.h"
#include "socket.h"
#include "utils.h"

#include "int_achieve.h"

// ----------------------------------------------------------
// 実績データ送信
// ----------------------------------------------------------
int mapif_load_achieve(int fd,int account_id,int char_id)
{
	const struct achieve *a = achievedb_load(char_id);
	int p = 8;

	WFIFOW(fd,0)=0x3868;
	WFIFOL(fd,4)=account_id;

	if(a) {
		int i;

		for(i=0; i<a->count; i++,p+=49) {
			WFIFOL(fd,p)    = a->data[i].nameid;
			WFIFOL(fd,p+4)  = a->data[i].count[0];
			WFIFOL(fd,p+8)  = a->data[i].count[1];
			WFIFOL(fd,p+12) = a->data[i].count[2];
			WFIFOL(fd,p+16) = a->data[i].count[3];
			WFIFOL(fd,p+20) = a->data[i].count[4];
			WFIFOL(fd,p+24) = a->data[i].count[5];
			WFIFOL(fd,p+28) = a->data[i].count[6];
			WFIFOL(fd,p+32) = a->data[i].count[7];
			WFIFOL(fd,p+36) = a->data[i].count[8];
			WFIFOL(fd,p+40) = a->data[i].count[9];
			WFIFOL(fd,p+44) = (unsigned int)a->data[i].comp_date;
			WFIFOB(fd,p+48) = a->data[i].reward;
		}
	}

	WFIFOW(fd,2)=p;
	WFIFOSET(fd,p);

	return 0;
}

// ----------------------------------------------------------
// 実績データ保存完了送信
// ----------------------------------------------------------
static int mapif_save_achieve_ack(int fd,int char_id,int flag)
{
	WFIFOW(fd,0)=0x3869;
	WFIFOL(fd,2)=char_id;
	WFIFOB(fd,6)=flag;
	WFIFOSET(fd,7);

	return 0;
}


// ----------------------------------------------------------
// 実績データ要求受信
// ----------------------------------------------------------
int mapif_parse_LoadAchieveList(int fd)
{
	mapif_load_achieve(fd,RFIFOL(fd,2),RFIFOL(fd,6));
	return 0;
}

// ----------------------------------------------------------
// 実績データ保存要求受信
// ----------------------------------------------------------
int mapif_parse_SaveAchieveList(int fd)
{
	struct achieve a;
	int i,p;
	short len = RFIFOW(fd,2);

	a.account_id = RFIFOL(fd,4);
	a.char_id    = RFIFOL(fd,8);

	for(i=0,p=12; p<len && i<MAX_ACHIEVELIST; i++,p+=49) {
		a.data[i].nameid    = RFIFOL(fd,p);
		a.data[i].count[0]  = RFIFOL(fd,p+4);
		a.data[i].count[1]  = RFIFOL(fd,p+8);
		a.data[i].count[2]  = RFIFOL(fd,p+12);
		a.data[i].count[3]  = RFIFOL(fd,p+16);
		a.data[i].count[4]  = RFIFOL(fd,p+20);
		a.data[i].count[5]  = RFIFOL(fd,p+24);
		a.data[i].count[6]  = RFIFOL(fd,p+28);
		a.data[i].count[7]  = RFIFOL(fd,p+32);
		a.data[i].count[8]  = RFIFOL(fd,p+36);
		a.data[i].count[9]  = RFIFOL(fd,p+40);
		a.data[i].comp_date = (unsigned int)RFIFOL(fd,p+44);
		a.data[i].reward    = RFIFOB(fd,p+48);
	}
	a.count = i;

	achievedb_save(&a);
	mapif_save_achieve_ack(fd,a.char_id,0);

	return 0;
}

// ----------------------------------------------------------
// マップサーバーからの通信
// ・１パケットのみ解析すること
// ・パケット長データはinter.cにセットしておくこと
// ・パケット長チェックや、RFIFOSKIPは呼び出し元で行われるので行ってはならない
// ・エラーなら0(false)、そうでないなら1(true)をかえさなければならない
// ----------------------------------------------------------
int inter_achieve_parse_frommap(int fd)
{
	switch(RFIFOW(fd,0)){
	case 0x3068: mapif_parse_LoadAchieveList(fd); break;
	case 0x3069: mapif_parse_SaveAchieveList(fd); break;
	default:
		return 0;
	}
	return 1;
}
