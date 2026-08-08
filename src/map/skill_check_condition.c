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
// PC用判定( 0: 使用失敗 1: 使用成功 )
int skill_check_condition2_pc(struct map_session_data *sd, struct skill_condition *cnd, int type)
{
	int i,hp,sp,ap,hp_rate,sp_rate,ap_rate,zeny,weapon,state,spiritball,coin,skilldb_id,arrow;
	int itemid[MAX_SKILL_DB_ITEM+1],amount[MAX_SKILL_DB_ITEM+1];
	int item_nocost = 0;
	int soulenergy = 0, servantweapon = 0;
	struct block_list *bl = NULL, *target = NULL;
	struct unit_data  *ud = NULL;
	struct status_change *sc = NULL, *tsc = NULL;

	nullpo_retr(0, sd);
	nullpo_retr(0, cnd);
	nullpo_retr(0, bl = &sd->bl);
	nullpo_retr(0, ud = unit_bl2ud(bl));

	target = map_id2bl( cnd->target );
	sc = status_get_sc(bl);
	if(target != NULL) tsc = status_get_sc(target);

	// チェイス、ハイド、クローキング時のスキル
	if(sd->sc.option&OPTION_HIDE) {
		switch(cnd->id) {
		case TF_HIDING:
		case AS_GRIMTOOTH:
		case RG_BACKSTAP:
		case RG_RAID:
		case NJ_KIRIKAGE:
		case NJ_SHADOWJUMP:
		case KO_YAMIKUMO:
			break;
		default:
			return 0;
		}
	}

	if(pc_ischasewalk(sd) && cnd->id != ST_CHASEWALK)	// チェイスウォーク
	 	return 0;

	// ソウルリンカーで使えないスキル
	if(pc_get_base_job(sd->s_class.job,2) == PC_JOB_SL) {
		switch(cnd->id) {
			case TK_READYSTORM:
			case TK_READYDOWN:
			case TK_READYTURN:
			case TK_READYCOUNTER:
			case TK_JUMPKICK:
				if( battle_config.soul_linker_battle_mode == 0 ||
				    (battle_config.soul_linker_battle_mode == 1 && sd->sc.data[SC_SOULLINKER].timer == -1) ) {
					clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
					return 0;
				}
				break;
			case SL_KAIZEL:		/* カイゼル */
			case SL_KAAHI:		/* カアヒ */
			case SL_KAITE:		/* カイト */
			case SL_KAUPE:		/* カウプ */
				if(target == NULL || target->type != BL_PC) {
					// 対象が人以外失敗
					clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
					return 0;
				}
				if(battle_config.soul_linker_battle_mode_ka == 0) {
					struct map_session_data *target_sd = (struct map_session_data *)target;
					if( target_sd->status.char_id == sd->status.char_id ||
					    target_sd->status.char_id == sd->status.partner_id ||
					    target_sd->status.char_id == sd->status.baby_id ||
					    sd->sc.data[SC_SOULLINKER].timer != -1 ) {
						;	// 何もしない
					} else {
						clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
						return 0;
					}
				}
				break;
		}
	}

	// ウォーグライダー中
	if(pc_iswolfmount(sd)) {
		switch(cnd->id) {
			case HT_SKIDTRAP:
			case HT_LANDMINE:
			case HT_ANKLESNARE:
			case HT_SHOCKWAVE:
			case HT_SANDMAN:
			case HT_FLASHER:
			case HT_FREEZINGTRAP:
			case HT_BLASTMINE:
			case HT_CLAYMORETRAP:
			case HT_TALKIEBOX:
			case RA_DETONATOR:
			case RA_CLUSTERBOMB:
			case RA_WUGRIDER:
			case RA_WUGDASH:
			case RA_WUGSTRIKE:
			case RA_FIRINGTRAP:
			case RA_ICEBOUNDTRAP:
				break;
			default:
				clif_skill_fail(sd,cnd->id,SKILLFAIL_MSGID,0x75e,0);	// 騎乗生物に騎乗中は、スキル使用ができません。
				return 0;
		}
	}

	// 魔導ギア搭乗時
	if(pc_isgear(sd)) {
		switch(cnd->id) {
		// マーチャント系スキル
		case MC_IDENTIFY:			// アイテム鑑定
		case MC_VENDING:			// 露店開設
		case MC_MAMMONITE:			// メマーナイト
		// ブラックスミス系スキル
		case BS_REPAIRWEAPON:		// 武器修理
		case BS_HAMMERFALL:			// ハンマーフォール
		case BS_ADRENALINE:			// アドレナリンラッシュ
		case BS_WEAPONPERFECT:		// ウェポンパーフェクション
		case BS_OVERTHRUST:			// オーバートラスト
		case BS_MAXIMIZE:			// マキシマイズパワー
		case BS_ADRENALINE2:		// フルアドレナリンラッシュ
		case BS_GREED:				// グリード
		// ホワイトスミス系スキル
		case WS_MELTDOWN:			// メルトダウン
		case WS_CARTBOOST:			// カートブースト
		case WS_WEAPONREFINE:		// 武器精錬
		case WS_CARTTERMINATION:	// カートターミネーション
		case WS_OVERTHRUSTMAX:		// オーバートラストマックス
		// メカニック追加スキル
		case NC_MAGMA_ERUPTION:		//マグマイラプション
		// マイスター追加スキル
		case MT_MIGHTY_SMASH:		// マイティスマッシュ
		// その他
		case AL_TELEPORT:			// テレポート
		case ALL_BUYING_STORE:		// 買取露店開設
			break;
		default:
			// メカニックスキルはまとめて判定
			if(cnd->id >= NC_BOOSTKNUCKLE && cnd->id <= NC_DISJOINT)
				break;
			// マイスタースキルはまとめて判定
			if(cnd->id >= MT_AXE_STOMP && cnd->id <= MT_SUMMON_ABR_INFINITY)
				break;
			clif_skill_fail(sd,cnd->id,SKILLFAIL_MADOGEAR_RIDE,0,0);
			return 0;
		}
	}

	// GMハイド中で、コンフィグでハイド中攻撃不可 GMレベルが指定より大きい場合
	if(sd->sc.option&OPTION_SPECIALHIDING && battle_config.hide_attack == 0 && pc_isGM(sd) < battle_config.gm_hide_attack_lv)
		return 0;	// 隠れてスキル使うなんて卑怯なGMデスネ

	if(battle_config.gm_skilluncond > 0 && pc_isGM(sd) >= battle_config.gm_skilluncond)
		return 1;
	// 点穴-快-は睡眠状態では使えない
	if( cnd->id  == SR_GENTLETOUCH_CURE ) {
		if( sd->sc.opt1 == OPT1_SLEEP ) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_CONDITION,0,0);
			return 0;
		}
	} else {
		if(sd->sc.opt1 > OPT1_NORMAL && sd->sc.opt1 != OPT1_BURNNING) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_CONDITION,0,0);
			return 0;
		}
	}
	if(pc_is90overweight(sd)) {
		clif_skill_fail(sd,cnd->id,SKILLFAIL_WEIGHTOVER,0,0);
		return 0;
	}

	if(cnd->id == sd->skill_menu.id)
		return 0;

	// 駆け足時にスキルを使った場合終了
	// 再度の駆け足か飛び蹴りは除外
	if(sd->sc.data[SC_RUN].timer != -1 && cnd->id != TK_RUN && cnd->id != TK_JUMPKICK)
		status_change_end(bl,SC_RUN,-1);

	// ウォーグダッシュ中のスキル使用
	if(sd->sc.data[SC_WUGDASH].timer != -1 && cnd->id != RA_WUGDASH)
		status_change_end(bl,SC_WUGDASH,-1);

	/* アイテムの場合の判定 */
	if(sd->skill_item.id == cnd->id) {
		if(type == 0)			// 初回の呼び出し（unit.cより）なら無条件で許可
			return 1;
		sd->skill_item.id   = -1;
		sd->skill_item.lv   = -1;
		if( !sd->skill_item.flag )	// フラグないなら許可
			return 1;
	}

	skilldb_id = skill_get_skilldb_id(cnd->id);
	hp         = skill_get_hp(cnd->id, cnd->lv);	/* 消費HP */
	sp         = skill_get_sp(cnd->id, cnd->lv);	/* 消費SP */
	ap         = skill_get_ap(cnd->id, cnd->lv);	/* 消費AP */
	hp_rate    = (cnd->lv <= 0)? 0: skill_db[skilldb_id].hp_rate[cnd->lv-1];
	sp_rate    = (cnd->lv <= 0)? 0: skill_db[skilldb_id].sp_rate[cnd->lv-1];
	ap_rate    = (cnd->lv <= 0)? 0: skill_db[skilldb_id].ap_rate[cnd->lv-1];
	zeny       = skill_get_zeny(cnd->id,cnd->lv);
	weapon     = skill_db[skilldb_id].weapon;
	state      = skill_db[skilldb_id].state;
	spiritball = (cnd->lv <= 0)? 0: skill_db[skilldb_id].spiritball[cnd->lv-1];
	coin       = (cnd->lv <= 0)? 0: skill_db[skilldb_id].coin[cnd->lv-1];
	arrow      = skill_get_arrow_cost(cnd->id,cnd->lv);

	for(i=0; i<MAX_SKILL_DB_ITEM; i++) {
		itemid[i] = skill_db[skilldb_id].itemid[i];
		amount[i] = skill_db[skilldb_id].amount[i];
	}
	// スキルLv毎の消費アイテム
	if(cnd->lv > 0 && cnd->lv <= MAX_SKILL_LEVEL) {
		itemid[i] = skill_db[skilldb_id].lv_itemid[cnd->lv-1];
		amount[i] = skill_db[skilldb_id].lv_amount[cnd->lv-1];
	}
	else {
		itemid[i] = 0;
		amount[i] = 0;
	}

	if(hp_rate > 0)
		hp += sd->status.hp * hp_rate / 100;
	else
		hp += sd->status.max_hp * abs(hp_rate) / 100;
	if(sp_rate > 0)
		sp += sd->status.sp * sp_rate / 100;
	else
		sp += sd->status.max_sp * abs(sp_rate) / 100;
	if(ap_rate > 0)
		ap += sd->status.ap * ap_rate / 100;
	else
		ap += sd->status.max_ap * abs(ap_rate) / 100;

	if(sd->skill_used.id == BD_ENCORE && cnd->id == sd->skill_dance.id)	// アンコール時はSP消費が半分
		sp /= 2;
	if(sd->skill_used.id == TR_RETROSPECTION && cnd->id == sd->skill_4thdance.id)	// 回想時はSP消費が半分
		sp /= 2;
	if(sd->sc.data[SC_RECOGNIZEDSPELL].timer!=-1)		// リゴグナイズドスペル時は消費SP25%増加
		sp = sp * 125 / 100;
	if(sd->sc.data[SC_UNLIMITED_HUMMING_VOICE].timer != -1) {	// エンドレスハミングボイス時は消費SP～15%増加
		int cost = 15;
		cost -= sd->sc.data[SC_UNLIMITED_HUMMING_VOICE].val4 * 3;
		if(cost > 0)
			sp = sp * (100 + cost) / 100;
	}
	if(sd->sc.data[SC_HANDICAPSTATE_DEPRESSION].timer!=-1)		// 憂鬱時は消費SP3倍
		sp *= 3;
	if(sd->skill_addspcost.count > 0) {		// カードによるSP使用量増加
		for(i=0; i<sd->skill_addspcost.count; i++) {
			if(cnd->id == sd->skill_addspcost.id[i])
				sp += sd->skill_addspcost.rate[i];
		}
	}

