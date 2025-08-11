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

#define DUMP_UNKNOWN_PACKET	1

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#ifndef WINDOWS
	#include <unistd.h>	// sleep
#else
	#include <windows.h>
#endif

#include "socket.h"
#include "timer.h"
#include "malloc.h"
#include "version.h"
#include "nullpo.h"
#include "httpd.h"
#include "utils.h"
#include "mmo.h"

#include "map.h"
#include "chrif.h"
#include "clif.h"
#include "pc.h"
#include "npc.h"
#include "itemdb.h"
#include "chat.h"
#include "trade.h"
#include "storage.h"
#include "script.h"
#include "skill.h"
#include "atcommand.h"
#include "msg.h"
#include "intif.h"
#include "battle.h"
#include "mob.h"
#include "party.h"
#include "guild.h"
#include "vending.h"
#include "pet.h"
#include "status.h"
#include "friend.h"
#include "unit.h"
#include "mail.h"
#include "homun.h"
#include "ranking.h"
#include "merc.h"
#include "quest.h"
#include "booking.h"
#include "buyingstore.h"
#include "elem.h"
#include "memorial.h"
#include "achieve.h"
#include "bank.h"
#include "luascript.h"

/* �p�P�b�g�f�[�^�x�[�X */
#define MAX_PACKET_DB 0xC20

struct packet_db {
	short len;
	void (*func)(int fd,struct map_session_data *sd, int cmd);
	short pos[8];
};

static struct packet_db packet_db[MAX_PACKET_DB];

// local define
#define WBUFPOS(p,pos,x,y,dir) \
	{ \
		unsigned char *__p = (p); \
		__p += (pos); \
		__p[0] = (unsigned char)((x)>>2); \
		__p[1] = (unsigned char)(((x)<<6) | (((y)>>4)&0x3f)); \
		__p[2] = (unsigned char)(((y)<<4) | ((dir)&0xf)); \
	}

#define WBUFPOS2(p,pos,x0,y0,x1,y1,sx0,sy0) \
	{ \
		unsigned char *__p = (p); \
		__p += (pos); \
		__p[0] = (unsigned char)((x0)>>2); \
		__p[1] = (unsigned char)(((x0)<<6) | (((y0)>>4)&0x3f)); \
		__p[2] = (unsigned char)(((y0)<<4) | (((x1)>>6)&0x0f)); \
		__p[3] = (unsigned char)(((x1)<<2) | (((y1)>>8)&0x03)); \
		__p[4] = (unsigned char)(y1); \
		__p[5] = (unsigned char)(((sx0)<<4) | ((sy0)&0x0f)); \
	}

#define WFIFOPOS(fd,pos,x,y,dir) { WBUFPOS(WFIFOP(fd,pos),0,x,y,dir); }
#define WFIFOPOS2(fd,pos,x0,y0,x1,y1,sx0,sy0) { WBUFPOS2(WFIFOP(fd,pos),0,x0,y0,x1,y1,sx0,sy0); }

#define WBUFLV(p,pos,lv,class_) \
	if(battle_config.clif_fix_level) { \
		if(((class_) >= PC_CLASS_RK && (class_) <= PC_CLASS_NC2_B) || (class_) == PC_CLASS_ESNV || ((class_) >= PC_CLASS_KG && (class_) <= PC_CLASS_SUM)) { \
			WBUFW((p),(pos)) = ((lv) > 175)? 175: (lv); \
		} else { \
			WBUFW((p),(pos)) = ((lv) > 99)? 99: (lv); \
		} \
	} else { \
		WBUFW((p),(pos)) = (lv); \
	}

#define WFIFOLV(fd,pos,lv,class_) { WBUFLV(WFIFOP(fd,pos),0,lv,class_); }

static char map_host[256] = "";
static unsigned long map_ip;
static unsigned short map_port = 5121;
static int map_fd;

static int g_packet_len = 0;
#define GETPACKETPOS(cmd,idx)  ( packet_db[cmd].pos[idx] + ( ( packet_db[cmd].pos[idx] < 0 )? g_packet_len : 0 ) )

static unsigned int cryptKey[3];


/*==========================================
 * map�I�̃z�X�g�ݒ�
 *------------------------------------------
 */
void clif_sethost(const char *host)
{
	size_t len = strlen(host) + 1;

	if(len > sizeof(map_host))
		len = sizeof(map_host);

	memcpy(map_host, host, len);
	map_host[len-1] = '\0';	// force \0 terminal

	return;
}

/*==========================================
 * map�I��ip�ݒ�
 *------------------------------------------
 */
void clif_setip(void)
{
	map_ip = host2ip(map_host, "Map server IP address");

	return;
}

/*==========================================
 * map�I��port�ݒ�
 *------------------------------------------
 */
void clif_setport(unsigned short port)
{
	map_port = port;

	return;
}

/*==========================================
 * map�I��ip�ǂݏo��
 *------------------------------------------
 */
unsigned long clif_getip(void)
{
	return map_ip;
}

/*==========================================
 * map�I��port�ǂݏo��
 *------------------------------------------
 */
unsigned short clif_getport(void)
{
	return map_port;
}

/*==========================================
 *
 *------------------------------------------
 */
int clif_countusers(void)
{
	int users=0,i;
	struct map_session_data *sd;

	for(i=0;i<fd_max;i++){
		if( session[i] && (sd = (struct map_session_data *)session[i]->session_data) && sd->state.auth &&
		    !(battle_config.hide_GM_session && pc_isGM(sd)) )
			users++;
	}

	return users;
}

/*==========================================
 * �S�Ă�client�ɑ΂���func()���s
 *------------------------------------------
 */
int clif_foreachclient(int (*func)(struct map_session_data*,va_list),...)
{
	int i, ret = 0;
	struct map_session_data *sd;

	for(i=0;i<fd_max;i++){
		if(
			session[i] && session[i]->func_parse == clif_parse &&
			(sd = (struct map_session_data *)session[i]->session_data) && sd->state.auth &&
			!sd->state.waitingdisconnect
		) {
			va_list ap;
			va_start(ap, func);
			ret += func(sd,ap);
			va_end(ap);
		}
	}

	return ret;
}

/*==========================================
 * clif_send��AREA*�w�莞�p
 *------------------------------------------
 */
static int clif_send_sub(struct block_list *bl,va_list ap)
{
	unsigned char *buf;
	int len;
	struct block_list *src_bl;
	int type, fd;
	struct map_session_data *sd;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, sd=(struct map_session_data *)bl);

	buf=va_arg(ap,unsigned char*);
	len=va_arg(ap,int);
	nullpo_retr(0, src_bl=va_arg(ap,struct block_list*));
	type=va_arg(ap,int);

	switch(type){
	case AREA_WOS:
		if(bl==src_bl)
			return 0;
		break;
	case AREA_WOC:
		if(sd->chatID || bl==src_bl)
			return 0;
		break;
	case AREA_WOSC:
		if(sd->chatID && src_bl->type == BL_PC && sd->chatID == ((struct map_session_data*)src_bl)->chatID)
			return 0;
		break;
	}

	fd = sd->fd;
	memcpy(WFIFOP(fd,0),buf,len);
	WFIFOSET(fd,len);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_send(unsigned char *buf, size_t len, struct block_list *bl, int type)
{
	int i;
	struct map_session_data *sd = NULL;
	int x0=0,x1=0,y0=0,y1=0;

	if( type != ALL_CLIENT ){
		nullpo_retv(bl);
	}

	switch(type){
	case ALL_CLIENT:	// �S�N���C�A���g�ɑ��M
		for(i=0;i<fd_max;i++){
			if(session[i] && (sd = (struct map_session_data *)session[i]->session_data) && sd->state.auth){
				memcpy(WFIFOP(i,0),buf,len);
				WFIFOSET(i,len);
			}
		}
		break;
	case ALL_SAMEMAP:	// �����}�b�v�̑S�N���C�A���g�ɑ��M
		for(i=0;i<fd_max;i++){
			if(session[i] && (sd = (struct map_session_data *)session[i]->session_data) && sd->state.auth && sd->bl.m == bl->m){
				memcpy(WFIFOP(i,0),buf,len);
				WFIFOSET(i,len);
			}
		}
		break;
	case AREA:
	case AREA_WOS:
	case AREA_WOC:
	case AREA_WOSC:
		map_foreachinarea(clif_send_sub,bl->m,bl->x-AREA_SIZE,bl->y-AREA_SIZE,bl->x+AREA_SIZE,bl->y+AREA_SIZE,BL_PC,buf,len,bl,type);
		break;
	case AREA_CHAT_WOC:
		map_foreachinarea(clif_send_sub,bl->m,bl->x-(AREA_SIZE-5),bl->y-(AREA_SIZE-5),bl->x+(AREA_SIZE-5),bl->y+(AREA_SIZE-5),BL_PC,buf,len,bl,AREA_WOC);
		break;
	case WIDE_AREA:
		map_foreachinarea(clif_send_sub,bl->m,bl->x-WIDE_AREA_SIZE,bl->y-WIDE_AREA_SIZE,bl->x+WIDE_AREA_SIZE,bl->y+WIDE_AREA_SIZE,BL_PC,buf,len,bl,type);
		break;
	case CHAT:
	case CHAT_WOS:
		{
			struct chat_data *cd = NULL;
			if(bl->type==BL_PC){
				sd=(struct map_session_data*)bl;
				if(sd->chatID)
					cd=map_id2cd(sd->chatID);
			} else if(bl->type==BL_CHAT) {
				cd=(struct chat_data*)bl;
			}
			if(cd==NULL)
				break;
			for(i=0;i<cd->users;i++){
				if(type==CHAT_WOS && &cd->usersd[i]->bl == bl)
					continue;
				memcpy(WFIFOP(cd->usersd[i]->fd,0),buf,len);
				WFIFOSET(cd->usersd[i]->fd,len);
			}
		}
		break;

	case PARTY_AREA:		// ������ʓ��̑S�p�[�e�B�[�����o�ɑ��M
	case PARTY_AREA_WOS:		// �����ȊO�̓�����ʓ��̑S�p�[�e�B�[�����o�ɑ��M
		x0=bl->x-AREA_SIZE;
		y0=bl->y-AREA_SIZE;
		x1=bl->x+AREA_SIZE;
		y1=bl->y+AREA_SIZE;
	case PARTY:			// �S�p�[�e�B�[�����o�ɑ��M
	case PARTY_WOS:			// �����ȊO�̑S�p�[�e�B�[�����o�ɑ��M
	case PARTY_SAMEMAP:		// �����}�b�v�̑S�p�[�e�B�[�����o�ɑ��M
	case PARTY_SAMEMAP_WOS:		// �����ȊO�̓����}�b�v�̑S�p�[�e�B�[�����o�ɑ��M
		{
			struct party *p = NULL;
			if(bl->type==BL_PC){
				sd=(struct map_session_data *)bl;
				if(sd && sd->status.party_id>0)
					p=party_search(sd->status.party_id);
			}
			if(p == NULL)
				break;
			for(i=0;i<MAX_PARTY;i++){
				if((sd=p->member[i].sd)!=NULL){
					if( sd->bl.id==bl->id && (type==PARTY_WOS ||
						type==PARTY_SAMEMAP_WOS || type==PARTY_AREA_WOS))
						continue;
					if(type!=PARTY && type!=PARTY_WOS && bl->m!=sd->bl.m)	// �}�b�v�`�F�b�N
						continue;
					if((type==PARTY_AREA || type==PARTY_AREA_WOS) &&
						(sd->bl.x<x0 || sd->bl.y<y0 ||
						 sd->bl.x>x1 || sd->bl.y>y1 ) )
						continue;

					memcpy(WFIFOP(sd->fd,0),buf,len);
					WFIFOSET(sd->fd,len);
				}
			}
		}
		break;
	case SELF:
		if(bl->type == BL_PC && (sd=(struct map_session_data *)bl)) {
			memcpy(WFIFOP(sd->fd,0),buf,len);
			WFIFOSET(sd->fd,len);
		}
		break;

	case GUILD:
	case GUILD_WOS:
	case GUILD_SAMEMAP_WOS:
		{
			struct guild *g = NULL;
			if(bl->type==BL_PC){
				sd=(struct map_session_data *)bl;
				if(sd && sd->status.guild_id>0)
					g=guild_search(sd->status.guild_id);
			}
			if(g == NULL)
				break;
			for(i=0;i<g->max_member;i++){
				if((sd=g->member[i].sd)!=NULL){
					if((type==GUILD_WOS || type==GUILD_SAMEMAP_WOS) && sd->bl.id==bl->id)
						continue;
					if(type==GUILD_SAMEMAP_WOS && sd->bl.m!=bl->m)
						continue;
					memcpy(WFIFOP(sd->fd,0),buf,len);
					WFIFOSET(sd->fd,len);
				}
			}
		}
		break;

	default:
		if(battle_config.error_log)
			printf("clif_send �܂�����ĂȂ���[\n");
		return;
	}

	return;
}

//
// �p�P�b�g����đ��M
//
/*==========================================
 *
 *------------------------------------------
 */
void clif_authok(struct map_session_data *sd)
{
	int fd;
	unsigned int tick = gettick();

	nullpo_retv(sd);

	fd=sd->fd;

#if PACKETVER < 20080102
	WFIFOW(fd,0)=0x73;
	WFIFOL(fd,2)=tick;
	WFIFOPOS(fd,6,sd->bl.x,sd->bl.y,sd->dir);
	WFIFOB(fd,9)=5;
	WFIFOB(fd,10)=5;
	WFIFOSET(fd,packet_db[0x73].len);
#elif PACKETVER < 20141022 || PACKETVER >= 20160330
	WFIFOW(fd,0)=0x2eb;
	WFIFOL(fd,2)=tick;
	WFIFOPOS(fd,6,sd->bl.x,sd->bl.y,sd->dir);
	WFIFOB(fd,9)=5;
	WFIFOB(fd,10)=5;
	WFIFOW(fd,11)=sd->status.font;
	WFIFOSET(fd,packet_db[0x2eb].len);
#else
	WFIFOW(fd,0)=0xa18;
	WFIFOL(fd,2)=tick;
	WFIFOPOS(fd,6,sd->bl.x,sd->bl.y,sd->dir);
	WFIFOB(fd,9)=5;
	WFIFOB(fd,10)=5;
	WFIFOW(fd,11)=sd->status.font;
	WFIFOB(fd,13)=sd->sex;
	WFIFOSET(fd,packet_db[0xa18].len);
#endif

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_authfail_fd(int fd, unsigned int type)
{
	WFIFOW(fd,0)=0x81;
	WFIFOL(fd,2)=type;
	WFIFOSET(fd,packet_db[0x81].len);

	clif_setwaitclose(fd);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_charselectok(int id)
{
	struct map_session_data *sd;
	int fd;

	if((sd=map_id2sd(id))==NULL)
		return;

	fd=sd->fd;
	WFIFOW(fd,0)=0xb3;
	WFIFOB(fd,2)=1;
	WFIFOSET(fd,packet_db[0xb3].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_disconnect_ack(int fd, int fail)
{
	WFIFOW(fd,0) = 0x18b;
	WFIFOW(fd,2) = fail;	// fail= 0: success, 1: failure (please wait 15 sec...)
	WFIFOSET(fd,packet_db[0x18b].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_dropflooritem(struct flooritem_data *fitem)
{
	int view, effect = 0;
	unsigned char buf[24];

	nullpo_retv(fitem);

	if(fitem->item_data.nameid <= 0)
		return;

#if PACKETVER < 20101020
	// 009e <ID>.l <name ID>.w <identify flag>.B <X>.w <Y>.w <subX>.B <subY>.B <amount>.w
	WBUFW(buf,0)=0x9e;
	WBUFL(buf,2)=fitem->bl.id;
	if((view = itemdb_viewid(fitem->item_data.nameid)) > 0)
		WBUFW(buf,6)=view;
	else
		WBUFW(buf,6)=fitem->item_data.nameid;
	WBUFB(buf,8)=fitem->item_data.identify;
	WBUFW(buf,9)=fitem->bl.x;
	WBUFW(buf,11)=fitem->bl.y;
	WBUFB(buf,13)=fitem->subx;
	WBUFB(buf,14)=fitem->suby;
	WBUFW(buf,15)=fitem->item_data.amount;
	clif_send(buf,packet_db[0x9e].len,&fitem->bl,AREA);
#elif PACKETVER < 20180418
	WBUFW(buf,0)=0x84b;
	WBUFL(buf,2)=fitem->bl.id;
	if((view = itemdb_viewid(fitem->item_data.nameid)) > 0)
		WBUFW(buf,6)=view;
	else
		WBUFW(buf,6)=fitem->item_data.nameid;
	WBUFW(buf,8)=0;	// TODO: unsigned short type;
	WBUFB(buf,10)=fitem->item_data.identify;
	WBUFW(buf,11)=fitem->bl.x;
	WBUFW(buf,13)=fitem->bl.y;
	WBUFB(buf,15)=fitem->subx;
	WBUFB(buf,16)=fitem->suby;
	WBUFW(buf,17)=fitem->item_data.amount;
	clif_send(buf,packet_db[0x84b].len,&fitem->bl,AREA);
#elif PACKETVER < 20180704
	WBUFW(buf,0)=0xadd;
	WBUFL(buf,2)=fitem->bl.id;
	if((view = itemdb_viewid(fitem->item_data.nameid)) > 0)
		WBUFW(buf,6)=view;
	else
		WBUFW(buf,6)=fitem->item_data.nameid;
	WBUFW(buf,8)=0;	// TODO: unsigned short type;
	WBUFB(buf,10)=fitem->item_data.identify;
	WBUFW(buf,11)=fitem->bl.x;
	WBUFW(buf,13)=fitem->bl.y;
	WBUFB(buf,15)=fitem->subx;
	WBUFB(buf,16)=fitem->suby;
	WBUFW(buf,17)=fitem->item_data.amount;
	if((effect = itemdb_dropeffect(fitem->item_data.nameid)) > 0) {
		WBUFB(buf,19)=1;
		WBUFW(buf,20)=effect - 1;
	}
	else {
		WBUFB(buf,19)=0;
		WBUFW(buf,20)=0;
	}
	clif_send(buf,packet_db[0xadd].len,&fitem->bl,AREA);
#else
	WBUFW(buf,0)=0xadd;
	WBUFL(buf,2)=fitem->bl.id;
	if((view = itemdb_viewid(fitem->item_data.nameid)) > 0)
		WBUFL(buf,6)=view;
	else
		WBUFL(buf,6)=fitem->item_data.nameid;
	WBUFW(buf,10)=0;	// TODO: unsigned short type;
	WBUFB(buf,12)=fitem->item_data.identify;
	WBUFW(buf,13)=fitem->bl.x;
	WBUFW(buf,15)=fitem->bl.y;
	WBUFB(buf,17)=fitem->subx;
	WBUFB(buf,18)=fitem->suby;
	WBUFW(buf,19)=fitem->item_data.amount;
	if((effect = itemdb_dropeffect(fitem->item_data.nameid)) > 0) {
		WBUFB(buf,21)=1;
		WBUFW(buf,22)=effect - 1;
	}
	else {
		WBUFB(buf,21)=0;
		WBUFW(buf,22)=0;
	}
	clif_send(buf,packet_db[0xadd].len,&fitem->bl,AREA);
#endif

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_clearflooritem(struct flooritem_data *fitem, int fd)
{
	unsigned char buf[8];

	nullpo_retv(fitem);

	WBUFW(buf,0) = 0xa1;
	WBUFL(buf,2) = fitem->bl.id;

	if(fd < 0) {
		clif_send(buf,packet_db[0xa1].len,&fitem->bl,AREA);
	} else {
		memcpy(WFIFOP(fd,0),buf,6);
		WFIFOSET(fd,packet_db[0xa1].len);
	}

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_clearchar(struct block_list *bl, int type)
{
	unsigned char buf[8];

	nullpo_retv(bl);

	WBUFW(buf,0) = 0x80;
	WBUFL(buf,2) = bl->id;
	WBUFB(buf,6) = type;
	clif_send(buf,packet_db[0x80].len,bl,(type == 1) ? AREA : AREA_WOS);

	return;
}

static int clif_clearchar_delay_sub(int tid,unsigned int tick,int id,void *data)
{
	struct block_list *bl = (struct block_list *)data;
	unsigned char buf[8];

	WBUFW(buf,0) = 0x80;
	WBUFL(buf,2) = bl->id;
	WBUFB(buf,6) = 0;
	clif_send(buf,packet_db[0x80].len,bl,(id == 1) ? AREA_WOS : ALL_SAMEMAP);

	aFree(bl);
	return 0;
}

int clif_clearchar_delay(unsigned int tick,struct block_list *bl)
{
	struct block_list *tmpbl = (struct block_list *)aMalloc(sizeof(struct block_list));

	memcpy(tmpbl,bl,sizeof(struct block_list));
	add_timer2(tick,clif_clearchar_delay_sub,battle_config.pcview_mob_clear_type,tmpbl);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_clearchar_id(int id, unsigned char type, int fd)
{
	if(fd < 0)
		return;

	WFIFOW(fd,0) = 0x80;
	WFIFOL(fd,2) = id;
	WFIFOB(fd,6) = type;
	WFIFOSET(fd,packet_db[0x80].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_get_weapon_view(struct map_session_data* sd, int *rhand, int *lhand)
{
	int flag = 0;

	nullpo_retv(sd);

	flag = (sd->view_class != PC_CLASS_WE && sd->view_class != PC_CLASS_ST && sd->view_class != PC_CLASS_SU);

#if PACKETVER < 4
	if(rhand) {
		*rhand = (flag) ? sd->status.weapon : WT_FIST;
	}

	if(lhand) {
		*lhand = (flag) ? sd->status.sheild : WT_FIST;
	}
#else
	if(rhand) {
		int idx = sd->equip_index[EQUIP_INDEX_RARM];
		struct item_data *id = NULL;

		if(idx >= 0 && (id = sd->inventory_data[idx]) != NULL && flag) {
			if(id->view_id > 0)
				*rhand = id->view_id;
			else
				*rhand = id->nameid;
		} else {
			*rhand = 0;
		}
	}

	if(lhand) {
		int idx = sd->equip_index[EQUIP_INDEX_LARM];
		struct item_data *id = NULL;

		if(idx >= 0 && idx != sd->equip_index[EQUIP_INDEX_RARM] && (id = sd->inventory_data[idx]) != NULL && flag) {
			if(id->view_id > 0)
				*lhand = id->view_id;
			else
				*lhand = id->nameid;
		} else {
			*lhand = 0;
		}
	}
#endif

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static int clif_set0078(struct map_session_data *sd,unsigned char *buf)
{
	int rhand = 0, lhand = 0;

	nullpo_retr(0, sd);

	clif_get_weapon_view(sd, &rhand, &lhand);

#if PACKETVER < 4
	WBUFW(buf,0)=0x78;
	WBUFL(buf,2)=sd->bl.id;
	WBUFW(buf,6)=sd->speed;
	WBUFW(buf,8)=sd->sc.opt1;
	WBUFW(buf,10)=sd->sc.opt2;
	WBUFW(buf,12)=sd->sc.option;
	WBUFW(buf,14)=sd->view_class;
	WBUFW(buf,16)=sd->status.hair;
	WBUFW(buf,18)=rhand;
	WBUFW(buf,20)=sd->status.head_bottom;
	WBUFW(buf,22)=lhand;
	WBUFW(buf,24)=sd->status.head_top;
	WBUFW(buf,26)=sd->status.head_mid;
	WBUFW(buf,28)=sd->status.hair_color;
	WBUFW(buf,30)=sd->status.clothes_color;
	WBUFW(buf,32)=sd->head_dir;
	WBUFL(buf,34)=sd->status.guild_id;
	WBUFL(buf,38)=sd->guild_emblem_id;
	WBUFW(buf,42)=sd->status.manner;
	WBUFB(buf,44)=(unsigned char)sd->status.karma;
	WBUFB(buf,45)=sd->sex;
	WBUFPOS(buf,46,sd->bl.x,sd->bl.y,sd->dir);
	WBUFB(buf,49)=5;
	WBUFB(buf,50)=5;
	WBUFB(buf,51)=sd->state.dead_sit;
	WBUFLV(buf,52,sd->status.base_level,sd->status.class_);

	return packet_db[0x78].len;
#elif PACKETVER < 7
	WBUFW(buf,0)=0x1d8;
	WBUFL(buf,2)=sd->bl.id;
	WBUFW(buf,6)=sd->speed;
	WBUFW(buf,8)=sd->sc.opt1;
	WBUFW(buf,10)=sd->sc.opt2;
	WBUFW(buf,12)=sd->sc.option;
	WBUFW(buf,14)=sd->view_class;
	WBUFW(buf,16)=sd->status.hair;
	WBUFW(buf,18)=rhand;
	WBUFW(buf,20)=lhand;
	WBUFW(buf,22)=sd->status.head_bottom;
	WBUFW(buf,24)=sd->status.head_top;
	WBUFW(buf,26)=sd->status.head_mid;
	WBUFW(buf,28)=sd->status.hair_color;
	WBUFW(buf,30)=sd->status.clothes_color;
	WBUFW(buf,32)=sd->head_dir;
	WBUFL(buf,34)=sd->status.guild_id;
	WBUFW(buf,38)=sd->guild_emblem_id;
	WBUFW(buf,40)=sd->status.manner;
	WBUFW(buf,42)=sd->sc.opt3;
	WBUFB(buf,44)=(unsigned char)sd->status.karma;
	WBUFB(buf,45)=sd->sex;
	WBUFPOS(buf,46,sd->bl.x,sd->bl.y,sd->dir);
	WBUFB(buf,49)=5;
	WBUFB(buf,50)=5;
	WBUFB(buf,51)=sd->state.dead_sit;
	WBUFLV(buf,52,sd->status.base_level,sd->status.class_);

	return packet_db[0x1d8].len;
#elif PACKETVER < 20080102
	WBUFW(buf,0)=0x22a;
	WBUFL(buf,2)=sd->bl.id;
	WBUFW(buf,6)=sd->speed;
	WBUFW(buf,8)=sd->sc.opt1;
	WBUFW(buf,10)=sd->sc.opt2;
	WBUFL(buf,12)=sd->sc.option;
	WBUFW(buf,16)=sd->view_class;
	WBUFW(buf,18)=sd->status.hair;
	WBUFW(buf,20)=rhand;
	WBUFW(buf,22)=lhand;
	WBUFW(buf,24)=sd->status.head_bottom;
	WBUFW(buf,26)=sd->status.head_top;
	WBUFW(buf,28)=sd->status.head_mid;
	WBUFW(buf,30)=sd->status.hair_color;
	WBUFW(buf,32)=sd->status.clothes_color;
	WBUFW(buf,34)=sd->head_dir;
	WBUFL(buf,36)=sd->status.guild_id;
	WBUFW(buf,40)=sd->guild_emblem_id;
	WBUFW(buf,42)=sd->status.manner;
	WBUFL(buf,44)=sd->sc.opt3;
	WBUFB(buf,48)=(unsigned char)sd->status.karma;
	WBUFB(buf,49)=sd->sex;
	WBUFPOS(buf,50,sd->bl.x,sd->bl.y,sd->dir);
	WBUFB(buf,53)=5;
	WBUFB(buf,54)=5;
	WBUFB(buf,55)=sd->state.dead_sit;
	WBUFLV(buf,56,sd->status.base_level,sd->status.class_);

	return packet_db[0x22a].len;
#elif PACKETVER < 20091104
	WBUFW(buf,0)=0x2ee;
	WBUFL(buf,2)=sd->bl.id;
	WBUFW(buf,6)=sd->speed;
	WBUFW(buf,8)=sd->sc.opt1;
	WBUFW(buf,10)=sd->sc.opt2;
	WBUFL(buf,12)=sd->sc.option;
	WBUFW(buf,16)=sd->view_class;
	WBUFW(buf,18)=sd->status.hair;
	WBUFW(buf,20)=rhand;
	WBUFW(buf,22)=lhand;
	WBUFW(buf,24)=sd->status.head_bottom;
	WBUFW(buf,26)=sd->status.head_top;
	WBUFW(buf,28)=sd->status.head_mid;
	WBUFW(buf,30)=sd->status.hair_color;
	WBUFW(buf,32)=sd->status.clothes_color;
	WBUFW(buf,34)=sd->head_dir;
	WBUFL(buf,36)=sd->status.guild_id;
	WBUFW(buf,40)=sd->guild_emblem_id;
	WBUFW(buf,42)=sd->status.manner;
	WBUFL(buf,44)=sd->sc.opt3;
	WBUFB(buf,48)=(unsigned char)sd->status.karma;
	WBUFB(buf,49)=sd->sex;
	WBUFPOS(buf,50,sd->bl.x,sd->bl.y,sd->dir);
	WBUFB(buf,53)=5;
	WBUFB(buf,54)=5;
	WBUFB(buf,55)=sd->state.dead_sit;
	WBUFLV(buf,56,sd->status.base_level,sd->status.class_);
	WBUFW(buf,58)=sd->status.font;

	return packet_db[0x2ee].len;
#elif PACKETVER < 20110111
	WBUFW(buf,0)=0x7f9;
	WBUFW(buf,2)=(unsigned short)(63 + strlen(sd->status.name));
	WBUFB(buf,4)=0;
	WBUFL(buf,5)=sd->bl.id;
	WBUFW(buf,9)=sd->speed;
	WBUFW(buf,11)=sd->sc.opt1;
	WBUFW(buf,13)=sd->sc.opt2;
	WBUFL(buf,15)=sd->sc.option;
	WBUFW(buf,19)=sd->view_class;
	WBUFW(buf,21)=sd->status.hair;
	WBUFW(buf,23)=rhand;
	WBUFW(buf,25)=lhand;
	WBUFW(buf,27)=sd->status.head_bottom;
	WBUFW(buf,29)=sd->status.head_top;
	WBUFW(buf,31)=sd->status.head_mid;
	WBUFW(buf,33)=sd->status.hair_color;
	WBUFW(buf,35)=sd->status.clothes_color;
	WBUFW(buf,37)=sd->head_dir;
	WBUFL(buf,39)=sd->status.guild_id;
	WBUFW(buf,43)=sd->guild_emblem_id;
	WBUFW(buf,45)=sd->status.manner;
	WBUFL(buf,47)=sd->sc.opt3;
	WBUFB(buf,51)=(unsigned char)sd->status.karma;
	WBUFB(buf,52)=sd->sex;
	WBUFPOS(buf,53,sd->bl.x,sd->bl.y,sd->dir);
	WBUFB(buf,56)=5;
	WBUFB(buf,57)=5;
	WBUFB(buf,58)=sd->state.dead_sit;
	WBUFLV(buf,59,sd->status.base_level,sd->status.class_);
	WBUFW(buf,61)=sd->status.font;
	strncpy(WBUFP(buf,63),sd->status.name,24);

	return WBUFW(buf,2);
#elif PACKETVER < 20120328
	WBUFW(buf,0)=0x857;
	WBUFW(buf,2)=(unsigned short)(65 + strlen(sd->status.name));
	WBUFB(buf,4)=0;
	WBUFL(buf,5)=sd->bl.id;
	WBUFW(buf,9)=sd->speed;
	WBUFW(buf,11)=sd->sc.opt1;
	WBUFW(buf,13)=sd->sc.opt2;
	WBUFL(buf,15)=sd->sc.option;
	WBUFW(buf,19)=sd->view_class;
	WBUFW(buf,21)=sd->status.hair;
	WBUFW(buf,23)=rhand;
	WBUFW(buf,25)=lhand;
	WBUFW(buf,27)=sd->status.head_bottom;
	WBUFW(buf,29)=sd->status.head_top;
	WBUFW(buf,31)=sd->status.head_mid;
	WBUFW(buf,33)=sd->status.hair_color;
	WBUFW(buf,35)=sd->status.clothes_color;
	WBUFW(buf,37)=sd->head_dir;
	WBUFW(buf,39)=sd->status.robe;
	WBUFL(buf,41)=sd->status.guild_id;
	WBUFW(buf,45)=sd->guild_emblem_id;
	WBUFW(buf,47)=sd->status.manner;
	WBUFL(buf,49)=sd->sc.opt3;
	WBUFB(buf,53)=(unsigned char)sd->status.karma;
	WBUFB(buf,54)=sd->sex;
	WBUFPOS(buf,55,sd->bl.x,sd->bl.y,sd->dir);
	WBUFB(buf,58)=5;
	WBUFB(buf,59)=5;
	WBUFB(buf,60)=sd->state.dead_sit;
	WBUFLV(buf,61,sd->status.base_level,sd->status.class_);
	WBUFW(buf,63)=sd->status.font;
	strncpy(WBUFP(buf,65),sd->status.name,24);

	return WBUFW(buf,2);
#elif PACKETVER < 20131223
	WBUFW(buf,0)=0x915;
	WBUFW(buf,2)=74;
	WBUFB(buf,4)=0;
	WBUFL(buf,5)=sd->bl.id;
	WBUFW(buf,9)=sd->speed;
	WBUFW(buf,11)=sd->sc.opt1;
	WBUFW(buf,13)=sd->sc.opt2;
	WBUFL(buf,15)=sd->sc.option;
	WBUFW(buf,19)=sd->view_class;
	WBUFW(buf,21)=sd->status.hair;
	WBUFW(buf,23)=rhand;
	WBUFW(buf,25)=lhand;
	WBUFW(buf,27)=sd->status.head_bottom;
	WBUFW(buf,29)=sd->status.head_top;
	WBUFW(buf,31)=sd->status.head_mid;
	WBUFW(buf,33)=sd->status.hair_color;
	WBUFW(buf,35)=sd->status.clothes_color;
	WBUFW(buf,37)=sd->head_dir;
	WBUFW(buf,39)=sd->status.robe;
	WBUFL(buf,41)=sd->status.guild_id;
	WBUFW(buf,45)=sd->guild_emblem_id;
	WBUFW(buf,47)=sd->status.manner;
	WBUFL(buf,49)=sd->sc.opt3;
	WBUFB(buf,53)=(unsigned char)sd->status.karma;
	WBUFB(buf,54)=sd->sex;
	WBUFPOS(buf,55,sd->bl.x,sd->bl.y,sd->dir);
	WBUFB(buf,58)=5;
	WBUFB(buf,59)=5;
	WBUFB(buf,60)=sd->state.dead_sit;
	WBUFLV(buf,61,sd->status.base_level,sd->status.class_);
	WBUFW(buf,63)=sd->status.font;
	WBUFL(buf,65) = 0xffffffff;
	WBUFL(buf,69) = 0xffffffff;
	WBUFB(buf,73) = 0;

	return WBUFW(buf,2);
#elif PACKETVER < 20150513
	WBUFW(buf,0)=0x9dd;
	WBUFW(buf,2)=(unsigned short)(78 + strlen(sd->status.name));
	WBUFB(buf,4)=0;
	WBUFL(buf,5)=sd->bl.id;
	WBUFL(buf,9)=sd->char_id;
	WBUFW(buf,13)=sd->speed;
	WBUFW(buf,15)=sd->sc.opt1;
	WBUFW(buf,17)=sd->sc.opt2;
	WBUFL(buf,19)=sd->sc.option;
	WBUFW(buf,23)=sd->view_class;
	WBUFW(buf,25)=sd->status.hair;
	WBUFW(buf,27)=rhand;
	WBUFW(buf,29)=lhand;
	WBUFW(buf,31)=sd->status.head_bottom;
	WBUFW(buf,33)=sd->status.head_top;
	WBUFW(buf,35)=sd->status.head_mid;
	WBUFW(buf,37)=sd->status.hair_color;
	WBUFW(buf,39)=sd->status.clothes_color;
	WBUFW(buf,41)=sd->head_dir;
	WBUFW(buf,43)=sd->status.robe;
	WBUFL(buf,45)=sd->status.guild_id;
	WBUFW(buf,49)=sd->guild_emblem_id;
	WBUFW(buf,51)=sd->status.manner;
	WBUFL(buf,53)=sd->sc.opt3;
	WBUFB(buf,57)=(unsigned char)sd->status.karma;
	WBUFB(buf,58)=sd->sex;
	WBUFPOS(buf,59,sd->bl.x,sd->bl.y,sd->dir);
	WBUFB(buf,62)=5;
	WBUFB(buf,63)=5;
	WBUFB(buf,64)=sd->state.dead_sit;
	WBUFLV(buf,65,sd->status.base_level,sd->status.class_);
	WBUFW(buf,67)=sd->status.font;
	WBUFL(buf,69) = 0xffffffff;
	WBUFL(buf,73) = 0xffffffff;
	WBUFB(buf,77) = 0;
	strncpy(WBUFP(buf,78),sd->status.name,24);

	return WBUFW(buf,2);
#elif PACKETVER < 20180704
	WBUFW(buf,0)=0x9ff;
	WBUFW(buf,2)=(unsigned short)(80 + strlen(sd->status.name));
	WBUFB(buf,4)=0;
	WBUFL(buf,5)=sd->bl.id;
	WBUFL(buf,9)=sd->char_id;
	WBUFW(buf,13)=sd->speed;
	WBUFW(buf,15)=sd->sc.opt1;
	WBUFW(buf,17)=sd->sc.opt2;
	WBUFL(buf,19)=sd->sc.option;
	WBUFW(buf,23)=sd->view_class;
	WBUFW(buf,25)=sd->status.hair;
	WBUFW(buf,27)=rhand;
	WBUFW(buf,29)=lhand;
	WBUFW(buf,31)=sd->status.head_bottom;
	WBUFW(buf,33)=sd->status.head_top;
	WBUFW(buf,35)=sd->status.head_mid;
	WBUFW(buf,37)=sd->status.hair_color;
	WBUFW(buf,39)=sd->status.clothes_color;
	WBUFW(buf,41)=sd->head_dir;
	WBUFW(buf,43)=sd->status.robe;
	WBUFL(buf,45)=sd->status.guild_id;
	WBUFW(buf,49)=sd->guild_emblem_id;
	WBUFW(buf,51)=sd->status.manner;
	WBUFL(buf,53)=sd->sc.opt3;
	WBUFB(buf,57)=(unsigned char)sd->status.karma;
	WBUFB(buf,58)=sd->sex;
	WBUFPOS(buf,59,sd->bl.x,sd->bl.y,sd->dir);
	WBUFB(buf,62)=5;
	WBUFB(buf,63)=5;
	WBUFB(buf,64)=sd->state.dead_sit;
	WBUFLV(buf,65,sd->status.base_level,sd->status.class_);
	WBUFW(buf,67)=sd->status.font;
	WBUFL(buf,69) = 0xffffffff;
	WBUFL(buf,73) = 0xffffffff;
	WBUFB(buf,77) = 0;
	WBUFW(buf,78) = sd->status.style;
	strncpy(WBUFP(buf,80),sd->status.name,24);

	return WBUFW(buf,2);
#else
	WBUFW(buf,0)=0x9ff;
	WBUFW(buf,2)=(unsigned short)(84 + strlen(sd->status.name));
	WBUFB(buf,4)=0;
	WBUFL(buf,5)=sd->bl.id;
	WBUFL(buf,9)=sd->char_id;
	WBUFW(buf,13)=sd->speed;
	WBUFW(buf,15)=sd->sc.opt1;
	WBUFW(buf,17)=sd->sc.opt2;
	WBUFL(buf,19)=sd->sc.option;
	WBUFW(buf,23)=sd->view_class;
	WBUFW(buf,25)=sd->status.hair;
	WBUFL(buf,27)=rhand;
	WBUFL(buf,31)=lhand;
	WBUFW(buf,35)=sd->status.head_bottom;
	WBUFW(buf,37)=sd->status.head_top;
	WBUFW(buf,39)=sd->status.head_mid;
	WBUFW(buf,41)=sd->status.hair_color;
	WBUFW(buf,43)=sd->status.clothes_color;
	WBUFW(buf,45)=sd->head_dir;
	WBUFW(buf,47)=sd->status.robe;
	WBUFL(buf,49)=sd->status.guild_id;
	WBUFW(buf,53)=sd->guild_emblem_id;
	WBUFW(buf,55)=sd->status.manner;
	WBUFL(buf,57)=sd->sc.opt3;
	WBUFB(buf,61)=(unsigned char)sd->status.karma;
	WBUFB(buf,62)=sd->sex;
	WBUFPOS(buf,63,sd->bl.x,sd->bl.y,sd->dir);
	WBUFB(buf,66)=5;
	WBUFB(buf,67)=5;
	WBUFB(buf,68)=sd->state.dead_sit;
	WBUFLV(buf,69,sd->status.base_level,sd->status.class_);
	WBUFW(buf,71)=sd->status.font;
	WBUFL(buf,73) = 0xffffffff;
	WBUFL(buf,77) = 0xffffffff;
	WBUFB(buf,81) = 0;
	WBUFW(buf,82) = sd->status.style;
	strncpy(WBUFP(buf,84),sd->status.name,24);

	return WBUFW(buf,2);
#endif
}

/*==========================================
 *
 *------------------------------------------
 */
static int clif_set007b(struct map_session_data *sd,unsigned char *buf)
{
	int rhand = 0, lhand = 0;
	unsigned int tick = gettick();

	nullpo_retr(0, sd);

	clif_get_weapon_view(sd, &rhand, &lhand);

#if PACKETVER < 4
	WBUFW(buf,0)=0x7b;
	WBUFL(buf,2)=sd->bl.id;
	WBUFW(buf,6)=sd->speed;
	WBUFW(buf,8)=sd->sc.opt1;
	WBUFW(buf,10)=sd->sc.opt2;
	WBUFW(buf,12)=sd->sc.option;
	WBUFW(buf,14)=sd->view_class;
	WBUFW(buf,16)=sd->status.hair;
	WBUFW(buf,18)=rhand;
	WBUFW(buf,20)=sd->status.head_bottom;
	WBUFL(buf,22)=tick;
	WBUFW(buf,26)=lhand;
	WBUFW(buf,28)=sd->status.head_top;
	WBUFW(buf,30)=sd->status.head_mid;
	WBUFW(buf,32)=sd->status.hair_color;
	WBUFW(buf,34)=sd->status.clothes_color;
	WBUFW(buf,36)=sd->head_dir;
	WBUFL(buf,38)=sd->status.guild_id;
	WBUFL(buf,42)=sd->guild_emblem_id;
	WBUFW(buf,46)=sd->status.manner;
	WBUFB(buf,48)=(unsigned char)sd->status.karma;
	WBUFB(buf,49)=sd->sex;
	WBUFPOS2(buf,50,sd->bl.x,sd->bl.y,sd->ud.to_x,sd->ud.to_y,8,8);
	WBUFB(buf,56)=5;
	WBUFB(buf,57)=5;
	WBUFLV(buf,58,sd->status.base_level,sd->status.class_);

	return packet_db[0x7b].len;
#elif PACKETVER < 7
	WBUFW(buf,0)=0x1da;
	WBUFL(buf,2)=sd->bl.id;
	WBUFW(buf,6)=sd->speed;
	WBUFW(buf,8)=sd->sc.opt1;
	WBUFW(buf,10)=sd->sc.opt2;
	WBUFW(buf,12)=sd->sc.option;
	WBUFW(buf,14)=sd->view_class;
	WBUFW(buf,16)=sd->status.hair;
	WBUFW(buf,18)=rhand;
	WBUFW(buf,20)=lhand;
	WBUFW(buf,22)=sd->status.head_bottom;
	WBUFL(buf,24)=tick;
	WBUFW(buf,28)=sd->status.head_top;
	WBUFW(buf,30)=sd->status.head_mid;
	WBUFW(buf,32)=sd->status.hair_color;
	WBUFW(buf,34)=sd->status.clothes_color;
	WBUFW(buf,36)=sd->head_dir;
	WBUFL(buf,38)=sd->status.guild_id;
	WBUFW(buf,42)=sd->guild_emblem_id;
	WBUFW(buf,44)=sd->status.manner;
	WBUFW(buf,46)=sd->sc.opt3;
	WBUFB(buf,48)=(unsigned char)sd->status.karma;
	WBUFB(buf,49)=sd->sex;
	WBUFPOS2(buf,50,sd->bl.x,sd->bl.y,sd->ud.to_x,sd->ud.to_y,8,8);
	WBUFB(buf,56)=5;
	WBUFB(buf,57)=5;
	WBUFLV(buf,58,sd->status.base_level,sd->status.class_);

	return packet_db[0x1da].len;
#elif PACKETVER < 20071106
	WBUFW(buf,0)=0x22c;
	WBUFL(buf,2)=sd->bl.id;
	WBUFW(buf,6)=sd->speed;
	WBUFW(buf,8)=sd->sc.opt1;
	WBUFW(buf,10)=sd->sc.opt2;
	WBUFL(buf,12)=sd->sc.option;
	WBUFW(buf,16)=sd->view_class;
	WBUFW(buf,18)=sd->status.hair;
	WBUFW(buf,20)=rhand;
	WBUFW(buf,22)=lhand;
	WBUFW(buf,24)=sd->status.head_bottom;
	WBUFL(buf,26)=tick;
	WBUFW(buf,30)=sd->status.head_top;
	WBUFW(buf,32)=sd->status.head_mid;
	WBUFW(buf,34)=sd->status.hair_color;
	WBUFW(buf,36)=sd->status.clothes_color;
	WBUFW(buf,38)=sd->head_dir;
	WBUFL(buf,40)=sd->status.guild_id;
	WBUFW(buf,44)=sd->guild_emblem_id;
	WBUFW(buf,46)=sd->status.manner;
	WBUFL(buf,48)=sd->sc.opt3;
	WBUFB(buf,52)=(unsigned char)sd->status.karma;
	WBUFB(buf,53)=sd->sex;
	WBUFPOS2(buf,54,sd->bl.x,sd->bl.y,sd->ud.to_x,sd->ud.to_y,8,8);
	WBUFB(buf,60)=0;
	WBUFB(buf,61)=0;
	WBUFLV(buf,62,sd->status.base_level,sd->status.class_);

	return packet_db[0x22c].len;
#elif PACKETVER < 20080102
	WBUFW(buf,0)=0x22c;
	WBUFB(buf,2)=0;
	WBUFL(buf,3)=sd->bl.id;
	WBUFW(buf,7)=sd->speed;
	WBUFW(buf,9)=sd->sc.opt1;
	WBUFW(buf,11)=sd->sc.opt2;
	WBUFL(buf,13)=sd->sc.option;
	WBUFW(buf,17)=sd->view_class;
	WBUFW(buf,19)=sd->status.hair;
	WBUFW(buf,21)=rhand;
	WBUFW(buf,23)=lhand;
	WBUFW(buf,25)=sd->status.head_bottom;
	WBUFL(buf,27)=tick;
	WBUFW(buf,31)=sd->status.head_top;
	WBUFW(buf,33)=sd->status.head_mid;
	WBUFW(buf,35)=sd->status.hair_color;
	WBUFW(buf,37)=sd->status.clothes_color;
	WBUFW(buf,39)=sd->head_dir;
	WBUFL(buf,41)=sd->status.guild_id;
	WBUFW(buf,45)=sd->guild_emblem_id;
	WBUFW(buf,47)=sd->status.manner;
	WBUFL(buf,49)=sd->sc.opt3;
	WBUFB(buf,53)=(unsigned char)sd->status.karma;
	WBUFB(buf,54)=sd->sex;
	WBUFPOS2(buf,55,sd->bl.x,sd->bl.y,sd->ud.to_x,sd->ud.to_y,8,8);
	WBUFB(buf,61)=0;
	WBUFB(buf,62)=0;
	WBUFLV(buf,63,sd->status.base_level,sd->status.class_);

	return packet_db[0x22c].len;
#elif PACKETVER < 20091104
	WBUFW(buf,0)=0x2ec;
	WBUFB(buf,2)=0;
	WBUFL(buf,3)=sd->bl.id;
	WBUFW(buf,7)=sd->speed;
	WBUFW(buf,9)=sd->sc.opt1;
	WBUFW(buf,11)=sd->sc.opt2;
	WBUFL(buf,13)=sd->sc.option;
	WBUFW(buf,17)=sd->view_class;
	WBUFW(buf,19)=sd->status.hair;
	WBUFW(buf,21)=rhand;
	WBUFW(buf,23)=lhand;
	WBUFW(buf,25)=sd->status.head_bottom;
	WBUFL(buf,27)=tick;
	WBUFW(buf,31)=sd->status.head_top;
	WBUFW(buf,33)=sd->status.head_mid;
	WBUFW(buf,35)=sd->status.hair_color;
	WBUFW(buf,37)=sd->status.clothes_color;
	WBUFW(buf,39)=sd->head_dir;
	WBUFL(buf,41)=sd->status.guild_id;
	WBUFW(buf,45)=sd->guild_emblem_id;
	WBUFW(buf,47)=sd->status.manner;
	WBUFL(buf,49)=sd->sc.opt3;
	WBUFB(buf,53)=(unsigned char)sd->status.karma;
	WBUFB(buf,54)=sd->sex;
	WBUFPOS2(buf,55,sd->bl.x,sd->bl.y,sd->ud.to_x,sd->ud.to_y,8,8);
	WBUFB(buf,61)=0;
	WBUFB(buf,62)=0;
	WBUFLV(buf,63,sd->status.base_level,sd->status.class_);
	WBUFW(buf,65)=sd->status.font;

	return packet_db[0x2ec].len;
#elif PACKETVER < 20110111
	WBUFW(buf,0)=0x7f7;
	WBUFW(buf,2)=(unsigned short)(69 + strlen(sd->status.name));
	WBUFB(buf,4)=0;
	WBUFL(buf,5)=sd->bl.id;
	WBUFW(buf,9)=sd->speed;
	WBUFW(buf,11)=sd->sc.opt1;
	WBUFW(buf,13)=sd->sc.opt2;
	WBUFL(buf,15)=sd->sc.option;
	WBUFW(buf,19)=sd->view_class;
	WBUFW(buf,21)=sd->status.hair;
	WBUFW(buf,23)=rhand;
	WBUFW(buf,25)=lhand;
	WBUFW(buf,27)=sd->status.head_bottom;
	WBUFL(buf,29)=tick;
	WBUFW(buf,33)=sd->status.head_top;
	WBUFW(buf,35)=sd->status.head_mid;
	WBUFW(buf,37)=sd->status.hair_color;
	WBUFW(buf,39)=sd->status.clothes_color;
	WBUFW(buf,41)=sd->head_dir;
	WBUFL(buf,43)=sd->status.guild_id;
	WBUFW(buf,47)=sd->guild_emblem_id;
	WBUFW(buf,49)=sd->status.manner;
	WBUFL(buf,51)=sd->sc.opt3;
	WBUFB(buf,55)=(unsigned char)sd->status.karma;
	WBUFB(buf,56)=sd->sex;
	WBUFPOS2(buf,57,sd->bl.x,sd->bl.y,sd->ud.to_x,sd->ud.to_y,8,8);
	WBUFB(buf,63)=5;
	WBUFB(buf,64)=5;
	WBUFLV(buf,65,sd->status.base_level,sd->status.class_);
	WBUFW(buf,67)=sd->status.font;
	strncpy(WBUFP(buf,69),sd->status.name,24);

	return WBUFW(buf,2);
#elif PACKETVER < 20120328
	WBUFW(buf,0)=0x856;
	WBUFW(buf,2)=(unsigned short)(71 + strlen(sd->status.name));
	WBUFB(buf,4)=0;
	WBUFL(buf,5)=sd->bl.id;
	WBUFW(buf,9)=sd->speed;
	WBUFW(buf,11)=sd->sc.opt1;
	WBUFW(buf,13)=sd->sc.opt2;
	WBUFL(buf,15)=sd->sc.option;
	WBUFW(buf,19)=sd->view_class;
	WBUFW(buf,21)=sd->status.hair;
	WBUFW(buf,23)=rhand;
	WBUFW(buf,25)=lhand;
	WBUFW(buf,27)=sd->status.head_bottom;
	WBUFL(buf,29)=tick;
	WBUFW(buf,33)=sd->status.head_top;
	WBUFW(buf,35)=sd->status.head_mid;
	WBUFW(buf,37)=sd->status.hair_color;
	WBUFW(buf,39)=sd->status.clothes_color;
	WBUFW(buf,41)=sd->head_dir;
	WBUFW(buf,43)=sd->status.robe;
	WBUFL(buf,45)=sd->status.guild_id;
	WBUFW(buf,49)=sd->guild_emblem_id;
	WBUFW(buf,51)=sd->status.manner;
	WBUFL(buf,53)=sd->sc.opt3;
	WBUFB(buf,57)=(unsigned char)sd->status.karma;
	WBUFB(buf,58)=sd->sex;
	WBUFPOS2(buf,59,sd->bl.x,sd->bl.y,sd->ud.to_x,sd->ud.to_y,8,8);
	WBUFB(buf,65)=5;
	WBUFB(buf,66)=5;
	WBUFLV(buf,67,sd->status.base_level,sd->status.class_);
	WBUFW(buf,69)=sd->status.font;
	strncpy(WBUFP(buf,71),sd->status.name,24);

	return WBUFW(buf,2);
#elif PACKETVER < 20131223
	WBUFW(buf,0)=0x914;
	WBUFW(buf,2)=80;
	WBUFB(buf,4)=0;
	WBUFL(buf,5)=sd->bl.id;
	WBUFW(buf,9)=sd->speed;
	WBUFW(buf,11)=sd->sc.opt1;
	WBUFW(buf,13)=sd->sc.opt2;
	WBUFL(buf,15)=sd->sc.option;
	WBUFW(buf,19)=sd->view_class;
	WBUFW(buf,21)=sd->status.hair;
	WBUFW(buf,23)=rhand;
	WBUFW(buf,25)=lhand;
	WBUFW(buf,27)=sd->status.head_bottom;
	WBUFL(buf,29)=tick;
	WBUFW(buf,33)=sd->status.head_top;
	WBUFW(buf,35)=sd->status.head_mid;
	WBUFW(buf,37)=sd->status.hair_color;
	WBUFW(buf,39)=sd->status.clothes_color;
	WBUFW(buf,41)=sd->head_dir;
	WBUFW(buf,43)=sd->status.robe;
	WBUFL(buf,45)=sd->status.guild_id;
	WBUFW(buf,49)=sd->guild_emblem_id;
	WBUFW(buf,51)=sd->status.manner;
	WBUFL(buf,53)=sd->sc.opt3;
	WBUFB(buf,57)=(unsigned char)sd->status.karma;
	WBUFB(buf,58)=sd->sex;
	WBUFPOS2(buf,59,sd->bl.x,sd->bl.y,sd->ud.to_x,sd->ud.to_y,8,8);
	WBUFB(buf,65)=5;
	WBUFB(buf,66)=5;
	WBUFLV(buf,67,sd->status.base_level,sd->status.class_);
	WBUFW(buf,69)=sd->status.font;
	WBUFL(buf,71)=0xffffffff;
	WBUFL(buf,75)=0xffffffff;
	WBUFB(buf,79)=0;

	return WBUFW(buf,2);
#elif PACKETVER < 20150513
	WBUFW(buf,0)=0x9db;
	WBUFW(buf,2)=(unsigned short)(84 + strlen(sd->status.name));
	WBUFB(buf,4)=0;
	WBUFL(buf,5)=sd->bl.id;
	WBUFL(buf,9)=sd->char_id;
	WBUFW(buf,13)=sd->speed;
	WBUFW(buf,15)=sd->sc.opt1;
	WBUFW(buf,17)=sd->sc.opt2;
	WBUFL(buf,19)=sd->sc.option;
	WBUFW(buf,23)=sd->view_class;
	WBUFW(buf,25)=sd->status.hair;
	WBUFW(buf,27)=rhand;
	WBUFW(buf,29)=lhand;
	WBUFW(buf,31)=sd->status.head_bottom;
	WBUFL(buf,33)=tick;
	WBUFW(buf,37)=sd->status.head_top;
	WBUFW(buf,39)=sd->status.head_mid;
	WBUFW(buf,41)=sd->status.hair_color;
	WBUFW(buf,43)=sd->status.clothes_color;
	WBUFW(buf,45)=sd->head_dir;
	WBUFW(buf,47)=sd->status.robe;
	WBUFL(buf,49)=sd->status.guild_id;
	WBUFW(buf,53)=sd->guild_emblem_id;
	WBUFW(buf,55)=sd->status.manner;
	WBUFL(buf,57)=sd->sc.opt3;
	WBUFB(buf,61)=(unsigned char)sd->status.karma;
	WBUFB(buf,62)=sd->sex;
	WBUFPOS2(buf,63,sd->bl.x,sd->bl.y,sd->ud.to_x,sd->ud.to_y,8,8);
	WBUFB(buf,69)=5;
	WBUFB(buf,70)=5;
	WBUFLV(buf,71,sd->status.base_level,sd->status.class_);
	WBUFW(buf,73)=sd->status.font;
	WBUFL(buf,75)=0xffffffff;
	WBUFL(buf,79)=0xffffffff;
	WBUFB(buf,83)=0;
	strncpy(WBUFP(buf,84),sd->status.name,24);

	return WBUFW(buf,2);
#elif PACKETVER < 20180704
	WBUFW(buf,0)=0x9fd;
	WBUFW(buf,2)=(unsigned short)(86 + strlen(sd->status.name));
	WBUFB(buf,4)=0;
	WBUFL(buf,5)=sd->bl.id;
	WBUFL(buf,9)=sd->char_id;
	WBUFW(buf,13)=sd->speed;
	WBUFW(buf,15)=sd->sc.opt1;
	WBUFW(buf,17)=sd->sc.opt2;
	WBUFL(buf,19)=sd->sc.option;
	WBUFW(buf,23)=sd->view_class;
	WBUFW(buf,25)=sd->status.hair;
	WBUFW(buf,27)=rhand;
	WBUFW(buf,29)=lhand;
	WBUFW(buf,31)=sd->status.head_bottom;
	WBUFL(buf,33)=tick;
	WBUFW(buf,37)=sd->status.head_top;
	WBUFW(buf,39)=sd->status.head_mid;
	WBUFW(buf,41)=sd->status.hair_color;
	WBUFW(buf,43)=sd->status.clothes_color;
	WBUFW(buf,45)=sd->head_dir;
	WBUFW(buf,47)=sd->status.robe;
	WBUFL(buf,49)=sd->status.guild_id;
	WBUFW(buf,53)=sd->guild_emblem_id;
	WBUFW(buf,55)=sd->status.manner;
	WBUFL(buf,57)=sd->sc.opt3;
	WBUFB(buf,61)=(unsigned char)sd->status.karma;
	WBUFB(buf,62)=sd->sex;
	WBUFPOS2(buf,63,sd->bl.x,sd->bl.y,sd->ud.to_x,sd->ud.to_y,8,8);
	WBUFB(buf,69)=5;
	WBUFB(buf,70)=5;
	WBUFLV(buf,71,sd->status.base_level,sd->status.class_);
	WBUFW(buf,73)=sd->status.font;
	WBUFL(buf,75)=0xffffffff;
	WBUFL(buf,79)=0xffffffff;
	WBUFB(buf,83)=0;
	WBUFW(buf,84)=sd->status.style;
	strncpy(WBUFP(buf,86),sd->status.name,24);

	return WBUFW(buf,2);
#else
	WBUFW(buf,0)=0x9fd;
	WBUFW(buf,2)=(unsigned short)(90 + strlen(sd->status.name));
	WBUFB(buf,4)=0;
	WBUFL(buf,5)=sd->bl.id;
	WBUFL(buf,9)=sd->char_id;
	WBUFW(buf,13)=sd->speed;
	WBUFW(buf,15)=sd->sc.opt1;
	WBUFW(buf,17)=sd->sc.opt2;
	WBUFL(buf,19)=sd->sc.option;
	WBUFW(buf,23)=sd->view_class;
	WBUFW(buf,25)=sd->status.hair;
	WBUFL(buf,27)=rhand;
	WBUFL(buf,31)=lhand;
	WBUFW(buf,35)=sd->status.head_bottom;
	WBUFL(buf,37)=tick;
	WBUFW(buf,41)=sd->status.head_top;
	WBUFW(buf,43)=sd->status.head_mid;
	WBUFW(buf,45)=sd->status.hair_color;
	WBUFW(buf,47)=sd->status.clothes_color;
	WBUFW(buf,49)=sd->head_dir;
	WBUFW(buf,51)=sd->status.robe;
	WBUFL(buf,53)=sd->status.guild_id;
	WBUFW(buf,57)=sd->guild_emblem_id;
	WBUFW(buf,59)=sd->status.manner;
	WBUFL(buf,61)=sd->sc.opt3;
	WBUFB(buf,65)=(unsigned char)sd->status.karma;
	WBUFB(buf,66)=sd->sex;
	WBUFPOS2(buf,67,sd->bl.x,sd->bl.y,sd->ud.to_x,sd->ud.to_y,8,8);
	WBUFB(buf,73)=5;
	WBUFB(buf,74)=5;
	WBUFLV(buf,75,sd->status.base_level,sd->status.class_);
	WBUFW(buf,77)=sd->status.font;
	WBUFL(buf,79)=0xffffffff;
	WBUFL(buf,83)=0xffffffff;
	WBUFB(buf,87)=0;
	WBUFW(buf,88)=sd->status.style;
	strncpy(WBUFP(buf,90),sd->status.name,24);

	return WBUFW(buf,2);
#endif
}

/*==========================================
 * �N���X�`�F���W type��Mob�̏ꍇ��1�ő���0�H
 *------------------------------------------
 */
void clif_class_change(struct block_list *bl,int class_,int type)
{
	unsigned char buf[16];

	nullpo_retv(bl);

	if(class_ >= PC_JOB_MAX) {
		WBUFW(buf,0)=0x1b0;
		WBUFL(buf,2)=bl->id;
		WBUFB(buf,6)=type;
		WBUFL(buf,7)=class_;
		clif_send(buf,packet_db[0x1b0].len,bl,AREA);
	}

	return;
}

/*==========================================
 * MOB�\��1
 *------------------------------------------
 */
static int clif_mob0078(struct mob_data *md,unsigned char *buf)
{
	int len;

	nullpo_retr(0, md);

	if(mob_is_pcview(md->class_)) {
#if PACKETVER < 4
		len = packet_db[0x78].len;
		memset(buf,0,len);

		WBUFW(buf,0)=0x78;
		WBUFL(buf,2)=md->bl.id;
		WBUFW(buf,6)=status_get_speed(&md->bl);
		WBUFW(buf,8)=md->sc.opt1;
		WBUFW(buf,10)=md->sc.opt2;
		WBUFW(buf,12)=md->sc.option;
		WBUFW(buf,14)=mob_get_viewclass(md->class_);
		WBUFW(buf,16)=mob_get_hair(md->class_);
		WBUFW(buf,18)=mob_get_weapon(md->class_);
		WBUFW(buf,20)=mob_get_head_bottom(md->class_);
		WBUFW(buf,22)=mob_get_shield(md->class_);
		WBUFW(buf,24)=mob_get_head_top(md->class_);
		WBUFW(buf,26)=mob_get_head_mid(md->class_);
		WBUFW(buf,28)=mob_get_hair_color(md->class_);
		WBUFW(buf,30)=mob_get_clothes_color(md->class_);
		if(md->guild_id){
			struct guild *g=guild_search(md->guild_id);
			if(g)
				WBUFL(buf,38)=g->emblem_id;
			WBUFL(buf,34)=md->guild_id;
		}
		WBUFW(buf,42)=md->sc.opt3;
		WBUFB(buf,44)=1;
		WBUFB(buf,45)=mob_get_sex(md->class_);
		WBUFPOS(buf,46,md->bl.x,md->bl.y,md->dir);
		WBUFB(buf,49)=5;
		WBUFB(buf,50)=5;
		WBUFLV(buf,52,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
#elif PACKETVER < 7
		len = packet_db[0x1d8].len;
		memset(buf,0,packet_db[0x1d8].len);

		WBUFW(buf,0)=0x1d8;
		WBUFL(buf,2)=md->bl.id;
		WBUFW(buf,6)=status_get_speed(&md->bl);
		WBUFW(buf,8)=md->sc.opt1;
		WBUFW(buf,10)=md->sc.opt2;
		WBUFW(buf,12)=md->sc.option;
		WBUFW(buf,14)=mob_get_viewclass(md->class_);
		WBUFW(buf,16)=mob_get_hair(md->class_);
		WBUFW(buf,18)=mob_get_weapon(md->class_);
		WBUFW(buf,20)=mob_get_shield(md->class_);
		WBUFW(buf,22)=mob_get_head_bottom(md->class_);
		WBUFW(buf,24)=mob_get_head_top(md->class_);
		WBUFW(buf,26)=mob_get_head_mid(md->class_);
		WBUFW(buf,28)=mob_get_hair_color(md->class_);
		WBUFW(buf,30)=mob_get_clothes_color(md->class_);
		if(md->guild_id){
			struct guild *g=guild_search(md->guild_id);
			if(g)
				WBUFL(buf,38)=g->emblem_id;
			WBUFL(buf,34)=md->guild_id;
		}
		WBUFW(buf,42)=md->sc.opt3;
		WBUFB(buf,44)=1;
		WBUFB(buf,45)=mob_get_sex(md->class_);
		WBUFPOS(buf,46,md->bl.x,md->bl.y,md->dir);
		WBUFB(buf,49)=5;
		WBUFB(buf,50)=5;
		WBUFLV(buf,52,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
#elif PACKETVER < 20080102
		len = packet_db[0x22a].len;
		memset(buf,0,len);

		WBUFW(buf,0)=0x22a;
		WBUFL(buf,2)=md->bl.id;
		WBUFW(buf,6)=status_get_speed(&md->bl);
		WBUFW(buf,8)=md->sc.opt1;
		WBUFW(buf,10)=md->sc.opt2;
		WBUFL(buf,12)=md->sc.option;
		WBUFW(buf,16)=mob_get_viewclass(md->class_);
		WBUFW(buf,18)=mob_get_hair(md->class_);
		WBUFW(buf,20)=mob_get_weapon(md->class_);
		WBUFW(buf,22)=mob_get_shield(md->class_);
		WBUFW(buf,24)=mob_get_head_bottom(md->class_);
		WBUFW(buf,26)=mob_get_head_top(md->class_);
		WBUFW(buf,28)=mob_get_head_mid(md->class_);
		WBUFW(buf,30)=mob_get_hair_color(md->class_);
		WBUFW(buf,32)=mob_get_clothes_color(md->class_);
		if(md->guild_id){
			struct guild *g=guild_search(md->guild_id);
			if(g)
				WBUFW(buf,40)=g->emblem_id;
			WBUFL(buf,36)=md->guild_id;
		}
		WBUFL(buf,44)=md->sc.opt3;
		WBUFB(buf,48)=1;
		WBUFB(buf,49)=mob_get_sex(md->class_);
		WBUFPOS(buf,50,md->bl.x,md->bl.y,md->dir);
		WBUFB(buf,53)=5;
		WBUFB(buf,54)=5;
		WBUFLV(buf,56,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
#elif PACKETVER < 20091104
		len = packet_db[0x2ee].len;
		memset(buf,0,len);

		WBUFW(buf,0)=0x2ee;
		WBUFL(buf,2)=md->bl.id;
		WBUFW(buf,6)=status_get_speed(&md->bl);
		WBUFW(buf,8)=md->sc.opt1;
		WBUFW(buf,10)=md->sc.opt2;
		WBUFL(buf,12)=md->sc.option;
		WBUFW(buf,16)=mob_get_viewclass(md->class_);
		WBUFW(buf,18)=mob_get_hair(md->class_);
		WBUFW(buf,20)=mob_get_weapon(md->class_);
		WBUFW(buf,22)=mob_get_shield(md->class_);
		WBUFW(buf,24)=mob_get_head_bottom(md->class_);
		WBUFW(buf,26)=mob_get_head_top(md->class_);
		WBUFW(buf,28)=mob_get_head_mid(md->class_);
		WBUFW(buf,30)=mob_get_hair_color(md->class_);
		WBUFW(buf,32)=mob_get_clothes_color(md->class_);
		if(md->guild_id){
			struct guild *g=guild_search(md->guild_id);
			if(g)
				WBUFW(buf,40)=g->emblem_id;
			WBUFL(buf,36)=md->guild_id;
		}
		WBUFL(buf,44)=md->sc.opt3;
		WBUFB(buf,48)=1;
		WBUFB(buf,49)=mob_get_sex(md->class_);
		WBUFPOS(buf,50,md->bl.x,md->bl.y,md->dir);
		WBUFB(buf,53)=5;
		WBUFB(buf,54)=5;
		WBUFLV(buf,56,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
		WBUFW(buf,58)=0;
#elif PACKETVER < 20110111
		len = 63 + (int)strlen(md->name);
		memset(buf,0,len);

		WBUFW(buf,0)=0x7f9;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=0;
		WBUFL(buf,5)=md->bl.id;
		WBUFW(buf,9)=status_get_speed(&md->bl);
		WBUFW(buf,11)=md->sc.opt1;
		WBUFW(buf,13)=md->sc.opt2;
		WBUFL(buf,15)=md->sc.option;
		WBUFW(buf,19)=mob_get_viewclass(md->class_);
		WBUFW(buf,21)=mob_get_hair(md->class_);
		WBUFW(buf,23)=mob_get_weapon(md->class_);
		WBUFW(buf,25)=mob_get_shield(md->class_);
		WBUFW(buf,27)=mob_get_head_bottom(md->class_);
		WBUFW(buf,29)=mob_get_head_top(md->class_);
		WBUFW(buf,31)=mob_get_head_mid(md->class_);
		WBUFW(buf,33)=mob_get_hair_color(md->class_);
		WBUFW(buf,35)=mob_get_clothes_color(md->class_);
		if(md->guild_id){
			struct guild *g=guild_search(md->guild_id);
			if(g)
				WBUFW(buf,43)=g->emblem_id;
			WBUFL(buf,39)=md->guild_id;
		}
		WBUFL(buf,47)=md->sc.opt3;
		WBUFB(buf,51)=1;
		WBUFB(buf,52)=mob_get_sex(md->class_);
		WBUFPOS(buf,53,md->bl.x,md->bl.y,md->dir);
		WBUFB(buf,56)=5;
		WBUFB(buf,57)=5;
		WBUFLV(buf,59,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
		strncpy(WBUFP(buf,63),md->name,24);
#elif PACKETVER < 20120328
		len = 65 + (int)strlen(md->name);
		memset(buf,0,len);

		WBUFW(buf,0)=0x857;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=0;
		WBUFL(buf,5)=md->bl.id;
		WBUFW(buf,9)=status_get_speed(&md->bl);
		WBUFW(buf,11)=md->sc.opt1;
		WBUFW(buf,13)=md->sc.opt2;
		WBUFL(buf,15)=md->sc.option;
		WBUFW(buf,19)=mob_get_viewclass(md->class_);
		WBUFW(buf,21)=mob_get_hair(md->class_);
		WBUFW(buf,23)=mob_get_weapon(md->class_);
		WBUFW(buf,25)=mob_get_shield(md->class_);
		WBUFW(buf,27)=mob_get_head_bottom(md->class_);
		WBUFW(buf,29)=mob_get_head_top(md->class_);
		WBUFW(buf,31)=mob_get_head_mid(md->class_);
		WBUFW(buf,33)=mob_get_hair_color(md->class_);
		WBUFW(buf,35)=mob_get_clothes_color(md->class_);
		WBUFW(buf,39)=mob_get_robe(md->class_);
		if(md->guild_id){
			struct guild *g=guild_search(md->guild_id);
			if(g)
				WBUFW(buf,45)=g->emblem_id;
			WBUFL(buf,41)=md->guild_id;
		}
		WBUFL(buf,49)=md->sc.opt3;
		WBUFB(buf,53)=1;
		WBUFB(buf,54)=mob_get_sex(md->class_);
		WBUFPOS(buf,55,md->bl.x,md->bl.y,md->dir);
		WBUFB(buf,58)=5;
		WBUFB(buf,59)=5;
		WBUFLV(buf,61,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
		strncpy(WBUFP(buf,65),md->name,24);
#elif PACKETVER < 20131223
		len = 74;
		memset(buf,0,len);

		WBUFW(buf,0)=0x915;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=0;
		WBUFL(buf,5)=md->bl.id;
		WBUFW(buf,9)=status_get_speed(&md->bl);
		WBUFW(buf,11)=md->sc.opt1;
		WBUFW(buf,13)=md->sc.opt2;
		WBUFL(buf,15)=md->sc.option;
		WBUFW(buf,19)=mob_get_viewclass(md->class_);
		WBUFW(buf,21)=mob_get_hair(md->class_);
		WBUFW(buf,23)=mob_get_weapon(md->class_);
		WBUFW(buf,25)=mob_get_shield(md->class_);
		WBUFW(buf,27)=mob_get_head_bottom(md->class_);
		WBUFW(buf,29)=mob_get_head_top(md->class_);
		WBUFW(buf,31)=mob_get_head_mid(md->class_);
		WBUFW(buf,33)=mob_get_hair_color(md->class_);
		WBUFW(buf,35)=mob_get_clothes_color(md->class_);
		WBUFW(buf,39)=mob_get_robe(md->class_);
		if(md->guild_id){
			struct guild *g=guild_search(md->guild_id);
			if(g)
				WBUFW(buf,45)=g->emblem_id;
			WBUFL(buf,41)=md->guild_id;
		}
		WBUFL(buf,49)=md->sc.opt3;
		WBUFB(buf,53)=1;
		WBUFB(buf,54)=mob_get_sex(md->class_);
		WBUFPOS(buf,55,md->bl.x,md->bl.y,md->dir);
		WBUFB(buf,58)=5;
		WBUFB(buf,59)=5;
		WBUFLV(buf,61,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
		WBUFL(buf,65) = 0xffffffff;
		WBUFL(buf,69) = 0xffffffff;
		WBUFB(buf,73) = 0;
#elif PACKETVER < 20150513
		len = 78 + (int)strlen(md->name);
		memset(buf,0,len);

		WBUFW(buf,0)=0x9dd;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=0;
		WBUFL(buf,5)=md->bl.id;
		WBUFL(buf,9)=0;
		WBUFW(buf,13)=status_get_speed(&md->bl);
		WBUFW(buf,15)=md->sc.opt1;
		WBUFW(buf,17)=md->sc.opt2;
		WBUFL(buf,19)=md->sc.option;
		WBUFW(buf,23)=mob_get_viewclass(md->class_);
		WBUFW(buf,25)=mob_get_hair(md->class_);
		WBUFW(buf,27)=mob_get_weapon(md->class_);
		WBUFW(buf,29)=mob_get_shield(md->class_);
		WBUFW(buf,31)=mob_get_head_bottom(md->class_);
		WBUFW(buf,33)=mob_get_head_top(md->class_);
		WBUFW(buf,35)=mob_get_head_mid(md->class_);
		WBUFW(buf,37)=mob_get_hair_color(md->class_);
		WBUFW(buf,39)=mob_get_clothes_color(md->class_);
		WBUFW(buf,43)=mob_get_robe(md->class_);
		if(md->guild_id){
			struct guild *g=guild_search(md->guild_id);
			if(g)
				WBUFW(buf,49)=g->emblem_id;
			WBUFL(buf,45)=md->guild_id;
		}
		WBUFL(buf,53)=md->sc.opt3;
		WBUFB(buf,57)=1;
		WBUFB(buf,58)=mob_get_sex(md->class_);
		WBUFPOS(buf,59,md->bl.x,md->bl.y,md->dir);
		WBUFB(buf,62)=5;
		WBUFB(buf,63)=5;
		WBUFLV(buf,65,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
		WBUFL(buf,69) = 0xffffffff;
		WBUFL(buf,73) = 0xffffffff;
		WBUFB(buf,77) = 0;
#elif PACKETVER < 20180704
		len = 80 + (int)strlen(md->name);
		memset(buf,0,len);

		WBUFW(buf,0)=0x9ff;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=0;
		WBUFL(buf,5)=md->bl.id;
		WBUFL(buf,9)=0;
		WBUFW(buf,13)=status_get_speed(&md->bl);
		WBUFW(buf,15)=md->sc.opt1;
		WBUFW(buf,17)=md->sc.opt2;
		WBUFL(buf,19)=md->sc.option;
		WBUFW(buf,23)=mob_get_viewclass(md->class_);
		WBUFW(buf,25)=mob_get_hair(md->class_);
		WBUFW(buf,27)=mob_get_weapon(md->class_);
		WBUFW(buf,29)=mob_get_shield(md->class_);
		WBUFW(buf,31)=mob_get_head_bottom(md->class_);
		WBUFW(buf,33)=mob_get_head_top(md->class_);
		WBUFW(buf,35)=mob_get_head_mid(md->class_);
		WBUFW(buf,37)=mob_get_hair_color(md->class_);
		WBUFW(buf,39)=mob_get_clothes_color(md->class_);
		WBUFW(buf,43)=mob_get_robe(md->class_);
		if(md->guild_id){
			struct guild *g=guild_search(md->guild_id);
			if(g)
				WBUFW(buf,49)=g->emblem_id;
			WBUFL(buf,45)=md->guild_id;
		}
		WBUFL(buf,53)=md->sc.opt3;
		WBUFB(buf,57)=1;
		WBUFB(buf,58)=mob_get_sex(md->class_);
		WBUFPOS(buf,59,md->bl.x,md->bl.y,md->dir);
		WBUFB(buf,62)=5;
		WBUFB(buf,63)=5;
		WBUFLV(buf,65,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
		WBUFL(buf,69) = 0xffffffff;
		WBUFL(buf,73) = 0xffffffff;
		WBUFB(buf,77) = 0;
		WBUFW(buf,78) = 0;
#else
		len = 84 + (int)strlen(md->name);
		memset(buf,0,len);

		WBUFW(buf,0)=0x9ff;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=0;
		WBUFL(buf,5)=md->bl.id;
		WBUFL(buf,9)=0;
		WBUFW(buf,13)=status_get_speed(&md->bl);
		WBUFW(buf,15)=md->sc.opt1;
		WBUFW(buf,17)=md->sc.opt2;
		WBUFL(buf,19)=md->sc.option;
		WBUFW(buf,23)=mob_get_viewclass(md->class_);
		WBUFW(buf,25)=mob_get_hair(md->class_);
		WBUFL(buf,27)=mob_get_weapon(md->class_);
		WBUFL(buf,31)=mob_get_shield(md->class_);
		WBUFW(buf,35)=mob_get_head_bottom(md->class_);
		WBUFW(buf,37)=mob_get_head_top(md->class_);
		WBUFW(buf,39)=mob_get_head_mid(md->class_);
		WBUFW(buf,41)=mob_get_hair_color(md->class_);
		WBUFW(buf,43)=mob_get_clothes_color(md->class_);
		WBUFW(buf,47)=mob_get_robe(md->class_);
		if(md->guild_id){
			struct guild *g=guild_search(md->guild_id);
			if(g)
				WBUFW(buf,53)=g->emblem_id;
			WBUFL(buf,49)=md->guild_id;
		}
		WBUFL(buf,57)=md->sc.opt3;
		WBUFB(buf,61)=1;
		WBUFB(buf,62)=mob_get_sex(md->class_);
		WBUFPOS(buf,63,md->bl.x,md->bl.y,md->dir);
		WBUFB(buf,66)=5;
		WBUFB(buf,67)=5;
		WBUFLV(buf,69,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
		WBUFL(buf,73) = 0xffffffff;
		WBUFL(buf,77) = 0xffffffff;
		WBUFB(buf,81) = 0;
		WBUFW(buf,82) = 0;
#endif
		return len;
	}
#if PACKETVER < 20071106
	len = packet_db[0x78].len;
	memset(buf,0,len);

	WBUFW(buf,0)=0x78;
	WBUFL(buf,2)=md->bl.id;
	WBUFW(buf,6)=status_get_speed(&md->bl);
	WBUFW(buf,8)=md->sc.opt1;
	WBUFW(buf,10)=md->sc.opt2;
	WBUFW(buf,12)=md->sc.option;
	WBUFW(buf,14)=mob_get_viewclass(md->class_);
	if((md->class_ == 1285 || md->class_ == 1286 || md->class_ == 1287) && md->guild_id){
		struct guild *g=guild_search(md->guild_id);
		if(g)
			WBUFL(buf,22)=g->emblem_id;
		WBUFL(buf,26)=md->guild_id;
	}
	WBUFW(buf,42)=md->sc.opt3;
	WBUFPOS(buf,46,md->bl.x,md->bl.y,md->dir);
	WBUFB(buf,49)=5;
	WBUFB(buf,50)=5;
	WBUFLV(buf,52,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
#elif PACKETVER < 20091104
	len = packet_db[0x78].len;
	memset(buf,0,len);

	WBUFW(buf,0)=0x78;
	WBUFB(buf,2)=0;
	WBUFL(buf,3)=md->bl.id;
	WBUFW(buf,7)=status_get_speed(&md->bl);
	WBUFW(buf,9)=md->sc.opt1;
	WBUFW(buf,11)=md->sc.opt2;
	WBUFW(buf,13)=md->sc.option;
	WBUFW(buf,15)=mob_get_viewclass(md->class_);
	if((md->class_ == 1285 || md->class_ == 1286 || md->class_ == 1287) && md->guild_id){
		struct guild *g=guild_search(md->guild_id);
		if(g)
			WBUFL(buf,23)=g->emblem_id;
		WBUFL(buf,27)=md->guild_id;
	}
	WBUFW(buf,43)=md->sc.opt3;
	WBUFPOS(buf,47,md->bl.x,md->bl.y,md->dir);
	WBUFB(buf,50)=5;
	WBUFB(buf,51)=5;
	WBUFLV(buf,52,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
#elif PACKETVER < 20110111
	len = 63 + (int)strlen(md->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x7f9;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=5;
	WBUFL(buf,5)=md->bl.id;
	WBUFW(buf,9)=status_get_speed(&md->bl);
	WBUFW(buf,11)=md->sc.opt1;
	WBUFW(buf,13)=md->sc.opt2;
	WBUFL(buf,15)=md->sc.option;
	WBUFW(buf,19)=mob_get_viewclass(md->class_);
	if(md->guild_id){
		struct guild *g=guild_search(md->guild_id);
		if(g)
			WBUFW(buf,43)=g->emblem_id;
		WBUFL(buf,39)=md->guild_id;
	}
	WBUFL(buf,47)=md->sc.opt3;
	WBUFPOS(buf,53,md->bl.x,md->bl.y,md->dir);
	WBUFLV(buf,59,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
	strncpy(WBUFP(buf,63),md->name,24);
#elif PACKETVER < 20120328
	len = 65 + (int)strlen(md->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x857;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=5;
	WBUFL(buf,5)=md->bl.id;
	WBUFW(buf,9)=status_get_speed(&md->bl);
	WBUFW(buf,11)=md->sc.opt1;
	WBUFW(buf,13)=md->sc.opt2;
	WBUFL(buf,15)=md->sc.option;
	WBUFW(buf,19)=mob_get_viewclass(md->class_);
	if(md->guild_id){
		struct guild *g=guild_search(md->guild_id);
		if(g)
			WBUFW(buf,45)=g->emblem_id;
		WBUFL(buf,41)=md->guild_id;
	}
	WBUFL(buf,49)=md->sc.opt3;
	WBUFPOS(buf,55,md->bl.x,md->bl.y,md->dir);
	WBUFLV(buf,61,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
	strncpy(WBUFP(buf,65),md->name,24);
#elif PACKETVER < 20131223
	len = 74;
	memset(buf,0,len);

	WBUFW(buf,0)=0x915;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=5;
	WBUFL(buf,5)=md->bl.id;
	WBUFW(buf,9)=status_get_speed(&md->bl);
	WBUFW(buf,11)=md->sc.opt1;
	WBUFW(buf,13)=md->sc.opt2;
	WBUFL(buf,15)=md->sc.option;
	WBUFW(buf,19)=mob_get_viewclass(md->class_);
	if(md->guild_id){
		struct guild *g=guild_search(md->guild_id);
		if(g)
			WBUFW(buf,45)=g->emblem_id;
		WBUFL(buf,41)=md->guild_id;
	}
	WBUFL(buf,49)=md->sc.opt3;
	WBUFPOS(buf,55,md->bl.x,md->bl.y,md->dir);
	WBUFLV(buf,61,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
	WBUFL(buf,65) = 0xffffffff;
	WBUFL(buf,69) = 0xffffffff;
	WBUFB(buf,73) = 0;
#elif PACKETVER < 20150513
	len = 78 + (int)strlen(md->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9dd;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=5;
	WBUFL(buf,5)=md->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=status_get_speed(&md->bl);
	WBUFW(buf,15)=md->sc.opt1;
	WBUFW(buf,17)=md->sc.opt2;
	WBUFL(buf,19)=md->sc.option;
	WBUFW(buf,23)=mob_get_viewclass(md->class_);
	if(md->guild_id){
		struct guild *g=guild_search(md->guild_id);
		if(g)
			WBUFW(buf,49)=g->emblem_id;
		WBUFL(buf,45)=md->guild_id;
	}
	WBUFL(buf,53)=md->sc.opt3;
	WBUFPOS(buf,59,md->bl.x,md->bl.y,md->dir);
	WBUFLV(buf,65,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
	WBUFL(buf,69) = 0xffffffff;
	WBUFL(buf,73) = 0xffffffff;
	WBUFB(buf,77) = 0;
	strncpy(WBUFP(buf,78),md->name,24);
#elif PACKETVER < 20180704
	len = 80 + (int)strlen(md->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9ff;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=5;
	WBUFL(buf,5)=md->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=status_get_speed(&md->bl);
	WBUFW(buf,15)=md->sc.opt1;
	WBUFW(buf,17)=md->sc.opt2;
	WBUFL(buf,19)=md->sc.option;
	WBUFW(buf,23)=mob_get_viewclass(md->class_);
	if(md->guild_id){
		struct guild *g=guild_search(md->guild_id);
		if(g)
			WBUFW(buf,49)=g->emblem_id;
		WBUFL(buf,45)=md->guild_id;
	}
	WBUFL(buf,53)=md->sc.opt3;
	WBUFPOS(buf,59,md->bl.x,md->bl.y,md->dir);
	WBUFLV(buf,65,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
	WBUFL(buf,69) = 0xffffffff;
	WBUFL(buf,73) = 0xffffffff;
	WBUFB(buf,77) = 0;
	WBUFW(buf,78) = 0;
	strncpy(WBUFP(buf,80),md->name,24);
#else
	len = 84 + (int)strlen(md->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9ff;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=5;
	WBUFL(buf,5)=md->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=status_get_speed(&md->bl);
	WBUFW(buf,15)=md->sc.opt1;
	WBUFW(buf,17)=md->sc.opt2;
	WBUFL(buf,19)=md->sc.option;
	WBUFW(buf,23)=mob_get_viewclass(md->class_);
	if(md->guild_id){
		struct guild *g=guild_search(md->guild_id);
		if(g)
			WBUFW(buf,53)=g->emblem_id;
		WBUFL(buf,49)=md->guild_id;
	}
	WBUFL(buf,57)=md->sc.opt3;
	WBUFPOS(buf,63,md->bl.x,md->bl.y,md->dir);
	WBUFLV(buf,69,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
	WBUFL(buf,73) = 0xffffffff;
	WBUFL(buf,77) = 0xffffffff;
	WBUFB(buf,81) = 0;
	WBUFW(buf,82) = 0;
	strncpy(WBUFP(buf,84),md->name,24);
#endif
	return len;
}

/*==========================================
 * MOB�\��2
 *------------------------------------------
 */
static int clif_mob007b(struct mob_data *md,unsigned char *buf)
{
	int len;
	unsigned int tick = gettick();

	nullpo_retr(0, md);

	if(mob_is_pcview(md->class_)) {
#if PACKETVER < 4
		len = packet_db[0x7b].len;
		memset(buf,0,len);

		WBUFW(buf,0)=0x7b;
		WBUFL(buf,2)=md->bl.id;
		WBUFW(buf,6)=status_get_speed(&md->bl);
		WBUFW(buf,8)=md->sc.opt1;
		WBUFW(buf,10)=md->sc.opt2;
		WBUFW(buf,12)=md->sc.option;
		WBUFW(buf,14)=mob_get_viewclass(md->class_);
		WBUFW(buf,16)=mob_get_hair(md->class_);
		WBUFW(buf,18)=mob_get_weapon(md->class_);
		WBUFW(buf,20)=mob_get_head_bottom(md->class_);
		WBUFL(buf,22)=tick;
		WBUFW(buf,26)=mob_get_shield(md->class_);
		WBUFW(buf,28)=mob_get_head_top(md->class_);
		WBUFW(buf,30)=mob_get_head_mid(md->class_);
		WBUFW(buf,32)=mob_get_hair_color(md->class_);
		WBUFW(buf,34)=mob_get_clothes_color(md->class_);
		if(md->guild_id){
			struct guild *g=guild_search(md->guild_id);
			if(g)
				WBUFL(buf,42)=g->emblem_id;
			WBUFL(buf,38)=md->guild_id;
		}
		WBUFW(buf,46)=md->sc.opt3;
		WBUFB(buf,48)=1;
		WBUFB(buf,49)=mob_get_sex(md->class_);
		WBUFPOS2(buf,50,md->bl.x,md->bl.y,md->ud.to_x,md->ud.to_y,8,8);
		WBUFB(buf,56)=5;
		WBUFB(buf,57)=5;
		WBUFLV(buf,58,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
#elif PACKETVER < 7
		len = packet_db[0x1da].len;
		memset(buf,0,len);

		WBUFW(buf,0)=0x1da;
		WBUFL(buf,2)=md->bl.id;
		WBUFW(buf,6)=status_get_speed(&md->bl);
		WBUFW(buf,8)=md->sc.opt1;
		WBUFW(buf,10)=md->sc.opt2;
		WBUFW(buf,12)=md->sc.option;
		WBUFW(buf,14)=mob_get_viewclass(md->class_);
		WBUFW(buf,16)=mob_get_hair(md->class_);
		WBUFW(buf,18)=mob_get_weapon(md->class_);
		WBUFW(buf,20)=mob_get_shield(md->class_);
		WBUFW(buf,22)=mob_get_head_bottom(md->class_);
		WBUFL(buf,24)=tick;
		WBUFW(buf,28)=mob_get_head_top(md->class_);
		WBUFW(buf,30)=mob_get_head_mid(md->class_);
		WBUFW(buf,32)=mob_get_hair_color(md->class_);
		WBUFW(buf,34)=mob_get_clothes_color(md->class_);
		if(md->guild_id){
			struct guild *g=guild_search(md->guild_id);
			if(g)
				WBUFL(buf,42)=g->emblem_id;
			WBUFL(buf,38)=md->guild_id;
		}
		WBUFW(buf,46)=md->sc.opt3;
		WBUFB(buf,48)=1;
		WBUFB(buf,49)=mob_get_sex(md->class_);
		WBUFPOS2(buf,50,md->bl.x,md->bl.y,md->ud.to_x,md->ud.to_y,8,8);
		WBUFB(buf,56)=5;
		WBUFB(buf,57)=5;
		WBUFLV(buf,58,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
#elif PACKETVER < 20071106
		len = packet_db[0x22c].len;
		memset(buf,0,len);

		WBUFW(buf,0)=0x22c;
		WBUFL(buf,2)=md->bl.id;
		WBUFW(buf,6)=status_get_speed(&md->bl);
		WBUFW(buf,8)=md->sc.opt1;
		WBUFW(buf,10)=md->sc.opt2;
		WBUFL(buf,12)=md->sc.option;
		WBUFW(buf,16)=mob_get_viewclass(md->class_);
		WBUFW(buf,18)=mob_get_hair(md->class_);
		WBUFW(buf,20)=mob_get_weapon(md->class_);
		WBUFW(buf,22)=mob_get_shield(md->class_);
		WBUFW(buf,24)=mob_get_head_bottom(md->class_);
		WBUFL(buf,26)=tick;
		WBUFW(buf,30)=mob_get_head_top(md->class_);
		WBUFW(buf,32)=mob_get_head_mid(md->class_);
		WBUFW(buf,34)=mob_get_hair_color(md->class_);
		WBUFW(buf,36)=mob_get_clothes_color(md->class_);
		if(md->guild_id){
			struct guild *g=guild_search(md->guild_id);
			if(g)
				WBUFL(buf,44)=g->emblem_id;
			WBUFL(buf,40)=md->guild_id;
		}
		WBUFL(buf,48)=md->sc.opt3;
		WBUFB(buf,52)=1;
		WBUFB(buf,53)=mob_get_sex(md->class_);
		WBUFPOS2(buf,54,md->bl.x,md->bl.y,md->ud.to_x,md->ud.to_y,8,8);
		WBUFB(buf,60)=0;
		WBUFB(buf,61)=0;
		WBUFLV(buf,62,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
#elif PACKETVER < 20080102
		len = packet_db[0x22c].len;
		memset(buf,0,len);

		WBUFW(buf,0)=0x22c;
		WBUFB(buf,2)=0;
		WBUFL(buf,3)=md->bl.id;
		WBUFW(buf,7)=status_get_speed(&md->bl);
		WBUFW(buf,9)=md->sc.opt1;
		WBUFW(buf,11)=md->sc.opt2;
		WBUFL(buf,13)=md->sc.option;
		WBUFW(buf,17)=mob_get_viewclass(md->class_);
		WBUFW(buf,19)=mob_get_hair(md->class_);
		WBUFW(buf,21)=mob_get_weapon(md->class_);
		WBUFW(buf,23)=mob_get_shield(md->class_);
		WBUFW(buf,25)=mob_get_head_bottom(md->class_);
		WBUFL(buf,27)=tick;
		WBUFW(buf,31)=mob_get_head_top(md->class_);
		WBUFW(buf,33)=mob_get_head_mid(md->class_);
		WBUFW(buf,35)=mob_get_hair_color(md->class_);
		WBUFW(buf,37)=mob_get_clothes_color(md->class_);
		if(md->guild_id){
			struct guild *g=guild_search(md->guild_id);
			if(g)
				WBUFL(buf,45)=g->emblem_id;
			WBUFL(buf,41)=md->guild_id;
		}
		WBUFL(buf,49)=md->sc.opt3;
		WBUFB(buf,53)=1;
		WBUFB(buf,54)=mob_get_sex(md->class_);
		WBUFPOS2(buf,55,md->bl.x,md->bl.y,md->ud.to_x,md->ud.to_y,8,8);
		WBUFB(buf,61)=0;
		WBUFB(buf,62)=0;
		WBUFLV(buf,63,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
#elif PACKETVER < 20091104
		len = packet_db[0x2ec].len;
		memset(buf,0,len);

		WBUFW(buf,0)=0x2ec;
		WBUFB(buf,2)=0;
		WBUFL(buf,3)=md->bl.id;
		WBUFW(buf,7)=status_get_speed(&md->bl);
		WBUFW(buf,9)=md->sc.opt1;
		WBUFW(buf,11)=md->sc.opt2;
		WBUFL(buf,13)=md->sc.option;
		WBUFW(buf,17)=mob_get_viewclass(md->class_);
		WBUFW(buf,19)=mob_get_hair(md->class_);
		WBUFW(buf,21)=mob_get_weapon(md->class_);
		WBUFW(buf,23)=mob_get_shield(md->class_);
		WBUFW(buf,25)=mob_get_head_bottom(md->class_);
		WBUFL(buf,27)=tick;
		WBUFW(buf,31)=mob_get_head_top(md->class_);
		WBUFW(buf,33)=mob_get_head_mid(md->class_);
		WBUFW(buf,35)=mob_get_hair_color(md->class_);
		WBUFW(buf,37)=mob_get_clothes_color(md->class_);
		if(md->guild_id){
			struct guild *g=guild_search(md->guild_id);
			if(g)
				WBUFL(buf,45)=g->emblem_id;
			WBUFL(buf,41)=md->guild_id;
		}
		WBUFL(buf,49)=md->sc.opt3;
		WBUFB(buf,53)=1;
		WBUFB(buf,54)=mob_get_sex(md->class_);
		WBUFPOS2(buf,55,md->bl.x,md->bl.y,md->ud.to_x,md->ud.to_y,8,8);
		WBUFB(buf,61)=0;
		WBUFB(buf,62)=0;
		WBUFLV(buf,63,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
		WBUFW(buf,65)=0;
#elif PACKETVER < 20110111
		len = 69 + (int)strlen(md->name);
		memset(buf,0,len);

		WBUFW(buf,0)=0x7f7;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=0;
		WBUFL(buf,5)=md->bl.id;
		WBUFW(buf,9)=status_get_speed(&md->bl);
		WBUFW(buf,11)=md->sc.opt1;
		WBUFW(buf,13)=md->sc.opt2;
		WBUFL(buf,15)=md->sc.option;
		WBUFW(buf,19)=mob_get_viewclass(md->class_);
		WBUFW(buf,21)=mob_get_hair(md->class_);
		WBUFW(buf,23)=mob_get_weapon(md->class_);
		WBUFW(buf,25)=mob_get_shield(md->class_);
		WBUFW(buf,27)=mob_get_head_bottom(md->class_);
		WBUFL(buf,29)=tick;
		WBUFW(buf,33)=mob_get_head_top(md->class_);
		WBUFW(buf,35)=mob_get_head_mid(md->class_);
		WBUFW(buf,37)=mob_get_hair_color(md->class_);
		WBUFW(buf,39)=mob_get_clothes_color(md->class_);
		if(md->guild_id){
			struct guild *g=guild_search(md->guild_id);
			if(g)
				WBUFW(buf,47)=g->emblem_id;
			WBUFL(buf,43)=md->guild_id;
		}
		WBUFL(buf,51)=md->sc.opt3;
		WBUFB(buf,55)=1;
		WBUFB(buf,56)=mob_get_sex(md->class_);
		WBUFPOS2(buf,57,md->bl.x,md->bl.y,md->ud.to_x,md->ud.to_y,8,8);
		WBUFB(buf,63)=5;
		WBUFB(buf,64)=5;
		WBUFLV(buf,65,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
		strncpy(WBUFP(buf,69),md->name,24);
#elif PACKETVER < 20120328
		len = 71 + (int)strlen(md->name);
		memset(buf,0,len);

		WBUFW(buf,0)=0x856;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=0;
		WBUFL(buf,5)=md->bl.id;
		WBUFW(buf,9)=status_get_speed(&md->bl);
		WBUFW(buf,11)=md->sc.opt1;
		WBUFW(buf,13)=md->sc.opt2;
		WBUFL(buf,15)=md->sc.option;
		WBUFW(buf,19)=mob_get_viewclass(md->class_);
		WBUFW(buf,21)=mob_get_hair(md->class_);
		WBUFW(buf,23)=mob_get_weapon(md->class_);
		WBUFW(buf,25)=mob_get_shield(md->class_);
		WBUFW(buf,27)=mob_get_head_bottom(md->class_);
		WBUFL(buf,29)=tick;
		WBUFW(buf,33)=mob_get_head_top(md->class_);
		WBUFW(buf,35)=mob_get_head_mid(md->class_);
		WBUFW(buf,37)=mob_get_hair_color(md->class_);
		WBUFW(buf,39)=mob_get_clothes_color(md->class_);
		WBUFW(buf,43)=mob_get_robe(md->class_);
		if(md->guild_id){
			struct guild *g=guild_search(md->guild_id);
			if(g)
				WBUFW(buf,49)=g->emblem_id;
			WBUFL(buf,45)=md->guild_id;
		}
		WBUFL(buf,53)=md->sc.opt3;
		WBUFB(buf,57)=1;
		WBUFB(buf,58)=mob_get_sex(md->class_);
		WBUFPOS2(buf,59,md->bl.x,md->bl.y,md->ud.to_x,md->ud.to_y,8,8);
		WBUFB(buf,65)=5;
		WBUFB(buf,66)=5;
		WBUFLV(buf,67,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
		strncpy(WBUFP(buf,71),md->name,24);
#elif PACKETVER < 20131223
		len = 80;
		memset(buf,0,len);

		WBUFW(buf,0)=0x914;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=0;
		WBUFL(buf,5)=md->bl.id;
		WBUFW(buf,9)=status_get_speed(&md->bl);
		WBUFW(buf,11)=md->sc.opt1;
		WBUFW(buf,13)=md->sc.opt2;
		WBUFL(buf,15)=md->sc.option;
		WBUFW(buf,19)=mob_get_viewclass(md->class_);
		WBUFW(buf,21)=mob_get_hair(md->class_);
		WBUFW(buf,23)=mob_get_weapon(md->class_);
		WBUFW(buf,25)=mob_get_shield(md->class_);
		WBUFW(buf,27)=mob_get_head_bottom(md->class_);
		WBUFL(buf,29)=tick;
		WBUFW(buf,33)=mob_get_head_top(md->class_);
		WBUFW(buf,35)=mob_get_head_mid(md->class_);
		WBUFW(buf,37)=mob_get_hair_color(md->class_);
		WBUFW(buf,39)=mob_get_clothes_color(md->class_);
		WBUFW(buf,43)=mob_get_robe(md->class_);
		if(md->guild_id){
			struct guild *g=guild_search(md->guild_id);
			if(g)
				WBUFW(buf,49)=g->emblem_id;
			WBUFL(buf,45)=md->guild_id;
		}
		WBUFL(buf,53)=md->sc.opt3;
		WBUFB(buf,57)=1;
		WBUFB(buf,58)=mob_get_sex(md->class_);
		WBUFPOS2(buf,59,md->bl.x,md->bl.y,md->ud.to_x,md->ud.to_y,8,8);
		WBUFB(buf,65)=5;
		WBUFB(buf,66)=5;
		WBUFLV(buf,67,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
		WBUFL(buf,71) = 0xffffffff;
		WBUFL(buf,75) = 0xffffffff;
		WBUFB(buf,79) = 0;
#elif PACKETVER < 20150513
		len = 84 + (int)strlen(md->name);
		memset(buf,0,len);

		WBUFW(buf,0)=0x9db;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=0;
		WBUFL(buf,5)=md->bl.id;
		WBUFL(buf,9)=0;
		WBUFW(buf,13)=status_get_speed(&md->bl);
		WBUFW(buf,15)=md->sc.opt1;
		WBUFW(buf,17)=md->sc.opt2;
		WBUFL(buf,19)=md->sc.option;
		WBUFW(buf,23)=mob_get_viewclass(md->class_);
		WBUFW(buf,25)=mob_get_hair(md->class_);
		WBUFW(buf,27)=mob_get_weapon(md->class_);
		WBUFW(buf,29)=mob_get_shield(md->class_);
		WBUFW(buf,31)=mob_get_head_bottom(md->class_);
		WBUFL(buf,33)=tick;
		WBUFW(buf,37)=mob_get_head_top(md->class_);
		WBUFW(buf,39)=mob_get_head_mid(md->class_);
		WBUFW(buf,41)=mob_get_hair_color(md->class_);
		WBUFW(buf,43)=mob_get_clothes_color(md->class_);
		WBUFW(buf,47)=mob_get_robe(md->class_);
		if(md->guild_id){
			struct guild *g=guild_search(md->guild_id);
			if(g)
				WBUFW(buf,53)=g->emblem_id;
			WBUFL(buf,49)=md->guild_id;
		}
		WBUFL(buf,57)=md->sc.opt3;
		WBUFB(buf,61)=1;
		WBUFB(buf,62)=mob_get_sex(md->class_);
		WBUFPOS2(buf,63,md->bl.x,md->bl.y,md->ud.to_x,md->ud.to_y,8,8);
		WBUFB(buf,69)=5;
		WBUFB(buf,70)=5;
		WBUFLV(buf,71,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
		WBUFL(buf,75) = 0xffffffff;
		WBUFL(buf,79) = 0xffffffff;
		WBUFB(buf,83) = 0;
		strncpy(WBUFP(buf,84),md->name,24);
#elif PACKETVER < 20180704
		len = 86 + (int)strlen(md->name);
		memset(buf,0,len);

		WBUFW(buf,0)=0x9fd;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=0;
		WBUFL(buf,5)=md->bl.id;
		WBUFL(buf,9)=0;
		WBUFW(buf,13)=status_get_speed(&md->bl);
		WBUFW(buf,15)=md->sc.opt1;
		WBUFW(buf,17)=md->sc.opt2;
		WBUFL(buf,19)=md->sc.option;
		WBUFW(buf,23)=mob_get_viewclass(md->class_);
		WBUFW(buf,25)=mob_get_hair(md->class_);
		WBUFW(buf,27)=mob_get_weapon(md->class_);
		WBUFW(buf,29)=mob_get_shield(md->class_);
		WBUFW(buf,31)=mob_get_head_bottom(md->class_);
		WBUFL(buf,33)=tick;
		WBUFW(buf,37)=mob_get_head_top(md->class_);
		WBUFW(buf,39)=mob_get_head_mid(md->class_);
		WBUFW(buf,41)=mob_get_hair_color(md->class_);
		WBUFW(buf,43)=mob_get_clothes_color(md->class_);
		WBUFW(buf,47)=mob_get_robe(md->class_);
		if(md->guild_id){
			struct guild *g=guild_search(md->guild_id);
			if(g)
				WBUFW(buf,53)=g->emblem_id;
			WBUFL(buf,49)=md->guild_id;
		}
		WBUFL(buf,57)=md->sc.opt3;
		WBUFB(buf,61)=1;
		WBUFB(buf,62)=mob_get_sex(md->class_);
		WBUFPOS2(buf,63,md->bl.x,md->bl.y,md->ud.to_x,md->ud.to_y,8,8);
		WBUFB(buf,69)=5;
		WBUFB(buf,70)=5;
		WBUFLV(buf,71,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
		WBUFL(buf,75) = 0xffffffff;
		WBUFL(buf,79) = 0xffffffff;
		WBUFB(buf,83) = 0;
		WBUFW(buf,84) = mob_get_style(md->class_);
		strncpy(WBUFP(buf,86),md->name,24);
#else
		len = 90 + (int)strlen(md->name);
		memset(buf,0,len);

		WBUFW(buf,0)=0x9fd;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=0;
		WBUFL(buf,5)=md->bl.id;
		WBUFL(buf,9)=0;
		WBUFW(buf,13)=status_get_speed(&md->bl);
		WBUFW(buf,15)=md->sc.opt1;
		WBUFW(buf,17)=md->sc.opt2;
		WBUFL(buf,19)=md->sc.option;
		WBUFW(buf,23)=mob_get_viewclass(md->class_);
		WBUFW(buf,25)=mob_get_hair(md->class_);
		WBUFL(buf,27)=mob_get_weapon(md->class_);
		WBUFL(buf,31)=mob_get_shield(md->class_);
		WBUFW(buf,35)=mob_get_head_bottom(md->class_);
		WBUFL(buf,37)=tick;
		WBUFW(buf,41)=mob_get_head_top(md->class_);
		WBUFW(buf,43)=mob_get_head_mid(md->class_);
		WBUFW(buf,45)=mob_get_hair_color(md->class_);
		WBUFW(buf,47)=mob_get_clothes_color(md->class_);
		WBUFW(buf,49)=mob_get_robe(md->class_);
		if(md->guild_id){
			struct guild *g=guild_search(md->guild_id);
			if(g)
				WBUFW(buf,57)=g->emblem_id;
			WBUFL(buf,53)=md->guild_id;
		}
		WBUFL(buf,61)=md->sc.opt3;
		WBUFB(buf,65)=1;
		WBUFB(buf,66)=mob_get_sex(md->class_);
		WBUFPOS2(buf,67,md->bl.x,md->bl.y,md->ud.to_x,md->ud.to_y,8,8);
		WBUFB(buf,73)=5;
		WBUFB(buf,74)=5;
		WBUFLV(buf,75,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
		WBUFL(buf,79) = 0xffffffff;
		WBUFL(buf,83) = 0xffffffff;
		WBUFB(buf,87) = 0;
		WBUFW(buf,88) = mob_get_style(md->class_);
		strncpy(WBUFP(buf,90),md->name,24);
#endif
		return len;
	}

#if PACKETVER < 20091104
	len = packet_db[0x7b].len;
	memset(buf,0,len);

	WBUFW(buf,0)=0x7b;
	WBUFL(buf,2)=md->bl.id;
	WBUFW(buf,6)=status_get_speed(&md->bl);
	WBUFW(buf,8)=md->sc.opt1;
	WBUFW(buf,10)=md->sc.opt2;
	WBUFW(buf,12)=md->sc.option;
	WBUFW(buf,14)=mob_get_viewclass(md->class_);
	WBUFL(buf,22)=tick;
	if((md->class_ == 1285 || md->class_ == 1286 || md->class_ == 1287) && md->guild_id){
		struct guild *g=guild_search(md->guild_id);
		if(g)
			WBUFL(buf,26)=g->emblem_id;
		WBUFL(buf,30)=md->guild_id;
	}
	WBUFW(buf,46)=md->sc.opt3;
	WBUFPOS2(buf,50,md->bl.x,md->bl.y,md->ud.to_x,md->ud.to_y,8,8);
	WBUFB(buf,56)=5;
	WBUFB(buf,57)=5;
	WBUFLV(buf,58,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
#elif PACKETVER < 20110111
	len = 69 + (int)strlen(md->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x7f7;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=5;
	WBUFL(buf,5)=md->bl.id;
	WBUFW(buf,9)=status_get_speed(&md->bl);
	WBUFW(buf,11)=md->sc.opt1;
	WBUFW(buf,13)=md->sc.opt2;
	WBUFL(buf,15)=md->sc.option;
	WBUFW(buf,19)=mob_get_viewclass(md->class_);
	WBUFL(buf,29)=tick;
	if(md->guild_id){
		struct guild *g=guild_search(md->guild_id);
		if(g)
			WBUFW(buf,47)=g->emblem_id;
		WBUFL(buf,43)=md->guild_id;
	}
	WBUFL(buf,51)=md->sc.opt3;
	WBUFPOS2(buf,57,md->bl.x,md->bl.y,md->ud.to_x,md->ud.to_y,8,8);
	WBUFLV(buf,65,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
	strncpy(WBUFP(buf,69),md->name,24);
#elif PACKETVER < 20120328
	len = 71 + (int)strlen(md->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x856;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=5;
	WBUFL(buf,5)=md->bl.id;
	WBUFW(buf,9)=status_get_speed(&md->bl);
	WBUFW(buf,11)=md->sc.opt1;
	WBUFW(buf,13)=md->sc.opt2;
	WBUFL(buf,15)=md->sc.option;
	WBUFW(buf,19)=mob_get_viewclass(md->class_);
	WBUFL(buf,29)=tick;
	if(md->guild_id){
		struct guild *g=guild_search(md->guild_id);
		if(g)
			WBUFW(buf,49)=g->emblem_id;
		WBUFL(buf,45)=md->guild_id;
	}
	WBUFL(buf,53)=md->sc.opt3;
	WBUFPOS2(buf,59,md->bl.x,md->bl.y,md->ud.to_x,md->ud.to_y,8,8);
	WBUFLV(buf,67,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
	strncpy(WBUFP(buf,71),md->name,24);
#elif PACKETVER < 20131223
	len = 80;
	memset(buf,0,len);

	WBUFW(buf,0)=0x914;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=5;
	WBUFL(buf,5)=md->bl.id;
	WBUFW(buf,9)=status_get_speed(&md->bl);
	WBUFW(buf,11)=md->sc.opt1;
	WBUFW(buf,13)=md->sc.opt2;
	WBUFL(buf,15)=md->sc.option;
	WBUFW(buf,19)=mob_get_viewclass(md->class_);
	WBUFL(buf,29)=tick;
	if(md->guild_id){
		struct guild *g=guild_search(md->guild_id);
		if(g)
			WBUFW(buf,49)=g->emblem_id;
		WBUFL(buf,45)=md->guild_id;
	}
	WBUFL(buf,53)=md->sc.opt3;
	WBUFPOS2(buf,59,md->bl.x,md->bl.y,md->ud.to_x,md->ud.to_y,8,8);
	WBUFLV(buf,67,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
	WBUFL(buf,71) = 0xffffffff;
	WBUFL(buf,75) = 0xffffffff;
	WBUFB(buf,79) = 0;
#elif PACKETVER < 20150513
	len = 84 + (int)strlen(md->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9db;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=5;
	WBUFL(buf,5)=md->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=status_get_speed(&md->bl);
	WBUFW(buf,15)=md->sc.opt1;
	WBUFW(buf,17)=md->sc.opt2;
	WBUFL(buf,19)=md->sc.option;
	WBUFW(buf,23)=mob_get_viewclass(md->class_);
	WBUFL(buf,33)=tick;
	if(md->guild_id){
		struct guild *g=guild_search(md->guild_id);
		if(g)
			WBUFW(buf,53)=g->emblem_id;
		WBUFL(buf,49)=md->guild_id;
	}
	WBUFL(buf,57)=md->sc.opt3;
	WBUFPOS2(buf,63,md->bl.x,md->bl.y,md->ud.to_x,md->ud.to_y,8,8);
	WBUFLV(buf,71,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
	WBUFL(buf,75) = 0xffffffff;
	WBUFL(buf,79) = 0xffffffff;
	WBUFB(buf,83) = 0;
	strncpy(WBUFP(buf,84),md->name,24);
#elif PACKETVER < 20180704
	len = 86 + (int)strlen(md->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9fd;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=5;
	WBUFL(buf,5)=md->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=status_get_speed(&md->bl);
	WBUFW(buf,15)=md->sc.opt1;
	WBUFW(buf,17)=md->sc.opt2;
	WBUFL(buf,19)=md->sc.option;
	WBUFW(buf,23)=mob_get_viewclass(md->class_);
	WBUFL(buf,33)=tick;
	if(md->guild_id){
		struct guild *g=guild_search(md->guild_id);
		if(g)
			WBUFW(buf,53)=g->emblem_id;
		WBUFL(buf,49)=md->guild_id;
	}
	WBUFL(buf,57)=md->sc.opt3;
	WBUFPOS2(buf,63,md->bl.x,md->bl.y,md->ud.to_x,md->ud.to_y,8,8);
	WBUFLV(buf,71,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
	WBUFL(buf,75) = 0xffffffff;
	WBUFL(buf,79) = 0xffffffff;
	WBUFB(buf,83) = 0;
	WBUFW(buf,84) = mob_get_style(md->class_);
	strncpy(WBUFP(buf,86),md->name,24);
#else
	len = 90 + (int)strlen(md->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9fd;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=5;
	WBUFL(buf,5)=md->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=status_get_speed(&md->bl);
	WBUFW(buf,15)=md->sc.opt1;
	WBUFW(buf,17)=md->sc.opt2;
	WBUFL(buf,19)=md->sc.option;
	WBUFW(buf,23)=mob_get_viewclass(md->class_);
	WBUFL(buf,37)=tick;
	if(md->guild_id){
		struct guild *g=guild_search(md->guild_id);
		if(g)
			WBUFW(buf,57)=g->emblem_id;
		WBUFL(buf,53)=md->guild_id;
	}
	WBUFL(buf,61)=md->sc.opt3;
	WBUFPOS2(buf,67,md->bl.x,md->bl.y,md->ud.to_x,md->ud.to_y,8,8);
	WBUFLV(buf,75,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
	WBUFL(buf,79) = 0xffffffff;
	WBUFL(buf,83) = 0xffffffff;
	WBUFB(buf,87) = 0;
	WBUFW(buf,88) = mob_get_style(md->class_);
	strncpy(WBUFP(buf,90),md->name,24);
#endif
	return len;
}

/*==========================================
 *
 *------------------------------------------
 */
static int clif_npc0078(struct npc_data *nd,unsigned char *buf,struct map_session_data* sd)
{
	struct guild *g;
	int len;
	int option = nd->option;

	nullpo_retr(0, nd);

	if(sd && option&OPTION_CLOAKING) {
		int i;
		for(i=0; i < MAX_CLOAKEDNPC; i++) {
			if(sd->cloaked_npc[i] == nd->bl.id) {
				option &= ~OPTION_CLOAKING;
				break;
			}
		}
	}
#if PACKETVER < 20071106
	len = packet_db[0x78].len;
	memset(buf,0,len);

	WBUFW(buf,0)=0x78;
	WBUFL(buf,2)=nd->bl.id;
	WBUFW(buf,6)=nd->speed;
	WBUFW(buf,12)=option;
	WBUFW(buf,14)=nd->class_;
	if( nd->subtype != WARP &&
	    nd->class_ == WARP_DEBUG_CLASS &&
	    nd->u.scr.guild_id > 0 &&
	    (g = guild_search(nd->u.scr.guild_id)) )
	{
		WBUFL(buf,26)=g->guild_id;
		WBUFL(buf,36)=g->guild_id;
		WBUFW(buf,40)=g->emblem_id;
	}
	WBUFPOS(buf,46,nd->bl.x,nd->bl.y,nd->dir);
	WBUFB(buf,49)=5;
	WBUFB(buf,50)=5;
#elif PACKETVER < 20091104
	len = packet_db[0x78].len;
	memset(buf,0,len);

	WBUFW(buf,0)=0x78;
	WBUFB(buf,2)=0;
	WBUFL(buf,3)=nd->bl.id;
	WBUFW(buf,7)=nd->speed;
	WBUFW(buf,13)=option;
	WBUFW(buf,15)=nd->class_;
	if( nd->subtype != WARP &&
	    nd->class_ == WARP_DEBUG_CLASS &&
	    nd->u.scr.guild_id > 0 &&
	    (g = guild_search(nd->u.scr.guild_id)) )
	{
		WBUFL(buf,26)=g->guild_id;
		WBUFL(buf,37)=g->guild_id;
		WBUFW(buf,41)=g->emblem_id;
	}
	WBUFPOS(buf,47,nd->bl.x,nd->bl.y,nd->dir);
	WBUFB(buf,50)=5;
	WBUFB(buf,51)=5;
#elif PACKETVER < 20110111
	len = 63 + (int)strlen(nd->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x7f9;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=(nd->u.scr.moveable > 0)? 12: 6;
	WBUFL(buf,5)=nd->bl.id;
	WBUFW(buf,9)=nd->speed;
	WBUFL(buf,15)=option;
	WBUFW(buf,19)=nd->class_;
	if(npc_is_pcview(nd)) {
		WBUFW(buf,21)=nd->hair;
		WBUFW(buf,23)=0;
		WBUFW(buf,25)=0;
		WBUFW(buf,27)=nd->head_bottom;
		WBUFW(buf,29)=nd->head_top;
		WBUFW(buf,31)=nd->head_mid;
		WBUFW(buf,33)=nd->hair_color;
		WBUFW(buf,35)=nd->clothes_color;
		WBUFW(buf,37)=0;
		WBUFB(buf,52)=nd->sex;
	}
	if( nd->subtype != WARP &&
	    nd->class_ == WARP_DEBUG_CLASS &&
	    nd->u.scr.guild_id > 0 &&
	    (g = guild_search(nd->u.scr.guild_id)) )
	{
		WBUFL(buf,31)=g->guild_id;
		WBUFL(buf,39)=g->guild_id;
		WBUFW(buf,43)=g->emblem_id;
	}
	WBUFPOS(buf,53,nd->bl.x,nd->bl.y,nd->dir);
	WBUFW(buf,59)=1;
	strncpy(WBUFP(buf,63),nd->name,24);
#elif PACKETVER < 20120328
	len = 65 + (int)strlen(nd->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x857;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=(nd->u.scr.moveable > 0)? 12: 6;
	WBUFL(buf,5)=nd->bl.id;
	WBUFW(buf,9)=nd->speed;
	WBUFL(buf,15)=option;
	WBUFW(buf,19)=nd->class_;
	if(npc_is_pcview(nd)) {
		WBUFW(buf,21)=nd->hair;
		WBUFW(buf,23)=0;
		WBUFW(buf,25)=0;
		WBUFW(buf,27)=nd->head_bottom;
		WBUFW(buf,29)=nd->head_top;
		WBUFW(buf,31)=nd->head_mid;
		WBUFW(buf,33)=nd->hair_color;
		WBUFW(buf,35)=nd->clothes_color;
		WBUFW(buf,37)=0;
		WBUFW(buf,39)=nd->robe;
		WBUFB(buf,54)=nd->sex;
	}
	if( nd->subtype != WARP &&
	    nd->class_ == WARP_DEBUG_CLASS &&
	    nd->u.scr.guild_id > 0 &&
	    (g = guild_search(nd->u.scr.guild_id)) )
	{
		WBUFL(buf,31)=g->guild_id;
		WBUFL(buf,41)=g->guild_id;
		WBUFW(buf,45)=g->emblem_id;
	}
	WBUFPOS(buf,55,nd->bl.x,nd->bl.y,nd->dir);
	WBUFW(buf,61)=1;
	strncpy(WBUFP(buf,65),nd->name,24);
#elif PACKETVER < 20131223
	len = 74;
	memset(buf,0,len);

	WBUFW(buf,0)=0x915;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=(nd->u.scr.moveable > 0)? 12: 6;
	WBUFL(buf,5)=nd->bl.id;
	WBUFW(buf,9)=nd->speed;
	WBUFL(buf,15)=option;
	WBUFW(buf,19)=nd->class_;
	if(npc_is_pcview(nd)) {
		WBUFW(buf,21)=nd->hair;
		WBUFW(buf,23)=0;
		WBUFW(buf,25)=0;
		WBUFW(buf,27)=nd->head_bottom;
		WBUFW(buf,29)=nd->head_top;
		WBUFW(buf,31)=nd->head_mid;
		WBUFW(buf,33)=nd->hair_color;
		WBUFW(buf,35)=nd->clothes_color;
		WBUFW(buf,37)=0;
		WBUFW(buf,39)=nd->robe;
		WBUFB(buf,54)=nd->sex;
	}
	if( nd->subtype != WARP &&
	    nd->class_ == WARP_DEBUG_CLASS &&
	    nd->u.scr.guild_id > 0 &&
	    (g = guild_search(nd->u.scr.guild_id)) )
	{
		WBUFL(buf,31)=g->guild_id;
		WBUFL(buf,41)=g->guild_id;
		WBUFW(buf,45)=g->emblem_id;
	}
	WBUFPOS(buf,55,nd->bl.x,nd->bl.y,nd->dir);
	WBUFW(buf,61)=1;
	WBUFL(buf,65) = 0xffffffff;
	WBUFL(buf,69) = 0xffffffff;
	WBUFB(buf,73) = 0;
#elif PACKETVER < 20150513
	len = 78 + (int)strlen(nd->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9dd;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=(nd->u.scr.moveable > 0)? 12: 6;
	WBUFL(buf,5)=nd->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=nd->speed;
	WBUFL(buf,19)=option;
	WBUFW(buf,23)=nd->class_;
	if(npc_is_pcview(nd)) {
		WBUFW(buf,25)=nd->hair;
		WBUFW(buf,27)=0;
		WBUFW(buf,29)=0;
		WBUFW(buf,31)=nd->head_bottom;
		WBUFW(buf,33)=nd->head_top;
		WBUFW(buf,35)=nd->head_mid;
		WBUFW(buf,37)=nd->hair_color;
		WBUFW(buf,39)=nd->clothes_color;
		WBUFW(buf,41)=0;
		WBUFW(buf,43)=nd->robe;
		WBUFB(buf,58)=nd->sex;
	}
	if( nd->subtype != WARP &&
	    nd->class_ == WARP_DEBUG_CLASS &&
	    nd->u.scr.guild_id > 0 &&
	    (g = guild_search(nd->u.scr.guild_id)) )
	{
		WBUFL(buf,35)=g->guild_id;
		WBUFL(buf,45)=g->guild_id;
		WBUFW(buf,49)=g->emblem_id;
	}
	WBUFPOS(buf,59,nd->bl.x,nd->bl.y,nd->dir);
	WBUFW(buf,65)=1;
	WBUFL(buf,69) = 0xffffffff;
	WBUFL(buf,73) = 0xffffffff;
	WBUFB(buf,77) = 0;
	strncpy(WBUFP(buf,78),nd->name,24);
#elif PACKETVER < 20180704
	len = 80 + (int)strlen(nd->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9ff;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=(nd->u.scr.moveable > 0)? 12: 6;
	WBUFL(buf,5)=nd->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=nd->speed;
	WBUFL(buf,19)=option;
	WBUFW(buf,23)=nd->class_;
	if(npc_is_pcview(nd)) {
		WBUFW(buf,25)=nd->hair;
		WBUFW(buf,27)=0;
		WBUFW(buf,29)=0;
		WBUFW(buf,31)=nd->head_bottom;
		WBUFW(buf,33)=nd->head_top;
		WBUFW(buf,35)=nd->head_mid;
		WBUFW(buf,37)=nd->hair_color;
		WBUFW(buf,39)=nd->clothes_color;
		WBUFW(buf,41)=0;
		WBUFW(buf,43)=nd->robe;
		WBUFB(buf,58)=nd->sex;
		WBUFW(buf,78)=nd->style;
	}
	if( nd->subtype != WARP &&
	    nd->class_ == WARP_DEBUG_CLASS &&
	    nd->u.scr.guild_id > 0 &&
	    (g = guild_search(nd->u.scr.guild_id)) )
	{
		WBUFL(buf,35)=g->guild_id;
		WBUFL(buf,45)=g->guild_id;
		WBUFW(buf,49)=g->emblem_id;
	}
	WBUFPOS(buf,59,nd->bl.x,nd->bl.y,nd->dir);
	WBUFW(buf,65)=1;
	WBUFL(buf,69) = 0xffffffff;
	WBUFL(buf,73) = 0xffffffff;
	WBUFB(buf,77) = 0;
	strncpy(WBUFP(buf,80),nd->name,24);
#else
	len = 84 + (int)strlen(nd->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9ff;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=(nd->u.scr.moveable > 0)? 12: 6;
	WBUFL(buf,5)=nd->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=nd->speed;
	WBUFL(buf,19)=option;
	WBUFW(buf,23)=nd->class_;
	if(npc_is_pcview(nd)) {
		WBUFW(buf,25)=nd->hair;
		WBUFL(buf,27)=0;
		WBUFL(buf,31)=0;
		WBUFW(buf,35)=nd->head_bottom;
		WBUFW(buf,37)=nd->head_top;
		WBUFW(buf,39)=nd->head_mid;
		WBUFW(buf,41)=nd->hair_color;
		WBUFW(buf,43)=nd->clothes_color;
		WBUFW(buf,45)=0;
		WBUFW(buf,47)=nd->robe;
		WBUFB(buf,62)=nd->sex;
		WBUFW(buf,82)=nd->style;
	}
	if( nd->subtype != WARP &&
	    nd->class_ == WARP_DEBUG_CLASS &&
	    nd->u.scr.guild_id > 0 &&
	    (g = guild_search(nd->u.scr.guild_id)) )
	{
		WBUFL(buf,39)=g->guild_id;
		WBUFL(buf,49)=g->guild_id;
		WBUFW(buf,53)=g->emblem_id;
	}
	WBUFPOS(buf,63,nd->bl.x,nd->bl.y,nd->dir);
	WBUFW(buf,69)=1;
	WBUFL(buf,73) = 0xffffffff;
	WBUFL(buf,77) = 0xffffffff;
	WBUFB(buf,81) = 0;
	strncpy(WBUFP(buf,84),nd->name,24);
#endif
	return len;
}

/*==========================================
 *
 *------------------------------------------
 */
static int clif_npc007b(struct npc_data *nd,unsigned char *buf,struct map_session_data* sd)
{
	int len;
	unsigned int tick = gettick();
	int option = nd->option;

	nullpo_retr(0, nd);

	if(sd && option&OPTION_CLOAKING) {
		int i;
		for(i=0; i < MAX_CLOAKEDNPC; i++) {
			if(sd->cloaked_npc[i] == nd->bl.id) {
				option &= ~OPTION_CLOAKING;
				break;
			}
		}
	}

#if PACKETVER < 20180704
	len = 86 + (int)strlen(nd->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9fd;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=(nd->u.scr.moveable > 0)? 12: 6;
	WBUFL(buf,5)=nd->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=nd->speed;
	WBUFL(buf,19)=option;
	WBUFW(buf,23)=nd->class_;
	if(npc_is_pcview(nd)) {
		WBUFW(buf,25)=nd->hair;
		WBUFL(buf,27)=0;
		WBUFL(buf,29)=0;
		WBUFW(buf,31)=nd->head_bottom;
		WBUFW(buf,37)=nd->head_top;
		WBUFW(buf,39)=nd->head_mid;
		WBUFW(buf,41)=nd->hair_color;
		WBUFW(buf,43)=nd->clothes_color;
		WBUFW(buf,45)=0;
		WBUFW(buf,47)=nd->robe;
		WBUFB(buf,62)=nd->sex;
		WBUFW(buf,84)=nd->style;
	}
	WBUFL(buf,33)=tick;
	WBUFPOS2(buf,63,nd->bl.x,nd->bl.y,nd->ud.to_x,nd->ud.to_y,8,8);
	WBUFL(buf,75) = 0xffffffff;
	WBUFL(buf,79) = 0xffffffff;
	WBUFB(buf,83) = 0;
	strncpy(WBUFP(buf,86),nd->name,24);
#else
	len = 90 + (int)strlen(nd->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9fd;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=(nd->u.scr.moveable > 0)? 12: 6;
	WBUFL(buf,5)=nd->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=nd->speed;
	WBUFL(buf,19)=option;
	WBUFW(buf,23)=nd->class_;
	if(npc_is_pcview(nd)) {
		WBUFW(buf,25)=nd->hair;
		WBUFL(buf,27)=0;
		WBUFL(buf,31)=0;
		WBUFW(buf,35)=nd->head_bottom;
		WBUFW(buf,41)=nd->head_top;
		WBUFW(buf,43)=nd->head_mid;
		WBUFW(buf,45)=nd->hair_color;
		WBUFW(buf,47)=nd->clothes_color;
		WBUFW(buf,49)=0;
		WBUFW(buf,51)=nd->robe;
		WBUFB(buf,66)=nd->sex;
		WBUFW(buf,88)=nd->style;
	}
	WBUFL(buf,37)=tick;
	WBUFPOS2(buf,67,nd->bl.x,nd->bl.y,nd->ud.to_x,nd->ud.to_y,8,8);
	WBUFL(buf,79) = 0xffffffff;
	WBUFL(buf,83) = 0xffffffff;
	WBUFB(buf,87) = 0;
	strncpy(WBUFP(buf,90),nd->name,24);
#endif
	return len;
}

/*==========================================
 *
 *------------------------------------------
 */
static int clif_pet0078(struct pet_data *pd,unsigned char *buf)
{
	int len, view;

	nullpo_retr(0, pd);

	if(mob_is_pcview(pd->class_)) {
#if PACKETVER < 4
		len = packet_db[0x78].len;
		memset(buf,0,len);

		WBUFW(buf,0)=0x78;
		WBUFL(buf,2)=pd->bl.id;
		WBUFW(buf,6)=pd->speed;
		WBUFW(buf,12)=mobdb_search(pd->class_)->option;
		WBUFW(buf,14)=mob_get_viewclass(pd->class_);
		WBUFW(buf,16)=mob_get_hair(pd->class_);
		WBUFW(buf,18)=mob_get_weapon(pd->class_);
		WBUFW(buf,20)=mob_get_head_bottom(pd->class_);
		WBUFW(buf,22)=mob_get_shield(pd->class_);
		WBUFW(buf,24)=mob_get_head_top(pd->class_);
		WBUFW(buf,26)=mob_get_head_mid(pd->class_);
		WBUFW(buf,28)=mob_get_hair_color(pd->class_);
		WBUFW(buf,30)=mob_get_clothes_color(pd->class_);
		WBUFB(buf,45)=mob_get_sex(pd->class_);
		WBUFPOS(buf,46,pd->bl.x,pd->bl.y,pd->dir);
		WBUFB(buf,49)=0;
		WBUFB(buf,50)=0;
		WBUFLV(buf,52,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
#elif PACKETVER < 7
		len = packet_db[0x1d8].len;
		memset(buf,0,len);

		WBUFW(buf,0)=0x1d8;
		WBUFL(buf,2)=pd->bl.id;
		WBUFW(buf,6)=pd->speed;
		WBUFW(buf,12)=mobdb_search(pd->class_)->option;
		WBUFW(buf,14)=mob_get_viewclass(pd->class_);
		WBUFW(buf,16)=mob_get_hair(pd->class_);
		WBUFW(buf,18)=mob_get_weapon(pd->class_);
		WBUFW(buf,20)=mob_get_shield(pd->class_);
		WBUFW(buf,22)=mob_get_head_bottom(pd->class_);
		WBUFW(buf,24)=mob_get_head_top(pd->class_);
		WBUFW(buf,26)=mob_get_head_mid(pd->class_);
		WBUFW(buf,28)=mob_get_hair_color(pd->class_);
		WBUFW(buf,30)=mob_get_clothes_color(pd->class_);
		WBUFB(buf,45)=mob_get_sex(pd->class_);
		WBUFPOS(buf,46,pd->bl.x,pd->bl.y,pd->dir);
		WBUFB(buf,49)=0;
		WBUFB(buf,50)=0;
		WBUFLV(buf,52,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
#elif PACKETVER < 20080102
		len = packet_db[0x22a].len;
		memset(buf,0,len);

		WBUFW(buf,0)=0x22a;
		WBUFL(buf,2)=pd->bl.id;
		WBUFW(buf,6)=pd->speed;
		WBUFL(buf,12)=mobdb_search(pd->class_)->option;
		WBUFW(buf,16)=mob_get_viewclass(pd->class_);
		WBUFW(buf,18)=mob_get_hair(pd->class_);
		WBUFW(buf,20)=mob_get_weapon(pd->class_);
		WBUFW(buf,22)=mob_get_shield(pd->class_);
		WBUFW(buf,24)=mob_get_head_bottom(pd->class_);
		WBUFW(buf,26)=mob_get_head_top(pd->class_);
		WBUFW(buf,28)=mob_get_head_mid(pd->class_);
		WBUFW(buf,30)=mob_get_hair_color(pd->class_);
		WBUFW(buf,32)=mob_get_clothes_color(pd->class_);
		WBUFB(buf,49)=mob_get_sex(pd->class_);
		WBUFPOS(buf,50,pd->bl.x,pd->bl.y,pd->dir);
		WBUFB(buf,53)=0;
		WBUFB(buf,54)=0;
		WBUFLV(buf,56,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
#elif PACKETVER < 20091104
		len = packet_db[0x2ee].len;
		memset(buf,0,len);

		WBUFW(buf,0)=0x2ee;
		WBUFL(buf,2)=pd->bl.id;
		WBUFW(buf,6)=pd->speed;
		WBUFL(buf,12)=mobdb_search(pd->class_)->option;
		WBUFW(buf,16)=mob_get_viewclass(pd->class_);
		WBUFW(buf,18)=mob_get_hair(pd->class_);
		WBUFW(buf,20)=mob_get_weapon(pd->class_);
		WBUFW(buf,22)=mob_get_shield(pd->class_);
		WBUFW(buf,24)=mob_get_head_bottom(pd->class_);
		WBUFW(buf,26)=mob_get_head_top(pd->class_);
		WBUFW(buf,28)=mob_get_head_mid(pd->class_);
		WBUFW(buf,30)=mob_get_hair_color(pd->class_);
		WBUFW(buf,32)=mob_get_clothes_color(pd->class_);
		WBUFB(buf,49)=mob_get_sex(pd->class_);
		WBUFPOS(buf,50,pd->bl.x,pd->bl.y,pd->dir);
		WBUFB(buf,53)=0;
		WBUFB(buf,54)=0;
		WBUFLV(buf,56,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
		WBUFW(buf,58)=0;
#elif PACKETVER < 20110111
		len = 63 + (int)strlen(pd->name);
		memset(buf,0,len);

		WBUFW(buf,0)=0x7f9;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=0;
		WBUFL(buf,5)=pd->bl.id;
		WBUFW(buf,9)=pd->speed;
		WBUFL(buf,15)=mobdb_search(pd->class_)->option;
		WBUFW(buf,19)=mob_get_viewclass(pd->class_);
		WBUFW(buf,21)=mob_get_hair(pd->class_);
		WBUFW(buf,23)=mob_get_weapon(pd->class_);
		WBUFW(buf,25)=mob_get_shield(pd->class_);
		WBUFW(buf,27)=mob_get_head_bottom(pd->class_);
		WBUFW(buf,29)=mob_get_head_top(pd->class_);
		WBUFW(buf,31)=mob_get_head_mid(pd->class_);
		WBUFW(buf,33)=mob_get_hair_color(pd->class_);
		WBUFW(buf,35)=mob_get_clothes_color(pd->class_);
		WBUFB(buf,52)=mob_get_sex(pd->class_);
		WBUFPOS(buf,53,pd->bl.x,pd->bl.y,pd->dir);
		WBUFB(buf,56)=5;
		WBUFB(buf,57)=5;
		WBUFLV(buf,59,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
		strncpy(WBUFP(buf,63),pd->name,24);
#elif PACKETVER < 20120328
		len = 65 + (int)strlen(pd->name);
		memset(buf,0,len);

		WBUFW(buf,0)=0x857;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=0;
		WBUFL(buf,5)=pd->bl.id;
		WBUFW(buf,9)=pd->speed;
		WBUFL(buf,15)=mobdb_search(pd->class_)->option;
		WBUFW(buf,19)=mob_get_viewclass(pd->class_);
		WBUFW(buf,21)=mob_get_hair(pd->class_);
		WBUFW(buf,23)=mob_get_weapon(pd->class_);
		WBUFW(buf,25)=mob_get_shield(pd->class_);
		WBUFW(buf,27)=mob_get_head_bottom(pd->class_);
		WBUFW(buf,29)=mob_get_head_top(pd->class_);
		WBUFW(buf,31)=mob_get_head_mid(pd->class_);
		WBUFW(buf,33)=mob_get_hair_color(pd->class_);
		WBUFW(buf,35)=mob_get_clothes_color(pd->class_);
		WBUFW(buf,39)=mob_get_robe(pd->class_);
		WBUFB(buf,54)=mob_get_sex(pd->class_);
		WBUFPOS(buf,55,pd->bl.x,pd->bl.y,pd->dir);
		WBUFB(buf,58)=5;
		WBUFB(buf,59)=5;
		WBUFLV(buf,61,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
		strncpy(WBUFP(buf,65),pd->name,24);
#elif PACKETVER < 20131223
		len = 74;
		memset(buf,0,len);

		WBUFW(buf,0)=0x915;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=0;
		WBUFL(buf,5)=pd->bl.id;
		WBUFW(buf,9)=pd->speed;
		WBUFL(buf,15)=mobdb_search(pd->class_)->option;
		WBUFW(buf,19)=mob_get_viewclass(pd->class_);
		WBUFW(buf,21)=mob_get_hair(pd->class_);
		WBUFW(buf,23)=mob_get_weapon(pd->class_);
		WBUFW(buf,25)=mob_get_shield(pd->class_);
		WBUFW(buf,27)=mob_get_head_bottom(pd->class_);
		WBUFW(buf,29)=mob_get_head_top(pd->class_);
		WBUFW(buf,31)=mob_get_head_mid(pd->class_);
		WBUFW(buf,33)=mob_get_hair_color(pd->class_);
		WBUFW(buf,35)=mob_get_clothes_color(pd->class_);
		WBUFW(buf,39)=mob_get_robe(pd->class_);
		WBUFB(buf,54)=mob_get_sex(pd->class_);
		WBUFPOS(buf,55,pd->bl.x,pd->bl.y,pd->dir);
		WBUFB(buf,58)=5;
		WBUFB(buf,59)=5;
		WBUFLV(buf,61,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
		WBUFL(buf,65) = 0xffffffff;
		WBUFL(buf,69) = 0xffffffff;
		WBUFB(buf,73) = 0;
#elif PACKETVER < 20150513
		len = 78 + (int)strlen(pd->name);
		memset(buf,0,len);

		WBUFW(buf,0)=0x9dd;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=0;
		WBUFL(buf,5)=pd->bl.id;
		WBUFL(buf,9)=0;
		WBUFW(buf,13)=pd->speed;
		WBUFL(buf,19)=mobdb_search(pd->class_)->option;
		WBUFW(buf,23)=mob_get_viewclass(pd->class_);
		WBUFW(buf,25)=mob_get_hair(pd->class_);
		WBUFW(buf,27)=mob_get_weapon(pd->class_);
		WBUFW(buf,29)=mob_get_shield(pd->class_);
		WBUFW(buf,31)=mob_get_head_bottom(pd->class_);
		WBUFW(buf,33)=mob_get_head_top(pd->class_);
		WBUFW(buf,35)=mob_get_head_mid(pd->class_);
		WBUFW(buf,37)=mob_get_hair_color(pd->class_);
		WBUFW(buf,39)=mob_get_clothes_color(pd->class_);
		WBUFW(buf,43)=mob_get_robe(pd->class_);
		WBUFB(buf,58)=mob_get_sex(pd->class_);
		WBUFPOS(buf,59,pd->bl.x,pd->bl.y,pd->dir);
		WBUFB(buf,62)=5;
		WBUFB(buf,63)=5;
		WBUFLV(buf,65,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
		WBUFL(buf,69) = 0xffffffff;
		WBUFL(buf,73) = 0xffffffff;
		WBUFB(buf,77) = 0;
		strncpy(WBUFP(buf,78),pd->name,24);
#elif PACKETVER < 20180704
		len = 80 + (int)strlen(pd->name);
		memset(buf,0,len);

		WBUFW(buf,0)=0x9ff;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=0;
		WBUFL(buf,5)=pd->bl.id;
		WBUFL(buf,9)=0;
		WBUFW(buf,13)=pd->speed;
		WBUFL(buf,19)=mobdb_search(pd->class_)->option;
		WBUFW(buf,23)=mob_get_viewclass(pd->class_);
		WBUFW(buf,25)=mob_get_hair(pd->class_);
		WBUFW(buf,27)=mob_get_weapon(pd->class_);
		WBUFW(buf,29)=mob_get_shield(pd->class_);
		WBUFW(buf,31)=mob_get_head_bottom(pd->class_);
		WBUFW(buf,33)=mob_get_head_top(pd->class_);
		WBUFW(buf,35)=mob_get_head_mid(pd->class_);
		WBUFW(buf,37)=mob_get_hair_color(pd->class_);
		WBUFW(buf,39)=mob_get_clothes_color(pd->class_);
		WBUFW(buf,43)=mob_get_robe(pd->class_);
		WBUFB(buf,58)=mob_get_sex(pd->class_);
		WBUFPOS(buf,59,pd->bl.x,pd->bl.y,pd->dir);
		WBUFB(buf,62)=5;
		WBUFB(buf,63)=5;
		WBUFLV(buf,65,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
		WBUFL(buf,69) = 0xffffffff;
		WBUFL(buf,73) = 0xffffffff;
		WBUFB(buf,77) = 0;
		WBUFW(buf,78) = 0;
		strncpy(WBUFP(buf,80),pd->name,24);
#else
		len = 84 + (int)strlen(pd->name);
		memset(buf,0,len);

		WBUFW(buf,0)=0x9ff;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=0;
		WBUFL(buf,5)=pd->bl.id;
		WBUFL(buf,9)=0;
		WBUFW(buf,13)=pd->speed;
		WBUFL(buf,19)=mobdb_search(pd->class_)->option;
		WBUFW(buf,23)=mob_get_viewclass(pd->class_);
		WBUFW(buf,25)=mob_get_hair(pd->class_);
		WBUFL(buf,27)=mob_get_weapon(pd->class_);
		WBUFL(buf,31)=mob_get_shield(pd->class_);
		WBUFW(buf,35)=mob_get_head_bottom(pd->class_);
		WBUFW(buf,37)=mob_get_head_top(pd->class_);
		WBUFW(buf,39)=mob_get_head_mid(pd->class_);
		WBUFW(buf,41)=mob_get_hair_color(pd->class_);
		WBUFW(buf,43)=mob_get_clothes_color(pd->class_);
		WBUFW(buf,47)=mob_get_robe(pd->class_);
		WBUFB(buf,62)=mob_get_sex(pd->class_);
		WBUFPOS(buf,63,pd->bl.x,pd->bl.y,pd->dir);
		WBUFB(buf,66)=5;
		WBUFB(buf,67)=5;
		WBUFLV(buf,69,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
		WBUFL(buf,73) = 0xffffffff;
		WBUFL(buf,77) = 0xffffffff;
		WBUFB(buf,81) = 0;
		WBUFW(buf,82) = 0;
		strncpy(WBUFP(buf,84),pd->name,24);
#endif
		return len;
	}
#if PACKETVER < 20071106
	len = packet_db[0x78].len;
	memset(buf,0,len);

	WBUFW(buf,0)=0x78;
	WBUFL(buf,2)=pd->bl.id;
	WBUFW(buf,6)=pd->speed;
	WBUFW(buf,14)=mob_get_viewclass(pd->class_);
	WBUFW(buf,16)=battle_config.pet0078_hair_id;
	if((view = itemdb_viewid(pd->equip)) > 0)
		WBUFW(buf,20)=view;
	else
		WBUFW(buf,20)=pd->equip;
	WBUFPOS(buf,46,pd->bl.x,pd->bl.y,pd->dir);
	WBUFB(buf,49)=0;
	WBUFB(buf,50)=0;
	WBUFLV(buf,52,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
#elif PACKETVER < 20091104
	len = packet_db[0x78].len;
	memset(buf,0,len);

	WBUFW(buf,0)=0x78;
	WBUFB(buf,2)=0;
	WBUFL(buf,3)=pd->bl.id;
	WBUFW(buf,7)=pd->speed;
	WBUFW(buf,15)=mob_get_viewclass(pd->class_);
	WBUFW(buf,17)=battle_config.pet0078_hair_id;
	if((view = itemdb_viewid(pd->equip)) > 0)
		WBUFW(buf,21)=view;
	else
		WBUFW(buf,21)=pd->equip;
	WBUFPOS(buf,47,pd->bl.x,pd->bl.y,pd->dir);
	WBUFB(buf,50)=0;
	WBUFB(buf,51)=0;
	WBUFLV(buf,53,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
#elif PACKETVER < 20110111
	len = 63 + (int)strlen(pd->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x7f9;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=7;
	WBUFL(buf,5)=pd->bl.id;
	WBUFW(buf,9)=pd->speed;
	WBUFW(buf,19)=mob_get_viewclass(pd->class_);
	WBUFW(buf,21)=100;	// ���ׂ�����Œ�
	if((view = itemdb_viewid(pd->equip)) > 0)
		WBUFW(buf,27)=view;
	else
		WBUFW(buf,27)=pd->equip;
	WBUFPOS(buf,53,pd->bl.x,pd->bl.y,pd->dir);
	WBUFLV(buf,59,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
	strncpy(WBUFP(buf,63),pd->name,24);
#elif PACKETVER < 20120328
	len = 65 + (int)strlen(pd->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x857;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=7;
	WBUFL(buf,5)=pd->bl.id;
	WBUFW(buf,9)=pd->speed;
	WBUFW(buf,19)=mob_get_viewclass(pd->class_);
	WBUFW(buf,21)=100;	// ���ׂ�����Œ�
	if((view = itemdb_viewid(pd->equip)) > 0)
		WBUFW(buf,27)=view;
	else
		WBUFW(buf,27)=pd->equip;
	WBUFPOS(buf,55,pd->bl.x,pd->bl.y,pd->dir);
	WBUFLV(buf,61,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
	strncpy(WBUFP(buf,65),pd->name,24);
#elif PACKETVER < 20131223
	len = 74;
	memset(buf,0,len);

	WBUFW(buf,0)=0x915;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=7;
	WBUFL(buf,5)=pd->bl.id;
	WBUFW(buf,9)=pd->speed;
	WBUFW(buf,19)=mob_get_viewclass(pd->class_);
	WBUFW(buf,21)=100;	// ���ׂ�����Œ�
	if((view = itemdb_viewid(pd->equip)) > 0)
		WBUFW(buf,27)=view;
	else
		WBUFW(buf,27)=pd->equip;
	WBUFPOS(buf,55,pd->bl.x,pd->bl.y,pd->dir);
	WBUFLV(buf,61,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
	WBUFL(buf,65) = 0xffffffff;
	WBUFL(buf,69) = 0xffffffff;
	WBUFB(buf,73) = 0;
#elif PACKETVER < 20150513
	len = 78 + (int)strlen(pd->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9dd;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=7;
	WBUFL(buf,5)=pd->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=pd->speed;
	WBUFW(buf,23)=mob_get_viewclass(pd->class_);
	WBUFW(buf,25)=100;	// ���ׂ�����Œ�
	if((view = itemdb_viewid(pd->equip)) > 0)
		WBUFW(buf,31)=view;
	else
		WBUFW(buf,31)=pd->equip;
	WBUFPOS(buf,59,pd->bl.x,pd->bl.y,pd->dir);
	WBUFLV(buf,65,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
	WBUFL(buf,69) = 0xffffffff;
	WBUFL(buf,73) = 0xffffffff;
	WBUFB(buf,77) = 0;
	strncpy(WBUFP(buf,78),pd->name,24);
#elif PACKETVER < 20180704
	len = 80 + (int)strlen(pd->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9ff;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=7;
	WBUFL(buf,5)=pd->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=pd->speed;
	WBUFW(buf,23)=mob_get_viewclass(pd->class_);
	WBUFW(buf,25)=100;	// ���ׂ�����Œ�
	if((view = itemdb_viewid(pd->equip)) > 0)
		WBUFW(buf,31)=view;
	else
		WBUFW(buf,31)=pd->equip;
	WBUFPOS(buf,59,pd->bl.x,pd->bl.y,pd->dir);
	WBUFLV(buf,65,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
	WBUFL(buf,69) = 0xffffffff;
	WBUFL(buf,73) = 0xffffffff;
	WBUFB(buf,77) = 0;
	WBUFW(buf,78) = 0;
	strncpy(WBUFP(buf,80),pd->name,24);
#else
	len = 84 + (int)strlen(pd->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9ff;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=7;
	WBUFL(buf,5)=pd->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=pd->speed;
	WBUFW(buf,23)=mob_get_viewclass(pd->class_);
	WBUFW(buf,25)=100;	// ���ׂ�����Œ�
	if((view = itemdb_viewid(pd->equip)) > 0)
		WBUFW(buf,35)=view;
	else
		WBUFW(buf,35)=pd->equip;
	WBUFPOS(buf,63,pd->bl.x,pd->bl.y,pd->dir);
	WBUFLV(buf,69,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
	WBUFL(buf,73) = 0xffffffff;
	WBUFL(buf,77) = 0xffffffff;
	WBUFB(buf,81) = 0;
	WBUFW(buf,82) = 0;
	strncpy(WBUFP(buf,84),pd->name,24);
#endif
	return len;
}

/*==========================================
 *
 *------------------------------------------
 */
static int clif_pet007b(struct pet_data *pd,unsigned char *buf)
{
	int len, view;
	unsigned int tick = gettick();

	nullpo_retr(0, pd);

	if(mob_is_pcview(pd->class_)) {
#if PACKETVER < 4
		len = packet_db[0x7b].len;
		memset(buf,0,len);

		WBUFW(buf,0)=0x7b;
		WBUFL(buf,2)=pd->bl.id;
		WBUFW(buf,6)=pd->speed;
		WBUFW(buf,12)=mobdb_search(pd->class_)->option;
		WBUFW(buf,14)=mob_get_viewclass(pd->class_);
		WBUFW(buf,16)=mob_get_hair(pd->class_);
		WBUFW(buf,18)=mob_get_weapon(pd->class_);
		WBUFW(buf,20)=mob_get_head_bottom(pd->class_);
		WBUFL(buf,22)=tick;
		WBUFW(buf,26)=mob_get_shield(pd->class_);
		WBUFW(buf,28)=mob_get_head_top(pd->class_);
		WBUFW(buf,30)=mob_get_head_mid(pd->class_);
		WBUFW(buf,32)=mob_get_hair_color(pd->class_);
		WBUFW(buf,34)=mob_get_clothes_color(pd->class_);
		WBUFB(buf,49)=mob_get_sex(pd->class_);
		WBUFPOS2(buf,50,pd->bl.x,pd->bl.y,pd->ud.to_x,pd->ud.to_y,8,8);
		WBUFB(buf,56)=0;
		WBUFB(buf,57)=0;
		WBUFLV(buf,58,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
#elif PACKETVER < 7
		len = packet_db[0x1da].len;
		memset(buf,0,len);

		WBUFW(buf,0)=0x1da;
		WBUFL(buf,2)=pd->bl.id;
		WBUFW(buf,6)=pd->speed;
		WBUFW(buf,12)=mobdb_search(pd->class_)->option;
		WBUFW(buf,14)=mob_get_viewclass(pd->class_);
		WBUFW(buf,16)=mob_get_hair(pd->class_);
		WBUFW(buf,18)=mob_get_weapon(pd->class_);
		WBUFW(buf,20)=mob_get_shield(pd->class_);
		WBUFW(buf,22)=mob_get_head_bottom(pd->class_);
		WBUFL(buf,24)=tick;
		WBUFW(buf,28)=mob_get_head_top(pd->class_);
		WBUFW(buf,30)=mob_get_head_mid(pd->class_);
		WBUFW(buf,32)=mob_get_hair_color(pd->class_);
		WBUFW(buf,34)=mob_get_clothes_color(pd->class_);
		WBUFB(buf,49)=mob_get_sex(pd->class_);
		WBUFPOS2(buf,50,pd->bl.x,pd->bl.y,pd->ud.to_x,pd->ud.to_y,8,8);
		WBUFB(buf,56)=0;
		WBUFB(buf,57)=0;
		WBUFLV(buf,58,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
#elif PACKETVER < 20071106
		len = packet_db[0x22c].len;
		memset(buf,0,len);

		WBUFW(buf,0)=0x22c;
		WBUFL(buf,2)=pd->bl.id;
		WBUFW(buf,6)=pd->speed;
		WBUFL(buf,12)=mobdb_search(pd->class_)->option;
		WBUFW(buf,16)=mob_get_viewclass(pd->class_);
		WBUFW(buf,18)=mob_get_hair(pd->class_);
		WBUFW(buf,20)=mob_get_weapon(pd->class_);
		WBUFW(buf,22)=mob_get_shield(pd->class_);
		WBUFW(buf,24)=mob_get_head_bottom(pd->class_);
		WBUFL(buf,26)=tick;
		WBUFW(buf,30)=mob_get_head_top(pd->class_);
		WBUFW(buf,32)=mob_get_head_mid(pd->class_);
		WBUFW(buf,34)=mob_get_hair_color(pd->class_);
		WBUFW(buf,36)=mob_get_clothes_color(pd->class_);
		WBUFB(buf,53)=mob_get_sex(pd->class_);
		WBUFPOS2(buf,54,pd->bl.x,pd->bl.y,pd->ud.to_x,pd->ud.to_y,8,8);
		WBUFB(buf,60)=0;
		WBUFB(buf,61)=0;
		WBUFLV(buf,62,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
#elif PACKETVER < 20080102
		len = packet_db[0x22c].len;
		memset(buf,0,len);

		WBUFW(buf,0)=0x22c;
		WBUFB(buf,2)=0;
		WBUFL(buf,3)=pd->bl.id;
		WBUFW(buf,7)=pd->speed;
		WBUFL(buf,13)=mobdb_search(pd->class_)->option;
		WBUFW(buf,17)=mob_get_viewclass(pd->class_);
		WBUFW(buf,19)=mob_get_hair(pd->class_);
		WBUFW(buf,21)=mob_get_weapon(pd->class_);
		WBUFW(buf,23)=mob_get_shield(pd->class_);
		WBUFW(buf,25)=mob_get_head_bottom(pd->class_);
		WBUFL(buf,27)=tick;
		WBUFW(buf,31)=mob_get_head_top(pd->class_);
		WBUFW(buf,33)=mob_get_head_mid(pd->class_);
		WBUFW(buf,35)=mob_get_hair_color(pd->class_);
		WBUFW(buf,37)=mob_get_clothes_color(pd->class_);
		WBUFB(buf,54)=mob_get_sex(pd->class_);
		WBUFPOS2(buf,55,pd->bl.x,pd->bl.y,pd->ud.to_x,pd->ud.to_y,8,8);
		WBUFB(buf,61)=0;
		WBUFB(buf,62)=0;
		WBUFLV(buf,63,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
#elif PACKETVER < 20091104
		len = packet_db[0x2ec].len;
		memset(buf,0,len);

		WBUFW(buf,0)=0x2ec;
		WBUFB(buf,2)=0;
		WBUFL(buf,3)=pd->bl.id;
		WBUFW(buf,7)=pd->speed;
		WBUFL(buf,13)=mobdb_search(pd->class_)->option;
		WBUFW(buf,17)=mob_get_viewclass(pd->class_);
		WBUFW(buf,19)=mob_get_hair(pd->class_);
		WBUFW(buf,21)=mob_get_weapon(pd->class_);
		WBUFW(buf,23)=mob_get_shield(pd->class_);
		WBUFW(buf,25)=mob_get_head_bottom(pd->class_);
		WBUFL(buf,27)=tick;
		WBUFW(buf,31)=mob_get_head_top(pd->class_);
		WBUFW(buf,33)=mob_get_head_mid(pd->class_);
		WBUFW(buf,35)=mob_get_hair_color(pd->class_);
		WBUFW(buf,37)=mob_get_clothes_color(pd->class_);
		WBUFB(buf,54)=mob_get_sex(pd->class_);
		WBUFPOS2(buf,55,pd->bl.x,pd->bl.y,pd->ud.to_x,pd->ud.to_y,8,8);
		WBUFB(buf,61)=0;
		WBUFB(buf,62)=0;
		WBUFLV(buf,63,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
		WBUFW(buf,65)=0;
#elif PACKETVER < 20110111
		len = 69 + (int)strlen(pd->name);
		memset(buf,0,len);

		WBUFW(buf,0)=0x7f7;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=0;
		WBUFL(buf,5)=pd->bl.id;
		WBUFW(buf,9)=pd->speed;
		WBUFL(buf,15)=mobdb_search(pd->class_)->option;
		WBUFW(buf,19)=mob_get_viewclass(pd->class_);
		WBUFW(buf,21)=mob_get_hair(pd->class_);
		WBUFW(buf,23)=mob_get_weapon(pd->class_);
		WBUFW(buf,25)=mob_get_shield(pd->class_);
		WBUFW(buf,27)=mob_get_head_bottom(pd->class_);
		WBUFL(buf,29)=tick;
		WBUFW(buf,33)=mob_get_head_top(pd->class_);
		WBUFW(buf,35)=mob_get_head_mid(pd->class_);
		WBUFW(buf,37)=mob_get_hair_color(pd->class_);
		WBUFW(buf,39)=mob_get_clothes_color(pd->class_);
		WBUFB(buf,56)=mob_get_sex(pd->class_);
		WBUFPOS2(buf,57,pd->bl.x,pd->bl.y,pd->ud.to_x,pd->ud.to_y,8,8);
		WBUFB(buf,63)=5;
		WBUFB(buf,64)=5;
		WBUFLV(buf,65,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
		strncpy(WBUFP(buf,69),pd->name,24);
#elif PACKETVER < 20120328
		len = 71 + (int)strlen(pd->name);
		memset(buf,0,len);

		WBUFW(buf,0)=0x856;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=0;
		WBUFL(buf,5)=pd->bl.id;
		WBUFW(buf,9)=pd->speed;
		WBUFL(buf,15)=mobdb_search(pd->class_)->option;
		WBUFW(buf,19)=mob_get_viewclass(pd->class_);
		WBUFW(buf,21)=mob_get_hair(pd->class_);
		WBUFW(buf,23)=mob_get_weapon(pd->class_);
		WBUFW(buf,25)=mob_get_shield(pd->class_);
		WBUFW(buf,27)=mob_get_head_bottom(pd->class_);
		WBUFL(buf,29)=tick;
		WBUFW(buf,33)=mob_get_head_top(pd->class_);
		WBUFW(buf,35)=mob_get_head_mid(pd->class_);
		WBUFW(buf,37)=mob_get_hair_color(pd->class_);
		WBUFW(buf,39)=mob_get_clothes_color(pd->class_);
		WBUFW(buf,43)=mob_get_robe(pd->class_);
		WBUFB(buf,58)=mob_get_sex(pd->class_);
		WBUFPOS2(buf,59,pd->bl.x,pd->bl.y,pd->ud.to_x,pd->ud.to_y,8,8);
		WBUFB(buf,65)=5;
		WBUFB(buf,66)=5;
		WBUFLV(buf,67,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
		strncpy(WBUFP(buf,71),pd->name,24);
#elif PACKETVER < 20131223
		len = 80;
		memset(buf,0,len);

		WBUFW(buf,0)=0x914;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=0;
		WBUFL(buf,5)=pd->bl.id;
		WBUFW(buf,9)=pd->speed;
		WBUFL(buf,15)=mobdb_search(pd->class_)->option;
		WBUFW(buf,19)=mob_get_viewclass(pd->class_);
		WBUFW(buf,21)=mob_get_hair(pd->class_);
		WBUFW(buf,23)=mob_get_weapon(pd->class_);
		WBUFW(buf,25)=mob_get_shield(pd->class_);
		WBUFW(buf,27)=mob_get_head_bottom(pd->class_);
		WBUFL(buf,29)=tick;
		WBUFW(buf,33)=mob_get_head_top(pd->class_);
		WBUFW(buf,35)=mob_get_head_mid(pd->class_);
		WBUFW(buf,37)=mob_get_hair_color(pd->class_);
		WBUFW(buf,39)=mob_get_clothes_color(pd->class_);
		WBUFW(buf,43)=mob_get_robe(pd->class_);
		WBUFB(buf,58)=mob_get_sex(pd->class_);
		WBUFPOS2(buf,59,pd->bl.x,pd->bl.y,pd->ud.to_x,pd->ud.to_y,8,8);
		WBUFB(buf,65)=5;
		WBUFB(buf,66)=5;
		WBUFLV(buf,67,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
		WBUFL(buf,71) = 0xffffffff;
		WBUFL(buf,75) = 0xffffffff;
		WBUFB(buf,79) = 0;
#elif PACKETVER < 20150513
		len = 84 + (int)strlen(pd->name);
		memset(buf,0,len);

		WBUFW(buf,0)=0x9db;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=0;
		WBUFL(buf,5)=pd->bl.id;
		WBUFL(buf,9)=0;
		WBUFW(buf,13)=pd->speed;
		WBUFL(buf,19)=mobdb_search(pd->class_)->option;
		WBUFW(buf,23)=mob_get_viewclass(pd->class_);
		WBUFW(buf,25)=mob_get_hair(pd->class_);
		WBUFW(buf,27)=mob_get_weapon(pd->class_);
		WBUFW(buf,29)=mob_get_shield(pd->class_);
		WBUFW(buf,31)=mob_get_head_bottom(pd->class_);
		WBUFL(buf,33)=tick;
		WBUFW(buf,37)=mob_get_head_top(pd->class_);
		WBUFW(buf,39)=mob_get_head_mid(pd->class_);
		WBUFW(buf,41)=mob_get_hair_color(pd->class_);
		WBUFW(buf,43)=mob_get_clothes_color(pd->class_);
		WBUFW(buf,47)=mob_get_robe(pd->class_);
		WBUFB(buf,62)=mob_get_sex(pd->class_);
		WBUFPOS2(buf,63,pd->bl.x,pd->bl.y,pd->ud.to_x,pd->ud.to_y,8,8);
		WBUFB(buf,69)=5;
		WBUFB(buf,70)=5;
		WBUFLV(buf,71,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
		WBUFL(buf,75) = 0xffffffff;
		WBUFL(buf,79) = 0xffffffff;
		WBUFB(buf,83) = 0;
		strncpy(WBUFP(buf,84),pd->name,24);
#elif PACKETVER < 20180704
		len = 86 + (int)strlen(pd->name);
		memset(buf,0,len);

		WBUFW(buf,0)=0x9fd;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=0;
		WBUFL(buf,5)=pd->bl.id;
		WBUFL(buf,9)=0;
		WBUFW(buf,13)=pd->speed;
		WBUFL(buf,19)=mobdb_search(pd->class_)->option;
		WBUFW(buf,23)=mob_get_viewclass(pd->class_);
		WBUFW(buf,25)=mob_get_hair(pd->class_);
		WBUFW(buf,27)=mob_get_weapon(pd->class_);
		WBUFW(buf,29)=mob_get_shield(pd->class_);
		WBUFW(buf,31)=mob_get_head_bottom(pd->class_);
		WBUFL(buf,33)=tick;
		WBUFW(buf,37)=mob_get_head_top(pd->class_);
		WBUFW(buf,39)=mob_get_head_mid(pd->class_);
		WBUFW(buf,41)=mob_get_hair_color(pd->class_);
		WBUFW(buf,43)=mob_get_clothes_color(pd->class_);
		WBUFW(buf,47)=mob_get_robe(pd->class_);
		WBUFB(buf,62)=mob_get_sex(pd->class_);
		WBUFPOS2(buf,63,pd->bl.x,pd->bl.y,pd->ud.to_x,pd->ud.to_y,8,8);
		WBUFB(buf,69)=5;
		WBUFB(buf,70)=5;
		WBUFLV(buf,71,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
		WBUFL(buf,75) = 0xffffffff;
		WBUFL(buf,79) = 0xffffffff;
		WBUFB(buf,83) = 0;
		WBUFW(buf,84) = mob_get_style(pd->class_);
		strncpy(WBUFP(buf,86),pd->name,24);
#else
		len = 90 + (int)strlen(pd->name);
		memset(buf,0,len);

		WBUFW(buf,0)=0x9fd;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=0;
		WBUFL(buf,5)=pd->bl.id;
		WBUFL(buf,9)=0;
		WBUFW(buf,13)=pd->speed;
		WBUFL(buf,19)=mobdb_search(pd->class_)->option;
		WBUFW(buf,23)=mob_get_viewclass(pd->class_);
		WBUFW(buf,25)=mob_get_hair(pd->class_);
		WBUFL(buf,27)=mob_get_weapon(pd->class_);
		WBUFL(buf,31)=mob_get_shield(pd->class_);
		WBUFW(buf,35)=mob_get_head_bottom(pd->class_);
		WBUFL(buf,37)=tick;
		WBUFW(buf,41)=mob_get_head_top(pd->class_);
		WBUFW(buf,43)=mob_get_head_mid(pd->class_);
		WBUFW(buf,45)=mob_get_hair_color(pd->class_);
		WBUFW(buf,47)=mob_get_clothes_color(pd->class_);
		WBUFW(buf,51)=mob_get_robe(pd->class_);
		WBUFB(buf,66)=mob_get_sex(pd->class_);
		WBUFPOS2(buf,67,pd->bl.x,pd->bl.y,pd->ud.to_x,pd->ud.to_y,8,8);
		WBUFB(buf,73)=5;
		WBUFB(buf,74)=5;
		WBUFLV(buf,75,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
		WBUFL(buf,79) = 0xffffffff;
		WBUFL(buf,83) = 0xffffffff;
		WBUFB(buf,87) = 0;
		WBUFW(buf,88) = mob_get_style(pd->class_);
		strncpy(WBUFP(buf,90),pd->name,24);
#endif
		return len;
	}
#if PACKETVER < 20091104
	len = packet_db[0x7b].len;
	memset(buf,0,len);

	WBUFW(buf,0)=0x7b;
	WBUFL(buf,2)=pd->bl.id;
	WBUFW(buf,6)=pd->speed;
	WBUFW(buf,14)=mob_get_viewclass(pd->class_);
	WBUFW(buf,16)=battle_config.pet0078_hair_id;
	if((view = itemdb_viewid(pd->equip)) > 0)
		WBUFW(buf,20)=view;
	else
		WBUFW(buf,20)=pd->equip;
	WBUFL(buf,22)=tick;
	WBUFPOS2(buf,50,pd->bl.x,pd->bl.y,pd->ud.to_x,pd->ud.to_y,8,8);
	WBUFB(buf,56)=0;
	WBUFB(buf,57)=0;
	WBUFLV(buf,58,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
#elif PACKETVER < 20110111
	len = 69 + (int)strlen(pd->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x7f7;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=7;
	WBUFL(buf,5)=pd->bl.id;
	WBUFW(buf,9)=pd->speed;
	WBUFW(buf,19)=mob_get_viewclass(pd->class_);
	WBUFW(buf,21)=100;	// ���ׂ�����ł͌Œ�
	if((view = itemdb_viewid(pd->equip)) > 0)
		WBUFW(buf,27)=view;
	else
		WBUFW(buf,27)=pd->equip;
	WBUFL(buf,29)=tick;
	WBUFPOS2(buf,57,pd->bl.x,pd->bl.y,pd->ud.to_x,pd->ud.to_y,8,8);
	WBUFLV(buf,65,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
	strncpy(WBUFP(buf,69),pd->name,24);
#elif PACKETVER < 20120328
	len = 71 + (int)strlen(pd->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x856;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=7;
	WBUFL(buf,5)=pd->bl.id;
	WBUFW(buf,9)=pd->speed;
	WBUFW(buf,19)=mob_get_viewclass(pd->class_);
	WBUFW(buf,21)=100;	// ���ׂ�����ł͌Œ�
	if((view = itemdb_viewid(pd->equip)) > 0)
		WBUFW(buf,27)=view;
	else
		WBUFW(buf,27)=pd->equip;
	WBUFL(buf,29)=tick;
	WBUFPOS2(buf,59,pd->bl.x,pd->bl.y,pd->ud.to_x,pd->ud.to_y,8,8);
	WBUFLV(buf,67,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
	strncpy(WBUFP(buf,71),pd->name,24);
#elif PACKETVER < 20131223
	len = 80;
	memset(buf,0,len);

	WBUFW(buf,0)=0x914;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=7;
	WBUFL(buf,5)=pd->bl.id;
	WBUFW(buf,9)=pd->speed;
	WBUFW(buf,19)=mob_get_viewclass(pd->class_);
	WBUFW(buf,21)=100;	// ���ׂ�����ł͌Œ�
	if((view = itemdb_viewid(pd->equip)) > 0)
		WBUFW(buf,27)=view;
	else
		WBUFW(buf,27)=pd->equip;
	WBUFL(buf,29)=tick;
	WBUFPOS2(buf,59,pd->bl.x,pd->bl.y,pd->ud.to_x,pd->ud.to_y,8,8);
	WBUFLV(buf,67,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
	WBUFL(buf,71) = 0xffffffff;
	WBUFL(buf,75) = 0xffffffff;
	WBUFB(buf,79) = 0;
#elif PACKETVER < 20150513
	len = 84 + (int)strlen(pd->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9db;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=7;
	WBUFL(buf,5)=pd->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=pd->speed;
	WBUFW(buf,23)=mob_get_viewclass(pd->class_);
	WBUFW(buf,25)=100;	// ���ׂ�����ł͌Œ�
	if((view = itemdb_viewid(pd->equip)) > 0)
		WBUFW(buf,31)=view;
	else
		WBUFW(buf,31)=pd->equip;
	WBUFL(buf,33)=tick;
	WBUFPOS2(buf,63,pd->bl.x,pd->bl.y,pd->ud.to_x,pd->ud.to_y,8,8);
	WBUFLV(buf,71,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
	WBUFL(buf,75) = 0xffffffff;
	WBUFL(buf,79) = 0xffffffff;
	WBUFB(buf,83) = 0;
	strncpy(WBUFP(buf,84),pd->name,24);
#elif PACKETVER < 20180704
	len = 86 + (int)strlen(pd->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9fd;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=7;
	WBUFL(buf,5)=pd->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=pd->speed;
	WBUFW(buf,23)=mob_get_viewclass(pd->class_);
	WBUFW(buf,25)=100;	// ���ׂ�����ł͌Œ�
	if((view = itemdb_viewid(pd->equip)) > 0)
		WBUFW(buf,31)=view;
	else
		WBUFW(buf,31)=pd->equip;
	WBUFL(buf,33)=tick;
	WBUFPOS2(buf,63,pd->bl.x,pd->bl.y,pd->ud.to_x,pd->ud.to_y,8,8);
	WBUFLV(buf,71,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
	WBUFL(buf,75) = 0xffffffff;
	WBUFL(buf,79) = 0xffffffff;
	WBUFB(buf,83) = 0;
	WBUFW(buf,84) = 0;
	strncpy(WBUFP(buf,86),pd->name,24);
#else
	len = 90 + (int)strlen(pd->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9fd;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=7;
	WBUFL(buf,5)=pd->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=pd->speed;
	WBUFW(buf,23)=mob_get_viewclass(pd->class_);
	WBUFW(buf,25)=100;	// ���ׂ�����ł͌Œ�
	if((view = itemdb_viewid(pd->equip)) > 0)
		WBUFW(buf,35)=view;
	else
		WBUFW(buf,35)=pd->equip;
	WBUFL(buf,37)=tick;
	WBUFPOS2(buf,67,pd->bl.x,pd->bl.y,pd->ud.to_x,pd->ud.to_y,8,8);
	WBUFLV(buf,75,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
	WBUFL(buf,79) = 0xffffffff;
	WBUFL(buf,83) = 0xffffffff;
	WBUFB(buf,87) = 0;
	WBUFW(buf,88) = 0;
	strncpy(WBUFP(buf,90),pd->name,24);
#endif
	return len;
}

/*==========================================
 *
 *------------------------------------------
 */
static int clif_hom0078(struct homun_data *hd,unsigned char *buf)
{
	int len;

	nullpo_retr(0, hd);

#if PACKETVER < 20071106
	len = packet_db[0x78].len;
	memset(buf,0,len);

	WBUFW(buf,0) =0x78;
	WBUFL(buf,2) =hd->bl.id;
	WBUFW(buf,6) =hd->speed;
	WBUFW(buf,8) =hd->sc.opt1;
	WBUFW(buf,10)=hd->sc.opt2;
	WBUFW(buf,12)=hd->sc.option;
	WBUFW(buf,14)=hd->view_class;
	WBUFW(buf,16)=battle_config.pet0078_hair_id;
	WBUFW(buf,20)=0;
	WBUFW(buf,42)=hd->sc.opt3;
	WBUFPOS(buf,46,hd->bl.x,hd->bl.y,hd->dir);
	WBUFB(buf,49)=0;
	WBUFB(buf,50)=0;
	WBUFLV(buf,52,status_get_lv(&hd->bl),hd->view_class);
#elif PACKETVER < 20091104
	len = packet_db[0x78].len;
	memset(buf,0,len);

	WBUFW(buf,0) =0x78;
	WBUFB(buf,2) =0;
	WBUFL(buf,3) =hd->bl.id;
	WBUFW(buf,7) =hd->speed;
	WBUFW(buf,9) =hd->sc.opt1;
	WBUFW(buf,11)=hd->sc.opt2;
	WBUFW(buf,13)=hd->sc.option;
	WBUFW(buf,15)=hd->view_class;
	WBUFW(buf,17)=battle_config.pet0078_hair_id;
	WBUFW(buf,21)=0;
	WBUFW(buf,43)=hd->sc.opt3;
	WBUFPOS(buf,47,hd->bl.x,hd->bl.y,hd->dir);
	WBUFB(buf,50)=0;
	WBUFB(buf,51)=0;
	WBUFLV(buf,53,status_get_lv(&hd->bl),hd->view_class);
#elif PACKETVER < 20110111
	len = 63 + (int)strlen(hd->status.name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x7f9;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=8;
	WBUFL(buf,5)=hd->bl.id;
	WBUFW(buf,9)=hd->speed;
	WBUFW(buf,11)=hd->sc.opt1;
	WBUFW(buf,13)=hd->sc.opt2;
	WBUFL(buf,15)=hd->sc.option;
	WBUFW(buf,19)=hd->view_class;
	WBUFW(buf,21)=100;
	WBUFL(buf,47)=hd->sc.opt3;
	WBUFPOS(buf,53,hd->bl.x,hd->bl.y,hd->dir);
	WBUFLV(buf,59,status_get_lv(&hd->bl),hd->view_class);
	strncpy(WBUFP(buf,63),hd->status.name,24);
#elif PACKETVER < 20120328
	len = 65 + (int)strlen(hd->status.name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x857;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=8;
	WBUFL(buf,5)=hd->bl.id;
	WBUFW(buf,9)=hd->speed;
	WBUFW(buf,11)=hd->sc.opt1;
	WBUFW(buf,13)=hd->sc.opt2;
	WBUFL(buf,15)=hd->sc.option;
	WBUFW(buf,19)=hd->view_class;
	WBUFW(buf,21)=100;
	WBUFL(buf,49)=hd->sc.opt3;
	WBUFPOS(buf,55,hd->bl.x,hd->bl.y,hd->dir);
	WBUFLV(buf,61,status_get_lv(&hd->bl),hd->view_class);
	strncpy(WBUFP(buf,65),hd->status.name,24);
#elif PACKETVER < 20131223
	len = 74;
	memset(buf,0,len);

	WBUFW(buf,0)=0x915;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=8;
	WBUFL(buf,5)=hd->bl.id;
	WBUFW(buf,9)=hd->speed;
	WBUFW(buf,11)=hd->sc.opt1;
	WBUFW(buf,13)=hd->sc.opt2;
	WBUFL(buf,15)=hd->sc.option;
	WBUFW(buf,19)=hd->view_class;
	WBUFW(buf,21)=100;
	WBUFL(buf,49)=hd->sc.opt3;
	WBUFPOS(buf,55,hd->bl.x,hd->bl.y,hd->dir);
	WBUFLV(buf,61,status_get_lv(&hd->bl),hd->view_class);
	WBUFL(buf,65) = 0xffffffff;
	WBUFL(buf,69) = 0xffffffff;
	WBUFB(buf,73) = 0;
#elif PACKETVER < 20150513
	len = 78 + (int)strlen(hd->status.name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9dd;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=8;
	WBUFL(buf,5)=hd->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=hd->speed;
	WBUFW(buf,15)=hd->sc.opt1;
	WBUFW(buf,17)=hd->sc.opt2;
	WBUFL(buf,19)=hd->sc.option;
	WBUFW(buf,23)=hd->view_class;
	WBUFW(buf,25)=100;
	WBUFL(buf,53)=hd->sc.opt3;
	WBUFPOS(buf,59,hd->bl.x,hd->bl.y,hd->dir);
	WBUFLV(buf,65,status_get_lv(&hd->bl),hd->view_class);
	WBUFL(buf,69) = 0xffffffff;
	WBUFL(buf,73) = 0xffffffff;
	WBUFB(buf,77) = 0;
	strncpy(WBUFP(buf,78),hd->status.name,24);
#elif PACKETVER < 20180704
	len = 80 + (int)strlen(hd->status.name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9ff;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=8;
	WBUFL(buf,5)=hd->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=hd->speed;
	WBUFW(buf,15)=hd->sc.opt1;
	WBUFW(buf,17)=hd->sc.opt2;
	WBUFL(buf,19)=hd->sc.option;
	WBUFW(buf,23)=hd->view_class;
	WBUFW(buf,25)=100;
	WBUFL(buf,53)=hd->sc.opt3;
	WBUFPOS(buf,59,hd->bl.x,hd->bl.y,hd->dir);
	WBUFLV(buf,65,status_get_lv(&hd->bl),hd->view_class);
	WBUFL(buf,69) = 0xffffffff;
	WBUFL(buf,73) = 0xffffffff;
	WBUFB(buf,77) = 0;
	WBUFW(buf,78) = 0;
	strncpy(WBUFP(buf,80),hd->status.name,24);
#else
	len = 84 + (int)strlen(hd->status.name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9ff;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=8;
	WBUFL(buf,5)=hd->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=hd->speed;
	WBUFW(buf,15)=hd->sc.opt1;
	WBUFW(buf,17)=hd->sc.opt2;
	WBUFL(buf,19)=hd->sc.option;
	WBUFW(buf,23)=hd->view_class;
	WBUFW(buf,25)=100;
	WBUFL(buf,57)=hd->sc.opt3;
	WBUFPOS(buf,63,hd->bl.x,hd->bl.y,hd->dir);
	WBUFLV(buf,69,status_get_lv(&hd->bl),hd->view_class);
	WBUFL(buf,73) = 0xffffffff;
	WBUFL(buf,77) = 0xffffffff;
	WBUFB(buf,81) = 0;
	WBUFW(buf,82) = 0;
	strncpy(WBUFP(buf,84),hd->status.name,24);
#endif
	return len;
}

/*==========================================
 *
 *------------------------------------------
 */
static int clif_hom007b(struct homun_data *hd,unsigned char *buf)
{
	int len, view;
	unsigned int tick = gettick();

	nullpo_retr(0, hd);

#if PACKETVER < 20091104
	len = packet_db[0x7b].len;
	memset(buf,0,len);

	WBUFW(buf,0) =0x7b;
	WBUFL(buf,2) =hd->bl.id;
	WBUFW(buf,6) =hd->speed;
	WBUFW(buf,8) =hd->sc.opt1;
	WBUFW(buf,10)=hd->sc.opt2;
	WBUFW(buf,12)=hd->sc.option;
	WBUFW(buf,14)=hd->view_class;
	WBUFW(buf,16)=battle_config.pet0078_hair_id;
	if((view = itemdb_viewid(hd->status.equip)) > 0)
		WBUFW(buf,20)=view;
	else
		WBUFW(buf,20)=hd->status.equip;
	WBUFL(buf,22)=tick;
	WBUFW(buf,46)=hd->sc.opt3;
	WBUFPOS2(buf,50,hd->bl.x,hd->bl.y,hd->ud.to_x,hd->ud.to_y,8,8);
	WBUFB(buf,56)=0;
	WBUFB(buf,57)=0;
	WBUFLV(buf,58,status_get_lv(&hd->bl),hd->view_class);
#elif PACKETVER < 20110111
	len = 69 + (int)strlen(hd->status.name);
	memset(buf,0,len);

	WBUFW(buf,0) =0x7f7;
	WBUFW(buf,2) =(unsigned short)len;
	WBUFB(buf,4) =8;
	WBUFL(buf,5) =hd->bl.id;
	WBUFW(buf,9) =hd->speed;
	WBUFW(buf,11)=hd->sc.opt1;
	WBUFW(buf,13)=hd->sc.opt2;
	WBUFL(buf,15)=hd->sc.option;
	WBUFW(buf,19)=hd->view_class;
	WBUFW(buf,21)=100;
	if((view = itemdb_viewid(hd->status.equip)) > 0)
		WBUFW(buf,23)=view;
	else
		WBUFW(buf,23)=hd->status.equip;
	WBUFL(buf,29)=tick;
	WBUFL(buf,51)=hd->sc.opt3;
	WBUFPOS2(buf,57,hd->bl.x,hd->bl.y,hd->ud.to_x,hd->ud.to_y,8,8);
	WBUFLV(buf,65,status_get_lv(&hd->bl),hd->view_class);
	strncpy(WBUFP(buf,69),hd->status.name,24);
#elif PACKETVER < 20120328
	len = 71 + (int)strlen(hd->status.name);
	memset(buf,0,len);

	WBUFW(buf,0) =0x856;
	WBUFW(buf,2) =(unsigned short)len;
	WBUFB(buf,4) =8;
	WBUFL(buf,5) =hd->bl.id;
	WBUFW(buf,9) =hd->speed;
	WBUFW(buf,11)=hd->sc.opt1;
	WBUFW(buf,13)=hd->sc.opt2;
	WBUFL(buf,15)=hd->sc.option;
	WBUFW(buf,19)=hd->view_class;
	WBUFW(buf,21)=100;
	if((view = itemdb_viewid(hd->status.equip)) > 0)
		WBUFW(buf,23)=view;
	else
		WBUFW(buf,23)=hd->status.equip;
	WBUFL(buf,29)=tick;
	WBUFL(buf,53)=hd->sc.opt3;
	WBUFPOS2(buf,59,hd->bl.x,hd->bl.y,hd->ud.to_x,hd->ud.to_y,8,8);
	WBUFLV(buf,67,status_get_lv(&hd->bl),hd->view_class);
	strncpy(WBUFP(buf,71),hd->status.name,24);
#elif PACKETVER < 20131223
	len = 80;
	memset(buf,0,len);

	WBUFW(buf,0) =0x914;
	WBUFW(buf,2) =(unsigned short)len;
	WBUFB(buf,4) =8;
	WBUFL(buf,5) =hd->bl.id;
	WBUFW(buf,9) =hd->speed;
	WBUFW(buf,11)=hd->sc.opt1;
	WBUFW(buf,13)=hd->sc.opt2;
	WBUFL(buf,15)=hd->sc.option;
	WBUFW(buf,19)=hd->view_class;
	WBUFW(buf,21)=100;
	if((view = itemdb_viewid(hd->status.equip)) > 0)
		WBUFW(buf,23)=view;
	else
		WBUFW(buf,23)=hd->status.equip;
	WBUFL(buf,29)=tick;
	WBUFL(buf,53)=hd->sc.opt3;
	WBUFPOS2(buf,59,hd->bl.x,hd->bl.y,hd->ud.to_x,hd->ud.to_y,8,8);
	WBUFLV(buf,67,status_get_lv(&hd->bl),hd->view_class);
	WBUFL(buf,71) = 0xffffffff;
	WBUFL(buf,75) = 0xffffffff;
	WBUFB(buf,79) = 0;
#elif PACKETVER < 20150513
	len = 84 + (int)strlen(hd->status.name);
	memset(buf,0,len);

	WBUFW(buf,0) =0x9db;
	WBUFW(buf,2) =(unsigned short)len;
	WBUFB(buf,4) =8;
	WBUFL(buf,5) =hd->bl.id;
	WBUFL(buf,9) =0;
	WBUFW(buf,13) =hd->speed;
	WBUFW(buf,15)=hd->sc.opt1;
	WBUFW(buf,17)=hd->sc.opt2;
	WBUFL(buf,19)=hd->sc.option;
	WBUFW(buf,23)=hd->view_class;
	WBUFW(buf,25)=100;
	if((view = itemdb_viewid(hd->status.equip)) > 0)
		WBUFW(buf,27)=view;
	else
		WBUFW(buf,27)=hd->status.equip;
	WBUFL(buf,33)=tick;
	WBUFL(buf,57)=hd->sc.opt3;
	WBUFPOS2(buf,63,hd->bl.x,hd->bl.y,hd->ud.to_x,hd->ud.to_y,8,8);
	WBUFLV(buf,71,status_get_lv(&hd->bl),hd->view_class);
	WBUFL(buf,75) = 0xffffffff;
	WBUFL(buf,79) = 0xffffffff;
	WBUFB(buf,83) = 0;
	strncpy(WBUFP(buf,84),hd->status.name,24);
#elif PACKETVER < 20180704
	len = 86 + (int)strlen(hd->status.name);
	memset(buf,0,len);

	WBUFW(buf,0) =0x9fd;
	WBUFW(buf,2) =(unsigned short)len;
	WBUFB(buf,4) =8;
	WBUFL(buf,5) =hd->bl.id;
	WBUFL(buf,9) =0;
	WBUFW(buf,13) =hd->speed;
	WBUFW(buf,15)=hd->sc.opt1;
	WBUFW(buf,17)=hd->sc.opt2;
	WBUFL(buf,19)=hd->sc.option;
	WBUFW(buf,23)=hd->view_class;
	WBUFW(buf,25)=100;
	if((view = itemdb_viewid(hd->status.equip)) > 0)
		WBUFW(buf,27)=view;
	else
		WBUFW(buf,27)=hd->status.equip;
	WBUFL(buf,33)=tick;
	WBUFL(buf,57)=hd->sc.opt3;
	WBUFPOS2(buf,63,hd->bl.x,hd->bl.y,hd->ud.to_x,hd->ud.to_y,8,8);
	WBUFLV(buf,71,status_get_lv(&hd->bl),hd->view_class);
	WBUFL(buf,75) = 0xffffffff;
	WBUFL(buf,79) = 0xffffffff;
	WBUFB(buf,83) = 0;
	WBUFW(buf,84) = 0;
	strncpy(WBUFP(buf,86),hd->status.name,24);
#else
	len = 90 + (int)strlen(hd->status.name);
	memset(buf,0,len);

	WBUFW(buf,0) =0x9fd;
	WBUFW(buf,2) =(unsigned short)len;
	WBUFB(buf,4) =8;
	WBUFL(buf,5) =hd->bl.id;
	WBUFL(buf,9) =0;
	WBUFW(buf,13) =hd->speed;
	WBUFW(buf,15)=hd->sc.opt1;
	WBUFW(buf,17)=hd->sc.opt2;
	WBUFL(buf,19)=hd->sc.option;
	WBUFW(buf,23)=hd->view_class;
	WBUFW(buf,25)=100;
	if((view = itemdb_viewid(hd->status.equip)) > 0)
		WBUFL(buf,27)=view;
	else
		WBUFL(buf,27)=hd->status.equip;
	WBUFL(buf,37)=tick;
	WBUFL(buf,61)=hd->sc.opt3;
	WBUFPOS2(buf,67,hd->bl.x,hd->bl.y,hd->ud.to_x,hd->ud.to_y,8,8);
	WBUFLV(buf,75,status_get_lv(&hd->bl),hd->view_class);
	WBUFL(buf,79) = 0xffffffff;
	WBUFL(buf,83) = 0xffffffff;
	WBUFB(buf,87) = 0;
	WBUFW(buf,88) = 0;
	strncpy(WBUFP(buf,90),hd->status.name,24);
#endif
	return len;
}

/*==========================================
 *
 *------------------------------------------
 */
static int clif_merc0078(struct merc_data *mcd,unsigned char *buf)
{
	int len;

	nullpo_retr(0, mcd);

#if PACKETVER < 20071106
	len = packet_db[0x78].len;
	memset(buf,0,len);

	WBUFW(buf,0) =0x78;
	WBUFL(buf,2) =mcd->bl.id;
	WBUFW(buf,6) =mcd->speed;
	WBUFW(buf,8) =mcd->sc.opt1;
	WBUFW(buf,10)=mcd->sc.opt2;
	WBUFW(buf,12)=mcd->sc.option;
	WBUFW(buf,14)=mcd->view_class;
	WBUFW(buf,16)=battle_config.pet0078_hair_id;
	WBUFW(buf,20)=0;
	WBUFW(buf,42)=mcd->sc.opt3;
	WBUFPOS(buf,46,mcd->bl.x,mcd->bl.y,mcd->dir);
	WBUFB(buf,49)=0;
	WBUFB(buf,50)=0;
	WBUFLV(buf,52,status_get_lv(&mcd->bl),mcd->view_class);
#elif PACKETVER < 20091104
	len = packet_db[0x78].len;
	memset(buf,0,len);

	WBUFW(buf,0) =0x78;
	WBUFB(buf,2) =0;
	WBUFL(buf,3) =mcd->bl.id;
	WBUFW(buf,7) =mcd->speed;
	WBUFW(buf,9) =mcd->sc.opt1;
	WBUFW(buf,11)=mcd->sc.opt2;
	WBUFW(buf,13)=mcd->sc.option;
	WBUFW(buf,15)=mcd->view_class;
	WBUFW(buf,17)=battle_config.pet0078_hair_id;
	WBUFW(buf,21)=0;
	WBUFW(buf,43)=mcd->sc.opt3;
	WBUFPOS(buf,47,mcd->bl.x,mcd->bl.y,mcd->dir);
	WBUFB(buf,50)=0;
	WBUFB(buf,51)=0;
	WBUFLV(buf,53,status_get_lv(&mcd->bl),mcd->view_class);
#elif PACKETVER < 20110111
	len = 63 + (int)strlen(mcd->name);
	memset(buf,0,len);

	WBUFW(buf,0) =0x7f9;
	WBUFW(buf,2) =(unsigned short)len;
	WBUFB(buf,4) =9;
	WBUFL(buf,5) =mcd->bl.id;
	WBUFW(buf,9) =mcd->speed;
	WBUFW(buf,11)=mcd->sc.opt1;
	WBUFW(buf,13)=mcd->sc.opt2;
	WBUFL(buf,15)=mcd->sc.option;
	WBUFW(buf,19)=mcd->view_class;
	WBUFW(buf,21)=100;
	WBUFL(buf,47)=mcd->sc.opt3;
	WBUFPOS(buf,53,mcd->bl.x,mcd->bl.y,mcd->dir);
	WBUFLV(buf,59,status_get_lv(&mcd->bl),mcd->view_class);
	strncpy(WBUFP(buf,63),mcd->name,24);
#elif PACKETVER < 20120328
	len = 65 + (int)strlen(mcd->name);
	memset(buf,0,len);

	WBUFW(buf,0) =0x857;
	WBUFW(buf,2) =(unsigned short)len;
	WBUFB(buf,4) =9;
	WBUFL(buf,5) =mcd->bl.id;
	WBUFW(buf,9) =mcd->speed;
	WBUFW(buf,11)=mcd->sc.opt1;
	WBUFW(buf,13)=mcd->sc.opt2;
	WBUFL(buf,15)=mcd->sc.option;
	WBUFW(buf,19)=mcd->view_class;
	WBUFW(buf,21)=100;
	WBUFL(buf,49)=mcd->sc.opt3;
	WBUFPOS(buf,55,mcd->bl.x,mcd->bl.y,mcd->dir);
	WBUFLV(buf,61,status_get_lv(&mcd->bl),mcd->view_class);
	strncpy(WBUFP(buf,65),mcd->name,24);
#elif PACKETVER < 20131223
	len = 74;
	memset(buf,0,len);

	WBUFW(buf,0) =0x915;
	WBUFW(buf,2) =(unsigned short)len;
	WBUFB(buf,4) =9;
	WBUFL(buf,5) =mcd->bl.id;
	WBUFW(buf,9) =mcd->speed;
	WBUFW(buf,11)=mcd->sc.opt1;
	WBUFW(buf,13)=mcd->sc.opt2;
	WBUFL(buf,15)=mcd->sc.option;
	WBUFW(buf,19)=mcd->view_class;
	WBUFW(buf,21)=100;
	WBUFL(buf,49)=mcd->sc.opt3;
	WBUFPOS(buf,55,mcd->bl.x,mcd->bl.y,mcd->dir);
	WBUFLV(buf,61,status_get_lv(&mcd->bl),mcd->view_class);
	WBUFL(buf,65) = 0xffffffff;
	WBUFL(buf,69) = 0xffffffff;
	WBUFB(buf,73) = 0;
#elif PACKETVER < 20150513
	len = 78 + (int)strlen(mcd->name);
	memset(buf,0,len);

	WBUFW(buf,0) =0x9dd;
	WBUFW(buf,2) =(unsigned short)len;
	WBUFB(buf,4) =9;
	WBUFL(buf,5) =mcd->bl.id;
	WBUFL(buf,9) =0;
	WBUFW(buf,13) =mcd->speed;
	WBUFW(buf,15)=mcd->sc.opt1;
	WBUFW(buf,17)=mcd->sc.opt2;
	WBUFL(buf,19)=mcd->sc.option;
	WBUFW(buf,23)=mcd->view_class;
	WBUFW(buf,25)=100;
	WBUFL(buf,53)=mcd->sc.opt3;
	WBUFPOS(buf,59,mcd->bl.x,mcd->bl.y,mcd->dir);
	WBUFLV(buf,65,status_get_lv(&mcd->bl),mcd->view_class);
	WBUFL(buf,69) = 0xffffffff;
	WBUFL(buf,73) = 0xffffffff;
	WBUFB(buf,77) = 0;
	strncpy(WBUFP(buf,78),mcd->name,24);
#elif PACKETVER < 20180704
	len = 80 + (int)strlen(mcd->name);
	memset(buf,0,len);

	WBUFW(buf,0) =0x9ff;
	WBUFW(buf,2) =(unsigned short)len;
	WBUFB(buf,4) =9;
	WBUFL(buf,5) =mcd->bl.id;
	WBUFL(buf,9) =0;
	WBUFW(buf,13) =mcd->speed;
	WBUFW(buf,15)=mcd->sc.opt1;
	WBUFW(buf,17)=mcd->sc.opt2;
	WBUFL(buf,19)=mcd->sc.option;
	WBUFW(buf,23)=mcd->view_class;
	WBUFW(buf,25)=100;
	WBUFL(buf,53)=mcd->sc.opt3;
	WBUFPOS(buf,59,mcd->bl.x,mcd->bl.y,mcd->dir);
	WBUFLV(buf,65,status_get_lv(&mcd->bl),mcd->view_class);
	WBUFL(buf,69) = 0xffffffff;
	WBUFL(buf,73) = 0xffffffff;
	WBUFB(buf,77) = 0;
	WBUFW(buf,78) = 0;
	strncpy(WBUFP(buf,80),mcd->name,24);
#else
	len = 84 + (int)strlen(mcd->name);
	memset(buf,0,len);

	WBUFW(buf,0) =0x9ff;
	WBUFW(buf,2) =(unsigned short)len;
	WBUFB(buf,4) =9;
	WBUFL(buf,5) =mcd->bl.id;
	WBUFL(buf,9) =0;
	WBUFW(buf,13) =mcd->speed;
	WBUFW(buf,15)=mcd->sc.opt1;
	WBUFW(buf,17)=mcd->sc.opt2;
	WBUFL(buf,19)=mcd->sc.option;
	WBUFW(buf,23)=mcd->view_class;
	WBUFW(buf,25)=100;
	WBUFL(buf,57)=mcd->sc.opt3;
	WBUFPOS(buf,63,mcd->bl.x,mcd->bl.y,mcd->dir);
	WBUFLV(buf,69,status_get_lv(&mcd->bl),mcd->view_class);
	WBUFL(buf,73) = 0xffffffff;
	WBUFL(buf,77) = 0xffffffff;
	WBUFB(buf,81) = 0;
	WBUFW(buf,82) = 0;
	strncpy(WBUFP(buf,84),mcd->name,24);
#endif
	return len;
}

/*==========================================
 *
 *------------------------------------------
 */
static int clif_merc007b(struct merc_data *mcd,unsigned char *buf)
{
	int len;
	unsigned int tick = gettick();

	nullpo_retr(0, mcd);

#if PACKETVER < 20091104
	len = packet_db[0x7b].len;
	memset(buf,0,len);

	WBUFW(buf,0) =0x7b;
	WBUFL(buf,2) =mcd->bl.id;
	WBUFW(buf,6) =mcd->speed;
	WBUFW(buf,8) =mcd->sc.opt1;
	WBUFW(buf,10)=mcd->sc.opt2;
	WBUFW(buf,12)=mcd->sc.option;
	WBUFW(buf,14)=mcd->view_class;
	WBUFW(buf,16)=battle_config.pet0078_hair_id;
	WBUFL(buf,22)=tick;
	WBUFW(buf,46)=mcd->sc.opt3;
	WBUFPOS2(buf,50,mcd->bl.x,mcd->bl.y,mcd->ud.to_x,mcd->ud.to_y,8,8);
	WBUFB(buf,56)=0;
	WBUFB(buf,57)=0;
	WBUFLV(buf,58,status_get_lv(&mcd->bl),mcd->view_class);
#elif PACKETVER < 20110111
	len = 69 + (int)strlen(mcd->name);
	memset(buf,0,len);

	WBUFW(buf,0) =0x7f7;
	WBUFW(buf,2) =(unsigned short)len;
	WBUFB(buf,4) =9;
	WBUFL(buf,5) =mcd->bl.id;
	WBUFW(buf,9) =mcd->speed;
	WBUFW(buf,11)=mcd->sc.opt1;
	WBUFW(buf,13)=mcd->sc.opt2;
	WBUFL(buf,15)=mcd->sc.option;
	WBUFW(buf,19)=mcd->view_class;
	WBUFW(buf,21)=100;
	WBUFL(buf,29)=tick;
	WBUFL(buf,51)=mcd->sc.opt3;
	WBUFPOS2(buf,57,mcd->bl.x,mcd->bl.y,mcd->ud.to_x,mcd->ud.to_y,8,8);
	WBUFLV(buf,65,status_get_lv(&mcd->bl),mcd->view_class);
	strncpy(WBUFP(buf,69),mcd->name,24);
#elif PACKETVER < 20120328
	len = 71 + (int)strlen(mcd->name);
	memset(buf,0,len);

	WBUFW(buf,0) =0x856;
	WBUFW(buf,2) =(unsigned short)len;
	WBUFB(buf,4) =9;
	WBUFL(buf,5) =mcd->bl.id;
	WBUFW(buf,9) =mcd->speed;
	WBUFW(buf,11)=mcd->sc.opt1;
	WBUFW(buf,13)=mcd->sc.opt2;
	WBUFL(buf,15)=mcd->sc.option;
	WBUFW(buf,19)=mcd->view_class;
	WBUFW(buf,21)=100;
	WBUFL(buf,29)=tick;
	WBUFL(buf,53)=mcd->sc.opt3;
	WBUFPOS2(buf,59,mcd->bl.x,mcd->bl.y,mcd->ud.to_x,mcd->ud.to_y,8,8);
	WBUFLV(buf,67,status_get_lv(&mcd->bl),mcd->view_class);
	strncpy(WBUFP(buf,71),mcd->name,24);
#elif PACKETVER < 20131223
	len = 80;
	memset(buf,0,len);

	WBUFW(buf,0) =0x914;
	WBUFW(buf,2) =(unsigned short)len;
	WBUFB(buf,4) =9;
	WBUFL(buf,5) =mcd->bl.id;
	WBUFW(buf,9) =mcd->speed;
	WBUFW(buf,11)=mcd->sc.opt1;
	WBUFW(buf,13)=mcd->sc.opt2;
	WBUFL(buf,15)=mcd->sc.option;
	WBUFW(buf,19)=mcd->view_class;
	WBUFW(buf,21)=100;
	WBUFL(buf,29)=tick;
	WBUFL(buf,53)=mcd->sc.opt3;
	WBUFPOS2(buf,59,mcd->bl.x,mcd->bl.y,mcd->ud.to_x,mcd->ud.to_y,8,8);
	WBUFLV(buf,67,status_get_lv(&mcd->bl),mcd->view_class);
	WBUFL(buf,71) = 0xffffffff;
	WBUFL(buf,75) = 0xffffffff;
	WBUFB(buf,79) = 0;
#elif PACKETVER < 20150513
	len = 84 + (int)strlen(mcd->name);
	memset(buf,0,len);

	WBUFW(buf,0) =0x9db;
	WBUFW(buf,2) =(unsigned short)len;
	WBUFB(buf,4) =9;
	WBUFL(buf,5) =mcd->bl.id;
	WBUFL(buf,9) =0;
	WBUFW(buf,13)=mcd->speed;
	WBUFW(buf,15)=mcd->sc.opt1;
	WBUFW(buf,17)=mcd->sc.opt2;
	WBUFL(buf,19)=mcd->sc.option;
	WBUFW(buf,23)=mcd->view_class;
	WBUFW(buf,25)=100;
	WBUFL(buf,33)=tick;
	WBUFL(buf,57)=mcd->sc.opt3;
	WBUFPOS2(buf,63,mcd->bl.x,mcd->bl.y,mcd->ud.to_x,mcd->ud.to_y,8,8);
	WBUFLV(buf,71,status_get_lv(&mcd->bl),mcd->view_class);
	WBUFL(buf,75) = 0xffffffff;
	WBUFL(buf,79) = 0xffffffff;
	WBUFB(buf,83) = 0;
	strncpy(WBUFP(buf,84),mcd->name,24);
#elif PACKETVER < 20180704
	len = 86 + (int)strlen(mcd->name);
	memset(buf,0,len);

	WBUFW(buf,0) =0x9fd;
	WBUFW(buf,2) =(unsigned short)len;
	WBUFB(buf,4) =9;
	WBUFL(buf,5) =mcd->bl.id;
	WBUFL(buf,9) =0;
	WBUFW(buf,13)=mcd->speed;
	WBUFW(buf,15)=mcd->sc.opt1;
	WBUFW(buf,17)=mcd->sc.opt2;
	WBUFL(buf,19)=mcd->sc.option;
	WBUFW(buf,23)=mcd->view_class;
	WBUFW(buf,25)=100;
	WBUFL(buf,33)=tick;
	WBUFL(buf,57)=mcd->sc.opt3;
	WBUFPOS2(buf,63,mcd->bl.x,mcd->bl.y,mcd->ud.to_x,mcd->ud.to_y,8,8);
	WBUFLV(buf,71,status_get_lv(&mcd->bl),mcd->view_class);
	WBUFL(buf,75) = 0xffffffff;
	WBUFL(buf,79) = 0xffffffff;
	WBUFB(buf,83) = 0;
	WBUFW(buf,84) = 0;
	strncpy(WBUFP(buf,86),mcd->name,24);
#else
	len = 90 + (int)strlen(mcd->name);
	memset(buf,0,len);

	WBUFW(buf,0) =0x9fd;
	WBUFW(buf,2) =(unsigned short)len;
	WBUFB(buf,4) =9;
	WBUFL(buf,5) =mcd->bl.id;
	WBUFL(buf,9) =0;
	WBUFW(buf,13)=mcd->speed;
	WBUFW(buf,15)=mcd->sc.opt1;
	WBUFW(buf,17)=mcd->sc.opt2;
	WBUFL(buf,19)=mcd->sc.option;
	WBUFW(buf,23)=mcd->view_class;
	WBUFW(buf,25)=100;
	WBUFL(buf,33)=tick;
	WBUFL(buf,61)=mcd->sc.opt3;
	WBUFPOS2(buf,67,mcd->bl.x,mcd->bl.y,mcd->ud.to_x,mcd->ud.to_y,8,8);
	WBUFLV(buf,75,status_get_lv(&mcd->bl),mcd->view_class);
	WBUFL(buf,79) = 0xffffffff;
	WBUFL(buf,83) = 0xffffffff;
	WBUFB(buf,87) = 0;
	WBUFW(buf,88) = 0;
	strncpy(WBUFP(buf,90),mcd->name,24);
#endif
	return len;
}

/*==========================================
 *
 *------------------------------------------
 */
static int clif_elem0078(struct elem_data *eld,unsigned char *buf)
{
	int len;

	nullpo_retr(0, eld);

#if PACKETVER < 20071106
	len = packet_db[0x78].len;
	memset(buf,0,len);

	WBUFW(buf,0) =0x78;
	WBUFL(buf,2) =eld->bl.id;
	WBUFW(buf,6) =eld->speed;
	WBUFW(buf,8) =eld->sc.opt1;
	WBUFW(buf,10)=eld->sc.opt2;
	WBUFW(buf,12)=eld->sc.option;
	WBUFW(buf,14)=eld->view_class;
	WBUFW(buf,16)=battle_config.pet0078_hair_id;
	WBUFW(buf,20)=0;
	WBUFW(buf,42)=eld->sc.opt3;
	WBUFPOS(buf,46,eld->bl.x,eld->bl.y,eld->dir);
	WBUFB(buf,49)=0;
	WBUFB(buf,50)=0;
	WBUFLV(buf,52,status_get_lv(&eld->bl),eld->view_class);
#elif PACKETVER < 20091104
	len = packet_db[0x78].len;
	memset(buf,0,len);

	WBUFW(buf,0) =0x78;
	WBUFB(buf,2) =10;
	WBUFL(buf,3) =eld->bl.id;
	WBUFW(buf,7) =eld->speed;
	WBUFW(buf,9) =eld->sc.opt1;
	WBUFW(buf,11)=eld->sc.opt2;
	WBUFW(buf,13)=eld->sc.option;
	WBUFW(buf,15)=eld->view_class;
	WBUFW(buf,17)=battle_config.pet0078_hair_id;
	WBUFW(buf,21)=0;
	WBUFW(buf,43)=eld->sc.opt3;
	WBUFPOS(buf,47,eld->bl.x,eld->bl.y,eld->dir);
	WBUFB(buf,50)=0;
	WBUFB(buf,51)=0;
	WBUFLV(buf,53,status_get_lv(&eld->bl),eld->view_class);
#elif PACKETVER < 20110111
	len = 63 + (int)strlen(eld->name);
	memset(buf,0,len);

	WBUFW(buf,0) =0x7f9;
	WBUFW(buf,2) =(unsigned short)len;
	WBUFB(buf,4) =10;
	WBUFL(buf,5) =eld->bl.id;
	WBUFW(buf,9) =eld->speed;
	WBUFW(buf,11)=eld->sc.opt1;
	WBUFW(buf,13)=eld->sc.opt2;
	WBUFL(buf,15)=eld->sc.option;
	WBUFW(buf,19)=eld->view_class;
	WBUFW(buf,21)=100;
	WBUFL(buf,47)=eld->sc.opt3;
	WBUFPOS(buf,53,eld->bl.x,eld->bl.y,eld->dir);
	WBUFLV(buf,59,status_get_lv(&eld->bl),eld->view_class);
	strncpy(WBUFP(buf,63),eld->name,24);
#elif PACKETVER < 20120328
	len = 65 + (int)strlen(eld->name);
	memset(buf,0,len);

	WBUFW(buf,0) =0x857;
	WBUFW(buf,2) =(unsigned short)len;
	WBUFB(buf,4) =10;
	WBUFL(buf,5) =eld->bl.id;
	WBUFW(buf,9) =eld->speed;
	WBUFW(buf,11)=eld->sc.opt1;
	WBUFW(buf,13)=eld->sc.opt2;
	WBUFL(buf,15)=eld->sc.option;
	WBUFW(buf,19)=eld->view_class;
	WBUFW(buf,21)=100;
	WBUFL(buf,49)=eld->sc.opt3;
	WBUFPOS(buf,55,eld->bl.x,eld->bl.y,eld->dir);
	WBUFLV(buf,61,status_get_lv(&eld->bl),eld->view_class);
	strncpy(WBUFP(buf,65),eld->name,24);
#elif PACKETVER < 20131223
	len = 74;
	memset(buf,0,len);

	WBUFW(buf,0) =0x915;
	WBUFW(buf,2) =(unsigned short)len;
	WBUFB(buf,4) =10;
	WBUFL(buf,5) =eld->bl.id;
	WBUFW(buf,9) =eld->speed;
	WBUFW(buf,11)=eld->sc.opt1;
	WBUFW(buf,13)=eld->sc.opt2;
	WBUFL(buf,15)=eld->sc.option;
	WBUFW(buf,19)=eld->view_class;
	WBUFW(buf,21)=100;
	WBUFL(buf,49)=eld->sc.opt3;
	WBUFPOS(buf,55,eld->bl.x,eld->bl.y,eld->dir);
	WBUFLV(buf,61,status_get_lv(&eld->bl),eld->view_class);
	WBUFL(buf,65) = 0xffffffff;
	WBUFL(buf,69) = 0xffffffff;
	WBUFB(buf,73) = 0;
#elif PACKETVER < 20150513
	len = 78 + (int)strlen(eld->name);
	memset(buf,0,len);

	WBUFW(buf,0) =0x9dd;
	WBUFW(buf,2) =(unsigned short)len;
	WBUFB(buf,4) =10;
	WBUFL(buf,5) =eld->bl.id;
	WBUFL(buf,9) =0;
	WBUFW(buf,13)=eld->speed;
	WBUFW(buf,15)=eld->sc.opt1;
	WBUFW(buf,17)=eld->sc.opt2;
	WBUFL(buf,19)=eld->sc.option;
	WBUFW(buf,23)=eld->view_class;
	WBUFW(buf,25)=100;
	WBUFL(buf,53)=eld->sc.opt3;
	WBUFPOS(buf,59,eld->bl.x,eld->bl.y,eld->dir);
	WBUFLV(buf,65,status_get_lv(&eld->bl),eld->view_class);
	WBUFL(buf,69) = 0xffffffff;
	WBUFL(buf,73) = 0xffffffff;
	WBUFB(buf,77) = 0;
	strncpy(WBUFP(buf,78),eld->name,24);
#elif PACKETVER < 20180704
	len = 80 + (int)strlen(eld->name);
	memset(buf,0,len);

	WBUFW(buf,0) =0x9ff;
	WBUFW(buf,2) =(unsigned short)len;
	WBUFB(buf,4) =10;
	WBUFL(buf,5) =eld->bl.id;
	WBUFL(buf,9) =0;
	WBUFW(buf,13)=eld->speed;
	WBUFW(buf,15)=eld->sc.opt1;
	WBUFW(buf,17)=eld->sc.opt2;
	WBUFL(buf,19)=eld->sc.option;
	WBUFW(buf,23)=eld->view_class;
	WBUFW(buf,25)=100;
	WBUFL(buf,53)=eld->sc.opt3;
	WBUFPOS(buf,59,eld->bl.x,eld->bl.y,eld->dir);
	WBUFLV(buf,65,status_get_lv(&eld->bl),eld->view_class);
	WBUFL(buf,69) = 0xffffffff;
	WBUFL(buf,73) = 0xffffffff;
	WBUFB(buf,77) = 0;
	WBUFW(buf,78) = 0;
	strncpy(WBUFP(buf,80),eld->name,24);
#else
	len = 84 + (int)strlen(eld->name);
	memset(buf,0,len);

	WBUFW(buf,0) =0x9ff;
	WBUFW(buf,2) =(unsigned short)len;
	WBUFB(buf,4) =10;
	WBUFL(buf,5) =eld->bl.id;
	WBUFL(buf,9) =0;
	WBUFW(buf,13)=eld->speed;
	WBUFW(buf,15)=eld->sc.opt1;
	WBUFW(buf,17)=eld->sc.opt2;
	WBUFL(buf,19)=eld->sc.option;
	WBUFW(buf,23)=eld->view_class;
	WBUFW(buf,25)=100;
	WBUFL(buf,57)=eld->sc.opt3;
	WBUFPOS(buf,63,eld->bl.x,eld->bl.y,eld->dir);
	WBUFLV(buf,69,status_get_lv(&eld->bl),eld->view_class);
	WBUFL(buf,73) = 0xffffffff;
	WBUFL(buf,77) = 0xffffffff;
	WBUFB(buf,81) = 0;
	WBUFW(buf,82) = 0;
	strncpy(WBUFP(buf,84),eld->name,24);
#endif
	return len;
}

/*==========================================
 *
 *------------------------------------------
 */
static int clif_elem007b(struct elem_data *eld,unsigned char *buf)
{
	int len;
	unsigned int tick = gettick();

	nullpo_retr(0, eld);

#if PACKETVER < 20091104
	len = packet_db[0x7b].len;
	memset(buf,0,len);

	WBUFW(buf,0) =0x7b;
	WBUFL(buf,2) =eld->bl.id;
	WBUFW(buf,6) =eld->speed;
	WBUFW(buf,8) =eld->sc.opt1;
	WBUFW(buf,10)=eld->sc.opt2;
	WBUFW(buf,12)=eld->sc.option;
	WBUFW(buf,14)=eld->view_class;
	WBUFW(buf,16)=battle_config.pet0078_hair_id;
	WBUFL(buf,22)=tick;
	WBUFW(buf,46)=eld->sc.opt3;
	WBUFPOS2(buf,50,eld->bl.x,eld->bl.y,eld->ud.to_x,eld->ud.to_y,8,8);
	WBUFB(buf,56)=0;
	WBUFB(buf,57)=0;
	WBUFLV(buf,58,status_get_lv(&eld->bl),eld->view_class);
#elif PACKETVER < 20110111
	len = 69 + (int)strlen(eld->name);
	memset(buf,0,len);

	WBUFW(buf,0) =0x7f7;
	WBUFW(buf,2) =(unsigned short)len;
	WBUFB(buf,4) =10;
	WBUFL(buf,5) =eld->bl.id;
	WBUFW(buf,9) =eld->speed;
	WBUFW(buf,11)=eld->sc.opt1;
	WBUFW(buf,13)=eld->sc.opt2;
	WBUFL(buf,15)=eld->sc.option;
	WBUFW(buf,19)=eld->view_class;
	WBUFW(buf,21)=100;
	WBUFL(buf,29)=tick;
	WBUFL(buf,51)=eld->sc.opt3;
	WBUFPOS2(buf,57,eld->bl.x,eld->bl.y,eld->ud.to_x,eld->ud.to_y,8,8);
	WBUFLV(buf,65,status_get_lv(&eld->bl),eld->view_class);
	strncpy(WBUFP(buf,69),eld->name,24);
#elif PACKETVER < 20120328
	len = 71 + (int)strlen(eld->name);
	memset(buf,0,len);

	WBUFW(buf,0) =0x856;
	WBUFW(buf,2) =(unsigned short)len;
	WBUFB(buf,4) =10;
	WBUFL(buf,5) =eld->bl.id;
	WBUFW(buf,9) =eld->speed;
	WBUFW(buf,11)=eld->sc.opt1;
	WBUFW(buf,13)=eld->sc.opt2;
	WBUFL(buf,15)=eld->sc.option;
	WBUFW(buf,19)=eld->view_class;
	WBUFW(buf,21)=100;
	WBUFL(buf,29)=tick;
	WBUFL(buf,53)=eld->sc.opt3;
	WBUFPOS2(buf,59,eld->bl.x,eld->bl.y,eld->ud.to_x,eld->ud.to_y,8,8);
	WBUFLV(buf,67,status_get_lv(&eld->bl),eld->view_class);
	strncpy(WBUFP(buf,71),eld->name,24);
#elif PACKETVER < 20131223
	len = 80;
	memset(buf,0,len);

	WBUFW(buf,0) =0x914;
	WBUFW(buf,2) =(unsigned short)len;
	WBUFB(buf,4) =10;
	WBUFL(buf,5) =eld->bl.id;
	WBUFW(buf,9) =eld->speed;
	WBUFW(buf,11)=eld->sc.opt1;
	WBUFW(buf,13)=eld->sc.opt2;
	WBUFL(buf,15)=eld->sc.option;
	WBUFW(buf,19)=eld->view_class;
	WBUFW(buf,21)=100;
	WBUFL(buf,29)=tick;
	WBUFL(buf,53)=eld->sc.opt3;
	WBUFPOS2(buf,59,eld->bl.x,eld->bl.y,eld->ud.to_x,eld->ud.to_y,8,8);
	WBUFLV(buf,67,status_get_lv(&eld->bl),eld->view_class);
	WBUFL(buf,71) = 0xffffffff;
	WBUFL(buf,75) = 0xffffffff;
	WBUFB(buf,79) = 0;
#elif PACKETVER < 20150513
	len = 84 + (int)strlen(eld->name);
	memset(buf,0,len);

	WBUFW(buf,0) =0x9db;
	WBUFW(buf,2) =(unsigned short)len;
	WBUFB(buf,4) =10;
	WBUFL(buf,5) =eld->bl.id;
	WBUFL(buf,9) =0;
	WBUFW(buf,13)=eld->speed;
	WBUFW(buf,15)=eld->sc.opt1;
	WBUFW(buf,17)=eld->sc.opt2;
	WBUFL(buf,19)=eld->sc.option;
	WBUFW(buf,23)=eld->view_class;
	WBUFW(buf,25)=100;
	WBUFL(buf,33)=tick;
	WBUFL(buf,57)=eld->sc.opt3;
	WBUFPOS2(buf,63,eld->bl.x,eld->bl.y,eld->ud.to_x,eld->ud.to_y,8,8);
	WBUFLV(buf,71,status_get_lv(&eld->bl),eld->view_class);
	WBUFL(buf,75) = 0xffffffff;
	WBUFL(buf,79) = 0xffffffff;
	WBUFB(buf,83) = 0;
	strncpy(WBUFP(buf,84),eld->name,24);
#elif PACKETVER < 20180704
	len = 86 + (int)strlen(eld->name);
	memset(buf,0,len);

	WBUFW(buf,0) =0x9fd;
	WBUFW(buf,2) =(unsigned short)len;
	WBUFB(buf,4) =10;
	WBUFL(buf,5) =eld->bl.id;
	WBUFL(buf,9) =0;
	WBUFW(buf,13)=eld->speed;
	WBUFW(buf,15)=eld->sc.opt1;
	WBUFW(buf,17)=eld->sc.opt2;
	WBUFL(buf,19)=eld->sc.option;
	WBUFW(buf,23)=eld->view_class;
	WBUFW(buf,25)=100;
	WBUFL(buf,33)=tick;
	WBUFL(buf,57)=eld->sc.opt3;
	WBUFPOS2(buf,63,eld->bl.x,eld->bl.y,eld->ud.to_x,eld->ud.to_y,8,8);
	WBUFLV(buf,71,status_get_lv(&eld->bl),eld->view_class);
	WBUFL(buf,75) = 0xffffffff;
	WBUFL(buf,79) = 0xffffffff;
	WBUFB(buf,83) = 0;
	WBUFW(buf,84) = 0;
	strncpy(WBUFP(buf,86),eld->name,24);
#else
	len = 90 + (int)strlen(eld->name);
	memset(buf,0,len);

	WBUFW(buf,0) =0x9fd;
	WBUFW(buf,2) =(unsigned short)len;
	WBUFB(buf,4) =10;
	WBUFL(buf,5) =eld->bl.id;
	WBUFL(buf,9) =0;
	WBUFW(buf,13)=eld->speed;
	WBUFW(buf,15)=eld->sc.opt1;
	WBUFW(buf,17)=eld->sc.opt2;
	WBUFL(buf,19)=eld->sc.option;
	WBUFW(buf,23)=eld->view_class;
	WBUFW(buf,25)=100;
	WBUFL(buf,37)=tick;
	WBUFL(buf,61)=eld->sc.opt3;
	WBUFPOS2(buf,67,eld->bl.x,eld->bl.y,eld->ud.to_x,eld->ud.to_y,8,8);
	WBUFLV(buf,75,status_get_lv(&eld->bl),eld->view_class);
	WBUFL(buf,79) = 0xffffffff;
	WBUFL(buf,83) = 0xffffffff;
	WBUFB(buf,87) = 0;
	WBUFW(buf,88) = 0;
	strncpy(WBUFP(buf,90),eld->name,24);
#endif
	return len;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_set01e1(const int fd, struct map_session_data *dstsd, short num)
{
	nullpo_retv(dstsd);

	WFIFOW(fd,0)=0x1e1;
	WFIFOL(fd,2)=dstsd->bl.id;
	WFIFOW(fd,6)=num;
	WFIFOSET(fd,packet_db[0x1e1].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_set0192(int fd, int m, int x, int y, int type)
{
	WFIFOW(fd,0) = 0x192;
	WFIFOW(fd,2) = x;
	WFIFOW(fd,4) = y;
	WFIFOW(fd,6) = type;
	memcpy(WFIFOP(fd,8),map[m].name,16);
	WFIFOSET(fd,packet_db[0x192].len);

	return;
}

/*==========================================
 * �e�T�E�O�̋��̕\��(ID�w�著�M)
 *------------------------------------------
 */
static void clif_elementball_id(const int fd, struct map_session_data *dstsd)
{
	nullpo_retv(dstsd);

	WFIFOW(fd,0)=0x8cf;
	WFIFOL(fd,2)=dstsd->bl.id;
	WFIFOW(fd,6)=dstsd->elementball.ele;
	WFIFOW(fd,8)=dstsd->elementball.num;
	WFIFOSET(fd,packet_db[0x8cf].len);

	return;
}

/*==========================================
 * �\�E���G�i�W�[�\��(ID�w�著�M)
 *------------------------------------------
 */
static void clif_soulenergy_id(const int fd, struct map_session_data *dstsd)
{
	nullpo_retv(dstsd);

	WFIFOW(fd,0)=0xb73;
	WFIFOL(fd,2)=dstsd->bl.id;
	WFIFOW(fd,6)=dstsd->soulenergy.num;
	WFIFOSET(fd,packet_db[0xb73].len);

	return;
}

/*==========================================
 * ���̕\��(ID�w�著�M)
 *------------------------------------------
 */
static void clif_ball_id(const int fd, struct map_session_data *dstsd)
{
	nullpo_retv(dstsd);

	WFIFOW(fd,0)=0x1d0;
	WFIFOL(fd,2)=dstsd->bl.id;
	WFIFOW(fd,6)=dstsd->ball.num;
	WFIFOSET(fd,packet_db[0x1d0].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_spawnpc(struct map_session_data *sd)
{
	int len;

	nullpo_retv(sd);

	clif_set0078(sd,WFIFOP(sd->fd,0));

#if PACKETVER < 4
	len = packet_db[0x79].len;
	WFIFOW(sd->fd,0)=0x79;
	WFIFOLV(sd->fd,51,sd->status.base_level,sd->status.class_);
#elif PACKETVER < 7
	len = packet_db[0x1d9].len;
	WFIFOW(sd->fd,0)=0x1d9;
	WFIFOLV(sd->fd,51,sd->status.base_level,sd->status.class_);
#elif PACKETVER < 20080102
	len = packet_db[0x22b].len;
	WFIFOW(sd->fd,0)=0x22b;
	WFIFOLV(sd->fd,55,sd->status.base_level,sd->status.class_);
#elif PACKETVER < 20091104
	len = packet_db[0x2ed].len;
	WFIFOW(sd->fd,0)=0x2ed;
	WFIFOLV(sd->fd,55,sd->status.base_level,sd->status.class_);
	WFIFOW(sd->fd,57)=sd->status.font;
#elif PACKETVER < 20110111
	len = 62 + (int)strlen(sd->status.name);
	WFIFOW(sd->fd,0)=0x7f8;
	WFIFOW(sd->fd,2)=(unsigned short)len;
	WFIFOB(sd->fd,4)=0;
	WFIFOLV(sd->fd,58,sd->status.base_level,sd->status.class_);
	WFIFOW(sd->fd,60)=sd->status.font;
	strncpy(WFIFOP(sd->fd,62),sd->status.name,24);
#elif PACKETVER < 20120328
	len = 64 + (int)strlen(sd->status.name);
	WFIFOW(sd->fd,0)=0x858;
	WFIFOW(sd->fd,2)=(unsigned short)len;
	WFIFOB(sd->fd,4)=0;
	WFIFOLV(sd->fd,60,sd->status.base_level,sd->status.class_);
	WFIFOW(sd->fd,62)=sd->status.font;
	strncpy(WFIFOP(sd->fd,64),sd->status.name,24);
#elif PACKETVER < 20131223
	len = 73;
	WFIFOW(sd->fd,0)=0x90f;
	WFIFOW(sd->fd,2)=(unsigned short)len;
	WFIFOB(sd->fd,4)=0;
	WFIFOLV(sd->fd,60,sd->status.base_level,sd->status.class_);
	WFIFOW(sd->fd,62)=sd->status.font;
	WFIFOL(sd->fd,64)=0xffffffff;
	WFIFOL(sd->fd,68)=0xffffffff;
	WFIFOB(sd->fd,72)=0;
#elif PACKETVER < 20150513
	len = 77 + (int)strlen(sd->status.name);
	WFIFOW(sd->fd,0)=0x9dc;
	WFIFOW(sd->fd,2)=(unsigned short)len;
	WFIFOB(sd->fd,4)=0;
	WFIFOLV(sd->fd,64,sd->status.base_level,sd->status.class_);
	WFIFOW(sd->fd,66)=sd->status.font;
	WFIFOL(sd->fd,68)=0xffffffff;
	WFIFOL(sd->fd,72)=0xffffffff;
	WFIFOB(sd->fd,76)=0;
	strncpy(WFIFOP(sd->fd,77),sd->status.name,24);
#elif PACKETVER < 20180704
	len = 79 + (int)strlen(sd->status.name);
	WFIFOW(sd->fd,0)=0x9fe;
	WFIFOW(sd->fd,2)=(unsigned short)len;
	WFIFOB(sd->fd,4)=0;
	WFIFOLV(sd->fd,64,sd->status.base_level,sd->status.class_);
	WFIFOW(sd->fd,66)=sd->status.font;
	WFIFOL(sd->fd,68)=0xffffffff;
	WFIFOL(sd->fd,72)=0xffffffff;
	WFIFOB(sd->fd,76)=0;
	WFIFOW(sd->fd,77)=sd->status.style;
	strncpy(WFIFOP(sd->fd,79),sd->status.name,24);
#else
	len = 83 + (int)strlen(sd->status.name);
	WFIFOW(sd->fd,0)=0x9fe;
	WFIFOW(sd->fd,2)=(unsigned short)len;
	WFIFOB(sd->fd,4)=0;
	WFIFOLV(sd->fd,68,sd->status.base_level,sd->status.class_);
	WFIFOW(sd->fd,70)=sd->status.font;
	WFIFOL(sd->fd,72)=0xffffffff;
	WFIFOL(sd->fd,76)=0xffffffff;
	WFIFOB(sd->fd,80)=0;
	WFIFOW(sd->fd,81)=sd->status.style;
	strncpy(WFIFOP(sd->fd,83),sd->status.name,24);
#endif
	clif_send(WFIFOP(sd->fd,0),len,&sd->bl,AREA_WOS);

	// ���S�ȃC���r�W�u�����[�h�Ȃ瑗�M���Ȃ�
	if(!battle_config.gm_perfect_hide || !pc_isinvisible(sd)) {
		if(sd->sc.data[SC_KYOUGAKU].timer != -1)	// ����
			clif_seteffect_enter(&sd->bl,SI_KYOUGAKU,0,MOBID_PORING,0,0);
//		else if(sd->sc.data[SC_MONSTER_TRANSFORM].timer != -1)	// �����X�^�[�ϐg�V�X�e��
//			clif_seteffect_enter(&sd->bl,SI_MONSTER_TRANSFORM,0,sd->sc.data[SC_MONSTER_TRANSFORM].val1,0,0);
//		else if(sd->sc.data[SC_ACTIVE_MONSTER_TRANSFORM].timer != -1)	// �A�N�e�B�u�����X�^�[�ϐg
//			clif_seteffect_enter(&sd->bl,SI_ACTIVE_MONSTER_TRANSFORM,0,sd->sc.data[SC_ACTIVE_MONSTER_TRANSFORM].val1,0,0);
		else if(sd->sc.data[SC_ALL_RIDING].timer != -1)	// ����V�X�e��
			clif_seteffect_enter(&sd->bl,SI_ALL_RIDING,9999,1,25,0);
		if(sd->sc.data[SC_ON_PUSH_CART].timer != -1)	// �J�[�g
			clif_seteffect_enter(&sd->bl,SI_ON_PUSH_CART,9999,sd->sc.data[SC_ON_PUSH_CART].val1,0,0);
		if(sd->sc.data[SC_BANDING].timer != -1)	// �o���f�B���O
			clif_seteffect_enter(&sd->bl,SI_BANDING,9999,sd->sc.data[SC_BANDING].val1,0,0);
		if(sd->sc.data[SC_HAT_EFFECT].timer != -1)	// �������G�t�F�N�g
			clif_seteffect_enter(&sd->bl,SI_HAT_EFFECT,9999,sd->sc.data[SC_HAT_EFFECT].val1,0,0);
		if(sd->sc.data[SC_SUHIDE].timer != -1)	// �������
			clif_seteffect_enter(&sd->bl,SI_SUHIDE,9999,sd->sc.data[SC_SUHIDE].val1,0,0);
		if(pc_checkskill(sd,SU_SPRITEMABLE) > 0)	// �ɂ��
			clif_seteffect_enter(&sd->bl,SI_SPRITEMABLE,9999,1,0,0);
#if PACKETVER >= 20150513
		if(sd->hatEffect.count)
			clif_hat_effects(sd,&sd->bl,AREA);
#endif
	}
	if(sd->spiritball.num > 0)
		clif_spiritball(sd);
	if(sd->coin.num > 0)
		clif_coin(sd);
	if(sd->elementball.num > 0)	// �e�T�E�O�̋��̕\��
		clif_elementball(sd);
	if(sd->soulenergy.num > 0)
		clif_soulenergy(sd);
	if(sd->ball.num > 0)
		clif_ball(sd);
	if(sd->sc.data[SC_MILLENNIUMSHIELD].timer != -1)
		clif_mshield(sd,sd->sc.data[SC_MILLENNIUMSHIELD].val2);
	if(sd->sc.data[SC_FORCEOFVANGUARD].timer != -1)
		clif_mshield(sd,sd->sc.data[SC_FORCEOFVANGUARD].val4);
	if(sd->view_size!=0)
		clif_misceffect2(&sd->bl,422+sd->view_size);

	if (map[sd->bl.m].flag.rain)
		clif_misceffect3(sd->fd, sd->bl.id, 161);
	if (map[sd->bl.m].flag.snow)
		clif_misceffect3(sd->fd, sd->bl.id, 162);
	if (map[sd->bl.m].flag.sakura)
		clif_misceffect3(sd->fd, sd->bl.id, 163);
	if (map[sd->bl.m].flag.leaves)
		clif_misceffect3(sd->fd, sd->bl.id, 333);
	if (map[sd->bl.m].flag.fireworks)
		clif_misceffect3(sd->fd, sd->bl.id, 297);
	if (map[sd->bl.m].flag.fireworks)
		clif_misceffect3(sd->fd, sd->bl.id, 299);
	if (map[sd->bl.m].flag.fireworks)
		clif_misceffect3(sd->fd, sd->bl.id, 301);
	if (map[sd->bl.m].flag.cloud1)
		clif_misceffect3(sd->fd, sd->bl.id, 230);
	if (map[sd->bl.m].flag.cloud2)
		clif_misceffect3(sd->fd, sd->bl.id, 233);
	if (map[sd->bl.m].flag.cloud3)
		clif_misceffect3(sd->fd, sd->bl.id, 516);
	if (map[sd->bl.m].flag.fog)
		clif_misceffect3(sd->fd, sd->bl.id, 515);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_spawnnpc(struct npc_data *nd)
{
	unsigned char buf[128];
	int len;

	nullpo_retv(nd);

	if(nd->class_ < 0 || (nd->flag&1 && (nd->option&OPTION_HIDE)==0) || nd->class_ == INVISIBLE_CLASS)
		return;

#if PACKETVER < 20071106
	len = packet_db[0x7c].len;
	memset(buf,0,len);

	WBUFW(buf,0)=0x7c;
	WBUFL(buf,2)=nd->bl.id;
	WBUFW(buf,6)=nd->speed;
	WBUFW(buf,12)=nd->option;
	WBUFW(buf,20)=nd->class_;
	WBUFPOS(buf,36,nd->bl.x,nd->bl.y,nd->dir);
#elif PACKETVER < 20091104
	len = packet_db[0x7c].len;
	memset(buf,0,len);

	WBUFW(buf,0)=0x7c;
	WBUFB(buf,2)=0;
	WBUFL(buf,3)=nd->bl.id;
	WBUFW(buf,7)=nd->speed;
	WBUFW(buf,13)=nd->option;
	WBUFW(buf,21)=nd->class_;
	WBUFPOS(buf,37,nd->bl.x,nd->bl.y,nd->dir);
#elif PACKETVER < 20110111
	len = 62 + (int)strlen(nd->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x7f8;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=(nd->u.scr.moveable > 0)? 12: 6;
	WBUFL(buf,5)=nd->bl.id;
	WBUFW(buf,9)=nd->speed;
	WBUFL(buf,15)=nd->option;
	WBUFW(buf,19)=nd->class_;
	WBUFW(buf,33)=6;
	WBUFPOS(buf,53,nd->bl.x,nd->bl.y,nd->dir);
	strncpy(WBUFP(buf,62),nd->name,24);
#elif PACKETVER < 20120328
	len = 64 + (int)strlen(nd->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x858;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=(nd->u.scr.moveable > 0)? 12: 6;
	WBUFL(buf,5)=nd->bl.id;
	WBUFW(buf,9)=nd->speed;
	WBUFL(buf,15)=nd->option;
	WBUFW(buf,19)=nd->class_;
	WBUFW(buf,33)=6;
	WBUFPOS(buf,55,nd->bl.x,nd->bl.y,nd->dir);
	strncpy(WBUFP(buf,64),nd->name,24);
#elif PACKETVER < 20131223
	len = 73;
	memset(buf,0,len);

	WBUFW(buf,0)=0x90f;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=(nd->u.scr.moveable > 0)? 12: 6;
	WBUFL(buf,5)=nd->bl.id;
	WBUFW(buf,9)=nd->speed;
	WBUFL(buf,15)=nd->option;
	WBUFW(buf,19)=nd->class_;
	WBUFW(buf,33)=6;
	WBUFPOS(buf,55,nd->bl.x,nd->bl.y,nd->dir);
	WBUFL(buf,64)=0xffffffff;
	WBUFL(buf,68)=0xffffffff;
	WBUFB(buf,72)=0;
#elif PACKETVER < 20150513
	len = 77 + (int)strlen(nd->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9dc;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=(nd->u.scr.moveable > 0)? 12: 6;
	WBUFL(buf,5)=nd->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=nd->speed;
	WBUFL(buf,19)=nd->option;
	WBUFW(buf,23)=nd->class_;
	WBUFW(buf,37)=6;
	WBUFPOS(buf,59,nd->bl.x,nd->bl.y,nd->dir);
	WBUFL(buf,68)=0xffffffff;
	WBUFL(buf,72)=0xffffffff;
	WBUFB(buf,76)=0;
	strncpy(WBUFP(buf,77),nd->name,24);
#elif PACKETVER < 20180704
	len = 79 + (int)strlen(nd->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9fe;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=(nd->u.scr.moveable > 0)? 12: 6;
	WBUFL(buf,5)=nd->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=nd->speed;
	WBUFL(buf,19)=nd->option;
	WBUFW(buf,23)=nd->class_;
	WBUFW(buf,37)=6;
	WBUFPOS(buf,59,nd->bl.x,nd->bl.y,nd->dir);
	WBUFL(buf,68)=0xffffffff;
	WBUFL(buf,72)=0xffffffff;
	WBUFB(buf,76)=0;
	WBUFW(buf,77)=0;
	strncpy(WBUFP(buf,79),nd->name,24);
#else
	len = 83 + (int)strlen(nd->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9fe;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=(nd->u.scr.moveable > 0)? 12: 6;
	WBUFL(buf,5)=nd->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=nd->speed;
	WBUFL(buf,19)=nd->option;
	WBUFW(buf,23)=nd->class_;
	WBUFW(buf,41)=6;
	WBUFPOS(buf,63,nd->bl.x,nd->bl.y,nd->dir);
	WBUFL(buf,72)=0xffffffff;
	WBUFL(buf,76)=0xffffffff;
	WBUFB(buf,80)=0;
	WBUFW(buf,81)=0;
	strncpy(WBUFP(buf,83),nd->name,24);
#endif
	clif_send(buf,len,&nd->bl,AREA);

	len = clif_npc0078(nd,buf,NULL);
	clif_send(buf,len,&nd->bl,AREA);

	if(nd->view_size!=0)
		clif_misceffect2(&nd->bl,422+nd->view_size);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_spawndynamicnpc(struct map_session_data *sd, struct npc_data *nd, int x, int y, int dir, int class_)
{
	unsigned char buf[128];
	int len;

	nullpo_retv(sd);
	nullpo_retv(nd);

#if PACKETVER < 20071106
	len = packet_db[0x7c].len;
	memset(buf,0,len);

	WBUFW(buf,0)=0x7c;
	WBUFL(buf,2)=nd->bl.id;
	WBUFW(buf,6)=nd->speed;
	WBUFW(buf,12)=nd->option;
	WBUFW(buf,20)=class_;
	WBUFPOS(buf,36,x,y,dir);
#elif PACKETVER < 20091104
	len = packet_db[0x7c].len;
	memset(buf,0,len);

	WBUFW(buf,0)=0x7c;
	WBUFB(buf,2)=0;
	WBUFL(buf,3)=nd->bl.id;
	WBUFW(buf,7)=nd->speed;
	WBUFW(buf,13)=nd->option;
	WBUFW(buf,21)=class_;
	WBUFPOS(buf,37,x,y,dir);
#elif PACKETVER < 20110111
	len = 62 + (int)strlen(nd->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x7f8;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=(nd->u.scr.moveable > 0)? 12: 6;
	WBUFL(buf,5)=nd->bl.id;
	WBUFW(buf,9)=nd->speed;
	WBUFL(buf,15)=nd->option;
	WBUFW(buf,19)=class_;
	WBUFW(buf,33)=6;
	WBUFPOS(buf,53,x,y,dir);
	strncpy(WBUFP(buf,62),nd->name,24);
#elif PACKETVER < 20120328
	len = 64 + (int)strlen(nd->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x858;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=(nd->u.scr.moveable > 0)? 12: 6;
	WBUFL(buf,5)=nd->bl.id;
	WBUFW(buf,9)=nd->speed;
	WBUFL(buf,15)=nd->option;
	WBUFW(buf,19)=class_;
	WBUFW(buf,33)=6;
	WBUFPOS(buf,55,x,y,dir);
	strncpy(WBUFP(buf,64),nd->name,24);
#elif PACKETVER < 20131223
	len = 73;
	memset(buf,0,len);

	WBUFW(buf,0)=0x90f;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=(nd->u.scr.moveable > 0)? 12: 6;
	WBUFL(buf,5)=nd->bl.id;
	WBUFW(buf,9)=nd->speed;
	WBUFL(buf,15)=nd->option;
	WBUFW(buf,19)=class_;
	WBUFW(buf,33)=6;
	WBUFPOS(buf,55,x,y,dir);
	WBUFL(buf,64)=0xffffffff;
	WBUFL(buf,68)=0xffffffff;
	WBUFB(buf,72)=0;
#elif PACKETVER < 20150513
	len = 77 + (int)strlen(nd->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9dc;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=(nd->u.scr.moveable > 0)? 12: 6;
	WBUFL(buf,5)=nd->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=nd->speed;
	WBUFL(buf,19)=nd->option;
	WBUFW(buf,23)=class_;
	WBUFW(buf,37)=6;
	WBUFPOS(buf,59,x,y,dir);
	WBUFL(buf,68)=0xffffffff;
	WBUFL(buf,72)=0xffffffff;
	WBUFB(buf,76)=0;
	strncpy(WBUFP(buf,77),nd->name,24);
#elif PACKETVER < 20180704
	len = 79 + (int)strlen(nd->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9fe;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=(nd->u.scr.moveable > 0)? 12: 6;
	WBUFL(buf,5)=nd->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=nd->speed;
	WBUFL(buf,19)=nd->option;
	WBUFW(buf,23)=class_;
	WBUFW(buf,37)=6;
	WBUFPOS(buf,59,x,y,dir);
	WBUFL(buf,68)=0xffffffff;
	WBUFL(buf,72)=0xffffffff;
	WBUFB(buf,76)=0;
	WBUFW(buf,77)=0;
	strncpy(WBUFP(buf,79),nd->name,24);
#else
	len = 83 + (int)strlen(nd->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9fe;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=(nd->u.scr.moveable > 0)? 12: 6;
	WBUFL(buf,5)=nd->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=nd->speed;
	WBUFL(buf,19)=nd->option;
	WBUFW(buf,23)=class_;
	WBUFW(buf,41)=6;
	WBUFPOS(buf,63,x,y,dir);
	WBUFL(buf,72)=0xffffffff;
	WBUFL(buf,76)=0xffffffff;
	WBUFB(buf,80)=0;
	WBUFW(buf,81)=0;
	strncpy(WBUFP(buf,83),nd->name,24);
#endif
	memcpy(WFIFOP(sd->fd,0),buf,len);
	WFIFOSET(sd->fd,len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_spawnmob(struct mob_data *md)
{
	unsigned char buf[128];
	int len;

	nullpo_retv(md);

	if(!mob_is_pcview(md->class_)) {
#if PACKETVER < 20071106
		len = packet_db[0x7c].len;
		memset(buf,0,len);

		WBUFW(buf,0)=0x7c;
		WBUFL(buf,2)=md->bl.id;
		WBUFW(buf,6)=status_get_speed(&md->bl);
		WBUFW(buf,8)=md->sc.opt1;
		WBUFW(buf,10)=md->sc.opt2;
		WBUFW(buf,12)=md->sc.option;
		WBUFW(buf,20)=mob_get_viewclass(md->class_);
		WBUFPOS(buf,36,md->bl.x,md->bl.y,md->dir);
#elif PACKETVER < 20091104
		len = packet_db[0x7c].len;
		memset(buf,0,len);

		WBUFW(buf,0)=0x7c;
		WBUFB(buf,2)=0;
		WBUFL(buf,3)=md->bl.id;
		WBUFW(buf,7)=status_get_speed(&md->bl);
		WBUFW(buf,9)=md->sc.opt1;
		WBUFW(buf,11)=md->sc.opt2;
		WBUFW(buf,13)=md->sc.option;
		WBUFW(buf,21)=mob_get_viewclass(md->class_);
		WBUFPOS(buf,37,md->bl.x,md->bl.y,md->dir);
#elif PACKETVER < 20110111
		len = 62 + (int)strlen(md->name);
		memset(buf,0,len);

		WBUFW(buf,0)=0x7f8;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=5;
		WBUFL(buf,5)=md->bl.id;
		WBUFW(buf,9)=status_get_speed(&md->bl);
		WBUFW(buf,11)=md->sc.opt1;
		WBUFW(buf,13)=md->sc.opt2;
		WBUFL(buf,15)=md->sc.option;
		WBUFW(buf,19)=mob_get_viewclass(md->class_);
		WBUFW(buf,33)=5;
		WBUFPOS(buf,53,md->bl.x,md->bl.y,md->dir);
		WBUFLV(buf,58,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
		strncpy(WBUFP(buf,62),md->name,24);
#elif PACKETVER < 20120328
		len = 64 + (int)strlen(md->name);
		memset(buf,0,len);

		WBUFW(buf,0)=0x858;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=5;
		WBUFL(buf,5)=md->bl.id;
		WBUFW(buf,9)=status_get_speed(&md->bl);
		WBUFW(buf,11)=md->sc.opt1;
		WBUFW(buf,13)=md->sc.opt2;
		WBUFL(buf,15)=md->sc.option;
		WBUFW(buf,19)=mob_get_viewclass(md->class_);
		WBUFW(buf,33)=5;
		WBUFPOS(buf,55,md->bl.x,md->bl.y,md->dir);
		WBUFLV(buf,60,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
		strncpy(WBUFP(buf,64),md->name,24);
#elif PACKETVER < 20131223
		len = 73;
		memset(buf,0,len);

		WBUFW(buf,0)=0x90f;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=5;
		WBUFL(buf,5)=md->bl.id;
		WBUFW(buf,9)=status_get_speed(&md->bl);
		WBUFW(buf,11)=md->sc.opt1;
		WBUFW(buf,13)=md->sc.opt2;
		WBUFL(buf,15)=md->sc.option;
		WBUFW(buf,19)=mob_get_viewclass(md->class_);
		WBUFW(buf,33)=5;
		WBUFPOS(buf,55,md->bl.x,md->bl.y,md->dir);
		WBUFLV(buf,60,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
		WBUFL(buf,64)=0xffffffff;
		WBUFL(buf,68)=0xffffffff;
		WBUFB(buf,72)=0;
#elif PACKETVER < 20150513
		len = 77 + (int)strlen(md->name);
		memset(buf,0,len);

		WBUFW(buf,0)=0x9dc;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=5;
		WBUFL(buf,5)=md->bl.id;
		WBUFL(buf,9)=0;
		WBUFW(buf,13)=status_get_speed(&md->bl);
		WBUFW(buf,15)=md->sc.opt1;
		WBUFW(buf,17)=md->sc.opt2;
		WBUFL(buf,19)=md->sc.option;
		WBUFW(buf,23)=mob_get_viewclass(md->class_);
		WBUFW(buf,37)=5;
		WBUFPOS(buf,59,md->bl.x,md->bl.y,md->dir);
		WBUFLV(buf,64,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
		WBUFL(buf,68)=0xffffffff;
		WBUFL(buf,72)=0xffffffff;
		WBUFB(buf,76)=0;
		strncpy(WBUFP(buf,77),md->name,24);
#elif PACKETVER < 20180704
		len = 79 + (int)strlen(md->name);
		memset(buf,0,len);

		WBUFW(buf,0)=0x9fe;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=5;
		WBUFL(buf,5)=md->bl.id;
		WBUFL(buf,9)=0;
		WBUFW(buf,13)=status_get_speed(&md->bl);
		WBUFW(buf,15)=md->sc.opt1;
		WBUFW(buf,17)=md->sc.opt2;
		WBUFL(buf,19)=md->sc.option;
		WBUFW(buf,23)=mob_get_viewclass(md->class_);
		WBUFW(buf,37)=5;
		WBUFPOS(buf,59,md->bl.x,md->bl.y,md->dir);
		WBUFLV(buf,64,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
		WBUFL(buf,68)=0xffffffff;
		WBUFL(buf,72)=0xffffffff;
		WBUFB(buf,76)=0;
		WBUFW(buf,77)=0;
		strncpy(WBUFP(buf,79),md->name,24);
#else
		len = 83 + (int)strlen(md->name);
		memset(buf,0,len);

		WBUFW(buf,0)=0x9fe;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=5;
		WBUFL(buf,5)=md->bl.id;
		WBUFL(buf,9)=0;
		WBUFW(buf,13)=status_get_speed(&md->bl);
		WBUFW(buf,15)=md->sc.opt1;
		WBUFW(buf,17)=md->sc.opt2;
		WBUFL(buf,19)=md->sc.option;
		WBUFW(buf,23)=mob_get_viewclass(md->class_);
		WBUFW(buf,41)=5;
		WBUFPOS(buf,63,md->bl.x,md->bl.y,md->dir);
		WBUFLV(buf,68,status_get_lv(&md->bl),mob_get_viewclass(md->class_));
		WBUFL(buf,72)=0xffffffff;
		WBUFL(buf,76)=0xffffffff;
		WBUFB(buf,80)=0;
		WBUFW(buf,81)=0;
		strncpy(WBUFP(buf,83),md->name,24);
#endif
		clif_send(buf,len,&md->bl,AREA);
	}

	len = clif_mob0078(md,buf);
	clif_send(buf,len,&md->bl,AREA);

	if(md->view_size!=0)
		clif_misceffect2(&md->bl,422+md->view_size);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_spawnpet(struct pet_data *pd)
{
	unsigned char buf[128];
	int len;

	nullpo_retv(pd);

	if(!mob_is_pcview(pd->class_)) {
#if PACKETVER < 20071106
		len = packet_db[0x7c].len;
		memset(buf,0,len);

		WBUFW(buf,0)=0x7c;
		WBUFL(buf,2)=pd->bl.id;
		WBUFW(buf,6)=pd->speed;
		WBUFW(buf,20)=mob_get_viewclass(pd->class_);
		WBUFPOS(buf,36,pd->bl.x,pd->bl.y,pd->dir);
#elif PACKETVER < 20091104
		len = packet_db[0x7c].len;
		memset(buf,0,len);

		WBUFW(buf,0)=0x7c;
		WBUFB(buf,2)=0;
		WBUFL(buf,3)=pd->bl.id;
		WBUFW(buf,7)=pd->speed;
		WBUFW(buf,21)=mob_get_viewclass(pd->class_);
		WBUFPOS(buf,37,pd->bl.x,pd->bl.y,pd->dir);
#elif PACKETVER < 20110111
		len = 62 + (int)strlen(pd->name);
		memset(buf,0,len);

		WBUFW(buf,0)=0x7f8;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=7;
		WBUFL(buf,5)=pd->bl.id;
		WBUFW(buf,9)=pd->speed;
		WBUFW(buf,19)=mob_get_viewclass(pd->class_);
		WBUFW(buf,33)=7;
		WBUFPOS(buf,53,pd->bl.x,pd->bl.y,pd->dir);
		WBUFLV(buf,58,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
		strncpy(WBUFP(buf,62),pd->name,24);
#elif PACKETVER < 20120328
		len = 64 + (int)strlen(pd->name);
		memset(buf,0,len);

		WBUFW(buf,0)=0x858;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=7;
		WBUFL(buf,5)=pd->bl.id;
		WBUFW(buf,9)=pd->speed;
		WBUFW(buf,19)=mob_get_viewclass(pd->class_);
		WBUFW(buf,33)=7;
		WBUFPOS(buf,55,pd->bl.x,pd->bl.y,pd->dir);
		WBUFLV(buf,60,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
		strncpy(WBUFP(buf,64),pd->name,24);
#elif PACKETVER < 20131223
		len = 73;
		memset(buf,0,len);

		WBUFW(buf,0)=0x90f;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=7;
		WBUFL(buf,5)=pd->bl.id;
		WBUFW(buf,9)=pd->speed;
		WBUFW(buf,19)=mob_get_viewclass(pd->class_);
		WBUFW(buf,33)=7;
		WBUFPOS(buf,55,pd->bl.x,pd->bl.y,pd->dir);
		WBUFLV(buf,60,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
		WBUFL(buf,64)=0xffffffff;
		WBUFL(buf,68)=0xffffffff;
		WBUFB(buf,72)=0;
#elif PACKETVER < 20150513
		len = 77 + (int)strlen(pd->name);
		memset(buf,0,len);

		WBUFW(buf,0)=0x9dc;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=7;
		WBUFL(buf,5)=pd->bl.id;
		WBUFL(buf,9)=0;
		WBUFW(buf,13)=pd->speed;
		WBUFW(buf,23)=mob_get_viewclass(pd->class_);
		WBUFW(buf,37)=7;
		WBUFPOS(buf,59,pd->bl.x,pd->bl.y,pd->dir);
		WBUFLV(buf,64,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
		WBUFL(buf,68)=0xffffffff;
		WBUFL(buf,72)=0xffffffff;
		WBUFB(buf,76)=0;
		strncpy(WBUFP(buf,77),pd->name,24);
#elif PACKETVER < 20180704
		len = 79 + (int)strlen(pd->name);
		memset(buf,0,len);

		WBUFW(buf,0)=0x9fe;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=7;
		WBUFL(buf,5)=pd->bl.id;
		WBUFL(buf,9)=0;
		WBUFW(buf,13)=pd->speed;
		WBUFW(buf,23)=mob_get_viewclass(pd->class_);
		WBUFW(buf,37)=7;
		WBUFPOS(buf,59,pd->bl.x,pd->bl.y,pd->dir);
		WBUFLV(buf,64,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
		WBUFL(buf,68)=0xffffffff;
		WBUFL(buf,72)=0xffffffff;
		WBUFB(buf,76)=0;
		WBUFW(buf,77)=0;
		strncpy(WBUFP(buf,79),pd->name,24);
#else
		len = 83 + (int)strlen(pd->name);
		memset(buf,0,len);

		WBUFW(buf,0)=0x9fe;
		WBUFW(buf,2)=(unsigned short)len;
		WBUFB(buf,4)=7;
		WBUFL(buf,5)=pd->bl.id;
		WBUFL(buf,9)=0;
		WBUFW(buf,13)=pd->speed;
		WBUFW(buf,23)=mob_get_viewclass(pd->class_);
		WBUFW(buf,41)=7;
		WBUFPOS(buf,63,pd->bl.x,pd->bl.y,pd->dir);
		WBUFLV(buf,68,status_get_lv(&pd->bl),mob_get_viewclass(pd->class_));
		WBUFL(buf,72)=0xffffffff;
		WBUFL(buf,76)=0xffffffff;
		WBUFB(buf,80)=0;
		WBUFW(buf,81)=0;
		strncpy(WBUFP(buf,83),pd->name,24);
#endif
		clif_send(buf,len,&pd->bl,AREA);
	}

	len = clif_pet0078(pd,buf);
	clif_send(buf,len,&pd->bl,AREA);

	if(pd->view_size!=0)
		clif_misceffect2(&pd->bl,422+pd->view_size);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_spawnhom(struct homun_data *hd)
{
	unsigned char buf[128];
	int len;

	nullpo_retv(hd);

#if PACKETVER < 20071106
	len = packet_db[0x7c].len;
	memset(buf,0,len);

	WBUFW(buf,0) =0x7c;
	WBUFL(buf,2) =hd->bl.id;
	WBUFW(buf,6) =hd->speed;
	WBUFW(buf,20)=hd->view_class;
	WBUFW(buf,28)=8;		// ���ׂ�����Œ�
	WBUFPOS(buf,36,hd->bl.x,hd->bl.y,hd->dir);
#elif PACKETVER < 20091104
	len = packet_db[0x7c].len;
	memset(buf,0,len);

	WBUFW(buf,0) =0x7c;
	WBUFB(buf,2) =0;
	WBUFL(buf,3) =hd->bl.id;
	WBUFW(buf,7) =hd->speed;
	WBUFW(buf,21)=hd->view_class;
	WBUFW(buf,29)=8;		// ���ׂ�����Œ�
	WBUFPOS(buf,37,hd->bl.x,hd->bl.y,hd->dir);
#elif PACKETVER < 20110111
	len = 62 + (int)strlen(hd->status.name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x7f8;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=8;
	WBUFL(buf,5)=hd->bl.id;
	WBUFW(buf,9)=hd->speed;
	WBUFW(buf,19)=hd->view_class;
	WBUFW(buf,33)=8;
	WBUFPOS(buf,53,hd->bl.x,hd->bl.y,hd->dir);
	WBUFLV(buf,58,status_get_lv(&hd->bl),hd->view_class);
	strncpy(WBUFP(buf,62),hd->status.name,24);
#elif PACKETVER < 20120328
	len = 64 + (int)strlen(hd->status.name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x858;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=8;
	WBUFL(buf,5)=hd->bl.id;
	WBUFW(buf,9)=hd->speed;
	WBUFW(buf,19)=hd->view_class;
	WBUFW(buf,33)=8;
	WBUFPOS(buf,55,hd->bl.x,hd->bl.y,hd->dir);
	WBUFLV(buf,60,status_get_lv(&hd->bl),hd->view_class);
	strncpy(WBUFP(buf,64),hd->status.name,24);
#elif PACKETVER < 20131223
	len = 73;
	memset(buf,0,len);

	WBUFW(buf,0)=0x90f;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=8;
	WBUFL(buf,5)=hd->bl.id;
	WBUFW(buf,9)=hd->speed;
	WBUFW(buf,19)=hd->view_class;
	WBUFW(buf,33)=8;
	WBUFPOS(buf,55,hd->bl.x,hd->bl.y,hd->dir);
	WBUFLV(buf,60,status_get_lv(&hd->bl),hd->view_class);
	WBUFL(buf,64)=0xffffffff;
	WBUFL(buf,68)=0xffffffff;
	WBUFB(buf,72)=0;
#elif PACKETVER < 20150513
	len = 77 + (int)strlen(hd->status.name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9dc;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=8;
	WBUFL(buf,5)=hd->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=hd->speed;
	WBUFW(buf,23)=hd->view_class;
	WBUFW(buf,37)=8;
	WBUFPOS(buf,59,hd->bl.x,hd->bl.y,hd->dir);
	WBUFLV(buf,64,status_get_lv(&hd->bl),hd->view_class);
	WBUFL(buf,68)=0xffffffff;
	WBUFL(buf,72)=0xffffffff;
	WBUFB(buf,76)=0;
	strncpy(WBUFP(buf,77),hd->status.name,24);
#elif PACKETVER < 20180704
	len = 79 + (int)strlen(hd->status.name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9fe;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=8;
	WBUFL(buf,5)=hd->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=hd->speed;
	WBUFW(buf,23)=hd->view_class;
	WBUFW(buf,37)=8;
	WBUFPOS(buf,59,hd->bl.x,hd->bl.y,hd->dir);
	WBUFLV(buf,64,status_get_lv(&hd->bl),hd->view_class);
	WBUFL(buf,68)=0xffffffff;
	WBUFL(buf,72)=0xffffffff;
	WBUFB(buf,76)=0;
	WBUFW(buf,77)=0;
	strncpy(WBUFP(buf,79),hd->status.name,24);
#else
	len = 83 + (int)strlen(hd->status.name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9fe;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=8;
	WBUFL(buf,5)=hd->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=hd->speed;
	WBUFW(buf,23)=hd->view_class;
	WBUFW(buf,41)=8;
	WBUFPOS(buf,63,hd->bl.x,hd->bl.y,hd->dir);
	WBUFLV(buf,68,status_get_lv(&hd->bl),hd->view_class);
	WBUFL(buf,72)=0xffffffff;
	WBUFL(buf,76)=0xffffffff;
	WBUFB(buf,80)=0;
	WBUFW(buf,81)=0;
	strncpy(WBUFP(buf,83),hd->status.name,24);
#endif
	clif_send(buf,len,&hd->bl,AREA);

	// �z���ł́A0x78�p�P�b�g��A����ɑ���p�P�b�g�̊m�F�ł���
	//len = clif_hom0078(hd,buf);
	//clif_send(buf,len,&hd->bl,AREA);

	if(hd->view_size!=0)
		clif_misceffect2(&hd->bl,422+hd->view_size);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_spawnmerc(struct merc_data *mcd)
{
	unsigned char buf[128];
	int len;

	nullpo_retv(mcd);

#if PACKETVER < 20071106
	len = packet_db[0x7c].len;
	memset(buf,0,len);

	WBUFW(buf,0) =0x7c;
	WBUFL(buf,2) =mcd->bl.id;
	WBUFW(buf,6) =mcd->speed;
	WBUFW(buf,20)=mcd->view_class;
	WBUFW(buf,28)=8;
	WBUFPOS(buf,36,mcd->bl.x,mcd->bl.y,mcd->dir);
#elif PACKETVER < 20091104
	len = packet_db[0x7c].len;
	memset(buf,0,len);

	WBUFW(buf,0) =0x7c;
	WBUFB(buf,2) =0;
	WBUFL(buf,3) =mcd->bl.id;
	WBUFW(buf,7) =mcd->speed;
	WBUFW(buf,21)=mcd->view_class;
	WBUFW(buf,29)=8;
	WBUFPOS(buf,37,mcd->bl.x,mcd->bl.y,mcd->dir);
#elif PACKETVER < 20110111
	len = 62 + (int)strlen(mcd->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x7f8;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=9;
	WBUFL(buf,5)=mcd->bl.id;
	WBUFW(buf,9)=mcd->speed;
	WBUFW(buf,19)=mcd->view_class;
	WBUFW(buf,33)=9;
	WBUFPOS(buf,53,mcd->bl.x,mcd->bl.y,mcd->dir);
	WBUFLV(buf,58,status_get_lv(&mcd->bl),mcd->view_class);
	strncpy(WBUFP(buf,62),mcd->name,24);
#elif PACKETVER < 20120328
	len = 64 + (int)strlen(mcd->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x858;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=9;
	WBUFL(buf,5)=mcd->bl.id;
	WBUFW(buf,9)=mcd->speed;
	WBUFW(buf,19)=mcd->view_class;
	WBUFW(buf,33)=9;
	WBUFPOS(buf,55,mcd->bl.x,mcd->bl.y,mcd->dir);
	WBUFLV(buf,60,status_get_lv(&mcd->bl),mcd->view_class);
	strncpy(WBUFP(buf,64),mcd->name,24);
#elif PACKETVER < 20131223
	len = 73;
	memset(buf,0,len);

	WBUFW(buf,0)=0x90f;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=9;
	WBUFL(buf,5)=mcd->bl.id;
	WBUFW(buf,9)=mcd->speed;
	WBUFW(buf,19)=mcd->view_class;
	WBUFW(buf,33)=9;
	WBUFPOS(buf,55,mcd->bl.x,mcd->bl.y,mcd->dir);
	WBUFLV(buf,60,status_get_lv(&mcd->bl),mcd->view_class);
	WBUFL(buf,64)=0xffffffff;
	WBUFL(buf,68)=0xffffffff;
	WBUFB(buf,72)=0;
#elif PACKETVER < 20150513
	len = 77 + (int)strlen(mcd->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9dc;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=9;
	WBUFL(buf,5)=mcd->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=mcd->speed;
	WBUFW(buf,23)=mcd->view_class;
	WBUFW(buf,37)=9;
	WBUFPOS(buf,59,mcd->bl.x,mcd->bl.y,mcd->dir);
	WBUFLV(buf,64,status_get_lv(&mcd->bl),mcd->view_class);
	WBUFL(buf,68)=0xffffffff;
	WBUFL(buf,72)=0xffffffff;
	WBUFB(buf,76)=0;
	strncpy(WBUFP(buf,77),mcd->name,24);
#elif PACKETVER < 20180704
	len = 79 + (int)strlen(mcd->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9fe;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=9;
	WBUFL(buf,5)=mcd->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=mcd->speed;
	WBUFW(buf,23)=mcd->view_class;
	WBUFW(buf,37)=9;
	WBUFPOS(buf,59,mcd->bl.x,mcd->bl.y,mcd->dir);
	WBUFLV(buf,64,status_get_lv(&mcd->bl),mcd->view_class);
	WBUFL(buf,68)=0xffffffff;
	WBUFL(buf,72)=0xffffffff;
	WBUFB(buf,76)=0;
	WBUFW(buf,77)=0;
	strncpy(WBUFP(buf,79),mcd->name,24);
#else
	len = 83 + (int)strlen(mcd->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9fe;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=9;
	WBUFL(buf,5)=mcd->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=mcd->speed;
	WBUFW(buf,23)=mcd->view_class;
	WBUFW(buf,41)=9;
	WBUFPOS(buf,63,mcd->bl.x,mcd->bl.y,mcd->dir);
	WBUFLV(buf,68,status_get_lv(&mcd->bl),mcd->view_class);
	WBUFL(buf,72)=0xffffffff;
	WBUFL(buf,76)=0xffffffff;
	WBUFB(buf,80)=0;
	WBUFW(buf,81)=0;
	strncpy(WBUFP(buf,83),mcd->name,24);
#endif
	clif_send(buf,len,&mcd->bl,AREA);

	if(mcd->view_size!=0)
		clif_misceffect2(&mcd->bl,422+mcd->view_size);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_spawnelem(struct elem_data *eld)
{
	unsigned char buf[128];
	int len;

	nullpo_retv(eld);

#if PACKETVER < 20071106
	len = packet_db[0x7c].len;
	memset(buf,0,len);

	WBUFW(buf,0) =0x7c;
	WBUFL(buf,2) =eld->bl.id;
	WBUFW(buf,6) =eld->speed;
	WBUFW(buf,20)=eld->view_class;
	WBUFW(buf,28)=8;
	WBUFPOS(buf,36,eld->bl.x,eld->bl.y,eld->dir);
#elif PACKETVER < 20091104
	len = packet_db[0x7c].len;
	memset(buf,0,len);

	WBUFW(buf,0) =0x7c;
	WBUFB(buf,2) =10;
	WBUFL(buf,3) =eld->bl.id;
	WBUFW(buf,7) =eld->speed;
	WBUFW(buf,21)=eld->view_class;
	WBUFW(buf,29)=8;
	WBUFPOS(buf,37,eld->bl.x,eld->bl.y,eld->dir);
#elif PACKETVER < 20110111
	len = 62 + (int)strlen(eld->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x7f8;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=10;
	WBUFL(buf,5)=eld->bl.id;
	WBUFW(buf,9)=eld->speed;
	WBUFW(buf,19)=eld->view_class;
	WBUFW(buf,33)=9;
	WBUFPOS(buf,53,eld->bl.x,eld->bl.y,eld->dir);
	WBUFLV(buf,58,status_get_lv(&eld->bl),eld->view_class);
	strncpy(WBUFP(buf,62),eld->name,24);
#elif PACKETVER < 20120328
	len = 64 + (int)strlen(eld->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x858;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=10;
	WBUFL(buf,5)=eld->bl.id;
	WBUFW(buf,9)=eld->speed;
	WBUFW(buf,19)=eld->view_class;
	WBUFW(buf,33)=9;
	WBUFPOS(buf,55,eld->bl.x,eld->bl.y,eld->dir);
	WBUFLV(buf,60,status_get_lv(&eld->bl),eld->view_class);
	strncpy(WBUFP(buf,64),eld->name,24);
#elif PACKETVER < 20131223
	len = 73;
	memset(buf,0,len);

	WBUFW(buf,0)=0x90f;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=10;
	WBUFL(buf,5)=eld->bl.id;
	WBUFW(buf,9)=eld->speed;
	WBUFW(buf,19)=eld->view_class;
	WBUFW(buf,33)=9;
	WBUFPOS(buf,55,eld->bl.x,eld->bl.y,eld->dir);
	WBUFLV(buf,60,status_get_lv(&eld->bl),eld->view_class);
	WBUFL(buf,64)=0xffffffff;
	WBUFL(buf,68)=0xffffffff;
	WBUFB(buf,72)=0;
#elif PACKETVER < 20150513
	len = 77 + (int)strlen(eld->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9dc;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=10;
	WBUFL(buf,5)=eld->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=eld->speed;
	WBUFW(buf,23)=eld->view_class;
	WBUFW(buf,37)=9;
	WBUFPOS(buf,59,eld->bl.x,eld->bl.y,eld->dir);
	WBUFLV(buf,64,status_get_lv(&eld->bl),eld->view_class);
	WBUFL(buf,68)=0xffffffff;
	WBUFL(buf,72)=0xffffffff;
	WBUFB(buf,76)=0;
	strncpy(WBUFP(buf,77),eld->name,24);
#elif PACKETVER < 20180704
	len = 79 + (int)strlen(eld->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9fe;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=10;
	WBUFL(buf,5)=eld->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=eld->speed;
	WBUFW(buf,23)=eld->view_class;
	WBUFW(buf,37)=9;
	WBUFPOS(buf,59,eld->bl.x,eld->bl.y,eld->dir);
	WBUFLV(buf,64,status_get_lv(&eld->bl),eld->view_class);
	WBUFL(buf,68)=0xffffffff;
	WBUFL(buf,72)=0xffffffff;
	WBUFB(buf,76)=0;
	WBUFW(buf,77)=0;
	strncpy(WBUFP(buf,79),eld->name,24);
#else
	len = 83 + (int)strlen(eld->name);
	memset(buf,0,len);

	WBUFW(buf,0)=0x9fe;
	WBUFW(buf,2)=(unsigned short)len;
	WBUFB(buf,4)=10;
	WBUFL(buf,5)=eld->bl.id;
	WBUFL(buf,9)=0;
	WBUFW(buf,13)=eld->speed;
	WBUFW(buf,23)=eld->view_class;
	WBUFW(buf,41)=9;
	WBUFPOS(buf,63,eld->bl.x,eld->bl.y,eld->dir);
	WBUFLV(buf,68,status_get_lv(&eld->bl),eld->view_class);
	WBUFL(buf,72)=0xffffffff;
	WBUFL(buf,76)=0xffffffff;
	WBUFB(buf,80)=0;
	WBUFW(buf,81)=0;
	strncpy(WBUFP(buf,83),eld->name,24);
#endif
	clif_send(buf,len,&eld->bl,AREA);

	if(eld->view_size!=0)
		clif_misceffect2(&eld->bl,422+eld->view_size);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_servertick(struct map_session_data *sd)
{
	int fd;
	unsigned int tick = gettick();

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x7f;
	WFIFOL(fd,2)=tick;
	WFIFOSET(fd,packet_db[0x7f].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static int clif_set_mobhpinfo(struct block_list *bl, va_list ap)
{
	int len;
	unsigned short offset = 0;
	struct map_session_data *sd;
	struct mob_data *md;

	nullpo_retr(0,bl);
	nullpo_retr(0,ap);
	nullpo_retr(0,sd=(struct map_session_data *)bl);
	nullpo_retr(0,md=va_arg(ap,struct mob_data *));

	len = clif_mob007b(md,WFIFOP(sd->fd,0));
#if PACKETVER >= 20180704
	offset = 14;
#elif PACKETVER >= 20131223
	offset = 10;
#elif PACKETVER >= 20120328
	offset = 6;
#endif

	// �����Ԉُ펞�E�G���y���E���EMVP�����X�^�[�ɂ͕\�����Ȃ�
	if(mob_check_hpinfo(sd,md))
	{
		WFIFOL(sd->fd,65+offset)=0xffffffff;
		WFIFOL(sd->fd,69+offset)=0xffffffff;
	} else {
		WFIFOL(sd->fd,65+offset)=status_get_max_hp(&md->bl);
		WFIFOL(sd->fd,69+offset)=status_get_hp(&md->bl);
	}
	WFIFOSET(sd->fd,len);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_walkok(struct map_session_data *sd)
{
	int fd;
	unsigned int tick = gettick();

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x87;
	WFIFOL(fd,2)=tick;
	WFIFOPOS2(fd,6,sd->bl.x,sd->bl.y,sd->ud.to_x,sd->ud.to_y,8,8);
	WFIFOSET(fd,packet_db[0x87].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_move_sub(struct block_list *bl)
{
	int len;

	nullpo_retv(bl);

	switch(bl->type) {
		case BL_PC:
		{
			struct map_session_data *sd = (struct map_session_data *)bl;
			len = clif_set007b(sd,WFIFOP(sd->fd,0));
			clif_send(WFIFOP(sd->fd,0),len,&sd->bl,AREA_WOS);
			break;
		}
		case BL_MOB:
		{
			struct mob_data *md = (struct mob_data *)bl;
#if PACKETVER < 20120328
			unsigned char buf[128];
			len = clif_mob007b(md,buf);
			clif_send(buf,len,&md->bl,AREA_WOS);
#else
			map_foreachinarea(clif_set_mobhpinfo,md->bl.m,md->bl.x-AREA_SIZE,md->bl.y-AREA_SIZE,md->bl.x+AREA_SIZE,md->bl.y+AREA_SIZE,BL_PC,md);
#endif
			break;
		}
		case BL_PET:
		{
			unsigned char buf[128];
			struct pet_data *pd = (struct pet_data *)bl;
			len = clif_pet007b(pd,buf);
			clif_send(buf,len,&pd->bl,AREA_WOS);
			break;
		}
		case BL_HOM:
		{
			unsigned char buf[128];
			struct homun_data *hd = (struct homun_data *)bl;
			len = clif_hom007b(hd,buf);
			clif_send(buf,len,&hd->bl,AREA_WOS);
			break;
		}
		case BL_MERC:
		{
			unsigned char buf[128];
			struct merc_data *mcd = (struct merc_data *)bl;
			len = clif_merc007b(mcd,buf);
			clif_send(buf,len,&mcd->bl,AREA_WOS);
			break;
		}
		case BL_ELEM:
		{
			unsigned char buf[128];
			struct elem_data *eld = (struct elem_data *)bl;
			len = clif_elem007b(eld,buf);
			clif_send(buf,len,&eld->bl,AREA_WOS);
			break;
		}
		case BL_NPC:
		{
			unsigned char buf[128];
			struct npc_data *nd = (struct npc_data *)bl;
			len = clif_npc007b(nd,buf,NULL);
			clif_send(buf,len,&nd->bl,AREA_WOS);
			break;
		}
		default:
			break;
	}

	return;
}

void clif_move(struct block_list *bl)
{
	nullpo_retv(bl);

	// ���S�ȃC���r�W�u�����[�h�Ȃ瑗�M���Ȃ�
	if(bl->type == BL_PC && battle_config.gm_perfect_hide) {
		struct map_session_data *sd = (struct map_session_data *)bl;
		if(sd && pc_isinvisible(sd))
			return;
	}

#if PACKETVER < 20091104
	{
		struct unit_data *ud = unit_bl2ud(bl);
		if(ud) {
			unsigned int tick = gettick();
			unsigned char buf[16];

			if(ud->state.change_speed) {
				// ���x���ύX���ꂽ�Ƃ��͌Â����s�p�P�b�g�𑗐M����
				clif_move_sub(bl);
				ud->state.change_speed = 0;
			}

			WBUFW(buf,0)=0x86;
			WBUFL(buf,2)=bl->id;
			WBUFPOS2(buf,6,bl->x,bl->y,ud->to_x,ud->to_y,8,8);
			WBUFL(buf,12)=tick;
			clif_send(buf, packet_db[0x86].len, bl, AREA_WOS);
		}
	}
#else
	clif_move_sub(bl);
#endif
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_quitsave(struct map_session_data *sd)
{
	map_quit(sd);
	chrif_chardisconnect(sd);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static int clif_waitclose(int tid,unsigned int tick,int id,void *data)
{
	if(session[id])
		session[id]->eof=1;
	close(id);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_setwaitclose(int fd)
{
	add_timer(gettick()+5000,clif_waitclose,fd,NULL);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_changemap(struct map_session_data *sd,const char *mapname,int x,int y)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x91;
	memcpy(WFIFOP(fd,2),mapname,16);
	WFIFOW(fd,18)=x;
	WFIFOW(fd,20)=y;
	WFIFOSET(fd,packet_db[0x91].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_changemapserver(struct map_session_data *sd, const char *mapname, int x, int y, unsigned long ip, unsigned short port)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
#if PACKETVER < 20170315
	WFIFOW(fd,0)=0x92;
	memcpy(WFIFOP(fd,2),mapname,16);
	WFIFOW(fd,18)=x;
	WFIFOW(fd,20)=y;
	WFIFOL(fd,22)=ip;
	WFIFOW(fd,26)=port;
	WFIFOSET(fd,packet_db[0x92].len);
#else
	WFIFOW(fd,0)=0xac7;
	memcpy(WFIFOP(fd,2),mapname,16);
	WFIFOW(fd,18)=x;
	WFIFOW(fd,20)=y;
	WFIFOL(fd,22)=ip;
	WFIFOW(fd,26)=port;
	memset(WFIFOP(fd,28), 0, 128);		//TODO: dnshost name
	WFIFOSET(fd,packet_db[0xac7].len);
#endif

	return;
}

/*==========================================
 * �ʒu�␳
 *------------------------------------------
 */
int clif_fixpos(struct block_list *bl)
{
	nullpo_retr(0, bl);

	if(battle_config.clif_fixpos_type)
	{
		int x[4], y[4];
		// clif_fixpos2 �p�̃f�[�^���쐬
		x[0] = bl->x - AREA_SIZE;
		x[1] = bl->x + AREA_SIZE;
		x[2] = bl->x - AREA_SIZE;
		x[3] = bl->x + AREA_SIZE;
		y[0] = bl->y - AREA_SIZE;
		y[1] = bl->y + AREA_SIZE;
		y[2] = bl->y - AREA_SIZE;
		y[3] = bl->y + AREA_SIZE;
		clif_fixpos2(bl, x, y);
	}else{
		unsigned char buf[16];
		WBUFW(buf,0)=0x88;
		WBUFL(buf,2)=bl->id;
		WBUFW(buf,6)=bl->x;
		WBUFW(buf,8)=bl->y;
		clif_send(buf,packet_db[0x88].len,bl,AREA);
	}

	return 0;
}

/*==========================================
 * �ʒu�␳2
 *------------------------------------------
 */
static int clif_fixpos2_sub(struct block_list *bl, va_list ap)
{
	struct map_session_data *sd;
	struct block_list *src_bl = va_arg(ap, struct block_list*);
	int len  = va_arg(ap, int);
	unsigned char *buf = va_arg(ap, unsigned char*);

	nullpo_retr(0, bl);
	nullpo_retr(0, sd = (struct map_session_data *)bl);

	if( src_bl->id != sd->bl.id ) { // �����͏��O
		memcpy( WFIFOP(sd->fd, 0), buf, len);
		WFIFOSET( sd->fd, len );
	}

	return 0;
}

int clif_fixpos2(struct block_list *bl, int x[4], int y[4])
{
	unsigned char buf[128];

	nullpo_retr(0, bl);

	if(battle_config.clif_fixpos_type)
	{
		int len;

		// self position is changed
		// ���L�����̐�����΂��p�P���M�i���͎ҕ�W�j
		// ����ς�JT�̃G�t�F�N�g���c���Ă�����Ƀp�P���M���Ă�
		// �ړ����Ȃ��̂͑��̎d�l���ۂ��B�B�B
		// �@�� clif_blown() �𗘗p����悤�ɕύX

		if( bl->type == BL_PC ) {
			struct map_session_data *sd = (struct map_session_data*)bl;
			WFIFOW(sd->fd, 0) = 0x88;
			WFIFOL(sd->fd, 2) = sd->bl.id;
			WFIFOW(sd->fd, 6) = sd->bl.x;
			WFIFOW(sd->fd, 8) = sd->bl.y;
			WFIFOSET(sd->fd, packet_db[0x88].len);
		}

		// sent other players to notify position change
		if( bl->type == BL_PC) {
			struct map_session_data *sd = (struct map_session_data *)bl;
			if(sd->ud.walktimer != -1){
				len = clif_set007b(sd,buf);
			} else {
				len = clif_set0078(sd,buf);
			}
		} else if( bl->type == BL_MOB) {
			struct mob_data *md = (struct mob_data*)bl;
			if(md->ud.walktimer != -1){
				len = clif_mob007b(md,buf);
			} else {
				len = clif_mob0078(md,buf);
			}
		} else if( bl->type == BL_PET ) {
			struct pet_data *pd = (struct pet_data *)bl;
			if(pd->ud.walktimer != -1) {
				len = clif_pet007b(pd,buf);
			} else {
				len = clif_pet0078(pd,buf);
			}
		} else if( bl->type == BL_HOM ) {
			struct homun_data *hd = (struct homun_data *)bl;
			if(hd->ud.walktimer != -1) {
				len = clif_hom007b(hd,buf);
			} else {
				len = clif_hom0078(hd,buf);
			}
		} else if( bl->type == BL_MERC ) {
			struct merc_data *mcd = (struct merc_data *)bl;
			if(mcd->ud.walktimer != -1) {
				len = clif_merc007b(mcd,buf);
			} else {
				len = clif_merc0078(mcd,buf);
			}
		} else if( bl->type == BL_ELEM ) {
			struct elem_data *eld = (struct elem_data *)bl;
			if(eld->ud.walktimer != -1) {
				len = clif_elem007b(eld,buf);
			} else {
				len = clif_elem0078(eld,buf);
			}
		} else if( bl->type == BL_NPC ) {
			struct npc_data *nd = (struct npc_data *)bl;
			if(nd->ud.walktimer != -1) {
				len = clif_npc007b(nd,buf,NULL);
			} else {
				len = clif_npc0078(nd,buf,NULL);
			}
		} else {
			WBUFW(buf,0)=0x88;
			WBUFL(buf,2)=bl->id;
			WBUFW(buf,6)=bl->x;
			WBUFW(buf,8)=bl->y;
			len = packet_db[0x88].len;
		}
		map_foreachcommonarea(clif_fixpos2_sub, bl->m, x, y, BL_PC, bl, len, buf);
	}else{
		WBUFW(buf,0)=0x88;
		WBUFL(buf,2)=bl->id;
		WBUFW(buf,6)=bl->x;
		WBUFW(buf,8)=bl->y;
		clif_send(buf,packet_db[0x88].len,bl,AREA);
	}

	return 0;
}

/*==========================================
 * �ړ����̈ʒu�␳
 *------------------------------------------
 */
void clif_fixwalkpos(struct block_list *bl)
{
	unsigned char buf[16];

	nullpo_retv(bl);

	WBUFW(buf,0)=0x88;
	WBUFL(buf,2)=bl->id;
	WBUFW(buf,6)=bl->x;
	WBUFW(buf,8)=bl->y;
	clif_send(buf,packet_db[0x88].len,bl,AREA);

	return;
}

/*==========================================
 * ������΂�
 *------------------------------------------
 */
void clif_blown(struct block_list *bl, int x, int y)
{
	unsigned char buf[10];

	nullpo_retv(bl);

	WBUFW(buf, 0) = 0x1ff;
	WBUFL(buf, 2) = bl->id;
	WBUFW(buf, 6) = x;
	WBUFW(buf, 8) = y;
	clif_send(buf,packet_db[0x1ff].len,bl,AREA);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_npcbuysell(struct map_session_data* sd, int id)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xc4;
	WFIFOL(fd,2)=id;
	WFIFOSET(fd,packet_db[0xc4].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_buylist(struct map_session_data *sd, struct npc_data *nd)
{
	struct item_data *id;
	int fd,i,val;

	nullpo_retv(sd);
	nullpo_retv(nd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xc6;
#if PACKETVER < 20180704
	for(i=0;nd->u.shop_item[i].nameid > 0;i++){
		id = itemdb_search(nd->u.shop_item[i].nameid);
		val=nd->u.shop_item[i].value;
		WFIFOL(fd,4+i*11)=val;
		if ( !id->flag.value_notdc )
			val=pc_modifybuyvalue(sd,val);
		WFIFOL(fd,8+i*11)=val;
		WFIFOB(fd,12+i*11)=id->type;
		if(id->view_id > 0)
			WFIFOW(fd,13+i*11)=id->view_id;
		else
			WFIFOW(fd,13+i*11)=nd->u.shop_item[i].nameid;
	}
	WFIFOW(fd,2)=i*11+4;
#else
	for(i=0;nd->u.shop_item[i].nameid > 0;i++){
		id = itemdb_search(nd->u.shop_item[i].nameid);
		val=nd->u.shop_item[i].value;
		WFIFOL(fd,4+i*13)=val;
		if ( !id->flag.value_notdc )
			val=pc_modifybuyvalue(sd,val);
		WFIFOL(fd,8+i*13)=val;
		WFIFOB(fd,12+i*13)=id->type;
		if(id->view_id > 0)
			WFIFOL(fd,13+i*13)=id->view_id;
		else
			WFIFOL(fd,13+i*13)=nd->u.shop_item[i].nameid;
	}
	WFIFOW(fd,2)=i*13+4;
#endif
	WFIFOSET(fd,WFIFOW(fd,2));

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_selllist(struct map_session_data *sd)
{
	int fd,i,j,c=0,val;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xc7;
	for(i=0,j=0;i<MAX_INVENTORY && j<sd->inventory_num;i++) {
		if(sd->status.inventory[i].nameid > 0 && sd->inventory_data[i]) {
			j++;
			val=sd->inventory_data[i]->value_sell;
			if(val < 0)
				continue;
			WFIFOW(fd,4+c*10)=i+2;
			WFIFOL(fd,6+c*10)=val;
			if ( !sd->inventory_data[i]->flag.value_notoc )
				val=pc_modifysellvalue(sd,val);
			WFIFOL(fd,10+c*10)=val;
			c++;
		}
	}
	WFIFOW(fd,2)=c*10+4;
	WFIFOSET(fd,WFIFOW(fd,2));

	return;
}

/*==========================================
 * �X�y�V�����A�C�e���̔����X�g
 *------------------------------------------
 */
void clif_pointshop_list(struct map_session_data *sd, struct npc_data *nd)
{
	struct item_data *id;
	int fd,i,val;

	nullpo_retv(sd);
	nullpo_retv(nd);

	fd  = sd->fd;

#if PACKETVER < 20070711
	WFIFOW(fd,0) = 0x287;
	WFIFOL(fd,4) = sd->shop_point;
	for(i=0; nd->u.shop_item[i].nameid > 0; i++) {
		id  = itemdb_search(nd->u.shop_item[i].nameid);
		val = nd->u.shop_item[i].value;
		WFIFOL(fd,8+i*11) = val;
		WFIFOL(fd,12+i*11) = val;		// DC�͂Ȃ��̂ŉ��i�͓���
		WFIFOB(fd,16+i*11) = id->type;
		if(id->view_id > 0)
			WFIFOW(fd,17+i*11) = id->view_id;
		else
			WFIFOW(fd,17+i*11) = nd->u.shop_item[i].nameid;
	}
	WFIFOW(fd,2) = 8+i*11;
	WFIFOSET(fd,WFIFOW(fd,2));
#elif PACKETVER < 20180704
	WFIFOW(fd,0) = 0x287;
	WFIFOL(fd,4) = sd->shop_point;
	WFIFOL(fd,8) = 0;	// cash?
	for(i=0; nd->u.shop_item[i].nameid > 0; i++) {
		id  = itemdb_search(nd->u.shop_item[i].nameid);
		val = nd->u.shop_item[i].value;
		WFIFOL(fd,12+i*11) = val;
		WFIFOL(fd,16+i*11) = val;		// DC�͂Ȃ��̂ŉ��i�͓���
		WFIFOB(fd,20+i*11) = id->type;
		if(id->view_id > 0)
			WFIFOW(fd,21+i*11) = id->view_id;
		else
			WFIFOW(fd,21+i*11) = nd->u.shop_item[i].nameid;
	}
	WFIFOW(fd,2) = 12+i*11;
	WFIFOSET(fd,WFIFOW(fd,2));
#else
	WFIFOW(fd,0) = 0x287;
	WFIFOL(fd,4) = sd->shop_point;
	WFIFOL(fd,8) = 0;	// cash?
	for(i=0; nd->u.shop_item[i].nameid > 0; i++) {
		id  = itemdb_search(nd->u.shop_item[i].nameid);
		val = nd->u.shop_item[i].value;
		WFIFOL(fd,12+i*13) = val;
		WFIFOL(fd,16+i*13) = val;		// DC�͂Ȃ��̂ŉ��i�͓���
		WFIFOB(fd,20+i*13) = id->type;
		if(id->view_id > 0)
			WFIFOL(fd,21+i*13) = id->view_id;
		else
			WFIFOL(fd,21+i*13) = nd->u.shop_item[i].nameid;
	}
	WFIFOW(fd,2) = 12+i*13;
	WFIFOSET(fd,WFIFOW(fd,2));
#endif

	return;
}

/*==========================================
 * �}�[�P�b�g�A�C�e���̔����X�g
 *------------------------------------------
 */
void clif_market_list(struct map_session_data *sd, struct npc_data *nd)
{
#if PACKETVER >= 20131223
	struct item_data *id;
	int fd,i,val;

	nullpo_retv(sd);
	nullpo_retv(nd);

	fd  = sd->fd;

	WFIFOW(fd,0) = 0x9d5;
#if PACKETVER < 20180704
	for(i=0; nd->u.shop_item[i].nameid > 0; i++) {
		id  = itemdb_search(nd->u.shop_item[i].nameid);
		val = nd->u.shop_item[i].value;
		if(id->view_id > 0)
			WFIFOW(fd,4+i*13) = id->view_id;
		else
			WFIFOW(fd,4+i*13) = nd->u.shop_item[i].nameid;
		WFIFOB(fd, 6+i*13) = id->type;
		WFIFOL(fd, 7+i*13) = val;
		WFIFOL(fd,11+i*13) = nd->u.shop_item[i].qty;
		WFIFOW(fd,15+i*13) = id->weight;
	}
	WFIFOW(fd,2) = 4+i*13;
	WFIFOSET(fd,WFIFOW(fd,2));
#else
	for(i=0; nd->u.shop_item[i].nameid > 0; i++) {
		id  = itemdb_search(nd->u.shop_item[i].nameid);
		val = nd->u.shop_item[i].value;
		if(id->view_id > 0)
			WFIFOL(fd,4+i*15) = id->view_id;
		else
			WFIFOL(fd,4+i*15) = nd->u.shop_item[i].nameid;
		WFIFOB(fd, 8+i*15) = id->type;
		WFIFOL(fd, 9+i*15) = val;
		WFIFOL(fd,13+i*15) = nd->u.shop_item[i].qty;
		WFIFOW(fd,17+i*15) = id->weight;
	}
	WFIFOW(fd,2) = 4+i*15;
	WFIFOSET(fd,WFIFOW(fd,2));
#endif

#endif
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_scriptmes(struct map_session_data *sd, int npcid, const char *mes)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xb4;
	WFIFOW(fd,2)=(unsigned short)(strlen(mes)+9);
	WFIFOL(fd,4)=npcid;
	strncpy(WFIFOP(fd,8),mes,strlen(mes)+1);
	WFIFOSET(fd,WFIFOW(fd,2));

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_scriptmessize(struct map_session_data *sd, int npcid, int height, int width)
{
#if PACKETVER >= 20220504
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xba2;
	WFIFOL(fd,2)=height;
	WFIFOL(fd,6)=width;
	WFIFOSET(fd,packet_db[0xba2].len);
#endif

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_scriptmespos(struct map_session_data *sd, int npcid, int x, int y)
{
#if PACKETVER >= 20220504
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xba3;
	WFIFOL(fd,2)=x;
	WFIFOL(fd,6)=y;
	WFIFOSET(fd,packet_db[0xba3].len);
#endif

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_scriptmesalign(struct map_session_data *sd, int npcid, char align)
{
#if PACKETVER >= 20210203
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xba1;
	WFIFOB(fd,2)=align;
	WFIFOSET(fd,packet_db[0xba1].len);
#endif

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_scriptnext(struct map_session_data *sd, int npcid)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xb5;
	WFIFOL(fd,2)=npcid;
	WFIFOSET(fd,packet_db[0xb5].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_scriptclose(struct map_session_data *sd, int npcid)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xb6;
	WFIFOL(fd,2)=npcid;
	WFIFOSET(fd,packet_db[0xb6].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_scriptclear(struct map_session_data *sd, int npcid)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x8d6;
	WFIFOL(fd,2)=npcid;
	WFIFOSET(fd,packet_db[0x8d6].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_scriptmenu(struct map_session_data *sd, int npcid, const char *mes)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xb7;
	WFIFOW(fd,2)=(unsigned short)(strlen(mes)+9);
	WFIFOL(fd,4)=npcid;
	strncpy(WFIFOP(fd,8),mes,strlen(mes)+1);
	WFIFOSET(fd,WFIFOW(fd,2));

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_scriptinput(struct map_session_data *sd, int npcid)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x142;
	WFIFOL(fd,2)=npcid;
	WFIFOSET(fd,packet_db[0x142].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_scriptinputstr(struct map_session_data *sd, int npcid)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x1d4;
	WFIFOL(fd,2)=npcid;
	WFIFOSET(fd,packet_db[0x1d4].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_viewpoint(struct map_session_data *sd, int npc_id, int type, int x, int y, int id, int color)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x144;
	WFIFOL(fd,2)=npc_id;
	WFIFOL(fd,6)=type;
	WFIFOL(fd,10)=x;
	WFIFOL(fd,14)=y;
	WFIFOB(fd,18)=id;
	WFIFOL(fd,19)=color;
	WFIFOSET(fd,packet_db[0x144].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_cutin(struct map_session_data *sd, const char *image, int type)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x1b3;
	memcpy(WFIFOP(fd,2),image,64);
	WFIFOB(fd,66)=type;
	WFIFOSET(fd,packet_db[0x1b3].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_additem(struct map_session_data *sd, int n, int amount, unsigned char fail)
{
	int fd,j;

	nullpo_retv(sd);

	fd=sd->fd;

#if PACKETVER < 20070711
	if(fail) {
		memset(WFIFOP(fd,0), 0, packet_db[0xa0].len);

		WFIFOW(fd,0)=0xa0;
		WFIFOW(fd,2)=n+2;
		WFIFOW(fd,4)=amount;
		WFIFOB(fd,22)=fail;
	} else {
		if(n<0 || n>=MAX_INVENTORY || sd->status.inventory[n].nameid <=0 || sd->inventory_data[n] == NULL)
			return;

		WFIFOW(fd,0)=0xa0;
		WFIFOW(fd,2)=n+2;
		WFIFOW(fd,4)=amount;
		if(sd->inventory_data[n]->view_id > 0)
			WFIFOW(fd,6)=sd->inventory_data[n]->view_id;
		else
			WFIFOW(fd,6)=sd->status.inventory[n].nameid;
		WFIFOB(fd,8)=sd->status.inventory[n].identify;
		WFIFOB(fd,9)=sd->status.inventory[n].attribute;
		WFIFOB(fd,10)=sd->status.inventory[n].refine;
		if(itemdb_isspecial(sd->status.inventory[n].card[0])) {
			if(sd->inventory_data[n]->flag.pet_egg) {
				WFIFOW(fd,11) = 0;
				WFIFOW(fd,13) = 0;
				WFIFOW(fd,15) = 0;
			} else {
				WFIFOW(fd,11) = sd->status.inventory[n].card[0];
				WFIFOW(fd,13) = sd->status.inventory[n].card[1];
				WFIFOW(fd,15) = sd->status.inventory[n].card[2];
			}
			WFIFOW(fd,17) = sd->status.inventory[n].card[3];
		} else {
			if(sd->status.inventory[n].card[0] > 0 && (j=itemdb_viewid(sd->status.inventory[n].card[0])) > 0)
				WFIFOW(fd,11)=j;
			else
				WFIFOW(fd,11)=sd->status.inventory[n].card[0];
			if(sd->status.inventory[n].card[1] > 0 && (j=itemdb_viewid(sd->status.inventory[n].card[1])) > 0)
				WFIFOW(fd,13)=j;
			else
				WFIFOW(fd,13)=sd->status.inventory[n].card[1];
			if(sd->status.inventory[n].card[2] > 0 && (j=itemdb_viewid(sd->status.inventory[n].card[2])) > 0)
				WFIFOW(fd,15)=j;
			else
				WFIFOW(fd,15)=sd->status.inventory[n].card[2];
			if(sd->status.inventory[n].card[3] > 0 && (j=itemdb_viewid(sd->status.inventory[n].card[3])) > 0)
				WFIFOW(fd,17)=j;
			else
				WFIFOW(fd,17)=sd->status.inventory[n].card[3];
		}
		WFIFOW(fd,19)=pc_equippoint(sd,n);
		WFIFOB(fd,21)=sd->inventory_data[n]->type;
		WFIFOB(fd,22)=fail;
	}
	WFIFOSET(fd,packet_db[0xa0].len);
#elif PACKETVER < 20070904
	if(fail) {
		memset(WFIFOP(fd,0), 0, packet_db[0x29a].len);

		WFIFOW(fd,0)=0x29a;
		WFIFOW(fd,2)=n+2;
		WFIFOW(fd,4)=amount;
		WFIFOB(fd,22)=fail;
	} else {
		if(n<0 || n>=MAX_INVENTORY || sd->status.inventory[n].nameid <=0 || sd->inventory_data[n] == NULL)
			return;

		WFIFOW(fd,0)=0x29a;
		WFIFOW(fd,2)=n+2;
		WFIFOW(fd,4)=amount;
		if(sd->inventory_data[n]->view_id > 0)
			WFIFOW(fd,6)=sd->inventory_data[n]->view_id;
		else
			WFIFOW(fd,6)=sd->status.inventory[n].nameid;
		WFIFOB(fd,8)=sd->status.inventory[n].identify;
		WFIFOB(fd,9)=sd->status.inventory[n].attribute;
		WFIFOB(fd,10)=sd->status.inventory[n].refine;
		if(itemdb_isspecial(sd->status.inventory[n].card[0])) {
			if(sd->inventory_data[n]->flag.pet_egg) {
				WFIFOW(fd,11) = 0;
				WFIFOW(fd,13) = 0;
				WFIFOW(fd,15) = 0;
			} else {
				WFIFOW(fd,11) = sd->status.inventory[n].card[0];
				WFIFOW(fd,13) = sd->status.inventory[n].card[1];
				WFIFOW(fd,15) = sd->status.inventory[n].card[2];
			}
			WFIFOW(fd,17) = sd->status.inventory[n].card[3];
		} else {
			if(sd->status.inventory[n].card[0] > 0 && (j=itemdb_viewid(sd->status.inventory[n].card[0])) > 0)
				WFIFOW(fd,11)=j;
			else
				WFIFOW(fd,11)=sd->status.inventory[n].card[0];
			if(sd->status.inventory[n].card[1] > 0 && (j=itemdb_viewid(sd->status.inventory[n].card[1])) > 0)
				WFIFOW(fd,13)=j;
			else
				WFIFOW(fd,13)=sd->status.inventory[n].card[1];
			if(sd->status.inventory[n].card[2] > 0 && (j=itemdb_viewid(sd->status.inventory[n].card[2])) > 0)
				WFIFOW(fd,15)=j;
			else
				WFIFOW(fd,15)=sd->status.inventory[n].card[2];
			if(sd->status.inventory[n].card[3] > 0 && (j=itemdb_viewid(sd->status.inventory[n].card[3])) > 0)
				WFIFOW(fd,17)=j;
			else
				WFIFOW(fd,17)=sd->status.inventory[n].card[3];
		}
		WFIFOW(fd,19)=pc_equippoint(sd,n);
		WFIFOB(fd,21)=sd->inventory_data[n]->type;
		WFIFOB(fd,22)=fail;
		WFIFOL(fd,23)=sd->status.inventory[n].limit;
	}
	WFIFOSET(fd,packet_db[0x29a].len);
#elif PACKETVER < 20120925
	if(fail) {
		memset(WFIFOP(fd,0), 0, packet_db[0x2d4].len);

		WFIFOW(fd,0)=0x2d4;
		WFIFOW(fd,2)=n+2;
		WFIFOW(fd,4)=amount;
		WFIFOB(fd,22)=fail;
	} else {
		if(n<0 || n>=MAX_INVENTORY || sd->status.inventory[n].nameid <=0 || sd->inventory_data[n] == NULL)
			return;

		WFIFOW(fd,0)=0x2d4;
		WFIFOW(fd,2)=n+2;
		WFIFOW(fd,4)=amount;
		if(sd->inventory_data[n]->view_id > 0)
			WFIFOW(fd,6)=sd->inventory_data[n]->view_id;
		else
			WFIFOW(fd,6)=sd->status.inventory[n].nameid;
		WFIFOB(fd,8)=sd->status.inventory[n].identify;
		WFIFOB(fd,9)=sd->status.inventory[n].attribute;
		WFIFOB(fd,10)=sd->status.inventory[n].refine;
		if(itemdb_isspecial(sd->status.inventory[n].card[0])) {
			if(sd->inventory_data[n]->flag.pet_egg) {
				WFIFOW(fd,11) = 0;
				WFIFOW(fd,13) = 0;
				WFIFOW(fd,15) = 0;
			} else {
				WFIFOW(fd,11) = sd->status.inventory[n].card[0];
				WFIFOW(fd,13) = sd->status.inventory[n].card[1];
				WFIFOW(fd,15) = sd->status.inventory[n].card[2];
			}
			WFIFOW(fd,17) = sd->status.inventory[n].card[3];
		} else {
			if(sd->status.inventory[n].card[0] > 0 && (j=itemdb_viewid(sd->status.inventory[n].card[0])) > 0)
				WFIFOW(fd,11)=j;
			else
				WFIFOW(fd,11)=sd->status.inventory[n].card[0];
			if(sd->status.inventory[n].card[1] > 0 && (j=itemdb_viewid(sd->status.inventory[n].card[1])) > 0)
				WFIFOW(fd,13)=j;
			else
				WFIFOW(fd,13)=sd->status.inventory[n].card[1];
			if(sd->status.inventory[n].card[2] > 0 && (j=itemdb_viewid(sd->status.inventory[n].card[2])) > 0)
				WFIFOW(fd,15)=j;
			else
				WFIFOW(fd,15)=sd->status.inventory[n].card[2];
			if(sd->status.inventory[n].card[3] > 0 && (j=itemdb_viewid(sd->status.inventory[n].card[3])) > 0)
				WFIFOW(fd,17)=j;
			else
				WFIFOW(fd,17)=sd->status.inventory[n].card[3];
		}
		WFIFOW(fd,19)=pc_equippoint(sd,n);
		WFIFOB(fd,21)=sd->inventory_data[n]->type;
		WFIFOB(fd,22)=fail;
		WFIFOL(fd,23)=sd->status.inventory[n].limit;
		WFIFOW(fd,27)=0;
	}
	WFIFOSET(fd,packet_db[0x2d4].len);
#elif PACKETVER < 20150513
	if(fail) {
		memset(WFIFOP(fd,0), 0, packet_db[0x990].len);

		WFIFOW(fd,0)=0x990;
		WFIFOW(fd,2)=n+2;
		WFIFOW(fd,4)=amount;
		WFIFOB(fd,24)=fail;
	} else {
		if(n<0 || n>=MAX_INVENTORY || sd->status.inventory[n].nameid <=0 || sd->inventory_data[n] == NULL)
			return;

		WFIFOW(fd,0)=0x990;
		WFIFOW(fd,2)=n+2;
		WFIFOW(fd,4)=amount;
		if(sd->inventory_data[n]->view_id > 0)
			WFIFOW(fd,6)=sd->inventory_data[n]->view_id;
		else
			WFIFOW(fd,6)=sd->status.inventory[n].nameid;
		WFIFOB(fd,8)=sd->status.inventory[n].identify;
		WFIFOB(fd,9)=sd->status.inventory[n].attribute;
		WFIFOB(fd,10)=sd->status.inventory[n].refine;
		if(itemdb_isspecial(sd->status.inventory[n].card[0])) {
			if(sd->inventory_data[n]->flag.pet_egg) {
				WFIFOW(fd,11) = 0;
				WFIFOW(fd,13) = 0;
				WFIFOW(fd,15) = 0;
			} else {
				WFIFOW(fd,11) = sd->status.inventory[n].card[0];
				WFIFOW(fd,13) = sd->status.inventory[n].card[1];
				WFIFOW(fd,15) = sd->status.inventory[n].card[2];
			}
			WFIFOW(fd,17) = sd->status.inventory[n].card[3];
		} else {
			if(sd->status.inventory[n].card[0] > 0 && (j=itemdb_viewid(sd->status.inventory[n].card[0])) > 0)
				WFIFOW(fd,11)=j;
			else
				WFIFOW(fd,11)=sd->status.inventory[n].card[0];
			if(sd->status.inventory[n].card[1] > 0 && (j=itemdb_viewid(sd->status.inventory[n].card[1])) > 0)
				WFIFOW(fd,13)=j;
			else
				WFIFOW(fd,13)=sd->status.inventory[n].card[1];
			if(sd->status.inventory[n].card[2] > 0 && (j=itemdb_viewid(sd->status.inventory[n].card[2])) > 0)
				WFIFOW(fd,15)=j;
			else
				WFIFOW(fd,15)=sd->status.inventory[n].card[2];
			if(sd->status.inventory[n].card[3] > 0 && (j=itemdb_viewid(sd->status.inventory[n].card[3])) > 0)
				WFIFOW(fd,17)=j;
			else
				WFIFOW(fd,17)=sd->status.inventory[n].card[3];
		}
		WFIFOL(fd,19)=pc_equippoint(sd,n);
		WFIFOB(fd,23)=sd->inventory_data[n]->type;
		WFIFOB(fd,24)=fail;
		WFIFOL(fd,25)=sd->status.inventory[n].limit;
		WFIFOW(fd,29)=0;
	}
	WFIFOSET(fd,packet_db[0x990].len);
#elif PACKETVER < 20160921
	if(fail) {
		memset(WFIFOP(fd,0), 0, packet_db[0xa0c].len);

		WFIFOW(fd,0)=0xa0c;
		WFIFOW(fd,2)=n+2;
		WFIFOW(fd,4)=amount;
		WFIFOB(fd,24)=fail;
	} else {
		if(n<0 || n>=MAX_INVENTORY || sd->status.inventory[n].nameid <=0 || sd->inventory_data[n] == NULL)
			return;

		WFIFOW(fd,0)=0xa0c;
		WFIFOW(fd,2)=n+2;
		WFIFOW(fd,4)=amount;
		if(sd->inventory_data[n]->view_id > 0)
			WFIFOW(fd,6)=sd->inventory_data[n]->view_id;
		else
			WFIFOW(fd,6)=sd->status.inventory[n].nameid;
		WFIFOB(fd,8)=sd->status.inventory[n].identify;
		WFIFOB(fd,9)=sd->status.inventory[n].attribute;
		WFIFOB(fd,10)=sd->status.inventory[n].refine;
		if(itemdb_isspecial(sd->status.inventory[n].card[0])) {
			if(sd->inventory_data[n]->flag.pet_egg) {
				WFIFOW(fd,11) = 0;
				WFIFOW(fd,13) = 0;
				WFIFOW(fd,15) = 0;
			} else {
				WFIFOW(fd,11) = sd->status.inventory[n].card[0];
				WFIFOW(fd,13) = sd->status.inventory[n].card[1];
				WFIFOW(fd,15) = sd->status.inventory[n].card[2];
			}
			WFIFOW(fd,17) = sd->status.inventory[n].card[3];
		} else {
			if(sd->status.inventory[n].card[0] > 0 && (j=itemdb_viewid(sd->status.inventory[n].card[0])) > 0)
				WFIFOW(fd,11)=j;
			else
				WFIFOW(fd,11)=sd->status.inventory[n].card[0];
			if(sd->status.inventory[n].card[1] > 0 && (j=itemdb_viewid(sd->status.inventory[n].card[1])) > 0)
				WFIFOW(fd,13)=j;
			else
				WFIFOW(fd,13)=sd->status.inventory[n].card[1];
			if(sd->status.inventory[n].card[2] > 0 && (j=itemdb_viewid(sd->status.inventory[n].card[2])) > 0)
				WFIFOW(fd,15)=j;
			else
				WFIFOW(fd,15)=sd->status.inventory[n].card[2];
			if(sd->status.inventory[n].card[3] > 0 && (j=itemdb_viewid(sd->status.inventory[n].card[3])) > 0)
				WFIFOW(fd,17)=j;
			else
				WFIFOW(fd,17)=sd->status.inventory[n].card[3];
		}
		WFIFOL(fd,19)=pc_equippoint(sd,n);
		WFIFOB(fd,23)=sd->inventory_data[n]->type;
		WFIFOB(fd,24)=fail;
		WFIFOL(fd,25)=sd->status.inventory[n].limit;
		WFIFOW(fd,29)=0;
		WFIFOW(fd,31)=sd->status.inventory[n].opt[0].id;
		WFIFOW(fd,33)=sd->status.inventory[n].opt[0].val;
		WFIFOB(fd,35)=0;
		WFIFOW(fd,36)=sd->status.inventory[n].opt[1].id;
		WFIFOW(fd,38)=sd->status.inventory[n].opt[1].val;
		WFIFOB(fd,40)=0;
		WFIFOW(fd,41)=sd->status.inventory[n].opt[2].id;
		WFIFOW(fd,43)=sd->status.inventory[n].opt[2].val;
		WFIFOB(fd,45)=0;
		WFIFOW(fd,46)=sd->status.inventory[n].opt[3].id;
		WFIFOW(fd,48)=sd->status.inventory[n].opt[3].val;
		WFIFOB(fd,50)=0;
		WFIFOW(fd,51)=sd->status.inventory[n].opt[4].id;
		WFIFOW(fd,53)=sd->status.inventory[n].opt[4].val;
		WFIFOB(fd,55)=0;
	}
	WFIFOSET(fd,packet_db[0xa0c].len);
#elif PACKETVER < 20180704
	if(fail) {
		memset(WFIFOP(fd,0), 0, packet_db[0xa37].len);

		WFIFOW(fd,0)=0xa37;
		WFIFOW(fd,2)=n+2;
		WFIFOW(fd,4)=amount;
		WFIFOB(fd,24)=fail;
	} else {
		if(n<0 || n>=MAX_INVENTORY || sd->status.inventory[n].nameid <=0 || sd->inventory_data[n] == NULL)
			return;

		WFIFOW(fd,0)=0xa37;
		WFIFOW(fd,2)=n+2;
		WFIFOW(fd,4)=amount;
		if(sd->inventory_data[n]->view_id > 0)
			WFIFOW(fd,6)=sd->inventory_data[n]->view_id;
		else
			WFIFOW(fd,6)=sd->status.inventory[n].nameid;
		WFIFOB(fd,8)=sd->status.inventory[n].identify;
		WFIFOB(fd,9)=sd->status.inventory[n].attribute;
		WFIFOB(fd,10)=sd->status.inventory[n].refine;
		if(itemdb_isspecial(sd->status.inventory[n].card[0])) {
			if(sd->inventory_data[n]->flag.pet_egg) {
				WFIFOW(fd,11) = 0;
				WFIFOW(fd,13) = 0;
				WFIFOW(fd,15) = 0;
			} else {
				WFIFOW(fd,11) = sd->status.inventory[n].card[0];
				WFIFOW(fd,13) = sd->status.inventory[n].card[1];
				WFIFOW(fd,15) = sd->status.inventory[n].card[2];
			}
			WFIFOW(fd,17) = sd->status.inventory[n].card[3];
		} else {
			if(sd->status.inventory[n].card[0] > 0 && (j=itemdb_viewid(sd->status.inventory[n].card[0])) > 0)
				WFIFOW(fd,11)=j;
			else
				WFIFOW(fd,11)=sd->status.inventory[n].card[0];
			if(sd->status.inventory[n].card[1] > 0 && (j=itemdb_viewid(sd->status.inventory[n].card[1])) > 0)
				WFIFOW(fd,13)=j;
			else
				WFIFOW(fd,13)=sd->status.inventory[n].card[1];
			if(sd->status.inventory[n].card[2] > 0 && (j=itemdb_viewid(sd->status.inventory[n].card[2])) > 0)
				WFIFOW(fd,15)=j;
			else
				WFIFOW(fd,15)=sd->status.inventory[n].card[2];
			if(sd->status.inventory[n].card[3] > 0 && (j=itemdb_viewid(sd->status.inventory[n].card[3])) > 0)
				WFIFOW(fd,17)=j;
			else
				WFIFOW(fd,17)=sd->status.inventory[n].card[3];
		}
		WFIFOL(fd,19)=pc_equippoint(sd,n);
		WFIFOB(fd,23)=sd->inventory_data[n]->type;
		WFIFOB(fd,24)=fail;
		WFIFOL(fd,25)=sd->status.inventory[n].limit;
		WFIFOW(fd,29)=0;
		WFIFOW(fd,31)=sd->status.inventory[n].opt[0].id;
		WFIFOW(fd,33)=sd->status.inventory[n].opt[0].val;
		WFIFOB(fd,35)=0;
		WFIFOW(fd,36)=sd->status.inventory[n].opt[1].id;
		WFIFOW(fd,38)=sd->status.inventory[n].opt[1].val;
		WFIFOB(fd,40)=0;
		WFIFOW(fd,41)=sd->status.inventory[n].opt[2].id;
		WFIFOW(fd,43)=sd->status.inventory[n].opt[2].val;
		WFIFOB(fd,45)=0;
		WFIFOW(fd,46)=sd->status.inventory[n].opt[3].id;
		WFIFOW(fd,48)=sd->status.inventory[n].opt[3].val;
		WFIFOB(fd,50)=0;
		WFIFOW(fd,51)=sd->status.inventory[n].opt[4].id;
		WFIFOW(fd,53)=sd->status.inventory[n].opt[4].val;
		WFIFOB(fd,55)=0;
		WFIFOB(fd,56)=sd->status.inventory[n].private_;
		WFIFOW(fd,57)=sd->inventory_data[n]->look;
	}
	WFIFOSET(fd,packet_db[0xa37].len);
#else
	if(fail) {
		memset(WFIFOP(fd,0), 0, packet_db[0xa37].len);

		WFIFOW(fd,0)=0xa37;
		WFIFOW(fd,2)=n+2;
		WFIFOW(fd,4)=amount;
		WFIFOB(fd,34)=fail;
	} else {
		if(n<0 || n>=MAX_INVENTORY || sd->status.inventory[n].nameid <=0 || sd->inventory_data[n] == NULL)
			return;

		WFIFOW(fd,0)=0xa37;
		WFIFOW(fd,2)=n+2;
		WFIFOW(fd,4)=amount;
		if(sd->inventory_data[n]->view_id > 0)
			WFIFOL(fd,6)=sd->inventory_data[n]->view_id;
		else
			WFIFOL(fd,6)=sd->status.inventory[n].nameid;
		WFIFOB(fd,10)=sd->status.inventory[n].identify;
		WFIFOB(fd,11)=sd->status.inventory[n].attribute;
		WFIFOB(fd,12)=sd->status.inventory[n].refine;
		if(itemdb_isspecial(sd->status.inventory[n].card[0])) {
			if(sd->inventory_data[n]->flag.pet_egg) {
				WFIFOL(fd,13) = 0;
				WFIFOL(fd,17) = 0;
				WFIFOL(fd,21) = 0;
			} else {
				WFIFOL(fd,13) = sd->status.inventory[n].card[0];
				WFIFOL(fd,17) = sd->status.inventory[n].card[1];
				WFIFOL(fd,21) = sd->status.inventory[n].card[2];
			}
			WFIFOL(fd,25) = sd->status.inventory[n].card[3];
		} else {
			if(sd->status.inventory[n].card[0] > 0 && (j=itemdb_viewid(sd->status.inventory[n].card[0])) > 0)
				WFIFOL(fd,13)=j;
			else
				WFIFOL(fd,13)=sd->status.inventory[n].card[0];
			if(sd->status.inventory[n].card[1] > 0 && (j=itemdb_viewid(sd->status.inventory[n].card[1])) > 0)
				WFIFOL(fd,17)=j;
			else
				WFIFOL(fd,17)=sd->status.inventory[n].card[1];
			if(sd->status.inventory[n].card[2] > 0 && (j=itemdb_viewid(sd->status.inventory[n].card[2])) > 0)
				WFIFOL(fd,21)=j;
			else
				WFIFOL(fd,21)=sd->status.inventory[n].card[2];
			if(sd->status.inventory[n].card[3] > 0 && (j=itemdb_viewid(sd->status.inventory[n].card[3])) > 0)
				WFIFOL(fd,25)=j;
			else
				WFIFOL(fd,25)=sd->status.inventory[n].card[3];
		}
		WFIFOL(fd,29)=pc_equippoint(sd,n);
		WFIFOB(fd,33)=sd->inventory_data[n]->type;
		WFIFOB(fd,34)=fail;
		WFIFOL(fd,35)=sd->status.inventory[n].limit;
		WFIFOW(fd,39)=0;
		WFIFOW(fd,41)=sd->status.inventory[n].opt[0].id;
		WFIFOW(fd,43)=sd->status.inventory[n].opt[0].val;
		WFIFOB(fd,45)=0;
		WFIFOW(fd,46)=sd->status.inventory[n].opt[1].id;
		WFIFOW(fd,48)=sd->status.inventory[n].opt[1].val;
		WFIFOB(fd,50)=0;
		WFIFOW(fd,51)=sd->status.inventory[n].opt[2].id;
		WFIFOW(fd,53)=sd->status.inventory[n].opt[2].val;
		WFIFOB(fd,55)=0;
		WFIFOW(fd,56)=sd->status.inventory[n].opt[3].id;
		WFIFOW(fd,58)=sd->status.inventory[n].opt[3].val;
		WFIFOB(fd,60)=0;
		WFIFOW(fd,61)=sd->status.inventory[n].opt[4].id;
		WFIFOW(fd,63)=sd->status.inventory[n].opt[4].val;
		WFIFOB(fd,65)=0;
		WFIFOB(fd,66)=sd->status.inventory[n].private_;
		WFIFOW(fd,67)=sd->inventory_data[n]->look;
	}
	WFIFOSET(fd,packet_db[0xa37].len);
#endif

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_delitem(struct map_session_data *sd, short type, int n, int amount)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;

#if PACKETVER < 20091118
	WFIFOW(fd,0)=0xaf;
	WFIFOW(fd,2)=n+2;
	WFIFOW(fd,4)=amount;
	WFIFOSET(fd,packet_db[0xaf].len);
#else
	WFIFOW(fd,0)=0x7fa;
	WFIFOW(fd,2)=type;
	WFIFOW(fd,4)=n+2;
	WFIFOW(fd,6)=amount;
	WFIFOSET(fd,packet_db[0x7fa].len);
#endif

	return;
}

/*==========================================
 * �A�C�e���̎��Ԑ؂�폜
 *------------------------------------------
 */
void clif_delitem_timeout(struct map_session_data *sd, int n, int itemid)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
#if PACKETVER < 20180704
	WFIFOW(fd,0)=0x299;
	WFIFOW(fd,2)=n+2;
	WFIFOW(fd,4)=itemid;
	WFIFOSET(fd,packet_db[0x299].len);
#else
	WFIFOW(fd,0)=0x299;
	WFIFOW(fd,2)=n+2;
	WFIFOL(fd,4)=itemid;
	WFIFOSET(fd,packet_db[0x299].len);
#endif

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_itemlist(struct map_session_data *sd)
{
	int i,j,n=0,fd,arrow=-1;

	nullpo_retv(sd);

	fd=sd->fd;

#if PACKETVER < 5
	WFIFOW(fd,0)=0xa3;
	for(i=0,j=0;i<MAX_INVENTORY && j<sd->inventory_num;i++){
		if(sd->status.inventory[i].nameid <=0 || sd->inventory_data[i] == NULL)
			continue;
		j++;
		if(itemdb_isequip2(sd->inventory_data[i]))
			continue;
		WFIFOW(fd,n*10+4)=i+2;
		if(sd->inventory_data[i]->view_id > 0)
			WFIFOW(fd,n*10+6)=sd->inventory_data[i]->view_id;
		else
			WFIFOW(fd,n*10+6)=sd->status.inventory[i].nameid;
		WFIFOB(fd,n*10+8)=sd->inventory_data[i]->type;
		WFIFOB(fd,n*10+9)=sd->status.inventory[i].identify;
		WFIFOW(fd,n*10+10)=sd->status.inventory[i].amount;
		if(sd->inventory_data[i]->equip == LOC_ARROW){
			WFIFOW(fd,n*10+12)=LOC_ARROW;
			if(sd->status.inventory[i].equip) arrow=i;	// ���łɖ���`�F�b�N
		}
		else
			WFIFOW(fd,n*10+12)=0;
		n++;
	}
	if(n){
		WFIFOW(fd,2)=4+n*10;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#elif PACKETVER < 20080102
	WFIFOW(fd,0)=0x1ee;
	for(i=0,j=0;i<MAX_INVENTORY && j<sd->inventory_num;i++){
		if(sd->status.inventory[i].nameid <=0 || sd->inventory_data[i] == NULL)
			continue;
		j++;
		if(itemdb_isequip2(sd->inventory_data[i]))
			continue;
		WFIFOW(fd,n*18+4)=i+2;
		if(sd->inventory_data[i]->view_id > 0)
			WFIFOW(fd,n*18+6)=sd->inventory_data[i]->view_id;
		else
			WFIFOW(fd,n*18+6)=sd->status.inventory[i].nameid;
		WFIFOB(fd,n*18+8)=sd->inventory_data[i]->type;
		WFIFOB(fd,n*18+9)=sd->status.inventory[i].identify;
		WFIFOW(fd,n*18+10)=sd->status.inventory[i].amount;
		if(sd->inventory_data[i]->equip == LOC_ARROW){
			WFIFOW(fd,n*18+12)=LOC_ARROW;
			if(sd->status.inventory[i].equip) arrow=i;	// ���łɖ���`�F�b�N
		}
		else
			WFIFOW(fd,n*18+12)=0;
		WFIFOW(fd,n*18+14)=sd->status.inventory[i].card[0];
		WFIFOW(fd,n*18+16)=sd->status.inventory[i].card[1];
		WFIFOW(fd,n*18+18)=sd->status.inventory[i].card[2];
		WFIFOW(fd,n*18+20)=sd->status.inventory[i].card[3];
		n++;
	}
	if(n){
		WFIFOW(fd,2)=4+n*18;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#elif PACKETVER < 20111025
	WFIFOW(fd,0)=0x2e8;
	for(i=0,j=0;i<MAX_INVENTORY && j<sd->inventory_num;i++){
		if(sd->status.inventory[i].nameid <=0 || sd->inventory_data[i] == NULL)
			continue;
		j++;
		if(itemdb_isequip2(sd->inventory_data[i]))
			continue;
		WFIFOW(fd,n*22+4)=i+2;
		if(sd->inventory_data[i]->view_id > 0)
			WFIFOW(fd,n*22+6)=sd->inventory_data[i]->view_id;
		else
			WFIFOW(fd,n*22+6)=sd->status.inventory[i].nameid;
		WFIFOB(fd,n*22+8)=sd->inventory_data[i]->type;
		WFIFOB(fd,n*22+9)=sd->status.inventory[i].identify;
		WFIFOW(fd,n*22+10)=sd->status.inventory[i].amount;
		if(sd->inventory_data[i]->equip == LOC_ARROW){
			WFIFOW(fd,n*22+12)=LOC_ARROW;
			if(sd->status.inventory[i].equip) arrow=i;	// ���łɖ���`�F�b�N
		}
		else
			WFIFOW(fd,n*22+12)=0;
		WFIFOW(fd,n*22+14)=sd->status.inventory[i].card[0];
		WFIFOW(fd,n*22+16)=sd->status.inventory[i].card[1];
		WFIFOW(fd,n*22+18)=sd->status.inventory[i].card[2];
		WFIFOW(fd,n*22+20)=sd->status.inventory[i].card[3];
		WFIFOL(fd,n*22+22)=sd->status.inventory[i].limit;
		n++;
	}
	if(n){
		WFIFOW(fd,2)=4+n*22;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#elif PACKETVER < 20120925
	WFIFOW(fd,0)=0x900;
	for(i=0,j=0;i<MAX_INVENTORY && j<sd->inventory_num;i++){
		if(sd->status.inventory[i].nameid <=0 || sd->inventory_data[i] == NULL)
			continue;
		j++;
		if(itemdb_isequip2(sd->inventory_data[i]))
			continue;
		WFIFOW(fd,n*22+4)=i+2;
		if(sd->inventory_data[i]->view_id > 0)
			WFIFOW(fd,n*22+6)=sd->inventory_data[i]->view_id;
		else
			WFIFOW(fd,n*22+6)=sd->status.inventory[i].nameid;
		WFIFOB(fd,n*22+8)=sd->inventory_data[i]->type;
		WFIFOW(fd,n*22+9)=sd->status.inventory[i].amount;
		if(sd->inventory_data[i]->equip == LOC_ARROW){
			WFIFOW(fd,n*22+11)=LOC_ARROW;
			if(sd->status.inventory[i].equip) arrow=i;	// ���łɖ���`�F�b�N
		}
		else
			WFIFOW(fd,n*22+11)=0;
		WFIFOW(fd,n*22+13)=sd->status.inventory[i].card[0];
		WFIFOW(fd,n*22+15)=sd->status.inventory[i].card[1];
		WFIFOW(fd,n*22+17)=sd->status.inventory[i].card[2];
		WFIFOW(fd,n*22+19)=sd->status.inventory[i].card[3];
		WFIFOL(fd,n*22+21)=sd->status.inventory[i].limit;
		WFIFOB(fd,n*22+25)=sd->status.inventory[i].identify+(sd->status.inventory[i].private_?2:0);
		n++;
	}
	if(n){
		WFIFOW(fd,2)=4+n*22;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#elif PACKETVER < 20180704
	WFIFOW(fd,0)=0x991;
	for(i=0,j=0;i<MAX_INVENTORY && j<sd->inventory_num;i++){
		if(sd->status.inventory[i].nameid <=0 || sd->inventory_data[i] == NULL)
			continue;
		j++;
		if(itemdb_isequip2(sd->inventory_data[i]))
			continue;
		WFIFOW(fd,n*24+4)=i+2;
		if(sd->inventory_data[i]->view_id > 0)
			WFIFOW(fd,n*24+6)=sd->inventory_data[i]->view_id;
		else
			WFIFOW(fd,n*24+6)=sd->status.inventory[i].nameid;
		WFIFOB(fd,n*24+8)=sd->inventory_data[i]->type;
		WFIFOW(fd,n*24+9)=sd->status.inventory[i].amount;
		if(sd->inventory_data[i]->equip == LOC_ARROW){
			WFIFOL(fd,n*24+11)=LOC_ARROW;
			if(sd->status.inventory[i].equip) arrow=i;	// ���łɖ���`�F�b�N
		}
		else
			WFIFOL(fd,n*24+11)=0;
		WFIFOW(fd,n*24+15)=sd->status.inventory[i].card[0];
		WFIFOW(fd,n*24+17)=sd->status.inventory[i].card[1];
		WFIFOW(fd,n*24+19)=sd->status.inventory[i].card[2];
		WFIFOW(fd,n*24+21)=sd->status.inventory[i].card[3];
		WFIFOL(fd,n*24+23)=sd->status.inventory[i].limit;
		WFIFOB(fd,n*24+27)=sd->status.inventory[i].identify+(sd->status.inventory[i].private_?2:0);
		n++;
	}
	if(n){
		WFIFOW(fd,2)=4+n*24;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#elif PACKETVER < 20180912
	WFIFOW(fd,0)=0x991;
	for(i=0,j=0;i<MAX_INVENTORY && j<sd->inventory_num;i++){
		if(sd->status.inventory[i].nameid <=0 || sd->inventory_data[i] == NULL)
			continue;
		j++;
		if(itemdb_isequip2(sd->inventory_data[i]))
			continue;
		WFIFOW(fd,n*34+4)=i+2;
		if(sd->inventory_data[i]->view_id > 0)
			WFIFOL(fd,n*34+6)=sd->inventory_data[i]->view_id;
		else
			WFIFOL(fd,n*34+6)=sd->status.inventory[i].nameid;
		WFIFOB(fd,n*34+10)=sd->inventory_data[i]->type;
		WFIFOW(fd,n*34+11)=sd->status.inventory[i].amount;
		if(sd->inventory_data[i]->equip == LOC_ARROW){
			WFIFOL(fd,n*34+13)=LOC_ARROW;
			if(sd->status.inventory[i].equip) arrow=i;	// ���łɖ���`�F�b�N
		}
		else
			WFIFOL(fd,n*34+13)=0;
		WFIFOL(fd,n*34+17)=sd->status.inventory[i].card[0];
		WFIFOL(fd,n*34+21)=sd->status.inventory[i].card[1];
		WFIFOL(fd,n*34+25)=sd->status.inventory[i].card[2];
		WFIFOL(fd,n*34+29)=sd->status.inventory[i].card[3];
		WFIFOL(fd,n*34+33)=sd->status.inventory[i].limit;
		WFIFOB(fd,n*34+37)=sd->status.inventory[i].identify+(sd->status.inventory[i].private_?2:0);
		n++;
	}
	if(n){
		WFIFOW(fd,2)=4+n*34;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#else
	WFIFOW(fd,0)=0xb09;
	WFIFOB(fd,4)=0;		// inventory_id
	for(i=0,j=0;i<MAX_INVENTORY && j<sd->inventory_num;i++){
		if(sd->status.inventory[i].nameid <=0 || sd->inventory_data[i] == NULL)
			continue;
		j++;
		if(itemdb_isequip2(sd->inventory_data[i]))
			continue;
		WFIFOW(fd,n*34+5)=i+2;
		if(sd->inventory_data[i]->view_id > 0)
			WFIFOL(fd,n*34+7)=sd->inventory_data[i]->view_id;
		else
			WFIFOL(fd,n*34+7)=sd->status.inventory[i].nameid;
		WFIFOB(fd,n*34+11)=sd->inventory_data[i]->type;
		WFIFOW(fd,n*34+12)=sd->status.inventory[i].amount;
		if(sd->inventory_data[i]->equip == LOC_ARROW){
			WFIFOL(fd,n*34+14)=LOC_ARROW;
			if(sd->status.inventory[i].equip) arrow=i;	// ���łɖ���`�F�b�N
		}
		else
			WFIFOL(fd,n*34+14)=0;
		WFIFOL(fd,n*34+18)=sd->status.inventory[i].card[0];
		WFIFOL(fd,n*34+22)=sd->status.inventory[i].card[1];
		WFIFOL(fd,n*34+26)=sd->status.inventory[i].card[2];
		WFIFOL(fd,n*34+30)=sd->status.inventory[i].card[3];
		WFIFOL(fd,n*34+34)=sd->status.inventory[i].limit;
		WFIFOB(fd,n*34+38)=sd->status.inventory[i].identify+(sd->status.inventory[i].private_?2:0);
		n++;
	}
	if(n){
		WFIFOW(fd,2)=5+n*34;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#endif
	if(arrow >= 0)
		clif_arrowequip(sd,arrow);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_equiplist(struct map_session_data *sd)
{
	int i,j,k,n=0,fd;

	nullpo_retv(sd);

	fd=sd->fd;

#if PACKETVER < 20070711
	WFIFOW(fd,0)=0xa4;
	for(i=0,k=0;i<MAX_INVENTORY && k<sd->inventory_num;i++){
		if(sd->status.inventory[i].nameid<=0 || sd->inventory_data[i] == NULL)
			continue;
		k++;
		if(!itemdb_isequip2(sd->inventory_data[i]))
			continue;
		WFIFOW(fd,n*20+4)=i+2;
		if(sd->inventory_data[i]->view_id > 0)
			WFIFOW(fd,n*20+6)=sd->inventory_data[i]->view_id;
		else
			WFIFOW(fd,n*20+6)=sd->status.inventory[i].nameid;
		WFIFOB(fd,n*20+8)=sd->inventory_data[i]->type;
		WFIFOB(fd,n*20+9)=sd->status.inventory[i].identify;
		WFIFOW(fd,n*20+10)=pc_equippoint(sd,i);
		WFIFOW(fd,n*20+12)=sd->status.inventory[i].equip;
		WFIFOB(fd,n*20+14)=sd->status.inventory[i].attribute;
		WFIFOB(fd,n*20+15)=sd->status.inventory[i].refine;
		if(itemdb_isspecial(sd->status.inventory[i].card[0])) {
			if(sd->inventory_data[i]->flag.pet_egg) {
				WFIFOW(fd,n*20+16) = 0;
				WFIFOW(fd,n*20+18) = 0;
				WFIFOW(fd,n*20+20) = 0;
			} else {
				WFIFOW(fd,n*20+16) = sd->status.inventory[i].card[0];
				WFIFOW(fd,n*20+18) = sd->status.inventory[i].card[1];
				WFIFOW(fd,n*20+20) = sd->status.inventory[i].card[2];
			}
			WFIFOW(fd,n*20+22) = sd->status.inventory[i].card[3];
		} else {
			if(sd->status.inventory[i].card[0] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[0])) > 0)
				WFIFOW(fd,n*20+16)=j;
			else
				WFIFOW(fd,n*20+16)=sd->status.inventory[i].card[0];
			if(sd->status.inventory[i].card[1] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[1])) > 0)
				WFIFOW(fd,n*20+18)=j;
			else
				WFIFOW(fd,n*20+18)=sd->status.inventory[i].card[1];
			if(sd->status.inventory[i].card[2] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[2])) > 0)
				WFIFOW(fd,n*20+20)=j;
			else
				WFIFOW(fd,n*20+20)=sd->status.inventory[i].card[2];
			if(sd->status.inventory[i].card[3] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[3])) > 0)
				WFIFOW(fd,n*20+22)=j;
			else
				WFIFOW(fd,n*20+22)=sd->status.inventory[i].card[3];
		}
		n++;
	}
	if(n){
		WFIFOW(fd,2)=4+n*20;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#elif PACKETVER < 20070904
	WFIFOW(fd,0)=0x295;
	for(i=0,k=0;i<MAX_INVENTORY && k<sd->inventory_num;i++){
		if(sd->status.inventory[i].nameid<=0 || sd->inventory_data[i] == NULL)
			continue;
		k++;
		if(!itemdb_isequip2(sd->inventory_data[i]))
			continue;
		WFIFOW(fd,n*24+4)=i+2;
		if(sd->inventory_data[i]->view_id > 0)
			WFIFOW(fd,n*24+6)=sd->inventory_data[i]->view_id;
		else
			WFIFOW(fd,n*24+6)=sd->status.inventory[i].nameid;
		WFIFOB(fd,n*24+8)=sd->inventory_data[i]->type;
		WFIFOB(fd,n*24+9)=sd->status.inventory[i].identify;
		WFIFOW(fd,n*24+10)=pc_equippoint(sd,i);
		WFIFOW(fd,n*24+12)=sd->status.inventory[i].equip;
		WFIFOB(fd,n*24+14)=sd->status.inventory[i].attribute;
		WFIFOB(fd,n*24+15)=sd->status.inventory[i].refine;
		if(itemdb_isspecial(sd->status.inventory[i].card[0])) {
			if(sd->inventory_data[i]->flag.pet_egg) {
				WFIFOW(fd,n*24+16) = 0;
				WFIFOW(fd,n*24+18) = 0;
				WFIFOW(fd,n*24+20) = 0;
			} else {
				WFIFOW(fd,n*24+16) = sd->status.inventory[i].card[0];
				WFIFOW(fd,n*24+18) = sd->status.inventory[i].card[1];
				WFIFOW(fd,n*24+20) = sd->status.inventory[i].card[2];
			}
			WFIFOW(fd,n*24+22) = sd->status.inventory[i].card[3];
		} else {
			if(sd->status.inventory[i].card[0] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[0])) > 0)
				WFIFOW(fd,n*24+16)=j;
			else
				WFIFOW(fd,n*24+16)=sd->status.inventory[i].card[0];
			if(sd->status.inventory[i].card[1] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[1])) > 0)
				WFIFOW(fd,n*24+18)=j;
			else
				WFIFOW(fd,n*24+18)=sd->status.inventory[i].card[1];
			if(sd->status.inventory[i].card[2] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[2])) > 0)
				WFIFOW(fd,n*24+20)=j;
			else
				WFIFOW(fd,n*24+20)=sd->status.inventory[i].card[2];
			if(sd->status.inventory[i].card[3] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[3])) > 0)
				WFIFOW(fd,n*24+22)=j;
			else
				WFIFOW(fd,n*24+22)=sd->status.inventory[i].card[3];
		}
		WFIFOL(fd,n*24+24)=sd->status.inventory[i].limit;
		n++;
	}
	if(n){
		WFIFOW(fd,2)=4+n*24;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#elif PACKETVER < 20100629
	WFIFOW(fd,0)=0x2d0;
	for(i=0,k=0;i<MAX_INVENTORY && k<sd->inventory_num;i++){
		if(sd->status.inventory[i].nameid<=0 || sd->inventory_data[i] == NULL)
			continue;
		k++;
		if(!itemdb_isequip2(sd->inventory_data[i]))
			continue;
		WFIFOW(fd,n*26+4)=i+2;
		if(sd->inventory_data[i]->view_id > 0)
			WFIFOW(fd,n*26+6)=sd->inventory_data[i]->view_id;
		else
			WFIFOW(fd,n*26+6)=sd->status.inventory[i].nameid;
		WFIFOB(fd,n*26+8)=sd->inventory_data[i]->type;
		WFIFOB(fd,n*26+9)=sd->status.inventory[i].identify;
		WFIFOW(fd,n*26+10)=pc_equippoint(sd,i);
		WFIFOW(fd,n*26+12)=sd->status.inventory[i].equip;
		WFIFOB(fd,n*26+14)=sd->status.inventory[i].attribute;
		WFIFOB(fd,n*26+15)=sd->status.inventory[i].refine;
		if(itemdb_isspecial(sd->status.inventory[i].card[0])) {
			if(sd->inventory_data[i]->flag.pet_egg) {
				WFIFOW(fd,n*26+16) = 0;
				WFIFOW(fd,n*26+18) = 0;
				WFIFOW(fd,n*26+20) = 0;
			} else {
				WFIFOW(fd,n*26+16) = sd->status.inventory[i].card[0];
				WFIFOW(fd,n*26+18) = sd->status.inventory[i].card[1];
				WFIFOW(fd,n*26+20) = sd->status.inventory[i].card[2];
			}
			WFIFOW(fd,n*26+22) = sd->status.inventory[i].card[3];
		} else {
			if(sd->status.inventory[i].card[0] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[0])) > 0)
				WFIFOW(fd,n*26+16)=j;
			else
				WFIFOW(fd,n*26+16)=sd->status.inventory[i].card[0];
			if(sd->status.inventory[i].card[1] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[1])) > 0)
				WFIFOW(fd,n*26+18)=j;
			else
				WFIFOW(fd,n*26+18)=sd->status.inventory[i].card[1];
			if(sd->status.inventory[i].card[2] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[2])) > 0)
				WFIFOW(fd,n*26+20)=j;
			else
				WFIFOW(fd,n*26+20)=sd->status.inventory[i].card[2];
			if(sd->status.inventory[i].card[3] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[3])) > 0)
				WFIFOW(fd,n*26+22)=j;
			else
				WFIFOW(fd,n*26+22)=sd->status.inventory[i].card[3];
		}
		WFIFOL(fd,n*26+24)=sd->status.inventory[i].limit;
		WFIFOW(fd,n*26+28)=0;
		n++;
	}
	if(n){
		WFIFOW(fd,2)=4+n*26;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#elif PACKETVER < 20111025
	WFIFOW(fd,0)=0x2d0;
	for(i=0,k=0;i<MAX_INVENTORY && k<sd->inventory_num;i++){
		if(sd->status.inventory[i].nameid<=0 || sd->inventory_data[i] == NULL)
			continue;
		k++;
		if(!itemdb_isequip2(sd->inventory_data[i]))
			continue;
		WFIFOW(fd,n*28+4)=i+2;
		if(sd->inventory_data[i]->view_id > 0)
			WFIFOW(fd,n*28+6)=sd->inventory_data[i]->view_id;
		else
			WFIFOW(fd,n*28+6)=sd->status.inventory[i].nameid;
		WFIFOB(fd,n*28+8)=sd->inventory_data[i]->type;
		WFIFOB(fd,n*28+9)=sd->status.inventory[i].identify;
		WFIFOW(fd,n*28+10)=pc_equippoint(sd,i);
		WFIFOW(fd,n*28+12)=sd->status.inventory[i].equip;
		WFIFOB(fd,n*28+14)=sd->status.inventory[i].attribute;
		WFIFOB(fd,n*28+15)=sd->status.inventory[i].refine;
		if(itemdb_isspecial(sd->status.inventory[i].card[0])) {
			if(sd->inventory_data[i]->flag.pet_egg) {
				WFIFOW(fd,n*28+16) = 0;
				WFIFOW(fd,n*28+18) = 0;
				WFIFOW(fd,n*28+20) = 0;
			} else {
				WFIFOW(fd,n*28+16) = sd->status.inventory[i].card[0];
				WFIFOW(fd,n*28+18) = sd->status.inventory[i].card[1];
				WFIFOW(fd,n*28+20) = sd->status.inventory[i].card[2];
			}
			WFIFOW(fd,n*28+22) = sd->status.inventory[i].card[3];
		} else {
			if(sd->status.inventory[i].card[0] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[0])) > 0)
				WFIFOW(fd,n*28+16)=j;
			else
				WFIFOW(fd,n*28+16)=sd->status.inventory[i].card[0];
			if(sd->status.inventory[i].card[1] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[1])) > 0)
				WFIFOW(fd,n*28+18)=j;
			else
				WFIFOW(fd,n*28+18)=sd->status.inventory[i].card[1];
			if(sd->status.inventory[i].card[2] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[2])) > 0)
				WFIFOW(fd,n*28+20)=j;
			else
				WFIFOW(fd,n*28+20)=sd->status.inventory[i].card[2];
			if(sd->status.inventory[i].card[3] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[3])) > 0)
				WFIFOW(fd,n*28+22)=j;
			else
				WFIFOW(fd,n*28+22)=sd->status.inventory[i].card[3];
		}
		WFIFOL(fd,n*28+24)=sd->status.inventory[i].limit;
		WFIFOW(fd,n*28+28)=0;
		WFIFOW(fd,n*28+30)=sd->inventory_data[i]->look;
		n++;
	}
	if(n){
		WFIFOW(fd,2)=4+n*28;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#elif PACKETVER < 20120925
	WFIFOW(fd,0)=0x901;
	for(i=0,k=0;i<MAX_INVENTORY && k<sd->inventory_num;i++){
		if(sd->status.inventory[i].nameid<=0 || sd->inventory_data[i] == NULL)
			continue;
		k++;
		if(!itemdb_isequip2(sd->inventory_data[i]))
			continue;
		WFIFOW(fd,n*27+4)=i+2;
		if(sd->inventory_data[i]->view_id > 0)
			WFIFOW(fd,n*27+6)=sd->inventory_data[i]->view_id;
		else
			WFIFOW(fd,n*27+6)=sd->status.inventory[i].nameid;
		WFIFOB(fd,n*27+8)=sd->inventory_data[i]->type;
		WFIFOW(fd,n*27+9)=pc_equippoint(sd,i);
		WFIFOW(fd,n*27+11)=sd->status.inventory[i].equip;
		WFIFOB(fd,n*27+13)=sd->status.inventory[i].refine;
		if(itemdb_isspecial(sd->status.inventory[i].card[0])) {
			if(sd->inventory_data[i]->flag.pet_egg) {
				WFIFOW(fd,n*27+14) = 0;
				WFIFOW(fd,n*27+16) = 0;
				WFIFOW(fd,n*27+18) = 0;
			} else {
				WFIFOW(fd,n*27+14) = sd->status.inventory[i].card[0];
				WFIFOW(fd,n*27+16) = sd->status.inventory[i].card[1];
				WFIFOW(fd,n*27+18) = sd->status.inventory[i].card[2];
			}
			WFIFOW(fd,n*27+20) = sd->status.inventory[i].card[3];
		} else {
			if(sd->status.inventory[i].card[0] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[0])) > 0)
				WFIFOW(fd,n*27+14)=j;
			else
				WFIFOW(fd,n*27+14)=sd->status.inventory[i].card[0];
			if(sd->status.inventory[i].card[1] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[1])) > 0)
				WFIFOW(fd,n*27+16)=j;
			else
				WFIFOW(fd,n*27+16)=sd->status.inventory[i].card[1];
			if(sd->status.inventory[i].card[2] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[2])) > 0)
				WFIFOW(fd,n*27+18)=j;
			else
				WFIFOW(fd,n*27+18)=sd->status.inventory[i].card[2];
			if(sd->status.inventory[i].card[3] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[3])) > 0)
				WFIFOW(fd,n*27+20)=j;
			else
				WFIFOW(fd,n*27+20)=sd->status.inventory[i].card[3];
		}
		WFIFOL(fd,n*27+22)=sd->status.inventory[i].limit;
		WFIFOW(fd,n*27+26)=0;
		WFIFOW(fd,n*27+28)=sd->inventory_data[i]->look;
		WFIFOB(fd,n*27+30)=sd->status.inventory[i].identify+(sd->status.inventory[i].attribute?2:0)+(sd->status.inventory[i].private_?4:0);
		n++;
	}
	if(n){
		WFIFOW(fd,2)=4+n*27;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#elif PACKETVER < 20150513
	WFIFOW(fd,0)=0x992;
	for(i=0,k=0;i<MAX_INVENTORY && k<sd->inventory_num;i++){
		if(sd->status.inventory[i].nameid<=0 || sd->inventory_data[i] == NULL)
			continue;
		k++;
		if(!itemdb_isequip2(sd->inventory_data[i]))
			continue;
		WFIFOW(fd,n*31+4)=i+2;
		if(sd->inventory_data[i]->view_id > 0)
			WFIFOW(fd,n*31+6)=sd->inventory_data[i]->view_id;
		else
			WFIFOW(fd,n*31+6)=sd->status.inventory[i].nameid;
		WFIFOB(fd,n*31+8)=sd->inventory_data[i]->type;
		WFIFOL(fd,n*31+9)=pc_equippoint(sd,i);
		WFIFOL(fd,n*31+13)=sd->status.inventory[i].equip;
		WFIFOB(fd,n*31+17)=sd->status.inventory[i].refine;
		if(itemdb_isspecial(sd->status.inventory[i].card[0])) {
			if(sd->inventory_data[i]->flag.pet_egg) {
				WFIFOW(fd,n*31+18) = 0;
				WFIFOW(fd,n*31+20) = 0;
				WFIFOW(fd,n*31+22) = 0;
			} else {
				WFIFOW(fd,n*31+18) = sd->status.inventory[i].card[0];
				WFIFOW(fd,n*31+20) = sd->status.inventory[i].card[1];
				WFIFOW(fd,n*31+22) = sd->status.inventory[i].card[2];
			}
			WFIFOW(fd,n*31+24) = sd->status.inventory[i].card[3];
		} else {
			if(sd->status.inventory[i].card[0] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[0])) > 0)
				WFIFOW(fd,n*31+18)=j;
			else
				WFIFOW(fd,n*31+18)=sd->status.inventory[i].card[0];
			if(sd->status.inventory[i].card[1] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[1])) > 0)
				WFIFOW(fd,n*31+20)=j;
			else
				WFIFOW(fd,n*31+20)=sd->status.inventory[i].card[1];
			if(sd->status.inventory[i].card[2] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[2])) > 0)
				WFIFOW(fd,n*31+22)=j;
			else
				WFIFOW(fd,n*31+22)=sd->status.inventory[i].card[2];
			if(sd->status.inventory[i].card[3] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[3])) > 0)
				WFIFOW(fd,n*31+24)=j;
			else
				WFIFOW(fd,n*31+24)=sd->status.inventory[i].card[3];
		}
		WFIFOL(fd,n*31+26)=sd->status.inventory[i].limit;
		WFIFOW(fd,n*31+30)=0;
		WFIFOW(fd,n*31+32)=sd->inventory_data[i]->look;
		WFIFOB(fd,n*31+34)=sd->status.inventory[i].identify+(sd->status.inventory[i].attribute?2:0)+(sd->status.inventory[i].private_?4:0);
		n++;
	}
	if(n){
		WFIFOW(fd,2)=4+n*31;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#elif PACKETVER < 20180704
	WFIFOW(fd,0)=0xa0d;
	for(i=0,k=0;i<MAX_INVENTORY && k<sd->inventory_num;i++){
		if(sd->status.inventory[i].nameid<=0 || sd->inventory_data[i] == NULL)
			continue;
		k++;
		if(!itemdb_isequip2(sd->inventory_data[i]))
			continue;
		WFIFOW(fd,n*57+4)=i+2;
		if(sd->inventory_data[i]->view_id > 0)
			WFIFOW(fd,n*57+6)=sd->inventory_data[i]->view_id;
		else
			WFIFOW(fd,n*57+6)=sd->status.inventory[i].nameid;
		WFIFOB(fd,n*57+8)=sd->inventory_data[i]->type;
		WFIFOL(fd,n*57+9)=pc_equippoint(sd,i);
		WFIFOL(fd,n*57+13)=sd->status.inventory[i].equip;
		WFIFOB(fd,n*57+17)=sd->status.inventory[i].refine;
		if(itemdb_isspecial(sd->status.inventory[i].card[0])) {
			if(sd->inventory_data[i]->flag.pet_egg) {
				WFIFOW(fd,n*57+18) = 0;
				WFIFOW(fd,n*57+20) = 0;
				WFIFOW(fd,n*57+22) = 0;
			} else {
				WFIFOW(fd,n*57+18) = sd->status.inventory[i].card[0];
				WFIFOW(fd,n*57+20) = sd->status.inventory[i].card[1];
				WFIFOW(fd,n*57+22) = sd->status.inventory[i].card[2];
			}
			WFIFOW(fd,n*57+24) = sd->status.inventory[i].card[3];
		} else {
			if(sd->status.inventory[i].card[0] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[0])) > 0)
				WFIFOW(fd,n*57+18)=j;
			else
				WFIFOW(fd,n*57+18)=sd->status.inventory[i].card[0];
			if(sd->status.inventory[i].card[1] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[1])) > 0)
				WFIFOW(fd,n*57+20)=j;
			else
				WFIFOW(fd,n*57+20)=sd->status.inventory[i].card[1];
			if(sd->status.inventory[i].card[2] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[2])) > 0)
				WFIFOW(fd,n*57+22)=j;
			else
				WFIFOW(fd,n*57+22)=sd->status.inventory[i].card[2];
			if(sd->status.inventory[i].card[3] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[3])) > 0)
				WFIFOW(fd,n*57+24)=j;
			else
				WFIFOW(fd,n*57+24)=sd->status.inventory[i].card[3];
		}
		WFIFOL(fd,n*57+26)=sd->status.inventory[i].limit;
		WFIFOW(fd,n*57+30)=0;
		WFIFOW(fd,n*57+32)=sd->inventory_data[i]->look;
		WFIFOB(fd,n*57+34)=0;
		WFIFOW(fd,n*57+35)=sd->status.inventory[i].opt[0].id;
		WFIFOW(fd,n*57+37)=sd->status.inventory[i].opt[0].val;
		WFIFOB(fd,n*57+39)=0;
		WFIFOW(fd,n*57+40)=sd->status.inventory[i].opt[1].id;
		WFIFOW(fd,n*57+42)=sd->status.inventory[i].opt[1].val;
		WFIFOB(fd,n*57+44)=0;
		WFIFOW(fd,n*57+45)=sd->status.inventory[i].opt[2].id;
		WFIFOW(fd,n*57+47)=sd->status.inventory[i].opt[2].val;
		WFIFOB(fd,n*57+49)=0;
		WFIFOW(fd,n*57+50)=sd->status.inventory[i].opt[3].id;
		WFIFOW(fd,n*57+52)=sd->status.inventory[i].opt[3].val;
		WFIFOB(fd,n*57+54)=0;
		WFIFOW(fd,n*57+55)=sd->status.inventory[i].opt[4].id;
		WFIFOW(fd,n*57+57)=sd->status.inventory[i].opt[4].val;
		WFIFOB(fd,n*57+59)=0;
		WFIFOB(fd,n*57+60)=sd->status.inventory[i].identify+(sd->status.inventory[i].attribute?2:0)+(sd->status.inventory[i].private_?4:0);
		n++;
	}
	if(n){
		WFIFOW(fd,2)=4+n*57;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#elif PACKETVER < 20180912
	WFIFOW(fd,0)=0xa0d;
	for(i=0,k=0;i<MAX_INVENTORY && k<sd->inventory_num;i++){
		if(sd->status.inventory[i].nameid<=0 || sd->inventory_data[i] == NULL)
			continue;
		k++;
		if(!itemdb_isequip2(sd->inventory_data[i]))
			continue;
		WFIFOW(fd,n*67+4)=i+2;
		if(sd->inventory_data[i]->view_id > 0)
			WFIFOL(fd,n*67+6)=sd->inventory_data[i]->view_id;
		else
			WFIFOL(fd,n*67+6)=sd->status.inventory[i].nameid;
		WFIFOB(fd,n*67+10)=sd->inventory_data[i]->type;
		WFIFOL(fd,n*67+11)=pc_equippoint(sd,i);
		WFIFOL(fd,n*67+15)=sd->status.inventory[i].equip;
		WFIFOB(fd,n*67+19)=sd->status.inventory[i].refine;
		if(itemdb_isspecial(sd->status.inventory[i].card[0])) {
			if(sd->inventory_data[i]->flag.pet_egg) {
				WFIFOL(fd,n*67+20) = 0;
				WFIFOL(fd,n*67+24) = 0;
				WFIFOL(fd,n*67+28) = 0;
			} else {
				WFIFOL(fd,n*67+20) = sd->status.inventory[i].card[0];
				WFIFOL(fd,n*67+24) = sd->status.inventory[i].card[1];
				WFIFOL(fd,n*67+28) = sd->status.inventory[i].card[2];
			}
			WFIFOL(fd,n*67+32) = sd->status.inventory[i].card[3];
		} else {
			if(sd->status.inventory[i].card[0] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[0])) > 0)
				WFIFOL(fd,n*67+20)=j;
			else
				WFIFOL(fd,n*67+20)=sd->status.inventory[i].card[0];
			if(sd->status.inventory[i].card[1] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[1])) > 0)
				WFIFOL(fd,n*67+24)=j;
			else
				WFIFOL(fd,n*67+24)=sd->status.inventory[i].card[1];
			if(sd->status.inventory[i].card[2] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[2])) > 0)
				WFIFOL(fd,n*67+28)=j;
			else
				WFIFOL(fd,n*67+28)=sd->status.inventory[i].card[2];
			if(sd->status.inventory[i].card[3] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[3])) > 0)
				WFIFOL(fd,n*67+32)=j;
			else
				WFIFOL(fd,n*67+32)=sd->status.inventory[i].card[3];
		}
		WFIFOL(fd,n*67+36)=sd->status.inventory[i].limit;
		WFIFOW(fd,n*67+40)=0;
		WFIFOW(fd,n*67+42)=sd->inventory_data[i]->look;
		WFIFOB(fd,n*67+44)=0;
		WFIFOW(fd,n*67+45)=sd->status.inventory[i].opt[0].id;
		WFIFOW(fd,n*67+47)=sd->status.inventory[i].opt[0].val;
		WFIFOB(fd,n*67+49)=0;
		WFIFOW(fd,n*67+50)=sd->status.inventory[i].opt[1].id;
		WFIFOW(fd,n*67+52)=sd->status.inventory[i].opt[1].val;
		WFIFOB(fd,n*67+54)=0;
		WFIFOW(fd,n*67+55)=sd->status.inventory[i].opt[2].id;
		WFIFOW(fd,n*67+57)=sd->status.inventory[i].opt[2].val;
		WFIFOB(fd,n*67+59)=0;
		WFIFOW(fd,n*67+60)=sd->status.inventory[i].opt[3].id;
		WFIFOW(fd,n*67+62)=sd->status.inventory[i].opt[3].val;
		WFIFOB(fd,n*67+64)=0;
		WFIFOW(fd,n*67+65)=sd->status.inventory[i].opt[4].id;
		WFIFOW(fd,n*67+67)=sd->status.inventory[i].opt[4].val;
		WFIFOB(fd,n*67+69)=0;
		WFIFOB(fd,n*67+70)=sd->status.inventory[i].identify+(sd->status.inventory[i].attribute?2:0)+(sd->status.inventory[i].private_?4:0);
		n++;
	}
	if(n){
		WFIFOW(fd,2)=4+n*67;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#else
	WFIFOW(fd,0)=0xb0a;
	WFIFOB(fd,4)=0;		// inventory_id
	for(i=0,k=0;i<MAX_INVENTORY && k<sd->inventory_num;i++){
		if(sd->status.inventory[i].nameid<=0 || sd->inventory_data[i] == NULL)
			continue;
		k++;
		if(!itemdb_isequip2(sd->inventory_data[i]))
			continue;
		WFIFOW(fd,n*67+5)=i+2;
		if(sd->inventory_data[i]->view_id > 0)
			WFIFOL(fd,n*67+7)=sd->inventory_data[i]->view_id;
		else
			WFIFOL(fd,n*67+7)=sd->status.inventory[i].nameid;
		WFIFOB(fd,n*67+11)=sd->inventory_data[i]->type;
		WFIFOL(fd,n*67+12)=pc_equippoint(sd,i);
		WFIFOL(fd,n*67+16)=sd->status.inventory[i].equip;
		WFIFOB(fd,n*67+20)=sd->status.inventory[i].refine;
		if(itemdb_isspecial(sd->status.inventory[i].card[0])) {
			if(sd->inventory_data[i]->flag.pet_egg) {
				WFIFOL(fd,n*67+21) = 0;
				WFIFOL(fd,n*67+25) = 0;
				WFIFOL(fd,n*67+29) = 0;
			} else {
				WFIFOL(fd,n*67+21) = sd->status.inventory[i].card[0];
				WFIFOL(fd,n*67+25) = sd->status.inventory[i].card[1];
				WFIFOL(fd,n*67+29) = sd->status.inventory[i].card[2];
			}
			WFIFOL(fd,n*67+33) = sd->status.inventory[i].card[3];
		} else {
			if(sd->status.inventory[i].card[0] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[0])) > 0)
				WFIFOL(fd,n*67+21)=j;
			else
				WFIFOL(fd,n*67+21)=sd->status.inventory[i].card[0];
			if(sd->status.inventory[i].card[1] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[1])) > 0)
				WFIFOL(fd,n*67+25)=j;
			else
				WFIFOL(fd,n*67+25)=sd->status.inventory[i].card[1];
			if(sd->status.inventory[i].card[2] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[2])) > 0)
				WFIFOL(fd,n*67+29)=j;
			else
				WFIFOL(fd,n*67+29)=sd->status.inventory[i].card[2];
			if(sd->status.inventory[i].card[3] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[3])) > 0)
				WFIFOL(fd,n*67+33)=j;
			else
				WFIFOL(fd,n*67+33)=sd->status.inventory[i].card[3];
		}
		WFIFOL(fd,n*67+37)=sd->status.inventory[i].limit;
		WFIFOW(fd,n*67+41)=0;
		WFIFOW(fd,n*67+43)=sd->inventory_data[i]->look;
		WFIFOB(fd,n*67+45)=0;
		WFIFOW(fd,n*67+46)=sd->status.inventory[i].opt[0].id;
		WFIFOW(fd,n*67+48)=sd->status.inventory[i].opt[0].val;
		WFIFOB(fd,n*67+50)=0;
		WFIFOW(fd,n*67+51)=sd->status.inventory[i].opt[1].id;
		WFIFOW(fd,n*67+53)=sd->status.inventory[i].opt[1].val;
		WFIFOB(fd,n*67+55)=0;
		WFIFOW(fd,n*67+56)=sd->status.inventory[i].opt[2].id;
		WFIFOW(fd,n*67+58)=sd->status.inventory[i].opt[2].val;
		WFIFOB(fd,n*67+60)=0;
		WFIFOW(fd,n*67+61)=sd->status.inventory[i].opt[3].id;
		WFIFOW(fd,n*67+63)=sd->status.inventory[i].opt[3].val;
		WFIFOB(fd,n*67+65)=0;
		WFIFOW(fd,n*67+66)=sd->status.inventory[i].opt[4].id;
		WFIFOW(fd,n*67+68)=sd->status.inventory[i].opt[4].val;
		WFIFOB(fd,n*67+70)=0;
		WFIFOB(fd,n*67+71)=sd->status.inventory[i].identify+(sd->status.inventory[i].attribute?2:0)+(sd->status.inventory[i].private_?4:0);
		n++;
	}
	if(n){
		WFIFOW(fd,2)=5+n*67;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#endif

	return;
}

/*==========================================
 * �q�ɂ̏��Օi&���W�i���X�g
 *------------------------------------------
 */
static void clif_storageitemlist_sub(const int fd, struct item *item, int idx, int max, const char *name)
{
	struct item_data *id;
	int i, len = 4;

	nullpo_retv(item);

#if PACKETVER < 5
	WFIFOW(fd,0)=0xa5;
	for(i = idx; i < max; i++) {
		if(item[i].nameid <= 0)
			continue;
		nullpo_retv(id = itemdb_search(item[i].nameid));
		if(itemdb_isequip2(id))
			continue;
		if(len + 10 > SOCKET_EMPTY_SIZE)
			break;

		WFIFOW(fd,len)=i+1;
		if(id->view_id > 0)
			WFIFOW(fd,len+2)=id->view_id;
		else
			WFIFOW(fd,len+2)=item[i].nameid;
		WFIFOB(fd,len+4)=id->type;
		WFIFOB(fd,len+5)=item[i].identify;
		WFIFOW(fd,len+6)=item[i].amount;
		if(item[i].equip == LOC_ARROW)
			WFIFOW(fd,len+8)=LOC_ARROW;
		else
			WFIFOW(fd,len+8)=0;
		len += 10;
	}
#elif PACKETVER < 20080102
	WFIFOW(fd,0)=0x1f0;
	for(i = idx; i < max; i++) {
		if(item[i].nameid <= 0)
			continue;
		nullpo_retv(id = itemdb_search(item[i].nameid));
		if(itemdb_isequip2(id))
			continue;
		if(len + 18 > SOCKET_EMPTY_SIZE)
			break;

		WFIFOW(fd,len)=i+1;
		if(id->view_id > 0)
			WFIFOW(fd,len+2)=id->view_id;
		else
			WFIFOW(fd,len+2)=item[i].nameid;
		WFIFOB(fd,len+4)=id->type;
		WFIFOB(fd,len+5)=item[i].identify;
		WFIFOW(fd,len+6)=item[i].amount;
		if(item[i].equip == LOC_ARROW)
			WFIFOW(fd,len+8)=LOC_ARROW;
		else
			WFIFOW(fd,len+8)=0;
		WFIFOW(fd,len+10)=item[i].card[0];
		WFIFOW(fd,len+12)=item[i].card[1];
		WFIFOW(fd,len+14)=item[i].card[2];
		WFIFOW(fd,len+16)=item[i].card[3];
		len += 18;
	}
#elif PACKETVER < 20111025
	WFIFOW(fd,0)=0x2ea;
	for(i = idx; i < max; i++) {
		if(item[i].nameid <= 0)
			continue;
		nullpo_retv(id = itemdb_search(item[i].nameid));
		if(itemdb_isequip2(id))
			continue;
		if(len + 22 > SOCKET_EMPTY_SIZE)
			break;

		WFIFOW(fd,len)=i+1;
		if(id->view_id > 0)
			WFIFOW(fd,len+2)=id->view_id;
		else
			WFIFOW(fd,len+2)=item[i].nameid;
		WFIFOB(fd,len+4)=id->type;
		WFIFOB(fd,len+5)=item[i].identify;
		WFIFOW(fd,len+6)=item[i].amount;
		if(item[i].equip == LOC_ARROW)
			WFIFOW(fd,len+8)=LOC_ARROW;
		else
			WFIFOW(fd,len+8)=0;
		WFIFOW(fd,len+10)=item[i].card[0];
		WFIFOW(fd,len+12)=item[i].card[1];
		WFIFOW(fd,len+14)=item[i].card[2];
		WFIFOW(fd,len+16)=item[i].card[3];
		WFIFOL(fd,len+18)=item[i].limit;
		len += 22;
	}
#elif PACKETVER < 20120925
	WFIFOW(fd,0)=0x904;
	for(i = idx; i < max; i++) {
		if(item[i].nameid <= 0)
			continue;
		nullpo_retv(id = itemdb_search(item[i].nameid));
		if(itemdb_isequip2(id))
			continue;
		if(len + 22 > SOCKET_EMPTY_SIZE)
			break;

		WFIFOW(fd,len)=i+1;
		if(id->view_id > 0)
			WFIFOW(fd,len+2)=id->view_id;
		else
			WFIFOW(fd,len+2)=item[i].nameid;
		WFIFOB(fd,len+4)=id->type;
		WFIFOW(fd,len+5)=item[i].amount;
		if(item[i].equip == LOC_ARROW)
			WFIFOW(fd,len+7)=LOC_ARROW;
		else
			WFIFOW(fd,len+7)=0;
		WFIFOW(fd,len+9)=item[i].card[0];
		WFIFOW(fd,len+11)=item[i].card[1];
		WFIFOW(fd,len+13)=item[i].card[2];
		WFIFOW(fd,len+15)=item[i].card[3];
		WFIFOL(fd,len+17)=item[i].limit;
		WFIFOB(fd,len+21)=item[i].identify;
		len += 22;
	}
#elif PACKETVER < 20180704
	WFIFOW(fd,0)=0x995;
	strncpy(WFIFOP(fd,4), name, strlen(name)+1);
	len += 24;
	for(i = idx; i < max; i++) {
		if(item[i].nameid <= 0)
			continue;
		nullpo_retv(id = itemdb_search(item[i].nameid));
		if(itemdb_isequip2(id))
			continue;
		if(len + 24 > SOCKET_EMPTY_SIZE)
			break;

		WFIFOW(fd,len)=i+1;
		if(id->view_id > 0)
			WFIFOW(fd,len+2)=id->view_id;
		else
			WFIFOW(fd,len+2)=item[i].nameid;
		WFIFOB(fd,len+4)=id->type;
		WFIFOW(fd,len+5)=item[i].amount;
		if(item[i].equip == LOC_ARROW)
			WFIFOL(fd,len+7)=LOC_ARROW;
		else
			WFIFOL(fd,len+7)=0;
		WFIFOW(fd,len+11)=item[i].card[0];
		WFIFOW(fd,len+13)=item[i].card[1];
		WFIFOW(fd,len+15)=item[i].card[2];
		WFIFOW(fd,len+17)=item[i].card[3];
		WFIFOL(fd,len+19)=item[i].limit;
		WFIFOB(fd,len+23)=item[i].identify;
		len += 24;
	}
#elif PACKETVER < 20180829
	WFIFOW(fd,0)=0x995;
	strncpy(WFIFOP(fd,4), name, strlen(name)+1);
	len += 24;
	for(i = idx; i < max; i++) {
		if(item[i].nameid <= 0)
			continue;
		nullpo_retv(id = itemdb_search(item[i].nameid));
		if(itemdb_isequip2(id))
			continue;
		if(len + 34 > SOCKET_EMPTY_SIZE)
			break;

		WFIFOW(fd,len)=i+1;
		if(id->view_id > 0)
			WFIFOL(fd,len+2)=id->view_id;
		else
			WFIFOL(fd,len+2)=item[i].nameid;
		WFIFOB(fd,len+6)=id->type;
		WFIFOW(fd,len+7)=item[i].amount;
		if(item[i].equip == LOC_ARROW)
			WFIFOL(fd,len+9)=LOC_ARROW;
		else
			WFIFOL(fd,len+9)=0;
		WFIFOL(fd,len+13)=item[i].card[0];
		WFIFOL(fd,len+17)=item[i].card[1];
		WFIFOL(fd,len+21)=item[i].card[2];
		WFIFOL(fd,len+25)=item[i].card[3];
		WFIFOL(fd,len+29)=item[i].limit;
		WFIFOB(fd,len+33)=item[i].identify;
		len += 34;
	}
#else
	WFIFOW(fd,0)=0xb09;
	WFIFOB(fd,4)=2;
	len++;
	for(i = idx; i < max; i++) {
		if(item[i].nameid <= 0)
			continue;
		nullpo_retv(id = itemdb_search(item[i].nameid));
		if(itemdb_isequip2(id))
			continue;
		if(len + 34 > SOCKET_EMPTY_SIZE)
			break;

		WFIFOW(fd,len)=i+1;
		if(id->view_id > 0)
			WFIFOL(fd,len+2)=id->view_id;
		else
			WFIFOL(fd,len+2)=item[i].nameid;
		WFIFOB(fd,len+6)=id->type;
		WFIFOW(fd,len+7)=item[i].amount;
		if(item[i].equip == LOC_ARROW)
			WFIFOL(fd,len+9)=LOC_ARROW;
		else
			WFIFOL(fd,len+9)=0;
		WFIFOL(fd,len+13)=item[i].card[0];
		WFIFOL(fd,len+17)=item[i].card[1];
		WFIFOL(fd,len+21)=item[i].card[2];
		WFIFOL(fd,len+25)=item[i].card[3];
		WFIFOL(fd,len+29)=item[i].limit;
		WFIFOB(fd,len+33)=item[i].identify;
		len += 34;
	}
#endif
	if(len > 4) {
		WFIFOW(fd,2)=len;
		WFIFOSET(fd,len);
		if(i < max) {
			// ���ߕ��̓p�P�b�g����
			clif_storageitemlist_sub(fd, item, i, max, name);
		}
	}

	return;
}

/*==========================================
 * �q�ɂ̑������X�g
 *------------------------------------------
 */
static void clif_storageequiplist_sub(const int fd, struct item *item, int idx, int max, const char *name)
{
	struct item_data *id;
	int i, j, len = 4;

	nullpo_retv(item);

#if PACKETVER < 20070711
	WFIFOW(fd,0)=0xa6;
	for(i = idx; i < max; i++) {
		if(item[i].nameid <= 0)
			continue;
		nullpo_retv(id = itemdb_search(item[i].nameid));
		if(!itemdb_isequip2(id))
			continue;
		if(len + 20 > SOCKET_EMPTY_SIZE)
			break;

		WFIFOW(fd,len)=i+1;
		if(id->view_id > 0)
			WFIFOW(fd,len+2)=id->view_id;
		else
			WFIFOW(fd,len+2)=item[i].nameid;
		WFIFOB(fd,len+4)=id->type;
		WFIFOB(fd,len+5)=item[i].identify;
		WFIFOW(fd,len+6)=id->equip;
		WFIFOW(fd,len+8)=item[i].equip;
		WFIFOB(fd,len+10)=item[i].attribute;
		WFIFOB(fd,len+11)=item[i].refine;
		if(itemdb_isspecial(item[i].card[0])) {
			if(id->flag.pet_egg) {
				WFIFOW(fd,len+12) = 0;
				WFIFOW(fd,len+14) = 0;
				WFIFOW(fd,len+16) = 0;
			} else {
				WFIFOW(fd,len+12) = item[i].card[0];
				WFIFOW(fd,len+14) = item[i].card[1];
				WFIFOW(fd,len+16) = item[i].card[2];
			}
			WFIFOW(fd,len+18) = item[i].card[3];
		} else {
			if(item[i].card[0] > 0 && (j=itemdb_viewid(item[i].card[0])) > 0)
				WFIFOW(fd,len+12)=j;
			else
				WFIFOW(fd,len+12)=item[i].card[0];
			if(item[i].card[1] > 0 && (j=itemdb_viewid(item[i].card[1])) > 0)
				WFIFOW(fd,len+14)=j;
			else
				WFIFOW(fd,len+14)=item[i].card[1];
			if(item[i].card[2] > 0 && (j=itemdb_viewid(item[i].card[2])) > 0)
				WFIFOW(fd,len+16)=j;
			else
				WFIFOW(fd,len+16)=item[i].card[2];
			if(item[i].card[3] > 0 && (j=itemdb_viewid(item[i].card[3])) > 0)
				WFIFOW(fd,len+18)=j;
			else
				WFIFOW(fd,len+18)=item[i].card[3];
		}
		len += 20;
	}
#elif PACKETVER < 20070904
	WFIFOW(fd,0)=0x296;
	for(i = idx; i < max; i++) {
		if(item[i].nameid <= 0)
			continue;
		nullpo_retv(id = itemdb_search(item[i].nameid));
		if(!itemdb_isequip2(id))
			continue;
		if(len + 24 > SOCKET_EMPTY_SIZE)
			break;

		WFIFOW(fd,len)=i+1;
		if(id->view_id > 0)
			WFIFOW(fd,len+2)=id->view_id;
		else
			WFIFOW(fd,len+2)=item[i].nameid;
		WFIFOB(fd,len+4)=id->type;
		WFIFOB(fd,len+5)=item[i].identify;
		WFIFOW(fd,len+6)=id->equip;
		WFIFOW(fd,len+8)=item[i].equip;
		WFIFOB(fd,len+10)=item[i].attribute;
		WFIFOB(fd,len+11)=item[i].refine;
		if(itemdb_isspecial(item[i].card[0])) {
			if(id->flag.pet_egg) {
				WFIFOW(fd,len+12) = 0;
				WFIFOW(fd,len+14) = 0;
				WFIFOW(fd,len+16) = 0;
			} else {
				WFIFOW(fd,len+12) = item[i].card[0];
				WFIFOW(fd,len+14) = item[i].card[1];
				WFIFOW(fd,len+16) = item[i].card[2];
			}
			WFIFOW(fd,len+18) = item[i].card[3];
		} else {
			if(item[i].card[0] > 0 && (j=itemdb_viewid(item[i].card[0])) > 0)
				WFIFOW(fd,len+12)=j;
			else
				WFIFOW(fd,len+12)=item[i].card[0];
			if(item[i].card[1] > 0 && (j=itemdb_viewid(item[i].card[1])) > 0)
				WFIFOW(fd,len+14)=j;
			else
				WFIFOW(fd,len+14)=item[i].card[1];
			if(item[i].card[2] > 0 && (j=itemdb_viewid(item[i].card[2])) > 0)
				WFIFOW(fd,len+16)=j;
			else
				WFIFOW(fd,len+16)=item[i].card[2];
			if(item[i].card[3] > 0 && (j=itemdb_viewid(item[i].card[3])) > 0)
				WFIFOW(fd,len+18)=j;
			else
				WFIFOW(fd,len+18)=item[i].card[3];
		}
		WFIFOL(fd,len+20)=item[i].limit;
		len += 24;
	}
#elif PACKETVER < 20100414
	WFIFOW(fd,0)=0x2d1;
	for(i = idx; i < max; i++) {
		if(item[i].nameid <= 0)
			continue;
		nullpo_retv(id = itemdb_search(item[i].nameid));
		if(!itemdb_isequip2(id))
			continue;
		if(len + 26 > SOCKET_EMPTY_SIZE)
			break;

		WFIFOW(fd,len)=i+1;
		if(id->view_id > 0)
			WFIFOW(fd,len+2)=id->view_id;
		else
			WFIFOW(fd,len+2)=item[i].nameid;
		WFIFOB(fd,len+4)=id->type;
		WFIFOB(fd,len+5)=item[i].identify;
		WFIFOW(fd,len+6)=id->equip;
		WFIFOW(fd,len+8)=item[i].equip;
		WFIFOB(fd,len+10)=item[i].attribute;
		WFIFOB(fd,len+11)=item[i].refine;
		if(itemdb_isspecial(item[i].card[0])) {
			if(id->flag.pet_egg) {
				WFIFOW(fd,len+12) = 0;
				WFIFOW(fd,len+14) = 0;
				WFIFOW(fd,len+16) = 0;
			} else {
				WFIFOW(fd,len+12) = item[i].card[0];
				WFIFOW(fd,len+14) = item[i].card[1];
				WFIFOW(fd,len+16) = item[i].card[2];
			}
			WFIFOW(fd,len+18) = item[i].card[3];
		} else {
			if(item[i].card[0] > 0 && (j=itemdb_viewid(item[i].card[0])) > 0)
				WFIFOW(fd,len+12)=j;
			else
				WFIFOW(fd,len+12)=item[i].card[0];
			if(item[i].card[1] > 0 && (j=itemdb_viewid(item[i].card[1])) > 0)
				WFIFOW(fd,len+14)=j;
			else
				WFIFOW(fd,len+14)=item[i].card[1];
			if(item[i].card[2] > 0 && (j=itemdb_viewid(item[i].card[2])) > 0)
				WFIFOW(fd,len+16)=j;
			else
				WFIFOW(fd,len+16)=item[i].card[2];
			if(item[i].card[3] > 0 && (j=itemdb_viewid(item[i].card[3])) > 0)
				WFIFOW(fd,len+18)=j;
			else
				WFIFOW(fd,len+18)=item[i].card[3];
		}
		WFIFOL(fd,len+20)=item[i].limit;
		WFIFOW(fd,len+24)=0;
		len += 26;
	}
#elif PACKETVER < 20111025
	WFIFOW(fd,0)=0x2d1;
	for(i = idx; i < max; i++) {
		if(item[i].nameid <= 0)
			continue;
		nullpo_retv(id = itemdb_search(item[i].nameid));
		if(!itemdb_isequip2(id))
			continue;
		if(len + 28 > SOCKET_EMPTY_SIZE)
			break;

		WFIFOW(fd,len)=i+1;
		if(id->view_id > 0)
			WFIFOW(fd,len+2)=id->view_id;
		else
			WFIFOW(fd,len+2)=item[i].nameid;
		WFIFOB(fd,len+4)=id->type;
		WFIFOB(fd,len+5)=item[i].identify;
		WFIFOW(fd,len+6)=id->equip;
		WFIFOW(fd,len+8)=item[i].equip;
		WFIFOB(fd,len+10)=item[i].attribute;
		WFIFOB(fd,len+11)=item[i].refine;
		if(itemdb_isspecial(item[i].card[0])) {
			if(id->flag.pet_egg) {
				WFIFOW(fd,len+12) = 0;
				WFIFOW(fd,len+14) = 0;
				WFIFOW(fd,len+16) = 0;
			} else {
				WFIFOW(fd,len+12) = item[i].card[0];
				WFIFOW(fd,len+14) = item[i].card[1];
				WFIFOW(fd,len+16) = item[i].card[2];
			}
			WFIFOW(fd,len+18) = item[i].card[3];
		} else {
			if(item[i].card[0] > 0 && (j=itemdb_viewid(item[i].card[0])) > 0)
				WFIFOW(fd,len+12)=j;
			else
				WFIFOW(fd,len+12)=item[i].card[0];
			if(item[i].card[1] > 0 && (j=itemdb_viewid(item[i].card[1])) > 0)
				WFIFOW(fd,len+14)=j;
			else
				WFIFOW(fd,len+14)=item[i].card[1];
			if(item[i].card[2] > 0 && (j=itemdb_viewid(item[i].card[2])) > 0)
				WFIFOW(fd,len+16)=j;
			else
				WFIFOW(fd,len+16)=item[i].card[2];
			if(item[i].card[3] > 0 && (j=itemdb_viewid(item[i].card[3])) > 0)
				WFIFOW(fd,len+18)=j;
			else
				WFIFOW(fd,len+18)=item[i].card[3];
		}
		WFIFOL(fd,len+20)=item[i].limit;
		WFIFOW(fd,len+24)=0;
		WFIFOW(fd,len+26)=id->look;
		len += 28;
	}
#elif PACKETVER < 20120925
	WFIFOW(fd,0)=0x905;
	for(i = idx; i < max; i++) {
		if(item[i].nameid <= 0)
			continue;
		nullpo_retv(id = itemdb_search(item[i].nameid));
		if(!itemdb_isequip2(id))
			continue;
		if(len + 27 > SOCKET_EMPTY_SIZE)
			break;

		WFIFOW(fd,len)=i+1;
		if(id->view_id > 0)
			WFIFOW(fd,len+2)=id->view_id;
		else
			WFIFOW(fd,len+2)=item[i].nameid;
		WFIFOB(fd,len+4)=id->type;
		WFIFOW(fd,len+5)=id->equip;
		WFIFOW(fd,len+7)=item[i].equip;
		WFIFOB(fd,len+9)=item[i].refine;
		if(itemdb_isspecial(item[i].card[0])) {
			if(id->flag.pet_egg) {
				WFIFOW(fd,len+10) = 0;
				WFIFOW(fd,len+12) = 0;
				WFIFOW(fd,len+14) = 0;
			} else {
				WFIFOW(fd,len+10) = item[i].card[0];
				WFIFOW(fd,len+12) = item[i].card[1];
				WFIFOW(fd,len+14) = item[i].card[2];
			}
			WFIFOW(fd,len+16) = item[i].card[3];
		} else {
			if(item[i].card[0] > 0 && (j=itemdb_viewid(item[i].card[0])) > 0)
				WFIFOW(fd,len+10)=j;
			else
				WFIFOW(fd,len+10)=item[i].card[0];
			if(item[i].card[1] > 0 && (j=itemdb_viewid(item[i].card[1])) > 0)
				WFIFOW(fd,len+12)=j;
			else
				WFIFOW(fd,len+12)=item[i].card[1];
			if(item[i].card[2] > 0 && (j=itemdb_viewid(item[i].card[2])) > 0)
				WFIFOW(fd,len+14)=j;
			else
				WFIFOW(fd,len+14)=item[i].card[2];
			if(item[i].card[3] > 0 && (j=itemdb_viewid(item[i].card[3])) > 0)
				WFIFOW(fd,len+16)=j;
			else
				WFIFOW(fd,len+16)=item[i].card[3];
		}
		WFIFOL(fd,len+18)=item[i].limit;
		WFIFOW(fd,len+22)=0;
		WFIFOW(fd,len+24)=id->look;
		WFIFOB(fd,len+26)=item[i].identify+(item[i].attribute?2:0);
		len += 27;
	}
#elif PACKETVER < 20150513
	WFIFOW(fd,0)=0x996;
	strncpy(WFIFOP(fd,4), name, strlen(name)+1);
	len += 24;
	for(i = idx; i < max; i++) {
		if(item[i].nameid <= 0)
			continue;
		nullpo_retv(id = itemdb_search(item[i].nameid));
		if(!itemdb_isequip2(id))
			continue;
		if(len + 31 > SOCKET_EMPTY_SIZE)
			break;

		WFIFOW(fd,len)=i+1;
		if(id->view_id > 0)
			WFIFOW(fd,len+2)=id->view_id;
		else
			WFIFOW(fd,len+2)=item[i].nameid;
		WFIFOB(fd,len+4)=id->type;
		WFIFOL(fd,len+5)=id->equip;
		WFIFOL(fd,len+9)=item[i].equip;
		WFIFOB(fd,len+13)=item[i].refine;
		if(itemdb_isspecial(item[i].card[0])) {
			if(id->flag.pet_egg) {
				WFIFOW(fd,len+14) = 0;
				WFIFOW(fd,len+16) = 0;
				WFIFOW(fd,len+18) = 0;
			} else {
				WFIFOW(fd,len+14) = item[i].card[0];
				WFIFOW(fd,len+16) = item[i].card[1];
				WFIFOW(fd,len+18) = item[i].card[2];
			}
			WFIFOW(fd,len+20) = item[i].card[3];
		} else {
			if(item[i].card[0] > 0 && (j=itemdb_viewid(item[i].card[0])) > 0)
				WFIFOW(fd,len+14)=j;
			else
				WFIFOW(fd,len+14)=item[i].card[0];
			if(item[i].card[1] > 0 && (j=itemdb_viewid(item[i].card[1])) > 0)
				WFIFOW(fd,len+16)=j;
			else
				WFIFOW(fd,len+16)=item[i].card[1];
			if(item[i].card[2] > 0 && (j=itemdb_viewid(item[i].card[2])) > 0)
				WFIFOW(fd,len+18)=j;
			else
				WFIFOW(fd,len+18)=item[i].card[2];
			if(item[i].card[3] > 0 && (j=itemdb_viewid(item[i].card[3])) > 0)
				WFIFOW(fd,len+20)=j;
			else
				WFIFOW(fd,len+20)=item[i].card[3];
		}
		WFIFOL(fd,len+22)=item[i].limit;
		WFIFOW(fd,len+26)=0;
		WFIFOW(fd,len+28)=id->look;
		WFIFOB(fd,len+30)=item[i].identify+(item[i].attribute?2:0);
		len += 31;
	}
#elif PACKETVER < 20180704
	WFIFOW(fd,0)=0xa10;
	strncpy(WFIFOP(fd,4), name, strlen(name)+1);
	len += 24;
	for(i = idx; i < max; i++) {
		if(item[i].nameid <= 0)
			continue;
		nullpo_retv(id = itemdb_search(item[i].nameid));
		if(!itemdb_isequip2(id))
			continue;
		if(len + 57 > SOCKET_EMPTY_SIZE)
			break;

		WFIFOW(fd,len)=i+1;
		if(id->view_id > 0)
			WFIFOW(fd,len+2)=id->view_id;
		else
			WFIFOW(fd,len+2)=item[i].nameid;
		WFIFOB(fd,len+4)=id->type;
		WFIFOL(fd,len+5)=id->equip;
		WFIFOL(fd,len+9)=item[i].equip;
		WFIFOB(fd,len+13)=item[i].refine;
		if(itemdb_isspecial(item[i].card[0])) {
			if(id->flag.pet_egg) {
				WFIFOW(fd,len+14) = 0;
				WFIFOW(fd,len+16) = 0;
				WFIFOW(fd,len+18) = 0;
			} else {
				WFIFOW(fd,len+14) = item[i].card[0];
				WFIFOW(fd,len+16) = item[i].card[1];
				WFIFOW(fd,len+18) = item[i].card[2];
			}
			WFIFOW(fd,len+20) = item[i].card[3];
		} else {
			if(item[i].card[0] > 0 && (j=itemdb_viewid(item[i].card[0])) > 0)
				WFIFOW(fd,len+14)=j;
			else
				WFIFOW(fd,len+14)=item[i].card[0];
			if(item[i].card[1] > 0 && (j=itemdb_viewid(item[i].card[1])) > 0)
				WFIFOW(fd,len+16)=j;
			else
				WFIFOW(fd,len+16)=item[i].card[1];
			if(item[i].card[2] > 0 && (j=itemdb_viewid(item[i].card[2])) > 0)
				WFIFOW(fd,len+18)=j;
			else
				WFIFOW(fd,len+18)=item[i].card[2];
			if(item[i].card[3] > 0 && (j=itemdb_viewid(item[i].card[3])) > 0)
				WFIFOW(fd,len+20)=j;
			else
				WFIFOW(fd,len+20)=item[i].card[3];
		}
		WFIFOL(fd,len+22)=item[i].limit;
		WFIFOW(fd,len+26)=0;
		WFIFOW(fd,len+28)=id->look;
		WFIFOB(fd,len+30)=0;
		WFIFOW(fd,len+31)=item[i].opt[0].id;
		WFIFOW(fd,len+33)=item[i].opt[0].val;
		WFIFOB(fd,len+35)=0;
		WFIFOW(fd,len+36)=item[i].opt[1].id;
		WFIFOW(fd,len+38)=item[i].opt[1].val;
		WFIFOB(fd,len+40)=0;
		WFIFOW(fd,len+41)=item[i].opt[2].id;
		WFIFOW(fd,len+43)=item[i].opt[2].val;
		WFIFOB(fd,len+45)=0;
		WFIFOW(fd,len+46)=item[i].opt[3].id;
		WFIFOW(fd,len+48)=item[i].opt[3].val;
		WFIFOB(fd,len+50)=0;
		WFIFOW(fd,len+51)=item[i].opt[4].id;
		WFIFOW(fd,len+53)=item[i].opt[4].val;
		WFIFOB(fd,len+55)=0;
		WFIFOB(fd,len+56)=item[i].identify+(item[i].attribute?2:0);
		len += 57;
	}
#elif PACKETVER < 20180829
	WFIFOW(fd,0)=0xa10;
	strncpy(WFIFOP(fd,4), name, strlen(name)+1);
	len += 24;
	for(i = idx; i < max; i++) {
		if(item[i].nameid <= 0)
			continue;
		nullpo_retv(id = itemdb_search(item[i].nameid));
		if(!itemdb_isequip2(id))
			continue;
		if(len + 67 > SOCKET_EMPTY_SIZE)
			break;

		WFIFOW(fd,len)=i+1;
		if(id->view_id > 0)
			WFIFOL(fd,len+2)=id->view_id;
		else
			WFIFOL(fd,len+2)=item[i].nameid;
		WFIFOB(fd,len+6)=id->type;
		WFIFOL(fd,len+7)=id->equip;
		WFIFOL(fd,len+11)=item[i].equip;
		WFIFOB(fd,len+15)=item[i].refine;
		if(itemdb_isspecial(item[i].card[0])) {
			if(id->flag.pet_egg) {
				WFIFOL(fd,len+16) = 0;
				WFIFOL(fd,len+20) = 0;
				WFIFOL(fd,len+24) = 0;
			} else {
				WFIFOL(fd,len+16) = item[i].card[0];
				WFIFOL(fd,len+20) = item[i].card[1];
				WFIFOL(fd,len+24) = item[i].card[2];
			}
			WFIFOL(fd,len+28) = item[i].card[3];
		} else {
			if(item[i].card[0] > 0 && (j=itemdb_viewid(item[i].card[0])) > 0)
				WFIFOL(fd,len+16)=j;
			else
				WFIFOL(fd,len+16)=item[i].card[0];
			if(item[i].card[1] > 0 && (j=itemdb_viewid(item[i].card[1])) > 0)
				WFIFOL(fd,len+20)=j;
			else
				WFIFOL(fd,len+20)=item[i].card[1];
			if(item[i].card[2] > 0 && (j=itemdb_viewid(item[i].card[2])) > 0)
				WFIFOL(fd,len+24)=j;
			else
				WFIFOL(fd,len+24)=item[i].card[2];
			if(item[i].card[3] > 0 && (j=itemdb_viewid(item[i].card[3])) > 0)
				WFIFOL(fd,len+28)=j;
			else
				WFIFOL(fd,len+28)=item[i].card[3];
		}
		WFIFOL(fd,len+32)=item[i].limit;
		WFIFOW(fd,len+36)=0;
		WFIFOW(fd,len+38)=id->look;
		WFIFOB(fd,len+40)=0;
		WFIFOW(fd,len+41)=item[i].opt[0].id;
		WFIFOW(fd,len+43)=item[i].opt[0].val;
		WFIFOB(fd,len+45)=0;
		WFIFOW(fd,len+46)=item[i].opt[1].id;
		WFIFOW(fd,len+48)=item[i].opt[1].val;
		WFIFOB(fd,len+50)=0;
		WFIFOW(fd,len+51)=item[i].opt[2].id;
		WFIFOW(fd,len+53)=item[i].opt[2].val;
		WFIFOB(fd,len+55)=0;
		WFIFOW(fd,len+56)=item[i].opt[3].id;
		WFIFOW(fd,len+58)=item[i].opt[3].val;
		WFIFOB(fd,len+60)=0;
		WFIFOW(fd,len+61)=item[i].opt[4].id;
		WFIFOW(fd,len+63)=item[i].opt[4].val;
		WFIFOB(fd,len+65)=0;
		WFIFOB(fd,len+66)=item[i].identify+(item[i].attribute?2:0);
		len += 67;
	}
#else
	WFIFOW(fd,0)=0xb0a;
	WFIFOB(fd,4)=2;
	len++;
	for(i = idx; i < max; i++) {
		if(item[i].nameid <= 0)
			continue;
		nullpo_retv(id = itemdb_search(item[i].nameid));
		if(!itemdb_isequip2(id))
			continue;
		if(len + 67 > SOCKET_EMPTY_SIZE)
			break;

		WFIFOW(fd,len)=i+1;
		if(id->view_id > 0)
			WFIFOL(fd,len+2)=id->view_id;
		else
			WFIFOL(fd,len+2)=item[i].nameid;
		WFIFOB(fd,len+6)=id->type;
		WFIFOL(fd,len+7)=id->equip;
		WFIFOL(fd,len+11)=item[i].equip;
		WFIFOB(fd,len+15)=item[i].refine;
		if(itemdb_isspecial(item[i].card[0])) {
			if(id->flag.pet_egg) {
				WFIFOL(fd,len+16) = 0;
				WFIFOL(fd,len+20) = 0;
				WFIFOL(fd,len+24) = 0;
			} else {
				WFIFOL(fd,len+16) = item[i].card[0];
				WFIFOL(fd,len+20) = item[i].card[1];
				WFIFOL(fd,len+24) = item[i].card[2];
			}
			WFIFOL(fd,len+28) = item[i].card[3];
		} else {
			if(item[i].card[0] > 0 && (j=itemdb_viewid(item[i].card[0])) > 0)
				WFIFOL(fd,len+16)=j;
			else
				WFIFOL(fd,len+16)=item[i].card[0];
			if(item[i].card[1] > 0 && (j=itemdb_viewid(item[i].card[1])) > 0)
				WFIFOL(fd,len+20)=j;
			else
				WFIFOL(fd,len+20)=item[i].card[1];
			if(item[i].card[2] > 0 && (j=itemdb_viewid(item[i].card[2])) > 0)
				WFIFOL(fd,len+24)=j;
			else
				WFIFOL(fd,len+24)=item[i].card[2];
			if(item[i].card[3] > 0 && (j=itemdb_viewid(item[i].card[3])) > 0)
				WFIFOL(fd,len+28)=j;
			else
				WFIFOL(fd,len+28)=item[i].card[3];
		}
		WFIFOL(fd,len+32)=item[i].limit;
		WFIFOW(fd,len+36)=0;
		WFIFOW(fd,len+38)=id->look;
		WFIFOB(fd,len+40)=0;
		WFIFOW(fd,len+41)=item[i].opt[0].id;
		WFIFOW(fd,len+43)=item[i].opt[0].val;
		WFIFOB(fd,len+45)=0;
		WFIFOW(fd,len+46)=item[i].opt[1].id;
		WFIFOW(fd,len+48)=item[i].opt[1].val;
		WFIFOB(fd,len+50)=0;
		WFIFOW(fd,len+51)=item[i].opt[2].id;
		WFIFOW(fd,len+53)=item[i].opt[2].val;
		WFIFOB(fd,len+55)=0;
		WFIFOW(fd,len+56)=item[i].opt[3].id;
		WFIFOW(fd,len+58)=item[i].opt[3].val;
		WFIFOB(fd,len+60)=0;
		WFIFOW(fd,len+61)=item[i].opt[4].id;
		WFIFOW(fd,len+63)=item[i].opt[4].val;
		WFIFOB(fd,len+65)=0;
		WFIFOB(fd,len+66)=item[i].identify+(item[i].attribute?2:0);
		len += 67;
	}
#endif
	if(len > 4) {
		WFIFOW(fd,2)=len;
		WFIFOSET(fd,len);
		if(i < max) {
			// ���ߕ��̓p�P�b�g����
			clif_storageequiplist_sub(fd, item, i, max, name);
		}
	}

	return;
}

/*==========================================
 * �J�v������ɗa���Ă�����Օi&���W�i���X�g
 *------------------------------------------
 */
void clif_storageitemlist(struct map_session_data *sd, struct storage *stor)
{
	nullpo_retv(sd);
	nullpo_retv(stor);

	clif_storageitemlist_sub(sd->fd, stor->store_item, 0, MAX_STORAGE, msg_txt(208));

	return;
}

/*==========================================
 * �J�v������ɗa���Ă��鑕�����X�g
 *------------------------------------------
 */
void clif_storageequiplist(struct map_session_data *sd, struct storage *stor)
{
	nullpo_retv(sd);
	nullpo_retv(stor);

	clif_storageequiplist_sub(sd->fd, stor->store_item, 0, MAX_STORAGE, msg_txt(208));

	return;
}

/*==========================================
 * �M���h�q�ɂɗa���Ă�����Օi&���W�i���X�g
 *------------------------------------------
 */
void clif_guildstorageitemlist(struct map_session_data *sd, struct guild_storage *stor)
{
	nullpo_retv(sd);
	nullpo_retv(stor);

	clif_storageitemlist_sub(sd->fd, stor->store_item, 0, MAX_GUILD_STORAGE, msg_txt(209));

	return;
}

/*==========================================
 * �M���h�q�ɂɗa���Ă��鑕���i���X�g
 *------------------------------------------
 */
void clif_guildstorageequiplist(struct map_session_data *sd, struct guild_storage *stor)
{
	nullpo_retv(sd);
	nullpo_retv(stor);

	clif_storageequiplist_sub(sd->fd, stor->store_item, 0, MAX_GUILD_STORAGE, msg_txt(209));

	return;
}

/*==========================================
 * �A�C�e���f�[�^���t�J�n�ʒm
 *------------------------------------------
 */
void clif_inventoryStart(struct map_session_data *sd, int type, const char *name)
{
#if PACKETVER >= 20180829
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
#if PACKETVER < 20180912
	WFIFOW(fd,0)=0xb08;
	memcpy(WFIFOP(fd,2),name,24);
	WFIFOSET(fd,packet_db[0xb08].len);
#elif PACKETVER < 20180919
	WFIFOW(fd,0)=0xb08;
	WFIFOB(fd,2)=type;
	memcpy(WFIFOP(fd,3),name,24);
	WFIFOSET(fd,packet_db[0xb08].len);
#else
	size_t len;

	len = strlen(name)+5;
	if(len > 29)
		len = 29;
	WFIFOW(fd,0)=0xb08;
	WFIFOW(fd,2)=(unsigned short)len;
	WFIFOB(fd,4)=type;
	memcpy(WFIFOP(fd,5),name,strlen(name));
	WFIFOSET(fd,len);
#endif

#endif
	return;
}

/*==========================================
 * �A�C�e���f�[�^���t�I���ʒm
 *------------------------------------------
 */
void clif_inventoryEnd(struct map_session_data *sd, int type)
{
#if PACKETVER >= 20180829
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
#if PACKETVER < 20180912
	WFIFOW(fd,0)=0xb0b;
	WFIFOB(fd,2)=0;
#else
	WFIFOW(fd,0)=0xb0b;
	WFIFOB(fd,2)=type;
	WFIFOB(fd,3)=0;
#endif
	WFIFOSET(fd,packet_db[0xb0b].len);

#endif
	return;
}

/*==========================================
 * GM�֏ꏊ��HP�ʒm
 *------------------------------------------
 */
static void clif_hpmeter(struct map_session_data *sd)
{
	struct map_session_data *dstsd;
	unsigned char buf[16], buf2[16];
	int i, len;

	nullpo_retv(sd);

	WBUFW(buf,0)=0x107;
	WBUFL(buf,2)=sd->bl.id;
	WBUFW(buf,6)=sd->bl.x;
	WBUFW(buf,8)=sd->bl.y;

#if PACKETVER < 20100223
	WBUFW(buf2,0)=0x106;
	WBUFL(buf2,2)=sd->status.account_id;
	WBUFW(buf2,6)=(sd->status.max_hp > 0x7fff)? (short)((atn_bignumber)sd->status.hp * 0x7fff / sd->status.max_hp): sd->status.hp;
	WBUFW(buf2,8)=(sd->status.max_hp > 0x7fff)? 0x7fff: sd->status.max_hp;
	len = packet_db[0x106].len;
#else
	WBUFW(buf2,0)=0x80e;
	WBUFL(buf2,2)=sd->status.account_id;
	WBUFL(buf2,6)=sd->status.hp;
	WBUFL(buf2,10)=sd->status.max_hp;
	len = packet_db[0x80e].len;
#endif

	for(i=0;i<fd_max;i++){
		if(session[i] && (dstsd = (struct map_session_data *)session[i]->session_data) && dstsd->state.auth &&
		   dstsd->bl.m == sd->bl.m && pc_isGM(dstsd) && sd != dstsd){
			memcpy(WFIFOP(i,0),buf,packet_db[0x107].len);
			WFIFOSET(i,packet_db[0x107].len);
			memcpy(WFIFOP(i,0),buf2,len);
			WFIFOSET(i,len);
		}
	}

	return;
}

/*==========================================
 * �X�e�[�^�X�𑗂����
 * �\����p�����͂��̒��Ōv�Z���đ���
 *------------------------------------------
 */
void clif_updatestatus(struct map_session_data *sd, int type)
{
	int fd,len=8;

	nullpo_retv(sd);

	fd=sd->fd;

	WFIFOW(fd,0)=0xb0;
	WFIFOW(fd,2)=type;
	switch(type){
		// 00b0
	case SP_WEIGHT:
		pc_checkweighticon(sd);
		WFIFOW(fd,0)=0xb0;
		WFIFOW(fd,2)=type;
		WFIFOL(fd,4)=sd->weight;
		break;
	case SP_MAXWEIGHT:
		WFIFOL(fd,4)=sd->max_weight;
		break;
	case SP_SPEED:
		WFIFOL(fd,4)=sd->speed;
		break;
	case SP_BASELEVEL:
		WFIFOL(fd,4)=sd->status.base_level;
		break;
	case SP_JOBLEVEL:
		WFIFOL(fd,4)=sd->status.job_level;
		break;
	case SP_MANNER:
		WFIFOL(fd,4)=sd->status.manner;
		clif_changestatus(&sd->bl,SP_MANNER,sd->status.manner);
		break;
	case SP_STATUSPOINT:
		WFIFOL(fd,4)=sd->status.status_point;
		break;
	case SP_SKILLPOINT:
		WFIFOL(fd,4)=sd->status.skill_point;
		break;
	case SP_HIT:
		WFIFOL(fd,4)=sd->hit;
		break;
	case SP_FLEE1:
		WFIFOL(fd,4)=sd->flee;
		break;
	case SP_FLEE2:
		WFIFOL(fd,4)=sd->flee2/10;
		break;
	case SP_MAXHP:
		WFIFOL(fd,4)=sd->status.max_hp;
		break;
	case SP_MAXSP:
		WFIFOL(fd,4)=sd->status.max_sp;
		break;
	case SP_HP:
		WFIFOL(fd,4)=sd->status.hp;
		if(battle_config.disp_hpmeter)
			clif_hpmeter(sd);
		break;
	case SP_SP:
		WFIFOL(fd,4)=sd->status.sp;
		break;
	case SP_ASPD:
		WFIFOL(fd,4)=sd->amotion;
		break;
#ifdef PRE_RENEWAL
	case SP_ATK1:
		WFIFOL(fd,4)=sd->base_atk+sd->watk+sd->watk_;
		break;
	case SP_DEF1:
		WFIFOL(fd,4)=sd->def;
		break;
	case SP_MDEF1:
		WFIFOL(fd,4)=sd->mdef;
		break;
	case SP_ATK2:
		WFIFOL(fd,4)=sd->watk2+sd->watk_2;
		break;
	case SP_DEF2:
		WFIFOL(fd,4)=sd->def2;
		break;
	case SP_MDEF2:
		WFIFOL(fd,4)=sd->mdef2;
		break;
#else
	case SP_ATK1:
		WFIFOL(fd,4)=sd->base_atk;
		break;
	case SP_DEF1:
		WFIFOL(fd,4)=sd->def2;
		break;
	case SP_MDEF1:
		WFIFOL(fd,4)=sd->mdef2;
		break;
	case SP_ATK2:
		WFIFOL(fd,4)=sd->watk+sd->watk_+sd->watk2+sd->watk_2+sd->plus_atk;
		break;
	case SP_DEF2:
		WFIFOL(fd,4)=sd->def;
		break;
	case SP_MDEF2:
		WFIFOL(fd,4)=sd->mdef;
		break;
#endif
	case SP_CRITICAL:
		WFIFOL(fd,4)=sd->critical/10;
		break;
	case SP_MATK1:
#ifdef PRE_RENEWAL
		WFIFOL(fd,4)=sd->matk1;
#else
		WFIFOL(fd,4)=sd->matk1+sd->plus_matk;
#endif
		break;
	case SP_MATK2:
		WFIFOL(fd,4)=sd->matk2;
		break;
#if PACKETVER >= 20200916
	case SP_PATK:
		WFIFOL(fd,4)=sd->patk;
		break;
	case SP_SMATK:
		WFIFOL(fd,4)=sd->smatk;
		break;
	case SP_RES:
		WFIFOL(fd,4)=sd->res;
		break;
	case SP_MRES:
		WFIFOL(fd,4)=sd->mres;
		break;
	case SP_HPLUS:
		WFIFOL(fd,4)=sd->hplus;
		break;
	case SP_CRATE:
		WFIFOL(fd,4)=sd->crate;
		break;
	case SP_TSTATUSPOINT:
		WFIFOL(fd,4)=sd->status.tstatus_point;
		break;
	case SP_AP:
		WFIFOL(fd,4)=sd->status.ap;
		break;
	case SP_MAXAP:
		WFIFOL(fd,4)=sd->status.max_ap;
		break;
#else
	case SP_PATK:
	case SP_SMATK:
	case SP_RES:
	case SP_MRES:
	case SP_HPLUS:
	case SP_CRATE:
	case SP_TSTATUSPOINT:
	case SP_AP:
	case SP_MAXAP:
		return;
#endif

		// 00b1
	case SP_ZENY:
		WFIFOW(fd,0)=0xb1;
		WFIFOL(fd,4)=sd->status.zeny;
		break;
#if PACKETVER < 20170830
	case SP_BASEEXP:
		WFIFOW(fd,0)=0xb1;
		WFIFOL(fd,4)=(sd->status.base_exp > 0x7fffffff)? 0x7fffffff: (int)sd->status.base_exp;
		break;
	case SP_JOBEXP:
		WFIFOW(fd,0)=0xb1;
		WFIFOL(fd,4)=(sd->status.job_exp > 0x7fffffff)? 0x7fffffff: (int)sd->status.job_exp;
		break;
	case SP_NEXTBASEEXP:
		WFIFOW(fd,0)=0xb1;
		WFIFOL(fd,4)=(pc_nextbaseexp(sd) > 0x7fffffff)? 0x7fffffff: (int)pc_nextbaseexp(sd);
		break;
	case SP_NEXTJOBEXP:
		WFIFOW(fd,0)=0xb1;
		WFIFOL(fd,4)=(pc_nextjobexp(sd) > 0x7fffffff)? 0x7fffffff: (int)pc_nextjobexp(sd);
		break;
#else
	case SP_BASEEXP:
		WFIFOW(fd,0)=0xacb;
		WFIFOQ(fd,4)=sd->status.base_exp;
		len=12;
		break;
	case SP_JOBEXP:
		WFIFOW(fd,0)=0xacb;
		WFIFOQ(fd,4)=sd->status.job_exp;
		len=12;
		break;
	case SP_NEXTBASEEXP:
		WFIFOW(fd,0)=0xacb;
		WFIFOQ(fd,4)=pc_nextbaseexp(sd);
		len=12;
		break;
	case SP_NEXTJOBEXP:
		WFIFOW(fd,0)=0xacb;
		WFIFOQ(fd,4)=pc_nextjobexp(sd);
		len=12;
		break;
#endif

		// 00be
	case SP_USTR:
	case SP_UAGI:
	case SP_UVIT:
	case SP_UINT:
	case SP_UDEX:
	case SP_ULUK:
		WFIFOW(fd,0)=0xbe;
		WFIFOB(fd,4)=pc_need_status_point(sd,type-SP_USTR+SP_STR);
		len=5;
		break;
#if PACKETVER >= 20200916
	case SP_UPOW:
	case SP_USTA:
	case SP_UWIS:
	case SP_USPL:
	case SP_UCON:
	case SP_UCRT:
		WFIFOW(fd,0)=0xbe;
		WFIFOB(fd,4)=pc_need_tstatus_point(sd,type-SP_UPOW+SP_POW);
		len=5;
		break;
#else
	case SP_UPOW:
	case SP_USTA:
	case SP_UWIS:
	case SP_USPL:
	case SP_UCON:
	case SP_UCRT:
		return;
#endif

		// 013a
	case SP_ATTACKRANGE:
		WFIFOW(fd,0)=0x13a;
		WFIFOW(fd,2)=sd->range.attackrange;
		len=4;
		break;

		// 0141
	case SP_STR:
		WFIFOW(fd,0)=0x141;
		WFIFOL(fd,2)=type;
		WFIFOL(fd,6)=sd->status.str;
		WFIFOL(fd,10)=sd->paramb[0] + sd->parame[0];
		len=14;
		break;
	case SP_AGI:
		WFIFOW(fd,0)=0x141;
		WFIFOL(fd,2)=type;
		WFIFOL(fd,6)=sd->status.agi;
		WFIFOL(fd,10)=sd->paramb[1] + sd->parame[1];
		len=14;
		break;
	case SP_VIT:
		WFIFOW(fd,0)=0x141;
		WFIFOL(fd,2)=type;
		WFIFOL(fd,6)=sd->status.vit;
		WFIFOL(fd,10)=sd->paramb[2] + sd->parame[2];
		len=14;
		break;
	case SP_INT:
		WFIFOW(fd,0)=0x141;
		WFIFOL(fd,2)=type;
		WFIFOL(fd,6)=sd->status.int_;
		WFIFOL(fd,10)=sd->paramb[3] + sd->parame[3];
		len=14;
		break;
	case SP_DEX:
		WFIFOW(fd,0)=0x141;
		WFIFOL(fd,2)=type;
		WFIFOL(fd,6)=sd->status.dex;
		WFIFOL(fd,10)=sd->paramb[4] + sd->parame[4];
		len=14;
		break;
	case SP_LUK:
		WFIFOW(fd,0)=0x141;
		WFIFOL(fd,2)=type;
		WFIFOL(fd,6)=sd->status.luk;
		WFIFOL(fd,10)=sd->paramb[5] + sd->parame[5];
		len=14;
		break;
#if PACKETVER >= 20200916
	case SP_POW:
		WFIFOW(fd,0)=0x141;
		WFIFOL(fd,2)=type;
		WFIFOL(fd,6)=sd->status.pow;
		WFIFOL(fd,10)=sd->paramb[6] + sd->parame[6];
		len=14;
		break;
	case SP_STA:
		WFIFOW(fd,0)=0x141;
		WFIFOL(fd,2)=type;
		WFIFOL(fd,6)=sd->status.sta;
		WFIFOL(fd,10)=sd->paramb[7] + sd->parame[7];
		len=14;
		break;
	case SP_WIS:
		WFIFOW(fd,0)=0x141;
		WFIFOL(fd,2)=type;
		WFIFOL(fd,6)=sd->status.wis;
		WFIFOL(fd,10)=sd->paramb[8] + sd->parame[8];
		len=14;
		break;
	case SP_SPL:
		WFIFOW(fd,0)=0x141;
		WFIFOL(fd,2)=type;
		WFIFOL(fd,6)=sd->status.spl;
		WFIFOL(fd,10)=sd->paramb[9] + sd->parame[9];
		len=14;
		break;
	case SP_CON:
		WFIFOW(fd,0)=0x141;
		WFIFOL(fd,2)=type;
		WFIFOL(fd,6)=sd->status.con;
		WFIFOL(fd,10)=sd->paramb[10] + sd->parame[10];
		len=14;
		break;
	case SP_CRT:
		WFIFOW(fd,0)=0x141;
		WFIFOL(fd,2)=type;
		WFIFOL(fd,6)=sd->status.crt;
		WFIFOL(fd,10)=sd->paramb[11] + sd->parame[11];
		len=14;
		break;
#else
	case SP_POW:
	case SP_STA:
	case SP_WIS:
	case SP_SPL:
	case SP_CON:
	case SP_CRT:
		return;
#endif

		// 0121
	case SP_CARTINFO:
		WFIFOW(fd,0)=0x121;
		WFIFOW(fd,2)=sd->cart_num;
		WFIFOW(fd,4)=sd->cart_max_num;
		WFIFOL(fd,6)=sd->cart_weight;
		WFIFOL(fd,10)=sd->cart_max_weight;
		len=14;
		break;

	default:
		if(battle_config.error_log)
			printf("clif_updatestatus : make %d routine\n",type);
		return;
	}
	WFIFOSET(fd,len);

	return;
}

void clif_changestatus(struct block_list *bl, int type, int val)
{
	struct map_session_data *sd = NULL;

	nullpo_retv(bl);

	if(type == SP_MANNER && battle_config.nomanner_mode)
		return;

	if(bl->type == BL_PC)
		sd = (struct map_session_data *)bl;

	if(sd){
		unsigned char buf[12];

		WBUFW(buf,0)=0x1ab;
		WBUFL(buf,2)=bl->id;
		WBUFW(buf,6)=type;
		switch(type){
		case SP_MANNER:
			WBUFL(buf,8)=val;
			break;
		default:
			if(battle_config.error_log)
				printf("clif_changestatus : make %d routine\n",type);
			return;
		}
		clif_send(buf,packet_db[0x1ab].len,bl,AREA_WOS);
	}

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_changelook(struct block_list *bl, int type, int val)
{
	unsigned char buf[16];
	int shield = 0;

	nullpo_retv(bl);

#if PACKETVER >= 4
	if(bl->type == BL_SKILL && type == LOOK_BASE) {		// �g���b�v�̃��j�b�gID�ύX
		WBUFW(buf,0)=0xc3;
		WBUFL(buf,2)=bl->id;
		WBUFB(buf,6)=type;
		WBUFB(buf,7)=val;
		clif_send(buf,packet_db[0xc3].len,bl,AREA);
		return;
	}
#endif

	if(bl->type == BL_PC) {
		struct map_session_data *sd = (struct map_session_data *)bl;
		if(sd) {
			switch (type) {
				case LOOK_WEAPON:
				case LOOK_SHIELD:
					clif_get_weapon_view(sd, &val, &shield);
					break;
				case LOOK_SHOES:
					{
						int idx = sd->equip_index[EQUIP_INDEX_SHOES];
						if(idx >= 0 && sd->inventory_data[idx]) {
							if(sd->inventory_data[idx]->view_id > 0)
								val = sd->inventory_data[idx]->view_id;
							else
								val = sd->status.inventory[idx].nameid;
						} else {
							val = 0;
						}
					}
					break;
				case LOOK_ROBE:
#if PACKETVER < 20110111
					return;
#endif
					break;
			}
		}
	}

#if PACKETVER < 4
	WBUFW(buf,0)=0xc3;
	WBUFL(buf,2)=bl->id;
	WBUFB(buf,6)=type;
	WBUFB(buf,7)=val;
	clif_send(buf,packet_db[0xc3].len,bl,AREA);
#elif PACKETVER < 20180704
	WBUFW(buf,0)=0x1d7;
	WBUFL(buf,2)=bl->id;
	if(type == LOOK_WEAPON || type == LOOK_SHIELD) {
		WBUFB(buf,6)=LOOK_WEAPON;
		WBUFW(buf,7)=val;
		WBUFW(buf,9)=shield;
	} else {
		WBUFB(buf,6)=type;
		WBUFL(buf,7)=val;
	}
	clif_send(buf,packet_db[0x1d7].len,bl,AREA);
#else
	WBUFW(buf,0)=0x1d7;
	WBUFL(buf,2)=bl->id;
	if(type == LOOK_WEAPON || type == LOOK_SHIELD) {
		WBUFB(buf,6)=LOOK_WEAPON;
		WBUFL(buf,7)=val;
		WBUFL(buf,11)=shield;
	} else {
		WBUFB(buf,6)=type;
		WBUFL(buf,7)=val;
	}
	clif_send(buf,packet_db[0x1d7].len,bl,AREA);
#endif
	return;
}

/*==========================================
 * ���F�p�P�b�g����t���i��{�F�������j
 *------------------------------------------
 */
/*void clif_send_clothcolor(struct block_list *bl)
{
	short color;
	unsigned char buf[16];

	nullpo_retv(bl);

	color = status_get_clothes_color(bl);
	if(color <= 0)
		return;

#if PACKETVER < 4
	WBUFW(buf,0) = 0xc3;
	WBUFL(buf,2) = bl->id;
	WBUFB(buf,6) = LOOK_CLOTHES_COLOR;
	WBUFB(buf,7) = (unsigned char)color;
	clif_send(buf,packet_db[0xc3].len,bl,AREA);
#else
	WBUFW(buf,0) = 0x1d7;
	WBUFL(buf,2) = bl->id;
	WBUFB(buf,6) = LOOK_CLOTHES_COLOR;
	WBUFW(buf,7) = color;
	WBUFW(buf,9) = 0;
	clif_send(buf,packet_db[0x1d7].len,bl,AREA);
#endif
	return;
}*/

/*==========================================
 *
 *------------------------------------------
 */
static void clif_initialstatus(struct map_session_data *sd)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xbd;
	WFIFOW(fd,2)=sd->status.status_point;
	WFIFOB(fd,4)=(sd->status.str > 255)? 255: sd->status.str;
	WFIFOB(fd,5)=pc_need_status_point(sd,SP_STR);
	WFIFOB(fd,6)=(sd->status.agi > 255)? 255: sd->status.agi;
	WFIFOB(fd,7)=pc_need_status_point(sd,SP_AGI);
	WFIFOB(fd,8)=(sd->status.vit > 255)? 255: sd->status.vit;
	WFIFOB(fd,9)=pc_need_status_point(sd,SP_VIT);
	WFIFOB(fd,10)=(sd->status.int_ > 255)? 255: sd->status.int_;
	WFIFOB(fd,11)=pc_need_status_point(sd,SP_INT);
	WFIFOB(fd,12)=(sd->status.dex > 255)? 255: sd->status.dex;
	WFIFOB(fd,13)=pc_need_status_point(sd,SP_DEX);
	WFIFOB(fd,14)=(sd->status.luk > 255)? 255: sd->status.luk;
	WFIFOB(fd,15)=pc_need_status_point(sd,SP_LUK);

#ifdef PRE_RENEWAL
	WFIFOW(fd,16) = sd->base_atk + sd->watk + sd->watk_;
	WFIFOW(fd,18) = sd->watk2 + sd->watk_2;	// atk bonus
	WFIFOW(fd,20) = sd->matk1;
	WFIFOW(fd,22) = sd->matk2;
	WFIFOW(fd,24) = sd->def;	// def
	WFIFOW(fd,26) = sd->def2;
	WFIFOW(fd,28) = sd->mdef;	// mdef
	WFIFOW(fd,30) = sd->mdef2;
	WFIFOW(fd,32) = sd->hit;
	WFIFOW(fd,34) = sd->flee;
	WFIFOW(fd,36) = sd->flee2/10;
	WFIFOW(fd,38) = sd->critical/10;
	WFIFOW(fd,40) = sd->amotion;
	WFIFOW(fd,42) = 0;
#else
	WFIFOW(fd,16) = sd->base_atk;
	WFIFOW(fd,18) = sd->watk + sd->watk_ + sd->watk2 + sd->watk_2 + sd->plus_atk;	// atk
	WFIFOW(fd,20) = sd->matk1 + sd->plus_matk;
	WFIFOW(fd,22) = sd->matk2;
	WFIFOW(fd,24) = sd->def2;
	WFIFOW(fd,26) = sd->def;	// def
	WFIFOW(fd,28) = sd->mdef2;
	WFIFOW(fd,30) = sd->mdef;	// mdef
	WFIFOW(fd,32) = sd->hit;
	WFIFOW(fd,34) = sd->flee;
	WFIFOW(fd,36) = sd->flee2/10;
	WFIFOW(fd,38) = sd->critical/10;
	WFIFOW(fd,40) = sd->amotion;
	WFIFOW(fd,42) = 0;
#endif

	WFIFOSET(fd,packet_db[0xbd].len);

	clif_updatestatus(sd,SP_ATTACKRANGE);

	return;
}

/*==========================================
 * ���
 *------------------------------------------
 */
void clif_arrowequip(struct map_session_data *sd, int idx)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x13c;
	WFIFOW(fd,2)=idx+2;
	WFIFOSET(fd,packet_db[0x13c].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_arrow_fail(struct map_session_data *sd, unsigned short type)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x13b;
	WFIFOW(fd,2)=type;
	WFIFOSET(fd,packet_db[0x13b].len);

	return;
}

/*==========================================
 * �쐬�\ ��X�g���M
 *------------------------------------------
 */
void clif_arrow_create_list(struct map_session_data *sd)
{
	int i, view, idx, c = 0;
	int fd;

	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x1ad;

#if PACKETVER < 20180704
	for(i = 0; i < MAX_SKILL_ARROW_DB; i++) {
		if(skill_arrow_db[i].nameid > 0 &&
		   (idx = pc_search_inventory(sd,skill_arrow_db[i].nameid)) >= 0 &&
		   !sd->status.inventory[idx].equip)
		{
			if((view = itemdb_viewid(skill_arrow_db[i].nameid)) > 0)
				WFIFOW(fd,c*2+4) = view;
			else
				WFIFOW(fd,c*2+4) = skill_arrow_db[i].nameid;
			c++;
		}
	}
	WFIFOW(fd,2) = c * 2 + 4;
	WFIFOSET(fd, WFIFOW(fd,2));
#else
	for(i = 0; i < MAX_SKILL_ARROW_DB; i++) {
		if(skill_arrow_db[i].nameid > 0 &&
		   (idx = pc_search_inventory(sd,skill_arrow_db[i].nameid)) >= 0 &&
		   !sd->status.inventory[idx].equip)
		{
			if((view = itemdb_viewid(skill_arrow_db[i].nameid)) > 0)
				WFIFOL(fd,c*4+4) = view;
			else
				WFIFOL(fd,c*4+4) = skill_arrow_db[i].nameid;
			c++;
		}
	}
	WFIFOW(fd,2) = c * 4 + 4;
	WFIFOSET(fd, WFIFOW(fd,2));
#endif

	if(c > 0) {
		sd->skill_menu.id = AC_MAKINGARROW;
		sd->skill_menu.lv = 1;
	}

	return;
}

/*==========================================
 * �|�C�Y�j���O�E�F�|���I��
 *------------------------------------------
 */
void clif_poison_list(struct map_session_data *sd, short lv)
{
	int i, view, idx, c = 0;
	int fd;
	static const int poison_list[] = {
		12717, 12718, 12719, 12720, 12721, 12722, 12723, 12724
	};

	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x1ad;

#if PACKETVER < 20180704
	for(i = 0; i < sizeof(poison_list)/sizeof(poison_list[0]); i++) {
		if(poison_list[i] > 0 &&
			(idx = pc_search_inventory(sd, poison_list[i])) >= 0 &&
			!sd->status.inventory[idx].equip && sd->status.inventory[idx].identify)
		{
			if((view = itemdb_viewid(poison_list[i])) > 0)
				WFIFOW(fd,c*2+4) = view;
			else
				WFIFOW(fd,c*2+4) = poison_list[i];
			c++;
		}
	}

	if(c > 0) {
		WFIFOW(fd,2) = c * 2 + 4;
		WFIFOSET(fd, WFIFOW(fd,2));
#else
	for(i = 0; i < sizeof(poison_list)/sizeof(poison_list[0]); i++) {
		if(poison_list[i] > 0 &&
			(idx = pc_search_inventory(sd, poison_list[i])) >= 0 &&
			!sd->status.inventory[idx].equip && sd->status.inventory[idx].identify)
		{
			if((view = itemdb_viewid(poison_list[i])) > 0)
				WFIFOL(fd,c*4+4) = view;
			else
				WFIFOL(fd,c*4+4) = poison_list[i];
			c++;
		}
	}

	if(c > 0) {
		WFIFOW(fd,2) = c * 4 + 4;
		WFIFOSET(fd, WFIFOW(fd,2));
#endif

		sd->skill_menu.id = GC_POISONINGWEAPON;
		sd->skill_menu.lv = lv;
	} else {
		clif_skill_fail(sd,GC_POISONINGWEAPON,SKILLFAIL_GC_POISON,0,0);
	}

	return;
}

/*==========================================
 * ���[�f�B���O�X�y���u�b�N�I��
 *------------------------------------------
 */
void clif_reading_sb_list(struct map_session_data *sd)
{
	int i, view, idx, c = 0;
	int fd;
	static const int sb_list[] = {
		6189, 6190, 6191, 6192, 6193, 6194,
		6195, 6196,	6197, 6198,	6199, 6200,
		6201, 6202, 6203, 6204, 6205
	};

	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x1ad;

#if PACKETVER < 20180704
	for(i = 0; i < sizeof(sb_list)/sizeof(sb_list[0]); i++) {
		if(sb_list[i] > 0 &&
			(idx = pc_search_inventory(sd, sb_list[i])) >= 0 &&
			!sd->status.inventory[idx].equip && sd->status.inventory[idx].identify)
		{
			if((view = itemdb_viewid(sb_list[i])) > 0)
				WFIFOW(fd,c*2+4) = view;
			else
				WFIFOW(fd,c*2+4) = sb_list[i];
			c++;
		}
	}

	if(c > 0) {
		WFIFOW(fd,2) = c * 2 + 4;
		WFIFOSET(fd, WFIFOW(fd,2));
#else
	for(i = 0; i < sizeof(sb_list)/sizeof(sb_list[0]); i++) {
		if(sb_list[i] > 0 &&
			(idx = pc_search_inventory(sd, sb_list[i])) >= 0 &&
			!sd->status.inventory[idx].equip && sd->status.inventory[idx].identify)
		{
			if((view = itemdb_viewid(sb_list[i])) > 0)
				WFIFOL(fd,c*4+4) = view;
			else
				WFIFOL(fd,c*4+4) = sb_list[i];
			c++;
		}
	}

	if(c > 0) {
		WFIFOW(fd,2) = c * 4 + 4;
		WFIFOSET(fd, WFIFOW(fd,2));
#endif

		sd->skill_menu.id = WL_READING_SB;
		sd->skill_menu.lv = 1;
	} else {
		clif_skill_fail(sd,WL_READING_SB,SKILLFAIL_SPELLBOOK,0,0);
	}

	return;
}

/*==========================================
 * FAW �}�W�b�N�f�R�C�I��
 *------------------------------------------
 */
void clif_magicdecoy_list(struct map_session_data *sd, short lv, short x, short y)
{
	int i, view, idx, c = 0;
	int fd;
	static const int ele_list[] = {
		990, 991, 992, 993
	};

	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x1ad;

#if PACKETVER < 20180704
	for(i = 0; i < sizeof(ele_list)/sizeof(ele_list[0]); i++) {
		if(ele_list[i] > 0 &&
			(idx = pc_search_inventory(sd, ele_list[i])) >= 0 &&
			!sd->status.inventory[idx].equip && sd->status.inventory[idx].identify)
		{
			if((view = itemdb_viewid(ele_list[i])) > 0)
				WFIFOW(fd,c*2+4) = view;
			else
				WFIFOW(fd,c*2+4) = ele_list[i];
			c++;
		}
	}

	if(c > 0) {
		WFIFOW(fd,2) = c * 2 + 4;
		WFIFOSET(fd, WFIFOW(fd,2));
#else
	for(i = 0; i < sizeof(ele_list)/sizeof(ele_list[0]); i++) {
		if(ele_list[i] > 0 &&
			(idx = pc_search_inventory(sd, ele_list[i])) >= 0 &&
			!sd->status.inventory[idx].equip && sd->status.inventory[idx].identify)
		{
			if((view = itemdb_viewid(ele_list[i])) > 0)
				WFIFOL(fd,c*4+4) = view;
			else
				WFIFOL(fd,c*4+4) = ele_list[i];
			c++;
		}
	}

	if(c > 0) {
		WFIFOW(fd,2) = c * 4 + 4;
		WFIFOSET(fd, WFIFOW(fd,2));
#endif

		sd->skill_menu.id = NC_MAGICDECOY;
		sd->skill_menu.lv = lv;
		sd->skill_menu.val = (x<<16)|y;
	} else {
		clif_skill_fail(sd,NC_MAGICDECOY,SKILLFAIL_MATERIAL,0,0);
	}

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_statusupack(struct map_session_data *sd, int type, int ok, int val)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xbc;
	WFIFOW(fd,2)=type;
	WFIFOB(fd,4)=ok;
	WFIFOB(fd,5)=val;
	WFIFOSET(fd,packet_db[0xbc].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_equipitemack(struct map_session_data *sd, int n, int pos, unsigned char ok)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
#if PACKETVER < 20100629
	WFIFOW(fd,0)=0xaa;
	WFIFOW(fd,2)=n+2;
	WFIFOW(fd,4)=pos;
	WFIFOB(fd,6)=ok;
	WFIFOSET(fd,packet_db[0xaa].len);
#elif PACKETVER < 20120925
	WFIFOW(fd,0)=0xaa;
	WFIFOW(fd,2)=n+2;
	WFIFOW(fd,4)=pos;
	if(ok && sd->inventory_data[n]->equip&(LOC_HEAD_TMB|LOC_COSTUME_HEAD_TMB))
		WFIFOW(fd,6)=sd->inventory_data[n]->look;
	else
		WFIFOW(fd,6)=0;
	WFIFOB(fd,8)=ok;
	WFIFOSET(fd,packet_db[0xaa].len);
#else
	WFIFOW(fd,0)=0x999;
	WFIFOW(fd,2)=n+2;
	WFIFOL(fd,4)=pos;
	if(ok && sd->inventory_data[n]->equip&(LOC_HEAD_TMB|LOC_COSTUME_HEAD_TMB))
		WFIFOW(fd,8)=sd->inventory_data[n]->look;
	else
		WFIFOW(fd,8)=0;
	WFIFOB(fd,10)=ok? 0: 1;
	WFIFOSET(fd,packet_db[0x999].len);
#endif

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_unequipitemack(struct map_session_data *sd, int n, int pos, unsigned char ok)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
#if PACKETVER < 20120925
	WFIFOW(fd,0)=0xac;
	WFIFOW(fd,2)=n+2;
	WFIFOW(fd,4)=pos;
	WFIFOB(fd,6)=ok;
	WFIFOSET(fd,packet_db[0xac].len);
#else
	WFIFOW(fd,0)=0x99a;
	WFIFOW(fd,2)=n+2;
	WFIFOL(fd,4)=pos;
	WFIFOB(fd,8)=ok? 0: 1;
	WFIFOSET(fd,packet_db[0x99a].len);
#endif

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_misceffect(struct block_list* bl, int type)
{
	unsigned char buf[16];

	nullpo_retv(bl);

	WBUFW(buf,0) = 0x19b;
	WBUFL(buf,2) = bl->id;
	WBUFL(buf,6) = type;
	clif_send(buf,packet_db[0x19b].len,bl,AREA);

	return;
}

/*==========================================
 * bl���甭������G�t�F�N�g
 *------------------------------------------
 */
void clif_misceffect2(struct block_list *bl,int type)
{
	unsigned char buf[16];

	nullpo_retv(bl);

	WBUFW(buf,0)=0x1f3;
	WBUFL(buf,2)=bl->id;
	WBUFL(buf,6)=type;
	clif_send(buf,packet_db[0x1f3].len,bl,AREA);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_misceffect3(int fd, int id, int type)
{
	WFIFOW(fd,0)=0x1f3;
	WFIFOL(fd,2)=id;
	WFIFOL(fd,6)=type;
	WFIFOSET(fd,packet_db[0x1f3].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_misceffect_value(struct block_list* bl, int type, int num)
{
	unsigned char buf[18];

	nullpo_retv(bl);

	WBUFW(buf,0) = 0x284;
	WBUFL(buf,2) = bl->id;
	WBUFL(buf,6) = type;
	WBUFL(buf,10) = num;
	clif_send(buf,packet_db[0x284].len,bl,AREA);

	return;
}

/*==========================================
 * bl���甭������G�t�F�N�g�폜
 *------------------------------------------
 */
void clif_remove_misceffect2(struct block_list *bl,int type)
{
    unsigned char buf[16];

    nullpo_retv(bl);

    WBUFW(buf,0)=0xb0d;
    WBUFL(buf,2)=bl->id;
    WBUFL(buf,6)=type;
    clif_send(buf,packet_db[0xb0d].len,bl,AREA);

    return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_remove_misceffect3(int fd, int id, int type)
{
    WFIFOW(fd,0)=0xb0d;
    WFIFOL(fd,2)=id;
    WFIFOL(fd,6)=type;
    WFIFOSET(fd,packet_db[0xb0d].len);

    return;
}

/*==========================================
 * �\���I�v�V�����ύX
 *------------------------------------------
 */
void clif_changeoption(struct block_list* bl)
{
	unsigned char buf[16];
	struct status_change *sc;
	struct map_session_data *sd = NULL;

	nullpo_retv(bl);

	sc = status_get_sc(bl);

	if(bl->type == BL_PC)
		sd = (struct map_session_data *)bl;
	if(sd) {
		clif_changelook(&sd->bl,LOOK_BASE,sd->view_class);
		pc_changebodystyle(sd);
	}

#if PACKETVER < 7
	WBUFW(buf, 0) = 0x119;
	WBUFL(buf, 2) = bl->id;
	WBUFW(buf, 6) = (sc) ? sc->opt1 : OPT1_NORMAL;
	WBUFW(buf, 8) = (sc) ? sc->opt2 : OPT2_NORMAL;
	WBUFW(buf,10) = (sc) ? sc->option : (bl->type == BL_NPC) ? ((struct npc_data *)bl)->option : OPTION_NOTHING;
	WBUFB(buf,12) = (sd) ? (unsigned char)sd->status.karma : ( bl->type == BL_MOB )? mob_is_pcview(((struct mob_data *)bl)->class_) : 0;
	clif_send(buf,packet_db[0x119].len,bl,AREA);
#else
	WBUFW(buf, 0) = 0x229;
	WBUFL(buf, 2) = bl->id;
	WBUFW(buf, 6) = (sc) ? sc->opt1 : OPT1_NORMAL;
	WBUFW(buf, 8) = (sc) ? sc->opt2 : OPT2_NORMAL;
	WBUFL(buf,10) = (sc) ? sc->option : (bl->type == BL_NPC) ? ((struct npc_data *)bl)->option : OPTION_NOTHING;
	WBUFB(buf,14) = (sd) ? (unsigned char)sd->status.karma : ( bl->type == BL_MOB )? mob_is_pcview(((struct mob_data *)bl)->class_) : 0;
	clif_send(buf,packet_db[0x229].len,bl,AREA);
#endif

	return;
}

/*==========================================
 * �\���I�v�V�����ύX
 *------------------------------------------
 */
void clif_changeoption_single(struct block_list* bl, struct map_session_data *tsd)
{
	int fd;
	struct status_change *sc;
	struct map_session_data *sd = NULL;

	nullpo_retv(bl);
	nullpo_retv(tsd);

	sc = status_get_sc(bl);

	if(bl->type == BL_PC)
		sd = (struct map_session_data *)bl;
	if(sd) {
		clif_changelook(&sd->bl,LOOK_BASE,sd->view_class);
		pc_changebodystyle(sd);
	}

	fd=tsd->fd;
#if PACKETVER < 7
	WFIFOW(fd, 0) = 0x119;
	WFIFOL(fd, 2) = bl->id;
	WFIFOW(fd, 6) = (sc) ? sc->opt1 : OPT1_NORMAL;
	WFIFOW(fd, 8) = (sc) ? sc->opt2 : OPT2_NORMAL;
	WFIFOW(fd,10) = (sc) ? sc->option : (bl->type == BL_NPC) ? ((struct npc_data *)bl)->option : OPTION_NOTHING;
	WFIFOB(fd,12) = (sd) ? (unsigned char)sd->status.karma : ( bl->type == BL_MOB )? mob_is_pcview(((struct mob_data *)bl)->class_) : 0;
	WFIFOSET(fd,packet_db[0x119].len);
#else
	WFIFOW(fd, 0) = 0x229;
	WFIFOL(fd, 2) = bl->id;
	WFIFOW(fd, 6) = (sc) ? sc->opt1 : OPT1_NORMAL;
	WFIFOW(fd, 8) = (sc) ? sc->opt2 : OPT2_NORMAL;
	WFIFOL(fd,10) = (sc) ? sc->option : (bl->type == BL_NPC) ? ((struct npc_data *)bl)->option : OPTION_NOTHING;
	WFIFOB(fd,14) = (sd) ? (unsigned char)sd->status.karma : ( bl->type == BL_MOB )? mob_is_pcview(((struct mob_data *)bl)->class_) : 0;
	WFIFOSET(fd,packet_db[0x229].len);
#endif

	return;
}

/*==========================================
 * �\���I�v�V�����ύX2
 *------------------------------------------
 */
void clif_changeoption2(struct block_list *bl)
{
	unsigned char buf[24];
	struct status_change *sc;

	nullpo_retv(bl);

	sc = status_get_sc(bl);

	WBUFW(buf,0)  = 0x28a;
	WBUFL(buf,2)  = bl->id;
	WBUFL(buf,6)  = (sc) ? sc->option : (bl->type == BL_NPC) ? ((struct npc_data *)bl)->option : OPTION_NOTHING;
	if(bl->type == BL_PC) {
		WBUFLV(buf,10,status_get_lv(bl),((struct map_session_data *)bl)->status.class_);
	} else if(bl->type == BL_MOB) {
		WBUFLV(buf,10,status_get_lv(bl),((struct mob_data *)bl)->class_);
	} else if(bl->type == BL_HOM) {
		WBUFLV(buf,10,status_get_lv(bl),((struct homun_data *)bl)->view_class);
	} else if(bl->type == BL_MERC) {
		WBUFLV(buf,10,status_get_lv(bl),((struct merc_data *)bl)->view_class);
	} else if(bl->type == BL_ELEM) {
		WBUFLV(buf,10,status_get_lv(bl),((struct elem_data *)bl)->view_class);
	} else if(bl->type == BL_PET) {
		WBUFLV(buf,10,status_get_lv(bl),((struct pet_data *)bl)->class_);
	}
	WBUFL(buf,14) = (sc) ? sc->opt3 : OPT3_NORMAL;
	clif_send(buf,packet_db[0x28a].len,bl,AREA);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_useitemack(struct map_session_data *sd, int idx, int amount, unsigned char ok)
{
	nullpo_retv(sd);

	if(!ok) {
		int fd=sd->fd;
		WFIFOW(fd,0)=0xa8;
		WFIFOW(fd,2)=idx+2;
		WFIFOW(fd,4)=amount;
		WFIFOB(fd,6)=ok;
		WFIFOSET(fd,packet_db[0xa8].len);
	} else {
#if PACKETVER < 3
		int fd=sd->fd;

		WFIFOW(fd,0)=0xa8;
		WFIFOW(fd,2)=idx+2;
		WFIFOW(fd,4)=amount;
		WFIFOB(fd,6)=ok;
		WFIFOSET(fd,packet_db[0xa8].len);
#elif PACKETVER < 20180704
		unsigned char buf[16];

		WBUFW(buf,0)=0x1c8;
		WBUFW(buf,2)=idx+2;
		if(sd->inventory_data[idx] && sd->inventory_data[idx]->view_id > 0)
			WBUFW(buf,4)=sd->inventory_data[idx]->view_id;
		else
			WBUFW(buf,4)=sd->status.inventory[idx].nameid;
		WBUFL(buf,6)=sd->bl.id;
		WBUFW(buf,10)=amount;
		WBUFB(buf,12)=ok;
		clif_send(buf,packet_db[0x1c8].len,&sd->bl,AREA);
#else
		unsigned char buf[18];

		WBUFW(buf,0)=0x1c8;
		WBUFW(buf,2)=idx+2;
		if(sd->inventory_data[idx] && sd->inventory_data[idx]->view_id > 0)
			WBUFL(buf,4)=sd->inventory_data[idx]->view_id;
		else
			WBUFL(buf,4)=sd->status.inventory[idx].nameid;
		WBUFL(buf,8)=sd->bl.id;
		WBUFW(buf,12)=amount;
		WBUFB(buf,14)=ok;
		clif_send(buf,packet_db[0x1c8].len,&sd->bl,AREA);
#endif
	}

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_createchat(struct map_session_data *sd, unsigned char fail)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xd6;
	WFIFOB(fd,2)=fail;
	WFIFOSET(fd,packet_db[0xd6].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_dispchat(struct chat_data *cd, int fd)
{
	unsigned char buf[80];	// �ő�title(60�o�C�g)+17

	if(cd==NULL || *cd->owner==NULL)
		return;

	WBUFW(buf, 0)=0xd7;
	WBUFW(buf, 2)=(unsigned short)(strlen(cd->title)+18);
	WBUFL(buf, 4)=(*cd->owner)->id;
	WBUFL(buf, 8)=cd->bl.id;
	WBUFW(buf,12)=cd->limit;
	WBUFW(buf,14)=cd->users;
	WBUFB(buf,16)=cd->pub;
	strncpy(WBUFP(buf,17),cd->title,strlen(cd->title)+1);
	if(fd >= 0) {
		memcpy(WFIFOP(fd,0),buf,WBUFW(buf,2));
		WFIFOSET(fd,WBUFW(buf,2));
	} else {
		clif_send(buf,WBUFW(buf,2),*cd->owner,AREA_WOSC);
	}

	return;
}

/*==========================================
 * chat�̏�ԕύX����
 * �O���̐l�p�Ɩ��߃R�[�h(d7->df)���Ⴄ����
 *------------------------------------------
 */
void clif_changechatstatus(struct chat_data *cd)
{
	unsigned char buf[80];	// �ő�title(60�o�C�g)+17

	if(cd==NULL || cd->usersd[0]==NULL)
		return;

	WBUFW(buf, 0)=0xdf;
	WBUFW(buf, 2)=(unsigned short)(strlen(cd->title)+18);
	WBUFL(buf, 4)=cd->usersd[0]->bl.id;
	WBUFL(buf, 8)=cd->bl.id;
	WBUFW(buf,12)=cd->limit;
	WBUFW(buf,14)=cd->users;
	WBUFB(buf,16)=cd->pub;
	strncpy(WBUFP(buf,17),cd->title,strlen(cd->title)+1);
	clif_send(buf,WBUFW(buf,2),&cd->usersd[0]->bl,CHAT);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_clearchat(struct chat_data *cd, int fd)
{
	unsigned char buf[8];

	nullpo_retv(cd);

	WBUFW(buf,0)=0xd8;
	WBUFL(buf,2)=cd->bl.id;
	if(fd >= 0) {
		memcpy(WFIFOP(fd,0),buf,packet_db[0xd8].len);
		WFIFOSET(fd,packet_db[0xd8].len);
	} else {
		clif_send(buf,packet_db[0xd8].len,*cd->owner,AREA_WOSC);
	}

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_joinchatfail(struct map_session_data *sd, unsigned char fail)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;

	WFIFOW(fd,0)=0xda;
	WFIFOB(fd,2)=fail;
	WFIFOSET(fd,packet_db[0xda].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_joinchatok(struct map_session_data *sd, struct chat_data* cd)
{
	int i,fd;

	nullpo_retv(sd);
	nullpo_retv(cd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xdb;
	WFIFOW(fd,2)=8+(28*cd->users);
	WFIFOL(fd,4)=cd->bl.id;
	for(i = 0;i < cd->users;i++){
		WFIFOL(fd,8+i*28) = (i!=0)||((*cd->owner)->type==BL_NPC);
		memcpy(WFIFOP(fd,8+i*28+4),cd->usersd[i]->status.name,24);
	}
	WFIFOSET(fd,WFIFOW(fd,2));

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_addchat(struct chat_data* cd, struct map_session_data *sd)
{
	unsigned char buf[32];

	nullpo_retv(sd);
	nullpo_retv(cd);

	WBUFW(buf, 0) = 0xdc;
	WBUFW(buf, 2) = cd->users;
	memcpy(WBUFP(buf, 4),sd->status.name,24);
	clif_send(buf,packet_db[0xdc].len,&sd->bl,CHAT_WOS);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_changechatowner(struct chat_data* cd, struct map_session_data *sd)
{
	unsigned char buf[64];

	nullpo_retv(sd);
	nullpo_retv(cd);

	WBUFW(buf, 0) = 0xe1;
	WBUFL(buf, 2) = 1;
	memcpy(WBUFP(buf,6),cd->usersd[0]->status.name,24);
	WBUFW(buf,30) = 0xe1;
	WBUFL(buf,32) = 0;
	memcpy(WBUFP(buf,36),sd->status.name,24);
	clif_send(buf,packet_db[0xe1].len*2,&sd->bl,CHAT);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_leavechat(struct chat_data* cd, struct map_session_data *sd, unsigned char flag)
{
	unsigned char buf[32];

	nullpo_retv(sd);
	nullpo_retv(cd);

	WBUFW(buf, 0) = 0xdd;
	WBUFW(buf, 2) = cd->users-1;
	memcpy(WBUFP(buf,4),sd->status.name,24);
	WBUFB(buf,28) = flag;
	clif_send(buf,packet_db[0xdd].len,&sd->bl,CHAT);

	return;
}

/*==========================================
 * �������v����
 *------------------------------------------
 */
void clif_traderequest(struct map_session_data *sd, const char *name)
{
	int fd;
	struct map_session_data *target_sd = NULL;

	nullpo_retv(sd);

	fd=sd->fd;
#if PACKETVER < 6
	WFIFOW(fd,0)=0xe5;
	strncpy(WFIFOP(fd,2),name,24);
	WFIFOSET(fd,packet_db[0xe5].len);
#else
	nullpo_retv((target_sd = map_id2sd(sd->trade.partner)));
	WFIFOW(fd,0)=0x1f4;
	strncpy(WFIFOP(fd,2),name,24);
	WFIFOL(fd,26)=target_sd->status.char_id;
	WFIFOW(fd,30)=target_sd->status.base_level;
	WFIFOSET(fd,packet_db[0x1f4].len);
#endif

	return;
}

/*==========================================
 * �������v������
 *------------------------------------------
 */
void clif_tradestart(struct map_session_data *sd, unsigned char type)
{
	int fd;
	struct map_session_data *target_sd = NULL;

	nullpo_retv(sd);

	fd=sd->fd;
#if PACKETVER < 6
	WFIFOW(fd,0)=0xe7;
	WFIFOB(fd,2)=type;
	WFIFOSET(fd,packet_db[0xe7].len);
#else
	target_sd = map_id2sd(sd->trade.partner);
	WFIFOW(fd,0)=0x1f5;
	WFIFOB(fd,2)=type;
	WFIFOL(fd,3)=(target_sd!=NULL)?target_sd->status.char_id:0;
	WFIFOW(fd,7)=(target_sd!=NULL)?target_sd->status.base_level:0;
	WFIFOSET(fd,packet_db[0x1f5].len);
#endif

	return;
}

/*==========================================
 * ���������̃A�C�e���ǉ�
 *------------------------------------------
 */
void clif_tradeadditem(struct map_session_data *sd,struct map_session_data *tsd, int idx, int amount)
{
	int fd,j;

	nullpo_retv(sd);
	nullpo_retv(tsd);

	fd=tsd->fd;
#if PACKETVER < 20100223
	WFIFOW(fd,0)=0xe9;
	WFIFOL(fd,2)=amount;
	if(idx==0){
		WFIFOW(fd,6) = 0; // type id
		WFIFOB(fd,8) = 0; // identify flag
		WFIFOB(fd,9) = 0; // attribute
		WFIFOB(fd,10)= 0; // refine
		WFIFOW(fd,11)= 0; // card (4w)
		WFIFOW(fd,13)= 0; // card (4w)
		WFIFOW(fd,15)= 0; // card (4w)
		WFIFOW(fd,17)= 0; // card (4w)
	} else {
		idx -= 2;
		if(sd->inventory_data[idx] && sd->inventory_data[idx]->view_id > 0)
			WFIFOW(fd,6) = sd->inventory_data[idx]->view_id;
		else
			WFIFOW(fd,6) = sd->status.inventory[idx].nameid;
		WFIFOB(fd,8) = sd->status.inventory[idx].identify;
		WFIFOB(fd,9) = sd->status.inventory[idx].attribute;
		WFIFOB(fd,10)= sd->status.inventory[idx].refine;
		if(itemdb_isspecial(sd->status.inventory[idx].card[0])) {
			if(sd->inventory_data[idx]->flag.pet_egg) {
				WFIFOW(fd,11) = 0;
				WFIFOW(fd,13) = 0;
				WFIFOW(fd,15) = 0;
			} else {
				WFIFOW(fd,11) = sd->status.inventory[idx].card[0];
				WFIFOW(fd,13) = sd->status.inventory[idx].card[1];
				WFIFOW(fd,15) = sd->status.inventory[idx].card[2];
			}
			WFIFOW(fd,17) = sd->status.inventory[idx].card[3];
		} else {
			if(sd->status.inventory[idx].card[0] > 0 && (j=itemdb_viewid(sd->status.inventory[idx].card[0])) > 0)
				WFIFOW(fd,11)= j;
			else
				WFIFOW(fd,11)= sd->status.inventory[idx].card[0];
			if(sd->status.inventory[idx].card[1] > 0 && (j=itemdb_viewid(sd->status.inventory[idx].card[1])) > 0)
				WFIFOW(fd,13)= j;
			else
				WFIFOW(fd,13)= sd->status.inventory[idx].card[1];
			if(sd->status.inventory[idx].card[2] > 0 && (j=itemdb_viewid(sd->status.inventory[idx].card[2])) > 0)
				WFIFOW(fd,15)= j;
			else
				WFIFOW(fd,15)= sd->status.inventory[idx].card[2];
			if(sd->status.inventory[idx].card[3] > 0 && (j=itemdb_viewid(sd->status.inventory[idx].card[3])) > 0)
				WFIFOW(fd,17)= j;
			else
				WFIFOW(fd,17)= sd->status.inventory[idx].card[3];
		}
	}
	WFIFOSET(fd,packet_db[0xe9].len);
#elif PACKETVER < 20150513
	WFIFOW(fd,0)=0x80f;
	if(idx==0){
		WFIFOW(fd,2) = 0; // type id
		WFIFOB(fd,4) = 0;	// type
		WFIFOL(fd,5) = amount;	// amount
		WFIFOB(fd,9) = 0; // identify flag
		WFIFOB(fd,10)= 0; // attribute
		WFIFOB(fd,11)= 0; // refine
		WFIFOW(fd,12)= 0; // card (4w)
		WFIFOW(fd,14)= 0; // card (4w)
		WFIFOW(fd,16)= 0; // card (4w)
		WFIFOW(fd,18)= 0; // card (4w)
	} else {
		idx -= 2;
		if(sd->inventory_data[idx] && sd->inventory_data[idx]->view_id > 0)
			WFIFOW(fd,2) = sd->inventory_data[idx]->view_id;
		else
			WFIFOW(fd,2) = sd->status.inventory[idx].nameid;
		WFIFOB(fd,4) = itemdb_type(sd->status.inventory[idx].nameid);
		WFIFOL(fd,5) = amount;
		WFIFOB(fd,9) = sd->status.inventory[idx].identify;
		WFIFOB(fd,10)= sd->status.inventory[idx].attribute;
		WFIFOB(fd,11)= sd->status.inventory[idx].refine;
		if(itemdb_isspecial(sd->status.inventory[idx].card[0])) {
			if(sd->inventory_data[idx]->flag.pet_egg) {
				WFIFOW(fd,12) = 0;
				WFIFOW(fd,14) = 0;
				WFIFOW(fd,16) = 0;
			} else {
				WFIFOW(fd,12) = sd->status.inventory[idx].card[0];
				WFIFOW(fd,14) = sd->status.inventory[idx].card[1];
				WFIFOW(fd,16) = sd->status.inventory[idx].card[2];
			}
			WFIFOW(fd,18) = sd->status.inventory[idx].card[3];
		} else {
			if(sd->status.inventory[idx].card[0] > 0 && (j=itemdb_viewid(sd->status.inventory[idx].card[0])) > 0)
				WFIFOW(fd,12)= j;
			else
				WFIFOW(fd,12)= sd->status.inventory[idx].card[0];
			if(sd->status.inventory[idx].card[1] > 0 && (j=itemdb_viewid(sd->status.inventory[idx].card[1])) > 0)
				WFIFOW(fd,14)= j;
			else
				WFIFOW(fd,14)= sd->status.inventory[idx].card[1];
			if(sd->status.inventory[idx].card[2] > 0 && (j=itemdb_viewid(sd->status.inventory[idx].card[2])) > 0)
				WFIFOW(fd,16)= j;
			else
				WFIFOW(fd,16)= sd->status.inventory[idx].card[2];
			if(sd->status.inventory[idx].card[3] > 0 && (j=itemdb_viewid(sd->status.inventory[idx].card[3])) > 0)
				WFIFOW(fd,18)= j;
			else
				WFIFOW(fd,18)= sd->status.inventory[idx].card[3];
		}
	}
	WFIFOSET(fd,packet_db[0x80f].len);
#elif PACKETVER < 20180704
	WFIFOW(fd,0)=0xa09;
	if(idx==0){
		WFIFOW(fd,2) = 0; // type id
		WFIFOB(fd,4) = 0;	// type
		WFIFOL(fd,5) = amount;	// amount
		WFIFOB(fd,9) = 0; // identify flag
		WFIFOB(fd,10)= 0; // attribute
		WFIFOB(fd,11)= 0; // refine
		WFIFOW(fd,12)= 0; // card (4w)
		WFIFOW(fd,14)= 0; // card (4w)
		WFIFOW(fd,16)= 0; // card (4w)
		WFIFOW(fd,18)= 0; // card (4w)
		WFIFOW(fd,20)= 0;
		WFIFOW(fd,22)= 0;
		WFIFOB(fd,24)= 0;
		WFIFOW(fd,25)= 0;
		WFIFOW(fd,27)= 0;
		WFIFOB(fd,29)= 0;
		WFIFOW(fd,30)= 0;
		WFIFOW(fd,32)= 0;
		WFIFOB(fd,34)= 0;
		WFIFOW(fd,35)= 0;
		WFIFOW(fd,37)= 0;
		WFIFOB(fd,39)= 0;
		WFIFOW(fd,40)= 0;
		WFIFOW(fd,42)= 0;
		WFIFOB(fd,44)= 0;
	} else {
		idx -= 2;
		if(sd->inventory_data[idx] && sd->inventory_data[idx]->view_id > 0)
			WFIFOW(fd,2) = sd->inventory_data[idx]->view_id;
		else
			WFIFOW(fd,2) = sd->status.inventory[idx].nameid;
		WFIFOB(fd,4) = itemdb_type(sd->status.inventory[idx].nameid);
		WFIFOL(fd,5) = amount;
		WFIFOB(fd,9) = sd->status.inventory[idx].identify;
		WFIFOB(fd,10)= sd->status.inventory[idx].attribute;
		WFIFOB(fd,11)= sd->status.inventory[idx].refine;
		if(itemdb_isspecial(sd->status.inventory[idx].card[0])) {
			if(sd->inventory_data[idx]->flag.pet_egg) {
				WFIFOW(fd,12) = 0;
				WFIFOW(fd,14) = 0;
				WFIFOW(fd,16) = 0;
			} else {
				WFIFOW(fd,12) = sd->status.inventory[idx].card[0];
				WFIFOW(fd,14) = sd->status.inventory[idx].card[1];
				WFIFOW(fd,16) = sd->status.inventory[idx].card[2];
			}
			WFIFOW(fd,18) = sd->status.inventory[idx].card[3];
		} else {
			if(sd->status.inventory[idx].card[0] > 0 && (j=itemdb_viewid(sd->status.inventory[idx].card[0])) > 0)
				WFIFOW(fd,12)= j;
			else
				WFIFOW(fd,12)= sd->status.inventory[idx].card[0];
			if(sd->status.inventory[idx].card[1] > 0 && (j=itemdb_viewid(sd->status.inventory[idx].card[1])) > 0)
				WFIFOW(fd,14)= j;
			else
				WFIFOW(fd,14)= sd->status.inventory[idx].card[1];
			if(sd->status.inventory[idx].card[2] > 0 && (j=itemdb_viewid(sd->status.inventory[idx].card[2])) > 0)
				WFIFOW(fd,16)= j;
			else
				WFIFOW(fd,16)= sd->status.inventory[idx].card[2];
			if(sd->status.inventory[idx].card[3] > 0 && (j=itemdb_viewid(sd->status.inventory[idx].card[3])) > 0)
				WFIFOW(fd,18)= j;
			else
				WFIFOW(fd,18)= sd->status.inventory[idx].card[3];
		}
		WFIFOW(fd,20)=sd->status.inventory[idx].opt[0].id;
		WFIFOW(fd,22)=sd->status.inventory[idx].opt[0].val;
		WFIFOB(fd,24)=0;
		WFIFOW(fd,25)=sd->status.inventory[idx].opt[1].id;
		WFIFOW(fd,27)=sd->status.inventory[idx].opt[1].val;
		WFIFOB(fd,29)=0;
		WFIFOW(fd,30)=sd->status.inventory[idx].opt[2].id;
		WFIFOW(fd,32)=sd->status.inventory[idx].opt[2].val;
		WFIFOB(fd,34)=0;
		WFIFOW(fd,35)=sd->status.inventory[idx].opt[3].id;
		WFIFOW(fd,37)=sd->status.inventory[idx].opt[3].val;
		WFIFOB(fd,39)=0;
		WFIFOW(fd,40)=sd->status.inventory[idx].opt[4].id;
		WFIFOW(fd,42)=sd->status.inventory[idx].opt[4].val;
		WFIFOB(fd,44)=0;
	}
	WFIFOSET(fd,packet_db[0xa09].len);
#else
	WFIFOW(fd,0)=0xa09;
	if(idx==0){
		WFIFOL(fd,2) = 0; // type id
		WFIFOB(fd,6) = 0;	// type
		WFIFOL(fd,7) = amount;	// amount
		WFIFOB(fd,11) = 0; // identify flag
		WFIFOB(fd,12)= 0; // attribute
		WFIFOB(fd,13)= 0; // refine
		WFIFOL(fd,14)= 0; // card (4l)
		WFIFOL(fd,18)= 0; // card (4l)
		WFIFOL(fd,22)= 0; // card (4l)
		WFIFOL(fd,26)= 0; // card (4l)
		WFIFOW(fd,30)= 0;
		WFIFOW(fd,32)= 0;
		WFIFOB(fd,34)= 0;
		WFIFOW(fd,35)= 0;
		WFIFOW(fd,37)= 0;
		WFIFOB(fd,39)= 0;
		WFIFOW(fd,40)= 0;
		WFIFOW(fd,42)= 0;
		WFIFOB(fd,44)= 0;
		WFIFOW(fd,45)= 0;
		WFIFOW(fd,47)= 0;
		WFIFOB(fd,49)= 0;
		WFIFOW(fd,50)= 0;
		WFIFOW(fd,52)= 0;
		WFIFOB(fd,54)= 0;
	} else {
		idx -= 2;
		if(sd->inventory_data[idx] && sd->inventory_data[idx]->view_id > 0)
			WFIFOL(fd,2) = sd->inventory_data[idx]->view_id;
		else
			WFIFOL(fd,2) = sd->status.inventory[idx].nameid;
		WFIFOB(fd,6) = itemdb_type(sd->status.inventory[idx].nameid);
		WFIFOL(fd,7) = amount;
		WFIFOB(fd,11) = sd->status.inventory[idx].identify;
		WFIFOB(fd,12)= sd->status.inventory[idx].attribute;
		WFIFOB(fd,13)= sd->status.inventory[idx].refine;
		if(itemdb_isspecial(sd->status.inventory[idx].card[0])) {
			if(sd->inventory_data[idx]->flag.pet_egg) {
				WFIFOL(fd,14) = 0;
				WFIFOL(fd,18) = 0;
				WFIFOL(fd,22) = 0;
			} else {
				WFIFOL(fd,14) = sd->status.inventory[idx].card[0];
				WFIFOL(fd,18) = sd->status.inventory[idx].card[1];
				WFIFOL(fd,22) = sd->status.inventory[idx].card[2];
			}
			WFIFOL(fd,26) = sd->status.inventory[idx].card[3];
		} else {
			if(sd->status.inventory[idx].card[0] > 0 && (j=itemdb_viewid(sd->status.inventory[idx].card[0])) > 0)
				WFIFOL(fd,14)= j;
			else
				WFIFOL(fd,14)= sd->status.inventory[idx].card[0];
			if(sd->status.inventory[idx].card[1] > 0 && (j=itemdb_viewid(sd->status.inventory[idx].card[1])) > 0)
				WFIFOL(fd,18)= j;
			else
				WFIFOL(fd,18)= sd->status.inventory[idx].card[1];
			if(sd->status.inventory[idx].card[2] > 0 && (j=itemdb_viewid(sd->status.inventory[idx].card[2])) > 0)
				WFIFOL(fd,22)= j;
			else
				WFIFOL(fd,22)= sd->status.inventory[idx].card[2];
			if(sd->status.inventory[idx].card[3] > 0 && (j=itemdb_viewid(sd->status.inventory[idx].card[3])) > 0)
				WFIFOL(fd,26)= j;
			else
				WFIFOL(fd,26)= sd->status.inventory[idx].card[3];
		}
		WFIFOW(fd,30)=sd->status.inventory[idx].opt[0].id;
		WFIFOW(fd,32)=sd->status.inventory[idx].opt[0].val;
		WFIFOB(fd,34)=0;
		WFIFOW(fd,35)=sd->status.inventory[idx].opt[1].id;
		WFIFOW(fd,37)=sd->status.inventory[idx].opt[1].val;
		WFIFOB(fd,39)=0;
		WFIFOW(fd,40)=sd->status.inventory[idx].opt[2].id;
		WFIFOW(fd,42)=sd->status.inventory[idx].opt[2].val;
		WFIFOB(fd,44)=0;
		WFIFOW(fd,45)=sd->status.inventory[idx].opt[3].id;
		WFIFOW(fd,47)=sd->status.inventory[idx].opt[3].val;
		WFIFOB(fd,49)=0;
		WFIFOW(fd,50)=sd->status.inventory[idx].opt[4].id;
		WFIFOW(fd,52)=sd->status.inventory[idx].opt[4].val;
		WFIFOB(fd,54)=0;
	}
	WFIFOSET(fd,packet_db[0xa09].len);
#endif

	return;
}

/*==========================================
 * �A�C�e���ǉ�����/���s
 *------------------------------------------
 */
void clif_tradeitemok(struct map_session_data *sd, unsigned short idx, unsigned char fail)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xea;
	WFIFOW(fd,2)=idx;
	WFIFOB(fd,4)=fail;
	WFIFOSET(fd,packet_db[0xea].len);

	return;
}

/*==========================================
 * ������ok����
 *------------------------------------------
 */
void clif_tradedeal_lock(struct map_session_data *sd, unsigned char fail)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xec;
	WFIFOB(fd,2)=fail; // 0=you 1=the other person
	WFIFOSET(fd,packet_db[0xec].len);

	return;
}

/*==========================================
 * ���������L�����Z������܂���
 *------------------------------------------
 */
void clif_tradecancelled(struct map_session_data *sd)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xee;
	WFIFOSET(fd,packet_db[0xee].len);

	return;
}

/*==========================================
 * ����������
 *------------------------------------------
 */
void clif_tradecompleted(struct map_session_data *sd, unsigned char fail)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xf0;
	WFIFOB(fd,2)=fail;
	WFIFOSET(fd,packet_db[0xf0].len);

	return;
}

/*==========================================
 * �J�v���q�ɂ̃A�C�e�������X�V
 *------------------------------------------
 */
void clif_updatestorageamount(struct map_session_data *sd, struct storage *stor)
{
	int fd;

	nullpo_retv(sd);
	nullpo_retv(stor);

	fd=sd->fd;
	WFIFOW(fd,0) = 0xf2;
	WFIFOW(fd,2) = stor->storage_amount;
	WFIFOW(fd,4) = MAX_STORAGE;
	WFIFOSET(fd,packet_db[0xf2].len);

	return;
}

/*==========================================
 * �J�v���q�ɂɃA�C�e����ǉ�����
 *------------------------------------------
 */
void clif_storageitemadded(struct map_session_data *sd, struct storage *stor, int idx, int amount)
{
	struct item_data *id;
	int fd,j;

	nullpo_retv(sd);
	nullpo_retv(stor);

	fd = sd->fd;
	id = itemdb_search(stor->store_item[idx].nameid);

#if PACKETVER < 7
	WFIFOW(fd,0) = 0xf4;
	WFIFOW(fd,2) = idx+1;
	WFIFOL(fd,4) = amount;
	if(id->view_id > 0)
		WFIFOW(fd,8) = id->view_id;
	else
		WFIFOW(fd,8) = stor->store_item[idx].nameid;
	WFIFOB(fd,10) = stor->store_item[idx].identify;
	WFIFOB(fd,11) = stor->store_item[idx].attribute;
	WFIFOB(fd,12) = stor->store_item[idx].refine;
	if(itemdb_isspecial(stor->store_item[idx].card[0])) {
		if(id->flag.pet_egg) {
			WFIFOW(fd,13) = 0;
			WFIFOW(fd,15) = 0;
			WFIFOW(fd,17) = 0;
		} else {
			WFIFOW(fd,13) = stor->store_item[idx].card[0];
			WFIFOW(fd,15) = stor->store_item[idx].card[1];
			WFIFOW(fd,17) = stor->store_item[idx].card[2];
		}
		WFIFOW(fd,19) = stor->store_item[idx].card[3];
	} else {
		if(stor->store_item[idx].card[0] > 0 && (j = itemdb_viewid(stor->store_item[idx].card[0])) > 0)
			WFIFOW(fd,13) = j;
		else
			WFIFOW(fd,13) = stor->store_item[idx].card[0];
		if(stor->store_item[idx].card[1] > 0 && (j = itemdb_viewid(stor->store_item[idx].card[1])) > 0)
			WFIFOW(fd,15) = j;
		else
			WFIFOW(fd,15)= stor->store_item[idx].card[1];
		if(stor->store_item[idx].card[2] > 0 && (j = itemdb_viewid(stor->store_item[idx].card[2])) > 0)
			WFIFOW(fd,17) = j;
		else
			WFIFOW(fd,17)= stor->store_item[idx].card[2];
		if(stor->store_item[idx].card[3] > 0 && (j = itemdb_viewid(stor->store_item[idx].card[3])) > 0)
			WFIFOW(fd,19) = j;
		else
			WFIFOW(fd,19) = stor->store_item[idx].card[3];
	}
	WFIFOSET(fd,packet_db[0xf4].len);
#elif PACKETVER < 20150513
	WFIFOW(fd,0) = 0x1c4;
	WFIFOW(fd,2) = idx+1;
	WFIFOL(fd,4) = amount;
	if(id->view_id > 0)
		WFIFOW(fd,8) = id->view_id;
	else
		WFIFOW(fd,8) = stor->store_item[idx].nameid;
	WFIFOB(fd,10) = id->type;
	WFIFOB(fd,11) = stor->store_item[idx].identify;
	WFIFOB(fd,12) = stor->store_item[idx].attribute;
	WFIFOB(fd,13) = stor->store_item[idx].refine;
	if(itemdb_isspecial(stor->store_item[idx].card[0])) {
		if(id->flag.pet_egg) {
			WFIFOW(fd,14) = 0;
			WFIFOW(fd,16) = 0;
			WFIFOW(fd,18) = 0;
		} else {
			WFIFOW(fd,14) = stor->store_item[idx].card[0];
			WFIFOW(fd,16) = stor->store_item[idx].card[1];
			WFIFOW(fd,18) = stor->store_item[idx].card[2];
		}
		WFIFOW(fd,20) = stor->store_item[idx].card[3];
	} else {
		if(stor->store_item[idx].card[0] > 0 && (j = itemdb_viewid(stor->store_item[idx].card[0])) > 0)
			WFIFOW(fd,14) = j;
		else
			WFIFOW(fd,14) = stor->store_item[idx].card[0];
		if(stor->store_item[idx].card[1] > 0 && (j = itemdb_viewid(stor->store_item[idx].card[1])) > 0)
			WFIFOW(fd,16) = j;
		else
			WFIFOW(fd,16) = stor->store_item[idx].card[1];
		if(stor->store_item[idx].card[2] > 0 && (j = itemdb_viewid(stor->store_item[idx].card[2])) > 0)
			WFIFOW(fd,18) = j;
		else
			WFIFOW(fd,18)= stor->store_item[idx].card[2];
		if(stor->store_item[idx].card[3] > 0 && (j = itemdb_viewid(stor->store_item[idx].card[3])) > 0)
			WFIFOW(fd,20) = j;
		else
			WFIFOW(fd,20) = stor->store_item[idx].card[3];
	}
	WFIFOSET(fd,packet_db[0x1c4].len);
#elif PACKETVER < 20180704
	WFIFOW(fd,0) = 0xa0a;
	WFIFOW(fd,2) = idx+1;
	WFIFOL(fd,4) = amount;
	if(id->view_id > 0)
		WFIFOW(fd,8) = id->view_id;
	else
		WFIFOW(fd,8) = stor->store_item[idx].nameid;
	WFIFOB(fd,10) = id->type;
	WFIFOB(fd,11) = stor->store_item[idx].identify;
	WFIFOB(fd,12) = stor->store_item[idx].attribute;
	WFIFOB(fd,13) = stor->store_item[idx].refine;
	if(itemdb_isspecial(stor->store_item[idx].card[0])) {
		if(id->flag.pet_egg) {
			WFIFOW(fd,14) = 0;
			WFIFOW(fd,16) = 0;
			WFIFOW(fd,18) = 0;
		} else {
			WFIFOW(fd,14) = stor->store_item[idx].card[0];
			WFIFOW(fd,16) = stor->store_item[idx].card[1];
			WFIFOW(fd,18) = stor->store_item[idx].card[2];
		}
		WFIFOW(fd,20) = stor->store_item[idx].card[3];
	} else {
		if(stor->store_item[idx].card[0] > 0 && (j = itemdb_viewid(stor->store_item[idx].card[0])) > 0)
			WFIFOW(fd,14) = j;
		else
			WFIFOW(fd,14) = stor->store_item[idx].card[0];
		if(stor->store_item[idx].card[1] > 0 && (j = itemdb_viewid(stor->store_item[idx].card[1])) > 0)
			WFIFOW(fd,16) = j;
		else
			WFIFOW(fd,16) = stor->store_item[idx].card[1];
		if(stor->store_item[idx].card[2] > 0 && (j = itemdb_viewid(stor->store_item[idx].card[2])) > 0)
			WFIFOW(fd,18) = j;
		else
			WFIFOW(fd,18)= stor->store_item[idx].card[2];
		if(stor->store_item[idx].card[3] > 0 && (j = itemdb_viewid(stor->store_item[idx].card[3])) > 0)
			WFIFOW(fd,20) = j;
		else
			WFIFOW(fd,20) = stor->store_item[idx].card[3];
	}
	WFIFOW(fd,22) = stor->store_item[idx].opt[0].id;
	WFIFOW(fd,24) = stor->store_item[idx].opt[0].val;
	WFIFOB(fd,26) = 0;
	WFIFOW(fd,27) = stor->store_item[idx].opt[1].id;
	WFIFOW(fd,29) = stor->store_item[idx].opt[1].val;
	WFIFOB(fd,31) = 0;
	WFIFOW(fd,32) = stor->store_item[idx].opt[2].id;
	WFIFOW(fd,34) = stor->store_item[idx].opt[2].val;
	WFIFOB(fd,36) = 0;
	WFIFOW(fd,37) = stor->store_item[idx].opt[3].id;
	WFIFOW(fd,39) = stor->store_item[idx].opt[3].val;
	WFIFOB(fd,41) = 0;
	WFIFOW(fd,42) = stor->store_item[idx].opt[4].id;
	WFIFOW(fd,44) = stor->store_item[idx].opt[4].val;
	WFIFOB(fd,46) = 0;
	WFIFOSET(fd,packet_db[0xa0a].len);
#else
	WFIFOW(fd,0) = 0xa0a;
	WFIFOW(fd,2) = idx+1;
	WFIFOL(fd,4) = amount;
	if(id->view_id > 0)
		WFIFOL(fd,8) = id->view_id;
	else
		WFIFOL(fd,8) = stor->store_item[idx].nameid;
	WFIFOB(fd,12) = id->type;
	WFIFOB(fd,13) = stor->store_item[idx].identify;
	WFIFOB(fd,14) = stor->store_item[idx].attribute;
	WFIFOB(fd,15) = stor->store_item[idx].refine;
	if(itemdb_isspecial(stor->store_item[idx].card[0])) {
		if(id->flag.pet_egg) {
			WFIFOL(fd,16) = 0;
			WFIFOL(fd,20) = 0;
			WFIFOL(fd,24) = 0;
		} else {
			WFIFOL(fd,16) = stor->store_item[idx].card[0];
			WFIFOL(fd,20) = stor->store_item[idx].card[1];
			WFIFOL(fd,24) = stor->store_item[idx].card[2];
		}
		WFIFOL(fd,28) = stor->store_item[idx].card[3];
	} else {
		if(stor->store_item[idx].card[0] > 0 && (j = itemdb_viewid(stor->store_item[idx].card[0])) > 0)
			WFIFOL(fd,16) = j;
		else
			WFIFOL(fd,16) = stor->store_item[idx].card[0];
		if(stor->store_item[idx].card[1] > 0 && (j = itemdb_viewid(stor->store_item[idx].card[1])) > 0)
			WFIFOL(fd,20) = j;
		else
			WFIFOL(fd,20) = stor->store_item[idx].card[1];
		if(stor->store_item[idx].card[2] > 0 && (j = itemdb_viewid(stor->store_item[idx].card[2])) > 0)
			WFIFOL(fd,24) = j;
		else
			WFIFOL(fd,24)= stor->store_item[idx].card[2];
		if(stor->store_item[idx].card[3] > 0 && (j = itemdb_viewid(stor->store_item[idx].card[3])) > 0)
			WFIFOL(fd,28) = j;
		else
			WFIFOL(fd,28) = stor->store_item[idx].card[3];
	}
	WFIFOW(fd,32) = stor->store_item[idx].opt[0].id;
	WFIFOW(fd,34) = stor->store_item[idx].opt[0].val;
	WFIFOB(fd,36) = 0;
	WFIFOW(fd,37) = stor->store_item[idx].opt[1].id;
	WFIFOW(fd,39) = stor->store_item[idx].opt[1].val;
	WFIFOB(fd,41) = 0;
	WFIFOW(fd,42) = stor->store_item[idx].opt[2].id;
	WFIFOW(fd,44) = stor->store_item[idx].opt[2].val;
	WFIFOB(fd,46) = 0;
	WFIFOW(fd,47) = stor->store_item[idx].opt[3].id;
	WFIFOW(fd,49) = stor->store_item[idx].opt[3].val;
	WFIFOB(fd,51) = 0;
	WFIFOW(fd,52) = stor->store_item[idx].opt[4].id;
	WFIFOW(fd,54) = stor->store_item[idx].opt[4].val;
	WFIFOB(fd,56) = 0;
	WFIFOSET(fd,packet_db[0xa0a].len);
#endif

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_updateguildstorageamount(struct map_session_data *sd, struct guild_storage *stor)
{
	int fd;

	nullpo_retv(sd);
	nullpo_retv(stor);

	fd=sd->fd;
	WFIFOW(fd,0) = 0xf2;
	WFIFOW(fd,2) = stor->storage_amount;
	WFIFOW(fd,4) = MAX_GUILD_STORAGE;
	WFIFOSET(fd,packet_db[0xf2].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_guildstorageitemadded(struct map_session_data *sd, struct guild_storage *stor, int idx, int amount)
{
	struct item_data *id;
	int fd,j;

	nullpo_retv(sd);
	nullpo_retv(stor);

	fd = sd->fd;
	id = itemdb_search(stor->store_item[idx].nameid);

#if PACKETVER < 7
	WFIFOW(fd,0) = 0xf4;
	WFIFOW(fd,2) = idx+1;
	WFIFOL(fd,4) = amount;
	if(id->view_id > 0)
		WFIFOW(fd,8) = id->view_id;
	else
		WFIFOW(fd,8) = stor->store_item[idx].nameid;
	WFIFOB(fd,10) = stor->store_item[idx].identify;
	WFIFOB(fd,11) = stor->store_item[idx].attribute;
	WFIFOB(fd,12) = stor->store_item[idx].refine;
	if(itemdb_isspecial(stor->store_item[idx].card[0])) {
		if(id->flag.pet_egg) {
			WFIFOW(fd,13) = 0;
			WFIFOW(fd,15) = 0;
			WFIFOW(fd,17) = 0;
		} else {
			WFIFOW(fd,13) = stor->store_item[idx].card[0];
			WFIFOW(fd,15) = stor->store_item[idx].card[1];
			WFIFOW(fd,17) = stor->store_item[idx].card[2];
		}
		WFIFOW(fd,19) = stor->store_item[idx].card[3];
	} else {
		if(stor->store_item[idx].card[0] > 0 && (j = itemdb_viewid(stor->store_item[idx].card[0])) > 0)
			WFIFOW(fd,13) = j;
		else
			WFIFOW(fd,13) = stor->store_item[idx].card[0];
		if(stor->store_item[idx].card[1] > 0 && (j = itemdb_viewid(stor->store_item[idx].card[1])) > 0)
			WFIFOW(fd,15) = j;
		else
			WFIFOW(fd,15) = stor->store_item[idx].card[1];
		if(stor->store_item[idx].card[2] > 0 && (j = itemdb_viewid(stor->store_item[idx].card[2])) > 0)
			WFIFOW(fd,17) = j;
		else
			WFIFOW(fd,17) = stor->store_item[idx].card[2];
		if(stor->store_item[idx].card[3] > 0 && (j = itemdb_viewid(stor->store_item[idx].card[3])) > 0)
			WFIFOW(fd,19) = j;
		else
			WFIFOW(fd,19) = stor->store_item[idx].card[3];
	}
	WFIFOSET(fd,packet_db[0xf4].len);
#elif PACKETVER < 20150513
	WFIFOW(fd,0) = 0x1c4;
	WFIFOW(fd,2) = idx+1;
	WFIFOL(fd,4) = amount;
	if(id->view_id > 0)
		WFIFOW(fd,8) = id->view_id;
	else
		WFIFOW(fd,8) = stor->store_item[idx].nameid;
	WFIFOB(fd,10) = id->type;
	WFIFOB(fd,11) = stor->store_item[idx].identify;
	WFIFOB(fd,12) = stor->store_item[idx].attribute;
	WFIFOB(fd,13) = stor->store_item[idx].refine;
	if(itemdb_isspecial(stor->store_item[idx].card[0])) {
		if(id->flag.pet_egg) {
			WFIFOW(fd,14) = 0;
			WFIFOW(fd,16) = 0;
			WFIFOW(fd,18) = 0;
		} else {
			WFIFOW(fd,14) = stor->store_item[idx].card[0];
			WFIFOW(fd,16) = stor->store_item[idx].card[1];
			WFIFOW(fd,18) = stor->store_item[idx].card[2];
		}
		WFIFOW(fd,20) = stor->store_item[idx].card[3];
	} else {
		if(stor->store_item[idx].card[0] > 0 && (j = itemdb_viewid(stor->store_item[idx].card[0])) > 0)
			WFIFOW(fd,14) = j;
		else
			WFIFOW(fd,14) = stor->store_item[idx].card[0];
		if(stor->store_item[idx].card[1] > 0 && (j = itemdb_viewid(stor->store_item[idx].card[1])) > 0)
			WFIFOW(fd,16) = j;
		else
			WFIFOW(fd,16) = stor->store_item[idx].card[1];
		if(stor->store_item[idx].card[2] > 0 && (j = itemdb_viewid(stor->store_item[idx].card[2])) > 0)
			WFIFOW(fd,18) = j;
		else
			WFIFOW(fd,18) = stor->store_item[idx].card[2];
		if(stor->store_item[idx].card[3] > 0 && (j = itemdb_viewid(stor->store_item[idx].card[3])) > 0)
			WFIFOW(fd,20) = j;
		else
			WFIFOW(fd,20) = stor->store_item[idx].card[3];
	}
	WFIFOSET(fd,packet_db[0x1c4].len);
#elif PACKETVER < 20180704
	WFIFOW(fd,0) = 0xa0a;
	WFIFOW(fd,2) = idx+1;
	WFIFOL(fd,4) = amount;
	if(id->view_id > 0)
		WFIFOW(fd,8) = id->view_id;
	else
		WFIFOW(fd,8) = stor->store_item[idx].nameid;
	WFIFOB(fd,10) = id->type;
	WFIFOB(fd,11) = stor->store_item[idx].identify;
	WFIFOB(fd,12) = stor->store_item[idx].attribute;
	WFIFOB(fd,13) = stor->store_item[idx].refine;
	if(itemdb_isspecial(stor->store_item[idx].card[0])) {
		if(id->flag.pet_egg) {
			WFIFOW(fd,14) = 0;
			WFIFOW(fd,16) = 0;
			WFIFOW(fd,18) = 0;
		} else {
			WFIFOW(fd,14) = stor->store_item[idx].card[0];
			WFIFOW(fd,16) = stor->store_item[idx].card[1];
			WFIFOW(fd,18) = stor->store_item[idx].card[2];
		}
		WFIFOW(fd,20) = stor->store_item[idx].card[3];
	} else {
		if(stor->store_item[idx].card[0] > 0 && (j = itemdb_viewid(stor->store_item[idx].card[0])) > 0)
			WFIFOW(fd,14) = j;
		else
			WFIFOW(fd,14) = stor->store_item[idx].card[0];
		if(stor->store_item[idx].card[1] > 0 && (j = itemdb_viewid(stor->store_item[idx].card[1])) > 0)
			WFIFOW(fd,16) = j;
		else
			WFIFOW(fd,16) = stor->store_item[idx].card[1];
		if(stor->store_item[idx].card[2] > 0 && (j = itemdb_viewid(stor->store_item[idx].card[2])) > 0)
			WFIFOW(fd,18) = j;
		else
			WFIFOW(fd,18) = stor->store_item[idx].card[2];
		if(stor->store_item[idx].card[3] > 0 && (j = itemdb_viewid(stor->store_item[idx].card[3])) > 0)
			WFIFOW(fd,20) = j;
		else
			WFIFOW(fd,20) = stor->store_item[idx].card[3];
	}
	WFIFOW(fd,22) = stor->store_item[idx].opt[0].id;
	WFIFOW(fd,24) = stor->store_item[idx].opt[0].val;
	WFIFOB(fd,26) = 0;
	WFIFOW(fd,27) = stor->store_item[idx].opt[1].id;
	WFIFOW(fd,29) = stor->store_item[idx].opt[1].val;
	WFIFOB(fd,31) = 0;
	WFIFOW(fd,32) = stor->store_item[idx].opt[2].id;
	WFIFOW(fd,34) = stor->store_item[idx].opt[2].val;
	WFIFOB(fd,36) = 0;
	WFIFOW(fd,37) = stor->store_item[idx].opt[3].id;
	WFIFOW(fd,39) = stor->store_item[idx].opt[3].val;
	WFIFOB(fd,41) = 0;
	WFIFOW(fd,42) = stor->store_item[idx].opt[4].id;
	WFIFOW(fd,44) = stor->store_item[idx].opt[4].val;
	WFIFOB(fd,46) = 0;
	WFIFOSET(fd,packet_db[0xa0a].len);
#else
	WFIFOW(fd,0) = 0xa0a;
	WFIFOW(fd,2) = idx+1;
	WFIFOL(fd,4) = amount;
	if(id->view_id > 0)
		WFIFOL(fd,8) = id->view_id;
	else
		WFIFOL(fd,8) = stor->store_item[idx].nameid;
	WFIFOB(fd,12) = id->type;
	WFIFOB(fd,13) = stor->store_item[idx].identify;
	WFIFOB(fd,14) = stor->store_item[idx].attribute;
	WFIFOB(fd,15) = stor->store_item[idx].refine;
	if(itemdb_isspecial(stor->store_item[idx].card[0])) {
		if(id->flag.pet_egg) {
			WFIFOL(fd,16) = 0;
			WFIFOL(fd,20) = 0;
			WFIFOL(fd,24) = 0;
		} else {
			WFIFOL(fd,16) = stor->store_item[idx].card[0];
			WFIFOL(fd,20) = stor->store_item[idx].card[1];
			WFIFOL(fd,24) = stor->store_item[idx].card[2];
		}
		WFIFOL(fd,28) = stor->store_item[idx].card[3];
	} else {
		if(stor->store_item[idx].card[0] > 0 && (j = itemdb_viewid(stor->store_item[idx].card[0])) > 0)
			WFIFOL(fd,16) = j;
		else
			WFIFOL(fd,16) = stor->store_item[idx].card[0];
		if(stor->store_item[idx].card[1] > 0 && (j = itemdb_viewid(stor->store_item[idx].card[1])) > 0)
			WFIFOL(fd,20) = j;
		else
			WFIFOL(fd,20) = stor->store_item[idx].card[1];
		if(stor->store_item[idx].card[2] > 0 && (j = itemdb_viewid(stor->store_item[idx].card[2])) > 0)
			WFIFOL(fd,24) = j;
		else
			WFIFOL(fd,24) = stor->store_item[idx].card[2];
		if(stor->store_item[idx].card[3] > 0 && (j = itemdb_viewid(stor->store_item[idx].card[3])) > 0)
			WFIFOL(fd,28) = j;
		else
			WFIFOL(fd,28) = stor->store_item[idx].card[3];
	}
	WFIFOW(fd,32) = stor->store_item[idx].opt[0].id;
	WFIFOW(fd,34) = stor->store_item[idx].opt[0].val;
	WFIFOB(fd,36) = 0;
	WFIFOW(fd,37) = stor->store_item[idx].opt[1].id;
	WFIFOW(fd,39) = stor->store_item[idx].opt[1].val;
	WFIFOB(fd,41) = 0;
	WFIFOW(fd,42) = stor->store_item[idx].opt[2].id;
	WFIFOW(fd,44) = stor->store_item[idx].opt[2].val;
	WFIFOB(fd,46) = 0;
	WFIFOW(fd,47) = stor->store_item[idx].opt[3].id;
	WFIFOW(fd,49) = stor->store_item[idx].opt[3].val;
	WFIFOB(fd,51) = 0;
	WFIFOW(fd,52) = stor->store_item[idx].opt[4].id;
	WFIFOW(fd,54) = stor->store_item[idx].opt[4].val;
	WFIFOB(fd,56) = 0;
	WFIFOSET(fd,packet_db[0xa0a].len);
#endif

	return;
}

/*==========================================
 * �J�v���q�ɂ���A�C�e������苎��
 *------------------------------------------
 */
void clif_storageitemremoved(struct map_session_data *sd, int idx, int amount)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xf6;
	WFIFOW(fd,2)=idx+1;
	WFIFOL(fd,4)=amount;
	WFIFOSET(fd,packet_db[0xf6].len);

	return;
}

/*==========================================
 * �J�v���q�ɂ����
 *------------------------------------------
 */
void clif_storageclose(struct map_session_data *sd)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xf8;
	WFIFOSET(fd,packet_db[0xf8].len);

	return;
}

/*==========================================
 * �ʏ�U���G�t�F�N�g���_���[�W
 *------------------------------------------
 */
void clif_damage(struct block_list *src, struct block_list *dst, unsigned int tick, int sdelay, int ddelay, atn_bignumber damage, int div_, int type, atn_bignumber damage2, int is_spdamage)
{
	unsigned char buf[36];
	struct status_change *sc;

	nullpo_retv(src);
	nullpo_retv(dst);

	sc = status_get_sc(dst);

	if(type != 4 && dst->type == BL_PC) {
		if( ((struct map_session_data *)dst)->special_state.infinite_endure )
			type = 9;
		if( sc && (sc->data[SC_ENDURE].timer != -1 || sc->data[SC_BERSERK].timer != -1) && !map[dst->m].flag.gvg )
			type = 9;
	}
	if(sc && sc->data[SC_HALLUCINATION].timer != -1) {
		damage  = atn_rand() & 0x7fff;
		damage2 = atn_rand() & 0x7fff;
	}

#if PACKETVER < 20071128
	WBUFW(buf,0)=0x8a;
	WBUFL(buf,2)=src->id;
	WBUFL(buf,6)=dst->id;
	WBUFL(buf,10)=tick;
	WBUFL(buf,14)=sdelay;
	WBUFL(buf,18)=ddelay;
	WBUFW(buf,22)=(int)((damage > 0x7fff)? 0x7fff: damage);
	WBUFW(buf,24)=div_;
	WBUFB(buf,26)=type;
	WBUFW(buf,27)=(int)((damage2 > 0x7fff)? 0x7fff: damage2);
	clif_send(buf,packet_db[0x8a].len,src,AREA);
#elif PACKETVER < 20110719
	WBUFW(buf,0)=0x2e1;
	WBUFL(buf,2)=src->id;
	WBUFL(buf,6)=dst->id;
	WBUFL(buf,10)=tick;
	WBUFL(buf,14)=sdelay;
	WBUFL(buf,18)=ddelay;
	WBUFL(buf,22)=BIGNUM2INT(damage);
	WBUFW(buf,26)=div_;
	WBUFB(buf,28)=type;
	WBUFL(buf,29)=BIGNUM2INT(damage2);
	clif_send(buf,packet_db[0x2e1].len,src,AREA);
#else
	WBUFW(buf,0)=0x8c8;
	WBUFL(buf,2)=src->id;
	WBUFL(buf,6)=dst->id;
	WBUFL(buf,10)=tick;
	WBUFL(buf,14)=sdelay;
	WBUFL(buf,18)=ddelay;
	WBUFL(buf,22)=BIGNUM2INT(damage);
	WBUFB(buf,26)=is_spdamage;
	WBUFW(buf,27)=div_;
	WBUFB(buf,29)=type;
	WBUFL(buf,30)=BIGNUM2INT(damage2);
	clif_send(buf,packet_db[0x8c8].len,src,AREA);
#endif

	return;
}

/*==========================================
 * �A�C�e�����E��
 *------------------------------------------
 */
void clif_takeitem(struct block_list* src, int dst_id)
{
	unsigned char buf[32];

	nullpo_retv(src);

	WBUFW(buf, 0) = 0x8a;
	WBUFL(buf, 2) = src->id;
	WBUFL(buf, 6) = dst_id;
	WBUFB(buf,26) = 1;
	clif_send(buf,packet_db[0x8a].len,src,AREA);

	return;
}

/*==========================================
 * PC�\��
 *------------------------------------------
 */
static void clif_getareachar_pc(struct map_session_data* sd,struct map_session_data* dstsd)
{
	nullpo_retv(sd);
	nullpo_retv(dstsd);

	// ���S�ȃC���r�W�u�����[�h�Ȃ瑗�M���Ȃ�
	if(!battle_config.gm_perfect_hide || !pc_isinvisible(dstsd))
	{
		int len;
		if(dstsd->ud.walktimer != -1) {
			len = clif_set007b(dstsd,WFIFOP(sd->fd,0));
			WFIFOSET(sd->fd,len);
		} else {
			len = clif_set0078(dstsd,WFIFOP(sd->fd,0));
			WFIFOSET(sd->fd,len);
		}

		if(dstsd->sc.data[SC_KYOUGAKU].timer != -1)	// ����
			clif_status_change_id(sd,dstsd->bl.id,SI_KYOUGAKU,1,0,MOBID_PORING,0,0);
		else if(dstsd->sc.data[SC_MONSTER_TRANSFORM].timer != -1)	// �����X�^�[�ϐg�V�X�e��
			clif_status_change_id(sd,dstsd->bl.id,SI_MONSTER_TRANSFORM,1,0,dstsd->sc.data[SC_MONSTER_TRANSFORM].val1,0,0);
		else if(dstsd->sc.data[SC_ACTIVE_MONSTER_TRANSFORM].timer != -1)	// �A�N�e�B�u�����X�^�[�ϐg
			clif_status_change_id(sd,dstsd->bl.id,SI_ACTIVE_MONSTER_TRANSFORM,1,0,dstsd->sc.data[SC_ACTIVE_MONSTER_TRANSFORM].val1,0,0);
		else if(dstsd->sc.data[SC_ALL_RIDING].timer != -1)	// ����V�X�e��
			clif_status_change_id(sd,dstsd->bl.id,SI_ALL_RIDING,1,9999,1,25,0);
		if(dstsd->sc.data[SC_ON_PUSH_CART].timer != -1)	// �J�[�g
			clif_status_change_id(sd,dstsd->bl.id,SI_ON_PUSH_CART,1,9999,dstsd->sc.data[SC_ON_PUSH_CART].val1,0,0);
		if(dstsd->sc.data[SC_BANDING].timer != -1)	// �o���f�B���O
			clif_status_change_id(sd,dstsd->bl.id,SI_BANDING,1,9999,dstsd->sc.data[SC_BANDING].val1,0,0);
		if(dstsd->sc.data[SC_HAT_EFFECT].timer != -1)	// �������G�t�F�N�g
			clif_status_change_id(sd,dstsd->bl.id,SI_HAT_EFFECT,1,9999,dstsd->sc.data[SC_HAT_EFFECT].val1,0,0);
		if(dstsd->sc.data[SC_SUHIDE].timer != -1)	// �������
			clif_status_change_id(sd,dstsd->bl.id,SI_SUHIDE,1,9999,dstsd->sc.data[SC_SUHIDE].val1,0,0);
		if(pc_checkskill(dstsd,SU_SPRITEMABLE) > 0)	// �ɂ��
			clif_status_change_id(sd,dstsd->bl.id,SI_SPRITEMABLE,1,9999,1,0,0);
#if PACKETVER >= 20150513
		if(dstsd->hatEffect.count)
			clif_hat_effects(sd,&dstsd->bl,SELF);
#endif
	}

	if(dstsd->chatID) {
		struct chat_data *cd = map_id2cd(dstsd->chatID);
		if(cd && cd->usersd[0]==dstsd)
			clif_dispchat(cd,sd->fd);
	}
	if(dstsd->state.store == STORE_TYPE_VENDING) {
		clif_showvendingboard(&dstsd->bl,dstsd->message,sd->fd);
	}
	if(dstsd->state.store == STORE_TYPE_BUYINGSTORE) {
		clif_show_buyingstore(&dstsd->bl,dstsd->message,sd->fd);
	}

	if(dstsd->spiritball.num > 0) {
		clif_set01e1(sd->fd,dstsd,dstsd->spiritball.num);
	}

	if(dstsd->coin.num > 0) {
		clif_set01e1(sd->fd,dstsd,dstsd->coin.num);
	}

	// �e�T�E�O�̋��̕\��
	if(dstsd->elementball.num > 0) {
		clif_elementball_id(sd->fd,dstsd);
	}

	// �\�E���G�i�W�[�\��
	if(dstsd->soulenergy.num > 0) {
		clif_soulenergy_id(sd->fd,dstsd);
	}

	// ���̕\��
	if(dstsd->ball.num > 0) {
		clif_ball_id(sd->fd,dstsd);
	}

	if(sd->status.manner < 0)
		clif_changestatus(&sd->bl,SP_MANNER,sd->status.manner);
	if(dstsd->view_size != 0)
		clif_misceffect2(&dstsd->bl,422+dstsd->view_size);

	return;
}

/*==========================================
 * NPC�\��
 *------------------------------------------
 */
static void clif_getareachar_npc(struct map_session_data* sd,struct npc_data* nd)
{
	int len;

	nullpo_retv(sd);
	nullpo_retv(nd);

	if(nd->class_ < 0 || (nd->flag&1 && (nd->option&(OPTION_HIDE))==0) || nd->class_ == INVISIBLE_CLASS)
		return;

	if(nd->ud.walktimer != -1) {
		len = clif_npc007b(nd,WFIFOP(sd->fd,0),sd);
	} else {
		len = clif_npc0078(nd,WFIFOP(sd->fd,0),sd);
	}
	WFIFOSET(sd->fd,len);

	if(nd->chat_id){
		clif_dispchat(map_id2cd(nd->chat_id),sd->fd);
	}

	if(nd->view_size!=0)
		clif_misceffect2(&nd->bl,422+nd->view_size);

	return;
}

/*==========================================
 * MOB�\��
 *------------------------------------------
 */
static void clif_getareachar_mob(struct map_session_data* sd, struct mob_data* md)
{
	int len;
	unsigned short offset = 0;

	nullpo_retv(sd);
	nullpo_retv(md);

	if(md->ud.walktimer != -1){
		len = clif_mob007b(md,WFIFOP(sd->fd,0));
#if PACKETVER >= 20180704
		offset = 14;
#elif PACKETVER >= 20131223
		offset = 10;
#elif PACKETVER >= 20120328
		offset = 6;
#endif
	} else {
		len = clif_mob0078(md,WFIFOP(sd->fd,0));
#if PACKETVER >= 20180704
		offset = 8;
#elif PACKETVER >= 20131223
		offset = 4;
#elif PACKETVER >= 20120328
		offset = 0;
#endif
	}
	// �����Ԉُ펞�E�G���y���E���EMVP�����X�^�[�ɂ͕\�����Ȃ�
	if(mob_check_hpinfo(sd,md))
	{
		WFIFOL(sd->fd,65+offset)=0xffffffff;
		WFIFOL(sd->fd,69+offset)=0xffffffff;
	} else {
		WFIFOL(sd->fd,65+offset)=status_get_max_hp(&md->bl);
		WFIFOL(sd->fd,69+offset)=status_get_hp(&md->bl);
	}
	WFIFOSET(sd->fd,len);

	if(md->view_size!=0)
		clif_misceffect2(&md->bl,422+md->view_size);

	return;
}

/*==========================================
 * PET�\��
 *------------------------------------------
 */
static void clif_getareachar_pet(struct map_session_data* sd, struct pet_data* pd)
{
	int len;

	nullpo_retv(sd);
	nullpo_retv(pd);

	if(pd->ud.walktimer != -1){
		len = clif_pet007b(pd,WFIFOP(sd->fd,0));
		WFIFOSET(sd->fd,len);
	} else {
		len = clif_pet0078(pd,WFIFOP(sd->fd,0));
		WFIFOSET(sd->fd,len);
	}

	if(pd->view_size!=0)
		clif_misceffect2(&pd->bl,422+pd->view_size);

	return;
}

/*==========================================
 * HOM�\��
 *------------------------------------------
 */
static void clif_getareachar_hom(struct map_session_data* sd, struct homun_data* hd)
{
	int len;

	nullpo_retv(sd);
	nullpo_retv(hd);

#if 0
	if(hd->ud.walktimer != -1) {
		len = clif_hom007b(hd,WFIFOP(sd->fd,0));
	} else {
		// 0x78���ƍ��W�Y�����N����
		len = clif_hom0078(hd,WFIFOP(sd->fd,0));
	}
#endif

	len = clif_hom007b(hd,WFIFOP(sd->fd,0));
	WFIFOSET(sd->fd,len);

	if(hd->view_size != 0)
		clif_misceffect2(&hd->bl,422+hd->view_size);

	return;
}

/*==========================================
 * MERC�\��
 *------------------------------------------
 */
static void clif_getareachar_merc(struct map_session_data* sd, struct merc_data* mcd)
{
	int len;

	nullpo_retv(sd);
	nullpo_retv(mcd);

#if 0
	if(mcd->ud.walktimer != -1) {
		len = clif_merc007b(mcd,WFIFOP(sd->fd,0));
	} else {
		// 0x78���ƍ��W�Y�����N����
		len = clif_merc0078(mcd,WFIFOP(sd->fd,0));
	}
#endif

	len = clif_merc007b(mcd,WFIFOP(sd->fd,0));
	WFIFOSET(sd->fd,len);

	if(mcd->view_size != 0)
		clif_misceffect2(&mcd->bl,422+mcd->view_size);

	return;
}

/*==========================================
 * ELEM�\��
 *------------------------------------------
 */
static void clif_getareachar_elem(struct map_session_data* sd, struct elem_data* eld)
{
	int len;

	nullpo_retv(sd);
	nullpo_retv(eld);

#if 0
	if(eld->ud.walktimer != -1) {
		len = clif_elem007b(eld,WFIFOP(sd->fd,0));
	} else {
		// 0x78���ƍ��W�Y�����N����
		len = clif_elem0078(eld,WFIFOP(sd->fd,0));
	}
#endif

	len = clif_elem007b(eld,WFIFOP(sd->fd,0));
	WFIFOSET(sd->fd,len);

	if(eld->view_size != 0)
		clif_misceffect2(&eld->bl,422+eld->view_size);

	return;
}

/*==========================================
 * ITEM�\��
 *------------------------------------------
 */
static void clif_getareachar_item(struct map_session_data* sd, struct flooritem_data* fitem)
{
	int view,fd;

	nullpo_retv(sd);
	nullpo_retv(fitem);

	// 009d <ID>.l <item ID>.w <identify flag>.B <X>.w <Y>.w <amount>.w <subX>.B <subY>.B
	fd=sd->fd;
#if PACKETVER < 20180704
	WFIFOW(fd,0)=0x9d;
	WFIFOL(fd,2)=fitem->bl.id;
	if((view = itemdb_viewid(fitem->item_data.nameid)) > 0)
		WFIFOW(fd,6)=view;
	else
		WFIFOW(fd,6)=fitem->item_data.nameid;
	WFIFOB(fd,8)=fitem->item_data.identify;
	WFIFOW(fd,9)=fitem->bl.x;
	WFIFOW(fd,11)=fitem->bl.y;
	WFIFOW(fd,13)=fitem->item_data.amount;
	WFIFOB(fd,15)=fitem->subx;
	WFIFOB(fd,16)=fitem->suby;
	WFIFOSET(fd,packet_db[0x9d].len);
#else
	WFIFOW(fd,0)=0x9d;
	WFIFOL(fd,2)=fitem->bl.id;
	if((view = itemdb_viewid(fitem->item_data.nameid)) > 0)
		WFIFOL(fd,6)=view;
	else
		WFIFOL(fd,6)=fitem->item_data.nameid;
	WFIFOB(fd,10)=fitem->item_data.identify;
	WFIFOW(fd,11)=fitem->bl.x;
	WFIFOW(fd,13)=fitem->bl.y;
	WFIFOW(fd,15)=fitem->item_data.amount;
	WFIFOB(fd,17)=fitem->subx;
	WFIFOB(fd,18)=fitem->suby;
	WFIFOSET(fd,packet_db[0x9d].len);
#endif

	return;
}

/*==========================================
 * �ꏊ�X�L���G�t�F�N�g�����E�ɓ���
 *------------------------------------------
 */
static void clif_getareachar_skillunit(struct map_session_data *sd, struct skill_unit *unit)
{
	int fd;

	nullpo_retv(sd);
	nullpo_retv(unit);

	fd=sd->fd;

#if PACKETVER < 3
	WFIFOW(fd, 0)=0x11f;
	WFIFOL(fd, 2)=unit->bl.id;
	WFIFOL(fd, 6)=unit->group->src_id;
	WFIFOW(fd,10)=unit->bl.x;
	WFIFOW(fd,12)=unit->bl.y;
	if(battle_config.trap_is_invisible && skill_unit_istrap(unit->group->unit_id))
		WFIFOB(fd,14)=UNT_ATTACK_SKILLS;
	else
		WFIFOB(fd,14)=unit->group->unit_id;
	WFIFOB(fd,15)=1;
	WFIFOSET(fd,packet_db[0x11f].len);

	if(unit->group->skill_id == WZ_ICEWALL)
		clif_set0192(fd,unit->bl.m,unit->bl.x,unit->bl.y,5);
#elif PACKETVER < 20110719
	if(unit->group->unit_id == UNT_GRAFFITI) {	// �O���t�B�e�B
		WFIFOW(fd, 0)=0x1c9;
		WFIFOL(fd, 2)=unit->bl.id;
		WFIFOL(fd, 6)=unit->group->src_id;
		WFIFOW(fd,10)=unit->bl.x;
		WFIFOW(fd,12)=unit->bl.y;
		WFIFOB(fd,14)=unit->group->unit_id;
		WFIFOB(fd,15)=1;
		WFIFOB(fd,16)=1;
		memcpy(WFIFOP(fd,17),unit->group->valstr,80);
		WFIFOSET(fd,packet_db[0x1c9].len);
	} else {
		WFIFOW(fd, 0)=0x11f;
		WFIFOL(fd, 2)=unit->bl.id;
		WFIFOL(fd, 6)=unit->group->src_id;
		WFIFOW(fd,10)=unit->bl.x;
		WFIFOW(fd,12)=unit->bl.y;
		if(battle_config.trap_is_invisible && skill_unit_istrap(unit->group->unit_id))
			WFIFOB(fd,14)=UNT_ATTACK_SKILLS;
		else
			WFIFOB(fd,14)=unit->group->unit_id;
		WFIFOB(fd,15)=1;
		WFIFOSET(fd,packet_db[0x11f].len);

		if(unit->group->skill_id == WZ_ICEWALL)
			clif_set0192(fd,unit->bl.m,unit->bl.x,unit->bl.y,5);
	}
#elif PACKETVER < 20120925
	if(unit->group->unit_id == UNT_GRAFFITI) {	// �O���t�B�e�B
		WFIFOW(fd, 0)=0x1c9;
		WFIFOL(fd, 2)=unit->bl.id;
		WFIFOL(fd, 6)=unit->group->src_id;
		WFIFOW(fd,10)=unit->bl.x;
		WFIFOW(fd,12)=unit->bl.y;
		WFIFOB(fd,14)=unit->group->unit_id;
		WFIFOB(fd,15)=1;
		WFIFOB(fd,16)=1;
		memcpy(WFIFOP(fd,17),unit->group->valstr,80);
		WFIFOSET(fd,packet_db[0x1c9].len);
	} else {
		WFIFOW(fd, 0)=0x8c7;
		WFIFOW(fd, 2)=19;
		WFIFOL(fd, 4)=unit->bl.id;
		WFIFOL(fd, 8)=unit->group->src_id;
		WFIFOW(fd,12)=unit->bl.x;
		WFIFOW(fd,14)=unit->bl.y;
		if(battle_config.trap_is_invisible && skill_unit_istrap(unit->group->unit_id))
			WFIFOB(fd,16)=UNT_ATTACK_SKILLS;
		else
			WFIFOB(fd,16)=unit->group->unit_id;
		WFIFOB(fd,17)=skill_get_unit_range(unit->group->skill_id,unit->group->skill_lv);
		WFIFOB(fd,18)=1;
		WFIFOSET(fd,WFIFOW(fd,2));

		if(unit->group->skill_id == WZ_ICEWALL)
			clif_set0192(fd,unit->bl.m,unit->bl.x,unit->bl.y,5);
	}
#elif PACKETVER < 20130731
	if(unit->group->unit_id == UNT_GRAFFITI) {	// �O���t�B�e�B
		WFIFOW(fd, 0)=0x1c9;
		WFIFOL(fd, 2)=unit->bl.id;
		WFIFOL(fd, 6)=unit->group->src_id;
		WFIFOW(fd,10)=unit->bl.x;
		WFIFOW(fd,12)=unit->bl.y;
		WFIFOB(fd,14)=unit->group->unit_id;
		WFIFOB(fd,15)=1;
		WFIFOB(fd,16)=1;
		memcpy(WFIFOP(fd,17),unit->group->valstr,80);
		WFIFOSET(fd,packet_db[0x1c9].len);
	} else {
		WFIFOW(fd, 0)=0x99f;
		WFIFOW(fd, 2)=22;
		WFIFOL(fd, 4)=unit->bl.id;
		WFIFOL(fd, 8)=unit->group->src_id;
		WFIFOW(fd,12)=unit->bl.x;
		WFIFOW(fd,14)=unit->bl.y;
		if(battle_config.trap_is_invisible && skill_unit_istrap(unit->group->unit_id))
			WFIFOL(fd,16)=UNT_ATTACK_SKILLS;
		else
			WFIFOL(fd,16)=unit->group->unit_id;
		WFIFOB(fd,20)=skill_get_unit_range(unit->group->skill_id,unit->group->skill_lv);
		WFIFOB(fd,21)=1;
		WFIFOSET(fd,WFIFOW(fd,2));

		if(unit->group->skill_id == WZ_ICEWALL)
			clif_set0192(fd,unit->bl.m,unit->bl.x,unit->bl.y,5);
	}
#else
	if(unit->group->unit_id == UNT_GRAFFITI) {	// �O���t�B�e�B
		WFIFOW(fd, 0)=0x1c9;
		WFIFOL(fd, 2)=unit->bl.id;
		WFIFOL(fd, 6)=unit->group->src_id;
		WFIFOW(fd,10)=unit->bl.x;
		WFIFOW(fd,12)=unit->bl.y;
		WFIFOB(fd,14)=unit->group->unit_id;
		WFIFOB(fd,15)=1;
		WFIFOB(fd,16)=1;
		memcpy(WFIFOP(fd,17),unit->group->valstr,80);
		WFIFOSET(fd,packet_db[0x1c9].len);
	} else {
		WFIFOW(fd, 0)=0x9ca;
		WFIFOW(fd, 2)=23;
		WFIFOL(fd, 4)=unit->bl.id;
		WFIFOL(fd, 8)=unit->group->src_id;
		WFIFOW(fd,12)=unit->bl.x;
		WFIFOW(fd,14)=unit->bl.y;
		if(battle_config.trap_is_invisible && skill_unit_istrap(unit->group->unit_id))
			WFIFOL(fd,16)=UNT_ATTACK_SKILLS;
		else
			WFIFOL(fd,16)=unit->group->unit_id;
		WFIFOB(fd,20)=skill_get_unit_range(unit->group->skill_id,unit->group->skill_lv);
		WFIFOB(fd,21)=1;
		WFIFOB(fd,22)=(unsigned char)unit->group->skill_lv;
		WFIFOSET(fd,WFIFOW(fd,2));

		if(unit->group->skill_id == WZ_ICEWALL)
			clif_set0192(fd,unit->bl.m,unit->bl.x,unit->bl.y,5);
	}
#endif

	return;
}

/*==========================================
 * �ꏊ�X�L���G�t�F�N�g�����E���������
 *------------------------------------------
 */
static void clif_clearchar_skillunit(struct skill_unit *unit, int fd)
{
	nullpo_retv(unit);

	WFIFOW(fd, 0)=0x120;
	WFIFOL(fd, 2)=unit->bl.id;
	WFIFOSET(fd,packet_db[0x120].len);

	if(unit->group->skill_id == WZ_ICEWALL)
		clif_set0192(fd,unit->bl.m,unit->bl.x,unit->bl.y,unit->val2);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_01ac(struct block_list *bl)
{
	unsigned char buf[8];

	nullpo_retv(bl);

	WBUFW(buf, 0) = 0x1ac;
	WBUFL(buf, 2) = bl->id;
	clif_send(buf,packet_db[0x1ac].len,bl,AREA);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static int clif_getareachar(struct block_list* bl, va_list ap)
{
	struct map_session_data *sd;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, sd = va_arg(ap,struct map_session_data*));

	switch(bl->type) {
	case BL_PC:
		if(&sd->bl != bl)
			clif_getareachar_pc(sd,(struct map_session_data *)bl);
		break;
	case BL_NPC:
		clif_getareachar_npc(sd,(struct npc_data *)bl);
		break;
	case BL_MOB:
		clif_getareachar_mob(sd,(struct mob_data *)bl);
		break;
	case BL_PET:
		clif_getareachar_pet(sd,(struct pet_data *)bl);
		break;
	case BL_ITEM:
		clif_getareachar_item(sd,(struct flooritem_data *)bl);
		break;
	case BL_SKILL:
		clif_getareachar_skillunit(sd,(struct skill_unit *)bl);
		break;
	case BL_HOM:
		clif_getareachar_hom(sd,(struct homun_data *)bl);
		break;
	case BL_MERC:
		clif_getareachar_merc(sd,(struct merc_data *)bl);
		break;
	case BL_ELEM:
		clif_getareachar_elem(sd,(struct elem_data *)bl);
		break;
	default:
		if(battle_config.error_log)
			printf("get area char ??? %d\n",bl->type);
		break;
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int clif_pcoutsight(struct block_list *bl,va_list ap)
{
	struct map_session_data *sd, *dstsd;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, sd = va_arg(ap,struct map_session_data*));

	switch(bl->type) {
	case BL_PC:
		dstsd = (struct map_session_data *)bl;
		if(dstsd && sd != dstsd) {
			clif_clearchar_id(dstsd->bl.id,0,sd->fd);
			clif_clearchar_id(sd->bl.id,0,dstsd->fd);
			if(dstsd->chatID) {
				struct chat_data *cd = map_id2cd(dstsd->chatID);
				if(cd && cd->usersd[0] == dstsd)
					clif_dispchat(cd,sd->fd);
			}
			if(dstsd->state.store == STORE_TYPE_VENDING) {
				clif_closevendingboard(&dstsd->bl,sd->fd);
			}
			if(dstsd->state.store == STORE_TYPE_BUYINGSTORE) {
				clif_close_buyingstore(&dstsd->bl,sd->fd);
			}
		}
		break;
	case BL_NPC:
		if( ((struct npc_data *)bl)->class_ != INVISIBLE_CLASS )
			clif_clearchar_id(bl->id,0,sd->fd);
		break;
	case BL_MOB:
	case BL_PET:
	case BL_HOM:
	case BL_MERC:
	case BL_ELEM:
		clif_clearchar_id(bl->id,0,sd->fd);
		break;
	case BL_ITEM:
		clif_clearflooritem((struct flooritem_data *)bl,sd->fd);
		break;
	case BL_SKILL:
		clif_clearchar_skillunit((struct skill_unit *)bl,sd->fd);
		break;
	}

	return 0;
}

/*==========================================
 * ����
 *------------------------------------------
 */
int clif_pcinsight(struct block_list *bl,va_list ap)
{
	struct map_session_data *sd, *dstsd;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, sd = va_arg(ap,struct map_session_data*));

	switch(bl->type) {
	case BL_PC:
		dstsd = (struct map_session_data *)bl;
		if(sd != dstsd) {
			clif_getareachar_pc(sd,dstsd);
			clif_getareachar_pc(dstsd,sd);
		}
		break;
	case BL_NPC:
		clif_getareachar_npc(sd,(struct npc_data *)bl);
		break;
	case BL_MOB:
		clif_getareachar_mob(sd,(struct mob_data *)bl);
		break;
	case BL_PET:
		clif_getareachar_pet(sd,(struct pet_data *)bl);
		break;
	case BL_ITEM:
		clif_getareachar_item(sd,(struct flooritem_data *)bl);
		break;
	case BL_SKILL:
		clif_getareachar_skillunit(sd,(struct skill_unit *)bl);
		break;
	case BL_HOM:
		clif_getareachar_hom(sd,(struct homun_data *)bl);
		break;
	case BL_MERC:
		clif_getareachar_merc(sd,(struct merc_data *)bl);
		break;
	case BL_ELEM:
		clif_getareachar_elem(sd,(struct elem_data *)bl);
		break;
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int clif_mobinsight(struct block_list *bl,va_list ap)
{
	struct map_session_data *sd;
	struct mob_data *md;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, md = va_arg(ap,struct mob_data*));
	nullpo_retr(0, sd = (struct map_session_data *)bl);

	clif_getareachar_mob(sd,md);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int clif_moboutsight(struct block_list *bl,va_list ap)
{
	struct map_session_data *sd;
	struct mob_data *md;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, md = va_arg(ap,struct mob_data*));
	nullpo_retr(0, sd = (struct map_session_data *)bl);

	clif_clearchar_id(md->bl.id,0,sd->fd);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int clif_petinsight(struct block_list *bl,va_list ap)
{
	struct map_session_data *sd;
	struct pet_data *pd;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, pd = va_arg(ap,struct pet_data*));
	nullpo_retr(0, sd = (struct map_session_data *)bl);

	clif_getareachar_pet(sd,pd);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int clif_petoutsight(struct block_list *bl,va_list ap)
{
	struct map_session_data *sd;
	struct pet_data *pd;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, pd = va_arg(ap,struct pet_data*));
	nullpo_retr(0, sd = (struct map_session_data *)bl);

	clif_clearchar_id(pd->bl.id,0,sd->fd);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int clif_hominsight(struct block_list *bl,va_list ap)
{
	struct map_session_data *sd;
	struct homun_data *hd;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, hd = va_arg(ap,struct homun_data*));
	nullpo_retr(0, sd = (struct map_session_data *)bl);

	clif_getareachar_hom(sd,hd);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int clif_homoutsight(struct block_list *bl,va_list ap)
{
	struct map_session_data *sd;
	struct homun_data *hd;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, hd = va_arg(ap,struct homun_data*));
	nullpo_retr(0, sd = (struct map_session_data *)bl);

	clif_clearchar_id(hd->bl.id,0,sd->fd);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int clif_mercinsight(struct block_list *bl,va_list ap)
{
	struct map_session_data *sd;
	struct merc_data *mcd;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, mcd = va_arg(ap,struct merc_data*));
	nullpo_retr(0, sd = (struct map_session_data *)bl);

	clif_getareachar_merc(sd,mcd);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int clif_mercoutsight(struct block_list *bl,va_list ap)
{
	struct map_session_data *sd;
	struct merc_data *mcd;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, mcd = va_arg(ap,struct merc_data*));
	nullpo_retr(0, sd = (struct map_session_data *)bl);

	clif_clearchar_id(mcd->bl.id,0,sd->fd);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int clif_eleminsight(struct block_list *bl,va_list ap)
{
	struct map_session_data *sd;
	struct elem_data *eld;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, eld = va_arg(ap,struct elem_data*));
	nullpo_retr(0, sd = (struct map_session_data *)bl);

	clif_getareachar_elem(sd,eld);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int clif_elemoutsight(struct block_list *bl,va_list ap)
{
	struct map_session_data *sd;
	struct elem_data *eld;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, eld = va_arg(ap,struct elem_data*));
	nullpo_retr(0, sd = (struct map_session_data *)bl);

	clif_clearchar_id(eld->bl.id,0,sd->fd);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int clif_npcinsight(struct block_list *bl,va_list ap)
{
	struct map_session_data *sd;
	struct npc_data *nd;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, nd = va_arg(ap,struct npc_data*));
	nullpo_retr(0, sd = (struct map_session_data *)bl);

	clif_getareachar_npc(sd,nd);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int clif_npcoutsight(struct block_list *bl,va_list ap)
{
	struct map_session_data *sd;
	struct npc_data *nd;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, nd = va_arg(ap,struct npc_data*));
	nullpo_retr(0, sd = (struct map_session_data *)bl);

	clif_clearchar_id(nd->bl.id,0,sd->fd);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_skillinfo(struct map_session_data *sd, int skillid, int type, int range)
{
	int fd,id=0,skill_lv;
	int tk_ranker_bonus = 0;

	nullpo_retv(sd);

	if( skillid < MAX_PCSKILL && skillid!=sd->skill_clone.id && (id=sd->status.skill[skillid].id) <= 0 )
		return;
	if( skillid >= HOM_SKILLID && skillid <= MAX_HOM_SKILLID && !sd->hd )
		return;

	if(sd->status.class_==PC_CLASS_TK && pc_checkskill2(sd,TK_MISSION)>0 && sd->status.base_level>=90 &&
			sd->status.skill_point==0 && ranking_get_pc_rank(sd,RK_TAEKWON)>0)
		tk_ranker_bonus=1;

	if( skillid >= HOM_SKILLID && skillid <= MAX_HOM_SKILLID && sd->hd ) {
		id = skillid;
		skill_lv = sd->hd->status.skill[skillid - HOM_SKILLID].lv;
	}
	else if(tk_ranker_bonus && sd->status.skill[skillid].flag == 0)
		skill_lv = pc_get_skilltree_max(&sd->s_class,id);
	else if(skillid==sd->skill_clone.id){
		id = skillid;
		skill_lv = sd->status.skill[skillid].lv>sd->skill_clone.lv?sd->status.skill[skillid].lv:sd->skill_clone.lv;
	}else
		skill_lv = sd->status.skill[skillid].lv;

	fd=sd->fd;
	WFIFOW(fd,0)=0x147;
	WFIFOW(fd,2) = id;
	if(type < 0)
		WFIFOL(fd,4) = skill_get_inf(id);
	else
		WFIFOL(fd,4) = type;
	WFIFOW(fd,8) = skill_lv;
	WFIFOW(fd,10) = skill_get_sp(id,skill_lv);
	if(range < 0)
		WFIFOW(fd,12)= skill_get_fixed_range(&sd->bl,id,skill_lv);
	else
		WFIFOW(fd,12)= range;
	memset(WFIFOP(fd,14),0,24);
	if(!(skill_get_inf2(id)&INF2_QUEST) || battle_config.quest_skill_learn == 1 || (battle_config.gm_allskill > 0 && pc_isGM(sd) >= battle_config.gm_allskill) )
		WFIFOB(fd,38) = (skill_lv < pc_get_skilltree_max(&sd->s_class,id) && skillid!=sd->skill_clone.id && sd->status.skill[skillid].flag == 0)? 1: 0;
	else
		WFIFOB(fd,38) = 0;
	WFIFOSET(fd,packet_db[0x147].len);

	return;
}

/*==========================================
 * �X�L�����X�g�𑗐M����
 * 16KB���߂ɔ�����WFIFORESERVE����
 *------------------------------------------
 */
void clif_skillinfoblock(struct map_session_data *sd)
{
	unsigned char buf[4+37*MAX_PCSKILL];
	int fd;
	int i,len=4,id,skill_lv,tk_ranker_bonus=0;

	nullpo_retv(sd);

	if(sd->status.class_==PC_CLASS_TK && pc_checkskill2(sd,TK_MISSION)>0 && sd->status.base_level>=90 &&
			sd->status.skill_point==0 && ranking_get_pc_rank(sd,RK_TAEKWON)>0)
		tk_ranker_bonus=1;

	fd=sd->fd;
	WBUFW(buf,0)=0x10f;
	for (i=0; i < MAX_PCSKILL; i++){
		if( (i==sd->skill_clone.id && (id=sd->skill_clone.id)!=0) || (i==sd->skill_reproduce.id && (id=sd->skill_reproduce.id)!=0) || (id=sd->status.skill[i].id)!=0 ){
			WBUFW(buf,len  ) = id;
			WBUFL(buf,len+2) = skill_get_inf(id);
			if(tk_ranker_bonus && sd->status.skill[i].flag==0)
				skill_lv = pc_get_skilltree_max(&sd->s_class,id);
			else if(i==sd->skill_clone.id)
				skill_lv = (sd->status.skill[i].lv > sd->skill_clone.lv)? sd->status.skill[i].lv: sd->skill_clone.lv;
			else if(i==sd->skill_reproduce.id)
				skill_lv = (sd->status.skill[i].lv > sd->skill_reproduce.lv)? sd->status.skill[i].lv: sd->skill_reproduce.lv;
			else
				skill_lv = sd->status.skill[i].lv;
			WBUFW(buf,len+6) = skill_lv;
			WBUFW(buf,len+8) = skill_get_sp(id,skill_lv);
			WBUFW(buf,len+10)= skill_get_fixed_range(&sd->bl,id,skill_lv);
			memset(WBUFP(buf,len+12),0,24);
			if(!(skill_get_inf2(id)&INF2_QUEST) || battle_config.quest_skill_learn == 1 || (battle_config.gm_allskill > 0 && pc_isGM(sd) >= battle_config.gm_allskill) )
				WBUFB(buf,len+36) = (skill_lv < pc_get_skilltree_max(&sd->s_class,id) && i!=sd->skill_clone.id && i!=sd->skill_reproduce.id && sd->status.skill[i].flag == 0)? 1: 0;
			else
				WBUFB(buf,len+36) = 0;
			len+=37;
		}
	}
	WBUFW(buf,2)=len;
	WFIFORESERVE(fd,len);
	memcpy(WFIFOP(fd,0), WBUFP(buf,0), len);
	WFIFOSET(fd,len);

	return;
}

/*==========================================
 * �X�L���ǉ�
 *------------------------------------------
 */
void clif_addskill(struct map_session_data *sd, int skill_num)
{
	int fd, skill_lv;

	nullpo_retv(sd);

	fd = sd->fd;
	if (!fd) return;

	if (sd->status.skill[skill_num].id <= 0)
		return;

	skill_lv = sd->status.skill[skill_num].lv;

	WFIFOW(fd,0) = 0x111;
	WFIFOW(fd,2) = skill_num;
	WFIFOL(fd,4) = skill_get_inf(skill_num);
	WFIFOW(fd,8) = skill_lv;
	if (skill_lv > 0) {
		WFIFOW(fd,10) = skill_get_sp(skill_num, skill_lv);
		WFIFOW(fd,12) = skill_get_range(skill_num, skill_lv);
	} else {
		WFIFOW(fd,10) = 0;
		WFIFOW(fd,12) = 0;
	}
	memset(WFIFOP(fd,14),0,24);
	if (sd->status.skill[skill_num].flag == 0)
		WFIFOB(fd,38) = (skill_lv < pc_get_skilltree_max(&sd->s_class,skill_num))? 1: 0;
	else
		WFIFOB(fd,38) = 0;
	WFIFOSET(fd,packet_db[0x111].len);
}

/*==========================================
 * �X�L���폜
 *------------------------------------------
 */
void clif_delskill(struct map_session_data *sd, int skill_num)
{
#if PACKETVER >= 20081217
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;

	WFIFOW(fd,0) = 0x441;
	WFIFOW(fd,2) = skill_num;
	WFIFOSET(fd,packet_db[0x441].len);
#endif
	clif_skillinfoblock(sd);
}

/*==========================================
 * �X�L������U��ʒm
 *------------------------------------------
 */
void clif_skillup(struct map_session_data *sd, int skill_num)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;

#if PACKETVER < 20090715
	WFIFOW(fd,0) = 0x10e;
	WFIFOW(fd,2) = skill_num;
	WFIFOW(fd,4) = sd->status.skill[skill_num].lv;
	WFIFOW(fd,6) = skill_get_sp(skill_num,sd->status.skill[skill_num].lv);
	WFIFOW(fd,8) = skill_get_fixed_range(&sd->bl,skill_num,sd->status.skill[skill_num].lv);
	WFIFOB(fd,10) = (sd->status.skill[skill_num].lv < pc_get_skilltree_max(&sd->s_class,sd->status.skill[skill_num].id))? 1: 0;
	WFIFOSET(fd,packet_db[0x10e].len);
#else
	WFIFOW(fd,0) = 0x7e1;
	WFIFOW(fd,2) = skill_num;
	WFIFOL(fd,4) = skill_get_inf(skill_num);
	WFIFOW(fd,8) = sd->status.skill[skill_num].lv;
	WFIFOW(fd,10) = skill_get_sp(skill_num,sd->status.skill[skill_num].lv);
	WFIFOW(fd,12) = skill_get_fixed_range(&sd->bl,skill_num,sd->status.skill[skill_num].lv);
	WFIFOB(fd,14) = (sd->status.skill[skill_num].lv < pc_get_skilltree_max(&sd->s_class,sd->status.skill[skill_num].id))? 1: 0;
	WFIFOSET(fd,packet_db[0x7e1].len);
#endif

	return;
}

/*==========================================
 * �X�L���r���G�t�F�N�g�𑗐M����
 *------------------------------------------
 */
void clif_skillcasting(struct block_list* bl,int src_id,int dst_id,int dst_x,int dst_y,int skill_num,int casttime)
{
	unsigned char buf[28];

#if PACKETVER < 20091118
	WBUFW(buf,0) = 0x13e;
	WBUFL(buf,2) = src_id;
	WBUFL(buf,6) = dst_id;
	WBUFW(buf,10) = dst_x;
	WBUFW(buf,12) = dst_y;
	WBUFW(buf,14) = skill_num;
	WBUFL(buf,16) = skill_get_pl(skill_num);	// ����
	WBUFL(buf,20) = casttime;
	clif_send(buf,packet_db[0x13e].len, bl, AREA);
#elif PACKETVER < 20181212
	WBUFW(buf,0) = 0x7fb;
	WBUFL(buf,2) = src_id;
	WBUFL(buf,6) = dst_id;
	WBUFW(buf,10) = dst_x;
	WBUFW(buf,12) = dst_y;
	WBUFW(buf,14) = skill_num;
	WBUFL(buf,16) = skill_get_pl(skill_num);	// ����
	WBUFL(buf,20) = casttime;
	WBUFB(buf,24) = 0;
	clif_send(buf,packet_db[0x7fb].len, bl, AREA);
#else
	WBUFW(buf,0) = 0xb1a;
	WBUFL(buf,2) = src_id;
	WBUFL(buf,6) = dst_id;
	WBUFW(buf,10) = dst_x;
	WBUFW(buf,12) = dst_y;
	WBUFW(buf,14) = skill_num;
	WBUFL(buf,16) = skill_get_pl(skill_num);	// ����
	WBUFL(buf,20) = casttime;
	WBUFB(buf,24) = 0;
	WBUFL(buf,25) = 0;
	clif_send(buf,packet_db[0xb1a].len, bl, AREA);
#endif
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_skillcastcancel(struct block_list* bl)
{
	unsigned char buf[8];

	nullpo_retv(bl);

	WBUFW(buf,0) = 0x1b9;
	WBUFL(buf,2) = bl->id;
	clif_send(buf,packet_db[0x1b9].len, bl, AREA);

	return;
}

/*==========================================
 * �X�L���g�p���s
 *------------------------------------------
 */
void clif_skill_fail(struct map_session_data *sd, int skill_id, int type, int btype, int val)
{
	int fd;

	nullpo_retv(sd);

	if(type==0x4 && battle_config.display_delay_skill_fail==0)
		return;

	fd=sd->fd;
#if PACKETVER < 20180704
	WFIFOW(fd,0) = 0x110;
	WFIFOW(fd,2) = skill_id;
	WFIFOW(fd,4) = btype;
	WFIFOW(fd,6) = val;
	WFIFOB(fd,8) = 0;
	WFIFOB(fd,9) = type;
	WFIFOSET(fd,packet_db[0x110].len);
#else
	WFIFOW(fd,0) = 0x110;
	WFIFOW(fd,2) = skill_id;
	WFIFOL(fd,4) = btype;
	WFIFOL(fd,8) = val;
	WFIFOB(fd,12) = 0;
	WFIFOB(fd,13) = type;
	WFIFOSET(fd,packet_db[0x110].len);
#endif

	return;
}

/*==========================================
 * �X�L���U���G�t�F�N�g���_���[�W
 *------------------------------------------
 */
void clif_skill_damage(struct block_list *src,struct block_list *dst,
	unsigned int tick,int sdelay,int ddelay,atn_bignumber damage,int div_,int skill_id,int skill_lv,int type)
{
	unsigned char buf[36];
	struct status_change *sc;

	nullpo_retv(src);
	nullpo_retv(dst);

	sc = status_get_sc(dst);

	if(type != 5 && dst->type == BL_PC && ((struct map_session_data *)dst)->special_state.infinite_endure)
		type = 9;
	if(sc) {
		if(type != 5 && (sc->data[SC_ENDURE].timer != -1 || sc->data[SC_BERSERK].timer != -1))
			type = 9;
		if(sc->data[SC_HALLUCINATION].timer != -1)
			damage = atn_rand() & 0x7fff;
	}

#if PACKETVER < 3
	WBUFW(buf,0)=0x114;
	WBUFW(buf,2)=skill_id;
	WBUFL(buf,4)=src->id;
	WBUFL(buf,8)=dst->id;
	WBUFL(buf,12)=tick;
	WBUFL(buf,16)=sdelay;
	WBUFL(buf,20)=ddelay;
	WBUFW(buf,24)=(int)((damage > 0x7fff)? 0x7fff: damage);
	WBUFW(buf,26)=skill_lv;
	WBUFW(buf,28)=div_;
	WBUFB(buf,30)=(type>0)?type:skill_get_hit(skill_id);
	clif_send(buf,packet_db[0x114].len,src,AREA);
#else
	WBUFW(buf,0)=0x1de;
	WBUFW(buf,2)=skill_id;
	WBUFL(buf,4)=src->id;
	WBUFL(buf,8)=dst->id;
	WBUFL(buf,12)=tick;
	WBUFL(buf,16)=sdelay;
	WBUFL(buf,20)=ddelay;
	WBUFL(buf,24)=BIGNUM2INT(damage);
	WBUFW(buf,28)=skill_lv;
	WBUFW(buf,30)=div_;
	WBUFB(buf,32)=(type>0)?type:skill_get_hit(skill_id);
	clif_send(buf,packet_db[0x1de].len,src,AREA);
#endif

	return;
}

/*==========================================
 * ������΂��X�L���U���G�t�F�N�g���_���[�W
 *------------------------------------------
 */
/*void clif_skill_damage2(struct block_list *src,struct block_list *dst,
	unsigned int tick,int sdelay,int ddelay,int damage,int div,int skill_id,int skill_lv,int type)
{
	unsigned char buf[36];
	struct status_change *sc;

	nullpo_retr(0, src);
	nullpo_retr(0, dst);

	sc = status_get_sc(dst);

	if(type != 5 && dst->type == BL_PC && ((struct map_session_data *)dst)->special_state.infinite_endure)
		type = 9;
	if(sc) {
		if(type != 5 && (sc->data[SC_ENDURE].timer != -1 || sc->data[SC_BERSERK].timer != -1))
			type = 9;
		if(sc->data[SC_HALLUCINATION].timer != -1)
			damage = atn_rand() & 0x7fff;
	}

	WBUFW(buf,0)=0x115;
	WBUFW(buf,2)=skill_id;
	WBUFL(buf,4)=src->id;
	WBUFL(buf,8)=dst->id;
	WBUFL(buf,12)=tick;
	WBUFL(buf,16)=sdelay;
	WBUFL(buf,20)=ddelay;
	WBUFW(buf,24)=dst->x;
	WBUFW(buf,26)=dst->y;
	WBUFW(buf,28)=damage;
	WBUFW(buf,30)=skill_lv;
	WBUFW(buf,32)=div;
	WBUFB(buf,34)=(type>0)?type:skill_get_hit(skill_id);
	clif_send(buf,packet_db[0x115].len,src,AREA);

	return;
}*/

/*==========================================
 * �x��/�񕜃X�L���G�t�F�N�g
 *------------------------------------------
 */
void clif_skill_nodamage(struct block_list *src,struct block_list *dst,int skill_id,int heal,int fail)
{
	unsigned char buf[18];

	nullpo_retv(src);
	nullpo_retv(dst);

#if PACKETVER < 20130731
	if(heal > 0x7fff && skill_id != NPC_SELFDESTRUCTION && skill_id != NPC_SELFDESTRUCTION2)
		heal=0x7fff;

	WBUFW(buf,0)=0x11a;
	WBUFW(buf,2)=skill_id;
	WBUFW(buf,4)=heal;
	WBUFL(buf,6)=dst->id;
	WBUFL(buf,10)=src->id;
	WBUFB(buf,14)=fail;
	clif_send(buf,packet_db[0x11a].len,src,AREA);
#else
	WBUFW(buf,0)=0x9cb;
	WBUFW(buf,2)=skill_id;
	WBUFL(buf,4)=heal;
	WBUFL(buf,8)=dst->id;
	WBUFL(buf,12)=src->id;
	WBUFB(buf,16)=fail;
	clif_send(buf,packet_db[0x9cb].len,src,AREA);
#endif

	return;
}

/*==========================================
 * �ꏊ�X�L���G�t�F�N�g
 *------------------------------------------
 */
void clif_skill_poseffect(struct block_list *src,int skill_id,int val,int x,int y,unsigned int tick)
{
	unsigned char buf[24];

	nullpo_retv(src);

	WBUFW(buf,0)=0x117;
	WBUFW(buf,2)=skill_id;
	WBUFL(buf,4)=src->id;
	WBUFW(buf,8)=val;
	WBUFW(buf,10)=x;
	WBUFW(buf,12)=y;
	WBUFL(buf,14)=tick;
	clif_send(buf,packet_db[0x117].len,src,AREA);

	return;
}

/*==========================================
 * �ꏊ�X�L���G�t�F�N�g�\��
 *------------------------------------------
 */
void clif_skill_setunit(struct skill_unit *unit)
{
	unsigned char buf[128];

	nullpo_retv(unit);

#if PACKETVER < 3
	WBUFW(buf, 0)=0x11f;
	WBUFL(buf, 2)=unit->bl.id;
	WBUFL(buf, 6)=unit->group->src_id;
	WBUFW(buf,10)=unit->bl.x;
	WBUFW(buf,12)=unit->bl.y;
	if(battle_config.trap_is_invisible && skill_unit_istrap(unit->group->unit_id))
		WBUFB(buf,14)=UNT_ATTACK_SKILLS;
	else
		WBUFB(buf,14)=unit->group->unit_id;
	WBUFB(buf,15)=1;
	clif_send(buf,packet_db[0x11f].len,&unit->bl,AREA);
#elif PACKETVER < 20110719
	if(unit->group->unit_id == UNT_GRAFFITI) {	// �O���t�B�e�B
		WBUFW(buf, 0)=0x1c9;
		WBUFL(buf, 2)=unit->bl.id;
		WBUFL(buf, 6)=unit->group->src_id;
		WBUFW(buf,10)=unit->bl.x;
		WBUFW(buf,12)=unit->bl.y;
		WBUFB(buf,14)=unit->group->unit_id;
		WBUFB(buf,15)=1;
		WBUFB(buf,16)=1;
		memcpy(WBUFP(buf,17),unit->group->valstr,80);
		clif_send(buf,packet_db[0x1c9].len,&unit->bl,AREA);
	} else {
		WBUFW(buf, 0)=0x11f;
		WBUFL(buf, 2)=unit->bl.id;
		WBUFL(buf, 6)=unit->group->src_id;
		WBUFW(buf,10)=unit->bl.x;
		WBUFW(buf,12)=unit->bl.y;
		if(battle_config.trap_is_invisible && skill_unit_istrap(unit->group->unit_id))
			WBUFB(buf,14)=UNT_ATTACK_SKILLS;
		else
			WBUFB(buf,14)=unit->group->unit_id;
		WBUFB(buf,15)=1;
		clif_send(buf,packet_db[0x11f].len,&unit->bl,AREA);
	}
#elif PACKETVER < 20120925
	if(unit->group->unit_id == UNT_GRAFFITI) {	// �O���t�B�e�B
		WBUFW(buf, 0)=0x1c9;
		WBUFL(buf, 2)=unit->bl.id;
		WBUFL(buf, 6)=unit->group->src_id;
		WBUFW(buf,10)=unit->bl.x;
		WBUFW(buf,12)=unit->bl.y;
		WBUFB(buf,14)=unit->group->unit_id;
		WBUFB(buf,15)=1;
		WBUFB(buf,16)=1;
		memcpy(WBUFP(buf,17),unit->group->valstr,80);
		clif_send(buf,packet_db[0x1c9].len,&unit->bl,AREA);
	} else {
		struct block_list *src = map_id2bl(unit->group->src_id);

		WBUFW(buf, 0)=0x8c7;
		WBUFW(buf, 2)=19;
		WBUFL(buf, 4)=unit->bl.id;
		WBUFL(buf, 8)=unit->group->src_id;
		WBUFW(buf,12)=unit->bl.x;
		WBUFW(buf,14)=unit->bl.y;
		if(battle_config.trap_is_invisible && skill_unit_istrap(unit->group->unit_id))
			WBUFB(buf,16)=UNT_ATTACK_SKILLS;
		else
			WBUFB(buf,16)=unit->group->unit_id;
		if(src && src->type == BL_PC) {
			struct map_session_data *sd = (struct map_session_data *)src;

			WBUFB(buf,17)= pc_checkskill(sd,WL_RADIUS);
		} else {
			WBUFB(buf,17)=0;
		}
		WBUFB(buf,18)=1;
		clif_send(buf,WBUFW(buf,2),&unit->bl,AREA);
	}
#elif PACKETVER < 20130731
	if(unit->group->unit_id == UNT_GRAFFITI) {	// �O���t�B�e�B
		WBUFW(buf, 0)=0x1c9;
		WBUFL(buf, 2)=unit->bl.id;
		WBUFL(buf, 6)=unit->group->src_id;
		WBUFW(buf,10)=unit->bl.x;
		WBUFW(buf,12)=unit->bl.y;
		WBUFB(buf,14)=unit->group->unit_id;
		WBUFB(buf,15)=1;
		WBUFB(buf,16)=1;
		memcpy(WBUFP(buf,17),unit->group->valstr,80);
		clif_send(buf,packet_db[0x1c9].len,&unit->bl,AREA);
	} else {
		struct block_list *src = map_id2bl(unit->group->src_id);

		WBUFW(buf, 0)=0x99f;
		WBUFW(buf, 2)=22;
		WBUFL(buf, 4)=unit->bl.id;
		WBUFL(buf, 8)=unit->group->src_id;
		WBUFW(buf,12)=unit->bl.x;
		WBUFW(buf,14)=unit->bl.y;
		if(battle_config.trap_is_invisible && skill_unit_istrap(unit->group->unit_id))
			WBUFL(buf,16)=UNT_ATTACK_SKILLS;
		else
			WBUFL(buf,16)=unit->group->unit_id;
		if(src && src->type == BL_PC) {
			struct map_session_data *sd = (struct map_session_data *)src;

			WBUFB(buf,20)= pc_checkskill(sd,WL_RADIUS);
		} else {
			WBUFB(buf,20)=0;
		}
		WBUFB(buf,21)=1;
		clif_send(buf,WBUFW(buf,2),&unit->bl,AREA);
	}
#else
	if(unit->group->unit_id == UNT_GRAFFITI) {	// �O���t�B�e�B
		WBUFW(buf, 0)=0x1c9;
		WBUFL(buf, 2)=unit->bl.id;
		WBUFL(buf, 6)=unit->group->src_id;
		WBUFW(buf,10)=unit->bl.x;
		WBUFW(buf,12)=unit->bl.y;
		WBUFB(buf,14)=unit->group->unit_id;
		WBUFB(buf,15)=1;
		WBUFB(buf,16)=1;
		memcpy(WBUFP(buf,17),unit->group->valstr,80);
		clif_send(buf,packet_db[0x1c9].len,&unit->bl,AREA);
	} else {
		struct block_list *src = map_id2bl(unit->group->src_id);

		WBUFW(buf, 0)=0x9ca;
		WBUFW(buf, 2)=23;
		WBUFL(buf, 4)=unit->bl.id;
		WBUFL(buf, 8)=unit->group->src_id;
		WBUFW(buf,12)=unit->bl.x;
		WBUFW(buf,14)=unit->bl.y;
		if(battle_config.trap_is_invisible && skill_unit_istrap(unit->group->unit_id))
			WBUFL(buf,16)=UNT_ATTACK_SKILLS;
		else
			WBUFL(buf,16)=unit->group->unit_id;
		if(src && src->type == BL_PC) {
			struct map_session_data *sd = (struct map_session_data *)src;

			WBUFB(buf,20)= pc_checkskill(sd,WL_RADIUS);
		} else {
			WBUFB(buf,20)=0;
		}
		WBUFB(buf,21)=1;
		WBUFB(buf,22)=(unsigned char)unit->group->skill_lv;
		clif_send(buf,WBUFW(buf,2),&unit->bl,AREA);
	}
#endif

	return;
}

/*==========================================
 * �ꏊ�X�L���G�t�F�N�g�폜
 *------------------------------------------
 */
void clif_skill_delunit(struct skill_unit *unit)
{
	unsigned char buf[8];

	nullpo_retv(unit);

	WBUFW(buf, 0)=0x120;
	WBUFL(buf, 2)=unit->bl.id;
	clif_send(buf,packet_db[0x120].len,&unit->bl,AREA);

	return;
}

/*==========================================
 * ��@�̈�x���\��
 *------------------------------------------
 */
void clif_skillscale(struct block_list *bl, int src_id, int x, int y, int skill_num, int skill_lv, int casttime)
{
#if PACKETVER >= 20151223
	unsigned char buf[20];

	nullpo_retv(bl);

	WBUFW(buf, 0) = 0xa41;
	WBUFL(buf, 2) = src_id;
	WBUFW(buf, 6) = skill_num;
	WBUFW(buf, 8) = skill_lv;
	WBUFW(buf, 10) = x;
	WBUFW(buf, 12) = y;
	WBUFL(buf, 14) = casttime;
	clif_send(buf,packet_db[0xa41].len, bl, AREA);
#endif
	return;
}

/*==========================================
 * ���[�v�ꏊ�I��
 *------------------------------------------
 */
void clif_skill_warppoint(struct map_session_data *sd,int skill_num,
	const char *map1,const char *map2,const char *map3,const char *map4)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x11c;
	WFIFOW(fd,2)=skill_num;
	strncpy(WFIFOP(fd, 4),map1,16);
	strncpy(WFIFOP(fd,20),map2,16);
	strncpy(WFIFOP(fd,36),map3,16);
	strncpy(WFIFOP(fd,52),map4,16);
	WFIFOSET(fd,packet_db[0x11c].len);

	return;
}

/*==========================================
 * ��������
 *------------------------------------------
 */
void clif_skill_memo(struct map_session_data *sd, unsigned char flag)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x11e;
	WFIFOB(fd,2)=flag;
	WFIFOSET(fd,packet_db[0x11e].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_skill_teleportmessage(struct map_session_data *sd, unsigned short flag)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x189;
	WFIFOW(fd,2)=flag;
	WFIFOSET(fd,packet_db[0x189].len);

	return;
}

/*==========================================
 * �����X�^�[���
 *------------------------------------------
 */
void clif_skill_estimation(struct map_session_data *sd, struct block_list *bl)
{
	unsigned char buf[32];
	struct mob_data *md;
	int i;

	nullpo_retv(sd);
	nullpo_retv(bl);

	if(bl->type != BL_MOB || (md = (struct mob_data *)bl) == NULL)
		return;

	WBUFW(buf, 0)=0x18c;
	WBUFW(buf, 2)=mob_get_viewclass(md->class_);
	WBUFW(buf, 4)=mobdb_search(md->class_)->lv;
	WBUFW(buf, 6)=mobdb_search(md->class_)->size;
	WBUFL(buf, 8)=md->hp;
#ifdef PRE_RENEWAL
	WBUFW(buf,12)=status_get_def2(&md->bl);
#else
	WBUFW(buf,12)=status_get_def(&md->bl);
#endif
	WBUFW(buf,14)=mobdb_search(md->class_)->race;
#ifdef PRE_RENEWAL
	WBUFW(buf,16)=status_get_mdef2(&md->bl) - (mobdb_search(md->class_)->vit>>1);
#else
	WBUFW(buf,16)=status_get_mdef(&md->bl);
#endif
	WBUFW(buf,18)=status_get_elem_type(&md->bl);
	for(i=0; i<9 && i<ELE_MAX-1; i++)
		WBUFB(buf,20+i) = (unsigned char)battle_attr_fix(100,i+1,md->def_ele);
	for( ; i<9; i++)
		WBUFB(buf,20+i) = 100;	// ELE_MAX��10��菬�����ꍇ

	if(sd->status.party_id>0) {
		clif_send(buf,packet_db[0x18c].len,&sd->bl,PARTY_AREA);
	} else {
		memcpy(WFIFOP(sd->fd,0),buf,packet_db[0x18c].len);
		WFIFOSET(sd->fd,packet_db[0x18c].len);
	}

	return;
}

/*==========================================
 * �A�C�e�������\���X�g
 *------------------------------------------
 */
void clif_skill_produce_mix_list(struct map_session_data *sd, int trigger, int skillid, int skilllv)
{
	int i,c,view,fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd, 0)=0x18d;

#if PACKETVER < 20180704
	for(i=0,c=0;i<MAX_SKILL_PRODUCE_DB;i++){
		if( skill_can_produce_mix(sd,i,trigger) ){
			if((view = itemdb_viewid(skill_produce_db[i].nameid)) > 0)
				WFIFOW(fd,c*8+ 4) = view;
			else
				WFIFOW(fd,c*8+ 4) = skill_produce_db[i].nameid;
			WFIFOW(fd,c*8+ 6) = 0x0012;
			WFIFOL(fd,c*8+ 8) = sd->status.char_id;
			c++;
		}
	}
	WFIFOW(fd, 2)=c*8+4;
#else
	for(i=0,c=0;i<MAX_SKILL_PRODUCE_DB;i++){
		if( skill_can_produce_mix(sd,i,trigger) ){
			if((view = itemdb_viewid(skill_produce_db[i].nameid)) > 0)
				WFIFOL(fd,c*16+ 4) = view;
			else
				WFIFOL(fd,c*16+ 4) = skill_produce_db[i].nameid;
			WFIFOL(fd,c*16+ 8) = 0;
			WFIFOL(fd,c*16+12) = 0;
			WFIFOL(fd,c*16+16) = 0;
			c++;
		}
	}
	WFIFOW(fd, 2)=c*16+4;
#endif
	WFIFOSET(fd,WFIFOW(fd,2));

	if(c > 0) {
		sd->skill_menu.id = skillid;
		sd->skill_menu.lv = skilllv;
	}

	return;
}

/*==========================================
 * �������X�g
 *------------------------------------------
 */
void clif_making_list(struct map_session_data *sd, int trigger, int skillid, int skilllv, int type)
{
	int i,c,view,fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd, 0)=0x25a;
	WFIFOW(fd, 4)=type;

#if PACKETVER < 20180704
	for(i=0,c=0;i<MAX_SKILL_PRODUCE_DB;i++){
		if( skill_can_produce_mix(sd,i,trigger) ){
			if((view = itemdb_viewid(skill_produce_db[i].nameid)) > 0)
				WFIFOW(fd,c*2+ 6)= view;
			else
				WFIFOW(fd,c*2+ 6)= skill_produce_db[i].nameid;
			c++;
		}
	}

	if(c > 0) {
		WFIFOW(fd, 2)=c*2+6;
		WFIFOSET(fd,WFIFOW(fd,2));
#else
	for(i=0,c=0;i<MAX_SKILL_PRODUCE_DB;i++){
		if( skill_can_produce_mix(sd,i,trigger) ){
			if((view = itemdb_viewid(skill_produce_db[i].nameid)) > 0)
				WFIFOL(fd,c*4+ 6)= view;
			else
				WFIFOL(fd,c*4+ 6)= skill_produce_db[i].nameid;
			c++;
		}
	}

	if(c > 0) {
		WFIFOW(fd, 2)=c*4+6;
		WFIFOSET(fd,WFIFOW(fd,2));
#endif

		sd->skill_menu.id = skillid;
		sd->skill_menu.lv = skilllv;
	}
	else if(skillid != 1) {
		clif_skill_message(sd, skillid, 1573);	// �ޗ������݂��܂���B
	}

	return;
}

/*==========================================
 * ��Ԉُ�A�C�R��/���b�Z�[�W�\���i�S�́j
 *------------------------------------------
 */
void clif_status_load(struct block_list *bl, int type, unsigned char flag)
{
	unsigned char buf[10];

	nullpo_retv(bl);

	WBUFW(buf,0)=0x196;
	WBUFW(buf,2)=type;
	WBUFL(buf,4)=bl->id;
	WBUFB(buf,8)=flag;
	clif_send(buf,packet_db[0x196].len,bl,AREA);

	return;
}

/*==========================================
 * ��Ԉُ�A�C�R��/���b�Z�[�W�\��
 *------------------------------------------
 */
void clif_status_load_id(struct map_session_data *sd, int type, unsigned char flag)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x196;
	WFIFOW(fd,2)=type;
	WFIFOL(fd,4)=sd->bl.id;
	WFIFOB(fd,8)=flag;
	WFIFOSET(fd,packet_db[0x196].len);

	return;
}

/*==========================================
 * ��Ԉُ�A�C�R��/���b�Z�[�W�\���i�S�́j
 *------------------------------------------
 */
void clif_status_change(struct block_list *bl, int type, unsigned char flag, unsigned int tick, int val1, int val2, int val3)
{
	unsigned char buf[32];

	nullpo_retv(bl);

	switch(type) {
		case SI_BLANK:
		case SI_MAXIMIZEPOWER:
		case SI_RIDING:
		case SI_FALCON:
		case SI_TRICKDEAD:
		case SI_BREAKARMOR:
		case SI_BREAKWEAPON:
		case SI_WEIGHT50:
		case SI_WEIGHT90:
		case SI_TENSIONRELAX:
		case SI_ELEMENTFIELD:
		case SI_AUTOBERSERK:
		case SI_RUN_STOP:
		case SI_READYSTORM:
		case SI_READYDOWN:
		case SI_READYTURN:
		case SI_READYCOUNTER:
		case SI_LUNARSTANCE:
		case SI_UNIVERSESTANCE:
		case SI_SUNSTANCE:
		case SI_STARSTANCE:
		case SI_DODGE:
		case SI_DEVIL:
		case SI_MIRACLE:
		case SI_TIGEREYE:
			tick = 0;
			break;
	}

#if PACKETVER < 20081126
	WBUFW(buf,0)=0x196;
	WBUFW(buf,2)=type;
	WBUFL(buf,4)=bl->id;
	WBUFB(buf,8)=flag;
	clif_send(buf,packet_db[0x196].len,bl,AREA);
#elif PACKETVER < 20120618
	WBUFW(buf,0)=0x43f;
	WBUFW(buf,2)=type;
	WBUFL(buf,4)=bl->id;
	WBUFB(buf,8)=flag;
	WBUFL(buf,9)=tick;
	WBUFL(buf,13)=val1;
	WBUFL(buf,17)=val2;
	WBUFL(buf,21)=val3;
	clif_send(buf,packet_db[0x43f].len,bl,AREA);
#else
	WBUFW(buf,0)=0x983;
	WBUFW(buf,2)=type;
	WBUFL(buf,4)=bl->id;
	WBUFB(buf,8)=flag;
	WBUFL(buf,9)=tick;	// �ő厝������
	WBUFL(buf,13)=tick;
	WBUFL(buf,17)=val1;
	WBUFL(buf,21)=val2;
	WBUFL(buf,25)=val3;
	clif_send(buf,packet_db[0x983].len,bl,AREA);
#endif

	return;
}

/*==========================================
 * ��Ԉُ�A�C�R��/���b�Z�[�W�\��
 *------------------------------------------
 */
void clif_status_change_id(struct map_session_data *sd, int id, int type, unsigned char flag, unsigned int tick, int val1, int val2, int val3)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
#if PACKETVER < 20120618
	WFIFOW(fd,0)=0x43f;
	WFIFOW(fd,2)=type;
	WFIFOL(fd,4)=id;
	WFIFOB(fd,8)=flag;
	WFIFOL(fd,9)=tick;
	WFIFOL(fd,13)=val1;
	WFIFOL(fd,17)=val2;
	WFIFOL(fd,21)=val3;
	WFIFOSET(fd,packet_db[0x43f].len);
#else
	WFIFOW(fd,0)=0x983;
	WFIFOW(fd,2)=type;
	WFIFOL(fd,4)=id;
	WFIFOB(fd,8)=flag;
	WFIFOL(fd,9)=tick;	// �ő厝������
	WFIFOL(fd,13)=tick;
	WFIFOL(fd,17)=val1;
	WFIFOL(fd,21)=val2;
	WFIFOL(fd,25)=val3;
	WFIFOSET(fd,packet_db[0x983].len);
#endif

	return;
}

/*==========================================
 * ��Ԉُ�G�t�F�N�g�\���i�S�́j
 *------------------------------------------
 */
void clif_seteffect_enter(struct block_list *bl, int type, unsigned int tick, int val1, int val2, int val3)
{
	unsigned char buf[32];

	nullpo_retv(bl);

#if PACKETVER < 20111102
	WBUFW(buf,0)=0x43f;
	WBUFW(buf,2)=type;
	WBUFL(buf,4)=bl->id;
	WBUFB(buf,8)=1;
	WBUFL(buf,9)=tick;
	WBUFL(buf,13)=val1;
	WBUFL(buf,17)=val2;
	WBUFL(buf,21)=val3;
	clif_send(buf,packet_db[0x43f].len,bl,AREA);
#elif PACKETVER < 20120618
	WBUFW(buf,0)=0x8ff;
	WBUFL(buf,2)=bl->id;
	WBUFW(buf,6)=type;
	WBUFL(buf,8)=tick;
	WBUFL(buf,12)=val1;
	WBUFL(buf,16)=val2;
	WBUFL(buf,20)=val3;
	clif_send(buf,packet_db[0x8ff].len,bl,AREA);
#else
	WBUFW(buf,0)=0x984;
	WBUFL(buf,2)=bl->id;
	WBUFW(buf,6)=type;
	WBUFL(buf,8)=tick;	// �ő厝������
	WBUFL(buf,12)=tick;
	WBUFL(buf,16)=val1;
	WBUFL(buf,20)=val2;
	WBUFL(buf,24)=val3;
	clif_send(buf,packet_db[0x984].len,bl,AREA);
#endif

	return;
}

/*==========================================
 * ���b�Z�[�W�\��
 *------------------------------------------
 */
void clif_displaymessage(const int fd, const char* mes)
{
	size_t len = strlen(mes)+1;

	WFIFOW(fd,0)=0x8e;
	WFIFOW(fd,2)=(unsigned short)(4+len);
	strncpy(WFIFOP(fd,4),mes,len);
	WFIFOSET(fd,WFIFOW(fd,2));

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_disp_onlyself(const int fd, const char *mes)
{
	size_t len = strlen(mes)+1;

	WFIFOW(fd,0)=0x17f;
	WFIFOW(fd,2)=(unsigned short)(4+len);
	memcpy(WFIFOP(fd,4),mes,len);
	WFIFOSET(fd,WFIFOW(fd,2));

	return;
}

/*==========================================
 * �V�̐��𑗐M����
 *------------------------------------------
 */
void clif_GMmessage(struct block_list *bl, const char* mes, size_t len, unsigned int flag)
{
	unsigned char *buf = (unsigned char *)aMalloc(len+8);
	int lp = (flag&0x30)? 8: 4;

	WBUFW(buf,0) = 0x9a;
	WBUFW(buf,2) = (unsigned short)(len+lp);
	if(flag&0x80)
		memcpy(WBUFP(buf,4), "micc", 4);
	else if(flag&0x40)
		memcpy(WBUFP(buf,4), "tool", 4);
	else if(flag&0x20)
		memcpy(WBUFP(buf,4), "ssss", 4);
	else if(flag&0x10)
		memcpy(WBUFP(buf,4), "blue", 4);
	memcpy(WBUFP(buf,lp), mes, len);
	flag&=0x07;
	clif_send(buf, WBUFW(buf,2), bl,
		(flag==1)? ALL_SAMEMAP:
		(flag==2)? AREA:
		(flag==3)? SELF:
		ALL_CLIENT);
	aFree(buf);

	return;
}

/*==========================================
 * �O���[�o�����b�Z�[�W
 *------------------------------------------
 */
void clif_GlobalMessage(struct block_list *bl, const char *message, int target)
{
	unsigned char buf[256];
	size_t len;

	nullpo_retv(bl);

	if(message == NULL)
		return;

	len = strlen(message)+1;
	if(len > sizeof(buf) - 8)
		len = sizeof(buf) - 8;

	WBUFW(buf,0) = 0x8d;
	WBUFW(buf,2) = (unsigned short)(len+8);
	WBUFL(buf,4) = bl->id;
	strncpy(WBUFP(buf,8), message, len);
	clif_send(buf, WBUFW(buf,2), bl, target);

	return;
}

/*==========================================
 * �O���[�o�����b�Z�[�W�i�Ώێw��j
 *------------------------------------------
 */
void clif_GlobalMessage_id(struct block_list *bl, int id, const char *message, int target)
{
	unsigned char buf[256];
	size_t len;

	nullpo_retv(bl);

	if(message == NULL)
		return;

	len = strlen(message)+1;
	if(len > sizeof(buf) - 8)
		len = sizeof(buf) - 8;

	WBUFW(buf,0) = 0x8d;
	WBUFW(buf,2) = (unsigned short)(len+8);
	WBUFL(buf,4) = id;
	strncpy(WBUFP(buf,8), message, len);
	clif_send(buf, WBUFW(buf,2), bl, target);

	return;
}

/*==========================================
 * �O���[�o�����b�Z�[�W�i�}���`�J���[�j
 *------------------------------------------
 */
void clif_GlobalMessage2(struct block_list *bl, unsigned int color, const char* mes, size_t len, int target)
{
	unsigned char buf[256];

	nullpo_retv(bl);

	if(mes == NULL)
		return;

	color = (color & 0x0000FF) << 16 | (color & 0x00FF00) | (color & 0xFF0000) >> 16;

	if(len > sizeof(buf) - 12)
		len = sizeof(buf) - 12;

	WBUFW(buf,0) = 0x2c1;
	WBUFW(buf,2) = (unsigned short)(len+12);
	WBUFL(buf,4) = bl->id;
	WBUFL(buf,8) = color;
	memcpy(WBUFP(buf,12), mes, len);
	clif_send(buf, WBUFW(buf,2), bl, target);

	return;
}

/*==========================================
 * �O���[�o�����b�Z�[�W�i�v���C���[�j
 *------------------------------------------
 */
void clif_disp_overhead(struct map_session_data *sd, const char* mes)
{
	unsigned char buf[256];
	size_t len;

	nullpo_retv(sd);

	if(mes == NULL)
		return;

	len = strlen(mes)+1;
	if(len > sizeof(buf) - 8)
		len = sizeof(buf) - 8;

	WBUFW(buf,0) = 0x8d;
	WBUFW(buf,2) = (unsigned short)(len + 8);
	WBUFL(buf,4) = sd->bl.id;
	memcpy(WBUFP(buf,8), mes, len);
	clif_send(WBUFP(buf,0), WBUFW(buf,2), &sd->bl, sd->chatID ? CHAT_WOS : AREA_CHAT_WOC);

	WBUFW(buf,0) = 0x8e;
	WBUFW(buf,2) = (unsigned short)(len + 4);
	memcpy(WBUFP(buf,4), mes, len);
	clif_send(buf, WBUFW(buf,2), &sd->bl, SELF);

	return;
}

/*==========================================
 * �V�̐��i�}���`�J���[�j�𑗐M
 *------------------------------------------
 */
void clif_announce(struct block_list *bl, const char* mes, size_t len, unsigned int color, int type, int size, int align, int pos_y, unsigned int flag)
{
	unsigned char *buf = (unsigned char *)aMalloc(len+16);

	WBUFW(buf,0) = 0x1c3;
	WBUFW(buf,2) = (unsigned short)(len+16);
	WBUFL(buf,4) = color;
	WBUFW(buf,8) = type;
	WBUFW(buf,10) = size;
	WBUFW(buf,12) = align;
	WBUFW(buf,14) = pos_y;
	memcpy(WBUFP(buf,16), mes, len);

	flag &= 0x07;
	clif_send(buf, WBUFW(buf,2), bl,
	          (flag == 1) ? ALL_SAMEMAP:
	          (flag == 2) ? AREA:
	          (flag == 3) ? SELF:
	          ALL_CLIENT);
	aFree(buf);

	return;
}

/*==========================================
 * HPSP�񕜃G�t�F�N�g�𑗐M����
 *------------------------------------------
 */
void clif_heal(int fd, int type, int val)
{
#if PACKETVER < 20141022
	WFIFOW(fd,0)=0x13d;
	WFIFOW(fd,2)=type;
	WFIFOW(fd,4)=val;
	WFIFOSET(fd,packet_db[0x13d].len);
#else
	WFIFOW(fd,0)=0xa27;
	WFIFOW(fd,2)=type;
	WFIFOL(fd,4)=val;
	WFIFOSET(fd,packet_db[0xa27].len);
#endif

	return;
}

/*==========================================
 * ��������
 *------------------------------------------
 */
void clif_resurrection(struct block_list *bl, unsigned short type)
{
	unsigned char buf[8];

	nullpo_retv(bl);

	WBUFW(buf,0)=0x148;
	WBUFL(buf,2)=bl->id;
	WBUFW(buf,6)=type;
	clif_send(buf,packet_db[0x148].len,bl,(type == 1) ? AREA : AREA_WOS);

	return;
}

/*==========================================
 * PvP�EGvG����
 *------------------------------------------
 */
void clif_set0199(int fd, unsigned short type)
{
	WFIFOW(fd,0)=0x199;
	WFIFOW(fd,2)=type;
	WFIFOSET(fd,packet_db[0x199].len);

	return;
}

/*==========================================
 * PvP�EGvG�����iMAP�S�́j
 *------------------------------------------
 */
void clif_send0199(int m, unsigned short type)
{
	struct block_list bl;
	unsigned char buf[4];

	memset(&bl,0,sizeof(bl));
	bl.m = m;

	WBUFW(buf,0)=0x199;
	WBUFW(buf,2)=type;
	clif_send(buf,packet_db[0x199].len,&bl,ALL_SAMEMAP);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_mapproperty(struct map_session_data *sd)
{
	int fd;

	nullpo_retv(sd);

	fd = sd->fd;
#if PACKETVER < 20120925
	WFIFOW(fd,0) = 0x2e7;
	WFIFOW(fd,2) = 33;
	WFIFOW(fd,4) = map_getmaptype(sd->bl.m);
	WFIFOB(fd,6) = (map[sd->bl.m].flag.pk)? 0x1: 0;
	WFIFOB(fd,7) = (map[sd->bl.m].flag.noteleport)? 0: 0x1;
	WFIFOB(fd,8) = (map[sd->bl.m].flag.nomemo)? 0: 0x1;
	WFIFOB(fd,9) = (map[sd->bl.m].flag.pvp_nightmaredrop)? 0x1: 0;
	WFIFOB(fd,10) = (map[sd->bl.m].flag.nopenalty)? 0: 0x1;
	WFIFOB(fd,11) = (map[sd->bl.m].flag.nosave)? 0x1: 0;
	WFIFOB(fd,12) = (map[sd->bl.m].flag.nobranch)? 0x1: 0;	// 0
	WFIFOB(fd,13) = (map[sd->bl.m].flag.pvp_noparty)? 0x1: 0;
	WFIFOB(fd,14) = (map[sd->bl.m].flag.pvp_noguild)? 0x1: 0;
	WFIFOB(fd,15) = (map[sd->bl.m].flag.gvg)? 0x1: 0;
	WFIFOB(fd,16) = 0;	// pk server
	WFIFOB(fd,17) = 0;	// pvp server
	WFIFOB(fd,18) = (map[sd->bl.m].flag.noskill)? 0x1: 0;
	WFIFOB(fd,19) = (map[sd->bl.m].flag.turbo)? 0x1: 0;
	WFIFOB(fd,20) = (map[sd->bl.m].flag.noreturn)? 0x1: 0;
	WFIFOB(fd,21) = (map[sd->bl.m].flag.gvg)? 0x1: 0;	// simple effect
	WFIFOB(fd,22) = (map[sd->bl.m].flag.gvg)? 0x1: 0;	// disable lockon
	WFIFOB(fd,23) = (map[sd->bl.m].flag.pvp)? 0x1: 0;	// count pk
	WFIFOB(fd,24) = 0;	// no party formation
	WFIFOB(fd,25) = 0;	// battle field
	WFIFOB(fd,26) = (map[sd->bl.m].flag.nocostume)? 0x1: 0;	// disable costume item
	WFIFOB(fd,27) = 0;	// prevent party make
	WFIFOB(fd,28) = 0;	// prevent party join
	WFIFOB(fd,29) = 0;	// prevent party reave
	WFIFOB(fd,30) = 0;	// prevent party expel
	WFIFOB(fd,31) = 1;	// show hp bar
	WFIFOB(fd,32) = 0;	// prevent party master change
	WFIFOSET(fd,WFIFOW(fd,2));
#else
	WFIFOW(fd,0) = 0x99b;
	WFIFOW(fd,2) = map_getmaptype(sd->bl.m);
	WFIFOB(fd,4) = 0 | ((map[sd->bl.m].flag.gvg)?0x1c:0) | ((map[sd->bl.m].flag.pvp)?0x20:0);
	WFIFOB(fd,5) = 0x6;
	WFIFOW(fd,6) = 0;
	WFIFOSET(fd,packet_db[0x99b].len);
#endif

	return;
}

/*==========================================
 * PVP����
 *------------------------------------------
 */
void clif_pvpset(struct map_session_data *sd, int pvprank, int pvpnum, char type)
{
	nullpo_retv(sd);

	if(type == 2) {
		int fd = sd->fd;

		WFIFOW(fd,0)  = 0x19a;
		WFIFOL(fd,2)  = sd->bl.id;
		WFIFOL(fd,6)  = pvprank;
		WFIFOL(fd,10) = pvpnum;
		WFIFOSET(fd,packet_db[0x19a].len);
	} else {
		unsigned char buf[16];

		WBUFW(buf,0) = 0x19a;
		WBUFL(buf,2) = sd->bl.id;
		if(sd->sc.option&(OPTION_HIDE | OPTION_CLOAKING | OPTION_SPECIALHIDING))
			WBUFL(buf,6) = 0xffffffff;
		else
			WBUFL(buf,6) = pvprank;
		WBUFL(buf,10) = pvpnum;
		clif_send(buf,packet_db[0x19a].len,&sd->bl,(type == 0) ? SELF : ALL_SAMEMAP);
	}

	return;
}

/*==========================================
 * ���B�G�t�F�N�g�𑗐M����
 *------------------------------------------
 */
void clif_refine(int fd, unsigned short fail, int idx, int val)
{
	WFIFOW(fd,0)=0x188;
	WFIFOW(fd,2)=fail;
	WFIFOW(fd,4)=idx+2;
	WFIFOW(fd,6)=val;
	WFIFOSET(fd,packet_db[0x188].len);

	return;
}

/*==========================================
 * Wis�𑗐M����
 *------------------------------------------
 */
void clif_wis_message(int fd, const char *nick, const char *mes, size_t mes_len, int gmlevel, int ccade)
{
#if PACKETVER <  20091104
	WFIFOW(fd,0)=0x97;
	WFIFOW(fd,2)=(unsigned short)(mes_len + 28);
	memcpy(WFIFOP(fd,4),nick,24);
	memcpy(WFIFOP(fd,28),mes,mes_len);
	WFIFOSET(fd,WFIFOW(fd,2));
#elif PACKETVER < 20131223
	WFIFOW(fd,0)=0x97;
	WFIFOW(fd,2)=(unsigned short)(mes_len + 32);
	memcpy(WFIFOP(fd,4),nick,24);
	WFIFOL(fd,28)=gmlevel;
	memcpy(WFIFOP(fd,32),mes,mes_len);
	WFIFOSET(fd,WFIFOW(fd,2));
#else
	WFIFOW(fd,0)=0x9de;
	WFIFOW(fd,2)=(unsigned short)(mes_len + 33);
	WFIFOL(fd,4)=ccade;
	memcpy(WFIFOP(fd,8),nick,24);
	WFIFOB(fd,32)=(unsigned char)gmlevel;
	memcpy(WFIFOP(fd,33),mes,mes_len);
	WFIFOSET(fd,WFIFOW(fd,2));
#endif

	return;
}

/*==========================================
 * Wis�̑��M���ʂ𑗐M����
 *------------------------------------------
 */
void clif_wis_end(int fd, unsigned char flag, int ccade)
{
#if PACKETVER < 20131223
	WFIFOW(fd,0)=0x98;
	WFIFOB(fd,2)=flag;
	WFIFOSET(fd,packet_db[0x98].len);
#else
	WFIFOW(fd,0)=0x9df;
	WFIFOB(fd,2)=flag;
	WFIFOL(fd,3)=ccade;
	WFIFOSET(fd,packet_db[0x9df].len);
#endif

	return;
}

/*==========================================
 * �L����ID���O�������ʂ𑗐M����
 *------------------------------------------
 */
void clif_solved_charname(struct map_session_data *sd, int char_id)
{
	char *p;

	nullpo_retv(sd);

	p = map_charid2nick(char_id);
	if(p!=NULL){
		int fd=sd->fd;
#if PACKETVER < 20180221
		WFIFOW(fd,0)=0x194;
		WFIFOL(fd,2)=char_id;
		memcpy(WFIFOP(fd,6), p, 24);
		WFIFOSET(fd,packet_db[0x194].len);
#else
		WFIFOW(fd,0)=0xaf7;
		WFIFOW(fd,2)=p[0]? 3 : 2;
		WFIFOL(fd,4)=char_id;
		memcpy(WFIFOP(fd,8), p, 24);
		WFIFOSET(fd,packet_db[0xaf7].len);
#endif
	}else{
		map_reqchariddb(sd,char_id,1);
		chrif_searchcharid(char_id);
	}

	return;
}

/*==========================================
 * �J�[�h�̑}���\���X�g��Ԃ�
 *------------------------------------------
 */
static void clif_use_card(struct map_session_data *sd, int idx)
{
	int i, j, k = 0, c = 0;
	int ep, fd;

	nullpo_retv(sd);

	if (idx < 0 || idx >= MAX_INVENTORY)
		return;

	if(sd->inventory_data[idx] == NULL)
		return;

	ep = sd->inventory_data[idx]->equip;
	fd = sd->fd;

	WFIFOW(fd,0)=0x17b;
	for(i = 0; i < MAX_INVENTORY && k<sd->inventory_num; i++) {
		if(sd->inventory_data[i] == NULL)
			continue;
		k++;
		if(!itemdb_isarmor(sd->inventory_data[i]->nameid) && !itemdb_isweapon(sd->inventory_data[i]->nameid))	// ����h���Ȃ�
			continue;
		if(itemdb_isspecial(sd->status.inventory[i].card[0]))
			continue;
		if(sd->status.inventory[i].identify == 0)	// ���Ӓ�
			continue;
		if((sd->inventory_data[i]->equip&ep) == 0)	// ���������Ⴄ
			continue;
		if(itemdb_isweapon(sd->inventory_data[i]->nameid) && ep == LOC_LARM)	// ���J�[�h�Ɨ��蕐��
			continue;

		for(j=0; j<sd->inventory_data[i]->slot; j++) {
			if(sd->status.inventory[i].card[j] == 0) {
				WFIFOW(fd,4+c*2) = i + 2;
				c++;
				break;
			}
		}
	}
	WFIFOW(fd,2)=4+c*2;
	WFIFOSET(fd,WFIFOW(fd,2));

	return;
}

/*==========================================
 * �J�[�h�̑}���I��
 *------------------------------------------
 */
void clif_insert_card(struct map_session_data *sd, int idx_equip, int idx_card, unsigned char flag)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x17d;
	WFIFOW(fd,2)=idx_equip+2;
	WFIFOW(fd,4)=idx_card+2;
	WFIFOB(fd,6)=flag;
	WFIFOSET(fd,packet_db[0x17d].len);

	return;
}

/*==========================================
 * �Ӓ�\�A�C�e�����X�g���M
 *------------------------------------------
 */
void clif_item_identify_list(struct map_session_data *sd)
{
	int i,j,c=0,fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x177;
	for(i=j=0;i<MAX_INVENTORY && j<sd->inventory_num;i++) {
		if(sd->status.inventory[i].nameid <= 0)
			continue;
		j++;
		if(sd->status.inventory[i].identify != 1) {
			WFIFOW(fd,c*2+4)=i+2;
			c++;
		}
	}
	if(c > 0) {
		WFIFOW(fd,2)=c*2+4;
		WFIFOSET(fd,WFIFOW(fd,2));
	}

	return;
}

/*==========================================
 * �Ӓ茋��
 *------------------------------------------
 */
void clif_item_identified(struct map_session_data *sd, int idx, unsigned char flag)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd, 0)=0x179;
	WFIFOW(fd, 2)=idx+2;
	WFIFOB(fd, 4)=flag;
	WFIFOSET(fd,packet_db[0x179].len);

	return;
}

/*==========================================
 * �{�q�v���_�C�A���O�\��
 *------------------------------------------
 */
static void clif_baby_req_display(struct map_session_data *dst_sd, struct map_session_data *src_sd, int p_id)
{
	int fd;

	nullpo_retv(dst_sd);

	fd=dst_sd->fd;
	WFIFOW(fd,0) = 0x1f6;
	WFIFOL(fd,2) = src_sd->status.account_id;
	WFIFOL(fd,6) = p_id;
	memcpy(WFIFOP(fd,10), src_sd->status.name, 24);
	WFIFOSET(fd,packet_db[0x1f6].len);

	return;
}

/*==========================================
 * �{�q�`�F�b�N���s
 *------------------------------------------
 */
void clif_baby_req_fail(struct map_session_data *sd, int type)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0) = 0x216;
	WFIFOL(fd,2) = type;
	WFIFOSET(fd,packet_db[0x216].len);

	return;
}

/*==========================================
 * �{�q�^�[�Q�b�g�\��
 *------------------------------------------
 */
// 0x1f8�͎g���ĂȂ������H
/*void clif_baby_target_display(struct map_session_data *sd)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0) = 0x1f8;
	WFIFOSET(fd,packet_db[0x1f8].len);

	return;
}*/

/*==========================================
 * �C���\�A�C�e�����X�g���M
 *------------------------------------------
 */
void clif_item_repair_list(struct map_session_data *sd, struct map_session_data *dstsd)
{
	int i,j,c=0,fd;
	int nameid;

	nullpo_retv(sd);
	nullpo_retv(dstsd);

	fd=sd->fd;
#if PACKETVER < 20180704
	WFIFOW(fd,0)=0x1fc;
	for(i=j=0;i<MAX_INVENTORY && j<dstsd->inventory_num;i++) {
		if((nameid=dstsd->status.inventory[i].nameid) <= 0)
			continue;
		j++;
		if(dstsd->status.inventory[i].attribute != 0) {
			WFIFOW(fd,c*13+4) = i;
			WFIFOW(fd,c*13+6) = nameid;
			WFIFOL(fd,c*13+8) = sd->status.char_id;
			WFIFOL(fd,c*13+12)= dstsd->status.char_id;
			WFIFOB(fd,c*13+16)= c;
			c++;
		}
	}
	if(c > 0) {
		WFIFOW(fd,2)=c*13+4;
		WFIFOSET(fd,WFIFOW(fd,2));
#else
	WFIFOW(fd,0)=0x1fc;
	for(i=j=0;i<MAX_INVENTORY && j<dstsd->inventory_num;i++) {
		if((nameid=dstsd->status.inventory[i].nameid) <= 0)
			continue;
		j++;
		if(dstsd->status.inventory[i].attribute != 0) {
			WFIFOW(fd,c*15+4) = i;
			WFIFOL(fd,c*15+6) = nameid;
			WFIFOL(fd,c*15+10) = sd->status.char_id;
			WFIFOL(fd,c*15+14)= dstsd->status.char_id;
			WFIFOB(fd,c*15+18)= c;
			c++;
		}
	}
	if(c > 0) {
		WFIFOW(fd,2)=c*15+4;
		WFIFOSET(fd,WFIFOW(fd,2));
#endif
		sd->skill_menu.id = BS_REPAIRWEAPON;
		sd->skill_menu.lv = 1;
		sd->skill_menu.val = dstsd->bl.id;
	}else
		clif_skill_fail(sd,sd->ud.skillid,SKILLFAIL_FAILED,0,0);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_item_repaireffect(struct map_session_data *sd, unsigned char flag, int idx)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd, 0)=0x1fe;
	WFIFOW(fd, 2)=idx+2;
	WFIFOB(fd, 4)=flag;
	WFIFOSET(fd,packet_db[0x1fe].len);

	if(sd->skill_menu.val && sd->bl.id != sd->skill_menu.val && flag == 0) {	// ���������瑊��ɂ��ʒm
		struct map_session_data *dstsd = map_id2sd(sd->skill_menu.val);
		if(dstsd)
			clif_item_repaireffect(dstsd,flag,idx);
	}

	memset(&sd->skill_menu,0,sizeof(sd->skill_menu));

	return;
}

/*==========================================
 * ���퐸�B�\�A�C�e�����X�g���M
 *------------------------------------------
 */
void clif_weapon_refine_list(struct map_session_data *sd)
{
	int i,j,c=0,fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x221;
#if PACKETVER < 20180704
	for(i=j=0;i<MAX_INVENTORY && j<sd->inventory_num;i++) {
		if(sd->status.inventory[i].nameid <= 0)
			continue;
		j++;
		if(sd->status.inventory[i].identify == 1 &&
		   sd->inventory_data[i]->refine &&
		   itemdb_wlv(sd->status.inventory[i].nameid) >=1 &&
		   !(sd->status.inventory[i].equip & LOC_RLARM))
		{
			WFIFOW(fd,c*13+ 4)=i+2;
			WFIFOW(fd,c*13+ 6)=sd->status.inventory[i].nameid;
			WFIFOB(fd,c*13+ 8)=sd->status.inventory[i].refine;
			if(itemdb_isspecial(sd->status.inventory[i].card[0])) {
				if(sd->inventory_data[i]->flag.pet_egg) {
					WFIFOW(fd,9) = 0;
					WFIFOW(fd,11) = 0;
					WFIFOW(fd,13) = 0;
				} else {
					WFIFOW(fd,9) = sd->status.inventory[i].card[0];
					WFIFOW(fd,11) = sd->status.inventory[i].card[1];
					WFIFOW(fd,13) = sd->status.inventory[i].card[2];
				}
				WFIFOW(fd,15) = sd->status.inventory[i].card[3];
			} else {
				if(sd->status.inventory[i].card[0] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[0])) > 0)
					WFIFOW(fd,9)=j;
				else
					WFIFOW(fd,9)=sd->status.inventory[i].card[0];
				if(sd->status.inventory[i].card[1] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[1])) > 0)
					WFIFOW(fd,11)=j;
				else
					WFIFOW(fd,11)=sd->status.inventory[i].card[1];
				if(sd->status.inventory[i].card[2] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[2])) > 0)
					WFIFOW(fd,13)=j;
				else
					WFIFOW(fd,13)=sd->status.inventory[i].card[2];
				if(sd->status.inventory[i].card[3] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[3])) > 0)
					WFIFOW(fd,15)=j;
				else
					WFIFOW(fd,15)=sd->status.inventory[i].card[3];
			}
			c++;
		}
	}
	WFIFOW(fd,2)=c*13+4;
#else
	for(i=j=0;i<MAX_INVENTORY && j<sd->inventory_num;i++) {
		if(sd->status.inventory[i].nameid <= 0)
			continue;
		j++;
		if(sd->status.inventory[i].identify == 1 &&
		   sd->inventory_data[i]->refine &&
		   itemdb_wlv(sd->status.inventory[i].nameid) >=1 &&
		   !(sd->status.inventory[i].equip & LOC_RLARM))
		{
			WFIFOW(fd,c*13+ 4)=i+2;
			WFIFOL(fd,c*13+ 6)=sd->status.inventory[i].nameid;
			WFIFOB(fd,c*13+10)=sd->status.inventory[i].refine;
			if(itemdb_isspecial(sd->status.inventory[i].card[0])) {
				if(sd->inventory_data[i]->flag.pet_egg) {
					WFIFOL(fd,11) = 0;
					WFIFOL(fd,15) = 0;
					WFIFOL(fd,19) = 0;
				} else {
					WFIFOL(fd,11) = sd->status.inventory[i].card[0];
					WFIFOL(fd,15) = sd->status.inventory[i].card[1];
					WFIFOL(fd,19) = sd->status.inventory[i].card[2];
				}
				WFIFOL(fd,23) = sd->status.inventory[i].card[3];
			} else {
				if(sd->status.inventory[i].card[0] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[0])) > 0)
					WFIFOL(fd,11)=j;
				else
					WFIFOL(fd,11)=sd->status.inventory[i].card[0];
				if(sd->status.inventory[i].card[1] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[1])) > 0)
					WFIFOL(fd,15)=j;
				else
					WFIFOL(fd,15)=sd->status.inventory[i].card[1];
				if(sd->status.inventory[i].card[2] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[2])) > 0)
					WFIFOL(fd,19)=j;
				else
					WFIFOL(fd,19)=sd->status.inventory[i].card[2];
				if(sd->status.inventory[i].card[3] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[3])) > 0)
					WFIFOL(fd,23)=j;
				else
					WFIFOL(fd,23)=sd->status.inventory[i].card[3];
			}
			c++;
		}
	}
	WFIFOW(fd,2)=c*23+4;
#endif
	WFIFOSET(fd,WFIFOW(fd,2));

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_weapon_refine_res(struct map_session_data *sd, int flag, int nameid)
{
	int view,fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd, 0)=0x223;
	WFIFOL(fd, 2)=flag;
#if PACKETVER < 20180704
	if((view = itemdb_viewid(nameid)) > 0)
		WFIFOW(fd, 6)=view;
	else
		WFIFOW(fd, 6)=nameid;
#else
	if((view = itemdb_viewid(nameid)) > 0)
		WFIFOL(fd, 6)=view;
	else
		WFIFOL(fd, 6)=nameid;
#endif
	WFIFOSET(fd,packet_db[0x223].len);

	return;
}

/*==========================================
 * �A�C�e���ɂ��ꎞ�I�ȃX�L������
 *------------------------------------------
 */
void clif_item_skill(struct map_session_data *sd, int skillid, int skilllv, const char *name)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd, 0)=0x147;
	WFIFOW(fd, 2)=skillid;
	if(skillid == MO_EXTREMITYFIST || skillid == TK_JUMPKICK || skillid == SR_TIGERCANNON || skillid == SR_GATEOFHELL)
		WFIFOL(fd, 4)=1;
	else
		WFIFOL(fd, 4)=skill_get_inf(skillid);
	WFIFOW(fd, 8)=skilllv;
	WFIFOW(fd,10)=skill_get_sp(skillid,skilllv);
	WFIFOW(fd,12)=skill_get_fixed_range(&sd->bl,skillid,skilllv);
	strncpy(WFIFOP(fd,14),name,24);
	WFIFOB(fd,38)=0;
	WFIFOSET(fd,packet_db[0x147].len);

	return;
}

/*==========================================
 * �J�[�g�ɃA�C�e���ǉ�
 *------------------------------------------
 */
void clif_cart_additem(struct map_session_data *sd, int n, int amount)
{
	struct item_data *id;
	int j,fd;

	nullpo_retv(sd);

	if (n < 0 || n >= MAX_CART || sd->status.cart[n].nameid <= 0)
		return;

	fd = sd->fd;
	id = itemdb_search(sd->status.cart[n].nameid);

#if PACKETVER < 7
	WFIFOW(fd,0)=0x124;
	WFIFOW(fd,2)=n+2;
	WFIFOL(fd,4)=amount;
	if(id->view_id > 0)
		WFIFOW(fd,8)=id->view_id;
	else
		WFIFOW(fd,8)=sd->status.cart[n].nameid;
	WFIFOB(fd,10)=sd->status.cart[n].identify;
	WFIFOB(fd,11)=sd->status.cart[n].attribute;
	WFIFOB(fd,12)=sd->status.cart[n].refine;
	if(itemdb_isspecial(sd->status.cart[n].card[0])) {
		if(id->flag.pet_egg) {
			WFIFOW(fd,13) = 0;
			WFIFOW(fd,15) = 0;
			WFIFOW(fd,17) = 0;
		} else {
			WFIFOW(fd,13) = sd->status.cart[n].card[0];
			WFIFOW(fd,15) = sd->status.cart[n].card[1];
			WFIFOW(fd,17) = sd->status.cart[n].card[2];
		}
		WFIFOW(fd,19) = sd->status.cart[n].card[3];
	} else {
		if(sd->status.cart[n].card[0] > 0 && (j=itemdb_viewid(sd->status.cart[n].card[0])) > 0)
			WFIFOW(fd,13)= j;
		else
			WFIFOW(fd,13)= sd->status.cart[n].card[0];
		if(sd->status.cart[n].card[1] > 0 && (j=itemdb_viewid(sd->status.cart[n].card[1])) > 0)
			WFIFOW(fd,15)= j;
		else
			WFIFOW(fd,15)= sd->status.cart[n].card[1];
		if(sd->status.cart[n].card[2] > 0 && (j=itemdb_viewid(sd->status.cart[n].card[2])) > 0)
			WFIFOW(fd,17)= j;
		else
			WFIFOW(fd,17)= sd->status.cart[n].card[2];
		if(sd->status.cart[n].card[3] > 0 && (j=itemdb_viewid(sd->status.cart[n].card[3])) > 0)
			WFIFOW(fd,19)= j;
		else
			WFIFOW(fd,19)= sd->status.cart[n].card[3];
	}
	WFIFOSET(fd,packet_db[0x124].len);
#elif PACKETVER < 20150513
	WFIFOW(fd,0)=0x1c5;
	WFIFOW(fd,2)=n+2;
	WFIFOL(fd,4)=amount;
	if(id->view_id > 0)
		WFIFOW(fd,8)=id->view_id;
	else
		WFIFOW(fd,8)=sd->status.cart[n].nameid;
	WFIFOB(fd,10)=id->type;
	WFIFOB(fd,11)=sd->status.cart[n].identify;
	WFIFOB(fd,12)=sd->status.cart[n].attribute;
	WFIFOB(fd,13)=sd->status.cart[n].refine;
	if(itemdb_isspecial(sd->status.cart[n].card[0])) {
		if(id->flag.pet_egg) {
			WFIFOW(fd,14) = 0;
			WFIFOW(fd,16) = 0;
			WFIFOW(fd,18) = 0;
		} else {
			WFIFOW(fd,14) = sd->status.cart[n].card[0];
			WFIFOW(fd,16) = sd->status.cart[n].card[1];
			WFIFOW(fd,18) = sd->status.cart[n].card[2];
		}
		WFIFOW(fd,20) = sd->status.cart[n].card[3];
	} else {
		if(sd->status.cart[n].card[0] > 0 && (j=itemdb_viewid(sd->status.cart[n].card[0])) > 0)
			WFIFOW(fd,14)= j;
		else
			WFIFOW(fd,14)= sd->status.cart[n].card[0];
		if(sd->status.cart[n].card[1] > 0 && (j=itemdb_viewid(sd->status.cart[n].card[1])) > 0)
			WFIFOW(fd,16)= j;
		else
			WFIFOW(fd,16)= sd->status.cart[n].card[1];
		if(sd->status.cart[n].card[2] > 0 && (j=itemdb_viewid(sd->status.cart[n].card[2])) > 0)
			WFIFOW(fd,18)= j;
		else
			WFIFOW(fd,18)= sd->status.cart[n].card[2];
		if(sd->status.cart[n].card[3] > 0 && (j=itemdb_viewid(sd->status.cart[n].card[3])) > 0)
			WFIFOW(fd,20)= j;
		else
			WFIFOW(fd,20)= sd->status.cart[n].card[3];
	}
	WFIFOSET(fd,packet_db[0x1c5].len);
#elif PACKETVER < 20180704
	WFIFOW(fd,0)=0xa0b;
	WFIFOW(fd,2)=n+2;
	WFIFOL(fd,4)=amount;
	if(id->view_id > 0)
		WFIFOW(fd,8)=id->view_id;
	else
		WFIFOW(fd,8)=sd->status.cart[n].nameid;
	WFIFOB(fd,10)=id->type;
	WFIFOB(fd,11)=sd->status.cart[n].identify;
	WFIFOB(fd,12)=sd->status.cart[n].attribute;
	WFIFOB(fd,13)=sd->status.cart[n].refine;
	if(itemdb_isspecial(sd->status.cart[n].card[0])) {
		if(id->flag.pet_egg) {
			WFIFOW(fd,14) = 0;
			WFIFOW(fd,16) = 0;
			WFIFOW(fd,18) = 0;
		} else {
			WFIFOW(fd,14) = sd->status.cart[n].card[0];
			WFIFOW(fd,16) = sd->status.cart[n].card[1];
			WFIFOW(fd,18) = sd->status.cart[n].card[2];
		}
		WFIFOW(fd,20) = sd->status.cart[n].card[3];
	} else {
		if(sd->status.cart[n].card[0] > 0 && (j=itemdb_viewid(sd->status.cart[n].card[0])) > 0)
			WFIFOW(fd,14)= j;
		else
			WFIFOW(fd,14)= sd->status.cart[n].card[0];
		if(sd->status.cart[n].card[1] > 0 && (j=itemdb_viewid(sd->status.cart[n].card[1])) > 0)
			WFIFOW(fd,16)= j;
		else
			WFIFOW(fd,16)= sd->status.cart[n].card[1];
		if(sd->status.cart[n].card[2] > 0 && (j=itemdb_viewid(sd->status.cart[n].card[2])) > 0)
			WFIFOW(fd,18)= j;
		else
			WFIFOW(fd,18)= sd->status.cart[n].card[2];
		if(sd->status.cart[n].card[3] > 0 && (j=itemdb_viewid(sd->status.cart[n].card[3])) > 0)
			WFIFOW(fd,20)= j;
		else
			WFIFOW(fd,20)= sd->status.cart[n].card[3];
	}
	WFIFOW(fd,22) = sd->status.cart[n].opt[0].id;
	WFIFOW(fd,24) = sd->status.cart[n].opt[0].val;
	WFIFOB(fd,26) = 0;
	WFIFOW(fd,27) = sd->status.cart[n].opt[1].id;
	WFIFOW(fd,29) = sd->status.cart[n].opt[1].val;
	WFIFOB(fd,31) = 0;
	WFIFOW(fd,32) = sd->status.cart[n].opt[2].id;
	WFIFOW(fd,34) = sd->status.cart[n].opt[2].val;
	WFIFOB(fd,36) = 0;
	WFIFOW(fd,37) = sd->status.cart[n].opt[3].id;
	WFIFOW(fd,39) = sd->status.cart[n].opt[3].val;
	WFIFOB(fd,41) = 0;
	WFIFOW(fd,42) = sd->status.cart[n].opt[4].id;
	WFIFOW(fd,44) = sd->status.cart[n].opt[4].val;
	WFIFOB(fd,46) = 0;
	WFIFOSET(fd,packet_db[0xa0b].len);
#else
	WFIFOW(fd,0)=0xa0b;
	WFIFOW(fd,2)=n+2;
	WFIFOL(fd,4)=amount;
	if(id->view_id > 0)
		WFIFOL(fd,8)=id->view_id;
	else
		WFIFOL(fd,8)=sd->status.cart[n].nameid;
	WFIFOB(fd,12)=id->type;
	WFIFOB(fd,13)=sd->status.cart[n].identify;
	WFIFOB(fd,14)=sd->status.cart[n].attribute;
	WFIFOB(fd,15)=sd->status.cart[n].refine;
	if(itemdb_isspecial(sd->status.cart[n].card[0])) {
		if(id->flag.pet_egg) {
			WFIFOL(fd,16) = 0;
			WFIFOL(fd,20) = 0;
			WFIFOL(fd,24) = 0;
		} else {
			WFIFOL(fd,16) = sd->status.cart[n].card[0];
			WFIFOL(fd,20) = sd->status.cart[n].card[1];
			WFIFOL(fd,24) = sd->status.cart[n].card[2];
		}
		WFIFOL(fd,28) = sd->status.cart[n].card[3];
	} else {
		if(sd->status.cart[n].card[0] > 0 && (j=itemdb_viewid(sd->status.cart[n].card[0])) > 0)
			WFIFOL(fd,16)= j;
		else
			WFIFOL(fd,16)= sd->status.cart[n].card[0];
		if(sd->status.cart[n].card[1] > 0 && (j=itemdb_viewid(sd->status.cart[n].card[1])) > 0)
			WFIFOL(fd,20)= j;
		else
			WFIFOL(fd,20)= sd->status.cart[n].card[1];
		if(sd->status.cart[n].card[2] > 0 && (j=itemdb_viewid(sd->status.cart[n].card[2])) > 0)
			WFIFOL(fd,24)= j;
		else
			WFIFOL(fd,24)= sd->status.cart[n].card[2];
		if(sd->status.cart[n].card[3] > 0 && (j=itemdb_viewid(sd->status.cart[n].card[3])) > 0)
			WFIFOL(fd,28)= j;
		else
			WFIFOL(fd,28)= sd->status.cart[n].card[3];
	}
	WFIFOW(fd,32) = sd->status.cart[n].opt[0].id;
	WFIFOW(fd,34) = sd->status.cart[n].opt[0].val;
	WFIFOB(fd,36) = 0;
	WFIFOW(fd,37) = sd->status.cart[n].opt[1].id;
	WFIFOW(fd,39) = sd->status.cart[n].opt[1].val;
	WFIFOB(fd,41) = 0;
	WFIFOW(fd,42) = sd->status.cart[n].opt[2].id;
	WFIFOW(fd,44) = sd->status.cart[n].opt[2].val;
	WFIFOB(fd,46) = 0;
	WFIFOW(fd,47) = sd->status.cart[n].opt[3].id;
	WFIFOW(fd,49) = sd->status.cart[n].opt[3].val;
	WFIFOB(fd,51) = 0;
	WFIFOW(fd,52) = sd->status.cart[n].opt[4].id;
	WFIFOW(fd,54) = sd->status.cart[n].opt[4].val;
	WFIFOB(fd,56) = 0;
	WFIFOSET(fd,packet_db[0xa0b].len);
#endif

	return;
}

/*==========================================
 * �J�[�g����A�C�e���폜
 *------------------------------------------
 */
void clif_cart_delitem(struct map_session_data *sd, int n, int amount)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x125;
	WFIFOW(fd,2)=n+2;
	WFIFOL(fd,4)=amount;
	WFIFOSET(fd,packet_db[0x125].len);

	return;
}

/*==========================================
 * �J�[�g�̃A�C�e�����X�g
 *------------------------------------------
 */
void clif_cart_itemlist(struct map_session_data *sd)
{
	struct item_data *id;
	int i,n,fd;

	nullpo_retv(sd);

	fd=sd->fd;

#if PACKETVER < 5
	WFIFOW(fd,0)=0x123;
	for(i=0,n=0;i<MAX_CART;i++){
		if(sd->status.cart[i].nameid<=0)
			continue;
		id = itemdb_search(sd->status.cart[i].nameid);
		if(itemdb_isequip2(id))
			continue;
		WFIFOW(fd,n*10+4)=i+2;
		if(id->view_id > 0)
			WFIFOW(fd,n*10+6)=id->view_id;
		else
			WFIFOW(fd,n*10+6)=sd->status.cart[i].nameid;
		WFIFOB(fd,n*10+8)=id->type;
		WFIFOB(fd,n*10+9)=sd->status.cart[i].identify;
		WFIFOW(fd,n*10+10)=sd->status.cart[i].amount;
		if(sd->status.cart[i].equip == LOC_ARROW)
			WFIFOW(fd,n*10+12)=LOC_ARROW;
		else
			WFIFOW(fd,n*10+12)=0;
		n++;
	}
	if(n){
		WFIFOW(fd,2)=4+n*10;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#elif PACKETVER < 20080102
	WFIFOW(fd,0)=0x1ef;
	for(i=0,n=0;i<MAX_CART;i++){
		if(sd->status.cart[i].nameid<=0)
			continue;
		id = itemdb_search(sd->status.cart[i].nameid);
		if(itemdb_isequip2(id))
			continue;
		WFIFOW(fd,n*18+4)=i+2;
		if(id->view_id > 0)
			WFIFOW(fd,n*18+6)=id->view_id;
		else
			WFIFOW(fd,n*18+6)=sd->status.cart[i].nameid;
		WFIFOB(fd,n*18+8)=id->type;
		WFIFOB(fd,n*18+9)=sd->status.cart[i].identify;
		WFIFOW(fd,n*18+10)=sd->status.cart[i].amount;
		if(sd->status.cart[i].equip == LOC_ARROW)
			WFIFOW(fd,n*18+12)=LOC_ARROW;
		else
			WFIFOW(fd,n*18+12)=0;
		WFIFOW(fd,n*18+14)=sd->status.cart[i].card[0];
		WFIFOW(fd,n*18+16)=sd->status.cart[i].card[1];
		WFIFOW(fd,n*18+18)=sd->status.cart[i].card[2];
		WFIFOW(fd,n*18+20)=sd->status.cart[i].card[3];
		n++;
	}
	if(n){
		WFIFOW(fd,2)=4+n*18;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#elif PACKETVER < 20111025
	WFIFOW(fd,0)=0x2e9;
	for(i=0,n=0;i<MAX_CART;i++){
		if(sd->status.cart[i].nameid<=0)
			continue;
		id = itemdb_search(sd->status.cart[i].nameid);
		if(itemdb_isequip2(id))
			continue;
		WFIFOW(fd,n*22+4)=i+2;
		if(id->view_id > 0)
			WFIFOW(fd,n*22+6)=id->view_id;
		else
			WFIFOW(fd,n*22+6)=sd->status.cart[i].nameid;
		WFIFOB(fd,n*22+8)=id->type;
		WFIFOB(fd,n*22+9)=sd->status.cart[i].identify;
		WFIFOW(fd,n*22+10)=sd->status.cart[i].amount;
		if(sd->status.cart[i].equip == LOC_ARROW)
			WFIFOW(fd,n*22+12)=LOC_ARROW;
		else
			WFIFOW(fd,n*22+12)=0;
		WFIFOW(fd,n*22+14)=sd->status.cart[i].card[0];
		WFIFOW(fd,n*22+16)=sd->status.cart[i].card[1];
		WFIFOW(fd,n*22+18)=sd->status.cart[i].card[2];
		WFIFOW(fd,n*22+20)=sd->status.cart[i].card[3];
		WFIFOL(fd,n*22+22)=sd->status.cart[i].limit;
		n++;
	}
	if(n){
		WFIFOW(fd,2)=4+n*22;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#elif PACKETVER < 20120925
	WFIFOW(fd,0)=0x902;
	for(i=0,n=0;i<MAX_CART;i++){
		if(sd->status.cart[i].nameid<=0)
			continue;
		id = itemdb_search(sd->status.cart[i].nameid);
		if(itemdb_isequip2(id))
			continue;
		WFIFOW(fd,n*22+4)=i+2;
		if(id->view_id > 0)
			WFIFOW(fd,n*22+6)=id->view_id;
		else
			WFIFOW(fd,n*22+6)=sd->status.cart[i].nameid;
		WFIFOB(fd,n*22+8)=id->type;
		WFIFOW(fd,n*22+9)=sd->status.cart[i].amount;
		if(sd->status.cart[i].equip == LOC_ARROW)
			WFIFOW(fd,n*22+11)=LOC_ARROW;
		else
			WFIFOW(fd,n*22+11)=0;
		WFIFOW(fd,n*22+13)=sd->status.cart[i].card[0];
		WFIFOW(fd,n*22+15)=sd->status.cart[i].card[1];
		WFIFOW(fd,n*22+17)=sd->status.cart[i].card[2];
		WFIFOW(fd,n*22+19)=sd->status.cart[i].card[3];
		WFIFOL(fd,n*22+21)=sd->status.cart[i].limit;
		WFIFOB(fd,n*22+25)=sd->status.cart[i].identify;
		n++;
	}
	if(n){
		WFIFOW(fd,2)=4+n*22;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#elif PACKETVER < 20180704
	WFIFOW(fd,0)=0x993;
	for(i=0,n=0;i<MAX_CART;i++){
		if(sd->status.cart[i].nameid<=0)
			continue;
		id = itemdb_search(sd->status.cart[i].nameid);
		if(itemdb_isequip2(id))
			continue;
		WFIFOW(fd,n*24+4)=i+2;
		if(id->view_id > 0)
			WFIFOW(fd,n*24+6)=id->view_id;
		else
			WFIFOW(fd,n*24+6)=sd->status.cart[i].nameid;
		WFIFOB(fd,n*24+8)=id->type;
		WFIFOW(fd,n*24+9)=sd->status.cart[i].amount;
		if(sd->status.cart[i].equip == LOC_ARROW)
			WFIFOL(fd,n*24+11)=LOC_ARROW;
		else
			WFIFOL(fd,n*24+11)=0;
		WFIFOW(fd,n*24+15)=sd->status.cart[i].card[0];
		WFIFOW(fd,n*24+17)=sd->status.cart[i].card[1];
		WFIFOW(fd,n*24+19)=sd->status.cart[i].card[2];
		WFIFOW(fd,n*24+21)=sd->status.cart[i].card[3];
		WFIFOL(fd,n*24+23)=sd->status.cart[i].limit;
		WFIFOB(fd,n*24+27)=sd->status.cart[i].identify;
		n++;
	}
	if(n){
		WFIFOW(fd,2)=4+n*24;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#else
	WFIFOW(fd,0)=0x993;
	for(i=0,n=0;i<MAX_CART;i++){
		if(sd->status.cart[i].nameid<=0)
			continue;
		id = itemdb_search(sd->status.cart[i].nameid);
		if(itemdb_isequip2(id))
			continue;
		WFIFOW(fd,n*34+4)=i+2;
		if(id->view_id > 0)
			WFIFOL(fd,n*34+6)=id->view_id;
		else
			WFIFOL(fd,n*34+6)=sd->status.cart[i].nameid;
		WFIFOB(fd,n*34+10)=id->type;
		WFIFOW(fd,n*34+11)=sd->status.cart[i].amount;
		if(sd->status.cart[i].equip == LOC_ARROW)
			WFIFOL(fd,n*34+13)=LOC_ARROW;
		else
			WFIFOL(fd,n*34+13)=0;
		WFIFOL(fd,n*34+17)=sd->status.cart[i].card[0];
		WFIFOL(fd,n*34+21)=sd->status.cart[i].card[1];
		WFIFOL(fd,n*34+25)=sd->status.cart[i].card[2];
		WFIFOL(fd,n*34+29)=sd->status.cart[i].card[3];
		WFIFOL(fd,n*34+33)=sd->status.cart[i].limit;
		WFIFOB(fd,n*34+37)=sd->status.cart[i].identify;
		n++;
	}
	if(n){
		WFIFOW(fd,2)=4+n*34;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#endif

	return;
}

/*==========================================
 * �J�[�g�̑����i���X�g
 *------------------------------------------
 */
void clif_cart_equiplist(struct map_session_data *sd)
{
	struct item_data *id;
	int i,j,n,fd;

	nullpo_retv(sd);

	fd=sd->fd;

#if PACKETVER < 20070711
	WFIFOW(fd,0)=0x122;
	for(i=0,n=0;i<MAX_CART;i++){
		if(sd->status.cart[i].nameid<=0)
			continue;
		id = itemdb_search(sd->status.cart[i].nameid);
		if(!itemdb_isequip2(id))
			continue;
		WFIFOW(fd,n*20+4)=i+2;
		if(id->view_id > 0)
			WFIFOW(fd,n*20+6)=id->view_id;
		else
			WFIFOW(fd,n*20+6)=sd->status.cart[i].nameid;
		WFIFOB(fd,n*20+8)=id->type;
		WFIFOB(fd,n*20+9)=sd->status.cart[i].identify;
		WFIFOW(fd,n*20+10)=id->equip;
		WFIFOW(fd,n*20+12)=sd->status.cart[i].equip;
		WFIFOB(fd,n*20+14)=sd->status.cart[i].attribute;
		WFIFOB(fd,n*20+15)=sd->status.cart[i].refine;
		if(itemdb_isspecial(sd->status.cart[i].card[0])) {
			if(id->flag.pet_egg) {
				WFIFOW(fd,n*20+16) = 0;
				WFIFOW(fd,n*20+18) = 0;
				WFIFOW(fd,n*20+20) = 0;
			} else {
				WFIFOW(fd,n*20+16) = sd->status.cart[i].card[0];
				WFIFOW(fd,n*20+18) = sd->status.cart[i].card[1];
				WFIFOW(fd,n*20+20) = sd->status.cart[i].card[2];
			}
			WFIFOW(fd,n*20+22) = sd->status.cart[i].card[3];
		} else {
			if(sd->status.cart[i].card[0] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[0])) > 0)
				WFIFOW(fd,n*20+16)= j;
			else
				WFIFOW(fd,n*20+16)= sd->status.cart[i].card[0];
			if(sd->status.cart[i].card[1] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[1])) > 0)
				WFIFOW(fd,n*20+18)= j;
			else
				WFIFOW(fd,n*20+18)= sd->status.cart[i].card[1];
			if(sd->status.cart[i].card[2] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[2])) > 0)
				WFIFOW(fd,n*20+20)= j;
			else
				WFIFOW(fd,n*20+20)= sd->status.cart[i].card[2];
			if(sd->status.cart[i].card[3] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[3])) > 0)
				WFIFOW(fd,n*20+22)= j;
			else
				WFIFOW(fd,n*20+22)= sd->status.cart[i].card[3];
		}
		n++;
	}
	if(n){
		WFIFOW(fd,2)=4+n*20;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#elif PACKETVER < 20070904
	WFIFOW(fd,0)=0x297;
	for(i=0,n=0;i<MAX_CART;i++){
		if(sd->status.cart[i].nameid<=0)
			continue;
		id = itemdb_search(sd->status.cart[i].nameid);
		if(!itemdb_isequip2(id))
			continue;
		WFIFOW(fd,n*24+4)=i+2;
		if(id->view_id > 0)
			WFIFOW(fd,n*24+6)=id->view_id;
		else
			WFIFOW(fd,n*24+6)=sd->status.cart[i].nameid;
		WFIFOB(fd,n*24+8)=id->type;
		WFIFOB(fd,n*24+9)=sd->status.cart[i].identify;
		WFIFOW(fd,n*24+10)=id->equip;
		WFIFOW(fd,n*24+12)=sd->status.cart[i].equip;
		WFIFOB(fd,n*24+14)=sd->status.cart[i].attribute;
		WFIFOB(fd,n*24+15)=sd->status.cart[i].refine;
		if(itemdb_isspecial(sd->status.cart[i].card[0])) {
			if(id->flag.pet_egg) {
				WFIFOW(fd,n*24+16) = 0;
				WFIFOW(fd,n*24+18) = 0;
				WFIFOW(fd,n*24+20) = 0;
			} else {
				WFIFOW(fd,n*24+16) = sd->status.cart[i].card[0];
				WFIFOW(fd,n*24+18) = sd->status.cart[i].card[1];
				WFIFOW(fd,n*24+20) = sd->status.cart[i].card[2];
			}
			WFIFOW(fd,n*24+22) = sd->status.cart[i].card[3];
		} else {
			if(sd->status.cart[i].card[0] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[0])) > 0)
				WFIFOW(fd,n*24+16)= j;
			else
				WFIFOW(fd,n*24+16)= sd->status.cart[i].card[0];
			if(sd->status.cart[i].card[1] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[1])) > 0)
				WFIFOW(fd,n*24+18)= j;
			else
				WFIFOW(fd,n*24+18)= sd->status.cart[i].card[1];
			if(sd->status.cart[i].card[2] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[2])) > 0)
				WFIFOW(fd,n*24+20)= j;
			else
				WFIFOW(fd,n*24+20)= sd->status.cart[i].card[2];
			if(sd->status.cart[i].card[3] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[3])) > 0)
				WFIFOW(fd,n*24+22)= j;
			else
				WFIFOW(fd,n*24+22)= sd->status.cart[i].card[3];
		}
		WFIFOL(fd,n*24+24)=sd->status.cart[i].limit;
		n++;
	}
	if(n){
		WFIFOW(fd,2)=4+n*24;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#elif PACKETVER < 20100414
	WFIFOW(fd,0)=0x2d2;
	for(i=0,n=0;i<MAX_CART;i++){
		if(sd->status.cart[i].nameid<=0)
			continue;
		id = itemdb_search(sd->status.cart[i].nameid);
		if(!itemdb_isequip2(id))
			continue;
		WFIFOW(fd,n*26+4)=i+2;
		if(id->view_id > 0)
			WFIFOW(fd,n*26+6)=id->view_id;
		else
			WFIFOW(fd,n*26+6)=sd->status.cart[i].nameid;
		WFIFOB(fd,n*26+8)=id->type;
		WFIFOB(fd,n*26+9)=sd->status.cart[i].identify;
		WFIFOW(fd,n*26+10)=id->equip;
		WFIFOW(fd,n*26+12)=sd->status.cart[i].equip;
		WFIFOB(fd,n*26+14)=sd->status.cart[i].attribute;
		WFIFOB(fd,n*26+15)=sd->status.cart[i].refine;
		if(itemdb_isspecial(sd->status.cart[i].card[0])) {
			if(id->flag.pet_egg) {
				WFIFOW(fd,n*26+16) = 0;
				WFIFOW(fd,n*26+18) = 0;
				WFIFOW(fd,n*26+20) = 0;
			} else {
				WFIFOW(fd,n*26+16) = sd->status.cart[i].card[0];
				WFIFOW(fd,n*26+18) = sd->status.cart[i].card[1];
				WFIFOW(fd,n*26+20) = sd->status.cart[i].card[2];
			}
			WFIFOW(fd,n*26+22) = sd->status.cart[i].card[3];
		} else {
			if(sd->status.cart[i].card[0] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[0])) > 0)
				WFIFOW(fd,n*26+16)= j;
			else
				WFIFOW(fd,n*26+16)= sd->status.cart[i].card[0];
			if(sd->status.cart[i].card[1] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[1])) > 0)
				WFIFOW(fd,n*26+18)= j;
			else
				WFIFOW(fd,n*26+18)= sd->status.cart[i].card[1];
			if(sd->status.cart[i].card[2] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[2])) > 0)
				WFIFOW(fd,n*26+20)= j;
			else
				WFIFOW(fd,n*26+20)= sd->status.cart[i].card[2];
			if(sd->status.cart[i].card[3] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[3])) > 0)
				WFIFOW(fd,n*26+22)= j;
			else
				WFIFOW(fd,n*26+22)= sd->status.cart[i].card[3];
		}
		WFIFOL(fd,n*26+24)=sd->status.cart[i].limit;
		WFIFOW(fd,n*26+28)=0;
		n++;
	}
	if(n){
		WFIFOW(fd,2)=4+n*26;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#elif PACKETVER < 20111025
	WFIFOW(fd,0)=0x2d2;
	for(i=0,n=0;i<MAX_CART;i++){
		if(sd->status.cart[i].nameid<=0)
			continue;
		id = itemdb_search(sd->status.cart[i].nameid);
		if(!itemdb_isequip2(id))
			continue;
		WFIFOW(fd,n*28+4)=i+2;
		if(id->view_id > 0)
			WFIFOW(fd,n*28+6)=id->view_id;
		else
			WFIFOW(fd,n*28+6)=sd->status.cart[i].nameid;
		WFIFOB(fd,n*28+8)=id->type;
		WFIFOB(fd,n*28+9)=sd->status.cart[i].identify;
		WFIFOW(fd,n*28+10)=id->equip;
		WFIFOW(fd,n*28+12)=sd->status.cart[i].equip;
		WFIFOB(fd,n*28+14)=sd->status.cart[i].attribute;
		WFIFOB(fd,n*28+15)=sd->status.cart[i].refine;
		if(itemdb_isspecial(sd->status.cart[i].card[0])) {
			if(id->flag.pet_egg) {
				WFIFOW(fd,n*28+16) = 0;
				WFIFOW(fd,n*28+18) = 0;
				WFIFOW(fd,n*28+20) = 0;
			} else {
				WFIFOW(fd,n*28+16) = sd->status.cart[i].card[0];
				WFIFOW(fd,n*28+18) = sd->status.cart[i].card[1];
				WFIFOW(fd,n*28+20) = sd->status.cart[i].card[2];
			}
			WFIFOW(fd,n*28+22) = sd->status.cart[i].card[3];
		} else {
			if(sd->status.cart[i].card[0] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[0])) > 0)
				WFIFOW(fd,n*28+16)= j;
			else
				WFIFOW(fd,n*28+16)= sd->status.cart[i].card[0];
			if(sd->status.cart[i].card[1] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[1])) > 0)
				WFIFOW(fd,n*28+18)= j;
			else
				WFIFOW(fd,n*28+18)= sd->status.cart[i].card[1];
			if(sd->status.cart[i].card[2] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[2])) > 0)
				WFIFOW(fd,n*28+20)= j;
			else
				WFIFOW(fd,n*28+20)= sd->status.cart[i].card[2];
			if(sd->status.cart[i].card[3] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[3])) > 0)
				WFIFOW(fd,n*28+22)= j;
			else
				WFIFOW(fd,n*28+22)= sd->status.cart[i].card[3];
		}
		WFIFOL(fd,n*28+24)=sd->status.cart[i].limit;
		WFIFOW(fd,n*28+28)=0;
		WFIFOW(fd,n*28+30)=id->look;
		n++;
	}
	if(n){
		WFIFOW(fd,2)=4+n*28;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#elif PACKETVER < 20120925
	WFIFOW(fd,0)=0x903;
	for(i=0,n=0;i<MAX_CART;i++){
		if(sd->status.cart[i].nameid<=0)
			continue;
		id = itemdb_search(sd->status.cart[i].nameid);
		if(!itemdb_isequip2(id))
			continue;
		WFIFOW(fd,n*27+4)=i+2;
		if(id->view_id > 0)
			WFIFOW(fd,n*27+6)=id->view_id;
		else
			WFIFOW(fd,n*27+6)=sd->status.cart[i].nameid;
		WFIFOB(fd,n*27+8)=id->type;
		WFIFOW(fd,n*27+9)=id->equip;
		WFIFOW(fd,n*27+11)=sd->status.cart[i].equip;
		WFIFOB(fd,n*27+13)=sd->status.cart[i].refine;
		if(itemdb_isspecial(sd->status.cart[i].card[0])) {
			if(id->flag.pet_egg) {
				WFIFOW(fd,n*27+14) = 0;
				WFIFOW(fd,n*27+16) = 0;
				WFIFOW(fd,n*27+18) = 0;
			} else {
				WFIFOW(fd,n*27+14) = sd->status.cart[i].card[0];
				WFIFOW(fd,n*27+16) = sd->status.cart[i].card[1];
				WFIFOW(fd,n*27+18) = sd->status.cart[i].card[2];
			}
			WFIFOW(fd,n*27+20) = sd->status.cart[i].card[3];
		} else {
			if(sd->status.cart[i].card[0] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[0])) > 0)
				WFIFOW(fd,n*27+14)= j;
			else
				WFIFOW(fd,n*27+14)= sd->status.cart[i].card[0];
			if(sd->status.cart[i].card[1] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[1])) > 0)
				WFIFOW(fd,n*27+16)= j;
			else
				WFIFOW(fd,n*27+16)= sd->status.cart[i].card[1];
			if(sd->status.cart[i].card[2] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[2])) > 0)
				WFIFOW(fd,n*27+18)= j;
			else
				WFIFOW(fd,n*27+18)= sd->status.cart[i].card[2];
			if(sd->status.cart[i].card[3] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[3])) > 0)
				WFIFOW(fd,n*27+20)= j;
			else
				WFIFOW(fd,n*27+20)= sd->status.cart[i].card[3];
		}
		WFIFOL(fd,n*27+22)=sd->status.cart[i].limit;
		WFIFOW(fd,n*27+26)=0;
		WFIFOW(fd,n*27+28)=id->look;
		WFIFOB(fd,n*27+30)=sd->status.cart[i].identify+(sd->status.cart[i].attribute?2:0);
		n++;
	}
	if(n){
		WFIFOW(fd,2)=4+n*27;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#elif PACKETVER < 20150513
	WFIFOW(fd,0)=0x994;
	for(i=0,n=0;i<MAX_CART;i++){
		if(sd->status.cart[i].nameid<=0)
			continue;
		id = itemdb_search(sd->status.cart[i].nameid);
		if(!itemdb_isequip2(id))
			continue;
		WFIFOW(fd,n*31+4)=i+2;
		if(id->view_id > 0)
			WFIFOW(fd,n*31+6)=id->view_id;
		else
			WFIFOW(fd,n*31+6)=sd->status.cart[i].nameid;
		WFIFOB(fd,n*31+8)=id->type;
		WFIFOL(fd,n*31+9)=id->equip;
		WFIFOL(fd,n*31+13)=sd->status.cart[i].equip;
		WFIFOB(fd,n*31+17)=sd->status.cart[i].refine;
		if(itemdb_isspecial(sd->status.cart[i].card[0])) {
			if(id->flag.pet_egg) {
				WFIFOW(fd,n*31+18) = 0;
				WFIFOW(fd,n*31+20) = 0;
				WFIFOW(fd,n*31+22) = 0;
			} else {
				WFIFOW(fd,n*31+18) = sd->status.cart[i].card[0];
				WFIFOW(fd,n*31+20) = sd->status.cart[i].card[1];
				WFIFOW(fd,n*31+22) = sd->status.cart[i].card[2];
			}
			WFIFOW(fd,n*31+24) = sd->status.cart[i].card[3];
		} else {
			if(sd->status.cart[i].card[0] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[0])) > 0)
				WFIFOW(fd,n*31+18)= j;
			else
				WFIFOW(fd,n*31+18)= sd->status.cart[i].card[0];
			if(sd->status.cart[i].card[1] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[1])) > 0)
				WFIFOW(fd,n*31+20)= j;
			else
				WFIFOW(fd,n*31+20)= sd->status.cart[i].card[1];
			if(sd->status.cart[i].card[2] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[2])) > 0)
				WFIFOW(fd,n*31+22)= j;
			else
				WFIFOW(fd,n*31+22)= sd->status.cart[i].card[2];
			if(sd->status.cart[i].card[3] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[3])) > 0)
				WFIFOW(fd,n*31+24)= j;
			else
				WFIFOW(fd,n*31+24)= sd->status.cart[i].card[3];
		}
		WFIFOL(fd,n*31+26)=sd->status.cart[i].limit;
		WFIFOW(fd,n*31+30)=0;
		WFIFOW(fd,n*31+32)=id->look;
		WFIFOB(fd,n*31+34)=sd->status.cart[i].identify+(sd->status.cart[i].attribute?2:0);
		n++;
	}
	if(n){
		WFIFOW(fd,2)=4+n*31;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#elif PACKETVER < 20180704
	WFIFOW(fd,0)=0xa0f;
	for(i=0,n=0;i<MAX_CART;i++){
		if(sd->status.cart[i].nameid<=0)
			continue;
		id = itemdb_search(sd->status.cart[i].nameid);
		if(!itemdb_isequip2(id))
			continue;
		WFIFOW(fd,n*57+4)=i+2;
		if(id->view_id > 0)
			WFIFOW(fd,n*57+6)=id->view_id;
		else
			WFIFOW(fd,n*57+6)=sd->status.cart[i].nameid;
		WFIFOB(fd,n*57+8)=id->type;
		WFIFOL(fd,n*57+9)=id->equip;
		WFIFOL(fd,n*57+13)=sd->status.cart[i].equip;
		WFIFOB(fd,n*57+17)=sd->status.cart[i].refine;
		if(itemdb_isspecial(sd->status.cart[i].card[0])) {
			if(id->flag.pet_egg) {
				WFIFOW(fd,n*57+18) = 0;
				WFIFOW(fd,n*57+20) = 0;
				WFIFOW(fd,n*57+22) = 0;
			} else {
				WFIFOW(fd,n*57+18) = sd->status.cart[i].card[0];
				WFIFOW(fd,n*57+20) = sd->status.cart[i].card[1];
				WFIFOW(fd,n*57+22) = sd->status.cart[i].card[2];
			}
			WFIFOW(fd,n*57+24) = sd->status.cart[i].card[3];
		} else {
			if(sd->status.cart[i].card[0] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[0])) > 0)
				WFIFOW(fd,n*57+18)= j;
			else
				WFIFOW(fd,n*57+18)= sd->status.cart[i].card[0];
			if(sd->status.cart[i].card[1] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[1])) > 0)
				WFIFOW(fd,n*57+20)= j;
			else
				WFIFOW(fd,n*57+20)= sd->status.cart[i].card[1];
			if(sd->status.cart[i].card[2] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[2])) > 0)
				WFIFOW(fd,n*57+22)= j;
			else
				WFIFOW(fd,n*57+22)= sd->status.cart[i].card[2];
			if(sd->status.cart[i].card[3] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[3])) > 0)
				WFIFOW(fd,n*57+24)= j;
			else
				WFIFOW(fd,n*57+24)= sd->status.cart[i].card[3];
		}
		WFIFOL(fd,n*57+26)=sd->status.cart[i].limit;
		WFIFOW(fd,n*57+30)=0;
		WFIFOW(fd,n*57+32)=id->look;
		WFIFOB(fd,n*57+34)=0;
		WFIFOW(fd,n*57+35)=sd->status.cart[i].opt[0].id;
		WFIFOW(fd,n*57+37)=sd->status.cart[i].opt[0].val;
		WFIFOB(fd,n*57+39)=0;
		WFIFOW(fd,n*57+40)=sd->status.cart[i].opt[1].id;
		WFIFOW(fd,n*57+42)=sd->status.cart[i].opt[1].val;
		WFIFOB(fd,n*57+44)=0;
		WFIFOW(fd,n*57+45)=sd->status.cart[i].opt[2].id;
		WFIFOW(fd,n*57+47)=sd->status.cart[i].opt[2].val;
		WFIFOB(fd,n*57+49)=0;
		WFIFOW(fd,n*57+50)=sd->status.cart[i].opt[3].id;
		WFIFOW(fd,n*57+52)=sd->status.cart[i].opt[3].val;
		WFIFOB(fd,n*57+54)=0;
		WFIFOW(fd,n*57+55)=sd->status.cart[i].opt[4].id;
		WFIFOW(fd,n*57+57)=sd->status.cart[i].opt[4].val;
		WFIFOB(fd,n*57+59)=0;
		WFIFOB(fd,n*57+60)=sd->status.cart[i].identify+(sd->status.cart[i].attribute?2:0);
		n++;
	}
	if(n){
		WFIFOW(fd,2)=4+n*57;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#else
	WFIFOW(fd,0)=0xa0f;
	for(i=0,n=0;i<MAX_CART;i++){
		if(sd->status.cart[i].nameid<=0)
			continue;
		id = itemdb_search(sd->status.cart[i].nameid);
		if(!itemdb_isequip2(id))
			continue;
		WFIFOW(fd,n*67+4)=i+2;
		if(id->view_id > 0)
			WFIFOL(fd,n*67+6)=id->view_id;
		else
			WFIFOL(fd,n*67+6)=sd->status.cart[i].nameid;
		WFIFOB(fd,n*67+10)=id->type;
		WFIFOL(fd,n*67+11)=id->equip;
		WFIFOL(fd,n*67+15)=sd->status.cart[i].equip;
		WFIFOB(fd,n*67+19)=sd->status.cart[i].refine;
		if(itemdb_isspecial(sd->status.cart[i].card[0])) {
			if(id->flag.pet_egg) {
				WFIFOL(fd,n*67+20) = 0;
				WFIFOL(fd,n*67+24) = 0;
				WFIFOL(fd,n*67+28) = 0;
			} else {
				WFIFOL(fd,n*67+20) = sd->status.cart[i].card[0];
				WFIFOL(fd,n*67+24) = sd->status.cart[i].card[1];
				WFIFOL(fd,n*67+28) = sd->status.cart[i].card[2];
			}
			WFIFOL(fd,n*67+32) = sd->status.cart[i].card[3];
		} else {
			if(sd->status.cart[i].card[0] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[0])) > 0)
				WFIFOL(fd,n*67+20)= j;
			else
				WFIFOL(fd,n*67+20)= sd->status.cart[i].card[0];
			if(sd->status.cart[i].card[1] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[1])) > 0)
				WFIFOL(fd,n*67+24)= j;
			else
				WFIFOL(fd,n*67+24)= sd->status.cart[i].card[1];
			if(sd->status.cart[i].card[2] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[2])) > 0)
				WFIFOL(fd,n*67+28)= j;
			else
				WFIFOL(fd,n*67+28)= sd->status.cart[i].card[2];
			if(sd->status.cart[i].card[3] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[3])) > 0)
				WFIFOL(fd,n*67+32)= j;
			else
				WFIFOL(fd,n*67+32)= sd->status.cart[i].card[3];
		}
		WFIFOL(fd,n*67+36)=sd->status.cart[i].limit;
		WFIFOW(fd,n*67+40)=0;
		WFIFOW(fd,n*67+42)=id->look;
		WFIFOB(fd,n*67+44)=0;
		WFIFOW(fd,n*67+45)=sd->status.cart[i].opt[0].id;
		WFIFOW(fd,n*67+47)=sd->status.cart[i].opt[0].val;
		WFIFOB(fd,n*67+49)=0;
		WFIFOW(fd,n*67+50)=sd->status.cart[i].opt[1].id;
		WFIFOW(fd,n*67+52)=sd->status.cart[i].opt[1].val;
		WFIFOB(fd,n*67+54)=0;
		WFIFOW(fd,n*67+55)=sd->status.cart[i].opt[2].id;
		WFIFOW(fd,n*67+57)=sd->status.cart[i].opt[2].val;
		WFIFOB(fd,n*67+59)=0;
		WFIFOW(fd,n*67+60)=sd->status.cart[i].opt[3].id;
		WFIFOW(fd,n*67+62)=sd->status.cart[i].opt[3].val;
		WFIFOB(fd,n*67+64)=0;
		WFIFOW(fd,n*67+65)=sd->status.cart[i].opt[4].id;
		WFIFOW(fd,n*67+67)=sd->status.cart[i].opt[4].val;
		WFIFOB(fd,n*67+69)=0;
		WFIFOB(fd,n*67+70)=sd->status.cart[i].identify+(sd->status.cart[i].attribute?2:0);
		n++;
	}
	if(n){
		WFIFOW(fd,2)=4+n*67;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#endif

	return;
}

/*==========================================
 * �J�[�g�̃N���A
 *------------------------------------------
 */
void clif_cart_clear(struct map_session_data *sd)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0) = 0x12b;
	WFIFOSET(fd,packet_db[0x12b].len);

	return;
}

/*==========================================
 * �I�X�J��
 *------------------------------------------
 */
void clif_openvendingreq(struct map_session_data *sd, int num)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x12d;
	WFIFOW(fd,2)=num;
	WFIFOSET(fd,packet_db[0x12d].len);

	return;
}

/*==========================================
 * �I�X�Ŕ\��
 *------------------------------------------
 */
void clif_showvendingboard(struct block_list* bl, const char *shop_title, int fd)
{
	unsigned char buf[96];

	nullpo_retv(bl);

	WBUFW(buf,0)=0x131;
	WBUFL(buf,2)=bl->id;
	strncpy(WBUFP(buf,6), shop_title, 80);
	if(fd >= 0) {
		memcpy(WFIFOP(fd,0),buf,packet_db[0x131].len);
		WFIFOSET(fd,packet_db[0x131].len);
	} else {
		clif_send(buf,packet_db[0x131].len,bl,AREA_WOS);
	}

	return;
}

/*==========================================
 * �I�X�Ŕ���
 *------------------------------------------
 */
void clif_closevendingboard(struct block_list* bl, int fd)
{
	unsigned char buf[8];

	nullpo_retv(bl);

	WBUFW(buf,0)=0x132;
	WBUFL(buf,2)=bl->id;
	if(fd >= 0) {
		memcpy(WFIFOP(fd,0),buf,packet_db[0x132].len);
		WFIFOSET(fd,packet_db[0x132].len);
	} else {
		clif_send(buf,packet_db[0x132].len,bl,AREA_WOS);
	}

	return;
}

/*==========================================
 * �I�X�A�C�e�����X�g
 *------------------------------------------
 */
void clif_vendinglist(struct map_session_data *sd, struct map_session_data *vsd)
{
	struct item_data *data;
	int i, j, n, idx, fd;
	struct vending *vending;

	nullpo_retv(sd);
	nullpo_retv(vsd);
	nullpo_retv(vending = vsd->vending);

	fd=sd->fd;
#if PACKETVER < 20091208
	WFIFOW(fd,0)=0x133;
	WFIFOL(fd,4)=vsd->status.account_id;
	n = 0;
	for(i = 0; i < vsd->vend_num; i++) {
		if(vending[i].amount<=0)
			continue;
		WFIFOL(fd, 8+n*22)=vending[i].value;
		WFIFOW(fd,12+n*22)=vending[i].amount;
		WFIFOW(fd,14+n*22)=(idx = vending[i].index) + 2;
		if(vsd->status.cart[idx].nameid <= 0 || vsd->status.cart[idx].amount <= 0)
			continue;
		data = itemdb_search(vsd->status.cart[idx].nameid);
		WFIFOB(fd,16+n*22)=data->type;
		if(data->view_id > 0)
			WFIFOW(fd,17+n*22)=data->view_id;
		else
			WFIFOW(fd,17+n*22)=vsd->status.cart[idx].nameid;
		WFIFOB(fd,19+n*22)=vsd->status.cart[idx].identify;
		WFIFOB(fd,20+n*22)=vsd->status.cart[idx].attribute;
		WFIFOB(fd,21+n*22)=vsd->status.cart[idx].refine;
		if(itemdb_isspecial(vsd->status.cart[idx].card[0])) {
			if(data->flag.pet_egg) {
				WFIFOW(fd,22+n*22) = 0;
				WFIFOW(fd,24+n*22) = 0;
				WFIFOW(fd,26+n*22) = 0;
			} else {
				WFIFOW(fd,22+n*22) = vsd->status.cart[idx].card[0];
				WFIFOW(fd,24+n*22) = vsd->status.cart[idx].card[1];
				WFIFOW(fd,26+n*22) = vsd->status.cart[idx].card[2];
			}
			WFIFOW(fd,28+n*22) = vsd->status.cart[idx].card[3];
		} else {
			if(vsd->status.cart[idx].card[0] > 0 && (j=itemdb_viewid(vsd->status.cart[idx].card[0])) > 0)
				WFIFOW(fd,22+n*22)= j;
			else
				WFIFOW(fd,22+n*22)= vsd->status.cart[idx].card[0];
			if(vsd->status.cart[idx].card[1] > 0 && (j=itemdb_viewid(vsd->status.cart[idx].card[1])) > 0)
				WFIFOW(fd,24+n*22)= j;
			else
				WFIFOW(fd,24+n*22)= vsd->status.cart[idx].card[1];
			if(vsd->status.cart[idx].card[2] > 0 && (j=itemdb_viewid(vsd->status.cart[idx].card[2])) > 0)
				WFIFOW(fd,26+n*22)= j;
			else
				WFIFOW(fd,26+n*22)= vsd->status.cart[idx].card[2];
			if(vsd->status.cart[idx].card[3] > 0 && (j=itemdb_viewid(vsd->status.cart[idx].card[3])) > 0)
				WFIFOW(fd,28+n*22)= j;
			else
				WFIFOW(fd,28+n*22)= vsd->status.cart[idx].card[3];
		}
		n++;
	}
	if(n > 0){
		WFIFOW(fd,2)=8+n*22;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#elif PACKETVER < 20150513
	WFIFOW(fd,0)=0x800;
	WFIFOL(fd,4)=vsd->status.account_id;
	WFIFOL(fd,8)=vsd->vender_id;
	n = 0;
	for(i = 0; i < vsd->vend_num; i++) {
		if(vending[i].amount<=0)
			continue;
		WFIFOL(fd,12+n*22)=vending[i].value;
		WFIFOW(fd,16+n*22)=vending[i].amount;
		WFIFOW(fd,18+n*22)=(idx = vending[i].index) + 2;
		if(vsd->status.cart[idx].nameid <= 0 || vsd->status.cart[idx].amount <= 0)
			continue;
		data = itemdb_search(vsd->status.cart[idx].nameid);
		WFIFOB(fd,20+n*22)=data->type;
		if(data->view_id > 0)
			WFIFOW(fd,21+n*22)=data->view_id;
		else
			WFIFOW(fd,21+n*22)=vsd->status.cart[idx].nameid;
		WFIFOB(fd,23+n*22)=vsd->status.cart[idx].identify;
		WFIFOB(fd,24+n*22)=vsd->status.cart[idx].attribute;
		WFIFOB(fd,25+n*22)=vsd->status.cart[idx].refine;
		if(itemdb_isspecial(vsd->status.cart[idx].card[0])) {
			if(data->flag.pet_egg) {
				WFIFOW(fd,26+n*22) = 0;
				WFIFOW(fd,28+n*22) = 0;
				WFIFOW(fd,30+n*22) = 0;
			} else {
				WFIFOW(fd,26+n*22) = vsd->status.cart[idx].card[0];
				WFIFOW(fd,28+n*22) = vsd->status.cart[idx].card[1];
				WFIFOW(fd,30+n*22) = vsd->status.cart[idx].card[2];
			}
			WFIFOW(fd,32+n*22) = vsd->status.cart[idx].card[3];
		} else {
			if(vsd->status.cart[idx].card[0] > 0 && (j=itemdb_viewid(vsd->status.cart[idx].card[0])) > 0)
				WFIFOW(fd,26+n*22)= j;
			else
				WFIFOW(fd,26+n*22)= vsd->status.cart[idx].card[0];
			if(vsd->status.cart[idx].card[1] > 0 && (j=itemdb_viewid(vsd->status.cart[idx].card[1])) > 0)
				WFIFOW(fd,28+n*22)= j;
			else
				WFIFOW(fd,28+n*22)= vsd->status.cart[idx].card[1];
			if(vsd->status.cart[idx].card[2] > 0 && (j=itemdb_viewid(vsd->status.cart[idx].card[2])) > 0)
				WFIFOW(fd,30+n*22)= j;
			else
				WFIFOW(fd,30+n*22)= vsd->status.cart[idx].card[2];
			if(vsd->status.cart[idx].card[3] > 0 && (j=itemdb_viewid(vsd->status.cart[idx].card[3])) > 0)
				WFIFOW(fd,32+n*22)= j;
			else
				WFIFOW(fd,32+n*22)= vsd->status.cart[idx].card[3];
		}
		n++;
	}
	if(n > 0){
		WFIFOW(fd,2)=12+n*22;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#elif PACKETVER < 20160921
	WFIFOW(fd,0)=0x800;
	WFIFOL(fd,4)=vsd->status.account_id;
	WFIFOL(fd,8)=vsd->vender_id;
	n = 0;
	for(i = 0; i < vsd->vend_num; i++) {
		if(vending[i].amount<=0)
			continue;
		WFIFOL(fd,12+n*47)=vending[i].value;
		WFIFOW(fd,16+n*47)=vending[i].amount;
		WFIFOW(fd,18+n*47)=(idx = vending[i].index) + 2;
		if(vsd->status.cart[idx].nameid <= 0 || vsd->status.cart[idx].amount <= 0)
			continue;
		data = itemdb_search(vsd->status.cart[idx].nameid);
		WFIFOB(fd,20+n*47)=data->type;
		if(data->view_id > 0)
			WFIFOW(fd,21+n*47)=data->view_id;
		else
			WFIFOW(fd,21+n*47)=vsd->status.cart[idx].nameid;
		WFIFOB(fd,23+n*47)=vsd->status.cart[idx].identify;
		WFIFOB(fd,24+n*47)=vsd->status.cart[idx].attribute;
		WFIFOB(fd,25+n*47)=vsd->status.cart[idx].refine;
		if(itemdb_isspecial(vsd->status.cart[idx].card[0])) {
			if(data->flag.pet_egg) {
				WFIFOW(fd,26+n*47) = 0;
				WFIFOW(fd,28+n*47) = 0;
				WFIFOW(fd,30+n*47) = 0;
			} else {
				WFIFOW(fd,26+n*47) = vsd->status.cart[idx].card[0];
				WFIFOW(fd,28+n*47) = vsd->status.cart[idx].card[1];
				WFIFOW(fd,30+n*47) = vsd->status.cart[idx].card[2];
			}
			WFIFOW(fd,32+n*47) = vsd->status.cart[idx].card[3];
		} else {
			if(vsd->status.cart[idx].card[0] > 0 && (j=itemdb_viewid(vsd->status.cart[idx].card[0])) > 0)
				WFIFOW(fd,26+n*47)= j;
			else
				WFIFOW(fd,26+n*47)= vsd->status.cart[idx].card[0];
			if(vsd->status.cart[idx].card[1] > 0 && (j=itemdb_viewid(vsd->status.cart[idx].card[1])) > 0)
				WFIFOW(fd,28+n*47)= j;
			else
				WFIFOW(fd,28+n*47)= vsd->status.cart[idx].card[1];
			if(vsd->status.cart[idx].card[2] > 0 && (j=itemdb_viewid(vsd->status.cart[idx].card[2])) > 0)
				WFIFOW(fd,30+n*47)= j;
			else
				WFIFOW(fd,30+n*47)= vsd->status.cart[idx].card[2];
			if(vsd->status.cart[idx].card[3] > 0 && (j=itemdb_viewid(vsd->status.cart[idx].card[3])) > 0)
				WFIFOW(fd,32+n*47)= j;
			else
				WFIFOW(fd,32+n*47)= vsd->status.cart[idx].card[3];
		}
		WFIFOW(fd,n*47+34) = vsd->status.cart[idx].opt[0].id;
		WFIFOW(fd,n*47+36) = vsd->status.cart[idx].opt[0].val;
		WFIFOB(fd,n*47+38) = 0;
		WFIFOW(fd,n*47+39) = vsd->status.cart[idx].opt[1].id;
		WFIFOW(fd,n*47+41) = vsd->status.cart[idx].opt[1].val;
		WFIFOB(fd,n*47+43) = 0;
		WFIFOW(fd,n*47+44) = vsd->status.cart[idx].opt[2].id;
		WFIFOW(fd,n*47+46) = vsd->status.cart[idx].opt[2].val;
		WFIFOB(fd,n*47+48) = 0;
		WFIFOW(fd,n*47+49) = vsd->status.cart[idx].opt[3].id;
		WFIFOW(fd,n*47+51) = vsd->status.cart[idx].opt[3].val;
		WFIFOB(fd,n*47+53) = 0;
		WFIFOW(fd,n*47+54) = vsd->status.cart[idx].opt[4].id;
		WFIFOW(fd,n*47+56) = vsd->status.cart[idx].opt[4].val;
		WFIFOB(fd,n*47+58) = 0;
		n++;
	}
	if(n > 0){
		WFIFOW(fd,2)=12+n*47;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#elif PACKETVER < 20180704
	WFIFOW(fd,0)=0x800;
	WFIFOL(fd,4)=vsd->status.account_id;
	WFIFOL(fd,8)=vsd->vender_id;
	n = 0;
	for(i = 0; i < vsd->vend_num; i++) {
		if(vending[i].amount<=0)
			continue;
		WFIFOL(fd,12+n*53)=vending[i].value;
		WFIFOW(fd,16+n*53)=vending[i].amount;
		WFIFOW(fd,18+n*53)=(idx = vending[i].index) + 2;
		if(vsd->status.cart[idx].nameid <= 0 || vsd->status.cart[idx].amount <= 0)
			continue;
		data = itemdb_search(vsd->status.cart[idx].nameid);
		WFIFOB(fd,20+n*53)=data->type;
		if(data->view_id > 0)
			WFIFOW(fd,21+n*53)=data->view_id;
		else
			WFIFOW(fd,21+n*53)=vsd->status.cart[idx].nameid;
		WFIFOB(fd,23+n*53)=vsd->status.cart[idx].identify;
		WFIFOB(fd,24+n*53)=vsd->status.cart[idx].attribute;
		WFIFOB(fd,25+n*53)=vsd->status.cart[idx].refine;
		if(itemdb_isspecial(vsd->status.cart[idx].card[0])) {
			if(data->flag.pet_egg) {
				WFIFOW(fd,26+n*53) = 0;
				WFIFOW(fd,28+n*53) = 0;
				WFIFOW(fd,30+n*53) = 0;
			} else {
				WFIFOW(fd,26+n*53) = vsd->status.cart[idx].card[0];
				WFIFOW(fd,28+n*53) = vsd->status.cart[idx].card[1];
				WFIFOW(fd,30+n*53) = vsd->status.cart[idx].card[2];
			}
			WFIFOW(fd,32+n*53) = vsd->status.cart[idx].card[3];
		} else {
			if(vsd->status.cart[idx].card[0] > 0 && (j=itemdb_viewid(vsd->status.cart[idx].card[0])) > 0)
				WFIFOW(fd,26+n*53)= j;
			else
				WFIFOW(fd,26+n*53)= vsd->status.cart[idx].card[0];
			if(vsd->status.cart[idx].card[1] > 0 && (j=itemdb_viewid(vsd->status.cart[idx].card[1])) > 0)
				WFIFOW(fd,28+n*53)= j;
			else
				WFIFOW(fd,28+n*53)= vsd->status.cart[idx].card[1];
			if(vsd->status.cart[idx].card[2] > 0 && (j=itemdb_viewid(vsd->status.cart[idx].card[2])) > 0)
				WFIFOW(fd,30+n*53)= j;
			else
				WFIFOW(fd,30+n*53)= vsd->status.cart[idx].card[2];
			if(vsd->status.cart[idx].card[3] > 0 && (j=itemdb_viewid(vsd->status.cart[idx].card[3])) > 0)
				WFIFOW(fd,32+n*53)= j;
			else
				WFIFOW(fd,32+n*53)= vsd->status.cart[idx].card[3];
		}
		WFIFOW(fd,n*53+34) = vsd->status.cart[idx].opt[0].id;
		WFIFOW(fd,n*53+36) = vsd->status.cart[idx].opt[0].val;
		WFIFOB(fd,n*53+38) = 0;
		WFIFOW(fd,n*53+39) = vsd->status.cart[idx].opt[1].id;
		WFIFOW(fd,n*53+41) = vsd->status.cart[idx].opt[1].val;
		WFIFOB(fd,n*53+43) = 0;
		WFIFOW(fd,n*53+44) = vsd->status.cart[idx].opt[2].id;
		WFIFOW(fd,n*53+46) = vsd->status.cart[idx].opt[2].val;
		WFIFOB(fd,n*53+48) = 0;
		WFIFOW(fd,n*53+49) = vsd->status.cart[idx].opt[3].id;
		WFIFOW(fd,n*53+51) = vsd->status.cart[idx].opt[3].val;
		WFIFOB(fd,n*53+53) = 0;
		WFIFOW(fd,n*53+54) = vsd->status.cart[idx].opt[4].id;
		WFIFOW(fd,n*53+56) = vsd->status.cart[idx].opt[4].val;
		WFIFOB(fd,n*53+58) = 0;
		WFIFOL(fd,n*53+59) = pc_equippoint(sd,idx);
		WFIFOW(fd,n*53+63) = data->look;
		n++;
	}
	if(n > 0){
		WFIFOW(fd,2)=12+n*53;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#else
	WFIFOW(fd,0)=0x800;
	WFIFOL(fd,4)=vsd->status.account_id;
	WFIFOL(fd,8)=vsd->vender_id;
	n = 0;
	for(i = 0; i < vsd->vend_num; i++) {
		if(vending[i].amount<=0)
			continue;
		WFIFOL(fd,12+n*63)=vending[i].value;
		WFIFOW(fd,16+n*63)=vending[i].amount;
		WFIFOW(fd,18+n*63)=(idx = vending[i].index) + 2;
		if(vsd->status.cart[idx].nameid <= 0 || vsd->status.cart[idx].amount <= 0)
			continue;
		data = itemdb_search(vsd->status.cart[idx].nameid);
		WFIFOB(fd,20+n*63)=data->type;
		if(data->view_id > 0)
			WFIFOL(fd,21+n*63)=data->view_id;
		else
			WFIFOL(fd,21+n*63)=vsd->status.cart[idx].nameid;
		WFIFOB(fd,25+n*63)=vsd->status.cart[idx].identify;
		WFIFOB(fd,26+n*63)=vsd->status.cart[idx].attribute;
		WFIFOB(fd,27+n*63)=vsd->status.cart[idx].refine;
		if(itemdb_isspecial(vsd->status.cart[idx].card[0])) {
			if(data->flag.pet_egg) {
				WFIFOL(fd,28+n*63) = 0;
				WFIFOL(fd,32+n*63) = 0;
				WFIFOL(fd,36+n*63) = 0;
			} else {
				WFIFOL(fd,28+n*63) = vsd->status.cart[idx].card[0];
				WFIFOL(fd,32+n*63) = vsd->status.cart[idx].card[1];
				WFIFOL(fd,36+n*63) = vsd->status.cart[idx].card[2];
			}
			WFIFOL(fd,40+n*63) = vsd->status.cart[idx].card[3];
		} else {
			if(vsd->status.cart[idx].card[0] > 0 && (j=itemdb_viewid(vsd->status.cart[idx].card[0])) > 0)
				WFIFOL(fd,28+n*63)= j;
			else
				WFIFOL(fd,28+n*63)= vsd->status.cart[idx].card[0];
			if(vsd->status.cart[idx].card[1] > 0 && (j=itemdb_viewid(vsd->status.cart[idx].card[1])) > 0)
				WFIFOL(fd,32+n*63)= j;
			else
				WFIFOL(fd,32+n*63)= vsd->status.cart[idx].card[1];
			if(vsd->status.cart[idx].card[2] > 0 && (j=itemdb_viewid(vsd->status.cart[idx].card[2])) > 0)
				WFIFOL(fd,36+n*63)= j;
			else
				WFIFOL(fd,36+n*63)= vsd->status.cart[idx].card[2];
			if(vsd->status.cart[idx].card[3] > 0 && (j=itemdb_viewid(vsd->status.cart[idx].card[3])) > 0)
				WFIFOL(fd,40+n*63)= j;
			else
				WFIFOL(fd,40+n*63)= vsd->status.cart[idx].card[3];
		}
		WFIFOW(fd,n*63+44) = vsd->status.cart[idx].opt[0].id;
		WFIFOW(fd,n*63+46) = vsd->status.cart[idx].opt[0].val;
		WFIFOB(fd,n*63+48) = 0;
		WFIFOW(fd,n*63+49) = vsd->status.cart[idx].opt[1].id;
		WFIFOW(fd,n*63+51) = vsd->status.cart[idx].opt[1].val;
		WFIFOB(fd,n*63+53) = 0;
		WFIFOW(fd,n*63+54) = vsd->status.cart[idx].opt[2].id;
		WFIFOW(fd,n*63+56) = vsd->status.cart[idx].opt[2].val;
		WFIFOB(fd,n*63+58) = 0;
		WFIFOW(fd,n*63+59) = vsd->status.cart[idx].opt[3].id;
		WFIFOW(fd,n*63+61) = vsd->status.cart[idx].opt[3].val;
		WFIFOB(fd,n*63+63) = 0;
		WFIFOW(fd,n*63+64) = vsd->status.cart[idx].opt[4].id;
		WFIFOW(fd,n*63+66) = vsd->status.cart[idx].opt[4].val;
		WFIFOB(fd,n*63+68) = 0;
		WFIFOL(fd,n*63+69) = pc_equippoint(sd,idx);
		WFIFOW(fd,n*63+73) = data->look;
		n++;
	}
	if(n > 0){
		WFIFOW(fd,2)=12+n*63;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#endif

	return;
}

/*==========================================
 * �I�X�A�C�e���w�����s
 *------------------------------------------
 */
void clif_buyvending(struct map_session_data *sd, int idx, int amount, unsigned char fail)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x135;
	WFIFOW(fd,2)=idx+2;
	WFIFOW(fd,4)=amount;
	WFIFOB(fd,6)=fail;
	WFIFOSET(fd,packet_db[0x135].len);

	return;
}

/*==========================================
 * �I�X�J�ݐ����ʒm
 *------------------------------------------
 */
void clif_openvending_ack(struct map_session_data *sd)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xa28;
	WFIFOB(fd,2)=0;
	WFIFOSET(fd,packet_db[0xa28].len);
}

/*==========================================
 * �I�X�J�ݐ���
 *------------------------------------------
 */
int clif_openvending(struct map_session_data *sd)
{
	struct item_data *data;
	int i, j, n, idx, fd;
	struct vending *vending;

	nullpo_retr(0, sd);
	nullpo_retr(0, vending = sd->vending);

	fd=sd->fd;
	WFIFOW(fd,0)=0x136;
	WFIFOL(fd,4)=sd->bl.id;
	n = 0;
#if PACKETVER < 20150513
	for(i = 0; i < sd->vend_num; i++) {
		WFIFOL(fd, 8+n*22)=vending[i].value;
		WFIFOW(fd,12+n*22)=(idx = vending[i].index) + 2;
		WFIFOW(fd,14+n*22)=vending[i].amount;
		if(sd->status.cart[idx].nameid <= 0 || sd->status.cart[idx].amount <= 0)
			continue;
		data = itemdb_search(sd->status.cart[idx].nameid);
		WFIFOB(fd,16+n*22)=data->type;
		if(data->view_id > 0)
			WFIFOW(fd,17+n*22)=data->view_id;
		else
			WFIFOW(fd,17+n*22)=sd->status.cart[idx].nameid;
		WFIFOB(fd,19+n*22)=sd->status.cart[idx].identify;
		WFIFOB(fd,20+n*22)=sd->status.cart[idx].attribute;
		WFIFOB(fd,21+n*22)=sd->status.cart[idx].refine;
		if(itemdb_isspecial(sd->status.cart[idx].card[0])) {
			if(data->flag.pet_egg) {
				WFIFOW(fd,22+n*22)=0;
				WFIFOW(fd,24+n*22)=0;
				WFIFOW(fd,26+n*22)=0;
			} else {
				WFIFOW(fd,22+n*22)=sd->status.cart[idx].card[0];
				WFIFOW(fd,24+n*22)=sd->status.cart[idx].card[1];
				WFIFOW(fd,26+n*22)=sd->status.cart[idx].card[2];
			}
			WFIFOW(fd,28+n*22)=sd->status.cart[idx].card[3];
		} else {
			if(sd->status.cart[idx].card[0] > 0 && (j=itemdb_viewid(sd->status.cart[idx].card[0])) > 0)
				WFIFOW(fd,22+n*22)= j;
			else
				WFIFOW(fd,22+n*22)= sd->status.cart[idx].card[0];
			if(sd->status.cart[idx].card[1] > 0 && (j=itemdb_viewid(sd->status.cart[idx].card[1])) > 0)
				WFIFOW(fd,24+n*22)= j;
			else
				WFIFOW(fd,24+n*22)= sd->status.cart[idx].card[1];
			if(sd->status.cart[idx].card[2] > 0 && (j=itemdb_viewid(sd->status.cart[idx].card[2])) > 0)
				WFIFOW(fd,26+n*22)= j;
			else
				WFIFOW(fd,26+n*22)= sd->status.cart[idx].card[2];
			if(sd->status.cart[idx].card[3] > 0 && (j=itemdb_viewid(sd->status.cart[idx].card[3])) > 0)
				WFIFOW(fd,28+n*22)= j;
			else
				WFIFOW(fd,28+n*22)= sd->status.cart[idx].card[3];
		}
		n++;
	}
	if(n > 0){
		WFIFOW(fd,2)=8+n*22;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#elif PACKETVER < 20180704
	for(i = 0; i < sd->vend_num; i++) {
		WFIFOL(fd, 8+n*47)=vending[i].value;
		WFIFOW(fd,12+n*47)=(idx = vending[i].index) + 2;
		WFIFOW(fd,14+n*47)=vending[i].amount;
		if(sd->status.cart[idx].nameid <= 0 || sd->status.cart[idx].amount <= 0)
			continue;
		data = itemdb_search(sd->status.cart[idx].nameid);
		WFIFOB(fd,16+n*47)=data->type;
		if(data->view_id > 0)
			WFIFOW(fd,17+n*47)=data->view_id;
		else
			WFIFOW(fd,17+n*47)=sd->status.cart[idx].nameid;
		WFIFOB(fd,19+n*47)=sd->status.cart[idx].identify;
		WFIFOB(fd,20+n*47)=sd->status.cart[idx].attribute;
		WFIFOB(fd,21+n*47)=sd->status.cart[idx].refine;
		if(itemdb_isspecial(sd->status.cart[idx].card[0])) {
			if(data->flag.pet_egg) {
				WFIFOW(fd,22+n*47)=0;
				WFIFOW(fd,24+n*47)=0;
				WFIFOW(fd,26+n*47)=0;
			} else {
				WFIFOW(fd,22+n*47)=sd->status.cart[idx].card[0];
				WFIFOW(fd,24+n*47)=sd->status.cart[idx].card[1];
				WFIFOW(fd,26+n*47)=sd->status.cart[idx].card[2];
			}
			WFIFOW(fd,28+n*47)=sd->status.cart[idx].card[3];
		} else {
			if(sd->status.cart[idx].card[0] > 0 && (j=itemdb_viewid(sd->status.cart[idx].card[0])) > 0)
				WFIFOW(fd,22+n*47)= j;
			else
				WFIFOW(fd,22+n*47)= sd->status.cart[idx].card[0];
			if(sd->status.cart[idx].card[1] > 0 && (j=itemdb_viewid(sd->status.cart[idx].card[1])) > 0)
				WFIFOW(fd,24+n*47)= j;
			else
				WFIFOW(fd,24+n*47)= sd->status.cart[idx].card[1];
			if(sd->status.cart[idx].card[2] > 0 && (j=itemdb_viewid(sd->status.cart[idx].card[2])) > 0)
				WFIFOW(fd,26+n*47)= j;
			else
				WFIFOW(fd,26+n*47)= sd->status.cart[idx].card[2];
			if(sd->status.cart[idx].card[3] > 0 && (j=itemdb_viewid(sd->status.cart[idx].card[3])) > 0)
				WFIFOW(fd,28+n*47)= j;
			else
				WFIFOW(fd,28+n*47)= sd->status.cart[idx].card[3];
		}
		WFIFOW(fd,n*47+30) = sd->status.cart[idx].opt[0].id;
		WFIFOW(fd,n*47+32) = sd->status.cart[idx].opt[0].val;
		WFIFOB(fd,n*47+34) = 0;
		WFIFOW(fd,n*47+35) = sd->status.cart[idx].opt[1].id;
		WFIFOW(fd,n*47+37) = sd->status.cart[idx].opt[1].val;
		WFIFOB(fd,n*47+39) = 0;
		WFIFOW(fd,n*47+40) = sd->status.cart[idx].opt[2].id;
		WFIFOW(fd,n*47+42) = sd->status.cart[idx].opt[2].val;
		WFIFOB(fd,n*47+44) = 0;
		WFIFOW(fd,n*47+45) = sd->status.cart[idx].opt[3].id;
		WFIFOW(fd,n*47+47) = sd->status.cart[idx].opt[3].val;
		WFIFOB(fd,n*47+49) = 0;
		WFIFOW(fd,n*47+50) = sd->status.cart[idx].opt[4].id;
		WFIFOW(fd,n*47+52) = sd->status.cart[idx].opt[4].val;
		WFIFOB(fd,n*47+54) = 0;
		n++;
	}
	if(n > 0){
		WFIFOW(fd,2)=8+n*47;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#else
	for(i = 0; i < sd->vend_num; i++) {
		WFIFOL(fd, 8+n*57)=vending[i].value;
		WFIFOW(fd,12+n*57)=(idx = vending[i].index) + 2;
		WFIFOW(fd,14+n*57)=vending[i].amount;
		if(sd->status.cart[idx].nameid <= 0 || sd->status.cart[idx].amount <= 0)
			continue;
		data = itemdb_search(sd->status.cart[idx].nameid);
		WFIFOB(fd,16+n*57)=data->type;
		if(data->view_id > 0)
			WFIFOL(fd,17+n*57)=data->view_id;
		else
			WFIFOL(fd,17+n*57)=sd->status.cart[idx].nameid;
		WFIFOB(fd,21+n*57)=sd->status.cart[idx].identify;
		WFIFOB(fd,22+n*57)=sd->status.cart[idx].attribute;
		WFIFOB(fd,23+n*57)=sd->status.cart[idx].refine;
		if(itemdb_isspecial(sd->status.cart[idx].card[0])) {
			if(data->flag.pet_egg) {
				WFIFOL(fd,24+n*57)=0;
				WFIFOL(fd,28+n*57)=0;
				WFIFOL(fd,32+n*57)=0;
			} else {
				WFIFOL(fd,24+n*57)=sd->status.cart[idx].card[0];
				WFIFOL(fd,28+n*57)=sd->status.cart[idx].card[1];
				WFIFOL(fd,32+n*57)=sd->status.cart[idx].card[2];
			}
			WFIFOL(fd,36+n*57)=sd->status.cart[idx].card[3];
		} else {
			if(sd->status.cart[idx].card[0] > 0 && (j=itemdb_viewid(sd->status.cart[idx].card[0])) > 0)
				WFIFOL(fd,24+n*57)= j;
			else
				WFIFOL(fd,24+n*57)= sd->status.cart[idx].card[0];
			if(sd->status.cart[idx].card[1] > 0 && (j=itemdb_viewid(sd->status.cart[idx].card[1])) > 0)
				WFIFOL(fd,28+n*57)= j;
			else
				WFIFOL(fd,28+n*57)= sd->status.cart[idx].card[1];
			if(sd->status.cart[idx].card[2] > 0 && (j=itemdb_viewid(sd->status.cart[idx].card[2])) > 0)
				WFIFOL(fd,32+n*57)= j;
			else
				WFIFOL(fd,32+n*57)= sd->status.cart[idx].card[2];
			if(sd->status.cart[idx].card[3] > 0 && (j=itemdb_viewid(sd->status.cart[idx].card[3])) > 0)
				WFIFOL(fd,36+n*57)= j;
			else
				WFIFOL(fd,36+n*57)= sd->status.cart[idx].card[3];
		}
		WFIFOW(fd,n*57+40) = sd->status.cart[idx].opt[0].id;
		WFIFOW(fd,n*57+42) = sd->status.cart[idx].opt[0].val;
		WFIFOB(fd,n*57+44) = 0;
		WFIFOW(fd,n*57+45) = sd->status.cart[idx].opt[1].id;
		WFIFOW(fd,n*57+47) = sd->status.cart[idx].opt[1].val;
		WFIFOB(fd,n*57+49) = 0;
		WFIFOW(fd,n*57+50) = sd->status.cart[idx].opt[2].id;
		WFIFOW(fd,n*57+52) = sd->status.cart[idx].opt[2].val;
		WFIFOB(fd,n*57+54) = 0;
		WFIFOW(fd,n*57+55) = sd->status.cart[idx].opt[3].id;
		WFIFOW(fd,n*57+57) = sd->status.cart[idx].opt[3].val;
		WFIFOB(fd,n*57+59) = 0;
		WFIFOW(fd,n*57+60) = sd->status.cart[idx].opt[4].id;
		WFIFOW(fd,n*57+62) = sd->status.cart[idx].opt[4].val;
		WFIFOB(fd,n*57+64) = 0;
		n++;
	}
	if(n > 0){
		WFIFOW(fd,2)=8+n*57;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#endif

#if PACKETVER >= 20150513
	clif_openvending_ack(sd);
#endif

	return n;
}

/*==========================================
 * �I�X�A�C�e���̔���
 *------------------------------------------
 */
void clif_vendingreport(struct map_session_data *sd, int idx, int amount, int account_id, int char_id, int value)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
#if PACKETVER < 20140129
	WFIFOW(fd,0)=0x137;
	WFIFOW(fd,2)=idx+2;
	WFIFOW(fd,4)=amount;
	WFIFOSET(fd,packet_db[0x137].len);
#else
	WFIFOW(fd, 0)=0x9e5;
	WFIFOW(fd, 2)=idx+2;
	WFIFOW(fd, 4)=amount;
	WFIFOL(fd, 6)=char_id;
	WFIFOL(fd,10)=account_id;
	WFIFOL(fd,14)=value;
	WFIFOSET(fd,packet_db[0x9e5].len);
#endif

	return;
}

/*==========================================
 * �p�[�e�B�쐬����
 *------------------------------------------
 */
void clif_party_created(struct map_session_data *sd, unsigned char flag)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xfa;
	WFIFOB(fd,2)=flag;
	WFIFOSET(fd,packet_db[0xfa].len);

	return;
}

/*==========================================
 * �p�[�e�B���C�����
 *------------------------------------------
 */
void clif_party_main_info(struct party *p, int fd)
{
#if PACKETVER < 20170502
	const int cmd = 0x1e9;
	unsigned char buf[81];
#elif PACKETVER < 20171207
	const int cmd = 0xa43;
	unsigned char buf[85];
#else
	const int cmd = 0xae4;
	unsigned char buf[89];
#endif
	int i;
	struct map_session_data *sd = NULL;

	nullpo_retv(p);

	for(i=0; i<MAX_PARTY && !p->member[i].sd; i++);

	if(i >= MAX_PARTY)
		return;
	sd = p->member[i].sd;

	WBUFW(buf,0)  = cmd;
#if PACKETVER < 20170502
	WBUFL(buf,2)  = p->member[i].account_id;
	WBUFL(buf,6)  = (p->member[i].leader)? 0: 1;
	WBUFW(buf,10) = (sd)? sd->bl.x: 0;
	WBUFW(buf,12) = (sd)? sd->bl.y: 0;
	WBUFB(buf,14) = (p->member[i].online)? 0: 1;
	memcpy(WBUFP(buf,15), p->name, 24);
	memcpy(WBUFP(buf,39), p->member[i].name, 24);
	memcpy(WBUFP(buf,63), p->member[i].map, 16);
	WBUFB(buf,79) = (p->item&1)? 1: 0;
	WBUFB(buf,80) = (p->item&2)? 1: 0;
#elif PACKETVER < 20171207
	WBUFL(buf,2)  = p->member[i].account_id;
	WBUFL(buf,6)  = (p->member[i].leader)? 0: 1;
	WBUFW(buf,10) = p->member[i].class_;
	WBUFW(buf,12) = p->member[i].lv;
	WBUFW(buf,14) = (sd)? sd->bl.x: 0;
	WBUFW(buf,16) = (sd)? sd->bl.y: 0;
	WBUFB(buf,18) = (p->member[i].online)? 0: 1;
	memcpy(WBUFP(buf,19), p->name, 24);
	memcpy(WBUFP(buf,43), p->member[i].name, 24);
	memcpy(WBUFP(buf,67), p->member[i].map, 16);
	WBUFB(buf,83) = (p->item&1)? 1: 0;
	WBUFB(buf,84) = (p->item&2)? 1: 0;
#else
	WBUFL(buf,2)  = p->member[i].account_id;
	WBUFL(buf,6)  = p->member[i].char_id;
	WBUFL(buf,10)  = (p->member[i].leader)? 0: 1;
	WBUFW(buf,14) = p->member[i].class_;
	WBUFW(buf,16) = p->member[i].lv;
	WBUFW(buf,18) = (sd)? sd->bl.x: 0;
	WBUFW(buf,20) = (sd)? sd->bl.y: 0;
	WBUFB(buf,22) = (p->member[i].online)? 0: 1;
	memcpy(WBUFP(buf,23), p->name, 24);
	memcpy(WBUFP(buf,47), p->member[i].name, 24);
	memcpy(WBUFP(buf,71), p->member[i].map, 16);
	WBUFB(buf,87) = (p->item&1)? 1: 0;
	WBUFB(buf,88) = (p->item&2)? 1: 0;
#endif

	if(fd >= 0){	// fd���ݒ肳��Ă�Ȃ炻��ɑ���
		memcpy(WFIFOP(fd,0),buf,packet_db[cmd].len);
		WFIFOSET(fd,packet_db[cmd].len);
		return;
	}
	else {
		clif_send(buf,packet_db[cmd].len,&sd->bl,PARTY);
	}

	return;
}

/*==========================================
 * �p�[�e�B��񑗐M
 *------------------------------------------
 */
void clif_party_info(struct party *p, int fd)
{
	int i,c;
	struct map_session_data *sd=NULL;
#if PACKETVER < 20170502
	unsigned char buf[28+MAX_PARTY*46];
#elif PACKETVER < 20171207
	unsigned char buf[28+MAX_PARTY*50+6];
#else
	unsigned char buf[28+MAX_PARTY*54+6];
#endif

	nullpo_retv(p);

#if PACKETVER < 20170502
	WBUFW(buf,0)=0xfb;
	memcpy(WBUFP(buf,4),p->name,24);
	for(i=c=0;i<MAX_PARTY;i++){
		struct party_member *m=&p->member[i];
		if(m->account_id > 0){
			if(sd==NULL) sd=m->sd;
			WBUFL(buf,28+c*46)=m->account_id;
			memcpy(WBUFP(buf,28+c*46+ 4),m->name,24);
			memcpy(WBUFP(buf,28+c*46+28),m->map,16);
			WBUFB(buf,28+c*46+44)=(m->leader)?0:1;
			WBUFB(buf,28+c*46+45)=(m->online)?0:1;
			c++;
		}
	}
	WBUFW(buf,2)=28+c*46;
#elif PACKETVER < 20171207
	WBUFW(buf,0)=0xa44;
	memcpy(WBUFP(buf,4),p->name,24);
	for(i=c=0;i<MAX_PARTY;i++){
		struct party_member *m=&p->member[i];
		if(m->account_id > 0){
			if(sd==NULL) sd=m->sd;
			WBUFL(buf,28+c*50)=m->account_id;
			memcpy(WBUFP(buf,28+c*50+ 4),m->name,24);
			memcpy(WBUFP(buf,28+c*50+28),m->map,16);
			WBUFB(buf,28+c*50+44)=(m->leader)?0:1;
			WBUFB(buf,28+c*50+45)=(m->online)?0:1;
			WBUFW(buf,28+c*50+46)=m->class_;
			WBUFW(buf,28+c*50+48)=m->lv;
			c++;
		}
	}
	WBUFB(buf,28+c*50) = (p->item & 1) ? 1 : 0;
	WBUFB(buf,28+c*50+1) = (p->item & 2) ? 1 : 0;
	WBUFL(buf,28+c*50+2) = 0; // unknown
	WBUFW(buf,2)=28+c*50+6;
#else
	WBUFW(buf,0)=0xae5;
	memcpy(WBUFP(buf,4),p->name,24);
	for(i=c=0;i<MAX_PARTY;i++){
		struct party_member *m=&p->member[i];
		if(m->account_id > 0){
			if(sd==NULL) sd=m->sd;
			WBUFL(buf,28+c*54)=m->account_id;
			WBUFL(buf,28+c*54+ 4)=m->char_id;
			memcpy(WBUFP(buf,28+c*54+ 8),m->name,24);
			memcpy(WBUFP(buf,28+c*54+32),m->map,16);
			WBUFB(buf,28+c*54+48)=(m->leader)?0:1;
			WBUFB(buf,28+c*54+49)=(m->online)?0:1;
			WBUFW(buf,28+c*54+50)=m->class_;
			WBUFW(buf,28+c*54+52)=m->lv;
			c++;
		}
	}
	WBUFB(buf,28+c*54) = (p->item & 1) ? 1 : 0;
	WBUFB(buf,28+c*54+1) = (p->item & 2) ? 1 : 0;
	WBUFL(buf,28+c*54+2) = 0; // unknown
	WBUFW(buf,2)=28+c*54+6;
#endif
	if(fd >= 0){	// fd���ݒ肳��Ă�Ȃ炻��ɑ���
		memcpy(WFIFOP(fd,0),buf,WBUFW(buf,2));
		WFIFOSET(fd,WFIFOW(fd,2));
		return;
	}
	else if(sd != NULL) {
		clif_send(buf,WBUFW(buf,2),&sd->bl,PARTY);
	}

	return;
}

/*==========================================
 * �p�[�e�B���U
 *------------------------------------------
 */
void clif_party_invite(struct map_session_data *sd, struct map_session_data *tsd, const char *name)
{
	int fd;

	nullpo_retv(sd);
	nullpo_retv(tsd);

	fd=tsd->fd;

#if PACKETVER < 20070904
	WFIFOW(fd,0)=0xfe;
	WFIFOL(fd,2)=sd->status.account_id;
	memcpy(WFIFOP(fd,6),name,24);
	WFIFOSET(fd,packet_db[0xfe].len);
#else
	WFIFOW(fd,0)=0x2c6;
	WFIFOL(fd,2)=sd->status.account_id;
	memcpy(WFIFOP(fd,6),name,24);
	WFIFOSET(fd,packet_db[0x2c6].len);
#endif

	return;
}

/*==========================================
 * �p�[�e�B���U����
 *------------------------------------------
 */
void clif_party_inviteack(struct map_session_data *sd, const char *nick, unsigned char flag)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;

#if PACKETVER < 20070904
	WFIFOW(fd, 0)=0xfd;
	strncpy(WFIFOP(fd,2),nick,24);
	WFIFOB(fd,26)=flag;
	WFIFOSET(fd,packet_db[0xfd].len);
#else
	WFIFOW(fd, 0)=0x2c5;
	strncpy(WFIFOP(fd,2),nick,24);
	WFIFOL(fd,26)=flag;
	WFIFOSET(fd,packet_db[0x2c5].len);
#endif

	return;
}

/*==========================================
 * �p�[�e�B�����v����
 *------------------------------------------
 */
void clif_send_partyconfig(struct map_session_data *sd)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0) = 0x2c9;
	WFIFOB(fd,2) = (unsigned char)sd->status.refuse_partyinvite;
	WFIFOSET(fd,packet_db[0x2c9].len);

	return;
}

/*==========================================
 * �p�[�e�B�ݒ著�M
 * flag & 0x001=exp�ύX�~�X
 *        0x010=item�ύX�~�X�i���݂͑��݂��Ȃ��j
 *        0x100=��l�ɂ̂ݑ��M
 *------------------------------------------
 */
void clif_party_option(struct party *p, struct map_session_data *sd, int flag)
{
	unsigned char buf[16];

	nullpo_retv(p);

	if(sd==NULL && flag==0){
		int i;
		for(i=0;i<MAX_PARTY;i++)
			if((sd=map_id2sd(p->member[i].account_id))!=NULL)
				break;
	}
	if(sd==NULL)
		return;

#if PACKETVER < 20090603
	WBUFW(buf,0)=0x101;
	WBUFL(buf,2)=((flag&0x01)?2:p->exp);
	if(flag == 0) {
		clif_send(buf,packet_db[0x101].len,&sd->bl,PARTY);
	} else {
		memcpy(WFIFOP(sd->fd,0),buf,packet_db[0x101].len);
		WFIFOSET(sd->fd,packet_db[0x101].len);
	}
#else
	WBUFW(buf,0)=0x7d8;
	WBUFL(buf,2)=((flag&0x01)?2:p->exp);
	WBUFB(buf,6)=(p->item&1)?1:0;
	WBUFB(buf,7)=(p->item&2)?1:0;
	if(flag == 0) {
		clif_send(buf,packet_db[0x7d8].len,&sd->bl,PARTY);
	} else {
		memcpy(WFIFOP(sd->fd,0),buf,packet_db[0x7d8].len);
		WFIFOSET(sd->fd,packet_db[0x7d8].len);
	}
#endif

	return;
}

/*==========================================
 * �p�[�e�B�E�ށi�E�ޑO�ɌĂԂ��Ɓj
 *------------------------------------------
 */
void clif_party_leaved(struct party *p, struct map_session_data *sd, int account_id, const char *name, int flag)
{
	unsigned char buf[32];

	nullpo_retv(p);

	WBUFW(buf,0)=0x105;
	WBUFL(buf,2)=account_id;
	memcpy(WBUFP(buf,6),name,24);
	WBUFB(buf,30)=flag&0x0f;

	if((flag&0xf0)==0){
		if(sd==NULL) {
			int i;
			for(i=0;i<MAX_PARTY;i++) {
				if((sd=p->member[i].sd)!=NULL)
					break;
			}
		}
		if(sd!=NULL)
			clif_send(buf,packet_db[0x105].len,&sd->bl,PARTY);
	}else if(sd!=NULL){
		memcpy(WFIFOP(sd->fd,0),buf,packet_db[0x105].len);
		WFIFOSET(sd->fd,packet_db[0x105].len);
	}

	return;
}

/*==========================================
 * �p�[�e�B���b�Z�[�W���M
 *------------------------------------------
 */
void clif_party_message(struct party *p, int account_id, const char *mes, size_t len)
{
	unsigned char buf[1024];
	struct map_session_data *sd = NULL;
	int i;

	nullpo_retv(p);

	for(i=0;i<MAX_PARTY;i++){
		if((sd=p->member[i].sd)!=NULL)
			break;
	}
	if(sd==NULL)
		return;

	if(len > sizeof(buf) - 8)
		len = sizeof(buf) - 8;

	WBUFW(buf,0)=0x109;
	WBUFW(buf,2)=(unsigned short)(len+8);
	WBUFL(buf,4)=account_id;
	memcpy(WBUFP(buf,8),mes,len);
	clif_send(buf,len+8,&sd->bl,PARTY);

	return;
}

/*==========================================
 * �p�[�e�B���W�ʒm
 *------------------------------------------
 */
void clif_party_xy(struct map_session_data *sd)
{
	unsigned char buf[16];

	nullpo_retv(sd);

	WBUFW(buf,0)=0x107;
	WBUFL(buf,2)=sd->status.account_id;
	WBUFW(buf,6)=sd->bl.x;
	WBUFW(buf,8)=sd->bl.y;
	clif_send(buf,packet_db[0x107].len,&sd->bl,PARTY_SAMEMAP_WOS);

	return;
}

/*==========================================
 * �p�[�e�BHP�ʒm
 *------------------------------------------
 */
void clif_party_hp(struct map_session_data *sd)
{
	unsigned char buf[16];

	nullpo_retv(sd);

#if PACKETVER < 20100223
	WBUFW(buf,0)=0x106;
	WBUFL(buf,2)=sd->status.account_id;
	WBUFW(buf,6)=(sd->status.max_hp > 0x7fff)? (short)((atn_bignumber)sd->status.hp * 0x7fff / sd->status.max_hp): sd->status.hp;
	WBUFW(buf,8)=(sd->status.max_hp > 0x7fff)? 0x7fff: sd->status.max_hp;
	clif_send(buf,packet_db[0x106].len,&sd->bl,PARTY_AREA_WOS);
#else
	WBUFW(buf,0)=0x80e;
	WBUFL(buf,2)=sd->status.account_id;
	WBUFL(buf,6)=sd->status.hp;
	WBUFL(buf,10)=sd->status.max_hp;
	clif_send(buf,packet_db[0x80e].len,&sd->bl,PARTY_AREA_WOS);
#endif

	return;
}

/*==========================================
 * �p�[�e�B�ꏊ�ړ��i���g�p�j
 *------------------------------------------
 */
/*void clif_party_move(struct party *p, struct map_session_data *sd, unsigned char online)
{
	unsigned char buf[96];

	nullpo_retv(sd);
	nullpo_retv(p);

	WBUFW(buf, 0)=0x104;
	WBUFL(buf, 2)=sd->status.account_id;
	WBUFL(buf, 6)=0;
	WBUFW(buf,10)=sd->bl.x;
	WBUFW(buf,12)=sd->bl.y;
	WBUFB(buf,14)=!online;
	memcpy(WBUFP(buf,15),p->name,24);
	memcpy(WBUFP(buf,39),sd->status.name,24);
	memcpy(WBUFP(buf,63),map[sd->bl.m].name,16);
	clif_send(buf,packet_db[0x104].len,&sd->bl,PARTY);

	return;
}*/

/*==========================================
 * �U�����邽�߂Ɉړ����K�v
 *------------------------------------------
 */
void clif_movetoattack(struct map_session_data *sd, struct block_list *bl)
{
	int fd;

	nullpo_retv(sd);
	nullpo_retv(bl);

	fd=sd->fd;
	WFIFOW(fd, 0)=0x139;
	WFIFOL(fd, 2)=bl->id;
	WFIFOW(fd, 6)=bl->x;
	WFIFOW(fd, 8)=bl->y;
	WFIFOW(fd,10)=sd->bl.x;
	WFIFOW(fd,12)=sd->bl.y;
	WFIFOW(fd,14)=sd->range.attackrange;
	WFIFOSET(fd,packet_db[0x139].len);

	return;
}

/*==========================================
 * �����G�t�F�N�g
 *------------------------------------------
 */
void clif_produceeffect(struct map_session_data *sd, unsigned short flag, int nameid)
{
	int view,fd;

	nullpo_retv(sd);

	// ���O�̓o�^�Ƒ��M���ɂ��Ă���
	if( map_charid2nick(sd->status.char_id)==NULL )
		map_addchariddb(sd->status.char_id,sd->status.name,sd->status.account_id,clif_getip(),clif_getport());
	clif_solved_charname(sd,sd->status.char_id);

	fd=sd->fd;
#if PACKETVER < 20180704
	WFIFOW(fd, 0)=0x18f;
	WFIFOW(fd, 2)=flag;
	if((view = itemdb_viewid(nameid)) > 0)
		WFIFOW(fd, 4)=view;
	else
		WFIFOW(fd, 4)=nameid;
	WFIFOSET(fd,packet_db[0x18f].len);
#else
	WFIFOW(fd, 0)=0x18f;
	WFIFOW(fd, 2)=flag;
	if((view = itemdb_viewid(nameid)) > 0)
		WFIFOL(fd, 4)=view;
	else
		WFIFOL(fd, 4)=nameid;
	WFIFOSET(fd,packet_db[0x18f].len);
#endif

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_catch_process(struct map_session_data *sd)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x19e;
	WFIFOSET(fd,packet_db[0x19e].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_pet_rulet(struct map_session_data *sd, unsigned char data)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x1a0;
	WFIFOB(fd,2)=data;
	WFIFOSET(fd,packet_db[0x1a0].len);

	return;
}

/*==========================================
 * pet�����X�g�쐬
 *------------------------------------------
 */
void clif_sendegg(struct map_session_data *sd)
{
	int n=0,fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x1a6;
	if(sd->status.pet_id <= 0) {
		int i, j;
		for(i=j=0;i<MAX_INVENTORY && j<sd->inventory_num;i++) {
			if(sd->status.inventory[i].nameid <= 0 || sd->inventory_data[i] == NULL)
				continue;
			j++;
			if(!sd->inventory_data[i]->flag.pet_egg ||
			   sd->status.inventory[i].amount<=0)
				continue;
			WFIFOW(fd,n*2+4)=i+2;
			n++;
		}
	}
	WFIFOW(fd,2)=4+n*2;
	WFIFOSET(fd,WFIFOW(fd,2));

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_send_petdata(struct map_session_data *sd, unsigned char type, int param)
{
	int fd;

	nullpo_retv(sd);

	if(!sd->pd)
		return; // �V���x0�ɂȂ��NULL

	fd=sd->fd;
	WFIFOW(fd,0)=0x1a4;
	WFIFOB(fd,2)=type;
	WFIFOL(fd,3)=sd->pd->bl.id;
	WFIFOL(fd,7)=param;
	WFIFOSET(fd,packet_db[0x1a4].len);

	return;
}

/*==========================================
 * pet�̔��^��񑗐M
 *------------------------------------------
 */
void clif_send_pethair(struct map_session_data *sd)
{
	unsigned char buf[11];

	nullpo_retv(sd);

	if(!sd->pd)
		return; // �V���x0�ɂȂ��NULL

	WBUFW(buf,0)=0x1a4;
	WBUFB(buf,2)=5;
	WBUFL(buf,3)=sd->pd->bl.id;
	WBUFL(buf,7)=100;
	clif_send(buf,packet_db[0x1a4].len,&sd->bl,AREA);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_send_petstatus(struct map_session_data *sd)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;

#if PACKETVER < 20081126
	WFIFOW(fd,0)=0x1a2;
	memcpy(WFIFOP(fd,2),sd->pet.name,24);
	WFIFOB(fd,26)=(battle_config.pet_rename == 1)? 0:sd->pet.rename_flag;
	WFIFOW(fd,27)=sd->pet.level;
	WFIFOW(fd,29)=sd->pet.hungry;
	WFIFOW(fd,31)=sd->pet.intimate;
	WFIFOW(fd,33)=sd->pet.equip;
	WFIFOSET(fd,packet_db[0x1a2].len);
#else
	WFIFOW(fd,0)=0x1a2;
	memcpy(WFIFOP(fd,2),sd->pet.name,24);
	WFIFOB(fd,26)=(battle_config.pet_rename == 1)? 0:sd->pet.rename_flag;
	WFIFOW(fd,27)=sd->pet.level;
	WFIFOW(fd,29)=sd->pet.hungry;
	WFIFOW(fd,31)=sd->pet.intimate;
	WFIFOW(fd,33)=sd->pet.equip;
	WFIFOW(fd,35)=sd->pet.class_;
	WFIFOSET(fd,packet_db[0x1a2].len);
#endif

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_pet_emotion(struct pet_data *pd,int param)
{
	unsigned char buf[16];
	struct map_session_data *sd;

	nullpo_retv(pd);
	nullpo_retv(sd = pd->msd);

	WBUFW(buf,0)=0x1aa;
	WBUFL(buf,2)=pd->bl.id;
	if(param >= 100 && sd->petDB->talk_convert_class) {
		if(sd->petDB->talk_convert_class < 0)
			return;
		if(sd->petDB->talk_convert_class > 0) {
			param -= (pd->class_ - 100)*100;
			param += (sd->petDB->talk_convert_class - 100)*100;
		}
	}
	WBUFL(buf,6)=param;
	clif_send(buf,packet_db[0x1aa].len,&pd->bl,AREA);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_pet_performance(struct block_list *bl, int param)
{
	unsigned char buf[16];

	nullpo_retv(bl);

	WBUFW(buf,0)=0x1a4;
	WBUFB(buf,2)=4;
	WBUFL(buf,3)=bl->id;
	WBUFL(buf,7)=param;
	clif_send(buf,packet_db[0x1a4].len,bl,AREA);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_pet_equip(struct pet_data *pd, int nameid)
{
	unsigned char buf[16];
	int view;

	nullpo_retv(pd);

	WBUFW(buf,0)=0x1a4;
	WBUFB(buf,2)=3;
	WBUFL(buf,3)=pd->bl.id;
	if((view = itemdb_viewid(nameid)) > 0)
		WBUFL(buf,7)=view;
	else
		WBUFL(buf,7)=nameid;
	clif_send(buf,packet_db[0x1a4].len,&pd->bl,AREA);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_pet_food(struct map_session_data *sd, int foodid, unsigned char fail)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
#if PACKETVER < 20180704
	WFIFOW(fd,0)=0x1a3;
	WFIFOB(fd,2)=fail;
	WFIFOW(fd,3)=foodid;
	WFIFOSET(fd,packet_db[0x1a3].len);
#else
	WFIFOW(fd,0)=0x1a3;
	WFIFOB(fd,2)=fail;
	WFIFOL(fd,3)=foodid;
	WFIFOSET(fd,packet_db[0x1a3].len);
#endif

	return;
}

/*==========================================
 * �I�[�g�X�y�� ���X�g���M
 *------------------------------------------
 */
void clif_autospell(struct map_session_data *sd, int skilllv)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd, 0)=0x1cd;

	if(skilllv>0 && pc_checkskill2(sd,MG_NAPALMBEAT)>0)
		WFIFOL(fd,2)= MG_NAPALMBEAT;
	else
		WFIFOL(fd,2)= 0;
	if(skilllv>1 && pc_checkskill2(sd,MG_COLDBOLT)>0)
		WFIFOL(fd,6)= MG_COLDBOLT;
	else
		WFIFOL(fd,6)= 0;
	if(skilllv>1 && pc_checkskill2(sd,MG_FIREBOLT)>0)
		WFIFOL(fd,10)= MG_FIREBOLT;
	else
		WFIFOL(fd,10)= 0;
	if(skilllv>1 && pc_checkskill2(sd,MG_LIGHTNINGBOLT)>0)
		WFIFOL(fd,14)= MG_LIGHTNINGBOLT;
	else
		WFIFOL(fd,14)= 0;
	if(skilllv>4 && pc_checkskill2(sd,MG_SOULSTRIKE)>0)
		WFIFOL(fd,18)= MG_SOULSTRIKE;
	else
		WFIFOL(fd,18)= 0;
	if(skilllv>7 && pc_checkskill2(sd,MG_FIREBALL)>0)
		WFIFOL(fd,22)= MG_FIREBALL;
	else
		WFIFOL(fd,22)= 0;
	if(skilllv>9 && pc_checkskill2(sd,MG_FROSTDIVER)>0)
		WFIFOL(fd,26)= MG_FROSTDIVER;
	else
		WFIFOL(fd,26)= 0;

	WFIFOSET(fd,packet_db[0x1cd].len);

	return;
}

/*==========================================
 * �f�B�{�[�V�����̐���
 *------------------------------------------
 */
void clif_devotion(struct map_session_data *sd)
{
	unsigned char buf[32];
	int n;

	nullpo_retv(sd);

	WBUFW(buf,0)=0x1cf;
	WBUFL(buf,2)=sd->bl.id;
	for(n=0;n<5;n++)
		WBUFL(buf,6+4*n)=sd->dev.val2[n];
	WBUFW(buf,26)=8;
	clif_send(buf,packet_db[0x1cf].len,&sd->bl,AREA);

	return;
}

/*==========================================
 * ����
 *------------------------------------------
 */
void clif_spiritball(struct map_session_data *sd)
{
	unsigned char buf[8];

	nullpo_retv(sd);

	WBUFW(buf,0)=0x1d0;
	WBUFL(buf,2)=sd->bl.id;
	WBUFW(buf,6)=sd->spiritball.num;
	clif_send(buf,packet_db[0x1d0].len,&sd->bl,AREA);

	return;
}

/*==========================================
 * ����(�z���p)
 *------------------------------------------
 */
void clif_spiritball2(struct homun_data *hd)
{
	unsigned char buf[8];

	nullpo_retv(hd);

	WBUFW(buf,0)=0x1d0;
	WBUFL(buf,2)=hd->bl.id;
	WBUFW(buf,6)=hd->spiritball;
	clif_send(buf,packet_db[0x1d0].len,&hd->bl,AREA);

	return;
}

/*==========================================
 * �R�C��
 *------------------------------------------
 */
void clif_coin(struct map_session_data *sd)
{
	unsigned char buf[8];

	nullpo_retv(sd);

	WBUFW(buf,0)=0x1d0;
	WBUFL(buf,2)=sd->bl.id;
	WBUFW(buf,6)=sd->coin.num;
	clif_send(buf,packet_db[0x1d0].len,&sd->bl,AREA);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_combo_delay(struct block_list *bl, int wait)
{
	unsigned char buf[16];

	nullpo_retv(bl);

	WBUFW(buf,0)=0x1d2;
	WBUFL(buf,2)=bl->id;
	WBUFL(buf,6)=wait;
	clif_send(buf,packet_db[0x1d2].len,bl,AREA);

	return;
}

/*==========================================
 * ���n���
 *------------------------------------------
 */
void clif_bladestop(struct block_list *src, int dst_id, int flag)
{
	unsigned char buf[16];

	nullpo_retv(src);

	WBUFW(buf,0)=0x1d1;
	WBUFL(buf,2)=src->id;
	WBUFL(buf,6)=dst_id;
	WBUFL(buf,10)=flag;
	clif_send(buf,packet_db[0x1d1].len,src,AREA);

	return;
}

/*==========================================
 * �S�X�y���̌��ʕ\��
 *------------------------------------------
 */
void clif_gospel_message(struct map_session_data *sd, int type)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0) = 0x215;
	WFIFOL(fd,2) = type;
	WFIFOSET(fd,packet_db[0x215].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_changemapcell(int m, int x, int y, int cell_type, int type)
{
	struct block_list bl;
	unsigned char buf[24];

	memset(&bl, 0, sizeof(bl));
	bl.m = m;
	bl.x = x;
	bl.y = y;

	WBUFW(buf,0) = 0x192;
	WBUFW(buf,2) = x;
	WBUFW(buf,4) = y;
	WBUFW(buf,6) = cell_type;
	memcpy(WBUFP(buf,8),map[m].name,16);
	clif_send(buf,packet_db[0x192].len,&bl,(type == 0) ? AREA : ALL_SAMEMAP);

	return;
}

/*==========================================
 * MVP�G�t�F�N�g
 *------------------------------------------
 */
void clif_mvp_effect(struct block_list *bl)
{
	unsigned char buf[8];

	nullpo_retv(bl);

	WBUFW(buf,0)=0x10c;
	WBUFL(buf,2)=bl->id;
	clif_send(buf,packet_db[0x10c].len,bl,AREA);

	return;
}

/*==========================================
 * MVP�A�C�e���擾
 *------------------------------------------
 */
void clif_mvp_item(struct map_session_data *sd, int nameid)
{
	int view,fd;

	nullpo_retv(sd);

	fd=sd->fd;
#if PACKETVER < 20180704
	WFIFOW(fd,0)=0x10a;
	if((view = itemdb_viewid(nameid)) > 0)
		WFIFOW(fd,2)=view;
	else
		WFIFOW(fd,2)=nameid;
	WFIFOSET(fd,packet_db[0x10a].len);
#else
	WFIFOW(fd,0)=0x10a;
	if((view = itemdb_viewid(nameid)) > 0)
		WFIFOL(fd,2)=view;
	else
		WFIFOL(fd,2)=nameid;
	WFIFOSET(fd,packet_db[0x10a].len);
#endif

	return;
}

/*==========================================
 * MVP�A�C�e���d�ʃI�[�o�[
 *------------------------------------------
 */
void clif_mvp_fail_item(struct map_session_data *sd)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x10d;
	WFIFOSET(fd,packet_db[0x10d].len);

	return;
}

/*==========================================
 * MVP�o���l�擾
 *------------------------------------------
 */
void clif_mvp_exp(struct map_session_data *sd, int exp)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x10b;
	WFIFOL(fd,2)=exp;
	WFIFOSET(fd,packet_db[0x10b].len);

	return;
}

/*==========================================
 * �M���h�쐬�ےʒm
 *------------------------------------------
 */
void clif_guild_created(struct map_session_data *sd, unsigned char flag)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x167;
	WFIFOB(fd,2)=flag;
	WFIFOSET(fd,packet_db[0x167].len);

	return;
}

/*==========================================
 * �M���h�����ʒm
 *------------------------------------------
 */
void clif_guild_belonginfo(struct map_session_data *sd, struct guild *g)
{
	int ps,fd;

	nullpo_retv(sd);
	nullpo_retv(g);

	ps=guild_getposition(sd,g);
	if(ps < 0)
		return;

	fd=sd->fd;
	WFIFOW(fd,0)=0x16c;
	WFIFOL(fd,2)=g->guild_id;
	WFIFOL(fd,6)=g->emblem_id;
	WFIFOL(fd,10)=g->position[ps].mode;
	WFIFOB(fd,14)=(strcmp(sd->status.name, g->master))? 0: 1;
	WFIFOL(fd,15)=0;	// unknown
	memcpy(WFIFOP(fd,19),g->name,24);
	WFIFOSET(fd,packet_db[0x16c].len);

	return;
}

/*==========================================
 * �M���h�����o���O�C���ʒm
 *------------------------------------------
 */
void clif_guild_memberlogin_notice(struct guild *g, int idx, unsigned char flag)
{
	unsigned char buf[32];

	nullpo_retv(g);

#if PACKETVER < 20070212
	WBUFW(buf, 0)=0x16d;
	WBUFL(buf, 2)=g->member[idx].account_id;
	WBUFL(buf, 6)=g->member[idx].char_id;
	WBUFL(buf,10)=flag;
	if(g->member[idx].sd==NULL){
		struct map_session_data *sd=guild_getavailablesd(g);
		if(sd!=NULL)
			clif_send(buf,packet_db[0x16d].len,&sd->bl,GUILD);
	}else
		clif_send(buf,packet_db[0x16d].len,&g->member[idx].sd->bl,GUILD_WOS);
#else
	WBUFW(buf, 0)=0x1f2;
	WBUFL(buf, 2)=g->member[idx].account_id;
	WBUFL(buf, 6)=g->member[idx].char_id;
	WBUFL(buf,10)=flag;
	WBUFW(buf,14)=g->member[idx].gender;
	WBUFW(buf,16)=g->member[idx].hair;
	WBUFW(buf,18)=g->member[idx].hair_color;
	if(g->member[idx].sd==NULL){
		struct map_session_data *sd=guild_getavailablesd(g);
		if(sd!=NULL)
			clif_send(buf,packet_db[0x1f2].len,&sd->bl,GUILD);
	}else
		clif_send(buf,packet_db[0x1f2].len,&g->member[idx].sd->bl,GUILD_WOS);
#endif

	return;
}

/*==========================================
 * �M���h�}�X�^�[�ʒm(14d�ւ̉���)
 *------------------------------------------
 */
static void clif_guild_masterormember(struct map_session_data *sd)
{
	int type=0x57,fd;
	struct guild *g;

	nullpo_retv(sd);

	g=guild_search(sd->status.guild_id);
	if(g!=NULL && strcmp(g->master,sd->status.name)==0)
		type=0xd7;

	fd=sd->fd;
	WFIFOW(fd,0)=0x14e;
	WFIFOL(fd,2)=type;
	WFIFOSET(fd,packet_db[0x14e].len);

	return;
}

/*==========================================
 * �M���h��{���
 *------------------------------------------
 */
void clif_guild_basicinfo(struct map_session_data *sd, struct guild *g)
{
	int fd;

	nullpo_retv(sd);
	nullpo_retv(g);

	fd=sd->fd;
#if PACKETVER < 20160622
	WFIFOW(fd, 0)=0x1b6;//0x150;
	WFIFOL(fd, 2)=g->guild_id;
	WFIFOL(fd, 6)=g->guild_lv;
	WFIFOL(fd,10)=g->connect_member;
	WFIFOL(fd,14)=g->max_member;
	WFIFOL(fd,18)=g->average_lv;
	WFIFOL(fd,22)=g->exp;
	WFIFOL(fd,26)=g->next_exp;
	WFIFOL(fd,30)=0;	// ��[
	WFIFOL(fd,34)=0;	// VW�i���i�̈����H�F�����O���t���E�j
	WFIFOL(fd,38)=0;	// RF�i���`�̓x�����H�F�����O���t�㉺�j
	WFIFOL(fd,42)=g->emblem_id;
	memcpy(WFIFOP(fd,46),g->name,24);
	memcpy(WFIFOP(fd,70),g->master,24);
	strncpy(WFIFOP(fd,94),"",20);	// �{���n
	WFIFOSET(fd,packet_db[0x1b6].len);
#else
	WFIFOW(fd, 0)=0xa84;//0x150;
	WFIFOL(fd, 2)=g->guild_id;
	WFIFOL(fd, 6)=g->guild_lv;
	WFIFOL(fd,10)=g->connect_member;
	WFIFOL(fd,14)=g->max_member;
	WFIFOL(fd,18)=g->average_lv;
	WFIFOL(fd,22)=g->exp;
	WFIFOL(fd,26)=g->next_exp;
	WFIFOL(fd,30)=0;	// ��[
	WFIFOL(fd,34)=0;	// VW�i���i�̈����H�F�����O���t���E�j
	WFIFOL(fd,38)=0;	// RF�i���`�̓x�����H�F�����O���t�㉺�j
	WFIFOL(fd,42)=g->emblem_id;
	memcpy(WFIFOP(fd,46),g->name,24);
	strncpy(WFIFOP(fd,70),"",20);	// �{���n
	WFIFOL(fd,90)=g->member[0].char_id;  // leader
	WFIFOSET(fd,packet_db[0xa84].len);
#endif

	return;
}

/*==========================================
 * �M���h����/�G�Ώ��
 *------------------------------------------
 */
void clif_guild_allianceinfo(struct map_session_data *sd, struct guild *g)
{
	int fd,i,c;

	nullpo_retv(sd);
	nullpo_retv(g);

	fd=sd->fd;
	WFIFOW(fd, 0)=0x14c;
	c = 0;
	for(i = 0; i < MAX_GUILDALLIANCE; i++) {
		struct guild_alliance *a=&g->alliance[i];
		if(a->guild_id>0){
			WFIFOL(fd,c*32+4)=a->opposition;
			WFIFOL(fd,c*32+8)=a->guild_id;
			memcpy(WFIFOP(fd,c*32+12),a->name,24);
			c++;
		}
	}
	WFIFOW(fd, 2)=c*32+4;
	WFIFOSET(fd,WFIFOW(fd,2));

	return;
}

/*==========================================
 * �M���h�����o�[���X�g
 *------------------------------------------
 */
void clif_guild_memberlist(struct map_session_data *sd, struct guild *g)
{
	int fd,i,c;

	nullpo_retv(sd);
	nullpo_retv(g);

	fd=sd->fd;
#if PACKETVER < 20161026
	WFIFOW(fd, 0)=0x154;
	c = 0;
	for(i = 0; i < g->max_member; i++) {
		struct guild_member *m=&g->member[i];
		if(m->account_id==0)
			continue;
		WFIFOL(fd,c*104+ 4)=m->account_id;
		WFIFOL(fd,c*104+ 8)=m->char_id;
		WFIFOW(fd,c*104+12)=m->hair;
		WFIFOW(fd,c*104+14)=m->hair_color;
		WFIFOW(fd,c*104+16)=m->gender;
		WFIFOW(fd,c*104+18)=m->class_;
		WFIFOW(fd,c*104+20)=m->lv;
		WFIFOL(fd,c*104+22)=m->exp;
		WFIFOL(fd,c*104+26)=(int)m->online;
		WFIFOL(fd,c*104+30)=m->position;
		memset(WFIFOP(fd,c*104+34),0,50);	// �����H
		memcpy(WFIFOP(fd,c*104+84),m->name,24);
		c++;
	}
	WFIFOW(fd, 2)=c*104+4;
	WFIFOSET(fd,WFIFOW(fd,2));
#else
	WFIFOW(fd, 0)=0xaa5;
	c = 0;
	for(i = 0; i < g->max_member; i++) {
		struct guild_member *m=&g->member[i];
		if(m->account_id==0)
			continue;
		WFIFOL(fd,c*34+ 4)=m->account_id;
		WFIFOL(fd,c*34+ 8)=m->char_id;
		WFIFOW(fd,c*34+12)=m->hair;
		WFIFOW(fd,c*34+14)=m->hair_color;
		WFIFOW(fd,c*34+16)=m->gender;
		WFIFOW(fd,c*34+18)=m->class_;
		WFIFOW(fd,c*34+20)=m->lv;
		WFIFOL(fd,c*34+22)=m->exp;
		WFIFOL(fd,c*34+26)=(int)m->online;
		WFIFOL(fd,c*34+30)=m->position;
		WFIFOL(fd,c*34+34)=0;	//TODO: m->last_login
		c++;
	}
	WFIFOW(fd, 2)=c*34+4;
	WFIFOSET(fd,WFIFOW(fd,2));
#endif

	return;
}

/*==========================================
 * �M���h��E�����X�g
 *------------------------------------------
 */
static void clif_guild_positionnamelist(struct map_session_data *sd, struct guild *g)
{
	int i,fd;

	nullpo_retv(sd);
	nullpo_retv(g);

	fd=sd->fd;
	WFIFOW(fd, 0)=0x166;
	for(i=0;i<MAX_GUILDPOSITION;i++){
		WFIFOL(fd,i*28+4)=i;
		memcpy(WFIFOP(fd,i*28+8),g->position[i].name,24);
	}
	WFIFOW(fd,2)=i*28+4;
	WFIFOSET(fd,WFIFOW(fd,2));

	return;
}

/*==========================================
 * �M���h��E��񃊃X�g
 *------------------------------------------
 */
static void clif_guild_positioninfolist(struct map_session_data *sd, struct guild *g)
{
	int i,fd;

	nullpo_retv(sd);
	nullpo_retv(g);

	fd=sd->fd;
	WFIFOW(fd,0)=0x160;
	for(i=0;i<MAX_GUILDPOSITION;i++){
		struct guild_position *p=&g->position[i];
		WFIFOL(fd,i*16+ 4)=i;
		WFIFOL(fd,i*16+ 8)=p->mode;
		WFIFOL(fd,i*16+12)=i;
		WFIFOL(fd,i*16+16)=p->exp_mode;
	}
	WFIFOW(fd,2)=i*16+4;
	WFIFOSET(fd,WFIFOW(fd,2));

	return;
}

/*==========================================
 * �M���h��E�ύX�ʒm
 *------------------------------------------
 */
void clif_guild_positionchanged(struct guild *g, int idx)
{
	struct map_session_data *sd;
	unsigned char buf[48];

	nullpo_retv(g);

	if( (sd = guild_getavailablesd(g)) == NULL )
		return;

	WBUFW(buf, 0)=0x174;
	WBUFW(buf, 2)=44;
	WBUFL(buf, 4)=idx;
	WBUFL(buf, 8)=g->position[idx].mode;
	WBUFL(buf,12)=idx;
	WBUFL(buf,16)=g->position[idx].exp_mode;
	memcpy(WBUFP(buf,20),g->position[idx].name,24);
	clif_send(buf,WBUFW(buf,2),&sd->bl,GUILD);

	return;
}

/*==========================================
 * �M���h�����o�ύX�ʒm
 *------------------------------------------
 */
void clif_guild_memberpositionchanged(struct guild *g, int idx)
{
	struct map_session_data *sd;
	unsigned char buf[16];

	nullpo_retv(g);

	if( (sd = guild_getavailablesd(g)) == NULL )
		return;

	WBUFW(buf, 0)=0x156;
	WBUFW(buf, 2)=16;
	WBUFL(buf, 4)=g->member[idx].account_id;
	WBUFL(buf, 8)=g->member[idx].char_id;
	WBUFL(buf,12)=g->member[idx].position;
	clif_send(buf,WBUFW(buf,2),&sd->bl,GUILD);

	return;
}

/*==========================================
 * �M���h�G���u�������M
 *------------------------------------------
 */
void clif_guild_emblem(struct map_session_data *sd, struct guild *g)
{
	int fd;

	nullpo_retv(sd);
	nullpo_retv(g);

	if(g->emblem_len <= 0)
		return;

	fd=sd->fd;
	WFIFOW(fd,0)=0x152;
	WFIFOW(fd,2)=g->emblem_len+12;
	WFIFOL(fd,4)=g->guild_id;
	WFIFOL(fd,8)=g->emblem_id;
	memcpy(WFIFOP(fd,12),g->emblem_data,g->emblem_len);
	WFIFOSET(fd,WFIFOW(fd,2));

	return;
}

/*==========================================
 * �M���h�X�L�����M
 *------------------------------------------
 */
void clif_guild_skillinfo(struct map_session_data *sd, struct guild *g)
{
	int fd,i,id,c = 0;

	nullpo_retv(sd);
	nullpo_retv(g);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x162;
	WFIFOW(fd,4) = g->skill_point;
	for(i = 0; i < MAX_GUILDSKILL; i++) {
		if((id = g->skill[i].id) > 0) {
			WFIFOW(fd,c*37+ 6) = id;
			WFIFOL(fd,c*37+ 8) = guild_skill_get_inf(id);
			WFIFOW(fd,c*37+12) = g->skill[i].lv;
			WFIFOW(fd,c*37+14) = skill_get_sp(id,g->skill[i].lv);
			WFIFOW(fd,c*37+16) = skill_get_range(id,g->skill[i].lv);
			memset(WFIFOP(fd,c*37+18),0,24);
			if(g->skill[i].lv < guild_get_skilltree_max(id))
				WFIFOB(fd,c*37+42) = 1;
			else
				WFIFOB(fd,c*37+42) = 0;
			c++;
		}
	}
	WFIFOW(fd,2) = c*37+6;
	WFIFOSET(fd,WFIFOW(fd,2));

	return;
}

/*==========================================
 * �M���h���m���M
 *------------------------------------------
 */
void clif_guild_notice(struct map_session_data *sd, struct guild *g)
{
	int fd;

	nullpo_retv(sd);
	nullpo_retv(g);

	if(*g->mes1==0 && *g->mes2==0)
		return;

	fd=sd->fd;
	WFIFOW(fd,0)=0x16f;
	memcpy(WFIFOP(fd,2),g->mes1,60);
	memcpy(WFIFOP(fd,62),g->mes2,120);
	WFIFOSET(fd,packet_db[0x16f].len);

	return;
}

/*==========================================
 * �M���h�����o���U
 *------------------------------------------
 */
void clif_guild_invite(struct map_session_data *sd, struct guild *g)
{
	int fd;

	nullpo_retv(sd);
	nullpo_retv(g);

	fd=sd->fd;
	WFIFOW(fd,0)=0x16a;
	WFIFOL(fd,2)=g->guild_id;
	memcpy(WFIFOP(fd,6),g->name,24);
	WFIFOSET(fd,packet_db[0x16a].len);

	return;
}

/*==========================================
 * �M���h�����o���U����
 *------------------------------------------
 */
void clif_guild_inviteack(struct map_session_data *sd, unsigned char flag)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x169;
	WFIFOB(fd,2)=flag;	// 0: in an other guild, 1: it was denied, 2: join, 3: guild has no more available place
	WFIFOSET(fd,packet_db[0x169].len);

	return;
}

/*==========================================
 * �M���h�����o�E�ޒʒm
 *------------------------------------------
 */
void clif_guild_leave(struct map_session_data *sd, const char *name, const char *mes)
{
	unsigned char buf[72];

	nullpo_retv(sd);

	WBUFW(buf, 0)=0x15a;
	memcpy(WBUFP(buf, 2),name,24);
	memcpy(WBUFP(buf,26),mes,40);
	clif_send(buf,packet_db[0x15a].len,&sd->bl,GUILD);

	return;
}

/*==========================================
 * �M���h�����o�Ǖ��ʒm
 *------------------------------------------
 */
void clif_guild_explusion(struct map_session_data *sd, const char *name, const char *mes)
{
	unsigned char buf[96];

	nullpo_retv(sd);

#if PACKETVER < 20100803
	WBUFW(buf, 0)=0x15c;
	memcpy(WBUFP(buf, 2),name,24);
	memcpy(WBUFP(buf,26),mes,40);
	strncpy(WBUFP(buf,66),"dummy",24);
	clif_send(buf,packet_db[0x15c].len,&sd->bl,GUILD);
#else
	WBUFW(buf, 0)=0x839;
	memcpy(WBUFP(buf, 2),name,24);
	memcpy(WBUFP(buf,26),mes,40);
	clif_send(buf,packet_db[0x839].len,&sd->bl,GUILD);
#endif

	return;
}

/*==========================================
 * �M���h�Ǖ������o���X�g
 *------------------------------------------
 */
static void clif_guild_explusionlist(struct map_session_data *sd, struct guild *g)
{
	int fd,i,c=0;

	nullpo_retv(sd);
	nullpo_retv(g);

	fd=sd->fd;

#if PACKETVER < 20100803
	WFIFOW(fd,0)=0x163;
	for(i = 0; i < MAX_GUILDEXPLUSION; i++) {
		struct guild_explusion *e=&g->explusion[i];
		if(e->account_id>0){
			memcpy(WFIFOP(fd,c*88+ 4),e->name,24);
			strncpy(WFIFOP(fd,c*88+28),"dummy",24);
			memcpy(WFIFOP(fd,c*88+52),e->mes,40);
			c++;
		}
	}
	WFIFOW(fd,2)=c*88+4;
	WFIFOSET(fd,WFIFOW(fd,2));
#else
	WFIFOW(fd,0)=0x163;
	for(i = 0; i < MAX_GUILDEXPLUSION; i++) {
		struct guild_explusion *e=&g->explusion[i];
		if(e->account_id>0){
			memcpy(WFIFOP(fd,c*64+ 4),e->name,24);
			memcpy(WFIFOP(fd,c*64+28),e->mes,40);
			c++;
		}
	}
	WFIFOW(fd,2)=c*64+4;
	WFIFOSET(fd,WFIFOW(fd,2));
#endif

	return;
}

/*==========================================
 * �M���h��b
 *------------------------------------------
 */
void clif_guild_message(struct guild *g, const char *mes, size_t len)
{
	struct map_session_data *sd;
	unsigned char *buf;

	nullpo_retv(g);

	if( (sd = guild_getavailablesd(g)) == NULL )
		return;

	buf = (unsigned char *)aMalloc(len+4);
	WBUFW(buf, 0)=0x17f;
	WBUFW(buf, 2)=(unsigned short)(len+4);
	memcpy(WBUFP(buf,4),mes,len);
	clif_send(buf,WBUFW(buf,2),&sd->bl,GUILD);

	aFree(buf);

	return;
}

/*==========================================
 * �M���h�X�L������U��ʒm
 *------------------------------------------
 */
void clif_guild_skillup(struct map_session_data *sd, int skill_num, int lv, int flag)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;

#if PACKETVER < 20090715
	WFIFOW(fd,0) = 0x10e;
	WFIFOW(fd,2) = skill_num;
	WFIFOW(fd,4) = lv;
	WFIFOW(fd,6) = skill_get_sp(skill_num,lv);
	WFIFOW(fd,8) = skill_get_range(skill_num,lv);
	WFIFOB(fd,10) = flag;
	WFIFOSET(fd,packet_db[0x10e].len);
#else
	WFIFOW(fd,0) = 0x7e1;
	WFIFOW(fd,2) = skill_num;
	WFIFOL(fd,4) = 0;
	WFIFOW(fd,8) = lv;
	WFIFOW(fd,10) = skill_get_sp(skill_num,lv);
	WFIFOW(fd,12) = skill_get_range(skill_num,lv);
	WFIFOB(fd,14) = flag;
	WFIFOSET(fd,packet_db[0x7e1].len);
#endif

	return;
}

/*==========================================
 * �M���h�����v��
 *------------------------------------------
 */
void clif_guild_reqalliance(struct map_session_data *sd, int account_id, const char *name)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x171;
	WFIFOL(fd,2)=account_id;
	memcpy(WFIFOP(fd,6),name,24);
	WFIFOSET(fd,packet_db[0x171].len);

	return;
}

/*==========================================
 * �M���h��������
 *------------------------------------------
 */
void clif_guild_allianceack(struct map_session_data *sd, unsigned int flag)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x173;
	WFIFOL(fd,2)=flag;
	WFIFOSET(fd,packet_db[0x173].len);

	return;
}

/*==========================================
 * �M���h�֌W�����ʒm
 *------------------------------------------
 */
void clif_guild_delalliance(struct map_session_data *sd, int guild_id, int flag)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x184;
	WFIFOL(fd,2)=guild_id;
	WFIFOL(fd,6)=flag;
	WFIFOSET(fd,packet_db[0x184].len);

	return;
}

/*==========================================
 * �M���h�G�Ό���
 *------------------------------------------
 */
void clif_guild_oppositionack(struct map_session_data *sd, unsigned char flag)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x181;
	WFIFOB(fd,2)=flag;
	WFIFOSET(fd,packet_db[0x181].len);

	return;
}

/*==========================================
 * �M���h�֌W�ǉ�
 *------------------------------------------
 */
/*void clif_guild_allianceadded(struct guild *g,int idx)
{
	struct map_session_data *sd;
	unsigned char buf[36];

	nullpo_retv(g);

	if( (sd = guild_getavailablesd(g)) == NULL )
		return;

	WBUFW(buf,0)=0x185;
	WBUFL(buf,2)=g->alliance[idx].opposition;
	WBUFL(buf,6)=g->alliance[idx].guild_id;
	memcpy(WBUFP(buf,10),g->alliance[idx].name,24);
	clif_send(buf,packet_db[0x185].len,&sd->bl,GUILD);

	return;
}*/

/*==========================================
 * �M���h���U�ʒm
 *------------------------------------------
 */
void clif_guild_broken(struct map_session_data *sd, unsigned int flag)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x15e;
	WFIFOL(fd,2)=flag;
	WFIFOSET(fd,packet_db[0x15e].len);

	return;
}

/*==========================================
 * �M���h�����o�[�̈ʒu���W���M
 *------------------------------------------
 */
void clif_guild_xy(struct map_session_data *sd)
{
	unsigned char buf[10];

	nullpo_retv(sd);

	WBUFW(buf,0)=0x1eb;
	WBUFL(buf,2)=sd->status.account_id;
	WBUFW(buf,6)=sd->bl.x;
	WBUFW(buf,8)=sd->bl.y;
	clif_send(buf,packet_db[0x1eb].len,&sd->bl,GUILD_SAMEMAP_WOS);

	return;
}

/*==========================================
 * �G���[�V����
 *------------------------------------------
 */
void clif_emotion(struct block_list *bl,int type)
{
	unsigned char buf[8];

	nullpo_retv(bl);

	WBUFW(buf,0)=0xc0;
	WBUFL(buf,2)=bl->id;
	WBUFB(buf,6)=type;
	clif_send(buf,packet_db[0xc0].len,bl,AREA);

	return;
}

void clif_emotion_self(struct map_session_data *sd,struct block_list *bl,int type)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0) = 0xc0;
	WFIFOL(fd,2)=bl->id;
	WFIFOB(fd,6)=type;
	WFIFOSET(fd,packet_db[0xc0].len);

	return;
}

/*==========================================
 * �g�[�L�[�{�b�N�X
 *------------------------------------------
 */
void clif_talkiebox(struct block_list *bl,const char* talkie)
{
	unsigned char buf[86];

	nullpo_retv(bl);

	WBUFW(buf,0)=0x191;
	WBUFL(buf,2)=bl->id;
	memcpy(WBUFP(buf,6),talkie,80);
	clif_send(buf,packet_db[0x191].len,bl,AREA);

	return;
}

/*==========================================
 * �����G�t�F�N�g
 *------------------------------------------
 */
void clif_wedding_effect(struct block_list *bl)
{
	unsigned char buf[6];

	nullpo_retv(bl);

	WBUFW(buf,0)=0x1ea;
	WBUFL(buf,2)=bl->id;
	clif_send(buf,packet_db[0x1ea].len,bl,AREA);

	return;
}

/*==========================================
 * ���Ȃ��Ɉ��������g�p�����O����
 *------------------------------------------
 */
void clif_callpartner(struct map_session_data *sd)
{
	unsigned char buf[26];
	char *p;

	nullpo_retv(sd);

	if(sd->status.partner_id <= 0)
		return;

	WBUFW(buf,0)=0x1e6;
	p = map_charid2nick(sd->status.partner_id);
	if(p)
		memcpy(WBUFP(buf,2),p,24);
	else
		strncpy(WBUFP(buf,2),"",24);
	clif_send(buf,packet_db[0x1e6].len,&sd->bl,AREA);

	return;
}

/*==========================================
 * ���������ʒm
 *------------------------------------------
 */
void clif_divorced(struct map_session_data *sd, const char *name)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0) = 0x205;
	strncpy(WFIFOP(fd,2),name,24);
	WFIFOSET(fd,packet_db[0x205].len);

	return;
}

/*==========================================
 * ����/����
 *------------------------------------------
 */
void clif_sitting(struct block_list *bl, int sit)
{
	unsigned char buf[32];

	nullpo_retv(bl);

	WBUFW(buf,0)  = 0x8a;
	WBUFL(buf,2)  = bl->id;
	WBUFB(buf,26) = (sit)? 2: 3;
	clif_send(buf,packet_db[0x8a].len,bl,AREA);

	return;
}

/*==========================================
 * ����
 *------------------------------------------
 */
void clif_onlymessage(const char *mes, size_t len)
{
	unsigned char *buf = (unsigned char *)aMalloc(len+8);

	switch (battle_config.mes_send_type) {
		case 0:	// �M���h��b
			WBUFW(buf, 0)=0x17f;
			WBUFW(buf, 2)=(unsigned short)(len+4);
			memcpy(WBUFP(buf,4),mes,len);
			break;
		case 1:	// �I�[�v����b
			WBUFW(buf, 0)=0x8d;
			WBUFW(buf, 2)=(unsigned short)(len+8);
			WBUFL(buf, 4)=0;
			memcpy(WBUFP(buf,8),mes,len);
			break;
		case 2:	// �p�[�e�B��b
			WBUFW(buf, 0)=0x109;
			WBUFW(buf, 2)=(unsigned short)(len+8);
			WBUFL(buf, 4)=0xffffffff;	// account_id��0���Ɩ������Ȃ̂Ń_�~�[�����Ă���
			memcpy(WBUFP(buf,8),mes,len);
			break;
		case 3:	// �I�[�v��GM��b
			WBUFW(buf, 0)=0x8d;
			WBUFW(buf, 2)=(unsigned short)(len+8);
			WBUFL(buf, 4)=pc_get_gm_account_dummy();	// �_�~�[�pGM�A�J�E���g������
			memcpy(WBUFP(buf,8),mes,len);
			break;
		default:
			aFree(buf);
			return;
	}
	clif_send(buf,WBUFW(buf,2),NULL,ALL_CLIENT);
	aFree(buf);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_GM_kickack(struct map_session_data *sd, int id)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xcd;
	WFIFOL(fd,2)=id;
	WFIFOSET(fd,packet_db[0xcd].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_GM_kick(struct map_session_data *sd, struct map_session_data *tsd, int type)
{
	int fd;

	nullpo_retv(tsd);

	if(type)
		clif_GM_kickack(sd,tsd->status.account_id);

	fd = tsd->fd;
	clif_disconnect_ack(fd, 0);
	clif_setwaitclose(fd);

	return;
}

/*==========================================
 * �}�i�[�|�C���g�t�^���b�Z�[�W
 *------------------------------------------
 */
void clif_manner_message(struct map_session_data* sd, int type)
{
	int fd;

	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x14a;
	WFIFOL(fd,2) = type;
	WFIFOSET(fd, packet_db[0x14a].len);
}

/*==========================================
 * �}�i�[�|�C���g�̎��
 *------------------------------------------
 */
void clif_GM_silence(struct map_session_data *sd, struct map_session_data *tsd, int type)
{
	int fd;

	nullpo_retv(sd);
	nullpo_retv(tsd);

	fd = tsd->fd;
	WFIFOW(fd,0) = 0x14b;
	WFIFOB(fd,2) = type;
	memcpy(WFIFOP(fd,3), sd->status.name, 24);
	WFIFOSET(fd, packet_db[0x14b].len);
}

/*==========================================
 * Wis���ۋ�����
 *------------------------------------------
 */
static void clif_wisexin(struct map_session_data *sd, int type, unsigned char flag)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xd1;
	WFIFOB(fd,2)=type;
	WFIFOB(fd,3)=flag;
	WFIFOSET(fd,packet_db[0xd1].len);

	return;
}

/*==========================================
 * Wis�S���ۋ�����
 *------------------------------------------
 */
static void clif_wisall(struct map_session_data *sd, int type, unsigned char flag)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xd2;
	WFIFOB(fd,2)=type;
	WFIFOB(fd,3)=flag;
	WFIFOSET(fd,packet_db[0xd2].len);

	return;
}

/*==========================================
 * �X�e�[�^�X�擾
 *------------------------------------------
 */
static void clif_check(int fd, struct map_session_data *sd)
{
	nullpo_retv(sd);

	WFIFOW(fd,0)  = 0x214;
	WFIFOB(fd,2)  = (sd->status.str > 255)? 255: sd->status.str;
	WFIFOB(fd,3)  = pc_need_status_point(sd, SP_STR);
	WFIFOB(fd,4)  = (sd->status.agi > 255)? 255: sd->status.agi;
	WFIFOB(fd,5)  = pc_need_status_point(sd, SP_AGI);
	WFIFOB(fd,6)  = (sd->status.vit > 255)? 255: sd->status.agi;
	WFIFOB(fd,7)  = pc_need_status_point(sd, SP_VIT);
	WFIFOB(fd,8)  = (sd->status.int_ > 255)? 255: sd->status.int_;
	WFIFOB(fd,9)  = pc_need_status_point(sd, SP_INT);
	WFIFOB(fd,10) = (sd->status.dex > 255)? 255: sd->status.dex;
	WFIFOB(fd,11) = pc_need_status_point(sd, SP_DEX);
	WFIFOB(fd,12) = (sd->status.luk > 255)? 255: sd->status.luk;
	WFIFOB(fd,13) = pc_need_status_point(sd, SP_LUK);

#ifdef PRE_RENEWAL
	WFIFOW(fd,16) = sd->base_atk + sd->watk + sd->watk_;
	WFIFOW(fd,18) = sd->watk2 + sd->watk_2;	// atk bonus
	WFIFOW(fd,20) = sd->matk1;
	WFIFOW(fd,22) = sd->matk2;
	WFIFOW(fd,24) = sd->def;	// def
	WFIFOW(fd,26) = sd->def2;
	WFIFOW(fd,28) = sd->mdef;	// mdef
	WFIFOW(fd,30) = sd->mdef2;
	WFIFOW(fd,32) = sd->hit;
	WFIFOW(fd,34) = sd->flee;
	WFIFOW(fd,36) = sd->flee2/10;
	WFIFOW(fd,38) = sd->critical/10;
	WFIFOW(fd,40) = sd->amotion;
	WFIFOW(fd,42) = 0;
#else
	WFIFOW(fd,16) = sd->base_atk;
	WFIFOW(fd,18) = sd->watk + sd->watk_ + sd->watk2 + sd->watk_2 + sd->plus_atk;	// atk
	WFIFOW(fd,20) = sd->matk1 + sd->plus_matk;
	WFIFOW(fd,22) = sd->matk2;
	WFIFOW(fd,24) = sd->def2;
	WFIFOW(fd,26) = sd->def;	// def
	WFIFOW(fd,28) = sd->mdef2;
	WFIFOW(fd,30) = sd->mdef;	// mdef
	WFIFOW(fd,32) = sd->hit;
	WFIFOW(fd,34) = sd->flee;
	WFIFOW(fd,36) = sd->flee2/10;
	WFIFOW(fd,38) = sd->critical/10;
	WFIFOW(fd,40) = sd->amotion;
	WFIFOW(fd,42) = 0;
#endif
	WFIFOSET(fd,packet_db[0x214].len);

	return;
}

/*==========================================
 * �T�E���h�G�t�F�N�g
 *------------------------------------------
 */
void clif_soundeffect(struct map_session_data *sd,struct block_list *bl,const char *name,int type,int interval)
{
	int fd;

	nullpo_retv(sd);

	if(bl == NULL)
		return;

	fd=sd->fd;
	WFIFOW(fd,0)=0x1d3;
	strncpy(WFIFOP(fd,2),name,24);
	WFIFOB(fd,26)=type;
	WFIFOL(fd,27)=interval;
	WFIFOL(fd,31)=bl->id;
	WFIFOSET(fd,packet_db[0x1d3].len);

	return;
}

/*==========================================
 * �c�e
 *------------------------------------------
 */
void clif_bodyrelocation(struct block_list *bl, int x, int y)
{
	unsigned char buf[10];

	nullpo_retv(bl);

	WBUFW(buf,0) = 0x8d2;
	WBUFL(buf,2) = bl->id;
	WBUFW(buf,6) = x;
	WBUFW(buf,8) = y;
	clif_send(buf,packet_db[0x8d2].len,bl,AREA);

	return;
}

/*==========================================
 * �F�B���X�g�̏��ʒm
 *------------------------------------------
 */
void clif_friend_send_info(struct map_session_data *sd)
{
	int len,i,fd;

	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW(fd, 0) = 0x201;
	for(i=0, len=4; i<sd->status.friend_num; i++) {
		struct friend_data *frd = &sd->status.friend_data[i];
		WFIFOL(fd,len  ) = frd->account_id;
		WFIFOL(fd,len+4) = frd->char_id;
#if PACKETVER < 20180221
		memcpy(WFIFOP(fd,len+8), frd->name, 24);
		len+=32;
#else
		len+=8;
#endif
	}
	WFIFOW(fd,2) = len;
	WFIFOSET(fd,len);

	return;
}

/*==========================================
 * �F�B���X�g�̃I�����C�����ʒm
 *------------------------------------------
 */
void clif_friend_send_online(const int fd, int account_id, int char_id, int flag)
{
#if PACKETVER >= 20180221
	char *p;

	p = map_charid2nick(char_id);
#endif
	WFIFOW(fd, 0) = 0x206;
	WFIFOL(fd, 2) = account_id;
	WFIFOL(fd, 6) = char_id;
	WFIFOB(fd,10) = flag;
#if PACKETVER >= 20180221
	if(p!=NULL){
		memcpy(WFIFOP(fd,11), p, 24);
	}
	else {
		memset(WFIFOP(fd,11), 0, 24);
	}
#endif
	WFIFOSET(fd,packet_db[0x206].len);

	return;
}

/*==========================================
 * �F�B���X�g�ǉ��v��
 *------------------------------------------
 */
void clif_friend_add_request(const int fd, struct map_session_data *sd)
{
	nullpo_retv(sd);

	WFIFOW(fd,0) = 0x207;
	WFIFOL(fd,2) = sd->bl.id;
	WFIFOL(fd,6) = sd->status.char_id;
	memcpy(WFIFOP(fd,10), sd->status.name, 24);
	WFIFOSET(fd,packet_db[0x207].len);

	return;
}

/*==========================================
 * �F�B���X�g�ǉ��v���ԓ�
 *------------------------------------------
 */
void clif_friend_add_ack(const int fd, int account_id, int char_id, const char* name, unsigned short flag)
{
	WFIFOW(fd,0) = 0x209;
	WFIFOW(fd,2) = flag;
	WFIFOL(fd,4) = account_id;
	WFIFOL(fd,8) = char_id;
	strncpy(WFIFOP(fd,12), name, 24);
	WFIFOSET(fd,packet_db[0x209].len);

	return;
}

/*==========================================
 * �F�B���X�g�ǉ��폜�ʒm
 *------------------------------------------
 */
void clif_friend_del_ack(const int fd, int account_id, int char_id)
{
	WFIFOW(fd,0) = 0x20a;
	WFIFOL(fd,2) = account_id;
	WFIFOL(fd,6) = char_id;
	WFIFOSET(fd,packet_db[0x20a].len);

	return;
}

/*==========================================
 * BS�����L���O�|�C���g
 *------------------------------------------
 */
void clif_blacksmith_point(const int fd,const int total,const int point)
{
	WFIFOW(fd,0) = 0x21b;
	WFIFOL(fd,2) = point;
	WFIFOL(fd,6) = total;
	WFIFOSET(fd,packet_db[0x21b].len);

	return;
}

/*==========================================
 * BS�����L���O
 *------------------------------------------
 */
void clif_blacksmith_ranking(const int fd,const char *charname[10],const int point[10])
{
	int i;

	WFIFOW(fd,0) = 0x219;
	for(i=0;i<10;i++){
		strncpy(WFIFOP(fd,i*24+2), charname[i], 24);
		WFIFOL(fd,i*4+242) = point[i];
	}
	WFIFOSET(fd,packet_db[0x219].len);

	return;
}

/*==========================================
 * �A���P�~�����L���O�|�C���g
 *------------------------------------------
 */
void clif_alchemist_point(const int fd,const int total,const int point)
{
	WFIFOW(fd,0) = 0x21c;
	WFIFOL(fd,2) = point;
	WFIFOL(fd,6) = total;
	WFIFOSET(fd,packet_db[0x21c].len);

	return;
}

/*==========================================
 * �A���P�~�����L���O
 *------------------------------------------
 */
void clif_alchemist_ranking(const int fd,const char *charname[10],const int point[10])
{
	int i;

	WFIFOW(fd,0) = 0x21a;
	for(i=0;i<10;i++){
		strncpy(WFIFOP(fd,i*24+2), charname[i], 24);
		WFIFOL(fd,i*4+242) = point[i];
	}
	WFIFOSET(fd,packet_db[0x21a].len);

	return;
}

/*==========================================
 * �e�R�������L���O�|�C���g
 *------------------------------------------
 */
void clif_taekwon_point(const int fd,const int total,const int point)
{
	WFIFOW(fd,0) = 0x224;
	WFIFOL(fd,2) = point;
	WFIFOL(fd,6) = total;
	WFIFOSET(fd,packet_db[0x224].len);

	return;
}

/*==========================================
 * �e�R�������L���O
 *------------------------------------------
 */
void clif_taekwon_ranking(const int fd,const char *charname[10],const int point[10])
{
	int i;

	WFIFOW(fd,0) = 0x226;
	for(i=0;i<10;i++){
		strncpy(WFIFOP(fd,i*24+2), charname[i], 24);
		WFIFOL(fd,i*4+242) = point[i];
	}
	WFIFOSET(fd,packet_db[0x226].len);

	return;
}

/*==========================================
 * �s�E�҃����L���O�|�C���g
 *------------------------------------------
 */
void clif_pk_point(const int fd,const int total,const int point)
{
	WFIFOW(fd,0) = 0x236;
	WFIFOL(fd,2) = point;
	WFIFOL(fd,6) = total;
	WFIFOSET(fd,packet_db[0x236].len);

	return;
}

/*==========================================
 * �s�E�҃����L���O
 *------------------------------------------
 */
void clif_pk_ranking(const int fd,const char *charname[10],const int point[10])
{
	int i;

	WFIFOW(fd,0) = 0x238;
	for(i=0;i<10;i++){
		strncpy(WFIFOP(fd,i*24+2), charname[i], 24);
		WFIFOL(fd,i*4+242) = point[i];
	}
	WFIFOSET(fd,packet_db[0x238].len);

	return;
}

/*==========================================
 * �ꊇ�����L���O�|�C���g
 *------------------------------------------
 */
void clif_updata_ranking_point(const int fd,const int total,const int point,int ranking_id)
{
	WFIFOW(fd,0) = 0x97e;
	WFIFOW(fd,2) = ranking_id;
	WFIFOL(fd,4) = point;
	WFIFOL(fd,8) = total;
	WFIFOSET(fd,packet_db[0x97e].len);

	return;
}

/*==========================================
 * �ꊇ�����L���O
 *------------------------------------------
 */
void clif_rankinglist(const int fd,const char *charname[10],const int point[10],int ranking_id,int mypoint)
{
	int i;

	WFIFOW(fd,0) = 0x97d;
	WFIFOW(fd,2) = ranking_id;
	for(i=0;i<10;i++){
		strncpy(WFIFOP(fd,i*24+4), charname[i], 24);
		WFIFOL(fd,i*4+244) = point[i];
	}
	WFIFOL(fd,284) = mypoint;
	WFIFOSET(fd,packet_db[0x97d].len);

	return;
}

/*==========================================
 * ���[��BOX��\��������
 *------------------------------------------
 */
void clif_openmailbox(const int fd)
{
	WFIFOW(fd,0) = 0x260;
	WFIFOL(fd,2) = 0;
	WFIFOSET(fd,packet_db[0x260].len);

	return;
}

/*==========================================
 * ���[���ꗗ�\�iBOX���J���Ă��鎞�ɑ��֑��M�j
 *  0x23f�̉���
 *------------------------------------------
 */
void clif_send_mailbox(struct map_session_data *sd,int store,struct mail_data md[MAIL_STORE_MAX])
{
	int i,fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0) = 0x240;
	WFIFOL(fd,4) = store;	// 0�̂Ƃ��͉�ʂ̃N���A
	for(i=0;i<store;i++){
		WFIFOL(fd,8+73*i)  = md[i].mail_num;
		memcpy(WFIFOP(fd,12+73*i),md[i].title,40);
		WFIFOB(fd,52+73*i) = md[i].read;
		memcpy(WFIFOP(fd,53+73*i),md[i].char_name,24);
		WFIFOL(fd,77+73*i) = md[i].times;
	}
	WFIFOW(fd,2) = 8+73*i;
	WFIFOSET(fd,WFIFOW(fd,2));

	return;
}

/*==========================================
 * ���[�������M�ł��܂����Ƃ��ł��܂���Ƃ�
 *------------------------------------------
 */
void clif_res_sendmail(const int fd,int fail)
{
	WFIFOW(fd,0) = 0x249;
	WFIFOB(fd,2) = fail;
	WFIFOSET(fd,packet_db[0x249].len);

	return;
}

/*==========================================
 * �A�C�e�����Y�t�ł��܂����Ƃ��ł��܂���Ƃ�
 *------------------------------------------
 */
void clif_res_sendmail_setappend(const int fd,int idx,int flag)
{
	WFIFOW(fd,0) = 0x255;
	WFIFOW(fd,2) = idx + 2;
	WFIFOB(fd,4) = flag;
	WFIFOSET(fd,packet_db[0x256].len);

	return;
}

/*==========================================
 * �Y�t�A�C�e���擾
 *------------------------------------------
 */
void clif_mail_getappend(const int fd,int flag)
{
	WFIFOW(fd,0) = 0x245;
	WFIFOB(fd,2) = flag;
	WFIFOSET(fd,packet_db[0x245].len);

	return;
}

/*==========================================
 * �V�����[�����͂��܂���
 *------------------------------------------
 */
void clif_arrive_newmail(const int fd,struct mail_data *md)
{
	nullpo_retv(md);

	WFIFOW(fd,0) = 0x24a;
	WFIFOL(fd,2) = md->mail_num;
	memcpy(WFIFOP(fd, 6),md->char_name,24);
	memcpy(WFIFOP(fd,30),md->title,40);
	WFIFOSET(fd,packet_db[0x24a].len);

	return;
}

/*==========================================
 * ���[����I����M	Inter���{�l��
 *------------------------------------------
 */
void clif_receive_mail(struct map_session_data *sd,struct mail_data *md)
{
	int fd,view;

	nullpo_retv(sd);
	nullpo_retv(md);

	fd=sd->fd;
	WFIFOW(fd,0)=0x242;
	WFIFOW(fd,2)=md->body_size+99;
	WFIFOL(fd,4)=md->mail_num;
	memcpy(WFIFOP(fd, 8),md->title,40);
	memcpy(WFIFOP(fd,48),md->char_name,24);
	WFIFOL(fd,72)=0x22;	// ���E�H
	WFIFOL(fd,76)=md->zeny;
	WFIFOL(fd,80)=md->item.amount;
	if((view = itemdb_viewid(md->item.nameid)) > 0)
		WFIFOW(fd,84)=view;
	else
		WFIFOW(fd,84)=md->item.nameid;
	WFIFOW(fd,86)=0;
	WFIFOB(fd,88)=md->item.identify;
	WFIFOB(fd,89)=md->item.attribute;
	WFIFOB(fd,90)=md->item.refine;
	WFIFOW(fd,91)=md->item.card[0];
	WFIFOW(fd,93)=md->item.card[1];
	WFIFOW(fd,95)=md->item.card[2];
	WFIFOW(fd,97)=md->item.card[3];
	memcpy(WFIFOP(fd,99),md->body,md->body_size);
	WFIFOSET(fd,WFIFOW(fd,2));

	return;
}

/*==========================================
 * ���[�����폜�ł��܂����Ƃ��ł��܂���Ƃ�
 *------------------------------------------
 */
void clif_deletemail_res(const int fd,int mail_num,int flag)
{
	WFIFOW(fd,0) = 0x257;
	WFIFOL(fd,2) = mail_num;
	WFIFOW(fd,6) = flag;
	WFIFOSET(fd,packet_db[0x257].len);

	return;
}

/*==========================================
 * �����]��
 *------------------------------------------
 */
void clif_changedir(struct block_list *bl, int headdir, int dir)
{
	unsigned char buf[16];

	nullpo_retv(bl);

	WBUFW(buf,0)=0x9c;
	WBUFL(buf,2)=bl->id;
	WBUFW(buf,6)=headdir;
	WBUFB(buf,8)=(unsigned char)dir;
	clif_send(buf,packet_db[0x9c].len,bl,AREA_WOS);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_send_homdata(struct map_session_data *sd, int state, int param)
{
	int fd;

	nullpo_retv(sd);
	nullpo_retv(sd->hd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x230;
	WFIFOB(fd,2)=0;
	WFIFOB(fd,3)=state;
	WFIFOL(fd,4)=sd->hd->bl.id;
	WFIFOL(fd,8)=param;
	WFIFOSET(fd,packet_db[0x230].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_send_homstatus(struct map_session_data *sd, int flag)
{
	int fd;
	struct homun_data *hd;

	nullpo_retv(sd);
	nullpo_retv((hd=sd->hd));

	fd=sd->fd;
#if PACKETVER < 20141223
	WFIFOW(fd,0)=0x22e;
	memcpy(WFIFOP(fd,2),hd->status.name,24);
	WFIFOB(fd,26)=(unit_isdead(&hd->bl))? 2: battle_config.homun_rename? 0: hd->status.rename_flag; // ���O�t�����t���O 1�ŕύX�s�� 2�͎��S���
	WFIFOW(fd,27)=hd->status.base_level;	// Lv
	WFIFOW(fd,29)=hd->status.hungry;		// �����x
	WFIFOW(fd,31)=hd->intimate/100;	// �V���x
	WFIFOW(fd,33)=hd->status.equip;			// equip id
	WFIFOW(fd,35)=hd->atk;					// Atk
	WFIFOW(fd,37)=hd->matk;					// MAtk
	WFIFOW(fd,39)=hd->hit;					// Hit
	WFIFOW(fd,41)=hd->critical;				// Cri
	WFIFOW(fd,43)=hd->def;					// Def
	WFIFOW(fd,45)=hd->mdef;					// Mdef
	WFIFOW(fd,47)=hd->flee;					// Flee
	WFIFOW(fd,49)=(flag)?0:status_get_amotion(&hd->bl);	// Aspd
	WFIFOW(fd,51)=hd->status.hp;			// HP
	WFIFOW(fd,53)=hd->max_hp;		// MHp
	WFIFOW(fd,55)=hd->status.sp;			// SP
	WFIFOW(fd,57)=hd->max_sp;		// MSP
	WFIFOL(fd,59)=hd->status.base_exp;		// Exp
	WFIFOL(fd,63)=homun_nextbaseexp(hd);	// NextExp
	WFIFOW(fd,67)=hd->status.skill_point;	// skill point
	WFIFOW(fd,69)=hd->attackable;			// �U���ۃt���O 0:�s��/1:����
	WFIFOSET(fd,packet_db[0x22e].len);
#elif PACKETVER < 20180704
	WFIFOW(fd,0)=0x9f7;
	memcpy(WFIFOP(fd,2),hd->status.name,24);
	WFIFOB(fd,26)=(unit_isdead(&hd->bl))? 2: battle_config.homun_rename? 0: hd->status.rename_flag; // ���O�t�����t���O 1�ŕύX�s�� 2�͎��S���
	WFIFOW(fd,27)=hd->status.base_level;	// Lv
	WFIFOW(fd,29)=hd->status.hungry;		// �����x
	WFIFOW(fd,31)=hd->intimate/100;	// �V���x
	WFIFOW(fd,33)=hd->status.equip;			// equip id
	WFIFOW(fd,35)=hd->atk;					// Atk
	WFIFOW(fd,37)=hd->matk;					// MAtk
	WFIFOW(fd,39)=hd->hit;					// Hit
	WFIFOW(fd,41)=hd->critical;				// Cri
	WFIFOW(fd,43)=hd->def;					// Def
	WFIFOW(fd,45)=hd->mdef;					// Mdef
	WFIFOW(fd,47)=hd->flee;					// Flee
	WFIFOW(fd,49)=(flag)?0:status_get_amotion(&hd->bl);	// Aspd
	WFIFOL(fd,51)=hd->status.hp;			// HP
	WFIFOL(fd,55)=hd->max_hp;		// MHp
	WFIFOW(fd,59)=hd->status.sp;			// SP
	WFIFOW(fd,61)=hd->max_sp;		// MSP
	WFIFOL(fd,63)=hd->status.base_exp;		// Exp
	WFIFOL(fd,67)=homun_nextbaseexp(hd);	// NextExp
	WFIFOW(fd,71)=hd->status.skill_point;	// skill point
	WFIFOW(fd,73)=hd->attackable;			// �U���ۃt���O 0:�s��/1:����
	WFIFOSET(fd,packet_db[0x9f7].len);
#else
	WFIFOW(fd,0)=0x9f7;
	memcpy(WFIFOP(fd,2),hd->status.name,24);
	WFIFOB(fd,26)=(unit_isdead(&hd->bl))? 2: battle_config.homun_rename? 0: hd->status.rename_flag; // ���O�t�����t���O 1�ŕύX�s�� 2�͎��S���
	WFIFOW(fd,27)=hd->status.base_level;	// Lv
	WFIFOW(fd,29)=hd->status.hungry;		// �����x
	WFIFOW(fd,31)=hd->intimate/100;	// �V���x
	WFIFOL(fd,33)=hd->status.equip;			// equip id
	WFIFOW(fd,37)=hd->atk;					// Atk
	WFIFOW(fd,39)=hd->matk;					// MAtk
	WFIFOW(fd,41)=hd->hit;					// Hit
	WFIFOW(fd,43)=hd->critical;				// Cri
	WFIFOW(fd,45)=hd->def;					// Def
	WFIFOW(fd,47)=hd->mdef;					// Mdef
	WFIFOW(fd,49)=hd->flee;					// Flee
	WFIFOW(fd,51)=(flag)?0:status_get_amotion(&hd->bl);	// Aspd
	WFIFOL(fd,53)=hd->status.hp;			// HP
	WFIFOL(fd,57)=hd->max_hp;		// MHp
	WFIFOW(fd,61)=hd->status.sp;			// SP
	WFIFOW(fd,63)=hd->max_sp;		// MSP
	WFIFOL(fd,65)=hd->status.base_exp;		// Exp
	WFIFOL(fd,69)=homun_nextbaseexp(hd);	// NextExp
	WFIFOW(fd,73)=hd->status.skill_point;	// skill point
	WFIFOW(fd,75)=hd->attackable;			// �U���ۃt���O 0:�s��/1:����
	WFIFOSET(fd,packet_db[0x9f7].len);
#endif

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_hom_food(struct map_session_data *sd, int foodid, unsigned char fail)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
#if PACKETVER < 20180704
	WFIFOW(fd,0)=0x22f;
	WFIFOB(fd,2)=fail;
	WFIFOW(fd,3)=foodid;
	WFIFOSET(fd,packet_db[0x22f].len);
#else
	WFIFOW(fd,0)=0x22f;
	WFIFOB(fd,2)=fail;
	WFIFOL(fd,3)=foodid;
	WFIFOSET(fd,packet_db[0x22f].len);
#endif

	return;
}

/*==========================================
 * �z���̃X�L�����X�g�𑗐M����
 *------------------------------------------
 */
void clif_homskillinfoblock(struct map_session_data *sd)
{
	int fd;
	int i,len=4,id,skill_lv;
	struct homun_data *hd;

	nullpo_retv(sd);
	nullpo_retv(hd = sd->hd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x235;
	for(i = 0; i < MAX_HOMSKILL; i++) {
		if((id = hd->status.skill[i].id) != 0) {
			if(hd->status.skill[i].id == MUTATION_BASEJOB)
				continue;
			skill_lv = hd->status.skill[i].lv;
			WFIFOW(fd,len  )  = id;
			WFIFOL(fd,len+2)  = skill_get_inf(id);
			WFIFOW(fd,len+6)  = skill_lv;
			WFIFOW(fd,len+8)  = skill_get_sp(id,skill_lv);
			WFIFOW(fd,len+10) = skill_get_fixed_range(&hd->bl,id,skill_lv);
			memset(WFIFOP(fd,len+12),0,24);
			if(!(skill_get_inf2(id)&INF2_QUEST))
				WFIFOB(fd,len+36) = (skill_lv < homun_get_skilltree_max(hd,id) && hd->status.skill[i].flag == 0)? 1: 0;
			else
				WFIFOB(fd,len+36) = 0;
			len += 37;
		}
	}
	WFIFOW(fd,2) = len;
	WFIFOSET(fd,len);

	return;
}

/*==========================================
 * �z���̃X�L������U��ʒm
 *------------------------------------------
 */
void clif_homskillup(struct map_session_data *sd, int skill_num)
{
	int fd,skillid;
	struct homun_data *hd;

	nullpo_retv(sd);
	nullpo_retv((hd=sd->hd));

	skillid = skill_num-HOM_SKILLID;

	fd=sd->fd;
	WFIFOW(fd,0) = 0x239;
	WFIFOW(fd,2) = skill_num;
	WFIFOW(fd,4) = hd->status.skill[skillid].lv;
	WFIFOW(fd,6) = skill_get_sp(skill_num,hd->status.skill[skillid].lv);
	WFIFOW(fd,8) = skill_get_fixed_range(&hd->bl,skill_num,hd->status.skill[skillid].lv);
	WFIFOB(fd,10) = (hd->status.skill[skillid].lv < homun_get_skilltree_max(hd,hd->status.skill[skillid].id)) ? 1 : 0;
	WFIFOSET(fd,packet_db[0x239].len);

	return;
}

/*==========================================
 * ���z�ƌ��Ɛ��̊���̓o�^����
 *------------------------------------------
 */
static void clif_feel_saveack(struct map_session_data *sd, int lv)
{
	int fd;

	nullpo_retv(sd);

	if(lv < 0 || lv > 2)
		return;

	if(pc_checkskill(sd,SG_FEEL) < lv + 1)
		return;

	if(battle_config.save_feel_map)
		strncpy(sd->status.feel_map[lv], map[sd->bl.m].name, 24);
	sd->feel_index[lv] = sd->bl.m;

	clif_misceffect2(&sd->bl, 432);
	clif_misceffect2(&sd->bl, 543);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x20e;
	memcpy(WFIFOP(fd,2), map[sd->bl.m].name, 24);
	WFIFOL(fd,26) = sd->bl.id;
	WFIFOB(fd,30) = lv;
	WFIFOB(fd,31) = 0;
	WFIFOSET(fd,packet_db[0x20e].len);

	return;
}

/*==========================================
 * ���z�ƌ��Ɛ��̊���̓o�^���
 *------------------------------------------
 */
void clif_feel_info(struct map_session_data *sd, int skilllv)
{
	int fd;

	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x20e;
	strncpy(WFIFOP(fd,2),sd->status.feel_map[skilllv-1],24);
	WFIFOL(fd,26) = sd->bl.id;
	WFIFOB(fd,30) = skilllv-1;
	WFIFOB(fd,31) = 1;
	WFIFOSET(fd,packet_db[0x20e].len);

	return;
}

/*==========================================
 * ���z�ƌ��Ɛ��̑����݂̓o�^����
 *------------------------------------------
 */
void clif_hate_mob(struct map_session_data *sd, int skilllv, int id)
{
	int fd;

	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x20e;
	if(mobdb_exists(id)) {
		strncpy(WFIFOP(fd,2),mobdb_search(id)->jname,24);
	} else {
		memset(WFIFOP(fd,2), 0, 24);
	}
	WFIFOL(fd,26) = id;
	WFIFOB(fd,30) = skilllv-1;
	WFIFOB(fd,31) = 10;
	WFIFOSET(fd,packet_db[0x20e].len);

	return;
}

/*==========================================
 * ���z�ƌ��Ɛ��̑����݂̓o�^���
 *------------------------------------------
 */
void clif_hate_info(struct map_session_data *sd, int skilllv, int id)
{
	int fd;

	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x20e;
	if(mobdb_exists(id)) {
		strncpy(WFIFOP(fd,2),mobdb_search(id)->jname,24);
	} else {
		memset(WFIFOP(fd,2), 0, 24);
	}
	WFIFOL(fd,26) = id;
	WFIFOB(fd,30) = skilllv-1;
	WFIFOB(fd,31) = 11;
	WFIFOSET(fd,packet_db[0x20e].len);

	return;
}

/*==========================================
 * �e�R���~�b�V����
 *------------------------------------------
 */
void clif_mission_mob(struct map_session_data *sd, int id, int count)
{
	int fd;

	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x20e;
	strncpy(WFIFOP(fd,2),mobdb_search(id)->jname,24);
	WFIFOL(fd,26) = id;
	WFIFOB(fd,30) = count;
	WFIFOB(fd,31) = 20;
	WFIFOSET(fd,packet_db[0x20e].len);

	return;
}

/*==========================================
 * ���z�ƌ��Ɛ��̓V�g
 *------------------------------------------
 */
void clif_angel_message(struct map_session_data *sd)
{
	int fd;

	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x20e;
	WFIFOL(fd,26) = sd->bl.id;
	WFIFOB(fd,30) = 0;
	WFIFOB(fd,31) = 30;
	WFIFOSET(fd,packet_db[0x20e].len);

	return;
}

/*==========================================
 * ���z�ƌ��Ɛ��̊���̃_�C�A���O�\��
 *------------------------------------------
 */
void clif_feel_display(struct map_session_data *sd, int skilllv)
{
	int fd;

	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x253;
	WFIFOB(fd,2) = skilllv-1;
	WFIFOSET(fd,packet_db[0x253].len);

	return;
}

/*==========================================
 * �}�[�_���[
 *------------------------------------------
 */
void clif_send_murderer(struct map_session_data *sd,int target,int flag)
{
	int fd;

	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x220;
	WFIFOL(fd,2) = target;
	WFIFOL(fd,6) = flag;
	WFIFOSET(fd,packet_db[0x220].len);

	return;
}

/*==========================================
 * temper�X�V
 *------------------------------------------
 */
void clif_update_temper(struct map_session_data *sd)
{
	int fd;
	char *nick1 = NULL, *nick2 = NULL;

	nullpo_retv(sd);

	if(sd->kill.char_id > 0) {
		nick1 = map_charid2nick(sd->kill.char_id);
		if(nick1 == NULL) {
			if(map_reqchariddb(sd,sd->kill.char_id,2))
				chrif_searchcharid(sd->kill.char_id);
		}
	}
	if(sd->kill.merderer_char_id > 0) {
		nick2 = map_charid2nick(sd->kill.merderer_char_id);
		if(nick2 == NULL) {
			if(map_reqchariddb(sd,sd->kill.merderer_char_id,2))
				chrif_searchcharid(sd->kill.merderer_char_id);
		}
	}

	fd = sd->fd;
	WFIFOW(fd,0)  = 0x21f;
	WFIFOL(fd,2)  = 0;	// ??
	WFIFOL(fd,6)  = 0;	// ??
	strncpy(WFIFOP(fd,10), (nick1 ? nick1 : ""), 24);
	strncpy(WFIFOP(fd,34), (nick2 ? nick2 : ""), 24);
	WFIFOL(fd,58) = 0;	// ??
	WFIFOL(fd,62) = 0;	// ??
	WFIFOSET(fd,packet_db[0x21f].len);

	return;
}

/*==========================================
 * �z�b�g�L�[�̑��M
 *------------------------------------------
 */
void clif_send_hotkey(struct map_session_data *sd)
{
	int i, j, fd;

	nullpo_retv(sd);

	fd = sd->fd;

#if PACKETVER < 20090603
	memset(WFIFOP(fd,0), 0, packet_db[0x2b9].len);

	WFIFOW(fd,0) = 0x2b9;
	for(i = 0, j = sd->hotkey_set * 27; i < 27 && j < MAX_HOTKEYS; i++, j++) {
		WFIFOB(fd,7*i+2) = sd->status.hotkey[j].type;
		WFIFOL(fd,7*i+3) = sd->status.hotkey[j].id;
		WFIFOW(fd,7*i+7) = sd->status.hotkey[j].lv;
	}
	WFIFOSET(fd,packet_db[0x2b9].len);
#elif PACKETVER < 20090617
	memset(WFIFOP(fd,0), 0, packet_db[0x7d9].len);

	WFIFOW(fd,0) = 0x7d9;
	for(i = 0, j = sd->hotkey_set * 36; i < 36 && j < MAX_HOTKEYS; i++, j++) {
		WFIFOB(fd,7*i+2) = sd->status.hotkey[j].type;
		WFIFOL(fd,7*i+3) = sd->status.hotkey[j].id;
		WFIFOW(fd,7*i+7) = sd->status.hotkey[j].lv;
	}
	WFIFOSET(fd,packet_db[0x7d9].len);
#elif PACKETVER < 20141022
	memset(WFIFOP(fd,0), 0, packet_db[0x7d9].len);

	WFIFOW(fd,0) = 0x7d9;
	for(i = 0, j = sd->hotkey_set * 38; i < 38 && j < MAX_HOTKEYS; i++, j++) {
		WFIFOB(fd,7*i+2) = sd->status.hotkey[j].type;
		WFIFOL(fd,7*i+3) = sd->status.hotkey[j].id;
		WFIFOW(fd,7*i+7) = sd->status.hotkey[j].lv;
	}
	WFIFOSET(fd,packet_db[0x7d9].len);
#elif PACKETVER < 20190522
	memset(WFIFOP(fd,0), 0, packet_db[0xa00].len);

	WFIFOW(fd,0) = 0xa00;
	WFIFOB(fd,2) = sd->hotkey_rotate[0];
	for(i = 0, j = sd->hotkey_set * 38; i < 38 && j < MAX_HOTKEYS; i++, j++) {
		WFIFOB(fd,7*i+3) = sd->status.hotkey[j].type;
		WFIFOL(fd,7*i+4) = sd->status.hotkey[j].id;
		WFIFOW(fd,7*i+8) = sd->status.hotkey[j].lv;
	}
	WFIFOSET(fd,packet_db[0xa00].len);
#else
	memset(WFIFOP(fd,0), 0, packet_db[0xb20].len);

	WFIFOW(fd,0) = 0xb20;
	WFIFOB(fd,2) = sd->hotkey_rotate[sd->hotkey_set];
	WFIFOW(fd,3) = sd->hotkey_set;
	for(i = 0, j = sd->hotkey_set * 38; i < 38 && j < MAX_HOTKEYS; i++, j++) {
		WFIFOB(fd,7*i+5) = sd->status.hotkey[j].type;
		WFIFOL(fd,7*i+6) = sd->status.hotkey[j].id;
		WFIFOW(fd,7*i+10) = sd->status.hotkey[j].lv;
	}
	WFIFOSET(fd,packet_db[0xb20].len);
#endif

	return;
}

void clif_send_hotkeyAll(struct map_session_data *sd)
{
#if PACKETVER >= 20190522
	int i;
	clif_send_hotkey(sd);

	for(i = MAX_HOTKEYS / 2; i < MAX_HOTKEYS; i++) {
		if(sd->status.hotkey[i].type != 0 || sd->status.hotkey[i].id != 0 || sd->status.hotkey[i].lv != 0) {
			sd->hotkey_set = 1;
			clif_send_hotkey(sd);
			sd->hotkey_set = 0;
			return;
		}
	}
#else
	clif_send_hotkey(sd);
#endif
}

/*==========================================
 * MVP�{�X���
 *------------------------------------------
 */
void clif_bossmapinfo(struct map_session_data *sd, const char *name, int x, int y, int tick, int type)
{
	int fd;

	nullpo_retv(sd);

	fd   = sd->fd;
	tick = tick / 1000 / 60;	// minute

	WFIFOW(fd,0)  = 0x293;
	WFIFOB(fd,2)  = type;
	WFIFOL(fd,3)  = x;
	WFIFOL(fd,7)  = y;
	WFIFOW(fd,11) = tick / 60;
	WFIFOW(fd,13) = tick % 60;
	WFIFOL(fd,15) = 0;
	strncpy(WFIFOP(fd,19), name, 50);
	WFIFOB(fd,69) = 0;	// \0 terminal
	WFIFOSET(fd,packet_db[0x293].len);

	return;
}

/*==========================================
 * �Ǐ��E�B���h�E�̕\��
 *------------------------------------------
 */
void clif_openbook(struct map_session_data *sd, int nameid, int page)
{
	int fd;

	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW(fd,0)  = 0x294;
	WFIFOL(fd,2)  = nameid;
	WFIFOL(fd,6)  = page;
	WFIFOSET(fd,packet_db[0x294].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_send_mercstatus(struct map_session_data *sd)
{
	int fd, val;
	struct merc_data *mcd;

	nullpo_retv(sd);
	nullpo_retv(mcd = sd->mcd);

	val = mcd->atk2 - mcd->atk1 + 1;

	fd = sd->fd;
	WFIFOW(fd,0)  = 0x29b;
	WFIFOL(fd,2)  = mcd->bl.id;
	WFIFOW(fd,6)  = (val > 0)? atn_rand() % val + mcd->atk1 : 0;
	WFIFOW(fd,8)  = mcd->matk1;
	WFIFOW(fd,10) = mcd->hit;
	WFIFOW(fd,12) = mcd->critical;
	WFIFOW(fd,14) = mcd->def;
	WFIFOW(fd,16) = mcd->mdef;
	WFIFOW(fd,18) = mcd->flee;
	WFIFOW(fd,20) = mcd->amotion;
	memcpy(WFIFOP(fd,22), mcd->name, 24);
	WFIFOW(fd,46) = mcd->base_level;
#if PACKETVER < 20071106
	WFIFOW(fd,48) = mcd->status.hp;
	WFIFOW(fd,50) = mcd->max_hp;
	WFIFOW(fd,52) = mcd->status.sp;
	WFIFOW(fd,54) = mcd->max_sp;
	WFIFOL(fd,56) = mcd->status.limit;	// �ٗp����
	WFIFOW(fd,60) = merc_get_fame(sd, mcd->status.class_);	// �����l
	WFIFOL(fd,62) = merc_get_call(sd, mcd->status.class_);	// ������
	WFIFOL(fd,66) = mcd->status.kill_count;	// �L���J�E���g
	WFIFOW(fd,70) = mcd->attackrange;	// �U���͈�
#else
	WFIFOL(fd,48) = mcd->status.hp;
	WFIFOL(fd,52) = mcd->max_hp;
	WFIFOL(fd,56) = mcd->status.sp;
	WFIFOL(fd,60) = mcd->max_sp;
	WFIFOL(fd,64) = mcd->status.limit;	// �ٗp����
	WFIFOW(fd,68) = merc_get_fame(sd, mcd->status.class_);	// �����l
	WFIFOL(fd,70) = merc_get_call(sd, mcd->status.class_);	// ������
	WFIFOL(fd,74) = mcd->status.kill_count;	// �L���J�E���g
	WFIFOW(fd,78) = mcd->attackrange;	// �U���͈�
#endif
	WFIFOSET(fd,packet_db[0x29b].len);

	return;
}

/*==========================================
 * �b���̃X�L�����X�g�𑗐M����
 *------------------------------------------
 */
void clif_mercskillinfoblock(struct map_session_data *sd)
{
	int fd;
	int i,len=4,id,skill_lv;
	struct merc_data *mcd;

	nullpo_retv(sd);
	nullpo_retv(mcd = sd->mcd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x29d;
	for(i = 0; i < MAX_MERCSKILL; i++) {
		if((id = mcd->skill[i].id) != 0) {
			skill_lv = mcd->skill[i].lv;
			WFIFOW(fd,len  )  = id;
			WFIFOL(fd,len+2)  = skill_get_inf(id);
			WFIFOW(fd,len+6)  = skill_lv;
			WFIFOW(fd,len+8)  = skill_get_sp(id,skill_lv);
			WFIFOW(fd,len+10) = skill_get_fixed_range(&mcd->bl,id,skill_lv);
			memset(WFIFOP(fd,len+12),0,24);
			if(!(skill_get_inf2(id)&INF2_QUEST))
				WFIFOB(fd,len+36) = (skill_lv < merc_get_skilltree_max(mcd->status.class_,id) && mcd->skill[i].flag == 0)? 1: 0;
			else
				WFIFOB(fd,len+36) = 0;
			len += 37;
		}
	}
	WFIFOW(fd,2) = len;
	WFIFOSET(fd,len);

	return;
}

/*==========================================
 * �b���̃X�e�[�^�X�𑗂����
 *------------------------------------------
 */
void clif_mercupdatestatus(struct map_session_data *sd, int type)
{
	int fd;
	struct merc_data *mcd;

	nullpo_retv(sd);
	nullpo_retv(mcd = sd->mcd);

	fd = sd->fd;

	WFIFOW(fd,0)  = 0x2a2;
	WFIFOW(fd,2)  = type;
	switch(type){
	case SP_HP:
		WFIFOL(fd,4) = mcd->status.hp;
		break;
	case SP_MAXHP:
		WFIFOL(fd,4) = mcd->max_hp;
		break;
	case SP_SP:
		WFIFOL(fd,4) = mcd->status.sp;
		break;
	case SP_MAXSP:
		WFIFOL(fd,4) = mcd->max_sp;
		break;
	case SP_ATK1:
		{
			int val = mcd->atk2 - mcd->atk1 + 1;
			WFIFOL(fd,4) = (val > 0)? atn_rand()%val + mcd->atk1 : 0;
		}
		break;
	case SP_MATK1:
		WFIFOL(fd,4) = mcd->matk1;
		break;
	case SP_DEF1:
		WFIFOL(fd,4) = mcd->def;
		break;
	case SP_MDEF1:
		WFIFOL(fd,4) = mcd->mdef;
		break;
	case SP_HIT:
		WFIFOL(fd,4) = mcd->hit;
		break;
	case SP_FLEE1:
	case SP_MERC_FLEE:
		WFIFOL(fd,4) = mcd->flee;
		break;
	case SP_CRITICAL:
		WFIFOL(fd,4) = mcd->critical;
		break;
	case SP_ASPD:
		WFIFOL(fd,4) = mcd->amotion;
		break;
	case SP_MERC_KILLCOUNT:
		WFIFOL(fd,4) = mcd->status.kill_count;
		break;
	case SP_MERC_FAME:
		WFIFOL(fd,4) = merc_get_fame(sd, mcd->status.class_);
		break;
	}
	WFIFOSET(fd,packet_db[0x2a2].len);

	return;
}

/*==========================================
 * msgstringtable�\��
 *------------------------------------------
 */
void clif_msgstringtable(struct map_session_data *sd, int line)
{
	int fd;

	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x291;
	WFIFOW(fd,2) = line;
	WFIFOSET(fd,packet_db[0x291].len);

	return;
}

/*==========================================
 * �N�G�X�g���X�g
 *------------------------------------------
 */
void clif_questlist(struct map_session_data *sd)
{
	int fd, i, len=8;
	int active=0;

	nullpo_retv(sd);

	fd = sd->fd;
#if PACKETVER < 20141022
	WFIFOW(fd,0) = 0x2b1;
	for(i = 0; i < sd->questlist; i++) {
		struct quest_data *qd = &sd->quest[i];
		if(qd->nameid != 0 && qd->state < 2) {
			WFIFOL(fd,len)   = qd->nameid;
			WFIFOB(fd,len+4) = qd->state;
			len += 5;
			active++;
		}
	}
#elif PACKETVER < 20150513
	WFIFOW(fd,0) = 0x97a;
	for(i = 0; i < sd->questlist; i++) {
		int id, j, n;
		struct quest_data *qd = &sd->quest[i];
		if(qd->nameid != 0 && qd->state < 2) {
			WFIFOL(fd,len)   = qd->nameid;
			WFIFOB(fd,len+4) = qd->state;
			WFIFOL(fd,len+5) = qd->limit/* - quest_db[quest_search_db(qd->nameid)].limit*/;
			WFIFOL(fd,len+9) = qd->limit;
			for(j = 0, n = 0; j < 3; j++) {
				if((id = (int)qd->mob[j].id) != 0) {
					WFIFOL(fd,len+15+n*32) = id;
					WFIFOW(fd,len+19+n*32) = qd->mob[j].count;
					WFIFOW(fd,len+21+n*32) = qd->mob[j].max;
					if(mobdb_exists(id)) {
						strncpy(WFIFOP(fd,len+23+n*32),mobdb_search(id)->jname,24);
					} else {
						memset(WFIFOP(fd,len+23+n*32), 0, 24);
					}
					n++;
				}
			}
			WFIFOW(fd,len+13) = n;
			len += 15+n*32;
			active++;
		}
	}
#else
	WFIFOW(fd,0) = 0x9f8;
	for(i = 0; i < sd->questlist; i++) {
		int id, j, n;
		struct quest_data *qd = &sd->quest[i];
		if(qd->nameid != 0 && qd->state < 2) {
			WFIFOL(fd,len)   = qd->nameid;
			WFIFOB(fd,len+4) = qd->state;
			WFIFOL(fd,len+5) = qd->limit/* - quest_db[quest_search_db(qd->nameid)].limit*/;
			WFIFOL(fd,len+9) = qd->limit;
			for(j = 0, n = 0; j < 3; j++) {
				if((id = (int)qd->mob[j].id) != 0) {
					WFIFOL(fd,len+15+n*44) = (qd->nameid * 1000) + j;
					WFIFOL(fd,len+19+n*44) = 0;
					WFIFOL(fd,len+23+n*44) = id;
					WFIFOW(fd,len+27+n*44) = 0;
					WFIFOW(fd,len+29+n*44) = 0;
					WFIFOW(fd,len+31+n*44) = qd->mob[j].count;
					WFIFOW(fd,len+33+n*44) = qd->mob[j].max;
					if(mobdb_exists(id)) {
						strncpy(WFIFOP(fd,len+35+n*44),mobdb_search(id)->jname,24);
					} else {
						memset(WFIFOP(fd,len+35+n*44), 0, 24);
					}
					n++;
				}
			}
			WFIFOW(fd,len+13) = n;
			len += 15+n*44;
			active++;
		}
	}
#endif
	WFIFOW(fd,2) = len;
	WFIFOL(fd,4) = active;
	WFIFOSET(fd,len);

	return;
}

/*==========================================
 * �N�G�X�g���X�g�ڍ�
 *------------------------------------------
 */
void clif_questlist_info(struct map_session_data *sd)
{
	int fd, i, j, n, id, len=8;
	int active=0;

	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x2b2;
	for(i = 0; i < sd->questlist; i++) {
		struct quest_data *qd = &sd->quest[i];
		if(qd->nameid != 0 && qd->state < 2) {
			WFIFOL(fd,len)   = qd->nameid;
			WFIFOL(fd,len+4) = 1;
			WFIFOL(fd,len+8) = qd->limit;
			for(j = 0, n = 0; j < 3; j++) {
				if((id = (int)qd->mob[j].id) != 0) {
					WFIFOL(fd,len+14+n*30) = id;
					WFIFOW(fd,len+18+n*30) = qd->mob[j].count;
					if(mobdb_exists(id)) {
						strncpy(WFIFOP(fd,len+20+n*30),mobdb_search(id)->jname,24);
					} else {
						memset(WFIFOP(fd,len+20+n*30), 0, 24);
					}
					n++;
				}
			}
			WFIFOW(fd,len+12) = n;
			len += 104;
			active++;
		}
	}
	WFIFOW(fd,2) = len;
	WFIFOL(fd,4) = active;
	WFIFOSET(fd,len);

	return;
}

/*==========================================
 * �N�G�X�g���X�g�ǉ�
 *------------------------------------------
 */
void clif_add_questlist(struct map_session_data *sd, int quest_id)
{
	int fd, i, n, id;
	struct quest_data *qd;

	nullpo_retv(sd);

	qd = quest_get_data(sd, quest_id);
	if(qd == NULL)
		return;

	fd = sd->fd;
	n = 0;

#if PACKETVER < 20150513
	WFIFOW(fd,0) = 0x2b3;
	WFIFOL(fd,2) = qd->nameid;
	WFIFOB(fd,6) = qd->state;
	WFIFOL(fd,7) = 0;
	WFIFOL(fd,11) = qd->limit;
	for(i = 0; i < 3; i++) {
		if((id = (int)qd->mob[i].id) != 0) {
			WFIFOL(fd,17+n*30) = id;
			WFIFOW(fd,21+n*30) = qd->mob[i].count;
			if(mobdb_exists(id)) {
				strncpy(WFIFOP(fd,23+n*30),mobdb_search(id)->jname,24);
			} else {
				memset(WFIFOP(fd,23+n*30), 0, 24);
			}
			n++;
		}
	}
	WFIFOW(fd,15) = n;
	WFIFOSET(fd,packet_db[0x2b3].len);
#elif PACKETVER < 20181017
	WFIFOW(fd,0) = 0x9f9;
	WFIFOL(fd,2) = qd->nameid;
	WFIFOB(fd,6) = qd->state;
	WFIFOL(fd,7) = 0;
	WFIFOL(fd,11) = qd->limit;
	for(i = 0; i < 3; i++) {
		if((id = (int)qd->mob[i].id) != 0) {
			WFIFOL(fd,17+n*42) = (qd->nameid * 1000) + i;
			WFIFOL(fd,21+n*42) = 0;
			WFIFOL(fd,25+n*42) = id;
			WFIFOW(fd,29+n*42) = 0;
			WFIFOW(fd,31+n*42) = 0;
			WFIFOW(fd,33+n*42) = qd->mob[i].count;
			if(mobdb_exists(id)) {
				strncpy(WFIFOP(fd,35+n*42),mobdb_search(id)->jname,24);
			} else {
				memset(WFIFOP(fd,35+n*42), 0, 24);
			}
			n++;
		}
	}
	WFIFOW(fd,15) = n;
	WFIFOSET(fd,packet_db[0x9f9].len);
#else
	WFIFOW(fd,0) = 0xb0c;
	WFIFOL(fd,2) = qd->nameid;
	WFIFOB(fd,6) = qd->state;
	WFIFOL(fd,7) = 0;
	WFIFOL(fd,11) = qd->limit;
	for(i = 0; i < 3; i++) {
		if((id = (int)qd->mob[i].id) != 0) {
			WFIFOL(fd,17+n*46) = qd->nameid;
			WFIFOL(fd,21+n*46) = i;
			WFIFOL(fd,25+n*46) = 0;
			WFIFOL(fd,29+n*46) = id;
			WFIFOW(fd,33+n*46) = 0;
			WFIFOW(fd,35+n*46) = 0;
			WFIFOW(fd,37+n*46) = qd->mob[i].count;
			if(mobdb_exists(id)) {
				strncpy(WFIFOP(fd,39+n*46),mobdb_search(id)->jname,24);
			} else {
				memset(WFIFOP(fd,39+n*46), 0, 24);
			}
			n++;
		}
	}
	WFIFOW(fd,15) = n;
	WFIFOSET(fd,packet_db[0xb0c].len);
#endif
	return;
}

/*==========================================
 * �N�G�X�g���X�g�폜
 *------------------------------------------
 */
void clif_del_questlist(struct map_session_data *sd, int quest_id)
{
	int fd;

	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x2b4;
	WFIFOL(fd,2) = quest_id;
	WFIFOSET(fd,packet_db[0x2b4].len);

	return;
}

/*==========================================
 * �N�G�X�g���X�g�������X�V
 *------------------------------------------
 */
void clif_update_questcount(struct map_session_data *sd, int quest_id)
{
	int fd, i, n = 0;
	struct quest_data *qd;

	nullpo_retv(sd);

	qd = quest_get_data(sd, quest_id);
	if(qd == NULL)
		return;

	fd = sd->fd;

#if PACKETVER < 20150513
	WFIFOW(fd,0) = 0x2b5;
	for(i = 0; i < 3; i++) {
		if(qd->mob[i].id != 0) {
			WFIFOL(fd, 6+n*12) = qd->nameid;
			WFIFOL(fd,10+n*12) = qd->mob[i].id;
			WFIFOW(fd,14+n*12) = qd->mob[i].max;
			WFIFOW(fd,16+n*12) = qd->mob[i].count;
			n++;
		}
	}
	WFIFOW(fd,2) = n * 12 + 6;
#elif PACKETVER < 20181017
	WFIFOW(fd,0) = 0x9fa;
	for(i = 0; i < 3; i++) {
		if(qd->mob[i].id != 0) {
			WFIFOL(fd, 6+n*12) = qd->nameid;
			WFIFOL(fd,10+n*12) = (qd->nameid * 1000) + i;
			WFIFOW(fd,14+n*12) = qd->mob[i].max;
			WFIFOW(fd,16+n*12) = qd->mob[i].count;
			n++;
		}
	}
	WFIFOW(fd,2) = n * 12 + 6;
#else
	WFIFOW(fd,0) = 0xafe;
	for(i = 0; i < 3; i++) {
		if(qd->mob[i].id != 0) {
			WFIFOL(fd, 6+n*16) = qd->nameid;
			WFIFOL(fd,10+n*16) = qd->nameid;
			WFIFOL(fd,14+n*16) = i;
			WFIFOW(fd,18+n*16) = qd->mob[i].max;
			WFIFOW(fd,20+n*16) = qd->mob[i].count;
			n++;
		}
	}
	WFIFOW(fd,2) = n * 16 + 6;
#endif
	WFIFOW(fd,4) = n;
	WFIFOSET(fd,WFIFOW(fd,2));

	return;
}

/*==========================================
 * �N�G�X�g���X�g�������X�V2
 *------------------------------------------
 */
void clif_update_questcount2(struct map_session_data *sd, int quest_id)
{
#if PACKETVER >= 20150513
	int fd, i, n = 0;
	struct quest_data *qd;

	nullpo_retv(sd);

	qd = quest_get_data(sd, quest_id);
	if(qd == NULL)
		return;

	fd = sd->fd;
	WFIFOW(fd,0) = 0x8fe;
	for(i = 0; i < 3; i++) {
		if(qd->mob[i].id != 0) {
			WFIFOL(fd, 4+n*12) = qd->nameid;
			WFIFOL(fd, 8+n*12) = qd->mob[i].id;
			WFIFOW(fd,12+n*12) = qd->mob[i].max;
			WFIFOW(fd,14+n*12) = qd->mob[i].count;
			n++;
		}
	}
	WFIFOW(fd,2) = n * 12 + 4;
	WFIFOSET(fd,WFIFOW(fd,2));

	return;
#endif
}

/*==========================================
 * �p�[�e�B�[�����o�[�A�C�e���l�����b�Z�[�W
 *------------------------------------------
 */
void clif_show_partyshareitem(struct map_session_data *sd, struct item *item_data)
{
	unsigned char buf[33];
	struct item_data *id;

	nullpo_retv(sd);
	nullpo_retv(item_data);

	id = itemdb_search(item_data->nameid);

#if PACKETVER < 20180704
	WBUFW(buf,0)=0x2b8;
	WBUFL(buf,2) = sd->status.account_id;
	WBUFW(buf,6) = item_data->nameid;
	WBUFB(buf,8) = item_data->identify;
	WBUFB(buf,9) = item_data->attribute;
	WBUFB(buf,10) = item_data->refine;
	WBUFW(buf,11) = item_data->card[0];
	WBUFW(buf,13) = item_data->card[1];
	WBUFW(buf,15) = item_data->card[2];
	WBUFW(buf,17) = item_data->card[3];
	WBUFW(buf,19) = id->equip;
	WBUFB(buf,21) = id->type;
#else
	WBUFW(buf,0)=0x2b8;
	WBUFL(buf,2) = sd->status.account_id;
	WBUFL(buf,6) = item_data->nameid;
	WBUFB(buf,10) = item_data->identify;
	WBUFB(buf,11) = item_data->attribute;
	WBUFB(buf,12) = item_data->refine;
	WBUFL(buf,13) = item_data->card[0];
	WBUFL(buf,17) = item_data->card[1];
	WBUFL(buf,21) = item_data->card[2];
	WBUFL(buf,25) = item_data->card[3];
	WBUFW(buf,29) = id->equip;
	WBUFB(buf,31) = id->type;
#endif
	clif_send(buf,packet_db[0x2b8].len,&sd->bl,PARTY_SAMEMAP_WOS);

	return;
}

/*==========================================
 * �����j��
 *------------------------------------------
 */
void clif_break_equip(struct map_session_data *sd, int where)
{
#if PACKETVER >= 20071106
	unsigned char buf[16];

	nullpo_retv(sd);

	WBUFW(buf,0) = 0x2bb;
	WBUFW(buf,2) = where;
	WBUFL(buf,4) = sd->bl.id;
	clif_send(buf,packet_db[0x2bb].len,&sd->bl,PARTY_SAMEMAP_WOS);
#endif

	return;
}

/*==========================================
 * msgstringtable�\���i�������������j
 *------------------------------------------
 */
void clif_msgstringtable2(struct map_session_data *sd, int line, const char *mes)
{
	int fd;
	size_t len;

	nullpo_retv(sd);

	fd  = sd->fd;
	len = strlen(mes)+1;
	WFIFOW(fd,0) = 0x2c2;
	WFIFOW(fd,2) = (unsigned short)(len+6);
	WFIFOW(fd,4) = line;
	memcpy(WFIFOP(fd,6),mes,len);
	WFIFOSET(fd,WFIFOW(fd,2));

	return;
}

/*==========================================
 * msgstringtable�\���i���l��������j
 *------------------------------------------
 */
void clif_msgstringtable3(struct map_session_data *sd, int line, int value)
{
	int fd;

	nullpo_retv(sd);

	fd  = sd->fd;
	WFIFOW(fd,0) = 0x7e2;
	WFIFOW(fd,2) = line;
	WFIFOL(fd,4) = value;
	WFIFOSET(fd,packet_db[0x7e2].len);

	return;
}

/*==========================================
 * �������A���_���W�����쐬
 *------------------------------------------
 */
void clif_memorial_create(struct map_session_data *sd, const char *name, int num, int flag)
{
#if PACKETVER >= 20071128
	unsigned char buf[65];

	nullpo_retv(sd);

	WBUFW(buf,0) = 0x2cb;
	memcpy(WBUFP(buf,2),name,61);
	WBUFB(buf,62) = '\0';	// \0 terminal
	WBUFW(buf,63) = num;
	if(flag) {	// �p�[�e�B�[�S�̂ɑ��M
		clif_send(buf,packet_db[0x2cb].len,&sd->bl,PARTY);
	} else {	// �ʂɑ��M
		memcpy(WFIFOP(sd->fd,0),buf,packet_db[0x2cb].len);
		WFIFOSET(sd->fd,packet_db[0x2cb].len);
	}
#endif

	return;
}

/*==========================================
 * �������A���_���W�����ҋ@��ԕύX
 *------------------------------------------
 */
void clif_memorial_changewait(struct map_session_data *sd, int num, int flag)
{
#if PACKETVER >= 20071128
	unsigned char buf[4];

	nullpo_retv(sd);

	WBUFW(buf,0) = 0x2cc;
	WBUFW(buf,2) = num;
	if(flag) {	// �p�[�e�B�[�S�̂ɑ��M
		clif_send(buf,packet_db[0x2cc].len,&sd->bl,PARTY);
	} else {	// �ʂɑ��M
		memcpy(WFIFOP(sd->fd,0),buf,packet_db[0x2cc].len);
		WFIFOSET(sd->fd,packet_db[0x2cc].len);
	}
#endif

	return;
}

/*==========================================
 * �������A���_���W������Ԓʒm
 *------------------------------------------
 */
void clif_memorial_status(struct map_session_data *sd, const char *name, unsigned int limit1, unsigned int limit2, int flag)
{
#if PACKETVER >= 20071128
	unsigned char buf[71];

	nullpo_retv(sd);

	WBUFW(buf,0) = 0x2cd;
	memcpy(WBUFP(buf,2),name,61);
	WBUFB(buf,62) = '\0';	// \0 terminal
	WBUFL(buf,63) = limit1;
	WBUFL(buf,67) = limit2;
	if(flag) {	// �p�[�e�B�[�S�̂ɑ��M
		clif_send(buf,packet_db[0x2cd].len,&sd->bl,PARTY);
	} else {	// �ʂɑ��M
		memcpy(WFIFOP(sd->fd,0),buf,packet_db[0x2cd].len);
		WFIFOSET(sd->fd,packet_db[0x2cd].len);
	}
#endif

	return;
}

/*==========================================
 * �������A���_���W�����i�s�ύX�ʒm
 *------------------------------------------
 */
void clif_memorial_changestatus(struct map_session_data *sd, int type, unsigned int limit, int flag)
{
#if PACKETVER >= 20071128
	unsigned char buf[10];

	nullpo_retv(sd);

	WBUFW(buf,0) = 0x2ce;
	WBUFL(buf,2) = type;
	WBUFL(buf,6) = limit;
	if(flag) {	// �p�[�e�B�[�S�̂ɑ��M
		clif_send(buf,packet_db[0x2ce].len,&sd->bl,PARTY);
	} else {	// �ʂɑ��M
		memcpy(WFIFOP(sd->fd,0),buf,packet_db[0x2ce].len);
		WFIFOSET(sd->fd,packet_db[0x2ce].len);
	}
#endif

	return;
}

/*==========================================
 * �����E�B���h�E���
 *------------------------------------------
 */
void clif_party_equiplist(struct map_session_data *sd, struct map_session_data *tsd)
{
	int i, j, k, n=0, fd;

	nullpo_retv(sd);
	nullpo_retv(tsd);

	fd = sd->fd;

#if PACKETVER < 20100629
	WFIFOW(fd,0) = 0x2d7;
	memcpy(WFIFOP(fd,4), tsd->status.name, 24);
	WFIFOW(fd,28) = tsd->status.class_;
	WFIFOW(fd,30) = tsd->status.hair;
	WFIFOW(fd,32) = tsd->status.head_top;
	WFIFOW(fd,34) = tsd->status.head_mid;
	WFIFOW(fd,36) = tsd->status.head_bottom;
	WFIFOW(fd,38) = tsd->status.hair_color;
	WFIFOW(fd,40) = tsd->status.clothes_color;
	WFIFOB(fd,42) = tsd->sex;

	for(i=0,k=0; i<MAX_INVENTORY && k<tsd->inventory_num; i++) {
		if(tsd->status.inventory[i].nameid <= 0 || tsd->inventory_data[i] == NULL)
			continue;
		k++;
		if(!itemdb_isequip2(tsd->inventory_data[i]))
			continue;
		WFIFOW(fd,n*26+43) = i + 2;
		if(tsd->inventory_data[i]->view_id > 0)
			WFIFOW(fd,n*26+45) = tsd->inventory_data[i]->view_id;
		else
			WFIFOW(fd,n*26+45) = tsd->status.inventory[i].nameid;
		WFIFOB(fd,n*26+47) = tsd->inventory_data[i]->type;
		WFIFOB(fd,n*26+48) = tsd->status.inventory[i].identify;
		WFIFOW(fd,n*26+49) = pc_equippoint(tsd,i);
		WFIFOW(fd,n*26+51) = tsd->status.inventory[i].equip;
		WFIFOB(fd,n*26+53) = tsd->status.inventory[i].attribute;
		WFIFOB(fd,n*26+54) = tsd->status.inventory[i].refine;
		if(itemdb_isspecial(tsd->status.inventory[i].card[0])) {
			if(tsd->inventory_data[i]->flag.pet_egg) {
				WFIFOW(fd,n*26+55) = 0;
				WFIFOW(fd,n*26+57) = 0;
				WFIFOW(fd,n*26+59) = 0;
			} else {
				WFIFOW(fd,n*26+55) = tsd->status.inventory[i].card[0];
				WFIFOW(fd,n*26+57) = tsd->status.inventory[i].card[1];
				WFIFOW(fd,n*26+59) = tsd->status.inventory[i].card[2];
			}
			WFIFOW(fd,n*26+61) = tsd->status.inventory[i].card[3];
		} else {
			if(tsd->status.inventory[i].card[0] > 0 && (j = itemdb_viewid(tsd->status.inventory[i].card[0])) > 0)
				WFIFOW(fd,n*26+55) = j;
			else
				WFIFOW(fd,n*26+55) = tsd->status.inventory[i].card[0];
			if(tsd->status.inventory[i].card[1] > 0 && (j = itemdb_viewid(tsd->status.inventory[i].card[1])) > 0)
				WFIFOW(fd,n*26+57) = j;
			else
				WFIFOW(fd,n*26+57) = tsd->status.inventory[i].card[1];
			if(tsd->status.inventory[i].card[2] > 0 && (j = itemdb_viewid(tsd->status.inventory[i].card[2])) > 0)
				WFIFOW(fd,n*26+59) = j;
			else
				WFIFOW(fd,n*26+59) = tsd->status.inventory[i].card[2];
			if(tsd->status.inventory[i].card[3] > 0 && (j = itemdb_viewid(tsd->status.inventory[i].card[3])) > 0)
				WFIFOW(fd,n*26+61) = j;
			else
				WFIFOW(fd,n*26+61) = tsd->status.inventory[i].card[3];
		}
		WFIFOL(fd,n*26+63) = tsd->status.inventory[i].limit;
		WFIFOW(fd,n*26+67) = 0;
		n++;
	}
	if(n) {
		WFIFOW(fd,2) = 43 + n*26;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#elif PACKETVER < 20110111
	WFIFOW(fd,0) = 0x2d7;
	memcpy(WFIFOP(fd,4), tsd->status.name, 24);
	WFIFOW(fd,28) = tsd->status.class_;
	WFIFOW(fd,30) = tsd->status.hair;
	WFIFOW(fd,32) = tsd->status.head_bottom;
	WFIFOW(fd,34) = tsd->status.head_mid;
	WFIFOW(fd,36) = tsd->status.head_top;
	WFIFOW(fd,38) = tsd->status.hair_color;
	WFIFOW(fd,40) = tsd->status.clothes_color;
	WFIFOB(fd,42) = tsd->sex;

	for(i=0,k=0; i<MAX_INVENTORY && k<tsd->inventory_num; i++) {
		if(tsd->status.inventory[i].nameid <= 0 || tsd->inventory_data[i] == NULL)
			continue;
		k++;
		if(!itemdb_isequip2(tsd->inventory_data[i]))
			continue;
		WFIFOW(fd,n*28+43) = i + 2;
		if(tsd->inventory_data[i]->view_id > 0)
			WFIFOW(fd,n*28+45) = tsd->inventory_data[i]->view_id;
		else
			WFIFOW(fd,n*28+45) = tsd->status.inventory[i].nameid;
		WFIFOB(fd,n*28+47) = tsd->inventory_data[i]->type;
		WFIFOB(fd,n*28+48) = tsd->status.inventory[i].identify;
		WFIFOW(fd,n*28+49) = pc_equippoint(tsd,i);
		WFIFOW(fd,n*28+51) = tsd->status.inventory[i].equip;
		WFIFOB(fd,n*28+53) = tsd->status.inventory[i].attribute;
		WFIFOB(fd,n*28+54) = tsd->status.inventory[i].refine;
		if(itemdb_isspecial(tsd->status.inventory[i].card[0])) {
			if(tsd->inventory_data[i]->flag.pet_egg) {
				WFIFOW(fd,n*28+55) = 0;
				WFIFOW(fd,n*28+57) = 0;
				WFIFOW(fd,n*28+59) = 0;
			} else {
				WFIFOW(fd,n*28+55) = tsd->status.inventory[i].card[0];
				WFIFOW(fd,n*28+57) = tsd->status.inventory[i].card[1];
				WFIFOW(fd,n*28+59) = tsd->status.inventory[i].card[2];
			}
			WFIFOW(fd,n*28+61) = tsd->status.inventory[i].card[3];
		} else {
			if(tsd->status.inventory[i].card[0] > 0 && (j = itemdb_viewid(tsd->status.inventory[i].card[0])) > 0)
				WFIFOW(fd,n*28+55) = j;
			else
				WFIFOW(fd,n*28+55) = tsd->status.inventory[i].card[0];
			if(tsd->status.inventory[i].card[1] > 0 && (j = itemdb_viewid(tsd->status.inventory[i].card[1])) > 0)
				WFIFOW(fd,n*28+57) = j;
			else
				WFIFOW(fd,n*28+57) = tsd->status.inventory[i].card[1];
			if(tsd->status.inventory[i].card[2] > 0 && (j = itemdb_viewid(tsd->status.inventory[i].card[2])) > 0)
				WFIFOW(fd,n*28+59) = j;
			else
				WFIFOW(fd,n*28+59) = tsd->status.inventory[i].card[2];
			if(tsd->status.inventory[i].card[3] > 0 && (j = itemdb_viewid(tsd->status.inventory[i].card[3])) > 0)
				WFIFOW(fd,n*28+61) = j;
			else
				WFIFOW(fd,n*28+61) = tsd->status.inventory[i].card[3];
		}
		WFIFOL(fd,n*28+63) = tsd->status.inventory[i].limit;
		WFIFOW(fd,n*28+67) = 0;
		if(tsd->inventory_data[i]->equip&LOC_HEAD_TMB)
			WFIFOW(fd,n*28+69)=tsd->inventory_data[i]->look;
		else
			WFIFOW(fd,n*28+69)=0;
		n++;
	}
	if(n) {
		WFIFOW(fd,2) = 43 + n*28;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#elif PACKETVER < 20111025
	WFIFOW(fd,0) = 0x859;
	memcpy(WFIFOP(fd,4), tsd->status.name, 24);
	WFIFOW(fd,28) = tsd->status.class_;
	WFIFOW(fd,30) = tsd->status.hair;
	WFIFOW(fd,32) = tsd->status.head_bottom;
	WFIFOW(fd,34) = tsd->status.head_mid;
	WFIFOW(fd,36) = tsd->status.head_top;
	WFIFOW(fd,38) = tsd->status.robe;
	WFIFOW(fd,40) = tsd->status.hair_color;
	WFIFOW(fd,42) = tsd->status.clothes_color;
	WFIFOB(fd,44) = tsd->sex;

	for(i=0,k=0; i<MAX_INVENTORY && k<tsd->inventory_num; i++) {
		if(tsd->status.inventory[i].nameid <= 0 || tsd->inventory_data[i] == NULL)
			continue;
		k++;
		if(!itemdb_isequip2(tsd->inventory_data[i]))
			continue;
		WFIFOW(fd,n*28+45) = i + 2;
		if(tsd->inventory_data[i]->view_id > 0)
			WFIFOW(fd,n*28+47) = tsd->inventory_data[i]->view_id;
		else
			WFIFOW(fd,n*28+47) = tsd->status.inventory[i].nameid;
		WFIFOB(fd,n*28+49) = tsd->inventory_data[i]->type;
		WFIFOB(fd,n*28+50) = tsd->status.inventory[i].identify;
		WFIFOW(fd,n*28+51) = pc_equippoint(tsd,i);
		WFIFOW(fd,n*28+53) = tsd->status.inventory[i].equip;
		WFIFOB(fd,n*28+55) = tsd->status.inventory[i].attribute;
		WFIFOB(fd,n*28+56) = tsd->status.inventory[i].refine;
		if(itemdb_isspecial(tsd->status.inventory[i].card[0])) {
			if(tsd->inventory_data[i]->flag.pet_egg) {
				WFIFOW(fd,n*28+57) = 0;
				WFIFOW(fd,n*28+59) = 0;
				WFIFOW(fd,n*28+61) = 0;
			} else {
				WFIFOW(fd,n*28+57) = tsd->status.inventory[i].card[0];
				WFIFOW(fd,n*28+59) = tsd->status.inventory[i].card[1];
				WFIFOW(fd,n*28+61) = tsd->status.inventory[i].card[2];
			}
			WFIFOW(fd,n*28+63) = tsd->status.inventory[i].card[3];
		} else {
			if(tsd->status.inventory[i].card[0] > 0 && (j = itemdb_viewid(tsd->status.inventory[i].card[0])) > 0)
				WFIFOW(fd,n*28+57) = j;
			else
				WFIFOW(fd,n*28+57) = tsd->status.inventory[i].card[0];
			if(tsd->status.inventory[i].card[1] > 0 && (j = itemdb_viewid(tsd->status.inventory[i].card[1])) > 0)
				WFIFOW(fd,n*28+59) = j;
			else
				WFIFOW(fd,n*28+59) = tsd->status.inventory[i].card[1];
			if(tsd->status.inventory[i].card[2] > 0 && (j = itemdb_viewid(tsd->status.inventory[i].card[2])) > 0)
				WFIFOW(fd,n*28+61) = j;
			else
				WFIFOW(fd,n*28+61) = tsd->status.inventory[i].card[2];
			if(tsd->status.inventory[i].card[3] > 0 && (j = itemdb_viewid(tsd->status.inventory[i].card[3])) > 0)
				WFIFOW(fd,n*28+63) = j;
			else
				WFIFOW(fd,n*28+63) = tsd->status.inventory[i].card[3];
		}
		WFIFOL(fd,n*28+65) = tsd->status.inventory[i].limit;
		WFIFOW(fd,n*28+69) = 0;
		if(tsd->inventory_data[i]->equip&LOC_HEAD_TMB)
			WFIFOW(fd,n*28+71)=tsd->inventory_data[i]->look;
		else
			WFIFOW(fd,n*28+71)=0;
		n++;
	}
	if(n) {
		WFIFOW(fd,2) = 45 + n*28;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#elif PACKETVER < 20120925
	WFIFOW(fd,0) = 0x906;
	memcpy(WFIFOP(fd,4), tsd->status.name, 24);
	WFIFOW(fd,28) = tsd->status.class_;
	WFIFOW(fd,30) = tsd->status.hair;
	WFIFOW(fd,32) = tsd->status.head_bottom;
	WFIFOW(fd,34) = tsd->status.head_mid;
	WFIFOW(fd,36) = tsd->status.head_top;
	WFIFOW(fd,38) = tsd->status.robe;
	WFIFOW(fd,40) = tsd->status.hair_color;
	WFIFOW(fd,42) = tsd->status.clothes_color;
	WFIFOB(fd,44) = tsd->sex;

	for(i=0,k=0; i<MAX_INVENTORY && k<tsd->inventory_num; i++) {
		if(tsd->status.inventory[i].nameid <= 0 || tsd->inventory_data[i] == NULL)
			continue;
		k++;
		if(!itemdb_isequip2(tsd->inventory_data[i]))
			continue;
		WFIFOW(fd,n*27+45) = i + 2;
		if(tsd->inventory_data[i]->view_id > 0)
			WFIFOW(fd,n*27+47) = tsd->inventory_data[i]->view_id;
		else
			WFIFOW(fd,n*27+47) = tsd->status.inventory[i].nameid;
		WFIFOB(fd,n*27+49) = tsd->inventory_data[i]->type;
		WFIFOW(fd,n*27+50) = pc_equippoint(tsd,i);
		WFIFOW(fd,n*27+52) = tsd->status.inventory[i].equip;
		WFIFOB(fd,n*27+54) = tsd->status.inventory[i].refine;
		if(itemdb_isspecial(tsd->status.inventory[i].card[0])) {
			if(tsd->inventory_data[i]->flag.pet_egg) {
				WFIFOW(fd,n*27+55) = 0;
				WFIFOW(fd,n*27+57) = 0;
				WFIFOW(fd,n*27+59) = 0;
			} else {
				WFIFOW(fd,n*27+55) = tsd->status.inventory[i].card[0];
				WFIFOW(fd,n*27+57) = tsd->status.inventory[i].card[1];
				WFIFOW(fd,n*27+59) = tsd->status.inventory[i].card[2];
			}
			WFIFOW(fd,n*27+61) = tsd->status.inventory[i].card[3];
		} else {
			if(tsd->status.inventory[i].card[0] > 0 && (j = itemdb_viewid(tsd->status.inventory[i].card[0])) > 0)
				WFIFOW(fd,n*27+55) = j;
			else
				WFIFOW(fd,n*27+55) = tsd->status.inventory[i].card[0];
			if(tsd->status.inventory[i].card[1] > 0 && (j = itemdb_viewid(tsd->status.inventory[i].card[1])) > 0)
				WFIFOW(fd,n*27+57) = j;
			else
				WFIFOW(fd,n*27+57) = tsd->status.inventory[i].card[1];
			if(tsd->status.inventory[i].card[2] > 0 && (j = itemdb_viewid(tsd->status.inventory[i].card[2])) > 0)
				WFIFOW(fd,n*27+59) = j;
			else
				WFIFOW(fd,n*27+59) = tsd->status.inventory[i].card[2];
			if(tsd->status.inventory[i].card[3] > 0 && (j = itemdb_viewid(tsd->status.inventory[i].card[3])) > 0)
				WFIFOW(fd,n*27+61) = j;
			else
				WFIFOW(fd,n*27+61) = tsd->status.inventory[i].card[3];
		}
		WFIFOL(fd,n*27+63) = tsd->status.inventory[i].limit;
		WFIFOW(fd,n*27+67) = 0;
		if(tsd->inventory_data[i]->equip&LOC_HEAD_TMB)
			WFIFOW(fd,n*27+69)=tsd->inventory_data[i]->look;
		else
			WFIFOW(fd,n*27+69)=0;
		WFIFOB(fd,n*27+71) = tsd->status.inventory[i].identify+(tsd->status.inventory[i].attribute?2:0);
		n++;
	}
	if(n) {
		WFIFOW(fd,2) = 45 + n*27;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#elif PACKETVER < 20180704
	WFIFOW(fd,0) = 0x997;
	memcpy(WFIFOP(fd,4), tsd->status.name, 24);
	WFIFOW(fd,28) = tsd->status.class_;
	WFIFOW(fd,30) = tsd->status.hair;
	WFIFOW(fd,32) = tsd->status.head_bottom;
	WFIFOW(fd,34) = tsd->status.head_mid;
	WFIFOW(fd,36) = tsd->status.head_top;
	WFIFOW(fd,38) = tsd->status.robe;
	WFIFOW(fd,40) = tsd->status.hair_color;
	WFIFOW(fd,42) = tsd->status.clothes_color;
	WFIFOB(fd,44) = tsd->sex;

	for(i=0,k=0; i<MAX_INVENTORY && k<tsd->inventory_num; i++) {
		if(tsd->status.inventory[i].nameid <= 0 || tsd->inventory_data[i] == NULL)
			continue;
		k++;
		if(!itemdb_isequip2(tsd->inventory_data[i]))
			continue;
		WFIFOW(fd,n*31+45) = i + 2;
		if(tsd->inventory_data[i]->view_id > 0)
			WFIFOW(fd,n*31+47) = tsd->inventory_data[i]->view_id;
		else
			WFIFOW(fd,n*31+47) = tsd->status.inventory[i].nameid;
		WFIFOB(fd,n*31+49) = tsd->inventory_data[i]->type;
		WFIFOL(fd,n*31+50) = pc_equippoint(tsd,i);
		WFIFOL(fd,n*31+54) = tsd->status.inventory[i].equip;
		WFIFOB(fd,n*31+58) = tsd->status.inventory[i].refine;
		if(itemdb_isspecial(tsd->status.inventory[i].card[0])) {
			if(tsd->inventory_data[i]->flag.pet_egg) {
				WFIFOW(fd,n*31+59) = 0;
				WFIFOW(fd,n*31+61) = 0;
				WFIFOW(fd,n*31+63) = 0;
			} else {
				WFIFOW(fd,n*31+59) = tsd->status.inventory[i].card[0];
				WFIFOW(fd,n*31+61) = tsd->status.inventory[i].card[1];
				WFIFOW(fd,n*31+63) = tsd->status.inventory[i].card[2];
			}
			WFIFOW(fd,n*31+65) = tsd->status.inventory[i].card[3];
		} else {
			if(tsd->status.inventory[i].card[0] > 0 && (j = itemdb_viewid(tsd->status.inventory[i].card[0])) > 0)
				WFIFOW(fd,n*31+59) = j;
			else
				WFIFOW(fd,n*31+59) = tsd->status.inventory[i].card[0];
			if(tsd->status.inventory[i].card[1] > 0 && (j = itemdb_viewid(tsd->status.inventory[i].card[1])) > 0)
				WFIFOW(fd,n*31+61) = j;
			else
				WFIFOW(fd,n*31+61) = tsd->status.inventory[i].card[1];
			if(tsd->status.inventory[i].card[2] > 0 && (j = itemdb_viewid(tsd->status.inventory[i].card[2])) > 0)
				WFIFOW(fd,n*31+63) = j;
			else
				WFIFOW(fd,n*31+63) = tsd->status.inventory[i].card[2];
			if(tsd->status.inventory[i].card[3] > 0 && (j = itemdb_viewid(tsd->status.inventory[i].card[3])) > 0)
				WFIFOW(fd,n*31+65) = j;
			else
				WFIFOW(fd,n*31+65) = tsd->status.inventory[i].card[3];
		}
		WFIFOL(fd,n*31+67) = tsd->status.inventory[i].limit;
		WFIFOW(fd,n*31+71) = 0;
		if(tsd->inventory_data[i]->equip&LOC_HEAD_TMB)
			WFIFOW(fd,n*31+73)=tsd->inventory_data[i]->look;
		else
			WFIFOW(fd,n*31+73)=0;
		WFIFOB(fd,n*31+75) = tsd->status.inventory[i].identify+(tsd->status.inventory[i].attribute?2:0);
		n++;
	}
	if(n) {
		WFIFOW(fd,2) = 45 + n*31;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#else
	WFIFOW(fd,0) = 0x997;
	memcpy(WFIFOP(fd,4), tsd->status.name, 24);
	WFIFOW(fd,28) = tsd->status.class_;
	WFIFOW(fd,30) = tsd->status.hair;
	WFIFOW(fd,32) = tsd->status.head_bottom;
	WFIFOW(fd,34) = tsd->status.head_mid;
	WFIFOW(fd,36) = tsd->status.head_top;
	WFIFOW(fd,38) = tsd->status.robe;
	WFIFOW(fd,40) = tsd->status.hair_color;
	WFIFOW(fd,42) = tsd->status.clothes_color;
	WFIFOB(fd,44) = tsd->sex;

	for(i=0,k=0; i<MAX_INVENTORY && k<tsd->inventory_num; i++) {
		if(tsd->status.inventory[i].nameid <= 0 || tsd->inventory_data[i] == NULL)
			continue;
		k++;
		if(!itemdb_isequip2(tsd->inventory_data[i]))
			continue;
		WFIFOW(fd,n*41+45) = i + 2;
		if(tsd->inventory_data[i]->view_id > 0)
			WFIFOL(fd,n*41+47) = tsd->inventory_data[i]->view_id;
		else
			WFIFOL(fd,n*41+47) = tsd->status.inventory[i].nameid;
		WFIFOB(fd,n*41+51) = tsd->inventory_data[i]->type;
		WFIFOL(fd,n*41+52) = pc_equippoint(tsd,i);
		WFIFOL(fd,n*41+56) = tsd->status.inventory[i].equip;
		WFIFOB(fd,n*41+60) = tsd->status.inventory[i].refine;
		if(itemdb_isspecial(tsd->status.inventory[i].card[0])) {
			if(tsd->inventory_data[i]->flag.pet_egg) {
				WFIFOL(fd,n*41+61) = 0;
				WFIFOL(fd,n*41+65) = 0;
				WFIFOL(fd,n*41+69) = 0;
			} else {
				WFIFOL(fd,n*41+61) = tsd->status.inventory[i].card[0];
				WFIFOL(fd,n*41+65) = tsd->status.inventory[i].card[1];
				WFIFOL(fd,n*41+69) = tsd->status.inventory[i].card[2];
			}
			WFIFOL(fd,n*41+73) = tsd->status.inventory[i].card[3];
		} else {
			if(tsd->status.inventory[i].card[0] > 0 && (j = itemdb_viewid(tsd->status.inventory[i].card[0])) > 0)
				WFIFOL(fd,n*41+61) = j;
			else
				WFIFOL(fd,n*41+61) = tsd->status.inventory[i].card[0];
			if(tsd->status.inventory[i].card[1] > 0 && (j = itemdb_viewid(tsd->status.inventory[i].card[1])) > 0)
				WFIFOL(fd,n*41+65) = j;
			else
				WFIFOL(fd,n*41+65) = tsd->status.inventory[i].card[1];
			if(tsd->status.inventory[i].card[2] > 0 && (j = itemdb_viewid(tsd->status.inventory[i].card[2])) > 0)
				WFIFOL(fd,n*41+69) = j;
			else
				WFIFOL(fd,n*41+69) = tsd->status.inventory[i].card[2];
			if(tsd->status.inventory[i].card[3] > 0 && (j = itemdb_viewid(tsd->status.inventory[i].card[3])) > 0)
				WFIFOL(fd,n*41+73) = j;
			else
				WFIFOL(fd,n*41+73) = tsd->status.inventory[i].card[3];
		}
		WFIFOL(fd,n*41+77) = tsd->status.inventory[i].limit;
		WFIFOW(fd,n*41+81) = 0;
		if(tsd->inventory_data[i]->equip&LOC_HEAD_TMB)
			WFIFOW(fd,n*41+83)=tsd->inventory_data[i]->look;
		else
			WFIFOW(fd,n*41+83)=0;
		WFIFOB(fd,n*41+85) = tsd->status.inventory[i].identify+(tsd->status.inventory[i].attribute?2:0);
		n++;
	}
	if(n) {
		WFIFOW(fd,2) = 45 + n*41;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#endif

	return;
}

/*==========================================
 * �ݒ�ύX�v������
 *------------------------------------------
 */
static void clif_configack(struct map_session_data* sd, int type, int flag)
{
	int fd;

	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x2d9;
	WFIFOL(fd,2) = type;
	WFIFOL(fd,6) = flag;
	WFIFOSET(fd,packet_db[0x2d9].len);

	return;
}

/*==========================================
 * �ݒ��񑗐M
 *------------------------------------------
 */
void clif_send_config(struct map_session_data *sd)
{
#if PACKETVER >= 20170906
	int fd;

	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0xadc;
	WFIFOB(fd,2) = (unsigned char)sd->status.show_equip;
	WFIFOB(fd,3) = (unsigned char)sd->status.allow_call;
	WFIFOB(fd,4) = (sd->status.autofeed&1)? 1: 0;
	WFIFOB(fd,5) = (sd->status.autofeed&2)? 1: 0;
	WFIFOSET(fd,packet_db[0xadc].len);
#elif PACKETVER >= 20071106
	int fd;

	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x2da;
	WFIFOB(fd,2) = (unsigned char)sd->status.show_equip;
	WFIFOSET(fd,packet_db[0x2da].len);
#endif

	return;
}

/*==========================================
 * �t�H���g���Z�b�g����
 *------------------------------------------
 */
void clif_setfont(struct map_session_data *sd)
{
	unsigned char buf[8];

	nullpo_retv(sd);

	WBUFW(buf,0)=0x2ef;
	WBUFL(buf,2)=sd->bl.id;
	WBUFW(buf,6)=sd->status.font;
	clif_send(buf,packet_db[0x2ef].len,&sd->bl,AREA);

	return;
}

/*==========================================
 * �r���o�[�\��
 *------------------------------------------
 */
void clif_progressbar(struct map_session_data *sd, unsigned int color, unsigned int second)
{
	int fd;

	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x02f0;
	WFIFOL(fd,2) = color;
	WFIFOL(fd,6) = second;
	WFIFOSET(fd,packet_db[0x2f0].len);

	return;
}

/*==========================================
 * �r���o�[���f
 *------------------------------------------
 */
void clif_progressbar_abort(struct map_session_data *sd)
{
	int fd;

	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x02f2;
	WFIFOSET(fd,packet_db[0x2f2].len);

	return;
}

/*==========================================
 * �X�L���ŗL�f�B���C�\��
 *------------------------------------------
 */
void clif_skill_cooldown(struct map_session_data *sd, int skillid, unsigned int tick)
{
#if PACKETVER > 20080820
	int fd;

	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x043d;
	WFIFOW(fd,2) = skillid;
	WFIFOL(fd,4) = tick;
	WFIFOSET(fd,packet_db[0x43d].len);
#endif

	return;
}

/*==========================================
 * �~���j�A���V�[���h
 *------------------------------------------
 */
void clif_mshield(struct map_session_data *sd, int num)
{
	unsigned char buf[10];

	nullpo_retv(sd);

	WBUFW(buf,0)=0x440;
	WBUFL(buf,2)=sd->bl.id;
	WBUFW(buf,6)=num;
	WBUFW(buf,8)=0;
	clif_send(buf,packet_db[0x440].len,&sd->bl,AREA);

	return;
}

/*==========================================
 * �I�[�g�V���h�E�X�y��
 *------------------------------------------
 */
void clif_autoshadowspell(struct map_session_data *sd, short lv)
{
	int fd, c = 0;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd, 0)=0x442;

	if(skill_db[skill_get_skilldb_id( sd->skill_clone.id )].autoshadowspell) {
		WFIFOW(fd,8+c*2) = sd->skill_clone.id;
		c++;
	}

	if(skill_db[skill_get_skilldb_id( sd->skill_reproduce.id )].autoshadowspell) {
		WFIFOW(fd,8+c*2) = sd->skill_reproduce.id;
		c++;
	}

	if(c > 0) {
		WFIFOW(fd,2) = c * 2 + 8;
		WFIFOL(fd,4) = 1;
		WFIFOSET(fd, WFIFOW(fd,2));

		sd->skill_menu.id = SC_AUTOSHADOWSPELL;
		sd->skill_menu.lv = lv;
	} else {
		clif_skill_fail(sd,SC_AUTOSHADOWSPELL,SKILLFAIL_CLONESKILL,0,0);
	}

	return;
}

/*==========================================
 * NPC�C�x���g�\��
 *------------------------------------------
 */
void clif_showevent(struct map_session_data *sd, struct block_list *bl, short state, short type)
{
	int fd;

	nullpo_retv(sd);
	nullpo_retv(bl);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x446;
	WFIFOL(fd,2) = bl->id;
	WFIFOW(fd,6) = bl->x;
	WFIFOW(fd,8) = bl->y;
	WFIFOW(fd,10) = state;
	WFIFOW(fd,12) = type;
	WFIFOSET(fd,packet_db[0x446].len);

	return;
}

/*==========================================
 * �A�C�e���������X�g
 *------------------------------------------
 */
void clif_convertitem(struct map_session_data *sd, int skillid, int skilllv)
{
#if PACKETVER > 20090715
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0) = 0x7e3;
	WFIFOL(fd,2) = skilllv;
	WFIFOSET(fd, packet_db[0x7e3].len);

	sd->skill_menu.id = skillid;
	sd->skill_menu.lv = skilllv;
#endif

	return;
}

/*==========================================
 * �X�L�����b�Z�[�W
 *------------------------------------------
 */
void clif_skill_message(struct map_session_data *sd, int skillid, int type)
{
#if PACKETVER > 20091104
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0) = 0x7e6;
	WFIFOW(fd,2) = skillid;
	WFIFOL(fd,4) = type;
	WFIFOSET(fd, packet_db[0x7e6].len);
#endif

	return;
}

/*==========================================
 * �o���l�擾�\��
 *------------------------------------------
 */
void clif_dispexp(struct map_session_data *sd, atn_bignumber exp, short type, short quest)
{
	int fd;

	nullpo_retv(sd);

	fd = sd->fd;
#if PACKETVER < 20170830
	WFIFOW(fd,0) = 0x7f6;
	WFIFOL(fd,2) = sd->bl.id;
	WFIFOL(fd,6) = (int)exp;
	WFIFOW(fd,10) = type;
	WFIFOW(fd,12) = quest;
	WFIFOSET(fd,packet_db[0x7f6].len);
#else
	WFIFOW(fd,0) = 0xacc;
	WFIFOL(fd,2) = sd->bl.id;
	WFIFOQ(fd,6) = exp;
	WFIFOW(fd,14) = type;
	WFIFOW(fd,16) = quest;
	WFIFOSET(fd,packet_db[0xacc].len);
#endif

    return;
}

/*==========================================
 * �p�[�e�B�[���[�_�[�ύX���
 *------------------------------------------
 */
void clif_partyleader_info(struct party *p, int old_account_id, int account_id)
{
	unsigned char buf[16];
	struct map_session_data *sd = map_id2sd(account_id);

	nullpo_retv(p);

	if(!sd) {
		// ���[�_�[���I�t���C���Ȃ̂Ń��O�C�����̃����o�[��T��
		sd = party_getavailablesd(p);
		if(!sd)
			return;
	}

	WBUFW(buf,0) = 0x7fc;
	WBUFL(buf,2) = old_account_id;
	WBUFL(buf,6) = account_id;
	clif_send(buf,packet_db[0x7fc].len,&sd->bl,PARTY);

	return;
}

/*==========================================
 * ���y�t�@�C����炷
 *------------------------------------------
 */
void clif_musiceffect(struct map_session_data *sd, const char *name)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x7fe;
	strncpy(WFIFOP(fd,2),name,24);
	WFIFOSET(fd,packet_db[0x7fe].len);

	return;
}

/*==========================================
 * �p�[�e�B�[�u�b�L���O�o�^�v������
 *------------------------------------------
 */
void clif_bookingregack(struct map_session_data *sd, int flag)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
#if PACKETVER < 20120222
	WFIFOW(fd,0) = 0x803;
	WFIFOW(fd,2) = flag;
	WFIFOSET(fd,packet_db[0x803].len);
#else
	WFIFOW(fd,0) = 0x8e6;
	WFIFOW(fd,2) = flag;
	WFIFOSET(fd,packet_db[0x8e6].len);
#endif

	return;
}

/*==========================================
 * �p�[�e�B�[�u�b�L���O�����v������
 *------------------------------------------
 */
void clif_searchbookingack(struct map_session_data *sd, struct booking_data **list, int count, int flag)
{
	int fd, n = 0;

	nullpo_retv(sd);

	fd=sd->fd;
#if PACKETVER < 20120222
	WFIFOW(fd,0) = 0x805;
	if(list) {
		int i, j;
		for(i=0; i<count; i++) {
			struct booking_data *bd = list[i];
			WFIFOL(fd,n*48+5)=bd->id; 
			memcpy(WFIFOP(fd,n*48+9),bd->name,24);
			WFIFOL(fd,n*48+33)=bd->time;
			WFIFOW(fd,n*48+37)=bd->lv;
			WFIFOW(fd,n*48+39)=bd->map;
			for(j=0; j<6; j++)
				WFIFOW(fd,n*48+41+j*2) = bd->job[j];
			n++;
		}
	}
	WFIFOW(fd,2)=5+n*48;
	WFIFOB(fd,4)=(flag > 0) ? 1 : 0;
	WFIFOSET(fd,WFIFOW(fd,2));
#else
	WFIFOW(fd,0) = 0x8e8;
	if(list) {
		int i;
		for(i = 0; i < count; i++) {
			struct booking_data *bd = list[i];
			WFIFOL(fd,n*71+5)=bd->id;
			WFIFOL(fd,n*71+9)=bd->time;
			memcpy(WFIFOP(fd,n*71+13),bd->name,24);
			WFIFOW(fd,n*71+37)=bd->lv;
			memcpy(WFIFOP(fd,n*71+39),bd->memo,MAX_BOOKING_MEMO_LENGTH);
			n++;
		}
	}
	WFIFOW(fd,2)=5+n*71;
	WFIFOB(fd,4)=(flag > 0) ? 1 : 0;
	WFIFOSET(fd,WFIFOW(fd,2));
#endif

	return;
}

/*==========================================
 * �p�[�e�B�[�u�b�L���O�o�^�폜�v������
 *------------------------------------------
 */
void clif_deletebookingack(struct map_session_data* sd, int flag)
{
	int fd;

	nullpo_retv(sd);

	fd = sd->fd;
#if PACKETVER < 20120222
	WFIFOW(fd,0) = 0x807;
	WFIFOW(fd,2) = flag;
	WFIFOSET(fd,packet_db[0x807].len);
#else
	WFIFOW(fd,0) = 0x8ea;
	WFIFOW(fd,2) = flag;
	WFIFOSET(fd,packet_db[0x8ea].len);
#endif

	return;
}

/*==========================================
 * �p�[�e�B�[�u�b�L���O���X�g�ǉ�
 *------------------------------------------
 */
void clif_insertbookinglist(struct map_session_data *sd, struct booking_data *bd)
{
	unsigned char buf[73];

	nullpo_retv(sd);
	nullpo_retv(bd);

#if PACKETVER < 20120222
	WBUFW(buf,0) = 0x809;
	WBUFL(buf,2) = bd->id;
	memcpy(WBUFP(buf,6),bd->name,24);
	WBUFL(buf,30) = bd->time;
	WBUFW(buf,34) = bd->lv;
	WBUFW(buf,36) = bd->map;
	{
		int i;
		for(i=0; i<6; i++)
			WBUFW(buf,38+i*2) = bd->job[i];
	}
	clif_send(buf,packet_db[0x809].len,&sd->bl,ALL_CLIENT);
#else
	WBUFW(buf,0) = 0x8ec;
	WBUFL(buf,2) = bd->id;
	WBUFL(buf,6) = bd->time;
	memcpy(WBUFP(buf,10),bd->name,24);
	WBUFW(buf,34) = bd->lv;
	memcpy(WBUFP(buf,36),bd->memo,MAX_BOOKING_MEMO_LENGTH);

	clif_send(buf,packet_db[0x8ec].len,&sd->bl,ALL_CLIENT);
#endif

	return;
}

/*==========================================
 * �p�[�e�B�[�u�b�L���O���X�g�X�V
 *------------------------------------------
 */
void clif_updatebookinglist(struct map_session_data* sd, struct booking_data *bd)
{
	unsigned char buf[47];

	nullpo_retv(sd);
	nullpo_retv(bd);

#if PACKETVER < 20120222
	WBUFW(buf,0) = 0x80a;
	WBUFL(buf,2) = bd->id;
	{
		int i;
		for(i=0; i<6; i++)
			WBUFW(buf,6+i*2) = bd->job[i];
	}
	clif_send(buf,packet_db[0x80a].len,&sd->bl,ALL_CLIENT);
#else
	WBUFW(buf,0) = 0x8ed;
	WBUFL(buf,2) = bd->id;
	memcpy(WBUFP(buf,6),bd->memo,MAX_BOOKING_MEMO_LENGTH);
	clif_send(buf,packet_db[0x8ed].len,&sd->bl,ALL_CLIENT);
#endif

	return;
}

/*==========================================
 * �p�[�e�B�[�u�b�L���O�o�^�폜
 *------------------------------------------
 */
void clif_deletebooking(struct map_session_data* sd, unsigned int id)
{
	unsigned char buf[6];

	nullpo_retv(sd);

#if PACKETVER < 20120222
	WBUFW(buf,0) = 0x80b;
	WBUFL(buf,2) = id;
	clif_send(buf,packet_db[0x80b].len,&sd->bl,ALL_CLIENT);
#else
	WBUFW(buf,0) = 0x8ee;
	WBUFL(buf,2) = id;
	clif_send(buf,packet_db[0x8ee].len,&sd->bl,ALL_CLIENT);
#endif

	return;
}

/*==========================================
 * ����I�X�E�C���h�E�I�[�v��
 *------------------------------------------
 */
void clif_openwindow_buyingstore(struct map_session_data *sd)
{
	int fd;

	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x810;
	WFIFOB(fd,2) = sd->buyingstore.count;
	WFIFOSET(fd,packet_db[0x810].len);

	return;
}

/*==========================================
 * ����I�X�J�ݎ��s
 *------------------------------------------
 */
void clif_failed_openbuyingstore(struct map_session_data *sd, unsigned short result, int weight)
{
	int fd;

	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x812;
	WFIFOW(fd,2) = result;
	WFIFOL(fd,4) = weight;
	WFIFOSET(fd,packet_db[0x812].len);

	return;
}

/*==========================================
 * ����I�X���A�C�e�����X�g
 *------------------------------------------
 */
void clif_showmylist_buyingstore(struct map_session_data *sd)
{
	int fd;
	int i;

	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x813;
	WFIFOL(fd,4) = sd->bl.id;
	WFIFOL(fd,8) = sd->buyingstore.limit_zeny;

	for( i = 0; i < sd->buyingstore.count; i++ )
	{
#if PACKETVER < 20180704
		WFIFOL(fd,12+i*9) = sd->buyingstore.item[i].value;
		WFIFOW(fd,16+i*9) = sd->buyingstore.item[i].amount;
		WFIFOB(fd,18+i*9) = itemdb_search(sd->buyingstore.item[i].nameid)->type;
		WFIFOW(fd,19+i*9) = sd->buyingstore.item[i].nameid;
	}
	WFIFOW(fd,2) = 12+sd->buyingstore.count*9;
#else
		WFIFOL(fd,12+i*11) = sd->buyingstore.item[i].value;
		WFIFOW(fd,16+i*11) = sd->buyingstore.item[i].amount;
		WFIFOB(fd,18+i*11) = itemdb_search(sd->buyingstore.item[i].nameid)->type;
		WFIFOL(fd,19+i*11) = sd->buyingstore.item[i].nameid;
	}
	WFIFOW(fd,2) = 12+sd->buyingstore.count*11;
#endif
	WFIFOSET(fd,WFIFOW(fd,2));

	return;
}

/*==========================================
 * ����I�X�\��
 *------------------------------------------
 */
void clif_show_buyingstore(struct block_list *bl, const char *store_title, int fd)
{
	unsigned char buf[86];

	nullpo_retv(bl);

	WBUFW(buf,0) = 0x814;
	WBUFL(buf,2) = bl->id;
	memcpy(WBUFP(buf,6), store_title, 80);
	WBUFB(buf,85) = '\0';	// \0 terminal

	if(fd >= 0) {
		memcpy(WFIFOP(fd,0),buf,packet_db[0x814].len);
		WFIFOSET(fd,packet_db[0x814].len);
	} else {
		clif_send(buf,packet_db[0x814].len,bl,AREA_WOS);
	}

	return;
}

/*==========================================
 * ����I�X��
 *------------------------------------------
 */
void clif_close_buyingstore(struct block_list *bl, int fd)
{
	unsigned char buf[6];

	nullpo_retv(bl);

	WBUFW(buf,0) = 0x816;
	WBUFL(buf,2) = bl->id;
	if(fd >= 0) {
		memcpy(WFIFOP(fd,0),buf,packet_db[0x816].len);
		WFIFOSET(fd,packet_db[0x816].len);
	} else {
		clif_send(buf,packet_db[0x816].len,bl,AREA_WOS);
	}

	return;
}

/*==========================================
 * ����I�X�A�C�e�����X�g
 *------------------------------------------
 */
void clif_itemlist_buyingstore(struct map_session_data *sd, struct map_session_data *ssd)
{
	int fd;
	int i;

	nullpo_retv(sd);
	nullpo_retv(ssd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x818;
	WFIFOL(fd,4) = ssd->bl.id;
	WFIFOL(fd,8) = ssd->buyer_id;
	WFIFOL(fd,12) = ssd->buyingstore.limit_zeny;

	for( i = 0; i < ssd->buyingstore.count; i++ )
	{
#if PACKETVER < 20180704
		WFIFOL(fd,16+i*9) = ssd->buyingstore.item[i].value;
		WFIFOW(fd,20+i*9) = ssd->buyingstore.item[i].amount;
		WFIFOB(fd,22+i*9) = itemdb_search(ssd->buyingstore.item[i].nameid)->type;
		WFIFOW(fd,23+i*9) = ssd->buyingstore.item[i].nameid;
	}
	WFIFOW(fd,2) = 16+ssd->buyingstore.count*9;
#else
		WFIFOL(fd,16+i*11) = ssd->buyingstore.item[i].value;
		WFIFOW(fd,20+i*11) = ssd->buyingstore.item[i].amount;
		WFIFOB(fd,22+i*11) = itemdb_search(ssd->buyingstore.item[i].nameid)->type;
		WFIFOL(fd,23+i*11) = ssd->buyingstore.item[i].nameid;
	}
	WFIFOW(fd,2) = 16+ssd->buyingstore.count*11;
#endif
	WFIFOSET(fd,WFIFOW(fd,2));

	return;
}

/*==========================================
 * ����I�X�I��
 *------------------------------------------
 */
void clif_failed_trybuyingstore(struct map_session_data *sd, short result)
{
	int fd;

	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x81a;
	WFIFOW(fd,2) = result;
	WFIFOSET(fd,packet_db[0x81a].len);

	return;
}

/*==========================================
 * ����I�X�A�C�e���X�V
 *------------------------------------------
 */
void clif_update_buyingstore(struct map_session_data *sd, int nameid, short amount, int value, int account_id, int char_id)
{
	int fd;

	nullpo_retv(sd);

	fd = sd->fd;
#if PACKETVER < 20140129
	WFIFOW(fd,0) = 0x81b;
	WFIFOW(fd,2) = (short)nameid;
	WFIFOW(fd,4) = amount;
	WFIFOL(fd,6) = sd->buyingstore.limit_zeny;
	WFIFOSET(fd,packet_db[0x81b].len);
#elif PACKETVER < 20180704
	WFIFOW(fd, 0) = 0x9e6;
	WFIFOW(fd, 2) = (short)nameid;
	WFIFOW(fd, 4) = amount;
	WFIFOL(fd, 6) = value;
	WFIFOL(fd,10) = sd->buyingstore.limit_zeny;
	WFIFOL(fd,14) = char_id;
	WFIFOL(fd,18) = account_id;
	WFIFOSET(fd,packet_db[0x9e6].len);
#else
	WFIFOW(fd, 0) = 0x9e6;
	WFIFOL(fd, 2) = nameid;
	WFIFOW(fd, 6) = amount;
	WFIFOL(fd, 8) = value;
	WFIFOL(fd,12) = sd->buyingstore.limit_zeny;
	WFIFOL(fd,16) = char_id;
	WFIFOL(fd,20) = account_id;
	WFIFOSET(fd,packet_db[0x9e6].len);
#endif

	return;
}

/*==========================================
 * ����I�X�A�C�e���폜
 *------------------------------------------
 */
void clif_delete_buyingstore(struct map_session_data *sd, short idx, short amount, int value)
{
	int fd;

	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x81c;
	WFIFOW(fd,2) = idx + 2;
	WFIFOW(fd,4) = amount;
	WFIFOL(fd,6) = value;
	WFIFOSET(fd,packet_db[0x81c].len);

	return;
}

/*==========================================
 * ����I�X������莸�s
 *------------------------------------------
 */
void clif_failed_tradebuyingstore(struct map_session_data *sd, short result, int nameid)
{
	int fd;

	nullpo_retv(sd);

	fd = sd->fd;
#if PACKETVER < 20180704
	WFIFOW(fd,0) = 0x824;
	WFIFOW(fd,2) = result;
	WFIFOW(fd,4) = (short)nameid;
	WFIFOSET(fd,packet_db[0x824].len);
#else
	WFIFOW(fd,0) = 0x824;
	WFIFOW(fd,2) = result;
	WFIFOL(fd,4) = nameid;
	WFIFOSET(fd,packet_db[0x824].len);
#endif

	return;
}

/*==========================================
 * ����X�e�[�^�X���M
 *------------------------------------------
 */
void clif_send_elemstatus(struct map_session_data *sd)
{
	int fd;
	struct elem_data *eld;

	nullpo_retv(sd);
	nullpo_retv(eld = sd->eld);

	fd = sd->fd;
	WFIFOW(fd,0)  = 0x81d;
	WFIFOL(fd,2)  = eld->bl.id;
	WFIFOL(fd,6)  = eld->status.hp;
	WFIFOL(fd,10) = eld->max_hp;
	WFIFOL(fd,14) = eld->status.sp;
	WFIFOL(fd,18) = eld->max_sp;
	WFIFOSET(fd,packet_db[0x81d].len);

	return;
}

/*==========================================
 * ����X�e�[�^�X�X�V
 *------------------------------------------
 */
void clif_elemupdatestatus(struct map_session_data *sd, int type)
{
	int fd;
	struct elem_data *eld;

	nullpo_retv(sd);
	nullpo_retv(eld = sd->eld);

	fd = sd->fd;

	WFIFOW(fd,0)  = 0x81e;
	WFIFOW(fd,2)  = type;
	switch(type){
	case SP_HP:
		WFIFOL(fd,4) = eld->status.hp;
		break;
	case SP_MAXHP:
		WFIFOL(fd,4) = eld->max_hp;
		break;
	case SP_SP:
		WFIFOL(fd,4) = eld->status.sp;
		break;
	case SP_MAXSP:
		WFIFOL(fd,4) = eld->max_sp;
		break;
	}
	WFIFOSET(fd,packet_db[0x81e].len);

	return;
}

/*==========================================
 * �e�T�E�O�̋��̕\��(�G���A���M)
 *------------------------------------------
 */
void clif_elementball(struct map_session_data *sd)
{
	unsigned char buf[10];

	nullpo_retv(sd);

	WBUFW(buf,0)=0x8cf;
	WBUFL(buf,2)=sd->bl.id;
	WBUFW(buf,6)=sd->elementball.ele;
	WBUFW(buf,8)=sd->elementball.num;
	clif_send(buf,packet_db[0x8cf].len,&sd->bl,AREA);

	return;
}

/*==========================================
 * �A�C�e���l�^�u�ړ�
 *------------------------------------------
 */
void clif_privateitem(struct map_session_data *sd, short idx, char flag)
{
	int fd;

	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x908;
	WFIFOW(fd,2) = idx + 2;
	WFIFOB(fd,4) = flag;
	WFIFOSET(fd,packet_db[0x908].len);

	return;
}

/*==========================================
* �����X�^�[HP�o�[�X�V
*------------------------------------------
*/
void clif_monster_hpinfo(struct map_session_data *sd, struct mob_data *md)
{
#if PACKETVER >= 20141126
	int fd;

	nullpo_retv(sd);
	nullpo_retv(md);

	fd=sd->fd;
	WFIFOW(fd,0) = 0xa36;
	WFIFOL(fd,2) = md->bl.id;
	// �����Ԉُ펞�E�G���y���E���EMVP�����X�^�[�ɂ͕\�����Ȃ�
	if(mob_check_hpinfo(sd,md))
	{
		WFIFOB(fd, 6) = 0xff;
	} else {
		int hp = status_get_hp(&md->bl);
		int max_hp = status_get_max_hp(&md->bl);

		WFIFOB(fd, 6) = (unsigned char)(hp * 20 / max_hp);
	}
	WFIFOSET(fd,packet_db[0xa36].len);
#elif PACKETVER >= 20120404
	int fd;

	nullpo_retv(sd);
	nullpo_retv(md);

	fd=sd->fd;
	WFIFOW(fd,0) = 0x977;
	WFIFOL(fd,2) = md->bl.id;
	// �����Ԉُ펞�E�G���y���E���EMVP�����X�^�[�ɂ͕\�����Ȃ�
	if(mob_check_hpinfo(sd,md))
	{
		WFIFOL(fd, 6) = 0xffffffff;
		WFIFOL(fd,10) = 0xffffffff;
	} else {
		WFIFOL(fd, 6) = status_get_hp(&md->bl);
		WFIFOL(fd,10) = status_get_max_hp(&md->bl);
	}
	WFIFOSET(fd,packet_db[0x977].len);
#endif

	return;
}

/*==========================================
 * ��s�a������ʒm
 *------------------------------------------
 */
void clif_bank_deposit(struct map_session_data *sd, int flag)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd, 0)=0x9a8;
	WFIFOW(fd, 2)=flag;
	WFIFOQ(fd, 4)=sd->deposit;
	WFIFOL(fd,12)=sd->status.zeny;
	WFIFOSET(fd,packet_db[0x9a8].len);

	return;
}

/*==========================================
 * ��s�����o���ʒm
 *------------------------------------------
 */
void clif_bank_withdraw(struct map_session_data *sd, int flag)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd, 0)=0x9aa;
	WFIFOW(fd, 2)=flag;
	WFIFOQ(fd, 4)=sd->deposit;
	WFIFOL(fd,12)=sd->status.zeny;
	WFIFOSET(fd,packet_db[0x9aa].len);

	return;
}

/*==========================================
 * ����Ƀ��b�Z�[�W�\��
 *------------------------------------------
 */
void clif_showscript(struct block_list *bl, char *mes)
{
	unsigned char buf[256];
	size_t len;

	nullpo_retv(bl);

	if(mes == NULL)
		return;

	len = strlen(mes)+1;
	if(len > sizeof(buf) - 8)
		len = sizeof(buf) - 8;

	WBUFW(buf,0) = 0x8b3;
	WBUFW(buf,2) = (unsigned short)(len + 8);
	WBUFL(buf,4) = bl->id;
	memcpy(WBUFP(buf,8), mes, len);
	clif_send(WBUFP(buf,0), WBUFW(buf,2), bl, AREA);

	return;
}

/*==========================================
 * �T�[�o�[���ʒm
 *------------------------------------------
 */
void clif_send_personalinfo(struct map_session_data *sd)
{
#if PACKETVER >= 20130320
	int fd;
	int exp=0, penalty=0, drop=0;

	nullpo_retv(sd);

	// base exp rate
	if(map[sd->bl.m].flag.base_exp_rate)
		exp = map[sd->bl.m].flag.base_exp_rate;
	else
		exp = battle_config.base_exp_rate;
	if(exp >= 100)
		exp = exp - 100;
	else
		exp = 0 - (100 - exp);

	// death penalty rate
	if(battle_config.death_penalty_base >= 100)
		penalty = battle_config.death_penalty_base - 100;
	else
		penalty = 0 - (100 - battle_config.death_penalty_base);

	// item drop rate
	if(battle_config.item_rate >= 100)
		drop = battle_config.item_rate - 100;
	else
		drop = 0 - (100 - battle_config.item_rate);

	fd=sd->fd;
	WFIFOW(fd, 0)=0x97b;
	WFIFOW(fd, 2)=68;
	WFIFOL(fd, 4)=(100 + exp) * 1000;
	WFIFOL(fd, 8)=(100 + penalty) * 1000;
	WFIFOL(fd,12)=(100 + drop) * 1000;
	WFIFOB(fd,16)=0;
	WFIFOL(fd,17)=0;	// pccafe exp
	WFIFOL(fd,21)=0;	// pccafe penalty
	WFIFOL(fd,25)=0;	// pccafe drop
	WFIFOB(fd,29)=3;
	WFIFOL(fd,30)=exp * 1000;	// world exp
	WFIFOL(fd,34)=penalty * 1000;	// world penalty
	WFIFOL(fd,38)=drop * 1000;	// world drop
	WFIFOB(fd,42)=1;
	WFIFOL(fd,43)=0;	// premium exp
	WFIFOL(fd,47)=0;	// premium penalty
	WFIFOL(fd,51)=0;	// premium drop
	WFIFOB(fd,55)=2;
	WFIFOL(fd,56)=0;
	WFIFOL(fd,60)=0;
	WFIFOL(fd,64)=0;
	WFIFOSET(fd,WFIFOW(fd,2));
#endif

	return;
}

/*==========================================
 * �f�W�^���^�C�}�[�\��
 *------------------------------------------
 */
void clif_showdigit(struct map_session_data* sd, unsigned char type, int value)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0) = 0x1b1;
	WFIFOB(fd,2) = type;
	WFIFOL(fd,3) = value;
	WFIFOSET(fd,packet_db[0x1b1].len);

	return;
}

/*==========================================
 * �h���X���[���\��
 *------------------------------------------
 */
void clif_dressing_room(struct map_session_data *sd, int view)
{
#if PACKETVER >= 20150513
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xa02;
	WFIFOW(fd,2)=view;
	WFIFOSET(fd,packet_db[0xa02].len);
#endif
	return;
}

/*==========================================
 * clif_hat_effects�������M
 *------------------------------------------
 */
void clif_hat_effects(struct map_session_data* sd, struct block_list* bl, int target)
{
#if PACKETVER >= 20150513
	unsigned char* buf;
	int len,i;
	struct map_session_data *tsd;
	struct block_list* tbl;

	if(target == SELF) {
		tsd = BL_DOWNCAST(BL_PC,bl);
		tbl = &sd->bl;
	}
	else {
		tsd = sd;
		tbl = bl;
	}

	if( !tsd || !tsd->hatEffect.count )
		return;

	len = 9 + tsd->hatEffect.count * 2;

	buf = (unsigned char*)aMalloc( len );

	WBUFW(buf,0) = 0xa3b;
	WBUFW(buf,2) = len;
	WBUFL(buf,4) = tsd->bl.id;
	WBUFB(buf,8) = 1;

	for( i = 0; i < tsd->hatEffect.count; i++ ) {
		WBUFW(buf,9+i*2) = tsd->hatEffect.id[i];
	}

	clif_send(buf, len, tbl, target);

	aFree(buf);
#endif
}

/*==========================================
 * clif_hat_effect���M
 *------------------------------------------
 */
void clif_hat_effect_single(struct map_session_data* sd, int effectId, bool enable)
{
#if PACKETVER >= 20150513
	unsigned char buf[11];

	nullpo_retv(sd);

	WBUFW(buf,0) = 0xa3b;
	WBUFW(buf,2) = 11;
	WBUFL(buf,4) = sd->bl.id;
	WBUFB(buf,8) = enable;
	WBUFW(buf,9) = effectId;

	clif_send(buf,WBUFW(buf,2),&sd->bl,AREA);
#endif
	return;
}

/*==========================================
 * clif_weight_limit���M
 *------------------------------------------
 */
static void clif_weight_limit(struct map_session_data* sd)
{
#if PACKETVER >= 20171025
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd, 0) = 0xade;
	WFIFOL(fd, 2) = battle_config.natural_heal_weight_rate;
	WFIFOSET(fd,packet_db[0xade].len);
#endif
	return;
}

/*==========================================
 * ���x���I���̃N�����]���}�[�J�[���M
 *------------------------------------------
 */
void clif_crimson_marker(struct map_session_data *sd, struct block_list *bl, bool remove)
{
	unsigned char buf[11];

	nullpo_retv(sd);

	WBUFW(buf, 0) = 0x9c1;
	WBUFL(buf, 2) = bl->id;
	WBUFW(buf, 6) = (remove ? -1 : bl->x);
	WBUFW(buf, 8) = (remove ? -1 : bl->y);

	clif_send(buf,packet_db[0x9c1].len,&sd->bl,PARTY);
	return;
}

/*==========================================
 * �_�C�i�~�b�NNPC�����v������
 *------------------------------------------
 */
void clif_dynamicnpc_create_ack(struct map_session_data *sd, int type)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd, 0)=0xa17;
	WFIFOL(fd, 2)=type;
	WFIFOSET(fd,packet_db[0xa17].len);

	return;
}

/*==========================================
 * ping���M�^�C�}�[�i�S�N���C�A���g�j
 *------------------------------------------
 */
static int clif_pingtimer_sub(struct map_session_data *sd, va_list va)
{
#if PACKETVER >= 20190227
	int fd;

	nullpo_retr(0, sd);

	fd=sd->fd;
	WFIFOW(fd, 0) = 0x0b1d;
	WFIFOSET(fd,packet_db[0x0b1d].len);
#endif
	return 0;
}

static int clif_pingtimer(int tid, unsigned int tick, int id, void *data)
{
	clif_foreachclient(clif_pingtimer_sub);
	return 0;
}

/*==========================================
 * ���у��X�g���M
 *------------------------------------------
 */
void clif_send_achievement_list(struct map_session_data *sd)
{
#if PACKETVER >= 20141126
	int fd;

	nullpo_retv(sd);

	achieve_calc_level(sd, -1);

	fd=sd->fd;
	WFIFOW(fd, 0) = 0xa23;
	WFIFOW(fd, 2) = (50 * sd->achievelist) + 22;
	WFIFOL(fd, 4) = sd->achievelist;
	WFIFOL(fd, 8) = sd->as.score;
	WFIFOW(fd,12) = sd->as.level;
	WFIFOL(fd,14) = sd->as.current;
	WFIFOL(fd,18) = sd->as.next;

	if(sd->achievelist > 0) {
		int i, j;
		for(i = 0; i < sd->achievelist; i++) {
			WFIFOL(fd, i * 50 + 22) = sd->achieve[i].nameid;
			WFIFOB(fd, i * 50 + 26) = (sd->achieve[i].comp_date > 0? 1: 0);
			for(j = 0; j < MAX_ACHIEVE_CONTENT; j++) 
				WFIFOL(fd, (i * 50) + 27 + (j * 4)) = sd->achieve[i].count[j];
			WFIFOL(fd, i * 50 + 67) = sd->achieve[i].comp_date;
			WFIFOB(fd, i * 50 + 71) = sd->achieve[i].reward;
		}
	}
	WFIFOSET(fd, WFIFOW(fd, 2));
#endif
	return;
}

/*==========================================
 * ���у��X�g�X�V
 *------------------------------------------
 */
void clif_send_achievement_update(struct map_session_data *sd, struct achieve_data *ad)
{
#if PACKETVER >= 20141126
	int fd;

	nullpo_retv(sd);

	achieve_calc_level(sd, -1);

	fd = sd->fd;
	WFIFOW(fd, 0) = 0xa24;
	WFIFOL(fd, 2) = sd->as.score;
	WFIFOW(fd, 6) = sd->as.level;
	WFIFOL(fd, 8) = sd->as.current;
	WFIFOL(fd,12) = sd->as.next;
	if(ad) {
		int i;
		WFIFOL(fd, 16) = ad->nameid;
		WFIFOB(fd, 20) = (ad->comp_date > 0? 1: 0);
		for(i = 0; i < MAX_ACHIEVE_CONTENT; i++)
			WFIFOL(fd, 21 + (i * 4)) = ad->count[i];
		WFIFOL(fd, 61) = ad->comp_date;
		WFIFOB(fd, 65) = ad->reward;
	} else
		memset(WFIFOP(fd, 16), 0, 50);
	WFIFOSET(fd, packet_db[0xa24].len);
#endif
	return;
}

/*==========================================
 * ���у��X�g��V�l������
 *------------------------------------------
 */
static void clif_achievement_reward_ack(int fd, char result, int achieve_id)
{
#if PACKETVER >= 20141126
	WFIFOW(fd, 0) = 0xa26;
	WFIFOB(fd, 2) = result;
	WFIFOL(fd, 3) = achieve_id;
	WFIFOSET(fd, packet_db[0xa26].len);
#endif
	return;
}

/*==========================================
 * �̍��ύX����
 *------------------------------------------
 */
static void clif_change_title_ack(int fd, char result, int title_id)
{
#if PACKETVER >= 20150513
	WFIFOW(fd, 0) = 0xa2f;
	WFIFOB(fd, 2) = result;
	WFIFOL(fd, 3) = title_id;
	WFIFOSET(fd, packet_db[0xa2f].len);
#endif
}

/*==========================================
 * �A�C�e���v���r���[
 *------------------------------------------
 */
void clif_item_preview(struct map_session_data *sd, short idx)
{
#if PACKETVER >= 20170621
	int fd, j;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd, 0) = 0xab9;
	WFIFOW(fd, 2) = idx + 2;
	WFIFOW(fd, 4) = sd->status.inventory[idx].refine;
#if PACKETVER < 20180704
	if(itemdb_isspecial(sd->status.inventory[idx].card[0])) {
		if(sd->inventory_data[idx]->flag.pet_egg) {
			WFIFOW(fd,6) = 0;
			WFIFOW(fd,8) = 0;
			WFIFOW(fd,10) = 0;
		} else {
			WFIFOW(fd,6) = sd->status.inventory[idx].card[0];
			WFIFOW(fd,8) = sd->status.inventory[idx].card[1];
			WFIFOW(fd,10) = sd->status.inventory[idx].card[2];
		}
		WFIFOW(fd,12) = sd->status.inventory[idx].card[3];
	} else {
		if(sd->status.inventory[idx].card[0] > 0 && (j=itemdb_viewid(sd->status.inventory[idx].card[0])) > 0)
			WFIFOW(fd,6)= j;
		else
			WFIFOW(fd,6)= sd->status.inventory[idx].card[0];
		if(sd->status.inventory[idx].card[1] > 0 && (j=itemdb_viewid(sd->status.inventory[idx].card[1])) > 0)
			WFIFOW(fd,8)= j;
		else
			WFIFOW(fd,8)= sd->status.inventory[idx].card[1];
		if(sd->status.inventory[idx].card[2] > 0 && (j=itemdb_viewid(sd->status.inventory[idx].card[2])) > 0)
			WFIFOW(fd,10)= j;
		else
			WFIFOW(fd,10)= sd->status.inventory[idx].card[2];
		if(sd->status.inventory[idx].card[3] > 0 && (j=itemdb_viewid(sd->status.inventory[idx].card[3])) > 0)
			WFIFOW(fd,12)= j;
		else
			WFIFOW(fd,12)= sd->status.inventory[idx].card[3];
	}
	WFIFOW(fd,14)=sd->status.inventory[idx].opt[0].id;
	WFIFOW(fd,16)=sd->status.inventory[idx].opt[0].val;
	WFIFOB(fd,18)=0;
	WFIFOW(fd,19)=sd->status.inventory[idx].opt[1].id;
	WFIFOW(fd,21)=sd->status.inventory[idx].opt[1].val;
	WFIFOB(fd,23)=0;
	WFIFOW(fd,24)=sd->status.inventory[idx].opt[2].id;
	WFIFOW(fd,26)=sd->status.inventory[idx].opt[2].val;
	WFIFOB(fd,28)=0;
	WFIFOW(fd,29)=sd->status.inventory[idx].opt[3].id;
	WFIFOW(fd,31)=sd->status.inventory[idx].opt[3].val;
	WFIFOB(fd,33)=0;
	WFIFOW(fd,34)=sd->status.inventory[idx].opt[4].id;
	WFIFOW(fd,36)=sd->status.inventory[idx].opt[4].val;
	WFIFOB(fd,38)=0;
#else
	if(itemdb_isspecial(sd->status.inventory[idx].card[0])) {
		if(sd->inventory_data[idx]->flag.pet_egg) {
			WFIFOL(fd,6) = 0;
			WFIFOL(fd,10) = 0;
			WFIFOL(fd,14) = 0;
		} else {
			WFIFOL(fd,6) = sd->status.inventory[idx].card[0];
			WFIFOL(fd,10) = sd->status.inventory[idx].card[1];
			WFIFOL(fd,14) = sd->status.inventory[idx].card[2];
		}
		WFIFOL(fd,18) = sd->status.inventory[idx].card[3];
	} else {
		if(sd->status.inventory[idx].card[0] > 0 && (j=itemdb_viewid(sd->status.inventory[idx].card[0])) > 0)
			WFIFOL(fd,6)= j;
		else
			WFIFOL(fd,6)= sd->status.inventory[idx].card[0];
		if(sd->status.inventory[idx].card[1] > 0 && (j=itemdb_viewid(sd->status.inventory[idx].card[1])) > 0)
			WFIFOL(fd,10)= j;
		else
			WFIFOL(fd,10)= sd->status.inventory[idx].card[1];
		if(sd->status.inventory[idx].card[2] > 0 && (j=itemdb_viewid(sd->status.inventory[idx].card[2])) > 0)
			WFIFOL(fd,14)= j;
		else
			WFIFOL(fd,14)= sd->status.inventory[idx].card[2];
		if(sd->status.inventory[idx].card[3] > 0 && (j=itemdb_viewid(sd->status.inventory[idx].card[3])) > 0)
			WFIFOL(fd,18)= j;
		else
			WFIFOL(fd,18)= sd->status.inventory[idx].card[3];
	}
	WFIFOW(fd,22)=sd->status.inventory[idx].opt[0].id;
	WFIFOW(fd,24)=sd->status.inventory[idx].opt[0].val;
	WFIFOB(fd,26)=0;
	WFIFOW(fd,27)=sd->status.inventory[idx].opt[1].id;
	WFIFOW(fd,29)=sd->status.inventory[idx].opt[1].val;
	WFIFOB(fd,31)=0;
	WFIFOW(fd,32)=sd->status.inventory[idx].opt[2].id;
	WFIFOW(fd,34)=sd->status.inventory[idx].opt[2].val;
	WFIFOB(fd,36)=0;
	WFIFOW(fd,37)=sd->status.inventory[idx].opt[3].id;
	WFIFOW(fd,39)=sd->status.inventory[idx].opt[3].val;
	WFIFOB(fd,41)=0;
	WFIFOW(fd,42)=sd->status.inventory[idx].opt[4].id;
	WFIFOW(fd,44)=sd->status.inventory[idx].opt[4].val;
	WFIFOB(fd,46)=0;
#endif
	WFIFOSET(fd, packet_db[0xab9].len);
#endif

	return;
}

/*==========================================
 * �����A�b�v�O���[�h�E�B���h�E���J��
 *------------------------------------------
 */
void clif_openlapineupgrade(struct map_session_data *sd, int nameid)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;

#if PACKETVER < 20180704
	WFIFOW(fd,0) = 0xab4;
	WFIFOW(fd,2) = nameid;
#else
	WFIFOW(fd,0) = 0xab4;
	WFIFOL(fd,2) = nameid;
#endif
	WFIFOSET(fd,packet_db[0xab4].len);

	return;
}

/*==========================================
 *�@�����A�b�v�O���[�h����
 *------------------------------------------
 */
void clif_lapineupgradeack(struct map_session_data *sd, int result)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0) = 0xab7;
	WFIFOW(fd,2) = result;
	WFIFOSET(fd,packet_db[0xab7].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_unequipitemallack(struct map_session_data *sd, unsigned char ok)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xbae;
	WFIFOB(fd,8)=ok;
	WFIFOSET(fd,packet_db[0xbae].len);

	return;
}

/*==========================================
 * �\�E���G�i�W�[�\��
 *------------------------------------------
 */
void clif_soulenergy(struct map_session_data *sd)
{
	unsigned char buf[10];

	nullpo_retv(sd);

	WBUFW(buf,0)=0xb73;
	WBUFL(buf,2)=sd->bl.id;
	WBUFW(buf,6)=sd->soulenergy.num;
	clif_send(buf,packet_db[0xb73].len,&sd->bl,AREA);

	return;
}

/*==========================================
 * ���̕\��
 *------------------------------------------
 */
void clif_ball(struct map_session_data *sd)
{
	unsigned char buf[8];

	nullpo_retv(sd);

	WBUFW(buf,0)=0x1d0;
	WBUFL(buf,2)=sd->bl.id;
	WBUFW(buf,6)=sd->ball.num;
	clif_send(buf,packet_db[0x1d0].len,&sd->bl,AREA);

	return;
}

/*==========================================
 * send packet �f�o�b�O�p
 *------------------------------------------
 */
void clif_send_packet(struct map_session_data *sd, const char *message)
{
	int fd,n,i;
	int packet,len,db_len;
	int p[256];

	nullpo_retv(sd);

	// �C�ӂ̓ǂݍ��݂�30byte�܂ŋ�����
	n = sscanf(message, "%x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x",
				&packet,&p[2],&p[3],&p[4],&p[5],&p[6],&p[7],&p[8],&p[9],
				&p[10],&p[11],&p[12],&p[13],&p[14],&p[15],&p[16],&p[17],&p[18],&p[19],
				&p[20],&p[21],&p[22],&p[23],&p[24],&p[25],&p[26],&p[27],&p[28],&p[29]);
	if(n == 0)
		return;
	if(packet < 0 || packet >= MAX_PACKET_DB)
		return;
	db_len = packet_db[packet].len;
	if(db_len > 255){
		printf("clif_send_packet_test too long packet!!\n");
		return;
	}

	fd = sd->fd;
	WFIFOW(fd,0) = packet;
	p[0] = packet&0xff;
	p[1] = (packet>>8)&0xff;

	if(db_len >= 0) {
		len = db_len;
		i = 2;
	} else {	// �ϒ�
		if(n == 1 || p[2] <= 0){
			printf("clif_send_packet_test packet:%x len=-1 input len %cpacket len x1 x2...\n", packet, GM_Symbol());
			return;
		}
		WFIFOW(fd,2) = (len=p[2]);
		i = 4;		// p[2]��short�^�Ƃ��Ď�邽��p[3]�͖�������
	}

	for(; i < len; i++) {
		if(i < n+1)
			WFIFOB(fd,i)= p[i];
		else
			WFIFOB(fd,i)= (p[i]=atn_rand()%256);
	}
	printf("clif_send_packet: test packet = 0x%x, len = %d\n", packet, db_len);
	hex_dump(stdout, WFIFOP(fd,0), len);
	printf("\n");

	WFIFOSET(fd,len);

	return;
}

// ------------
// clif_parse_*
// ------------
// �p�P�b�g�ǂݎ���ĐF�X����
/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_WantToConnection(int fd,struct map_session_data *sd, int cmd)
{
	struct map_session_data *old_sd;
	int account_id,char_id,login_id1,sex;
	unsigned int client_tick;

	if(sd) {
		if(battle_config.error_log)
			printf("clif_parse_WantToConnection : invalid request?\n");
		return;
	}

	account_id  = RFIFOL(fd,GETPACKETPOS(cmd,0));
	char_id     = RFIFOL(fd,GETPACKETPOS(cmd,1));
	login_id1   = RFIFOL(fd,GETPACKETPOS(cmd,2));
	client_tick = RFIFOL(fd,GETPACKETPOS(cmd,3));
	sex         = RFIFOB(fd,GETPACKETPOS(cmd,4));

	// �A�J�E���gID�̕s���`�F�b�N
	if(account_id < START_ACCOUNT_NUM || account_id > END_ACCOUNT_NUM) {
		printf("clif_parse_WantToConnection : invalid Account ID !!\n");
		return;
	}
	// Sex�̃`�F�b�N
	if(sex != SEX_FEMALE && sex != SEX_MALE) {
		printf("clif_parse_WantToConnection : invalid Sex !!\n");
		return;
	}

	session[fd]->session_data = aCalloc(1,sizeof(struct map_session_data));
	sd = (struct map_session_data *)session[fd]->session_data;
	sd->fd = fd;
	sd->cryptKey = (( ((( cryptKey[0] * cryptKey[1] ) + cryptKey[2]) & 0xFFFFFFFF)
						* cryptKey[1] ) + cryptKey[2]) & 0xFFFFFFFF;

	pc_setnewpc(sd, account_id, char_id, login_id1, client_tick, sex);
	if((old_sd = map_id2sd(account_id)) != NULL) {
		// 2�dlogin�Ȃ̂Őؒf�p�̃f�[�^��ۑ�����
		old_sd->new_fd=fd;
		sd->new_fd = -1; // �V�����f�[�^�̓Z�[�u���Ȃ��t���O
	} else {
		map_addiddb(&sd->bl);
	}

#if PACKETVER < 20070521
	WFIFOL(fd,0) = sd->bl.id; // account_id
	WFIFOSET(fd,4);
#else
	WFIFOW(fd,0) = 0x283;
	WFIFOL(fd,2) = sd->bl.id;
	WFIFOSET(fd,packet_db[0x283].len);
#endif

	if(chrif_authreq(sd))
		session[fd]->eof = 1;

	return;
}

/*==========================================
 * 007d �N���C�A���g���}�b�v�ǂݍ��݊���
 * map�N�����ɕK�v�ȃf�[�^��S�đ������
 *------------------------------------------
 */
static void clif_parse_LoadEndAck(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	if(sd->bl.prev != NULL)
		return;

	if(!sd->state.auth) {	// �F�؊������ĂȂ�
		clif_authfail_fd(fd,0);
		return;
	}

	if(sd->npc_id) {
		npc_event_dequeue(sd);
	}

	// item
	pc_checkitem(sd);
	clif_inventoryStart(sd, 0, "");
	clif_itemlist(sd);
	clif_equiplist(sd);
	clif_inventoryEnd(sd, 0);
	// cart
	if(pc_iscarton(sd)){
		clif_inventoryStart(sd, 1, "");
		clif_cart_itemlist(sd);
		clif_cart_equiplist(sd);
		clif_inventoryEnd(sd, 1);
		clif_updatestatus(sd,SP_CARTINFO);
	}
	// weight max , now
	clif_weight_limit(sd);
	clif_updatestatus(sd,SP_MAXWEIGHT);
	clif_updatestatus(sd,SP_WEIGHT);

	if(battle_config.pc_invincible_time > 0) {
		if(map[sd->bl.m].flag.gvg)
			pc_setinvincibletimer(sd,battle_config.pc_invincible_time<<1);
		else
			pc_setinvincibletimer(sd,battle_config.pc_invincible_time);
	}

	map_addblock(&sd->bl);	// �u���b�N�o�^
	if(!battle_config.gm_perfect_hide || !pc_isinvisible(sd)) {
		clif_spawnpc(sd);	// spawn
	}
	mob_ai_hard_spawn(&sd->bl);

	// party
	party_send_movemap(sd);
	// guild
	guild_send_memberinfoshort(sd,1);
	// friend
	friend_send_info(sd);
	friend_send_online(sd, 0);

	// mapinfo
	clif_mapproperty(sd);

	// pvp
	if(sd->pvp_timer != -1)
		delete_timer(sd->pvp_timer,pc_calc_pvprank_timer);

	if(map[sd->bl.m].flag.pk) {
		sd->pvp_timer = -1;
		clif_set0199(sd->fd,4);
		if(battle_config.pk_noshift)
			sd->status.karma = 1;
	} else if(map[sd->bl.m].flag.pvp) {
		sd->pvp_timer     = add_timer(gettick()+200,pc_calc_pvprank_timer,sd->bl.id,NULL);
		sd->pvp_rank      = 0;
		sd->pvp_lastusers = 0;
		sd->pvp_point     = 5;
		clif_set0199(sd->fd,1);
	} else {
		sd->pvp_timer = -1;
	}

	if(map[sd->bl.m].flag.gvg)
		clif_set0199(sd->fd,3);

	if(battle_config.pk_noshift && !map[sd->bl.m].flag.pk)
		sd->status.karma = 0;

	// �y�b�g
	if(sd->status.pet_id > 0 && sd->pd && sd->pet.intimate > 0) {
		map_addblock(&sd->pd->bl);
		clif_spawnpet(sd->pd);
		clif_send_petdata(sd,0,0);
		clif_send_pethair(sd);
		clif_send_petstatus(sd);
	}
	// �z��
	if(sd->hd) {
		map_addblock(&sd->hd->bl);
		mob_ai_hard_spawn(&sd->hd->bl);
		clif_spawnhom(sd->hd);
		clif_send_homdata(sd,0,0);
		clif_send_homstatus(sd,1);
		clif_send_homstatus(sd,0);
	}
	// �b��
	if(sd->mcd) {
		map_addblock(&sd->mcd->bl);
		mob_ai_hard_spawn(&sd->mcd->bl);
		clif_spawnmerc(sd->mcd);
		clif_send_mercstatus(sd);
		clif_mercskillinfoblock(sd);
	}
	// ����
	if(sd->eld) {
		map_addblock(&sd->eld->bl);
		mob_ai_hard_spawn(&sd->eld->bl);
		clif_spawnelem(sd->eld);
		clif_send_elemstatus(sd);
	}

	if(sd->state.connect_new) {
		// �X�e�[�^�X�ُ�f�[�^�v��
		// pc_authok() �ŌĂяo���ƃN���C�A���g�ɃG�t�F�N�g�����f����Ȃ�
		intif_request_scdata(sd->status.account_id,sd->status.char_id);

#if PACKETVER < 20190101
		clif_skillinfoblock(sd);
#endif
		clif_send_hotkeyAll(sd);
		clif_send_partyconfig(sd);
		clif_send_config(sd);
		clif_updatestatus(sd,SP_NEXTBASEEXP);
		clif_updatestatus(sd,SP_NEXTJOBEXP);
		clif_updatestatus(sd,SP_SKILLPOINT);
		clif_initialstatus(sd);
#if PACKETVER >= 20200916
		clif_updatestatus(sd,SP_PATK);
		clif_updatestatus(sd,SP_SMATK);
		clif_updatestatus(sd,SP_RES);
		clif_updatestatus(sd,SP_MRES);
		clif_updatestatus(sd,SP_HPLUS);
		clif_updatestatus(sd,SP_CRATE);
		clif_updatestatus(sd,SP_TSTATUSPOINT);
		clif_updatestatus(sd,SP_AP);
		clif_updatestatus(sd,SP_MAXAP);
		clif_updatestatus(sd,SP_UPOW);
		clif_updatestatus(sd,SP_USTA);
		clif_updatestatus(sd,SP_UWIS);
		clif_updatestatus(sd,SP_USPL);
		clif_updatestatus(sd,SP_UCON);
		clif_updatestatus(sd,SP_UCRT);
#endif
		clif_send_personalinfo(sd);

		// �L���[��񑗐M
		if(battle_config.save_pckiller_type)
			clif_update_temper(sd);

		if(sd->status.class_ != sd->view_class)
			clif_changelook(&sd->bl,LOOK_BASE,sd->view_class);
		if(sd->status.pet_id > 0 && sd->pd && sd->pet.intimate > 900)
			clif_pet_emotion(sd->pd,(sd->pd->class_ - 100)*100 + 50 + pet_hungry_val(sd));
	}

	// param
	clif_updatestatus(sd,SP_STR);
	clif_updatestatus(sd,SP_AGI);
	clif_updatestatus(sd,SP_VIT);
	clif_updatestatus(sd,SP_INT);
	clif_updatestatus(sd,SP_DEX);
	clif_updatestatus(sd,SP_LUK);
#if PACKETVER >= 20200916
	clif_updatestatus(sd,SP_POW);
	clif_updatestatus(sd,SP_STA);
	clif_updatestatus(sd,SP_WIS);
	clif_updatestatus(sd,SP_SPL);
	clif_updatestatus(sd,SP_CON);
	clif_updatestatus(sd,SP_CRT);
#endif

	// view equipment item
#if PACKETVER < 4
	clif_changelook(&sd->bl,LOOK_WEAPON,sd->status.weapon);
	clif_changelook(&sd->bl,LOOK_SHIELD,sd->status.shield);
#else
	clif_changelook(&sd->bl,LOOK_WEAPON,0);
#endif
	pc_costumelook(sd);

	// option�n������(�N���C�A���g�ɑ΂���...)
	// ����p�P��2�񑗂邱�Ƃł��\���ł����A�C���������̂�0�ŏ������Ƃ����`��
	clif_changeoption(&sd->bl);
	clif_changeoption(&sd->bl);

#if PACKETVER >= 20190101
	clif_skillinfoblock(sd);
#endif

	// �b��ԃG���h�~����
	if(sd->status.manner < 0) {
		if(battle_config.nomanner_mode)
			sd->status.manner = 0;
		else
			status_change_start(&sd->bl,SC_NOCHAT,0,0,0,0,0,0);
	}

	map_foreachinarea(clif_getareachar,sd->bl.m,sd->bl.x-AREA_SIZE,sd->bl.y-AREA_SIZE,sd->bl.x+AREA_SIZE,sd->bl.y+AREA_SIZE,BL_ALL,sd);

	if(sd->state.connect_new) {
		sd->state.connect_new = 0;

		if(pc_isriding(sd) || pc_isdragon(sd))
			clif_status_load_id(sd,SI_RIDING,1);
		if(pc_isfalcon(sd))
			clif_status_load_id(sd,SI_FALCON,1);

		// OnPCLogin�C�x���g
		if(battle_config.pc_login_script)
			npc_event_doall_id("OnPCLogin",sd->bl.id,sd->bl.m);
	}

	// OnPCMapIn�C�x���g
	if (battle_config.pc_mapin_script)
		npc_event_doall_id("OnPCMapIn",sd->bl.id,sd->bl.m);

	if(map_getcell(sd->bl.m,sd->bl.x,sd->bl.y,CELL_CHKNPC))
		npc_touch_areanpc(sd,sd->bl.m,sd->bl.x,sd->bl.y);
	else
		memset(sd->areanpc_id,0,sizeof(sd->areanpc_id));

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_TickSend(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	sd->client_tick = RFIFOL(fd,GETPACKETPOS(cmd,0));
	clif_servertick(sd);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_WalkToXY(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	if(unit_isdead(&sd->bl)) {
		clif_clearchar_area(&sd->bl,1);
		return;
	}

	if( sd->npc_id != 0 || sd->state.store || sd->state.deal_mode != 0 || sd->chatID != 0 )
		return;
	if( sd->state.storage_flag )
		return;
	if( sd->state.blockedmove )
		return;
	if( pc_issit(sd) )
		return;

	if( !unit_isrunning(&sd->bl) ) {
		int x = RFIFOB(fd,GETPACKETPOS(cmd,0))*4+(RFIFOB(fd,GETPACKETPOS(cmd,0)+1)>>6);
		int y = ((RFIFOB(fd,GETPACKETPOS(cmd,0)+1)&0x3f)<<4)+(RFIFOB(fd,GETPACKETPOS(cmd,0)+2)>>4);

		if( unit_walktoxy(&sd->bl,x,y) ) {
			unit_stopattack(&sd->bl);
			if(sd->invincible_timer != -1)
				pc_delinvincibletimer(sd,1);
		}
	}
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_QuitGame(int fd,struct map_session_data *sd, int cmd)
{
	int fail = 0;

	nullpo_retv(sd);

	if(!pc_isquitable(sd))
		fail = 1;

	clif_disconnect_ack(fd, fail);
	clif_setwaitclose(fd);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_GetCharNameRequest(int fd,struct map_session_data *sd, int cmd)
{
	struct block_list *bl;
	int account_id;

	account_id = RFIFOL(fd,GETPACKETPOS(cmd,0));
	bl=map_id2bl(account_id);
	if(bl==NULL)
		return;
	if((sd->bl.m != bl->m || unit_distance(&sd->bl,bl) > AREA_SIZE) && bl->id != sd->npc_dynamic_id)
		return;

	memset(WFIFOP(fd,0), 0, packet_db[0xa30].len);
	WFIFOW(fd,0) = 0x95;
	WFIFOL(fd,2) = account_id;

	switch(bl->type){
	case BL_PC:
		{
			struct map_session_data *ssd = (struct map_session_data *)bl;
			struct party *p = NULL;
			struct guild *g = NULL;

			memcpy(WFIFOP(fd,6), ssd->status.name, 24);
			if (ssd->status.party_id > 0)
				p = party_search(ssd->status.party_id);
			if (ssd->status.guild_id > 0)
				g = guild_search(ssd->status.guild_id);

#if PACKETVER < 20141126
			if ((battle_config.show_always_party_name && p != NULL) || g != NULL) {
				// �M���h�����Ȃ�p�P�b�g0195��Ԃ�
				WFIFOW(fd, 0) = 0x195;
				if (p)
					memcpy(WFIFOP(fd,30), p->name, 24);
				if (g) {
					int i, ps = -1;
					memcpy(WFIFOP(fd,54), g->name, 24);
					for(i = 0; i < g->max_member; i++) {
						if (g->member[i].char_id == ssd->status.char_id) { // char_id is unique, not need to check account_id
							ps = g->member[i].position;
							break;
						}
					}
					if (ps >= 0 && ps < MAX_GUILDPOSITION)
						memcpy(WFIFOP(fd,78), g->position[ps].name, 24);
					else
						strncpy(WFIFOP(fd,78), msg_txt(45), 24); // No Position
				}
				WFIFOSET(fd,packet_db[0x195].len);
			} else {
				WFIFOSET(fd,packet_db[0x95].len);
			}
#else
			WFIFOW(fd, 0) = 0xa30;
			if (p && (battle_config.show_always_party_name || g != NULL))
				memcpy(WFIFOP(fd,30), p->name, 24);
			if (g) {
				int i, ps = -1;
				memcpy(WFIFOP(fd,54), g->name, 24);
				for(i = 0; i < g->max_member; i++) {
					if (g->member[i].char_id == ssd->status.char_id) { // char_id is unique, not need to check account_id
						ps = g->member[i].position;
						break;
					}
				}
				if (ps >= 0 && ps < MAX_GUILDPOSITION)
					memcpy(WFIFOP(fd,78), g->position[ps].name, 24);
				else
					strncpy(WFIFOP(fd,78), msg_txt(45), 24); // No Position
			}
			WFIFOL(fd,102) = ssd->status.title_id;
			WFIFOSET(fd,packet_db[0xa30].len);
#endif
			// �}�[�_���[
			if(battle_config.pk_murderer_point > 0) {
				if(ranking_get_point(ssd,RK_PK) >= battle_config.pk_murderer_point)
					clif_send_murderer(sd,ssd->bl.id,1);
			}
		}
		break;
	case BL_NPC:
		{
			struct npc_data *snd=(struct npc_data*)bl;
#if PACKETVER < 20171129
			memcpy(WFIFOP(fd,6),snd->name,24);
			if(snd->position[0]) {
				// �M���h�����Ȃ�p�P�b�g0195��Ԃ�
#if PACKETVER < 20141126
				WFIFOW(fd, 0)=0x195;
				strncpy(WFIFOP(fd,30),"NPC",24);	// PT��
				strncpy(WFIFOP(fd,54),"NPC",24);	// Guild��
				memcpy(WFIFOP(fd,78),snd->position,24);
				WFIFOSET(fd,packet_db[0x195].len);
#else
				WFIFOW(fd, 0)=0xa30;
				strncpy(WFIFOP(fd,30),"NPC",24);	// PT��
				strncpy(WFIFOP(fd,54),"NPC",24);	// Guild��
				memcpy(WFIFOP(fd,78),snd->position,24);
				WFIFOL(fd,102) = 0;	// TODO: title_id
				WFIFOSET(fd,packet_db[0xa30].len);
#endif
				break;
			}
			WFIFOSET(fd,packet_db[0x95].len);
#else
			WFIFOW(fd, 0) = 0xadf;
			WFIFOL(fd, 6) = snd->group_id;
			memcpy(WFIFOP(fd,10),snd->name,24);
			strncpy(WFIFOP(fd,34),snd->title,24);	// Title_name
			WFIFOSET(fd,packet_db[0xadf].len);
#endif
		}
		break;
	case BL_PET:
#if PACKETVER < 20171129
		memcpy(WFIFOP(fd,6),((struct pet_data*)bl)->name,24);
		WFIFOSET(fd,packet_db[0x95].len);
#else
		WFIFOW(fd, 0) = 0xadf;
		WFIFOL(fd, 6) = 0;
		memcpy(WFIFOP(fd,10),((struct pet_data*)bl)->name,24);
		strncpy(WFIFOP(fd,34),"",24);	// Title_name
		WFIFOSET(fd,packet_db[0xadf].len);
#endif
		break;
	case BL_MOB:
#if PACKETVER < 20171129
		memcpy(WFIFOP(fd,6),((struct mob_data*)bl)->name,24);
		WFIFOSET(fd,packet_db[0x95].len);
#else
		WFIFOW(fd, 0) = 0xadf;
		WFIFOL(fd, 6) = ((struct mob_data*)bl)->group_id;
		memcpy(WFIFOP(fd,10),((struct mob_data*)bl)->name,24);
		strncpy(WFIFOP(fd,34),((struct mob_data*)bl)->title,24);	// Title_name
		WFIFOSET(fd,packet_db[0xadf].len);
#endif
		break;
	case BL_HOM:
#if PACKETVER < 20171129
		memcpy(WFIFOP(fd,6),((struct homun_data*)bl)->status.name,24);
		WFIFOSET(fd,packet_db[0x95].len);
#else
		WFIFOW(fd, 0) = 0xadf;
		WFIFOL(fd, 6) = 0;
		memcpy(WFIFOP(fd,10),((struct homun_data*)bl)->status.name,24);
		strncpy(WFIFOP(fd,34),"",24);	// Title_name
		WFIFOSET(fd,packet_db[0xadf].len);
#endif
		break;
	case BL_MERC:
#if PACKETVER < 20171129
		memcpy(WFIFOP(fd,6),((struct merc_data*)bl)->name,24);
		WFIFOSET(fd,packet_db[0x95].len);
#else
		WFIFOW(fd, 0) = 0xadf;
		WFIFOL(fd, 6) = 0;
		memcpy(WFIFOP(fd,10),((struct merc_data*)bl)->name,24);
		strncpy(WFIFOP(fd,34),"",24);	// Title_name
		WFIFOSET(fd,packet_db[0xadf].len);
#endif
		break;
	case BL_ELEM:
#if PACKETVER < 20171129
		memcpy(WFIFOP(fd,6),((struct elem_data*)bl)->name,24);
		WFIFOSET(fd,packet_db[0x95].len);
#else
		WFIFOW(fd, 0) = 0xadf;
		WFIFOL(fd, 6) = 0;
		memcpy(WFIFOP(fd,10),((struct elem_data*)bl)->name,24);
		strncpy(WFIFOP(fd,34),"",24);	// Title_name
		WFIFOSET(fd,packet_db[0xadf].len);
#endif
		break;
	case BL_SKILL:
		break;
	default:
		if(battle_config.error_log)
			printf("clif_parse_GetCharNameRequest : bad type %d(%d)\n",bl->type,account_id);
		break;
	}

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_GlobalMessage(int fd,struct map_session_data *sd, int cmd)
{
	char *message;
	int len, message_size;

	nullpo_retv(sd);

	len = RFIFOW(fd, GETPACKETPOS(cmd,0));
	message = (char *)RFIFOP(fd, GETPACKETPOS(cmd,1));
	message_size = len - GETPACKETPOS(cmd,1); // including NULL

	if (message_size < 8)	// name (mini:4) + " : " (3) + NULL (1) (void mesages are possible for skills)
		return;
	if (message_size > 255)	// too long
		return;

#if PACKETVER >= 20151029
	message[message_size] = 0; // be sure to have a NULL (hacker can send a no-NULL terminated string)
#else
	message[message_size - 1] = 0; // be sure to have a NULL (hacker can send a no-NULL terminated string)
#endif

	if (battle_config.check_player_name_global_msg) {
		// structure of message: <player_name> : <message>
		int name_length;
		char *p_message;
		name_length = (int)strlen(sd->status.name);
		if (name_length > 24)
			name_length = 24;
		p_message = message + name_length;
		if (message_size < name_length + 3 + 1 || // check void message (at least 1 char) -> normal client refuse to send void message (but some skills can)
		    memcmp(message, sd->status.name, name_length) != 0 || // check player name
		    *p_message != ' ' || *(p_message + 1) != ':' || *(p_message + 2) != ' ') { // check ' : '
			// add here a message if necessary
			return;
		}
	}

	if (is_atcommand(fd, sd, message) != AtCommand_None)
		return;

	// �o�[�T�[�N�A�`���b�g�֎~��ԂȂ��b�s��
	if (sd->sc.data[SC_BERSERK].timer != -1 || sd->sc.data[SC_NOCHAT].timer != -1 || sd->sc.data[SC_DEEP_SLEEP].timer != -1)
		return;

	clif_disp_overhead(sd, message);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_MapMove(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	if (battle_config.atc_gmonly == 0 || pc_isGM(sd) >= get_atcommand_level(AtCommand_MapMove)) {
		char mapname[17];

		mapname[16] = 0;
		memcpy(mapname, RFIFOP(fd,GETPACKETPOS(cmd,0)), 16);
		if (mapname[0] != '\0') {
			int x = RFIFOW(fd, GETPACKETPOS(cmd,1));
			int y = RFIFOW(fd, GETPACKETPOS(cmd,2));
			pc_setpos(sd, mapname, x, y, 2);
		}
	}

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_ChangeDir(int fd,struct map_session_data *sd, int cmd)
{
	int headdir,dir;

	nullpo_retv(sd);

	headdir = RFIFOW(fd,GETPACKETPOS(cmd,0)) & 0x07;
	dir     = RFIFOB(fd,GETPACKETPOS(cmd,1)) & 0x07;
	pc_setdir(sd,dir,headdir);

	clif_changedir(&sd->bl, headdir, dir);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_Emotion(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	if(battle_config.basic_skill_check == 0 || pc_checkskill(sd,NV_BASIC) >= 2 || pc_checkskill(sd,SU_BASIC_SKILL)) {
		unsigned int tick = gettick();

		// anti hacker
		if(DIFF_TICK(tick, sd->anti_hacker.emotion_delay_tick) > 0) {
			sd->anti_hacker.emotion_delay_tick = tick + 1000;

			WFIFOW(fd,0)=0xc0;
			WFIFOL(fd,2)=sd->bl.id;
			WFIFOB(fd,6)=RFIFOB(fd,GETPACKETPOS(cmd,0));
			clif_send(WFIFOP(fd,0),packet_db[0xc0].len,&sd->bl,AREA);
		}
	} else {
		clif_skill_fail(sd,NV_BASIC,SKILLFAIL_LEVEL,1,0);
	}

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_HowManyConnections(int fd,struct map_session_data *sd, int cmd)
{
	WFIFOW(fd,0)=0xc2;
	WFIFOL(fd,2)=map_getusers();
	WFIFOSET(fd,packet_db[0xc2].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_ActionRequest(int fd,struct map_session_data *sd, int cmd)
{
	unsigned int tick;
	int action_type,target_id;

	nullpo_retv(sd);

	if(unit_isdead(&sd->bl)) {
		clif_clearchar_area(&sd->bl,1);
		return;
	}
	if(sd->npc_id != 0 || (sd->sc.opt1 > OPT1_NORMAL && sd->sc.opt1 != OPT1_BURNNING) || sd->sc.option&OPTION_HIDE || sd->state.storage_flag || sd->state.deal_mode != 0 || sd->chatID || sd->state.mail_appending)
		return;
	if(sd->sc.data[SC_AUTOCOUNTER].timer != -1 ||	// �I�[�g�J�E���^�[
	   sd->sc.data[SC_DEATHBOUND].timer != -1 ||	// �f�X�o�E���h
	   sd->sc.data[SC_BLADESTOP].timer != -1 ||	// ���n���
	   sd->sc.data[SC_RUN].timer != -1 ||		// �^�C���M
	   sd->sc.data[SC_FORCEWALKING].timer != -1 ||	// �����ړ���
	   (sd->sc.data[SC_DANCING].timer != -1 && sd->sc.data[SC_LONGINGFREEDOM].timer == -1) ||	// �_���X��
	   sd->sc.data[SC__MANHOLE].timer != -1 ||		// �}���z�[��
	   sd->sc.data[SC_CURSEDCIRCLE_USER].timer != -1 ||	// �����w(�g�p��)
	   sd->sc.data[SC_CURSEDCIRCLE].timer != -1 ||		// �����w
	   sd->sc.data[SC_SUHIDE].timer != -1 )	// �������
		return;

	tick=gettick();

	unit_stop_walking(&sd->bl,0);
	unit_stopattack(&sd->bl);

	target_id   = RFIFOL(fd,GETPACKETPOS(cmd,0));
	action_type = RFIFOB(fd,GETPACKETPOS(cmd,1));

	// decode for jRO 2005-05-09dRagexe
	if( packet_db[cmd].pos[0]==0 )
	{
		int t1[]={ 88, 37 }, t2[]={ 80, 4 };
		int pos = ( ( g_packet_len - t1[g_packet_len&1] ) >> 1 ) + t2[g_packet_len&1];
		target_id = RFIFOL(fd,pos);
	}
	// end decode

	switch(action_type){
	case 0x00:	// once attack
	case 0x07:	// continuous attack
		if(sd->state.store) return;
		if(sd->state.blockedmove) return;

		if(!battle_config.sdelay_attack_enable && pc_checkskill(sd,SA_FREECAST) <= 0 ) {
			if(DIFF_TICK(tick , sd->ud.canact_tick) < 0) {
				clif_skill_fail(sd,1,SKILLFAIL_INTERVAL,0,0);
				return;
			}
		}
		if(sd->sc.data[SC_WEDDING].timer != -1 ||
		   sd->sc.data[SC_BASILICA].timer != -1 ||
		   sd->sc.data[SC_GOSPEL].timer != -1 ||
		   sd->sc.data[SC_SANTA].timer != -1 ||
		   sd->sc.data[SC_SUMMER].timer != -1 ||
		   (sd->sc.data[SC_GRAVITATION_USER].timer != -1 && battle_config.player_gravitation_type < 2) ||
		   sd->sc.data[SC_ALL_RIDING].timer != -1)
			return;
		if(sd->invincible_timer != -1)
			pc_delinvincibletimer(sd,1);
		unit_attack(&sd->bl,target_id,action_type!=0);
		break;
	case 0x02:	// sitdown
		if(battle_config.basic_skill_check == 0 || pc_checkskill(sd,NV_BASIC) >= 3 || pc_checkskill(sd,SU_BASIC_SKILL)) {
			pc_setsit(sd);
			clif_sitting(&sd->bl, 1);
			skill_sit(sd,1);	// �M�����O�X�^�[�p���_�C�X����уe�R���x���ݒ�
		} else {
			clif_skill_fail(sd,NV_BASIC,SKILLFAIL_LEVEL,2,0);
		}
		break;
	case 0x03:	// standup
		if(sd->sc.data[SC_SITDOWN_FORCE].timer == -1 || sd->sc.data[SC_BANANA_BOMB].timer == -1) {
			pc_setstand(sd);
			clif_sitting(&sd->bl, 0);
			skill_sit(sd,0);	// �M�����O�X�^�[�p���_�C�X����уe�R���x������
		}
		break;
	}

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_Restart(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	switch(RFIFOB(fd,GETPACKETPOS(cmd,0))){ // restarttype
	case 0x00: // 0: restart game when character died
		if(unit_isdead(&sd->bl)) {
			pc_setpos(sd,sd->status.save_point.map,sd->status.save_point.x,sd->status.save_point.y,2);
		}
		break;
	case 0x01: // 1: request character select
		if(unit_isdead(&sd->bl))
			pc_setrestartvalue(sd,3);
		if(!pc_isquitable(sd)) {
			clif_disconnect_ack(fd, 1);
			return;
		}
		if(sd->pd) {
			pet_lootitem_drop(sd->pd,sd);
			unit_free(&sd->pd->bl, 0);
		}
		if(sd->hd) {
			unit_free(&sd->hd->bl, 0);
		}
		if(sd->mcd) {
			unit_free(&sd->mcd->bl, 0);
		}
		if(sd->eld) {
			unit_free(&sd->eld->bl, 0);
		}
		unit_free(&sd->bl, 2);
		chrif_save(sd, 2);
		sd->state.waitingdisconnect = 1;
		break;
	}

	return;
}

/*==========================================
 * Wis�̑��M
 *------------------------------------------
 */
static void clif_parse_Wis(int fd,struct map_session_data *sd, int cmd)
{
	char *message, *name;
	int message_size;

	nullpo_retv(sd);

	message_size = RFIFOW(fd,GETPACKETPOS(cmd,0)) - GETPACKETPOS(cmd,2); // including NULL
	message = (char *)RFIFOP(fd,GETPACKETPOS(cmd,2));

	if (message_size <= 1)	// NULL (1) (no void message)
		return;
	if (message_size > 255)	// too long
		return;

#if PACKETVER >= 20151029
	message[message_size] = 0; // be sure to have a NULL (hacker can send a no-NULL terminated string)
	message_size++;
#else
	message[message_size - 1] = 0; // be sure to have a NULL (hacker can send a no-NULL terminated string)
#endif

	if(is_atcommand_sub(fd, sd, message, 0) != AtCommand_None)
		return;

	name = (char *)RFIFOP(fd,GETPACKETPOS(cmd,1));
	name[23] = '\0';	// force \0 terminal

	// a normal client can not send a wisp message to yourself (anti-hack)
	if (strncmp(name, sd->status.name, 24) == 0)
		return;

	// �o�[�T�[�N�A�`���b�g�֎~��ԂȂ��b�s��
	if (sd->sc.data[SC_BERSERK].timer != -1 || sd->sc.data[SC_NOCHAT].timer != -1 || sd->sc.data[SC_DEEP_SLEEP].timer != -1)
		return;

	intif_wis_message(sd, name, message, message_size);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_GMmessage(int fd,struct map_session_data *sd, int cmd)
{
	char *message;
	int message_size;

	message_size = RFIFOW(fd,GETPACKETPOS(cmd,0)) - GETPACKETPOS(cmd,1); // including NULL
	message = (char *)RFIFOP(fd,GETPACKETPOS(cmd,1));

	if (message_size <= 1)	// NULL (1) (no void message)
		return;
	if (message_size > 255)	// too long
		return;

#if PACKETVER >= 20151029
	message[message_size] = 0; // be sure to have a NULL (hacker can send a no-NULL terminated string)
	message_size++;
#else
	message[message_size - 1] = 0; // be sure to have a NULL (hacker can send a no-NULL terminated string)
#endif

	if (battle_config.atc_gmonly == 0 ||
	    pc_isGM(sd) >= get_atcommand_level(AtCommand_Broadcast))
		intif_GMmessage(message, message_size, 0);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_TakeItem(int fd,struct map_session_data *sd, int cmd)
{
	struct block_list *bl;
	struct flooritem_data *fitem = NULL;

	nullpo_retv(sd);

	if(unit_isdead(&sd->bl)) {
		clif_clearchar_area(&sd->bl,1);
		return;
	}

	if( sd->npc_id != 0 || sd->state.store || sd->state.deal_mode != 0 || (sd->sc.opt1 > OPT1_NORMAL && sd->sc.opt1 != OPT1_BURNNING) || sd->chatID || sd->state.mail_appending ||
	    sd->state.storage_flag || pc_iscloaking(sd) ||
	    sd->sc.data[SC_AUTOCOUNTER].timer != -1 ||		// �I�[�g�J�E���^�[
	    sd->sc.data[SC_DEATHBOUND].timer != -1 ||	// �f�X�o�E���h
	    sd->sc.data[SC_RUN].timer != -1 ||			// �^�C���M
	    sd->sc.data[SC_FORCEWALKING].timer != -1 ||		// �����ړ����E���Ȃ�
	    sd->sc.data[SC_BLADESTOP].timer != -1 ||		// ���n���
	    sd->sc.data[SC__MANHOLE].timer != -1 ||		// �}���z�[��
	    sd->sc.data[SC_CURSEDCIRCLE_USER].timer != -1 ||	// �����w(�g�p��)
	    sd->sc.data[SC_CURSEDCIRCLE].timer != -1 ||		// �����w
		sd->sc.data[SC_SUHIDE].timer != -1 )	// �������
	{
		clif_additem(sd,0,0,6);
		return;
	}

	bl = map_id2bl(RFIFOL(fd,GETPACKETPOS(cmd,0)));	// map_object_id
	if(bl && bl->type == BL_ITEM)
		fitem = (struct flooritem_data *)bl;

	if(fitem == NULL || fitem->bl.m != sd->bl.m)
		return;

	pc_takeitem(sd,fitem);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_DropItem(int fd,struct map_session_data *sd, int cmd)
{
	int item_index = 0, item_amount = 0;
	unsigned int tick = gettick();

	nullpo_retv(sd);

	item_index  = RFIFOW(fd,GETPACKETPOS(cmd,0)) - 2;
	item_amount = RFIFOW(fd,GETPACKETPOS(cmd,1));

	if(unit_isdead(&sd->bl)) {
		clif_clearchar_area(&sd->bl,1);
		clif_delitem(sd, 0, item_index, 0);	// �N���C�A���g�Ɏ��s�p�P�b�g�𑗐M����K�v������
		return;
	}

	if(++sd->anti_hacker.drop_delay_count == 6) {
		char output[128];
		// %s (ID:%d) �̃A�C�e���h���b�v�Ԋu���ُ�ł��I
		snprintf(output, sizeof(output), msg_txt(47), sd->status.name, sd->status.char_id);
		printf("%s\n", output);
	}

	if( sd->npc_id != 0 || sd->state.store || sd->state.deal_mode != 0 || (sd->sc.opt1 > OPT1_NORMAL && sd->sc.opt1 != OPT1_BURNNING) || sd->state.mail_appending || sd->state.storage_flag || sd->chatID ||
	    DIFF_TICK(tick, sd->anti_hacker.drop_delay_tick) < 0 ||
	    sd->sc.data[SC_AUTOCOUNTER].timer != -1 ||		// �I�[�g�J�E���^�[
	    sd->sc.data[SC_DEATHBOUND].timer != -1 ||	// �f�X�o�E���h
	    sd->sc.data[SC_BLADESTOP].timer != -1 ||		// ���n���
	    sd->sc.data[SC_FORCEWALKING].timer != -1 ||		// �����ړ���
	    sd->sc.data[SC_BERSERK].timer != -1 ||		// �o�[�T�[�N
	    sd->sc.data[SC__MANHOLE].timer != -1 ||		// �}���z�[��
	    sd->sc.data[SC_CURSEDCIRCLE_USER].timer != -1 ||	// �����w(�g�p��)
	    sd->sc.data[SC_CURSEDCIRCLE].timer != -1 ||	// �����w
	    sd->sc.data[SC_DEEP_SLEEP].timer != -1 ||	// ���炬�̎q��S
		sd->sc.data[SC_DIAMONDDUST].timer != -1 ||	// �_�C�������h�_�X�g
		sd->sc.data[SC_SUHIDE].timer != -1 )	// �������
	{
		clif_delitem(sd, 0, item_index, 0);
		return;
	}
	sd->anti_hacker.drop_delay_tick  = tick + 300;
	sd->anti_hacker.drop_delay_count = 0;

	if( pc_dropitem(sd, item_index, item_amount) ) {
		if (battle_config.save_player_when_drop_item) {
			// [Anti-hack] Protection against duplication of items
			// how -> A player drops an item on floor. An other takes the item and disconnects (and the item is saved).
			//        If players know a solution to crash server, they crash it. Then, first player can be not saved and they have duplicated.
			chrif_save(sd, 0);
			if(sd->state.storage_flag == 1)
				storage_storage_save(sd);
		}
	} else {
		clif_delitem(sd, 0, item_index, 0);
	}

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_UseItem(int fd,struct map_session_data *sd, int cmd)
{
	int idx;
	unsigned int tick = gettick();

	nullpo_retv(sd);

	idx = RFIFOW(fd,GETPACKETPOS(cmd,0)) - 2;
	if(idx < 0 || idx >= MAX_INVENTORY)
		return;

	if(unit_isdead(&sd->bl)) {
		clif_clearchar_area(&sd->bl,1);
		clif_useitemack(sd, idx, sd->status.inventory[idx].amount, 0);
		return;
	}
	if( (sd->npc_id != 0 && sd->npc_allowuseitem != 0 && sd->npc_allowuseitem != sd->status.inventory[idx].nameid) ||
	    sd->special_state.item_no_use != 0 || sd->state.store || sd->state.deal_mode != 0 ||
		(sd->sc.opt1 > OPT1_NORMAL && sd->sc.opt1 != OPT1_STONECURSE_ING && sd->sc.opt1 != OPT1_BURNNING) ||
	    sd->state.storage_flag || sd->chatID || sd->state.mail_appending ||
	    DIFF_TICK(tick, sd->item_delay_tick) < 0 || 	// �A�C�e���f�B���C
	    sd->sc.data[SC_TRICKDEAD].timer != -1 ||	// ���񂾂ӂ�
	    sd->sc.data[SC_FORCEWALKING].timer != -1 ||	// �����ړ���
	    sd->sc.data[SC_BERSERK].timer != -1 ||	// �o�[�T�[�N
	    sd->sc.data[SC_WEDDING].timer != -1 ||	// �����ߑ�
	    sd->sc.data[SC_NOCHAT].timer != -1 ||	// ��b�֎~
	    sd->sc.data[SC_GRAVITATION_USER].timer != -1 ||	// �O���r�e�[�V�����t�B�[���h�g�p��
	    sd->sc.data[SC_KINGS_GRACE].timer != -1 ||	// �L���O�X�O���C�X
	    sd->sc.data[SC__SHADOWFORM].timer != -1 ||	// �V���h�E�t�H�[��
	    sd->sc.data[SC__INVISIBILITY].timer != -1 ||	// �C���r�W�r���e�B
	    sd->sc.data[SC__MANHOLE].timer != -1 ||	// �}���z�[��
	    sd->sc.data[SC_DEEP_SLEEP].timer != -1 ||	// ���炬�̎q��S
	    sd->sc.data[SC_SATURDAY_NIGHT_FEVER].timer != -1 ||	// �t���C�f�[�i�C�g�t�B�[�o�[
		sd->sc.data[SC_DIAMONDDUST].timer != -1 ||	// �_�C�������h�_�X�g
		sd->sc.data[SC_SUHIDE].timer != -1 ||	// �������
		sd->sc.data[SC_HANDICAPSTATE_FROSTBITE].timer != -1 ||	// �}��
		sd->sc.data[SC_HANDICAPSTATE_SWOONING].timer != -1 ||	// ���_
		sd->sc.data[SC_HANDICAPSTATE_LIGHTNINGSTRIKE].timer != -1 ||	// ����
		sd->sc.data[SC_HANDICAPSTATE_CRYSTALLIZATION].timer != -1 )	// ������
	{
		clif_useitemack(sd, idx, sd->status.inventory[idx].amount, 0);
		return;
	}

	pc_useitem(sd, idx);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_EquipItem(int fd,struct map_session_data *sd, int cmd)
{
	int idx;

	nullpo_retv(sd);

	if(unit_isdead(&sd->bl)) {
		clif_clearchar_area(&sd->bl,1);
		return;
	}

	idx = RFIFOW(fd,GETPACKETPOS(cmd,0)) - 2;
	if (idx < 0 || idx >= MAX_INVENTORY)
		return;

	if ((sd->npc_id != 0 && sd->npc_allowuseitem != 0 && sd->npc_allowuseitem != sd->status.inventory[idx].nameid) ||
	     sd->state.store || sd->state.deal_mode != 0 || sd->state.mail_appending)
		return;
	if (sd->sc.data[SC_BLADESTOP].timer != -1 || sd->sc.data[SC_BERSERK].timer != -1 || sd->sc.data[SC_KYOUGAKU].timer != -1 || sd->sc.data[SC_SUHIDE].timer != -1)
		return;

	// ����v����
	if (sd->trade.partner != 0) {
		clif_equipitemack(sd, idx, 0, 0);	// fail
		return;
	}

	// ���Ӓ�������͔j�󂳂�Ă���
	if (sd->status.inventory[idx].identify != 1 || sd->status.inventory[idx].attribute != 0) {
		clif_equipitemack(sd, idx, 0, 0);	// fail
		return;
	}

	if (sd->inventory_data[idx]) {
		switch(sd->inventory_data[idx]->type) {
			case ITEMTYPE_ARROW:
			case ITEMTYPE_AMMO:
			case ITEMTYPE_THROWWEAPON:
			case ITEMTYPE_CANNONBALL:
				// ��E�e�ہE�ꖳ�E�藠���E�L���m���{�[��
				pc_equipitem(sd, idx, LOC_ARROW);
				break;
			default:
				if(sd->inventory_data[idx]->flag.pet_acce)	// �y�b�g�p�����i
					pet_equipitem(sd, idx);
				else
#if PACKETVER < 20120925
					pc_equipitem(sd, idx, RFIFOW(fd,GETPACKETPOS(cmd,1)));
#else
					pc_equipitem(sd, idx, RFIFOL(fd,GETPACKETPOS(cmd,1)));
#endif
				break;
		}
	}

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_UnequipItem(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	if (unit_isdead(&sd->bl)) {
		clif_clearchar_area(&sd->bl, 1);
		return;
	}

	if (sd->sc.data[SC_BLADESTOP].timer != -1 || sd->sc.data[SC_BERSERK].timer != -1 || sd->sc.data[SC_KYOUGAKU].timer != -1 || sd->sc.data[SC_SUHIDE].timer != -1)
		return;
	if (sd->npc_id != 0 || sd->state.store || (sd->sc.opt1 > OPT1_NORMAL && sd->sc.opt1 != OPT1_BURNNING) || sd->state.mail_appending)
		return;

	// ����v����
	if (sd->trade.partner != 0) {
		clif_unequipitemack(sd, RFIFOW(fd,GETPACKETPOS(cmd,0)) - 2, 0, 0);	// fail
		return;
	}

	pc_unequipitem(sd, RFIFOW(fd,GETPACKETPOS(cmd,0)) - 2, 0);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_NpcClicked(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	// ����ł�����A�ԃG���̎���NPC���N���b�N�ł��Ȃ�
	if(unit_isdead(&sd->bl)) {
		clif_clearchar_area(&sd->bl,1);
		return;
	}
	if(sd->sc.data[SC_SUHIDE].timer != -1)
		return;
	if(sd->npc_id != 0 || sd->state.store || sd->state.deal_mode != 0 || sd->ud.skilltimer != -1 || sd->status.manner < 0 || sd->state.mail_appending)
		return;
	npc_click(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)));

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_NpcBuySellSelected(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	// ����ł�����A�ԃG���̎���NPC���N���b�N�ł��Ȃ�
	if(unit_isdead(&sd->bl)) {
		clif_clearchar_area(&sd->bl,1);
		return;
	}
	if(sd->sc.data[SC_SUHIDE].timer != -1)
		return;
	if(sd->npc_id != 0 || sd->state.store || sd->state.deal_mode != 0 || sd->status.manner < 0 || sd->state.mail_appending)
		return;
	npc_buysellsel(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)),RFIFOB(fd,GETPACKETPOS(cmd,1)));

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_NpcBuyListSend(int fd,struct map_session_data *sd, int cmd)
{
	int fail, n;
#if PACKETVER < 20180704
	short size = 4;
#else
	short size = 6;
#endif

	nullpo_retv(sd);

	// ����ł�����A�ԃG���̎���NPC���N���b�N�ł��Ȃ�
	if(unit_isdead(&sd->bl)) {
		clif_clearchar_area(&sd->bl,1);
		return;
	}
	if(sd->sc.data[SC_SUHIDE].timer != -1)
		return;
	if(sd->npc_id != 0 || sd->state.store || sd->state.deal_mode != 0 || sd->status.manner < 0 || sd->state.mail_appending)
		return;

	n = (RFIFOW(fd,GETPACKETPOS(cmd,0)) - 4) /size;
	if (n <= 0) // max is checked in npc_buylist function
		return;

	fail = npc_buylist(sd, n, (unsigned char*)RFIFOP(fd,GETPACKETPOS(cmd,1))); // item_list

	sd->npc_shopid = 0;

	WFIFOW(fd,0)=0xca;
	WFIFOB(fd,2)=fail; // 0: The deal has successfully completed., 1: You dont have enough zeny., 2: you are overcharged!, 3: You are over your weight limit.
	WFIFOSET(fd,packet_db[0xca].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_NpcSellListSend(int fd,struct map_session_data *sd, int cmd)
{
	int fail, n;

	nullpo_retv(sd);

	// ����ł�����A�ԃG���̎���NPC���N���b�N�ł��Ȃ�
	if(unit_isdead(&sd->bl)) {
		clif_clearchar_area(&sd->bl,1);
		return;
	}
	if(sd->sc.data[SC_SUHIDE].timer != -1)
		return;
	if(sd->npc_id != 0 || sd->state.store || sd->state.deal_mode != 0 || sd->status.manner < 0 || sd->state.mail_appending)
		return;

	n = (RFIFOW(fd,GETPACKETPOS(cmd,0))-4) /4;
	if (n <= 0 || n > MAX_INVENTORY) // max is checked in npc_selllist function, but normal clients never send more items than total in inventory
		return;

	fail = npc_selllist(sd, n, (unsigned short*)RFIFOP(fd,GETPACKETPOS(cmd,1))); // item_list

	sd->npc_shopid = 0;

	WFIFOW(fd,0)=0xcb;
	WFIFOB(fd,2)=fail;
	WFIFOSET(fd,packet_db[0xcb].len);

	return;
}

/*==========================================
 * �X�y�V�����A�C�e���w���A�C�R��
 *------------------------------------------
 */
static void clif_parse_NpcPointShopOpen(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_NpcPointShopClose(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	sd->npc_shopid = 0;
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_NpcPointShopItemList(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_NpcPointShopBuy(int fd,struct map_session_data *sd, int cmd)
{
	int fail;

	nullpo_retv(sd);

	// ����ł�����A�ԃG���̎���NPC���N���b�N�ł��Ȃ�
	if(unit_isdead(&sd->bl)) {
		clif_clearchar_area(&sd->bl,1);
		return;
	}
	if(sd->sc.data[SC_SUHIDE].timer != -1)
		return;
	if(sd->npc_id != 0 || sd->state.store || sd->status.manner < 0 || sd->state.mail_appending)
		return;
	else
	{
#if PACKETVER < 20070711
		int nameid = RFIFOW(fd,GETPACKETPOS(cmd,0));
		int count  = RFIFOW(fd,GETPACKETPOS(cmd,1));
		fail = npc_pointshop_buy(sd,nameid,count);

		WFIFOW(fd,0)  = 0x289;
		WFIFOL(fd,2)  = sd->shop_point;
		WFIFOW(fd,6)  = fail;
		WFIFOSET(fd,packet_db[0x289].len);
#elif PACKETVER < 20100803
		int nameid = RFIFOW(fd,GETPACKETPOS(cmd,0));
		int count  = RFIFOW(fd,GETPACKETPOS(cmd,1));
		//int points = RFIFOL(fd,GETPACKETPOS(cmd,2));
		fail = npc_pointshop_buy(sd,nameid,count);

		WFIFOW(fd,0)  = 0x289;
		WFIFOL(fd,2)  = sd->shop_point;
		WFIFOL(fd,6)  = 0;	// ??
		WFIFOW(fd,10) = fail;
		WFIFOSET(fd,packet_db[0x289].len);
#else
		int len    = RFIFOW(fd,GETPACKETPOS(cmd,0)) - 10;
		//int points = RFIFOL(fd,GETPACKETPOS(cmd,1));
		int count  = RFIFOW(fd,GETPACKETPOS(cmd,2));
		const unsigned char *item_list = RFIFOP(fd,GETPACKETPOS(cmd,3));
#if PACKETVER < 20180704
		short size = 4;
#else
		short size = 6;
#endif
		fail = npc_pointshop_buylist(sd,( len <= 0 ) ? 0 : len/size,count,item_list);

		WFIFOW(fd,0)  = 0x289;
		WFIFOL(fd,2)  = sd->shop_point;
		WFIFOL(fd,6)  = 0;	// ??
		WFIFOW(fd,10) = fail;
		WFIFOSET(fd,packet_db[0x289].len);
#endif
	}

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_CreateChatRoom(int fd,struct map_session_data *sd, int cmd)
{
	char *chat_title;
	int len;

	nullpo_retv(sd);

	if(sd->status.manner < 0 || (battle_config.basic_skill_check && pc_checkskill(sd,NV_BASIC) < 4 && !pc_checkskill(sd,SU_BASIC_SKILL))) {
		clif_skill_fail(sd,NV_BASIC,SKILLFAIL_LEVEL,3,0);
		return;
	}

	if(npc_isnear(&sd->bl)) {
		clif_skill_fail(sd,NV_BASIC,SKILLFAIL_NEARNPC,0,0);
		return;
	}

	len = (int)RFIFOW(fd,GETPACKETPOS(cmd,0));
	if (len <= GETPACKETPOS(cmd,4))
		return;
	chat_title = (char *)RFIFOP(fd,GETPACKETPOS(cmd,4)); // don't include \0
	if (chat_title[0] == '\0')
		return;
	chat_createchat(sd, RFIFOW(fd,GETPACKETPOS(cmd,1)), RFIFOB(fd,GETPACKETPOS(cmd,2)), (const char *)RFIFOP(fd,GETPACKETPOS(cmd,3)), chat_title, len - GETPACKETPOS(cmd,4));

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_ChatAddMember(int fd,struct map_session_data *sd, int cmd)
{
	chat_joinchat(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)),RFIFOP(fd,GETPACKETPOS(cmd,1)));

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_ChatRoomStatusChange(int fd,struct map_session_data *sd, int cmd)
{
	char *chat_title;
	int len;

	len = (int)RFIFOW(fd,GETPACKETPOS(cmd,0));
	if (len <= GETPACKETPOS(cmd,4))
		return;
	chat_title = (char *)RFIFOP(fd,GETPACKETPOS(cmd,4)); // don't include \0
	if (chat_title[0] == '\0')
		return;
	chat_changechatstatus(sd, RFIFOW(fd,GETPACKETPOS(cmd,1)), RFIFOB(fd,GETPACKETPOS(cmd,2)), (char *)RFIFOP(fd,GETPACKETPOS(cmd,3)), chat_title, len - GETPACKETPOS(cmd,4));

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_ChangeChatOwner(int fd,struct map_session_data *sd, int cmd)
{
	chat_changechatowner(sd, (const char *)RFIFOP(fd,GETPACKETPOS(cmd,1)));

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_KickFromChat(int fd,struct map_session_data *sd, int cmd)
{
	chat_kickchat(sd, (const char *)RFIFOP(fd,GETPACKETPOS(cmd,0)));

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_ChatLeave(int fd,struct map_session_data *sd, int cmd)
{
	chat_leavechat(sd,0);

	return;
}

/*==========================================
 * ����v���𑊎�ɑ���
 *------------------------------------------
 */
static void clif_parse_TradeRequest(int fd,struct map_session_data *sd, int cmd)
{
	int gmlvl = 0;

	nullpo_retv(sd);

	if(map[sd->bl.m].flag.notrade)
		return;
	if(sd->state.store || sd->state.deal_mode != 0 || sd->state.mail_appending)
		return;

	gmlvl = pc_isGM(sd);
	if(gmlvl > 0 && battle_config.gm_can_drop_lv > gmlvl)
		return;

	if(battle_config.basic_skill_check == 0 || pc_checkskill(sd,NV_BASIC) >= 1 || pc_checkskill(sd,SU_BASIC_SKILL))
		trade_traderequest(sd,RFIFOL(sd->fd,GETPACKETPOS(cmd,0)));
	else
		clif_skill_fail(sd,NV_BASIC,SKILLFAIL_LEVEL,0,0);

	return;
}

/*==========================================
 * ����v��
 *------------------------------------------
 */
static void clif_parse_TradeAck(int fd,struct map_session_data *sd, int cmd)
{
	int gmlvl = 0;

	nullpo_retv(sd);

	if(map[sd->bl.m].flag.notrade)
		return;

	gmlvl = pc_isGM(sd);
	if(gmlvl > 0 && battle_config.gm_can_drop_lv > gmlvl)
		return;

	trade_tradeack(sd,RFIFOB(sd->fd,GETPACKETPOS(cmd,0)));

	return;
}

/*==========================================
 * �A�C�e���ǉ�
 *------------------------------------------
 */
static void clif_parse_TradeAddItem(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	trade_tradeadditem(sd,RFIFOW(sd->fd,GETPACKETPOS(cmd,0)),RFIFOL(sd->fd,GETPACKETPOS(cmd,1)));

	return;
}

/*==========================================
 * �A�C�e���ǉ�����(ok����)
 *------------------------------------------
 */
static void clif_parse_TradeOk(int fd,struct map_session_data *sd, int cmd)
{
	trade_tradeok(sd);

	return;
}

/*==========================================
 * ����L�����Z��
 *------------------------------------------
 */
static void clif_parse_TradeCancel(int fd,struct map_session_data *sd, int cmd)
{
	trade_tradecancel(sd);

	return;
}

/*==========================================
 * �������(trade����)
 *------------------------------------------
 */
static void clif_parse_TradeCommit(int fd,struct map_session_data *sd, int cmd)
{
	trade_tradecommit(sd);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_StopAttack(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	unit_stopattack(&sd->bl);

	return;
}

/*==========================================
 * �J�[�g�փA�C�e�����ڂ�
 *------------------------------------------
 */
static void clif_parse_PutItemToCart(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	if (sd->npc_id != 0 || sd->state.store || sd->state.deal_mode != 0 || sd->state.mail_appending || pc_iscarton(sd) == 0)
		return;
	pc_putitemtocart(sd,RFIFOW(fd,GETPACKETPOS(cmd,0))-2,RFIFOL(fd,GETPACKETPOS(cmd,1)));

	return;
}

/*==========================================
 * �J�[�g����A�C�e�����o��
 *------------------------------------------
 */
static void clif_parse_GetItemFromCart(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	if (sd->npc_id != 0 || sd->state.store || sd->state.deal_mode != 0 || sd->state.mail_appending || pc_iscarton(sd) == 0)
		return;
	pc_getitemfromcart(sd,RFIFOW(fd,GETPACKETPOS(cmd,0))-2,RFIFOL(fd,GETPACKETPOS(cmd,1)));

	return;
}

/*==========================================
 * �t���i(��,�y�R,�J�[�g)���͂���
 *------------------------------------------
 */
static void clif_parse_RemoveOption(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	if (sd->npc_id != 0 || sd->state.store || sd->state.deal_mode != 0 || sd->state.mail_appending)
		return;
	pc_setoption(sd,0);

	return;
}

/*==========================================
 * �`�F���W�J�[�g
 *------------------------------------------
 */
static void clif_parse_ChangeCart(int fd,struct map_session_data *sd, int cmd)
{
	if(pc_iscarton(sd))
		pc_setcart(sd, RFIFOW(fd,GETPACKETPOS(cmd,0)));

	return;
}

/*==========================================
 * �X�e�[�^�X�A�b�v
 *------------------------------------------
 */
static void clif_parse_StatusUp(int fd,struct map_session_data *sd, int cmd)
{
	// Is amount RFIFOB(fd,GETPACKETPOS(cmd,1)) always 1?
	pc_statusup(sd, RFIFOW(fd,GETPACKETPOS(cmd,0)), RFIFOB(fd,GETPACKETPOS(cmd,1)));

	return;
}

/*==========================================
 * �X�L�����x���A�b�v
 *------------------------------------------
 */
static void clif_parse_SkillUp(int fd,struct map_session_data *sd, int cmd)
{
	int skill_num = RFIFOW(fd,GETPACKETPOS(cmd,0));

	if( skill_num >= GUILD_SKILLID )	// �M���h�X�L��
		guild_skillup(sd,skill_num,0,0);
	else if( skill_num >= HOM_SKILLID )	// �z�����N���X�X�L��
		homun_skillup(sd,skill_num);
	else
		pc_skillup(sd,skill_num);

	return;
}

/*==========================================
 * �X�L���g�p�iID�w��j�{��
 *------------------------------------------
 */
static void clif_UseSkillToId_Sub(struct map_session_data *sd, int skillnum, int skilllv, int target_id)
{
	int lv, skilldb_id, inf, change_inf = 0;
	unsigned int tick = gettick();
	struct block_list *bl;
	struct status_change *sc;

	nullpo_retv(sd);

	if(map[sd->bl.m].flag.noskill)
		return;
	if(sd->npc_id != 0 || sd->state.store || sd->state.deal_mode != 0 || sd->chatID || sd->state.storage_flag || sd->state.mail_appending || sd->state.blockedmove)
		return;
	if(pc_issit(sd))
		return;

	bl = map_id2bl(target_id);
	if(bl == NULL)
		return;

	inf = skill_get_inf(skillnum);
	if(inf == INF_PASSIVE || inf & INF_GROUND) {
		// anti hacker
		return;
	}

	if(skillnum >= HOM_SKILLID && skillnum < MAX_HOM_SKILLID) {
		// �z���X�L��
		struct homun_data *hd = sd->hd;
		if( hd && (lv = homun_checkskill(hd,skillnum)) ) {
			if(skilllv > lv)
				skilllv = lv;
			if(hd->ud.skilltimer != -1)
				return;
			if(DIFF_TICK(tick, hd->ud.canact_tick) < 0)
				return;
			if(DIFF_TICK(tick, hd->skillstatictimer[skillnum-HOM_SKILLID]) < 0)
				return;

			if(skillnum == MH_SONIC_CRAW) {
				if(hd->sc.data[SC_COMBO].timer == -1 || hd->sc.data[SC_COMBO].val1 != MH_MIDNIGHT_FRENZY)
					change_inf = 1;
			}

			if(inf & INF_SELF && !change_inf) {
				// ���������Ȃ�^�[�Q�b�g���������g�ɂ���
				target_id = hd->bl.id;
			}

			if(change_inf && target_id == hd->bl.id) {
				clif_skillinfo(hd->msd,skillnum,1,-1);
				return;
			}
			unit_skilluse_id(&hd->bl,target_id,skillnum,skilllv);
		}
		return;
	}
	if(skillnum >= MERC_SKILLID && skillnum < MAX_MERC_SKILLID) {
		// �b���X�L��
		struct merc_data *mcd = sd->mcd;
		if( mcd && (lv = merc_checkskill(mcd,skillnum)) ) {
			if(skilllv > lv)
				skilllv = lv;
			if(mcd->ud.skilltimer != -1)
				return;
			if(DIFF_TICK(tick, mcd->ud.canact_tick) < 0)
				return;
			if(DIFF_TICK(tick, mcd->skillstatictimer[skillnum-MERC_SKILLID]) < 0)
				return;

			if(inf & INF_SELF)	// �������Ώ�
				unit_skilluse_id(&mcd->bl,mcd->bl.id,skillnum,skilllv);
			else
				unit_skilluse_id(&mcd->bl,target_id,skillnum,skilllv);
		}
		return;
	}
	if(skillnum >= ELEM_SKILLID && skillnum < MAX_ELEM_SKILLID) {
		// ����X�L��
		struct elem_data *eld = sd->eld;
		if( eld && (lv = elem_checkskill(eld,skillnum)) ) {
			if(skilllv > lv)
				skilllv = lv;
			if(eld->ud.skilltimer != -1)
				return;
			if(DIFF_TICK(tick, eld->ud.canact_tick) < 0)
				return;
			if(DIFF_TICK(tick, eld->skillstatictimer[skillnum-ELEM_SKILLID]) < 0)
				return;

			if(inf & INF_SELF)	// �������Ώ�
				unit_skilluse_id(&eld->bl,eld->bl.id,skillnum,skilllv);
			else
				unit_skilluse_id(&eld->bl,target_id,skillnum,skilllv);
		}
		return;
	}
	if(skillnum >= GUILD_SKILLID) {
		struct guild *g = guild_search(sd->status.guild_id);

		// �M���h�X�L���̓M���}�X�̂�
		if(g == NULL || sd != guild_get_guildmaster_sd(g))
			return;
		// skilllv�͏��0�Ȃ̂Ō��݂̃X�L��Lv�ŕ␳����
		skilllv = guild_checkskill(g, skillnum);
	}

	// inf�́u���������v���u�G�v�ɕς��ꍇ
	switch(skillnum) {
		case MO_EXTREMITYFIST:
			if(sd->sc.data[SC_COMBO].timer == -1 || (sd->sc.data[SC_COMBO].val1 != MO_COMBOFINISH && sd->sc.data[SC_COMBO].val1 != CH_CHAINCRUSH)) {
				change_inf = 1;
			}
			break;
		case TK_JUMPKICK:
			if(sd->sc.data[SC_DODGE_DELAY].timer == -1) {
				change_inf = 1;
			}
			break;
		case SR_TIGERCANNON:
		case SR_GATEOFHELL:
			if(sd->sc.data[SC_COMBO].timer == -1 || sd->sc.data[SC_COMBO].val1 != SR_FALLENEMPIRE) {
				change_inf = 1;
			}
			break;
	}

	if((inf & INF_SELF) && !change_inf) {
		// ���������Ȃ�^�[�Q�b�g���������g�ɂ���
		target_id = sd->bl.id;
	}

	if(sd->ud.skilltimer != -1) {
		if(skillnum != SA_CASTCANCEL && !(skillnum == SO_SPELLFIST && (sd->ud.skillid == MG_FIREBOLT || sd->ud.skillid == MG_COLDBOLT || sd->ud.skillid == MG_LIGHTNINGBOLT)))
			return;
	} else if(DIFF_TICK(tick, sd->ud.canact_tick) < 0) {
		clif_skill_fail(sd,skillnum,SKILLFAIL_INTERVAL,0,0);
		return;
	}

	// static timer�̔���
	skilldb_id = skill_get_skilldb_id(skillnum);
	if(skilldb_id <= 0)
		return;
	if(DIFF_TICK(tick, sd->skillstatictimer[skilldb_id]) < 0) {
		clif_skill_fail(sd,skillnum,SKILLFAIL_INTERVAL,0,0);
		return;
	}
	// cooldown�̔���
	if(DIFF_TICK(tick, sd->skillcooldown[skilldb_id]) < 0) {
		clif_skill_fail(sd,skillnum,SKILLFAIL_INTERVAL,0,0);
		return;
	}
	// ��z�̏ꍇ�͉��t�̍Ďg�p���Ԃ𔻒�
	if(skillnum == TR_RETROSPECTION && sd->skill_4thdance.id) {
		if(DIFF_TICK(tick, sd->skillcooldown[skill_get_skilldb_id(sd->skill_4thdance.id)]) < 0) {
			clif_skill_fail(sd,skillnum,SKILLFAIL_INTERVAL,0,0);
			return;
		}
	}

	if( (sd->sc.data[SC_TRICKDEAD].timer != -1 && skillnum != NV_TRICKDEAD) ||
	    sd->sc.data[SC_NOCHAT].timer != -1 ||
	    sd->sc.data[SC_WEDDING].timer != -1 ||
	    sd->sc.data[SC_FORCEWALKING].timer != -1 ||
	    sd->sc.data[SC_SANTA].timer != -1 ||
	    sd->sc.data[SC_SUMMER].timer != -1 ||
	    sd->sc.data[SC_ALL_RIDING].timer != -1 ||
	    sd->sc.data[SC_KINGS_GRACE].timer != -1 ||	// �L���O�X�O���C�X
	    (sd->sc.data[SC_MEIKYOUSISUI].timer != -1 && !(inf & INF_SELF)) ||
	    (sd->sc.data[SC_SUHIDE].timer != -1 && skillnum != SU_HIDE))
		return;
	if(sd->sc.data[SC_BASILICA].timer != -1 && (skillnum != HP_BASILICA || sd->sc.data[SC_BASILICA].val2 != sd->bl.id))
		return;
	if(sd->sc.data[SC_GOSPEL].timer != -1 && (skillnum != PA_GOSPEL || sd->sc.data[SC_GOSPEL].val2 != sd->bl.id))
		return;

	sc = status_get_sc(bl);
	if(sc && sc->option & (OPTION_HIDE | OPTION_CLOAKING | OPTION_FOOTPRINT) && ((&sd->bl) != bl))
	{
		// �����ƈ����͍U���\�H
		if(sd->race != RCT_INSECT && sd->race != RCT_DEMON)
			return;
	}

	if(sd->invincible_timer != -1)
		pc_delinvincibletimer(sd,1);

	if(sd->skill_item.id >= 0 && sd->skill_item.id == skillnum) {
		if(skilllv != sd->skill_item.lv)
			skilllv = sd->skill_item.lv;
		if( !unit_skilluse_id(&sd->bl,target_id,skillnum,skilllv) ) {
			sd->skill_item.id      = -1;
			sd->skill_item.lv      = -1;
			sd->skill_item.flag    = 0;
		}
	} else {
		sd->skill_item.id      = -1;
		sd->skill_item.lv      = -1;
		sd->skill_item.flag    = 0;

		if(change_inf) {
			if(!sd->state.skill_flag) {
				sd->state.skill_flag = 1;
				clif_skillinfo(sd,skillnum,1,-1);
				return;
			}
			if(sd->bl.id == target_id) {
				clif_skillinfo(sd,skillnum,1,-1);
				return;
			}
		}
		if((lv = pc_checkskill(sd,skillnum)) > 0) {
			if(skilllv > lv)
				skilllv = lv;
			unit_skilluse_id(&sd->bl,target_id,skillnum,skilllv);
			if(sd->state.skill_flag)
				sd->state.skill_flag = 0;
		}
	}
	return;
}

/*==========================================
 * �X�L���g�p�iID�w��j
 *------------------------------------------
 */
static void clif_parse_UseSkillToId(int fd, struct map_session_data *sd, int cmd)
{
	int skillnum, skilllv, target_id;

	nullpo_retv(sd);

	skilllv   = RFIFOW(fd,GETPACKETPOS(cmd,0));
	skillnum  = RFIFOW(fd,GETPACKETPOS(cmd,1));
	target_id = RFIFOL(fd,GETPACKETPOS(cmd,2));

	// decode for jRO 2005-05-09dRagexe
	if(packet_db[cmd].pos[0] == 0 && packet_db[cmd].pos[1] == 0 && packet_db[cmd].pos[2] == 0)
	{
		int tmp = g_packet_len % 3;
		const int t1[] = { 138,43,170 }, t2[] = { 103,4,80 }, t3[] = { 130,33,84 }, t4[] = { 134, 39, 166 };
		int tmp2 = (g_packet_len - t1[tmp]) / 3;
		skilllv   = RFIFOW(fd, tmp2   + t2[tmp] );
		skillnum  = RFIFOW(fd, tmp2*2 + t3[tmp] );
		target_id = RFIFOL(fd, tmp2*3 + t4[tmp] );
	}
	// end decode

	clif_UseSkillToId_Sub(sd, skillnum, skilllv, target_id);
	return;
}

/*==========================================
 * �X�L���g�p�J�n�iID�w��j
 *------------------------------------------
 */
static void clif_parse_StartUseSkillToId(int fd,struct map_session_data *sd, int cmd)
{
#if PACKETVER >= 20181002
	int skillnum, skilllv, target_id;

	nullpo_retv(sd);

	skillnum  = RFIFOW(fd,GETPACKETPOS(cmd,0));
	skilllv   = RFIFOW(fd,GETPACKETPOS(cmd,1));
	target_id = RFIFOL(fd,GETPACKETPOS(cmd,2));

	if(skillnum != GC_ROLLINGCUTTER)
		// anti hacker
		return;

	sd->state.autoskill_flag = true;

	clif_UseSkillToId_Sub(sd, skillnum, skilllv, target_id);
	return;
#endif
}

/*==========================================
 * �X�L���g�p�I���iID�w��j
 *------------------------------------------
 */
static void clif_parse_StopUseSkillToId(int fd,struct map_session_data *sd, int cmd)
{
#if PACKETVER >= 20181002
	int skillnum = RFIFOW(fd,GETPACKETPOS(cmd,0));
	if(skillnum != GC_ROLLINGCUTTER) {
		// anti hacker
	}
	sd->state.autoskill_flag = false;
	return;
#endif
}

/*==========================================
 * �X�L���g�p�i�ꏊ�w��j
 *------------------------------------------
 */
static void clif_parse_UseSkillToPos(int fd, struct map_session_data *sd, int cmd)
{
	int skillnum, skilllv, lv, x, y, skilldb_id;
	unsigned int tick = gettick();

	nullpo_retv(sd);

	if(map[sd->bl.m].flag.noskill)
		return;
	if(sd->npc_id != 0 || sd->state.store || sd->state.deal_mode != 0 || sd->chatID || sd->state.storage_flag || sd->state.mail_appending || sd->state.blockedmove)
		return;

	skilllv  = RFIFOW(fd,GETPACKETPOS(cmd,0));
	skillnum = RFIFOW(fd,GETPACKETPOS(cmd,1));
	x        = RFIFOW(fd,GETPACKETPOS(cmd,2));
	y        = RFIFOW(fd,GETPACKETPOS(cmd,3));

	if(!(skill_get_inf(skillnum) & INF_GROUND)) {
		// anti hacker
		return;
	}

	if(skillnum >= HOM_SKILLID && skillnum < MAX_HOM_SKILLID) {
		// �z���X�L��
		struct homun_data *hd = sd->hd;
		if( hd && (lv = homun_checkskill(hd,skillnum)) ) {
			if(skilllv > lv)
				skilllv = lv;
			if(hd->ud.skilltimer != -1)
				return;
			if(DIFF_TICK(tick, hd->ud.canact_tick) < 0)
				return;
			if(DIFF_TICK(tick, hd->skillstatictimer[skillnum-HOM_SKILLID]) < 0)
				return;

			unit_skilluse_pos(&hd->bl,x,y,skillnum,skilllv);
		}
		return;
	}
	if(skillnum >= MERC_SKILLID && skillnum < MAX_MERC_SKILLID) {
		// �b���X�L��
		struct merc_data *mcd = sd->mcd;
		if( mcd && (lv = merc_checkskill(mcd,skillnum)) ) {
			if(skilllv > lv)
				skilllv = lv;
			if(mcd->ud.skilltimer != -1)
				return;
			if(DIFF_TICK(tick, mcd->ud.canact_tick) < 0)
				return;
			if(DIFF_TICK(tick, mcd->skillstatictimer[skillnum-MERC_SKILLID]) < 0)
				return;

			unit_skilluse_pos(&mcd->bl,x,y,skillnum,skilllv);
		}
		return;
	}
	if(skillnum >= ELEM_SKILLID && skillnum < MAX_ELEM_SKILLID) {
		// ����X�L��
		struct elem_data *eld = sd->eld;
		if( eld && (lv = elem_checkskill(eld,skillnum)) ) {
			if(skilllv > lv)
				skilllv = lv;
			if(eld->ud.skilltimer != -1)
				return;
			if(DIFF_TICK(tick, eld->ud.canact_tick) < 0)
				return;
			if(DIFF_TICK(tick, eld->skillstatictimer[skillnum-ELEM_SKILLID]) < 0)
				return;

			unit_skilluse_pos(&eld->bl,x,y,skillnum,skilllv);
		}
		return;
	}

	if(sd->ud.skilltimer != -1)
		return;
	if(DIFF_TICK(tick, sd->ud.canact_tick) < 0) {
		clif_skill_fail(sd,skillnum,SKILLFAIL_INTERVAL,0,0);
		return;
	}

	// static timer�̔���
	skilldb_id = skill_get_skilldb_id(skillnum);
	if(skilldb_id <= 0)
		return;
	if(DIFF_TICK(tick, sd->skillstatictimer[skilldb_id]) < 0) {
		clif_skill_fail(sd,skillnum,SKILLFAIL_INTERVAL,0,0);
		return;
	}
	// cooldown�̔���
	if(DIFF_TICK(tick, sd->skillcooldown[skilldb_id]) < 0) {
		clif_skill_fail(sd,skillnum,SKILLFAIL_INTERVAL,0,0);
		return;
	}

	if(GETPACKETPOS(cmd,4)) {
		if(pc_issit(sd)) {
			clif_skill_fail(sd,skillnum,SKILLFAIL_FAILED,0,0);
			return;
		}
		memcpy(sd->message,RFIFOP(fd,GETPACKETPOS(cmd,4)),80);
		sd->message[79] = '\0'; // message includes NULL, but add it against hacker
	}
	else if(pc_issit(sd)) {
		return;
	}

	if( (sd->sc.data[SC_TRICKDEAD].timer != -1 && skillnum != NV_TRICKDEAD) ||
	    sd->sc.data[SC_NOCHAT].timer != -1 ||
	    sd->sc.data[SC_WEDDING].timer != -1 ||
	    sd->sc.data[SC_GOSPEL].timer != -1 ||
	    sd->sc.data[SC_FORCEWALKING].timer != -1 ||
	    sd->sc.data[SC_SANTA].timer != -1 ||
	    sd->sc.data[SC_SUMMER].timer != -1 ||
	    sd->sc.data[SC_ALL_RIDING].timer != -1 ||
	    sd->sc.data[SC_KINGS_GRACE].timer != -1 ||	// �L���O�X�O���C�X
	    sd->sc.data[SC_MEIKYOUSISUI].timer != -1 ||
	    sd->sc.data[SC_SUHIDE].timer != -1)
		return;
	if(sd->sc.data[SC_BASILICA].timer != -1 && (skillnum != HP_BASILICA || sd->sc.data[SC_BASILICA].val2 != sd->bl.id))
		return;

	if(sd->invincible_timer != -1)
		pc_delinvincibletimer(sd,1);

	if(sd->skill_item.id >= 0 && sd->skill_item.id == skillnum) {
		if(skilllv != sd->skill_item.lv)
			skilllv = sd->skill_item.lv;
		if( !unit_skilluse_pos(&sd->bl,x,y,skillnum,skilllv) ) {
			sd->skill_item.id      = -1;
			sd->skill_item.lv      = -1;
			sd->skill_item.flag    = 0;
		}
	} else {
		sd->skill_item.id      = -1;
		sd->skill_item.lv      = -1;
		sd->skill_item.flag    = 0;
		if((lv = pc_checkskill(sd,skillnum)) > 0) {
			if(skilllv > lv)
				skilllv = lv;
			unit_skilluse_pos(&sd->bl,x,y,skillnum,skilllv);
		}
	}

	return;
}

/*==========================================
 * �X�L���g�p�imap�w��j
 *------------------------------------------
 */
static void clif_parse_UseSkillMap(int fd, struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	if(map[sd->bl.m].flag.noskill)
		return;
	if(sd->npc_id != 0 || sd->state.store || sd->state.deal_mode != 0 || sd->chatID || sd->state.storage_flag || sd->state.mail_appending || sd->state.blockedmove)
		return;

	if(sd->sc.data[SC_TRICKDEAD].timer != -1 ||
	   sd->sc.data[SC_NOCHAT].timer != -1 ||
	   sd->sc.data[SC_WEDDING].timer != -1 ||
	   sd->sc.data[SC_BASILICA].timer != -1 ||
	   sd->sc.data[SC_GOSPEL].timer != -1 ||
	   sd->sc.data[SC_FORCEWALKING].timer != -1 ||
	   sd->sc.data[SC_SANTA].timer != -1 ||
	   sd->sc.data[SC_SUMMER].timer != -1 ||
	   sd->sc.data[SC_ALL_RIDING].timer != -1 ||
	   sd->sc.data[SC_KINGS_GRACE].timer != -1 ||	// �L���O�X�O���C�X
	   sd->sc.data[SC_MEIKYOUSISUI].timer != -1 ||
	   sd->sc.data[SC_SUHIDE].timer != -1)
		return;

	if(sd->invincible_timer != -1)
		pc_delinvincibletimer(sd,1);

	RFIFOB(fd,GETPACKETPOS(cmd,1)+15) = '\0'; // be sure to have NULL
	skill_castend_map(sd,RFIFOW(fd,GETPACKETPOS(cmd,0)),RFIFOP(fd,GETPACKETPOS(cmd,1)));

	return;
}

/*==========================================
 * �����v��
 *------------------------------------------
 */
static void clif_parse_RequestMemo(int fd,struct map_session_data *sd, int cmd)
{
	pc_memo(sd,-1);

	return;
}

/*==========================================
 * �A�C�e������
 *------------------------------------------
 */
static void clif_parse_ProduceMix(int fd,struct map_session_data *sd, int cmd)
{
	int nameid, slot1, slot2, slot3;

	nullpo_retv(sd);

#if PACKETVER < 20180704
	switch(sd->skill_menu.id)
	{
		case AC_MAKINGARROW:		/* ��쐬 */
			skill_arrow_create(sd,RFIFOW(fd,GETPACKETPOS(cmd,0)));
			break;

		case GC_POISONINGWEAPON:	/* �|�C�Y�j���O�E�F�|�� */
			skill_poisoning_weapon(sd,RFIFOW(fd,GETPACKETPOS(cmd,0)));
			break;

		case WL_READING_SB:			/* ���[�f�B���O�X�y���u�b�N */
			skill_reading_sb(sd,RFIFOW(fd,GETPACKETPOS(cmd,0)));
			break;

		case NC_MAGICDECOY:			/* FAW �}�W�b�N�f�R�C */
			skill_magicdecoy(sd,RFIFOW(fd,GETPACKETPOS(cmd,0)));
			break;
	}
	nameid = RFIFOW(fd,GETPACKETPOS(cmd,0));
	slot1  = RFIFOW(fd,GETPACKETPOS(cmd,1));
	slot2  = RFIFOW(fd,GETPACKETPOS(cmd,2));
	slot3  = RFIFOW(fd,GETPACKETPOS(cmd,3));
#else
	switch(sd->skill_menu.id)
	{
		case AC_MAKINGARROW:		/* ��쐬 */
			skill_arrow_create(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)));
			break;

		case GC_POISONINGWEAPON:	/* �|�C�Y�j���O�E�F�|�� */
			skill_poisoning_weapon(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)));
			break;

		case WL_READING_SB:			/* ���[�f�B���O�X�y���u�b�N */
			skill_reading_sb(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)));
			break;

		case NC_MAGICDECOY:			/* FAW �}�W�b�N�f�R�C */
			skill_magicdecoy(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)));
			break;
	}
	nameid = RFIFOL(fd,GETPACKETPOS(cmd,0));
	slot1  = RFIFOL(fd,GETPACKETPOS(cmd,1));
	slot2  = RFIFOL(fd,GETPACKETPOS(cmd,2));
	slot3  = RFIFOL(fd,GETPACKETPOS(cmd,3));
#endif
	skill_produce_mix(sd,nameid,slot1,slot2,slot3);

	memset(&sd->skill_menu,0,sizeof(sd->skill_menu));

	return;
}

/*==========================================
 * ����C��
 *------------------------------------------
 */
static void clif_parse_RepairItem(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	skill_repair_weapon(sd,RFIFOW(fd,GETPACKETPOS(cmd,0)));

	memset(&sd->skill_menu,0,sizeof(sd->skill_menu));

	return;
}

/*==========================================
 * ���퐸�B
 *------------------------------------------
 */
static void clif_parse_WeaponRefine(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	skill_weapon_refine(sd, RFIFOW(fd,GETPACKETPOS(cmd,0)) - 2); // index

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_NpcSelectMenu(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	sd->npc_menu=RFIFOB(fd,GETPACKETPOS(cmd,1));
	npc_scriptcont(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)));

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_NpcNextClicked(int fd,struct map_session_data *sd, int cmd)
{
	npc_scriptcont(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)));

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_NpcAmountInput(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	sd->npc_amount = (int)RFIFOL(fd,GETPACKETPOS(cmd,1));
	npc_scriptcont(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)));

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_NpcStringInput(int fd,struct map_session_data *sd, int cmd)
{
	int len;

	nullpo_retv(sd);

	len = (int)RFIFOW(fd,GETPACKETPOS(cmd,0));

	// check validity of length (against hacker)
	if (len < (int)GETPACKETPOS(cmd,2) + 1)
		return;
	// normal client send NULL -> force it (against hacker)
#if PACKETVER >= 20151029
	RFIFOB(fd,len) = '\0';
#else
	RFIFOB(fd,len - 1) = '\0';
#endif

	if (len - (int)GETPACKETPOS(cmd,2) >= sizeof(sd->npc_str)) { // message includes NULL
		//printf("clif: input string too long !\n"); // no display, it's not an error, just a check against overflow (and hacker)
		memcpy(sd->npc_str, RFIFOP(fd,GETPACKETPOS(cmd,2)), sizeof(sd->npc_str));
	} else {
		strncpy(sd->npc_str, RFIFOP(fd,GETPACKETPOS(cmd,2)), sizeof(sd->npc_str));
	}
	sd->npc_str[sizeof(sd->npc_str) - 1] = 0;
	npc_scriptcont(sd,RFIFOL(fd,GETPACKETPOS(cmd,1)));

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_NpcCloseClicked(int fd,struct map_session_data *sd, int cmd)
{
	npc_scriptcont(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)));

	return;
}

/*==========================================
 * �A�C�e���Ӓ�
 *------------------------------------------
 */
static void clif_parse_ItemIdentify(int fd,struct map_session_data *sd, int cmd)
{
	pc_item_identify(sd,RFIFOW(fd,GETPACKETPOS(cmd,0))-2);

	return;
}

/*==========================================
 * �A�C�e�����X�g�I����M
 *------------------------------------------
 */
static void clif_parse_SelectItem(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

#if PACKETVER < 20180704
	switch(sd->skill_menu.id)
	{
		case AC_MAKINGARROW:		/* ��쐬 */
			skill_arrow_create(sd,RFIFOW(fd,GETPACKETPOS(cmd,0)));
			break;

		case GC_POISONINGWEAPON:	/* �|�C�Y�j���O�E�F�|�� */
			skill_poisoning_weapon(sd,RFIFOW(fd,GETPACKETPOS(cmd,0)));
			break;

		case WL_READING_SB:			/* ���[�f�B���O�X�y���u�b�N */
			skill_reading_sb(sd,RFIFOW(fd,GETPACKETPOS(cmd,0)));
			break;

		case NC_MAGICDECOY:			/* FAW �}�W�b�N�f�R�C */
			skill_magicdecoy(sd,RFIFOW(fd,GETPACKETPOS(cmd,0)));
			break;
	}
#else
	switch(sd->skill_menu.id)
	{
		case AC_MAKINGARROW:		/* ��쐬 */
			skill_arrow_create(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)));
			break;

		case GC_POISONINGWEAPON:	/* �|�C�Y�j���O�E�F�|�� */
			skill_poisoning_weapon(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)));
			break;

		case WL_READING_SB:			/* ���[�f�B���O�X�y���u�b�N */
			skill_reading_sb(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)));
			break;

		case NC_MAGICDECOY:			/* FAW �}�W�b�N�f�R�C */
			skill_magicdecoy(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)));
			break;
	}
#endif

	memset(&sd->skill_menu,0,sizeof(sd->skill_menu));

	return;
}

/*==========================================
 * �I�[�g�X�y����M
 *------------------------------------------
 */
static void clif_parse_AutoSpell(int fd,struct map_session_data *sd, int cmd)
{
	skill_autospell(sd,RFIFOW(fd,GETPACKETPOS(cmd,0)));

	return;
}

/*==========================================
 * �J�[�h�g�p
 *------------------------------------------
 */
static void clif_parse_UseCard(int fd,struct map_session_data *sd, int cmd)
{
	clif_use_card(sd,RFIFOW(fd,GETPACKETPOS(cmd,0))-2);

	return;
}

/*==========================================
 * �J�[�h�}�������I��
 *------------------------------------------
 */
static void clif_parse_InsertCard(int fd,struct map_session_data *sd, int cmd)
{
	int idx;

	nullpo_retv(sd);

	idx = RFIFOW(fd,GETPACKETPOS(cmd,0)) - 2;
	if (idx < 0 || idx >= MAX_INVENTORY)
		return;

	if (sd->npc_id != 0 && sd->npc_allowuseitem != 0 && sd->npc_allowuseitem != sd->status.inventory[idx].nameid)
		return;
	if (sd->state.store || sd->state.deal_mode != 0 || (sd->sc.opt1 > OPT1_NORMAL && sd->sc.opt1 < OPT1_STONECURSE_ING) || sd->state.storage_flag || sd->chatID || sd->state.mail_appending)
		return;
	if (unit_isdead(&sd->bl))
		return;

	if (sd->sc.data[SC_TRICKDEAD].timer != -1 ||	// ���񂾂ӂ�
	    sd->sc.data[SC_BLADESTOP].timer != -1 ||	// ���n���
	    sd->sc.data[SC_FORCEWALKING].timer != -1 ||	// �����ړ�
	    sd->sc.data[SC_BERSERK].timer != -1 ||	// �o�[�T�[�N
	    sd->sc.data[SC_WEDDING].timer != -1 ||	// �����ߑ�
	    sd->sc.data[SC_NOCHAT].timer != -1)		// ��b�֎~
		return;

	pc_insert_card(sd, idx, RFIFOW(fd,GETPACKETPOS(cmd,1))-2);

	return;
}

/*==========================================
 * 0193 �L����ID���O����
 *------------------------------------------
 */
static void clif_parse_SolveCharName(int fd,struct map_session_data *sd, int cmd)
{
	clif_solved_charname(sd, RFIFOL(fd,GETPACKETPOS(cmd,0)));

	return;
}

/*==========================================
 * 0197 /resetskill /resetstate
 *------------------------------------------
 */
static void clif_parse_ResetChar(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	if (battle_config.atc_gmonly == 0 ||
	    pc_isGM(sd) >= get_atcommand_level(AtCommand_ResetState)) {
		switch(RFIFOW(fd,GETPACKETPOS(cmd,0))){
		case 0:
			pc_resetstatus(sd, 0);
			break;
		case 1:
			pc_resetskill(sd, 0);
			break;
		}
	}

	return;
}

/*==========================================
 * 019c /lb (with GM name), /nlb, /mb (in blue)
 *------------------------------------------
 */
static void clif_parse_LGMmessage(int fd,struct map_session_data *sd, int cmd)
{
	int len;
	int message_size;

	nullpo_retv(sd);

	len = RFIFOW(fd,GETPACKETPOS(cmd,0));
	message_size = len - GETPACKETPOS(cmd,1);
	if (message_size <= 0)	// must have at least \0
		return;
	if (message_size > 255)	// too long
		return;

	// force \0 against hack
	RFIFOB(fd, len-1) = '\0';

	if (battle_config.atc_gmonly == 0 ||
	    pc_isGM(sd) >= get_atcommand_level(AtCommand_LocalBroadcast)) {
		WFIFOW(fd,0)=0x9a;
		WFIFOW(fd,2)=len;
		memcpy(WFIFOP(fd,4), RFIFOP(fd, GETPACKETPOS(cmd,1)), message_size);
		clif_send(WFIFOP(fd,0), len, &sd->bl, ALL_SAMEMAP);
	}

	return;
}

/*==========================================
 * �J�v���q�ɂ֓����
 *------------------------------------------
 */
static void clif_parse_MoveToKafra(int fd,struct map_session_data *sd, int cmd)
{
	int idx, amount;

	nullpo_retv(sd);

	if(sd->npc_id != 0 || sd->state.store || sd->state.deal_mode != 0 || sd->state.mail_appending || sd->sc.data[SC_BERSERK].timer != -1)
		return;

	idx    = RFIFOW(fd,GETPACKETPOS(cmd,0))-2;
	amount = RFIFOL(fd,GETPACKETPOS(cmd,1));

	if(sd->state.storage_flag==2)
		storage_guild_storageadd(sd, idx, amount);
	else if(sd->state.storage_flag==1)
		storage_storageadd(sd, idx, amount);

	return;
}

/*==========================================
 * �J�v���q�ɂ���o��
 *------------------------------------------
 */
static void clif_parse_MoveFromKafra(int fd,struct map_session_data *sd, int cmd)
{
	int idx, amount;

	nullpo_retv(sd);

	if(sd->npc_id != 0 || sd->state.store || sd->state.deal_mode != 0 || sd->state.mail_appending || sd->sc.data[SC_BERSERK].timer != -1)
		return;

	idx    = RFIFOW(fd,GETPACKETPOS(cmd,0))-1;
	amount = RFIFOL(fd,GETPACKETPOS(cmd,1));

	if(sd->state.storage_flag==2)
		storage_guild_storageget(sd, idx, amount);
	else if(sd->state.storage_flag==1)
		storage_storageget(sd, idx, amount);

	return;
}

/*==========================================
 * �J�v���q�ɂփJ�[�g��������
 *------------------------------------------
 */
static void clif_parse_MoveToKafraFromCart(int fd,struct map_session_data *sd, int cmd)
{
	int idx, amount;

	nullpo_retv(sd);

	if(sd->npc_id != 0 || sd->state.store || sd->state.deal_mode != 0 || sd->state.mail_appending ||
	   pc_iscarton(sd) == 0 || sd->sc.data[SC_BERSERK].timer != -1)
		return;

	idx    = RFIFOW(fd,GETPACKETPOS(cmd,0))-2;
	amount = RFIFOL(fd,GETPACKETPOS(cmd,1));

	if(sd->state.storage_flag==2)
		storage_guild_storageaddfromcart(sd, idx, amount);
	else if(sd->state.storage_flag==1)
		storage_storageaddfromcart(sd, idx, amount);

	return;
}

/*==========================================
 * �J�v���q�ɂ���J�[�g�֏o��
 *------------------------------------------
 */
static void clif_parse_MoveFromKafraToCart(int fd,struct map_session_data *sd, int cmd)
{
	int idx, amount;

	nullpo_retv(sd);

	if(sd->npc_id != 0 || sd->state.store || sd->state.deal_mode != 0 || sd->state.mail_appending ||
	   pc_iscarton(sd) == 0 || sd->sc.data[SC_BERSERK].timer != -1)
		return;

	idx    = RFIFOW(fd,GETPACKETPOS(cmd,0))-1;
	amount = RFIFOL(fd,GETPACKETPOS(cmd,1));

	if(sd->state.storage_flag==2)
		storage_guild_storagegettocart(sd, idx, amount);
	else if(sd->state.storage_flag==1)
		storage_storagegettocart(sd, idx, amount);

	return;
}

/*==========================================
 * �J�v���q�ɂ����
 *------------------------------------------
 */
static void clif_parse_CloseKafra(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	if(sd->state.storage_flag==2) {
		storage_guild_storageclose(sd);
	} else if(sd->state.storage_flag==1) {
		storage_storageclose(sd);
	} else {
		sd->state.storage_flag = 0;
		clif_storageclose(sd);
	}

	return;
}

/*==========================================
 * �p�[�e�B�����
 *------------------------------------------
 */
static void clif_parse_CreateParty(int fd,struct map_session_data *sd, int cmd)
{
	if(battle_config.basic_skill_check == 0 || pc_checkskill(sd,NV_BASIC) >= 7 || pc_checkskill(sd,SU_BASIC_SKILL))
		party_create(sd,RFIFOP(fd,GETPACKETPOS(cmd,0)),0,0);
	else
		clif_skill_fail(sd,NV_BASIC,SKILLFAIL_LEVEL,4,0);

	return;
}

/*==========================================
 * �p�[�e�B�����2
 *------------------------------------------
 */
static void clif_parse_CreateParty2(int fd,struct map_session_data *sd, int cmd)
{
	int item1 = (int)RFIFOB(fd,GETPACKETPOS(cmd,1));
	int item2 = (int)RFIFOB(fd,GETPACKETPOS(cmd,2));

	if(battle_config.basic_skill_check == 0 || pc_checkskill(sd,NV_BASIC) >= 7 || pc_checkskill(sd,SU_BASIC_SKILL))
		party_create(sd,RFIFOP(fd,GETPACKETPOS(cmd,0)),item1,item2);
	else
		clif_skill_fail(sd,NV_BASIC,SKILLFAIL_LEVEL,4,0);

	return;
}

/*==========================================
 * �p�[�e�B�Ɋ��U
 *------------------------------------------
 */
static void clif_parse_PartyInvite(int fd,struct map_session_data *sd, int cmd)
{
	struct map_session_data *tsd = map_id2sd(RFIFOL(fd,GETPACKETPOS(cmd,0)));

	party_invite(sd,tsd);

	return;
}

/*==========================================
 * �p�[�e�B�Ɋ��U2
 *------------------------------------------
 */
static void clif_parse_PartyInvite2(int fd,struct map_session_data *sd, int cmd)
{
	char *name = (char *)RFIFOP(fd,GETPACKETPOS(cmd,0));
	struct map_session_data *tsd = map_nick2sd(name);

	party_invite(sd,tsd);

	return;
}

/*==========================================
 * �p�[�e�B���U�ԓ�
 *------------------------------------------
 */
static void clif_parse_ReplyPartyInvite(int fd,struct map_session_data *sd, int cmd)
{
	if(battle_config.basic_skill_check == 0 || pc_checkskill(sd,NV_BASIC) >= 5 || pc_checkskill(sd,SU_BASIC_SKILL)) {
		party_reply_invite(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)),RFIFOL(fd,GETPACKETPOS(cmd,1)));
	} else {
		party_reply_invite(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)),-1);
		clif_skill_fail(sd,NV_BASIC,SKILLFAIL_LEVEL,4,0);
	}

	return;
}

/*==========================================
 * �p�[�e�B���U�ԓ�2
 *------------------------------------------
 */
static void clif_parse_ReplyPartyInvite2(int fd,struct map_session_data *sd, int cmd)
{
	if(battle_config.basic_skill_check == 0 || pc_checkskill(sd,NV_BASIC) >= 5 || pc_checkskill(sd,SU_BASIC_SKILL)) {
		party_reply_invite(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)),RFIFOB(fd,GETPACKETPOS(cmd,1)));
	} else {
		party_reply_invite(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)),-1);
		clif_skill_fail(sd,NV_BASIC,SKILLFAIL_LEVEL,8,0);
	}

	return;
}

/*==========================================
 * /accept, /refuse
 *------------------------------------------
 */
static void clif_parse_RefusePartyInvite(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	sd->status.refuse_partyinvite = ( RFIFOB(fd,GETPACKETPOS(cmd,0)) ) ? 1 : 0;

	WFIFOW(fd,0) = 0x2c9;
	WFIFOB(fd,2) = (unsigned char)sd->status.refuse_partyinvite;
	WFIFOSET(fd,packet_db[0x2c9].len);

	return;
}

/*==========================================
 * �p�[�e�B�E�ޗv��
 *------------------------------------------
 */
static void clif_parse_LeaveParty(int fd,struct map_session_data *sd, int cmd)
{
	party_leave(sd);

	return;
}

/*==========================================
 * �p�[�e�B�����v��
 *------------------------------------------
 */
static void clif_parse_RemovePartyMember(int fd,struct map_session_data *sd, int cmd)
{
	party_removemember(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)),RFIFOP(fd,GETPACKETPOS(cmd,1)));

	return;
}

/*==========================================
 * �p�[�e�B�ݒ�ύX�v��
 *------------------------------------------
 */
static void clif_parse_PartyChangeOption(int fd,struct map_session_data *sd, int cmd)
{
	party_changeoption(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)),-1);

	return;
}

/*==========================================
 * �p�[�e�B�ݒ�ύX�v��2
 *------------------------------------------
 */
static void clif_parse_PartyChangeOption2(int fd,struct map_session_data *sd, int cmd)
{
	int item = (int)RFIFOB(fd,GETPACKETPOS(cmd,1));
	int item2 = (int)RFIFOB(fd,GETPACKETPOS(cmd,1)+1);

	party_changeoption(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)),(item ? 1 : 0) | (item2 ? 2 : 0));

	return;
}

/*==========================================
 * �p�[�e�B���b�Z�[�W���M�v��
 *------------------------------------------
 */
static void clif_parse_PartyMessage(int fd,struct map_session_data *sd, int cmd)
{
	char *message;
	int message_size;

	nullpo_retv(sd);

	message = (char *)RFIFOP(fd, GETPACKETPOS(cmd,1));
	message_size = RFIFOW(fd, GETPACKETPOS(cmd,0)) - GETPACKETPOS(cmd,1);

	if (message_size <= 0)	// against hack
		return;
	if (message_size > 255)	// too long
		return;

	// normal client send NULL -> force it (against hacker)
#if PACKETVER >= 20151029
	message[message_size] = '\0';
	message_size++;
#else
	message[message_size - 1] = '\0';
#endif

	if (battle_config.check_player_name_party_msg) {
		// structure of message: <player_name> : <message>
		char *p_message;
		int name_length;
		name_length = (int)strlen(sd->status.name);
		if (name_length > 24)
			name_length = 24;
		p_message = message + name_length;
		if (message_size < name_length + 3 + 1 || // check void message (at least 1 char) -> normal client refuse to send void message
		    memcmp(message, sd->status.name, name_length) != 0 || // check player name
		    *p_message != ' ' || *(p_message + 1) != ':' || *(p_message + 2) != ' ') { // check ' : '
			// add here a message if necessary
			return;
		}
	}

	if (is_atcommand(fd, sd, message) != AtCommand_None)
		return;

	// �o�[�T�[�N�A�`���b�g�֎~��ԂȂ��b�s��
	if(sd->sc.data[SC_BERSERK].timer != -1 || sd->sc.data[SC_NOCHAT].timer != -1 || sd->sc.data[SC_DEEP_SLEEP].timer != -1)
		return;

	party_send_message(sd, message, message_size);

	return;
}

/*==========================================
 * �I�X��
 *------------------------------------------
 */
static void clif_parse_CloseVending(int fd,struct map_session_data *sd, int cmd)
{
	vending_closevending(sd);

	return;
}

/*==========================================
 * �I�X�A�C�e�����X�g�v��
 *------------------------------------------
 */
static void clif_parse_VendingListReq(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	if(sd->state.store)
		return;

	vending_vendinglistreq(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)));
	if(sd->npc_id)
		npc_event_dequeue(sd);

	return;
}

/*==========================================
 * �I�X�A�C�e���w��
 *------------------------------------------
 */
static void clif_parse_PurchaseReq(int fd,struct map_session_data *sd, int cmd)
{
	short len = RFIFOW(fd,GETPACKETPOS(cmd,0)) - 8;
	int account_id = RFIFOL(fd,GETPACKETPOS(cmd,1));
	const unsigned char *data = RFIFOP(fd,GETPACKETPOS(cmd,2));

	if(sd->state.store)
		return;

	vending_purchasereq(sd, ( len <= 0 ) ? 0 : len/4, account_id, sd->vender_id, data);

	return;
}

/*==========================================
 * �I�X�A�C�e���w��2
 *------------------------------------------
 */
static void clif_parse_PurchaseReq2(int fd,struct map_session_data *sd, int cmd)
{
	short len = RFIFOW(fd,GETPACKETPOS(cmd,0)) - 12;
	int account_id =  RFIFOL(fd,GETPACKETPOS(cmd,1));
	unsigned int vender_id = RFIFOL(fd,GETPACKETPOS(cmd,2));
	const unsigned char *data = RFIFOP(fd,GETPACKETPOS(cmd,3));

	if(sd->state.store)
		return;

	vending_purchasereq(sd, ( len <= 0 ) ? 0 : len/4, account_id, vender_id, data);

	return;
}

/*==========================================
 * �I�X�J��
 *------------------------------------------
 */
static void clif_parse_OpenVending(int fd,struct map_session_data *sd, int cmd)
{
	short len = RFIFOW(fd,GETPACKETPOS(cmd,0)) - 85;
	char *shop_title = RFIFOP(fd,GETPACKETPOS(cmd,1));
	bool is_open = ( RFIFOB(fd,GETPACKETPOS(cmd,2)) ) ? true : false;
	const unsigned char *data = RFIFOP(fd,GETPACKETPOS(cmd,3));

	// normal client send NULL -> force it (against hacker)
	shop_title[79] = '\0';

	vending_openvending(sd, ( len <= 0 ) ? 0 : len/8, shop_title, is_open, data);

	return;
}

/*==========================================
 * �M���h�����
 *------------------------------------------
 */
static void clif_parse_CreateGuild(int fd,struct map_session_data *sd, int cmd)
{
	char *name = RFIFOP(fd,GETPACKETPOS(cmd,0));

	// force NULL in guild name (hacker or incorrect at command)
	// normal client doesn't send more than 23 char, and it always sends NULL
	name[23] = '\0';

	guild_create(sd, name);

	return;
}

/*==========================================
 * �M���h�}�X�^�[���ǂ����m�F
 *------------------------------------------
 */
static void clif_parse_GuildCheckMaster(int fd,struct map_session_data *sd, int cmd)
{
	clif_guild_masterormember(sd);

	return;
}

/*==========================================
 * �M���h���v��
 *------------------------------------------
 */
static void clif_parse_GuildRequestInfo(int fd,struct map_session_data *sd, int cmd)
{
	struct guild *g;

	nullpo_retv(sd);

	// only a guild member can ask for guild info
	if(sd->status.guild_id == 0 || (g = guild_search(sd->status.guild_id)) == NULL)
		return;

	switch(RFIFOL(fd,GETPACKETPOS(cmd,0))) {
	case 0:	// �M���h��{���A�����G�Ώ��
		clif_guild_basicinfo(sd, g);
		clif_guild_allianceinfo(sd, g);
		clif_guild_emblem(sd, g);
		break;
	case 1:	// �����o�[���X�g�A��E�����X�g
		clif_guild_positionnamelist(sd, g);
		clif_guild_memberlist(sd, g);
		break;
	case 2:	// ��E�����X�g�A��E��񃊃X�g
		clif_guild_positionnamelist(sd, g);
		clif_guild_positioninfolist(sd, g);
		break;
	case 3:	// �X�L�����X�g
		clif_guild_skillinfo(sd, g);
		break;
	case 4:	// �Ǖ����X�g
		clif_guild_explusionlist(sd, g);
		break;
	default:
		if(battle_config.error_log)
			printf("clif: guild request info: unknown type %d\n", RFIFOL(fd,GETPACKETPOS(cmd,0)));
	}

	return;
}

/*==========================================
 * �M���h��E�ύX
 *------------------------------------------
 */
static void clif_parse_GuildChangePositionInfo(int fd,struct map_session_data *sd, int cmd)
{
	struct guild *g;
	int i, n, len;

	nullpo_retv(sd);

	// only guild master can change position.
	if (sd->status.guild_id == 0 || (g = guild_search(sd->status.guild_id)) == NULL)
		return;
	if (strcmp(sd->status.name, g->master))
		return;

	len = GETPACKETPOS(cmd,1);
	n   = (RFIFOW(fd,GETPACKETPOS(cmd,0)) - len) / 40;
	if(n <= 0)
		return;

	for(i = 0; i < n; i++) {	// {<index>.l <mode>.l <index>.l <exp_mode>.l <nickname>.24B}.40B*
		guild_change_position(sd->status.guild_id, RFIFOL(fd,len), RFIFOL(fd,len+4), RFIFOL(fd,len+12), RFIFOP(fd,len+16));
		len += 40;
	}

	return;
}

/*==========================================
 * �M���h�����o��E�ύX
 *------------------------------------------
 */
static void clif_parse_GuildChangeMemberPosition(int fd,struct map_session_data *sd, int cmd)
{
	struct guild *g;
	int i, n, len;

	nullpo_retv(sd);

	// only guild master can change a member position
	if (sd->status.guild_id == 0 || (g = guild_search(sd->status.guild_id)) == NULL)
		return;
	if (strcmp(sd->status.name, g->master))
		return;

	len = GETPACKETPOS(cmd,1);
	n   = (RFIFOW(fd,GETPACKETPOS(cmd,0)) - len) / 12;
	if(n <= 0)
		return;

	for(i = 0; i < n; i++) {	// {<accID>.l <charaID>.l <index>.l}.12B*
		guild_change_memberposition(sd->status.guild_id, RFIFOL(fd,len), RFIFOL(fd,len+4), RFIFOL(fd,len+8));
		len += 12;
	}

	return;
}

/*==========================================
 * �M���h�G���u�����v��
 *------------------------------------------
 */
static void clif_parse_GuildRequestEmblem(int fd,struct map_session_data *sd, int cmd)
{
	struct guild *g = guild_search(RFIFOL(fd,GETPACKETPOS(cmd,0)));

	if(g)
		clif_guild_emblem(sd,g);

	return;
}

/*==========================================
 * �M���h�G���u�����ύX
 *------------------------------------------
 */
static void clif_parse_GuildChangeEmblem(int fd,struct map_session_data *sd, int cmd)
{
	int offset;
	unsigned int len;
	struct guild *g;

	// only guild master can change emblem.
	if (sd->status.guild_id == 0 || (g = guild_search(sd->status.guild_id)) == NULL)
		return;
	if (strcmp(sd->status.name, g->master))
		return;

	offset = GETPACKETPOS(cmd,1);
	len    = RFIFOW(fd,GETPACKETPOS(cmd,0)) - offset;

	guild_change_emblem(sd->status.guild_id,len,RFIFOP(fd,offset));
}

/*==========================================
 * �M���h�G���u�����ύX
 *------------------------------------------
 */
static void clif_parse_GuildChangeEmblem2(int fd,struct map_session_data *sd, int cmd)
{
	int guild_id = RFIFOL(fd,GETPACKETPOS(cmd,0));
	int version  = RFIFOL(fd,GETPACKETPOS(cmd,1));
	struct guild *g;
	unsigned char buf[14];

	nullpo_retv(sd);

	// only guild master can change emblem.
	if (sd->status.guild_id == 0 || sd->status.guild_id != guild_id || (g = guild_search(sd->status.guild_id)) == NULL)
		return;
	if (strcmp(sd->status.name, g->master))
		return;

	WBUFW(buf, 0)=0xb47;
	WBUFL(buf, 2)=sd->status.guild_id;
	WBUFL(buf, 6)=version;
	WBUFL(buf,10)=0;

	clif_send(buf,packet_db[0xb47].len,&sd->bl,GUILD);

	return;
}

/*==========================================
 * �M���h���m�ύX
 *------------------------------------------
 */
static void clif_parse_GuildChangeNotice(int fd,struct map_session_data *sd, int cmd)
{
	struct guild *g;
	int guild_id;

	nullpo_retv(sd);

	// only guild master can change guild message
	if (sd->status.guild_id == 0 || (g = guild_search(sd->status.guild_id)) == NULL)
		return;
	if (strcmp(sd->status.name, g->master))
		return;

	// you can not change message of another guild!
	guild_id = RFIFOL(fd,GETPACKETPOS(cmd,0));
	if (sd->status.guild_id != RFIFOL(fd,GETPACKETPOS(cmd,0)))
		return;

	// client sends NULL -> force it (angainst hack)
	RFIFOB(fd, GETPACKETPOS(cmd,1) + 59)  = '\0';
	RFIFOB(fd, GETPACKETPOS(cmd,2) + 119) = '\0';

	guild_change_notice(guild_id, RFIFOP(fd,GETPACKETPOS(cmd,1)), RFIFOP(fd,GETPACKETPOS(cmd,2)));

	return;
}

/*==========================================
 * �M���h���U
 *------------------------------------------
 */
static void clif_parse_GuildInvite(int fd,struct map_session_data *sd, int cmd) // S 0x0168 <TargetAccID>.l <sourceAccID>.l <myCharactorID>.l
{
	nullpo_retv(sd);

	// check to be sure that is original packet (not need to have these values after)
	if (RFIFOL(fd,GETPACKETPOS(cmd,1)) != sd->status.account_id ||
	    RFIFOL(fd,GETPACKETPOS(cmd,2)) != sd->status.char_id)
		return;

	guild_invite(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)));

	return;
}

/*==========================================
 * �M���h���U�ԐM
 *------------------------------------------
 */
static void clif_parse_GuildReplyInvite(int fd,struct map_session_data *sd, int cmd)
{
	guild_reply_invite(sd, RFIFOL(fd,GETPACKETPOS(cmd,0)), (unsigned char)RFIFOL(fd,GETPACKETPOS(cmd,1)));

	return;
}

/*==========================================
 * �M���h�E��
 *------------------------------------------
 */
static void clif_parse_GuildLeave(int fd,struct map_session_data *sd, int cmd)
{
	// client sends NULL -> force it (against hack)
	RFIFOB(fd, GETPACKETPOS(cmd,3) + 39) = '\0';

	guild_leave(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)),RFIFOL(fd,GETPACKETPOS(cmd,1)),RFIFOL(fd,GETPACKETPOS(cmd,2)),RFIFOP(fd,GETPACKETPOS(cmd,3)));

	return;
}

/*==========================================
 * �M���h�Ǖ�
 *------------------------------------------
 */
static void clif_parse_GuildExplusion(int fd,struct map_session_data *sd, int cmd)
{
	// client sends NULL -> force it (against hack)
	RFIFOB(fd, GETPACKETPOS(cmd,3) + 39) = '\0';

	guild_explusion(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)),RFIFOL(fd,GETPACKETPOS(cmd,1)),RFIFOL(fd,GETPACKETPOS(cmd,2)),RFIFOP(fd,GETPACKETPOS(cmd,3)));

	return;
}

/*==========================================
 * �M���h��b
 *------------------------------------------
 */
static void clif_parse_GuildMessage(int fd,struct map_session_data *sd, int cmd)
{
	char *message;
	int message_size;

	nullpo_retv(sd);

	message = (char *)RFIFOP(fd, GETPACKETPOS(cmd,1));
	message_size = RFIFOW(fd, GETPACKETPOS(cmd,0)) - GETPACKETPOS(cmd,1);

	if (message_size <= 0)	// against hack
		return;
	if (message_size > 255)	// too long
		return;

	// normal client send NULL -> force it (against hacker)
#if PACKETVER >= 20151029
	message[message_size] = '\0';
	message_size++;
#else
	message[message_size - 1] = '\0';
#endif

	if (battle_config.check_player_name_guild_msg) {
		// structure of message: <player_name> : <message>
		char *p_message;
		int name_length;
		name_length = (int)strlen(sd->status.name);
		if (name_length > 24)
			name_length = 24;
		p_message = message + name_length;
		if (message_size < name_length + 3 + 1 || // check void message (at least 1 char) -> normal client refuse to send void message
		    memcmp(message, sd->status.name, name_length) != 0 || // check player name
		    *p_message != ' ' || *(p_message + 1) != ':' || *(p_message + 2) != ' ') { // check ' : '
			// add here a message if necessary
			return;
		}
	}

	if (is_atcommand(fd, sd, message) != AtCommand_None)
		return;

	// �o�[�T�[�N�A�`���b�g�֎~��ԂȂ��b�s��
	if (sd->sc.data[SC_BERSERK].timer != -1 || sd->sc.data[SC_NOCHAT].timer != -1 || sd->sc.data[SC_DEEP_SLEEP].timer != -1)
		return;

	guild_send_message(sd, message, message_size);

	return;
}

/*==========================================
 * �M���h�����v��
 *------------------------------------------
 */
static void clif_parse_GuildRequestAlliance(int fd,struct map_session_data *sd, int cmd)
{
	guild_reqalliance(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)));
}

/*==========================================
 * �M���h�����v���ԐM
 *------------------------------------------
 */
static void clif_parse_GuildReplyAlliance(int fd,struct map_session_data *sd, int cmd)
{
	guild_reply_reqalliance(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)),RFIFOL(fd,GETPACKETPOS(cmd,1)));
}

/*==========================================
 * �M���h�֌W����
 *------------------------------------------
 */
static void clif_parse_GuildDelAlliance(int fd,struct map_session_data *sd, int cmd)
{
	guild_delalliance(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)),RFIFOL(fd,GETPACKETPOS(cmd,1)));
}

/*==========================================
 * �M���h�G��
 *------------------------------------------
 */
static void clif_parse_GuildOpposition(int fd,struct map_session_data *sd, int cmd)
{
	guild_opposition(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)));
}

/*==========================================
 * �M���h���U
 *------------------------------------------
 */
static void clif_parse_GuildBreak(int fd,struct map_session_data *sd, int cmd)
{
	guild_break(sd,RFIFOP(fd,GETPACKETPOS(cmd,0)));
}

/*==========================================
 * �M���h�����o�[���i���g�p�j
 *------------------------------------------
 */
static void clif_parse_GuildMemberInfo(int fd,struct map_session_data *sd, int cmd)
{
	//int account_id = GETPACKETPOS(cmd,0);
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_PetMenu(int fd,struct map_session_data *sd, int cmd)
{
	pet_menu(sd,RFIFOB(fd,GETPACKETPOS(cmd,0)));
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_CatchPet(int fd,struct map_session_data *sd, int cmd)
{
	pet_catch_process2(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)));
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_SelectEgg(int fd,struct map_session_data *sd, int cmd)
{
	pet_select_egg(sd,(short)(RFIFOW(fd,GETPACKETPOS(cmd,0))-2));
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_SendEmotion(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	if(sd->pd)
		clif_pet_emotion(sd->pd,RFIFOL(fd,GETPACKETPOS(cmd,0)));
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_ChangePetName(int fd,struct map_session_data *sd, int cmd)
{
	pet_change_name(sd,RFIFOP(fd,GETPACKETPOS(cmd,0)));
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_GMKick(int fd,struct map_session_data *sd, int cmd)
{
	int tid = RFIFOL(fd,GETPACKETPOS(cmd,0));

	nullpo_retv(sd);

	if(pc_isGM(sd) >= get_atcommand_level(AtCommand_Kick)) {
		struct block_list *target = map_id2bl(tid);
		if(target) {
			if(target->type == BL_PC) {
				struct map_session_data *tsd = (struct map_session_data *)target;
				if(pc_isGM(sd) > pc_isGM(tsd))
					clif_GM_kick(sd,tsd,1);
				else
					clif_GM_kickack(sd,0);
			} else if(target->type == BL_MOB) {
				struct mob_data *md = (struct mob_data *)target;
				sd->state.attack_type = 0;
				mob_damage(&sd->bl,md,md->hp,2);
			} else {
				clif_GM_kickack(sd,0);
			}
		} else {
			clif_GM_kickack(sd,0);
		}
	}
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_GMHide(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	if(pc_isGM(sd) >= get_atcommand_level(AtCommand_Hide)) {
		if(sd->sc.option&OPTION_SPECIALHIDING) {
			sd->sc.option &= ~OPTION_SPECIALHIDING;
			clif_displaymessage(fd, msg_txt(10)); // invisible off!
		} else {
			sd->sc.option |= OPTION_SPECIALHIDING;
			clif_displaymessage(fd, msg_txt(11)); // invisible!
		}
		clif_changeoption(&sd->bl);
	}
}

/*==========================================
 * GM�ɂ��`���b�g�֎~���ԕt�^
 *------------------------------------------
 */
static void clif_parse_GMReqNoChat(int fd,struct map_session_data *sd, int cmd)
{
	int tid = RFIFOL(fd,GETPACKETPOS(cmd,0));
	int type = RFIFOB(fd,GETPACKETPOS(cmd,1));
	int limit = RFIFOW(fd,GETPACKETPOS(cmd,2));
	struct map_session_data *dstsd = NULL;

	nullpo_retv(sd);

	if(battle_config.nomanner_mode)
		return;

	// �^�C���M���͐ԃG���ɂȂ�Ȃ�
	if(sd->sc.data[SC_RUN].timer != -1)
		return;
	// �O�̂��ߋ����ړ�����
	if(sd->sc.data[SC_FORCEWALKING].timer != -1)
		return;

	dstsd = map_id2sd(tid);
	if(dstsd == NULL)
		return;

	if( (type == 2 && !pc_isGM(sd) && sd->bl.id == tid) ||
	    (pc_isGM(sd) > pc_isGM(dstsd) && pc_isGM(sd) >= battle_config.gm_nomanner_lv) )
	{
		int dstfd = dstsd->fd;

		WFIFOW(dstfd,0)=0x14b;
		WFIFOB(dstfd,2)=(type==2)? 1: type;
		memcpy(WFIFOP(dstfd,3),sd->status.name,24);
		WFIFOSET(dstfd,packet_db[0x14b].len);

		if(!battle_config.nomanner_mode)
			dstsd->status.manner += (type == 0)? limit: -limit;
		if(dstsd->status.manner < 0) {
			status_change_start(&dstsd->bl,SC_NOCHAT,0,0,0,0,0,0);
		} else {
			dstsd->status.manner = 0;
			status_change_end(&dstsd->bl,SC_NOCHAT,-1);
		}
	}

	return;
}

/*==========================================
 * GM�ɂ��`���b�g�֎~���ԎQ�Ɓi�H�j
 *------------------------------------------
 */
static void clif_parse_GMReqNoChatCount(int fd,struct map_session_data *sd, int cmd)
{
	int tid = RFIFOL(fd,GETPACKETPOS(cmd,0));

	WFIFOW(fd,0)=0x1e0;
	WFIFOL(fd,2)=tid;
	snprintf(WFIFOP(fd,6),24,"%d",tid);
	WFIFOSET(fd,packet_db[0x1e0].len);

	return;
}

/*==========================================
 * /doridori�ɂ��SPR2�{
 *------------------------------------------
 */
static void clif_parse_doridori(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	if(sd->s_class.job == PC_JOB_SNV || sd->s_class.job == PC_JOB_ESNV) {
		sd->state.sn_doridori = 1;
	}
	else if(sd->state.taekwonrest && sd->s_class.job >= PC_JOB_TK && sd->s_class.job <= PC_JOB_SL) {
		sd->state.tk_doridori_hp = 1;
		sd->state.tk_doridori_sp = 1;
	}

	return;
}

/*==========================================
 * �X�p�m�r�̔����g��
 *------------------------------------------
 */
static void clif_parse_sn_explosionspirits(int fd,struct map_session_data *sd, int cmd)
{
	atn_bignumber next;
	int rate = 0;

	nullpo_retv(sd);

	if(sd->s_class.job != PC_JOB_SNV && sd->s_class.job != PC_JOB_ESNV)
		return;

	next = pc_nextbaseexp(sd);
	if( (next > 0 && (rate = (int)((atn_bignumber)sd->status.base_exp * 1000 / next)) > 0 && rate % 100 == 0) ||
	    (next <= 0 && sd->status.base_exp >= battle_config.snovice_maxexp_border) )
	{
		if(battle_config.etc_log) {
			printf(
				"SuperNovice explosionspirits!! %d %d %" BIGNUMCODE " %d\n",
				sd->bl.id, sd->s_class.job, sd->status.base_exp, rate
			);
		}
		clif_skill_nodamage(&sd->bl,&sd->bl,MO_EXPLOSIONSPIRITS,5,1);
		status_change_start(&sd->bl,SC_EXPLOSIONSPIRITS,5,0,0,0,skill_get_time(MO_EXPLOSIONSPIRITS,5),0);
	}

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static int pstrcmp(const void *a, const void *b)
{
	return strcmp((char *)a, (char *)b);
}

/*==========================================
 * Wis���ۋ��� /ex /in
 *------------------------------------------
 */
static void clif_parse_wisexin(int fd,struct map_session_data *sd, int cmd)
{
	char *name = RFIFOP(fd,GETPACKETPOS(cmd,0));
	int type   = RFIFOB(fd,GETPACKETPOS(cmd,1));
	int i;
	unsigned char flag = 1;

	nullpo_retv(sd);

	qsort(sd->wis_refusal[0], MAX_WIS_REFUSAL, sizeof(sd->wis_refusal[0]), pstrcmp);
	if(type == 0) {	// ex
		for(i=0; i<MAX_WIS_REFUSAL; i++) {	// ���łɒǉ�����Ă���Ή������Ȃ�
			if(strcmp(sd->wis_refusal[i], name) == 0) {
				flag = 0;
				clif_wisexin(sd, type, flag);
				return;
			}
		}
		for(i=0; i<MAX_WIS_REFUSAL; i++) {	// ��̋��ۃ��X�g�ɒǉ�(�Ƃ肠����)
			if(sd->wis_refusal[i][0] == 0) {
				memcpy(sd->wis_refusal[i], name, 24);
				sd->wis_refusal[i][23] = '\0';
				flag = 0;
				break;
			}
		}
		if(flag == 1) {
			memcpy(sd->wis_refusal[MAX_WIS_REFUSAL-1], name, 24);
			sd->wis_refusal[MAX_WIS_REFUSAL-1][23] = '\0';
			flag = 0;
		}
	} else {		// in
		for(i=0; i<MAX_WIS_REFUSAL; i++) {	// ��v���鋑�ۃ��X�g�����
			if(strcmp(sd->wis_refusal[i], name) == 0) {
				sd->wis_refusal[i][0] = 0;
				flag = 0;
			}
		}
		sd->state.wis_all = 0;
	}
	clif_wisexin(sd, type, flag);

	return;
}

/*==========================================
 * Wis���ۃ��X�g
 *------------------------------------------
 */
static void clif_parse_wisexlist(int fd,struct map_session_data *sd, int cmd)
{
	int i, j = 0;

	nullpo_retv(sd);

	qsort(sd->wis_refusal[0], MAX_WIS_REFUSAL, sizeof(sd->wis_refusal[0]), pstrcmp);

	WFIFOW(fd,0)=0xd4;
	for(i=0; i<MAX_WIS_REFUSAL; i++) {
		if(sd->wis_refusal[i][0] != 0) {
			memcpy(WFIFOP(fd,4+j*24),sd->wis_refusal[i],24);
			j++;
		}
	}
	WFIFOW(fd,2) = 4+j*24;
	WFIFOSET(fd,WFIFOW(fd,2));

	if(j >= MAX_WIS_REFUSAL)	// ���^���Ȃ�Ō��1������
		sd->wis_refusal[MAX_WIS_REFUSAL-1][0] = 0;

	return;
}

/*==========================================
 * Wis�S���ۋ��� /exall /inall
 *------------------------------------------
 */
static void clif_parse_wisall(int fd,struct map_session_data *sd, int cmd)
{
	int type = RFIFOB(fd,GETPACKETPOS(cmd,0));

	nullpo_retv(sd);

	if(type==0) {	// exall
		sd->state.wis_all = 1;
	} else {	// inall
		int i;
		for(i=0;i<MAX_WIS_REFUSAL;i++)	// ���ۃ��X�g�����
			sd->wis_refusal[i][0]=0;
		sd->state.wis_all = 0;
	}
	clif_wisall(sd, type, 0);
}

/*==========================================
 * GM�R�}���h /killall
 *------------------------------------------
 */
static void clif_parse_GMkillall(int fd,struct map_session_data *sd, int cmd)
{
	char command[40];

	nullpo_retv(sd);

	sprintf(command, "%ckickall", GM_Symbol());
	is_atcommand_sub(fd, sd, command, 0);

	return;
}

/*==========================================
 * GM�R�}���h /summon
 *------------------------------------------
 */
static void clif_parse_GMsummon(int fd,struct map_session_data *sd, int cmd)
{
	char command[64];

	nullpo_retv(sd);

	sprintf(command, "%csummon ", GM_Symbol());
	strncat(command, RFIFOP(fd,GETPACKETPOS(cmd,0)), 24);
	is_atcommand_sub(fd, sd, command, 0);

	return;
}

/*==========================================
 * GM�R�}���h /item /monster
 *------------------------------------------
 */
static void clif_parse_GMitemmonster( int fd, struct map_session_data *sd, int cmd )
{
	char command[64];

	nullpo_retv(sd);

	sprintf(command, "%cim ", GM_Symbol());
	strncat(command, RFIFOP(fd, GETPACKETPOS(cmd, 0)), 24);
	is_atcommand_sub(fd, sd, command, 0);

	return;
}

/*==========================================
 * GM�R�}���h /shift
 *------------------------------------------
 */
static void clif_parse_GMshift(int fd,struct map_session_data *sd, int cmd)
{
	char command[64];

	nullpo_retv(sd);

	sprintf(command, "%cjumpto ", GM_Symbol());
	strncat(command, RFIFOP(fd,GETPACKETPOS(cmd,0)), 24);
	is_atcommand_sub(fd, sd, command, 0);

	return;
}

/*==========================================
 * GM�R�}���h /recall
 *------------------------------------------
 */
static void clif_parse_GMrecall(int fd,struct map_session_data *sd, int cmd)
{
	char command[64];

	nullpo_retv(sd);

	sprintf(command, "%crecall ", GM_Symbol());
	strncat(command, RFIFOP(fd,GETPACKETPOS(cmd,0)), 24);
	is_atcommand_sub(fd, sd, command, 0);

	return;
}

/*==========================================
 * GM�R�}���h /changemaptype
 *------------------------------------------
 */
static void clif_parse_GMchangemaptype(int fd,struct map_session_data *sd, int cmd)
{
	int x,y,type;
	char command[64];

	nullpo_retv(sd);

	x    = RFIFOW(fd, GETPACKETPOS(cmd,0));
	y    = RFIFOW(fd, GETPACKETPOS(cmd,1));
	type = RFIFOW(fd, GETPACKETPOS(cmd,2));	// 0��1�̂�

	sprintf(command, "%cchangemaptype %d %d %d", GM_Symbol(), x, y, type&1);
	is_atcommand_sub(fd, sd, command, 0);

	return;
}

/*==========================================
 * GM�R�}���h /rc
 *------------------------------------------
 */
static void clif_parse_GMrc(int fd,struct map_session_data *sd, int cmd)
{
	char command[64];

	sprintf(command, "%cmannerpoint %d ", GM_Symbol(), 60);
	strncat(command, RFIFOP(fd, GETPACKETPOS(cmd,0)), 24);
	is_atcommand_sub(fd, sd, command, 0);

	return;
}

/*==========================================
 * GM�R�}���h /check
 *------------------------------------------
 */
static void clif_parse_GMcheck(int fd,struct map_session_data *sd, int cmd)
{
	char *name;
	struct map_session_data *pl_sd;

	name = (char *)RFIFOP(fd, GETPACKETPOS(cmd,0));
	name[23] = '\0';	// force \0 terminal

	pl_sd = map_nick2sd(name);
	if(pl_sd)
		clif_check(fd, pl_sd);

	return;
}

/*==========================================
 * GM�R�}���h /�\䱃�
 *------------------------------------------
 */
static void clif_parse_GMcharge(int fd,struct map_session_data *sd, int cmd)
{
	// ���ʕs��
	return;
}

/*==========================================
 * �F�B���X�g�ǉ��v��
 *------------------------------------------
 */
static void clif_parse_FriendAddRequest(int fd,struct map_session_data *sd, int cmd)
{
	friend_add_request(sd, RFIFOP(fd,GETPACKETPOS(cmd,0)));
	return;
}

/*==========================================
 * �F�B���X�g�ǉ��v���ԓ�
 *------------------------------------------
 */
static void clif_parse_FriendAddReply(int fd,struct map_session_data *sd, int cmd)
{
	friend_add_reply(sd, RFIFOL(fd,GETPACKETPOS(cmd,0)), RFIFOL(fd,GETPACKETPOS(cmd,1)), RFIFOL(fd,GETPACKETPOS(cmd,2)));
	return;
}

/*==========================================
 * �F�B���X�g�폜�v��
 *------------------------------------------
 */
static void clif_parse_FriendDeleteRequest(int fd,struct map_session_data *sd, int cmd)
{
	friend_del_request(sd, RFIFOL(fd,GETPACKETPOS(cmd,0)), RFIFOL(fd,GETPACKETPOS(cmd,1)));
	return;
}

/*==========================================
 * /pvpinfo
 *------------------------------------------
 */
static void clif_parse_PvPInfo(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	if(!map[sd->bl.m].flag.pk)
		return;

	WFIFOW(fd,0)  = 0x210;
	WFIFOL(fd,2)  = sd->status.account_id;
	WFIFOL(fd,6)  = sd->status.char_id;
	WFIFOL(fd,10) = 0;	// times won
	WFIFOL(fd,14) = 0;	// times lost
	WFIFOL(fd,18) = ranking_get_point(sd, RK_PK);
	WFIFOSET(fd, packet_db[0x210].len);

	return;
}

/*==========================================
 * BS�����L���O	/blacksmith
 *------------------------------------------
 */
static void clif_parse_RankingBlacksmith(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	ranking_clif_display(sd,RK_BLACKSMITH);
	return;
}

/*==========================================
 * �A���P�~�����L���O	/alchemist
 *------------------------------------------
 */
static void clif_parse_RankingAlchemist(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	ranking_clif_display(sd,RK_ALCHEMIST);
	return;
}

/*==========================================
 * �e�R�������L���O	/taekwon
 *------------------------------------------
 */
static void clif_parse_RankingTaekwon(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	ranking_clif_display(sd,RK_TAEKWON);
	return;
}

/*==========================================
 * �s�E�҃����L���O	/pk
 *------------------------------------------
 */
static void clif_parse_RankingPk(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	ranking_clif_display(sd,RK_PK);
	return;
}

/*==========================================
 * �����L���O
 *------------------------------------------
 */
static void clif_parse_Ranking(int fd,struct map_session_data *sd, int cmd)
{
	int ranking_id;

	nullpo_retv(sd);

	ranking_id = RFIFOW(fd,GETPACKETPOS(cmd,0));

	ranking_clif_display(sd,ranking_id);
	return;
}

/*==========================================
 * ���[�����M
 *------------------------------------------
 */
static void clif_parse_SendMail(int fd,struct map_session_data *sd, int cmd)
{
	int bodylen;

	nullpo_retv(sd);

	if(!battle_config.romail) {	// ���[�����M���֎~
		clif_res_sendmail(fd,1);
		return;
	}

	bodylen = RFIFOW(fd,GETPACKETPOS(cmd,0)) - GETPACKETPOS(cmd,3) - 1;	// \0�͍��
	mail_checkmail(sd, RFIFOP(fd,GETPACKETPOS(cmd,1)), RFIFOP(fd,GETPACKETPOS(cmd,2)), RFIFOP(fd,GETPACKETPOS(cmd,3)), bodylen);

	return;
}

/*==========================================
 * ���[���̑I����M
 *------------------------------------------
 */
static void clif_parse_ReadMail(int fd,struct map_session_data *sd, int cmd)
{
	int mail_num = RFIFOL(fd,GETPACKETPOS(cmd,0));

	nullpo_retv(sd);

	intif_readmail(sd->status.char_id,mail_num);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_MailGetAppend(int fd,struct map_session_data *sd, int cmd)
{
	int mail_num = RFIFOL(fd,GETPACKETPOS(cmd,0));

	nullpo_retv(sd);

	intif_mail_getappend(sd->status.char_id,mail_num);
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_MailWinOpen(int fd,struct map_session_data *sd, int cmd)
{
	int flag;

	nullpo_retv(sd);

	// 0: �S�ĕԋp 1: �A�C�e���̂ݕԋp 2: Zeny�̂ݕԋp
	flag = RFIFOW(fd,GETPACKETPOS(cmd,0));

	mail_removeitem(sd, flag&3);

	return;
}

/*==========================================
 * ���[��BOX�̍X�V�v��
 *------------------------------------------
 */
static void clif_parse_RefleshMailBox(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	intif_mailbox(sd->status.char_id);

	return;
}

/*==========================================
 * ���[���ɓY�t
 *------------------------------------------
 */
static void clif_parse_SendMailSetAppend(int fd,struct map_session_data *sd, int cmd)
{
	int idx    = RFIFOW(fd,GETPACKETPOS(cmd,0));
	int amount = RFIFOL(fd,GETPACKETPOS(cmd,1));

	nullpo_retv(sd);

	if (idx < 0 || amount < 0)
		return;

	mail_setitem(sd, idx, amount);
	return;
}

/*==========================================
 * ���[���폜
 *------------------------------------------
 */
static void clif_parse_DeleteMail(int fd,struct map_session_data *sd, int cmd)
{
	int mail_num = RFIFOL(fd,GETPACKETPOS(cmd,0));

	nullpo_retv(sd);

	intif_deletemail(sd->status.char_id,mail_num);
	return;
}

/*==========================================
 * ���[���ԑ�
 *------------------------------------------
 */
static void clif_parse_ReturnMail(int fd,struct map_session_data *sd, int cmd)
{
	//int mail_num = RFIFOL(fd,GETPACKETPOS(cmd,0));
	//char *name = (char*)RFIFOP(fd,GETPACKETPOS(cmd,1));

	nullpo_retv(sd);

	// �Ƃ肠����������
	return;
}

/*==========================================
 * �z�����N���X
 *------------------------------------------
 */
static void clif_parse_HomMenu(int fd,struct map_session_data *sd, int cmd)
{
	homun_menu(sd,RFIFOB(fd,GETPACKETPOS(cmd,0)));
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_HomMercWalkMaster(int fd,struct map_session_data *sd, int cmd)
{
	struct block_list *bl = map_id2bl(RFIFOL(fd,GETPACKETPOS(cmd,0)));

	nullpo_retv(sd);

	if(bl == NULL || bl->prev == NULL)
		return;

	if(bl->type == BL_HOM) {
		if(sd->hd && bl == &sd->hd->bl) {
			homun_return_master(sd);
		}
	} else if(bl->type == BL_MERC) {
		if(sd->mcd && bl == &sd->mcd->bl) {
			merc_return_master(sd);
		}
	}
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_HomMercWalkToXY(int fd,struct map_session_data *sd, int cmd)
{
	struct block_list *bl = map_id2bl(RFIFOL(fd,GETPACKETPOS(cmd,0)));

	nullpo_retv(sd);

	if(bl == NULL || bl->prev == NULL)
		return;

	if( (bl->type == BL_HOM && sd->hd && bl == &sd->hd->bl) ||
	    (bl->type == BL_MERC && sd->mcd && bl == &sd->mcd->bl) )
	{
		int x = RFIFOB(fd,GETPACKETPOS(cmd,1))*4+(RFIFOB(fd,GETPACKETPOS(cmd,1)+1)>>6);
		int y = ((RFIFOB(fd,GETPACKETPOS(cmd,1)+1)&0x3f)<<4)+(RFIFOB(fd,GETPACKETPOS(cmd,1)+2)>>4);

		unit_walktoxy(bl,x,y);
	}
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_HomMercActionRequest(int fd,struct map_session_data *sd, int cmd)
{
	struct block_list *src = map_id2bl(RFIFOL(fd,GETPACKETPOS(cmd,0)));
	struct status_change *sc;
	int action_type,target_id;

	nullpo_retv(sd);

	if(src == NULL || src->prev == NULL)
		return;

	if(src->type == BL_HOM && (!sd->hd || src != &sd->hd->bl))
		return;
	else if(src->type == BL_MERC && (!sd->mcd || src != &sd->mcd->bl))
		return;

	if(unit_isdead(src)) {
		clif_clearchar_area(src,1);
		return;
	}

	sc = status_get_sc(src);
	if(sc && sc->option&OPTION_HIDE)
		return;

	unit_stop_walking(src,1);
	unit_stopattack(src);

	target_id   = RFIFOL(fd,GETPACKETPOS(cmd,1));
	action_type = RFIFOB(fd,GETPACKETPOS(cmd,2));

	// �v���C���[�ƈႢ once attack �����Ȃ�
	if(action_type == 0) {
		struct block_list *bl = map_id2bl(target_id);
		if(bl && mob_gvmobcheck(sd,bl) == 0)
			return;
		unit_attack(src,target_id,0);
	}
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_ChangeHomName(int fd,struct map_session_data *sd, int cmd)
{
	homun_change_name(sd,RFIFOP(fd,GETPACKETPOS(cmd,0)));
}

/*==========================================
 * /effect�Ƃ�
 *------------------------------------------
 */
static void clif_parse_clientsetting(int fd,struct map_session_data *sd, int cmd)
{
	// RFIFOL(fd,GETPACKETPOS(cmd,0))	effect��؂��Ă邩�ǂ���
	return;
}

/*==========================================
 * �{�q�v��
 *------------------------------------------
 */
static void clif_parse_BabyRequest(int fd,struct map_session_data *sd, int cmd)
{
	struct map_session_data* baby_sd = NULL;

	nullpo_retv(sd);

	baby_sd = map_id2sd(RFIFOL(fd,GETPACKETPOS(cmd,0)));

	if(baby_sd) {
		struct map_session_data *p_sd = pc_get_partner(sd);

		if(p_sd && pc_check_adopt_condition(baby_sd, sd, p_sd, 1)) {
			baby_sd->adopt_invite = sd->status.account_id;
			clif_baby_req_display(baby_sd, sd, p_sd->status.account_id);
		}
	}
	return;
}

/*==========================================
 * �{�q�ԓ�
 *------------------------------------------
 */
static void clif_parse_BabyReply(int fd,struct map_session_data *sd, int cmd)
{
	pc_adopt_reply(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)),RFIFOL(fd,GETPACKETPOS(cmd,1)),RFIFOL(fd,GETPACKETPOS(cmd,2)));
	return;
}

/*==========================================
 * ���z�ƌ��Ɛ��̊���̃Z�[�u�ԓ�
 *------------------------------------------
 */
static void clif_parse_FeelSaveAck(int fd,struct map_session_data *sd, int cmd)
{
	clif_feel_saveack(sd,(int)RFIFOB(fd,GETPACKETPOS(cmd,0)));
	return;
}

/*==========================================
 * �����v������
 *------------------------------------------
 */
static void clif_parse_Making(int fd,struct map_session_data *sd, int cmd)
{
	int nameid;

	nullpo_retv(sd);

#if PACKETVER < 20180704
	nameid = RFIFOW(fd,GETPACKETPOS(cmd,0));
#else
	nameid = RFIFOL(fd,GETPACKETPOS(cmd,0));
#endif
	skill_produce_mix(sd,nameid,0,0,0);

	memset(&sd->skill_menu,0,sizeof(sd->skill_menu));

	return;
}

/*==========================================
 * �z�b�g�L�[�̃Z�[�u
 *------------------------------------------
 */
static void clif_parse_HotkeySave(int fd,struct map_session_data *sd, int cmd)
{
	int idx;

	nullpo_retv(sd);

#if PACKETVER < 20090603
	idx = sd->hotkey_set * 27 + RFIFOW(fd,GETPACKETPOS(cmd,0));
	if(idx < 0 || idx >= MAX_HOTKEYS)
		return;

	sd->status.hotkey[idx].type = RFIFOB(fd,GETPACKETPOS(cmd,1));
	sd->status.hotkey[idx].id   = RFIFOL(fd,GETPACKETPOS(cmd,2));
	sd->status.hotkey[idx].lv   = RFIFOW(fd,GETPACKETPOS(cmd,3));
#elif PACKETVER < 20090617
	idx = sd->hotkey_set * 36 + RFIFOW(fd,GETPACKETPOS(cmd,0));
	if(idx < 0 || idx >= MAX_HOTKEYS)
		return;

	sd->status.hotkey[idx].type = RFIFOB(fd,GETPACKETPOS(cmd,1));
	sd->status.hotkey[idx].id   = RFIFOL(fd,GETPACKETPOS(cmd,2));
	sd->status.hotkey[idx].lv   = RFIFOW(fd,GETPACKETPOS(cmd,3));
#else
	idx = sd->hotkey_set * 38 + RFIFOW(fd,GETPACKETPOS(cmd,0));
	if(idx < 0 || idx >= MAX_HOTKEYS)
		return;

	sd->status.hotkey[idx].type = RFIFOB(fd,GETPACKETPOS(cmd,1));
	sd->status.hotkey[idx].id   = RFIFOL(fd,GETPACKETPOS(cmd,2));
	sd->status.hotkey[idx].lv   = RFIFOW(fd,GETPACKETPOS(cmd,3));
#endif

	return;
}

/*==========================================
 * �z�b�g�L�[�̃Z�[�u
 *------------------------------------------
 */
static void clif_parse_HotkeySave2(int fd,struct map_session_data *sd, int cmd)
{
#if PACKETVER >= 20190522
	int idx, tab;

	nullpo_retv(sd);

	tab = RFIFOW(fd,GETPACKETPOS(cmd,0));
	idx = tab * 38 + RFIFOW(fd,GETPACKETPOS(cmd,1));
	if(idx < 0 || idx >= MAX_HOTKEYS)
		return;

	sd->status.hotkey[idx].type = RFIFOB(fd,GETPACKETPOS(cmd,2));
	sd->status.hotkey[idx].id   = RFIFOL(fd,GETPACKETPOS(cmd,3));
	sd->status.hotkey[idx].lv   = RFIFOW(fd,GETPACKETPOS(cmd,4));
#endif

	return;
}

/*==========================================
 * �W�[�N�t���[�h�̏؂ɂ�镜��
 *------------------------------------------
 */
static void clif_parse_Revive(int fd,struct map_session_data *sd, int cmd)
{
	int idx;

	nullpo_retv(sd);

	if(map[sd->bl.m].flag.pvp && sd->pvp_point < 0)	// PVP�ŕ����s�\���
		return;
	if(!unit_isdead(&sd->bl))
		return;
	if(sd->sc.data[SC_HELLPOWER].timer != -1)		// �w���p���[��Ԃ͑h���s��
		return;
	if((idx = pc_search_inventory(sd,7621)) < 0) {	// �W�[�N�t���[�h�̏؂��������Ă��Ȃ�
		// �Đ��̌�
		if(sd->sc.data[SC_LIGHT_OF_REGENE].timer == -1)
			return;
		sd->status.hp = sd->status.max_hp * sd->sc.data[SC_LIGHT_OF_REGENE].val2 / 100;
		sd->status.sp = 0;
		status_change_end(&sd->bl,SC_LIGHT_OF_REGENE,-1);
	}
	else {
		pc_delitem(sd,idx,1,0,1);
		sd->status.hp = sd->status.max_hp;
		sd->status.sp = sd->status.max_sp;
	}
	clif_updatestatus(sd,SP_HP);
	clif_updatestatus(sd,SP_SP);
	pc_setstand(sd);
	if(battle_config.pc_invincible_time > 0)
		pc_setinvincibletimer(sd,battle_config.pc_invincible_time);
	clif_resurrection(&sd->bl,1);
	clif_misceffect2(&sd->bl,77);	// ���U�̃G�t�F�N�g��t���Ă݂�

	return;
}

/*==========================================
 * �b�����j���[
 *------------------------------------------
 */
static void clif_parse_MercMenu(int fd,struct map_session_data *sd, int cmd)
{
	merc_menu(sd,RFIFOB(fd,GETPACKETPOS(cmd,0)));

	return;
}

/*==========================================
 * �����E�B���h�E�\���v��
 *------------------------------------------
 */
static void clif_parse_PartyEquipWindow(int fd,struct map_session_data *sd, int cmd)
{
	party_equip_window(sd, RFIFOL(fd,GETPACKETPOS(cmd,0)));

	return;
}

/*==========================================
 * �ݒ�ύX�v��
 *------------------------------------------
 */
static void clif_parse_Config(int fd,struct map_session_data *sd, int cmd)
{
	int type = RFIFOL(fd,GETPACKETPOS(cmd,0));
	int flag = ( RFIFOL(fd,GETPACKETPOS(cmd,1)) ) ? 1 : 0;

	nullpo_retv(sd);

	switch(type) {
	case 0:		// �������J
		sd->status.show_equip = flag;
		break;
	case 1:		// �Ăяo������@�\
		sd->status.allow_call = flag;
		return;
	case 2:		// �y�b�g�����a���
		if(sd->pd) {
			if(flag)
				sd->status.autofeed |= 1;
			else
				sd->status.autofeed &= ~1;
		}
		else
			return;
		break;
	case 3:		// �z�������a���
		if(sd->hd) {
			if(flag)
				sd->status.autofeed |= 2;
			else
				sd->status.autofeed &= ~2;
		}
		else
			return;
		break;
	default:
		return;
	}

	clif_configack(sd, type, flag);

	return;
}

/*==========================================
 * �n���e�B���O���X�g
 * �ڍוs���Ȃ��ߖ�����
 *------------------------------------------
 */
static void clif_parse_HuntingList(int fd,struct map_session_data *sd, int cmd)
{
/*
	char buf[] = "";

	nullpo_retv(sd);

	WFIFOW(fd,0) = 0x27a;
	WFIFOW(fd,2) = strlen(buf) + 1;
	memcpy(WFIFOP(fd,4), buf, sizeof(buf));
	WFIFOSET(fd,WFIFOW(fd,2));
*/
	return;
}

/*==========================================
 * ���`���b�g���M�v��
 * �ڍוs���Ȃ��ߖ�����
 *------------------------------------------
 */
static void clif_parse_BattleMessage(int fd,struct map_session_data *sd, int cmd)
{
	char *message;
	int len, message_size;

	nullpo_retv(sd);

	len = RFIFOW(fd, GETPACKETPOS(cmd,0));
	message = (char *)RFIFOP(fd, GETPACKETPOS(cmd,1));
	message_size = len - GETPACKETPOS(cmd,1); // including NULL

	if (message_size < 8)	// name (mini:4) + " : " (3) + NULL (1) (void mesages are possible for skills)
		return;
	if (message_size > 255)	// too long
		return;

	message[message_size - 1] = 0; // be sure to have a NULL (hacker can send a no-NULL terminated string)

	if (battle_config.check_player_name_battle_msg) {
		// structure of message: <player_name> : <message>
		int name_length;
		char *p_message;
		name_length = (int)strlen(sd->status.name);
		if (name_length > 24)
			name_length = 24;
		p_message = message + name_length;
		if (message_size < name_length + 3 + 1 || // check void message (at least 1 char) -> normal client refuse to send void message (but some skills can)
		    memcmp(message, sd->status.name, name_length) != 0 || // check player name
		    *p_message != ' ' || *(p_message + 1) != ':' || *(p_message + 2) != ' ') { // check ' : '
			// add here a message if necessary
			return;
		}
	}

	if (is_atcommand(fd, sd, message) != AtCommand_None)
		return;

	// �o�[�T�[�N�A�`���b�g�֎~��ԂȂ��b�s��
	if (sd->sc.data[SC_BERSERK].timer != -1 || sd->sc.data[SC_NOCHAT].timer != -1 || sd->sc.data[SC_DEEP_SLEEP].timer != -1)
		return;

/*
	WFIFOW(fd,0) = 0x2dc;
	WFIFOW(fd,2) = message_size + 32;
	WFIFOL(fd,4) = sd->bl.id;
	memcpy(WFIFOP(fd,8), sd->status.name, 24);
	memcpy(WFIFOP(fd,32), message, message_size);
	clif_send(WFIFOP(fd,0), WFIFOW(fd,2), &sd->bl, AREA);
*/

	return;
}

/*==========================================
 * �p�[�e�B�[���[�_�[�`�F���W
 *------------------------------------------
 */
static void clif_parse_PartyChangeLeader(int fd,struct map_session_data *sd, int cmd)
{
	party_changeleader(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)));

	return; 
}

/*==========================================
 * GM�ɂ�鑕������
 *------------------------------------------
 */
static void clif_parse_GmFullstrip(int fd,struct map_session_data *sd, int cmd)
{
	int id,lv,i;
	struct map_session_data *tsd = NULL;

	nullpo_retv(sd);

	id = RFIFOL(fd, GETPACKETPOS(cmd,0));
	lv = pc_isGM(sd);
	tsd = map_id2sd(id);
	if(tsd == NULL)
		return;

	if(lv <= 0 || lv < pc_isGM(tsd))
		return;

	status_calc_pc_stop_begin(&tsd->bl);

	for(i=0; i<MAX_INVENTORY; i++) {
		if(tsd->status.inventory[i].equip) {
			pc_unequipitem(tsd,i,0);
		}
	}

	/* 1���ԒE�ߌn�̏�Ԉُ�ɂ����� */
	status_change_start(&tsd->bl,SC_STRIPWEAPON,1,0,0,0,60000,0);
	status_change_start(&tsd->bl,SC_STRIPSHIELD,1,0,0,0,60000,0);
	status_change_start(&tsd->bl,SC_STRIPARMOR,1,0,0,0,60000,0);
	status_change_start(&tsd->bl,SC_STRIPHELM,1,0,0,0,60000,0);
	status_change_start(&tsd->bl,SC__STRIPACCESSARY,1,0,0,0,60000,0);

	status_calc_pc_stop_end(&tsd->bl);

	return;
}

/*==========================================
 * �p�[�e�B�[�u�b�L���O�o�^
 *------------------------------------------
 */
static void clif_parse_PartyBookingRegisterReq(int fd,struct map_session_data *sd, int cmd)
{
	int i,lv,mapid;
	int job[6];

	nullpo_retv(sd);

	lv = RFIFOW(fd,GETPACKETPOS(cmd,0));
	mapid = RFIFOW(fd,GETPACKETPOS(cmd,1));
	for(i=0; i<6; i++)
		job[i] = RFIFOW(fd,GETPACKETPOS(cmd,2+i));

	booking_register(sd,lv,mapid,job);

	return;
}

/*==========================================
 * �p�[�e�B�[�u�b�L���O�o�^2
 *------------------------------------------
 */
static void clif_parse_PartyBookingRegisterReq2(int fd,struct map_session_data *sd, int cmd)
{
	int lv;
	char *memo;

	nullpo_retv(sd);

	// parse
	lv   = RFIFOW(fd,GETPACKETPOS(cmd,0));
	memo = (char *)RFIFOP(fd,GETPACKETPOS(cmd,1));

	// �o�^����
	booking_register2(sd,lv,memo);

	return;
}

/*==========================================
 * �p�[�e�B�[�u�b�L���O�����v��
 *------------------------------------------
 */
static void clif_parse_PartyBookingSearchReq(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	booking_searchcond(sd,RFIFOW(fd,GETPACKETPOS(cmd,0)),RFIFOW(fd,GETPACKETPOS(cmd,1)),RFIFOW(fd,GETPACKETPOS(cmd,2)),RFIFOL(fd,GETPACKETPOS(cmd,3)),RFIFOW(fd,GETPACKETPOS(cmd,4)));

	return;
}

/*==========================================
 * �p�[�e�B�[�u�b�L���O�����v��2
 *------------------------------------------
 */
static void clif_parse_PartyBookingSearchReq2(int fd,struct map_session_data *sd, int cmd)
{
	int lv;
	// TODO:�c��6�o�C�g�͉��Ɏg���̂��s��

	nullpo_retv(sd);

	// parse
	lv = RFIFOW(fd,GETPACKETPOS(cmd,0));

	// ��������
	booking_searchcond2(sd,lv);

	return;
}

/*==========================================
 * �p�[�e�B�[�u�b�L���O�폜�v��
 *------------------------------------------
 */
static void clif_parse_PartyBookingDeleteReq(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	booking_delete(sd);

	return;
}

/*==========================================
 * �p�[�e�B�[�u�b�L���O�폜�v��2
 *------------------------------------------
 */
static void clif_parse_PartyBookingDeleteReq2(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	booking_delete(sd);

	return;
}

/*==========================================
 * �p�[�e�B�[�u�b�L���O�A�b�v�f�[�g�v��
 *------------------------------------------
 */
static void clif_parse_PartyBookingUpdateReq(int fd,struct map_session_data *sd, int cmd)
{
	int i;
	int job[6];

	nullpo_retv(sd);

	for(i=0; i<6; i++)
		job[i] = RFIFOW(fd,GETPACKETPOS(cmd,i));

	booking_update(sd,job);

	return;
}

/*==========================================
 * �p�[�e�B�[�u�b�L���O�A�b�v�f�[�g�v��2
 *------------------------------------------
 */
static void clif_parse_PartyBookingUpdateReq2(int fd,struct map_session_data *sd, int cmd)
{
	char *memo;

	nullpo_retv(sd);

	// parse
	memo = (char *)RFIFOP(fd, GETPACKETPOS(cmd,0));

	booking_update2(sd,memo);

	return;
}

/*==========================================
 * �X�L�����X�g�I����M
 *------------------------------------------
 */
static void clif_parse_SelectSkill(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	switch(sd->skill_menu.id)
	{
		case SC_AUTOSHADOWSPELL:		/* �V���h�E�I�[�g�X�y�� */
			skill_autoshadowspell(sd,RFIFOW(fd,GETPACKETPOS(cmd,1)));
			break;
	}

	memset(&sd->skill_menu,0,sizeof(sd->skill_menu));

	return;
}

/*==========================================
 * �A�C�e���ϊ����X�g��M
 *------------------------------------------
 */
static void clif_parse_ConvertItem(int fd,struct map_session_data *sd, int cmd)
{
	int num, type, flag;
	nullpo_retv(sd);

	num = ((RFIFOW(fd,GETPACKETPOS(cmd,0))) - 12) / 4;
	type = RFIFOL(fd,GETPACKETPOS(cmd,1));
	flag = RFIFOL(fd,GETPACKETPOS(cmd,2));

	// OK�����A�C�e����1�ȏ�̏ꍇ
	if(flag == 1 && num > 0) {
		switch(type) {
			case 0:
				/* �`�F���W�}�e���A�� */
				if(sd->skill_menu.id == GN_CHANGEMATERIAL) {
					skill_changematerial(sd, num, (unsigned short*)RFIFOP(fd,GETPACKETPOS(cmd,3)));
				}
				break;
			case 1:
			case 2:
				/* �G�������^���A�i���C�V�X */
				if(sd->skill_menu.id == SO_EL_ANALYSIS) {
					skill_el_analysis(sd, num, type, (unsigned short*)RFIFOP(fd,GETPACKETPOS(cmd,3)));
				}
				break;
		}
	}

	memset(&sd->skill_menu,0,sizeof(sd->skill_menu));

	return;
}

/*==========================================
 * �N�G�X�g���X�g��ԕύX
 *------------------------------------------
 */
static void clif_parse_QuestState(int fd,struct map_session_data *sd, int cmd)
{
	int nameid;
	char result;

	nullpo_retv(sd);

	nameid = RFIFOL(fd,GETPACKETPOS(cmd,0));

	result = quest_update_status(sd, nameid, ( RFIFOB(fd,GETPACKETPOS(cmd,1)) )? 1 : 0);
	if(result < 0)
		return;

	WFIFOW(fd,0) = 0x2b7;
	WFIFOL(fd,2) = nameid;
	WFIFOB(fd,6) = result;
	WFIFOSET(fd,packet_db[0x2b7].len);

	return;
}

/*==========================================
 * �r���o�[����
 *------------------------------------------
 */
static void clif_parse_ProgressBar(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	npc_scriptcont(sd, sd->progressbar.npc_id);

	return;
}

/*==========================================
 * ����I�X�J�ݗv��
 *------------------------------------------
 */
static void clif_parse_OpenBuyingStoreReq(int fd,struct map_session_data *sd, int cmd)
{
	int len = RFIFOW(fd,GETPACKETPOS(cmd,0)) - 89;
	int limit_zeny = RFIFOL(fd,GETPACKETPOS(cmd,1));
	bool result = ( RFIFOB(fd,GETPACKETPOS(cmd,2)) ) ? true : false;
	char *store_name = RFIFOP(fd,GETPACKETPOS(cmd,3));
	const unsigned char *data = RFIFOP(fd,GETPACKETPOS(cmd,4));
#if PACKETVER < 20180704
	short size = 8;
#else
	short size = 10;
#endif

	// ������null�������Z�b�g
	store_name[79] = '\0';

	buyingstore_openstore(sd, limit_zeny, result, store_name, data, ( len <= 0 ) ? 0 : len/size);

	return;
}

/*==========================================
 * ����I�X���v��
 *------------------------------------------
 */
static void clif_parse_CloseBuyingStoreReq(int fd,struct map_session_data *sd, int cmd)
{
	buyingstore_close(sd);

	return;
}

/*==========================================
 * ����I�X�A�C�e�����X�g�v��
 *------------------------------------------
 */
static void clif_parse_ClickBuyingStoreReq(int fd,struct map_session_data *sd, int cmd)
{
	int account_id = RFIFOL(fd,GETPACKETPOS(cmd,0));

	buyingstore_itemlist(sd, account_id);

	return;
}

/*==========================================
 * ����I�X�A�C�e�����p�v��
 *------------------------------------------
 */
static void clif_parse_SellBuyingStoreReq(int fd,struct map_session_data *sd, int cmd)
{
	int len = RFIFOW(fd,GETPACKETPOS(cmd,0)) - 12;
	int account_id = RFIFOL(fd,GETPACKETPOS(cmd,1));
	unsigned int buyer_id = RFIFOL(fd,GETPACKETPOS(cmd,2));
	const unsigned char *data = RFIFOP(fd,GETPACKETPOS(cmd,3));
#if PACKETVER < 20180704
	short size = 6;
#else
	short size = 8;
#endif

	buyingstore_sell(sd, account_id, buyer_id, data, ( len <= 0 ) ? 0 : len/size);

	return;
}

/*==========================================
 * GM�R�}���h /recall2
 *------------------------------------------
 */
static void clif_parse_GMrecall2(int fd,struct map_session_data *sd, int cmd)
{
	int account_id;
	struct map_session_data *pl_sd;

	account_id = RFIFOL(fd, GETPACKETPOS(cmd,0));

	if((pl_sd = map_id2sd(account_id)) != NULL) {
		char command[64];
		sprintf(command, "%crecall %s", GM_Symbol(), pl_sd->status.name);
		is_atcommand_sub(fd, sd, command, 0);
	}

	return;
}

/*==========================================
 * GM�R�}���h /remove2
 *------------------------------------------
 */
static void clif_parse_GMremove2(int fd,struct map_session_data *sd, int cmd)
{
	int account_id;
	struct map_session_data *pl_sd;

	account_id = RFIFOL(fd, GETPACKETPOS(cmd,0));

	if((pl_sd = map_id2sd(account_id)) != NULL) {
		char command[64];
		sprintf(command, "%cjumpto %s", GM_Symbol(), pl_sd->status.name);
		is_atcommand_sub(fd, sd, command, 0);
	}

	return;
}

/*==========================================
 * ������o�^
 *------------------------------------------
 */
static void clif_parse_RegBattleGround(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 * �l�^�u�փA�C�e���ړ�
 *------------------------------------------
 */
static void clif_parse_MoveItem(int fd,struct map_session_data *sd, int cmd)
{
	int idx;
	char flag;

	nullpo_retv(sd);

	idx = RFIFOW(fd,GETPACKETPOS(cmd,0)) - 2;
	if(idx < 0 || idx >= MAX_INVENTORY)
		return;

	flag = RFIFOB(fd,GETPACKETPOS(cmd,1));

	if(sd->status.inventory[idx].private_ && flag == 1 )
		sd->status.inventory[idx].private_ = 0;
	else if(flag == 0)
		sd->status.inventory[idx].private_ = 1;
	else
		return;

	clif_privateitem(sd, idx, flag);

	return;
}

/*==========================================
 * �p�[�e�B�[�u�b�L���O���X�g���珜�O
 *------------------------------------------
 */
static void clif_parse_PartyBookingIgnoreReq(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 * �p�[�e�B�[�u�b�L���O���X�g����p�[�e�B�[�������N�G�X�g
 *------------------------------------------
 */
static void clif_parse_PartyBookingJoinPartyReq(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 * �p�[�e�B�[�u�b�L���O�����o�[�������N�G�X�g
 *------------------------------------------
 */
static void clif_parse_PartyBookingSummonMember(int fd,struct map_session_data *sd, int cmd)
{
	//int len = RFIFOW(fd,GETPACKETPOS(cmd,0)) - 4;
	//const unsigned char *account_list = RFIFOP(fd,GETPACKETPOS(cmd,1));

	// TODO

	return;
}

/*==========================================
 * �p�[�e�B�[�u�b�L���O���X�g����p�[�e�B�[�������N�G�X�g�L�����Z��
 *------------------------------------------
 */
static void clif_parse_PartyBookingJoinPartyCancel(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_BlockingPlayCancel(int fd,struct map_session_data *sd, int cmd)
{
#if PACKETVER >= 20190403
	WFIFOW(fd, 0)=0xb1b;
	WFIFOSET(fd,packet_db[0xb1b].len);
#endif
	return;
}

/*==========================================
 * �N�����`���b�g���M�v��
 * �ڍוs���Ȃ��ߖ�����
 *------------------------------------------
 */
static void clif_parse_ClanMessage(int fd,struct map_session_data *sd, int cmd)
{
	char *message;
	int message_size;

	nullpo_retv(sd);

	message = (char *)RFIFOP(fd, GETPACKETPOS(cmd,1));
	message_size = RFIFOW(fd, GETPACKETPOS(cmd,0)) - GETPACKETPOS(cmd,1); // including NULL

	if (message_size < 8)	// name (mini:4) + " : " (3) + NULL (1) (void mesages are possible for skills)
		return;
	if (message_size > 255)	// too long
		return;

	message[message_size - 1] = 0; // be sure to have a NULL (hacker can send a no-NULL terminated string)

	if (is_atcommand(fd, sd, message) != AtCommand_None)
		return;

	// �o�[�T�[�N�A�`���b�g�֎~��ԂȂ��b�s��
	if (sd->sc.data[SC_BERSERK].timer != -1 || sd->sc.data[SC_NOCHAT].timer != -1 || sd->sc.data[SC_DEEP_SLEEP].timer != -1)
		return;

/*
	WFIFOW(fd, 0)=0x98e;
	WFIFOW(fd, 2)=message_size+28;
	memcpy(WFIFOP(fd, 4),sd->status.name,24);
	memcpy(WFIFOP(fd,28),message,message_size);
	WFIFOSET(fd,WFIFOW(fd,2));
*/

	return;
}

/*==========================================
 * ��s�a������v��
 *------------------------------------------
 */
static void clif_parse_BankingDepositReq(int fd,struct map_session_data *sd, int cmd)
{
	int account_id = RFIFOL(fd,GETPACKETPOS(cmd,0));
	int zeny       = RFIFOL(fd,GETPACKETPOS(cmd,1));

	nullpo_retv(sd);

	bank_deposit(sd, account_id, zeny);

	return;
}

/*==========================================
 * ��s�����o���v��
 *------------------------------------------
 */
static void clif_parse_BankingWithdrawReq(int fd,struct map_session_data *sd, int cmd)
{
	int account_id = RFIFOL(fd,GETPACKETPOS(cmd,0));
	int zeny       = RFIFOL(fd,GETPACKETPOS(cmd,1));

	nullpo_retv(sd);

	bank_withdraw(sd, account_id, zeny);

	return;
}

/*==========================================
 * ��s���v��
 *------------------------------------------
 */
static void clif_parse_BankingInfoReq(int fd,struct map_session_data *sd, int cmd)
{
	int result = 0;
	int account_id = RFIFOL(fd,GETPACKETPOS(cmd,0));
	struct map_session_data *tmpsd;

	nullpo_retv(sd);

	tmpsd = map_id2sd(account_id);
	if(!tmpsd || sd != tmpsd)
		result = 1;
	if( sd->npc_id != 0 || sd->state.storage_flag || sd->state.store || sd->state.deal_mode != 0 ||
	    sd->state.mail_appending || sd->chatID != 0 )
		result = 1;

	WFIFOW(fd, 0)=0x9a6;
	WFIFOQ(fd, 2)=sd->deposit;
	WFIFOW(fd,10)=result;
	WFIFOSET(fd,packet_db[0x9a6].len);

	return;
}

/*==========================================
 * �}�[�P�b�g�A�C�e���w���v��
 *------------------------------------------
 */
static void clif_parse_SellMarketReq(int fd,struct map_session_data *sd, int cmd)
{
#if PACKETVER >= 20131223
	int fail, n, c = 0;
#if PACKETVER < 20180704
	short size = 6;
#else
	short size = 8;
#endif

	nullpo_retv(sd);

	// ����ł�����A�ԃG���̎���NPC���N���b�N�ł��Ȃ�
	if(unit_isdead(&sd->bl)) {
		clif_clearchar_area(&sd->bl,1);
		return;
	}
	if(sd->sc.data[SC_SUHIDE].timer != -1)
		return;
	if(sd->npc_id != 0 || sd->state.store || sd->state.deal_mode != 0 || sd->status.manner < 0 || sd->state.mail_appending)
		return;

	n = (RFIFOW(fd,GETPACKETPOS(cmd,0)) - 4) /size;
	if (n <= 0) // max is checked in npc_buylist function
		return;

	fail = npc_buylist(sd, n, (unsigned char*)RFIFOP(fd,GETPACKETPOS(cmd,1))); // item_list

#if PACKETVER >= 20190807
	fail = ( fail == 0 ? 0 : -1 );
#else
	fail = ( fail == 0 ? 1 : 0 );
#endif

	WFIFOW(fd,0)=0x9d7;
	WFIFOB(fd,4)=fail;
	if( fail ){
		int i, j;
		int nameid, amount;
		struct npc_data *nd = map_id2nd( sd->npc_shopid );

		size += 2;

		for(i=0; i < n; i++){
#if PACKETVER < 20180704
			nameid = *(unsigned short *)RFIFOP(fd,6*i + 0 + GETPACKETPOS(cmd,1));
			amount = *(unsigned int *)RFIFOP(fd,6*i + 2 + GETPACKETPOS(cmd,1));
#else
			nameid = *(unsigned int *)RFIFOP(fd,8*i + 0 + GETPACKETPOS(cmd,1));
			amount = *(unsigned int *)RFIFOP(fd,8*i + 4 + GETPACKETPOS(cmd,1));
#endif
			for(j=0; nd->u.shop_item[j].nameid; j++) {
				if (nd->u.shop_item[j].nameid == nameid)
					break;
			}
			if (nd->u.shop_item[j].nameid == 0)
				continue;

#if PACKETVER < 20180704
			WFIFOW(fd,c*size+5)=nameid;
			WFIFOW(fd,c*size+7)=amount;
			WFIFOL(fd,c*size+9)=nd->u.shop_item[j].value;
#else
			WFIFOL(fd,c*size+5)=nameid;
			WFIFOW(fd,c*size+9)=amount;
			WFIFOL(fd,c*size+11)=nd->u.shop_item[j].value;
#endif
			c++;
		}
	}
	WFIFOW(fd,2)=c*size+5;
	WFIFOSET(fd,WFIFOW(fd,2));
#endif
	sd->npc_shopid = 0;

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_CloseMarketReq(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	sd->npc_shopid = 0;
	return;
}

/*==========================================
 * �N���C�A���g�̃^�C���X�^���v
 * ���p�@��Ȃ��̂ŃR�����g�A�E�g
 *------------------------------------------
 */
static void clif_parse_ClientTimeStamp(int fd,struct map_session_data *sd, int cmd)
{
	/*
	time_t t;
	char tmpstr[32];

	t = (time_t)RFIFOL(fd,GETPACKETPOS(cmd,0));
	strftime(tmpstr, sizeof(tmpstr), "%Y-%m-%d %H:%M:%S", localtime(&t));

	printf("client session #%d %s\n", fd, tmpstr);
	*/

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_OpenRoDEX(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_CloseRoDEX(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_ReadRoDEX(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_WriteRoDEX(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_NextListRoDEX(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_RefreshRoDEX(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_ZenyfromRoDEX(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_ItemfromRoDEX(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_DeleteRoDEX(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_CancelWriteRoDEX(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_AdditemRoDEX(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_DelitemRoDEX(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_OpenWriteRoDEX(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 * �z�b�g�L�[�̃e�[�u����]
 *------------------------------------------
 */
static void clif_parse_HotkeyRotate(int fd,struct map_session_data *sd, int cmd)
{
	int id = RFIFOB(fd,GETPACKETPOS(cmd,0));

	nullpo_retv(sd);

	sd->hotkey_rotate[0] = id;

	return;
}

/*==========================================
 * �z�b�g�L�[�̃e�[�u����]
 *------------------------------------------
 */
static void clif_parse_HotkeyRotate2(int fd,struct map_session_data *sd, int cmd)
{
#if PACKETVER >= 20190522
	int tab = RFIFOW(fd,GETPACKETPOS(cmd,0));
	int id = RFIFOB(fd,GETPACKETPOS(cmd,1));

	nullpo_retv(sd);

	if(tab >= MAX_HOTKEYS_TAB)
		return;

	sd->hotkey_rotate[tab] = id;
#endif
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_OpenRoulette(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_CloseRoulette(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_ChangeTitleReq(int fd,struct map_session_data *sd, int cmd)
{
	int title_id;

	nullpo_retv(sd);

	title_id = RFIFOL(fd,GETPACKETPOS(cmd,0));

	if(title_id == sd->status.title_id)
		return;

	if(title_id <= 0) {
		sd->status.title_id = 0;
	}
	else {
		if(achieve_check_title(sd, title_id)) {
			clif_change_title_ack(sd->fd, 1, title_id);
			return;
		}
	}

	//clif_name_area(&sd->bl);
	clif_change_title_ack(sd->fd, 0, title_id);
	return;
}

/*==========================================
 * �����N���b�N�Ӓ�
 *------------------------------------------
 */
static void clif_parse_OneClickItemidentify(int fd,struct map_session_data *sd, int cmd)
{
	int idx = RFIFOW(fd,GETPACKETPOS(cmd,0))-2;
	int i;

	nullpo_retv(sd);

	if(idx < 0 || idx >= MAX_INVENTORY)
		return;

	if(sd->status.inventory[idx].nameid <= 0 || sd->status.inventory[idx].identify == 1)
		return;

	if((i = pc_search_inventory(sd, 611)) == -1)
		return;

	pc_delitem(sd,i,1,0,1);
	pc_item_identify(sd,idx);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_GetRewardReq(int fd,struct map_session_data *sd, int cmd)
{
	int achieve_id;
	char result;

	nullpo_retv(sd);

	achieve_id = RFIFOL(fd,GETPACKETPOS(cmd,0));

	result = achieve_check_reward(sd, achieve_id);

	clif_achievement_reward_ack(sd->fd, result, achieve_id);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_OpenUi(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_CameraInfo(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_ResetCooldown(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_AddEquipSwitch(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 
 *------------------------------------------
 */
static void clif_parse_DelEquipSwitch(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_EquipSwitchReq(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_EquipSwitchReqSingle(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_ChangeDress(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_AttendanceReq(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_PrivateAirshipReq(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_Ping(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 * �������A���_���W��������
 *------------------------------------------
 */
static void clif_parse_MemorialCommand(int fd,struct map_session_data *sd, int cmd)
{
	int menu = RFIFOL(fd,GETPACKETPOS(cmd,0));
	struct party *pt;

	nullpo_retv(sd);

	// �p�[�e�B�[������
	if((pt = party_search(sd->status.party_id)) == NULL)
		return;

	switch(menu) {
	case 3:
		memorial_delete(pt->memorial_id);
		break;
	}

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_InventoryExpantion(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_PetEvolution(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_CloseLapineUpgrade(int fd,struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_LapineUpgradeAck(int fd,struct map_session_data *sd, int cmd)
{
	int nameid, idx;
	int ret;

	nullpo_retv(sd);

	if(sd->npc_id != 0 || sd->state.store || sd->state.deal_mode != 0 || sd->chatID || sd->state.storage_flag || sd->state.mail_appending || sd->state.blockedmove)
		return;

#if PACKETVER < 20180704
	nameid = RFIFOW(fd,GETPACKETPOS(cmd,0));
#else
	nameid = RFIFOL(fd,GETPACKETPOS(cmd,0));
#endif

	idx = RFIFOW(fd,GETPACKETPOS(cmd,1)) - 2;

	ret = pc_upgrade_item(sd, nameid, idx);

	clif_lapineupgradeack(sd, ret);
	return;
}

/*==========================================
 * �R��֌W����
 *------------------------------------------
 */
static void clif_parse_MountOff(int fd, struct map_session_data *sd, int cmd)
{
#if PACKETVER >= 20190703
	const int menu = RFIFOB(fd,GETPACKETPOS(cmd,0));

	nullpo_retv(sd);

	switch (menu) {
	case 1:		// dragon
		if (pc_isdragon(sd))
			pc_setoption(sd, sd->sc.option &~ OPTION_DRAGON);
		break;
	case 3:		// madogear
		if (pc_isgear(sd))
			pc_setoption(sd, sd->sc.option &~ OPTION_MADOGEAR);
		break;
	case 4:		// peco
		if (pc_isriding(sd))
			pc_setoption(sd, sd->sc.option &~ OPTION_PECO);
		break;
	case 5:		// falcon
		if (pc_isfalcon(sd))
			pc_setoption(sd, sd->sc.option &~ OPTION_FALCON);
		break;
	case 6:		// cart
		if (sd->sc.data[SC_ON_PUSH_CART].timer != -1)
			pc_setcart(sd, 0);
		break;
	default:	// unused
		break;
	}
#endif
	return;
}

/*==========================================
 * 
 *------------------------------------------
 */
static void clif_parse_CashMarketOpen(int fd, struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 * 
 *------------------------------------------
 */
static void clif_parse_AdventureGuide(int fd, struct map_session_data *sd, int cmd)
{
	// TODO
	return;
}

/*==========================================
 * 
 *------------------------------------------
 */
static void clif_parse_UnequipItemAll(int fd, struct map_session_data *sd, int cmd)
{
	int i;

	nullpo_retv(sd);

	if (unit_isdead(&sd->bl)) {
		clif_clearchar_area(&sd->bl, 1);
		return;
	}

	if (sd->sc.data[SC_BLADESTOP].timer != -1 || sd->sc.data[SC_BERSERK].timer != -1 || sd->sc.data[SC_KYOUGAKU].timer != -1 || sd->sc.data[SC_SUHIDE].timer != -1) {
		clif_unequipitemallack(sd,1);
		return;
	}
	if (sd->npc_id != 0 || sd->state.store || (sd->sc.opt1 > OPT1_NORMAL && sd->sc.opt1 != OPT1_BURNNING) || sd->state.mail_appending) {
		clif_unequipitemallack(sd,1);
		return;
	}

	for(i=0; i<MAX_INVENTORY; i++) {
		if(sd->status.inventory[i].equip) {
			pc_unequipitem(sd,i,0);
		}
	}

	clif_unequipitemallack(sd,0);
	return;
}

/*==========================================
 * 
 *------------------------------------------
 */
static void clif_parse_UnequipItemAll2(int fd, struct map_session_data *sd, int cmd)
{
	int i;
	int pos = RFIFOL(fd,GETPACKETPOS(cmd,0));

	nullpo_retv(sd);

	if (unit_isdead(&sd->bl)) {
		clif_clearchar_area(&sd->bl, 1);
		return;
	}

	if (sd->sc.data[SC_BLADESTOP].timer != -1 || sd->sc.data[SC_BERSERK].timer != -1 || sd->sc.data[SC_KYOUGAKU].timer != -1 || sd->sc.data[SC_SUHIDE].timer != -1) {
		clif_unequipitemallack(sd,1);
		return;
	}
	if (sd->npc_id != 0 || sd->state.store || (sd->sc.opt1 > OPT1_NORMAL && sd->sc.opt1 != OPT1_BURNNING) || sd->state.mail_appending) {
		clif_unequipitemallack(sd,1);
		return;
	}

	for(i=0; i<MAX_INVENTORY; i++) {
		if(sd->status.inventory[i].equip & pos) {
			pc_unequipitem(sd,i,0);
		}
	}

	clif_unequipitemallack(sd,0);
	return;
}

/*==========================================
 * �����X�e�[�^�X�A�b�v
 *------------------------------------------
 */
static void clif_parse_TStatusUp(int fd, struct map_session_data *sd, int cmd)
{
	pc_tstatusup(sd, RFIFOW(fd,GETPACKETPOS(cmd,0)), RFIFOW(fd,GETPACKETPOS(cmd,1)));

	return;
}

/*==========================================
 * �N���C�A���g�̃f�X�g���N�^
 *------------------------------------------
 */
static int clif_disconnect(int fd)
{
	struct map_session_data *sd = (struct map_session_data *)session[fd]->session_data;

	if(sd && sd->state.auth) {
		clif_quitsave(sd);
	}
	close(fd);

	if(sd) {
		struct map_session_data *tmpsd = map_id2sd(sd->bl.id);
		if(tmpsd == sd)
			map_deliddb(&sd->bl);
		if(sd->bl.prev)
			map_delblock(&sd->bl);
	}

	return 0;
}

/*==========================================
 * �N���C�A���g����̃p�P�b�g���
 * socket.c��do_parsepacket����Ăяo�����
 *------------------------------------------
 */
int clif_parse(int fd)
{
	int cmd, packet_len = 0;
	struct map_session_data *sd;

	// char�I�Ɍq�����ĂȂ��Ԃ͐ڑ��֎~
	if(!chrif_isconnect())
		session[fd]->eof = 1;

	while(session[fd] != NULL && !session[fd]->eof) {
		sd = (struct map_session_data *)session[fd]->session_data;

		if(RFIFOREST(fd) < 2)
			return 0;
		cmd = RFIFOW(fd,0);

		// �Ǘ��p�p�P�b�g����
		if(cmd >= 30000) {
			switch(cmd) {
			case 0x7530:	// Auriga���擾
				WFIFOW(fd,0)=0x7531;
				WFIFOB(fd,2)=AURIGA_MAJOR_VERSION;
				WFIFOB(fd,3)=AURIGA_MINOR_VERSION;
				WFIFOW(fd,4)=AURIGA_REVISION;
				WFIFOB(fd,6)=AURIGA_RELEASE_FLAG;
				WFIFOB(fd,7)=AURIGA_OFFICIAL_FLAG;
				WFIFOB(fd,8)=AURIGA_SERVER_MAP;
				WFIFOW(fd,9)=get_current_version();
				WFIFOSET(fd,11);
				RFIFOSKIP(fd,2);
				return 0;
			case 0x7532:	// �ڑ��̐ؒf
				close(fd);
				session[fd]->eof = 1;
				return 0;
			default:
				if(battle_config.use_packet_obfuscation) {
					// �p�P�b�g��ǉ��̉\��������̂Ŏ��̏����ɓn��
					break;
				}
				printf("clif_parse: unknown admin packet 0x%04x disconnect session #%d\n", cmd, fd);
#ifdef DUMP_UNKNOWN_PACKET
				hex_dump(stdout, RFIFOP(fd,0), RFIFOREST(fd));
				printf("\n");
#endif
				close(fd);
				session[fd]->eof = 1;
				return 0;
			}
		}

		if(battle_config.use_packet_obfuscation) {
			if(sd) {
				cmd = (cmd ^ ((sd->cryptKey >> 16) & 0x7FFF));
			}
			else {
				cmd = (cmd ^ (((( cryptKey[0] * cryptKey[1] ) + cryptKey[2]) >> 16) & 0x7FFF));
			}
			break;
		}

		// �Q�[���p�ȊO�̃p�P�b�g�Ȃ̂Őؒf
		if(cmd >= MAX_PACKET_DB || packet_db[cmd].len == 0) {
			printf("clif_parse: unsupported packet 0x%04x disconnect session #%d\n", cmd, fd);
#ifdef DUMP_UNKNOWN_PACKET
			hex_dump(stdout, RFIFOP(fd,0), RFIFOREST(fd));
			printf("\n");
#endif
			close(fd);
			session[fd]->eof = 1;
			return 0;
		}

		// �F�؂��I����O��0072�ȊO�������̂Őؒf
		if((!sd || sd->state.auth == 0) && packet_db[cmd].func != clif_parse_WantToConnection) {
			close(fd);
			session[fd]->eof = 1;
			return 0;
		}

		// �p�P�b�g�����v�Z
		packet_len = packet_db[cmd].len;
		if(packet_len == -1) {
			if(RFIFOREST(fd) < 4)
				return 0;	// �ϒ��p�P�b�g�Œ����̏��܂Ńf�[�^�����ĂȂ�
			packet_len = RFIFOW(fd,2);
			if(packet_len < 4 || packet_len > 0x8000) {
				printf("clif_parse: invalid packet 0x%04x length %d disconnect session #%d\n", cmd, packet_len, fd);
#ifdef DUMP_UNKNOWN_PACKET
				hex_dump(stdout, RFIFOP(fd,0), RFIFOREST(fd));
				printf("\n");
#endif
				close(fd);
				session[fd]->eof = 1;
				return 0;
			}
		}
		if(RFIFOREST(fd) < packet_len)
			return 0;	// �܂�1�p�P�b�g���f�[�^�������ĂȂ�

		if(battle_config.use_packet_obfuscation || cmd != RFIFOW(fd, 0)) {
			RFIFOW(fd, 0) = cmd;
			if(sd) {
				sd->cryptKey = (( sd->cryptKey * cryptKey[1] ) + cryptKey[2]) & 0xFFFFFFFF;
			}
		}

		if(sd && sd->state.auth == 1 && sd->state.waitingdisconnect) {
			;	// �ؒf�҂��̏ꍇ�p�P�b�g���������Ȃ�
		} else if(sd && sd->bl.prev == NULL && packet_db[cmd].func != clif_parse_LoadEndAck && packet_db[cmd].func != clif_parse_ClientTimeStamp) {
			;	// �u���b�N�Ɍq�����Ă��Ȃ��Ƃ���007d��044a�ȊO�������珈�����Ȃ�
		} else if(packet_db[cmd].func) {
			g_packet_len = packet_len;	// GETPACKETPOS �p�ɕۑ�
			// �p�P�b�g����
			packet_db[cmd].func(fd,sd,cmd);
		} else {
			// �s���ȃp�P�b�g
			printf("clif_parse: unknown packet 0x%04x session #%d\n", cmd, fd);
#ifdef DUMP_UNKNOWN_PACKET
			hex_dump(stdout, RFIFOP(fd,0), packet_len);
			printf("\n");
#endif
		}
		RFIFOSKIP(fd,packet_len);
	}

	return 0;
}

/*==========================================
 * �p�P�b�g�f�[�^�x�[�X�ǂݍ���
 *------------------------------------------
 */
static int packetdb_readdb_sub(char *line, int ln)
{
	int cmd, j;
	char *str[4], *p;
	static struct {
		void (*func)(int fd,struct map_session_data *sd, int cmd);
		const char *name;
	} clif_parse_func[] = {
		{ clif_parse_WantToConnection,            "wanttoconnection"          },
		{ clif_parse_LoadEndAck,                  "loadendack"                },
		{ clif_parse_TickSend,                    "ticksend"                  },
		{ clif_parse_WalkToXY,                    "walktoxy"                  },
		{ clif_parse_QuitGame,                    "quitgame"                  },
		{ clif_parse_GetCharNameRequest,          "getcharnamerequest"        },
		{ clif_parse_GlobalMessage,               "globalmessage"             },
		{ clif_parse_MapMove,                     "mapmove"                   },
		{ clif_parse_ChangeDir,                   "changedir"                 },
		{ clif_parse_Emotion,                     "emotion"                   },
		{ clif_parse_Emotion,                     "emotion2"                  },
		{ clif_parse_HowManyConnections,          "howmanyconnections"        },
		{ clif_parse_ActionRequest,               "actionrequest"             },
		{ clif_parse_Restart,                     "restart"                   },
		{ clif_parse_Wis,                         "wis"                       },
		{ clif_parse_GMmessage,                   "gmmessage"                 },
		{ clif_parse_TakeItem,                    "takeitem"                  },
		{ clif_parse_DropItem,                    "dropitem"                  },
		{ clif_parse_UseItem,                     "useitem"                   },
		{ clif_parse_EquipItem,                   "equipitem"                 },
		{ clif_parse_UnequipItem,                 "unequipitem"               },
		{ clif_parse_NpcClicked,                  "npcclicked"                },
		{ clif_parse_NpcBuySellSelected,          "npcbuysellselected"        },
		{ clif_parse_NpcBuyListSend,              "npcbuylistsend"            },
		{ clif_parse_NpcSellListSend,             "npcselllistsend"           },
		{ clif_parse_NpcPointShopOpen,            "npcpointshopopen"          },
		{ clif_parse_NpcPointShopClose,           "npcpointshopclose"         },
		{ clif_parse_NpcPointShopItemList,        "npcpointshopitemlist"      },
		{ clif_parse_NpcPointShopBuy,             "npcpointshopbuy"           },
		{ clif_parse_CreateChatRoom,              "createchatroom"            },
		{ clif_parse_ChatAddMember,               "chataddmember"             },
		{ clif_parse_ChatRoomStatusChange,        "chatroomstatuschange"      },
		{ clif_parse_ChangeChatOwner,             "changechatowner"           },
		{ clif_parse_KickFromChat,                "kickfromchat"              },
		{ clif_parse_ChatLeave,                   "chatleave"                 },
		{ clif_parse_TradeRequest,                "traderequest"              },
		{ clif_parse_TradeAck,                    "tradeack"                  },
		{ clif_parse_TradeAddItem,                "tradeadditem"              },
		{ clif_parse_TradeOk,                     "tradeok"                   },
		{ clif_parse_TradeCancel,                 "tradecancel"               },
		{ clif_parse_TradeCommit,                 "tradecommit"               },
		{ clif_parse_StopAttack,                  "stopattack"                },
		{ clif_parse_PutItemToCart,               "putitemtocart"             },
		{ clif_parse_GetItemFromCart,             "getitemfromcart"           },
		{ clif_parse_RemoveOption,                "removeoption"              },
		{ clif_parse_ChangeCart,                  "changecart"                },
		{ clif_parse_StatusUp,                    "statusup"                  },
		{ clif_parse_SkillUp,                     "skillup"                   },
		{ clif_parse_UseSkillToId,                "useskilltoid"              },
		{ clif_parse_UseSkillToPos,               "useskilltopos"             },
		{ clif_parse_UseSkillMap,                 "useskillmap"               },
		{ clif_parse_RequestMemo,                 "requestmemo"               },
		{ clif_parse_ProduceMix,                  "producemix"                },
		{ clif_parse_RepairItem,                  "repairitem"                },
		{ clif_parse_WeaponRefine,                "weaponrefine"              },
		{ clif_parse_NpcSelectMenu,               "npcselectmenu"             },
		{ clif_parse_NpcNextClicked,              "npcnextclicked"            },
		{ clif_parse_NpcAmountInput,              "npcamountinput"            },
		{ clif_parse_NpcStringInput,              "npcstringinput"            },
		{ clif_parse_NpcCloseClicked,             "npccloseclicked"           },
		{ clif_parse_ItemIdentify,                "itemidentify"              },
		{ clif_parse_SelectItem,                  "selectitem"                },
		{ clif_parse_AutoSpell,                   "autospell"                 },
		{ clif_parse_UseCard,                     "usecard"                   },
		{ clif_parse_InsertCard,                  "insertcard"                },
		{ clif_parse_SolveCharName,               "solvecharname"             },
		{ clif_parse_ResetChar,                   "resetchar"                 },
		{ clif_parse_LGMmessage,                  "lgmmessage"                },
		{ clif_parse_MoveToKafra,                 "movetokafra"               },
		{ clif_parse_MoveFromKafra,               "movefromkafra"             },
		{ clif_parse_MoveToKafraFromCart,         "movetokafrafromcart"       },
		{ clif_parse_MoveFromKafraToCart,         "movefromkafratocart"       },
		{ clif_parse_CloseKafra,                  "closekafra"                },
		{ clif_parse_CreateParty,                 "createparty"               },
		{ clif_parse_CreateParty2,                "createparty2"              },
		{ clif_parse_PartyInvite,                 "partyinvite"               },
		{ clif_parse_PartyInvite2,                "partyinvite2"              },
		{ clif_parse_ReplyPartyInvite,            "replypartyinvite"          },
		{ clif_parse_ReplyPartyInvite2,           "replypartyinvite2"         },
		{ clif_parse_RefusePartyInvite,           "refusepartyinvite"         },
		{ clif_parse_LeaveParty,                  "leaveparty"                },
		{ clif_parse_RemovePartyMember,           "removepartymember"         },
		{ clif_parse_PartyChangeOption,           "partychangeoption"         },
		{ clif_parse_PartyChangeOption2,          "partychangeoption2"        },
		{ clif_parse_PartyMessage,                "partymessage"              },
		{ clif_parse_CloseVending,                "closevending"              },
		{ clif_parse_VendingListReq,              "vendinglistreq"            },
		{ clif_parse_PurchaseReq,                 "purchasereq"               },
		{ clif_parse_PurchaseReq2,                "purchasereq2"              },
		{ clif_parse_OpenVending,                 "openvending"               },
		{ clif_parse_CreateGuild,                 "createguild"               },
		{ clif_parse_GuildCheckMaster,            "guildcheckmaster"          },
		{ clif_parse_GuildRequestInfo,            "guildrequestinfo"          },
		{ clif_parse_GuildChangePositionInfo,     "guildchangepositioninfo"   },
		{ clif_parse_GuildChangeMemberPosition,   "guildchangememberposition" },
		{ clif_parse_GuildRequestEmblem,          "guildrequestemblem"        },
		{ clif_parse_GuildChangeEmblem,           "guildchangeemblem"         },
		{ clif_parse_GuildChangeEmblem2,          "guildchangeemblem2"        },
		{ clif_parse_GuildChangeNotice,           "guildchangenotice"         },
		{ clif_parse_GuildInvite,                 "guildinvite"               },
		{ clif_parse_GuildReplyInvite,            "guildreplyinvite"          },
		{ clif_parse_GuildLeave,                  "guildleave"                },
		{ clif_parse_GuildExplusion,              "guildexplusion"            },
		{ clif_parse_GuildMessage,                "guildmessage"              },
		{ clif_parse_GuildRequestAlliance,        "guildrequestalliance"      },
		{ clif_parse_GuildReplyAlliance,          "guildreplyalliance"        },
		{ clif_parse_GuildDelAlliance,            "guilddelalliance"          },
		{ clif_parse_GuildOpposition,             "guildopposition"           },
		{ clif_parse_GuildBreak,                  "guildbreak"                },
		{ clif_parse_GuildMemberInfo,             "guildmemberinfo"           },
		{ clif_parse_PetMenu,                     "petmenu"                   },
		{ clif_parse_CatchPet,                    "catchpet"                  },
		{ clif_parse_SelectEgg,                   "selectegg"                 },
		{ clif_parse_SendEmotion,                 "sendemotion"               },
		{ clif_parse_ChangePetName,               "changepetname"             },
		{ clif_parse_GMKick,                      "gmkick"                    },
		{ clif_parse_GMHide,                      "gmhide"                    },
		{ clif_parse_GMReqNoChat,                 "gmreqnochat"               },
		{ clif_parse_GMReqNoChatCount,            "gmreqnochatcount"          },
		{ clif_parse_doridori,                    "doridori"                  },
		{ clif_parse_sn_explosionspirits,         "snexplosionspirits"        },
		{ clif_parse_wisexin,                     "wisexin"                   },
		{ clif_parse_wisexlist,                   "wisexlist"                 },
		{ clif_parse_wisall,                      "wisall"                    },
		{ clif_parse_GMkillall,                   "killall"                   },
		{ clif_parse_GMsummon,                    "summon"                    },
		{ clif_parse_GMitemmonster,               "itemmonster"               },
		{ clif_parse_GMshift,                     "shift"                     },
		{ clif_parse_GMrecall,                    "recall"                    },
		{ clif_parse_GMshift,                     "gmremove"                  },
		{ clif_parse_GMchangemaptype,             "changemaptype"             },
		{ clif_parse_GMrc,                        "gmrc"                      },
		{ clif_parse_GMcheck,                     "gmcheck"                   },
		{ clif_parse_GMcharge,                    "gmcharge"                  },
		{ clif_parse_FriendAddRequest,            "friendaddrequest"          },
		{ clif_parse_FriendAddReply,              "friendaddreply"            },
		{ clif_parse_FriendDeleteRequest,         "frienddeleterequest"       },
		{ clif_parse_clientsetting,               "clientsetting"             },
		{ clif_parse_BabyRequest,                 "babyrequest"               },
		{ clif_parse_BabyReply,                   "babyreply"                 },
		{ clif_parse_PvPInfo,                     "pvpinfo"                   },
		{ clif_parse_RankingBlacksmith,           "rankingblacksmith"         },
		{ clif_parse_RankingAlchemist,            "rankingalchemist"          },
		{ clif_parse_RankingTaekwon,              "rankingtaekwon"            },
		{ clif_parse_RankingPk,                   "rankingpk"                 },
		{ clif_parse_Ranking,                     "ranking"                   },
		{ clif_parse_HomMenu,                     "hommenu"                   },
		{ clif_parse_HomMercWalkMaster,           "hommercwalkmaster"         },
		{ clif_parse_HomMercWalkToXY,             "hommercwalktoxy"           },
		{ clif_parse_HomMercActionRequest,        "hommercactionrequest"      },
		{ clif_parse_ChangeHomName,               "changehomname"             },
		{ clif_parse_MailWinOpen,                 "mailwinopen"               },
		{ clif_parse_ReadMail,                    "readmail"                  },
		{ clif_parse_MailGetAppend,               "mailgetappend"             },
		{ clif_parse_SendMail,                    "sendmail"                  },
		{ clif_parse_RefleshMailBox,              "refleshmailbox"            },
		{ clif_parse_SendMailSetAppend,           "sendmailsetappend"         },
		{ clif_parse_DeleteMail,                  "deletemail"                },
		{ clif_parse_ReturnMail,                  "returnmail"                },
		{ clif_parse_FeelSaveAck,                 "feelsaveack"               },
		{ clif_parse_Making,                      "making"                    },
		{ clif_parse_HotkeySave,                  "hotkeysave"                },
		{ clif_parse_HotkeySave2,                 "hotkeysave2"               },
		{ clif_parse_Revive,                      "revive"                    },
		{ clif_parse_MercMenu,                    "mercmenu"                  },
		{ clif_parse_PartyEquipWindow,            "partyequipwindow"          },
		{ clif_parse_Config,                      "config"                    },
		{ clif_parse_HuntingList,                 "huntinglist"               },
		{ clif_parse_BattleMessage,               "battlemessage"             },
		{ clif_parse_PartyChangeLeader,           "partychangeleader"         },
		{ clif_parse_GmFullstrip,                 "gmfullstrip"               },
		{ clif_parse_PartyBookingRegisterReq,     "bookingregreq"             },
		{ clif_parse_PartyBookingSearchReq,       "bookingsearchreq"          },
		{ clif_parse_PartyBookingUpdateReq,       "bookingupdatereq"          },
		{ clif_parse_PartyBookingDeleteReq,       "bookingdelreq"             },
		{ clif_parse_SelectSkill,                 "selectskill"               },
		{ clif_parse_ConvertItem,                 "convertitem"               },
		{ clif_parse_QuestState,                  "queststate"                },
		{ clif_parse_ProgressBar,                 "progressbar"               },
		{ clif_parse_OpenBuyingStoreReq,          "openbuyingstorereq"        },
		{ clif_parse_CloseBuyingStoreReq,         "closebuyingstorereq"       },
		{ clif_parse_ClickBuyingStoreReq,         "clickbuyingstorereq"       },
		{ clif_parse_SellBuyingStoreReq,          "sellbuyingstorereq"        },
		{ clif_parse_GMrecall2,                   "recall2"                   },
		{ clif_parse_GMremove2,                   "gmremove2"                 },
		{ clif_parse_RegBattleGround,             "regbattleground"           },
		{ clif_parse_MoveItem,                    "moveitem"                  },
		{ clif_parse_PartyBookingRegisterReq2,    "bookingregreq2"            },
		{ clif_parse_PartyBookingSearchReq2,      "bookingsearchreq2"         },
		{ clif_parse_PartyBookingDeleteReq2,      "bookingdelreq2"            },
		{ clif_parse_PartyBookingUpdateReq2,      "bookingupdatereq2"         },
		{ clif_parse_PartyBookingIgnoreReq,       "bookingignorereq"          },
		{ clif_parse_PartyBookingJoinPartyReq,    "bookingjoinpartyreq"       },
		{ clif_parse_PartyBookingSummonMember,    "bookingsummonmember"       },
		{ clif_parse_PartyBookingJoinPartyCancel, "bookingjoinpartycancel"    },
		{ clif_parse_BlockingPlayCancel,          "blockplaycancel"           },
		{ clif_parse_ClanMessage,                 "clanmessage"               },
		{ clif_parse_BankingDepositReq,           "bankdepositreq"            },
		{ clif_parse_BankingWithdrawReq,          "bankwithdrawreq"           },
		{ clif_parse_BankingInfoReq,              "bankinforeq"               },
		{ clif_parse_SellMarketReq,               "sellmarketreq"             },
		{ clif_parse_CloseMarketReq,              "closemarketreq"            },
		{ clif_parse_ClientTimeStamp,             "clienttimestamp"           },
		{ clif_parse_OpenRoDEX,                   "openrodex"                 },
		{ clif_parse_CloseRoDEX,                  "closerodex"                },
		{ clif_parse_ReadRoDEX,                   "readrodex"                 },
		{ clif_parse_WriteRoDEX,                  "writerodex"                },
		{ clif_parse_NextListRoDEX,               "nextlistrodex"             },
		{ clif_parse_RefreshRoDEX,                "refreshrodex"              },
		{ clif_parse_ZenyfromRoDEX,               "zenyfromrodex"             },
		{ clif_parse_ItemfromRoDEX,               "itemfromrodex"             },
		{ clif_parse_DeleteRoDEX,                 "deleterodex"               },
		{ clif_parse_CancelWriteRoDEX,            "cancelwriterodex"          },
		{ clif_parse_AdditemRoDEX,                "additemrodex"              },
		{ clif_parse_DelitemRoDEX,                "delitemrodex"              },
		{ clif_parse_OpenWriteRoDEX,              "openwriterodex"            },
		{ clif_parse_HotkeyRotate,                "hotkeyrotate"              },
		{ clif_parse_HotkeyRotate2,               "hotkeyrotate2"             },
		{ clif_parse_OpenRoulette,                "openroulette"              },
		{ clif_parse_CloseRoulette,               "closeroulette"             },
		{ clif_parse_ChangeTitleReq,              "changetitlereq"            },
		{ clif_parse_OneClickItemidentify,        "oneclickitemidentify"      },
		{ clif_parse_GetRewardReq,                "getrewardreq"              },
		{ clif_parse_OpenUi,                      "openui"                    },
		{ clif_parse_CameraInfo,                  "camerainfo"                },
		{ clif_parse_ResetCooldown,               "resetcooldown"             },
		{ clif_parse_AddEquipSwitch,              "addequipswitch"            },
		{ clif_parse_DelEquipSwitch,              "delequipswitch"            },
		{ clif_parse_EquipSwitchReq,              "equipswitchreq"            },
		{ clif_parse_EquipSwitchReqSingle,        "equipswitchreqsingle"      },
		{ clif_parse_ChangeDress,                 "changedress"               },
		{ clif_parse_AttendanceReq,               "attendancereq"             },
		{ clif_parse_PrivateAirshipReq,           "privateairshipreq"         },
		{ clif_parse_Ping,                        "ping"                      },
		{ clif_parse_MemorialCommand,             "memorialcommand"           },
		{ clif_parse_InventoryExpantion,          "inventoryexpantion"        },
		{ clif_parse_PetEvolution,                "petevolution"              },
		{ clif_parse_StartUseSkillToId,           "startuseskilltoid"         },
		{ clif_parse_StopUseSkillToId,            "stopuseskilltoid"          },
		{ clif_parse_CloseLapineUpgrade,          "closelapineupgrade"        },
		{ clif_parse_LapineUpgradeAck,            "lapineupgradeack"          },
		{ clif_parse_MountOff,                    "mountoff"                  },
		{ clif_parse_CashMarketOpen,              "cashmarketopen"            },
		{ clif_parse_AdventureGuide,              "adventureguide"            },
		{ clif_parse_UnequipItemAll,              "unequipitemall"            },
		{ clif_parse_UnequipItemAll2,             "unequipitemall2"           },
		{ clif_parse_TStatusUp,                   "tstatusup"                 },
		{ NULL,                                   NULL                        },
	};

	memset(str, 0, sizeof(str));

	for(j = 0, p = line; j < 4 && p; j++) {
		str[j] = p;
		p = strchr(p, ',');
		if(p) *p++ = 0;
	}
	if(str[0] == NULL)
		return 0;

	cmd = strtol(str[0], (char **)NULL, 0);
	if(cmd <= 0 || cmd >= MAX_PACKET_DB)
		return 0;

	if(str[1] == NULL) {
		printf("packet_db: 0x%04x packet len error (line %d)\n", cmd, ln);
		return 1;
	}
	packet_db[cmd].len = atoi(str[1]);

	if(str[2] == NULL) {
		return 0;
	}
	p = strchr(str[2], '\n');
	if(p)
		*p = '\0';

	for(j = 0; j <sizeof(clif_parse_func)/sizeof(clif_parse_func[0]); j++) {
		if(clif_parse_func[j].name == NULL) {
			printf("packet_db: 0x%04x no func %s (line %d)\n", cmd, str[2], ln);
			return 1;
		}
		if(strcmp(str[2], clif_parse_func[j].name) == 0) {
			packet_db[cmd].func = clif_parse_func[j].func;
			break;
		}
	}
	if(str[3] == NULL) {
		printf("packet_db: 0x%04x packet error (line %d)\n", cmd, ln);
		return 1;
	}
	for(j = 0, p = str[3]; p; j++) {
		char *p2 = p;

		if(j >= sizeof(packet_db[0].pos)/sizeof(packet_db[0].pos[0])) {
			printf("packet_db: 0x%04x pos overflow (line %d)\n", cmd, ln);
			return 1;
		}
		p = strchr(p, ':');
		if(p) *p++ = 0;

		packet_db[cmd].pos[j] = atoi(p2);
	}

	//if(packet_db[cmd].len > 2 && packet_db[cmd].pos[0] == 0)
	//	printf("packet_db:? %d 0x%04x %d %s %p\n", ln, cmd, packet_db[cmd].len, str[2], packet_db[cmd].func);

	return 0;
}

static void packetdb_readdb(void)
{
	FILE *fp;
	char line[1024], w1[1024], w2[1024];
	int ln = 0, count = 0;
	const char *filename = "db/packet_db.txt";
	struct {
		int version, skip;
		int count, size;
		unsigned int crypt[3];
		struct stock_line {
			char line[1024];
			int ln;
		} *data;
	} stock;

	memset(packet_db, 0, sizeof(packet_db));
	memset(&stock, 0, sizeof(stock));
	memset(cryptKey, 0, sizeof(cryptKey));

	if( (fp = fopen(filename, "r")) == NULL ) {
		printf("packetdb_readdb: open [%s] failed !\n", filename);
		exit(1);
	}

	while(fgets(line,1020,fp)) {
		ln++;
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0] == '/' && line[1] == '/')
			continue;

		if(sscanf(line,"%1023[^:]: %1023[^\r\n]", w1, w2) == 2) {
			if(strcasecmp(w1, "#packet_ver") == 0) {
				int ver = atoi(w2);
				if(ver <= PACKETVER && ver >= stock.version) {
					// PACKETVER�ɍł��߂����t�����������̂ŌÂ�����j������
					memset(stock.data, 0, sizeof(struct stock_line) * stock.size);
					memset(stock.crypt, 0, sizeof(stock.crypt));
					stock.count   = 0;
					stock.version = ver;
					stock.skip    = 0;
				} else {
					stock.skip = 1;
				}
				continue;
			}
			if(strcasecmp(w1, "#packet_key") == 0) {
				int i;
				char *str[3], *p;
				for(i = 0, p = w2; i < 3 && p; i++) {
					str[i] = p;
					p = strchr(p, ',');
					if(p) *p++ = 0;
				}
				if(str[0] == NULL || str[1] == NULL || str[2] == NULL)
					continue;
				if(stock.version > 0) {
					stock.crypt[0] = strtol(str[0], (char **)NULL, 0);
					stock.crypt[1] = strtol(str[1], (char **)NULL, 0);
					stock.crypt[2] = strtol(str[2], (char **)NULL, 0);
				} else {
					cryptKey[0] = strtol(str[0], (char **)NULL, 0);
					cryptKey[1] = strtol(str[1], (char **)NULL, 0);
					cryptKey[2] = strtol(str[2], (char **)NULL, 0);
				}
				continue;
			}
		}
		if(stock.skip)
			continue;

		if(stock.version > 0) {
			// packet_ver�̒�`������̂Ŏ擾�s���ꎞ�I�ɕۑ����Ă���
			if(stock.count >= stock.size) {
				stock.size += 16;
				stock.data = (struct stock_line *)aRealloc(stock.data, sizeof(struct stock_line) * stock.size);
				memset(stock.data + (stock.size - 16), 0, sizeof(struct stock_line) * 16);
			}
			strncpy(stock.data[stock.count].line, line, sizeof(stock.data[0].line) - 1);
			stock.data[stock.count].ln = ln;
			stock.count++;
		} else {
			// ���̂܂ܓǂݍ���
			if(packetdb_readdb_sub(line, ln)) {
				aFree(stock.data);
				exit(1);
			}
			count++;
		}
	}
	fclose(fp);

	// �ۑ����Ă�����packet_ver�̏��ŏ㏑��
	if(stock.version > 0) {
		int i;
		for(i = 0; i < stock.count; i++) {
			if(packetdb_readdb_sub(stock.data[i].line, stock.data[i].ln)) {
				aFree(stock.data);
				exit(1);
			}
		}
		memcpy(cryptKey,stock.crypt,sizeof(cryptKey));
		count += stock.count;
	}

	printf("read %s done (count=%d)\n", filename, count);
	if(stock.version > 0) {
		printf("use packet_ver: %d\n", stock.version);
		printf("use packet_key: 0x%08x,0x%08x,0x%08x\n", stock.crypt[0], stock.crypt[1], stock.crypt[2]);
	}
	aFree(stock.data);

	return;
}

/*==========================================
 * �p�P�b�g�f�[�^�x�[�X�ǂݍ���
 *------------------------------------------
 */
void packetdb_insert_packet(char *line)
{
	if(line == NULL || !line[0])
		return;

	if(packetdb_readdb_sub(line, 0)) {
		exit(1);
	}

	return;
}

/*==========================================
 * �p�P�b�g�f�[�^�x�[�X�L�[�ǂݍ���
 *------------------------------------------
 */
void packetdb_insert_packet_key(unsigned int key1, unsigned int key2, unsigned int key3)
{
	cryptKey[0] = key1;
	cryptKey[1] = key2;
	cryptKey[2] = key3;

	return;
}

/*==========================================
 * Web�`���b�g�V�X�e��
 *------------------------------------------
 */
#define MAX_CHAT_MESSAGE 15

static char webchat_message[MAX_CHAT_MESSAGE][256*4+1];
static int webchat_pos = 0;

void clif_webchat_message(const char* head,const char *mes1,const char *mes2)
{
	int  i;
	char *p;
	char temp[512];

	snprintf(temp, sizeof(temp), "%s %s : %s", head, mes1, mes2);
	p = httpd_quote_meta(temp);

	// �d�����b�Z�[�W������ꍇ����������
	for(i = 0; i < MAX_CHAT_MESSAGE; i++) {
		if(!strcmp(p, webchat_message[i])) {
			aFree(p);
			return;
		}
	}
	clif_onlymessage(temp,strlen(temp) + 1);

	strncpy(webchat_message[webchat_pos], p, sizeof(webchat_message[0]));
	webchat_message[webchat_pos][sizeof(webchat_message[0])-1] = '\0';
	if(++webchat_pos >= MAX_CHAT_MESSAGE)
		webchat_pos = 0;

	aFree(p);

	return;
}

void clif_webchat(struct httpd_session_data* sd,const char* url)
{
	char *name1 = httpd_get_value(sd,"name");
	char *name2 = httpd_binary_encode(name1);
	char *name3 = httpd_quote_meta(name1);
	char *mes   = httpd_get_value(sd,"mes");
	const char *err = NULL;
	char buf[8192];
	char *p = buf;

	do {
		int i, j;
		if(get_atcommand_level(AtCommand_MesWeb) > 0) {
			err = "Chat system disabled."; break;
		} else if(!name1[0]) {
			err = "Please input your name."; break;
		} else if(strlen(name1) > 24) {
			err = "Name is too long."; break;
		} else if(strlen(mes) > 100) {
			err = "Message is too long."; break;
		} else if(mes[0]) {
			if(httpd_get_method(sd) != HTTPD_METHOD_POST) {
				// POST�ȊO�̏������݂͂��f��
				err = "Illegal request."; break;
			}
			clif_webchat_message("[web]",name1,mes);
		}
		// print form
		// �R�O�b���ƂɍX�V
		p += sprintf(p,"<html><head>\n");
		p += sprintf(p,"<meta http-equiv=\"Refresh\" content=\"30;URL=/chat?name=%s\">\n",name2);
		p += sprintf(p,"<title>Auriga Chat</title></head>\n\n<body>\n");
		p += sprintf(p,"<form action=\"/chat\" method=\"POST\">\n");
		p += sprintf(p,"%s : <input type=\"text\" name=\"mes\" size=\"32\">\n",name3);
		p += sprintf(p,"<input type=\"hidden\" name=\"name\" value=\"%s\">\n",name3);
		p += sprintf(p,"<input type=\"submit\" value=\"Send!\">\n");
		p += sprintf(p,"</form>\n");

		i = webchat_pos;
		for(j = 0; j < MAX_CHAT_MESSAGE; j++) {
			if(webchat_message[i][0]) {
				p += sprintf(p,"%s<br>\n",webchat_message[i]);
			}
			if(++i >= MAX_CHAT_MESSAGE)
				i = 0;
		}
		p += sprintf(p,"</body></html>\n");
		httpd_send(sd,200,"text/html",(int)(p - buf),buf);
	} while(0);

	if(err != NULL) {
		httpd_send(sd,200,"text/html",(int)strlen(err),err);
	}
	aFree(name1);
	aFree(name2);
	aFree(name3);
	aFree(mes);

	return;
}

/*==========================================
 * �I��
 *------------------------------------------
 */
void do_final_clif(void)
{
	delete_session(map_fd);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void do_init_clif(void)
{
	int i;

	//packetdb_readdb();
	memset(packet_db, 0, sizeof(packet_db));
	memset(cryptKey, 0, sizeof(cryptKey));
	luascript_addscript("db/packet_db.lua");

	set_defaultparse(clif_parse);
	set_sock_destruct(clif_disconnect);
	for(i=0;i<10;i++){
		if ((map_fd = make_listen_port(map_port, listen_ip)))
			break;
#ifdef WINDOWS
		Sleep(20);
#else
		sleep(20);
#endif
	}
	if(i==10){
		printf("can't bind game port\n");
		exit(1);
	}
	memset(webchat_message, 0, sizeof(webchat_message));

	add_timer_func_list(clif_waitclose);
	add_timer_func_list(clif_clearchar_delay_sub);

#if PACKETVER >= 20190403
	add_timer_func_list(clif_pingtimer);
	if (battle_config.ping_timer_interval != 0)
		add_timer_interval(gettick() + battle_config.ping_timer_interval * 1000, clif_pingtimer, 0, NULL, battle_config.ping_timer_interval * 1000);
#endif

	return;
}

