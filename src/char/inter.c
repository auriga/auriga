/*
 * Copyright (C) 2002-2007  Auriga
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

#include <string.h>
#include <stdlib.h>

#include "socket.h"
#include "timer.h"
#include "db.h"
#include "malloc.h"
#include "utils.h"
#include "sqldbs.h"

#include "char.h"
#include "inter.h"
#include "int_party.h"
#include "int_guild.h"
#include "int_storage.h"
#include "int_pet.h"
#include "int_homun.h"
#include "int_mail.h"
#include "int_status.h"
#include "int_merc.h"
#include "int_quest.h"
#include "int_elem.h"

#define WISDATA_TTL    (60*1000)	// Wisデータの生存時間(60秒)
#define WISDELLIST_MAX 128		// Wisデータ削除リストの要素数

// 受信パケット長リスト
int inter_recv_packet_length[] = {
	-1,-1, 7, 0, -1, 6, 0, 0,  6, 0, 0, 0,  0, 0,  0, 0,	// 3000-
	 6,-1, 0, 0,  0, 0, 0, 0, 10,-1,14, 6,  6, 0,  0, 0,	// 3010-
	80, 6,58,16, 14,35, 6,-1, 14,14, 0, 0,  0, 0,  0, 0,	// 3020-
	-1, 6,-1, 0, 55,19, 6,-1, 14,-1,-1,-1, 19,22,186,-1,	// 3030-
	 5, 9, 0, 0,  0, 0, 0, 0,  0, 6,-1,10, 10,10, -1,10,	// 3040-
	 0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0,  0, 0,	// 3050-
	10,-1, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0,  0, 0,	// 3060-
	-1,14,-1,14,  0, 0, 0, 0, 10,-1, 0, 0, -1,14, -1,14,	// 3070-
	48,14,-1, 6,  0, 0, 0, 0, -1,14,-1,14,  0, 0,  0, 0,	// 3080-
	31,51,51,-1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0,  0, 0,	// 3090-
};

struct WisData {
	int id,fd,count,len,gmlevel;
	unsigned int tick;
	char src[24],dst[24],msg[512];
};
static struct dbt * wis_db = NULL;

/*==========================================
 * WISデータの生存チェック
 *------------------------------------------
 */
static int check_ttl_wisdata_sub(void *key,void *data,va_list ap)
{
	unsigned int tick;
	struct WisData *wd = (struct WisData *)data;

	tick = va_arg(ap, unsigned int);

	if(DIFF_TICK(tick, wd->tick) > WISDATA_TTL) {
		printf("inter: wis data id=%d time out : from %s to %s\n", wd->id, wd->src, wd->dst);
		numdb_erase(wis_db, wd->id);
		aFree(wd);
	}
	return 0;
}

static int check_ttl_wisdata(void)
{
	numdb_foreach(wis_db, check_ttl_wisdata_sub, gettick());

	return 0;
}

/*==========================================
 * 設定ファイルを読み込む
 *------------------------------------------
 */
int inter_config_read(const char *cfgName)
{
	char line[1024],w1[1024],w2[1024];
	FILE *fp;

	fp = fopen(cfgName,"r");
	if(fp == NULL) {
		printf("inter_config_read: open [%s] failed !\n", cfgName);
		return 1;
	}
	while(fgets(line,1020,fp)) {
		if(sscanf(line,"%1023[^:]: %1023[^\r\n]",w1,w2) != 2)
			continue;

		if(strcmpi(w1,"import") == 0) {
			inter_config_read(w2);
		}
		else {
			if(interlog_config_read(w1, w2))
				continue;
			if(accregdb_config_read_sub(w1,w2))
				continue;
			if(petdb_config_read_sub(w1,w2))
				continue;
			if(storagedb_config_read_sub(w1,w2))
				continue;
			if(party_config_read(w1,w2))
				continue;
			if(guild_config_read(w1,w2))
				continue;
			if(maildb_config_read_sub(w1,w2))
				continue;
			if(homundb_config_read_sub(w1,w2))
				continue;
			if(statusdb_config_read_sub(w1,w2))
				continue;
			if(mercdb_config_read_sub(w1,w2))
				continue;
			if(questdb_config_read_sub(w1,w2))
				continue;
			if(elemdb_config_read_sub(w1,w2))
				continue;
		}
	}
	fclose(fp);

	return 0;
}

