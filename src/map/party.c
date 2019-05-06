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
#include <string.h>

#include "db.h"
#include "timer.h"
#include "socket.h"
#include "nullpo.h"
#include "malloc.h"
#include "utils.h"

#include "party.h"
#include "pc.h"
#include "map.h"
#include "path.h"
#include "battle.h"
#include "intif.h"
#include "clif.h"
#include "status.h"
#include "skill.h"
#include "unit.h"
#include "msg.h"
#include "memorial.h"

#define PARTY_SEND_XYHP_INVERVAL	1000	// 座標やＨＰ送信の間隔

static struct dbt* party_db = NULL;

/*==========================================
 * パーティ検索
 *------------------------------------------
 */
struct party *party_search(int party_id)
{
	return (struct party *)numdb_search(party_db,party_id);
}

/*==========================================
 * パーティ名検索
 *------------------------------------------
 */
static int party_searchname_sub(void *key, void *data, va_list ap)
{
	struct party *p, **dst;
	char *str;

	p   = (struct party *)data;
	str = va_arg(ap,char *);
	dst = va_arg(ap,struct party **);

	if(*dst == NULL) {
		if(strcmp(p->name,str) == 0)
			*dst = p;
	}

	return 0;
}

struct party* party_searchname(const char *str)
{
	struct party *p = NULL;

	numdb_foreach(party_db,party_searchname_sub,str,&p);

	return p;
}

/*==========================================
 * 作成要求
 *------------------------------------------
 */
void party_create(struct map_session_data *sd, const char *name, int item, int item2)
{
	nullpo_retv(sd);

	if (sd->status.party_id == 0 && sd->state.party_creating == 0) {
		int i;
		char party_name[24]; // 23 + NULL

		strncpy(party_name, name, 23);
		// force '\0' at end (against hacker: normal player can not create a party with a name longer than 23 characters)
		party_name[23] = '\0';

		// if too short name (hacker)
		if (party_name[0] == '\0') {
			clif_party_created(sd, 1); // 0xfa <flag>.B: 0: Party has successfully been organized, 1: That Party Name already exists., 2: The Character is already in a party.
			return;
		}

		// check control chars and del (is checked in char-server, check before to send to char-server to avoid packet transmission)
		for(i = 0; party_name[i]; i++) {
			if (!(party_name[i] & 0xe0) || party_name[i] == 0x7f) {
				clif_party_created(sd, 1); // 0xfa <flag>.B: 0: Party has successfully been organized, 1: That Party Name already exists., 2: The Character is already in a party.
				return;
			}
		}

		// ask char-server for creation
		sd->state.party_creating = 1;
		intif_create_party(sd, party_name, item, item2);
	} else {
		clif_party_created(sd,2); // 0xfa <flag>.B: 0: Party has successfully been organized, 1: That Party Name already exists., 2: The Character is already in a party.
	}

	return;
}

/*==========================================
 * 作成可否
 *------------------------------------------
 */
void party_created(int account_id, unsigned char fail, int party_id, const char *name)
{
	struct map_session_data *sd = map_id2sd(account_id);

	if(sd == NULL)
		return;

	sd->state.party_creating = 0;

	if(fail==0){
		struct party *p;
		if (party_search(party_id) != NULL) {
			printf("party: id already exists!\n");
			return;
		}
		sd->status.party_id=party_id;
		p=(struct party *)aCalloc(1,sizeof(struct party));
		p->party_id=party_id;
		memcpy(p->name,name,24);
		numdb_insert(party_db,party_id,p);
		clif_party_created(sd,0);
	}else{
		clif_party_created(sd,1);
	}

	return;
}

/*==========================================
 * 情報要求
 *------------------------------------------
 */
void party_request_info(int party_id)
{
	intif_request_partyinfo(party_id);

	return;
}

/*==========================================
 * 所属キャラの確認
 *------------------------------------------
 */
