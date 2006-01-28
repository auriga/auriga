
#ifndef _WIN32
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <sys/time.h>
	#include <sys/ioctl.h>
	#include <unistd.h>
	#include <signal.h>
	#include <fcntl.h>
	#include <arpa/inet.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "malloc.h"
#include "nullpo.h"
#include "socket.h"
#include "timer.h"
#include "utils.h"

#include "map.h"
#include "battle.h"
#include "chrif.h"
#include "clif.h"
#include "pc.h"
#include "intif.h"
#include "storage.h"
#include "party.h"
#include "guild.h"
#include "pet.h"
#include "homun.h"
#include "atcommand.h"
#include "status.h"
#include "mail.h"
#include "npc.h"

#ifdef MEMWATCH
#include "memwatch.h"
#endif

static const int packet_len_table[]={
	-1,-1,27, 0, -1, 0, 0, 0,  0, 0, 0, 0,  0, 0,  0, 0,	// 3800-
	-1, 7, 0, 0,  0, 0, 0, 0, -1,11,15, 7,  0, 0,  0, 0,	// 3810-
	35,-1,35,15, 34,53, 7,-1,  0, 0, 0, 0,  0, 0,  0, 0,	// 3820-
	10,-1,15, 0, 79,19, 7,-1,  0,-1,-1,-1, 14,67,186,-1,	// 3830-
	 9, 9,-1, 0,  0, 0, 0, 0,  7,-1,-1,-1, 11,-1, -1, 0,	// 3840-
	 0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0,  0, 0,	// 3850-
	 0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0,  0, 0,	// 3860-
	 0, 0, 0, 0,  0, 0, 0, 0, -1, 7, 0, 0,  0, 0,  0, 0,	// 3870-
	11,-1, 7, 3,  0, 0, 0, 0, -1, 7, 3, 0,  0, 0,  0, 0,	// 3880-
	31,51,51,-1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0,  0, 0,	// 3890-
};

extern int char_fd;		// inter serverのfdはchar_fdを使う
#define inter_fd (char_fd)	// エイリアス

//-----------------------------------------------------------------
// inter serverへの送信


// pet
void intif_create_pet(int account_id,int char_id,short pet_class,short pet_lv,short pet_egg_id,
	short pet_equip,short intimate,short hungry,char rename_flag,char incubate,char *pet_name)
{
	if (inter_fd < 0)
		return;

	WFIFOW(inter_fd, 0) = 0x3080;
	WFIFOL(inter_fd, 2) = account_id;
	WFIFOL(inter_fd, 6) = char_id;
	WFIFOW(inter_fd,10) = pet_class;
	WFIFOW(inter_fd,12) = pet_lv;
	WFIFOW(inter_fd,14) = pet_egg_id;
	WFIFOW(inter_fd,16) = pet_equip;
	WFIFOW(inter_fd,18) = intimate;
	WFIFOW(inter_fd,20) = hungry;
	WFIFOB(inter_fd,22) = rename_flag;
	WFIFOB(inter_fd,23) = incubate;
	memcpy(WFIFOP(inter_fd,24),pet_name,24);
	WFIFOSET(inter_fd,48);

	return;
}

void intif_request_petdata(int account_id, int char_id, int pet_id)
{
	if (inter_fd < 0)
		return;

	WFIFOW(inter_fd, 0) = 0x3081;
	WFIFOL(inter_fd, 2) = account_id;
	WFIFOL(inter_fd, 6) = char_id;
	WFIFOL(inter_fd,10) = pet_id;
	WFIFOSET(inter_fd,14);

	return;
}

void intif_save_petdata(int account_id, struct s_pet *p)
{
	if (inter_fd < 0)
		return;

	WFIFOW(inter_fd,0) = 0x3082;
	WFIFOW(inter_fd,2) = sizeof(struct s_pet) + 8;
	WFIFOL(inter_fd,4) = account_id;
	memcpy(WFIFOP(inter_fd,8),p,sizeof(struct s_pet));
	WFIFOSET(inter_fd,WFIFOW(inter_fd,2));

	return;
}

void intif_delete_petdata(int pet_id)
{
	if (inter_fd < 0)
		return;

	WFIFOW(inter_fd,0) = 0x3083;
	WFIFOL(inter_fd,2) = pet_id;
	WFIFOSET(inter_fd,6);

	return;
}

// hom
void intif_create_hom(int account_id, int char_id, struct mmo_homunstatus *h)
{
	if (inter_fd < 0)
		return;

	WFIFOW(inter_fd,0) = 0x3088;
	WFIFOW(inter_fd,2) = sizeof(struct mmo_homunstatus) + 12;
	WFIFOL(inter_fd,4) = account_id;
	WFIFOL(inter_fd,8) = char_id;
	memcpy(WFIFOP(inter_fd,12),h,sizeof(struct mmo_homunstatus));
	WFIFOSET(inter_fd,WFIFOW(inter_fd,2));

	return;
}

void intif_request_homdata(int account_id, int char_id, int homun_id)
{
	if (inter_fd < 0)
		return;

	WFIFOW(inter_fd, 0) = 0x3089;
	WFIFOL(inter_fd, 2) = account_id;
	WFIFOL(inter_fd, 6) = char_id;
	WFIFOW(inter_fd,10)= homun_id;
	WFIFOSET(inter_fd,12);

	return;
}

void intif_save_homdata(int account_id, struct mmo_homunstatus *h)
{
	if (inter_fd < 0)
		return;

	WFIFOW(inter_fd,0) = 0x308a;
	WFIFOW(inter_fd,2) = sizeof(struct mmo_homunstatus) + 8;
	WFIFOL(inter_fd,4) = account_id;
	memcpy(WFIFOP(inter_fd,8),h,sizeof(struct mmo_homunstatus));
	WFIFOSET(inter_fd,WFIFOW(inter_fd,2));

	return;
}

void intif_delete_homdata(int account_id, int char_id, int homun_id)
{
	if (inter_fd < 0)
		return;

	WFIFOW(inter_fd, 0) = 0x308b;
	WFIFOL(inter_fd, 2) = account_id;
	WFIFOL(inter_fd, 6) = char_id;
	WFIFOW(inter_fd,10) = homun_id;
	WFIFOSET(inter_fd,12);

	return;
}

// GMメッセージを送信
void intif_GMmessage(char* mes, int len, int flag)
{
	int lp;

	if (inter_fd < 0)
		return;

	lp=(flag&0x10)?8:4;
	WFIFOW(inter_fd,0) = 0x3000;
	WFIFOW(inter_fd,2) = lp + len + 4;
	WFIFOL(inter_fd,4) = 0xFF000000;	//non color用ダミーコード
	WFIFOL(inter_fd,8) = 0x65756c62;
	memcpy(WFIFOP(inter_fd,4+lp), mes, len);
	WFIFOSET(inter_fd, WFIFOW(inter_fd,2));

	return;
}

// GMメッセージ（マルチカラー）を送信
int intif_announce(char* mes,int len,unsigned long color,int flag)
{
	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd,0) = 0x3000;
	WFIFOW(inter_fd,2) = 8+len;
	WFIFOL(inter_fd,4) = color;
	memcpy(WFIFOP(inter_fd,8), mes, len);
	WFIFOSET(inter_fd, WFIFOW(inter_fd,2));

	return 0;
}

// Wisの送信
void intif_wis_message(struct map_session_data *sd, char *nick, char *mes, int mes_len)
{
	nullpo_retv(sd);

	if (inter_fd < 0)
		return;

	WFIFOW(inter_fd,0) = 0x3001;
	WFIFOW(inter_fd,2) = mes_len+52;
	memcpy(WFIFOP(inter_fd,4),sd->status.name,24);
	memcpy(WFIFOP(inter_fd,28),nick,24);
	memcpy(WFIFOP(inter_fd,52),mes,mes_len);
	WFIFOSET(inter_fd, WFIFOW(inter_fd,2) );
//	if(battle_config.etc_log)
//		printf("intif_wis_message %s %s %s\n",sd->status.name,nick,mes);

	return;
}

