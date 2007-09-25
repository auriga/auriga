#ifndef _STATUS_H_
#define _STATUS_H_

struct status_pretimer {
	int timer;
	int target_id;
	int map;
	int type;
	int val1,val2,val3,val4;
	int tick;
	int flag;
};

// ステータス異常データベース
struct scdata_db {
	short save;
	int releasable;
	int disable;
};

// パラメータ取得系
int status_get_class(struct block_list *bl);
int status_get_dir(struct block_list *bl);
int status_get_lv(struct block_list *bl);
int status_get_range(struct block_list *bl);
int status_get_group(struct block_list *bl);
int status_get_hp(struct block_list *bl);
int status_get_sp(struct block_list *bl);
int status_get_max_hp(struct block_list *bl);
int status_get_str(struct block_list *bl);
int status_get_agi(struct block_list *bl);
int status_get_vit(struct block_list *bl);
int status_get_int(struct block_list *bl);
int status_get_dex(struct block_list *bl);
int status_get_luk(struct block_list *bl);
int status_get_hit(struct block_list *bl);
int status_get_flee(struct block_list *bl);
int status_get_def(struct block_list *bl);
int status_get_mdef(struct block_list *bl);
int status_get_flee2(struct block_list *bl);
int status_get_def2(struct block_list *bl);
int status_get_mdef2(struct block_list *bl);
int status_get_baseatk(struct block_list *bl);
int status_get_atk(struct block_list *bl);
int status_get_atk2(struct block_list *bl);
int status_get_speed(struct block_list *bl);
int status_get_adelay(struct block_list *bl);
int status_get_amotion(struct block_list *bl);
int status_get_dmotion(struct block_list *bl);
int status_get_element(struct block_list *bl);
int status_get_attack_element(struct block_list *bl);
int status_get_attack_element2(struct block_list *bl);
int status_get_attack_element_nw(struct block_list *bl);
#define status_get_elem_type(bl)	(status_get_element(bl)%20)
#define status_get_elem_level(bl)	(status_get_element(bl)/20)
int status_get_party_id(struct block_list *bl);
int status_get_guild_id(struct block_list *bl);
int status_get_race(struct block_list *bl);
int status_get_size(struct block_list *bl);
int status_get_mode(struct block_list *bl);
int status_get_mexp(struct block_list *bl);
int status_get_enemy_type(struct block_list *bl);
short status_get_clothes_color(struct block_list *bl);

struct status_change *status_get_sc_data(struct block_list *bl);
short *status_get_sc_count(struct block_list *bl);
unsigned short *status_get_opt1(struct block_list *bl);
unsigned short *status_get_opt2(struct block_list *bl);
unsigned int *status_get_opt3(struct block_list *bl);
unsigned int *status_get_option(struct block_list *bl);

int status_get_matk1(struct block_list *bl);
int status_get_matk2(struct block_list *bl);
int status_get_critical(struct block_list *bl);
int status_get_atk_(struct block_list *bl);
int status_get_atk_2(struct block_list *bl);
int status_get_atk2(struct block_list *bl);
int status_get_aspd(struct block_list *bl);

// 状態異常関連
int status_can_save(int type);
int status_is_disable(int type,int mask);
int status_change_start(struct block_list *bl,int type,int val1,int val2,int val3,int val4,int tick,int flag);
int status_change_end(struct block_list* bl, int type, int tid);
int status_change_pretimer(struct block_list *bl,int type,int val1,int val2,int val3,int val4,int tick,int flag,int pre_tick);
int status_change_timer(int tid, unsigned int tick, int id, int data);
int status_change_timer_sub(struct block_list *bl, va_list ap);
int status_change_race_end(struct block_list *bl,int type);
int status_change_soulstart(struct block_list *bl,int val1,int val2,int val3,int val4,int tick,int flag);
int status_change_soulclear(struct block_list *bl);
int status_change_resistclear(struct block_list *bl);
int status_enchant_armor_elemental_end(struct block_list *bl,int type);
int status_enchant_elemental_end(struct block_list *bl,int type);
int status_change_clear(struct block_list *bl,int type);
int status_change_release(struct block_list *bl,int mask);
int status_clearpretimer(struct block_list *bl);
int status_change_attacked_end(struct block_list *bl);
int status_change_hidden_end(struct block_list *bl);
int status_change_removemap_end(struct block_list *bl);

// 状態チェック
int status_check_no_magic_damage(struct block_list *bl);

