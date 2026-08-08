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
 * スキル使用（詠唱完了、ID指定支援系）
 *------------------------------------------
 */
int skill_castend_nodamage_id( struct block_list *src, struct block_list *bl,int skillid,int skilllv,unsigned int tick,int flag )
{
	struct map_session_data *sd  = NULL, *dstsd  = NULL;
	struct mob_data         *md  = NULL, *dstmd  = NULL;
	struct homun_data       *hd  = NULL;
	struct merc_data        *mcd = NULL;
	struct elem_data        *eld = NULL;
	struct status_change    *sc  = NULL;
	int is_enemy = 1;

	nullpo_retr(1, src);
	nullpo_retr(1, bl);

	if(bl->prev == NULL)
		return 1;
	if(unit_isdead(bl) && skillid != ALL_RESURRECTION && skillid != PR_REDEMPTIO && skillid != WM_DEADHILLHERE)
		return 1;
	if(status_get_class(bl) == MOBID_EMPERIUM)
		return 1;

	sd  = BL_DOWNCAST( BL_PC,   src );
	md  = BL_DOWNCAST( BL_MOB,  src );
	hd  = BL_DOWNCAST( BL_HOM,  src );
	mcd = BL_DOWNCAST( BL_MERC, src );
	eld = BL_DOWNCAST( BL_ELEM, src );

	dstsd  = BL_DOWNCAST( BL_PC,   bl );
	dstmd  = BL_DOWNCAST( BL_MOB,  bl );

	if(sd && unit_isdead(&sd->bl))
		return 1;
	if(!md && dstmd && dstmd->mode&MD_SKILLIMMUNITY)
		return 1;

	switch(skillid) {
		case KN_BRANDISHSPEAR:
		case ML_BRANDISH:
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
	case AL_HEAL:				/* ヒール */
	case AB_HIGHNESSHEAL:		/* ハイネスヒール */
		{
			int heal;
			int heal_get_jobexp;
			int lv;
			lv = (skillid == AB_HIGHNESSHEAL)? 10: skilllv;
			heal = skill_fix_heal(src, bl, skillid, skill_calc_heal(src, lv));
			sc = status_get_sc(bl);
			if(md && battle_config.monster_skill_over && skilllv >= battle_config.monster_skill_over)
				heal = 9999;	// 9999ヒール
			if(dstsd && dstsd->special_state.no_magic_damage)
				heal = 0;	// 黄金蟲カード（ヒール量０）
			if(sc && sc->data[SC_BERSERK].timer != -1)
				heal = 0; 	// バーサーク中はヒール０
			if(dstsd && pc_isgear(dstsd))
				heal = 0; 	// 魔道ギア搭乗中はヒール０
			if(sd && dstsd && sd->status.partner_id == dstsd->status.char_id && (sd->s_class.job == PC_CLASS_SNV || sd->s_class.job == PC_CLASS_ESNV) && sd->sex == SEX_FEMALE)
				heal *= 2;	// スパノビの嫁が旦那にヒールすると2倍になる
			if(skillid == AB_HIGHNESSHEAL)
				heal = heal * (170 + 30 * skilllv) / 100;
			if(sc && sc->data[SC_KAITE].timer != -1
#ifndef PRE_RENEWAL
				&& atn_rand()%100 < 50
#endif
			) {	// カイト
				clif_misceffect2(bl,438);
				if(--sc->data[SC_KAITE].val2 <= 0)
					status_change_end(bl, SC_KAITE, -1);
				if(src == bl) {		// 自分自身に対しては回復量0
					heal = 0;
				} else {		// ヒール反射
					bl = src;
					dstsd = sd;
				}
			}
			clif_skill_nodamage(src,bl,skillid,heal,1);
			heal_get_jobexp = battle_heal(NULL,bl,heal,0,0);

			// JOB経験値獲得
			if(sd && dstsd && heal > 0 && src != bl && battle_config.heal_exp > 0) {
				heal_get_jobexp = heal_get_jobexp * battle_config.heal_exp / 100;
				if(heal_get_jobexp <= 0)
					heal_get_jobexp = 1;
				pc_gainexp(sd,NULL,0,heal_get_jobexp,0);
			}
		}
		break;

	case HLIF_HEAL:		/* 治癒の手助け */
		{
			int heal = skill_fix_heal(src, bl, skillid, skill_calc_heal(src, skilllv));
			sc = status_get_sc(bl);
			if(hd) {
				int skill = homun_checkskill(hd,HLIF_BRAIN);
				if(skill > 0)
					heal += heal * skill / 50;
			}
			if(md && battle_config.monster_skill_over && skilllv >= battle_config.monster_skill_over)
				heal = 9999;	// 9999ヒール
			if(dstsd && dstsd->special_state.no_magic_damage)
				heal = 0;	// 黄金蟲カード（ヒール量０）
			if(sc && sc->data[SC_BERSERK].timer != -1)
				heal = 0;	// バーサーク中はヒール０
			if(dstsd && pc_isgear(dstsd))
				heal = 0; 	// 魔道ギア搭乗中はヒール０
			if(sc && sc->data[SC_KAITE].timer != -1
#ifndef PRE_RENEWAL
				&& atn_rand()%100 < 50
#endif
			) {	// カイト
				clif_misceffect2(bl,438);
				if(--sc->data[SC_KAITE].val2 <= 0)
					status_change_end(bl, SC_KAITE, -1);
				if(src == bl) {		// 自分自身に対しては回復量0
					heal = 0;
				} else {		// ヒール反射
					bl = src;
				}
			}
			clif_skill_nodamage(src,bl,skillid,heal,1);
			battle_heal(NULL,bl,heal,0,0);
		}
		break;

	case ALL_RESURRECTION:		/* リザレクション */
		if(!dstsd)
			break;
		if(map[bl->m].flag.pvp && dstsd->pvp_point < 0)	// PVPで復活不可能状態
			break;
		if(!unit_isdead(&dstsd->bl))			// 死亡判定
			break;
		if(dstsd->sc.data[SC_HELLPOWER].timer != -1)		// ヘルパワー状態は蘇生不可
			break;

		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		dstsd->status.hp = dstsd->status.max_hp * ((skilllv >= 4)? 80: skilllv*20-10)/100;
		if(dstsd->status.hp <= 0)
			dstsd->status.hp = 1;
		if(dstsd->special_state.restart_full_recover) {	// オシリスカード
			dstsd->status.hp = dstsd->status.max_hp;
			dstsd->status.sp = dstsd->status.max_sp;
			clif_updatestatus(dstsd,SP_SP);
		}
		clif_updatestatus(dstsd,SP_HP);
		pc_setstand(dstsd);
		if(battle_config.pc_invincible_time > 0)
			pc_setinvincibletimer(dstsd,battle_config.pc_invincible_time);
		clif_resurrection(&dstsd->bl,1);

		if(src != bl && sd && battle_config.resurrection_exp > 0)
		{
			atn_bignumber exp = 0, jexp = 0;
			int lv  = dstsd->status.base_level - sd->status.base_level;
			int jlv = dstsd->status.job_level  - sd->status.job_level;
			if(lv > 0) {
				exp = (atn_bignumber)dstsd->status.base_exp * lv * battle_config.resurrection_exp / 1000000;
				if(exp < 1)
					exp = 1;
			}
			if(jlv > 0) {
				jexp = (atn_bignumber)dstsd->status.job_exp * jlv * battle_config.resurrection_exp / 1000000;
				if(jexp < 1)
					jexp = 1;
			}
			if(exp > 0 || jexp > 0)
				pc_gainexp(sd,NULL,exp,jexp,0);
		}
		break;

	case AL_DECAGI:			/* 速度減少 */
	case MER_DECAGI:
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		if( atn_rand()%100 < (50+skilllv*3+(status_get_lv(src)+status_get_int(src)/5)-status_get_mdef(bl)) ) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(md && battle_config.monster_skill_over && skilllv >= battle_config.monster_skill_over)
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,1,0,0,skill_get_time(skillid,skilllv),0);
			else
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		status_change_release(bl,0x80); // 速度減少による状態異常解除
		break;

	case AL_CRUCIS:
		if(flag&1) {
			int race = status_get_race(bl);
			int ele = status_get_elem_type(bl);
			if(race == RCT_DEMON || battle_check_undead(race,ele)) {
				int rate = 23 + skilllv*4 + status_get_lv(src) - status_get_lv(bl);
				if(atn_rand()%100 < rate)
					status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,0,0);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;

	case PR_LEXDIVINA:		/* レックスディビーナ */
	case MER_LEXDIVINA:
		sc = status_get_sc(bl);
		if(sc) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if( dstsd && dstsd->special_state.no_magic_damage )
				break;
			if(sc->data[SC_SILENCE].timer != -1) {
				// 沈黙中なら敵味方問わず沈黙解除
				status_change_end(bl,SC_SILENCE,-1);
			} else if(battle_check_target(src,bl,BCT_ENEMY) > 0) {
				if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),10000,status_get_lv(src)))
					status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case SA_ABRACADABRA:
		if( sd && !map[src->m].flag.noabra ) {
			int abra_skillid = 0, maxlv;
			int abra_skilllv = pc_checkskill(sd,SA_ABRACADABRA);
			while(abra_skillid == 0) {
				abra_skillid=skill_abra_dataset(sd,skilllv);
			}
			maxlv = skill_get_max(abra_skillid);
			if(abra_skilllv > maxlv)
				abra_skilllv = maxlv;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			sd->skill_item.id      = abra_skillid;
			sd->skill_item.lv      = abra_skilllv;
			sd->skill_item.flag    = 1;		// 使用条件判定する
			clif_item_skill(sd, abra_skillid, abra_skilllv, msg_txt(179)); // アブラカダブラ
		}
		break;
	case SA_COMA:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd ) {
			if( dstsd->special_state.no_magic_damage )
				break;
			dstsd->status.hp = 1;
			dstsd->status.sp = 1;
			clif_updatestatus(dstsd,SP_HP);
			clif_updatestatus(dstsd,SP_SP);
		}
		else if(dstmd) {
			dstmd->hp = 1;
		}
		break;
	case SA_FULLRECOVERY:
	case NPC_ALLHEAL:		/* ライフストリーム */
		{
			int heal;
			if(skillid == NPC_ALLHEAL)
				heal = status_get_max_hp(bl) - status_get_hp(bl);
			else
				heal = status_get_max_hp(bl);
			clif_skill_nodamage(src,bl,AL_HEAL,heal,1);
			if( dstsd ) {
				if( dstsd->special_state.no_magic_damage )
					break;
				pc_heal(dstsd,heal,dstsd->status.max_sp,0,0);
			}
			else if(dstmd) {
				dstmd->hp = status_get_max_hp(bl);
			}
		}
		break;
	case SA_SUMMONMONSTER:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sd)
			mob_once_spawn(sd,sd->bl.m,sd->bl.x,sd->bl.y,"--ja--",-1,1,"");
		break;
	case SA_LEVELUP:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sd && pc_nextbaseexp(sd) > 0)
			pc_gainexp(sd,NULL,pc_nextbaseexp(sd)*10/100,0,0);
		break;

	case SA_INSTANTDEATH:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sd)
			pc_damage(NULL,sd,sd->status.max_hp);
		break;

	case SA_QUESTION:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		clif_emotion(bl,1);
		break;
	case SA_GRAVITY:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		break;
	case SA_CLASSCHANGE:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(dstmd) {
			// クラスチェンジ用ボスモンスターID
			static const int changeclass[] = {
				1038,1039,1046,1059,1086,1087,1112,1115,1147,1150,
				1157,1159,1190,1251,1252,1272,1312,1373,1389,1418,
				1492,1511
			};
			mob_class_change(dstmd,changeclass,sizeof(changeclass)/sizeof(changeclass[0]));
		}
		break;
	case SA_MONOCELL:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(dstmd) {
			// チェンジポリン用モンスターID
			static const int poringclass[] = { MOBID_PORING, MOBID_PORING };
			mob_class_change(dstmd,poringclass,sizeof(poringclass)/sizeof(poringclass[0]));
		}
		break;
	case SA_DEATH:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(dstsd)
			pc_damage(NULL,dstsd,dstsd->status.max_hp);
		else if(dstmd)
			mob_damage(NULL,dstmd,dstmd->hp,1);
		break;
	case SA_REVERSEORCISH:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(dstsd)
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SA_FORTUNE:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sd)
			pc_getzeny(sd,status_get_lv(bl)*100);
		break;
	case SA_TAMINGMONSTER:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sd && dstmd) {
			if(pet_search_data(dstmd->class_, PET_CLASS) != NULL)
				pet_catch_process1(sd,dstmd->class_);
		}
		break;
	case PF_SPIDERWEB:		/* スパイダーウェブ */
	case NPC_FLAMECROSS:		/* フレイムクロス */
	case NPC_VENOMFOG:		/* ベナムフォグ */
		skill_castend_pos2(src,bl->x,bl->y,skillid,skilllv,tick,0);
		break;

	case AL_INCAGI:			/* 速度増加 */
	case MER_INCAGI:
	case AL_BLESSING:		/* ブレッシング */
	case MER_BLESSING:
		sc = status_get_sc(bl);
		if(sc && sc->data[SC_HIGH].timer != -1)
			status_change_end(bl,SC_HIGH,-1);
		if(dstsd && dstsd->sc.data[SC_ELEMENTUNDEAD].timer != -1) {
			battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			break;
		}
	case PR_SLOWPOISON:
	case PR_IMPOSITIO:		/* イムポシティオマヌス */
	case PR_LEXAETERNA:		/* レックスエーテルナ */
	case PR_SUFFRAGIUM:		/* サフラギウム */
	case CR_PROVIDENCE:		/* プロヴィデンス */
	case SA_FLAMELAUNCHER:		/* フレイムランチャー */
	case SA_FROSTWEAPON:		/* フロストウェポン */
	case SA_LIGHTNINGLOADER:	/* ライトニングローダー */
	case SA_SEISMICWEAPON:		/* サイズミックウェポン */
		if( !(dstsd && dstsd->special_state.no_magic_damage) ) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		break;
	case PR_BENEDICTIO:		/* 聖体降福 */
		{
			int race = status_get_race(bl);
			if( battle_check_undead(race,status_get_elem_type(bl)) || race == RCT_DEMON )
				break;
			if( !(dstsd && dstsd->special_state.no_magic_damage) ) {
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case SA_ELEMENTWATER:	/* ウォーターエレメンタルチェンジ */
	case SA_ELEMENTGROUND:	/* アースエレメンタルチェンジ */
	case SA_ELEMENTFIRE:	/* ファイアーエレメンタルチェンジ */
	case SA_ELEMENTWIND:	/* ウィンドエレメンタルチェンジ */
		if(dstmd) {
			// ボス属性だった場合と暫定で40%の確率で使用失敗
			if((battle_config.boss_no_element_change && dstmd && dstmd->mode&MD_BOSS) || atn_rand() % 100 < 40) {
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				break;
			}
			// 敵は属性レベルを維持する
			switch(skillid) {
				case SA_ELEMENTWATER:	// 水
					dstmd->def_ele = (dstmd->def_ele/20)*20 + ELE_WATER;
					break;
				case SA_ELEMENTGROUND:	// 土
					dstmd->def_ele = (dstmd->def_ele/20)*20 + ELE_EARTH;
					break;
				case SA_ELEMENTFIRE:	// 火
					dstmd->def_ele = (dstmd->def_ele/20)*20 + ELE_FIRE;
					break;
				case SA_ELEMENTWIND:	// 風
					dstmd->def_ele = (dstmd->def_ele/20)*20 + ELE_WIND;
					break;
			}
			// ディスペル対策を一応やる？
			//status_change_start(bl,GetSkillStatusChangeTable(skillid),dstmd->def_ele/20,0,0,0,skill_get_time(skillid,skilllv),0 );
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		else if(!dstsd) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		break;
	case NPC_CHANGEUNDEAD:		/* 不死属性付与 */
		if( dstsd && dstsd->special_state.no_magic_damage ) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		} else {
			if(status_get_elem_type(bl) == ELE_DARK || status_get_race(bl) == RCT_DEMON)
				break;
			status_change_start(bl,GetSkillStatusChangeTable(skillid),1,0,0,0,skill_get_time(skillid,skilllv),0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;

	case BA_PANGVOICE:	/* パンボイス */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		sc = status_get_sc(bl);
		if(sc && sc->data[SC_CONFUSION].timer != -1)
			status_change_end(bl,SC_CONFUSION,-1);
		else if( !(status_get_mode(bl)&MD_BOSS) && atn_rand() % 10000 < status_change_rate(bl,SC_CONFUSION,7000,status_get_lv(src)) )
			status_change_pretimer(bl,SC_CONFUSION,7,0,0,0,30000,0,tick+status_get_amotion(src));
		else if(sd)
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		break;
	case DC_WINKCHARM:	/* 魅惑のウィンク */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(dstsd) {
			if(atn_rand() % 10000 < status_change_rate(&dstsd->bl,SC_CONFUSION,1000,status_get_lv(src))) {
				status_change_pretimer(&dstsd->bl,SC_CONFUSION,7,0,0,0,30000,0,tick+status_get_amotion(src));
				break;
			}
		} else if(dstmd) {
			int race = status_get_race(&dstmd->bl);
			if( !(dstmd->mode&MD_BOSS) && (race == RCT_DEMON || race == RCT_DEMIHUMAN || race == RCT_ANGEL) ) {
				if(atn_rand() % 100 < 40 + status_get_lv(src) - status_get_lv(bl)) {
					status_change_start(&dstmd->bl,GetSkillStatusChangeTable(skillid),skilllv,src->id,0,0,10000,0);
					break;
				}
			}
		}
		if(sd)
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		break;
	case TK_RUN:		/* タイリギ */
		if(sd) {
			if(sd->sc.data[SC_RUN].timer != -1) {
				// 5セル以内でLv7以上で素手ならスパート開始
				if(sd->sc.data[SC_RUN].val4 >= 2) {
					int lv = sd->sc.data[SC_RUN].val1;
			   		if(lv >= 7 && sd->sc.data[SC_RUN].val4 <= 6 && sd->weapontype1 == WT_FIST && sd->weapontype2 == WT_FIST)
						status_change_start(bl,SC_SPURT,lv,0,0,0,skill_get_time2(TK_RUN,lv),0);
					status_change_end(bl,SC_RUN,-1);
					clif_skill_nodamage(src,bl,skillid,skilllv,1);
				}
			} else {
				status_change_start(bl,SC_RUN,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case TK_HIGHJUMP:	/* ノピティギ */
		{
			int dir = status_get_dir(src);
			int x,y;
			if(dir & 1) {	// 斜め移動の場合
				x = src->x + dirx[dir] * (skilllv+skilllv/3);
				y = src->y + diry[dir] * (skilllv+skilllv/3);
			} else {
				x = src->x + dirx[dir] * skilllv*2;
				y = src->y + diry[dir] * skilllv*2;
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			// 着地地点とその一歩先が移動可能セルでPC,MOB,NPCいずれも居ないなら
			if( !map[src->m].flag.pvp && (!map[src->m].flag.noteleport || map[src->m].flag.gvg) && !map[src->m].flag.nojump &&
			    map_getcell(src->m,x,y,CELL_CHKPASS) && map_getcell(src->m,x+dirx[dir],y+diry[dir],CELL_CHKPASS) &&
			    !map_count_oncell(src->m,x,y,BL_PC|BL_MOB|BL_NPC)
			) {
				unit_movepos(src,x,y,0x11);
			}
		}
		break;
	case TK_MISSION:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sd && pc_checkskill(sd,TK_MISSION)>0)
		{
			if(sd->status.class_ == PC_CLASS_TK) {
				int count = ranking_get_point(sd,RK_TAEKWON)%100;
				if(sd->tk_mission_target == 0 || (count == 0 && atn_rand()%100 == 0))
				{
					int i = 0;
					while(i++ < 1000) {
						sd->tk_mission_target = mobdb_searchrandomid(1,sd->status.base_level);
						if(mobdb_search(sd->tk_mission_target)->max_hp <= 0)
							continue;
						if(mobdb_search(sd->tk_mission_target)->mode&MD_BOSS)	// ボス属性除外
							continue;
						break;
					}
					if(i >= 1000)
						sd->tk_mission_target = 0;
					pc_setglobalreg(sd,"PC_MISSION_TARGET",sd->tk_mission_target);
				}
				clif_mission_mob(sd,sd->tk_mission_target,count);
			} else {
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
			}
		}
		break;
	case SG_SUN_WARM:		/* 太陽の温もり */
	case SG_MOON_WARM:		/* 月の温もり */
	case SG_STAR_WARM:		/* 星の温もり */
		{
			struct skill_unit_group *sg;
			sc = status_get_sc(src);
			if(sc && sc->data[SC_WARM].timer != -1) {
				status_change_end(src,SC_WARM,-1);
			}
			sg = skill_unitsetting(src,skillid,skilllv,src->x,src->y,0);
			if(sg) {
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,bl->id,0,sg->bl.id,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case TK_SEVENWIND:		/* 暖かい風 */
		{
#ifdef PRE_RENEWAL
			int type = (skilllv < 7)? GetSkillStatusChangeTable(skillid): SC_ASPERSIO;
#else
			int type = GetSkillStatusChangeTable(skillid);
#endif
			status_change_start(bl,type,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case SL_SWOO:			/* エスウ */
		if(sd && !dstmd && !battle_config.allow_es_magic_all) {
			if(atn_rand() % 10000 < status_change_rate(&sd->bl,SC_STUN,10000,sd->status.base_level))
				status_change_pretimer(&sd->bl,SC_STUN,7,0,0,0,10000,0,tick+status_get_amotion(src));
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
			break;
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		sc = status_get_sc(bl);
		if(sc && sc->data[SC_SWOO].timer != -1) {
			status_change_end(bl,SC_SWOO,-1);
			status_change_pretimer(src,SC_STUN,7,0,0,0,10000,0,tick+status_get_amotion(src));
		} else {
			status_change_start(bl,SC_SWOO,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;

	case SL_SKA:			/* エスカ */
	case SL_SKE:			/* エスク */
		if( sd && !dstmd && !battle_config.allow_es_magic_all ) {
			if(atn_rand() % 10000 < status_change_rate(&sd->bl,SC_STUN,10000,sd->status.base_level))
				status_change_pretimer(&sd->bl,SC_STUN,7,0,0,0,1000,0,tick+status_get_amotion(src));
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
			break;
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		if(skillid == SL_SKE)
			status_change_start(src,SC_SMA,skilllv,0,0,0,3000,0);
		break;
	case SL_KAAHI:			/* カアヒ */
		sc = status_get_sc(src);
		if(sc && sc->data[SC_KAAHI].timer != -1) {
			status_change_end(src,SC_KAAHI,-1);
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case PR_ASPERSIO:		/* アスペルシオ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		if(dstmd)
			break;
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case PR_KYRIE:			/* キリエエレイソン */
	case MER_KYRIE:
		clif_skill_nodamage(bl,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		if(dstmd)
			break;
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SM_AUTOBERSERK:
	case KN_AUTOCOUNTER:		/* オートカウンター */
	case KN_TWOHANDQUICKEN:		/* ツーハンドクイッケン */
	case CR_SPEARQUICKEN:		/* スピアクイッケン */
	case CR_REFLECTSHIELD:
	case AS_ENCHANTPOISON:		/* エンチャントポイズン */
	case AS_POISONREACT:		/* ポイズンリアクト */
	case MC_LOUD:			/* ラウドボイス */
	case MG_ENERGYCOAT:		/* エナジーコート */
	case AL_RUWACH:			/* ルアフ */
	case MO_EXPLOSIONSPIRITS:	/* 爆裂波動 */
	case MO_STEELBODY:		/* 金剛 */
	case WE_BABY:
	case LK_AURABLADE:		/* オーラブレイド */
	case WS_CARTBOOST:		/* カートブースト */
	case SN_SIGHT:			/* トゥルーサイト */
	case WS_MELTDOWN:		/* メルトダウン */
	case ST_REJECTSWORD:		/* リジェクトソード */
	case HW_MAGICPOWER:		/* 魔法力増幅 */
	case PF_MEMORIZE:		/* メモライズ */
	case PF_DOUBLECASTING:		/* ダブルキャスティング */
	case PA_SACRIFICE:		/* サクリファイス */
	case ST_PRESERVE:		/* プリザーブ */
	case WS_OVERTHRUSTMAX:		/* オーバートラストマックス */
	case WZ_SIGHTBLASTER:		/* サイトブラスター */
	case KN_ONEHAND:		/* ワンハンドクイッケン */
	case TK_READYSTORM:
	case TK_READYDOWN:
	case TK_READYTURN:
	case TK_READYCOUNTER:
	case TK_DODGE:
	case SG_SUN_COMFORT:
	case SG_MOON_COMFORT:
	case SG_STAR_COMFORT:
	case SJ_LUNARSTANCE:	/* 月の構え */
	case SJ_STARSTANCE:		/* 星の構え */
	case SJ_UNIVERSESTANCE:	/* 宇宙の構え */
	case SJ_SUNSTANCE:		/* 太陽の構え */
	case SJ_LIGHTOFMOON:	/* 月の光 */
	case SJ_LIGHTOFSTAR:	/* 星の光 */
	case SJ_LIGHTOFSUN:		/* 太陽の光 */
	case SJ_FALLINGSTAR:	/* 流星落下 */
	case SJ_BOOKOFDIMENSION:	/* 次元の書 */
	case SL_KAIZEL:			/* カイゼル */
	case SL_KAITE:			/* カイト */
	case SL_KAUPE:			/* カウプ */
	case GS_INCREASING:		/* インクリージングアキュラシー */
	case GS_MAGICALBULLET:	/* マジカルバレット */
	case NJ_UTSUSEMI:		/* 空蝉の術 */
	case NJ_NEN:			/* 念 */
	case NPC_POWERUP:		/* ラッシュアタック */
	case NPC_AGIUP:			/* 速度強化 */
	case NPC_DEFENDER:
	case NPC_MAGICMIRROR:		/* マジックミラー */
	case NPC_HELLPOWER:			/* ヘルパワー */
	case NPC_MAXPAIN:			/* マックスペイン */
	case RK_DEATHBOUND:			/* デスバウンド */
	case RK_MILLENNIUMSHIELD:	/* ミレニアムシールド */
	case RK_GIANTGROWTH:		/* ジャイアントグロース */
	case RK_VITALITYACTIVATION:	/* バイタリティアクティベーション */
	case RK_ABUNDANCE:			/* アバンダンス */
	case GC_VENOMIMPRESS:		/* ベナムインプレス */
	case GC_WEAPONBLOCKING:		/* ウェポンブロッキング */
	case GC_HALLUCINATIONWALK:	/* ハルシネーションウォーク */
	case AB_DUPLELIGHT:			/* デュプレライト */
	case AB_OFFERTORIUM:		/* オフェルトリウム */
	case WL_MARSHOFABYSS:		/* マーシュオブアビス */
	case WL_RECOGNIZEDSPELL:	/* リゴグナイズドスペル */
	case WL_TELEKINESIS_INTENSE:	/* テレキネシスインテンス */
	case RA_FEARBREEZE:			/* フィアーブリーズ */
	case RA_UNLIMIT:			/* アンリミット */
	case NC_ACCELERATION:		/* アクセラレーション */
	case NC_HOVERING:			/* ホバーリング */
	case NC_SHAPESHIFT:			/* シェイプシフト */
	case SC_REPRODUCE:			/* リプロデュース */
	case SC_DEADLYINFECT:		/* デッドリーインフェクト */
	case LG_REFLECTDAMAGE:		/* リフレクトダメージ */
	case LG_FORCEOFVANGUARD:	/* フォースオブバンガード */
	case LG_EXEEDBREAK:			/* イクシードブレイク */
	case LG_PRESTIGE:			/* プレスティージ */
	case SR_CRESCENTELBOW:		/* 破碎柱 */
	case SR_LIGHTNINGWALK:		/* 閃電歩 */
	case SR_GENTLETOUCH_ENERGYGAIN:	/* 点穴 -球- */
	case WM_GLOOMYDAY:			/* メランコリー */
	case GN_CARTBOOST:			/* カートブースト */
	case ALL_ODINS_POWER:		/* オーディンの力 */
	case KO_MEIKYOUSISUI:		/* 明鏡止水 */
	case RL_E_CHAIN:			/* エターナルチェーン */
	case DK_SERVANTWEAPON:		/* サーヴァントウェポン */
	case DK_SERVANT_W_SIGN:		/* サーヴァントウェポン：サイン */
	case DK_CHARGINGPIERCE:		/* チャージングピアース */
	case DK_VIGOR:				/* ヴィゴール */
	case AG_CLIMAX:				/* クライマックス */
	case IQ_POWERFUL_FAITH:		/* 強靭な信念 */
	case IQ_FIRM_FAITH:			/* 堅固な信念 */
	case IQ_SINCERE_FAITH:		/* 忠実な信念 */
	case IQ_FIRST_FAITH_POWER:	/* 第一章：信念の力 */
	case IQ_JUDGE:				/* 第二章：審判者 */
	case IQ_THIRD_EXOR_FLAME:	/* 最終章：滅魔の炎 */
	case IG_GUARD_STANCE:		/* ガードスタンス */
	case IG_ATTACK_STANCE:		/* アタックスタンス */
	case IG_HOLY_SHIELD:		/* ホーリーシールド */
	case IG_REBOUND_SHIELD:		/* リバウンドシールド */
	case CD_ARGUTUS_VITA:		/* アルグトゥスヴィタ */
	case CD_ARGUTUS_TELUM:		/* アルグトゥステルム */
	case CD_PRESENS_ACIES:		/* プレセンスアキエース */
	case CD_RELIGIO:			/* レリギオ */
	case CD_BENEDICTUM:			/* ベネディクトゥム */
	case SHC_SHADOW_EXCEED:		/* シャドウエクシード */
	case SHC_DANCING_KNIFE:		/* ダンシングナイフ */
	case SHC_POTENT_VENOM:		/* ポテントベナム */
	case SHC_ENCHANTING_SHADOW:	/* エンチャンティングシャドウ */
	case MT_A_MACHINE:			/* 攻撃装置有効化 */
	case MT_D_MACHINE:			/* 防御装置有効化 */
	case ABC_FROM_THE_ABYSS:	/* フロムジアビス */
	case WH_WIND_SIGN:			/* ウィンドサイン */
	case BO_ADVANCE_PROTECTION:	/* フルシャドウチャージ */
	case BO_RESEARCHREPORT:		/* リサーチレポート */
	case TR_MYSTIC_SYMPHONY:	/* ミスティックシンフォニー */
	case TR_KVASIR_SONATA:		/* ソナタオブクヴァシル */
	case EM_SPELL_ENCHANTING:	/* スペルエンチャンティング */
	case NPC_BO_HELL_DUSTY:		/* ヘルダスティ */
	case NW_INTENSIVE_AIM:		/* インテンシブエイム */
	case NW_AUTO_FIRING_LAUNCHER:	/* オートファイアリングランチャー */
	case NW_HIDDEN_CARD:		/* ヒドゥンカード */
	case SOA_TALISMAN_OF_WARRIOR:	/* 武士符 */
	case SOA_TALISMAN_OF_MAGICIAN:	/* 法師符 */
	case SOA_TALISMAN_OF_FIVE_ELEMENTS:	/* 五行符 */
	case SH_TEMPORARY_COMMUNION:	/* 三霊一体 */
	case HN_BREAKINGLIMIT:		/* ブレイキングリミット */
	case HN_RULEBREAK:			/* ルールブレイク */
	case SKE_ENCHANTING_SKY:	/* 天気の身 */
	case MS_REFLECTSHIELD:
	case MER_QUICKEN:			/* ウェポンクイッケン */
	case MER_AUTOBERSERK:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case NPC_STONESKIN:		/* ストーンスキン */
	case NPC_ANTIMAGIC:		/* アンチマジック */
		//clif_skill_nodamage(src,bl,skillid,skilllv,1);
		clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case LK_PARRYING:		/* パリイング */
	case MG_SIGHT:			/* サイト */
	case MS_PARRYING:
	case MER_SIGHT:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,skillid,skill_get_time(skillid,skilllv),0);
		break;
	case HP_ASSUMPTIO:		/* アスムプティオ */
		if( !(dstsd && dstsd->special_state.no_magic_damage) ) {
			status_change_start(bl,SC_ASSUMPTIO,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);	// アイコンパケット送信後に送る
		break;
	case CASH_ASSUMPTIO:	/* パーティーアスムプティオ */
		if((flag&1) || sd == NULL || sd->status.party_id == 0) {
			/* 個別の処理 */
			if( dstsd && dstsd->special_state.no_magic_damage )
				break;
			status_change_start(bl,SC_ASSUMPTIO,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);	// アイコンパケット送信後に送る
		} else {
			/* パーティ全体への処理 */
			party_foreachsamemap(skill_area_sub,
				sd,skill_get_area(skillid,skilllv),
				src,skillid,skilllv,tick, flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case LK_CONCENTRATION:	/* コンセントレイション */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		if(sd)
			sd->skillstatictimer[SM_ENDURE] = tick;
		status_change_start(bl,SC_ENDURE,1,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case LK_BERSERK:		/* バーサーク */
	case MS_BERSERK:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		if(sd) {
			sd->status.hp = sd->status.max_hp;
			clif_updatestatus(sd,SP_HP);
		} else if(hd) {
			hd->status.hp = hd->max_hp;
			clif_send_homstatus(hd->msd,0);
		} else if(mcd) {
			mcd->status.hp = mcd->max_hp;
			clif_mercupdatestatus(mcd->msd,SP_HP);
		}
		break;
	case SM_ENDURE:			/* インデュア */
		if(sd)
			sd->skillstatictimer[SM_ENDURE] = tick + 10000;
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case LK_TENSIONRELAX:	/* テンションリラックス */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sd){
			pc_setsit(sd);
			clif_sitting(&sd->bl, 1);
		}
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case MC_CHANGECART:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		break;
	case AC_CONCENTRATION:	/* 集中力向上 */
		{
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			map_foreachinarea(status_change_timer_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_CHAR,
				src,GetSkillStatusChangeTable(skillid),skilllv,tick);
		}
		break;
	case SM_PROVOKE:		/* プロボック */
	case SM_SELFPROVOKE:	/* セルフプロボック */
	case MER_PROVOKE:
		// MVPmobと不死には効かない・成功判定
		if( status_get_mode(bl)&MD_BOSS || battle_check_undead(status_get_race(bl),status_get_elem_type(bl)) || atn_rand()%100 > 70 + skilllv * 3 + status_get_lv(src) - status_get_lv(bl) ) {
			if(skillid != SM_SELFPROVOKE) {
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				map_freeblock_unlock();
				return 1;
			}
		}
		clif_skill_nodamage(src,bl,(skillid == SM_SELFPROVOKE)? SM_PROVOKE : skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0 );

		// 凍結・石化・睡眠を解除
		status_change_attacked_end(bl);

		if(dstmd) {
			int range = skill_get_fixed_range(src,skillid,skilllv);
			mob_target(dstmd,src,range);
			battle_join_struggle(dstmd, src);
			if(dstmd->state.angry)
				dstmd->state.angry = 0;
		}
		if(sd)	// 使用者がプレイヤーのとき詠唱妨害
			unit_skillcastcancel(bl,2);
		break;

	case CG_MARIONETTE:		/* マリオネットコントロール */
		if(sd && dstsd)
		{
			status_change_start(src,SC_MARIONETTE,1,bl->id,0,0,60000,0);
			status_change_start(bl,SC_MARIONETTE2,1,src->id,0,0,60000,0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);	// アイコンパケット送信後に送る
		}
		break;
	case CR_DEVOTION:		/* ディボーション */
		if(sd && dstsd) {
			int i, n;
			int lv   = abs(sd->status.base_level - dstsd->status.base_level);
			int type = GetSkillStatusChangeTable(skillid);

			if( sd->bl.id == dstsd->bl.id ||			// 相手は自分はダメ
			    lv > battle_config.devotion_level_difference ||	// レベル差
			    sd->status.party_id <= 0 ||				// 自分がPT未所属だとダメ
			    dstsd->status.party_id <= 0 ||			// 相手がPT未所属だとダメ
			    sd->status.party_id != dstsd->status.party_id ||	// 同じパーティじゃないとダメ
			    dstsd->s_class.job == PC_JOB_CR ||		// 相手がクルセイダーだとダメ
			    dstsd->s_class.job == PC_JOB_LG ||		// 相手がロイヤルガードだとダメ
			    (type >= 0 && dstsd->sc.data[type].timer != -1 && dstsd->sc.data[type].val1 != sd->bl.id) )	// 違うクルセからディボーション済みならダメ
			{
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				map_freeblock_unlock();
				return 1;
			}

			for(i = 0, n = -1; i < skilllv && i < 5; i++) {
				if(sd->dev.val1[i] == dstsd->bl.id) {	// 既にディボーション済みの相手
					n = i;
					break;
				}
				if(!sd->dev.val1[i])	// 空きがあったら確保する
					n = i;
			}
			if(n < 0) {	// 何故か空きがなかった
				map_freeblock_unlock();
				return 1;
			}
			sd->dev.val1[n] = dstsd->bl.id;
			sd->dev.val2[n] = dstsd->bl.id;
			clif_skill_nodamage(&sd->bl,&dstsd->bl,skillid,skilllv,1);
			clif_devotion(sd);
			status_change_start(&dstsd->bl,type,sd->bl.id,1,0,0,skill_get_time(skillid,skilllv),0 );
		}
		else if(sd) {
			if(dstmd) {
				int range = skill_get_fixed_range(&sd->bl,skillid,skilllv);
				clif_skill_nodamage(&sd->bl,&dstmd->bl,skillid,skilllv,1);
				mob_target(dstmd, &sd->bl, range);
				battle_join_struggle(dstmd, &sd->bl);
			} else {
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
			}
		}
		break;
	case MO_CALLSPIRITS:	/* 気功 */
		if(sd) {
			pc_addspiritball(sd,skill_get_time(skillid,skilllv),1);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case CH_SOULCOLLECT:	/* 練気功 */
		if(sd) {
			pc_addspiritball(sd,skill_get_time(skillid,skilllv),MAX_SPIRITBALL);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case MO_BLADESTOP:	/* 白刃取り */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0 );
		break;
	case MO_ABSORBSPIRITS:	/* 気奪 */
		{
			int val = 0;
			if(dstsd && dstsd->spiritball.num > 0) {
				if( sd && sd != dstsd && !map[sd->bl.m].flag.pvp && !map[sd->bl.m].flag.gvg && !map[sd->bl.m].flag.pk )
					break;
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
				val = dstsd->spiritball.num * 7;
				pc_delspiritball(dstsd,dstsd->spiritball.num,0);
			} else if(dstmd && !(dstmd->mode&MD_BOSS)) { // 対象がモンスターでBOSS属性でない場合
				// 20%の確率で対象のLv*2のSPを回復する。成功したときはターゲッティングする。
				if(atn_rand()%100 < 20) {
					val = 2 * mobdb_search(dstmd->class_)->lv;
					mob_target(dstmd,src,0);
					battle_join_struggle(dstmd, src);
					unit_skillcastcancel(bl,2);	// 詠唱妨害

					// 凍結・石化・睡眠を解除
					status_change_attacked_end(bl);
				}
			}
			if(sd) {
				if(val > 0x7FFF)
					val = 0x7FFF;
				if(sd->status.sp + val > sd->status.max_sp)
					val = sd->status.max_sp - sd->status.sp;
				if(val > 0) {
					sd->status.sp += val;
					clif_heal(sd->fd,SP_SP,val);
					clif_skill_nodamage(src,bl,skillid,skilllv,1);
				} else {
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				}
			}
		}
		break;

	case AC_MAKINGARROW:		/* 矢作成 */
		if(sd) {
			clif_arrow_create_list(sd);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case AM_PHARMACY:			/* ポーション作成 */
		if(sd) {
			clif_skill_produce_mix_list(sd,PRD_PHARMACY,skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case AM_TWILIGHT1:
	case AM_TWILIGHT2:
	case AM_TWILIGHT3:
		if(sd) {
			skill_am_twilight(sd,skillid);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case AM_CALLHOMUN:	/* コールホムンクルス */
		if(sd && !sd->hd) {
			homun_callhom(sd);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case AM_REST:				/* 安息 */
		if(sd && homun_isalive(sd)) {
			homun_return_embryo(sd);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case AM_RESURRECTHOMUN:				/* リザレクションホムンクルス */
		if(sd && !sd->hd && sd->hom.hp <= 0) {
			homun_revive(sd,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case ASC_CDP:				/* デッドリーポイズン作成 */
		if(sd) {
			clif_skill_produce_mix_list(sd,PRD_CDP,skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case WS_CREATECOIN:			/* クリエイトコイン */
		if(sd) {
			clif_skill_produce_mix_list(sd,PRD_COIN,skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case WS_CREATENUGGET:			/* 塊製造 */
		if(sd) {
			clif_skill_produce_mix_list(sd,PRD_NUGGET,skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case SA_CREATECON:
		if(sd) {
			clif_skill_produce_mix_list(sd,PRD_CONVERTER,skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case BS_HAMMERFALL:		/* ハンマーフォール */
		if( dstsd && dstsd->special_state.no_weapon_damage )
			break;
		if( atn_rand() % 10000 < status_change_rate(bl,SC_STUN,(skilllv > 5)? 10000: 2000+skilllv*1000,status_get_lv(src)) )
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;
	case RG_RAID:			/* サプライズアタック */
		{
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(src,SC_RAID,0,10,0,0,skill_get_time(skillid,skilllv),0 );
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
			status_change_end(src, SC_HIDING, -1);	// ハイディング解除
		}
		break;
	case ASC_METEORASSAULT:	/* メテオアサルト */
		{
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case KN_BRANDISHSPEAR:	/* ブランディッシュスピア */
	case ML_BRANDISH:
		{
			int c, n = 4;
			int dir = path_calc_dir(src,bl->x,bl->y);
			struct square tc;

			skill_brandishspear_first(&tc,dir,bl->x,bl->y);
			skill_brandishspear_dir(&tc,dir,4);

			skill_area_temp[1] = 0;

			/* 範囲4 */
			if(skilllv > 9) {
				for(c=1; c<4; c++) {
					map_foreachinarea(skill_area_sub,
						bl->m,tc.val1[c],tc.val2[c],tc.val1[c],tc.val2[c],(BL_CHAR|BL_SKILL),
						src,skillid,skilllv,tick, flag|BCT_ENEMY|n,
						skill_castend_damage_id);
				}
			}
			/* 範囲3,2 */
			if(skilllv > 6) {
				skill_brandishspear_dir(&tc,dir,-1);
				n--;
			} else {
				skill_brandishspear_dir(&tc,dir,-2);
				n-=2;
			}
			if(skilllv > 3) {
				for(c=0; c<5; c++) {
					map_foreachinarea(skill_area_sub,
						bl->m,tc.val1[c],tc.val2[c],tc.val1[c],tc.val2[c],(BL_CHAR|BL_SKILL),
						src,skillid,skilllv,tick, flag|BCT_ENEMY|n,
						skill_castend_damage_id);
					if(skilllv > 6 && n == 3 && c == 4) {
						skill_brandishspear_dir(&tc,dir,-1);
						n--;
						c = -1;
					}
				}
			}
			/* 範囲1 */
			for(c=0; c<10; c++) {
				if(c == 0 || c == 5)
					skill_brandishspear_dir(&tc,dir,-1);
				map_foreachinarea(skill_area_sub,
					bl->m,tc.val1[c%5],tc.val2[c%5],tc.val1[c%5],tc.val2[c%5],(BL_CHAR|BL_SKILL),
					src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
					skill_castend_damage_id);
			}

			if(skill_area_temp[1] == 0) {
				skill_castend_damage_id(src,bl,skillid,skilllv,tick,flag|(is_enemy ? 0 : 0x01000000));
			}
		}
		break;
	case GS_GLITTERING:		/* フリップザコイン */
		if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(atn_rand()%100 < 20 + skilllv * 10) {
				pc_addcoin(sd,skill_get_time(skillid,skilllv),MAX_COIN);
			} else {
				if(pc_checkskill(sd,RL_RICHS_COIN) < 1)
					pc_delcoin(sd,1,0);
			}
		}
		break;

	/* パーティスキル */
	case AL_ANGELUS:		/* エンジェラス */
	case PR_MAGNIFICAT:		/* マグニフィカート */
	case PR_GLORIA:			/* グロリア */
	case SN_WINDWALK:		/* ウインドウォーク */
	case CASH_BLESSING:		/* パーティーブレッシング */
	case CASH_INCAGI:		/* パーティー速度増加 */
		if((flag&1) || sd == NULL || sd->status.party_id == 0) {
			/* 個別の処理 */
			if( dstsd && dstsd->special_state.no_magic_damage )
				break;
			clif_skill_nodamage(bl,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			/* パーティ全体への処理 */
			party_foreachsamemap(skill_area_sub,
				sd,skill_get_area(skillid,skilllv),
				src,skillid,skilllv,tick, flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case BS_ADRENALINE:		/* アドレナリンラッシュ */
	case BS_ADRENALINE2:		/* フルアドレナリンラッシュ */
	case BS_WEAPONPERFECT:		/* ウェポンパーフェクション */
	case BS_OVERTHRUST:		/* オーバートラスト */
		if((flag&1) || sd == NULL || sd->status.party_id == 0) {
			/* 個別の処理 */
			clif_skill_nodamage(bl,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,((src == bl)? 1: 0),0,0,skill_get_time(skillid,skilllv),0);
		} else {
			/* パーティ全体への処理 */
			party_foreachsamemap(skill_area_sub,
				sd,skill_get_area(skillid,skilllv),
				src,skillid,skilllv,tick, flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case MER_MAGNIFICAT:
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		clif_skill_nodamage(bl,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);

		if(mcd && mcd->msd) {
			// 傭兵なら雇い主にも
			if( mcd->msd->special_state.no_magic_damage )
				break;
			clif_skill_nodamage(&mcd->msd->bl,&mcd->msd->bl,skillid,skilllv,1);
			status_change_start(&mcd->msd->bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;

	/*（付加と解除が必要） */
	case BS_MAXIMIZE:		/* マキシマイズパワー */
	case NV_TRICKDEAD:		/* 死んだふり */
	case CR_DEFENDER:		/* ディフェンダー */
	case CR_AUTOGUARD:		/* オートガード */
	case CR_SHRINK:			/* シュリンク */
	case GS_GATLINGFEVER:			/* ガトリングフィーバー */
	case ML_DEFENDER:
	case ML_AUTOGUARD:
		{
			int type = GetSkillStatusChangeTable(skillid);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			sc = status_get_sc(bl);
			if(type >= 0 && sc && sc->data[type].timer != -1) {
				/* 解除する */
				status_change_end(bl, type, -1);
			} else {
				/* 付加する */
				if(skillid == BS_MAXIMIZE)
					status_change_start(bl,type,skilllv,skill_get_time(skillid,skilllv),0,0,0,0);
				else
					status_change_start(bl,type,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		}
		break;

	case TF_HIDING:			/* ハイディング */
	case KO_YAMIKUMO:		/* 闇雲 */
		{
			int type = GetSkillStatusChangeTable(skillid);
			clif_skill_nodamage(src,bl,skillid,-1,1);
			sc = status_get_sc(bl);
			if(type >= 0 && sc && sc->data[type].timer != -1) {
				/* 解除する */
				status_change_end(bl, type, -1);
			} else {
				/* 付加する */
				status_change_start(bl,type,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
			if(sc && sc->data[SC_CLOSECONFINE].timer != -1)
				status_change_end(bl,SC_CLOSECONFINE,-1);
		}
		break;

	case ST_CHASEWALK:		/* チェイスウォーク */
	case AS_CLOAKING:		/* クローキング */
	case GC_CLOAKINGEXCEED:	/* クローキングエクシード */
	case SC_INVISIBILITY:	/* インビジビリティ */
	case RA_CAMOUFLAGE:		/* カモフラージュ */
		{
			int type = GetSkillStatusChangeTable(skillid);
			clif_skill_nodamage(src,bl,skillid,-1,1);
			sc = status_get_sc(bl);
			if(type >= 0 && sc && sc->data[type].timer != -1) {
				/* 解除する */
				status_change_end(bl, type, -1);
			} else {
				/* 付加する */
				status_change_start(bl,type,skilllv,skill_get_time(skillid,skilllv),0,0,0,0);
			}
			if(skillid == AS_CLOAKING && skilllv < 3)
				skill_check_cloaking(bl);
		}
		break;
	case NPC_INVISIBLE:		/* インビジブル */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;

	/* 対地スキル */
	case HP_BASILICA:			/* バジリカ */
		sc = status_get_sc(src);
		if(sc && sc->data[SC_BASILICA].timer != -1) {
			skill_basilica_cancel(src);
			status_change_end(bl,SC_BASILICA,-1);
			break;
		}
		status_change_start(bl,SC_BASILICA,skilllv,bl->id,0,0,skill_get_time(skillid,skilllv),0);
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_unitsetting(src,skillid,skilllv,src->x,src->y,0);
		break;
	case BD_LULLABY:			/* 子守唄 */
	case BD_RICHMANKIM:			/* ニヨルドの宴 */
	case BD_ETERNALCHAOS:		/* 永遠の混沌 */
	case BD_DRUMBATTLEFIELD:	/* 戦太鼓の響き */
	case BD_RINGNIBELUNGEN:		/* ニーベルングの指輪 */
	case BD_ROKISWEIL:			/* ロキの叫び */
	case BD_INTOABYSS:			/* 深淵の中に */
	case BD_SIEGFRIED:			/* 不死身のジークフリード */
	case BA_DISSONANCE:			/* 不協和音 */
	case BA_POEMBRAGI:			/* ブラギの詩 */
	case BA_WHISTLE:			/* 口笛 */
	case BA_ASSASSINCROSS:		/* 夕陽のアサシンクロス */
	case BA_APPLEIDUN:			/* イドゥンの林檎 */
	case DC_UGLYDANCE:			/* 自分勝手なダンス */
	case DC_HUMMING:			/* ハミング */
	case DC_DONTFORGETME:		/* 私を忘れないで… */
	case DC_FORTUNEKISS:		/* 幸運のキス */
	case DC_SERVICEFORYOU:		/* サービスフォーユー */
	case CG_MOONLIT:			/* 月明りの下で */
	case CG_HERMODE:			/* ヘルモードの杖 */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_unitsetting(src,skillid,skilllv,src->x,src->y,0);
		break;
	case CG_LONGINGFREEDOM:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,SC_LONGINGFREEDOM,skilllv,0,0,0,1000,0);
		break;

	case PA_GOSPEL:				/* ゴスペル */
		sc = status_get_sc(src);
		if(sc && sc->data[SC_GOSPEL].timer != -1) {
			status_change_end(bl,SC_GOSPEL,-1);
		} else {
			struct skill_unit_group *sg = skill_unitsetting(src,skillid,skilllv,src->x,src->y,0);
			status_change_release(src,0x04);	// ゴスペル術者のステータス異常解除
			if(sg) {
				clif_skill_poseffect(src,skillid,skilllv,src->x,src->y,tick);
				status_change_start(bl,SC_GOSPEL,skilllv,bl->id,0,sg->bl.id,skill_get_time(skillid,skilllv),0);
			}
		}
		break;

	case BD_ADAPTATION:			/* アドリブ */
		sc = status_get_sc(src);
		if(sc && sc->data[SC_DANCING].timer != -1) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_stop_dancing(src,0);
		}
		break;

	case BA_FROSTJOKE:			/* 寒いジョーク */
	case DC_SCREAM:				/* スクリーム */
		if( sd || (md && mob_is_pcview(md->class_)) ) {
			// 見た目がPCでない場合は何故か姿が消えてしまうので除外する
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		skill_addtimerskill(src,tick+3000,bl->id,0,0,skillid,skilllv,0,flag);
		if(md) {		// Mobは喋れないから、スキル名を叫ばせてみる
			char output[100];
			if(skillid == BA_FROSTJOKE)
				snprintf(output, sizeof(output), msg_txt(181), md->name); // %s : 寒いジョーク !!
			else
				snprintf(output, sizeof(output), msg_txt(182), md->name); // %s : スクリーム !!
			clif_GlobalMessage(&md->bl, output, AREA_CHAT_WOC);
		}
		break;

	case TF_STEAL:			/* スティール */
		if(sd) {
			if(dstmd && pc_steal_item(sd,dstmd))
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
			else
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		}
		break;

	case RG_STEALCOIN:		/* スティールコイン */
		if(sd) {
			if(dstmd && pc_steal_coin(sd,dstmd)) {
				int range = skill_get_fixed_range(src,skillid,skilllv);
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
				mob_target(dstmd,src,range);
				battle_join_struggle(dstmd, src);
			} else {
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
			}
		}
		break;

	case MG_STONECURSE:			/* ストーンカース */
		if(status_get_mode(bl)&MD_BOSS) {
			if(sd)
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
			break;
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(dstsd && dstsd->special_state.no_magic_damage)
			break;
		if(dstmd)
			mob_target(dstmd,src,skill_get_fixed_range(src,skillid,skilllv));

		sc = status_get_sc(bl);
		if(sc && sc->data[SC_STONE].timer != -1) {
			status_change_end(bl,SC_STONE,-1);
		} else if(!battle_check_undead(status_get_race(bl),status_get_elem_type(bl)) && atn_rand() % 10000 < status_change_rate(bl,SC_STONE,skilllv*400+2000,status_get_lv(src))) {
			status_change_start(bl,SC_STONE,skilllv,0,0,5000,skill_get_time2(skillid,skilllv),0);

			// 成功なのでLv6以上はジェム消費処理
			if(skilllv >= 6) {
				int i, val;
				struct map_session_data *msd = map_bl2msd(src);

				if(msd == NULL)
					break;

				for(i=0; i<MAX_SKILL_DB_ITEM; i++) {
					if(skill_db[skillid].itemid[i] < 715 || skill_db[skillid].itemid[i] > 717)
						continue;

					val = skill_db[skillid].amount[i];
					if(msd->special_state.no_gemstone || msd->sc.data[SC_WIZARD].timer != -1 || msd->sc.data[SC_INTOABYSS].timer != -1)
						val--;

					if(val > 0) {
						int idx = pc_search_inventory(msd,skill_db[skillid].itemid[i]);
						if(idx < 0)
							continue;
						pc_delitem(msd,idx,val,0,1);
					}
				}
			}
		} else {
			if(sd)
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		}
		break;

	case NV_FIRSTAID:			/* 応急手当 */
		{
			int heal = skill_fix_heal(src, bl, skillid, 5);
			clif_skill_nodamage(src,bl,skillid,heal,1);
			battle_heal(NULL,bl,heal,0,0);
		}
		break;

	case AL_CURE:				/* キュアー */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		status_change_end(bl, SC_SILENCE, -1);
		status_change_end(bl, SC_BLIND, -1);
		status_change_end(bl, SC_CONFUSION, -1);
		break;

	case TF_DETOXIFY:			/* 解毒 */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_end(bl, SC_POISON, -1);
		status_change_end(bl, SC_DPOISON, -1);
		break;

	case PR_STRECOVERY:			/* リカバリー */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		status_change_end(bl, SC_FREEZE, -1);
		status_change_end(bl, SC_STONE, -1);
		status_change_end(bl, SC_SLEEP, -1);
		status_change_end(bl, SC_STUN, -1);
		if( battle_check_undead(status_get_race(bl),status_get_elem_type(bl)) ) {	// アンデッドなら暗闇効果
			if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,10000,status_get_lv(src)))
				status_change_pretimer(bl, SC_BLIND,1,0,0,0,30000,0,tick+status_get_amotion(src));
		}
		if(dstmd) {
			mob_unlocktarget(dstmd,tick);
			dstmd->attacked_id = 0;
			dstmd->attacked_players = 0;
		}
		break;

	case WZ_ESTIMATION:			/* モンスター情報 */
		if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_skill_estimation(sd,bl);
		}
		break;
	case MER_ESTIMATION:
		if(mcd && mcd->msd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_skill_estimation(mcd->msd,bl);
		}
		break;

	case MC_IDENTIFY:			/* アイテム鑑定 */
		if(sd)
			clif_item_identify_list(sd);
		break;

	case WS_WEAPONREFINE:		/* 武器精錬 */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sd)
			clif_weapon_refine_list(sd);
		break;

	case BS_REPAIRWEAPON:			/* 武器修理 */
		if(sd && dstsd)
			clif_item_repair_list(sd,dstsd);
		break;

	case MC_VENDING:			/* 露店開設 */
		if(sd && pc_iscarton(sd)) {
			if(npc_isnear(&sd->bl)) {
				clif_skill_fail(sd,skillid,SKILLFAIL_NEARNPC,0,0);
				return 1;
			}
			clif_openvendingreq(sd,2+sd->ud.skilllv);
		}
		break;

	case AL_TELEPORT:			/* テレポート */
		{
			int alive = 1;
			if(!md || !(md->mode&MD_BOSS) || !battle_config.boss_teleport_on_landprotector) {
				// PCおよび一般MOBはランドプロテクター上ではテレポート不可
				map_foreachinarea(skill_landprotector,src->m,src->x,src->y,src->x,src->y,BL_SKILL,skillid,&alive);
			}
			if(alive) {
				if(sd) {
					clif_skill_nodamage(src,bl,skillid,skilllv,1);
					if(sd->ud.skilllv == 1) {
						clif_skill_warppoint(sd,sd->ud.skillid,"Random","","","");
					} else {
						clif_skill_warppoint(sd,sd->ud.skillid,"Random",sd->status.save_point.map,"","");
					}
				} else if(md && md->sc.data[SC_ANKLE].timer == -1) {
					mob_warp(md,-1,-1,-1,3);
				}
			}
		}
		break;

	case AL_HOLYWATER:			/* アクアベネディクタ */
		if(sd) {
			int eflag;
			struct item item_tmp;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			memset(&item_tmp,0,sizeof(item_tmp));
			item_tmp.nameid   = 523;
			item_tmp.identify = 1;
			if(battle_config.holywater_name_input) {
				item_tmp.card[0] = 0xfe;
				item_tmp.card[1] = 0;
				*((int *)(&item_tmp.card[2]))=sd->status.char_id;	// キャラID
			}
			eflag = pc_additem(sd,&item_tmp,1,false);
			if(eflag) {
				clif_additem(sd,0,0,eflag);
				map_addflooritem(&item_tmp,1,sd->bl.m,sd->bl.x,sd->bl.y,0,0,0,0);
			}
		}
		break;
	case TF_PICKSTONE:
		if(sd) {
			int eflag;
			struct item item_tmp;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			memset(&item_tmp,0,sizeof(item_tmp));
			item_tmp.nameid   = 7049;
			item_tmp.identify = 1;
			clif_takeitem(&sd->bl,0);
			eflag = pc_additem(sd,&item_tmp,1,false);
			if(eflag) {
				clif_additem(sd,0,0,eflag);
				map_addflooritem(&item_tmp,1,sd->bl.m,sd->bl.x,sd->bl.y,0,0,0,0);
			}
		}
		break;

	case RG_STRIPWEAPON:		/* ストリップウェポン */
	case RG_STRIPSHIELD:		/* ストリップシールド */
	case RG_STRIPARMOR:			/* ストリップアーマー */
	case RG_STRIPHELM:			/* ストリップヘルム */
		{
			int cp_scid, scid, equip;
			int strip_fix, strip_time;

			scid = GetSkillStatusChangeTable(skillid);
			if(scid < 0)
				break;
			switch (skillid) {
				case RG_STRIPWEAPON:
					equip   = LOC_RARM;
					cp_scid = SC_CP_WEAPON;
					break;
				case RG_STRIPSHIELD:
					equip   = LOC_LARM;
					cp_scid = SC_CP_SHIELD;
					break;
				case RG_STRIPARMOR:
					equip   = LOC_BODY;
					cp_scid = SC_CP_ARMOR;
					break;
				case RG_STRIPHELM:
					equip   = LOC_HEAD2;
					cp_scid = SC_CP_HELM;
					break;
				default:
					map_freeblock_unlock();
					return 1;
			}
			sc = status_get_sc(bl);
			if(sc && (sc->data[scid].timer != -1 || sc->data[cp_scid].timer != -1)) {
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				break;
			}

			strip_fix = 2 * (status_get_dex(src) - status_get_dex(bl));

			if(atn_rand()%1000 > 50 + skilllv*50 + strip_fix)
				break;

			if(dstsd) {
				int i;
				if(equip == LOC_LARM) {
					// ストリップシールドは弓以外の両手武器には失敗
					if( dstsd->equip_index[EQUIP_INDEX_LARM] >= 0 &&
					    itemdb_isweapon(dstsd->inventory_data[dstsd->equip_index[EQUIP_INDEX_LARM]]->nameid) &&
					    dstsd->status.weapon != WT_BOW )
						break;
				}
				for(i=0; i<MAX_INVENTORY; i++) {
					if(dstsd->status.inventory[i].equip && (dstsd->status.inventory[i].equip & equip)) {
						pc_unequipitem(dstsd,i,0);
						break;
					}
				}
				if(i >= MAX_INVENTORY && !md) {	// MOB -> PC は装備をしていなくても発動
					if(sd)
						clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
					break;
				}
			}
			if(bl->type == BL_PC)	// PCの場合のみ計算式が違う
				strip_time = 1000 * (30 * (skilllv+2) - status_get_dex(src) + status_get_dex(bl));
			else
				strip_time = 500 * (30 * (skilllv+4) - status_get_dex(src) + status_get_dex(bl));
			status_change_start(bl,scid,skilllv,0,0,0,strip_time,0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case ST_FULLSTRIP:		/* フルストリップ */
		{
			int strip_fix, rate, strip_time;
			int fail = 1;
			int skill_fix = 50 + 20 * skilllv;

			strip_fix = status_get_dex(src) - status_get_dex(bl);
			rate = skill_fix + 2 * strip_fix;

			if(rate < skill_fix)
				rate = skill_fix;
			if(atn_rand()%1000 >= rate)
				break;
			if(bl->type == BL_PC)	// PCの場合のみ計算式が違う
				strip_time = 1000 * (30 * (skilllv+2) - status_get_dex(src) + status_get_dex(bl));
			else
				strip_time = 500 * (30 * (skilllv+4) - status_get_dex(src) + status_get_dex(bl));

			sc = status_get_sc(bl);
			if(dstsd) {
				int i;

				status_calc_pc_stop_begin(&dstsd->bl);
				for(i=0; i<MAX_INVENTORY; i++) {
					if( dstsd->status.inventory[i].equip & LOC_RARM &&
					    (!sc || (sc->data[SC_CP_WEAPON].timer == -1 && sc->data[SC_STRIPWEAPON].timer == -1)) ) {
						pc_unequipitem(dstsd,i,0);
						status_change_start(bl,SC_STRIPWEAPON,skilllv,0,0,0,strip_time,0);
						fail = 0;
					}
					if( dstsd->status.inventory[i].equip & LOC_LARM ) {
						// ストリップシールドは弓以外の両手武器には失敗
						if( dstsd->equip_index[EQUIP_INDEX_LARM] >= 0 &&
						    itemdb_isweapon(dstsd->inventory_data[dstsd->equip_index[EQUIP_INDEX_LARM]]->nameid) &&
						    dstsd->status.weapon != WT_BOW ) {
							;
						}
						else if( !sc || (sc->data[SC_CP_SHIELD].timer == -1 && sc->data[SC_STRIPSHIELD].timer == -1) ) {
							pc_unequipitem(dstsd,i,0);
							status_change_start(bl,SC_STRIPSHIELD,skilllv,0,0,0,strip_time,0);
							fail = 0;
						}
					}
					if( dstsd->status.inventory[i].equip & LOC_BODY &&
					    (!sc || (sc->data[SC_CP_ARMOR].timer == -1 && sc->data[SC_STRIPARMOR].timer == -1)) ) {
						pc_unequipitem(dstsd,i,0);
						status_change_start(bl,SC_STRIPARMOR,skilllv,0,0,0,strip_time,0);
						fail = 0;
					}
					if( dstsd->status.inventory[i].equip & LOC_HEAD2 &&
					    (!sc || (sc->data[SC_CP_HELM].timer == -1 && sc->data[SC_STRIPHELM].timer == -1)) ) {
						pc_unequipitem(dstsd,i,0);
						status_change_start(bl,SC_STRIPHELM,skilllv,0,0,0,strip_time,0);
						fail = 0;
					}
				}
				status_calc_pc_stop_end(&dstsd->bl);
			} else {
				if(!sc || (sc->data[SC_CP_WEAPON].timer == -1 && sc->data[SC_STRIPWEAPON].timer == -1)) {
					status_change_start(bl,SC_STRIPWEAPON,skilllv,0,0,0,strip_time,0);
					fail = 0;
				}
				if(!sc || (sc->data[SC_CP_SHIELD].timer == -1 && sc->data[SC_STRIPSHIELD].timer == -1)) {
					status_change_start(bl,SC_STRIPSHIELD,skilllv,0,0,0,strip_time,0);
					fail = 0;
				}
				if(!sc || (sc->data[SC_CP_ARMOR].timer == -1 && sc->data[SC_STRIPARMOR].timer == -1)) {
					status_change_start(bl,SC_STRIPARMOR,skilllv,0,0,0,strip_time,0);
					fail = 0;
				}
				if(!sc || (sc->data[SC_CP_HELM].timer == -1 && sc->data[SC_STRIPHELM].timer == -1)) {
					status_change_start(bl,SC_STRIPHELM,skilllv,0,0,0,strip_time,0);
					fail = 0;
				}
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(fail && sd)
				clif_fullstrip_fail(sd);
		}
		break;
	case AM_POTIONPITCHER:		/* ポーションピッチャー */
		{
			struct block_list tbl;
			int hp = 0, sp = 0;
			if(sd) {
				int i = pc_search_inventory(sd,skill_db[skillid].lv_itemid[skilllv-1]);

				if(i < 0 || skill_db[skillid].lv_itemid[skilllv-1] <= 0) {
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
					map_freeblock_unlock();
					return 1;
				}
				if(sd->inventory_data[i] == NULL || sd->status.inventory[i].amount < skill_db[skillid].lv_amount[skilllv-1]) {
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
					map_freeblock_unlock();
					return 1;
				}
				sd->state.potionpitcher_flag = 1;
				memset(&sd->potion,0,sizeof(sd->potion));
				sd->ud.skilltarget = bl->id;
				if(sd->inventory_data[i]->use_script) {
					run_script(sd->inventory_data[i]->use_script,0,sd->bl.id,0);
				}
				pc_delitem(sd,i,skill_db[skillid].lv_amount[skilllv-1],0,1);
				sd->state.potionpitcher_flag = 0;
				if(sd->potion.hp_per > 0 || sd->potion.sp_per > 0) {
					hp = (int)((atn_bignumber)status_get_max_hp(bl) * sd->potion.hp_per / 100);
					hp = hp * (100 + pc_checkskill(sd,AM_POTIONPITCHER)*10 + pc_checkskill(sd,AM_LEARNINGPOTION)*5)/100;
					if(dstsd) {
						sp = dstsd->status.max_sp * sd->potion.sp_per / 100;
						sp = sp * (100 + pc_checkskill(sd,AM_POTIONPITCHER) + pc_checkskill(sd,AM_LEARNINGPOTION)*5)/100;
					}
				} else {
					if(sd->potion.hp > 0) {
						hp = sd->potion.hp * (100 + pc_checkskill(sd,AM_POTIONPITCHER)*10 + pc_checkskill(sd,AM_LEARNINGPOTION)*5)/100;
						hp = hp * (100 + (status_get_vit(bl)<<1)) / 100;
						if(dstsd)
							hp = hp * (100 + pc_checkskill(dstsd,SM_RECOVERY)*10) / 100;
					}
					if(sd->potion.sp > 0) {
						sp = sd->potion.sp * (100 + pc_checkskill(sd,AM_POTIONPITCHER)*10 + pc_checkskill(sd,AM_LEARNINGPOTION)*5)/100;
						sp = sp * (100 + (status_get_int(bl)<<1)) / 100;
						if(dstsd)
							sp = sp * (100 + pc_checkskill(dstsd,MG_SRECOVERY)*10) / 100;
					}
				}
				if(sd->sc.data[SC_ALCHEMIST].timer != -1) {
					hp = hp * (100 + sd->status.base_level) / 100;
					sp = sp * (100 + sd->status.base_level) / 100;
				}
			} else {
				hp = (1 + atn_rand()%400) * (100 + skilllv*10) / 100;
				hp = hp * (100 + (status_get_vit(bl)<<1)) / 100;
				if(dstsd)
					hp = hp * (100 + pc_checkskill(dstsd,SM_RECOVERY)*10) / 100;
			}
			hp = skill_fix_heal(src, bl, skillid, hp);

			memset(&tbl, 0, sizeof(tbl));
			tbl.m = src->m;
			tbl.x = src->x;
			tbl.y = src->y;
			sc = status_get_sc(bl);
			if(sc && sc->data[SC_BERSERK].timer != -1)
				hp = sp = 0;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(hp > 0 || (hp <= 0 && sp <= 0))
				clif_skill_nodamage(&tbl,bl,AL_HEAL,hp,1);
			if(sp > 0)
				clif_skill_nodamage(&tbl,bl,MG_SRECOVERY,sp,1);
			battle_heal(src,bl,hp,sp,0);
		}
		break;

	case CR_SLIMPITCHER:	/* スリムポーションピッチャー */
		if(sd && flag&1) {
			struct block_list tbl;
			int hp = sd->potion.hp * (100 + pc_checkskill(sd,CR_SLIMPITCHER)*10 + pc_checkskill(sd,AM_POTIONPITCHER)*10 + pc_checkskill(sd,AM_LEARNINGPOTION)*5)/100;
			hp = hp * (100 + (status_get_vit(bl)<<1))/100;
			if(dstsd) {
				hp = hp * (100 + pc_checkskill(dstsd,SM_RECOVERY)*10)/100;
			}
			hp = skill_fix_heal(&sd->bl, bl, skillid, hp);
			memset(&tbl, 0, sizeof(tbl));
			tbl.m = src->m;
			tbl.x = src->x;
			tbl.y = src->y;
			clif_skill_nodamage(&tbl,bl,AL_HEAL,hp,1);
			battle_heal(NULL,bl,hp,0,0);
		}
		break;

	case AM_BERSERKPITCHER:		/* バーサークピッチャー */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,SC_SPEEDPOTION2,1,0,0,0,900000,0);
		break;
	case AM_CP_WEAPON:
	case AM_CP_SHIELD:
	case AM_CP_ARMOR:
	case AM_CP_HELM:
		{
			int type = GetSkillStatusChangeTable(skillid);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			sc = status_get_sc(bl);
			if(type >= 0 && sc && sc->data[type].timer != -1)
				status_change_end(bl, type, -1);
			status_change_start(bl,type,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case CR_FULLPROTECTION:			/* フルケミカルチャージ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		sc = status_get_sc(bl);
		if(sc) {
			if(sc->data[SC_STRIPWEAPON].timer != -1)
				status_change_end(bl, SC_STRIPWEAPON, -1);
			if(sc->data[SC_STRIPSHIELD].timer != -1)
				status_change_end(bl, SC_STRIPSHIELD, -1);
			if(sc->data[SC_STRIPARMOR].timer != -1)
				status_change_end(bl, SC_STRIPARMOR, -1);
			if(sc->data[SC_STRIPHELM].timer != -1)
				status_change_end(bl, SC_STRIPHELM, -1);
		}
		status_change_start(bl,SC_CP_WEAPON,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		status_change_start(bl,SC_CP_SHIELD,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		status_change_start(bl,SC_CP_ARMOR,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		status_change_start(bl,SC_CP_HELM,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;

	case SA_DISPELL:			/* ディスペル */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		// ソウルリンカーは無効
		if(dstsd && dstsd->status.class_ == PC_CLASS_SL)
			break;
		sc = status_get_sc(bl);
		if(sc && sc->data[SC_ROGUE].timer != -1)	// ローグの魂中は無効
			break;
		if(atn_rand()%100 >= skilllv*10+50)
			break;
		status_change_release(bl,0x02);	// ディスペルによるステータス異常解除
		break;

	case TF_BACKSLIDING:		/* バックステップ */
		sc = status_get_sc(src);
		if(!sc || sc->data[SC_ANKLE].timer == -1) {
			// 方向を保存しておいて、吹き飛ばし後に戻す
			int dir = 0, head_dir = 0;
			int count = skill_get_blewcount(skillid,skilllv);
			if(sd) {
				dir = sd->dir;
				head_dir = sd->head_dir;
			}
			unit_stop_walking(src,1);
			clif_skill_nodamage(src,src,skillid,skilllv,1);
			skill_blown(src,bl,count|SAB_REVERSEBLOW|SAB_NODAMAGE|SAB_NOPATHSTOP|SAB_NOTKNOCK);
			if(sd)
				pc_setdir(sd, dir, head_dir);
			if(sc && sc->data[SC_CLOSECONFINE].timer != -1)
				status_change_end(bl,SC_CLOSECONFINE,-1);
		}
		break;

	case SA_CASTCANCEL:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		unit_skillcastcancel(src,1);
		if(sd) {
			int sp = skill_get_sp(sd->skill_used.id,sd->skill_used.lv) * (110 - 20 * skilllv) / 100;
			if(sp > 0)
				pc_heal(sd,0,-sp,0,0);
		}
		break;
	case SA_SPELLBREAKER:	/* スペルブレイカー */
		if(sd && status_get_mode(bl)&MD_BOSS && atn_rand()%100 < 90) {
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
			break;
		}
		sc = status_get_sc(bl);
		if(sc && sc->data[SC_MAGICROD].timer != -1) {
			int sp;
			if(dstsd) {
				sp = skill_get_sp(skillid,skilllv) * sc->data[SC_MAGICROD].val2 / 100; 
				if(sp > 0x7fff) sp = 0x7fff;
				else if(sp < 1) sp = 1;
				if(dstsd->status.sp + sp > dstsd->status.max_sp) {
					sp = dstsd->status.max_sp - dstsd->status.sp;
					dstsd->status.sp = dstsd->status.max_sp;
				} else {
					dstsd->status.sp += sp;
				}
				clif_heal(dstsd->fd,SP_SP,sp);
			}
			clif_skill_nodamage(bl,bl,SA_MAGICROD,sc->data[SC_MAGICROD].val1,1);
			if(sd) {
				sp = sd->status.max_sp/5;
				if(sp < 1) sp = 1;
				pc_heal(sd,0,-sp,0,0);
			}
		} else {
			struct unit_data *ud = unit_bl2ud(bl);
			if(ud && ud->skilltimer != -1 && ud->skillid > 0 && skill_get_skill_type(ud->skillid) == BF_MAGIC) {
				int sp = skill_get_sp(ud->skillid,ud->skilllv);
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
				unit_skillcastcancel(bl,0);
				if(dstsd)
					pc_heal(dstsd,0,-sp,0,0);
				if(sd) {
					sp = sp * 25 * (skilllv - 1) / 100;
					if(skilllv > 1 && sp < 1) sp = 1;
					if(sp > 0x7fff) sp = 0x7fff;
					else if(sp < 1) sp = 1;
					if(sd->status.sp + sp > sd->status.max_sp) {
						sp = sd->status.max_sp - sd->status.sp;
						sd->status.sp = sd->status.max_sp;
					} else {
						sd->status.sp += sp;
					}
					clif_heal(sd->fd,SP_SP,sp);
				}
			} else if(sd) {
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
			}
		}
		break;
	case SA_MAGICROD:
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SA_AUTOSPELL:			/* オートスペル */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sd) {
			clif_autospell(sd,skilllv);
		} else {
			int maxlv = 1, spellid = 0;
			if(skilllv >= 10) {
				spellid = MG_FROSTDIVER;
				maxlv = skilllv - 9;
			}
			else if(skilllv >= 8) {
				spellid = MG_FIREBALL;
				maxlv = skilllv - 7;
			}
			else if(skilllv >= 5) {
				spellid = MG_SOULSTRIKE;
				maxlv = skilllv - 4;
			}
			else if(skilllv >= 2) {
				int r = atn_rand()%3;
				if(r == 0)
					spellid = MG_COLDBOLT;
				else if(r == 1)
					spellid = MG_FIREBOLT;
				else
					spellid = MG_LIGHTNINGBOLT;
				maxlv = skilllv - 1;
			}
			else if(skilllv > 0) {
				spellid = MG_NAPALMBEAT;
				maxlv = 3;
			}
			if(spellid > 0)
				status_change_start(src,SC_AUTOSPELL,skilllv,spellid,maxlv,0,skill_get_time(SA_AUTOSPELL,skilllv),0);
		}
		break;
	case PF_MINDBREAKER:
		if(atn_rand()%100 < 55 + skilllv * 5) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);

			// 凍結・石化・睡眠を解除
			status_change_attacked_end(bl);

			if(dstmd) {
				int range = skill_get_fixed_range(src,skillid,skilllv);
				mob_target(dstmd,src,range);
				battle_join_struggle(dstmd, src);
			}
			unit_skillcastcancel(bl,2);	// 詠唱妨害
		} else if(sd) {
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		}
		break;
	case PF_SOULCHANGE:		/* ソウルチェンジ */
		if(sd && dstsd) {
			int sp;
			// PVP,GVG以外ではPTメンバーにのみ使用可
			if(!map[src->m].flag.pvp && !map[src->m].flag.gvg && battle_check_target(src,bl,BCT_PARTY) <= 0)
				break;
			// 対象がバーサーク中でない場合のみ使用可
			if(dstsd->sc.data[SC_BERSERK].timer != -1)
				break;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			sp = sd->status.sp - dstsd->status.sp;
#ifndef PRE_RENEWAL
			sp = sp / 2;
#endif
			pc_heal(sd,0,-sp,0,0);
			pc_heal(dstsd,0,sp,0,1);
		}
		break;
	case NPC_ATTRICHANGE:	/* ランダム属性変化 */
		if(md) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			md->def_ele = atn_rand()%ELE_MAX;
			if(md->def_ele == ELE_UNDEAD)		// 不死は除く
				md->def_ele = ELE_NEUTRAL;
			md->def_ele += (1 + atn_rand()%4) * 20;	// 属性レベルはランダム
		} else if(sd) {
			static int armor_element[9]={
				SC_ELEMENTWATER,SC_ELEMENTGROUND,SC_ELEMENTFIRE,SC_ELEMENTWIND,SC_ELEMENTPOISON,
				SC_ELEMENTHOLY,SC_ELEMENTDARK,SC_ELEMENTELEKINESIS,SC_ELEMENTUNDEAD
			};
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,armor_element[atn_rand()%9],skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;

	case NPC_CHANGEWATER:
	case NPC_CHANGEGROUND:
	case NPC_CHANGEFIRE:
	case NPC_CHANGEWIND:
	case NPC_CHANGEPOISON:
	case NPC_CHANGEHOLY:
	case NPC_CHANGETELEKINESIS:
	case NPC_CHANGEDARKNESS:
	case NPC_CHANGEUNDEAD2:
		if(md) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			md->def_ele = skill_get_pl(skillid);
			md->def_ele += (1 + atn_rand()%4) * 20;	// 属性レベルはランダム
		} else if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case NPC_PROVOCATION:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(md && md->skillidx != -1)
			clif_pet_performance(src,mobdb_search(md->class_)->skill[md->skillidx].val[0]);
		break;

	case NPC_SMOKING:			/* 喫煙 */
		clif_damage(src,src,tick,status_get_amotion(src),status_get_dmotion(src),3,1,0,0,0);
		break;

	case NPC_HALLUCINATION:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;

	case NPC_KEEPING:
	case NPC_BARRIER:
		{
			struct unit_data *ud = unit_bl2ud(src);
			int skill_time = skill_get_time(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_time,0);
			if(ud)
				ud->canmove_tick = tick + skill_time;
		}
		break;

	case NPC_DARKBLESSING:
		{
			int sc_def = 100 - status_get_mdef(bl);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(dstsd && dstsd->special_state.no_magic_damage)
				break;
			if(status_get_elem_type(bl) == ELE_DARK || status_get_race(bl) == RCT_DEMON)
				break;
			if(atn_rand()%100 < sc_def * (50 + skilllv * 5) / 100) {
				if(dstsd) {
					int hp = status_get_hp(bl) - 1;
					pc_heal(dstsd,-hp,0,0,0);
				}
				else if(dstmd) {
					dstmd->hp = 1;
				}
			}
		}
		break;

	case NPC_LICK:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_weapon_damage )
			break;
		if(dstsd)
			pc_heal(dstsd,0,-100,0,0);
		if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,skilllv*500,status_get_lv(src)))
			status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		break;

	case NPC_SUICIDE:			/* 自決 */
		if(md) {
			md->state.noexp  = 1;
			md->state.nodrop = 1;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			mob_damage(NULL,md,md->hp,3);
		}
		break;

	case NPC_SUMMONSLAVE:		/* 手下召喚 */
	case NPC_SUMMONMONSTER:		/* MOB召喚 */
	case NPC_DEATHSUMMON:		/* デスサモン */
		if(md && md->skillidx != -1) {
			struct mob_skill *ms = &mobdb_search(md->class_)->skill[md->skillidx];
			mob_summonslave(md,ms->val,sizeof(ms->val)/sizeof(ms->val[0]),skilllv,skillid);
		}
		break;
	case NPC_CALLSLAVE:		/* 取り巻き呼び戻し */
		if(md) {
			int mobcount;
			md->recallcount       = 0;	// 初期化
			md->state.recall_flag = 0;
			mobcount = mob_countslave(md);
			if(mobcount > 0) {
				md->state.recall_flag = 1;	// mob.cの[取り巻きモンスターの処理]で利用
				md->recallmob_count   = mobcount;
			}
		}
		break;
	case NPC_REBIRTH:
		if(md && !md->state.rebirth) {
			// 1度もリバースを使ってない場合のみ発動
			status_change_start(src,SC_REBIRTH,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case NPC_RUN:		/* 後退 */
		if(md) {
			int dx = dirx[md->dir] * skilllv;
			int dy = diry[md->dir] * skilllv;
			mob_unlocktarget(md,tick);
			unit_walktoxy(&md->bl,md->bl.x-dx,md->bl.y-dy);	// 自分の向いている方向と逆向きに移動
		}
		break;

	case NPC_TRANSFORMATION:
	case NPC_METAMORPHOSIS:
		if(md && md->skillidx != -1) {
			struct mob_skill *ms = &mobdb_search(md->class_)->skill[md->skillidx];
			int size = sizeof(ms->val)/sizeof(ms->val[0]);
			if(skilllv > 1)
				mob_summonslave(md,ms->val,size,skilllv-1,0);
			mob_class_change(md,ms->val,size);
		}
		break;

	case NPC_EMOTION:			/* エモーション */
	case NPC_EMOTION_ON:			/* モードチェンジ */
		if(md && md->skillidx != -1) {
			clif_emotion(&md->bl,mobdb_search(md->class_)->skill[md->skillidx].val[0]);
			if(mobdb_search(md->class_)->skill[md->skillidx].val[1]) {	// モードチェンジ
				md->mode = mobdb_search(md->class_)->skill[md->skillidx].val[1];
				unit_stop_walking(&md->bl,1);
				unit_stopattack(&md->bl);
				mob_unlocktarget(md, tick);
				if( md->state.norandomwalk )
					md->state.norandomwalk = 0;
			}
			status_change_end(src,SC_MODECHANGE,-1);
			if(skillid == NPC_EMOTION_ON)
				status_change_start(src,SC_MODECHANGE,skilllv,skillid,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;

	case WE_MALE:				/* 君だけは護るよ */
		if(sd && dstsd) {
			int hp_rate = (skilllv <= 0)? 0: skill_db[skillid].hp_rate[skilllv-1];
			int gain_hp;
			if(battle_config.new_marrige_skill)
				gain_hp = dstsd->status.max_hp;
			else
				gain_hp = sd->status.max_hp;
			gain_hp = gain_hp * abs(hp_rate) / 100;
			gain_hp = skill_fix_heal(&sd->bl, &dstsd->bl, skillid, gain_hp);
			clif_skill_nodamage(src,bl,skillid,gain_hp,1);
			battle_heal(NULL,bl,gain_hp,0,0);
		}
		break;
	case WE_FEMALE:				/* あなたに尽くします */
		if(sd && dstsd) {
			int sp_rate = (skilllv <= 0)? 0: skill_db[skillid].sp_rate[skilllv-1];
			int gain_sp;
			// バーサーク中の対象には無効
			if(dstsd->sc.data[SC_BERSERK].timer != -1)
				break;
			if(battle_config.new_marrige_skill)
				gain_sp = dstsd->status.max_sp;
			else
				gain_sp = sd->status.max_sp;
			gain_sp = gain_sp * abs(sp_rate) / 100;
			clif_skill_nodamage(src,bl,skillid,gain_sp,1);
			battle_heal(NULL,bl,0,gain_sp,0);

			// スパノビの嫁が旦那に使用すると10%の確率でステータス付与
			if((sd->s_class.job == PC_JOB_SNV || sd->s_class.job == PC_JOB_ESNV) && sd->sex == SEX_FEMALE && atn_rand()%100 < 10) {
				int sec = skill_get_time2(skillid,skilllv);
				status_change_start(&sd->bl,GetSkillStatusChangeTable(skillid),skilllv,1,0,0,sec,0);
				status_change_start(&dstsd->bl,GetSkillStatusChangeTable(skillid),skilllv,2,0,0,sec,0);
			}
		}
		break;

	case WE_CALLPARTNER:			/* あなたに逢いたい */
	case WE_CALLPARENT:			/* ママ、パパ、来て */
	case WE_CALLBABY:			/* 坊や、いらっしゃい */
		if(sd) {
			int i, d, x, y;
			if(map[sd->bl.m].flag.nomemo) {
				clif_skill_teleportmessage(sd,1);
				map_freeblock_unlock();
				return 0;
			}
			if(skillid == WE_CALLPARTNER)
				clif_callpartner(sd);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);

			if(battle_config.pc_land_skill_limit) {
				int maxcount = skill_get_maxcount(sd->ud.skillid,sd->ud.skilllv);
				if(maxcount > 0) {
					if(skill_count_unitgroup(&sd->ud, sd->ud.skillid) >= maxcount) {
						clif_skill_fail(sd,sd->ud.skillid,SKILLFAIL_FAILED,0,0);
						sd->ud.canact_tick  = tick;
						sd->ud.canmove_tick = tick;
						map_freeblock_unlock();
						return 0;
					}
				}
			}
			// 目の前に呼び出す
			for(i = 0; i < 8; i++) {
				if(i&1)
					d = (sd->dir - ((i+1)>>1)) & 7;
				else
					d = (sd->dir + ((i+1)>>1)) & 7;

				x = sd->bl.x + dirx[d];
				y = sd->bl.y + diry[d];
				if(map_getcell(sd->bl.m,x,y,CELL_CHKPASS))
					break;
			}
			if(i >= 8) {
				x = sd->bl.x;
				y = sd->bl.y;
			}
			skill_unitsetting(src,skillid,skilllv,x,y,0);
		}
		break;
	case PF_HPCONVERSION:			/* 生命力変換 */
		if(sd) {
			if(sd->status.hp <= sd->status.max_hp / 10) {
				clif_skill_fail(sd,skillid,SKILLFAIL_HP,0,0);
			} else {
				int conv_hp = 0, conv_sp = 0;
				clif_skill_nodamage(src, bl, skillid, skilllv, 1);
				conv_hp = sd->status.max_hp / 10; // 基本はMAXHPの10%
				conv_sp = conv_hp * 10 * skilllv / 100;
				if(sd->status.sp + conv_sp > sd->status.max_sp)
					conv_sp = sd->status.max_sp - sd->status.sp;
				pc_heal(sd, -conv_hp, conv_sp,0,1);
			}
		}
		break;
	case HT_REMOVETRAP:				/* リムーブトラップ */
	case MA_REMOVETRAP:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(bl->type == BL_SKILL) {
			struct skill_unit *su = (struct skill_unit *)bl;
			if(!su || !su->group || !skill_unit_istrap(su->group->unit_id))
				break;
			if(su->group->src_id != src->id && !map[bl->m].flag.pvp && !map[bl->m].flag.gvg)
				break;
			if(su->group->unit_id == UNT_ANKLESNARE && su->group->val2) {
				struct block_list *target = map_id2bl(su->group->val2);
				if(target && target->type == BL_PC)
					status_change_end(target,SC_ANKLE,-1);
			} else if(sd && itemdb_exists(su->group->val3)) {
				// 罠を取り返す
				struct item item_tmp;
				int eflag;
				if(battle_config.skill_removetrap_type == 1) {
					int i;
					for(i=0; i<MAX_SKILL_DB_ITEM; i++) {
						if(skill_db[su->group->skill_id].itemid[i] <= 0)
							continue;
						memset(&item_tmp,0,sizeof(item_tmp));
						// 設置用トラップの代わりに改良型設置用トラップを消費していた場合
						if(skill_db[su->group->skill_id].itemid[i] == 1065 && su->group->val3 == 7940) {
							item_tmp.nameid = 7940;
							item_tmp.amount = 1;
						} else {
							item_tmp.nameid = skill_db[su->group->skill_id].itemid[i];
							item_tmp.amount = skill_db[su->group->skill_id].amount[i];
						}
						item_tmp.identify = 1;
						if((eflag = pc_additem(sd,&item_tmp,item_tmp.amount,false))) {
							clif_additem(sd,0,0,eflag);
							map_addflooritem(&item_tmp,item_tmp.amount,sd->bl.m,sd->bl.x,sd->bl.y,0,0,0,0);
						}
					}
				} else {
					memset(&item_tmp,0,sizeof(item_tmp));
					item_tmp.nameid   = su->group->val3;
					item_tmp.identify = 1;
					if((eflag = pc_additem(sd,&item_tmp,1,false))) {
						clif_additem(sd,0,0,eflag);
						map_addflooritem(&item_tmp,1,sd->bl.m,sd->bl.x,sd->bl.y,0,0,0,0);
					}
				}

			}
			skill_delunit(su);
		}
		break;
	case HT_SPRINGTRAP:				/* スプリングトラップ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(bl->type == BL_SKILL) {
			struct skill_unit *su = (struct skill_unit *)bl;
			if(!su || !su->group || !skill_unit_istrap(su->group->unit_id))
				break;
			if(su->group->unit_id == UNT_ANKLESNARE && su->group->val2 > 0)		// 補足中は破壊不可
				break;
			su->group->unit_id = UNT_USED_TRAPS;
			clif_changelook(bl,LOOK_BASE,su->group->unit_id);
			su->group->limit = su->limit = DIFF_TICK(tick+1500,su->group->tick);
		}
		break;
	case BD_ENCORE:					/* アンコール */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sd)
			unit_skilluse_id(&sd->bl,src->id,sd->skill_dance.id,sd->skill_dance.lv);
		break;
	case AS_SPLASHER:		/* ベナムスプラッシャー */
		if(
#ifdef PRE_RENEWAL
			(atn_bignumber)status_get_max_hp(bl)*3/4 < status_get_hp(bl) ||
#endif
			status_get_mode(bl)&MD_BOSS) {
			// HPが3/4以上残っているか相手がボス属性なら失敗
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
			map_freeblock_unlock();
			return 1;
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,skillid,src->id,0,skill_get_time(skillid,skilllv),0);
		break;
	case ASC_EDP:			/* エンチャントデッドリーポイズン */
		{
			int time = skill_get_time(skillid,skilllv);
			if(sd)
				time += pc_checkskill(sd,GC_RESEARCHNEWPOISON) * 3000;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,time,0);
#ifndef PRE_RENEWAL
			// pre時の計算式が不明のためRE限定
			status_change_start(bl,SC_MAGNUM,skilllv,ELE_POISON,0,0,time,0);
#endif
		}
		break;
	case RG_CLOSECONFINE:		/* クローズコンファイン */
		{
			int dir;
			if(status_get_mode(bl)&MD_BOSS) {
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				break;
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(src,GetSkillStatusChangeTable(skillid),1,1,src->id,bl->id,skill_get_time(skillid,skilllv),0);

			dir = path_calc_dir(src,bl->x,bl->y);
			//unit_setdir(src,dir);
			unit_movepos(bl,src->x+dirx[dir],src->y+diry[dir],0);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),1,2,bl->id,src->id,skill_get_time(skillid,skilllv),0);
		}
		break;
	case NPC_STOP:			/* ホールドウェブ */
		status_change_start(src,GetSkillStatusChangeTable(skillid),1,1,src->id,bl->id,skill_get_time(skillid,skilllv),0);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),1,2,bl->id,src->id,skill_get_time(skillid,skilllv),0);
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		break;
	case PR_REDEMPTIO:		/* レデムプティオ */
		if(sd == NULL)
			break;
		if(flag&1) {
			if(unit_isdead(bl)) {
				skill_area_temp[0]++;
				skill_castend_nodamage_id(src,bl,ALL_RESURRECTION,3,tick,1);
			}
		} else {
			skill_area_temp[0] = 0;
			party_foreachsamemap(skill_area_sub,
				sd,AREA_SIZE,
				src,skillid,skilllv,tick, flag|BCT_PARTY|1,
				skill_castend_nodamage_id);

			if(!battle_config.redemptio_penalty_type)
				break;
			if(battle_config.redemptio_penalty_type&1 && skill_area_temp[0] == 0)
				break;
			if(battle_config.redemptio_penalty_type&2 && skill_area_temp[0] >= 5)
				break;

			// HP1, SP0
			pc_heal(sd, -sd->status.hp + 1, -sd->status.sp, 0, 0);

			// 経験値ペナルティ
			if(skill_area_temp[0] < 5) {
				int per = (5 - skill_area_temp[0]) * 20;
				pc_exp_penalty(sd, NULL, per, 3);
			}
		}
		break;

	case MO_KITRANSLATION:		/* 気功転移 */
		if(dstsd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			pc_addspiritball(dstsd,skill_get_time(skillid,skilllv),1);
		}
		break;
	case BS_GREED:			/* グリード */
		if (sd && (battle_config.greed_use_town || !map[src->m].flag.town) && !map[src->m].flag.pvp && !map[src->m].flag.gvg) {	// 街・PvP・GvGでは使用不可
			struct party *p = NULL;
			int ar = skill_get_area(skillid,skilllv);
			if(sd->status.party_id > 0)
				p = party_search(sd->status.party_id);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_greed,sd->bl.m,sd->bl.x-ar,sd->bl.y-ar,sd->bl.x+ar,sd->bl.y+ar,BL_ITEM,sd,p);
		}
		break;

	case GD_BATTLEORDER:		/* 臨戦態勢 */
	case GD_REGENERATION:		/* 激励 */
	case GD_RESTORE:		/* 治療 */
		if(sd) {
			int mi, range;
			struct guild *g = guild_search(sd->status.guild_id);

			if(g == NULL)
				break;
			range = skill_get_range(skillid,skilllv);
			for(mi = 0; mi < g->max_member; mi++)
			{
				struct map_session_data *member = g->member[mi].sd;
				if(member == NULL)
					continue;
				if(sd->bl.m != member->bl.m)
					continue;
				if(path_distance(sd->bl.x,sd->bl.y,member->bl.x,member->bl.y) <= range) {
					clif_skill_nodamage(src,&member->bl,skillid,skilllv,1);
					if(skillid == GD_RESTORE) {
						// バーサーク中のメンバーには使用不可
						if(member->sc.data[SC_BERSERK].timer != -1)
							continue;
						pc_heal(member, member->status.max_hp * 90 / 100, member->status.max_sp * 90 / 100, 0, 0);
					} else {
						status_change_start(&member->bl,GetSkillStatusChangeTable(skillid),skilllv,skillid,0,0,skill_get_time(skillid,skilllv),0);
					}
				}
			}
			if(skillid == GD_BATTLEORDER)
				status_change_start(&sd->bl,SC_BATTLEORDER_DELAY,0,0,0,0,300000,0);
			else if(skillid == GD_REGENERATION)
				status_change_start(&sd->bl,SC_REGENERATION_DELAY,0,0,0,0,300000,0);
			else
				status_change_start(&sd->bl,SC_RESTORE_DELAY,0,0,0,0,300000,0);
		}
		break;
	case GD_EMERGENCYCALL:		/* 緊急招集 */
		if(sd) {
			int mi, px, py, count = 0;
			struct guild *g = guild_search(sd->status.guild_id);
			struct cell_xy free_cell[7*7];

			if(g == NULL)
				break;
			clif_skill_nodamage(src,src,skillid,skilllv,1);

			if(battle_config.emergencycall_point_type != 0)
				count = map_searchfreecell(free_cell,sd->bl.m,sd->bl.x-3,sd->bl.y-3,sd->bl.x+3,sd->bl.y+3);

			for(mi = 0; mi < g->max_member; mi++)
			{
				struct map_session_data *member = g->member[mi].sd;
				if(member == NULL)
					continue;
				if(member->bl.id == sd->bl.id)	// 自分自身は除外
					continue;
				if(battle_config.emergencycall_call_limit && sd->bl.m != member->bl.m)	// 同マップのみ
					continue;
				if(member->state.refuse_emergencycall)
					continue;

				if(count <= 0) {
					// 足元
					px = sd->bl.x;
					py = sd->bl.y;
				} else {
					int idx = atn_rand()%count;
					px = free_cell[idx].x;
					py = free_cell[idx].y;
					if(battle_config.emergencycall_point_type == 2 &&
					   path_search(NULL,sd->bl.m,sd->bl.x,sd->bl.y,px,py,0))
					{
						// 崖越えEMC禁止
						mi--;
						count--;
						free_cell[idx] = free_cell[count];
						continue;
					}
				}
				pc_setpos(member,map[sd->bl.m].name,px,py,3);
			}
			status_change_start(&sd->bl,SC_EMERGENCYCALL_DELAY,0,0,0,0,300000,0);
		}
		break;

	case SG_FEEL:
		if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(!sd->status.feel_map[skilllv-1][0])
				clif_feel_display(sd,skilllv);
			else
				clif_feel_info(sd,skilllv);
		}
		break;
	case SG_HATE:
		if(sd && skilllv > 0 && skilllv <= 3) {
			// 既に登録済み
			if(sd->hate_mob[skilllv-1] != -1) {
				clif_hate_info(sd,skilllv,sd->hate_mob[skilllv-1]);
				break;
			}
			if(dstsd) {	// 登録相手がPC
				sd->hate_mob[skilllv-1] = dstsd->status.class_;
				if(battle_config.save_hate_mob)
					pc_setglobalreg(sd,"PC_HATE_MOB_STAR",sd->hate_mob[skilllv-1]+1);
				clif_skill_nodamage(src,src,skillid,skilllv,1);
				clif_hate_mob(sd,skilllv,sd->hate_mob[skilllv-1]);
			} else if(dstmd) {	// 登録相手がMOB
				switch(skilllv) {
				case 1:
					if(status_get_size(bl) == 0) {
						sd->hate_mob[0] = dstmd->class_;
						if(battle_config.save_hate_mob)
							pc_setglobalreg(sd, "PC_HATE_MOB_SUN", sd->hate_mob[0]+1);
						clif_skill_nodamage(src,src,skillid,skilllv,1);
						clif_hate_mob(sd,skilllv,sd->hate_mob[0]);
					} else {
						clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
					}
					break;
				case 2:
					if(status_get_size(bl) == 1 && status_get_max_hp(bl) >= 6000) {
						sd->hate_mob[1] = dstmd->class_;
						if(battle_config.save_hate_mob)
							pc_setglobalreg(sd, "PC_HATE_MOB_MOON", sd->hate_mob[1]+1);
						clif_skill_nodamage(src,src,skillid,skilllv,1);
						clif_hate_mob(sd,skilllv,sd->hate_mob[1]);
					} else {
						clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
					}
					break;
				case 3:
					if(status_get_size(bl) == 2 && status_get_max_hp(bl) >= 20000) {
						sd->hate_mob[2] = dstmd->class_;
						if(battle_config.save_hate_mob)
							pc_setglobalreg(sd, "PC_HATE_MOB_STAR", sd->hate_mob[2]+1);
						clif_skill_nodamage(src,src,skillid,skilllv,1);
						clif_hate_mob(sd,skilllv,sd->hate_mob[2]);
					} else {
						clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
					}
					break;
				default:
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
					break;
				}
			}
		}
		break;
	case SG_FUSION:
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_end(bl,SC_STAR,-1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SL_ALCHEMIST:		/* アルケミストの魂 */
	case SL_MONK:			/* モンクの魂 */
	case SL_STAR:			/* ケンセイの魂 */
	case SL_SAGE:			/* セージの魂 */
	case SL_CRUSADER:		/* クルセイダーの魂 */
	case SL_KNIGHT:			/* ナイトの魂 */
	case SL_WIZARD:			/* ウィザードの魂 */
	case SL_PRIEST:			/* プリーストの魂 */
	case SL_SUPERNOVICE:		/* スーパーノービスの魂 */
	case SL_BARDDANCER:		/* バードとダンサーの魂 */
	case SL_ROGUE:			/* ローグの魂 */
	case SL_ASSASIN:		/* アサシンの魂 */
	case SL_BLACKSMITH:		/* ブラックスミスの魂 */
	case SL_HUNTER:			/* ハンターの魂 */
	case SL_SOULLINKER:		/* ソウルリンカーの魂 */
	case SL_DEATHKNIGHT:		/* デスナイトの魂 */
	case SL_COLLECTOR:		/* ダークコレクターの魂 */
	case SL_NINJA:			/* 忍者の魂 */
	case SL_GUNNER:			/* ガンスリンガーの魂 */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(src,SC_SMA,skilllv,0,0,0,3000,0);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SL_HIGH:			/* 転生一次職業の魂 */
		if(status_get_lv(bl) < 11 || status_get_lv(bl) > 70) {   // 対象のベースレベルが11以下、または70以上だと使用不可
			if(sd)
				clif_skill_fail(sd,skillid,SKILLFAIL_TOTARGET,0,0);
				break;
			}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(src,SC_SMA,skilllv,0,0,0,3000,0);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case GS_MADNESSCANCEL:		/* マッドネスキャンセラー */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		sc = status_get_sc(bl);
		if(sc && sc->data[GetSkillStatusChangeTable(skillid)].timer != -1) {
			status_change_end(bl, GetSkillStatusChangeTable(skillid), -1);
		} else {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case GS_ADJUSTMENT:			/* アジャストメント */
		sc = status_get_sc(bl);
		if(!sc || sc->data[SC_MADNESSCANCEL].timer == -1) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		} else if(sd) {
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		}
		break;
	case GS_CRACKER:			/* クラッカー */
		{
			int cost = skill_get_arrow_cost(skillid,skilllv);
			int rate;
			if(cost > 0 && !battle_delarrow(sd, cost, skillid))	// 弾の消費
				break;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			rate = 5000 - (unit_distance(src,bl) / 3) * 1000;
			if(rate < 2000)
				rate = 2000;

			if(atn_rand() % 10000 < status_change_rate(bl,SC_STUN,rate,status_get_lv(src))) {
				status_change_pretimer(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
			} else if(sd) {
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
			}
		}
		break;
	case NJ_BUNSINJYUTSU:		/* 影分身 */
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		sc = status_get_sc(bl);
		if(sc && sc->data[SC_NEN].timer != -1)
			status_change_end(bl,SC_NEN,-1);
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		break;
	case ALL_BUYING_STORE:			/* 買取露店開設 */
		if(sd) {
			if(npc_isnear(&sd->bl)) {
				clif_skill_fail(sd,skillid,SKILLFAIL_NEARNPC,0,0);
				return 1;
			}
			buyingstore_openstorewindow(sd, MAX_BUYINGSTORE_COUNT);
		}
		break;
	case ALL_WEWISH:			/* ホーリーナイト */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		break;
	case RETURN_TO_ELDICASTES:		/* エルディカスティスへの帰還 */
	case ALL_GUARDIAN_RECALL:		/* モーラへの帰還 */
	case ECLAGE_RECALL:		/* エクラージュへの帰還 */
	case ALL_NIFLHEIM_RECALL:		/* ニブルヘイムへの帰還 */
	case ALL_PRONTERA_RECALL:		/* プロンテラへの帰還 */
	case ALL_GLASTHEIM_RECALL:		/* グラストヘイムへの帰還 */
	case ALL_THANATOS_RECALL:		/* タナトスタワーへの帰還 */
	case ALL_LIGHTHALZEN_RECALL:	/* リヒタルゼンへの帰還 */
		if(sd) {
			int x, y;
			const char *mapname;

			if(battle_config.noportal_flag) {
				if(map[sd->bl.m].flag.noportal)		// noportalで禁止
					break;
			}
			if(skillid == RETURN_TO_ELDICASTES) {
				x = 198;
				y = 187;
				mapname = "dicastes01.gat";
			} else if(skillid == ALL_GUARDIAN_RECALL) {
				x = 44;
				y = 151;
				mapname = "mora.gat";
			} else if(skillid == ALL_NIFLHEIM_RECALL) {
				x = 193;
				y = 186;
				mapname = "niflheim.gat";
			} else if(skillid == ALL_PRONTERA_RECALL) {
				x = (skilllv==1)? 115: 159;
				y = (skilllv==1)? 72: 192;
				mapname = "prontera.gat";
			} else if(skillid == ALL_GLASTHEIM_RECALL) {
				x = 200;
				y = 268;
				mapname = "glast_01.gat";
			} else if(skillid == ALL_THANATOS_RECALL) {
				x = 139;
				y = 156;
				mapname = "hu_fild01.gat";
			} else if(skillid == ALL_LIGHTHALZEN_RECALL) {
				x = 307;
				y = 307;
				mapname = "lighthalzen.gat";
			} else {
				x = 47;
				y = 31;
				mapname = "ecl_in01.gat";
			}

			if(pc_setpos(sd,mapname,x,y,0)) {
				// マップが存在しなかった
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				map_freeblock_unlock();
				return 0;
			}
		}
		break;
	case HAMI_CASTLE:		/* キャスリング */
		if(hd && hd->msd && atn_rand()%100 < 20*skilllv)
		{
			int x, y;
			struct map_session_data *msd = hd->msd;
			if( path_search(NULL,hd->bl.m,hd->bl.x,hd->bl.y,msd->bl.x,msd->bl.y,0) != 0 ) {
				// キャスリングを用いた壁越え禁止
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				break;
			}
			clif_skill_nodamage(&hd->bl,&msd->bl,skillid,skilllv,1);

			x = hd->bl.x;
			y = hd->bl.y;

			unit_movepos(&hd->bl,msd->bl.x,msd->bl.y,0);
			unit_movepos(&msd->bl,x,y,0);

			map_foreachinarea(skill_castle_mob_changetarget,hd->bl.m,
				hd->bl.x-AREA_SIZE,hd->bl.y-AREA_SIZE,
				hd->bl.x+AREA_SIZE,hd->bl.y+AREA_SIZE,
				BL_MOB,&msd->bl,&hd->bl);
		}
		break;
	case HVAN_CHAOTIC:		/* カオティックベネディクション */
		if(hd) {
			struct block_list* heal_target = NULL;
			int n = (skilllv < 5)? skilllv - 1: 4;
			int rnd = atn_rand()%100;
			static const int per[5][2] = {
				{20,50},{50,60},{25,75},{60,64},{34,67}
			};

			if(rnd < per[n][0]) {
				// ホム
				heal_target = &hd->bl;
			} else if(rnd < per[n][1]) {
				// 主人
				if(!unit_isdead(&hd->msd->bl))	// 生存
					heal_target = &hd->msd->bl;
				else
					heal_target = &hd->bl;
			} else {
				// MOB
				heal_target = map_id2bl(hd->target_id);
				if(heal_target == NULL)
					heal_target = &hd->bl;
			}
			if(heal_target) {
				int val  = (skilllv > 0)? skill_calc_heal(src, 1+atn_rand()%skilllv) : 0;
				int heal = skill_fix_heal(&hd->bl, heal_target, skillid, val);
				// エフェクト出ないのでヒール
				clif_skill_nodamage(src,heal_target,AL_HEAL,heal,1);
				clif_skill_nodamage(src,heal_target,skillid,heal,1);
				battle_heal(NULL,heal_target,heal,0,0);
				hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_time2(skillid,skilllv);
			}
		}
		break;
	case HLIF_AVOID:		/* 緊急回避 */
	case HAMI_DEFENCE:		/* ディフェンス */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		if(hd) {
			// 主人にも
			if(hd->msd && !unit_isdead(&hd->msd->bl)) {
				clif_skill_nodamage(src,&hd->msd->bl,skillid,skilllv,1);
				status_change_start(&hd->msd->bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
			hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_time2(skillid,skilllv);
		}
		break;
	case HAMI_BLOODLUST:		/* ブラッドラスト */
	case HFLI_FLEET:		/* フリートムーブ */
	case HFLI_SPEED:		/* オーバードスピード */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		if(hd) {
			hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_time2(skillid,skilllv);
		}
		break;
	case HLIF_CHANGE:		/* メンタルチェンジ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		unit_heal(src,status_get_max_hp(src),0,0,0);
		if(hd) {
			hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_time2(skillid,skilllv);
		}
		break;
	case MH_GOLDENE_FERSE:	/* ゴールデンペルジェ */
	case MH_ANGRIFFS_MODUS:	/* アングリフスモドス */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		if(hd) {
			hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
		}
		break;
	case MH_SUMMON_LEGION:	/* サモンレギオン */
		if(hd && hd->msd) {
			const int summons[5] = {2158, 2159, 2159, 2160, 2160};
			const int qty[5]     = {3   , 3   , 4   , 4   , 5};
			struct mob_data *tmpmd = NULL;
			int i,id;

			// レギオンモンスターの削除
			homun_deletelegion(hd);

			for(i=0; i<qty[skilllv - 1]; i++){
				id = mob_once_spawn_area(hd->msd, src->m, src->x-2, src->y-2, src->x+2, src->y+2, "--ja--", summons[skilllv - 1], 1, "");
				if((tmpmd = map_id2md(id)) != NULL) {
					tmpmd->master_id =  src->id;
					tmpmd->deletetimer  = add_timer(tick+skill_get_time(skillid,skilllv),mob_timer_delete,id,NULL);
					tmpmd->state.nodrop = battle_config.cannibalize_no_drop;
					tmpmd->state.noexp  = battle_config.cannibalize_no_exp;
					tmpmd->state.nomvp  = battle_config.cannibalize_no_mvp;
					tmpmd->target_id = bl->id;
					tmpmd->min_chase = 5 + path_distance(src->x,src->y,bl->x,bl->y);
					tmpmd->state.master_check = 1;
					tmpmd->state.norandomwalk = 1;
					tmpmd->state.special_mob_ai = MOB_AI_LEGION;
				}
			}
			hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
		}
		break;
	case MH_PAIN_KILLER:	/* ペインキラー */
		if(hd && hd->msd && bl->type != BL_PC && bl->type != BL_HOM) {
			clif_emotion(src,9);
			clif_skill_fail(hd->msd, skillid, SKILLFAIL_TOTARGET, 0, 0);
			return 0;
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,status_get_lv(src),status_get_lv(bl),0,skill_get_time(skillid,skilllv),0);
		status_change_start(bl,SC_ENDURE,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		if(hd) {
			hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
		}
		break;
	case MH_LIGHT_OF_REGENE:	/* 再生の光 */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(hd) {
			hd->intimate -= 10000;
			if(battle_config.homun_skill_intimate_type)
				hd->status.intimate = 1;
			clif_send_homdata(hd->msd,1,hd->intimate/100);
			status_change_start(&hd->msd->bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
		}
		break;
	case MH_OVERED_BOOST:	/* オーバードブースト */
	case MH_GRANITIC_ARMOR:	/* グラニティックアーマー */
	case MH_PYROCLASTIC:	/* パイロクラスティック */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(hd) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,skillid==MH_PYROCLASTIC? status_get_lv(bl): 0,skill_get_time(skillid,skilllv),0);
			status_change_start(&hd->msd->bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,skillid==MH_PYROCLASTIC? status_get_lv(bl): 0,skill_get_time(skillid,skilllv),0);
			hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
		}
		break;
	case MH_SILENT_BREEZE:	/* サイレントブリーズ */
		{
			int heal = skill_fix_heal(src, bl, skillid, skill_calc_heal(src, skilllv));

			// エフェクト出ないのでヒール
			clif_skill_nodamage(src,bl,AL_HEAL,heal,1);
			clif_skill_nodamage(src,bl,skillid,heal,1);
			battle_heal(NULL,bl,heal,0,0);
			status_change_end(bl, SC_HALLUCINATION, -1);
			status_change_end(bl, SC_CONFUSION, -1);
			status_change_end(bl, SC_SLEEP, -1);
			status_change_end(bl, SC_HARMONIZE, -1);
			status_change_end(bl, SC_DEEP_SLEEP, -1);
			status_change_end(bl, SC_MANDRAGORA, -1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			if(hd) {
				hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
			}
		}
		break;
	case MH_STYLE_CHANGE:	/* スタイルチェンジ */
		if(hd) {
			sc = status_get_sc(bl);
			if(sc && sc->data[SC_STYLE_CHANGE].timer != -1) {
				if(sc->data[SC_STYLE_CHANGE].val1 == 1) sc->data[SC_STYLE_CHANGE].val1 = 2;
				else sc->data[SC_STYLE_CHANGE].val1 = 1;
			}
			else
				status_change_start(bl,SC_STYLE_CHANGE,1,0,0,0,skill_get_time(skillid,skilllv),0);
			hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case MH_MAGMA_FLOW:		/* マグマフロー */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,skillid,skill_get_time(skillid,skilllv),0);
		if(hd)
			hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
		break;
	case MH_STEINWAND:			/* シュタインワンド */
		if(hd && hd->msd) {
			skill_castend_pos2(src,src->x,src->y,skillid,skilllv,tick,0);
			skill_castend_pos2(src,hd->msd->bl.x,hd->msd->bl.y,skillid,skilllv,tick,0);
			hd->skillstatictimer[skillid-HOM_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
		}
		break;
	case NPC_DRAGONFEAR:		/* ドラゴンフィアー */
	case NPC_WIDESILENCE:		/* 範囲沈黙攻撃 */
	case NPC_WIDEFREEZE:		/* 範囲凍結攻撃 */
	case NPC_WIDEBLEEDING:		/* 範囲出血攻撃 */
	case NPC_WIDESTONE:		/* 範囲石化攻撃 */
	case NPC_WIDECONFUSE:		/* 範囲混乱攻撃 */
	case NPC_WIDESLEEP:		/* 範囲睡眠攻撃 */
	case NPC_WIDECURSE:		/* 範囲呪い攻撃 */
	case NPC_WIDESTUN:		/* 範囲スタン攻撃 */
	case NPC_WIDEHELLDIGNITY:	/* ヘルディグニティ */
		if(flag&1) {
			if(skillid == NPC_DRAGONFEAR) {
				const int sc_type[4] = { SC_STUN, SC_CONFUSION, SC_SILENCE, SC_BLEED };
				int n = atn_rand() % 4;
				// upkeep_time2は配列の添え字に従う
				if(atn_rand() % 10000 < status_change_rate(bl,sc_type[n],10000,status_get_lv(src)))
					status_change_pretimer(bl,sc_type[n],skilllv,0,0,0,skill_get_time2(skillid,n+1),0,tick+status_get_amotion(src));
			} else {
				if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),10000,status_get_lv(src)))
					status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			//clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case NPC_WIDESIGHT:		/* ワイドサイト */
		clif_skill_nodamage(src,bl,MG_SIGHT,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,skillid,skill_get_time(skillid,skilllv),0);
		break;
	case NPC_SLOWCAST:		/* スロウキャスト */
		if(flag&1) {
			clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case NPC_WIDESOULDRAIN:	/* マナバーン */
		if(flag&1) {
			if(dstsd) {
				int sp = dstsd->status.max_sp * (((skilllv - 1) % 5 + 1) * 20) / 100;
				if(sp < 1) sp = 1;
				pc_heal(dstsd,0,-sp,0,0);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case NPC_TALK:			/* トーク */
		if(md && md->skillidx != -1) {
			mob_talk(md,mobdb_search(md->class_)->skill[md->skillidx].val[0]);
		}
		break;
	case NPC_INVINCIBLE:		/* インビンシブル */
		status_change_end(bl, SC_INVINCIBLEOFF, -1);
	case NPC_INVINCIBLEOFF:		/* インビンシブルオフ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	case NPC_PULSESTRIKE2:		/* パルスストライクII */
		{
			int i;

			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			for(i = 0; i < 3; i++) {
				skill_addtimerskill(src,tick + 1000 * i,bl->id,0,0,skillid,skilllv,0,0x0500);
			}
		}
		break;
	case NPC_LEX_AETERNA:		/* Mレックスエーテルナ */
		if( !(dstsd && dstsd->special_state.no_magic_damage) ) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case NPC_WIDEWEB:		/* ワイドウェブ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(flag&1) {
			skill_castend_pos2(src,bl->x,bl->y,PF_SPIDERWEB,skilllv,tick,0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case NPC_FIRESTORM:		/* 獄炎 */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(flag&1) {
			if(bl->id != skill_area_temp[1]) {
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
				battle_skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ALL|1,
				skill_castend_nodamage_id);
		}
		break;
	case NPC_WIDESUCK:		/* ワイドブラッド */
		{
			int heal = (int)((atn_bignumber)status_get_max_hp(bl) * 15 / 100);
			if(heal > 0) {
				struct block_list tbl;
				memset(&tbl, 0, sizeof(tbl));
				tbl.m = src->m;
				tbl.x = skill_area_temp[2];
				tbl.y = skill_area_temp[3];
				clif_damage(src,bl,tick,0,0,heal,0,0,0,0);
				clif_skill_nodamage(&tbl,src,AL_HEAL,heal,1);
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
				battle_heal(NULL,bl,-heal,0,0);
				battle_heal(NULL,src,heal,0,0);
			}
		}
		break;
	case NPC_ELECTRICWALK:	/* Mエレクトリックウォーク */
	case NPC_FIREWALK:		/* Mファイアーウォーク */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,skillid,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	case NPC_MANDRAGORA:		/* Mハウリングオブマンドラゴラ */
		if(flag&1) {
			if(atn_rand() % 10000 < 2000 * skilllv) {
				if(dstsd) {
					int sp = dstsd->status.max_sp * (25 + skilllv * 5) / 100;
					if(dstsd->status.sp < sp)
						sp = dstsd->status.sp;
					dstsd->status.sp -= sp;
					clif_updatestatus(dstsd,SP_SP);
				}
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case NPC_LEASH:	/* デスハンド */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(battle_check_target(src,bl,BCT_ENEMY) > 0 && !map[bl->m].flag.gvg && !(status_get_mode(bl)&MD_BOSS)) {
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
		break;
	case NPC_WIDELEASH:		/* ワイドデスハンド */
		if(flag&1) {
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
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case NPC_WIDEDISPEL:			/* ワイドディスペル */
		if(flag&1) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if( dstsd && dstsd->special_state.no_magic_damage )
				break;
			// ソウルリンカーは無効
			if(dstsd && dstsd->status.class_ == PC_CLASS_SL)
				break;
			sc = status_get_sc(bl);
			if(sc && sc->data[SC_ROGUE].timer != -1)	// ローグの魂中は無効
				break;
			status_change_release(bl,0x02);	// ディスペルによるステータス異常解除
		} else {
			int ar = skill_get_area(skillid,skilllv);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case NPC_ALL_STAT_DOWN:		/* オールステータスダウン */
		{
			int val = (skilllv>=5)? 100: skilllv*20 - 10;
			clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			clif_skill_nodamage(src, bl, skillid, skilllv, 1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,val,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case NPC_GRADUAL_GRAVITY:		/* グラデュアルグラビティ */
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,skilllv*30,0,0,skill_get_time(skillid,skilllv),0);
		clif_skill_nodamage(src, bl, skillid, skilllv, 1);
		break;
	case NPC_DAMAGE_HEAL:		/* ダメージヒール */
	case NPC_KILLING_AURA:	/* キリングオーラ */
		clif_skill_nodamage(src, bl, skillid, skilllv, 1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case NPC_IMMUNE_PROPERTY:		/* イミューンプロパティ */
		{
			const int sc_type[10] = {
				SC_IMMUNE_PROPERTY_NOTHING, SC_IMMUNE_PROPERTY_WATER,
				SC_IMMUNE_PROPERTY_GROUND, SC_IMMUNE_PROPERTY_FIRE, 
				SC_IMMUNE_PROPERTY_WIND, SC_IMMUNE_PROPERTY_DARKNESS,
				SC_IMMUNE_PROPERTY_SAINT, SC_IMMUNE_PROPERTY_POISON,
				SC_IMMUNE_PROPERTY_TELEKINESIS, SC_IMMUNE_PROPERTY_UNDEAD
			};
			if(skilllv >= 1 && skilllv <= 10) {
				clif_skill_nodamage(src, bl, skillid, skilllv, 1);
				status_change_start(bl,sc_type[skilllv-1],skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case NPC_MOVE_COORDINATE:		/* ポジションチェンジ */
		{
			int tx = bl->x, ty = bl->y;
			if (unit_movepos(bl, src->x, src->y, 0))
				return 0;

			clif_skill_nodamage(src, bl, skillid, skilllv, 1);
			clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);
			clif_blown(bl,src->x,src->y);

			if(!(status_get_mode(src)&MD_BOSS)) {
				if (unit_movepos(src, tx, ty, 0))
					return 0;
				clif_blown(src,tx,ty);
			}
		}
		break;
	case MER_REGAIN:		/* リゲイン */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		status_change_end(bl, SC_STUN, -1);
		status_change_end(bl, SC_SLEEP, -1);
		break;
	case MER_TENDER:		/* テンダー */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		status_change_end(bl, SC_FREEZE, -1);
		status_change_end(bl, SC_STONE, -1);
		break;
	case MER_BENEDICTION:		/* ベネディクション */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		status_change_end(bl, SC_CURSE, -1);
		status_change_end(bl, SC_BLIND, -1);
		break;
	case MER_RECUPERATE:		/* リキュポレイト */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		status_change_end(bl, SC_SILENCE, -1);
		status_change_end(bl, SC_POISON, -1);
		break;
	case MER_MENTALCURE:		/* メンタルキュア */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		status_change_end(bl, SC_CONFUSION, -1);
		status_change_end(bl, SC_HALLUCINATION, -1);
		break;
	case MER_COMPRESS:		/* コンプレス */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if( dstsd && dstsd->special_state.no_magic_damage )
			break;
		status_change_end(bl, SC_BLEED, -1);
		break;
	case MER_SCAPEGOAT:		/* 身代わり */
		if(mcd && mcd->msd) {
			int hp = status_get_hp(&mcd->bl);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			pc_heal(mcd->msd,hp,0,0,0);
			battle_damage(NULL,&mcd->bl,hp,skillid,skilllv,flag);
		}
		break;
	case MER_INVINCIBLEOFF2:	/* マインドブラスター */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		if(mcd)
			mcd->skillstatictimer[skillid-MERC_SKILLID] = tick + skill_get_cooldown(skillid,skilllv);
		break;
	case RK_ENCHANTBLADE:		/* エンチャントブレイド */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,status_get_int(src),0,0,skill_get_time(skillid,skilllv),0);
		break;
	case RK_DRAGONHOWLING:	/* ドラゴンハウリング */
		if(flag&1) {
			if(atn_rand() % 100 < 50 + skilllv * 6)
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case RK_CRUSHSTRIKE:		/* クラッシュストライク */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case RK_STONEHARDSKIN:		/* ストーンハードスキン */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,((sd)? pc_checkskill(sd,RK_RUNEMASTERY): 0),((sd)? sd->status.job_level: 0),0,skill_get_time(skillid,skilllv),0);
		break;
	case RK_REFRESH:			/* リフレッシュ */
		{
			int heal = (int)((atn_bignumber)status_get_max_hp(bl) * 25 / 100);
			battle_heal(NULL,bl,heal,0,0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_release(bl,0x08);		// 暫定でゴスペル全状態異常無効と同効果
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case RK_FIGHTINGSPIRIT:		/* ファイティングスピリット */
		if(flag&1) {
			if(src != bl && skill_area_temp[0])
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,skill_area_temp[0]*7/4,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			skill_area_temp[0] = 0;
			if(sd && sd->status.party_id > 0) {
				skill_area_temp[0] = party_check_same_map_member_count(sd);
				/* パーティ全体への処理 */
				party_foreachsamemap(skill_area_sub,
					sd,skill_get_area(skillid,skilllv),
					src,skillid,skilllv,tick, flag|BCT_PARTY|1,
					skill_castend_nodamage_id);
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,skill_area_temp[0]*7,((sd)? pc_checkskill(sd,RK_RUNEMASTERY): 0),0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case RK_LUXANIMA:		/* ラクスアニマ */
		{
			const int runes[6] = { SC_MILLENNIUMSHIELD, SC_REFRESH, SC_GIANTGROWTH, SC_STONEHARDSKIN, SC_VITALITYACTIVATION, SC_ABUNDANCE };

			if(sd == NULL || sd->status.party_id == 0 || flag&1) {
				if(src->id == bl->id)
					break;

				status_change_start(bl, runes[skill_area_temp[5]], skilllv, 0, 0, 0, skill_get_time(skillid, skilllv),0);
			} else if(sd) {
				int recent = 0, result = -1;
				int i;

				for(i = 0; i < 6; i++) {
					if(sd->sc.data[runes[i]].timer != -1 && ((sd->sc.data[runes[i]].timer * (runes[i] == SC_REFRESH? 3 : 1)) > recent || recent == 0)) {
						recent = sd->sc.data[runes[i]].timer;
						result = i;
					}
				}

				if(result != -1) {
					skill_area_temp[5] = result;
					status_change_end(src, runes[result], -1);
					party_foreachsamemap(skill_area_sub,sd,skill_get_area(skillid,skilllv),src,skillid,skilllv,tick, flag|BCT_PARTY|1,skill_castend_nodamage_id);
					clif_skill_nodamage(src, src, skillid, skilllv, 1);
				}
			}
		}
		break;
	case GC_CREATENEWPOISON:	/* 新毒製造 */
		if(sd) {
			clif_skill_produce_mix_list(sd,PRD_NEWPOISON,skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case GC_ANTIDOTE:			/* アンチドート */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_calc_pc_stop_begin(bl);

		status_change_end(bl, SC_TOXIN, -1);
		status_change_end(bl, SC_PARALIZE, -1);
		status_change_end(bl, SC_VENOMBLEED, -1);
		status_change_end(bl, SC_MAGICMUSHROOM, -1);
		status_change_end(bl, SC_DEATHHURT, -1);
		status_change_end(bl, SC_PYREXIA, -1);
		status_change_end(bl, SC_OBLIVIONCURSE, -1);
		status_change_end(bl, SC_LEECHEND, -1);

		status_calc_pc_stop_end(bl);
		break;
	case GC_POISONINGWEAPON:	/* ポイズニングウェポン */
		if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_poison_list(sd,skilllv);
		}
		break;
	case AB_ANCILLA:			/* アンシラ */
		if(sd) {
			struct item item_tmp;

			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			memset(&item_tmp,0,sizeof(item_tmp));
			item_tmp.nameid   = 12333;
			item_tmp.identify = 1;
			pc_additem(sd,&item_tmp,1,false);
		}
		break;
	case AB_CLEMENTIA:		/* クレメンティア */
	case AB_CANTO:			/* カントキャンディダス */
	case AB_CHEAL:			/* コルセオヒール */
		if(sd == NULL)
			break;
		if(flag&1 || sd->status.party_id == 0) {
			int lv = 0;

			switch(skillid) {
				case AB_CLEMENTIA: lv = pc_checkskill(sd,AL_BLESSING); break;
				case AB_CANTO:     lv = pc_checkskill(sd,AL_INCAGI);   break;
				case AB_CHEAL:     lv = pc_checkskill(sd,AL_HEAL);     break;
			}
			lv = (lv < 1)? 1: lv;

			if(skillid == AB_CHEAL) {
				int heal;

				heal = skill_fix_heal(&sd->bl, bl, skillid, skill_calc_heal(&sd->bl, lv));
				if(sd->status.party_id == 0)
					skill_area_temp[0] = 1;
				heal += heal * skill_area_temp[0] * 25 / 1000;

				if(dstsd) {
					if(dstsd->sc.data[SC_BERSERK].timer != -1)
						heal = 0; 	// バーサーク中はヒール０

					if(pc_isgear(dstsd))
						heal = 0; 	// 魔道ギア搭乗中はヒール０
				}

				clif_skill_nodamage(&sd->bl,bl,skillid,heal,1);
				battle_heal(&sd->bl,bl,heal,0,0);
			} else {
				clif_skill_nodamage(&sd->bl,bl,skillid,skilllv,1);
				status_change_start(bl,GetSkillStatusChangeTable(skillid),lv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			if(skillid == AB_CHEAL) {
				// 人数を確認
				skill_area_temp[0] = 0;

				party_foreachsamemap(skill_area_sub,
					sd,ar,
					src,skillid,skilllv,tick, flag|BCT_PARTY|1,
					skill_area_sub_count);
			}
			/* パーティ全体への処理 */
			party_foreachsamemap(skill_area_sub,
				sd,ar,
				src,skillid,skilllv,tick, flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case AB_PRAEFATIO:		/* プラエファティオ */
		if((flag&1) || sd == NULL || sd->status.party_id == 0) {
			/* 個別の処理 */
			if( dstsd && dstsd->special_state.no_magic_damage )
				break;
			if( sd == NULL || sd->status.party_id == 0 )
				skill_area_temp[0] = 1;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,skill_area_temp[0],skill_get_time(skillid,skilllv),0);	// キリエエレイソンと区別するためにval4にskillidを格納
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[0] = 0;
			/* パーティ全体への処理 */
			party_foreachsamemap(skill_area_sub,
				sd,ar,
				src,skillid,skilllv,tick, flag|BCT_PARTY|1,
				skill_area_sub_count);
			party_foreachsamemap(skill_area_sub,
				sd,ar,
				src,skillid,skilllv,tick, flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case AB_ORATIO:	/* オラティオ */
		if(flag&1) {
			if(atn_rand() % 100 < 40 + skilllv * 5)
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,bl->m,
				bl->x-ar,bl->y-ar,
				bl->x+ar,bl->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case AB_LAUDAAGNUS:		/* ラウダアグヌス */
	case AB_LAUDARAMUS:		/* ラウダラムス */
		if(sd == NULL)
			break;
		if(flag&1 || sd->status.party_id == 0) {
			/* 個別の処理 */
			if(dstsd && dstsd->special_state.no_magic_damage)
				break;
			sc = status_get_sc(bl);
			if(skillid == AB_LAUDAAGNUS && sc && (sc->data[SC_FREEZE].timer != -1 || sc->data[SC_STONE].timer != -1 || sc->data[SC_BLIND].timer != -1 ||
				sc->data[SC_HELLINFERNO].timer != -1 || sc->data[SC_FROSTMISTY].timer != -1 || sc->data[SC_DIAMONDDUST].timer != -1) && atn_rand() % 100 < skilllv * 25)
			{
				status_change_end(bl, SC_FREEZE, -1);
				status_change_end(bl, SC_STONE, -1);
				status_change_end(bl, SC_BLIND, -1);
				status_change_end(bl, SC_HELLINFERNO, -1);
				status_change_end(bl, SC_FROSTMISTY, -1);
				status_change_end(bl, SC_DIAMONDDUST, -1);
			} else if(skillid == AB_LAUDARAMUS && sc && (sc->data[SC_SILENCE].timer != -1 || sc->data[SC_SLEEP].timer != -1 || sc->data[SC_STUN].timer != -1 ||
				sc->data[SC_DEEP_SLEEP].timer != -1 || sc->data[SC_MANDRAGORA].timer != -1) && atn_rand() % 100 < skilllv * 25)
			{
				status_change_end(bl, SC_SILENCE, -1);
				status_change_end(bl, SC_SLEEP, -1);
				status_change_end(bl, SC_STUN, -1);
				status_change_end(bl, SC_DEEP_SLEEP, -1);
				status_change_end(bl, SC_MANDRAGORA, -1);
			} else {
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
			clif_skill_nodamage(&sd->bl,bl,skillid,skilllv,1);
		} else {
			/* パーティ全体への処理 */
			party_foreachsamemap(skill_area_sub,
				sd,skill_get_area(skillid,skilllv),
				src,skillid,skilllv,tick, flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case AB_RENOVATIO:			/* レノヴァティオ */
		{	// 付与と同時にヒール
			int heal = (int)((atn_bignumber)status_get_max_hp(bl) * (skilllv * 2 + 1) / 100);
			if(heal) {
				if(sc && sc->data[SC_AKAITSUKI].timer != -1)
					unit_fixdamage(bl,bl,gettick(),0,status_get_dmotion(bl),heal,0,0,0,0);
				else
					unit_heal(bl,heal,0,0,1);
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case AB_EXPIATIO:			/* エクスピアティオ */
	case AB_SECRAMENT:			/* サクラメント */
		if(battle_check_target(src,bl,BCT_NOENEMY) > 0) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		else if(sd)
			clif_skill_fail(sd,skillid,SKILLFAIL_TOTARGET,0,0);
		break;
	case AB_CLEARANCE:		/* クリアランス */
		if(atn_rand() % 100 < 60 + skilllv * 8) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_release(bl,0x200);
		} else if(sd) {
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		}
		break;
	case AB_SILENTIUM:	/* シレンティウム */
		if(flag&1) {
			if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),10000,status_get_lv(src)))
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case WL_WHITEIMPRISON:	/* ホワイトインプリズン */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		sc = status_get_sc(bl);
		if( src == bl || (sc && sc->data[SC_WHITEIMPRISON].timer == -1) && (battle_check_target(src,bl,BCT_ENEMY) > 0 && !(status_get_mode(bl)&MD_BOSS) )) {
			int rate = 0;

			if(src == bl) rate = 100;
			else if(bl->type == BL_PC) rate = 20 + skilllv * 10;
			else rate = 40 + skilllv * 10;

			if( atn_rand() % 100 < rate )
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,(src == bl)? 5000: skill_get_time(skillid,skilllv),0);
			else if(sd)
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		}
		else if(sd)
			clif_skill_fail(sd,skillid,SKILLFAIL_TOTARGET,0,0);
		break;
	case WL_SIENNAEXECRATE:	/* シエナエクセクレイト */
		if(flag&1) {
			if(!battle_check_undead(status_get_race(bl),status_get_elem_type(bl)) && atn_rand() % 10000 < status_change_rate(bl,SC_STONE,skilllv*500+4500,status_get_lv(src))) {
				status_change_pretimer(bl,SC_STONE,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case WL_STASIS:		/* ステイシス */
		if(flag&1) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case WL_TETRAVORTEX:		/* テトラボルテックス */
		{
			int summon_id[4] = { WL_TETRAVORTEX_FIRE, WL_TETRAVORTEX_WATER, WL_TETRAVORTEX_WIND, WL_TETRAVORTEX_GROUND };
			int i;
			sc = status_get_sc(src);
			if(sc) {
				int c = 0;
				for(i = 0; i < 5; i++) {
					if(sc->data[SC_SUMMONBALL1 + i].timer != -1) {
						if(c < 4) {
							switch(sc->data[SC_SUMMONBALL1 + i].val2) {
								case 1:		// サモンボールライトニング
									summon_id[c] = WL_TETRAVORTEX_WIND;
									break;
								case 2:		// サモンウォーターボール
									summon_id[c] = WL_TETRAVORTEX_WATER;
									break;
								case 3:		// サモンストーン
									summon_id[c] = WL_TETRAVORTEX_GROUND;
									break;
								default:	// サモンファイアーボール
									summon_id[c] = WL_TETRAVORTEX_FIRE;
									break;
							}
							c++;
						}
						status_change_end(src,SC_SUMMONBALL1 + i,-1);
					}
				}
			}
			for(i = 0; i < 4; i++) {
				skill_addtimerskill(src,tick + 200 * i,bl->id,0,0,summon_id[i],skilllv,0,0x0500);
			}
			status_change_pretimer(bl,GetSkillStatusChangeTable(summon_id[atn_rand()%4]),skilllv,0,0,0,skill_get_time(summon_id[atn_rand()%4],skilllv),0,tick+status_get_amotion(src));
		}
		break;
	case WL_SUMMONFB:		/* サモンファイアボール */
	case WL_SUMMONBL:		/* サモンボールライトニング */
	case WL_SUMMONWB:		/* サモンウォーターボール */
	case WL_SUMMONSTONE:	/* サモンストーン */
		sc = status_get_sc(bl);
		if(sc) {
			int i;
			for(i = 0; i < 5; i++) {
				if(sc->data[SC_SUMMONBALL1 + i].timer == -1) {
					int type = (skillid == WL_SUMMONSTONE)? 3: skillid - WL_SUMMONFB;
					clif_skill_nodamage(src,bl,skillid,skilllv,1);
					status_change_start(bl,SC_SUMMONBALL1 + i,skilllv,type,0,0,skill_get_time(skillid,skilllv),0);
					break;
				}
			}
			if(i >= 5 && sd)
				clif_skill_fail(sd,skillid,SKILLFAIL_SUMMON_OVER,0,0);
		}
		break;
	case WL_RELEASE:	/* リリース */
		sc = status_get_sc(src);
		if(sc) {
			/* 保持スペルがある場合 */
			if(sd && pc_checkskill(sd,sd->freeze_sp_skill[0]) > 0 && sc->data[SC_SPELLBOOK].timer != -1) {
				int freeze_skillid = sd->freeze_sp_skill[0];
				int freeze_skilliv = pc_checkskill(sd,freeze_skillid);

				clif_skill_nodamage(src,bl,skillid,skilllv,1);
				if(skill_get_inf(freeze_skillid)&INF_GROUND) {	// 場所指定のスキル
					skill_castend_pos2(src,bl->x,bl->y,freeze_skillid,freeze_skilliv,tick,0);
				} else if(skill_get_nk(freeze_skillid)&1){
					skill_castend_nodamage_id(src,bl,freeze_skillid,freeze_skilliv,tick,0);
				} else {
					skill_castend_damage_id(src,bl,freeze_skillid,freeze_skilliv,tick,0);
				}
				memmove(&sd->freeze_sp_skill[0],&sd->freeze_sp_skill[1],sizeof(sd->freeze_sp_skill[0])*(MAX_FREEZE_SPELL-1));
				memset(&sd->freeze_sp_skill[MAX_FREEZE_SPELL-1], 0, sizeof(sd->freeze_sp_skill[0]));
				sd->freeze_sp_slot -= skill_get_spellslot(freeze_skillid);

				// 保存スキルを全て使用
				if(sd->freeze_sp_skill[0] == 0) {
					status_change_end(src,SC_SPELLBOOK,-1);
				}
			} else {
				int i, j = 0;
				for(i = 0; i < 5; i++) {
					if(sc->data[SC_SUMMONBALL1 + i].timer != -1) {
						if(j == 0) {	// エフェクトは1発目のみ
							clif_skill_nodamage(src,bl,skillid,skilllv,1);
						}
						skill_addtimerskill(src,tick + status_get_adelay(src) * j,bl->id,0,0,WL_SUMMON_ATK_FIRE + sc->data[SC_SUMMONBALL1 + i].val2,sc->data[SC_SUMMONBALL1 + i].val1,0,(0x0f<<20)|flag);
						status_change_end(src,SC_SUMMONBALL1 + i,-1);
						j++;
						if(skilllv < 2) {		// SkillLv2は全てのサモンボールを消費
							break;
						}
					}
				}
				if(j <= 0 && sd) {	// サモンボールが無かった
					clif_skill_fail(sd,skillid,SKILLFAIL_SUMMON_NOTHING,0,0);
				}
			}
		}
		break;
	case WL_READING_SB:	/* リーディングスペルブック */
		if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_reading_sb_list(sd);
		}
		break;
	case RA_WUGMASTERY:	/* ウォーグマスタリー */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sd) {
			if(pc_isfalcon(sd) && pc_checkskill(sd,WH_HAWK_M) > 0) {	// 鷹を連れていてホークマスタリー習得済み
				if(pc_iswolf(sd)) {
					pc_setoption(sd,sd->sc.option & ~OPTION_WUG);
				} else {
					pc_setoption(sd,OPTION_WUG | OPTION_FALCON);
				}
			}
			else if(pc_iswolf(sd)) {
				pc_setoption(sd,OPTION_NOTHING);
			} else {
				pc_setoption(sd,OPTION_WUG);
			}
		}
		break;
	case RA_WUGRIDER:	/* ウォーグライダー */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sd) {
			if(pc_isfalcon(sd) && pc_checkskill(sd,WH_HAWK_M) > 0) {	// 鷹を連れていてホークマスタリー習得済み
				if(pc_iswolfmount(sd)) {
					pc_setoption(sd,OPTION_WUG | OPTION_FALCON);
				} else {
					pc_setoption(sd,OPTION_WUGRIDER | OPTION_FALCON);
				}
			}
			else if(pc_iswolfmount(sd)) {
				pc_setoption(sd,OPTION_WUG);
			} else {
				pc_setoption(sd,OPTION_WUGRIDER);
			}
		}
		break;
	case RA_WUGDASH:	/* ウォーグダッシュ */
		if(sd) {
			if(sd->sc.data[SC_WUGDASH].timer != -1) {
				status_change_end(bl,SC_WUGDASH,-1);
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
			} else {
				int dir = status_get_dir(bl);
				if(map_getcell(sd->bl.m,sd->bl.x+dirx[dir],sd->bl.y+diry[dir],CELL_CHKPASS) && map_count_oncell(sd->bl.m,sd->bl.x+dirx[dir],sd->bl.y+diry[dir],BL_PC|BL_MOB|BL_NPC) == 0)
					status_change_start(bl,SC_WUGDASH,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case NC_F_SIDESLIDE:	/* フロントサイドスライド */
	case NC_B_SIDESLIDE:	/* リアサイドスライド */
		sc = status_get_sc(src);
		if(!sc || sc->data[SC_ANKLE].timer == -1) {
			int dir, pc_dir = 0, head_dir = 0;
			int count = skill_get_blewcount(skillid,skilllv);

			dir = status_get_dir(src);

			if(skillid == NC_F_SIDESLIDE) {
				dir = (dir+4) & 0x07;
				if(dir == 0)
					dir = 8;
			}

			// 方向を保存しておいて、吹き飛ばし後に戻す
			if(sd) {
				pc_dir = sd->dir;
				head_dir = sd->head_dir;
			}

			unit_stop_walking(src,1);
			skill_blown(src,bl,count|(dir<<20)|SAB_REVERSEBLOW|SAB_NODAMAGE|SAB_NOPATHSTOP|SAB_NOTKNOCK);
			clif_blown(src,src->x,src->y);
			clif_skill_nodamage(src,src,skillid,skilllv,1);

			if(sd)
				pc_setdir(sd, pc_dir, head_dir);
		}
		break;
	case NC_EMERGENCYCOOL:	/* エマージェンシークール */
		sc = status_get_sc(src);
		if(sc && sc->data[SC_OVERHEAT_LIMITPOINT].timer != -1) {
			int heat = sc->data[SC_OVERHEAT_LIMITPOINT].val1;
			heat -= 45;
			if(heat > 0)
				sc->data[SC_OVERHEAT_LIMITPOINT].val1 = heat;
			else
				status_change_end(bl, SC_OVERHEAT_LIMITPOINT, -1);
			// オーバーヒートの終了判定はstatus_change_timerで判定
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		break;
	case NC_INFRAREDSCAN:	/* インフラレッドスキャン */
		if(flag&1) {
			skill_detect(bl);		// ディティクト効果
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case NC_ANALYZE:		/* アナライズ */
		if(atn_rand() % 10000 < 2000 + (skilllv - 1) * 4000) {
			clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else if(sd) {
			clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
		}
		break;
	case NC_MAGNETICFIELD:	/* マグネティックフィールド */
		if(flag&1) {
			sc = status_get_sc(bl);
			if(!sc || (sc->data[SC_HOVERING].timer == -1 && sc->data[SC_MAGNETICFIELD].timer == -1)) {
				unit_stop_walking(bl,1);
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			sc = status_get_sc(src);
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			// ホバーリング状態じゃなければ自信にも状態異常
			if(!sc || (sc->data[SC_HOVERING].timer == -1 && sc->data[SC_MAGNETICFIELD].timer == -1)) {
				status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case NC_NEUTRALBARRIER:		/* ニュートラルバリアー */
	case NC_STEALTHFIELD:		/* ステルスフィールド */
		{
			struct skill_unit_group *sg;
			int type = GetSkillStatusChangeTable(skillid);
			if(type < 0)
				break;
			sc = status_get_sc(src);
			if(sc && sc->data[type].timer != -1) {
				status_change_end(src,type,-1);
			}
			sg = skill_unitsetting(src,skillid,skilllv,src->x,src->y,0);
			if(sg) {
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
				status_change_start(bl,type,skilllv,0,0,sg->bl.id,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case NC_REPAIR:			/* リペア */
		if(dstsd && pc_isgear(dstsd)) {
			static const int repair[] = { 20, 23, 35, 40, 50 };
			int heal = (int)((atn_bignumber)status_get_max_hp(bl) * ((skilllv > 5)? repair[4]: repair[skilllv-1]) / 100);
			clif_skill_nodamage(src,bl,AL_HEAL,heal,1);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			battle_heal(NULL,bl,heal,0,0);
		} else if(sd) {
			clif_skill_fail(sd,skillid,SKILLFAIL_TOTARGET,0,0);
		}
		break;
	case SC_AUTOSHADOWSPELL:	/* オートシャドウスペル */
		if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_autoshadowspell(sd,skilllv);
		}
		break;
	case SC_SHADOWFORM:			/* シャドウフォーム */
		if(sd) {
			if(dstsd && dstsd->shadowform_id == 0) {
				if(sd->bl.id == dstsd->bl.id ||
				   ((!map[src->m].flag.pvp && !map[src->m].flag.gvg) &&
				    (sd->status.party_id <= 0 || dstsd->status.party_id <= 0 ||
				    sd->status.party_id != dstsd->status.party_id)))
				{
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
					break;
				}
				clif_skill_nodamage(&sd->bl,&dstsd->bl,skillid,skilllv,1);
				status_change_start(&sd->bl,GetSkillStatusChangeTable(skillid),skilllv,dstsd->bl.id,0,0,skill_get_time(skillid,skilllv),0 );
				dstsd->shadowform_id = sd->bl.id;
			} else {
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
			}
		}
		break;
	case SC_BODYPAINT:	/* ボディペインティング */
		if(flag&1) {
			if(bl->id != skill_area_temp[1]) {
				skill_detect(bl);		// ディティクト効果
				if(atn_rand() % 10000 < status_change_rate(bl,SC_BLIND,300+200*skilllv,status_get_lv(src)))
					status_change_pretimer(bl,SC_BLIND,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
				if(atn_rand() % 10000 < 500 * skilllv)
					status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* スキルエフェクト表示 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			skill_area_temp[1] = src->id;
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SC_ENERVATION:		/* マスカレード：エナベーション */
	case SC_GROOMY:			/* マスカレード：グルーミー */
	case SC_IGNORANCE:		/* マスカレード：イグノアランス */
	case SC_LAZINESS:		/* マスカレード：レイジネス */
	case SC_UNLUCKY:		/* マスカレード：アンラッキー */
	case SC_WEAKNESS:		/* マスカレード：ウィークネス */
		{
			int mask_fix;

			sc = status_get_sc(bl);
			if(sc && sc->data[GetSkillStatusChangeTable(skillid)].timer != -1) {
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				break;
			}

			mask_fix = (status_get_dex(src) + status_get_lv(src)) - (status_get_agi(bl) - status_get_lv(bl));
			if(mask_fix < 0)
				mask_fix = 0;

			if(atn_rand()%100 >= 5 + 2 * skilllv + mask_fix / 5) {
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				break;
			}

			// スキルごとの個別処理
			switch(skillid) {
			case SC_ENERVATION:	/* マスカレード：エナベーション */
				if(dstsd)
					pc_delspiritball(dstsd,dstsd->spiritball.num,0);	// 気弾を削除
				break;
			case SC_GROOMY:		/* マスカレード：グルーミー */
				if(dstsd) {
					pc_setoption(dstsd,(dstsd->sc.option & ~(OPTION_CARTMASK | OPTION_FALCON |
						OPTION_PECO | OPTION_DRAGONMASK | OPTION_WUG | OPTION_WUGRIDER)));	// カートなどの付属品を削除
					if(dstsd->pd) pet_return_egg(dstsd);
					if(dstsd->hd) homun_return_embryo(dstsd);
					status_change_end(bl,SC_ALL_RIDING,-1);
					status_change_end(bl,SC_ON_PUSH_CART,-1);
				}
				break;
			case SC_IGNORANCE:		/* マスカレード：イグノアランス */
				{
					int sp;

					if(dstsd) {
						sp = 100 * skilllv;
						if(dstsd->status.sp < sp)
							sp = dstsd->status.sp;
						dstsd->status.sp -= sp;
						clif_updatestatus(dstsd,SP_SP);
					}
					else
					{
						sp = status_get_lv(bl);
					}

					if(sd) {
						sd->status.sp += sp;
						if(sd->status.sp > sd->status.max_sp)
							sd->status.sp = sd->status.max_sp;
						clif_updatestatus(sd,SP_SP);
					}
				}
				break;
			case SC_WEAKNESS:		/* マスカレード：ウィークネス */
				if(dstsd) {
					int i;

					for(i=0; i<MAX_INVENTORY; i++) {
						if(dstsd->status.inventory[i].equip & LOC_RLARM) {
							pc_unequipitem(dstsd,i,0);	// 武器と盾を解除
						}
					}
				}
				break;
			default:
				break;
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SC_STRIPACCESSARY:		/* ストリップアクセサリー */
		{
			int strip_fix;

			sc = status_get_sc(bl);
			if(sc && sc->data[GetSkillStatusChangeTable(skillid)].timer != -1) {
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				break;
			}

			strip_fix = status_get_dex(src) - status_get_dex(bl);
			if(strip_fix < 0)
				strip_fix = 0;
			if(atn_rand()%100 >= 12 + 2 * skilllv + ((strip_fix)? strip_fix / 5: 0)) {
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				break;
			}

			if(dstsd) {
				int i;
				for(i=0; i<MAX_INVENTORY; i++) {
					if(dstsd->status.inventory[i].equip && (dstsd->status.inventory[i].equip & LOC_RLACCESSORY)) {
						pc_unequipitem(dstsd,i,0);
					}
				}
			}
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case SC_FEINTBOMB:		/* フェイントボム */
		clif_skill_nodamage(src,src,skillid,skilllv,1);
		skill_unitsetting(src,skillid,skilllv,src->x,src->y,0);
		sc = status_get_sc(src);
		if(!sc || sc->data[SC_ANKLE].timer == -1) {
			// バックステップ
			int dir = 0, head_dir = 0;
			int count = skill_get_blewcount(skillid,skilllv);

			if(sd) {
				dir = sd->dir;
				head_dir = sd->head_dir;
			}
			unit_stop_walking(src,1);
			skill_blown(src,bl,count|SAB_REVERSEBLOW|SAB_NODAMAGE|SAB_NOPATHSTOP|SAB_NOTKNOCK);
			if(sd)
				pc_setdir(sd, dir, head_dir);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		}
		break;
	case SC_ESCAPE:			/* エスケープ */
		clif_skill_nodamage(src,src,skillid,skilllv,1);
		skill_unitsetting(src,skillid,skilllv,src->x,src->y,0);
		sc = status_get_sc(src);
		if(!sc || sc->data[SC_ANKLE].timer == -1) {
			// バックステップ
			int dir = 0, head_dir = 0;
			int count = skill_get_blewcount(skillid,skilllv);

			if(sd) {
				dir = sd->dir;
				head_dir = sd->head_dir;
			}
			unit_stop_walking(src,1);
			skill_blown(src,bl,count|SAB_REVERSEBLOW|SAB_NODAMAGE|SAB_NOPATHSTOP|SAB_NOTKNOCK);
			if(sd)
				pc_setdir(sd, dir, head_dir);
		}
		break;
	case LG_TRAMPLE:		/* トランプル */
		{
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			map_foreachinarea(skill_trample,bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_SKILL,src,skilllv);
		}
		break;
	case LG_SHIELDSPELL:		/* シールドスペル */
		if(flag&1) {
			if(atn_rand() % 10000 < status_change_rate(bl,SC_SILENCE,10000,status_get_lv(src))) {
				int time = 20000;
				if(sd) {
					int idx = sd->equip_index[EQUIP_INDEX_LARM];
					if(idx >= 0 && sd->inventory_data[idx] && itemdb_isarmor(sd->inventory_data[idx]->nameid)) {
						time = time * sd->inventory_data[idx]->mdef;
					}
				}
				status_change_pretimer(bl,SC_SILENCE,1,0,0,0,time,0,tick+status_get_amotion(src));
			}
		}
		else if(sd) {
			int idx = sd->equip_index[EQUIP_INDEX_LARM];
			if(idx >= 0 && sd->inventory_data[idx] && itemdb_isarmor(sd->inventory_data[idx]->nameid)) {
				int rate,val;
				switch(skilllv) {
				case 1:
#ifdef PRE_RENEWAL
					val = sd->inventory_data[idx]->def * 10;
#else
					val = sd->inventory_data[idx]->def;
#endif
					if(atn_rand()%100 >= val) {
						clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
						break;
					}

					clif_skill_nodamage(src,bl,skillid,skilllv,1);
					rate = atn_rand()%100;
					if(rate < 50) {			// 範囲物理攻撃
						int ar = (val>80? 3: (val>40? 2: 1));
						skill_area_temp[1] = src->id;
						map_foreachinarea(skill_area_sub,
							src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
							src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
							skill_castend_damage_id);
					}
					else if(rate < 75) {	// 物理攻撃反射
						status_change_start(bl,SC_SHIELDSPELL_DEF,skilllv,1,val/10,0,val*2000,0);
					}
					else {					// 攻撃力増加
						status_change_start(bl,SC_SHIELDSPELL_DEF,skilllv,2,val,0,val*3000,0);
					}
					break;
				case 2:
					val = sd->inventory_data[idx]->mdef;
					if(atn_rand()%100 >= val * 10) {
						clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
						break;
					}

					clif_skill_nodamage(src,bl,skillid,skilllv,1);
					rate = atn_rand()%100;
					if(rate < 30) {			// 範囲魔法攻撃
						int ar = val / 3;
						skill_area_temp[1] = src->id;
						map_foreachinarea(skill_area_sub,
							src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
							src,skillid,skilllv,tick, flag|BCT_ENEMY|2,
							skill_castend_damage_id);
					}
					else if(rate < 60) {	// 沈黙攻撃
						int ar = val / 3;
						skill_area_temp[1] = src->id;
						map_foreachinarea(skill_area_sub,
							src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,(BL_CHAR|BL_SKILL),
							src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
							skill_castend_nodamage_id);
					}
					else {					// マグニフィカート
						status_change_start(bl,SC_SHIELDSPELL_MDEF,skilllv,0,0,0,val*30000,0);
					}
					break;
				case 3:
					val = sd->status.inventory[idx].refine;
					if(atn_rand()%100 >= val * 10) {
						clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
						break;
					}

					clif_skill_nodamage(src,bl,skillid,skilllv,1);
					rate = atn_rand()%100;
					if(rate < 50) {			// HP回復
						int heal = sd->status.max_hp * (1 + sd->status.base_level / 10 + val) / 100;
						clif_skill_nodamage(src,bl,AL_HEAL,heal,1);
						pc_heal(sd,heal,0,0,0);
					}
					else if(rate < 75) {	// 鎧破壊
						status_change_start(bl,SC_SHIELDSPELL_REF,skilllv,1,val*10,0,val*30000,0);
					}
					else {					// DEF増加
						status_change_start(bl,SC_SHIELDSPELL_REF,skilllv,2,val*10*sd->status.base_level/100,0,val*20000,0);
					}
					break;
				}
			}
		}
		break;
	case LG_BANDING:			/* バンディング */
		sc = status_get_sc(src);
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sc && sc->data[GetSkillStatusChangeTable(skillid)].timer != -1) {
			status_change_end(src,GetSkillStatusChangeTable(skillid),-1);
		}
		else {
			struct skill_unit_group *sg = skill_unitsetting(src,skillid,skilllv,src->x,src->y,0);
			if(sg) {
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,1,0,sg->bl.id,0,0);
			}
		}
		break;
	case LG_PIETY:		/* パイエティ */
		if(flag&1) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_PC,
				src,skillid,skilllv,tick, flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case LG_INSPIRATION:		/* インスピレーション */
		if(sd) {
			atn_bignumber loss_exp = pc_nextbaseexp(sd) / 1000;
			if(loss_exp > 0) {
				sd->status.base_exp -= loss_exp;
				if(sd->status.base_exp < 0)
					sd->status.base_exp = 0;
				clif_updatestatus(sd,SP_BASEEXP);
			}
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_release(src,0x04);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SR_CURSEDCIRCLE:		/* 呪縛陣 */
	case NPC_SR_CURSEDCIRCLE:		/* M呪縛陣 */
		if(flag&1) {
			if(!(status_get_mode(bl)&MD_BOSS)) {
				if(sd) {
					if(sd->spiritball.num > 0) {
						pc_delspiritball(sd,1,0);
						status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
					}
				} else {
					status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
				}
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			if(skillid==SR_CURSEDCIRCLE)
				status_change_start(bl,SC_CURSEDCIRCLE_USER,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SR_RAISINGDRAGON:		/* 潜龍昇天 */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		if(sd) {
			if(pc_checkskill(sd,MO_EXPLOSIONSPIRITS) > 0)		// 爆裂波動の習得レベルで発動
				status_change_start(bl,SC_EXPLOSIONSPIRITS,pc_checkskill(sd,MO_EXPLOSIONSPIRITS),0,0,0,skill_get_time(skillid,skilllv),0);
			pc_addspiritball(sd,skill_get_time2(skillid,skilllv),MAX_SPIRITBALL);
		}
		else
			status_change_start(bl,SC_EXPLOSIONSPIRITS,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SR_ASSIMILATEPOWER:	/* 吸気功 */
		if(flag&1) {
			int val = 0;
			if(dstsd && dstsd->spiritball.num > 0) {
				val += dstsd->spiritball.num;
				pc_delspiritball(dstsd,dstsd->spiritball.num,0);
			}
			if(sd) {
				int sp = sd->status.max_sp * val / 100;
				if(sd->status.sp + sp > sd->status.max_sp)
					sp = sd->status.max_sp - sd->status.sp;
				if(sp > 0) {
					sd->status.sp += sp;
					clif_updatestatus(sd,SP_SP);
				}
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			/* スキルエフェクト表示 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_skill_damage(src, src, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			map_foreachinarea(skill_area_sub,
				src->m,src->x-ar,src->y-ar,src->x+ar,src->y+ar,BL_PC,
				src,skillid,skilllv,tick, flag|BCT_ALL|1,
				skill_castend_nodamage_id);
		}
		break;
	case SR_POWERVELOCITY:		/* 全気注入 */
		if(sd && dstsd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			pc_addspiritball(dstsd,skill_get_time(skillid,skilllv),sd->spiritball.num);
			pc_delspiritball(sd,sd->spiritball.num,0);
		}
		break;
	case SR_GENTLETOUCH_CURE:	/* 点穴 -快- */
		{
			int heal = (int)(skilllv * 120 + (atn_bignumber)status_get_max_hp(bl) * (2 + skilllv) / 100);
			battle_heal(NULL,bl,heal,0,0);
			if(atn_rand()%100 < skilllv * 5 + status_get_dex(src) / 2) {
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
				status_calc_pc_stop_begin(bl);

				status_change_end(bl, SC_STONE, -1);
				status_change_end(bl, SC_FREEZE, -1);
				status_change_end(bl, SC_STUN, -1);
				status_change_end(bl, SC_POISON, -1);
				status_change_end(bl, SC_SILENCE, -1);
				status_change_end(bl, SC_BLIND, -1);
				status_change_end(bl, SC_HALLUCINATION, -1);
				status_change_end(bl, SC_HELLINFERNO, -1);
				status_change_end(bl, SC_FROSTMISTY, -1);
				status_change_end(bl, SC_TOXIN, -1);
				status_change_end(bl, SC_PARALIZE, -1);
				status_change_end(bl, SC_VENOMBLEED, -1);
				status_change_end(bl, SC_MAGICMUSHROOM, -1);
				status_change_end(bl, SC_DEATHHURT, -1);
				status_change_end(bl, SC_PYREXIA, -1);
				status_change_end(bl, SC_OBLIVIONCURSE, -1);
				status_change_end(bl, SC_LEECHEND, -1);

				status_calc_pc_stop_end(bl);
			}
		}
		break;
	case SR_GENTLETOUCH_CHANGE:		/* 点穴 -反- */
		{
			int val1 = (status_get_str(src) / 2 + status_get_dex(src) / 4) * skilllv / 5;
			int val2 = (200 / (status_get_int(src)>1? status_get_int(src): 1) ) * skilllv;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,val1,val2>0? val2: 0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SR_GENTLETOUCH_REVITALIZE:	/* 点穴 -活- */
		{
			int val = status_get_vit(src) / 2 * skilllv;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,val,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SR_FLASHCOMBO:		/* 閃光連撃 */
		{
			int combo_id[4] = { SR_DRAGONCOMBO,SR_FALLENEMPIRE,SR_TIGERCANNON,SR_SKYNETBLOW };
			int combo_lv[4] = { 10,5,10,5 };
			int delay[4] = { 0,250,500,2000 };
			int i;
			if(sd)
				sd->ud.attackabletime = sd->item_delay_tick = sd->ud.canact_tick = tick + 2000;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			for(i = 0; i < 4; i++) {
				skill_addtimerskill(src,tick + delay[i],bl->id,0,0,
					combo_id[i],(sd ? pc_checkskill(sd,combo_id[i]) : combo_lv[i]),BF_WEAPON,flag|1);
			}
		}
		break;
	case WA_SWING_DANCE:		/* スイングダンス */
	case WA_SYMPHONY_OF_LOVE:	/* 恋人たちの為のシンフォニー */
	case WA_MOONLIT_SERENADE:	/* 月明かりのセレナーデ */
	case MI_RUSH_WINDMILL:		/* 風車に向かって突撃 */
	case MI_ECHOSONG:			/* エコーの歌 */
		if((flag&1) || sd == NULL || sd->status.party_id == 0) {
			/* 個別の処理 */
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,((sd)? sd->status.job_level: 0),((sd)? pc_checkskill(sd,WM_LESSON): 0),0,skill_get_time(skillid,skilllv),0);
		} else {
			/* パーティ全体への処理 */
			party_foreachsamemap(skill_area_sub,
				sd,skill_get_area(skillid,skilllv),
				src,skillid,skilllv,tick, flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case MI_HARMONIZE:			/* ハーモナイズ */
		{
			int param = 5 + skilllv * 5;

			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,param,0,0,skill_get_time(skillid,skilllv),0);
			if(src != bl)
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,param,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case WM_VOICEOFSIREN:	/* セイレーンの声 */
		if(flag&1) {
			if(atn_rand() % 10000 < 2000 + 1000 * skilllv) {
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,src->id,0,0,skill_get_time(skillid,skilllv),0);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case WM_DEADHILLHERE:		/* 生死の境で */
		if(dstsd) {
			if(map[bl->m].flag.pvp && dstsd->pvp_point < 0)	// PVPで復活不可能状態
				break;
			if(!unit_isdead(&dstsd->bl))			// 死亡判定
				break;
			if(atn_rand() % 10000 >= 9000 + 200 * skilllv)
				break;
			if(dstsd->sc.data[SC_HELLPOWER].timer != -1)		// ヘルパワー状態は蘇生不可
				break;
			if(dstsd->special_state.no_magic_damage)
				break;

			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(dstsd->special_state.restart_full_recover) {	// オシリスカード
				dstsd->status.hp = dstsd->status.max_hp;
				dstsd->status.sp = dstsd->status.max_sp;
			}
			else {
				if(dstsd->status.sp > 0) {
					dstsd->status.hp = dstsd->status.sp;
					dstsd->status.sp -= dstsd->status.sp * (50 - skilllv * 10) / 100;
				}
				else
					dstsd->status.hp = 1;
			}

			clif_updatestatus(dstsd,SP_HP);
			clif_updatestatus(dstsd,SP_SP);
			pc_setstand(dstsd);
			if(battle_config.pc_invincible_time > 0)
				pc_setinvincibletimer(dstsd,battle_config.pc_invincible_time);
			clif_resurrection(&dstsd->bl,1);
		}
		break;
	case WM_LULLABY_DEEPSLEEP:	/* 安らぎの子守唄 */
		if(flag&1) {
			if(bl->id != skill_area_temp[0]) {
				if(atn_rand() % 10000 < status_change_rate(bl,SC_DEEP_SLEEP,400 * skilllv,status_get_lv(src)))
					status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[0] = src->id;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ALL|1,
				skill_castend_nodamage_id);
		}
		break;
	case WM_SIRCLEOFNATURE:		/* 循環する自然の音 */
		if(flag&1) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_PC,
				src,skillid,skilllv,tick,flag|BCT_ALL|1,
				skill_castend_nodamage_id);
		}
		break;
	case WM_RANDOMIZESPELL:		/* 不確定要素の言語 */
		if(sd) {
			int rand_skillid = skill_searchrandomid(2);
			int rand_skilllv = skill_get_max(rand_skillid);

			if(rand_skilllv > skilllv + 5)
				rand_skilllv = skilllv + 5;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			sd->skill_item.id      = rand_skillid;
			sd->skill_item.lv      = rand_skilllv;
			sd->skill_item.flag    = 1;		// 使用条件判定する
			clif_item_skill(sd, rand_skillid, rand_skilllv, "");
		}
		break;
	case WM_SONG_OF_MANA:		/* マナの歌 */
	case WM_DANCE_WITH_WUG:		/* ダンスウィズウォーグ */
		if(flag&1) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,skill_area_temp[0],0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[0] = 0;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			party_foreachsamemap(skill_area_sub,
				sd,PT_AREA_SIZE,
				src,skillid,skilllv,tick, flag|BCT_PARTY|1,
				skill_partner_count);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case WM_SATURDAY_NIGHT_FEVER:		/* フライデーナイトフィーバー */
		if(flag&1) {
			if(skill_area_temp[0] >= 7) {
				int dmg = 9999;
				if(status_get_max_hp(src) < dmg)
					dmg = status_get_max_hp(src);
				clif_damage(bl,bl,tick,0,0,dmg,0,9,0,0);
				battle_damage(bl,bl,dmg,0,0,0);
			}
			if(!unit_isdead(bl))
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[0] = 0;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
					bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_PC,
					src,skillid,skilllv,tick,flag|BCT_ALL|1,
					skill_partner_count);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_PC,
				src,skillid,skilllv,tick,flag|BCT_ALL|1,
				skill_castend_nodamage_id);
		}
		break;
	case WM_LERADS_DEW:			/* レーラズの霧 */
		if(flag&1) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case WM_BEYOND_OF_WARCRY:	/* ビヨンドオブウォークライ */
	case WM_MELODYOFSINK:		/* メロディーオブシンク */
		if(flag&1) {
			int rate = 1500 + 500 * skilllv;
			if(skill_area_temp[0] >= 3 && skill_area_temp[0] <= 7)
				rate += 5 * (skill_area_temp[0]-2);
			if(atn_rand() % 10000 < rate) {
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,skill_area_temp[0],0,0,skill_get_time(skillid,skilllv),0);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[0] = 0;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			party_foreachsamemap(skill_area_sub,
				sd,PT_AREA_SIZE,
				src,skillid,skilllv,tick, flag|BCT_PARTY|1,
				skill_partner_count);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case WM_UNLIMITED_HUMMING_VOICE:	/* エンドレスハミングボイス */
		if(flag&1) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case WM_FRIGG_SONG:		/* フリッグの歌 */
		if(flag&1) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			// 通常マップは全プレイヤー、対人MAPではPARTYのみ
			if(!map[src->m].flag.pvp && !map[src->m].flag.gvg && !map[src->m].flag.pk) {
				map_foreachinarea(skill_area_sub,
					bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
					src,skillid,skilllv,tick,flag|BCT_NOENEMY|1,
					skill_castend_nodamage_id);
			}
			else {
				map_foreachinarea(skill_area_sub,
					bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
					src,skillid,skilllv,tick,flag|BCT_PARTY|1,
					skill_castend_nodamage_id);
			}
		}
		break;
	case SO_FIREWALK:		/* ファイアーウォーク */
	case SO_ELECTRICWALK:	/* エレクトリックウォーク */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,skillid,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	case SO_SPELLFIST:		/* スペルフィスト */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		unit_skillcastcancel(src,1);
		if(sd) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,sd->skill_used.id,sd->skill_used.lv,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SO_STRIKING:		/* ストライキング */
		{
			int val = 8 + skilllv * 2;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(dstsd) {
				int idx = dstsd->equip_index[EQUIP_INDEX_RARM];
				if(idx >= 0 && dstsd->inventory_data[idx])
					val = val * dstsd->inventory_data[idx]->wlv;
			}
			if(sd) {
				val += pc_checkskill(sd,SA_FLAMELAUNCHER) * 5;
				val += pc_checkskill(sd,SA_FROSTWEAPON) * 5;
				val += pc_checkskill(sd,SA_LIGHTNINGLOADER) * 5;
				val += pc_checkskill(sd,SA_SEISMICWEAPON) * 5;
			}
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,val,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SO_ARRULLO:	/* アルージョ */
		if(flag&1) {
			if(atn_rand() % 10000 < status_change_rate(bl,GetSkillStatusChangeTable(skillid),skilllv*500+4500,status_get_lv(src))) {
				status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SO_EL_CONTROL:		/* エレメンタルコントロール */
		if(sd && sd->eld) {
			int mode;

			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(skilllv == 4) {
				elem_delete_data(sd);
				break;
			}
			switch(skilllv) {
				case 1:  mode = ELMODE_PASSIVE;   break;
				case 2:  mode = ELMODE_DEFENSIVE; break;
				case 3:  mode = ELMODE_OFFENSIVE; break;
				default: mode = ELMODE_WAIT;      break;
			}
			elem_change_mode(sd->eld, mode);
		}
		break;
	case SO_SUMMON_AGNI:	/* サモンアグニ */
	case SO_SUMMON_AQUA:	/* サモンアクア */
	case SO_SUMMON_VENTUS:	/* サモンベントス */
	case SO_SUMMON_TERA:	/* サモンテラ */
		if(sd) {
			int elem_id = 0;
			int type = GetSkillStatusChangeTable(skillid);
			if(type < 0)
				break;

			switch(skillid) {
				case SO_SUMMON_AGNI:   elem_id = 2114 + skilllv - 1; break;
				case SO_SUMMON_AQUA:   elem_id = 2117 + skilllv - 1; break;
				case SO_SUMMON_VENTUS: elem_id = 2120 + skilllv - 1; break;
				case SO_SUMMON_TERA:   elem_id = 2123 + skilllv - 1; break;
			}

			// 精霊召喚中の場合は一旦解除する
			if(sd->sc.data[type].timer != -1)
				status_change_end(src,type,-1);
			if(sd->sc.data[SC_SUMMON_ELEMENTAL_ARDOR].timer != -1)
				status_change_end(src,SC_SUMMON_ELEMENTAL_ARDOR,-1);
			if(sd->sc.data[SC_SUMMON_ELEMENTAL_DILUVIO].timer != -1)
				status_change_end(src,SC_SUMMON_ELEMENTAL_DILUVIO,-1);
			if(sd->sc.data[SC_SUMMON_ELEMENTAL_PROCELLA].timer != -1)
				status_change_end(src,SC_SUMMON_ELEMENTAL_PROCELLA,-1);
			if(sd->sc.data[SC_SUMMON_ELEMENTAL_TERREMOTUS].timer != -1)
				status_change_end(src,SC_SUMMON_ELEMENTAL_TERREMOTUS,-1);
			if(sd->sc.data[SC_SUMMON_ELEMENTAL_SERPENS].timer != -1)
				status_change_end(src,SC_SUMMON_ELEMENTAL_SERPENS,-1);

			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			elem_create_data(sd,elem_id,skill_get_time(skillid,skilllv)/1000);
			status_change_start(src,type,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SO_EL_ACTION:	/* エレメンタルアクション */
		if(sd && sd->eld) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			elem_skilluse(sd->eld, bl, ELMODE_OFFENSIVE);
		}
		break;
	case SO_EL_ANALYSIS:	/* エレメンタルアナライシス */
		if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_convertitem(sd,skillid,skilllv);
		}
		break;
	case SO_EL_CURE:	/* エレメンタルキュアー */
		if(sd && sd->eld) {
			int hp = sd->status.max_hp * 10 / 100;
			int sp = sd->status.max_sp * 10 / 100;
			if(sd->status.hp >= hp && sd->status.sp >= sp) {
				int hp2 = sd->eld->max_hp * 10 / 100;
				int sp2 = sd->eld->max_sp * 10 / 100;

				sd->status.hp -= hp;
				sd->status.sp -= sp;
				clif_updatestatus(sd,SP_HP);
				clif_updatestatus(sd,SP_SP);

				clif_skill_nodamage(src,bl,skillid,skilllv,1);
				elem_heal(sd->eld,hp2,sp2);
			}
		}
		break;
	case SO_ELEMENTAL_SHIELD:	/* エレメンタルシールド */
		if(flag&1 || sd == NULL) {
			if(unit_isdead(bl))			// 死亡判定
				break;
			skill_unitsetting(src,MG_SAFETYWALL,skilllv + 5,bl->x,bl->y,0);
			skill_unitsetting(src,AL_PNEUMA,1,bl->x,bl->y,0);
		} else if(sd) {
			if(!sd->eld)
				break;
			elem_delete_data(sd);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(sd->status.party_id)
				party_foreachsamemap(skill_area_sub,sd,5,src,skillid,skilllv,tick,flag|BCT_PARTY|1,skill_castend_nodamage_id);
			else {
				skill_unitsetting(src,MG_SAFETYWALL,skilllv + 5,src->x,src->y,0);
				skill_unitsetting(src,AL_PNEUMA,1,src->x,src->y,0);
			}
		}
		break;
	case GN_BLOOD_SUCKER:		/* ブラッドサッカー */
	case GN_SPORE_EXPLOSION:	/* スポアエクスプロージョン */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,skillid,src->id,0,skill_get_time(skillid,skilllv),0);
		break;
	case LG_KINGS_GRACE:	/* キングスグレイス */
	case GN_WALLOFTHORN:	/* ソーンウォール */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_unitsetting(src,skillid,skilllv,bl->x,bl->y,0);
		break;
	case GN_MANDRAGORA:		/* ハウリングオブマンドラゴラ */
		if(flag&1) {
			if(atn_rand() % 10000 < 2500 + 1000 * skilllv) {
				if(dstsd) {
					int sp = dstsd->status.max_sp * (25 + skilllv * 5) / 100;
					if(dstsd->status.sp < sp)
						sp = dstsd->status.sp;
					dstsd->status.sp -= sp;
					clif_updatestatus(dstsd,SP_SP);
				}
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_CHAR,
				src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case GN_SLINGITEM:		/* スリングアイテム */
		if(sd) {
			int idx = sd->equip_index[EQUIP_INDEX_ARROW];
			if(idx >= 0 && sd->inventory_data[idx]) {
				int nameid = sd->inventory_data[idx]->nameid;
				int cost = skill_get_arrow_cost(skillid,skilllv);
				if(nameid <= 0)
					break;
				if(cost > 0 && !battle_delarrow(sd, cost, skillid))
					break;
				clif_skill_nodamage(src,bl,skillid,skilllv,1);

				// 投擲物によって効果決定
				switch(nameid) {
				case 13260:		// リンゴ爆弾
				case 13261:		// ココナッツ爆弾
				case 13262:		// メロン爆弾
				case 13264:		// バナナ爆弾
				case 13265:		// 黒い塊
				case 13266:		// 硬くて黒い塊
				case 13267:		// とても硬い塊
					if(battle_check_target(src,bl,BCT_ENEMY) > 0)
						battle_skill_attack(BF_WEAPON,src,src,bl,GN_SLINGITEM_RANGEMELEEATK,nameid - 13260,tick,flag|(0x0f<<20));
					break;
				case 13263:		// パイナップル爆弾
					if(battle_check_target(src,bl,BCT_ENEMY) > 0) {
						int ar = skill_get_area(GN_SLINGITEM_RANGEMELEEATK,skilllv);
						map_foreachinarea(skill_area_sub,
							bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,(BL_CHAR|BL_SKILL),
							src,GN_SLINGITEM_RANGEMELEEATK,3,tick,flag|BCT_ENEMY|(0x0f<<20),
							skill_castend_damage_id);
					}
					break;
				default:
					if(dstsd) {
						struct item_data *item = itemdb_search(nameid);
						if(item->use_script)
							run_script(item->use_script,0,dstsd->bl.id,0);
					}
					break;
				}
			}
		}
		break;
	case GN_CHANGEMATERIAL:	/* チェンジマテリアル */
		if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_convertitem(sd,skillid,0);
		}
		break;
	case GN_MIX_COOKING:	/* ミックスクッキング */
		if(sd) {
			clif_making_list(sd,PRD_MIX_COOKING,skillid,skilllv,4);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case GN_MAKEBOMB:		/* 爆弾製造 */
		if(sd) {
			clif_making_list(sd,PRD_MAKEBOMB,skillid,skilllv,5);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case GN_S_PHARMACY:		/* スペシャルファーマシー */
		if(sd) {
			clif_making_list(sd,PRD_S_PHARMACY,skillid,skilllv,6);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case KO_ZANZOU:		/* 幻術 -影武者- */
		if(sd) {
			int id = 0;
			struct mob_data *tmpmd = NULL;

			id = mob_once_spawn(sd, sd->bl.m, sd->bl.x, sd->bl.y, sd->status.name, 2308, 1, "");

			if((tmpmd = map_id2md(id)) != NULL) {
				tmpmd->master_id    = sd->bl.id;
				tmpmd->hp           = 3000 + skilllv * 3000 + sd->status.max_sp;
				tmpmd->deletetimer  = add_timer(tick+skill_get_time(skillid,skilllv),mob_timer_delete,id,NULL);
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			sc = status_get_sc(src);
			if(!sc || sc->data[SC_ANKLE].timer == -1) {
				// バックステップ
				int dir = 0, head_dir = 0;
				int count = skill_get_blewcount(skillid,skilllv);

				if(sd) {
					dir = sd->dir;
					head_dir = sd->head_dir;
				}
				unit_stop_walking(src,1);
				skill_blown(src,bl,count|SAB_REVERSEBLOW|SAB_NODAMAGE|SAB_NOPATHSTOP|SAB_NOTKNOCK);
				if(sd)
					pc_setdir(sd, dir, head_dir);
			}
		}
		break;
	case KO_KYOUGAKU:		/* 幻術 -驚愕- */
		{
			int rate;
			// プレイヤー以外または味方には使用不可
			if(bl->type != BL_PC || battle_check_target(src,bl,BCT_PARTY) > 0) {
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_TOTARGET,0,0);
				break;
			}
			rate = 4500 + 500 * skilllv - status_get_int(bl) / 10;
			if(rate < 500)
				rate = 500;
			if(atn_rand() % 10000 < rate) {
				int param = (skilllv > 0)? skilllv*2 + atn_rand()%(skilllv*3) : 0;
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,param,0,0,skill_get_time(skillid,skilllv),0);
			} else {
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				break;
			}
		}
		break;
	case KO_JYUSATSU:		/* 幻術 -呪殺- */
		{
			int rate;
			// プレイヤー以外には使用不可
			if(bl->type != BL_PC) {
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_TOTARGET,0,0);
				break;
			}
			rate = 4500 + 1000 * skilllv - status_get_int(bl) / 2;
			if(rate < 500)
				rate = 500;
			if(atn_rand() % 10000 < rate) {
				int damage = (int)((atn_bignumber)status_get_max_hp(bl) * skilllv * 5 / 100);
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
				battle_damage(src,bl,damage,0,0,0);
				if(status_get_lv(src) >= status_get_lv(bl)) {
					if(atn_rand() % 10000 < 10 * skilllv) {
						// コーマ
						if(dstsd) {
							dstsd->status.hp = 1;
							clif_updatestatus(dstsd,SP_HP);
						}
					}
				}
				status_change_pretimer(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			} else {
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				break;
			}
		}
		break;
	case KO_KAHU_ENTEN:	/* 火符：炎天 */
	case KO_HYOUHU_HUBUKI:	/* 氷符：吹雪 */
	case KO_KAZEHU_SEIRAN:	/* 風符：青嵐 */
	case KO_DOHU_KOUKAI:	/* 土符：剛塊 */
		if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			// 他属性を召喚している場合は削除
			if(sd->elementball.num) {
				if(sd->elementball.ele != skill_get_pl(skillid)) {
					pc_delelementball(sd,sd->elementball.num,0);
				}
			}
			pc_addelementball(sd,skill_get_time(skillid,skilllv),MAX_ELEMENTBALL,skill_get_pl(skillid));
		}
		break;
	case KO_GENWAKU:		/* 幻術 -幻惑- */
		{
			int rate = 4500 + 500 * skilllv - status_get_int(bl) / 10;
			if(rate < 500)
				rate = 500;
			if(atn_rand() % 10000 < rate) {
				int x = src->x;
				int y = src->y;
				struct block_list *t_bl = src;
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
				unit_movepos(src,bl->x,bl->y,0);
				if(!(status_get_mode(bl)&MD_BOSS))	// ボス属性以外
					unit_movepos(bl,x,y,0);
				if(atn_rand() % 10000 < 7500) {
					t_bl = bl;
				}
				status_change_pretimer(t_bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			} else {
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				break;
			}
		}
		break;
	case KO_IZAYOI:		/* 十六夜 */
	case KG_KYOMU:		/* 幻術 -虚無の影- */
	case KG_KAGEMUSYA:	/* 幻術 -分身- */
	case OB_ZANGETSU:	/* 幻術 -残月- */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case KG_KAGEHUMI:	/* 幻術 -影踏み- */
		if(flag&1) {
			sc = status_get_sc(bl);
			if(sc) {
				if(sc->data[SC_HIDING].timer != -1 || sc->data[SC_CLOAKING].timer != -1 || sc->data[SC_CLOAKINGEXCEED].timer != -1 ||
				   sc->data[SC__SHADOWFORM].timer != -1 || sc->data[SC_CAMOUFLAGE].timer != -1 || sc->data[SC_MARIONETTE].timer != -1 ||
				   sc->data[SC_MARIONETTE2].timer != -1 || sc->data[SC_HARMONIZE].timer != -1 || sc->data[SC_NEWMOON].timer != -1)
				{
					status_change_end(bl, SC_HIDING, -1);
					status_change_end(bl, SC_CLOAKING, -1);
					status_change_end(bl, SC_CLOAKINGEXCEED, -1);
					status_change_end(bl, SC_NEWMOON, -1);
					status_change_end(bl, SC__SHADOWFORM, -1);
					status_change_end(bl, SC_CAMOUFLAGE, -1);
					status_change_end(bl, SC_MARIONETTE, -1);
					status_change_end(bl, SC_MARIONETTE2, -1);
					status_change_end(bl, SC_HARMONIZE, -1);
					status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
				}
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			map_foreachinarea(skill_area_sub,bl->m,
				bl->x-ar,bl->y-ar,
				bl->x+ar,bl->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case OB_OBOROGENSOU:	/* 幻術 -朧幻想- */
		{
			int hp = 0, hp_val, hp_max, hp_per = 0, hp_lv;
			int sp = 0, sp_val, sp_max, sp_per = 0, sp_lv;

			// プレイヤー以外には無効
			if(bl->type != BL_PC) {
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_TOTARGET,0,0);
				break;
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置

			// HPの割合算出
			hp_val = status_get_hp(bl);
			hp_max = status_get_max_hp(bl);

			if(hp_max != 0) {
				hp_per = 100 * hp_val / hp_max;
			}
			if(hp_per > 75)      hp_lv = 5;
			else if(hp_per > 50) hp_lv = 4;
			else if(hp_per > 30) hp_lv = 3;
			else if(hp_per > 15) hp_lv = 2;
			else                 hp_lv = 1;

			if(hp_val % 2 == 0)
				hp = hp_max * ((6 - hp_lv) * 4 + skilllv) / 100;
			else
				hp -= hp_max * (hp_lv * 4 + skilllv) / 100;

			// SPの割合算出
			sp_val = status_get_sp(bl);
			sp_max = status_get_max_sp(bl);

			if(sp_max != 0) {
				sp_per = 100 * sp_val / sp_max;
			}
			if(sp_per > 75)      sp_lv = 5;
			else if(sp_per > 50) sp_lv = 4;
			else if(sp_per > 30) sp_lv = 3;
			else if(sp_per > 15) sp_lv = 2;
			else                 sp_lv = 1;

			if(sp_val % 2 == 0)
				sp = sp_max * ((6 - sp_lv) * 3 + skilllv) / 100;
			else
				sp -= sp_max * (sp_lv * 3 + skilllv) / 100;

			unit_heal(bl,hp,sp,0,0);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case OB_AKAITSUKI:	/* 幻術 -紅月- */
		// 対人MAP以外ではプレイヤーに使用不可またはBOSS、味方には使用不可
		if((!map[src->m].flag.pvp && !map[src->m].flag.gvg && !map[src->m].flag.pk && bl->type == BL_PC) || status_get_mode(bl)&MD_BOSS || battle_check_target(src,bl,BCT_PARTY) > 0) {
			if(sd)
				clif_skill_fail(sd,skillid,SKILLFAIL_TOTARGET,0,0);
			break;
		}
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case RL_RICHS_COIN:		/* リッチズコイン */
		if(sd) {
			int i;
			if(sd->coin.num >= MAX_COIN) {
				clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				break;
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			for(i=0;i<MAX_COIN && sd->coin.num<MAX_COIN;i++)
				pc_addcoin(sd,skill_get_time(skillid,skilllv),MAX_COIN);
		}
		break;
	case RL_C_MARKER:		/* クリムゾンマーカー */
		if(sd) {
			int i;

			sc = status_get_sc(bl);
			if(sc && sc->data[SC_C_MARKER].timer != -1 && sc->data[SC_C_MARKER].val2 != src->id)
				status_change_end(bl, SC_C_MARKER, -1);

			for(i=0;i<3;i++) {
				if(sd->c_marker[i] == bl->id || sd->c_marker[i] == 0)
					break;
			}
			if(i == 3) {
				clif_skill_fail(sd,skillid,SKILLFAIL_MORESKILL,0,0);
				break;
			}
			sd->c_marker[i] = bl->id;
			status_change_start(bl,SC_C_MARKER,skilllv,src->id,i,0,skill_get_time(skillid,skilllv),0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		else {
			status_change_start(bl,SC_C_MARKER,skilllv,src->id,0,0,skill_get_time(skillid,skilllv),0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case RL_FLICKER:		/* フリッカー */
		{
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_flicker,bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_SKILL,src,tick);
			map_foreachinarea(skill_area_sub,src->m,
				src->x-ar,src->y-ar,
				src->x+ar,src->y+ar,
				BL_CHAR,src,RL_H_MINE,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_damage_id);
		}
		break;
	case RL_B_TRAP:			/* バインドトラップ */
		skill_unitsetting(src,skillid,skilllv,src->x,src->y,0);
		break;
	case RL_HEAT_BARREL:	/* ヒートバレル */
	case RL_P_ALTER:	/* プラチナムアルター */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,(sd)? sd->coin.num: 10,skill_get_time(skillid,skilllv),0);
		if(sd)
			pc_delcoin(sd,MAX_COIN,0);
		break;
	case SJ_DOCUMENT:	/* 太陽と月と星の記録 */
		{
			int i;
			if( skilllv & 0x01 ){
				for (i = 0; i < 3; i++ ) {
					sd->feel_index[i] = -1;
					memset(&sd->status.feel_map[i], 0, sizeof(sd->status.feel_map[0]));
				}
			}
			if( skilllv & 0x02 ){
				const char *reg[] = { "PC_HATE_MOB_SUN", "PC_HATE_MOB_MOON", "PC_HATE_MOB_STAR" };
				for (i = 0; i < 3; i++ ) {
					sd->hate_mob[i] = -1;
					pc_setglobalreg(sd,reg[i],0);
				}
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case SJ_GRAVITYCONTROL:	/* 重力調節 */
		{
			int type = GetSkillStatusChangeTable(skillid);
			sc = status_get_sc(bl);
			if(sc && sc->data[type].timer != -1 ){
				sc->data[type].val2 = 0;
				status_change_end(bl, type, -1);
			}
			else{
				int fall_damage = status_get_baseatk(src) + status_get_atk(src) - status_get_def2(bl);

				if (bl->type == BL_PC)
					fall_damage += dstsd->weight / 10 - status_get_def(bl);
				else // Monster's don't have weight. Put something in its place.
					fall_damage += 50 * status_get_lv(src) - status_get_def(bl);

				fall_damage = max(1, fall_damage);
				status_change_start(bl,type,skilllv,fall_damage,0,0,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case SP_SOULGOLEM:			/* ゴーレムの魂 */
	case SP_SOULSHADOW:			/* 影の魂 */
	case SP_SOULFALCON:			/* 鷹の魂 */
	case SP_SOULFAIRY:			/* 妖精の魂 */
	case SP_SOULREAPER:			/* 魂の収穫 */
	case SP_SOULCOLLECT:		/* 魂の蓄積 */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SP_SOULDIVISION:		/* 魂の分裂 */
		clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SP_SOULCURSE:			/* 死霊憑依 */
		if(flag&1) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,(status_get_mode(bl)&MD_BOSS)? 20: 100,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,BL_MOB,
				src,skillid,skilllv,tick, flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SP_SOULUNITY:	/* 魂の連結 */
		if((flag&1) || sd == NULL || sd->status.party_id == 0) {
			clif_skill_nodamage(bl,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			/* パーティ全体への処理 */
			party_foreachsamemap(skill_area_sub,
				sd,skill_get_area(skillid,skilllv),
				src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SP_SOULREVOLVE:		/* 魂の循環 */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_end(bl,SC_ALCHEMIST,-1);
		status_change_end(bl,SC_MONK,-1);
		status_change_end(bl,SC_STAR,-1);
		status_change_end(bl,SC_SAGE,-1);
		status_change_end(bl,SC_CRUSADER,-1);
		status_change_end(bl,SC_SUPERNOVICE,-1);
		status_change_end(bl,SC_KNIGHT,-1);
		status_change_end(bl,SC_WIZARD,-1);
		status_change_end(bl,SC_PRIEST,-1);
		status_change_end(bl,SC_BARDDANCER,-1);
		status_change_end(bl,SC_ROGUE,-1);
		status_change_end(bl,SC_ASSASIN,-1);
		status_change_end(bl,SC_BLACKSMITH,-1);
		status_change_end(bl,SC_HUNTER,-1);
		status_change_end(bl,SC_SOULLINKER,-1);
		status_change_end(bl,SC_HIGH,-1);
		status_change_end(bl,SC_DEATHKINGHT,-1);
		status_change_end(bl,SC_COLLECTOR,-1);
		status_change_end(bl,SC_NINJA,-1);
		status_change_end(bl,SC_GUNNER,-1);
		status_change_end(bl,SC_SOULGOLEM,-1);
		status_change_end(bl,SC_SOULSHADOW,-1);
		status_change_end(bl,SC_SOULFALCON,-1);
		status_change_end(bl,SC_SOULFAIRY,-1);
		unit_heal(bl,0,460,0,1);
		break;
	case SP_KAUTE:	/* カウト */
		if(sd) {
			int heal_sp = 0;
			clif_skill_nodamage(src, bl, skillid, skilllv, 1);
			heal_sp = (int)((atn_bignumber)status_get_max_sp(bl) * (13+skilllv*3) / 100);
			unit_heal(bl,0,heal_sp,0,1);
		}
		break;
	case SU_HIDE:	/* かくれる */
		{
			int type = GetSkillStatusChangeTable(skillid);
			clif_skill_nodamage(src,bl,skillid,-1,1);
			sc = status_get_sc(bl);
			if(type >= 0 && sc && sc->data[type].timer != -1) {
				/* 解除する */
				status_change_end(bl, type, -1);
			} else {
				/* 付加する */
				status_change_start(bl,type,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
			break;
		}
	case SU_STOOP:	/* うずくまる */
	case SU_CHATTERING:	/* チャタリング */
	case SU_ARCLOUSEDASH:	/* アクラウスダッシュ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SU_TUNAPARTY:	/* マグロシールド */
		{
			int rate;

			rate = (int)(skilllv * 10 * (atn_bignumber)status_get_max_hp(bl) / 100);
			if(sd && pc_checkskill(sd,SU_SPIRITOFSEA) > 0)	// 海の魂
				rate *= 2;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,rate,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SU_CN_POWDERING:	/* イヌハッカシャワー */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		skill_unitsetting(src,skillid,skilllv,bl->x,bl->y,0);
		break;
	case SU_SV_ROOTTWIST:	/* マタタビの根っこ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,src->id,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SU_HISS:	/* 警戒 */
		if(flag&1 || sd == NULL) {
			int val2 = (skilllv >= 5)? 500: ((skilllv == 4)? 250: skilllv * 50);	// 完全回避増加
			int val3 = (skilllv >= 4)? 60: ((skilllv == 3)? 40: 25);	// 移動速度増加

			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),15,val2,val3,0,skill_get_time(skillid,skilllv),0);
		} else if(sd) {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			party_foreachsamemap(skill_area_sub,
				sd,ar,
				src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SU_POWEROFFLOCK:	/* 群れの力 */
		if(flag&1) {
			int rate = 1000 + 500 * skilllv + status_get_dex(src) * 10 + status_get_luk(src) * 10;	// 暫定確率
			if(atn_rand() % 10000 < rate)
				status_change_pretimer(bl,SC_FEAR,skilllv,0,0,0,skill_get_time(skillid,skilllv),0,tick+status_get_amotion(src));
			if(atn_rand() % 10000 < status_change_rate(bl,SC_FREEZE,rate,status_get_lv(src)))
				status_change_pretimer(bl,SC_FREEZE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0,tick+status_get_amotion(src));
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,bl->m,
				bl->x-ar,bl->y-ar,
				bl->x+ar,bl->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SU_GROOMING:	/* グルーミング */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_end(bl, SC_STUN, -1);
		status_change_end(bl, SC_FREEZE, -1);
		status_change_end(bl, SC_STONE, -1);
		status_change_end(bl, SC_SLEEP, -1);
		status_change_end(bl, SC_SILENCE, -1);
		status_change_end(bl, SC_BLEED, -1);
		status_change_end(bl, SC_POISON, -1);
		status_change_end(bl, SC_FEAR, -1);
		status_change_end(bl, SC_MANDRAGORA, -1);
		status_change_end(bl, SC_DIAMONDDUST, -1);
		status_change_end(bl, SC_FROSTMISTY, -1);
		status_change_end(bl, SC_DEEP_SLEEP, -1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SU_PURRING:	/* のどを鳴らす */
		if(flag&1) {
			int lv = pc_checkskill(sd,SU_GROOMING);
			clif_skill_nodamage(bl,bl,skillid,skilllv,1);
			status_change_end(bl, SC_STUN, -1);
			status_change_end(bl, SC_FREEZE, -1);
			status_change_end(bl, SC_STONE, -1);
			status_change_end(bl, SC_SLEEP, -1);
			status_change_end(bl, SC_SILENCE, -1);
			status_change_end(bl, SC_BLEED, -1);
			status_change_end(bl, SC_POISON, -1);
			status_change_end(bl, SC_FEAR, -1);
			status_change_end(bl, SC_MANDRAGORA, -1);
			status_change_end(bl, SC_DIAMONDDUST, -1);
			status_change_end(bl, SC_FROSTMISTY, -1);
			status_change_end(bl, SC_DEEP_SLEEP, -1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),lv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			party_foreachsamemap(skill_area_sub,
				sd,skill_get_area(skillid,skilllv),
				src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SU_MEOWMEOW:	/* ミャウミャウ */
		if(flag&1) {
			clif_skill_nodamage(bl,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			party_foreachsamemap(skill_area_sub,
				sd,skill_get_area(skillid,skilllv),
				src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SU_FRESHSHRIMP:	/* 新鮮なエビ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,skill_fix_heal(src, bl, skillid, skill_calc_heal(src, skilllv)),skill_get_time(skillid,skilllv),0);
		break;
	case SU_BUNCHOFSHRIMP:	/* エビ三昧 */
		if(flag&1) {
			int heal;
			heal = skill_fix_heal(src, bl, skillid, skill_calc_heal(src, skilllv));

			if(sc) {
				if(sc->data[SC_CRITICALWOUND].timer != -1)
					heal = heal * (100 - sc->data[SC_CRITICALWOUND].val2) / 100;
				if(sc->data[SC_DEATHHURT].timer != -1)	/* デスハート */
					heal = heal * (100 - sc->data[SC_DEATHHURT].val2) / 100;
				if(sc->data[SC_BERSERK].timer != -1) /* バーサーク中はヒール０ */
					heal = 0;
			}
			clif_skill_nodamage(src,bl,AL_HEAL,heal,1);
			clif_skill_nodamage(bl,bl,skillid,skilllv,1);
			battle_heal(NULL,bl,heal,0,0);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skillid,skilllv,0,0,((sd)? pc_checkskill(sd, SU_SPIRITOFSEA): 0)*30000 + skill_get_time(skillid,skilllv),0);
		} else {
			party_foreachsamemap(skill_area_sub,
				sd,skill_get_area(skillid,skilllv),
				src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SU_TUNABELLY:	/* 大トロ */
		{
			int heal = (int)((5 + skilllv * 5 + (skilllv>=5? 20: (skilllv==4? 10: 0))) * (atn_bignumber)status_get_max_hp(bl) / 100);

			if(sc) {
				if(sc->data[SC_CRITICALWOUND].timer != -1)
					heal = heal * (100 - sc->data[SC_CRITICALWOUND].val2) / 100;
				if(sc->data[SC_DEATHHURT].timer != -1)	/* デスハート */
					heal = heal * (100 - sc->data[SC_DEATHHURT].val2) / 100;
				if(sc->data[SC_BERSERK].timer != -1) /* バーサーク中はヒール０ */
					heal = 0;
			}
			clif_skill_nodamage(src,bl,AL_HEAL,heal,1);
			clif_skill_nodamage(bl,bl,skillid,skilllv,1);
			battle_heal(NULL,bl,heal,0,0);
		}
		break;
	case SU_SHRIMPARTY:	/* エビパーティー */
		if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skillid,skilllv,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SU_LUNATICCARROTBEAT:	// キャロットビート
		if(sd) {
			int nameid, amount, idx = 0;

			nameid = 515;	// ニンジン
			amount = 1;

			idx = pc_search_inventory(sd,nameid);

			if(idx >= 0 && sd->status.inventory[idx].amount >= amount) {	// ニンジン持ってたら消費
				pc_delitem(sd,idx,amount,0,1);
				skill_castend_damage_id(src,bl,SU_LUNATICCARROTBEAT2,skilllv,tick,0);
				break;
			}
		}
		skill_castend_damage_id(src,bl,SU_LUNATICCARROTBEAT,skilllv,tick,0);
		break;
	case ECL_SNOWFLIP:
		status_change_end(bl, SC_SLEEP, -1);
		status_change_end(bl, SC_BLEED, -1);
		status_change_end(bl, SC_HELLINFERNO, -1);
		status_change_end(bl, SC_DEEP_SLEEP, -1);
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
		break;
	case ECL_PEONYMAMY:
		status_change_end(bl, SC_FREEZE, -1);
		status_change_end(bl, SC_FROSTMISTY, -1);
		status_change_end(bl, SC_DIAMONDDUST, -1);
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
		break;
	case ECL_SADAGUI:
		status_change_end(bl, SC_STUN, -1);
		status_change_end(bl, SC_CONFUSION, -1);
		status_change_end(bl, SC_HALLUCINATION, -1);
		status_change_end(bl, SC_FEAR, -1);
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
		break;
	case ECL_SEQUOIADUST:
		status_change_end(bl, SC_STONE, -1);
		status_change_end(bl, SC_POISON, -1);
		status_change_end(bl, SC_CURSE, -1);
		status_change_end(bl, SC_BLIND, -1);
		status_change_end(bl, SC_DECREASEAGI, -1);
		status_change_end(bl, SC_REVERSEORCISH, -1);
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
		break;
	case EVT_FULL_THROTTLE:	/* フルスロットル */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		unit_heal(src,status_get_max_hp(src),0,0,0);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case NV_HELPANGEL:	/* 天使さま助けて */
		if((flag&1) || sd == NULL || sd->status.party_id == 0) {
			clif_skill_nodamage(bl,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			/* パーティ全体への処理 */
			party_foreachsamemap(skill_area_sub,
				sd,skill_get_area(skillid,skilllv),
				src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case IG_GUARDIAN_SHIELD:	/* ガーディアンシールド */
		if((flag&1) || sd == NULL || sd->status.party_id == 0) {
			int val = (int)((atn_bignumber)(status_get_max_hp(src)*5/100 + status_get_sta(src)*status_get_lv(src)*2) * (50+50*skilllv)/100);
			clif_skill_nodamage(bl,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,val,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			/* パーティ全体への処理 */
			party_foreachsamemap(skill_area_sub,
				sd,skill_get_area(skillid,skilllv),
				src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case IG_ULTIMATE_SACRIFICE:		/* アルティメットサクリファイス */
		if(flag&1) {
			if(bl->id != skill_area_temp[1]) {
				clif_skill_nodamage(src,bl,skillid,skilllv,1);
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		} else {
			skill_area_temp[1] = src->id;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			/* パーティ全体への処理 */
			party_foreachsamemap(skill_area_sub,
				sd,skill_get_area(skillid,skilllv),
				src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
			unit_heal(src,-status_get_hp(src)+1,0,0,0);
		}
		break;
	case CD_REPARATIO:		/* レパラティオ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		clif_misceffect_value(bl, 657, status_get_max_hp(bl));
		unit_heal(src,status_get_max_hp(bl),0,0,0);
		break;
	case CD_MEDIALE_VOTUM:		/* メディアリボトゥム */
		if(flag&0x20) {
			int heal = (int)((atn_bignumber)status_get_max_hp(bl) * 5 / 100);
			clif_misceffect_value(bl, 312, heal);
			clif_misceffect_value(bl, 657, heal);
			unit_heal(bl,heal,0,0,0);
		} else if(flag&0x10) {
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-(flag&0x0f),bl->y-(flag&0x0f),bl->x+(flag&0x0f),bl->y+(flag&0x0f),
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_PARTY|0x20,
				skill_castend_nodamage_id);
		} else {
			int ar = skill_get_area(skillid,skilllv) + status_get_hplus(src)/100;
			if(ar > 10) ar = 10;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,ar,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case CD_COMPETENTIA:	/* コンペテンティア */
		if(flag&1) {
			int hp = BIGNUM2INT((atn_bignumber)status_get_max_hp(bl) * ((skilllv < 4)? (65 + skilllv * 5): (75 + skilllv * 5)) / 100);
			int sp = BIGNUM2INT((atn_bignumber)status_get_max_sp(bl) * ((skilllv < 5)? (15 + skilllv * 15): 100) / 100);
			unit_heal(bl,hp,sp,0,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case CD_DILECTIO_HEAL:			/* ディレクティオヒール */
		if(flag&1) {
			int heallv = (sd)? pc_checkskill(sd, AL_HEAL): skilllv;
			int heal = skill_fix_heal(src, bl, skillid, skill_calc_heal(src, heallv));
			heal = BIGNUM2INT((atn_bignumber)heal * (500 + skilllv * 25) / 100 + status_get_hplus(src) * skilllv);
			clif_misceffect_value(bl, 312, heal);
			clif_misceffect_value(bl, 657, heal);
			unit_heal(bl,heal,0,0,0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case MT_M_MACHINE:	/* 装置製造 */
		if(sd) {
			clif_making_list(sd,PRD_M_MACHINE,skillid,skilllv,7);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case ABC_STRIP_SHADOW:		/* ストリップシャドウ */
		{
			int strip_fix;

			strip_fix = status_get_crt(src) - status_get_crt(bl);
			if(strip_fix < 0)
				strip_fix = 0;
			if(atn_rand()%100 >= 5 * skilllv + ((strip_fix)? strip_fix / 4: 0)) {
				if(sd)
					clif_skill_fail(sd,skillid,SKILLFAIL_FAILED,0,0);
				break;
			}

			if(dstsd) {
				int i;
				for(i=0; i<MAX_INVENTORY; i++) {
					if(dstsd->status.inventory[i].equip && (dstsd->status.inventory[i].equip & LOC_SHADOW_ALL)) {
						pc_unequipitem(dstsd,i,0);
					}
				}
			}
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case ABC_ABYSS_SLAYER:		/* アビススレイヤー */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		unit_heal(src,status_get_max_hp(bl),status_get_max_sp(bl),0,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case WH_HAWK_M:		/* ホークマスタリー */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sd) {
			if(pc_isfalcon(sd)) {
				pc_setoption(sd,sd->sc.option & ~OPTION_FALCON);
			} else {
				pc_setoption(sd,sd->sc.option | OPTION_FALCON);
			}
		}
		break;
	case WH_CALAMITYGALE:		/* カラミティゲイル */
		{
			int skill;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			if(sd && ((skill = pc_checkskill(sd,RA_UNLIMIT)) > 0)) {
				status_change_start(bl,SC_UNLIMIT,skill,0,0,0,skill_get_time2(skillid,skill),0);
			}
		}
		break;
	case BO_BIONIC_PHARMACY:	/* バイオニックファーマシー */
		if(sd) {
			clif_making_list(sd,PRD_BIONIC_PHARMACY,skillid,skilllv,8);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
		}
		break;
	case BO_THE_WHOLE_PROTECTION:	/* ホールフルケミカルチャージ */
		if(flag&1) {
			status_change_start(bl,SC_CP_HELM,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			status_change_start(bl,SC_CP_SHIELD,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			status_change_start(bl,SC_CP_ARMOR,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			status_change_start(bl,SC_CP_WEAPON,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case EL_CIRCLE_OF_FIRE:	/* サークルオブファイア */
	case EL_FIRE_CLOAK:		/* ファイアークローク */
	case EL_WATER_SCREEN:	/* ウォータースクリーン */
	case EL_WATER_DROP:		/* ウォータードロップ */
	case EL_WIND_STEP:		/* ウィンドステップ */
	case EL_WIND_CURTAIN:	/* ウィンドカーテン */
	case EL_SOLID_SKIN:		/* ソリッドスキン */
	case EL_STONE_SHIELD:	/* ストーンシールド */
	case EL_PYROTECHNIC:	/* パイロテクニック */
	case EL_HEATER:			/* ヒーター */
	case EL_TROPIC:			/* トロピック */
	case EL_AQUAPLAY:		/* アクアプレイ */
	case EL_COOLER:			/* クーラー */
	case EL_CHILLY_AIR:		/* クールエアー */
	case EL_GUST:			/* ガスト */
	case EL_BLAST:			/* ブラスト */
	case EL_WILD_STORM:		/* ワイルドストーム */
	case EL_PETROLOGY:		/* ペトロジー */
	case EL_CURSED_SOIL:	/* カースドソイル */
	case EL_UPHEAVAL:		/* アップヘイバル */
		if(eld && eld->msd) {
			clif_skill_damage(src, bl, tick, 0, 0, -1, 1, skillid, -1, 0);	// エフェクトを出すための暫定処置
			status_change_start(&eld->msd->bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			status_change_start(bl,GetSkillStatusChangeTable(skillid)+1,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case EL_FIRE_MANTLE:		/* ファイアーマントル */
	case EL_WATER_BARRIER:		/* ウォーターバリアー */
	case EL_ZEPHYR:				/* ゼファー */
	case EL_POWER_OF_GAIA:		/* パワーオブガイア */
		if(eld && eld->msd) {
			clif_skill_poseffect(src,skillid,skilllv,eld->msd->bl.x,eld->msd->bl.y,tick);
			skill_unitsetting(src,skillid,skilllv,eld->msd->bl.x,eld->msd->bl.y,0);
		}
		break;
	case EM_EL_FLAMETECHNIC:		/* フレイムテクニック */
	case EM_EL_FLAMEARMOR:			/* フレイムアーマー */
	case EM_EL_COLD_FORCE:			/* コールドフォース */
	case EM_EL_CRYSTAL_ARMOR:		/* クリスタルアーマー */
	case EM_EL_GRACE_BREEZE:		/* グレイスブリーズ */
	case EM_EL_EYES_OF_STORM:		/* アイズオブストーム */
	case EM_EL_EARTH_CARE:			/* アースケア */
	case EM_EL_STRONG_PROTECTION:	/* ストロングプロテクション */
	case EM_EL_DEEP_POISONING:		/* ディープポイズニング */
	case EM_EL_POISON_SHIELD:		/* ポイズンシールド */
		if(eld && eld->msd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(&eld->msd->bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			status_change_start(src,GetSkillStatusChangeTable(skillid)+1,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case NPC_DISSONANCE:
	case NPC_UGLYDANCE:
		sc = status_get_sc(src);
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sc && sc->data[SC_DANCING].timer != -1) {
			status_change_end(src,SC_DANCING,-1);
		}
		else {
			struct skill_unit_group *sg = skill_unitsetting(src,skillid,skilllv,src->x,src->y,0);
			if(sg) {
				status_change_start(src,SC_DANCING,skillid,sg->bl.id,0,0,skill_get_time(skillid,skilllv)+1000,0);
			}
		}
		break;
	case NPC_CHEAL:			/* Mハイネスヒール */
		if(flag&1) {
			int heal = (status_get_lv(src) + status_get_int(src)) / 5 * 30;

			clif_skill_nodamage(src,bl,AB_CHEAL,heal,1);
			battle_heal(src,bl,heal,0,0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			map_foreachinarea(skill_area_sub,bl->m,
				bl->x-ar,bl->y-ar,
				bl->x+ar,bl->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_NOENEMY|1,
				skill_castend_nodamage_id);
		}
		break;
	case MT_SUMMON_ABR_BATTLE_WARIOR:	/* ABR バトルウォリアー */
	case MT_SUMMON_ABR_DUAL_CANNON:		/* ABR デュアルキャノン */
	case MT_SUMMON_ABR_MOTHER_NET:		/* ABR マザーネット */
	case MT_SUMMON_ABR_INFINITY:		/* ABR インフィニティ */
		if(sd) {
			const int mob_id[4] = { MOBID_ABR_BATTLE_WARIOR, MOBID_ABR_DUAL_CANNON, MOBID_ABR_MOTHER_NET, MOBID_ABR_INFINITY };
			int id;
			struct mob_data *tmpmd = NULL;

			clif_skill_nodamage(src,bl,skillid,skilllv,1);

			id = mob_once_spawn_area(sd, sd->bl.m, sd->bl.x-1, sd->bl.y-1, sd->bl.x+1, sd->bl.y+1, "--ja--", mob_id[ skillid-MT_SUMMON_ABR_BATTLE_WARIOR ], 1, "");
			if((tmpmd = map_id2md(id)) != NULL) {
				const int add_abr_max_hp[11] = { 0, 25000, 50000, 75000, 112500, 150000, 187500, 225000, 275000, 375000, 500000 };
				const int add_abr_atk[11] = { 0, 100, 300, 500, 800, 1100, 1400, 1700, 2000, 2500, 3000 };
				int n = pc_checkskill(sd,MT_ABR_M);
				if(n > 10)
					n = 10;
				tmpmd->master_id    = sd->bl.id;
				tmpmd->guild_id     = status_get_guild_id(src);
				tmpmd->speed        = sd->speed;
				tmpmd->deletetimer  = add_timer(tick+skill_get_time(skillid,skilllv),mob_timer_delete,id,NULL);
				tmpmd->state.nodrop = battle_config.cannibalize_no_drop;
				tmpmd->state.noexp  = battle_config.cannibalize_no_exp;
				tmpmd->state.nomvp  = battle_config.cannibalize_no_mvp;
				tmpmd->state.norandomwalk = 1;
				tmpmd->state.special_mob_ai = MOB_AI_ABR;
				// ABRのステータス変更
				switch(skillid){
				case MT_SUMMON_ABR_BATTLE_WARIOR:	/* ABR バトルウォリアー */
					tmpmd->hp = tmpmd->st.max_hp = BIGNUM2INT((atn_bignumber)status_get_max_hp(src) * 12 / 10 + add_abr_max_hp[n]);
#ifdef PRE_RENEWAL
					tmpmd->st.atk = 200 + (status_get_atk(src) + sd->base_atk) * 12 / 10 + add_abr_atk[n];
#else
					tmpmd->st.atk = 200 + (status_get_atk(src) + sd->plus_atk) * 12 / 10 + add_abr_atk[n];
#endif
					tmpmd->st.def = status_get_def(src) * 8 / 10 + n * 160;
					tmpmd->st.mdef = status_get_mdef(src) * 3 / 10 + n * 40;
					tmpmd->st.flee = status_get_flee(src) * 8 / 10 + n * 10;
					tmpmd->st.hit = status_get_hit(src);
					break;
				case MT_SUMMON_ABR_DUAL_CANNON:		/* ABR デュアルキャノン */
					tmpmd->hp = tmpmd->st.max_hp = BIGNUM2INT((atn_bignumber)status_get_max_hp(src) * 9 / 10 + add_abr_max_hp[n]);
#ifdef PRE_RENEWAL
					tmpmd->st.atk = 200 + (sd->watk + sd->base_atk) * 12 / 10 + add_abr_atk[n];
#else
					tmpmd->st.atk = 200 + (sd->watk + sd->plus_atk) * 12 / 10 + add_abr_atk[n];
#endif
					tmpmd->st.def = status_get_def(src) * 6 / 10 + n * 160;
					tmpmd->st.mdef = status_get_mdef(src) * 4 / 10 + n * 40;
					tmpmd->st.flee = status_get_flee(src) * 9 / 10 + n * 10;
					tmpmd->st.hit = status_get_hit(src);
					break;
				case MT_SUMMON_ABR_MOTHER_NET:		/* ABR マザーネット */
					tmpmd->hp = tmpmd->st.max_hp = BIGNUM2INT((atn_bignumber)status_get_max_hp(src) * 8 / 10 + add_abr_max_hp[n]);
#ifdef PRE_RENEWAL
					tmpmd->st.atk = 200 + (sd->watk + sd->base_atk) * 8 / 10 + add_abr_atk[n];
#else
					tmpmd->st.atk = 200 + (sd->watk + sd->plus_atk) * 8 / 10 + add_abr_atk[n];
#endif
					tmpmd->st.def = status_get_def(src) * 5 / 10 + n * 160;
					tmpmd->st.mdef = status_get_mdef(src) * 8 / 10 + n * 40;
					tmpmd->st.flee = status_get_flee(src) * 8 / 10 + n * 10;
					tmpmd->st.hit = status_get_hit(src);
					break;
				case MT_SUMMON_ABR_INFINITY:		/* ABR インフィニティ */
					tmpmd->hp = tmpmd->st.max_hp = BIGNUM2INT((atn_bignumber)status_get_max_hp(src) * 15 / 10 + add_abr_max_hp[n]);
#ifdef PRE_RENEWAL
					tmpmd->st.atk = 200 + (sd->watk + sd->base_atk) * 15 / 10 + add_abr_atk[n];
#else
					tmpmd->st.atk = 200 + (sd->watk + sd->plus_atk) * 15 / 10 + add_abr_atk[n];
#endif
					tmpmd->st.def = status_get_def(src) * 9 / 10 + n * 160;
					tmpmd->st.mdef = status_get_mdef(src) * 9 / 10 + n * 40;
					tmpmd->st.flee = status_get_flee(src) * 9 / 10 + n * 10;
					tmpmd->st.hit = status_get_hit(src);
					break;
				}
				status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case ABR_NET_REPAIR:	/* ネットリペア */
	case ABR_NET_SUPPORT:	/* ネットサポート */
		if(flag&1) {
			int hp = (skillid == ABR_NET_REPAIR)? BIGNUM2INT((atn_bignumber)status_get_max_hp(bl) * 10 / 100): 0;
			int sp = (skillid == ABR_NET_SUPPORT)? BIGNUM2INT((atn_bignumber)status_get_max_sp(bl) * 5 / 100): 0;
			unit_heal(bl,hp,sp,0,1);
		} else {
			// 主の情報を取得
			if(md && md->master_id) {
				struct block_list *master = map_id2bl(md->master_id);
				if(master && master->type == BL_PC) {
					int ar = skill_get_area(skillid,skilllv);
					clif_skill_nodamage(src,bl,skillid,skilllv,1);
					map_foreachinarea(skill_area_sub,src->m,
						src->x-ar,src->y-ar,
						src->x+ar,src->y+ar,
						BL_CHAR,master,skillid,skilllv,tick,flag|BCT_PARTY|1,
						skill_castend_nodamage_id);
				}
			}
		}
		break;
	case BO_WOODENWARRIOR:		/* クリエイトウドゥンウォリアー */
	case BO_WOODEN_FAIRY:		/* クリエイトウドゥンフェアリー */
	case BO_CREEPER:			/* クリエイトクリーパー */
	case BO_HELLTREE:			/* クリエイトヘルツリー */
		if(sd) {
			const int mob_id[5] = { MOBID_SUMMON_WOODENWARRIOR, MOBID_SUMMON_WOODEN_FAIRY, MOBID_SUMMON_CREEPER, 0, MOBID_SUMMON_HELLTREE };
			int id;
			struct mob_data *tmpmd = NULL;

			clif_skill_nodamage(src,bl,skillid,skilllv,1);

			id = mob_once_spawn_area(sd, sd->bl.m, sd->bl.x-1, sd->bl.y-1, sd->bl.x+1, sd->bl.y+1, "--ja--", mob_id[ skillid-BO_WOODENWARRIOR ], 1, "");
			if((tmpmd = map_id2md(id)) != NULL) {
				const int add_bionic_max_hp[11] = { 0, 25000, 50000, 75000, 112500, 150000, 187500, 225000, 275000, 375000, 500000 };
				const int add_bionic_atk[11] = { 0, 100, 300, 500, 800, 1100, 1400, 1700, 2000, 2500, 3000 };
				const int add_bionic_matk[11] = { 0, 50, 150, 250, 400, 550, 700, 850, 1000, 1500, 2000 };
				int n = pc_checkskill(sd,BO_BIONICS_M);
				if(n > 10)
					n = 10;
				tmpmd->master_id    = sd->bl.id;
				tmpmd->guild_id     = status_get_guild_id(src);
				tmpmd->speed        = sd->speed;
				tmpmd->deletetimer  = add_timer(tick+skill_get_time(skillid,skilllv),mob_timer_delete,id,NULL);
				tmpmd->state.nodrop = battle_config.cannibalize_no_drop;
				tmpmd->state.noexp  = battle_config.cannibalize_no_exp;
				tmpmd->state.nomvp  = battle_config.cannibalize_no_mvp;
				tmpmd->state.norandomwalk = 1;
				tmpmd->state.special_mob_ai = MOB_AI_BIONIC;
				// バイオニックモンスターのステータス変更
				switch(skillid){
				case BO_WOODENWARRIOR:		/* クリエイトウドゥンウォリアー */
					tmpmd->hp = tmpmd->st.max_hp = BIGNUM2INT((atn_bignumber)status_get_max_hp(src) * 12 / 10 + add_bionic_max_hp[n]);
#ifdef PRE_RENEWAL
					tmpmd->st.atk = 200 + (status_get_atk(src) + sd->base_atk) * 12 / 10 + add_bionic_atk[n];
#else
					tmpmd->st.atk = 200 + (status_get_atk(src) + sd->plus_atk) * 12 / 10 + add_bionic_atk[n];
#endif
					tmpmd->st.matk = 100 + (status_get_matk1(src) + status_get_matk2(src)) * 12 / 10 + add_bionic_matk[n];
					tmpmd->st.def = status_get_def(src) * 8 / 10 + n * 160;
					tmpmd->st.mdef = status_get_mdef(src) * 3 / 10 + n * 40;
					tmpmd->st.flee = status_get_flee(src) * 8 / 10 + n * 10;
					tmpmd->st.hit = status_get_hit(src);
					break;
				case BO_WOODEN_FAIRY:		/* クリエイトウドゥンフェアリー */
					tmpmd->hp = tmpmd->st.max_hp = BIGNUM2INT((atn_bignumber)status_get_max_hp(src) * 9 / 10 + add_bionic_max_hp[n]);
#ifdef PRE_RENEWAL
					tmpmd->st.atk = 200 + (sd->watk + sd->base_atk) * 12 / 10 + add_bionic_atk[n];
#else
					tmpmd->st.atk = 200 + (sd->watk + sd->plus_atk) * 12 / 10 + add_bionic_atk[n];
#endif
					tmpmd->st.matk = 100 + (status_get_matk1(src) + status_get_matk2(src)) * 12 / 10 + add_bionic_matk[n];
					tmpmd->st.def = status_get_def(src) * 6 / 10 + n * 160;
					tmpmd->st.mdef = status_get_mdef(src) * 4 / 10 + n * 40;
					tmpmd->st.flee = status_get_flee(src) * 9 / 10 + n * 10;
					tmpmd->st.hit = status_get_hit(src);
					break;
				case BO_CREEPER:			/* クリエイトクリーパー */
					tmpmd->hp = tmpmd->st.max_hp = BIGNUM2INT((atn_bignumber)status_get_max_hp(src) * 8 / 10 + add_bionic_max_hp[n]);
#ifdef PRE_RENEWAL
					tmpmd->st.atk = 200 + (sd->watk + sd->base_atk) * 8 / 10 + add_bionic_atk[n];
#else
					tmpmd->st.atk = 200 + (sd->watk + sd->plus_atk) * 8 / 10 + add_bionic_atk[n];
#endif
					tmpmd->st.matk = 100 + (status_get_matk1(src) + status_get_matk2(src)) * 8 / 10 + add_bionic_matk[n];
					tmpmd->st.def = status_get_def(src) * 5 / 10 + n * 160;
					tmpmd->st.mdef = status_get_mdef(src) * 8 / 10 + n * 40;
					tmpmd->st.flee = status_get_flee(src) * 8 / 10 + n * 10;
					tmpmd->st.hit = status_get_hit(src);
					break;
				case BO_HELLTREE:			/* クリエイトヘルツリー */
					tmpmd->hp = tmpmd->st.max_hp = BIGNUM2INT((atn_bignumber)status_get_max_hp(src) * 15 / 10 + add_bionic_max_hp[n]);
#ifdef PRE_RENEWAL
					tmpmd->st.atk = 200 + (sd->watk + sd->base_atk) * 15 / 10 + add_bionic_atk[n];
#else
					tmpmd->st.atk = 200 + (sd->watk + sd->plus_atk) * 15 / 10 + add_bionic_atk[n];
#endif
					tmpmd->st.matk = 100 + (status_get_matk1(src) + status_get_matk2(src)) * 15 / 10 + add_bionic_matk[n];
					tmpmd->st.def = status_get_def(src) * 9 / 10 + n * 160;
					tmpmd->st.mdef = status_get_mdef(src) * 9 / 10 + n * 40;
					tmpmd->st.flee = status_get_flee(src) * 9 / 10 + n * 10;
					tmpmd->st.hit = status_get_hit(src);
					break;
				}
				status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		}
		break;
	case TR_RETROSPECTION:		/* 回想 */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(sd)
			unit_skilluse_id(&sd->bl,src->id,sd->skill_4thdance.id,sd->skill_4thdance.lv);
		break;
	case TR_SOUNDBLEND:			/* サウンドブレンド */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,src->id,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case TR_GEF_NOCTURN:		/* ゲフェニアノクターン */
	case TR_AIN_RHAPSODY:		/* 鉱員のラプソディ */
		if(flag&1) {
			if(!(status_get_mode(bl)&MD_BOSS)) {
				status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,skill_area_temp[0],0,0,skill_get_time(skillid,skilllv),0);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[0] = 0;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(sd->sc.data[SC_KVASIR_SONATA].timer == -1) {
				party_foreachsamemap(skill_area_sub,
					sd,15,src,skillid,skilllv,tick, flag|BCT_PARTY|1,
					skill_4thpartner_count);
			} else {
				skill_area_temp[0] = 2;
			}
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
			if(sd) {
				sd->skill_4thdance.id = skillid;
				sd->skill_4thdance.lv = skilllv;
			}
		}
		break;
	case TR_ROKI_CAPRICCIO:		/* ロキの気まぐれ */
	case TR_NIPELHEIM_REQUIEM:	/* 死者たちへのレクイエム */
		if(flag&1) {
			if(bl->type == BL_PC) {
				int rate = 10 * skilllv;
				if(skill_area_temp[0] > 1) {		// パートナーが居る場合
					rate = rate * 15 / 10;
				}
				if(atn_rand()%100 < rate) {
					if(skillid == TR_ROKI_CAPRICCIO) {
						status_change_start(bl,SC_HANDICAPSTATE_MISFORTUNE,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
						status_change_start(bl,SC_CONFUSION,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
					} else {
						status_change_start(bl,SC_HANDICAPSTATE_DEPRESSION,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
						status_change_start(bl,SC_CURSE,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
					}
				}
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[0] = 0;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(sd->sc.data[SC_KVASIR_SONATA].timer == -1) {
				party_foreachsamemap(skill_area_sub,
					sd,15,src,skillid,skilllv,tick, flag|BCT_PARTY|1,
					skill_4thpartner_count);
			} else {
				skill_area_temp[0] = 2;
			}
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_ENEMY|1,
				skill_castend_nodamage_id);
			if(sd) {
				sd->skill_4thdance.id = skillid;
				sd->skill_4thdance.lv = skilllv;
			}
		}
		break;
	case TR_MUSICAL_INTERLUDE:		/* ミュージカルインタールード */
	case TR_JAWAII_SERENADE:		/* 夕焼けのセレナーデ */
	case TR_PRON_MARCH:				/* プロンテラマーチ */
		if(flag&1) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,skill_area_temp[0],0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			skill_area_temp[0] = 0;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			if(sd->sc.data[SC_KVASIR_SONATA].timer == -1) {
				party_foreachsamemap(skill_area_sub,
					sd,15,src,skillid,skilllv,tick, flag|BCT_PARTY|1,
					skill_4thpartner_count);
			} else {
				skill_area_temp[0] = 2;
			}
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
			if(sd) {
				sd->skill_4thdance.id = skillid;
				sd->skill_4thdance.lv = skilllv;
			}
		}
		break;
	case EM_ACTIVITY_BURN:		/* アクティビティバーン */
		{
			const int damage_ap[5] = { 60, 80, 110, 150, 200 };
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			unit_heal(bl,0,0,-(damage_ap[(skilllv <= 5)? skilllv-1: 5]),0);
		}
		break;
	case EM_INCREASING_ACTIVITY:		/* インクリーシングアクティビティ */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		unit_heal(bl,0,0,50+20*skilllv,0);
		break;
	case EM_SUMMON_ELEMENTAL_ARDOR:			/* サモンアルドール */
	case EM_SUMMON_ELEMENTAL_DILUVIO:		/* サモンディルビオ */
	case EM_SUMMON_ELEMENTAL_PROCELLA:		/* サモンプロセラ */
	case EM_SUMMON_ELEMENTAL_TERREMOTUS:	/* サモンテレモトゥス */
	case EM_SUMMON_ELEMENTAL_SERPENS:		/* サモンサーペンス */
		if(sd) {
			int elem_id = 0;

			switch(skillid) {
				case EM_SUMMON_ELEMENTAL_ARDOR:      elem_id = ELEMID_EM_ARDOR;      break;
				case EM_SUMMON_ELEMENTAL_DILUVIO:    elem_id = ELEMID_EM_DILUVIO;    break;
				case EM_SUMMON_ELEMENTAL_PROCELLA:   elem_id = ELEMID_EM_PROCELLA;   break;
				case EM_SUMMON_ELEMENTAL_TERREMOTUS: elem_id = ELEMID_EM_TERREMOTUS; break;
				case EM_SUMMON_ELEMENTAL_SERPENS:    elem_id = ELEMID_EM_SERPENS;    break;
			}

			// 精霊召喚中の場合は一旦解除する
			if(sd->sc.data[SC_SUMMON_ELEM].timer != -1)
				status_change_end(src,SC_SUMMON_ELEM,-1);

			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			elem_create_data(sd,elem_id,skill_get_time(skillid,skilllv)/1000);
			status_change_start(src,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case EM_ELEMENTAL_VEIL:				/* エレメンタルヴェール */
		if(sd && sd->eld) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(&sd->eld->bl,GetSkillStatusChangeTable(skillid),skilllv,skillid,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case NW_GRENADE_FRAGMENT:		/* グレネードフラグメント */
	case SH_COLORS_OF_HYUN_ROK:		/* レインボーホーン */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		if(skilllv < 7) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid)+skilllv-1,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			sc = status_get_sc(bl);
			if(sc) {
				int i;
				for(i = GetSkillStatusChangeTable(skillid); i < GetSkillStatusChangeTable(skillid)+6; i++) {
					if(sc->data[i].timer != -1) {
						status_change_end(bl,i,-1);
					}
				}
			}
		}
		break;
	case SOA_TALISMAN_OF_PROTECTION:	/* 守護符 */
		{	// 付与と同時にヒール
			int heal = skill_fix_heal(src, bl, AL_HEAL, skill_calc_heal(src, skilllv));
			heal += (1000 + skilllv * 500 + status_get_crt(src) * 5 + ((sd)? pc_checkskill(sd,SOA_TALISMAN_MASTERY) * skilllv * 50: 0)) * status_get_lv(src) / 100;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			clif_misceffect_value(bl, 312, heal);
			clif_misceffect_value(bl, 657, heal);
			unit_heal(bl,heal,0,0,0);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,heal,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SOA_SOUL_GATHERING:	/* 護魂一身 */
		if(sd) {
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			pc_addsoulenergy(sd,600000,MAX_SOULENERGY);
		}
		break;
	case SOA_SOUL_OF_HEAVEN_AND_EARTH:	/* 天地神霊 */
		if(flag&1) {
			unit_heal(bl,0,status_get_max_sp(bl),0,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SH_KI_SUL_WATER_SPRAYING:	/* タートルスプリンクラー */
		if(flag&1) {
			clif_misceffect_value(bl, 312, skill_area_temp[0]);
			clif_misceffect_value(bl, 657, skill_area_temp[0]);
			unit_heal(bl,skill_area_temp[0],0,0,0);
		} else {
			int heal = skill_fix_heal(src, bl, AL_HEAL, skill_calc_heal(src, skilllv));
			int ar = skill_get_area(skillid,skilllv);
			sc = status_get_sc(src);
			if((sd && pc_checkskill(sd,SH_COMMUNE_WITH_KI_SUL)) || (sc && sc->data[SC_TEMPORARY_COMMUNION].timer != -1)) {
				heal += (4500 + skilllv * 1500 + status_get_crt(src) * 5 + ((sd)? pc_checkskill(sd,SH_MYSTICAL_CREATURE_MASTERY) * 150: 0)) * status_get_lv(src) / 100;
				ar += 2;
			} else {
				heal += (3000 + skilllv * 1000 + status_get_crt(src) * 5 + ((sd)? pc_checkskill(sd,SH_MYSTICAL_CREATURE_MASTERY) * 100: 0)) * status_get_lv(src) / 100;
			}
			skill_area_temp[0] = heal;
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SH_MARINE_FESTIVAL_OF_KI_SUL:	/* マリンフェスティバル */
	case SH_SANDY_FESTIVAL_OF_KI_SUL:	/* サンドフェスティバル */
		if(flag&1) {
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else {
			int ar = skill_get_area(skillid,skilllv);
			sc = status_get_sc(src);
			if((sd && pc_checkskill(sd,SH_COMMUNE_WITH_KI_SUL)) || (sc && sc->data[SC_TEMPORARY_COMMUNION].timer != -1)) {
				ar += 2;
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_PARTY|1,
				skill_castend_nodamage_id);
		}
		break;
	case SH_KI_SUL_RAMPAGE:		/* タートルランページ */
		if(flag&0x20) {
			if(src != bl) {
				int ap = 2;
				if(flag&0x0f) {
					ap *= 3;
				}
				unit_heal(bl,0,0,ap,1);
			}
		} else if(flag&0x10) {
			int ar = skill_get_area(skillid,skilllv);
			if(flag&0x0f) {
				ar += 2;
			}
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_PARTY|0x20,
				skill_castend_nodamage_id);
		} else {
			int increases = 0;	// 強化フラグ
			sc = status_get_sc(src);
			if((sd && pc_checkskill(sd,SH_COMMUNE_WITH_KI_SUL)) || (sc && sc->data[SC_TEMPORARY_COMMUNION].timer != -1)) {
				increases = 1;
			}
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,increases,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;
	case SH_BLESSING_OF_MYSTICAL_CREATURES:		/* にゃんブレッシング */
		clif_skill_nodamage(src,bl,skillid,skilllv,1);
		unit_heal(bl,0,0,200,1);
		status_change_start(bl,GetSkillStatusChangeTable(skillid),skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		break;
	case SS_AKUMUKESU:			/* 悪夢消し */
		if(flag&1) {
			sc = status_get_sc(bl);
			if(sc && sc->data[SC_NIGHTMARE].timer != -1 ) {
				status_change_end(bl,SC_NIGHTMARE,-1);
			}
		} else {
			int ar = skill_get_area(skillid,skilllv);
			sc = status_get_sc(src);
			clif_skill_nodamage(src,bl,skillid,skilllv,1);
			map_foreachinarea(skill_area_sub,
				bl->m,bl->x-ar,bl->y-ar,bl->x+ar,bl->y+ar,
				BL_CHAR,src,skillid,skilllv,tick,flag|BCT_ALL|1,
				skill_castend_nodamage_id);
		}
		break;
	default:
		printf("skill_castend_nodamage_id: Unknown skill used:%d\n",skillid);
		map_freeblock_unlock();
		return 1;
	}
	map_freeblock_unlock();

	return 0;
}
