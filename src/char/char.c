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

#define _CHAR_C_

#define DUMP_UNKNOWN_PACKET	1

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core.h"
#include "socket.h"
#include "timer.h"
#include "db.h"
#include "mmo.h"
#include "version.h"
#include "nullpo.h"
#include "malloc.h"
#include "httpd.h"
#include "graph.h"
#include "md5calc.h"
#include "utils.h"

#include "char.h"
#include "charlog.h"
#include "inter.h"
#include "chardb.h"
#include "storagedb.h"
#include "statusdb.h"
#include "questdb.h"
#include "petdb.h"
#include "partydb.h"
#include "mercdb.h"
#include "maildb.h"
#include "homundb.h"
#include "guilddb.h"
#include "int_party.h"
#include "int_storage.h"

static struct mmo_map_server server[MAX_MAP_SERVERS];
static int server_fd[MAX_MAP_SERVERS];

static int login_fd = -1;
static int char_fd  = -1;
static int char_sfd = -1;
static char userid[24] = "";
static char passwd[24] = "";
static char server_name[20] = "Auriga";
static char login_host[256] = "";
static unsigned long login_ip;
static unsigned short login_port = 6900;
static char char_host[256] = "";
static unsigned long char_ip;
static unsigned short char_port = 6121;
static char char_shost[256] = "";
static unsigned long char_sip = 0;
static unsigned short char_sport = 0;
static int char_loginaccess_autorestart;
static int char_maintenance;
static int char_new;
static int delete_delay_time = 86400;

int start_zeny   = 500;
int start_weapon = 1201;		/* Knife */
int start_armor  = 2301;		/* Cotton Shirt */

struct Ranking_Data ranking_data[MAX_RANKING][MAX_RANKER];
char GM_account_filename[1024] = "conf/GM_account.txt";
char char_conf_filename[256]  = "conf/char_auriga.conf";
char inter_conf_filename[256] = "conf/inter_auriga.conf";

char unknown_char_name[24] = "Unknown";
static char default_map_name[16] = "prontera.gat";
static int  default_map_type = 0;

int check_status_polygon = 2;
int max_char_slot = 9;	// キャラクタースロットの最大数

struct char_online {
	int account_id;
	int char_id;
	unsigned long ip;
	unsigned short port;
	char name[24];
};

struct cram_session_data {
	int md5keylen;
	char md5key[128];
};

static struct {
	int account_id;
	int char_id;
	int login_id1;
	int login_id2;
	unsigned long ip;
	int delflag;
	int sex;
} auth_fifo[AUTH_FIFO_SIZE];
static int auth_fifo_pos = 0;

// online DB
static struct dbt *char_online_db;

#define CHAR_STATE_WAITAUTH 0
#define CHAR_STATE_AUTHOK 1

static int max_connect_user = 0;
static int autosave_interval = DEFAULT_AUTOSAVE_INTERVAL_CS;

const char ranking_reg[MAX_RANKING][32] = {
	"PC_BLACKSMITH_POINT",
	"PC_ALCHEMIST_POINT",
	"PC_TAEKWON_POINT",
	"PC_PK_POINT",
	//"PC_PVP_POINT",
};

// 初期位置（confファイルから再設定可能）
struct point start_point = { "new_1-1.gat", 53, 111 };

static struct dbt *gm_account_db;

int isGM(int account_id)
{
	struct gm_account *p = (struct gm_account *)numdb_search(gm_account_db,account_id);

	if( p == NULL)
		return 0;

	return p->level;
}

static void read_gm_account(void)
{
	char line[8192];
	struct gm_account *p;
	FILE *fp;
	int c, l;
	int account_id, level;
	int i;
	int range, start_range, end_range;

	gm_account_db = numdb_init();

	if ((fp = fopen(GM_account_filename, "r")) == NULL) {
		printf("File not found: %s.\n", GM_account_filename);
		return;
	}

	line[sizeof(line)-1] = '\0';
	c = 0;
	l = 0;
	while(fgets(line, sizeof(line)-1, fp)) {
		l++;
		if ((line[0] == '/' && line[1] == '/') || line[0] == '\0' || line[0] == '\n' || line[0] == '\r')
			continue;

		if ((range = sscanf(line, "%d%*[-~]%d %d", &start_range, &end_range, &level)) == 3 ||
		    (range = sscanf(line, "%d%*[-~]%d:%d", &start_range, &end_range, &level)) == 3 ||
		    (range = sscanf(line, "%d %d", &start_range, &level)) == 2 ||
		    (range = sscanf(line, "%d:%d", &start_range, &level)) == 2 ||
		    (range = sscanf(line, "%d: %d", &start_range, &level)) == 2) {
			if (level <= 0) {
				printf("gm_account [%s]: invalid GM level [%ds] line %d\n", GM_account_filename, level, l);
			} else {
				if (level > 99)
					level = 99;
				if (range == 2) {
					end_range = start_range;
				} else if (end_range < start_range) {
					i = end_range;
					end_range = start_range;
					start_range = i;
				}
				for (account_id = start_range; account_id <= end_range; account_id++) {
					if ((p = (struct gm_account *)numdb_search(gm_account_db, account_id)) == NULL) {
						p = (struct gm_account *)aCalloc(1, sizeof(struct gm_account));
						numdb_insert(gm_account_db, account_id, p);
					}
					p->account_id = account_id;
					p->level = level;
					c++;
				}
			}
		} else {
			printf("gm_account: broken data [%s] line %d\n", GM_account_filename, l);
		}
	}
	fclose(fp);
	//printf("gm_account: %s read done (%d gm account ID)\n", GM_account_filename, c);

	return;
}

static int mmo_char_sync_timer(int tid,unsigned int tick,int id,void *data)
{
	chardb_sync();
	inter_sync();

	return 0;
}

static int count_users(void)
{
	int i, users = 0;

	if (login_fd >= 0 && session[login_fd]) {
		for(i = 0; i < MAX_MAP_SERVERS; i++) {
			if (server_fd[i] >= 0)
				users += server[i].users;
		}
	}

	return users;
}

static int mmo_char_send006b(int fd,struct char_session_data *sd)
{
	int i,found_num;
	int j = 0;
	const struct mmo_charstatus *st;
#ifdef NEW_006b
	int offset=24;
#else
	int offset=4;
#endif

#if PACKETVER >= 8
	int len = 108;
#else
	int len = 106;
#endif

#ifdef NEW_006b_RE
	len += 4;
#endif

#if PACKETVER > 26
	offset += 3;
#endif

#if PACKETVER > 28 && PACKETVER < 30 || PACKETVER > 30
	len += 16;
#endif

#if PACKETVER > 30
	len += 4;
#endif

	session[fd]->auth = 1; // 認証終了を socket.c に伝える

	sd->state = CHAR_STATE_AUTHOK;
	found_num = chardb_load_all(sd,sd->account_id);

	memset(WFIFOP(fd,0),0,offset+found_num*len);
	WFIFOW(fd,0)=0x6b;
	WFIFOW(fd,2)=offset+found_num*len;
#if PACKETVER > 26
	WFIFOB(fd,4) = max_char_slot;
	WFIFOB(fd,5) = max_char_slot;
	WFIFOB(fd,6) = max_char_slot;
#endif

	for( i = 0; i < max_char_slot ; i++ ) {
		if(sd->found_char[i] == NULL)
			continue;
		st = &sd->found_char[i]->st;
		WFIFOL(fd,offset+(i*len)    ) = st->char_id;
		WFIFOL(fd,offset+(i*len)+  4) = st->base_exp;
		WFIFOL(fd,offset+(i*len)+  8) = st->zeny;
		WFIFOL(fd,offset+(i*len)+ 12) = st->job_exp;
		WFIFOL(fd,offset+(i*len)+ 16) = st->job_level;
		WFIFOL(fd,offset+(i*len)+ 20) = 0;
		WFIFOL(fd,offset+(i*len)+ 24) = 0;
		WFIFOL(fd,offset+(i*len)+ 28) = st->option;
		WFIFOL(fd,offset+(i*len)+ 32) = st->karma;
		WFIFOL(fd,offset+(i*len)+ 36) = st->manner;
		WFIFOW(fd,offset+(i*len)+ 40) = st->status_point;
#ifdef NEW_006b_RE
		WFIFOL(fd,offset+(i*len)+ 42) = st->hp;
		WFIFOL(fd,offset+(i*len)+ 46) = st->max_hp;
		j = 4;
#else
		WFIFOW(fd,offset+(i*len)+ 42) = (st->hp     > 0x7fff) ? 0x7fff : st->hp;
		WFIFOW(fd,offset+(i*len)+ 44) = (st->max_hp > 0x7fff) ? 0x7fff : st->max_hp;
#endif
		WFIFOW(fd,offset+(i*len)+ 46 + j) = (st->sp     > 0x7fff) ? 0x7fff : st->sp;
		WFIFOW(fd,offset+(i*len)+ 48 + j) = (st->max_sp > 0x7fff) ? 0x7fff : st->max_sp;
		WFIFOW(fd,offset+(i*len)+ 50 + j) = DEFAULT_WALK_SPEED; // char_dat[j].st.speed;
		WFIFOW(fd,offset+(i*len)+ 52 + j) = st->class_;
		WFIFOW(fd,offset+(i*len)+ 54 + j) = st->hair;
		WFIFOW(fd,offset+(i*len)+ 56 + j) = st->weapon;
		WFIFOW(fd,offset+(i*len)+ 58 + j) = st->base_level;
		WFIFOW(fd,offset+(i*len)+ 60 + j) = st->skill_point;
		WFIFOW(fd,offset+(i*len)+ 62 + j) = st->head_bottom;
		WFIFOW(fd,offset+(i*len)+ 64 + j) = st->shield;
		WFIFOW(fd,offset+(i*len)+ 66 + j) = st->head_top;
		WFIFOW(fd,offset+(i*len)+ 68 + j) = st->head_mid;
		WFIFOW(fd,offset+(i*len)+ 70 + j) = st->hair_color;
		WFIFOW(fd,offset+(i*len)+ 72 + j) = st->clothes_color;
		memcpy( WFIFOP(fd,offset+(i*len)+74 + j), st->name, 24 );
		WFIFOB(fd,offset+(i*len)+ 98 + j) = (st->str > 255)  ? 255: st->str;
		WFIFOB(fd,offset+(i*len)+ 99 + j) = (st->agi > 255)  ? 255: st->agi;
		WFIFOB(fd,offset+(i*len)+100 + j) = (st->vit > 255)  ? 255: st->vit;
		WFIFOB(fd,offset+(i*len)+101 + j) = (st->int_ > 255) ? 255: st->int_;
		WFIFOB(fd,offset+(i*len)+102 + j) = (st->dex > 255)  ? 255: st->dex;
		WFIFOB(fd,offset+(i*len)+103 + j) = (st->luk > 255)  ? 255: st->luk;
		WFIFOW(fd,offset+(i*len)+104 + j) = st->char_num;
		if(len >= (108+j))
			WFIFOW(fd,offset+(i*len)+106 + j) = 1;	// キャラ名の変更が可能な状態かどうか(0でON 1でOFF)
		if(len >= (124+j))	// 最後に在籍していたMAP名
			memcpy(WFIFOP(fd,offset+(i*len)+108 + j),st->last_point.map,16);
		if(len >= (128+j))	// 削除時間
			WFIFOL(fd,offset+(i*len)+124 + j) = st->delete_date;

		// 騎乗中のログイン時エラー対策
		if (st->option&0x7e80020)
			WFIFOL(fd,offset+(i*len)+28) = 0;
		else
			WFIFOL(fd,offset+(i*len)+28) = st->option;
	}
	WFIFOSET(fd,WFIFOW(fd,2));

	return 0;
}

// ##変数の保存
static int set_account_reg2(int acc,int num,struct global_reg *reg)
{
	int i;
	struct char_session_data sd;
	struct mmo_chardata *cd;
	int max = chardb_load_all(&sd,acc);

	for(i=0;i<max;i++) {
		// ##変数は利用される可能性が低いので、手抜きとしてconst外して強引にここで書き換える
		cd = (struct mmo_chardata *)&(*sd.found_char[i]);
		if(cd) {
			memcpy(&cd->reg.account2, reg, sizeof(cd->reg.account2));
			cd->reg.account2_num = num;
		}
	}

	return max;
}