static void party_check_member(struct party *p)
{
	int i;
	struct map_session_data *sd;

	nullpo_retv(p);

	for(i=0;i<fd_max;i++){
		if(session[i] && (sd = (struct map_session_data *)session[i]->session_data) && sd->state.auth){
			if(sd->status.party_id==p->party_id){
				int j,f=1;
				for(j=0;j<MAX_PARTY;j++){	// パーティにデータがあるか確認
					if(p->member[j].account_id==sd->status.account_id){
						if(p->member[j].char_id == sd->status.char_id)
							f=0;	// データがある
						else
							p->member[j].sd=NULL;	// 同垢別キャラだった
					}
				}
				if(f){
					sd->status.party_id=0;
					if(battle_config.error_log)
						printf("party: check_member %d[%s] is not member\n",sd->status.account_id,sd->status.name);
				}
			}
		}
	}

	return;
}

/*==========================================
 * 情報取得失敗（そのIDのキャラを全部未所属にする）
 *------------------------------------------
 */
void party_recv_noinfo(int party_id)
{
	int i;
	struct map_session_data *sd;

	for(i=0;i<fd_max;i++){
		if(session[i] && (sd = (struct map_session_data *)session[i]->session_data) && sd->state.auth){
			if(sd->status.party_id==party_id)
				sd->status.party_id=0;
		}
	}

	return;
}

/*==========================================
 * 情報取得
 *------------------------------------------
 */
void party_recv_info(struct party *sp)
{
	struct map_session_data *sd;
	struct party *p;
	int i;
	int memorial_id;

	nullpo_retv(sp);

	if((p = party_search(sp->party_id)) == NULL){
		p = (struct party *)aMalloc(sizeof(struct party));
		numdb_insert(party_db,sp->party_id,p);

		// 最初のロードなのでユーザーのチェックを行う
		party_check_member(sp);
	}

	// メモリアルダンジョンIDの一時保存＆書き戻し
	memorial_id = memorial_search_party(sp->party_id);
	memcpy(p,sp,sizeof(struct party));
	p->memorial_id = memorial_id;

	for(i=0;i<MAX_PARTY;i++){	// sdの設定
		sd = map_id2sd(p->member[i].account_id);
		if( sd != NULL &&
		    sd->status.char_id == p->member[i].char_id &&
		    sd->status.party_id == p->party_id &&
		    !sd->state.waitingdisconnect )
			p->member[i].sd = sd;
		else
			p->member[i].sd = NULL;
	}

	clif_party_main_info(p,-1);
	clif_party_info(p,-1);

	for(i=0;i<MAX_PARTY;i++){	// 設定情報の送信
		sd = p->member[i].sd;
		if(sd!=NULL && sd->state.party_sended == 0){
			clif_party_option(p,sd,0x100);
			sd->state.party_sended = 1;
		}
	}

	return;
}

/*==========================================
 * 位置通知クリア
 *------------------------------------------
 */
static void party_send_xy_clear(struct party *p)
{
	int i;

	nullpo_retv(p);

	for(i=0;i<MAX_PARTY;i++){
		struct map_session_data *sd = p->member[i].sd;
		if(sd) {
			sd->party_x  = -1;
			sd->party_y  = -1;
			sd->party_hp = -1;
		}
	}

	return;
}

/*==========================================
 * パーティへの勧誘
 *------------------------------------------
 */
