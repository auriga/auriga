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
#include "socket.h"
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
#include "chat.h"
#include "mob.h"
#include "skill.h"
#include "status.h"
#include "unit.h"
#include "path.h"
#include "battle.h"
#include "intif.h"
#include "memorial.h"
#include "buyingstore.h"

/* Split from script.c (Issue #61) */

/*==========================================
 * NPCのID取得
 *------------------------------------------
 */
int buildin_getnpcid(struct script_state *st)
{
	int num, id = -1;
	struct npc_data *nd;

	num = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if( st->end > st->start+3 )
		nd = npc_name2id(conv_str(st,& (st->stack->stack_data[st->start+3])));
	else
		nd = map_id2nd(st->oid);

	if(nd) {
		switch(num) {
			case 0: id = nd->bl.id; break;
		}
	}
	push_val(st->stack,C_INT,id);

	return 0;
}

/*==========================================
 * イベント実行
 *------------------------------------------
 */
int buildin_doevent(struct script_state *st)
{
	char *event = conv_str(st,& (st->stack->stack_data[st->start+2]));

	npc_event(script_rid2sd(st),event);
	return 0;
}

/*==========================================
 * NPC主体イベント実行
 *------------------------------------------
 */
int buildin_donpcevent(struct script_state *st)
{
	char *event= conv_str(st,& (st->stack->stack_data[st->start+2]));

	npc_event_do(event);
	return 0;
}

/*==========================================
 * イベントタイマー追加
 *------------------------------------------
 */
int buildin_addtimer(struct script_state *st)
{
	int tick    = conv_num(st,& (st->stack->stack_data[st->start+2]));
	char *event = conv_str(st,& (st->stack->stack_data[st->start+3]));

	pc_addeventtimer(script_rid2sd(st),tick,event);
	return 0;
}

/*==========================================
 * イベントタイマー削除
 *------------------------------------------
 */
int buildin_deltimer(struct script_state *st)
{
	char *event = conv_str(st,& (st->stack->stack_data[st->start+2]));

	pc_deleventtimer(script_rid2sd(st),event);
	return 0;
}

/*==========================================
 * イベントタイマーのカウント値追加
 *------------------------------------------
 */
int buildin_addtimercount(struct script_state *st)
{
	char *event = conv_str(st,& (st->stack->stack_data[st->start+2]));
	int tick    = conv_num(st,& (st->stack->stack_data[st->start+3]));

	pc_addeventtimercount(script_rid2sd(st),event,tick);
	return 0;
}

/*==========================================
 * イベントタイマーの残り時間取得
 *------------------------------------------
 */
int buildin_gettimerdiff(struct script_state *st)
{
	char *event;
	int ret;

	event = conv_str(st,& (st->stack->stack_data[st->start+2]));
	ret = pc_geteventtimerdiff(script_rid2sd(st),event);

	push_val(st->stack,C_INT,ret);
	return 0;
}

/*==========================================
 * NPCタイマー初期化
 *------------------------------------------
 */
int buildin_initnpctimer(struct script_state *st)
{
	struct npc_data *nd;

	if( st->end > st->start+2 )
		nd = npc_name2id(conv_str(st,& (st->stack->stack_data[st->start+2])));
	else
		nd = map_id2nd(st->oid);

	npc_settimerevent_tick(nd,0);
	npc_timerevent_start(nd);
	return 0;
}

/*==========================================
 * NPCタイマー開始
 *------------------------------------------
 */
int buildin_startnpctimer(struct script_state *st)
{
	struct npc_data *nd;

	if( st->end > st->start+2 )
		nd = npc_name2id(conv_str(st,& (st->stack->stack_data[st->start+2])));
	else
		nd = map_id2nd(st->oid);

	npc_timerevent_start(nd);
	return 0;
}

/*==========================================
 * NPCタイマー停止
 *------------------------------------------
 */
int buildin_stopnpctimer(struct script_state *st)
{
	struct npc_data *nd;

	if( st->end > st->start+2 )
		nd = npc_name2id(conv_str(st,& (st->stack->stack_data[st->start+2])));
	else
		nd = map_id2nd(st->oid);

	npc_timerevent_stop(nd);
	return 0;
}

/*==========================================
 * NPCタイマー情報取得
 *------------------------------------------
 */
int buildin_getnpctimer(struct script_state *st)
{
	struct npc_data *nd;
	int type, val = 0;

	type = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if(st->end > st->start+3)
		nd = npc_name2id(conv_str(st,& (st->stack->stack_data[st->start+3])));
	else
		nd = map_id2nd(st->oid);

	if(nd) {
		switch(type){
			case 0: val = npc_gettimerevent_tick(nd);       break;
			case 1: val = (nd->u.scr.nexttimer >= 0)? 1: 0; break;
			case 2: val = nd->u.scr.timeramount;            break;
		}
	}
	push_val(st->stack,C_INT,val);
	return 0;
}

/*==========================================
 * NPCタイマー値設定
 *------------------------------------------
 */
int buildin_setnpctimer(struct script_state *st)
{
	int tick;
	struct npc_data *nd;

	tick=conv_num(st,& (st->stack->stack_data[st->start+2]));
	if( st->end > st->start+3 )
		nd = npc_name2id(conv_str(st,& (st->stack->stack_data[st->start+3])));
	else
		nd = map_id2nd(st->oid);

	npc_settimerevent_tick(nd,tick);
	return 0;
}


