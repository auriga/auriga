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

// $Id: chrif.c,v 1.6 2003/06/29 05:52:56 lemit Exp $

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "socket.h"
#include "timer.h"
#include "malloc.h"
#include "nullpo.h"
#include "md5calc.h"

#include "map.h"
#include "battle.h"
#include "chrif.h"
#include "clif.h"
#include "intif.h"
#include "npc.h"
#include "pc.h"
#include "msg.h"
#include "friend.h"
#include "ranking.h"
#include "status.h"
#include "storage.h"

#define DUMP_UNKNOWN_PACKET 1

static const int packet_len_table[]={
	60, 3,-1, 3,23,-1, 7, 6,		// 2af8-2aff
	 6,-1,19, 7,-1,41,40, 7,		// 2b00-2b07
	 6,40,-1,10, 9, 7, 0, 0,		// 2b08-2b0f
	-1,-1, 6, 3, 3, 3,-1, 6,		// 2b10-2b17
	10, 6, 6, 0, 0, 0, 0, 0,		// 2b18-2b1f
	 6, 0, 0, 0,18,18,-1,-1,		// 2b20-2b27
	30,30, 2,-1,60,-1, 2,-1,		// 2b28-2b2f
	-1,	3				// 2b31
};

int char_fd = -1;
static char char_host[256] = "";
static unsigned long char_ip;
static unsigned short char_port = 6121;
static char userid[24] = "", passwd[24] = "";
static int chrif_state;

/*==========================================
 * ユーザー ID セット
 *------------------------------------------
 */
void chrif_setuserid(const char *id)
{
	memcpy(userid,id,24);
	userid[23] = '\0';	// force \0 terminal
}

/*==========================================
 * パスワードセット
 *------------------------------------------
 */
void chrif_setpasswd(const char *pwd)
{
	memcpy(passwd,pwd,24);
	passwd[23] = '\0';	// force \0 terminal
}

/*==========================================
 * ホストセット
 *------------------------------------------
 */
void chrif_sethost(const char *host)
{
	size_t len = strlen(host) + 1;

	if(len > sizeof(char_host))
		len = sizeof(char_host);

	memcpy(char_host, host, len);
	char_host[len-1] = '\0';	// force \0 terminal

	return;
}

/*==========================================
 * IP アドレスセット
 *------------------------------------------
 */
void chrif_setip(void)
{
	char_ip = host2ip(char_host, "Character server IP address");
}

/*==========================================
 * ポート番号セット
 *------------------------------------------
 */
void chrif_setport(unsigned short port)
{
	char_port = port;
}

/*==========================================
 * 接続しているかどうか
 *------------------------------------------
 */
int chrif_isconnect(void)
{
	return (chrif_state == 2);
}

/*==========================================
 * キャラ永続変数保存
 *------------------------------------------
 */
static int chrif_save_globalreg(struct map_session_data *sd)
{
	int i,p;

	nullpo_retr(-1, sd);

	if (char_fd < 0)
		return -1;

	WFIFOW(char_fd,0)=0x2b2d;
	WFIFOL(char_fd,4)=sd->bl.id;
	WFIFOL(char_fd,8)=sd->char_id;
	for(i=0,p=12; i<sd->save_reg.global_num; i++) {
		struct global_reg *reg = &sd->save_reg.global[i];
		if(reg->str[0] && reg->value != 0) {
			memcpy(WFIFOP(char_fd,p), reg->str, 32);
			WFIFOL(char_fd,p+32)=reg->value;
			p+=36;
		}
	}
	WFIFOW(char_fd,2)=p;
	WFIFOSET(char_fd,p);

	return 0;
}

/*==========================================
 * キャラクターデータ保存
 *------------------------------------------
 */
int chrif_save(struct map_session_data *sd, int final)
{
	nullpo_retr(-1, sd);

	if (char_fd < 0)
		return -1;

	// 切断待ちの時は処理しない
	if(sd->state.waitingdisconnect)
		return 0;

	if(!final)
		pc_makesavestatus(sd);

	if(sd->state.reg_dirty) {	// キャラ永続変数は変更があったときのみセーブする
		sd->state.reg_dirty = 0;
		chrif_save_globalreg(sd);
	}

	WFIFOW(char_fd,0)=0x2b01;
	WFIFOW(char_fd,2)=sizeof(sd->status)+13;
	WFIFOL(char_fd,4)=sd->bl.id;
	WFIFOL(char_fd,8)=sd->char_id;
	WFIFOB(char_fd,12) = final;
	memcpy(WFIFOP(char_fd,13),&sd->status,sizeof(sd->status));
	WFIFOSET(char_fd,WFIFOW(char_fd,2));

	return 0;
}

