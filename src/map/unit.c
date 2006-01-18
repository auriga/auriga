#include <stdio.h>
#include <stdlib.h>

#include "db.h"
#include "timer.h"
#include "nullpo.h"
#include "malloc.h"
#include "utils.h"

#include "map.h"
#include "pc.h"
#include "mob.h"
#include "pet.h"
#include "homun.h"
#include "skill.h"
#include "unit.h"
#include "battle.h"
#include "status.h"
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

/*==========================================
 * 二点間の距離を返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int unit_distance(int x0,int y0,int x1,int y1)
{
	int dx,dy;

	dx=abs(x0-x1);
	dy=abs(y0-y1);
	return dx>dy ? dx : dy;
}

int unit_distance2( struct block_list *bl, struct block_list *bl2)
{
	nullpo_retr(0, bl);
	nullpo_retr(0, bl2);

	return unit_distance(bl->x,bl->y,bl2->x,bl2->y);
}

struct unit_data* unit_bl2ud(struct block_list *bl) {
	if( bl == NULL) return NULL;
	if( bl->type == BL_PC)  return &((struct map_session_data*)bl)->ud;
	if( bl->type == BL_MOB) return &((struct mob_data*)bl)->ud;
	if( bl->type == BL_PET) return &((struct pet_data*)bl)->ud;
	if( bl->type == BL_HOM) return &((struct homun_data*)bl)->ud;
	return NULL;
}

static int unit_walktoxy_timer(int tid,unsigned int tick,int id,int data);

int unit_walktoxy_sub(struct block_list *bl)
{
	int i;
	struct walkpath_data wpd;
	struct map_session_data *sd = NULL;
	struct pet_data         *pd = NULL;
	struct mob_data         *md = NULL;
	struct homun_data       *hd = NULL;
	struct unit_data        *ud = NULL;
	struct status_change    *sc_data = NULL;

	nullpo_retr(1, bl);

	if( (sd = BL_DOWNCAST( BL_PC,  bl ) ) ) {
		ud = &sd->ud;
	} else if( (md = BL_DOWNCAST( BL_MOB, bl ) ) ) {
		ud = &md->ud;
	} else if( (pd = BL_DOWNCAST( BL_PET, bl ) ) ) {
		ud = &pd->ud;
	} else if( (hd = BL_DOWNCAST( BL_HOM, bl ) ) ) {
		ud = &hd->ud;
	}
	if(ud == NULL) return 1;

	if(sd && pc_iscloaking(sd))// クローキング時再計算
		status_calc_pc(sd,0);

	sc_data = status_get_sc_data(bl);
	if(sc_data && sc_data[SC_FORCEWALKING].timer!=-1) {
		if(path_search2(&wpd,bl->m,bl->x,bl->y,ud->to_x,ud->to_y,0))
			return 1;
	} else {
		if(path_search(&wpd,bl->m,bl->x,bl->y,ud->to_x,ud->to_y,0))
			return 1;
	}

	if(md) {
		int x = md->bl.x+dirx[wpd.path[0]];
		int y = md->bl.y+diry[wpd.path[0]];
		if (map_getcell(bl->m,x,y,CELL_CHKBASILICA) && !(status_get_mode(bl)&0x20)) {
			ud->state.change_walk_target=0;
			return 1;
		}
	}

	memcpy(&ud->walkpath,&wpd,sizeof(wpd));

	if(sd) {
		clif_walkok(sd);
	} else if(md) {
		clif_movemob(md);
	} else if(pd) {
		clif_movepet(pd);
	} else if(hd) {
		clif_movehom(hd);
	}

	ud->state.change_walk_target=0;

	if(ud->walkpath.path_pos>=ud->walkpath.path_len)
		i = -1;
	else if(ud->walkpath.path[ud->walkpath.path_pos]&1)
		i = status_get_speed(bl)*14/10;
	else
		i = status_get_speed(bl);
	if(i>0) {
		i = i>>1;
		ud->walktimer = add_timer(gettick()+i,unit_walktoxy_timer,bl->id,0);
	}
	if(sd) {
		clif_movechar(sd);
	}

	return 0;
}


static int unit_walktoxy_timer(int tid,unsigned int tick,int id,int data)
{
	int i;
	int moveblock;
	int x,y,dx,dy,dir;
	struct block_list       *bl = NULL;
	struct map_session_data *sd = NULL;
	struct pet_data         *pd = NULL;
	struct mob_data         *md = NULL;
	struct homun_data       *hd = NULL;
	struct unit_data        *ud = NULL;
	struct status_change    *sc_data = NULL;

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
	}
	if(ud == NULL) return 0;

	if(ud->walktimer != tid){
		if(battle_config.error_log)
			printf("unit_walk_timer %d != %d\n",ud->walktimer,tid);
		return 0;
	}
	ud->walktimer=-1;
	if( bl->prev == NULL ) return 0; // block_list から抜けているので移動停止する

	if(ud->walkpath.path_pos>=ud->walkpath.path_len || ud->walkpath.path_pos!=data)
		return 0;

	//歩いたので息吹のタイマーを初期化
	if(sd) {
		sd->inchealspirithptick = 0;
		sd->inchealspiritsptick = 0;
		sd->warp_waiting		= 0;
	}

	sc_data = status_get_sc_data(bl);
	ud->walkpath.path_half ^= 1;

	if(ud->walkpath.path_half==0){ // マス目中心へ到着
		if( (md || pd) && ud->walkpath.path[ud->walkpath.path_pos]>=8)
			return 1;
		x = bl->x;
		y = bl->y;

		dir = ud->walkpath.path[ud->walkpath.path_pos];
		if(sd) pc_setdir(sd, dir, dir);
		if(md) md->dir = dir;
		if(pd) pd->dir = dir;
		if(hd) hd->dir = dir;

		dx = dirx[(int)dir];
		dy = diry[(int)dir];

		// 障害物に当たった
		if(sd && sd->sc_data[SC_RUN].timer != -1) {
			if(map_getcell(sd->bl.m,x+dx,y+dy,CELL_CHKNOPASS) ||
			   map_getcell(sd->bl.m,x   ,y+dy,CELL_CHKNOPASS) ||
			   map_getcell(sd->bl.m,x+dx,y   ,CELL_CHKNOPASS) ||
			   map_count_oncell(sd->bl.m,x+dx,y+dy,BL_PC|BL_MOB|BL_NPC) > 0) {
				skill_blown(&sd->bl,&sd->bl,skill_get_blewcount(TK_RUN,sd->sc_data[SC_RUN].val1)|SAB_NODAMAGE);
				status_change_end(&sd->bl,SC_RUN,-1);
				clif_status_change(&sd->bl,SI_RUN_STOP,1);
				pc_setdir(sd, dir, dir);
				return 0;
			}
		} else if(map_getcell(bl->m,x+dx,y+dy,CELL_CHKNOPASS)) {
			if(!sc_data || sc_data[SC_FORCEWALKING].timer==-1) {
				clif_fixwalkpos(bl);
				return 0;
			}
		}

		// バシリカ判定
		if(md && map_getcell(bl->m,x+dx,y+dy,CELL_CHKBASILICA) && !(status_get_mode(bl)&0x20)) {
			clif_fixwalkpos(bl);
			return 0;
		}

		moveblock = ( x/BLOCK_SIZE != (x+dx)/BLOCK_SIZE || y/BLOCK_SIZE != (y+dy)/BLOCK_SIZE);

		ud->walktimer = 1;
		if(sd) {
			map_foreachinmovearea(clif_pcoutsight,bl->m,x-AREA_SIZE,y-AREA_SIZE,x+AREA_SIZE,y+AREA_SIZE,dx,dy,0,sd);
			map_foreachinmovearea(mob_ai_hard_spawn_sub,bl->m,x-AREA_SIZE*2,y-AREA_SIZE*2,x+AREA_SIZE*2,y+AREA_SIZE*2,dx,dy,BL_MOB,sd,0);
		} else if(md) {
			map_foreachinmovearea(clif_moboutsight,bl->m,x-AREA_SIZE,y-AREA_SIZE,x+AREA_SIZE,y+AREA_SIZE,dx,dy,BL_PC,md);
			map_foreachinmovearea(mob_ai_hard_spawn_sub,bl->m,x-AREA_SIZE*2,y-AREA_SIZE*2,x+AREA_SIZE*2,y+AREA_SIZE*2,dx,dy,BL_PC|BL_HOM,md,0);
		} else if(pd) {
			map_foreachinmovearea(clif_petoutsight,bl->m,x-AREA_SIZE,y-AREA_SIZE,x+AREA_SIZE,y+AREA_SIZE,dx,dy,BL_PC,pd);
		} else if(hd) {
			map_foreachinmovearea(clif_homoutsight,bl->m,x-AREA_SIZE,y-AREA_SIZE,x+AREA_SIZE,y+AREA_SIZE,dx,dy,BL_PC,hd);
			map_foreachinmovearea(mob_ai_hard_spawn_sub,bl->m,x-AREA_SIZE*2,y-AREA_SIZE*2,x+AREA_SIZE*2,y+AREA_SIZE*2,dx,dy,BL_MOB,hd,0);
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

		if(sd && sd->sc_data[SC_DANCING].timer != -1 && sd->sc_data[SC_LONGINGFREEDOM].timer == -1) // Not 拘束しないで
		{
			skill_unit_move_unit_group((struct skill_unit_group *)sd->sc_data[SC_DANCING].val2,sd->bl.m,dx,dy);
			sd->dance.x += dx;
			sd->dance.y += dy;
		}

		ud->walktimer = 1;
		if(sd) {
			map_foreachinmovearea(clif_pcinsight,bl->m,x-AREA_SIZE,y-AREA_SIZE,x+AREA_SIZE,y+AREA_SIZE,-dx,-dy,0,sd);
			map_foreachinmovearea(mob_ai_hard_spawn_sub,bl->m,x-AREA_SIZE*2,y-AREA_SIZE*2,x+AREA_SIZE*2,y+AREA_SIZE*2,-dx,-dy,BL_MOB,sd,1);
		} else if(md) {
			map_foreachinmovearea(clif_mobinsight,bl->m,x-AREA_SIZE,y-AREA_SIZE,x+AREA_SIZE,y+AREA_SIZE,-dx,-dy,BL_PC,md);
			map_foreachinmovearea(mob_ai_hard_spawn_sub,bl->m,x-AREA_SIZE*2,y-AREA_SIZE*2,x+AREA_SIZE*2,y+AREA_SIZE*2,-dx,-dy,BL_PC|BL_HOM,md,1);
		} else if(pd) {
			map_foreachinmovearea(clif_petinsight,bl->m,x-AREA_SIZE,y-AREA_SIZE,x+AREA_SIZE,y+AREA_SIZE,-dx,-dy,BL_PC,pd);
		} else if(hd) {
			map_foreachinmovearea(clif_hominsight,bl->m,x-AREA_SIZE,y-AREA_SIZE,x+AREA_SIZE,y+AREA_SIZE,-dx,-dy,BL_PC,hd);
			map_foreachinmovearea(mob_ai_hard_spawn_sub,bl->m,x-AREA_SIZE*2,y-AREA_SIZE*2,x+AREA_SIZE*2,y+AREA_SIZE*2,-dx,-dy,BL_MOB,hd,1);
		}
		ud->walktimer = -1;

		if(md && md->option&4)
			skill_check_cloaking(bl);

		if(sd) {
			if(sd->status.party_id > 0 && party_search(sd->status.party_id) != NULL) {	// パーティのＨＰ情報通知検査
				int p_flag=0;
				map_foreachinmovearea(party_send_hp_check,sd->bl.m,x-AREA_SIZE,y-AREA_SIZE,x+AREA_SIZE,y+AREA_SIZE,-dx,-dy,BL_PC,sd->status.party_id,&p_flag);
				if(p_flag)
					sd->party_hp=-1;
			}
			if(pc_iscloaking(sd) && pc_checkskill(sd,AS_CLOAKING) < 3) {	// クローキングの消滅検査
				skill_check_cloaking(&sd->bl);
			}
			/* ディボーション検査 */
			for(i=0;i<5;i++)
				if(sd->dev.val1[i]){
					skill_devotion3(sd,sd->dev.val1[i]);
					break;
				}
			if(sd->sc_data)
			{
				/* 被ディボーション検査 */
				if(sd->sc_data[SC_DEVOTION].val1){
					skill_devotion2(&sd->bl,sd->sc_data[SC_DEVOTION].val1);
				}
				/* マリオネット検査 */
				if(sd->sc_data[SC_MARIONETTE].timer!=-1){
					skill_marionette(sd,sd->sc_data[SC_MARIONETTE].val2);
				}
				/* 被マリオネット検査 */
				if(sd->sc_data[SC_MARIONETTE2].timer!=-1){
					skill_marionette2(sd,sd->sc_data[SC_MARIONETTE2].val2);
				}
				//ダンスチェック
				if(sd->sc_data[SC_LONGINGFREEDOM].timer!=-1)
				{
					//範囲外に出たら止める
					if(unit_distance(sd->bl.x,sd->bl.y,sd->dance.x,sd->dance.y)>4)
					{
						skill_stop_dancing(&sd->bl,0);
					}
				}
				//ヘルモードチェック
				if(battle_config.hermode_wp_check &&
					sd->sc_data[SC_DANCING].timer !=-1 && sd->sc_data[SC_DANCING].val1 ==CG_HERMODE)
				{
					if(skill_hermode_wp_check(&sd->bl,battle_config.hermode_wp_check_range)==0)
						skill_stop_dancing(&sd->bl,0);
				}
			}
			//ギルドスキル有効
			pc_check_guild_skill_effective_range(sd);

			if(map_getcell(sd->bl.m,x,y,CELL_CHKNPC))
				npc_touch_areanpc(sd,sd->bl.m,x,y);
			else
				sd->areanpc_id=0;

			if(sd->sc_data[SC_RUN].timer != -1)	// タイリギ継続中なら歩数カウント
				sd->sc_data[SC_RUN].val4++;
		}

		ud->walkpath.path_pos++;
		if(ud->state.change_walk_target) {
			unit_walktoxy_sub(bl);
			return 0;
		}
	}/*
	 else { // マス目境界へ到着
		
	}
	*/

	if(ud->walkpath.path_pos>=ud->walkpath.path_len)
		i = -1;
	else if(ud->walkpath.path[ud->walkpath.path_pos]&1)
		i = status_get_speed(bl)*14/10;
	else
		i = status_get_speed(bl);

	if(i > 0) {
		i = i>>1;
//		if(i < 1 && ud->walkpath.path_half == 0)
//			i = 1;
		ud->walktimer = add_timer(tick+i,unit_walktoxy_timer,id,ud->walkpath.path_pos);
	} else {
		// 目的地に着いた
		if(sd && sd->sc_data[SC_RUN].timer!=-1){
			//継続判定
			pc_runtodir(sd);
		}
		if(sc_data && sc_data[SC_FORCEWALKING].timer != -1) {
			if(sc_data[SC_FORCEWALKING].val4==0) {
				sc_data[SC_FORCEWALKING].val4++;
				unit_walktodir(bl,1);
			}
			else if(sc_data[SC_FORCEWALKING].val4==1) {
				sc_data[SC_FORCEWALKING].val4++;
			}
		}
		if(md && sc_data && sc_data[SC_SELFDESTRUCTION].timer != -1) {
			md->dir = sc_data[SC_SELFDESTRUCTION].val4;
			unit_walktodir(bl,1);
		}

		// とまったときの位置の再送信は不要（カクカクするため）
		// clif_fixwalkpos(bl);
	}

	return 0;
}