// ##変数の取得
static int get_account_reg2(struct char_session_data *sd,struct global_reg *reg)
{
	int i;

	if(sd == NULL)
		return 0;

	for(i=0;i<max_char_slot;i++) {
		const struct mmo_chardata *cd = sd->found_char[i];
		if(cd) {
			if(cd->reg.account2_num > 0) {
				memcpy(reg, &cd->reg.account2, sizeof(cd->reg.account2));
				return cd->reg.account2_num;
			}
		}
	}
	return 0;
}

// 離婚
static int char_divorce(const struct mmo_charstatus *st)
{
	if(st == NULL)
		return 0;

	if(st->partner_id){
		int i;
		struct mmo_charstatus s1;
		memcpy(&s1,st,sizeof(struct mmo_charstatus));

		// 離婚
		s1.partner_id = 0;

		// 結婚指輪を剥奪
		for(i=0;i<MAX_INVENTORY;i++){
			if(s1.inventory[i].nameid == WEDDING_RING_M || s1.inventory[i].nameid == WEDDING_RING_F){
				memset(&s1.inventory[i],0,sizeof(s1.inventory[0]));
			}
		}
		chardb_save(&s1);
		return 1;
	}

	return 0;
}

// 養子解体
static int char_break_adoption(const struct mmo_charstatus *st)
{
	if(st == NULL)
		return 0;
	if(st->baby_id > 0 || st->parent_id[0] > 0 || st->parent_id[1] > 0) {
		struct mmo_charstatus s1;
		memcpy(&s1,st,sizeof(struct mmo_charstatus));
		// 養子であれば元の職に戻す
		if(s1.class_ >= PC_CLASS_NV_B && s1.class_ <= PC_CLASS_SNV_B) {
			if(s1.class_ == PC_CLASS_SNV_B)
				s1.class_ = PC_CLASS_SNV;
			else
				s1.class_ -= PC_CLASS_NV_B;
		}
		else if(s1.class_ >= PC_CLASS_RK_B && s1.class_ <= PC_CLASS_LG_B) {
			s1.class_ -= PC_CLASS_RK_B;
		}
		else if(s1.class_ >= PC_CLASS_LG_B && s1.class_ <= PC_CLASS_SC_B) {
			s1.class_ -= PC_CLASS_LG_B;
		}
		s1.baby_id = 0;
		s1.parent_id[0] = 0;
		s1.parent_id[1] = 0;
		chardb_save(&s1);
		return 1;
	}

	return 0;
}

// ランキングデータ送信セット
static int char_set_ranking_send(int ranking_id,unsigned char *buf)
{
	WBUFW(buf,0) = 0x2b30;
	WBUFW(buf,2) = 6+sizeof(ranking_data[0]);
	WBUFW(buf,4) = ranking_id;
	memcpy(WBUFP(buf,6), &ranking_data[ranking_id], sizeof(ranking_data[0]));

	return (int)WBUFW(buf,2);
}

// ランキングデータ更新
int compare_ranking_data(const void *a,const void *b)
{
	struct Ranking_Data *p1 = (struct Ranking_Data *)a;
	struct Ranking_Data *p2 = (struct Ranking_Data *)b;

	if(p1->point < p2->point)
		return 1;
	if(p1->point > p2->point)
		return -1;

	return 0;
}

static int char_ranking_update(int ranking_id,int rank,struct Ranking_Data *rd)
{
	if(rd == NULL)
		return 0;
	if(ranking_id < 0 || ranking_id >= MAX_RANKING)
		return 0;

	if(rank >= 0 && rank < MAX_RANKER) {
		// ランカーのポイント更新
		if(ranking_data[ranking_id][rank].char_id == rd->char_id) {
			ranking_data[ranking_id][rank].point = rd->point;
		} else {
			// 順位が変更されている可能性があるので該当キャラを探す
			int i;
			for(i=0; i<MAX_RANKER; i++) {
				if(ranking_data[ranking_id][i].char_id == rd->char_id) {
					ranking_data[ranking_id][i].point = rd->point;
					rank = i;
					break;
				}
			}
			if(i >= MAX_RANKER)	// 見つからない場合もある
				return 0;
		}
	} else if(rank == MAX_RANKER) {
		// 新規ランクイン
		if(ranking_data[ranking_id][MAX_RANKER-1].point < rd->point)
		{
			int i;
			for(i=MAX_RANKER; i>0 && ranking_data[ranking_id][i-1].char_id <= 0; i--);
			if(i == MAX_RANKER)
				i--;
			strncpy(ranking_data[ranking_id][i].name, rd->name, 24);
			ranking_data[ranking_id][i].point   = rd->point;
			ranking_data[ranking_id][i].char_id = rd->char_id;
			rank = i;
		} else {
			return 0;	// ランクインできない場合もある
		}
	} else {
		printf("char_ranking_update: invalid rank %d !!\n",rank);
		return 0;
	}

	// 順位が変動するならソート
	if( (rank > 0 && ranking_data[ranking_id][rank-1].point < rd->point) ||
	    (rank < MAX_RANKER-1 && ranking_data[ranking_id][rank+1].point > rd->point) )
	{
		qsort(ranking_data[ranking_id], MAX_RANKER, sizeof(struct Ranking_Data), compare_ranking_data);
	}

	return 0;
}

// ランキングデータ削除
static int char_ranking_delete(int char_id)
{
	int i,j;

	for(i=0; i<MAX_RANKING; i++) {
		for(j=0; j<MAX_RANKER; j++) {
			if(ranking_data[i][j].char_id == char_id) {
				strncpy(ranking_data[i][j].name, unknown_char_name, 24);
				ranking_data[i][j].point   = 0;
				ranking_data[i][j].char_id = 0;
				break;
			}
		}
		if(j < MAX_RANKER) {
			int len;
			char buf[6+32*MAX_RANKER];

			// ランキングの再構築はしない
			qsort(ranking_data[i], MAX_RANKER, sizeof(struct Ranking_Data), compare_ranking_data);
			len = char_set_ranking_send(i,buf);
			mapif_sendall(buf,len);
		}
	}
	return 0;
}

// キャラ削除に伴うデータ削除
static int char_delete(const struct mmo_chardata *cd)
{
	int j;
	unsigned char buf[8];

	nullpo_retr(-1,cd);

	printf("char_delete: %s\n",cd->st.name);
	// キャラが接続しているかもしれないのでmapに切断要求
	WBUFW(buf,0)=0x2b19;
	WBUFL(buf,2)=cd->st.account_id;
	mapif_sendall(buf,6);

	// ステータス異常削除
	statusdb_delete(cd->st.char_id);

	// クエストリスト削除
	questdb_delete(cd->st.char_id);

	// ROメール削除
	maildb_delete(cd->st.char_id);

	// ランキング削除
	char_ranking_delete(cd->st.char_id);

	// ペット削除
	if(cd->st.pet_id)
		petdb_delete(cd->st.pet_id);
	for(j=0;j<MAX_INVENTORY;j++) {
		if(cd->st.inventory[j].card[0] == (short)0xff00)
			petdb_delete(*((int *)(&cd->st.inventory[j].card[1])));
	}
	for(j=0;j<MAX_CART;j++) {
		if(cd->st.cart[j].card[0] == (short)0xff00)
			petdb_delete(*((int *)(&cd->st.cart[j].card[1])));
	}
	// ホムンクルス削除
	if(cd->st.homun_id)
		homundb_delete(cd->st.homun_id);
	// 傭兵削除
	if(cd->st.merc_id)
		mercdb_delete(cd->st.merc_id);
	// ギルド脱退
	if(cd->st.guild_id)
		inter_guild_leave(cd->st.guild_id, cd->st.account_id, cd->st.char_id);
	// パーティー脱退
	if(cd->st.party_id)
		inter_party_leave(cd->st.party_id, cd->st.account_id, cd->st.char_id);
	// 離婚
	if(cd->st.partner_id){
		const struct mmo_chardata *p_cd = chardb_load(cd->st.partner_id);
		if(p_cd && cd->st.partner_id == p_cd->st.char_id && p_cd->st.partner_id == cd->st.char_id) {
			// 相方が自分と結婚している場合
			// 相方の離婚情報をmapに通知
			WBUFW(buf,0)=0x2b12;
			WBUFL(buf,2)=p_cd->st.char_id;
			mapif_sendall(buf,6);

			// 相方の離婚処理
			char_divorce(&p_cd->st);
		}

		// 自分の離婚処理
		char_divorce(&cd->st);
	}
	chardb_delete_sub(cd->st.char_id);

	return 0;
}

// authfifoの比較
static bool cmp_authfifo(int i,int account_id,int login_id1,int login_id2,unsigned long ip)
{
	if( auth_fifo[i].account_id == account_id && auth_fifo[i].login_id1 == login_id1 )
		return true;

#ifdef CMP_AUTHFIFO_LOGIN2
	if( auth_fifo[i].login_id2 == login_id2 && login_id2 != 0 )
		return true;
#endif

#ifdef CMP_AUTHFIFO_IP
	if( auth_fifo[i].ip == ip && ip != 0 && ip != 0xffffffff )
		return true;
#endif
	return false;
}

// ソケットのデストラクタ
int parse_login_disconnect(int fd)
{
	if (fd == login_fd)
		login_fd = -1;

	return 0;
}