/*==========================================
 * NPCの有効化
 *------------------------------------------
 */
int buildin_enablenpc(struct script_state *st)
{
	struct npc_data *nd;

	if(st->end > st->start+2) {
		char *name = conv_str(st,& (st->stack->stack_data[st->start+2]));
		nd = npc_name2id(name);
		if(nd == NULL) {
			return 0;
		}
	} else {
		nd = map_id2nd(st->oid);
		if(nd == NULL) {
			printf("buildin_enablenpc: fatal error: npc not attached\n");
			return 0;
		}
	}
	npc_enable(nd->exname,1);
	return 0;
}

/*==========================================
 * NPCの無効化
 *------------------------------------------
 */
int buildin_disablenpc(struct script_state *st)
{
	struct npc_data *nd;

	if(st->end > st->start+2) {
		char *name = conv_str(st,& (st->stack->stack_data[st->start+2]));
		nd = npc_name2id(name);
		if(nd == NULL) {
			return 0;
		}
	} else {
		nd = map_id2nd(st->oid);
		if(nd == NULL) {
			printf("buildin_disablenpc: fatal error: npc not attached\n");
			return 0;
		}
	}
	npc_enable(nd->exname,0);
	return 0;
}

/*==========================================
 * 隠れているNPCの表示
 *------------------------------------------
 */
int buildin_hideoffnpc(struct script_state *st)
{
	struct npc_data *nd;

	if(st->end > st->start+2) {
		char *name = conv_str(st,& (st->stack->stack_data[st->start+2]));
		nd = npc_name2id(name);
		if(nd == NULL) {
			return 0;
		}
	} else {
		nd = map_id2nd(st->oid);
		if(nd == NULL) {
			printf("buildin_hideoffnpc: fatal error: npc not attached\n");
			return 0;
		}
	}
	npc_enable(nd->exname,2);
	return 0;
}

/*==========================================
 * NPCをハイディング
 *------------------------------------------
 */
int buildin_hideonnpc(struct script_state *st)
{
	struct npc_data *nd;

	if(st->end > st->start+2) {
		char *name = conv_str(st,& (st->stack->stack_data[st->start+2]));
		nd = npc_name2id(name);
		if(nd == NULL) {
			return 0;
		}
	} else {
		nd = map_id2nd(st->oid);
		if(nd == NULL) {
			printf("buildin_hideonnpc: fatal error: npc not attached\n");
			return 0;
		}
	}
	npc_enable(nd->exname,4);
	return 0;
}

/*==========================================
 * 特定のユーザーの視界内NPCの表示
 *------------------------------------------
 */
int buildin_cloakoffnpc(struct script_state *st)
{
	struct npc_data *nd;
	struct map_session_data *sd = script_rid2sd(st);

	if(st->end > st->start+2) {
		char *name = conv_str(st,& (st->stack->stack_data[st->start+2]));
		nd = npc_name2id(name);
		if(nd == NULL) {
			return 0;
		}
	} else {
		nd = map_id2nd(st->oid);
		if(nd == NULL) {
			printf("buildin_cloakoffnpc: fatal error: npc not attached\n");
			return 0;
		}
	}

	if(sd) {
		// 表示用に一時退避
		int flag = nd->option;
		int i;
		nd->option = OPTION_NOTHING;
		clif_changeoption_single(&nd->bl, sd);
		nd->option = flag;
		for(i=0; i < MAX_CLOAKEDNPC; i++) {
			if(sd->cloaked_npc[i] == nd->bl.id)
				break;
		}
		if(i == MAX_CLOAKEDNPC) {
			for(i=0; i < MAX_CLOAKEDNPC; i++) {
				if(sd->cloaked_npc[i] == 0)
					break;
			}
		}
		if(i == MAX_CLOAKEDNPC) {
			printf("buildin_cloakoffnpc: fatal error: max cloakednpc list\n");
			return 0;
		}
		sd->cloaked_npc[i] = nd->bl.id;
	}
	else	// アタッチがない場合はNPC情報書き換え
		nd->option &= ~OPTION_CLOAKING;

	return 0;
}

/*==========================================
 * 特定のユーザーの視界内NPCをクローキング
 *------------------------------------------
 */
int buildin_cloakonnpc(struct script_state *st)
{
	struct npc_data *nd;
	struct map_session_data *sd = NULL;

	if(st->rid)	// クローキング時はアタッチがなくても許容する
		sd = script_rid2sd(st);

	if(st->end > st->start+2) {
		char *name = conv_str(st,& (st->stack->stack_data[st->start+2]));
		nd = npc_name2id(name);
		if(nd == NULL) {
			return 0;
		}
	} else {
		nd = map_id2nd(st->oid);
		if(nd == NULL) {
			printf("buildin_cloakonnpc: fatal error: npc not attached\n");
			return 0;
		}
	}

	if(sd) {
		// 表示用に一時退避
		int flag = nd->option;
		int i;
		nd->option |= OPTION_CLOAKING;
		clif_changeoption_single(&nd->bl, sd);
		nd->option = flag;
		for(i=0; i < MAX_CLOAKEDNPC; i++) {
			if(sd->cloaked_npc[i] == nd->bl.id) {
				sd->cloaked_npc[i] = 0;
				break;
			}
		}
	}
	else	// アタッチがない場合はNPC情報書き換え
		nd->option |= OPTION_CLOAKING;

	return 0;
}