// Wisの返事
int intif_wis_replay(int id,int flag)
{
	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd,0) = 0x3002;
	WFIFOL(inter_fd,2) = id;
	WFIFOB(inter_fd,6) = flag;
	WFIFOSET(inter_fd,7);
//	if(battle_config.etc_log)
//		printf("intif_wis_replay %d %d\n",id,flag);

	return 0;
}

// アカウント変数送信
int intif_saveaccountreg(struct map_session_data *sd)
{
	int j,p;

	nullpo_retr(0, sd);

	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd,0) = 0x3004;
	WFIFOL(inter_fd,4) = sd->bl.id;
	for(j=0,p=8;j<sd->save_reg.account_num;j++,p+=36){
		memcpy(WFIFOP(inter_fd,p),sd->save_reg.account[j].str,32);
		WFIFOL(inter_fd,p+32)=sd->save_reg.account[j].value;
	}
	WFIFOW(inter_fd,2)=p;
	WFIFOSET(inter_fd,p);

	return 0;
}

// アカウント変数要求
int intif_request_accountreg(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd,0) = 0x3005;
	WFIFOL(inter_fd,2) = sd->bl.id;
	WFIFOSET(inter_fd,6);

	return 0;
}

// 倉庫データ要求
int intif_request_storage(int account_id)
{
	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd,0) = 0x3010;
	WFIFOL(inter_fd,2) = account_id;
	WFIFOSET(inter_fd,6);

	return 0;
}

// 倉庫データ送信
int intif_send_storage(struct storage *stor)
{
	nullpo_retr(0, stor);

	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd,0) = 0x3011;
	WFIFOW(inter_fd,2) = sizeof(struct storage)+8;
	WFIFOL(inter_fd,4) = stor->account_id;
	memcpy( WFIFOP(inter_fd,8),stor, sizeof(struct storage) );
	WFIFOSET(inter_fd,WFIFOW(inter_fd,2));

	return 0;
}

// ギルド倉庫データ要求
int intif_request_guild_storage(int account_id,int guild_id)
{
	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd,0) = 0x3018;
	WFIFOL(inter_fd,2) = account_id;
	WFIFOL(inter_fd,6) = guild_id;
	WFIFOSET(inter_fd,10);

	return 0;
}

// ギルド倉庫データ送信
int intif_send_guild_storage(int account_id,struct guild_storage *gstor)
{
	if (inter_fd < 0)
		return -1;

	WFIFORESERVE( inter_fd, sizeof(struct guild_storage)+12 );
	WFIFOW(inter_fd,0) = 0x3019;
	WFIFOW(inter_fd,2) = sizeof(struct guild_storage)+12;
	WFIFOL(inter_fd,4) = account_id;
	WFIFOL(inter_fd,8) = gstor->guild_id;
	memcpy( WFIFOP(inter_fd,12),gstor, sizeof(struct guild_storage) );
	WFIFOSET(inter_fd,WFIFOW(inter_fd,2));

	return 0;
}

// ギルド倉庫ロック要求
int intif_trylock_guild_storage(struct map_session_data *sd,int npc_id)
{
	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd,0)  = 0x301a;
	WFIFOL(inter_fd,2)  = sd->status.account_id;
	WFIFOL(inter_fd,6)  = sd->status.guild_id;
	WFIFOL(inter_fd,10) = npc_id;
	WFIFOSET(inter_fd,14);

	return 0;
}

// ギルド倉庫ロック解除
int intif_unlock_guild_storage(int guild_id)
{
	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd,0) = 0x301b;
	WFIFOL(inter_fd,2) = guild_id;
	WFIFOSET(inter_fd,6);

	return 0;
}

// パーティ作成要求
void intif_create_party(struct map_session_data *sd, char *name)
{
	nullpo_retv(sd);

	if (inter_fd < 0)
		return;

	WFIFOW(inter_fd,0) = 0x3020;
	WFIFOL(inter_fd,2) = sd->status.account_id;
	memcpy(WFIFOP(inter_fd, 6),name,24);
	memcpy(WFIFOP(inter_fd,30),sd->status.name,24);
	memcpy(WFIFOP(inter_fd,54),map[sd->bl.m].name,16);
	WFIFOW(inter_fd,70)= sd->status.base_level;
	WFIFOSET(inter_fd,72);

	return;
}

// パーティ情報要求
int intif_request_partyinfo(int party_id)
{
	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd,0) = 0x3021;
	WFIFOL(inter_fd,2) = party_id;
	WFIFOSET(inter_fd,6);
//	if(battle_config.etc_log)
//		printf("intif: request party info\n");

	return 0;
}

// パーティ追加要求
void intif_party_addmember(struct map_session_data *sd)
{
	if (inter_fd < 0)
		return;

//	if(battle_config.etc_log)
//		printf("intif: party add member %d %d\n", sd->party_invite, sd->status.account_id);
	if(sd!=NULL){
		WFIFOW(inter_fd, 0) = 0x3022;
		WFIFOL(inter_fd, 2) = sd->party_invite;
		WFIFOL(inter_fd, 6) = sd->status.account_id;
		memcpy(WFIFOP(inter_fd,10),sd->status.name,24);
		memcpy(WFIFOP(inter_fd,34),map[sd->bl.m].name,16);
		WFIFOW(inter_fd,50) = sd->status.base_level;
		WFIFOSET(inter_fd,52);
	}

	return;
}

// パーティ設定変更
void intif_party_changeoption(int party_id, int account_id, unsigned short exp, unsigned short item)
{
	if (inter_fd < 0)
		return;

	WFIFOW(inter_fd, 0)=0x3023;
	WFIFOL(inter_fd, 2)=party_id;
	WFIFOL(inter_fd, 6)=account_id;
	WFIFOW(inter_fd,10)=exp;
	WFIFOW(inter_fd,12)=item;
	WFIFOSET(inter_fd,14);

	return;
}

// パーティ脱退要求
void intif_party_leave(int party_id, int account_id, const char * name)
{
	if (inter_fd < 0)
		return;

//	if(battle_config.etc_log)
//		printf("intif: party leave %d %d\n",party_id,account_id);
	WFIFOW(inter_fd,0)=0x3024;
	WFIFOL(inter_fd,2)=party_id;
	WFIFOL(inter_fd,6)=account_id;
	strncpy(WFIFOP(inter_fd,10), name, 24);
	WFIFOSET(inter_fd,34);

	return;
}

// パーティ移動要求
void intif_party_changemap(struct map_session_data *sd, unsigned char online)
{
	if (inter_fd < 0)
		return;

	if(sd!=NULL){
		WFIFOW(inter_fd,0)=0x3025;
		WFIFOL(inter_fd,2)=sd->status.party_id;
		WFIFOL(inter_fd,6)=sd->status.account_id;
		memcpy(WFIFOP(inter_fd,10),map[sd->bl.m].name,16);
		WFIFOB(inter_fd,26)=online;
		WFIFOW(inter_fd,27)=sd->status.base_level;
		memcpy(WFIFOP(inter_fd,29),sd->status.name,24);
		WFIFOSET(inter_fd,53);
	}
//	if(battle_config.etc_log)
//		printf("party: change map\n");

	return;
}

// パーティー解散要求
int intif_break_party(int party_id)
{
	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd,0)=0x3026;
	WFIFOL(inter_fd,2)=party_id;
	WFIFOSET(inter_fd,6);

	return 0;
}

// パーティ会話送信
int intif_party_message(int party_id,int account_id,char *mes,int len)
{
	if (inter_fd < 0)
		return -1;

//	if(battle_config.etc_log)
//		printf("intif_party_message: %s\n",mes);
	WFIFOW(inter_fd,0)=0x3027;
	WFIFOW(inter_fd,2)=len+12;
	WFIFOL(inter_fd,4)=party_id;
	WFIFOL(inter_fd,8)=account_id;
	memcpy(WFIFOP(inter_fd,12),mes,len);
	WFIFOSET(inter_fd,len+12);

	return 0;
}