int parse_tologin(int fd)
{
	int i,fdc;
	struct char_session_data *sd;

	//printf("parse_tologin : %d %d %d\n",fd,RFIFOREST(fd),RFIFOW(fd,0));
	sd = (struct char_session_data *)session[fd]->session_data;

	while(RFIFOREST(fd)>=2){
		switch(RFIFOW(fd,0)){
		case 0x2711:
			if(RFIFOREST(fd)<3)
				return 0;
			if(RFIFOB(fd,2)){
				printf("connect login server error : %d\n",RFIFOB(fd,2));
				exit(1);
			}
			RFIFOSKIP(fd,3);
			session[fd]->auth = -1; // 認証終了を socket.c に伝える
			break;

		case 0x2713:
			if(RFIFOREST(fd)<15)
				return 0;
			for(i=0;i<fd_max;i++){
				if(session[i] && (sd = (struct char_session_data *)session[i]->session_data)){
					if(sd->account_id==RFIFOL(fd,2))
						break;
				}
			}
			fdc=i;
			if(fdc==fd_max){
				RFIFOSKIP(fd,15);
				break;
			}
			//printf("parse_tologin 2713 : %d\n",RFIFOB(fd,6));
			if(RFIFOB(fd,6)!=0){
				WFIFOW(fdc,0)=0x6c;
				WFIFOB(fdc,2)=0x42;
				WFIFOSET(fdc,3);
				RFIFOSKIP(fd,15);
				break;
			}
			sd->account_id=RFIFOL(fd,7);
			sd->login_id1=RFIFOL(fd,11);

			if(char_maintenance && isGM(sd->account_id)==0){
				close(fd);
				session[fd]->eof=1;
				return 0;
			}
			if(max_connect_user > 0) {
				if(count_users() < max_connect_user  || isGM(sd->account_id) > 0) {
					mmo_char_send006b(fdc,sd);
				} else {
					WFIFOW(fdc,0)=0x6c;
					WFIFOW(fdc,2)=0;
					WFIFOSET(fdc,3);
				}
			} else {
				mmo_char_send006b(fdc,sd);
			}
			RFIFOSKIP(fd,15);
			break;

		// キャラ削除(メールアドレス確認後)
		case 0x2716:
			if(RFIFOREST(fd)<11)
				return 0;
			{
				int ch;
				for(i=0;i<fd_max;i++){
					if(session[i] && (sd = (struct char_session_data *)session[i]->session_data)){
						if(sd->account_id==RFIFOL(fd,2))
							break;
					}
				}
				fdc=i;
				if(fdc==fd_max){
					RFIFOSKIP(fd,15);
					break;
				}
				if(RFIFOB(fd,10)!=0){
					WFIFOW(fdc,0)=0x70;
					WFIFOB(fdc,2)=1;
					WFIFOSET(fdc,3);
				}else{
					for(i=0;i<max_char_slot;i++){
						const struct mmo_chardata *cd = sd->found_char[i];
						if(cd && cd->st.char_id == RFIFOL(fd,6)){
							char_delete(cd);
							for(ch=i;ch<max_char_slot-1;ch++)
								sd->found_char[ch]=sd->found_char[ch+1];
							sd->found_char[max_char_slot-1] = NULL;
							break;
						}
					}
					if( i==max_char_slot ){
						WFIFOW(fdc,0)=0x70;
						WFIFOB(fdc,2)=0;
						WFIFOSET(fdc,3);
					} else {
						WFIFOW(fdc,0)=0x6f;
						WFIFOSET(fdc,2);
					}
				}
				RFIFOSKIP(fd,11);
			}
			break;
		// キャラ削除(誕生日確認後)
		case 0x2718:
			if( RFIFOREST(fd) < 11 )
				return 0;
			{
				int ch;
				int account_id = RFIFOL(fd,2);
				int char_id = RFIFOL(fd,6);
				for( i = 0 ; i < fd_max; i++ )
				{
					if(session[i] && (sd = (struct char_session_data *)session[i]->session_data))
					{
						if(sd->account_id == account_id)
							break;
					}
				}

				fdc = i;
				if(fdc == fd_max)
				{
					RFIFOSKIP(fd,15);
					break;
				}
				if(RFIFOB(fd,10) != 0)
				{
					WFIFOW(fdc,0) = 0x82a;
					WFIFOL(fdc,2) = char_id;
					WFIFOL(fdc,6) = 5;
					WFIFOSET(fdc,10);
				}
				else
				{
					for( i = 0; i < max_char_slot; i++ )
					{
						const struct mmo_chardata *cd = sd->found_char[i];
						if( cd && cd->st.char_id == char_id )
						{
							if( i >= max_char_slot )
							{
								WFIFOW(fdc,0) = 0x82a;
								WFIFOL(fdc,2) = char_id;
								WFIFOL(fdc,6) = 3;
								WFIFOSET(fdc,10);
								break;
							}
							else if( !cd->st.delete_date || cd->st.delete_date > (unsigned int)time(NULL) )
							{
								WFIFOW(fdc,0) = 0x82a;
								WFIFOL(fdc,2) = char_id;
								WFIFOL(fdc,6) = 4;
								WFIFOSET(fdc,10);
								break;
							}
							else
							{
								char_delete(cd);
								for( ch = i; ch < max_char_slot - 1 ; ch++ )
									sd->found_char[ch] = sd->found_char[ch + 1];
								sd->found_char[max_char_slot - 1] = NULL;
								WFIFOW(fdc,0) = 0x82a;
								WFIFOL(fdc,2) = char_id;
								WFIFOL(fdc,6) = 1;
								WFIFOSET(fdc,10);
								break;
							}
						}
					}
				}
				RFIFOSKIP(fd,11);
			}
			break;

		// gm reply
		case 0x2721:
			{
				// SQL 化が面倒くさいので保留
				unsigned char buf[16];
				if(RFIFOREST(fd)<10)
					return 0;
				RFIFOSKIP(fd,10);
				WBUFW(buf,0)=0x2b0b;
				WBUFL(buf,2)=RFIFOL(fd,2);
				WBUFL(buf,6)=RFIFOL(fd,6);
				mapif_sendall(buf,10);
			}
			break;

		// changesex reply
		case 0x2723:
			if(RFIFOREST(fd)<7)
				return 0;
			{
				int sex = RFIFOB(fd,6);
				unsigned char buf[8];
				struct char_session_data csd;
				struct mmo_charstatus    st;
				int found_char = chardb_load_all(&csd,RFIFOL(fd,2));
				for(i=0;i<found_char;i++){
					int flag = 0;
					memcpy(&st,&csd.found_char[i]->st,sizeof(struct mmo_charstatus));
					// 雷鳥は職も変更
					if(st.class_ == PC_CLASS_BA || st.class_ == PC_CLASS_DC) {
						flag = 1; st.class_ = (sex ? PC_CLASS_BA : PC_CLASS_DC);
					} else if(st.class_ == PC_CLASS_BA_H || st.class_ == PC_CLASS_DC_H) {
						flag = 1; st.class_ = (sex ? PC_CLASS_BA_H : PC_CLASS_DC_H);
					} else if(st.class_ == PC_CLASS_BA_B || st.class_ == PC_CLASS_DC_B) {
						flag = 1; st.class_ = (sex ? PC_CLASS_BA_B : PC_CLASS_DC_B);
					}
					if(flag) {
						// 雷鳥装備外し
						int j;
						for(j=0;j<MAX_INVENTORY;j++) {
							if(st.inventory[j].equip) st.inventory[j].equip=0;
						}
						// 雷鳥スキルリセット
						for(j=0;j<MAX_PCSKILL;j++) {
							if(st.skill[j].id>0 && !st.skill[j].flag){
								st.skill_point += st.skill[j].lv;
								st.skill[j].lv = 0;
							}
						}
						chardb_save(&st);	// キャラデータ変更のセーブ
					}
				}
				WBUFW(buf,0)=0x2b0d;
				WBUFL(buf,2)=RFIFOL(fd,2);
				WBUFB(buf,6)=RFIFOB(fd,6);
				mapif_sendall(buf,7);
				RFIFOSKIP(fd,7);
			}
			break;

		// account_reg2変更通知
		case 0x2729:
			{
				struct global_reg reg[ACCOUNT_REG2_NUM];
				unsigned char buf[ACCOUNT_REG2_NUM*36+16];
				int j,p,acc;
				if(RFIFOREST(fd)<4)
					return 0;
				if(RFIFOREST(fd)<RFIFOW(fd,2))
					return 0;
				acc=RFIFOL(fd,4);
				memset(&reg, 0, sizeof(reg));
				for(p=8,j=0;p<RFIFOW(fd,2) && j<ACCOUNT_REG2_NUM;p+=36,j++){
					strncpy(reg[j].str,RFIFOP(fd,p),32);
					reg[j].str[31] = '\0';	// force \0 terminal
					reg[j].value   = RFIFOL(fd,p+32);
				}
				set_account_reg2(acc,j,reg);
				// 同垢ログインを禁止していれば送る必要は無い
				memcpy(buf,RFIFOP(fd,0),RFIFOW(fd,2));
				WBUFW(buf,0)=0x2b11;
				mapif_sendall(buf,WBUFW(buf,2));
				RFIFOSKIP(fd,RFIFOW(fd,2));
				//printf("char: save_account_reg_reply\n");
			}
			break;

		// アカウント削除通知
		case 0x272a:
			{
				// 該当キャラクターの削除
				struct char_session_data csd;
				int max = chardb_load_all(&csd,RFIFOL(fd,2));
				for(i=0;i<max;i++) {
					char_delete(csd.found_char[i]);
				}
				// 倉庫の削除
				storagedb_delete(RFIFOL(fd,2));
				RFIFOSKIP(fd,6);
			}
			break;

		// charメンテナンス状態変更応答
		case 0x272c:
			{
				unsigned char buf[4];
				if(RFIFOREST(fd)<3)
					return 0;
				WBUFW(buf,0)=0x2b15;
				WBUFB(buf,2)=RFIFOB(fd,2);
				mapif_sendall(buf,3);

				RFIFOSKIP(fd,3);
			}
			break;

		// 暗号化ログインのチャレンジ返答
		case 0x272e:
			{
				if(RFIFOREST(fd)<4 || RFIFOREST(fd)<RFIFOW(fd,2))
					return 0;
				if( RFIFOW(fd,2)>192 || RFIFOW(fd,2)<10 )
				{
					close(fd);
					session[fd]->eof=1;
					return 0;
				}
				// 暗号化ログイン
				WFIFOW(login_fd,0)=0x272f;
				memcpy(WFIFOP(login_fd,2),userid,24);
				HMAC_MD5_Binary( passwd, (int)strlen(passwd), RFIFOP(fd,4), RFIFOW(fd,2)-4, WFIFOP(login_fd,26) );
				WFIFOL(login_fd,42)=0;
				WFIFOL(login_fd,46)=4;	// 暗号化に HMAC-MD5 を使う
				WFIFOL(login_fd,50)=0;
				WFIFOL(login_fd,54)=char_ip;
				WFIFOW(login_fd,58)=char_port;
				memcpy(WFIFOP(login_fd,60),server_name,20);
				WFIFOW(login_fd,80)=char_maintenance;
				WFIFOW(login_fd,82)=char_new;
				WFIFOSET(login_fd,84);

				RFIFOSKIP(login_fd,RFIFOW(fd,2));
			}
			break;

		// 新規ログインのため同一アカウントを切断
		case 0x2730:
			if(RFIFOREST(fd)<6)
				return 0;
			{
				int account_id = RFIFOL(fd,2);
				for(i=0; i<fd_max; i++) {
					if(session[i] && (sd = (struct char_session_data *)session[i]->session_data) && sd->account_id == account_id) {
						WFIFOW(i,0) = 0x81;
						WFIFOB(i,2) = 2;
						WFIFOSET(i,3);
						session[i]->auth = 0;	// 認証取消し
					}
				}

				// 同一アカウントの未認証データを全て破棄しておく
				for( i = 0; i < AUTH_FIFO_SIZE; i++ )
				{
					if( auth_fifo[i].account_id == account_id && !auth_fifo[i].delflag )
						auth_fifo[i].delflag = 1;
				}

				// 全mapサーバに切断要求
				if(numdb_search(char_online_db,account_id))
				{
					unsigned char buf[8];
					WBUFW(buf,0) = 0x2b1a;
					WBUFL(buf,2) = account_id;
					mapif_sendall(buf,6);
				}
				RFIFOSKIP(fd,6);
			}
			break;

		default:
			close(fd);
			session[fd]->eof=1;
			return 0;
		}
	}

	return 0;
}

/*==========================================
 * mapが含まれているmap-serverを探す
 *------------------------------------------
 */
static int search_mapserver(const char *map)
{
	int i, j;

	for(i = 0; i < MAX_MAP_SERVERS; i++) {
		if (server_fd[i] < 0)
			continue;
		for(j = 0; j < server[i].map_num; j++) {
			if (!strncmp(server[i].map + (j * 16), map, 16))
				return i;
		}
	}

	return -1;
}

static int search_mapserver_char(const char *map, struct mmo_charstatus *cd)
{
	int i;

	i = search_mapserver(map);
	if(i != -1) {
		//printf("search_mapserver %s : success -> %d\n", map, i);
		return i;
	}

	if (cd) {
		for(i = 0; i < MAX_MAP_SERVERS; i++) {
			if (server_fd[i] < 0)
				continue;
			if (server[i].map_num > 0) {
				memcpy(cd->last_point.map, server[i].map, 16);
				printf("search_mapserver %s : another map %s -> %d\n", map, server[i].map, i);
				return i;
			}
		}
	}

	printf("search_mapserver failed : %s\n", map);

	return -1;
}

int char_erasemap(int fd, int id)
{
	int i;

	for(i = 0; i < MAX_MAP_SERVERS; i++) {
		int dfd = server_fd[i];
		if(dfd >= 0 && i != id) {
			WFIFORESERVE(dfd, server[id].map_num * 16 + 12);
			WFIFOW(dfd, 0) = 0x2b16;
			WFIFOW(dfd, 2) = server[id].map_num * 16 + 12;
			WFIFOL(dfd, 4) = server[id].ip;
			WFIFOW(dfd, 8) = server[id].port;
			WFIFOW(dfd,10) = server[id].map_num;
			memcpy(WFIFOP(dfd,12), server[id].map, 16 * server[id].map_num);
			WFIFOSET(dfd, WFIFOW(dfd,2));
		}
	}
	printf("char: map erase: %d (%d maps)\n", id, server[id].map_num);

	aFree(server[id].map);
	server[id].map = NULL;
	server[id].map_num = 0;

	return 0;
}

