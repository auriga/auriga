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

#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>

#include "db.h"
#include "malloc.h"
#include "nullpo.h"
#include "timer.h"
#include "utils.h"

#include "pc.h"
#include "map.h"
#include "path.h"
#include "pet.h"
#include "homun.h"
#include "mob.h"
#include "clif.h"
#include "skill.h"
#include "itemdb.h"
#include "battle.h"
#include "status.h"
#include "status_internal.h"
#include "script.h"
#include "guild.h"
#include "unit.h"
#include "ranking.h"
#include "merc.h"
#include "elem.h"
#include "msg.h"
#include "bonus.h"
#include "date.h"

/* Split from status.c (Issue #57 PR3) */

/*==========================================
 * ステータス異常終了
 *------------------------------------------
 */
int status_change_end(struct block_list* bl, int type, int tid)
{
	struct map_session_data *sd  = NULL;
	struct mob_data         *md  = NULL;
	struct homun_data       *hd  = NULL;
	struct merc_data        *mcd = NULL;
	struct elem_data        *eld = NULL;
	struct status_change    *sc  = NULL;
	struct unit_data        *ud  = NULL;
	int opt_flag = 0, calc_flag = 0;

	nullpo_retr(0, bl);
	nullpo_retr(0, sc = status_get_sc(bl));

	if(type < 0)
		return 0;
	ud = unit_bl2ud(bl);
	if(ud == NULL)
		return 0;

	if(type >= MAX_STATUSCHANGE) {
		switch(type) {
			case SC_RACECLEAR:
				status_change_race_end(bl,-1);
				break;
			case SC_RESISTCLEAR:
				status_change_resistclear(bl);
				break;
			case SC_SOUL:
			case SC_SOULCLEAR:
				status_change_soulclear(bl);
				break;
			default:
				if(battle_config.error_log)
					printf("UnknownStatusChangeEnd [%d]\n", type);
				break;
		}
		return 0;
	}

	if(sc->count <= 0 || sc->data[type].timer == -1)
		return 0;

	if(tid != -1 && sc->data[type].timer != tid)
		return 0;

	if(tid == -1)	/* タイマから呼ばれていないならタイマ削除をする */
		delete_timer(sc->data[type].timer,status_change_timer);

	/* 該当の異常を正常に戻す */
	sc->data[type].timer = -1;
	sc->count--;

	sd  = BL_DOWNCAST( BL_PC,   bl );
	md  = BL_DOWNCAST( BL_MOB,  bl );
	hd  = BL_DOWNCAST( BL_HOM,  bl );
	mcd = BL_DOWNCAST( BL_MERC, bl );
	eld = BL_DOWNCAST( BL_ELEM, bl );

	if(type >= 0 && type < MAX_STATUSCHANGE && status_change_handlers[type].end) {
		struct status_change_end_ctx ectx;
		int hr;
		memset(&ectx, 0, sizeof(ectx));
		ectx.bl = bl;
		ectx.sd = sd;
		ectx.hd = hd;
		ectx.mcd = mcd;
		ectx.eld = eld;
		ectx.sc = sc;
		ectx.ud = ud;
		ectx.type = type;
		ectx.tid = tid;
		ectx.calc_flag = &calc_flag;
		ectx.opt_flag = &opt_flag;
		hr = status_change_handlers[type].end(&ectx);
		if(hr == STATUS_CHANGE_HANDLER_ABORT)
			return 0;
	} else {
		/* fallback: handler 未登録の type のみ */
		switch(type) {	/* 異常の種類ごとの処理 */
		case SC_CONCENTRATE:			/* 集中力向上 */
		case SC_ANGELUS:			/* アンゼルス */
		case SC_SIGNUMCRUCIS:			/* シグナムクルシス */
		case SC_HIDING:
		case SC_CLOAKING:
		case SC_TWOHANDQUICKEN:			/* 2HQ */
		case SC_ONEHAND:			/* 1HQ */
		case SC_ADRENALINE:			/* アドレナリンラッシュ */
		case SC_ENCPOISON:			/* エンチャントポイズン */
		case SC_GLORIA:				/* グロリア */
		case SC_LOUD:				/* ラウドボイス */
		case SC_MINDBREAKER:			/* マインドブレーカー */
		case SC_PROVIDENCE:			/* プロヴィデンス */
		case SC_SPEARQUICKEN:			/* スピアクイッケン */
		case SC_VOLCANO:
		case SC_DELUGE:
		case SC_VIOLENTGALE:
		case SC_ETERNALCHAOS:			/* エターナルカオス */
		case SC_DRUMBATTLE:			/* 戦太鼓の響き */
		case SC_NIBELUNGEN:			/* ニーベルングの指輪 */
		case SC_SIEGFRIED:			/* 不死身のジークフリード */
		case SC_EXPLOSIONSPIRITS:		/* 爆裂波動 */
		case SC_SPEEDPOTION0:			/* 増速ポーション */
		case SC_SPEEDPOTION1:
		case SC_SPEEDPOTION2:
		case SC_BLADESTOP_WAIT:
		case SC_CONCENTRATION:			/* コンセントレーション */
		case SC_TRUESIGHT:			/* トゥルーサイト */
		case SC_SPIDERWEB:			/* スパイダーウェッブ */
		case SC_CARTBOOST:			/* カートブースト */
		case SC_INCATK:				/* ATK上昇 (神酒用) */
		case SC_INCMATK:			/* MATK上昇 (神秘の草用) */
		case SC_WEDDING:			/* ウェディング */
		case SC_SANTA:
		case SC_SUMMER:
		case SC_INCALLSTATUS:
		case SC_INCHIT:
		case SC_INCMHP2:
		case SC_INCMSP2:
		case SC_INCATK2:
		case SC_INCHIT2:
		case SC_INCFLEE2:
		case SC_OVERTHRUSTMAX:
		case SC_CHASEWALK:			/* チェイスウォーク */
		case SC_CHASEWALK_STR:
		case SC_BATTLEORDER:
		case SC_MEAL_INCSTR:	// 食事用
		case SC_MEAL_INCAGI:
		case SC_MEAL_INCVIT:
		case SC_MEAL_INCINT:
		case SC_MEAL_INCDEX:
		case SC_MEAL_INCLUK:
		case SC_MEAL_INCHIT:
		case SC_MEAL_INCFLEE:
		case SC_MEAL_INCFLEE2:
		case SC_MEAL_INCCRITICAL:
		case SC_MEAL_INCDEF:
		case SC_MEAL_INCMDEF:
		case SC_MEAL_INCATK:
		case SC_MEAL_INCMATK:
		case SC_MEAL_INCSTR2:	// 課金料理用
		case SC_MEAL_INCAGI2:
		case SC_MEAL_INCVIT2:
		case SC_MEAL_INCINT2:
		case SC_MEAL_INCDEX2:
		case SC_MEAL_INCLUK2:
		case SC_SPURT:
		case SC_SUN_COMFORT:			/* 太陽の安楽 */
		case SC_MOON_COMFORT:			/* 月の安楽 */
		case SC_STAR_COMFORT:			/* 星の安楽 */
		case SC_FUSION:				/* 太陽と月と星の融合 */
		case SC_ADRENALINE2:			/* フルアドレナリンラッシュ */
		case SC_RESISTWATER:
		case SC_RESISTGROUND:
		case SC_RESISTFIRE:
		case SC_RESISTWIND:
		case SC_RESISTPOISON:
		case SC_RESISTHOLY:
		case SC_RESISTDARK:
		case SC_RESISTTELEKINESIS:
		case SC_RESISTUNDEAD:
		case SC_RESISTALL:
		case SC_INVISIBLE:
		case SC_TIGEREYE:
		case SC_THE_MAGICIAN:
		case SC_STRENGTH:
		case SC_THE_DEVIL:
		case SC_THE_SUN:
		case SC_FLING:				/* フライング */
		case SC_MADNESSCANCEL:			/* マッドネスキャンセラー */
		case SC_ADJUSTMENT:			/* アジャストメント */
		case SC_INCREASING:			/* インクリージングアキュラシー */
		case SC_NEN:				/* 念 */
		case SC_AVOID:				/* 緊急回避 */
		case SC_CHANGE:				/* メンタルチェンジ */
		case SC_DEFENCE:			/* ディフェンス */
		case SC_BLOODLUST:			/* ブラッドラスト */
		case SC_FLEET:				/* フリートムーブ */
		case SC_SPEED:				/* オーバードスピード */
		case SC_STONESKIN:			/* ストーンスキン */
		case SC_ANTIMAGIC:			/* アンチマジック */
		case SC_WEAPONQUICKEN:			/* ウェポンクイッケン */
		case SC_WE_FEMALE:			/* あなたに尽くします */
		case SC_GIANTGROWTH:		/* ジャイアントグロース */
		case SC_FIGHTINGSPIRIT:		/* ファイティングスピリット */
		case SC_FEAR:				/* 恐怖 */
		case SC_UNLIMIT:			/* アンリミット */
		case SC_EPICLESIS:			/* エピクレシス */
		case SC_LAUDAAGNUS:			/* ラウダアグヌス */
		case SC_LAUDARAMUS:			/* ラウダラムス */
		case SC_TELEKINESIS_INTENSE:	/* テレキネシスインテンス */
		case SC_VENOMIMPRESS:		/* ベナムインプレス */
		case SC_CLOAKINGEXCEED:		/* クローキングエクシード */
		case SC_VENOMBLEED:			/* ベナムブリード */
		case SC_INFRAREDSCAN:		/* インフラレッドスキャン */
		case SC_ANALYZE:			/* アナライズ */
		case SC_NEUTRALBARRIER:		/* ニュートラルバリアー */
		case SC__BODYPAINT:			/* ボディペインティング */
		case SC__INVISIBILITY:		/* インビジビリティ */
		case SC__ENERVATION:		/* マスカレード：エナベーション */
		case SC__UNLUCKY:			/* マスカレード：アンラッキー */
		case SC__STRIPACCESSARY:	/* ストリップアクセサリー */
		case SC__BLOODYLUST:		/* ブラッディラスト */
		case SC_SHIELDSPELL_DEF:	/* シールドスペル(DEF) */
		case SC_SHIELDSPELL_MDEF:	/* シールドスペル(MDEF) */
		case SC_SHIELDSPELL_REF:	/* シールドスペル(精錬) */
		case SC_PRESTIGE:			/* プレスティージ */
		case SC_EARTHDRIVE:			/* アースドライブ */
		case SC_INSPIRATION:		/* インスピレーション */
		case SC_GENTLETOUCH_CHANGE:	/* 点穴 -反- */
		case SC_GENTLETOUCH_REVITALIZE:	/* 点穴 -活- */
		case SC_SYMPHONY_LOVE:		/* 恋人たちの為のシンフォニー */
		case SC_ECHOSONG:			/* エコーの歌 */
		case SC_HARMONIZE:			/* ハーモナイズ */
		case SC_GLOOMYDAY:			/* メランコリー */
		case SC_LERADS_DEW:			/* レーラズの露 */
		case SC_DANCE_WITH_WUG:		/* ダンスウィズウォーグ */
		case SC_BEYOND_OF_WARCRY:	/* ビヨンドオブウォークライ */
		case SC_MELODYOFSINK:		/* メロディーオブシンク */
		case SC_FRIGG_SONG:			/* フリッグの歌 */
		case SC_STRIKING:			/* ストライキング */
		case SC_FIRE_EXPANSION_SMOKE_POWDER:	/* ファイアーエクスパンション(煙幕) */
		case SC_FIRE_EXPANSION_TEAR_GAS:	/* ファイアーエクスパンション(催涙ガス) */
		case SC_MANDRAGORA:			/* ハウリングオブマンドラゴラ */
		case SC_BANANA_BOMB:		/* バナナ爆弾 */
		case SC_MYSTERIOUS_POWDER:	/* 不思議な粉 */
		case SC_BOOST500:			/* ブースト500 */
		case SC_FULL_SWING_K:		/* フルスイングK */
		case SC_MANA_PLUS:			/* マナプラス */
		case SC_MUSTLE_M:			/* マッスルM */
		case SC_LIFE_FORCE_F:		/* ライフフォースF */
		case SC_PROMOTE_HEALTH_RESERCH:	/* HP増加ポーション */
		case SC_ENERGY_DRINK_RESERCH:	/* SP増加ポーション */
		case SC_EXTRACT_WHITE_POTION_Z:	/* 濃縮ホワイトポーションZ */
		case SC_VITATA_500:			/* ビタタ500 */
		case SC_EXTRACT_SALAMINE_JUICE:	/* 濃縮サラマインジュース */
		case SC_SAVAGE_STEAK:		/* サベージの丸焼き */
		case SC_COCKTAIL_WARG_BLOOD:	/* カクテルウォーグブラッド */
		case SC_MINOR_BBQ:			/* ミノタウロスの牛カルビ */
		case SC_SIROMA_ICE_TEA:		/* シロマアイスティー */
		case SC_DROCERA_HERB_STEAMED:	/* ドロセラのハーブ煮 */
		case SC_PUTTI_TAILS_NOODLES:	/* プティットのしっぽ麺 */
		case SC_STOMACHACHE:		/* 腹痛 */
		case SC_MONSTER_TRANSFORM:	/* モンスター変身 */
		case SC_MEIKYOUSISUI:		/* 明鏡止水 */
		case SC_IZAYOI:				/* 十六夜 */
		case SC_KG_KAGEHUMI:		/* 幻術 -影踏み- */
		case SC_KYOMU:				/* 幻術 -虚無の影- */
		case SC_KAGEMUSYA:			/* 幻術 -分身- */
		case SC_ZANGETSU:			/* 幻術 -残月- */
		case SC_AKAITSUKI:			/* 幻術 -紅月- */
		case SC_KYOUGAKU:			/* 幻術 -驚愕- */
		case SC_SHRIMP:				/* エビ三昧 */
		case SC_GROOMING:			/* グルーミング */
		case SC_NYANGGRASS:			/* ニャングラス */
		case SC_BURNT:				/* 獄炎呪 */
		case SC_ODINS_POWER:		/* オーディンの力 */
		case SC_MER_FLEE:			/* 傭兵ボーナス(FLEE) */
		case SC_MER_ATK:			/* 傭兵ボーナス(ATK) */
		case SC_MER_HP:				/* 傭兵ボーナス(HP) */
		case SC_MER_SP:				/* 傭兵ボーナス(SP) */
		case SC_MER_HIT:			/* 傭兵ボーナス(HIT) */
		case SC_FIRE_CLOAK:			/* ファイアークローク */
		case SC_WATER_DROP:			/* ウォータードロップ */
		case SC_WIND_CURTAIN:		/* ウィンドカーテン */
		case SC_SOLID_SKIN:			/* ソリッドスキン */
		case SC_STONE_SHIELD:		/* ストーンシールド */
		case SC_PYROTECHNIC:		/* パイロテクニック */
		case SC_HEATER:				/* ヒーター */
		case SC_TROPIC:				/* トロピック */
		case SC_AQUAPLAY:			/* アクアプレイ */
		case SC_COOLER:				/* クーラー */
		case SC_CHILLY_AIR:			/* クールエアー */
		case SC_GUST:				/* ガスト */
		case SC_BLAST:				/* ブラスト */
		case SC_WILD_STORM:			/* ワイルドストーム */
		case SC_PETROLOGY:			/* ペトロジー */
		case SC_CURSED_SOIL:		/* カースドソイル */
		case SC_UPHEAVAL:			/* アップヘイバル */
		case SC_TIDAL_WEAPON_OPTION:	/* タイダルウェポン(精霊) */
		case SC_INVINCIBLE:			/* インビンシブル */
		case SC_INVINCIBLEOFF:		/* インビンシブルオフ */
		case SC_PARALYZE:			/* 麻痺 */
		case SC_PAIN_KILLER:		/* ペインキラー */
		case SC_ANGRIFFS_MODUS:		/* アングリフスモドス */
		case SC_GOLDENE_FERSE:		/* ゴールデンペルジェ */
		case SC_TINDER_BREAKER:		/* 捕獲 */
		case SC_CBC:				/* 絞め技 */
		case SC_EQC:				/* E.Q.C */
		case SC_ALL_STAT_DOWN:	/* オールステータスダウン */
		case SC_LUNARSTANCE:		/* 月の構え */
		case SC_UNIVERSESTANCE:		/* 宇宙の構え */
		case SC_SUNSTANCE:			/* 太陽の構え */
		case SC_STARSTANCE:			/* 星の構え */
		case SC_SOULSHADOW:		/* 影の魂 */
		case SC_SOULFAIRY:		/* 妖精の魂 */
		case SC_SOULFALCON:		/* 鷹の魂 */
		case SC_SOULGOLEM:		/* ゴーレムの魂 */
		case SC_HANDICAPSTATE_DEEPBLIND:		/* 漆黒 */
		case SC_HANDICAPSTATE_DEEPSILENCE:		/* 静寂 */
		case SC_HANDICAPSTATE_FROSTBITE:		/* 急冷 */
		case SC_HANDICAPSTATE_CRYSTALLIZATION:	/* 結晶化 */
		case SC_HANDICAPSTATE_MISFORTUNE:		/* 不幸 */
		case SC_HANDICAPSTATE_DEADLYPOISON:		/* 強毒 */
		case SC_DEADLY_DEFEASANCE:		/* デッドリープロジェクション */
		case SC_CLIMAX_DES_HU:		/* クライマックスハリケーン */
		case SC_CLIMAX_CRYIMP:		/* クライマックスインパクト */
		case SC_POWERFUL_FAITH:		/* 強靭な信念 */
		case SC_FIRM_FAITH:		/* 堅固な信念 */
		case SC_SINCERE_FAITH:		/* 忠実な信念 */
		case SC_ATTACK_STANCE:		/* アタックスタンス */
		case SC_HOLY_S:		/* ホーリーシールド */
		case SC_PRE_ACIES:		/* プレセンスアキエース */
		case SC_COMPETENTIA:	/* コンペテンティア */
		case SC_RELIGIO:		/* レリギオ */
		case SC_BENEDICTUM:		/* ベネディクトゥム */
		case SC_RUSH_QUAKE2:		/* ラッシュ */
		case SC_D_MACHINE:		/* 防御装置有効化 */
		case SC_SHADOW_STRIP:	/* ストリップシャドウ */
		case SC_ABYSS_SLAYER:	/* アビススレイヤー */
		case SC_BO_HELL_DUSTY:	/* ヘルダスティ */
		case SC_MYSTIC_SYMPHONY:	/* ミスティックシンフォニー */
		case SC_GEF_NOCTURN:		/* ゲフェニアノクターン */
		case SC_AIN_RHAPSODY:		/* 鉱員のラプソディ */
		case SC_MUSICAL_INTERLUDE:	/* ミュージカルインタールード */
		case SC_SPELL_ENCHANTING:	/* スペルエンチャンティング */
		case SC_FLAMETECHNIC:		/* フレイムテクニック */
		case SC_COLD_FORCE:			/* コールドフォース */
		case SC_GRACE_BREEZE:		/* グレイスブリーズ */
		case SC_EARTH_CARE:			/* アースケア */
		case SC_DEEP_POISONING:		/* ディープポイズニング */
		case SC_FLAMEARMOR:			/* フレイムアーマー */
		case SC_CRYSTAL_ARMOR:		/* クリスタルアーマー */
		case SC_EYES_OF_STORM:		/* アイズオブストーム */
		case SC_STRONG_PROTECTION:	/* ストロングプロテクション */
		case SC_POISON_SHIELD:		/* ポイズンシールド */
		case SC_HIDDEN_CARD:		/* ヒドゥンカード */
		case SC_TALISMAN_OF_WARRIOR:	/* 武士符 */
		case SC_TALISMAN_OF_MAGICIAN:	/* 法師符 */
		case SC_TALISMAN_OF_FIVE_ELEMENTS:	/* 五行符 */
		case SC_T_FIVETH_GOD:		/* 四方五行陣 */
		case SC_HEAVEN_AND_EARTH:	/* 天地神霊 */
		case SC_MARINE_FESTIVAL:	/* マリンフェスティバル */
		case SC_SANDY_FESTIVAL:		/* サンドフェスティバル */
		case SC_TEMPORARY_COMMUNION:	/* 三霊一体 */
			calc_flag = 1;
			break;
		case SC_NEWMOON:			/* 朔月脚 */
		case SC_WALKSPEED:			/* 移動速度増加(スクリプト) */
		case SC_SLOWPOTION:			/* 移動速度低下(アイテム) */
		case SC_STEELBODY:			/* 金剛 */
		case SC_WINDWALK:			/* ウインドウォーク */
		case SC_INCFLEE:
		case SC_DECREASEAGI:			/* 速度減少 */
		case SC_QUAGMIRE:			/* クァグマイア */
		case SC_MARSHOFABYSS:		/* マーシュオブアビス */
		case SC_DEFENDER:			/* ディフェンダー */
		case SC_GRAVITATION:
		case SC_SUITON:				/* 水遁 */
		case SC_GATLINGFEVER:			/* ガトリングフィーバー */
		case SC_HALLUCINATIONWALK_POSTDELAY:	/* ハルシネーションウォーク(ペナルティ) */
		case SC_PARALIZE:			/* パラライズ */
		case SC_FROSTMISTY:			/* フロストミスティ */
		case SC_CAMOUFLAGE:			/* カモフラージュ */
		case SC__GROOMY:			/* マスカレード：グルーミー */
		case SC__LAZINESS:			/* マスカレード：レイジネス */
		case SC_SWING:				/* スイングダンス */
		case SC_GN_CARTBOOST:		/* カートブースト */
		case SC_MELON_BOMB:			/* メロン爆弾 */
		case SC_HISS:				/* 警戒 */
		case SC_ARCLOUSEDASH:		/* アクラウスダッシュ */
		case SC_CHATTERING:			/* チャタリング */
		case SC_WIND_STEP:			/* ウィンドステップ */
		case SC_REBOUND:			/* リバウンド */
		case SC_HANDICAPSTATE_LASSITUDE:		/* 無気力 */
		case SC_JAWAII_SERENADE:	/* 夕焼けのセレナーデ */
		case SC_PRON_MARCH:			/* プロンテラマーチ */
		case SC_SHIELDCHAINRUSH:	/* シールドチェーンラッシュ */
		case SC_GROUNDGRAVITY:		/* グラウンドグラビテーション */
		case SC_SHADOW_CLOCK:		/* 影隠れ */
			calc_flag = 1;
			ud->state.change_speed = 1;
			break;
		case SC_ALL_RIDING:			/* 騎乗システム */
			if(sd)
				clif_status_load_id(sd,SI_RIDING,0);
			calc_flag = 1;
			ud->state.change_speed = 1;
			break;
		case SC_ON_PUSH_CART:		/* カート */
			calc_flag = 1;
			ud->state.change_speed = 1;
			if(sc->data[SC_CARTBOOST].timer != -1)
				status_change_end(bl, SC_CARTBOOST, -1);
			if(sc->data[SC_GN_CARTBOOST].timer != -1)
				status_change_end(bl, SC_GN_CARTBOOST, -1);
			if(sd)
				clif_cart_clear(sd);
			break;
		case SC_ELEMENTWATER:		// 水
		case SC_ELEMENTGROUND:		// 土
		case SC_ELEMENTFIRE:		// 火
		case SC_ELEMENTWIND:		// 風
		case SC_ELEMENTHOLY:		// 光
		case SC_ELEMENTDARK:		// 闇
		case SC_ELEMENTELEKINESIS:	// 念
		case SC_ELEMENTPOISON:		// 毒
		//case SC_ELEMENTUNDEAD:	// 不死
			if(sd)
				clif_displaymessage(sd->fd, msg_txt(203));	// 防具の属性が元に戻りました
			break;
		case SC_RACEUNKNOWN:
		case SC_RACEUNDEAD:
		case SC_RACEBEAST:
		case SC_RACEPLANT:
		case SC_RACEINSECT:
		case SC_RACEFISH:
		case SC_RACEDEVIL:
		case SC_RACEHUMAN:
		case SC_RACEANGEL:
		case SC_RACEDRAGON:
			if(sd)
				clif_displaymessage(sd->fd, msg_txt(205));	// 種族が元に戻りました
			break;
		case SC_RUN:			/* タイリギ */
		case SC_WUGDASH:		/* ウォーグダッシュ */
			unit_stop_walking(bl,0);
			calc_flag = 1;
			break;
		case SC_MONK:			/* モンクの魂 */
		case SC_STAR:			/* ケンセイの魂 */
		case SC_SAGE:			/* セージの魂 */
		case SC_CRUSADER:		/* クルセイダーの魂 */
		case SC_WIZARD:			/* ウィザードの魂 */
		case SC_PRIEST:			/* プリーストの魂 */
		case SC_ROGUE:			/* ローグの魂 */
		case SC_ASSASIN:		/* アサシンの魂 */
		case SC_SOULLINKER:		/* ソウルリンカーの魂 */
		case SC_SUPERNOVICE:		/* スーパーノービスの魂 */
		case SC_GUNNER:			/* ガンスリンガーの魂 */
		case SC_NINJA:			/* 忍者の魂 */
		case SC_DEATHKINGHT:		/* デスナイトの魂 */
		case SC_COLLECTOR:		/* コレクターの魂 */
			if(sd && battle_config.disp_job_soul_state_change)
				clif_disp_onlyself(sd->fd, msg_txt(207));	// 魂状態が終了しました
			break;
		case SC_KNIGHT:			/* ナイトの魂 */
		case SC_ALCHEMIST:		/* アルケミストの魂 */
		case SC_BARDDANCER:		/* バードとダンサーの魂 */
		case SC_BLACKSMITH:		/* ブラックスミスの魂 */
		case SC_HUNTER:			/* ハンターの魂 */
		case SC_HIGH:			/* 一次上位職業の魂 */
			if(sd && battle_config.disp_job_soul_state_change)
				clif_disp_onlyself(sd->fd, msg_txt(207));	// 魂状態が終了しました
			calc_flag = 1;
			break;
		case SC_POEMBRAGI:			/* ブラギ */
		case SC_WHISTLE:			/* 口笛 */
		case SC_ASSNCROS:			/* 夕陽のアサシンクロス */
		case SC_APPLEIDUN:			/* イドゥンの林檎 */
		case SC_HUMMING:			/* ハミング */
		case SC_DONTFORGETME:			/* 私を忘れないで */
		case SC_FORTUNE:			/* 幸運のキス */
		case SC_SERVICE4U:			/* サービスフォーユー */
			calc_flag = 1;
			if(type == SC_DONTFORGETME)
				ud->state.change_speed = 1;
			// 踊り演奏持続セット
			if(sc->data[type + SC_WHISTLE_ - SC_WHISTLE].timer == -1)
				status_change_start(bl,type + SC_WHISTLE_ - SC_WHISTLE,sc->data[type].val1,
					sc->data[type].val2,sc->data[type].val3,sc->data[type].val4,battle_config.dance_and_play_duration,0);
			break;
		case SC_WHISTLE_:			/* 口笛 */
		case SC_ASSNCROS_:			/* 夕陽のアサシンクロス */
		case SC_APPLEIDUN_:			/* イドゥンの林檎 */
		case SC_HUMMING_:			/* ハミング */
		case SC_DONTFORGETME_:			/* 私を忘れないで */
		case SC_FORTUNE_:			/* 幸運のキス */
		case SC_SERVICE4U_:			/* サービスフォーユー */
			calc_flag = 1;
			break;
		case SC_MARIONETTE:			/* マリオネットコントロール (自分) */
		case SC_MARIONETTE2:			/* マリオネットコントロール (相手) */
			{
				struct block_list *tbl = map_id2bl(sc->data[type].val2);
				if(tbl) {
					struct status_change *tsc = status_get_sc(tbl);
					int tmp = (type == SC_MARIONETTE)? SC_MARIONETTE2: SC_MARIONETTE;
					// 相方がマリオネット状態ならいっしょに解除
					if(tsc && tsc->data[tmp].timer != -1)
						status_change_end(tbl, tmp, -1);
				}
			}
			calc_flag = 1;
			break;
		case SC_BERSERK:			/* バーサーク */
			calc_flag = 1;
			if(sd) {
				clif_status_load_id(sd,SI_INCREASEAGI,0);	// アイコン消去
				status_change_start(bl,SC_NATURAL_HEAL_STOP,0,0,0,0,skill_get_time2(LK_BERSERK,sc->data[type].val1),0);
			}
			break;
		case SC_HALLUCINATION:
			if(sd)
				clif_status_load_id(sd,SI_HALLUCINATION,0);	// アイコン消去
			break;

		case SC_ENDURE:				/* インデュア */
			calc_flag = 1;
			// fall through
		case SC_AUTOGUARD:			/* オートガード */
		case SC_REFLECTSHIELD:			/* リフレクトシールド */
			if(sd) {
				struct map_session_data *tsd;
				int i;
				// 被ディボーション者も解除する
				for(i = 0; i < 5; i++) {
					if(sd->dev.val1[i] && (tsd = map_id2sd(sd->dev.val1[i])) != NULL && tsd->sc.data[type].timer != -1)
						status_change_end(&tsd->bl, type, -1);
				}
			}
			break;

		case SC_DEVOTION:		/* ディボーション */
			{
				struct map_session_data *dsd = map_id2sd(sc->data[type].val1);

				sc->data[type].val1 = 0;
				sc->data[type].val2 = 0;

				if(sc->data[SC_AUTOGUARD].timer != -1)
					status_change_end(bl, SC_AUTOGUARD, -1);
				if(sc->data[SC_DEFENDER].timer != -1)
					status_change_end(bl, SC_DEFENDER, -1);
				if(sc->data[SC_REFLECTSHIELD].timer != -1)
					status_change_end(bl, SC_REFLECTSHIELD, -1);
				if(sc->data[SC_ENDURE].timer != -1)
					status_change_end(bl, SC_ENDURE, -1);
				if(dsd)
					skill_devotion(dsd);
			}
			break;
		case SC_BLADESTOP:
			{
				struct block_list *tbl = map_id2bl(sc->data[type].val4);
				if(tbl) {
					struct status_change *tsc = status_get_sc(tbl);
					// 片方が切れたので相手の白刃状態が切れてないのなら解除
					if(tsc && tsc->data[SC_BLADESTOP].timer != -1)
						status_change_end(tbl,SC_BLADESTOP,-1);
					if(sc->data[type].val2 == 2)
						clif_bladestop(map_id2bl(sc->data[type].val3),tbl->id,0);
				}
			}
			break;
		case SC_CLOSECONFINE:
		case SC_STOP:
			{
				struct block_list *tbl = map_id2bl(sc->data[type].val4);
				if(tbl) {
					struct status_change *tsc = status_get_sc(tbl);
					// 片方が切れたので相手が切れてないのなら解除
					if(tsc && tsc->data[type].timer != -1)
						status_change_end(tbl,type,-1);
				}
				calc_flag = 1;
			}
			break;
		case SC_DANCING:
			{
				struct map_session_data *dsd;
				// 月明りだけここでアイコン消去
				if(sc->data[type].val1 == CG_MOONLIT)
					clif_status_change(bl,SI_MOONLIT,0,0,0,0,0);	// アイコン消去

				if(sc->data[type].val4 && (dsd = map_id2sd(sc->data[type].val4))) {
					// 合奏で相手がいる場合相手のval4を0にする
					if(dsd->sc.data[type].timer != -1)
						dsd->sc.data[type].val4 = 0;
				}
				if(sc->data[SC_LONGINGFREEDOM].timer != -1)
					status_change_end(bl,SC_LONGINGFREEDOM,-1);
			}
			calc_flag = 1;
			ud->state.change_speed = 1;
			break;
		case SC_GOSPEL:
		case SC_GRAFFITI:
		case SC_WARM:
		case SC_GRAVITATION_USER:
		case SC_DANCING_KNIFE:
			{
				struct skill_unit_group *sg = map_id2sg(sc->data[type].val4);	// val4がgroup_id
				sc->data[type].val4 = 0;
				if(sg)
					skill_delunitgroup(sg);
			}
			break;
		case SC_NOCHAT:			/* チャット禁止状態 */
			if(sd)
				clif_updatestatus(sd,SP_MANNER);
			break;
		case SC_SPLASHER:		/* ベナムスプラッシャー */
			{
				struct block_list *src = map_id2bl(sc->data[type].val3);
				if(src && tid != -1) {
					// 自分にダメージ＆周囲3*3にダメージ
					skill_castend_damage_id(src,bl,sc->data[type].val2,sc->data[type].val1,gettick(),0);
				}
			}
			break;
		case SC_ANKLE:
		case SC_THORNS_TRAP:	/* ソーントラップ */
			{
				struct skill_unit_group *sg = map_id2sg(sc->data[type].val2);
				// skill_delunitgroupからstatus_change_end が呼ばれない為に、
				// 一端発動していない事にしてからグループ削除する。
				if(sg) {
					sg->val2 = 0;
					skill_delunitgroup(sg);
				}
			}
			break;
		case SC_SELFDESTRUCTION:	/* 自爆 */
			unit_stop_walking(bl,5);
			if(md) {
				md->mode &= ~MD_CANMOVE;
				md->state.special_mob_ai = 2;
			}
			break;
		case SC_BUNSINJYUTSU:	/* 分身の術 */
			if(sd) {
				int color = sc->data[SC_BUNSINJYUTSU].val4;
				if(color > 0)
					pc_changelook(sd, LOOK_CLOTHES_COLOR, color);
			}
			break;
		case SC_SEVENWIND:	/* 暖かい風 */
			if(sd)
				clif_status_load_id(sd,sc->data[type].val2,0);
			break;
		case SC_AUTOBERSERK:
			if(sc->data[SC_PROVOKE].timer != -1 && sc->data[SC_PROVOKE].val2 == 1) {
				status_change_end(bl,SC_PROVOKE,-1);
			}
			break;
		case SC_HALLUCINATIONWALK:	/* ハルシネーションウォーク */
			// ペナルティ開始
			status_change_start(bl,SC_HALLUCINATIONWALK_POSTDELAY,0,0,0,0,skill_get_time2(GC_HALLUCINATIONWALK,sc->data[type].val1),0);
			calc_flag = 1;
			ud->state.change_speed = 1;
			break;
		case SC_MILLENNIUMSHIELD:	/* ミレニアムシールド */
			if(sd)
				clif_mshield(sd, 0);
			break;
		case SC_WHITEIMPRISON:	/* ホワイトインプリズン */
			{
				int dmg = 400 * sc->data[type].val1;
				clif_damage(bl,bl,gettick(),0,0,dmg,0,9,0,0);
				battle_damage(bl,bl,dmg,0,0,0);
			}
			break;
		case SC_SPELLBOOK:			/* スペルブック */
			if(sd) {
				// 保存スキル情報を初期化
				memset(sd->freeze_sp_skill, 0, sizeof(sd->freeze_sp_skill[0])*MAX_FREEZE_SPELL);
				sd->freeze_sp_slot = 0;		// スロット数を初期化
			}
			break;
		case SC_NEUTRALBARRIER_MASTER:	/* ニュートラルバリアー(使用者) */
		case SC_STEALTHFIELD_MASTER:	/* ステルスフィールド(使用者) */
			{
				struct skill_unit_group *sg = map_id2sg(sc->data[type].val4);	// val4がgroup_id
				sc->data[type].val4 = 0;
				if(sg)
					skill_delunitgroup(sg);
				calc_flag = 1;
				ud->state.change_speed = 1;
			}
			break;
		case SC__SHADOWFORM:		/* シャドウフォーム */
			{
				struct map_session_data *dsd;
				if((dsd = map_id2sd(sc->data[type].val2)) != NULL)
					dsd->shadowform_id = 0;
			}
			break;
		case SC_FORCEOFVANGUARD:	/* フォースオブバンガード */
			if(sd)
				clif_mshield(sd, 0);
			calc_flag = 1;
			break;
		case SC_BANDING:		/* バンディング */
			{
				struct skill_unit_group *sg = map_id2sg(sc->data[type].val4);
				sc->data[type].val4 = 0;
				if(sg)
					skill_delunitgroup(sg);
				calc_flag = 1;
			}
			break;
		case SC_RAISINGDRAGON:		/* 潜龍昇天 */
			if(sd) {
				int max = pc_checkskill(sd,MO_CALLSPIRITS);
				if(sd->spiritball.num > max)
					pc_delspiritball(sd,sd->spiritball.num-max,0);
			}
			calc_flag = 1;
			break;
		case SC_SATURDAY_NIGHT_FEVER:	/* フライデーナイトフィーバー */
			status_change_start(bl,SC_SITDOWN_FORCE,0,0,0,0,3000,0);
			calc_flag = 1;
			break;
		case SC_SPORE_EXPLOSION:	/* スポアエクスプロージョン */
			{
				struct block_list *src = map_id2bl(sc->data[type].val3);
				if(src && tid != -1) {
					skill_castend_damage_id(src,bl,sc->data[type].val2,sc->data[type].val1,gettick(),0);
				}
			}
			break;
		case SC_SUMMON_ELEM:	/* サモンエレメンタル */
			if(sd && sd->eld)
				elem_delete_data(sd);
			break;
		case SC_OVERED_BOOST:		/* オーバードブースト */
			if(sd) {
				int sp = status_get_max_sp(bl) / 2;
				if(sd->status.sp > sp)
					sd->status.sp -= sp;
				else
					sd->status.sp = 0;
				clif_updatestatus(sd,SP_SP);
			}
			else if(hd) {
				hd->status.hungry -= 50;
				if(hd->status.hungry <= 0) {
					hd->status.hungry = 1;	// 0にはならない
				}
			}
			calc_flag = 1;
			break;
		case SC_GRANITIC_ARMOR:		/* グラニティックアーマー */
			{
				int dmg = (int)((atn_bignumber)status_get_max_hp(bl) * sc->data[type].val3 / 100);
				unit_heal(bl, -dmg, 0, 0, 0);
			}
			break;
		case SC_PYROCLASTIC:		/* パイロクラスティック */
			if(sd)
				pc_break_equip(sd, LOC_RARM);
			calc_flag = 1;
			break;
		case SC_FULL_THROTTLE:		/* フルスロットル */
			status_change_start(bl,SC_REBOUND,0,0,0,0,10000,0);
			calc_flag = 1;
			ud->state.change_speed = 1;
			break;
		case SC_SERVANTWEAPON:		/* サーヴァントウェポン */
			if(sd)
				pc_delball(sd,sd->ball.num,0);
			break;
		case SC_CHARGINGPIERCE:		/* チャージングスピア */
			if(sc->data[SC_CHARGINGPIERCE_COUNT].timer != -1)
				status_change_end(bl,SC_CHARGINGPIERCE_COUNT,-1);
			break;
		case SC_GUARD_STANCE:		/* ガードスタンス */
			if(sc->data[SC_GUARDIAN_S].timer != -1)
				status_change_end(bl,SC_GUARDIAN_S,-1);
			if(sc->data[SC_REBOUND_S].timer != -1)
				status_change_end(bl,SC_REBOUND_S,-1);
			calc_flag = 1;
			break;
		case SC_ABYSSFORCEWEAPON:		/* フロムジアビス */
			if(sd)
				pc_delball(sd,sd->ball.num,0);
			break;
		case SC_ROSEBLOSSOM:			/* ロゼブロッサム */
			{
				struct block_list *src = map_id2bl(sc->data[type].val2);
				if(src && tid != -1) {
					skill_castend_damage_id(src,bl,TR_ROSEBLOSSOM_ATK,sc->data[type].val1,gettick(),0);
				}
			}
			break;
		case SC_SUMMON_ELEMENTAL_ARDOR:		/* サモンアルドール */
			if(sd && sd->eld && sd->eld->status.class_ == ELEMID_EM_ARDOR)
				elem_delete_data(sd);
			calc_flag = 1;
			break;
		case SC_SUMMON_ELEMENTAL_DILUVIO:		/* サモンディルビオ */
			if(sd && sd->eld && sd->eld->status.class_ == ELEMID_EM_DILUVIO)
				elem_delete_data(sd);
			calc_flag = 1;
			break;
		case SC_SUMMON_ELEMENTAL_PROCELLA:		/* サモンプロセラ */
			if(sd && sd->eld && sd->eld->status.class_ == ELEMID_EM_PROCELLA)
				elem_delete_data(sd);
			calc_flag = 1;
			break;
		case SC_SUMMON_ELEMENTAL_TERREMOTUS:	/* サモンテレモトゥス */
			if(sd && sd->eld && sd->eld->status.class_ == ELEMID_EM_TERREMOTUS)
				elem_delete_data(sd);
			calc_flag = 1;
			break;
		case SC_SUMMON_ELEMENTAL_SERPENS:		/* サモンサーペンス */
			if(sd && sd->eld && sd->eld->status.class_ == ELEMID_EM_SERPENS)
				elem_delete_data(sd);
			calc_flag = 1;
			break;
		case SC_INTENSIVE_AIM:			/* インテンシブエイム */
			if(sc->data[SC_INTENSIVE_AIM_COUNT].timer != -1)
				status_change_end(bl,SC_INTENSIVE_AIM_COUNT,-1);
			calc_flag = 1;
			break;
		case SC_BLESSING_OF_M_CREATURES:	/* にゃんブレッシング */
			unit_heal(bl,0,0,-200,0);
			status_change_start(bl,SC_BLESSING_OF_M_C_DEBUFF,sc->data[type].val1,0,0,0,skill_get_time2(SH_BLESSING_OF_MYSTICAL_CREATURES,sc->data[type].val1),0);
			calc_flag = 1;
			break;
		/* option1 */
		case SC_FREEZE:
			sc->data[type].val3 = 0;
			break;

		/* option2 */
		case SC_POISON:				/* 毒 */
		case SC_BLIND:				/* 暗黒 */
		case SC_CURSE:
			calc_flag = 1;
			break;
		case SC_GRAVITYCONTROL:	/* 重力調節 */
			{
				int fall_damage = sc->data[type].val2;
				if( fall_damage > 0 ){
					clif_damage(bl,bl,gettick(),0,0,fall_damage,0,9,0,0);
					battle_damage(bl,bl,fall_damage,0,0,0);
				}
			}
			break;
		case SC_DIMENSION2:	/* 次元の書(星帝降臨) */
			if(sd)
				clif_mshield(sd, 0);
			break;
	}
	}

	if(StatusIconChangeTable[type] != SI_BLANK)	// アイコン消去
		clif_status_load(bl,StatusIconChangeTable[type],0);

	switch(type) {	/* 正常に戻るときなにか処理が必要 */
		// opt1
		case SC_STONE:
		case SC_FREEZE:
		case SC_STUN:
		case SC_SLEEP:
		case SC_HELLINFERNO:
		case SC_WHITEIMPRISON:
			sc->opt1 = OPT1_NORMAL;
			opt_flag = 1;
			break;
		// opt2
		case SC_POISON:
			sc->opt2 &= ~OPT2_POISON;
			opt_flag = 1;
			break;
		case SC_CURSE:
		case SC_SILENCE:
		case SC_CONFUSION:
			sc->opt2 &= ~(OPT2_POISON<<(type-SC_POISON));
			opt_flag = 1;
			if(type == SC_CURSE)
				ud->state.change_speed = 1;
			break;
		case SC_FOGWALLPENALTY:
			if(sc->data[SC_BLIND].timer == -1) {
				sc->opt2 &= ~OPT2_BLIND;
				opt_flag = 1;
			}
			break;
		case SC_BLIND:
			if(sc->data[SC_FOGWALLPENALTY].timer == -1) {
				sc->opt2 &= ~OPT2_BLIND;
				opt_flag = 1;
			}
			break;
		case SC_ANGELUS:			/* アンゼルス */
			sc->opt2 &= ~OPT2_ANGELUS;
			opt_flag = 1;
			break;
		case SC_DPOISON:
			sc->opt2 &= ~OPT2_HEAVYPOISON;
			opt_flag = 1;
			break;
		case SC_BLEED:
			sc->opt2 &= ~OPT2_BLEEDING;
			opt_flag = 1;
			break;
		case SC_FEAR:
			sc->opt2 &= ~OPT2_FEAR;
			opt_flag = 1;
			break;
		// opt3
		case SC_ONEHAND:		/* 1HQ */
		case SC_TWOHANDQUICKEN:		/* 2HQ */
		case SC_SPEARQUICKEN:		/* スピアクイッケン */
		case SC_CONCENTRATION:		/* コンセントレーション */
		case SC_WEAPONQUICKEN:		/* ウェポンクイッケン */
			sc->opt3 &= ~OPT3_QUICKEN;
			opt_flag = 2;
			break;
		case SC_OVERTHRUST:		/* オーバートラスト */
		case SC_SWOO:			/* エスウ */
			sc->opt3 &= ~OPT3_OVERTHRUST;
			opt_flag = 2;
			if(type == SC_SWOO)
				ud->state.change_speed = 1;
			break;
		case SC_ENERGYCOAT:		/* エナジーコート */
		case SC_SKE:			/* エスク */
			sc->opt3 &= ~OPT3_ENERGYCOAT;
			opt_flag = 2;
			break;
		case SC_EXPLOSIONSPIRITS:	/* 爆裂波動 */
			sc->opt3 &= ~OPT3_EXPLOSIONSPIRITS;
			opt_flag = 2;
			break;
		case SC_STEELBODY:		/* 金剛 */
		case SC_SKA:			/* エスカ */
			sc->opt3 &= ~OPT3_STEELBODY;
			opt_flag = 2;
			break;
		case SC_BLADESTOP:		/* 白刃取り */
			sc->opt3 &= ~OPT3_BLADESTOP;
			opt_flag = 2;
			break;
		case SC_AURABLADE:			/* オーラブレード */
			sc->opt3 &= ~OPT3_AURABLADE;
			opt_flag = 2;
			break;
		case SC_BERSERK:		/* バーサーク */
			sc->opt3 &= ~OPT3_BERSERK;
			opt_flag = 2;
			break;
		case SC_DANCING:			/* ダンス/演奏中 */
			if(sc->data[SC_DANCING].val1 != CG_MOONLIT)
				break;
			sc->opt3 &= ~OPT3_MOON;
			opt_flag = 2;
			break;
		case SC_MARIONETTE:		/* マリオネットコントロール */
		case SC_MARIONETTE2:		/* マリオネットコントロール */
			sc->opt3 &= ~OPT3_MARIONETTE;
			opt_flag = 2;
			break;
		case SC_ASSUMPTIO:		/* アスムプティオ */
		case SC_ASSUMPTIO2:		/* キャッシュアスムプティオ */
			sc->opt3 &= ~OPT3_ASSUMPTIO;
			opt_flag = 2;
			break;
		case SC_WARM:			/* 温もり */
			sc->opt3 &= ~OPT3_SUN_WARM;
			opt_flag = 2;
			break;
		case SC_KAITE:			/* カイト */
			sc->opt3 &= ~OPT3_KAITE;
			opt_flag = 2;
			break;
		case SC_BUNSINJYUTSU:		/* 分身の術 */
			sc->opt3 &= ~OPT3_BUNSIN;
			opt_flag = 2;
			break;
		case SC_MONK:			/* モンクの魂 */
		case SC_STAR:			/* ケンセイの魂 */
		case SC_SAGE:			/* セージの魂 */
		case SC_CRUSADER:		/* クルセイダーの魂 */
		case SC_WIZARD:			/* ウィザードの魂 */
		case SC_PRIEST:			/* プリーストの魂 */
		case SC_ROGUE:			/* ローグの魂 */
		case SC_ASSASIN:		/* アサシンの魂 */
		case SC_SOULLINKER:		/* ソウルリンカーの魂 */
		case SC_KNIGHT:			/* ナイトの魂 */
		case SC_ALCHEMIST:		/* アルケミストの魂 */
		case SC_BARDDANCER:		/* バードとダンサーの魂 */
		case SC_BLACKSMITH:		/* ブラックスミスの魂 */
		case SC_HUNTER:			/* ハンターの魂 */
		case SC_HIGH:			/* 一次上位職業の魂 */
		case SC_SUPERNOVICE:		/* スーパーノービスの魂 */
		case SC_GUNNER:			/* ガンスリンガーの魂 */
		case SC_NINJA:			/* 忍者の魂 */
		case SC_DEATHKINGHT:		/* デスナイトの魂 */
		case SC_COLLECTOR:		/* コレクターの魂 */
			sc->opt3 &= ~OPT3_SOULLINK;
			opt_flag = 2;
			break;
		case SC_ELEMENTUNDEAD:		// 不死
			sc->opt3 &= ~OPT3_UNDEAD;
			opt_flag = 2;
			break;
		// option
		case SC_SIGHT:
			sc->option &= ~OPTION_SIGHT;
			opt_flag = 1;
			break;
		case SC_HIDING:
			// 霞斬りでない通常のハイドならアイコン消去
			if(sd && sc->data[type].val3 == 0)
				clif_status_load_id(sd,SI_HIDING,0);
			sc->option &= ~OPTION_HIDE;
			opt_flag = 1;
			break;
		case SC_CLOAKING:
		case SC_CLOAKINGEXCEED:		/* クローキングエクシード */
		case SC_NEWMOON:			/* 朔月脚 */
		case SC__INVISIBILITY:		/* インビジビリティ */
			sc->option &= ~OPTION_CLOAKING;
			opt_flag = 1;
			break;
		case SC_INVISIBLE:
		case SC__FEINTBOMB:			/* フェイントボム */
			sc->option &= ~OPTION_SPECIALHIDING;
			opt_flag = 1;
			break;
		case SC_REVERSEORCISH:
			sc->option &= ~OPTION_ORCFACE;
			opt_flag = 1;
			break;
		case SC_WEDDING:		/* ウェディング */
			sc->option &= ~OPTION_MARRIED;
			opt_flag = 1;
			break;
		case SC_RUWACH:
			sc->option &= ~OPTION_RUWACH;
			opt_flag = 1;
			break;
		case SC_CHASEWALK:		/* チェイスウォーク */
			sc->option &= ~(OPTION_CLOAKING | OPTION_FOOTPRINT);
			opt_flag = 1;
			break;
		case SC_FUSION:
			sc->option &= ~OPTION_STAR2;
			opt_flag = 1;
			break;
		case SC_SANTA:
			sc->option &= ~OPTION_SANTA;
			opt_flag = 1;
			break;
		case SC_SUMMER:
			sc->option &= ~OPTION_SUMMER;
			opt_flag = 1;
			break;
		case SC_ON_PUSH_CART:
#if PACKETVER < 20120201
			// 古いクライアントはオプションを更新する
			sc->option &= ~sc->data[type].val1;
			opt_flag = 1;
#endif
			break;
	}

	/* optionの変更 */
	if(opt_flag == 1) {
		clif_changeoption(bl);
	} else if(opt_flag == 2) {
		clif_changeoption2(bl);
	}

#ifdef DYNAMIC_SC_DATA
	if(sc->count <= 0 && battle_config.free_sc_data_dynamically)
		status_free_sc_data(sc);
#endif

	/* ステータス再計算 */
	if(sd) {
		if(calc_flag || sd->auto_status_calc_pc[type] == 1) {
			status_calc_pc(sd,0);
		}
	} else if(hd) {
		if(calc_flag) {
			homun_calc_status(hd);
			clif_send_homstatus(hd->msd,0);
		}
	} else if(mcd) {
		if(calc_flag) {
			merc_calc_status(mcd);
			clif_send_mercstatus(mcd->msd);
			clif_mercskillinfoblock(mcd->msd);
		}
	} else if(eld) {
		if(calc_flag) {
			elem_calc_status(eld);
			clif_send_elemstatus(eld->msd);
		}
	}

	return 0;
}