int unit_walktoxy( struct block_list *bl, int x, int y) {
	struct unit_data        *ud = NULL;
	struct map_session_data *sd = NULL;
	struct pet_data         *pd = NULL;
	struct mob_data         *md = NULL;
	struct homun_data       *hd = NULL;

	nullpo_retr(0, bl);
	if( (sd = BL_DOWNCAST( BL_PC,  bl ) ) ) {
		ud = &sd->ud;
	} else if( (md = BL_DOWNCAST( BL_MOB, bl ) ) ) {
		ud = &md->ud;
	} else if( (pd = BL_DOWNCAST( BL_PET, bl ) ) ) {
		ud = &pd->ud;
	} else if( (hd = BL_DOWNCAST( BL_HOM, bl ) ) ) {
		ud = &hd->ud;
	}
	if( ud == NULL) return 0;

	// 移動出来ないユニットは弾く
	if( ! ( status_get_mode( bl ) & 1) ) return 0;

	if( !unit_can_move(bl) )
		return 0;

	//強制移動中は混乱から除外
	if(sd && sd->sc_data[SC_CONFUSION].timer!=-1 && sd->sc_data[SC_FORCEWALKING].timer==-1)
	{
		ud->to_x = sd->bl.x + atn_rand()%7 - 3;
		ud->to_y = sd->bl.y + atn_rand()%7 - 3;
	}else{
		ud->to_x = x;
		ud->to_y = y;
	}

	if(ud->walktimer != -1) {
		// 現在歩いている最中の目的地変更なのでマス目の中心に来た時に
		// timer関数からunit_walktoxy_subを呼ぶようにする
		ud->state.change_walk_target = 1;
		return 0;
	} else {
		return unit_walktoxy_sub(bl);
	}
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

	for(i=0;i<step;i++)
	{
		// 次のセルへ１歩で移動可能でないなら
		if(map_getcell(bl->m,to_x+dir_x,to_y+dir_y,CELL_CHKNOPASS) ||
		   map_getcell(bl->m,to_x      ,to_y+dir_y,CELL_CHKNOPASS) ||
		   map_getcell(bl->m,to_x+dir_x,to_y      ,CELL_CHKNOPASS))
			break;

		if(map_getcell(bl->m,to_x+dir_x,to_y+dir_y,CELL_CHKPASS))
		{
			to_x += dir_x;
			to_y += dir_y;
			continue;
		}
		break;
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
	struct status_change *sc_data = NULL;
	int i,to_x,to_y,dir_x,dir_y,d;

	nullpo_retr(0, bl);

	sc_data = status_get_sc_data(bl);
	d = status_get_dir(bl);

	to_x = bl->x;
	to_y = bl->y;
	dir_x = dirx[d];
	dir_y = diry[d];

	for(i=distance;i>1;i--)
	{
		if(map_getcell(bl->m,bl->x+dir_x*i,bl->y+dir_y*i,CELL_CHKPASS))
		{
			to_x = bl->x+dir_x*(i-1);
			to_y = bl->y+dir_y*(i-1);
			break;
		}
	}

	if(sc_data)
		sc_data[SC_FORCEWALKING].val4=0;
	unit_walktoxy(bl, to_x, to_y);

	return 1;
}

int unit_attack_timer(int tid,unsigned int tick,int id,int data);

/*==========================================
 * 位置移動
 *   flag -> 0xXY
 *	X : 経路検索方法、0,1,2
 *	Y : パケットの種類、0,1
 *------------------------------------------
 */
int unit_movepos(struct block_list *bl,int dst_x,int dst_y,int flag)
{
	int moveblock;
	int dx,dy,dir,x[4],y[4];
	unsigned int tick = gettick();
	struct map_session_data *sd = NULL;
	struct pet_data         *pd = NULL;
	struct mob_data         *md = NULL;
	struct homun_data       *hd = NULL;
	struct unit_data        *ud = NULL;
	struct walkpath_data wpd;

	nullpo_retr(0, bl);
	if( bl->prev == NULL ) return 1;
	if( (sd = BL_DOWNCAST( BL_PC,  bl ) ) ) {
		ud = &sd->ud;
	} else if( (md = BL_DOWNCAST( BL_MOB, bl ) ) ) {
		ud = &md->ud;
	} else if( (pd = BL_DOWNCAST( BL_PET, bl ) ) ) {
		ud = &pd->ud;
	} else if( (hd = BL_DOWNCAST( BL_HOM, bl ) ) ) {
		ud = &hd->ud;
	}
	if( ud == NULL ) return 1;

	unit_stop_walking(bl,1);

	if(ud->attacktimer != -1) {
		delete_timer( ud->attacktimer, unit_attack_timer );
		ud->attacktimer = -1;
	}

	switch ( (flag&0xf0)>>4 ) {
		case 0:
			if(path_search(&wpd,bl->m,bl->x,bl->y,dst_x,dst_y,0))
				return 1;
			break;
		case 1:
			if(path_search2(&wpd,bl->m,bl->x,bl->y,dst_x,dst_y,0))
				return 1;
			break;
		case 2:
			if(path_search3(&wpd,bl->m,bl->x,bl->y,dst_x,dst_y,0))
				return 1;
			break;
	}

	dir = map_calc_dir(bl, dst_x,dst_y);
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
		map_foreachinmovearea(clif_pcoutsight,bl->m,bl->x-AREA_SIZE,bl->y-AREA_SIZE,bl->x+AREA_SIZE,bl->y+AREA_SIZE,dx,dy,0,sd);
		map_foreachinmovearea(mob_ai_hard_spawn_sub,bl->m,bl->x-AREA_SIZE*2,bl->y-AREA_SIZE*2,bl->x+AREA_SIZE*2,bl->y+AREA_SIZE*2,dx,dy,BL_MOB,sd,0);
	} else if(md) {
		map_foreachinmovearea(clif_moboutsight,bl->m,bl->x-AREA_SIZE,bl->y-AREA_SIZE,bl->x+AREA_SIZE,bl->y+AREA_SIZE,dx,dy,BL_PC,md);
		map_foreachinmovearea(mob_ai_hard_spawn_sub,bl->m,bl->x-AREA_SIZE*2,bl->y-AREA_SIZE*2,bl->x+AREA_SIZE*2,bl->y+AREA_SIZE*2,dx,dy,BL_PC|BL_HOM,md,0);
	} else if(pd) {
		map_foreachinmovearea(clif_petoutsight,bl->m,bl->x-AREA_SIZE,bl->y-AREA_SIZE,bl->x+AREA_SIZE,bl->y+AREA_SIZE,dx,dy,BL_PC,pd);
	} else if(hd) {
		map_foreachinmovearea(clif_homoutsight,bl->m,bl->x-AREA_SIZE,bl->y-AREA_SIZE,bl->x+AREA_SIZE,bl->y+AREA_SIZE,dx,dy,BL_PC,hd);
		map_foreachinmovearea(mob_ai_hard_spawn_sub,bl->m,bl->x-AREA_SIZE*2,bl->y-AREA_SIZE*2,bl->x+AREA_SIZE*2,bl->y+AREA_SIZE*2,dx,dy,BL_MOB,hd,0);
	}

	if(!pd) skill_unit_move(bl,tick,0);
	if(moveblock) map_delblock(bl);
	bl->x = dst_x;
	bl->y = dst_y;
	if(moveblock) map_addblock(bl);
	if(!pd) skill_unit_move(bl,tick,1);

	if(sd) {	/* 画面内に入ってきたので表示 */
		map_foreachinmovearea(clif_pcinsight,bl->m,bl->x-AREA_SIZE,bl->y-AREA_SIZE,bl->x+AREA_SIZE,bl->y+AREA_SIZE,-dx,-dy,0,sd);
		map_foreachinmovearea(mob_ai_hard_spawn_sub,bl->m,bl->x-AREA_SIZE*2,bl->y-AREA_SIZE*2,bl->x+AREA_SIZE*2,bl->y+AREA_SIZE*2,-dx,-dy,BL_MOB,sd,1);
	} else if(md) {
		map_foreachinmovearea(clif_mobinsight,bl->m,bl->x-AREA_SIZE,bl->y-AREA_SIZE,bl->x+AREA_SIZE,bl->y+AREA_SIZE,-dx,-dy,BL_PC,md);
		map_foreachinmovearea(mob_ai_hard_spawn_sub,bl->m,bl->x-AREA_SIZE*2,bl->y-AREA_SIZE*2,bl->x+AREA_SIZE*2,bl->y+AREA_SIZE*2,-dx,-dy,BL_PC|BL_HOM,md,1);
	} else if(pd) {
		map_foreachinmovearea(clif_petinsight,bl->m,bl->x-AREA_SIZE,bl->y-AREA_SIZE,bl->x+AREA_SIZE,bl->y+AREA_SIZE,-dx,-dy,BL_PC,pd);
	} else if(hd) {
		map_foreachinmovearea(clif_hominsight,bl->m,bl->x-AREA_SIZE,bl->y-AREA_SIZE,bl->x+AREA_SIZE,bl->y+AREA_SIZE,-dx,-dy,BL_PC,hd);
		map_foreachinmovearea(mob_ai_hard_spawn_sub,bl->m,bl->x-AREA_SIZE*2,bl->y-AREA_SIZE*2,bl->x+AREA_SIZE*2,bl->y+AREA_SIZE*2,-dx,-dy,BL_MOB,hd,1);
	}

	if( flag&1 )		// 吹き飛ばし用パケット送信
		clif_blown(bl,dst_x,dst_y);
	else			// 位置変更情報送信
		clif_fixpos2(bl,x,y);

	if(sd && sd->status.party_id > 0 && party_search(sd->status.party_id) != NULL) {	// パーティのＨＰ情報通知検査
		map_foreachinmovearea(party_send_hp_check,sd->bl.m,sd->bl.x-AREA_SIZE,sd->bl.y-AREA_SIZE,sd->bl.x+AREA_SIZE,sd->bl.y+AREA_SIZE,-dx,-dy,BL_PC,sd->status.party_id,&flag);
		if(flag)
			sd->party_hp=-1;
	}

	if(sd && !(sd->status.option&0x4000) && sd->status.option&4)	// クローキングの消滅検査
	{
		if(pc_checkskill(sd,AS_CLOAKING) < 3)
			skill_check_cloaking(&sd->bl);
	}

	if(sd) {
		if(map_getcell(bl->m,bl->x,bl->y,CELL_CHKNPC))
			npc_touch_areanpc(sd,sd->bl.m,sd->bl.x,sd->bl.y);
		else
			sd->areanpc_id=0;
	}

	return 0;
}

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
	clif_changedir( bl, dir, dir );
	return 0;
}