#ifndef PRE_RENEWAL
	if(spiritball > 0)
		sd->spiritball.old = 0;
#endif

	// ソウルリーパーのスキルはspiritball要求をsoulenergyに置き換える
	if(cnd->id >= SP_SOULGOLEM && cnd->id <= SP_KAUTE && spiritball > 0) {
		soulenergy = spiritball;
		spiritball = 0;
	}

	// ドラゴンナイトのスキルはspiritball要求をservantweaponに置き換える
	if(cnd->id >= DK_SERVANTWEAPON && cnd->id <= DK_STORMSLASH && spiritball > 0) {
		servantweapon = spiritball;
		spiritball = 0;
	}

	switch( cnd->id ) {
	case SL_SMA:	/* エスマ */
		if(!(type&1) && sd->sc.data[SC_SMA].timer==-1){	// エスマ詠唱可能状態
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case CG_LONGINGFREEDOM:
		// 合奏以外使えない
		if(sd->sc.data[SC_DANCING].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		} else {
			int dance_id = sd->sc.data[SC_DANCING].val1;
			if( (dance_id >= BA_WHISTLE && dance_id <= BA_APPLEIDUN) ||
			    (dance_id >= DC_HUMMING && dance_id <= DC_SERVICEFORYOU) ||
			    dance_id == CG_MOONLIT || dance_id == CG_HERMODE )
			{
				clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
				return 0;
			}
		}
		break;
	case CG_MOONLIT:			/* 月明りの下で */
		{
			int x1,x2,y1,y2,j;
			int range = skill_get_unit_range(cnd->id,cnd->lv)+1;
			x1 = bl->x - range;
			x2 = bl->x + range;
			y1 = bl->y - range;
			y2 = bl->y + range;
			// 終始点がマップ外
			if(x1<0 || x2>=map[bl->m].xs-1 || y1<0 || y2>=map[bl->m].ys-1)
				return 0;

			for(i=x1;i<=x2;i++)
			{
				for(j=y1;j<=y2;j++)
				{
					if(map_getcell(bl->m,i,j,CELL_CHKNOPASS))
						return 0;
				}
			}
		}
		// fall through
	case BD_LULLABY:				/* 子守歌 */
	case BD_RICHMANKIM:				/* ニヨルドの宴 */
	case BD_ETERNALCHAOS:			/* 永遠の混沌 */
	case BD_DRUMBATTLEFIELD:		/* 戦太鼓の響き */
	case BD_RINGNIBELUNGEN:			/* ニーベルングの指輪 */
	case BD_ROKISWEIL:				/* ロキの叫び */
	case BD_INTOABYSS:				/* 深淵の中に */
	case BD_SIEGFRIED:				/* 不死身のジークフリード */
	case BD_RAGNAROK:				/* 神々の黄昏 */
		{
			int range=1;
			int c=0;
			map_foreachinarea(skill_check_condition_char_sub,bl->m,
				bl->x-range,bl->y-range,
				bl->x+range,bl->y+range,BL_PC,sd,&c,cnd);
			// ダンス開始位置(合奏用)
			sd->dance.x = bl->x;
			sd->dance.y = bl->y;
			if(c<1){
				clif_skill_fail(sd,cnd->id,SKILLFAIL_PARTNER,0,0);
				return 0;
			}else if(c==0x7fffffff){ // 相方不要設定だった
				;
			}else{
				cnd->lv = (c + cnd->lv)/2;
			}
		}
		break;
	case SA_ELEMENTWATER:	// 水
	case SA_ELEMENTGROUND:	// 土
	case SA_ELEMENTFIRE:	// 火
	case SA_ELEMENTWIND:	// 風
		{
			// PC -> PCだけ禁止する
			if( target && target->type == BL_PC )
			{
				clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
				return 0;
			}
		}
		break;
	case RA_WUGDASH:	// ウォーグダッシュ
		if(!pc_iswolfmount(sd)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SP_SWHOO:	/* エスフ */
		if(!(type&1) && sd->sc.data[SC_SWHOO].timer == -1){	// エスフ詠唱可能状態
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	}

	// 特殊な消費処理
	switch(cnd->id)
	{
		case MC_MAMMONITE:	/* メマーナイト */
			if(pc_checkskill(sd,BS_UNFAIRLYTRICK)>0)
				zeny = zeny*90/100;
			break;
		case AL_HOLYLIGHT:	/* ホーリーライト */
			// プリーストの魂時はSP消費量増加
			if(sd->sc.data[SC_PRIEST].timer!=-1)
				sp = sp * 5;
			break;
#ifndef PRE_RENEWAL
		case AS_SONICBLOW:	/* ソニックブロー */
			if(sd->sc.data[SC_ASSASIN].timer != -1)
				sp = sp * 2;
			break;
#endif
		case SL_SMA:		/* エスマ */
		case SL_STUN:		/* エスタン */
		case SL_STIN:		/* エスティン */
			{
				int kaina_lv = pc_checkskill(sd,SL_KAINA);

				if(kaina_lv==0)
					break;
				if(sd->status.base_level>=90)
					sp -= sp*7*kaina_lv/100;
				else if(sd->status.base_level>=80)
					sp -= sp*5*kaina_lv/100;
				else if(sd->status.base_level>=70)
					sp -= sp*3*kaina_lv/100;
			}
			break;
		case MO_CHAINCOMBO:
		case MO_COMBOFINISH:
		case CH_TIGERFIST:
		case CH_CHAINCRUSH:
			// モンクの魂　連携スキルのSP消費減少
			if(sd->sc.data[SC_MONK].timer!=-1)
				sp -= sp*sd->sc.data[SC_MONK].val1/10;
			break;
		case NJ_ZENYNAGE:
			if(!(type&1)) {
				if(zeny>=2) {
					zeny /= 2;
					sd->zenynage_damage = zeny + atn_rand()%zeny;
					zeny = sd->zenynage_damage;
				} else if(cnd->lv > 0) {
					// お金消費無しのデフォルトダメージ
					sd->zenynage_damage = 500*cnd->lv + atn_rand()%(500*cnd->lv);
				}
			} else {
				zeny = sd->zenynage_damage;
			}
			break;
		case MG_NAPALMBEAT:
		case MG_SOULSTRIKE:
		case HW_NAPALMVULCAN:
		case WL_SOULEXPANSION:
		case WL_WHITEIMPRISON:
			// テレキネシスインテンス
			if(sd->sc.data[SC_TELEKINESIS_INTENSE].timer != -1)
				sp -= sp*sd->sc.data[SC_TELEKINESIS_INTENSE].val3/100;
			break;
		case KO_MUCHANAGE:
			if(!(type&1) && cnd->lv > 0) {
				sd->zenynage_damage = 5000*cnd->lv + atn_rand()%(5000*cnd->lv);
			}
			break;
		case WH_CRESCIVE_BOLT:		/* クレッシブボルト */
			if(sd->sc.data[SC_CRESCIVEBOLT].timer != -1) {
				if(sd->sc.data[SC_CRESCIVEBOLT].val1 == 1) {
					sp += sp * 20 / 100;
				} else if(sd->sc.data[SC_CRESCIVEBOLT].val1 == 2) {
					sp += sp * 40 / 100;
				} else {
					sp += sp * 60 / 100;
				}
			}
			break;
	}
#ifndef PRE_RENEWAL
	// バードとダンサーの魂
	if(sd->sc.data[SC_BARDDANCER].timer != -1)
		sp += sp * 50 / 100;	/* 消費SP増加 */
	// ウィザードの魂
	if(sd->sc.data[SC_WIZARD].timer != -1) {
		for(i=0; i<MAX_SKILL_DB_ITEM; i++) {
			if(itemid[i] <= 0)
				continue;
			if(itemid[i] == 717)
				sp += sp * 50 / 100;	/* 消費SP増加 */
		}
	}
#endif

	if(sd->dsprate!=100)
		sp=sp*sd->dsprate/100;	/* 消費SP修正 */

	// マスカレード：レイジネス
	if(sd->sc.data[SC__LAZINESS].timer != -1)
		sp += sd->sc.data[SC__LAZINESS].val1 * 10;	/* 消費SP増加 */

	// マスカレード：アンラッキー
	if(sd->sc.data[SC__UNLUCKY].timer != -1)
		zeny += 1000;			/* 消費zeny増加 */

	switch(cnd->id) {
	case SA_CASTCANCEL:
	case SO_SPELLFIST:
		if(ud->skilltimer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case BS_MAXIMIZE:		/* マキシマイズパワー */
	case NV_TRICKDEAD:		/* 死んだふり */
	case TF_HIDING:			/* ハイディング */
	case AS_CLOAKING:		/* クローキング */
	case CR_AUTOGUARD:		/* オートガード */
	case PA_GOSPEL:			/* ゴスペル */
	case ST_CHASEWALK:		/* チェイスウォーク */
	case NPC_INVISIBLE:		/* インビジブル */
	case TK_RUN:			/* タイリギ */
	case GS_GATLINGFEVER:		/* ガトリングフィーバー */
	case CR_SHRINK:			/* シュリンク */
	case ML_AUTOGUARD:
	case KO_YAMIKUMO:		/* 闇雲 */
	case IG_GUARD_STANCE:		/* ガードスタンス */
	case IG_ATTACK_STANCE:		/* アタックスタンス */
		{
			int sc_type = GetSkillStatusChangeTable(cnd->id);
			if(sc_type > 0 && sd->sc.data[sc_type].timer != -1)
				sp = 0;	// 解除する場合はSP消費しない
		}
		break;
	case AL_TELEPORT:
		{
			int alive;
			if(map[bl->m].flag.noteleport) {
				alive = 0;
			} else {
				alive = 1;
				map_foreachinarea(skill_landprotector,bl->m,bl->x,bl->y,bl->x,bl->y,BL_SKILL,AL_TELEPORT,&alive);
			}
			if(!alive) {
				clif_skill_teleportmessage(sd,0);
				return 0;
			}
		}
		break;
	case AL_WARP:
		if(map[bl->m].flag.noportal) {
			clif_skill_teleportmessage(sd,0);
			return 0;
		}
		break;
	case MO_CALLSPIRITS:		/* 気功 */
		{
			int max = (sd->s_class.job == PC_JOB_MO || sd->s_class.job == PC_JOB_SR)? cnd->lv: skill_get_max(cnd->id);
			if(sd->sc.data[SC_RAISINGDRAGON].timer != -1)
				max += sd->sc.data[SC_RAISINGDRAGON].val1;
			if(sd->spiritball.num >= max) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		}
		break;
	case MO_BODYRELOCATION:		/* 残影 */
		if(sd->sc.data[SC_EXPLOSIONSPIRITS].timer != -1)
			spiritball = 0;
		break;
	case CH_SOULCOLLECT:		/* 練気功 */
		if(battle_config.soulcollect_max_fail) {
			int max = (sd->s_class.job == PC_JOB_MO || sd->s_class.job == PC_JOB_SR)? pc_checkskill(sd,MO_CALLSPIRITS): skill_get_max(MO_CALLSPIRITS);
			if(sd->sc.data[SC_RAISINGDRAGON].timer != -1)
				max += sd->sc.data[SC_RAISINGDRAGON].val1;
			if(sd->spiritball.num >= max) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		}
		break;
	case MO_FINGEROFFENSIVE:	/* 指弾 */
		if (sd->spiritball.num > 0 && sd->spiritball.num < spiritball) {
			spiritball = sd->spiritball.num;
			sd->spiritball.old = sd->spiritball.num;
		} else {
			sd->spiritball.old = cnd->lv;
		}
		break;
	case MO_CHAINCOMBO:		/* 連打掌 */
		if(sd->sc.data[SC_BLADESTOP].timer==-1){
			if(sd->sc.data[SC_COMBO].timer == -1 || sd->sc.data[SC_COMBO].val1 != MO_TRIPLEATTACK)
				return 0;
		}
		break;
	case MO_COMBOFINISH:		/* 猛龍拳 */
		if(sd->sc.data[SC_COMBO].timer == -1 || sd->sc.data[SC_COMBO].val1 != MO_CHAINCOMBO)
			return 0;
#ifndef PRE_RENEWAL
		sd->spiritball.old = sd->spiritball.num;
#endif
		break;
	case CH_TIGERFIST:		/* 伏虎拳 */
		if(sd->sc.data[SC_COMBO].timer == -1 || (sd->sc.data[SC_COMBO].val1 != MO_COMBOFINISH && sd->sc.data[SC_COMBO].val1 != CH_CHAINCRUSH))
			return 0;
#ifndef PRE_RENEWAL
		sd->spiritball.old = sd->spiritball.num;
#endif
		break;
	case CH_CHAINCRUSH:		/* 連柱崩撃 */
		if(sd->sc.data[SC_COMBO].timer == -1 || (sd->sc.data[SC_COMBO].val1 != MO_COMBOFINISH && sd->sc.data[SC_COMBO].val1 != CH_TIGERFIST))
			return 0;
#ifndef PRE_RENEWAL
		sd->spiritball.old = sd->spiritball.num;
#endif
		break;
	case MO_EXTREMITYFIST:		/* 阿修羅覇鳳拳 */
		if((sd->sc.data[SC_COMBO].timer != -1 && (sd->sc.data[SC_COMBO].val1 == MO_COMBOFINISH || sd->sc.data[SC_COMBO].val1 == CH_CHAINCRUSH)) || sd->sc.data[SC_BLADESTOP].timer!=-1)
		{
			if(sd->sc.data[SC_COMBO].timer != -1 && sd->sc.data[SC_COMBO].val1 == CH_CHAINCRUSH)
				spiritball = 1;
			else
				spiritball--;	// =4でも良いが
			if(spiritball<0)
				spiritball=0;
		}
		break;
	case TK_STORMKICK:		/* フェオリチャギ */
	case TK_DOWNKICK:		/* ネリョチャギ */
	case TK_TURNKICK:		/* トルリョチャギ */
	case TK_COUNTER:		/* アプチャオルリギ */
		if(sd->sc.data[SC_TKCOMBO].timer == -1 ||
		   (sd->sc.data[SC_TKCOMBO].val4 != TK_MISSION && sd->sc.data[SC_TKCOMBO].val1 != cnd->id) ||
		   (sd->sc.data[SC_TKCOMBO].val4 == TK_MISSION && sd->sc.data[SC_TKCOMBO].val1 == cnd->id)	// ランカーは直前のスキルと同一ならコンボ終了
		) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_COMBOSKILL,0,0);
			status_change_end(&sd->bl,SC_TKCOMBO,-1);
			return 0;
		}
		break;
	case BD_ADAPTATION:		/* アドリブ */
		{
			struct skill_unit_group *group=NULL;
			if(
				sd->sc.data[SC_DANCING].timer==-1 ||
				((group=map_id2sg(sd->sc.data[SC_DANCING].val2)) &&
				(skill_get_time(sd->sc.data[SC_DANCING].val1,group->skill_lv) -
				sd->sc.data[SC_DANCING].val3*1000) <= skill_get_time2(cnd->id,cnd->lv))
			){
				// ダンス中で使用後5秒以上のみ？
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		}
		break;
	case PR_BENEDICTIO:		/* 聖体降福 */
		{
			int range=1;
			int c=0;
			if(!(type&1)){
				map_foreachinarea(skill_check_condition_char_sub,bl->m,
					bl->x-range,bl->y-range,
					bl->x+range,bl->y+range,BL_PC,sd,&c,cnd);
				if(c<2){
					clif_skill_fail(sd,cnd->id,SKILLFAIL_PARTNER,0,0);
					return 0;
				}
			}else{
				map_foreachinarea(skill_check_condition_use_sub,bl->m,
					bl->x-range,bl->y-range,
					bl->x+range,bl->y+range,BL_PC,sd,&c);
			}
		}
		break;
	case WE_CALLPARTNER:		/* あなたに逢いたい */
		if(!sd->status.partner_id){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case WE_CALLPARENT:		/* ママ、パパ、来て */
		if(!sd->status.parent_id[0] && !sd->status.parent_id[1]){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case WE_CALLBABY:		/* 坊や、いらっしゃい */
		if(!sd->status.baby_id){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case AM_CANNIBALIZE:		/* バイオプラント */
	case AM_SPHEREMINE:		/* スフィアーマイン */
		if(type&1){
			const int summons[5] = { 1589, 1579, 1575, 1555, 1590 };
			int maxcount = skill_get_maxcount(cnd->id,cnd->lv);

			if(battle_config.pc_land_skill_limit && maxcount>0) {
				int c,n=0;
				do{
					c = map_foreachinarea(
						skill_check_condition_mob_master_sub, bl->m, 0, 0, map[bl->m].xs,
						map[bl->m].ys, BL_MOB, bl->id,
						(cnd->id==AM_CANNIBALIZE)? summons[n]: 1142
					);
					// 今回召喚するmobとは別の種類のmobを召喚していないかもチェック
					if((cnd->id==AM_CANNIBALIZE && ((c > 0 && n != cnd->lv-1) || (n == cnd->lv-1 && c >= maxcount)))
						|| (cnd->id==AM_SPHEREMINE && c >= maxcount)){
						clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
						return 0;
					}
				}while(cnd->id != AM_SPHEREMINE && ++n < 5);
			}
		}
		break;
	case AM_CALLHOMUN:			/* コールホムンクルス */
		// 作成済みで安息時
		if(sd->hom.homun_id > 0 && sd->status.homun_id == sd->hom.homun_id && !sd->hom.incubate)
			break;
		if(sd->hd) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		if(sd->hom.homun_id > 0) {	// 作成済みホムが居る時にエンブリオ持ってたら失敗
			for(i=0; i<MAX_INVENTORY; i++) {
				if(sd->status.inventory[i].nameid == 7142) {
					clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
					return 0;
				}
			}
		}
		break;
	case AM_REST:			/* 安息 */
		if(!homun_isalive(sd) || status_get_hp(&sd->hd->bl) < sd->hd->max_hp * 80 / 100) {
			// ホムのHPがMHPの80%以上であること
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case AM_RESURRECTHOMUN:			/* リザレクションホムンクルス */
		if(sd->hd || sd->hom.hp > 0) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case WZ_FIREPILLAR:
		if(cnd->lv <= 5)	// no gems required at level 1-5
			item_nocost = 1;
		// fall through
	case PF_SPIDERWEB:		/* スパイダーウェブ */
	case MG_FIREWALL:		/* ファイアーウォール */
	case GN_THORNS_TRAP:	/* ソーントラップ */
	case GN_WALLOFTHORN:	/* ソーンウォール */
		/* 数制限 */
		if(battle_config.pc_land_skill_limit) {
			int maxcount = skill_get_maxcount(cnd->id,cnd->lv);
			if(maxcount > 0 && skill_count_unitgroup(ud,cnd->id) >= maxcount) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_MORESKILL,0,0);
				return 0;
			}
		}
		break;
	case PF_HPCONVERSION:		/* 生命力変換 */
		if(sd->status.sp >= sd->status.max_sp)
			return 0;
		break;
	case PA_PRESSURE:		/* プレッシャー */
		if(status_get_class(target) == MOBID_EMPERIUM) {	// エンペは使用不可
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		break;
	case CR_DEVOTION:		/* ディボーション */
		if(target && target->type == BL_PC) {
			for(i = 0; i < cnd->lv && i < 5; i++) {
				if(sd->dev.val1[i] <= 0)
					break;
			}
			if(i >= cnd->lv || i >= 5) {
				// 定員オーバー
				clif_skill_fail(sd,cnd->id,SKILLFAIL_MORESKILL,0,0);
				return 0;
			}
		}
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
		if(sd->sc.data[SC_LONGINGFREEDOM].timer!=-1)
			return 0;
		break;
	case CG_HERMODE:			/* ヘルモードの杖 */
		if(sd->sc.data[SC_LONGINGFREEDOM].timer!=-1)
			return 0;
		if(battle_config.hermode_gvg_only && map[bl->m].flag.gvg==0){	// シーズ以外使えない
			clif_skill_fail(sd,cnd->id,SKILLFAIL_GVGONLY,0,0);
			return 0;
		}
		// WPチェック？
		if(battle_config.hermode_wp_check && !skill_hermode_wp_check(bl))
		{
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SG_SUN_WARM:
		if(sd->sc.data[SC_MIRACLE].timer==-1)
		{
			if(bl->m != sd->feel_index[0]){
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		}
		break;
	case SG_SUN_COMFORT:
		if(sd->sc.data[SC_MIRACLE].timer==-1)
		{
			if(bl->m == sd->feel_index[0] && (battle_config.allow_skill_without_day || is_day_of_sun()))
				break;
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SG_MOON_WARM:
		if(sd->sc.data[SC_MIRACLE].timer==-1)
		{
			if(bl->m != sd->feel_index[1]){
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		}
		break;
	case SG_MOON_COMFORT:
		if(sd->sc.data[SC_MIRACLE].timer==-1)
		{
			if(bl->m == sd->feel_index[1] && (battle_config.allow_skill_without_day || is_day_of_moon()))
				break;
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SG_STAR_WARM:
		if(sd->sc.data[SC_MIRACLE].timer==-1)
		{
			if(bl->m != sd->feel_index[2]){
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		}
		break;
	case SG_STAR_COMFORT:
		if(sd->sc.data[SC_MIRACLE].timer==-1)
		{
			if(bl->m == sd->feel_index[2] && (battle_config.allow_skill_without_day || is_day_of_star()))
				break;
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SG_HATE:
		if(status_get_class(target) == MOBID_EMPERIUM) {	// エンペは登録不可
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		break;
	case SG_FUSION:
		if(sd->sc.data[SC_FUSION].timer != -1) {	// 解除するときはsp消費なし
			sp = 0;
		}
		if(sd->sc.data[SC_STAR].timer == -1) {	// ケンセイの魂状態
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case PR_REDEMPTIO:
		if(battle_config.redemptio_penalty_type) {
			atn_bignumber exp = pc_nextbaseexp(sd);
			if(exp <= 0) {
				// オーラの場合は現在のレベルに必要な経験値を参照する
				sd->status.base_level--;
				exp = pc_nextbaseexp(sd);
				sd->status.base_level++;
				if(exp <= 0) {
					// それでもexpが未設定なら許可
					break;
				}
			}
			if(sd->status.base_exp < exp / 100 * battle_config.death_penalty_base / 100) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_EXP,0,0);
				return 0;
			}
		}
		break;
	case GS_GLITTERING:		/* フリップザコイン */
		if(sd->coin.num >= MAX_COIN) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case GS_FLING:		/* フライング */
		if(sd->coin.num < coin) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_COIN,coin,0);
			return 0;
		}
		coin = 0;	// コインは状態付与時に消費させる
		break;
	case GS_MADNESSCANCEL:	/* マッドネスキャンセラー */
		if(sd->sc.data[SC_ADJUSTMENT].timer != -1 || sd->sc.data[SC_HEAT_BARREL].timer != -1 || sd->sc.data[SC_P_ALTER].timer != -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		else if(sd->sc.data[SC_MADNESSCANCEL].timer != -1) {
			// 解除する場合は消費しない
			sp = 0;
			coin = 0;
		}
		break;
	case GS_ADJUSTMENT:		/* アジャストメント */
		if(sd->sc.data[SC_MADNESSCANCEL].timer != -1 || sd->sc.data[SC_HEAT_BARREL].timer != -1 || sd->sc.data[SC_P_ALTER].timer != -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case HT_POWER:			/* ビーストストレイフィング */
		if(sd->sc.data[SC_DOUBLE].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case RK_GIANTGROWTH:	// ジャイアントグロース
		if(pc_checkskill(sd,RK_RUNEMASTERY) < 1) {		// ルーンマスタリーLv1が必要
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case RK_VITALITYACTIVATION:	// バイタリティアクティベーション
		if(pc_checkskill(sd,RK_RUNEMASTERY) < 2) {		// ルーンマスタリーLv2が必要
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case RK_STORMBLAST:		// ストームブラスト
		if(pc_checkskill(sd,RK_RUNEMASTERY) < 3) {		// ルーンマスタリーLv3が必要
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case RK_STONEHARDSKIN:	// ストーンハードスキン
		if(pc_checkskill(sd,RK_RUNEMASTERY) < 4) {		// ルーンマスタリーLv4が必要
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case RK_FIGHTINGSPIRIT:	// ファイティングスピリット
		if(pc_checkskill(sd,RK_RUNEMASTERY) < 5) {		// ルーンマスタリーLv5が必要
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case RK_ABUNDANCE:		// アバンダンス
		if(pc_checkskill(sd,RK_RUNEMASTERY) < 6) {		// ルーンマスタリーLv6が必要
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case RK_CRUSHSTRIKE:	// クラッシュストライク
		if(pc_checkskill(sd,RK_RUNEMASTERY) < 7) {		// ルーンマスタリーLv7が必要
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case RK_REFRESH:	// リフレッシュ
		if(pc_checkskill(sd,RK_RUNEMASTERY) < 8) {		// ルーンマスタリーLv8が必要
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case RK_MILLENNIUMSHIELD:	// ミレニアムシールド
		if(pc_checkskill(sd,RK_RUNEMASTERY) < 9) {		// ルーンマスタリーLv9が必要
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case RK_LUXANIMA:	// ラクスアニマ
		if(pc_checkskill(sd,RK_RUNEMASTERY) < 10) {		// ルーンマスタリーLv10が必要
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case GC_WEAPONBLOCKING:	/* ウェポンブロッキング */
		if(sd->sc.data[SC_WEAPONBLOCKING].timer != -1)
			sp = 0;		// 解除する場合はSP消費しない
		break;
	case GC_COUNTERSLASH:		/* カウンタースラッシュ */
		if(sd->sc.data[SC_WEAPONBLOCK_ON].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_GC_WEAPONBLOCKING,0,0);
			return 0;
		}
		break;
	case GC_WEAPONCRUSH:		/* ウェポンクラッシュ */
		if(sd->sc.data[SC_WEAPONBLOCKING_POSTDELAY].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_GC_WEAPONBLOCKING,0,0);
			return 0;
		}
		break;
	case GC_VENOMPRESSURE:		/* ベナムプレッシャー */
	case GC_POISONSMOKE:		/* ポイズンスモーク */
		if(sd->sc.data[SC_POISONINGWEAPON].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_GC_POISONINGWEAPON,0,0);
			return 0;
		}
		break;
	case GC_CLOAKINGEXCEED:	/* クローキングエクシード */
		if(sd->sc.data[SC_CLOAKINGEXCEED].timer != -1)
			sp = 0;		// 解除する場合はSP消費しない
		break;
	case GC_HALLUCINATIONWALK:	/* ハルシネーションウォーク */
		if(sd->sc.data[SC_HALLUCINATIONWALK].timer != -1 || sd->sc.data[SC_HALLUCINATIONWALK_POSTDELAY].timer != -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case GC_CROSSRIPPERSLASHER:		/* クロスリッパースラッシャー */
		if(sd->sc.data[SC_ROLLINGCUTTER].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case AB_ANCILLA:			/* アンシラ */
		{
			int idx = pc_search_inventory(sd,12333);
			if(idx >= 0 && sd->status.inventory[idx].amount >= 3 ) {	/* 作成前に所持限界数を超えている */
				clif_skill_fail(sd,cnd->id,SKILLFAIL_ANCILLAOVER,0,0);
				return 0;
			}
		}
		break;
	case WL_TETRAVORTEX:		/* テトラボルテックス */
		{
			int c = 0;
			for(i = 0; i < 5; i++) {
				if(sd->sc.data[SC_SUMMONBALL1 + i].timer != -1) {
					c++;
				}
			}
			if(c < 4) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_SUMMON_NOTHING,0,0);
				return 0;
			}
		}
		break;
	case WL_SUMMONFB:		/* サモンファイアボール */
	case WL_SUMMONBL:		/* サモンボールライトニング */
	case WL_SUMMONWB:		/* サモンウォーターボール */
	case WL_SUMMONSTONE:	/* サモンストーン */
		for(i = 0; i < 5; i++) {
			if(sd->sc.data[SC_SUMMONBALL1 + i].timer == -1)
				break;
		}
		if(i >= 5) {	// 召喚数がいっぱい
			clif_skill_fail(sd,cnd->id,SKILLFAIL_SUMMON_OVER,0,0);
			return 0;
		}
		break;
	case RA_CAMOUFLAGE:		/* カモフラージュ */
		if(sd->sc.data[SC_CAMOUFLAGE].timer != -1) {
			sp = 0;		// 解除する場合はSP消費しない
		}
		// Lv1～2は壁付近チェック
		else if(cnd->lv < 3) {
			int i;
			for(i=0; i<8;i++){
				if(map_getcell(bl->m,bl->x+dirx[i],bl->y+diry[i],CELL_CHKNOPASS))
					break;
			}
			if(i >= 8) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_NEERWALL,0,0);
				return 0;
			}
		}
		break;
	case NC_PILEBUNKER:			/* パイルバンカー */
		{
			// パイルバンカーの装備チェック
 			static const int pile_item[] = { 1549, 16044, 16045, 16046 };		// パイルバンカー系列の装備品
			static const int pile_max = sizeof(pile_item)/sizeof(pile_item[0]);
			for(i = 0; i < pile_max; i++) {
				if(pc_equippeditem(sd,pile_item[i]))
					break;	// 装備していたら判定OK
			}
			if(i >= pile_max) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_NEED_EQUIP,0,pile_item[0]);
				return 0;
			}
		}
		break;
	case NC_HOVERING:			/* ホバーリング */
		// ホバーリングブースターを装備しているか判定
		if(pc_equippeditem(sd,2801) == 0) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_NEED_EQUIP,0,2801);
			return 0;
		}
		break;
	case NC_SILVERSNIPER:		/* FAW シルバースナイパー */
		if(type&1){
			int maxcount = skill_get_maxcount(cnd->id,cnd->lv);

			if(battle_config.pc_land_skill_limit && maxcount > 0) {
				int c = map_foreachinarea(
					skill_check_condition_mob_master_sub, bl->m, 0, 0, map[bl->m].xs,
					map[bl->m].ys, BL_MOB, bl->id, 2042
				);
				if(c >= maxcount){
					clif_skill_fail(sd,cnd->id,SKILLFAIL_MORESKILL,0,0);
					return 0;
				}
			}
		}
		break;
	case NC_MAGICDECOY:      /* FAW マジックデコイ */
		if(type&1){
			const int mob_id[4] = {
				2043, 2044, 2046, 2045
			};
			int maxcount = skill_get_maxcount(cnd->id,cnd->lv);

			if(battle_config.pc_land_skill_limit && maxcount > 0) {
				int c = 0;
				for(i = 0; i < 4; i++) {
					c += map_foreachinarea(
						skill_check_condition_mob_master_sub, bl->m, 0, 0, map[bl->m].xs,
						map[bl->m].ys, BL_MOB, bl->id, mob_id[i]
					);
				}
				if(c >= maxcount){
					clif_skill_fail(sd,cnd->id,SKILLFAIL_MORESKILL,0,0);
					return 0;
				}
			}
		}
		break;
	case SC_REPRODUCE:	/* リプロデュース */
		if(sd->sc.data[SC__REPRODUCE].timer != -1)
			sp = 0;		// 解除する場合はSP消費しない
		break;
	case SC_INVISIBILITY:	/* インビジビリティ */
		if(sd->sc.data[SC__INVISIBILITY].timer != -1)
			sp = 0;		// 解除する場合はSP消費しない
		break;
	case SC_DIMENSIONDOOR:	/* ディメンションドア */
		if(map[bl->m].flag.noteleport) {
			clif_skill_teleportmessage(sd,2);
			return 0;
		}
		break;
	case LG_FORCEOFVANGUARD:	/* フォースオブバンガード */
		if(sd->sc.data[SC_FORCEOFVANGUARD].timer != -1)
			sp = 0;		// 解除する場合はSP消費しない
		break;
	case LG_RAGEBURST:	/* レイジバーストアタック */
		if(sd->sc.data[SC_FORCEOFVANGUARD].timer == -1 || sd->sc.data[SC_FORCEOFVANGUARD].val4 < 1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_SPIRITBALL,0,0);
			return 0;
		}
		break;
	case LG_PRESTIGE:	/* プレスティージ */
	case LG_BANDING:	/* バンディング */
		if(sd->sc.data[SC_INSPIRATION].timer != -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_CONDITION,0,0);
			return 0;
		}
		break;
	case LG_HESPERUSLIT:	/* ヘスペルスリット */
		if(sd->sc.data[SC_INSPIRATION].timer == -1 && (sd->sc.data[SC_BANDING].timer == -1 || sd->sc.data[SC_BANDING].val2 < 3)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case LG_INSPIRATION:	/* インスピレーション */
		if(sd->sc.data[SC_PRESTIGE].timer != -1 || sd->sc.data[SC_BANDING].timer != -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_CONDITION,0,0);
			return 0;
		}
		break;
	case SR_FALLENEMPIRE:		/* 大纏崩捶 */
		if(sd->sc.data[SC_COMBO].timer == -1 || sd->sc.data[SC_COMBO].val1 != SR_DRAGONCOMBO) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_COMBOSKILL,SR_DRAGONCOMBO,0);
			return 0;
		}
		if(sd->sc.data[SC_FIRST_FAITH_POWER].timer != -1 || sd->sc.data[SC_SECOND_JUDGE].timer != -1 || sd->sc.data[SC_THIRD_EXOR_FLAME].timer != -1) {
			spiritball = 0;
		}
		break;
	case SR_TIGERCANNON:		/* 號砲 */
		if(sd->sc.data[SC_THIRD_EXOR_FLAME].timer != -1) {
			spiritball = 0;
		}
		break;
	case SR_RAMPAGEBLASTER:		/* 爆気散弾 */
		if(sd->spiritball.num) {
			sd->spiritball.old = sd->spiritball.num;
			if(sd->sc.data[SC_MASSIVE_F_BLASTER].timer != -1) {
				spiritball = 0;
			} else {
				spiritball = sd->spiritball.num;
			}
		} else {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_SPIRITBALL,0,0);
			return 0;
		}
		break;
	case SR_GATEOFHELL:		/* 羅刹破凰撃 */
		if(sd->status.sp < sd->status.max_sp * 30 / 100) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_SP,0,0);
			return 0;
		}
		break;
	case SR_RIDEINLIGHTNING:	/* 雷光弾 */
		if(sd->sc.data[SC_MASSIVE_F_BLASTER].timer != -1) {
			spiritball = 0;
		}
		break;
	case SR_FLASHCOMBO:		/* 閃光連撃 */
		if(sd->sc.data[SC_SECOND_JUDGE].timer != -1 || sd->sc.data[SC_THIRD_EXOR_FLAME].timer != -1) {
			spiritball = 0;
		}
		break;
	case WM_GREAT_ECHO:					/* グレートエコー */
	case WM_SONG_OF_MANA:				/* マナの歌 */
	case WM_DANCE_WITH_WUG:				/* ダンスウィズウォーグ */
	case WM_SOUND_OF_DESTRUCTION:		/* サウンドオブディストラクション */
	case WM_SATURDAY_NIGHT_FEVER:		/* フライデーナイトフィーバー */
	case WM_LERADS_DEW:					/* レーラズの霧 */
	case WM_MELODYOFSINK:				/* メロディーオブシンク */
	case WM_BEYOND_OF_WARCRY:			/* ビヨンドオブウォークライ */
	case WM_UNLIMITED_HUMMING_VOICE:	/* エンドレスハミングボイス */
		{
			int c=0;
			if(cnd->id == WM_SATURDAY_NIGHT_FEVER && !map[bl->m].flag.gvg && !map[bl->m].flag.pvp) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_MAP,0,0);
				return 0;
			}
			if(sd->sc.data[SC_KVASIR_SONATA].timer == -1) {
				if(!(type&1)){
					map_foreachinarea(skill_check_condition_char_sub,bl->m,
						bl->x-15,bl->y-15,
						bl->x+15,bl->y+15,BL_PC,sd,&c,cnd);
					if(c<1){
						clif_skill_fail(sd,cnd->id,SKILLFAIL_PARTNER,0,0);
						return 0;
					}
				}else{
					map_foreachinarea(skill_check_condition_use_sub,bl->m,
						bl->x-15,bl->y-15,
						bl->x+15,bl->y+15,BL_PC,sd,&c);
				}
			}
		}
		break;
	case SO_POISON_BUSTER:	/* ポイズンバスター */
		if(target) {
			struct status_change *sc = status_get_sc(target);

			if(sc && sc->data[SC_POISON].timer == -1) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		}
		break;
	case SO_ARRULLO:	/* アルージョ */
		if(!map[bl->m].flag.gvg && !map[bl->m].flag.pvp) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_MAP,0,0);
			return 0;
		}
		break;
	case SO_SUMMON_AGNI:	/* サモンアグニ */
	case SO_SUMMON_AQUA:	/* サモンアクア */
	case SO_SUMMON_VENTUS:	/* サモンベントス */
	case SO_SUMMON_TERA:	/* サモンテラ */
		{
			int skill = pc_checkskill(sd,SO_EL_SYMPATHY);
			if(skill > 0) {
				sp -= sp * (5 + skill * 5) / 100;
			}
		}
		break;
	case SO_EL_CONTROL:	/* エレメンタルコントロール */
	case SO_EL_ACTION:	/* エレメンタルアクション */
	case SO_ELEMENTAL_SHIELD:	/* エレメンタルシールド */
		if(!sd->eld) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_EL_SUMMON,0,0);
			return 0;
		}
		break;
	case SO_EL_CURE:	/* エレメンタルキュアー */
		if(!sd->eld) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_EL_SUMMON,0,0);
			return 0;
		}
		if(sd->status.sp < sd->status.max_sp * 10 / 100) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_SP,0,0);
			return 0;
		}
		if(sd->status.hp < sd->status.max_hp * 10 / 100) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_HP,0,0);
			return 0;
		}
		break;
	case KO_KAHU_ENTEN:	/* 火符‐炎天 */
	case KO_HYOUHU_HUBUKI:	/* 氷符‐吹雪 */
	case KO_KAZEHU_SEIRAN:	/* 風符‐青嵐 */
	case KO_DOHU_KOUKAI:	/* 土符‐剛塊 */
		if(sd->elementball.num >= MAX_ELEMENTBALL) {
			if(sd->elementball.ele == skill_get_pl(cnd->id)) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_SUMMON_OVER,0,0);
				return 0;
			}
		}
		break;
	case KO_KAIHOU:	/* 術式解放 */
	case KO_ZENKAI:	/* 術式全開 */
		if(sd->elementball.num < 1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_SUMMON_NOTHING,0,0);
			return 0;
		}
		break;
	case RL_B_TRAP:	/* バインドトラップ */
		/* 数制限 */
		if(battle_config.pc_land_skill_limit) {
			int maxcount = skill_get_maxcount(cnd->id,cnd->lv);
			if(maxcount > 0 && skill_count_unitgroup(ud,cnd->id) >= maxcount) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_MORESKILL,0,0);
				return 0;
			}
		}
		break;
	case RL_QD_SHOT:			/* クイックドローショット */
		if(sd->sc.data[SC_QD_SHOT_READY].timer == -1 || sd->sc.data[SC_QD_SHOT_READY].val2 == sd->bl.id)
			return 0;
		break;
	case GD_BATTLEORDER:		/* 臨戦態勢 */
	case GD_REGENERATION:		/* 激励 */
	case GD_RESTORE:		/* 治療 */
	case GD_EMERGENCYCALL:		/* 緊急招集 */
		if(!battle_config.guild_skill_available) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		if(battle_config.allow_guild_skill_in_gvg_only && !map[bl->m].flag.gvg) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_GVGONLY,0,0);
			return 0;
		}
		if(battle_config.guild_skill_in_pvp_limit && map[bl->m].flag.pvp) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_MAP,0,0);
			return 0;
		}
		if(sd->sc.data[SC_BATTLEORDER_DELAY + cnd->id - GD_BATTLEORDER].timer != -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		if(cnd->id == GD_EMERGENCYCALL && battle_config.no_emergency_call) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
		
	case SJ_SOLARBURST:		/* 太陽爆発 */
		if(sd->sc.data[SC_COMBO].timer == -1 || sd->sc.data[SC_COMBO].val1 != SJ_PROMINENCEKICK){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_COMBOSKILL,SJ_PROMINENCEKICK,0);
			return 0;
		}
		//fall through
	case SJ_PROMINENCEKICK:		/* 紅焔脚 */
		if((sd->sc.data[SC_SUNSTANCE].timer == -1 ) && (sd->sc.data[SC_UNIVERSESTANCE].timer == -1 )){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SJ_LIGHTOFSUN:		/* 太陽の光 */
		if(sd->sc.data[SC_SUNSTANCE].timer == -1 ){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SJ_FULLMOONKICK:		/* 満月脚 */
		if(sd->sc.data[SC_NEWMOON].timer == -1 ){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		//fall through
	case SJ_NEWMOONKICK:		/* 朔月脚 */
		if((sd->sc.data[SC_LUNARSTANCE].timer == -1 ) && (sd->sc.data[SC_UNIVERSESTANCE].timer == -1 )){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SJ_LIGHTOFMOON:		/* 月の光 */
		if(sd->sc.data[SC_LUNARSTANCE].timer == -1 ){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SJ_FLASHKICK:		/* 閃光脚 */
	case SJ_FALLINGSTAR:		/* 流星落下 */
		if((sd->sc.data[SC_STARSTANCE].timer == -1 ) && (sd->sc.data[SC_UNIVERSESTANCE].timer == -1 )){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SJ_LIGHTOFSTAR:		/* 星の光 */
		if(sd->sc.data[SC_STARSTANCE].timer == -1 ){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SJ_GRAVITYCONTROL:		/* 重力調節 */
	case SJ_NOVAEXPLOSING:		/* 新星爆発 */
	case SJ_STAREMPEROR:		/* 星帝降臨 */
	case SJ_BOOKOFCREATINGSTAR:		/* 創星の書 */
	case SJ_BOOKOFDIMENSION:		/* 次元の書 */
		if(sd->sc.data[SC_UNIVERSESTANCE].timer == -1 ){
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		if(battle_config.allow_se_univ_skill_limit && !map[bl->m].flag.gvg && !map[bl->m].flag.pvp) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_MAP,0,0);
			return 0;
		}
		break;
	case SP_SOULGOLEM:		/* ゴーレムの魂 */
	case SP_SOULSHADOW:		/* 影の魂 */
	case SP_SOULFALCON:		/* 鷹の魂 */
	case SP_SOULFAIRY:		/* 妖精の魂 */
		if(target && target->type != BL_PC) {		// PC以外は使用失敗
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		/* 使うスキル以外の魂状態かを判定 */
		if(tsc &&
		   (cnd->id == SP_SOULGOLEM && (tsc->data[SC_SOULSHADOW].timer != -1 || tsc->data[SC_SOULFALCON].timer != -1 || tsc->data[SC_SOULFAIRY].timer != -1)) ||
		   (cnd->id == SP_SOULSHADOW && (tsc->data[SC_SOULGOLEM].timer != -1 || tsc->data[SC_SOULFALCON].timer != -1 || tsc->data[SC_SOULFAIRY].timer != -1)) ||
		   (cnd->id == SP_SOULFALCON && (tsc->data[SC_SOULSHADOW].timer != -1 || tsc->data[SC_SOULSHADOW].timer != -1 || tsc->data[SC_SOULFAIRY].timer != -1)) ||
		   (cnd->id == SP_SOULFAIRY && (tsc->data[SC_SOULGOLEM].timer != -1 || tsc->data[SC_SOULSHADOW].timer != -1 || tsc->data[SC_SOULFALCON].timer != -1)) ||
		   tsc->data[SC_ALCHEMIST].timer != -1 || tsc->data[SC_MONK].timer != -1 || tsc->data[SC_STAR].timer != -1 || tsc->data[SC_SAGE].timer != -1 ||
		   tsc->data[SC_CRUSADER].timer != -1 || tsc->data[SC_SUPERNOVICE].timer != -1 || tsc->data[SC_KNIGHT].timer != -1 || tsc->data[SC_WIZARD].timer != -1 ||
		   tsc->data[SC_PRIEST].timer != -1 || tsc->data[SC_BARDDANCER].timer != -1 || tsc->data[SC_ROGUE].timer != -1 || tsc->data[SC_ASSASIN].timer != -1 ||
		   tsc->data[SC_BLACKSMITH].timer != -1 || tsc->data[SC_HUNTER].timer != -1 || tsc->data[SC_SOULLINKER].timer != -1 || tsc->data[SC_HIGH].timer != -1 ||
		   tsc->data[SC_DEATHKINGHT].timer != -1 || tsc->data[SC_COLLECTOR].timer != -1 || tsc->data[SC_NINJA].timer != -1 || tsc->data[SC_GUNNER].timer != -1)
		{
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SP_SOULCURSE:		/* 死霊憑依 */
		if(target && target->type != BL_MOB) {		// MOB以外は使用失敗
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		break;
	case SP_SPA:				/* エスパ */
	case SP_SWHOO:				/* エスフ */
		if(target && target->type != BL_MOB && !battle_config.allow_es_magic_all) {		// MOB以外は使用失敗
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		break;
	case SP_SOULDIVISION:		/* 魂の分裂 */
		if(target->type != BL_PC) {		// PC以外は使用失敗
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		break;
	case SP_SOULREVOLVE:		/* 魂の循環 */
		if(target->type != BL_PC) {		// PC以外は使用失敗
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		if(bl != target) {
			struct map_session_data *tsd = (struct map_session_data *)target;
			if(!sd || !tsd || sd->status.party_id == 0 || tsd->status.party_id == 0 || sd->status.party_id != tsd->status.party_id) {	// 同じパーティじゃないとダメ
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		}
		// 魂状態かを判定
		if(!tsc ||
		  (tsc->data[SC_ALCHEMIST].timer == -1 && tsc->data[SC_MONK].timer == -1 && tsc->data[SC_STAR].timer == -1 && tsc->data[SC_SAGE].timer == -1 &&
		   tsc->data[SC_CRUSADER].timer == -1 && tsc->data[SC_SUPERNOVICE].timer == -1 && tsc->data[SC_KNIGHT].timer == -1 && tsc->data[SC_WIZARD].timer == -1 &&
		   tsc->data[SC_PRIEST].timer == -1 && tsc->data[SC_BARDDANCER].timer == -1 && tsc->data[SC_ROGUE].timer == -1 && tsc->data[SC_ASSASIN].timer == -1 &&
		   tsc->data[SC_BLACKSMITH].timer == -1 && tsc->data[SC_HUNTER].timer == -1 && tsc->data[SC_SOULLINKER].timer == -1 && tsc->data[SC_HIGH].timer == -1 &&
		   tsc->data[SC_DEATHKINGHT].timer == -1 && tsc->data[SC_COLLECTOR].timer == -1 && tsc->data[SC_NINJA].timer == -1 && tsc->data[SC_GUNNER].timer == -1 &&
		   tsc->data[SC_SOULGOLEM].timer == -1 && tsc->data[SC_SOULSHADOW].timer == -1 && tsc->data[SC_SOULFALCON].timer == -1 && tsc->data[SC_SOULFAIRY].timer == -1))
		{
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SP_SOULEXPLOSION:		/* 魂の崩壊 */
		if(status_get_hp(target) < 10) {	// 対象のHPが10未満は失敗
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		// 魂状態かを判定
		if(!tsc ||
		  (tsc->data[SC_ALCHEMIST].timer == -1 && tsc->data[SC_MONK].timer == -1 && tsc->data[SC_STAR].timer == -1 && tsc->data[SC_SAGE].timer == -1 &&
		   tsc->data[SC_CRUSADER].timer == -1 && tsc->data[SC_SUPERNOVICE].timer == -1 && tsc->data[SC_KNIGHT].timer == -1 && tsc->data[SC_WIZARD].timer == -1 &&
		   tsc->data[SC_PRIEST].timer == -1 && tsc->data[SC_BARDDANCER].timer == -1 && tsc->data[SC_ROGUE].timer == -1 && tsc->data[SC_ASSASIN].timer == -1 &&
		   tsc->data[SC_BLACKSMITH].timer == -1 && tsc->data[SC_HUNTER].timer == -1 && tsc->data[SC_SOULLINKER].timer == -1 && tsc->data[SC_HIGH].timer == -1 &&
		   tsc->data[SC_DEATHKINGHT].timer == -1 && tsc->data[SC_COLLECTOR].timer == -1 && tsc->data[SC_NINJA].timer == -1 && tsc->data[SC_GUNNER].timer == -1 &&
		   tsc->data[SC_SOULGOLEM].timer == -1 && tsc->data[SC_SOULSHADOW].timer == -1 && tsc->data[SC_SOULFALCON].timer == -1 && tsc->data[SC_SOULFAIRY].timer == -1))
		{
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SP_KAUTE:		/* カウト */
		{
			struct map_session_data *tsd = (struct map_session_data *)target;
			if(!tsd) {
				// 対象が人以外失敗
				clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
				return 0;
			}
			// HPが30%以上必要
			if(sd->status.hp < sd->status.max_hp * 30 / 100) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_HP,0,0);
				return 0;
			}
			if(battle_config.soul_linker_battle_mode_ka == 0) {
				// ソウルリンカー系職業か家族以外、魂の連結状態効果中でなければ使用失敗
				if( pc_get_base_job(tsd->s_class.job,2) != PC_JOB_SL &&
					tsd->status.char_id != sd->status.char_id &&
				    tsd->status.char_id != sd->status.partner_id &&
				    tsd->status.char_id != sd->status.baby_id &&
					tsd->sc.data[SC_SOULUNITY].timer == -1) {
					clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
					return 0;
				}
			}
		}
		break;
	case IQ_JUDGE:		/* 第二章：審判者 */
		if(sd->sc.data[SC_FIRST_FAITH_POWER].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case IQ_SECOND_FLAME:		/* 第二撃：滅魔の火 */
		if(sd->sc.data[SC_THIRD_EXOR_FLAME].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		if(!tsc || (tsc->data[SC_FIRST_BRAND].timer == -1 && tsc->data[SC_SECOND_BRAND].timer == -1)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case IQ_SECOND_FAITH:		/* 第二撃：信念 */
		if(sd->sc.data[SC_FIRST_FAITH_POWER].timer == -1 && sd->sc.data[SC_SECOND_JUDGE].timer == -1 && sd->sc.data[SC_THIRD_EXOR_FLAME].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		if(!tsc || (tsc->data[SC_FIRST_BRAND].timer == -1 && tsc->data[SC_SECOND_BRAND].timer == -1)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case IQ_SECOND_JUDGEMENT:		/* 第二撃：審判 */
		if(sd->sc.data[SC_SECOND_JUDGE].timer == -1 && sd->sc.data[SC_THIRD_EXOR_FLAME].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		if(!tsc || (tsc->data[SC_FIRST_BRAND].timer == -1 && tsc->data[SC_SECOND_BRAND].timer == -1)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case IQ_THIRD_PUNISH:		/* 第三撃：断罪 */
		if(sd->sc.data[SC_FIRST_FAITH_POWER].timer == -1 && sd->sc.data[SC_SECOND_JUDGE].timer == -1 && sd->sc.data[SC_THIRD_EXOR_FLAME].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		if(!tsc || tsc->data[SC_SECOND_BRAND].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case IQ_THIRD_FLAME_BOMB:		/* 第三撃：滅火撃 */
		if(sd->sc.data[SC_THIRD_EXOR_FLAME].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		if(!tsc || tsc->data[SC_SECOND_BRAND].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case IQ_THIRD_CONSECRATION:		/* 第三撃：浄化 */
		if(sd->sc.data[SC_SECOND_JUDGE].timer == -1 && sd->sc.data[SC_THIRD_EXOR_FLAME].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		if(!tsc || tsc->data[SC_SECOND_BRAND].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case IQ_THIRD_EXOR_FLAME:		/* 最終章：滅魔の炎 */
		if(sd->sc.data[SC_SECOND_JUDGE].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case IG_GUARDIAN_SHIELD:		/* ガーディアンシールド */
	case IG_ULTIMATE_SACRIFICE:		/* アルティメットサクリファイス */
		if(sd->sc.data[SC_GUARD_STANCE].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case IG_REBOUND_SHIELD:			/* リバウンドシールド */
		if(sd->sc.data[SC_GUARD_STANCE].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		// ディボーション検査
		for(i=0; i<5; i++) {
			if(sd->dev.val1[i]) {
				break;
			}
		}
		// ディボーションを使用していない
		if(i >= 5) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case IG_GRAND_JUDGEMENT:		/* グランドジャッジメント */
	case IG_SHIELD_SHOOTING:		/* シールドシューティング */
	case IG_OVERSLASH:				/* オーバースラッシュ */
		if(sd->sc.data[SC_ATTACK_STANCE].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case CD_REPARATIO:				/* レパラティオ */
		if(target->type != BL_PC || battle_check_undead(status_get_race(target),status_get_elem_type(target))) {		// PC以外と不死属性には使用失敗
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		break;
	case CD_MEDIALE_VOTUM:			/* メディアリボトゥム */
	case CD_DILECTIO_HEAL:			/* ディレクティオヒール */
		if(target->type != BL_PC || battle_check_undead(status_get_race(target),status_get_elem_type(target))) {		// PC以外と不死属性には使用失敗
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		} else if(bl != target) {
			struct map_session_data *tsd = (struct map_session_data *)target;
			if(!sd || !tsd || sd->status.party_id == 0 || tsd->status.party_id == 0 || sd->status.party_id != tsd->status.party_id) {	// 同じパーティじゃないとダメ
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		}
		break;
	case CD_ARGUTUS_VITA:		/* アルグトゥスヴィタ */
	case CD_ARGUTUS_TELUM:		/* アルグトゥステルム */
	case CD_PRESENS_ACIES:		/* プレセンスアキエース */
	case MT_D_MACHINE:			/* 防御装置有効化 */
	case EM_SPELL_ENCHANTING:	/* スペルエンチャンティング */
	case SOA_TALISMAN_OF_PROTECTION:	/* 守護符 */
	case SOA_TALISMAN_OF_WARRIOR:	/* 武士符 */
	case SOA_TALISMAN_OF_MAGICIAN:	/* 法師符 */
	case SOA_TALISMAN_OF_FIVE_ELEMENTS:	/* 五行符 */
		if(target->type != BL_PC) {		// PC以外には使用失敗
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		} else if(bl != target) {
			struct map_session_data *tsd = (struct map_session_data *)target;
			if(!sd || !tsd || sd->status.party_id == 0 || tsd->status.party_id == 0 || sd->status.party_id != tsd->status.party_id) {	// 同じパーティじゃないとダメ
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		}
		break;
	case SHC_ETERNAL_SLASH:		/* エターナルスラッシュ */
		if(sd->sc.data[SC_WEAPONBLOCK_ON].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_GC_WEAPONBLOCKING,0,0);
			return 0;
		}
		break;
	case SHC_POTENT_VENOM:		/* ポテントベナム */
		if(sd->sc.data[SC_EDP].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SHC_IMPACT_CRATER:		/* インパクトクレーター */
		if(sd->sc.data[SC_ROLLINGCUTTER].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case MT_A_MACHINE:			/* 攻撃装置有効化 */
		if(target->type != BL_PC) {		// PC以外には使用失敗
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		} else if(bl != target) {
			struct map_session_data *tsd = (struct map_session_data *)target;
			if(!sd || !tsd || sd->status.party_id == 0 || tsd->status.party_id == 0 || sd->status.party_id != tsd->status.party_id) {	// 同じパーティじゃないとダメ
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
			if(abs(sd->status.base_level - tsd->status.base_level) > 15) {	// レベル差が15以上の相手は使用失敗
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		}
		break;
	case MT_SUMMON_ABR_BATTLE_WARIOR:	/* ABR バトルウォリアー */
	case MT_SUMMON_ABR_DUAL_CANNON:		/* ABR デュアルキャノン */
	case MT_SUMMON_ABR_MOTHER_NET:		/* ABR マザーネット */
	case MT_SUMMON_ABR_INFINITY:		/* ABR インフィニティ */
		{
			const int mob_id[4] = { MOBID_ABR_BATTLE_WARIOR, MOBID_ABR_DUAL_CANNON, MOBID_ABR_MOTHER_NET, MOBID_ABR_INFINITY };
			int maxcount = skill_get_maxcount(cnd->id,cnd->lv);

			if(battle_config.pc_land_skill_limit && maxcount > 0) {
				int c = map_foreachinarea(
					skill_check_condition_mob_master_sub, bl->m, 0, 0, map[bl->m].xs,
					map[bl->m].ys, BL_MOB, bl->id, mob_id[cnd->id-MT_SUMMON_ABR_BATTLE_WARIOR]
				);
				if(c >= maxcount){
					clif_skill_fail(sd,cnd->id,SKILLFAIL_MORESKILL,0,0);
					return 0;
				}
			}
		}
		break;
	case BO_WOODENWARRIOR:		/* クリエイトウドゥンウォリアー */
	case BO_WOODEN_FAIRY:		/* クリエイトウドゥンフェアリー */
	case BO_CREEPER:			/* クリエイトクリーパー */
	case BO_HELLTREE:			/* クリエイトヘルツリー */
		{
			const int mob_id[5] = { MOBID_SUMMON_WOODENWARRIOR, MOBID_SUMMON_WOODEN_FAIRY, MOBID_SUMMON_CREEPER, 0, MOBID_SUMMON_HELLTREE };
			int maxcount = skill_get_maxcount(cnd->id,cnd->lv);

			if(battle_config.pc_land_skill_limit && maxcount > 0) {
				int c = map_foreachinarea(
					skill_check_condition_mob_master_sub, bl->m, 0, 0, map[bl->m].xs,
					map[bl->m].ys, BL_MOB, bl->id, mob_id[cnd->id-BO_WOODENWARRIOR]
				);
				if(c >= maxcount){
					clif_skill_fail(sd,cnd->id,SKILLFAIL_MORESKILL,0,0);
					return 0;
				}
			}
		}
		break;
	case EM_ACTIVITY_BURN:					/* アクティビティバーン */
		if(target->type != BL_PC) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		break;
	case EM_INCREASING_ACTIVITY:			/* インクリーシングアクティビティ */
		if(target->type != BL_PC || bl == target) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		}
		break;
	case EM_SUMMON_ELEMENTAL_ARDOR:			/* サモンアルドール */
		if(sd->eld) {
			if(sd->eld->status.class_ != ELEMID_EL_AGNI_L) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		} else {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_EL_SUMMON,0,0);
			return 0;
		}
		break;
	case EM_SUMMON_ELEMENTAL_DILUVIO:		/* サモンディルビオ */
		if(sd->eld) {
			if(sd->eld->status.class_ != ELEMID_EL_AQUA_L) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		} else {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_EL_SUMMON,0,0);
			return 0;
		}
		break;
	case EM_SUMMON_ELEMENTAL_PROCELLA:		/* サモンプロセラ */
		if(sd->eld) {
			if(sd->eld->status.class_ != ELEMID_EL_VENTUS_L) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		} else {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_EL_SUMMON,0,0);
			return 0;
		}
		break;
	case EM_SUMMON_ELEMENTAL_TERREMOTUS:	/* サモンテレモトゥス */
		if(sd->eld) {
			if(sd->eld->status.class_ != ELEMID_EL_TERA_L) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		} else {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_EL_SUMMON,0,0);
			return 0;
		}
		break;
	case EM_SUMMON_ELEMENTAL_SERPENS:		/* サモンサーペンス */
		if(sd->eld) {
			if(sd->eld->status.class_ != ELEMID_EL_AGNI_L && sd->eld->status.class_ != ELEMID_EL_AQUA_L && sd->eld->status.class_ != ELEMID_EL_VENTUS_L && sd->eld->status.class_ != ELEMID_EL_TERA_L) {
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		} else {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_EL_SUMMON,0,0);
			return 0;
		}
		break;
	case EM_ELEMENTAL_BUSTER:	/* エレメンタルバスター */
	case EM_ELEMENTAL_VEIL:		/* エレメンタルヴェール */
		if(!sd->eld) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_EL_SUMMON,0,0);
			return 0;
		}
		if(!elem_is4thclass(sd->eld)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SOA_SOUL_GATHERING:		/* 護魂一身 */
		if(sd->sc.data[SC_SOULCOLLECT].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_SOULCOLLECT,0,0);
			return 0;
		}
		break;
	case SOA_EXORCISM_OF_MALICIOUS_SOUL:	/* 死霊浄化 */
		if(sd->soulenergy.num == 0) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_SOULENERGY,0,0);
			return 0;
		}
		break;
	case SOA_CIRCLE_OF_DIRECTIONS_AND_ELEMENTALS:	/* 四方五行陣 */
		if(sd->sc.data[SC_T_FOURTH_GOD].timer == -1 && sd->sc.data[SC_T_FIVETH_GOD].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SH_BLESSING_OF_MYSTICAL_CREATURES:		/* にゃんブレッシング */
		if(bl == target) {		// 自分には使用不可
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		} else if(tsc && tsc->data[SC_BLESSING_OF_M_C_DEBUFF].timer != -1) {		// リバウンド状態には使用不可
			clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
			return 0;
		} else {
			struct map_session_data *tsd = (struct map_session_data *)target;
			if(tsd && pc_isdoram(tsd)) {			// ドラム系列には使用不可
				clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
				return 0;
			}
			if(!sd || !tsd || sd->status.party_id == 0 || tsd->status.party_id == 0 || sd->status.party_id != tsd->status.party_id) {	// 同じパーティじゃないとダメ
				clif_skill_fail(sd,cnd->id,SKILLFAIL_TOTARGET,0,0);
				return 0;
			}
		}
		break;
	case SKE_NOON_BLAST:		/* 太天一陽 */
		if(sd->sc.data[SC_RISING_SUN].timer == -1 && sd->sc.data[SC_NOON_SUN].timer == -1 && sd->sc.data[SC_SKY_ENCHANT].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SKE_SUNSET_BLAST:		/* 天陽 */
		if(sd->sc.data[SC_NOON_SUN].timer == -1 && sd->sc.data[SC_SUNSET_SUN].timer == -1 && sd->sc.data[SC_SKY_ENCHANT].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SKE_MIDNIGHT_KICK:		/* 太天一月 */
		if(sd->sc.data[SC_RISING_MOON].timer == -1 && sd->sc.data[SC_MIDNIGHT_MOON].timer == -1 && sd->sc.data[SC_SKY_ENCHANT].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SKE_DAWN_BREAK:		/* 天月 */
		if(sd->sc.data[SC_MIDNIGHT_MOON].timer == -1 && sd->sc.data[SC_DAWN_MOON].timer == -1 && sd->sc.data[SC_SKY_ENCHANT].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_OTHERSKILL,0,0);
			return 0;
		}
		break;
	case SKE_STAR_BURST:		/* 天命落星 */
	case SKE_STAR_CANNON:		/* 天星 */
		{
			// 天地万星の範囲内かチェック
			int range = skill_get_unit_range(SKE_TWINKLING_GALAXY, 1);
			if(map_foreachinarea(skill_check_unit_id,
				bl->m, bl->x-range, bl->y-range, bl->x+range, bl->y+range, BL_SKILL,
				bl->id, SKE_TWINKLING_GALAXY) == 0)
			{
				clif_skill_fail(sd,cnd->id,SKILLFAIL_TWINKLINGGALAXY,0,0);
				return 0;
			}
		}
		break;
	case SS_KUNAIKUSSETSU:		/* 苦無 -屈折- */
		{
			// 苦無トラップ判定
			int range = skill_get_area(cnd->id, cnd->lv);
			if(map_foreachinarea(skill_check_unit_id,
				bl->m, bl->x-range, bl->y-range, bl->x+range, bl->y+range, BL_SKILL,
				bl->id, SS_KUNAIWAIKYOKU) == 0)
			{
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		}
		break;
	}

	if(!(type&2)) {
		int w;

		if(!sd->skill_item.flag) {		// アイテムスキル由来ならSPチェックは不要
			if(sp > 0 && sd->status.sp < sp) {		/* SPチェック */
				clif_skill_fail(sd,cnd->id,SKILLFAIL_SP,0,0);
				return 0;
			}
		}
		if(hp > 0 && sd->status.hp < hp) {			/* HPチェック */
			clif_skill_fail(sd,cnd->id,SKILLFAIL_HP,0,0);
			return 0;
		}
		if(ap > 0 && sd->status.ap < ap) {			/* APチェック */
			clif_skill_fail(sd,cnd->id,SKILLFAIL_AP,0,0);
			return 0;
		}
		if(zeny > 0 && sd->status.zeny < zeny) {
			sd->zenynage_damage = 0;
			clif_skill_fail(sd,cnd->id,SKILLFAIL_ZENY,0,0);
			return 0;
		}

		w = sd->status.weapon;
		if(w >= WT_MAX)
			w -= WT_DOUBLE_DD + WT_MAX;

		if(!(weapon & (1<<w))) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_WEAPON,0,0);
			return 0;
		}
		if(spiritball > 0 && sd->spiritball.num < spiritball) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_SPIRITBALL,spiritball,0);
			return 0;
		}
		if(coin > 0 && sd->coin.num < coin) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_COIN,coin,0);
			return 0;
		}
		if(soulenergy > 0 && sd->soulenergy.num < soulenergy) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_SOULENERGY,soulenergy,0);
			return 0;
		}
		if(servantweapon > 0 && sd->ball.num < servantweapon) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_SERVANTWEAPOM,servantweapon,0);
			return 0;
		}
		if(arrow > 0) {						// 矢不足
			int idx = sd->equip_index[EQUIP_INDEX_ARROW];
			if( idx == -1 ||
			    !(sd->inventory_data[idx]->arrow_type & skill_get_arrow_type(cnd->id)) ||
			    sd->status.inventory[idx].amount < arrow )
			{
				// 矢の種類ごとに失敗メッセージを表示
				switch(skill_get_arrow_type(cnd->id)) {
				case 0x0004:		// ハンドガン専用弾
				case 0x0008:		// ライフル専用弾
				case 0x0010:		// ショットガン専用弾
				case 0x0020:		// ガトリンガン専用弾
				case 0x0040:		// グレネードランチャー専用弾
					clif_skill_fail(sd,cnd->id,SKILLFAIL_BULLET,0,0);
					break;
				case 0x0100:		// 苦無
					clif_skill_fail(sd,cnd->id,SKILLFAIL_KUNAI,0,0);
					break;
				case 0x0200:		// キャノンボール
					clif_skill_fail(sd,cnd->id,SKILLFAIL_CANONBALL,0,0);
					break;
				default:
					clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
					break;
				}
				return 0;
			}
		}
	}

	switch(state) {
	case SST_HIDING:
		if(!(sd->sc.option&OPTION_HIDE)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SST_CLOAKING:
		if(!pc_iscloaking(sd)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SST_CHASEWALKING:
		if(!pc_ischasewalk(sd)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SST_HIDDEN:
		if(!pc_ishiding(sd)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SST_RIDING:
		if(!pc_isriding(sd) && !pc_isdragon(sd)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SST_FALCON:
		if(!pc_isfalcon(sd)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SST_CART:
		if(!pc_iscarton(sd)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_CART,0,0);
			return 0;
		}
		break;
	case SST_SHIELD:
		if(sd->status.shield <= 0) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SST_SIGHT:
		if(sd->sc.data[SC_SIGHT].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SST_EXPLOSIONSPIRITS:
		if(sd->sc.data[SC_EXPLOSIONSPIRITS].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SST_CARTBOOST:
		if(sd->sc.data[SC_CARTBOOST].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SST_NEN:
		if(sd->sc.data[SC_NEN].timer == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SST_RECOV_WEIGHT_RATE:
		if(battle_config.natural_heal_weight_rate <= 100 && sd->weight*100/sd->max_weight >= battle_config.natural_heal_weight_rate) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SST_MOVE_ENABLE:
		if(path_search(NULL,bl->m,bl->x,bl->y,cnd->x,cnd->y,1) == -1) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SST_WATER:
		if(!map[bl->m].flag.rain) {
			// 水場判定
			if(( !map_getcell(bl->m,bl->x,bl->y,CELL_CHKWATER) &&
			    sd->sc.data[SC_DELUGE].timer == -1 &&
			    sd->sc.data[SC_SUITON].timer == -1 ) ||
			    map_find_skill_unit_oncell(bl,bl->x,bl->y,SA_LANDPROTECTOR,NULL))
			{
				clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
				return 0;
			}
		}
		break;
	case SST_DRAGON:
		if(!pc_isdragon(sd)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_DRAGON,0,0);
			return 0;
		}
		break;
	case SST_WOLF:
		if(!pc_iswolf(sd) && !pc_iswolfmount(sd)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_FAILED,0,0);
			return 0;
		}
		break;
	case SST_GEAR:
		if(!pc_isgear(sd)) {
			clif_skill_fail(sd,cnd->id,SKILLFAIL_MADOGEAR,0,0);
			return 0;
		}
		break;
	}

	switch(cnd->id)
	{
		case SA_VOLCANO:		/* ボルケーノ */
		case SA_DELUGE:			/* デリュージ */
		case SA_VIOLENTGALE:	/* バイオレントゲイル */
			// 属性場用 出ている間はコスト無し
			if(sd->sc.data[SC_ELEMENTFIELD].timer != -1)
				item_nocost = 1;
			break;
		case SR_CURSEDCIRCLE:	/* 呪縛陣 */
			spiritball = 0;		// 気弾の消費はスキル効果発動時
			break;
		case DK_SERVANT_W_PHANTOM:		/* サーヴァントウェポン：ファントム */
		case DK_SERVANT_W_DEMOL:		/* サーヴァントウェポン：デモリッション */
			servantweapon = 0;	// 武器体の消費はスキル効果発動時
			break;
	}

	// GVG PVP以外のマップでの特殊処理
	if(map[bl->m].flag.pvp==0 && map[bl->m].flag.gvg==0)
	{
		switch(cnd->id)
		{
			case AM_DEMONSTRATION:
				if(battle_config.demonstration_nocost)
					item_nocost = 1;
				break;
			case AM_ACIDTERROR:
				if(battle_config.acidterror_nocost)
					item_nocost = 1;
				break;
			case AM_CANNIBALIZE:
				if(battle_config.cannibalize_nocost)
					item_nocost = 1;
				break;
			case AM_SPHEREMINE:
				if(battle_config.spheremine_nocost)
					item_nocost = 1;
				break;
			case AM_CP_WEAPON:
			case AM_CP_SHIELD:
			case AM_CP_ARMOR:
			case AM_CP_HELM:
			case CR_FULLPROTECTION:
				if(battle_config.chemical_nocost)
					item_nocost = 1;
				break;
			case CR_ACIDDEMONSTRATION:
				if(battle_config.aciddemonstration_nocost)
					item_nocost = 1;
				break;
			case CR_SLIMPITCHER:
				if(battle_config.slimpitcher_nocost)
				{
					if(cnd->lv < 5) {
						// 赤ポーション
						itemid[MAX_SKILL_DB_ITEM] = 501;
						amount[MAX_SKILL_DB_ITEM] = 1;
					}
					else if(cnd->lv < 10) {
						// 黄ポーション
						itemid[MAX_SKILL_DB_ITEM] = 503;
						amount[MAX_SKILL_DB_ITEM] = 1;
					}
					else {
						// 白ポーション
						itemid[MAX_SKILL_DB_ITEM] = 504;
						amount[MAX_SKILL_DB_ITEM] = 1;
					}
				}
			default:
				break;
		}
	}

	if(!item_nocost) {
		if(skill_item_consume(&sd->bl, cnd, type, itemid, amount) == 0)
			return 0;
	}

	if(type == 1) {
		if(!sd->skill_item.flag) {	// アイテムスキル由来ならSP消費しない
			if(sp > 0) {				// SP消費
				sd->status.sp -= sp;
				clif_updatestatus(sd,SP_SP);
			}
		}
		if(hp > 0) {					// HP消費
			sd->status.hp -= hp;
			clif_updatestatus(sd,SP_HP);
		}
		if(ap > 0) {					// AP消費
			sd->status.ap -= ap;
			clif_updatestatus(sd,SP_AP);
		}
		if(zeny > 0)					// Zeny消費
			pc_payzeny(sd,zeny);
		if(spiritball > 0)				// 気球消費
			pc_delspiritball(sd,spiritball,0);
		if(coin > 0)					// コイン消費
			pc_delcoin(sd,coin,0);
		if(soulenergy > 0)				// ソウルエナジー消費
			pc_delsoulenergy(sd,soulenergy,0);
		if(servantweapon > 0)			// サーヴァントウェポン消費
			pc_delball(sd,servantweapon,0);
	}
	return 1;
}

// MOB用判定( 0: 使用失敗 1: 使用成功 )