static int parse_map_disconnect_sub(void *key,void *data,va_list ap)
{
	int fd = va_arg(ap,int);
	unsigned long ip    = (unsigned long)va_arg(ap,int);
	unsigned short port = (unsigned short)va_arg(ap,int);
	struct char_online *c = (struct char_online*)data;
	unsigned char buf[8];

	if(c->ip == ip && c->port == port) {
		// printf("char: mapdisconnect %s %08x:%d\n",c->name,ip,port);
		WBUFW(buf,0) = 0x2b17;
		WBUFL(buf,2) = c->char_id;
		mapif_sendallwos(fd,buf,6);
		numdb_erase(char_online_db,key);
		chardb_set_offline( c->char_id );
		aFree(c);
	}

	return 0;
}

int parse_map_disconnect(int fd)
{
	int id;

	for(id = 0; id < MAX_MAP_SERVERS; id++) {
		if (server_fd[id] == fd) {
			server_fd[id] = -1;
			char_erasemap(fd, id);
			// 残っていたキャラの切断を他map-serverに通知
			numdb_foreach(char_online_db, parse_map_disconnect_sub, fd, (int)server[id].ip, (int)server[id].port);
			close(fd);
		}
	}

	return 0;
}

int parse_frommap(int fd)
{
	int i, j;
	int id;

	for(id = 0; id < MAX_MAP_SERVERS; id++) {
		if (server_fd[id] == fd)
			break;
	}
	if (id == MAX_MAP_SERVERS)
		session[fd]->eof = 1;

	//printf("parse_frommap : %d %d %d\n",fd,RFIFOREST(fd),RFIFOW(fd,0));

	while(RFIFOREST(fd)>=2){
		switch(RFIFOW(fd,0)){
		// マップサーバーから担当マップ名を受信
		case 0x2afa:
			if (RFIFOREST(fd) < 4 || RFIFOREST(fd) < RFIFOW(fd,2))
				return 0;
			j = server[id].map_num; // get actual quantity of maps for the server
			for(i = 4; i < RFIFOW(fd,2); i += 16) {
				int k = search_mapserver(RFIFOP(fd,i));
				if (k == -1) { // the map isn't assigned to any server
					// 担当マップサーバーが決まっていないマップなら設定
					if (j == 0) {
						server[id].map = (char *)aMalloc(16 * sizeof(char));
					} else {
						server[id].map = (char *)aRealloc(server[id].map, sizeof(char) * 16 * (j + 1));
					}
					memcpy(server[id].map + (j * 16), RFIFOP(fd,i), 16);
					server[id].map[j * 16 + 15] = '\0';
					j++;
				} else if (k != id) { // if same map-server, it's probably an error (duplicated packet)
					// printf("Error to fix: 2 map-servers have same map: %16s\n", RFIFOP(fd,i));
					// If 2 map-servers manage same mapX, a problem exists with players.
					// When a player change of map, map-server will search at first if it manages the map.
					// So, player1 on map-server1 go on a mapX managed by map-server1. Player1 stay on map-server1.
					// Player2 on map-server2 go on same mapX managed by map-server2 too. Player2 Stays on map-server2.
					// Conclusion: player1 and player2 on same map can not see them!

					// [Eoe]
					// Above case NEVER occures because jA system managed to assign duplicated
					// map entries to ONLY one server. If map server received 0x2b04 packet and
					// notice that loaded maps are assigned to other map server, map server marks
					// loaded maps to other server's map. And if recives other map server crashes
					// packet(0x2b16) and crashed map entries includes the map which is loaded but
					// not assigned, map server requests char server to try assign lacked maps.

					// This systems can create redundancy system by loading "prontera.gat" in
					// two or more servers. If one server encountered serious trouble which cannot
					// recover soon, all players, however, can login to other servers by this system.
				}
			}
			server[id].map_num = j;

			{
				unsigned char *p = (unsigned char *)&server[id].ip;
				printf("set map %d from %d.%d.%d.%d:%d (%d maps)\n", id, p[0], p[1], p[2], p[3], server[id].port, j);
			}

			RFIFOSKIP(fd,RFIFOW(fd,2));

			WFIFOW(fd,0) = 0x2afb;
			WFIFOW(fd,2) = 0; // ok
			WFIFOSET(fd,3);

			for(i = 0; i < MAX_MAP_SERVERS; i++) {
				int dfd = server_fd[i];
				if(dfd < 0)
					continue;

				// 他のマップサーバーに担当マップ情報を送信
				// map 鯖はchar鯖からのこのパケットを受信して初めて
				// 自分が担当するマップが分かる
				WFIFORESERVE(dfd, j * 16 + 12);
				WFIFOW(dfd, 0) = 0x2b04;
				WFIFOW(dfd, 2) = j * 16 + 12;
				WFIFOL(dfd, 4) = server[id].ip;
				WFIFOW(dfd, 8) = server[id].port;
				WFIFOW(dfd,10) = j;
				memcpy(WFIFOP(dfd,12), server[id].map, 16 * j);
				WFIFOSET(dfd, WFIFOW(dfd,2));

				if (i != id && server[i].map_num > 0) {
					// 他のマップサーバーの担当マップを送信
					WFIFOW(fd, 0) = 0x2b04;
					WFIFOW(fd, 2) = server[i].map_num * 16 + 12;
					WFIFOL(fd, 4) = server[i].ip;
					WFIFOW(fd, 8) = server[i].port;
					WFIFOW(fd,10) = server[i].map_num;
					memcpy(WFIFOP(fd, 12), server[i].map, 16 * server[i].map_num);
					WFIFOSET(fd, WFIFOW(fd,2));
				}
			}
			break;

		// 認証要求
		case 0x2afc:
			if(RFIFOREST(fd)<23)
				return 0;
			{
				int account_id   = RFIFOL(fd,2);
				int char_id      = RFIFOL(fd,6);
				int login_id1    = RFIFOL(fd,10);
				int login_id2    = RFIFOL(fd,14);
				unsigned long ip = RFIFOL(fd,18);
				int sex          = RFIFOB(fd,22);
				const struct mmo_chardata *cd = chardb_load(char_id);

				for( i = 0; i < AUTH_FIFO_SIZE; i++ )
				{
					if( cmp_authfifo(i,account_id,login_id1,login_id2,ip) == true &&
					    auth_fifo[i].char_id == char_id &&
					    !auth_fifo[i].delflag )
					{
						auth_fifo[i].delflag = 1;
						break;
					}
				}
				if( cd != NULL && i <= AUTH_FIFO_SIZE && auth_fifo[i].sex == sex )
				{
					unsigned char buf[48];
					struct char_online *c;
					size_t s1 = sizeof(struct mmo_charstatus);
					size_t s2 = sizeof(struct registry);

					WFIFOW(fd,0) = 0x2afd;
					WFIFOW(fd,2) = (unsigned short)(12 + s1 + s2);
					WFIFOL(fd,4) = account_id; // account id
					WFIFOL(fd,8) = auth_fifo[i].login_id2;
					memcpy(WFIFOP(fd,12   ), &cd->st , s1);
					memcpy(WFIFOP(fd,12+s1), &cd->reg, s2);
					WFIFOSET(fd,WFIFOW(fd,2));

					// オンラインdbに挿入
					c = (struct char_online *)numdb_search(char_online_db,account_id);
					if(c == NULL) {
						c = (struct char_online *)aCalloc(1,sizeof(struct char_online));
						numdb_insert(char_online_db,account_id,c);
					}
					c->ip         = server[id].ip;
					c->port       = server[id].port;
					c->account_id = cd->st.account_id;
					c->char_id    = cd->st.char_id;
					memcpy(c->name,cd->st.name,24);
					chardb_set_online( c->char_id );

					// このmap-server以外にログインしたことを通知する
					WBUFW(buf, 0) = 0x2b09;
					WBUFL(buf, 2) = cd->st.char_id;
					memcpy(WBUFP(buf,6),cd->st.name,24);
					WBUFL(buf,30) = cd->st.account_id;
					WBUFL(buf,34) = server[id].ip;
					WBUFW(buf,38) = server[id].port;
					mapif_sendallwos(fd,buf,40);
				}
				else
				{
					WFIFOW(fd,0)=0x2afe;
					WFIFOW(fd,2)=account_id;
					WFIFOB(fd,6)=0;
					WFIFOSET(fd,7);
					printf("auth_fifo search error! %d\n", char_id);
				}
			}
			RFIFOSKIP(fd,23);
			break;

		// MAPサーバー上のユーザー数受信
		case 0x2aff:
			if(RFIFOREST(fd)<6)
				return 0;
			server[id].users=RFIFOL(fd,2);
			RFIFOSKIP(fd,6);
			break;

		// キャラデータ保存
		case 0x2b01:
			if(RFIFOREST(fd)<4 || RFIFOREST(fd)<RFIFOW(fd,2))
				return 0;
			if( ((struct mmo_charstatus*)RFIFOP(fd,12))->char_id != RFIFOL(fd,8) ) {
				// キャラID違いのデータを送ってきたので強制切断
				unsigned char buf[8];
				WBUFW(buf,0) = 0x2b19;
				WBUFL(buf,2) = RFIFOL(fd,4);
				mapif_sendall(buf,6);
			} else {
				chardb_save((struct mmo_charstatus *)RFIFOP(fd,12));
			}
			RFIFOSKIP(fd,RFIFOW(fd,2));
			break;

		// キャラセレ要求
		case 0x2b02:
			if(RFIFOREST(fd)<19)
				return 0;
			{
				int account_id   = RFIFOL(fd,2);
				int login_id1    = RFIFOL(fd,6);
				int login_id2    = RFIFOL(fd,10);
				unsigned long ip = RFIFOL(fd,14);
				int sex          = WFIFOB(fd,18);

				if( auth_fifo_pos >= AUTH_FIFO_SIZE )
					auth_fifo_pos = 0;

				auth_fifo[auth_fifo_pos].account_id = account_id;
				auth_fifo[auth_fifo_pos].char_id    = 0;
				auth_fifo[auth_fifo_pos].login_id1  = login_id1;
				auth_fifo[auth_fifo_pos].login_id2  = login_id2;
				auth_fifo[auth_fifo_pos].delflag    = 2;
				auth_fifo[auth_fifo_pos].ip         = ip;
				auth_fifo[auth_fifo_pos].sex        = sex;
				auth_fifo_pos++;

				WFIFOW(fd,0) = 0x2b03;
				WFIFOL(fd,2) = account_id;
				WFIFOB(fd,6) = 0;
				WFIFOSET(fd,7);
				RFIFOSKIP(fd,19);
			}
			break;

		// マップサーバー間移動要求
		case 0x2b05:
			if(RFIFOREST(fd)<41)
				return 0;
			{
				int account_id = RFIFOL(fd,2);
				int login_id1  = RFIFOL(fd,6);
				int sex        = RFIFOB(fd,40);

				if( auth_fifo_pos >= AUTH_FIFO_SIZE )
					auth_fifo_pos = 0;

				auth_fifo[auth_fifo_pos].account_id = account_id;
				auth_fifo[auth_fifo_pos].char_id    = 0;
				auth_fifo[auth_fifo_pos].login_id1  = login_id1;
				auth_fifo[auth_fifo_pos].delflag    = 2;
				auth_fifo[auth_fifo_pos].ip         = session[fd]->client_addr.sin_addr.s_addr;
				auth_fifo[auth_fifo_pos].sex        = sex;
				auth_fifo_pos++;

				WFIFOW(fd,0)=0x2b06;
				memcpy(WFIFOP(fd,2),RFIFOP(fd,2),38);
				WFIFOL(fd,6)=0;
				WFIFOSET(fd,40);
				RFIFOSKIP(fd,41);
			}
			break;

		// キャラ名検索
		case 0x2b08:
			if(RFIFOREST(fd)<6)
				return 0;
			{
				const struct mmo_chardata *cd = chardb_load(RFIFOL(fd,2));
				WFIFOW(fd,0) = 0x2b09;
				WFIFOL(fd,2) = RFIFOL(fd,2);
				if(cd){
					struct char_online* c = (struct char_online *)numdb_search(char_online_db,cd->st.account_id);
					memcpy(WFIFOP(fd,6),cd->st.name,24);
					WFIFOL(fd,30) = cd->st.account_id;
					WFIFOL(fd,34) = (c && c->char_id == cd->st.char_id ? c->ip   : 0);
					WFIFOW(fd,38) = (c && c->char_id == cd->st.char_id ? c->port : 0);
				} else {
					memcpy(WFIFOP(fd,6),unknown_char_name,24);
					WFIFOL(fd,30)=0;
					WFIFOL(fd,34)=0;
					WFIFOW(fd,38)=0;
				}
				WFIFOSET(fd,40);
				RFIFOSKIP(fd,6);
			}
			break;

		// GMになりたーい
		case 0x2b0a:
			if(RFIFOREST(fd)<4)
				return 0;
			if(RFIFOREST(fd)<RFIFOW(fd,2))
				return 0;
			if (login_fd >= 0 && session[login_fd])
			{
				memcpy(WFIFOP(login_fd,2),RFIFOP(fd,2),RFIFOW(fd,2)-2);
				WFIFOW(login_fd,0)=0x2720;
				WFIFOSET(login_fd,RFIFOW(fd,2));
			}
			//printf("char : change gm -> login %d %s %d\n",RFIFOL(fd,4),RFIFOP(fd,8),RFIFOW(fd,2));
			RFIFOSKIP(fd,RFIFOW(fd,2));
			break;

		// 性別変換要求
		case 0x2b0c:
			if(RFIFOREST(fd)<4)
				return 0;
			if(RFIFOREST(fd)<RFIFOW(fd,2))
				return 0;
			if (login_fd >= 0 && session[login_fd])
			{
				WFIFOW(login_fd,0) = 0x2722;
				WFIFOW(login_fd,2) = RFIFOW(fd,2);
				WFIFOL(login_fd,4) = RFIFOL(fd,4);
				WFIFOB(login_fd,8) = RFIFOB(fd,8);
				WFIFOSET(login_fd,RFIFOW(fd,2));
			}
			//printf("char : change sex -> login %d %d %d \n",RFIFOL(fd,4),RFIFOB(fd,8),RFIFOW(fd,2));
			RFIFOSKIP(fd,RFIFOW(fd,2));
			break;

		// account_reg保存要求
		case 0x2b10:
			{
				struct global_reg reg[ACCOUNT_REG2_NUM];
				int p,acc;
				if(RFIFOREST(fd)<4)
					return 0;
				if(RFIFOREST(fd)<RFIFOW(fd,2))
					return 0;
				acc=RFIFOL(fd,4);
				memset(&reg, 0, sizeof(reg));
				for(p=8,j=0;p<RFIFOW(fd,2) && j<ACCOUNT_REG2_NUM;p+=36,j++){
					strncpy(reg[j].str,RFIFOP(fd,p),32);
					reg[j].str[31] = '\0';	// force \0 terminal
					reg[j].value   = RFIFOL(fd,p+32);
				}
				set_account_reg2(acc,j,reg);
				// loginサーバーへ送る
				if (login_fd >= 0 && session[login_fd])
				{
					memcpy(WFIFOP(login_fd,0),RFIFOP(fd,0),RFIFOW(fd,2));
					WFIFOW(login_fd,0) = 0x2728;
					WFIFOSET(login_fd,WFIFOW(login_fd,2));
				}
				// ワールドへの同垢ログインがなければmapサーバーに送る必要はない
				//memcpy(buf,RFIFOP(fd,0),RFIFOW(fd,2));
				//WBUFW(buf,0)=0x2b11;
				//mapif_sendall(buf,WBUFW(buf,2));
				RFIFOSKIP(fd,RFIFOW(fd,2));
				//printf("char: save_account_reg (from map)\n");
			}
			break;

		// mapサーバ有効化
		case 0x2b13:
			if(RFIFOREST(fd)<3)
				return 0;
			server[id].active=RFIFOB(fd,2);
			printf("char: map %s: %d\n",(server[id].active)? "active": "inactive",id);
			RFIFOSKIP(fd,3);
			break;

		// charサーバメンテナンス状態に
		case 0x2b14:
			if(RFIFOREST(fd)<3)
				return 0;
			char_maintenance=RFIFOB(fd,2);
			printf("char: maintenance: %d\n",char_maintenance);
			// loginに通知
			if (login_fd >= 0 && session[login_fd])
			{
				WFIFOW(login_fd,0)=0x272b;
				WFIFOB(login_fd,2)=char_maintenance;
				WFIFOSET(login_fd,3);
			}
			RFIFOSKIP(fd,3);
			break;

		// キャラクター切断を他mapに通知
		case 0x2b18:
			if(RFIFOREST(fd)<10)
				return 0;
			{
				struct char_online *c = (struct char_online *)numdb_erase(char_online_db,RFIFOL(fd,2));
				if(c) {
					unsigned char buf[8];
					chardb_set_offline( c->char_id );
					aFree(c);
					WBUFW(buf,0) = 0x2b17;
					WBUFL(buf,2) = RFIFOL(fd,6);
					mapif_sendallwos(fd,buf,6);
				}
				RFIFOSKIP(fd,10);
			}
			break;

		// 離婚
		case 0x2b20:
			if(RFIFOREST(fd)<6)
				return 0;
			{
				const struct mmo_chardata *cd1 = chardb_load(RFIFOL(fd,2));
				if( cd1 && cd1->st.partner_id ) {
					unsigned char buf[8];
					// 離婚情報をmapに通知
					WBUFW(buf,0)=0x2b12;
					WBUFL(buf,2)=cd1->st.char_id;
					mapif_sendall(buf,6);
					char_divorce(&cd1->st);
				}
				RFIFOSKIP(fd,6);
			}
			break;

		// 友達リスト削除
		case 0x2b24:
			if( RFIFOREST(fd)<18 )
				return 0;
			{
				const struct mmo_chardata *cpcd = chardb_load(RFIFOL(fd,6));

				if(cpcd) {
					unsigned char buf[32];
					struct mmo_charstatus st = cpcd->st;

					for( i=0; i<st.friend_num; i++ )
					{
						if( st.friend_data[i].account_id == RFIFOL(fd,10) &&
							st.friend_data[i].char_id == RFIFOL(fd,14) )
						{
							st.friend_num--;
							memmove( &st.friend_data[i], &st.friend_data[i+1], sizeof(st.friend_data[0])*(st.friend_num-i) );
							break;
						}
					}
					chardb_save(&st);

					memcpy( buf, RFIFOP(fd,0), 18 );
					WBUFW(buf,0) = 0x2b25;
					mapif_sendallwos(fd,buf,18);
				}
				RFIFOSKIP(fd,18);
			}
			break;

		// 友達リストオンライン通知
		case 0x2b26:
			if( RFIFOREST(fd)<4 || RFIFOREST(fd)<RFIFOW(fd,2) )
				return 0;
			if( RFIFOW(fd,2) <= MAX_FRIEND*8+16 )
			{
				unsigned char buf[MAX_FRIEND*8+32];
				memcpy( buf, RFIFOP(fd,0), RFIFOW(fd,2) );
				WBUFW(buf,0) = 0x2b27;
				mapif_sendallwos(fd,buf,RFIFOW(fd,2));
			}
			RFIFOSKIP(fd,RFIFOW(fd,2));
			break;

		// 養子解体
		case 0x2b28:
			if(RFIFOREST(fd)<30)
				return 0;
			{
				const struct mmo_chardata *cd1 = chardb_load(RFIFOL(fd,2));
				if( cd1 && (cd1->st.baby_id || cd1->st.parent_id[0] || cd1->st.parent_id[1]) ) {
					unsigned char buf[32];
					// 養子解体情報をmapに通知
					WBUFW(buf,0)=0x2b29;
					WBUFL(buf,2)=cd1->st.char_id;
					memcpy(WBUFP(buf,6), RFIFOP(fd,6), 24);
					mapif_sendall(buf,30);
					char_break_adoption(&cd1->st);
				}
				RFIFOSKIP(fd,30);
			}
			break;

		// キャラ永続変数の保存要求
		case 0x2b2d:
			{
				struct global_reg reg[GLOBAL_REG_NUM];
				int p,account_id,char_id;
				if(RFIFOREST(fd)<4)
					return 0;
				if(RFIFOREST(fd)<RFIFOW(fd,2))
					return 0;
				account_id = RFIFOL(fd,4);
				char_id    = RFIFOL(fd,8);
				memset(&reg, 0, sizeof(reg));
				for(i=0,p=12; p<RFIFOW(fd,2) && i<GLOBAL_REG_NUM ;i++,p+=36) {
					strncpy(reg[i].str,RFIFOP(fd,p),32);
					reg[i].str[31] = '\0';	// force \0 terminal
					reg[i].value   = RFIFOL(fd,p+32);
				}
				chardb_save_reg(account_id,char_id,i,reg);
				RFIFOSKIP(fd,RFIFOW(fd,2));
			}
			break;

		// ランキングデータ取得要求
		case 0x2b2e:
			if(RFIFOREST(fd) < 2)
				return 0;

			for(i=0; i<MAX_RANKING; i++) {
				int len = char_set_ranking_send(i,WFIFOP(fd,0));
				WFIFOSET(fd,len);
			}
			RFIFOSKIP(fd,2);
			break;

		// ランキングデータ更新
		case 0x2b2f:
			if(RFIFOREST(fd) < 4 || RFIFOREST(fd) < RFIFOW(fd,2))
				return 0;
			{
				int len;
				int ranking_id = (int)RFIFOW(fd,4);
				char buf[6+MAX_RANKER*32];

				char_ranking_update(ranking_id,(int)RFIFOW(fd,6),(struct Ranking_Data *)RFIFOP(fd,8));

				// 全MAPサーバにデータをフラッシュ
				len = char_set_ranking_send(ranking_id,buf);
				mapif_sendall(buf,len);

				RFIFOSKIP(fd,RFIFOW(fd,2));
			}
			break;

		default:
			// inter server処理に渡す
			{
				int r=inter_parse_frommap(fd);
				if( r==1 )	break;		// 処理できた
				if( r==2 )	return 0;	// パケット長が足りない
			}

			// inter server処理でもない場合は切断
			printf("char: unknown packet %x! (from map)\n",RFIFOW(fd,0));
			close(fd);
			session[fd]->eof=1;
			return 0;
		}
	}

	return 0;
}

