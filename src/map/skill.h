#ifndef _SKILL_H_
#define _SKILL_H_

#include "map.h"
#include "mmo.h"

#define MAX_SKILL_DB			MAX_SKILL
#define MAX_HOMSKILL_DB			MAX_HOMSKILL
#define MAX_GUILDSKILL_DB		MAX_GUILDSKILL
#define MAX_SKILL_PRODUCE_DB	300
#define MAX_PRODUCE_RESOURCE	10
#define MAX_SKILL_ARROW_DB	 150
#define MAX_SKILL_ABRA_DB	 350

// スキルデータベース
struct skill_db {
	int range[MAX_SKILL_LEVEL],hit,inf,pl,nk,max;
	int num[MAX_SKILL_LEVEL];
	int cast[MAX_SKILL_LEVEL],fixedcast[MAX_SKILL_LEVEL],delay[MAX_SKILL_LEVEL];
	int upkeep_time[MAX_SKILL_LEVEL],upkeep_time2[MAX_SKILL_LEVEL];
	int castcancel,cast_def_rate;
	int inf2,maxcount[MAX_SKILL_LEVEL],skill_type;
	int blewcount[MAX_SKILL_LEVEL];
	int hp[MAX_SKILL_LEVEL],sp[MAX_SKILL_LEVEL],hp_rate[MAX_SKILL_LEVEL],sp_rate[MAX_SKILL_LEVEL],zeny[MAX_SKILL_LEVEL];
	int weapon,state,spiritball[MAX_SKILL_LEVEL],coin[MAX_SKILL_LEVEL],arrow_cost[MAX_SKILL_LEVEL],arrow_type;
	int itemid[10],amount[10];
	int unit_id[4];
	int unit_layout_type[MAX_SKILL_LEVEL];
	int unit_range;
	int unit_interval;
	int unit_target;
	int unit_flag;
	int cloneable;
	int misfire;
	int zone;
	int damage_rate[4];
};

#define MAX_SKILL_UNIT_LAYOUT	50
#define MAX_SQUARE_LAYOUT		5	// 11*11のユニット配置が最大
#define MAX_SKILL_UNIT_COUNT ((MAX_SQUARE_LAYOUT*2+1)*(MAX_SQUARE_LAYOUT*2+1))
struct skill_unit_layout {
	int count;
	int dx[MAX_SKILL_UNIT_COUNT];
	int dy[MAX_SKILL_UNIT_COUNT];
};

enum {
	UF_DEFNOTENEMY		= 0x0001,	// defnotenemy 設定でBCT_NOENEMYに切り替え
	UF_NOREITERATION	= 0x0002,	// 重複置き禁止
	UF_NOFOOTSET		= 0x0004,	// 足元置き禁止
	UF_NOOVERLAP		= 0x0008,	// ユニット効果が重複しない
	UF_PATHCHECK		= 0x0010,	// オブジェクト発生時に射線チェック
	UF_DANCE			= 0x0100,	// ダンススキル
	UF_ENSEMBLE			= 0x0200,	// 合奏スキル
};

enum {
	PRD_WEAPON_L1	=    1,
	PRD_WEAPON_L2	=    2,
	PRD_WEAPON_L3	=    3,
	PRD_ORE		=   16,
	PRD_PHARMACY	=   32,
	PRD_COIN	=   64,
	PRD_NUGGET	=  128,
	PRD_CDP		=  256,
	PRD_CONVERTER	=  512,
	PRD_COOKING	= 1000,
	PRD_SCROLL	= 1001,
	PRD_SYN_POTION	= 1002,
	PRD_ORIDEOCON	= 1003,
};

extern struct skill_db skill_db[MAX_SKILL_DB+MAX_HOMSKILL_DB+MAX_GUILDSKILL_DB];

// アイテム作成データベース
struct skill_produce_db {
	int nameid;
	int req_skill,req_skilllv,itemlv;
	int per;
	int mat_id[MAX_PRODUCE_RESOURCE],mat_amount[MAX_PRODUCE_RESOURCE];
};
extern struct skill_produce_db skill_produce_db[MAX_SKILL_PRODUCE_DB];

// 矢作成データベース
struct skill_arrow_db {
	int nameid, trigger;
	int cre_id[5],cre_amount[5];
};
extern struct skill_arrow_db skill_arrow_db[MAX_SKILL_ARROW_DB];

// アブラカダブラデータベース
struct skill_abra_db {
	int nameid;
	int req_lv;
	int per;
};
extern struct skill_abra_db skill_abra_db[MAX_SKILL_ABRA_DB];

int do_init_skill(void);

//
int GetSkillStatusChangeTable(int id);
//マクロから関数化
//ギルドIDも使用可能に
int skill_get_skilldb_id(int id);
int skill_get_hit(int id);
int skill_get_inf(int id);
int skill_get_pl(int id);
int skill_get_nk(int id);
int skill_get_max(int id);
int skill_get_range(int id,int lv);
int skill_get_hp(int id,int lv);
int skill_get_sp(int id,int lv);
int skill_get_zeny(int id,int lv);
int skill_get_num(int id,int lv);
int skill_get_cast(int id,int lv);
int skill_get_fixedcast(int id ,int lv);
int skill_get_delay(int id,int lv);
int skill_get_time(int id ,int lv);
int skill_get_time2(int id,int lv);
int skill_get_castdef(int id);
int skill_get_weapontype(int id);
int skill_get_inf2(int id);
int skill_get_maxcount(int id,int lv);
int skill_get_blewcount(int id,int lv);
int skill_get_unit_id(int id,int flag);
int skill_get_unit_layout_type(int id,int lv);
int skill_get_unit_interval(int id);
int skill_get_unit_range(int id);
int skill_get_unit_target(int id);
int skill_get_unit_flag(int id);
int skill_get_arrow_cost(int id,int lv);
int skill_get_arrow_type(int id);
int skill_get_cloneable(int id);
int skill_get_misfire(int id);
int skill_get_zone(int id);
int skill_get_damage_rate(int id,int type);