void party_invite(struct map_session_data *sd, struct map_session_data *tsd)
{
	struct party *p;
	int i, empty = 0;

	nullpo_retv(sd);

	p = party_search(sd->status.party_id);
	if(p == NULL)
		return;

	if(tsd == NULL) {	// 相手が見つからない
		clif_party_inviteack(sd,"",7);
		return;
	}
	if(tsd->state.waitingdisconnect) {	// 相手が切断待ち
		clif_party_inviteack(sd,tsd->status.name,1);
		return;
	}
	if(!battle_config.invite_request_check) {
		if(tsd->guild_invite > 0 || tsd->trade.partner || tsd->adopt_invite) {	// 相手が取引中かどうか
			clif_party_inviteack(sd,tsd->status.name,1);
			return;
		}
	}
	if(tsd->status.party_id > 0 || tsd->party_invite > 0) {	// 相手の所属確認
		clif_party_inviteack(sd,tsd->status.name,0);
		return;
	}
	for(i=0; i<MAX_PARTY; i++) {
		if(p->member[i].account_id == sd->status.account_id &&
		   p->member[i].char_id == sd->status.char_id &&
		   p->member[i].leader == 0)
			return;		// 要請者がリーダーではない（hacker?）

		if(p->member[i].account_id <= 0) {
			empty = 1;
		} else if(p->member[i].account_id == tsd->status.account_id) {
			if(battle_config.party_join_limit) {
				clif_party_inviteack(sd,tsd->status.name,4);
				return;
			}
			if(p->member[i].char_id == tsd->status.char_id) {
				clif_party_inviteack(sd,tsd->status.name,0);
				return;
			}
		}
	}
	if(!empty) {	// 定員オーバー
		clif_party_inviteack(sd,tsd->status.name,3);
		return;
	}
	if(tsd->status.refuse_partyinvite) {	// 相手が勧誘拒否中
		clif_party_inviteack(sd,tsd->status.name,5);
		return;
	}
	if(battle_config.party_invite_range_check) {	// 相手のMAPと距離を確認
		if(sd->bl.m != tsd->bl.m || path_distance(sd->bl.x,sd->bl.y,tsd->bl.x,tsd->bl.y) > AREA_SIZE) {
			clif_party_inviteack(sd,tsd->status.name,1);
			return;
		}
	}

	tsd->party_invite         = sd->status.party_id;
	tsd->party_invite_account = sd->status.account_id;

	clif_party_invite(sd,tsd,p->name);

	return;
}

/*==========================================
 * パーティ勧誘への返答
 *------------------------------------------
 */
void party_reply_invite(struct map_session_data *sd, int account_id, int flag)
{
	struct map_session_data *tsd;

	nullpo_retv(sd);

	if(flag == 1) {	// 承諾
		if(sd->party_invite > 0) {
			// inter鯖へ追加要求
			intif_party_addmember(sd);
			return;
		}
	}

	// 拒否
	sd->party_invite         = 0;
	sd->party_invite_account = 0;
	tsd = map_id2sd(account_id);
	if(tsd)
		clif_party_inviteack(tsd,sd->status.name,1);

	return;
}

/*==========================================
 * パーティ競合確認
 *------------------------------------------
 */
static void party_check_conflict(struct map_session_data *sd)
{
	nullpo_retv(sd);

	//intif_party_checkconflict(sd->status.party_id,sd->status.account_id,sd->status.char_id);

	return;
}

/*==========================================
 * パーティが追加された
 *------------------------------------------
 */
void party_member_added(int party_id, int account_id, int char_id, unsigned char flag)
{
	struct map_session_data *sd, *sd2;
	struct party *p;

	if((p = party_search(party_id)) == NULL)
		return;

	sd = map_id2sd(account_id);
	if(sd == NULL) {
		if(flag == 0) {
			if(battle_config.error_log)
				printf("party: member added error %d is not online\n",account_id);
			intif_party_leave(party_id, account_id, char_id); // キャラ側に登録できなかったため脱退要求を出す
		}
		return;
	}
	sd2 = map_id2sd(sd->party_invite_account);
	sd->party_invite         = 0;
	sd->party_invite_account = 0;

	if(flag == 1) {	// 失敗
		if(sd2)
			clif_party_inviteack(sd2,sd->status.name,0);
		return;
	}

	// 成功
	sd->state.party_sended = 0;
	sd->status.party_id    = party_id;

	if(sd2)
		clif_party_inviteack(sd2,sd->status.name,2);

	// いちおう競合確認
	party_check_conflict(sd);

	// 座標再通知要請
	party_send_xy_clear(p);

	return;
}

/*==========================================
 * パーティ除名要求
 *------------------------------------------
 */
