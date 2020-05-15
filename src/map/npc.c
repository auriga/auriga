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

// $Id: npc.c,v 1.12 2003/07/01 00:29:54 lemit Exp $

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "db.h"
#include "timer.h"
#include "nullpo.h"
#include "malloc.h"
#include "utils.h"

#include "map.h"
#include "npc.h"
#include "clif.h"
#include "intif.h"
#include "pc.h"
#include "itemdb.h"
#include "script.h"
#include "mob.h"
#include "pet.h"
#include "battle.h"
#include "skill.h"
#include "unit.h"
#include "status.h"
#include "memorial.h"

struct npc_src_list {
	struct npc_src_list * next;
	struct npc_src_list * prev;
	char name[4];
};

static struct npc_src_list *npc_src_first, *npc_src_last;
static int npc_id = START_NPC_NUM;
static int npc_warp = 0, npc_shop = 0, npc_script = 0, npc_mob = 0;

static struct dbt *ev_db = NULL;
static struct dbt *npcname_db = NULL;

struct event_data {
	struct npc_data *nd;
	int pos;
	char *key;
	struct event_data *next;
	struct event_data *prev;
};

static struct tm ev_tm_b;	// 時計イベント用

static int npc_exportlabel_data(struct npc_data *nd);


/*==========================================
 * IDを取得
 *------------------------------------------
 */
int npc_get_new_npc_id(void)
{
	if(npc_id == END_NPC_NUM+1) {	// 警告は一度だけ
		printf("npc_get_new_id : ID is over END_NPC_NUM %d\n",END_NPC_NUM);
	} else if(npc_id == 0x7fffffff) {
		printf("npc_get_new_id : ID is overflow !!\n");
		exit(1);		// 整合性が取れなくなるので落とす
	}
	return npc_id++;
}

/*==========================================
 * NPCの無効化/有効化
 * npc_enable
 * npc_enable_sub 有効時にOnTouchイベントを実行
 *------------------------------------------
 */
static int npc_enable_sub( struct block_list *bl, va_list ap )
{
	struct map_session_data *sd;
	struct npc_data *nd;
	char name[50];
	int i;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, nd = va_arg(ap,struct npc_data *));
	nullpo_retr(0, sd = (struct map_session_data *)bl);

	if(nd->flag&1) {	// 無効化されている
		for(i=0; i < MAX_EVENTQUEUE; i++) {
			if(sd->areanpc_id[i] == nd->bl.id) {	// NPCと接触していたら解放させる
				sd->areanpc_id[i] = 0;
			}
		}
		return 1;
	}

	for(i=0; i < MAX_EVENTQUEUE; i++) {
		if(sd->areanpc_id[i] == 0) {
			sd->areanpc_id[i] = nd->bl.id;
			break;
		}
	}
	if(i == MAX_EVENTQUEUE)
		return 1;
	sprintf(name, "%s::OnTouch", nd->exname);

	switch(nd->subtype) {
	case WARP:
		// 隠れているとワープできない
		if(pc_ishiding(sd))
			break;
		skill_stop_dancing(&sd->bl,0);
		pc_setpos(sd,nd->u.warp.name,nd->u.warp.x,nd->u.warp.y,0);
		break;
	case SCRIPT:
		if(npc_event(sd,name)) {
			if(sd->npc_id != 0)
				return 0;
			npc_click(sd,nd->bl.id);
		}
		break;
	}

	return 0;
}

int npc_enable(const char *name,int flag)
{
	struct npc_data *nd = (struct npc_data *)strdb_search(npcname_db,name);
	int xs = 0, ys = 0;

	if (nd == NULL)
		return 0;

	if (flag&1) {	// 有効化
		nd->flag &= ~3;
		clif_spawnnpc(nd);
	} else if (flag&2) {
		nd->flag &= ~1;
		nd->option = OPTION_NOTHING;
		clif_changeoption(&nd->bl);
	} else if (flag&4) {
		nd->flag |= 1;
		nd->option = OPTION_HIDE;
		clif_changeoption(&nd->bl);
	} else {	// 無効化
		nd->flag |= 3;
		clif_clearchar(&nd->bl,0);
	}
	switch(nd->subtype) {
	case WARP:
		xs = nd->u.warp.xs;
		ys = nd->u.warp.ys;
		break;
	case SCRIPT:
		xs = nd->u.scr.xs;
		ys = nd->u.scr.ys;
		break;
	}
	if (xs > 0 || ys > 0) {
		map_foreachinarea(npc_enable_sub,
			nd->bl.m,nd->bl.x-xs/2,nd->bl.y-ys/2,nd->bl.x+xs/2,nd->bl.y+ys/2,
			BL_PC,nd);
	}

	return 0;
}

/*==========================================
 * NPCを名前で探す
 *------------------------------------------
 */
struct npc_data* npc_name2id(const char *name)
{
	return (struct npc_data *)strdb_search(npcname_db,name);
}

/*==========================================
 * イベントの遅延実行
 *------------------------------------------
 */
static int npc_event_timer(int tid,unsigned int tick,int id,void *data)
{
	struct map_session_data *sd = map_id2sd(id);
	char *p = (char *)data;

	if(sd == NULL)
		return 0;

	npc_event(sd,p);
	aFree(p);
	return 0;
}

/*==========================================
 * イベントキューのイベント処理
 *------------------------------------------
 */
int npc_event_dequeue(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	if(sd->stack) {
		// 元のスタック情報を破棄
		script_free_stack(sd->stack);
		sd->stack = NULL;
	}

	sd->npc_sleep = NULL;
	sd->npc_pos = -1;
	sd->npc_id = 0;
	sd->state.menu_or_input = 0;
	sd->progressbar.npc_id = 0;
	sd->progressbar.tick = 0;

	if(sd->eventqueue[0][0]) {	// キューのイベント処理
		char *name = (char *)aCalloc(50,sizeof(char));
		int i;
		unsigned int tick = gettick();

		// copy the first event
		memcpy(name,sd->eventqueue[0],50);

		// shift queued events down by one
		for(i=1; i<MAX_EVENTQUEUE; i++)
			memcpy(sd->eventqueue[i-1],sd->eventqueue[i],50);

		// clear the last event
		sd->eventqueue[MAX_EVENTQUEUE-1][0] = 0;

		// add the timer
		add_timer2(tick+100,npc_event_timer,sd->bl.id,name);
	}
	return 0;
}

/*==========================================
 * 全てのNPCのOn*イベント実行
 *------------------------------------------
 */
int npc_event_doall(const char *name)
{
	struct event_data *ev;
	int c = 0;
	char buf[64] = "::";

	strncpy(buf+2,name,61);
	ev = (struct event_data *)strdb_search(ev_db, buf);

	while(ev) {
		if(ev->nd) {
			run_script(ev->nd->u.scr.script,ev->pos,0,ev->nd->bl.id);
			c++;
		}
		ev = ev->next;
	}

	return c;
}

/*==========================================
 * 指定マップ全てのNPCのOn*イベント実行
 *------------------------------------------
 */
int npc_event_doall_map(const char *name, int m)
{
	struct event_data *ev;
	int c = 0;
	char buf[64] = "::";

	strncpy(buf+2,name,61);
	ev = (struct event_data *)strdb_search(ev_db, buf);

	while(ev) {
		if(ev->nd && ev->nd->bl.m == m) {
			// 指定MAP内のNPCでのみ発動
			run_script(ev->nd->u.scr.script,ev->pos,0,ev->nd->bl.id);
			c++;
		}
		ev = ev->next;
	}

	return c;
}

/*==========================================
 * OnPC*イベント実行
 *------------------------------------------
 */
int npc_event_doall_id(const char *name, int rid, int m)
{
	struct event_data *ev;
	int c = 0;
	char buf[64] = "::";

	strncpy(buf+2,name,61);
	ev = (struct event_data *)strdb_search(ev_db, buf);

	while(ev) {
		// 同一MAPかマップ非配置型NPCでのみ発動
		if(ev->nd && (ev->nd->bl.m == m || ev->nd->bl.m == -1)) {
			run_script(ev->nd->u.scr.script,ev->pos,rid,ev->nd->bl.id);
			c++;
		}
		ev = ev->next;
	}

	return c;
}

/*==========================================
 * NPCイベント実行
 *------------------------------------------
 */
int npc_event_do(const char *name)
{
	int c = 0;

	if(name[0] == ':' && name[1] == ':') {
		c = npc_event_doall(name+2);
	} else {
		struct event_data *ev = (struct event_data *)strdb_search(ev_db,name);
		if(ev && ev->nd) {
			run_script(ev->nd->u.scr.script,ev->pos,0,ev->nd->bl.id);
			c = 1;
		}
	}
	return c;
}

/*==========================================
 * 時計イベント実行
 *------------------------------------------
 */
static int npc_event_do_clock(int tid,unsigned int tick,int id,void *data)
{
	time_t now;
	struct tm t;
	char buf[64];
	int c = 0;

	time(&now);
	memcpy(&t, localtime(&now), sizeof(t));

	if (t.tm_min != ev_tm_b.tm_min) {
		sprintf(buf,"OnMinute%02d",t.tm_min);
		c += npc_event_doall(buf);
		sprintf(buf,"OnClock%02d%02d",t.tm_hour,t.tm_min);
		c += npc_event_doall(buf);
		sprintf(buf,"OnWeekTime%02d%02d%02d",t.tm_wday,t.tm_hour,t.tm_min);
		c += npc_event_doall(buf);
	}
	if (t.tm_hour != ev_tm_b.tm_hour) {
		sprintf(buf,"OnHour%02d",t.tm_hour);
		c += npc_event_doall(buf);
	}
	if (t.tm_mday != ev_tm_b.tm_mday) {
		sprintf(buf,"OnDay%02d",t.tm_mday);
		c += npc_event_doall(buf);
		sprintf(buf,"OnMonthDay%02d%02d",t.tm_mon+1,t.tm_mday);
		c += npc_event_doall(buf);
	}
	memcpy(&ev_tm_b, &t, sizeof(ev_tm_b));
	return c;
}

/*==========================================
 * OnInitイベント実行(&時計イベント開始)
 *------------------------------------------
 */
int npc_event_do_oninit(void)
{
	unsigned int tick = gettick();
	int c = npc_event_doall("OnInit");

	printf("npc: OnInit Event done. (%d npc)\n",c);
	add_timer_interval(tick+100,npc_event_do_clock,0,NULL,1000);

	return 0;
}

/*==========================================
 * タイマーイベント実行
 *------------------------------------------
 */
static int npc_timerevent(int tid,unsigned int tick,int id,void *data)
{
	struct npc_data* nd = map_id2nd(id);
	struct npc_timerevent_list *te;

	if( nd == NULL || nd->u.scr.nexttimer < 0 ) {
		printf("npc_timerevent: ??\n");
		return 0;
	}
	nd->u.scr.timertick = tick;
	te = nd->u.scr.timer_event + nd->u.scr.nexttimer;
	nd->u.scr.timerid = -1;

	nd->u.scr.timer += PTR2INT(data);
	nd->u.scr.nexttimer++;
	if( nd->u.scr.timeramount > nd->u.scr.nexttimer ) {
		int next = nd->u.scr.timer_event[nd->u.scr.nexttimer].timer - nd->u.scr.timer;
		nd->u.scr.timerid = add_timer(tick+next,npc_timerevent,id,INT2PTR(next));
	}

	run_script(nd->u.scr.script,te->pos,0,nd->bl.id);
	return 0;
}

/*==========================================
 * タイマーイベント開始
 *------------------------------------------
 */