// パーティ競合チェック要求
int intif_party_checkconflict(int party_id,int account_id,char *nick)
{
	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd,0)=0x3028;
	WFIFOL(inter_fd,2)=party_id;
	WFIFOL(inter_fd,6)=account_id;
	memcpy(WFIFOP(inter_fd,10),nick,24);
	WFIFOSET(inter_fd,34);

	return 0;
}

// ギルド作成要求
void intif_guild_create(const char *name, const struct guild_member *master)
{
	nullpo_retv(master);

	if (inter_fd < 0)
		return;

	WFIFOW(inter_fd,0)=0x3030;
	WFIFOW(inter_fd,2)=sizeof(struct guild_member)+32;
	WFIFOL(inter_fd,4)=master->account_id;
	memcpy(WFIFOP(inter_fd,8),name,24);
	memcpy(WFIFOP(inter_fd,32),master,sizeof(struct guild_member));
	WFIFOSET(inter_fd,WFIFOW(inter_fd,2));

	return;
}

// ギルド情報要求
void intif_guild_request_info(int guild_id)
{
	if (inter_fd < 0)
		return;

	WFIFOW(inter_fd,0) = 0x3031;
	WFIFOL(inter_fd,2) = guild_id;
	WFIFOSET(inter_fd,6);

	return;
}

// ギルドメンバ追加要求
int intif_guild_addmember(int guild_id,struct guild_member *m)
{
	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd,0) = 0x3032;
	WFIFOW(inter_fd,2) = sizeof(struct guild_member)+8;
	WFIFOL(inter_fd,4) = guild_id;
	memcpy(WFIFOP(inter_fd,8),m,sizeof(struct guild_member));
	WFIFOSET(inter_fd,WFIFOW(inter_fd,2));

	return 0;
}

// ギルドメンバ脱退/追放要求
int intif_guild_leave(int guild_id,int account_id,int char_id,int flag,const char *mes)
{
	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd, 0) = 0x3034;
	WFIFOL(inter_fd, 2) = guild_id;
	WFIFOL(inter_fd, 6) = account_id;
	WFIFOL(inter_fd,10) = char_id;
	WFIFOB(inter_fd,14) = flag;
	memcpy(WFIFOP(inter_fd,15),mes,40);
	WFIFOSET(inter_fd,55);

	return 0;
}

// ギルドメンバのオンライン状況/Lv更新要求
void intif_guild_memberinfoshort(int guild_id,
	int account_id, int char_id, unsigned char online, int lv, int class_)
{
	if (inter_fd < 0)
		return;

	WFIFOW(inter_fd, 0) = 0x3035;
	WFIFOL(inter_fd, 2) = guild_id;
	WFIFOL(inter_fd, 6) = account_id;
	WFIFOL(inter_fd,10) = char_id;
	WFIFOB(inter_fd,14) = online;
	WFIFOW(inter_fd,15) = lv;
	WFIFOW(inter_fd,17) = class_;
	WFIFOSET(inter_fd,19);

	return;
}

// ギルド解散通知
int intif_guild_break(int guild_id)
{
	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd, 0) = 0x3036;
	WFIFOL(inter_fd, 2) = guild_id;
	WFIFOSET(inter_fd,6);

	return 0;
}

// ギルド会話送信
int intif_guild_message(int guild_id,int account_id,char *mes,int len)
{
	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd,0)=0x3037;
	WFIFOW(inter_fd,2)=len+12;
	WFIFOL(inter_fd,4)=guild_id;
	WFIFOL(inter_fd,8)=account_id;
	memcpy(WFIFOP(inter_fd,12),mes,len);
	WFIFOSET(inter_fd,len+12);

	return 0;
}

// ギルド競合チェック要求
int intif_guild_checkconflict(int guild_id,int account_id,int char_id)
{
	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd, 0)=0x3038;
	WFIFOL(inter_fd, 2)=guild_id;
	WFIFOL(inter_fd, 6)=account_id;
	WFIFOL(inter_fd,10)=char_id;
	WFIFOSET(inter_fd,14);

	return 0;
}

// ギルド基本情報変更要求
int intif_guild_change_basicinfo(int guild_id,int type,const void *data,int len)
{
	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd,0)=0x3039;
	WFIFOW(inter_fd,2)=len+10;
	WFIFOL(inter_fd,4)=guild_id;
	WFIFOW(inter_fd,8)=type;
	memcpy(WFIFOP(inter_fd,10),data,len);
	WFIFOSET(inter_fd,len+10);

	return 0;
}

// ギルドメンバ情報変更要求
int intif_guild_change_memberinfo(int guild_id,int account_id,int char_id,
	int type,const void *data,int len)
{
	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd, 0)=0x303a;
	WFIFOW(inter_fd, 2)=len+18;
	WFIFOL(inter_fd, 4)=guild_id;
	WFIFOL(inter_fd, 8)=account_id;
	WFIFOL(inter_fd,12)=char_id;
	WFIFOW(inter_fd,16)=type;
	memcpy(WFIFOP(inter_fd,18),data,len);
	WFIFOSET(inter_fd,len+18);

	return 0;
}

// ギルド役職変更要求
void intif_guild_position(int guild_id, int idx, struct guild_position *p)
{
	if (inter_fd < 0)
		return;

	WFIFOW(inter_fd,0)=0x303b;
	WFIFOW(inter_fd,2)=sizeof(struct guild_position)+12;
	WFIFOL(inter_fd,4)=guild_id;
	WFIFOL(inter_fd,8)=idx;
	memcpy(WFIFOP(inter_fd,12),p,sizeof(struct guild_position));
	WFIFOSET(inter_fd,WFIFOW(inter_fd,2));

	return;
}

// ギルドスキルアップ要求
int intif_guild_skillup(int guild_id,int skill_num,int account_id,int flag)
{
	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd, 0)=0x303c;
	WFIFOL(inter_fd, 2)=guild_id;
	WFIFOL(inter_fd, 6)=skill_num;
	WFIFOL(inter_fd,10)=account_id;
	WFIFOL(inter_fd,14)=flag;
	WFIFOSET(inter_fd,18);

	return 0;
}
// ギルド同盟/敵対要求
int intif_guild_alliance(int guild_id1,int guild_id2,int account_id1,int account_id2,int flag)
{
	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd, 0)=0x303d;
	WFIFOL(inter_fd, 2)=guild_id1;
	WFIFOL(inter_fd, 6)=guild_id2;
	WFIFOL(inter_fd,10)=account_id1;
	WFIFOL(inter_fd,14)=account_id2;
	WFIFOB(inter_fd,18)=flag;
	WFIFOSET(inter_fd,19);

	return 0;
}
// ギルド告知変更要求
void intif_guild_notice(int guild_id, const char *mes1, const char *mes2)
{
	if (inter_fd < 0)
		return;

	WFIFOW(inter_fd,0)=0x303e;
	WFIFOL(inter_fd,2)=guild_id;
	memcpy(WFIFOP(inter_fd,6),mes1,60);
	memcpy(WFIFOP(inter_fd,66),mes2,120);
	WFIFOSET(inter_fd,186);

	return;
}

// ギルドエンブレム変更要求
void intif_guild_emblem(int guild_id, unsigned short len, const char *data)
{
	if (guild_id <= 0 || len > 2000) // len always >=0, it's unsigned
		return;

	if (inter_fd < 0)
		return;

	WFIFOW(inter_fd,0)=0x303f;
	WFIFOW(inter_fd,2)=len+12;
	WFIFOL(inter_fd,4)=guild_id;
	WFIFOL(inter_fd,8)=0;
	memcpy(WFIFOP(inter_fd,12),data,len);
	WFIFOSET(inter_fd,len+12);

	return;
}

//現在のギルド城占領ギルドを調べる
int intif_guild_castle_dataload(int castle_id, int idx)
{
	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd,0)=0x3040;
	WFIFOW(inter_fd,2)=castle_id;
	WFIFOB(inter_fd,4)=idx;
	WFIFOSET(inter_fd,5);

	return 0;
}

