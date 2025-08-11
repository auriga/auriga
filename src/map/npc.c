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

static struct tm ev_tm_b;	// ���v�C�x���g�p

static int npc_exportlabel_data(struct npc_data *nd);


/*==========================================
 * ID���擾
 *------------------------------------------
 */
int npc_get_new_npc_id(void)
{
	if(npc_id == END_NPC_NUM+1) {	// �x���͈�x����
		printf("npc_get_new_id : ID is over END_NPC_NUM %d\n",END_NPC_NUM);
	} else if(npc_id == 0x7fffffff) {
		printf("npc_get_new_id : ID is overflow !!\n");
		exit(1);		// �����������Ȃ��Ȃ�̂ŗ��Ƃ�
	}
	return npc_id++;
}

/*==========================================
 * NPC�̖�����/�L����
 * npc_enable
 * npc_enable_sub �L������OnTouch�C�x���g�����s
 *------------------------------------------
 */
static int npc_enable_sub( struct block_list *bl, va_list ap )
{
	struct map_session_data *sd;
	struct npc_data *nd;
	char name[76];
	int i;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, nd = va_arg(ap,struct npc_data *));
	nullpo_retr(0, sd = (struct map_session_data *)bl);

	if(nd->flag&1) {	// ����������Ă���
		for(i=0; i < MAX_EVENTQUEUE; i++) {
			if(sd->areanpc_id[i] == nd->bl.id) {	// NPC�ƐڐG���Ă�������������
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
		// �B��Ă���ƃ��[�v�ł��Ȃ�
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

	if (flag&1) {	// �L����
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
	} else {	// ������
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
 * NPC�𖼑O�ŒT��
 *------------------------------------------
 */
struct npc_data* npc_name2id(const char *name)
{
	return (struct npc_data *)strdb_search(npcname_db,name);
}

/*==========================================
 * NPC���v���C���[�̌����ڂ��ǂ���
 *------------------------------------------
 */
int npc_is_pcview(struct npc_data *nd)
{
	nullpo_retr(0, nd);

	if(nd->class_ >= 0 && nd->class_ <= PC_CLASS_SU2)
		return 1;
	if(nd->class_ >= PC_CLASS_NV_H && nd->class_ < PC_CLASS_MAX)
		return 1;

	return 0;
}

/*==========================================
 * NPC�̍ēo�^
 *------------------------------------------
 */
int npc_refresh(const char *name, struct npc_data *nd)
{
	strdb_erase(npcname_db,name);
	strdb_insert(npcname_db,name,nd);

	return 0;
}

/*==========================================
 * �C�x���g�̒x�����s
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
 * �C�x���g�L���[�̃C�x���g����
 *------------------------------------------
 */
int npc_event_dequeue(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	if(sd->stack) {
		// ���̃X�^�b�N����j��
		script_free_stack(sd->stack);
		sd->stack = NULL;
	}

	sd->npc_sleep = NULL;
	sd->npc_pos = -1;
	sd->npc_id = 0;
	sd->state.menu_or_input = 0;
	sd->progressbar.npc_id = 0;
	sd->progressbar.tick = 0;

	if(sd->eventqueue[0][0]) {	// �L���[�̃C�x���g����
		char *name = (char *)aCalloc(76,sizeof(char));
		int i;
		unsigned int tick = gettick();

		// copy the first event
		memcpy(name,sd->eventqueue[0],76);

		// shift queued events down by one
		for(i=1; i<MAX_EVENTQUEUE; i++)
			memcpy(sd->eventqueue[i-1],sd->eventqueue[i],76);

		// clear the last event
		sd->eventqueue[MAX_EVENTQUEUE-1][0] = 0;

		// add the timer
		add_timer2(tick+100,npc_event_timer,sd->bl.id,name);
	}
	return 0;
}

/*==========================================
 * �S�Ă�NPC��On*�C�x���g���s
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
 * �w��}�b�v�S�Ă�NPC��On*�C�x���g���s
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
			// �w��MAP����NPC�ł̂ݔ���
			run_script(ev->nd->u.scr.script,ev->pos,0,ev->nd->bl.id);
			c++;
		}
		ev = ev->next;
	}

	return c;
}

/*==========================================
 * OnPC*�C�x���g���s
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
		// ����MAP���}�b�v��z�u�^NPC�ł̂ݔ���
		if(ev->nd && (ev->nd->bl.m == m || ev->nd->bl.m == -1)) {
			run_script(ev->nd->u.scr.script,ev->pos,rid,ev->nd->bl.id);
			c++;
		}
		ev = ev->next;
	}

	return c;
}

/*==========================================
 * NPC�C�x���g���s
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
 * ���v�C�x���g���s
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
 * OnInit�C�x���g���s(&���v�C�x���g�J�n)
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
 * �^�C�}�[�C�x���g���s
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
 * �^�C�}�[�C�x���g�J�n
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
 * �^�C�}�[�C�x���g�I��
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
 * �^�C�}�[�l�̎擾
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
 * �^�C�}�[�l�̐ݒ�
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
 * �^�C���A�E�g���s
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
			// ���̃X�^�b�N����j��
			script_free_stack(sd->stack);
			sd->stack = NULL;
		}
		// menu, select, input�̕ԓ��ҋ@�����i�M���h�q�ɂ͉�����҂j
		if(sd->state.menu_or_input == 1 && sd->state.gstorage_lockreq == 0)
			sd->state.menu_or_input = 0;

		// �v���O���X�o�[�̉����ҋ@����
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
 * �^�C���A�E�g�^�C�}�[�J�n
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
 * �^�C���A�E�g�^�C�}�[�I��
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
 * �_�C�i�~�b�NNPC�^�C���A�E�g���s
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
		// �^�C���A�E�g�^�C�}�[���~�߂�
		if(sd->npc_id == sd->npc_dynamic_id) {
			npc_timeout_stop(sd);

			if(sd->stack) {
				// ���̃X�^�b�N����j��
				script_free_stack(sd->stack);
				sd->stack = NULL;
			}

			// menu, select, input�̕ԓ��ҋ@�����i�M���h�q�ɂ͉�����҂j
			if(sd->state.menu_or_input == 1 && sd->state.gstorage_lockreq == 0)
				sd->state.menu_or_input = 0;

			// �v���O���X�o�[�̉����ҋ@����
			if(sd->progressbar.tick) {
				sd->progressbar.npc_id = 0;
				sd->progressbar.tick   = 0;
			}
		}

		// �_�C�i�~�b�NNPC�^�C�}�[���~�߂�
		clif_clearchar_id(sd->npc_dynamic_id, 0, sd->fd);
		sd->npc_dynamic_timer = -1;
		sd->npc_dynamic_id = 0;

	} else {
		sd->npc_dynamic_timer = add_timer(gettick()+1000,npc_dynamicnpc_timer,sd->bl.id,0);
	}

	return 0;
}

/*==========================================
 * �_�C�i�~�b�NNPC�^�C�}�[�J�n
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
 * �_�C�i�~�b�NNPC�^�C�}�[�I��
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
 * �C�x���g�^��NPC����
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
			strncpy(sd->eventqueue[i],eventname,76);
			sd->eventqueue[i][75] = '\0';	// force \0 terminal
		}
		return 1;
	}
	if (nd->flag&3) {	// ����������Ă���
		npc_event_dequeue(sd);
		return 0;
	}

	run_script(nd->u.scr.script,ev->pos,sd->bl.id,nd->bl.id);
	return 0;
}

/*==========================================
 * �ڐG�^��NPC����
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

		if(nd->flag&1) {	// ����������Ă���
			f = 0;
			continue;
		}
		if(nd->option&OPTION_CLOAKING) {
			int j;
			for(j=0; j < MAX_CLOAKEDNPC; j++) {
				if(sd->cloaked_npc[j] == nd->bl.id) {
					break;
				}
			}
			if(j == MAX_CLOAKEDNPC) {	// �����ȃN���[�L���O���
				f = 0;
				continue;
			}
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
				// �B��Ă���ƃ��[�v�ł��Ȃ�
				if(pc_ishiding(sd))
					break;
				skill_stop_dancing(&sd->bl,0);
				pc_setpos(sd,nd->u.warp.name,nd->u.warp.x,nd->u.warp.y,0);
				break;
			case SCRIPT:
				if(sd->sc.data[SC_FORCEWALKING].timer == -1) {
					char name[76];
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
 * �ڐG�^��NPC����(NPC�p)
 *------------------------------------------
 */
int npc_touch_areanpc2(struct mob_data *md,int m,int x,int y)
{
	int i, id, xs, ys;
	struct npc_data *nd = NULL;

	nullpo_retr(1, md);

	for(i = 0; i < map[m].npc_num; i++) {
		nd = map[m].npc[i];

		if (nd->flag&1) {	// ����������Ă���
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
				char name[76];

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
 * �߂����ǂ����̔���
 *------------------------------------------
 */
static int npc_checknear(struct map_session_data *sd, struct npc_data *nd)
{
	nullpo_retr(1, sd);

	if (nd == NULL || nd->bl.type != BL_NPC) {
		printf("npc_checknear: npc not found!!\n");
		return 1;
	}

	if (nd->class_ < 0 || sd->npc_dynamic_id == nd->bl.id)	// �C�x���g�n�͏��OK
		return 0;

	// �G���A����
	if (nd->bl.m != sd->bl.m ||
	    nd->bl.x < sd->bl.x-AREA_SIZE-1 || nd->bl.x > sd->bl.x+AREA_SIZE+1 ||
	    nd->bl.y < sd->bl.y-AREA_SIZE-1 || nd->bl.y > sd->bl.y+AREA_SIZE+1) {
		printf("npc_checknear: npc too far!! %s\n",nd->exname);
		return 1;
	}
	return 0;
}

/*==========================================
 * �߂����ǂ����̔���
 *------------------------------------------
 */
static int npc_isnear_sub(struct block_list *bl, va_list ap)
{
	struct npc_data *nd;

	nullpo_retr(0, bl);
	nullpo_retr(0, nd = (struct npc_data *)bl);

	if(nd->class_ < 0)	// �C�x���g�n�͏��OK
		return 0;

	return 1;
}

bool npc_isnear(struct block_list *bl)
{
	int r;

	nullpo_retr(false, bl);

	r = battle_config.min_npc_vendchat_distance;

	// �G���A����
	if(r > 0 && map_foreachinarea(npc_isnear_sub,bl->m,bl->x-r,bl->y-r,bl->x+r,bl->y+r,BL_NPC) )
		return true;

	return false;
}

/*==========================================
 * NPC�̃I�[�v���`���b�g����
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
	if((p = strchr(temp,'#')) != NULL)	// #�ȉ��̕�����͕\�����Ȃ�
		*p = 0;

	len = strlen(temp);
	snprintf(temp+len, sizeof(temp)-len, " : %s", mes);
	clif_GlobalMessage(&nd->bl,temp,AREA_CHAT_WOC);

	return 0;
}

/*==========================================
 * �N���b�N����NPC����
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

	if (nd->flag&1)	// ����������Ă���
		return;
	if (nd->subtype == SCRIPT && nd->ud.walktimer != -1 && nd->click_able < 1)
		return;
	if (nd->option&OPTION_CLOAKING) {
		int i;
		for(i=0; i < MAX_CLOAKEDNPC; i++) {
			if(sd->cloaked_npc[i] == nd->bl.id) {
				break;
			}
		}
		if(i == MAX_CLOAKEDNPC)
			return;
	}

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
	case MARKET:
#if PACKETVER >= 20131223
		{
			int i;

			for (i = 0; nd->u.shop_item[i].nameid; i++) {
				if (nd->u.shop_item[i].qty) {
					sd->npc_id     = id;
					sd->npc_shopid = id;
					clif_market_list(sd,nd);
					npc_event_dequeue(sd);
					break;
				}
			}
		}
#endif
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

	if (id <= 0)
		return;

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

	if (nd->flag&1)	// ����������Ă���
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
int npc_buylist(struct map_session_data *sd,int n,unsigned char *item_list)
{
	struct npc_data *nd;
	double z;
	int i, j, w, new_add = 0;
	struct item_data *item_data;
	short market_qty[MAX_INVENTORY];

	nullpo_retr(3, sd);
	nullpo_retr(3, item_list);

	nd = map_id2nd(sd->npc_shopid);
	if (npc_checknear(sd, nd)) // check NULL of nd and if nd->bl.type is BL_NPC
		return 3;

	if (nd->subtype != SHOP && nd->subtype != MARKET)
		return 3;

	w = 0;
	z = 0.;
	memset(market_qty, 0, sizeof(market_qty));
	for(i = 0; i < n; i++) {
		int nameid, amount;
#if PACKETVER < 20180704
		if (nd->subtype == MARKET) {
			nameid = *(unsigned short *)(item_list + 6*i + 0);
			amount = *(unsigned int *)(item_list + 6*i + 2);
		} else {
			amount = *(unsigned short *)(item_list + 4*i + 0);
			nameid = *(unsigned short *)(item_list + 4*i + 2);
		}
#else
		if (nd->subtype == MARKET) {
			nameid = *(unsigned int *)(item_list + 8*i + 0);
			amount = *(unsigned int *)(item_list + 8*i + 4);
		} else {
			amount = *(unsigned short *)(item_list + 6*i + 0);
			nameid = *(unsigned int *)(item_list + 6*i + 2);
		}
#endif
		if (amount <= 0)
			return 3;
		if (nameid <= 0 || (item_data = itemdb_exists(nameid)) == NULL)
			return 3;

		for(j=0; nd->u.shop_item[j].nameid; j++) {
			int view_id = itemdb_viewid(nd->u.shop_item[j].nameid);
			if (view_id > 0) {
				if (view_id == nameid) {
					// ���̃A�C�e��ID�ɒu������
#if PACKETVER < 20180704
					if (nd->subtype == MARKET)
						*(short *)(item_list + 6*i + 0) = (short)nd->u.shop_item[j].nameid;
					else
						*(short *)(item_list + 4*i + 2) = (short)nd->u.shop_item[j].nameid;
#else
					if (nd->subtype == MARKET)
						*(int *)(item_list + 8*i + 0) = (int)nd->u.shop_item[j].nameid;
					else
						*(int *)(item_list + 6*i + 2) = (int)nd->u.shop_item[j].nameid;
#endif
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

#if PACKETVER >= 20131223
		if (nd->subtype == MARKET) {
			if (amount > nd->u.shop_item[j].qty)
				return 3;
			market_qty[i] = j;
		}
#endif

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
		return 3;	// ��ސ�����

	pc_payzeny(sd,(int)z);

	for(i=0; i<n; i++) {
		struct item item_tmp;
		unsigned short amount;

		memset(&item_tmp,0,sizeof(item_tmp));
#if PACKETVER < 20180704
		if (nd->subtype == MARKET) {
			item_tmp.nameid = *(unsigned short *)(item_list + 6*i + 0);
			amount = *(unsigned short *)(item_list + 6*i + 2);
		} else {
			item_tmp.nameid = *(unsigned short *)(item_list + 4*i + 2);
			amount = *(unsigned short *)(item_list + 4*i);
		}
#else
		if (nd->subtype == MARKET) {
			item_tmp.nameid = *(unsigned int *)(item_list + 8*i + 0);
			amount = *(unsigned short *)(item_list + 8*i + 4);
		} else {
			item_tmp.nameid = *(unsigned int *)(item_list + 6*i + 2);
			amount = *(unsigned short *)(item_list + 6*i);
		}
#endif
		item_tmp.identify = 1;	// npc�̔��A�C�e���͊Ӓ�ς�

#if PACKETVER >= 20131223
		if (nd->subtype == MARKET) {
			j = market_qty[i];
			if (amount > nd->u.shop_item[j].qty)
				return 1;
			nd->u.shop_item[j].qty -= amount;
		}
#endif

		pc_additem(sd,&item_tmp,amount,false);
	}

	// ���l�o���l
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

	// ���l�o���l
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
 * �X�y�V�����A�C�e���w��
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
	item_tmp.identify = 1;	// npc�̔��A�C�e���͊Ӓ�ς�

	pc_additem(sd, &item_tmp, amount,false);
	sd->shop_point -= point;

	return 0;
}

/*==========================================
 * �X�y�V�����A�C�e���w������
 *------------------------------------------
 */
int npc_pointshop_buylist(struct map_session_data *sd, int len, int count, const unsigned char *item_list)
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
#if PACKETVER < 20180704
		const unsigned int nameid = *(short *)(item_list + 4*i + 2);
		const unsigned short amount = *(short *)(item_list + 4*i + 0);
#else
		const unsigned int nameid = *(int *)(item_list + 6*i + 2);
		const unsigned short amount = *(short *)(item_list + 6*i + 0);
#endif

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
				return 3; // ��ސ�����
			break;
		case ADDITEM_OVERAMOUNT:
			return 3; // �A�C�e��������
		}

		weight += item_data->weight * amount;
		if(weight + sd->weight > sd->max_weight)
			return 2;
	}

	sd->shop_point -= point;

	for( i = 0; i < count; i++) {
#if PACKETVER < 20180704
		const unsigned int nameid = *(short *)(item_list + 4*i + 2);
		const unsigned short amount = *(short *)(item_list + 4*i + 0);
#else
		const unsigned int nameid = *(int *)(item_list + 6*i + 2);
		const unsigned short amount = *(short *)(item_list + 6*i + 0);
#endif
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
		item_tmp.identify = 1;	// npc�̔��A�C�e���͊Ӓ�ς�

		pc_additem(sd, &item_tmp, amount,false);
	}

	return 0;
}

/*==========================================
 * �������A���_���W����NPC�ǉ�
 *------------------------------------------
 */
int npc_addmdnpc(struct npc_data *src_nd, int m)
{
	struct npc_data *nd;
	char newname[50];

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
	nd->name[49] = '\0';
	nd->exname[49] = '\0';

	nd->bl.prev = nd->bl.next = NULL;
	nd->bl.m    = m;
	nd->bl.x    = src_nd->bl.x;
	nd->bl.y    = src_nd->bl.y;
	nd->bl.id   = npc_get_new_npc_id();
	nd->dir     = src_nd->dir;
	nd->flag    = src_nd->flag;
	nd->class_  = src_nd->class_;
	nd->speed   = 200;
	nd->chat_id = 0;
	nd->click_able = 0;
	nd->option  = src_nd->option;
	nd->bl.type = BL_NPC;
	nd->subtype = src_nd->subtype;

	nd->group_id = src_nd->group_id;
	strcpy(nd->title, src_nd->title);
	nd->title[23] = '\0';	// froce \0 terminal

	unit_dataset( &nd->bl );

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
	case MARKET:
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
		if(nd->subtype == WARP || (nd->subtype == SCRIPT && nd->u.scr.xs > 0 && nd->u.scr.ys > 0))	// �ڐG�^�Ȃ̂œo�^
			nd->n = map_addnpc(m,nd);
		else
			map_addiddb(&nd->bl);

		if(nd->class_ < 0) {	// �C�x���g�^
			struct event_data *ev, *old_ev;
			ev       = (struct event_data *)aCalloc(1,sizeof(struct event_data));
			ev->key  = NULL;
			ev->nd   = nd;
			ev->pos  = 0;
			ev->next = NULL;
			old_ev   = (struct event_data *)strdb_insert(ev_db,nd->exname,ev);
			if(old_ev) {
				// �C�x���g���d�����Ă���ꍇ�B������return����ƈȑO�̏�����
				// ���r���[�ɂȂ�ׁA�����𑱍s����B
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

	// �C�x���g�p���x���f�[�^�̃G�N�X�|�[�g
	if(nd->subtype == SCRIPT)
		npc_exportlabel_data(nd);

	return 1;
}

/*==========================================
 * NPC���
 *------------------------------------------
 */
int npc_free(struct npc_data *nd)
{
	struct chat_data  *cd;
	struct event_data *ev;

	nullpo_retr(0, nd);

	// blocklist�������
	if(nd->bl.prev) {
		map_delblock( &nd->bl );
		map_deliddb( &nd->bl );
	}

	// �`���b�g����
	if(nd->chat_id && (cd = map_id2cd(nd->chat_id))) {
		aFree(cd);
		cd = NULL;
	}

	if(nd->subtype == SCRIPT) {
		// �^�C�}�[���
		if(nd->u.scr.timer_event)
			aFree(nd->u.scr.timer_event);
		// �X�N���v�g�R�[�h���
		if(nd->u.scr.script) {
			script_free_code(nd->u.scr.script);
			nd->u.scr.script = NULL;
		}
		// ���x���f�[�^�̃C�x���g���
		if(nd->u.scr.label_list) {
			int i;
			for(i = 0; i < nd->u.scr.label_list_num; i++) {
				char key[76];

				snprintf(key, 76, "%s::%s", nd->exname, nd->u.scr.label_list[i].name);
				ev = (struct event_data *)strdb_search(ev_db,key);
				if(ev) {
					strdb_erase(ev_db,key);

					// �m�[�h�̃����N�ύX
					if(ev->prev)
						ev->prev->next = ev->next;
					if(ev->next)
						ev->next->prev = ev->prev;

					aFree(ev->key);
					aFree(ev);
				}
			}
		}
		// ���x���f�[�^����i��NPC�̂݁j
		if(nd->u.scr.src_id == 0) {
			aFree(nd->u.scr.label_list);
			nd->u.scr.label_list = NULL;
		}
	}

	// �C�x���g�^NPC
	if(nd->class_ < 0) {
		ev = (struct event_data *)strdb_search(ev_db,nd->exname);
		if(ev) {
			strdb_erase(ev_db,nd->exname);

			// �m�[�h�̃����N�ύX
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

/*==========================================

 *------------------------------------------
 */
static int npc_unit_move_sub( struct block_list *bl, va_list ap )
{
	struct map_session_data *sd;
	struct npc_data *nd;
	int i;
	int xs,ys;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, nd = va_arg(ap,struct npc_data *));
	nullpo_retr(0, sd = (struct map_session_data *)bl);

	if(sd == NULL || nd == NULL)
		return 0;

	for(i = 0; i < MAX_EVENTQUEUE; i++) {
		if(sd->areanpc_id[i] == nd->bl.id) {
			if(!(nd->bl.m == nd->bl.m &&
				sd->bl.x >= nd->bl.x - nd->u.scr.xs/2 && sd->bl.x < nd->bl.x - nd->u.scr.xs/2 + nd->u.scr.xs &&
				sd->bl.y >= nd->bl.y - nd->u.scr.ys/2 && sd->bl.y < nd->bl.y - nd->u.scr.ys/2 + nd->u.scr.ys))
			sd->areanpc_id[i] = 0;
		}
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
		return 0;
	}

	if(sd->bl.x >= nd->bl.x-xs/2 && sd->bl.x < nd->bl.x-xs/2+xs &&
	   sd->bl.y >= nd->bl.y-ys/2 && sd->bl.y < nd->bl.y-ys/2+ys) {
		switch(nd->subtype) {
		case WARP:
			// �B��Ă���ƃ��[�v�ł��Ȃ�
			if(pc_ishiding(sd))
				break;
			skill_stop_dancing(&sd->bl,0);
			pc_setpos(sd,nd->u.warp.name,nd->u.warp.x,nd->u.warp.y,0);
			break;
		case SCRIPT:
			if(sd->sc.data[SC_FORCEWALKING].timer == -1) {
				char name[76];
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
		default:
			return 0;
		}
	}

	return 0;
}

/*==========================================
 * NPC���ړ������Ƃ���OnTouch����
 * flag : 0 �ړ��O
 * flag : 1 �ړ���
 *------------------------------------------
 */
int npc_unit_move(struct npc_data *nd, int flag)
{
	int xs = 0, ys = 0;

	nullpo_retr(0, nd);

	if (nd == NULL)
		return 0;

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
		return 0;
	}
	if (xs > 0 || ys > 0) {
		int i,j;
		for(i=0; i<ys; i++) {
			for(j=0; j<xs; j++) {
				if(map_getcell(nd->bl.m,nd->bl.x-xs/2+j,nd->bl.y-ys/2+i,CELL_CHKNOPASS))
					continue;
				if(flag == 1) {
					map_setcell(nd->bl.m,nd->bl.x-xs/2+j,nd->bl.y-ys/2+i,CELL_SETMOVENPC);
				} else {
					map_setcell(nd->bl.m,nd->bl.x-xs/2+j,nd->bl.y-ys/2+i,CELL_CLRMOVENPC);
				}
			}
		}
		if(flag == 1) {
			map_foreachinarea(npc_unit_move_sub,
				nd->bl.m,nd->bl.x-xs,nd->bl.y-ys,nd->bl.x+xs,nd->bl.y+ys,
				BL_PC,nd);
		}
	}

	return 0;
}

//
// �������֌W
//

/*==========================================
 * �ǂݍ���npc�t�@�C���̃N���A
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
 * �ǂݍ���npc�t�@�C���̒ǉ�
 *------------------------------------------
 */
void npc_addsrcfile(const char *name)
{
	struct npc_src_list *node;

	if(strcasecmp(name,"clear") == 0) {
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
 * �ǂݍ���npc�t�@�C���̍폜
 *------------------------------------------
 */
void npc_delsrcfile(const char *name)
{
	struct npc_src_list *node, *node2;

	if(strcasecmp(name,"all") == 0) {
		npc_clearsrcfile();
		return;
	}

	// �d�������t�@�C��������̂őS���[�v
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
 * npc�t�@�C���s�̓ǂݔ�΂�
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
 * warp�s���
 *------------------------------------------
 */
static int npc_parse_warp(const char *w1,const char *w2,const char *w3,const char *w4,int lines)
{
	int m, x, y, dir = 0, xs, ys, to_x, to_y;
	int i, j, n;
	char mapname[4096], to_mapname[4096];
	char *p;
	struct npc_data *nd;

	// �����̌��`�F�b�N
	// dir�͂����Ă��Ȃ��Ă��ǂ�
	if(sscanf(w1,"%4095[^,],%d,%d%n",mapname,&x,&y,&n) != 3 ||
	   (w1[n] != 0 && (sscanf(w1+n,",%d%n",&dir,&i) != 1 || w1[n+i] != 0)) ||
	   sscanf(w4,"%d,%d,%4095[^,],%d,%d%n",&xs,&ys,to_mapname,&to_x,&to_y,&n) != 5 || w4[n] != 0)
	{
		printf("bad warp declaration : %s line %d\a\n",w3,lines);
		return 0;
	}

	m = map_mapname2mapid(mapname);
	if(m < 0)
		return 0;	// assign����ĂȂ�MAP�Ȃ̂ŏI��

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
		strncpy(nd->name,w3,50);
		strncpy(nd->exname,p,50);
	} else {
		strncpy(nd->name,w3,50);
		strncpy(nd->exname,w3,50);
	}
	nd->name[49]   = '\0';
	nd->exname[49] = '\0';

	nd->chat_id = 0;
	if (!battle_config.warp_point_debug)
		nd->class_ = WARP_CLASS;
	else
		nd->class_ = WARP_DEBUG_CLASS;
	nd->speed  = 200;
	nd->click_able = 0;
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
 * shop�s���
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
	else if(strcmp(w2,"market") == 0)
#if PACKETVER < 20131223
		return 0;
#else
		subtype = MARKET;
#endif
	else
		subtype = 0;

	if(strcmp(w1,"-") == 0) {
		x = 0;
		y = 0;
		m = -1;
	} else {
		char mapname[4096];

		// �����̌��`�F�b�N
		if(sscanf(w1, "%4095[^,],%d,%d,%d%n", mapname, &x, &y, &dir, &n) != 4 || w1[n] != 0 ||
		   (subtype != 0 && strchr(w4,',') == NULL))
		{
			printf("bad shop declaration : %s line %d\a\n", w3, lines);
			return 0;
		}
		m = map_mapname2mapid(mapname);
		if(m < 0)
			return 0;	// assign����ĂȂ�MAP�Ȃ̂ŏI��
	}

	if(subtype == SHOP || subtype == POINTSHOP || subtype == MARKET) {
		const int max = 100;
		char *c;

		nd = (struct npc_data *)aCalloc(1, sizeof(struct npc_data) + sizeof(nd->u.shop_item[0]) * (max + 1));
		c = strchr(w4, ',');
		while(c && pos < max) {
			struct item_data *id = NULL;
			int nameid, value = -1;
			int qty = -1;
			c++;
			if(subtype == MARKET) {
				if(sscanf(c, "%d:%d:%d", &nameid, &value, &qty) < 3) {
					char *np = strchr(c, ',');
					if(np) {
						np[1] = 0;
					}
					printf("bad %s item %s : %s line %d\a\n", w2, c, w3, lines);
					pos = 0;
					break;
				}
			} else {
				int ret;
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
			}
			id = itemdb_search(nameid);
			nd->u.shop_item[pos].nameid = nameid;
			nd->u.shop_item[pos].qty = qty;
			if(subtype == SHOP) {
				int sell_max, buy_max;
				if(value < 0) {
					value = id->value_buy;
				}
				if(id->flag.value_notoc)	//NOTOC�t���O�𔻒�
					sell_max = id->value_sell;
				else
					sell_max = pc_modifysellvalue(NULL, id->value_sell);

				if(id->flag.value_notdc)	//NOTDC�t���O�𔻒�
					buy_max  = value;
				else
					buy_max  = pc_modifybuyvalue(NULL, value);

				if(sell_max > buy_max) {
					// ����l�������l���z����\��������̂Ōx��
					printf("warning shop sell value (id = %d, %dz > %dz) : %s line %d\a\n", nameid, sell_max, buy_max, w3, lines);
				}
			}
			else if(subtype == MARKET && value < 0)
				value = id->value_buy;
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
		// substore�̓R�s�[���邾��
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
		if(nd2->subtype != SHOP && nd2->subtype != POINTSHOP && nd2->subtype != MARKET) {
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
		strncpy(nd->name,w3,50);
		strncpy(nd->exname,p,50);
	} else {
		strncpy(nd->name,w3,50);
		strncpy(nd->exname,w3,50);
	}
	nd->name[49]   = '\0';
	nd->exname[49] = '\0';

	nd->class_  = atoi(w4);
	nd->speed   = 200;
	nd->click_able = 0;
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
 * NPC�̃��x���f�[�^�R���o�[�g
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

	// �����v��Ȃ��Ȃ����̂ŉ��
	linkdb_final(&scriptlabel_db);

	return 0;
}

/*==========================================
 * NPC�̃��x���f�[�^�G�N�X�|�[�g
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

		// �G�N�X�|�[�g�����
		ev       = (struct event_data *)aCalloc(1,sizeof(struct event_data));
		ev->key  = (char *)aCalloc(76,sizeof(char));
		ev->nd   = nd;
		ev->pos  = pos;
		ev->next = NULL;
		snprintf(ev->key, 76, "%s::%s", nd->exname, lname);
		if(strdb_search(ev_db,ev->key)) {
			printf("npc_exportlabel_data : dup event %s\n",ev->key);
			aFree(ev->key);
			aFree(ev);
			return 1;
		}
		strdb_insert(ev_db,ev->key,ev);

		if(strncmp(lname, "OnTimer", 7) != 0) {
			// �^�C�}�[�ȊO��doall�p�Ƀ��x�����X�g�����
			struct event_data *node;
			char buf[32] = "::";

			strcat(buf,lname);
			node = (struct event_data *)strdb_search(ev_db,buf);
			if(node == NULL) {
				// �o�^����ĂȂ����x���Ȃ̂ŐV�K�쐬����
				node       = (struct event_data *)aCalloc(1,sizeof(struct event_data));
				node->key  = (char *)aCalloc(76,sizeof(char));
				node->nd   = NULL;
				node->pos  = -1;
				node->next = NULL;
				strncpy(node->key, buf, strlen(buf)+1);
				strdb_insert(ev_db,node->key,node);
			}
			// ���X�g�̖����ɘA��
			while(node->next) {
				node = node->next;
			}
			node->next = ev;
			ev->prev = node;
		}
		else if(sscanf(lname,"OnTimer%d%n",&t,&n) == 1 && lname[n] == '\0') {
			// �^�C�}�[�C�x���g
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
 * script�s���
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
	int move = 0;
	int flag = 1;
	int option = OPTION_NOTHING;

	if(strcmp(w1,"-") == 0) {
		x = 0;
		y = 0;
		m = -1;
	} else {
		// �����̌��`�F�b�N
		char mapname[4096];
		int n;

		if(sscanf(w1,"%4095[^,],%d,%d,%d%n",mapname,&x,&y,&dir,&n) != 4 || w1[n] != 0 ||
		   (strstr(w2,"script") && strchr(w4,',') == NULL))
		{
			printf("bad script declaration : %s line %d\a\n",w3,*lines);
			return 0;
		}
		m = map_mapname2mapid(mapname);
	}

	if(strstr(w2,"script")) {
		// �X�N���v�g�̉��
		// { , } �̓���q�������炱�����ł��ȈՉ�͂��Ȃ��Ƃ����Ȃ��Ȃ����������
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
			// line �̒��ɕ����� , {} ���܂܂�Ă��邩����
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
		if(strcmp(w1,"-") != 0 && m < 0) {	// assign����ĂȂ�MAP�Ȃ̂�parse�����ɏI��
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
		// duplicate����
		char srcname[4096];
		struct npc_data *nd2;
		int n;

		if(sscanf(w2,"duplicate(%4095[^)])%n",srcname,&n) != 1 || w2[n] != 0) {
			printf("bad duplicate name! : %s line %d\a\n",w2,*lines);
			return 0;
		}
		if(strcmp(w1,"-") != 0 && m < 0) {	// assign����ĂȂ�MAP�Ȃ̂ŏI��
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
		move         = nd2->u.scr.moveable;
		option       = nd2->option;
	}
	// end of �X�N���v�g���

	nd = (struct npc_data *)aCalloc(1,sizeof(struct npc_data));
	nd->u.scr.xs = 0;
	nd->u.scr.ys = 0;

	if(m == -1) {
		// �X�N���v�g�R�s�[�p�̃_�~�[NPC
	} else if(sscanf(w4,"%d,%d,%d",&class_,&xs,&ys) == 3) {
		// �ڐG�^NPC
		if(xs >= 0) xs = xs * 2 + 1;
		if(ys >= 0) ys = ys * 2 + 1;

		if(class_ >= 0 && !nd->u.scr.moveable) {
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
		// �N���b�N�^NPC
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
		strncpy(nd->name,w3,50);
		strncpy(nd->exname,p,50);
	} else {
		strncpy(nd->name,w3,50);
		strncpy(nd->exname,w3,50);
	}
	nd->name[49]   = '\0';
	nd->exname[49] = '\0';

	nd->bl.prev = nd->bl.next = NULL;
	nd->bl.m    = m;
	nd->bl.x    = x;
	nd->bl.y    = y;
	nd->bl.id   = npc_get_new_npc_id();
	nd->dir     = dir;
	nd->flag    = 0;
	nd->class_  = class_;
	nd->sex  = 0;
	nd->hair  = 0;
	nd->hair_color  = 0;
	nd->clothes_color  = 0;
	nd->head_top  = 0;
	nd->head_mid  = 0;
	nd->head_bottom  = 0;
	nd->robe  = 0;
	nd->style  = 0;
	nd->speed   = 200;
	nd->click_able = 0;
	nd->u.scr.script = script;
	nd->u.scr.src_id = src_id;
	nd->chat_id = 0;
	nd->option  = option;

	nd->group_id = 0;
	nd->title[23] = '\0';	// froce \0 terminal

	npc_script++;
	nd->bl.type = BL_NPC;
	nd->subtype = SCRIPT;

	unit_dataset( &nd->bl );

	// �X�N���v�g�^�̏�ԏ���
	if(strstr(w2,"script") && strcmp(w2,"script") > 0) {
		char state_name[128] = "";
		size_t len = strlen(w2);
		int shift = 7;

		// ���sNPC(script2)����
		if (w2[shift-1] == '2') {
			move = 1;
			shift++;
		}

		// ��Ԗ�����
		if (w2[shift-1] != '(' || w2[len-1] != ')' || len <= shift || len-shift >= sizeof(state_name)) {
			if(!move)	// �ʏ���sNPC�ȊO�̓G���[
				printf("npc_parse_script : invalid npc state %s! name: %s\n", w2, nd->exname);
		} else {
			flag = 0;
			strncpy(state_name, w2+shift, len-shift-1);
			if (strcmp("CLOAKED", state_name) == 0) {
				nd->option = OPTION_CLOAKING;
			} else if (strcmp("HIDDEN", state_name) == 0) {
				nd->flag |= 1;
				nd->option = OPTION_HIDE;
			} else if (strcmp("DISABLED", state_name) == 0) {
				nd->flag |= 3;
			} else
				printf("npc_parse_script : invalid npc state %s! name: %s\n", state_name, nd->exname);
		}
	}

	if(move)
		nd->u.scr.moveable = 1;
	else
		nd->u.scr.moveable = 0;

	//printf("script npc %s %d %d read done\n",mapname,nd->bl.id,nd->class_);

	if(m >= 0) {
		map_addblock(&nd->bl);
		if(nd->u.scr.xs > 0 && nd->u.scr.ys > 0)	// �ڐG�^�Ȃ̂œo�^
			nd->n = map_addnpc(m,nd);
		else
			map_addiddb(&nd->bl);

		if(class_ < 0) {	// �C�x���g�^
			struct event_data *ev, *old_ev;
			ev       = (struct event_data *)aCalloc(1,sizeof(struct event_data));
			ev->key  = NULL;
			ev->nd   = nd;
			ev->pos  = 0;
			ev->next = NULL;
			old_ev   = (struct event_data *)strdb_insert(ev_db,nd->exname,ev);
			if(old_ev) {
				// �C�x���g���d�����Ă���ꍇ�B������return����ƈȑO�̏�����
				// ���r���[�ɂȂ�ׁA�����𑱍s����B
				printf("npc_parse_script : dup event name %s\n",nd->exname);
				aFree(old_ev);
				fail = 1;
			}
		} else if(flag) {
			clif_spawnnpc(nd);
		}
	} else {
		map_addiddb(&nd->bl);
	}
	strdb_insert(npcname_db,nd->exname,nd);

	// ���x���f�[�^�̏���
	if(srcbuf) {
		// script�{�̂�����ꍇ�̏���
		if(script) {
			// �R�[�h������Ȃ烉�x���f�[�^���R���o�[�g
			npc_convertlabel_db(nd);
		}
		aFree(srcbuf);	// �����g��Ȃ��̂Ńo�b�t�@���
	} else {
		// duplicate
		nd->u.scr.label_list     = label_dup;	// ���x���f�[�^���L
		nd->u.scr.label_list_num = label_dupnum;
	}

	// �C�x���g�p���x���f�[�^�̃G�N�X�|�[�g
	if(fail == 0)
		fail = npc_exportlabel_data(nd);

	nd->u.scr.nexttimer = -1;
	nd->u.scr.timerid   = -1;

	if(fail) {
		// �f�[�^�𐳏�ɕ��A�ł��Ȃ��̂ŃT�[�o�I��
		exit(1);
	}

	return 0;
}

/*==========================================
 * function�s���
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

	// �X�N���v�g�̉��
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

	// �����g��Ȃ��̂Ńo�b�t�@���
	aFree(srcbuf);

	if(script_is_error(script)) {
		// script parse error
		return 0;
	}
	if(script == NULL) {
		// �R�[�h�������Ȃ�function�͕s���ƌ��Ȃ��ēo�^���Ȃ�
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
 * mob�s���
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

	// �����̌��`�F�b�N
	if(sscanf(w1,"%23[^,],%d,%d,%d,%d%n",mapname,&x,&y,&xs,&ys,&n) != 5 || w1[n] != 0 ||
	   sscanf(w4,"%d,%d,%d,%d,%4095[^\n]",&class_,&num,&delay1,&delay2,eventtemp) < 4)
	{
		printf("bad monster declaration : %s line %d\a\n",w3,lines);
		return 0;
	}
	m = map_mapname2mapid(mapname);
	if(m < 0)
		return 0;	// assign����ĂȂ�MAP�Ȃ̂ŏI��

	if(!mobdb_exists(class_)) {
		// ���������ID�ُ�͒��ӂ𑣂�
		printf("npc_monster bad class: %d line %d\a\n",class_,lines);
		return 0;
	}

	id = mobdb_search(class_);

	if(eventtemp[0]) {
		char *p;
		// ,,<guild_id> �̂悤�ɃC�x���g�w�薳���̃p�^�[��������̂�sscanf���Ȃ�
		if((p = strchr(eventtemp,',')) != NULL) {
			*p = 0;
			guild_id = atoi(p+1);
		}
		p = eventtemp;
		if(*p) {
			if(isdigit((unsigned char)p[0]) && p[1] == 0) {
				// ����1���������̏ꍇ�̓C�x���g�w�薳���Ƃ��Ĉ����i�������Ȃ��j
				;
			} else {
				strncpy(eventname,p,76);
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

		md->group_id = 0;
		md->title[23] = '\0';	// froce \0 terminal

		if(id->mode & MD_ITEMLOOT)
			md->lootitem = (struct item *)aCalloc(LOOTITEM_SIZE,sizeof(struct item));
		else
			md->lootitem = NULL;

		if(eventname[0]) {
			memcpy(md->npc_event,eventname,76);
			md->npc_event[75] = '\0';	// froce \0 terminal
		}
		md->bl.type = BL_MOB;
		map_addiddb(&md->bl);

		if(mob_spawn(md->bl.id)) {
			// �o�����s�A���W���w�肳��Ă���Ȃ���͂̃Z�����`�F�b�N
			if(md->x0 != 0 && md->y0 != 0) {
				int x0 = md->x0 - md->xs;
				int y0 = md->y0 - md->ys;
				int x1 = md->x0 + md->xs;
				int y1 = md->y0 + md->ys;

				if(map_searchfreecell(NULL, md->m, x0, y0, x1, y1) <= 0) {
					// �N���\�Z�����S���Ȃ��̂ō폜����
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
				// �ďo������MVP�{�X�Ȃ�ʖʋ��p�ɓo�^
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
 * �}�b�v�t���O�s�̉��
 *------------------------------------------
 */
static int npc_parse_mapflag(const char *w1,const char *w2,const char *w3,const char *w4,int lines)
{
	int m;
	char mapname[4096];

	// �����̌��`�F�b�N
	if(sscanf(w1,"%4095[^,]",mapname) != 1 || strlen(w1) != strlen(mapname)) {
		printf("bad mapflag declaration : %s line %d\a\n",w3,lines);
		return 0;
	}

	m = map_mapname2mapid(mapname);
	if(m < 0)
		return 0;	// assign����ĂȂ�MAP�Ȃ̂ŏI��

	if(npc_set_mapflag(m, w3, w4) < 0) {
		printf("npc_parse_mapflag: mapflag \"%s\" not exist!! line %d\a\n",w3,lines);
	}
	return 0;
}

/*==========================================
 * �}�b�v�t���O�̐ݒ�
 *------------------------------------------
 */
int npc_set_mapflag(int m,const char *w3,const char *w4)
{
	if(m < 0 || m >= map_num)
		return 0;

	if (strcasecmp(w3,"nosave") == 0) {
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
	} else if (strcasecmp(w3,"nomemo") == 0) {
		map[m].flag.nomemo ^= 1;
	} else if (strcasecmp(w3,"noteleport") == 0) {
		map[m].flag.noteleport ^= 1;
	} else if (strcasecmp(w3,"noportal") == 0) {
		map[m].flag.noportal ^= 1;
	} else if (strcasecmp(w3,"noreturn") == 0) {
		map[m].flag.noreturn ^= 1;
	} else if (strcasecmp(w3,"monster_noteleport") == 0) {
		map[m].flag.monster_noteleport ^= 1;
	} else if (strcasecmp(w3,"nobranch") == 0) {
		map[m].flag.nobranch ^= 1;
	} else if (strcasecmp(w3,"nopenalty") == 0) {
		map[m].flag.nopenalty ^= 1;
	} else if (strcasecmp(w3,"pvp") == 0) {
		map[m].flag.pvp ^= 1;
	} else if (strcasecmp(w3,"pvp_noparty") == 0) {
		map[m].flag.pvp_noparty ^= 1;
	} else if (strcasecmp(w3,"pvp_noguild") == 0) {
		map[m].flag.pvp_noguild ^= 1;
	} else if (strcasecmp(w3,"pvp_nightmaredrop") == 0) {
		if (npc_set_mapflag_sub(m, w4, MF_PVP_NIGHTMAREDROP))
			map[m].flag.pvp_nightmaredrop = 1;
	} else if (strcasecmp(w3,"pvp_nocalcrank") == 0) {
		map[m].flag.pvp_nocalcrank ^= 1;
	} else if (strcasecmp(w3,"gvg") == 0) {
		map[m].flag.gvg ^= 1;
	} else if (strcasecmp(w3,"gvg_noparty") == 0) {
		map[m].flag.gvg_noparty ^= 1;
	} else if (strcasecmp(w3,"gvg_nightmaredrop") == 0) {
		if (npc_set_mapflag_sub(m, w4, MF_GVG_NIGHTMAREDROP))
			map[m].flag.gvg_nightmaredrop = 1;
	} else if (strcasecmp(w3,"nozenypenalty") == 0) {
		map[m].flag.nozenypenalty ^= 1;
	} else if (strcasecmp(w3,"notrade") == 0) {
		map[m].flag.notrade ^= 1;
	} else if (strcasecmp(w3,"noskill") == 0) {
		map[m].flag.noskill ^= 1;
	} else if (strcasecmp(w3,"noabra") == 0) {
		map[m].flag.noabra ^= 1;
	} else if (strcasecmp(w3,"nodrop") == 0) {
		map[m].flag.nodrop ^= 1;
	} else if (strcasecmp(w3,"snow") == 0) {
		map[m].flag.snow ^= 1;
	} else if (strcasecmp(w3,"fog") == 0) {
		map[m].flag.fog ^= 1;
	} else if (strcasecmp(w3,"sakura") == 0) {
		map[m].flag.sakura ^= 1;
	} else if (strcasecmp(w3,"leaves") == 0) {
		map[m].flag.leaves ^= 1;
	} else if (strcasecmp(w3,"rain") == 0) {
		map[m].flag.rain ^= 1;
	} else if (strcasecmp(w3,"fireworks") == 0) {
		map[m].flag.fireworks ^= 1;
	} else if (strcasecmp(w3,"cloud1") == 0) {
		map[m].flag.cloud1 ^= 1;
	} else if (strcasecmp(w3,"cloud2") == 0) {
		map[m].flag.cloud2 ^= 1;
	} else if (strcasecmp(w3,"cloud3") == 0) {
		map[m].flag.cloud3 ^= 1;
	} else if (strcasecmp(w3,"base_exp_rate") == 0) {
		map[m].flag.base_exp_rate = atoi(w4);
	} else if (strcasecmp(w3,"job_exp_rate") == 0) {
		map[m].flag.job_exp_rate = atoi(w4);
	} else if (strcasecmp(w3,"pk") == 0) {
		map[m].flag.pk ^= 1;
	} else if (strcasecmp(w3,"pk_noparty") == 0) {
		map[m].flag.pk_noparty ^= 1;
	} else if (strcasecmp(w3,"pk_noguild") == 0) {
		map[m].flag.pk_noguild ^= 1;
	} else if (strcasecmp(w3,"pk_nightmaredrop") == 0) {
		if (npc_set_mapflag_sub(m, w4, MF_PK_NIGHTMAREDROP))
			map[m].flag.pk_nightmaredrop = 1;
	} else if (strcasecmp(w3,"pk_nocalcrank") == 0) {
		map[m].flag.pk_nocalcrank ^= 1;
	} else if (strcasecmp(w3,"noicewall") == 0) {
		map[m].flag.noicewall ^= 1;
	} else if (strcasecmp(w3,"turbo") == 0) {
		map[m].flag.turbo ^= 1;
	} else if (strcasecmp(w3,"norevive") == 0) {
		map[m].flag.norevive ^= 1;
	} else if (strcasecmp(w3,"nocommand") == 0) {
		map[m].flag.nocommand = atoi(w4);
	} else if (strcasecmp(w3,"nojump") == 0) {
		map[m].flag.nojump ^= 1;
	} else if (strcasecmp(w3,"nocostume") == 0) {
		map[m].flag.nocostume ^= 1;
	} else if (strcasecmp(w3,"town") == 0) {
		map[m].flag.town ^= 1;
	} else if (strcasecmp(w3,"damage_rate") == 0) {
		map[m].flag.damage_rate = atoi(w4);
	} else {
		return -1;	// ���݂��Ȃ��}�b�v�t���O�Ȃ̂ŃG���[
	}
	return 0;
}

/*==========================================
 * �i�C�g���A���[�h�̐ݒ�
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
 * NPC�t�@�C�����
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

		// �s�v�ȃX�y�[�X��^�u�̘A���͋l�߂�
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

		// line�Ɋ܂܂��R�����g�������X�L�b�v
		lp = npc_skip_line(line, &comment_flag);
		if(lp == NULL)
			continue;

		// �ŏ��̓^�u��؂�Ń`�F�b�N���Ă݂āA�_���Ȃ�X�y�[�X��؂�Ŋm�F
		if((count = sscanf(lp,"%4095[^\t]\t%4095[^\t]\t%4095[^\t\r\n]\t%n%4095[^\t\r\n]",w1,w2,w3,&w4pos,w4)) < 3 &&
		   (count = sscanf(lp,"%4095s%4095s%4095s%n%4095s",w1,w2,w3,&w4pos,w4)) < 3)
		{
			script_error(lp, filepath, lines, "npc file syntax error", lp+w4pos);
			break;
		}

		// �}�b�v���Ƃ��ċL�q����Ă��邩�m�F
		// MAP�̑��݃`�F�b�N���̂͊eparser�ōs��
		if(strcmp(w1,"-") != 0 && strcasecmp(w1,"function") != 0) {
			size_t len;
			char mapname[4096] = "";
			sscanf(w1,"%4095[^,]",mapname);
			len = strlen(mapname);
			if(len <= 4 || len > 24 || strcmp(mapname+len-4,".gat") != 0) {
				script_error(lp, filepath, lines, "npc file syntax error", lp);
				break;
			}
		}

		if (strcasecmp(w2,"warp") == 0 && count > 3) {
			ret = npc_parse_warp(w1,w2,w3,w4,lines);
		} else if ((strcasecmp(w2,"shop") == 0 || strcasecmp(w2,"pointshop") == 0 || strcasecmp(w2,"market") == 0) && count > 3) {
			ret = npc_parse_shop(w1,w2,w3,w4,lines);
		} else if ((i = 0, sscanf(w2,"substore%n",&i), (i > 0 && w2[i] == '(')) && count > 3) {
			ret = npc_parse_shop(w1,w2,w3,w4,lines);
		} else if (strstr(w2,"script") && count > 3) {
			if(strcasecmp(w1,"function") == 0) {
				ret = npc_parse_function(w1,w2,w3,w4,line+w4pos,fp,&lines,filepath);
			} else {
				ret = npc_parse_script(w1,w2,w3,w4,line+w4pos,fp,&lines,filepath);
			}
		} else if ((i = 0, sscanf(w2,"duplicate%n",&i), (i > 0 && w2[i] == '(')) && count > 3) {
			ret = npc_parse_script(w1,w2,w3,w4,line+w4pos,fp,&lines,filepath);
		} else if (strcasecmp(w2,"monster") == 0 && count > 3) {
			ret = npc_parse_mob(w1,w2,w3,w4,lines);
		} else if (strcasecmp(w2,"mapflag") == 0 && count >= 3) {
			ret = npc_parse_mapflag(w1,w2,w3,w4,lines);
		} else {
			script_error(lp, filepath, lines, "npc file syntax error", lp+strlen(w1)+1);
			break;
		}
		if(ret) {
			// �G���[�������̓t�@�C���̉�͏I��
			break;
		}
	}
	fclose(fp);

	if(comment_flag) {
		// script�u���b�N�O���Ń}���`���C���R�����g����Y��
		printf("Missing */ on %s\a\n", filepath);
	} else {
		printf("\r");
	}
	parse_script_line_curly(NULL, 0, 0);	// script�u���b�N������comment_flag��������

	return 1;
}

/*==========================================
 * �I��
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
					// �������Ȃ�MOB�Ƃ��Ĉ���
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
 * npc������
 *------------------------------------------
 */
int do_init_npc(void)
{
	int number = 0;
	struct npc_src_list *nsl;
	time_t now;

	ev_db = strdb_init(76);
	npcname_db = strdb_init(50);

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