/*==========================================
 * 接続
 *------------------------------------------
 */
static int chrif_connect(int fd)
{
	// 暗号化ログインのチャレンジ要求
	WFIFOW(fd,0)=0x2b2a;
	WFIFOSET(fd,2);

	/* プレーンなログインは現在廃止 */
	//WFIFOW(fd,0)=0x2af8;
	//memcpy(WFIFOP(fd,2),userid,24);
	//memcpy(WFIFOP(fd,26),passwd,24);
	//WFIFOL(fd,50)=0;
	//WFIFOL(fd,54)=clif_getip();
	//WFIFOW(fd,58)=clif_getport();
	//memcpy(WFIFOP(fd,60), map_server_tag, MAPSERVER_TAGNAME);
	//WFIFOSET(fd,60 + MAPSERVER_TAGNAME);

	return 0;
}

/*==========================================
 * 暗号化ログイン
 *------------------------------------------
 */
static int chrif_cram_connect(int fd)
{
	WFIFOW(fd,0)=0x2b2c;
	memcpy(WFIFOP(fd,2),userid,24);
	HMAC_MD5_Binary( passwd, (int)strlen(passwd), RFIFOP(fd,4), RFIFOW(fd,2)-4, WFIFOP(fd,26) );
	WFIFOL(fd,42)=0;
	WFIFOL(fd,46)=4;	// HMAC-MD5
	WFIFOL(fd,50)=0;
	WFIFOL(fd,54)=clif_getip();
	WFIFOW(fd,58)=clif_getport();
	memcpy(WFIFOP(fd,60), map_server_tag, MAPSERVER_TAGNAME);
	WFIFOSET(fd,60 + MAPSERVER_TAGNAME);

	return 0;
}

/*==========================================
 * マップ送信
 *------------------------------------------
 */
static int chrif_sendmap(int fd)
{
	int i;

	WFIFOW(fd,0)=0x2afa;
	for(i=0;i<map_num;i++)
		memcpy(WFIFOP(fd,4+i*16),map[i].name,16);
	WFIFOW(fd,2)=4+i*16;
	WFIFOSET(fd,WFIFOW(fd,2));

	return 0;
}

/*==========================================
 * マップ受信
 *------------------------------------------
 */
static int chrif_recvmap(int fd)
{
	int i,j;
	unsigned long ip;
	unsigned short port;

	if(chrif_state < 2)	// まだ準備中
		return -1;

	ip   = RFIFOL(fd,4);
	port = RFIFOW(fd,8);
	for(i=12,j=0; i<RFIFOW(fd,2); i+=16,j++) {
		map_setipport(RFIFOP(fd,i),ip,port);
	}
	if(battle_config.etc_log) {
		unsigned char *p = (unsigned char *)&ip;
		printf("recv map on %d.%d.%d.%d:%d (%d maps)\n",p[0],p[1],p[2],p[3],port,j);
	}

	return 0;
}

/*==========================================
 * 削除マップ受信
 *------------------------------------------
 */
static int chrif_recverasemap(int fd)
{
	int i,j,ret = 0;
	unsigned long ip;
	unsigned short port;

	if(chrif_state < 2)	// まだ準備中
		return -1;

	ip   = RFIFOL(fd,4);
	port = RFIFOW(fd,8);
	for(i=12,j=0; i<RFIFOW(fd,2); i+=16,j++) {
		ret |= map_eraseipport(RFIFOP(fd,i),ip,port);
	}
	if(battle_config.etc_log) {
		unsigned char *p = (unsigned char *)&ip;
		printf("recv erase map on %d.%d.%d.%d:%d (%d maps)\n",p[0],p[1],p[2],p[3],port,j);
	}
	if(ret) {
		chrif_sendmap(fd);
	}
	return 0;
}

