#ifndef _STATUS_H_
#define _STATUS_H_

// ステータス異常データベース
struct scdata_db {
	short save;
	int releasable;
	int disable;
};

// パラメータ所得系 battle.c より移動
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
int status_get_attack_element2(struct block_list *bl);  //左手武器属性取得
//int status_get_sevenwind_element(struct block_list *bl);
//int status_get_sevenwind_element2(struct block_list *bl);  //左手武器属性取得
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
int status_change_end( struct block_list* bl , int type,int tid );
int status_change_pretimer(struct block_list *bl,int type,int val1,int val2,int val3,int val4,int tick,int flag,int pre_tick);
int status_change_timer(int tid, unsigned int tick, int id, int data);
int status_change_timer_sub(struct block_list *bl, va_list ap );
int status_change_race_end(struct block_list *bl,int type);
int status_change_soulstart(struct block_list *bl,int val1,int val2,int val3,int val4,int tick,int flag);
int status_change_soulclear(struct block_list *bl);
int status_change_resistclear(struct block_list *bl);
int status_enchant_armor_eremental_end(struct block_list *bl,int type);
int status_encchant_eremental_end(struct block_list *bl,int type);
int status_change_clear(struct block_list *bl,int type);
int status_change_release(struct block_list *bl,int mask);
int status_clearpretimer(struct block_list *bl);
int status_change_attacked_end(struct block_list *bl);
int status_change_hidden_end(struct block_list *bl);

//状態チェック
int status_check_no_magic_damage(struct block_list *bl);
#ifdef DYNAMIC_SC_DATA
int status_calloc_sc_data(struct block_list *bl);
int status_free_sc_data(struct block_list *bl);
int status_check_dummy_sc_data(struct block_list *bl);
#endif
// ステータス計算
int status_calc_pc_stop_begin(struct block_list *bl);
int status_calc_pc_stop_end(struct block_list *bl);
int status_calc_pc(struct map_session_data* sd,int first);
int status_calc_skilltree(struct map_session_data *sd);
int status_get_overrefine_bonus(int lv);
int status_percentrefinery(struct map_session_data *sd,struct item *item);
int status_percentrefinery_weaponrefine(struct map_session_data *sd,struct item *item);
extern int current_equip_item_index;
extern int current_equip_card_id;

extern struct status_change dummy_sc_data[MAX_STATUSCHANGE];

//DB再読込用
int status_readdb(void);

int do_init_status(void);

enum {	// struct map_session_data の status_changeの番号テーブル
// SC_SENDMAX未満はクライアントへの通知あり。
// 2-2次職の値はなんかめちゃくちゃっぽいので暫定。たぶん変更されます。
	//SC_SENDMAX				=128,

