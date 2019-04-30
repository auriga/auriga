/*
 * Copyright (C) 2002-2007  Auriga
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

#include "db.h"
#include "timer.h"
#include "nullpo.h"
#include "malloc.h"
#include "utils.h"

#include "map.h"
#include "path.h"
#include "pc.h"
#include "mob.h"
#include "pet.h"
#include "homun.h"
#include "skill.h"
#include "unit.h"
#include "battle.h"
#include "status.h"
#include "storage.h"
#include "clif.h"
#include "party.h"
#include "npc.h"
#include "chat.h"
#include "trade.h"
#include "guild.h"
#include "friend.h"
#include "mob.h"
#include "vending.h"
#include "intif.h"
#include "mail.h"
#include "merc.h"
#include "booking.h"
#include "buyingstore.h"
#include "elem.h"
#include "memorial.h"

static int unit_walktoxy_timer(int tid,unsigned int tick,int id,void *data);
static int unit_attack_timer(int tid,unsigned int tick,int id,void *data);

/*==========================================
 * 二点間の距離を返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int unit_distance( struct block_list *bl, struct block_list *bl2)
{
	nullpo_retr(0, bl);
	nullpo_retr(0, bl2);

	return path_distance(bl->x,bl->y,bl2->x,bl2->y);
}

/*==========================================
 *
 *------------------------------------------
 */
struct unit_data* unit_bl2ud(struct block_list *bl)
{
	if( bl == NULL ) return NULL;
	if( bl->type == BL_PC   ) return &((struct map_session_data*)bl)->ud;
	if( bl->type == BL_MOB  ) return &((struct mob_data*)bl)->ud;
	if( bl->type == BL_PET  ) return &((struct pet_data*)bl)->ud;
	if( bl->type == BL_HOM  ) return &((struct homun_data*)bl)->ud;
	if( bl->type == BL_MERC ) return &((struct merc_data*)bl)->ud;
	if( bl->type == BL_ELEM ) return &((struct elem_data*)bl)->ud;
	return NULL;
}

/*==========================================
 *
 *------------------------------------------
 */
static int unit_walktoxy_sub(struct block_list *bl)
{
	int i;
	struct walkpath_data wpd;
	struct map_session_data *sd = NULL;
	struct unit_data        *ud = NULL;
	struct status_change    *sc = NULL;

	nullpo_retr(0, bl);

	ud = unit_bl2ud(bl);
	if(ud == NULL)
		return 0;

	if(bl->type == BL_PC)
		sd = (struct map_session_data *)bl;

	if(sd && pc_iscloaking(sd))	// クローキング時再計算
		status_calc_pc(sd,0);

	sc = status_get_sc(bl);
	if(sc && sc->data[SC_FORCEWALKING].timer != -1) {
		if(path_search2(&wpd,bl->m,bl->x,bl->y,ud->to_x,ud->to_y,0))
			return 0;
	} else {
		if(path_search(&wpd,bl->m,bl->x,bl->y,ud->to_x,ud->to_y,0))
			return 0;
	}
	if(sc && sc->data[SC_SU_STOOP].timer != -1)	// うずくまる解除
		status_change_end(bl, SC_SU_STOOP, -1);

	if(bl->type == BL_MOB) {
		struct mob_data *md = (struct mob_data *)bl;
		if(md) {
			int x = md->bl.x+dirx[wpd.path[0]];
			int y = md->bl.y+diry[wpd.path[0]];
			if (map_getcell(bl->m,x,y,CELL_CHKBASILICA) && !(status_get_mode(bl)&MD_BOSS)) {
				ud->state.change_walk_target=0;
				return 0;
			}
		}
	}

	memcpy(&ud->walkpath,&wpd,sizeof(wpd));

	if(sd) {
		clif_walkok(sd);
	}
	clif_move(bl);

	ud->state.change_walk_target = 0;

	if(ud->walkpath.path_pos>=ud->walkpath.path_len)
		i = -1;
	else if(ud->walkpath.path[ud->walkpath.path_pos]&1)
		i = status_get_speed(bl)*14/10;
	else
		i = status_get_speed(bl);
	if(i > 0) {
		ud->walktimer = add_timer(gettick()+i,unit_walktoxy_timer,bl->id,(void*)0);
	}

	return 1;
}

/*==========================================
 *
 *------------------------------------------
 */
