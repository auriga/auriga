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

// $Id: chat.c,v 1.7 2003/06/29 05:52:56 lemit Exp $

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "db.h"
#include "nullpo.h"
#include "malloc.h"
#include "map.h"
#include "path.h"
#include "clif.h"
#include "chat.h"
#include "npc.h"
#include "pc.h"

/*==========================================
 * 規定人数以上でイベントが定義されてるなら実行
 *------------------------------------------
 */
static int chat_triggerevent(struct chat_data *cd)
{
	nullpo_retr(0, cd);

	if(cd->users >= cd->trigger && cd->npc_event[0])
		npc_event_do(cd->npc_event);

	return 0;
}

/*==========================================
 * チャットルーム作成
 *------------------------------------------
 */
void chat_createchat(struct map_session_data *sd, unsigned short limit, unsigned char pub, const char* pass, const char* title, int titlelen)
{
	struct chat_data *cd;

	nullpo_retv(sd);

	if(sd->state.joinchat && chat_leavechat(sd,0))
		return;

	cd = (struct chat_data *)aCalloc(1,sizeof(struct chat_data));

	cd->limit = (unsigned char)limit;
	cd->pub   = pub;
	cd->users = 1;
	memcpy(cd->pass,pass,8);
	if(titlelen >= sizeof(cd->title)-1) {
		titlelen = sizeof(cd->title)-1;
	}
	memcpy(cd->title,title,titlelen);
	cd->title[titlelen] = 0;

	cd->owner     = (struct block_list **)(&cd->usersd[0]);
	cd->usersd[0] = sd;
	cd->bl.m      = sd->bl.m;
	cd->bl.x      = sd->bl.x;
	cd->bl.y      = sd->bl.y;
	cd->bl.type   = BL_CHAT;
	cd->zeny      = 0;
	cd->lowlv     = 0;
	cd->highlv    = MAX_LEVEL;
	cd->job       = 0xFFFFFFFF;
	cd->upper     = 0;

	cd->bl.id = map_addobject(&cd->bl);
	if(cd->bl.id == 0) {
		clif_createchat(sd,1);
		aFree(cd);
		return;
	}

	sd->chatID         = cd->bl.id;
	sd->state.joinchat = 1;

	clif_createchat(sd,0);
	clif_dispchat(cd,-1);

	return;
}

/*==========================================
 * 既存チャットルームに参加
 *------------------------------------------
 */
void chat_joinchat(struct map_session_data *sd, int chatid, const char* pass)
{
	struct chat_data *cd;

	nullpo_retv(sd);

	if((cd = map_id2cd(chatid)) == NULL)
		return;

	if(cd->bl.m != sd->bl.m || sd->state.store || sd->state.joinchat || path_distance(cd->bl.x,cd->bl.y,sd->bl.x,sd->bl.y) > AREA_SIZE) {
		clif_joinchatfail(sd,3);
		return;
	}
	if(cd->limit <= cd->users || cd->users >= sizeof(cd->usersd)/sizeof(cd->usersd[0])) {
		clif_joinchatfail(sd,0);
		return;
	}
	if(cd->pub == 0 && strncmp(pass,cd->pass,8)) {
		clif_joinchatfail(sd,1);
		return;
	}
	if(linkdb_exists(&cd->ban_list, INT2PTR(sd->status.char_id))) {
		clif_joinchatfail(sd,2);
		return;
	}
	if(cd->zeny > sd->status.zeny) {
		clif_joinchatfail(sd,4);
		return;
	}
	if(cd->lowlv > sd->status.base_level) {
		clif_joinchatfail(sd,5);
		return;
	}
	if(cd->highlv < sd->status.base_level) {
		clif_joinchatfail(sd,6);
		return;
	}
	if((pc_get_job_bit(sd->s_class.job) & cd->job) == 0) {
		clif_joinchatfail(sd,7);
		return;
	}
	if(cd->upper) {
		if(((1<<sd->s_class.upper)&cd->upper) == 0) {
			clif_joinchatfail(sd,7);
			return;
		}
	}

	cd->usersd[cd->users] = sd;
	cd->users++;

	sd->chatID         = cd->bl.id;
	sd->state.joinchat = 1;

	clif_joinchatok(sd,cd);	// 新たに参加した人には全員のリスト
	clif_addchat(cd,sd);	// 既に中に居た人には追加した人の報告
	clif_dispchat(cd,-1);	// 周囲の人には人数変化報告

	chat_triggerevent(cd);	// イベント

	return;
}