/*==========================================
 * マップ鯖間移動のためのデータ準備要求
 *------------------------------------------
 */
int chrif_changemapserver(struct map_session_data *sd,const char *name,int x,int y,unsigned long ip,unsigned short port)
{
	nullpo_retr(-1, sd);

	if (char_fd < 0)
		return -1;

	WFIFOW(char_fd, 0)=0x2b05;
	WFIFOL(char_fd, 2)=sd->bl.id;
	WFIFOL(char_fd, 6)=sd->login_id1;
	WFIFOL(char_fd,10)=sd->status.char_id;
	memcpy(WFIFOP(char_fd,14),name,16);
	WFIFOW(char_fd,30)=x;
	WFIFOW(char_fd,32)=y;
	WFIFOL(char_fd,34)=ip;
	WFIFOW(char_fd,38)=port;
	WFIFOB(char_fd,40)=sd->sex;
	WFIFOSET(char_fd,41);

	return 0;
}

/*==========================================
 * マップ鯖間移動ack
 *------------------------------------------
 */
static int chrif_changemapserverack(int fd)
{
	struct map_session_data *sd = map_id2sd(RFIFOL(fd,2));

	if(sd==NULL || sd->status.char_id!=RFIFOL(fd,10) )
		return -1;
	if(RFIFOL(fd,6)==1){
		if(battle_config.error_log)
			printf("map server change failed.\n");
		pc_authfail(sd->fd);
		return 0;
	}
	clif_changemapserver(sd,RFIFOP(fd,14),RFIFOW(fd,30),RFIFOW(fd,32),RFIFOL(fd,34),RFIFOW(fd,38));

	return 0;
}

/*==========================================
 * キャラクターデータ保存ack
 *------------------------------------------
 */
static int chrif_saveack(int fd)
{
	struct map_session_data *sd = map_id2sd(RFIFOL(fd,2));
	int type = RFIFOB(fd,6);

	if(sd) {
		if(type == 1) {		// 切断
			;
		} else if(type == 2) {	// キャラクターセレクト
			chrif_charselectreq(sd);
		} else if(type == 3) {	// 別マップサーバーへ移動
			unsigned long ip;
			unsigned short port;

			if(map_mapname2ipport(sd->status.last_point.map,&ip,&port) == 0) {
				chrif_changemapserver(sd,sd->status.last_point.map,sd->status.last_point.x,sd->status.last_point.y,ip,port);
			}
		}
	}

	return 0;
}

/*==========================================
 * 接続完了
 *------------------------------------------
 */
static int chrif_connectack(int fd)
{
	if(RFIFOB(fd,2)){
		printf("chrif : connect char server failed %d\n",RFIFOB(fd,2));
		exit(1);
	}
	chrif_state = 1;
	session[fd]->auth = -1; // 認証終了を socket.c に伝える

	chrif_sendmap(fd);
	chrif_ranking_request(fd);
	chrif_mapactive(1);

	printf("chrif: OnCharIfInit event done. (%d events)\n", npc_event_doall("OnCharIfInit") );
	printf("chrif: OnInterIfInit event done. (%d events)\n", npc_event_doall("OnInterIfInit") );

	// <Agit> Run Event [AgitInit]
//	printf("NPC_Event:[OnAgitInit] do (%d) events (Agit Initialize).\n", npc_event_doall("OnAgitInit"));

	return 0;
}

/*==========================================
 * マップ送信終了
 *------------------------------------------
 */
static int chrif_sendmapack(int fd)
{
	if(RFIFOB(fd,2)){
		printf("chrif : send map list to char server failed %d\n",RFIFOB(fd,2));
		exit(1);
	}
	chrif_state = 2;

	return 0;
}

/*==========================================
 * クライアントの認証要求
 *------------------------------------------
 */
int chrif_authreq(struct map_session_data *sd)
{
	nullpo_retr(-1, sd);

	if (char_fd < 0)
		return -1;

	WFIFOW(char_fd, 0) = 0x2afc;
	WFIFOL(char_fd, 2) = sd->bl.id;
	WFIFOL(char_fd, 6) = sd->char_id;
	WFIFOL(char_fd,10) = sd->login_id1;
	WFIFOL(char_fd,14) = sd->login_id2;
	WFIFOL(char_fd,18) = session[sd->fd]->client_addr.sin_addr.s_addr;
	WFIFOB(char_fd,22) = sd->sex;
	WFIFOSET(char_fd,23);

	return 0;
}

