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

#define _INT_GUILD_C_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "socket.h"
#include "db.h"
#include "malloc.h"
#include "journal.h"
#include "utils.h"

#include "char.h"
#include "inter.h"
#include "int_guild.h"

int guild_exp[MAX_GUILDLEVEL];
struct dbt *guild_db = NULL;
struct guild_castle castle_db[MAX_GUILDCASTLE];

static int guild_join_limit = 0;
static int guild_extension_increment = 4;

static struct {
	int id;
	int max;
	struct{
		short id;
		short lv;
	} need[5];
} guild_skill_tree[MAX_GUILDSKILL];

static int mapif_guild_info(int fd,const struct guild *g);

// ギルド関連データベース読み込み
int guild_readdb(void)
{
	int i;
	FILE *fp;
	char line[1024], *p;
	const char *filename;

	// ギルド経験値
	filename = "db/exp_guild.txt";
	fp = fopen(filename, "r");
	if(fp == NULL) {
		printf("guild_readdb: open [%s] failed !\n", filename);
		return 1;
	}
	i=0;
	while(fgets(line,1020,fp)) {
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0] == '/' && line[1] == '/')
			continue;
		guild_exp[i]=atoi(line);
		i++;
		if(i >= MAX_GUILDLEVEL)
			break;
	}
	fclose(fp);
	printf("read %s done.\n", filename);

	// ギルドスキルツリー
	memset(guild_skill_tree,0,sizeof(guild_skill_tree));

	filename = "db/guild_skill_tree.txt" ;
	fp = fopen(filename, "r");
	if(fp == NULL) {
		printf("guild_readdb: open [%s] failed !\n", filename);
		return 1;
	}

	while(fgets(line,1020,fp)){
		int skillid, id, k;
		char *split[12];
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0] == '/' && line[1] == '/')
			continue;
		for(i=0,p=line;i<12 && p;i++){
			split[i]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		if(i<12)
			continue;

		skillid = atoi(split[0]);
		id = skillid - GUILD_SKILLID;
		if(id < 0 || id >= MAX_GUILDSKILL)
			continue;
		guild_skill_tree[id].id  = skillid;
		guild_skill_tree[id].max = atoi(split[1]);

		for(k=0;k<5;k++){
			guild_skill_tree[id].need[k].id=atoi(split[k*2+2]);
			guild_skill_tree[id].need[k].lv=atoi(split[k*2+3]);
		}
	}
	fclose(fp);
	printf("read %s done.\n", filename);

	return 0;
}

// エンブレムデータのデコード
char* guild_decode_emblem(char *dst, const char *src, int len)
{
	int i;
	const char *p = src;

	for(i = 0; i < len; i++, p += 2) {
		int c1 = p[0], c2 = p[1], x1 = 0, x2 = 0;

		if(c1 >= '0' && c1 <= '9') x1 = c1 - '0';
		if(c1 >= 'a' && c1 <= 'f') x1 = c1 - 'a' + 10;
		if(c1 >= 'A' && c1 <= 'F') x1 = c1 - 'A' + 10;
		if(c2 >= '0' && c2 <= '9') x2 = c2 - '0';
		if(c2 >= 'a' && c2 <= 'f') x2 = c2 - 'a' + 10;
		if(c2 >= 'A' && c2 <= 'F') x2 = c2 - 'A' + 10;

		dst[i] = (x1 << 4) | x2;
	}

	return dst;
}

// ギルドが空かどうかチェック
static int guild_check_empty(const struct guild *g)
{
	int i;

	for(i=0;i<g->max_member;i++){
		if(g->member[i].account_id>0){
			return 0;
		}
	}
	return 1;
}

// キャラの競合がないかチェック
// とりあえず省略
int guild_check_conflict(int guild_id,int account_id,int char_id)
{
	return 0;
}

int guild_nextexp(int level)
{
	if(level == 0) return 1;

	if(level < MAX_GUILDLEVEL && level > 0)
		return guild_exp[level-1];

	return 0;
}

// ギルドスキルがあるか確認
int guild_checkskill(const struct guild *g,int id)
{
	int idx = id - GUILD_SKILLID;

	if (idx < 0 || idx >= MAX_GUILDSKILL)
		return 0;
	return g->skill[idx].lv;
}

// ギルドスキルツリー計算
void guild_calc_skilltree(struct guild *g)
{
	int i, id, flag;

	if(g == NULL)
		return;

	do {
		flag = 0;
		for(i = 0; i < MAX_GUILDSKILL && (id = guild_skill_tree[i].id) > 0; i++) {
			if(g->skill[i].id <= 0) {
				int j, skillid, fail = 0;
				for(j = 0; j < 5 && (skillid = guild_skill_tree[i].need[j].id) > 0; j++) {
					if(guild_checkskill(g,skillid) < guild_skill_tree[i].need[j].lv) {
						fail = 1;
						break;
					}
				}
				if(!fail) {
					g->skill[i].id = id;
					flag = 1;
				}
			}
		}
	} while(flag);

	return;
}