int unit_getdir(struct block_list *bl)
{
	nullpo_retr( 0, bl );
	if(bl->type == BL_PC)
		return ((struct map_session_data *)bl)->dir;
	else if(bl->type == BL_MOB)
		return ((struct mob_data         *)bl)->dir;
	else if(bl->type == BL_PET)
		return ((struct pet_data         *)bl)->dir;
	else if(bl->type == BL_HOM)
		return ((struct homun_data       *)bl)->dir;
	return 0;
}

/*==========================================
 * 歩行停止
 *------------------------------------------
 */
int unit_stop_walking(struct block_list *bl,int type)
{
	struct map_session_data *sd = NULL;
	struct pet_data         *pd = NULL;
	struct mob_data         *md = NULL;
	struct homun_data       *hd = NULL;
	struct unit_data        *ud = NULL;
	nullpo_retr(0, bl);

	if( (sd = BL_DOWNCAST( BL_PC,  bl ) ) ) {
		ud = &sd->ud;
	} else if( (md = BL_DOWNCAST( BL_MOB, bl ) ) ) {
		ud = &md->ud;
	} else if( (pd = BL_DOWNCAST( BL_PET, bl ) ) ) {
		ud = &pd->ud;
	} else if( (hd = BL_DOWNCAST( BL_HOM, bl ) ) ) {
		ud = &hd->ud;
	}
	if( ud == NULL) return 0;

	ud->walkpath.path_len = 0;
	ud->walkpath.path_pos = 0;
	ud->to_x              = bl->x;
	ud->to_y              = bl->y;

	if(ud->walktimer == -1) return 0;

	delete_timer(ud->walktimer, unit_walktoxy_timer);
	ud->walktimer         = -1;
//	if(md) { md->state.skillstate = MSS_IDLE; }
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
		int dx=ud->to_x-md->bl.x;
		int dy=ud->to_y-md->bl.y;
		if(dx<0) dx=-1; else if(dx>0) dx=1;
		if(dy<0) dy=-1; else if(dy>0) dy=1;
		if(dx || dy) {
			unit_walktoxy( bl, md->bl.x+dx, md->bl.y+dy );
		}
	}

	return 0;
}

