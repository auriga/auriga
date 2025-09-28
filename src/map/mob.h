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

#ifndef _MOB_H_
#define _MOB_H_

#define MOB_ID_DEFAULT 1002
#define MAX_RAND_MOB_TYPE	10
#define MAX_RAND_MOB_ENTRY	1000
#define MAX_RAND_MOB_AMOUNT	10000
#define ITEM_DROP_COUNT 10
#define MAX_MOB_TALK 100
#define MAX_MODE_OPT 10

#define MIN_MOBTHINKTIME 100
#define MIN_MOBTHINKTIME_LAZY (MIN_MOBTHINKTIME * 10)

struct mob_skill {
	unsigned short state;
	short skill_id,skill_lv;
	short permillage;
	int casttime,delay;
	short cancel;
	short cond1,cond2;
	short target;
	int val[6];
	short emotion;
	short msg_id;
};

struct mobdb_data {
	int class_;
	char name[24],jname[24];
	unsigned short lv;
	int max_hp,max_sp;
	int base_exp,job_exp;
	int atk1,atk2;
	int def,mdef;
	int str,agi,vit,int_,dex,luk;
	int range,range2,range3;
	short size,race;
	int element,mode,mode_opt[MAX_MODE_OPT];
	int speed,adelay,amotion,dmotion;
	int mexp,mexpper;
	struct {
		int nameid;
		int p;
	} dropitem[ITEM_DROP_COUNT];
	struct {
		int nameid;
		int p;
	} mvpitem[3];
	int view_class;
	short effect;
	short hair,hair_color,clothes_color;
	short weapon,shield,robe,head_top,head_mid,head_bottom;
	short style;
	short group_id;
	unsigned char sex,pcview_flag;
	unsigned int option;
	int maxskill;
	struct mob_skill skill[MAX_MOBSKILL];
};

struct random_mob_data_entry {
	int class_;
	int qty;
};

struct random_mob_data {
	struct random_mob_data_entry data[MAX_RAND_MOB_ENTRY];
	int entry;
};

struct mob_talk {
	unsigned int color;
	char msg[210];
};

enum {
	MST_TARGET = 0,
	MST_SELF,
	MST_FRIEND,
	MST_SLAVE,
	MST_MASTER,
	MST_COMMAND,
	MST_MODECHANGE,
	MST_TARGETCHANGE,
	MST_ANOTHERTARGET,
	MST_AROUND5,
	MST_AROUND6,
	MST_AROUND7,
	MST_AROUND8,
	MST_AROUND1,
	MST_AROUND2,
	MST_AROUND3,
	MST_AROUND4,
	MST_AROUND = MST_AROUND4,
};

enum {
	MSC_ALWAYS            = 0x0000,
	MSC_MYHPLTMAXRATE     = 0x0001,
	MSC_MYHPGTMAXRATE     = 0x0002,
	MSC_FRIENDHPLTMAXRATE = 0x0010,
	MSC_FRIENDHPGTMAXRATE = 0x0011,
	MSC_MYSTATUSON        = 0x0020,
	MSC_MYSTATUSOFF       = 0x0021,
	MSC_FRIENDSTATUSON    = 0x0030,
	MSC_FRIENDSTATUSOFF   = 0x0031,
	MSC_TARGETHPGTMAXRATE = 0x0040,
	MSC_TARGETHPLTMAXRATE = 0x0041,
	MSC_TARGETHPGT        = 0x0042,
	MSC_TARGETHPLT        = 0x0043,
	MSC_TARGETSTATUSON    = 0x0044,
	MSC_TARGETSTATUSOFF   = 0x0045,
	MSC_MASTERHPGTMAXRATE = 0x0050,
	MSC_MASTERHPLTMAXRATE = 0x0051,
	MSC_MASTERSTATUSON    = 0x0052,
	MSC_MASTERSTATUSOFF   = 0x0053,
	MSC_MASTERATTACKED    = 0x0054,
	MSC_ATTACKPCGT        = 0x0100,
	MSC_ATTACKPCGE        = 0x0101,
	MSC_SLAVELT           = 0x0110,
	MSC_SLAVELE           = 0x0111,
	MSC_AREASLAVEGT       = 0x0112,
	MSC_AREASLAVELE       = 0x0113,
	MSC_CLOSEDATTACKED    = 0x1000,
	MSC_LONGRANGEATTACKED = 0x1001,
	MSC_SKILLUSED         = 0x1010,
	MSC_CASTTARGETED      = 0x1011,
	MSC_AFTERSKILL        = 0x1012,
	MSC_RUDEATTACKED      = 0x1020,
	MSC_SPAWN             = 0x1030,
};

enum {
	MCT_TARGET = 1,
	MCT_SELF,
	MCT_SLAVE,
	MCT_SLAVES,
	MCT_GROUP,
	MCT_FRIEND,
	MCT_FRIENDS,
	MCT_COMMANDER,
	MCT_MASTER,
};