#ifdef DYNAMIC_SC_DATA
int status_calloc_sc_data(struct block_list *bl);
int status_free_sc_data(struct block_list *bl);
int status_check_dummy_sc_data(struct block_list *bl);
extern struct status_change dummy_sc_data[MAX_STATUSCHANGE];
#endif

// ステータス計算
int status_calc_pc(struct map_session_data* sd,int first);
int status_get_overrefine_bonus(int lv);
int status_percentrefinery(struct map_session_data *sd,struct item *item);
int status_percentrefinery_weaponrefine(struct map_session_data *sd,struct item *item);
extern int current_equip_item_index;
extern int current_equip_card_id;

// DB再読込用
int status_readdb(void);

int do_init_status(void);

// ステータス異常番号テーブル
enum {
	SC_PROVOKE              = 0,
	SC_ENDURE               = 1,
	SC_TWOHANDQUICKEN       = 2,
	SC_CONCENTRATE          = 3,
	SC_HIDING               = 4,
	SC_CLOAKING             = 5,
	SC_ENCPOISON            = 6,
	SC_POISONREACT          = 7,
	SC_QUAGMIRE             = 8,
	SC_ANGELUS              = 9,
	SC_BLESSING             = 10,
	SC_SIGNUMCRUCIS         = 11,
	SC_INCREASEAGI          = 12,
	SC_DECREASEAGI          = 13,
	SC_SLOWPOISON           = 14,
	SC_IMPOSITIO            = 15,
	SC_SUFFRAGIUM           = 16,
	SC_ASPERSIO             = 17,
	SC_BENEDICTIO           = 18,
	SC_KYRIE                = 19,
	SC_MAGNIFICAT           = 20,
	SC_GLORIA               = 21,
	SC_AETERNA              = 22,
	SC_ADRENALINE           = 23,
	SC_WEAPONPERFECTION     = 24,
	SC_OVERTHRUST           = 25,
	SC_MAXIMIZEPOWER        = 26,
	//
	SC_TRICKDEAD            = 29,
	SC_LOUD                 = 30,
	SC_ENERGYCOAT           = 31,
	SC_PK_PENALTY           = 32,
	SC_REVERSEORCISH        = 33,
	SC_HALLUCINATION        = 34,
	//
	SC_SPEEDPOTION0         = 37,
	SC_SPEEDPOTION1         = 38,
	SC_SPEEDPOTION2         = 39,
	SC_SPEEDPOTION3         = 40,
	//
	//
	//
	//
	//
	//
	//
	//
	//
	SC_STRIPWEAPON          = 50,
	SC_STRIPSHIELD          = 51,
	SC_STRIPARMOR           = 52,
	SC_STRIPHELM            = 53,
	SC_CP_WEAPON            = 54,
	SC_CP_SHIELD            = 55,
	SC_CP_ARMOR             = 56,
	SC_CP_HELM              = 57,
	SC_AUTOGUARD            = 58,
	SC_REFLECTSHIELD        = 59,
	SC_DEVOTION             = 60,
	SC_PROVIDENCE           = 61,
	SC_DEFENDER             = 62,
	SC_SANTA                = 63,
	SC_SUMMER               = 64,
	SC_AUTOSPELL            = 65,
	//
	//
	SC_SPEARSQUICKEN        = 68,
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	SC_EXPLOSIONSPIRITS     = 86,
	SC_STEELBODY            = 87,
	//
	SC_COMBO                = 89,
	SC_FLAMELAUNCHER        = 90,
	SC_FROSTWEAPON          = 91,
	SC_LIGHTNINGLOADER      = 92,
	SC_SEISMICWEAPON        = 93,
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	SC_AURABLADE            = 103,
	SC_PARRYING             = 104,
	SC_CONCENTRATION        = 105,
	SC_TENSIONRELAX         = 106,
	SC_BERSERK              = 107,
	//
	//
	//
	SC_ASSUMPTIO            = 110,
	//
	//
	SC_MAGICPOWER           = 113,
	SC_EDP                  = 114,
	SC_TRUESIGHT            = 115,
	SC_WINDWALK             = 116,
	SC_MELTDOWN             = 117,
	SC_CARTBOOST            = 118,
	SC_CHASEWALK            = 119,
	SC_REJECTSWORD          = 120,
	SC_MARIONETTE           = 121,
	SC_MARIONETTE2          = 122,
	//
	SC_HEADCRUSH            = 124,
	SC_JOINTBEAT            = 125,
	//
	//
	SC_STONE                = 128,
	SC_FREEZE               = 129,
	SC_STAN                 = 130,
	SC_SLEEP                = 131,
	SC_POISON               = 132,
	SC_CURSE                = 133,
	SC_SILENCE              = 134,
	SC_CONFUSION            = 135,
	SC_BLIND                = 136,
	SC_BLEED                = 137,
	//
	//
	SC_SAFETYWALL           = 140,
	SC_PNEUMA               = 141,
	//
	SC_ANKLE                = 143,
	SC_DANCING              = 144,
	SC_KEEPING              = 145,
	SC_BARRIER              = 146,
	SC_TIGERFIST            = 147,
	//
	SC_MAGICROD             = 149,
	SC_SIGHT                = 150,
	SC_RUWACH               = 151,
	SC_AUTOCOUNTER          = 152,
	SC_VOLCANO              = 153,
	SC_DELUGE               = 154,
	SC_VIOLENTGALE          = 155,
	SC_BLADESTOP_WAIT       = 156,
	SC_BLADESTOP            = 157,
	SC_EXTREMITYFIST        = 158,
	SC_GRAFFITI             = 159,
	SC_LULLABY              = 160,
	SC_RICHMANKIM           = 161,
	SC_ETERNALCHAOS         = 162,
	SC_DRUMBATTLE           = 163,
	SC_NIBELUNGEN           = 164,
	SC_ROKISWEIL            = 165,
	SC_INTOABYSS            = 166,
	SC_SIEGFRIED            = 167,
	SC_DISSONANCE           = 168,
	SC_WHISTLE              = 169,
	SC_ASSNCROS             = 170,
	SC_POEMBRAGI            = 171,
	SC_APPLEIDUN            = 172,
	SC_UGLYDANCE            = 173,
	SC_HUMMING              = 174,
	SC_DONTFORGETME         = 175,
	SC_FORTUNE              = 176,
	SC_SERVICE4U            = 177,
	SC_BASILICA             = 178,
	SC_MINDBREAKER          = 179,
	SC_SPIDERWEB            = 180,
	SC_MEMORIZE             = 181,
	SC_DPOISON              = 182,
	//
	SC_SACRIFICE            = 184,
	SC_INCATK               = 185,
	SC_INCMATK              = 186,
	SC_WEDDING              = 187,
	SC_NOCHAT               = 188,
	SC_SPLASHER             = 189,
	SC_SELFDESTRUCTION      = 190,
	SC_MAGNUM               = 191,
	SC_GOSPEL               = 192,
	SC_INCALLSTATUS         = 193,
	SC_INCHIT               = 194,
	SC_INCFLEE              = 195,
	SC_INCMHP2              = 196,
	SC_INCMSP2              = 197,
	SC_INCATK2              = 198,
	SC_INCHIT2              = 199,
	SC_INCFLEE2             = 200,
	SC_PRESERVE             = 201,
	SC_OVERTHRUSTMAX        = 202,
	SC_CHASEWALK_STR        = 203,
	SC_WHISTLE_             = 204,
	SC_ASSNCROS_            = 205,
	SC_POEMBRAGI_           = 206,
	SC_APPLEIDUN_           = 207,
	SC_HUMMING_             = 209,
	SC_DONTFORGETME_        = 210,
	SC_FORTUNE_             = 211,
	SC_SERVICE4U_           = 212,
	SC_BATTLEORDER          = 213,
	SC_REGENERATION         = 214,
	//
	SC_POISONPOTION         = 219,
	SC_THE_MAGICIAN         = 220,
	SC_STRENGTH             = 221,
	SC_THE_DEVIL            = 222,
	SC_THE_SUN              = 223,
	SC_MEAL_INCSTR          = 224,
	SC_MEAL_INCAGI          = 225,
	SC_MEAL_INCVIT          = 226,
	SC_MEAL_INCINT          = 227,
	SC_MEAL_INCDEX          = 228,
	SC_MEAL_INCLUK          = 229,
	SC_RUN                  = 230,
	SC_SPURT                = 231,
	SC_TKCOMBO              = 232,
	SC_DODGE                = 233,
	SC_HERMODE              = 234,
	SC_TRIPLEATTACK_RATE_UP = 235,
	SC_COUNTER_RATE_UP      = 236,
	SC_WARM                 = 237,
	SC_SEVENWIND            = 238,
	//
	SC_SUN_COMFORT          = 240,
	SC_MOON_COMFORT         = 241,
	SC_STAR_COMFORT         = 242,
	SC_FUSION               = 243,
	SC_ALCHEMIST            = 244,
	SC_MONK                 = 245,
	SC_STAR                 = 246,
	SC_SAGE                 = 247,
	SC_CRUSADER             = 248,
	SC_SUPERNOVICE          = 249,
	SC_KNIGHT               = 250,
	SC_WIZARD               = 251,
	SC_PRIEST               = 252,
	SC_BARDDANCER           = 253,
	SC_ROGUE                = 254,
	SC_ASSASIN              = 255,
	SC_BLACKSMITH           = 256,
	SC_HUNTER               = 257,
	SC_SOULLINKER           = 258,
	SC_HIGH                 = 259,
	SC_DEATHKINGHT          = 260,
	SC_COLLECTOR            = 261,
	SC_NINJA                = 262,
	SC_GUNNER               = 263,
	SC_KAIZEL               = 264,
	SC_KAAHI                = 265,
	SC_KAUPE                = 266,
	SC_KAITE                = 267,
	SC_SMA                  = 268,
	SC_SWOO                 = 269,
	SC_SKE                  = 270,
	SC_SKA                  = 271,
	SC_ONEHAND              = 272,
	SC_READYSTORM           = 273,
	SC_READYDOWN            = 274,
	SC_READYTURN            = 275,
	SC_READYCOUNTER         = 276,
	SC_DODGE_DELAY          = 277,
	SC_AUTOBERSERK          = 278,
	//
	SC_DOUBLECASTING        = 280,
	SC_ELEMENTFIELD         = 281,
	SC_DARKELEMENT          = 282,
	SC_ATTENELEMENT         = 283,
	SC_MIRACLE              = 284,
	SC_ANGEL                = 285,
	SC_FORCEWALKING         = 286,
	SC_DOUBLE               = 287,
	//
	SC_BABY                 = 289,
	SC_LONGINGFREEDOM       = 290,
	SC_SHRINK               = 291,
	SC_CLOSECONFINE         = 292,
	SC_SIGHTBLASTER         = 293,
	SC_ELEMENTWATER         = 294,
	SC_MEAL_INCHIT          = 295,
	SC_MEAL_INCFLEE         = 296,
	SC_MEAL_INCFLEE2        = 297,
	SC_MEAL_INCCRITICAL     = 298,
	SC_MEAL_INCDEF          = 299,
	SC_MEAL_INCMDEF         = 300,
	SC_MEAL_INCATK          = 301,
	SC_MEAL_INCMATK         = 302,
	SC_MEAL_INCEXP          = 303,
	SC_MEAL_INCJOB          = 304,
	SC_ELEMENTGROUND        = 305,
	SC_ELEMENTFIRE          = 306,
	SC_ELEMENTWIND          = 307,
	SC_WINKCHARM            = 308,
	SC_ELEMENTPOISON        = 309,
	SC_ELEMENTDARK          = 310,
	SC_ELEMENTELEKINESIS    = 311,
	SC_ELEMENTUNDEAD        = 312,
	SC_UNDEADELEMENT        = 313,
	SC_ELEMENTHOLY          = 314,
	SC_NPC_DEFENDER         = 315,
	SC_RESISTWATER          = 316,
	SC_RESISTGROUND         = 317,
	SC_RESISTFIRE           = 318,
	SC_RESISTWIND           = 319,
	SC_RESISTPOISON         = 320,
	SC_RESISTHOLY           = 321,
	SC_RESISTDARK           = 322,
	SC_RESISTTELEKINESIS    = 323,
	SC_RESISTUNDEAD         = 324,
	SC_RESISTALL            = 325,
	SC_RACEUNKNOWN          = 326,
	SC_RACEUNDEAD           = 327,
	SC_RACEBEAST            = 328,
	SC_RACEPLANT            = 329,
	SC_RACEINSECT           = 330,
	SC_RACEFISH             = 332,
	SC_RACEDEVIL            = 333,
	SC_RACEHUMAN            = 334,
	SC_RACEANGEL            = 335,
	SC_RACEDRAGON           = 336,
	SC_TIGEREYE             = 337,
	SC_GRAVITATION_USER     = 338,
	SC_GRAVITATION          = 339,
	SC_FOGWALL              = 340,
	SC_FOGWALLPENALTY       = 341,
	SC_REDEMPTIO            = 342,
	//
	SC_HOLDWEB              = 344,
	SC_INVISIBLE            = 345,
	//
	SC_FLING                = 347,
	SC_MADNESSCANCEL        = 348,
	SC_ADJUSTMENT           = 349,
	SC_INCREASING           = 350,
	SC_DISARM               = 351,
	SC_GATLINGFEVER         = 352,
	SC_FULLBUSTER           = 353,
	SC_TATAMIGAESHI         = 354,
	SC_UTSUSEMI             = 355,
	SC_BUNSINJYUTSU         = 356,
	SC_SUITON               = 357,
	SC_NEN                  = 358,
	SC_AVOID                = 359,
	SC_CHANGE               = 360,
	SC_DEFENCE              = 361,
	SC_BLOODLUST            = 362,
	SC_FLEET                = 363,
	SC_SPEED                = 364,
	SC_ADRENALINE2          = 365,
	SC_STATUS_UNCHANGE      = 366,
	SC_INCDAMAGE            = 367,
	SC_COMBATHAN            = 368,
	SC_LIFEINSURANCE        = 369,
	SC_ITEMDROPRATE         = 370,
	SC_BOSSMAPINFO          = 371,
	SC_MEAL_INCSTR2         = 372,
	SC_MEAL_INCAGI2         = 373,
	SC_MEAL_INCVIT2         = 374,
	SC_MEAL_INCDEX2         = 375,
	SC_MEAL_INCINT2         = 376,
	SC_MEAL_INCLUK2         = 377,
	SC_SLOWCAST             = 378,
	SC_CRITICALWOUND        = 379,
	SC_MAGICMIRROR          = 380,
	SC_STONESKIN            = 381,
	SC_ANTIMAGIC            = 382,
	SC_WEAPONQUICKEN        = 383,