// ギルドの情報の再計算
int guild_calcinfo(struct guild *g)
{
	int i,c,nextexp;
	int sum = 0;
	struct guild before = *g;

	// ギルドレベル
	if(g->guild_lv <= 0)
		g->guild_lv = 1;
	if(g->guild_lv > MAX_GUILDLEVEL)
		g->guild_lv = MAX_GUILDLEVEL;
	nextexp = guild_nextexp(g->guild_lv);

	while(nextexp > 0 && g->exp >= nextexp){	// レベルアップ処理
		g->exp-=nextexp;
		g->guild_lv++;
		g->skill_point++;
		nextexp = guild_nextexp(g->guild_lv);
	}

	// ギルドの次の経験値
	g->next_exp = nextexp;

	// メンバ上限（ギルド拡張適用）
	g->max_member = 16 + guild_checkskill(g, GD_EXTENSION) * guild_extension_increment;
	if(g->max_member > MAX_GUILD)
		g->max_member = MAX_GUILD;

	// 平均レベルとオンライン人数
	g->average_lv=0;
	g->connect_member=0;
	for(i=c=0;i<g->max_member;i++){
		if(g->member[i].account_id>0){
			sum += g->member[i].lv;
			c++;

			if(g->member[i].online>0)
				g->connect_member++;
		}
	}
	if(c != 0) {
		g->average_lv = (unsigned short)(sum / c);
	}

	// 全データを送る必要がありそう
	if( g->max_member!=before.max_member ||
	    g->guild_lv!=before.guild_lv ||
	    g->skill_point!=before.skill_point )
	{
		mapif_guild_info(-1,g);
		return 1;
	}

	return 0;
}

//-------------------------------------------------------------------
// map serverへの通信

// ギルド作成可否
int mapif_guild_created(int fd,int account_id,const struct guild *g)
{
	WFIFOW(fd,0)=0x3830;
	WFIFOL(fd,2)=account_id;
	if(g!=NULL){
		WFIFOL(fd,6)=g->guild_id;
		printf("int_guild: created! %d %s\n",g->guild_id,g->name);
	}else{
		WFIFOL(fd,6)=0;
	}
	WFIFOSET(fd,10);
	return 0;
}

// ギルド情報見つからず
int mapif_guild_noinfo(int fd,int guild_id)
{
	WFIFOW(fd,0)=0x3831;
	WFIFOW(fd,2)=8;
	WFIFOL(fd,4)=guild_id;
	WFIFOSET(fd,8);
	printf("int_guild: info not found %d\n",guild_id);
	return 0;
}

// ギルド情報まとめ送り
static int mapif_guild_info(int fd,const struct guild *g)
{
	unsigned char *buf = (unsigned char *)aMalloc(4+sizeof(struct guild));

	WBUFW(buf,0)=0x3831;
	memcpy(buf+4,g,sizeof(struct guild));
	WBUFW(buf,2)=4+sizeof(struct guild);
	if(fd<0)
		mapif_sendall(buf,WBUFW(buf,2));
	else
		mapif_send(fd,buf,WBUFW(buf,2));
	aFree(buf);
	return 0;
}

// メンバ追加可否
int mapif_guild_memberadded(int fd,int guild_id,int account_id,int char_id,int flag)
{
	WFIFOW(fd,0)=0x3832;
	WFIFOL(fd,2)=guild_id;
	WFIFOL(fd,6)=account_id;
	WFIFOL(fd,10)=char_id;
	WFIFOB(fd,14)=flag;
	WFIFOSET(fd,15);
	return 0;
}

// 脱退/追放通知
int mapif_guild_leaved(int guild_id,int account_id,int char_id,int flag,const char *name,const char *mes)
{
	unsigned char buf[128];

	WBUFW(buf, 0)=0x3834;
	WBUFL(buf, 2)=guild_id;
	WBUFL(buf, 6)=account_id;
	WBUFL(buf,10)=char_id;
	WBUFB(buf,14)=flag;
	strncpy(WBUFP(buf,15),mes,40);
	strncpy(WBUFP(buf,55),name,24);
	mapif_sendall(buf,79);
	printf("int_guild: guild leaved %d %d %s %s\n",guild_id,account_id,name,mes);
	return 0;
}

// オンライン状態とLv更新通知
int mapif_guild_memberinfoshort(struct guild *g,int idx)
{
	unsigned char buf[32];

	WBUFW(buf, 0)=0x3835;
	WBUFL(buf, 2)=g->guild_id;
	WBUFL(buf, 6)=g->member[idx].account_id;
	WBUFL(buf,10)=g->member[idx].char_id;
	WBUFB(buf,14)=(unsigned char)g->member[idx].online;
	WBUFW(buf,15)=g->member[idx].lv;
	WBUFW(buf,17)=g->member[idx].class_;
	mapif_sendall(buf,19);
	return 0;
}

