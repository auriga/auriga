#ifndef _MOB_H_
#define _MOB_H_

#define MOB_ID_MIN 1001
#define MOB_ID_MAX 2001
#define MAX_RANDOMMONSTER 3
#define ITEM_DROP_COUNT 10

struct mob_skill {
	short state;
	short skill_id,skill_lv;
	short permillage;
	int casttime,delay;
	short cancel;
	short cond1,cond2;
	short target;
	int val[5];
	short emotion;
};

struct mob_db {
	char name[24],jname[24];
	short lv;
	int max_hp,max_sp;
	int base_exp,job_exp;
	int atk1,atk2;
	int def,mdef;
	int str,agi,vit,int_,dex,luk;
	int range,range2,range3;
	int size,race,element,mode;
	int speed,adelay,amotion,dmotion;
	int mexp,mexpper;
	struct { int nameid,p; } dropitem[ITEM_DROP_COUNT];
	struct { int nameid,p; } mvpitem[3];
	int view_class,sex;
	short hair,hair_color,clothes_color,weapon,shield,head_top,head_mid,head_buttom,option,trans,group_id,view_size;
	int summonper[MAX_RANDOMMONSTER];
	int maxskill;
	struct mob_skill skill[MAX_MOBSKILL];
};
extern struct mob_db *mob_db;

enum {
	MST_TARGET				=	0,
	MST_SELF				=	1,
	MST_FRIEND				=	2,
	MST_SLAVE				=	3,
	MST_MASTER				=	4,
	MST_COMMAND				=	5,
	MST_MODECHANGE				=	6,
	MST_TARGETCHANGE			=	7,
	MST_ANOTHERTARGET			=	8,
	MST_AROUND5				=	9,
	MST_AROUND6				=	10,
	MST_AROUND7				=	11,
	MST_AROUND8				=	12,
	MST_AROUND1				=	13,
	MST_AROUND2				=	14,
	MST_AROUND3				=	15,
	MST_AROUND4				=	16,
	MST_AROUND				=	MST_AROUND4,

	MSC_ALWAYS			=	0x0000,
	MSC_MYHPLTMAXRATE	=	0x0001,
	MSC_FRIENDHPLTMAXRATE=	0x0010,
	MSC_MYSTATUSON		=	0x0020,
	MSC_MYSTATUSOFF		=	0x0021,
	MSC_FRIENDSTATUSON	=	0x0030,
	MSC_FRIENDSTATUSOFF	=	0x0031,
	MSC_TARGETHPGTMAXRATE=	0x0040,
	MSC_TARGETHPLTMAXRATE=	0x0041,
	MSC_TARGETHPGT		=	0x0042,
	MSC_TARGETHPLT		=	0x0043,
	MSC_TARGETSTATUSON	=	0x0044,
	MSC_TARGETSTATUSOFF	=	0x0045,
	MSC_MASTERHPGTMAXRATE=	0x0050,
	MSC_MASTERHPLTMAXRATE=	0x0051,
	MSC_MASTERSTATUSON	=	0x0052,
	MSC_MASTERSTATUSOFF	=	0x0053,

	MSC_ATTACKPCGT		=	0x0100,
	MSC_ATTACKPCGE		=	0x0101,
	MSC_SLAVELT			=	0x0110,
	MSC_SLAVELE			=	0x0111,
	MSC_AREASLAVEGT		=	0x0112,
	MSC_AREASLAVELE		=	0x0113,
	MSC_CLOSEDATTACKED	=	0x1000,
	MSC_LONGRANGEATTACKED=	0x1001,
	MSC_SKILLUSED		=	0x1010,
	MSC_CASTTARGETED	=	0x1011,
	MSC_RUDEATTACKED	=	0x1020,
	MSC_SPAWN	=	0x1030,
	
	MCT_TARGET			=   1,
	MCT_SELF			=	2,
	MCT_SLAVE 			=	3,
	MCT_SLAVES			=	4,
	MCT_GROUP			=	5,
	MCT_FRIEND  		=	6,
	MCT_FRIENDS 		=	7,
	MCT_COMMANDER		=	8,
	MCT_MASTER			=	9,
};

enum {
	MSS_DISABLE = -2,	// 無効
	MSS_ANY     = -1,	// 常時発動
	MSS_IDLE,			// 待機
	MSS_WALK,			// 移動
	MSS_ATTACK,			// 攻撃
	MSS_DEAD,			// 死亡
	MSS_LOOT,			// ルート
	MSS_CHASE,			// 突撃
	MSS_COMMANDONLY,	//命令専用
};

int mobdb_searchname(const char *str);
int mobdb_checkid(const int mob_id);

int mob_once_spawn(struct map_session_data *sd,char *mapname,
	int x,int y,const char *mobname,int class,int amount,const char *event);
int mob_once_spawn_area(struct map_session_data *sd,char *mapname,
	int x0,int y0,int x1,int y1,
	const char *mobname,int class,int amount,const char *event);

int mob_target(struct mob_data *md,struct block_list *bl,int dist);
int mob_spawn(int);
int mob_damage(struct block_list *,struct mob_data*,int,int);
int mob_heal(struct mob_data*,int);
int mob_get_viewclass(int);
int mob_get_sex(int);
short mob_get_hair(int);
short mob_get_hair_color(int);
short mob_get_clothes_color(int);
short mob_get_weapon(int);
short mob_get_shield(int);
short mob_get_head_top(int);
short mob_get_head_mid(int);
short mob_get_head_buttom(int);
int do_init_mob(void);
int do_final_mob(void);

int mob_change_summon_monster_data(struct mob_data* ma);

int mob_timer_delete(int tid, unsigned int tick, int id, int data);

int mob_deleteslave(struct mob_data *md);

int mob_class_change_randam(struct mob_data *md,int lv);
int mob_class_change(struct mob_data *md,int *value,int value_count);
int mob_class_change_id(struct mob_data *md,int mob_id);
int mob_warp(struct mob_data *md,int m,int x,int y,int type);


int mob_attacktarget(struct mob_data *md,struct block_list *target,int flag);
int mobskill_use(struct mob_data *md,unsigned int tick,int event);
int mobskill_event(struct mob_data *md,int flag);

int mobskill_use_id2(struct mob_data *md, int target_id, int skill_id, int skill_lv, int casttime, int cancel);
int mobskill_use_pos2( struct mob_data *md,
	int skill_x, int skill_y, int skill_id, int skill_lv, int casttime, int cancel);

int mobskill_use_id_sub_command_to_slave(struct block_list *bl, va_list ap );

int mob_summonslave(struct mob_data *md2,int *value,int amount,int flag);
int mob_countslave(struct mob_data *md);

int mob_gvmobcheck(struct map_session_data *sd, struct block_list *bl);
void mob_reload(void);
int mob_delayspawn(int tid,unsigned int tick,int m,int n);
int mob_unlocktarget(struct mob_data *md,int tick);
int mob_droprate_fix(int item,int drop);

int mob_ai_hard_add(struct mob_data *md);
int mob_ai_hard_del(struct mob_data *md);
int mob_ai_hard_spawn( struct block_list *bl, int flag );
int mob_ai_hard_spawn_sub(struct block_list *tbl, va_list ap);
double mob_ai_hard_sensor(void);

#endif