	SC_PROVOKE				= 0,	/* プロボック */
	SC_ENDURE				= 1,	/* インデュア */
	SC_TWOHANDQUICKEN		= 2,	/* ツーハンドクイッケン */
	SC_CONCENTRATE			= 3,	/* 集中力向上 */
	SC_HIDING				= 4,	/* ハイディング */
	SC_CLOAKING				= 5,	/* クローキング */
	SC_ENCPOISON			= 6,	/* エンチャントポイズン */
	SC_POISONREACT			= 7,	/* ポイズンリアクト */
	SC_QUAGMIRE				= 8,	/* クァグマイア */
	SC_ANGELUS				= 9,	/* エンジェラス */
	SC_BLESSING				=10,	/* ブレッシング */
	SC_SIGNUMCRUCIS			=11,	/* シグナムクルシス？ */
	SC_INCREASEAGI			=12,	/*  */
	SC_DECREASEAGI			=13,	/*  */
	SC_SLOWPOISON			=14,	/* スローポイズン */
	SC_IMPOSITIO			=15,	/* イムポシティオマヌス */
	SC_SUFFRAGIUM			=16,	/* サフラギウム */
	SC_ASPERSIO				=17,	/* アスペルシオ */
	SC_BENEDICTIO			=18,	/* 聖体降臨 */
	SC_KYRIE				=19,	/* キリエエレイソン */
	SC_MAGNIFICAT			=20,	/* マグニフィカート */
	SC_GLORIA				=21,	/* グロリア */
	SC_AETERNA				=22,	/*  */
	SC_ADRENALINE			=23,	/* アドレナリンラッシュ */
	SC_WEAPONPERFECTION		=24,	/* ウェポンパーフェクション */
	SC_OVERTHRUST			=25,	/* オーバートラスト */
	SC_MAXIMIZEPOWER		=26,	/* マキシマイズパワー */
	SC_RIDING				=27,	/* ライディング */
	SC_FALCON				=28,	/* ファルコンマスタリー */
	SC_TRICKDEAD			=29,	/* 死んだふり */
	SC_LOUD					=30,	/* ラウドボイス */
	SC_ENERGYCOAT			=31,	/* エナジーコート */
	SC_PK_PENALTY			=32,	//PKのペナルティ
	SC_REVERSEORCISH		=33,    //リバースオーキッシュ
	SC_HALLUCINATION		=34,	/* 幻覚 */
	SC_WEIGHT50				=35,	/* 重量50％オーバー */
	SC_WEIGHT90				=36,	/* 重量90％オーバー */
	SC_SPEEDPOTION0			=37,	/* 速度ポーション？ */
	SC_SPEEDPOTION1			=38,	/* スピードアップポーション？ */
	SC_SPEEDPOTION2			=39,	/* ハイスピードポーション？ */
	SC_SPEEDPOTION3			=40,	/* バーサークポーション */
	SC_ITEM_DELAY			=41,
	//
	//
	//
	//
	//
	//
	//
	//
	SC_STRIPWEAPON			=50,	/* ストリップウェポン */
	SC_STRIPSHIELD			=51,	/* ストリップシールド */
	SC_STRIPARMOR			=52,	/* ストリップアーマー */
	SC_STRIPHELM			=53,	/* ストリップヘルム */
	SC_CP_WEAPON			=54,	/* ケミカルウェポンチャージ */
	SC_CP_SHIELD			=55,	/* ケミカルシールドチャージ */
	SC_CP_ARMOR				=56,	/* ケミカルアーマーチャージ */
	SC_CP_HELM				=57,	/* ケミカルヘルムチャージ */
	SC_AUTOGUARD			=58,	/* オートガード */
	SC_REFLECTSHIELD		=59,	/* リフレクトシールド */
	SC_DEVOTION				=60,	/* ディボーション */
	SC_PROVIDENCE			=61,	/* プロヴィデンス */
	SC_DEFENDER				=62,	/* ディフェンダー */
	SC_SANTA				=63,	//サンタ
	//
	SC_AUTOSPELL			=65,	/* オートスペル */
	//
	//
	SC_SPEARSQUICKEN		=68,	/* スピアクイッケン */
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
	SC_EXPLOSIONSPIRITS		=86,	/* 爆裂波動 */
	SC_STEELBODY			=87,	/* 金剛 */
	//
	SC_COMBO				=89,
	SC_FLAMELAUNCHER		=90,	/* フレイムランチャー */
	SC_FROSTWEAPON			=91,	/* フロストウェポン */
	SC_LIGHTNINGLOADER		=92,	/* ライトニングローダー */
	SC_SEISMICWEAPON		=93,	/* サイズミックウェポン */
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
	SC_AURABLADE			=103,	/* オーラブレード */
	SC_PARRYING				=104,	/* パリイング */
	SC_CONCENTRATION		=105,	/* コンセントレーション */
	SC_TENSIONRELAX			=106,	/* テンションリラックス */
	SC_BERSERK				=107,	/* バーサーク */
	//
	//
	//
	SC_ASSUMPTIO			=110,	/* アスムプティオ */
	//
	//
	SC_MAGICPOWER			=113,	/* 魔法力増幅 */
	SC_EDP					=114,	/* エフェクトが判明したら移動 */
	SC_TRUESIGHT			=115,	/* トゥルーサイト */
	SC_WINDWALK				=116,	/* ウインドウォーク */
	SC_MELTDOWN				=117,	/* メルトダウン */
	SC_CARTBOOST			=118,	/* カートブースト */
	SC_CHASEWALK			=119,	/* チェイスウォーク */
	SC_REJECTSWORD			=120,	/* リジェクトソード */
	SC_MARIONETTE			=121,	/* マリオネットコントロール */ //自分用
	SC_MARIONETTE2			=122,	/* マリオネットコントロール */ //ターゲット用
	//
	SC_HEADCRUSH			=124,	/* ヘッドクラッシュ */
	SC_JOINTBEAT			=125,	/* ジョイントビート */
	//
	//
	SC_STONE				=128,	/* 状態異常：石化 */
	SC_FREEZE				=129,	/* 状態異常：氷結 */
	SC_STAN					=130,	/* 状態異常：スタン */
	SC_SLEEP				=131,	/* 状態異常：睡眠 */
	SC_POISON				=132,	/* 状態異常：毒 */
	SC_CURSE				=133,	/* 状態異常：呪い */
	SC_SILENCE				=134,	/* 状態異常：沈黙 */
	SC_CONFUSION			=135,	/* 状態異常：混乱 */
	SC_BLIND				=136,	/* 状態異常：暗闇 */
	SC_BLEED				=137,	/* 状態異常：出血 */
	//138
	//139
	SC_SAFETYWALL			=140,	/* セーフティーウォール */
	SC_PNEUMA				=141,	/* ニューマ */
	//
	SC_ANKLE				=143,	/* アンクルスネア */
	SC_DANCING				=144,	/*  */
	SC_KEEPING				=145,	/*  */
	SC_BARRIER				=146,	/*  */
	SC_TIGERFIST			=147,	/* 伏虎拳 */
	//
	SC_MAGICROD				=149,	/*  */
	SC_SIGHT				=150,	/*  */
	SC_RUWACH				=151,	/*  */
	SC_AUTOCOUNTER			=152,	/*  */
	SC_VOLCANO				=153,	/*  */
	SC_DELUGE				=154,	/*  */
	SC_VIOLENTGALE			=155,	/*  */
	SC_BLADESTOP_WAIT		=156,	/*  */
	SC_BLADESTOP			=157,	/*  */
	SC_EXTREMITYFIST		=158,	/*  */
	SC_GRAFFITI				=159,	/*  */
	SC_LULLABY				=160,	/*  */
	SC_RICHMANKIM			=161,	/*  */
	SC_ETERNALCHAOS			=162,	/*  */
	SC_DRUMBATTLE			=163,	/*  */
	SC_NIBELUNGEN			=164,	/*  */
	SC_ROKISWEIL			=165,	/*  */
	SC_INTOABYSS			=166,	/*  */
	SC_SIEGFRIED			=167,	/*  */
	SC_DISSONANCE			=168,	/*  */
	SC_WHISTLE				=169,	/*  */
	SC_ASSNCROS				=170,	/*  */
	SC_POEMBRAGI			=171,	/*  */
	SC_APPLEIDUN			=172,	/*  */
	SC_UGLYDANCE			=173,	/*  */
	SC_HUMMING				=174,	/*  */
	SC_DONTFORGETME			=175,	/*  */
	SC_FORTUNE				=176,	/*  */
	SC_SERVICE4U			=177,	/*  */
	SC_BASILICA				=178,	/*  */
	SC_MINDBREAKER			=179,	/*  */
	SC_SPIDERWEB			=180,	/* スパイダーウェッブ */
	SC_MEMORIZE				=181,	/* メモライズ */
	SC_DPOISON				=182,	/* 猛毒 */
	//
	SC_SACRIFICE			=184,	/* サクリファイス */
	SC_INCATK				=185,	//item 682用
	SC_INCMATK				=186,	//item 683用
	SC_WEDDING				=187,	//結婚用(結婚衣裳になって歩くのが遅いとか)
	SC_NOCHAT				=188,	//赤エモ状態
	SC_SPLASHER				=189,	/* ベナムスプラッシャー */
	SC_SELFDESTRUCTION		=190,	/* 自爆 */
	SC_MAGNUM				=191,	/* マグナムブレイク */
	SC_GOSPEL				=192,	/* ゴスペル */
	SC_INCALLSTATUS			=193,	/* 全てのステータスを上昇(今のところゴスペル用) */
	SC_INCHIT				=194,	/* HIT上昇(今のところゴスペル用) */
	SC_INCFLEE				=195,	/* FLEE上昇(今のところゴスペル用) */
	SC_INCMHP2				=196,	/* MHPを%上昇(今のところゴスペル用) */
	SC_INCMSP2				=197,	/* MSPを%上昇(今のところゴスペル用) */
	SC_INCATK2				=198,	/* ATKを%上昇(今のところゴスペル用) */
	SC_INCHIT2				=199,	/* HITを%上昇(今のところゴスペル用) */
	SC_INCFLEE2				=200,	/* FLEEを%上昇(今のところゴスペル用) */
	SC_PRESERVE				=201,	/* プリザーブ */
	SC_OVERTHRUSTMAX		=202,	/* オーバートラストマックス */
	SC_CHASEWALK_STR		=203,	/*STR上昇（チェイスウォーク用）*/
	SC_WHISTLE_				=204,
	SC_ASSNCROS_			=205,
	SC_POEMBRAGI_			=206,
	SC_APPLEIDUN_			=207,
	SC_HUMMING_				=209,
	SC_DONTFORGETME_		=210,
	SC_FORTUNE_				=211,
	SC_SERVICE4U_			=212,
	SC_BATTLEORDER			=213,//ギルドスキル
	SC_REGENERATION			=214,
	SC_BATTLEORDER_DELAY	=215,
	SC_REGENERATION_DELAY	=216,
	SC_RESTORE_DELAY		=217,
	SC_EMERGENCYCALL_DELAY	=218,
	SC_POISONPOTION			=219,
	SC_THE_MAGICIAN			=220,
	SC_STRENGTH				=221,
	SC_THE_DEVIL			=222,
	SC_THE_SUN				=223,
	SC_MEAL_INCSTR			=224,//食事用
	SC_MEAL_INCAGI			=225,
	SC_MEAL_INCVIT			=226,
	SC_MEAL_INCINT			=227,
	SC_MEAL_INCDEX			=228,
	SC_MEAL_INCLUK			=229,
	SC_RUN 					= 230,
	SC_SPURT 				= 231,
	SC_TKCOMBO 				= 232,	//テコンのコンボ用
	SC_DODGE				= 233,
	SC_HERMODE				= 234,
	SC_TRIPLEATTACK_RATE_UP	= 235,	//三段発動率アップ
	SC_COUNTER_RATE_UP		= 236,	//カウンターキック発動率アップ
	SC_SUN_WARM				= 237,
	SC_MOON_WARM			= 238,
	SC_STAR_WARM			= 239,
	SC_SUN_COMFORT			= 240,
	SC_MOON_COMFORT			= 241,
	SC_STAR_COMFORT			= 242,
	SC_FUSION				= 243,
	SC_ALCHEMIST			= 244,//魂
	SC_MONK					= 245,
	SC_STAR					= 246,
	SC_SAGE					= 247,
	SC_CRUSADER				= 248,
	SC_SUPERNOVICE			= 249,
	SC_KNIGHT				= 250,
	SC_WIZARD				= 251,
	SC_PRIEST				= 252,
	SC_BARDDANCER			= 253,
	SC_ROGUE				= 254,
	SC_ASSASIN				= 255,
	SC_BLACKSMITH			= 256,
	SC_HUNTER				= 257,
	SC_SOULLINKER			= 258,
	SC_HIGH					= 259,
	SC_DEATHKINGHT			= 260,
	SC_COLLECTOR			= 261,
	SC_NINJA				= 262,
	SC_GUNNER				= 263,
	SC_KAIZEL				= 264,
	SC_KAAHI				= 265,
	SC_KAUPE				= 266,
	SC_KAITE				= 267,
	SC_SMA					= 268,	//エスマ詠唱可能時間用
	SC_SWOO					= 269,
	SC_SKE					= 270,
	SC_SKA					= 271,
	SC_ONEHAND				= 272,
	SC_READYSTORM			= 273,
	SC_READYDOWN			= 274,
	SC_READYTURN			= 275,
	SC_READYCOUNTER			= 276,
	SC_DODGE_DELAY			= 277,
	SC_AUTOBERSERK			= 278,
	SC_DEVIL				= 279,
	SC_DOUBLECASTING 		= 280,//ダブルキャスティング
	SC_ELEMENTFIELD			= 281,//属性場
	SC_DARKELEMENT			= 282,//闇
	SC_ATTENELEMENT			= 283,//念
	SC_MIRACLE				= 284,//太陽と月と星の奇跡
	SC_ANGEL				= 285,//太陽と月と星の天使
	SC_FORCEWALKING				= 286,//SC_HIGHJUMPを強制移動状態として再利用
	SC_DOUBLE				= 287,//ダブルストレイフィング状態
	SC_ACTION_DELAY			= 288,//
	SC_BABY					= 289,//パパ、ママ、大好き
	SC_LONGINGFREEDOM		= 290,
	SC_SHRINK				= 291,//#シュリンク#
	SC_CLOSECONFINE			= 292,//#クローズコンファイン#
	SC_SIGHTBLASTER			= 293,//#サイトブラスター#
	SC_ELEMENTWATER			= 294,//#エルレメンタルチェンジ水#
	//食事用2
	SC_MEAL_INCHIT			= 295,
	SC_MEAL_INCFLEE			= 296,
	SC_MEAL_INCFLEE2		= 297,
	SC_MEAL_INCCRITICAL		= 298,
	SC_MEAL_INCDEF			= 299,
	SC_MEAL_INCMDEF			= 300,
	SC_MEAL_INCATK			= 301,
	SC_MEAL_INCMATK			= 302,
	SC_MEAL_INCEXP			= 303,
	SC_MEAL_INCJOB			= 304,
	//
	SC_ELEMENTGROUND		= 305,//土(鎧)
	SC_ELEMENTFIRE			= 306,//火(鎧)
	SC_ELEMENTWIND			= 307,//風(鎧)
	SC_WINKCHARM			= 308,
	SC_ELEMENTPOISON		= 309,//毒(鎧)
	SC_ELEMENTDARK			= 310,//闇(鎧)
	SC_ELEMENTELEKINESIS	= 311,//念(鎧)
	SC_ELEMENTUNDEAD		= 312,//不死(鎧)
	SC_UNDEADELEMENT		= 313,//不死(武)
	SC_ELEMENTHOLY			= 314,//聖(鎧)
	SC_NPC_DEFENDER			= 315,
	SC_RESISTWATER			= 316,//耐性
	SC_RESISTGROUND			= 317,//耐性
	SC_RESISTFIRE			= 318,//耐性
	SC_RESISTWIND			= 319,//耐性
	SC_RESISTPOISON			= 320,//耐性
	SC_RESISTHOLY			= 321,//耐性
	SC_RESISTDARK			= 322,//耐性
	SC_RESISTTELEKINESIS	= 323,//耐性
	SC_RESISTUNDEAD			= 324,//耐性
	SC_RESISTALL			= 325,//耐性
	//種族変更？
	SC_RACEUNKNOWN			= 326,//無形
	SC_RACEUNDEAD			= 327,//不死種族
	SC_RACEBEAST			= 328,
	SC_RACEPLANT			= 329,
	SC_RACEINSECT			= 330,
	SC_RACEFISH				= 332,
	SC_RACEDEVIL			= 333,
	SC_RACEHUMAN			= 334,
	SC_RACEANGEL			= 335,
	SC_RACEDRAGON			= 336,
	SC_TIGEREYE				= 337,
	SC_GRAVITATION_USER		= 338,
	SC_GRAVITATION			= 339,
	SC_FOGWALL				= 340,
	SC_FOGWALLPENALTY		= 341,
	SC_REDEMPTIO			= 342,
	SC_TAROTCARD			= 343,
	SC_HOLDWEB				= 344,
	SC_INVISIBLE			= 345,
	SC_DETECTING			= 346,
	//
	SC_FLING				= 347,
	SC_MADNESSCANCEL		= 348,
	SC_ADJUSTMENT			= 349,
	SC_INCREASING			= 350,
	SC_DISARM				= 351,
	SC_GATLINGFEVER			= 352,
	SC_FULLBUSTER			= 353,
	//ニンジャスキル
	SC_TATAMIGAESHI			= 354,
	SC_UTSUSEMI				= 355,//#NJ_UTSUSEMI#
	SC_BUNSINJYUTSU			= 356,//#NJ_BUNSINJYUTSU#
	SC_SUITON				= 357,//#NJ_SUITON#
	SC_NEN					= 358,//#NJ_NEN#
	SC_AVOID				= 359,//#緊急回避#
	SC_CHANGE				= 360,//#メンタルチェンジ#
	SC_DEFENCE				= 361,//#ディフェンス#
	SC_BLOODLUST			= 362,//#ブラッドラスト#
	SC_FLEET				= 363,//#フリートムーブ#
	SC_SPEED				= 364,//#オーバードスピード#
	//
	SC_ADRENALINE2			= 365,
	SC_STATUS_UNCHANGE		= 366,/* 状態異常耐性（ゴスペル用）*/
	SC_INCDAMAGE			= 367,/* 被ダメージが%上昇（ゴスペル用）*/