// スキルの使用
void skill_castend_map(struct map_session_data *sd, int skill_num, const char *map);

int skill_cleartimerskill(struct block_list *src);
int skill_addtimerskill(struct block_list *src,unsigned int tick,int target,int x,int y,int skill_id,int skill_lv,int type,int flag);

// 追加効果
int skill_additional_effect( struct block_list* src, struct block_list *bl,int skillid,int skilllv,int attack_type,unsigned int tick);

enum {	//吹き飛ばしフラグ
	SAB_NOMALBLOW   = 0x00000,
	SAB_REVERSEBLOW = 0x10000,
	SAB_NODAMAGE    = 0x20000,
	SAB_NOPATHSTOP  = 0x40000,
};

int skill_add_blown( struct block_list *src, struct block_list *target,int skillid,int flag);

//カード効果のオートスペル
int skill_use_bonus_autospell(struct block_list * src,struct block_list * bl,int skill_id,int skill_lv,int rate,long skill_flag,int tick,int flag);
int skill_bonus_autospell(struct block_list * src,struct block_list * bl,long mode,int tick,int flag);

// ユニットスキル
struct skill_unit *skill_initunit(struct skill_unit_group *group,int idx,int x,int y);
int skill_delunit(struct skill_unit *unit);
struct skill_unit_group *skill_initunitgroup(struct block_list *src,int count,int skillid,int skilllv,int unit_id);
int skill_delunitgroup(struct skill_unit_group *group);
int skill_clear_unitgroup(struct block_list *src);

int skill_unit_ondamaged(struct skill_unit *src,struct block_list *bl,int damage,unsigned int tick);

int skill_castfix( struct block_list *bl, int time );
int skill_delayfix( struct block_list *bl, int time, int cast );
int skill_check_unit_range(int m,int x,int y,int skillid, int skilllv);
int skill_check_unit_range2(int m,int x,int y,int skillid, int skilllv);
int skill_unit_move(struct block_list *bl,unsigned int tick,int flag);
int skill_unit_move_unit_group( struct skill_unit_group *group, int m,int dx,int dy);

int skill_hermode_wp_check(struct block_list *bl,int range);

struct skill_unit_group *skill_check_dancing( struct block_list *src );
void skill_stop_dancing(struct block_list *src, int flag);
void skill_stop_gravitation(struct block_list *src);

// 詠唱キャンセル
int skill_castcancel(struct block_list *bl,int type);

int skill_gangsterparadise(struct map_session_data *sd ,int type);
void skill_brandishspear_first(struct square *tc,int dir,int x,int y);
void skill_brandishspear_dir(struct square *tc,int dir,int are);
void skill_autospell(struct map_session_data *sd, int skillid);
void skill_devotion(struct map_session_data *md,int target);
void skill_devotion2(struct block_list *bl,int crusader);
int skill_devotion3(struct map_session_data *sd,int target);
void skill_devotion_end(struct map_session_data *md,struct map_session_data *sd,int target);
int skill_marionette(struct map_session_data *sd,int target);
void skill_marionette2(struct map_session_data *sd,int src);
int skill_tarot_card_of_fate(struct block_list *src,struct block_list *target,int skillid,int skilllv,int tick,int flag,int wheel);

#define skill_calc_heal(bl,skill_lv) (( status_get_lv(bl)+status_get_int(bl) )/8 *(4+ skill_lv*8))
int skill_castend_id( int tid, unsigned int tick, int id,int data );
int skill_castend_pos( int tid, unsigned int tick, int id,int data );

// その他
int skill_check_cloaking(struct block_list *bl);

// スキル使用かどうかの判定。

// 判定関数に渡す構造体。関数内部でデータが上書きされるので、
// 戻った後に変更するのを忘れないように。
struct skill_condition {
	int id;
	int lv;
	int x;
	int y;
	int target;
};

int skill_check_condition(struct block_list *bl, int type);
int skill_check_condition2(struct block_list *bl, struct skill_condition *sc, int type);

// アイテム作成
int skill_can_produce_mix(struct map_session_data *sd, int idx, int trigger);
void skill_produce_mix(struct map_session_data *sd, int nameid, int slot1, int slot2, int slot3);
int skill_am_twilight1(struct map_session_data* sd);
int skill_am_twilight2(struct map_session_data* sd);
int skill_am_twilight3(struct map_session_data* sd);

void skill_arrow_create(struct map_session_data *sd, int nameid);
void skill_repair_weapon(struct map_session_data *sd, int idx);