//ギルド城占領ギルド変更要求
int intif_guild_castle_datasave(int castle_id, int idx, int value)
{
	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd,0)=0x3041;
	WFIFOW(inter_fd,2)=castle_id;
	WFIFOB(inter_fd,4)=idx;
	WFIFOL(inter_fd,5)=value;
	WFIFOSET(inter_fd,9);

	return 0;
}

/*==========================================
 * 指定した名前のキャラの場所要求
 *------------------------------------------
 */
int intif_charposreq(int account_id,char *name,int flag)
{
	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd,0)=0x3090;
	WFIFOL(inter_fd,2)=account_id;
	memcpy(WFIFOP(inter_fd,6),name,24);
	WFIFOB(inter_fd,30)=flag;
	WFIFOSET(inter_fd,31);

	return 0;
}
/*==========================================
 * 指定した名前のキャラの場所に移動する
 * @jumpto
 *------------------------------------------
 */
int intif_jumpto(int account_id,char *name)
{
	intif_charposreq(account_id,name,1);
	//printf("intif_jumpto: %d %s\n",account_id,name);

	return 0;
}
/*==========================================
 * 指定した名前のキャラの場所表示する
 * @where
 *------------------------------------------
 */
int intif_where(int account_id,char *name)
{
	intif_charposreq(account_id,name,0);
	//printf("intif_where: %d %s\n",account_id,name);

	return 0;
}
/*==========================================
 * 指定した名前のキャラを呼び寄せる
 * flag=0 あなたに逢いたい
 * flag=1 @recall
 *------------------------------------------
 */
int intif_charmovereq(struct map_session_data *sd,char *name,int flag)
{
	nullpo_retr(0,sd);

	//printf("intif_charmovereq: %d %s\n",sd->status.account_id,name);
	if(name==NULL)
		return -1;

	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd,0)=0x3092;
	WFIFOL(inter_fd,2)=sd->status.account_id;
	memcpy(WFIFOP(inter_fd,6),name,24);
	WFIFOB(inter_fd,30)=flag;
	memcpy(WFIFOP(inter_fd,31),sd->mapname,16);
	WFIFOW(inter_fd,47)=sd->bl.x;
	WFIFOW(inter_fd,49)=sd->bl.y;
	WFIFOSET(inter_fd,51);

	return 0;
}
/*==========================================
 * 指定した名前のキャラを指定した場所に呼び寄せる
 * flag=0 あなたに逢いたい
 * flag=1 @recall
 * flag=2 養子系呼び出しスキル
 *------------------------------------------
 */
int intif_charmovereq2(struct map_session_data *sd,char *name,char *mapname,short x, short y,int flag)
{
	nullpo_retr(0,sd);

	//printf("intif_charmovereq: %d %s\n",sd->status.account_id,name);
	if(name==NULL)
		return -1;

	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd,0)=0x3092;
	WFIFOL(inter_fd,2)=sd->status.account_id;
	memcpy(WFIFOP(inter_fd,6),name,24);
	WFIFOB(inter_fd,30)=flag;
	memcpy(WFIFOP(inter_fd,31),mapname,16);
	WFIFOW(inter_fd,47)=x;
	WFIFOW(inter_fd,49)=y;
	WFIFOSET(inter_fd,51);

	return 0;
}
/*==========================================
 * 対象IDにメッセージを送信
 *------------------------------------------
 */
int intif_displaymessage(int account_id, char* mes)
{
	int len;

	if (inter_fd < 0)
		return -1;

	len = 6+strlen(mes)+1;
	WFIFOW(inter_fd,0) = 0x3093;
	WFIFOW(inter_fd,2) = len;
	WFIFOL(inter_fd,4) = account_id;
	strncpy(WFIFOP(inter_fd,8), mes, len-6);
	WFIFOSET(inter_fd, len );

	return 0;
}
/*==========================================
 * メールBOX更新要求
 *------------------------------------------
 */
int intif_mailbox(int char_id)
{
	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd,0) = 0x3049;
	WFIFOL(inter_fd,2) = char_id;
	WFIFOSET(inter_fd,6);

	return 0;
}
/*==========================================
 * メールの送信
 *------------------------------------------
 */
int intif_sendmail(struct mail_data *md)
{
	int size;

	if (inter_fd < 0)
		return -1;

	size = sizeof(struct mail_data);
	WFIFOW(inter_fd,0) = 0x304a;
	WFIFOW(inter_fd,2) = 4+size;
	memcpy(WFIFOP(inter_fd,4), md, size);
	WFIFOSET(inter_fd, 4+size);

	return 0;
}
/*==========================================
 * メールの削除要求
 *------------------------------------------
 */
int intif_deletemail(int char_id,int mail_num)
{
	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd,0) = 0x304b;
	WFIFOL(inter_fd,2) = char_id;
	WFIFOL(inter_fd,6) = mail_num;
	WFIFOSET(inter_fd, 10);

	return 0;
}
/*==========================================
 * メールの選択受信
 *------------------------------------------
 */
int intif_readmail(int char_id,int mail_num)
{
	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd,0) = 0x304c;
	WFIFOL(inter_fd,2) = char_id;
	WFIFOL(inter_fd,6) = mail_num;
	WFIFOSET(inter_fd, 10);

	return 0;
}
/*==========================================
 * メールに添付されたもの受信
 *------------------------------------------
 */
int intif_mail_getappend(int char_id,int mail_num)
{
	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd,0) = 0x304d;
	WFIFOL(inter_fd,2) = char_id;
	WFIFOL(inter_fd,6) = mail_num;
	WFIFOSET(inter_fd, 10);

	return 0;
}
/*==========================================
 * メールを受け取る人がいるか確認要求
 *------------------------------------------
 */
int intif_mail_checkmail(int account_id,struct mail_data *md)
{
	int size;

	if (inter_fd < 0)
		return -1;

	size = sizeof(struct mail_data);
	WFIFOW(inter_fd,0) = 0x304e;
	WFIFOW(inter_fd,2) = 8+size;
	WFIFOL(inter_fd,4) = account_id;
	memcpy(WFIFOP(inter_fd,8), md, size);
	WFIFOSET(inter_fd, 8+size);

	return 0;
}

/*==========================================
 * ステータス異常データ要求
 *------------------------------------------
 */
int intif_request_scdata(int account_id,int char_id)
{
#ifndef NO_SCDATA_SAVING
	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd,0) = 0x3078;
	WFIFOL(inter_fd,2) = account_id;
	WFIFOL(inter_fd,6) = char_id;
	WFIFOSET(inter_fd, 10);
#endif

	return 0;
}

/*==========================================
 * ステータス異常データ保存
 *------------------------------------------
 */
int intif_save_scdata(struct map_session_data *sd)
{
#ifndef NO_SCDATA_SAVING
	struct TimerData *td = NULL;
	int i,p;
	unsigned int tick = gettick();

	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd,0) = 0x3079;
	WFIFOL(inter_fd,4) = sd->status.account_id;
	WFIFOL(inter_fd,8) = sd->status.char_id;

	p=12;
	if(sd->sc_count > 0) {
		for(i=0; i<MAX_STATUSCHANGE; i++) {
			if(sd->sc_data[i].timer != -1 && status_can_save(i))
			{
				td = get_timer(sd->sc_data[i].timer);
				WFIFOW(inter_fd,p)    = i;
				WFIFOL(inter_fd,p+2)  = sd->sc_data[i].val1;
				WFIFOL(inter_fd,p+6)  = sd->sc_data[i].val2;
				WFIFOL(inter_fd,p+10) = sd->sc_data[i].val3;
				WFIFOL(inter_fd,p+14) = sd->sc_data[i].val4;
				WFIFOL(inter_fd,p+18) = DIFF_TICK(td->tick, tick);	// 残り時間
				p+=22;
			}
		}
	}
	WFIFOW(inter_fd,2) = p;
	WFIFOSET(inter_fd,p);
#endif

	return 0;
}

/*==========================================
 * キャラ鯖の制限人数の変更送信
 *------------------------------------------
 */