/*==========================================
 * チャットルームから抜ける
 *------------------------------------------
 */
int chat_leavechat(struct map_session_data *sd, unsigned char flag)
{
	struct chat_data *cd;
	int i,leavechar;

	nullpo_retr(1, sd);

	if((cd = map_id2cd(sd->chatID)) == NULL)
		return 1;

	leavechar = -1;
	for(i = 0; i < cd->users; i++) {
		if(cd->usersd[i] == sd) {
			leavechar = i;
			break;
		}
	}
	if(leavechar < 0)	// そのchatに所属していないらしい (バグ時のみ)
		return -1;

	if(leavechar == 0 && cd->users > 1 && (*cd->owner)->type == BL_PC) {
		// 所有者だった&他に人が居る&PCのチャット
		clif_changechatowner(cd,cd->usersd[1]);
		clif_clearchat(cd,-1);
	}

	// 抜けるPCにも送るのでusersを減らす前に実行
	clif_leavechat(cd,sd,flag);

	cd->users--;
	sd->chatID         = 0;
	sd->state.joinchat = 0;

	if(cd->users == 0 && (*cd->owner)->type == BL_PC) {
		// 全員居なくなった&PCのチャットなので消す
		clif_clearchat(cd,-1);
		linkdb_final(&cd->ban_list);
		map_delobject(cd->bl.id);	// freeまでしてくれる
	} else {
		for(i = leavechar; i < cd->users; i++) {
			cd->usersd[i] = cd->usersd[i+1];
		}
		if(leavechar == 0 && (*cd->owner)->type == BL_PC) {
			// PCのチャットで所有者が抜けたので位置変更
			cd->bl.x = cd->usersd[0]->bl.x;
			cd->bl.y = cd->usersd[0]->bl.y;
		}
		clif_dispchat(cd,-1);
	}

	return 0;
}

/*==========================================
 * チャットルームの持ち主を譲る
 *------------------------------------------
 */
void chat_changechatowner(struct map_session_data *sd, const char *nextownername)
{
	struct chat_data *cd;
	struct map_session_data *tmp_sd;
	int i,nextowner;

	nullpo_retv(sd);

	cd = map_id2cd(sd->chatID);
	if(cd == NULL || &sd->bl != (*cd->owner))
		return;

	nextowner = -1;
	for(i = 1; i < cd->users; i++) {
		if(strncmp(cd->usersd[i]->status.name, nextownername, 24) == 0) {
			nextowner = i;
			break;
		}
	}
	if(nextowner < 0)	// そんな人は居ない
		return;

	clif_changechatowner(cd,cd->usersd[nextowner]);
	// 一旦消す
	clif_clearchat(cd,-1);

	// userlistの順番変更 (0が所有者なので)
	if( (tmp_sd = cd->usersd[0]) == NULL )
		return; //ありえるのかな？

	cd->usersd[0] = cd->usersd[nextowner];
	cd->usersd[nextowner] = tmp_sd;

	// 新しい所有者の位置へ変更
	cd->bl.x = cd->usersd[0]->bl.x;
	cd->bl.y = cd->usersd[0]->bl.y;

	// 再度表示
	clif_dispchat(cd,-1);

	return;
}

/*==========================================
 * チャットの状態(タイトル等)を変更
 *------------------------------------------
 */
void chat_changechatstatus(struct map_session_data *sd, unsigned short limit, unsigned char pub, const char* pass, const char* title, int titlelen)
{
	struct chat_data *cd;

	nullpo_retv(sd);

	cd = map_id2cd(sd->chatID);
	if(cd == NULL || &sd->bl != (*cd->owner))
		return;

	cd->limit = (unsigned char)limit;
	cd->pub   = pub;
	memcpy(cd->pass,pass,8);
	if(titlelen >= sizeof(cd->title) - 1) {
		titlelen = sizeof(cd->title) - 1;
	}
	memcpy(cd->title,title,titlelen);
	cd->title[titlelen] = 0;

	clif_changechatstatus(cd);
	clif_dispchat(cd,-1);

	return;
}