/*==========================================
 * npcチャット作成
 *------------------------------------------
 */
int buildin_waitingroom(struct script_state *st)
{
	char *name;
	const char *ev = "";
	int limit, trigger = 0,pub=1;
	int zeny=0,lowlv=0,highlv=MAX_LEVEL;
	unsigned int job = 0xFFFFFFFF;
	int upper = 0;

	name  = conv_str(st,& (st->stack->stack_data[st->start+2]));
	limit = conv_num(st,& (st->stack->stack_data[st->start+3]));
	if(limit == 0)
		pub = 3;

	if(st->end > st->start+4) {
		ev = conv_str(st,& (st->stack->stack_data[st->start+4]));
	}
	if(st->end > st->start+5) {
		trigger = conv_num(st,& (st->stack->stack_data[st->start+5]));
	}
	if(st->end > st->start+8) {
		zeny   = conv_num(st,& (st->stack->stack_data[st->start+6]));
		lowlv  = conv_num(st,& (st->stack->stack_data[st->start+7]));
		highlv = conv_num(st,& (st->stack->stack_data[st->start+8]));
	}
	if(st->end > st->start+10) {
		job   = (unsigned int)conv_num(st,& (st->stack->stack_data[st->start+9]));
		upper = conv_num(st,& (st->stack->stack_data[st->start+10]));
	}
	chat_createnpcchat(map_id2nd(st->oid),
		limit,pub,trigger,name,(int)(strlen(name)+1),ev,zeny,lowlv,highlv,job,upper);
	return 0;
}

/*==========================================
 * NPCがオープンチャットで発言
 *------------------------------------------
 */
int buildin_globalmes(struct script_state *st)
{
	char *mes, *name = NULL;

	mes = conv_str(st,& (st->stack->stack_data[st->start+2]));

	if(st->end > st->start+3) {	// NPC名の取得(123#456)
		name = conv_str(st,& (st->stack->stack_data[st->start+3]));
	} else {
		struct npc_data *nd = map_id2nd(st->oid);
		if(nd)
			name = nd->exname;
	}
	if(name)
		npc_globalmessage(name,mes);	// グローバルメッセージ送信

	return 0;
}

/*==========================================
 * npcチャット削除
 *------------------------------------------
 */
int buildin_delwaitingroom(struct script_state *st)
{
	struct npc_data *nd;

	if( st->end > st->start+2 )
		nd = npc_name2id(conv_str(st,& (st->stack->stack_data[st->start+2])));
	else
		nd = map_id2nd(st->oid);
	chat_deletenpcchat(nd);
	return 0;
}

/*==========================================
 * チャットから指定プレイヤーを蹴り出す
 *------------------------------------------
 */
int buildin_kickwaitingroom(struct script_state *st)
{
	struct map_session_data *sd;

	sd = map_id2sd(conv_num(st,& (st->stack->stack_data[st->start+2])));

	if(sd && sd->chatID)
		chat_leavechat(sd,1);
	return 0;
}

/*==========================================
 * npcチャットから全員蹴り出す
 *------------------------------------------
 */
int buildin_kickwaitingroomall(struct script_state *st)
{
	struct npc_data *nd;
	struct chat_data *cd;

	if( st->end > st->start+2 )
		nd = npc_name2id(conv_str(st,& (st->stack->stack_data[st->start+2])));
	else
		nd = map_id2nd(st->oid);

	if( nd && (cd = map_id2cd(nd->chat_id)) )
		chat_npckickall(cd);
	return 0;
}

/*==========================================
 * npcチャットイベント有効化
 *------------------------------------------
 */
int buildin_enablewaitingroomevent(struct script_state *st)
{
	struct npc_data *nd;
	struct chat_data *cd;

	if( st->end > st->start+2 )
		nd = npc_name2id(conv_str(st,& (st->stack->stack_data[st->start+2])));
	else
		nd = map_id2nd(st->oid);

	if(nd && (cd = map_id2cd(nd->chat_id)) )
		chat_enableevent(cd);
	return 0;
}

/*==========================================
 * npcチャットイベント無効化
 *------------------------------------------
 */
int buildin_disablewaitingroomevent(struct script_state *st)
{
	struct npc_data *nd;
	struct chat_data *cd;

	if( st->end > st->start+2 )
		nd = npc_name2id(conv_str(st,& (st->stack->stack_data[st->start+2])));
	else
		nd = map_id2nd(st->oid);

	if(nd && (cd = map_id2cd(nd->chat_id)) )
		chat_disableevent(cd);
	return 0;
}

/*==========================================
 * npcチャット状態取得
 *------------------------------------------
 */