// 解散通知
int mapif_guild_broken(int guild_id,int flag)
{
	unsigned char buf[16];

	WBUFW(buf,0)=0x3836;
	WBUFL(buf,2)=guild_id;
	WBUFB(buf,6)=flag;
	mapif_sendall(buf,7);
	printf("int_guild: broken %d\n",guild_id);
	return 0;
}

// ギルド内発言
int mapif_guild_message(int guild_id,int account_id,const char *mes,size_t len)
{
	unsigned char buf[512];

	WBUFW(buf,0)=0x3837;
	WBUFW(buf,2)=(unsigned short)(len+12);
	WBUFL(buf,4)=guild_id;
	WBUFL(buf,8)=account_id;
	memcpy(WBUFP(buf,12),mes,len);
	mapif_sendall(buf,len+12);
	return 0;
}

// ギルド基本情報変更通知
int mapif_guild_basicinfochanged(int guild_id,int type,const void *data,int len)
{
	unsigned char buf[2048];

	WBUFW(buf, 0)=0x3839;
	WBUFW(buf, 2)=len+10;
	WBUFL(buf, 4)=guild_id;
	WBUFW(buf, 8)=type;
	memcpy(WBUFP(buf,10),data,len);
	mapif_sendall(buf,len+10);
	return 0;
}

// ギルドメンバ情報変更通知
int mapif_guild_memberinfochanged(int guild_id,int account_id,int char_id,int type,const void *data,int len)
{
	unsigned char buf[2048];

	WBUFW(buf, 0)=0x383a;
	WBUFW(buf, 2)=len+18;
	WBUFL(buf, 4)=guild_id;
	WBUFL(buf, 8)=account_id;
	WBUFL(buf,12)=char_id;
	WBUFW(buf,16)=type;
	memcpy(WBUFP(buf,18),data,len);
	mapif_sendall(buf,len+18);
	return 0;
}

// ギルドスキルアップ通知
int mapif_guild_skillupack(int guild_id,int skill_num,int account_id,int flag)
{
	unsigned char buf[16];

	WBUFW(buf, 0)=0x383c;
	WBUFL(buf, 2)=guild_id;
	WBUFL(buf, 6)=skill_num;
	WBUFL(buf,10)=account_id;
	WBUFB(buf,14)=flag;
	mapif_sendall(buf,15);
	return 0;
}

// ギルド同盟/敵対通知
int mapif_guild_alliance(int guild_id1,int guild_id2,int account_id1,int account_id2,
	int flag,const char *name1,const char *name2)
{
	unsigned char buf[128];

	WBUFW(buf, 0)=0x383d;
	WBUFL(buf, 2)=guild_id1;
	WBUFL(buf, 6)=guild_id2;
	WBUFL(buf,10)=account_id1;
	WBUFL(buf,14)=account_id2;
	WBUFB(buf,18)=flag;
	memcpy(WBUFP(buf,19),name1,24);
	memcpy(WBUFP(buf,43),name2,24);
	mapif_sendall(buf,67);
	return 0;
}

// ギルド役職変更通知
int mapif_guild_position(struct guild *g,int idx)
{
	unsigned char buf[128];

	WBUFW(buf,0)=0x383b;
	WBUFW(buf,2)=sizeof(struct guild_position)+12;
	WBUFL(buf,4)=g->guild_id;
	WBUFL(buf,8)=idx;
	memcpy(WBUFP(buf,12),&g->position[idx],sizeof(struct guild_position));
	mapif_sendall(buf,WBUFW(buf,2));
	return 0;
}

// ギルド告知変更通知
int mapif_guild_notice(struct guild *g)
{
	unsigned char buf[256];

	WBUFW(buf,0)=0x383e;
	WBUFL(buf,2)=g->guild_id;
	memcpy(WBUFP(buf,6),g->mes1,60);
	memcpy(WBUFP(buf,66),g->mes2,120);
	mapif_sendall(buf,186);
	return 0;
}

// ギルドエンブレム変更通知
int mapif_guild_emblem(struct guild *g)
{
	unsigned char buf[2048];

	WBUFW(buf,0)=0x383f;
	WBUFW(buf,2)=g->emblem_len+12;
	WBUFL(buf,4)=g->guild_id;
	WBUFL(buf,8)=g->emblem_id;
	memcpy(WBUFP(buf,12),g->emblem_data,g->emblem_len);
	mapif_sendall(buf,WBUFW(buf,2));
	return 0;
}

int mapif_guild_castle_dataload(int castle_id,int idx,int value)
{
	unsigned char buf[16];

	WBUFW(buf, 0)=0x3840;
	WBUFW(buf, 2)=castle_id;
	WBUFB(buf, 4)=idx;
	WBUFL(buf, 5)=value;
	mapif_sendall(buf,9);
	return 0;
}

int mapif_guild_castle_datasave(int castle_id,int idx,int value)
{
	unsigned char buf[16];

	WBUFW(buf, 0)=0x3841;
	WBUFW(buf, 2)=castle_id;
	WBUFB(buf, 4)=idx;
	WBUFL(buf, 5)=value;
	mapif_sendall(buf,9);
	return 0;
}