// char_mapifの初期化処理（現在はinter_mapif初期化のみ）
static int char_mapif_init(int fd)
{
	return inter_mapif_init(fd);
}

int parse_char_disconnect(int fd)
{
	if (fd == login_fd)
		login_fd = -1;

	return 0;
}

// 他マップにログインしているキャラクター情報を送信する
static int parse_char_sendonline(void *key,void *data,va_list ap)
{
	int fd = va_arg(ap,int);
	struct char_online *c = (struct char_online*)data;

	WFIFOW(fd, 0) = 0x2b09;
	WFIFOL(fd, 2) = c->char_id;
	memcpy(WFIFOP(fd,6),c->name,24);
	WFIFOL(fd,30) = c->account_id;
	WFIFOL(fd,34) = c->ip;
	WFIFOW(fd,38) = c->port;
	WFIFOSET(fd,40);

	return 0;
}

int parse_char(int fd)
{
	int i,ch;
	unsigned short cmd;
	struct char_session_data *sd;

	if (login_fd < 0) {
		session[fd]->eof = 1;
		return 0;
	}

	sd = (struct char_session_data *)session[fd]->session_data;

	while(RFIFOREST(fd)>=2){
		cmd = RFIFOW(fd,0);
		// crc32のスキップ用
		if( sd == NULL &&					// 未ログインor管理パケット
		    RFIFOREST(fd) >= 4 &&				// 最低バイト数制限 ＆ 0x7530,0x7532管理パケ除去
		    RFIFOREST(fd) <= 21 &&				// 最大バイト数制限 ＆ サーバーログイン除去
		    cmd != 0x20b &&					// md5通知パケット除去
		    cmd != 0x228 &&
		    cmd != 0x2b2a &&					// map鯖暗号化ログイン除去
		    (RFIFOREST(fd) < 6 || RFIFOW(fd,4) == 0x65) )	// 次に何かパケットが来てるなら、接続でないとだめ
		{
			RFIFOSKIP(fd,4);
			cmd = RFIFOW(fd,0);
			//printf("parse_char : %d crc32 skipped\n",fd);
			if(RFIFOREST(fd)==0)
				return 0;
		}

		//if(cmd<30000 && cmd!=0x187)
		//	printf("parse_char : %d %d %d\n",fd,RFIFOREST(fd),cmd);

		// 不正パケットの処理
		if( sd == NULL && cmd != 0x65 && cmd != 0x20b && cmd != 0x187 && cmd != 0x258 && cmd != 0x228 &&
		    cmd != 0x7e5 && cmd != 0x7e7 && cmd != 0x827 && cmd != 0x829 && cmd != 0x82b && cmd != 0x2af8 && cmd != 0x7530 && cmd != 0x7532 && cmd != 0x2b2a && cmd != 0x2b2c )
			cmd = 0xffff;	// パケットダンプを表示させる

		switch(cmd) {
		case 0x20b:		// 20040622暗号化ragexe対応
			if(RFIFOREST(fd)<19)
				return 0;
			RFIFOSKIP(fd,19);
			break;

		case 0x258:		// 20051214 nProtect関係 Part 1
			memset(WFIFOP(fd,0),0,18);
			WFIFOW(fd,0)=0x0227;
			WFIFOSET(fd,18);
			RFIFOSKIP(fd,2);
			break;

		case 0x228:		// 20051214 nProtect関係 Part 2
			if(RFIFOREST(fd)<18)
				return 0;
			WFIFOW(fd,0)=0x0259;
			WFIFOB(fd,2)=2;
			WFIFOSET(fd,3);
			RFIFOSKIP(fd,18);
			break;

		case 0x65:	// 接続要求
			if( RFIFOREST(fd) < 17 )
				return 0;
			{
				int account_id  = RFIFOL(fd,2);
				int login_id1   = RFIFOL(fd,6);
				int login_id2   = RFIFOL(fd,10);
				//int client_type = RFIFOW(fd,14);
				int sex         = RFIFOB(fd,16);

				if( sd == NULL )
				{
					session[fd]->session_data = aCalloc(1,sizeof(*sd));
					sd = (struct char_session_data *)session[fd]->session_data;
				}
				sd->account_id = account_id;
				sd->login_id1  = login_id1;
				sd->login_id2  = login_id2;
				sd->sex        = sex;
				sd->state      = CHAR_STATE_WAITAUTH;
				WFIFOL(fd,0) = account_id;
				WFIFOSET(fd,4);

				for( i = 0; i < AUTH_FIFO_SIZE; i++ )
				{
					if( cmp_authfifo(i,sd->account_id,sd->login_id1,sd->login_id2,session[fd]->client_addr.sin_addr.s_addr) == true &&
					    auth_fifo[i].delflag == 2 )
					{
						auth_fifo[i].delflag = 1;
						sd->account_id       = auth_fifo[i].account_id;
						sd->login_id1        = auth_fifo[i].login_id1;
						sd->login_id2        = auth_fifo[i].login_id2;
						break;
					}
				}
				if( i <= AUTH_FIFO_SIZE )
				{
					// メンテナンス中
					if( char_maintenance && isGM(sd->account_id) == 0 )
					{
						close(fd);
						session[fd]->eof = 1;
						return 0;
					}

					// 接続人数制限中
					if( max_connect_user > 0 )
					{
						if( count_users() < max_connect_user || isGM(sd->account_id) > 0 )
							mmo_char_send006b(fd,sd);
						else
						{
							WFIFOW(fd,0)=0x6c;
							WFIFOW(fd,2)=0;
							WFIFOSET(fd,3);
						}
					}

					// 0x6b送信
					else
						mmo_char_send006b(fd,sd);
				}
				else
				{
					if( login_fd >= 0 && session[login_fd] )
					{
						WFIFOW(login_fd, 0)=0x2712;
						WFIFOL(login_fd, 2)=sd->account_id;
						WFIFOL(login_fd, 6)=sd->login_id1;
						WFIFOL(login_fd,10)=sd->login_id2;
						WFIFOB(login_fd,14)=sd->sex;
						WFIFOL(login_fd,15)=session[fd]->client_addr.sin_addr.s_addr;
						WFIFOSET(login_fd,19);
					}
				}
			}
			RFIFOSKIP(fd,17);
			break;

		case 0x66:	// キャラ選択
			if( RFIFOREST(fd) < 3 )
				return 0;
			{
				struct char_online *c;
				struct mmo_charstatus st;

				for( ch = 0; ch < max_char_slot; ch++ )
				{
					if( sd->found_char[ch] && sd->found_char[ch]->st.char_num == RFIFOB(fd,2) )
						break;
				}
				RFIFOSKIP(fd,3);
				if( ch >= max_char_slot )
					break;

				charlog_log("char select %d - %d %s",sd->account_id,sd->found_char[ch]->st.char_num,sd->found_char[ch]->st.name);
				memcpy(&st,&sd->found_char[ch]->st,sizeof(struct mmo_charstatus));

				i = search_mapserver_char(st.last_point.map, NULL);
				if( i < 0 )
				{
					if( default_map_type & 1 )
					{
						memcpy(st.last_point.map,default_map_name,16);
						i = search_mapserver_char(st.last_point.map,NULL);
					}
					if( default_map_type & 2 && i < 0 )
						i = search_mapserver_char(st.last_point.map,&st);
					if( i >= 0 )
					{
						// 現在地が書き換わったので上書き
						chardb_save(&st);
					}
				}
				if( strstr(st.last_point.map,".gat") == NULL && strlen(st.last_point.map) < 20 )
				{
					strcat(st.last_point.map,".gat");
					chardb_save(&st);
				}
				if( i < 0 || server[i].active == 0 )
				{
					WFIFOW(fd,0)=0x6c;
					WFIFOW(fd,2)=0;
					WFIFOSET(fd,3);
					break;
				}
				// ２重ログイン撃退（違うマップサーバの場合）
				// 同じマップサーバの場合は、マップサーバー内で処理される
				c = (struct char_online *)numdb_search(char_online_db,sd->found_char[ch]->st.account_id);
				if( c && (c->ip != server[i].ip || c->port != server[i].port) )
				{
					// ２重ログイン検出
					// mapに切断要求
					unsigned char buf[8];
					WBUFW(buf,0) = 0x2b1a;
					WBUFL(buf,2) = sd->account_id;
					mapif_sendall(buf,6);

					// 接続失敗送信
					WFIFOW(fd,0) = 0x6c;
					WFIFOW(fd,2) = 0;
					WFIFOSET(fd,3);
					break;
				}

				WFIFOW(fd,0) = 0x71;
				WFIFOL(fd,2) = st.char_id;
				memcpy(WFIFOP(fd,6),st.last_point.map,16);
				WFIFOL(fd,22) = server[i].ip;
				WFIFOW(fd,26) = server[i].port;
				WFIFOSET(fd,28);

				// 同一アカウントの未認証データを全て破棄しておく
				for( i = 0; i < AUTH_FIFO_SIZE; i++ )
				{
					if( auth_fifo[i].account_id == sd->account_id && !auth_fifo[i].delflag )
						auth_fifo[i].delflag = 1;
				}
				if( auth_fifo_pos >= AUTH_FIFO_SIZE )
					auth_fifo_pos = 0;
				auth_fifo[auth_fifo_pos].account_id = sd->account_id;
				auth_fifo[auth_fifo_pos].char_id    = st.char_id;
				auth_fifo[auth_fifo_pos].login_id1  = sd->login_id1;
				auth_fifo[auth_fifo_pos].login_id2  = sd->login_id2;
				auth_fifo[auth_fifo_pos].delflag    = 0;
				auth_fifo[auth_fifo_pos].sex        = sd->sex;
				auth_fifo_pos++;
			}
			break;

		case 0x67:	// 作成
			if(RFIFOREST(fd)<37)
				return 0;
			{
				int flag=0x04;
				int i = 0;
				const struct mmo_chardata *cd = chardb_make(sd->account_id,RFIFOP(fd,2),&flag);
				const struct mmo_charstatus *st;
				struct global_reg reg[ACCOUNT_REG2_NUM];
#if PACKETVER >= 8
				int len = 108;
#else
				int len = 106;
#endif

#ifdef NEW_006b_RE
				len += 4;
#endif

#if PACKETVER > 28 && PACKETVER < 30 || PACKETVER > 30
				len += 16;
#endif

#if PACKETVER > 30
				len += 4;
#endif

				if(cd == NULL){
					WFIFOW(fd,0)=0x6e;
					WFIFOB(fd,2)=flag;
					WFIFOSET(fd,3);
					RFIFOSKIP(fd,37);
					break;
				}

				st = &cd->st;
				memset(WFIFOP(fd,2),0x00,len);
				WFIFOW(fd,0)     = 0x6d;
				WFIFOL(fd,2    ) = st->char_id;
				WFIFOL(fd,2+  4) = st->base_exp;
				WFIFOL(fd,2+  8) = st->zeny;
				WFIFOL(fd,2+ 12) = st->job_exp;
				WFIFOL(fd,2+ 16) = st->job_level;
				WFIFOL(fd,2+ 28) = st->karma;
				WFIFOL(fd,2+ 32) = st->manner;
				WFIFOW(fd,2+ 40) = 0x30;
#ifdef NEW_006b_RE
				WFIFOL(fd,2+ 42) = st->hp;
				WFIFOL(fd,2+ 46) = st->max_hp;
				i = 4;
#else
				WFIFOW(fd,2+ 42) = (st->hp     > 0x7fff) ? 0x7fff : st->hp;
				WFIFOW(fd,2+ 44) = (st->max_hp > 0x7fff) ? 0x7fff : st->max_hp;
#endif
				WFIFOW(fd,2+ 46 + i) = (st->sp     > 0x7fff) ? 0x7fff : st->sp;
				WFIFOW(fd,2+ 48 + i) = (st->max_sp > 0x7fff) ? 0x7fff : st->max_sp;
				WFIFOW(fd,2+ 50 + i) = DEFAULT_WALK_SPEED; // char_dat[i].speed;
				WFIFOW(fd,2+ 52 + i) = st->class_;
				WFIFOW(fd,2+ 54 + i) = st->hair;
				WFIFOW(fd,2+ 58 + i) = st->base_level;
				WFIFOW(fd,2+ 60 + i) = st->skill_point;
				WFIFOW(fd,2+ 64 + i) = st->shield;
				WFIFOW(fd,2+ 66 + i) = st->head_top;
				WFIFOW(fd,2+ 68 + i) = st->head_mid;
				WFIFOW(fd,2+ 70 + i) = st->hair_color;
				memcpy( WFIFOP(fd,2+74 + i), st->name, 24 );
				WFIFOB(fd,2+ 98 + i) = (st->str  > 255) ? 255 : st->str;
				WFIFOB(fd,2+ 99 + i) = (st->agi  > 255) ? 255 : st->agi;
				WFIFOB(fd,2+100 + i) = (st->vit  > 255) ? 255 : st->vit;
				WFIFOB(fd,2+101 + i) = (st->int_ > 255) ? 255 : st->int_;
				WFIFOB(fd,2+102 + i) = (st->dex  > 255) ? 255 : st->dex;
				WFIFOB(fd,2+103 + i) = (st->luk  > 255) ? 255 : st->luk;
				WFIFOW(fd,2+104 + i) = st->char_num;
				if(len >= (108+i))
					WFIFOW(fd,2+106+i) = 1;
				if(len >= (124+i))
					memcpy(WFIFOP(fd,2+108+i),st->last_point.map,16);
				if(len >= (128+i))
					WFIFOL(fd,2+124+i) = st->delete_date;
				WFIFOSET(fd,len+2);
				RFIFOSKIP(fd,37);

				for(ch=0;ch<max_char_slot;ch++) {
					if(sd->found_char[ch] == NULL) {
						sd->found_char[ch] = cd;
						break;
					}
				}
				// ##変数を再設定する
				i = get_account_reg2(sd,reg);
				if(i > 0)
					set_account_reg2(sd->account_id,i,reg);
			}

		case 0x68:	// 削除
			if(RFIFOREST(fd)<46)
				return 0;
			if (login_fd >= 0) {
				WFIFOW(login_fd,0)=0x2715;
				WFIFOL(login_fd,2)=sd->account_id;
				WFIFOL(login_fd,6)=RFIFOL(fd,2);
				memcpy(WFIFOP(login_fd,10), RFIFOP(fd,6), 40);
				WFIFOSET(login_fd,50);
			}
			RFIFOSKIP(fd,46);
			break;

		case 0x2b2a:	// マップサーバー暗号化ログインのチャレンジ要求
			RFIFOSKIP(fd, 2);
			if(sd) {
				printf("char: illegal md5key request.");
				close(fd);
				session[fd]->eof=1;
				return 0;
			} else {
				struct cram_session_data *csd=(struct cram_session_data *)(session[fd]->session_data=aCalloc(1,sizeof(struct cram_session_data)));

				// 暗号化用のチャレンジ生成
				csd->md5keylen = atn_rand()%(sizeof(csd->md5key)/4)+(sizeof(csd->md5key)-sizeof(csd->md5key)/4);
				for(i=0;i<csd->md5keylen;i++)
					csd->md5key[i]=atn_rand()%255+1;

				WFIFOW(fd,0)= 0x2b2b;
				WFIFOW(fd,2)=4+csd->md5keylen;
				memcpy(WFIFOP(fd,4),csd->md5key,csd->md5keylen);
				WFIFOSET(fd,WFIFOW(fd,2));
			}
			break;

		case 0x2af8:	// マップサーバーログイン (map-server connection)
		case 0x2b2c:	// マップサーバー暗号化ログイン
		{
			int authok=0;
			struct cram_session_data *csd=(struct cram_session_data *)(session[fd]->session_data);
			if (RFIFOREST(fd) < 60)
				return 0;
			if (char_sport != 0 && char_port != char_sport && session[fd]->server_port != char_sport) {
				printf("server login failed: connected port %d\n", session[fd]->server_port);
				session[fd]->eof = 1;
				RFIFOSKIP(fd,60);
				return 0;
			}
			// search an available place
			for(i = 0; i < MAX_MAP_SERVERS; i++) {
				if (server_fd[i] < 0)
					break;
			}
			// 暗号化ログイン
			if( RFIFOW(fd,0)==0x2b2c )
			{
				if( RFIFOW(fd,46) == 4 && csd && csd->md5keylen )	// HMAC-MD5
				{
					char md5bin[16];
					HMAC_MD5_Binary( passwd, (int)strlen(passwd), csd->md5key, csd->md5keylen, md5bin );
					authok = ( memcmp( md5bin, RFIFOP(fd,26), 16 ) == 0 );
				}
			}
			else
			{
				authok = (strcmp(RFIFOP(fd,26), passwd) == 0 );
			}
			// いらないセッション情報は削除
			if( sd )
			{
				aFree( csd );
				session[fd]->session_data = NULL;
			}
			if (i == MAX_MAP_SERVERS || strcmp(RFIFOP(fd,2), userid) || !authok ) {
				WFIFOW(fd,0)=0x2af9;
				WFIFOB(fd,2)=3;
				WFIFOSET(fd,3);
				RFIFOSKIP(fd,60);
			} else {
				WFIFOW(fd,0)=0x2af9;
				WFIFOB(fd,2)=0;
				session[fd]->func_parse = parse_frommap;
				session[fd]->func_destruct = parse_map_disconnect;
				server_fd[i] = fd;
				server[i].ip = RFIFOL(fd,54);
				server[i].port = RFIFOW(fd,58);
				server[i].users = 0;
				server[i].map_num = 0;
				if (server[i].map != NULL) {
					aFree(server[i].map);
					server[i].map = NULL;
				}
				WFIFOSET(fd,3);
				numdb_foreach(char_online_db,parse_char_sendonline,fd);
				RFIFOSKIP(fd,60);
				session[fd]->auth = -1; // 認証終了を socket.c に伝える
				realloc_fifo(fd, RFIFOSIZE_SERVERLINK, WFIFOSIZE_SERVERLINK);
				char_mapif_init(fd);
				return 0;
			}
			break;
		}

		case 0x187:	// Alive信号？
			if (RFIFOREST(fd) < 6)
				return 0;
			WFIFOW(fd,0)=0x187;
			WFIFOL(fd,2)=sd->account_id;
			WFIFOSET(fd,6);
			RFIFOSKIP(fd, 6);
			break;

		case 0x7e5:
			if (RFIFOREST(fd) < 8)
				return 0;
			WFIFOW(fd,0) = 0x7e9;
			WFIFOW(fd,2) = 5;
			WFIFOB(fd,4) = 1;
			WFIFOSET(fd,5);
			RFIFOSKIP(fd,8);
			break;

		case 0x7e7:
			if (RFIFOREST(fd) < 32)
				return 0;
			WFIFOW(fd,0) = 0x7e9;
			WFIFOW(fd,2) = 5;
			WFIFOB(fd,4) = 1;
			WFIFOSET(fd,5);
			RFIFOSKIP(fd,32);
			break;

		case 0x827:
			if (RFIFOREST(fd) < 6)
				return 0;
			{
				struct mmo_charstatus st;
				int char_id = RFIFOL(fd,2);

				for( ch = 0; ch < max_char_slot; ch++ )
				{
					if(sd->found_char[ch] && sd->found_char[ch]->st.char_id == char_id)
						break;
				}

				if(ch >= max_char_slot)
				{
					WFIFOW(fd,0) = 0x828;
					WFIFOL(fd,2) = char_id;
					WFIFOL(fd,6) = 3;
					WFIFOL(fd,10) = 0;
					WFIFOSET(fd,14);
					RFIFOSKIP(fd,6);
					break;
				}

				memcpy(&st,&sd->found_char[ch]->st,sizeof(struct mmo_charstatus));
				if(st.delete_date)
				{
					WFIFOW(fd,0) = 0x828;
					WFIFOL(fd,2) = char_id;
					WFIFOL(fd,6) = 0;
					WFIFOL(fd,10) = 0;
					WFIFOSET(fd,14);
					RFIFOSKIP(fd,6);
					break;
				}

				st.delete_date = (unsigned int)time(NULL) + delete_delay_time;
				chardb_save(&st);
				WFIFOW(fd,0) = 0x828;
				WFIFOL(fd,2) = char_id;
				WFIFOL(fd,6) = 1;
				WFIFOL(fd,10) = st.delete_date&0xffffffff;
				WFIFOSET(fd,14);
				RFIFOSKIP(fd,6);
				break;
			}

		case 0x829:
			if (RFIFOREST(fd) < 12)
				return 0;
			{
				int char_id = RFIFOL(fd,2);
				char birth[7];

				memcpy(birth,RFIFOP(fd,6),6);
				birth[6] = '\0';

				if(login_fd >= 0)
				{
					WFIFOW(login_fd,0)=0x2717;
					WFIFOL(login_fd,2)=sd->account_id;
					WFIFOL(login_fd,6)=char_id;
					memcpy(WFIFOP(login_fd,10), birth, 7);
					WFIFOSET(login_fd,17);
				}
				RFIFOSKIP(fd,12);
				break;
			}

		case 0x82b:
			if (RFIFOREST(fd) < 6)
				return 0;
			{
				struct mmo_charstatus st;
				int char_id = RFIFOL(fd,2);

				for( ch = 0; ch < max_char_slot; ch++ )
				{
					if(sd->found_char[ch] && sd->found_char[ch]->st.char_id == char_id)
						break;
				}

				if(ch >= max_char_slot)
				{
					WFIFOW(fd,0) = 0x82c;
					WFIFOL(fd,2) = char_id;
					WFIFOL(fd,6) = 2;
					WFIFOSET(fd,10);
					RFIFOSKIP(fd,6);
					break;
				}

				memcpy(&st,&sd->found_char[ch]->st,sizeof(struct mmo_charstatus));
				st.delete_date = 0;
				chardb_save(&st);
				WFIFOW(fd,0) = 0x82c;
				WFIFOL(fd,2) = char_id;
				WFIFOL(fd,6) = 1;
				WFIFOSET(fd,10);
				RFIFOSKIP(fd,6);
				break;
			}

		case 0x7530:	// Auriga情報取得
			WFIFOW(fd,0)=0x7531;
			WFIFOB(fd,2)=AURIGA_MAJOR_VERSION;
			WFIFOB(fd,3)=AURIGA_MINOR_VERSION;
			WFIFOW(fd,4)=AURIGA_REVISION;
			WFIFOB(fd,6)=AURIGA_RELEASE_FLAG;
			WFIFOB(fd,7)=AURIGA_OFFICIAL_FLAG;
			WFIFOB(fd,8)=AURIGA_SERVER_INTER | AURIGA_SERVER_CHAR;
			WFIFOW(fd,9)=get_current_version();
			WFIFOSET(fd,11);
			RFIFOSKIP(fd,2);
			return 0;
		case 0x7532:	// 接続の切断(defaultと処理は一緒だが明示的にするため)
			RFIFOSKIP(fd,2);
			close(fd);
			session[fd]->eof=1;
			return 0;

		default:
#ifdef DUMP_UNKNOWN_PACKET
			hex_dump(stdout, RFIFOP(fd,0), RFIFOREST(fd));
			printf("\n");
#endif
			close(fd);
			session[fd]->eof=1;
			return 0;
		}
	}

	return 0;
}