int intif_char_connect_limit(int limit)
{
	if (inter_fd < 0)
		return -1;

	WFIFOW(inter_fd,0) = 0x3070;
	WFIFOL(inter_fd,2) = limit;
	WFIFOSET(inter_fd, 6);

	return 0;
}
//-----------------------------------------------------------------
// inter serverから受信

// wis受信
int intif_parse_WisMessage(int fd)
{
	struct map_session_data* sd;
	int id=RFIFOL(fd,4);
	int i,j=0;

//	if(battle_config.etc_log)
//		printf("intif_parse_wismessage: %d %s %s %s\n",id,RFIFOP(fd,6),RFIFOP(fd,30),RFIFOP(fd,54) );

	sd=map_nick2sd(RFIFOP(fd,32));	// 送信先を探す
	if(sd!=NULL){
		for(i=0;i<MAX_WIS_REFUSAL;i++){	//拒否リストに名前があるかどうか判定してあれば拒否
			if(strcmp(sd->wis_refusal[i],RFIFOP(fd,8))==0){
				j++;
				break;
			}
		}
		if(sd->wis_all)
			intif_wis_replay(id,3);	// 受信拒否
		else if(j>0)
			intif_wis_replay(id,2);	// 受信拒否
		else{
			clif_wis_message(sd->fd,RFIFOP(fd,8),RFIFOP(fd,56),RFIFOW(fd,2)-56);
			intif_wis_replay(id,0);	// 送信成功
		}
	}else
		intif_wis_replay(id,1);	// そんな人いません
	return 0;
}

// wis送信結果受信
int intif_parse_WisEnd(int fd)
{
	struct map_session_data* sd;
//	if(battle_config.etc_log)
//		printf("intif_parse_wisend: %s %d\n",RFIFOP(fd,2),RFIFOB(fd,26));
	sd=map_nick2sd(RFIFOP(fd,2));
	if(sd!=NULL)
		clif_wis_end(sd->fd,RFIFOB(fd,26));
	return 0;
}

// アカウント変数通知
int intif_parse_AccountReg(int fd)
{
	int j,p;
	struct map_session_data *sd;
	if( (sd=map_id2sd(RFIFOL(fd,4)))==NULL )
		return 1;

	for(p=8,j=0;p<RFIFOW(fd,2) && j<ACCOUNT_REG_NUM;p+=36,j++){
		memcpy(sd->save_reg.account[j].str,RFIFOP(fd,p),32);
		sd->save_reg.account[j].value=RFIFOL(fd,p+32);
	}
	sd->save_reg.account_num=j;
//	printf("intif: accountreg\n");
	return 0;
}
// 倉庫データ受信
int intif_parse_LoadStorage(int fd)
{
	struct storage *stor;
	struct map_session_data *sd;
	stor=account2storage( RFIFOL(fd,4) );
	if( RFIFOW(fd,2)-8 != sizeof(struct storage) ){
		if(battle_config.error_log)
			printf("intif_parse_LoadStorage: data size error %d %d\n",RFIFOW(fd,2)-8 , sizeof(struct storage));
		return 1;
	}
	sd=map_id2sd( RFIFOL(fd,4) );
	if(sd==NULL){
		if(battle_config.error_log)
			printf("intif_parse_LoadStorage: user not found %d\n",RFIFOL(fd,4));
		storage_delete( RFIFOL(fd,4) );
		return 1;
	}
	if(battle_config.save_log)
		printf("intif_openstorage: %d\n",RFIFOL(fd,4) );
	memcpy(stor,RFIFOP(fd,8),sizeof(struct storage));
	stor->storage_status=1;
	sd->state.storage_flag = 1;
	clif_storageitemlist(sd,stor);
	clif_storageequiplist(sd,stor);
	clif_updatestorageamount(sd,stor);
	return 0;
}
// 倉庫データ送信成功
int intif_parse_SaveStorage(int fd)
{
	if(battle_config.save_log)
		printf("intif_savestorage: done %d %d\n",RFIFOL(fd,2),RFIFOB(fd,6) );
	return 0;
}

// ギルド倉庫データ受信
int intif_parse_LoadGuildStorage(int fd)
{
	struct guild_storage *gstor;
	struct map_session_data *sd;
	int guild_id = RFIFOL(fd,8);
	if(guild_id > 0) {
		gstor=guild2storage(guild_id);
		if(!gstor) {
			if(battle_config.error_log)
				printf("intif_parse_LoadGuildStorage: error guild_id %d not exist\n",guild_id);
			return 1;
		}
		if( RFIFOW(fd,2)-12 != sizeof(struct guild_storage) ){
			gstor->storage_status = 0;
			if(battle_config.error_log)
				printf("intif_parse_LoadGuildStorage: data size error %d %d\n",RFIFOW(fd,2)-12 , sizeof(struct guild_storage));
			return 1;
		}
		sd=map_id2sd( RFIFOL(fd,4) );
		if(sd==NULL){
			if(battle_config.error_log)
				printf("intif_parse_LoadGuildStorage: user not found %d\n",RFIFOL(fd,4));
			guild_storage_delete( guild_id );
			return 1;
		}
		if(battle_config.save_log)
			printf("intif_open_guild_storage: %d\n",RFIFOL(fd,4) );
		memcpy(gstor,RFIFOP(fd,12),sizeof(struct guild_storage));
		gstor->storage_status = 1;
		sd->state.storage_flag = 2;
		clif_guildstorageitemlist(sd,gstor);
		clif_guildstorageequiplist(sd,gstor);
		clif_updateguildstorageamount(sd,gstor);
	}
	return 0;
}
// ギルド倉庫データ送信成功
int intif_parse_SaveGuildStorage(int fd)
{
	if(battle_config.save_log) {
		printf("intif_save_guild_storage: done %d %d %d\n",RFIFOL(fd,2),RFIFOL(fd,6),RFIFOB(fd,10) );
	}
	return 0;
}
// ギルド倉庫ロック要求返答
int intif_parse_TrylockGuildStorageAck(int fd)
{
	struct map_session_data *sd = map_id2sd(RFIFOL(fd,2));
	int guild_id = RFIFOL(fd,6);
	int succeed  = RFIFOB(fd,14);

	// 既に存在してないかギルドが違うなら
	if(sd == NULL || sd->status.guild_id != guild_id) {
		intif_unlock_guild_storage(guild_id);
		return 0;
	}

	if(sd->state.gstorage_lockreq == 1) {	// script
		sd->npc_menu = succeed;
		npc_scriptcont(sd,RFIFOL(fd,10));
	}
	else if(sd->state.gstorage_lockreq == 2) {	// atcommand
		if(succeed)
			storage_guild_storageopen(sd);
		else
			clif_displaymessage(sd->fd, msg_txt(130));
	}
	else {
		// リログイン等をしたため倉庫を開く必要がない
		intif_unlock_guild_storage(sd->status.guild_id);
	}
	sd->state.gstorage_lockreq = 0;

	return 0;
}
// ギルド倉庫ロック解除返答
int intif_parse_UnlockGuildStorageAck(int fd)
{
	if(battle_config.save_log)
		printf("intif_unlock_guild_storage: done %d %d\n",RFIFOL(fd,2),RFIFOB(fd,6) );
	return 0;
}

// パーティ作成可否
int intif_parse_PartyCreated(int fd)
{
	if(battle_config.etc_log)
		printf("intif: party created\n");
	party_created(RFIFOL(fd,2),RFIFOB(fd,6),RFIFOL(fd,7),RFIFOP(fd,11));
	return 0;
}
// パーティ情報
int intif_parse_PartyInfo(int fd)
{
	if( RFIFOW(fd,2)==8){
		if(battle_config.error_log)
			printf("intif: party noinfo %d\n",RFIFOL(fd,4));
		party_recv_noinfo(RFIFOL(fd,4));
		return 0;
	}

//	printf("intif: party info %d\n",RFIFOL(fd,4));
	if( RFIFOW(fd,2)!=sizeof(struct party)+4 ){
		if(battle_config.error_log)
			printf("intif: party info : data size error %d %d %d\n",RFIFOL(fd,4),RFIFOW(fd,2),sizeof(struct party)+4);
	}
	party_recv_info((struct party *)RFIFOP(fd,4));
	return 0;
}