int mapif_guild_castle_alldataload(int fd)
{
	WFIFOW(fd,0)=0x3842;
	WFIFOW(fd,2)=4+sizeof(castle_db);
	memcpy(WFIFOP(fd,4), castle_db, sizeof(castle_db));
	WFIFOSET(fd,WFIFOW(fd,2));
	return 0;
}

int mapif_guild_skillmax_load(int fd)
{
	int i, len = 4;

	WFIFOW(fd,0) = 0x3843;
	for(i = 0; i < MAX_GUILDSKILL; i++) {
		WFIFOL(fd,len) = guild_skill_tree[i].max;
		len += 4;
	}
	WFIFOW(fd,2) = len;
	WFIFOSET(fd,len);
	return 0;
}

//-------------------------------------------------------------------
// map serverからの通信


// ギルド作成要求
int mapif_parse_CreateGuild(int fd,int account_id,const char *name,struct guild_member *master)
{
	struct guild g;
	int i;

	for(i=0;i<24 && name[i];i++){
		if( !(name[i]&0xe0) || name[i]==0x7f){
			printf("int_guild: illegal guild name [%s]\n",name);
			mapif_guild_created(fd,account_id,NULL);
			return 0;
		}
	}

	if(guilddb_load_str(name) !=NULL) {
		printf("int_guild: same name guild exists [%s]\n",name);
		mapif_guild_created(fd,account_id,NULL);
		return 0;
	}
	memset(&g,0,sizeof(struct guild));
	memcpy(g.name,name,24);
	memcpy(g.master,master->name,24);
	memcpy(&g.member[0],master,sizeof(struct guild_member));

	g.position[0].mode=0x11;

	strncpy(g.position[0].name,"GuildMaster",24);
	for(i=1;i<MAX_GUILDPOSITION-1;i++) {
		sprintf(g.position[i].name,"Position %d",i+1);
	}
	strncpy(g.position[MAX_GUILDPOSITION-1].name,"Newbie",24);

	// ここでギルド情報計算が必要と思われる
	g.max_member = (MAX_GUILD > 16)? 16: MAX_GUILD;
	g.average_lv = master->lv;
	g.guild_lv   = 1;

	guild_calc_skilltree(&g);
	guilddb_new(&g);

	mapif_guild_created(fd,account_id,&g);
	mapif_guild_info(-1,&g);

	interlog_log("guild %s (id=%d) created by master %s (id=%d)",
		name, g.guild_id, master->name, master->account_id);

	return 0;
}

// ギルド情報要求
int mapif_parse_GuildInfo(int fd,int guild_id)
{
	const struct guild *g = guilddb_load_num(guild_id);

	if(g == NULL){
		// 存在しないギルド
		mapif_guild_noinfo(fd,guild_id);
	} else if(guild_check_empty(g)) {
		// メンバーがいないので解散扱い
		guilddb_delete(guild_id); // 残骸削除
		mapif_guild_noinfo(fd,guild_id);
		return 0;
	} else {
		// ギルド情報送信
		mapif_guild_info(fd,g);
	}
	return 0;
}

// ギルドメンバ追加要求
int mapif_parse_GuildAddMember(int fd,int guild_id,struct guild_member *m)
{
	const struct guild *g1 = guilddb_load_num(guild_id);
	struct guild g2;
	int i;

	if(g1 == NULL){
		mapif_guild_memberadded(fd,guild_id,m->account_id,m->char_id,1);
		return 0;
	}

	memcpy(&g2,g1,sizeof(struct guild));
	for(i=0;i<g2.max_member;i++){
		if(guild_join_limit && g2.member[i].account_id==m->account_id)
			break;
		if(g2.member[i].account_id==0){
			memcpy(&g2.member[i],m,sizeof(struct guild_member));
			mapif_guild_memberadded(fd,guild_id,m->account_id,m->char_id,0);
			if(guild_calcinfo(&g2) == 0)
				mapif_guild_info(-1,&g2);
			guilddb_save(&g2);
			return 0;
		}
	}
	mapif_guild_memberadded(fd,guild_id,m->account_id,m->char_id,1);
	return 0;
}