int buildin_getwaitingroomstate(struct script_state *st)
{
	struct npc_data *nd;
	struct chat_data *cd;
	int type, val = -1;
	char *str = NULL;

	type = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if(st->end > st->start+3)
		nd = npc_name2id(conv_str(st,& (st->stack->stack_data[st->start+3])));
	else
		nd = map_id2nd(st->oid);

	if(nd == NULL || (cd = map_id2cd(nd->chat_id)) == NULL){
		push_val(st->stack,C_INT,-1);
		return 0;
	}

	switch(type) {
		case 0:  val = cd->users;                        break;
		case 1:  val = cd->limit;                        break;
		case 2:  val = cd->trigger&0x7f;                 break;
		case 3:  val = ((cd->trigger&0x80) > 0)? 1: 0;   break;
		case 6:  val = cd->zeny;                         break;
		case 7:  val = cd->lowlv;                        break;
		case 8:  val = cd->highlv;                       break;
		case 9:  val = cd->job;                          break;
		case 10: val = cd->upper;                        break;
		case 32: val = (cd->users >= cd->limit)? 1: 0;   break;
		case 33: val = (cd->users >= cd->trigger)? 1: 0; break;
		case 4:
			str = (char *)aStrdup(cd->title);
			break;
		case 5:
			// passは\0が付いてない場合がある
			str = (char *)aCalloc(sizeof(cd->pass)+1, sizeof(char));
			memcpy(str, cd->pass, sizeof(cd->pass));
			break;
		case 16:
			str = (char *)aStrdup(cd->npc_event);
			break;
	}
	if(str)
		push_str(st->stack,C_STR,str);
	else
		push_val(st->stack,C_INT,val);
	return 0;
}

/*==========================================
 * チャットメンバー(規定人数)ワープ
 *------------------------------------------
 */
int buildin_warpwaitingpc(struct script_state *st)
{
	int x,y,i,j,n,num;
	char *str;
	struct npc_data *nd = map_id2nd(st->oid);
	struct chat_data *cd;

	if(nd == NULL || (cd = map_id2cd(nd->chat_id)) == NULL)
		return 0;

	str = conv_str(st,& (st->stack->stack_data[st->start+2]));
	x   = conv_num(st,& (st->stack->stack_data[st->start+3]));
	y   = conv_num(st,& (st->stack->stack_data[st->start+4]));

	if(st->end > st->start+5)
		n = conv_num(st,& (st->stack->stack_data[st->start+5]));
	else
		n = cd->trigger&0x7f;

	num = add_str("$@warpwaitingpc");
	for(i=0, j=0; i<n && i<128; i++) {
		struct map_session_data *sd = cd->usersd[0];	// リスト先頭のPCを次々に。

		if(sd == NULL)
			continue;
		mapreg_setreg(num+(j<<24),sd->bl.id,0);
		j++;
		script_warp(sd, str, x, y);
	}
	mapreg_setreg(add_str("$@warpwaitingpcnum"),j,0);
	return 0;
}

/*==========================================
 * NPCチャット内に居るPCのIDをリストアップする
 *------------------------------------------
 */
int buildin_getwaitingpcid(struct script_state *st)
{
	int i,j=0;
	struct map_session_data *sd = NULL;
	struct npc_data *nd;
	struct chat_data *cd;
	int num;
	char *name;
	char prefix, postfix;

	if( st->stack->stack_data[st->start+2].type != C_NAME ) {
		printf("buildin_getwaitingpcid: param not name\n");
		return 0;
	}
	num     = st->stack->stack_data[st->start+2].u.num;
	name    = get_str(num&0x00ffffff);
	prefix  = *name;
	postfix = name[strlen(name)-1];

	if( prefix != '$' && prefix != '@' && prefix != '\'' ) {
		printf("buildin_getwaitingpcid: illegal scope !\n");
		return 0;
	}
	if( prefix != '$' && prefix != '\'' )
		sd = script_rid2sd(st);

	if(st->end > st->start+3)
		nd = npc_name2id(conv_str(st,& (st->stack->stack_data[st->start+3])));
	else
		nd = map_id2nd(st->oid);

	if(nd == NULL || (cd = map_id2cd(nd->chat_id)) == NULL)
		return 0;

	for(i=0; i<cd->users; i++) {
		struct map_session_data *pl_sd;
		pl_sd=cd->usersd[i];
		if(pl_sd) {
			void *v;
			if( postfix == '$' ) {
				char str[16];
				sprintf(str,"%d",pl_sd->bl.id);
				v = (void*)str;
			} else {
				v = INT2PTR(pl_sd->bl.id);
			}
			set_reg(st,sd,num+(j<<24),name,v,st->stack->stack_data[st->start+2].ref);
			j++;
			if((num>>24)+j >= 128)
				break;
		}
	}
	return 0;
}

/*==========================================
 * RIDのアタッチ
 *------------------------------------------
 */
int buildin_attachrid(struct script_state *st)
{
	struct map_session_data *sd;

	st->rid = conv_num(st,& (st->stack->stack_data[st->start+2]));

	sd = map_id2sd(st->rid);
	if(sd && sd->npc_id == 0) {
		sd->npc_id = st->oid;
		npc_timeout_start(sd);
		if(sd->npc_dynamic_id == sd->npc_id)
			npc_dynamicnpc_start(sd);
	}
	push_val(st->stack,C_INT,(sd ? 1: 0));

	return 0;
}

/*==========================================
 * RIDのデタッチ
 *------------------------------------------
 */
int buildin_detachrid(struct script_state *st)
{
	struct map_session_data *sd = map_id2sd(st->rid);

	st->rid = 0;
	if(sd && sd->npc_id == st->oid) {
		sd->npc_id = 0;
		npc_timeout_stop(sd);
	}
	return 0;
}

/*==========================================
 * NPCエモーション
 *------------------------------------------
 */
