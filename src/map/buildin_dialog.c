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
#include <stdarg.h>

#include "db.h"
#include "timer.h"
#include "malloc.h"
#include "mmo.h"
#include "nullpo.h"
#include "utils.h"

#include "map.h"
#include "clif.h"
#include "pc.h"
#include "script.h"
#include "script_internal.h"
#include "npc.h"
#include "unit.h"
#include "status.h"
#include "battle.h"

/* Split from script.c (Issue #61) */

/*==========================================
 *
 *------------------------------------------
 */
int buildin_mes(struct script_state *st)
{
	char *str;

	str = conv_str(st,& (st->stack->stack_data[st->start+2]));
	if(*str)
		clif_scriptmes(script_rid2sd(st),st->oid,str);
	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int buildin_messize(struct script_state *st)
{
	int height, width;

	height = conv_num(st,& (st->stack->stack_data[st->start+2]));
	width = conv_num(st,& (st->stack->stack_data[st->start+3]));
	if(height && width)
		clif_scriptmessize(script_rid2sd(st),st->oid,height,width);
	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int buildin_mespos(struct script_state *st)
{
	int x, y;

	x = conv_num(st,& (st->stack->stack_data[st->start+2]));
	y = conv_num(st,& (st->stack->stack_data[st->start+3]));
	if(x && y)
		clif_scriptmespos(script_rid2sd(st),st->oid,x,y);
	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int buildin_mesalign(struct script_state *st)
{
	char align;

	align = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if(align)
		clif_scriptmesalign(script_rid2sd(st),st->oid,align);
	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int buildin_next(struct script_state *st)
{
	st->state=STOP;
	clif_scriptnext(script_rid2sd(st),st->oid);
	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int buildin_close(struct script_state *st)
{
	st->state=END;
	clif_scriptclose(script_rid2sd(st),st->oid);
	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int buildin_close2(struct script_state *st)
{
	st->state=STOP;
	clif_scriptclose(script_rid2sd(st),st->oid);
	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int buildin_clear(struct script_state *st)
{
	clif_scriptclear(script_rid2sd(st),st->oid);
	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int buildin_menu(struct script_state *st)
{
	int i;
	struct map_session_data *sd = script_rid2sd(st);

	if(sd == NULL) {	// キャンセル扱いにする
		st->state = END;
		return 0;
	}

	if(sd->state.menu_or_input == 0) {
		char *buf;
		st->state = RERUNLINE;
		sd->state.menu_or_input = 1;

		if((st->end - st->start - 2) % 2 == 1) {
			// 引数の数が奇数なのでエラー扱い
			printf("buildin_menu: illigal argument count(%d).\n", st->end - st->start - 2);
			sd->state.menu_or_input = 0;
			st->state = END;
			return 0;
		}
		if(st->end > st->start+3) {
			size_t len = 0;
			for(i=st->start+2; i<st->end; i+=2) {
				conv_str(st,& (st->stack->stack_data[i]));
				len += strlen(st->stack->stack_data[i].u.str) + 1;
			}
			buf = (char *)aCalloc(len + 1, sizeof(char));
			for(i=st->start+2; i<st->end; i+=2) {
				if(st->stack->stack_data[i].u.str[0]) {
					if(buf[0]) {
						strcat(buf,":");
					}
					strcat(buf,st->stack->stack_data[i].u.str);
				}
			}
			clif_scriptmenu(sd,st->oid,buf);
			aFree(buf);
		} else {
			buf = conv_str(st,& (st->stack->stack_data[st->start+2]));
			clif_scriptmenu(sd,st->oid,buf);
		}
	} else if(sd->npc_menu <= 0 || sd->npc_menu == 0xff) {	// invalid or cancel
		sd->state.menu_or_input = 0;
		st->state = END;
	} else {	// goto動作
		int count = 0;
		sd->state.menu_or_input = 0;
		// 空文字と : のメニュー補正
		for(i=st->start+2; count < sd->npc_menu && i<st->end; i+=2) {
			char *p  = conv_str(st,& (st->stack->stack_data[i]));
			char *np = NULL;
			count++;
			if(*p == '\0') {
				sd->npc_menu++;
				continue;
			}
			while(count <= sd->npc_menu && (np = strchr(p,':')) != NULL) {
				count++;
				if(np == p) {
					sd->npc_menu++;
				}
				p = np + 1;
			}
		}
		if(count >= sd->npc_menu) {
			pc_setreg(sd,add_str("@menu"),sd->npc_menu);
			if(st->stack->stack_data[i-1].type != C_POS) {
				printf("buildin_menu: not label !\n");
				st->state = END;
				return 0;
			}
			st->pos   = conv_num(st,& (st->stack->stack_data[i-1]));
			st->state = GOTO;
		} else {
			// 不正な値なのでキャンセル扱い
			st->state = END;
		}
	}
	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int buildin_input(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int num;
	char *name;
	char postfix;

	if(sd == NULL) {	// エラー扱いにする
		st->state = END;
		return 0;
	}
	if(st->stack->stack_data[st->start+2].type != C_NAME) {
		// 変数ではないのでエラー扱い
		printf("buildin_input: param not name\n");
		st->state = END;
		return 0;
	}
	num     = st->stack->stack_data[st->start+2].u.num;
	name    = get_str(num&0x00ffffff);
	postfix = name[strlen(name)-1];

	if(sd->state.menu_or_input) {
		sd->state.menu_or_input=0;
		if(postfix == '$')
			set_reg(st,sd,num,name,(void*)sd->npc_str,st->stack->stack_data[st->start+2].ref);
		else
			set_reg(st,sd,num,name,INT2PTR(sd->npc_amount),st->stack->stack_data[st->start+2].ref);
	} else {
		st->state=RERUNLINE;
		if(postfix == '$')
			clif_scriptinputstr(sd,st->oid);
		else
			clif_scriptinput(sd,st->oid);
		sd->state.menu_or_input=1;
	}
	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int buildin_cutin(struct script_state *st)
{
	char *str = conv_str(st,& (st->stack->stack_data[st->start+2]));
	int type  = conv_num(st,& (st->stack->stack_data[st->start+3]));

	clif_cutin(script_rid2sd(st),str,type);

	return 0;
}


/*==========================================
 *
 *------------------------------------------
 */
int buildin_viewpoint(struct script_state *st)
{
	int type,x,y,id,color;

	type=conv_num(st,& (st->stack->stack_data[st->start+2]));
	x=conv_num(st,& (st->stack->stack_data[st->start+3]));
	y=conv_num(st,& (st->stack->stack_data[st->start+4]));
	id=conv_num(st,& (st->stack->stack_data[st->start+5]));
	color=conv_num(st,& (st->stack->stack_data[st->start+6]));

	clif_viewpoint(script_rid2sd(st),st->oid,type,x,y,id,color);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int buildin_debugmes(struct script_state *st)
{
	char *str = conv_str(st,& (st->stack->stack_data[st->start+2]));

	printf("script debug : %d %d : %s\n",st->rid,st->oid,str);
	return 0;
}

/*==========================================
 * コメント欄にメッセージ表示
 *------------------------------------------
 */
int buildin_dispbottom(struct script_state *st)
{
	struct map_session_data *sd=script_rid2sd(st);
	char *message;

	message=conv_str(st,& (st->stack->stack_data[st->start+2]));
	if(sd)
		clif_disp_onlyself(sd->fd,message);
	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int buildin_select(struct script_state *st)
{
	int i;
	struct map_session_data *sd = script_rid2sd(st);

	if(sd == NULL) {	// キャンセル扱いにする
		st->state = END;
		return 0;
	}

	if(sd->state.menu_or_input == 0) {
		char *buf;
		st->state = RERUNLINE;
		sd->state.menu_or_input = 1;

		if(st->end > st->start+3) {
			size_t len = 0;
			for(i=st->start+2; i<st->end; i++) {
				conv_str(st,& (st->stack->stack_data[i]));
				len += strlen(st->stack->stack_data[i].u.str) + 1;
			}
			buf = (char *)aCalloc(len + 1, sizeof(char));
			for(i=st->start+2; i<st->end; i++) {
				if(st->stack->stack_data[i].u.str[0]) {
					if(buf[0]) {
						strcat(buf,":");
					}
					strcat(buf,st->stack->stack_data[i].u.str);
				}
			}
			clif_scriptmenu(sd,st->oid,buf);
			aFree(buf);
		} else {
			buf = conv_str(st,& (st->stack->stack_data[st->start+2]));
			clif_scriptmenu(sd,st->oid,buf);
		}
	} else if(sd->npc_menu <= 0 || sd->npc_menu == 0xff) {	// invalid or cancel
		sd->state.menu_or_input = 0;
		st->state = END;
	} else {
		int count = 0;
		sd->state.menu_or_input = 0;
		// 空文字と : のメニュー補正
		for(i=st->start+2; count < sd->npc_menu && i<st->end; i++) {
			char *p  = conv_str(st,& (st->stack->stack_data[i]));
			char *np = NULL;
			count++;
			if(*p == '\0') {
				sd->npc_menu++;
				continue;
			}
			while(count <= sd->npc_menu && (np = strchr(p,':')) != NULL) {
				count++;
				if(np == p) {
					sd->npc_menu++;
				}
				p = np + 1;
			}
		}
		if(count >= sd->npc_menu) {
			pc_setreg(sd,add_str("@menu"),sd->npc_menu);
			push_val(st->stack,C_INT,sd->npc_menu);
		} else {
			// 不正な値なのでキャンセル扱い
			st->state = END;
		}
	}
	return 0;
}

/*==========================================
 * NPCイベント表示
 *------------------------------------------
 */
int buildin_showevent(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	struct npc_data *nd;
	int state, type = 0;

	if(st->end>st->start+4)
		nd = npc_name2id(conv_str(st,& (st->stack->stack_data[st->start+4])));
	else
		nd = map_id2nd(st->oid);

	if(nd == NULL) {
		printf("buildin_showevent: npc not found\n");
		return 0;
	}

	state = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if(st->end>st->start+3)
		type = conv_num(st,& (st->stack->stack_data[st->start+3]));

#if PACKETVER >= 20120410
	if(state < 0 || (state > 8 && state != 9999) || state == 7)
		state = 9999;
#else
	if(state < 0 || state > 7)
		state = 0;
	else
		state = state + 1;
#endif

	if(type < 0 || type > 3)
		return 0;

	clif_showevent(sd,&nd->bl,state,type);

	return 0;
}

/*==========================================
 * 詠唱バー表示
 *------------------------------------------
 */
int buildin_progressbar(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	unsigned int tick = gettick();

	if(sd == NULL) {
		st->state = END;
		return 0;
	}

	if(sd->progressbar.tick == 0) {
		unsigned int second, color = 0;

		second = conv_num(st,& (st->stack->stack_data[st->start+2]));
		if(st->end>st->start+3)
			color = (unsigned int)conv_num(st,&(st->stack->stack_data[st->start+3]));

		if(second > 0) {
			st->state = RERUNLINE;
			sd->progressbar.npc_id = st->oid;
			sd->progressbar.tick = tick + second * 1000;
			clif_progressbar(sd, color, second);
		}
	} else {
		if(tick < sd->progressbar.tick) {
			// 経過時間が不正
			st->state = END;
		}

		// 続行
		sd->progressbar.npc_id = 0;
		sd->progressbar.tick   = 0;
		npc_timeout_start(sd);
		if(sd->npc_dynamic_id == sd->npc_id)
			npc_dynamicnpc_start(sd);
	}

	return 0;
}

/*==========================================
 * 頭上にメッセージ表示
 *------------------------------------------
 */
int buildin_showmessage(struct script_state *st)
{
	struct npc_data *nd;
	char *mes;

	mes  = conv_str(st,& (st->stack->stack_data[st->start+2]));
	if( st->end > st->start+3 )
		nd = npc_name2id(conv_str(st,& (st->stack->stack_data[st->start+3])));
	else
		nd = map_id2nd(st->oid);

	if(nd) {
		clif_showscript(&nd->bl,mes);
	} else {
		struct block_list *bl = map_id2bl(st->rid);
		if(bl)
			clif_showscript(bl,mes);
	}
	return 0;
}

/*==========================================
 * デジタルタイマー表示
 *------------------------------------------
 */
int buildin_showdigit(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int type = 0;
	int value;

	nullpo_retr(0, sd);

	value = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if( st->end > st->start+3 )
		type = conv_num(st,& (st->stack->stack_data[st->start+3]));

	if(type < 0 || type > 3)
		return 0;

	clif_showdigit(sd, (unsigned char)type, value);
	return 0;
}