// ギルド脱退/追放要求
int mapif_parse_GuildLeave(int fd,int guild_id,int account_id,int char_id,int flag,const char *mes)
{
	const struct guild *g1 = guilddb_load_num(guild_id);
	struct guild g2;
	int i;

	if(g1 == NULL)
		return 0;

	memcpy(&g2,g1,sizeof(struct guild));
	for(i=0;i<MAX_GUILD;i++){
		if(g2.member[i].account_id == account_id && g2.member[i].char_id == char_id)
		{
			if(flag) {	// 追放の場合追放リストに入れる
				int j;
				for(j=0;j<MAX_GUILDEXPLUSION;j++){
					if(g2.explusion[j].account_id==0)
						break;
				}
				if(j>=MAX_GUILDEXPLUSION) {	// 一杯なので古いのを消す
					j=MAX_GUILDEXPLUSION-1;
					memmove(&g2.explusion[0],&g2.explusion[1],j*sizeof(g2.explusion[0]));
				}
				g2.explusion[j].account_id=account_id;
				strncpy(g2.explusion[j].name,g2.member[i].name,24);
				strncpy(g2.explusion[j].mes,mes,40);
			}

			mapif_guild_leaved(guild_id,account_id,char_id,flag,g2.member[i].name,mes);
			memset(&g2.member[i],0,sizeof(struct guild_member));

			if(fd >= 0) {
				// キャラ削除でない場合はギルドIDを0に初期化
				const struct mmo_chardata *cd = chardb_load(char_id);
				if(cd) {
					struct mmo_charstatus st;
					memcpy(&st, &cd->st, sizeof(st));
					st.guild_id = 0;
					chardb_save(&st);
				}
			}

			if( guild_check_empty(&g2) ) {
				// 空データ
				guilddb_delete(g2.guild_id);
			} else {
				guilddb_save(&g2);
				mapif_guild_info(-1,&g2);	// まだ人がいるのでデータ送信
			}
			return 0;
		}
	}

	return 0;
}

// オンライン/Lv更新
static int mapif_parse_GuildChangeMemberInfoShort(int fd,int guild_id,int account_id,int char_id,unsigned char online,int lv,int class_)
{
	const struct guild *g1 = guilddb_load_num(guild_id);
	int i,alv,c;
	struct guild g2;

	if(g1 == NULL){
		return 0;
	}
	memcpy(&g2,g1,sizeof(struct guild));

	g2.connect_member=0;

	for(i=0,alv=0,c=0;i<MAX_GUILD;i++){
		if( g2.member[i].account_id==account_id && g2.member[i].char_id==char_id ) {
			g2.member[i].online=online;
			g2.member[i].lv=lv;
			g2.member[i].class_=class_;
			mapif_guild_memberinfoshort(&g2,i);
		}
		if( g2.member[i].account_id>0 ){
			alv+=g2.member[i].lv;
			c++;
		}
		if( g2.member[i].online )
			g2.connect_member++;
	}
	// 平均レベル
	if(c != 0) {
		g2.average_lv=alv/c;
	}
	guilddb_save(&g2);
	return 0;
}

// ギルド解散要求
int mapif_parse_BreakGuild(int fd,int guild_id)
{
	guilddb_delete(guild_id);
	interlog_log("guild (id=%d) broken",guild_id);
	return 0;
}

// ギルドメッセージ送信
int mapif_parse_GuildMessage(int fd,int guild_id,int account_id,const char *mes,size_t len)
{
	return mapif_guild_message(guild_id,account_id,mes,len);
}

// ギルド基本データ変更要求
int mapif_parse_GuildBasicInfoChange(int fd,int guild_id,int type,const char *data,int len)
{
	const struct guild *g1 = guilddb_load_num(guild_id);
	struct guild g2;

	if(g1 == NULL){
		return 0;
	}
	memcpy(&g2,g1,sizeof(struct guild));

	switch(type) {
	case GBI_GUILDLV:
		{
			short dw = *((short *)data);
			if(dw > 0 && g2.guild_lv + dw <= MAX_GUILDLEVEL) {
				g2.guild_lv    += dw;
				g2.skill_point += dw;
			} else if(dw < 0 && g2.guild_lv + dw >= 1) {
				g2.guild_lv += dw;
			}
		}
		break;
	case GBI_SKILLPOINT:
		g2.skill_point += *((int *)data);
		break;
	default:
		printf("int_guild: GuildBasicInfoChange: Unknown type %d\n",type);
		return 0;
	}
	mapif_guild_info(-1,&g2);
	guilddb_save(&g2);

	return 0;
}

// ギルドメンバデータ変更要求
int mapif_parse_GuildMemberInfoChange(int fd,int guild_id,int account_id,int char_id,int type,const char *data,int len)
{
	int i;
	const struct guild *g1 = guilddb_load_num(guild_id);
	struct guild g2;
	const void *p = NULL;

	if(g1 == NULL){
		return 0;
	}
	memcpy(&g2,g1,sizeof(struct guild));
	for(i=0;i<g2.max_member;i++) {
		if(g2.member[i].account_id==account_id && g2.member[i].char_id==char_id)
			break;
	}
	if(i == g2.max_member){
		printf("int_guild: GuildMemberChange: Not found %d,%d in %d[%s]\n",
			account_id,char_id,guild_id,g2.name);
		return 0;
	}
	switch(type){
	case GMI_POSITION:	// 役職
		g2.member[i].position=*((int *)data);
		break;
	case GMI_EXP:
		{	// EXP
			atn_bignumber tmp;
			int exp = *((int *)data);

			tmp = (atn_bignumber)g2.member[i].exp + exp;
			g2.member[i].exp = (tmp > 0x7fffffff)? 0x7fffffff: (tmp < 0)? 0: (int)tmp;

			tmp = (atn_bignumber)g2.exp + exp;
			g2.exp = (tmp > 0x7fffffff)? 0x7fffffff: (tmp < 0)? 0: (int)tmp;

			guild_calcinfo(&g2);	// Lvアップ判断
			mapif_guild_basicinfochanged(guild_id,GBI_EXP,&g2.exp,sizeof(g2.exp));
			p = &g2.member[i].exp;
		}
		break;
	default:
		printf("int_guild: GuildMemberInfoChange: Unknown type %d\n",type);
		return 0;
	}
	mapif_guild_memberinfochanged(guild_id,account_id,char_id,type,(p == NULL)? data: p,len);
	guilddb_save(&g2);
	return 0;
}