// mobスキルのため
int skill_castend_nodamage_id( struct block_list *src, struct block_list *bl,int skillid,int skilllv,unsigned int tick,int flag );
int skill_castend_damage_id( struct block_list* src, struct block_list *bl,int skillid,int skilllv,unsigned int tick,int flag );
int skill_castend_pos2( struct block_list *src, int x,int y,int skillid,int skilllv,unsigned int tick,int flag);

int skill_cloneable(int skillid);
int skill_upperskill(int skillid);
int skill_mobskill(int skillid);
int skill_abraskill(int skillid);
int skill_clone(struct map_session_data* sd,int skillid,int skilllv);


void skill_weapon_refine(struct map_session_data *sd, int idx);
int skill_success_weaponrefine(struct map_session_data *sd,int idx);
int skill_fail_weaponrefine(struct map_session_data *sd,int idx);

// スキル攻撃一括処理
int skill_blown( struct block_list *src, struct block_list *target,int count);

int skill_castend_delay (struct block_list* src, struct block_list *bl,int skillid,int skilllv,unsigned int tick,int flag);

// バシリカ発動停止
void skill_basilica_cancel( struct block_list *bl );

// 罠スキルかどうか
#define skill_unit_istrap(id) (((id) >= UNT_BLASTMINE) && ((id) <= UNT_TALKIEBOX) && ((id) != UNT_VENOMDUST))

void skill_reload(void);

enum {
	SST_NONE,SST_HIDING,SST_CLOAKING,SST_CHASEWALKING,SST_HIDDEN,SST_RIDING,SST_FALCON,SST_CART,SST_SHIELD,SST_SIGHT,SST_EXPLOSIONSPIRITS,
	SST_RECOV_WEIGHT_RATE,SST_MOVE_ENABLE,SST_WATER,
};

enum {
	NV_BASIC = 1,

	SM_SWORD,
	SM_TWOHAND,
	SM_RECOVERY,
	SM_BASH,
	SM_PROVOKE,
	SM_MAGNUM,
	SM_ENDURE,

	MG_SRECOVERY,
	MG_SIGHT,
	MG_NAPALMBEAT,
	MG_SAFETYWALL,
	MG_SOULSTRIKE,
	MG_COLDBOLT,
	MG_FROSTDIVER,
	MG_STONECURSE,
	MG_FIREBALL,
	MG_FIREWALL,
	MG_FIREBOLT,
	MG_LIGHTNINGBOLT,
	MG_THUNDERSTORM,
	AL_DP,
	AL_DEMONBANE,
	AL_RUWACH,
	AL_PNEUMA,
	AL_TELEPORT,
	AL_WARP,
	AL_HEAL,
	AL_INCAGI,
	AL_DECAGI,
	AL_HOLYWATER,
	AL_CRUCIS,
	AL_ANGELUS,
	AL_BLESSING,
	AL_CURE,

	MC_INCCARRY,
	MC_DISCOUNT,
	MC_OVERCHARGE,
	MC_PUSHCART,
	MC_IDENTIFY,
	MC_VENDING,
	MC_MAMMONITE,

	AC_OWL,
	AC_VULTURE,
	AC_CONCENTRATION,
	AC_DOUBLE,
	AC_SHOWER,

	TF_DOUBLE,
	TF_MISS,
	TF_STEAL,
	TF_HIDING,
	TF_POISON,
	TF_DETOXIFY,

	ALL_RESURRECTION,

	KN_SPEARMASTERY,
	KN_PIERCE,
	KN_BRANDISHSPEAR,
	KN_SPEARSTAB,
	KN_SPEARBOOMERANG,
	KN_TWOHANDQUICKEN,
	KN_AUTOCOUNTER,
	KN_BOWLINGBASH,
	KN_RIDING,
	KN_CAVALIERMASTERY,

	PR_MACEMASTERY,
	PR_IMPOSITIO,
	PR_SUFFRAGIUM,
	PR_ASPERSIO,
	PR_BENEDICTIO,
	PR_SANCTUARY,
	PR_SLOWPOISON,
	PR_STRECOVERY,
	PR_KYRIE,
	PR_MAGNIFICAT,
	PR_GLORIA,
	PR_LEXDIVINA,
	PR_TURNUNDEAD,
	PR_LEXAETERNA,
	PR_MAGNUS,

	WZ_FIREPILLAR,
	WZ_SIGHTRASHER,
	WZ_FIREIVY,
	WZ_METEOR,
	WZ_JUPITEL,
	WZ_VERMILION,
	WZ_WATERBALL,
	WZ_ICEWALL,
	WZ_FROSTNOVA,
	WZ_STORMGUST,
	WZ_EARTHSPIKE,
	WZ_HEAVENDRIVE,
	WZ_QUAGMIRE,
	WZ_ESTIMATION,

	BS_IRON,
	BS_STEEL,
	BS_ENCHANTEDSTONE,
	BS_ORIDEOCON,
	BS_DAGGER,
	BS_SWORD,
	BS_TWOHANDSWORD,
	BS_AXE,
	BS_MACE,
	BS_KNUCKLE,
	BS_SPEAR,
	BS_HILTBINDING,
	BS_FINDINGORE,
	BS_WEAPONRESEARCH,
	BS_REPAIRWEAPON,
	BS_SKINTEMPER,
	BS_HAMMERFALL,
	BS_ADRENALINE,
	BS_WEAPONPERFECT,
	BS_OVERTHRUST,
	BS_MAXIMIZE,