// パーティ追加通知
static void intif_parse_PartyMemberAdded(int fd)
{
	if(battle_config.etc_log)
		printf("intif: party member added %d %d %d %-24s\n",RFIFOL(fd,2),RFIFOL(fd,6),RFIFOB(fd,10),RFIFOP(fd,11));
	party_member_added(RFIFOL(fd,2),RFIFOL(fd,6),RFIFOB(fd,10),RFIFOP(fd,11));

	return;
}

// パーティ設定変更通知
int intif_parse_PartyOptionChanged(int fd)
{
	party_optionchanged(RFIFOL(fd,2),RFIFOL(fd,6),RFIFOW(fd,10),RFIFOW(fd,12),RFIFOB(fd,14));
	return 0;
}
// パーティ脱退通知
int intif_parse_PartyMemberLeaved(int fd)
{
	if(battle_config.etc_log)
		printf("intif: party member leaved %d %d %s\n",RFIFOL(fd,2),RFIFOL(fd,6),RFIFOP(fd,10));
	party_member_leaved(RFIFOL(fd,2),RFIFOL(fd,6),RFIFOP(fd,10));
	return 0;
}
// パーティ解散通知
int intif_parse_PartyBroken(int fd)
{
	party_broken(RFIFOL(fd,2));
	return 0;
}

// パーティ移動通知
static void intif_parse_PartyMove(int fd)
{
//	if(battle_config.etc_log)
//		printf("intif: party move %d %d %s %d %d %-24s\n",RFIFOL(fd,2),RFIFOL(fd,6),RFIFOP(fd,10),RFIFOB(fd,26),RFIFOW(fd,27),RFIFOP(fd,29));
	party_recv_movemap(RFIFOL(fd,2),RFIFOL(fd,6),RFIFOP(fd,10),RFIFOB(fd,26),RFIFOW(fd,27),RFIFOP(fd,29));

	return;
}

// パーティメッセージ
int intif_parse_PartyMessage(int fd)
{
//	if(battle_config.etc_log)
//		printf("intif_parse_PartyMessage: %s\n",RFIFOP(fd,12));
	party_recv_message(RFIFOL(fd,4),RFIFOL(fd,8),RFIFOP(fd,12),RFIFOW(fd,2)-12);
	return 0;
}

// ギルド作成可否
int intif_parse_GuildCreated(int fd)
{
	guild_created(RFIFOL(fd,2),RFIFOL(fd,6));
	return 0;
}
// ギルド情報
int intif_parse_GuildInfo(int fd)
{
	if( RFIFOW(fd,2)==8){
		if(battle_config.error_log)
			printf("intif: guild noinfo %d\n",RFIFOL(fd,4));
		guild_recv_noinfo(RFIFOL(fd,4));
		return 0;
	}

//	if(battle_config.etc_log)
//		printf("intif: guild info %d\n",RFIFOL(fd,4));
	if( RFIFOW(fd,2)!=sizeof(struct guild)+4 ){
		if(battle_config.error_log)
			printf("intif: guild info : data size error\n %d %d %d",RFIFOL(fd,4),RFIFOW(fd,2),sizeof(struct guild)+4);
	}
	guild_recv_info((struct guild *)RFIFOP(fd,4));
	return 0;
}
// ギルドメンバ追加通知
int intif_parse_GuildMemberAdded(int fd)
{
	if(battle_config.etc_log)
		printf("intif: guild member added %d %d %d %d\n",RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10),RFIFOB(fd,14));
	guild_member_added(RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10),RFIFOB(fd,14));
	return 0;
}
// ギルドメンバ脱退/追放通知
int intif_parse_GuildMemberLeaved(int fd)
{
	guild_member_leaved(RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10),RFIFOB(fd,14),
		RFIFOP(fd,55),RFIFOP(fd,15));
	return 0;
}

// ギルドメンバオンライン状態/Lv変更通知
int intif_parse_GuildMemberInfoShort(int fd)
{
	guild_recv_memberinfoshort(RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10),RFIFOB(fd,14),RFIFOW(fd,15),RFIFOW(fd,17));
	return 0;
}
// ギルド解散通知
int intif_parse_GuildBroken(int fd)
{
	guild_broken(RFIFOL(fd,2),RFIFOB(fd,6));
	return 0;
}

// ギルド基本情報変更通知
int intif_parse_GuildBasicInfoChanged(int fd)
{
	int type=RFIFOW(fd,8),guild_id=RFIFOL(fd,4);
	void *data=RFIFOP(fd,10);
	struct guild *g=guild_search(guild_id);
	short dw=*((short *)data);
	int dd=*((int *)data);
	if( g==NULL )
		return 0;
	switch(type){
	case GBI_EXP:			g->exp=dd; break;
	case GBI_GUILDLV:		g->guild_lv=dw; break;
	case GBI_SKILLPOINT:	g->skill_point=dd; break;
	}
	return 0;
}

// ギルドメンバ情報変更通知
int intif_parse_GuildMemberInfoChanged(int fd)
{
	int type=RFIFOW(fd,16),guild_id=RFIFOL(fd,4);
	int account_id=RFIFOL(fd,8),char_id=RFIFOL(fd,12);
	void *data=RFIFOP(fd,18);
	struct guild *g=guild_search(guild_id);
	int idx,dd=*((int *)data);
	if( g==NULL )
		return 0;
	idx=guild_getindex(g,account_id,char_id);
	if(idx < 0)
		return 0;

	switch(type){
	case GMI_POSITION:
		g->member[idx].position=dd;
		guild_memberposition_changed(g,idx,dd);
		break;
	case GMI_EXP:
		g->member[idx].exp=dd;
		break;
	}
	return 0;
}

// ギルド役職変更通知
int intif_parse_GuildPosition(int fd)
{
	if( RFIFOW(fd,2)!=sizeof(struct guild_position)+12 ){
		if(battle_config.error_log)
			printf("intif: guild info : data size error\n %d %d %d",RFIFOL(fd,4),RFIFOW(fd,2),sizeof(struct guild_position)+12);
	}
	guild_position_changed(RFIFOL(fd,4),RFIFOL(fd,8),(struct guild_position *)RFIFOP(fd,12));
	return 0;
}
// ギルドスキル割り振り通知
int intif_parse_GuildSkillUp(int fd)
{
	guild_skillupack(RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10));
	return 0;
}
// ギルド同盟/敵対通知
int intif_parse_GuildAlliance(int fd)
{
	guild_allianceack(RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10),RFIFOL(fd,14),
		RFIFOB(fd,18),RFIFOP(fd,19),RFIFOP(fd,43));
	return 0;
}
// ギルド告知変更通知
int intif_parse_GuildNotice(int fd)
{
	guild_notice_changed(RFIFOL(fd,2),RFIFOP(fd,6),RFIFOP(fd,66));
	return 0;
}
// ギルドエンブレム変更通知
int intif_parse_GuildEmblem(int fd)
{
	guild_emblem_changed(RFIFOW(fd,2)-12,RFIFOL(fd,4),RFIFOL(fd,8),RFIFOP(fd,12));
	return 0;
}
// ギルド会話受信
int intif_parse_GuildMessage(int fd)
{
	guild_recv_message(RFIFOL(fd,4),RFIFOL(fd,8),RFIFOP(fd,12),RFIFOW(fd,2)-12);
	return 0;
}

// ギルド城データ要求返信
static void intif_parse_GuildCastleDataLoad(int fd)
{
	guild_castledataloadack(RFIFOW(fd,2),RFIFOB(fd,4),RFIFOL(fd,5));

	return;
}

// ギルド城データ変更通知
static void intif_parse_GuildCastleDataSave(int fd)
{
	guild_castledatasaveack(RFIFOW(fd,2),RFIFOB(fd,4),RFIFOL(fd,5));

	return;
}