// ギルド役職名変更要求
int mapif_parse_GuildPosition(int fd,int guild_id,int idx,struct guild_position *p)
{
	const struct guild *g1 = guilddb_load_num(guild_id);
	struct guild g2;

	if(g1 == NULL || idx<0 || idx>=MAX_GUILDPOSITION){
		return 0;
	}
	memcpy(&g2,g1,sizeof(struct guild));
	memcpy(&g2.position[idx],p,sizeof(struct guild_position));
	{
		unsigned char *p2 = g2.position[idx].name;
		int limit = sizeof(g2.position[0].name);
		while(*p2 && --limit) {
			if(*p2 < 0x20) *p2 = '.';
			p2++;
		}
	}
	mapif_guild_position(&g2,idx);
	guilddb_save(&g2);
	printf("int_guild: position changed %d\n",idx);
	return 0;
}

// ギルドスキルアップ要求
int mapif_parse_GuildSkillUp(int fd,int guild_id,int skill_num,int account_id,int level,unsigned char flag)
{
	const struct guild *g1 = guilddb_load_num(guild_id);
	struct guild g2;
	int idx = skill_num - GUILD_SKILLID;
	int succeed = 0;

	if (g1 == NULL || idx < 0 || idx >= MAX_GUILDSKILL)
		return 0;

	memcpy(&g2,g1,sizeof(struct guild));

	if(g2.skill[idx].id > 0) {
		if(level < 0) {
			if(!(flag&1)) {
				g2.skill_point += g2.skill[idx].lv;
			}
			g2.skill[idx].lv = 0;
			succeed = 1;
		} else {
			if((g2.skill_point > 0 || flag&1) && g2.skill[idx].id > 0) {
				if(level == 0)
					level = g2.skill[idx].lv + 1;
				if(level > guild_skill_tree[idx].max)
					level = guild_skill_tree[idx].max;

				if(!(flag&1)) {
					g2.skill_point -= level - g2.skill[idx].lv;
				}
				g2.skill[idx].lv = level;
				succeed = 1;
			}
		}
	}

	if(succeed) {
		guild_calc_skilltree(&g2);
		if(guild_calcinfo(&g2) == 0)
			mapif_guild_info(-1, &g2);
		mapif_guild_skillupack(guild_id,skill_num,account_id,1);
		guilddb_save(&g2);

		if(level >= 0)
			printf("int_guild: %d skill %d up %d\n", guild_id, skill_num, level);
		else
			printf("int_guild: %d skill %d lost\n", guild_id, skill_num);
	} else {
		mapif_guild_skillupack(guild_id,skill_num,account_id,0);
	}
	return 0;
}

// ギルド同盟要求
int mapif_parse_GuildAlliance(int fd,int guild_id1,int guild_id2,int account_id1,int account_id2,int flag)
{
	const struct guild *g1[2];
	struct guild g2[2];
	int j,i;

	g1[0] = guilddb_load_num(guild_id1);
	g1[1] = guilddb_load_num(guild_id2);
	if(g1[0]==NULL || g1[1]==NULL) return 0;

	memcpy(&g2[0],g1[0],sizeof(struct guild));
	memcpy(&g2[1],g1[1],sizeof(struct guild));

	if(!(flag&0x8)){
		for(i=0;i<2-(flag&1);i++){
			for(j=0;j<MAX_GUILDALLIANCE;j++) {
				if(g2[i].alliance[j].guild_id==0) {
					g2[i].alliance[j].guild_id = g2[1-i].guild_id;
					memcpy(g2[i].alliance[j].name,g2[1-i].name,24);
					g2[i].alliance[j].opposition = flag&1;
					break;
				}
			}
		}
	} else {	// 関係解消
		for(i=0;i<2-(flag&1);i++){
			for(j=0;j<MAX_GUILDALLIANCE;j++) {
				if( g2[i].alliance[j].guild_id == g2[1-i].guild_id &&
				    g2[i].alliance[j].opposition == (flag&1))
				{
					g2[i].alliance[j].guild_id=0;
					break;
				}
			}
		}
	}
	mapif_guild_alliance(guild_id1,guild_id2,account_id1,account_id2,flag,g2[0].name,g2[1].name);
	guilddb_save(&g2[0]);
	guilddb_save(&g2[1]);
	return 0;
}