	HT_SKIDTRAP,
	HT_LANDMINE,
	HT_ANKLESNARE,
	HT_SHOCKWAVE,
	HT_SANDMAN,
	HT_FLASHER,
	HT_FREEZINGTRAP,
	HT_BLASTMINE,
	HT_CLAYMORETRAP,
	HT_REMOVETRAP,
	HT_TALKIEBOX,
	HT_BEASTBANE,
	HT_FALCON,
	HT_STEELCROW,
	HT_BLITZBEAT,
	HT_DETECTING,
	HT_SPRINGTRAP,

	AS_RIGHT,
	AS_LEFT,
	AS_KATAR,
	AS_CLOAKING,
	AS_SONICBLOW,
	AS_GRIMTOOTH,
	AS_ENCHANTPOISON,
	AS_POISONREACT,
	AS_VENOMDUST,
	AS_SPLASHER,

	NV_FIRSTAID,
	NV_TRICKDEAD,
	SM_MOVINGRECOVERY,
	SM_FATALBLOW,
	SM_AUTOBERSERK,
	AC_MAKINGARROW,
	AC_CHARGEARROW,
	TF_SPRINKLESAND,
	TF_BACKSLIDING,
	TF_PICKSTONE,
	TF_THROWSTONE,
	MC_CARTREVOLUTION,
	MC_CHANGECART,
	MC_LOUD,
	AL_HOLYLIGHT,
	MG_ENERGYCOAT,

	NPC_PIERCINGATT=158,
	NPC_MENTALBREAKER,
	NPC_RANGEATTACK,
	NPC_ATTRICHANGE,
	NPC_CHANGEWATER,
	NPC_CHANGEGROUND,
	NPC_CHANGEFIRE,
	NPC_CHANGEWIND,
	NPC_CHANGEPOISON,
	NPC_CHANGEHOLY,
	NPC_CHANGETELEKINESIS,
	NPC_CHANGEDARKNESS,
	NPC_CRITICALSLASH,
	NPC_COMBOATTACK,
	NPC_GUIDEDATTACK,
	NPC_SELFDESTRUCTION,
	NPC_SPLASHATTACK,
	NPC_SUICIDE,
	NPC_POISON,
	NPC_BLINDATTACK,
	NPC_SILENCEATTACK,
	NPC_STUNATTACK,
	NPC_PETRIFYATTACK,
	NPC_CURSEATTACK,
	NPC_SLEEPATTACK,
	NPC_RANDOMATTACK,
	NPC_WATERATTACK,
	NPC_GROUNDATTACK,
	NPC_FIREATTACK,
	NPC_WINDATTACK,
	NPC_POISONATTACK,
	NPC_HOLYATTACK,
	NPC_DARKNESSATTACK,
	NPC_TELEKINESISATTACK,
	NPC_MAGICALATTACK,
	NPC_METAMORPHOSIS,
	NPC_PROVOCATION,
	NPC_SMOKING,
	NPC_SUMMONSLAVE,
	NPC_EMOTION,
	NPC_TRANSFORMATION,
	NPC_BLOODDRAIN,
	NPC_ENERGYDRAIN,
	NPC_KEEPING,
	NPC_DARKBREATH,
	NPC_DARKBLESSING,
	NPC_BARRIER,
	NPC_DEFENDER,
	NPC_LICK,
	NPC_HALLUCINATION,
	NPC_REBIRTH,
	NPC_SUMMONMONSTER,

	RG_SNATCHER,
	RG_STEALCOIN,
	RG_BACKSTAP,
	RG_TUNNELDRIVE,
	RG_RAID,
	RG_STRIPWEAPON,
	RG_STRIPSHIELD,
	RG_STRIPARMOR,
	RG_STRIPHELM,
	RG_INTIMIDATE,
	RG_GRAFFITI,
	RG_FLAGGRAFFITI,
	RG_CLEANER,
	RG_GANGSTER,
	RG_COMPULSION,
	RG_PLAGIARISM,

	AM_AXEMASTERY,
	AM_LEARNINGPOTION,
	AM_PHARMACY,
	AM_DEMONSTRATION,
	AM_ACIDTERROR,
	AM_POTIONPITCHER,
	AM_CANNIBALIZE,
	AM_SPHEREMINE,
	AM_CP_WEAPON,
	AM_CP_SHIELD,
	AM_CP_ARMOR,
	AM_CP_HELM,
	AM_BIOETHICS,
	AM_BIOTECHNOLOGY,
	AM_CREATECREATURE,
	AM_CULTIVATION,
	AM_FLAMECONTROL,
	AM_CALLHOMUN,
	AM_REST,
	AM_DRILLMASTER,
	AM_HEALHOMUN,
	AM_RESURRECTHOMUN,

	CR_TRUST,
	CR_AUTOGUARD,
	CR_SHIELDCHARGE,
	CR_SHIELDBOOMERANG,
	CR_REFLECTSHIELD,
	CR_HOLYCROSS,
	CR_GRANDCROSS,
	CR_DEVOTION,
	CR_PROVIDENCE,
	CR_DEFENDER,
	CR_SPEARQUICKEN,