//--------------------------------------------------------

/*==========================================
 * 同期
 *------------------------------------------
 */
int inter_sync(void)
{
	statusdb_sync();
	questdb_sync();
	petdb_sync();
	homundb_sync();
	mercdb_sync();
	elemdb_sync();
	partydb_sync();
	guilddb_sync();
	accregdb_sync();
	storagedb_sync();
	gstoragedb_sync();
	maildb_sync();

	return 0;
}

/*==========================================
 * マップサーバー接続
 *------------------------------------------
 */
int inter_mapif_init(int fd)
{
	inter_guild_mapif_init(fd);
	return 0;
}

//--------------------------------------------------------

/*==========================================
 * GMメッセージ送信
 *------------------------------------------
 */
int mapif_GMmessage(const char *mes,size_t len,unsigned int color,int type,int size,int align,int pos_y)
{
	unsigned char *buf = (unsigned char*)aMalloc(len);

	WBUFW(buf,0) = 0x3800;
	WBUFW(buf,2) = (unsigned short)len;
	WBUFL(buf,4) = color;
	WBUFW(buf,8) = type;
	WBUFW(buf,10) = size;
	WBUFW(buf,12) = align;
	WBUFW(buf,14) = pos_y;
	memcpy(WBUFP(buf,16), mes, len-16);
	mapif_sendall(buf,len);

	aFree(buf);
	return 0;
}

/*==========================================
 * Wis送信
 *------------------------------------------
 */
int mapif_wis_message(struct WisData *wd)
{
	unsigned char buf[1024];

	WBUFW(buf, 0)=0x3801;
	WBUFW(buf, 2)=60 + wd->len;
	WBUFL(buf, 4)=wd->id;
	WBUFL(buf, 8)=wd->gmlevel;
	memcpy(WBUFP(buf,12),wd->src,24);
	memcpy(WBUFP(buf,36),wd->dst,24);
	memcpy(WBUFP(buf,60),wd->msg,wd->len);
	wd->count = mapif_sendall(buf,WBUFW(buf,2));

	return 0;
}

/*==========================================
 * Wis送信結果
 *------------------------------------------
 */
int mapif_wis_end(struct WisData *wd,int flag)
{
	unsigned char buf[52];

	WBUFW(buf, 0)=0x3802;
	memcpy(WBUFP(buf, 2),wd->src,24);
	memcpy(WBUFP(buf,26),wd->dst,24);
	WBUFB(buf,50)=flag;
	mapif_send(wd->fd,buf,51);

	return 0;
}

/*==========================================
 * アカウント変数送信
 *------------------------------------------
 */
int mapif_account_reg(int fd,const unsigned char *src)
{
	int len = WBUFW(src,2);
	unsigned char *buf = (unsigned char *)aMalloc(len);

	memcpy(WBUFP(buf,0),src,len);
	WBUFW(buf, 0)=0x3804;
	mapif_sendallwos(fd,buf,WBUFW(buf,2));
	aFree(buf);
	return 0;
}

/*==========================================
 * アカウント変数要求返信
 *------------------------------------------
 */
int mapif_account_reg_reply(int fd,int account_id)
{
	const struct accreg *reg = accregdb_load(account_id);

	WFIFOW(fd,0)=0x3804;
	WFIFOL(fd,4)=account_id;
	if(reg == NULL) {
		WFIFOW(fd,2)=8;
	} else {
		int j,p;
		for(j=0,p=8; j<reg->reg_num; j++,p+=36) {
			memcpy(WFIFOP(fd,p),reg->reg[j].str,32);
			WFIFOL(fd,p+32)=reg->reg[j].value;
		}
		WFIFOW(fd,2)=p;
	}
	WFIFOSET(fd,WFIFOW(fd,2));
	return 0;
}