/*==========================================
 * チャットルームから蹴り出す
 *------------------------------------------
 */
void chat_kickchat(struct map_session_data *sd, const char *kickusername)
{
	struct chat_data *cd;
	int i;

	nullpo_retv(sd);

	cd = map_id2cd(sd->chatID);
	if(cd == NULL || &sd->bl != (*cd->owner))
		return;

	for(i = 0; i < cd->users; i++) {
		if(strncmp(cd->usersd[i]->status.name, kickusername, 24) == 0) {
			linkdb_insert(&cd->ban_list, INT2PTR(cd->usersd[i]->status.char_id), INT2PTR(1));
			chat_leavechat(cd->usersd[i], 1);
			break;
		}
	}

	return;
}

/*==========================================
 * npcチャットルーム作成
 *------------------------------------------
 */
int chat_createnpcchat(
	struct npc_data *nd,int limit,int pub,int trigger,const char* title,int titlelen,const char *ev,
	int zeny,int lowlv,int highlv,unsigned int job,int upper)
{
	int change_flag = 0;
	struct chat_data *cd;

	nullpo_retr(1, nd);

	// 既にチャットを持っているなら状態変更するだけ
	if( nd->chat_id && (cd = map_id2cd(nd->chat_id)) ) {
		change_flag = 1;
		memset(cd->npc_event, 0, sizeof(cd->npc_event));
	} else {
		cd = (struct chat_data *)aCalloc(1,sizeof(struct chat_data));
		cd->pass[0] = 0;
		cd->users   = 0;
		cd->bl.type = BL_CHAT;
		cd->owner_  = &nd->bl;
		cd->owner   = &cd->owner_;
		cd->bl.id   = map_addobject(&cd->bl);
		if(cd->bl.id == 0) {
			aFree(cd);
			return 0;
		}
		nd->chat_id = cd->bl.id;
	}

	cd->limit   = (unsigned char)limit;
	cd->trigger = (trigger > 0)? trigger: limit;
	cd->pub     = pub;

	if(titlelen >= (int)(sizeof(cd->title) - 1)) {
		titlelen = (int)(sizeof(cd->title) - 1);
	}
	memcpy(cd->title,title,titlelen);
	cd->title[titlelen] = 0;

	cd->bl.m   = nd->bl.m;
	cd->bl.x   = nd->bl.x;
	cd->bl.y   = nd->bl.y;
	cd->zeny   = zeny;
	cd->lowlv  = lowlv;
	cd->highlv = highlv;
	cd->job    = job;
	cd->upper  = upper;
	memcpy(cd->npc_event,ev,sizeof(cd->npc_event));
	cd->npc_event[sizeof(cd->npc_event)-1] = '\0';

	if(change_flag)
		clif_changechatstatus(cd);
	clif_dispchat(cd,-1);

	return 0;
}

/*==========================================
 * npcチャットルーム削除
 *------------------------------------------
 */
int chat_deletenpcchat(struct npc_data *nd)
{
	struct chat_data *cd;

	nullpo_retr(0, nd);

	cd = map_id2cd(nd->chat_id);
	if(cd) {
		chat_npckickall(cd);
		clif_clearchat(cd,-1);
		map_delobject(cd->bl.id);	// freeまでしてくれる
		nd->chat_id = 0;
	}
	return 0;
}

/*==========================================
 * イベントの有効化
 *------------------------------------------
 */
int chat_enableevent(struct chat_data *cd)
{
	nullpo_retr(0, cd);

	cd->trigger &= 0x7f;
	chat_triggerevent(cd);
	return 0;
}

/*==========================================
 * イベントの無効化
 *------------------------------------------
 */
int chat_disableevent(struct chat_data *cd)
{
	nullpo_retr(0, cd);

	cd->trigger |= 0x80;
	return 0;
}

/*==========================================
 * チャットルームから全員蹴り出す
 *------------------------------------------
 */
int chat_npckickall(struct chat_data *cd)
{
	nullpo_retr(0, cd);

	while(cd->users > 0) {
		chat_leavechat(cd->usersd[cd->users-1],0);
	}
	return 0;
}