	MO_IRONHAND,
	MO_SPIRITSRECOVERY,
	MO_CALLSPIRITS,
	MO_ABSORBSPIRITS,
	MO_TRIPLEATTACK,
	MO_BODYRELOCATION,
	MO_DODGE,
	MO_INVESTIGATE,
	MO_FINGEROFFENSIVE,
	MO_STEELBODY,
	MO_BLADESTOP,
	MO_EXPLOSIONSPIRITS,
	MO_EXTREMITYFIST,
	MO_CHAINCOMBO,
	MO_COMBOFINISH,

	SA_ADVANCEDBOOK,
	SA_CASTCANCEL,
	SA_MAGICROD,
	SA_SPELLBREAKER,
	SA_FREECAST,
	SA_AUTOSPELL,
	SA_FLAMELAUNCHER,
	SA_FROSTWEAPON,
	SA_LIGHTNINGLOADER,
	SA_SEISMICWEAPON,
	SA_DRAGONOLOGY,
	SA_VOLCANO,
	SA_DELUGE,
	SA_VIOLENTGALE,
	SA_LANDPROTECTOR,
	SA_DISPELL,
	SA_ABRACADABRA,
	SA_MONOCELL,
	SA_CLASSCHANGE,
	SA_SUMMONMONSTER,
	SA_REVERSEORCISH,
	SA_DEATH,
	SA_FORTUNE,
	SA_TAMINGMONSTER,
	SA_QUESTION,
	SA_GRAVITY,
	SA_LEVELUP,
	SA_INSTANTDEATH,
	SA_FULLRECOVERY,
	SA_COMA,

	BD_ADAPTATION,
	BD_ENCORE,
	BD_LULLABY,
	BD_RICHMANKIM,
	BD_ETERNALCHAOS,
	BD_DRUMBATTLEFIELD,
	BD_RINGNIBELUNGEN,
	BD_ROKISWEIL,
	BD_INTOABYSS,
	BD_SIEGFRIED,
	BD_RAGNAROK,

	BA_MUSICALLESSON,
	BA_MUSICALSTRIKE,
	BA_DISSONANCE,
	BA_FROSTJOKE,
	BA_WHISTLE,
	BA_ASSASSINCROSS,
	BA_POEMBRAGI,
	BA_APPLEIDUN,

	DC_DANCINGLESSON,
	DC_THROWARROW,
	DC_UGLYDANCE,
	DC_SCREAM,
	DC_HUMMING,
	DC_DONTFORGETME,
	DC_FORTUNEKISS,
	DC_SERVICEFORYOU,

	WE_MALE = 334,
	WE_FEMALE,
	WE_CALLPARTNER,

	NPC_SELFDESTRUCTION2 = 331,
	ITM_TOMAHAWK = 337,
	NPC_DARKCROSS,
	NPC_DARKGRANDCROSS,
	NPC_DARKSOULSTRIKE,
	NPC_DARKJUPITEL,
	NPC_HOLDWEB,
	NPC_BREAKWEAPON,
	NPC_BREAKARMOR,
	NPC_BREAKHELM,
	NPC_BREAKSIELD,
	NPC_UNDEADATTACK,
	NPC_RUNAWAY = 348,
	NPC_EXPLOSIONSPIRITS,
	NPC_INCREASEFLEE,
	NPC_ELEMENTUNDEAD,
	NPC_INVISIBLE,
	NPC_RECALL = 354,

	LK_AURABLADE = 355,
	LK_PARRYING,
	LK_CONCENTRATION,
	LK_TENSIONRELAX,
	LK_BERSERK,
	LK_FURY,
	HP_ASSUMPTIO,
	HP_BASILICA,
	HP_MEDITATIO,
	HW_SOULDRAIN,
	HW_MAGICCRASHER,
	HW_MAGICPOWER,
	PA_PRESSURE,
	PA_SACRIFICE,
	PA_GOSPEL,
	CH_PALMSTRIKE,
	CH_TIGERFIST,
	CH_CHAINCRUSH,
	PF_HPCONVERSION,
	PF_SOULCHANGE,
	PF_SOULBURN,
	ASC_KATAR,
	ASC_HALLUCINATION,
	ASC_EDP,
	ASC_BREAKER,
	SN_SIGHT,
	SN_FALCONASSAULT,
	SN_SHARPSHOOTING,
	SN_WINDWALK,
	WS_MELTDOWN,
	WS_CREATECOIN,
	WS_CREATENUGGET,
	WS_CARTBOOST,
	WS_SYSTEMCREATE,
	ST_CHASEWALK,
	ST_REJECTSWORD,
	ST_STEALBACKPACK,
	CR_ALCHEMY,
	CR_SYNTHESISPOTION,
	CG_ARROWVULCAN,
	CG_MOONLIT,
	CG_MARIONETTE,
	LK_SPIRALPIERCE,
	LK_HEADCRUSH,
	LK_JOINTBEAT,
	HW_NAPALMVULCAN,
	CH_SOULCOLLECT,
	PF_MINDBREAKER,
	PF_MEMORIZE,
	PF_FOGWALL,
	PF_SPIDERWEB,
	ASC_METEORASSAULT,
	ASC_CDP,
	WE_BABY,
	WE_CALLPARENT,
	WE_CALLBABY,
	TK_RUN,
	TK_READYSTORM,
	TK_STORMKICK,
	TK_READYDOWN,
	TK_DOWNKICK,
	TK_READYTURN,
	TK_TURNKICK,
	TK_READYCOUNTER,
	TK_COUNTER,
	TK_DODGE,
	TK_JUMPKICK,
	TK_HPTIME,
	TK_SPTIME,
	TK_POWER,
	TK_SEVENWIND,
	TK_HIGHJUMP,
	SG_FEEL,
	SG_SUN_WARM,
	SG_MOON_WARM,
	SG_STAR_WARM,
	SG_SUN_COMFORT,
	SG_MOON_COMFORT,
	SG_STAR_COMFORT,
	SG_HATE,
	SG_SUN_ANGER,
	SG_MOON_ANGER,
	SG_STAR_ANGER,
	SG_SUN_BLESS,
	SG_MOON_BLESS,
	SG_STAR_BLESS,
	SG_DEVIL,
	SG_FRIEND,
	SG_KNOWLEDGE,
	SG_FUSION,
	SL_ALCHEMIST,
	AM_BERSERKPITCHER,
	SL_MONK,
	SL_STAR,
	SL_SAGE,
	SL_CRUSADER,
	SL_SUPERNOVICE,
	SL_KNIGHT,
	SL_WIZARD,
	SL_PRIEST,
	SL_BARDDANCER,
	SL_ROGUE,
	SL_ASSASIN,
	SL_BLACKSMITH,
	BS_ADRENALINE2,
	SL_HUNTER,
	SL_SOULLINKER,
	SL_KAIZEL,
	SL_KAAHI,
	SL_KAUPE,
	SL_KAITE,
	SL_KAINA,
	SL_STIN,
	SL_STUN,
	SL_SMA,
	SL_SWOO,
	SL_SKE,
	SL_SKA,