/*==========================================
 * クライアントの認証完了
 *------------------------------------------
 */
static int chrif_authok(int fd)
{
	struct map_session_data *sd=map_id2sd(RFIFOL(fd,4));
	struct mmo_charstatus *st;
	struct registry *reg;

	if(sd)
		sd->login_id2=RFIFOL(fd,8);

	st  = (struct mmo_charstatus *)RFIFOP(fd,12);
	reg = (struct registry *)RFIFOP(fd,12+sizeof(struct mmo_charstatus));

	return pc_authok(RFIFOL(fd,4), st, reg);
}

/*==========================================
 * クライアントのキャラセレのための準備要求
 *------------------------------------------
 */
int chrif_charselectreq(struct map_session_data *sd)
{
	int i;

	nullpo_retr(-1, sd);

	if (char_fd < 0)
		return -1;

	for(i=0;i<fd_max;i++){
		if(session[i] && sd == (struct map_session_data *)session[i]->session_data) {
			WFIFOW(char_fd, 0) = 0x2b02;
			WFIFOL(char_fd, 2) = sd->bl.id;
			WFIFOL(char_fd, 6) = sd->login_id1;
			WFIFOL(char_fd,10) = sd->login_id2;
			WFIFOL(char_fd,14) = session[i]->client_addr.sin_addr.s_addr;
			WFIFOB(char_fd,18) = sd->sex;
			WFIFOSET(char_fd,19);
			break;
		}
	}

	return 0;
}

/*==========================================
 * キャラ名問い合わせ
 *------------------------------------------
 */
void chrif_searchcharid(int char_id)
{
	if (char_fd < 0)
		return;

	WFIFOW(char_fd,0)=0x2b08;
	WFIFOL(char_fd,2)=char_id;
	WFIFOSET(char_fd,6);

	return;
}

/*==========================================
 * GMに変化要求
 *------------------------------------------
 */
int chrif_changegm(int id,const char *pass,size_t len)
{
	if (char_fd < 0)
		return -1;

	WFIFOW(char_fd,0)=0x2b0a;
	WFIFOW(char_fd,2)=(unsigned short)(len+8);
	WFIFOL(char_fd,4)=id;
	memcpy(WFIFOP(char_fd,8),pass,len);
	WFIFOSET(char_fd,len+8);

	return 0;
}

/*==========================================
 * 性別変化要求
 *------------------------------------------
 */
int chrif_changesex(int id,int sex)
{
	if (char_fd < 0)
		return -1;

	WFIFOW(char_fd,0)=0x2b0c;
	WFIFOW(char_fd,2)=9;
	WFIFOL(char_fd,4)=id;
	WFIFOB(char_fd,8)=sex;
	WFIFOSET(char_fd,9);

	printf("chrif : sended 0x2b0c\n");

	return 0;
}

/*==========================================
 * GMに変化終了
 *------------------------------------------
 */
static int chrif_changedgm(int fd)
{
	int oldacc,newacc;
	struct map_session_data *sd;

	oldacc=RFIFOL(fd,2);
	newacc=RFIFOL(fd,6);

	if((sd = map_id2sd(oldacc)) == NULL)
		return 0;

	if(battle_config.etc_log)
		printf("chrif_changedgm %d -> %d\n",oldacc,newacc);

	if(newacc>0){	// GM変更による強制切断
		clif_displaymessage(sd->fd, msg_txt(172)); // GM変更成功。再接続して下さい。
		clif_setwaitclose(sd->fd);
	}else{
		clif_displaymessage(sd->fd, msg_txt(173)); // GM変更失敗
	}
	return 0;
}

/*==========================================
 * 性別変化終了
 *------------------------------------------
 */
static int chrif_changedsex(int fd)
{
	int acc = RFIFOL(fd,2);

	if(battle_config.etc_log)
		printf("chrif_changedsex %d \n",acc);

	if(acc > 0) {
		struct map_session_data *sd = map_id2sd(acc);
		if(sd)	// 変更による強制切断
			clif_setwaitclose(sd->fd);
	}else{
		printf("chrif_changedsex failed\n");
	}
	return 0;
}