//--------------------------------------------------------

/*==========================================
 * GMメッセージ送信
 *------------------------------------------
 */
int mapif_parse_GMmessage(int fd)
{
	mapif_GMmessage(RFIFOP(fd,16), RFIFOW(fd,2), RFIFOL(fd,4), RFIFOW(fd,8), RFIFOW(fd,10), RFIFOW(fd,12), RFIFOW(fd,14));
	return 0;
}

/*==========================================
 * Wis送信要求
 *------------------------------------------
 */
int mapif_parse_WisRequest(int fd)
{
	struct WisData* wd;
	static int wisid = 0;
	unsigned int tick = gettick();

	if(RFIFOW(fd,2) - 56 >= sizeof(wd->msg)) {
		printf("inter: Wis message size too long.\n");
		return 0;
	}

	wd = (struct WisData *)aCalloc(1,sizeof(struct WisData));
	check_ttl_wisdata();

	wd->id  = ++wisid;
	wd->fd  = fd;
	wd->len = RFIFOW(fd,2) - 56;
	wd->gmlevel = RFIFOL(fd,4);
	memcpy(wd->src, RFIFOP(fd, 8), 24);
	memcpy(wd->dst, RFIFOP(fd,32), 24);
	memcpy(wd->msg, RFIFOP(fd,56), wd->len);
	wd->tick = tick;
	numdb_insert(wis_db, wd->id, wd);
	mapif_wis_message(wd);

	return 0;
}

/*==========================================
 * Wis送信結果
 *------------------------------------------
 */
int mapif_parse_WisReply(int fd)
{
	int id   = RFIFOL(fd,2);
	int flag = RFIFOB(fd,6);
	struct WisData *wd = (struct WisData *)numdb_search(wis_db, id);

	if(wd == NULL)
		return 0;	// タイムアウトしたかIDが存在しない

	if((--wd->count) == 0 || flag != 1) {
		mapif_wis_end(wd,flag);
		numdb_erase(wis_db, id);
		aFree(wd);
	}
	return 0;
}

/*==========================================
 * アカウント変数保存要求
 *------------------------------------------
 */
int mapif_parse_AccReg(int fd)
{
	int j,p;
	struct accreg reg;

	memset(&reg,0,sizeof(reg));

	reg.account_id = RFIFOL(fd,4);
	for(j=0,p=8; j<ACCOUNT_REG_NUM && p<RFIFOW(fd,2); j++,p+=36) {
		strncpy(reg.reg[j].str,RFIFOP(fd,p),32);
		reg.reg[j].str[31] = '\0';	// force \0 terminal
		reg.reg[j].value   = RFIFOL(fd,p+32);
	}
	reg.reg_num = j;

	accregdb_save(&reg);
	mapif_account_reg(fd,RFIFOP(fd,0));	// 他のMAPサーバーに送信
	return 0;
}

/*==========================================
 * アカウント変数送信要求
 *------------------------------------------
 */
int mapif_parse_AccRegRequest(int fd)
{
	//printf("mapif: accreg request\n");
	return mapif_account_reg_reply(fd,RFIFOL(fd,2));
}

/*==========================================
 * キャラクターの位置要求
 *------------------------------------------
 */
int mapif_parse_CharPosReq(int fd)
{
	unsigned char buf[32];

	WBUFW(buf,0)=0x3890;
	memcpy(WBUFP(buf,2),RFIFOP(fd,2),29);
	mapif_sendall(buf,31);

	return 0;
}

/*==========================================
 * キャラクターの位置を要求者に通知
 *------------------------------------------
 */
int mapif_parse_CharPos(int fd)
{
	unsigned char buf[60];

	WBUFW(buf,0)=0x3891;
	memcpy(WBUFP(buf,2),RFIFOP(fd,2),49);
	mapif_sendall(buf,51);

	return 0;
}

/*==========================================
 * キャラクターの移動要求
 *------------------------------------------
 */