void party_removemember(struct map_session_data *sd, int account_id, const char *name)
{
	struct party *p;
	int i;

	nullpo_retv(sd);

	if( (p = party_search(sd->status.party_id)) == NULL )
		return;

	for(i=0;i<MAX_PARTY;i++){	// リーダーかどうかチェック
		if (p->member[i].account_id == sd->status.account_id &&
		    p->member[i].char_id == sd->status.char_id) {
			if(p->member[i].leader==0)
				return;
		}
	}

	for(i=0;i<MAX_PARTY;i++){	// 所属しているか調べる
		if (p->member[i].account_id == account_id &&
		    strncmp(p->member[i].name, name, 24) == 0){
			intif_party_leave(p->party_id, account_id, p->member[i].char_id);
			return;
		}
	}

	return;
}

/*==========================================
 * パーティ脱退要求
 *------------------------------------------
 */
void party_leave(struct map_session_data *sd)
{
	struct party *p;
	int i;

	nullpo_retv(sd);

	if( (p = party_search(sd->status.party_id)) == NULL )
		return;

	for(i=0;i<MAX_PARTY;i++){	// 所属しているか
		if (p->member[i].account_id == sd->status.account_id &&
		    p->member[i].char_id == sd->status.char_id) {
			intif_party_leave(p->party_id, sd->status.account_id, p->member[i].char_id);
			return;
		}
	}

	return;
}

/*==========================================
 * パーティメンバが脱退した
 *------------------------------------------
 */
void party_member_leaved(int party_id, int account_id, int char_id)
{
	struct map_session_data *sd = map_id2sd(account_id);
	struct party *p = party_search(party_id);

	if(p) {
		int i;
		for(i=0;i<MAX_PARTY;i++) {
			if (p->member[i].account_id == account_id &&
			    p->member[i].char_id == char_id) {
				clif_party_leaved(p,sd,account_id,p->member[i].name,0x00);
				p->member[i].account_id = 0;
				p->member[i].char_id    = 0;
				p->member[i].sd         = NULL;
			}
		}
	}
	if(sd && sd->status.party_id == party_id && sd->status.char_id == char_id) {
		sd->status.party_id    = 0;
		sd->state.party_sended = 0;
		// メモリアルダンジョンに居る場合
		if(map[sd->bl.m].memorial_id) {
			pc_setpos(sd, sd->status.save_point.map, sd->status.save_point.x, sd->status.save_point.y, 3);
		}
		// メモリアルダンジョン情報ウィンドウを閉じる
		if(p && p->memorial_id) {
			clif_memorial_changestatus(sd, 4, 0, 0);
		}
	}

	return;
}

/*==========================================
 * パーティ解散通知
 *------------------------------------------
 */
void party_broken(int party_id)
{
	struct party *p = party_search(party_id);
	int i;

	if(p == NULL)
		return;

	for(i=0;i<MAX_PARTY;i++){
		if(p->member[i].sd!=NULL){
			clif_party_leaved(p, p->member[i].sd, p->member[i].account_id, p->member[i].name, 0x10);
			p->member[i].sd->status.party_id    = 0;
			p->member[i].sd->state.party_sended = 0;
			// メモリアルダンジョンに居る場合
			if(map[p->member[i].sd->bl.m].memorial_id) {
				pc_setpos(p->member[i].sd, p->member[i].sd->status.save_point.map, p->member[i].sd->status.save_point.x, p->member[i].sd->status.save_point.y, 3);
			}
			// メモリアルダンジョン情報ウィンドウを閉じる
			if(p->memorial_id) {
				clif_memorial_changestatus(p->member[i].sd, 4, 0, 0);
			}
		}
	}

	// メモリアルダンジョン削除
	if(p->memorial_id)
		memorial_delete(p->memorial_id);

	numdb_erase(party_db,party_id);
	aFree(p);

	return;
}

/*==========================================
 * 家族公平に必要な最低条件をチェックして
 * 養子キャラのIDを返す
 *------------------------------------------
 */