/*==========================================
 * アカウント変数保存要求
 *------------------------------------------
 */
int chrif_saveaccountreg2(struct map_session_data *sd)
{
	int p,j;

	nullpo_retr(-1, sd);

	if (char_fd < 0)
		return -1;

	for(p=8,j=0;j<sd->save_reg.account2_num;j++){
		struct global_reg *reg=&sd->save_reg.account2[j];
		if(reg->str[0] && reg->value!=0){
			memcpy(WFIFOP(char_fd,p),reg->str,32);
			WFIFOL(char_fd,p+32)=reg->value;
			p+=36;
		}
	}
	WFIFOW(char_fd,0)=0x2b10;
	WFIFOW(char_fd,2)=p;
	WFIFOL(char_fd,4)=sd->bl.id;
	WFIFOSET(char_fd,p);

	return 0;
}

/*==========================================
 * アカウント変数通知
 *------------------------------------------
 */
static int chrif_accountreg2(int fd)
{
	int j,p;
	struct map_session_data *sd;

	if( (sd=map_id2sd(RFIFOL(fd,4)))==NULL )
		return 1;

	for(p=8,j=0;p<RFIFOW(fd,2) && j<ACCOUNT_REG2_NUM;p+=36,j++){
		memcpy(sd->save_reg.account2[j].str,RFIFOP(fd,p),32);
		sd->save_reg.account2[j].str[31] = '\0';	// force \0 terminal
		sd->save_reg.account2[j].value   = RFIFOL(fd,p+32);
	}
	sd->save_reg.account2_num=j;
	return 0;
}

/*==========================================
 * 離婚情報同期要求
 *------------------------------------------
 */
int chrif_reqdivorce(int char_id)
{
	if (char_fd < 0)
		return -1;

	WFIFOW(char_fd,0)=0x2b20;
	WFIFOL(char_fd,2)=char_id;
	WFIFOSET(char_fd,6);

	return 0;
}

/*==========================================
 * 離婚情報同期受付
 *------------------------------------------
 */
static int chrif_divorce(int char_id)
{
	struct map_session_data *sd = NULL;

	if( char_id <= 0 )
		return 0;
	if( (sd = map_charid2sd(char_id)) == NULL )
		return 0;

	if( sd->status.partner_id ){
		struct map_session_data *p_sd = map_id2sd(sd->status.partner_id);
		int i;
		// 離婚
		sd->status.partner_id = 0;

		// 結婚指輪を剥奪
		for(i=0;i<MAX_INVENTORY;i++) {
			if(sd->status.inventory[i].nameid == WEDDING_RING_M || sd->status.inventory[i].nameid == WEDDING_RING_F) {
				pc_delitem(sd,i,1,0,0);
				break;
			}
		}
		if(p_sd)
			clif_divorced(sd, p_sd->status.name);
	}
	return 0;
}

/*==========================================
 * mapサーバアクティブ要求
 *------------------------------------------
 */
int chrif_mapactive(int active)
{
	if (char_fd < 0)
		return -1;

	WFIFOW(char_fd,0)=0x2b13;
	WFIFOB(char_fd,2)=active;
	WFIFOSET(char_fd,3);
	printf("chrif: map_server_active %d\n",active);

	return 0;
}

/*==========================================
 * charサーバメンテナンス要求
 *------------------------------------------
 */
int chrif_maintenance(int maintenance)
{
	if (char_fd < 0)
		return -1;

	WFIFOW(char_fd,0)=0x2b14;
	WFIFOB(char_fd,2)=maintenance;
	WFIFOSET(char_fd,3);
	printf("chrif: char_server_maintenance %d\n",maintenance);

	return 0;
}

/*==========================================
 * charサーバメンテナンス応答
 *------------------------------------------
 */
static int chrif_maintenanceack(int maintenance)
{
	const char *mes = (maintenance)? msg_txt(82): msg_txt(83);

	clif_GMmessage(NULL, mes, strlen(mes) + 1, 0);

	return 0;
}

/*==========================================
 * キャラクター切断通知
 *------------------------------------------
 */
