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
 * スキル使用（詠唱完了、ID指定攻撃系）
 *------------------------------------------
 */
int skill_castend_damage_id( struct block_list* src, struct block_list *bl,int skillid,int skilllv,unsigned int tick,int flag )
{
	struct map_session_data *sd  = NULL;
	struct mob_data         *md  = NULL;
	struct homun_data       *hd  = NULL;
	struct elem_data        *eld = NULL;
	struct status_change    *sc  = NULL;
	int is_enemy = 1;

	nullpo_retr(1, src);
	nullpo_retr(1, bl);

	if(bl->prev == NULL)
		return 1;
	if(unit_isdead(bl))
		return 1;

	sd  = BL_DOWNCAST( BL_PC,   src );
	md  = BL_DOWNCAST( BL_MOB,  src );
	hd  = BL_DOWNCAST( BL_HOM,  src );
	eld = BL_DOWNCAST( BL_ELEM, src );

	switch(skillid) {
		case CR_GRANDCROSS:
		case NPC_GRANDDARKNESS:
			if(src != bl)
				bl = src;
			break;
		case AS_GRIMTOOTH:
		case SN_SHARPSHOOTING:
		case GS_SPREADATTACK:
		case NJ_HUUMA:
		case NJ_BAKUENRYU:
		case NJ_KAMAITACHI:
		case MA_SHARPSHOOTING:
		case MO_EXTREMITYFIST:
		case TK_JUMPKICK:
		case SR_TIGERCANNON:
		case SR_GATEOFHELL:
			// skill_castend_idで許可したスキルはここで敵チェック
			if(skill_get_inf2(skillid) & INF2_ATTACK || skill_get_inf(skillid) & INF_ATTACK) {
				if(battle_check_target(src,bl,BCT_ENEMY) <= 0)
					is_enemy = 0;
			}
			break;
	}

	map_freeblock_lock();

	switch(skillid)
	{
	/* 武器攻撃系スキル */
	case SM_BASH:			/* バッシュ */
	case MC_MAMMONITE:		/* メマーナイト */
	case KN_PIERCE:			/* ピアース */
	case KN_SPEARBOOMERANG:	/* スピアブーメラン */
	case TF_POISON:			/* インベナム */
	case TF_SPRINKLESAND:	/* 砂まき */
	case AC_CHARGEARROW:	/* チャージアロー */
	case ASC_METEORASSAULT:	/* メテオアサルト */
	case RG_INTIMIDATE:		/* インティミデイト */
	case AM_ACIDTERROR:		/* アシッドテラー */
	case BA_MUSICALSTRIKE:	/* ミュージカルストライク */
	case DC_THROWARROW:		/* 矢撃ち */
	case BA_DISSONANCE:		/* 不協和音 */
	case CR_HOLYCROSS:		/* ホーリークロス */
	case CR_SHIELDCHARGE:
	case CR_SHIELDBOOMERANG:
	case NPC_PIERCINGATT:
	case NPC_MENTALBREAKER:
	case NPC_RANGEATTACK:
	case NPC_CRITICALSLASH:
	case NPC_COMBOATTACK:
	case NPC_POISON:
	case NPC_BLINDATTACK:
	case NPC_SILENCEATTACK:
	case NPC_STUNATTACK:
	case NPC_PETRIFYATTACK:
	case NPC_CURSEATTACK:
	case NPC_SLEEPATTACK:
	case NPC_RANDOMATTACK:
	case NPC_WATERATTACK:
	case NPC_GROUNDATTACK:
	case NPC_FIREATTACK:
	case NPC_WINDATTACK:
	case NPC_POISONATTACK:
	case NPC_HOLYATTACK:
	case NPC_DARKNESSATTACK:
	case NPC_TELEKINESISATTACK:
	case NPC_UNDEADATTACK:
	case NPC_WEAPONBRAKER:
	case NPC_ARMORBRAKE:
	case NPC_HELMBRAKE:
	case NPC_SHIELDBRAKE:
	case NPC_DARKCROSS:
	case LK_SPIRALPIERCE:		/* スパイラルピアース */
	case LK_HEADCRUSH:			/* ヘッドクラッシュ */
	case LK_JOINTBEAT:			/* ジョイントビート */
	case ASC_BREAKER:			/* ソウルブレイカー */
	case HW_MAGICCRASHER:		/* マジッククラッシャー */
	case PA_SHIELDCHAIN:		/* シールドチェイン */
	case WS_CARTTERMINATION:	/* カートターミネーション */
	case CR_ACIDDEMONSTRATION:	/* アシッドデモンストレーション */
	case ITM_TOMAHAWK:			/* トマホーク投げ */
	case AS_VENOMKNIFE:			/* ベナムナイフ */
	case HT_PHANTASMIC:			/* ファンタズミックアロー */
	case CH_TIGERFIST:		/* 伏虎拳 */
	case CH_CHAINCRUSH:		/* 連柱崩撃 */
	case TK_DOWNKICK:	/* ネリョチャギ */
	case TK_COUNTER:	/* アプチャオルリギ */
	case GS_FLING:			/* フライング */
	case GS_TRIPLEACTION:	/* トリプルアクション */
	case GS_BULLSEYE:		/* ブルズアイ */
	case GS_MAGICALBULLET:	/* マジカルバレット */
	case GS_TRACKING:		/* トラッキング */
	case GS_RAPIDSHOWER:	/* ラピッドシャワー */
	case GS_DUST:			/* ダスト */
	case GS_PIERCINGSHOT:	/* ピアーシングショット */
	case GS_FULLBUSTER:		/* フルバスター */
	case NJ_SYURIKEN:		/* 手裏剣投げ */
	case NJ_KUNAI:			/* 苦無投げ */
	case NJ_ZENYNAGE:		/* 銭投げ */
	case NJ_KASUMIKIRI:		/* 霞斬り */
	case HFLI_MOON:
	case HFLI_SBR44:
	case NPC_BLEEDING:		/* 出血攻撃 */
	case NPC_CRITICALWOUND:		/* 致命傷攻撃 */
	case NPC_EXPULSION:		/* エクスパルシオン */
	case NPC_DRAGONBREATH:	/* Mドラゴンブレス */
	case MS_BASH:
	case MA_CHARGEARROW:
	case ML_PIERCE:
	case ML_SPIRALPIERCE:
	case MER_CRASH:			/* クラッシュ */
	case RK_SONICWAVE:			/* ソニックウェーブ */
	case RK_DRAGONBREATH:	/* ファイアードラゴンブレス */
	case RK_DRAGONBREATH_WATER:	/* ウォータードラゴンブレス */
	case AB_DUPLELIGHT_MELEE:	/* グレイアムライト */
	case RA_WUGBITE:		/* ウォーグバイト */
	case NC_BOOSTKNUCKLE:	/* ブーストナックル */
	case NC_PILEBUNKER:		/* パイルバンカー */
	case NC_COLDSLOWER:		/* コールドスローワー */
	case NC_AXEBOOMERANG:	/* アックスブーメラン */
	case NC_MAGMA_ERUPTION:	/* マグマイラプション */
	case NPC_MAGMA_ERUPTION:	/* Mマグマイラプション */
	case LG_BANISHINGPOINT:	/* バニシングポイント */
	case LG_SHIELDPRESS:	/* シールドプレス */
	case LG_OVERBRAND:		/* オーバーブランド */
	case LG_HESPERUSLIT:	/* ヘスペルスリット */
	case SR_DRAGONCOMBO:	/* 双龍脚 */
	case SR_FALLENEMPIRE:	/* 大纏崩捶 */
	case SR_RIDEINLIGHTNING:	/* 雷光弾 */
	case WM_GREAT_ECHO:		/* グレートエコー */
	case GN_DEMONIC_FIRE:	/* デモニックファイアー */
	case GN_FIRE_EXPANSION_ACID:	/* ファイアーエクスパンション(塩酸) */
	case GN_SLINGITEM_RANGEMELEEATK:	/* スリングアイテム(遠距離攻撃) */
	case KO_SETSUDAN:		/* 霊魂絶断 */
	case EL_WIND_SLASH:		/* ウィンドスラッシュ */
	case EL_STONE_HAMMER:	/* ストーンハンマー */
	case NPC_DISSONANCE:
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case NPC_GUIDEDATTACK:	/* ガイデッドアタック */
		status_change_start(src,SC_INCHIT,status_get_dex(src)/2,0,0,0,skill_get_time(skillid,skilllv),0);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case KN_BRANDISHSPEAR:		/* ブランディッシュスピア */
	case ML_BRANDISH:
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		skill_area_temp[1]++;
		break;
	case AC_DOUBLE:			/* ダブルストレイフィング */
	case MA_DOUBLE:
		status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case GS_DISARM:			/* ディスアーム */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case AS_SONICBLOW:		/* ソニックブロー */
	case CG_ARROWVULCAN:		/* アローバルカン */
	case GC_CROSSIMPACT:	/* クロスインパクト */
		{
			struct unit_data *ud = unit_bl2ud(src);
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			if(ud) {
				// スキルモーションディレイは最大で3秒くらい？
				int delay = status_get_adelay(src);
				ud->canmove_tick = tick + ( (delay>2000)? 3000: 6000*1000/(4000-delay) );
			}
		}
		break;
	case HT_POWER:			/* ピーストストレイフィング*/
		status_change_end(src,SC_DOUBLE,-1);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case MO_INVESTIGATE:	/* 発勁 */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		sc = status_get_sc(src);
		if(sc && sc->data[SC_BLADESTOP].timer != -1)
			status_change_end(src,SC_BLADESTOP,-1);
		break;
	case RG_RAID:			/* サプライズアタック */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
#ifndef PRE_RENEWAL
		status_change_start(bl,SC_RAID,7,0,0,0,skill_get_time(skillid,skilllv),0 );
#endif
		break;
	case RG_BACKSTAP:		/* バックスタブ */
		{
			int dir   = path_calc_dir(src,bl->x,bl->y);
			int t_dir = status_get_dir(bl);
			int dist  = unit_distance(src,bl);
			if((dist > 0 && !path_check_dir(dir,t_dir)) || bl->type == BL_SKILL) {
				sc = status_get_sc(src);
				if(sc && sc->data[SC_HIDING].timer != -1)
					status_change_end(src, SC_HIDING, -1);	// ハイディング解除
				if(battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag)>0) { // 攻撃を受けた目標は振り向く
					unit_setdir(bl, path_calc_dir(bl,src->x,src->y));
				}
			} else if(sd) {
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
			}
		}
		break;
	case MO_FINGEROFFENSIVE:	/* 指弾 */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		if(md && !mob_is_pcview(md->class_)) {
			// 見た目がPCでない場合は何故か姿が消えてしまうので抑制する
			clif_skill_nodamage(src,src,skillid,skilllv,1);
		}
		if(battle_config.finger_offensive_type && sd) {
			int i;
			for(i=1; i<sd->spiritball.old; i++)
				skill_addtimerskill(src,tick+i*200,bl->id,0,0,skillid,skilllv,BF_WEAPON,flag);
			sd->ud.canmove_tick = tick + (sd->spiritball.old-1)*200;
		}
		sc = status_get_sc(src);
		if(sc && sc->data[SC_BLADESTOP].timer != -1)
			status_change_end(src,SC_BLADESTOP,-1);
		break;
	case MO_CHAINCOMBO:		/* 連打掌 */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		sc = status_get_sc(src);
		if(sc && sc->data[SC_BLADESTOP].timer != -1)
			status_change_end(src,SC_BLADESTOP,-1);
		break;
	case TK_STORMKICK:	/* フェオリチャギ */
		if(flag&1) {
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1]=src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			clif_skill_nodamage(src,src,skillid,skilllv,1);
		}
		break;

	case TK_TURNKICK:	/* トルリョチャギ */
		if(flag&1){
			/* 個別処理 */
			if(bl->id != skill_area_temp[1]) {
				struct block_list pos;
				memset(&pos,0,sizeof(pos));
				pos.m = bl->m;
				pos.x = skill_area_temp[2];
				pos.y = skill_area_temp[3];
				skill_blown(&pos,bl,skill_area_temp[4] | SAB_NODAMAGE);
				skill_additional_effect(src,bl,skillid,skilllv,BF_WEAPON,tick);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			skill_area_temp[2] = bl->x;
			skill_area_temp[3] = bl->y;
			skill_area_temp[4] = skill_get_blewcount(skillid,skilllv);
			/* まずターゲットに攻撃を加える */
			if(!battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0))
				break;
			/* その後ターゲット以外の範囲内のMOB全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,skill_area_temp[2]-ar,skill_area_temp[3]-ar,skill_area_temp[2]+ar,skill_area_temp[3]+ar,BL_MOB,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;

	case KN_CHARGEATK:	/* チャージアタック */
	case TK_JUMPKICK:	/* ティオアプチャギ */
	case NJ_ISSEN:		/* 一閃 */
		{
			int dist = unit_distance(src,bl);
			if(sd && (skillid != KN_CHARGEATK || battle_config.gvg_chargeattack_move || !map[sd->bl.m].flag.gvg)) {
				int dx = bl->x - sd->bl.x;
				int dy = bl->y - sd->bl.y;

				if(dx > 0) dx++;
				else if(dx < 0) dx--;
				if(dy > 0) dy++;
				else if(dy < 0) dy--;
				if(dx == 0 && dy == 0) dx++;
				if(path_search(NULL,src->m,sd->bl.x,sd->bl.y,sd->bl.x+dx,sd->bl.y+dy,1) == -1) {
					dx = bl->x - sd->bl.x;
					dy = bl->y - sd->bl.y;
					if(path_search(NULL,src->m,sd->bl.x,sd->bl.y,sd->bl.x+dx,sd->bl.y+dy,1) == -1) {
						clif_skill_fail(sd,sd->ud.skillid,SKILLFAIL_FAILED,0,0);
						break;
					}
				}
				sd->ud.to_x = sd->bl.x + dx;
				sd->ud.to_y = sd->bl.y + dy;
				clif_skill_poseffect(&sd->bl,skillid,skilllv,sd->bl.x,sd->bl.y,tick);
				if(skillid == TK_JUMPKICK)
					battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(is_enemy ? 0 : 0x01000000));
				else
					battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,dist);
				clif_walkok(sd);
				clif_move(&sd->bl);
				if(dx < 0) dx = -dx;
				if(dy < 0) dy = -dy;
				sd->ud.attackabletime = sd->ud.canmove_tick = tick + sd->speed * ((dx > dy)? dx:dy);
				if(sd->ud.canact_tick < sd->ud.canmove_tick)
					sd->ud.canact_tick = sd->ud.canmove_tick;
				unit_movepos(&sd->bl,sd->ud.to_x,sd->ud.to_y,0);
			} else {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,dist);
			}
			if(skillid == TK_JUMPKICK) {
				sc = status_get_sc(src);
				if(sc && sc->data[SC_RUN].timer != -1)
					status_change_end(src,SC_RUN,-1);
			}
		}
		break;
	case MO_COMBOFINISH:	/* 猛龍拳 */
		sc = status_get_sc(src);
		/* モンクの魂状態の場合は範囲攻撃 */
		if(sc && sc->data[SC_MONK].timer != -1) {
			if(flag&1) {
				if(bl->id != skill_area_temp[1])
					battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			} else {
				int ar = skill_get_area(skillid,skilllv);
				skill_area_temp[1] = bl->id;
				skill_area_temp[2] = bl->x;
				skill_area_temp[3] = bl->y;
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
				map_foreachinarea(skill_area_sub,
					src->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
					src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
					skill_castend_damage_id);
			}
		} else {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		}
		break;
	case CH_PALMSTRIKE:		/* 猛虎硬爬山 */
		clif_damage(src,bl,tick,status_get_amotion(src),0,-1,1,4,0,0);	// 攻撃モーションのみ入れる
		skill_addtimerskill(src,tick+1000,bl->id,0,0,skillid,skilllv,BF_WEAPON,flag);
		break;
	case MO_EXTREMITYFIST:	/* 阿修羅覇鳳拳 */
		{
			int dx = 0;
			int dy = 0;
			short dir = 0;

			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag|(is_enemy ? 0 : 0x01000000));
			if(!is_enemy && sd && sd->status.sp > 0) {
				sd->status.sp = 0;
				clif_updatestatus(sd, SP_SP);
			}
			if(sd) {
				sd->ud.attackabletime = sd->ud.canmove_tick = tick + 100 + sd->speed * ((dx > dy)? dx: dy);
				if(sd->ud.canact_tick < sd->ud.canmove_tick)
					sd->ud.canact_tick = sd->ud.canmove_tick;
			}
			status_change_end(src,SC_COMBO,-1);
			status_change_end(src, SC_EXPLOSIONSPIRITS, -1);
			sc = status_get_sc(src);
			if(sc && sc->data[SC_BLADESTOP].timer != -1) {
				status_change_end(src,SC_BLADESTOP,-1);
			}
			dir = path_calc_dir(src,bl->x,bl->y);
			if(dir > 0 && dir < 4) dx = -3;
			else if(dir > 4) dx = 3;
			if(dir > 2 && dir < 6) dy = -3;
			else if(dir == 7 || dir < 2) dy = 3;
			if(dx == 0 && dy == 0) dx = 1;
			if(!unit_movepos(src,src->x + dx,src->y + dy,1)) {
				if(dx > 0) dx = -1;
				else if(dx < 0) dx = 1;
				if(dy > 0) dy = -1;
				else if(dy < 0) dy = 1;

				unit_movepos(src,src->x + dx,src->y + dy,1);
			}
		}
		break;
	case NJ_KIRIKAGE:		/* 影斬り */
		{
			int dist = unit_distance(src,bl);
			if(sd && pc_checkskill(sd,NJ_SHADOWJUMP) * 2 + 5 >= dist) {
				int dx = bl->x - sd->bl.x;
				int dy = bl->y - sd->bl.y;

				if(dx > 0) dx++;
				else if(dx < 0) dx--;
				if(dy > 0) dy++;
				else if(dy < 0) dy--;
				if(dx == 0 && dy == 0) dx++;
				if(path_search(NULL,src->m,sd->bl.x,sd->bl.y,sd->bl.x+dx,sd->bl.y+dy,1) == -1) {
					dx = bl->x - sd->bl.x;
					dy = bl->y - sd->bl.y;
					if(path_search(NULL,src->m,sd->bl.x,sd->bl.y,sd->bl.x+dx,sd->bl.y+dy,1) == -1) {
						clif_skill_fail(sd,sd->ud.skillid,SKILLFAIL_FAILED,0,0);
						break;
					}
				}
				if(!map[src->m].flag.gvg) {
					sd->ud.to_x = sd->bl.x + dx;
					sd->ud.to_y = sd->bl.y + dy;
					clif_walkok(sd);
					clif_move(&sd->bl);
					if(dx < 0) dx = -dx;
					if(dy < 0) dy = -dy;
					sd->ud.attackabletime = sd->ud.canmove_tick = tick + sd->speed * ((dx > dy)? dx:dy);
					if(sd->ud.canact_tick < sd->ud.canmove_tick)
						sd->ud.canact_tick = sd->ud.canmove_tick;
					unit_movepos(&sd->bl,sd->ud.to_x,sd->ud.to_y,0);
				}
				else {
					if(status_get_range(src) < dist) {
						status_change_end(src, SC_HIDING, -1);	// ハイディング解除
						break;
					}
				}
				clif_skill_poseffect(&sd->bl,skillid,skilllv,sd->bl.x,sd->bl.y,tick);
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,dist);
			} else {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,dist);
			}
			status_change_end(src, SC_HIDING, -1);	// ハイディング解除
		}
		break;
	/* 武器系範囲攻撃スキル */
	case AC_SHOWER:			/* アローシャワー */
	case MA_SHOWER:
		{
			// 指定セルを攻撃中心にするためにsrcの代わりを用意する
			struct block_list pos;
			memset(&pos,0,sizeof(struct block_list));
			pos.m = bl->m;
			pos.x = skill_area_temp[2];
			pos.y = skill_area_temp[3];
			if( battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500) ) {
				int count = skill_get_blewcount(skillid,skilllv)|SAB_NOPATHSTOP;
				if(bl->x == pos.x && bl->y == pos.y)
					count |= 6<<20;		// 指定座標と同一なら西へノックバック
				skill_blown(&pos,bl,count);
			}
		}
		break;
	case SM_MAGNUM:			/* マグナムブレイク */
	case MS_MAGNUM:
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				int x = skill_area_temp[2], y = skill_area_temp[3];
				int type;
				if(path_distance(bl->x,bl->y,x,y) > 1)
					type = 1;	// 外周
				else
					type = 0;	// 内周
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500|type);
			}
		} else {
			int ar = (md && battle_config.monster_skill_over && skilllv >= battle_config.monster_skill_over)? 4: skill_get_area(skillid,skilllv);

			/* スキルエフェクト表示 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = src->x;
			skill_area_temp[3] = src->y;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			map_foreachinarea(skill_area_trap_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_SKILL,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,ELE_FIRE,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case NPC_SPLASHATTACK:	/* スプラッシュアタック */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			/* まずターゲットに攻撃を加える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			/* その後ターゲット以外の範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case AS_SPLASHER:		/* ベナムスプラッシャー */
		if(flag&1) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(0x0f<<20)|0x500|skill_area_temp[0]);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[0] = 0;
			//分散範囲は3x3 攻撃範囲は5x5
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar-1,bl->y-ar-1,bl->x+ar-1,bl->y+ar-1,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY,
				skill_area_sub_count);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case AS_GRIMTOOTH:		/* グリムトゥース */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			/* まずターゲットに攻撃を加える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(is_enemy ? 0 : 0x01000000));
			/* その後ターゲット以外の範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			map_foreachinarea(skill_area_trap_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_SKILL,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case MC_CARTREVOLUTION:	/* カートレボリューション */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id == skill_area_temp[1])
				break;
			if(battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500))
			{
				if(bl->x == skill_area_temp[2] && bl->y == skill_area_temp[3]) {
					skill_blown(src,bl,skill_area_temp[4]|(6<<20));		// ターゲットと同一座標なら西へノックバック
				} else {
					struct block_list pos;
					memset(&pos,0,sizeof(pos));
					pos.m = bl->m;
					pos.x = skill_area_temp[2];
					pos.y = skill_area_temp[3];
					skill_blown(&pos,bl,skill_area_temp[4]);		// ターゲットとの位置関係で飛ばす方向を決める
				}
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			int x = bl->x, y = bl->y;
			skill_area_temp[1] = bl->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			skill_area_temp[4] = skill_get_blewcount(skillid,skilllv);
			/* まずターゲットに攻撃を加える */
			if(battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0))
				skill_blown(src,bl,skill_area_temp[4]|(6<<20));		// 西に強制ノックバック

			/* その後ターゲット以外の範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case KN_BOWLINGBASH:	/* ボウリングバッシュ */
	case MS_BOWLINGBASH:
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id!=skill_area_temp[1]) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
			}
		} else {
			int i,c,dir;	/* 他人から聞いた動きなので間違ってる可能性大＆効率が悪いっす＞＜ */
			int ar = skill_get_area(skillid,skilllv);
			/* まずターゲットに攻撃を加える */
			if(!battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0))
				break;
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			c   = skill_get_blewcount(skillid,skilllv);
			dir = (status_get_dir(src)+4) & 0x07;
			if(dir == 0)
				dir = 8;
			if(map[bl->m].flag.gvg) c = 0;
			for(i=0; i<c; i++) {
				skill_blown(src,bl,(dir<<20)|SAB_NODAMAGE|1);
				skill_area_temp[0] = 0;
				map_foreachinarea(skill_area_sub,
					bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
					src,skillid,skilllv,tick, flag|BCT_ENEMY ,
					skill_area_sub_count);
				if(skill_area_temp[0] > 1)
					break;
			}
			unit_stop_walking(bl,2);	// 最後にダメージディレイを入れる
			skill_area_temp[1] = bl->id;
			/* その後ターゲット以外の範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case MO_BALKYOUNG:
		{
			int ar = skill_get_area(skillid,skilllv);
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			map_foreachinarea(skill_balkyoung,bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),src,bl);
		}
		break;
	case KN_SPEARSTAB:		/* スピアスタブ */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id == skill_area_temp[1])
				break;
			if(battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500))
				skill_blown(src,bl,skill_area_temp[2]);
		} else {
			int x = bl->x, y = bl->y;
			int i, dir = path_calc_dir(bl,src->x,src->y);
			if(dir == 0)
				dir = 8;
			skill_area_temp[1] = bl->id;
			skill_area_temp[2] = skill_get_blewcount(skillid,skilllv)|(dir<<20);
			if(map[bl->m].flag.gvg)
				skill_area_temp[2] = 0;
			/* まずターゲットに攻撃を加える */
			if(battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0))
				skill_blown(src,bl,skill_area_temp[2]);
			for(i=0; i<4; i++) {
				map_foreachinarea(skill_area_sub,bl->m,x,y,x,y,(BL_CHAR|BL_SKILL),
					src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
					skill_castend_damage_id);
				x += dirx[dir];
				y += diry[dir];
			}
		}
		break;
	case SN_SHARPSHOOTING:			/* シャープシューティング */
	case MA_SHARPSHOOTING:
		if(flag&1) {
			/* 個別にダメージを与える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(skill_area_temp[1] == 0 ? 0 : 0x0500));
			skill_area_temp[1]++;
		} else {
			int dir = path_calc_dir(src,bl->x,bl->y);
			skill_area_temp[1] = 0;
			map_foreachinshootpath(
				skill_area_sub,bl->m,src->x,src->y,dirx[dir],diry[dir],12,skill_get_area(skillid,skilllv),(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,skill_castend_damage_id
			);
			if(skill_area_temp[1] == 0) {
				/* ターゲットに攻撃 */
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(is_enemy ? 0 : 0x01000000));
			}
		}
		break;
	case GS_SPREADATTACK:	/* スプレッドアタック */
		if(flag&1) {
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(is_enemy ? 0 : 0x01000000));
			map_foreachinarea(skill_area_sub,
				src->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NJ_HUUMA:		/* 風魔手裏剣投げ */
		if(flag&1) {
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,skill_area_temp[0]);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[0] = 0;
			skill_area_temp[1] = bl->id;
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY,
				skill_area_sub_count);
			if( !battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,skill_area_temp[0]|(is_enemy ? 0 : 0x01000000)) )
				break;
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NPC_EARTHQUAKE:		/* アースクエイク */
		if(flag&1) {
			if(bl->id != skill_area_temp[1]) {
				skill_addtimerskill(src,tick+200,bl->id,0,0,skillid,skilllv,0,(0x0f<<20)|0x0500|skill_area_temp[0]);
				skill_addtimerskill(src,tick+400,bl->id,0,0,skillid,skilllv,0,(0x0f<<20)|0x0500|skill_area_temp[0]);
				skill_addtimerskill(src,tick+600,bl->id,0,0,skillid,skilllv,0,(0x0f<<20)|0x0500|skill_area_temp[0]);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[0] = 0;
			skill_area_temp[1] = bl->id;
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_PC|BL_MOB),
				src,skillid,skilllv,tick,flag|BCT_ENEMY,
				skill_area_sub_count);
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_PC|BL_MOB),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NPC_FIREBREATH:		/* ファイアブレス */
	case NPC_ICEBREATH:		/* アイスブレス */
	case NPC_THUNDERBREATH:		/* サンダーブレス */
	case NPC_ACIDBREATH:		/* アシッドブレス */
	case NPC_DARKNESSBREATH:	/* ダークネスブレス */
		if(flag&1) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
		} else {
			int dir = path_calc_dir(src,bl->x,bl->y);
			map_foreachinshootpath(
				skill_area_sub,bl->m,src->x,src->y,dirx[dir],diry[dir],14,skill_get_area(skillid,skilllv),(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,skill_castend_damage_id
			);
		}
		break;
	case NPC_PULSESTRIKE:		/* パルスストライク */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				if(battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0))
					skill_blown(src,bl,skill_area_temp[2]);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			skill_area_temp[2] = skill_get_blewcount(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NPC_HELLJUDGEMENT:		/* ヘルジャッジメント */
	case NPC_HELLJUDGEMENT2:		/* デモニックヘルジャッジメント */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NPC_VAMPIRE_GIFT:		/* ヴァンパイアリックタッチ */
		if(flag&1) {
			/* 個別にダメージを与える */
			int heal = battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			if(heal) {
				clif_skill_nodamage(src,src,AL_HEAL,heal,1);
				battle_heal(NULL,src,heal,0,0);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NPC_PULSESTRIKE2:		/* パルスストライクII */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				if(battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(0x0f<<20)))
					skill_blown(src,bl,skill_area_temp[2]);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_poseffect(src,skillid,-1,src->x,src->y,tick);
			skill_area_temp[1] = bl->id;
			skill_area_temp[2] = skill_get_blewcount(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NPC_DANCINGBLADE:		/* ダンシングブレイド */
		clif_skill_poseffect(src,skillid,-1,bl->x,bl->y,tick);
		skill_addtimerskill(src,tick+150,bl->id,0,0,NPC_DANCINGBLADE_ATK,skilllv,1,(0x0f<<20)|flag);
		break;
	case NPC_DARKPIERCING:		/* ダークピアーシング */
		if(flag&1) {
			/* 個別にダメージを与える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(skill_area_temp[1] == 0 ? 0 : 0x500));
			skill_area_temp[1]++;
		} else {
			int dir = path_calc_dir(src,bl->x,bl->y);
			skill_area_temp[1] = 0;
			map_foreachinshootpath(
				skill_area_sub,bl->m,src->x,src->y,dirx[dir],diry[dir],14,skill_get_area(skillid,skilllv),(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,skill_castend_damage_id
			);
			if(skill_area_temp[1] == 0) {
				/* ターゲットに攻撃 */
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			}
		}
		break;
	case NPC_VENOMIMPRESS:		/* Mベナムインプレス */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = src->x;
			skill_area_temp[3] = src->y;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NPC_IGNITIONBREAK:	/* Mイグニッションブレイク */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* スキルエフェクト表示 */
			clif_skill_nodamage(src, src, skillid, skilllv, 1);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = src->x;
			skill_area_temp[3] = src->y;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NPC_POISON_BUSTER:		/* Mポイズンバスター */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,0x0500);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			/* ターゲットに攻撃を加える(スキルエフェクト表示) */
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			/* ターゲット以外の範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NPC_WIDECRITICALWOUND:		/* ワイドクリティカルウーンズ */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x500);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = src->id;
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NPC_KILLING_AURA:	/* キリングオーラ */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				battle_skill_attack(BF_MISC,src,src,bl,skillid,skilllv,tick,0x0500);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_PC,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;

	/* 魔法系スキル */
	case MG_SOULSTRIKE:			/* ソウルストライク */
	case NPC_DARKSTRIKE:		/* ダークストライク */
	case MG_COLDBOLT:			/* コールドボルト */
	case MG_FIREBOLT:			/* ファイアーボルト */
	case MG_LIGHTNINGBOLT:		/* ライトニングボルト*/
	case WZ_EARTHSPIKE:			/* アーススパイク */
	case AL_HEAL:				/* ヒール */
	case AL_HOLYLIGHT:			/* ホーリーライト */
	case WZ_JUPITEL:			/* ユピテルサンダー */
	case NPC_DARKTHUNDER:		/* ダークサンダー */
	case NPC_MAGICALATTACK:		/* 魔法打撃攻撃 */
	case PR_ASPERSIO:			/* アスペルシオ */
	case NJ_KOUENKA:			/* 紅炎華 */
	case NJ_HYOUSENSOU:			/* 氷閃槍 */
	case NJ_HUUJIN:				/* 風刃 */
	case AB_RENOVATIO:			/* レノヴァティオ */
	case AB_HIGHNESSHEAL:		/* ハイネスヒール */
	case AB_ADORAMUS:			/* アドラムス */
	case AB_DUPLELIGHT_MAGIC:	/* ミリアムライト */
	case WL_TETRAVORTEX_FIRE:	/* テトラボルテックス(火) */
	case WL_TETRAVORTEX_WATER:	/* テトラボルテックス(水) */
	case WL_TETRAVORTEX_WIND:	/* テトラボルテックス(風) */
	case WL_TETRAVORTEX_GROUND:	/* テトラボルテックス(地) */
	case LG_RAYOFGENESIS:		/* レイオブジェネシス */
	case WM_METALICSOUND:		/* メタリックサウンド */
	case EL_FIRE_ARROW:			/* ファイアーアロー */
	case EL_ICE_NEEDLE:			/* アイスニードル */
	case NPC_RAYOFGENESIS:		/* Mレイオブジェネシス */
	case IG_JUDGEMENT_CROSS:	/* ジャッジメントクロス */
		battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case ALL_RESURRECTION:		/* リザレクション */
	case PR_TURNUNDEAD:			/* ターンアンデッド */
		if(battle_check_undead(status_get_race(bl),status_get_elem_type(bl))) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			map_freeblock_unlock();
			return 1;
		}
		break;
	case HVAN_CAPRICE:		/* カプリス */
		{
			static const int caprice[4] = { MG_COLDBOLT,MG_FIREBOLT,MG_LIGHTNINGBOLT,WZ_EARTHSPIKE};
			battle_skill_attack(BF_MAGIC,src,src,bl,caprice[atn_rand()%4],skilllv,tick,flag);
			clif_skill_nodamage(src,src,skillid,skilllv,1);
		}
		break;
	case CG_TAROTCARD:		/* 運命のタロットカード */
		sc = status_get_sc(bl);
		if(sc && sc->data[SC_TRICKDEAD].timer != -1) {
			if(sd)
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
			break;
		}
		skill_tarot_card_of_fate(src,bl,skillid,skilllv,tick,0);
		break;
	case MG_FROSTDIVER:		/* フロストダイバー */
		{
			int damage;

			sc = status_get_sc(bl);
			if(sc && sc->data[SC_FREEZE].timer != -1) {
				battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				break;
			}
			damage = battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			if(status_get_hp(bl) > 0 && damage > 0 && atn_rand() % 10000 < status_change_rate(bl,SC_FREEZE,skilllv*300+3500,status_get_lv(src))) {
				status_change_pretimer(bl,SC_FREEZE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
			} else if(sd) {
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
			}
		}
		break;
	case WZ_WATERBALL:			/* ウォーターボール */
		battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		if(skilllv > 1) {
			int cnt, range;
			range = (skilllv > 5)? 2: skilllv / 2;
			if(sd && !map[sd->bl.m].flag.rain)
				cnt = skill_count_water(src,range) - 1;
			else
				cnt = skill_get_num(skillid,skilllv) - 1;
			if(cnt > 0)
				skill_addtimerskill(src,tick+150,bl->id,0,0,skillid,skilllv,cnt,flag);
		}
		break;

	case PR_BENEDICTIO:			/* 聖体降福 */
		{
			int race = status_get_race(bl);
			if(battle_check_undead(race,status_get_elem_type(bl)) || race == RCT_DEMON) {
				if(bl->type == BL_MOB || !map[bl->m].flag.normal)
					battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			}
		}
		break;

	case SL_SMA:				/* エスマ */
	case SL_STUN:				/* エストン */
	case SL_STIN:				/* エスティン */
		if(sd && bl->type != BL_MOB && !battle_config.allow_es_magic_all)
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		else
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		break;

	/* 魔法系範囲攻撃スキル */
	case MG_NAPALMBEAT:			/* ナパームビート */
	case MG_FIREBALL:			/* ファイアーボール */
	case WZ_SIGHTRASHER:		/* サイトラッシャー */
	case HW_NAPALMVULCAN:		/* ナパームバルカン */
	case AB_JUDEX:				/* ジュデックス */
	case WL_SOULEXPANSION:		/* ソウルエクスパンション */
	case SO_POISON_BUSTER:		/* ポイズンバスター */
	case SO_VARETYR_SPEAR:		/* ヴェラチュールスピア */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				int count;
				if(skillid == MG_FIREBALL) {
					/* ファイアーボールなら中心からの距離を計算 */
					count = path_distance(bl->x,bl->y,skill_area_temp[2],skill_area_temp[3]);
				} else {
					count = skill_area_temp[0];
				}
				if(skillid != HW_NAPALMVULCAN && skillid != AB_JUDEX && skillid != WL_SOULEXPANSION && skillid != WL_CRIMSONROCK)
					count |= 0x0500;
				battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,count);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			int srcflg = 0;
			skill_area_temp[0] = 0;
			skill_area_temp[1] = bl->id;
			switch (skillid) {
				case MG_NAPALMBEAT:
				case HW_NAPALMVULCAN:
					/* ナパームビート・ナパームバルカンは分散ダメージなので敵の数を数える */
					map_foreachinarea(skill_area_sub,
							bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
							src,skillid,skilllv,tick,flag|BCT_ENEMY,
							skill_area_sub_count);
					break;
				case MG_FIREBALL:
				case AB_JUDEX:				/* ジュデックス */
				case WL_SOULEXPANSION:		/* ソウルエクスパンション */
				case SO_POISON_BUSTER:	/* ポイズンバスター */
				case SO_VARETYR_SPEAR:	/* ヴェラチュールスピア */
					skill_area_temp[2] = bl->x;
					skill_area_temp[3] = bl->y;
					break;
				case WZ_SIGHTRASHER:
					srcflg = 1;
					bl = src;
					status_change_end(src,SC_SIGHT,-1);
					break;
			}
			if(srcflg) {
				/* スキルエフェクト表示 */
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
			} else {
				/* ターゲットに攻撃を加える(スキルエフェクト表示) */
				battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,skill_area_temp[0]);
			}
			/* ターゲット以外の範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			if(skillid == WZ_SIGHTRASHER)
				map_foreachinarea(skill_area_trap_sub,
					bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_SKILL,
					src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
					skill_castend_damage_id);
		}
		break;
	case WZ_FROSTNOVA:			/* フロストノヴァ */
		bl = src;
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_castend_pos2(src,bl->x,bl->y,skillid,skilllv,tick,0);
		break;

	case NJ_HYOUSYOURAKU:		/* 氷柱落し */
		bl = src;
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_castend_pos2(src,bl->x,bl->y,skillid,skilllv,tick,0);
		break;

	case NJ_RAIGEKISAI:			/* 雷撃砕 */
		bl = src;
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_castend_pos2(src,bl->x,bl->y,skillid,skilllv,tick,0);
		break;

	case NJ_KAMAITACHI:			/* 朔風 */
		if(flag&1) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,(skill_area_temp[1] == 0 ? 0 : flag));
			skill_area_temp[1]++;
		} else {
			int dir = path_calc_dir(src,bl->x,bl->y);
			skill_area_temp[1] = 0;
			map_foreachinshootpath(
				skill_area_sub,bl->m,src->x,src->y,dirx[dir],diry[dir],skill_get_fixed_range(src,skillid,skilllv),skill_get_area(skillid,skilllv),
				(BL_CHAR|BL_SKILL),src,skillid,skilllv,tick,flag|BCT_ENEMY|1,skill_castend_damage_id
			);
			if(skill_area_temp[1] == 0) {
				battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,(is_enemy ? 0 : 0x01000000));
			}
		}
		break;

	/* その他 */
	case TF_THROWSTONE:			/* 石投げ */
	case PA_PRESSURE:			/* プレッシャー */
	case SN_FALCONASSAULT:			/* ファルコンアサルト */
	case GN_HELLS_PLANT_ATK:	/* ヘルズプラント */
	case NPC_DARKBREATH:
		battle_skill_attack(BF_MISC,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case HT_BLITZBEAT:			/* ブリッツビート */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_MISC,src,src,bl,skillid,skilllv,tick,skill_area_temp[0]|(flag&0xf00000));
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[0] = 0;
			skill_area_temp[1] = bl->id;
			if(flag&0xf00000) {
				map_foreachinarea(skill_area_sub,bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
					src,skillid,skilllv,tick, flag|BCT_ENEMY,skill_area_sub_count);
			}
			/* まずターゲットに攻撃を加える */
			battle_skill_attack(BF_MISC,src,src,bl,skillid,skilllv,tick,skill_area_temp[0]|(flag&0xf00000));
			/* その後ターゲット以外の範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			map_foreachinarea(skill_area_trap_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_SKILL,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;

	case CR_GRANDCROSS:			/* グランドクロス */
	case NPC_GRANDDARKNESS:			/* グランドダークネス */
		{
			struct unit_data *ud = unit_bl2ud(src);
			if(status_check_no_magic_damage(src))
				break;
			status_change_start(src,SC_STRIPSHIELD,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			/* スキルユニット配置 */
			skill_castend_pos2(src,bl->x,bl->y,skillid,skilllv,tick,0);
			if(ud)
				ud->canmove_tick = tick + 900;
		}
		break;
	case PF_SOULBURN:		/* ソウルバーン */
		if(bl->type == BL_PC) {
			struct block_list *dstbl;
			int sp, rate;
			if(status_check_no_magic_damage(bl))
				break;
			if(sd && !map[sd->bl.m].flag.pvp && !map[sd->bl.m].flag.gvg && !map[sd->bl.m].flag.pk)
				break;
			rate = (skilllv >= 5)? 70: 10 * skilllv + 30;
			if(atn_rand() % 100 >= rate) {
				dstbl = src;	// 自分に対してダメージ
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
			} else {
				dstbl = bl;
			}
			clif_skill_nodamage(src,dstbl,skillid,skilllv,1);
			sp = status_get_sp(dstbl);
			// SPを0にする
			if(dstbl->type == BL_PC)
				unit_heal(dstbl,0,-sp,0,0);
			if(skilllv >= 5) {
				// SP*2のダメージを与える(MDEFで計算)
				int damage = sp * 2 * (100 - status_get_mdef(dstbl)) / 100 - status_get_mdef2(dstbl);
				if(damage < 1)
					damage = 1;
				battle_damage(src,dstbl,damage,skillid,skilllv,0);
			}
			if(sd)
				sd->skillstatictimer[PF_SOULBURN] = tick + skill_get_time2(skillid,skilllv);
		}
		break;
	case NPC_SELFDESTRUCTION2:	/* 自爆2 */
		if(flag&1) {
			if(bl->type == BL_PC && !map[src->m].flag.pvp && !map[src->m].flag.gvg)
				break;
		}
		// fall through
	case NPC_SELFDESTRUCTION:	/* 自爆 */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(md) {
				md->hp = skill_area_temp[2];
				if(bl->id != skill_area_temp[1]) {
					battle_skill_attack(BF_MISC,src,src,bl,NPC_SELFDESTRUCTION,skilllv,tick,flag);
				}
				md->hp = 1;
			}
		} else {
			sc = status_get_sc(src);
			if(sc && sc->data[SC_SELFDESTRUCTION].timer != -1)
				status_change_end(src,SC_SELFDESTRUCTION,-1);

			if(md && md->hp > 0) {
				int ar = skill_get_area(skillid,skilllv);
				if(skillid == NPC_SELFDESTRUCTION2 && md->hp >= status_get_max_hp(&md->bl)) {
					// 自爆2でHP全回復状態なら発動しない
					break;
				}
				skill_area_temp[1] = bl->id;
				skill_area_temp[2] = md->hp;
				clif_skill_nodamage(src,src,NPC_SELFDESTRUCTION,-1,1);
				map_foreachinarea(skill_area_sub,
					bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
					src,skillid,skilllv,tick, flag|BCT_ALL|1,
					skill_castend_damage_id);
				mob_damage(NULL,md,md->hp,1);
			}
		}
		break;
	case HVAN_EXPLOSION:	/* バイオエクスプロージョン */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_MISC,src,src,bl,skillid,skilllv,tick,0x0500);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			skill_area_temp[2] = bl->x;
			skill_area_temp[3] = bl->y;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* その後ターゲット以外の範囲内の敵全体に処理を行う */
			if(map[src->m].flag.normal) {
				map_foreachinarea(skill_area_sub,
					bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_MOB,
					src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
					skill_castend_damage_id);
			} else {
				map_foreachinarea(skill_area_sub,
					bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
					src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
					skill_castend_damage_id);
			}
			if(hd) {
				hd->intimate = 1;
				if(battle_config.homun_skill_intimate_type)
					hd->status.intimate = 1;
				clif_send_homdata(hd->msd,1,hd->intimate/100);
			}
			battle_damage(NULL,src,status_get_hp(src),skillid,skilllv,flag);
		}
		break;
	case MH_NEEDLE_OF_PARALYZE:	/* ニードルオブパラライズ */
	case MH_SONIC_CRAW:			/* ソニッククロー */
	case MH_SILVERVEIN_RUSH:	/* シルバーベインラッシュ */
	case MH_MIDNIGHT_FRENZY:	/* ミッドナイトフレンジ */
	case MH_STAHL_HORN:			/* シュタールホーン */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
		if(hd)
			hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
		break;
	case MH_TINDER_BREAKER:	/* ティンダーブレイカー */
		{
			int dist = unit_distance(src,bl);
			if(hd && !map[hd->bl.m].flag.gvg && dist > 1) {
				int dx = bl->x - hd->bl.x;
				int dy = bl->y - hd->bl.y;

				if(dx > 0) dx--;
				else if(dx < 0) dx++;
				if(dy > 0) dy--;
				else if(dy < 0) dy++;
				if(dx == 0 && dy == 0) dx++;
				if(path_search(NULL,src->m,hd->bl.x,hd->bl.y,hd->bl.x+dx,hd->bl.y+dy,1) == -1) {
					dx = bl->x - hd->bl.x;
					dy = bl->y - hd->bl.y;
					if(path_search(NULL,src->m,hd->bl.x,hd->bl.y,hd->bl.x+dx,hd->bl.y+dy,1) == -1) {
						clif_skill_fail(hd->msd,skillid,SKILLFAIL_FAILED,0,0);
						break;
					}
				}
				hd->ud.to_x = hd->bl.x + dx;
				hd->ud.to_y = hd->bl.y + dy;
				clif_skill_poseffect(&hd->bl,skillid,skilllv,hd->bl.x,hd->bl.y,tick);
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,dist);
				clif_move(&hd->bl);
				if(dx < 0) dx = -dx;
				if(dy < 0) dy = -dy;
				hd->ud.attackabletime = hd->ud.canmove_tick = tick + hd->speed * ((dx > dy)? dx:dy);
				if(hd->ud.canact_tick < hd->ud.canmove_tick)
					hd->ud.canact_tick = hd->ud.canmove_tick;
				unit_movepos(&hd->bl,hd->ud.to_x,hd->ud.to_y,0);
			} else {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,dist);
			}
			if(hd && hd->spiritball >= 1) {
				hd->spiritball--;
			}
			if(hd)
				hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
		}
		break;
	case MH_CBC:	/* C.B.C */
		sc = status_get_sc(bl);
		if(sc && sc->data[SC_TINDER_BREAKER].timer != -1) {
			int duration = status_get_str(src) / 7 - status_get_str(bl) / 10;
			int val3 = 50 * skilllv * status_get_lv(src) / 150;	// HP減少値(暫定)
			int val4 = 10 + (status_get_dex(src) + status_get_lv(src)) / 15;	// SP減少値(暫定)
			if(duration < skilllv)
				duration = skilllv;

			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_end(bl,SC_TINDER_BREAKER,-1);
			status_change_start(bl,SC_CBC,skilllv,0,val3,val4,duration*1000,0);
			if(hd && hd->spiritball >= 1) {
				status_change_start(src,SC_COMBO,skillid,skilllv,0,0,1000,0);
				clif_combo_delay(src,1000);
			}
		}
		if(hd)
			hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
		break;
	case MH_EQC:	/* E.Q.C */
		{
			int t_hp = status_get_hp(bl);
			status_change_start(bl,SC_EQC,skilllv,t_hp,0,0,skill_get_time2(skillid,skilllv),0);
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			if(hd)
				hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
		}
		break;
	case MH_ERASER_CUTTER:	/* イレイサーカッター */
	case MH_XENO_SLASHER:		/* ゼノスラッシャー */
		battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,0);
		if(hd)
			hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
		break;
	case MH_HEILIGE_STANGE:	/* ハイリエージュスタンジェ */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,0x0500);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			skill_area_temp[2] = bl->x;
			skill_area_temp[3] = bl->y;
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			/* その後ターゲット以外の範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_MOB,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			if(hd)
				hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
		}
		break;
	case MH_MAGMA_FLOW:	/* マグマフロー */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = bl->x;
			skill_area_temp[3] = bl->y;
			/* その後ターゲット以外の範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_MOB,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			if(hd)
				hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
		}
		break;
	case NJ_TATAMIGAESHI:	/* 畳返し */
		status_change_start(src,SC_TATAMIGAESHI,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		skill_castend_pos2(src,bl->x,bl->y,skillid,skilllv,tick,0);
		break;
	case NJ_KAENSIN:	/* 火炎陣 */
		bl = src;
		skill_castend_pos2(src,bl->x,bl->y,skillid,skilllv,tick,0);
		break;
	case NJ_BAKUENRYU:	/* 龍炎陣 */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_castend_pos2(src,bl->x,bl->y,skillid,skilllv,tick,0);
		break;
	case GS_DESPERADO:	/* デスペラード */
		{
			int tmpx, tmpy, i, num;
			int fa = 0;
			int ar = skill_get_area(skillid,skilllv);
			bl = src;
			sc = status_get_sc(src);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(sd) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// 弾の消費
					break;
			}
			num = skill_get_num(skillid,skilllv);
			if(sc && sc->data[SC_FALLEN_ANGEL].timer != -1)
				fa = 1;
			for(i=0; i<num; i++) {
				tmpx = src->x + (atn_rand()%(ar*2+1) - ar);
				tmpy = src->y + (atn_rand()%(ar*2+1) - ar);
				skill_addtimerskill(src,tick+i*100,0,tmpx,tmpy,skillid,skilllv,0,fa);
			}
			status_change_end(src,SC_FALLEN_ANGEL,-1);
		}
		break;

	/* HP吸収/HP吸収魔法 */
	case NPC_BLOODDRAIN:
	case NPC_ENERGYDRAIN:
		{
			int heal = battle_skill_attack((skillid == NPC_BLOODDRAIN)? BF_WEAPON: BF_MAGIC,
					src,src,bl,skillid,skilllv,tick,flag);
			if(heal > 0) {
				struct block_list tbl;
				memset(&tbl, 0, sizeof(tbl));
				tbl.m = src->m;
				tbl.x = src->x;
				tbl.y = src->y;
				clif_skill_nodamage(&tbl,src,AL_HEAL,heal,1);
				battle_heal(NULL,src,heal,0,0);
			}
		}
		break;
	case RK_HUNDREDSPEAR:	/* ハンドレッドスピア */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		if(atn_rand()%100 < (10 + 3*skilllv)) {
			skill_blown(src,bl,6|SAB_NOPATHSTOP);
			skill_addtimerskill(src,tick+800,bl->id,0,0,skillid,skilllv,BF_WEAPON,flag);
		}
		break;
	case RK_IGNITIONBREAK:	/* イグニッションブレイク */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* スキルエフェクト表示 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = src->x;
			skill_area_temp[3] = src->y;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case RK_WINDCUTTER:		/* ウィンドカッター */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(skill_area_temp[1] == 0 ? 0 : 0x0500));
			}
		}
		break;
	case RK_CRUSHSTRIKE:	/* クラッシュストライク */
		if(sd && battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag))
			pc_break_equip(sd, LOC_RARM);
		break;
	case RK_STORMBLAST:		/* ストームブラスト */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				if(battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500))
					skill_blown(src,bl,7 - path_distance(bl->x,bl->y,skill_area_temp[2],skill_area_temp[3]));
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* スキルエフェクト表示 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = src->x;
			skill_area_temp[3] = src->y;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case RK_PHANTOMTHRUST:	/* ファントムスラスト */
	case NPC_PHANTOMTHRUST:	/* Mファントムスラスト */
		if(battle_check_target(src,bl,BCT_ENEMY) > 0 || battle_check_target(src,bl,BCT_PARTY) > 0) {
			if(!map[bl->m].flag.gvg && !(status_get_mode(bl)&MD_BOSS)) {
				int posx = 0, posy = 0;

				if(bl->x > src->x) {
					posx = 1;
				} else if(bl->x < src->x) {
					posx = -1;
				}

				if(bl->y >= src->y) {
					posy = 1;
				} else if(bl->y < src->y) {
					posy = -1;
				}
				unit_movepos(bl, src->x+posx, src->y+posy, 0);
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if (battle_check_target(src,bl,BCT_ENEMY) > 0 ){
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			}
		}
		break;
	case GC_DARKILLUSION:	/* ダークイリュージョン */
	case RA_WUGSTRIKE:		/* ウォーグストライク */
	case LG_PINPOINTATTACK:	/* ピンポイントアタック */
	case KO_JYUMONJIKIRI:	/* 十文字斬り */
		{
			int dist = unit_distance(src,bl);
			if(sd && !map[sd->bl.m].flag.gvg && dist > 1 && (skillid != RA_WUGSTRIKE || pc_iswolfmount(sd))) {
				int dx = bl->x - sd->bl.x;
				int dy = bl->y - sd->bl.y;

				if(dx > 0) dx--;
				else if(dx < 0) dx++;
				if(dy > 0) dy--;
				else if(dy < 0) dy++;
				if(dx == 0 && dy == 0) dx++;
				if(path_search(NULL,src->m,sd->bl.x,sd->bl.y,sd->bl.x+dx,sd->bl.y+dy,1) == -1) {
					dx = bl->x - sd->bl.x;
					dy = bl->y - sd->bl.y;
					if(path_search(NULL,src->m,sd->bl.x,sd->bl.y,sd->bl.x+dx,sd->bl.y+dy,1) == -1) {
						clif_skill_fail(sd,sd->ud.skillid,SKILLFAIL_FAILED,0,0);
						break;
					}
				}
				sd->ud.to_x = sd->bl.x + dx;
				sd->ud.to_y = sd->bl.y + dy;
				clif_skill_poseffect(&sd->bl,skillid,skilllv,sd->bl.x,sd->bl.y,tick);
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
				clif_walkok(sd);
				clif_move(&sd->bl);
				if(dx < 0) dx = -dx;
				if(dy < 0) dy = -dy;
				sd->ud.attackabletime = sd->ud.canmove_tick = tick + sd->speed * ((dx > dy)? dx:dy);
				if(sd->ud.canact_tick < sd->ud.canmove_tick)
					sd->ud.canact_tick = sd->ud.canmove_tick;
				unit_movepos(&sd->bl,sd->ud.to_x,sd->ud.to_y,0);
			} else {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			}
			if(skillid == GC_DARKILLUSION) {
				if(atn_rand()%100 < (30 - 5*skilllv))
					skill_addtimerskill(src,tick+500,bl->id,0,0,skillid,skilllv,BF_WEAPON,flag);
			}
		}
		break;
	case GC_COUNTERSLASH:	/* カウンタースラッシュ */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* スキルエフェクト表示 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case GC_WEAPONCRUSH:	/* ウェポンクラッシュ */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		skill_castend_nodamage_id(src,bl,RG_STRIPWEAPON,skilllv,tick,0);	// ストリップウェポン実行
		break;
	case GC_VENOMPRESSURE:	/* ベナムプレッシャー */
		if(battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag)) {
			sc = status_get_sc(src);
			if(sc && sc->data[SC_POISONINGWEAPON].timer != -1) {
				if(atn_rand() % 10000 < status_change_rate(bl,sc->data[SC_POISONINGWEAPON].val2,7000+skilllv*500,status_get_lv(src)))
					status_change_start(bl,sc->data[SC_POISONINGWEAPON].val2,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
				else if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				status_change_end(src,SC_POISONINGWEAPON,-1);
			}
		}
		break;
	case GC_PHANTOMMENACE:	/* ファントムメナス */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				if(skill_detect(bl)) {		// ディテクト効果で暴いた相手に
					battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
				}
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* スキルエフェクト表示 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case GC_ROLLINGCUTTER:	/* ローリングカッター */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			sc = status_get_sc(src);
			if(sc) {
				if(sc->data[SC_ROLLINGCUTTER].timer == -1) {
					status_change_start(src,SC_ROLLINGCUTTER,1,0,0,0,skill_get_time(skillid,skilllv),0);
				} else if(sc->data[SC_ROLLINGCUTTER].val1 < 10) {
					int rolling = ++sc->data[SC_ROLLINGCUTTER].val1;
					status_change_start(src,SC_ROLLINGCUTTER,rolling,0,0,0,skill_get_time(skillid,skilllv),0);
				}
			}

			/* スキルエフェクト表示 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case GC_CROSSRIPPERSLASHER:	/* クロスリッパースラッシャー */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		status_change_end(src,SC_ROLLINGCUTTER,-1);
		break;
	case GC_DARKCROW:	/* ダーククロー */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case WL_FROSTMISTY:		/* フロストミスティ */
		if(flag&1) {
			if(bl->id != skill_area_temp[1]) {
				if(path_search_long(NULL,src->m,src->x,src->y,bl->x,bl->y)) {
					battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
				}
				if(atn_rand() % 10000 < 2500 + skilllv * 500)
					status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* スキルエフェクト表示 */
			clif_skill_poseffect(src,skillid,skilllv,src->x,src->y,tick);
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case WL_JACKFROST:		/* ジャックフロスト */
	case NPC_JACKFROST:		/* Mジャックフロスト */
		if(flag&1) {
			if(!path_search_long(NULL,src->m,src->x,src->y,bl->x,bl->y))
				break;
			if(bl->id != skill_area_temp[1]) {
				battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* スキルエフェクト表示 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case WL_DRAINLIFE:		/* ドレインライフ */
		{
			int heal = battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			if(heal > 0 && atn_rand() % 100 < 70 + skilllv * 5) {
				heal = heal * (skilllv * 8 * status_get_lv(src) / 100) / 100;
				unit_heal(src,heal,0,0,1);
			}
		}
		break;
	case WL_CRIMSONROCK:		/* クリムゾンロック */
		if(flag&1) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case WL_HELLINFERNO:		/* ヘルインフェルノ */
		if(battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag)) {
			if(atn_rand() % 10000 < 5500 + skilllv * 500) {
				status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			}
		}
		skill_addtimerskill(src,tick + 300,bl->id,0,0,WL_HELLINFERNO,skilllv,0,(0x0f<<20)|0x500|flag|1);
		break;
	case WL_CHAINLIGHTNING:		/* チェーンライトニング */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_addtimerskill(src,tick + 650,bl->id,0,0,WL_CHAINLIGHTNING_ATK,skilllv,1,(0x0f<<20)|flag);
		break;
	case RA_ARROWSTORM:		/* アローストーム */
	case NPC_ARROWSTORM:	/* Mアローストーム */
		if(flag&1) {
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			if(sd) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// 矢の消費
					break;
			}
			skill_area_temp[0] = 0;
			skill_area_temp[1] = bl->id;
			if( !battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(is_enemy ? 0 : 0x01000000)) )
				break;
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case RA_AIMEDBOLT:      /* エイムドボルト */
		{
			int div_ = 2 + status_get_size(bl) + atn_rand()%2;
			if(sd && !battle_delarrow(sd,div_,skillid))   // 矢の消費
				break;
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,div_);
		}
		break;
	case RA_WUGDASH:		/* ウォーグダッシュ */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(0x0f<<20)|0x0500);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case RA_SENSITIVEKEEN:	/* 鋭敏な嗅覚 */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				if(skill_detect(bl)) {		// ディテクト効果で暴いた相手に
					battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
					if(atn_rand()%100 < (8*skilllv)) {
						skill_addtimerskill(src,tick+500,bl->id,0,0,skillid,skilllv,BF_WEAPON,flag);
					}
				}
			}
		} else if(flag&2) {
			if(bl->type == BL_SKILL) {
				struct skill_unit *su = (struct skill_unit *)bl;
				if(!su || !su->group || !skill_unit_istrap(su->group->unit_id))
					break;
				if(su->group->unit_id == UNT_ANKLESNARE && su->group->val2)		// 補足中のアンクルスネアは除外
					break;
				if(itemdb_exists(su->group->val3)) {
					struct item item_tmp;
					memset(&item_tmp,0,sizeof(item_tmp));
					item_tmp.nameid = su->group->val3;
					item_tmp.identify = 1;
					map_addflooritem(&item_tmp,1,bl->m,bl->x,bl->y,0,0,0,0);
				}
				skill_delunit(su);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* スキルエフェクト表示 */
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			map_foreachinarea(skill_area_trap_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_SKILL,
				src,skillid,skilllv,tick, flag|BCT_ALL|2,
				skill_castend_damage_id);
		}
		break;
	case NC_VULCANARM:		/* バルカンアーム */
		if(flag&1) {
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			/* まずターゲットに攻撃を加える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NC_FLAMELAUNCHER:	/* フレイムスローワー */
		if(flag&1) {
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x500);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			/* まずターゲットに攻撃を加える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NC_ARMSCANNON:		/* アームズキャノン */
		if(flag&1) {
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x500);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			if(sd) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// 矢の消費
					break;
			}
			skill_area_temp[1] = bl->id;
			/* まずターゲットに攻撃を加える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NC_SELFDESTRUCTION:	/* セルフディストラクション */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);

			if(sd) {
				if(!pc_isgear(sd)) {
					clif_skill_fail(sd,skillid,SKILLFAIL_MADOGEAR,0,0);
					break;
				}
			}

			/* スキルエフェクト表示 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);

			skill_area_temp[1] = src->id;
			skill_area_temp[2] = src->x;
			skill_area_temp[3] = src->y;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			if(sd) {
				/* 魔導ギアを解除 */
				pc_setoption(sd, (sd->sc.option & ~OPTION_MADOGEAR));
				sd->status.sp = 0;
				clif_updatestatus(sd,SP_SP);
			}
		}
		break;
	case NC_AXETORNADO:	/* アックストルネード */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* スキルエフェクト表示 */
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			clif_skill_nodamage(src,bl,skillid,skilllv,1);

			skill_area_temp[1] = src->id;
			skill_area_temp[2] = src->x;
			skill_area_temp[3] = src->y;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NC_POWERSWING:		/* パワースイング */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		if(atn_rand()%100 < 5 * skilllv) {
			skill_addtimerskill(src,tick+800,bl->id,0,0,skillid,skilllv,BF_WEAPON,flag);
		}
		break;
	case NC_DISJOINT:		/* FAW解除 */
		if(bl->type == BL_MOB) {
			struct mob_data* tmd = (struct mob_data*)bl;
			if(tmd->class_ >= 2042 && tmd->class_ <= 2046 && tmd->master_id != 0) {
				clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, skilllv, 0);
				mob_damage(src, tmd, tmd->hp, 2);
			} else if(sd) {
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
			}
		} else if(sd) {
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		}
		break;
	case SC_FATALMENACE:	/* フェイタルメナス */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			/* まずターゲットに攻撃を加える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SC_TRIANGLESHOT:	/* トライアングルショット */
		if(battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag)) {
			if(atn_rand()%10000 < 100 + 100 * skilllv) {
				skill_blown(src,bl,5|SAB_REVERSEBLOW|SAB_NOPATHSTOP);
			}
		}
		break;
	case SC_FEINTBOMB:		/* フェイントボム */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x500);
		break;
	case LG_CANNONSPEAR:	/* キャノンスピア */
		if(flag&1) {
			/* 個別にダメージを与える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(skill_area_temp[1] == 0 ? 0 : 0x0500));
			skill_area_temp[1]++;
		} else {
			int dir = path_calc_dir(src,bl->x,bl->y);
			skill_area_temp[1] = 0;
			map_foreachinshootpath(
				skill_area_sub,bl->m,src->x,src->y,dirx[dir],diry[dir],10,skill_get_area(skillid,skilllv),(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,skill_castend_damage_id
			);
			if(skill_area_temp[1] == 0) {
				/* ターゲットに攻撃 */
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(is_enemy ? 0 : 0x01000000));
			}
		}
		break;
	case LG_RAGEBURST:		/* レイジバーストアタック */
		sc = status_get_sc(src);
		if(sc && sc->data[SC_FORCEOFVANGUARD].timer != -1 && sc->data[SC_FORCEOFVANGUARD].val4 > 0) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			sc->data[SC_FORCEOFVANGUARD].val4 = 0;
			if(sd)
				clif_mshield(sd,0);
		}
		break;
	case LG_SHIELDSPELL:	/* シールドスペル */
		if(flag&1) {
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		}
		else if(flag&2) {
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		}
		break;
	case LG_OVERBRAND_BRANDISH:		/* オーバーブランド(薙ぎ) */
		{
			int dist = unit_distance(src,bl);
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
			if(unit_distance(src,bl) < skill_get_blewcount(skillid,skilllv) + dist) {
				battle_skill_attack(BF_WEAPON,src,src,bl,LG_OVERBRAND_PLUSATK,skilllv,tick,0x0500);
			}
		}
		break;
	case LG_MOONSLASHER:	/* ムーンスラッシャー */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* スキルエフェクト表示 */
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case LG_EARTHDRIVE:		/* アースドライブ */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* スキルエフェクト表示 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			map_foreachinarea(skill_delunit_by_ganbantein,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_SKILL);
			if(sd && atn_rand() % 10000 < 500)
				pc_break_equip(sd, LOC_LARM);
		}
		break;
	case SR_SKYNETBLOW:	/* 天羅地網 */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* スキルエフェクト表示 */
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SR_EARTHSHAKER:	/* 地雷震 */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				if(skill_detect(bl))		// ディテクト効果で暴いた相手に
					battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag|1);
				else
					battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag&~1);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* スキルエフェクト表示 */
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SR_TIGERCANNON:	/* 號砲 */
	case SR_GATEOFHELL:		/* 羅刹破凰撃 */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag|(is_enemy ? 0 : 0x01000000));
		break;
	case SR_KNUCKLEARROW:	/* 修羅身弾 */
		{
			int dist = unit_distance(src,bl);
			if(sd && !map[sd->bl.m].flag.gvg && dist > 1) {
				int dx = bl->x - sd->bl.x;
				int dy = bl->y - sd->bl.y;

				if(dx > 0) dx--;
				else if(dx < 0) dx++;
				if(dy > 0) dy--;
				else if(dy < 0) dy++;
				if(dx == 0 && dy == 0) dx++;
				if(path_search(NULL,src->m,sd->bl.x,sd->bl.y,sd->bl.x+dx,sd->bl.y+dy,1) == -1) {
					dx = bl->x - sd->bl.x;
					dy = bl->y - sd->bl.y;
					if(path_search(NULL,src->m,sd->bl.x,sd->bl.y,sd->bl.x+dx,sd->bl.y+dy,1) == -1) {
						clif_skill_fail(sd,sd->ud.skillid,SKILLFAIL_FAILED,0,0);
						break;
					}
				}
				sd->ud.to_x = sd->bl.x + dx;
				sd->ud.to_y = sd->bl.y + dy;
				clif_skill_poseffect(&sd->bl,skillid,skilllv,sd->bl.x,sd->bl.y,tick);
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
				clif_walkok(sd);
				clif_move(&sd->bl);
				if(dx < 0) dx = -dx;
				if(dy < 0) dy = -dy;
				sd->ud.attackabletime = sd->ud.canmove_tick = tick + sd->speed * ((dx > dy)? dx:dy);
				if(sd->ud.canact_tick < sd->ud.canmove_tick)
					sd->ud.canact_tick = sd->ud.canmove_tick;
				unit_movepos(&sd->bl,sd->ud.to_x,sd->ud.to_y,0);
			} else {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			}
			if(unit_distance(src,bl) < skill_get_blewcount(skillid,skilllv)) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x500|1);
			}
		}
		break;
	case SR_WINDMILL:	/* 旋風腿 */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* スキルエフェクト表示 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = src->x;
			skill_area_temp[3] = src->y;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SR_RAMPAGEBLASTER:		/* 爆気散弾 */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* スキルエフェクト表示 */
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SR_GENTLETOUCH_QUIET:	/* 点穴 -默- */
		if(atn_rand()%100 < skilllv * 5 + (status_get_lv(src) + status_get_dex(src)) / 10) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else if(sd) {
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		}
		break;
	case SR_HOWLINGOFLION:	/* 獅子吼 */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* スキルエフェクト表示 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = src->x;
			skill_area_temp[3] = src->y;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case WM_SOUND_OF_DESTRUCTION:	/* サウンドオブディストラクション */
		if(flag&1) {
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x500);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[0] = 0;
			skill_area_temp[1] = bl->id;
			/* まずターゲットに攻撃を加える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case GN_CART_TORNADO:	/* カートトルネード */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* スキルエフェクト表示 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = src->x;
			skill_area_temp[3] = src->y;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case GN_CARTCANNON:		/* カートキャノン */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* まずターゲットに攻撃を加える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			/* その後ターゲット以外の範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case GN_BLOOD_SUCKER:	/* ブラッドサッカー */
		if(unit_distance(src,bl) < 12){
			int heal = battle_skill_attack(BF_MISC,src,src,bl,skillid,skilllv,tick,(0x0f<<20)|0x500);
			heal = heal * (5 + skilllv * 5) / 100;
			if(status_get_hp(src) + heal > status_get_max_hp(src))
				heal = status_get_max_hp(src) - status_get_hp(src);
			if(heal > 0) {
				battle_heal(NULL,src,heal,0,0);
				if(sd)
					clif_heal(sd->fd,SP_HP,heal);
			}
		}
		break;
	case GN_SPORE_EXPLOSION:	/* スポアエクスプロージョン */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(0x0f<<20)|flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(0x0f<<20)|flag);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case GN_ILLUSIONDOPING:	/* イリュージョンドーピング */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(0x0f<<20)|0x0500);
			}
			if( atn_rand() % 10000 < 9000-1000*skilllv )
				status_change_start(bl,SC_ILLUSIONDOPING,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			if( !(status_get_mode(bl)&MD_BOSS) && atn_rand() % 10000 < status_change_rate(bl,SC_CONFUSION,9000-1000*skilllv,status_get_lv(src)) )
				status_change_pretimer(bl,SC_CONFUSION,7,0,0,0,30000,0,tick+status_get_amotion(src));
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(0x0f<<20));
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case KO_BAKURETSU:		/* 爆裂苦無 */
	case KO_HUUMARANKA:		/* 風魔手裏剣 -乱華- */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* まずターゲットに攻撃を加える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			/* その後ターゲット以外の範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case KO_HAPPOKUNAI:		/* 八方苦無 */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			if(sd) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// 矢の消費
					break;
			}
			/* スキルエフェクト表示 */
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			clif_skill_nodamage(src,bl,skillid,skilllv,1);

			skill_area_temp[1] = src->id;
			skill_area_temp[2] = src->x;
			skill_area_temp[3] = src->y;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case KO_MUCHANAGE:	/* 無茶投げ */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,skill_area_temp[0]);
		break;
	case KO_MAKIBISHI:			/* 撒菱 */
		skill_castend_pos2(src,bl->x,bl->y,skillid,skilllv,tick,0);
		break;
	case KO_KAIHOU:				/* 術式 -解放- */
		battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		if(sd && sd->elementball.num)
			pc_delelementball(sd,sd->elementball.num,0);
		break;
	case RL_MASS_SPIRAL:		/* マススパイラル */
	case RL_BANISHING_BUSTER:	/* バニシングバスター */
	case RL_AM_BLAST:			/* アンチマテリアルブラスト */
	case RL_SLUGSHOT:			/* スラッグショット */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case RL_B_FLICKER_ATK:		/* バインドトラップ(爆発) */
		battle_skill_attack(BF_MISC,src,src,bl,skillid,skilllv,tick,flag);
		status_change_end(bl, SC_B_TRAP, -1);
		break;
	case RL_S_STORM:		/* シャッターストーム */
	case RL_D_TAIL:			/* ドラゴンテイル */
	case RL_HAMMER_OF_GOD:	/* ハンマーオブゴッド */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			int tx = bl->x, ty = bl->y;
			skill_area_temp[1] = bl->id;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* まずターゲットに攻撃を加える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			/* その後ターゲット以外の範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			if(sd) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// 矢の消費
					break;
			}
			if(skillid == RL_HAMMER_OF_GOD)
				pc_delcoin(sd,MAX_COIN,0);
		}
		break;
	case RL_QD_SHOT:	/* クイックドローショット */
		if(flag&0x10) {
			sc = status_get_sc(bl);
			if(sc && sc->data[SC_C_MARKER].timer != -1 && sc->data[SC_C_MARKER].val2 == src->id && skill_area_temp[1] != bl->id)
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int div_ = 1;
			int ar = skill_get_area(skillid,skilllv);
			if(sd) {
				div_ += sd->status.job_level / 20;
				if(div_ > 4)
					div_ = 4;
				if(!battle_delarrow(sd,div_,0))
					break;
			}
			skill_area_temp[1] = bl->id;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag|div_);
			map_foreachinarea(skill_area_sub,src->m,
				src->x-ar,src->y-ar,
				src->x+ar,src->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_ENEMY|0x10|div_,
				skill_castend_damage_id);
			status_change_end(src, SC_QD_SHOT_READY, -1);
		}
		break;
	case RL_FIREDANCE:	/* ファイアーダンス */
		if(flag&1) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,src->m,
				src->x-ar,src->y-ar,
				src->x+ar,src->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			if(sd) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// 矢の消費
					break;
			}
		}
		break;
	case RL_H_MINE:		/* ハウリングマイン */
		if(flag&2) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(0x0f<<20)|flag|0x500);
		} else if(flag&1) {
			sc = status_get_sc(bl);
			if(sc && sc->data[SC_H_MINE].timer != -1 && sc->data[SC_H_MINE].val2 == src->id) {
				int ar = skill_get_area(skillid,skilllv);
				status_change_start(bl,SC_H_MINE_SPLASH,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
				map_foreachinarea(skill_area_sub,bl->m,
					bl->x-ar,bl->y-ar,
					bl->x+ar,bl->y+ar,
					BL_CHAR,src,skillid,sc->data[SC_H_MINE].val1,tick,flag|BCT_ENEMY|2,
					skill_castend_damage_id);
				status_change_end(bl,SC_H_MINE,-1);
			}
		} else {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,src->id,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case RL_R_TRIP:	/* ラウンドトリップ */
		if(flag&1) {
			int dist = unit_distance(src,bl);
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			if(unit_distance(src,bl) < skill_get_blewcount(skillid,skilllv) + dist) {
				battle_skill_attack(BF_WEAPON,src,src,bl,RL_R_TRIP_PLUSATK,skilllv,tick,(0x0f<<20)|flag);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,src->m,
				src->x-ar,src->y-ar,
				src->x+ar,src->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			if(sd) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// 矢の消費
					break;
			}
		}
		break;
	case SJ_FULLMOONKICK:		/* 満月脚 */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]){
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			status_change_end(src, SC_NEWMOON, -1);
			/* スキルエフェクト表示 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);

			skill_area_temp[1] = src->id;
			skill_area_temp[2] = src->x;
			skill_area_temp[3] = src->y;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SJ_NEWMOONKICK:	/* 朔月脚 */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* スキルエフェクト表示 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = src->x;
			skill_area_temp[3] = src->y;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			sc = status_get_sc(src);
			if(sc && sc->data[GetSkillStatusChangeTable(skillid)].timer != -1) {
				status_change_end(src, GetSkillStatusChangeTable(skillid), -1);
			} else {
				status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case SJ_FLASHKICK:	/* 閃光脚 */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag) > 0) {
			if(sd) {
				int i;

				sc = status_get_sc(bl);
				if(sc && sc->data[SC_FLASHKICK].timer != -1 && sc->data[SC_FLASHKICK].val2 != src->id)
					status_change_end(bl, SC_FLASHKICK, -1);

				for(i=0; i<MAX_STELLAR_MARKS; i++) {
					if(sd->stellar_mark[i] == bl->id || sd->stellar_mark[i] == 0)
						break;
				}
				if(i < MAX_STELLAR_MARKS) {
					sd->stellar_mark[i] = bl->id;
					status_change_start(bl,SC_FLASHKICK,skilllv,src->id,i,0,skill_get_time(skillid,skilllv),0);
				}
			}
		}
		break;
	case SJ_STAREMPEROR:		/* 星帝降臨 */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]){
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* スキルエフェクト表示 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);

			skill_area_temp[1] = src->id;
			skill_area_temp[2] = src->x;
			skill_area_temp[3] = src->y;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			sc = status_get_sc(src);
			if(sc) {
				if(sc->data[SC_DIMENSION].timer != -1){
					status_change_end(src,SC_DIMENSION,-1);
					status_change_start(src,SC_DIMENSION2,skilllv,0,0,status_get_max_sp(src)*2,skill_get_time(skillid,skilllv),0);
				}
			}
		}
		break;
	case SJ_NOVAEXPLOSING:	// 新星爆発
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		sc = status_get_sc(src);
		if(sc) {
			if( sc->data[SC_DIMENSION].timer != -1 ){
				status_change_end(src,SC_DIMENSION,-1);
				status_change_start(src,SC_DIMENSION1,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
			}
			else if( sc->data[SC_DIMENSION1].timer != -1 ){
				//Do nothing
			}
			else{
				status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case SJ_SOLARBURST:		/* 太陽爆発 */
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* スキルエフェクト表示 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = src->x;
			skill_area_temp[3] = src->y;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SJ_PROMINENCEKICK:	/* 紅焔脚 */
		if(flag&1) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag|0x500);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* スキルエフェクト表示 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SJ_FALLINGSTAR_ATK:	/* 流星落下(攻撃) */
		if(flag&1) {
			sc = status_get_sc(bl);
			if (sc && sc->data[SC_FLASHKICK].timer != -1 && sc->data[SC_FLASHKICK].val2 == src->id) {
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
				battle_skill_attack(BF_WEAPON, src, src, bl, skillid, skilllv, tick, flag);
				skill_addtimerskill(src,tick+300,bl->id,0,0,SJ_FALLINGSTAR_ATK2,skilllv,0,flag);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SJ_FALLINGSTAR_ATK2:	/* 流星落下(追撃) */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case SP_CURSEEXPLOSION:		// 死霊爆発
		if(flag&1) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SP_SPA:				// エスパ
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case SP_SHA:			// エスハ
		if(flag&1) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			status_change_start(src,SC_SMA,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			if(bl->type != BL_MOB && !battle_config.allow_es_magic_all)
				status_change_start(src,SC_STUN,skilllv,0,0,0,5000,0);
		}
		break;
	case SP_SWHOO:			// エスフ
		if(flag&1) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,
				battle_config.allow_es_magic_all? (BL_CHAR|BL_SKILL): BL_MOB,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			if(sc && sc->data[SC_SWHOO].timer != -1)
				status_change_end(bl,SC_SWHOO,-1);
			status_change_start(src,SC_SMA,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SP_SOULEXPLOSION:		// 魂の崩壊
		battle_skill_attack(BF_MISC,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case SU_BITE:			// かみつく
	case SU_SCAROFTAROU:	// タロウの傷
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case SU_SCRATCH:	// ひっかく
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1])
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* まずターゲットに攻撃を加える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			/* その後ターゲット以外の範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SU_PICKYPECK:	// ピッキ突き
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if((int)((atn_bignumber)status_get_hp(bl) * 100 / status_get_max_hp(bl)) <= 20 + skilllv * 10) {	// 敵のHPが一定以下なら
			battle_skill_attack(BF_WEAPON,src,src,bl,SU_PICKYPECK_DOUBLE_ATK,skilllv,tick,flag);
		} else {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		}
		break;
	case SU_LUNATICCARROTBEAT:	// キャロットビート
	case SU_LUNATICCARROTBEAT2:	// キャロットビート(スタン)
		if(flag&1) {
			/* 個別にダメージを与える */
			if(bl->id == skill_area_temp[1])
				break;
			if(battle_skill_attack(BF_WEAPON,src,src,bl,SU_LUNATICCARROTBEAT,skilllv,tick,flag) > 0) {
				if(skillid == SU_LUNATICCARROTBEAT2 && atn_rand() % 10000 < status_change_rate(&sd->bl,SC_STUN,5000,status_get_lv(src)))
					status_change_pretimer(&sd->bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = bl->id;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* まずターゲットに攻撃を加える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			/* その後ターゲット以外の範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SU_SVG_SPIRIT:	// サベージの魂
		if(flag&1) {
			/* 個別にダメージを与える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(skill_area_temp[1] == 0 ? 0 : 0x0500));
			skill_area_temp[1]++;
		} else {
			int dir = path_calc_dir(src,bl->x,bl->y);
			int dist = unit_distance(src,bl);
			skill_area_temp[1] = 0;
			map_foreachinshootpath(
				skill_area_sub,bl->m,src->x,src->y,dirx[dir],diry[dir],dist,0,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,skill_castend_damage_id
			);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(skill_area_temp[1] == 0) {
				/* ターゲットに攻撃 */
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(is_enemy ? 0 : 0x01000000));
			}
		}
		break;
	case SU_SV_STEMSPEAR:	/* マタタビランス */
		battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case NPC_MAXPAIN_ATK:		/* マックスペイン */
		if(flag&1) {
			/* 個別にダメージを与える */
			battle_skill_attack(BF_MISC,src,src,bl,NPC_MAXPAIN_ATK,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* 範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case DK_SERVANTWEAPON_ATK:		/* サーヴァントウェポン(攻撃) */
	case SHC_DANCING_KNIFE:			/* ダンシングナイフ */
	case MT_A_MACHINE:			/* 攻撃装置有効化 */
		if(flag&1) {
			/* 個別にダメージを与える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(0x0f<<20)|flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* 範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case DK_SERVANT_W_PHANTOM:		/* サーヴァントウェポン：ファントム */
		if(flag&0x20) {
			/* 個別にダメージを与える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(flag&0x0f));
		} else if(flag&0x10) {
			// サーヴァントサイン判定
			sc = status_get_sc(bl);
			if(sc && sc->data[SC_SERVANT_SIGN].timer != -1) {
				/* 対象の敵周囲に処理を行う */
				map_foreachinarea(skill_area_sub,
					bl->m,bl->x-1,bl->y-1,bl->x+1,bl->y+1,BL_CHAR,
					src,skillid,skilllv,tick, flag|BCT_ENEMY|0x20|(flag&0x0f),
					skill_castend_damage_id);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			int dist = unit_distance(src,bl);
			int num = 1;
			// ターゲットの隣接セル移動
			if(sd && !map[sd->bl.m].flag.gvg && dist > 1) {
				int dx = bl->x - sd->bl.x;
				int dy = bl->y - sd->bl.y;

				if(dx > 0) dx--;
				else if(dx < 0) dx++;
				if(dy > 0) dy--;
				else if(dy < 0) dy++;
				if(dx == 0 && dy == 0) dx++;
				if(path_search(NULL,src->m,sd->bl.x,sd->bl.y,sd->bl.x+dx,sd->bl.y+dy,1) == -1) {
					dx = bl->x - sd->bl.x;
					dy = bl->y - sd->bl.y;
					if(path_search(NULL,src->m,sd->bl.x,sd->bl.y,sd->bl.x+dx,sd->bl.y+dy,1) == -1) {
						clif_skill_fail(sd,sd->ud.skillid,SKILLFAIL_FAILED,0,0);
						break;
					}
				}
				sd->ud.to_x = sd->bl.x + dx;
				sd->ud.to_y = sd->bl.y + dy;
				clif_skill_poseffect(&sd->bl,skillid,skilllv,sd->bl.x,sd->bl.y,tick);
				clif_walkok(sd);
				clif_move(&sd->bl);
				if(dx < 0) dx = -dx;
				if(dy < 0) dy = -dy;
				sd->ud.attackabletime = sd->ud.canmove_tick = tick + sd->speed * ((dx > dy)? dx:dy);
				if(sd->ud.canact_tick < sd->ud.canmove_tick)
					sd->ud.canact_tick = sd->ud.canmove_tick;
				unit_movepos(&sd->bl,sd->ud.to_x,sd->ud.to_y,0);
			}
			if(sd) {
				num = sd->ball.num;
				pc_delball(sd,sd->ball.num,0);
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* 範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|0x10|num,
				skill_castend_damage_id);

		}
		break;
	case DK_SERVANT_W_DEMOL:		/* サーヴァントウェポン：デモリッション */
		if(flag&0x10) {
			// サーヴァントサイン判定
			sc = status_get_sc(bl);
			if(sc && sc->data[SC_SERVANT_SIGN].timer != -1) {
				/* 個別にダメージを与える */
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,(flag&0x0f));
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			int num = 1;
			if(sd) {
				num = sd->ball.num;
				pc_delball(sd,sd->ball.num,0);
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* 範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|0x10|num,
				skill_castend_damage_id);
		}
		break;
	case DK_DRAGONIC_AURA:		/* ドラゴニックオーラ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case DK_HACKANDSLASHER:		/* ハックアンドスラッシャー */
	case DK_HACKANDSLASHER_ATK:	/* ハックアンドスラッシャー(攻撃) */
	case DK_MADNESS_CRUSHER:	/* マッドネスクラッシャー */
	case DK_DRAGONIC_BREATH:	/* ドラゴニックブレス */
	case CD_PETITIO:			/* ペティティオ */
	case IQ_OLEUM_SANCTUM:		/* 聖油洗礼 */
	case IQ_EXPOSION_BLASTER:	/* 爆火神弾 */
	case IQ_FIRST_BRAND:		/* 第一撃：烙印 */
	case IQ_SECOND_FLAME:		/* 第二撃：滅魔の火 */
	case IQ_SECOND_FAITH:		/* 第二撃：信念 */
	case IQ_SECOND_JUDGEMENT:	/* 第二撃：審判 */
	case IQ_THIRD_FLAME_BOMB:	/* 第三撃：滅火撃 */
	case BO_ACIDIFIED_ZONE_WATER:		/* アシディファイドゾーン(水) */
	case BO_ACIDIFIED_ZONE_GROUND:		/* アシディファイドゾーン(地) */
	case BO_ACIDIFIED_ZONE_WIND:		/* アシディファイドゾーン(風) */
	case BO_ACIDIFIED_ZONE_FIRE:		/* アシディファイドゾーン(火) */
	case NPC_BO_THROWROCK:		/* スローロック */
	case NPC_BO_WOODEN_ATTACK:	/* ウドゥンアタック */
		if(flag&1) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* 範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case DK_STORMSLASH:		/* ストームスラッシュ */
	case CD_EFFLIGO:		/* エフィリゴ */
	case SHC_SHADOW_STAB:	/* シャドウスタブ */
	case ABC_FRENZY_SHOT:	/* フレンジショット */
	case WH_HAWKRUSH:		/* ホークラッシュ */
	case WH_HAWKBOOMERANG:	/* ホークブーメラン */
	case TR_RHYTHMSHOOTING:		/*リズムシューティング */
	case MT_TRIPLE_LASER:		/* トリプルレーザー */
	case ABR_BATTLE_BUSTER:		/* バトルバスター */
	case ABR_DUAL_CANNON_FIRE:	/* デュアルキャノンファイヤー */
	case ABR_INFINITY_BUSTER:	/* インフィニティバスター */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case AG_DEADLY_PROJECTION:		/* デッドリープロジェクション */
	case TR_ROSEBLOSSOM:	/* ロゼブロッサム */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case AG_DESTRUCTIVE_HURRICANE:		/* ディストラクティブハリケーン */
		if(flag&0x20) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,0x10);
		} else if(flag&0x10) {
			/* 個別にダメージを与える */
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag&0xf);
			if((flag&0xf) == 1) {	// クライマックスLv1：風属性追加ダメージ
				skill_addtimerskill(src,tick+300,bl->id,0,0,skillid,skilllv,0,flag|0x20);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			int climax = 0;
			sc = status_get_sc(src);
			if(sc && sc->data[SC_CLIMAX].timer != -1) {
				climax = sc->data[SC_CLIMAX].val1;
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(climax == 4) {		// クライマックスLv4：自身にクライマックスハリケーン状態付与
				status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			} else {
				if(climax == 5)		// クライマックスLv5：範囲が19x19に拡大
					ar = 9;
				/* 範囲内の敵全体に処理を行う */
				skill_area_temp[1] = src->id;
				map_foreachinarea(skill_area_sub,
					src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_CHAR,
					src,skillid,skilllv,tick, flag|BCT_ENEMY|0x10|climax,
					skill_castend_damage_id);
			}
		}
		break;
	case AG_RAIN_OF_CRYSTAL:		/* レインオブクリスタル */
		bl = src;
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_castend_pos2(src,bl->x,bl->y,skillid,skilllv,tick,0);
		break;
	case AG_SOUL_VC_STRIKE:		/* ソウルバルカンストライク */
	case AG_ROCK_DOWN:			/* ロックダウン */
	case AG_FROZEN_SLASH:		/* フローズンスラッシュ */
	case CD_FRAMEN:				/* フレーメン */
	case TR_METALIC_FURY:		/* メタリックフューリー */
	case NPC_BO_HELL_HOWLING:	/* ヘルハウリング */
	case NPC_BO_FAIRY_DUSTY:	/* フェアリーダスティ */
		if(flag&1) {
			/* 個別にダメージを与える */
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* 範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case AG_CRYSTAL_IMPACT:		/* クリスタルインパクト */
		if(flag&0x20) {
			status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else if(flag&0x10) {
			/* 個別にダメージを与える */
			if(bl->id != skill_area_temp[1]) {
				if((flag&0xf) == 2) {		// クライマックスLv2：2回連続攻撃
					battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,0x800|flag&0xf);
				} else {
					battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag&0xf);
				}
				skill_addtimerskill(src,tick+300,bl->id,0,0,AG_CRYSTAL_IMPACT_ATK,skilllv,0,flag&0xf);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			int climax = 0;
			sc = status_get_sc(src);
			if(sc && sc->data[SC_CLIMAX].timer != -1) {
				climax = sc->data[SC_CLIMAX].val1;
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);

			if(climax == 5)		// クライマックスLv5：範囲が19x19に拡大
				ar = 9;
			/* 範囲内の敵全体に処理を行う */
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|0x10|climax,
				skill_castend_damage_id);
			if(climax == 1) {		// クライマックスLv1：範囲内の味方に付与効果
				map_foreachinarea(skill_area_sub,
					src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_CHAR,
					src,skillid,skilllv,tick, flag|BCT_NOENEMY|0x20,
					skill_castend_damage_id);
			}
		}
		break;
	case AG_CRYSTAL_IMPACT_ATK:		/* クリスタルインパクト(追撃) */
		if((flag&0x0f) != 5 || flag&0x10) {		// クライマックスLv5：追撃ダメージの範囲拡大
			/* 個別にダメージを与える */
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,(0x0f<<20)|flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* 範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|0x10,
				skill_castend_damage_id);
		}
		break;
	case AG_ASTRAL_STRIKE_ATK:	/* アストラルストライク(初撃) */
	case TR_SOUNDBLEND:			/* サウンドブレンド */
		battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,(0x0f<<20));
		break;
	case AG_STORM_CANNON:	/* ストームキャノン */
		if(flag&1) {
			/* 個別にダメージを与える */
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			skill_area_temp[1]++;
		} else {
			int dir = path_calc_dir(src,bl->x,bl->y);
			skill_area_temp[1] = 0;
			map_foreachinshootpath(
				skill_area_sub,bl->m,src->x,src->y,dirx[dir],diry[dir],unit_distance(src,bl),skill_get_area(skillid,skilllv),(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,skill_castend_damage_id
			);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(skill_area_temp[1] == 0) {
				/* ターゲットに攻撃 */
				battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			}
		}
		break;
	case AG_CRIMSON_ARROW:	/* クリムゾンアロー */
		if(flag&1) {
			/* 個別にダメージを与える */
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			skill_area_temp[1]++;
		} else {
			int dir = path_calc_dir(src,bl->x,bl->y);
			skill_area_temp[1] = 0;
			map_foreachinshootpath(
				skill_area_sub,bl->m,src->x,src->y,dirx[dir],diry[dir],unit_distance(src,bl),skill_get_area(skillid,skilllv),(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,skill_castend_damage_id
			);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(skill_area_temp[1] == 0) {
				/* ターゲットに攻撃 */
				battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			}
			skill_addtimerskill(src,tick+300,bl->id,0,0,AG_CRIMSON_ARROW_ATK,skilllv,0,flag);
		}
		break;
	case AG_CRIMSON_ARROW_ATK:	/* クリムゾンアロー(攻撃) */
	case CD_ARBITRIUM_ATK:		/* アルビトリウム(追撃) */
	case ABC_FROM_THE_ABYSS_ATK:	/* フロムジアビス(攻撃) */
	case TR_ROSEBLOSSOM_ATK:	/* ロゼブロッサム(攻撃) */
		if(flag&1) {
			/* 個別にダメージを与える */
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,(0x0f<<20)|flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* 範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case IQ_MASSIVE_F_BLASTER:		/* 炎火滅魔神弾 */
	case IG_GRAND_JUDGEMENT:		/* グランドジャッジメント */
	case IG_SHIELD_SHOOTING:		/* シールドシューティング */
	case SHC_IMPACT_CRATER:			/* インパクトクレーター */
	case MT_AXE_STOMP:				/* アックスストンプ */
	case ABC_ABYSS_DAGGER:			/* アビスダガー */
	case ABC_DEFT_STAB:				/* デフトスタブ */
	case MT_SPARK_BLASTER:			/* スパークブラスター */
	case MT_MIGHTY_SMASH:			/* マイティスマッシュ */
	case BO_EXPLOSIVE_POWDER:		/* エクスプロッシブパウダー */
	case BO_MAYHEMIC_THORNS:		/* メイヘミックソーンズ */
		if(flag&1) {
			/* 個別にダメージを与える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* 範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case IQ_THIRD_PUNISH:			/* 第三撃：断罪 */
		if(flag&1) {
			/* 個別にダメージを与える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* 範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			pc_addspiritball(sd,skill_get_time(skillid,skilllv),MAX_SPIRITBALL);
		}
		break;
	case IQ_THIRD_CONSECRATION:		/* 第三撃：浄化 */
		if(flag&1) {
			/* 個別にダメージを与える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int hp = (int)((atn_bignumber)status_get_max_hp(src) * skilllv * 6 / 100);
			int sp = (int)((atn_bignumber)status_get_max_sp(src) * skilllv * 6 / 100);
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* 範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			unit_heal(src,hp,sp,0,1);
		}
		break;
	case IG_OVERSLASH:		/* オーバースラッシュ */
		if(flag&1) {
			/* 個別にダメージを与える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag|(skill_area_temp[0]&0xff));
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[0] = 0;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY,
				skill_area_sub_count);
			/* 範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case CD_ARBITRIUM:	/* アルビトリウム */
		battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		skill_addtimerskill(src,tick+500,bl->id,0,0,CD_ARBITRIUM_ATK,skilllv,0,flag);
		break;
	case SHC_SAVAGE_IMPACT:		/* サベージインパクト */
		if(flag&1) {
			/* 個別にダメージを与える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			int dist = unit_distance(src,bl);
			// ターゲットの隣接セル移動
			if(sd && !map[sd->bl.m].flag.gvg && dist > 1) {
				int dx = bl->x - sd->bl.x;
				int dy = bl->y - sd->bl.y;

				if(dx > 0) dx--;
				else if(dx < 0) dx++;
				if(dy > 0) dy--;
				else if(dy < 0) dy++;
				if(dx == 0 && dy == 0) dx++;
				if(path_search(NULL,src->m,sd->bl.x,sd->bl.y,sd->bl.x+dx,sd->bl.y+dy,1) == -1) {
					dx = bl->x - sd->bl.x;
					dy = bl->y - sd->bl.y;
					if(path_search(NULL,src->m,sd->bl.x,sd->bl.y,sd->bl.x+dx,sd->bl.y+dy,1) == -1) {
						clif_skill_fail(sd,sd->ud.skillid,SKILLFAIL_FAILED,0,0);
						break;
					}
				}
				sd->ud.to_x = sd->bl.x + dx;
				sd->ud.to_y = sd->bl.y + dy;
				clif_skill_poseffect(&sd->bl,skillid,skilllv,sd->bl.x,sd->bl.y,tick);
				clif_walkok(sd);
				clif_move(&sd->bl);
				if(dx < 0) dx = -dx;
				if(dy < 0) dy = -dy;
				sd->ud.attackabletime = sd->ud.canmove_tick = tick + sd->speed * ((dx > dy)? dx:dy);
				if(sd->ud.canact_tick < sd->ud.canmove_tick)
					sd->ud.canact_tick = sd->ud.canmove_tick;
				unit_movepos(&sd->bl,sd->ud.to_x,sd->ud.to_y,0);
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* 範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);

		}
		break;
	case SHC_ETERNAL_SLASH:		/*エターナルスラッシュ */
		sc = status_get_sc(src);
		if(sc && sc->data[SC_E_SLASH_COUNT].timer != -1) {
			if(sc->data[SC_E_SLASH_COUNT].val1 < 5) {
				status_change_start(src,GetSkillStatusChangeTable(skillid),sc->data[SC_E_SLASH_COUNT].val1+1,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		}
		else {
			status_change_start(src,GetSkillStatusChangeTable(skillid),1,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case SHC_FATAL_SHADOW_CROW:		/* フェイタルシャドウクロー */
		if(flag&1) {
			int skill;
			if(sd && (skill = pc_checkskill(sd,GC_DARKCROW)) > 0) {
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skill,0,0,0,skill_get_time(skillid,skilllv),0);
			}
			/* 個別にダメージを与える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			int dist = unit_distance(src,bl);
			// ターゲットの隣接セル移動
			if(sd && !map[sd->bl.m].flag.gvg && dist > 1) {
				int dx = bl->x - sd->bl.x;
				int dy = bl->y - sd->bl.y;

				if(dx > 0) dx--;
				else if(dx < 0) dx++;
				if(dy > 0) dy--;
				else if(dy < 0) dy++;
				if(dx == 0 && dy == 0) dx++;
				if(path_search(NULL,src->m,sd->bl.x,sd->bl.y,sd->bl.x+dx,sd->bl.y+dy,1) == -1) {
					dx = bl->x - sd->bl.x;
					dy = bl->y - sd->bl.y;
					if(path_search(NULL,src->m,sd->bl.x,sd->bl.y,sd->bl.x+dx,sd->bl.y+dy,1) == -1) {
						clif_skill_fail(sd,sd->ud.skillid,SKILLFAIL_FAILED,0,0);
						break;
					}
				}
				sd->ud.to_x = sd->bl.x + dx;
				sd->ud.to_y = sd->bl.y + dy;
				clif_skill_poseffect(&sd->bl,skillid,skilllv,sd->bl.x,sd->bl.y,tick);
				clif_walkok(sd);
				clif_move(&sd->bl);
				if(dx < 0) dx = -dx;
				if(dy < 0) dy = -dy;
				sd->ud.attackabletime = sd->ud.canmove_tick = tick + sd->speed * ((dx > dy)? dx:dy);
				if(sd->ud.canact_tick < sd->ud.canmove_tick)
					sd->ud.canact_tick = sd->ud.canmove_tick;
				unit_movepos(&sd->bl,sd->ud.to_x,sd->ud.to_y,0);
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* 範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);

		}
		break;
	case MT_RUSH_QUAKE:				/* ラッシュクエイク */
		if(flag&1) {
			/* 個別にダメージを与える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			int dist = unit_distance(src,bl);
			// ターゲットの隣接セル移動
			if(sd && !map[sd->bl.m].flag.gvg && dist > 1) {
				int dx = bl->x - sd->bl.x;
				int dy = bl->y - sd->bl.y;

				if(dx > 0) dx--;
				else if(dx < 0) dx++;
				if(dy > 0) dy--;
				else if(dy < 0) dy++;
				if(dx == 0 && dy == 0) dx++;
				if(path_search(NULL,src->m,sd->bl.x,sd->bl.y,sd->bl.x+dx,sd->bl.y+dy,1) == -1) {
					dx = bl->x - sd->bl.x;
					dy = bl->y - sd->bl.y;
					if(path_search(NULL,src->m,sd->bl.x,sd->bl.y,sd->bl.x+dx,sd->bl.y+dy,1) == -1) {
						clif_skill_fail(sd,sd->ud.skillid,SKILLFAIL_FAILED,0,0);
						break;
					}
				}
				sd->ud.to_x = sd->bl.x + dx;
				sd->ud.to_y = sd->bl.y + dy;
				clif_skill_poseffect(&sd->bl,skillid,skilllv,sd->bl.x,sd->bl.y,tick);
				clif_walkok(sd);
				clif_move(&sd->bl);
				if(dx < 0) dx = -dx;
				if(dy < 0) dy = -dy;
				sd->ud.attackabletime = sd->ud.canmove_tick = tick + sd->speed * ((dx > dy)? dx:dy);
				if(sd->ud.canact_tick < sd->ud.canmove_tick)
					sd->ud.canact_tick = sd->ud.canmove_tick;
				unit_movepos(&sd->bl,sd->ud.to_x,sd->ud.to_y,0);
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* 範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case ABC_UNLUCKY_RUSH:		/* アンラッキーラッシュ */
		{
			int dist = unit_distance(src,bl);
			// ターゲットの隣接セル移動
			if(sd && !map[sd->bl.m].flag.gvg && dist > 1) {
				int dx = bl->x - sd->bl.x;
				int dy = bl->y - sd->bl.y;

				if(dx > 0) dx--;
				else if(dx < 0) dx++;
				if(dy > 0) dy--;
				else if(dy < 0) dy++;
				if(dx == 0 && dy == 0) dx++;
				if(path_search(NULL,src->m,sd->bl.x,sd->bl.y,sd->bl.x+dx,sd->bl.y+dy,1) == -1) {
					dx = bl->x - sd->bl.x;
					dy = bl->y - sd->bl.y;
					if(path_search(NULL,src->m,sd->bl.x,sd->bl.y,sd->bl.x+dx,sd->bl.y+dy,1) == -1) {
						clif_skill_fail(sd,sd->ud.skillid,SKILLFAIL_FAILED,0,0);
						break;
					}
				}
				sd->ud.to_x = sd->bl.x + dx;
				sd->ud.to_y = sd->bl.y + dy;
				clif_skill_poseffect(&sd->bl,skillid,skilllv,sd->bl.x,sd->bl.y,tick);
				clif_walkok(sd);
				clif_move(&sd->bl);
				if(dx < 0) dx = -dx;
				if(dy < 0) dy = -dy;
				sd->ud.attackabletime = sd->ud.canmove_tick = tick + sd->speed * ((dx > dy)? dx:dy);
				if(sd->ud.canact_tick < sd->ud.canmove_tick)
					sd->ud.canact_tick = sd->ud.canmove_tick;
				unit_movepos(&sd->bl,sd->ud.to_x,sd->ud.to_y,0);
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		}
		break;
	case ABC_CHAIN_REACTION_SHOT:	/* チェーンリアクションショット */
	case ABC_CHAIN_REACTION_SHOT_ATK:	/* チェーンリアクションショット(攻撃) */
	case WH_GALESTORM:		/* ゲイルストーム */
		if(flag&1) {
			/* 個別にダメージを与える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			if(sd) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// 矢の消費
					break;
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* 範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case WH_CRESCIVE_BOLT:	/* クレッシブボルト */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		sc = status_get_sc(src);
		if(sc && sc->data[GetSkillStatusChangeTable(skillid)].timer != -1) {
			int count = sc->data[GetSkillStatusChangeTable(skillid)].val1;
			if(count < 3) {
				status_change_start(src,GetSkillStatusChangeTable(skillid),count+1,0,0,0,skill_get_time(skillid,skilllv),0);
			} else {
				status_change_start(src,GetSkillStatusChangeTable(skillid),count,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		} else {
			status_change_start(src,GetSkillStatusChangeTable(skillid),1,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case EM_ELEMENTAL_BUSTER:		/* エレメンタルバスター */
		{
			int busterid = EM_ELEMENTAL_BUSTER;
			if(sd && sd->eld) {
				switch(sd->eld->status.class_) {
					case ELEMID_EM_ARDOR:      busterid = EM_ELEMENTAL_BUSTER_FIRE;   break;
					case ELEMID_EM_DILUVIO:    busterid = EM_ELEMENTAL_BUSTER_WATER;  break;
					case ELEMID_EM_PROCELLA:   busterid = EM_ELEMENTAL_BUSTER_WIND;   break;
					case ELEMID_EM_TERREMOTUS: busterid = EM_ELEMENTAL_BUSTER_GROUND; break;
					case ELEMID_EM_SERPENS:    busterid = EM_ELEMENTAL_BUSTER_POISON; break;
				}
			}
			clif_skill_nodamage(src,bl,busterid,skilllv,1);
			skill_unitsetting(src,busterid,skilllv,src->x,src->y,0);
		}
		break;
	case NW_THE_VIGILANTE_AT_NIGHT:		/* ビジラントアットナイト */
		if(flag&1) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar;
			if(sd) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// 矢の消費
					break;
			}
			if(sd && sd->status.weapon == WT_GATLING) {
				clif_skill_nodamage(src,bl,NW_THE_VIGILANTE_AT_NIGHT_GUN_GATLING,skilllv,1);
				ar = skill_get_area(NW_THE_VIGILANTE_AT_NIGHT_GUN_GATLING,skilllv);
			} else {
				clif_skill_nodamage(src,bl,NW_THE_VIGILANTE_AT_NIGHT_GUN_SHOTGUN,skilllv,1);
				ar = skill_get_area(NW_THE_VIGILANTE_AT_NIGHT_GUN_SHOTGUN,skilllv);
			}
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			sc = status_get_sc(src);
			if(sc && sc->data[SC_INTENSIVE_AIM_COUNT].timer != -1)
				status_change_end(src, SC_INTENSIVE_AIM_COUNT, -1);
		}
		break;
	case NW_ONLY_ONE_BULLET:		/* オンリーワンバレット */
	case NW_MAGAZINE_FOR_ONE:		/* マガジンフォーワン */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		sc = status_get_sc(src);
		if(sc && sc->data[SC_INTENSIVE_AIM_COUNT].timer != -1)
			status_change_end(src, SC_INTENSIVE_AIM_COUNT, -1);
		break;
	case NW_SPIRAL_SHOOTING:		/* スパイラルシューティング */
		if(flag&1) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			if(sd) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// 矢の消費
					break;
				if(sd->status.weapon == WT_GRENADE)
					ar += 2;
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			sc = status_get_sc(src);
			if(sc && sc->data[SC_INTENSIVE_AIM_COUNT].timer != -1)
				status_change_end(src, SC_INTENSIVE_AIM_COUNT, -1);
		}
		break;
	case NW_WILD_FIRE:			/* ワイルドファイア */
	case NW_HASTY_FIRE_IN_THE_HOLE:	/* ヘイスティファイアインザホール */
	case NW_GRENADES_DROPPING:	/* グレネーズドロッピング */
	case NW_MISSION_BOMBARD:	/* ミッションボンバード */
	case SS_KAGEGARI:			/* 影狩り */
	case SS_FUUMAKOUCHIKU:		/* 風魔手裏剣 -構築- */
	case SS_KUNAIWAIKYOKU:		/* 苦無 -歪曲- */
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case NW_BASIC_GRENADE:		/* ベーシックグレネード */
	case HN_SHIELD_CHAIN_RUSH:	/* シールドチェーンラッシュ */
	case SKE_NOON_BLAST:		/* 太天一陽 */
	case SKE_SUNSET_BLAST:		/* 天陽 */
	case SKE_MIDNIGHT_KICK:		/* 太天一月 */
	case SKE_DAWN_BREAK:		/* 天月 */
	case SS_KAGEGISSEN:			/* 影一閃 */
		if(flag&1) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SOA_TALISMAN_OF_SOUL_STEALING:		/* 霊道符 */
		if(battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag)) {
			int sp = (status_get_lv(src) - 100) * skilllv;
			if(sp)
				unit_heal(src,0,sp,0,1);
		}
		break;
	case SOA_EXORCISM_OF_MALICIOUS_SOUL:	/* 死霊浄化 */
		if(flag&1) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			if(sd)
				pc_delsoulenergy(sd,MAX_SOULENERGY,0);
		}
		break;
	case SOA_TALISMAN_OF_BLUE_DRAGON:		/* 青龍符 */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		sc = status_get_sc(src);
		if(sc && sc->data[SC_T_SECOND_GOD].timer == -1 && sc->data[SC_T_THIRD_GOD].timer == -1 && sc->data[SC_T_FOURTH_GOD].timer == -1 && sc->data[SC_T_FIVETH_GOD].timer == -1) {
			status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SOA_TALISMAN_OF_WHITE_TIGER:		/* 白虎符 */
		if(flag&1) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			sc = status_get_sc(src);
			if(sc && sc->data[SC_T_FIRST_GOD].timer != -1) {
				status_change_end(src, SC_T_FIRST_GOD, -1);
				status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case SOA_TALISMAN_OF_RED_PHOENIX:		/* 朱雀符 */
		if(flag&1) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			sc = status_get_sc(src);
			if(sc && sc->data[SC_T_SECOND_GOD].timer != -1) {
				status_change_end(src, SC_T_SECOND_GOD, -1);
				status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case SOA_TALISMAN_OF_BLACK_TORTOISE:	/* 玄武符 */
	case HN_METEOR_STORM_BUSTER:	/* メテオストームバスター */
	case HN_JACK_FROST_NOVA:		/* ジャックフロストノヴァ */
	case SS_TOKEDASU:				/* 影溶き */
	case SS_REIKETSUHOU:			/* 冷血砲 */
		battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case SOA_TALISMAN_OF_FOUR_BEARING_GOD:	/* 四方神符 */
	case HN_JUPITEL_THUNDER_STORM:	/* ユピテルサンダーストーム */
	case HN_HELLS_DRIVE:			/* ヘルズドライブ */
	case HN_NAPALM_VULCAN_STRIKE:	/* ナパームバルカンストライク */
		if(flag&1) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SOA_CIRCLE_OF_DIRECTIONS_AND_ELEMENTALS:	/* 四方五行陣 */
		if(flag&1) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			sc = status_get_sc(src);
			if(sc && sc->data[SC_T_FOURTH_GOD].timer != -1) {
				status_change_end(src, SC_T_FOURTH_GOD, -1);
			}
			status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SH_CHUL_HO_SONIC_CLAW:		/* タイガースラッシュ */
	case HN_MEGA_SONIC_BLOW:		/* メガソニックブロー */
	case HN_SPIRAL_PIERCE_MAX:		/* スパイラルピアースマックス */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case SH_HOWLING_OF_CHUL_HO:		/* タイガーハウリング */
		if(flag&1) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			sc = status_get_sc(src);
			if((sd && pc_checkskill(sd,SH_COMMUNE_WITH_CHUL_HO)) || (sc && sc->data[SC_TEMPORARY_COMMUNION].timer != -1)) {
				ar += 3;
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SH_HOGOGONG_STRIKE:		/* タイガーストライク */
		if(flag&1) {
			sc = status_get_sc(bl);
			if(sc && sc->data[SC_HOGOGONG].timer != -1) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SH_HYUN_ROK_CANNON:		/* ディアーキャノン */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case HN_DOUBLEBOWLINGBASH:		/* ダブルボウリングバッシュ */
		if(flag&1) {
			/* 個別にダメージを与える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag|(skill_area_temp[0]&0xff));
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[0] = 0;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY,
				skill_area_sub_count);
			/* 範囲内の敵全体に処理を行う */
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case HN_GROUND_GRAVITATION:		/* グラウンドグラビテーション */
		if(flag&1) {
			/* 個別にダメージを与える */
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			skill_unitsetting(src,skillid,skilllv,bl->x,bl->y,0);
		}
		break;
	case SKE_RISING_SUN:		/* 天地一陽 */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		sc = status_get_sc(src);
		if(sc) {
			if(sc->data[SC_RISING_SUN].timer != -1) {		// 日出->正午
				status_change_end(src,SC_RISING_SUN,-1);
				status_change_start(src,SC_NOON_SUN,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			} else if(sc->data[SC_NOON_SUN].timer != -1) {	// 正午->日没
				status_change_end(src,SC_NOON_SUN,-1);
				status_change_start(src,SC_SUNSET_SUN,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			} else if(sc->data[SC_SUNSET_SUN].timer == -1 && sc->data[SC_RISING_MOON].timer == -1 && sc->data[SC_MIDNIGHT_MOON].timer == -1 && sc->data[SC_SKY_ENCHANT].timer == -1) {	// 日没・月出・正子・天気の身ではない
				if(sc->data[SC_DAWN_MOON].timer != -1)		// 月没は解除
					status_change_end(src,SC_DAWN_MOON,-1);
				status_change_start(src,SC_RISING_SUN,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case SKE_RISING_MOON:		/* 天地一月 */
		if(flag&1) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			sc = status_get_sc(src);
			if(sc) {
				if(sc->data[SC_RISING_MOON].timer != -1) {		// 月出->正子
					status_change_end(src,SC_RISING_MOON,-1);
					status_change_start(src,SC_MIDNIGHT_MOON,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
				} else if(sc->data[SC_MIDNIGHT_MOON].timer != -1) {	// 正子->月没
					status_change_end(src,SC_MIDNIGHT_MOON,-1);
					status_change_start(src,SC_DAWN_MOON,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
				} else if(sc->data[SC_DAWN_MOON].timer == -1 && sc->data[SC_RISING_SUN].timer == -1 && sc->data[SC_NOON_SUN].timer == -1 && sc->data[SC_SKY_ENCHANT].timer == -1) {	// 日没・月出・正子・天気の身ではない
					if(sc->data[SC_SUNSET_SUN].timer != -1)		// 日没は解除
						status_change_end(src,SC_SUNSET_SUN,-1);
					status_change_start(src,SC_RISING_MOON,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
				}
			}
		}
		break;
	case SKE_TWINKLING_GALAXY:	/* 天地万星 */
	case SKE_STAR_CANNON:		/* 天星 */
		if(flag&1) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_unitsetting(src,skillid,skilllv,bl->x,bl->y,0);
		}
		break;
	case SKE_STAR_BURST:		/* 天命落星 */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		skill_unitsetting(src,skillid,skilllv,bl->x,bl->y,0);
		break;
	case SKE_ALL_IN_THE_SKY:	/* 天羅万象 */
		{
			int dist = unit_distance(src,bl);
			// ターゲットの隣接セル移動
			if(sd && !map[sd->bl.m].flag.gvg && dist > 1) {
				int dx = bl->x - sd->bl.x;
				int dy = bl->y - sd->bl.y;

				if(dx > 0) dx--;
				else if(dx < 0) dx++;
				if(dy > 0) dy--;
				else if(dy < 0) dy++;
				if(dx == 0 && dy == 0) dx++;
				if(path_search(NULL,src->m,sd->bl.x,sd->bl.y,sd->bl.x+dx,sd->bl.y+dy,1) == -1) {
					dx = bl->x - sd->bl.x;
					dy = bl->y - sd->bl.y;
					if(path_search(NULL,src->m,sd->bl.x,sd->bl.y,sd->bl.x+dx,sd->bl.y+dy,1) == -1) {
						clif_skill_fail(sd,sd->ud.skillid,SKILLFAIL_FAILED,0,0);
						break;
					}
				}
				sd->ud.to_x = sd->bl.x + dx;
				sd->ud.to_y = sd->bl.y + dy;
				clif_skill_poseffect(&sd->bl,skillid,skilllv,sd->bl.x,sd->bl.y,tick);
				clif_walkok(sd);
				clif_move(&sd->bl);
				if(dx < 0) dx = -dx;
				if(dy < 0) dy = -dy;
				sd->ud.attackabletime = sd->ud.canmove_tick = tick + sd->speed * ((dx > dy)? dx:dy);
				if(sd->ud.canact_tick < sd->ud.canmove_tick)
					sd->ud.canact_tick = sd->ud.canmove_tick;
				unit_movepos(&sd->bl,sd->ud.to_x,sd->ud.to_y,0);
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		}
		break;
	case SS_SHIMIRU:	/* 影潜り */
		{
			int dist = unit_distance(src,bl);
			int ar = skill_get_area(skillid,skilllv);
			// ターゲットの隣接セル移動
			if(sd && !map[sd->bl.m].flag.gvg && dist > 0) {
				int dx = bl->x - sd->bl.x;
				int dy = bl->y - sd->bl.y;

				if(dx > 0) dx++;
				else if(dx < 0) dx--;
				if(dy > 0) dy++;
				else if(dy < 0) dy--;
				if(dx == 0 && dy == 0) dx--;
				if(path_search(NULL,src->m,sd->bl.x,sd->bl.y,sd->bl.x+dx,sd->bl.y+dy,1) == -1) {
					dx = bl->x - sd->bl.x;
					dy = bl->y - sd->bl.y;
					if(path_search(NULL,src->m,sd->bl.x,sd->bl.y,sd->bl.x+dx,sd->bl.y+dy,1) == -1) {
						clif_skill_fail(sd,sd->ud.skillid,SKILLFAIL_FAILED,0,0);
						break;
					}
				}
				sd->ud.to_x = sd->bl.x + dx;
				sd->ud.to_y = sd->bl.y + dy;
				clif_walkok(sd);
				clif_move(&sd->bl);
				if(dx < 0) dx = -dx;
				if(dy < 0) dy = -dy;
				sd->ud.attackabletime = sd->ud.canmove_tick = tick + sd->speed * ((dx > dy)? dx:dy);
				if(sd->ud.canact_tick < sd->ud.canmove_tick)
					sd->ud.canact_tick = sd->ud.canmove_tick;
				unit_movepos(&sd->bl,sd->ud.to_x,sd->ud.to_y,0);
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			map_foreachinarea(skill_shimiru,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_SKILL,
				src);
		}
		break;
	case SS_KAGENOMAI:		/* 影の舞 */
		if(flag&3) {
			/* 個別にダメージを与える */
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			int ar2 = skill_get_area(SS_SHINKIROU,1);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			map_foreachinarea(skill_shinkirou,
				bl->m,bl->x-ar2,bl->y-ar2,bl->x+ar2,bl->y+ar2,BL_SKILL,
				src,skillid,tick);
		}
		break;
	case SS_KUNAIKAITEN:		/* 苦無 -回転- */
		if(sd) {
			int cost = skill_get_arrow_cost(skillid,skilllv);
			if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// 矢の消費
				break;
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_unitsetting(src,skillid,skilllv,bl->x,bl->y,0);
		skill_unitsetting(src,SS_KUNAIWAIKYOKU,skilllv,bl->x,bl->y,0);
		status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	case SS_KUNAIKUSSETSU:		/* 苦無 -屈折- */
		{
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_kunaikussetsu,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_SKILL,
				src,skilllv);
		}
		break;
	case SS_SEKIENHOU:		/* 赤炎砲 */
	case SS_RAIDENPOU:		/* 雷電砲 */
	case SS_KINRYUUHOU:		/* 金龍砲 */
	case SS_ANTENPOU:		/* 暗転砲 */
		if(flag&3) {
			/* 個別にダメージを与える */
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			int ar2 = skill_get_area(SS_SHINKIROU,1);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_skill_poseffect(src,skillid,skilllv,bl->x,bl->y,tick);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			map_foreachinarea(skill_shinkirou,
				src->m,src->x-ar2,src->y-ar2,src->x+ar2,src->y+ar2,BL_SKILL,
				src,SS_ANTENPOU,tick);
		}
		break;
	case SS_KAGEAKUMU:			/* 幻術 -影縫い- */
	case SS_HITOUAKUMU:			/* 幻術 -苦無- */
		if(flag&1) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			status_change_end(bl,SC_NIGHTMARE,-1);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SS_ANKOKURYUUAKUMU:	/* 幻術 -暗黒龍- */
		if(flag&1) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			sc = status_get_sc(bl);
			if(sc && sc->data[SC_NIGHTMARE].timer != -1) {
				skill_addtimerskill(src,tick+500,bl->id,0,0,skillid,skilllv,0,(0x0f<<20)|flag|2);
				status_change_end(bl,SC_NIGHTMARE,-1);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case EL_FIRE_BOMB:		/* ファイアーボム */
	case EL_FIRE_WAVE:		/* ファイアーウェーブ */
	case EL_WATER_SCREW:	/* ウォータースクリュー */
		if(flag&1) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid+1,skilllv,tick,(0x0f<<20)|0x0500);
		} else {
			if(atn_rand()%10000 < 7000) {
				battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			} else {
				int ar = skill_get_area(skillid,skilllv);
				clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
				map_foreachinarea(skill_area_sub,
					bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
					src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
					skill_castend_damage_id);
			}
		}
		break;
	case EL_TIDAL_WEAPON:	/* タイダルウェポン */
		if(atn_rand()%10000 < 7000) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else if(eld && eld->msd) {
			clif_skill_nodamage(src,&eld->msd->bl,skillid,skilllv,1);
			//clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			status_change_start(&eld->msd->bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			status_change_start(bl,GetSkillStatusChangeTable(skillid)+1,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case EL_HURRICANE:		/* ハリケーンレイジ */
		if(flag&1) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid+1,skilllv,tick,(0x0f<<20)|0x0500);
		} else {
			if(atn_rand()%10000 < 7000) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			} else {
				int ar = skill_get_area(skillid,skilllv);
				clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
				map_foreachinarea(skill_area_sub,
					bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
					src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
					skill_castend_damage_id);
			}
		}
		break;
	case EL_TYPOON_MIS:		/* タイフーンミサイル */
	case EL_ROCK_CRUSHER:	/* ロックランチャー */
		if(atn_rand()%10000 < 7000) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid+1,skilllv,tick,flag);
		}
		break;
	case EL_STONE_RAIN:		/* ストーンレイン */
		if(flag&1) {
			battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		} else {
			if(atn_rand()%10000 < 7000) {
				battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			} else {
				int ar = skill_get_area(skillid,skilllv);
				clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
				map_foreachinarea(skill_area_sub,
					bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
					src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
					skill_castend_damage_id);
			}
		}
		break;
	case EM_EL_FLAMEROCK:		/* フレイムロック */
	case EM_EL_STORM_WIND:		/* ストームウインド */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_unitsetting(src,skillid,skilllv,src->x,src->y,0);
		skill_unitsetting(src,skillid,skilllv,bl->x,bl->y,0);
		break;
	case EM_EL_AGE_OF_ICE:		/* エイジオブアイス */
	case EM_EL_AVALANCHE:		/* アバランチェ */
	case EM_EL_DEADLY_POISON:	/* デッドリーポイズン */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_unitsetting(src,skillid,skilllv,bl->x,bl->y,0);
		break;
	case 0:
		if(sd) {
			if(flag&3) {
				if(bl->id != skill_area_temp[1])
					battle_skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
			} else {
				int ar = sd->splash_range;
				skill_area_temp[1] = bl->id;
				map_foreachinarea(skill_area_sub,
					bl->m, bl->x - ar, bl->y - ar, bl->x + ar, bl->y + ar, (BL_CHAR|BL_SKILL),
					src, skillid, skilllv, tick, flag|BCT_ENEMY|1,
					skill_castend_damage_id);
			}
		}
		break;
	default:
		map_freeblock_unlock();
		return 1;
	}
	map_freeblock_unlock();

	return 0;
}
