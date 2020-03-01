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

#define _INT_STATUS_C_

#include <stdio.h>

#include "mmo.h"
#include "socket.h"
#include "utils.h"

#include "int_status.h"

// ダミー関数群
#ifdef NO_SCDATA_SAVING

bool status_dummy_init(void) { return true; }
int status_dummy_sync(void) { return true; }
bool status_dummy_delete(int char_id) { return true; }
struct scdata *status_dummy_load(int char_id) { return NULL; }
bool status_dummy_save(struct scdata *sc2) { return true; }
void status_dummy_final(void) { return; }
int status_dummy_config_read_sub(const char *w1,const char *w2) { return 0; }

#endif

int mapif_load_scdata(int fd,int account_id,int char_id)
{
	struct scdata *sc = statusdb_load(char_id);

	if(sc) {
		if(sc->account_id <= 0) {	// アカウントIDがないのは困るので補完
			sc->account_id = account_id;
		}
		else if(sc->account_id != account_id) {
			printf("inter_status: data load error %d %d\n",account_id,char_id);
			return 0;
		}
	}

	WFIFOW(fd,0)=0x3878;
	WFIFOL(fd,4)=account_id;

	if(sc == NULL) {
		WFIFOW(fd,2)=8;
		WFIFOSET(fd,8);
	} else {
		int i,p;
		for(i=0,p=8; i<sc->count; i++,p+=22) {
			WFIFOW(fd,p)    = sc->data[i].type;
			WFIFOL(fd,p+2)  = sc->data[i].val1;
			WFIFOL(fd,p+6)  = sc->data[i].val2;
			WFIFOL(fd,p+10) = sc->data[i].val3;
			WFIFOL(fd,p+14) = sc->data[i].val4;
			WFIFOL(fd,p+18) = sc->data[i].tick;
		}
		WFIFOW(fd,2)=p;
		WFIFOSET(fd,p);
	}
	return 0;
}

static int mapif_save_scdata_ack(int fd,int account_id,int flag)
{
	/*
	// 今のところ使い道がないのでコメントアウト
	WFIFOW(fd,0)=0x3879;
	WFIFOL(fd,2)=account_id;
	WFIFOB(fd,6)=flag;
	WFIFOSET(fd,7);
	*/
	return 0;
}

//-------------------------------------------------------------------
// map serverからの通信

// ステータス異常データ要求受信
int mapif_parse_LoadStatusChange(int fd)
{
	mapif_load_scdata(fd,RFIFOL(fd,2),RFIFOL(fd,6));
	return 0;
}

// ステータス異常データ保存
int mapif_parse_SaveStatusChange(int fd)
{
	struct scdata sc;
	int i,p;
	short len = RFIFOW(fd,2);

	sc.account_id = RFIFOL(fd,4);
	sc.char_id    = RFIFOL(fd,8);

	for(i=0,p=12; p<len && i<MAX_STATUSCHANGE; i++,p+=22) {
		sc.data[i].type = RFIFOW(fd,p);
		sc.data[i].val1 = RFIFOL(fd,p+2);
		sc.data[i].val2 = RFIFOL(fd,p+6);
		sc.data[i].val3 = RFIFOL(fd,p+10);
		sc.data[i].val4 = RFIFOL(fd,p+14);
		sc.data[i].tick = RFIFOL(fd,p+18);
	}
	sc.count = i;

	statusdb_save(&sc);
	mapif_save_scdata_ack(fd,sc.account_id,0);

	return 0;
}

//---------------------------------------------------------
// map server からの通信
// ・１パケットのみ解析すること
// ・パケット長データはinter.cにセットしておくこと
// ・パケット長チェックや、RFIFOSKIPは呼び出し元で行われるので行ってはならない
// ・エラーなら0(false)、そうでないなら1(true)をかえさなければならない
int inter_status_parse_frommap(int fd)
{
#ifndef NO_SCDATA_SAVING
	switch(RFIFOW(fd,0)){
	case 0x3078: mapif_parse_LoadStatusChange(fd); break;
	case 0x3079: mapif_parse_SaveStatusChange(fd); break;
	default:
		return 0;
	}
#endif
	return 1;
}