static int party_check_family_share(struct party *p)
{
	int i, count = 0;
	int p1_idx = -1, p2_idx = -1, baby_idx = -1;
	struct party_member *m;

	nullpo_retr(0, p);

	for(i=0; i<MAX_PARTY; i++) {
		m = &p->member[i];
		if(m->account_id > 0) {
			count++;
			if(m->online && m->sd) {
				if(m->sd->status.baby_id > 0) {
					if(p1_idx <= 0)
						p1_idx = i;
					else
						p2_idx = i;
				}
				if(m->sd->status.parent_id[0] > 0 && m->sd->status.parent_id[1] > 0) {
					baby_idx = i;
				}
			}
		}
	}

	// 3人PTで養子キャラが居てどちらかの親と同一MAP上にいるなら許可
	// ただし親子関係が正しいかどうかのチェックはint_party.cで行う

	if(count == 3 && baby_idx >= 0) {
		m = &p->member[baby_idx];
		if( (p1_idx >= 0 && strcmp(m->map, p->member[p1_idx].map) == 0) ||
		    (p2_idx >= 0 && strcmp(m->map, p->member[p2_idx].map) == 0) )
			return m->sd->status.char_id;
	}
	return 0;
}

/*==========================================
 * パーティの設定変更要求
 *------------------------------------------
 */
void party_changeoption(struct map_session_data *sd, int exp, int item)
{
	struct party *p;
	int i, baby_id = 0;

	nullpo_retv(sd);

	if ((p = party_search(sd->status.party_id)) == NULL)
		return;

	// ONLY the party leader can choose either 'Each Take' or 'Even Share' for experience points.
	for(i = 0; i < MAX_PARTY; i++) {
		if (p->member[i].account_id == sd->status.account_id &&
		    p->member[i].char_id == sd->status.char_id) {
			if (p->member[i].leader) {
				if(exp > 0 && !p->exp) {
					baby_id = party_check_family_share(p);
				}
				if(item < 0) {	// 負のときはアイテム分配設定を変更しない
					item = p->item;
				}
				intif_party_changeoption(sd->status.party_id, sd->status.account_id, baby_id, exp, item);
				return;
			}
		}
	}

	return;
}

/*==========================================
 * パーティの設定変更通知
 *------------------------------------------
 */
void party_optionchanged(int party_id, int account_id, unsigned char exp, unsigned char item, int flag)
{
	struct party *p;
	struct map_session_data *sd=map_id2sd(account_id);

	if( (p=party_search(party_id))==NULL)
		return;

	if(!(flag&0x01))
		p->exp = exp;
	if(!(flag&0x10)) {
		int old_item = p->item;
		p->item = item;
		if(old_item != item)
			clif_party_main_info(p,-1);
	}
	clif_party_option(p,sd,flag);

	return;
}

/*==========================================
 * パーティメンバの移動通知
 *------------------------------------------
 */
void party_recv_movemap(int party_id, int account_id, int char_id, const char *mapname, unsigned char online, unsigned short lv, unsigned short class_)
{
	struct map_session_data *sd;
	struct party *p;
	int i;

	if( (p=party_search(party_id))==NULL)
		return;

	for(i=0;i<MAX_PARTY;i++){
		struct party_member *m = &p->member[i];
		if (m->account_id == account_id && m->char_id == char_id) {
			memcpy(m->map,mapname,16);
			m->online = online;
			m->lv     = lv;
			m->class_ = class_;
			break;
		}
	}
	if(i==MAX_PARTY){
		if(battle_config.error_log)
			printf("party: not found member %d on %d[%s]",account_id,party_id,p->name);
		return;
	}

	for(i=0;i<MAX_PARTY;i++){	// sd再設定
		sd = map_id2sd(p->member[i].account_id);
		if( sd != NULL &&
		    sd->status.char_id == p->member[i].char_id &&
		    sd->status.party_id == p->party_id &&
		    !sd->state.waitingdisconnect )
			p->member[i].sd = sd;
		else
			p->member[i].sd = NULL;
	}

	party_send_xy_clear(p);	// 座標再通知要請

	clif_party_main_info(p,-1);
	clif_party_info(p,-1);

	return;
}

/*==========================================
 * パーティメンバの移動
 *------------------------------------------
 */
