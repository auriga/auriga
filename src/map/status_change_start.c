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
 * ステータス異常開始
 *------------------------------------------
 */
int status_change_start(struct block_list *bl,int type,int val1,int val2,int val3,int val4,int tick,int flag)
{
	struct map_session_data *sd  = NULL;
	struct mob_data         *md  = NULL;
	struct homun_data       *hd  = NULL;
	struct merc_data        *mcd = NULL;
	struct elem_data        *eld = NULL;
	struct status_change    *sc  = NULL;
	struct unit_data        *ud  = NULL;
	int icon_tick = tick, icon_val1 = 0, icon_val2 = 0, icon_val3 = 0, opt_flag = 0, calc_flag = 0, race, mode, elem;
	unsigned int current_tick = gettick();

	nullpo_retr(0, bl);

	if(type < 0)
		return 0;

	sc = status_get_sc(bl);
	if(sc == NULL)
		return 0;
	ud = unit_bl2ud(bl);
	if(ud == NULL)
		return 0;

	if(bl->type == BL_HOM && !battle_config.allow_homun_status_change)
	{
		if((type < SC_AVOID || (type > SC_SPEED && type < SC_PARALYZE) || type > SC_VOLCANIC_ASH) && type != SC_COMBO)
			return 0;
	}

	if(status_get_class(bl) == MOBID_EMPERIUM && type != SC_SAFETYWALL && type != SC_PNEUMA)
		return 0;

	race = status_get_race(bl);
	mode = status_get_mode(bl);
	elem = status_get_elem_type(bl);

	if(type == SC_AETERNA && (sc->data[SC_STONE].timer != -1 || sc->data[SC_FREEZE].timer != -1))
		return 0;

	// 特殊系
	if(type >= MAX_STATUSCHANGE) {
		switch(type) {
			case SC_SOUL:
				status_change_soulstart(bl,val1,val2,val3,val4,tick,flag);
				break;
			default:
				if(battle_config.error_log)
					printf("UnknownStatusChange [%d]\n", type);
				break;
		}
		return 0;
	}

	// ON/OFF
	switch(type) {
		case SC_AUTOBERSERK:
		case SC_READYSTORM:
		case SC_READYDOWN:
		case SC_READYTURN:
		case SC_READYCOUNTER:
		case SC_DODGE:
		case SC_FUSION:
		case SC_WEAPONBLOCKING:
		case SC_CLOAKINGEXCEED:
		//case SC_CAMOUFLAGE:
		case SC__REPRODUCE:
		case SC__INVISIBILITY:
		case SC_REFLECTDAMAGE:
		case SC_FORCEOFVANGUARD:
		case SC_SOULCOLLECT:		/* 魂の蓄積 */
			if(sc->data[type].timer != -1) {
				status_change_end(bl,type,-1);
				return 0;
			}
			break;
		case SC_MAGNIFICAT:
			status_change_end(bl,SC_OFFERTORIUM,-1);
			break;
		case SC_OFFERTORIUM:
			status_change_end(bl,SC_MAGNIFICAT,-1);
			break;
		case SC_MADNESSCANCEL:
			status_change_end(bl,SC_HEAT_BARREL,-1);
			status_change_end(bl,SC_P_ALTER,-1);
			break;
		case SC_HEAT_BARREL:
			status_change_end(bl,SC_P_ALTER,-1);
			status_change_end(bl,SC_MADNESSCANCEL,-1);
			break;
		case SC_P_ALTER:
			status_change_end(bl,SC_MADNESSCANCEL,-1);
			status_change_end(bl,SC_HEAT_BARREL,-1);
			break;
		case SC_LUNARSTANCE:
		case SC_UNIVERSESTANCE:
		case SC_SUNSTANCE:
		case SC_STARSTANCE:
			{
				int i;
				bool cancel = false;
				const int se_stance_list[] = { SC_LUNARSTANCE, SC_UNIVERSESTANCE, SC_SUNSTANCE, SC_STARSTANCE };
				const int se_light_list[] = { SC_LIGHTOFMOON, -1, SC_LIGHTOFSUN, SC_LIGHTOFSTAR };

				for( i = 0; i < sizeof(se_stance_list)/sizeof(se_stance_list[0]); i++ ){
					int sc_checking = se_stance_list[i];
					if(sc->data[sc_checking].timer != -1){
						status_change_end(bl,sc_checking,-1);
						if( sc_checking == type ){
							cancel = true;
						}
						sc_checking = se_light_list[i];
						if( sc_checking >= 0 && sc->data[sc_checking].timer != -1){
							status_change_end(bl,sc_checking,-1);
						}
					}
				}
				if( cancel ){
					return 0;
				}
			}
			break;
		// 3次新毒スキル
		case SC_TOXIN:
		case SC_PARALIZE:
		case SC_VENOMBLEED:
		case SC_MAGICMUSHROOM:
		case SC_DEATHHURT:
		case SC_PYREXIA:
		case SC_OBLIVIONCURSE:
		case SC_LEECHEND:
			if(sc->data[SC_TOXIN].timer != -1 ||
			   sc->data[SC_PARALIZE].timer != -1 ||
			   sc->data[SC_VENOMBLEED].timer != -1 ||
			   sc->data[SC_MAGICMUSHROOM].timer != -1 ||
			   sc->data[SC_DEATHHURT].timer != -1 ||
			   sc->data[SC_PYREXIA].timer != -1 ||
			   sc->data[SC_OBLIVIONCURSE].timer != -1 ||
			   sc->data[SC_LEECHEND].timer != -1
			) {
				// 新毒は重複させない
				return 0;
			}
			break;
		// 3次歌スキル 独奏
		case SC_SWING:
		case SC_SYMPHONY_LOVE:
		case SC_MOONLIT_SERENADE:
		case SC_RUSH_WINDMILL:
		case SC_ECHOSONG:
		case SC_HARMONIZE:
		case SC_FRIGG_SONG:
			if(sc->data[SC_SWING].timer != -1)
				status_change_end(bl,SC_SWING,-1);
			if(sc->data[SC_SYMPHONY_LOVE].timer != -1)
				status_change_end(bl,SC_SYMPHONY_LOVE,-1);
			if(sc->data[SC_MOONLIT_SERENADE].timer != -1)
				status_change_end(bl,SC_MOONLIT_SERENADE,-1);
			if(sc->data[SC_RUSH_WINDMILL].timer != -1)
				status_change_end(bl,SC_RUSH_WINDMILL,-1);
			if(sc->data[SC_ECHOSONG].timer != -1)
				status_change_end(bl,SC_ECHOSONG,-1);
			if(sc->data[SC_HARMONIZE].timer != -1)
				status_change_end(bl,SC_HARMONIZE,-1);
			if(sc->data[SC_FRIGG_SONG].timer != -1)
				status_change_end(bl,SC_FRIGG_SONG,-1);
			break;
		// 3次歌スキル 合奏
		case SC_SIREN:
		case SC_SIRCLEOFNATURE:
		case SC_SONG_OF_MANA:
		case SC_DANCE_WITH_WUG:
		case SC_SATURDAY_NIGHT_FEVER:
		case SC_LERADS_DEW:
		case SC_MELODYOFSINK:
		case SC_BEYOND_OF_WARCRY:
		case SC_UNLIMITED_HUMMING_VOICE:
			if(battle_config.third_song_overlap) {	// 戦闘設定で歌スキル重複可能の場合
				// メロディーオブシンクとビヨンドオブウォークライは重複させない
				if(type == SC_MELODYOFSINK && sc->data[SC_BEYOND_OF_WARCRY].timer != -1)
					status_change_end(bl,SC_BEYOND_OF_WARCRY,-1);
				if(type == SC_BEYOND_OF_WARCRY && sc->data[SC_MELODYOFSINK].timer != -1)
					status_change_end(bl,SC_MELODYOFSINK,-1);
				break;
			}
			if(sc->data[SC_SIREN].timer != -1)
				status_change_end(bl,SC_SIREN,-1);
			if(sc->data[SC_SIRCLEOFNATURE].timer != -1)
				status_change_end(bl,SC_SIRCLEOFNATURE,-1);
			if(sc->data[SC_SONG_OF_MANA].timer != -1)
				status_change_end(bl,SC_SONG_OF_MANA,-1);
			if(sc->data[SC_DANCE_WITH_WUG].timer != -1)
				status_change_end(bl,SC_DANCE_WITH_WUG,-1);
			if(sc->data[SC_SATURDAY_NIGHT_FEVER].timer != -1)
				status_change_end(bl,SC_SATURDAY_NIGHT_FEVER,-1);
			if(sc->data[SC_LERADS_DEW].timer != -1)
				status_change_end(bl,SC_LERADS_DEW,-1);
			if(sc->data[SC_MELODYOFSINK].timer != -1)
				status_change_end(bl,SC_MELODYOFSINK,-1);
			if(sc->data[SC_BEYOND_OF_WARCRY].timer != -1)
				status_change_end(bl,SC_BEYOND_OF_WARCRY,-1);
			if(sc->data[SC_UNLIMITED_HUMMING_VOICE].timer != -1)
				status_change_end(bl,SC_UNLIMITED_HUMMING_VOICE,-1);
			break;
		case SC_POWERFUL_FAITH:
		case SC_FIRM_FAITH:
		case SC_SINCERE_FAITH:
			if(sc->data[SC_POWERFUL_FAITH].timer != -1)
				status_change_end(bl,SC_POWERFUL_FAITH,-1);
			if(sc->data[SC_FIRM_FAITH].timer != -1)
				status_change_end(bl,SC_FIRM_FAITH,-1);
			if(sc->data[SC_SINCERE_FAITH].timer != -1)
				status_change_end(bl,SC_SINCERE_FAITH,-1);
			break;
		case SC_FIRST_FAITH_POWER:
			if(sc->data[SC_SECOND_JUDGE].timer != -1)
				status_change_end(bl,SC_SECOND_JUDGE,-1);
			if(sc->data[SC_THIRD_EXOR_FLAME].timer != -1)
				status_change_end(bl,SC_THIRD_EXOR_FLAME,-1);
			break;
		case SC_SECOND_JUDGE:
			if(sc->data[SC_FIRST_FAITH_POWER].timer != -1)
				status_change_end(bl,SC_FIRST_FAITH_POWER,-1);
			break;
		case SC_THIRD_EXOR_FLAME:
			if(sc->data[SC_SECOND_JUDGE].timer != -1)
				status_change_end(bl,SC_SECOND_JUDGE,-1);
			break;
		case SC_GUARD_STANCE:
			if(sc->data[SC_GUARD_STANCE].timer != -1) {
				status_change_end(bl,SC_GUARD_STANCE,-1);
				return 0;
			}
			if(sc->data[SC_ATTACK_STANCE].timer != -1)
				status_change_end(bl,SC_ATTACK_STANCE,-1);
			break;
		case SC_ATTACK_STANCE:
			if(sc->data[SC_ATTACK_STANCE].timer != -1) {
				status_change_end(bl,SC_ATTACK_STANCE,-1);
				return 0;
			}
			if(sc->data[SC_GUARD_STANCE].timer != -1)
				status_change_end(bl,SC_GUARD_STANCE,-1);
			break;
		case SC_INTENSIVE_AIM:		/* インテンシブエイム */
			if(sc->data[SC_INTENSIVE_AIM].timer != -1) {
				status_change_end(bl,SC_INTENSIVE_AIM,-1);
				return 0;
			}
			break;
	}

	sd  = BL_DOWNCAST( BL_PC,   bl );
	md  = BL_DOWNCAST( BL_MOB,  bl );
	hd  = BL_DOWNCAST( BL_HOM,  bl );
	mcd = BL_DOWNCAST( BL_MERC, bl );
	eld = BL_DOWNCAST( BL_ELEM, bl );

	if( sd ) {
		int weapon = sd->status.weapon;
		if(weapon >= WT_MAX)
			weapon -= WT_DOUBLE_DD + WT_MAX;

		// アドレナリンラッシュの武器判定
		if( type == SC_ADRENALINE && !(skill_get_weapontype(BS_ADRENALINE)&(1<<weapon)) )
			return 0;
		// フルアドレナリンラッシュの武器判定
		if( type == SC_ADRENALINE2 && !(skill_get_weapontype(BS_ADRENALINE2)&(1<<weapon)) )
			return 0;
		if( !(flag&8) && SC_STONE <= type && type <= SC_BLEED ) {	/* カードによる耐性 */
			int scdef = sd->reseff[type-SC_STONE];
			if(sc->data[SC_SIEGFRIED].timer != -1) {	// ジークフリードの状態異常耐性
				scdef += 5000;
			}
			if(scdef > 0 && atn_rand()%10000 < scdef) {
				if(battle_config.battle_log)
					printf("PC %d skill_sc_start: cardによる異常耐性発動\n", sd->bl.id);
				return 0;
			}
#ifndef PRE_RENEWAL
			tick = tick * (10000 - scdef) / 10000;
			if(tick <= 0)
				return 0;
#endif
		}
	}

	// アンデッドは凍結・石化・出血無効
	if((race == RCT_UNDEAD || elem == ELE_UNDEAD) && !(flag&1) && (type == SC_STONE || type == SC_FREEZE || type == SC_BLEED))
		return 0;

	// ウォーグバイト状態中はハイディング、クローキング無効
	if(sc->data[SC_WUGBITE].timer != -1 && (type == SC_HIDING || type == SC_CLOAKING || type == SC_CLOAKINGEXCEED || type == SC_NEWMOON))
		return 0;

	// ウォーマー状態中は凍結、氷結、冷凍無効
	if(sc->data[SC_WARMER].timer != -1 && (type == SC_FREEZE || type == SC_FROSTMISTY || type == SC_DIAMONDDUST))
		return 0;

	// 永久霜状態中は獄炎呪無効
	if(sc->data[SC_CHILL].timer != -1 && type == SC_BURNT)
		return 0;

	// 行動不能状態異常の優先順位
	if(type >= SC_STONE && type < SC_SLEEP) {
		int i;
		for(i = type; i < SC_SLEEP; i++) {
			if(sc->data[i+1].timer != -1)
				return 0;
		}
	}

	if((type == SC_ADRENALINE || type == SC_ADRENALINE2 || type == SC_WEAPONPERFECTION || type == SC_OVERTHRUST) &&
		sc->data[type].timer != -1 && sc->data[type].val2 && !val2)
		return 0;

	// ボス属性には無効(ただしカードによる効果は適用される)
	if( (mode&MD_BOSS || mode&MD_STATUSCHANGEIMMUNITY) && !(flag&1) && status_is_disable(type,0x01) ) {
		if(type == SC_BLESSING && !battle_check_undead(race,elem) && race != RCT_DEMON) {
			// ブレスは不死/悪魔でないなら効く
			;
		} else {
			return 0;
		}
	}

	// クァグマイア中は無効
	if(sc->data[SC_QUAGMIRE].timer != -1 && status_is_disable(type,0x02))
		return 0;
	// 私を忘れないで中は無効
	if(sc->data[SC_DONTFORGETME].timer != -1 && status_is_disable(type,0x04))
		return 0;
	// 速度減少中は無効
	if(sc->data[SC_DECREASEAGI].timer != -1 && status_is_disable(type,0x08))
		return 0;

	if(type == SC_STUN || type == SC_SLEEP)
		unit_stop_walking(bl,1);

	// ブレッシングによる呪い、石化の解除
	if(type == SC_BLESSING && (sd || (!battle_check_undead(race,elem) && race != RCT_DEMON))) {
		bool f = false;
		if(sc->data[SC_CURSE].timer != -1) {
			status_change_end(bl,SC_CURSE,-1);
			f = true;
		}
		if(sc->data[SC_STONE].timer != -1 && sc->data[SC_STONE].val2 == 0) {
			status_change_end(bl,SC_STONE,-1);
			f = true;
		}

		// 呪い、石化解除時はブレッシング状態にならないので終わる
		if(f)
			return 0;
	}

	/* キングスグレイス状態では特定異常にかからない */
	if(sc->data[SC_KINGS_GRACE].timer != -1) {
		if(type >= SC_STONE && type <= SC_BLEED)
			return 0;
		switch(type) {
			case SC_DPOISON:	case SC_HALLUCINATION:	case SC_FEAR:		case SC_HELLINFERNO:
			case SC_FROSTMISTY:	case SC_DEEP_SLEEP:	case SC_DIAMONDDUST:	case SC_MANDRAGORA:
				return 0;
		}
	}
	/* 特定MAPではタロウの傷状態にならない */
	if(type == SC_BITESCAR && !map[bl->m].flag.pvp && !map[bl->m].flag.gvg && !map[bl->m].flag.turbo)
		return 0;

	if(sc->data[type].timer != -1) {	/* すでに同じ異常になっている場合タイマ解除 */
		if(type == SC_ALL_RIDING || type == SC_HAT_EFFECT) {
			status_change_end(bl,type,-1);
			return 0;
		}
		if(sc->data[type].val1 > val1 && type != SC_COMBO && type != SC_DANCING && type != SC_DEVOTION &&
			type != SC_SPEEDPOTION0 && type != SC_SPEEDPOTION1 && type != SC_SPEEDPOTION2 &&
			type != SC_DOUBLE && type != SC_TKCOMBO && type != SC_DODGE && type != SC_SPURT && type != SC_SEVENWIND &&
			type != SC_SHAPESHIFT && type != SC_ON_PUSH_CART && type != SC_TINDER_BREAKER && type != SC_CBC && type != SC_PYROCLASTIC &&
			type != SC_CLIMAX)
			return 0;
		if((type >= SC_STUN && type <= SC_BLIND) ||
			type == SC_DPOISON || type == SC_FOGWALLPENALTY || type == SC_FORCEWALKING || type == SC_ORATIO ||
			type == SC_FRESHSHRIMP || type == SC_HEAT_BARREL || type == SC_OVERED_BOOST)
			return 0;	/* 継ぎ足しができない状態異常である時は状態異常を行わない */
		if(type == SC_GRAFFITI || type == SC_SEVENWIND || type == SC_SHAPESHIFT || type == SC__AUTOSHADOWSPELL || type == SC_PROPERTYWALK || type == SC_PYROCLASTIC) {
			// 異常中にもう一度状態異常になった時に解除してから再度かかる
			status_change_end(bl,type,-1);
		} else {
			sc->count--;
			delete_timer(sc->data[type].timer, status_change_timer);
			sc->data[type].timer = -1;
#ifdef DYNAMIC_SC_DATA
			if(sc->count <= 0 && battle_config.free_sc_data_dynamically)
				status_free_sc_data(sc);
#endif
		}
	}

	if(type >= 0 && type < MAX_STATUSCHANGE && status_change_handlers[type].start) {
		struct status_change_start_ctx sctx;
		int hr;
		memset(&sctx, 0, sizeof(sctx));
		sctx.bl = bl;
		sctx.sd = sd;
		sctx.md = md;
		sctx.hd = hd;
		sctx.mcd = mcd;
		sctx.eld = eld;
		sctx.sc = sc;
		sctx.ud = ud;
		sctx.type = type;
		sctx.val1 = &val1;
		sctx.val2 = &val2;
		sctx.val3 = &val3;
		sctx.val4 = &val4;
		sctx.tick = &tick;
		sctx.flag = flag;
		sctx.calc_flag = &calc_flag;
		sctx.icon_tick = &icon_tick;
		sctx.icon_val1 = &icon_val1;
		sctx.icon_val2 = &icon_val2;
		sctx.icon_val3 = &icon_val3;
		sctx.opt_flag = &opt_flag;
		hr = status_change_handlers[type].start(&sctx);
		if(hr == STATUS_CHANGE_HANDLER_ABORT)
			return 0;
	} else {
	switch(type) {	/* 異常の種類ごとの処理 */
		case SC_DOUBLE:				/* ダブルストレイフィング */
		case SC_SUFFRAGIUM:			/* サフラギム */
		case SC_MAGNIFICAT:			/* マグニフィカート */
		case SC_AETERNA:			/* エーテルナ */
		case SC_BASILICA:			/* バジリカ */
		case SC_TRICKDEAD:			/* 死んだふり */
		case SC_STRIPWEAPON:
		case SC_STRIPSHIELD:
		case SC_STRIPARMOR:
		case SC_STRIPHELM:
		case SC_CP_WEAPON:
		case SC_CP_SHIELD:
		case SC_CP_ARMOR:
		case SC_CP_HELM:
		case SC_DEVOTION:			/* ディボーション */
		case SC_COMBO:
		case SC_EXTREMITYFIST:			/* 阿修羅覇凰拳 */
		case SC_RICHMANKIM:
		case SC_ROKISWEIL:			/* ロキの叫び */
		case SC_INTOABYSS:			/* 深淵の中に */
		case SC_POEMBRAGI:			/* ブラギの詩 */
		case SC_ANKLE:				/* アンクル */
		case SC_MAGNUM:				/* マグナムブレイク */
		case SC_TIGERFIST:			/* 伏虎拳 */
		case SC_ENERGYCOAT:			/* エナジーコート */
		case SC_POEMBRAGI_:			/* ブラギの詩 */
		case SC_FOGWALLPENALTY:
		case SC_FOGWALL:
		case SC_REVERSEORCISH:
		case SC_GRAVITATION_USER:
		case SC_BLADESTOP_WAIT:			/* 白刃取り(待ち) */
		case SC_SAFETYWALL:			/* セーフティウォール */
		case SC_PNEUMA:				/* ニューマ */
		case SC_KEEPING:
		case SC_BARRIER:
		case SC_AURABLADE:			/* オーラブレード */
		case SC_HEADCRUSH:			/* ヘッドクラッシュ */
		case SC_MELTDOWN:			/* メルトダウン */
		case SC_SPLASHER:			/* ベナムスプラッシャー */
		case SC_GOSPEL:				/* ゴスペル */
		case SC_STATUS_UNCHANGE:		/* 全状態異常耐性 */
		case SC_INCDAMAGE:			/* 被ダメージ%上昇 */
		case SC_PRESERVE:			/* プリザーブ */
		case SC_REGENERATION:			/* 激励 */
		case SC_BATTLEORDER_DELAY:
		case SC_REGENERATION_DELAY:
		case SC_RESTORE_DELAY:
		case SC_EMERGENCYCALL_DELAY:
		case SC_MEAL_INCEXP:
		case SC_MEAL_INCJOB:
		case SC_COMBATHAN:			/* 戦闘教範 */
		case SC_LIFEINSURANCE:			/* 生命保険証 */
		case SC_JOB_COMBATHAN:		/* JOB教範 */
		case SC_FORCEWALKING:
		case SC_TKCOMBO:			/* テコンコンボ */
		case SC_TRIPLEATTACK_RATE_UP:
		case SC_COUNTER_RATE_UP:
		case SC_WARM:				/* 温もり */
		case SC_KAIZEL:				/* カイゼル */
		case SC_KAAHI:				/* カアヒ */
		case SC_SMA:				/* エスマ */
		case SC_MIRACLE:			/* 太陽と月と星の奇跡 */
		case SC_ANGEL:				/* 太陽と月と星の天使 */
		case SC_BABY:				/* パパ、ママ、大好き */
		case SC_DODGE:
		case SC_DODGE_DELAY:
		case SC_DOUBLECASTING:			/* ダブルキャスティング */
		case SC_SHRINK:				/* シュリンク */
		case SC_TIGEREYE:
		case SC_PK_PENALTY:
		case SC_HERMODE:
		case SC_TATAMIGAESHI:			/* 畳返し */
		case SC_NPC_DEFENDER:
		case SC_SLOWCAST:			/* スロウキャスト */
		case SC_CRITICALWOUND:			/* 致命傷 */
		case SC_MAGICMIRROR:			/* マジックミラー */
		case SC_ITEMDROPRATE:			/* バブルガム */
		case SC_HAPPY:				/* 楽しい状態 */
		case SC_NATURAL_HEAL_STOP:		/* 自然回復停止 */
		case SC_REBIRTH:			/* リバース */
		case SC_HELLPOWER:			/* ヘルパワー */
		case SC_MANU_ATK:			/* マヌクフィールドMOB(物理ダメージ上昇) */
		case SC_MANU_DEF:			/* マヌクフィールドMOB(ダメージ減少) */
		case SC_MANU_MATK:			/* マヌクフィールドMOB(魔法ダメージ上昇) */
		case SC_SPL_ATK:			/* スプレンティッドフィールドMOB(物理ダメージ上昇) */
		case SC_SPL_DEF:			/* スプレンティッドフィールドMOB(ダメージ減少) */
		case SC_SPL_MATK:			/* スプレンティッドフィールドMOB(魔法ダメージ減少) */
		case SC_ENCHANTBLADE:		/* エンチャントブレイド */
		case SC_REFRESH:			/* リフレッシュ */
		case SC_VITALITYACTIVATION:	/* バイタリティアクティベーション */
		case SC_WEAPONBLOCKING_POSTDELAY:	/* ウェポンブロッキング（ブロック） */
		case SC_OFFERTORIUM:		/* オフェルトリウム */
		case SC_WHITEIMPRISON:		/* ホワイトインプリズン */
		case SC_RECOGNIZEDSPELL:	/* リゴグナイズドスペル */
		case SC_STASIS:				/* ステイシス */
		case SC_SPELLBOOK:			/* スペルブック */
		case SC_FEARBREEZE:			/* フィアーブリーズ */
		case SC_WUGBITE:			/* ウォーグバイト */
		case SC_HOVERING:			/* ホバーリング */
		case SC_STEALTHFIELD:		/* ステルスフィールド */
		case SC__DEADLYINFECT:		/* デッドリーインフェクト */
		case SC__IGNORANCE:			/* マスカレード：イグノアランス */
		case SC__MANHOLE:			/* マンホール */
		case SC__ESCAPE:			/* エスケープ */
		case SC_FALLENEMPIRE:		/* 大纏崩捶 */
		case SC_CURSEDCIRCLE_USER:	/* 呪縛陣(使用者) */
		case SC_CURSEDCIRCLE:		/* 呪縛陣 */
		case SC_NETHERWORLD:		/* 地獄の歌 */
		case SC_UNLIMITED_HUMMING_VOICE:	/* エンドレスハミングボイス */
		case SC_WARMER:				/* ウォーマー */
		case SC_VACUUM_EXTREME:		/* バキュームエクストリーム */
		case SC_THORNS_TRAP:		/* ソーントラップ */
		case SC_SPORE_EXPLOSION:	/* スポアエクスプロージョン */
		case SC_KG_KAGEHUMI:		/* 幻術 -影踏み- */
		case SC_KYOMU:				/* 幻術 -虚無の影- */
		case SC_AKAITSUKI:			/* 幻術 -紅月- */
		case SC_KO_ZENKAI:			/* 術式 -展開- */
		case SC_KO_JYUMONJIKIRI:	/* 十文字斬り */
		case SC_E_CHAIN:			/* エターナルチェーン */
		case SC_QD_SHOT_READY:		/* クイックドローショット*/
		case SC_FALLEN_ANGEL:		/* フォーリンエンジェル */
		case SC_H_MINE:				/* ハウリングマイン */
		case SC_CIRCLE_OF_FIRE:		/* サークルオブファイア */
		case SC_TIDAL_WEAPON:		/* タイダルウェポン */
		case SC_SU_STOOP:			/* うずくまる */
		case SC_BITESCAR:			/* タロウの傷 */
		case SC_TUNAPARTY:			/* マグロシールド */
		case SC_PROTECTIONOFSHRIMP:	/* エビパーティー */
		case SC_SPIRITOFLAND:		/* 大地の魂 */
		case SC_JP_EVENT01:
		case SC_JP_EVENT02:
		case SC_JP_EVENT03:
		case SC_JP_EVENT04:
		case SC_SUPPORT_EXP:
		case SC_RAID:
		case SC_STYLE_CHANGE:		/* スタイルチェンジ */
		case SC_PHI_DEMON:			/* 古代精霊のお守り */
		case SC_MAXPAIN:			/* マックスペイン */
		case SC_IMMUNE_PROPERTY_NOTHING:	/* イミューンプロパティ(ニュートラル) */
		case SC_IMMUNE_PROPERTY_WATER:	/* イミューンプロパティ(ウォータ) */
		case SC_IMMUNE_PROPERTY_GROUND:	/* イミューンプロパティ(アース) */
		case SC_IMMUNE_PROPERTY_FIRE:	/* イミューンプロパティ(ファイア) */
		case SC_IMMUNE_PROPERTY_WIND	:	/* イミューンプロパティ(ウインド) */
		case SC_IMMUNE_PROPERTY_DARKNESS:	/* イミューンプロパティ(ダーク) */
		case SC_IMMUNE_PROPERTY_SAINT:	/* イミューンプロパティ(ホーリー) */
		case SC_IMMUNE_PROPERTY_POISON:	/* イミューンプロパティ(ポイズン) */
		case SC_IMMUNE_PROPERTY_TELEKINESIS:	/* イミューンプロパティ(ゴースト) */
		case SC_IMMUNE_PROPERTY_UNDEAD:	/* イミューンプロパティ(アンデット) */
		case SC_PC_STOP:		/* 移動不可 */
		case SC_CRUSHSTRIKE:		/* クラッシュストライク */
		case SC_WEAPONBLOCK_ON:		/* カウンタースラッシュ */
		case SC__FEINTBOMB:			/* フェイントボム */
		case SC_MAGICALBULLET:		/* マジカルバレット */
		case SC_SOULCURSE:		/* 死霊憑依 */
		case SC_SWHOO:			/* エスフ詠唱可能状態 */
		case SC_SERVANT_SIGN:		/* サーヴァントサイン */
		case SC_CHARGINGPIERCE:		/* チャージングピアース */
		case SC_DRAGONIC_AURA:		/* ドラゴニックオーラ */
		case SC_VIGOR:			/* ヴィゴール */
		case SC_MASSIVE_F_BLASTER:	/* 炎火滅魔神弾 */
		case SC_FIRST_BRAND:	/* 第一撃：烙印 */
		case SC_FIRST_FAITH_POWER:	/* 第一章：信念の力 */
		case SC_SECOND_JUDGE:	/* 第二章：審判者 */
		case SC_SECOND_BRAND:	/* 第二撃：烙印 */
		case SC_THIRD_EXOR_FLAME:	/* 最終章：滅魔の炎 */
		case SC_GUARDIAN_S:		/* ガーディアンシールド */
		case SC_REBOUND_S:		/* リバウンドシールド */
		case SC_ULTIMATE_S:		/* アルティメットサクリファイス */
		case SC_SPEAR_SCAR:		/* グランドジャッジメント */
		case SC_SHIELD_POWER:	/* シールドシューティング */
		case SC_SHADOW_EXCEED:	/* シャドウエクシード */
		case SC_AXE_STOMP:		/* アックスストンプ */
		case SC_ABR_BATTLE_WARIOR:	/* ABR バトルウォリアー */
		case SC_ABR_DUAL_CANNON:	/* ABR デュアルキャノン */
		case SC_ABR_MOTHER_NET:		/* ABR マザーネット */
		case SC_ABR_INFINITY:		/* ABR インフィニティ */
		case SC_ABYSS_DAGGER:		/* アビスダガー */
		case SC_CALAMITYGALE:		/* カラミティゲイル */
		case SC_CRESCIVEBOLT:		/* クレッシブボルト */
		case SC_PROTECTSHADOWEQUIP:	/* フルシャドウチャージ */
		case SC_RESEARCHREPORT:		/* リサーチレポート */
		case SC_BO_WOODENWARRIOR:	/* ウドゥンウォリアー */
		case SC_BO_WOODEN_FAIRY:	/* ウドゥンフェアリー */
		case SC_BO_CREEPER:			/* クリーパー */
		case SC_BO_HELLTREE:		/* ヘルツリー */
		case SC_KVASIR_SONATA:		/* ソナタオブクヴァシル */
		case SC_ROSEBLOSSOM:		/* ロゼブロッサム */
		case SC_ELEMENTAL_VEIL:		/* エレメンタルヴェール */
		case SC_H_MINE_SPLASH:		/* ハウリングマイン(分散) */
		case SC_T_FIRST_GOD:		/* 青龍符 */
		case SC_T_SECOND_GOD:		/* 白虎符 */
		case SC_T_THIRD_GOD:		/* 朱雀符 */
		case SC_T_FOURTH_GOD:		/* 玄武符 */
		case SC_HOGOGONG:			/* タイガーハウリング */
		case SC_BLESSING_OF_M_C_DEBUFF:	/* にゃんブレッシングリバウンド */
		case SC_BREAKINGLIMIT:		/* ブレイキングリミット */
		case SC_RULEBREAK:			/* ルールブレイク */
		case SC_RISING_SUN:			/* 日出 */
		case SC_NOON_SUN:			/* 正午 */
		case SC_SUNSET_SUN:			/* 日没 */
		case SC_RISING_MOON:		/* 月出 */
		case SC_MIDNIGHT_MOON:		/* 正子 */
		case SC_DAWN_MOON:			/* 月没 */
		case SC_STAR_BURST:			/* 天命落星 */
		case SC_NIGHTMARE:			/* 悪夢 */
			break;

		case SC_CONCENTRATE:			/* 集中力向上 */
		case SC_ANGELUS:			/* アンゼルス */
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
		case SC_GLORIA:				/* グロリア */
		case SC_LOUD:				/* ラウドボイス */
		case SC_MINDBREAKER:			/* マインドブレーカー */
		case SC_ETERNALCHAOS:			/* エターナルカオス */
		case SC_WHISTLE:			/* 口笛 */
		case SC_ASSNCROS:			/* 夕陽のアサシンクロス */
		case SC_APPLEIDUN:			/* イドゥンの林檎 */
		case SC_SANTA:
		case SC_SUMMER:
		case SC_TRUESIGHT:			/* トゥルーサイト */
		case SC_SPIDERWEB:			/* スパイダーウェッブ */
		case SC_CONCENTRATION:			/* コンセントレーション */
		case SC_MARIONETTE:			/* マリオネットコントロール */
		case SC_MARIONETTE2:			/* マリオネットコントロール */
		case SC_WEDDING:			/* 結婚用(結婚衣裳になって歩くのが遅いとか) */
		case SC_HUMMING:			/* ハミング */
		case SC_FORTUNE:			/* 幸運のキス */
		case SC_SERVICE4U:			/* サービスフォーユー */
		case SC_WHISTLE_:			/* 口笛 */
		case SC_ASSNCROS_:			/* 夕陽のアサシンクロス */
		case SC_APPLEIDUN_:			/* イドゥンの林檎 */
		case SC_HUMMING_:			/* ハミング */
		case SC_DONTFORGETME_:			/* 私を忘れないで */
		case SC_FORTUNE_:			/* 幸運のキス */
		case SC_SERVICE4U_:			/* サービスフォーユー */
		case SC_INCATK:				/* ATK上昇 (神酒用) */
		case SC_INCMATK:			/* MATK上昇 (神秘の草用) */
		case SC_INCHIT:				/* HIT上昇 */
		case SC_INCMHP2:			/* MHP%上昇 */
		case SC_INCMSP2:			/* MSP%上昇 */
		case SC_INCATK2:			/* ATK%上昇 */
		case SC_INCHIT2:			/* HIT%上昇 */
		case SC_INCFLEE2:			/* FLEE%上昇 */
		case SC_INCALLSTATUS:			/* 全ステータス＋20 */
		case SC_CHASEWALK_STR:			/* STR上昇 */
		case SC_BATTLEORDER:			/* 臨戦態勢 */
		case SC_THE_MAGICIAN:
		case SC_STRENGTH:
		case SC_THE_DEVIL:
		case SC_THE_SUN:
		case SC_SPURT:				/* 駆け足用STR */
		case SC_SUN_COMFORT:			/* 太陽の安楽 */
		case SC_MOON_COMFORT:			/* 月の安楽 */
		case SC_STAR_COMFORT:			/* 星の安楽 */
		case SC_FUSION:				/* 太陽と月と星の融合 */
		case SC_MEAL_INCHIT:	// 食事用
		case SC_MEAL_INCFLEE:
		case SC_MEAL_INCFLEE2:
		case SC_MEAL_INCCRITICAL:
		case SC_MEAL_INCDEF:
		case SC_MEAL_INCMDEF:
		case SC_MEAL_INCATK:
		case SC_MEAL_INCMATK:
		case SC_SKE:				/* エスク */
		case SC_SKA:				/* エスカ */
		case SC_CLOSECONFINE:			/* クローズコンファイン */
		case SC_STOP:				/* ホールドウェブ */
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
		case SC_INFRAREDSCAN:		/* インフラレッドスキャン */
		case SC_ANALYZE:			/* アナライズ */
		case SC_NEUTRALBARRIER_MASTER:	/* ニュートラルバリアー(使用者) */
		case SC_NEUTRALBARRIER:		/* ニュートラルバリアー */
		case SC__BODYPAINT:			/* ボディペインティング */
		case SC__ENERVATION:		/* マスカレード：エナベーション */
		case SC__UNLUCKY:			/* マスカレード：アンラッキー */
		case SC__WEAKNESS:			/* マスカレード：ウィークネス */
		case SC__STRIPACCESSARY:	/* ストリップアクセサリー */
		case SC__BLOODYLUST:		/* ブラッディラスト */
		case SC_EARTHDRIVE:			/* アースドライブ */
		case SC_HARMONIZE:			/* ハーモナイズ */
		case SC_GLOOMYDAY:			/* メランコリー */
		case SC_LERADS_DEW:			/* レーラズの露 */
		case SC_DANCE_WITH_WUG:		/* ダンスウィズウォーグ */
		case SC_ILLUSIONDOPING:		/* イリュージョンドーピング */
		case SC_NYANGGRASS:			/* ニャングラス */
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
		case SC_ODINS_POWER:		/* オーディンの力 */
		case SC_ZEPHYR:				/* ゼファー */
		case SC_INVINCIBLE:			/* インビンシブル */
		case SC_INVINCIBLEOFF:		/* インビンシブルオフ */
		case SC_TINDER_BREAKER:		/* 捕獲 */
		case SC_ALL_STAT_DOWN:	/* オールステータスダウン */
		case SC_ADORAMUS:		/* アドラムス */
		case SC_DEADLY_DEFEASANCE:		/* デッドリープロジェクション */
			calc_flag = 1;
			break;

		case SC_MONSTER_TRANSFORM:	/* モンスター変身 */
			icon_val1 = val1;	// val1はモンスターID
			calc_flag = 1;
			break;
		case SC_ALL_RIDING:			/* 騎乗システム */
			if(sd) {
				// 既に既存の乗り物に搭乗中である場合は何もしない
				if(pc_isriding(sd) || pc_isdragon(sd) || pc_iswolfmount(sd) || pc_isgear(sd))
					return 0;
				icon_val1 = 1;	// val1は1
				icon_val2 = 25;	// val2は25(移動速度向上)
				clif_status_load_id(sd,SI_RIDING,1);
			}
			calc_flag = 1;
			ud->state.change_speed = 1;
			break;
		case SC_KYOUGAKU:			/* 幻術 -驚愕- */
			icon_val1 = 1002;
			calc_flag = 1;
			break;
		case SC_HAT_EFFECT:			/* 頭装備エフェクト */
			icon_val1 = val1;
			break;
		case SC_ACTIVE_MONSTER_TRANSFORM:	/* アクティブモンスター変身 */
			icon_val1 = val1;	// val1はモンスターID
			break;

		case SC_WALKSPEED:			/* 移動速度増加(スクリプト) */
		case SC_SLOWPOTION:			/* 移動速度低下(アイテム) */
		case SC_STEELBODY:			/* 金剛 */
		case SC_INCFLEE:			/* FLEE上昇 */
		case SC_GRAVITATION:			/* グラビテーションフィールド */
		case SC_SUITON:				/* 水遁 */
		case SC_GATLINGFEVER:			/* ガトリングフィーバー */
		case SC_HALLUCINATIONWALK:	/* ハルシネーションウォーク */
		case SC_PARALIZE:			/* パラライズ */
		case SC_FROSTMISTY:			/* フロストミスティ */
		case SC_WUGDASH:			/* ウォーグダッシュ */
		case SC_ACCELERATION:		/* アクセラレーション */
		case SC_HALLUCINATIONWALK_POSTDELAY:	/* ハルシネーションウォーク(ペナルティ) */
		case SC__GROOMY:			/* マスカレード：グルーミー */
		case SC__LAZINESS:			/* マスカレード：レイジネス */
		case SC_GN_CARTBOOST:		/* カートブースト */
		case SC_MELON_BOMB:			/* メロン爆弾 */
		case SC_POWER_OF_GAIA:		/* パワーオブガイア */
		case SC_SUPPORT_SPEED:
			calc_flag = 1;
			ud->state.change_speed = 1;
			break;

		case SC_ENDURE:				/* インデュア */
			if(tick <= 0) tick = 1000 * 60;
			calc_flag = 1;
			val2 = 7;	// 7回攻撃されたら解除
			if(sd && !map[bl->m].flag.gvg) {
				// 被ディボーション者もインデュアにする
				struct map_session_data *tsd;
				int i;
				for(i = 0; i < 5; i++) {
					if(sd->dev.val1[i] && (tsd = map_id2sd(sd->dev.val1[i])) != NULL)
						status_change_start(&tsd->bl,type,val1,0,0,0,skill_get_time(SM_ENDURE,val1),0);
				}
			}
			break;
		case SC_DECREASEAGI:		/* 速度減少 */
			calc_flag = 1;
			ud->state.change_speed = 1;
			break;
		case SC_SIGNUMCRUCIS:		/* シグナムクルシス */
			calc_flag = 1;
			val2 = 10 + val1*4;
			tick = 600*1000;
			clif_emotion(bl,4);
			break;
		case SC_SLOWPOISON:
			if (sc->data[SC_POISON].timer == -1 && sc->data[SC_DPOISON].timer == -1)
				return 0;
			break;
		case SC_ONEHAND:			/* 1HQ */
			if(sc->data[SC_SPEEDPOTION0].timer != -1)
				status_change_end(bl,SC_SPEEDPOTION0,-1);
			if(sc->data[SC_SPEEDPOTION1].timer != -1)
				status_change_end(bl,SC_SPEEDPOTION1,-1);
			if(sc->data[SC_SPEEDPOTION2].timer != -1)
				status_change_end(bl,SC_SPEEDPOTION2,-1);
			calc_flag = 1;
			break;
		case SC_ADRENALINE:			/* アドレナリンラッシュ */
			calc_flag = 1;
			if(sc->data[SC_ADRENALINE2].timer != -1)
				status_change_end(bl,SC_ADRENALINE2,-1);
			if(!(flag&2) && sd && pc_checkskill(sd,BS_HILTBINDING) > 0)
				icon_tick = tick += tick / 10;
			break;
		case SC_ADRENALINE2:			/* フルアドレナリンラッシュ */
			calc_flag = 1;
			if(sc->data[SC_ADRENALINE].timer != -1)
				status_change_end(bl,SC_ADRENALINE,-1);
			if(!(flag&2) && sd && pc_checkskill(sd,BS_HILTBINDING) > 0)
				icon_tick = tick += tick / 10;
			break;
		case SC_WEAPONPERFECTION:		/* ウェポンパーフェクション */
			if(!(flag&2) && sd && pc_checkskill(sd,BS_HILTBINDING) > 0)
				icon_tick = tick += tick / 10;
			break;
		case SC_OVERTHRUST:			/* オーバートラスト */
			if(sc->data[SC_OVERTHRUSTMAX].timer != -1)
				return 0;
			val3 = (val2)? val1*5 : val1;
			if(!(flag&2) && sd && pc_checkskill(sd,BS_HILTBINDING) > 0)
				icon_tick = tick += tick / 10;
			break;
		case SC_MAXIMIZEPOWER:		/* マキシマイズパワー */
			if(sd)
				tick = val2;	// SPが1減る時間
			else
				tick = 5000*val1;
			break;
		case SC_ENCPOISON:			/* エンチャントポイズン */
			calc_flag = 1;
			val2 = (((val1 - 1) / 2) + 3)*100;	// 毒付与確率
			status_enchant_elemental_end(bl,SC_ENCPOISON);
			break;
		case SC_EDP:			/* エンチャントデッドリーポイズン */
			val2 = 250 + val1 * 50;	// 猛毒付与確率(%)
			break;
		case SC_POISONREACT:	/* ポイズンリアクト */
			val2 = (val1 + 1) / 2;
			break;
		case SC_ASPERSIO:			/* アスペルシオ */
			status_enchant_elemental_end(bl,SC_ASPERSIO);
			break;
		case SC_BENEDICTIO:			/* 聖体 */
			status_enchant_armor_elemental_end(bl,SC_BENEDICTIO);
			break;
		case SC_ELEMENTWATER:		// 水
			status_enchant_armor_elemental_end(bl,SC_ELEMENTWATER);
			if(sd) {
				// 防具に水属性が付与されました。
				clif_displaymessage(sd->fd, msg_txt(195));
			}
			break;
		case SC_ELEMENTGROUND:		// 土
			status_enchant_armor_elemental_end(bl,SC_ELEMENTGROUND);
			if(sd) {
				// 防具に土属性が付与されました。
				clif_displaymessage(sd->fd, msg_txt(196));
			}
			break;
		case SC_ELEMENTFIRE:		// 火
			status_enchant_armor_elemental_end(bl,SC_ELEMENTFIRE);
			if(sd) {
				// 防具に火属性が付与されました。
				clif_displaymessage(sd->fd, msg_txt(197));
			}
			break;
		case SC_ELEMENTWIND:		// 風
			status_enchant_armor_elemental_end(bl,SC_ELEMENTWIND);
			if(sd) {
				// 防具に風属性が付与されました。
				clif_displaymessage(sd->fd, msg_txt(198));
			}
			break;
		case SC_ELEMENTHOLY:		// 光
			status_enchant_armor_elemental_end(bl,SC_ELEMENTHOLY);
			if(sd) {
				// 防具に聖属性が付与されました。
				clif_displaymessage(sd->fd, msg_txt(199));
			}
			break;
		case SC_ELEMENTDARK:		// 闇
			status_enchant_armor_elemental_end(bl,SC_ELEMENTDARK);
			if(sd) {
				// 防具に闇属性が付与されました。
				clif_displaymessage(sd->fd, msg_txt(200));
			}
			break;
		case SC_ELEMENTELEKINESIS:	// 念
			status_enchant_armor_elemental_end(bl,SC_ELEMENTELEKINESIS);
			if(sd) {
				// 防具に念属性が付与されました。
				clif_displaymessage(sd->fd, msg_txt(201));
			}
			break;
		case SC_ELEMENTPOISON:		// 毒
			status_enchant_armor_elemental_end(bl,SC_ELEMENTPOISON);
			if(sd) {
				// 防具に毒属性が付与されました。
				clif_displaymessage(sd->fd, msg_txt(202));
			}
			break;
		case SC_ELEMENTUNDEAD:		// 不死
			status_enchant_armor_elemental_end(bl,SC_ELEMENTUNDEAD);
			if(sc->data[SC_BLESSING].timer != -1)
				status_change_end(bl,SC_BLESSING,-1);
			if(sc->data[SC_INCREASEAGI].timer != -1)
				status_change_end(bl,SC_INCREASEAGI,-1);
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
			status_change_race_end(bl,type);
			if(sd) {
				const char *race_name[] = { "無形", "不死", "動物", "植物", "昆虫", "", "魚貝", "悪魔", "人間", "天使", "竜" };
				msg_output(sd->fd, msg_txt(204), race_name[type-SC_RACEUNKNOWN]);	// 種族が%sになりました
			}
			break;
		case SC_MAGICROD:
			val2 = val1*20;
			break;
		case SC_KYRIE:				/* キリエエレイソン */
			// アスムが掛かっていたら解除して
			if(sc->data[SC_ASSUMPTIO].timer != -1)
				status_change_end(bl,SC_ASSUMPTIO,-1);
			if(sc->data[SC_ASSUMPTIO2].timer != -1)
				status_change_end(bl,SC_ASSUMPTIO2,-1);
			// キリエを掛ける
			if(val4 > 0) {		// プラエファティオの場合
				val2 = (int)((atn_bignumber)status_get_max_hp(bl) * (val1 * 2 + 16 + val4 * 2) / 100);	// 耐久度
				val3 = val1 + 6;	// 回数
			} else {
				val2 = (int)((atn_bignumber)status_get_max_hp(bl) * (val1 * 2 + 10) / 100);	// 耐久度
				val3 = val1 / 2 + 5;	// 回数
			}
			break;
		case SC_QUAGMIRE:			/* クァグマイア */
			calc_flag = 1;
			ud->state.change_speed = 1;
			if(sc->data[SC_CONCENTRATE].timer != -1)
				status_change_end(bl,SC_CONCENTRATE,-1);
			if(sc->data[SC_INCREASEAGI].timer != -1)
				status_change_end(bl,SC_INCREASEAGI,-1);
			if(sc->data[SC_TWOHANDQUICKEN].timer != -1)
				status_change_end(bl,SC_TWOHANDQUICKEN,-1);
			if(sc->data[SC_SPEARQUICKEN].timer != -1)
				status_change_end(bl,SC_SPEARQUICKEN,-1);
			if(sc->data[SC_ADRENALINE].timer != -1)
				status_change_end(bl,SC_ADRENALINE,-1);
			if(sc->data[SC_ADRENALINE2].timer != -1)
				status_change_end(bl,SC_ADRENALINE2,-1);
			if(sc->data[SC_LOUD].timer != -1)
				status_change_end(bl,SC_LOUD,-1);
			if(sc->data[SC_WINDWALK].timer != -1)
				status_change_end(bl,SC_WINDWALK,-1);
			if(sc->data[SC_CARTBOOST].timer != -1)
				status_change_end(bl,SC_CARTBOOST,-1);
			if(sc->data[SC_ONEHAND].timer != -1)
				status_change_end(bl,SC_ONEHAND,-1);
			if(sc->data[SC_SPEEDUP1].timer != -1)
				status_change_end(bl,SC_SPEEDUP1,-1);
			break;
		case SC_MAGICPOWER:			/* 魔法力増幅 */
			val2 = 1;	// 一度だけ増幅
			break;
		case SC_SACRIFICE:			/* サクリファイス */
			val2 = 5;	// 5回の攻撃で有効
			break;
		case SC_FLAMELAUNCHER:		/* フレームランチャー */
		case SC_FROSTWEAPON:		/* フロストウェポン */
		case SC_LIGHTNINGLOADER:	/* ライトニングローダー */
		case SC_SEISMICWEAPON:		/* サイズミックウェポン */
		case SC_DARKELEMENT:		/* 闇属性 */
		case SC_ATTENELEMENT:		/* 念属性 */
		case SC_UNDEADELEMENT:		/* 不死属性 */
			status_enchant_elemental_end(bl,type);
			break;
		case SC_SEVENWIND:			/* 暖かい風 */
			status_enchant_elemental_end(bl,SC_ENCPOISON);	// エンチャントポイズンは重複してもよい？
#ifdef PRE_RENEWAL
			switch(val1) {
				case 1:  val2 = SI_SEISMICWEAPON;   val3 = ELE_EARTH; break;
				case 2:  val2 = SI_LIGHTNINGLOADER; val3 = ELE_WIND;  break;
				case 3:  val2 = SI_FROSTWEAPON;     val3 = ELE_WATER; break;
				case 4:  val2 = SI_FLAMELAUNCHER;   val3 = ELE_FIRE;  break;
				case 5:  val2 = SI_ATTENELEMENT;    val3 = ELE_GHOST; break;
				default: val2 = SI_DARKELEMENT;     val3 = ELE_DARK;  break;
			}
#else
			switch(val1) {
				case 1:  val2 = SI_SEISMICWEAPON;   val3 = ELE_EARTH; break;
				case 2:  val2 = SI_LIGHTNINGLOADER; val3 = ELE_WIND;  break;
				case 3:  val2 = SI_FROSTWEAPON;     val3 = ELE_WATER; break;
				case 4:  val2 = SI_FLAMELAUNCHER;   val3 = ELE_FIRE;  break;
				case 5:  val2 = SI_ATTENELEMENT;    val3 = ELE_GHOST; break;
				case 6:  val2 = SI_DARKELEMENT;     val3 = ELE_DARK;  break;
				default: val2 = SI_ASPERSIO;        val3 = ELE_HOLY;  break;
			}
#endif
			if(sd) {
				clif_status_change(bl,val2,1,icon_tick,0,0,0);
			}
			break;
		case SC_PROVIDENCE:			/* プロヴィデンス */
			calc_flag = 1;
			val2 = val1*5;
			break;
		case SC_REFLECTSHIELD:
			// リフレクトダメージが掛かっていたら解除
			if(sc->data[SC_REFLECTDAMAGE].timer != -1)
				status_change_end(bl,SC_REFLECTDAMAGE,-1);
			val2 = 10+val1*3;
			if(sd) {
				// 被ディボーション者もリフレクトシールドにする
				struct map_session_data *tsd;
				int i;
				for(i = 0; i < 5; i++) {
					if(sd->dev.val1[i] && (tsd = map_id2sd(sd->dev.val1[i])) != NULL) {
						status_change_start(&tsd->bl,type,val1,0,0,0,skill_get_time(CR_REFLECTSHIELD,val1),0);
					}
				}
			}
			break;
		case SC_AUTOSPELL:			/* オートスペル */
			val4 = 5 + val1*2;
			break;
		case SC_VOLCANO:
			calc_flag = 1;
			val3 = val1*10;
			val4 = (val1 > 5)? 20: val1*(11-val1)/2 + 5;
			break;
		case SC_DELUGE:
			calc_flag = 1;
			val3 = (val1 > 5)? 15: val1*(11-val1)/2;
			val4 = (val1 > 5)? 20: val1*(11-val1)/2 + 5;
			break;
		case SC_VIOLENTGALE:
			calc_flag = 1;
			val3 = val1*3;
			val4 = (val1 > 5)? 20: val1*(11-val1)/2 + 5;
			break;
		case SC_TWOHANDQUICKEN:			/* 2HQ */
			calc_flag = 1;
			if(bl->type == BL_MOB && battle_config.monster_skill_over && val1 >= battle_config.monster_skill_over)
				val2 = 70;
			else
				val2 = 30;
			break;
		case SC_SPEARQUICKEN:		/* スピアクイッケン */
			calc_flag = 1;
#ifdef PRE_RENEWAL
			val2 = 20+val1;
#else
			val2 = 30;
#endif
			break;
		case SC_BLADESTOP:		/* 白刃取り */
			if(val2 == 2)
				clif_bladestop(map_id2bl(val3),val4,1);
			break;
		case SC_LULLABY:			/* 子守唄 */
			val2 = 11;
			break;
		case SC_DRUMBATTLE:			/* 戦太鼓の響き */
			calc_flag = 1;
#ifdef PRE_RENEWAL
			val2 = (val1+1)*25;
			val3 = (val1+1)*2;
#else
			val2 = 100+val1*30;
			val3 = val1*10;
#endif
			break;
		case SC_NIBELUNGEN:			/* ニーベルングの指輪 */
			calc_flag = 1;
#ifdef PRE_RENEWAL
			val2 = (val1+2)*25;
#else
			val2 = val1*40;
#endif
			break;
		case SC_SIEGFRIED:			/* 不死身のジークフリード */
			calc_flag = 1;
			val2 = 5 + val1*15;
			break;
		case SC_DISSONANCE:			/* 不協和音 */
			val2 = 10;
			break;
		case SC_UGLYDANCE:			/* 自分勝手なダンス */
			val2 = 10;
			break;
		case SC_DONTFORGETME:		/* 私を忘れないで */
			calc_flag = 1;
			ud->state.change_speed = 1;
			if(sc->data[SC_INCREASEAGI].timer != -1)
				status_change_end(bl,SC_INCREASEAGI,-1);
			if(sc->data[SC_TWOHANDQUICKEN].timer != -1)
				status_change_end(bl,SC_TWOHANDQUICKEN,-1);
			if(sc->data[SC_SPEARQUICKEN].timer != -1)
				status_change_end(bl,SC_SPEARQUICKEN,-1);
			if(sc->data[SC_ADRENALINE].timer != -1)
				status_change_end(bl,SC_ADRENALINE,-1);
			if(sc->data[SC_ADRENALINE2].timer != -1)
				status_change_end(bl,SC_ADRENALINE2,-1);
			if(sc->data[SC_ASSNCROS].timer != -1)
				status_change_end(bl,SC_ASSNCROS,-1);
			if(sc->data[SC_WINDWALK].timer != -1)
				status_change_end(bl,SC_WINDWALK,-1);
			if(sc->data[SC_CARTBOOST].timer != -1)
				status_change_end(bl,SC_CARTBOOST,-1);
			if(sc->data[SC_ONEHAND].timer != -1)
				status_change_end(bl,SC_ONEHAND,-1);
			break;
		case SC_LONGINGFREEDOM:		/* 私を拘束しないで */
			calc_flag = 1;
			val3 = 1;
			tick = 1000;
			break;
		case SC_DANCING:			/* ダンス/演奏中 */
			calc_flag = 1;
			ud->state.change_speed = 1;
			val3 = tick / 1000;
			tick = 1000;
			break;
		case SC_EXPLOSIONSPIRITS:	/* 爆裂波動 */
			calc_flag = 1;
			val2 = 75 + 25*val1;
			break;
		case SC_AUTOCOUNTER:
			val3 = 0;
			val4 = 0;
			break;
		case SC_SPEEDPOTION0:		/* 増速ポーション */
		case SC_SPEEDPOTION1:
		case SC_SPEEDPOTION2:
			calc_flag = 1;
			val2 = 5*(2+type-SC_SPEEDPOTION0);
			break;
		case SC_NOCHAT:		/* チャット禁止状態 */
			{
				time_t timer;
				tick = 60000;
				if(!val2)
					val2 = (int)time(&timer);
				if(sd)
					clif_updatestatus(sd,SP_MANNER);	// ステータスをクライアントに送る
			}
			break;
		case SC_SELFDESTRUCTION:	/* 自爆 */
			tick = 100;
			break;

		/* option1 */
		case SC_STONE:				/* 石化 */
			if(!(flag&2)) {
#ifdef PRE_RENEWAL
				tick += 100 * status_get_luk(bl) - status_get_mdef(bl) * tick / 100;
#else
				tick += 3000 - tick * status_get_mdef(bl) / 100;
#endif
			}
			val3 = tick / 1000;
			if(val3 < 1)
				val3 = 1;
			tick = val4;
			if(tick < 1000)
				tick = 1000;
			val2 = 1;
			break;
		case SC_SLEEP:				/* 睡眠 */
			if(!(flag&2)) {
#ifdef PRE_RENEWAL
				tick += -10 * status_get_luk(bl) - tick * status_get_int(bl) / 100;
#else
				tick += 1000 - tick * status_get_agi(bl) / 100;
#endif
			}
			break;
		case SC_FREEZE:				/* 凍結 */
			if(!(flag&2)) {
#ifdef PRE_RENEWAL
				tick += 10 * status_get_luk(bl) - tick * status_get_mdef(bl) / 100;
#else
				tick += 3000 - tick * status_get_mdef(bl) / 100;
#endif
			}
			break;
		case SC_STUN:				/* スタン（val2にミリ秒セット） */
			if(!(flag&2)) {
#ifdef PRE_RENEWAL
				tick += -10 * status_get_luk(bl) - tick * status_get_vit(bl) / 100;
#else
				tick += 1000 - tick * status_get_vit(bl) / 100;
#endif
			}
			break;
		/* option2 */
		case SC_DPOISON:			/* 猛毒 */
			{
				int mhp = status_get_max_hp(bl);
				int hp  = status_get_hp(bl);
				if(!(flag&2)) {
					if(bl->type == BL_PC)	// PCの場合のみ計算式が違う
						tick = 5000 + -10000 * status_get_luk(bl) / 100 - 45000 * status_get_vit(bl) / 100 + 55000;
					else
						tick = 30000 - 20000 * status_get_vit(bl) / 100;
				}
				// MHPの1/4以下にはならない
				if(hp > mhp>>2) {
					int diff = 0;
					if(sd)
						diff = mhp * 10 / 100;
					else if(md)
						diff = mhp * 15 / 100;
					if(hp - diff < mhp>>2)
						diff = hp - (mhp>>2);
					unit_heal(bl, -diff, 0, 0, 0);
				}
			}
			// fall through
		case SC_POISON:				/* 毒 */
			calc_flag = 1;
			if(!(flag&2)) {
				if(bl->type == BL_PC)	// PCの場合のみ計算式が違う
					tick = 5000 + -10000 * status_get_luk(bl) / 100 - 45000 * status_get_vit(bl) / 100 + 55000;
				else
					tick = 30000 - 20000 * status_get_vit(bl) / 100;
			}
			val3 = tick/1000;
			if(val3 < 1) val3 = 1;
			tick = 1000;
			break;
		case SC_SILENCE:			/* 沈黙 */
			skill_stop_dancing(bl,0);
			if (sc->data[SC_GOSPEL].timer != -1) {
				status_change_end(bl,SC_GOSPEL,-1);
				break;
			}
			if(!(flag&2)) {
#ifdef PRE_RENEWAL
				tick += -10 * status_get_luk(bl) - tick * status_get_vit(bl) / 100;
#else
				tick += 1000 - tick * status_get_int(bl) / 100;
#endif
			}
			break;
		case SC_BLIND:				/* 暗黒 */
			calc_flag = 1;
			if(!(flag&2)) {
#ifdef PRE_RENEWAL
				tick += -10 * status_get_luk(bl) - tick * (status_get_vit(bl) + status_get_int(bl)) / 200;
#else
				tick += 1000 - tick * status_get_int(bl) / 100;
#endif
			}
			break;
		case SC_CURSE:				/* 呪い */
			calc_flag = 1;
			ud->state.change_speed = 1;
			if(!(flag&2)) {
#ifdef PRE_RENEWAL
				tick += -10 * status_get_luk(bl) - tick * status_get_vit(bl) / 100;
#else
				tick += 1000 - tick * status_get_luk(bl) / 100;
#endif
			}
			break;
		case SC_CONFUSION:			/* 混乱 */
			if(!(flag&2)) {
#ifdef PRE_RENEWAL
				tick += -10 * status_get_luk(bl) - tick * (status_get_str(bl) + status_get_int(bl)) / 200;
#else
				tick += 1000 - tick * status_get_luk(bl) / 100;
#endif
			}
			break;
		case SC_BLEED:				/* 出血 */
			if(!(flag&2)) {
#ifdef PRE_RENEWAL
				icon_tick = tick = -10 * status_get_luk(bl) - tick * status_get_vit(bl) / 100 + tick;
#else
				icon_tick = tick = 1000 - tick * status_get_agi(bl) / 100 + tick;
#endif
			}
			val3 = (tick < 10000)? 1: tick / 10000;
			tick = 10000;	// ダメージ発生は10sec毎
			break;

		/* option */
		case SC_HIDING:		/* ハイディング */
			calc_flag = 1;
			if(sd) {
				val2 = tick / 1000;		/* 持続時間 */
				tick = 1000;
			}
			break;
		case SC_CHASEWALK:		/* チェイスウォーク */
		case SC_CLOAKING:		/* クローキング */
			if(sd) {
				calc_flag = 1;
				tick = val2;
			} else {
				tick = 5000*val1;
			}
			break;
		case SC_INVISIBLE:		/* インビジブル */
			break;
		case SC_SIGHTBLASTER:		/* サイトブラスター */
		case SC_SIGHT:			/* サイト */
		case SC_RUWACH:			/* ルアフ */
			val2 = tick/250;
			tick = 10;
			break;

		case SC_MODECHANGE:
			tick = 1200;
			break;
		case SC_AUTOGUARD:
			val2 = (val1 > 10)? 30: (22 - val1) * val1 / 4;
			if(sd) {
				// 被ディボーション者もオートガードにする
				struct map_session_data *tsd;
				int i;
				for(i = 0; i < 5; i++) {
					if(sd->dev.val1[i] && (tsd = map_id2sd(sd->dev.val1[i])) != NULL)
						status_change_start(&tsd->bl,type,val1,0,0,0,skill_get_time(CR_AUTOGUARD,val1),0);
				}
			}
			break;
		case SC_DEFENDER:
			calc_flag = 1;
			ud->state.change_speed = 1;
			val2 = 5 + val1*15;
			val3 = 250 - val1*50;
			if(sd) {
				// 被ディボーション者をディフェンダーにする
				struct map_session_data *tsd;
				int i;
				for(i = 0; i < 5; i++) {
					if(sd->dev.val1[i] && (tsd = map_id2sd(sd->dev.val1[i])) != NULL)
						status_change_start(&tsd->bl,type,val1,0,0,0,skill_get_time(CR_DEFENDER,val1),0);
				}
			}
			break;
		case SC_HALLUCINATION:
			if(sd && !battle_config.hallucianation_off) {
				// onなのでアイコン表示
				clif_status_change(bl, SI_HALLUCINATION, 1, icon_tick, 0, 0, 0);
			}
			break;
		case SC_TENSIONRELAX:	/* テンションリラックス */
			if(sd == NULL)
				return 0;
			tick = 10000;
			break;
		case SC_PARRYING:		/* パリイング */
			val2 = 20 + val1*3;
			break;
		case SC_JOINTBEAT:		/* ジョイントビート */
			calc_flag = 1;
			ud->state.change_speed = 1;
			val4 = atn_rand()%6;
			if(val4 == 5) {
				// 首は強制的に出血付加 ・ 使用者のレベルが取得できないのでとりあえず0を引数に
				if(atn_rand() % 10000 < status_change_rate(bl,SC_BLEED,10000,0))
					status_change_start(bl,SC_BLEED,val1,0,0,0,skill_get_time2(LK_JOINTBEAT,val1),10);
			}
			if(!(flag&2)) {
				tick = tick - (status_get_agi(bl)/10 + status_get_luk(bl)/4)*1000;
			}
			break;
		case SC_WINDWALK:		/* ウインドウォーク */
			calc_flag = 1;
			ud->state.change_speed = 1;
			val2 = val1 / 2;	// Flee上昇率
			break;
		case SC_BERSERK:		/* バーサーク */
			unit_heal(bl,0,-status_get_sp(bl),0,0);
			if(sd) {
				clif_status_change(bl,SI_INCREASEAGI,1,icon_tick, 0, 0, 0);	// アイコン表示
			}
			tick = 1000;
			calc_flag = 1;
			break;
		case SC_ASSUMPTIO:		/* アスムプティオ */
		case SC_ASSUMPTIO2:		/* キャッシュアスムプティオ */
			// キリエが掛かっていたら解除
			if(sc->data[SC_KYRIE].timer != -1)
				status_change_end(bl,SC_KYRIE,-1);
			// カイトが掛かっていたら解除
			if(sc->data[SC_KAITE].timer != -1)
				status_change_end(bl,SC_KAITE,-1);
			break;
		case SC_CARTBOOST:		/* カートブースト */
			calc_flag = 1;
			if(sc->data[SC_DECREASEAGI].timer != -1)
				status_change_end(bl,SC_DECREASEAGI,-1);
			break;
		case SC_REJECTSWORD:	/* リジェクトソード */
			val2 = 3; // 3回攻撃を跳ね返す
			break;
		case SC_MEMORIZE:		/* メモライズ */
			val2 = 5; // 5回詠唱を1/2にする
			break;
		case SC_GRAFFITI:		/* グラフィティ */
			{
				struct skill_unit_group *sg = skill_unitsetting(bl,RG_GRAFFITI,val1,val2,val3,0);
				if(sg)
					val4 = sg->bl.id;
			}
			break;
		case SC_OVERTHRUSTMAX:		/* オーバートラストマックス */
			if(sc->data[SC_OVERTHRUST].timer != -1)
				status_change_end(bl,SC_OVERTHRUST,-1);
			calc_flag = 1;
			break;

		case SC_MEAL_INCSTR:	// 食事用
		case SC_MEAL_INCAGI:
		case SC_MEAL_INCVIT:
		case SC_MEAL_INCINT:
		case SC_MEAL_INCDEX:
		case SC_MEAL_INCLUK:
			if(sc->data[type - SC_MEAL_INCSTR + SC_MEAL_INCSTR2].timer != -1) {
				// 効果が低い場合は効果なし
				if(val1 < sc->data[type - SC_MEAL_INCSTR + SC_MEAL_INCSTR2].val1)
					return 0;
				// 同等か高い効果なら使用中の効果を消す
				else
					status_change_end(bl, type - SC_MEAL_INCSTR + SC_MEAL_INCSTR2, -1);
			}
			calc_flag = 1;
			break;
		case SC_MEAL_INCSTR2:	// 課金料理用
		case SC_MEAL_INCAGI2:
		case SC_MEAL_INCVIT2:
		case SC_MEAL_INCINT2:
		case SC_MEAL_INCDEX2:
		case SC_MEAL_INCLUK2:
			if(sc->data[type - SC_MEAL_INCSTR2 + SC_MEAL_INCSTR].timer != -1) {
				// 効果が低い場合は効果なし
				if(val1 < sc->data[type - SC_MEAL_INCSTR2 + SC_MEAL_INCSTR].val1)
					return 0;
				// 同等か高い効果なら使用中の効果を消す
				else
					status_change_end(bl, type - SC_MEAL_INCSTR2 + SC_MEAL_INCSTR, -1);
			}
			calc_flag = 1;
			break;
		case SC_ELEMENTFIELD:		/* 属性場 */
			tick = val2;
			break;
		case SC_RUN:			/* タイリギ */
			val4 = 0;
			calc_flag = 1;
			break;
		case SC_KAUPE:			/* カウプ */
			val2 = val1*33;
			if(val1 >= 3)
				val2 = 100;
			break;
		case SC_KAITE:			/* カイト */
			// アスムが掛かっていたら解除して
			if(sc->data[SC_ASSUMPTIO].timer != -1)
				status_change_end(bl,SC_ASSUMPTIO,-1);
			if(sc->data[SC_ASSUMPTIO2].timer != -1)
				status_change_end(bl,SC_ASSUMPTIO2,-1);
			// 反射回数
			val2 = val1 / 5 + 1;
			break;
		case SC_SWOO:			/* エスウ */
			calc_flag = 1;
			ud->state.change_speed = 1;
			if(status_get_mode(bl)&MD_BOSS)
				tick /= 5;
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
		case SC_GUNNER:			/* ガンスリンガーの魂 */
		case SC_NINJA:			/* 忍者の魂 */
		case SC_DEATHKINGHT:		/* デスナイトの魂 */
		case SC_COLLECTOR:		/* コレクターの魂 */
			if(sd && battle_config.disp_job_soul_state_change)
				clif_disp_onlyself(sd->fd, msg_txt(206));	// 魂状態になりました
			break;
		case SC_KNIGHT:			/* ナイトの魂 */
		case SC_ALCHEMIST:		/* アルケミストの魂 */
		case SC_BARDDANCER:		/* バードとダンサーの魂 */
		case SC_BLACKSMITH:		/* ブラックスミスの魂 */
		case SC_HUNTER:			/* ハンターの魂 */
		case SC_HIGH:			/* 一次上位職業の魂 */
			if(sd && battle_config.disp_job_soul_state_change)
				clif_disp_onlyself(sd->fd, msg_txt(206));	// 魂状態になりました
			calc_flag = 1;
			break;
		case SC_SUPERNOVICE:		/* スーパーノービスの魂 */
			if(sd) {
				// 1%で死亡フラグ消す
				if(atn_rand()%10000 < battle_config.repeal_die_counter_rate) {
					sd->status.die_counter = 0;	// 死にカウンターリセット
					if(sd->status.job_level >= 70 || sd->s_class.job == PC_JOB_ESNV)
						clif_misceffect(&sd->bl,7);	// スパノビ天使
				}
				if(battle_config.disp_job_soul_state_change)
					clif_disp_onlyself(sd->fd, msg_txt(206));	// 魂状態になりました
			}
			calc_flag = 1;
			break;
		case SC_AUTOBERSERK:
			if( status_get_hp(bl) < status_get_max_hp(bl) >> 2 &&
			    (sc->data[SC_PROVOKE].timer == -1 || sc->data[SC_PROVOKE].val2 == 0) )
			{
				// オートバーサーク発動
				status_change_start(&sd->bl,SC_PROVOKE,10,1,0,0,0,0);
			}
			tick = 600*1000;
			break;
		case SC_READYSTORM:
		case SC_READYDOWN:
		case SC_READYTURN:
		case SC_READYCOUNTER:
			tick = 600*1000;
			break;
		case SC_UTSUSEMI:		/* 空蝉 */
			val3 = (val1+1)/2;
			break;
		case SC_BUNSINJYUTSU:		/* 分身の術 */
			val3 = (val1+1)/2;
			if(sd) {
				val4 = sd->status.clothes_color;
				pc_changelook(sd, LOOK_CLOTHES_COLOR, 0);
			}
			break;
		case SC_BOSSMAPINFO:		/* 凸面鏡 */
			if(map[bl->m].mvpboss == NULL) {
				if(sd) {
					// 居ないのでメッセージを出して終了
					clif_bossmapinfo(sd, "", 0, 0, 0, 0);
				}
				tick = 0;
			}
			break;
		case SC_STONEHARDSKIN:		/* ストーンハードスキン */
			{
				val3 = (int)((atn_bignumber)status_get_hp(bl) * 20 / 100);
				unit_heal(bl, -val3, 0, 0, 0);
			}
			break;
		case SC_MILLENNIUMSHIELD:	/* ミレニアムシールド */
			val2 = 2 + atn_rand()%3;
			val3 = 1000;
			if(sd)
				clif_mshield(sd, val2);
			break;
		case SC_FIGHTINGSPIRIT:		/* ファイティングスピリット */
			calc_flag = 1;
			val3 = (val3>9)? 4: (val3>7)? 3: (val3>4)? 2: (val3>2)? 1: 0;
			break;
		case SC_ABUNDANCE:			/* アバンダンス */
			val3 = tick / 10000;
			if(val3 < 1)
				val3 = 1;
			tick = 10000;
			break;
		case SC_DEATHBOUND:			/* デスバウンド */
			val2 = 500+val1*100;
			break;
		case SC_FEAR:				/* 恐怖 */
			calc_flag = 1;
			clif_emotion(bl,79);
			val3 = (tick < 2000) ? 2000: tick - 2000;
			tick = 2000;
			break;
		case SC_VENOMIMPRESS:		/* ベナムインプレス */
			val2 = val1 * 10;
			break;
		case SC_POISONINGWEAPON:	/* ポイズニングウェポン */
			val3 = 200 + val1 * 200;
			break;
		case SC_WEAPONBLOCKING:		/* ウェポンブロッキング */
			val2 = 10 + val1 * 2;
			val3 = tick / 5000;
			tick = 5000;
			break;
		case SC_CLOAKINGEXCEED:		/* クローキングエクシード */
			calc_flag = 1;
			val2 = (val1 + 1) / 2;	// ダメージ耐性
			tick = 1000;
			break;
		case SC_ROLLINGCUTTER:		/* ローリングカッター */
			icon_val1 = val1;	// val1(回転数)を渡してアイコン表示する
			break;
		case SC_TOXIN:				/* トキシン */
			val2 = tick / 10000;
			tick = 10000;
			break;
		case SC_VENOMBLEED:			/* ベナムブリード */
			calc_flag = 1;
			val2 = 15;
			break;
		case SC_MAGICMUSHROOM:		/* マジックマッシュルーム */
		case SC_OBLIVIONCURSE:		/* オブリビオンカース */
			val2 = tick / 2000;
			tick = 2000;
			break;
		case SC_DEATHHURT:			/* デスハート */
			val2 = 20;
			break;
		case SC_PYREXIA:			/* パイレックシア */
			val2 = tick / 3000;
			tick = 3000;
			break;
		case SC_LEECHEND:			/* リーチエンド */
			val2 = tick / 1000;
			tick = 1000;
			break;
		case SC_DARKCROW:			/* ダーククロー */
			val2 = val1 * 30;
			break;
		case SC_EPICLESIS:			/* エピクレシス */
			calc_flag = 1;
			val2 = val1 * 5;
			break;
		case SC_ORATIO:				/* オラティオ */
			val2 = val1 * 5;
			break;
		case SC_LAUDAAGNUS:			/* ラウダアグヌス */
		case SC_LAUDARAMUS:			/* ラウダラムス */
			calc_flag = 1;
			val2 = val1 + 4;
			break;
		case SC_RENOVATIO:			/* レノヴァティオ */
			val2 = val1 * 2 + 1;
			val3 = tick / 5000;
			tick = 5000;
			break;
		case SC_EXPIATIO:			/* エクスピアティオ */
			val2 = val1 * 20;
			break;
		case SC_DUPLELIGHT:			/* デュプレライト */
			val2 = 10 + val1 * 2;	// 物理攻撃発生確率
			val3 = 10 + val1 * 2;	// 魔法攻撃発生確率
			break;
		case SC_SACRAMENT:			/* サクラメント */
			val2 = val1 * 10;
			break;
		case SC_MARSHOFABYSS:		/* マーシュオブアビス */
			calc_flag = 1;
			ud->state.change_speed = 1;
			val2 = val1 * 10;	// 移動速度減少率
			val3 = val1 * 6;	// AGI/DEX減少率
			break;
		case SC_SUMMONBALL1:		/* サモンボール(1個目) */
		case SC_SUMMONBALL2:		/* サモンボール(2個目) */
		case SC_SUMMONBALL3:		/* サモンボール(3個目) */
		case SC_SUMMONBALL4:		/* サモンボール(4個目) */
		case SC_SUMMONBALL5:		/* サモンボール(5個目) */
			icon_val1 = val2;	// val2(属性の種類)を渡してアイコン表示する
			val3 = tick / 1000;
			tick = 1000;
			break;
		case SC_HELLINFERNO:		/* ヘルインフェルノ */
			calc_flag = 1;
			val2 = tick / 1000;
			val3 = 0;
			tick = 1000;
			break;
		case SC_TELEKINESIS_INTENSE:	/* テレキネシスインテンス */
			val2 = val1 * 40;	// 増加率
			val3 = val1 * 10;	// 消費SP軽減率
			break;
		case SC_ELECTRICSHOCKER:	/* エレクトリックショッカー */
			val2 = tick / 1000;
			tick = 1000;
			break;
		case SC_CAMOUFLAGE:			/* カモフラージュ */
			calc_flag = 1;
			ud->state.change_speed = 1;
			val2 = 0;			// 1秒ごとの強化値
			tick = 1000;
			break;
		case SC_UNLIMIT:			/* アンリミット */
			calc_flag = 1;
			val2 = val1 * 50;	// 増加率
			break;
		case SC_OVERHEAT_LIMITPOINT:	/* オーバーヒート加熱値 */
		case SC_OVERHEAT:				/* オーバーヒート */
			icon_val1 = val1;
			break;
		case SC_SHAPESHIFT:			/* シェイプシフト */
			switch(val1) {
				case 1:  val2 = ELE_FIRE;  break;
				case 2:  val2 = ELE_EARTH; break;
				case 3:  val2 = ELE_WIND;  break;
				default: val2 = ELE_WATER; break;
			}
			break;
		case SC_MAGNETICFIELD:		/* マグネティックフィールド */
			val2 = tick / 1000;
			tick = 1000;
			break;
		case SC_STEALTHFIELD_MASTER:	/* ステルスフィールド(使用者) */
			val3 = 1000 * (val1 + 2);
			val2 = tick / val3;
			tick = val3;
			calc_flag = 1;
			ud->state.change_speed = 1;
			break;
		case SC__REPRODUCE:		/* リプロデュース */
			tick = 1000;
			break;
		case SC__AUTOSHADOWSPELL:	/* シャドウオートスペル */
			val4 = 30 - ((val1%2)? 2: 0) - ((val1+1)/2) * 2;		// 発動確率
			val4 = (val4 < 1)? 1: val4;
			break;
		case SC__SHADOWFORM:		/* シャドウフォーム */
			val3 = 4 + val1;	// 残り回数
			val4 = tick / 1000;
			tick = 1000;
			break;
		case SC__INVISIBILITY:		/* インビジビリティ */
			if(sd) {
				tick = 1000;
				calc_flag = 1;
			} else {
				tick = 5000*val1;
			}
			break;
		case SC_REFLECTDAMAGE:		/* リフレクトダメージ */
			// リフレクトシールドが掛かっていたら解除
			if(sc->data[SC_REFLECTSHIELD].timer != -1)
				status_change_end(bl,SC_REFLECTSHIELD,-1);
			val2 = tick / 10000;
			val3 = val1 * 5 + 15;	// 反射率
			val4 = val1 * 5 + 25;	// 反射回数
			tick = 10000;
			break;
		case SC_FORCEOFVANGUARD:	/* フォースオブバンガード */
			val2 = tick / 10000;
			val3 = val1 * 12 + 8;	// 怒りカウンター発動率
			tick = 10000;
			icon_tick = -1;
			calc_flag = 1;
			break;
		case SC_SHIELDSPELL_DEF:	/* シールドスペル(DEF) */
		case SC_SHIELDSPELL_MDEF:	/* シールドスペル(MDEF) */
		case SC_SHIELDSPELL_REF:	/* シールドスペル(精錬) */
			if(sc->data[SC_SHIELDSPELL_DEF].timer != -1)
				status_change_end(bl,SC_SHIELDSPELL_DEF,-1);
			if(sc->data[SC_SHIELDSPELL_MDEF].timer != -1)
				status_change_end(bl,SC_SHIELDSPELL_MDEF,-1);
			if(sc->data[SC_SHIELDSPELL_REF].timer != -1)
				status_change_end(bl,SC_SHIELDSPELL_REF,-1);
			calc_flag = 1;
			break;
		case SC_EXEEDBREAK:			/* イクシードブレイク */
			if(sd) {
				int idx = sd->equip_index[EQUIP_INDEX_RARM];
				val2 = 100 + val1 * 150 + sd->status.job_level * 15;
				if(idx >= 0 && sd->inventory_data[idx])
					val2 += sd->inventory_data[idx]->weight/10 * sd->inventory_data[idx]->wlv * sd->status.base_level / 100;
			}
			else {
				val2 = val1 * 150;
			}
			tick = 600*1000;
			break;
		case SC_PRESTIGE:	/* プレスティージ */
			val2 = val1 * 15 * status_get_lv(bl) / 100;		// Def増加値
			if(sd) {
				val2 += pc_checkskill(sd,CR_DEFENDER) / 5 * status_get_lv(bl) / 2;
			}
			val3 = (1 + status_get_agi(bl) / 20 + status_get_luk(bl) / 40) * val1 / 2;		// 魔法回避率
			calc_flag = 1;
			break;
		case SC_BANDING:	/* バンディング */
			tick = 5000;
			icon_tick = 9999;
			calc_flag = 1;
			break;
		case SC_SITDOWN_FORCE:		/* 転倒 */
			if(sd){
				pc_setsit(sd);
				clif_sitting(&sd->bl, 1);
			}
			break;
		case SC_INSPIRATION:	/* インスピレーション */
			val2 = tick / 6000;
			tick = 6000;
			calc_flag = 1;
			break;
		case SC_KINGS_GRACE:	/* キングスグレイス */
			status_change_end(bl,SC_POISON,-1);
			status_change_end(bl,SC_BLIND,-1);
			status_change_end(bl,SC_FREEZE,-1);
			status_change_end(bl,SC_STONE,-1);
			status_change_end(bl,SC_STUN,-1);
			status_change_end(bl,SC_SLEEP,-1);
			status_change_end(bl,SC_BLEED,-1);
			status_change_end(bl,SC_CURSE,-1);
			status_change_end(bl,SC_CONFUSION,-1);
			status_change_end(bl,SC_SILENCE,-1);
			status_change_end(bl,SC_DPOISON,-1);
			status_change_end(bl,SC_HALLUCINATION,-1);
			status_change_end(bl,SC_FEAR,-1);
			status_change_end(bl,SC_HELLINFERNO,-1);
			status_change_end(bl,SC_FROSTMISTY,-1);
			status_change_end(bl,SC_DEEP_SLEEP,-1);
			status_change_end(bl,SC_DIAMONDDUST,-1);
			status_change_end(bl,SC_MANDRAGORA,-1);
			status_change_end(bl,SC_DEVOTION,-1);
			unit_stopattack(bl);
			unit_stop_walking(bl,0);
			val2 = tick / 1000;
			val4 = 3 + val1;
			tick = 1000;
			break;
		case SC_CRESCENTELBOW:		/* 破碎柱 */
			val2 = 40 + val1 * 5 + status_get_jlv(bl) / 2;		// 発動率
			break;
		case SC_LIGHTNINGWALK:		/* 閃電歩 */
			val2 = 40 + val1 * 5 + status_get_jlv(bl) / 2;		// 発動率
			break;
		case SC_RAISINGDRAGON:	/* 潜龍昇天 */
			val2 = tick / 5000;
			val3 = val1 + 2;	// MaxHP,MaxSP増加率
			tick = 5000;
			calc_flag = 1;
			break;
		case SC_GENTLETOUCH_ENERGYGAIN:	/* 点穴 -球- */
			// 点穴 -反-が掛かっていたら解除
			if(sc->data[SC_GENTLETOUCH_CHANGE].timer != -1)
				status_change_end(bl,SC_GENTLETOUCH_CHANGE,-1);
			// 点穴 -活-が掛かっていたら解除
			if(sc->data[SC_GENTLETOUCH_REVITALIZE].timer != -1)
				status_change_end(bl,SC_GENTLETOUCH_REVITALIZE,-1);
			val2 = val1 * 5 + 10;	// 気弾生成率
			break;
		case SC_GENTLETOUCH_CHANGE:	/* 点穴 -反- */
			// 点穴 -球-が掛かっていたら解除
			if(sc->data[SC_GENTLETOUCH_ENERGYGAIN].timer != -1)
				status_change_end(bl,SC_GENTLETOUCH_ENERGYGAIN,-1);
			// 点穴 -活-が掛かっていたら解除
			if(sc->data[SC_GENTLETOUCH_REVITALIZE].timer != -1)
				status_change_end(bl,SC_GENTLETOUCH_REVITALIZE,-1);
			val4 = status_get_agi(bl) / 15;		// ASPD上昇値
			calc_flag = 1;
			break;
		case SC_GENTLETOUCH_REVITALIZE:	/* 点穴 -活- */
			// 点穴 -球-が掛かっていたら解除
			if(sc->data[SC_GENTLETOUCH_ENERGYGAIN].timer != -1)
				status_change_end(bl,SC_GENTLETOUCH_ENERGYGAIN,-1);
			// 点穴 -反-が掛かっていたら解除
			if(sc->data[SC_GENTLETOUCH_CHANGE].timer != -1)
				status_change_end(bl,SC_GENTLETOUCH_CHANGE,-1);
			calc_flag = 1;
			break;
		case SC_SWING:				/* スイングダンス */
			val4 = (val1 * 5) + (val2 * 2 / 10);
			calc_flag = 1;
			ud->state.change_speed = 1;
			break;
		case SC_RUSH_WINDMILL:		/* 風車に向かって突撃 */
			val4 = (val1 * 6) + (val2 / 5) + val3;
			calc_flag = 1;
			break;
		case SC_MOONLIT_SERENADE:	/* 月明かりのセレナーデ */
			val4 = (val1 * 5) + (val2 / 4) + val3;
			calc_flag = 1;
			break;
		case SC_ECHOSONG:			/* エコーの歌 */
			calc_flag = 1;
			val4 = (val1 * 6) + (val2 / 4) + val3;
			break;
		case SC_SYMPHONY_LOVE:		/* 恋人たちの為のシンフォニー */
			calc_flag = 1;
			val4 = (val1 * 12) + (val2 / 4) + val3;
			break;
		case SC_WINKCHARM:	/* 魅惑のウィンク */
		case SC_SIREN:		/* セイレーンの声 */
			val3 = tick / 3000;
			tick = 3000;
			break;
		case SC_DEEP_SLEEP:		/* 安らぎの子守唄 */
			val2 = tick / 2000;
			tick = 2000;
			break;
		case SC_SIRCLEOFNATURE:		/* 循環する自然の音 */
			val2 = tick / 1000;
			tick = 1000;
			break;
		case SC_BEYOND_OF_WARCRY:	/* ビヨンドオブウォークライ */
			val3 = val1 * 4;
			val4 = val1;
			if(val2 >= 3 && val2 <= 7) {
				val3 += (val2-2) * 4;
				val4 += val2-2;
			}
			calc_flag = 1;
			break;
		case SC_MELODYOFSINK:		/* メロディーオブシンク */
			val3 = val1 * 2;
			val4 = val1;
			if(val2 >= 3 && val2 <= 7) {
				val3 += (val2-2) * 2;
				val4 += val2-2;
			}
			val2 = tick / 1000;
			tick = 1000;
			calc_flag = 1;
			break;
		case SC_SONG_OF_MANA:		/* マナの歌 */
			val2 = tick / 5000;
			tick = 5000;
			break;
		case SC_SATURDAY_NIGHT_FEVER:	/* フライデーナイトフィーバー */
			val3 = 12000 - val1 * 2000;
			val2 = tick / val3;
			tick = val3;
			calc_flag = 1;
			break;
		case SC_FRIGG_SONG:			/* フリッグの歌 */
			val2 = tick / 1000;
			val3 = val1 * 5;
			val4 = val1 * 20 + 80;
			calc_flag = 1;
			break;
		case SC_PROPERTYWALK:		/* ファイアー/エレクトリックウォーク */
			val3 = val1 * 2 + 6;	// 発生個数
			break;
		case SC_DIAMONDDUST:		/* ダイヤモンドダスト */
			val2 = tick / 1000;
			tick = 1000;
			break;
		case SC_SPELLFIST:		/* スペルフィスト */
			val4 = val1 * 7;	// 回数
			break;
		case SC_STRIKING:			/* ストライキング */
			val2 = tick / 1000;
			tick = 1000;
			calc_flag = 1;
			break;
		case SC_BLOOD_SUCKER:		/* ブラッドサッカー */
			val4 = tick / 1000;
			tick = 1000;	// ダメージ発生間隔
			break;
		case SC_FIRE_EXPANSION_SMOKE_POWDER:	/* ファイアーエクスパンション(煙幕) */
			val2 = 25;		// 近距離・遠距離ダメージ減少率
			val3 = 25;		// Flee上昇率
			calc_flag = 1;
			break;
		case SC_FIRE_EXPANSION_TEAR_GAS:	/* ファイアーエクスパンション(催涙ガス) */
			val2 = 25;		// Hit,Flee減少率
			val3 = tick / 3000;
			tick = 3000;
			calc_flag = 1;
			break;
		case SC_MANDRAGORA:			/* ハウリングオブマンドラゴラ */
			val2 = val1 * 5 + 5;		// Int減少値
			val3 = 3000;		// 固定詠唱増加値
			calc_flag = 1;
			break;
		case SC_BANANA_BOMB:		/* バナナ爆弾 */
			if(sd){
				pc_setsit(sd);
				clif_sitting(&sd->bl, 1);
			}
			calc_flag = 1;
			break;
		case SC_MEIKYOUSISUI:		/* 明鏡止水 */
			val2 = tick / 1000;
			tick = 1000;
			calc_flag = 1;
			break;
		case SC_IZAYOI:			/* 十六夜 */
			if(sd) {
				val2 = sd->status.job_level/2 * val1;
			} else {
				val2 = 50 * val1;
			}
			val3 = tick / 1000;
			tick = 1000;
			calc_flag = 1;
			break;
		case SC_KAGEMUSYA:		/* 幻術 -分身- */
			val2 = 20;		// ダメージ増加率
			val3 = tick / 1000;
			tick = 1000;
			calc_flag = 1;
			break;
		case SC_ZANGETSU:		/* 幻術 -残月- */
			if(status_get_hp(bl)%2 == 0)
				val2 += status_get_lv(bl) / 3 + val1 * 20; 	// HPが偶数の場合
			else
				val2 -= status_get_lv(bl) / 3 + val1 * 30; 	// HPが奇数の場合
			if(status_get_sp(bl)%2 == 0)
				val3 += status_get_lv(bl) / 3 + val1 * 20; 	// SPが偶数の場合
			else
				val3 -= status_get_lv(bl) / 3 + val1 * 30; 	// SPが奇数の場合
			calc_flag = 1;
			break;
		case SC_GENSOU:		/* 幻術 -朧幻想- */
			val2 = val1 * 10; 	// ダメージ反射率
			break;
		case SC_C_MARKER:		/* クリムゾンマーカー */
			if(val3 < 0 || val3 >= 3)
				return 0;
			val4 = tick/1000;
			tick = 1000;
			calc_flag = 1;
			break;
		case SC_B_TRAP:			/* バインドトラップ */
			val3 = val1 * 25;
			ud->state.change_speed = 1;
			break;
		case SC_HEAT_BARREL:		/* ヒートバレル */
			val2 = val4 * 5;		// fixcast
			val3 = (6 + val1 * 2) * val4; // atk
			val4 = 25 + val1 * 5; // hit
			calc_flag = 1;
			break;
		case SC_P_ALTER:		/* プラチナムアルター */
			if(sd) {
				int idx = sd->equip_index[EQUIP_INDEX_ARROW];
				if(idx >= 0 && sd->inventory_data[idx] &&
					(sd->inventory_data[idx]->nameid == 13220 ||		// サンクタファイドバレット
					sd->inventory_data[idx]->nameid == 13221)		// シルバーバレットC
				)
					val2 = 10 + 10 * val4; // atk
			}
			else
				val2 = 10 + 10 * val4; // atk
			val3 = (int)((atn_bignumber)status_get_max_hp(bl) * (val1 * 5) / 100);	// 耐久度
			val4 = val1 + 3;	// 回数
			break;
		case SC_ANTI_M_BLAST:
			val2 = 15 + val1 * 2;
			break;
		case SC_SUHIDE:				/* かくれる */
			tick = 60 * 1000;
			break;
		case SC_ARCLOUSEDASH:		/* アクラウスダッシュ */
			val2 = 3 + ((val1-1) / 2) * 6;	// AGI増加
			val3 = 5 + (val1/2) * 5;	// 遠距離攻撃増加
			ud->state.change_speed = 1;
			calc_flag = 1;
			break;
		case SC_SHRIMP:		/* エビ三昧 */
			if(val2 >= 5)	// WATK/MATK増加
				val3 = 30;
			else if(val2 == 1)
				val3 = 5;
			else
				val3 = (val2 - 1) * 5;
			calc_flag = 1;
			break;
		case SC_FRESHSHRIMP:		/* 新鮮なエビ */
			val3 = 13000 - 2000 * val1;
			val2 = tick / val3;
			tick = val3;
			break;
		case SC_CHATTERING:			/* チャタリング */
			if(val1 >= 5)	// ATK/MATK増加
				val2 = 150;
			else if(val1 == 4)
				val2 = 100;
			else
				val2 = 10 + val1 * 20;
			val3 = (val1>=5)? 35: 25;	// 移動速度増加
			ud->state.change_speed = 1;
			calc_flag = 1;
			break;
		case SC_HISS:				/* 警戒 */
			val4 = tick / 1000;
			tick = 1000;
			ud->state.change_speed = 1;
			calc_flag = 1;
			break;
		case SC_GROOMING:			/* グルーミング */
			val2 = val1 * 10;	// Flee増加
			calc_flag = 1;
			break;
		case SC_SV_ROOTTWIST:	/* マタタビの根っこ */
			val3 = tick / 1000;
			tick = 1000;
			break;
		case SC_CATNIPPOWDER:		/* イヌハッカシャワー */
			val2 = 30;	// 武器攻撃力とMatk減少
			val3 = 50;	// HP・SP自然回復量増加
			calc_flag = 1;
			break;
		case SC_BURNT:			/* 獄炎呪 */
			val3 = tick / 1000;
			tick = 1000;
			calc_flag = 1;
			break;
		case SC_CHILL:			/* 永久霜 */
			status_change_end(bl,SC_BURNT,-1);
			break;
		case SC_MER_FLEE:		/* 傭兵ボーナス(FLEE) */
		case SC_MER_ATK:		/* 傭兵ボーナス(ATK) */
		case SC_MER_HIT:		/* 傭兵ボーナス(HIT) */
			val2 = val1 * 15;
			calc_flag = 1;
			break;
		case SC_MER_HP:			/* 傭兵ボーナス(HP) */
		case SC_MER_SP:			/* 傭兵ボーナス(SP) */
			val2 = val1 * 5;
			calc_flag = 1;
			break;
		case SC_ON_PUSH_CART:	/* カート */
			icon_val1 = val1;	// カートタイプを渡す
			ud->state.change_speed = 1;
			calc_flag = 1;
			if(sd && val2) {
				clif_cart_itemlist(sd);
				clif_cart_equiplist(sd);
				clif_updatestatus(sd,SP_CARTINFO);
			}
			val2 = 1;
			break;
		case SC_SUMMON_ELEM:	/* サモンエレメンタル */
			val2 = tick / 10000;
			tick = 10000;
			val3 = val1 * 3 + 2;		// SP消費量
			break;
		case SC_FIRE_CLOAK:		/* ファイアークローク */
		case SC_WATER_DROP:		/* ウォータードロップ */
		case SC_WIND_CURTAIN:	/* ウィンドカーテン */
		case SC_STONE_SHIELD:	/* ストーンシールド */
			val2 = 100;		// 属性耐性増加値
			val3 = 100;		// 属性耐性減少値
			calc_flag = 1;
			break;
		case SC_WATER_SCREEN:	/* ウォータースクリーン */
			val2 = tick / 5000;
			tick = 5000;
			break;
		case SC_WIND_STEP:			/* ウィンドステップ */
			val2 = 10;	// Flee増加値
			val3 = 50;	// 移動速度増加率
			calc_flag = 1;
			ud->state.change_speed = 1;
			break;
		case SC_SOLID_SKIN:			/* ソリッドスキン */
			val2 = 10;	// Def増加率
			val3 = 25;	// MaxHP増加率
			calc_flag = 1;
			break;
		case SC_PYROTECHNIC:	/* パイロテクニック */
			val2 = 40;	// Atk増加値
			val3 = 10;	// ダメージ増加率
			calc_flag = 1;
			break;
		case SC_HEATER:	/* ヒーター */
			val2 = 80;	// Atk増加値
			val3 = 20;	// ダメージ増加率
			calc_flag = 1;
			break;
		case SC_TROPIC:	/* トロピック */
			val2 = 120;	// Atk増加値
			calc_flag = 1;
			break;
		case SC_AQUAPLAY:	/* アクアプレイ */
			val2 = 40;	// Matk増加値
			val3 = 10;	// ダメージ増加率
			calc_flag = 1;
			break;
		case SC_COOLER:	/* クーラー */
			val2 = 80;	// Matk増加値
			val3 = 20;	// ダメージ増加率
			calc_flag = 1;
			break;
		case SC_CHILLY_AIR:	/* クールエアー */
			val2 = 120;	// Matk増加値
			calc_flag = 1;
			break;
		case SC_GUST:	/* ガスト */
			val2 = 50;	// Aspd増加値
			val3 = 10;	// ダメージ増加率
			calc_flag = 1;
			break;
		case SC_BLAST:	/* ブラスト */
			val2 = 50;	// Aspd増加値
			val3 = 10;	// ダメージ増加率
			calc_flag = 1;
			break;
		case SC_WILD_STORM:	/* ワイルドストーム */
			val2 = 50;	// Aspd増加値
			calc_flag = 1;
			break;
		case SC_PETROLOGY:	/* ペトロジー */
			val2 = 5;	// MaxHP増加率
			val3 = 10;	// ダメージ増加率
			calc_flag = 1;
			break;
		case SC_CURSED_SOIL:	/* カースドソイル */
			val2 = 10;	// MaxHP増加率
			val3 = 20;	// ダメージ増加率
			calc_flag = 1;
			break;
		case SC_UPHEAVAL:	/* アップヘイバル */
			val2 = 15;	// MaxHP増加率
			calc_flag = 1;
			break;
		case SC_TIDAL_WEAPON_OPTION:	/* タイダルウェポン(精霊) */
			val2 = 20;	// Atk増加率
			calc_flag = 1;
			break;
		case SC_CIRCLE_OF_FIRE_OPTION:	/* サークルオブファイア(精霊) */
		case SC_FIRE_CLOAK_OPTION:		/* ファイアークローク(精霊) */
		case SC_WATER_SCREEN_OPTION:	/* ウォータースクリーン(精霊) */
		case SC_WATER_DROP_OPTION:		/* ウォータードロップ(精霊) */
		case SC_WIND_STEP_OPTION:		/* ウィンドステップ(精霊) */
		case SC_WIND_CURTAIN_OPTION:	/* ウィンドカーテン(精霊) */
		case SC_SOLID_SKIN_OPTION:		/* ソリッドスキン(精霊) */
		case SC_STONE_SHIELD_OPTION:	/* ストーンシールド(精霊) */
			val2 = tick / 1000;
			tick = 1000;
			val3 = 5;		// SP消費量
			break;
		case SC_PYROTECHNIC_OPTION:	/* パイロテクニック(精霊) */
		case SC_AQUAPLAY_OPTION:	/* アクアプレイ(精霊) */
		case SC_GUST_OPTION:		/* ガスト(精霊) */
		case SC_PETROLOGY_OPTION:	/* ペトロジー(精霊) */
			val2 = tick / 10000;
			tick = 10000;
			val3 = 10;		// SP消費量
			break;
		case SC_HEATER_OPTION:		/* ヒーター(精霊) */
		case SC_COOLER_OPTION:		/* クーラー(精霊) */
		case SC_BLAST_OPTION:		/* ブラスト(精霊) */
		case SC_CURSED_SOIL_OPTION:	/* カースドソイル(精霊) */
			val2 = tick / 10000;
			tick = 10000;
			val3 = 20;		// SP消費量
			break;
		case SC_TROPIC_OPTION:		/* トロピック(精霊) */
		case SC_CHILLY_AIR_OPTION:	/* クールエアー(精霊) */
		case SC_WILD_STORM_OPTION:	/* ワイルドストーム(精霊) */
		case SC_UPHEAVAL_OPTION:	/* アップヘイバル(精霊) */
			val2 = tick / 10000;
			tick = 10000;
			val3 = 30;		// SP消費量
			break;
		case SC_PARALYZE:			/* 麻痺 */
			val2 = 1000;		// 強制詠唱時間(ms)
			val3 = val1 * 5;	// Def, Mdef減少率
			break;
		case SC_PAIN_KILLER:		/* ペインキラー */
			val4 = val1 * 100;	// ダメージ減少率
			val4 = val4 * val2 / 100 * val3 / 150;
			calc_flag = 1;
			break;
		case SC_LIGHT_OF_REGENE:	/* 再生の光 */
			val2 = 20 * val1;
			break;
		case SC_OVERED_BOOST:		/* オーバードブースト */
			val3 = 300 + val1 * 40;	// Flee固定値
			val4 = 410 - val1 * 40;	// Aspd固定値
			calc_flag = 1;
			break;
		case SC_ANGRIFFS_MODUS:		/* アングリフスモドス */
			val2 = tick / 1000;
			val3 = 30 + val1 * 20;	// Def減少値
			val4 = 40 + val1 * 20;	// Flee減少値
			tick = 1000;
			calc_flag = 1;
			break;
		case SC_GOLDENE_FERSE:		/* ゴールデンペルジェ */
			val2 = 10 + val1 * 10;	// Flee上昇値
			val3 = 6 + val1 * 4;	// Aspd上昇率
			val4 = 25;			// 聖属性追加ダメージ
			calc_flag = 1;
			break;
		case SC_CBC:		/* 絞め技 */
			val2 = tick / 1000;
			tick = 1000;
			calc_flag = 1;
			break;
		case SC_EQC:				/* E.Q.C */
			val3 = 2 * val1;	// MaxHP減少率
			val4 = 5 * val1;	// Atk、Def減少率
			calc_flag = 1;
			break;
		case SC_MAGMA_FLOW:		/* マグマフロー */
			val2 = 3 * val1;	// 発動率
			break;
		case SC_GRANITIC_ARMOR:	/* グラニティックアーマー */
			val2 = 2 * val1;	// ダメージ減少率
			if(val1 >= 4)	// 消費HP率
				val3 = (val1 - 2) * 5;
			else if(val1 >= 2)
				val3 = (val1 - 1) * 3;
			else
				val3 = 1;
			break;
		case SC_PYROCLASTIC:	/* パイロクラスティック */
			val2 = 10 * val1 + val4;	// 追加Atk
			val3 = 2 * val1;	// HF率
			calc_flag = 1;
			break;
		case SC_VOLCANIC_ASH:	/* 火山灰 */
			val2 = val3 = val4 = 0;
			if(bl->type == BL_PC || bl->type == BL_MOB)
				val2 = 50;	// 全対象
			if(bl->type == BL_MOB) {
				if(status_get_race(bl) == RCT_PLANT)
					val3 = 50;	// 対植物Mob
				if((status_get_element(bl)%20) == ELE_WATER)
					val4 = 50;	// 対水属性Mob
			}
			calc_flag = 1;
			break;
		case SC_FULL_THROTTLE:	/* フルスロットル */
			val2 = 20;
			val3 = tick / 1000;
			tick = 1000;
			calc_flag = 1;
			ud->state.change_speed = 1;
			break;
		case SC_REBOUND:	/* リバウンド */
			val2 = tick / 2000;
			tick = 2000;
			calc_flag = 1;
			ud->state.change_speed = 1;
			break;
		case SC_DAMAGE_HEAL:
			switch( val1 ) {
			case 1:
				val2 = BF_WEAPON;
				break;
			case 2:
				val2 = BF_MAGIC;
				break;
			case 3:
				val2 = BF_MISC;
				break;
			}
			break;
		case SC_GRADUAL_GRAVITY:	/* 重力増加 */
		case SC_KILLING_AURA:	/* キリングオーラ */
			val3 = tick / 1000;
			tick = 1000;
			break;
		case SC_LUNARSTANCE:	/* 月の構え */
			tick = 600*1000;
			calc_flag = 1;
			val2 = val1 * 10 - 5;
			break;
		case SC_UNIVERSESTANCE:	/* 宇宙の構え */
		case SC_SUNSTANCE:	/* 太陽の構え */
		case SC_STARSTANCE:	/* 星の構え */
			tick = 600*1000;
			calc_flag = 1;
			val2 = val1 * 5;
			break;
		case SC_LIGHTOFMOON:	/* 月の光 */
		case SC_LIGHTOFSUN:	/* 太陽の光 */
		case SC_LIGHTOFSTAR:	/* 星の光 */
			val2 = 5 * val1 + 25;
			break;
		case SC_FLASHKICK:	/* 閃光脚 */
		case SC_NOVAEXPLOSING:	/* 新星爆発 */
		case SC_GRAVITYCONTROL:	/* 重力調節 */
		case SC_CREATINGSTAR:	/* 創星の書 */
		case SC_DIMENSION:	/* 次元の書 */
		case SC_DIMENSION1:	/* 次元の書(新星爆発) */
			break;
		case SC_NEWMOON:		/* 朔月脚 */
			val2 = 15;	// ダメージ耐性
			val3 = tick / 1000;
			tick = 1000;
			break;
		case SC_FALLINGSTAR:	/* 流星落下 */
			val2 = val1 <= 5 ? 20 : 25;
			break;
		case SC_DIMENSION2:	/* 次元の書(星帝降臨) */
			val2 = 2;		// 盾の個数
			val3 = val4;	// 盾の耐久値
			if(sd)
				clif_mshield(sd, val2);
			break;
		case SC_SOULCOLLECT:		/* 魂の蓄積 */
			val2 = tick;		// ソウルエナジー獲得時間
			icon_tick = -1;
			break;
		case SC_SOULREAPER:			/* 魂の収穫 */
			val2 = val1;		// ソウルエナジー獲得率
			break;
		case SC_SOULUNITY:		/* 魂の連結 */
			{
				int i, add = 600;
				for(i = 0; i < val1; i++) {
					add += 100;
					val2 = val2 + add;		// HP回復量
				}
				val3 = tick / 3000;
				tick = 3000;
			}
			break;
		case SC_SOULSHADOW:		/* 影の魂 */
			val2 = 70;				// Cri増加値
			val3 = (val1+1)/2 * 10;	// Aspd増加値
			calc_flag = 1;
			break;
		case SC_SOULFAIRY:		/* 妖精の魂 */
			val2 = 50;				// 装備Matk増加値
			val3 = 25 + val1 * 5;	// 詠唱時間減少率
			calc_flag = 1;
			break;
		case SC_SOULFALCON:		/* 鷹の魂 */
			val2 = 50;				// 装備Atk増加値
			val3 = 25 + val1 * 25;	// Hit増加値
			calc_flag = 1;
			break;
		case SC_SOULGOLEM:		/* ゴーレムの魂 */
			val2 = 100;				// 装備Def増加値
			val3 = val1 * 10;		// 装備Mdef増加値
			calc_flag = 1;
			break;
		case SC_SOULDIVISION:	/* 魂の分裂 */
			val2 = 100;				// ディレイ増加率
			break;
		case SC_SHA:			/* エスハ */
			val2 = 50;				// 移動速度低下率
			ud->state.change_speed = 1;
			break;
		case SC_HELPANGEL:		/* 天使さま助けて */
			val2 = tick / 1000;
			tick = 1000;
			break;
		case SC_HANDICAPSTATE_DEEPBLIND:		/* 漆黒 */
			calc_flag = 1;
			icon_tick = tick -= status_get_sta(bl) * 100;
			break;
		case SC_HANDICAPSTATE_DEEPSILENCE:		/* 静寂 */
			val2 = 500;		// ASPD減少値
			calc_flag = 1;
			icon_tick = tick -= status_get_spl(bl) * 100;
			break;
		case SC_HANDICAPSTATE_LASSITUDE:		/* 無気力 */
			calc_flag = 1;
			ud->state.change_speed = 1;
			icon_tick = tick -= status_get_pow(bl) * 100;
			break;
		case SC_HANDICAPSTATE_FROSTBITE:		/* 急冷 */
			val2 = 50;		// Def/Mdef減少率
			calc_flag = 1;
			icon_tick = tick -= status_get_crt(bl) * 100;
			break;
		case SC_HANDICAPSTATE_SWOONING:			/* 失神 */
			icon_tick = tick -= status_get_sta(bl) * 100;
			break;
		case SC_HANDICAPSTATE_LIGHTNINGSTRIKE:	/* 激流 */
			val2 = 25;		// 地属性ダメージ増加率
			icon_tick = tick -= status_get_wis(bl) * 100;
			break;
		case SC_HANDICAPSTATE_CRYSTALLIZATION:	/* 結晶化 */
			calc_flag = 1;
			icon_tick = tick -= status_get_crt(bl) * 100;
			break;
		case SC_HANDICAPSTATE_CONFLAGRATION:	/* 火災 */
			icon_tick = tick -= status_get_spl(bl) * 100;
			val2 = tick / 3000;
			tick = 3000;
			break;
		case SC_HANDICAPSTATE_MISFORTUNE:		/* 不幸 */
			calc_flag = 1;
			icon_tick = tick -= status_get_crt(bl) * 100;
			break;
		case SC_HANDICAPSTATE_DEADLYPOISON:		/* 強毒 */
			val2 = 25;		// 毒属性ダメージ増加率
			calc_flag = 1;
			icon_tick = tick -= status_get_sta(bl) * 100;
			val3 = tick / 1000;
			tick = 1000;
			break;
		case SC_HANDICAPSTATE_DEPRESSION:		/* 憂鬱 */
			icon_tick = tick -= status_get_wis(bl) * 100;
			val2 = tick / 3000;
			tick = 3000;
			break;
		case SC_SERVANTWEAPON:		/* サーヴァントウェポン */
			val2 = 10 * val1;		// 武器体攻撃発動率
			val3 = skill_get_time2(DK_SERVANTWEAPON,val1);	// 武器体生成時間
			val3 = (val3 < 100)? 100: val3;
			val4 = tick / val3;
			tick = val3;
			if(sd)
				pc_addball(sd,600000,MAX_BALL);
			break;
		case SC_CHARGINGPIERCE_COUNT:		/* チャージングスピア(回数) */
			icon_val1 = val1;	// val1(回数)を渡してアイコン表示する
			break;
		case SC_CLIMAX_DES_HU:	/* クライマックスハリケーン */
			val2 = 200;			// Matk増加値
			val3 = 50;			// 風属性ダメージ増加率
			calc_flag = 1;
			break;
		case SC_CLIMAX:			/* クライマックス */
			icon_val1 = val1;	// val1(使用レベル)を渡してアイコン表示する
			break;
		case SC_CLIMAX_EARTH:	/* クライマックスクエイク */
			val2 = 50;			// 地属性ダメージ増加率
			break;
		case SC_CLIMAX_BLOOM:	/* クライマックスブルーム */
			val2 = 50;			// 火属性ダメージ増加率
			break;
		case SC_CLIMAX_CRYIMP:	/* クライマックスインパクト */
			val2 = 300;			// Def増加値
			val3 = 50;			// Mdef増加値
			val4 = 25;			// 水属性ダメージ減少率/水属性ダメージ増加率
			calc_flag = 1;
			break;
		case SC_POWERFUL_FAITH:		/* 強靭な信念 */
			val2 = 100;			// Atk増加値
			val3 = (val1 > 2)? 5*(val1-2): 1+2*(val1-1);	// P.Atk増加値
			calc_flag = 1;
			break;
		case SC_FIRM_FAITH:		/* 堅固な信念 */
			val2 = 10;			// MaxHP増加率
			val3 = (val1 > 2)? 10+30*(val1-2): 10*val1;		// Res増加値
			calc_flag = 1;
			break;
		case SC_SINCERE_FAITH:		/* 忠実な信念 */
			val2 = 10;			// Aspd増加値
			val3 = (val1 > 2)? 5*(val1-2): 1+2*(val1-1);	// 必中攻撃増加率
			calc_flag = 1;
			break;
		case SC_GUARD_STANCE:		/* ガードスタンス */
			val2 = (val1 > 4)? 60*val1: 50*val1;		// Def増加値
			val3 = 10*val1;		// Atk減少値
			calc_flag = 1;
			break;
		case SC_ATTACK_STANCE:		/* アタックスタンス */
			val2 = (val1 > 2)? 5*(val1-2): 1+2*(val1-1);	// P.Atk/S.Matk増加値
			val3 = 10*val1;		// Def減少値
			calc_flag = 1;
			break;
		case SC_HOLY_S:		/* ホーリーシールド */
			val2 = 5*val1;		// 聖属性魔法ダメージ増加率
			val3 = 3*val1;		// 闇/不死属性ダメージ減少率
			calc_flag = 1;
			break;
		case SC_MEDIALE:		/* メディアリボトゥム */
			//val2				// 効果範囲(スキル使用時に設定)
			val3 = skill_get_time2(CD_MEDIALE_VOTUM,val1);	// 回復間隔
			val3 = (val3 < 100)? 100: val3;
			val4 = tick / val3;
			tick = val3;
			skill_castend_nodamage_id(bl,bl,CD_MEDIALE_VOTUM,val1,tick,0x10|val2);
			break;
		case SC_A_VITA:			/* アルグトゥスヴィタ */
			val2 = 5*val1;		// Mres無視率
			break;
		case SC_A_TELUM:		/* アルグトゥステルム */
			val2 = 5*val1;		// Res無視率
			break;
		case SC_PRE_ACIES:		/* プレセンスアキエース */
			val2 = 5*val1;		// C.Rate増加値
			calc_flag = 1;
			break;
		case SC_COMPETENTIA:	/* コンペテンティア */
			val2 = 20+val1*2;	// P.Atk増加値
			val3 = 20+val1*2;	// S.Matk増加値
			calc_flag = 1;
			break;
		case SC_RELIGIO:		/* レリギオ */
			// サンドフェスティバルが掛かっていたら解除
			if(sc->data[SC_SANDY_FESTIVAL].timer != -1)
				status_change_end(bl,SC_SANDY_FESTIVAL,-1);
			val2 = val1*2;		// Sta増加値
			val3 = val1*2;		// Wis増加値
			val4 = val1*2;		// Spl増加値
			calc_flag = 1;
			break;
		case SC_BENEDICTUM:		/* ベネディクトゥム */
			// マリンフェスティバルが掛かっていたら解除
			if(sc->data[SC_MARINE_FESTIVAL].timer != -1)
				status_change_end(bl,SC_MARINE_FESTIVAL,-1);
			val2 = val1*2;		// Pow増加値
			val3 = val1*2;		// Con増加値
			val4 = val1*2;		// Crt増加値
			calc_flag = 1;
			break;
		case SC_DANCING_KNIFE:	/* ダンシングナイフ */
			val2 = skill_get_time2(SHC_DANCING_KNIFE,val1);	// 攻撃間隔
			val2 = (val2 < 100)? 100: val2;
			val3 = tick / val2;
			tick = val2;
			break;
		case SC_E_SLASH_COUNT:		/* エターナルカウンター */
			icon_val1 = val1;	// val1(回数)を渡してアイコン表示する
			break;
		case SC_POTENT_VENOM:		/* ポテントベナム */
			val2 = 20+val1;		// Res無視率
			break;
		case SC_SHADOW_WEAPON:		/* エンチャンティングシャドウ */
			val2 = val1;		// シャドウペイン付与率
			break;
		case SC_SHADOW_SCAR:		/* シャドウペイン */
			icon_val1 = val1;		// val1(回数)を渡してアイコン表示する
			val2 = val1 * 3;		// 近接ダメージ増加率
			break;
		case SC_RUSH_QUAKE1:		/* クエイク */
			val2 = 15;				// 物理ダメージ増加率
			break;
		case SC_RUSH_QUAKE2:		/* ラッシュ */
			val2 = val1 * 2;		// 近接/遠距離ダメージ増加率
			calc_flag = 1;
			break;
		case SC_A_MACHINE:		/* 攻撃装置有効化 */
			val2 = skill_get_time2(MT_A_MACHINE,val1);	// 攻撃間隔
			val2 = (val2 < 100)? 100: val2;
			val3 = tick / val2;
			tick = val2;
			break;
		case SC_D_MACHINE:		/* 防御装置有効化 */
			val2 = 300;			// Def増加値
			val3 = ((val1 < 4)? 10+val1*10: (val1 == 4)? 60: 100);		// Res増加値
			calc_flag = 1;
			break;
		case SC_SHADOW_STRIP:	/* ストリップシャドウ */
			val2 = 50;			// Res/Mres減少値
			calc_flag = 1;
			break;
		case SC_ABYSS_SLAYER:	/* アビススレイヤー */
			val2 = val1 * 2;		// P.Atk/S.Matk増加値
			val3 = (val1+1)/2 * 50;	// Hit増加値
			calc_flag = 1;
			break;
		case SC_ABYSSFORCEWEAPON:		/* フロムジアビス */
			val2 = 10 * val1;		// アビス球体攻撃発動率
			val3 = skill_get_time2(ABC_FROM_THE_ABYSS,val1);	// アビス球体生成時間
			val3 = (val3 < 100)? 100: val3;
			val4 = tick / val3;
			tick = val3;
			if(sd)
				pc_addball(sd,600000,MAX_BALL);
			break;
		case SC_WINDSIGN:	/* ウィンドサイン */
			val2 = 50 + val1 * 10;		// AP回復確率
			break;
		case SC_BO_HELL_DUSTY:		/* ヘルダスティ */
			val2 = 20;		// 無・植物形ダメージ増加率
			val3 = 20;		// 遠距離ダメージ増加率
			calc_flag = 1;
			break;
		case SC_MYSTIC_SYMPHONY:	/* ミスティックシンフォニー */
			val2 = 50;		// ダメージ増加率
			calc_flag = 1;
			break;
		case SC_SOUNDBLEND:			/* サウンドブレンド */
			tick = tick - 200;
			break;
		case SC_GEF_NOCTURN:		/* ゲフェニアノクターン */
			val3 = 10 * val1;
			if(val2 > 1) {		// パートナーが居る場合
				val3 = val3 * 15 / 10;
			}
			calc_flag = 1;
			break;
		case SC_AIN_RHAPSODY:		/* 鉱員のラプソディ */
			val3 = 10 * val1;
			if(val2 > 1) {		// パートナーが居る場合
				val3 = val3 * 15 / 10;
			}
			calc_flag = 1;
			break;
		case SC_MUSICAL_INTERLUDE:	/* ミュージカルインタールード */
			val3 = ((val1 < 4)? 10+val1*10: (val1 == 4)? 60: 100);		// Res増加値
			if(val2 > 1) {		// パートナーが居る場合
				val3 = val3 * 15 / 10;
			}
			calc_flag = 1;
			break;
		case SC_JAWAII_SERENADE:	/* 夕焼けのセレナーデ */
			val3 = 1 + ((val1 > 1)? 2: 0) + ((val1 > 2)? 2: 0) + ((val1 > 3)? 3: 0) + ((val1 > 4)? 4: 0);		// S.Matk増加値
			if(val2 > 1) {		// パートナーが居る場合
				val3 = val3 * 15 / 10;
			}
			val4 = 35;			// 移動ディレイ減少率
			calc_flag = 1;
			ud->state.change_speed = 1;
			break;
		case SC_PRON_MARCH:			/* プロンテラマーチ */
			val3 = 1 + ((val1 > 1)? 2: 0) + ((val1 > 2)? 2: 0) + ((val1 > 3)? 3: 0) + ((val1 > 4)? 4: 0);		// P.Atk増加値
			if(val2 > 1) {		// パートナーが居る場合
				val3 = val3 * 15 / 10;
			}
			val4 = 35;			// 移動ディレイ減少率
			calc_flag = 1;
			ud->state.change_speed = 1;
			break;
		case SC_SPELL_ENCHANTING:	/* スペルエンチャンティング */
			val2 = val1*5;	// S.Matk増加値
			calc_flag = 1;
			break;
		case SC_SUMMON_ELEMENTAL_ARDOR:			/* サモンアルドール */
		case SC_SUMMON_ELEMENTAL_DILUVIO:		/* サモンディルビオ */
		case SC_SUMMON_ELEMENTAL_PROCELLA:		/* サモンプロセラ */
		case SC_SUMMON_ELEMENTAL_TERREMOTUS:	/* サモンテレモトゥス */
		case SC_SUMMON_ELEMENTAL_SERPENS:		/* サモンサーペンス */
			val2 = 10;	// 属性魔法ダメージ増加率
			val3 = tick / 1000;
			tick = 1000;
			calc_flag = 1;
			break;
		case SC_FLAMETECHNIC:		/* フレイムテクニック */
		case SC_COLD_FORCE:			/* コールドフォース */
		case SC_GRACE_BREEZE:		/* グレイスブリーズ */
		case SC_EARTH_CARE:			/* アースケア */
			val2 = 75;		// ボルト系ダメージ増加率
			calc_flag = 1;
			break;
		case SC_DEEP_POISONING:		/* ディープポイズニング */
			val2 = 200;		// クラウドキルダメージ増加率
			calc_flag = 1;
			break;
		case SC_FLAMEARMOR:			/* フレイムアーマー */
		case SC_CRYSTAL_ARMOR:		/* クリスタルアーマー */
		case SC_EYES_OF_STORM:		/* アイズオブストーム */
		case SC_STRONG_PROTECTION:	/* ストロングプロテクション */
		case SC_POISON_SHIELD:		/* ポイズンシールド */
			val2 = 95;		// 属性ダメージ軽減率
			calc_flag = 1;
			break;
		case SC_FLAMETECHNIC_OPTION:		/* フレイムテクニック(精霊) */
			val2 = tick / 10000;
			tick = 10000;
			val3 = skill_get_sp(EM_EL_FLAMETECHNIC,val1);		// SP消費量
			break;
		case SC_FLAMEARMOR_OPTION:			/* フレイムアーマー(精霊) */
			val2 = tick / 1000;
			tick = 1000;
			val3 = skill_get_sp(EM_EL_FLAMEARMOR,val1) / 10;		// SP消費量
			break;
		case SC_COLD_FORCE_OPTION:			/* コールドフォース(精霊) */
			val2 = tick / 10000;
			tick = 10000;
			val3 = skill_get_sp(EM_EL_COLD_FORCE,val1);		// SP消費量
			break;
		case SC_CRYSTAL_ARMOR_OPTION:		/* クリスタルアーマー(精霊) */
			val2 = tick / 1000;
			tick = 1000;
			val3 = skill_get_sp(EM_EL_CRYSTAL_ARMOR,val1) / 10;		// SP消費量
			break;
		case SC_GRACE_BREEZE_OPTION:		/* グレイスブリーズ(精霊) */
			val2 = tick / 10000;
			tick = 10000;
			val3 = skill_get_sp(EM_EL_GRACE_BREEZE,val1);		// SP消費量
			break;
		case SC_EYES_OF_STORM_OPTION:		/* アイズオブストーム(精霊) */
			val2 = tick / 1000;
			tick = 1000;
			val3 = skill_get_sp(EM_EL_EYES_OF_STORM,val1) / 10;		// SP消費量
			break;
		case SC_EARTH_CARE_OPTION:			/* アースケア(精霊) */
			val2 = tick / 10000;
			tick = 10000;
			val3 = skill_get_sp(EM_EL_EARTH_CARE,val1);		// SP消費量
			break;
		case SC_STRONG_PROTECTION_OPTION:	/* ストロングプロテクション(精霊) */
			val2 = tick / 1000;
			tick = 1000;
			val3 = skill_get_sp(EM_EL_STRONG_PROTECTION,val1) / 10;		// SP消費量
			break;
		case SC_DEEP_POISONING_OPTION:		/* ディープポイズニング(精霊) */
			val2 = tick / 10000;
			tick = 10000;
			val3 = skill_get_sp(EM_EL_DEEP_POISONING,val1);		// SP消費量
			break;
		case SC_POISON_SHIELD_OPTION:		/* ポイズンシールド(精霊) */
			val2 = tick / 1000;
			tick = 1000;
			val3 = skill_get_sp(EM_EL_POISON_SHIELD,val1) / 10;		// SP消費量
			break;
		case SC_INTENSIVE_AIM:			/* インテンシブエイム */
			tick = 300;
			val2 = 100;			// 装備Atk増加値
			val3 = 250;			// Hit増加値
			val4 = 50;			// Cri増加値
			calc_flag = 1;
			break;
		case SC_INTENSIVE_AIM_COUNT:	/* インテンシブエイム(カウント) */
			tick = 600*1000;
			icon_val1 = val1;	// val1(回数)を渡してアイコン表示する
			break;
		case SC_GRENADE_FRAGMENT_1:		/* グレネードフラグメント(水属性) */
		case SC_GRENADE_FRAGMENT_2:		/* グレネードフラグメント(風属性) */
		case SC_GRENADE_FRAGMENT_3:		/* グレネードフラグメント(地属性) */
		case SC_GRENADE_FRAGMENT_4:		/* グレネードフラグメント(火属性) */
		case SC_GRENADE_FRAGMENT_5:		/* グレネードフラグメント(闇属性) */
		case SC_GRENADE_FRAGMENT_6:		/* グレネードフラグメント(聖属性) */
			{
				int i;
				for(i = SC_GRENADE_FRAGMENT_1; i <= SC_GRENADE_FRAGMENT_6; i++) {
					if(i == type)
						continue;
					if(sc->data[i].timer != -1)
						status_change_end(bl,i,-1);
				}
			}
			break;
		case SC_AUTO_FIRING_LAUNCHEREFST:	/* オートファイアリングランチャー */
			val2 = 450 + val1 * 50;		// ベーシックグレネード確率(万分率)
			val3 = 200 + val1 * 50;		// ヘイスティファイアインザホール確率(万分率)
			val4 = 100 + val1 * 50;		// グレネーズドロッピング確率(万分率)
			break;
		case SC_HIDDEN_CARD:			/* ヒドゥンカード */
			val2 = 5 + val1;		// P.Atk増加値
			val3 = 100 + val1 * 5;	// 遠距離物理増加値
			calc_flag = 1;
			break;
		case SC_TALISMAN_OF_PROTECTION:	/* 守護符 */
			val3 = tick / 3000;
			tick = 3000;
			break;
		case SC_TALISMAN_OF_WARRIOR:	/* 武士符 */
			val2 = val1 * 2;		// P.Atk増加値
			calc_flag = 1;
			break;
		case SC_TALISMAN_OF_MAGICIAN:	/* 法師符 */
			val2 = val1 * 2;		// S.Matk増加値
			calc_flag = 1;
			break;
		case SC_TALISMAN_OF_FIVE_ELEMENTS:	/* 五行符 */
			val2 = val1 * 2;		// 属性モンスターダメージ増加率
			calc_flag = 1;
			break;
		case SC_T_FIVETH_GOD:			/* 四方五行陣 */
			val2 = val1 * 2;		// S.Matk増加値
			calc_flag = 1;
			break;
		case SC_HEAVEN_AND_EARTH:		/* 天地神霊 */
			val2 = 10 + val1;		// ダメージ増加率
			calc_flag = 1;
			break;
		case SC_MARINE_FESTIVAL:	/* マリンフェスティバル */
			// ベネディクトゥムが掛かっていたら解除
			if(sc->data[SC_BENEDICTUM].timer != -1)
				status_change_end(bl,SC_BENEDICTUM,-1);
			val2 = val1*2;		// Pow増加値
			val3 = val1*2;		// Con増加値
			val4 = val1*2;		// Crt増加値
			calc_flag = 1;
			break;
		case SC_SANDY_FESTIVAL:		/* サンドフェスティバル */
			// レリギオが掛かっていたら解除
			if(sc->data[SC_RELIGIO].timer != -1)
				status_change_end(bl,SC_RELIGIO,-1);
			val2 = val1*2;		// Sta増加値
			val3 = val1*2;		// Wis増加値
			val4 = val1*2;		// Spl増加値
			calc_flag = 1;
			break;
		case SC_KI_SUL_RAMPAGE:		/* タートルランページ */
			//val2				// 強化フラグ(スキル使用時に設定)
			val3 = tick / 1000;
			tick = 1000;
			skill_castend_nodamage_id(bl,bl,SH_KI_SUL_RAMPAGE,val1,tick,0x10|val2);
			break;
		case SC_COLORS_OF_HYUN_ROK_1:		/* レインボーホーン(水属性) */
		case SC_COLORS_OF_HYUN_ROK_2:		/* レインボーホーン(風属性) */
		case SC_COLORS_OF_HYUN_ROK_3:		/* レインボーホーン(地属性) */
		case SC_COLORS_OF_HYUN_ROK_4:		/* レインボーホーン(火属性) */
		case SC_COLORS_OF_HYUN_ROK_5:		/* レインボーホーン(闇属性) */
		case SC_COLORS_OF_HYUN_ROK_6:		/* レインボーホーン(聖属性) */
			{
				int i;
				for(i = SC_COLORS_OF_HYUN_ROK_1; i <= SC_COLORS_OF_HYUN_ROK_6; i++) {
					if(i == type)
						continue;
					if(sc->data[i].timer != -1)
						status_change_end(bl,i,-1);
				}
			}
			break;
		case SC_TEMPORARY_COMMUNION:	/* 三霊一体 */
			val2 = val1 * 3;		// P.Atk増加値
			val3 = val1 * 3;		// S.Matk増加値
			val4 = val1 * 3;		// H.Plus増加値
			calc_flag = 1;
			break;
		case SC_BLESSING_OF_M_CREATURES:	/* にゃんブレッシング */
			val2 = val1 * 5;		// P.Atk増加値
			val3 = val1 * 5;		// S.Matk増加値
			calc_flag = 1;
			break;
		case SC_SHIELDCHAINRUSH:		/* シールドチェーンラッシュ */
			val2 = 10;	// 物理ダメージ増加率（未実装）
			val3 = 20;	// 移動速度低下率
			calc_flag = 1;
			ud->state.change_speed = 1;
			break;
		case SC_MISTYFROST:			/* ジャックフロストノヴァ */
			val2 = 15;	// 水属性ダメージ増加率
			break;
		case SC_GROUNDGRAVITY:		/* グラウンドグラビテーション */
			val2 = 10;	// ダメージ増加率（未実装）
			val3 = 30;	// 移動速度低下率
			calc_flag = 1;
			ud->state.change_speed = 1;
			break;
		case SC_SHADOW_CLOCK:		/* 影隠れ */
			val2 = 85;	// 物理・魔法ダメージ減少率（未実装）
			val3 = 30;	// 移動速度増加率
			calc_flag = 1;
			ud->state.change_speed = 1;
			break;
		case SC_SKY_ENCHANT:		/* 天気の身 */
			{
				int i;
				// 日出～月没は解除
				for(i = SC_RISING_SUN; i <= SC_DAWN_MOON; i++) {
					if(sc->data[i].timer != -1)
						status_change_end(bl,i,-1);
				}
			}
			break;
		default:
			if(battle_config.error_log)
				printf("UnknownStatusChange [%d]\n", type);
			return 0;
	}
	}

	if(tick <= 0)
		return 0;

	if(StatusIconChangeTable[type] != SI_BLANK)
		clif_status_change(bl,StatusIconChangeTable[type],1,icon_tick,icon_val1,icon_val2,icon_val3);	// アイコン表示

	/* 凸面鏡はアイコン送信後に処理する */
	if(type == SC_BOSSMAPINFO) {
		struct mob_data *mmd = map[bl->m].mvpboss;
		if(sd && mmd) {
			if(mmd->bl.prev == NULL) {	// 再沸き待ち中
				int diff = DIFF_TICK(mmd->last_spawntime, current_tick);
				if(diff < 0)
					diff = 0;
				clif_bossmapinfo(sd, mmd->name, 0, 0, diff, 3);
				val3 = -1;
				val4 = -1;
			} else {			// 出現中
				clif_bossmapinfo(sd, mmd->name, 0, 0, 0, 2);
				if(mmd->bl.m == bl->m) {
					clif_bossmapinfo(sd, "", mmd->bl.x, mmd->bl.y, 0, 1);
				}
				val3 = mmd->bl.m;
				val4 = mmd->bl.x + (mmd->bl.y << 16);
			}
		}
		val2 = tick / 1000;
		tick = 1000;
	}

	/* optionの変更 */
	switch(type) {
		// opt1
		case SC_STONE:
		case SC_FREEZE:
		case SC_STUN:
		case SC_SLEEP:
			unit_stopattack(bl);	// 攻撃停止
			skill_stop_dancing(bl,0);	// 演奏/ダンスの中断
			{
				// 同時に掛からないステータス異常を解除
				int i;
				for(i = SC_STONE; i <= SC_SLEEP; i++) {
					if(sc->data[i].timer != -1) {
						sc->count--;
						delete_timer(sc->data[i].timer, status_change_timer);
						sc->data[i].timer = -1;
					}
				}
			}
			if(type == SC_STONE)
				sc->opt1 = OPT1_STONECURSE_ING;
			else
				sc->opt1 = type - SC_STONE + 1;

			if(md) {
				mob_unlocktarget(md, current_tick);
				md->attacked_id = 0;
				md->attacked_players = 0;
			}
			opt_flag = 1;
			break;
		case SC_HELLINFERNO:		/* ヘルインフェルノ */
			sc->opt1 = OPT1_BURNNING;
			opt_flag = 1;
			break;
		case SC_WHITEIMPRISON:		/* ホワイトインプリズン */
			sc->opt1 = OPT1_IMPRISON;
			opt_flag = 1;
			break;
		// opt2
		case SC_POISON:
		case SC_CURSE:
		case SC_SILENCE:
		case SC_CONFUSION:
			sc->opt2 |= OPT2_POISON<<(type-SC_POISON);
			opt_flag = 1;
			break;
		case SC_FOGWALLPENALTY:
		case SC_BLIND:
			if(sc->data[SC_FOGWALLPENALTY].timer == -1) {
				sc->opt2 |= OPT2_BLIND;
				opt_flag = 1;
				if(md && !(flag&2))
					md->target_id = 0;
			}
			break;
		case SC_ANGELUS:			/* アンゼルス */
			sc->opt2 |= OPT2_ANGELUS;
			opt_flag = 1;
			break;
		case SC_DPOISON:
			sc->opt2 |= OPT2_HEAVYPOISON;
			opt_flag = 1;
			break;
		case SC_BLEED:
			sc->opt2 |= OPT2_BLEEDING;
			opt_flag = 1;
			break;
		case SC_FEAR:
			sc->opt2 |= OPT2_FEAR;
			opt_flag = 1;
			break;
		// opt3
		case SC_ONEHAND:		/* 1HQ */
		case SC_TWOHANDQUICKEN:		/* 2HQ */
		case SC_SPEARQUICKEN:		/* スピアクイッケン */
		case SC_CONCENTRATION:		/* コンセントレーション */
		case SC_WEAPONQUICKEN:		/* ウェポンクイッケン */
			sc->opt3 |= OPT3_QUICKEN;
			opt_flag = 2;
			break;
		case SC_OVERTHRUST:		/* オーバートラスト */
		case SC_SWOO:			/* エスウ */
			sc->opt3 |= OPT3_OVERTHRUST;
			opt_flag = 2;
			break;
		case SC_ENERGYCOAT:		/* エナジーコート */
		case SC_SKE:			/* エスク */
			sc->opt3 |= OPT3_ENERGYCOAT;
			opt_flag = 2;
			break;
		case SC_EXPLOSIONSPIRITS:	/* 爆裂波動 */
			sc->opt3 |= OPT3_EXPLOSIONSPIRITS;
			opt_flag = 2;
			break;
		case SC_STEELBODY:		/* 金剛 */
		case SC_SKA:			/* エスカ */
			sc->opt3 |= OPT3_STEELBODY;
			opt_flag = 2;
			break;
		case SC_BLADESTOP:		/* 白刃取り */
			sc->opt3 |= OPT3_BLADESTOP;
			opt_flag = 2;
			break;
		case SC_AURABLADE:			/* オーラブレード */
			sc->opt3 |= OPT3_AURABLADE;
			opt_flag = 2;
			break;
		case SC_BERSERK:		/* バーサーク */
			sc->opt3 |= OPT3_BERSERK;
			opt_flag = 2;
			break;
		case SC_DANCING:			/* ダンス/演奏中 */
			if(sc->data[SC_DANCING].val1 != CG_MOONLIT)
				break;
			sc->opt3 |= OPT3_MOON;
			opt_flag = 2;
			break;
		case SC_MARIONETTE:		/* マリオネットコントロール */
		case SC_MARIONETTE2:		/* マリオネットコントロール */
			sc->opt3 |= OPT3_MARIONETTE;
			opt_flag = 2;
			break;
		case SC_ASSUMPTIO:		/* アスムプティオ */
		case SC_ASSUMPTIO2:		/* キャッシュアスムプティオ */
			sc->opt3 |= OPT3_ASSUMPTIO;
			clif_misceffect2(bl,375);
			opt_flag = 2;
			break;
		case SC_WARM:			/* 温もり */
			sc->opt3 |= OPT3_SUN_WARM;
			opt_flag = 2;
			break;
		case SC_KAITE:
			sc->opt3 |= OPT3_KAITE;
			opt_flag = 2;
			break;
		case SC_BUNSINJYUTSU:		/* 分身の術 */
			sc->opt3 |= OPT3_BUNSIN;
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
			sc->opt3 |= OPT3_SOULLINK;
			clif_misceffect2(bl,424);
			opt_flag = 2;
			break;
		case SC_ELEMENTUNDEAD:		// 不死
			sc->opt3 |= OPT3_UNDEAD;
			opt_flag = 2;
			break;
		// option
		case SC_SIGHT:
			sc->option |= OPTION_SIGHT;
			opt_flag = 1;
			break;
		case SC_HIDING:
			if(sd && val3 == 0)	// 霞斬りでない通常のハイドならアイコン表示
				clif_status_change(bl,SI_HIDING,1,icon_tick,0,0,0);
			unit_stopattack(bl);
			sc->option |= OPTION_HIDE;
			opt_flag = 1;
			break;
		case SC_CLOAKING:
		case SC_CLOAKINGEXCEED:		/* クローキングエクシード */
		case SC_NEWMOON:			/* 朔月脚 */
		case SC__INVISIBILITY:		/* インビジビリティ */
			unit_stopattack(bl);
			sc->option |= OPTION_CLOAKING;
			opt_flag = 1;
			break;
		case SC_INVISIBLE:
		case SC__FEINTBOMB:			/* フェイントボム */
			unit_stopattack(bl);
			sc->option |= OPTION_SPECIALHIDING;
			opt_flag = 1;
			break;
		case SC_REVERSEORCISH:
			sc->option |= OPTION_ORCFACE;
			opt_flag = 1;
			break;
		case SC_WEDDING:
			sc->option |= OPTION_MARRIED;
			opt_flag = 1;
			break;
		case SC_RUWACH:
			sc->option |= OPTION_RUWACH;
			opt_flag = 1;
			break;
		case SC_CHASEWALK:
			unit_stopattack(bl);
			sc->option |= (OPTION_CLOAKING | OPTION_FOOTPRINT);
			opt_flag = 1;
			break;
		case SC_FUSION:
			sc->option |= OPTION_STAR2;
			opt_flag = 1;
			break;
		case SC_SANTA:
			sc->option |= OPTION_SANTA;
			opt_flag = 1;
			break;
		case SC_SUMMER:
			sc->option |= OPTION_SUMMER;
			opt_flag = 1;
			break;
		case SC_ON_PUSH_CART:	/* カート */
#if PACKETVER < 20120201
			// 古いクライアントはオプションを更新する
			sc->option = (sc->option & ~OPTION_CARTMASK) | val1;
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
	status_calloc_sc_data(sc);
#endif

	sc->count++;	/* ステータス異常の数 */

	sc->data[type].val1 = val1;
	sc->data[type].val2 = val2;
	sc->data[type].val3 = val3;
	sc->data[type].val4 = val4;
	/* タイマー設定 */
	sc->data[type].timer = add_timer(current_tick + tick, status_change_timer, bl->id, INT2PTR(type));

	if(calc_flag) {
		// ステータス再計算
		if(sd) {
			if(!(flag&4))
				status_calc_pc(sd,0);
		} else if(hd) {
			homun_calc_status(hd);
			clif_send_homstatus(hd->msd,0);
		} else if(mcd) {
			merc_calc_status(mcd);
			clif_send_mercstatus(mcd->msd);
			clif_mercskillinfoblock(mcd->msd);
		} else if(eld) {
			elem_calc_status(eld);
			clif_send_elemstatus(eld->msd);
		}
	}
	// 計算後に走らせる
	switch(type) {
		case SC_RUN:
		case SC_WUGDASH:
			// clif_skill_nodamage() は必ず clif_status_change() と clif_walkok() の間に呼び出す
			if(type == SC_RUN)
				clif_skill_nodamage(bl,bl,TK_RUN,val1,1);
			else if(type == SC_WUGDASH)
				clif_skill_nodamage(bl,bl,RA_WUGDASH,val1,1);
			if(sd) {
				pc_runtodir(sd);
			}
			break;
		case SC_FORCEWALKING:
			unit_forcewalktodir(bl,val4);
			break;
	}

	return 0;
}