static int unit_walktoxy_timer(int tid,unsigned int tick,int id,void *data)
{
	int i;
	int moveblock;
	int x,y,dx,dy,dir;
	struct block_list       *bl  = NULL;
	struct map_session_data *sd  = NULL;
	struct pet_data         *pd  = NULL;
	struct mob_data         *md  = NULL;
	struct homun_data       *hd  = NULL;
	struct merc_data        *mcd = NULL;
	struct elem_data        *eld = NULL;
	struct unit_data        *ud  = NULL;
	struct status_change    *sc  = NULL;

	bl=map_id2bl(id);
	if(bl == NULL)
		return 0;
	if( (sd = BL_DOWNCAST( BL_PC,  bl ) ) ) {
		ud = &sd->ud;
	} else if( (md = BL_DOWNCAST( BL_MOB, bl ) ) ) {
		ud = &md->ud;
	} else if( (pd = BL_DOWNCAST( BL_PET, bl ) ) ) {
		ud = &pd->ud;
	} else if( (hd = BL_DOWNCAST( BL_HOM, bl ) ) ) {
		ud = &hd->ud;
	} else if( (mcd = BL_DOWNCAST( BL_MERC, bl ) ) ) {
		ud = &mcd->ud;
	} else if( (eld = BL_DOWNCAST( BL_ELEM, bl ) ) ) {
		ud = &eld->ud;
	}
	if(ud == NULL) return 0;

	if(ud->walktimer != tid) {
		if(battle_config.error_log)
			printf("unit_walk_timer %d != %d\n",ud->walktimer,tid);
		return 0;
	}
	ud->walktimer = -1;
	if( bl->prev == NULL ) return 0; // block_list から抜けているので移動停止する

	if(ud->walkpath.path_pos >= ud->walkpath.path_len || ud->walkpath.path_pos != PTR2INT(data))
		return 0;

	// 歩いたので息吹のタイマーを初期化
	if(sd) {
		sd->regen.spirithptick = 0;
		sd->regen.spiritsptick = 0;
		sd->state.warp_waiting  = 0;
		// 歩いたので詠唱バー表示中断
		if(sd->progressbar.npc_id)
			clif_progressbar_abort(sd);
	}

	sc = status_get_sc(bl);

	x = bl->x;
	y = bl->y;

	dir = ud->walkpath.path[ud->walkpath.path_pos];
	if(sd) pc_setdir(sd, dir, dir);
	else if(md)  md->dir  = dir;
	else if(pd)  pd->dir  = dir;
	else if(hd)  hd->dir  = dir;
	else if(mcd) mcd->dir = dir;
	else if(eld) eld->dir = dir;

	dx = dirx[(int)dir];
	dy = diry[(int)dir];

	moveblock = map_block_is_differ(bl,bl->m,x+dx,y+dy);

	ud->walktimer = 1;
	if(sd) {
		map_foreachinmovearea(clif_pcoutsight,bl->m,x-AREA_SIZE,y-AREA_SIZE,x+AREA_SIZE,y+AREA_SIZE,dx,dy,BL_ALL,sd);
		map_foreachinmovearea(mob_ai_hard_spawn_sub,bl->m,x-AREA_SIZE*2,y-AREA_SIZE*2,x+AREA_SIZE*2,y+AREA_SIZE*2,dx,dy,BL_MOB,sd,0);
	} else if(md) {
		map_foreachinmovearea(clif_moboutsight,bl->m,x-AREA_SIZE,y-AREA_SIZE,x+AREA_SIZE,y+AREA_SIZE,dx,dy,BL_PC,md);
		map_foreachinmovearea(mob_ai_hard_spawn_sub,bl->m,x-AREA_SIZE*2,y-AREA_SIZE*2,x+AREA_SIZE*2,y+AREA_SIZE*2,dx,dy,BL_PC|BL_HOM|BL_MERC|BL_ELEM,md,0);
	} else if(pd) {
		map_foreachinmovearea(clif_petoutsight,bl->m,x-AREA_SIZE,y-AREA_SIZE,x+AREA_SIZE,y+AREA_SIZE,dx,dy,BL_PC,pd);
	} else if(hd) {
		map_foreachinmovearea(clif_homoutsight,bl->m,x-AREA_SIZE,y-AREA_SIZE,x+AREA_SIZE,y+AREA_SIZE,dx,dy,BL_PC,hd);
		map_foreachinmovearea(mob_ai_hard_spawn_sub,bl->m,x-AREA_SIZE*2,y-AREA_SIZE*2,x+AREA_SIZE*2,y+AREA_SIZE*2,dx,dy,BL_MOB,hd,0);
	} else if(mcd) {
		map_foreachinmovearea(clif_mercoutsight,bl->m,x-AREA_SIZE,y-AREA_SIZE,x+AREA_SIZE,y+AREA_SIZE,dx,dy,BL_PC,mcd);
		map_foreachinmovearea(mob_ai_hard_spawn_sub,bl->m,x-AREA_SIZE*2,y-AREA_SIZE*2,x+AREA_SIZE*2,y+AREA_SIZE*2,dx,dy,BL_MOB,mcd,0);
	} else if(eld) {
		map_foreachinmovearea(clif_elemoutsight,bl->m,x-AREA_SIZE,y-AREA_SIZE,x+AREA_SIZE,y+AREA_SIZE,dx,dy,BL_PC,eld);
		map_foreachinmovearea(mob_ai_hard_spawn_sub,bl->m,x-AREA_SIZE*2,y-AREA_SIZE*2,x+AREA_SIZE*2,y+AREA_SIZE*2,dx,dy,BL_MOB,eld,0);
	}
	ud->walktimer = -1;

	x += dx;
	y += dy;

	if(md && md->min_chase>13)
		md->min_chase--;

	if(!pd) skill_unit_move(bl,tick,0);
	if(moveblock) map_delblock(bl);
	bl->x = x;
	bl->y = y;
	if(moveblock) map_addblock(bl);
	if(!pd) skill_unit_move(bl,tick,1);

	if(sd) {
		if(sd->sc.data[SC_DANCING].timer != -1 && sd->sc.data[SC_LONGINGFREEDOM].timer == -1)	// Not 拘束しないで
		{
			skill_unit_move_unit_group(map_id2sg(sd->sc.data[SC_DANCING].val2),sd->bl.m,dx,dy);
			sd->dance.x += dx;
			sd->dance.y += dy;
		}
		if(sd->sc.data[SC_WARM].timer != -1)
			skill_unit_move_unit_group(map_id2sg(sd->sc.data[SC_WARM].val4),sd->bl.m,dx,dy);
		if(sd->sc.data[SC_NEUTRALBARRIER_USER].timer != -1)
			skill_unit_move_unit_group(map_id2sg(sd->sc.data[SC_NEUTRALBARRIER_USER].val4),sd->bl.m,dx,dy);
		if(sd->sc.data[SC_STEALTHFIELD_USER].timer != -1)
			skill_unit_move_unit_group(map_id2sg(sd->sc.data[SC_STEALTHFIELD_USER].val4),sd->bl.m,dx,dy);
		if(sd->sc.data[SC_BANDING].timer != -1)
			skill_unit_move_unit_group(map_id2sg(sd->sc.data[SC_BANDING].val4),sd->bl.m,dx,dy);
	}
	if(md) {
		if(sc && sc->data[SC_DANCING].timer != -1)
			skill_unit_move_unit_group(map_id2sg(sc->data[SC_DANCING].val2),bl->m,dx,dy);
	}
	ud->walktimer = 1;
	if(sd) {
		map_foreachinmovearea(clif_pcinsight,bl->m,x-AREA_SIZE,y-AREA_SIZE,x+AREA_SIZE,y+AREA_SIZE,-dx,-dy,BL_ALL,sd);
		map_foreachinmovearea(mob_ai_hard_spawn_sub,bl->m,x-AREA_SIZE*2,y-AREA_SIZE*2,x+AREA_SIZE*2,y+AREA_SIZE*2,-dx,-dy,BL_MOB,sd,1);
	} else if(md) {
		map_foreachinmovearea(clif_mobinsight,bl->m,x-AREA_SIZE,y-AREA_SIZE,x+AREA_SIZE,y+AREA_SIZE,-dx,-dy,BL_PC,md);
		map_foreachinmovearea(mob_ai_hard_spawn_sub,bl->m,x-AREA_SIZE*2,y-AREA_SIZE*2,x+AREA_SIZE*2,y+AREA_SIZE*2,-dx,-dy,BL_PC|BL_HOM|BL_MERC|BL_ELEM,md,1);
	} else if(pd) {
		map_foreachinmovearea(clif_petinsight,bl->m,x-AREA_SIZE,y-AREA_SIZE,x+AREA_SIZE,y+AREA_SIZE,-dx,-dy,BL_PC,pd);
	} else if(hd) {
		map_foreachinmovearea(clif_hominsight,bl->m,x-AREA_SIZE,y-AREA_SIZE,x+AREA_SIZE,y+AREA_SIZE,-dx,-dy,BL_PC,hd);
		map_foreachinmovearea(mob_ai_hard_spawn_sub,bl->m,x-AREA_SIZE*2,y-AREA_SIZE*2,x+AREA_SIZE*2,y+AREA_SIZE*2,-dx,-dy,BL_MOB,hd,1);
	} else if(mcd) {
		map_foreachinmovearea(clif_mercinsight,bl->m,x-AREA_SIZE,y-AREA_SIZE,x+AREA_SIZE,y+AREA_SIZE,-dx,-dy,BL_PC,mcd);
		map_foreachinmovearea(mob_ai_hard_spawn_sub,bl->m,x-AREA_SIZE*2,y-AREA_SIZE*2,x+AREA_SIZE*2,y+AREA_SIZE*2,-dx,-dy,BL_MOB,mcd,1);
	} else if(eld) {
		map_foreachinmovearea(clif_eleminsight,bl->m,x-AREA_SIZE,y-AREA_SIZE,x+AREA_SIZE,y+AREA_SIZE,-dx,-dy,BL_PC,eld);
		map_foreachinmovearea(mob_ai_hard_spawn_sub,bl->m,x-AREA_SIZE*2,y-AREA_SIZE*2,x+AREA_SIZE*2,y+AREA_SIZE*2,-dx,-dy,BL_MOB,eld,1);
	}
	ud->walktimer = -1;

	if(sd) {
		if(sd->status.party_id > 0 && party_search(sd->status.party_id) != NULL) {	// パーティのＨＰ情報通知検査
			if(map_foreachinmovearea(party_send_hp_check,sd->bl.m,x-AREA_SIZE,y-AREA_SIZE,x+AREA_SIZE,y+AREA_SIZE,-dx,-dy,BL_PC,sd->status.party_id)) {
				sd->party_hp = -1;
			}
		}

		/* ディボーション検査 */
		for(i=0; i<5; i++) {
			if(sd->dev.val1[i]) {
				skill_devotion3(sd,sd->dev.val1[i]);
			}
		}
		/* 被シャドウフォーム検査 */
		if(sd->shadowform_id != 0) {
			skill_shadowform2(sd);
		}

		if(sd->sc.count > 0)
		{
			/* 被ディボーション検査 */
			if(sd->sc.data[SC_DEVOTION].timer != -1) {
				skill_devotion2(&sd->bl,sd->sc.data[SC_DEVOTION].val1);
			}
			/* マリオネット検査 */
			if(sd->sc.data[SC_MARIONETTE].timer != -1) {
				skill_marionette(sd,sd->sc.data[SC_MARIONETTE].val2);
			}
			/* 被マリオネット検査 */
			if(sd->sc.data[SC_MARIONETTE2].timer != -1) {
				skill_marionette2(sd,sd->sc.data[SC_MARIONETTE2].val2);
			}
			/* ダンスチェック */
			if(sd->sc.data[SC_LONGINGFREEDOM].timer != -1) {
				// 範囲外に出たら止める
				if(path_distance(sd->bl.x,sd->bl.y,sd->dance.x,sd->dance.y) > 4)
					skill_stop_dancing(&sd->bl,0);
			}
			/* ヘルモードチェック */
			if(battle_config.hermode_wp_check &&
			   sd->sc.data[SC_DANCING].timer != -1 &&
			   sd->sc.data[SC_DANCING].val1 == CG_HERMODE) {
				if(skill_hermode_wp_check(&sd->bl) == 0)
					skill_stop_dancing(&sd->bl,0);
			}
			/* クローキングの消滅検査 */
			if(pc_iscloaking(sd) && sd->sc.data[SC_CLOAKING].timer != -1) {
				if(sd->sc.data[SC_CLOAKING].val1 < 3)
					skill_check_cloaking(&sd->bl);
			}
			/* タイリギ歩数カウント */
			if(sd->sc.data[SC_RUN].timer != -1) {
				sd->sc.data[SC_RUN].val4++;
			}
			/* 回転カウントリセット */
			if(sd->sc.data[SC_ROLLINGCUTTER].timer != -1) {
				status_change_end(&sd->bl,SC_ROLLINGCUTTER,-1);
			}
			/* シャドウフォーム検査 */
			if(sd->sc.data[SC__SHADOWFORM].timer != -1) {
				skill_shadowform(sd,sd->sc.data[SC__SHADOWFORM].val2);
			}
			// ファイアー/エレクトリックウォーク配置
			if(sd->sc.data[SC_PROPERTYWALK].timer != -1) {
				skill_unitsetting(&sd->bl,sd->sc.data[SC_PROPERTYWALK].val2,sd->sc.data[SC_PROPERTYWALK].val1,sd->bl.x,sd->bl.y,0);
				if(--sd->sc.data[SC_PROPERTYWALK].val3 <= 0) {
					status_change_end(&sd->bl, SC_PROPERTYWALK, -1);
				}
			}
		}
		// ギルドスキル有効
		pc_check_guild_skill_effective_range(sd);

		if(map_getcell(sd->bl.m,x,y,CELL_CHKNPC))
			npc_touch_areanpc(sd,sd->bl.m,x,y);
		else
			sd->areanpc_id = 0;
	}
	else if(md) {
		if(md->sc.option&OPTION_CLOAKING)
			skill_check_cloaking(&md->bl);

		if(map_getcell(md->bl.m,x,y,CELL_CHKNPC))
			npc_touch_areanpc2(md,md->bl.m,x,y);
		else
			md->areanpc_id = 0;
	}

	ud->walkpath.path_pos++;
	if(ud->state.change_walk_target) {
		unit_walktoxy_sub(bl);
		return 0;
	}

	if(ud->walkpath.path_pos >= ud->walkpath.path_len)
		i = -1;
	else if(ud->walkpath.path[ud->walkpath.path_pos] & 1)
		i = status_get_speed(bl)*14/10;
	else
		i = status_get_speed(bl);

	if(i > 0) {
		// 移動途中
		dir = ud->walkpath.path[ud->walkpath.path_pos];
		dx  = dirx[(int)dir];
		dy  = diry[(int)dir];

		if(sd && sd->sc.data[SC_RUN].timer != -1) {
			// タイリギの障害物に当たった
			if(map_getcell(sd->bl.m,x+dx,y+dy,CELL_CHKNOPASS) ||
			   map_getcell(sd->bl.m,x   ,y+dy,CELL_CHKNOPASS) ||
			   map_getcell(sd->bl.m,x+dx,y   ,CELL_CHKNOPASS) ||
			   map_count_oncell(sd->bl.m,x+dx,y+dy,BL_PC|BL_MOB|BL_NPC) > 0) {
				skill_blown(&sd->bl,&sd->bl,skill_get_blewcount(TK_RUN,sd->sc.data[SC_RUN].val1)|SAB_NODAMAGE);
				status_change_end(&sd->bl,SC_RUN,-1);
				clif_status_change(&sd->bl,SI_RUN_STOP,1,0,0,0,0);
				pc_setdir(sd, dir, dir);
				return 0;
			}
		} else if(sd && sd->sc.data[SC_WUGDASH].timer != -1) {
			// ウォーグダッシュ中に障害物に当たった
			if(map_getcell(sd->bl.m,x+dx,y+dy,CELL_CHKNOPASS) ||
			   map_getcell(sd->bl.m,x   ,y+dy,CELL_CHKNOPASS) ||
			   map_getcell(sd->bl.m,x+dx,y   ,CELL_CHKNOPASS) ||
			   map_count_oncell(sd->bl.m,x+dx,y+dy,BL_PC|BL_MOB|BL_NPC) > 0) {
				if(pc_checkskill(sd,RA_WUGSTRIKE))
					skill_castend_damage_id(&sd->bl,&sd->bl,RA_WUGDASH,sd->sc.data[SC_WUGDASH].val1,tick,0);
				status_change_end(&sd->bl,SC_WUGDASH,-1);
				return 0;
			}
		} else if(map_getcell(bl->m,x+dx,y+dy,CELL_CHKNOPASS)) {	// 障害物に当たった
			if(!sc || sc->data[SC_FORCEWALKING].timer == -1) {
				clif_fixwalkpos(bl);
				return 0;
			}
		}
		ud->walktimer = add_timer(tick+i,unit_walktoxy_timer,id,INT2PTR(ud->walkpath.path_pos));
	} else {
		// 目的地に着いた
		if(sd && (sd->sc.data[SC_RUN].timer != -1 || sd->sc.data[SC_WUGDASH].timer != -1)) {
			// 継続判定
			pc_runtodir(sd);
		}
		else if(md && md->sc.data[SC_SELFDESTRUCTION].timer != -1) {
			md->dir = md->sc.data[SC_SELFDESTRUCTION].val4;
			unit_walktodir(bl,1);
		}
		else if(sc && sc->data[SC_FORCEWALKING].timer != -1) {
			if(sc->data[SC_FORCEWALKING].val4 == 0) {
				sc->data[SC_FORCEWALKING].val4++;
				unit_walktodir(bl,1);
			}
			else if(sc->data[SC_FORCEWALKING].val4 == 1) {
				sc->data[SC_FORCEWALKING].val4++;
			}
		}
		else if(md && md->target_id > 0) {
			// MobはAIを実行
			md->last_thinktime = tick - MIN_MOBTHINKTIME;
			mob_ai_sub_hard(md, tick);
		}

		// とまったときの位置の再送信は不要（カクカクするため）
		// clif_fixwalkpos(bl);
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int unit_walktoxy(struct block_list *bl, int x, int y)
{
	struct unit_data        *ud  = NULL;
	struct map_session_data *sd  = NULL;
	struct pet_data         *pd  = NULL;
	struct mob_data         *md  = NULL;
	struct homun_data       *hd  = NULL;
	struct merc_data        *mcd = NULL;
	struct elem_data        *eld = NULL;
	struct status_change    *sc  = NULL;

	nullpo_retr(0, bl);

	if( (sd = BL_DOWNCAST( BL_PC,  bl ) ) ) {
		ud = &sd->ud;
	} else if( (md = BL_DOWNCAST( BL_MOB, bl ) ) ) {
		ud = &md->ud;
	} else if( (pd = BL_DOWNCAST( BL_PET, bl ) ) ) {
		ud = &pd->ud;
	} else if( (hd = BL_DOWNCAST( BL_HOM, bl ) ) ) {
		ud = &hd->ud;
	} else if( (mcd = BL_DOWNCAST( BL_MERC, bl ) ) ) {
		ud = &mcd->ud;
	} else if( (eld = BL_DOWNCAST( BL_ELEM, bl ) ) ) {
		ud = &eld->ud;
	}
	if( ud == NULL ) return 0;

	// 移動出来ないユニットは弾く(ペットは除く)
	if( !pd && !(status_get_mode(bl)&MD_CANMOVE) )
		return 0;

	if( !unit_can_move(bl) )
		return 0;

	sc = status_get_sc(bl);

	// 強制移動中は混乱から除外
	if(sc && sc->data[SC_CONFUSION].timer != -1 && sc->data[SC_FORCEWALKING].timer == -1) {
		ud->to_x = bl->x + atn_rand()%7 - 3;
		ud->to_y = bl->y + atn_rand()%7 - 3;
	} else {
		ud->to_x = x;
		ud->to_y = y;
	}

	if(ud->walktimer != -1) {
		// 現在歩いている最中の目的地変更なのでマス目の中心に来た時に
		// timer関数からunit_walktoxy_subを呼ぶようにする
		ud->state.change_walk_target = 1;
		return 1;
	}
	return unit_walktoxy_sub(bl);
}

/*==========================================
 * 向いている方向にstep分歩く
 *------------------------------------------
 */
int unit_walktodir(struct block_list *bl,int step)
{
	int i,to_x,to_y,dir_x,dir_y,d;

	nullpo_retr(0, bl);

	d = status_get_dir(bl);

	to_x = bl->x;
	to_y = bl->y;
	dir_x = dirx[d];
	dir_y = diry[d];

	for(i=0; i<step; i++) {
		if(!map_getcell(bl->m,to_x+dir_x,to_y+dir_y,CELL_CHKPASS))
			break;

		// 次のセルへ１歩で移動可能でないなら
		if(map_getcell(bl->m,to_x+dir_x,to_y+dir_y,CELL_CHKNOPASS) ||
		   map_getcell(bl->m,to_x      ,to_y+dir_y,CELL_CHKNOPASS) ||
		   map_getcell(bl->m,to_x+dir_x,to_y      ,CELL_CHKNOPASS))
			break;

		to_x += dir_x;
		to_y += dir_y;
	}
	unit_walktoxy(bl, to_x, to_y);

	return 1;
}

/*==========================================
 * 進入不可セルを無視して歩く要求
 *------------------------------------------
 */
int unit_forcewalktodir(struct block_list *bl,int distance)
{
	struct status_change *sc = NULL;
	int i,to_x,to_y,dir_x,dir_y,d;

	nullpo_retr(0, bl);

	sc = status_get_sc(bl);
	d  = status_get_dir(bl);

	to_x = bl->x;
	to_y = bl->y;
	dir_x = dirx[d];
	dir_y = diry[d];

	for(i=distance; i>1; i--) {
		if(map_getcell(bl->m,bl->x+dir_x*i,bl->y+dir_y*i,CELL_CHKPASS)) {
			to_x = bl->x+dir_x*(i-1);
			to_y = bl->y+dir_y*(i-1);
			break;
		}
	}

	if(sc) {
		sc->data[SC_FORCEWALKING].val4 = 0;
	}
	unit_walktoxy(bl, to_x, to_y);

	return 1;
}

/*==========================================
 * 位置移動
 *   flag -> 0xXY
 *	X : 経路検索方法、0,1,2
 *	Y : パケットの種類、0,1,2
 *------------------------------------------
 */
int unit_movepos(struct block_list *bl,int dst_x,int dst_y,int flag)
{
	int moveblock;
	int dx,dy,dir,x[4],y[4];
	unsigned int tick = gettick();
	struct map_session_data *sd  = NULL;
	struct pet_data         *pd  = NULL;
	struct mob_data         *md  = NULL;
	struct homun_data       *hd  = NULL;
	struct merc_data        *mcd = NULL;
	struct elem_data        *eld = NULL;
	struct unit_data        *ud  = NULL;

	nullpo_retr(1, bl);

	if( bl->prev == NULL ) return 1;

	if( (sd = BL_DOWNCAST( BL_PC,  bl ) ) ) {
		ud = &sd->ud;
	} else if( (md = BL_DOWNCAST( BL_MOB, bl ) ) ) {
		ud = &md->ud;
	} else if( (pd = BL_DOWNCAST( BL_PET, bl ) ) ) {
		ud = &pd->ud;
	} else if( (hd = BL_DOWNCAST( BL_HOM, bl ) ) ) {
		ud = &hd->ud;
	} else if( (mcd = BL_DOWNCAST( BL_MERC, bl ) ) ) {
		ud = &mcd->ud;
	} else if( (eld = BL_DOWNCAST( BL_ELEM, bl ) ) ) {
		ud = &eld->ud;
	}
	if( ud == NULL ) return 1;

	unit_stop_walking(bl,1);

	if(ud->attacktimer != -1) {
		delete_timer( ud->attacktimer, unit_attack_timer );
		ud->attacktimer = -1;
	}

	switch ( (flag>>4)&0x0f ) {
		case 0:
			if(path_search(NULL,bl->m,bl->x,bl->y,dst_x,dst_y,0))
				return 1;
			break;
		case 1:
			if(path_search2(NULL,bl->m,bl->x,bl->y,dst_x,dst_y,0))
				return 1;
			break;
		case 2:
			if(path_search3(NULL,bl->m,bl->x,bl->y,dst_x,dst_y,0))
				return 1;
			break;
	}

	dir = path_calc_dir(bl, dst_x, dst_y);
	if(sd)
		pc_setdir(sd, dir, dir);

	// 位置変更前、変更後も画面内にあるクライアントの座標を記録
	x[0] = bl->x-AREA_SIZE;
	x[1] = bl->x+AREA_SIZE;
	x[2] = dst_x-AREA_SIZE;
	x[3] = dst_x+AREA_SIZE;
	y[0] = bl->y-AREA_SIZE;
	y[1] = bl->y+AREA_SIZE;
	y[2] = dst_y-AREA_SIZE;
	y[3] = dst_y+AREA_SIZE;

	dx = dst_x - bl->x;
	dy = dst_y - bl->y;

	moveblock = ( bl->x/BLOCK_SIZE != dst_x/BLOCK_SIZE || bl->y/BLOCK_SIZE != dst_y/BLOCK_SIZE);

	if(sd) {	/* 画面外に出たので消去 */
		map_foreachinmovearea(clif_pcoutsight,bl->m,bl->x-AREA_SIZE,bl->y-AREA_SIZE,bl->x+AREA_SIZE,bl->y+AREA_SIZE,dx,dy,BL_ALL,sd);
		map_foreachinmovearea(mob_ai_hard_spawn_sub,bl->m,bl->x-AREA_SIZE*2,bl->y-AREA_SIZE*2,bl->x+AREA_SIZE*2,bl->y+AREA_SIZE*2,dx,dy,BL_MOB,sd,0);
	} else if(md) {
		map_foreachinmovearea(clif_moboutsight,bl->m,bl->x-AREA_SIZE,bl->y-AREA_SIZE,bl->x+AREA_SIZE,bl->y+AREA_SIZE,dx,dy,BL_PC,md);
		map_foreachinmovearea(mob_ai_hard_spawn_sub,bl->m,bl->x-AREA_SIZE*2,bl->y-AREA_SIZE*2,bl->x+AREA_SIZE*2,bl->y+AREA_SIZE*2,dx,dy,BL_PC|BL_HOM|BL_MERC|BL_ELEM,md,0);
	} else if(pd) {
		map_foreachinmovearea(clif_petoutsight,bl->m,bl->x-AREA_SIZE,bl->y-AREA_SIZE,bl->x+AREA_SIZE,bl->y+AREA_SIZE,dx,dy,BL_PC,pd);
	} else if(hd) {
		map_foreachinmovearea(clif_homoutsight,bl->m,bl->x-AREA_SIZE,bl->y-AREA_SIZE,bl->x+AREA_SIZE,bl->y+AREA_SIZE,dx,dy,BL_PC,hd);
		map_foreachinmovearea(mob_ai_hard_spawn_sub,bl->m,bl->x-AREA_SIZE*2,bl->y-AREA_SIZE*2,bl->x+AREA_SIZE*2,bl->y+AREA_SIZE*2,dx,dy,BL_MOB,hd,0);
	} else if(mcd) {
		map_foreachinmovearea(clif_mercoutsight,bl->m,bl->x-AREA_SIZE,bl->y-AREA_SIZE,bl->x+AREA_SIZE,bl->y+AREA_SIZE,dx,dy,BL_PC,mcd);
		map_foreachinmovearea(mob_ai_hard_spawn_sub,bl->m,bl->x-AREA_SIZE*2,bl->y-AREA_SIZE*2,bl->x+AREA_SIZE*2,bl->y+AREA_SIZE*2,dx,dy,BL_MOB,mcd,0);
	} else if(eld) {
		map_foreachinmovearea(clif_elemoutsight,bl->m,bl->x-AREA_SIZE,bl->y-AREA_SIZE,bl->x+AREA_SIZE,bl->y+AREA_SIZE,dx,dy,BL_PC,eld);
		map_foreachinmovearea(mob_ai_hard_spawn_sub,bl->m,bl->x-AREA_SIZE*2,bl->y-AREA_SIZE*2,bl->x+AREA_SIZE*2,bl->y+AREA_SIZE*2,dx,dy,BL_MOB,eld,0);
	}

	if(!pd) skill_unit_move(bl,tick,0);
	if(moveblock) map_delblock(bl);
	bl->x = dst_x;
	bl->y = dst_y;
	if(moveblock) map_addblock(bl);
	if(!pd) skill_unit_move(bl,tick,1);

	if(sd) {	/* 画面内に入ってきたので表示 */
		map_foreachinmovearea(clif_pcinsight,bl->m,bl->x-AREA_SIZE,bl->y-AREA_SIZE,bl->x+AREA_SIZE,bl->y+AREA_SIZE,-dx,-dy,BL_ALL,sd);
		map_foreachinmovearea(mob_ai_hard_spawn_sub,bl->m,bl->x-AREA_SIZE*2,bl->y-AREA_SIZE*2,bl->x+AREA_SIZE*2,bl->y+AREA_SIZE*2,-dx,-dy,BL_MOB,sd,1);
	} else if(md) {
		map_foreachinmovearea(clif_mobinsight,bl->m,bl->x-AREA_SIZE,bl->y-AREA_SIZE,bl->x+AREA_SIZE,bl->y+AREA_SIZE,-dx,-dy,BL_PC,md);
		map_foreachinmovearea(mob_ai_hard_spawn_sub,bl->m,bl->x-AREA_SIZE*2,bl->y-AREA_SIZE*2,bl->x+AREA_SIZE*2,bl->y+AREA_SIZE*2,-dx,-dy,BL_PC|BL_HOM|BL_MERC|BL_ELEM,md,1);
	} else if(pd) {
		map_foreachinmovearea(clif_petinsight,bl->m,bl->x-AREA_SIZE,bl->y-AREA_SIZE,bl->x+AREA_SIZE,bl->y+AREA_SIZE,-dx,-dy,BL_PC,pd);
	} else if(hd) {
		map_foreachinmovearea(clif_hominsight,bl->m,bl->x-AREA_SIZE,bl->y-AREA_SIZE,bl->x+AREA_SIZE,bl->y+AREA_SIZE,-dx,-dy,BL_PC,hd);
		map_foreachinmovearea(mob_ai_hard_spawn_sub,bl->m,bl->x-AREA_SIZE*2,bl->y-AREA_SIZE*2,bl->x+AREA_SIZE*2,bl->y+AREA_SIZE*2,-dx,-dy,BL_MOB,hd,1);
	} else if(mcd) {
		map_foreachinmovearea(clif_mercinsight,bl->m,bl->x-AREA_SIZE,bl->y-AREA_SIZE,bl->x+AREA_SIZE,bl->y+AREA_SIZE,-dx,-dy,BL_PC,mcd);
		map_foreachinmovearea(mob_ai_hard_spawn_sub,bl->m,bl->x-AREA_SIZE*2,bl->y-AREA_SIZE*2,bl->x+AREA_SIZE*2,bl->y+AREA_SIZE*2,-dx,-dy,BL_MOB,mcd,1);
	} else if(eld) {
		map_foreachinmovearea(clif_eleminsight,bl->m,bl->x-AREA_SIZE,bl->y-AREA_SIZE,bl->x+AREA_SIZE,bl->y+AREA_SIZE,-dx,-dy,BL_PC,eld);
		map_foreachinmovearea(mob_ai_hard_spawn_sub,bl->m,bl->x-AREA_SIZE*2,bl->y-AREA_SIZE*2,bl->x+AREA_SIZE*2,bl->y+AREA_SIZE*2,-dx,-dy,BL_MOB,eld,1);
	}

	if( flag&1 )		// 吹き飛ばし用パケット送信
		clif_blown(bl,dst_x,dst_y);
	else if( flag&2 )		// 残影用パケット送信
		clif_bodyrelocation(bl,dst_x,dst_y);
	else			// 位置変更情報送信
		clif_fixpos2(bl,x,y);

	if(sd) {
		if(sd->status.party_id > 0 && party_search(sd->status.party_id) != NULL) {	// パーティのＨＰ情報通知検査
			if(map_foreachinmovearea(party_send_hp_check,sd->bl.m,sd->bl.x-AREA_SIZE,sd->bl.y-AREA_SIZE,sd->bl.x+AREA_SIZE,sd->bl.y+AREA_SIZE,-dx,-dy,BL_PC,sd->status.party_id)) {
				sd->party_hp = -1;
			}
		}

		// クローキングの消滅検査
		if(pc_iscloaking(sd) && sd->sc.data[SC_CLOAKING].timer != -1 && sd->sc.data[SC_CLOAKING].val1 < 3) {
			skill_check_cloaking(&sd->bl);
		}

		// 温もりの位置変更
		if(sd->sc.data[SC_WARM].timer != -1) {
			skill_unit_move_unit_group(map_id2sg(sd->sc.data[SC_WARM].val4),sd->bl.m,dx,dy);
		}
		// ニュートラルバリアーの位置変更
		if(sd->sc.data[SC_NEUTRALBARRIER_USER].timer != -1) {
			skill_unit_move_unit_group(map_id2sg(sd->sc.data[SC_NEUTRALBARRIER_USER].val4),sd->bl.m,dx,dy);
		}
		// ステルスフィールドの位置変更
		if(sd->sc.data[SC_STEALTHFIELD_USER].timer != -1) {
			skill_unit_move_unit_group(map_id2sg(sd->sc.data[SC_STEALTHFIELD_USER].val4),sd->bl.m,dx,dy);
		}
		// バンディングの位置変更
		if(sd->sc.data[SC_BANDING].timer != -1) {
			skill_unit_move_unit_group(map_id2sg(sd->sc.data[SC_BANDING].val4),sd->bl.m,dx,dy);
		}

		if(map_getcell(bl->m,bl->x,bl->y,CELL_CHKNPC))
			npc_touch_areanpc(sd,sd->bl.m,sd->bl.x,sd->bl.y);
		else
			sd->areanpc_id=0;
	}
	if(md) {
		struct status_change *sc = NULL;
		sc = status_get_sc(bl);
		if(sc && sc->data[SC_DANCING].timer != -1)
			skill_unit_move_unit_group(map_id2sg(sc->data[SC_DANCING].val2),bl->m,dx,dy);
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int unit_setdir(struct block_list *bl,int dir)
{
	nullpo_retr( 0, bl );

	if(bl->type == BL_PC)
		pc_setdir((struct map_session_data *)bl, dir, dir);
	else if(bl->type == BL_MOB)
		((struct mob_data *)bl)->dir = dir;
	else if(bl->type == BL_PET)
		((struct pet_data *)bl)->dir = dir;
	else if(bl->type == BL_HOM)
		((struct homun_data *)bl)->dir = dir;
	else if(bl->type == BL_MERC)
		((struct merc_data *)bl)->dir = dir;
	else if(bl->type == BL_ELEM)
		((struct elem_data *)bl)->dir = dir;

	clif_changedir( bl, dir, dir );
	return 0;
}

/*==========================================
 * 歩行停止
 *------------------------------------------
 */
int unit_stop_walking(struct block_list *bl,int type)
{
	struct map_session_data *sd  = NULL;
	struct pet_data         *pd  = NULL;
	struct mob_data         *md  = NULL;
	struct homun_data       *hd  = NULL;
	struct merc_data        *mcd = NULL;
	struct elem_data        *eld = NULL;
	struct unit_data        *ud  = NULL;

	nullpo_retr(0, bl);

	if( (sd = BL_DOWNCAST( BL_PC,  bl ) ) ) {
		ud = &sd->ud;
	} else if( (md = BL_DOWNCAST( BL_MOB, bl ) ) ) {
		ud = &md->ud;
	} else if( (pd = BL_DOWNCAST( BL_PET, bl ) ) ) {
		ud = &pd->ud;
	} else if( (hd = BL_DOWNCAST( BL_HOM, bl ) ) ) {
		ud = &hd->ud;
	} else if( (mcd = BL_DOWNCAST( BL_MERC, bl ) ) ) {
		ud = &mcd->ud;
	} else if( (eld = BL_DOWNCAST( BL_ELEM, bl ) ) ) {
		ud = &eld->ud;
	}
	if( ud == NULL ) return 0;

	ud->to_x = bl->x;
	ud->to_y = bl->y;

	if(type&0x08 && md) {
		if(ud->walktimer == -1)
			return 0;
	} else {
		ud->walkpath.path_len = 0;
		ud->walkpath.path_pos = 0;

		if(ud->walktimer == -1)
			return 0;

		delete_timer(ud->walktimer, unit_walktoxy_timer);
		ud->walktimer = -1;
	}

	if(type&0x01) { // 位置補正送信が必要
		clif_fixwalkpos(bl);
	}
	if(type&0x02) { // ダメージ食らう
		unsigned int tick = gettick();
		int delay = status_get_dmotion(bl);
		if( (sd && battle_config.pc_damage_delay) || (md && battle_config.monster_damage_delay) ) {
			ud->canmove_tick = tick + delay;
		}
		else if( (sd && !battle_config.pc_damage_delay) || (md && !battle_config.monster_damage_delay) ) {
			ud->canmove_tick = (tick)/2 + (delay)/5;
		}
	}
	if(type&0x04 && md) {
		int dx = ud->to_x - md->bl.x;
		int dy = ud->to_y - md->bl.y;

		if(dx < 0) dx = -1; else if(dx > 0) dx = 1;
		if(dy < 0) dy = -1; else if(dy > 0) dy = 1;

		if(dx || dy) {
			unit_walktoxy( bl, md->bl.x+dx, md->bl.y+dy );
		}
	}

	return 0;
}

/*==========================================
 * 位置移動計算（PET, HOM, MERC, ELEM用）
 *------------------------------------------
 */
int unit_calc_pos(struct block_list *bl,int tx,int ty,int dir,int distance)
{
	struct pet_data   *pd = NULL;
	struct homun_data *hd = NULL;
	struct merc_data *mcd = NULL;
	struct elem_data *eld = NULL;
	struct unit_data  *ud = NULL;
	int x, y, dx, dy;
	int j = 0;

	nullpo_retr(0, bl);

	if( (pd = BL_DOWNCAST( BL_PET, bl ) ) ) {
		ud = &pd->ud;
	} else if( (hd = BL_DOWNCAST( BL_HOM, bl ) ) ) {
		ud = &hd->ud;
	} else if( (mcd = BL_DOWNCAST( BL_MERC, bl ) ) ) {
		ud = &mcd->ud;
	} else if( (eld = BL_DOWNCAST( BL_ELEM, bl ) ) ) {
		ud = &eld->ud;
	}
	if( ud == NULL ) return 0;

	ud->to_x = tx;
	ud->to_y = ty;

	if(dir < 0 || dir >= 8)
		return 1;

	dx = -dirx[dir] * distance;
	dy = -diry[dir] * distance;
	x  = tx + dx;
	y  = ty + dy;

	if(!(j = unit_can_reach(ud->bl, x, y))) {
		if(dx > 0) x--;
		else if(dx < 0) x++;
		if(dy > 0) y--;
		else if(dy < 0) y++;

		if(!(j = unit_can_reach(ud->bl, x, y))) {
			int i;
			for(i = 0; i < 12; i++) {
				int k = atn_rand()%8;

				dx = -dirx[k] * distance;
				dy = -diry[k] * distance;
				x  = tx + dx;
				y  = ty + dy;

				if((j = unit_can_reach(ud->bl, x, y)))
					break;

				if(dx > 0) x--;
				else if(dx < 0) x++;
				if(dy > 0) y--;
				else if(dy < 0) y++;

				if((j = unit_can_reach(ud->bl, x, y)))
					break;
			}
			if(!j) {
				x = tx;
				y = ty;
				if(!unit_can_reach(ud->bl, x, y))
					return 1;
			}
		}
	}
	ud->to_x = x;
	ud->to_y = y;

	return 0;
}

/*==========================================
 * スキル使用（ID指定）
 *------------------------------------------
 */
int unit_skilluse_id(struct block_list *src, int target_id, int skill_num, int skill_lv)
{
	int id = skill_get_skilldb_id(skill_num);

	if( id == 0 )
		return 0;
	if( skill_lv <= 0 || skill_lv > MAX_SKILL_LEVEL )
		return 0;

	return unit_skilluse_id2(
		src, target_id, skill_num, skill_lv,
		skill_castfix(src, skill_num, skill_db[id].cast[skill_lv-1], skill_db[id].fixedcast[skill_lv-1]),
		skill_db[id].castcancel
	);
}

int unit_skilluse_id2(struct block_list *src, int target_id, int skill_num, int skill_lv, int casttime, int castcancel)
{
	struct map_session_data *src_sd  = NULL;
	struct pet_data         *src_pd  = NULL;
	struct mob_data         *src_md  = NULL;
	struct homun_data       *src_hd  = NULL;
	struct merc_data        *src_mcd = NULL;
	struct elem_data        *src_eld = NULL;
	struct unit_data        *src_ud  = NULL;
	unsigned int tick;
	int range;
	struct block_list       *target;
	struct map_session_data *target_sd  = NULL;
	struct mob_data         *target_md  = NULL;
	int forcecast = 0, zone = 0, nomemorize = 0;
	struct status_change *sc;

	nullpo_retr(0, src);

	if( (src_sd = BL_DOWNCAST( BL_PC, src ) ) ) {
		src_ud = &src_sd->ud;
	} else if( (src_md = BL_DOWNCAST( BL_MOB, src ) ) ) {
		src_ud = &src_md->ud;
	} else if( (src_pd = BL_DOWNCAST( BL_PET, src ) ) ) {
		src_ud = &src_pd->ud;
	} else if( (src_hd = BL_DOWNCAST( BL_HOM, src ) ) ) {
		src_ud = &src_hd->ud;
	} else if( (src_mcd = BL_DOWNCAST( BL_MERC, src ) ) ) {
		src_ud = &src_mcd->ud;
	} else if( (src_eld = BL_DOWNCAST( BL_ELEM, src ) ) ) {
		src_ud = &src_eld->ud;
	}
	if( src_ud == NULL ) return 0;

	if( unit_isdead(src) )		 return 0;	// 死んでいないか
	if( skill_num == SR_GENTLETOUCH_CURE ) {
		if( src_sd->sc.opt1 == OPT1_SLEEP )
			return 0;	// 点穴-快-は睡眠状態では使えない
	} else {
		if( src_sd && src_sd->sc.opt1 > OPT1_NORMAL && src_sd->sc.opt1 != OPT1_BURNNING )
			return 0;	// 沈黙や異常（ただし、グリムなどの判定をする）
	}

	// スキル制限
	zone = skill_get_zone(skill_num);
	if(zone) {
		int m = src->m;
		int ban = 0;

		if(map[m].flag.turbo && zone&16)
			ban = 1;
		else if(map[m].flag.normal && zone&1)
			ban = 1;
		else if(map[m].flag.pvp && zone&2)
			ban = 1;
		else if(map[m].flag.gvg && zone&4)
			ban = 1;
		else if(map[m].flag.pk && zone&8)
			ban = 1;
		if(ban) {
			if(src_sd) {
				if(skill_num == AL_TELEPORT || skill_num == AL_WARP)
					clif_skill_teleportmessage(src_sd,0);
				else
					clif_skill_fail(src_sd,skill_num,0,0,0);
			}
			return 0;
		}
	}

	sc = status_get_sc(src);

	// 虚無の影中はスキル使用に失敗することがある(確率暫定)
	if(sc && sc->data[SC_KYOMU].timer != -1) {
		if(atn_rand()%100 < 10) {
			if(src_sd)
				clif_skill_fail(src_sd,skill_num,0,0,0);
		}
	}

	// ターゲットの自動選択
	switch(skill_num) {
	case TK_STORMKICK:		/* 旋風蹴り */
	case TK_DOWNKICK:		/* 下段蹴り */
	case TK_TURNKICK:		/* 回転蹴り */
	case TK_COUNTER:		/* カウンター蹴り */
	case MO_COMBOFINISH:		/* 猛龍拳 */
	case CH_TIGERFIST:		/* 伏虎拳 */
	case CH_CHAINCRUSH:		/* 連柱崩撃 */
	case SR_FALLENEMPIRE:	/* 大纏崩捶 */
		target_id = src_ud->attacktarget;
		break;
	case MO_CHAINCOMBO:		/* 連打掌 */
		target_id = src_ud->attacktarget;
		if(sc && sc->data[SC_BLADESTOP].timer != -1)
			target_id = sc->data[SC_BLADESTOP].val4;
		break;
	case TK_JUMPKICK:		/* 飛び蹴り（ティオアプチャギ）*/
		if(sc && sc->data[SC_DODGE_DELAY].timer != -1 && src->id == target_id)
			target_id = sc->data[SC_DODGE_DELAY].val2;
		break;
	case MO_EXTREMITYFIST:		/* 阿修羅覇鳳拳 */
		if(sc && sc->data[SC_COMBO].timer != -1 && (sc->data[SC_COMBO].val1 == MO_COMBOFINISH || sc->data[SC_COMBO].val1 == CH_CHAINCRUSH) )
			target_id = src_ud->attacktarget;
		break;
	case SR_TIGERCANNON:	/* 號砲 */
	case SR_GATEOFHELL:		/* 羅刹破凰撃 */
		if(sc && sc->data[SC_COMBO].timer != -1 && sc->data[SC_COMBO].val1 == SR_FALLENEMPIRE)
			target_id = src_ud->attacktarget;
		break;
	case WE_MALE:
	case WE_FEMALE:
		{
			struct map_session_data *p_sd = NULL;
			if(src_sd) {
				p_sd = pc_get_partner(src_sd);
			}
			target_id = (p_sd)? p_sd->bl.id: 0;
		}
		break;
	case GC_WEAPONCRUSH:	/* ウェポンクラッシュ */
		if(sc && sc->data[SC_WEAPONBLOCKING2].timer != -1)
			target_id = sc->data[SC_WEAPONBLOCKING2].val2;
		break;
	}

	if( (target = map_id2bl(target_id)) == NULL ) {
		if(src_sd)
			clif_skill_fail(src_sd,skill_num,0,0,0);
		return 0;
	}

	if(skill_get_inf2(skill_num)&0x200 && src->id == target_id)
		return 0;

	if(src->m != target->m)         return 0; // 同じマップかどうか
	if(!src->prev || !target->prev) return 0; // map 上に存在するか

	target_sd  = BL_DOWNCAST( BL_PC,  target );
	target_md  = BL_DOWNCAST( BL_MOB, target );

	// 直前のスキル状況の記録
	if(src_sd) {
		switch(skill_num) {
		case SA_CASTCANCEL:
		case SO_SPELLFIST:				/* スペルフィスト */
			if(src_ud->skillid != skill_num) { // キャストキャンセル自体は覚えない
				src_sd->skill_used.id = src_ud->skillid;
				src_sd->skill_used.lv = src_ud->skilllv;
				break;
			}
		case BD_ENCORE:					/* アンコール */
			 // 前回使用した踊りがないとだめ
			if(!src_sd->skill_dance.id || pc_checkskill(src_sd,src_sd->skill_dance.id) <= 0) {
				clif_skill_fail(src_sd,skill_num,0,0,0);
				return 0;
			}
			src_sd->skill_used.id = skill_num;
			break;
		}
	}

	// コンディション確認
	{
		struct skill_condition cnd;

		cnd.id     = skill_num;
		cnd.lv     = skill_lv;
		cnd.x      = 0;
		cnd.y      = 0;
		cnd.target = target_id;

		if(!skill_check_condition2(src, &cnd, 0)) return 0;

		skill_num = cnd.id;
		skill_lv  = cnd.lv;
		target_id = cnd.target;
	}

	/* 射程と障害物チェック */
	range = skill_get_fixed_range(src,skill_num,skill_lv);
	if(!battle_check_range(src,target,range + 1))
		return 0;

	switch(skill_num) {
		case MO_CHAINCOMBO:
		case MO_COMBOFINISH:
		case CH_TIGERFIST:
		case CH_CHAINCRUSH:
		case TK_STORMKICK:
		case TK_DOWNKICK:
		case TK_TURNKICK:
		case TK_COUNTER:
		case GC_WEAPONCRUSH:
		case SR_FALLENEMPIRE:
			break;
		case MO_EXTREMITYFIST:
		case TK_JUMPKICK:
			if(src_sd && !src_sd->state.skill_flag)
				break;
			// fall through
		default:
			unit_stopattack(src);
			break;
	}

	src_ud->state.skillcastcancel = castcancel;

	/* 何か特殊な処理が必要 */
	// 失敗判定はskill_check_condition() に書くこと
	switch(skill_num)
	{
	case ALL_RESURRECTION:	/* リザレクション */
		if( !target_sd && battle_check_undead(status_get_race(target),status_get_elem_type(target)) ) {	/* 敵がアンデッドなら */
			forcecast = 1;	/* ターンアンデットと同じ詠唱時間 */
			casttime  = skill_castfix(src, skill_num, skill_get_cast(PR_TURNUNDEAD,skill_lv), skill_get_fixedcast(PR_TURNUNDEAD,skill_lv));
		}
		break;
	case MO_FINGEROFFENSIVE:	/* 指弾 */
		if(src_sd)
			casttime += casttime * ((skill_lv > src_sd->spiritball.num)? src_sd->spiritball.num: skill_lv);
		break;
	case MO_EXTREMITYFIST:	/* 阿修羅覇鳳拳 */
		if(sc && sc->data[SC_COMBO].timer != -1 && (sc->data[SC_COMBO].val1 == MO_COMBOFINISH || sc->data[SC_COMBO].val1 == CH_CHAINCRUSH)) {
			casttime = 0;
		}
		forcecast = 1;
		break;
	case SA_MAGICROD:
	case SA_SPELLBREAKER:
		forcecast = 1;
		break;
	case HP_BASILICA:
		if(sc && sc->data[SC_BASILICA].timer != -1)
			casttime = 0;
		break;
	case PF_MEMORIZE:
	case GD_REGENERATION:	/* 激励 */
	case GD_RESTORE:	/* 治療 */
		nomemorize = 1;
		break;
	case KN_CHARGEATK:	/* チャージアタック */
		{
			int dist = path_distance(src->x,src->y,target->x,target->y);
			if(dist >= 4 && dist <= 6)
				casttime = casttime * 2;
			else if(dist > 6)
				casttime = casttime * 3;
		}
		break;
	case TK_RUN:		/* 駆け足（タイリギ）*/
		if(sc && sc->data[SC_RUN].timer != -1)
			casttime = 0;
		break;
	case GD_EMERGENCYCALL:	/* 緊急召集 */
		if(src_sd && pc_checkskill(src_sd,TK_HIGHJUMP) > 0) {
			casttime <<= 1;
		}
		nomemorize = 1;
		break;
	case ST_CHASEWALK:	/* チェイスウォーク */
		if(sc && sc->data[SC_CHASEWALK].timer != -1)
			casttime = 0;
		break;
	case SR_TIGERCANNON:	/* 號砲 */
	case SR_GATEOFHELL:		/* 羅刹破凰撃 */
		if(sc && sc->data[SC_COMBO].timer != -1 && sc->data[SC_COMBO].val1 == SR_FALLENEMPIRE) {
			casttime = 0;
		}
		forcecast = 1;
		break;
	}

	// メモライズ状態ならキャストタイムが1/2
	if(sc && sc->data[SC_MEMORIZE].timer != -1 && casttime > 0 && !nomemorize) {
		casttime = casttime/2;
		if((--sc->data[SC_MEMORIZE].val2) <= 0)
			status_change_end(src, SC_MEMORIZE, -1);
	}

	if(battle_config.pc_skill_log)
		printf("PC %d skill use target_id=%d skill=%d lv=%d cast=%d\n",src->id,target_id,skill_num,skill_lv,casttime);

	tick = gettick();
	clif_skillcasting(src, src->id, target_id, 0, 0, skill_num,casttime);

#ifndef PRE_RENEWAL
	forcecast = 1;		// 詠唱反応用
#endif

	if( casttime > 0 || forcecast ) { /* 詠唱が必要 */
		/* 詠唱反応モンスター */
		if(src_sd && target_md && status_get_mode(&target_md->bl)&MD_CASTSENSOR && target_md->ud.attacktimer == -1 && src_sd->invincible_timer == -1) {
			target_md->target_id = src->id;
			target_md->min_chase = 13;
			if(target_md->state.angry)
				target_md->state.angry = 0;
		}
		/* 反撃などのMOBスキル判定 */
		if(target_md) {
			int id = target_md->target_id;
			if(battle_config.mob_changetarget_byskill || id == 0)
			{
				if(src->type & (BL_PC | BL_HOM | BL_MERC | BL_ELEM))
					target_md->target_id = src->id;
			}
			mobskill_use(target_md,tick,MSC_CASTTARGETED);
			target_md->target_id = id;
		}
	}

	if( casttime <= 0 )	/* 詠唱の無いものはキャンセルされない */
		src_ud->state.skillcastcancel = 0;

	src_ud->canact_tick  = tick + casttime + skill_delayfix(src, skill_num, skill_lv);
	src_ud->canmove_tick = tick;
	src_ud->skilltarget  = target_id;
	src_ud->skillx       = 0;
	src_ud->skilly       = 0;
	src_ud->skillid      = skill_num;
	src_ud->skilllv      = skill_lv;

	if( (src_sd && !(battle_config.pc_cloak_check_type&2)) ||
	    (src_md && !(battle_config.monster_cloak_check_type&2)) )
	{
		if(sc && sc->data[SC_CLOAKING].timer != -1 && skill_num != AS_CLOAKING)
			status_change_end(src,SC_CLOAKING,-1);
	}

	if(sc && sc->data[SC_CLOAKINGEXCEED].timer != -1 && skill_num != GC_CLOAKINGEXCEED) {
		status_change_end(src,SC_CLOAKINGEXCEED,-1);
	}

	if(sc && sc->data[SC__INVISIBILITY].timer != -1 && skill_num != SC_INVISIBILITY) {
		status_change_end(src,SC__INVISIBILITY,-1);
	}

	if(sc && sc->data[SC_SPELLFIST].timer != -1 && skill_num) {
		status_change_end(src, SC_SPELLFIST,-1);
	}

	if(casttime > 0) {
		int speed_rate = 0;
		src_ud->skilltimer = add_timer(tick+casttime, skill_castend_id, src->id, NULL);
		if(src_sd) {
			int lv;
			if((lv = pc_checkskill(src_sd,SA_FREECAST)) > 0) {
				speed_rate = 175 - 5 * lv;
			} else if(skill_num == LG_EXEEDBREAK) {
				speed_rate = 160 - 10 * skill_lv;
			}
		}
		if(src_sd && speed_rate > 0) {
			src_sd->prev_speed = src_sd->speed;
			src_sd->speed = src_sd->speed * speed_rate / 100;
			clif_updatestatus(src_sd,SP_SPEED);
		} else {
			unit_stop_walking(src,1);
		}
	} else {
		if(skill_num != SA_CASTCANCEL && skill_num != SO_SPELLFIST)
			src_ud->skilltimer = -1;
		skill_castend_id(src_ud->skilltimer,tick,src->id,NULL);
	}
	return 1;
}

/*==========================================
 * スキル使用（場所指定）
 *------------------------------------------
 */
int unit_skilluse_pos(struct block_list *src, int skill_x, int skill_y, int skill_num, int skill_lv)
{
	int id = skill_get_skilldb_id(skill_num);

	if( id == 0 )
		return 0;
	if( skill_lv <= 0 || skill_lv > MAX_SKILL_LEVEL )
		return 0;

	return unit_skilluse_pos2(
		src, skill_x, skill_y, skill_num, skill_lv,
		skill_castfix(src, skill_num, skill_db[id].cast[skill_lv-1], skill_db[id].fixedcast[skill_lv-1]),
		skill_db[id].castcancel
	);
}

int unit_skilluse_pos2( struct block_list *src, int skill_x, int skill_y, int skill_num, int skill_lv, int casttime, int castcancel)
{
	struct map_session_data *src_sd  = NULL;
	struct pet_data         *src_pd  = NULL;
	struct mob_data         *src_md  = NULL;
	struct homun_data       *src_hd  = NULL;
	struct merc_data        *src_mcd = NULL;
	struct elem_data        *src_eld = NULL;
	struct unit_data        *src_ud  = NULL;
	int zone;
	unsigned int tick = gettick();
	struct status_change *sc;

	nullpo_retr(0, src);

	if(!src->prev) return 0; // map 上に存在するか

	if( (src_sd = BL_DOWNCAST( BL_PC,  src ) ) ) {
		src_ud = &src_sd->ud;
	} else if( (src_md = BL_DOWNCAST( BL_MOB, src ) ) ) {
		src_ud = &src_md->ud;
	} else if( (src_pd = BL_DOWNCAST( BL_PET, src ) ) ) {
		src_ud = &src_pd->ud;
	} else if( (src_hd = BL_DOWNCAST( BL_HOM, src ) ) ) {
		src_ud = &src_hd->ud;
	} else if( (src_mcd = BL_DOWNCAST( BL_MERC, src ) ) ) {
		src_ud = &src_mcd->ud;
	} else if( (src_eld = BL_DOWNCAST( BL_ELEM, src ) ) ) {
		src_ud = &src_eld->ud;
	}
	if( src_ud == NULL ) return 0;

	if(unit_isdead(src)) return 0;

	sc = status_get_sc(src);

	// 虚無の影中はスキル使用に失敗することがある(確率暫定)
	if(sc && sc->data[SC_KYOMU].timer != -1) {
		if(atn_rand()%100 < 10) {
			if(src_sd)
				clif_skill_fail(src_sd,skill_num,0,0,0);
		}
	}

	// スキル制限
	zone = skill_get_zone(skill_num);
	if(zone) {
		int m = src->m;
		int ban = 0;
		if(map[m].flag.turbo && zone&16)
			ban = 1;
		else if(map[m].flag.normal && zone&1)
			ban = 1;
		else if(map[m].flag.pvp && zone&2)
			ban = 1;
		else if(map[m].flag.gvg && zone&4)
			ban = 1;
		else if(map[m].flag.pk && zone&8)
			ban = 1;
		if(ban) {
			if(src_sd) {
				if(skill_num == AL_TELEPORT)
					clif_skill_teleportmessage(src_sd,0);
				else
					clif_skill_fail(src_sd,skill_num,0,0,0);
			}
			return 0;
		}
	}

	// チェイスウォークだと設置系失敗
	if(src_sd && pc_ischasewalk(src_sd))
	 	return 0;

	// コンディション確認
	{
		struct skill_condition cnd;

		cnd.id     = skill_num;
		cnd.lv     = skill_lv;
		cnd.x      = skill_x;
		cnd.y      = skill_y;
		cnd.target = 0;

		if(!skill_check_condition2(src, &cnd ,0)) return 0;

		skill_num = cnd.id;
		skill_lv  = cnd.lv;
		skill_x   = cnd.x;
		skill_y   = cnd.y;
	}

	/* 射程と障害物チェック */
	{
		struct block_list bl;
		int range;

		memset(&bl, 0, sizeof(bl));
		bl.type = BL_NUL;
		bl.m = src->m;
		bl.x = skill_x;
		bl.y = skill_y;

		range = skill_get_fixed_range(src,skill_num,skill_lv);
		if(!battle_check_range(src,&bl,range+1))
			return 0;
	}

	if(!map_getcell(src->m,skill_x,skill_y,CELL_CHKPASS))
		return 0;

	unit_stopattack(src);

	src_ud->state.skillcastcancel = castcancel;

	if(battle_config.pc_skill_log)
		printf("PC %d skill use target_pos=(%d,%d) skill=%d lv=%d cast=%d\n",src->id,skill_x,skill_y,skill_num,skill_lv,casttime);

	// メモライズ状態ならキャストタイムが1/2
	if(sc && sc->data[SC_MEMORIZE].timer != -1 && casttime > 0) {
		casttime = casttime/2;
		if((--sc->data[SC_MEMORIZE].val2) <= 0)
			status_change_end(src, SC_MEMORIZE, -1);
	}

	if( casttime > 0 ) {
		/* 詠唱が必要 */
		unit_stop_walking( src, 1 );		// 歩行停止
		clif_skillcasting( src, src->id, 0, skill_x,skill_y, skill_num,casttime );
	}

	if( casttime <= 0 )	/* 詠唱の無いものはキャンセルされない */
		src_ud->state.skillcastcancel = 0;

	tick = gettick();
	src_ud->canact_tick  = tick + casttime + skill_delayfix(src, skill_num, skill_lv);
	src_ud->canmove_tick = tick;
	src_ud->skillid      = skill_num;
	src_ud->skilllv      = skill_lv;
	src_ud->skillx       = skill_x;
	src_ud->skilly       = skill_y;
	src_ud->skilltarget  = 0;

	if( (src_sd && !(battle_config.pc_cloak_check_type&2)) ||
	    (src_md && !(battle_config.monster_cloak_check_type&2)) )
	{
		if(sc && sc->data[SC_CLOAKING].timer != -1)
			status_change_end(src,SC_CLOAKING,-1);
	}

	if(sc && sc->data[SC_CLOAKINGEXCEED].timer != -1)
		status_change_end(src,SC_CLOAKINGEXCEED,-1);

	if(casttime > 0) {
		int skill;
		src_ud->skilltimer = add_timer(tick+casttime, skill_castend_pos, src->id, NULL);
		if(src_sd && (skill = pc_checkskill(src_sd,SA_FREECAST)) > 0) {
			src_sd->prev_speed = src_sd->speed;
			src_sd->speed = src_sd->speed * (175 - 5 * skill) / 100;
			clif_updatestatus(src_sd,SP_SPEED);
		} else {
			unit_stop_walking(src,1);
		}
	} else {
		src_ud->skilltimer = -1;
		skill_castend_pos(src_ud->skilltimer,tick,src->id,NULL);
	}
	return 1;
}

/*==========================================
 * 攻撃停止
 *------------------------------------------
 */
void unit_stopattack(struct block_list *bl)
{
	struct unit_data *ud = NULL;

	nullpo_retv(bl);

	ud = unit_bl2ud(bl);
	if(!ud || ud->attacktimer == -1) {
		return;
	}
	delete_timer(ud->attacktimer, unit_attack_timer);
	ud->attacktimer = -1;
	if(bl->type == BL_MOB) {
		mob_unlocktarget( (struct mob_data*)bl, gettick());
	}

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
static int unit_unattackable(struct block_list *bl)
{
	if(bl && bl->type == BL_MOB) {
		mob_unlocktarget((struct mob_data*)bl, gettick());
	}
	return 0;
}

/*==========================================
 * 攻撃要求
 * typeが1なら継続攻撃
 *------------------------------------------
 */
int unit_attack(struct block_list *src,int target_id,int type)
{
	struct block_list *target;
	struct unit_data  *src_ud;
	int d;
	unsigned int tick;

	nullpo_retr(0, src);
	nullpo_retr(0, src_ud = unit_bl2ud(src));

	target = map_id2bl(target_id);
	if(target == NULL || battle_check_target(src,target,BCT_ENEMY) <= 0) {
		unit_unattackable(src);
		return 1;
	}
	unit_stopattack(src);
	src_ud->attacktarget          = target_id;
	src_ud->state.attack_continue = type;

	tick = gettick();
	d = DIFF_TICK(src_ud->attackabletime,tick);
	if(d > 0) {
		// 攻撃delay中
		src_ud->attacktimer = add_timer(src_ud->attackabletime,unit_attack_timer,src->id,NULL);
	} else {
		// 本来timer関数なので引数を合わせる
		unit_attack_timer(-1,tick,src->id,NULL);
	}

	return 0;
}

/*==========================================
 * 指定位置に到達可能かどうか
 *------------------------------------------
 */
int unit_can_reach(struct block_list *bl,int x,int y)
{
	nullpo_retr(0, bl);

	if( bl->x == x && bl->y == y )	// 同じマス
		return 1;

	// 障害物判定
	return (path_search(NULL,bl->m,bl->x,bl->y,x,y,0) != -1);
}

/*==========================================
 * 移動可能な状態かどうか
 *------------------------------------------
 */
int unit_can_move(struct block_list *bl)
{
	struct map_session_data *sd = NULL;
	struct unit_data *ud = NULL;
	struct status_change *sc = NULL;

	nullpo_retr(0, bl);

	ud = unit_bl2ud(bl);
	if( ud == NULL )
		return 0;

	if( DIFF_TICK(ud->canmove_tick, gettick()) > 0 )
		return 0;

	sc = status_get_sc(bl);

	if( sc && sc->opt1 > OPT1_NORMAL && sc->opt1 != OPT1_STONECURSE_ING && sc->opt1 != OPT1_BURNNING )
		return 0;

	if( bl->type == BL_PC )
		sd = (struct map_session_data *)bl;
	if( sc && sc->option&OPTION_HIDE && (!sd || pc_checkskill(sd,RG_TUNNELDRIVE) <= 0) )
		return 0;

	if( ud->skilltimer != -1 &&
		(!sc || sc->data[SC_SELFDESTRUCTION].timer == -1) &&
		(ud->skillid != LG_EXEEDBREAK) &&
		(!sd || (pc_checkskill(sd,SA_FREECAST) <= 0) ||
		(ud->skillid >= GD_BATTLEORDER && ud->skillid <= GD_EMERGENCYCALL)) )
		return 0;

	if(sc && sc->count > 0)
	{
		if( sc->data[SC_ANKLE].timer != -1 ||		// アンクルスネア
		    sc->data[SC_AUTOCOUNTER].timer != -1 ||	// オートカウンター
		    sc->data[SC_DEATHBOUND].timer != -1 ||	// デスバウンド
		    sc->data[SC_TRICKDEAD].timer != -1 ||	// 死んだふり
		    sc->data[SC_BLADESTOP_WAIT].timer != -1 ||		// 白刃取り
		    sc->data[SC_BLADESTOP].timer != -1 ||	// 白刃取り
		    sc->data[SC_SPIDERWEB].timer != -1 ||	// スパイダーウェッブ
		    sc->data[SC_TIGERFIST].timer != -1 ||	// 伏虎拳
		    sc->data[SC_STOP].timer != -1 ||		// ホールドウェブ
		    sc->data[SC_MADNESSCANCEL].timer != -1 ||	// マッドネスキャンセラー
		    sc->data[SC_CLOSECONFINE].timer != -1 ||	// クローズコンファイン
		    (sc->data[SC_GRAVITATION_USER].timer != -1 && battle_config.player_gravitation_type < 2) ||	//グラビテーションフィールド使用者
		    (battle_config.hermode_no_walking && sc->data[SC_DANCING].timer != -1 && sc->data[SC_DANCING].val1 == CG_HERMODE) ||
		    (sc->data[SC_FEAR].timer != -1 && sc->data[SC_FEAR].val3 > 0) ||	// 恐怖状態（2秒間）
		    sc->data[SC_WEAPONBLOCKING2].timer != -1 ||	// ウェポンブロッキング（ブロック中）
		    sc->data[SC_ELECTRICSHOCKER].timer != -1 ||	// エレクトリックショッカー
		    sc->data[SC_WUGBITE].timer != -1 ||		// ウォーグバイト
		    (sc->data[SC_CAMOUFLAGE].timer != -1 && sc->data[SC_CAMOUFLAGE].val1 < 3) ||	// カモフラージュ（Lv3未満）
		    sc->data[SC_MAGNETICFIELD].timer != -1 ||		// マグネティックフィールド
		    sc->data[SC__MANHOLE].timer != -1 ||	// マンホール
		    sc->data[SC_SITDOWN_FORCE].timer != -1 ||	// 転倒
		    sc->data[SC_KINGS_GRACE].timer != -1 ||	// キングスグレイス
		    sc->data[SC_FALLENEMPIRE].timer != -1 ||	// 大纏崩捶
		    sc->data[SC_CURSEDCIRCLE_USER].timer != -1 ||	// 呪縛陣(使用者)
		    sc->data[SC_CURSEDCIRCLE].timer != -1 ||	// 呪縛陣
		    sc->data[SC_NETHERWORLD].timer != -1 ||	// 地獄の歌
		    sc->data[SC_DEEP_SLEEP].timer != -1 ||	// 安らぎの子守唄
		    sc->data[SC_DIAMONDDUST].timer != -1 ||	// ダイヤモンドダスト
		    sc->data[SC_VACUUM_EXTREME].timer != -1 ||	// バキュームエクストリーム
		    sc->data[SC_THORNS_TRAP].timer != -1 ||	// ソーントラップ
		    sc->data[SC_BANANA_BOMB].timer != -1 ||	// バナナ爆弾
			sc->data[SC__ESCAPE].timer != -1 ||		// エスケープ
			sc->data[SC_MEIKYOUSISUI].timer != -1 ||	// 明鏡止水
			sc->data[SC_KG_KAGEHUMI].timer != -1 ||	// 影踏み
			sc->data[SC_SUHIDE].timer != -1	||	// かくれる
			sc->data[SC_SV_ROOTTWIST].timer != -1	// マタタビの根っこ
		)
			return 0;

		if(sc->data[SC_LONGINGFREEDOM].timer == -1 && sc->data[SC_DANCING].timer != -1)
		{
			struct skill_unit_group *sg = NULL;

			// 合奏スキル演奏中
			if(sc->data[SC_DANCING].val4)
				return 0;
			// 単独合奏時に動けない設定
			sg = map_id2sg(sc->data[SC_DANCING].val2);
			if(sg && skill_get_unit_flag(sg->skill_id, sg->skill_lv) & UF_ENSEMBLE) {
				if(!sd || (!battle_config.player_skill_partner_check && !(battle_config.sole_concert_type & 1)))
					return 0;
			}
		}

		if((sc->data[SC_BASILICA].timer != -1 && sc->data[SC_BASILICA].val2 == bl->id) ||
		   (sc->data[SC_GOSPEL].timer != -1 && sc->data[SC_GOSPEL].val2 == bl->id))
			return 0;		// バジリカもしくはゴスペルを張っている人は動けない
	}
	return 1;
}

/*==========================================
 * 強制的な移動中かどうか
 *------------------------------------------
 */
int unit_isrunning(struct block_list *bl)
{
	struct status_change *sc = NULL;

	nullpo_retr(0, bl);

	sc = status_get_sc(bl);
	if(sc) {
		if( sc->data[SC_RUN].timer != -1 ||		// 駆け足
		    sc->data[SC_WUGDASH].timer != -1 ||	// ウォーグダッシュ
		    sc->data[SC_FORCEWALKING].timer != -1 ||	// 強制移動
		    sc->data[SC_SELFDESTRUCTION].timer != -1 )	// 自爆2
			return 1;
	}
	return 0;
}

/*==========================================
 * 攻撃 (timer関数)
 *------------------------------------------
 */
static int unit_attack_timer_sub(int tid,unsigned int tick,int id,void *data)
{
	struct block_list *src, *target;
	struct status_change *sc, *tsc;
	int dist,range;
	struct unit_data *src_ud;
	struct map_session_data *src_sd  = NULL, *target_sd  = NULL;
	struct pet_data         *src_pd  = NULL;
	struct mob_data         *src_md  = NULL;
	struct homun_data       *src_hd  = NULL;
	struct merc_data        *src_mcd = NULL;
	struct elem_data        *src_eld = NULL;

	if((src = map_id2bl(id)) == NULL)
		return 0;
	if((src_ud = unit_bl2ud(src)) == NULL)
		return 0;

	if(src_ud->attacktimer != tid) {
		if(battle_config.error_log)
			printf("unit_attack_timer %d != %d\n",src_ud->attacktimer,tid);
		return 0;
	}
	src_ud->attacktimer = -1;
	target = map_id2bl(src_ud->attacktarget);

	if(src->prev == NULL)
		return 0;
	if(target == NULL || target->prev == NULL)
		return 0;
	if(src->m != target->m || unit_isdead(src) || unit_isdead(target))	// ターゲットと同じMAPでないか死んでるなら攻撃しない
		return 0;

	sc  = status_get_sc( src    );
	tsc = status_get_sc( target );

	if( sc ) {
		if(sc->data[SC_AUTOCOUNTER].timer != -1 ||
		   sc->data[SC_DEATHBOUND].timer != -1 ||
		   sc->data[SC_TRICKDEAD].timer != -1 ||
		   sc->data[SC_BLADESTOP].timer != -1 ||
		   sc->data[SC_FULLBUSTER].timer != -1 ||
		   sc->data[SC_KEEPING].timer != -1 ||
		   sc->data[SC_WHITEIMPRISON].timer != -1 ||
		   sc->data[SC_KINGS_GRACE].timer != -1 ||
		   sc->data[SC__SHADOWFORM].timer != -1 ||
		   sc->data[SC__MANHOLE].timer != -1 ||
		   sc->data[SC_CURSEDCIRCLE_USER].timer != -1 ||
		   sc->data[SC_CURSEDCIRCLE].timer != -1 ||
		   sc->data[SC_DEEP_SLEEP].timer != -1 ||
		   sc->data[SC_DIAMONDDUST].timer != -1 ||
		   sc->data[SC_SUHIDE].timer != -1)
			return 0;
	}
	if( tsc ) {
		if(tsc->data[SC_TRICKDEAD].timer != -1 ||
		   tsc->data[SC_KINGS_GRACE].timer != -1 ||
		   tsc->data[SC__MANHOLE].timer != -1)
			return 0;
	}

	src_sd  = BL_DOWNCAST( BL_PC ,  src );
	src_pd  = BL_DOWNCAST( BL_PET,  src );
	src_md  = BL_DOWNCAST( BL_MOB,  src );
	src_hd  = BL_DOWNCAST( BL_HOM,  src );
	src_mcd = BL_DOWNCAST( BL_MERC, src );
	src_eld = BL_DOWNCAST( BL_ELEM, src );

	target_sd  = BL_DOWNCAST( BL_PC, target );

	if( src_sd ) {
		// 異常などで攻撃できない
		if( (src_sd->sc.opt1 > OPT1_NORMAL && src_sd->sc.opt1 != OPT1_BURNNING) || src_sd->sc.option&OPTION_HIDE || pc_ischasewalk(src_sd) )
			return 0;
		// 昆虫・悪魔状態でないならハイド中の敵に攻撃できない
		if( tsc && tsc->option&(OPTION_HIDE | OPTION_CLOAKING | OPTION_SPECIALHIDING) && src_sd->race != RCT_INSECT && src_sd->race != RCT_DEMON )
			return 0;
	}

	if( src_md ) {
		int mode, race;
		if(src_md->sc.opt1 > OPT1_NORMAL && src_md->sc.opt1 != OPT1_BURNNING)
			return 0;
		if(src_md->sc.data[SC_WINKCHARM].timer != -1 && src_md->sc.data[SC_WINKCHARM].val2 == target->id)
			return 0;
		if(src_md->sc.data[SC_SIREN].timer != -1 && src_md->sc.data[SC_SIREN].val2 == target->id)
			return 0;

		mode = status_get_mode(src);
		race = status_get_race(src);

		if( !(mode&MD_CANATTACK) )
			return 0;
		if( !(mode&MD_BOSS) ) {
			if( tsc && tsc->data[SC_FORCEWALKING].timer != -1 || tsc->data[SC_STEALTHFIELD].timer != -1 || tsc->data[SC_SUHIDE].timer != -1)
					return 0;
			if( target_sd ) {
				if( pc_ishiding(target_sd) && race != RCT_INSECT && race != RCT_DEMON )
					return 0;
				if( target_sd->state.gangsterparadise )
					return 0;
			}
		}
	}

	if( target_sd ) {
		if( target_sd->invincible_timer != -1 )
			return 0;
		if( pc_isinvisible(target_sd) )
			return 0;
	}

	if(src_ud->skilltimer != -1 && (!src_sd || pc_checkskill(src_sd,SA_FREECAST) <= 0))
		return 0;

	if(!battle_config.sdelay_attack_enable && (!src_sd || pc_checkskill(src_sd,SA_FREECAST) <= 0)) {
		if(DIFF_TICK(tick , src_ud->canact_tick) < 0) {
			if(src_sd)
				clif_skill_fail(src_sd,1,4,0,0);
			return 0;
		}
	}

	dist  = path_distance(src->x,src->y,target->x,target->y);
	range = status_get_range(src);
	if( src_md && status_get_mode(src) & MD_CANMOVE )
		range++;
	if(src_sd && (src_sd->status.weapon != WT_BOW && !(src_sd->status.weapon >= WT_HANDGUN && src_sd->status.weapon <= WT_GRENADE)))
		range++;

	if( dist > range ) {	// 届かないので移動
		if(!unit_can_reach(src,target->x,target->y))
			return 0;
		if(src_sd)
			clif_movetoattack(src_sd,target);
		return 1;
	}
	if(dist <= range && !battle_check_range(src,target,range)) {
		if(unit_can_reach(src,target->x,target->y))
			unit_walktoxy(src,target->x,target->y);
		src_ud->attackabletime = tick + status_get_adelay(src);
	} else {
		// 向き設定
		int dir = path_calc_dir(src, target->x,target->y);
		if(src_sd && battle_config.pc_attack_direction_change)
			pc_setdir(src_sd, dir, dir);
		else if(src_pd && battle_config.monster_attack_direction_change)
			src_pd->dir = dir;
		else if(src_md && battle_config.monster_attack_direction_change)
			src_md->dir = dir;
		else if(src_hd && battle_config.monster_attack_direction_change)
			src_hd->dir = dir;
		else if(src_mcd && battle_config.monster_attack_direction_change)
			src_mcd->dir = dir;
		else if(src_eld && battle_config.monster_attack_direction_change)
			src_eld->dir = dir;
		else if(src_ud->walktimer != -1)
			unit_stop_walking(src,1);

		if( src_md && mobskill_use(src_md,tick,-2) ) {	// スキル使用
			return 1;
		}
		if(src_eld && atn_rand()%10000 < battle_config.elem_attackskill_rate) {	// 精霊のスキル使用
			elem_skilluse(src_eld,target,ELMODE_OFFENSIVE);
			return 1;
		}

		if(!sc || (sc->data[SC_COMBO].timer == -1 && sc->data[SC_TKCOMBO].timer == -1)) {
			map_freeblock_lock();
			unit_stop_walking(src,1);

			src_ud->attacktarget_lv = battle_weapon_attack(src,target,tick,0);

			if(src_md && !(battle_config.monster_cloak_check_type&2) && sc && sc->data[SC_CLOAKING].timer != -1)
				status_change_end(src,SC_CLOAKING,-1);
			if(src_sd && !(battle_config.pc_cloak_check_type&2) && sc && sc->data[SC_CLOAKING].timer != -1)
				status_change_end(src,SC_CLOAKING,-1);
			if(sc && sc->data[SC_CLOAKINGEXCEED].timer != -1)
				status_change_end(src,SC_CLOAKINGEXCEED,-1);
			if(sc && sc->data[SC_CAMOUFLAGE].timer != -1)
				status_change_end(src,SC_CAMOUFLAGE,-1);
			if(src_sd && src_sd->status.pet_id > 0 && src_sd->pd && src_sd->petDB)
				pet_target_check(src_sd,target,0);
			map_freeblock_unlock();
			src_ud->attackabletime = tick + status_get_adelay(src);
		}
		else if(src_ud->attackabletime <= tick) {
			src_ud->attackabletime = tick + status_get_adelay(src);
		}
		if(src_ud->attackabletime <= tick)
			src_ud->attackabletime = tick + (battle_config.max_aspd<<1);
	}

	if(src_ud->state.attack_continue) {
		src_ud->attacktimer = add_timer(src_ud->attackabletime,unit_attack_timer,src->id,NULL);
	}
	return 1;
}

static int unit_attack_timer(int tid,unsigned int tick,int id,void *data)
{
	if(unit_attack_timer_sub(tid, tick, id, data) == 0) {
		unit_unattackable( map_id2bl(id) );
	}
	return 0;
}

/*==========================================
 * スキル詠唱キャンセル
 *   type= 0: 詠唱の強制中止
 *   type=+1: キャストキャンセル用
 *   type=+2: 詠唱の妨害
 *------------------------------------------
 */
int unit_skillcastcancel(struct block_list *bl,int type)
{
	int skillid;
	int ret=0;
	struct map_session_data *sd = NULL;
	struct mob_data         *md = NULL;
	struct unit_data        *ud = NULL;
	struct status_change    *sc = NULL;
	unsigned int tick = gettick();

	nullpo_retr(0, bl);

	if( (ud = unit_bl2ud(bl)) == NULL || ud->skilltimer == -1 )
		return 0;

	sd = BL_DOWNCAST( BL_PC,  bl );
	md = BL_DOWNCAST( BL_MOB, bl );

	if(type&2) {	// キャンセル可能な状態か判定
		if(!ud->state.skillcastcancel)
			return 0;
		if(sd) {
			if(sd->special_state.no_castcancel && !map[bl->m].flag.gvg)
				return 0;
			if(sd->special_state.no_castcancel2)
				return 0;
			if(sd->sc.data[SC_UNLIMITED_HUMMING_VOICE].timer != -1 && !map[bl->m].flag.gvg)
				return 0;
		}
	}

	ud->canact_tick  = tick;
	ud->canmove_tick = tick;

	skillid = (type&1 && sd)? sd->skill_used.id: ud->skillid;

	if(sd && (pc_checkskill(sd,SA_FREECAST) > 0 || skillid == LG_EXEEDBREAK)) {
		sd->speed = sd->prev_speed;
		clif_updatestatus(sd,SP_SPEED);
	}


	if(skill_get_inf(skillid) & INF_GROUND)
		ret = delete_timer(ud->skilltimer, skill_castend_pos);
	else
		ret = delete_timer(ud->skilltimer, skill_castend_id);
	if(ret < 0)
		printf("delete timer error : skillid : %d\n", skillid);

	if(md) {
		md->skillidx = -1;
	}

	ud->skilltimer = -1;
	clif_skillcastcancel(bl);

	sc = status_get_sc(bl);
	if(sc && sc->data[SC_SELFDESTRUCTION].timer != -1)
		status_change_end(bl,SC_SELFDESTRUCTION,-1);

	return 1;
}

/*==========================================
 * unit_data の初期化処理
 *------------------------------------------
 */
int unit_dataset(struct block_list *bl)
{
	struct unit_data *ud;
	unsigned int tick = gettick();

	nullpo_retr(0, ud = unit_bl2ud(bl));

	memset(ud, 0, sizeof(struct unit_data));
	ud->bl             = bl;
	ud->walktimer      = -1;
	ud->skilltimer     = -1;
	ud->attacktimer    = -1;
	ud->attackabletime = tick;
	ud->canact_tick    = tick;
	ud->canmove_tick   = tick;

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int unit_heal(struct block_list *bl,int hp,int sp)
{
	nullpo_retr(0, bl);

	if(bl->type == BL_PC)
		pc_heal((struct map_session_data*)bl,hp,sp);
	else if(bl->type == BL_MOB)
		mob_heal((struct mob_data*)bl,hp);
	else if(bl->type == BL_HOM)
		homun_heal((struct homun_data*)bl,hp,sp);
	else if(bl->type == BL_MERC)
		merc_heal((struct merc_data*)bl,hp,sp);
	else if(bl->type == BL_ELEM)
		elem_heal((struct elem_data*)bl,hp,sp);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int unit_fixdamage(struct block_list *src,struct block_list *target,unsigned int tick,int sdelay,int ddelay,int damage,int div_,int type,int damage2,int is_spdamage)
{
	nullpo_retr(0, target);

	if(damage + damage2 <= 0)
		return 0;
	// タゲ
	if(target->type == BL_MOB) {
		mob_attacktarget((struct mob_data*)target,src,0);
	}
	clif_damage(target,target,tick,sdelay,ddelay,damage,div_,type,damage2,0);
	battle_damage(src,target,damage + damage2,0,0,0);
	return 0;
}

/*==========================================
 * 自分をロックしているユニットの数を数える(foreachclient)
 *------------------------------------------
 */
static int unit_counttargeted_sub(struct block_list *bl, va_list ap)
{
	int id, target_lv;

	nullpo_retr(0, bl);

	id        = va_arg(ap,int);
	target_lv = va_arg(ap,int);

	if(bl->id == id) {
		// 自分
		return 0;
	}

	if(bl->type == BL_PC) {
		struct map_session_data *sd = (struct map_session_data *)bl;
		if( sd && sd->ud.attacktarget == id && sd->ud.attacktimer != -1 && sd->ud.attacktarget_lv >= target_lv ) {
			return 1;
		}
	} else if(bl->type == BL_MOB) {
		struct mob_data *md = (struct mob_data *)bl;
		if( md && md->target_id == id && md->ud.attacktimer != -1 && md->ud.attacktarget_lv >= target_lv ) {
			return 1;
		}
	} else if(bl->type == BL_PET) {
		struct pet_data *pd = (struct pet_data *)bl;
		if( pd && pd->target_id == id && pd->ud.attacktimer != -1 && pd->ud.attacktarget_lv >= target_lv ) {
			return 1;
		}
	} else if(bl->type == BL_HOM) {
		struct homun_data *hd = (struct homun_data *)bl;
		if( hd && hd->target_id == id && hd->ud.attacktimer != -1 && hd->ud.attacktarget_lv >= target_lv ) {
			return 1;
		}
	} else if(bl->type == BL_MERC) {
		struct merc_data *mcd = (struct merc_data *)bl;
		if( mcd && mcd->target_id == id && mcd->ud.attacktimer != -1 && mcd->ud.attacktarget_lv >= target_lv ) {
			return 1;
		}
	} else if(bl->type == BL_ELEM) {
		struct elem_data *eld = (struct elem_data *)bl;
		if( eld && eld->target_id == id && eld->ud.attacktimer != -1 && eld->ud.attacktarget_lv >= target_lv ) {
			return 1;
		}
	}
	return 0;
}

/*==========================================
 * 自分をロックしている対象の数を返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int unit_counttargeted(struct block_list *bl,int target_lv)
{
	nullpo_retr(0, bl);

	return map_foreachinarea(unit_counttargeted_sub, bl->m,
		bl->x-AREA_SIZE,bl->y-AREA_SIZE,
		bl->x+AREA_SIZE,bl->y+AREA_SIZE,(BL_CHAR|BL_PET),bl->id,target_lv
	);
}

/*==========================================
 * 死亡しているかどうか
 *------------------------------------------
 */
int unit_isdead(struct block_list *bl)
{
	nullpo_retr(1, bl);

	if(bl->type == BL_PC) {
		struct map_session_data *sd = (struct map_session_data*)bl;
		return (sd->state.dead_sit == 1);
	} else if(bl->type == BL_MOB) {
		struct mob_data *md = (struct mob_data *)bl;
		return md->hp <= 0;
	} else if(bl->type == BL_PET) {
		return 0;
	} else if(bl->type == BL_HOM) {
		struct homun_data *hd = (struct homun_data *)bl;
		return hd->status.hp <= 0;
	} else if(bl->type == BL_MERC) {
		struct merc_data *mcd = (struct merc_data *)bl;
		return mcd->status.hp <= 0;
	} else if(bl->type == BL_ELEM) {
		struct elem_data *eld = (struct elem_data *)bl;
		return eld->status.hp <= 0;
	}
	return 0;
}

/*==========================================
 * idを攻撃しているPCの攻撃を停止
 * clif_foreachclientのcallback関数
 *------------------------------------------
 */
int unit_mobstopattacked(struct map_session_data *sd,va_list ap)
{
	int id;

	nullpo_retr(0, sd);
	nullpo_retr(0, ap);

	id = va_arg(ap,int);

	if(sd->ud.attacktarget == id)
		unit_stopattack(&sd->bl);
	return 0;
}

/*==========================================
 * 見た目のサイズを変更する
 *------------------------------------------
 */
int unit_changeviewsize(struct block_list *bl,int size)
{
	nullpo_retr(0, bl);

	size = (size < 0)? -1: (size > 0)? 1: 0;

	if(bl->type == BL_PC) {
		struct map_session_data *sd = (struct map_session_data*)bl;
		sd->view_size = size;
	} else if(bl->type == BL_MOB) {
		struct mob_data *md = (struct mob_data *)bl;
		md->view_size = size;
	} else if(bl->type == BL_PET) {
		struct pet_data *pd = (struct pet_data *)bl;
		pd->view_size = size;
	} else if(bl->type == BL_HOM) {
		struct homun_data *hd = (struct homun_data *)bl;
		hd->view_size = size;
	} else if(bl->type == BL_MERC) {
		struct merc_data *mcd = (struct merc_data *)bl;
		mcd->view_size = size;
	} else if(bl->type == BL_ELEM) {
		struct elem_data *eld = (struct elem_data *)bl;
		eld->view_size = size;
	} else if(bl->type == BL_NPC) {
		struct npc_data *nd = (struct npc_data *)bl;
		nd->view_size = size;
	} else {
		return 0;
	}
	if(size != 0)
		clif_misceffect2(bl,421+size);
	return 0;
}

/*==========================================
 * スキル詠唱中かどうかを返す
 *------------------------------------------
 */
int unit_iscasting(struct block_list *bl)
{
	struct unit_data *ud = unit_bl2ud(bl);

	if( ud == NULL )
		return 0;

	return (ud->skilltimer != -1);
}

/*==========================================
 * 歩行中かどうかを返す
 *------------------------------------------
 */
int unit_iswalking(struct block_list *bl)
{
	struct unit_data *ud = unit_bl2ud(bl);

	if( ud == NULL )
		return 0;

	return (ud->walktimer != -1);
}

/*==========================================
 * マップから離脱する
 *------------------------------------------
 */
int unit_remove_map(struct block_list *bl, int clrtype, int flag)
{
	struct unit_data *ud;

	nullpo_retr(0, bl);
	nullpo_retr(0, ud = unit_bl2ud(bl));

	if(bl->prev == NULL)
		return 1;

	map_freeblock_lock();

	unit_stop_walking(bl,1);			// 歩行中断
	unit_stopattack(bl);				// 攻撃中断
	unit_skillcastcancel(bl,0);			// 詠唱中断
	skill_stop_dancing(bl,1);			// ダンス中断
	if(!flag)
		skill_clear_unitgroup(bl);		// スキルユニットグループの削除
	if(!unit_isdead(bl))
		skill_unit_move(bl,gettick(),0);	// スキルユニットから離脱

	// tickset 削除
	linkdb_final( &ud->skilltickset );
	status_clearpretimer( bl );
	skill_cleartimerskill( bl );			// タイマースキルクリア

	// MAPを離れるときの状態異常解除
	status_change_removemap_end(bl);

	if(bl->type == BL_PC) {
		struct map_session_data *sd = (struct map_session_data*)bl;
		// チャットから出る
		if(sd->chatID)
			chat_leavechat(sd,0);

		// 取引を中断する
		if(sd->trade.partner)
			trade_tradecancel(sd);

		// 露天を閉じる
		vending_closevending(sd);
		buyingstore_close(sd);

		// 倉庫を開いてるなら閉じて保存する
		if(sd->state.storage_flag == 2)
			storage_guild_storageclose(sd);
		else if(sd->state.storage_flag == 1)
			storage_storageclose(sd);

		// NPC商店情報を取り消し
		sd->npc_shopid = 0;

		// 友達リスト勧誘を拒否する
		if(sd->friend_invite > 0)
			friend_add_reply(sd,sd->friend_invite,sd->friend_invite_char,0);

		// パーティ勧誘を拒否する
		if(sd->party_invite > 0)
			party_reply_invite(sd,sd->party_invite_account,0);

		// ギルド勧誘を拒否する
		if(sd->guild_invite > 0)
			guild_reply_invite(sd,sd->guild_invite,0);

		// ギルド同盟勧誘を拒否する
		if(sd->guild_alliance > 0)
			guild_reply_reqalliance(sd,sd->guild_alliance_account,0);

		// 養子要請を拒否する
		if(sd->adopt_invite > 0)
			pc_adopt_reply(sd,0,0,0);

		// メール添付情報を破棄
		mail_removeitem(sd,0);

		// スキルメニューを取り消し
		if(sd->skill_menu.id > 0)
			memset(&sd->skill_menu,0,sizeof(sd->skill_menu));

		// アイテムスキルを取り消し
		if(sd->skill_item.id >= 0) {
			sd->skill_item.id   = -1;
			sd->skill_item.lv   = -1;
			sd->skill_item.flag = 0;
		}

		pc_delinvincibletimer(sd,0);		// 無敵タイマー削除

		// PVP タイマー削除
		if(sd->pvp_timer != -1) {
			delete_timer(sd->pvp_timer,pc_calc_pvprank_timer);
			sd->pvp_timer = -1;
		}

		skill_sit(sd,0);			// ギャングスターパラダイスおよびテコン休息削除

		clif_clearchar_area(&sd->bl,clrtype&0xffff);
		mob_ai_hard_spawn( &sd->bl, 0 );
		map_delblock(&sd->bl);
	} else if(bl->type == BL_MOB) {
		struct mob_data *md = (struct mob_data*)bl;

		linkdb_final( &md->dmglog );
		//mobskill_deltimer(md);
		md->state.skillstate = MSS_DEAD;
		// 死んだのでこのmobへの攻撃者全員の攻撃を止める
		clif_foreachclient(unit_mobstopattacked,md->bl.id);
		status_change_clear(&md->bl,2);	// ステータス異常を解除する
		if(md->deletetimer != -1) {
			delete_timer(md->deletetimer,mob_timer_delete);
			md->deletetimer = -1;
		}
		md->hp               = 0;
		md->target_id        = 0;
		md->attacked_id      = 0;
		md->attacked_players = 0;

		clif_clearchar_area(&md->bl,clrtype);
		if(mob_is_pcview(md->class_)) {
			if(battle_config.pcview_mob_clear_type == 2)
				clif_clearchar(&md->bl,0);
			else
				clif_clearchar_delay(gettick()+3000,&md->bl);
		}
		mob_ai_hard_spawn( &md->bl, 0 );
		if(!battle_config.monster_damage_delay || battle_config.monster_damage_delay_rate == 0)
			mob_deleteslave(md);

		if( md->ai_pc_count != 0 || md->ai_prev != NULL || md->ai_next != NULL ) {
			printf("unit_remove_map: ai error\n");
			mob_ai_hard_del( md );
			md->ai_pc_count = 0;
		}
		map_delblock(&md->bl);
#ifdef DYNAMIC_SC_DATA
		if(md->sc.data != NULL)
			status_free_sc_data(&md->sc);
#endif
		if(md->lootitem) {
			int i;
			for(i=0; i<md->lootitem_count; i++) {
				if(md->lootitem[i].card[0] == (short)0xff00)
					intif_delete_petdata(*((int *)(&md->lootitem[i].card[1])));
			}
			md->lootitem_count = 0;
		}

		// 復活しないMOBの処理
		if(md->spawndelay1 == -1 && md->spawndelay2 == -1 && md->n == 0) {
			map_deliddb(&md->bl);
			if(md->lootitem) {
				aFree(md->lootitem);
				md->lootitem = NULL;
			}
			map_freeblock(md);	// freeのかわり
		} else {
			unsigned int spawntime;
			unsigned int tick = gettick();
			spawntime = tick + 1000;
			md->last_spawntime = tick + md->spawndelay1;
			if(md->spawndelay2 > 0) {
				md->last_spawntime += atn_rand()%md->spawndelay2;
			}
			if(DIFF_TICK(spawntime,md->last_spawntime) > 0) {
				md->last_spawntime = spawntime;
			}
			add_timer(md->last_spawntime,mob_delayspawn,bl->id,NULL);
		}
	} else if(bl->type == BL_PET) {
		struct pet_data *pd = (struct pet_data*)bl;

		clif_clearchar_area(&pd->bl,0);
		map_delblock(&pd->bl);
	} else if(bl->type == BL_HOM) {
		struct homun_data *hd = (struct homun_data*)bl;

		if(battle_config.homun_skilldelay_reset) {
			unsigned int tick = gettick();
			int i;
			for(i = 0; i < MAX_HOMSKILL; i++) {
				hd->skillstatictimer[i] = tick;
			}
		}
		clif_clearchar_area(&hd->bl,clrtype);
		mob_ai_hard_spawn( &hd->bl, 0 );
		map_delblock(&hd->bl);
	} else if(bl->type == BL_MERC) {
		struct merc_data *mcd = (struct merc_data*)bl;

		clif_clearchar_area(&mcd->bl,clrtype);
		mob_ai_hard_spawn( &mcd->bl, 0 );
		map_delblock(&mcd->bl);
	} else if(bl->type == BL_ELEM) {
		struct elem_data *eld = (struct elem_data*)bl;

		clif_clearchar_area(&eld->bl,clrtype);
		mob_ai_hard_spawn( &eld->bl, 0 );
		map_delblock(&eld->bl);
	}
	map_freeblock_unlock();
	return 0;
}

/*==========================================
 * マップから離脱後、領域を解放する
 *------------------------------------------
 */
int unit_free(struct block_list *bl, int clrtype)
{
	struct unit_data *ud = unit_bl2ud( bl );

	nullpo_retr(0, ud);

	map_freeblock_lock();
	if( bl->prev )
		unit_remove_map(bl, clrtype, 0);

	if( bl->type == BL_PC ) {
		struct map_session_data *sd = (struct map_session_data*)bl;

		if(unit_isdead(&sd->bl))
			pc_setrestartvalue(sd,2);

		if(sd->sc.data[SC_BERSERK].timer != -1) // バーサーク中の終了はHPを100に
			sd->status.hp = 100;

		// OnPCLogoutイベント
		if(battle_config.pc_logout_script)
			npc_event_doall_id("OnPCLogout",sd->bl.id,sd->bl.m);

		// メモリアルダンジョンに居る場合はユーザー数削除
		if(map[sd->bl.m].memorial_id)
			memorial_delusers(map[sd->bl.m].memorial_id);

		friend_send_online( sd, 1 );			// 友達リストのログアウトメッセージ送信
		party_send_logout(sd);					// パーティのログアウトメッセージ送信
		guild_send_memberinfoshort(sd,0);		// ギルドのログアウトメッセージ送信
		intif_save_scdata(sd);				// ステータス異常データの保存
		intif_save_quest(sd);				// クエストリストデータの保存
		status_change_clear(&sd->bl,1);			// ステータス異常を解除する
		pc_cleareventtimer(sd);					// イベントタイマを破棄する
		pc_delspiritball(sd,sd->spiritball.num,1);	// 気功削除
		pc_delcoin(sd,sd->coin.num,1);				// コイン削除
		pc_delelementball(sd,sd->elementball.num,1);	// 影狼・朧の球体削除
		booking_delete(sd);
		//storage_storage_save(sd);
		storage_delete(sd->status.account_id);
		pc_clearitemlimit(sd);
		pc_makesavestatus(sd);
	} else if( bl->type == BL_PET ) {
		struct pet_data *pd = (struct pet_data*)bl;
		struct map_session_data *sd = pd->msd;
		if(sd && sd->status.pet_id > 0 && sd->pd) {
			if(sd->pet.intimate <= 0) {
				intif_delete_petdata(sd->status.pet_id);
				sd->status.pet_id = 0;
				sd->pd = NULL;
				sd->petDB = NULL;
				if(battle_config.pet_status_support)
					status_calc_pc(sd,2);
			} else {
				intif_save_petdata(sd->status.account_id,&sd->pet);
				sd->pd = NULL;
			}
		}
		if(pd->a_skill) {
			aFree(pd->a_skill);
			pd->a_skill = NULL;
		}
		if(pd->s_skill) {
			if(pd->s_skill->timer != -1)
				delete_timer(pd->s_skill->timer, pet_skill_support_timer);
			aFree(pd->s_skill);
			pd->s_skill = NULL;
		}
		pet_hungry_timer_delete(pd);
		map_deliddb(&pd->bl);
		pet_lootitem_free(pd);
		pd->lootitem = NULL;
		map_freeblock(pd);
	} else if( bl->type == BL_HOM ) {
		struct homun_data *hd = (struct homun_data*)bl;
		struct map_session_data *sd = hd->msd;

		status_change_clear(&hd->bl,1);			// ステータス異常を解除する
		if(sd && sd->hd) {
			homun_hungry_timer_delete(sd->hd);
			//sd->hd->status.incubate = 0;
			homun_save_data(sd);
			if(sd->hd->natural_heal_hp != -1 || sd->hd->natural_heal_sp != -1)
				homun_natural_heal_timer_delete(sd->hd);
			sd->hd = NULL;
		}
		map_deliddb(&hd->bl);
#ifdef DYNAMIC_SC_DATA
		status_free_sc_data(&hd->sc);
#endif
		map_freeblock(hd);
	} else if( bl->type == BL_MERC ) {
		struct merc_data *mcd = (struct merc_data*)bl;
		struct map_session_data *sd = mcd->msd;

		if(mcd->sc.data[SC_BERSERK].timer != -1) // バーサーク中の終了はHPを100に
			mcd->status.hp = 100;

		status_change_clear(&mcd->bl,1);			// ステータス異常を解除する
		if(sd && sd->mcd) {
			merc_employ_timer_delete(sd->mcd);
			merc_save_data(sd);
			if(sd->mcd->natural_heal_hp != -1 || sd->mcd->natural_heal_sp != -1)
				merc_natural_heal_timer_delete(sd->mcd);
			sd->mcd = NULL;
		}
		map_deliddb(&mcd->bl);
#ifdef DYNAMIC_SC_DATA
		status_free_sc_data(&mcd->sc);
#endif
		map_freeblock(mcd);
	} else if( bl->type == BL_ELEM ) {
		struct elem_data *eld = (struct elem_data*)bl;
		struct map_session_data *sd = eld->msd;

		status_change_clear(&eld->bl,1);			// ステータス異常を解除する
		if(sd && sd->eld) {
			elem_summon_timer_delete(sd->eld);
			elem_save_data(sd);
			if(sd->eld->natural_heal_hp != -1 || sd->eld->natural_heal_sp != -1)
				elem_natural_heal_timer_delete(sd->eld);
			sd->eld = NULL;
		}
		map_deliddb(&eld->bl);
#ifdef DYNAMIC_SC_DATA
		status_free_sc_data(&eld->sc);
#endif
		map_freeblock(eld);
	}
	map_freeblock_unlock();

	return 0;
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
int do_init_unit(void)
{
	add_timer_func_list(unit_attack_timer);
	add_timer_func_list(unit_walktoxy_timer);
	return 0;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
int do_final_unit(void)
{
	// nothing to do
	return 0;
}