void party_send_movemap(struct map_session_data *sd)
{
	struct party *p;

	nullpo_retv(sd);

	if( sd->status.party_id==0 )
		return;

	intif_party_changemap(sd,1);

	if( sd->state.party_sended != 0 )	// もうパーティデータは送信済み
		return;

	// 競合確認
	party_check_conflict(sd);

	// あるならパーティ情報送信
	if( (p=party_search(sd->status.party_id))!=NULL ){
		party_check_member(p);	// 所属を確認する
		if(sd->status.party_id==p->party_id){
			clif_party_main_info(p,sd->fd);
			clif_party_info(p,sd->fd);
			clif_party_option(p,sd,0x100);
			sd->state.party_sended = 1;
			// メモリアルダンジョン情報
			if(p->memorial_id)
				memorial_reqinfo(sd, p->memorial_id);
		}
	}

	return;
}

/*==========================================
 * パーティメンバのログアウト
 *------------------------------------------
 */
void party_send_logout(struct map_session_data *sd)
{
	struct party *p;

	nullpo_retv(sd);

	if( sd->status.party_id>0 )
		intif_party_changemap(sd,0);

	// sdが無効になるのでパーティ情報から削除
	if( (p=party_search(sd->status.party_id))!=NULL ){
		int i;
		for(i=0;i<MAX_PARTY;i++) {
			if(p->member[i].sd==sd)
				p->member[i].sd=NULL;
		}
	}

	return;
}

/*==========================================
 * パーティメッセージ送信
 *------------------------------------------
 */
void party_send_message(struct map_session_data *sd, const char *mes, size_t len)
{
	if(sd->status.party_id==0)
		return;

	intif_party_message(sd->status.party_id,sd->status.account_id,mes,len);

	return;
}

/*==========================================
 * パーティメッセージ受信
 *------------------------------------------
 */
void party_recv_message(int party_id, int account_id, const char *mes, size_t len)
{
	struct party *p;

	if( (p=party_search(party_id))==NULL)
		return;
	clif_party_message(p,account_id,mes,len);

	return;
}

/*==========================================
 * 位置やHP通知
 *------------------------------------------
 */
static int party_send_xyhp_timer_sub(void *key, void *data, va_list ap)
{
	struct party *p=(struct party *)data;
	int i;

	nullpo_retr(0, p);

	for(i=0;i<MAX_PARTY;i++){
		struct map_session_data *sd;
		if((sd=p->member[i].sd)!=NULL){
			// 座標通知
			if(sd->party_x!=sd->bl.x || sd->party_y!=sd->bl.y){
				clif_party_xy(sd);
				sd->party_x=sd->bl.x;
				sd->party_y=sd->bl.y;
			}
			// ＨＰ通知
			if(sd->party_hp!=sd->status.hp){
				clif_party_hp(sd);
				sd->party_hp=sd->status.hp;
			}
		}
	}

	return 0;
}

static int party_send_xyhp_timer(int tid, unsigned int tick, int id, void *data)
{
	numdb_foreach(party_db,party_send_xyhp_timer_sub);

	return 0;
}

/*==========================================
 * HP通知の必要性検査用（map_foreachinmoveareaから呼ばれる）
 *------------------------------------------
 */
int party_send_hp_check(struct block_list *bl,va_list ap)
{
	int party_id;
	struct map_session_data *sd;

	nullpo_retr(0, bl);
	nullpo_retr(0, ap);
	nullpo_retr(0, sd = (struct map_session_data *)bl);

	party_id = va_arg(ap,int);

	if(sd->status.party_id == party_id){
		sd->party_hp = -1;
		return 1;
	}

	return 0;
}

/*==========================================
 * 経験値公平分配
 *------------------------------------------
 */