int npc_timerevent_start(struct npc_data *nd)
{
	int j, n, next;
	unsigned int tick = gettick();

	nullpo_retr(0, nd);

	n = nd->u.scr.timeramount;
	if( nd->u.scr.nexttimer >= 0 || n == 0 )
		return 0;

	for(j=0; j<n; j++) {
		if(nd->u.scr.timer_event[j].timer > nd->u.scr.timer)
			break;
	}
	nd->u.scr.nexttimer = j;
	nd->u.scr.timertick = tick;

	if(j >= n)
		return 0;

	next = nd->u.scr.timer_event[j].timer - nd->u.scr.timer;
	nd->u.scr.timerid = add_timer(tick+next,npc_timerevent,nd->bl.id,INT2PTR(next));
	return 0;
}

/*==========================================
 * タイマーイベント終了
 *------------------------------------------
 */
int npc_timerevent_stop(struct npc_data *nd)
{
	nullpo_retr(0, nd);

	if( nd->u.scr.nexttimer >= 0 ) {
		nd->u.scr.nexttimer = -1;
		nd->u.scr.timer += DIFF_TICK(gettick(), nd->u.scr.timertick);
		if(nd->u.scr.timerid != -1)
			delete_timer(nd->u.scr.timerid,npc_timerevent);
		nd->u.scr.timerid = -1;
	}
	return 0;
}

/*==========================================
 * タイマー値の取得
 *------------------------------------------
 */
int npc_gettimerevent_tick(struct npc_data *nd)
{
	int tick;

	nullpo_retr(0, nd);

	tick = nd->u.scr.timer;

	if( nd->u.scr.nexttimer >= 0 )
		tick += DIFF_TICK(gettick(), nd->u.scr.timertick);
	return tick;
}

/*==========================================
 * タイマー値の設定
 *------------------------------------------
 */
int npc_settimerevent_tick(struct npc_data *nd,int newtimer)
{
	int flag;

	nullpo_retr(0, nd);

	flag = nd->u.scr.nexttimer;

	npc_timerevent_stop(nd);
	nd->u.scr.timer = newtimer;
	if(flag >= 0)
		npc_timerevent_start(nd);
	return 0;
}

/*==========================================
 * タイムアウト実行
 *------------------------------------------
 */
static int npc_timeout_timer(int tid,unsigned int tick,int id,void *data)
{
	struct map_session_data* sd = NULL;

	if((sd = map_id2sd(id)) == NULL || sd->npc_id == 0) {
		if(sd) {
			sd->npc_idle_timer = -1;
		}
		return 0;
	}

	if(battle_config.npc_timeout_time > 0 && DIFF_TICK(tick, sd->npc_idle_tick) > (battle_config.npc_timeout_time*1000)) {
		clif_scriptclose(sd,sd->npc_id);
		sd->npc_id         =  0;
		sd->npc_idle_timer = -1;
		if(sd->stack) {
			// 元のスタック情報を破棄
			script_free_stack(sd->stack);
			sd->stack = NULL;
		}
		// menu, select, inputの返答待機解除（ギルド倉庫は応答を待つ）
		if(sd->state.menu_or_input == 1 && sd->state.gstorage_lockreq == 0)
			sd->state.menu_or_input = 0;

		// プログレスバーの応答待機解除
		if(sd->progressbar.tick) {
			sd->progressbar.npc_id = 0;
			sd->progressbar.tick   = 0;
		}
	} else {
		sd->npc_idle_timer = add_timer(gettick()+1000,npc_timeout_timer,sd->bl.id,0);
	}

	return 0;
}

/*==========================================
 * タイムアウトタイマー開始
 *------------------------------------------
 */
int npc_timeout_start(struct map_session_data *sd)
{
	unsigned int tick = gettick();

	nullpo_retr(0, sd);

	if( sd->npc_idle_timer == -1 )
		sd->npc_idle_timer = add_timer(tick+1000,npc_timeout_timer,sd->bl.id,0);
	sd->npc_idle_tick = tick;

	return 0;
}

/*==========================================
 * タイムアウトタイマー終了
 *------------------------------------------
 */
int npc_timeout_stop(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	if( sd->npc_idle_timer != -1 ) {
		delete_timer(sd->npc_idle_timer,npc_timeout_timer);
		sd->npc_idle_timer = -1;
	}
	return 0;
}

/*==========================================
 * ダイナミックNPCタイムアウト実行
 *------------------------------------------
 */
static int npc_dynamicnpc_timer(int tid,unsigned int tick,int id,void *data)
{
	struct map_session_data* sd = NULL;

	if((sd = map_id2sd(id)) == NULL || sd->npc_dynamic_id == 0) {
		if(sd) {
			sd->npc_dynamic_timer = -1;
		}
		return 0;
	}

	if(DIFF_TICK(tick, sd->npc_dynamic_tick) > (180*1000)) {
		// タイムアウトタイマーを止める
		if(sd->npc_id == sd->npc_dynamic_id) {
			npc_timeout_stop(sd);

			if(sd->stack) {
				// 元のスタック情報を破棄
				script_free_stack(sd->stack);
				sd->stack = NULL;
			}

			// menu, select, inputの返答待機解除（ギルド倉庫は応答を待つ）
			if(sd->state.menu_or_input == 1 && sd->state.gstorage_lockreq == 0)
				sd->state.menu_or_input = 0;

			// プログレスバーの応答待機解除
			if(sd->progressbar.tick) {
				sd->progressbar.npc_id = 0;
				sd->progressbar.tick   = 0;
			}
		}

		// ダイナミックNPCタイマーを止める
		clif_clearchar_id(sd->npc_dynamic_id, 0, sd->fd);
		sd->npc_dynamic_timer = -1;
		sd->npc_dynamic_id = 0;

	} else {
		sd->npc_dynamic_timer = add_timer(gettick()+1000,npc_dynamicnpc_timer,sd->bl.id,0);
	}

	return 0;
}

/*==========================================
 * ダイナミックNPCタイマー開始
 *------------------------------------------
 */
int npc_dynamicnpc_start(struct map_session_data *sd)
{
	unsigned int tick = gettick();

	nullpo_retr(0, sd);

	if( sd->npc_dynamic_timer == -1 )
		sd->npc_dynamic_timer = add_timer(tick+1000,npc_dynamicnpc_timer,sd->bl.id,0);
	sd->npc_dynamic_tick = tick;

	return 0;
}

/*==========================================
 * ダイナミックNPCタイマー終了
 *------------------------------------------
 */
int npc_dynamicnpc_stop(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	if( sd->npc_dynamic_timer != -1 ) {
		delete_timer(sd->npc_dynamic_timer,npc_dynamicnpc_timer);
		sd->npc_dynamic_timer = -1;
		if(sd->npc_dynamic_id) {
			clif_clearchar_id(sd->npc_dynamic_id, 0, sd->fd);
			sd->npc_dynamic_id = 0;
		}
	}
	return 0;
}

/*==========================================
 * イベント型のNPC処理
 *------------------------------------------
 */
int npc_event(struct map_session_data *sd,const char *eventname)
{
	struct event_data *ev;
	struct npc_data *nd;
	int xs, ys;

	nullpo_retr(1, sd);
	nullpo_retr(1, eventname);

	ev = (struct event_data *)strdb_search(ev_db,eventname);

	if (ev == NULL) {
		int len = (int)strlen(eventname) - 9;
		if (len >= 0 && strcmp(eventname + len, "::OnTouch") == 0)
			return 1;
	}
	if (ev == NULL || (nd = ev->nd) == NULL) {
		if (battle_config.error_log)
			printf("npc_event: event not found [%s]\n",eventname);
		return 1;
	}

	xs = nd->u.scr.xs;
	ys = nd->u.scr.ys;
	if (xs >= 0 && ys >= 0 ) {
		if ( nd->bl.m != sd->bl.m )
			return 1;
		if ( xs > 0 && (sd->bl.x < nd->bl.x-xs/2 || sd->bl.x > nd->bl.x+xs/2) )
			return 1;
		if ( ys > 0 && (sd->bl.y < nd->bl.y-ys/2 || sd->bl.y > nd->bl.y+ys/2) )
			return 1;
	}

	if ( sd->npc_id != 0 ) {
		int i;
		for(i=0; i<MAX_EVENTQUEUE; i++) {
			if (!sd->eventqueue[i][0])
				break;
		}
		if (i == MAX_EVENTQUEUE) {
			if (battle_config.error_log)
				printf("npc_event: event queue is full !\n");
		} else {
			strncpy(sd->eventqueue[i],eventname,50);
			sd->eventqueue[i][49] = '\0';	// force \0 terminal
		}
		return 1;
	}
	if (nd->flag&3) {	// 無効化されている
		npc_event_dequeue(sd);
		return 0;
	}

	run_script(nd->u.scr.script,ev->pos,sd->bl.id,nd->bl.id);
	return 0;
}

/*==========================================
 * 接触型のNPC処理
 *------------------------------------------
 */
int npc_touch_areanpc(struct map_session_data *sd,int m,int x,int y)
{
	int i, f = 1;
	int xs, ys;
	struct npc_data *nd = NULL;

	nullpo_retr(1, sd);

	if(sd->npc_id)
		return 1;

	for(i = 0; i < MAX_EVENTQUEUE; i++) {
		struct npc_data *nd = map_id2nd(sd->areanpc_id[i]);

		if (!nd || nd->subtype != SCRIPT ||
			!(nd->bl.m == m &&
				x >= nd->bl.x - nd->u.scr.xs/2 && x < nd->bl.x - nd->u.scr.xs/2 + nd->u.scr.xs &&
				y >= nd->bl.y - nd->u.scr.ys/2 && y < nd->bl.y - nd->u.scr.ys/2 + nd->u.scr.ys))
			sd->areanpc_id[i] = 0;
	}

	for(i = 0; i < map[m].npc_num; i++) {
		nd = map[m].npc[i];

		if(nd->flag&1) {	// 無効化されている
			f = 0;
			continue;
		}
		switch(nd->subtype) {
		case WARP:
			xs = nd->u.warp.xs;
			ys = nd->u.warp.ys;
			break;
		case SCRIPT:
			xs = nd->u.scr.xs;
			ys = nd->u.scr.ys;
			break;
		default:
			continue;
		}
		if(x >= nd->bl.x-xs/2 && x < nd->bl.x-xs/2+xs &&
		   y >= nd->bl.y-ys/2 && y < nd->bl.y-ys/2+ys) {
			f = 0;
			switch(nd->subtype) {
			case WARP:
				// 隠れているとワープできない
				if(pc_ishiding(sd))
					break;
				skill_stop_dancing(&sd->bl,0);
				pc_setpos(sd,nd->u.warp.name,nd->u.warp.x,nd->u.warp.y,0);
				break;
			case SCRIPT:
				if(sd->sc.data[SC_FORCEWALKING].timer == -1) {
					char name[50];
					int j, n = -1;
					for(j = 0; j < MAX_EVENTQUEUE; j++) {
						if(sd->areanpc_id[j] == 0)
							n = j;
						if(sd->areanpc_id[j] == nd->bl.id)
							break;
					}
					if(j == MAX_EVENTQUEUE && n >= 0) {
						sd->areanpc_id[n] = nd->bl.id;
						sprintf(name, "%s::OnTouch", nd->exname);
						if(npc_event(sd,name) > 0)
							npc_click(sd,nd->bl.id);
						break;
					}
				}
				break;
			}
		}
	}
//	if(i >= map[m].npc_num) {
		if(f) {
			if(battle_config.error_log)
				printf("npc_touch_areanpc : some bug \n");
			return 1;
		}
//	}

	return 0;
}

/*==========================================
 * 接触型のNPC処理(NPC用)
 *------------------------------------------
 */