// ギルド城データ一括受信(初期化時)
static void intif_parse_GuildCastleAllDataLoad(int fd)
{
	guild_castlealldataload(RFIFOW(fd,2),(struct guild_castle *)RFIFOP(fd,4));

	return;
}

// pet
int intif_parse_CreatePet(int fd)
{
	pet_get_egg(RFIFOL(fd,2),RFIFOL(fd,7),RFIFOB(fd,6));

	return 0;
}

int intif_parse_RecvPetData(int fd)
{
	struct s_pet p;
	int len=RFIFOW(fd,2);
	if(sizeof(struct s_pet)!=len-9) {
		if(battle_config.etc_log)
			printf("intif: pet data: data size error %d %d\n",sizeof(struct s_pet),len-9);
	}
	else{
		memcpy(&p,RFIFOP(fd,9),sizeof(struct s_pet));
		pet_recv_petdata(RFIFOL(fd,4),&p,RFIFOB(fd,8));
	}

	return 0;
}
int intif_parse_SavePetOk(int fd)
{
	if(RFIFOB(fd,6) == 1) {
		if(battle_config.error_log)
			printf("pet data save failure\n");
	}

	return 0;
}

int intif_parse_DeletePetOk(int fd)
{
	if(RFIFOB(fd,2) == 1) {
		if(battle_config.error_log)
			printf("pet data delete failure\n");
	}

	return 0;
}
/*==========================================
 * homun
 *------------------------------------------
 */
int intif_parse_RecvHomData(int fd)
{
	struct mmo_homunstatus p;
	int len=RFIFOW(fd,2);
	if(sizeof(struct mmo_homunstatus)!=len-9) {
		if(battle_config.etc_log)
			printf("intif: hom data: data size error %d %d\n",sizeof(struct mmo_homunstatus),len-9);
	}
	else{
		memcpy(&p,RFIFOP(fd,9),sizeof(struct mmo_homunstatus));
		homun_recv_homdata(RFIFOL(fd,4),&p,RFIFOB(fd,8));
	}

	return 0;
}
int intif_parse_SaveHomOk(int fd)
{
	if(RFIFOB(fd,6) == 1) {
		if(battle_config.error_log)
			printf("hom data save failure\n");
	}

	return 0;
}

int intif_parse_DeleteHomOk(int fd)
{
	if(RFIFOB(fd,2) == 1) {
		if(battle_config.error_log)
			printf("hom data delete failure\n");
	}

	return 0;
}

/*==========================================
 * メール関連
 *------------------------------------------
 */
int intif_parse_MailSendRes(int fd)
{
	struct map_session_data *sd = map_id2sd(RFIFOL(fd,2));
	int flag = RFIFOB(fd,6);

	if(sd) {
		clif_res_sendmail(sd->fd,flag);
		if(flag)
			mail_removeitem(sd);
	}
	return 0;
}
int intif_parse_MailBoxLoad(int fd)
{
	int i,size=sizeof(struct mail_data);
	struct map_session_data *sd = map_nick2sd(RFIFOP(fd,8));
	struct mail_data *md[MAIL_STORE_MAX];

	for(i=0;i<(int)RFIFOL(fd,4);i++){
		md[i]=(struct mail_data *)aCalloc(1,size);
		memcpy(md[i],RFIFOP(fd,32+i*size),size);
	}
	clif_send_mailbox(sd,RFIFOL(fd,4),md);
	for(i=0;i<(int)RFIFOL(fd,4);i++)
		aFree(md[i]);
	return 0;
}
int intif_parse_ArriveNewMail(int fd)
{
	struct map_session_data *sd;
	struct mail_data md;
	memcpy(&md,RFIFOP(fd,4),sizeof(struct mail_data));
	if((sd = map_nick2sd(md.receive_name))==NULL)
		return 0;
	clif_arrive_newmail(sd->fd,&md);
	return 0;
}
int intif_parse_ReadMail(int fd)
{
	struct map_session_data *sd;
	struct mail_data md;
	memcpy(&md,RFIFOP(fd,4),sizeof(struct mail_data));
	if((sd = map_nick2sd(md.receive_name))==NULL)
		return 0;
	clif_receive_mail(sd,&md);
	return 0;
}
int intif_parse_MailDeleteRes(int fd)
{
	struct map_session_data *sd = map_id2sd(RFIFOL(fd,2));
	if(sd)
		clif_deletemail_res(sd->fd,RFIFOL(fd,6),RFIFOB(fd,7));
	return 0;
}
int intif_parse_MailGetAppend(int fd)
{
	struct map_session_data *sd = map_id2sd(RFIFOL(fd,4));
	struct item item;
	int zeny = RFIFOL(fd,8);
	if(sd){
		if(zeny > 0){
			sd->status.zeny += zeny;
			clif_updatestatus(sd,SP_ZENY);
		}
		memcpy(&item,RFIFOP(fd,12),sizeof(struct item));
		if(item.nameid>0 && item.amount>0)
			pc_additem(sd,&item,item.amount);
	}
	return 0;
}
int intif_parse_MailCheckOK(int fd)
{
	struct map_session_data *sd = map_id2sd(RFIFOL(fd,4));

	if(sd)
		mail_sendmail(sd,(struct mail_data *)RFIFOP(fd,8));

	return 0;
}

/*==========================================
 * ステータス異常関連
 *------------------------------------------
 */
int intif_parse_LoadStatusChange(int fd)
{
	short len = RFIFOW(fd,2);
	struct map_session_data *sd = map_id2sd(RFIFOL(fd,4));
	short type = 0;
	int p,calc_flag=0;

	if(sd == NULL)
		return 0;

	for(p=8; p<len; p+=22) {
		type = RFIFOW(fd,p);
		if(status_can_save(type))
		{
			int tick = (int)RFIFOL(fd,p+18);
			if(tick <= 0)
				continue;
			// ここでは効果時間補正およびステータス再計算しない（flag=2+4）
			status_change_start(&sd->bl, type, RFIFOL(fd,p+2), RFIFOL(fd,p+6), RFIFOL(fd,p+10), RFIFOL(fd,p+14), (unsigned int)tick, 6);
			calc_flag = 1;
		}
	}
	if(calc_flag)
		status_calc_pc(sd,0);

	return 0;
}

int intif_parse_SaveStatusChange(int fd)
{
	if(RFIFOB(fd,6) == 1) {
		if(battle_config.error_log)
			printf("status change data save failure\n");
	}

	return 0;
}

/*==========================================
 * キャラが存在したらInterへその位置を返信
 *------------------------------------------
 */
int intif_parse_CharPosReq(int fd)
{
	//3890
	struct map_session_data *sd=map_nick2sd(RFIFOP(fd,6));
	//printf("intif_parse_CharPosReq: %d %s\n",RFIFOL(fd,2),RFIFOP(fd,6));

	if (inter_fd < 0)
		return -1;

	if(sd){
		WFIFOW(inter_fd,0)=0x3091;
		memcpy(WFIFOP(inter_fd,2),RFIFOP(fd,2),29);
		memcpy(WFIFOP(inter_fd,31),sd->mapname,16);
		WFIFOW(inter_fd,47)=sd->bl.x;
		WFIFOW(inter_fd,49)=sd->bl.y;
		WFIFOSET(inter_fd,51);
	}

	return 0;
}
/*==========================================
 * Interから対象キャラの居場所が送られて来た
 * flag=0 @where
 * flag=1 @jumpto
 *------------------------------------------
 */
