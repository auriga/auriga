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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "db.h"
#include "timer.h"
#include "nullpo.h"
#include "malloc.h"
#include "mmo.h"
#include "utils.h"

#include "guild.h"
#include "skill.h"
#include "skill_internal.h"
#include "map.h"
#include "path.h"
#include "clif.h"
#include "pc.h"
#include "bonus.h"
#include "pet.h"
#include "mob.h"
#include "battle.h"
#include "party.h"
#include "itemdb.h"
#include "script.h"
#include "intif.h"
#include "status.h"
#include "date.h"
#include "unit.h"
#include "homun.h"
#include "msg.h"
#include "ranking.h"
#include "npc.h"
#include "merc.h"
#include "buyingstore.h"
#include "elem.h"

/* Split from skill.c (Issue #56) */
/*==========================================
 * スキルユニットの発動イベント(タイマー発動)
 *------------------------------------------
 */
int skill_unit_onplace_timer(struct skill_unit *src,struct block_list *bl,unsigned int tick)
{
	struct skill_unit_group *sg;
	struct block_list *ss;
	struct status_change *sc;
	struct unit_data *ud;
	struct linkdb_node **node;
	int tickset_id, diff = 0;
	unsigned int tickset_tick;

	nullpo_retr(0, src);
	nullpo_retr(0, bl);
	nullpo_retr(0, sg = src->group);

	if(!src->alive)
		return 0;

	if(unit_isdead(bl))
		return 0;

	nullpo_retr(0, ss = map_id2bl(sg->src_id));
	nullpo_retr(0, ud = unit_bl2ud(bl));

	sc = status_get_sc(bl);

	if(status_get_mode(bl)&MD_SKILLIMMUNITY)
		return 0;

	// 対象がホバーリング状態の場合は一部無効
	if(sc && sc->data[SC_HOVERING].timer != -1) {
		switch(sg->unit_id) {
		case UNT_QUAGMIRE:
		case UNT_BLASTMINE:
		case UNT_SKIDTRAP:
		case UNT_ANKLESNARE:
		case UNT_VENOMDUST:
		case UNT_LANDMINE:
		case UNT_SHOCKWAVE:
		case UNT_SANDMAN:
		case UNT_FLASHER:
		case UNT_FREEZINGTRAP:
		case UNT_CLAYMORETRAP:
		case UNT_TALKIEBOX:
		case UNT_GRAVITATION:
		case UNT_SUITON:
		case UNT_MAKIBISHI:
		case UNT_B_TRAP:
			return 0;
		}
	}

	// 時間切れ間際は発動させないようにするか判定
	if(battle_config.skill_unit_interval_limit && ((sg->limit > 0 && DIFF_TICK(tick,sg->tick) >= sg->limit) || (src->limit > 0 && DIFF_TICK(tick,sg->tick) >= src->limit))) {
		return 0;
	}

	// 前に影響を受けてからintervalの間は影響を受けない
	if(skill_get_unit_flag(sg->skill_id,sg->skill_lv)&UF_NOOVERLAP) {
		tickset_id = sg->skill_id;
		node       = &ud->skilltickset;
	} else {
		tickset_id = bl->id;
		node       = &sg->tickset;
	}
	tickset_tick = PTR2UINT(linkdb_search( node, INT2PTR(tickset_id) ));
	if(tickset_tick == 0)
		tickset_tick = tick;

	diff = DIFF_TICK(tick, tickset_tick);
	if(sg->skill_id == PR_SANCTUARY) {
		diff += 500; // 新規に回復したユニットだけカウントするための仕掛け
	}

	if(diff < 0) {
		if(sg->skill_id == WZ_STORMGUST && status_get_mode(bl)&MD_BOSS) {
			// ボス属性にはストームガストの3HIT毎に2HITのダメージが重なる
			if(!sc || sc->data[SC_FREEZE].val3 != 3)
				return 0;
		} else {
			return 0;
		}
	}

	tickset_tick = tick + sg->interval;

	// GXは重なっていたら3HITしない
	if(sg->skill_id == CR_GRANDCROSS && !battle_config.gx_allhit) {
		int count = map_count_oncell(bl->m,bl->x,bl->y,BL_PC|BL_MOB);
		if(count > 0)
			tickset_tick += sg->interval * (count-1);
	}
	linkdb_replace( node, INT2PTR(tickset_id), UINT2PTR(tickset_tick) );

	switch (sg->unit_id) {
	case UNT_PNEUMA:	/* ニューマ */
		status_change_start(bl,SC_PNEUMA,sg->skill_lv,src->bl.id,0,0,sg->interval+100,0);
		break;
	case UNT_WARP_ACTIVE:	/* ワープポータル(発動後) */
		if (bl->type == BL_PC) {
			struct map_session_data *sd = (struct map_session_data *)bl;
			if(sd) {
				if ((sd->state.warp_waiting || strcmp(map[bl->m].name,sg->valstr) == 0) &&
				    src->bl.m == bl->m &&
				    src->bl.x == bl->x &&
				    src->bl.y == bl->y &&
				    src->bl.x == sd->ud.to_x &&
				    src->bl.y == sd->ud.to_y)
				{
					sd->state.warp_waiting = 0;
					if (battle_config.chat_warpportal || !sd->chatID){
						char mapname[24];
						int  x = sg->val2>>16;
						int  y = sg->val2&0xffff;
						strncpy(mapname,sg->valstr,24);
						if( sg->src_id == bl->id ||
						    (strcmp(map[src->bl.m].name,sg->valstr) == 0 && src->bl.x == (sg->val2>>16) && src->bl.y == (sg->val2&0xffff)) ||
						    (--sg->val1) <= 0 )
						{
							skill_delunitgroup(sg);
						}
						pc_setpos(sd,mapname,x,y,3);
					}
				} else {
				 	sd->state.warp_waiting = 1;
				}
			}
		} else if(bl->type == BL_MOB && battle_config.mob_warpportal) {
			int m = map_mapname2mapid(sg->valstr);
			mob_warp((struct mob_data *)bl,m,sg->val2>>16,sg->val2&0xffff,3);
		}
		break;
	case UNT_SANCTUARY:	/* サンクチュアリ */
		{
			int race = status_get_race(bl);

#ifndef PRE_RENEWAL
			if(bl->type == BL_MOB && ((struct mob_data *)bl)->class_ == MOBID_EMPERIUM)
				break;
#endif
			if (battle_check_undead(race,status_get_elem_type(bl)) || race == RCT_DEMON || (sc && sc->data[SC_AKAITSUKI].timer != -1)) {
				if (bl->type == BL_PC) {
					if(!map[bl->m].flag.pvp && !map[bl->m].flag.gvg)
						break;
				}
				if (battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0))
					sg->val1 = sg->val1-2;	// チャットキャンセルに対応
			} else {
				int heal;
				if (status_get_hp(bl) >= status_get_max_hp(bl))
					break;
				heal = sg->val2;
				if(sc) {
					if(sc->data[SC_CRITICALWOUND].timer != -1)
						heal = heal * (100 - sc->data[SC_CRITICALWOUND].val2) / 100;
					if(sc->data[SC_DEATHHURT].timer != -1)	/* デスハート */
						heal = heal * (100 - sc->data[SC_DEATHHURT].val2) / 100;
					if(sc->data[SC_BERSERK].timer != -1) /* バーサーク中はヒール０ */
						heal = 0;
				}
				if(bl->type == BL_PC && ((struct map_session_data *)bl)->special_state.no_magic_damage)
					heal = 0;	/* 黄金蟲カード（ヒール量０） */

				clif_skill_nodamage(&src->bl,bl,AL_HEAL,heal,1);
				battle_heal(NULL,bl,heal,0,0);
				if (diff >= 500)
					sg->val1--;	// 新規に入ったユニットだけカウント
			}
			if (sg->val1 <= 0)
				skill_delunitgroup(sg);
		}
		break;
	case UNT_MAGNUS:	/* マグヌスエクソシズム */
		{
			int race = status_get_race(bl);
			if (!battle_check_undead(race,status_get_elem_type(bl)) && race != RCT_DEMON)
				return 0;
			battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
			src->val2++;
		}
		break;
	case UNT_FIREWALL:		/* ファイアーウォール */
	case UNT_FLAMECROSS:	/* フレイムクロス */
		do {
			battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		} while((--src->val2) > 0 && !unit_isdead(bl) && bl->x == src->bl.x && bl->y == src->bl.y);
		if (src->val2 <= 0)
			skill_delunit(src);
		break;
	case UNT_ATTACK_SKILLS:	/* 攻撃系スキル全般 */
		switch(sg->skill_id) {
		case GS_DESPERADO:	/* デスペラード */
			battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,sg->val2|0x0500);
			break;
		case GN_CRAZYWEED_ATK:	/* クレイジーウィード */
			battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0x0500);
			break;
		case SG_SUN_WARM:	/* 温もり */
		case SG_MOON_WARM:	/* 温もり */
		case SG_STAR_WARM:	/* 温もり */
			{
				const int x = bl->x, y = bl->y;
				int hit   = 0;
				int count = skill_get_blewcount(sg->skill_id,sg->skill_lv);

				do {
					if(bl->type != BL_PC) {
						if(battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0))
							skill_blown(&src->bl,bl,count|SAB_REVERSEBLOW|SAB_NOPATHSTOP);
					} else {
						struct map_session_data *sd = (struct map_session_data *)bl;
						if(sd) {
							sd->status.sp -= 15;
								if(sd->status.sp < 0)
									sd->status.sp = 0;
								clif_updatestatus(sd,SP_SP);
							}
						}
				} while(sg->alive_count > 0 && !unit_isdead(bl) && x == bl->x && y == bl->y &&
					sg->interval > 0 && ++hit < SKILLUNITTIMER_INVERVAL / sg->interval);
			}
			break;
		case WL_COMET:				/* コメット */
		case NPC_COMET:				/* Mコメット */
			{
				struct skill_unit *su = (struct skill_unit *)(sg->unit);
				if(su) {
					int dist = path_distance(bl->x,bl->y,su->bl.x,su->bl.y);
					clif_skill_damage(ss, bl, tick, 0, 0, 0, 0, sg->skill_id, sg->skill_lv, 1);
					battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,(dist > 7)? 3: (dist > 5)? 2: (dist > 3)? 1: 0);
				}
			}
			break;
		case AG_VIOLENT_QUAKE_ATK:		/* バイオレントクエイク(攻撃) */
		case AG_ALL_BLOOM_ATK:			/* オールブルーム(攻撃) */
			battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,sg->val1);
			break;
		case SKE_STAR_BURST:			/* 天命落星 */
		case SS_KUNAIKAITEN:			/* 苦無 -回転- */
		case SS_KUNAIKUSSETSU:			/* 苦無 -屈折- */
			battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
			break;
		default:
			battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		}
		break;
	case UNT_EARTHSTRAIN:	/* アースストレイン */
	case UNT_PSYCHIC_WAVE:	/* サイキックウェーブ */
	case UNT_CLOUD_KILL:	/* クラウドキル */
	case UNT_POISON_MIST:	/* ポイズンミスト */
	case UNT_RAIN_OF_CRYSTAL:	/* レインオブクリスタル */
	case UNT_MYSTERY_ILLUSION:	/* ミステリーイリュージョン */
	case UNT_STRANTUM_TREMOR:	/* ストラタムトレマー */
	case UNT_TORNADO_STORM:		/* トルネードストーム */
	case UNT_FLORAL_FLARE_ROAD:	/* フローラルフレアロード */
	case UNT_CROSS_RAIN:	/* クロスレイン */
	case UNT_PNEUMATICUS_PROCELLA:	/* ニューマティックプロセラ */
	case UNT_LIGHTNING_LAND:	/* ライトニングランド */
	case UNT_VENOM_SWAMP:		/* ベナムスワンプ */
	case UNT_CONFLAGRATION:		/* コンフラグレーション */
	case UNT_HYUN_ROKS_BREEZE:	/* ディアーブリーズ */
		battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		break;
	case UNT_FIREPILLAR_WAITING:	/* ファイアーピラー(発動前) */
		skill_unitsetting(ss,sg->skill_id,sg->skill_lv,src->bl.x,src->bl.y,1);
		skill_delunit(src);
		break;
	case UNT_FIREPILLAR_ACTIVE:	/* ファイアーピラー(発動後) */
		{
			int i = src->range;
			int splash_count = 0;
#ifdef PRE_RENEWAL
			if(sg->skill_lv>5)
				i += 2;
#else
			i += 1;
#endif
			splash_count = map_foreachinarea(skill_count_target,src->bl.m,
						src->bl.x-i,src->bl.y-i,
						src->bl.x+i,src->bl.y+i,
						(BL_CHAR|BL_SKILL),src);
			map_foreachinarea(skill_trap_splash,src->bl.m,
						src->bl.x-i,src->bl.y-i,
						src->bl.x+i,src->bl.y+i,
						(BL_CHAR|BL_SKILL),src,tick,splash_count);
		}
		break;
	case UNT_SKIDTRAP:	/* スキッドトラップ */
		{
			// 罠設置時のキャラの座標とターゲットの位置関係で飛ぶ方向を決める
			int xs = sg->val1, ys = sg->val2, dir;
			int count = skill_get_blewcount(sg->skill_id,sg->skill_lv);
			if( (bl->x == src->bl.x && bl->y == src->bl.y) || (bl->x == xs && bl->y == ys) ) {
				dir = 6;	// 罠の直上か設置時の位置に居るなら真西に飛ぶ
			} else {
				dir = path_calc_dir(bl,xs,ys);
				if(dir == 0)
					dir = 8;
			}
			skill_blown(&src->bl,bl,count|(dir<<20)|SAB_NODAMAGE|SAB_NOPATHSTOP);
			sg->unit_id = UNT_USED_TRAPS;
			clif_changelook(&src->bl,LOOK_BASE,sg->unit_id);
			sg->limit=DIFF_TICK(tick,sg->tick)+1500;
		}
		break;
	case UNT_LANDMINE:	/* ランドマイン */
		battle_skill_attack(BF_MISC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		sg->unit_id = UNT_USED_TRAPS;
		clif_changelook(&src->bl,LOOK_BASE,UNT_FIREPILLAR_ACTIVE);
		sg->limit = DIFF_TICK(tick,sg->tick)+1500;
		break;

	case UNT_BLASTMINE:	/* ブラストマイン */
	case UNT_SHOCKWAVE:	/* ショックウェーブトラップ */
	case UNT_SANDMAN:	/* サンドマン */
	case UNT_FLASHER:	/* フラッシャー */
	case UNT_FREEZINGTRAP:	/* フリージングトラップ */
	case UNT_CLAYMORETRAP:	/* クレイモアトラップ */
	case UNT_MAGENTATRAP:		/* マゼンタトラップ */
	case UNT_COBALTTRAP:		/* コバルトトラップ */
	case UNT_MAIZETRAP:			/* メイズトラップ */
	case UNT_VERDURETRAP:		/* ヴェルデュールトラップ */
	case UNT_FIRINGTRAP:		/* ファイアリングトラップ */
	case UNT_ICEBOUNDTRAP:		/* アイスバウンドトラップ */
		{
			int splash_count = 0;
			int ar = skill_get_area(sg->skill_id,sg->skill_lv);		// 効果範囲はskill_dbのarea参照
			int sec;

			sec = (sg->unit_id == UNT_FIRINGTRAP)? 0: 1500;
			splash_count = map_foreachinarea(skill_count_target,src->bl.m,
						src->bl.x-ar,src->bl.y-ar,
						src->bl.x+ar,src->bl.y+ar,
						(BL_CHAR|BL_SKILL),src);
			map_foreachinarea(skill_trap_splash,src->bl.m,
						src->bl.x-ar,src->bl.y-ar,
						src->bl.x+ar,src->bl.y+ar,
						(BL_CHAR|BL_SKILL),src,tick,splash_count);
			sg->unit_id = UNT_USED_TRAPS;
			clif_changelook(&src->bl,LOOK_BASE,sg->unit_id);
			sg->limit = DIFF_TICK(tick,sg->tick) + sec;
		}
		break;

	case UNT_ANKLESNARE:	/* アンクルスネア */
		{
			int type = GetSkillStatusChangeTable(sg->skill_id);
			if (sg->val2 == 0 && (!sc || sc->data[type].timer == -1)) {
				int sec = skill_get_time2(sg->skill_id,sg->skill_lv) - status_get_agi(bl)*100;
				if(status_get_mode(bl)&MD_BOSS)
					sec /= 5;
				// 最低拘束時間補償（式はeAのものをとりあえず採用）
				if(sec < 3000 + 30 * sg->skill_lv)
					sec = 3000 + 30 * sg->skill_lv;
				status_change_start(bl,type,sg->skill_lv,sg->bl.id,0,0,sec,0);
				// 本来ならボス属性なら吸い寄せられないが、skill_delunitgroup() 等の処理と上手く折り合いが付かないので保留
				if(!map[src->bl.m].flag.pvp && !map[src->bl.m].flag.gvg) {
					unit_movepos(bl, src->bl.x, src->bl.y, 0);
					clif_01ac(&src->bl);
				}
				sg->limit    = DIFF_TICK(tick,sg->tick) + sec;
				sg->val2     = bl->id;
				sg->interval = -1;
				src->range   = 0;
			}
		}
		break;
	case UNT_VENOMDUST:	/* ベナムダスト */
		{
			int type = GetSkillStatusChangeTable(sg->skill_id);
			if(type < 0)
				break;
			if (sc && sc->data[type].timer != -1)
				break;
			if(atn_rand() % 10000 < status_change_rate(bl,type,10000,status_get_lv(ss)))
				status_change_start(bl,type,sg->skill_lv,src->bl.id,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		}
		break;
	case UNT_DEMONSTRATION:	/* デモンストレーション */
		battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		if(bl->type == BL_PC && atn_rand()%100 < sg->skill_lv)
			pc_break_equip((struct map_session_data *)bl, LOC_RARM);
		break;
	case UNT_TALKIEBOX:				/* トーキーボックス */
		if(sg->src_id == bl->id) // 自分が踏んでも発動しない
			break;
		if(sg->val2 == 0) {
			clif_talkiebox(&src->bl,sg->valstr);
			sg->unit_id = UNT_USED_TRAPS;
			clif_changelook(&src->bl,LOOK_BASE,sg->unit_id);
			sg->limit = DIFF_TICK(tick,sg->tick) + 5000;
			sg->val2  = -1; // 踏んだ
		}
		break;
	case UNT_GOSPEL:	/* ゴスペル */
		{
			struct map_session_data *sd = NULL;
			if(bl->type == BL_PC)
				sd = (struct map_session_data *)bl;
			if (sd && sg->src_id == bl->id) {
				int hp = (sg->skill_lv <= 5) ? 30 : 45;
				int sp = (sg->skill_lv <= 5) ? 20 : 35;
				if(sd->status.hp <= hp || sd->status.sp <= sp) {
					status_change_end(bl,SC_GOSPEL,-1);
					break;
				}
				pc_heal(sd,-hp,-sp,0,0);
				break;
			}
			if (sd && sd->special_state.no_magic_damage)
				break;
			if (atn_rand()%100 >= 50 + sg->skill_lv * 5)
				break;
			if (battle_check_target(&src->bl,bl,BCT_PARTY) > 0) {	// 味方(PT)対象
				int type = 0;
				switch(atn_rand()%13) {
				case 0:		// HPを回復(1000～9999？)
					battle_heal(NULL,bl,1000+atn_rand()%9000,0,0);
					break;
				case 1:		// MHPを100%増加(持続時間60秒)
					status_change_start(bl,SC_INCMHP2,100,0,0,0,60000,0);
					type = 0x17;
					break;
				case 2:		// MSPを100%増加(持続時間60秒)
					status_change_start(bl,SC_INCMSP2,100,0,0,0,60000,0);
					type = 0x18;
					break;
				case 3:		// 全てのステータス+20(持続時間60秒)
					status_change_start(bl,SC_INCALLSTATUS,20,0,0,0,60000,0);
					type = 0x19;
					break;
				case 4:		// ブレッシングLv10効果付与
					status_change_start(bl,SC_BLESSING,10,0,0,0,skill_get_time(AL_BLESSING,10),0);
					break;
				case 5:		// 速度増加Lv10効果付与
					status_change_start(bl,SC_INCREASEAGI,10,0,0,0,skill_get_time(AL_INCAGI,10),0);
					break;
				case 6:		// 武器に聖属性効果付与
					status_change_start(bl,SC_ASPERSIO,sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
					type = 0x1c;
					break;
				case 7:		// 鎧に聖属性効果付与
					status_change_start(bl,SC_BENEDICTIO,sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
					type = 0x1d;
					break;
				case 8:		// ATKが100%増加
					status_change_start(bl,SC_INCATK2,100,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
					type = 0x1f;
					break;
				case 9:		// HIT, FLEEが+50(持続時間60秒)
					status_change_start(bl,SC_INCHIT,50,0,0,0,60000,0);
					status_change_start(bl,SC_INCFLEE,50,0,0,0,60000,0);
					type = 0x20;
					break;
				case 10:	// 全ての状態異常を解除
					status_change_release(bl,0x08);
					type = 0x15;
					break;
				case 11:	// 全状態異常の耐性(持続時間60秒)
					status_change_start(bl,SC_STATUS_UNCHANGE,0,0,0,0,60000,0);
					type = 0x16;
					break;
				case 12:	// 防御力増加(持続時間10秒)
					status_change_start(bl,SC_INCDAMAGE,-50,0,0,0,10000,0);
					type = 0x1e;
					break;
				}
				if(type > 0 && sd)
					clif_gospel_message(sd,type);
			}
			else if (battle_check_target(&src->bl,bl,BCT_ENEMY) > 0 && !(status_get_mode(bl)&MD_BOSS)) {	// 敵対象でボス以外
				switch(atn_rand()%8) {
				case 0:		// ランダムダメージ(1000～9999？)
					battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
					break;
				case 1:		// 呪い効果付与
					if(atn_rand() % 10000 < status_change_rate(bl,SC_CURSE,10000,status_get_lv(ss)))
						status_change_pretimer(bl,SC_CURSE,sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0,tick+status_get_amotion(ss));
					break;
				case 2:		// 暗黒効果付与
					if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,10000,status_get_lv(ss)))
						status_change_pretimer(bl,SC_BLIND,sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0,tick+status_get_amotion(ss));
					break;
				case 3:		// 毒効果付与
					if(atn_rand() % 10000 < status_change_rate(bl,SC_POISON,10000,status_get_lv(ss)))
						status_change_pretimer(bl,SC_POISON,sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0,tick+status_get_amotion(ss));
					break;
				case 4:		// プロボックLv10効果付与
					status_change_start(bl,SC_PROVOKE,10,0,0,0,skill_get_time(SM_PROVOKE,10),0);
					break;
				case 5:		// ATKが0に減少(持続時間20秒)
					status_change_start(bl,SC_INCATK2,-100,0,0,0,20000,0);
					break;
				case 6:		// FLEEが0に減少(持続時間20秒)
					status_change_start(bl,SC_INCFLEE2,-100,0,0,0,20000,0);
					break;
				case 7:		// HITが0に減少(持続時間50秒)
					status_change_start(bl,SC_INCHIT2,-100,0,0,0,50000,0);
					break;
				}
			}
		}
		break;
	case UNT_BASILICA:	/* バジリカ */
		if (sg->src_id == bl->id)
			break;
		if ( battle_check_target(&src->bl,bl,BCT_ENEMY) > 0 && !(status_get_mode(bl)&MD_BOSS) )
			skill_blown(&src->bl,bl,SAB_NODAMAGE|1);
		if (battle_check_target(&src->bl,bl,BCT_NOENEMY)>0) {
			int type = GetSkillStatusChangeTable(sg->skill_id);
			if(type < 0)
				break;
			status_change_start(bl,type,sg->skill_lv,sg->val1,sg->val2,src->bl.id,sg->interval+100,0);
		}
		break;
	case UNT_SPIDERWEB:	/* スパイダーウェブ */
		if((!sc || sc->data[SC_SPIDERWEB].timer == -1) && sg->val2 == 0) {
			skill_additional_effect(ss,bl,sg->skill_id,sg->skill_lv,BF_MISC,tick);
			unit_movepos(bl, src->bl.x, src->bl.y, 0);
			sg->limit    = DIFF_TICK(tick,sg->tick) + skill_get_time2(sg->skill_id,sg->skill_lv);
			sg->val2     = bl->id;
			sg->interval = -1;
			src->range   = 0;
		}
		break;
	case UNT_MOONLIT: 	/* 月明りの下で */
		if(!(bl->type & (BL_MOB | BL_PC)))
			break;
		if (sg->src_id == bl->id)
			break;
		// 相方
		if(sc && sc->data[SC_DANCING].timer != -1 && sg->src_id == sc->data[SC_DANCING].val4)
			break;
		if(!(status_get_mode(bl)&MD_BOSS))
		{
			int d = unit_distance(&src->bl,bl);
			int range = skill_get_unit_range(sg->skill_id,sg->skill_lv);
			int count = (d < range)? range-d+2: 1;
			skill_blown(&src->bl,bl,count|SAB_NODAMAGE);
		}
		break;
	case UNT_GRAVITATION:
		if (battle_check_target(&src->bl,bl,BCT_ENEMY) > 0)		// 敵対象
		{
			battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		//	unit_fixdamage(&src->bl,bl,0, 0, 0,sg->skill_lv*200+200,1, 4, 0, 0);
		}
		break;
	case UNT_TATAMIGAESHI:	/* 畳返し */
		battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0x0500);
		break;
	case UNT_KAEN:	/* 火炎陣 */
		battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		if(--src->val1 <= 0)
			skill_delunit(src);
		break;
	case UNT_GROUNDDRIFT_WIND:	/* グラウンドドリフト */
	case UNT_GROUNDDRIFT_DARK:
	case UNT_GROUNDDRIFT_POISON:
	case UNT_GROUNDDRIFT_WATER:
	case UNT_GROUNDDRIFT_FIRE:
	case UNT_GROUNDDRIFT_NEUTRAL:
#ifdef PRE_RENEWAL
		battle_skill_attack(BF_MISC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
#else
		int ar = skill_get_area(sg->skill_id,sg->skill_lv);		// 効果範囲はskill_dbのarea参照
		map_foreachinarea(skill_trap_splash,src->bl.m,
					src->bl.x-ar,src->bl.y-ar,
					src->bl.x+ar,src->bl.y+ar,
					(BL_CHAR|BL_SKILL),src,tick,1);
#endif
		sg->unit_id = UNT_USED_TRAPS;
		clif_changelook(&src->bl,LOOK_BASE,UNT_FIREPILLAR_ACTIVE);
		sg->limit = DIFF_TICK(tick,sg->tick) + 1500;
		break;
	case UNT_EVILLAND:	/* イービルランド */
		{
			int race = status_get_race(bl);

			if(battle_check_undead(race,status_get_elem_type(bl)) || race == RCT_DEMON) {
				int heal = sg->val1;
				if(status_get_hp(bl) >= status_get_max_hp(bl))
					break;
				clif_skill_nodamage(&src->bl,bl,AL_HEAL,heal,1);
				battle_heal(NULL,bl,heal,0,0);
			} else if(battle_check_target(&src->bl,bl,BCT_ENEMY) > 0 && bl->type == BL_PC) {
				battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
			}
		}
		break;
	case UNT_POISONSMOKE:	/* ポイズンスモーク */
		if(atn_rand() % 10000 < status_change_rate(bl,sg->val1,5000,status_get_lv(&src->bl)))
			status_change_start(bl,sg->val1,sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		break;
	case UNT_EPICLESIS:	/* エピクレシス */
		if(battle_check_target(&src->bl,bl,BCT_NOENEMY)) {
			status_change_start(bl,SC_EPICLESIS,sg->skill_lv,0,0,0,sg->interval+100,0);
			if(bl->type == BL_PC) {
				struct map_session_data *sd = (struct map_session_data *)bl;

				if(sd->status.hp < sd->status.max_hp) {
					int hp = sd->status.max_hp * (((sg->skill_lv - 1) / 2) + 3) / 100;
					if(sd->status.hp + hp > sd->status.max_hp) {
						hp = sd->status.max_hp - sd->status.hp;
					}
					if(hp > 0) {
						sd->status.hp += hp;
						clif_heal(sd->fd,SP_HP,hp);
					}
				}

				if(sd->status.sp < sd->status.max_sp) {
					int sp = sd->status.max_sp * (((sg->skill_lv - 1) / 2) + 2) / 100;
					if(sd->status.sp + sp > sd->status.max_sp) {
						sp = sd->status.max_sp - sd->status.sp;
					}
					if(sp > 0) {
						sd->status.sp += sp;
						clif_heal(sd->fd,SP_SP,sp);
					}
				}
			}
		}
		skill_detect(bl);		// ディティクト効果
		break;
	case UNT_ELECTRICSHOCKER:	/* エレクトリックショッカー */
		{
			int ar = skill_get_area(sg->skill_id,sg->skill_lv);		// 効果範囲はskill_dbのarea参照
			unit_movepos(bl, src->bl.x, src->bl.y, 0);		// 踏んだ対象者のみ移動
			map_foreachinarea(skill_trap_splash,src->bl.m,
						src->bl.x-ar,src->bl.y-ar,
						src->bl.x+ar,src->bl.y+ar,
						(BL_CHAR|BL_SKILL),src,tick,1);
			sg->unit_id = UNT_USED_TRAPS;
			//clif_changelook(&src->bl,LOOK_BASE,sg->unit_id);
			sg->limit=DIFF_TICK(tick,sg->tick)+1500;
		}
		break;
	case UNT_CLUSTERBOMB:		/* クラスターボム */
		// 効果範囲(設置禁止領域)ではなく罠上に重なったら発動
		if(src->bl.m == bl->m && src->bl.x == bl->x && src->bl.y == bl->y){
			int ar = skill_get_area(sg->skill_id,sg->skill_lv);		// 効果範囲はskill_dbのarea参照
			map_foreachinarea(skill_trap_splash,src->bl.m,
						src->bl.x-ar,src->bl.y-ar,
						src->bl.x+ar,src->bl.y+ar,
						(BL_CHAR|BL_SKILL),src,tick,1);
			sg->unit_id = UNT_USED_TRAPS;
			clif_changelook(&src->bl,LOOK_BASE,sg->unit_id);
			sg->limit = DIFF_TICK(tick,sg->tick) + 1000;
		}
		break;
	case UNT_MAGMA_ERUPTION:	/* マグマイラプション */
		if(sg->skill_id == NC_MAGMA_ERUPTION)
			battle_skill_attack(BF_MISC,ss,&src->bl,bl,NC_MAGMA_ERUPTION_DOTDAMAGE,sg->skill_lv,tick,0x500);
		else
			battle_skill_attack(BF_MISC,ss,&src->bl,bl,NPC_MAGMA_ERUPTION_DOTDAMAGE,sg->skill_lv,tick,0x500);
		break;
	case UNT_MANHOLE:	/* マンホール */
		if(sg->val2 == 0) {
			int sec = skill_get_time2(sg->skill_id,sg->skill_lv) - status_get_agi(bl)*100;
			if(status_get_mode(bl)&MD_BOSS)
				sec /= 5;
			if(sec < 3000 + 30 * sg->skill_lv)
				sec = 3000 + 30 * sg->skill_lv;
			status_change_start(bl,GetSkillStatusChangeTable(sg->skill_id),sg->skill_lv,sg->bl.id,0,0,sec,0);
			unit_movepos(bl, src->bl.x, src->bl.y, 0);
			sg->limit    = DIFF_TICK(tick,sg->tick) + sec;
			sg->val2     = bl->id;
			sg->interval = -1;
			src->range   = 0;
		}
		break;
	case UNT_DIMENSIONDOOR:	/* ディメンションドア */
		if(bl->type == BL_PC)
			pc_randomwarp((struct map_session_data *)bl,3);
		else if(bl->type == BL_MOB)
			mob_warp((struct mob_data *)bl,-1,-1,-1,3);
		break;
	case UNT_CHAOSPANIC:	/* カオスパニック */
		if(sc && sc->data[SC_CONFUSION].timer == -1)
			status_change_pretimer(bl,SC_CONFUSION,7,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0,tick+status_get_amotion(ss));
		break;
	case UNT_SEVERE_RAINSTORM:	/* シビアレインストーム */
		battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,WM_SEVERE_RAINSTORM_MELEE,sg->skill_lv,tick,0);
		break;
	case UNT_REVERBERATION:		/* 振動残響 */
		{
			int ar = skill_get_area(sg->skill_id,sg->skill_lv);		// 効果範囲はskill_dbのarea参照
			int splash_count = map_foreachinarea(skill_count_target,src->bl.m,
						src->bl.x-ar,src->bl.y-ar,
						src->bl.x+ar,src->bl.y+ar,
						(BL_CHAR|BL_SKILL),src);
			map_foreachinarea(skill_trap_splash,src->bl.m,
						src->bl.x-ar,src->bl.y-ar,
						src->bl.x+ar,src->bl.y+ar,
						(BL_CHAR|BL_SKILL),src,tick,splash_count);
			sg->unit_id = UNT_USED_TRAPS;
			clif_changelook(&src->bl,LOOK_BASE,sg->unit_id);
			sg->limit=DIFF_TICK(tick,sg->tick)+1500;
		}
		break;
	case UNT_POEMOFNETHERWORLD:	/* 地獄の歌 */
		if(sg->val2 == 0 && !(status_get_mode(bl)&MD_BOSS)) {
			int sec = skill_get_time2(sg->skill_id,sg->skill_lv) - status_get_agi(bl)*100;
			if(sec < 3000 + 30 * sg->skill_lv)
				sec = 3000 + 30 * sg->skill_lv;
			status_change_start(bl,GetSkillStatusChangeTable(sg->skill_id),sg->skill_lv,sg->bl.id,0,0,sec,0);
			sg->limit    = DIFF_TICK(tick,sg->tick) + sec;
			sg->val2     = bl->id;
			sg->interval = -1;
			src->range   = 0;
		}
		break;
	case UNT_FIREWALK:		/* ファイアーウォーク */
	case UNT_ELECTRICWALK:	/* エレクトリックウォーク */
		battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		if(--src->val1 <= 0)
			skill_delunit(src);
		break;
	case UNT_WARMER:	/* ウォーマー */
		if(sc && sc->data[GetSkillStatusChangeTable(sg->skill_id)].timer == -1)
			status_change_start(bl,GetSkillStatusChangeTable(sg->skill_id),sg->skill_lv,0,0,0,sg->limit,0);
		if(bl->type == BL_PC) {
			struct map_session_data *sd = (struct map_session_data *)bl;

			if(sd->status.hp < sd->status.max_hp) {
				int hp = sd->status.max_hp * sg->skill_lv / 100;
				if(sd->status.hp + hp > sd->status.max_hp) {
					hp = sd->status.max_hp - sd->status.hp;
				}
				if(hp > 0) {
					if(sc && sc->data[SC_AKAITSUKI].timer != -1) {
						unit_fixdamage(ss,bl,tick,0,status_get_dmotion(bl),hp,0,0,0,0);
					} else {
						sd->status.hp += hp;
						clif_heal(sd->fd,SP_HP,hp);
					}
				}
			}
		}
		status_change_end(bl,SC_DIAMONDDUST,-1);// 冷凍
		status_change_end(bl,SC_FREEZE,-1);		// 凍結
		status_change_end(bl,SC_FROSTMISTY,-1);	// 氷結
		break;
	case UNT_VACUUM_EXTREME:	/* バキュームエクストリーム */
		{
			int sec = skill_get_time(sg->skill_id,sg->skill_lv) - status_get_str(bl)*100;
			if(status_get_mode(bl)&MD_BOSS)
				sec /= 5;
			// 最低拘束時間補償
			if(sec < 3000 + 30 * sg->skill_lv)
				sec = 3000 + 30 * sg->skill_lv;
			status_change_start(bl,GetSkillStatusChangeTable(sg->skill_id),sg->skill_lv,sg->bl.id,0,0,sec,0);
			if(!(status_get_mode(bl)&MD_BOSS) && !map[bl->m].flag.gvg && bl->x != src->bl.x && bl->y != src->bl.y)
				unit_movepos(bl, src->bl.x, src->bl.y, 0);
			//sg->limit=DIFF_TICK(tick,sg->tick)+sec;
		}
		break;
	case UNT_THORNS_TRAP:		/* ソーントラップ */
		if(sg->val2 == 0 && (!sc || sc->data[GetSkillStatusChangeTable(sg->skill_id)].timer == -1)) {
			int sec = skill_get_time2(sg->skill_id,sg->skill_lv);
			if(status_get_mode(bl)&MD_CANMOVE)
				unit_movepos(bl, src->bl.x, src->bl.y, 0);
			status_change_start(bl,GetSkillStatusChangeTable(sg->skill_id),sg->skill_lv,sg->bl.id,0,0,sec,0);
			sg->limit    = DIFF_TICK(tick,sg->tick) + sec;
			sg->val2     = bl->id;
		}
		else if(sc && sc->data[SC_THORNS_TRAP].timer != -1 && bl->id == sg->val2) {
			battle_skill_attack(BF_MISC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		}
		break;
	case UNT_WALLOFTHORN:	/* ソーンウォール */
		if(!(status_get_mode(bl)&MD_BOSS))
			battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		break;
	case UNT_DEMONIC_FIRE:	/* デモニックファイアー */
		battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,sg->val2);
		break;
	case UNT_FIRE_EXPANSION_SMOKE_POWDER:	/* ファイアーエクスパンション(煙幕) */
		if(sc && sc->data[SC_FIRE_EXPANSION_SMOKE_POWDER].timer == -1)
			status_change_start(bl,SC_FIRE_EXPANSION_SMOKE_POWDER,sg->skill_lv,0,0,0,skill_get_time(GN_FIRE_EXPANSION_SMOKE_POWDER,sg->skill_lv),0);
		break;
	case UNT_FIRE_EXPANSION_TEAR_GAS:		/* ファイアーエクスパンション(催涙ガス) */
		if(sc && sc->data[SC_FIRE_EXPANSION_TEAR_GAS].timer == -1)
			status_change_start(bl,SC_FIRE_EXPANSION_TEAR_GAS,sg->skill_lv,0,0,0,skill_get_time(GN_FIRE_EXPANSION_TEAR_GAS,sg->skill_lv),0);
		break;
	case UNT_HELLS_PLANT:	/* ヘルズプラント */
		battle_skill_attack(BF_MISC,ss,&src->bl,bl,GN_HELLS_PLANT_ATK,sg->skill_lv,tick,0);
		skill_delunit(src);
		break;
	case UNT_FIRE_MANTLE:	/* ファイアーマントル */
		do {
			battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		} while((--src->val2) > 0 && !unit_isdead(bl) && bl->x == src->bl.x && bl->y == src->bl.y);
		if (src->val2 <= 0)
			skill_delunit(src);
		break;
	case UNT_MAKIBISHI:	/* 撒菱 */
		unit_fixdamage(ss,bl,tick,0,status_get_dmotion(bl),20*sg->skill_lv,0,0,0,0);
		skill_delunit(src);
		break;
	case UNT_ZENKAI_WATER:	/* 術式全開(水属性) */
	case UNT_ZENKAI_GROUND:	/* 術式全開(地属性) */
	case UNT_ZENKAI_FIRE:	/* 術式全開(火属性) */
	case UNT_ZENKAI_WIND:	/* 術式全開(風属性) */
		// 敵ならユニットに応じて状態異常を付与する
		if( battle_check_target(&src->bl,bl,BCT_ENEMY) > 0 ) {
			switch(sg->unit_id) {
				case UNT_ZENKAI_WATER:	/* 術式全開(水属性) */
					switch(atn_rand()%3) {
					case 0:	// 凍結
						if(atn_rand() % 10000 < status_change_rate(bl,SC_FREEZE,10000,status_get_lv(&src->bl)))
							status_change_pretimer(bl,SC_FREEZE,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					case 1:	// 氷結
						status_change_pretimer(bl,SC_FROSTMISTY,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					case 2:	// 冷凍
						status_change_pretimer(bl,SC_DIAMONDDUST,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					}
					break;
				case UNT_ZENKAI_GROUND:	/* 術式全開(地属性) */
					switch(atn_rand()%2) {
					case 0:	// 石化
						if(atn_rand() % 10000 < status_change_rate(bl,SC_STONE,10000,status_get_lv(&src->bl)))
							status_change_pretimer(bl,SC_STONE,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					case 1:	// 毒
						if(atn_rand() % 10000 < status_change_rate(bl,SC_POISON,10000,status_get_lv(&src->bl)))
							status_change_pretimer(bl,SC_POISON,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					}
					break;
				case UNT_ZENKAI_FIRE:	/* 術式全開(火属性) */
					// 発火
					status_change_pretimer(bl,SC_HELLINFERNO,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
					break;
				case UNT_ZENKAI_WIND:	/* 術式全開(風属性) */
					switch(atn_rand()%3) {
					case 0:	// 沈黙
						if(atn_rand() % 10000 < status_change_rate(bl,SC_SILENCE,10000,status_get_lv(&src->bl)))
							status_change_pretimer(bl,SC_SILENCE,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					case 1:	// 睡眠
						if(atn_rand() % 10000 < status_change_rate(bl,SC_SLEEP,10000,status_get_lv(&src->bl)))
							status_change_pretimer(bl,SC_SLEEP,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					case 2:	// 深い睡眠
						status_change_pretimer(bl,SC_DEEP_SLEEP,sg->skill_lv,0,0,0,30000,0,tick+status_get_amotion(&src->bl));
						break;
					}
					break;
			}
		}
		break;
	case UNT_B_TRAP:		/* バインドトラップ */
		if(sg->src_id == bl->id || (status_get_mode(bl)&MD_BOSS))
			break;
		if(sc && sc->data[GetSkillStatusChangeTable(sg->skill_id)].timer == -1 && battle_check_target(&src->bl, bl, BCT_ENEMY) > 0)
			status_change_start(bl,GetSkillStatusChangeTable(sg->skill_id),sg->skill_lv,sg->bl.id,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		break;
	case UNT_FIRE_RAIN:		/* ファイアーレイン */
		battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0x500);
		break;
	case UNT_CATNIPPOWDER:	/* イヌハッカシャワー */
		if(sg->src_id == bl->id || (status_get_mode(bl)&MD_BOSS))
			break;
		if(sc && sc->data[GetSkillStatusChangeTable(sg->skill_id)].timer == -1 && battle_check_target(&src->bl, bl, BCT_ENEMY) > 0)
			status_change_start(bl,GetSkillStatusChangeTable(sg->skill_id),sg->skill_lv,0,0,0,sg->limit,0);
		break;
	case UNT_NYANGGRASS:	/* ニャングラス */
		if(battle_check_target(&src->bl,bl,BCT_ENEMY) > 0) {
			if(sc && sc->data[SC_NYANGGRASS].timer == -1)
				status_change_start(bl,SC_NYANGGRASS,sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		}
		break;
	case UNT_VENOMFOG:	/* ベナムフォグ */
		if(battle_check_target(&src->bl,bl,BCT_ENEMY) > 0 && bl->type == BL_PC) {
			battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,NPC_VENOMFOG,sg->skill_lv,tick,0);
		} else if(bl->type == BL_MOB) {
			if(status_get_hp(bl) < status_get_max_hp(bl)) {
				clif_skill_nodamage(&src->bl,bl,AL_HEAL,sg->val1*sg->skill_lv,1);
				battle_heal(NULL,bl,sg->val1*sg->skill_lv,0,0);
			}
		}
		break;
	case UNT_CANE_OF_EVIL_EYE:		/* ケーンオブイビルアイ */
		// 初回ダメージが出ない？
		if(sg->val2 == 1 && battle_check_target(&src->bl,bl,BCT_ENEMY) > 0)
			battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,NPC_CANE_OF_EVIL_EYE,sg->skill_lv,tick,0x500);
		sg->val2 = 1;
 		break;
	case UNT_LAVA_SLIDE:			/* ラーヴァスライド */
		battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,MH_LAVA_SLIDE,sg->skill_lv,tick,0);
		if(--sg->val2 <= 0)
			skill_delunitgroup(sg);
		break;
	case UNT_VOLCANIC_ASH:		/* ボルカニックアッシュ */
		if(battle_check_target(&src->bl,bl,BCT_ENEMY) > 0) {
			if(sc && sc->data[SC_VOLCANIC_ASH].timer == -1)
				status_change_start(bl,SC_VOLCANIC_ASH,sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		}
		break;
	case UNT_CREATINGSTAR:	/* 創星の書 */
		battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0x500);
		status_change_start(bl,SC_CREATINGSTAR,sg->skill_lv,0,0,0,sg->interval+100,0);
		break;
	case UNT_VIOLENT_QUAKE:	/* バイオレントクエイク */
	case UNT_ALL_BLOOM:		/* オールブルーム */
		if(sg->val1 == 4) {		// クライマックスLv4：発動範囲内の敵を状態異常
			status_change_start(bl,GetSkillStatusChangeTable(sg->skill_id),sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		}
		break;
	case UNT_ASTRAL_STRIKE:		/* アストラルストライク */
		if(DIFF_TICK(tick,sg->tick) >= 500) {	// 設置直後は攻撃なし
			battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		}
		break;
	case UNT_ABYSS_SQUARE:		/* アビススクエア */
		{
			int ismaster = 0;
			struct skill_unit *su = (struct skill_unit *)(sg->unit);
			if(su) {
				if(path_distance(su->bl.x,su->bl.y,ss->x,ss->y) <= src->range) {
					ismaster = 1;
				}
			}
			battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,ismaster);
		}
		break;
	case UNT_DEEPBLIND_TRAP:	/* ディープブラインドトラップ */
	case UNT_SOLID_TRAP:		/* ソリッドトラップ */
	case UNT_SWIFT_TRAP:		/* スイフトトラップ */
	case UNT_FLAME_TRAP:		/* フレイムトラップ */
		if(sc && sc->data[GetSkillStatusChangeTable(sg->skill_id)].timer != -1)
			break;
		battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		break;
	case UNT_ACIDIFIED_ZONE_WATER:		/* アシディファイドゾーン(水) */
	case UNT_ACIDIFIED_ZONE_GROUND:		/* アシディファイドゾーン(地) */
	case UNT_ACIDIFIED_ZONE_WIND:		/* アシディファイドゾーン(風) */
	case UNT_ACIDIFIED_ZONE_FIRE:		/* アシディファイドゾーン(火) */
	case UNT_FUUMASHOUAKU:				/* 風魔手裏剣 -掌握- */
		battle_skill_attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
		break;
	case UNT_TOTEM_OF_TUTELARY:			/* 城隍堂 */
		if(sg->val1%2 == 0 || sg->val1%3 == 0){
			struct map_session_data *sd = (struct map_session_data *)ss;
			int hp = 0;
			int sp = 0;
			if(sg->val1%2 == 0) {
				hp = skill_fix_heal(ss, bl, AL_HEAL, skill_calc_heal(ss, sg->skill_lv));
				hp += (1000 + sg->skill_lv * 4000 + status_get_crt(ss) * 5 + ((sd)? pc_checkskill(sd,SOA_TALISMAN_MASTERY) * sg->skill_lv * 50: 0)) * status_get_lv(ss) / 100;
			}
			if(sg->val1%3 == 0) {
				sp = (sg->skill_lv * 50 + status_get_crt(ss) * 5 + ((sd)? pc_checkskill(sd,SOA_TALISMAN_MASTERY) * sg->skill_lv * 5: 0)) * status_get_lv(ss) / 100;
			}
			unit_heal(bl,hp,sp,0,1);
		}
		break;
	case UNT_JACK_FROST_NOVA:		/* ジャックフロストノヴァ */
		battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,1);
		status_change_start(bl,GetSkillStatusChangeTable(sg->skill_id),sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		break;
	case UNT_GROUND_GRAVITATION:	/* グラウンドグラビテーション */
		battle_skill_attack(BF_MAGIC,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,2);
		status_change_start(bl,GetSkillStatusChangeTable(sg->skill_id),sg->skill_lv,0,0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		break;
	}

	if(bl->type == BL_MOB && ss != bl)	/* スキル使用条件のMOBスキル */
	{
		struct mob_data *md = (struct mob_data *)bl;
		int target = md->target_id;
		if(battle_config.mob_changetarget_byskill == 1 || target == 0)
		{
			if(ss->type & (BL_PC | BL_HOM | BL_MERC | BL_ELEM))
				md->target_id = ss->id;
		}
		mobskill_use(md,tick,MSC_SKILLUSED|(sg->skill_id<<16));
		md->target_id = target;
	}
	return 0;
}