int chrif_chardisconnect(struct map_session_data *sd)
{
	nullpo_retr(-1, sd);

	if (char_fd < 0)
		return -1;

	WFIFOW(char_fd,0)=0x2b18;
	WFIFOL(char_fd,2)=sd->status.account_id;
	WFIFOL(char_fd,6)=sd->status.char_id;
	WFIFOSET(char_fd,10);

	return 0;
}

/*==========================================
 * charからキャラクター強制切断要求
 *------------------------------------------
 */
static int chrif_parse_chardisconnectreq(int account_id)
{
	struct map_session_data *sd=map_id2sd(account_id);

	if(sd)
		clif_setwaitclose(sd->fd);

	return 0;
}

/*==========================================
 * ニ重ログイン時の処理
 *------------------------------------------
 */
static int chrif_parse_chardisconnect_doublelogin(int account_id)
{
	struct map_session_data *sd=map_id2sd(account_id);

	if(sd) {
		clif_authfail_fd(sd->fd,2);
		clif_setwaitclose(sd->fd);
	}
	return 0;
}

/*==========================================
 * 友達リストの削除通知
 *------------------------------------------
 */
int chrif_friend_delete( struct map_session_data* sd, int account_id, int char_id )
{
	if (char_fd < 0)
		return -1;

	WFIFOW(char_fd, 0) = 0x2b24;
	WFIFOL(char_fd, 2) = account_id;
	WFIFOL(char_fd, 6) = char_id;
	WFIFOL(char_fd,10) = sd->bl.id;
	WFIFOL(char_fd,14) = sd->status.char_id;
	WFIFOSET(char_fd, 18);

	return 0;
}

/*==========================================
 * 友達リストの削除通知
 *------------------------------------------
 */
static int chrif_parse_friend_delete( int fd )
{
	friend_del_from_otherserver( RFIFOL(fd,2), RFIFOL(fd,6), RFIFOL(fd,10), RFIFOL(fd,14) );
	return 0;
}

/*==========================================
 * 友達リストのオンライン情報通知
 *------------------------------------------
 */
int chrif_friend_online( struct map_session_data *sd, int flag )
{
	int i, len;

	if (char_fd < 0)
		return -1;

	WFIFOW(char_fd, 0) = 0x2b26;
	WFIFOL(char_fd, 4) = sd->bl.id;
	WFIFOL(char_fd, 8) = sd->status.char_id;
	WFIFOL(char_fd,12) = flag;
	for( i=0, len=16; i<sd->status.friend_num; i++, len+=8 )
	{
		WFIFOL(char_fd, len  ) = sd->status.friend_data[i].account_id;
		WFIFOL(char_fd, len+4) = sd->status.friend_data[i].char_id;
	}
	WFIFOW(char_fd, 2) = len;
	WFIFOSET(char_fd, len);

	return 0;
}

/*==========================================
 * 友達リストのオンライン情報通知受信
 *------------------------------------------
 */
static int chrif_parse_friend_online( int fd )
{
	friend_send_online_from_otherserver( RFIFOL(fd,4), RFIFOL(fd,8), RFIFOL(fd,12), ( (RFIFOW(fd,2)-16)/8 ), (int*)RFIFOP( fd,16 ) );
	return 0;
}

/*==========================================
 * 養子解体情報同期要求
 *------------------------------------------
 */
int chrif_req_break_adoption(int char_id, const char *name)
{
	if (char_fd < 0)
		return -1;

	WFIFOW(char_fd,0)=0x2b28;
	WFIFOL(char_fd,2)=char_id;
	strncpy(WFIFOP(char_fd,6), name, 24);
	WFIFOSET(char_fd,30);

	return 0;
}

/*==========================================
 * 養子情報同期受付
 *------------------------------------------
 */
static int chrif_breakadoption(int char_id, const char *name)
{
	struct map_session_data *sd = NULL;
	char output[100];

	if( char_id <= 0 )
		return 0;
	if( (sd = map_charid2sd(char_id)) == NULL )
		return 0;

	sd->status.baby_id      = 0;
	sd->status.parent_id[0] = 0;
	sd->status.parent_id[1] = 0;

	if(pc_isbaby(sd)) {
		// 子供なら元の職に戻す
		pc_jobchange(sd,sd->s_class.job,0);
	} else {
		// 親ならWE_BABY破棄（離婚しててもいいのでpc_ismarriedは使わない）
		status_calc_pc(sd,0);
	}

	snprintf(output, sizeof(output), msg_txt(174), name); // %sさんの要望により、養子関係が破棄されました
	clif_disp_onlyself(sd->fd, output);
#if PACKETVER > 20080102
	clif_skillinfoblock(sd);
#endif
	return 0;
}