int buildin_emotion(struct script_state *st)
{
	struct npc_data *nd;
	int type, flag = 0;

	type = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if( st->end > st->start+3 )
		nd = npc_name2id(conv_str(st,& (st->stack->stack_data[st->start+3])));
	else
		nd = map_id2nd(st->oid);
	if( st->end > st->start+4 )
		flag = conv_num(st,& (st->stack->stack_data[st->start+4]));

	if(nd) {
		if(flag) {
			struct map_session_data *sd = map_id2sd(st->rid);
			if(sd)
				clif_emotion_self(sd,&nd->bl,type);
		}
		else
			clif_emotion(&nd->bl,type);
	} else {
		struct block_list *bl = map_id2bl(st->rid);
		if(bl) {
			if(flag && bl->type == BL_PC)
				clif_emotion_self((struct map_session_data *)bl,bl,type);
			else
				clif_emotion(bl,type);
		}
	}
	return 0;
}

/*==========================================
 * NPCクラスチェンジ
 * classは変わりたいclass
 * typeは通常0なのかな？
 *------------------------------------------
 */
int buildin_classchange(struct script_state *st)
{
	int class_ = conv_num(st,& (st->stack->stack_data[st->start+2]));
	int type   = conv_num(st,& (st->stack->stack_data[st->start+3]));
	struct block_list *bl;

	if((bl = map_id2bl(st->oid)) != NULL)
		clif_class_change(bl,class_,type);

	return 0;
}

/*==========================================
 * NPC見た目変更
 *------------------------------------------
 */
int buildin_setnpcdisplay(struct script_state *st)
{
	struct npc_data *nd;
	int class_ = -1;

	nd = npc_name2id(conv_str(st,& (st->stack->stack_data[st->start+2])));
	if(nd == NULL)
		return 0;

	class_ = conv_num(st,& (st->stack->stack_data[st->start+3]));

	if(class_ != -1 && nd->class_ != class_) {
		nd->class_ = class_;
		if(npc_is_pcview(nd)) {
			nd->sex = (st->end > st->start+4)? conv_num(st,& (st->stack->stack_data[st->start+4])): 0;
			nd->hair = (st->end > st->start+5)? conv_num(st,& (st->stack->stack_data[st->start+5])): 0;
			nd->hair_color = (st->end > st->start+6)? conv_num(st,& (st->stack->stack_data[st->start+6])): 0;
			nd->clothes_color = (st->end > st->start+7)? conv_num(st,& (st->stack->stack_data[st->start+7])): 0;
			nd->head_top = (st->end > st->start+8)? conv_num(st,& (st->stack->stack_data[st->start+8])): 0;
			nd->head_mid = (st->end > st->start+9)? conv_num(st,& (st->stack->stack_data[st->start+9])): 0;
			nd->head_bottom = (st->end > st->start+10)? conv_num(st,& (st->stack->stack_data[st->start+10])): 0;
			nd->robe = (st->end > st->start+11)? conv_num(st,& (st->stack->stack_data[st->start+11])): 0;
			nd->style = (st->end > st->start+12)? conv_num(st,& (st->stack->stack_data[st->start+12])): 0;
			clif_clearchar(&nd->bl, 4);
			clif_spawnnpc(nd);
		}
		else {
			nd->sex = 0;
			nd->hair = 0;
			nd->hair_color = 0;
			nd->clothes_color = 0;
			nd->head_top = 0;
			nd->head_mid = 0;
			nd->head_bottom = 0;
			nd->robe = 0;
			nd->style = 0;
			clif_class_change(&nd->bl,class_,0);
		}
	}

	return 0;
}

/*==========================================
 * getnpcposition [Sapientia]
 *------------------------------------------
 */