enum {
	MSS_DISABLE     = 0,	// 無効
	MSS_ANY         = 1,	// 常時発動
	MSS_IDLE        = 2,	// 待機
	MSS_WALK        = 3,	// 移動
	MSS_ATTACK      = 4,	// 攻撃
	MSS_DEAD        = 5,	// 死亡
	MSS_LOOT        = 6,	// ルート
	MSS_CHASE       = 7,	// 突撃
	MSS_COMMANDONLY = 8,	// 命令専用
	MSS_ANGRY       = 9,	// 攻撃(非狂化)
	MSS_FOLLOW      = 10,	// 突撃(非狂化)
};

enum {
	MOB_AI_NONE    = 0,	// なし
	MOB_AI_SUMMON  = 1,	// 召喚
	MOB_AI_SPHERE1 = 2,	// スフィアマイン(待機)
	MOB_AI_SPHERE2 = 3,	// スフィアマイン(自爆)
	MOB_AI_LEGION  = 4,	// サモンレギオン
	MOB_AI_ABR     = 5,	// ABR
	MOB_AI_BIONIC  = 6,	// バイオニック
};

enum {
	MOBID_ABR_BATTLE_WARIOR    = 20834,	// バトルウォリアー
	MOBID_ABR_DUAL_CANNON      = 20835,	// デュアルキャノン
	MOBID_ABR_MOTHER_NET       = 20836,	// マザーネット
	MOBID_ABR_INFINITY         = 20837,	// インフィニティ
	MOBID_SUMMON_WOODENWARRIOR = 20848,	// ウドゥンウォリアー
	MOBID_SUMMON_WOODEN_FAIRY  = 20849,	// ウドゥンフェアリー
	MOBID_SUMMON_CREEPER       = 20850,	// クリーパー
	MOBID_SUMMON_HELLTREE      = 20851,	// ヘルツリー
};

struct mobdb_data* mobdb_exists(int mob_id);
struct mobdb_data* mobdb_search(int mob_id);
int mobdb_searchname(const char *name);

int mobdb_searchrandomid(int type,unsigned short lv);

int mob_once_spawn(struct map_session_data *sd,int m,
	int x,int y,const char *mobname,int class_,int amount,const char *event);
int mob_once_spawn_area(struct map_session_data *sd,int m,
	int x0,int y0,int x1,int y1,const char *mobname,int class_,int amount,const char *event);

int mob_target(struct mob_data *md,struct block_list *bl,int dist);
int mob_spawn(int);
int mob_damage(struct block_list *,struct mob_data*,int,int);
int mob_heal(struct mob_data*,int);

// 見かけ取得
#define mob_get_viewclass(a)     mobdb_search(a)->view_class
#define mob_get_sex(a)           mobdb_search(a)->sex
#define mob_get_hair(a)          mobdb_search(a)->hair
#define mob_get_hair_color(a)    mobdb_search(a)->hair_color
#define mob_get_clothes_color(a) mobdb_search(a)->clothes_color
#define mob_get_weapon(a)        mobdb_search(a)->weapon
#define mob_get_shield(a)        mobdb_search(a)->shield
#define mob_get_robe(a)          mobdb_search(a)->robe
#define mob_get_head_top(a)      mobdb_search(a)->head_top
#define mob_get_head_mid(a)      mobdb_search(a)->head_mid
#define mob_get_head_bottom(a)   mobdb_search(a)->head_bottom
#define mob_get_style(a)         mobdb_search(a)->style
#define mob_is_pcview(a)         mobdb_search(a)->pcview_flag

int do_init_mob(void);
int do_final_mob(void);

int mob_timer_delete(int tid, unsigned int tick, int id, void *data);

int mob_deleteslave(struct mob_data *md);

int mob_class_change_randam(struct mob_data *md,unsigned short lv);
int mob_class_change(struct mob_data *md,const int *value,int value_count);
int mob_warp(struct mob_data *md,int m,int x,int y,int type);


int mob_attacktarget(struct mob_data *md,struct block_list *target,int flag);
int mobskill_use(struct mob_data *md,unsigned int tick,int event);
int mobskill_event(struct mob_data *md,int flag);

int mob_summonslave(struct mob_data *md2,int *value,int size,int amount,int flag);
int mob_countslave(struct mob_data *md);

int mob_gvmobcheck(struct map_session_data *sd, struct block_list *bl);
void mob_reload(void);
int mob_delayspawn(int tid,unsigned int tick,int id,void *data);
int mob_unlocktarget(struct mob_data *md,unsigned int tick);
int mob_droprate_fix(struct block_list *bl,int item,int drop);
struct block_list * mob_selecttarget(struct mob_data *md, int range);
int mob_talk(struct mob_data *md, int msg_id);
int mob_check_hpinfo(struct map_session_data *sd, struct mob_data *md);

int mob_ai_sub_hard(struct mob_data *md,unsigned int tick);
int mob_ai_hard_add(struct mob_data *md);
int mob_ai_hard_del(struct mob_data *md);
int mob_ai_hard_spawn(struct block_list *bl);
int mob_ai_hard_spawn_movearea(struct block_list *bl, int x, int y);
int mob_ai_hard_spawn_sub(struct block_list *tbl, va_list ap);
double mob_ai_hard_sensor(void);

#endif