/*==========================================
 * ランキングデータ要求
 *------------------------------------------
 */
int chrif_ranking_request(int fd)
{
	if (fd < 0)
		return -1;

	WFIFOW(fd,0) = 0x2b2e;
	WFIFOSET(fd,2);

	return 0;
}

/*==========================================
 * ランキングデータ更新
 *------------------------------------------
 */
int chrif_ranking_update(struct Ranking_Data *rd,int ranking_id,int rank)
{
	if (char_fd < 0)
		return -1;

	WFIFOW(char_fd,0) = 0x2b2f;
	WFIFOW(char_fd,2) = 8+sizeof(struct Ranking_Data);
	WFIFOW(char_fd,4) = ranking_id;
	WFIFOW(char_fd,6) = rank;
	memcpy(WFIFOP(char_fd,8), rd, sizeof(struct Ranking_Data));
	WFIFOSET(char_fd,WFIFOW(char_fd,2));

	return 0;
}

/*==========================================
 * ランキングデータ受信
 *------------------------------------------
 */
static int chrif_ranking_recv(int fd)
{
	ranking_set_data((int)RFIFOW(fd,4),(struct Ranking_Data *)RFIFOP(fd,6));
	return 0;
}

/*==========================================
 * MAPサーバタグ名登録応答
 *------------------------------------------
 */
static int chrif_mapservertag_ack(int fail)
{
	if(fail)
		printf("Map Server Tag: tag name is duplicated!\a\n");

	return 0;
}

/*==========================================
 * クライアントを切断する
 *------------------------------------------
 */
int chrif_disconnect_sub(struct map_session_data* sd,va_list va)
{
	delete_session(sd->fd);
	return 0;
}

/*==========================================
 * 切断された場合の処理
 *------------------------------------------
 */
static int chrif_disconnect(int fd)
{
	if (fd == char_fd) {
		char_fd = -1;
		// 同期が取れないのと、再接続した時に問題が起る可能性があるので、
		// map 鯖に接続しているキャラを全て切断する。
		printf("chrif: connection to the char server was closed. kick all chars\n");
		clif_foreachclient(chrif_disconnect_sub);
		// 他のmap 鯖のデータを消す
		map_eraseallipport();

		// 倉庫キャッシュを消す
		storage_clear_cache();
	}
	close(fd);

	return 0;
}

/*==========================================
 * パケットの解析
 *------------------------------------------
 */
