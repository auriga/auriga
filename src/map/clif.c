#define DUMP_UNKNOWN_PACKET	1

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#ifndef _WIN32
	#include <unistd.h>
	#include <stdarg.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
#else
	#include <winsock.h>
#endif

#include <time.h>

#include "socket.h"
#include "timer.h"
#include "malloc.h"
#include "version.h"
#include "nullpo.h"
#include "httpd.h"
#include "grfio.h"
#include "utils.h"

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

#ifdef MEMWATCH
#include "memwatch.h"
#endif

const unsigned char grounddrift_unit_id[] = {0xc2,0xbe,0xc0,0xbf,0xc1};	//グラウンドドリフト個別エフェクト

/* パケットデータベース */
struct packet_db packet_db[MAX_PACKET_DB];

// local define
enum {
	ALL_CLIENT,
	ALL_SAMEMAP,
	AREA,
	AREA_WOS,
	AREA_WOC,
	AREA_WOSC,
	AREA_CHAT_WOC,
	CHAT,
	CHAT_WOS,
	PARTY,
	PARTY_WOS,
	PARTY_SAMEMAP,
	PARTY_SAMEMAP_WOS,
	PARTY_AREA,
	PARTY_AREA_WOS,
	GUILD,
	GUILD_WOS,
	GUILD_SAMEMAP_WOS,
	SELF
};

#define WBUFPOS(p,pos,x,y) { unsigned char *__p = (p); __p+=(pos); __p[0] = (unsigned char)((x)>>2); __p[1] = (unsigned char)(((x)<<6) | (((y)>>4)&0x3f)); __p[2] = (unsigned char)((y)<<4); }
#define WBUFPOS2(p,pos,x0,y0,x1,y1) { unsigned char *__p = (p); __p+=(pos); __p[0] = (unsigned char)((x0)>>2); __p[1] = (unsigned char)(((x0)<<6) | (((y0)>>4)&0x3f)); __p[2] = (unsigned char)(((y0)<<4) | (((x1)>>6)&0x0f)); __p[3] = (unsigned char)(((x1)<<2) | (((y1)>>8)&0x03)); __p[4] = (unsigned char)(y1); }

#define WFIFOPOS(fd,pos,x,y) { WBUFPOS (WFIFOP(fd,pos),0,x,y); }
#define WFIFOPOS2(fd,pos,x0,y0,x1,y1) { WBUFPOS2(WFIFOP(fd,pos),0,x0,y0,x1,y1); }

static char map_ip_str[16];
static in_addr_t map_ip;
static int map_port = 5121;
static int map_fd;


static int g_packet_len = 0;
#define GETPACKETPOS(cmd,idx)  ( packet_db[cmd].pos[idx] + ( ( packet_db[cmd].pos[idx] < 0 )? g_packet_len : 0 ) )

/*==========================================
 * map鯖のip設定
 *------------------------------------------
 */
void clif_setip(char *ip)
{
	memcpy(map_ip_str,ip,16);
	map_ip=inet_addr(map_ip_str);

	return;
}

/*==========================================
 * map鯖のport設定
 *------------------------------------------
 */
void clif_setport(int port)
{
	map_port=port;

	return;
}

/*==========================================
 * map鯖のip読み出し
 *------------------------------------------
 */
in_addr_t clif_getip(void)
{
	return map_ip;
}

/*==========================================
 * map鯖のport読み出し
 *------------------------------------------
 */
int clif_getport(void)
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
		if(session[i] && (sd=session[i]->session_data) && sd->state.auth
			&& !(battle_config.hide_GM_session && pc_isGM(sd)) )
			users++;
	}

	return users;
}

/*==========================================
 * 全てのclientに対してfunc()実行
 *------------------------------------------
 */
int clif_foreachclient(int (*func)(struct map_session_data*,va_list),...)
{
	int i;
	va_list ap;
	struct map_session_data *sd;

	va_start(ap,func);
	for(i=0;i<fd_max;i++){
		if(
			session[i] && session[i]->func_parse == clif_parse &&
			(sd=session[i]->session_data) && sd->state.auth &&
			!sd->state.waitingdisconnect
		) {
			func(sd,ap);
		}
	}
	va_end(ap);

	return 0;
}

/*==========================================
 * clif_sendでAREA*指定時用
 *------------------------------------------
 */
int clif_send_sub(struct block_list *bl,va_list ap)
{
	unsigned char *buf;
	int len;
	struct block_list *src_bl;
	int type, fd;
	short *src_option = NULL;
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
	src_option = status_get_option(src_bl);
	//看破
	if(src_option && bl != src_bl && ((*src_option)&6) &&
		(sd->sc_data[SC_TIGEREYE].timer!=-1 || sd->infinite_tigereye || sd->race==4 || sd->race==6)
		&&(src_bl->type==BL_PC || src_bl->type==BL_MOB || src_bl->type==BL_PET || src_bl->type==BL_HOM) )
	{
		//optionの修正
		switch(((unsigned short*)buf)[0])
		{
#if PACKETVER < 7
			case 0x119:
				WFIFOW(fd,6)  =  1;
				WFIFOW(fd,10) &=~6;
				break;
#else
			case 0x229:
				WFIFOW(fd,6)  =  1;
				WFIFOL(fd,10) &=~6;
				break;
#endif

#if PACKETVER < 4
			case 0x78:
			case 0x79:
			case 0x7b:
				WFIFOW(fd,8)  =  1;
				WFIFOW(fd,12) &=~6;
				break;
#elif PACKETVER < 7
			case 0x1d8:
			case 0x1d9:
			case 0x1da:
				WFIFOW(fd,8)  =  1;
				WFIFOW(fd,12) &=~6;
				break;
#else
			case 0x22a:
			case 0x22b:
			case 0x22c:
				WFIFOW(fd,8)  =  1;
				WFIFOL(fd,12) &=~6;
				break;
#endif
		}
	}
	WFIFOSET(fd,len);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_send(unsigned char *buf, int len, struct block_list *bl, int type)
{
	int i;
	struct map_session_data *sd = NULL;
	int x0=0,x1=0,y0=0,y1=0;

	if( type != ALL_CLIENT ){
		nullpo_retv(bl);
	}
	nullpo_retv(buf);

	switch(type){
	case ALL_CLIENT:	// 全クライアントに送信
		for(i=0;i<fd_max;i++){
			if(session[i] && (sd=session[i]->session_data) && sd->state.auth){
				memcpy(WFIFOP(i,0),buf,len);
				WFIFOSET(i,len);
			}
		}
		break;
	case ALL_SAMEMAP:	// 同じマップの全クライアントに送信
		for(i=0;i<fd_max;i++){
			if(session[i] && (sd=session[i]->session_data) && sd->state.auth &&
			   sd->bl.m == bl->m){
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

	case PARTY_AREA:		// 同じ画面内の全パーティーメンバに送信
	case PARTY_AREA_WOS:		// 自分以外の同じ画面内の全パーティーメンバに送信
		x0=bl->x-AREA_SIZE;
		y0=bl->y-AREA_SIZE;
		x1=bl->x+AREA_SIZE;
		y1=bl->y+AREA_SIZE;
	case PARTY:			// 全パーティーメンバに送信
	case PARTY_WOS:			// 自分以外の全パーティーメンバに送信
	case PARTY_SAMEMAP:		// 同じマップの全パーティーメンバに送信
	case PARTY_SAMEMAP_WOS:		// 自分以外の同じマップの全パーティーメンバに送信
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
					if(type!=PARTY && type!=PARTY_WOS && bl->m!=sd->bl.m)	// マップチェック
						continue;
					if((type==PARTY_AREA || type==PARTY_AREA_WOS) &&
						(sd->bl.x<x0 || sd->bl.y<y0 ||
						 sd->bl.x>x1 || sd->bl.y>y1 ) )
						continue;

					memcpy(WFIFOP(sd->fd,0),buf,len);
					WFIFOSET(sd->fd,len);
//					if(battle_config.etc_log)
//						printf("send party %d %d %d\n",p->party_id,i,flag);
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
			printf("clif_send まだ作ってないよー\n");
		return;
	}

	return;
}

//
// パケット作って送信
//
/*==========================================
 *
 *------------------------------------------
 */
void clif_authok(struct map_session_data *sd)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;

	WFIFOW(fd,0)=0x73;
	WFIFOL(fd,2)=gettick();
	WFIFOPOS(fd,6,sd->bl.x,sd->bl.y);
	WFIFOB(fd,9)=5;
	WFIFOB(fd,10)=5;
	WFIFOSET(fd,packet_db[0x73].len);

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
static void clif_set009e(struct flooritem_data *fitem, unsigned char *buf)
{
	int view;

	nullpo_retv(fitem);

	//009e <ID>.l <name ID>.w <identify flag>.B <X>.w <Y>.w <subX>.B <subY>.B <amount>.w
	WBUFW(buf,0)=0x9e;
	WBUFL(buf,2)=fitem->bl.id;
	if((view = itemdb_viewid(fitem->item_data.nameid)) > 0)
		WBUFW(buf,6)=view;
	else
		WBUFW(buf,6)=fitem->item_data.nameid;
	WBUFB(buf,8)=fitem->item_data.identify;
	WBUFW(buf,9)=fitem->bl.x;
	WBUFW(buf,11)=fitem->bl.y;
	WBUFB(buf,13)=(unsigned char)fitem->subx;
	WBUFB(buf,14)=(unsigned char)fitem->suby;
	WBUFW(buf,15)=fitem->item_data.amount;

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_dropflooritem(struct flooritem_data *fitem)
{
	char buf[32];

	nullpo_retv(fitem);

	if(fitem->item_data.nameid <= 0)
		return;

	clif_set009e(fitem,buf);
	clif_send(buf,packet_db[0x9e].len,&fitem->bl,AREA);

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

	if(fd==0){
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
	clif_send(buf,packet_db[0x80].len,bl,type==1 ? AREA : AREA_WOS);

	return;
}

static int clif_clearchar_delay_sub(int tid,unsigned int tick,int id,int data)
{
	struct block_list *bl = (struct block_list *)id;

	clif_clearchar(bl,data);
	aFree(bl);

	return 0;
}

int clif_clearchar_delay(unsigned int tick,struct block_list *bl,int type)
{
	struct block_list *tmpbl=(struct block_list *)aCalloc(1,sizeof(struct block_list));
	memcpy(tmpbl,bl,sizeof(struct block_list));
	add_timer2(tick,clif_clearchar_delay_sub,(int)tmpbl,type,TIMER_FREE_ID);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_clearchar_id(int id, unsigned char type, int fd)
{
	unsigned char buf[16];

	WBUFW(buf,0) = 0x80;
	WBUFL(buf,2) = id;
	WBUFB(buf,6) = type;
	memcpy(WFIFOP(fd,0),buf,7);
	WFIFOSET(fd,packet_db[0x80].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static int clif_set0078(struct map_session_data *sd,unsigned char *buf)
{
	nullpo_retr(0, sd);

#if PACKETVER < 4
	WBUFW(buf,0)=0x78;
	WBUFL(buf,2)=sd->bl.id;
	WBUFW(buf,6)=sd->speed;
	WBUFW(buf,8)=sd->opt1;
	WBUFW(buf,10)=sd->opt2;
	WBUFW(buf,12)=sd->status.option;
	WBUFW(buf,14)=sd->view_class;
	WBUFW(buf,16)=sd->status.hair;
	if(sd->view_class != 22 && sd->view_class != 26)
		WBUFW(buf,18)=sd->status.weapon;
	else
		WBUFW(buf,18)=0;
	WBUFW(buf,20)=sd->status.head_bottom;
	WBUFW(buf,22)=sd->status.shield;
	WBUFW(buf,24)=sd->status.head_top;
	WBUFW(buf,26)=sd->status.head_mid;
	WBUFW(buf,28)=sd->status.hair_color;
	WBUFW(buf,30)=sd->status.clothes_color;
	WBUFW(buf,32)=sd->head_dir;
	WBUFL(buf,34)=sd->status.guild_id;
	WBUFL(buf,38)=sd->guild_emblem_id;
	WBUFW(buf,42)=sd->status.manner;
	WBUFB(buf,44)=sd->status.karma;
	WBUFB(buf,45)=sd->sex;
	WBUFPOS(buf,46,sd->bl.x,sd->bl.y);
	WBUFB(buf,48)|=sd->dir&0x0f;
	WBUFB(buf,49)=5;
	WBUFB(buf,50)=5;
	WBUFB(buf,51)=sd->state.dead_sit;
	WBUFW(buf,52)=(sd->status.base_level>99)?99:sd->status.base_level;

	return packet_db[0x78].len;
#elif PACKETVER < 7
	WBUFW(buf,0)=0x1d8;
	WBUFL(buf,2)=sd->bl.id;
	WBUFW(buf,6)=sd->speed;
	WBUFW(buf,8)=sd->opt1;
	WBUFW(buf,10)=sd->opt2;
	WBUFW(buf,12)=sd->status.option;
	WBUFW(buf,14)=sd->view_class;
	WBUFW(buf,16)=sd->status.hair;
	if(sd->equip_index[9] >= 0
	&& sd->inventory_data[sd->equip_index[9]]
	&& sd->view_class != 22
	&& sd->view_class != 26) {
		if(sd->inventory_data[sd->equip_index[9]]->view_id > 0)
			WBUFW(buf,18)=sd->inventory_data[sd->equip_index[9]]->view_id;
		else
			WBUFW(buf,18)=sd->status.inventory[sd->equip_index[9]].nameid;
	}
	else
		WBUFW(buf,18)=0;
	if(sd->equip_index[8] >= 0
	&& sd->equip_index[8] != sd->equip_index[9]
	&& sd->inventory_data[sd->equip_index[8]]
	&& sd->view_class != 22
	&& sd->view_class != 26) {
		if(sd->inventory_data[sd->equip_index[8]]->view_id > 0)
			WBUFW(buf,20)=sd->inventory_data[sd->equip_index[8]]->view_id;
		else
			WBUFW(buf,20)=sd->status.inventory[sd->equip_index[8]].nameid;
	}
	else
		WBUFW(buf,20)=0;
	WBUFW(buf,22)=sd->status.head_bottom;
	WBUFW(buf,24)=sd->status.head_top;
	WBUFW(buf,26)=sd->status.head_mid;
	WBUFW(buf,28)=sd->status.hair_color;
	WBUFW(buf,30)=sd->status.clothes_color;
	WBUFW(buf,32)=sd->head_dir;
	WBUFL(buf,34)=sd->status.guild_id;
	WBUFW(buf,38)=sd->guild_emblem_id;
	WBUFW(buf,40)=sd->status.manner;
	WBUFW(buf,42)=sd->opt3;
	WBUFB(buf,44)=(unsigned char)sd->status.karma;
	WBUFB(buf,45)=sd->sex;
	WBUFPOS(buf,46,sd->bl.x,sd->bl.y);
	WBUFB(buf,48)|=sd->dir&0x0f;
	WBUFB(buf,49)=5;
	WBUFB(buf,50)=5;
	WBUFB(buf,51)=sd->state.dead_sit;
	WBUFW(buf,52)=(sd->status.base_level>99)?99:sd->status.base_level;

	return packet_db[0x1d8].len;
#else
	WBUFW(buf,0)=0x22a;
	WBUFL(buf,2)=sd->bl.id;
	WBUFW(buf,6)=sd->speed;
	WBUFW(buf,8)=sd->opt1;
	WBUFW(buf,10)=sd->opt2;
	WBUFL(buf,12)=sd->status.option;
	WBUFW(buf,16)=sd->view_class;
	WBUFW(buf,18)=sd->status.hair;
	if(sd->equip_index[9] >= 0
	&& sd->inventory_data[sd->equip_index[9]]
	&& sd->view_class != 22
	&& sd->view_class != 26) {
		if(sd->inventory_data[sd->equip_index[9]]->view_id > 0)
			WBUFW(buf,20)=sd->inventory_data[sd->equip_index[9]]->view_id;
		else
			WBUFW(buf,20)=sd->status.inventory[sd->equip_index[9]].nameid;
	}
	else
		WBUFW(buf,20)=0;
	if(sd->equip_index[8] >= 0
	&& sd->equip_index[8] != sd->equip_index[9]
	&& sd->inventory_data[sd->equip_index[8]]
	&& sd->view_class != 22
	&& sd->view_class != 26) {
		if(sd->inventory_data[sd->equip_index[8]]->view_id > 0)
			WBUFW(buf,22)=sd->inventory_data[sd->equip_index[8]]->view_id;
		else
			WBUFW(buf,22)=sd->status.inventory[sd->equip_index[8]].nameid;
	}
	else
		WBUFW(buf,22)=0;
	WBUFW(buf,24)=sd->status.head_bottom;
	WBUFW(buf,26)=sd->status.head_top;
	WBUFW(buf,28)=sd->status.head_mid;
	WBUFW(buf,30)=sd->status.hair_color;
	WBUFW(buf,32)=sd->status.clothes_color;
	WBUFW(buf,34)=sd->head_dir;
	WBUFL(buf,36)=sd->status.guild_id;
	WBUFW(buf,40)=sd->guild_emblem_id;
	WBUFW(buf,42)=sd->status.manner;
	WBUFL(buf,44)=sd->opt3;
	WBUFB(buf,48)=(unsigned char)sd->status.karma;
	WBUFB(buf,49)=sd->sex;
	WBUFPOS(buf,50,sd->bl.x,sd->bl.y);
	WBUFB(buf,52)|=sd->dir&0x0f;
	WBUFB(buf,53)=5;
	WBUFB(buf,54)=5;
	WBUFB(buf,55)=sd->state.dead_sit;
	WBUFW(buf,56)=(sd->status.base_level>99)?99:sd->status.base_level;

	return packet_db[0x22a].len;
#endif
}

/*==========================================
 *
 *------------------------------------------
 */
static int clif_set007b(struct map_session_data *sd,unsigned char *buf)
{
	nullpo_retr(0, sd);

#if PACKETVER < 4
	WBUFW(buf,0)=0x7b;
	WBUFL(buf,2)=sd->bl.id;
	WBUFW(buf,6)=sd->speed;
	WBUFW(buf,8)=sd->opt1;
	WBUFW(buf,10)=sd->opt2;
	WBUFW(buf,12)=sd->status.option;
	WBUFW(buf,14)=sd->view_class;
	WBUFW(buf,16)=sd->status.hair;
	if(sd->view_class != 22 && sd->view_class != 26)
		WBUFW(buf,18)=sd->status.weapon;
	else
		WBUFW(buf,18)=0;
	WBUFW(buf,20)=sd->status.head_bottom;
	WBUFL(buf,22)=gettick();
	WBUFW(buf,26)=sd->status.shield;
	WBUFW(buf,28)=sd->status.head_top;
	WBUFW(buf,30)=sd->status.head_mid;
	WBUFW(buf,32)=sd->status.hair_color;
	WBUFW(buf,34)=sd->status.clothes_color;
	WBUFW(buf,36)=sd->head_dir;
	WBUFL(buf,38)=sd->status.guild_id;
	WBUFL(buf,42)=sd->guild_emblem_id;
	WBUFW(buf,46)=sd->status.manner;
	WBUFB(buf,48)=sd->status.karma;
	WBUFB(buf,49)=sd->sex;
	WBUFPOS2(buf,50,sd->bl.x,sd->bl.y,sd->to_x,sd->to_y);
	WBUFB(buf,55)=0;
	WBUFB(buf,56)=5;
	WBUFB(buf,57)=5;
	WBUFW(buf,58)=(sd->status.base_level>99)?99:sd->status.base_level;

	return packet_db[0x7b].len;
#elif PACKETVER < 7
	WBUFW(buf,0)=0x1da;
	WBUFL(buf,2)=sd->bl.id;
	WBUFW(buf,6)=sd->speed;
	WBUFW(buf,8)=sd->opt1;
	WBUFW(buf,10)=sd->opt2;
	WBUFW(buf,12)=sd->status.option;
	WBUFW(buf,14)=sd->view_class;
	WBUFW(buf,16)=sd->status.hair;
	if(sd->equip_index[9] >= 0
	&& sd->inventory_data[sd->equip_index[9]]
	&& sd->view_class != 22
	&& sd->view_class != 26) {
		if(sd->inventory_data[sd->equip_index[9]]->view_id > 0)
			WBUFW(buf,18)=sd->inventory_data[sd->equip_index[9]]->view_id;
		else
			WBUFW(buf,18)=sd->status.inventory[sd->equip_index[9]].nameid;
	}
	else
		WBUFW(buf,18)=0;
	if(sd->equip_index[8] >= 0
	&& sd->equip_index[8] != sd->equip_index[9]
	&& sd->inventory_data[sd->equip_index[8]]
	&& sd->view_class != 22
	&& sd->view_class != 26) {
		if(sd->inventory_data[sd->equip_index[8]]->view_id > 0)
			WBUFW(buf,20)=sd->inventory_data[sd->equip_index[8]]->view_id;
		else
			WBUFW(buf,20)=sd->status.inventory[sd->equip_index[8]].nameid;
	}
	else
		WBUFW(buf,20)=0;
	WBUFW(buf,22)=sd->status.head_bottom;
	WBUFL(buf,24)=gettick();
	WBUFW(buf,28)=sd->status.head_top;
	WBUFW(buf,30)=sd->status.head_mid;
	WBUFW(buf,32)=sd->status.hair_color;
	WBUFW(buf,34)=sd->status.clothes_color;
	WBUFW(buf,36)=sd->head_dir;
	WBUFL(buf,38)=sd->status.guild_id;
	WBUFW(buf,42)=sd->guild_emblem_id;
	WBUFW(buf,44)=sd->status.manner;
	WBUFW(buf,46)=sd->opt3;
	WBUFB(buf,48)=(unsigned char)sd->status.karma;
	WBUFB(buf,49)=sd->sex;
	WBUFPOS2(buf,50,sd->bl.x,sd->bl.y,sd->ud.to_x,sd->ud.to_y);
	WBUFB(buf,55)=0;
	WBUFB(buf,56)=5;
	WBUFB(buf,57)=5;
	WBUFW(buf,58)=(sd->status.base_level>99)?99:sd->status.base_level;

	return packet_db[0x1da].len;
#else
	WBUFW(buf,0)=0x22c;
	WBUFL(buf,2)=sd->bl.id;
	WBUFW(buf,6)=sd->speed;
	WBUFW(buf,8)=sd->opt1;
	WBUFW(buf,10)=sd->opt2;
	WBUFL(buf,12)=sd->status.option;
	WBUFW(buf,16)=sd->view_class;
	WBUFW(buf,18)=sd->status.hair;
	if(sd->equip_index[9] >= 0
	&& sd->inventory_data[sd->equip_index[9]]
	&& sd->view_class != 22
	&& sd->view_class != 26) {
		if(sd->inventory_data[sd->equip_index[9]]->view_id > 0)
			WBUFW(buf,20)=sd->inventory_data[sd->equip_index[9]]->view_id;
		else
			WBUFW(buf,20)=sd->status.inventory[sd->equip_index[9]].nameid;
	}
	else
		WBUFW(buf,20)=0;
	if(sd->equip_index[8] >= 0
	&& sd->equip_index[8] != sd->equip_index[9]
	&& sd->inventory_data[sd->equip_index[8]]
	&& sd->view_class != 22
	&& sd->view_class != 26) {
		if(sd->inventory_data[sd->equip_index[8]]->view_id > 0)
			WBUFW(buf,22)=sd->inventory_data[sd->equip_index[8]]->view_id;
		else
			WBUFW(buf,22)=sd->status.inventory[sd->equip_index[8]].nameid;
	}
	else
		WBUFW(buf,22)=0;
	WBUFW(buf,24)=sd->status.head_bottom;
	WBUFL(buf,26)=gettick();
	WBUFW(buf,30)=sd->status.head_top;
	WBUFW(buf,32)=sd->status.head_mid;
	WBUFW(buf,34)=sd->status.hair_color;
	WBUFW(buf,36)=sd->status.clothes_color;
	WBUFW(buf,38)=sd->head_dir;
	WBUFL(buf,40)=sd->status.guild_id;
	WBUFW(buf,44)=sd->guild_emblem_id;
	WBUFW(buf,46)=sd->status.manner;
	WBUFL(buf,48)=sd->opt3;
	WBUFB(buf,52)=(unsigned char)sd->status.karma;
	WBUFB(buf,53)=sd->sex;
	WBUFPOS2(buf,54,sd->bl.x,sd->bl.y,sd->ud.to_x,sd->ud.to_y);
	WBUFB(buf,59)=0x88;
	WBUFB(buf,60)=0;
	WBUFB(buf,61)=0;
	WBUFW(buf,62)=(sd->status.base_level>99)?99:sd->status.base_level;

	return packet_db[0x22c].len;
#endif
}

/*==========================================
 * クラスチェンジ typeはMobの場合は1で他は0？
 *------------------------------------------
 */
void clif_class_change(struct block_list *bl,int class,int type)
{
	char buf[16];

	nullpo_retv(bl);

	if(class >= MAX_VALID_PC_CLASS) {
		WBUFW(buf,0)=0x1b0;
		WBUFL(buf,2)=bl->id;
		WBUFB(buf,6)=type;
		WBUFL(buf,7)=class;
		clif_send(buf,packet_db[0x1b0].len,bl,AREA);
	}

	return;
}

/*==========================================
 * MOB表示1
 *------------------------------------------
 */
static int clif_mob0078(struct mob_data *md,unsigned char *buf)
{
	int level;

	nullpo_retr(0, md);

	if(mob_get_viewclass(md->class) < MAX_VALID_PC_CLASS) {
#if PACKETVER < 4
		memset(buf,0,packet_db[0x78].len);

		WBUFW(buf,0)=0x78;
		WBUFL(buf,2)=md->bl.id;
		WBUFW(buf,6)=status_get_speed(&md->bl);
		WBUFW(buf,8)=md->opt1;
		WBUFW(buf,10)=md->opt2;
		WBUFW(buf,12)=md->option;
		WBUFW(buf,14)=pc_calc_class_job(mob_get_viewclass(md->class),mob_db[md->class].trans);
		WBUFW(buf,16)=mob_get_hair(md->class);
		WBUFW(buf,18)=mob_get_weapon(md->class);
		WBUFW(buf,20)=mob_get_head_buttom(md->class);
		WBUFW(buf,22)=mob_get_shield(md->class);
		WBUFW(buf,24)=mob_get_head_top(md->class);
		WBUFW(buf,26)=mob_get_head_mid(md->class);
		WBUFW(buf,28)=mob_get_hair_color(md->class);
		WBUFW(buf,30)=mob_get_clothes_color(md->class);
		if(md->guild_id){
			struct guild *g=guild_search(md->guild_id);
			if(g)
				WBUFL(buf,38)=g->emblem_id;
			WBUFL(buf,34)=md->guild_id;
		}
		WBUFW(buf,42)=md->opt3;
		WBUFB(buf,44)=1;
		WBUFB(buf,45)=mob_get_sex(md->class);
		WBUFPOS(buf,46,md->bl.x,md->bl.y);
		WBUFB(buf,48)|=md->dir&0x0f;
		WBUFB(buf,49)=5;
		WBUFB(buf,50)=5;
		WBUFW(buf,52)=((level = status_get_lv(&md->bl))>99)? 99:level;

		return packet_db[0x78].len;
#elif PACKETVER < 7
		memset(buf,0,packet_db[0x1d8].len);

		WBUFW(buf,0)=0x1d8;
		WBUFL(buf,2)=md->bl.id;
		WBUFW(buf,6)=status_get_speed(&md->bl);
		WBUFW(buf,8)=md->opt1;
		WBUFW(buf,10)=md->opt2;
		WBUFW(buf,12)=md->option;
		WBUFW(buf,14)=pc_calc_class_job(mob_get_viewclass(md->class),mob_db[md->class].trans);
		WBUFW(buf,16)=mob_get_hair(md->class);
		WBUFW(buf,18)=mob_get_weapon(md->class);
		WBUFW(buf,20)=mob_get_shield(md->class);
		WBUFW(buf,22)=mob_get_head_buttom(md->class);
		WBUFW(buf,24)=mob_get_head_top(md->class);
		WBUFW(buf,26)=mob_get_head_mid(md->class);
		WBUFW(buf,28)=mob_get_hair_color(md->class);
		WBUFW(buf,30)=mob_get_clothes_color(md->class);
		if(md->guild_id){
			struct guild *g=guild_search(md->guild_id);
			if(g)
				WBUFL(buf,38)=g->emblem_id;
			WBUFL(buf,34)=md->guild_id;
		}
		WBUFW(buf,42)=md->opt3;
		WBUFB(buf,44)=1;
		WBUFB(buf,45)=mob_get_sex(md->class);
		WBUFPOS(buf,46,md->bl.x,md->bl.y);
		WBUFB(buf,48)|=md->dir&0x0f;
		WBUFB(buf,49)=5;
		WBUFB(buf,50)=5;
		WBUFW(buf,52)=((level = status_get_lv(&md->bl))>99)? 99:level;

		return packet_db[0x1d8].len;
#else
		memset(buf,0,packet_db[0x22a].len);

		WBUFW(buf,0)=0x22a;
		WBUFL(buf,2)=md->bl.id;
		WBUFW(buf,6)=status_get_speed(&md->bl);
		WBUFW(buf,8)=md->opt1;
		WBUFW(buf,10)=md->opt2;
		WBUFL(buf,12)=md->option;
		WBUFW(buf,16)=pc_calc_class_job(mob_get_viewclass(md->class),mob_db[md->class].trans);
		WBUFW(buf,18)=mob_get_hair(md->class);
		WBUFW(buf,20)=mob_get_weapon(md->class);
		WBUFW(buf,22)=mob_get_shield(md->class);
		WBUFW(buf,24)=mob_get_head_buttom(md->class);
		WBUFW(buf,26)=mob_get_head_top(md->class);
		WBUFW(buf,28)=mob_get_head_mid(md->class);
		WBUFW(buf,30)=mob_get_hair_color(md->class);
		WBUFW(buf,32)=mob_get_clothes_color(md->class);
		if(md->guild_id){
			struct guild *g=guild_search(md->guild_id);
			if(g)
				WBUFW(buf,40)=g->emblem_id;
			WBUFL(buf,36)=md->guild_id;
		}
		WBUFL(buf,44)=md->opt3;
		WBUFB(buf,48)=1;
		WBUFB(buf,49)=mob_get_sex(md->class);
		WBUFPOS(buf,50,md->bl.x,md->bl.y);
		WBUFB(buf,52)|=md->dir&0x0f;
		WBUFB(buf,53)=5;
		WBUFB(buf,54)=5;
		WBUFW(buf,56)=((level = status_get_lv(&md->bl))>99)? 99:level;

		return packet_db[0x22a].len;
#endif
	}
	memset(buf,0,packet_db[0x78].len);

	WBUFW(buf,0)=0x78;
	WBUFL(buf,2)=md->bl.id;
	WBUFW(buf,6)=status_get_speed(&md->bl);
	WBUFW(buf,8)=md->opt1;
	WBUFW(buf,10)=md->opt2;
	WBUFW(buf,12)=md->option;
	WBUFW(buf,14)=mob_get_viewclass(md->class);
	if((md->class == 1285 || md->class == 1286 || md->class == 1287) && md->guild_id){
		struct guild *g=guild_search(md->guild_id);
		if(g)
			WBUFL(buf,22)=g->emblem_id;
		WBUFL(buf,26)=md->guild_id;
	}
	WBUFW(buf,42)=md->opt3;
	WBUFPOS(buf,46,md->bl.x,md->bl.y);
	WBUFB(buf,48)|=md->dir&0x0f;
	WBUFB(buf,49)=5;
	WBUFB(buf,50)=5;
	WBUFW(buf,52)=((level = status_get_lv(&md->bl))>99)? 99:level;

	return packet_db[0x78].len;
}

/*==========================================
 * MOB表示2
 *------------------------------------------
 */
static int clif_mob007b(struct mob_data *md,unsigned char *buf)
{
	int level;

	nullpo_retr(0, md);

	if(mob_get_viewclass(md->class) < MAX_VALID_PC_CLASS) {
#if PACKETVER < 4
		memset(buf,0,packet_db[0x7b].len);

		WBUFW(buf,0)=0x7b;
		WBUFL(buf,2)=md->bl.id;
		WBUFW(buf,6)=status_get_speed(&md->bl);
		WBUFW(buf,8)=md->opt1;
		WBUFW(buf,10)=md->opt2;
		WBUFW(buf,12)=md->option;
		WBUFW(buf,14)=pc_calc_class_job(mob_get_viewclass(md->class),mob_db[md->class].trans);
		WBUFW(buf,16)=mob_get_hair(md->class);
		WBUFW(buf,18)=mob_get_weapon(md->class);
		WBUFW(buf,20)=mob_get_head_buttom(md->class);
		WBUFL(buf,22)=gettick();
		WBUFW(buf,26)=mob_get_shield(md->class);
		WBUFW(buf,28)=mob_get_head_top(md->class);
		WBUFW(buf,30)=mob_get_head_mid(md->class);
		WBUFW(buf,32)=mob_get_hair_color(md->class);
		WBUFW(buf,34)=mob_get_clothes_color(md->class);
		if(md->guild_id){
			struct guild *g=guild_search(md->guild_id);
			if(g)
				WBUFL(buf,42)=g->emblem_id;
			WBUFL(buf,38)=md->guild_id;
		}
		WBUFW(buf,46)=md->opt3;
		WBUFB(buf,48)=1;
		WBUFB(buf,49)=mob_get_sex(md->class);
		WBUFPOS2(buf,50,md->bl.x,md->bl.y,md->ud.to_x,md->ud.to_y);
		WBUFB(buf,56)=5;
		WBUFB(buf,57)=5;
		WBUFW(buf,58)=((level = status_get_lv(&md->bl))>99)? 99:level;

		return packet_db[0x7b].len;
#elif PACKETVER < 7
		memset(buf,0,packet_db[0x1da].len);

		WBUFW(buf,0)=0x1da;
		WBUFL(buf,2)=md->bl.id;
		WBUFW(buf,6)=status_get_speed(&md->bl);
		WBUFW(buf,8)=md->opt1;
		WBUFW(buf,10)=md->opt2;
		WBUFW(buf,12)=md->option;
		WBUFW(buf,14)=pc_calc_class_job(mob_get_viewclass(md->class),mob_db[md->class].trans);
		WBUFW(buf,16)=mob_get_hair(md->class);
		WBUFW(buf,18)=mob_get_weapon(md->class);
		WBUFW(buf,20)=mob_get_shield(md->class);
		WBUFW(buf,22)=mob_get_head_buttom(md->class);
		WBUFL(buf,24)=gettick();
		WBUFW(buf,28)=mob_get_head_top(md->class);
		WBUFW(buf,30)=mob_get_head_mid(md->class);
		WBUFW(buf,32)=mob_get_hair_color(md->class);
		WBUFW(buf,34)=mob_get_clothes_color(md->class);
		if(md->guild_id){
			struct guild *g=guild_search(md->guild_id);
			if(g)
				WBUFL(buf,42)=g->emblem_id;
			WBUFL(buf,38)=md->guild_id;
		}
		WBUFW(buf,46)=md->opt3;
		WBUFB(buf,48)=1;
		WBUFB(buf,49)=mob_get_sex(md->class);
		WBUFPOS2(buf,50,md->bl.x,md->bl.y,md->ud.to_x,md->ud.to_y);
		WBUFB(buf,56)=5;
		WBUFB(buf,57)=5;
		WBUFW(buf,58)=((level = status_get_lv(&md->bl))>99)? 99:level;

		return packet_db[0x1da].len;
#else
		memset(buf,0,packet_db[0x22c].len);

		WBUFW(buf,0)=0x22c;
		WBUFL(buf,2)=md->bl.id;
		WBUFW(buf,6)=md->speed;
		WBUFW(buf,8)=md->opt1;
		WBUFW(buf,10)=md->opt2;
		WBUFL(buf,12)=md->option;
		WBUFW(buf,16)=pc_calc_class_job(mob_get_viewclass(md->class),mob_db[md->class].trans);
		WBUFW(buf,18)=mob_get_hair(md->class);
		WBUFW(buf,20)=mob_get_weapon(md->class);
		WBUFW(buf,22)=mob_get_shield(md->class);
		WBUFW(buf,24)=mob_get_head_buttom(md->class);
		WBUFL(buf,26)=gettick();
		WBUFW(buf,30)=mob_get_head_top(md->class);
		WBUFW(buf,32)=mob_get_head_mid(md->class);
		WBUFW(buf,34)=mob_get_hair_color(md->class);
		WBUFW(buf,36)=mob_get_clothes_color(md->class);
		if(md->guild_id){
			struct guild *g=guild_search(md->guild_id);
			if(g)
				WBUFL(buf,44)=g->emblem_id;
			WBUFL(buf,40)=md->guild_id;
		}
		WBUFL(buf,48)=md->opt3;
		WBUFB(buf,52)=1;
		WBUFB(buf,53)=mob_get_sex(md->class);
		WBUFPOS2(buf,54,md->bl.x,md->bl.y,md->ud.to_x,md->ud.to_y);
		WBUFB(buf,59)=0x88;
		WBUFB(buf,60)=0;
		WBUFB(buf,61)=0;
		WBUFW(buf,62)=((level = status_get_lv(&md->bl))>99)? 99:level;

		return packet_db[0x22c].len;
#endif
	}
	memset(buf,0,packet_db[0x7b].len);

	WBUFW(buf,0)=0x7b;
	WBUFL(buf,2)=md->bl.id;
	WBUFW(buf,6)=status_get_speed(&md->bl);
	WBUFW(buf,8)=md->opt1;
	WBUFW(buf,10)=md->opt2;
	WBUFW(buf,12)=md->option;
	WBUFW(buf,14)=mob_get_viewclass(md->class);
	WBUFL(buf,22)=gettick();
	if((md->class == 1285 || md->class == 1286 || md->class == 1287) && md->guild_id){
		struct guild *g=guild_search(md->guild_id);
		if(g)
			WBUFL(buf,26)=g->emblem_id;
		WBUFL(buf,30)=md->guild_id;
	}
	WBUFW(buf,46)=md->opt3;
	WBUFPOS2(buf,50,md->bl.x,md->bl.y,md->ud.to_x,md->ud.to_y);
	WBUFB(buf,56)=5;
	WBUFB(buf,57)=5;
	WBUFW(buf,58)=((level = status_get_lv(&md->bl))>99)? 99:level;

	return packet_db[0x7b].len;
}

/*==========================================
 *
 *------------------------------------------
 */
static int clif_npc0078(struct npc_data *nd,unsigned char *buf)
{
	struct guild *g;

	nullpo_retr(0, nd);

	memset(buf,0,packet_db[0x78].len);

	WBUFW(buf,0)=0x78;
	WBUFL(buf,2)=nd->bl.id;
	WBUFW(buf,6)=nd->speed;
	WBUFW(buf,12)=nd->option;
	WBUFW(buf,14)=nd->class;
	if( (nd->bl.subtype!=WARP) &&
		(nd->class == 722) &&
		(nd->u.scr.guild_id > 0) &&
		((g=guild_search(nd->u.scr.guild_id))) )
	{
		WBUFL(buf,22)=g->emblem_id;
		WBUFL(buf,26)=g->guild_id;
	}
	WBUFPOS(buf,46,nd->bl.x,nd->bl.y);
	WBUFB(buf,48)|=nd->dir&0x0f;
	WBUFB(buf,49)=5;
	WBUFB(buf,50)=5;

	return packet_db[0x78].len;
}

/*==========================================
 *
 *------------------------------------------
 */
static int clif_pet0078(struct pet_data *pd,unsigned char *buf)
{
	int view,level;

	nullpo_retr(0, pd);

	if(mob_get_viewclass(pd->class) < MAX_VALID_PC_CLASS) {
#if PACKETVER < 4
		memset(buf,0,packet_db[0x78].len);

		WBUFW(buf,0)=0x78;
		WBUFL(buf,2)=pd->bl.id;
		WBUFW(buf,6)=pd->speed;
		WBUFW(buf,12)=mob_db[pd->class].option;
		WBUFW(buf,14)=pc_calc_class_job(mob_get_viewclass(pd->class),mob_db[pd->class].trans);
		WBUFW(buf,16)=mob_get_hair(pd->class);
		WBUFW(buf,18)=mob_get_weapon(pd->class);
		WBUFW(buf,20)=mob_get_head_buttom(pd->class);
		WBUFW(buf,22)=mob_get_shield(pd->class);
		WBUFW(buf,24)=mob_get_head_top(pd->class);
		WBUFW(buf,26)=mob_get_head_mid(pd->class);
		WBUFW(buf,28)=mob_get_hair_color(pd->class);
		WBUFW(buf,30)=mob_get_clothes_color(pd->class);
		WBUFB(buf,45)=mob_get_sex(pd->class);
		WBUFPOS(buf,46,pd->bl.x,pd->bl.y);
		WBUFB(buf,48)|=pd->dir&0x0f;
		WBUFB(buf,49)=0;
		WBUFB(buf,50)=0;
		WBUFW(buf,52)=((level = status_get_lv(&pd->bl))>99)? 99:level;

		return packet_db[0x78].len;
#elif PACKETVER < 7
		memset(buf,0,packet_db[0x1d8].len);

		WBUFW(buf,0)=0x1d8;
		WBUFL(buf,2)=pd->bl.id;
		WBUFW(buf,6)=pd->speed;
		WBUFW(buf,12)=mob_db[pd->class].option;
		WBUFW(buf,14)=pc_calc_class_job(mob_get_viewclass(pd->class),mob_db[pd->class].trans);
		WBUFW(buf,16)=mob_get_hair(pd->class);
		WBUFW(buf,18)=mob_get_weapon(pd->class);
		WBUFW(buf,20)=mob_get_shield(pd->class);
		WBUFW(buf,22)=mob_get_head_buttom(pd->class);
		WBUFW(buf,24)=mob_get_head_top(pd->class);
		WBUFW(buf,26)=mob_get_head_mid(pd->class);
		WBUFW(buf,28)=mob_get_hair_color(pd->class);
		WBUFW(buf,30)=mob_get_clothes_color(pd->class);
		WBUFB(buf,45)=mob_get_sex(pd->class);
		WBUFPOS(buf,46,pd->bl.x,pd->bl.y);
		WBUFB(buf,48)|=pd->dir&0x0f;
		WBUFB(buf,49)=0;
		WBUFB(buf,50)=0;
		WBUFW(buf,52)=((level = status_get_lv(&pd->bl))>99)? 99:level;

		return packet_db[0x1d8].len;
#else
		memset(buf,0,packet_db[0x22a].len);

		WBUFW(buf,0)=0x22a;
		WBUFL(buf,2)=pd->bl.id;
		WBUFW(buf,6)=pd->speed;
		WBUFL(buf,12)=mob_db[pd->class].option;
		WBUFW(buf,16)=pc_calc_class_job(mob_get_viewclass(pd->class),mob_db[pd->class].trans);
		WBUFW(buf,18)=mob_get_hair(pd->class);
		WBUFW(buf,20)=mob_get_weapon(pd->class);
		WBUFW(buf,22)=mob_get_shield(pd->class);
		WBUFW(buf,24)=mob_get_head_buttom(pd->class);
		WBUFW(buf,26)=mob_get_head_top(pd->class);
		WBUFW(buf,28)=mob_get_head_mid(pd->class);
		WBUFW(buf,30)=mob_get_hair_color(pd->class);
		WBUFW(buf,32)=mob_get_clothes_color(pd->class);
		WBUFB(buf,49)=mob_get_sex(pd->class);
		WBUFPOS(buf,50,pd->bl.x,pd->bl.y);
		WBUFB(buf,52)|=pd->dir&0x0f;
		WBUFB(buf,53)=0;
		WBUFB(buf,54)=0;
		WBUFW(buf,56)=((level = status_get_lv(&pd->bl))>99)? 99:level;

		return packet_db[0x22a].len;
#endif
	}
	memset(buf,0,packet_db[0x78].len);

	WBUFW(buf,0)=0x78;
	WBUFL(buf,2)=pd->bl.id;
	WBUFW(buf,6)=pd->speed;
	WBUFW(buf,14)=mob_get_viewclass(pd->class);
	WBUFW(buf,16)=battle_config.pet0078_hair_id;
	if((view = itemdb_viewid(pd->equip)) > 0)
		WBUFW(buf,20)=view;
	else
		WBUFW(buf,20)=pd->equip;
	WBUFPOS(buf,46,pd->bl.x,pd->bl.y);
	WBUFB(buf,48)|=pd->dir&0x0f;
	WBUFB(buf,49)=0;
	WBUFB(buf,50)=0;
	WBUFW(buf,52)=((level = status_get_lv(&pd->bl))>99)? 99:level;

	return packet_db[0x78].len;
}

/*==========================================
 *
 *------------------------------------------
 */
static int clif_pet007b(struct pet_data *pd,unsigned char *buf)
{
	int view,level;

	nullpo_retr(0, pd);

	if(mob_get_viewclass(pd->class) < MAX_VALID_PC_CLASS) {
#if PACKETVER < 4
		memset(buf,0,packet_db[0x7b].len);

		WBUFW(buf,0)=0x7b;
		WBUFL(buf,2)=pd->bl.id;
		WBUFW(buf,6)=pd->speed;
		WBUFW(buf,12)=mob_db[pd->class].option;
		WBUFW(buf,14)=pc_calc_class_job(mob_get_viewclass(pd->class),mob_db[pd->class].trans);
		WBUFW(buf,16)=mob_get_hair(pd->class);
		WBUFW(buf,18)=mob_get_weapon(pd->class);
		WBUFW(buf,20)=mob_get_head_buttom(pd->class);
		WBUFL(buf,22)=gettick();
		WBUFW(buf,26)=mob_get_shield(pd->class);
		WBUFW(buf,28)=mob_get_head_top(pd->class);
		WBUFW(buf,30)=mob_get_head_mid(pd->class);
		WBUFW(buf,32)=mob_get_hair_color(pd->class);
		WBUFW(buf,34)=mob_get_clothes_color(pd->class);
		WBUFB(buf,49)=mob_get_sex(pd->class);
		WBUFPOS2(buf,50,pd->bl.x,pd->bl.y,pd->ud.to_x,pd->ud.to_y);
		WBUFB(buf,56)=0;
		WBUFB(buf,57)=0;
		WBUFW(buf,58)=((level = status_get_lv(&pd->bl))>99)? 99:level;

		return packet_db[0x7b].len;
#elif PACKETVER < 7
		memset(buf,0,packet_db[0x1da].len);

		WBUFW(buf,0)=0x1da;
		WBUFL(buf,2)=pd->bl.id;
		WBUFW(buf,6)=pd->speed;
		WBUFW(buf,12)=mob_db[pd->class].option;
		WBUFW(buf,14)=pc_calc_class_job(mob_get_viewclass(pd->class),mob_db[pd->class].trans);
		WBUFW(buf,16)=mob_get_hair(pd->class);
		WBUFW(buf,18)=mob_get_weapon(pd->class);
		WBUFW(buf,20)=mob_get_shield(pd->class);
		WBUFW(buf,22)=mob_get_head_buttom(pd->class);
		WBUFL(buf,24)=gettick();
		WBUFW(buf,28)=mob_get_head_top(pd->class);
		WBUFW(buf,30)=mob_get_head_mid(pd->class);
		WBUFW(buf,32)=mob_get_hair_color(pd->class);
		WBUFW(buf,34)=mob_get_clothes_color(pd->class);
		WBUFB(buf,49)=mob_get_sex(pd->class);
		WBUFPOS2(buf,50,pd->bl.x,pd->bl.y,pd->ud.to_x,pd->ud.to_y);
		WBUFB(buf,56)=0;
		WBUFB(buf,57)=0;
		WBUFW(buf,58)=((level = status_get_lv(&pd->bl))>99)? 99:level;

		return packet_db[0x1da].len;
#else
		memset(buf,0,packet_db[0x22c].len);

		WBUFW(buf,0)=0x22c;
		WBUFL(buf,2)=pd->bl.id;
		WBUFW(buf,6)=pd->speed;
		WBUFL(buf,12)=mob_db[pd->class].option;
		WBUFW(buf,16)=pc_calc_class_job(mob_get_viewclass(pd->class),mob_db[pd->class].trans);
		WBUFW(buf,18)=mob_get_hair(pd->class);
		WBUFW(buf,20)=mob_get_weapon(pd->class);
		WBUFW(buf,22)=mob_get_shield(pd->class);
		WBUFW(buf,24)=mob_get_head_buttom(pd->class);
		WBUFL(buf,26)=gettick();
		WBUFW(buf,30)=mob_get_head_top(pd->class);
		WBUFW(buf,32)=mob_get_head_mid(pd->class);
		WBUFW(buf,34)=mob_get_hair_color(pd->class);
		WBUFW(buf,36)=mob_get_clothes_color(pd->class);
		WBUFB(buf,53)=mob_get_sex(pd->class);
		WBUFPOS2(buf,54,pd->bl.x,pd->bl.y,pd->ud.to_x,pd->ud.to_y);
		WBUFB(buf,59)=0x88;
		WBUFB(buf,60)=0;
		WBUFB(buf,61)=0;
		WBUFW(buf,62)=((level = status_get_lv(&pd->bl))>99)? 99:level;

		return packet_db[0x22c].len;
#endif
	}
	memset(buf,0,packet_db[0x7b].len);

	WBUFW(buf,0)=0x7b;
	WBUFL(buf,2)=pd->bl.id;
	WBUFW(buf,6)=pd->speed;
	WBUFW(buf,14)=mob_get_viewclass(pd->class);
	WBUFW(buf,16)=battle_config.pet0078_hair_id;
	if((view = itemdb_viewid(pd->equip)) > 0)
		WBUFW(buf,20)=view;
	else
		WBUFW(buf,20)=pd->equip;
	WBUFL(buf,22)=gettick();
	WBUFPOS2(buf,50,pd->bl.x,pd->bl.y,pd->ud.to_x,pd->ud.to_y);
	WBUFB(buf,56)=0;
	WBUFB(buf,57)=0;
	WBUFW(buf,58)=((level = status_get_lv(&pd->bl))>99)? 99:level;

	return packet_db[0x7b].len;
}

/*==========================================
 *
 *------------------------------------------
 */
static int clif_hom0078(struct homun_data *hd,unsigned char *buf)
{
	int level;

	nullpo_retr(0, hd);

	memset(buf,0,packet_db[0x78].len);

	WBUFW(buf,0) =0x78;
	WBUFL(buf,2) =hd->bl.id;
	WBUFW(buf,6) =hd->speed;
	WBUFW(buf,8) =hd->opt1;
	WBUFW(buf,10)=hd->opt2;
	WBUFW(buf,12)=hd->status.option;
	WBUFW(buf,14)=hd->view_class;
	WBUFW(buf,16)=battle_config.pet0078_hair_id;
	WBUFW(buf,20)=0;
	WBUFW(buf,42)=hd->opt3;
	WBUFPOS(buf,46,hd->bl.x,hd->bl.y);
	WBUFB(buf,48)=hd->dir&0x0f;
	WBUFB(buf,49)=0;
	WBUFB(buf,50)=0;
	WBUFW(buf,52)=((level = status_get_lv(&hd->bl))>99)? 99:level;

	return packet_db[0x78].len;
}

static int clif_hom007b(struct homun_data *hd,unsigned char *buf)
{
	int view,level;

	nullpo_retr(0, hd);

	memset(buf,0,packet_db[0x7b].len);

	WBUFW(buf,0) =0x7b;
	WBUFL(buf,2) =hd->bl.id;
	WBUFW(buf,6) =hd->speed;
	WBUFW(buf,8) =hd->opt1;
	WBUFW(buf,10)=hd->opt2;
	WBUFW(buf,12)=hd->status.option;
	WBUFW(buf,14)=hd->view_class;
	WBUFW(buf,16)=battle_config.pet0078_hair_id;
	if((view = itemdb_viewid(hd->equip)) > 0)
		WBUFW(buf,20)=view;
	else
		WBUFW(buf,20)=hd->equip;
	WBUFL(buf,22)=gettick();
	WBUFW(buf,46)=hd->opt3;
	WBUFPOS2(buf,50,hd->bl.x,hd->bl.y,hd->ud.to_x,hd->ud.to_y);
	WBUFB(buf,56)=0;
	WBUFB(buf,57)=0;
	WBUFW(buf,58)=((level = status_get_lv(&hd->bl))>99)? 99:level;

	return packet_db[0x7b].len;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_set01e1(struct map_session_data *sd, unsigned char *buf)
{
	nullpo_retv(sd);

	WBUFW(buf,0)=0x1e1;
	WBUFL(buf,2)=sd->bl.id;
	WBUFW(buf,6)=sd->spiritball;

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
 *
 *------------------------------------------
 */
void clif_spawnpc(struct map_session_data *sd)
{
	nullpo_retv(sd);

	clif_set0078(sd,WFIFOP(sd->fd,0));
#if PACKETVER < 4
	WFIFOW(sd->fd,0)=0x79;
	WFIFOW(sd->fd,51)=(sd->status.base_level>99)?99:sd->status.base_level;
	clif_send(WFIFOP(sd->fd,0),packet_db[0x79].len,&sd->bl,AREA_WOS);
#elif PACKETVER < 7
	WFIFOW(sd->fd,0)=0x1d9;
	WFIFOW(sd->fd,51)=(sd->status.base_level>99)?99:sd->status.base_level;
	clif_send(WFIFOP(sd->fd,0),packet_db[0x1d9].len,&sd->bl,AREA_WOS);
#else
	WFIFOW(sd->fd,0)=0x22b;
	WFIFOW(sd->fd,55)=(sd->status.base_level>99)?99:sd->status.base_level;
	clif_send(WFIFOP(sd->fd,0),packet_db[0x22b].len,&sd->bl,AREA_WOS);
#endif

	if(sd->spiritball > 0)
		clif_spiritball(sd);
	if(sd->coin > 0)
		clif_coin(sd);
	if(sd->view_size!=0)
		clif_misceffect2(&sd->bl,422+sd->view_size);

	if (map[sd->bl.m].flag.rain)
		clif_misceffect3(&sd->bl, 161);
	if (map[sd->bl.m].flag.snow)
		clif_misceffect3(&sd->bl, 162);
	if (map[sd->bl.m].flag.sakura)
		clif_misceffect3(&sd->bl, 163);
	if (map[sd->bl.m].flag.leaves)
		clif_misceffect3(&sd->bl, 333);
	if (map[sd->bl.m].flag.fireworks)
		clif_misceffect3(&sd->bl, 297);
	if (map[sd->bl.m].flag.fireworks)
		clif_misceffect3(&sd->bl, 299);
	if (map[sd->bl.m].flag.fireworks)
		clif_misceffect3(&sd->bl, 301);
	if (map[sd->bl.m].flag.cloud1)
		clif_misceffect3(&sd->bl, 230);
	if (map[sd->bl.m].flag.cloud2)
		clif_misceffect3(&sd->bl, 233);
	if (map[sd->bl.m].flag.cloud3)
		clif_misceffect3(&sd->bl, 516);
	if (map[sd->bl.m].flag.fog)
		clif_misceffect3(&sd->bl, 515);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_spawnnpc(struct npc_data *nd)
{
	unsigned char buf[64];
	int len;

	nullpo_retv(nd);

	if(nd->class < 0 || (nd->flag&1 && nd->option != 0x0002) || nd->class == INVISIBLE_CLASS)
		return;

	memset(buf,0,packet_db[0x7c].len);

	WBUFW(buf,0)=0x7c;
	WBUFL(buf,2)=nd->bl.id;
	WBUFW(buf,6)=nd->speed;
	WBUFW(buf,12)=nd->option;
	WBUFW(buf,20)=nd->class;
	WBUFPOS(buf,36,nd->bl.x,nd->bl.y);

	clif_send(buf,packet_db[0x7c].len,&nd->bl,AREA);

	len = clif_npc0078(nd,buf);
	clif_send(buf,len,&nd->bl,AREA);

	if(nd->view_size!=0)
		clif_misceffect2(&nd->bl,422+nd->view_size);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_spawnmob(struct mob_data *md)
{
	unsigned char buf[64];
	int len;

	nullpo_retv(md);

	if(mob_get_viewclass(md->class) >= MAX_VALID_PC_CLASS) {
		memset(buf,0,packet_db[0x7c].len);

		WBUFW(buf,0)=0x7c;
		WBUFL(buf,2)=md->bl.id;
		WBUFW(buf,6)=md->speed;
		WBUFW(buf,8)=md->opt1;
		WBUFW(buf,10)=md->opt2;
		WBUFW(buf,12)=md->option;
		WBUFW(buf,20)=mob_get_viewclass(md->class);

		WBUFPOS(buf,36,md->bl.x,md->bl.y);

		clif_send(buf,packet_db[0x7c].len,&md->bl,AREA);
	}

	len = clif_mob0078(md,buf);
	clif_send(buf,len,&md->bl,AREA);

	clif_send_clothcolor(&md->bl);
	if(md->view_size!=0)
		clif_misceffect2(&md->bl,422+md->view_size);

	return;
}

// pet

/*==========================================
 *
 *------------------------------------------
 */
void clif_spawnpet(struct pet_data *pd)
{
	unsigned char buf[64];
	int len;

	nullpo_retv(pd);

	if(mob_get_viewclass(pd->class) >= MAX_VALID_PC_CLASS) {
		memset(buf,0,packet_db[0x7c].len);

		WBUFW(buf,0)=0x7c;
		WBUFL(buf,2)=pd->bl.id;
		WBUFW(buf,6)=pd->speed;
		WBUFW(buf,20)=mob_get_viewclass(pd->class);
		WBUFPOS(buf,36,pd->bl.x,pd->bl.y);

		clif_send(buf,packet_db[0x7c].len,&pd->bl,AREA);
	}

	len = clif_pet0078(pd,buf);
	clif_send(buf,len,&pd->bl,AREA);

	clif_send_clothcolor(&pd->bl);
	if(pd->view_size!=0)
		clif_misceffect2(&pd->bl,422+pd->view_size);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_movepet(struct pet_data *pd)
{
	unsigned char buf[128];
	int len;

	nullpo_retv(pd);

	len = clif_pet007b(pd,buf);
	clif_send(buf,len,&pd->bl,AREA);

	clif_send_clothcolor(&pd->bl);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_send_homdata(struct map_session_data *sd, int type, int param)
{
	int fd;
	nullpo_retv(sd);
	nullpo_retv(sd->hd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x230;
	WFIFOW(fd,2)=type;
	WFIFOL(fd,4)=sd->hd->bl.id;
	WFIFOL(fd,8)=param;
	WFIFOSET(fd,packet_db[0x230].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_spawnhom(struct homun_data *hd)
{
	unsigned char buf[64];
//	int len;

	nullpo_retv(hd);

	memset(buf,0,packet_db[0x7c].len);

	WBUFW(buf,0) =0x7c;
	WBUFL(buf,2) =hd->bl.id;
	WBUFW(buf,6) =hd->speed;
	//WBUFW(buf,20)=hd->status.class;
	//if(hd->view_class)
	WBUFW(buf,20)=hd->view_class;
	//else
	//	WBUFW(buf,20)=hd->status.class;
	WBUFB(buf,28)=8;		// 調べた限り固定
	WBUFPOS(buf,36,hd->bl.x,hd->bl.y);

	clif_send(buf,packet_db[0x7c].len,&hd->bl,AREA);
//	ホムでは、0x78パケットや、それに代わるパケットの確認できず
//	len = clif_hom0078(hd,buf);
//	clif_send(buf,len,&hd->bl,AREA);

	if(hd->view_size!=0)
		clif_misceffect2(&hd->bl,422+hd->view_size);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_movehom(struct homun_data *hd)
{
	unsigned char buf[128];
	int len;

	nullpo_retv(hd);

	len = clif_hom007b(hd,buf);
	clif_send(buf,len,&hd->bl,AREA);

	return;
}

void clif_send_homstatus(struct map_session_data *sd, int flag)
{
	int fd;
	struct homun_data *hd;

	nullpo_retv(sd);
	nullpo_retv((hd=sd->hd));

	fd=sd->fd;
	WFIFOW(fd,0)=0x22e;
	memcpy(WFIFOP(fd,2),hd->status.name,24);
	WFIFOB(fd,26)=hd->status.rename_flag*2;	// 名前付けたフラグ 2で変更不可
	WFIFOW(fd,27)=hd->status.base_level;	// Lv
	WFIFOW(fd,29)=hd->status.hungry;		// 満腹度
	WFIFOW(fd,31)=hd->intimate/100;	// 新密度
	WFIFOW(fd,33)=hd->status.equip;			// equip id
	WFIFOW(fd,35)=hd->atk;					// Atk
	WFIFOW(fd,37)=hd->matk;					// MAtk
	WFIFOW(fd,39)=hd->hit;					// Hit
	WFIFOW(fd,41)=hd->critical;				// Cri
	WFIFOW(fd,43)=hd->def;					// Def
	WFIFOW(fd,45)=hd->mdef;					// Mdef
	WFIFOW(fd,47)=hd->flee;					// Flee
	WFIFOW(fd,49)=(flag)?0:status_get_amotion(&hd->bl)+200;	// Aspd
	WFIFOW(fd,51)=hd->status.hp;			// HP
	WFIFOW(fd,53)=hd->max_hp;		// MHp
	WFIFOW(fd,55)=hd->status.sp;			// SP
	WFIFOW(fd,57)=hd->max_sp;		// MSP
	WFIFOL(fd,59)=hd->status.base_exp;		// Exp
	WFIFOL(fd,63)=homun_nextbaseexp(hd);	// NextExp
	WFIFOW(fd,67)=hd->status.skill_point;	// skill point
	WFIFOW(fd,69)=hd->attackable;			// 攻撃可否フラグ	0:不可/1:許可
	WFIFOSET(fd,packet_db[0x22e].len);

	return;
}

void clif_hom_food(struct map_session_data *sd, int foodid, unsigned char fail)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x22f;
	WFIFOB(fd,2)=fail;
	WFIFOW(fd,3)=foodid;
	WFIFOSET(fd,packet_db[0x22f].len);

	return;
}

/*==========================================
 * ホムのスキルリストを送信する
 *------------------------------------------
 */
void clif_homskillinfoblock(struct map_session_data *sd)
{
	int fd;
	int i,c,len=4,id,range,skill_lv;
	struct homun_data *hd;

	nullpo_retv(sd);
	nullpo_retv((hd=sd->hd));

	fd=sd->fd;
	WFIFOW(fd,0)=0x235;
	for ( i = c = 0; i < MAX_HOM_SKILLID-HOM_SKILLID; i++){
		if( (id=hd->status.skill[i].id)!=0 ){
			WFIFOW(fd,len  ) = id;
			WFIFOL(fd,len+2) = skill_get_inf(id);
			skill_lv = hd->status.skill[i].lv;
			WFIFOW(fd,len+6) = skill_lv;
			WFIFOW(fd,len+8) = skill_get_sp(id,skill_lv);
			range = skill_get_range(id,skill_lv);
			if(range < 0)
				range = status_get_range(&hd->bl) - (range + 1);
			WFIFOW(fd,len+10)= range;
			memset(WFIFOP(fd,len+12),0,24);
			if(!(skill_get_inf2(id)&0x01))
				WFIFOB(fd,len+36)= (skill_lv < skill_get_max(id) && sd->status.skill[i].flag ==0 )? 1:0;
			else
				WFIFOB(fd,len+36) = 0;
			len+=37;
			c++;
		}
	}
	WFIFOW(fd,2)=len;
	WFIFOSET(fd,len);

	return;
}

/*==========================================
 * スキル割り振り通知
 *------------------------------------------
 */
void clif_homskillup(struct map_session_data *sd, int skill_num)
{
	int range,fd,skillid;
	struct homun_data *hd;

	nullpo_retv(sd);
	nullpo_retv((hd=sd->hd));
	skillid = skill_num-HOM_SKILLID;

	fd=sd->fd;
	WFIFOW(fd,0) = 0x10e;
	WFIFOW(fd,2) = skill_num;
	WFIFOW(fd,4) = hd->status.skill[skillid].lv;
	WFIFOW(fd,6) = skill_get_sp(skill_num,sd->status.skill[skillid].lv);
	range = skill_get_range(skill_num,sd->status.skill[skillid].lv);
	if(range < 0)
		range = status_get_range(&sd->bl) - (range + 1);
	WFIFOW(fd,8) = range;
	WFIFOB(fd,10) = (sd->status.skill[skillid].lv < skill_get_max(sd->status.skill[skillid].id)) ? 1 : 0;
	WFIFOSET(fd,packet_db[0x10e].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_servertick(struct map_session_data *sd)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x7f;
	WFIFOL(fd,2)=sd->server_tick;
	WFIFOSET(fd,packet_db[0x7f].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_walkok(struct map_session_data *sd)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x87;
	WFIFOL(fd,2)=gettick();
	WFIFOPOS2(fd,6,sd->bl.x,sd->bl.y,sd->ud.to_x,sd->ud.to_y);
	WFIFOB(fd,11)=0;
	WFIFOSET(fd,packet_db[0x87].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_movechar(struct map_session_data *sd)
{
	int fd;
	int len;

	nullpo_retv(sd);

	fd=sd->fd;

	len = clif_set007b(sd,WFIFOP(fd,0));
	clif_send(WFIFOP(fd,0),len,&sd->bl,AREA_WOS);

	clif_send_clothcolor(&sd->bl);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_quitsave(int fd, struct map_session_data *sd)
{
	map_quit(sd);
	chrif_chardisconnect(sd);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static int clif_waitclose(int tid,unsigned int tick,int id,int data)
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
	add_timer(gettick()+5000,clif_waitclose,fd,0);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_changemap(struct map_session_data *sd,char *mapname,int x,int y)
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
void clif_changemapserver(struct map_session_data *sd, char *mapname, int x, int y, int ip, int port)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x92;
	memcpy(WFIFOP(fd,2),mapname,16);
	WFIFOW(fd,18)=x;
	WFIFOW(fd,20)=y;
	WFIFOL(fd,22)=ip;
	WFIFOW(fd,26)=port;
	WFIFOSET(fd,packet_db[0x92].len);

	return;
}

/*==========================================
 * 位置補正
 *------------------------------------------
 */

int clif_fixpos(struct block_list *bl) {

	nullpo_retr(0, bl);

	if(battle_config.clif_fixpos_type)
	{
		int x[4], y[4];
		// clif_fixpos2 用のデータを作成
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
		char buf[16];
		WBUFW(buf,0)=0x88;
		WBUFL(buf,2)=bl->id;
		WBUFW(buf,6)=bl->x;
		WBUFW(buf,8)=bl->y;
		clif_send(buf,packet_db[0x88].len,bl,AREA);
	}

	return 0;
}

static int clif_fixpos2_sub(struct block_list *bl, va_list ap) {
	struct block_list *src_bl = va_arg(ap, struct block_list*);
	int  len  = va_arg(ap, int);
	char *buf = va_arg(ap, char*);

	if( bl && bl->type == BL_PC && src_bl->id != bl->id) { // 自分は除外
		struct map_session_data *sd = (struct map_session_data*)bl;
		memcpy( WFIFOP(sd->fd, 0), buf, len);
		WFIFOSET( sd->fd, len );
	}

	return 0;
}

int clif_fixpos2(struct block_list *bl, int x[4], int y[4])
{
	int  len;
	char buf[128];

	nullpo_retr(0, bl);

	if(battle_config.clif_fixpos_type)
	{
		// self position is changed
		// 自キャラの吹き飛ばしパケ送信（協力者募集）
		// やっぱりJTのエフェクトが残っている内にパケ送信しても
		// 移動しないのは蔵の仕様っぽい。。。
		// 　→ clif_blown() を利用するように変更

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

void clif_blown(struct block_list *bl, int x, int y)
{
	char buf[10];

	nullpo_retv(bl);

	WBUFW(buf, 0) = 0x01ff;
	WBUFL(buf, 2) = bl->id;
	WBUFW(buf, 6) = x;
	WBUFW(buf, 8) = y;
	clif_send(buf,packet_db[0x1ff].len,bl,AREA);

	return;
}

/*==========================================
 * 移動中の位置補正
 *------------------------------------------
 */

void clif_fixwalkpos(struct block_list *bl)
{
	char buf[16];

	nullpo_retv(bl);

	WBUFW(buf,0)=0x88;
	WBUFL(buf,2)=bl->id;
	WBUFW(buf,6)=bl->x;
	WBUFW(buf,8)=bl->y;
	clif_send(buf,packet_db[0x88].len,bl,AREA);

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
	for(i=0;nd->u.shop_item[i].nameid > 0;i++){
		id = itemdb_search(nd->u.shop_item[i].nameid);
		val=nd->u.shop_item[i].value;
		WFIFOL(fd,4+i*11)=val;
		if ( ! id->flag.value_notdc)
			val=pc_modifybuyvalue(sd,val);
		WFIFOL(fd,8+i*11)=val;
		WFIFOB(fd,12+i*11)=id->type;
		if(id->view_id > 0)
			WFIFOW(fd,13+i*11)=id->view_id;
		else
			WFIFOW(fd,13+i*11)=nd->u.shop_item[i].nameid;
	}
	WFIFOW(fd,2)=i*11+4;
	WFIFOSET(fd,WFIFOW(fd,2));

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_selllist(struct map_session_data *sd)
{
	int fd,i,c=0,val;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xc7;
	for(i=0;i<MAX_INVENTORY;i++) {
		if(sd->status.inventory[i].nameid > 0 && sd->inventory_data[i]) {
			val=sd->inventory_data[i]->value_sell;
			if(val < 0)
				continue;
			WFIFOW(fd,4+c*10)=i+2;
			WFIFOL(fd,6+c*10)=val;
			if ( !sd->inventory_data[i]->flag.value_notoc)
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
 *
 *------------------------------------------
 */
void clif_scriptmes(struct map_session_data *sd, int npcid, char *mes)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xb4;
	WFIFOW(fd,2)=strlen(mes)+9;
	WFIFOL(fd,4)=npcid;
	strncpy(WFIFOP(fd,8),mes,strlen(mes)+1);
	WFIFOSET(fd,WFIFOW(fd,2));

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
void clif_scriptmenu(struct map_session_data *sd, int npcid, char *mes)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xb7;
	WFIFOW(fd,2)=strlen(mes)+9;
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
void clif_cutin(struct map_session_data *sd, char *image, int type)
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
	unsigned char *buf;

	nullpo_retv(sd);

	fd=sd->fd;
	buf=WFIFOP(fd,0);
	if(fail) {
		WBUFW(buf,0)=0xa0;
		WBUFW(buf,2)=n+2;
		WBUFW(buf,4)=amount;
		WBUFW(buf,6)=0;
		WBUFB(buf,8)=0;
		WBUFB(buf,9)=0;
		WBUFB(buf,10)=0;
		WBUFW(buf,11)=0;
		WBUFW(buf,13)=0;
		WBUFW(buf,15)=0;
		WBUFW(buf,17)=0;
		WBUFW(buf,19)=0;
		WBUFB(buf,21)=0;
		WBUFB(buf,22)=fail;
	}
	else {
		if(n<0 || n>=MAX_INVENTORY || sd->status.inventory[n].nameid <=0 || sd->inventory_data[n] == NULL)
			return;

		WBUFW(buf,0)=0xa0;
		WBUFW(buf,2)=n+2;
		WBUFW(buf,4)=amount;
		if(sd->inventory_data[n]->view_id > 0)
			WBUFW(buf,6)=sd->inventory_data[n]->view_id;
		else
			WBUFW(buf,6)=sd->status.inventory[n].nameid;
		WBUFB(buf,8)=sd->status.inventory[n].identify;
		WBUFB(buf,9)=sd->status.inventory[n].attribute;
		WBUFB(buf,10)=sd->status.inventory[n].refine;
		if(sd->status.inventory[n].card[0]==0x00ff || sd->status.inventory[n].card[0]==0x00fe || sd->status.inventory[n].card[0]==(short)0xff00) {
			WBUFW(buf,11)=sd->status.inventory[n].card[0];
			WBUFW(buf,13)=sd->status.inventory[n].card[1];
			WBUFW(buf,15)=sd->status.inventory[n].card[2];
			WBUFW(buf,17)=sd->status.inventory[n].card[3];
		}
		else {
			if(sd->status.inventory[n].card[0] > 0 && (j=itemdb_viewid(sd->status.inventory[n].card[0])) > 0)
				WBUFW(buf,11)=j;
			else
				WBUFW(buf,11)=sd->status.inventory[n].card[0];
			if(sd->status.inventory[n].card[1] > 0 && (j=itemdb_viewid(sd->status.inventory[n].card[1])) > 0)
				WBUFW(buf,13)=j;
			else
				WBUFW(buf,13)=sd->status.inventory[n].card[1];
			if(sd->status.inventory[n].card[2] > 0 && (j=itemdb_viewid(sd->status.inventory[n].card[2])) > 0)
				WBUFW(buf,15)=j;
			else
				WBUFW(buf,15)=sd->status.inventory[n].card[2];
			if(sd->status.inventory[n].card[3] > 0 && (j=itemdb_viewid(sd->status.inventory[n].card[3])) > 0)
				WBUFW(buf,17)=j;
			else
				WBUFW(buf,17)=sd->status.inventory[n].card[3];
		}
		WBUFW(buf,19)=pc_equippoint(sd,n);
		WBUFB(buf,21)=(sd->inventory_data[n]->type == 7)? 4:sd->inventory_data[n]->type;
		WBUFB(buf,22)=fail;
	}

	WFIFOSET(fd,packet_db[0xa0].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_delitem(struct map_session_data *sd, int n, int amount)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xaf;
	WFIFOW(fd,2)=n+2;
	WFIFOW(fd,4)=amount;

	WFIFOSET(fd,packet_db[0xaf].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_itemlist(struct map_session_data *sd)
{
	int i,n,fd,arrow=-1;
	unsigned char *buf;

	nullpo_retv(sd);

	fd=sd->fd;
	buf = WFIFOP(fd,0);

#if PACKETVER < 5
	WBUFW(buf,0)=0xa3;
	for(i=0,n=0;i<MAX_INVENTORY;i++){
		if(sd->status.inventory[i].nameid <=0 || sd->inventory_data[i] == NULL || itemdb_isequip2(sd->inventory_data[i]))
			continue;
		WBUFW(buf,n*10+4)=i+2;
		if(sd->inventory_data[i]->view_id > 0)
			WBUFW(buf,n*10+6)=sd->inventory_data[i]->view_id;
		else
			WBUFW(buf,n*10+6)=sd->status.inventory[i].nameid;
		WBUFB(buf,n*10+8)=sd->inventory_data[i]->type;
		WBUFB(buf,n*10+9)=sd->status.inventory[i].identify;
		WBUFW(buf,n*10+10)=sd->status.inventory[i].amount;
		if(sd->inventory_data[i]->equip == 0x8000){
			WBUFW(buf,n*10+12)=0x8000;
			if(sd->status.inventory[i].equip) arrow=i;	// ついでに矢装備チェック
		}
		else
			WBUFW(buf,n*10+12)=0;
		n++;
	}
	if(n){
		WBUFW(buf,2)=4+n*10;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#else
	WBUFW(buf,0)=0x1ee;
	for(i=0,n=0;i<MAX_INVENTORY;i++){
		if(sd->status.inventory[i].nameid <=0 || sd->inventory_data[i] == NULL || itemdb_isequip2(sd->inventory_data[i]))
			continue;
		WBUFW(buf,n*18+4)=i+2;
		if(sd->inventory_data[i]->view_id > 0)
			WBUFW(buf,n*18+6)=sd->inventory_data[i]->view_id;
		else
			WBUFW(buf,n*18+6)=sd->status.inventory[i].nameid;
		WBUFB(buf,n*18+8)=sd->inventory_data[i]->type;
		WBUFB(buf,n*18+9)=sd->status.inventory[i].identify;
		WBUFW(buf,n*18+10)=sd->status.inventory[i].amount;
		if(sd->inventory_data[i]->equip == 0x8000){
			WBUFW(buf,n*18+12)=0x8000;
			if(sd->status.inventory[i].equip) arrow=i;	// ついでに矢装備チェック
		}
		else
			WBUFW(buf,n*18+12)=0;
		WBUFW(buf,n*18+14)=sd->status.inventory[i].card[0];
		WBUFW(buf,n*18+16)=sd->status.inventory[i].card[1];
		WBUFW(buf,n*18+18)=sd->status.inventory[i].card[2];
		WBUFW(buf,n*18+20)=sd->status.inventory[i].card[3];
		n++;
	}
	if(n){
		WBUFW(buf,2)=4+n*18;
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
	int i,j,n,fd;
	unsigned char *buf;

	nullpo_retv(sd);

	fd=sd->fd;
	buf = WFIFOP(fd,0);
	WBUFW(buf,0)=0xa4;
	for(i=0,n=0;i<MAX_INVENTORY;i++){
		if(sd->status.inventory[i].nameid<=0 || sd->inventory_data[i] == NULL || !itemdb_isequip2(sd->inventory_data[i]))
			continue;
		WBUFW(buf,n*20+4)=i+2;
		if(sd->inventory_data[i]->view_id > 0)
			WBUFW(buf,n*20+6)=sd->inventory_data[i]->view_id;
		else
			WBUFW(buf,n*20+6)=sd->status.inventory[i].nameid;
		WBUFB(buf,n*20+8)=(sd->inventory_data[i]->type == 7)? 4:sd->inventory_data[i]->type;
		WBUFB(buf,n*20+9)=sd->status.inventory[i].identify;
		WBUFW(buf,n*20+10)=pc_equippoint(sd,i);
		WBUFW(buf,n*20+12)=sd->status.inventory[i].equip;
		WBUFB(buf,n*20+14)=sd->status.inventory[i].attribute;
		WBUFB(buf,n*20+15)=sd->status.inventory[i].refine;
		if(sd->status.inventory[i].card[0]==0x00ff || sd->status.inventory[i].card[0]==0x00fe || sd->status.inventory[i].card[0]==(short)0xff00) {
			WBUFW(buf,n*20+16)=sd->status.inventory[i].card[0];
			WBUFW(buf,n*20+18)=sd->status.inventory[i].card[1];
			WBUFW(buf,n*20+20)=sd->status.inventory[i].card[2];
			WBUFW(buf,n*20+22)=sd->status.inventory[i].card[3];
		}
		else {
			if(sd->status.inventory[i].card[0] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[0])) > 0)
				WBUFW(buf,n*20+16)=j;
			else
				WBUFW(buf,n*20+16)=sd->status.inventory[i].card[0];
			if(sd->status.inventory[i].card[1] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[1])) > 0)
				WBUFW(buf,n*20+18)=j;
			else
				WBUFW(buf,n*20+18)=sd->status.inventory[i].card[1];
			if(sd->status.inventory[i].card[2] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[2])) > 0)
				WBUFW(buf,n*20+20)=j;
			else
				WBUFW(buf,n*20+20)=sd->status.inventory[i].card[2];
			if(sd->status.inventory[i].card[3] > 0 && (j=itemdb_viewid(sd->status.inventory[i].card[3])) > 0)
				WBUFW(buf,n*20+22)=j;
			else
				WBUFW(buf,n*20+22)=sd->status.inventory[i].card[3];
		}
		n++;
	}
	if(n){
		WBUFW(buf,2)=4+n*20;
		WFIFOSET(fd,WFIFOW(fd,2));
	}

	return;
}

/*==========================================
 * カプラさんに預けてある消耗品&収集品リスト
 *------------------------------------------
 */
void clif_storageitemlist(struct map_session_data *sd, struct storage *stor)
{
	struct item_data *id;
	int i,n,fd;
	unsigned char *buf;

	nullpo_retv(sd);
	nullpo_retv(stor);

	fd=sd->fd;
	buf = WFIFOP(fd,0);

#if PACKETVER < 5
	WBUFW(buf,0)=0xa5;
	for(i=0,n=0;i<MAX_STORAGE;i++){
		if(stor->storage[i].nameid<=0)
			continue;
		nullpo_retv(id = itemdb_search(stor->storage[i].nameid));
		if(itemdb_isequip2(id))
			continue;

		WBUFW(buf,n*10+4)=i+1;
		if(id->view_id > 0)
			WBUFW(buf,n*10+6)=id->view_id;
		else
			WBUFW(buf,n*10+6)=stor->storage[i].nameid;
		WBUFB(buf,n*10+8)=id->type;
		WBUFB(buf,n*10+9)=stor->storage[i].identify;
		WBUFW(buf,n*10+10)=stor->storage[i].amount;
		WBUFW(buf,n*10+12)=0;
		n++;
	}
	if(n){
		WBUFW(buf,2)=4+n*10;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#else
	WBUFW(buf,0)=0x1f0;
	for(i=0,n=0;i<MAX_STORAGE;i++){
		if(stor->storage[i].nameid<=0)
			continue;
		nullpo_retv(id = itemdb_search(stor->storage[i].nameid));
		if(itemdb_isequip2(id))
			continue;

		WBUFW(buf,n*18+4)=i+1;
		if(id->view_id > 0)
			WBUFW(buf,n*18+6)=id->view_id;
		else
			WBUFW(buf,n*18+6)=stor->storage[i].nameid;
		WBUFB(buf,n*18+8)=id->type;
		WBUFB(buf,n*18+9)=stor->storage[i].identify;
		WBUFW(buf,n*18+10)=stor->storage[i].amount;
		WBUFW(buf,n*18+12)=0;
		WBUFW(buf,n*18+14)=stor->storage[i].card[0];
		WBUFW(buf,n*18+16)=stor->storage[i].card[1];
		WBUFW(buf,n*18+18)=stor->storage[i].card[2];
		WBUFW(buf,n*18+20)=stor->storage[i].card[3];
		n++;
	}
	if(n){
		WBUFW(buf,2)=4+n*18;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#endif

	return;
}

/*==========================================
 * カプラさんに預けてある装備リスト
 *------------------------------------------
 */
void clif_storageequiplist(struct map_session_data *sd, struct storage *stor)
{
	struct item_data *id;
	int i,j,n,fd;
	unsigned char *buf;

	nullpo_retv(sd);
	nullpo_retv(stor);

	fd=sd->fd;
	buf = WFIFOP(fd,0);
	WBUFW(buf,0)=0xa6;
	for(i=0,n=0;i<MAX_STORAGE;i++){
		if(stor->storage[i].nameid<=0)
			continue;
		nullpo_retv(id = itemdb_search(stor->storage[i].nameid));
		if(!itemdb_isequip2(id))
			continue;
		WBUFW(buf,n*20+4)=i+1;
		if(id->view_id > 0)
			WBUFW(buf,n*20+6)=id->view_id;
		else
			WBUFW(buf,n*20+6)=stor->storage[i].nameid;
		WBUFB(buf,n*20+8)=id->type;
		WBUFB(buf,n*20+9)=stor->storage[i].identify;
		WBUFW(buf,n*20+10)=id->equip;
		WBUFW(buf,n*20+12)=stor->storage[i].equip;
		WBUFB(buf,n*20+14)=stor->storage[i].attribute;
		WBUFB(buf,n*20+15)=stor->storage[i].refine;
		if(stor->storage[i].card[0]==0x00ff || stor->storage[i].card[0]==0x00fe || stor->storage[i].card[0]==(short)0xff00) {
			WBUFW(buf,n*20+16)=stor->storage[i].card[0];
			WBUFW(buf,n*20+18)=stor->storage[i].card[1];
			WBUFW(buf,n*20+20)=stor->storage[i].card[2];
			WBUFW(buf,n*20+22)=stor->storage[i].card[3];
		}
		else {
			if(stor->storage[i].card[0] > 0 && (j=itemdb_viewid(stor->storage[i].card[0])) > 0)
				WBUFW(buf,n*20+16)=j;
			else
				WBUFW(buf,n*20+16)=stor->storage[i].card[0];
			if(stor->storage[i].card[1] > 0 && (j=itemdb_viewid(stor->storage[i].card[1])) > 0)
				WBUFW(buf,n*20+18)=j;
			else
				WBUFW(buf,n*20+18)=stor->storage[i].card[1];
			if(stor->storage[i].card[2] > 0 && (j=itemdb_viewid(stor->storage[i].card[2])) > 0)
				WBUFW(buf,n*20+20)=j;
			else
				WBUFW(buf,n*20+20)=stor->storage[i].card[2];
			if(stor->storage[i].card[3] > 0 && (j=itemdb_viewid(stor->storage[i].card[3])) > 0)
				WBUFW(buf,n*20+22)=j;
			else
				WBUFW(buf,n*20+22)=stor->storage[i].card[3];
		}
		n++;
	}
	if(n){
		WBUFW(buf,2)=4+n*20;
		WFIFOSET(fd,WFIFOW(fd,2));
	}

	return;
}

/*==========================================
 * ギルド倉庫に預けてある消耗品&収集品リスト
 * 16KB超過に備えてWFIFORESERVEする
 *------------------------------------------
 */
void clif_guildstorageitemlist(struct map_session_data *sd, struct guild_storage *stor)
{
	struct item_data *id;
	int i,n,fd;
#if PACKETVER < 5
	unsigned char buf[4+10*MAX_GUILD_STORAGE];
#else
	unsigned char buf[4+18*MAX_GUILD_STORAGE];
#endif

	nullpo_retv(sd);
	nullpo_retv(stor);

	fd=sd->fd;

#if PACKETVER < 5
	WBUFW(buf,0)=0xa5;
	for(i=0,n=0;i<MAX_GUILD_STORAGE;i++){
		if(stor->storage[i].nameid<=0)
			continue;
		nullpo_retv(id = itemdb_search(stor->storage[i].nameid));
		if(itemdb_isequip2(id))
			continue;

		WBUFW(buf,n*10+4)=i+1;
		if(id->view_id > 0)
			WBUFW(buf,n*10+6)=id->view_id;
		else
			WBUFW(buf,n*10+6)=stor->storage[i].nameid;
		WBUFB(buf,n*10+8)=id->type;
		WBUFB(buf,n*10+9)=stor->storage[i].identify;
		WBUFW(buf,n*10+10)=stor->storage[i].amount;
		WBUFW(buf,n*10+12)=0;
		n++;
	}
	if(n){
		int len=4+n*10;
		WBUFW(buf,2)=len;
		WFIFORESERVE(fd,len);
		memcpy(WFIFOP(fd,0), WBUFP(buf,0), len);
		WFIFOSET(fd,len);
	}
#else
	WBUFW(buf,0)=0x1f0;
	for(i=0,n=0;i<MAX_GUILD_STORAGE;i++){
		if(stor->storage[i].nameid<=0)
			continue;
		nullpo_retv(id = itemdb_search(stor->storage[i].nameid));
		if(itemdb_isequip2(id))
			continue;

		WBUFW(buf,n*18+4)=i+1;
		if(id->view_id > 0)
			WBUFW(buf,n*18+6)=id->view_id;
		else
			WBUFW(buf,n*18+6)=stor->storage[i].nameid;
		WBUFB(buf,n*18+8)=id->type;
		WBUFB(buf,n*18+9)=stor->storage[i].identify;
		WBUFW(buf,n*18+10)=stor->storage[i].amount;
		WBUFW(buf,n*18+12)=0;
		WBUFW(buf,n*18+14)=stor->storage[i].card[0];
		WBUFW(buf,n*18+16)=stor->storage[i].card[1];
		WBUFW(buf,n*18+18)=stor->storage[i].card[2];
		WBUFW(buf,n*18+20)=stor->storage[i].card[3];
		n++;
	}
	if(n){
		int len=4+n*18;
		WBUFW(buf,2)=len;
		WFIFORESERVE(fd,len);
		memcpy(WFIFOP(fd,0), WBUFP(buf,0), len);
		WFIFOSET(fd,len);
	}
#endif

	return;
}

/*==========================================
 * ギルド倉庫に預けてある装備品リスト
 * 16KB超過に備えてWFIFORESERVEする
 *------------------------------------------
 */
void clif_guildstorageequiplist(struct map_session_data *sd, struct guild_storage *stor)
{
	struct item_data *id;
	int i,j,n,fd;
	unsigned char buf[4+20*MAX_GUILD_STORAGE];

	nullpo_retv(sd);

	fd=sd->fd;

	WBUFW(buf,0)=0xa6;
	for(i=0,n=0;i<MAX_GUILD_STORAGE;i++){
		if(stor->storage[i].nameid<=0)
			continue;
		nullpo_retv(id = itemdb_search(stor->storage[i].nameid));
		if(!itemdb_isequip2(id))
			continue;
		WBUFW(buf,n*20+4)=i+1;
		if(id->view_id > 0)
			WBUFW(buf,n*20+6)=id->view_id;
		else
			WBUFW(buf,n*20+6)=stor->storage[i].nameid;
		WBUFB(buf,n*20+8)=id->type;
		WBUFB(buf,n*20+9)=stor->storage[i].identify;
		WBUFW(buf,n*20+10)=id->equip;
		WBUFW(buf,n*20+12)=stor->storage[i].equip;
		WBUFB(buf,n*20+14)=stor->storage[i].attribute;
		WBUFB(buf,n*20+15)=stor->storage[i].refine;
		if(stor->storage[i].card[0]==0x00ff || stor->storage[i].card[0]==0x00fe || stor->storage[i].card[0]==(short)0xff00) {
			WBUFW(buf,n*20+16)=stor->storage[i].card[0];
			WBUFW(buf,n*20+18)=stor->storage[i].card[1];
			WBUFW(buf,n*20+20)=stor->storage[i].card[2];
			WBUFW(buf,n*20+22)=stor->storage[i].card[3];
		}
		else {
			if(stor->storage[i].card[0] > 0 && (j=itemdb_viewid(stor->storage[i].card[0])) > 0)
				WBUFW(buf,n*20+16)=j;
			else
				WBUFW(buf,n*20+16)=stor->storage[i].card[0];
			if(stor->storage[i].card[1] > 0 && (j=itemdb_viewid(stor->storage[i].card[1])) > 0)
				WBUFW(buf,n*20+18)=j;
			else
				WBUFW(buf,n*20+18)=stor->storage[i].card[1];
			if(stor->storage[i].card[2] > 0 && (j=itemdb_viewid(stor->storage[i].card[2])) > 0)
				WBUFW(buf,n*20+20)=j;
			else
				WBUFW(buf,n*20+20)=stor->storage[i].card[2];
			if(stor->storage[i].card[3] > 0 && (j=itemdb_viewid(stor->storage[i].card[3])) > 0)
				WBUFW(buf,n*20+22)=j;
			else
				WBUFW(buf,n*20+22)=stor->storage[i].card[3];
		}
		n++;
	}
	if(n){
		int len=4+n*20;
		WBUFW(buf,2)=len;
		WFIFORESERVE(fd,len);
		memcpy(WFIFOP(fd,0), WBUFP(buf,0), len);
		WFIFOSET(fd,len);
	}

	return;
}

/*==========================================
 * GMへ場所とHP通知
 *------------------------------------------
 */
static void clif_hpmeter(struct map_session_data *sd)
{
	struct map_session_data *md;
	unsigned char buf[16];
	unsigned char buf2[16];
	int i;

	nullpo_retv(sd);

	WBUFW(buf,0)=0x107;
	WBUFL(buf,2)=sd->bl.id;
	WBUFW(buf,6)=sd->bl.x;
	WBUFW(buf,8)=sd->bl.y;

	for(i=0;i<fd_max;i++){
		if(session[i] && (md=session[i]->session_data) && md->state.auth &&
		   md->bl.m == sd->bl.m && pc_isGM(md) && sd != md){
			memcpy(WFIFOP(i,0),buf,packet_db[0x107].len);
			WFIFOSET(i,packet_db[0x107].len);
		}
	}

	WBUFW(buf2,0)=0x106;
	WBUFL(buf2,2)=sd->status.account_id;
	WBUFW(buf2,6)=(sd->status.hp > 0x7fff)? 0x7fff:sd->status.hp;
	WBUFW(buf2,8)=(sd->status.max_hp > 0x7fff)? 0x7fff:sd->status.max_hp;
	for(i=0;i<fd_max;i++){
		if(session[i] && (md=session[i]->session_data) && md->state.auth &&
		   sd->bl.m == md->bl.m && pc_isGM(md) && sd != md){
			memcpy(WFIFOP(i,0),buf2,packet_db[0x106].len);
			WFIFOSET(i,packet_db[0x106].len);
		}
	}

	return;
}

/*==========================================
 * ステータスを送りつける
 * 表示専用数字はこの中で計算して送る
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
		WFIFOL(fd,4)=sd->aspd;
		break;
	case SP_ATK1:
		WFIFOL(fd,4)=sd->base_atk+sd->watk;
		break;
	case SP_DEF1:
		WFIFOL(fd,4)=sd->def;
		break;
	case SP_MDEF1:
		WFIFOL(fd,4)=sd->mdef;
		break;
	case SP_ATK2:
		WFIFOL(fd,4)=sd->watk2;
		break;
	case SP_DEF2:
		WFIFOL(fd,4)=sd->def2;
		break;
	case SP_MDEF2:
		WFIFOL(fd,4)=sd->mdef2;
		break;
	case SP_CRITICAL:
		WFIFOL(fd,4)=sd->critical/10;
		break;
	case SP_MATK1:
		WFIFOL(fd,4)=sd->matk1;
		break;
	case SP_MATK2:
		WFIFOL(fd,4)=sd->matk2;
		break;

		// 00b1 終了
	case SP_ZENY:
		WFIFOW(fd,0)=0xb1;
		WFIFOL(fd,4)=sd->status.zeny;
		break;
	case SP_BASEEXP:
		WFIFOW(fd,0)=0xb1;
		WFIFOL(fd,4)=sd->status.base_exp;
		break;
	case SP_JOBEXP:
		WFIFOW(fd,0)=0xb1;
		WFIFOL(fd,4)=sd->status.job_exp;
		break;
	case SP_NEXTBASEEXP:
		WFIFOW(fd,0)=0xb1;
		WFIFOL(fd,4)=pc_nextbaseexp(sd);
		break;
	case SP_NEXTJOBEXP:
		WFIFOW(fd,0)=0xb1;
		WFIFOL(fd,4)=pc_nextjobexp(sd);
		break;

		// 00be 終了
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

		// 013a 終了
	case SP_ATTACKRANGE:
		WFIFOW(fd,0)=0x13a;
		WFIFOW(fd,2)=sd->attackrange;
		len=4;
		break;

		// 0141 終了
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
	unsigned char buf[12];
	struct map_session_data *sd = NULL;

	nullpo_retv(bl);

	if(type == SP_MANNER && battle_config.nomanner_mode)
		return;

	if(bl->type == BL_PC)
		sd = (struct map_session_data *)bl;

//printf("clif_changestatus id:%d type:%d val:%d\n",bl->id,type,val);
	if(sd){
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
	struct map_session_data *sd = NULL;

	nullpo_retv(bl);

	if(bl->type == BL_PC)
		sd = (struct map_session_data *)bl;

	if(sd && type == LOOK_BASE)
		val = sd->view_class;

#if PACKETVER < 4
	if(sd && (type == LOOK_WEAPON || type == LOOK_SHIELD) && (sd->view_class == 22 || sd->view_class == 26))
		val = 0;
	WBUFW(buf,0)=0xc3;
	WBUFL(buf,2)=bl->id;
	WBUFB(buf,6)=type;
	WBUFB(buf,7)=val;
	clif_send(buf,packet_db[0xc3].len,bl,AREA);
#else
	if(bl->type == BL_SKILL && type == LOOK_BASE) {		// トラップのユニットID変更
		WBUFW(buf,0)=0xc3;
		WBUFL(buf,2)=bl->id;
		WBUFB(buf,6)=type;
		WBUFB(buf,7)=val;
		clif_send(buf,packet_db[0xc3].len,bl,AREA);
	}
	else {
		int idx=0, shield=0;
		if(sd) {
			switch (type) {
			case LOOK_SHOES:
				val = 0;
				if((idx = sd->equip_index[2]) >= 0 && sd->inventory_data[idx]) {
					if(sd->inventory_data[idx]->view_id > 0)
						val = sd->inventory_data[idx]->view_id;
					else
						val = sd->status.inventory[idx].nameid;
				}
				break;
			case LOOK_WEAPON:
			case LOOK_SHIELD:
				val = 0;
				type = LOOK_WEAPON;
				if(sd->view_class == 22 || sd->view_class == 26)
					break;
				if((idx = sd->equip_index[9]) >= 0 && sd->inventory_data[idx]) {
					if(sd->inventory_data[idx]->view_id > 0)
						val = sd->inventory_data[idx]->view_id;
					else
						val = sd->status.inventory[idx].nameid;
				}
				if((idx = sd->equip_index[8]) >= 0 && idx != sd->equip_index[9] && sd->inventory_data[idx]) {
					if(sd->inventory_data[idx]->view_id > 0)
						shield = sd->inventory_data[idx]->view_id;
					else
						shield = sd->status.inventory[idx].nameid;
				}
				break;
			}
		}
		WBUFW(buf,0)=0x1d7;
		WBUFL(buf,2)=bl->id;
		WBUFB(buf,6)=type;
		WBUFW(buf,7)=val;
		WBUFW(buf,9)=shield;
		clif_send(buf,packet_db[0x1d7].len,bl,AREA);
	}
#endif
	return;
}

/*==========================================
 * 服色パケット送り付け（基本色を除く）
 *------------------------------------------
 */
void clif_send_clothcolor(struct block_list *bl)
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
	WBUFB(buf,7) = color;
	clif_send(buf,packet_db[0xc3].len,bl,AREA);
#else
	WBUFW(buf,0) = 0x1d7;
	WBUFL(buf,2) = bl->id;
	WBUFB(buf,6) = LOOK_CLOTHES_COLOR;
	WBUFW(buf,7) = color;
	WBUFW(buf,9)=0;
	clif_send(buf,packet_db[0x1d7].len,bl,AREA);
#endif
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_initialstatus(struct map_session_data *sd)
{
	int fd;
	unsigned char *buf;

	nullpo_retv(sd);

	fd=sd->fd;
	buf=WFIFOP(fd,0);

	WBUFW(buf,0)=0xbd;
	WBUFW(buf,2)=sd->status.status_point;
	WBUFB(buf,4)=(sd->status.str > 255)? 255:sd->status.str;
	WBUFB(buf,5)=pc_need_status_point(sd,SP_STR);
	WBUFB(buf,6)=(sd->status.agi > 255)? 255:sd->status.agi;
	WBUFB(buf,7)=pc_need_status_point(sd,SP_AGI);
	WBUFB(buf,8)=(sd->status.vit > 255)? 255:sd->status.vit;
	WBUFB(buf,9)=pc_need_status_point(sd,SP_VIT);
	WBUFB(buf,10)=(sd->status.int_ > 255)? 255:sd->status.int_;
	WBUFB(buf,11)=pc_need_status_point(sd,SP_INT);
	WBUFB(buf,12)=(sd->status.dex > 255)? 255:sd->status.dex;
	WBUFB(buf,13)=pc_need_status_point(sd,SP_DEX);
	WBUFB(buf,14)=(sd->status.luk > 255)? 255:sd->status.luk;
	WBUFB(buf,15)=pc_need_status_point(sd,SP_LUK);

	WBUFW(buf,16) = sd->base_atk + sd->watk;
	WBUFW(buf,18) = sd->watk2; //atk bonus
	WBUFW(buf,20) = sd->matk1;
	WBUFW(buf,22) = sd->matk2;
	WBUFW(buf,24) = sd->def; // def
	WBUFW(buf,26) = sd->def2;
	WBUFW(buf,28) = sd->mdef; // mdef
	WBUFW(buf,30) = sd->mdef2;
	WBUFW(buf,32) = sd->hit;
	WBUFW(buf,34) = sd->flee;
	WBUFW(buf,36) = sd->flee2/10;
	WBUFW(buf,38) = sd->critical/10;
	WBUFW(buf,40) = sd->status.karma;
	WBUFW(buf,42) = sd->status.manner;

	WFIFOSET(fd,packet_db[0xbd].len);

	clif_updatestatus(sd,SP_STR);
	clif_updatestatus(sd,SP_AGI);
	clif_updatestatus(sd,SP_VIT);
	clif_updatestatus(sd,SP_INT);
	clif_updatestatus(sd,SP_DEX);
	clif_updatestatus(sd,SP_LUK);

	clif_updatestatus(sd,SP_ATTACKRANGE);
	clif_updatestatus(sd,SP_ASPD);

	return;
}

/*==========================================
 *矢装備
 *------------------------------------------
 */
void clif_arrowequip(struct map_session_data *sd, int val)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x013c;
	WFIFOW(fd,2)=val+2;//矢のアイテムID
	WFIFOSET(fd,packet_db[0x013c].len);

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
	WFIFOW(fd,0)=0x013b;
	WFIFOW(fd,2)=type;
	WFIFOSET(fd,packet_db[0x013b].len);

	return;
}

/*==========================================
 * 作成可能 矢リスト送信
 *------------------------------------------
 */
void clif_arrow_create_list(struct map_session_data *sd)
{
	int i,c,view;
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x1ad;

	for(i=0,c=0;i<MAX_SKILL_ARROW_DB;i++){
		if(skill_arrow_db[i].nameid > 0 && pc_search_inventory(sd,skill_arrow_db[i].nameid)>=0){
			if((view = itemdb_viewid(skill_arrow_db[i].nameid)) > 0)
				WFIFOW(fd,c*2+4) = view;
			else
				WFIFOW(fd,c*2+4) = skill_arrow_db[i].nameid;
			c++;
		}
	}
	WFIFOW(fd,2)=c*2+4;
	WFIFOSET(fd,WFIFOW(fd,2));
	if(c > 0) sd->state.make_arrow_flag = 1;

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
	WFIFOW(fd,0)=0xaa;
	WFIFOW(fd,2)=n+2;
	WFIFOW(fd,4)=pos;
	WFIFOB(fd,6)=ok;
	WFIFOSET(fd,packet_db[0xaa].len);

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
	WFIFOW(fd,0)=0xac;
	WFIFOW(fd,2)=n+2;
	WFIFOW(fd,4)=pos;
	WFIFOB(fd,6)=ok;
	WFIFOSET(fd,packet_db[0xac].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_misceffect(struct block_list* bl, int type)
{
	char buf[16];

	nullpo_retv(bl);

	WBUFW(buf,0) = 0x19b;
	WBUFL(buf,2) = bl->id;
	WBUFL(buf,6) = type;
	clif_send(buf,packet_db[0x19b].len,bl,AREA);

	return;
}

/*==========================================
 * blから発生するエフェクト
 *------------------------------------------
 */
void clif_misceffect2(struct block_list *bl,int type)
{
	char buf[16];

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
void clif_misceffect3(struct block_list *bl,int type)
{
	char buf[16];

	nullpo_retv(bl);

	WBUFW(buf,0)=0x1f3;
	WBUFL(buf,2)=bl->id;
	WBUFL(buf,6)=type;
	clif_send(buf,packet_db[0x1f3].len,bl,SELF);

	return;
}

/*==========================================
 * 表示オプション変更
 *------------------------------------------
 */
void clif_changeoption(struct block_list* bl)
{
	char buf[16];
	short option;
	struct status_change *sc_data;
	struct map_session_data *sd;
	static const int omask[]={ 0x10,0x20 };
	static const int scnum[]={ SC_FALCON, SC_RIDING };
	int i;

	nullpo_retv(bl);

	if(bl->type==BL_PC && (sd=(struct map_session_data *)bl))
		clif_changelook(bl,LOOK_BASE,sd->view_class);

	option = *status_get_option(bl);
	sc_data = status_get_sc_data(bl);

#if PACKETVER < 7
	WBUFW(buf,0) = 0x119;
	WBUFL(buf,2) = bl->id;
	WBUFW(buf,6) = *status_get_opt1(bl);
	WBUFW(buf,8) = *status_get_opt2(bl);
	WBUFW(buf,10) = option;
	WBUFB(buf,12) = 0;	// ??
	clif_send(buf,packet_db[0x119].len,bl,AREA);
#else
	WBUFW(buf, 0) = 0x0229;
	WBUFL(buf, 2) = bl->id;
	WBUFW(buf, 6) = *status_get_opt1(bl);
	WBUFW(buf, 8) = *status_get_opt2(bl);
	WBUFL(buf,10) = option;
	WBUFB(buf,14) = 0;
	clif_send(buf,packet_db[0x229].len,bl,AREA);
#endif

	// アイコンの表示
	if(sc_data){
		for(i=0;i<sizeof(omask)/sizeof(omask[0]);i++){
			if( option&omask[i] ){
				if( sc_data[scnum[i]].timer==-1)
					status_change_start(bl,scnum[i],0,0,0,0,0,0);
			}else{
				status_change_end(bl,scnum[i],-1);
			}
		}
	}

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
	}
	else {
#if PACKETVER < 3
		int fd=sd->fd;
		WFIFOW(fd,0)=0xa8;
		WFIFOW(fd,2)=idx+2;
		WFIFOW(fd,4)=amount;
		WFIFOB(fd,6)=ok;
		WFIFOSET(fd,packet_db[0xa8].len);
#else
		char buf[16];

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
	char buf[128];	// 最大title(60バイト)+17

	if(cd==NULL || *cd->owner==NULL)
		return;

	WBUFW(buf, 0)=0xd7;
	WBUFW(buf, 2)=strlen(cd->title)+18;
	WBUFL(buf, 4)=(*cd->owner)->id;
	WBUFL(buf, 8)=cd->bl.id;
	WBUFW(buf,12)=cd->limit;
	WBUFW(buf,14)=cd->users;
	WBUFB(buf,16)=cd->pub;
	strncpy(WBUFP(buf,17),cd->title,strlen(cd->title)+1);
	if(fd){
		memcpy(WFIFOP(fd,0),buf,WBUFW(buf,2));
		WFIFOSET(fd,WBUFW(buf,2));
	} else {
		clif_send(buf,WBUFW(buf,2),*cd->owner,AREA_WOSC);
	}

	return;
}

/*==========================================
 * chatの状態変更成功
 * 外部の人用と命令コード(d7->df)が違うだけ
 *------------------------------------------
 */
void clif_changechatstatus(struct chat_data *cd)
{
	char buf[128];	// 最大title(60バイト)+17

	if(cd==NULL || cd->usersd[0]==NULL)
		return;

	WBUFW(buf, 0)=0xdf;
	WBUFW(buf, 2)=strlen(cd->title)+18;
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
	char buf[8];

	nullpo_retv(cd);

	WBUFW(buf,0)=0xd8;
	WBUFL(buf,2)=cd->bl.id;
	if(fd){
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
	int fd;
	int i;

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
	char buf[32];

	nullpo_retv(sd);
	nullpo_retv(cd);

	WBUFW(buf, 0) = 0x0dc;
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
	char buf[64];

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
	char buf[32];

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
 * 取り引き要請受け
 *------------------------------------------
 */
void clif_traderequest(struct map_session_data *sd, char *name)
{
	int fd;
#if PACKETVER >= 6
	struct map_session_data *target_sd;
#endif

	nullpo_retv(sd);

	fd=sd->fd;
#if PACKETVER < 6
	WFIFOW(fd,0)=0xe5;
	strncpy(WFIFOP(fd,2),name,24);
	WFIFOSET(fd,packet_db[0xe5].len);
#else
	nullpo_retv((target_sd = map_id2sd(sd->trade_partner)));

	WFIFOW(fd,0)=0x1f4;
	strncpy(WFIFOP(fd,2),name,24);
	WFIFOL(fd,26)=target_sd->status.char_id;	//良く分からないからとりあえずchar_id
	WFIFOW(fd,30)=target_sd->status.base_level;
	WFIFOSET(fd,packet_db[0x1f4].len);
#endif

	return;
}

/*==========================================
 * 取り引き要求応答
 *------------------------------------------

 */
void clif_tradestart(struct map_session_data *sd, unsigned char type)
{
	int fd;
#if PACKETVER >= 6
	struct map_session_data *target_sd;
#endif

	nullpo_retv(sd);

	fd=sd->fd;
#if PACKETVER < 6
	WFIFOW(fd,0)=0xe7;
	WFIFOB(fd,2)=type;
	WFIFOSET(fd,packet_db[0xe7].len);
#else
	target_sd = map_id2sd(sd->trade_partner);
	WFIFOW(fd,0)=0x1f5;
	WFIFOB(fd,2)=type;
	WFIFOL(fd,3)=(target_sd!=NULL)?target_sd->status.char_id:0;	//良く分からないからとりあえずchar_id
	WFIFOW(fd,7)=(target_sd!=NULL)?target_sd->status.base_level:0;
	WFIFOSET(fd,packet_db[0x1f5].len);
#endif

	return;
}

/*==========================================
 * 相手方からのアイテム追加
 *------------------------------------------
 */
void clif_tradeadditem(struct map_session_data *sd,struct map_session_data *tsd, int idx, int amount)
{
	int fd,j;

	nullpo_retv(sd);
	nullpo_retv(tsd);

	fd=tsd->fd;
	WFIFOW(fd,0)=0xe9;
	WFIFOL(fd,2)=amount;
	if(idx==0){
		WFIFOW(fd,6) = 0; // type id
		WFIFOB(fd,8) = 0; //identify flag
		WFIFOB(fd,9) = 0; // attribute
		WFIFOB(fd,10)= 0; //refine
		WFIFOW(fd,11)= 0; //card (4w)
		WFIFOW(fd,13)= 0; //card (4w)
		WFIFOW(fd,15)= 0; //card (4w)
		WFIFOW(fd,17)= 0; //card (4w)
	}
	else{
		idx -= 2;
		if(sd->inventory_data[idx] && sd->inventory_data[idx]->view_id > 0)
			WFIFOW(fd,6) = sd->inventory_data[idx]->view_id;
		else
			WFIFOW(fd,6) = sd->status.inventory[idx].nameid; // type id
		WFIFOB(fd,8) = sd->status.inventory[idx].identify; //identify flag
		WFIFOB(fd,9) = sd->status.inventory[idx].attribute; // attribute
		WFIFOB(fd,10)= sd->status.inventory[idx].refine; //refine
		if(sd->status.inventory[idx].card[0]==0x00ff || sd->status.inventory[idx].card[0]==0x00fe || sd->status.inventory[idx].card[0]==(short)0xff00) {
			WFIFOW(fd,11)= sd->status.inventory[idx].card[0]; //card (4w)
			WFIFOW(fd,13)= sd->status.inventory[idx].card[1]; //card (4w)
			WFIFOW(fd,15)= sd->status.inventory[idx].card[2]; //card (4w)
			WFIFOW(fd,17)= sd->status.inventory[idx].card[3]; //card (4w)
		}
		else {
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

	return;
}

/*==========================================
 * アイテム追加成功/失敗
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
 * 取り引きok押し
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
 * 取り引きがキャンセルされました
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
 * 取り引き完了
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
 * カプラ倉庫のアイテム数を更新
 *------------------------------------------
 */
void clif_updatestorageamount(struct map_session_data *sd, struct storage *stor)
{
	int fd;

	nullpo_retv(sd);
	nullpo_retv(stor);

	fd=sd->fd;
	WFIFOW(fd,0) = 0xf2;  // update storage amount
	WFIFOW(fd,2) = stor->storage_amount;  //items
	WFIFOW(fd,4) = MAX_STORAGE; //items max
	WFIFOSET(fd,packet_db[0xf2].len);

	return;
}

/*==========================================
 * カプラ倉庫にアイテムを追加する
 *------------------------------------------
 */
void clif_storageitemadded(struct map_session_data *sd, struct storage *stor, int idx, int amount)
{
	int view,fd,j;

	nullpo_retv(sd);
	nullpo_retv(stor);

	fd=sd->fd;
	WFIFOW(fd,0) =0xf4; // Storage item added
	WFIFOW(fd,2) =idx+1; // index
	WFIFOL(fd,4) =amount; // amount
	if((view = itemdb_viewid(stor->storage[idx].nameid)) > 0)
		WFIFOW(fd,8) =view;
	else
		WFIFOW(fd,8) =stor->storage[idx].nameid; // id
	WFIFOB(fd,10)=stor->storage[idx].identify; //identify flag
	WFIFOB(fd,11)=stor->storage[idx].attribute; // attribute
	WFIFOB(fd,12)=stor->storage[idx].refine; //refine
	if(stor->storage[idx].card[0]==0x00ff || stor->storage[idx].card[0]==0x00fe || stor->storage[idx].card[0]==(short)0xff00) {
		WFIFOW(fd,13)=stor->storage[idx].card[0]; //card (4w)
		WFIFOW(fd,15)=stor->storage[idx].card[1]; //card (4w)
		WFIFOW(fd,17)=stor->storage[idx].card[2]; //card (4w)
		WFIFOW(fd,19)=stor->storage[idx].card[3]; //card (4w)
	}
	else {
		if(stor->storage[idx].card[0] > 0 && (j=itemdb_viewid(stor->storage[idx].card[0])) > 0)
			WFIFOW(fd,13)= j;
		else
			WFIFOW(fd,13)= stor->storage[idx].card[0];
		if(stor->storage[idx].card[1] > 0 && (j=itemdb_viewid(stor->storage[idx].card[1])) > 0)
			WFIFOW(fd,15)= j;
		else
			WFIFOW(fd,15)= stor->storage[idx].card[1];
		if(stor->storage[idx].card[2] > 0 && (j=itemdb_viewid(stor->storage[idx].card[2])) > 0)
			WFIFOW(fd,17)= j;
		else
			WFIFOW(fd,17)= stor->storage[idx].card[2];
		if(stor->storage[idx].card[3] > 0 && (j=itemdb_viewid(stor->storage[idx].card[3])) > 0)
			WFIFOW(fd,19)= j;
		else
			WFIFOW(fd,19)= stor->storage[idx].card[3];
	}
	WFIFOSET(fd,packet_db[0xf4].len);

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
	WFIFOW(fd,0) = 0xf2;  // update storage amount
	WFIFOW(fd,2) = stor->storage_amount;  //items
	WFIFOW(fd,4) = MAX_GUILD_STORAGE; //items max
	WFIFOSET(fd,packet_db[0xf2].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_guildstorageitemadded(struct map_session_data *sd, struct guild_storage *stor, int idx, int amount)
{
	int view,fd,j;

	nullpo_retv(sd);
	nullpo_retv(stor);

	fd=sd->fd;
	WFIFOW(fd,0) =0xf4; // Storage item added
	WFIFOW(fd,2) =idx+1; // index
	WFIFOL(fd,4) =amount; // amount
	if((view = itemdb_viewid(stor->storage[idx].nameid)) > 0)
		WFIFOW(fd,8) =view;
	else
		WFIFOW(fd,8) =stor->storage[idx].nameid; // id
	WFIFOB(fd,10)=stor->storage[idx].identify; //identify flag
	WFIFOB(fd,11)=stor->storage[idx].attribute; // attribute
	WFIFOB(fd,12)=stor->storage[idx].refine; //refine
	if(stor->storage[idx].card[0]==0x00ff || stor->storage[idx].card[0]==0x00fe || stor->storage[idx].card[0]==(short)0xff00) {
		WFIFOW(fd,13)=stor->storage[idx].card[0]; //card (4w)
		WFIFOW(fd,15)=stor->storage[idx].card[1]; //card (4w)
		WFIFOW(fd,17)=stor->storage[idx].card[2]; //card (4w)
		WFIFOW(fd,19)=stor->storage[idx].card[3]; //card (4w)
	}
	else {
		if(stor->storage[idx].card[0] > 0 && (j=itemdb_viewid(stor->storage[idx].card[0])) > 0)
			WFIFOW(fd,13)= j;
		else
			WFIFOW(fd,13)= stor->storage[idx].card[0];
		if(stor->storage[idx].card[1] > 0 && (j=itemdb_viewid(stor->storage[idx].card[1])) > 0)
			WFIFOW(fd,15)= j;
		else
			WFIFOW(fd,15)= stor->storage[idx].card[1];
		if(stor->storage[idx].card[2] > 0 && (j=itemdb_viewid(stor->storage[idx].card[2])) > 0)
			WFIFOW(fd,17)= j;
		else
			WFIFOW(fd,17)= stor->storage[idx].card[2];
		if(stor->storage[idx].card[3] > 0 && (j=itemdb_viewid(stor->storage[idx].card[3])) > 0)
			WFIFOW(fd,19)= j;
		else
			WFIFOW(fd,19)= stor->storage[idx].card[3];
	}
	WFIFOSET(fd,packet_db[0xf4].len);

	return;
}

/*==========================================
 * カプラ倉庫からアイテムを取り去る
 *------------------------------------------
 */
void clif_storageitemremoved(struct map_session_data *sd, int idx, int amount)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xf6; // Storage item removed
	WFIFOW(fd,2)=idx+1;
	WFIFOL(fd,4)=amount;
	WFIFOSET(fd,packet_db[0xf6].len);

	return;
}

/*==========================================
 * カプラ倉庫を閉じる
 *------------------------------------------
 */
void clif_storageclose(struct map_session_data *sd)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0xf8; // Storage Closed
	WFIFOSET(fd,packet_db[0xf8].len);

	return;
}

//
// callback系 ?
//
/*==========================================
 * PC表示
 *------------------------------------------
 */
static void clif_getareachar_pc(struct map_session_data* sd,struct map_session_data* dstsd)
{
	int len;

	nullpo_retv(sd);
	nullpo_retv(dstsd);

	if(dstsd->ud.walktimer != -1){
		len = clif_set007b(dstsd,WFIFOP(sd->fd,0));
		WFIFOSET(sd->fd,len);
	} else {
		len = clif_set0078(dstsd,WFIFOP(sd->fd,0));
		WFIFOSET(sd->fd,len);
	}

	if(dstsd->chatID){
		struct chat_data *cd = map_id2cd(dstsd->chatID);
		if(cd && cd->usersd[0]==dstsd)
			clif_dispchat(cd,sd->fd);
	}
	if(dstsd->vender_id){
		clif_showvendingboard(&dstsd->bl,dstsd->message,sd->fd);
	}

	//if(!pc_ishiding(dstsd) && dstsd->spiritball > 0 && dstsd->it_is_found==0) {
	if(dstsd->spiritball > 0) {
		clif_set01e1(dstsd,WFIFOP(sd->fd,0));
		WFIFOSET(sd->fd,packet_db[0x1e1].len);
	}

	clif_send_clothcolor(&dstsd->bl);
	if(sd->status.manner < 0)
		clif_changestatus(&sd->bl,SP_MANNER,sd->status.manner);
	if(dstsd->view_size!=0)
		clif_misceffect2(&dstsd->bl,422+dstsd->view_size);

	return;
}

/*==========================================
 * NPC表示
 *------------------------------------------
 */
static void clif_getareachar_npc(struct map_session_data* sd,struct npc_data* nd)
{
	int len;

	nullpo_retv(sd);
	nullpo_retv(nd);

	if(nd->class < 0 ||(nd->flag&1 && nd->option != 0x0002) || nd->class == INVISIBLE_CLASS)
		return;

	len = clif_npc0078(nd,WFIFOP(sd->fd,0));
	WFIFOSET(sd->fd,len);

	if(nd->chat_id){
		clif_dispchat(map_id2cd(nd->chat_id),sd->fd);
	}

	if(nd->view_size!=0)
		clif_misceffect2(&nd->bl,422+nd->view_size);

	return;
}

/*==========================================
 * 移動停止
 *------------------------------------------
 */
void clif_movemob(struct mob_data *md)
{
	unsigned char buf[128];
	int len;

	nullpo_retv(md);

	len = clif_mob007b(md,buf);
	clif_send(buf,len,&md->bl,AREA);

	clif_send_clothcolor(&md->bl);

	return;
}

/*==========================================
 * 通常攻撃エフェクト＆ダメージ
 *------------------------------------------
 */
void clif_damage(struct block_list *src, struct block_list *dst, unsigned int tick, int sdelay, int ddelay, int damage, int div, int type, int damage2)
{
	unsigned char buf[32];
	struct status_change *sc_data;

	nullpo_retv(src);
	nullpo_retv(dst);

	sc_data = status_get_sc_data(dst);

	if(type != 4 && dst->type == BL_PC) {
		if( ((struct map_session_data *)dst)->special_state.infinite_endure )
			type = 9;
		if( sc_data && (sc_data[SC_ENDURE].timer != -1 || sc_data[SC_BERSERK].timer != -1) && !map[dst->m].flag.gvg )
			type = 9;
	}
	if(sc_data && sc_data[SC_HALLUCINATION].timer != -1) {
		if(damage > 0)
			damage = damage*(5+sc_data[SC_HALLUCINATION].val1) + rand()%100;
		if(damage2 > 0)
			damage2 = damage2*(5+sc_data[SC_HALLUCINATION].val1) + rand()%100;
	}

	WBUFW(buf,0)=0x8a;
	WBUFL(buf,2)=src->id;
	WBUFL(buf,6)=dst->id;
	WBUFL(buf,10)=tick;
	WBUFL(buf,14)=sdelay;
	WBUFL(buf,18)=ddelay;
	WBUFW(buf,22)=(damage > 0x7fff)? 0x7fff:damage;
	WBUFW(buf,24)=div;
	WBUFB(buf,26)=type;
	WBUFW(buf,27)=damage2;
	clif_send(buf,packet_db[0x8a].len,src,AREA);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_getareachar_mob(struct map_session_data* sd, struct mob_data* md)
{
	int len;
	nullpo_retv(sd);
	nullpo_retv(md);

	if(md->ud.walktimer != -1){
		len = clif_mob007b(md,WFIFOP(sd->fd,0));
		WFIFOSET(sd->fd,len);
	} else {
		len = clif_mob0078(md,WFIFOP(sd->fd,0));
		WFIFOSET(sd->fd,len);
	}

	clif_send_clothcolor(&md->bl);
	if(md->view_size!=0)
		clif_misceffect2(&md->bl,422+md->view_size);

	return;
}

/*==========================================
 *
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

	clif_send_clothcolor(&pd->bl);
	if(pd->view_size!=0)
		clif_misceffect2(&pd->bl,422+pd->view_size);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_getareachar_hom(struct map_session_data* sd, struct homun_data* hd)
{
	int len;

	nullpo_retv(sd);
	nullpo_retv(hd);

	if(hd->ud.walktimer != -1){
		len = clif_hom007b(hd,WFIFOP(sd->fd,0));
		WFIFOSET(sd->fd,len);
	} else {
		// 0x78だと座標ズレを起こす
		//len = clif_hom0078(hd,WFIFOP(sd->fd,0));
		//WFIFOSET(sd->fd,len);
		len = clif_hom007b(hd,WFIFOP(sd->fd,0));
		WFIFOSET(sd->fd,len);
	}
	if(hd->view_size!=0)
		clif_misceffect2(&hd->bl,422+hd->view_size);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_getareachar_item(struct map_session_data* sd, struct flooritem_data* fitem)
{
	int view,fd;

	nullpo_retv(sd);
	nullpo_retv(fitem);

	fd=sd->fd;
	//009d <ID>.l <item ID>.w <identify flag>.B <X>.w <Y>.w <amount>.w <subX>.B <subY>.B
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
	WFIFOB(fd,15)=(unsigned char)fitem->subx;
	WFIFOB(fd,16)=(unsigned char)fitem->suby;

	WFIFOSET(fd,packet_db[0x9d].len);

	return;
}

/*==========================================
 * 場所スキルエフェクトが視界に入る
 *------------------------------------------
 */
static void clif_getareachar_skillunit(struct map_session_data *sd, struct skill_unit *unit)
{
	int fd;

	nullpo_retv(unit);

	fd=sd->fd;

#if PACKETVER >= 3
	if(unit->group->unit_id == 0xb0) {	//グラフィティ
		memset(WFIFOP(fd,0),0,packet_db[0x1c9].len);
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

		return;
	}
#endif
	memset(WFIFOP(fd,0),0,packet_db[0x11f].len);
	WFIFOW(fd, 0)=0x11f;
	WFIFOL(fd, 2)=unit->bl.id;
	WFIFOL(fd, 6)=unit->group->src_id;
	WFIFOW(fd,10)=unit->bl.x;
	WFIFOW(fd,12)=unit->bl.y;
	//旧GS_GROUNDDRIFT?
	if(unit->group->skill_id!=GS_GROUNDDRIFT)
	{
		WFIFOB(fd,14)=unit->group->unit_id;
	}else{
		WFIFOB(fd,14)=grounddrift_unit_id[unit->group->val1-13203];
	}
	WFIFOB(fd,15)=0;
	WFIFOSET(fd,packet_db[0x11f].len);

	if(unit->group->skill_id == WZ_ICEWALL)
		clif_set0192(fd,unit->bl.m,unit->bl.x,unit->bl.y,5);

	return;
}

/*==========================================
 * 場所スキルエフェクトが視界から消える
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
	char buf[8];

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

	sd=va_arg(ap,struct map_session_data*);

	switch(bl->type){
	case BL_PC:
		if(&sd->bl != bl)
			clif_getareachar_pc(sd,(struct map_session_data*) bl);
		break;
	case BL_NPC:
		clif_getareachar_npc(sd,(struct npc_data*) bl);
		break;
	case BL_MOB:
		clif_getareachar_mob(sd,(struct mob_data*) bl);
		break;
	case BL_PET:
		clif_getareachar_pet(sd,(struct pet_data*) bl);
		break;
	case BL_ITEM:
		clif_getareachar_item(sd,(struct flooritem_data*) bl);
		break;
	case BL_SKILL:
		clif_getareachar_skillunit(sd,(struct skill_unit *)bl);
		break;
	case BL_HOM:
		clif_getareachar_hom(sd,(struct homun_data*) bl);
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
	struct map_session_data *sd,*dstsd;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, sd=va_arg(ap,struct map_session_data*));

	switch(bl->type){
	case BL_PC:
		dstsd = (struct map_session_data*) bl;
		if(dstsd && sd != dstsd) {
			clif_clearchar_id(dstsd->bl.id,0,sd->fd);
			clif_clearchar_id(sd->bl.id,0,dstsd->fd);
			if(dstsd->chatID){
				struct chat_data *cd = map_id2cd(dstsd->chatID);
				if(cd && cd->usersd[0]==dstsd)
					clif_dispchat(cd,sd->fd);
			}
			if(dstsd->vender_id){
				clif_closevendingboard(&dstsd->bl,sd->fd);
			}
		}
		break;
	case BL_NPC:
		if( ((struct npc_data *)bl)->class != INVISIBLE_CLASS )
			clif_clearchar_id(bl->id,0,sd->fd);
		break;
	case BL_MOB:
	case BL_PET:
	case BL_HOM:
		clif_clearchar_id(bl->id,0,sd->fd);
		break;
	case BL_ITEM:
		clif_clearflooritem((struct flooritem_data*)bl,sd->fd);
		break;
	case BL_SKILL:
		clif_clearchar_skillunit((struct skill_unit *)bl,sd->fd);
		break;
	}

	return 0;
}

/*==========================================
 *視野
 *------------------------------------------
 */
int clif_pcinsight(struct block_list *bl,va_list ap)
{
	struct map_session_data *sd,*dstsd;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, sd=va_arg(ap,struct map_session_data*));

	switch(bl->type){
	case BL_PC:
		dstsd = (struct map_session_data *)bl;
		if(sd != dstsd) {
			clif_getareachar_pc(sd,dstsd);
			clif_getareachar_pc(dstsd,sd);
		}
		break;
	case BL_NPC:
		clif_getareachar_npc(sd,(struct npc_data*)bl);
		break;
	case BL_MOB:
		clif_getareachar_mob(sd,(struct mob_data*)bl);
		break;
	case BL_PET:
		clif_getareachar_pet(sd,(struct pet_data*)bl);
		break;
	case BL_ITEM:
		clif_getareachar_item(sd,(struct flooritem_data*)bl);
		break;
	case BL_SKILL:
		clif_getareachar_skillunit(sd,(struct skill_unit *)bl);
		break;
	case BL_HOM:
		clif_getareachar_hom(sd,(struct homun_data*)bl);
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

	md=va_arg(ap,struct mob_data*);
	if(bl->type==BL_PC && (sd = (struct map_session_data *)bl)){
		clif_getareachar_mob(sd,md);
	}

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
	nullpo_retr(0, md=va_arg(ap,struct mob_data*));

	if(bl->type==BL_PC && (sd = (struct map_session_data*) bl)){
		clif_clearchar_id(md->bl.id,0,sd->fd);
	}

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

	pd=va_arg(ap,struct pet_data*);
	if(bl->type==BL_PC && (sd = (struct map_session_data *)bl)){
		clif_getareachar_pet(sd,pd);
	}

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
	nullpo_retr(0, pd=va_arg(ap,struct pet_data*));

	if(bl->type==BL_PC && (sd = (struct map_session_data*) bl)){
		clif_clearchar_id(pd->bl.id,0,sd->fd);
	}

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

	hd=va_arg(ap,struct homun_data*);
	if(bl->type==BL_PC && (sd = (struct map_session_data *)bl)){
		clif_getareachar_hom(sd,hd);
	}
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
	nullpo_retr(0, hd=va_arg(ap,struct homun_data*));

	if(bl->type==BL_PC && (sd = (struct map_session_data*) bl)){
		clif_clearchar_id(hd->bl.id,0,sd->fd);
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_skillinfo(struct map_session_data *sd, int skillid, int type, int range)
{
	int fd,id=0,skill_lv;
	int tk_ranker_bonus = 0;

	nullpo_retv(sd);

	if( skillid!=sd->cloneskill_id && (id=sd->status.skill[skillid].id) <= 0 )
		return;

	if(sd->status.class==PC_CLASS_TK && pc_checkskill2(sd,TK_MISSION)>0 && sd->status.base_level>=90 &&
			sd->status.skill_point==0 && ranking_get_pc_rank(sd,RK_TAEKWON)>0)
		tk_ranker_bonus=1;

	if(tk_ranker_bonus && sd->status.skill[skillid].flag == 0)
		skill_lv = skill_get_max(id);
	else if(skillid==sd->cloneskill_id){
		id = skillid;
		skill_lv = sd->status.skill[skillid].lv>sd->cloneskill_lv?sd->status.skill[skillid].lv:sd->cloneskill_lv;
	}else
		skill_lv = sd->status.skill[skillid].lv;

	fd=sd->fd;
	WFIFOW(fd,0)=0x147;
	WFIFOW(fd,2) = id;
	if(type < 0)
		WFIFOW(fd,4) = skill_get_inf(id);
	else
		WFIFOW(fd,4) = type;
	WFIFOW(fd,6) = 0;
	WFIFOW(fd,8) = skill_lv;
	WFIFOW(fd,10) = skill_get_sp(id,skill_lv);
	if(range < 0) {
		range = skill_get_range(id,skill_lv);
		if(range < 0)
			range = status_get_range(&sd->bl) - (range + 1);
		WFIFOW(fd,12)= range;
	}
	else
		WFIFOW(fd,12)= range;
	memset(WFIFOP(fd,14),0,24);
	if(!(skill_get_inf2(id)&0x01) || battle_config.quest_skill_learn == 1 || (battle_config.gm_allskill > 0 && pc_isGM(sd) >= battle_config.gm_allskill) )
		WFIFOB(fd,38)= (skill_lv < skill_get_max(id) && skillid!=sd->cloneskill_id && sd->status.skill[skillid].flag ==0 )? 1:0;
	else
		WFIFOB(fd,38) = 0;
	WFIFOSET(fd,packet_db[0x147].len);

	return;
}

/*==========================================
 * スキルリストを送信する
 * 16KB超過に備えてWFIFORESERVEする
 *------------------------------------------
 */
void clif_skillinfoblock(struct map_session_data *sd)
{
	unsigned char buf[4+37*MAX_SKILL];
	int fd;
	int i,len=4,id,range,skill_lv,tk_ranker_bonus=0;

	nullpo_retv(sd);

	if(sd->status.class==PC_CLASS_TK && pc_checkskill2(sd,TK_MISSION)>0 && sd->status.base_level>=90 &&
			sd->status.skill_point==0 && ranking_get_pc_rank(sd,RK_TAEKWON)>0)
		tk_ranker_bonus=1;

	fd=sd->fd;
	WBUFW(buf,0)=0x10f;
	for (i=0; i < MAX_SKILL; i++){
		if( (i==sd->cloneskill_id && (id=sd->cloneskill_id)!=0) || (id=sd->status.skill[i].id)!=0 ){
			WBUFW(buf,len  ) = id;
			WBUFW(buf,len+2) = skill_get_inf(id);
			WBUFW(buf,len+4) = 0;
			if(tk_ranker_bonus && sd->status.skill[i].flag==0)
				skill_lv = skill_get_max(id);
			else if(i==sd->cloneskill_id)
				skill_lv = sd->status.skill[i].lv>sd->cloneskill_lv?sd->status.skill[i].lv:sd->cloneskill_lv;
			else
				skill_lv = sd->status.skill[i].lv;
			WBUFW(buf,len+6) = skill_lv;
			WBUFW(buf,len+8) = skill_get_sp(id,skill_lv);
			range = skill_get_range(id,skill_lv);
			if(range < 0)
				range = status_get_range(&sd->bl) - (range + 1);
			WBUFW(buf,len+10)= range;
			memset(WBUFP(buf,len+12),0,24);
			if(!(skill_get_inf2(id)&0x01) || battle_config.quest_skill_learn == 1 || (battle_config.gm_allskill > 0 && pc_isGM(sd) >= battle_config.gm_allskill) )
				WBUFB(buf,len+36)= (skill_lv < skill_get_max(id) && i!=sd->cloneskill_id && sd->status.skill[i].flag ==0 )? 1:0;
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
 * スキル割り振り通知
 *------------------------------------------
 */
void clif_skillup(struct map_session_data *sd, int skill_num)
{
	int range,fd;

	nullpo_retv(sd);

	if(skill_num>8000)
		skill_num = skill_num-7100;
	fd=sd->fd;
	WFIFOW(fd,0) = 0x10e;
	WFIFOW(fd,2) = skill_num;
	WFIFOW(fd,4) = sd->status.skill[skill_num].lv;
	WFIFOW(fd,6) = skill_get_sp(skill_num,sd->status.skill[skill_num].lv);
	range = skill_get_range(skill_num,sd->status.skill[skill_num].lv);
	if(range < 0)
		range = status_get_range(&sd->bl) - (range + 1);
	WFIFOW(fd,8) = range;
	WFIFOB(fd,10) = (sd->status.skill[skill_num].lv < skill_get_max(sd->status.skill[skill_num].id)) ? 1 : 0;
	WFIFOSET(fd,packet_db[0x10e].len);

	return;
}

/*==========================================
 * スキル詠唱エフェクトを送信する
 *------------------------------------------
 */
void clif_skillcasting(struct block_list* bl,
	int src_id,int dst_id,int dst_x,int dst_y,int skill_num,int casttime)
{
	unsigned char buf[32];

	WBUFW(buf,0) = 0x13e;
	WBUFL(buf,2) = src_id;
	WBUFL(buf,6) = dst_id;
	WBUFW(buf,10) = dst_x;
	WBUFW(buf,12) = dst_y;
	WBUFW(buf,14) = skill_num;//魔法詠唱スキル
	WBUFL(buf,16) = skill_get_pl(skill_num);//属性
	WBUFL(buf,20) = casttime;//skill詠唱時間
	clif_send(buf,packet_db[0x13e].len, bl, AREA);

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
 * スキル詠唱失敗
 *------------------------------------------
 */
void clif_skill_fail(struct map_session_data *sd, int skill_id, unsigned char type, unsigned short btype)
{
	int fd;

	nullpo_retv(sd);

	if(type==0x4 && battle_config.display_delay_skill_fail==0){
		return;
	}

	fd=sd->fd;

	WFIFOW(fd,0) = 0x110;
	WFIFOW(fd,2) = skill_id;
	WFIFOW(fd,4) = btype;
	WFIFOW(fd,6) = 0;
	WFIFOB(fd,8) = 0;
	WFIFOB(fd,9) = type;
	WFIFOSET(fd,packet_db[0x110].len);

	return;
}

/*==========================================
 * スキル攻撃エフェクト＆ダメージ
 *------------------------------------------
 */
void clif_skill_damage(struct block_list *src,struct block_list *dst,
	unsigned int tick,int sdelay,int ddelay,int damage,int div,int skill_id,int skill_lv,int type)
{
	unsigned char buf[64];
	struct status_change *sc_data;

	nullpo_retv(src);
	nullpo_retv(dst);

	sc_data = status_get_sc_data(dst);

	if(type != 5 && dst->type == BL_PC && ((struct map_session_data *)dst)->special_state.infinite_endure)
		type = 9;
	if(sc_data) {
		if(type != 5 && (sc_data[SC_ENDURE].timer != -1 || sc_data[SC_BERSERK].timer != -1))
			type = 9;
		if(sc_data[SC_HALLUCINATION].timer != -1 && damage > 0)
			damage = damage*(5+sc_data[SC_HALLUCINATION].val1) + rand()%100;
	}

#if PACKETVER < 3
	WBUFW(buf,0)=0x114;
	WBUFW(buf,2)=skill_id;
	WBUFL(buf,4)=src->id;
	WBUFL(buf,8)=dst->id;
	WBUFL(buf,12)=tick;
	WBUFL(buf,16)=sdelay;
	WBUFL(buf,20)=ddelay;
	WBUFW(buf,24)=damage;
	WBUFW(buf,26)=skill_lv;
	WBUFW(buf,28)=div;
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
	WBUFL(buf,24)=damage;
	WBUFW(buf,28)=skill_lv;
	WBUFW(buf,30)=div;
	WBUFB(buf,32)=(type>0)?type:skill_get_hit(skill_id);
	clif_send(buf,packet_db[0x1de].len,src,AREA);
#endif

	return;
}

/*==========================================
 * 吹き飛ばしスキル攻撃エフェクト＆ダメージ
 *------------------------------------------
 */
/*int clif_skill_damage2(struct block_list *src,struct block_list *dst,
	unsigned int tick,int sdelay,int ddelay,int damage,int div,int skill_id,int skill_lv,int type)
{
	unsigned char buf[64];
	struct status_change *sc_data;

	nullpo_retr(0, src);
	nullpo_retr(0, dst);

	sc_data = status_get_sc_data(dst);

	if(type != 5 && dst->type == BL_PC && ((struct map_session_data *)dst)->special_state.infinite_endure)
		type = 9;
	if(sc_data) {
		if(type != 5 && (sc_data[SC_ENDURE].timer != -1 || sc_data[SC_BERSERK].timer != -1))
			type = 9;
		if(sc_data[SC_HALLUCINATION].timer != -1 && damage > 0)
			damage = damage*(5+sc_data[SC_HALLUCINATION].val1) + rand()%100;
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

	return 0;
}*/

/*==========================================
 * 支援/回復スキルエフェクト
 *------------------------------------------
 */
void clif_skill_nodamage(struct block_list *src,struct block_list *dst,
	int skill_id,int heal,int fail)
{
	unsigned char buf[32];

	nullpo_retv(src);
	nullpo_retv(dst);

	if(heal>0x7fff && skill_id != (NPC_SELFDESTRUCTION || NPC_SELFDESTRUCTION2))
		heal=0x7fff;

	WBUFW(buf,0)=0x11a;
	WBUFW(buf,2)=skill_id;
	WBUFW(buf,4)=heal;
	WBUFL(buf,6)=dst->id;
	WBUFL(buf,10)=src->id;
	WBUFB(buf,14)=fail;
	clif_send(buf,packet_db[0x11a].len,src,AREA);

	return;
}

/*==========================================
 * 場所スキルエフェクト
 *------------------------------------------
 */
void clif_skill_poseffect(struct block_list *src,int skill_id,int val,int x,int y,int tick)
{
	unsigned char buf[32];

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
 * 場所スキルエフェクト表示
 *------------------------------------------
 */
void clif_skill_setunit(struct skill_unit *unit)
{
	unsigned char buf[128];

	nullpo_retv(unit);

#if PACKETVER >= 3
	if(unit->group->unit_id == 0xb0) {	//グラフィティ
		memset(WBUFP(buf, 0),0,packet_db[0x1c9].len);
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

		return;
	}
#endif
	memset(WBUFP(buf, 0),0,packet_db[0x11f].len);
	WBUFW(buf, 0)=0x11f;
	WBUFL(buf, 2)=unit->bl.id;
	WBUFL(buf, 6)=unit->group->src_id;
	WBUFW(buf,10)=unit->bl.x;
	WBUFW(buf,12)=unit->bl.y;
	//旧GS_GROUNDDRIFT?
	if(unit->group->skill_id!=GS_GROUNDDRIFT)
	{
		WBUFB(buf,14)=unit->group->unit_id;
	}else{
		WBUFB(buf,14)=grounddrift_unit_id[unit->group->val1-13203];
	}
	WBUFB(buf,15)=0;
	clif_send(buf,packet_db[0x11f].len,&unit->bl,AREA);

	return;
}

/*==========================================
 * 場所スキルエフェクト削除
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
 * ワープ場所選択
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
	memcpy(WFIFOP(fd, 4),map1,16);
	memcpy(WFIFOP(fd,20),map2,16);
	memcpy(WFIFOP(fd,36),map3,16);
	memcpy(WFIFOP(fd,52),map4,16);
	WFIFOSET(fd,packet_db[0x11c].len);

	return;
}

/*==========================================
 * メモ応答
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
 * モンスター情報
 *------------------------------------------
 */
void clif_skill_estimation(struct map_session_data *sd, struct block_list *dst)
{
	unsigned char buf[32];
	int i;

	nullpo_retv(sd);
	nullpo_retv(dst);

	if(dst->type==BL_MOB) {
		struct mob_data *md = (struct mob_data *)dst;
		if(md == NULL)
			return;

		WBUFW(buf, 0)=0x18c;
		WBUFW(buf, 2)=mob_get_viewclass(md->class);
		WBUFW(buf, 4)=mob_db[md->class].lv;
		WBUFW(buf, 6)=mob_db[md->class].size;
		WBUFL(buf, 8)=md->hp;
		WBUFW(buf,12)=status_get_def2(&md->bl);
		WBUFW(buf,14)=mob_db[md->class].race;
		WBUFW(buf,16)=status_get_mdef2(&md->bl) - (mob_db[md->class].vit>>1);
		WBUFW(buf,18)=status_get_elem_type(&md->bl);
		for(i=0;i<9;i++)
			WBUFB(buf,20+i)= battle_attr_fix(100,i+1,md->def_ele);

		if(sd->status.party_id>0)
			clif_send(buf,packet_db[0x18c].len,&sd->bl,PARTY_AREA);
		else{
			memcpy(WFIFOP(sd->fd,0),buf,packet_db[0x18c].len);
			WFIFOSET(sd->fd,packet_db[0x18c].len);
		}
	}

	return;
}

/*==========================================
 * アイテム合成可能リスト
 *------------------------------------------
 */
void clif_skill_produce_mix_list(struct map_session_data *sd, int trigger)
{
	int i,c,view,fd;

	nullpo_retv( sd);

	fd=sd->fd;
	WFIFOW(fd, 0)=0x18d;

	for(i=0,c=0;i<MAX_SKILL_PRODUCE_DB;i++){
		if( skill_can_produce_mix(sd,skill_produce_db[i].nameid,trigger) ){
			if((view = itemdb_viewid(skill_produce_db[i].nameid)) > 0)
				WFIFOW(fd,c*8+ 4)= view;
			else
				WFIFOW(fd,c*8+ 4)= skill_produce_db[i].nameid;
			WFIFOW(fd,c*8+ 6)= 0x0012;
			WFIFOL(fd,c*8+ 8)= sd->status.char_id;
			c++;
		}
	}
	WFIFOW(fd, 2)=c*8+8;
	WFIFOSET(fd,WFIFOW(fd,2));
	if(c > 0) sd->state.produce_flag = 1;

	return;
}

/*==========================================
 * 状態異常アイコン/メッセージ表示
 *------------------------------------------
 */
void clif_status_change(struct block_list *bl, int type, unsigned char flag)
{
	unsigned char buf[16];

	nullpo_retv(bl);

	WBUFW(buf,0)=0x0196;
	WBUFW(buf,2)=type;
	WBUFL(buf,4)=bl->id;
	WBUFB(buf,8)=flag;
	clif_send(buf,packet_db[0x196].len,bl,AREA);

	return;
}

/*==========================================
 * メッセージ表示
 *------------------------------------------
 */
void clif_displaymessage(const int fd, char* mes)
{
	WFIFOW(fd,0) = 0x8e;
	WFIFOW(fd,2) = 4+1+strlen(mes);
	strncpy(WFIFOP(fd,4), mes, WFIFOW(fd,2)-4);
	WFIFOSET(fd, WFIFOW(fd,2));

	return;
}

/*==========================================
 * 天の声を送信する
 *------------------------------------------
 */
void clif_GMmessage(struct block_list *bl, char* mes, int len, int flag)
{
	unsigned char *buf = malloc(len+16);
	int lp=(flag&0x10)?8:4;

	WBUFW(buf,0) = 0x9a;
	WBUFW(buf,2) = len+lp;
	WBUFL(buf,4) = 0x65756c62;
	memcpy(WBUFP(buf,lp), mes, len);
	flag&=0x07;
	clif_send(buf, WBUFW(buf,2), bl,
		(flag==1)? ALL_SAMEMAP:
		(flag==2)? AREA:
		(flag==3)? SELF:
		ALL_CLIENT);
	free(buf);

	return;
}

/*==========================================
 * グローバルメッセージ
 *------------------------------------------
 */
void clif_GlobalMessage(struct block_list *bl,char *message)
{
	char buf[100];
	int len;

	nullpo_retv(bl);

	if(message == NULL)
		return;

	len=strlen(message)+1;

	WBUFW(buf,0)=0x8d;
	WBUFW(buf,2)=len+8;
	WBUFL(buf,4)=bl->id;
	strncpy(WBUFP(buf,8),message,len);
	clif_send(buf,WBUFW(buf,2),bl,AREA_CHAT_WOC);

	return;
}

/*==========================================
 * 天の声（マルチカラー）を送信
 *------------------------------------------
 */
void clif_announce(struct block_list *bl, char* mes, int len, unsigned long color, int flag)
{
	unsigned char *buf = malloc(len+16);

	WBUFW(buf,0) = 0x1c3;
	WBUFW(buf,2) = len+16;
	WBUFL(buf,4) = color;
	WBUFW(buf,8) = 0x190; //Font style? Type?
	WBUFW(buf,10) = 0x0c;  //12? Font size?
	WBUFL(buf,12) = 0;	//Unknown!
	memcpy(WBUFP(buf,16), mes, len);

	flag &= 0x07;
	clif_send(buf, WBUFW(buf,2), bl,
	          (flag == 1) ? ALL_SAMEMAP:
	          (flag == 2) ? AREA:
	          (flag == 3) ? SELF:
	          ALL_CLIENT);
	free(buf);

	return;
}

/*==========================================
 * HPSP回復エフェクトを送信する
 *------------------------------------------
 */
void clif_heal(int fd, int type, int val)
{
	WFIFOW(fd,0)=0x13d;
	WFIFOW(fd,2)=type;
	WFIFOW(fd,4)=val;
	WFIFOSET(fd,packet_db[0x13d].len);

	return;
}

/*==========================================
 * 復活する
 *------------------------------------------
 */
void clif_resurrection(struct block_list *bl, unsigned short type)
{
	unsigned char buf[16];

	nullpo_retv(bl);

	WBUFW(buf,0)=0x148;
	WBUFL(buf,2)=bl->id;
	WBUFW(buf,6)=type;
	clif_send(buf,packet_db[0x148].len,bl,type==1 ? AREA : AREA_WOS);

	return;
}

/*==========================================
 * PVP実装？（仮）
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
 * PVP実装？(仮)
 *------------------------------------------
 */
void clif_pvpset(struct map_session_data *sd, int pvprank, int pvpnum, char type)
{
	nullpo_retv(sd);

	if(type == 2) {
		WFIFOW(sd->fd,0) = 0x19a;
		WFIFOL(sd->fd,2) = sd->bl.id;
		WFIFOL(sd->fd,6) = pvprank;
		WFIFOL(sd->fd,10) = pvpnum;
		WFIFOSET(sd->fd,packet_db[0x19a].len);
	}
	else {
		char buf[16];

		WBUFW(buf,0) = 0x19a;
		WBUFL(buf,2) = sd->bl.id;
		if(sd->status.option&0x46)
			WBUFL(buf,6) = -1;
		else
			WBUFL(buf,6) = pvprank;
		WBUFL(buf,10) = pvpnum;
		if(!type)
			clif_send(buf,packet_db[0x19a].len,&sd->bl,SELF);
		else
			clif_send(buf,packet_db[0x19a].len,&sd->bl,ALL_SAMEMAP);
	}

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_send0199(int map, unsigned short type)
{
	struct block_list bl;
	char buf[8];

	bl.m = map;
	WBUFW(buf,0)=0x199;
	WBUFW(buf,2)=type;
	clif_send(buf,packet_db[0x199].len,&bl,ALL_SAMEMAP);

	return;
}

/*==========================================
 * 精錬エフェクトを送信する
 *------------------------------------------
 */
void clif_refine(int fd, struct map_session_data *sd, unsigned short fail, int idx, int val)
{
	WFIFOW(fd,0)=0x188;
	WFIFOW(fd,2)=fail;
	WFIFOW(fd,4)=idx+2;
	WFIFOW(fd,6)=val;
	WFIFOSET(fd,packet_db[0x188].len);

	return;
}

/*==========================================
 * Wisを送信する
 *------------------------------------------
 */
void clif_wis_message(int fd,char *nick,char *mes, int mes_len)
{
	WFIFOW(fd,0)=0x97;
	WFIFOW(fd,2)=mes_len +24+ 4;
	memcpy(WFIFOP(fd,4),nick,24);
	memcpy(WFIFOP(fd,28),mes,mes_len);
	WFIFOSET(fd,WFIFOW(fd,2));

	return;
}

/*==========================================
 * Wisの送信結果を送信する
 *------------------------------------------
 */
void clif_wis_end(int fd, unsigned short flag)
{
	WFIFOW(fd,0)=0x98;
	WFIFOW(fd,2)=flag;
	WFIFOSET(fd,packet_db[0x98].len);

	return;
}

/*==========================================
 * キャラID名前引き結果を送信する
 *------------------------------------------
 */
void clif_solved_charname(struct map_session_data *sd, int char_id)
{
	char *p;
	int fd;

	nullpo_retv(sd);

	p= map_charid2nick(char_id);
	if(p!=NULL){
		fd=sd->fd;
		WFIFOW(fd,0)=0x194;
		WFIFOL(fd,2)=char_id;
		memcpy(WFIFOP(fd,6), p,24 );
		WFIFOSET(fd,packet_db[0x194].len);
	}else{
		map_reqchariddb(sd,char_id);
		chrif_searchcharid(char_id);
	}

	return;
}

/*==========================================
 * カードの挿入可能リストを返す
 *------------------------------------------
 */
static void clif_use_card(struct map_session_data *sd, int idx)
{
	nullpo_retv(sd);

	if (idx < 0 || idx >= MAX_INVENTORY)
		return;

	if(sd->inventory_data[idx]) {
		int i, j, c;
		int ep=sd->inventory_data[idx]->equip;
		int fd=sd->fd;

		WFIFOW(fd,0)=0x017b;

		c = 0;
		for(i = 0; i < MAX_INVENTORY; i++) {
			if(sd->inventory_data[i] == NULL)
				continue;
			if(sd->inventory_data[i]->type!=4 && sd->inventory_data[i]->type!=5)	// 武器防具じゃない
				continue;
			if(sd->status.inventory[i].card[0]==0x00ff)	// 製造武器
				continue;
			if(sd->status.inventory[i].card[0]==(short)0xff00 || sd->status.inventory[i].card[0]==0x00fe)
				continue;
			if(sd->status.inventory[i].identify==0 )	// 未鑑定
				continue;

			if((sd->inventory_data[i]->equip&ep)==0)	// 装備個所が違う
				continue;
			if(sd->inventory_data[i]->type==4 && ep==32)	// 盾カードと両手武器
				continue;

			for(j=0;j<sd->inventory_data[i]->slot;j++){
				if (sd->status.inventory[i].card[j] == 0) {
					WFIFOW(fd,4+c*2) = i + 2;
					c++;
					break;
				}
			}
		}
		WFIFOW(fd,2)=4+c*2;
		WFIFOSET(fd,WFIFOW(fd,2));
	}

	return;
}

/*==========================================
 * カードの挿入終了
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
 * 鑑定可能アイテムリスト送信
 *------------------------------------------
 */
void clif_item_identify_list(struct map_session_data *sd)
{
	int i,c;
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;

	WFIFOW(fd,0)=0x177;
	for(i=c=0;i<MAX_INVENTORY;i++){
		if(sd->status.inventory[i].nameid > 0 && sd->status.inventory[i].identify!=1){
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
 * 鑑定結果
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
 * 養子要請ダイアログ表示
 *------------------------------------------
 */
static void clif_baby_req_display(struct map_session_data *dst_sd, struct map_session_data *src_sd, int p_id)
{
	int fd;

	nullpo_retv(dst_sd);

	fd=dst_sd->fd;
	WFIFOW(fd,0) = 0x01f6;
	WFIFOL(fd,2) = src_sd->status.account_id;
	WFIFOL(fd,6) = p_id;
	memcpy(WFIFOP(fd,10), src_sd->status.name, 24);
	WFIFOSET(fd,packet_db[0x1f6].len);

	return;
}

/*==========================================
 * 養子チェック失敗
 *------------------------------------------
 */
void clif_baby_req_fail(struct map_session_data *sd, int type)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0) = 0x0216;
	WFIFOL(fd,2) = type;
	WFIFOSET(fd,packet_db[0x216].len);

	return;
}

/*==========================================
 * 養子ターゲット表示
 *------------------------------------------
 */
// 0x1f8は使われてない方式？
/*void clif_baby_target_display(struct map_session_data *sd)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0) = 0x01f8;
	WFIFOSET(sd->fd,packet_db[0x1f8].len);

	return;
}*/

/*==========================================
 * 修理可能アイテムリスト送信
 *------------------------------------------
 */
void clif_item_repair_list(struct map_session_data *sd, struct map_session_data *dstsd)
{
	int i,c;
	int fd;
	int nameid;

	nullpo_retv(sd);
	nullpo_retv(dstsd);

	fd=sd->fd;

	WFIFOW(fd,0)=0x1fc;
	for(i=c=0;i<MAX_INVENTORY;i++){
		if((nameid=dstsd->status.inventory[i].nameid) > 0 && dstsd->status.inventory[i].attribute!=0){// && skill_can_repair(sd,nameid)){
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
		sd->state.produce_flag = 1;
		sd->repair_target=dstsd->bl.id;
	}else
		clif_skill_fail(sd,sd->ud.skillid,0,0);

	return;
}

void clif_item_repaireffect(struct map_session_data *sd, unsigned char flag, int nameid)
{
	int view,fd;

	nullpo_retv(sd);

	fd=sd->fd;

	WFIFOW(fd, 0)=0x1fe;
	if((view = itemdb_viewid(nameid)) > 0)
		WFIFOW(fd, 2)=view;
	else
		WFIFOW(fd, 2)=nameid;
	WFIFOB(fd, 4)=flag;
	WFIFOSET(fd,packet_db[0x1fe].len);

	if(sd->repair_target && sd->bl.id != sd->repair_target && flag==0) {	// 成功したら相手にも通知
		struct map_session_data *dstsd = map_id2sd(sd->repair_target);
		if(dstsd)
			clif_item_repaireffect(dstsd,flag,nameid);
		sd->repair_target=0;
	}

	return;
}

/*==========================================
 * 武器精錬可能アイテムリスト送信
 *------------------------------------------
 */
void clif_weapon_refine_list(struct map_session_data *sd)
{
	int i,c;
	int fd;
	int skilllv;

	nullpo_retv(sd);

	skilllv = pc_checkskill(sd,WS_WEAPONREFINE);

	fd=sd->fd;

	WFIFOW(fd,0)=0x221;
	for(i=c=0;i<MAX_INVENTORY;i++){
		if(sd->status.inventory[i].nameid > 0 && sd->status.inventory[i].identify==1 &&
			itemdb_wlv(sd->status.inventory[i].nameid) >=1 && !(sd->status.inventory[i].equip&0x0022)){
			WFIFOW(fd,c*13+ 4)=i+2;
			WFIFOW(fd,c*13+ 6)=sd->status.inventory[i].nameid;
			WFIFOW(fd,c*13+ 8)=0;
			WFIFOW(fd,c*13+10)=0;
			WFIFOB(fd,c*13+12)=c;
			c++;
		}
	}
	WFIFOW(fd,2)=c*13+4;
	WFIFOSET(fd,WFIFOW(fd,2));

	return;
}

void clif_weapon_refine_res(struct map_session_data *sd, int flag, int nameid)
{
	int view,fd;

	nullpo_retv(sd);

	fd=sd->fd;

	WFIFOW(fd, 0)=0x223;
	WFIFOL(fd, 2)=flag;
	WFIFOW(fd, 4)=0;
	if((view = itemdb_viewid(nameid)) > 0)
		WFIFOW(fd, 6)=view;
	else
		WFIFOW(fd, 6)=nameid;
	WFIFOSET(fd,packet_db[0x223].len);

	return;
}

/*==========================================
 * アイテムによる一時的なスキル効果
 *------------------------------------------
 */
void clif_item_skill(struct map_session_data *sd, int skillid, int skilllv, const char *name)
{
	int range,fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd, 0)=0x147;
	WFIFOW(fd, 2)=skillid;
	if(skillid == MO_EXTREMITYFIST || skillid == TK_JUMPKICK)
		WFIFOW(fd, 4)=1;
	else
		WFIFOW(fd, 4)=skill_get_inf(skillid);
	WFIFOW(fd, 6)=0;
	WFIFOW(fd, 8)=skilllv;
	WFIFOW(fd,10)=skill_get_sp(skillid,skilllv);
	range = skill_get_range(skillid,skilllv);
	if(range < 0)
		range = status_get_range(&sd->bl) - (range + 1);
	WFIFOW(fd,12)=range;
	memcpy(WFIFOP(fd,14),name,24);
	WFIFOB(fd,38)=0;
	WFIFOSET(fd,packet_db[0x147].len);

	return;
}

/*==========================================
 * カートにアイテム追加
 *------------------------------------------
 */
void clif_cart_additem(struct map_session_data *sd, int n, int amount)
{
	int view,j,fd;
	unsigned char *buf;

	nullpo_retv(sd);

	if (n < 0 || n >= MAX_CART || sd->status.cart[n].nameid <= 0)
		return;

	fd=sd->fd;
	buf=WFIFOP(fd,0);

	WBUFW(buf,0)=0x124;
	WBUFW(buf,2)=n+2;
	WBUFL(buf,4)=amount;
	if((view = itemdb_viewid(sd->status.cart[n].nameid)) > 0)
		WBUFW(buf,8)=view;
	else
		WBUFW(buf,8)=sd->status.cart[n].nameid;
	WBUFB(buf,10)=sd->status.cart[n].identify;
	WBUFB(buf,11)=sd->status.cart[n].attribute;
	WBUFB(buf,12)=sd->status.cart[n].refine;
	if(sd->status.cart[n].card[0]==0x00ff || sd->status.cart[n].card[0]==0x00fe || sd->status.cart[n].card[0]==(short)0xff00) {
		WBUFW(buf,13)=sd->status.cart[n].card[0];
		WBUFW(buf,15)=sd->status.cart[n].card[1];
		WBUFW(buf,17)=sd->status.cart[n].card[2];
		WBUFW(buf,19)=sd->status.cart[n].card[3];
	}
	else {
		if(sd->status.cart[n].card[0] > 0 && (j=itemdb_viewid(sd->status.cart[n].card[0])) > 0)
			WBUFW(buf,13)= j;
		else
			WBUFW(buf,13)= sd->status.cart[n].card[0];
		if(sd->status.cart[n].card[1] > 0 && (j=itemdb_viewid(sd->status.cart[n].card[1])) > 0)
			WBUFW(buf,15)= j;
		else
			WBUFW(buf,15)= sd->status.cart[n].card[1];
		if(sd->status.cart[n].card[2] > 0 && (j=itemdb_viewid(sd->status.cart[n].card[2])) > 0)
			WBUFW(buf,17)= j;
		else
			WBUFW(buf,17)= sd->status.cart[n].card[2];
		if(sd->status.cart[n].card[3] > 0 && (j=itemdb_viewid(sd->status.cart[n].card[3])) > 0)
			WBUFW(buf,19)= j;
		else
			WBUFW(buf,19)= sd->status.cart[n].card[3];
	}
	WFIFOSET(fd,packet_db[0x124].len);

	return;
}

/*==========================================
 * カートからアイテム削除
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
 * カートのアイテムリスト
 *------------------------------------------
 */
void clif_cart_itemlist(struct map_session_data *sd)
{
	struct item_data *id;
	int i,n,fd;
	unsigned char *buf;

	nullpo_retv(sd);

	fd=sd->fd;
	buf = WFIFOP(fd,0);

#if PACKETVER < 5
	WBUFW(buf,0)=0x123;
	for(i=0,n=0;i<MAX_CART;i++){
		if(sd->status.cart[i].nameid<=0)
			continue;
		id = itemdb_search(sd->status.cart[i].nameid);
		if(itemdb_isequip2(id))
			continue;
		WBUFW(buf,n*10+4)=i+2;
		if(id->view_id > 0)
			WBUFW(buf,n*10+6)=id->view_id;
		else
			WBUFW(buf,n*10+6)=sd->status.cart[i].nameid;
		WBUFB(buf,n*10+8)=id->type;
		WBUFB(buf,n*10+9)=sd->status.cart[i].identify;
		WBUFW(buf,n*10+10)=sd->status.cart[i].amount;
		WBUFW(buf,n*10+12)=0;
		n++;
	}
	if(n){
		WBUFW(buf,2)=4+n*10;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#else
	WBUFW(buf,0)=0x1ef;
	for(i=0,n=0;i<MAX_CART;i++){
		if(sd->status.cart[i].nameid<=0)
			continue;
		id = itemdb_search(sd->status.cart[i].nameid);
		if(itemdb_isequip2(id))
			continue;
		WBUFW(buf,n*18+4)=i+2;
		if(id->view_id > 0)
			WBUFW(buf,n*18+6)=id->view_id;
		else
			WBUFW(buf,n*18+6)=sd->status.cart[i].nameid;
		WBUFB(buf,n*18+8)=id->type;
		WBUFB(buf,n*18+9)=sd->status.cart[i].identify;
		WBUFW(buf,n*18+10)=sd->status.cart[i].amount;
		WBUFW(buf,n*18+12)=0;
		WBUFW(buf,n*18+14)=sd->status.cart[i].card[0];
		WBUFW(buf,n*18+16)=sd->status.cart[i].card[1];
		WBUFW(buf,n*18+18)=sd->status.cart[i].card[2];
		WBUFW(buf,n*18+20)=sd->status.cart[i].card[3];
		n++;
	}
	if(n){
		WBUFW(buf,2)=4+n*18;
		WFIFOSET(fd,WFIFOW(fd,2));
	}
#endif

	return;
}

/*==========================================
 * カートの装備品リスト
 *------------------------------------------
 */
void clif_cart_equiplist(struct map_session_data *sd)
{
	struct item_data *id;
	int i,j,n,fd;
	unsigned char *buf;

	nullpo_retv(sd);

	fd=sd->fd;
	buf = WFIFOP(fd,0);

	WBUFW(buf,0)=0x122;
	for(i=0,n=0;i<MAX_CART;i++){
		if(sd->status.cart[i].nameid<=0)
			continue;
		id = itemdb_search(sd->status.cart[i].nameid);
		if(!itemdb_isequip2(id))
			continue;
		WBUFW(buf,n*20+4)=i+2;
		if(id->view_id > 0)
			WBUFW(buf,n*20+6)=id->view_id;
		else
			WBUFW(buf,n*20+6)=sd->status.cart[i].nameid;
		WBUFB(buf,n*20+8)=id->type;
		WBUFB(buf,n*20+9)=sd->status.cart[i].identify;
		WBUFW(buf,n*20+10)=id->equip;
		WBUFW(buf,n*20+12)=sd->status.cart[i].equip;
		WBUFB(buf,n*20+14)=sd->status.cart[i].attribute;
		WBUFB(buf,n*20+15)=sd->status.cart[i].refine;
		if(sd->status.cart[i].card[0]==0x00ff || sd->status.cart[i].card[0]==0x00fe || sd->status.cart[i].card[0]==(short)0xff00) {
			WBUFW(buf,n*20+16)=sd->status.cart[i].card[0];
			WBUFW(buf,n*20+18)=sd->status.cart[i].card[1];
			WBUFW(buf,n*20+20)=sd->status.cart[i].card[2];
			WBUFW(buf,n*20+22)=sd->status.cart[i].card[3];
		}
		else {
			if(sd->status.cart[i].card[0] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[0])) > 0)
				WBUFW(buf,n*20+16)= j;
			else
				WBUFW(buf,n*20+16)= sd->status.cart[i].card[0];
			if(sd->status.cart[i].card[1] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[1])) > 0)
				WBUFW(buf,n*20+18)= j;
			else
				WBUFW(buf,n*20+18)= sd->status.cart[i].card[1];
			if(sd->status.cart[i].card[2] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[2])) > 0)
				WBUFW(buf,n*20+20)= j;
			else
				WBUFW(buf,n*20+20)= sd->status.cart[i].card[2];
			if(sd->status.cart[i].card[3] > 0 && (j=itemdb_viewid(sd->status.cart[i].card[3])) > 0)
				WBUFW(buf,n*20+22)= j;
			else
				WBUFW(buf,n*20+22)= sd->status.cart[i].card[3];
		}
		n++;
	}
	if(n){
		WBUFW(buf,2)=4+n*20;
		WFIFOSET(fd,WFIFOW(fd,2));
	}

	return;
}

/*==========================================
 * 露店開設
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
 * 露店看板表示
 *------------------------------------------
 */
void clif_showvendingboard(struct block_list* bl, const char *shop_title, int fd)
{
	unsigned char buf[128];

	nullpo_retv(bl);

	WBUFW(buf,0)=0x131;
	WBUFL(buf,2)=bl->id;
	strncpy(WBUFP(buf,6), shop_title, 80);
	if(fd){
		memcpy(WFIFOP(fd,0),buf,packet_db[0x131].len);
		WFIFOSET(fd,packet_db[0x131].len);
	}else{
		clif_send(buf,packet_db[0x131].len,bl,AREA_WOS);
	}

	return;
}

/*==========================================
 * 露店看板消去
 *------------------------------------------
 */
void clif_closevendingboard(struct block_list* bl, int fd)
{
	unsigned char buf[8];

	nullpo_retv(bl);

	WBUFW(buf,0)=0x132;
	WBUFL(buf,2)=bl->id;
	if(fd){
		memcpy(WFIFOP(fd,0),buf,packet_db[0x132].len);
		WFIFOSET(fd,packet_db[0x132].len);
	}else{
		clif_send(buf,packet_db[0x132].len,bl,AREA_WOS);
	}

	return;
}

/*==========================================
 * 露店アイテムリスト
 *------------------------------------------
 */
void clif_vendinglist(struct map_session_data *sd, struct map_session_data *vsd)
{
	struct item_data *data;
	int i, j, n, idx, fd;
	struct vending *vending;
	unsigned char *buf;

	nullpo_retv(sd);
	nullpo_retv(vsd);
	nullpo_retv(vending = vsd->vending);

	fd=sd->fd;
	buf = WFIFOP(fd,0);
	WBUFW(buf,0)=0x133;
	WBUFL(buf,4)=vsd->status.account_id;
	n = 0;
	for(i = 0; i < vsd->vend_num; i++) {
		if(vending[i].amount<=0)
			continue;
		WBUFL(buf, 8+n*22)=vending[i].value;
		WBUFW(buf,12+n*22)=vending[i].amount;
		WBUFW(buf,14+n*22)=(idx = vending[i].index) + 2;
		if(vsd->status.cart[idx].nameid <= 0 || vsd->status.cart[idx].amount <= 0)
			continue;
		data = itemdb_search(vsd->status.cart[idx].nameid);
		WBUFB(buf,16+n*22)=data->type;
		if(data->view_id > 0)
			WBUFW(buf,17+n*22)=data->view_id;
		else
			WBUFW(buf,17+n*22)=vsd->status.cart[idx].nameid;
		WBUFB(buf,19+n*22)=vsd->status.cart[idx].identify;
		WBUFB(buf,20+n*22)=vsd->status.cart[idx].attribute;
		WBUFB(buf,21+n*22)=vsd->status.cart[idx].refine;
		if(vsd->status.cart[idx].card[0]==0x00ff || vsd->status.cart[idx].card[0]==0x00fe || vsd->status.cart[idx].card[0]==(short)0xff00) {
			WBUFW(buf,22+n*22)=(data->type==7)?0:vsd->status.cart[idx].card[0];
			WBUFW(buf,24+n*22)=(data->type==7)?0:vsd->status.cart[idx].card[1];
			WBUFW(buf,26+n*22)=(data->type==7)?0:vsd->status.cart[idx].card[2];
			WBUFW(buf,28+n*22)=vsd->status.cart[idx].card[3];
		}
		else {
			if(vsd->status.cart[idx].card[0] > 0 && (j=itemdb_viewid(vsd->status.cart[idx].card[0])) > 0)
				WBUFW(buf,22+n*22)= j;
			else
				WBUFW(buf,22+n*22)= vsd->status.cart[idx].card[0];
			if(vsd->status.cart[idx].card[1] > 0 && (j=itemdb_viewid(vsd->status.cart[idx].card[1])) > 0)
				WBUFW(buf,24+n*22)= j;
			else
				WBUFW(buf,24+n*22)= vsd->status.cart[idx].card[1];
			if(vsd->status.cart[idx].card[2] > 0 && (j=itemdb_viewid(vsd->status.cart[idx].card[2])) > 0)
				WBUFW(buf,26+n*22)= j;
			else
				WBUFW(buf,26+n*22)= vsd->status.cart[idx].card[2];
			if(vsd->status.cart[idx].card[3] > 0 && (j=itemdb_viewid(vsd->status.cart[idx].card[3])) > 0)
				WBUFW(buf,28+n*22)= j;
			else
				WBUFW(buf,28+n*22)= vsd->status.cart[idx].card[3];
		}
		n++;
	}
	if(n > 0){
		WBUFW(buf,2)=8+n*22;
		WFIFOSET(fd,WFIFOW(fd,2));
	}

	return;
}

/*==========================================
 * 露店アイテム購入失敗
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
 * 露店開設成功
 *------------------------------------------
*/
int clif_openvending(struct map_session_data *sd)
{
	struct item_data *data;
	int i, j, n, idx, fd;
	unsigned char *buf;
	struct vending *vending;

	nullpo_retr(0, sd);

	vending = sd->vending;

	fd=sd->fd;
	buf = WFIFOP(fd,0);

	WBUFW(buf,0)=0x136;
	WBUFL(buf,4)=sd->bl.id;
	n = 0;
	for(i = 0; i < sd->vend_num; i++) {
		WBUFL(buf, 8+n*22)=vending[i].value;
		WBUFW(buf,12+n*22)=(idx = vending[i].index) + 2;
		WBUFW(buf,14+n*22)=vending[i].amount;
		if(sd->status.cart[idx].nameid <= 0 || sd->status.cart[idx].amount <= 0)
			continue;
		data = itemdb_search(sd->status.cart[idx].nameid);
		WBUFB(buf,16+n*22)=data->type;
		if(data->view_id > 0)
			WBUFW(buf,17+n*22)=data->view_id;
		else
			WBUFW(buf,17+n*22)=sd->status.cart[idx].nameid;
		WBUFB(buf,19+n*22)=sd->status.cart[idx].identify;
		WBUFB(buf,20+n*22)=sd->status.cart[idx].attribute;
		WBUFB(buf,21+n*22)=sd->status.cart[idx].refine;
		if(sd->status.cart[idx].card[0]==0x00ff || sd->status.cart[idx].card[0]==0x00fe || sd->status.cart[idx].card[0]==(short)0xff00) {
			WBUFW(buf,22+n*22)=(data->type==7)?0:sd->status.cart[idx].card[0];
			WBUFW(buf,24+n*22)=(data->type==7)?0:sd->status.cart[idx].card[1];
			WBUFW(buf,26+n*22)=(data->type==7)?0:sd->status.cart[idx].card[2];
			WBUFW(buf,28+n*22)=sd->status.cart[idx].card[3];
		}
		else {
			if(sd->status.cart[idx].card[0] > 0 && (j=itemdb_viewid(sd->status.cart[idx].card[0])) > 0)
				WBUFW(buf,22+n*22)= j;
			else
				WBUFW(buf,22+n*22)= sd->status.cart[idx].card[0];
			if(sd->status.cart[idx].card[1] > 0 && (j=itemdb_viewid(sd->status.cart[idx].card[1])) > 0)
				WBUFW(buf,24+n*22)= j;
			else
				WBUFW(buf,24+n*22)= sd->status.cart[idx].card[1];
			if(sd->status.cart[idx].card[2] > 0 && (j=itemdb_viewid(sd->status.cart[idx].card[2])) > 0)
				WBUFW(buf,26+n*22)= j;
			else
				WBUFW(buf,26+n*22)= sd->status.cart[idx].card[2];
			if(sd->status.cart[idx].card[3] > 0 && (j=itemdb_viewid(sd->status.cart[idx].card[3])) > 0)
				WBUFW(buf,28+n*22)= j;
			else
				WBUFW(buf,28+n*22)= sd->status.cart[idx].card[3];
		}
		n++;
	}
	if(n > 0){
		WBUFW(buf,2)=8+n*22;
		WFIFOSET(fd,WFIFOW(fd,2));
	}

	return n;
}

/*==========================================
 * 露店アイテム販売報告
 *------------------------------------------
*/
void clif_vendingreport(struct map_session_data *sd, int idx, int amount)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x137;
	WFIFOW(fd,2)=idx+2;
	WFIFOW(fd,4)=amount;
	WFIFOSET(fd,packet_db[0x137].len);

	return;
}

/*==========================================
 * パーティ作成完了
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
 * パーティ情報送信
 *------------------------------------------
 */
void clif_party_info(struct party *p, int fd)
{
	unsigned char buf[28+MAX_PARTY*46];
	int i,c;
	struct map_session_data *sd=NULL;

	nullpo_retv(p);

	WBUFW(buf,0)=0xfb;
	memcpy(WBUFP(buf,4),p->name,24);
	for(i=c=0;i<MAX_PARTY;i++){
		struct party_member *m=&p->member[i];
		if(m->account_id>0){
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
	if(fd>=0){	// fdが設定されてるならそれに送る
		memcpy(WFIFOP(fd,0),buf,WBUFW(buf,2));
		WFIFOSET(fd,WFIFOW(fd,2));
		return;
	}
	if(sd!=NULL)
		clif_send(buf,WBUFW(buf,2),&sd->bl,PARTY);

	return;
}

/*==========================================
 * パーティ勧誘
 *------------------------------------------
 */
void clif_party_invite(struct map_session_data *sd, struct map_session_data *tsd)
{
	int fd;
	struct party *p;

	nullpo_retv(sd);
	nullpo_retv(tsd);

	fd=tsd->fd;

	if( (p=party_search(sd->status.party_id))==NULL )
		return;

	WFIFOW(fd,0)=0xfe;
	WFIFOL(fd,2)=sd->status.account_id;
	memcpy(WFIFOP(fd,6),p->name,24);
	WFIFOSET(fd,packet_db[0xfe].len);

	return;
}

/*==========================================
 * パーティ勧誘結果
 *------------------------------------------
 */
void clif_party_inviteack(struct map_session_data *sd, char *nick, unsigned char flag)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd, 0)=0xfd;
	memcpy(WFIFOP(fd,2),nick,24);
	WFIFOB(fd,26)=flag; // 0: the player is already in other party, 1: invitation was denied, 2: success to invite
	WFIFOSET(fd,packet_db[0xfd].len);

	return;
}

/*==========================================
 * パーティ設定送信
 * flag & 0x001=exp変更ミス
 *        0x010=item変更ミス
 *        0x100=一人にのみ送信
 *------------------------------------------
 */
void clif_party_option(struct party *p, struct map_session_data *sd, int flag)
{
	unsigned char buf[8];

	nullpo_retv(p);

//	if(battle_config.etc_log)
//		printf("clif_party_option: %d %d %d\n",p->exp,p->item,flag);
	if(sd==NULL && flag==0){
		int i;
		for(i=0;i<MAX_PARTY;i++)
			if((sd=map_id2sd(p->member[i].account_id))!=NULL)
				break;
	}
	if(sd==NULL)
		return;
	WBUFW(buf,0)=0x101;
	WBUFW(buf,2)=((flag&0x01)?2:p->exp);
	WBUFW(buf,4)=((flag&0x10)?2:p->item);
	if(flag==0)
		clif_send(buf,packet_db[0x101].len,&sd->bl,PARTY);
	else{
		memcpy(WFIFOP(sd->fd,0),buf,packet_db[0x101].len);
		WFIFOSET(sd->fd,packet_db[0x101].len);
	}

	return;
}

/*==========================================
 * パーティ脱退（脱退前に呼ぶこと）
 *------------------------------------------
 */
void clif_party_leaved(struct party *p, struct map_session_data *sd, int account_id, char *name, int flag)
{
	unsigned char buf[64];
	int i;

	nullpo_retv(p);

	WBUFW(buf,0)=0x105;
	WBUFL(buf,2)=account_id;
	memcpy(WBUFP(buf,6),name,24);
	WBUFB(buf,30)=flag&0x0f;

	if((flag&0xf0)==0){
		if(sd==NULL)
			for(i=0;i<MAX_PARTY;i++)
				if((sd=p->member[i].sd)!=NULL)
					break;
		if(sd!=NULL)
			clif_send(buf,packet_db[0x105].len,&sd->bl,PARTY);
	}else if(sd!=NULL){
		memcpy(WFIFOP(sd->fd,0),buf,packet_db[0x105].len);
		WFIFOSET(sd->fd,packet_db[0x105].len);
	}

	return;
}

/*==========================================
 * パーティメッセージ送信
 *------------------------------------------
 */
void clif_party_message(struct party *p, int account_id, char *mes, int len)
{
	struct map_session_data *sd;
	int i;

	nullpo_retv(p);

	for(i=0;i<MAX_PARTY;i++){
		if((sd=p->member[i].sd)!=NULL)
			break;
	}
	if(sd!=NULL){
		unsigned char buf[1024];
		WBUFW(buf,0)=0x109;
		WBUFW(buf,2)=len+8;
		WBUFL(buf,4)=account_id;
		memcpy(WBUFP(buf,8),mes,len);
		clif_send(buf,len+8,&sd->bl,PARTY);
	}

	return;
}
/*==========================================
 * パーティ座標通知
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
//	if(battle_config.etc_log)
//		printf("clif_party_xy %d\n",sd->status.account_id);

	return;
}

/*==========================================
 * パーティHP通知
 *------------------------------------------
 */
void clif_party_hp(struct map_session_data *sd)
{
	unsigned char buf[16];

	nullpo_retv(sd);

	WBUFW(buf,0)=0x106;
	WBUFL(buf,2)=sd->status.account_id;
	WBUFW(buf,6)=(sd->status.hp > 0x7fff)? 0x7fff:sd->status.hp;
	WBUFW(buf,8)=(sd->status.max_hp > 0x7fff)? 0x7fff:sd->status.max_hp;
	clif_send(buf,packet_db[0x106].len,&sd->bl,PARTY_AREA_WOS);
//	if(battle_config.etc_log)
//		printf("clif_party_hp %d\n",sd->status.account_id);

	return;
}

/*==========================================
 * パーティ場所移動（未使用）
 *------------------------------------------
 */
/*void clif_party_move(struct party *p, struct map_session_data *sd, unsigned char online)
{
	unsigned char buf[128];

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
 * 攻撃するために移動が必要
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
	WFIFOW(fd,14)=sd->attackrange;
	WFIFOSET(fd,packet_db[0x139].len);

	return;
}

/*==========================================
 * 製造エフェクト
 *------------------------------------------
 */
void clif_produceeffect(struct map_session_data *sd, unsigned short flag, int nameid)
{
	int view,fd;

	nullpo_retv(sd);

	// 名前の登録と送信を先にしておく
	if( map_charid2nick(sd->status.char_id)==NULL )
		map_addchariddb(sd->status.char_id,sd->status.name,sd->status.account_id,clif_getip(),clif_getport());
	clif_solved_charname(sd,sd->status.char_id);

	fd=sd->fd;
	WFIFOW(fd, 0)=0x18f;
	WFIFOW(fd, 2)=flag;
	if((view = itemdb_viewid(nameid)) > 0)
		WFIFOW(fd, 4)=view;
	else
		WFIFOW(fd, 4)=nameid;
	WFIFOSET(fd,packet_db[0x18f].len);

	return;
}

// pet
void clif_catch_process(struct map_session_data *sd)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x19e;
	WFIFOSET(fd,packet_db[0x19e].len);

	return;
}

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
 * pet卵リスト作成
 *------------------------------------------
 */
void clif_sendegg(struct map_session_data *sd)
{
	//R 01a6 <len>.w <index>.w*
	int i,n=0,fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x1a6;
	if(sd->status.pet_id <= 0) {
		for(i=0,n=0;i<MAX_INVENTORY;i++){
			if(sd->status.inventory[i].nameid<=0 || sd->inventory_data[i] == NULL ||
			   sd->inventory_data[i]->type!=7 ||
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

void clif_send_petdata(struct map_session_data *sd, unsigned char type, int param)
{
	int fd;

	nullpo_retv(sd);

	if(!sd->pd) return; // 新密度0になるとNULL

	fd=sd->fd;
	WFIFOW(fd,0)=0x1a4;
	WFIFOB(fd,2)=type;
	WFIFOL(fd,3)=sd->pd->bl.id;
	WFIFOL(fd,7)=param;
	WFIFOSET(fd,packet_db[0x1a4].len);

	return;
}

void clif_send_petstatus(struct map_session_data *sd)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x1a2;
	memcpy(WFIFOP(fd,2),sd->pet.name,24);
	WFIFOB(fd,26)=(battle_config.pet_rename == 1)? 0:sd->pet.rename_flag;
	WFIFOW(fd,27)=sd->pet.level;
	WFIFOW(fd,29)=sd->pet.hungry;
	WFIFOW(fd,31)=sd->pet.intimate;
	WFIFOW(fd,33)=sd->pet.equip;
	WFIFOSET(fd,packet_db[0x1a2].len);

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

	memset(buf,0,packet_db[0x1aa].len);

	WBUFW(buf,0)=0x1aa;
	WBUFL(buf,2)=pd->bl.id;
	if(param >= 100 && sd->petDB->talk_convert_class) {
		if(sd->petDB->talk_convert_class < 0)
			return;
		else if(sd->petDB->talk_convert_class > 0) {
			param -= (pd->class - 100)*100;
			param += (sd->petDB->talk_convert_class - 100)*100;
		}
	}
	WBUFL(buf,6)=param;
	clif_send(buf,packet_db[0x1aa].len,&pd->bl,AREA);

	return;
}

void clif_pet_performance(struct block_list *bl, int param)
{
	unsigned char buf[16];

	nullpo_retv(bl);

	memset(buf,0,packet_db[0x1a4].len);

	WBUFW(buf,0)=0x1a4;
	WBUFB(buf,2)=4;
	WBUFL(buf,3)=bl->id;
	WBUFL(buf,7)=param;
	clif_send(buf,packet_db[0x1a4].len,bl,AREA);

	return;
}

void clif_pet_equip(struct pet_data *pd, int nameid)
{
	unsigned char buf[16];
	int view;

	nullpo_retv(pd);

	memset(buf,0,packet_db[0x1a4].len);

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

void clif_pet_food(struct map_session_data *sd, int foodid, unsigned char fail)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x1a3;
	WFIFOB(fd,2)=fail;
	WFIFOW(fd,3)=foodid;
	WFIFOSET(fd,packet_db[0x1a3].len);

	return;
}

/*==========================================
 * オートスペル リスト送信
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
		WFIFOL(fd,2)= 0x00000000;
	if(skilllv>1 && pc_checkskill2(sd,MG_COLDBOLT)>0)
		WFIFOL(fd,6)= MG_COLDBOLT;
	else
		WFIFOL(fd,6)= 0x00000000;
	if(skilllv>1 && pc_checkskill2(sd,MG_FIREBOLT)>0)
		WFIFOL(fd,10)= MG_FIREBOLT;
	else
		WFIFOL(fd,10)= 0x00000000;
	if(skilllv>1 && pc_checkskill2(sd,MG_LIGHTNINGBOLT)>0)
		WFIFOL(fd,14)= MG_LIGHTNINGBOLT;
	else
		WFIFOL(fd,14)= 0x00000000;
	if(skilllv>4 && pc_checkskill2(sd,MG_SOULSTRIKE)>0)
		WFIFOL(fd,18)= MG_SOULSTRIKE;
	else
		WFIFOL(fd,18)= 0x00000000;
	if(skilllv>7 && pc_checkskill2(sd,MG_FIREBALL)>0)
		WFIFOL(fd,22)= MG_FIREBALL;
	else
		WFIFOL(fd,22)= 0x00000000;
	if(skilllv>9 && pc_checkskill2(sd,MG_FROSTDIVER)>0)
		WFIFOL(fd,26)= MG_FROSTDIVER;
	else
		WFIFOL(fd,26)= 0x00000000;

	WFIFOSET(fd,packet_db[0x1cd].len);

	return;
}

/*==========================================
 * ディボーションの青い糸
 *------------------------------------------
 */
void clif_devotion(struct map_session_data *sd, int target)
{
	unsigned char buf[32];
	int n;

	nullpo_retv(sd);

	WBUFW(buf,0)=0x1cf;
	WBUFL(buf,2)=sd->bl.id;
//	WBUFL(buf,6)=target;
	for(n=0;n<5;n++)
		WBUFL(buf,6+4*n)=sd->dev.val2[n];
//		WBUFL(buf,10+4*n)=0;
	WBUFB(buf,26)=8;
	WBUFB(buf,27)=0;
	clif_send(buf,packet_db[0x1cf].len,&sd->bl,AREA);

	return;
}

/*==========================================
 * 氣球
 *------------------------------------------
 */
void clif_spiritball(struct map_session_data *sd)
{
	unsigned char buf[16];

	nullpo_retv(sd);

	WBUFW(buf,0)=0x1d0;
	WBUFL(buf,2)=sd->bl.id;
	WBUFW(buf,6)=sd->spiritball;
	clif_send(buf,packet_db[0x1d0].len,&sd->bl,AREA);

	return;
}

/*==========================================
 * コイン
 *------------------------------------------
 */
void clif_coin(struct map_session_data *sd)
{
	unsigned char buf[16];

	nullpo_retv(sd);

	WBUFW(buf,0)=0x1d0;
	WBUFL(buf,2)=sd->bl.id;
	WBUFW(buf,6)=sd->coin;
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
 *白刃取り
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
 * ゴスペルの効果表示
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
	char buf[32];

	bl.m = m;
	bl.x = x;
	bl.y = y;
	WBUFW(buf,0) = 0x192;
	WBUFW(buf,2) = x;
	WBUFW(buf,4) = y;
	WBUFW(buf,6) = cell_type;
	memcpy(WBUFP(buf,8),map[m].name,16);
	if(!type)
		clif_send(buf,packet_db[0x192].len,&bl,AREA);
	else
		clif_send(buf,packet_db[0x192].len,&bl,ALL_SAMEMAP);

	return;
}

/*==========================================
 * MVPエフェクト
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
 * MVPアイテム所得
 *------------------------------------------
 */
void clif_mvp_item(struct map_session_data *sd, int nameid)
{
	int view,fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x10a;
	if((view = itemdb_viewid(nameid)) > 0)
		WFIFOW(fd,2)=view;
	else
		WFIFOW(fd,2)=nameid;
	WFIFOSET(fd,packet_db[0x10a].len);

	return;
}

/*==========================================
 * MVPアイテム重量オーバー
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
 * MVP経験値所得
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
 * ギルド作成可否通知
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
 * ギルド所属通知
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
	memset(WFIFOP(fd,0),0,packet_db[0x16c].len);
	WFIFOW(fd,0)=0x16c;
	WFIFOL(fd,2)=g->guild_id;
	WFIFOL(fd,6)=g->emblem_id;
	WFIFOL(fd,10)=g->position[ps].mode;
	memcpy(WFIFOP(fd,19),g->name,24);
	WFIFOSET(fd,packet_db[0x16c].len);

	return;
}

/*==========================================
 * ギルドメンバログイン通知
 *------------------------------------------
 */
void clif_guild_memberlogin_notice(struct guild *g, int idx, unsigned char flag)
{
	unsigned char buf[16];

	nullpo_retv(g);

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

	return;
}

/*==========================================
 * ギルドマスター通知(14dへの応答)
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
 * ギルド基本情報
 *------------------------------------------
 */
void clif_guild_basicinfo(struct map_session_data *sd, struct guild *g)
{
	int fd;

	nullpo_retv(sd);

	if (g == NULL)
		return;

	fd=sd->fd;
	WFIFOW(fd, 0)=0x1b6;//0x150;
	WFIFOL(fd, 2)=g->guild_id;
	WFIFOL(fd, 6)=g->guild_lv;
	WFIFOL(fd,10)=g->connect_member;
	WFIFOL(fd,14)=g->max_member;
	WFIFOL(fd,18)=g->average_lv;
	WFIFOL(fd,22)=g->exp;
	WFIFOL(fd,26)=g->next_exp;
	WFIFOL(fd,30)=0;	// 上納
	WFIFOL(fd,34)=0;	// VW（性格の悪さ？：性向グラフ左右）
	WFIFOL(fd,38)=0;	// RF（正義の度合い？：性向グラフ上下）
	WFIFOL(fd,42)=0;	// 人数？
	memcpy(WFIFOP(fd,46),g->name,24);
	memcpy(WFIFOP(fd,70),g->master,24);
	memcpy(WFIFOP(fd,94),"",20);	// 本拠地
	WFIFOSET(fd,packet_db[WFIFOW(fd,0)].len);

	return;
}

/*==========================================
 * ギルド同盟/敵対情報
 *------------------------------------------
 */
void clif_guild_allianceinfo(struct map_session_data *sd, struct guild *g)
{
	int fd,i,c;

	nullpo_retv(sd);

	if (g == NULL)
		return;

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
 * ギルドメンバーリスト
 *------------------------------------------
 */
void clif_guild_memberlist(struct map_session_data *sd, struct guild *g)
{
	int fd;
	int i,c;

	nullpo_retv(sd);

	if (g == NULL)
		return;

	fd=sd->fd;
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
		WFIFOW(fd,c*104+18)=m->class;
		WFIFOW(fd,c*104+20)=m->lv;
		WFIFOL(fd,c*104+22)=m->exp;
		WFIFOL(fd,c*104+26)=(int)m->online;
		WFIFOL(fd,c*104+30)=m->position;
		memset(WFIFOP(fd,c*104+34),0,50);	// メモ？
		memcpy(WFIFOP(fd,c*104+84),m->name,24);
		c++;
	}
	WFIFOW(fd, 2)=c*104+4;
	WFIFOSET(fd,WFIFOW(fd,2));

	return;
}

/*==========================================
 * ギルド役職名リスト
 *------------------------------------------
 */
static void clif_guild_positionnamelist(struct map_session_data *sd, struct guild *g)
{
	int i,fd;

	nullpo_retv(sd);

	if (g == NULL)
		return;

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
 * ギルド役職情報リスト
 *------------------------------------------
 */
static void clif_guild_positioninfolist(struct map_session_data *sd, struct guild *g)
{
	int i,fd;

	nullpo_retv(sd);

	if (g == NULL)
		return;

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
 * ギルド役職変更通知
 *------------------------------------------
 */
void clif_guild_positionchanged(struct guild *g, int idx)
{
	struct map_session_data *sd;
	unsigned char buf[64];

	nullpo_retv(g);

	WBUFW(buf, 0)=0x174;
	WBUFW(buf, 2)=44;
	WBUFL(buf, 4)=idx;
	WBUFL(buf, 8)=g->position[idx].mode;
	WBUFL(buf,12)=idx;
	WBUFL(buf,16)=g->position[idx].exp_mode;
	memcpy(WBUFP(buf,20),g->position[idx].name,24);
	if( (sd=guild_getavailablesd(g))!=NULL )
		clif_send(buf,WBUFW(buf,2),&sd->bl,GUILD);

	return;
}

/*==========================================
 * ギルドメンバ変更通知
 *------------------------------------------
 */
void clif_guild_memberpositionchanged(struct guild *g, int idx)
{
	struct map_session_data *sd;
	unsigned char buf[32];

	nullpo_retv(g);

	WBUFW(buf, 0)=0x156;
	WBUFW(buf, 2)=16;
	WBUFL(buf, 4)=g->member[idx].account_id;
	WBUFL(buf, 8)=g->member[idx].char_id;
	WBUFL(buf,12)=g->member[idx].position;
	if( (sd=guild_getavailablesd(g))!=NULL )
		clif_send(buf,WBUFW(buf,2),&sd->bl,GUILD);

	return;
}

/*==========================================
 * ギルドエンブレム送信
 *------------------------------------------
 */
void clif_guild_emblem(struct map_session_data *sd, struct guild *g)
{
	int fd;

	nullpo_retv(sd);
	nullpo_retv(g);

	if(g->emblem_len<=0)
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
 * ギルドスキル送信
 *------------------------------------------
 */
void clif_guild_skillinfo(struct map_session_data *sd, struct guild *g)
{
	int fd;
	int i,id,c,up=1;

	nullpo_retv(sd);

	if (g == NULL)
		return;

	fd=sd->fd;
	WFIFOW(fd,0)=0x0162;
	WFIFOW(fd,4)=g->skill_point;
	c = 0;
	for(i = 0; i < MAX_GUILDSKILL; i++) {
		if(g->skill[i].id>0 && guild_check_skill_require(g,g->skill[i].id)){
			WFIFOW(fd,c*37+ 6) = id = g->skill[i].id;
			WFIFOW(fd,c*37+ 8) = guild_skill_get_inf(id);
			WFIFOW(fd,c*37+10) = 0;
			WFIFOW(fd,c*37+12) = g->skill[i].lv;
			WFIFOW(fd,c*37+14) = skill_get_sp(id,g->skill[i].lv);
			WFIFOW(fd,c*37+16) = skill_get_range(id,g->skill[i].lv);
			memset(WFIFOP(fd,c*37+18),0,24);
			if(g->skill[i].lv < guild_skill_get_max(id) && (sd == g->member[0].sd))
				up = 1;
			else
				up = 0;
			WFIFOB(fd,c*37+42)= up;//up;
			c++;
		}
	}
	WFIFOW(fd,2)=c*37+6;
	WFIFOSET(fd,WFIFOW(fd,2));

	return;
}

/*==========================================
 * ギルド告知送信
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
 * ギルドメンバ勧誘
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
 * ギルドメンバ勧誘結果
 *------------------------------------------
 */
void clif_guild_inviteack(struct map_session_data *sd, unsigned char flag) // flag: 0: in an other guild, 1: it was denied, 2: join, 3: guild has no more available place
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x169;
	WFIFOB(fd,2)=flag;
	WFIFOSET(fd,packet_db[0x169].len);

	return;
}

/*==========================================
 * ギルドメンバ脱退通知
 *------------------------------------------
 */
void clif_guild_leave(struct map_session_data *sd, const char *name, const char *mes)
{
	unsigned char buf[128];

	nullpo_retv(sd);

	WBUFW(buf, 0)=0x15a;
	memcpy(WBUFP(buf, 2),name,24);
	memcpy(WBUFP(buf,26),mes,40);
	clif_send(buf,packet_db[0x15a].len,&sd->bl,GUILD);

	return;
}

/*==========================================
 * ギルドメンバ追放通知
 *------------------------------------------
 */
void clif_guild_explusion(struct map_session_data *sd, const char *name, const char *mes, int account_id)
{
	unsigned char buf[128];

	nullpo_retv(sd);

	WBUFW(buf, 0)=0x15c;
	memcpy(WBUFP(buf, 2),name,24);
	memcpy(WBUFP(buf,26),mes,40);
	memcpy(WBUFP(buf,66),"dummy",24);
	clif_send(buf,packet_db[0x15c].len,&sd->bl,GUILD);

	return;
}

/*==========================================
 * ギルド追放メンバリスト
 *------------------------------------------
 */
static void clif_guild_explusionlist(struct map_session_data *sd, struct guild *g)
{
	int fd;
	int i,c;

	nullpo_retv(sd);

	if (g == NULL)
		return;

	fd=sd->fd;
	WFIFOW(fd,0)=0x163;
	c = 0;
	for(i = 0; i < MAX_GUILDEXPLUSION; i++) {
		struct guild_explusion *e=&g->explusion[i];
		if(e->account_id>0){
			memcpy(WFIFOP(fd,c*88+ 4),e->name,24);
			memcpy(WFIFOP(fd,c*88+28),e->acc,24);
			memcpy(WFIFOP(fd,c*88+52),e->mes,44);
			c++;
		}
	}
	WFIFOW(fd,2)=c*88+4;
	WFIFOSET(fd,WFIFOW(fd,2));

	return;
}

/*==========================================
 * ギルド会話
 *------------------------------------------
 */
void clif_guild_message(struct guild *g, int account_id, const char *mes, int len)
{
	struct map_session_data *sd;
	unsigned char *buf = malloc(len+32);

	WBUFW(buf, 0)=0x17f;
	WBUFW(buf, 2)=len+4;
	memcpy(WBUFP(buf,4),mes,len);

	if( (sd=guild_getavailablesd(g))!=NULL )
		clif_send(buf,WBUFW(buf,2),&sd->bl,GUILD);
	free(buf);

	return;
}

/*==========================================
 * ギルドスキル割り振り通知
 *------------------------------------------
 */
void clif_guild_skillup(struct map_session_data *sd, int skill_num, int lv)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0) = 0x10e;
	WFIFOW(fd,2) = skill_num;
	WFIFOW(fd,4) = lv;
	WFIFOW(fd,6) = skill_get_sp(skill_num,lv);
	WFIFOW(fd,8) = skill_get_range(skill_num,lv);
	WFIFOB(fd,10) = 1;
	WFIFOSET(fd,11);

	return;
}

/*==========================================
 * ギルド同盟要請
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
 * ギルド同盟結果
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
 * ギルド関係解消通知
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
 * ギルド敵対結果
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
 * ギルド関係追加
 *------------------------------------------
 */
/*int clif_guild_allianceadded(struct guild *g,int idx)
{
	unsigned char buf[64];

	WBUFW(fd,0)=0x185;
	WBUFL(fd,2)=g->alliance[idx].opposition;
	WBUFL(fd,6)=g->alliance[idx].guild_id;
	memcpy(WBUFP(fd,10),g->alliance[idx].name,24);
	clif_send(buf,packet_db[0x185].len,guild_getavailablesd(g),GUILD);

	return 0;
}*/
/*==========================================
 * ギルド解散通知
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
 * ギルドメンバーの位置座標送信
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
 * エモーション
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

/*==========================================
 * トーキーボックス
 *------------------------------------------
 */
void clif_talkiebox(struct block_list *bl,char* talkie)
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
 * 結婚エフェクト
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
 * あなたに逢いたい使用時名前叫び
 *------------------------------------------
 */
void clif_callpartner(struct map_session_data *sd)
{
	unsigned char buf[26];
	char *p;

	nullpo_retv(sd);

	if(sd->status.partner_id){
		WBUFW(buf,0)=0x1e6;
		p = map_charid2nick(sd->status.partner_id);
		if(p){
			memcpy(WBUFP(buf,2),p,24);
		}else{
			map_reqchariddb(sd,sd->status.partner_id);
			chrif_searchcharid(sd->status.partner_id);
			WBUFB(buf,2) = 0;
		}
		clif_send(buf,packet_db[0x1e6].len,&sd->bl,AREA);
	}

	return;
}

/*==========================================
 * 離婚完了通知
 *------------------------------------------
 */
void clif_divorced(struct map_session_data *sd, char *name)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0) = 0x205;
	memcpy(WFIFOP(fd,2),name,24);
	WFIFOSET(fd,packet_db[0x205].len);

	return;
}

/*==========================================
 * 座る
 *------------------------------------------
 */
void clif_sitting(struct map_session_data *sd)
{
	int fd;

	nullpo_retv(sd);

	fd=sd->fd;
	WFIFOW(fd,0)=0x8a;
	WFIFOL(fd,2)=sd->bl.id;
	WFIFOB(fd,26)=2;
	clif_send(WFIFOP(fd,0),packet_db[0x8a].len,&sd->bl,AREA);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void clif_disp_onlyself(struct map_session_data *sd, char *mes, int len)
{
	unsigned char *buf = malloc(len+32);

	nullpo_retv(sd);

	WBUFW(buf, 0)=0x17f;
	WBUFW(buf, 2)=len+8;
	memcpy(WBUFP(buf,4),mes,len+4);

	clif_send(buf,WBUFW(buf,2),&sd->bl,SELF);
	free(buf);

	return;
}

/*==========================================
 * 叫ぶ
 *------------------------------------------
 */
static void clif_onlymessage(struct map_session_data *sd, char *mes, int len)
{
	unsigned char *buf = malloc(len+32);

	if(battle_config.mes_send_type){
		WBUFW(buf, 0)=0x08d;
		WBUFW(buf, 2)=len+8;
		WBUFL(buf, 4)=0;
		memcpy(WBUFP(buf,8),mes,len);
	} else {
		WBUFW(buf, 0)=0x17f;
		WBUFW(buf, 2)=len+4;
		memcpy(WBUFP(buf,4),mes,len);
	}

	clif_send(buf,WBUFW(buf,2),NULL,ALL_CLIENT);
	free(buf);

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


void clif_GM_kick(struct map_session_data *sd, struct map_session_data *tsd, int type)
{
	int fd;

	nullpo_retv(tsd);

	if(type)
		clif_GM_kickack(sd,tsd->status.account_id);
	tsd->opt1 = 0;
	tsd->opt2 = 0;
	fd = tsd->fd;
	WFIFOW(fd,0)=0x18b;
	WFIFOW(fd,2)=0;
	WFIFOSET(fd,packet_db[0x18b].len);
	clif_setwaitclose(fd);

	return;
}

/*==========================================
 * Wis拒否許可応答
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
 * Wis全拒否許可応答
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
 * サウンドエフェクト
 *------------------------------------------
 */
void clif_soundeffect(struct map_session_data *sd,struct block_list *bl,char *name,int type)
{
	int fd;

	nullpo_retv(sd);
	nullpo_retv(bl);

	fd=sd->fd;
	WFIFOW(fd,0)=0x1d3;
	memcpy(WFIFOP(fd,2),name,24);
	WFIFOB(fd,26)=type;
	WFIFOL(fd,27)=0;
	WFIFOL(fd,31)=bl->id;
	WFIFOSET(fd,packet_db[0x1d3].len);

	return;
}

// -- 友達リスト関連

/*==========================================
 * 友達リストの情報通知
 *------------------------------------------
 */
void clif_friend_send_info( struct map_session_data *sd )
{
	int len,i;
	int fd;
	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW( fd, 0 ) = 0x201;
	for( i=0, len=4; i<sd->status.friend_num; i++, len+=32 )
	{
		struct friend_data *frd = &sd->status.friend_data[ i ];
		WFIFOL( fd, len   ) = frd->account_id;
		WFIFOL( fd, len+4 ) = frd->char_id;
		memcpy( WFIFOP( fd, len+8 ), frd->name, 24 );
	}
	WFIFOW( fd, 2 ) = len;
	WFIFOSET( fd, len );

	return;
}

/*==========================================
 * 友達リストのオンライン情報通知
 *------------------------------------------
 */
void clif_friend_send_online(const int fd, int account_id, int char_id, int flag )
{
	WFIFOW( fd, 0 ) = 0x206;
	WFIFOL( fd, 2 ) = account_id;
	WFIFOL( fd, 6 ) = char_id;
	WFIFOB( fd,10 ) = flag;
	WFIFOSET( fd, packet_db[0x206].len );

	return;
}

/*==========================================
 * 友達リスト追加要請
 *------------------------------------------
 */
void clif_friend_add_request(const int fd, struct map_session_data *from_sd )
{
	WFIFOW( fd, 0 ) = 0x207;
	WFIFOL( fd, 2 ) = from_sd->bl.id;
	WFIFOL( fd, 6 ) = from_sd->status.char_id;
	memcpy(WFIFOP( fd, 10 ), from_sd->status.name, 24 );
	WFIFOSET( fd, packet_db[0x207].len );

	return;
}

/*==========================================
 * 友達リスト追加要請返答
 *------------------------------------------
 */
void clif_friend_add_ack(const int fd, int account_id, int char_id, char* name, unsigned short flag)
{
	WFIFOW( fd, 0 ) = 0x209;
	WFIFOW( fd, 2 ) = flag;
	WFIFOL( fd, 4 ) = account_id;
	WFIFOL( fd, 8 ) = char_id;
	memcpy(WFIFOP( fd, 12 ), name, 24 );
	WFIFOSET( fd, packet_db[0x209].len );

	return;
}

/*==========================================
 * 友達リスト追加削除通知
 *------------------------------------------
 */
void clif_friend_del_ack(const int fd, int account_id, int char_id )
{
	WFIFOW( fd, 0 ) = 0x20a;
	WFIFOL( fd, 2 ) = account_id;
	WFIFOL( fd, 6 ) = char_id;
	WFIFOSET( fd, packet_db[0x20a].len );

	return;
}

// ランキング表示関連
/*==========================================
 * BSランキング
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

void clif_blacksmith_ranking(const int fd,char *charname[10],const int point[10])
{
	int i;

	WFIFOW(fd,0) = 0x219;
	for(i=0;i<10;i++){
		memcpy(WFIFOP(fd,i*24+2), charname[i], 24 );
		WFIFOL(fd,i*4+242) = point[i];
	}
	WFIFOSET(fd,packet_db[0x219].len);

	return;
}

/*==========================================
 * アルケミランキング
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

void clif_alchemist_ranking(const int fd,char *charname[10],const int point[10])
{
	int i;

	WFIFOW(fd,0) = 0x21a;
	for(i=0;i<10;i++){
		memcpy(WFIFOP(fd,i*24+2), charname[i], 24 );
		WFIFOL(fd,i*4+242) = point[i];
	}
	WFIFOSET(fd,packet_db[0x21a].len);

	return;
}

/*==========================================
 * テコンランキング
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

void clif_taekwon_ranking(const int fd,char *charname[10],const int point[10])
{
	int i;

	WFIFOW(fd,0) = 0x226;
	for(i=0;i<10;i++){
		memcpy(WFIFOP(fd,i*24+2), charname[i], 24 );
		WFIFOL(fd,i*4+242) = point[i];
	}
	WFIFOSET(fd,packet_db[0x226].len);

	return;
}

/*==========================================
 * 虐殺者ランキング
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

void clif_pk_ranking(const int fd,char *charname[10],const int point[10])
{
	int i;

	WFIFOW(fd,0) = 0x238;
	for(i=0;i<10;i++){
		memcpy(WFIFOP(fd,i*24+2), charname[i], 24 );
		WFIFOL(fd,i*4+242) = point[i];
	}
	WFIFOSET(fd,packet_db[0x238].len);

	return;
}

/*==========================================
 * メールBOXを表示させる
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
 * メール一覧表（BOXを開いている時に蔵へ送信）
 *  0x23fの応答
 *------------------------------------------
 */
void clif_send_mailbox(struct map_session_data *sd,int mail_num,struct mail_data *md[MAIL_STORE_MAX])
{
	int len,fd;
	int i;

	if(!sd || mail_num<=0)
		return;

	fd=sd->fd;
	WFIFOW(fd,0)  = 0x240;
	WFIFOW(fd,2)  = (len=8+73*mail_num);
	WFIFOL(fd,4)  = mail_num;	// 0だとエラー
	for(i=0;i<mail_num && md[i];i++){
		WFIFOL(fd,8+73*i)  = md[i]->mail_num;
		memcpy(WFIFOP(fd,12+73*i),md[i]->title,40);
		WFIFOB(fd,52+73*i) = md[i]->read;
		memcpy(WFIFOP(fd,53+73*i),md[i]->char_name, 24);
		WFIFOL(fd,77+73*i) = md[i]->times;
	}
	WFIFOSET(fd,len);

	return;
}

/*==========================================
 * メールが送信できましたとかできませんとか
 *------------------------------------------
 */
void clif_res_sendmail(const int fd,int flag)
{
	WFIFOW(fd,0) = 0x249;
	WFIFOB(fd,2) = flag;
	WFIFOSET(fd,packet_db[0x249].len);

	return;
}

/*==========================================
 * アイテムが添付できましたとかできませんとか
 *------------------------------------------
 */
static void clif_res_sendmail_setappend(const int fd,int flag)
{
	WFIFOW(fd,0) = 0x245;
	WFIFOB(fd,2) = flag;
	WFIFOSET(fd,packet_db[0x245].len);

	return;
}

/*==========================================
 * 新着メールが届きました
 *------------------------------------------
 */
void clif_arrive_newmail(const int fd,struct mail_data *md)
{
	if(!md)
		return;

	WFIFOW(fd,0) = 0x24a;
	WFIFOL(fd,2) = md->mail_num;
	memcpy(WFIFOP(fd, 6),md->char_name ,24);
	memcpy(WFIFOP(fd,30),md->title ,40);
	WFIFOSET(fd,packet_db[0x24a].len);

	return;
}

/*==========================================
 * メールを選択受信	Inter→本人へ
 *------------------------------------------
 */
void clif_receive_mail(struct map_session_data *sd,struct mail_data *md)
{
	int len,fd;
	struct item_data *data;

	if(!md)
		return;

	len=99+strlen(md->body);
	fd=sd->fd;

	WFIFOW(fd,0)=0x242;
	WFIFOW(fd,2)=len;
	WFIFOL(fd,4)=md->mail_num;
	memcpy(WFIFOP(fd, 8),md->title ,sizeof(md->title));
	memcpy(WFIFOP(fd,48),md->char_name,sizeof(md->char_name));
	WFIFOL(fd,72)=0x22;	// 境界？
	WFIFOL(fd,76)=md->zeny;
	WFIFOL(fd,80)=md->item.amount;
	data = itemdb_search(md->item.nameid);
	if(data->view_id > 0)
		WFIFOW(fd,84)=data->view_id;
	else
		WFIFOW(fd,84)=md->item.nameid;
	WFIFOW(fd,86)=0;
	WFIFOB(fd,88)=md->item.identify;
	WFIFOB(fd,89)=md->item.attribute;
	// refineやcardを入れても認識してくれない？
	WFIFOW(fd,90)=0;	// 謎
	WFIFOW(fd,92)=0;	// 謎
	WFIFOW(fd,94)=0;	// 謎
	WFIFOW(fd,96)=0;	// 謎
	WFIFOB(fd,98)=0x22;
	memcpy(WFIFOP(fd,99),md->body,strlen(md->body));
	WFIFOSET(fd,len);

	return;
}

/*==========================================
 * メールが削除できましたとかできませんとか
 *------------------------------------------
 */
void clif_deletemail_res(const int fd,int mail_num,int flag)
{
	WFIFOW(fd,0) = 0x257;
	WFIFOL(fd,2) = mail_num;
	WFIFOL(fd,6) = flag;
	WFIFOSET(fd,packet_db[0x257].len);

	return;
}

/*==========================================
 * 方向転換
 *------------------------------------------
 */

void clif_changedir( struct block_list *bl, int headdir, int dir ){
	char buf[16];

	nullpo_retv(bl);

	WBUFW(buf,0)=0x9c;
	WBUFL(buf,2)=bl->id;
	WBUFW(buf,6)=headdir;
	WBUFB(buf,8)=(unsigned char)dir;
	clif_send(buf,packet_db[0x9c].len,bl,AREA_WOS);

	return;
}

/*==========================================
 * 太陽と月と星の感情の登録完了
 *------------------------------------------
 */
static void clif_feel_saveack(struct map_session_data *sd, int lv)
{
	int fd;

	nullpo_retv(sd);

	if(lv < 0 || lv > 2)
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
 * 太陽と月と星の感情の登録情報
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
 * 太陽と月と星の憎しみの登録完了
 *------------------------------------------
 */
void clif_hate_mob(struct map_session_data *sd, int skilllv, int id)
{
	int fd;

	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x20e;
	if(mobdb_checkid(id) > 0) {
		strncpy(WFIFOP(fd,2),mob_db[id].jname,24);
	} else {
		char output[24];
		sprintf(output, "JOB (%d)",id);
		strncpy(WFIFOP(fd,2),output,24);
	}
	WFIFOL(fd,26) = sd->bl.id;
	WFIFOB(fd,30) = skilllv-1;
	WFIFOB(fd,31) = 10;
	WFIFOSET(fd,packet_db[0x20e].len);

	return;
}

/*==========================================
 * 太陽と月と星の憎しみの登録情報
 *------------------------------------------
 */
void clif_hate_info(struct map_session_data *sd, int skilllv, int id)
{
	int fd;

	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x20e;
	if(mobdb_checkid(id) > 0) {
		strncpy(WFIFOP(fd,2),mob_db[id].jname,24);
	} else {
		char output[24];
		sprintf(output, "JOB (%d)",id);
		strncpy(WFIFOP(fd,2),output,24);
	}
	WFIFOL(fd,26) = sd->bl.id;
	WFIFOB(fd,30) = skilllv-1;
	WFIFOB(fd,31) = 11;
	WFIFOSET(fd,packet_db[0x20e].len);

	return;
}

/*==========================================
 * テコンミッション
 *------------------------------------------
 */
void clif_mission_mob(struct map_session_data *sd, int id, int count)
{
	int fd;

	nullpo_retv(sd);

	fd = sd->fd;
	WFIFOW(fd,0) = 0x20e;
	strncpy(WFIFOP(fd,2),mob_db[id].jname,24);
	WFIFOL(fd,26) = id;
	WFIFOB(fd,30) = count;
	WFIFOB(fd,31) = 20;
	WFIFOSET(fd,packet_db[0x20e].len);

	return;
}

/*==========================================
 * 太陽と月と星の天使（未実装）
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
 * 太陽と月と星の感情のダイアログ表示
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
 * send packet デバッグ用
 *------------------------------------------
 */
void clif_send_packet(struct map_session_data *sd, const char *message)
{
	int fd,n,i;
	int packet,len,db_len;
	int p[256];

	nullpo_retv(sd);

	// 任意の読み込みは30byteまで許可する
	n = sscanf(message, "%x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x",
				&packet,&p[2],&p[3],&p[4],&p[5],&p[6],&p[7],&p[8],&p[9],
				&p[10],&p[11],&p[12],&p[13],&p[14],&p[15],&p[16],&p[17],&p[18],&p[19],
				&p[20],&p[21],&p[22],&p[23],&p[24],&p[25],&p[26],&p[27],&p[28],&p[29]);
	if(n == 0)
		return;
	if(packet < 0 || packet > MAX_PACKET_DB)
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
	} else {	// 可変長
		if(n == 1 || p[2] <= 0){
			printf("clif_send_packet_test packet:%x len=-1 input len %cpacket len x1 x2...\n", packet, GM_Symbol());
			return;
		}
		WFIFOW(fd,2) = (len=p[2]);
		i = 4;		// p[2]をshort型として取るためp[3]は無視する
	}

	for(; i < len; i++) {
		if(i < n+1)
			WFIFOB(fd,i)= p[i];
		else
			WFIFOB(fd,i)= (p[i]=atn_rand()%256);
	}
	printf("clif_send_packet_test packet:%x len:%d\nSend:",packet,db_len);
	for(i = 0; i < len; i++) {
		if(i > 0 && !(i&0x0f))
			printf("\n     ");
		printf(" %02d",i);
	}
	printf("\nRead:");
	for(i = 0; i < len; i++) {
		if(i > 0 && !(i&0x0f))
			printf("\n     ");
		printf(" %02x",p[i]);
	}
	printf("\n");
	WFIFOSET(fd,len);

	return;
}

// ------------
// clif_parse_*
// ------------
// パケット読み取って色々操作
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

	// アカウントIDの不正チェック
	if(account_id < START_ACCOUNT_NUM || account_id > END_ACCOUNT_NUM) {
		printf("clif_parse_WantToConnection : invalid Account ID !!\n");
		return;
	}
	// Sexのチェック
	if(sex < 0 || sex > 1) {
		printf("clif_parse_WantToConnection : invalid Sex !!\n");
		return;
	}

	session[fd]->session_data = (struct map_session_data *)aCalloc(1,sizeof(struct map_session_data));
	sd = session[fd]->session_data;
	sd->fd = fd;

	pc_setnewpc(sd, account_id, char_id, login_id1, client_tick, sex);
	if((old_sd = map_id2sd(account_id)) != NULL) {
		// 2重loginなので切断用のデータを保存する
		old_sd->new_fd=fd;
		sd->new_fd = -1; // 新しいデータはセーブしないフラグ
	} else {
		map_addiddb(&sd->bl);
	}

	if(chrif_authreq(sd))
		session[fd]->eof = 1;

	WFIFOL(fd,0) = sd->bl.id; // account_id
	WFIFOSET(fd,4);

	return;
}

/*==========================================
 * 007d クライアント側マップ読み込み完了
 * map侵入時に必要なデータを全て送りつける
 *------------------------------------------
 */
static void clif_parse_LoadEndAck(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	if(sd->bl.prev != NULL)
		return;

	// 接続ok時
	//clif_authok();
	if(sd->npc_id) npc_event_dequeue(sd);
	clif_skillinfoblock(sd);
	pc_checkitem(sd);
	//guild_info();

	// loadendack時

	// next exp
	clif_updatestatus(sd,SP_NEXTBASEEXP);
	clif_updatestatus(sd,SP_NEXTJOBEXP);
	// skill point
	clif_updatestatus(sd,SP_SKILLPOINT);
	// item
	clif_itemlist(sd);
	clif_equiplist(sd);
	// cart
	if(pc_iscarton(sd)){
		clif_cart_itemlist(sd);
		clif_cart_equiplist(sd);
		clif_updatestatus(sd,SP_CARTINFO);
	}
	// param all
	clif_initialstatus(sd);
	// party
	party_send_movemap(sd);
	// guild
	guild_send_memberinfoshort(sd,1);
	// friend
	friend_send_info(sd);
	friend_send_online( sd, 0 );

	if(battle_config.pc_invincible_time > 0) {
		if(map[sd->bl.m].flag.gvg)
			pc_setinvincibletimer(sd,battle_config.pc_invincible_time<<1);
		else
			pc_setinvincibletimer(sd,battle_config.pc_invincible_time);
	}

	map_addblock(&sd->bl);	// ブロック登録
	clif_spawnpc(sd);	// spawn
	mob_ai_hard_spawn( &sd->bl, 1 );

	// weight max , now
	clif_updatestatus(sd,SP_MAXWEIGHT);
	clif_updatestatus(sd,SP_WEIGHT);

	// pvp
	if(sd->pvp_timer!=-1)
		delete_timer(sd->pvp_timer,pc_calc_pvprank_timer);
	if(map[sd->bl.m].flag.pk){
		sd->pvp_timer=-1;
		if(battle_config.pk_noshift)
			clif_set0199(sd->fd,1);
	}else if(map[sd->bl.m].flag.pvp){
		sd->pvp_timer=add_timer(gettick()+200,pc_calc_pvprank_timer,sd->bl.id,0);
		sd->pvp_rank=0;
		sd->pvp_lastusers=0;
		sd->pvp_point=5;
		clif_set0199(sd->fd,1);
	}
	else {
		sd->pvp_timer=-1;
	}
	if(map[sd->bl.m].flag.gvg) {
		clif_set0199(sd->fd,3);
	}

	// pet
	if(sd->status.pet_id > 0 && sd->pd && sd->pet.intimate > 0) {
		map_addblock(&sd->pd->bl);
		clif_spawnpet(sd->pd);
		clif_send_petdata(sd,0,0);
		clif_send_petdata(sd,5,0x14);
		clif_send_petstatus(sd);
	}
	// ホムンクルス
	if(sd->hd){
		map_addblock(&sd->hd->bl);
		mob_ai_hard_spawn( &sd->hd->bl, 1 );
		clif_spawnhom(sd->hd);
		clif_send_homdata(sd,0,0);
		clif_send_homstatus(sd,1);
		clif_send_homstatus(sd,0);
	}
	if(sd->state.connect_new) {
		// ステータス異常データ要求
		// pc_authok() で呼び出すとクライアントにエフェクトが反映されない
		intif_request_scdata(sd->status.account_id,sd->status.char_id);

		if(sd->status.class != sd->view_class)
			clif_changelook(&sd->bl,LOOK_BASE,sd->view_class);
		if(sd->status.pet_id > 0 && sd->pd && sd->pet.intimate > 900)
			clif_pet_emotion(sd->pd,(sd->pd->class - 100)*100 + 50 + pet_hungry_val(sd));
	}

	// view equipment item
#if PACKETVER < 4
	clif_changelook(&sd->bl,LOOK_WEAPON,sd->status.weapon);
	clif_changelook(&sd->bl,LOOK_SHIELD,sd->status.shield);
#else
	clif_changelook(&sd->bl,LOOK_WEAPON,0);
#endif

	if(sd->status.hp<sd->status.max_hp>>2 && pc_checkskill(sd,SM_AUTOBERSERK)>0 &&
		(sd->sc_data[SC_PROVOKE].timer==-1 || sd->sc_data[SC_PROVOKE].val2==0 ))
		// オートバーサーク発動
		status_change_start(&sd->bl,SC_PROVOKE,10,1,0,0,0,0);

	//暫定　赤エモ防止処理
	if(battle_config.nomanner_mode && sd->status.manner < 0)
		sd->status.manner = 0;

	if(sd->status.manner < 0)
		status_change_start(&sd->bl,SC_NOCHAT,0,0,0,0,0,0);

	// option系初期化(クライアントに対する...)
	// 同一パケを2回送ることでも十分ですが、気持ち悪いので0で初期化という形に
	//clif_changeoption_clear(&sd->bl); これが削除されたので下を追加しました(1577)
	clif_changeoption(&sd->bl);
	// option
	clif_changeoption(&sd->bl);

	clif_send_clothcolor(&sd->bl);

	if(sd->sc_data[SC_TRICKDEAD].timer != -1)
		status_change_end(&sd->bl,SC_TRICKDEAD,-1);
	if(sd->sc_data[SC_SIGNUMCRUCIS].timer != -1 && !battle_check_undead(7,sd->def_ele))
		status_change_end(&sd->bl,SC_SIGNUMCRUCIS,-1);

	map_foreachinarea(clif_getareachar,sd->bl.m,sd->bl.x-AREA_SIZE,sd->bl.y-AREA_SIZE,sd->bl.x+AREA_SIZE,sd->bl.y+AREA_SIZE,0,sd);

	if(sd->state.connect_new) {
		sd->state.connect_new = 0;
		//OnPCLoginイベント
		if(battle_config.pc_login_script)
			npc_event_doall_id("OnPCLogin",sd->bl.id,sd->bl.m);
	}

	if(map_getcell(sd->bl.m,sd->bl.x,sd->bl.y,CELL_CHKNPC))
		npc_touch_areanpc(sd,sd->bl.m,sd->bl.x,sd->bl.y);
	else
		sd->areanpc_id = 0;

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_TickSend(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	sd->client_tick=RFIFOL(fd,GETPACKETPOS(cmd,0));
	sd->server_tick=gettick();
	clif_servertick(sd);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_WalkToXY(int fd,struct map_session_data *sd, int cmd)
{
	int x,y;

	nullpo_retv(sd);

	if(unit_isdead(&sd->bl)) {
		clif_clearchar_area(&sd->bl,1);
		return;
	}

	if( sd->npc_id != 0 || sd->vender_id != 0 || sd->deal_mode != 0 || sd->chatID != 0 )
		return;
	if( pc_issit(sd) )
		return;

	if(unit_can_move(&sd->bl) && !unit_isrunning(&sd->bl)) {
		if(sd->invincible_timer != -1)
			pc_delinvincibletimer(sd);

		unit_stopattack(&sd->bl);

		x = RFIFOB(fd,GETPACKETPOS(cmd,0))*4+(RFIFOB(fd,GETPACKETPOS(cmd,0)+1)>>6);
		y = ((RFIFOB(fd,GETPACKETPOS(cmd,0)+1)&0x3f)<<4)+(RFIFOB(fd,GETPACKETPOS(cmd,0)+2)>>4);

		unit_walktoxy(&sd->bl,x,y);
	}
	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_QuitGame(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	WFIFOW(fd,0)=0x18b;
	if(pc_isquitable(sd)){
		WFIFOW(fd,2)=1; // flag= 0: success, 1: failure (please wait 15 sec...)
		WFIFOSET(fd,packet_db[0x18b].len);
		return;
	}
	WFIFOW(fd,2)=0;
	WFIFOSET(fd,packet_db[0x18b].len);
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

	memset(WFIFOP(fd,0), 0, packet_db[0x195].len);
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

			if ((battle_config.show_always_party_name && p != NULL) || g != NULL) {
				// ギルド所属ならパケット0195を返す
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
				WFIFOSET(fd, packet_db[0x195].len);
				break;
			}
			WFIFOSET(fd,packet_db[0x95].len);
		}
		break;
	case BL_PET:
		memcpy(WFIFOP(fd,6),((struct pet_data*)bl)->name,24);
		WFIFOSET(fd,packet_db[0x95].len);
		break;
	case BL_NPC:
		{
			struct npc_data *snd=(struct npc_data*)bl;
			memcpy(WFIFOP(fd,6),snd->name,24);
			if(strlen(snd->position)>0){
				// ギルド所属ならパケット0195を返す
				WFIFOW(fd, 0)=0x195;
				strncpy(WFIFOP(fd,30),"NPC",24);	// PT名
				strncpy(WFIFOP(fd,54),"NPC",24);	// Guild名
				memcpy(WFIFOP(fd,78),snd->position,24);
				WFIFOSET(fd,packet_db[0x195].len);
				break;
			}
			WFIFOSET(fd,packet_db[0x95].len);
		}
		break;
	case BL_MOB:
		{
			// struct mob_data *smd=(struct mob_data *)bl;
			// struct guild *g=NULL;
			// struct guild_castle *gc=NULL;
			memcpy(WFIFOP(fd,6),((struct mob_data*)bl)->name,24);
			/*=============================================================
			if( smd->guild_id>0 &&(g=guild_search(smd->guild_id))!=NULL ){
				int i;
				for(i=0;i<MAX_GUILDCASTLE;i++){
					gc=guild_castle_search(i);
					if(gc->guild_id == g->guild_id){
						break;
					}
				}
				// ギルド所属ならパケット0195を返す
				WFIFOW(fd, 0)=0x195;
				strncpy(WFIFOP(fd,30),"NPC",24);	// PT名
				memcpy(WFIFOP(fd,54),g->name,24);	// Guild名
			//	strncpy(WFIFOP(fd,78),"",24);		// 役職名
				memcpy(WFIFOP(fd,78),gc->castle_name,24);
				WFIFOSET(fd,packet_db[0x195].len);
				break;
			}
			*-------------------------------------------------------------
			*/
			WFIFOSET(fd,packet_db[0x95].len);
		} 
		break;
	case BL_HOM:
		{
			memcpy(WFIFOP(fd,6),((struct homun_data*)bl)->status.name,24);
			WFIFOSET(fd,packet_db[0x95].len);
		}
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

	if (message_size < 8) // name (mini:4) + " : " (3) + NULL (1) (void mesages are possible for skills)
		return;

	message[message_size - 1] = 0; // be sure to have a NULL (hacker can send a no-NULL terminated string)

	if (battle_config.check_player_name_global_msg) {
		// structure of message: <player_name> : <message>
		int name_length;
		char *p_message;
		name_length = strlen(sd->status.name);
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

	if (is_atcommand(fd, sd, message, 0) != AtCommand_None)
		return;
	if(sd->sc_data &&
	   (sd->sc_data[SC_BERSERK].timer != -1 ||	//バーサーク時は会話も不可
	    sd->sc_data[SC_NOCHAT].timer != -1))	//チャット禁止
		return;

	WFIFOW(fd,0) = 0x8d;
	WFIFOW(fd,2) = message_size + 8;
	WFIFOL(fd,4) = sd->bl.id;
	memcpy(WFIFOP(fd,8), message, message_size);
	clif_send(WFIFOP(fd,0), WFIFOW(fd,2), &sd->bl, sd->chatID ? CHAT_WOS : AREA_CHAT_WOC);

	memcpy(WFIFOP(fd,0), RFIFOP(fd,0), len);
	WFIFOW(fd,0) = 0x8e;
	WFIFOSET(fd,WFIFOW(fd,2));

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_MapMove(int fd,struct map_session_data *sd, int cmd)
{
	char mapname[17];
	int x,y;

	if (battle_config.atc_gmonly == 0 ||
	    pc_isGM(sd) >= get_atcommand_level(AtCommand_MapMove)) {
		mapname[16] = 0;
		memcpy(mapname, RFIFOP(fd,GETPACKETPOS(cmd,0)), 16);
		if (mapname[0] != '\0') {
			x = RFIFOW(fd, GETPACKETPOS(cmd,1));
			y = RFIFOW(fd, GETPACKETPOS(cmd,2));
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
	short headdir,dir;

	nullpo_retv(sd);

	headdir=RFIFOW(fd,GETPACKETPOS(cmd,0));
	dir=RFIFOB(fd,GETPACKETPOS(cmd,1));
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
	int emotion;

	nullpo_retv(sd);

	if(battle_config.basic_skill_check == 0 || pc_checkskill(sd,NV_BASIC) >= 2){
		emotion=RFIFOB(fd,GETPACKETPOS(cmd,0));
		WFIFOW(fd,0)=0xc0;
		WFIFOL(fd,2)=sd->bl.id;
		WFIFOB(fd,6)=emotion;
		clif_send(WFIFOP(fd,0),packet_db[0xc0].len,&sd->bl,AREA);
	}
	else
		clif_skill_fail(sd,1,0,1);

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
	if(sd->npc_id!=0 || sd->opt1 > 0 || sd->status.option&2 ||
	   (sd->sc_data &&
	    (sd->sc_data[SC_AUTOCOUNTER].timer != -1 ||	//オートカウンター
	     sd->sc_data[SC_BLADESTOP].timer != -1 ||	//白刃取り
	     sd->sc_data[SC_FORCEWALKING].timer != -1 ||	//強制移動中
	     (sd->sc_data[SC_DANCING].timer!=-1 && sd->sc_data[SC_LONGINGFREEDOM].timer == -1))) ) // ダンス中
			return;

	tick=gettick();

	unit_stop_walking(&sd->bl,1);
	unit_stopattack(&sd->bl);

	target_id = RFIFOL(fd,GETPACKETPOS(cmd,0));
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
		{
			struct block_list *bl=map_id2bl(target_id);
			if(sd->vender_id != 0) return;
			if(bl && mob_gvmobcheck(sd,bl)==0)
				return;

			if(!battle_config.sdelay_attack_enable && pc_checkskill(sd,SA_FREECAST) <= 0 ) {
				if(DIFF_TICK(tick , sd->ud.canact_tick) < 0) {
					clif_skill_fail(sd,1,4,0);
					return;
				}
			}
			if (sd->sc_data[SC_WEDDING].timer!=-1 || sd->sc_data[SC_BASILICA].timer!=-1 || sd->sc_data[SC_GOSPEL].timer!=-1)
				return;
			if(sd->invincible_timer != -1)
				pc_delinvincibletimer(sd);
			unit_attack(&sd->bl,target_id,action_type!=0);
		}
		break;
	case 0x02:	// sitdown
		if(battle_config.basic_skill_check == 0 || pc_checkskill(sd,NV_BASIC) >= 3) {
			pc_setsit(sd);
			clif_sitting(sd);
			skill_gangsterparadise(sd,1);/* ギャングスターパラダイス設定 */
		}
		else
			clif_skill_fail(sd,1,0,2);
		break;
	case 0x03:	// standup
		pc_setstand(sd);
		WFIFOW(fd,0)=0x8a;
		WFIFOL(fd,2)=sd->bl.id;
		WFIFOB(fd,26)=3;
		clif_send(WFIFOP(fd,0),packet_db[0x8a].len,&sd->bl,AREA);
		skill_gangsterparadise(sd,0);/* ギャングスターパラダイス解除 */
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
		if(unit_isdead(&sd->bl)){
			pc_setstand(sd);
			pc_setrestartvalue(sd,3);
			pc_setpos(sd,sd->status.save_point.map,sd->status.save_point.x,sd->status.save_point.y,2);
		}
		break;
	case 0x01: // 1: request character select
		if(unit_isdead(&sd->bl))
			pc_setrestartvalue(sd,3);
		if(pc_isquitable(sd)){
			WFIFOW(fd,0)=0x18b;
			WFIFOW(fd,2)=1;
			WFIFOSET(fd,packet_db[0x18b].len);
			return;
		}
		if( sd->pd )
			unit_free( &sd->pd->bl, 0);
		if( sd->hd )
			unit_free( &sd->hd->bl, 0);
		unit_free(&sd->bl, 0);
		chrif_save(sd);
		chrif_charselectreq(sd);
		break;
	}

	return;
}

/*==========================================
 * Wisの送信
 *------------------------------------------
 */
static void clif_parse_Wis(int fd,struct map_session_data *sd, int cmd)
{
	char *message, *gm_message;
	int message_size;

	nullpo_retv(sd);

	message_size = RFIFOW(fd,GETPACKETPOS(cmd,0)) - GETPACKETPOS(cmd,2); // including NULL
	message = (char *)RFIFOP(fd,GETPACKETPOS(cmd,2));

	if (message_size <= 1) // NULL (1) (no void message)
		return;

	message[message_size - 1] = 0; // be sure to have a NULL (hacker can send a no-NULL terminated string)

	gm_message = (char *)aCalloc(message_size + 28, sizeof(char)); // (name) 24 + " : " (3) + message + NULL (1)
	strncpy(gm_message, sd->status.name, 24);
	strcat(gm_message, " : ");
	memcpy(gm_message + strlen(gm_message), message, message_size);

	if (is_atcommand(fd, sd, gm_message, 0) != AtCommand_None) {
		aFree(gm_message);
		return;
	}
	aFree(gm_message);

	// a normal client can not send a wisp message to yourself (anti-hack)
	if (strncmp(RFIFOP(fd,GETPACKETPOS(cmd,1)), sd->status.name, 24) == 0)
		return;

	if (sd->sc_data &&
	    (sd->sc_data[SC_BERSERK].timer != -1 ||	//バーサーク時は会話も不可
	     sd->sc_data[SC_NOCHAT].timer != -1))	//チャット禁止
		return;

	intif_wis_message(sd, RFIFOP(fd,GETPACKETPOS(cmd,1)), message, message_size);

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

	if (message_size <= 1) // NULL (1) (no void message)
		return;

	message[message_size - 1] = 0; // be sure to have a NULL (hacker can send a no-NULL terminated string)

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

	if( sd->npc_id!=0 || sd->vender_id != 0 || sd->deal_mode != 0 || sd->opt1 > 0 || sd->chatID ||
		(sd->sc_data && (sd->sc_data[SC_AUTOCOUNTER].timer!=-1 || //オートカウンター
		sd->sc_data[SC_FORCEWALKING].timer!=-1 ||     //強制移動中拾えない
		sd->sc_data[SC_BLADESTOP].timer!=-1)) ) { //白刃取り
			clif_additem(sd,0,0,6);
			return;
	}
	if(pc_iscloaking(sd) || pc_ischasewalk(sd))
		return;

	bl = map_id2bl(RFIFOL(fd,GETPACKETPOS(cmd,0)));	// map_object_id
	if(bl && bl->type == BL_ITEM)
		fitem = (struct flooritem_data *)bl;

	if(fitem==NULL || fitem->bl.m != sd->bl.m)
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

	nullpo_retv(sd);

	item_index  = RFIFOW(fd,GETPACKETPOS(cmd,0)) - 2;
	item_amount = RFIFOW(fd,GETPACKETPOS(cmd,1));

	if(unit_isdead(&sd->bl)) {
		clif_clearchar_area(&sd->bl,1);
		clif_delitem(sd, item_index, 0);	// クライアントに失敗パケットを送信する必要がある
		return;
	}
	if(sd->sc_data)
		sd->sc_data[SC_ACTION_DELAY].val2++;

	if(sd->sc_data && sd->sc_data[SC_ACTION_DELAY].val2==6)
	{
		printf(msg_txt(47), sd->status.name, sd->status.char_id); // %s様(ID:%d)のアイテムドロップ間隔が異常です\n
	}

	if( sd->npc_id != 0 || sd->vender_id != 0 || sd->deal_mode != 0 || sd->opt1 > 0 ||
		(sd->sc_data && (sd->sc_data[SC_AUTOCOUNTER].timer!=-1 || //オートカウンター
		sd->sc_data[SC_BLADESTOP].timer!=-1 || //白刃取り
		sd->sc_data[SC_FORCEWALKING].timer!=-1  || //強制移動中
		sd->sc_data[SC_BERSERK].timer!=-1   || //バーサーク
		sd->sc_data[SC_ACTION_DELAY].timer!=-1)) )
	{
		clif_delitem(sd, item_index, 0);
		return;
	}
	status_change_start(&sd->bl,SC_ACTION_DELAY,0,0,0,0,300,0);

	if( pc_dropitem(sd, item_index, item_amount) ) {
		if (battle_config.save_player_when_drop_item) {
			/* [Anti-hack] Protection against duplication of items
			   how -> A player drops an item on floor. An other takes the item and disconnects (and the item is saved).
			          If players know a solution to crash server, they crash it. Then, first player can be not saved and they have duplicated.*/
			chrif_save(sd);
			storage_storage_save(sd);
		}
	} else {
		clif_delitem(sd, item_index, 0);
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

	nullpo_retv(sd);

	idx = RFIFOW(fd,GETPACKETPOS(cmd,0)) - 2;
	if (idx < 0 || idx >= MAX_INVENTORY)
		return;

	if(unit_isdead(&sd->bl)) {
		clif_clearchar_area(&sd->bl,1);
		clif_useitemack(sd, idx, sd->status.inventory[idx].amount, 0);
		return;
	}
	if ((sd->npc_id != 0 && sd->npc_allowuseitem != 0 && sd->npc_allowuseitem != sd->status.inventory[idx].nameid) ||
		sd->special_state.item_no_use != 0 || sd->vender_id != 0 || sd->deal_mode != 0 || (sd->opt1 > 0 && sd->opt1 != 6) || sd->state.storage_flag ||
		(sd->sc_data && (sd->sc_data[SC_TRICKDEAD].timer != -1 || //死んだふり
		sd->sc_data[SC_FORCEWALKING].timer!=-1 || //強制移動中
		sd->sc_data[SC_BERSERK].timer!=-1 ||	//バーサーク
		sd->sc_data[SC_FULLBUSTER].timer!=-1 ||	//フルバスター
		sd->sc_data[SC_WEDDING].timer!=-1 ||	//結婚衣装
		sd->sc_data[SC_NOCHAT].timer!=-1 ||//会話禁止
		sd->sc_data[SC_ITEM_DELAY].timer!=-1)) )
	{
		clif_useitemack(sd, idx, sd->status.inventory[idx].amount, 0);
		return;
	}

	if(sd->invincible_timer != -1)
		pc_delinvincibletimer(sd);

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

	if ((sd->npc_id != 0 && sd->npc_allowuseitem != 0 && sd->npc_allowuseitem != sd->status.inventory[idx].nameid)
	    || sd->vender_id != 0 || sd->deal_mode != 0)
		return;
	if (sd->sc_data && (sd->sc_data[SC_BLADESTOP].timer != -1 || sd->sc_data[SC_BERSERK].timer != -1))
		return;

	if (sd->status.inventory[idx].identify != 1) {		// 未鑑定
		clif_equipitemack(sd, idx, 0, 0);	// fail
		return;
	}

	if (sd->status.inventory[idx].attribute != 0) {		// 破壊されている
		clif_equipitemack(sd, idx, 0, 0);	// fail
		return;
	}
	//ペット用装備であるかないか
	if (sd->inventory_data[idx]) {
		if (sd->inventory_data[idx]->type != 8){
			if (sd->inventory_data[idx]->type == 10)
				RFIFOW(fd,GETPACKETPOS(cmd,1))=0x8000;	// 矢を無理やり装備できるように（−−；
			pc_equipitem(sd, idx, RFIFOW(fd,GETPACKETPOS(cmd,1)));
		}
		else
			pet_equipitem(sd, idx);
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

	if (sd->sc_data && (sd->sc_data[SC_BLADESTOP].timer != -1 || sd->sc_data[SC_BERSERK].timer != -1))
		return;
	if (sd->npc_id != 0 || sd->vender_id != 0 || sd->opt1 > 0)
		return;

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
	// 死んでいたり、赤エモの時はNPCをクリックできない
	if(unit_isdead(&sd->bl)) {
		clif_clearchar_area(&sd->bl,1);
		return;
	}
	if(sd->npc_id != 0 || sd->vender_id != 0 || sd->deal_mode != 0 || sd->status.manner < 0)
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
	// 死んでいたり、赤エモの時はNPCをクリックできない
	if(unit_isdead(&sd->bl)) {
		clif_clearchar_area(&sd->bl,1);
		return;
	}
	if(sd->npc_id != 0 || sd->vender_id != 0 || sd->deal_mode != 0 || sd->status.manner < 0)
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

	nullpo_retv(sd);
	// 死んでいたり、赤エモの時はNPCをクリックできない
	if(unit_isdead(&sd->bl)) {
		clif_clearchar_area(&sd->bl,1);
		return;
	}
	if(sd->npc_id != 0 || sd->vender_id != 0 || sd->deal_mode != 0 || sd->status.manner < 0)
		return;

	n = (RFIFOW(fd,GETPACKETPOS(cmd,0)) - 4) /4;
	if (n <= 0) // max is checked in npc_buylist function
		return;

	fail = npc_buylist(sd, n, (unsigned short*)RFIFOP(fd,GETPACKETPOS(cmd,1))); // item_list

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
	// 死んでいたり、赤エモの時はNPCをクリックできない
	if(unit_isdead(&sd->bl)) {
		clif_clearchar_area(&sd->bl,1);
		return;
	}
	if(sd->npc_id != 0 || sd->vender_id != 0 || sd->deal_mode != 0 || sd->status.manner < 0)
		return;

	n = (RFIFOW(fd,GETPACKETPOS(cmd,0))-4) /4;
	if (n <= 0 || n > MAX_INVENTORY) // max is checked in npc_selllist function, but normal clients never send more items than total in inventory
		return;

	fail = npc_selllist(sd, n, (unsigned short*)RFIFOP(fd,GETPACKETPOS(cmd,1))); // item_list

	WFIFOW(fd,0)=0xcb;
	WFIFOB(fd,2)=fail;
	WFIFOSET(fd,packet_db[0xcb].len);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_CreateChatRoom(int fd,struct map_session_data *sd, int cmd)
{
	if(sd->status.manner >= 0 &&
		(battle_config.basic_skill_check == 0 || pc_checkskill(sd,NV_BASIC) >= 4)){
		char *chat_title;
		int len;
		len = (int)RFIFOW(fd,GETPACKETPOS(cmd,0));
		if (len <= GETPACKETPOS(cmd,4))
			return;
		chat_title = (char *)RFIFOP(fd,GETPACKETPOS(cmd,4)); // don't include \0
		if (chat_title[0] == '\0')
			return;
		chat_createchat(sd, RFIFOW(fd,GETPACKETPOS(cmd,1)), RFIFOB(fd,GETPACKETPOS(cmd,2)), (char *)RFIFOP(fd,GETPACKETPOS(cmd,3)), chat_title, len - GETPACKETPOS(cmd,4));
	}
	else
		clif_skill_fail(sd,1,0,3);

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
	chat_changechatowner(sd, (char *)RFIFOP(fd,GETPACKETPOS(cmd,1)));

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_KickFromChat(int fd,struct map_session_data *sd, int cmd)
{
	chat_kickchat(sd, (char *)RFIFOP(fd,GETPACKETPOS(cmd,0)));

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
 * 取引要請を相手に送る
 *------------------------------------------
 */
static void clif_parse_TradeRequest(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	if(map[sd->bl.m].flag.notrade) return;

	if(sd->vender_id != 0 || sd->deal_mode != 0) return;

	if(battle_config.basic_skill_check == 0 || pc_checkskill(sd,NV_BASIC) >= 1){
		trade_traderequest(sd,RFIFOL(sd->fd,GETPACKETPOS(cmd,0)));
	}
	else
		clif_skill_fail(sd,1,0,0);

	return;
}

/*==========================================
 * 取引要請
 *------------------------------------------
 */
static void clif_parse_TradeAck(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	if(map[sd->bl.m].flag.notrade) return;

	trade_tradeack(sd,RFIFOB(sd->fd,GETPACKETPOS(cmd,0)));

	return;
}

/*==========================================
 * アイテム追加
 *------------------------------------------
 */
static void clif_parse_TradeAddItem(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	trade_tradeadditem(sd,RFIFOW(sd->fd,GETPACKETPOS(cmd,0)),RFIFOL(sd->fd,GETPACKETPOS(cmd,1)));

	return;
}

/*==========================================
 * アイテム追加完了(ok押し)
 *------------------------------------------
 */
static void clif_parse_TradeOk(int fd,struct map_session_data *sd, int cmd)
{
	trade_tradeok(sd);

	return;
}

/*==========================================
 * 取引キャンセル
 *------------------------------------------
 */
static void clif_parse_TradeCancel(int fd,struct map_session_data *sd, int cmd)
{
	trade_tradecancel(sd);

	return;
}

/*==========================================
 * 取引許諾(trade押し)
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
	unit_stopattack(&sd->bl);

	return;
}

/*==========================================
 * カートへアイテムを移す
 *------------------------------------------
 */
static void clif_parse_PutItemToCart(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	if (sd->npc_id != 0 || sd->vender_id != 0 || sd->deal_mode != 0 || pc_iscarton(sd) == 0)
		return;
	pc_putitemtocart(sd,RFIFOW(fd,GETPACKETPOS(cmd,0))-2,RFIFOL(fd,GETPACKETPOS(cmd,1)));

	return;
}
/*==========================================
 * カートからアイテムを出す
 *------------------------------------------
 */
static void clif_parse_GetItemFromCart(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	if (sd->npc_id != 0 || sd->vender_id != 0 || sd->deal_mode != 0 || pc_iscarton(sd) == 0)
		return;
	pc_getitemfromcart(sd,RFIFOW(fd,GETPACKETPOS(cmd,0))-2,RFIFOL(fd,GETPACKETPOS(cmd,1)));

	return;
}

/*==========================================
 * 付属品(鷹,ペコ,カート)をはずす
 *------------------------------------------
 */
static void clif_parse_RemoveOption(int fd,struct map_session_data *sd, int cmd)
{
	if (sd->npc_id != 0 || sd->vender_id != 0 || sd->deal_mode != 0)
		return;
	pc_setoption(sd,0);

	return;
}

/*==========================================
 * チェンジカート
 *------------------------------------------
 */
static void clif_parse_ChangeCart(int fd,struct map_session_data *sd, int cmd)
{
	pc_setcart(sd, RFIFOW(fd,GETPACKETPOS(cmd,0)));

	return;
}

/*==========================================
 * ステータスアップ
 *------------------------------------------
 */
static void clif_parse_StatusUp(int fd,struct map_session_data *sd, int cmd)
{

	// Is amount RFIFOB(fd,GETPACKETPOS(cmd,1)) always 1?
	pc_statusup(sd, RFIFOW(fd,GETPACKETPOS(cmd,0)));

	return;
}

/*==========================================
 * スキルレベルアップ
 *------------------------------------------
 */
static void clif_parse_SkillUp(int fd,struct map_session_data *sd, int cmd)
{
	int skill_num = RFIFOW(fd,GETPACKETPOS(cmd,0));

	if( skill_num>=10000 )				// ギルドスキル
		guild_skillup(sd,skill_num,0);
	else if( skill_num>=HOM_SKILLID )	// ホムンクルススキル
		homun_skillup(sd,skill_num);
	else
		pc_skillup(sd,skill_num);

	return;
}

/*==========================================
 * スキル使用（ID指定）
 *------------------------------------------
 */
static void clif_parse_UseSkillToId(int fd,struct map_session_data *sd, int cmd)
{
	int skillnum,skilllv,lv,target_id;
	unsigned int tick=gettick();
	struct block_list *bl;
	short *option;

	nullpo_retv(sd);

	if(map[sd->bl.m].flag.noskill) return;
	if(sd->npc_id!=0 || sd->vender_id != 0) return;
	if(sd->chatID) return;

	if (pc_issit(sd))
		return;

	skilllv = RFIFOW(fd,GETPACKETPOS(cmd,0));
	skillnum = RFIFOW(fd,GETPACKETPOS(cmd,1));
	target_id = RFIFOL(fd,GETPACKETPOS(cmd,2));

	// decode for jRO 2005-05-09dRagexe
	if( packet_db[cmd].pos[0]==0 && packet_db[cmd].pos[1]==0 && packet_db[cmd].pos[2]==0)
	{
		int tmp = g_packet_len % 3;
		static const int t1[]={ 138,43,170 }, t2[]={ 103,4,80 }, t3[]={ 130,33,84 }, t4[]={ 134, 39, 166 };
		int tmp2 = (g_packet_len - t1[tmp]) / 3;
		skilllv  = RFIFOW(fd, tmp2   + t2[tmp] );
		skillnum = RFIFOW(fd, tmp2*2 + t3[tmp] );
		target_id= RFIFOL(fd, tmp2*3 + t4[tmp] );
	}
	// end decode

	if (skillnum >= GD_SKILLBASE) {
		//ギルドスキルはギルマスのみ
		if (sd != guild_get_guildmaster_sd(guild_search(sd->status.guild_id)))
			return;
		//ギルドスキルのデコードがおかしい！
		//わかる人頼みます
		skilllv = pc_checkskill(sd, skillnum);
	}

	bl = map_id2bl(target_id);
	if(bl == NULL)
		return;

	//ホムスキル
	if(skillnum >= HOM_SKILLID && skillnum < MAX_HOM_SKILLID)
	{
		struct homun_data *hd = sd->hd;
		if( hd && (lv = homun_checkskill(hd,skillnum)) ) {
			if(skilllv > lv)
				skilllv = lv;
			if(hd->ud.skilltimer != -1) {
				if(skillnum != SA_CASTCANCEL)
					return;
			}
			else if(DIFF_TICK(tick, hd->ud.canact_tick) < 0)
				return;
			if(DIFF_TICK(tick, hd->homskillstatictimer[skillnum-HOM_SKILLID]) < 0)
				return;

			if(skill_get_inf(skillnum)==4)	//自分が対象
				unit_skilluse_id(&hd->bl,hd->bl.id,skillnum,skilllv);
			else
				unit_skilluse_id(&hd->bl,target_id,skillnum,skilllv);
			return;
		}
	}

	if(bl && mob_gvmobcheck(sd,bl)==0)
		return;

	if(sd->ud.skilltimer != -1) {
		if(skillnum != SA_CASTCANCEL)
			return;
	}
	else if(DIFF_TICK(tick, sd->ud.canact_tick) < 0) {
		clif_skill_fail(sd,skillnum,4,0);
		return;
	}

	// 通常スキルの場合はstatic timerの判定
	if(skillnum >= 0 && skillnum < MAX_SKILL_ID) {
		if(DIFF_TICK(tick, sd->skillstatictimer[skillnum]) < 0) {
			clif_skill_fail(sd,skillnum,4,0);
			return;
		}
	}

	if((sd->sc_data[SC_TRICKDEAD].timer != -1 && skillnum != NV_TRICKDEAD) ||
		sd->sc_data[SC_BERSERK].timer!=-1 ||
		sd->sc_data[SC_NOCHAT].timer!=-1 ||
		sd->sc_data[SC_WEDDING].timer!=-1||
		sd->sc_data[SC_FORCEWALKING].timer!=-1
		) return;


	if((option = status_get_option(bl)) != NULL && *option&0x4006 && ((&sd->bl)!=bl))
	{
		//昆虫と悪魔は攻撃可能？
		if(sd->race!=4 && sd->race!=6)
			return;
	}

	if (sd->sc_data[SC_BASILICA].timer!=-1 && (skillnum!=HP_BASILICA ||
			sd->sc_data[SC_BASILICA].val2!=sd->bl.id))
		return;
	if (sd->sc_data[SC_GOSPEL].timer!=-1 && (skillnum!=PA_GOSPEL ||
			sd->sc_data[SC_GOSPEL].val2!=sd->bl.id))
		return;

	if(sd->invincible_timer != -1)
		pc_delinvincibletimer(sd);

	if(sd->skillitem >= 0 && sd->skillitem == skillnum) {
		if(skilllv != sd->skillitemlv)
			skilllv = sd->skillitemlv;
		if( !unit_skilluse_id(&sd->bl,target_id,skillnum,skilllv) ) {
			sd->skillitem = -1;
			sd->skillitemlv = -1;
			sd->skillitem_flag = 0;
		}
	}
	else {
		sd->skillitem = -1;
		sd->skillitemlv = -1;
		sd->skillitem_flag = 0;
		if(skillnum == MO_EXTREMITYFIST) {
			if(sd->sc_data[SC_COMBO].timer == -1 || (sd->sc_data[SC_COMBO].val1 != MO_COMBOFINISH && sd->sc_data[SC_COMBO].val1 != CH_CHAINCRUSH)) {
				if(!sd->state.skill_flag ) {
					sd->state.skill_flag = 1;
					clif_skillinfo(sd,MO_EXTREMITYFIST,1,-1);
					return;
				}
				else if(sd->bl.id == target_id) {
					clif_skillinfo(sd,MO_EXTREMITYFIST,1,-1);
					return;
				}
			}
		}
		if(skillnum == TK_JUMPKICK) {
			if(sd->sc_data[SC_DODGE_DELAY].timer == -1) {
				if(!sd->state.skill_flag ) {
					sd->state.skill_flag = 1;
					clif_skillinfo(sd,TK_JUMPKICK,1,-1);
					return;
				}
				else if(sd->bl.id == target_id) {
					clif_skillinfo(sd,TK_JUMPKICK,1,-1);
					return;
				}
			}
		}
		if( (lv = pc_checkskill(sd,skillnum)) > 0) {
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
 * スキル使用（場所指定）
 *------------------------------------------
 */
static void clif_parse_UseSkillToPos(int fd,struct map_session_data *sd, int cmd)
{
	int skillnum,skilllv,lv,x,y;
	unsigned int tick=gettick();

	nullpo_retv(sd);

	if(map[sd->bl.m].flag.noskill) return;
	if(sd->npc_id!=0 || sd->vender_id != 0) return;
	if(sd->chatID) return;

	skilllv = RFIFOW(fd,GETPACKETPOS(cmd,0));
	skillnum = RFIFOW(fd,GETPACKETPOS(cmd,1));
	x = RFIFOW(fd,GETPACKETPOS(cmd,2));
	y = RFIFOW(fd,GETPACKETPOS(cmd,3));

	if(sd->ud.skilltimer != -1)
		return;

	if(DIFF_TICK(tick, sd->ud.canact_tick) < 0) {
		clif_skill_fail(sd,skillnum,4,0);
		return;
	}
	// 通常スキルの場合はstatic timerの判定
	if(skillnum >= 0 && skillnum < MAX_SKILL_ID) {
		if(DIFF_TICK(tick, sd->skillstatictimer[skillnum]) < 0) {
			clif_skill_fail(sd,skillnum,4,0);
			return;
		}
	}

	if(GETPACKETPOS(cmd,4)){
		if(pc_issit(sd)){
			clif_skill_fail(sd,skillnum,0,0);
			return;
		}
		memcpy(sd->message,RFIFOP(fd,GETPACKETPOS(cmd,4)),80);
		sd->message[79] = '\0'; // message includes NULL, but add it against hacker
	}
	else if (pc_issit(sd)){
		return;
	}

	if((sd->sc_data[SC_TRICKDEAD].timer != -1 && skillnum != NV_TRICKDEAD) ||
		sd->sc_data[SC_BERSERK].timer!=-1 ||
		sd->sc_data[SC_NOCHAT].timer!=-1 ||
		sd->sc_data[SC_WEDDING].timer!=-1 ||
		sd->sc_data[SC_GOSPEL].timer!=-1||
		sd->sc_data[SC_FORCEWALKING].timer!=-1
		)
		return;
	if (sd->sc_data[SC_BASILICA].timer!=-1 && (skillnum!=HP_BASILICA ||
			sd->sc_data[SC_BASILICA].val2!=sd->bl.id))
		return;

	if(sd->invincible_timer != -1)
		pc_delinvincibletimer(sd);

	if(sd->skillitem >= 0 && sd->skillitem == skillnum) {
		if(skilllv != sd->skillitemlv)
			skilllv = sd->skillitemlv;
		if( !unit_skilluse_pos(&sd->bl,x,y,skillnum,skilllv) ) {
			sd->skillitem = -1;
			sd->skillitemlv = -1;
			sd->skillitem_flag = 0;
		}
	}
	else {
		sd->skillitem = -1;
		sd->skillitemlv = -1;
		sd->skillitem_flag = 0;
		if( (lv = pc_checkskill(sd,skillnum)) > 0) {
			if(skilllv > lv)
				skilllv = lv;
			unit_skilluse_pos(&sd->bl,x,y,skillnum,skilllv);
		}
	}

	return;
}

/*==========================================
 * スキル使用（map指定）
 *------------------------------------------
 */
static void clif_parse_UseSkillMap(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	if(map[sd->bl.m].flag.noskill) return;
	if(sd->chatID) return;

	if(sd->npc_id!=0 || sd->vender_id != 0 || (sd->sc_data &&
		(sd->sc_data[SC_TRICKDEAD].timer != -1 ||
		sd->sc_data[SC_BERSERK].timer!=-1 ||
		sd->sc_data[SC_NOCHAT].timer!=-1 ||
		sd->sc_data[SC_WEDDING].timer!=-1 ||
		sd->sc_data[SC_BASILICA].timer!=-1 ||
		sd->sc_data[SC_GOSPEL].timer!=-1||
		sd->sc_data[SC_FORCEWALKING].timer!=-1)))
		return;

	if(sd->invincible_timer != -1)
		pc_delinvincibletimer(sd);

	RFIFOB(fd,GETPACKETPOS(cmd,1)+15) = '\0'; // be sure to have NULL
	skill_castend_map(sd,RFIFOW(fd,GETPACKETPOS(cmd,0)),RFIFOP(fd,GETPACKETPOS(cmd,1)));

	return;
}

/*==========================================
 * メモ要求
 *------------------------------------------
 */
static void clif_parse_RequestMemo(int fd,struct map_session_data *sd, int cmd)
{
	pc_memo(sd,-1);

	return;
}

/*==========================================
 * アイテム合成
 *------------------------------------------
 */
static void clif_parse_ProduceMix(int fd,struct map_session_data *sd, int cmd)
{
	int nameid, slot1, slot2, slot3;

	nullpo_retv(sd);

	sd->state.produce_flag = 0;

	nameid = RFIFOW(fd,GETPACKETPOS(cmd,0));
	slot1  = RFIFOW(fd,GETPACKETPOS(cmd,1));
	slot2  = RFIFOW(fd,GETPACKETPOS(cmd,2));
	slot3  = RFIFOW(fd,GETPACKETPOS(cmd,3));

	skill_produce_mix(sd,nameid,slot1,slot2,slot3);

	return;
}

/*==========================================
 * 武器修理
 *------------------------------------------
 */
static void clif_parse_RepairItem(int fd,struct map_session_data *sd, int cmd)
{
	int idx, itemid = 0;

	nullpo_retv(sd);

	idx = RFIFOW(fd,GETPACKETPOS(cmd,0));
	if (idx != 0xFFFF && (idx < 0 || idx >= MAX_INVENTORY)) // invalid range
		return;

	sd->state.produce_flag = 0;
	if (idx != 0xFFFF && (itemid = skill_repair_weapon(sd, idx)) > 0)
		clif_item_repaireffect(sd,0,itemid);
	else
		clif_item_repaireffect(sd,1,itemid);

	return;
}

/*==========================================
 * 武器精錬
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
	RFIFOB(fd,len - 1) = '\0';

	if (len - (int)GETPACKETPOS(cmd,2) >= sizeof(sd->npc_str)) { // message includes NULL
		//printf("clif: input string too long !\n"); // no display, it's not an error, just a check against overflow (and hacker)
		memcpy(sd->npc_str, RFIFOP(fd,GETPACKETPOS(cmd,2)), sizeof(sd->npc_str));
	}else
		strncpy(sd->npc_str, RFIFOP(fd,GETPACKETPOS(cmd,2)), sizeof(sd->npc_str));
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
 * アイテム鑑定
 *------------------------------------------
 */
static void clif_parse_ItemIdentify(int fd,struct map_session_data *sd, int cmd)
{
	pc_item_identify(sd,RFIFOW(fd,GETPACKETPOS(cmd,0))-2);

	return;
}

/*==========================================
 * 矢作成
 *------------------------------------------
 */
static void clif_parse_SelectArrow(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	sd->state.make_arrow_flag = 0;
	skill_arrow_create(sd,RFIFOW(fd,GETPACKETPOS(cmd,0)));

	return;
}

/*==========================================
 * オートスペル受信
 *------------------------------------------
 */
static void clif_parse_AutoSpell(int fd,struct map_session_data *sd, int cmd)
{
	skill_autospell(sd,RFIFOW(fd,GETPACKETPOS(cmd,0)));

	return;
}

/*==========================================
 * カード使用
 *------------------------------------------
 */
static void clif_parse_UseCard(int fd,struct map_session_data *sd, int cmd)
{
	clif_use_card(sd,RFIFOW(fd,GETPACKETPOS(cmd,0))-2);

	return;
}

/*==========================================
 * カード挿入装備選択
 *------------------------------------------
 */
static void clif_parse_InsertCard(int fd,struct map_session_data *sd, int cmd)
{
	int idx;

	nullpo_retv(sd);

	idx = RFIFOW(fd,GETPACKETPOS(cmd,0)) - 2;
	if (idx < 0 || idx >= MAX_INVENTORY)
		return;

	if ((sd->npc_id != 0 && sd->npc_allowuseitem != 0 && sd->npc_allowuseitem != sd->status.inventory[idx].nameid) || unit_isdead(&sd->bl) ||
		sd->vender_id != 0 || sd->deal_mode != 0 || (sd->opt1 > 0 && sd->opt1 != 6) ||
		(sd->sc_data && (sd->sc_data[SC_TRICKDEAD].timer != -1 || //死んだふり
		sd->sc_data[SC_BLADESTOP].timer!=-1 ||	//白刃取り
		sd->sc_data[SC_FORCEWALKING].timer!=-1 ||
		sd->sc_data[SC_BERSERK].timer!=-1 ||	//バーサーク
		sd->sc_data[SC_WEDDING].timer!=-1 ||	//結婚衣装
		sd->sc_data[SC_NOCHAT].timer!=-1 )) )	//会話禁止
	{
		return;
	}
	pc_insert_card(sd, idx, RFIFOW(fd,GETPACKETPOS(cmd,1))-2);

	return;
}

/*==========================================
 * 0193 キャラID名前引き
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
	if (battle_config.atc_gmonly == 0 ||
		pc_isGM(sd) >= get_atcommand_level(AtCommand_ResetState)) {
		switch(RFIFOW(fd,GETPACKETPOS(cmd,0))){
		case 0:
			pc_resetstate(sd);
			break;
		case 1:
			pc_resetskill(sd);
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
	if (message_size <= 0) // must have at least \0
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
 * カプラ倉庫へ入れる
 *------------------------------------------
 */
static void clif_parse_MoveToKafra(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	if(sd->npc_id != 0 || sd->vender_id != 0 || sd->deal_mode != 0 || sd->sc_data[SC_BERSERK].timer != -1)
		return;

	if(sd->state.storage_flag==2)
		storage_guild_storageadd(sd, RFIFOW(fd,GETPACKETPOS(cmd,0))-2, RFIFOW(fd,GETPACKETPOS(cmd,1)));	// item_index, item_amount
	else if(sd->state.storage_flag==1)
		storage_storageadd(sd, RFIFOW(fd,GETPACKETPOS(cmd,0))-2, RFIFOW(fd,GETPACKETPOS(cmd,1)));	// item_index, item_amount

	return;
}

/*==========================================
 * カプラ倉庫から出す
 *------------------------------------------
 */
static void clif_parse_MoveFromKafra(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	if(sd->npc_id != 0 || sd->vender_id != 0 || sd->deal_mode != 0 || sd->sc_data[SC_BERSERK].timer != -1)
		return;

	if(sd->state.storage_flag==2)
		storage_guild_storageget(sd, RFIFOW(fd,GETPACKETPOS(cmd,0))-1, RFIFOL(fd,GETPACKETPOS(cmd,1))); // item_index, item_amount
	else if(sd->state.storage_flag==1)
		storage_storageget(sd, RFIFOW(fd,GETPACKETPOS(cmd,0))-1, RFIFOL(fd,GETPACKETPOS(cmd,1))); 	// item_index, item_amount

	return;
}

/*==========================================
 * カプラ倉庫へカートから入れる
 *------------------------------------------
 */
static void clif_parse_MoveToKafraFromCart(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	if(sd->npc_id != 0 || sd->vender_id != 0 || sd->deal_mode != 0 || pc_iscarton(sd) == 0 || sd->sc_data[SC_BERSERK].timer != -1)
		return;

	if(sd->state.storage_flag==2)
		storage_guild_storageaddfromcart(sd, RFIFOW(fd,GETPACKETPOS(cmd,0))-2, RFIFOL(fd,GETPACKETPOS(cmd,1))); // item_index, item_amount
	else if(sd->state.storage_flag==1)
		storage_storageaddfromcart(sd, RFIFOW(fd,GETPACKETPOS(cmd,0))-2, RFIFOL(fd,GETPACKETPOS(cmd,1))); 	// item_index, item_amount

	return;
}

/*==========================================
 * カプラ倉庫からカートへ出す
 *------------------------------------------
 */
static void clif_parse_MoveFromKafraToCart(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	if(sd->npc_id != 0 || sd->vender_id != 0 || sd->deal_mode != 0 || pc_iscarton(sd) == 0 || sd->sc_data[SC_BERSERK].timer != -1)
		return;

	if(sd->state.storage_flag==2)
		storage_guild_storagegettocart(sd, RFIFOW(fd,GETPACKETPOS(cmd,0))-1, RFIFOL(fd,GETPACKETPOS(cmd,1)));	// item_index, item_amount
	else if(sd->state.storage_flag==1)
		storage_storagegettocart(sd, RFIFOW(fd,GETPACKETPOS(cmd,0))-1, RFIFOL(fd,GETPACKETPOS(cmd,1))); 	// item_index, item_amount

	return;
}

/*==========================================
 * カプラ倉庫を閉じる
 *------------------------------------------
 */
static void clif_parse_CloseKafra(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	if(sd->state.storage_flag==2)
		storage_guild_storageclose(sd);
	else if(sd->state.storage_flag==1)
		storage_storageclose(sd);
	else
		clif_storageclose(sd);

	return;
}

/*==========================================
 * パーティを作る
 *------------------------------------------
 */
static void clif_parse_CreateParty(int fd,struct map_session_data *sd, int cmd)
{
	// アイテム分配未対応
	//int item1 = RFIFOP(fd,GETPACKETPOS(cmd,1));
	//int item2 = RFIFOP(fd,GETPACKETPOS(cmd,2));

	if(battle_config.basic_skill_check == 0 || pc_checkskill(sd,NV_BASIC) >= 7){
		party_create(sd,RFIFOP(fd,GETPACKETPOS(cmd,0)));
	}
	else
		clif_skill_fail(sd,1,0,4);

	return;
}

/*==========================================
 * パーティを作る
 *------------------------------------------
 */
static void clif_parse_CreateParty2(int fd,struct map_session_data *sd, int cmd)
{
	if(battle_config.basic_skill_check == 0 || pc_checkskill(sd,NV_BASIC) >= 7){
		party_create(sd,RFIFOP(fd,GETPACKETPOS(cmd,0)));
	}
	else
		clif_skill_fail(sd,1,0,4);

	return;
}

/*==========================================
 * パーティに勧誘
 *------------------------------------------
 */
static void clif_parse_PartyInvite(int fd,struct map_session_data *sd, int cmd)
{
	party_invite(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)));

	return;
}

/*==========================================
 * パーティ勧誘返答
 *------------------------------------------
 */
static void clif_parse_ReplyPartyInvite(int fd,struct map_session_data *sd, int cmd)
{
	if(battle_config.basic_skill_check == 0 || pc_checkskill(sd,NV_BASIC) >= 5){
		party_reply_invite(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)),RFIFOL(fd,GETPACKETPOS(cmd,1)));
	}
	else {
		party_reply_invite(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)),-1);
		clif_skill_fail(sd,1,0,4);
	}

	return;
}

/*==========================================
 * パーティ脱退要求
 *------------------------------------------
 */
static void clif_parse_LeaveParty(int fd,struct map_session_data *sd, int cmd)
{
	party_leave(sd);

	return;
}

/*==========================================
 * パーティ除名要求
 *------------------------------------------
 */
static void clif_parse_RemovePartyMember(int fd,struct map_session_data *sd, int cmd)
{
	party_removemember(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)),RFIFOP(fd,GETPACKETPOS(cmd,1)));

	return;
}

/*==========================================
 * パーティ設定変更要求
 *------------------------------------------
 */
static void clif_parse_PartyChangeOption(int fd,struct map_session_data *sd, int cmd)
{
	party_changeoption(sd,RFIFOW(fd,GETPACKETPOS(cmd,0)),RFIFOW(fd,GETPACKETPOS(cmd,1)));

	return;
}

/*==========================================
 * パーティメッセージ送信要求
 *------------------------------------------
 */
static void clif_parse_PartyMessage(int fd,struct map_session_data *sd, int cmd)
{
	char *message;
	int message_size;

	nullpo_retv(sd);

	message = (char *)RFIFOP(fd, GETPACKETPOS(cmd,1));
	message_size = RFIFOW(fd, GETPACKETPOS(cmd,0)) - GETPACKETPOS(cmd,1);

	if (message_size <= 0) // against hack
		return;
	// normal client send NULL -> force it (against hacker)
	message[message_size - 1] = '\0';

	if (battle_config.check_player_name_party_msg) {
		// structure of message: <player_name> : <message>
		char *p_message;
		int name_length;
		name_length = strlen(sd->status.name);
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

	if (is_atcommand(fd, sd, message, 0) != AtCommand_None)
		return;

	if(sd->sc_data &&
	   (sd->sc_data[SC_BERSERK].timer != -1 ||	//バーサーク時は会話も不可
	    sd->sc_data[SC_NOCHAT].timer != -1))		//チャット禁止
		return;

	party_send_message(sd, message, message_size);

	return;
}

/*==========================================
 * 露店閉鎖
 *------------------------------------------
 */
static void clif_parse_CloseVending(int fd,struct map_session_data *sd, int cmd)
{
	vending_closevending(sd);

	return;
}

/*==========================================
 * 露店アイテムリスト要求
 *------------------------------------------
 */
static void clif_parse_VendingListReq(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	vending_vendinglistreq(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)));
	if(sd->npc_id)
		npc_event_dequeue(sd);

	return;
}

/*==========================================
 * 露店アイテム購入
 *------------------------------------------
 */
static void clif_parse_PurchaseReq(int fd,struct map_session_data *sd, int cmd)
{
	vending_purchasereq(sd,RFIFOW(fd,GETPACKETPOS(cmd,0)),RFIFOL(fd,GETPACKETPOS(cmd,1)),RFIFOP(fd,GETPACKETPOS(cmd,2)));

	return;
}

/*==========================================
 * 露店開設
 *------------------------------------------
 */
static void clif_parse_OpenVending(int fd,struct map_session_data *sd, int cmd)
{
	vending_openvending(sd, RFIFOW(fd,GETPACKETPOS(cmd,0)), RFIFOP(fd,GETPACKETPOS(cmd,1)), RFIFOB(fd,GETPACKETPOS(cmd,2)), RFIFOP(fd,GETPACKETPOS(cmd,3)));

	return;
}

/*==========================================
 * ギルドを作る
 *------------------------------------------
 */
static void clif_parse_CreateGuild(int fd,struct map_session_data *sd, int cmd)
{
	guild_create(sd,RFIFOP(fd,GETPACKETPOS(cmd,0)));

	return;
}

/*==========================================
 * ギルドマスターかどうか確認
 *------------------------------------------
 */
static void clif_parse_GuildCheckMaster(int fd,struct map_session_data *sd, int cmd)
{
	clif_guild_masterormember(sd);

	return;
}

/*==========================================
 * ギルド情報要求
 *------------------------------------------
 */
static void clif_parse_GuildRequestInfo(int fd,struct map_session_data *sd, int cmd)
{
	struct guild *g;

	// only a guild member can ask for guild info
	if(sd->status.guild_id == 0 || (g = guild_search(sd->status.guild_id)) == NULL)
		return;

	switch(RFIFOL(fd,GETPACKETPOS(cmd,0))){
	case 0:	// ギルド基本情報、同盟敵対情報
		clif_guild_basicinfo(sd, g);
		clif_guild_allianceinfo(sd, g);
		break;
	case 1:	// メンバーリスト、役職名リスト
		clif_guild_positionnamelist(sd, g);
		clif_guild_memberlist(sd, g);
		break;
	case 2:	// 役職名リスト、役職情報リスト
		clif_guild_positionnamelist(sd, g);
		clif_guild_positioninfolist(sd, g);
		break;
	case 3:	// スキルリスト
		clif_guild_skillinfo(sd, g);
		break;
	case 4:	// 追放リスト
		clif_guild_explusionlist(sd, g);
		break;
	default:
		if(battle_config.error_log)
			printf("clif: guild request info: unknown type %d\n", RFIFOL(fd,GETPACKETPOS(cmd,0)));
		break;
	}

	return;
}

/*==========================================
 * ギルド役職変更
 *------------------------------------------
 */
static void clif_parse_GuildChangePositionInfo(int fd,struct map_session_data *sd, int cmd)
{
	struct guild *g;
	int i;

	// only guild master can change position.
	if (sd->status.guild_id == 0 || (g = guild_search(sd->status.guild_id)) == NULL)
		return;
	if (strcmp(sd->status.name, g->master))
		return;

	for(i=4;i<RFIFOW(fd,GETPACKETPOS(cmd,0));i+=40){ // {<index>.l <mode>.l <index>.l <exp_mode>.l <nickname>.24B}.40B*
		guild_change_position(sd->status.guild_id, RFIFOL(fd,i), RFIFOL(fd,i+4), RFIFOL(fd,i+12), RFIFOP(fd,i+16));
	}

	return;
}

/*==========================================
 * ギルドメンバ役職変更
 *------------------------------------------
 */
static void clif_parse_GuildChangeMemberPosition(int fd,struct map_session_data *sd, int cmd)
{
	int i;
	struct guild *g;

	nullpo_retv(sd);

	// only guild master can change a member position
	if (sd->status.guild_id == 0 || (g = guild_search(sd->status.guild_id)) == NULL)
		return;
	if (strcmp(sd->status.name, g->master))
		return;

	for(i=4;i<RFIFOW(fd,GETPACKETPOS(cmd,0));i+=12){ // {<accID>.l <charaID>.l <index>.l}.12B*
		guild_change_memberposition(sd->status.guild_id, RFIFOL(fd,i), RFIFOL(fd,i+4), RFIFOL(fd,i+8));
	}

	return;
}

/*==========================================
 * ギルドエンブレム要求
 *------------------------------------------
 */
static void clif_parse_GuildRequestEmblem(int fd,struct map_session_data *sd, int cmd)
{
	struct guild *g=guild_search(RFIFOL(fd,GETPACKETPOS(cmd,0)));

	if(g!=NULL)
		clif_guild_emblem(sd,g);

	return;
}

/*==========================================
 * ギルドエンブレム変更
 *------------------------------------------
 */
static void clif_parse_GuildChangeEmblem(int fd,struct map_session_data *sd, int cmd)
{
	struct guild *g;
	int zipbitmap_len, bitmap_offset;
	char dest_bitmap[4100]; // max possible (16/24 bits): 4086 (windows)-> (header1)14 + (header2)40 + (576 colors)2304 + (bitmap:24x24)1728 (no compression with palette)
	unsigned long dest_bitmap_len;
	int ncol;

	// only guild master can change emblem.
	if (sd->status.guild_id == 0 || (g = guild_search(sd->status.guild_id)) == NULL)
		return;
	if (strcmp(sd->status.name, g->master))
		return;

	// length of zipbitmap (client doesn't send bmp structure, but a zipped BMP)
	bitmap_offset = (int)GETPACKETPOS(cmd,1);
	zipbitmap_len = (int)RFIFOW(fd,GETPACKETPOS(cmd,0)) - bitmap_offset;
	if (zipbitmap_len < 0 || zipbitmap_len > 2000)
		return;

	// analyse of bmp
	dest_bitmap_len = sizeof(dest_bitmap);
	if (decode_zip(dest_bitmap, &dest_bitmap_len, RFIFOP(fd, bitmap_offset), zipbitmap_len) != 0) { // Z_OK = 0
		return;
	}
	if (dest_bitmap_len < 14 + 40) { // strict minimum -> windows: header1(14) header2(40), os/2 v1 header1(14) header2(12) 256colors(768)
		return;
	}

	/*Structure BITMAPFILEHEADER (14 bytes)
	bfType       Word  (2 bytes)  0 Magic identifier (should be 'BM'=0x4D 0x4E)
	bfSize       Dword (4 bytes)  2 File size in bytes
	bfReserved1  Word  (2 bytes)  6 always 0
	bfReserved2  Word  (2 bytes)  8 always 0
	bfOffBits    Dword (4 bytes) 10 Offset to image data, bytes*/
	if(strncmp(dest_bitmap, "BM", 2) != 0 ||
	   RBUFL(dest_bitmap, 2) != dest_bitmap_len ||
	   RBUFW(dest_bitmap, 6) != 0 ||
	   RBUFW(dest_bitmap, 8) != 0) {
		// check of Offset is done with colors.
		return;
	}

	// Structure BITMAPINFOHEADER (40 bytes: Windows 3.1x, 95, NT, ..., 12 bytes: OS/2 1.x, 64 bytes: OS/2 2.x, ?? bytes: OS/2 3.x)
	switch(RBUFL(dest_bitmap, 14)) {
	case 40: // windows version
		/*biSize           DWord (4 bytes) 14 Header size in bytes (must be: 40)
			biWidth          Dword (4 bytes) 18 Width of image
			biHeight         Dword (4 bytes) 22 Height of image
			biPlanes         Word  (2 bytes) 26 Number of colour planes (always 1)
			biBitCount       Word  (2 bytes) 28 Bits per pixel (1, 4, 8, 16, 24 or 32)
			biCompression    Dword (4 bytes) 30 Compression type (0 - no compression, 1 - 8 bit run length encoding, 2 - 4 bit run length encoding, 3 - RGB bitmap with mask)
			biSizeImage      Dword (4 bytes) 34 Image size in bytes (usefull for compression)
			biXpelsPerMeter  Dword (4 bytes) 38 Pixels per meter
			biYpelsPerMeter  Dword (4 bytes) 42 Pixels per meter
			biClrUsed        Dword (4 bytes) 46 Number of used colours (number of colors in palette)
			biClrImportant   Dword (4 bytes) 50 Number of important colours (0: all)*/
		if (RBUFL(dest_bitmap, 18) != 24 || // ragnarok condition
		    RBUFL(dest_bitmap, 22) != 24 || // ragnarok condition
		    RBUFW(dest_bitmap, 26) != 1 ||
		    // number of colors is checked after
		    (RBUFL(dest_bitmap, 30) != 0 && RBUFL(dest_bitmap, 30) != 1 && RBUFL(dest_bitmap, 30) != 2 && RBUFL(dest_bitmap, 30) != 3)) {
			return;
		}
		/* color structure (8 bits, always exist)
		Windows RGBQUAD color map entry
		0       rgbBlue     (1 bytes)  Blue value for color map entry.
		1       rgbGreen    (1 bytes)  Green value for color map entry.
		2       rgbRed      (1 bytes)  Red value for color map entry.
		3       rgbReserved (1 bytes)  Zero*/
		if (RBUFL(dest_bitmap, 28) == 8) { // 256 colors (ragnarok condition)
			ncol = (RBUFL(dest_bitmap, 10) - 54) / 4; // compute number of colors recorded
			// check offset of bitmap and number of colors
			if (ncol > 256 || // 8 bits colored bitmap, used colors must be at maximum 256
			    (RBUFL(dest_bitmap, 46) == 0 && ncol != 256) || // biClrUsed not used
			    (RBUFL(dest_bitmap, 46) != 0 && ncol != RBUFL(dest_bitmap, 46))) { // biClrUsed used
				return;
			}
			// check size of file (when no compression)
			if (RBUFL(dest_bitmap, 10) < 14 + 40 + ncol * 4 || // check minimum position of bitmap data
			    (RBUFL(dest_bitmap, 30) == 0 && (dest_bitmap_len < 14 + 40 + ncol * 4 + 576 || // no compression (check minimum)
			                                     dest_bitmap_len - RBUFL(dest_bitmap, 10) < 576)) ||
			    (RBUFL(dest_bitmap, 30) != 0 && dest_bitmap_len <= 14 + 40 + ncol * 4)) { // with compression (check minimum)
				return;
			}
		// 16-24 bits colors (Additional ragnarok conditions)
		} else if (((battle_config.guild_emblem_colors & 1) == 1 && RBUFL(dest_bitmap, 28) == 16) ||
		           ((battle_config.guild_emblem_colors & 2) == 2 && RBUFL(dest_bitmap, 28) == 24)) {
			ncol = RBUFL(dest_bitmap, 46); // compute number of colors recorded (could be 0 if not important colors)
			// check offset of bitmap and number of colors
			if (ncol > 576) { // can not have more colors than number of used pixels
				return;
			}
			// check size of file (when no compression)
			if (RBUFL(dest_bitmap, 10) < 14 + 40 + ncol * 4 || // check minimum position of bitmap data
			    (RBUFL(dest_bitmap, 30) == 0 && (dest_bitmap_len < 14 + 40 + ncol * 4 + 576 * 3 || // no compression (check minimum)
			                                     dest_bitmap_len - RBUFL(dest_bitmap, 10) < 576 * 3)) ||
			    (RBUFL(dest_bitmap, 30) != 0 && dest_bitmap_len <= 14 + 40 + ncol * 4)) { // with compression (check minimum)
				return;
			}
		} else // non supported number of colors
			return;
		break;

	case 12: // os/2 v1.x version
		/*biSize           DWord (4 bytes) 14 Header size in bytes (must be: 12)
			biWidth          Word  (2 bytes) 18 Width of image
			biHeight         Word  (2 bytes) 20 Height of image
			biPlanes         Word  (2 bytes) 22 Number of colour planes (always 1)
			biBitCount       Word  (2 bytes) 24 Bits per pixel (1, 4, 8, 24) -> color palette size: 2, 16, 256, 0
			no compression*/
		if (RBUFW(dest_bitmap, 18) != 24 || // ragnarok condition
		    RBUFW(dest_bitmap, 20) != 24 || // ragnarok condition
		    RBUFW(dest_bitmap, 22) != 1
		    // number of colors is checked after
		    ) {
			return;
		}
		/* color structure (8 bits, always exist)
		OS/2 RGBTRIPLE color map entry
		0       rgbtBlue  (1 bytes)  Blue value for color map entry.
		1       rgbtGreen (1 bytes)  Green value for color map entry.
		2       rgbtRed   (1 bytes)  Red value for color map entry.*/
		if (RBUFW(dest_bitmap, 24) == 8) { // 256 colors (ragnarok condition)
			ncol = (RBUFL(dest_bitmap, 10) - 26) / 3; // compute number of colors recorded
			// check offset of bitmap
			if (ncol != 256) { // bmp start after the 2 headers and color structure
				return;
			}
			// check size of file
			if (dest_bitmap_len != 14 + 12 + ncol * 3 + 576) {
				return;
			}
		// 24 bits colors (Additional ragnarok condition)
		} else if ((battle_config.guild_emblem_colors & 2) == 2 && RBUFW(dest_bitmap, 24) == 24) {
			// check size of file
			if (dest_bitmap_len != 14 + 12 + 1728) { // bmp start after the 2 headers
				return;
			}
		} else // non supported number of colors
			return;
		break;

	default: // other -> not supported
		/* note: Ragnarok run under windows, client don't support OS/2 1.x, 2.x or 3.x versions. OS/2 1.x version is here for example */
		return;
	}

	guild_change_emblem(sd, (unsigned short)zipbitmap_len, RFIFOP(fd, bitmap_offset));

	return;
}

/*==========================================
 * ギルド告知変更
 *------------------------------------------
 */
static void clif_parse_GuildChangeNotice(int fd,struct map_session_data *sd, int cmd)
{
	struct guild *g;
	int guild_id;

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
	RFIFOB(fd, GETPACKETPOS(cmd,1) + 59) = '\0';
	RFIFOB(fd, GETPACKETPOS(cmd,2) + 119) = '\0';

	guild_change_notice(guild_id, RFIFOP(fd,GETPACKETPOS(cmd,1)), RFIFOP(fd,GETPACKETPOS(cmd,2)));

	return;
}

/*==========================================
 * ギルド勧誘
 *------------------------------------------
 */
static void clif_parse_GuildInvite(int fd,struct map_session_data *sd, int cmd) // S 0x0168 <TargetAccID>.l <sourceAccID>.l <myCharactorID>.l
{
	// check to be sure that is original packet (not need to have these values after)
	if (RFIFOL(fd,GETPACKETPOS(cmd,1)) != sd->status.account_id ||
	    RFIFOL(fd,GETPACKETPOS(cmd,2)) != sd->status.char_id)
		return;

	guild_invite(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)));

	return;
}

/*==========================================
 * ギルド勧誘返信
 *------------------------------------------
 */
static void clif_parse_GuildReplyInvite(int fd,struct map_session_data *sd, int cmd)
{
	guild_reply_invite(sd, RFIFOL(fd,GETPACKETPOS(cmd,0)), (unsigned char)RFIFOL(fd,GETPACKETPOS(cmd,1)));

	return;
}

/*==========================================
 * ギルド脱退
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
 * ギルド追放
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
 * ギルド会話
 *------------------------------------------
 */
static void clif_parse_GuildMessage(int fd,struct map_session_data *sd, int cmd)
{
	char *message;
	int message_size;

	nullpo_retv(sd);

	message = (char *)RFIFOP(fd, GETPACKETPOS(cmd,1));
	message_size = RFIFOW(fd, GETPACKETPOS(cmd,0)) - GETPACKETPOS(cmd,1);

	if (message_size <= 0) // against hack
		return;
	// normal client send NULL -> force it (against hacker)
	message[message_size - 1] = '\0';

	if (battle_config.check_player_name_guild_msg) {
		// structure of message: <player_name> : <message>
		char *p_message;
		int name_length;
		name_length = strlen(sd->status.name);
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

	if (is_atcommand(fd, sd, message, 0) != AtCommand_None)
		return;
	if (sd->sc_data &&
	    (sd->sc_data[SC_BERSERK].timer != -1 ||	//バーサーク時は会話も不可
	     sd->sc_data[SC_NOCHAT].timer != -1))		//チャット禁止
		return;

	guild_send_message(sd, message, message_size);

	return;
}

/*==========================================
 * ギルド同盟要求
 *------------------------------------------
 */
static void clif_parse_GuildRequestAlliance(int fd,struct map_session_data *sd, int cmd)
{
	guild_reqalliance(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)));
}
/*==========================================
 * ギルド同盟要求返信
 *------------------------------------------
 */
static void clif_parse_GuildReplyAlliance(int fd,struct map_session_data *sd, int cmd)
{
	guild_reply_reqalliance(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)),RFIFOL(fd,GETPACKETPOS(cmd,1)));
}
/*==========================================
 * ギルド関係解消
 *------------------------------------------
 */
static void clif_parse_GuildDelAlliance(int fd,struct map_session_data *sd, int cmd)
{
	guild_delalliance(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)),RFIFOL(fd,GETPACKETPOS(cmd,1)));
}
/*==========================================
 * ギルド敵対
 *------------------------------------------
 */
static void clif_parse_GuildOpposition(int fd,struct map_session_data *sd, int cmd)
{
	guild_opposition(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)));
}
/*==========================================
 * ギルド解散
 *------------------------------------------
 */
static void clif_parse_GuildBreak(int fd,struct map_session_data *sd, int cmd)
{
	guild_break(sd,RFIFOP(fd,GETPACKETPOS(cmd,0)));
}

// pet
static void clif_parse_PetMenu(int fd,struct map_session_data *sd, int cmd)
{
	pet_menu(sd,RFIFOB(fd,GETPACKETPOS(cmd,0)));
}
static void clif_parse_CatchPet(int fd,struct map_session_data *sd, int cmd)
{
	pet_catch_process2(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)));
}

static void clif_parse_SelectEgg(int fd,struct map_session_data *sd, int cmd)
{
	pet_select_egg(sd,(short)(RFIFOW(fd,GETPACKETPOS(cmd,0))-2));
}

static void clif_parse_SendEmotion(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	if(sd->pd)
		clif_pet_emotion(sd->pd,RFIFOL(fd,GETPACKETPOS(cmd,0)));
}

static void clif_parse_ChangePetName(int fd,struct map_session_data *sd, int cmd)
{
	pet_change_name(sd,RFIFOP(fd,GETPACKETPOS(cmd,0)));
}

// Kick
static void clif_parse_GMKick(int fd,struct map_session_data *sd, int cmd)
{
	struct block_list *target;
	int tid = RFIFOL(fd,GETPACKETPOS(cmd,0));

	nullpo_retv(sd);

	if(pc_isGM(sd) >= get_atcommand_level(AtCommand_Kick)) {
		target = map_id2bl(tid);
		if(target) {
			if(target->type == BL_PC) {
				struct map_session_data *tsd = (struct map_session_data *)target;
				if(pc_isGM(sd) > pc_isGM(tsd))
					clif_GM_kick(sd,tsd,1);
				else
					clif_GM_kickack(sd,0);
			}
			else if(target->type == BL_MOB) {
				struct mob_data *md = (struct mob_data *)target;
				sd->state.attack_type = 0;
				mob_damage(&sd->bl,md,md->hp,2);
			}
			else
				clif_GM_kickack(sd,0);
		}
		else
			clif_GM_kickack(sd,0);
	}
}

static void clif_parse_GMHide(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);

	if(pc_isGM(sd) >= get_atcommand_level(AtCommand_Hide)) {
		if(sd->status.option&0x40){
			sd->status.option&=~0x40;
			clif_displaymessage(fd, msg_txt(10)); // invisible off!
		}else{
			sd->status.option|=0x40;
			clif_displaymessage(fd, msg_txt(11)); // invisible!
		}
		clif_changeoption(&sd->bl);
		clif_send_clothcolor(&sd->bl);
	}
}

/*==========================================
 * GMによるチャット禁止時間付与
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

	//駆け足中は赤エモにならない
	if(sd->sc_data && sd->sc_data[SC_RUN].timer!=-1)
		return;
	//念のため強制移動中も
	if(sd->sc_data && sd->sc_data[SC_FORCEWALKING].timer!=-1)
		return;

	dstsd = map_id2sd(tid);
	if(dstsd == NULL)
		return;

	if( (type == 2 && !pc_isGM(sd)) ||
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
 * GMによるチャット禁止時間参照（？）
 *------------------------------------------
 */
static void clif_parse_GMReqNoChatCount(int fd,struct map_session_data *sd, int cmd)
{
	int tid = RFIFOL(fd,GETPACKETPOS(cmd,0));

	WFIFOW(fd,0)=0x1e0;
	WFIFOL(fd,2)=tid;
	snprintf(WFIFOP(fd,6),24,"%d",tid);
//	memcpy(WFIFOP(fd,6),"TESTNAME",24);
	WFIFOSET(fd,packet_db[0x1e0].len);

	return;
}

/*==========================================
 * スパノビの/doridoriによるSPR2倍
 *------------------------------------------
 */
static void clif_parse_sn_doridori(int fd,struct map_session_data *sd, int cmd)
{
	if(sd){
		sd->doridori_counter = 1;
		sd->tk_doridori_counter_hp = 1;
		sd->tk_doridori_counter_sp = 1;
	}
	return;
}
/*==========================================
 * スパノビの爆裂波動
 *------------------------------------------
 */
static void clif_parse_sn_explosionspirits(int fd,struct map_session_data *sd, int cmd)
{
	if(sd){
		int nextbaseexp=pc_nextbaseexp(sd);
		struct pc_base_job s_class = pc_calc_base_job(sd->status.class);
		if (battle_config.etc_log){
			if(nextbaseexp != 0)
				printf("SuperNovice explosionspirits!! %d %d %d %d\n",sd->bl.id,s_class.job,sd->status.base_exp,(int)((atn_bignumber)1000*sd->status.base_exp/nextbaseexp));
			else
				printf("SuperNovice explosionspirits!! %d %d %d 000\n",sd->bl.id,s_class.job,sd->status.base_exp);
		}

		if(s_class.job == 23 && sd->status.base_exp > 0 && nextbaseexp > 0 && (int)((atn_bignumber)1000*sd->status.base_exp/nextbaseexp)%100==0){
			clif_skill_nodamage(&sd->bl,&sd->bl,MO_EXPLOSIONSPIRITS,5,1);
			status_change_start(&sd->bl,SkillStatusChangeTable[MO_EXPLOSIONSPIRITS],5,0,0,0,skill_get_time(MO_EXPLOSIONSPIRITS,5),0 );
		}
	}
	return;
}
/*==========================================
 * Wis拒否許可 /ex /in
 *------------------------------------------
 */
int pstrcmp(const void *a, const void *b)
{
	return strcmp((char *)a, (char *)b);
}
static void clif_parse_wisexin(int fd,struct map_session_data *sd, int cmd)
{
	int type = RFIFOB(fd,GETPACKETPOS(cmd,1));
	int i;
	unsigned char flag = 1;

	if(sd){
		qsort(sd->wis_refusal[0], MAX_WIS_REFUSAL, sizeof(sd->wis_refusal[0]), pstrcmp);
		if(type==0){	//ex
			for(i=0;i<MAX_WIS_REFUSAL;i++){	//すでに追加されていれば何もしない
				if(strcmp(sd->wis_refusal[i],RFIFOP(fd,GETPACKETPOS(cmd,0)))==0){
					flag=0;
					clif_wisexin(sd, type, flag);
					return;
				}
			}
			for(i=0;i<MAX_WIS_REFUSAL;i++){	//空の拒否リストに追加(とりあえず)
				if(sd->wis_refusal[i][0]==0){
					memcpy(sd->wis_refusal[i],RFIFOP(fd,GETPACKETPOS(cmd,0)),24);
					flag=0;
					break;
				}
			}
			if(flag==1){
					memcpy(sd->wis_refusal[MAX_WIS_REFUSAL-1],RFIFOP(fd,GETPACKETPOS(cmd,0)),24);
					flag=0;
			}
		}else{		//in
			for(i=0;i<MAX_WIS_REFUSAL;i++){	//一致する拒否リストを空に
				if(strcmp(sd->wis_refusal[i],RFIFOP(fd,GETPACKETPOS(cmd,0)))==0){
					sd->wis_refusal[i][0]=0;
					flag=0;
				}
			}
			sd->wis_all = 0;
		}
		clif_wisexin(sd, type, flag);
	}
	return;
}

/*==========================================
 * Wis拒否リスト
 *------------------------------------------
 */
static void clif_parse_wisexlist(int fd,struct map_session_data *sd, int cmd)
{
	int i,j=0,count=0;

	if(sd){
		qsort(sd->wis_refusal[0], MAX_WIS_REFUSAL, sizeof(sd->wis_refusal[0]), pstrcmp);
		for(i=0;i<MAX_WIS_REFUSAL;i++){	//中身があるのを数える
			if(sd->wis_refusal[i][0]!=0)
				count++;
		}
		WFIFOW(fd,0)=0xd4;
		WFIFOW(fd,2)=4+(24*count);
		for(i=0;i<MAX_WIS_REFUSAL;i++){
			if(sd->wis_refusal[i][0]!=0){
				memcpy(WFIFOP(fd,4+j*24),sd->wis_refusal[i],24);
				j++;
			}
		}
		WFIFOSET(fd,WFIFOW(fd,2));
		if(count>=MAX_WIS_REFUSAL)	//満タンなら最後の1個を消す
			sd->wis_refusal[MAX_WIS_REFUSAL-1][0]=0;
	}

	return;
}

/*==========================================
 * Wis全拒否許可 /exall /inall
 *------------------------------------------
 */
static void clif_parse_wisall(int fd,struct map_session_data *sd, int cmd)
{
	int type = RFIFOB(fd,GETPACKETPOS(cmd,0));
	int i;

	if(sd){
		if(type==0)	//exall
			sd->wis_all = 1;
		else{		//inall
			for(i=0;i<MAX_WIS_REFUSAL;i++)	//拒否リストを空に
				sd->wis_refusal[i][0]=0;
			sd->wis_all = 0;
		}
		clif_wisall(sd, type, 0);
	}
}
/*==========================================
 * GMコマンド/killall
 *------------------------------------------
 */
static void clif_parse_GMkillall(int fd,struct map_session_data *sd, int cmd)
{
	char message[40];

	nullpo_retv(sd);

	memset(message, 0, sizeof(message));
	strncpy(message, sd->status.name, 24);
	strcat(message, " : ");
	message[strlen(message)] = GM_Symbol();
	strcat(message, "kickall");

	is_atcommand(fd, sd, message, 0);

	return;
}

/*==========================================
 * GMコマンド/summon
 *------------------------------------------
 */
static void clif_parse_GMsummon(int fd,struct map_session_data *sd, int cmd)
{
	char message[64];

	nullpo_retv(sd);

	memset(message, 0, sizeof(message));
	strncpy(message, sd->status.name, 24);
	strcat(message, " : ");
	message[strlen(message)] = GM_Symbol();
	strcat(message, "summon ");
	strncat(message, RFIFOP(fd,GETPACKETPOS(cmd,0)), 24);

	is_atcommand(fd, sd, message, 0);

	return;
}

/*==========================================
 * GMコマンド/item /monster
 *------------------------------------------
 */
static void clif_parse_GMitemmonster( int fd, struct map_session_data *sd, int cmd )
{
	char message[64];

	nullpo_retv(sd);

	memset(message, 0, sizeof(message));
	strncpy(message, sd->status.name, 24);
	strcat(message, " : ");
	message[strlen(message)] = GM_Symbol();
	strcat(message, "im ");
	strncat(message, RFIFOP(fd, GETPACKETPOS(cmd, 0)), 24);

	is_atcommand(fd, sd, message, 0);

	return;
}

/*==========================================
 * GMコマンド/shift
 *------------------------------------------
 */
static void clif_parse_GMshift(int fd,struct map_session_data *sd, int cmd)
{
	char message[100];

	nullpo_retv(sd);

	memset(message, 0, sizeof(message));
	strncpy(message, sd->status.name, 24);
	strcat(message, " : ");
	message[strlen(message)] = GM_Symbol();
	strcat(message, "jumpto ");
	strncat(message, RFIFOP(fd,GETPACKETPOS(cmd,0)), 24);

	is_atcommand(fd, sd, message, 0);

	return;
}

/*==========================================
 * GMコマンド /recall
 *------------------------------------------
 */
static void clif_parse_GMrecall(int fd,struct map_session_data *sd, int cmd)
{
	char message[100];

	memset(message, 0, sizeof(message));
	strncpy(message, sd->status.name, 24);
	strcat(message, " : ");
	message[strlen(message)] = GM_Symbol();
	strcat(message, "recall ");
	strncat(message, RFIFOP(fd,GETPACKETPOS(cmd,0)), 24);

	is_atcommand(fd, sd, message, 0);

	return;
}

/*==========================================
 * GMコマンド /remove
 *------------------------------------------
 */
static void clif_parse_GMremove(int fd,struct map_session_data *sd, int cmd)
{
	// 効果不明
	return;
}

/*==========================================
 * GMコマンド /changemaptype
 *------------------------------------------
 */
static void clif_parse_GMchangemaptype(int fd,struct map_session_data *sd, int cmd)
{
	// 詳細不明なので未実装
	return;
}

/*==========================================
 * GMコマンド /rc
 *------------------------------------------
 */
static void clif_parse_GMrc(int fd,struct map_session_data *sd, int cmd)
{
	// 効果不明
	return;
}

/*==========================================
 * GMコマンド /check
 *------------------------------------------
 */
static void clif_parse_GMcheck(int fd,struct map_session_data *sd, int cmd)
{
	// 効果不明
	return;
}

/*==========================================
 * 友達リスト追加要請
 *------------------------------------------
 */
static void clif_parse_FriendAddRequest(int fd,struct map_session_data *sd, int cmd)
{
	friend_add_request( sd, RFIFOP(fd,GETPACKETPOS(cmd,0)) );
	return;
}
/*==========================================
 * 友達リスト追加要請返答
 *------------------------------------------
 */
static void clif_parse_FriendAddReply(int fd,struct map_session_data *sd, int cmd)
{
	friend_add_reply( sd, RFIFOL(fd,GETPACKETPOS(cmd,0)), RFIFOL(fd,GETPACKETPOS(cmd,1)), RFIFOL(fd,GETPACKETPOS(cmd,2)) );
	return;
}
/*==========================================
 * 友達リスト削除要求
 *------------------------------------------
 */
static void clif_parse_FriendDeleteRequest(int fd,struct map_session_data *sd, int cmd)
{
	friend_del_request( sd, RFIFOL(fd,GETPACKETPOS(cmd,0)), RFIFOL(fd,GETPACKETPOS(cmd,1)) );
	return;
}
/*==========================================
 * BSランキング	/blacksmith
 *------------------------------------------
 */
static void clif_parse_RankingBlacksmith(int fd,struct map_session_data *sd, int cmd)
{
	ranking_clif_display(sd,RK_BLACKSMITH);
	return;
}
/*==========================================
 * アルケミランキング	/alchemist
 *------------------------------------------
 */
static void clif_parse_RankingAlchemist(int fd,struct map_session_data *sd, int cmd)
{
	ranking_clif_display(sd,RK_ALCHEMIST);
	return;
}
/*==========================================
 * テコンランキング	/taekwon
 *------------------------------------------
 */
static void clif_parse_RankingTaekwon(int fd,struct map_session_data *sd, int cmd)
{
	ranking_clif_display(sd,RK_TAEKWON);
	return;
}
/*==========================================
 * 虐殺者ランキング	/pk
 *------------------------------------------
 */
static void clif_parse_RankingPk(int fd,struct map_session_data *sd, int cmd)
{
	ranking_clif_display(sd,RK_PK);
	return;
}
/*==========================================
 * メール送信→Interへ
 *------------------------------------------
 */
static void clif_parse_SendMail(int fd,struct map_session_data *sd, int cmd)
{
	struct map_session_data *rd;
	struct mail_data md;
	int bodylen;

	nullpo_retv(sd);

	if(!battle_config.romail){	// メール送信を禁止
		clif_res_sendmail(sd->fd,1);
		return;
	}

	if(RFIFOW(fd,GETPACKETPOS(cmd,0))<70)		// 短すぎ、おかしい
		return;

	bodylen = RFIFOW(fd,2)-69;
	rd = map_nick2sd(RFIFOP(fd,GETPACKETPOS(cmd,0)));

	if(rd && rd==sd){		// 自分はダメ
		clif_res_sendmail(sd->fd,1);
		mail_removeitem(sd);
		return;
	}

	memset(&md, 0, sizeof(md));

	if(rd)
		md.receive_id = rd->status.char_id;

	strcpy(md.char_name,sd->status.name);
	md.char_id = sd->status.char_id;

	memcpy(md.receive_name,RFIFOP(fd,GETPACKETPOS(cmd,1)),24);
	snprintf(md.title,40,"%s",RFIFOP(fd,GETPACKETPOS(cmd,2)));

	if(bodylen > sizeof(md.body))
		return;

	memcpy(md.body,RFIFOP(fd,GETPACKETPOS(cmd,3)),bodylen);
	md.body_size = bodylen;

	// 日付の保存
	md.times = (int)mail_calctimes();
	// アイテム・Zenyチェック
	if(mail_checkappend(sd,&md)==0)
		intif_sendmail(&md);

	sd->mail_zeny = 0;
	sd->mail_amount = 0;
	mail_removeitem(sd);
	return;
}
/*==========================================
 * メールの選択受信
 *------------------------------------------
 */
static void clif_parse_ReadMail(int fd,struct map_session_data *sd, int cmd)
{
	int mail_num;
	nullpo_retv(sd);
	mail_num = RFIFOL(fd,GETPACKETPOS(cmd,0));
	intif_readmail(sd->status.char_id,mail_num);

	return;
}
/*==========================================
 *
 *------------------------------------------
 */
static void clif_parse_MailGetAppend(int fd,struct map_session_data *sd, int cmd)
{
	int mail_num;

	nullpo_retv(sd);
	mail_num = RFIFOL(fd,GETPACKETPOS(cmd,0));
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
	flag = RFIFOW(fd,GETPACKETPOS(cmd,0));

	if(!flag || flag==1)
		mail_removeitem(sd);
	if(!flag || flag==2)
		sd->mail_zeny = 0;

	return;
}
/*==========================================
 * メールBOXの更新要求
 *------------------------------------------
 */
static void clif_parse_RefleshMailBox(int fd,struct map_session_data *sd, int cmd)
{
	nullpo_retv(sd);
	intif_mailbox(sd->status.char_id);
	return;
}
/*==========================================
 * メールに添付
 *------------------------------------------
 */
static void clif_parse_SendMailSetAppend(int fd,struct map_session_data *sd, int cmd)
{
	int idx = RFIFOW(fd,GETPACKETPOS(cmd,0));
	int amount=RFIFOL(fd,GETPACKETPOS(cmd,1));
	int flag;

	nullpo_retv(sd);
	if (idx < 0 || amount < 0)
		return;
	flag = mail_setitem(sd, idx, amount);

	if(flag>=0)
		clif_res_sendmail_setappend(sd->fd,flag);
	return;
}
/*==========================================
 * メール削除
 *------------------------------------------
 */
static void clif_parse_DeleteMail(int fd,struct map_session_data *sd, int cmd)
{
	int mail_num=RFIFOL(fd,GETPACKETPOS(cmd,0));

	nullpo_retv(sd);
	intif_deletemail(sd->status.char_id,mail_num);
	return;
}

/*==========================================
 * メール返送
 *------------------------------------------
 */
static void clif_parse_ReturnMail(int fd,struct map_session_data *sd, int cmd)
{
	//int mail_num = RFIFOL(fd,GETPACKETPOS(cmd,0));
	//char *name = (char*)RFIFOP(fd,GETPACKETPOS(cmd,1));

	nullpo_retv(sd);

	// とりあえず未実装
	return;
}

/*==========================================
 * ホムンクルス
 *------------------------------------------
 */
// homun
static void clif_parse_HomMenu(int fd,struct map_session_data *sd, int cmd)
{
	homun_menu(sd,RFIFOB(fd,GETPACKETPOS(cmd,0)));
}
static void clif_parse_HomWalkMaster(int fd,struct map_session_data *sd, int cmd)
{
//	int id = RFIFOL(fd,2);	hd->bl.idが入ってる
	struct homun_data *hd;

	nullpo_retv(sd);
	if((hd=sd->hd)==NULL) return;

	homun_return_master(sd);
}
static void clif_parse_HomWalkToXY(int fd,struct map_session_data *sd, int cmd)
{
//	int id = RFIFOL(fd,2);	//hd->bl.idが入ってる
	int x,y;

	nullpo_retv(sd);
	if(!sd->hd) return;

	x = RFIFOB(fd,GETPACKETPOS(cmd,0))*4+(RFIFOB(fd,GETPACKETPOS(cmd,0)+1)>>6);
	y = ((RFIFOB(fd,GETPACKETPOS(cmd,0)+1)&0x3f)<<4)+(RFIFOB(fd,GETPACKETPOS(cmd,0)+2)>>4);

	unit_walktoxy(&sd->hd->bl,x,y);
}
static void clif_parse_HomActionRequest(int fd,struct map_session_data *sd, int cmd)
{
	struct homun_data *hd;
	struct block_list *bl;
	unsigned int tick;
	int action_type,target_id;

	nullpo_retv(sd);
	if((hd=sd->hd)==NULL) return;

	if(unit_isdead(&hd->bl)) {
		clif_clearchar_area(&hd->bl,1);
		return;
	}
	if(hd->status.option&2)
		return;

	tick=gettick();

	unit_stop_walking(&hd->bl,1);
	unit_stopattack(&hd->bl);

	target_id = RFIFOL(fd,GETPACKETPOS(cmd,0));
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
	case 0x07:	// continuous attack ...あるのかな？
		{
			bl=map_id2bl(target_id);
			if(bl && mob_gvmobcheck(sd,bl)==0)
				return;
			unit_attack(&hd->bl,target_id,action_type!=0);
		}
		break;
	}
	return;
}
static void clif_parse_ChangeHomName(int fd,struct map_session_data *sd, int cmd)
{
	homun_change_name(sd,RFIFOP(fd,GETPACKETPOS(cmd,0)));
}

/*==========================================
 * パケットデバッグ
 *------------------------------------------
 */
static void clif_parse_debug(int fd,struct map_session_data *sd, int cmd)
{
	int i;

	printf("packet debug 0x%4X\n",cmd);
	printf("---- 00-01-02-03-04-05-06-07-08-09-0A-0B-0C-0D-0E-0F");
	for(i=0;i<packet_db[cmd].len;i++){
		if((i&15)==0)
			printf("\n%04X ",i);
		printf("%02X ",RFIFOB(fd,i));
	}
	printf("\n");
}
/*==========================================
 * /effectとか
 *------------------------------------------
 */
static void clif_parse_clientsetting(int fd,struct map_session_data *sd, int cmd)
{
	// RFIFOB(fd,0)	effectを切ってるかどうか
	return;
}

/*==========================================
 * 養子要求
 *------------------------------------------
 */
static void clif_parse_BabyRequest(int fd,struct map_session_data *sd, int cmd)
{
	struct map_session_data* baby_sd = NULL;

	nullpo_retv(sd);

	baby_sd = map_id2sd(RFIFOL(fd,GETPACKETPOS(cmd,0)));

	if(baby_sd && baby_sd->bl.type == BL_PC) {
		struct map_session_data *p_sd = pc_get_partner(sd);

		if(p_sd && pc_check_adopt_condition(baby_sd, sd, p_sd, 1)) {
			baby_sd->adopt_invite = sd->status.account_id;
			clif_baby_req_display(baby_sd, sd, p_sd->status.account_id);
		}
	}
	return;
}

/*==========================================
 * 養子返答
 *------------------------------------------
 */
static void clif_parse_BabyReply(int fd,struct map_session_data *sd, int cmd)
{
	pc_adopt_reply(sd,RFIFOL(fd,GETPACKETPOS(cmd,0)),RFIFOL(fd,GETPACKETPOS(cmd,1)),RFIFOL(fd,GETPACKETPOS(cmd,2)));
	return;
}

/*==========================================
 * 太陽と月と星の感情のセーブ返答
 *------------------------------------------
 */
static void clif_parse_FeelSaveAck(int fd,struct map_session_data *sd, int cmd)
{
	clif_feel_saveack(sd,(int)RFIFOB(fd,GETPACKETPOS(cmd,0)));
	return;
}

/*==========================================
 * クライアントからのパケット解析
 * socket.cのdo_parsepacketから呼び出される
 *------------------------------------------
 */

int clif_disconnect(int fd) {
	struct map_session_data *sd = session[fd]->session_data;
	if(sd && sd->state.auth)
		clif_quitsave(fd,sd);
	close(fd);
	if (sd) {
		struct map_session_data *tmpsd = map_id2sd(sd->bl.id);
		if (tmpsd == sd)
			map_deliddb(&sd->bl);
		if( sd->bl.prev )
			map_delblock( &sd->bl );
	}

	return 0;
}

struct {
	void (*func)(int fd,struct map_session_data *sd, int cmd);
	char *name;
} clif_parse_func[]={
	{clif_parse_WantToConnection,"wanttoconnection"},
	{clif_parse_LoadEndAck,"loadendack"},
	{clif_parse_TickSend,"ticksend"},
	{clif_parse_WalkToXY,"walktoxy"},
	{clif_parse_QuitGame,"quitgame"},
	{clif_parse_GetCharNameRequest,"getcharnamerequest"},
	{clif_parse_GlobalMessage,"globalmessage"},
	{clif_parse_MapMove,"mapmove"},
	{clif_parse_ChangeDir,"changedir"},
	{clif_parse_Emotion,"emotion"},
	{clif_parse_HowManyConnections,"howmanyconnections"},
	{clif_parse_ActionRequest,"actionrequest"},
	{clif_parse_Restart,"restart"},
	{clif_parse_Wis,"wis"},
	{clif_parse_GMmessage,"gmmessage"},
	{clif_parse_TakeItem,"takeitem"},
	{clif_parse_DropItem,"dropitem"},
	{clif_parse_UseItem,"useitem"},
	{clif_parse_EquipItem,"equipitem"},
	{clif_parse_UnequipItem,"unequipitem"},
	{clif_parse_NpcClicked,"npcclicked"},
	{clif_parse_NpcBuySellSelected,"npcbuysellselected"},
	{clif_parse_NpcBuyListSend,"npcbuylistsend"},
	{clif_parse_NpcSellListSend,"npcselllistsend"},
	{clif_parse_CreateChatRoom,"createchatroom"},
	{clif_parse_ChatAddMember,"chataddmember"},
	{clif_parse_ChatRoomStatusChange,"chatroomstatuschange"},
	{clif_parse_ChangeChatOwner,"changechatowner"},
	{clif_parse_KickFromChat,"kickfromchat"},
	{clif_parse_ChatLeave,"chatleave"},
	{clif_parse_TradeRequest,"traderequest"},
	{clif_parse_TradeAck,"tradeack"},
	{clif_parse_TradeAddItem,"tradeadditem"},
	{clif_parse_TradeOk,"tradeok"},
	{clif_parse_TradeCancel,"tradecancel"},
	{clif_parse_TradeCommit,"tradecommit"},
	{clif_parse_StopAttack,"stopattack"},
	{clif_parse_PutItemToCart,"putitemtocart"},
	{clif_parse_GetItemFromCart,"getitemfromcart"},
	{clif_parse_RemoveOption,"removeoption"},
	{clif_parse_ChangeCart,"changecart"},
	{clif_parse_StatusUp,"statusup"},
	{clif_parse_SkillUp,"skillup"},
	{clif_parse_UseSkillToId,"useskilltoid"},
	{clif_parse_UseSkillToPos,"useskilltopos"},
	{clif_parse_UseSkillMap,"useskillmap"},
	{clif_parse_RequestMemo,"requestmemo"},
	{clif_parse_ProduceMix,"producemix"},
	{clif_parse_RepairItem,"repairitem"},
	{clif_parse_WeaponRefine,"weaponrefine"},
	{clif_parse_NpcSelectMenu,"npcselectmenu"},
	{clif_parse_NpcNextClicked,"npcnextclicked"},
	{clif_parse_NpcAmountInput,"npcamountinput"},
	{clif_parse_NpcStringInput,"npcstringinput"},
	{clif_parse_NpcCloseClicked,"npccloseclicked"},
	{clif_parse_ItemIdentify,"itemidentify"},
	{clif_parse_SelectArrow,"selectarrow"},
	{clif_parse_AutoSpell,"autospell"},
	{clif_parse_UseCard,"usecard"},
	{clif_parse_InsertCard,"insertcard"},
	{clif_parse_SolveCharName,"solvecharname"},
	{clif_parse_ResetChar,"resetchar"},
	{clif_parse_LGMmessage,"lgmmessage"},
	{clif_parse_MoveToKafra,"movetokafra"},
	{clif_parse_MoveFromKafra,"movefromkafra"},
	{clif_parse_MoveToKafraFromCart,"movetokafrafromcart"},
	{clif_parse_MoveFromKafraToCart,"movefromkafratocart"},
	{clif_parse_CloseKafra,"closekafra"},
	{clif_parse_CreateParty,"createparty"},
	{clif_parse_CreateParty2,"createparty2"},
	{clif_parse_PartyInvite,"partyinvite"},
	{clif_parse_ReplyPartyInvite,"replypartyinvite"},
	{clif_parse_LeaveParty,"leaveparty"},
	{clif_parse_RemovePartyMember,"removepartymember"},
	{clif_parse_PartyChangeOption,"partychangeoption"},
	{clif_parse_PartyMessage,"partymessage"},
	{clif_parse_CloseVending,"closevending"},
	{clif_parse_VendingListReq,"vendinglistreq"},
	{clif_parse_PurchaseReq,"purchasereq"},
	{clif_parse_OpenVending,"openvending"},
	{clif_parse_CreateGuild,"createguild"},
	{clif_parse_GuildCheckMaster,"guildcheckmaster"},
	{clif_parse_GuildRequestInfo,"guildrequestinfo"},
	{clif_parse_GuildChangePositionInfo,"guildchangepositioninfo"},
	{clif_parse_GuildChangeMemberPosition,"guildchangememberposition"},
	{clif_parse_GuildRequestEmblem,"guildrequestemblem"},
	{clif_parse_GuildChangeEmblem,"guildchangeemblem"},
	{clif_parse_GuildChangeNotice,"guildchangenotice"},
	{clif_parse_GuildInvite,"guildinvite"},
	{clif_parse_GuildReplyInvite,"guildreplyinvite"},
	{clif_parse_GuildLeave,"guildleave"},
	{clif_parse_GuildExplusion,"guildexplusion"},
	{clif_parse_GuildMessage,"guildmessage"},
	{clif_parse_GuildRequestAlliance,"guildrequestalliance"},
	{clif_parse_GuildReplyAlliance,"guildreplyalliance"},
	{clif_parse_GuildDelAlliance,"guilddelalliance"},
	{clif_parse_GuildOpposition,"guildopposition"},
	{clif_parse_GuildBreak,"guildbreak"},
	{clif_parse_PetMenu,"petmenu"},
	{clif_parse_CatchPet,"catchpet"},
	{clif_parse_SelectEgg,"selectegg"},
	{clif_parse_SendEmotion,"sendemotion"},
	{clif_parse_ChangePetName,"changepetname"},
	{clif_parse_GMKick,"gmkick"},
	{clif_parse_GMHide,"gmhide"},
	{clif_parse_GMReqNoChat,"gmreqnochat"},
	{clif_parse_GMReqNoChatCount,"gmreqnochatcount"},
	{clif_parse_sn_doridori,"sndoridori"},
	{clif_parse_sn_explosionspirits,"snexplosionspirits"},
	{clif_parse_wisexin,"wisexin"},
	{clif_parse_wisexlist,"wisexlist"},
	{clif_parse_wisall,"wisall"},
	{clif_parse_GMkillall,"killall"},
	{clif_parse_GMsummon,"summon"},
	{clif_parse_GMitemmonster,"itemmonster"},
	{clif_parse_GMshift,"shift"},
	{clif_parse_GMrecall,"recall"},
	{clif_parse_GMremove,"gmremove"},
	{clif_parse_GMchangemaptype,"changemaptype"},
	{clif_parse_GMrc,"gmrc"},
	{clif_parse_GMcheck,"gmcheck"},
	{clif_parse_FriendAddRequest,"friendaddrequest"},
	{clif_parse_FriendAddReply,"friendaddreply"},
	{clif_parse_FriendDeleteRequest,"frienddeleterequest"},
	{clif_parse_debug,"debug"},
	{clif_parse_clientsetting,"clientsetting"},
	{clif_parse_BabyRequest,"babyrequest"},
	{clif_parse_BabyReply,"babyreply"},
	{clif_parse_RankingBlacksmith,"rankingblacksmith"},
	{clif_parse_RankingAlchemist,"rankingalchemist"},
	{clif_parse_RankingTaekwon,"rankingtaekwon"},
	{clif_parse_RankingPk,"rankingpk"},
	{clif_parse_HomMenu,"hommenu"},
	{clif_parse_HomWalkMaster,"homwalkmaster"},
	{clif_parse_HomWalkToXY,"homwalktoxy"},
	{clif_parse_HomActionRequest,"homactionrequest"},
	{clif_parse_ChangeHomName,"changehomname"},
	{clif_parse_MailWinOpen,"mailwinopen"},
	{clif_parse_ReadMail,"readmail"},
	{clif_parse_MailGetAppend,"mailgetappend"},
	{clif_parse_SendMail,"sendmail"},
	{clif_parse_RefleshMailBox,"refleshmailbox"},
	{clif_parse_SendMailSetAppend,"sendmailsetappend"},
	{clif_parse_DeleteMail,"deletemail"},
	{clif_parse_ReturnMail,"returnmail"},
	{clif_parse_FeelSaveAck,"feelsaveack"},
	{NULL,NULL}
};

int clif_parse(int fd)
{
	int packet_len=0,cmd;
	struct map_session_data *sd;

	// char鯖に繋がってない間は接続禁止
	if(!chrif_isconnect())
		session[fd]->eof = 1;

	while(session[fd] != NULL && !session[fd]->eof) {
		sd = session[fd]->session_data;

		if(RFIFOREST(fd)<2)
			return 0;
		cmd = RFIFOW(fd,0);

		// 管理用パケット処理
		if(cmd>=30000){
			switch(cmd){
			case 0x7530:	// Athena情報所得
				WFIFOW(fd,0)=0x7531;
				WFIFOB(fd,2)=AURIGA_MAJOR_VERSION;
				WFIFOB(fd,3)=AURIGA_MINOR_VERSION;
				WFIFOB(fd,4)=AURIGA_REVISION;
				WFIFOB(fd,5)=AURIGA_RELEASE_FLAG;
				WFIFOB(fd,6)=AURIGA_OFFICIAL_FLAG;
				WFIFOB(fd,7)=AURIGA_SERVER_MAP;
				WFIFOW(fd,8)=AURIGA_MOD_VERSION;
				WFIFOSET(fd,10);
				RFIFOSKIP(fd,2);
				break;
			case 0x7532:	// 接続の切断
				close(fd);
				session[fd]->eof=1;
				break;
			}
			return 0;
		}

		// ゲーム用以外パケットか、認証を終える前に0072以外が来たら、切断する
		if(cmd>=MAX_PACKET_DB || packet_db[cmd].len==0 ||
		   ((!sd || (sd && sd->state.auth==0)) && packet_db[cmd].func!=clif_parse_WantToConnection) ){

			close(fd);
			session[fd]->eof = 1;
			if(cmd<MAX_PACKET_DB && packet_db[cmd].len==0) {
				printf("clif_parse : %d %d %x\n",fd,packet_db[cmd].len,cmd);
				printf("%x length 0 packet disconnect %d\n",cmd,fd);
			}
			return 0;
		}
		// パケット長を計算
		packet_len = packet_db[cmd].len;
		if(packet_len==-1){
			if(RFIFOREST(fd)<4)
				return 0;	// 可変長パケットで長さの所までデータが来てない
			packet_len = RFIFOW(fd,2);
			if(packet_len<4 || packet_len>32768){
				close(fd);
				session[fd]->eof =1;
				return 0;
			}
		}

		if(RFIFOREST(fd)<packet_len)
			return 0;	// まだ1パケット分データが揃ってない

		if(sd && sd->state.auth==1 &&
			sd->state.waitingdisconnect==1 ){// 切断待ちの場合パケットを処理しない

		}else if(packet_db[cmd].func){
			g_packet_len = packet_len;	// GETPACKETPOS 用に保存
			// パケット処理
			packet_db[cmd].func(fd,sd,cmd);
		} else {
			// 不明なパケット
			if(battle_config.error_log) {
				printf("clif_parse : %d %d %x\n",fd,packet_len,cmd);
#ifdef DUMP_UNKNOWN_PACKET
				{
					int i;
					printf("---- 00-01-02-03-04-05-06-07-08-09-0A-0B-0C-0D-0E-0F");
					for(i=0;i<packet_len;i++){
						if((i&15)==0)
							printf("\n%04X ",i);
						printf("%02X ",RFIFOB(fd,i));
					}
					printf("\n");
				}
#endif
			}
		}
		RFIFOSKIP(fd,packet_len);
	}

	return 0;
}

/*==========================================
 * パケットデータベース読み込み
 *------------------------------------------
 */
static void packetdb_readdb(void)
{
	FILE *fp;
	char line[1024];
	int ln=0;
	int cmd,j;
	char *str[32],*p,*str2[32],*p2;

	memset(packet_db,0,sizeof(packet_db));

	if( (fp=fopen("db/packet_db.txt","r"))==NULL ){
		printf("can't read db/packet_db.txt\n");
		exit(1);
	}
	while(fgets(line,1020,fp)){
		if(line[0]=='/' && line[1]=='/')
			continue;
		memset(str,0,sizeof(str));
		for(j=0,p=line;j<4 && p;j++){
			str[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		if(str[0]==NULL)
			continue;

		cmd=strtol(str[0],(char **)NULL,0);
		if(cmd<=0 || cmd>=MAX_PACKET_DB)
			continue;

		if(str[1]==NULL){
			printf("packet_db: packet len error\n");
			exit(1);
		}
		packet_db[cmd].len = atoi(str[1]);

		if(str[2]==NULL){
			ln++;
			continue;
		}
		for(j=0;j<sizeof(clif_parse_func)/sizeof(clif_parse_func[0]);j++){
			if(clif_parse_func[j].name == NULL){
				printf("packet_db: %d 0x%x no func %s\n",ln+1,cmd,str[2]);
				exit(1);
			}
			if( strcmp(str[2],clif_parse_func[j].name)==0){
				packet_db[cmd].func=clif_parse_func[j].func;
				break;
			}
		}
		if(str[3]==NULL){
			printf("packet_db: packet error\n");
			exit(1);
		}
		for(j=0,p2=str[3];p2;j++){
			str2[j]=p2;
			p2=strchr(p2,':');
			if(p2) *p2++=0;
			packet_db[cmd].pos[j]=atoi(str2[j]);
		}

		ln++;
//		if(packet_db[cmd].len > 2 && packet_db[cmd].pos[0] == 0)
//			printf("packet_db:? %d 0x%x %d %s %p\n",ln,cmd,packet_db[cmd].len,str[2],packet_db[cmd].func);
	}
	fclose(fp);
	printf("read db/packet_db.txt done (count=%d)\n",ln);

	return;
}

// athena chat system

#define MAX_CHAT_MESSAGE 15

char webchat_message[MAX_CHAT_MESSAGE][256*4+1];

void clif_webchat_message(const char* head,const char *mes1,const char *mes2) {
	int  i;
	char *p;
	char temp[512];

	sprintf(temp,"%s %s : %s",head,mes1,mes2);
	p = httpd_quote_meta(temp);
	// 重複メッセージがある場合発言取り消し
	for(i = 0; i < MAX_CHAT_MESSAGE; i++) {
		if(!strcmp(p,webchat_message[i])) {
			aFree(p);
			return;
		}
	}
	clif_onlymessage(NULL,temp,strlen(temp) + 1);

	memmove(&webchat_message[1],&webchat_message[0],sizeof(webchat_message[0]) * (MAX_CHAT_MESSAGE - 1));
	strcpy(webchat_message[0],p);
	aFree(p);

	return;
}

void clif_webchat(struct httpd_session_data* sd,const char* url) {
	char *name1 = httpd_get_value(sd,"name");
	char *name2 = httpd_binary_encode(name1);
	char *name3 = httpd_quote_meta(name1);
	char *mes   = httpd_get_value(sd,"mes");
	const char *err = NULL;
	char buf[8192];
	char *p = buf;
	do {
		int i;
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
				// POST以外の書き込みはお断り
				err = "Illegal request."; break;
			}
			clif_webchat_message("[web]",name1,mes);
		}
		// print form
		// ３０秒ごとに更新
		p += sprintf(p,"<html><head>\n");
		p += sprintf(p,"<meta http-equiv=\"Refresh\" content=\"30;URL=/chat?name=%s\">\n",name2);
		p += sprintf(p,"<title>Athena Chat</title></head>\n\n<body>\n");
		p += sprintf(p,"<form action=\"/chat\" method=\"POST\">\n");
		p += sprintf(p,"%s : <input type=\"text\" name=\"mes\" size=\"32\">\n",name3);
		p += sprintf(p,"<input type=\"hidden\" name=\"name\" value=\"%s\">\n",name3);
		p += sprintf(p,"<input type=\"submit\" value=\"Send!\">\n");
		p += sprintf(p,"</form>\n");
		for(i = 0;i < MAX_CHAT_MESSAGE; i++) {
			if(webchat_message[i][0])
				p += sprintf(p,"%s<br>\n",webchat_message[i]);
		}
		p += sprintf(p,"</body></html>\n");
		httpd_send(sd,200,"text/html",p - buf,buf);
	} while(0);
	if(err != NULL) {
		httpd_send(sd,200,"text/html",strlen(err),err);
	}
	aFree(name1);
	aFree(name2);
	aFree(name3);
	aFree(mes);

	return;
}

/*==========================================
 * 終了
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

	packetdb_readdb();
	set_defaultparse(clif_parse);
	set_sock_destruct(clif_disconnect);
	for(i=0;i<10;i++){
		if ((map_fd = make_listen_port(map_port, listen_ip)))
			break;
#ifdef _WIN32
		Sleep(20);
#else
		sleep(20);
#endif
	}
	if(i==10){
		printf("cant bind game port\n");
		exit(1);
	}
	add_timer_func_list(clif_waitclose, "clif_waitclose");
	add_timer_func_list(clif_clearchar_delay_sub, "clif_clearchar_delay_sub");

	return;
}

