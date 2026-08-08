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
 * スキル使用（詠唱完了、場所指定の実際の処理）
 *------------------------------------------
 */
int skill_castend_pos2( struct block_list *src, int x,int y,int skillid,int skilllv,unsigned int tick,int flag)
{
	struct map_session_data *sd = NULL;

	nullpo_retr(0, src);

	sd = BL_DOWNCAST( BL_PC, src );

	switch(skillid) {
	case WZ_METEOR:
	case WZ_ICEWALL:
	case MO_BODYRELOCATION:
	case AM_CANNIBALIZE:
	case AM_SPHEREMINE:
	case CR_CULTIVATION:
	case SC_ESCAPE:
	case SU_CN_METEOR:
	case SU_CN_METEOR2:
	case HN_METEOR_STORM_BUSTER:
		break;
	default:
		clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
	}

	switch(skillid)
	{
	case AC_SHOWER:				/* アローシャワー */
	case MA_SHOWER:
		{
			int ar = skill_get_area(skillid,skilllv);
			if(sd) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// 矢の消費
					break;
			}
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			map_foreachinarea(skill_area_trap_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,BL_SKILL,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;

	case PR_BENEDICTIO:			/* 聖体降福 */
		{
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,BL_PC,
				src,skillid,skilllv,tick, flag|BCT_ALL|1,
				skill_castend_nodamage_id);
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ALL|1,
				skill_castend_damage_id);
		}
		break;

	case BS_HAMMERFALL:			/* ハンマーフォール */
		skill_addtimerskill(src,tick+skill_get_time(skillid,skilllv),0,x,y,skillid,skilllv,BF_WEAPON,flag|BCT_ENEMY|2);
		break;

	case HT_DETECTING:				/* ディテクティング */
		{
			int ar = skill_get_area(skillid,skilllv);
			map_foreachinarea(status_change_timer_sub,src->m,x-ar,y-ar,x+ar,y+ar,BL_CHAR,src,SC_SIGHT,skilllv,tick);
		}
		break;

	case WZ_ICEWALL:			/* アイスウォール */
		if(map[src->m].flag.noicewall) {
			if(sd)
				clif_skill_fail(sd,skillid,SKILLFAIL_MAP,0,0);
		} else {
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
			skill_unitsetting(src,skillid,skilllv,x,y,0);
		}
		break;

	case MG_SAFETYWALL:			/* セイフティウォール */
	case MG_FIREWALL:			/* ファイアーウォール */
	case MG_THUNDERSTORM:		/* サンダーストーム */
	case AL_PNEUMA:				/* ニューマ */
	case WZ_FIREPILLAR:			/* ファイアピラー */
	case WZ_VERMILION:			/* ロードオブヴァーミリオン */
	case WZ_FROSTNOVA:          /* フロストノヴァ */ 
	case WZ_HEAVENDRIVE:		/* ヘヴンズドライブ */
	case WZ_QUAGMIRE:			/* クァグマイア */
	case PR_SANCTUARY:			/* サンクチュアリ */
	case PR_MAGNUS:				/* マグヌスエクソシズム */
	case CR_GRANDCROSS:			/* グランドクロス */
	case NPC_GRANDDARKNESS:			/* グランドダークネス */
	case AS_VENOMDUST:			/* ベナムダスト */
	case AM_DEMONSTRATION:		/* デモンストレーション */
	case PF_SPIDERWEB:			/* スパイダーウェブ */
	case PF_FOGWALL:			/* ウォールオブフォグ */
	case NJ_TATAMIGAESHI:		/* 畳返し */
	case NJ_BAKUENRYU:			/* 龍炎陣 */
	case NJ_HYOUSYOURAKU:		/* 氷柱落し */
	case MH_POISON_MIST:		/* ポイズンミスト */
	case MH_STEINWAND:			/* シュタインワンド */
	case MH_LAVA_SLIDE:			/* ラーヴァスライド */
	case MH_VOLCANIC_ASH:		/* ボルカニックアッシュ */
	case NPC_EVILLAND:			/* イービルランド */
	case NPC_VENOMFOG:			/* ベナムフォグ */
	case NPC_FLAMECROSS:		/* フレイムクロス */
	case NPC_HELLBURNING:		/* ヘルバーニング */
	case NPC_REVERBERATION:		/* M振動残響 */
	case NPC_CLOUD_KILL:			/* Mクラウドキル */
	case NPC_PSYCHIC_WAVE:		/* Mサイキックウェーブ */
	case NPC_CANE_OF_EVIL_EYE:		/* ケーンオブイビルアイ */
	case GC_POISONSMOKE:		/* ポイズンスモーク */
	case WL_COMET:				/* コメット */
	case NPC_COMET:				/* Mコメット */
	case SC_MANHOLE:			/* マンホール */
	case SC_DIMENSIONDOOR:		/* ディメンションドア */
	case SC_CHAOSPANIC:			/* カオスパニック */
	case SC_MAELSTROM:			/* メイルストーム */
	case SC_BLOODYLUST:			/* ブラッディラスト */
	case WM_REVERBERATION:		/* 振動残響 */
	case WM_POEMOFNETHERWORLD:	/* 地獄の歌 */
	case SO_EARTHGRAVE:			/* アースグレイブ */
	case SO_DIAMONDDUST:		/* ダイヤモンドダスト */
	case SO_PSYCHIC_WAVE:		/* サイキックウェーブ */
	case SO_CLOUD_KILL:			/* クラウドキル */
	case SO_WARMER:				/* ウォーマー */
	case SO_VACUUM_EXTREME:		/* バキュームエクストリーム */
	case SO_FIRE_INSIGNIA:		/* ファイアーインシグニア */
	case SO_WATER_INSIGNIA:		/* ウォーターインシグニア */
	case SO_WIND_INSIGNIA:		/* ウィンドインシグニア */
	case SO_EARTH_INSIGNIA:		/* アースインシグニア */
	case GN_THORNS_TRAP:		/* ソーントラップ */
	case GN_DEMONIC_FIRE:		/* デモニックファイアー */
	case GN_HELLS_PLANT:		/* ヘルズプラント */
	case SU_NYANGGRASS:			/* ニャングラス */
	case SJ_BOOKOFCREATINGSTAR:	/* 創星の書 */
	case AG_RAIN_OF_CRYSTAL:	/* レインオブクリスタル */
	case AG_MYSTERY_ILLUSION:	/* ミステリーイリュージョン */
	case AG_STRANTUM_TREMOR:	/* ストラタムトレマー */
	case AG_TORNADO_STORM:		/* トルネードストーム */
	case AG_FLORAL_FLARE_ROAD:	/* フローラルフレアロード */
	case IG_CROSS_RAIN:			/* クロスレイン */
	case CD_PNEUMATICUS_PROCELLA:	/* ニューマティックプロセラ */
	case ABC_ABYSS_STRIKE:		/* オメガアビスストライク */
	case ABC_ABYSS_SQUARE:		/* アビススクエア */
	case WH_DEEPBLINDTRAP:		/* ディープブラインドトラップ */
	case WH_SOLIDTRAP:			/* ソリッドトラップ */
	case WH_SWIFTTRAP:			/* スイフトトラップ */
	case WH_FLAMETRAP:			/* フレイムトラップ */
	case EM_DIAMOND_STORM:		/* ダイヤモンドストーム */
	case EM_LIGHTNING_LAND:		/* ライトニングランド */
	case EM_VENOM_SWAMP:		/* ベナムスワンプ */
	case EM_CONFLAGRATION:		/* コンフラグレーション */
	case EM_TERRA_DRIVE:		/* テラドライブ */
	case NW_GRENADES_DROPPING:	/* グレネーズドロッピング */
	case SOA_TOTEM_OF_TUTELARY:	/* 城隍堂 */
	case SH_HYUN_ROKS_BREEZE:	/* ディアーブリーズ */
	case SS_SHINKIROU:			/* 蜃気楼分身 */
	case SS_FUUMASHOUAKU:		/* 風魔手裏剣 -掌握- */
	case MA_SKIDTRAP:
	case MA_LANDMINE:
	case MA_SANDMAN:
	case MA_FREEZINGTRAP:
		skill_unitsetting(src,skillid,skilllv,x,y,0);
		break;
	case HT_SKIDTRAP:			/* スキッドトラップ */
	case HT_LANDMINE:			/* ランドマイン */
	case HT_ANKLESNARE:			/* アンクルスネア */
	case HT_SHOCKWAVE:			/* ショックウェーブトラップ */
	case HT_SANDMAN:			/* サンドマン */
	case HT_FLASHER:			/* フラッシャー */
	case HT_FREEZINGTRAP:		/* フリージングトラップ */
	case HT_BLASTMINE:			/* ブラストマイン */
	case HT_CLAYMORETRAP:		/* クレイモアトラップ */
	case HT_TALKIEBOX:			/* トーキーボックス */
		if(sd) {
			int i, nameid, amount, idx, trapid = 0;
			for(i = 0; i < MAX_SKILL_DB_ITEM; i++) {
				nameid = skill_db[skill_get_skilldb_id(skillid)].itemid[i];
				amount = skill_db[skill_get_skilldb_id(skillid)].amount[i];
				if(nameid <= 0 || amount <= 0)
					continue;
				idx = pc_search_inventory(sd,nameid);

				// トラップ研究を習得中で設置用トラップが足りなかった場合
				if((idx < 0 || sd->status.inventory[idx].amount < amount) &&
					pc_checkskill(sd,RA_RESEARCHTRAP) && nameid == 1065)
				{
					// 改良型設置用トラップを検索
					nameid = 7940;
					amount = 1;
					idx = pc_search_inventory(sd,nameid);
				}

				if(idx >= 0 && sd->status.inventory[idx].amount >= amount) {
					pc_delitem(sd,idx,amount,0,1);
					// 消費したのがトラップ系アイテムの場合
					if(nameid == 1065 || nameid == 7940)
						trapid = nameid;
				}
			}
			skill_unitsetting(src,skillid,skilllv,x,y,trapid);
		} else {
			skill_unitsetting(src,skillid,skilllv,x,y,0);
		}
		break;
	case HW_GRAVITATION:		/* グラビテーションフィールド */
		{
			struct skill_unit_group *sg = skill_unitsetting(src,skillid,skilllv,x,y,0);
			if(sg) {
				struct unit_data *ud = unit_bl2ud(src);
				if(ud && DIFF_TICK(ud->canact_tick, tick) < 5000) {
					// 発動後5秒間はリログ禁止
					ud->canact_tick = tick + 5000;
				}
				status_change_start(src,SC_GRAVITATION_USER,skilllv,0,0,sg->bl.id,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case RG_GRAFFITI:			/* グラフィティ */
		status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,x,y,0,skill_get_time(skillid,skilllv),0);
		break;
	case GS_GROUNDDRIFT:			/* グラウンドドリフト */
		if(sd) {
			int idx = sd->equip_index[EQUIP_INDEX_ARROW];
			if(idx >= 0 && sd->inventory_data[idx]) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// 弾の消費
					break;
				skill_unitsetting(src,skillid,skilllv,x,y,sd->arrow_ele);
			}
		} else {
			skill_unitsetting(src,skillid,skilllv,x,y,0);
		}
		break;

	case SA_VOLCANO:		/* ボルケーノ */
	case SA_DELUGE:			/* デリュージ */
	case SA_VIOLENTGALE:		/* バイオレントゲイル */
	case SA_LANDPROTECTOR:		/* ランドプロテクター */
	case NJ_SUITON:			/* 水遁 */
	case NJ_KAENSIN:		/* 火炎陣 */
		skill_clear_element_field(src);	// 既に自分が発動している属性場をクリア
		skill_unitsetting(src,skillid,skilllv,x,y,0);
		break;

	case WZ_METEOR:			/* メテオストーム */
		{
			int ar = skill_get_area(skillid,skilllv);
			int i, tmpx = 0, tmpy = 0, x1 = 0, y1 = 0;
			int interval = (skilllv > 10)? 2500: 1000;
			int loop = skilllv / 2 + 2;
			for(i=0; i < loop; i++) {
				if(skilllv > 10) {
					tmpx = x + (atn_rand()%29 - 14);
					tmpy = y + (atn_rand()%29 - 14);
				} else {
					tmpx = x + (atn_rand()%(ar*2+1) - ar);
					tmpy = y + (atn_rand()%(ar*2+1) - ar);
				}
				if(i == 0 && map_getcell(src->m,tmpx,tmpy,CELL_CHKPASS)) {
					clif_skill_poseffect(src,skillid,skilllv,tmpx,tmpy,tick);
				} else if(i > 0) {
					skill_addtimerskill(src,tick+i*interval,0,tmpx,tmpy,skillid,skilllv,(x1<<16)|y1,0);
				}
				x1 = tmpx;
				y1 = tmpy;
			}
			skill_addtimerskill(src,tick+i*interval,0,tmpx,tmpy,skillid,skilllv,-1,0);
		}
		break;

	case WZ_STORMGUST:          /* ストームガスト */ 
		{
			int ar = skill_get_area(skillid,skilllv);
			int i, j;

			// ユニットを南西→北東まで81個作る
			for(i = 0; i < (ar*2+1); i++) {
				for(j = 0; j < (ar*2+1); j++) {
					skill_unitsetting(src,skillid,skilllv,x-ar+i,y-ar+j,0);
				}
			}
		}
		break;

	case AL_WARP:				/* ワープポータル */
		if(sd) {
			const char *p[3];
			int i = 0;
			if(battle_config.noportal_flag) {
				if(map[sd->bl.m].flag.noportal)		// noportalで禁止
					break;
			} else {
				if(map[sd->bl.m].flag.noteleport)	// noteleportで禁止
					break;
			}
			for(i=0; i<3; i++) {
				if(sd->ud.skilllv > i+1 && i < MAX_PORTAL_MEMO)
					p[i] = sd->status.memo_point[i].map;
				else
					p[i] = "";
			}
			clif_skill_warppoint(sd,sd->ud.skillid,sd->status.save_point.map, p[0], p[1], p[2]);
		}
		break;
	case HW_GANBANTEIN:			/* ガンバンテイン */
		if(atn_rand()%100 < 80) {
			map_foreachinarea(skill_delunit_by_ganbantein,src->m,x-1,y-1,x+1,y+1,BL_SKILL);
		} else if(sd) {
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		}
		break;
	case MO_BODYRELOCATION:			/* 残影 */
		{
			struct status_change *sc = status_get_sc(src);
			if(!sc || sc->data[SC_ANKLE].timer == -1) {
				if(sd) {
					sd->skillstatictimer[MO_EXTREMITYFIST] = tick + 2000;
				}
#if PACKETVER < 20111025
				clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
				unit_movepos(src,x,y,1);
#else
				unit_movepos(src,x,y,2);
#endif
			}
		}
		break;
	case AM_CANNIBALIZE:	/* バイオプラント */
		if(sd) {
			int n, id = 0;
			const int summons[5] = { 1589, 1579, 1575, 1555, 1590 };
			struct mob_data *tmpmd = NULL;

			n  = (skilllv > 5)? 4: skilllv - 1;
			id = mob_once_spawn(sd, sd->bl.m, x, y, sd->status.name, summons[n], 1, "");

			if((tmpmd = map_id2md(id)) != NULL) {
				tmpmd->master_id = sd->bl.id;
				tmpmd->guild_id  = status_get_guild_id(src);
				tmpmd->hp        = 1500 + skilllv * 200 + sd->status.base_level * 10;

				// 非移動でアクティブで反撃する[0x0:非移動 0x1:移動 0x4:ACT 0x8:非ACT 0x40:反撃無 0x80:反撃有]
				tmpmd->mode = MD_AGGRESSIVE + MD_CANATTACK;

				tmpmd->deletetimer  = add_timer(tick+skill_get_time(skillid,skilllv),mob_timer_delete,id,NULL);
				tmpmd->state.nodrop = battle_config.cannibalize_no_drop;
				tmpmd->state.noexp  = battle_config.cannibalize_no_exp;
				tmpmd->state.nomvp  = battle_config.cannibalize_no_mvp;
				tmpmd->state.special_mob_ai = MOB_AI_SUMMON;
			}
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
		}
		break;
	case CR_CULTIVATION:	/* 植物栽培 */
		if(sd) {
			int id, n = (skilllv >= 2)? 1: 0;
			const int summons[2][6] = {
				{ 1084, 1085, 1084, 1085, 1084, 1085 },
				{ 1078, 1079, 1080, 1081, 1082, 1083 }
			};
			int i = skilllv - 1;
			int j = pc_search_inventory(sd,skill_db[skillid].lv_itemid[i]);
			struct mob_data *tmpmd = NULL;

			if(j < 0 || skill_db[skillid].lv_itemid[i] <= 0 || sd->inventory_data[j] == NULL ||
				sd->status.inventory[j].amount < skill_db[skillid].lv_amount[i] ||
				map_count_oncell(src->m,x,y,BL_MOB) || atn_rand()%100 < 50)
			{
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				break;
			}

			id = mob_once_spawn(sd, sd->bl.m, x, y, "--ja--", summons[n][atn_rand()%6], 1, "");

			if((tmpmd = map_id2md(id)) != NULL)
				tmpmd->deletetimer = add_timer(tick+skill_get_time(skillid,skilllv),mob_timer_delete,id,NULL);
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
		}
		break;
	case AM_SPHEREMINE:	/* スフィアーマイン */
		if(sd) {
			int id = 0;
			struct mob_data *tmpmd = NULL;

			id = mob_once_spawn(sd, sd->bl.m, x, y, sd->status.name, 1142, 1, "");

			if((tmpmd = map_id2md(id)) != NULL) {
				tmpmd->master_id    = sd->bl.id;
				tmpmd->hp           = 2000 + skilllv * 400;
				tmpmd->def_ele      = 40 + ELE_WATER;
				tmpmd->deletetimer  = add_timer(tick+skill_get_time(skillid,skilllv),mob_timer_delete,id,NULL);
				tmpmd->state.nodrop = battle_config.spheremine_no_drop;
				tmpmd->state.noexp  = battle_config.spheremine_no_exp;
				tmpmd->state.nomvp  = battle_config.spheremine_no_mvp;
				tmpmd->state.special_mob_ai = MOB_AI_SPHERE1;
			}
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
		}
		break;
	case CR_SLIMPITCHER:
		if(sd) {
			int ar = skill_get_area(skillid,skilllv);
			int i = (skilllv > 10)? 9: skilllv - 1;
			int j, itemid;

			if(battle_config.slimpitcher_nocost && !map[sd->bl.m].flag.pvp && !map[sd->bl.m].flag.gvg) {
				const int potion[10] = { 501, 501, 501, 501, 501, 503, 503, 503, 503, 504 };
				itemid = potion[i];
			} else {
				itemid = skill_db[skillid].lv_itemid[i];
			}
			j = pc_search_inventory(sd,itemid);
			if(j < 0 || itemid <= 0 || sd->inventory_data[j] == NULL ||
			   sd->status.inventory[j].amount < skill_db[skillid].lv_amount[i]) {
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				return 1;
			}
			sd->state.potionpitcher_flag = 1;
			sd->potion.hp = 0;
			if(sd->inventory_data[j]->use_script) {
				run_script(sd->inventory_data[j]->use_script,0,sd->bl.id,0);
			}
			pc_delitem(sd,j,skill_db[skillid].lv_amount[i],0,1);
			sd->state.potionpitcher_flag = 0;
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
			if(sd->potion.hp > 0) {
				map_foreachinarea(skill_area_sub,
					src->m,x-ar,y-ar,x+ar,y+ar,BL_CHAR,
					src,skillid,skilllv,tick,flag|BCT_PARTY|1,
					skill_castend_nodamage_id);
			}
		}
		break;
	case NJ_HUUMA:		/* 風魔手裏剣投げ */
		{
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[0] = 0;
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NJ_RAIGEKISAI:	/* 雷撃砕 */
#ifndef PRE_RENEWAL
		clif_skill_nodamage(src,src,skillid,skilllv,1);
#endif
		skill_unitsetting(src,skillid,skilllv,x,y,0);
		break;
	case NJ_SHADOWJUMP:	/* 影跳び */
		if(sd && map[sd->bl.m].flag.gvg) {
			clif_skill_fail(sd,skillid,SKILLFAIL_MAP,0,0);
		} else {
			struct status_change *sc = status_get_sc(src);
			if(!sc || sc->data[SC_ANKLE].timer == -1) {
				// 崖打ち可能セルは無視して移動
				if(map_getcellp(&map[src->m],x,y,CELL_CHKPASS)) {
					unit_movepos(src,x,y,0x21);
					status_change_end(src, SC_HIDING, -1);
				}
			}
		}
		break;
	case MH_XENO_SLASHER:		/*ゼノスラッシャー */
		{
			int ar = skill_get_area(skillid,skilllv);

			skill_area_temp[1] = src->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case RK_WINDCUTTER:	/* ウィンドカッター */
		{
			int dir = path_calc_dir(src,x,y);
			skill_area_temp[1] = src->id;
			clif_skill_nodamage(src,src,skillid,skilllv,1);
			map_foreachinshootpath(
				skill_area_sub,src->m,src->x,src->y,dirx[dir],diry[dir],7,skill_get_area(skillid,skilllv),(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,skill_castend_damage_id
			);
		}
		break;
	case RK_DRAGONBREATH:		/* ファイアードラゴンブレス */
	case RK_DRAGONBREATH_WATER:	/* ウォータードラゴンブレス */
		{
			int ar = skill_get_area(skillid,skilllv);

			skill_area_temp[1] = src->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			clif_skill_nodamage(src,src,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case AB_EPICLESIS:			/* エピクレシス */
		{
			int ar = skill_get_unit_range(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,BL_PC,
				src,ALL_RESURRECTION,3,tick,flag|BCT_NOENEMY|1,
				skill_castend_nodamage_id);
			skill_unitsetting(src,skillid,skilllv,x,y,0);
		}
		break;
	case WL_EARTHSTRAIN:		/* アースストレイン */
		{
			int dir = 4;
			int tmpx, tmpy;
			int addx = 0, addy = 0;
			int i, loop = skilllv + 4;
			struct skill_unit_group *sg = NULL;

			if(src->type == BL_PC)
				dir = (src->x == x && src->y == y)? 4: path_calc_dir(src,x,y);

			// 縦を優先
			addy = diry[dir];
			addx = (addy == 0)? dirx[dir]: 0;

			// 初期位置を指定
			tmpx = src->x + addx;
			tmpy = src->y + addy;

			sg = skill_unitsetting(src,skillid,skilllv,tmpx,tmpy,0);
			if(sg) {
				for(i = 1; i < loop; i++) {
					tmpx += addx;
					tmpy += addy;

					skill_addtimerskill(src,tick+i*200,0,addx,addy,skillid,skilllv,sg->bl.id,(tmpx<<16)|tmpy);
				}
			}
		}
		break;
	case RA_DETONATOR:				/* デトネイター */
		{
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			map_foreachinarea(skill_detonator,src->m,x-ar,y-ar,x+ar,y+ar,BL_SKILL,src);
		}
		break;
	case RA_ELECTRICSHOCKER:	/* エレクトリックショッカー */
	case RA_CLUSTERBOMB:		/* クラスターボム */
	case RA_MAGENTATRAP:		/* マゼンタトラップ */
	case RA_COBALTTRAP:			/* コバルトトラップ */
	case RA_MAIZETRAP:			/* メイズトラップ */
	case RA_VERDURETRAP:		/* ヴェルデュールトラップ */
	case RA_FIRINGTRAP:			/* ファイアリングトラップ */
	case RA_ICEBOUNDTRAP:		/* アイスバウンドトラップ */
		if(sd)
			skill_unitsetting(src,skillid,skilllv,x,y,7940);
		else
			skill_unitsetting(src,skillid,skilllv,x,y,0);
		break;
	case NC_COLDSLOWER:	/* コールドスローワー */
		{
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NC_SILVERSNIPER:	/* FAW シルバースナイパー */
		if(sd) {
			int id;
			struct mob_data *tmpmd = NULL;

			id = mob_once_spawn(sd, sd->bl.m, x, y, sd->status.name, 2042, 1, "");

			if((tmpmd = map_id2md(id)) != NULL) {
				tmpmd->master_id    = sd->bl.id;
				tmpmd->guild_id     = status_get_guild_id(src);
				tmpmd->deletetimer  = add_timer(tick+skill_get_time(skillid,skilllv),mob_timer_delete,id,NULL);
				tmpmd->state.nodrop = battle_config.cannibalize_no_drop;
				tmpmd->state.noexp  = battle_config.cannibalize_no_exp;
				tmpmd->state.nomvp  = battle_config.cannibalize_no_mvp;
				tmpmd->state.special_mob_ai = MOB_AI_SUMMON;
			}
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
		}
		break;
	case NC_MAGICDECOY:		/* FAW マジックデコイ */
		if(sd) {
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
			clif_magicdecoy_list(sd,skilllv,x,y);
		}
		break;
	case NC_MAGMA_ERUPTION:	/* マグマイラプション */
	case NPC_MAGMA_ERUPTION:	/* Mマグマイラプション */
		skill_addtimerskill(src,tick+1000,0,x,y,skillid,skilllv,0,flag);
		break;
	case LG_OVERBRAND:		/* オーバーブランド */
		{
			int dir = path_calc_dir(src,x,y);
			map_foreachinshootpath(
				skill_area_sub,src->m,src->x,src->y,dirx[dir],diry[dir],6,1,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY,skill_castend_damage_id
			);
			skill_addtimerskill(src,tick+200,0,x,y,LG_OVERBRAND_BRANDISH,skilllv,0,flag);
		}
		break;
	case LG_RAYOFGENESIS:	/* レイオブジェネシス */
	case NPC_RAYOFGENESIS:	/* Mレイオブジェネシス */
		{
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SR_RIDEINLIGHTNING:	/* 雷光弾 */
		{
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case WM_DOMINION_IMPULSE:		/* ドミニオンインパルス */
		{
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
			map_foreachinarea(skill_dominion_impulse,src->m,x-ar,y-ar,x+ar,y+ar,BL_SKILL);
		}
		break;
	case WM_SEVERE_RAINSTORM:	/* シビアレインストーム */
		if(sd) {
			int cost = skill_get_arrow_cost(skillid,skilllv);
			if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// 矢の消費
				break;
		}
		skill_unitsetting(src,skillid,skilllv,x,y,0);
		break;
	case WM_LULLABY_DEEPSLEEP:		/* 安らぎの子守唄 */
		{
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ALL|1,
				skill_castend_nodamage_id);
		}
		break;
	case WM_GREAT_ECHO:			/* グレートエコー */
		{
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case SO_ARRULLO:	/* アルージョ */
		{
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case GN_CRAZYWEED:		/* クレイジーウィード */
		{
			int ar = skill_get_area(skillid,skilllv);
			int tmpx, tmpy, i, num;
			clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
			num = skill_get_num(skillid,skilllv);
			for(i=0; i<num; i++) {
				tmpx = x + (atn_rand()%(ar*2+1) - ar);
				tmpy = y + (atn_rand()%(ar*2+1) - ar);
				skill_addtimerskill(src,tick+i*200,0,tmpx,tmpy,skillid,skilllv,0,0);
			}
		}
		break;
	case GN_FIRE_EXPANSION:		/* ファイアーエクスパンション */
		if(sd) {
			int i = (skilllv > skill_get_max(skillid))? skill_get_max(skillid) - 1: skilllv - 1;
			int id, j;

			if(i >= 10) {
				i = 9;
			}
			id = skill_get_skilldb_id(skillid);
			j  = pc_search_inventory(sd,skill_db[id].lv_itemid[i]);

			if(j < 0 || sd->inventory_data[j] == NULL ||
			   sd->status.inventory[j].amount < skill_db[id].lv_amount[i]) {
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				break;
			}
			pc_delitem(sd,j,skill_db[id].lv_amount[i],0,1);
		}
		clif_skill_poseffect(src,skillid,skilllv,x,y,tick);
		map_foreachinarea(skill_fire_expansion,src->m,x-2,y-2,x+2,y+2,BL_SKILL,src,skilllv,tick);
		break;
	case KO_MUCHANAGE:		/* 無茶投げ */
		{
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[0] = 0;
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY,
				skill_area_sub_count);
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY,
				skill_castend_damage_id);
		}
		break;
	case KO_MAKIBISHI:			/* 撒菱 */
		{
			int ar = skill_get_area(skillid,skilllv);
			int i;
			for(i = 0; i < skilllv+2; i++) {
				x = src->x - ar + atn_rand()%(ar*2+1);
				y = src->y - ar + atn_rand()%(ar*2+1);
				skill_unitsetting(src,skillid,skilllv,x,y,0);
			}
		}
		break;
	case KO_ZENKAI:		/* 術式全開 */
		skill_unitsetting(src,skillid,skilllv,x,y,0);
		if(sd && sd->elementball.num)
			pc_delelementball(sd,sd->elementball.num,0);
		break;
	case RL_FALLEN_ANGEL:		/* フォーリンエンジェル */
		if( !map[src->m].flag.turbo && (!map[src->m].flag.noteleport || map[src->m].flag.gvg) && !map[src->m].flag.nojump &&
		    map_getcell(src->m,x,y,CELL_CHKPASS)
		) {
			unit_movepos(src,x,y,1);
			clif_skill_nodamage(src,src,skillid,skilllv,1);
			status_change_start(src,SC_FALLEN_ANGEL,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		else if(sd)
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		break;
	case RL_FIRE_RAIN:	/* ファイアーレイン */
		{
			int dir = (src->x == x && src->y == y)? 0: path_calc_dir(src,x,y);
			int tmpx, tmpy;
			int addx = 0, addy = 0;
			int dist = path_distance(src->x,src->y,x,y);
			int i;

			// 縦を優先
			addy = diry[dir];
			addx = (addy == 0)? dirx[dir]: 0;

			// 初期位置を指定
			tmpx = src->x + addx * dist;
			tmpy = src->y + addy * dist;

			clif_skill_poseffect(src,skillid,skilllv,tmpx,tmpy,tick);
			for(i = 1; i <= 10; i++) {
				skill_addtimerskill(src,tick+i*100,0,tmpx,tmpy,skillid,skilllv,0,flag);
				tmpx += addx;
				tmpy += addy;
			}
		}
		break;
	case SU_LOPE:		/* ニャンジャンプ */
		if( !map[src->m].flag.turbo && (!map[src->m].flag.noteleport || map[src->m].flag.gvg) && !map[src->m].flag.nojump &&
		    map_getcell(src->m,x,y,CELL_CHKPASS) && !map_count_oncell(src->m,x,y,BL_PC|BL_MOB|BL_NPC)
		) {
			unit_movepos(src,x,y,1);
			clif_skill_nodamage(src,src,skillid,skilllv,1);
		}
		else if(sd)
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		break;
	case SU_CN_METEOR:	/* イヌハッカメテオ */
	case SU_CN_METEOR2:			/* イヌハッカメテオ(呪い) */
		{
			int i, tmpx = 0, tmpy = 0, x1 = 0, y1 = 0;
			int ar = skill_get_area(skillid,skilllv);
			int interval = 650;
			int skill = SU_CN_METEOR;
			if(sd) {
				int nameid, amount, idx = 0;

				nameid = 11602;	// イヌハッカの実
				amount = 1;

				idx = pc_search_inventory(sd,nameid);

				if(idx >= 0 && sd->status.inventory[idx].amount >= amount) {	// イヌハッカの実を持ってたら消費
					pc_delitem(sd,idx,amount,0,1);
					skill = SU_CN_METEOR2;
				}
			}
			for(i=0; i < 7; i++) {
				tmpx = x + atn_rand()%(ar*2+1) - ar;
				tmpy = y + atn_rand()%(ar*2+1) - ar;
				if(i == 0 && map_getcell(src->m,tmpx,tmpy,CELL_CHKPASS)) {
					clif_skill_poseffect(src,skill,skilllv,tmpx,tmpy,tick);
				} else if(i > 0) {
					skill_addtimerskill(src,tick+i*interval,0,tmpx,tmpy,skill,skilllv,(x1<<16)|y1,0);
				}
				x1 = tmpx;
				y1 = tmpy;
			}
			skill_addtimerskill(src,tick+i*interval,0,tmpx,tmpy,skill,skilllv,-1,0);
		}
		break;
	case NPC_LEX_AETERNA:		/* Mレックスエーテルナ */
		{
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,src,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case NPC_DRAGONBREATH:	/* Mドラゴンブレス */
		{
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case NPC_WIDESUCK:		/* ワイドブラッド */
		skill_area_temp[1] = src->id;
		skill_area_temp[2] = x;
		skill_area_temp[3] = y;
		skill_addtimerskill(src,tick+500,0,x,y,skillid,skilllv,0,0);
		skill_addtimerskill(src,tick+1500,0,x,y,skillid,skilllv,0,0);
		skill_addtimerskill(src,tick+2500,0,x,y,skillid,skilllv,0,0);
		break;
	case AG_VIOLENT_QUAKE:		/* バイオレントクエイク */
	case AG_ALL_BLOOM:			/* オールブルーム */
		{
			int climax = 0;
			struct status_change *sc = status_get_sc(src);
			if(sc && sc->data[SC_CLIMAX].timer != -1)
				climax = sc->data[SC_CLIMAX].val1;
			skill_unitsetting(src,skillid,skilllv,x,y,climax);
		}
		break;
	case AG_ASTRAL_STRIKE:		/* アストラルストライク */
		{
			int ar = skill_get_area(AG_ASTRAL_STRIKE_ATK,skilllv);
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,AG_ASTRAL_STRIKE_ATK,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			skill_unitsetting(src,skillid,skilllv,x,y,0);
		}
		break;
	case NW_WILD_FIRE:		/* ワイルドファイア */
		{
			int ar = skill_get_area(skillid,skilllv);
			struct status_change *sc = status_get_sc(src);
			if(sd) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// 矢の消費
					break;
				if(sd->status.weapon == WT_GRENADE)
					ar += 1;
			}
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY,
				skill_castend_damage_id);
			if(sc && sc->data[SC_INTENSIVE_AIM_COUNT].timer != -1)
				status_change_end(src, SC_INTENSIVE_AIM_COUNT, -1);
		}
		break;
	case NW_HASTY_FIRE_IN_THE_HOLE:	/* ヘイスティファイアインザホール */
		{
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY,
				skill_castend_damage_id);
			skill_addtimerskill(src,tick+300,0,x,y,skillid,skilllv,BF_WEAPON,flag);
			skill_addtimerskill(src,tick+600,0,x,y,skillid,skilllv,BF_WEAPON,flag);
		}
		break;
	case NW_MISSION_BOMBARD:	/* ミッションボンバード */
		{
			int ar = skill_get_unit_range(skillid,skilllv);
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY,
				skill_castend_damage_id);
			skill_unitsetting(src,skillid,skilllv,x,y,0);
		}
		break;
	case SOA_TALISMAN_OF_BLACK_TORTOISE:	/* 玄武符 */
		{
			int ar = skill_get_area(skillid,skilllv);
			struct status_change *sc = status_get_sc(src);
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			if(sc && sc->data[SC_T_THIRD_GOD].timer != -1) {
				status_change_end(src, SC_T_THIRD_GOD, -1);
				status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case HN_METEOR_STORM_BUSTER:	/* メテオストームバスター */
		{
			int ar = skill_get_area(skillid,skilllv);
			int i, tmpx = 0, tmpy = 0, x1 = 0, y1 = 0;
			int loop = skilllv / 2 + 3;
			for(i=0; i < loop; i++) {
				tmpx = x + (atn_rand()%(ar*2+1) - ar);
				tmpy = y + (atn_rand()%(ar*2+1) - ar);
				if(i == 0 && map_getcell(src->m,tmpx,tmpy,CELL_CHKPASS)) {
					clif_skill_poseffect(src,skillid,skilllv,tmpx,tmpy,tick);
				} else if(i > 0) {
					skill_addtimerskill(src,tick+i*500,0,tmpx,tmpy,skillid,skilllv,(x1<<16)|y1,0);
				}
				x1 = tmpx;
				y1 = tmpy;
			}
			skill_addtimerskill(src,tick+i*500,0,tmpx,tmpy,skillid,skilllv,-1,0);
		}
		break;
	case HN_JACK_FROST_NOVA:	/* ジャックフロストノヴァ */
		{
			int ar = skill_get_area(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY,
				skill_castend_damage_id);
			skill_unitsetting(src,skillid,skilllv,x,y,0);
		}
		break;
	case SS_TOKEDASU:		/* 影溶き */
		{
			int ar = skill_get_area(skillid,skilllv);
			struct status_change *sc = status_get_sc(src);
			clif_skill_nodamage(src,src,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			if(!sc || sc->data[SC_ANKLE].timer == -1) {
				// バックステップ
				int dir = 0, head_dir = 0;
				int count = skill_get_blewcount(skillid,skilllv);
				struct block_list pos;
				memset(&pos,0,sizeof(pos));
				pos.m = src->m;
				pos.x = x;
				pos.y = y;

				if(sd) {
					dir = sd->dir;
					head_dir = sd->head_dir;
				}
				unit_stop_walking(src,1);
				skill_blown(&pos,src,count|SAB_NODAMAGE|SAB_NOPATHSTOP|SAB_NOTKNOCK);
				if(sd)
					pc_setdir(sd, dir, head_dir);
			}
			status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SS_KAGEGARI:			/* 影狩り */
		{
			int ar = skill_get_area(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY,
				skill_castend_damage_id);
		}
		break;
	case SS_FUUMAKOUCHIKU:		/* 風魔手裏剣 -構築- */
		{
			int ar = skill_get_area(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY,
				skill_castend_damage_id);
			map_foreachinarea(skill_fuumakouchiku,
				src->m,x-ar,y-ar,x+ar,y+ar,BL_SKILL,
				src,skilllv,tick);
		}
		break;
	case SS_KUNAIWAIKYOKU:		/* 苦無 -歪曲- */
		{
			int ar = skill_get_area(skillid,skilllv);
			int ar2 = skill_get_area(SS_SHINKIROU,1);
			if(sd) {
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// 矢の消費
					break;
			}
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY,
				skill_castend_damage_id);
			skill_unitsetting(src,skillid,skilllv,x,y,0);
			map_foreachinarea(skill_shinkirou,
				src->m,src->x-ar2,src->y-ar2,src->x+ar2,src->y+ar2,BL_SKILL,
				src,skillid,tick);
		}
		break;
	case SS_REIKETSUHOU:		/* 冷血砲 */
		{
			int ar = skill_get_area(skillid,skilllv);
			int ar2 = skill_get_area(SS_SHINKIROU,1);
			map_foreachinarea(skill_area_sub,
				src->m,x-ar,y-ar,x+ar,y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick,flag|BCT_ENEMY,
				skill_castend_damage_id);
			map_foreachinarea(skill_shinkirou,
				src->m,src->x-ar2,src->y-ar2,src->x+ar2,src->y+ar2,BL_SKILL,
				src,SS_ANTENPOU,tick);
		}
		break;
	}
	return 0;
}