void party_exp_share(struct party *p, struct mob_data *md, atn_bignumber base_exp, atn_bignumber job_exp)
{
	struct map_session_data *sd;
	int i,c;
	int base_bonus, job_bonus;
	struct map_session_data *sdlist[MAX_PARTY];

	nullpo_retv(p);
	nullpo_retv(md);

	for(i=c=0;i<MAX_PARTY;i++)
	{
		if((sd = p->member[i].sd) != NULL && sd->bl.prev && sd->bl.m == md->bl.m && !unit_isdead(&sd->bl)) {
			if( (sd->sc.data[SC_TRICKDEAD].timer == -1 || !battle_config.noexp_trickdead) && 	// 死んだふりしていない
			    (sd->sc.data[SC_HIDING].timer == -1	   || !battle_config.noexp_hiding   ) )		// ハイドしていない
				sdlist[c++] = sd;
		}
	}
	if(c==0)
		return;

	base_bonus = 100 + (battle_config.pt_bonus_b*(c-1));
	job_bonus  = 100 + (battle_config.pt_bonus_j*(c-1));
	for(i=0;i<c;i++)
	{
		atn_bignumber bexp = base_exp * base_bonus / 100 / c + 1;
		atn_bignumber jexp = job_exp  * job_bonus  / 100 / c + 1;

		pc_gainexp(sdlist[i],md,bexp,jexp,0);
	}

	return;
}

/*==========================================
 * アイテム分配
 *------------------------------------------
 */
int party_loot_share(struct party *p, struct map_session_data *sd, struct item *item_data, int first)
{
	nullpo_retr(1, sd);
	nullpo_retr(1, item_data);

	if(p && p->item&2 && (first || battle_config.party_item_share_type)) {
		struct map_session_data *psd[MAX_PARTY];
		int i, c=0;

		for(i=0; i<MAX_PARTY; i++) {
			if((psd[c] = p->member[i].sd) && psd[c]->bl.prev && psd[c]->bl.m == sd->bl.m && !unit_isdead(&psd[c]->bl))
				c++;
		}
		while(c > 0) {	// ランダム選択
			i = atn_rand()%c;
			if(pc_additem(psd[i],item_data,item_data->amount)) {
				// 取得失敗
				psd[i] = psd[c-1];
				c--;
			} else {
				if(battle_config.party_item_share_show && psd[i] != sd) {
#if PACKETVER < 20071106
					msg_output(sd->fd, msg_txt(177), psd[i]->status.name);	// %sさんにアイテムが分配されました
#else
					clif_show_partyshareitem(sd,item_data);
#endif
				}
				return 0;
			}
		}
	}

	// 分配できないので元のsdに渡す
	return pc_additem(sd,item_data,item_data->amount);
}

/*==========================================
 * 装備ウィンドウ表示
 *------------------------------------------
 */
void party_equip_window(struct map_session_data *sd, int account_id)
{
	struct map_session_data *tsd;

	nullpo_retv(sd);

	if(battle_config.equip_window_type == 0)
		return;

	tsd = map_id2sd(account_id);
	if(tsd == NULL)
		return;

	if(tsd->state.waitingdisconnect)	// 相手が切断待ち
		return;
	if(battle_config.equip_window_type == 1) {
		if(tsd->status.party_id <= 0 || sd->status.party_id != tsd->status.party_id)	// PTが異なる
			return;
	}
	if(sd->bl.m != tsd->bl.m || path_distance(sd->bl.x, sd->bl.y, tsd->bl.x, tsd->bl.y) > AREA_SIZE)	// 距離が遠い
		return;
	if(!tsd->status.show_equip) {	// 相手が装備を公開してない
		clif_msgstringtable(sd, 0x54d);
		return;
	}

	clif_party_equiplist(sd, tsd);

	return;
}

/*==========================================
 * パーティーリーダー変更要求
 *------------------------------------------
 */
void party_changeleader(struct map_session_data *sd, int id)
{
	struct party *p;
	struct map_session_data *tsd;
	int i,j;

	nullpo_retv(sd);

	if(sd->status.party_id == 0)
		return;

	if((p = party_search(sd->status.party_id)) == NULL)
		return;

	for(i=0; i<MAX_PARTY && p->member[i].sd!=sd; i++);

	if(i >= MAX_PARTY)
		return;

	if(!p->member[i].leader)
		return;

	tsd = map_id2sd(id);

	if(tsd == NULL || tsd->status.party_id != sd->status.party_id)
		return;

	for(j=0; j<MAX_PARTY && p->member[j].sd!=tsd; j++);

	if(j >= MAX_PARTY)
		return;

	intif_party_leaderchange(p->party_id,p->member[j].account_id,p->member[j].char_id);

	return;
}

/*==========================================
 * パーティーリーダー変更通知
 *------------------------------------------
 */