// 全てのMAPサーバーにデータ送信（送信したmap鯖の数を返す）
int mapif_sendall(unsigned char *buf,unsigned int len)
{
	int i, c = 0;

	for(i = 0; i < MAX_MAP_SERVERS; i++) {
		int fd;
		if ((fd = server_fd[i]) >= 0) {
			memcpy(WFIFOP(fd,0), buf, len);
			WFIFOSET(fd, len);
			c++;
		}
	}

	return c;
}

// 自分以外の全てのMAPサーバーにデータ送信（送信したmap鯖の数を返す）
int mapif_sendallwos(int sfd,unsigned char *buf,unsigned int len)
{
	int i, c = 0;

	for(i = 0; i < MAX_MAP_SERVERS; i++) {
		int fd;
		if ((fd = server_fd[i]) >= 0 && fd != sfd) {
			memcpy(WFIFOP(fd,0), buf, len);
			WFIFOSET(fd, len);
			c++;
		}
	}

	return c;
}

// MAPサーバーにデータ送信（map鯖生存確認有り）
int mapif_send(int fd,unsigned char *buf,unsigned int len)
{
	int i;

	for(i = 0; i < MAX_MAP_SERVERS; i++) {
		if (fd == server_fd[i]) {
			memcpy(WFIFOP(fd,0), buf, len);
			WFIFOSET(fd, len);
			return 1;
		}
	}

	return 0;
}