int unit_skilluse_id(struct block_list *src, int target_id, int skill_num, int skill_lv)
{
	int id = skill_get_skilldb_id(skill_num);

	if( id < 0 || id >= MAX_SKILL_DB+MAX_HOMSKILL_DB+MAX_GUILDSKILL_DB) {
		return 0;
	} else {
		return unit_skilluse_id2(
			src, target_id, skill_num, skill_lv,
			skill_castfix(src, skill_get_cast( skill_num, skill_lv) ) + skill_get_fixedcast(skill_num, skill_lv),
			skill_db[id].castcancel
		);
	}
}

int unit_skilluse_id2(struct block_list *src, int target_id, int skill_num, int skill_lv, int casttime, int castcancel) {
	struct map_session_data *src_sd = NULL;
	struct pet_data         *src_pd = NULL;
	struct mob_data         *src_md = NULL;
	struct homun_data       *src_hd = NULL;
	struct unit_data        *src_ud = NULL;
	unsigned int tick = gettick();
	int delay=0,range;
	struct block_list       *target;
	struct map_session_data *target_sd = NULL;
	struct mob_data         *target_md = NULL;
	struct homun_data       *target_hd = NULL;
//	struct unit_data        *target_ud = NULL;
	int forcecast = 0,zone = 0;
	struct status_change *sc_data;
	struct status_change *tsc_data;

	nullpo_retr(0, src);

	if( (target=map_id2bl(target_id)) == NULL ) return 0;
	if(src->m != target->m)                     return 0; // 同じマップかどうか
	if(!src->prev || !target->prev)             return 0; // map 上に存在するか

	if( (src_sd = BL_DOWNCAST( BL_PC,  src ) ) ) {
		src_ud = &src_sd->ud;
	} else if( (src_md = BL_DOWNCAST( BL_MOB, src ) ) ) {
		src_ud = &src_md->ud;
	} else if( (src_pd = BL_DOWNCAST( BL_PET, src ) ) ) {
		src_ud = &src_pd->ud;
	} else if( (src_hd = BL_DOWNCAST( BL_HOM, src ) ) ) {
		src_ud = &src_hd->ud;
	}
	if( src_ud == NULL) return 0;

	target_sd = BL_DOWNCAST( BL_PC,  target );
	target_md = BL_DOWNCAST( BL_MOB, target );
	target_hd = BL_DOWNCAST( BL_HOM, target );

	if(unit_isdead(src))		return 0; // 死んでいないか
	if(src_sd && src_sd->opt1>0 )   return 0; /* 沈黙や異常（ただし、グリムなどの判定をする） */

	//スキル制限
	zone = skill_get_zone(skill_num);
	if(zone){
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
		if(ban)
		{
			if(src_sd)
			{
				if(skill_num == AL_TELEPORT || skill_num == AL_WARP)
					clif_skill_teleportmessage(src_sd,0);
				else
					clif_skill_fail(src_sd,skill_num,0,0);
			}
			return 0;
		}
	}

	sc_data  = status_get_sc_data(src);
	tsc_data = status_get_sc_data(target);

	if(skill_get_inf2(skill_num)&0x200 && src->id == target_id)
		return 0;

	//直前のスキル状況の記録
	if(src_sd) {
		switch(skill_num){
		case SA_CASTCANCEL:
			if(src_ud->skillid != skill_num){ //キャストキャンセル自体は覚えない
				src_sd->skillid_old = src_ud->skillid;
				src_sd->skilllv_old = src_ud->skilllv;
				break;
			}
		case BD_ENCORE:					/* アンコール */
			 //前回使用した踊りがないとだめ
			if(!src_sd->skillid_dance || (src_sd->skillid_dance && pc_checkskill(src_sd,src_sd->skillid_dance)<=0)){
				clif_skill_fail(src_sd,skill_num,0,0);
				return 0;
			}else{
				src_sd->skillid_old = skill_num;
			}
			break;
		}
	}

	// コンディション確認
	{
		struct skill_condition sc;
		memset( &sc, 0, sizeof( struct skill_condition ) );

		sc.id     = skill_num;
		sc.lv     = skill_lv;
		sc.target = target_id;

		if(!skill_check_condition2(src, &sc, 0)) return 0;

		skill_num = sc.id;
		skill_lv  = sc.lv;
		target_id = sc.target;
	}

	/* 射程と障害物チェック */
	range = skill_get_range(skill_num,skill_lv);
	if(range < 0)
		range = status_get_range(src) - (range + 1);
	if (!battle_check_range(src,target,range + 1))
		return 0;

	switch (skill_num) {
		case MO_CHAINCOMBO:
		case MO_COMBOFINISH:
		case CH_TIGERFIST:
		case CH_CHAINCRUSH:
		case TK_STORMKICK:
		case TK_DOWNKICK:
		case TK_TURNKICK:
		case TK_COUNTER:
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

	if(skill_num != SA_MAGICROD)
		delay=skill_delayfix(src, skill_get_delay( skill_num,skill_lv), skill_get_cast( skill_num,skill_lv) );
	src_ud->state.skillcastcancel = castcancel;

	/* 何か特殊な処理が必要 */
	// 失敗判定はskill_check_condition() に書くこと
	switch(skill_num)
	{
	case ALL_RESURRECTION:	/* リザレクション */
		if( !target_sd && battle_check_undead(status_get_race(target),status_get_elem_type(target))){	/* 敵がアンデッドなら */
			forcecast=1;	/* ターンアンデットと同じ詠唱時間 */
			casttime=skill_castfix(src, skill_get_cast(PR_TURNUNDEAD,skill_lv) ) + skill_get_fixedcast(PR_TURNUNDEAD,skill_lv);
		}
		break;
	case MO_FINGEROFFENSIVE:	/* 指弾 */
		if(src_sd)
			casttime += casttime * ((skill_lv > src_sd->spiritball)? src_sd->spiritball:skill_lv);
		break;
	case MO_CHAINCOMBO:		/*連打掌*/
		if( !src_ud || !src_ud->attacktarget )
			return 0;
		target_id = src_ud->attacktarget;
		if( sc_data && sc_data[SC_BLADESTOP].timer!=-1 ){
			struct block_list *tbl = map_id2bl(sc_data[SC_BLADESTOP].val4);
			if(tbl == NULL) //ターゲットがいない？
				return 0;
			target_id = tbl->id;
		}
		break;
	case CR_SHIELDBOOMERANG:
		if(sc_data && sc_data[SC_CRUSADER].timer!=-1)
			delay = delay/2;
		break;
	case AS_SONICBLOW:
		if(sc_data && sc_data[SC_ASSASIN].timer!=-1 && map[src->m].flag.gvg==0)
			delay = delay/2;
		break;
	case TK_STORMKICK://旋風蹴り
	case TK_DOWNKICK://下段蹴り
	case TK_TURNKICK://回転蹴り
	case TK_COUNTER://カウンター蹴り
	case MO_COMBOFINISH:	/*猛龍拳*/
	case CH_TIGERFIST:		/* 伏虎拳 */
	case CH_CHAINCRUSH:		/* 連柱崩撃 */
		if( !src_ud || !src_ud->attacktarget )
			return 0;
		target_id = src_ud->attacktarget;
		break;
	case MO_EXTREMITYFIST:	/*阿修羅覇鳳拳*/
		if(! src_ud || !sc_data) return 0;
		if(sc_data[SC_COMBO].timer != -1 && (sc_data[SC_COMBO].val1 == MO_COMBOFINISH || sc_data[SC_COMBO].val1 == CH_CHAINCRUSH)) {
			casttime = 0;
			target_id = src_ud->attacktarget;
		}
		forcecast=1;
		break;
	case SA_MAGICROD:
	case SA_SPELLBREAKER:
		forcecast=1;
		break;
	case WE_MALE:
	case WE_FEMALE:
		{
			struct map_session_data *p_sd = NULL;
			if(!src_sd) return 0;
			if((p_sd = pc_get_partner(src_sd)) == NULL)
				return 0;
			target_id = p_sd->bl.id;
			//rangeをもう1回検査
			range = skill_get_range(skill_num,skill_lv);
			if(range < 0)
				range = status_get_range(src) - (range + 1);
			if( !battle_check_range(src,&p_sd->bl,range) )
				return 0;
		}
		break;
	case SA_ABRACADABRA:
		delay=skill_get_delay(SA_ABRACADABRA,skill_lv);
		break;
	case HP_BASILICA:
		if(sc_data && sc_data[SC_BASILICA].timer != -1)
			casttime = 0;
		break;
	case KN_CHARGEATK:			//チャージアタック
		{
			int dist = unit_distance(src->x,src->y,target->x,target->y);
			if(dist >= 4 && dist <= 6)
				casttime = casttime * 2;
			else if(dist > 6)
				casttime = casttime * 3;
		}
		break;
	case TK_RUN:		// 駆け足（タイリギ）
		if(sc_data && sc_data[SC_RUN].timer != -1)
			casttime = 0;
		break;
	case TK_JUMPKICK:	// 飛び蹴り（ティオアプチャギ）
		if(sc_data && sc_data[SC_DODGE_DELAY].timer != -1 && src->id == target->id)
			target_id = sc_data[SC_DODGE_DELAY].val2;
		break;
	case GD_EMERGENCYCALL:	// 緊急召集
		if(src_sd && pc_checkskill(src_sd,TK_HIGHJUMP) > 0)
			casttime <<= 1;
		break;
	}

	//メモライズ状態ならキャストタイムが1/2
	if(sc_data && sc_data[SC_MEMORIZE].timer != -1 && casttime > 0){
		casttime = casttime/2;
		if((--sc_data[SC_MEMORIZE].val2)<=0)
			status_change_end(src, SC_MEMORIZE, -1);
	}

	if(battle_config.pc_skill_log)
		printf("PC %d skill use target_id=%d skill=%d lv=%d cast=%d\n",src->id,target_id,skill_num,skill_lv,casttime);

	if( casttime>0 || forcecast ){ /* 詠唱が必要 */
		clif_skillcasting( src, src->id, target_id, 0,0, skill_num,casttime);

		/* 詠唱反応モンスター */
		if(src_sd && target_md && status_get_mode(&target_md->bl)&0x10 && target_md->ud.attacktimer == -1 && src_sd->invincible_timer == -1) {
			target_md->target_id=src->id;
			target_md->min_chase=13;
		}
		/* 反撃などのMOBスキル判定 */
		if(target_md) {
			int id = target_md->target_id;
			if(battle_config.mob_changetarget_byskill || id == 0)
			{
				if(src->type == BL_PC || src->type == BL_HOM)
					target_md->target_id = src->id;
			}
			mobskill_use(target_md,tick,MSC_CASTTARGETED);
			target_md->target_id = id;
		}
	}

	if( casttime<=0 )	/* 詠唱の無いものはキャンセルされない */
		src_ud->state.skillcastcancel=0;

	src_ud->canact_tick  = tick + casttime + delay;
	src_ud->canmove_tick = tick;
	src_ud->skilltarget  = target_id;
	src_ud->skillx       = 0;
	src_ud->skilly       = 0;
	src_ud->skillid      = skill_num;
	src_ud->skilllv      = skill_lv;

	if(
		(src_sd && !(battle_config.pc_cloak_check_type&2) ) ||
		(src_md && !(battle_config.monster_cloak_check_type&2) )
	) {
	 	if( sc_data && sc_data[SC_CLOAKING].timer != -1 && skill_num != AS_CLOAKING)
			status_change_end(src,SC_CLOAKING,-1);
	}

	if(casttime > 0) {
		int skill;
		src_ud->skilltimer = add_timer( tick+casttime, skill_castend_id, src->id, 0 );
		if(src_sd && (skill = pc_checkskill(src_sd,SA_FREECAST)) > 0) {
			src_sd->prev_speed = src_sd->speed;
			src_sd->speed = src_sd->speed*(175 - skill*5)/100;
			clif_updatestatus(src_sd,SP_SPEED);
		}
		else
			unit_stop_walking(src,1);
	}
	else {
		if(skill_num != SA_CASTCANCEL)
			src_ud->skilltimer = -1;
		skill_castend_id(src_ud->skilltimer,tick,src->id,0);
	}
	return 1;
}

int unit_skilluse_pos(struct block_list *src, int skill_x, int skill_y, int skill_num, int skill_lv)
{
	int id = skill_get_skilldb_id(skill_num);

	if( id < 0 || id >= MAX_SKILL_DB+MAX_HOMSKILL_DB+MAX_GUILDSKILL_DB) {
		return 0;
	} else {
		return unit_skilluse_pos2(
			src, skill_x, skill_y, skill_num, skill_lv,
			skill_castfix(src, skill_get_cast( skill_num, skill_lv) ) + skill_get_fixedcast(skill_num, skill_lv),
			skill_db[id].castcancel
		);
	}
}

int unit_skilluse_pos2( struct block_list *src, int skill_x, int skill_y, int skill_num, int skill_lv, int casttime, int castcancel) {
	struct map_session_data *src_sd = NULL;
	struct pet_data         *src_pd = NULL;
	struct mob_data         *src_md = NULL;
	struct homun_data       *src_hd = NULL;
	struct unit_data        *src_ud = NULL;
	int zone;
	unsigned int tick = gettick();
	int delay=0,range;
	struct status_change *sc_data;
	struct block_list    bl;

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
	}
	if( src_ud == NULL) return 0;

	if(unit_isdead(src)) return 0;

	sc_data = status_get_sc_data(src);

	//スキル制限
	zone = skill_get_zone(skill_num);
	if(zone){
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
		if(ban)
		{
			if(src_sd)
			{
				if(skill_num == AL_TELEPORT)
					clif_skill_teleportmessage(src_sd,0);
				else
					clif_skill_fail(src_sd,skill_num,0,0);
			}
			return 0;
		}
	}

	//チェイスウォークだと設置系失敗
	if(src_sd && pc_ischasewalk(src_sd))
	 	return 0;

	// コンディション確認
	{
		struct skill_condition sc;
		memset( &sc, 0, sizeof( struct skill_condition ) );
		sc.id     = skill_num;
		sc.lv     = skill_lv;
		sc.x      = skill_x;
		sc.y      = skill_y;

		if(!skill_check_condition2(src, &sc ,0)) return 0;

		skill_num = sc.id;
		skill_lv  = sc.lv;
		skill_x   = sc.x;
		skill_y   = sc.y;
	}

	/* 射程と障害物チェック */
	bl.type = BL_NUL;
	bl.m = src->m;
	bl.x = skill_x;
	bl.y = skill_y;
	range = skill_get_range(skill_num,skill_lv);
	if(range < 0)
		range = status_get_range(src) - (range + 1);

	if(!battle_check_range(src,&bl,range+1))
		return 0;

	if(!map_getcell(src->m,skill_x,skill_y,CELL_CHKPASS))
		return 0;

	unit_stopattack(src);

	delay=skill_delayfix(src, skill_get_delay( skill_num,skill_lv), skill_get_cast( skill_num,skill_lv) );
	src_ud->state.skillcastcancel = castcancel;

	if(battle_config.pc_skill_log)
		printf("PC %d skill use target_pos=(%d,%d) skill=%d lv=%d cast=%d\n",src->id,skill_x,skill_y,skill_num,skill_lv,casttime);

	//メモライズ状態ならキャストタイムが1/2
	if(sc_data && sc_data[SC_MEMORIZE].timer != -1 && casttime > 0){
		casttime = casttime/2;
		if((--sc_data[SC_MEMORIZE].val2)<=0)
			status_change_end(src, SC_MEMORIZE, -1);
	}

	if( casttime>0 ) {
		/* 詠唱が必要 */
		unit_stop_walking( src, 1 );		// 歩行停止
		clif_skillcasting( src, src->id, 0, skill_x,skill_y, skill_num,casttime );
	}

	if( casttime<=0 )	/* 詠唱の無いものはキャンセルされない */
		src_ud->state.skillcastcancel=0;

	tick=gettick();
	src_ud->canact_tick  = tick + casttime + delay;
	src_ud->canmove_tick = tick;
	src_ud->skillid      = skill_num;
	src_ud->skilllv      = skill_lv;
	src_ud->skillx       = skill_x;
	src_ud->skilly       = skill_y;
	src_ud->skilltarget  = 0;

	if(src_sd && !(battle_config.pc_cloak_check_type&2) && sc_data && sc_data[SC_CLOAKING].timer != -1)
		status_change_end(src,SC_CLOAKING,-1);
	if(src_md && !(battle_config.monster_cloak_check_type&2) && sc_data && sc_data[SC_CLOAKING].timer != -1)
		status_change_end(src,SC_CLOAKING,-1);

	if(casttime > 0) {
		int skill;
		src_ud->skilltimer = add_timer( tick+casttime, skill_castend_pos, src->id, 0 );
		if(src_sd && (skill = pc_checkskill(src_sd,SA_FREECAST)) > 0) {
			src_sd->prev_speed = src_sd->speed;
			src_sd->speed = src_sd->speed*(175 - skill*5)/100;
			clif_updatestatus(src_sd,SP_SPEED);
		}
		else
			unit_stop_walking(src,1);
	}
	else {
		src_ud->skilltimer = -1;
		skill_castend_pos(src_ud->skilltimer,tick,src->id,0);
	}
	return 1;
}