	// startでは使えないresistをアイテム側で全てクリアするための物
	SC_RESISTCLEAR          = 1001,
	SC_RACECLEAR            = 1002,
	SC_SOUL                 = 1003,
	SC_SOULCLEAR            = 1004,
};

// 状態アイコン
// 厳密にはキャラクターの色の変化なども含まれている(爆裂波動など)
enum {
	SI_BLANK            = 43,

	SI_PROVOKE          = 0,
	SI_ENDURE           = 1,
	SI_TWOHANDQUICKEN   = 2,
	SI_CONCENTRATE      = 3,
	SI_HIDING           = 4,
	SI_CLOAKING         = 5,
	SI_ENCPOISON        = 6,
	SI_POISONREACT      = 7,
	SI_QUAGMIRE         = 8,
	SI_ANGELUS          = 9,
	SI_BLESSING         = 10,
	SI_SIGNUMCRUCIS     = 11,
	SI_INCREASEAGI      = 12,
	SI_DECREASEAGI      = 13,
	SI_SLOWPOISON       = 14,
	SI_IMPOSITIO        = 15,
	SI_SUFFRAGIUM       = 16,
	SI_ASPERSIO         = 17,
	SI_BENEDICTIO       = 18,
	SI_KYRIE            = 19,
	SI_MAGNIFICAT       = 20,
	SI_GLORIA           = 21,
	SI_AETERNA          = 22,
	SI_ADRENALINE       = 23,
	SI_WEAPONPERFECTION = 24,
	SI_OVERTHRUST       = 25,
	SI_MAXIMIZEPOWER    = 26,
	SI_RIDING           = 27,
	SI_FALCON           = 28,
	SI_TRICKDEAD        = 29,
	SI_LOUD             = 30,
	SI_ENERGYCOAT       = 31,
	SI_BREAKARMOR       = 32,
	SI_BREAKWEAPON      = 33,
	SI_HALLUCINATION    = 34,
	SI_WEIGHT50         = 35,
	SI_WEIGHT90         = 36,
	SI_SPEEDPOTION0     = 37,
	SI_SPEEDPOTION1     = 38,
	SI_SPEEDPOTION2     = 39,
	SI_SPEEDPOTION3     = 40,
	SI_INCREASEAGI2     = 41,
	SI_INCREASEAGI3     = 42,
	SI_STRIPWEAPON      = 50,
	SI_STRIPSHIELD      = 51,
	SI_STRIPARMOR       = 52,
	SI_STRIPHELM        = 53,
	SI_CP_WEAPON        = 54,
	SI_CP_SHIELD        = 55,
	SI_CP_ARMOR         = 56,
	SI_CP_HELM          = 57,
	SI_AUTOGUARD        = 58,
	SI_REFLECTSHIELD    = 59,
	SI_DEVOTION         = 60,
	SI_PROVIDENCE       = 61,
	SI_DEFENDER         = 62,
	SI_AUTOSPELL        = 65,
	SI_SPEARSQUICKEN    = 68,
	SI_EXPLOSIONSPIRITS = 86,
	SI_STEELBODY        = 87,
	SI_COMBO            = 89,
	SI_FLAMELAUNCHER    = 90,
	SI_FROSTWEAPON      = 91,
	SI_LIGHTNINGLOADER  = 92,
	SI_SEISMICWEAPON    = 93,
	SI_HOLDWEB          = 95,
	SI_UNDEAD           = 97,
	SI_AURABLADE        = 103,
	SI_PARRYING         = 104,
	SI_CONCENTRATION    = 105,
	SI_TENSIONRELAX     = 106,
	SI_BERSERK          = 107,
	SI_ASSUMPTIO        = 110,
	SI_ELEMENTFIELD     = 112,
	SI_MAGICPOWER       = 113,
	SI_EDP              = 114,
	SI_TRUESIGHT        = 115,
	SI_WINDWALK         = 116,
	SI_MELTDOWN         = 117,
	SI_CARTBOOST        = 118,
	SI_CHASEWALK        = 119,
	SI_REJECTSWORD      = 120,
	SI_MARIONETTE       = 121,
	SI_MARIONETTE2      = 122,
	SI_MOONLIT          = 123,
	SI_HEADCRUSH        = 124,
	SI_JOINTBEAT        = 125,
	SI_BABY             = 130,
	SI_MAGNUM           = 131,
	SI_AUTOBERSERK      = 132,
	SI_RUN              = 133,
	SI_RUN_STOP         = 134,
	SI_READYSTORM       = 135,
	SI_READYDOWN        = 137,
	SI_READYTURN        = 139,
	SI_READYCOUNTER     = 141,
	SI_DODGE            = 143,
	SI_SPURT            = 145,
	SI_DARKELEMENT      = 146,
	SI_ADRENALINE2      = 147,
	SI_ATTENELEMENT     = 148,
	SI_SOULLINK         = 149,
	SI_DEVIL            = 152,
	SI_KAITE            = 153,
	SI_KAIZEL           = 156,
	SI_KAAHI            = 157,
	SI_KAUPE            = 158,
	SI_SMA              = 159,
	SI_MIRACLE          = 160,
	SI_ONEHAND          = 161,
	SI_WARM             = 165,
	//SI_WARM           = 166,
	//SI_WARM           = 167,
	SI_SUN_COMFORT      = 169,
	SI_MOON_COMFORT     = 170,
	SI_STAR_COMFORT     = 171,
	SI_PRESERVE         = 181,
	SI_CHASEWALK_STR    = 182,
	SI_TIGEREYE         = 184,
	SI_DOUBLECASTING    = 186,
	SI_OVERTHRUSTMAX    = 188,
	SI_TAROTCARD        = 191,
	SI_SHRINK           = 197,
	SI_SIGHTBLASTER     = 198,
	SI_CLOSECONFINE     = 200,
	SI_CLOSECONFINE2    = 201,
	SI_MADNESSCANCEL    = 203,
	SI_GATLINGFEVER     = 204,
	SI_UTSUSEMI         = 206,
	SI_BUNSINJYUTSU     = 207,
	SI_NEN              = 208,
	SI_ADJUSTMENT       = 209,
	SI_INCREASING       = 210,
	SI_MEAL_INCSTR      = 241,
	SI_MEAL_INCAGI      = 242,
	SI_MEAL_INCVIT      = 243,
	SI_MEAL_INCDEX      = 244,
	SI_MEAL_INCINT      = 245,
	SI_MEAL_INCLUK      = 246,
	SI_MEAL_INCFLEE     = 247,
	SI_MEAL_INCHIT      = 248,
	SI_MEAL_INCCRITICAL = 249,
	SI_COMBATHAN        = 250,
	SI_LIFEINSURANCE    = 251,
	SI_ITEMDROPRATE     = 252,
	SI_BOSSMAPINFO      = 253,
	//260：全てのMobがドラキュラに見える
	//263：死んだふりと同じアイコンだが倒れない
	//264：一瞬画面が霞んでグロリアアイコンが付く
	SI_MEAL_INCSTR2     = 271,
	SI_MEAL_INCAGI2     = 272,
	SI_MEAL_INCVIT2     = 273,
	SI_MEAL_INCDEX2     = 274,
	SI_MEAL_INCINT2     = 275,
	SI_MEAL_INCLUK2     = 276,
	//
	SI_SLOWCAST         = 282,
	//
	SI_CRITICALWOUND    = 286,
	//289：??
};

#endif