	ST_PRESERVE = 475,
	ST_FULLSTRIP,
	WS_WEAPONREFINE,
	CR_SLIMPITCHER,
	CR_FULLPROTECTION,
	PA_SHIELDCHAIN,
	HP_MANARECHARGE,
	PF_DOUBLECASTING,
	HW_GANBANTEIN,
	HW_GRAVITATION,
	WS_CARTTERMINATION,
	WS_OVERTHRUSTMAX,
	CG_LONGINGFREEDOM,
	CG_HERMODE,
	CG_TAROTCARD,
	CR_ACIDDEMONSTRATION,
	CR_CULTIVATION,
	// = 492,
	TK_MISSION		= 493,
	SL_HIGH			= 494,
	KN_ONEHAND		= 495,
	AM_TWILIGHT1	= 496,
	AM_TWILIGHT2	= 497,
	AM_TWILIGHT3	= 498,
	HT_POWER 		= 499,

	GS_GLITTERING   = 500,//#GS_GLITTERING#
	GS_FLING,//#GS_FLING#
	GS_TRIPLEACTION,//#GS_TRIPLEACTION#
	GS_BULLSEYE,//#GS_BULLSEYE#
	GS_MADNESSCANCEL,//#GS_MADNESSCANCEL#
	GS_ADJUSTMENT,//#GS_ADJUSTMENT#
	GS_INCREASING,//#GS_INCREASING#
	GS_MAGICALBULLET,//#GS_MAGICALBULLET#
	GS_CRACKER,//#GS_CRACKER#
	GS_SINGLEACTION,//#GS_SINGLEACTION#
	GS_SNAKEEYE,//#GS_SNAKEEYE#	
	GS_CHAINACTION,//#GS_CHAINACTION#
	GS_TRACKING,//#GS_TRACKING#
	GS_DISARM,//#GS_DISARM#
	GS_PIERCINGSHOT,//#GS_PIERCINGSHOT#
	GS_RAPIDSHOWER,//#GS_RAPIDSHOWER#
	GS_DESPERADO,//#GS_DESPERADO#
	GS_GATLINGFEVER,//#GS_GATLINGFEVER#
	GS_DUST,//#GS_DUST#
	GS_FULLBUSTER,//#GS_FULLBUSTER#
	GS_SPREADATTACK,//#GS_SPREADATTACK#
	GS_GROUNDDRIFT,//#GS_GROUNDDRIFT#

	NJ_TOBIDOUGU,//#NJ_TOBIDOUGU#
	NJ_SYURIKEN,//#NJ_SYURIKEN#
	NJ_KUNAI,//#NJ_KUNAI#
	NJ_HUUMA,//#NJ_HUUMA#
	NJ_ZENYNAGE,//#NJ_ZENYNAGE#
	NJ_TATAMIGAESHI,//#NJ_TATAMIGAESHI#
	NJ_KASUMIKIRI,//#NJ_KASUMIKIRI#
	NJ_SHADOWJUMP,//#NJ_SHADOWJUMP#
	NJ_KIRIKAGE,//#NJ_KIRIKAGE#
	NJ_UTSUSEMI,//#NJ_UTSUSEMI#
	NJ_BUNSINJYUTSU,//#NJ_BUNSINJYUTSU#
	NJ_NINPOU,//#NJ_NINPOU#
	NJ_KOUENKA,//#NJ_KOUENKA#
	NJ_KAENSIN,//#NJ_KAENSIN#
	NJ_BAKUENRYU,//#NJ_BAKUENRYU#
	NJ_HYOUSENSOU,//#NJ_HYOUSENSOU#
	NJ_SUITON,//#NJ_SUITON#
	NJ_HYOUSYOURAKU,//#NJ_HYOUSYOURAKU#
	NJ_HUUJIN,//#NJ_HUUJIN#
	NJ_RAIGEKISAI,//#NJ_RAIGEKISAI#
	NJ_KAMAITACHI,//#NJ_KAMAITACHI#
	NJ_NEN,//#NJ_NEN#
	NJ_ISSEN,//#NJ_ISSEN#