int npc_touch_areanpc2(struct mob_data *md,int m,int x,int y)
{
	int i, id, xs, ys;
	struct npc_data *nd = NULL;

	nullpo_retr(1, md);

	for(i = 0; i < map[m].npc_num; i++) {
		nd = map[m].npc[i];

		if (nd->flag&1) {	// 無効化されている
			continue;
		}
		if(nd->subtype == SCRIPT) {
			xs = nd->u.scr.xs;
			ys = nd->u.scr.ys;
			if (x < nd->bl.x-xs/2 || x >= nd->bl.x-xs/2+xs ||
			    y < nd->bl.y-ys/2 || y >= nd->bl.y-ys/2+ys)
				continue;
			if(md->sc.data[SC_FORCEWALKING].timer == -1) {
				struct event_data *ev = NULL;
				char name[50];

				if(md->areanpc_id == nd->bl.id)
					return 1;
				sprintf(name, "%s::OnTouchNPC", nd->exname);
				ev = (struct event_data *)strdb_search(ev_db,name);
				if(ev == NULL || ev->nd == NULL)
					return 1;
				md->areanpc_id = nd->bl.id;
				id = md->bl.id;
				run_script(ev->nd->u.scr.script, ev->pos, md->bl.id, ev->nd->bl.id);
				if(map_id2md(id) == NULL)
					return 1;
			}
		}
	}
	return 0;
}

/*==========================================
 * 近くかどうかの判定
 *------------------------------------------
 */
static int npc_checknear(struct map_session_data *sd, struct npc_data *nd)
{
	nullpo_retr(1, sd);

	if (nd == NULL || nd->bl.type != BL_NPC) {
		printf("npc_checknear: npc not found!!\n");
		return 1;
	}

	if (nd->class_ < 0 || sd->npc_dynamic_id == nd->bl.id)	// イベント系は常にOK
		return 0;

	// エリア判定
	if (nd->bl.m != sd->bl.m ||
	    nd->bl.x < sd->bl.x-AREA_SIZE-1 || nd->bl.x > sd->bl.x+AREA_SIZE+1 ||
	    nd->bl.y < sd->bl.y-AREA_SIZE-1 || nd->bl.y > sd->bl.y+AREA_SIZE+1) {
		printf("npc_checknear: npc too far!! %s\n",nd->exname);
		return 1;
	}
	return 0;
}

/*==========================================
 * 近くかどうかの判定
 *------------------------------------------
 */
static int npc_isnear_sub(struct block_list *bl, va_list ap)
{
	struct npc_data *nd;

	nullpo_retr(0, bl);
	nullpo_retr(0, nd = (struct npc_data *)bl);

	if(nd->class_ < 0)	// イベント系は常にOK
		return 0;

	return 1;
}

bool npc_isnear(struct block_list *bl)
{
	int r;

	nullpo_retr(false, bl);

	r = battle_config.min_npc_vendchat_distance;

	// エリア判定
	if(r > 0 && map_foreachinarea(npc_isnear_sub,bl->m,bl->x-r,bl->y-r,bl->x+r,bl->y+r,BL_NPC) )
		return true;

	return false;
}

/*==========================================
 * NPCのオープンチャット発言
 *------------------------------------------
 */
int npc_globalmessage(const char *name,const char *mes)
{
	struct npc_data *nd = npc_name2id(name);
	char temp[100], *p;
	size_t len;

	if(!nd)
		return 0;

	strcpy(temp, nd->name);
	temp[sizeof(nd->name)] = 0;
	if((p = strchr(temp,'#')) != NULL)	// #以下の文字列は表示しない
		*p = 0;

	len = strlen(temp);
	snprintf(temp+len, sizeof(temp)-len, " : %s", mes);
	clif_GlobalMessage(&nd->bl,temp,AREA_CHAT_WOC);

	return 0;
}

/*==========================================
 * クリック時のNPC処理
 *------------------------------------------
 */