int chrif_parse(int fd)
{
	int packet_len,cmd;

	while(RFIFOREST(fd)>=2){
		cmd = RFIFOW(fd,0);
		if(cmd<0x2af8 || cmd>=0x2af8+(sizeof(packet_len_table)/sizeof(packet_len_table[0])) || packet_len_table[cmd-0x2af8]==0)
		{
			int r=intif_parse(fd);// intifに渡す

			if( r==1 )	continue;	// intifで処理した
			if( r==2 )	return 0;	// intifで処理したが、データが足りない

			// intifで処理できなかった
			printf("chrif_parse: unknown packet 0x%04x disconnect session #%d\n", cmd, fd);
#ifdef DUMP_UNKNOWN_PACKET
			hex_dump(stdout, RFIFOP(fd,0), RFIFOREST(fd));
			printf("\n");
#endif
			close(fd);
			session[fd]->eof = 1;
			return 0;
		}
		packet_len = packet_len_table[cmd-0x2af8];
		if(packet_len==-1){
			if(RFIFOREST(fd)<4)
				return 0;
			packet_len = RFIFOW(fd,2);
		}
		if(RFIFOREST(fd)<packet_len)
			return 0;

		switch(cmd){
		case 0x2af9: chrif_connectack(fd); break;
		case 0x2afb: chrif_sendmapack(fd); break;
		case 0x2afd: chrif_authok(fd); break;
		case 0x2afe: pc_authfail(RFIFOL(fd,2)); break;
		case 0x2b00: map_setusers(RFIFOL(fd,2)); break;
		case 0x2b03: clif_charselectok(RFIFOL(fd,2)); break;
		case 0x2b04: chrif_recvmap(fd); break;
		case 0x2b06: chrif_changemapserverack(fd); break;
		case 0x2b07: chrif_saveack(fd); break;
		case 0x2b09: map_addchariddb(RFIFOL(fd,2),RFIFOP(fd,6),RFIFOL(fd,30),RFIFOL(fd,34),RFIFOW(fd,38)); break;
		case 0x2b0b: chrif_changedgm(fd); break;
		case 0x2b0d: chrif_changedsex(fd); break;
		case 0x2b11: chrif_accountreg2(fd); break;
		case 0x2b12: chrif_divorce(RFIFOL(fd,2)); break;
		case 0x2b15: chrif_maintenanceack(RFIFOB(fd,2)); break;
		case 0x2b16: chrif_recverasemap(fd); break;
		case 0x2b17: map_delchariddb(RFIFOL(fd,2)); break;
		case 0x2b19: chrif_parse_chardisconnectreq(RFIFOL(fd,2)); break;
		case 0x2b1a: chrif_parse_chardisconnect_doublelogin(RFIFOL(fd,2)); break;
		case 0x2b25: chrif_parse_friend_delete(fd); break;
		case 0x2b27: chrif_parse_friend_online(fd); break;
		case 0x2b29: chrif_breakadoption(RFIFOL(fd,2),RFIFOP(fd,6)); break;
		case 0x2b2b: chrif_cram_connect(fd); break;
		case 0x2b30: chrif_ranking_recv(fd); break;
		case 0x2b31: chrif_mapservertag_ack(RFIFOB(fd,2)); break;

		default:
			printf("chrif_parse: unknown packet 0x%04x disconnect session #%d\n", cmd, fd);
#ifdef DUMP_UNKNOWN_PACKET
			hex_dump(stdout, RFIFOP(fd,0), packet_len);
			printf("\n");
#endif
			close(fd);
			session[fd]->eof=1;
			return 0;
		}
		RFIFOSKIP(fd,packet_len);
	}
	return 0;
}

/*==========================================
 * クライアント数通知
 *------------------------------------------
 */
static int send_users_tochar(int tid,unsigned int tick,int id,void *data)
{
	if (char_fd < 0 || session[char_fd] == NULL || session[char_fd]->auth == 0)
		return 0;

	// 今このmap鯖に繋がっているクライアント人数をchar鯖へ送る
	WFIFOW(char_fd,0)=0x2aff;
	WFIFOL(char_fd,2)=clif_countusers();
	WFIFOSET(char_fd,6);

	return 0;
}

/*==========================================
 * 自動再接続
 *------------------------------------------
 */
static int check_connect_char_server(int tid,unsigned int tick,int id,void *data)
{
	// char鯖との接続を確認し、もし切れていたら再度接続する
	if (char_fd < 0 || session[char_fd] == NULL) {
		chrif_state = 0;
		char_fd = make_connection(char_ip,char_port);
		if (char_fd < 0)
			return 0;
		session[char_fd]->func_parse=chrif_parse;
		session[char_fd]->func_destruct=chrif_disconnect;
		realloc_fifo(char_fd, RFIFOSIZE_SERVERLINK, WFIFOSIZE_SERVERLINK);

		chrif_connect(char_fd);
	}

	return 0;
}

/*==========================================
 * char,interサーバへデータ送信
 *------------------------------------------
 */
int chrif_flush_fifo(void)
{
	if(char_fd < 0)
		return -1;

	flush_fifo(char_fd);

	return 0;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
int do_final_chrif(void)
{
	chrif_flush_fifo();
	delete_session(char_fd);

	return 0;
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
int do_init_chrif(void)
{
	unsigned int tick = gettick();

	add_timer_func_list(check_connect_char_server);
	add_timer_func_list(send_users_tochar);
	add_timer_interval(tick+1000,check_connect_char_server,0,NULL,10*1000);
	add_timer_interval(tick+1000,send_users_tochar,0,NULL,5*1000);

	return 0;
}