	MB_FIGHTING		=545,//#ファイティング#
	MB_NEUTRAL,//#ニュートラル,//#
	MB_TAIMING_PUTI,//#テイミングプティ,//#
	MB_WHITEPOTION,//#ホワイトポーション,//#
	MB_CARDPITCHER,//#カードピッチャー,//#
	MB_MENTAL,//#メンタル,//#
	MB_PETPITCHER,//#ペットピッチャー,//#
	MB_BODYSTUDY,//#ボディスタディ,//#
	MB_BODYALTER,//#ボディオルター,//#
	MB_PETMEMORY,//#ペットメモリー,//#
	MB_M_TELEPORT,//#テレポート,//#
	MB_B_GAIN,//#ゲイン,//#
	MB_M_GAIN,//#ゲイン,//#
	MB_MISSION,//#ミッション,//#
	MB_MUNAKKNOWLEDGE,//#ムナックノウリッジ,//#
	MB_MUNAKBALL,//#ムナックボール,//#
	MB_SCROLL,//#スクロール,//#
	MB_B_GATHERING,//#ギャザリング,//#
	MB_B_EXCLUDE,//#エクスクルード,//#
	MB_B_DRIFT,//#ドリフト,//#
	MB_M_DRIFT,//#ドリフト,//#
	MB_B_WALLRUSH,//#ウォールラッシュ,//#
	MB_M_WALLRUSH,//#ウォールラッシュ,//#
	MB_B_WALLSHIFT,//#ウォールシフト,//#
	MB_M_WALLCRASH,//#ウォールクラッシュ,//#
	MB_M_REINCARNATION,//#リインカーネーション,//#
	MB_B_EQUIP,//#イクイップ,//#

	SL_DEATHKNIGHT	=572,//#デスナイトの魂,//#
	SL_COLLECTOR,//#ダークコレクターの魂,//#
	SL_NINJA,//#忍者の魂,//#
	SL_GUNNER,//#ガンスリンガーの魂,//#
	AM_TWILIGHT4,//#トワイライトファーマシー4,//#

	DE_PASSIVE		=577,//#パッシブ,//#
	DE_PATTACK,//#Pアタック,//#
	DE_PSPEED,//#Pスピード ,//#
	DE_PDEFENSE,//#Pディフェンス ,//#
	DE_PCRITICAL,//#Pクリティカル,//#
	DE_PHP,//#PHP,//#
	DE_PSP,//#PSP,//#
	DE_RESET,//#リセット,//#
	DE_RANKING,//#ランキング,//#
	DE_PTRIPLE,//#Pトリプル,//#
	DE_ENERGY,//#エナジー,//#
	DE_NIGHTMARE,//#ナイトメア,//#
	DE_SLASH,//#スラッシュ,//#
	DE_COIL,//#コイル,//#
	DE_WAVE,//#ウェーブ,//#
	DE_REBIRTH,//#リバース,//#
	DE_AURA,//#オーラ,//#
	DE_FREEZER,//#フリーザー,//#
	DE_CHANGEATTACK,//#チェンジアタック,//#
	DE_PUNISH,//#パニッシュ,//#
	DE_POISON,//#ポイズン,//#
	DE_INSTANT,//#インスタント,//#
	DE_WARNING,//#ワーニング,//#
	DE_RANKEDKNIFE,//#ランクドナイフ,//#
	DE_RANKEDGRADIUS,//#ランクドグラディウス,//#
	DE_GAUGE,//#Gオージェ,//#
	DE_GTIME,//#Gタイム,//#
	DE_GPAIN,//#Gペイン,//#
	DE_GSKILL,//#Gスキル,//#
	DE_GKILL,//#Gキル,//#
	DE_ACCEL,//#アクセル,//#
	DE_BLOCKDOUBLE,//#ダブルブロック,//#
	DE_BLOCKMELEE,//#メイレイブロック,//#
	DE_BLOCKFAR,//#ファーブロック,//#
	DE_FRONTATTACK,//#フロントアタック,//#
	DE_DANGERATTACK,//#デンジャーアタック,//#
	DE_TWINATTACK,//#ツインアタック,//#
	DE_WINDATTACK,//#ウィンドアタック,//#
	DE_WATERATTACK	=	615,//#ウォーターアタック,//#

	KN_CHARGEATK	=	1001,//#チャージアタック#
	CR_SHRINK		=	1002,//#シュリンク#
	AS_SONICACCEL	=	1003,//#ソニックアクセラレーション#
	AS_VENOMKNIFE	=	1004,//#ベナムナイフ#
	RG_CLOSECONFINE	=	1005,//#クローズコンファイン#
	WZ_SIGHTBLASTER	=	1006,//#サイトブラスター#
	SA_CREATECON	=	1007,//#エルレメンタルコンバータ製造#
	SA_ELEMENTWATER	=	1008,//#エルレメンタルチェンジ（水）#
	HT_PHANTASMIC	=	1009,//#ファンタスミックアロー#
	BA_PANGVOICE	=	1010,//#パンボイス#
	DC_WINKCHARM	=	1011,//#魅惑のウィンク#
	BS_UNFAIRLYTRICK=	1012,//#アンフェアリートリック#
	BS_GREED		=	1013,//#貪欲#
	PR_REDEMPTIO	=	1014,//#レデムプティオ#
	MO_KITRANSLATION=	1015,//#珍奇注入(振気注入)#
	MO_BALKYOUNG	=	1016,//#足頃(発勁)#
	SA_ELEMENTGROUND=	1017,
	SA_ELEMENTFIRE	=	1018,
	SA_ELEMENTWIND	=	1019,