void mapif_parse_CharConnectLimit(int fd)
{
	int limit = RFIFOL(fd,2);

	if (limit < 0)
		limit = 0;
	printf("char:max_connect_user change %d->%d\n", max_connect_user, limit);
	max_connect_user = limit;

	return;
}

int send_users_tologin(int tid,unsigned int tick,int id,void *data)
{
	if (login_fd >= 0 && session[login_fd] && session[login_fd]->auth) {
		int i, users = 0;

		for(i = 0; i < MAX_MAP_SERVERS; i++) {
			if (server_fd[i] >= 0)
				users += server[i].users;
		}

		WFIFOW(login_fd,0) = 0x2714;
		WFIFOL(login_fd,2) = users;
		WFIFOSET(login_fd,6);

		for(i = 0; i < MAX_MAP_SERVERS; i++) {
			int fd;
			if ((fd = server_fd[i]) >= 0) {
				WFIFOW(fd,0) = 0x2b00;
				WFIFOL(fd,2) = users;
				WFIFOSET(fd,6);
			}
		}
	}

	return 0;
}

static int check_connect_login_server(int tid,unsigned int tick,int id,void *data)
{
	if (login_fd < 0 || session[login_fd] == NULL) {
		login_fd = make_connection(login_ip, login_port);
		if (login_fd < 0) {
			if (char_loginaccess_autorestart >= 1)
				exit(1);
			return 0;
		}
		session[login_fd]->func_parse=parse_tologin;
		session[login_fd]->func_destruct = parse_login_disconnect;
		realloc_fifo(login_fd, RFIFOSIZE_SERVERLINK, WFIFOSIZE_SERVERLINK);

		// 暗号化ログインのチャレンジ要求
		WFIFOW(login_fd,0)=0x272d;
		WFIFOSET(login_fd,2);

		/* プレーンなログインは現在廃止 */
		//WFIFOW(login_fd,0)=0x2710;
		//memcpy(WFIFOP(login_fd,2),userid,24);
		//memcpy(WFIFOP(login_fd,26),passwd,24);
		//WFIFOL(login_fd,50)=0;
		//WFIFOL(login_fd,54)=char_ip;
		//WFIFOW(login_fd,58)=char_port;
		//memcpy(WFIFOP(login_fd,60),server_name,20);
		//WFIFOW(login_fd,80)=char_maintenance;
		//WFIFOW(login_fd,82)=char_new;
		//WFIFOSET(login_fd,84);
	}

	return 0;
}