int buildin_getnpcposition(struct script_state *st)
{
	struct npc_data *nd = map_id2nd(st->oid);
	char *str;

	str = conv_str(st,& (st->stack->stack_data[st->start+2]));

	if(nd) {
		strncpy(nd->position, str, 24);
		nd->position[23] = '\0';
	}
	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int buildin_sleep(struct script_state *st)
{
	struct map_session_data *sd = map_id2sd(st->rid);

	if(sd && sd->npc_id == st->oid) {
		sd->npc_id = 0;
	}
	st->rid = 0;

	if(st->sleep.tick == 0) {
		// 初回実行
		int tick = conv_num(st,& (st->stack->stack_data[st->start+2]));

		if(tick <= 0) {
			// 何もしない
			return 0;
		}
		st->state = RERUNLINE;
		st->sleep.tick = tick;
	} else {
		// 続行
		st->sleep.tick = 0;
	}
	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int buildin_sleep2(struct script_state *st)
{
	if(st->sleep.tick == 0) {
		// 初回実行時
		int tick = conv_num(st,& (st->stack->stack_data[st->start+2]));

		if(tick <= 0) {
			// 0ms の待機時間を指定された
			push_val(st->stack,C_INT,(map_id2sd(st->rid) != NULL)? 1: 0);
			return 0;
		}
		st->state = RERUNLINE;
		st->sleep.tick = tick;
	} else {
		// 続行
		push_val(st->stack,C_INT,(map_id2sd(st->rid) != NULL)? 1: 0);
		st->sleep.tick = 0;
	}
	return 0;
}

/*==========================================
 * 指定NPCの全てのsleepを再開する
 *------------------------------------------
 */
int buildin_awake(struct script_state *st)
{
	struct npc_data *nd;
	struct linkdb_node *node = (struct linkdb_node *)sleep_db;

	nd = npc_name2id(conv_str(st,& (st->stack->stack_data[st->start+2])));
	if(nd == NULL)
		return 0;

	while(node) {
		if(PTR2INT(node->key) == nd->bl.id) {
			struct script_state *tst = (struct script_state *)node->data;

			if(tst->sleep.timer != -1) {
				delete_timer(tst->sleep.timer, run_script_timer);
				node = script_erase_sleepdb(node);

				run_script_awake(tst);
				continue;
			}
		}
		node = node->next;
	}
	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int buildin_getvariableofnpc(struct script_state *st)
{
	if( st->stack->stack_data[st->start+2].type != C_NAME ) {
		// 第一引数が変数名じゃない
		printf("buildin_getvariableofnpc: param not name\n");
		push_val(st->stack,C_INT,0);
	} else {
		int num = st->stack->stack_data[st->start+2].u.num;
		char *var_name = get_str(num&0x00ffffff);
		char *npc_name = conv_str(st,& (st->stack->stack_data[st->start+3]));
		struct npc_data *nd = npc_name2id(npc_name);

		if( var_name[0] != '\'' || var_name[1] == '@' ) {
			// ' 変数以外はダメ
			printf("buildin_getvariableofnpc: invalid scope %s\n", var_name);
			push_val(st->stack,C_INT,0);
		} else if( nd == NULL || nd->subtype != SCRIPT || !nd->u.scr.script) {
			// NPC が見つからない or SCRIPT以外のNPC
			printf("buildin_getvariableofnpc: can't find npc %s\n", npc_name);
			push_val(st->stack,C_INT,0);
		} else {
			push_val2(st->stack,C_NAME,num, &nd->u.scr.script->script_vars );
		}
	}
	return 0;
}

/*==========================================
 * NPC攻撃スキルエフェクト
 *------------------------------------------
 */
int buildin_npcskillattack(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	struct block_list *bl = map_id2bl(st->oid);
	int id=conv_num(st,& (st->stack->stack_data[st->start+2]));
	int lv=conv_num(st,& (st->stack->stack_data[st->start+3]));
	int damage=conv_num(st,& (st->stack->stack_data[st->start+4]));

	nullpo_retr(0, sd);

	if(bl == NULL || bl->type != BL_NPC)
		bl = &sd->bl;

	clif_skill_damage(bl,&sd->bl,gettick(),status_get_amotion(bl),status_get_dmotion(&sd->bl),
				damage, skill_get_num(id,lv), id, lv, skill_get_hit(id));
	return 0;
}

/*==========================================
 * NPC支援/回復スキルエフェクト
 *------------------------------------------
 */
int buildin_npcskillsupport(struct script_state *st)
{
	struct npc_data *nd;
	struct map_session_data *sd = script_rid2sd(st);
	struct block_list *bl = map_id2bl(st->oid), *tbl = NULL;
	int skillid=conv_num(st,& (st->stack->stack_data[st->start+2]));
	int heal=conv_num(st,& (st->stack->stack_data[st->start+3]));

	nullpo_retr(0, sd);

	if(st->end > st->start+4) {
		nd = npc_name2id(conv_str(st,& (st->stack->stack_data[st->start+4])));
		if(nd)
			bl = &nd->bl;
		else
			bl = NULL;
	}
	if(bl == NULL || bl->type != BL_NPC)
		bl = &sd->bl;

	if(st->end > st->start+5) {
		nd = npc_name2id(conv_str(st,& (st->stack->stack_data[st->start+5])));
		if(nd)
			tbl = &nd->bl;
	}
	if(tbl == NULL || tbl->type != BL_NPC)
		tbl = &sd->bl;

	clif_skill_nodamage(bl,tbl,skillid,heal,1);

	return 0;
}

/*==========================================
 * NPC場所指定スキルエフェクト
 *------------------------------------------
 */
int buildin_npcskillpos(struct script_state *st)
{
	struct block_list *bl = map_id2bl(st->oid);
	int skillid=conv_num(st,& (st->stack->stack_data[st->start+2]));
	int skilllv=conv_num(st,& (st->stack->stack_data[st->start+3]));
	int x=conv_num(st,& (st->stack->stack_data[st->start+4]));
	int y=conv_num(st,& (st->stack->stack_data[st->start+5]));

	if(bl == NULL || bl->type != BL_NPC) {
		struct map_session_data *sd = script_rid2sd(st);
		if(sd == NULL)
			return 0;
		bl = &sd->bl;
	}
	clif_skill_poseffect(bl,skillid,skilllv,x,y,gettick());

	return 0;
}

/*==========================================
 * 呼び出し元のNPC情報を取得する
 *------------------------------------------
 */
int buildin_strnpcinfo(struct script_state *st)
{
	struct npc_data *nd = map_id2nd(st->oid);
	int type;
	char *p, *name = NULL;

	type = conv_num(st,& (st->stack->stack_data[st->start+2]));

	if(nd == NULL) {
		push_str(st->stack,C_CONSTSTR,"");
		return 0;
	}
	switch(type) {
		case 0:
			name = (char *)aStrdup(nd->name);
			break;
		case 1:
			name = (char *)aStrdup(nd->name);
			if((p = strchr(name,'#')) != NULL)
				*p = 0;
			break;
		case 2:
			if((p = strchr(nd->name,'#')) != NULL)
				name = (char *)aStrdup(p+1);
			break;
		case 3:
			name = (char *)aStrdup(nd->exname);
			break;
		case 4:
			name = (char *)aStrdup(nd->exname);
			if((p = strchr(name,'#')) != NULL)
				*p = 0;
			break;
		case 5:
			if((p = strchr(nd->exname,'#')) != NULL)
				name = (char *)aStrdup(p+1);
			break;
		case 6:
			name = (char *)aStrdup(nd->position);
			break;
	}
	if(name)
		push_str(st->stack,C_STR,name);
	else
		push_str(st->stack,C_CONSTSTR,"");
	return 0;
}

/*==========================================
 * shopを呼び出す。
 *------------------------------------------
 */
int buildin_callshop(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	struct npc_data *nd;
	const char *shopname;
	int flag = 0;

	nullpo_retr(0, sd);

	shopname = conv_str(st,& (st->stack->stack_data[st->start+2]));
	nd = npc_name2id(shopname);
	if(!nd || nd->bl.type != BL_NPC || (nd->subtype != SHOP && nd->subtype != POINTSHOP && nd->subtype != MARKET)) {
		return 0;
	}

	if(st->end>st->start+3)
		flag = conv_num(st,& (st->stack->stack_data[st->start+3]));

	switch(nd->subtype) {
	case SHOP:
		switch(flag) {
			case 1: npc_buysellsel(sd,nd->bl.id,0); break;	//購入ウィンドウ
			case 2: npc_buysellsel(sd,nd->bl.id,1); break;	//売却ウィンドウ
			default: clif_npcbuysell(sd,nd->bl.id); break;	//メニューを開く
		}
		break;
	case POINTSHOP:
		sd->npc_shopid = nd->bl.id;
		clif_pointshop_list(sd, nd);
		break;
	case MARKET:
		{
			int i;
			for (i = 0; nd->u.shop_item[i].nameid; i++) {
				if (nd->u.shop_item[i].qty) {
					sd->npc_shopid = nd->bl.id;
					clif_market_list(sd, nd);
					break;
				}
			}
		}
		break;
	}

	return 0;
}

/*==========================================
 * shopを変更する。
 *------------------------------------------
 */
int buildin_npcshopitem(struct script_state *st)
{
	struct npc_data *nd;
	const char *shopname;
	int n = 0, i;
	int count, offset = 2;

	shopname = conv_str(st,& (st->stack->stack_data[st->start+2]));
	nd = npc_name2id(shopname);
	if(!nd || nd->bl.type != BL_NPC || (nd->subtype != SHOP && nd->subtype != POINTSHOP && nd->subtype != MARKET)) {
		return 0;
	}

	if(nd->subtype == MARKET) {
#if PACKETVER >= 20131223
		offset = 3;
#else
		return 0;
#endif
	}

	count = (st->end-3)/offset;

	map_deliddb( &nd->bl );
	nd = (struct npc_data *)aRealloc(nd, sizeof(struct npc_data) + sizeof(nd->u.shop_item[0]) * (count+1));
	for(n = 0, i = 3; n < count; n++, i+=offset) {
		nd->u.shop_item[n].nameid = conv_num(st,& (st->stack->stack_data[st->start+i]));
		nd->u.shop_item[n].value = conv_num(st,& (st->stack->stack_data[st->start+i+1]));
		if(nd->subtype == MARKET)
			nd->u.shop_item[n].qty = conv_num(st,& (st->stack->stack_data[st->start+i+2]));
	}
	nd->u.shop_item[n++].nameid = 0;
	npc_refresh(shopname,nd);
	map_addiddb(&nd->bl);

	return 0;
}

/*==========================================
 * メモリアルダンジョンNPC名取得
 *------------------------------------------
 */
int buildin_getmdnpcname(struct script_state *st)
{
	unsigned char name[24];
	char *str = conv_str(st,& (st->stack->stack_data[st->start+2]));
	struct npc_data *nd = npc_name2id(str);
	int id = script_getmemorialid(st);

	if(id > 0 && nd) {
		sprintf(name, "mdnpc_%03d_%d", id, nd->bl.id);
		name[23] = '\0';
	} else {
		strncpy(name, str, 24);
	}

	push_str(st->stack,C_STR,(unsigned char *)aStrdup(name));

	return 0;
}

/*==========================================
 * ダイナミックNPC
 *------------------------------------------
 */
int buildin_dynamicnpc(struct script_state *st)
{
	int m,x,y,dir,class_;
	char *mapname;
	struct map_session_data *sd;
	struct npc_data *nd;
	int i;

	sd = script_rid2sd(st);
	if(!sd)
		return 0;
	if(sd->npc_dynamic_id) {
		clif_dynamicnpc_create_ack(sd,3);
		return 0;
	}

	nd = npc_name2id(conv_str(st,& (st->stack->stack_data[st->start+2])));
	if(!nd)
		return 0;

	mapname = conv_str(st,& (st->stack->stack_data[st->start+3]));
	x       = conv_num(st,& (st->stack->stack_data[st->start+4]));
	y       = conv_num(st,& (st->stack->stack_data[st->start+5]));
	dir     = conv_num(st,& (st->stack->stack_data[st->start+6]));
	class_  = conv_num(st,& (st->stack->stack_data[st->start+7]));

	m  = script_mapname2mapid(st,mapname);
	if(m < 0) {
		m = sd->bl.m;
		for(i=0;i<5;i++) {
			x = sd->bl.x + (atn_rand()%3 - 1) + (atn_rand()%2? 2: -2);
			y = sd->bl.y + (atn_rand()%3 - 1) + (atn_rand()%2? 2: -2);
			if(!map_getcell(m,x,y,CELL_CHKGROUND))
				break;
		}
		if(i == 5) {
			x = sd->bl.x;
			y = sd->bl.y;
		}
	}
	dir = (dir%8);

	sd->npc_dynamic_id = nd->bl.id;
	npc_dynamicnpc_start(sd);
	clif_spawndynamicnpc(sd, nd, x, y, dir, class_);
	return 0;
}

/*==========================================
 * NPCを移動させる
 *------------------------------------------
 */
int buildin_npcwalkto(struct script_state *st)
{
	int x,y;
	struct npc_data *nd;

	x   = conv_num(st,& (st->stack->stack_data[st->start+2]));
	y   = conv_num(st,& (st->stack->stack_data[st->start+3]));
	if(st->end > st->start+4)
		nd = npc_name2id(conv_str(st,& (st->stack->stack_data[st->start+4])));
	else
		nd = map_id2nd(st->oid);

	if(nd == NULL)
		return 0;
	if(nd->flag&1)
		return 0;

	if(x > map[nd->bl.m].xs || y > map[nd->bl.m].ys )
		return 0;

	unit_walktoxy(&nd->bl,x,y);

	return 0;
}

/*==========================================
 * NPCの移動時間分待機する
 *------------------------------------------
 */
int buildin_npcwalkwait(struct script_state *st)
{
	struct npc_data *nd;
	int delay = 50;

	if(st->end > st->start+2)
		delay = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if(st->end > st->start+3)
		nd = npc_name2id(conv_str(st,& (st->stack->stack_data[st->start+3])));
	else
		nd = map_id2nd(st->oid);

	if(nd == NULL)
		return 0;
	if(nd->flag&1)
		return 0;

	if(delay < 50)
		delay = 50;

	if(st->sleep.tick == 0) {
		// 初回実行
		int tick = 0;
		int dist = path_distance(nd->bl.x,nd->bl.y,nd->ud.to_x,nd->ud.to_y);

		// 同軸ならSpeed * 距離
		if(nd->bl.x == nd->ud.to_x || nd->bl.y == nd->ud.to_y) {
			tick = nd->speed * dist + delay;
		} else {
			int i, c=0, s=0;
			for(i=0;i<nd->ud.walkpath.path_len;i++) {
				if(nd->ud.walkpath.path[i]&1)
					s++;
				else
					c++;
			}
			tick = nd->speed * c + nd->speed * s * 14 / 10 + delay;
		}

		if(tick <= 0) {
			// 何もしない
			return 0;
		}
		st->state = RERUNLINE;
		st->sleep.tick = tick;
	} else {
		// 続行
		st->sleep.tick = 0;
	}

	return 0;
}

/*==========================================
 * NPCの移動速度を設定する
 *------------------------------------------
 */
int buildin_setnpcspeed(struct script_state *st)
{
	struct npc_data *nd;
	int speed;

	speed = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if(st->end > st->start+3)
		nd = npc_name2id(conv_str(st,& (st->stack->stack_data[st->start+3])));
	else
		nd = map_id2nd(st->oid);

	if(nd == NULL)
		return 0;

	if(speed > 0)
		nd->speed = speed;
	else
		nd->speed = 300;

	return 0;
}

/*==========================================
 * NPC移動中のクリックを許可するOn / Off
 *------------------------------------------
 */
int buildin_npcclickable(struct script_state *st)
{
	struct npc_data *nd;
	int flag = 0;

	flag = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if( st->end > st->start+3 ) {
		nd = npc_name2id(conv_str(st,& (st->stack->stack_data[st->start+3])));
	}
	else {
		nd = map_id2nd(st->oid);
	}

	if(nd == NULL)
		return 0;

	nd->click_able = flag;

	return 0;
}

/*==========================================
 * Group_id設定
 *------------------------------------------
 */
int buildin_setnpcgroup(struct script_state *st)
{
	struct npc_data *nd;
	int id;

	id = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if( st->end > st->start+3 ) {
		nd = npc_name2id(conv_str(st,& (st->stack->stack_data[st->start+3])));
	}
	else {
		nd = map_id2nd(st->oid);
	}

	if(nd == NULL)
		return 0;
	if(id < 0)
		return 0;

	nd->group_id = id;

	return 0;
}

/*==========================================
 * Title設定
 *------------------------------------------
 */
int buildin_setnpctitle(struct script_state *st)
{
	struct npc_data *nd;
	char *str;

	str = conv_str(st,& (st->stack->stack_data[st->start+2]));
	if( st->end > st->start+3 ) {
		nd = npc_name2id(conv_str(st,& (st->stack->stack_data[st->start+3])));
	}
	else {
		nd = map_id2nd(st->oid);
	}

	if(nd) {
		strncpy(nd->title, str, 24);
		nd->title[23] = '\0';
	}

	return 0;
}