void npc_click(struct map_session_data *sd, int id)
{
	struct npc_data *nd;

	nullpo_retv(sd);

	if (sd->npc_id != 0) {
		if (battle_config.error_log)
			printf("npc_click: npc_id != 0\n");
		return;
	}

	nd = map_id2nd(id);
	if (npc_checknear(sd, nd)) // check NULL of nd and if nd->bl.type is BL_NPC
		return;

	if (nd->flag&1)	// 無効化されている
		return;

	sd->npc_allowuseitem = -1;

	switch(nd->subtype) {
	case SHOP:
		sd->npc_id = id;
		clif_npcbuysell(sd,id);
		npc_event_dequeue(sd);
		break;
	case POINTSHOP:
		sd->npc_id     = id;
		sd->npc_shopid = id;
		clif_pointshop_list(sd,nd);
		npc_event_dequeue(sd);
		break;
	case SCRIPT:
		if(nd->u.scr.script) {
			sd->npc_id = id;
			run_script(nd->u.scr.script,0,sd->bl.id,id);
		}
		break;
	}

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void npc_scriptcont(struct map_session_data *sd, int id)
{
	struct npc_data *nd;

	nullpo_retv(sd);

	if (id != sd->npc_id)
		return;

	nd = map_id2nd(id);
	if (npc_checknear(sd, nd)) // check NULL of nd and if nd->bl.type is BL_NPC
		return;

	sd->npc_idle_tick = gettick();

	run_script(nd->u.scr.script,sd->npc_pos,sd->bl.id,id);

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
void npc_buysellsel(struct map_session_data *sd, int id, unsigned char type)
{
	struct npc_data *nd;

	nullpo_retv(sd);

	nd = map_id2nd(id);
	if (npc_checknear(sd, nd)) // check NULL of nd and if nd->bl.type is BL_NPC
		return;

	if (nd->subtype != SHOP) {
		if (battle_config.error_log)
			printf("no such shop npc : %d\n",id);
		sd->npc_id = 0;
		return;
	}

	if (nd->flag&1)	// 無効化されている
		return;

	sd->npc_shopid = id;
	if (type == 0) {
		clif_buylist(sd,nd);
	} else {
		clif_selllist(sd);
	}

	return;
}

/*==========================================
 *
 *------------------------------------------
 */
// return value:
// 0: The deal has successfully completed., 1: You dont have enough zeny., 2: you are overcharged!, 3: You are over your weight limit.
int npc_buylist(struct map_session_data *sd,int n,unsigned short *item_list)
{
	struct npc_data *nd;
	double z;
	int i, j, w, new_add = 0;
	struct item_data *item_data;

	nullpo_retr(3, sd);
	nullpo_retr(3, item_list);

	nd = map_id2nd(sd->npc_shopid);
	if (npc_checknear(sd, nd)) // check NULL of nd and if nd->bl.type is BL_NPC
		return 3;

	if (nd->subtype != SHOP)
		return 3;

	w = 0;
	z = 0.;
	for(i = 0; i < n; i++) {
		int nameid, amount;
		amount = (int)item_list[i * 2];
		if (amount <= 0)
			return 3;
		nameid = (int)item_list[i * 2 + 1];
		if (nameid <= 0 || (item_data = itemdb_exists(nameid)) == NULL)
			return 3;

		for(j=0; nd->u.shop_item[j].nameid; j++) {
			int view_id = itemdb_viewid(nd->u.shop_item[j].nameid);
			if (view_id > 0) {
				if (view_id == nameid) {
					// 元のアイテムIDに置き換え
					item_list[i*2+1] = (unsigned short)nd->u.shop_item[j].nameid;
					break;
				}
			} else if (nd->u.shop_item[j].nameid == nameid) {
				break;
			}
		}
		if (nd->u.shop_item[j].nameid == 0)
			return 3;

		if (itemdb_isequip3(nameid) && amount > 1) {
			// Player sent a hexed packet trying to buy x of nonstackable item y!
			return 3;
		}

		if (item_data->flag.value_notdc)
			z += ((double)nd->u.shop_item[j].value * (double)amount);
		else
			z += ((double)pc_modifybuyvalue(sd, nd->u.shop_item[j].value) * (double)amount);
		if (z < 0. || z > (double)sd->status.zeny)
			return 1;

		switch(pc_checkadditem(sd, nameid, amount)) {
		case ADDITEM_EXIST:
			break;
		case ADDITEM_NEW:
			new_add++;
			break;
		case ADDITEM_OVERAMOUNT:
			return 2;
		}

		w += item_data->weight * amount;
		if (w + sd->weight > sd->max_weight)
			return 2;
	}

	if (pc_inventoryblank(sd) < new_add)
		return 3;	// 種類数超過

	pc_payzeny(sd,(int)z);

	for(i=0; i<n; i++) {
		struct item item_tmp;

		memset(&item_tmp,0,sizeof(item_tmp));
		item_tmp.nameid   = item_list[i*2+1];
		item_tmp.identify = 1;	// npc販売アイテムは鑑定済み

		pc_additem(sd,&item_tmp,item_list[i*2]);
	}

	// 商人経験値
	if (battle_config.shop_exp > 0 && z > 0.) {
		int skill = pc_checkskill(sd,MC_DISCOUNT);
		if (skill > 0) {
			if (sd->status.skill[MC_DISCOUNT].flag != 0)
				skill = sd->status.skill[MC_DISCOUNT].flag - 2;
			if (skill > 0) {
				z = (log(z * (double)skill) * (double)battle_config.shop_exp/100.);
				if (z < 1.)
					z = 1.;
				pc_gainexp(sd,NULL,0,(atn_bignumber)z,0);
			}
		}
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int npc_selllist(struct map_session_data *sd,int n,unsigned short *item_list)
{
	struct npc_data *nd;
	double z;
	int i, idx;
	struct item_data *item_data;
	struct item inventory[MAX_INVENTORY]; // too fix cumulativ selling (hack)

	nullpo_retr(1, sd);
	nullpo_retr(1, item_list);

	nd = map_id2nd(sd->npc_shopid);
	if (npc_checknear(sd, nd)) // check NULL of nd and if nd->bl.type is BL_NPC
		return 1;

	if (nd->subtype != SHOP)
		return 1;

	// get inventory of player
	memcpy(&inventory, &sd->status.inventory, sizeof(struct item) * MAX_INVENTORY);

	// do checks
	z = 0.;
	for(i = 0; i < n; i++) {
		int nameid, amount;
		idx = item_list[i * 2] - 2;
		if (idx < 0 || idx >= MAX_INVENTORY)
			return 1;
		amount = item_list[i * 2 + 1];
		if (amount <= 0 || inventory[idx].amount < amount)
			return 1;
		inventory[idx].amount = inventory[idx].amount - amount;
		nameid = inventory[idx].nameid;
		if (nameid <= 0 || (item_data = itemdb_exists(nameid)) == NULL)
			return 1;
		if (itemdb_issellable(nameid) == 0)
			return 1;
		if (item_data->value_sell < 0)
			return 1;
		if (item_data->flag.value_notoc)
			z += ((double)item_data->value_sell * (double)amount);
		else
			z += ((double)pc_modifysellvalue(sd, item_data->value_sell) * (double)amount);
		if (z < 0.)
			return 1;
		if (z > (double)MAX_ZENY - (double)sd->status.zeny) {
			return 1;
		}
	}

	// remove items and give zenys
	for(i=0; i<n; i++) {
		idx = item_list[i * 2] - 2;
		if (sd->inventory_data[idx] != NULL &&
		    sd->inventory_data[idx]->flag.pet_egg &&
		    sd->status.inventory[idx].card[0] == (short)0xff00 &&
		    pet_search_data(sd->status.inventory[idx].nameid, PET_EGG) != NULL)
		{
			intif_delete_petdata((*(int *)(&sd->status.inventory[idx].card[1])));
		}
		pc_delitem(sd, idx, item_list[i * 2 + 1], 0, 6);
	}
	pc_getzeny(sd, (int)z);

	// 商人経験値
	if (battle_config.shop_exp > 0 && z > 0.) {
		int skill = pc_checkskill(sd,MC_OVERCHARGE);
		if (skill > 0) {
			if (sd->status.skill[MC_OVERCHARGE].flag != 0)
				skill = sd->status.skill[MC_OVERCHARGE].flag - 2;
			if (skill > 0) {
				z = (log(z * (double)skill) * (double)battle_config.shop_exp/100.);
				if (z < 1.)
					z = 1.;
				pc_gainexp(sd,NULL,0,(atn_bignumber)z,0);
			}
		}
	}

	return 0;
}

/*==========================================
 * スペシャルアイテム購入
 *------------------------------------------
 */
int npc_pointshop_buy(struct map_session_data *sd, int nameid, int amount)
{
	struct npc_data *nd;
	struct item_data *item_data;
	struct item item_tmp;
	int i, point;

	nullpo_retr(1, sd);

	nd = map_id2nd(sd->npc_shopid);
	if(npc_checknear(sd, nd)) // check NULL of nd and if nd->bl.type is BL_NPC
		return 1;

	if(nd->subtype != POINTSHOP)
		return 1;

	if(sd->state.deal_mode != 0)
		return 4;

	if(nameid <= 0 || amount <= 0)
		return 5;

	for(i = 0; nd->u.shop_item[i].nameid; i++) {
		int view_id = itemdb_viewid(nd->u.shop_item[i].nameid);
		if(view_id > 0) {
			if(view_id == nameid) {
				break;
			}
		} else if(nd->u.shop_item[i].nameid == nameid) {
			break;
		}
	}
	if(nd->u.shop_item[i].nameid == 0 || (item_data = itemdb_exists(nd->u.shop_item[i].nameid)) == NULL)
		return 5;

	point = nd->u.shop_item[i].value * amount;
	if(point < 0 || point > sd->shop_point)
		return 6;

	switch(pc_checkadditem(sd, nameid, amount)) {
		case ADDITEM_EXIST:
			break;
		case ADDITEM_NEW:
			if(pc_inventoryblank(sd) < 1)
				return 3;
			break;
		case ADDITEM_OVERAMOUNT:
			return 3;
	}
	if(item_data->weight * amount + sd->weight > sd->max_weight)
		return 3;

	memset(&item_tmp, 0, sizeof(item_tmp));
	item_tmp.nameid   = nd->u.shop_item[i].nameid;
	item_tmp.identify = 1;	// npc販売アイテムは鑑定済み

	pc_additem(sd, &item_tmp, amount);
	sd->shop_point -= point;

	return 0;
}

/*==========================================
 * スペシャルアイテム購入複数
 *------------------------------------------
 */
int npc_pointshop_buylist(struct map_session_data *sd, int len, int count, const unsigned short *item_list)
{
	struct npc_data *nd;
	struct item_data *item_data;
	int i, j, blank;
	int point = 0, weight = 0, new_ = 0;

	nullpo_retr(1, sd);

	nd = map_id2nd(sd->npc_shopid);
	if(npc_checknear(sd, nd)) // check NULL of nd and if nd->bl.type is BL_NPC
		return 1;

	if(nd->subtype != POINTSHOP)
		return 1;

	if(sd->state.deal_mode != 0)
		return 4;

	if(len <= 0 || count <= 0)
		return 5;

	blank = pc_inventoryblank(sd);

	for(i = 0; i < count; i++) {
		const unsigned short nameid = item_list[i*2+1];
		const unsigned short amount = item_list[i*2+0];

		if(nameid == 0 || amount == 0)
			return 5;

		for(j = 0; nd->u.shop_item[j].nameid; j++) {
			int view_id = itemdb_viewid(nd->u.shop_item[j].nameid);
			if(view_id > 0) {
				if(view_id == nameid) {
					break;
				}
			} else if(nd->u.shop_item[j].nameid == nameid) {
				break;
			}
		}

		if((item_data = itemdb_exists(nd->u.shop_item[j].nameid)) == NULL)
			return 5;

		if (nd->u.shop_item[j].nameid == 0)
			return 3;

		if (itemdb_isequip3(nameid) && amount > 1) {
			// Player sent a hexed packet trying to buy x of nonstackable item y!
			return 3;
		}

		point += nd->u.shop_item[j].value * amount;
		if(point > sd->shop_point)
			return 6;

		switch(pc_checkadditem(sd, nameid, amount)) {
		case ADDITEM_EXIST:
			break;
		case ADDITEM_NEW:
			new_++;
			if (new_ > blank)
				return 3; // 種類数超過
			break;
		case ADDITEM_OVERAMOUNT:
			return 3; // アイテム数超過
		}

		weight += item_data->weight * amount;
		if(weight + sd->weight > sd->max_weight)
			return 2;
	}

	sd->shop_point -= point;

	for( i = 0; i < count; i++) {
		const unsigned short nameid = item_list[i*2+1];
		const unsigned short amount = item_list[i*2+0];
		struct item item_tmp;

		for(j = 0; nd->u.shop_item[j].nameid; j++) {
			int view_id = itemdb_viewid(nd->u.shop_item[j].nameid);
			if(view_id > 0) {
				if(view_id == nameid) {
					break;
				}
			} else if(nd->u.shop_item[j].nameid == nameid) {
				break;
			}
		}

		memset(&item_tmp, 0, sizeof(item_tmp));
		item_tmp.nameid   = nd->u.shop_item[j].nameid;
		item_tmp.identify = 1;	// npc販売アイテムは鑑定済み

		pc_additem(sd, &item_tmp, amount);
	}

	return 0;
}

/*==========================================
 * メモリアルダンジョンNPC追加
 *------------------------------------------
 */
int npc_addmdnpc(struct npc_data *src_nd, int m)
{
	struct npc_data *nd;
	char newname[24];

	nullpo_retr(0, src_nd);

	if(m < 0)
		return 0;

	snprintf(newname, sizeof(newname), "mdnpc_%03d_%d", map[m].memorial_id, src_nd->bl.id);
	if(npc_name2id(newname) != NULL) {
		printf("npc_addmdnpc: npc name \"%s\" is already, memorial_id: %d name: \"%s\"\n", newname, map[m].memorial_id, src_nd->exname);
		return 0;
	}

	nd = (struct npc_data *)aCalloc(1,sizeof(struct npc_data));
	strcpy(nd->name, src_nd->name);
	strcpy(nd->exname, newname);
	nd->name[23] = '\0';
	nd->exname[23] = '\0';

	nd->bl.prev = nd->bl.next = NULL;
	nd->bl.m    = m;
	nd->bl.x    = src_nd->bl.x;
	nd->bl.y    = src_nd->bl.y;
	nd->bl.id   = npc_get_new_npc_id();
	nd->dir     = src_nd->dir;
	nd->flag    = 0;
	nd->class_  = src_nd->class_;
	nd->speed   = 200;
	nd->chat_id = 0;
	nd->option  = OPTION_NOTHING;
	nd->bl.type = BL_NPC;
	nd->subtype = src_nd->subtype;

	switch(nd->subtype) {
	case SCRIPT:
		{
			struct script_code *code = NULL;
			if(src_nd->u.scr.script) {
				int script_size = src_nd->u.scr.script->script_size;
				code = (struct script_code *)aMalloc(sizeof(struct script_code) + script_size);
				code->script_vars = NULL;
				code->script_size = script_size;
				memcpy(code->script_buf, src_nd->u.scr.script->script_buf, script_size);
			}
			nd->u.scr.script         = code;
			nd->u.scr.xs             = src_nd->u.scr.xs;
			nd->u.scr.ys             = src_nd->u.scr.ys;
			nd->u.scr.label_list     = src_nd->u.scr.label_list;
			nd->u.scr.label_list_num = src_nd->u.scr.label_list_num;
			nd->u.scr.src_id         = src_nd->bl.id;
			nd->u.scr.timer_event    = NULL;
			nd->u.scr.timer          = -1;
			nd->u.scr.timerid        = -1;
			nd->u.scr.timeramount    = 0;
			nd->u.scr.nexttimer      = -1;
		}
		break;
	case SHOP:
	case POINTSHOP:
		{
			int pos = 0;
			while(src_nd->u.shop_item[pos++].nameid);
			nd = (struct npc_data *)aRealloc(nd, sizeof(struct npc_data) + sizeof(src_nd->u.shop_item[0]) * pos);
			memcpy(&nd->u.shop_item, &src_nd->u.shop_item, sizeof(src_nd->u.shop_item[0]) * pos);
		}
		break;
	case WARP:
		{
			int warp_m = memorial_mapname2mapid(src_nd->u.warp.name, map[m].memorial_id);
			nd->u.warp.xs = src_nd->u.warp.xs;
			nd->u.warp.ys = src_nd->u.warp.ys;
			nd->u.warp.x = src_nd->u.warp.x;
			nd->u.warp.y = src_nd->u.warp.y;
			if(warp_m < 0)
				memcpy(nd->u.warp.name, src_nd->u.warp.name, sizeof(nd->u.warp.name));
			else
				memcpy(nd->u.warp.name, map[warp_m].name, sizeof(nd->u.warp.name));
		}
		break;
	}

	if(m >= 0) {
		map_addblock(&nd->bl);
		if(nd->subtype == WARP || (nd->subtype == SCRIPT && nd->u.scr.xs > 0 && nd->u.scr.ys > 0))	// 接触型なので登録
			nd->n = map_addnpc(m,nd);
		else
			map_addiddb(&nd->bl);

		if(nd->class_ < 0) {	// イベント型
			struct event_data *ev, *old_ev;
			ev       = (struct event_data *)aCalloc(1,sizeof(struct event_data));
			ev->key  = NULL;
			ev->nd   = nd;
			ev->pos  = 0;
			ev->next = NULL;
			old_ev   = (struct event_data *)strdb_insert(ev_db,nd->exname,ev);
			if(old_ev) {
				// イベントが重複している場合。ここでreturnすると以前の処理が
				// 中途半端になる為、処理を続行する。
				printf("npc_parse_script : dup event name %s\n",nd->exname);
				aFree(old_ev);
			}
		} else {
			clif_spawnnpc(nd);
		}
	} else {
		map_addiddb(&nd->bl);
	}
	strdb_insert(npcname_db,nd->exname,nd);

	// イベント用ラベルデータのエクスポート
	if(nd->subtype == SCRIPT)
		npc_exportlabel_data(nd);

	return 1;
}

/*==========================================
 * NPC解放
 *------------------------------------------
 */
int npc_free(struct npc_data *nd)
{
	struct chat_data  *cd;
	struct event_data *ev;

	nullpo_retr(0, nd);

	// blocklistから消去
	if(nd->bl.prev) {
		map_delblock( &nd->bl );
		map_deliddb( &nd->bl );
	}

	// チャット消去
	if(nd->chat_id && (cd = map_id2cd(nd->chat_id))) {
		aFree(cd);
		cd = NULL;
	}

	if(nd->subtype == SCRIPT) {
		// タイマー解放
		if(nd->u.scr.timer_event)
			aFree(nd->u.scr.timer_event);
		// スクリプトコード解放
		if(nd->u.scr.script) {
			script_free_code(nd->u.scr.script);
			nd->u.scr.script = NULL;
		}
		// ラベルデータのイベント解放
		if(nd->u.scr.label_list) {
			int i;
			for(i = 0; i < nd->u.scr.label_list_num; i++) {
				char key[50];

				snprintf(key, 50, "%s::%s", nd->exname, nd->u.scr.label_list[i].name);
				ev = (struct event_data *)strdb_search(ev_db,key);
				if(ev) {
					strdb_erase(ev_db,key);

					// ノードのリンク変更
					if(ev->prev)
						ev->prev->next = ev->next;
					if(ev->next)
						ev->next->prev = ev->prev;

					aFree(ev->key);
					aFree(ev);
				}
			}
		}
		// ラベルデータ解放（元NPCのみ）
		if(nd->u.scr.src_id == 0) {
			aFree(nd->u.scr.label_list);
			nd->u.scr.label_list = NULL;
		}
	}

	// イベント型NPC
	if(nd->class_ < 0) {
		ev = (struct event_data *)strdb_search(ev_db,nd->exname);
		if(ev) {
			strdb_erase(ev_db,nd->exname);

			// ノードのリンク変更
			if(ev->prev)
				ev->prev->next = ev->next;
			if(ev->next)
				ev->next->prev = ev->prev;

			aFree(ev->key);
			aFree(ev);
		}
	}

	strdb_erase(npcname_db,nd->exname);

	map_deliddb(&nd->bl);
	map_freeblock(nd);

	return 1;
}

//
// 初期化関係
//

/*==========================================
 * 読み込むnpcファイルのクリア
 *------------------------------------------
 */
static void npc_clearsrcfile(void)
{
	struct npc_src_list *node, *node2;

	node = npc_src_first;
	while( node ) {
		node2 = node->next;
		aFree( node );
		node = node2;
	}
	npc_src_first = NULL;
	npc_src_last  = NULL;
}

/*==========================================
 * 読み込むnpcファイルの追加
 *------------------------------------------
 */
void npc_addsrcfile(const char *name)
{
	struct npc_src_list *node;

	if(strcmpi(name,"clear") == 0) {
		npc_clearsrcfile();
		return;
	}

	node = (struct npc_src_list *)aCalloc(1,sizeof(struct npc_src_list) + strlen(name));
	strncpy(node->name, name, strlen(name)+1);

	if(npc_src_first == NULL) {
		node->prev = NULL;
		npc_src_first = node;
	}
	if(npc_src_last) {
		node->prev = npc_src_last;
		npc_src_last->next = node;
	}

	node->next = NULL;
	npc_src_last = node;
}

/*==========================================
 * 読み込むnpcファイルの削除
 *------------------------------------------
 */
void npc_delsrcfile(const char *name)
{
	struct npc_src_list *node, *node2;

	if(strcmpi(name,"all") == 0) {
		npc_clearsrcfile();
		return;
	}

	// 重複したファイルがあるので全ループ
	node = npc_src_first;
	while( node ) {
		node2 = node->next;
		if(strcmp(node->name,name) == 0) {
			if(node->prev == NULL)
				npc_src_first = node->next;
			else
				node->prev->next = node->next;
			if(node->next == NULL)
				npc_src_last = node->prev;
			else
				node->next->prev = node->prev;
			aFree( node );
		}
		node = node2;
	}
}

/*==========================================
 * npcファイル行の読み飛ばし
 *------------------------------------------
 */
static char *npc_skip_line(unsigned char *p, int *comment_flag)
{
	while(isspace(*p))
		p++;

	if(p[0] == '/' && p[1] == '*') {
		p += 2;
		*comment_flag = 1;
	}

	if(p[0] == '\0') {
		p = NULL;
	}
	else if(*comment_flag) {
		while (*p) {
			if(p[0] == '*' && p[1] == '/') {
				p += 2;
				*comment_flag = 0;
				break;
			}
			p++;
		}
		return npc_skip_line(p, comment_flag);
	}
	else if(p[0] == '/' && p[1] == '/') {
		p = NULL;
	}
	return p;
}

/*==========================================
 * warp行解析
 *------------------------------------------
 */
static int npc_parse_warp(const char *w1,const char *w2,const char *w3,const char *w4,int lines)
{
	int m, x, y, dir = 0, xs, ys, to_x, to_y;
	int i, j, n;
	char mapname[4096], to_mapname[4096];
	char *p;
	struct npc_data *nd;

	// 引数の個数チェック
	// dirはあってもなくても良い
	if(sscanf(w1,"%4095[^,],%d,%d%n",mapname,&x,&y,&n) != 3 ||
	   (w1[n] != 0 && (sscanf(w1+n,",%d%n",&dir,&i) != 1 || w1[n+i] != 0)) ||
	   sscanf(w4,"%d,%d,%4095[^,],%d,%d%n",&xs,&ys,to_mapname,&to_x,&to_y,&n) != 5 || w4[n] != 0)
	{
		printf("bad warp declaration : %s line %d\a\n",w3,lines);
		return 0;
	}

	m = map_mapname2mapid(mapname);
	if(m < 0)
		return 0;	// assignされてないMAPなので終了

	nd = (struct npc_data *)aCalloc(1,sizeof(struct npc_data));
	nd->bl.id = npc_get_new_npc_id();
	nd->n     = map_addnpc(m,nd);

	nd->bl.prev = nd->bl.next = NULL;
	nd->bl.m = m;
	nd->bl.x = x;
	nd->bl.y = y;
	nd->dir  = dir;
	nd->flag = 0;

	p = strstr(w3,"::");
	if(p) {
		char *p2;
		*p = 0;
		p += 2;
		if((p2 = strstr(p,"::")) != NULL) {
			*p2 = 0;
		}
		strncpy(nd->name,w3,24);
		strncpy(nd->exname,p,24);
	} else {
		strncpy(nd->name,w3,24);
		strncpy(nd->exname,w3,24);
	}
	nd->name[23]   = '\0';
	nd->exname[23] = '\0';

	nd->chat_id = 0;
	if (!battle_config.warp_point_debug)
		nd->class_ = WARP_CLASS;
	else
		nd->class_ = WARP_DEBUG_CLASS;
	nd->speed  = 200;
	nd->option = OPTION_NOTHING;
	memcpy(nd->u.warp.name,to_mapname,16);
	nd->u.warp.name[15] = '\0';	// force \0 terminal
	xs += 2;
	ys += 2;
	nd->u.warp.x  = to_x;
	nd->u.warp.y  = to_y;
	nd->u.warp.xs = xs;
	nd->u.warp.ys = ys;

	for(i=0; i<ys; i++) {
		for(j=0; j<xs; j++) {
//			if(map_getcell(m,x-xs/2+j,y-ys/2+i,CELL_CHKNOPASS))
//				continue;
			map_setcell(m,x-xs/2+j,y-ys/2+i,CELL_SETNPC);
		}
	}

	npc_warp++;
	nd->bl.type = BL_NPC;
	nd->subtype = WARP;
	map_addblock(&nd->bl);
	clif_spawnnpc(nd);
	strdb_insert(npcname_db,nd->exname,nd);

	//printf("warp npc %s %d read done\n",mapname,nd->bl.id);

	return 0;
}

/*==========================================
 * shop行解析
 *------------------------------------------
 */
static int npc_parse_shop(const char *w1,const char *w2,const char *w3,const char *w4,int lines)
{
	char *p;
	int m, x, y, dir = 0;
	int n, pos = 0;
	unsigned char subtype;
	struct npc_data *nd;

	if(strcmp(w2,"shop") == 0)
		subtype = SHOP;
	else if(strcmp(w2,"pointshop") == 0)
		subtype = POINTSHOP;
	else
		subtype = 0;

	if(strcmp(w1,"-") == 0) {
		x = 0;
		y = 0;
		m = -1;
	} else {
		char mapname[4096];

		// 引数の個数チェック
		if(sscanf(w1, "%4095[^,],%d,%d,%d%n", mapname, &x, &y, &dir, &n) != 4 || w1[n] != 0 ||
		   (subtype != 0 && strchr(w4,',') == NULL))
		{
			printf("bad shop declaration : %s line %d\a\n", w3, lines);
			return 0;
		}
		m = map_mapname2mapid(mapname);
		if(m < 0)
			return 0;	// assignされてないMAPなので終了
	}

	if(subtype == SHOP || subtype == POINTSHOP) {
		const int max = 100;
		char *c;

		nd = (struct npc_data *)aCalloc(1, sizeof(struct npc_data) + sizeof(nd->u.shop_item[0]) * (max + 1));
		c = strchr(w4, ',');
		while(c && pos < max) {
			struct item_data *id = NULL;
			int ret, nameid, value = -1;
			c++;
			ret = sscanf(c, "%d:%d", &nameid, &value);
			if(ret < 1 || (subtype == POINTSHOP && ret < 2)) {
				char *np = strchr(c, ',');
				if(np) {
					np[1] = 0;
				}
				printf("bad %s item %s : %s line %d\a\n", w2, c, w3, lines);
				pos = 0;
				break;
			}
			id = itemdb_search(nameid);
			nd->u.shop_item[pos].nameid = nameid;
			if(subtype == SHOP) {
				int sell_max, buy_max;
				if(value < 0) {
					value = id->value_buy;
				}
				if(id->flag.value_notoc)	//NOTOCフラグを判定
					sell_max = id->value_sell;
				else
					sell_max = pc_modifysellvalue(NULL, id->value_sell);

				if(id->flag.value_notdc)	//NOTDCフラグを判定
					buy_max  = value;
				else
					buy_max  = pc_modifybuyvalue(NULL, value);

				if(sell_max > buy_max) {
					// 売り値が買い値を越える可能性があるので警告
					printf("warning shop sell value (id = %d, %dz > %dz) : %s line %d\a\n", nameid, sell_max, buy_max, w3, lines);
				}
			}
			nd->u.shop_item[pos].value = value;
			pos++;
			c = strchr(c,',');
		}
		if(pos == 0) {
			aFree(nd);
			return 0;
		}
		nd->u.shop_item[pos++].nameid = 0;

		nd = (struct npc_data *)aRealloc(nd, sizeof(struct npc_data) + sizeof(nd->u.shop_item[0]) * pos);
	} else {
		// substoreはコピーするだけ
		char srcname[4096];
		struct npc_data *nd2;

		if(sscanf(w2,"substore(%4095[^)])%n",srcname,&n) != 1 || w2[n] != 0) {
			printf("bad substore name! : %s line %d\a\n",w2,lines);
			return 0;
		}
		nd2 = npc_name2id(srcname);
		if(nd2 == NULL) {
			printf("bad substore name! (not exist) : %s line %d\a\n",srcname,lines);
			return 0;
		}
		if(nd2->subtype != SHOP && nd2->subtype != POINTSHOP) {
			printf("bad substore name! (not shop) : %s line %d\a\n",srcname,lines);
			return 0;
		}
		subtype = nd2->subtype;
		while(nd2->u.shop_item[pos++].nameid);

		nd = (struct npc_data *)aCalloc(1, sizeof(struct npc_data) + sizeof(nd2->u.shop_item[0]) * pos);
		memcpy(&nd->u.shop_item, &nd2->u.shop_item, sizeof(nd2->u.shop_item[0]) * pos);
	}

	nd->bl.prev = nd->bl.next = NULL;
	nd->bl.m  = m;
	nd->bl.x  = x;
	nd->bl.y  = y;
	nd->bl.id = npc_get_new_npc_id();
	nd->dir   = dir;
	nd->flag  = 0;

	p = strstr(w3,"::");
	if(p) {
		char *p2;
		*p = 0;
		p += 2;
		if((p2 = strstr(p,"::")) != NULL) {
			*p2 = 0;
		}
		strncpy(nd->name,w3,24);
		strncpy(nd->exname,p,24);
	} else {
		strncpy(nd->name,w3,24);
		strncpy(nd->exname,w3,24);
	}
	nd->name[23]   = '\0';
	nd->exname[23] = '\0';

	nd->class_  = atoi(w4);
	nd->speed   = 200;
	nd->chat_id = 0;
	nd->option  = OPTION_NOTHING;
	npc_shop++;
	nd->bl.type = BL_NPC;
	nd->subtype = subtype;
	map_addiddb(&nd->bl);

	if(m >= 0) {
		map_addblock(&nd->bl);
		clif_spawnnpc(nd);
	}
	strdb_insert(npcname_db,nd->exname,nd);

	//printf("shop npc %s %d read done\n",mapname,nd->bl.id);

	return 0;
}

/*==========================================
 * NPCのラベルデータコンバート
 *------------------------------------------
 */
static int npc_convertlabel_db(struct npc_data *nd)
{
	struct npc_label_list *lst;
	struct linkdb_node *node;
	int num = 0, i = 0;

	nullpo_retr(0, nd);

	node = scriptlabel_db;
	if(node == NULL)
		return 0;

	while(node) {
		num++;
		node = node->next;
	}
	lst = (struct npc_label_list *)aCalloc(num, sizeof(struct npc_label_list));

	node = scriptlabel_db;
	while(node) {
		unsigned char *p = (unsigned char *)node->key;
		unsigned char c;

		while( isalnum(*p) || *p == '_' ) {
			p++;
		}
		c = *p;
		*p = '\0';
		strncpy(lst[i].name, (char *)node->key, 24);
		lst[i].name[23] = '\0';	// force \0 terminal
		*p = c;
		lst[i].pos = PTR2INT(node->data);
		i++;
		node = node->next;
	}

	nd->u.scr.label_list     = lst;
	nd->u.scr.label_list_num = num;

	// もう要らなくなったので解放
	linkdb_final(&scriptlabel_db);

	return 0;
}

/*==========================================
 * NPCのラベルデータエクスポート
 *------------------------------------------
 */
static int npc_exportlabel_data(struct npc_data *nd)
{
	int i, t, n;

	nullpo_retr(1, nd);

	for(i = 0; i < nd->u.scr.label_list_num; i++) {
		struct event_data *ev;
		const char *lname = nd->u.scr.label_list[i].name;
		int pos = nd->u.scr.label_list[i].pos;

		// エクスポートされる
		ev       = (struct event_data *)aCalloc(1,sizeof(struct event_data));
		ev->key  = (char *)aCalloc(50,sizeof(char));
		ev->nd   = nd;
		ev->pos  = pos;
		ev->next = NULL;
		snprintf(ev->key, 50, "%s::%s", nd->exname, lname);
		if(strdb_search(ev_db,ev->key)) {
			printf("npc_exportlabel_data : dup event %s\n",ev->key);
			aFree(ev->key);
			aFree(ev);
			return 1;
		}
		strdb_insert(ev_db,ev->key,ev);

		if(strncmp(lname, "OnTimer", 7) != 0) {
			// タイマー以外はdoall用にラベルリストを作る
			struct event_data *node;
			char buf[32] = "::";

			strcat(buf,lname);
			node = (struct event_data *)strdb_search(ev_db,buf);
			if(node == NULL) {
				// 登録されてないラベルなので新規作成する
				node       = (struct event_data *)aCalloc(1,sizeof(struct event_data));
				node->key  = (char *)aCalloc(50,sizeof(char));
				node->nd   = NULL;
				node->pos  = -1;
				node->next = NULL;
				strncpy(node->key, buf, strlen(buf)+1);
				strdb_insert(ev_db,node->key,node);
			}
			// リストの末尾に連結
			while(node->next) {
				node = node->next;
			}
			node->next = ev;
			ev->prev = node;
		}
		else if(sscanf(lname,"OnTimer%d%n",&t,&n) == 1 && lname[n] == '\0') {
			// タイマーイベント
			struct npc_timerevent_list *te = nd->u.scr.timer_event;
			int j, k = nd->u.scr.timeramount;

			if(te == NULL)
				te = (struct npc_timerevent_list *)aCalloc(1,sizeof(struct npc_timerevent_list));
			else
				te = (struct npc_timerevent_list *)aRealloc(te,sizeof(struct npc_timerevent_list)*(k+1));
			for(j = 0; j < k; j++) {
				if(te[j].timer > t) {
					memmove(te+j+1,te+j,sizeof(struct npc_timerevent_list)*(k-j));
					break;
				}
			}
			te[j].timer = t;
			te[j].pos   = pos;
			nd->u.scr.timer_event = te;
			nd->u.scr.timeramount = k+1;
		}
		else {
			printf("npc_exportlabel_data : invalid OnTimer label %s\n", lname);
			return 1;
		}
	}

	return 0;
}

/*==========================================
 * script行解析
 *------------------------------------------
 */
static int npc_parse_script(const char *w1,const char *w2,const char *w3,const char *w4,const char *first_line,FILE *fp,int *lines,const char* file)
{
	int x, y, m, xs, ys;
	int dir = 0, class_ = 0, label_dupnum = 0, src_id = 0, fail = 0;
	char *p, *srcbuf = NULL;
	struct script_code *script;
	struct npc_data *nd;
	struct npc_label_list *label_dup = NULL;

	if(strcmp(w1,"-") == 0) {
		x = 0;
		y = 0;
		m = -1;
	} else {
		// 引数の個数チェック
		char mapname[4096];
		int n;

		if(sscanf(w1,"%4095[^,],%d,%d,%d%n",mapname,&x,&y,&dir,&n) != 4 || w1[n] != 0 ||
		   (strcmp(w2,"script") == 0 && strchr(w4,',') == NULL))
		{
			printf("bad script declaration : %s line %d\a\n",w3,*lines);
			return 0;
		}
		m = map_mapname2mapid(mapname);
	}

	if(strcmp(w2,"script") == 0) {
		// スクリプトの解析
		// { , } の入れ子許したらこっちでも簡易解析しないといけなくなったりもする
		size_t len, srclen;
		size_t srcsize = 32768;
		int curly_count = 0, startline = 0;
		char line[4096];

		srcbuf = (char *)aMalloc(srcsize);
		srcbuf[0] = 0;
		p = strchr(first_line, '{');
		if(p) {
			strcpy(srcbuf, p);
			startline = *lines;
		}
		if( !parse_script_line_curly(srcbuf, &curly_count, *lines) ) {
			aFree(srcbuf);
			return 1;
		}
		srclen = strlen(srcbuf);

		while(curly_count > 0) {
			// line の中に文字列 , {} が含まれているか調査
			if(!fgets(line, sizeof(line), fp))
				break;
			(*lines)++;
			if( !parse_script_line_curly(line, &curly_count, *lines) ) {
				aFree(srcbuf);
				return 1;
			}
			len = strlen(line);
			if(srclen + len + 1 >= srcsize) {
				srcsize += 65536;
				srcbuf = (char *)aRealloc(srcbuf, srcsize);
			}
			if(srcbuf[0] != '{') {
				p = strchr(line, '{');
				if(p) {
					strcpy(srcbuf, p);
					startline = *lines;
				}
				srclen = strlen(srcbuf);
			} else {
				strcpy(srcbuf + srclen, line);
				srclen += len;
			}
		}
		if(curly_count > 0) {
			script_error( srcbuf, file, startline, "missing right curly", srcbuf + strlen(srcbuf) );
			aFree(srcbuf);
			return 1;
		}
		if(strcmp(w1,"-") != 0 && m < 0) {	// assignされてないMAPなのでparseせずに終了
			aFree(srcbuf);
			return 0;
		}

		script = parse_script(srcbuf, file, startline);
		if(script_is_error(script)) {
			// script parse error
			aFree(srcbuf);
			return 0;
		}
	} else {
		// duplicateする
		char srcname[4096];
		struct npc_data *nd2;
		int n;

		if(sscanf(w2,"duplicate(%4095[^)])%n",srcname,&n) != 1 || w2[n] != 0) {
			printf("bad duplicate name! : %s line %d\a\n",w2,*lines);
			return 0;
		}
		if(strcmp(w1,"-") != 0 && m < 0) {	// assignされてないMAPなので終了
			return 0;
		}
		nd2 = npc_name2id(srcname);
		if(nd2 == NULL) {
			printf("bad duplicate name! (not exist) : %s line %d\a\n",srcname,*lines);
			return 0;
		}
		if(nd2->subtype != SCRIPT) {
			printf("bad duplicate name! (not script) : %s line %d\a\n",srcname,*lines);
			return 0;
		}
		script       = nd2->u.scr.script;
		label_dup    = nd2->u.scr.label_list;
		label_dupnum = nd2->u.scr.label_list_num;
		src_id       = nd2->bl.id;
	}
	// end of スクリプト解析

	nd = (struct npc_data *)aCalloc(1,sizeof(struct npc_data));
	nd->u.scr.xs = 0;
	nd->u.scr.ys = 0;

	if(m == -1) {
		// スクリプトコピー用のダミーNPC
	} else if(sscanf(w4,"%d,%d,%d",&class_,&xs,&ys) == 3) {
		// 接触型NPC
		if(xs >= 0) xs = xs * 2 + 1;
		if(ys >= 0) ys = ys * 2 + 1;

		if(class_ >= 0) {
			int i, j;
			for(i=0; i<ys; i++) {
				for(j=0; j<xs; j++) {
					if(map_getcell(m,x-xs/2+j,y-ys/2+i,CELL_CHKNOPASS))
						continue;
					map_setcell(m,x-xs/2+j,y-ys/2+i,CELL_SETNPC);
				}
			}
		}
		nd->u.scr.xs = xs;
		nd->u.scr.ys = ys;
	} else {
		// クリック型NPC
		class_ = atoi(w4);
	}

	p = strstr(w3,"::");
	if(p) {
		char *p2;
		*p = 0;
		p += 2;
		if((p2 = strstr(p,"::")) != NULL) {
			*p2 = 0;
		}
		strncpy(nd->name,w3,24);
		strncpy(nd->exname,p,24);
	} else {
		strncpy(nd->name,w3,24);
		strncpy(nd->exname,w3,24);
	}
	nd->name[23]   = '\0';
	nd->exname[23] = '\0';

	nd->bl.prev = nd->bl.next = NULL;
	nd->bl.m    = m;
	nd->bl.x    = x;
	nd->bl.y    = y;
	nd->bl.id   = npc_get_new_npc_id();
	nd->dir     = dir;
	nd->flag    = 0;
	nd->class_  = class_;
	nd->speed   = 200;
	nd->u.scr.script = script;
	nd->u.scr.src_id = src_id;
	nd->chat_id = 0;
	nd->option  = OPTION_NOTHING;

	npc_script++;
	nd->bl.type = BL_NPC;
	nd->subtype = SCRIPT;

	//printf("script npc %s %d %d read done\n",mapname,nd->bl.id,nd->class_);

	if(m >= 0) {
		map_addblock(&nd->bl);
		if(nd->u.scr.xs > 0 && nd->u.scr.ys > 0)	// 接触型なので登録
			nd->n = map_addnpc(m,nd);
		else
			map_addiddb(&nd->bl);

		if(class_ < 0) {	// イベント型
			struct event_data *ev, *old_ev;
			ev       = (struct event_data *)aCalloc(1,sizeof(struct event_data));
			ev->key  = NULL;
			ev->nd   = nd;
			ev->pos  = 0;
			ev->next = NULL;
			old_ev   = (struct event_data *)strdb_insert(ev_db,nd->exname,ev);
			if(old_ev) {
				// イベントが重複している場合。ここでreturnすると以前の処理が
				// 中途半端になる為、処理を続行する。
				printf("npc_parse_script : dup event name %s\n",nd->exname);
				aFree(old_ev);
				fail = 1;
			}
		} else {
			clif_spawnnpc(nd);
		}
	} else {
		map_addiddb(&nd->bl);
	}
	strdb_insert(npcname_db,nd->exname,nd);

	// ラベルデータの準備
	if(srcbuf) {
		// script本体がある場合の処理
		if(script) {
			// コードがあるならラベルデータをコンバート
			npc_convertlabel_db(nd);
		}
		aFree(srcbuf);	// もう使わないのでバッファ解放
	} else {
		// duplicate
		nd->u.scr.label_list     = label_dup;	// ラベルデータ共有
		nd->u.scr.label_list_num = label_dupnum;
	}

	// イベント用ラベルデータのエクスポート
	if(fail == 0)
		fail = npc_exportlabel_data(nd);

	nd->u.scr.nexttimer = -1;
	nd->u.scr.timerid   = -1;

	if(fail) {
		// データを正常に復帰できないのでサーバ終了
		exit(1);
	}

	return 0;
}

/*==========================================
 * function行解析
 *------------------------------------------
 */
static int npc_parse_function(const char *w1,const char *w2,const char *w3,const char *w4,const char *first_line,FILE *fp,int *lines,const char* file)
{
	size_t len, srclen;
	size_t srcsize = 32768;
	char *p, *srcbuf = NULL;
	struct script_code *script;
	int curly_count = 0, startline = 0;
	char line[4096];

	// スクリプトの解析
	srcbuf = (char *)aMalloc(srcsize);
	srcbuf[0] = 0;
	p = strchr(first_line, '{');
	if(p) {
		strcpy(srcbuf, p);
		startline = *lines;
	}
	if( !parse_script_line_curly(srcbuf, &curly_count, *lines) ) {
		aFree(srcbuf);
		return 1;
	}
	srclen = strlen(srcbuf);

	while(curly_count > 0) {
		if(!fgets(line,sizeof(line),fp))
			break;
		(*lines)++;
		if( !parse_script_line_curly(line, &curly_count, *lines) ) {
			aFree(srcbuf);
			return 1;
		}
		len = strlen(line);
		if(srclen + len + 1 >= srcsize) {
			srcsize += 65536;
			srcbuf = (char *)aRealloc(srcbuf, srcsize);
		}
		if(srcbuf[0] != '{') {
			p = strchr(line, '{');
			if(p) {
				strcpy(srcbuf, p);
				startline = *lines;
			}
			srclen = strlen(srcbuf);
		} else {
			strcpy(srcbuf + srclen, line);
			srclen += len;
		}
	}
	if(curly_count > 0) {
		script_error( srcbuf, file, startline, "missing right curly", srcbuf + strlen(srcbuf) );
		aFree(srcbuf);
		return 1;
	}
	script = parse_script(srcbuf,file,startline);

	// もう使わないのでバッファ解放
	aFree(srcbuf);

	if(script_is_error(script)) {
		// script parse error
		return 0;
	}
	if(script == NULL) {
		// コードを持たないfunctionは不正と見なして登録しない
		printf("npc_parse_function : nothing function %s\a\n",w3);
		return 0;
	}
	if(script_get_userfunc(w3) != NULL) {
		printf("npc_parse_function : dup function name %s\a\n",w3);
		script_free_code(script);
		return 0;
	}

	p = (char *)aCalloc(50,sizeof(char));
	strncpy(p,w3,49);
	script_set_userfunc(p, script);

	return 0;
}

/*==========================================
 * mob行解析
 *------------------------------------------
 */
static int npc_parse_mob(const char *w1,const char *w2,const char *w3,const char *w4,int lines)
{
	int m, x, y, xs, ys, class_, num, delay1, delay2;
	int i, n, guild_id = 0;
	char mapname[24];
	char eventname[4096] = "";
	char eventtemp[4096] = "";
	struct mob_data *md;
	struct mobdb_data *id;

	// 引数の個数チェック
	if(sscanf(w1,"%23[^,],%d,%d,%d,%d%n",mapname,&x,&y,&xs,&ys,&n) != 5 || w1[n] != 0 ||
	   sscanf(w4,"%d,%d,%d,%d,%4095[^\n]",&class_,&num,&delay1,&delay2,eventtemp) < 4)
	{
		printf("bad monster declaration : %s line %d\a\n",w3,lines);
		return 0;
	}
	m = map_mapname2mapid(mapname);
	if(m < 0)
		return 0;	// assignされてないMAPなので終了

	if(!mobdb_exists(class_)) {
		// 定期沸きでID異常は注意を促す
		printf("npc_monster bad class: %d line %d\a\n",class_,lines);
		return 0;
	}

	id = mobdb_search(class_);

	if(eventtemp[0]) {
		char *p;
		// ,,<guild_id> のようにイベント指定無しのパターンがあるのでsscanfしない
		if((p = strchr(eventtemp,',')) != NULL) {
			*p = 0;
			guild_id = atoi(p+1);
		}
		p = eventtemp;
		if(*p) {
			if(isdigit((unsigned char)p[0]) && p[1] == 0) {
				// 数字1文字だけの場合はイベント指定無しとして扱う（何もしない）
				;
			} else {
				strncpy(eventname,p,50);
			}
		}
	}
	if(num > 1 && battle_config.mob_count_rate != 100) {
		if((num = num * battle_config.mob_count_rate / 100) < 1)
			num = 1;
	}

	if(id->mode & MD_BOSS) {
		if(id->mexp > 0) {
			if(battle_config.mob_mvp_boss_delay_rate != 100) {
				delay1 = delay1 * battle_config.mob_mvp_boss_delay_rate / 100;
				delay2 = delay2 * battle_config.mob_mvp_boss_delay_rate / 100;
			}
		} else {
			if(battle_config.mob_middle_boss_delay_rate != 100) {
				delay1 = delay1 * battle_config.mob_middle_boss_delay_rate / 100;
				delay2 = delay2 * battle_config.mob_middle_boss_delay_rate / 100;
			}
		}
	} else {
		if(battle_config.mob_delay_rate != 100) {
			delay1 = delay1 * battle_config.mob_delay_rate / 100;
			delay2 = delay2 * battle_config.mob_delay_rate / 100;
		}
	}

	if(delay1 < 0) delay1 = 0;
	if(delay2 < 0) delay2 = 0;

	for(i=0; i<num; i++) {
		md = (struct mob_data *)aCalloc(1,sizeof(struct mob_data));

		md->bl.prev = NULL;
		md->bl.next = NULL;
		md->bl.m = m;
		md->bl.x = x;
		md->bl.y = y;

		if(strcmp(w3,"--en--") == 0) {
			memcpy(md->name,id->name,24);
		} else if(strcmp(w3,"--ja--") == 0) {
			memcpy(md->name,id->jname,24);
		} else {
			memcpy(md->name,w3,24);
			md->name[23] = '\0';
		}

		md->n           = i;
		md->base_class  = class_;
		md->class_      = class_;
		md->bl.id       = npc_get_new_npc_id();
		md->m           = m;
		md->x0          = x;
		md->y0          = y;
		md->xs          = xs;
		md->ys          = ys;
		md->spawndelay1 = delay1;
		md->spawndelay2 = delay2;

		memset(&md->state,0,sizeof(md->state));
		md->target_id   = 0;
		md->attacked_id = 0;
		md->speed       = id->speed;

		if(id->mode & MD_ITEMLOOT)
			md->lootitem = (struct item *)aCalloc(LOOTITEM_SIZE,sizeof(struct item));
		else
			md->lootitem = NULL;

		if(eventname[0]) {
			memcpy(md->npc_event,eventname,50);
			md->npc_event[49] = '\0';	// froce \0 terminal
		}
		md->bl.type = BL_MOB;
		map_addiddb(&md->bl);

		if(mob_spawn(md->bl.id)) {
			// 出現失敗、座標が指定されているなら周囲のセルをチェック
			if(md->x0 != 0 && md->y0 != 0) {
				int x0 = md->x0 - md->xs;
				int y0 = md->y0 - md->ys;
				int x1 = md->x0 + md->xs;
				int y1 = md->y0 + md->ys;

				if(map_searchfreecell(NULL, md->m, x0, y0, x1, y1) <= 0) {
					// 侵入可能セルが全くないので削除する
					printf("npc_monster spawn stacked (%d,%d) - (%d,%d) line %d\a\n", x0, y0, x1, y1, lines);
					map_deliddb(&md->bl);
					if(md->lootitem) {
						aFree(md->lootitem);
						md->lootitem = NULL;
					}
					map_freeblock(md);
					break;
				}
			}
		}
		if(id->mexp > 0) {
			if(!(md->spawndelay1 == -1 && md->spawndelay2 == -1 && md->n == 0)) {
				// 再出現するMVPボスなら凸面鏡用に登録
				map[md->bl.m].mvpboss = md;
			}
		}

		if(guild_id > 0)
			md->guild_id = guild_id;
		npc_mob++;
	}
	//printf("mob npc %s %d read done\n",mapname,nd->bl.id);

	return 0;
}

/*==========================================
 * マップフラグ行の解析
 *------------------------------------------
 */
static int npc_parse_mapflag(const char *w1,const char *w2,const char *w3,const char *w4,int lines)
{
	int m;
	char mapname[4096];

	// 引数の個数チェック
	if(sscanf(w1,"%4095[^,]",mapname) != 1 || strlen(w1) != strlen(mapname)) {
		printf("bad mapflag declaration : %s line %d\a\n",w3,lines);
		return 0;
	}

	m = map_mapname2mapid(mapname);
	if(m < 0)
		return 0;	// assignされてないMAPなので終了

	if(npc_set_mapflag(m, w3, w4) < 0) {
		printf("npc_parse_mapflag: mapflag \"%s\" not exist!! line %d\a\n",w3,lines);
	}
	return 0;
}

/*==========================================
 * マップフラグの設定
 *------------------------------------------
 */
int npc_set_mapflag(int m,const char *w3,const char *w4)
{
	if(m < 0 || m >= map_num)
		return 0;

	if (strcmpi(w3,"nosave") == 0) {
		char savemap[4096];
		int savex, savey;
		if (strcmp(w4,"SavePoint") == 0) {
			strncpy(map[m].save.map,"SavePoint",16);
			map[m].save.x = -1;
			map[m].save.y = -1;
			map[m].flag.nosave = 1;
		} else if (sscanf(w4,"%4095[^,],%d,%d",savemap,&savex,&savey) == 3) {
			memcpy(map[m].save.map,savemap,16);
			map[m].save.map[15] = '\0';	// force \0 terminal
			map[m].save.x = savex;
			map[m].save.y = savey;
			map[m].flag.nosave = 1;
		} else {
			map[m].flag.nosave = 0;
		}
	} else if (strcmpi(w3,"nomemo") == 0) {
		map[m].flag.nomemo ^= 1;
	} else if (strcmpi(w3,"noteleport") == 0) {
		map[m].flag.noteleport ^= 1;
	} else if (strcmpi(w3,"noportal") == 0) {
		map[m].flag.noportal ^= 1;
	} else if (strcmpi(w3,"noreturn") == 0) {
		map[m].flag.noreturn ^= 1;
	} else if (strcmpi(w3,"monster_noteleport") == 0) {
		map[m].flag.monster_noteleport ^= 1;
	} else if (strcmpi(w3,"nobranch") == 0) {
		map[m].flag.nobranch ^= 1;
	} else if (strcmpi(w3,"nopenalty") == 0) {
		map[m].flag.nopenalty ^= 1;
	} else if (strcmpi(w3,"pvp") == 0) {
		map[m].flag.pvp ^= 1;
	} else if (strcmpi(w3,"pvp_noparty") == 0) {
		map[m].flag.pvp_noparty ^= 1;
	} else if (strcmpi(w3,"pvp_noguild") == 0) {
		map[m].flag.pvp_noguild ^= 1;
	} else if (strcmpi(w3,"pvp_nightmaredrop") == 0) {
		if (npc_set_mapflag_sub(m, w4, MF_PVP_NIGHTMAREDROP))
			map[m].flag.pvp_nightmaredrop = 1;
	} else if (strcmpi(w3,"pvp_nocalcrank") == 0) {
		map[m].flag.pvp_nocalcrank ^= 1;
	} else if (strcmpi(w3,"gvg") == 0) {
		map[m].flag.gvg ^= 1;
	} else if (strcmpi(w3,"gvg_noparty") == 0) {
		map[m].flag.gvg_noparty ^= 1;
	} else if (strcmpi(w3,"gvg_nightmaredrop") == 0) {
		if (npc_set_mapflag_sub(m, w4, MF_GVG_NIGHTMAREDROP))
			map[m].flag.gvg_nightmaredrop = 1;
	} else if (strcmpi(w3,"nozenypenalty") == 0) {
		map[m].flag.nozenypenalty ^= 1;
	} else if (strcmpi(w3,"notrade") == 0) {
		map[m].flag.notrade ^= 1;
	} else if (strcmpi(w3,"noskill") == 0) {
		map[m].flag.noskill ^= 1;
	} else if (strcmpi(w3,"noabra") == 0) {
		map[m].flag.noabra ^= 1;
	} else if (strcmpi(w3,"nodrop") == 0) {
		map[m].flag.nodrop ^= 1;
	} else if (strcmpi(w3,"snow") == 0) {
		map[m].flag.snow ^= 1;
	} else if (strcmpi(w3,"fog") == 0) {
		map[m].flag.fog ^= 1;
	} else if (strcmpi(w3,"sakura") == 0) {
		map[m].flag.sakura ^= 1;
	} else if (strcmpi(w3,"leaves") == 0) {
		map[m].flag.leaves ^= 1;
	} else if (strcmpi(w3,"rain") == 0) {
		map[m].flag.rain ^= 1;
	} else if (strcmpi(w3,"fireworks") == 0) {
		map[m].flag.fireworks ^= 1;
	} else if (strcmpi(w3,"cloud1") == 0) {
		map[m].flag.cloud1 ^= 1;
	} else if (strcmpi(w3,"cloud2") == 0) {
		map[m].flag.cloud2 ^= 1;
	} else if (strcmpi(w3,"cloud3") == 0) {
		map[m].flag.cloud3 ^= 1;
	} else if (strcmpi(w3,"base_exp_rate") == 0) {
		map[m].flag.base_exp_rate = atoi(w4);
	} else if (strcmpi(w3,"job_exp_rate") == 0) {
		map[m].flag.job_exp_rate = atoi(w4);
	} else if (strcmpi(w3,"pk") == 0) {
		map[m].flag.pk ^= 1;
	} else if (strcmpi(w3,"pk_noparty") == 0) {
		map[m].flag.pk_noparty ^= 1;
	} else if (strcmpi(w3,"pk_noguild") == 0) {
		map[m].flag.pk_noguild ^= 1;
	} else if (strcmpi(w3,"pk_nightmaredrop") == 0) {
		if (npc_set_mapflag_sub(m, w4, MF_PK_NIGHTMAREDROP))
			map[m].flag.pk_nightmaredrop = 1;
	} else if (strcmpi(w3,"pk_nocalcrank") == 0) {
		map[m].flag.pk_nocalcrank ^= 1;
	} else if (strcmpi(w3,"noicewall") == 0) {
		map[m].flag.noicewall ^= 1;
	} else if (strcmpi(w3,"turbo") == 0) {
		map[m].flag.turbo ^= 1;
	} else if (strcmpi(w3,"norevive") == 0) {
		map[m].flag.norevive ^= 1;
	} else if (strcmpi(w3,"nocommand") == 0) {
		map[m].flag.nocommand = atoi(w4);
	} else if (strcmpi(w3,"nojump") == 0) {
		map[m].flag.nojump ^= 1;
	} else if (strcmpi(w3,"town") == 0) {
		map[m].flag.town ^= 1;
	} else {
		return -1;	// 存在しないマップフラグなのでエラー
	}
	return 0;
}

/*==========================================
 * ナイトメアモードの設定
 *------------------------------------------
 */
int npc_set_mapflag_sub(int m,const char *str,short flag)
{
	char drop_arg1[4096], drop_arg2[4096];
	int drop_id = 0, drop_type = 0, drop_per = 0;

	if(sscanf(str, "%4095[^,],%4095[^,],%d", drop_arg1, drop_arg2, &drop_per) != 3)
		return 0;

	if(strcmp(drop_arg1,"random") == 0) {
		drop_id = -1;
	} else {
		drop_id = atoi(drop_arg1);
		if(itemdb_exists(drop_id) == NULL)
			drop_id = 0;
	}
	if(strcmp(drop_arg2,"inventory") == 0)
		drop_type = 1;
	else if(strcmp(drop_arg2,"equip") == 0)
		drop_type = 2;
	else if(strcmp(drop_arg2,"all") == 0)
		drop_type = 3;

	if(drop_id != 0) {
		int i;
		for(i=0; i<MAX_DROP_PER_MAP; i++) {
			if(map[m].drop_list[i].drop_id == 0) {
				map[m].drop_list[i].drop_id   = drop_id;
				map[m].drop_list[i].drop_type = drop_type;
				map[m].drop_list[i].drop_per  = drop_per;
				map[m].drop_list[i].drop_flag = flag;
				break;
			}
		}
		if(i >= MAX_DROP_PER_MAP)
			printf("npc_set_mapflag_sub: drop list is full (%s, size = %d)\a\n", map[m].name, i);
		return 1;
	}
	return 0;
}

static int ev_db_final(void *key,void *data,va_list ap)
{
	aFree(data);
	if(strstr((const char *)key,"::") != NULL)
		aFree(key);

	return 0;
}

/*==========================================
 * NPCファイル解析
 *------------------------------------------
 */
static int npc_parse_srcfile(const char *filepath)
{
	char line[4096], w1[4096], w2[4096], w3[4096], w4[4096];
	int lines = 0, ret = 0;
	int comment_flag = 0;
	FILE *fp = fopen(filepath,"r");

	if(fp == NULL) {
		printf("reading npc file not found : %s\a\n",filepath);
		return 0;
	}

	while(fgets(line,sizeof(line),fp)) {
		char *lp;
		int i = 0, j = 0, w4pos = 0, count;

		lines++;

		// 不要なスペースやタブの連続は詰める
		while(line[i]) {
			switch(line[i]) {
			case ' ':
				if(!j || line[j-1] != ',') {
					if(!line[i+1]) {
						line[j++] = ' ';
					} else if(!isspace((unsigned char)line[i+1]) && line[i+1] != ',') {
						line[j++] = ' ';
					}
				}
				break;
			case '\t':
				if(!j || line[j-1] != '\t') {
					line[j++] = '\t';
				}
				break;
			default:
				line[j++] = line[i];
			}
			i++;
		}
		line[j] = 0;

		// lineに含まれるコメント部分をスキップ
		lp = npc_skip_line(line, &comment_flag);
		if(lp == NULL)
			continue;

		// 最初はタブ区切りでチェックしてみて、ダメならスペース区切りで確認
		if((count = sscanf(lp,"%4095[^\t]\t%4095[^\t]\t%4095[^\t\r\n]\t%n%4095[^\t\r\n]",w1,w2,w3,&w4pos,w4)) < 3 &&
		   (count = sscanf(lp,"%4095s%4095s%4095s%n%4095s",w1,w2,w3,&w4pos,w4)) < 3)
		{
			script_error(lp, filepath, lines, "npc file syntax error", lp+w4pos);
			break;
		}

		// マップ名として記述されているか確認
		// MAPの存在チェック自体は各parserで行う
		if(strcmp(w1,"-") != 0 && strcmpi(w1,"function") != 0) {
			size_t len;
			char mapname[4096] = "";
			sscanf(w1,"%4095[^,]",mapname);
			len = strlen(mapname);
			if(len <= 4 || len > 24 || strcmp(mapname+len-4,".gat") != 0) {
				script_error(lp, filepath, lines, "npc file syntax error", lp);
				break;
			}
		}

		if (strcmpi(w2,"warp") == 0 && count > 3) {
			ret = npc_parse_warp(w1,w2,w3,w4,lines);
		} else if ((strcmpi(w2,"shop") == 0 || strcmpi(w2,"pointshop") == 0) && count > 3) {
			ret = npc_parse_shop(w1,w2,w3,w4,lines);
		} else if ((i = 0, sscanf(w2,"substore%n",&i), (i > 0 && w2[i] == '(')) && count > 3) {
			ret = npc_parse_shop(w1,w2,w3,w4,lines);
		} else if (strcmpi(w2,"script") == 0 && count > 3) {
			if(strcmpi(w1,"function") == 0) {
				ret = npc_parse_function(w1,w2,w3,w4,line+w4pos,fp,&lines,filepath);
			} else {
				ret = npc_parse_script(w1,w2,w3,w4,line+w4pos,fp,&lines,filepath);
			}
		} else if ((i = 0, sscanf(w2,"duplicate%n",&i), (i > 0 && w2[i] == '(')) && count > 3) {
			ret = npc_parse_script(w1,w2,w3,w4,line+w4pos,fp,&lines,filepath);
		} else if (strcmpi(w2,"monster") == 0 && count > 3) {
			ret = npc_parse_mob(w1,w2,w3,w4,lines);
		} else if (strcmpi(w2,"mapflag") == 0 && count >= 3) {
			ret = npc_parse_mapflag(w1,w2,w3,w4,lines);
		} else {
			script_error(lp, filepath, lines, "npc file syntax error", lp+strlen(w1)+1);
			break;
		}
		if(ret) {
			// エラー発生時はファイルの解析終了
			break;
		}
	}
	fclose(fp);

	if(comment_flag) {
		// scriptブロック外部でマルチラインコメントを閉じ忘れ
		printf("Missing */ on %s\a\n", filepath);
	} else {
		printf("\r");
	}
	parse_script_line_curly(NULL, 0, 0);	// scriptブロック内部のcomment_flagを初期化

	return 1;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
int do_final_npc(void)
{
	int i;
	struct block_list *bl;
	struct npc_data   *nd;
	struct mob_data   *md;
	struct chat_data  *cd;

	if(npc_src_first)
		npc_clearsrcfile();

	if(ev_db)
		strdb_final(ev_db,ev_db_final);
	if(npcname_db)
		strdb_final(npcname_db,NULL);

	for(i=START_NPC_NUM; i<npc_id; i++) {
		if((bl = map_id2bl(i))) {
			if(bl->type == BL_NPC && (nd = (struct npc_data *)bl)) {
				if(bl->prev) {
					map_delblock( &nd->bl );
					map_deliddb( &nd->bl );
				}
				if(nd->chat_id && (cd = map_id2cd(nd->chat_id))) {
					aFree(cd);
					cd = NULL;
				}
				if(nd->subtype == SCRIPT) {
					if(nd->u.scr.timer_event)
						aFree(nd->u.scr.timer_event);
				 	if(nd->u.scr.src_id == 0) {
						if(nd->u.scr.script) {
							script_free_code(nd->u.scr.script);
							nd->u.scr.script = NULL;
						}
						if(nd->u.scr.label_list) {
							aFree(nd->u.scr.label_list);
							nd->u.scr.label_list = NULL;
						}
					}
				}
				aFree(nd);
				nd = NULL;
			} else if(bl->type == BL_MOB && (md = (struct mob_data *)bl)) {
				if(map[md->bl.m].mvpboss == md) {
					map[md->bl.m].mvpboss = NULL;
				}
				if(bl->prev) {
					// 復活しないMOBとして扱う
					md->spawndelay1 = -1;
					md->spawndelay2 = -1;
					md->n = 0;
					unit_remove_map(&md->bl,0,0);
				} else {
					map_deliddb(&md->bl);
					if(md->lootitem) {
						aFree(md->lootitem);
						md->lootitem = NULL;
					}
					aFree(md);
				}
				md = NULL;
			} else if(bl->type & (BL_PET | BL_HOM | BL_MERC | BL_ELEM)) {
				printf("do_final_npc: remain PET, HOM, MERC or ELEM ?\n");
				unit_free(bl,0);
			}
		}
	}

	return 0;
}

/*==========================================
 * npc初期化
 *------------------------------------------
 */
int do_init_npc(void)
{
	int number = 0;
	struct npc_src_list *nsl;
	time_t now;

	ev_db = strdb_init(48);
	npcname_db = strdb_init(24);

	time(&now);
	memcpy(&ev_tm_b, localtime(&now), sizeof(ev_tm_b));

	for(nsl = npc_src_first; nsl; nsl = nsl->next) {
		printf("reading npc [%4d] %-60s", ++number, nsl->name);
		if( !npc_parse_srcfile(nsl->name) )
			number--;
	}
	npc_clearsrcfile();

	printf("\nread %d npcs done (%d warp, %d shop, %d script, %d mob)\n",
		   npc_id-START_NPC_NUM,npc_warp,npc_shop,npc_script,npc_mob);

	add_timer_func_list(npc_event_timer);
	add_timer_func_list(npc_event_do_clock);
	add_timer_func_list(npc_timerevent);
	add_timer_func_list(npc_timeout_timer);
	add_timer_func_list(npc_dynamicnpc_timer);

	return 0;
}