int mapif_parse_CharMoveReq(int fd)
{
	unsigned char buf[60];

	WBUFW(buf,0)=0x3892;
	memcpy(WBUFP(buf,2),RFIFOP(fd,2),49);
	mapif_sendall(buf,51);

	return 0;
}

/*==========================================
 * 対象IDにメッセージを送信
 *------------------------------------------
 */
int mapif_parse_DisplayMessage(int fd)
{
	int len = RFIFOW(fd,2);
	unsigned char *buf = (unsigned char *)aMalloc(len);

	WBUFW(buf,0)=0x3893;
	memcpy(WBUFP(buf,2),RFIFOP(fd,2),len-2);
	mapif_sendall(buf,len);
	aFree(buf);
	return 0;
}

//--------------------------------------------------------

/*==========================================
 * RFIFOのパケット長確認
 * 必要パケット長があればパケット長、まだ足りなければ0
 *------------------------------------------
 */
static int inter_check_length(int fd,int length)
{
	if(length == -1) {	// 可変パケット長
		if(RFIFOREST(fd) < 4)	// パケット長が未着
			return 0;
		length = RFIFOW(fd,2);
	}

	if(RFIFOREST(fd) < length)	// パケットが未着
		return 0;

	return length;
}

/*==========================================
 * map server からの通信（１パケットのみ解析すること）
 * エラーなら0(false)、処理できたなら1、
 * パケット長が足りなければ2を返さなければならない
 *------------------------------------------
 */
int inter_parse_frommap(int fd)
{
	int cmd = RFIFOW(fd,0);
	int len = 0;

	// inter鯖管轄かを調べる
	if( cmd < 0x3000 || cmd >= 0x3000 + sizeof(inter_recv_packet_length) / sizeof(inter_recv_packet_length[0]) )
		return 0;

	// パケット長を調べる
	if( (len = inter_check_length(fd,inter_recv_packet_length[cmd-0x3000])) == 0 )
		return 2;

	switch(cmd) {
	case 0x3000: mapif_parse_GMmessage(fd);        break;
	case 0x3001: mapif_parse_WisRequest(fd);       break;
	case 0x3002: mapif_parse_WisReply(fd);         break;
	case 0x3004: mapif_parse_AccReg(fd);           break;
	case 0x3005: mapif_parse_AccRegRequest(fd);    break;
	case 0x3008: mapif_parse_CharConnectLimit(fd); break;
	case 0x3090: mapif_parse_CharPosReq(fd);       break;
	case 0x3091: mapif_parse_CharPos(fd);          break;
	case 0x3092: mapif_parse_CharMoveReq(fd);      break;
	case 0x3093: mapif_parse_DisplayMessage(fd);   break;
	default:
		if( inter_party_parse_frommap(fd) )
			break;
		if( inter_guild_parse_frommap(fd) )
			break;
		if( inter_storage_parse_frommap(fd) )
			break;
		if( inter_pet_parse_frommap(fd) )
			break;
		if( inter_hom_parse_frommap(fd) )
			break;
		if( inter_merc_parse_frommap(fd) )
			break;
		if( inter_elem_parse_frommap(fd) )
			break;
		if( inter_mail_parse_frommap(fd) )
			break;
		if( inter_status_parse_frommap(fd) )
			break;
		if( inter_quest_parse_frommap(fd) )
			break;
		return 0;
	}
	RFIFOSKIP(fd, len);
	return 1;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
static int wis_db_final(void *key,void *data,va_list ap)
{
	struct WisData *wd = (struct WisData *)data;

	aFree(wd);

	return 0;
}

void do_final_inter(void)
{
	if(wis_db) {
		numdb_final(wis_db, wis_db_final);
		wis_db = NULL;
	}

	accregdb_final();
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
int inter_init(const char *file)
{
	inter_config_read(file);

	wis_db = numdb_init();

	statusdb_init();
	questdb_init();
	petdb_init();
	homundb_init();
	mercdb_init();
	elemdb_init();
	partydb_init();
	guilddb_init();
	accregdb_init();
	storagedb_init();
	maildb_init();

	return 0;
}