// ギルド告知変更要求
int mapif_parse_GuildNotice(int fd,int guild_id,const char *mes1,const char *mes2)
{
	const struct guild *g1 = guilddb_load_num(guild_id);
	struct guild g2;
	unsigned char *p2;
	int limit;

	if(g1 == NULL)
		return 0;
	memcpy(&g2,g1,sizeof(struct guild));
	memcpy(g2.mes1,mes1,60);
	memcpy(g2.mes2,mes2,120);

	p2    = g2.mes1;
	limit = sizeof(g2.mes1);

	while(*p2 && --limit) {
		if(*p2 < 0x20) *p2 = '.';
		p2++;
	}
	p2 = g2.mes2;
	limit = sizeof(g2.mes2);
	while(*p2 && --limit) {
		if(*p2 < 0x20) *p2 = '.';
		p2++;
	}
	guilddb_save(&g2);
	return mapif_guild_notice(&g2);
}

// ギルドエンブレム変更要求
int mapif_parse_GuildEmblem(int fd,int len,int guild_id,int dummy,const char *data)
{
	const struct guild *g1 = guilddb_load_num(guild_id);
	struct guild g2;

	if(g1 == NULL)
		return 0;
	memcpy(&g2,g1,sizeof(struct guild));
	memcpy(g2.emblem_data,data,len);
	g2.emblem_len=len;
	g2.emblem_id++;
	guilddb_save(&g2);
	return mapif_guild_emblem(&g2);
}

int mapif_parse_GuildCastleDataLoad(int fd,int castle_id,int idx)
{
	struct guild_castle *gc;

	if(castle_id < 0 || castle_id >= MAX_GUILDCASTLE) {
		return mapif_guild_castle_dataload(castle_id,0,0);
	}
	gc = &castle_db[castle_id];

	switch(idx){
		case 1:  return mapif_guild_castle_dataload(gc->castle_id,idx,gc->guild_id);             break;
		case 2:  return mapif_guild_castle_dataload(gc->castle_id,idx,gc->economy);              break;
		case 3:  return mapif_guild_castle_dataload(gc->castle_id,idx,gc->defense);              break;
		case 4:  return mapif_guild_castle_dataload(gc->castle_id,idx,gc->triggerE);             break;
		case 5:  return mapif_guild_castle_dataload(gc->castle_id,idx,gc->triggerD);             break;
		case 6:  return mapif_guild_castle_dataload(gc->castle_id,idx,gc->nextTime);             break;
		case 7:  return mapif_guild_castle_dataload(gc->castle_id,idx,gc->payTime);              break;
		case 8:  return mapif_guild_castle_dataload(gc->castle_id,idx,gc->createTime);           break;
		case 9:  return mapif_guild_castle_dataload(gc->castle_id,idx,gc->visibleC);             break;
		case 10: return mapif_guild_castle_dataload(gc->castle_id,idx,gc->guardian[0].visible);  break;
		case 11: return mapif_guild_castle_dataload(gc->castle_id,idx,gc->guardian[1].visible);  break;
		case 12: return mapif_guild_castle_dataload(gc->castle_id,idx,gc->guardian[2].visible);  break;
		case 13: return mapif_guild_castle_dataload(gc->castle_id,idx,gc->guardian[3].visible);  break;
		case 14: return mapif_guild_castle_dataload(gc->castle_id,idx,gc->guardian[4].visible);  break;
		case 15: return mapif_guild_castle_dataload(gc->castle_id,idx,gc->guardian[5].visible);  break;
		case 16: return mapif_guild_castle_dataload(gc->castle_id,idx,gc->guardian[6].visible);  break;
		case 17: return mapif_guild_castle_dataload(gc->castle_id,idx,gc->guardian[7].visible);  break;
		default:
			printf("mapif_parse_GuildCastleDataLoad ERROR!! (Not found index=%d)\n", idx);
			break;
	}
	return 0;
}

int mapif_parse_GuildCastleDataSave(int fd,int castle_id,int idx,int value)
{
	struct guild_castle *gc;

	if(castle_id < 0 || castle_id >= MAX_GUILDCASTLE) {
		return mapif_guild_castle_datasave(castle_id,idx,value);
	}
	gc = &castle_db[castle_id];

	switch(idx){
		case 1:
			if( gc->guild_id != value ) {
				interlog_log(
					"guild id=%d %s castle id=%d",
					((value)? value: gc->guild_id), ((value)? "occupy": "abandon"), idx
				);
			}
			gc->guild_id = value;
			break;
		case 2:  gc->economy             = value; break;
		case 3:  gc->defense             = value; break;
		case 4:  gc->triggerE            = value; break;
		case 5:  gc->triggerD            = value; break;
		case 6:  gc->nextTime            = value; break;
		case 7:  gc->payTime             = value; break;
		case 8:  gc->createTime          = value; break;
		case 9:  gc->visibleC            = value; break;
		case 10: gc->guardian[0].visible = value; break;
		case 11: gc->guardian[1].visible = value; break;
		case 12: gc->guardian[2].visible = value; break;
		case 13: gc->guardian[3].visible = value; break;
		case 14: gc->guardian[4].visible = value; break;
		case 15: gc->guardian[5].visible = value; break;
		case 16: gc->guardian[6].visible = value; break;
		case 17: gc->guardian[7].visible = value; break;
		default:
			printf("mapif_parse_GuildCastleDataSave ERROR!! (Not found index=%d)\n", idx);
			return 0;
	}
#if defined(TXT_ONLY) && defined(TXT_JOURNAL)
	if( guildcastle_journal_enable )
		journal_write( &guildcastle_journal, gc->castle_id, gc );
#endif
	return mapif_guild_castle_datasave(gc->castle_id,idx,value);
}