void party_leaderchanged(int party_id, int old_account_id, int account_id)
{
	struct party *p = party_search(party_id);
	int i,j;

	if(p == NULL)
		return;

	for(i=0; i<MAX_PARTY && p->member[i].account_id!=old_account_id; i++);

	if(i >= MAX_PARTY)
		return;

	for(j=0; j<MAX_PARTY && p->member[j].account_id!=account_id; j++);

	if(j >= MAX_PARTY)
		return;

	p->member[i].leader = 0;
	p->member[j].leader = 1;

#if PACKETVER < 20091208
	for(i=0; i<MAX_PARTY; i++) {
		struct map_session_data *sd = p->member[i].sd;
		if(sd)
			clif_displaymessage(sd->fd,msg_txt(194));
	}
	clif_party_info(p,-1);
#else
	clif_partyleader_info(p,old_account_id,account_id);
#endif

	return;
}

/*==========================================
 * 同じマップのパーティメンバー全体に処理をかける
 *------------------------------------------
 */
int party_foreachsamemap(int (*func)(struct block_list*,va_list),struct map_session_data *sd,int range,...)
{
	struct party *p;
	int i, x0, y0, x1, y1;
	struct block_list *list[MAX_PARTY];
	int blockcount = 0;
	int ret = 0;

	nullpo_retr(0, sd);

	if((p = party_search(sd->status.party_id)) == NULL)
		return 0;

	x0 = sd->bl.x - range;
	y0 = sd->bl.y - range;
	x1 = sd->bl.x + range;
	y1 = sd->bl.y + range;

	for(i=0; i<MAX_PARTY; i++) {
		struct party_member *m = &p->member[i];
		if(m != NULL && m->sd != NULL) {
			if( sd->bl.m != m->sd->bl.m )
				continue;
			if( m->sd->bl.x < x0 || m->sd->bl.y < y0 ||
			    m->sd->bl.x > x1 || m->sd->bl.y > y1 )
				continue;
			list[blockcount++] = &m->sd->bl;
		}
	}

	map_freeblock_lock();	// メモリからの解放を禁止する

	for(i=0; i<blockcount; i++) {
		if(list[i]->prev) {	// 有効かどうかチェック
			va_list ap;
			va_start(ap, range);
			ret += func(list[i],ap);
			va_end(ap);
		}
	}

	map_freeblock_unlock();	// 解放を許可する

	return ret;
}

/*==========================================
 * 同じマップでオンライン中のパーティメンバーの数を返す
 * 0:居ないか,PTがない
 *------------------------------------------
 */
int party_check_same_map_member_count(struct map_session_data *sd)
{
	int count = 0;
	int i;
	struct party* pt = NULL;

	nullpo_retr(0, sd);

	pt = party_search(sd->status.party_id);

	if(pt == NULL)
		return 0;

	for(i=0;i<MAX_PARTY;i++)
	{
		if(pt->member[i].online && pt->member[i].sd!=NULL)
		{
			if(sd != pt->member[i].sd && sd->bl.m == pt->member[i].sd->bl.m)
				count++;
		}
	}

	return count;
}

/*==========================================
 * ログイン中のパーティメンバーの１人のsdを返す
 *------------------------------------------
 */
struct map_session_data *party_getavailablesd(struct party *p)
{
	int i;

	nullpo_retr(NULL, p);

	for(i = 0; i < MAX_PARTY; i++) {
		if(p->member[i].sd) {
			return p->member[i].sd;
		}
	}

	return NULL;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
static int party_db_final(void *key,void *data,va_list ap)
{
	aFree(data);

	return 0;
}

void do_final_party(void)
{
	if(party_db)
		numdb_final(party_db,party_db_final);

	return;
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
void do_init_party(void)
{
	unsigned int tick = gettick();

	party_db = numdb_init();

	add_timer_func_list(party_send_xyhp_timer);
	add_timer_interval(tick+PARTY_SEND_XYHP_INVERVAL,party_send_xyhp_timer,0,NULL,PARTY_SEND_XYHP_INVERVAL);

	return;
}