// 攻撃停止
void unit_stopattack(struct block_list *bl)
{
	struct unit_data *ud = NULL;

	nullpo_retv(bl);

	ud = unit_bl2ud(bl);
	if(!ud || ud->attacktimer == -1) {
		return;
	}
	delete_timer( ud->attacktimer, unit_attack_timer );
	ud->attacktimer = -1;
	if(bl->type==BL_MOB) {
		mob_unlocktarget( (struct mob_data*)bl, gettick());
	}

	return;
}

int unit_unattackable(struct block_list *bl) {
	if( bl == NULL || bl->type != BL_MOB) return 0;

	mob_unlocktarget( (struct mob_data*)bl, gettick()) ;
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

	nullpo_retr(0, src);
	nullpo_retr(0, src_ud = unit_bl2ud(src));

	target=map_id2bl(target_id);
	if(target==NULL || battle_check_target(src,target,BCT_ENEMY)<=0) {
		unit_unattackable(src);
		return 1;
	}
	unit_stopattack(src);
	src_ud->attacktarget          = target_id;
	src_ud->state.attack_continue = type;

	d=DIFF_TICK(src_ud->attackabletime,gettick());
	if(d > 0){	// 攻撃delay中
		src_ud->attacktimer = add_timer(src_ud->attackabletime,unit_attack_timer,src->id,0);
	} else {
		// 本来timer関数なので引数を合わせる
		unit_attack_timer(-1,gettick(),src->id,0);
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int unit_can_reach(struct block_list *bl,int x,int y)
{
	struct walkpath_data wpd;

	nullpo_retr(0, bl);

	if( bl->x==x && bl->y==y )	// 同じマス
		return 1;

	// 障害物判定
	wpd.path_len=0;
	wpd.path_pos=0;
	wpd.path_half=0;
	return (path_search(&wpd,bl->m,bl->x,bl->y,x,y,0)!=-1)?1:0;
}

/*==========================================
 * 移動可能な状態かどうか
 *------------------------------------------
 */
int unit_can_move(struct block_list *bl)
{
	struct map_session_data *sd = NULL;
	struct unit_data *ud = NULL;
	struct status_change *sc_data = NULL;
	short *sc_count;
	unsigned short *opt1;
	unsigned int *option;

	nullpo_retr(0, bl);

	ud = unit_bl2ud(bl);
	if( ud == NULL )
		return 0;

	if( DIFF_TICK(ud->canmove_tick, gettick()) > 0 )
		return 0;

	if( (opt1 = status_get_opt1(bl)) && *opt1 > 0 && *opt1 != 6 )
		return 0;

	if( bl->type == BL_PC )
		sd = (struct map_session_data *)bl;
	if( (option = status_get_option(bl)) && (*option)&2 && (!sd || pc_checkskill(sd,RG_TUNNELDRIVE) <= 0) )
		return 0;

	sc_data = status_get_sc_data(bl);
	sc_count = status_get_sc_count(bl);

	if( ud->skilltimer != -1 && (!sc_data || sc_data[SC_SELFDESTRUCTION].timer == -1) && (!sd || pc_checkskill(sd,SA_FREECAST) <= 0) )
		return 0;

	if(sc_data && sc_count && (*sc_count) > 0)
	{
		if(	sc_data[SC_ANKLE].timer != -1 ||		// アンクルスネア
			sc_data[SC_AUTOCOUNTER].timer != -1 ||		// オートカウンター
			sc_data[SC_TRICKDEAD].timer != -1 ||		// 死んだふり
			sc_data[SC_BLADESTOP].timer != -1 ||		// 白刃取り
			sc_data[SC_SPIDERWEB].timer != -1 ||		// スパイダーウェッブ
			sc_data[SC_TIGERFIST].timer != -1 ||		// 伏虎拳
			sc_data[SC_HOLDWEB].timer != -1 ||		// ホールドウェブ
			sc_data[SC_MADNESSCANCEL].timer != -1 ||	// マッドネスキャンセラー
			sc_data[SC_CLOSECONFINE].timer != -1 ||		// クローズコンファイン
			(sc_data[SC_GRAVITATION_USER].timer != -1 && battle_config.player_gravitation_type < 2) ||	//グラビテーションフィールド使用者
			(battle_config.hermode_no_walking && sc_data[SC_DANCING].timer != -1 && sc_data[SC_DANCING].val1 == CG_HERMODE)
		)
			return 0;

		if(sc_data[SC_LONGINGFREEDOM].timer == -1 && sc_data[SC_DANCING].timer != -1) {
			// 合奏スキル演奏中
			if(sc_data[SC_DANCING].val4)
				return 0;
			// 単独合奏時に動けない設定
			if(skill_get_unit_flag(sc_data[SC_DANCING].val1) & UF_ENSEMBLE) {
				if(!sd || (!battle_config.player_skill_partner_check && !(battle_config.sole_concert_type & 1)))
					return 0;
			}
		}

		if((sc_data[SC_BASILICA].timer != -1 && sc_data[SC_BASILICA].val2 == bl->id) ||
		   (sc_data[SC_GOSPEL].timer != -1 && sc_data[SC_GOSPEL].val2 == bl->id))
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
	struct status_change *sc_data = NULL;

	nullpo_retr(0, bl);

	sc_data = status_get_sc_data(bl);
	if(sc_data) {
		if(	sc_data[SC_RUN].timer != -1 ||			// 駆け足
			sc_data[SC_FORCEWALKING].timer != -1 ||		// 強制移動
			sc_data[SC_SELFDESTRUCTION].timer != -1		// 自爆2
		)
			return 1;
	}
	return 0;
}

/*==========================================
 * 攻撃 (timer関数)
 *------------------------------------------
 */
int unit_attack_timer_sub(int tid,unsigned int tick,int id,int data)
{
	struct block_list *src, *target;
	struct status_change *sc_data, *tsc_data;
	int dist,skill,range;
	struct unit_data *src_ud;
	struct map_session_data *src_sd = NULL, *target_sd = NULL;
	struct pet_data         *src_pd = NULL;
	struct mob_data         *src_md = NULL, *target_md = NULL;
	struct homun_data       *src_hd = NULL, *target_hd = NULL;

	if((src=map_id2bl(id))==NULL)
		return 0;
	if((src_ud=unit_bl2ud(src)) == NULL)
		return 0;

	if(src_ud->attacktimer != tid){
		if(battle_config.error_log)
			printf("unit_attack_timer %d != %d\n",src_ud->attacktimer,tid);
		return 0;
	}
	src_ud->attacktimer=-1;
	target=map_id2bl(src_ud->attacktarget);

	if(src->prev == NULL)
		return 0;
	if(target==NULL || target->prev == NULL)
		return 0;
	if(src->m != target->m || unit_isdead(src) || unit_isdead(target))	// ターゲットと同じMAPでないか死んでるなら攻撃しない
		return 0;

	sc_data  = status_get_sc_data( src    );
	tsc_data = status_get_sc_data( target );

	if( sc_data ) {
		if(sc_data[SC_AUTOCOUNTER].timer != -1 ||
		   sc_data[SC_BLADESTOP].timer != -1 ||
		   sc_data[SC_FULLBUSTER].timer != -1 ||
		   sc_data[SC_KEEPING].timer != -1)
			return 0;
	}
	if( tsc_data ) {
		if(tsc_data[SC_TRICKDEAD].timer != -1)
			return 0;
	}

	src_sd = BL_DOWNCAST( BL_PC , src );
	src_pd = BL_DOWNCAST( BL_PET, src );
	src_md = BL_DOWNCAST( BL_MOB, src );
	src_hd = BL_DOWNCAST( BL_HOM, src );

	target_sd = BL_DOWNCAST( BL_PC , target );
	target_md = BL_DOWNCAST( BL_MOB, target );
	target_hd = BL_DOWNCAST( BL_HOM, target );

	if( src_sd ) {
		unsigned int *opt;
		// 異常などで攻撃できない
		if( src_sd->opt1 > 0 || src_sd->status.option&2 || pc_ischasewalk(src_sd) )
			return 0;
		// 昆虫・悪魔状態でないならハイド中の敵に攻撃できない
		if( (opt = status_get_option(target)) != NULL && *opt&0x46 && src_sd->race != RCT_INSECT && src_sd->race != RCT_DEMON )
			return 0;
	}

	if( src_md ) {
		int mode, race;
		if(src_md->opt1 > 0 || src_md->option&2)
			return 0;
		if(src_md->sc_data && src_md->sc_data[SC_WINKCHARM].timer != -1)
			return 0;

		mode = status_get_mode(src);
		race = status_get_race(src);

		if( !(mode&0x80) )
			return 0;
		if( !(mode&0x20) ) {
			if( tsc_data && (tsc_data[SC_FORCEWALKING].timer != -1 || tsc_data[SC_WINKCHARM].timer != -1) )
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
				clif_skill_fail(src_sd,1,4,0);
			return 0;
		}
	}

	dist  = unit_distance(src->x,src->y,target->x,target->y);
	range = status_get_range( src );
	if( src_md && status_get_mode( src ) & 1 ) range++;

	if(src_sd && (src_sd->status.weapon != WT_BOW && !(src_sd->status.weapon >= WT_HANDGUN && src_sd->status.weapon <= WT_GRENADE))) range++;
	if( dist > range ){	// 届かないので移動
		if(!unit_can_reach(src,target->x,target->y))
			return 0;
		if(src_sd)
			clif_movetoattack(src_sd,target);
		return 1;
	}
	if(dist <= range && !battle_check_range(src,target,range) ) {
		if(unit_can_reach(src,target->x,target->y))
			unit_walktoxy(src,target->x,target->y);
		src_ud->attackabletime = tick + status_get_adelay(src);
	}
	else {
		// 向き設定
		int dir = map_calc_dir(src, target->x,target->y );
		if(src_sd && battle_config.pc_attack_direction_change)
			pc_setdir(src_sd, dir, dir);
		if(src_pd && battle_config.monster_attack_direction_change)
			src_pd->dir = dir;
		if(src_md && battle_config.monster_attack_direction_change)
			src_md->dir = dir;
		if(src_hd && battle_config.monster_attack_direction_change)
			src_hd->dir = dir;
		if(src_ud->walktimer != -1)
			unit_stop_walking(src,1);

		if( src_md && mobskill_use(src_md,tick,-2) ) {	// スキル使用
			return 1;
		}
		if(!sc_data || (sc_data[SC_COMBO].timer == -1 && sc_data[SC_TKCOMBO].timer == -1)) {
			map_freeblock_lock();
			unit_stop_walking(src,1);

			src_ud->attacktarget_lv = battle_weapon_attack(src,target,tick,0);

			if(src_md && !(battle_config.monster_cloak_check_type&2) && sc_data && sc_data[SC_CLOAKING].timer != -1)
				status_change_end(src,SC_CLOAKING,-1);
			if(src_sd && !(battle_config.pc_cloak_check_type&2) && sc_data && sc_data[SC_CLOAKING].timer != -1)
				status_change_end(src,SC_CLOAKING,-1);
			if(src_sd && src_sd->status.pet_id > 0 && src_sd->pd && src_sd->petDB)
				pet_target_check(src_sd,target,0);
			map_freeblock_unlock();
			if(src_ud->skilltimer != -1 && src_sd && (skill = pc_checkskill(src_sd,SA_FREECAST)) > 0 )	// フリーキャスト
				src_ud->attackabletime = tick + (status_get_adelay(src)*(150 - skill*5)/100);
			else
				src_ud->attackabletime = tick + status_get_adelay(src);
		}
		else if(src_ud->attackabletime <= tick) {
			if(src_ud->skilltimer != -1 && src_sd && (skill = pc_checkskill(src_sd,SA_FREECAST)) > 0 )	// フリーキャスト
				src_ud->attackabletime = tick + (status_get_adelay(src)*(150 - skill*5)/100);
			else
				src_ud->attackabletime = tick + status_get_adelay(src);
		}
		if(src_ud->attackabletime <= tick)
			src_ud->attackabletime = tick + (battle_config.max_aspd<<1);
	}

	if(src_ud->state.attack_continue) {
		src_ud->attacktimer = add_timer(src_ud->attackabletime,unit_attack_timer,src->id,0);
	}
	return 1;
}

int unit_attack_timer(int tid,unsigned int tick,int id,int data) {
	if(unit_attack_timer_sub(tid, tick, id, data) == 0) {
		unit_unattackable( map_id2bl( id ) );
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
	struct status_change    *sc_data = NULL;
	unsigned long tick = gettick();

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
		}
	}

	ud->canact_tick  = tick;
	ud->canmove_tick = tick;

	if(sd && pc_checkskill(sd,SA_FREECAST) > 0) {
		sd->speed = sd->prev_speed;
		clif_updatestatus(sd,SP_SPEED);
	}

	skillid = (type&1 && sd)? sd->skillid_old: ud->skillid;

	if(skill_get_inf(skillid)&34)
		ret = delete_timer( ud->skilltimer, skill_castend_pos );
	else
		ret = delete_timer( ud->skilltimer, skill_castend_id );
	if(ret < 0)
		printf("delete timer error : skillid : %d\n", skillid);

	if( md ) {
		md->skillidx = -1;
	}

	ud->skilltimer = -1;
	clif_skillcastcancel(bl);

	sc_data = status_get_sc_data(bl);
	if(sc_data && sc_data[SC_SELFDESTRUCTION].timer != -1)
		status_change_end(bl,SC_SELFDESTRUCTION,-1);

	return 1;
}

// unit_data の初期化処理
int unit_dataset(struct block_list *bl) {
	struct unit_data *ud;
	nullpo_retr(0, ud = unit_bl2ud(bl));

	memset( ud, 0, sizeof( struct unit_data) );
	ud->bl             = bl;
	ud->walktimer      = -1;
	ud->skilltimer     = -1;
	ud->attacktimer    = -1;
	ud->attackabletime = gettick();
	ud->canact_tick    = gettick();
	ud->canmove_tick   = gettick();

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
	{
		pc_heal((struct map_session_data*)bl,hp,sp);
	}else if(bl->type == BL_MOB)
	{
		mob_heal((struct mob_data*)bl,hp);
	}
	else if(bl->type == BL_HOM)
	{
		homun_heal((struct homun_data*)bl,hp,sp);
	}
	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int unit_fixdamage(struct block_list *src,struct block_list *target,unsigned int tick,int sdelay,int ddelay,int damage,int div,int type,int damage2)
{
	nullpo_retr(0, target);

	if(damage+damage2 <= 0)
		return 0;
	//タゲ
	if(target->type==BL_MOB){
		mob_attacktarget((struct mob_data*)target,src,0);
	}
	clif_damage(target,target,tick,sdelay,ddelay,damage,div,type,damage2);
	battle_damage(src,target,damage+damage2,0);
	return 0;
}

/*==========================================
 * 自分をロックしているユニットの数を数える(foreachclient)
 *------------------------------------------
 */
static int unit_counttargeted_sub(struct block_list *bl, va_list ap)
{
	int id, *c, target_lv;
	nullpo_retr(0, bl);

	id        = va_arg(ap,int);
	c         = va_arg(ap,int *);
	target_lv = va_arg(ap,int);

	if(bl->id == id) {
		// 自分
	} else if(bl->type == BL_PC) {
		struct map_session_data *sd=(struct map_session_data *)bl;
		if( sd && sd->ud.attacktarget == id && sd->ud.attacktimer != -1 && sd->ud.attacktarget_lv >= target_lv )
			(*c)++;
	} else if(bl->type == BL_MOB) {
		struct mob_data *md = (struct mob_data *)bl;
		if( md && md->target_id == id && md->ud.attacktimer != -1 && md->ud.attacktarget_lv >= target_lv )
			(*c)++;
	} else if(bl->type == BL_PET) {
		struct pet_data *pd = (struct pet_data *)bl;
		if( pd && pd->target_id == id && pd->ud.attacktimer != -1 && pd->ud.attacktarget_lv >= target_lv )
			(*c)++;
	} else if(bl->type == BL_HOM) {
		struct homun_data *hd = (struct homun_data *)bl;
		if( hd && hd->target_id == id && hd->ud.attacktimer != -1 && hd->ud.attacktarget_lv >= target_lv )
			(*c)++;
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
	int c = 0;
	nullpo_retr(0, bl);
	map_foreachinarea(unit_counttargeted_sub, bl->m,
		bl->x-AREA_SIZE,bl->y-AREA_SIZE,
		bl->x+AREA_SIZE,bl->y+AREA_SIZE,0,bl->id,&c,target_lv
	);
	return c;
}

int unit_isdead(struct block_list *bl) {
	nullpo_retr(1, bl);
	if(bl->type == BL_PC) {
		struct map_session_data *sd = (struct map_session_data*)bl;
		return (sd->state.dead_sit == 1);
	} else if(bl->type == BL_MOB) {
		struct mob_data *md = (struct mob_data *)bl;
		return md->hp<=0;
	} else if(bl->type == BL_PET) {
		return 0;
	} else if(bl->type == BL_HOM) {
		struct homun_data *hd = (struct homun_data *)bl;
		return hd->status.hp<=0;
	} else {
		return 0;
	}
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

	id=va_arg(ap,int);
	if(sd->ud.attacktarget==id)
		unit_stopattack(&sd->bl);
	return 0;
}
/*==========================================
 * 見た目のサイズを変更する
 *------------------------------------------
 */
int unit_changeviewsize(struct block_list *bl,short size)
{
	nullpo_retr(0, bl);

	size=(size<0)?-1:(size>0)?1:0;

	if(bl->type == BL_PC) {
		struct map_session_data *sd = (struct map_session_data*)bl;
		sd->view_size=size;
	} else if(bl->type == BL_MOB) {
		struct mob_data *md = (struct mob_data *)bl;
		md->view_size=size;
	} else if(bl->type == BL_PET) {
		struct pet_data *pd = (struct pet_data *)bl;
		pd->view_size=size;
	} else if(bl->type == BL_HOM) {
		struct homun_data *hd = (struct homun_data *)bl;
		hd->view_size=size;
	} else if(bl->type == BL_NPC) {
		struct npc_data *nd = (struct npc_data *)bl;
		nd->view_size=size;
	} else {
		return 0;
	}
	if(size!=0)
		clif_misceffect2(bl,421+size);
	return 0;
}

/*==========================================
 * スキル詠唱中かどうかを返す
 *------------------------------------------
 */

int unit_iscasting(struct block_list *bl) {
	struct unit_data *ud = unit_bl2ud(bl);

	if( ud == NULL )
		return 0;
	else
		return (ud->skilltimer != -1);
}

/*==========================================
 * 歩行中かどうかを返す
 *------------------------------------------
 */

int unit_iswalking(struct block_list *bl) {
	struct unit_data *ud = unit_bl2ud(bl);

	if( ud == NULL )
		return 0;
	else
		return (ud->walktimer != -1);
}

/*==========================================
 * マップから離脱する
 *------------------------------------------
 */
int unit_remove_map(struct block_list *bl, int clrtype)
{
	struct unit_data *ud;
	struct status_change *sc_data;

	nullpo_retr(0, bl);
	nullpo_retr(0, ud = unit_bl2ud(bl));

	if(bl->prev == NULL) {
		// printf("unit_remove_map: nullpo bl->prev\n");
		return 1;
	}
	map_freeblock_lock();

	unit_stop_walking(bl,1);			// 歩行中断
	unit_stopattack(bl);				// 攻撃中断
	unit_skillcastcancel(bl,0);			// 詠唱中断
	skill_stop_dancing(bl,1);			// ダンス中断
	skill_clear_unitgroup(bl);			// スキルユニットグループの削除
	if(!unit_isdead(bl))
		skill_unit_move(bl,gettick(),0);	// スキルユニットから離脱

	// tickset 削除
	linkdb_final( &ud->skilltickset );
	status_clearpretimer( bl );

	// MAP を離れるときの状態異常関連
	sc_data = status_get_sc_data(bl);
	if( sc_data ) {
		// ブレードストップを終わらせる
		if(sc_data[SC_BLADESTOP].timer!=-1) {
			status_change_end(bl,SC_BLADESTOP,-1);
		}
		// バシリカ削除
		if(sc_data[SC_BASILICA].timer!=-1) {
			skill_basilica_cancel( bl );
			status_change_end(bl,SC_BASILICA,-1);
		}
		// グラフィティ削除
		if(sc_data[SC_GRAFFITI].timer != -1) {
			status_change_end(bl, SC_GRAFFITI, -1);
		}
		// アンクルスネア撤去
		if(sc_data[SC_ANKLE].timer != -1) {
			status_change_end(bl, SC_ANKLE, -1);
		}
		sc_data = NULL;
	}

	if(bl->type == BL_PC) {
		struct map_session_data *sd = (struct map_session_data*)bl;
		// チャットから出る
		if(sd->chatID)
			chat_leavechat(sd,0);

		// 取引を中断する
		if(sd->trade_partner)
			trade_tradecancel(sd);

		// 露天を閉じる
		if(sd->vender_id)
			vending_closevending(sd);

		// 倉庫を開いてるなら保存する
		if(sd->state.storage_flag == 2)
			storage_guild_storage_quit(sd,0);
		else
			storage_storage_quit(sd);

		// 友達リスト勧誘を拒否する
		if(sd->friend_invite>0)
			friend_add_reply(sd,sd->friend_invite,sd->friend_invite_char,0);

		// パーティ勧誘を拒否する
		if(sd->party_invite>0)
			party_reply_invite(sd,sd->party_invite_account,0);

		// ギルド勧誘を拒否する
		if(sd->guild_invite>0)
			guild_reply_invite(sd,sd->guild_invite,0);

		// ギルド同盟勧誘を拒否する
		if(sd->guild_alliance>0)
			guild_reply_reqalliance(sd,sd->guild_alliance_account,0);

		// 養子要請を拒否する
		if(sd->adopt_invite>0)
			pc_adopt_reply(sd,0,0,0);

		pc_delinvincibletimer(sd);		// 無敵タイマー削除

		// PVP タイマー削除
		if(sd->pvp_timer!=-1) {
			delete_timer(sd->pvp_timer,pc_calc_pvprank_timer);
			sd->pvp_timer = -1;
		}

		skill_gangsterparadise(sd,0);			// ギャングスターパラダイス削除
		skill_cleartimerskill(&sd->bl);			// タイマースキルクリア

		clif_clearchar_area(&sd->bl,clrtype&0xffff);
		mob_ai_hard_spawn( &sd->bl, 0 );
		map_delblock(&sd->bl);
	} else if(bl->type == BL_MOB) {
		struct mob_data *md = (struct mob_data*)bl;

		linkdb_final( &md->dmglog );
//		mobskill_deltimer(md);
		md->state.skillstate=MSS_DEAD;
		md->last_deadtime=gettick();
		// 死んだのでこのmobへの攻撃者全員の攻撃を止める
		clif_foreachclient(unit_mobstopattacked,md->bl.id);
		status_change_clear(&md->bl,2);	// ステータス異常を解除する
		skill_cleartimerskill(&md->bl);
		if(md->deletetimer!=-1)
			delete_timer(md->deletetimer,mob_timer_delete);
		md->deletetimer=-1;
		md->hp=md->target_id=md->attacked_id=0;
		md->attacked_players = 0;

		clif_clearchar_area(&md->bl,clrtype);
		if(mob_get_viewclass(md->class_) < MAX_VALID_PC_CLASS) {
			clif_clearchar_delay(gettick()+3000,&md->bl,0);
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
		if(md->sc_data!=NULL)
			status_free_sc_data(&md->bl);
#endif
		// 復活しないMOBの処理
		if(md->spawndelay1==-1 && md->spawndelay2==-1 && md->n==0){
			map_deliddb(&md->bl);
			if(md->lootitem) {
				map_freeblock(md->lootitem);
				md->lootitem=NULL;
			}
			map_freeblock(md);	// freeのかわり
		} else {
			unsigned int spawntime,spawntime1,spawntime2,spawntime3;
			spawntime1=md->last_spawntime+md->spawndelay1;
			spawntime2=md->last_deadtime+md->spawndelay2;
			spawntime3=gettick()+5000;
			// spawntime = max(spawntime1,spawntime2,spawntime3);
			if(DIFF_TICK(spawntime1,spawntime2)>0){
				spawntime=spawntime1;
			} else {
				spawntime=spawntime2;
			}
			if(DIFF_TICK(spawntime3,spawntime)>0){
				spawntime=spawntime3;
			}

			add_timer(spawntime,mob_delayspawn,bl->id,0);
		}
	} else if(bl->type == BL_PET) {
		struct pet_data *pd = (struct pet_data*)bl;
		clif_clearchar_area(&pd->bl,0);
		map_delblock(&pd->bl);
	} else if(bl->type == BL_HOM) {
		struct homun_data *hd = (struct homun_data*)bl;
		clif_clearchar_area(&hd->bl,clrtype);
		mob_ai_hard_spawn( &hd->bl, 0 );
		map_delblock(&hd->bl);
	}
	map_freeblock_unlock();
	return 0;
}

/*==========================================
 * マップから離脱後、領域を解放する
 *------------------------------------------
 */
int unit_free(struct block_list *bl, int clrtype) {
	struct unit_data *ud = unit_bl2ud( bl );
	nullpo_retr(0, ud);

	map_freeblock_lock();
	if( bl->prev )
		unit_remove_map(bl, clrtype);

	if( bl->type == BL_PC ) {
		struct map_session_data *sd = (struct map_session_data*)bl;

		if(unit_isdead(&sd->bl))
			pc_setrestartvalue(sd,2);

		if(sd->sc_data && sd->sc_data[SC_BERSERK].timer!=-1) //バーサーク中の終了はHPを100に
			sd->status.hp = 100;

		//OnPCLogoutイベント
		if(battle_config.pc_logout_script)
			npc_event_doall_id("OnPCLogout",sd->bl.id,sd->bl.m);

		friend_send_online( sd, 1 );			// 友達リストのログアウトメッセージ送信
		party_send_logout(sd);					// パーティのログアウトメッセージ送信
		guild_send_memberinfoshort(sd,0);		// ギルドのログアウトメッセージ送信
		intif_save_scdata(sd);				// ステータス異常データの保存
		status_change_clear(&sd->bl,1);			// ステータス異常を解除する
		pc_cleareventtimer(sd);					// イベントタイマを破棄する
		pc_delspiritball(sd,sd->spiritball,1);	// 気功削除
		storage_storage_save(sd);
		storage_delete(sd->status.account_id);
		pc_makesavestatus(sd);
		sd->state.waitingdisconnect = 1;
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
		if (pd->a_skill)
		{
			aFree(pd->a_skill);
			pd->a_skill = NULL;
		}
		if (pd->s_skill)
		{
			if (pd->s_skill->timer != -1)
				delete_timer(pd->s_skill->timer, pet_skill_support_timer);
			aFree(pd->s_skill);
			pd->s_skill = NULL;
		}
		if(sd && sd->pet_hungry_timer != -1)
			pet_hungry_timer_delete(sd);
		map_deliddb(&pd->bl);
		aFree(pd->lootitem);
		map_freeblock(pd);
	} else if( bl->type == BL_HOM ) {
		struct homun_data *hd = (struct homun_data*)bl;
		struct map_session_data *sd = hd->msd;

		status_change_clear(&hd->bl,1);			// ステータス異常を解除する
		if(sd && sd->hd) {
		//	sd->hd->status.incubate = 0;
			homun_save_data(sd);
			if(sd->hd->natural_heal_hp != -1 || sd->hd->natural_heal_sp != -1)
				homun_natural_heal_timer_delete(sd->hd);
			sd->hd = NULL;
		}
		if(sd && sd->homun_hungry_timer != -1)
			homun_hungry_timer_delete(sd);
		map_deliddb(&hd->bl);
		map_freeblock(hd);
	}
	map_freeblock_unlock();
	return 0;
}

int do_init_unit(void) {
	add_timer_func_list(unit_attack_timer,  "unit_attack_timer");
	add_timer_func_list(unit_walktoxy_timer,"unit_walktoxy_timer");
	return 0;
}

int do_final_unit(void) {
	// nothing to do
	return 0;
}