// ギルドチェック要求
int mapif_parse_GuildCheck(int fd,int guild_id,int account_id,int char_id)
{
	return guild_check_conflict(guild_id,account_id,char_id);
}


// map server からの通信
// ・１パケットのみ解析すること
// ・パケット長データはinter.cにセットしておくこと
// ・パケット長チェックや、RFIFOSKIPは呼び出し元で行われるので行ってはならない
// ・エラーなら0(false)、そうでないなら1(true)をかえさなければならない
int inter_guild_parse_frommap(int fd)
{
	switch(RFIFOW(fd,0)){
	case 0x3030: mapif_parse_CreateGuild(fd,RFIFOL(fd,4),RFIFOP(fd,8),(struct guild_member *)RFIFOP(fd,32)); break;
	case 0x3031: mapif_parse_GuildInfo(fd,RFIFOL(fd,2)); break;
	case 0x3032: mapif_parse_GuildAddMember(fd,RFIFOL(fd,4),(struct guild_member *)RFIFOP(fd,8)); break;
	case 0x3034: mapif_parse_GuildLeave(fd,RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10),RFIFOB(fd,14),RFIFOP(fd,15)); break;
	case 0x3035: mapif_parse_GuildChangeMemberInfoShort(fd,RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10),RFIFOB(fd,14),RFIFOW(fd,15),RFIFOW(fd,17)); break;
	case 0x3036: mapif_parse_BreakGuild(fd,RFIFOL(fd,2)); break;
	case 0x3037: mapif_parse_GuildMessage(fd,RFIFOL(fd,4),RFIFOL(fd,8),RFIFOP(fd,12),RFIFOW(fd,2)-12); break;
	case 0x3038: mapif_parse_GuildCheck(fd,RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10)); break;
	case 0x3039: mapif_parse_GuildBasicInfoChange(fd,RFIFOL(fd,4),RFIFOW(fd,8),RFIFOP(fd,10),RFIFOW(fd,2)-10); break;
	case 0x303A: mapif_parse_GuildMemberInfoChange(fd,RFIFOL(fd,4),RFIFOL(fd,8),RFIFOL(fd,12),RFIFOW(fd,16),RFIFOP(fd,18),RFIFOW(fd,2)-18); break;
	case 0x303B: mapif_parse_GuildPosition(fd,RFIFOL(fd,4),RFIFOL(fd,8),(struct guild_position *)RFIFOP(fd,12)); break;
	case 0x303C: mapif_parse_GuildSkillUp(fd,RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10),RFIFOL(fd,14),RFIFOB(fd,18)); break;
	case 0x303D: mapif_parse_GuildAlliance(fd,RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10),RFIFOL(fd,14),RFIFOL(fd,18)); break;
	case 0x303E: mapif_parse_GuildNotice(fd,RFIFOL(fd,2),RFIFOP(fd,6),RFIFOP(fd,66)); break;
	case 0x303F: mapif_parse_GuildEmblem(fd,RFIFOW(fd,2)-12,RFIFOL(fd,4),RFIFOL(fd,8),RFIFOP(fd,12)); break;
	case 0x3040: mapif_parse_GuildCastleDataLoad(fd,RFIFOW(fd,2),RFIFOB(fd,4)); break;
	case 0x3041: mapif_parse_GuildCastleDataSave(fd,RFIFOW(fd,2),RFIFOB(fd,4),RFIFOL(fd,5)); break;

	default:
		return 0;
	}
	return 1;
}

// マップサーバーの接続時処理
int inter_guild_mapif_init(int fd)
{
	mapif_guild_castle_alldataload(fd);
	mapif_guild_skillmax_load(fd);
	return 0;
}

// サーバーから脱退要求（キャラ削除用）
int inter_guild_leave(int guild_id,int account_id,int char_id)
{
	return mapif_parse_GuildLeave(-1,guild_id,account_id,char_id,0,"**サーバー命令**");
}

// ギルド設定読み込み
int guild_config_read(const char *w1,const char* w2)
{
	if(strcmpi(w1,"guild_extension_increment")==0)
	{
		guild_extension_increment = atoi(w2);
		if(guild_extension_increment < 0)
			guild_extension_increment = 0;
		if(guild_extension_increment > 6)
			guild_extension_increment = 6;
		return 1;
	}
	if(strcmpi(w1,"guild_join_limit")==0)
	{
		guild_join_limit = atoi(w2);
		return 1;
	}

	return guilddb_config_read_sub(w1,w2);
}