static void char_config_read(const char *cfgName)
{
	char line[1024], w1[1024], w2[1024];
	FILE *fp;

	fp = fopen(cfgName, "r");
	if (fp == NULL) {
		printf("file not found: %s\n", cfgName);
		return;
	}

	while(fgets(line, sizeof(line) - 1, fp)) {
		if (line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if (line[0] == '/' && line[1] == '/')
			continue;
		if (sscanf(line,"%[^:]: %[^\r\n]", w1, w2) != 2)
			continue;

		if (strcmpi(w1, "userid") == 0) {
			memcpy(userid, w2, 24);
			userid[23] = '\0';
		} else if (strcmpi(w1, "passwd") == 0) {
			memcpy(passwd ,w2, 24);
			passwd[23] = '\0';
		} else if (strcmpi(w1, "server_name") == 0) {
			memcpy(server_name, w2, 20);
			server_name[19] = '\0';
		} else if (strcmpi(w1, "login_ip") == 0) {
			memcpy(login_host, w2, sizeof(login_host));
			login_host[sizeof(login_host)-1] = '\0';	// force \0 terminal
		} else if (strcmpi(w1, "login_port") == 0) {
			int n = atoi(w2);
			if (n < 0 || n > 65535) {
				printf("char_config_read: Invalid login_port value: %d. Set to 6900 (default).\n", n);
				login_port = 6900; // default
			} else {
				login_port = (unsigned short)n;
			}
		} else if (strcmpi(w1, "char_ip") == 0) {
			memcpy(char_host, w2, sizeof(char_host));
			char_host[sizeof(char_host)-1] = '\0';	// force \0 terminal
		} else if (strcmpi(w1, "char_port") == 0) {
			int n = atoi(w2);
			if (n < 0 || n > 65535) {
				printf("char_config_read: Invalid char_port value: %d. Set to 6121 (default).\n", n);
				char_port = 6121; // default
			} else {
				char_port = (unsigned short)n;
			}
		} else if (strcmpi(w1, "listen_ip") == 0) {
			unsigned long ip_result = host2ip(w2, NULL);
			if(ip_result == INADDR_NONE) // not always -1
				printf("char_config_read: Invalid listen_ip value: %s.\n", w2);
			else
				listen_ip = ip_result;
		} else if (strcmpi(w1, "char_sip") == 0) {
			memcpy(char_shost, w2, sizeof(char_shost));
			char_shost[sizeof(char_shost)-1] = '\0';	// force \0 terminal
		} else if (strcmpi(w1, "char_sport") == 0) {
			int n = atoi(w2);
			if (n< 0 || n > 65535) {
				printf("char_config_read: Invalid char_sport value: %d. Set to 0 (default).\n", n);
				char_sport = 0;
			} else {
				char_sport = (unsigned short)n;
			}
		} else if (strcmpi(w1, "char_maintenance") == 0) {
			char_maintenance = atoi(w2);
		} else if (strcmpi(w1, "char_loginaccess_autorestart") == 0) {
			char_loginaccess_autorestart = atoi(w2);
		} else if (strcmpi(w1, "char_new")==0){
			char_new = atoi(w2);
		} else if (strcmpi(w1, "max_connect_user") == 0) {
			max_connect_user = atoi(w2);
			if (max_connect_user < 0) {
				printf("char_config_read: Invalid max_connect_user value: %d. Set to 0 (default).\n", max_connect_user);
				max_connect_user = 0;
			}
		} else if (strcmpi(w1, "autosave_time") == 0) {
			autosave_interval = atoi(w2) * 1000;
			if (autosave_interval <= 0)
				autosave_interval = DEFAULT_AUTOSAVE_INTERVAL_CS;
		} else if (strcmpi(w1, "start_point") == 0) {
			char map[1024];
			int x, y;
			if (sscanf(w2, "%[^,],%d,%d", map, &x, &y) < 3)
				continue;
			memcpy(start_point.map, map, 16);
			start_point.map[15] = '\0';
			start_point.x       = x;
			start_point.y       = y;
		} else if (strcmpi(w1, "start_zeny") == 0) {
			start_zeny = atoi(w2);
			if (start_zeny < 0) {
				printf("char_config_read: Invalid start_zeny value: %d. Set to 0 (default).\n", start_zeny);
				start_zeny = 0;
			}
		} else if (strcmpi(w1, "start_weapon") == 0) {
			start_weapon = atoi(w2);
		} else if (strcmpi(w1, "start_armor") == 0) {
			start_armor = atoi(w2);
		} else if (strcmpi(w1, "unknown_char_name") == 0) {
			strncpy(unknown_char_name, w2, 24);
			unknown_char_name[23] = '\0';
		} else if (strcmpi(w1, "default_map_type") == 0) {
			default_map_type = atoi(w2);
		} else if (strcmpi(w1, "default_map_name") == 0) {
			strncpy(default_map_name, w2, 16);
			default_map_name[15] = '\0';
		} else if (strcmpi(w1, "max_char_slot") == 0) {
			max_char_slot = atoi(w2);
			if (max_char_slot <= 0 || max_char_slot > MAX_CHAR_SLOT) {
				printf("char_config_read: Invalid max_char_slot value: %d. Set to %d (default).\n", max_char_slot, MAX_CHAR_SLOT);
				max_char_slot = MAX_CHAR_SLOT;
			}
		} else if (strcmpi(w1, "check_status_polygon") == 0) {
			check_status_polygon = atoi(w2);
		} else if (strcmpi(w1, "delete_delay_time") == 0) {
			delete_delay_time = atoi(w2);
		} else if (strcmpi(w1, "httpd_enable") == 0) {
			socket_enable_httpd(atoi(w2));
		} else if (strcmpi(w1, "httpd_document_root") == 0) {
			httpd_set_document_root(w2);
		} else if (strcmpi(w1, "httpd_log_filename") == 0) {
			httpd_set_logfile(w2);
		} else if (strcmpi(w1, "httpd_config") == 0) {
			httpd_config_read(w2);
		} else if (strcmpi(w1, "import") == 0) {
			char_config_read(w2);
		} else {
			charlog_config_read(w1, w2);
			chardb_config_read_sub(w1, w2);
		}
	}
	fclose(fp);

	return;
}

static void char_socket_ctrl_panel_func(int fd,char* usage,char* user,char* status)
{
	struct socket_data *sd = session[fd];
	struct char_session_data *cd = (struct char_session_data *)sd->session_data;

	strcpy( usage,
		( sd->func_parse == parse_char )? "char user" :
		( sd->func_parse == parse_tologin )? "login server" :
		( sd->func_parse == parse_frommap)? "map server" : "unknown" );

	if( sd->func_parse == parse_tologin )
	{
		strcpy( user, userid );
	}
	else if( sd->func_parse == parse_char && sd->auth )
	{
		sprintf( user, "%d", cd->account_id );
	}

	return;
}

static int gm_account_db_final(void *key,void *data,va_list ap)
{
	struct gm_account *p = (struct gm_account *)data;

	aFree(p);

	return 0;
}

static int char_online_db_final(void *key,void *data,va_list ap)
{
	struct char_online *p = (struct char_online *)data;

	aFree(p);

	return 0;
}

void do_pre_final(void)
{
	// nothing to do
	return;
}

void do_final(void)
{
	int i;

	chardb_set_offline(-1);

	chardb_sync();
	inter_sync();
	do_final_inter();
	petdb_final();
	homundb_final();
	mercdb_final();
	guilddb_final();
	partydb_final();
	storagedb_final();
	gstoragedb_final();
	maildb_final();
	statusdb_final();
	questdb_final();
	if(gm_account_db)
		numdb_final(gm_account_db,gm_account_db_final);
	delete_session(login_fd);
	delete_session(char_fd);
	if(char_sport != 0 && char_port != char_sport)
		delete_session(char_sfd);
	for(i = 0; i < MAX_MAP_SERVERS; i++) {
		if (server_fd[i] >= 0)
			delete_session(server_fd[i]);
	}
	numdb_final(char_online_db,char_online_db_final);
	chardb_final();
	exit_dbn();
	do_final_timer();

	return;
}

int do_init(int argc,char **argv)
{
	int i;

	printf("Auriga Char Server [%s] v%d.%d.%d version %04d\n",
#ifdef TXT_ONLY
		"TXT",
#else
		"SQL",
#endif
		AURIGA_MAJOR_VERSION, AURIGA_MINOR_VERSION, AURIGA_REVISION,
		get_current_version()
	);

	for(i = 1; i < argc - 1; i += 2) {
		if(strcmp(argv[i], "--char_config") == 0 || strcmp(argv[i], "--char-config") == 0) {
			strncpy(char_conf_filename, argv[i+1], sizeof(char_conf_filename));
			char_conf_filename[sizeof(char_conf_filename)-1] = '\0';
		}
		else if(strcmp(argv[i], "--inter_config") == 0 || strcmp(argv[i], "--inter-config") == 0) {
			strncpy(inter_conf_filename, argv[i+1], sizeof(inter_conf_filename));
			inter_conf_filename[sizeof(inter_conf_filename)-1] = '\0';
		}
		else {
			printf("illegal command line argument %s !!\n", argv[i]);
			exit(1);
		}
	}

	char_config_read(char_conf_filename);

	login_ip = host2ip(login_host, "Login server IP address");
	char_ip  = host2ip(char_host, "Character server IP address");
	if(char_shost[0])
		char_sip = host2ip(char_shost, "Character server sIP address");

	for(i = 0; i < MAX_MAP_SERVERS; i++) {
		server_fd[i] = -1;
		memset(&server[i], 0, sizeof(struct mmo_map_server));
	}
	char_online_db = numdb_init();
	if(chardb_init() == false)
		exit(1);
	inter_storage_init();
	chardb_build_ranking();
	read_gm_account();
	inter_init(inter_conf_filename);	// inter server 初期化

	set_defaultparse(parse_char);
	set_sock_destruct(parse_char_disconnect);
	socket_set_httpd_page_connection_func( char_socket_ctrl_panel_func );

	char_fd = make_listen_port(char_port, listen_ip);
	if (char_sport != 0 && char_port != char_sport)
		char_sfd = make_listen_port(char_sport, char_sip);

	add_timer_func_list(check_connect_login_server);
	add_timer_func_list(send_users_tologin);
	add_timer_func_list(mmo_char_sync_timer);

	add_timer_interval(gettick()+1000,check_connect_login_server,0,NULL,10*1000);
	add_timer_interval(gettick()+1000,send_users_tologin,0,NULL,5*1000);
	add_timer_interval(gettick()+autosave_interval,mmo_char_sync_timer,0,NULL,autosave_interval);

	// for httpd support
	do_init_httpd();
	do_init_graph();
	graph_add_sensor("Uptime(days)",60*1000,uptime);
	graph_add_sensor("Memory Usage(KB)",60*1000,memmgr_usage);
	httpd_default_page(httpd_send_file);

	chardb_set_offline(-1);

	return 0;
}