int intif_parse_CharPos(int fd)
{
	//3891
	struct map_session_data *sd=map_id2sd(RFIFOL(fd,2));
	int flag=RFIFOB(fd,30);

	if(sd){
		char output[200];

		if(flag==1){
			pc_setpos(sd,RFIFOP(fd,31),RFIFOW(fd,47),RFIFOW(fd,49),3);
			snprintf(output, sizeof output, msg_txt(4), RFIFOP(fd,6));
		}else{
			snprintf(output, sizeof output, "%s %s %d %d",RFIFOP(fd,6),RFIFOP(fd,31),RFIFOW(fd,47),RFIFOW(fd,49));
		}
		clif_displaymessage(sd->fd, output);
	}
	return 0;
}
/*==========================================
 * キャラクターを指定位置に移動させる
 * flag=0 あなたいに逢いたいなので指輪の所持チェック
 * flag=1 @recallなのでGMレベルを比べたりメッセージを表示したり
 * flag=2 養子系呼び出しスキル
 *------------------------------------------
 */
int intif_parse_CharMoveReq(int fd)
{
	//3892
	struct map_session_data *sd=map_nick2sd(RFIFOP(fd,6));
	int flag=RFIFOB(fd,30);
	int account_id=RFIFOL(fd,2);
	printf("intif_parse_CharMoveReq: %d %s %s %d %d\n",RFIFOL(fd,2),RFIFOP(fd,6),RFIFOP(fd,31),RFIFOW(fd,47),RFIFOW(fd,49));

	if(sd){
		if(flag==0){
			// あなたに逢いたい
			int i;
			for( i = 0; i < MAX_INVENTORY; i++ ){
				if( (sd->status.inventory[i].nameid == WEDDING_RING_M || sd->status.inventory[i].nameid == WEDDING_RING_F) && sd->status.inventory[i].equip ){
					pc_setpos(sd,RFIFOP(fd,31),RFIFOW(fd,47),RFIFOW(fd,49),3);
					break;
				}
			}
		}
		else if(flag==1){
			char output[200];
			if(pc_numisGM(account_id) > pc_isGM(sd)){	//@recallかつ呼び出し元GMレベルが大きい
				pc_setpos(sd,RFIFOP(fd,31),RFIFOW(fd,47),RFIFOW(fd,49),2);
				snprintf(output, sizeof output, msg_txt(46), RFIFOP(fd,6));
				intif_displaymessage(account_id,output);
			}
		}else{
			pc_setpos(sd,RFIFOP(fd,31),RFIFOW(fd,47),RFIFOW(fd,49),3);
		}
	}
	return 0;
}
/*==========================================
 * 対象IDにメッセージを送信
 *------------------------------------------
 */
int intif_parse_DisplayMessage(int fd)
{
	struct map_session_data *sd=map_id2sd(RFIFOL(fd,4));

	if(sd){
		clif_displaymessage(sd->fd,RFIFOP(fd,8));
	}
	return 0;
}
//-----------------------------------------------------------------
// inter serverからの通信
// エラーがあれば0(false)を返すこと
// パケットが処理できれば1,パケット長が足りなければ2を返すこと
int intif_parse(int fd)
{
	int packet_len;
	int cmd = RFIFOW(fd,0);
	// パケットのID確認
	if(cmd<0x3800 || cmd>=0x3800+(sizeof(packet_len_table)/sizeof(packet_len_table[0])) ||
	   packet_len_table[cmd-0x3800]==0){
		return 0;
	}
	// パケットの長さ確認
	packet_len = packet_len_table[cmd-0x3800];
	if(packet_len==-1){
		if(RFIFOREST(fd)<4)
			return 2;
		packet_len = RFIFOW(fd,2);
	}
//	if(battle_config.etc_log)
//		printf("intif_parse %d %x %d %d\n",fd,cmd,packet_len,RFIFOREST(fd));
	if(RFIFOREST(fd)<packet_len){
		return 2;
	}

	// 処理分岐
	switch(cmd){
	case 0x3800:
		if (RFIFOL(fd,4) == 0xFF000000)
			clif_GMmessage(NULL,(char*)RFIFOP(fd,8),packet_len-8,0);	//non color
		else
			clif_announce(NULL,(char*)RFIFOP(fd,8),packet_len-8,RFIFOL(fd,4),0);	//multi-color
		break;
	case 0x3801:	intif_parse_WisMessage(fd); break;
	case 0x3802:	intif_parse_WisEnd(fd); break;
	case 0x3804:	intif_parse_AccountReg(fd); break;
	case 0x3810:	intif_parse_LoadStorage(fd); break;
	case 0x3811:	intif_parse_SaveStorage(fd); break;
	case 0x3818:	intif_parse_LoadGuildStorage(fd); break;
	case 0x3819:	intif_parse_SaveGuildStorage(fd); break;
	case 0x381a:	intif_parse_TrylockGuildStorageAck(fd); break;
	case 0x381b:	intif_parse_UnlockGuildStorageAck(fd); break;
	case 0x3820:	intif_parse_PartyCreated(fd); break;
	case 0x3821:	intif_parse_PartyInfo(fd); break;
	case 0x3822:	intif_parse_PartyMemberAdded(fd); break;
	case 0x3823:	intif_parse_PartyOptionChanged(fd); break;
	case 0x3824:	intif_parse_PartyMemberLeaved(fd); break;
	case 0x3825:	intif_parse_PartyMove(fd); break;
	case 0x3826:	intif_parse_PartyBroken(fd); break;
	case 0x3827:	intif_parse_PartyMessage(fd); break;
	case 0x3830:	intif_parse_GuildCreated(fd); break;
	case 0x3831:	intif_parse_GuildInfo(fd); break;
	case 0x3832:	intif_parse_GuildMemberAdded(fd); break;
	case 0x3834:	intif_parse_GuildMemberLeaved(fd); break;
	case 0x3835:	intif_parse_GuildMemberInfoShort(fd); break;
	case 0x3836:	intif_parse_GuildBroken(fd); break;
	case 0x3837:	intif_parse_GuildMessage(fd); break;
	case 0x3839:	intif_parse_GuildBasicInfoChanged(fd); break;
	case 0x383a:	intif_parse_GuildMemberInfoChanged(fd); break;
	case 0x383b:	intif_parse_GuildPosition(fd); break;
	case 0x383c:	intif_parse_GuildSkillUp(fd); break;
	case 0x383d:	intif_parse_GuildAlliance(fd); break;
	case 0x383e:	intif_parse_GuildNotice(fd); break;
	case 0x383f:	intif_parse_GuildEmblem(fd); break;
	case 0x3840:	intif_parse_GuildCastleDataLoad(fd); break;
	case 0x3841:	intif_parse_GuildCastleDataSave(fd); break;
	case 0x3842:	intif_parse_GuildCastleAllDataLoad(fd); break;
	case 0x3848:	intif_parse_MailSendRes(fd); break;
	case 0x3849:	intif_parse_MailBoxLoad(fd); break;
	case 0x384a:	intif_parse_ArriveNewMail(fd); break;
	case 0x384b:	intif_parse_ReadMail(fd); break;
	case 0x384c:	intif_parse_MailDeleteRes(fd); break;
	case 0x384d:	intif_parse_MailGetAppend(fd); break;
	case 0x384e:	intif_parse_MailCheckOK(fd); break;
	case 0x3878:	intif_parse_LoadStatusChange(fd); break;
	case 0x3879:	intif_parse_SaveStatusChange(fd); break;
	case 0x3880:	intif_parse_CreatePet(fd); break;
	case 0x3881:	intif_parse_RecvPetData(fd); break;
	case 0x3882:	intif_parse_SavePetOk(fd); break;
	case 0x3883:	intif_parse_DeletePetOk(fd); break;
	case 0x3888:	intif_parse_RecvHomData(fd); break;
	case 0x3889:	intif_parse_SaveHomOk(fd); break;
	case 0x388a:	intif_parse_DeleteHomOk(fd); break;
	case 0x3890:	intif_parse_CharPosReq(fd); break;
	case 0x3891:	intif_parse_CharPos(fd); break;
	case 0x3892:	intif_parse_CharMoveReq(fd); break;
	case 0x3893:	intif_parse_DisplayMessage(fd); break;
	default:
		if(battle_config.error_log)
			printf("intif_parse : unknown packet %d %x\n",fd,RFIFOW(fd,0));
		return 0;
	}
	// パケット読み飛ばし
	RFIFOSKIP(fd,packet_len);

	return 1;
}