	//startでは使えないresistをアイテム側で全てクリアするための物
	SC_RESISTCLEAR			= 1001,
	SC_RACECLEAR			= 1002,
	SC_SOUL					= 1003,
	SC_SOULCLEAR			= 1004,
};

//状態アイコン
//厳密にはキャラクターの色の変化なども含まれている(爆裂波動など)
enum {
	SI_BLANK				= 43,//送っても空白のもの

	SI_PROVOKE				= 0,
	SI_ENDURE				= 1,
	SI_TWOHANDQUICKEN		= 2,
	SI_CONCENTRATE			= 3,
	SI_HIDING				= 4,
	SI_CLOAKING				= 5,
	SI_ENCPOISON			= 6,
	SI_POISONREACT			= 7,
	SI_QUAGMIRE				= 8,
	SI_ANGELUS				= 9,
	SI_BLESSING				=10,
	SI_SIGNUMCRUCIS			=11,
	SI_INCREASEAGI			=12,
	SI_DECREASEAGI			=13,
	SI_SLOWPOISON			=14,
	SI_IMPOSITIO			=15,
	SI_SUFFRAGIUM			=16,
	SI_ASPERSIO				=17,
	SI_BENEDICTIO			=18,
	SI_KYRIE				=19,
	SI_MAGNIFICAT			=20,
	SI_GLORIA				=21,
	SI_AETERNA				=22,
	SI_ADRENALINE			=23,
	SI_WEAPONPERFECTION		=24,
	SI_OVERTHRUST			=25,
	SI_MAXIMIZEPOWER		=26,
	SI_RIDING				=27,
	SI_FALCON				=28,
	SI_TRICKDEAD			=29,
	SI_LOUD					=30,
	SI_ENERGYCOAT			=31,
	SI_BREAKARMOR			=32,	// 防具破壊
	SI_BREAKWEAPON			=33,	// 武器破壊
	SI_HALLUCINATION		=34,
	SI_WEIGHT50				=35,
	SI_WEIGHT90				=36,
	SI_SPEEDPOTION0			=37,	// スピードアップポーション
	SI_SPEEDPOTION1			=38,	// ハイスピードポーション
	SI_SPEEDPOTION2			=39,	// バーサクポーション
	SI_SPEEDPOTION3			=40,	// サーバークピッチャー？
	SI_INCREASEAGI2			=41,	// 馬牌？
	SI_INCREASEAGI3			=42,	// 移動速度増加ポーション？
	SI_STRIPWEAPON			=50,
	SI_STRIPSHIELD			=51,
	SI_STRIPARMOR			=52,
	SI_STRIPHELM			=53,
	SI_CP_WEAPON			=54,
	SI_CP_SHIELD			=55,
	SI_CP_ARMOR				=56,
	SI_CP_HELM				=57,
	SI_AUTOGUARD			=58,
	SI_REFLECTSHIELD		=59,
	SI_DEVOTION				=60,
	SI_PROVIDENCE			=61,
	SI_DEFENDER				=62,
	SI_AUTOSPELL			=65,
	SI_SPEARSQUICKEN		=68,
	SI_EXPLOSIONSPIRITS		=86,	/* 爆裂波動 */
	SI_STEELBODY			=87,	/* 金剛エフェクト */
	SI_COMBO				=89,
	SI_FLAMELAUNCHER		=90,	/* フレイムランチャー */
	SI_FROSTWEAPON			=91,	/* フロストウェポン */
	SI_LIGHTNINGLOADER		=92,	/* ライトニングローダー */
	SI_SEISMICWEAPON		=93,	/* サイズミックウェポン */
	SI_HOLDWEB			=95,	/* ホールドウェブ */
	SI_AURABLADE			=103,	/* オーラブレード */
	SI_PARRYING				=104,	/* パリイング */
	SI_CONCENTRATION		=105,	/* コンセントレーション */
	SI_TENSIONRELAX			=106,	/* テンションリラックス */
	SI_BERSERK				=107,	/* バーサーク */
	SI_ASSUMPTIO			=110,	/* アスムプティオ */
	SI_ELEMENTFIELD 		=112,	/* 属性場 */
	SI_MAGICPOWER			=113,	/* 魔法力増幅 */
	SI_EDP					=114, 	//
	SI_TRUESIGHT			=115,	/* トゥルーサイト */
	SI_WINDWALK				=116,	/* ウインドウォーク */
	SI_MELTDOWN				=117,	/* メルトダウン */
	SI_CARTBOOST			=118,	/* カートブースト */
	SI_CHASEWALK			=119,	/* チェイスウォーク */
	SI_REJECTSWORD			=120,	/* リジェクトソード */
	SI_MARIONETTE			=121,	/* マリオネットコントロール */
	SI_MARIONETTE2			=122,	/* マリオネットコントロール2 */
	SI_MOONLIT 				=123,	//月明かりの下で
	SI_HEADCRUSH			=124,	/* ヘッドクラッシュ */
	SI_JOINTBEAT			=125,	/* ジョイントビート */
	SI_BABY					=130,	//パパ、ママ、大好き
	SI_MAGNUM			=131,	//マグナムブレイク
	SI_AUTOBERSERK			=132,	//オートバーサーク
	SI_RUN				=133,	//タイリギ
	SI_RUN_STOP			=134,	//タイリギ衝突
	SI_READYSTORM			=135,	//旋風準備
	SI_READYDOWN			=137,	//下段準備
	SI_READYTURN			=139,	//回転準備
	SI_READYCOUNTER			=141,	//カウンター準備
	SI_DODGE				=143,	//落法
	SI_SPURT				=145,	//駆け足スパート
	SI_DARKELEMENT			=146,	//暗
	SI_ADRENALINE2			=147,	//フルアドレナリンラッシュ
	SI_ATTENELEMENT			=148,	//念
	SI_SOULLINK				=149,	//魂状態
	SI_DEVIL				=152,	//太陽と月と星の悪魔
	SI_KAITE				=153,	//カイト
	SI_KAIZEL				=156,	//カイゼル
	SI_KAAHI				=157,	//カアヒ
	SI_KAUPE				=158,	//カウプ
	SI_SMA					=159,	//エスマ可能状態
	//160 SI_SOULLINKと同じ？
	SI_ONEHAND				=161,	//ワンハンドクイッケン
	SI_SUN_WARM				=165,	//太陽の温もり
	SI_MOON_WARM			=166,	//月の温もり
	SI_STAR_WARM			=167,	//星の温もり
	SI_SUN_COMFORT			=169,	//太陽の安楽
	SI_MOON_COMFORT			=170,	//月の安楽
	SI_STAR_COMFORT			=171,	//星の安楽
	SI_PRESERVE				=181,	//プリザーブ
	SI_CHASEWALK_STR		=182,	//チェイスウォークのSTR?
	SI_TIGEREYE			=184,	//タイガーアイ（ハイド見破り）
	SI_DOUBLECASTING		=186,	//ダブルキャスティング
	SI_OVERTHRUSTMAX		=188,	//オーバートラストマックス
	SI_TAROTCARD			=191,
	SI_SHRINK				=197,	//#シュリンク#
	SI_SIGHTBLASTER			=198,	//#サイトブラスター#
	SI_CLOSECONFINE			=200,	//#クローズコンファイン#
	SI_CLOSECONFINE2		=201,	//#クローズコンファイン#
	SI_MADNESSCANCEL		=203,	//#GS_MADNESSCANCEL#
	SI_GATLINGFEVER			=204,	//#GS_GATLINGFEVER#
	SI_UTSUSEMI				=206,	//#NJ_UTSUSEMI#
	SI_BUNSINJYUTSU			=207,	//#NJ_BUNSINJYUTSU#
	SI_NEN					=208,	//#NJ_NEN#
	SI_ADJUSTMENT			=209,	//#GS_ADJUSTMENT#
	SI_INCREASING			=210,	//#GS_INCREASING#
};

#endif