	HM_SKILLBASE	=8001,
	HLIF_HEAL		=8001,//#治癒の手助け(ヒール)#
	HLIF_AVOID		=8002,//#緊急回避#
	HLIF_BRAIN		=8003,//=//#脳手術#
	HLIF_CHANGE		=8004,//#メンタルチェンジ#
	HAMI_CASTLE		=8005,//#キャストリング#
	HAMI_DEFENCE	=8006,//#ディフェンス#
	HAMI_SKIN		=8007,//#アダマンティウムスキン#
	HAMI_BLOODLUST	=8008,//#ブラッドラスト#
	HFLI_MOON		=8009,//#ムーンライト#
	HFLI_FLEET		=8010,//#フリートムーブ#
	HFLI_SPEED		=8011,//#オーバードスピード#
	HFLI_SBR44		=8012,//#S.B.R.44#
	HVAN_CAPRICE	=8013,//#カプリス#
	HVAN_CHAOTIC	=8014,//#カオティックベネディクション#
	HVAN_INSTRUCT	=8015,//#チェンジインストラクション#
	HVAN_EXPLOSION	=8016,//#バイオエクスプロージョン#

	GD_SKILLBASE=10000,
	GD_APPROVAL=10000,
	GD_KAFRACONTACT,
	GD_GUARDIANRESEARCH,
	GD_GUARDUP,
	//GD_CHARISMA, -> GD_GUARDUPに変更あり
	// GD_GURADUP,	// GD)CHARISMAと同ID
	GD_EXTENSION,
	GD_GLORYGUILD,
	GD_LEADERSHIP,
	GD_GLORYWOUNDS,
	GD_SOULCOLD,
	GD_HAWKEYES,
	GD_BATTLEORDER,
	GD_REGENERATION,
	GD_RESTORE,
	GD_EMERGENCYCALL,
	GD_DEVELOPMENT,
};

enum {
	UNT_SAFETYWALL = 0x7e,
	UNT_FIREWALL,
	UNT_WARP_ACTIVE,
	UNT_WARP_WAITING,
	//0x82
	UNT_SANCTUARY = 0x83,
	UNT_MAGNUS,
	UNT_PNEUMA,
	UNT_ATTACK_SKILLS,	// 攻撃系スキル全般
	UNT_FIREPILLAR_WAITING,
	UNT_FIREPILLAR_ACTIVE,
	UNT_MOONLIT,
	//0x8a
	//0x8b
	UNT_USED_TRAPS = 0x8c,
	UNT_ICEWALL,
	UNT_QUAGMIRE,
	UNT_BLASTMINE,
	UNT_SKIDTRAP,
	UNT_ANKLESNARE,
	UNT_VENOMDUST,
	UNT_LANDMINE,
	UNT_SHOCKWAVE,
	UNT_SANDMAN,
	UNT_FLASHER,
	UNT_FREEZINGTRAP,
	UNT_CLAYMORETRAP,
	UNT_TALKIEBOX,
	UNT_VOLCANO,
	UNT_DELUGE,
	UNT_VIOLENTGALE,
	UNT_LANDPROTECTOR,
	UNT_LULLABY,
	UNT_RICHMANKIM,
	UNT_ETERNALCHAOS,
	UNT_DRUMBATTLEFIELD,
	UNT_RINGNIBELUNGEN,
	UNT_ROKISWEIL,
	UNT_INTOABYSS,
	UNT_SIEGFRIED,
	UNT_DISSONANCE,
	UNT_WHISTLE,
	UNT_ASSASSINCROSS,
	UNT_POEMBRAGI,
	UNT_APPLEIDUN,
	UNT_UGLYDANCE,
	UNT_HUMMING,
	UNT_DONTFORGETME,
	UNT_FORTUNEKISS,
	UNT_SERVICEFORYOU,
	UNT_GRAFFITI,
	UNT_DEMONSTRATION,
	UNT_CALLFAMILY,
	UNT_GOSPEL,
	UNT_BASILICA,
	//0xb5
	UNT_FOGWALL = 0xb6,
	UNT_SPIDERWEB,
	UNT_GRAVITATION,
	UNT_HERMODE,
	UNT_DESPERADO,	// エフェクト無しを利用して暫定
	UNT_SUITON = 0xbb,
	UNT_TATAMIGAESHI,
	UNT_KAENSIN,
	UNT_GROUNDDRIFT_WIND,
	UNT_GROUNDDRIFT_DARK,
	UNT_GROUNDDRIFT_POISON,
	UNT_GROUNDDRIFT_WATER,
	UNT_GROUNDDRIFT_FIRE,
};

extern int SkillStatusChangeTable[];
extern int GuildSkillStatusChangeTable[];

struct skill_unit_group *skill_unitsetting( struct block_list *src, int skillid,int skilllv,int x,int y,int flag);

#endif

