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

#include "db.h"
#include "timer.h"
#include "socket.h"
#include "nullpo.h"
#include "malloc.h"
#include "utils.h"
#include "grfio.h"

#include "guild.h"
#include "storage.h"
#include "battle.h"
#include "npc.h"
#include "pc.h"
#include "map.h"
#include "path.h"
#include "skill.h"
#include "mob.h"
#include "intif.h"
#include "clif.h"
#include "status.h"
#include "msg.h"

static struct dbt *guild_db = NULL;
static struct dbt *guild_expcache_db = NULL;
static struct dbt *guild_infoevent_db = NULL;
static struct dbt *guild_castleinfoevent_db = NULL;

static struct guild_castle castle_db[MAX_GUILDCASTLE];
static int guild_skill_max[MAX_GUILDSKILL];

struct eventlist {
	char name[50];
	struct eventlist *next;
};

#define GUILD_PAYEXP_INVERVAL 10000	// ギルドEXPキャッシュの間隔(最大生存時間、ミリ秒)
#define GUILD_SEND_XY_INVERVAL 1000	// 座標送信の間隔

// ギルドのEXPキャッシュ
struct guild_expcache {
	int guild_id;
	int account_id;
	int char_id;
	int exp;
};

/*==========================================
 * ギルドスキルdbのアクセサ（今は直打ちで代用）
 *------------------------------------------
 */
int guild_skill_get_inf(int id)
{
	return skill_get_inf(id);
}

int guild_skill_get_sp(int id,int lv)
{
	return skill_get_sp(id,lv);
}

int guild_skill_get_range(int id,int lv)
{
	return skill_get_range(id,lv);
}

int guild_skill_get_lv(struct guild *g,int id)
{
	int idx = id-GUILD_SKILLID;

	if(g == NULL) return 0;

	if (idx < 0 || idx >= MAX_GUILDSKILL)
		return 0;

	return g->skill[id-GUILD_SKILLID].lv;
}

/*==========================================
 * スキルのMaxLvを受信（初期化時）
 *------------------------------------------
 */
void guild_skillmax_load(int len, int *maxlv)
{
	if( maxlv == NULL || sizeof(guild_skill_max) != len - 4) {
		if(battle_config.etc_log)
			printf("guild_skillmax_load: data size error %lu %d\n", (unsigned long)sizeof(guild_skill_max), len - 4);
		memset(guild_skill_max, 0, sizeof(guild_skill_max));
	} else {
		memcpy(guild_skill_max, maxlv, sizeof(guild_skill_max));
	}

	return;
}

/*==========================================
 * スキルのMaxLvを返す
 *------------------------------------------
 */
int guild_get_skilltree_max(int id)
{
	int idx = id - GUILD_SKILLID;

	if(idx < 0 || idx >= MAX_GUILDSKILL)
		return 0;

	return guild_skill_max[idx];
}

/*==========================================
 * ギルドスキルがあるか確認
 *------------------------------------------
 */
int guild_checkskill(struct guild *g,int id)
{
	int idx = id-GUILD_SKILLID;

	if (idx < 0 || idx >= MAX_GUILDSKILL)
		return 0;
	return g->skill[idx].lv;
}

/*==========================================
 * ギルドマスターのsdを返す
 *------------------------------------------
 */
struct map_session_data *guild_get_guildmaster_sd(struct guild *g)
{
	if(g == NULL)
		return NULL;

	return g->member[0].sd;
}

/*==========================================
 * ギルド検索
 *------------------------------------------
 */
struct guild *guild_search(int guild_id)
{
	return (struct guild *)numdb_search(guild_db,guild_id);
}

/*==========================================
 * ギルド名検索
 *------------------------------------------
 */
static int guild_searchname_sub(void *key,void *data,va_list ap)
{
	struct guild *g, **dst;
	char *str;

	g   = (struct guild *)data;
	str = va_arg(ap,char *);
	dst = va_arg(ap,struct guild **);

	if(*dst == NULL) {
		if(strcmp(g->name,str) == 0)
			*dst = g;
	}

	return 0;
}

struct guild* guild_searchname(const char *str)
{
	struct guild *g = NULL;

	numdb_foreach(guild_db,guild_searchname_sub,str,&g);

	return g;
}

/*==========================================
 * ギルド城検索
 *------------------------------------------
 */
struct guild_castle *guild_castle_search(int gcid)
{
	if(gcid < 0 || gcid >= MAX_GUILDCASTLE)
		return NULL;

	return &castle_db[gcid];
}

/*==========================================
 * mapnameに対応したアジトのgcを返す
 *------------------------------------------
 */
struct guild_castle *guild_mapname2gc(const char *mapname)
{
	int i;

	for(i = 0; i < MAX_GUILDCASTLE; i++) {
		struct guild_castle *gc = guild_castle_search(i);
		if(gc && strcmp(gc->map_name, mapname) == 0)
			return gc;
	}

	return NULL;
}

/*==========================================
 * MAP番号に対応したアジトのgcを返す
 * 他サーバ管理のMAPの場合は取得不可
 *------------------------------------------
 */
struct guild_castle *guild_mapid2gc(int m)
{
	int i;

	for(i = 0; i < MAX_GUILDCASTLE; i++) {
		struct guild_castle *gc = guild_castle_search(i);
		if(gc && gc->m == m)
			return gc;
	}

	return NULL;
}

/*==========================================
 * ログイン中のギルドメンバーの１人のsdを返す
 *------------------------------------------
 */
struct map_session_data *guild_getavailablesd(struct guild *g)
{
	int i;

	nullpo_retr(NULL, g);

	for(i=0;i<g->max_member;i++) {
		if(g->member[i].sd!=NULL)
			return g->member[i].sd;
	}

	return NULL;
}

/*==========================================
 * ギルドメンバーのインデックスを返す
 *------------------------------------------
 */
int guild_getindex(struct guild *g,int account_id,int char_id)
{
	int i;

	if(g==NULL)
		return -1;

	for(i=0;i<g->max_member;i++) {
		if( g->member[i].account_id==account_id &&
		    g->member[i].char_id==char_id )
			return i;
	}

	return -1;
}

/*==========================================
 * ギルドメンバーの役職を返す
 *------------------------------------------
 */
int guild_getposition(struct map_session_data *sd,struct guild *g)
{
	int i;

	nullpo_retr(-1, sd);

	if(g==NULL && (g=guild_search(sd->status.guild_id))==NULL)
		return -1;
	for(i=0;i<g->max_member;i++) {
		if (g->member[i].char_id == sd->status.char_id) // not need to check accoun_id. char_id is unique
			return g->member[i].position;
	}

	return -1;
}

/*==========================================
 * メンバー情報の作成
 *------------------------------------------
 */
static void guild_makemember(struct guild_member *m,struct map_session_data *sd)
{
	nullpo_retv(sd);

	memset(m,0,sizeof(struct guild_member));

	m->account_id = sd->status.account_id;
	m->char_id    = sd->status.char_id;
	m->hair       = sd->status.hair;
	m->hair_color = sd->status.hair_color;
	m->gender     = sd->sex;
	m->class_     = sd->status.class_;
	m->lv         = sd->status.base_level;
	m->online     = 1;
	m->position   = MAX_GUILDPOSITION-1;
	memcpy(m->name,sd->status.name,24);

	return;
}

/*==========================================
 * ギルド競合確認
 *------------------------------------------
 */
static void guild_check_conflict(struct map_session_data *sd)
{
	nullpo_retv(sd);

	intif_guild_checkconflict(sd->status.guild_id,sd->status.account_id,sd->status.char_id);

	return;
}

/*==========================================
 * ギルドのEXPキャッシュをinter鯖にフラッシュ
 *------------------------------------------
 */
static int guild_payexp_timer_sub(void *key,void *data,va_list ap)
{
	int i;
	struct guild_expcache *c;
	struct guild *g;
	atn_bignumber tmp;

	nullpo_retr(0, c = (struct guild_expcache *)data);

	if( (g = guild_search(c->guild_id)) == NULL )
		return 0;
	if( (i = guild_getindex(g,c->account_id,c->char_id)) < 0 )
		return 0;

	tmp = (atn_bignumber)g->member[i].exp + c->exp;
	g->member[i].exp = (tmp > 0x7fffffff)? 0x7fffffff: (tmp < 0)? 0: (int)tmp;

	// メンバーのExpがMAX値でも上納は行う
	intif_guild_change_memberinfo(g->guild_id,c->account_id,c->char_id,GMI_EXP,&c->exp,sizeof(c->exp));

	aFree(c);

	return 0;
}

void guild_flush_expcache(void)
{
	numdb_clear(guild_expcache_db,guild_payexp_timer_sub);
	return;
}

static int guild_payexp_timer(int tid,unsigned int tick,int id,void *data)
{
	guild_flush_expcache();
	return 0;
}

/*==========================================
 * ギルドのEXP上納
 *------------------------------------------
 */
atn_bignumber guild_payexp(struct map_session_data *sd,atn_bignumber exp)
{
	struct guild *g;
	struct guild_expcache *c;
	int pos,per;
	atn_bignumber exp2;

	nullpo_retr(0, sd);

	if(sd->status.guild_id==0 || (g=guild_search(sd->status.guild_id))==NULL )
		return 0;
	if( (pos=guild_getposition(sd,g)) < 0)
		return 0;
	if( (per=g->position[pos].exp_mode)<=0 )
		return 0;
	if( per>100 )
		per=100;
	if( (exp2=exp*per/100)<=0 )
		return 0;

	if(battle_config.guild_exp_rate!=100)
		exp2 = exp2*battle_config.guild_exp_rate/100;

	if( (c = (struct guild_expcache *)numdb_search(guild_expcache_db,sd->status.char_id)) == NULL ){
		c=(struct guild_expcache *)aCalloc(1,sizeof(struct guild_expcache));
		c->guild_id=sd->status.guild_id;
		c->account_id=sd->status.account_id;
		c->char_id=sd->status.char_id;
		numdb_insert(guild_expcache_db,c->char_id,c);
	}

	if(0x7fffffff - c->exp <= (int)exp2)
		c->exp = 0x7fffffff;
	else
		c->exp += (int)exp2;

	return exp2;
}

/*==========================================
 * ギルドEXP取得
 *------------------------------------------
 */
void guild_getexp(struct map_session_data *sd, int exp)
{
	struct guild_expcache *c;
	atn_bignumber tmp;

	nullpo_retv(sd);

	if (sd->status.guild_id == 0 || guild_search(sd->status.guild_id) == NULL)
		return;

	if ((c = (struct guild_expcache *)numdb_search(guild_expcache_db,sd->status.char_id)) == NULL) {
		c = (struct guild_expcache *)aCalloc(1,sizeof(struct guild_expcache));
		c->guild_id   = sd->status.guild_id;
		c->account_id = sd->status.account_id;
		c->char_id    = sd->status.char_id;
		numdb_insert(guild_expcache_db,c->char_id,c);
	}
	tmp = (atn_bignumber)c->exp + exp;
	c->exp = (tmp > 0x7fffffff) ? 0x7fffffff : (int)tmp;

	return;
}

/*==========================================
 * 作成要求
 *------------------------------------------
 */
void guild_create(struct map_session_data *sd, const char *name)
{
	nullpo_retv(sd);

	if(sd->status.guild_id == 0 && sd->state.guild_creating == 0) {
		if(!battle_config.guild_emperium_check || pc_search_inventory(sd,714) >= 0) {
			struct guild_member m;
			// check no guild name! (hacker)
			if (name[0] == '\0') {
				clif_guild_created(sd, 2); // 0x167 <flag>.b: 0: Guild has been created., 1: You are already in a guild., 2: That Guild Name already exists., 3: You need the necessary item to create a Guild.
				return;
			}

			// check guild name with " -> use a " in a guild name disables /breakguild command (it doesn't work)
			if (strchr(name, '\"') != NULL) {
				clif_guild_created(sd, 2); // 0x167 <flag>.b: 0: Guild has been created., 1: You are already in a guild., 2: That Guild Name already exists., 3: You need the necessary item to create a Guild.
				return;
			}
			guild_makemember(&m, sd);
			m.position=0;
			sd->state.guild_creating = 1;
			intif_guild_create(name, &m);
		} else {
			clif_guild_created(sd,3);	// エンペリウムがない
		}
	} else {
		clif_guild_created(sd,1);	// すでに所属している
	}
	return;
}

/*==========================================
 * 作成可否
 *------------------------------------------
 */
void guild_created(int account_id, int guild_id)
{
	struct map_session_data *sd=map_id2sd(account_id);

	if(sd==NULL)
		return;

	if(guild_id>0) {
		sd->status.guild_id    = guild_id;
		sd->state.guild_sended = 0;
		clif_guild_created(sd,0);
		if(battle_config.guild_emperium_check) {
			int idx = pc_search_inventory(sd,714);
			if(idx >= 0)
				pc_delitem(sd,idx,1,0,0);	// エンペリウム消耗
		}
	} else {
		clif_guild_created(sd,2);	// 作成失敗（同名ギルド存在）
	}
	sd->state.guild_creating = 0;

	return;
}

/*==========================================
 * 情報要求
 *------------------------------------------
 */
void guild_request_info(int guild_id)
{
	intif_guild_request_info(guild_id);

	return;
}

/*==========================================
 * イベント付き情報要求
 *------------------------------------------
 */
void guild_npc_request_info(int guild_id,const char *event)
{
	struct eventlist *ev;

	if( guild_search(guild_id) ){
		if(event && *event)
			npc_event_do(event);
		return;
	}

	if(event==NULL || *event==0) {
		guild_request_info(guild_id);
		return;
	}

	ev=(struct eventlist *)aCalloc(1,sizeof(struct eventlist));
	strncpy(ev->name,event,sizeof(ev->name));
	ev->name[sizeof(ev->name)-1] = '\0';	// force \0 terminal
	ev->next=(struct eventlist *)numdb_insert(guild_infoevent_db,guild_id,ev);
	guild_request_info(guild_id);

	return;
}

/*==========================================
 * 所属キャラの確認
 *------------------------------------------
 */
static void guild_check_member(struct guild *g)
{
	int i;
	struct map_session_data *sd;

	nullpo_retv(g);

	for(i=0;i<fd_max;i++){
		if(session[i] && (sd = (struct map_session_data *)session[i]->session_data) && sd->state.auth && !sd->state.waitingdisconnect){
			if(sd->status.guild_id==g->guild_id){
				int j,f=1;
				for(j=0;j<MAX_GUILD;j++){	// データがあるか
					if( g->member[j].account_id==sd->status.account_id &&
					    g->member[j].char_id==sd->status.char_id )
					{
						struct guild_member *m=&g->member[j];
						m->hair=sd->status.hair;
						m->hair_color=sd->status.hair_color;
						m->gender=sd->sex;
						f=0;
					}
				}
				if(f){
					sd->status.guild_id    = 0;
					sd->state.guild_sended = 0;
					sd->guild_emblem_id    = 0;
					if(battle_config.error_log)
						printf("guild: check_member %d[%s] is not member\n",sd->status.account_id,sd->status.name);
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
void guild_recv_noinfo(int guild_id)
{
	int i;
	struct map_session_data *sd;

	for(i=0;i<fd_max;i++){
		if(session[i] && (sd = (struct map_session_data *)session[i]->session_data) && sd->state.auth && !sd->state.waitingdisconnect){
			if(sd->status.guild_id==guild_id)
				sd->status.guild_id=0;
		}
	}

	return;
}

/*==========================================
 * 情報取得
 *------------------------------------------
 */
void guild_recv_info(struct guild *sg)
{
	struct map_session_data *sd;
	struct guild *g;
	struct guild before;
	struct eventlist *ev, *ev2;
	int i, bm = 0, m = 0;

	nullpo_retv(sg);

	if((g = (struct guild *)numdb_search(guild_db,sg->guild_id)) == NULL) {
		g = (struct guild *)aCalloc(1,sizeof(struct guild));
		numdb_insert(guild_db,sg->guild_id,g);
		before = *sg;

		// 最初のロードなのでユーザーのチェックを行う
		guild_check_member(sg);
	} else {
		before = *g;
	}

	memcpy(g,sg,sizeof(struct guild));

	for(i=0; i<g->max_member; i++) {	// sdの設定と人数の確認
		if(g->member[i].account_id > 0) {
			sd = map_id2sd(g->member[i].account_id);
			if( sd != NULL &&
			    sd->status.char_id == g->member[i].char_id &&
			    sd->status.guild_id == g->guild_id &&
			    !sd->state.waitingdisconnect )
				g->member[i].sd = sd;
			else
				g->member[i].sd = NULL;
			m++;
		} else {
			g->member[i].sd = NULL;
		}
		if(before.member[i].account_id > 0)
			bm++;
	}

	for(i=0; i<g->max_member; i++) {		// 情報の送信
		sd = g->member[i].sd;
		if(sd == NULL)
			continue;

		if(before.guild_lv != g->guild_lv || bm != m || before.max_member != g->max_member) {
			clif_guild_basicinfo(sd, g);	// 基本情報送信
			clif_guild_emblem(sd, g);	// エンブレム送信
		}

		if(bm != m) {	// メンバー情報送信
			clif_guild_memberlist(g->member[i].sd, g);
		}

		if(before.skill_point != g->skill_point)
			clif_guild_skillinfo(sd, g);	// スキル情報送信

		if(sd->state.guild_sended == 0) {	// 未送信なら所属情報も送る
			clif_guild_belonginfo(sd,g);
			clif_guild_notice(sd,g);
			sd->guild_emblem_id    = g->emblem_id;
			sd->state.guild_sended = 1;
		}
	}

	// イベントの発生
	if((ev = (struct eventlist *)numdb_search(guild_infoevent_db,sg->guild_id)) != NULL) {
		numdb_erase(guild_infoevent_db,sg->guild_id);
		while(ev) {
			npc_event_do(ev->name);
			ev2 = ev->next;
			aFree(ev);
			ev = ev2;
		}
	}

	return;
}

/*==========================================
 * ギルドへの勧誘
 *------------------------------------------
 */
void guild_invite(struct map_session_data *sd, int account_id)
{
	struct map_session_data *tsd;
	struct guild *g;
	int i, ps;

	nullpo_retv(sd);

	g = guild_search(sd->status.guild_id);
	if (g == NULL)
		return;

	tsd = map_id2sd(account_id);
	if (tsd == NULL)
		return;

	// player must have ability to invite...
	if ((ps = guild_getposition(sd, g)) < 0 || !(g->position[ps].mode & 0x0001))
		return;

	// player must be on same map... (how to use mouse menu otherwise?)
	if (sd->bl.m != tsd->bl.m)
		return;
	// and in visible area of member
	if (path_distance(sd->bl.x,sd->bl.y,tsd->bl.x,tsd->bl.y) > AREA_SIZE)
		return;

	// GVGでは勧誘できない
	if (!battle_config.allow_guild_invite_in_gvg) {
		if (agit_flag && map[sd->bl.m].flag.gvg)
			return;
	}

	if(tsd->state.waitingdisconnect) {	// 相手が切断待ち
		clif_guild_inviteack(sd,1);
		return;
	}
	if(!battle_config.invite_request_check) {
		if (tsd->party_invite > 0 || tsd->trade.partner || tsd->adopt_invite) {	// 相手が取引中かどうか
			clif_guild_inviteack(sd,1);
			return;
		}
	}
	if(tsd->status.guild_id > 0 || tsd->guild_invite > 0) {	// 相手の所属確認
		clif_guild_inviteack(sd,0);
		return;
	}

	// 定員確認
	for(i=0; i<g->max_member; i++) {
		if(g->member[i].account_id == 0)
			break;
	}
	if(i >= g->max_member) {
		clif_guild_inviteack(sd,3);
		return;
	}

	tsd->guild_invite         = sd->status.guild_id;
	tsd->guild_invite_account = sd->status.account_id;

	clif_guild_invite(tsd,g);

	return;
}

/*==========================================
 * ギルド勧誘への返答
 *------------------------------------------
 */
void guild_reply_invite(struct map_session_data *sd, int guild_id, unsigned char flag)
{
	struct map_session_data *tsd;

	nullpo_retv(sd);

	if(sd->guild_invite != guild_id)	// 勧誘とギルドIDが違う
		return;

	tsd = map_id2sd(sd->guild_invite_account);

	if(flag == 1) {	// 承諾
		struct guild_member m;
		struct guild *g;
		int i;

		// 定員確認
		if(tsd == NULL || (g = guild_search(tsd->status.guild_id)) == NULL) {
			sd->guild_invite         = 0;
			sd->guild_invite_account = 0;
			return;
		}
		for(i=0; i<g->max_member; i++) {
			if(g->member[i].account_id == 0)
				break;
		}
		if(i >= g->max_member) {
			sd->guild_invite         = 0;
			sd->guild_invite_account = 0;
			clif_guild_inviteack(tsd,3);
			return;
		}

		// inter鯖へ追加要求
		guild_makemember(&m,sd);
		intif_guild_addmember(sd->guild_invite, &m);
	} else {		// 拒否
		sd->guild_invite         = 0;
		sd->guild_invite_account = 0;
		if(tsd)
			clif_guild_inviteack(tsd,1);
	}

	return;
}

/*==========================================
 * ギルドメンバが追加された
 *------------------------------------------
 */
void guild_member_added(int guild_id, int account_id, int char_id, unsigned char flag)
{
	struct map_session_data *sd, *sd2;

	if(guild_search(guild_id) == NULL)
		return;

	sd = map_id2sd(account_id);
	if(sd == NULL || sd->guild_invite == 0) {
		if(flag == 0) {
			// キャラ側に登録できなかったため脱退要求を出す
			char mes[40];
			if(battle_config.error_log)
				printf("guild: member added error %d is not online\n",account_id);

			strncpy(mes, msg_txt(176), 40); // **登録失敗**
			mes[39] = '\0';			// force \0 terminal

			intif_guild_leave(guild_id, account_id,char_id, 0, mes);
		}
		return;
	}
	sd->guild_invite         = 0;
	sd->guild_invite_account = 0;

	sd2 = map_id2sd(sd->guild_invite_account);

	if(flag == 1) {	// 失敗
		if(sd2)
			clif_guild_inviteack(sd2,3);
		return;
	}

	// 成功
	sd->state.guild_sended = 0;
	sd->status.guild_id    = guild_id;

	if(sd2)
		clif_guild_inviteack(sd2,2);

	// いちおう競合確認
	guild_check_conflict(sd);

	return;
}

/*==========================================
 * ギルド脱退要求
 *------------------------------------------
 */
void guild_leave(struct map_session_data *sd, int guild_id, int account_id, int char_id, const char *mes)
{
	struct guild *g;
	int i;

	nullpo_retv(sd);

	if (sd->status.account_id != account_id || sd->status.char_id != char_id || sd->status.guild_id != guild_id)
		return;

	g = guild_search(sd->status.guild_id);
	if (g == NULL)
		return;

	if (!battle_config.allow_guild_leave_in_gvg) {
		if (agit_flag && map[sd->bl.m].flag.gvg)
			return;
	}

	for(i=0;i<g->max_member;i++){	// 所属しているか
		if(g->member[i].char_id == sd->status.char_id) { // char_id is unique. don't check account_id
			intif_guild_leave(g->guild_id,sd->status.account_id,sd->status.char_id,0,mes);
			return;
		}
	}

	return;
}

/*==========================================
 * ギルド追放要求
 *------------------------------------------
 */
void guild_explusion(struct map_session_data *sd, int guild_id, int account_id, int char_id, const char *mes)
{
	struct guild *g;
	int i,ps;

	nullpo_retv(sd);

	g = guild_search(sd->status.guild_id);
	if(g==NULL)
		return;

	if (sd->status.guild_id != guild_id)
		return;

	if( (ps=guild_getposition(sd,g))<0 || !(g->position[ps].mode&0x0010) )
		return;	// 処罰権限無し

	for(i=0;i<g->max_member;i++){	// 所属しているか
		if (g->member[i].char_id == char_id) { // check only char_id (it's unique). account_id is not necessary
			// シーズモードでは抜けれない
			if(!battle_config.allow_guild_leave_in_gvg)
			{
				if(g->member[i].sd){
					if(agit_flag && map[g->member[i].sd->bl.m].flag.gvg)
						return;
				}
			}
			intif_guild_leave(g->guild_id,account_id,char_id,1,mes);
			return;
		}
	}

	return;
}

/*==========================================
 * ギルドメンバが脱退した
 *------------------------------------------
 */
void guild_member_leaved(int guild_id, int account_id, int char_id, unsigned char flag, const char *name, const char *mes)
{
	struct map_session_data *sd=map_id2sd(account_id);
	struct guild *g=guild_search(guild_id);

	if(g!=NULL){
		int i;
		for(i=0;i<g->max_member;i++) {
			if(g->member[i].account_id==account_id && g->member[i].char_id==char_id) {
				struct map_session_data *sd2=sd;
				if(sd2==NULL)
					sd2=guild_getavailablesd(g);
				if(sd2!=NULL){
					if(flag==0)
						clif_guild_leave(sd2,name,mes);
					else
						clif_guild_explusion(sd2,name,mes);
				}
				g->member[i].account_id=0;
				g->member[i].sd=NULL;
			}
		}
		// メンバーリストを全員に再通知
		for(i=0;i<g->max_member;i++){
			if( g->member[i].sd!=NULL )
				clif_guild_memberlist(g->member[i].sd, g);
		}
	}
	if(sd!=NULL && sd->status.char_id==char_id && sd->status.guild_id==guild_id){
		if(sd->state.storage_flag == 2)
			storage_guild_storageclose(sd);
		sd->status.guild_id    = 0;
		sd->guild_emblem_id    = 0;
		sd->state.guild_sended = 0;
	}

	return;
}

/*==========================================
 * 位置通知クリア
 *------------------------------------------
 */
static void guild_send_xy_clear(struct guild *g)
{
	int i;

	nullpo_retv(g);

	for(i=0; i < g->max_member; i++) {
		struct map_session_data *sd;
		if((sd = g->member[i].sd) != NULL) {
			sd->guild_x = -1;
			sd->guild_y = -1;
		}
	}

	return;
}

/*==========================================
 * 位置の通知タイマー
 *------------------------------------------
 */
static int guild_send_xy_timer_sub(void *key,void *data,va_list ap)
{
	struct guild *g = (struct guild *)data;
	int i;

	nullpo_retr(0, g);

	for(i=0; i < g->max_member; i++) {
		struct map_session_data *sd;
		if((sd = g->member[i].sd) != NULL) {
			if(sd->guild_x != sd->bl.x || sd->guild_y != sd->bl.y) {
				if(battle_config.pvp_send_guild_xy || !map[sd->bl.m].flag.pvp) {	// PvPモードで送信するか
					clif_guild_xy(sd);
				}
				sd->guild_x = sd->bl.x;
				sd->guild_y = sd->bl.y;
			}
		}
	}

	return 0;
}

static int guild_send_xy_timer(int tid,unsigned int tick,int id,void *data)
{
	numdb_foreach(guild_db,guild_send_xy_timer_sub);

	return 0;
}

/*==========================================
 * ギルドメンバのオンライン状態/Lv更新送信
 *------------------------------------------
 */
void guild_send_memberinfoshort(struct map_session_data *sd, unsigned char online)
{
	struct guild *g;

	nullpo_retv(sd);

	if(sd->status.guild_id<=0)
		return;
	g=guild_search(sd->status.guild_id);
	if(g==NULL)
		return;

	intif_guild_memberinfoshort(g->guild_id,
		sd->status.account_id,sd->status.char_id,online,sd->status.base_level,sd->status.class_);

	if( !online ){	// ログアウトするならsdをクリアして終了
		int i=guild_getindex(g,sd->status.account_id,sd->status.char_id);
		if(i>=0)
			g->member[i].sd=NULL;

		if(i==0)	// マスターが落ちた
		{
			struct map_session_data *member = NULL;
			for(i=1;i<g->max_member;i++){
				member = g->member[i].sd;
				if(member && member->under_the_influence_of_the_guild_skill > 0)
					status_calc_pc(sd,0);
			}
		}
		return;
	}

	if( sd->state.guild_sended != 0 )	// ギルド初期送信データは送信済み
		return;

	// 競合確認
	guild_check_conflict(sd);

	// ギルド初期送信データ送信
	guild_check_member(g);	// 所属を確認する
	if(sd->status.guild_id==g->guild_id){
		clif_guild_belonginfo(sd,g);
		clif_guild_notice(sd,g);
		sd->state.guild_sended = 1;
		sd->guild_emblem_id    = g->emblem_id;
	}

	/*
	//guild_recv_memberinfoshortで更新されるからいらない？
	if(g)
	{
		struct map_session_data *gmsd = g->member[0].sd;
		if(gmsd && battle_config.guild_hunting_skill_available
			&& (pc_checkskill(gmsd,GD_LEADERSHIP) > 0 || pc_checkskill(gmsd,GD_SOULCOLD) > 0
					||pc_checkskill(gmsd,GD_GLORYWOUNDS) > 0 ||pc_checkskill(gmsd,GD_HAWKEYES) > 0))
		{
			if(sd == gmsd && battle_config.allow_me_guild_skill)
				status_calc_pc(gmsd,0);
			pc_check_guild_skill_effective_range(gmsd);
		}
	}
	*/

	return;
}

/*==========================================
 * ギルドメンバのオンライン状態/Lv更新通知
 *------------------------------------------
 */
void guild_recv_memberinfoshort(int guild_id, int account_id, int char_id, unsigned char online, int lv, int class_)
{
	int i, alv = 0, c = 0, idx = -1, om = 0;
	unsigned char oldonline = !online;
	struct guild *g=guild_search(guild_id);
	struct map_session_data *sd;

	if(g==NULL)
		return;

	for(i=0;i<g->max_member;i++){
		struct guild_member *m=&g->member[i];
		if(!m) continue;
		if(m->account_id==account_id && m->char_id==char_id ){
			oldonline = m->online;
			m->online = online;
			m->lv     = lv;
			m->class_ = class_;
			idx       = i;
		}
		if(m->account_id>0){
			alv+=m->lv;
			c++;
		}
		if(m->online)
			om++;
	}
	if(idx == -1 || c == 0) {
		// ギルドのメンバー外なので追放扱いする
		sd = map_id2sd(account_id);
		if(sd && sd->status.char_id == char_id) {
			sd->status.guild_id    = 0;
			sd->guild_emblem_id    = 0;
			sd->state.guild_sended = 0;
		}
		if(battle_config.error_log)
			printf("guild: not found member %d,%d on %d[%s]\n",account_id,char_id,guild_id,g->name);
		return;
	}
	g->average_lv=alv/c;
	g->connect_member=om;

	for(i=0;i<g->max_member;i++){	// sd再設定
		sd = map_id2sd(g->member[i].account_id);
		g->member[i].sd=(sd!=NULL &&
			sd->status.char_id==g->member[i].char_id &&
			sd->status.guild_id==guild_id &&
			!sd->state.waitingdisconnect)?sd:NULL;
	}

	if(oldonline!=online)	// オンライン状態が変わったので通知
		clif_guild_memberlogin_notice(g,idx,online);

	// マップ移動,接続などでギルドスキルの有効チェック＆ステータス更新
	if(g->member[0].sd)
		pc_check_guild_skill_effective_range(g->member[0].sd);
	// ここにクライアントに送信処理が必要

	guild_send_xy_clear(g);	// 座標再通知要請

	return;
}

/*==========================================
 * ギルド会話送信
 *------------------------------------------
 */
void guild_send_message(struct map_session_data *sd, const char *mes, size_t len)
{
	struct guild *g;
	int i;

	nullpo_retv(sd);

	if(sd->status.guild_id == 0 || (g = guild_search(sd->status.guild_id)) == NULL)
		return;

	intif_guild_message(sd->status.guild_id,sd->status.account_id,mes,len);

	if(battle_config.alliance_message && sd->state.alliance_message)
	{
		for(i = 0; i < MAX_GUILDALLIANCE; ++i)
		{
			if(g->alliance[i].guild_id && g->alliance[i].opposition==0)
				intif_guild_message(g->alliance[i].guild_id,sd->status.account_id,mes,len);
		}
	}

	return;
}

/*==========================================
 * ギルド会話受信
 *------------------------------------------
 */
void guild_recv_message(int guild_id, int account_id, const char *mes, size_t len)
{
	struct guild *g = guild_search(guild_id);

	if(g)
		clif_guild_message(g,mes,len);

	return;
}

/*==========================================
 * ギルドメンバの役職変更
 *------------------------------------------
 */
void guild_change_memberposition(int guild_id, int account_id, int char_id, int idx)
{
	if(idx < 0 || idx >= MAX_GUILDPOSITION)
		return;

	intif_guild_change_memberinfo(guild_id, account_id, char_id, GMI_POSITION, &idx, sizeof(idx));

	return;
}

/*==========================================
 * ギルドメンバの役職変更通知
 *------------------------------------------
 */
void guild_memberposition_changed(struct guild *g, int idx, int pos)
{
	nullpo_retv(g);

	g->member[idx].position=pos;
	clif_guild_memberpositionchanged(g,idx);

	return;
}

/*==========================================
 * ギルド役職変更
 *------------------------------------------
 */
void guild_change_position(int guild_id, int idx, int mode, int exp_mode, const char *name)
{
	struct guild_position p;

	if (idx < 0 || idx >= MAX_GUILDPOSITION)
		return;

	memset(&p, 0, sizeof(struct guild_position));

	strncpy(p.name, name, 24);
	p.name[23] = '\0';	// force \0 terminal
	p.mode = mode;
	if (exp_mode < 0)
		p.exp_mode = 0;
	else if (exp_mode > battle_config.guild_exp_limit)
		p.exp_mode = battle_config.guild_exp_limit;
	else
		p.exp_mode = exp_mode;

	intif_guild_position(guild_id, idx, &p);

	return;
}

/*==========================================
 * ギルド役職変更通知
 *------------------------------------------
 */
void guild_position_changed(int guild_id, int idx, struct guild_position *p)
{
	struct guild *g = guild_search(guild_id);

	if(g == NULL)
		return;
	if(idx < 0 || idx >= MAX_GUILDPOSITION)
		return;

	memcpy(&g->position[idx],p,sizeof(struct guild_position));
	clif_guild_positionchanged(g,idx);

	return;
}

/*==========================================
 * ギルド告知変更
 *------------------------------------------
 */
void guild_change_notice(int guild_id, const char *mes1, const char *mes2)
{
	intif_guild_notice(guild_id, mes1, mes2);

	return;
}

/*==========================================
 * ギルド告知変更通知
 *------------------------------------------
 */
void guild_notice_changed(int guild_id, const char *mes1, const char *mes2)
{
	int i;
	struct map_session_data *sd;
	struct guild *g=guild_search(guild_id);

	if(g==NULL)
		return;

	memcpy(g->mes1,mes1,60);
	memcpy(g->mes2,mes2,120);
	g->mes1[59]  = '\0';
	g->mes2[119] = '\0';

	for(i=0;i<g->max_member;i++){
		if((sd=g->member[i].sd)!=NULL)
			clif_guild_notice(sd,g);
	}

	return;
}

/*==========================================
 * ギルドエンブレム変更
 *------------------------------------------
 */
void guild_change_emblem(int guild_id, unsigned int zipbitmap_len, const char *data)
{
	char dest_bitmap[4100]; // max possible (16/24 bits): 4086 (windows)-> (header1)14 + (header2)40 + (576 colors)2304 + (bitmap:24x24)1728 (no compression with palette)
	unsigned long dest_bitmap_len;
	unsigned int ncol;

	// length of zipbitmap (client doesn't send bmp structure, but a zipped BMP)
	if (zipbitmap_len > 2000)
		return;

	// analyse of bmp
	dest_bitmap_len = sizeof(dest_bitmap);
	if (decode_zip(dest_bitmap, &dest_bitmap_len, data, zipbitmap_len) != 0) { // Z_OK = 0
		return;
	}
	if (dest_bitmap_len < 14 + 40) { // strict minimum -> windows: header1(14) header2(40), os/2 v1 header1(14) header2(12) 256colors(768)
		return;
	}

	/*Structure BITMAPFILEHEADER (14 bytes)
	bfType       Word  (2 bytes)  0 Magic identifier (should be 'BM'=0x4D 0x4E)
	bfSize       Dword (4 bytes)  2 File size in bytes
	bfReserved1  Word  (2 bytes)  6 always 0
	bfReserved2  Word  (2 bytes)  8 always 0
	bfOffBits    Dword (4 bytes) 10 Offset to image data, bytes*/
	if(strncmp(dest_bitmap, "BM", 2) != 0 ||
	   RBUFL(dest_bitmap, 2) != dest_bitmap_len ||
	   RBUFW(dest_bitmap, 6) != 0 ||
	   RBUFW(dest_bitmap, 8) != 0) {
		// check of Offset is done with colors.
		return;
	}

	// Structure BITMAPINFOHEADER (40 bytes: Windows 3.1x, 95, NT, ..., 12 bytes: OS/2 1.x, 64 bytes: OS/2 2.x, ?? bytes: OS/2 3.x)
	switch(RBUFL(dest_bitmap, 14)) {
	case 40: // windows version
		/*biSize           DWord (4 bytes) 14 Header size in bytes (must be: 40)
			biWidth          Dword (4 bytes) 18 Width of image
			biHeight         Dword (4 bytes) 22 Height of image
			biPlanes         Word  (2 bytes) 26 Number of colour planes (always 1)
			biBitCount       Word  (2 bytes) 28 Bits per pixel (1, 4, 8, 16, 24 or 32)
			biCompression    Dword (4 bytes) 30 Compression type (0 - no compression, 1 - 8 bit run length encoding, 2 - 4 bit run length encoding, 3 - RGB bitmap with mask)
			biSizeImage      Dword (4 bytes) 34 Image size in bytes (usefull for compression)
			biXpelsPerMeter  Dword (4 bytes) 38 Pixels per meter
			biYpelsPerMeter  Dword (4 bytes) 42 Pixels per meter
			biClrUsed        Dword (4 bytes) 46 Number of used colours (number of colors in palette)
			biClrImportant   Dword (4 bytes) 50 Number of important colours (0: all)*/
		if (RBUFL(dest_bitmap, 18) != 24 || // ragnarok condition
		    RBUFL(dest_bitmap, 22) != 24 || // ragnarok condition
		    RBUFW(dest_bitmap, 26) != 1 ||
		    // number of colors is checked after
		    (RBUFL(dest_bitmap, 30) != 0 && RBUFL(dest_bitmap, 30) != 1 && RBUFL(dest_bitmap, 30) != 2 && RBUFL(dest_bitmap, 30) != 3)) {
			return;
		}
		/* color structure (8 bits, always exist)
		Windows RGBQUAD color map entry
		0       rgbBlue     (1 bytes)  Blue value for color map entry.
		1       rgbGreen    (1 bytes)  Green value for color map entry.
		2       rgbRed      (1 bytes)  Red value for color map entry.
		3       rgbReserved (1 bytes)  Zero*/
		if (RBUFL(dest_bitmap, 28) == 8) { // 256 colors (ragnarok condition)
			ncol = (RBUFL(dest_bitmap, 10) - 54) / 4; // compute number of colors recorded
			// check offset of bitmap and number of colors
			if (ncol > 256 || // 8 bits colored bitmap, used colors must be at maximum 256
			    (RBUFL(dest_bitmap, 46) == 0 && ncol != 256) || // biClrUsed not used
			    (RBUFL(dest_bitmap, 46) != 0 && ncol != RBUFL(dest_bitmap, 46))) { // biClrUsed used
				return;
			}
			// check size of file (when no compression)
			if (RBUFL(dest_bitmap, 10) < 14 + 40 + ncol * 4 || // check minimum position of bitmap data
			    (RBUFL(dest_bitmap, 30) == 0 && (dest_bitmap_len < 14 + 40 + ncol * 4 + 576 || // no compression (check minimum)
			                                     dest_bitmap_len - RBUFL(dest_bitmap, 10) < 576)) ||
			    (RBUFL(dest_bitmap, 30) != 0 && dest_bitmap_len <= 14 + 40 + ncol * 4)) { // with compression (check minimum)
				return;
			}
		// 16-24 bits colors (Additional ragnarok conditions)
		} else if (((battle_config.guild_emblem_colors & 1) == 1 && RBUFL(dest_bitmap, 28) == 16) ||
		           ((battle_config.guild_emblem_colors & 2) == 2 && RBUFL(dest_bitmap, 28) == 24)) {
			ncol = RBUFL(dest_bitmap, 46); // compute number of colors recorded (could be 0 if not important colors)
			// check offset of bitmap and number of colors
			if (ncol > 576) { // can not have more colors than number of used pixels
				return;
			}
			// check size of file (when no compression)
			if (RBUFL(dest_bitmap, 10) < 14 + 40 + ncol * 4 || // check minimum position of bitmap data
			    (RBUFL(dest_bitmap, 30) == 0 && (dest_bitmap_len < 14 + 40 + ncol * 4 + 576 * 3 || // no compression (check minimum)
			                                     dest_bitmap_len - RBUFL(dest_bitmap, 10) < 576 * 3)) ||
			    (RBUFL(dest_bitmap, 30) != 0 && dest_bitmap_len <= 14 + 40 + ncol * 4)) { // with compression (check minimum)
				return;
			}
		} else {	// non supported number of colors
			return;
		}
		break;

	case 12: // os/2 v1.x version
		/*biSize           DWord (4 bytes) 14 Header size in bytes (must be: 12)
			biWidth          Word  (2 bytes) 18 Width of image
			biHeight         Word  (2 bytes) 20 Height of image
			biPlanes         Word  (2 bytes) 22 Number of colour planes (always 1)
			biBitCount       Word  (2 bytes) 24 Bits per pixel (1, 4, 8, 24) -> color palette size: 2, 16, 256, 0
			no compression*/
		if (RBUFW(dest_bitmap, 18) != 24 || // ragnarok condition
		    RBUFW(dest_bitmap, 20) != 24 || // ragnarok condition
		    RBUFW(dest_bitmap, 22) != 1
		    // number of colors is checked after
		    ) {
			return;
		}
		/* color structure (8 bits, always exist)
		OS/2 RGBTRIPLE color map entry
		0       rgbtBlue  (1 bytes)  Blue value for color map entry.
		1       rgbtGreen (1 bytes)  Green value for color map entry.
		2       rgbtRed   (1 bytes)  Red value for color map entry.*/
		if (RBUFW(dest_bitmap, 24) == 8) { // 256 colors (ragnarok condition)
			ncol = (RBUFL(dest_bitmap, 10) - 26) / 3; // compute number of colors recorded
			// check offset of bitmap
			if (ncol != 256) { // bmp start after the 2 headers and color structure
				return;
			}
			// check size of file
			if (dest_bitmap_len != 14 + 12 + ncol * 3 + 576) {
				return;
			}
		// 24 bits colors (Additional ragnarok condition)
		} else if ((battle_config.guild_emblem_colors & 2) == 2 && RBUFW(dest_bitmap, 24) == 24) {
			// check size of file
			if (dest_bitmap_len != 14 + 12 + 1728) { // bmp start after the 2 headers
				return;
			}
		} else {	// non supported number of colors
			return;
		}
		break;

	default: // other -> not supported
		/* note: Ragnarok run under windows, client don't support OS/2 1.x, 2.x or 3.x versions. OS/2 1.x version is here for example */
		return;
	}

	intif_guild_emblem(guild_id, (unsigned short)zipbitmap_len, data);

	return;
}

/*==========================================
 * ギルドエンブレム変更通知
 *------------------------------------------
 */
void guild_emblem_changed(int len, int guild_id, int emblem_id, const char *data)
{
	int i;
	struct map_session_data *sd;
	struct guild *g=guild_search(guild_id);

	if(g==NULL)
		return;

	memcpy(g->emblem_data,data,len);
	g->emblem_len=len;
	g->emblem_id=emblem_id;

	for(i=0;i<g->max_member;i++){
		if((sd=g->member[i].sd)!=NULL){
			sd->guild_emblem_id=emblem_id;
			clif_guild_belonginfo(sd,g);
			clif_guild_emblem(sd,g);
		}
	}

	return;
}

/*==========================================
 * スキルポイント割り振り
 *------------------------------------------
 */
void guild_skillup(struct map_session_data *sd, int skill_num, int level, int flag)
{
	struct guild *g;
	int idx;

	nullpo_retv(sd);

	if(sd->status.guild_id==0 || (g=guild_search(sd->status.guild_id))==NULL)
		return;
	if(strcmp(sd->status.name,g->master))
		return;

	idx = skill_num - GUILD_SKILLID;
	if(idx < 0 || idx >= MAX_GUILDSKILL)
		return;

	if(g->skill[idx].id <= 0)
		return;

	if( level < 0 || ((g->skill_point > 0 || flag&1) && g->skill[idx].lv < guild_skill_max[idx]) ) {
		// 情報更新
		// スキルツリーのチェックはint_guild.cで行う
		intif_guild_skillup(g->guild_id, skill_num, sd->status.account_id, level, flag);
	}

	return;
}

/*==========================================
 * スキルポイント割り振り通知
 *------------------------------------------
 */
void guild_skillupack(int guild_id, int skill_num, int account_id, int flag)
{
	struct map_session_data *sd=map_id2sd(account_id);
	struct guild *g=guild_search(guild_id);

	if(g==NULL)
		return;

	if(sd!=NULL)
		clif_guild_skillup(sd,skill_num,g->skill[skill_num-GUILD_SKILLID].lv,flag);

	if(flag) {
		int i;

		// 全員に通知
		for(i=0;i<g->max_member;i++) {
			if((sd=g->member[i].sd)!=NULL)
				clif_guild_skillinfo(sd, g);
		}
	}

	return;
}

/*==========================================
 * ギルド同盟数取得
 *------------------------------------------
 */
static int guild_get_alliance_count(struct guild *g,int flag)
{
	int i,c;

	nullpo_retr(0, g);

	for(i=c=0;i<MAX_GUILDALLIANCE;i++){
		if( g->alliance[i].guild_id>0 && g->alliance[i].opposition==flag )
			c++;
	}

	return c;
}

/*==========================================
 * 同盟関係かどうかチェック
 * 同盟なら1、それ以外は0
 *------------------------------------------
 */
int guild_check_alliance(int guild_id1, int guild_id2, int flag)
{
	struct guild *g;
	int i;

	g = guild_search(guild_id1);
	if (g == NULL)
		return 0;

	for (i=0; i<MAX_GUILDALLIANCE; i++)
	{
		if (g->alliance[i].guild_id == guild_id2 && g->alliance[i].opposition == flag)
			return 1;
	}

	return 0;
}

/*==========================================
 * ギルド同盟要求
 *------------------------------------------
 */
void guild_reqalliance(struct map_session_data *sd, int account_id)
{
	struct map_session_data *tsd;
	struct guild *g[2];
	int i;

	nullpo_retv(sd);

	tsd = map_id2sd(account_id);
	if(tsd == NULL || tsd->status.guild_id <= 0)
		return;

	// 同じギルドにはできない
	if(sd->status.guild_id == tsd->status.guild_id)
		return;

	// player must be on same map... (how to use mouse menu otherwise?)
	if (sd->bl.m != tsd->bl.m)
		return;
	// and in visible area of member
	if (path_distance(sd->bl.x,sd->bl.y,tsd->bl.x,tsd->bl.y) > AREA_SIZE)
		return;

	// 攻城戦中では同盟できない
	if (!battle_config.allow_guild_alliance_in_agit) {
		if (agit_flag)
			return;
	}

	g[0] = guild_search(sd->status.guild_id);
	g[1] = guild_search(tsd->status.guild_id);

	if(g[0] == NULL || g[1] == NULL)
		return;

	if(strcmp(sd->status.name, g[0]->master))	// マスターかどうか確認
		return;

	if(guild_get_alliance_count(g[0],0) > 3)	// 同盟数確認
		clif_guild_allianceack(sd,4);
	if(guild_get_alliance_count(g[1],0) > 3)
		clif_guild_allianceack(sd,3);

	if(tsd->guild_alliance > 0) {	// 相手が同盟要請状態かどうか確認
		clif_guild_allianceack(sd,1);
		return;
	}

	for(i=0; i<MAX_GUILDALLIANCE; i++) {	// すでに同盟状態か確認
		if(g[0]->alliance[i].guild_id == tsd->status.guild_id && g[0]->alliance[i].opposition == 0) {
			clif_guild_allianceack(sd,0);
			return;
		}
	}

	tsd->guild_alliance         = sd->status.guild_id;
	tsd->guild_alliance_account = sd->status.account_id;

	clif_guild_reqalliance(tsd,sd->status.account_id,g[0]->name);

	return;
}

/*==========================================
 * ギルド同盟勧誘への返答
 *------------------------------------------
 */
void guild_reply_reqalliance(struct map_session_data *sd, int account_id, int flag)
{
	struct map_session_data *tsd;

	nullpo_retv(sd);

	if((tsd = map_id2sd(account_id)) == NULL)
		return;
	if(sd->guild_alliance != tsd->status.guild_id)	// 勧誘とギルドIDが違う
		return;

	if(flag == 1) {
		// 承諾
		int i;
		struct guild *g;

		// 同盟数再確認
		if((g = guild_search(sd->status.guild_id)) == NULL || guild_get_alliance_count(g,0) > 3) {
			clif_guild_allianceack(sd,4);
			clif_guild_allianceack(tsd,3);
			return;
		}
		if((g = guild_search(tsd->status.guild_id)) == NULL || guild_get_alliance_count(g,0) > 3) {
			clif_guild_allianceack(sd,3);
			clif_guild_allianceack(tsd,4);
			return;
		}

		// 敵対関係なら敵対を止める
		if((g = guild_search(sd->status.guild_id)) == NULL)
			return;
		for(i=0; i<MAX_GUILDALLIANCE; i++) {
			if(g->alliance[i].guild_id == tsd->status.guild_id && g->alliance[i].opposition == 1) {
				intif_guild_alliance( sd->status.guild_id,tsd->status.guild_id,
					sd->status.account_id,tsd->status.account_id,9 );
			}
		}
		if((g = guild_search(tsd->status.guild_id)) == NULL)
			return;
		for(i=0; i<MAX_GUILDALLIANCE; i++) {
			if(g->alliance[i].guild_id == sd->status.guild_id && g->alliance[i].opposition == 1) {
				intif_guild_alliance( tsd->status.guild_id,sd->status.guild_id,
					tsd->status.account_id,sd->status.account_id,9 );
			}
		}

		// inter鯖へ同盟要請
		intif_guild_alliance( sd->status.guild_id,tsd->status.guild_id,
			sd->status.account_id,tsd->status.account_id,0 );
	} else {
		// 拒否
		sd->guild_alliance         = 0;
		sd->guild_alliance_account = 0;
		if(tsd)
			clif_guild_allianceack(tsd,3);
	}

	return;
}

/*==========================================
 * ギルド関係解消
 *------------------------------------------
 */
void guild_delalliance(struct map_session_data *sd, int guild_id, int flag)
{
	nullpo_retv(sd);

	// 攻城戦中では解消できない
	if(!battle_config.allow_guild_alliance_in_agit) {
		if(agit_flag)
			return;
	}

	intif_guild_alliance(sd->status.guild_id,guild_id,sd->status.account_id,0,flag|8);

	return;
}

/*==========================================
 * ギルド敵対
 *------------------------------------------
 */
void guild_opposition(struct map_session_data *sd, int account_id)
{
	struct map_session_data *tsd;
	struct guild *g;
	int i;

	nullpo_retv(sd);

	tsd = map_id2sd(account_id);
	if(tsd == NULL || tsd->status.guild_id <= 0)
		return;

	// 同じギルドにはできない
	if(sd->status.guild_id == tsd->status.guild_id)
		return;

	if(sd->bl.m != tsd->bl.m)
		return;
	if(path_distance(sd->bl.x,sd->bl.y,tsd->bl.x,tsd->bl.y) > AREA_SIZE)
		return;

	// 攻城戦中では敵対できない
	if(!battle_config.allow_guild_alliance_in_agit) {
		if(agit_flag)
			return;
	}

	if((g = guild_search(sd->status.guild_id)) == NULL)
		return;
	if(strcmp(sd->status.name, g->master))	// マスターかどうか確認
		return;

	if(guild_get_alliance_count(g,1) > 3)	// 敵対数確認
		clif_guild_oppositionack(sd,1);

	for(i=0; i<MAX_GUILDALLIANCE; i++) {	// すでに関係を持っているか確認
		if(g->alliance[i].guild_id == tsd->status.guild_id) {
			if(g->alliance[i].opposition == 1) {	// すでに敵対
				clif_guild_oppositionack(sd,2);
				return;
			}
			// 同盟破棄
			intif_guild_alliance( sd->status.guild_id,tsd->status.guild_id,
				sd->status.account_id,tsd->status.account_id,8 );
		}
	}

	// inter鯖に敵対要請
	intif_guild_alliance( sd->status.guild_id,tsd->status.guild_id,
			sd->status.account_id,tsd->status.account_id,1 );

	return;
}

/*==========================================
 * ギルド同盟/敵対通知
 *------------------------------------------
 */
void guild_allianceack(int guild_id1, int guild_id2, int account_id1, int account_id2,
	unsigned char flag, const char *name1, const char *name2)
{
	struct guild *g[2];
	int guild_id[2];
	const char *guild_name[2];
	struct map_session_data *sd[2];
	int j,i;

	guild_id[0]   = guild_id1;
	guild_id[1]   = guild_id2;
	guild_name[0] = name1;
	guild_name[1] = name2;
	sd[0]         = map_id2sd(account_id1);
	sd[1]         = map_id2sd(account_id2);

	g[0] = guild_search(guild_id1);
	g[1] = guild_search(guild_id2);

	if(sd[0]!=NULL && (flag&0x0f)==0){
		sd[0]->guild_alliance=0;
		sd[0]->guild_alliance_account=0;
	}

	if(flag&0x70){	// 失敗
		for(i=0;i<2-(flag&1);i++)
			if( sd[i]!=NULL )
				clif_guild_allianceack(sd[i],((flag>>4)==i+1)?3:4);
		return;
	}

	if(!(flag&0x08)) {	// 関係追加
		for(i=0;i<2-(flag&1);i++) {
			if(g[i]!=NULL) {
				for(j=0;j<MAX_GUILDALLIANCE;j++) {
					if(g[i]->alliance[j].guild_id==0){
						g[i]->alliance[j].guild_id=guild_id[1-i];
						memcpy(g[i]->alliance[j].name,guild_name[1-i],24);
						g[i]->alliance[j].opposition=flag&1;
						break;
					}
				}
			}
		}
	} else {		// 関係解消
		for(i=0;i<2-(flag&1);i++) {
			if(g[i]!=NULL) {
				for(j=0;j<MAX_GUILDALLIANCE;j++) {
					if(g[i]->alliance[j].guild_id==guild_id[1-i] &&
					   g[i]->alliance[j].opposition==(flag&1)){
						g[i]->alliance[j].guild_id=0;
						break;
					}
				}
			}
			if( sd[i]!=NULL )	// 解消通知
				clif_guild_delalliance(sd[i],guild_id[1-i],(flag&1));
		}
	}

	if((flag&0x0f)==0){			// 同盟通知
		if( sd[1]!=NULL )
			clif_guild_allianceack(sd[1],2);
	}else if((flag&0x0f)==1){	// 敵対通知
		if( sd[0]!=NULL )
			clif_guild_oppositionack(sd[0],0);
	}


	for(i=0;i<2-(flag&1);i++) {	// 同盟/敵対リストの再送信
		struct map_session_data *tmpsd;
		if(g[i]!=NULL) {
			for(j=0;j<g[i]->max_member;j++) {
				if((tmpsd=g[i]->member[j].sd)!=NULL)
					clif_guild_allianceinfo(tmpsd, g[i]);
			}
		}
	}

	return;
}

/*==========================================
 * ギルド解散通知
 *------------------------------------------
 */
static int guild_broken_sub(void *key,void *data,va_list ap)
{
	struct guild *g=(struct guild *)data;
	int guild_id=va_arg(ap,int);
	int i,j;
	struct map_session_data *sd=NULL;

	nullpo_retr(0,g);

	for(i=0;i<MAX_GUILDALLIANCE;i++){	// 関係を破棄
		if(g->alliance[i].guild_id==guild_id){
			for(j=0;j<g->max_member;j++) {
				if( (sd=g->member[j].sd)!=NULL )
					clif_guild_delalliance(sd,guild_id,g->alliance[i].opposition);
			}
			g->alliance[i].guild_id=0;
		}
	}

	return 0;
}

void guild_broken(int guild_id, unsigned char flag)
{
	struct guild *g;
	struct guild_castle *gc;
	struct map_session_data *sd;
	int i;

	if(flag != 0)
		return;
	if((g = guild_search(guild_id)) == NULL)
		return;

	// 所有砦の破棄
	for(i=0; i<MAX_GUILDCASTLE; i++) {
		if((gc = guild_castle_search(i)) != NULL) {
			if(gc->guild_id == guild_id) {
				char name[50];
				memcpy(name,gc->castle_event,24);
				npc_event_do(strcat(name,"::OnGuildBreak"));
			}
		}
	}

	for(i=0; i<g->max_member; i++) {	// ギルド解散を通知
		if((sd = g->member[i].sd) != NULL) {
			if(sd->state.storage_flag == 2) {
				// ギルド倉庫を開いているなら閉じる
				sd->state.storage_flag = 0;
				clif_storageclose(sd);
			}
			sd->status.guild_id    = 0;
			sd->state.guild_sended = 0;
			clif_guild_broken(g->member[i].sd,0);
		}
	}

	numdb_foreach(guild_db,guild_broken_sub,guild_id);
	numdb_erase(guild_db,guild_id);
	storage_guild_delete(guild_id);
	aFree(g);

	return;
}

/*==========================================
 * ギルド解散
 *------------------------------------------
 */
void guild_break(struct map_session_data *sd, const char *name)
{
	struct guild *g;
	int i;

	nullpo_retv(sd);

	if( (g=guild_search(sd->status.guild_id))==NULL )
		return;
	if(strcmp(g->name,name)!=0)
		return;
	if(strcmp(sd->status.name,g->master)!=0)
		return;
	for(i=0;i<g->max_member;i++){
		if( g->member[i].account_id>0 ) {
			if( g->member[i].account_id!=sd->status.account_id ||
			    g->member[i].char_id!=sd->status.char_id )
				break;
		}
	}
	if(i<g->max_member){
		clif_guild_broken(sd,2);
		return;
	}

	intif_guild_break(g->guild_id);

	return;
}

/*==========================================
 * ギルド城データ要求
 *------------------------------------------
 */
void guild_castledataload(int castle_id, int idx)
{
	intif_guild_castle_dataload(castle_id, idx);

	return;
}

/*==========================================
 * ギルド城情報取得時イベント追加
 *------------------------------------------
 */
void guild_addcastleinfoevent(int castle_id, int idx, const char *name)
{
	struct eventlist *ev;
	int code;

	if( name==NULL || *name==0 )
		return;

	code = castle_id | (idx << 16);
	ev = (struct eventlist *)aCalloc(1,sizeof(struct eventlist));
	memcpy(ev->name,name,sizeof(ev->name));
	ev->name[sizeof(ev->name)-1] = '\0';	// force \0 terminal
	ev->next = (struct eventlist *)numdb_insert(guild_castleinfoevent_db,code,ev);

	return;
}

/*==========================================
 * ギルド城データ要求返信
 *------------------------------------------
 */
void guild_castledataloadack(int castle_id, int idx, int value)
{
	struct guild_castle *gc=guild_castle_search(castle_id);
	int code;
	struct eventlist *ev,*ev2;

	if(gc==NULL){
		return;
	}
	code = castle_id | (idx << 16);
	switch(idx) {
		case  1: gc->guild_id            = value; break;
		case  2: gc->economy             = value; break;
		case  3: gc->defense             = value; break;
		case  4: gc->triggerE            = value; break;
		case  5: gc->triggerD            = value; break;
		case  6: gc->nextTime            = value; break;
		case  7: gc->payTime             = value; break;
		case  8: gc->createTime          = value; break;
		case  9: gc->visibleC            = value; break;
		case 10: gc->guardian[0].visible = value; break;
		case 11: gc->guardian[1].visible = value; break;
		case 12: gc->guardian[2].visible = value; break;
		case 13: gc->guardian[3].visible = value; break;
		case 14: gc->guardian[4].visible = value; break;
		case 15: gc->guardian[5].visible = value; break;
		case 16: gc->guardian[6].visible = value; break;
		case 17: gc->guardian[7].visible = value; break;
		default:
			printf("guild_castledataloadack ERROR!! (Not found index=%d)\n", idx);
			return;
	}
	if( (ev = (struct eventlist *)numdb_search(guild_castleinfoevent_db,code)) != NULL ){
		numdb_erase(guild_castleinfoevent_db,code);
		while(ev){
			npc_event_do(ev->name);
			ev2=ev->next;
			aFree(ev);
			ev=ev2;
		}
	}

	return;
}

/*==========================================
 * ギルド城データ変更要求
 *------------------------------------------
 */
void guild_castledatasave(int castle_id, int idx, int value)
{
	intif_guild_castle_datasave(castle_id, idx, value);

	return;
}

/*==========================================
 * ギルド城データ変更通知
 *------------------------------------------
 */
void guild_castledatasaveack(int castle_id, int idx, int value)
{
	struct guild_castle *gc=guild_castle_search(castle_id);

	if(gc==NULL){
		return;
	}
	switch(idx) {
		case  1: gc->guild_id            = value; break;
		case  2: gc->economy             = value; break;
		case  3: gc->defense             = value; break;
		case  4: gc->triggerE            = value; break;
		case  5: gc->triggerD            = value; break;
		case  6: gc->nextTime            = value; break;
		case  7: gc->payTime             = value; break;
		case  8: gc->createTime          = value; break;
		case  9: gc->visibleC            = value; break;
		case 10: gc->guardian[0].visible = value; break;
		case 11: gc->guardian[1].visible = value; break;
		case 12: gc->guardian[2].visible = value; break;
		case 13: gc->guardian[3].visible = value; break;
		case 14: gc->guardian[4].visible = value; break;
		case 15: gc->guardian[5].visible = value; break;
		case 16: gc->guardian[6].visible = value; break;
		case 17: gc->guardian[7].visible = value; break;
		default:
			printf("guild_castledatasaveack ERROR!! (Not found index=%d)\n", idx);
			return;
	}

	return;
}

/*==========================================
 * ギルドデータ一括受信（初期化時）
 *------------------------------------------
 */
void guild_castlealldataload(int len, struct guild_castle *gc)
{
	int i, ev = -1;
	int n = (len - 4) / sizeof(struct guild_castle);

	nullpo_retv(gc);

	// イベント付きで要求するデータ位置を探す(最後の占拠データ)
	for(i = n - 1; i >= 0; i--) {
		if( (gc+i)->guild_id ) {
			ev = i;
			break;
		}
	}

	// 城データ格納とギルド情報要求
	for(i = 0; i < n; i++, gc++) {
		struct guild_castle *c = guild_castle_search(gc->castle_id);
		if(!c) {
			printf("guild_castlealldataload ??\n");
			continue;
		}

		c->guild_id   = gc->guild_id;
		c->economy    = gc->economy;
		c->defense    = gc->defense;
		c->triggerE   = gc->triggerE;
		c->triggerD   = gc->triggerD;
		c->nextTime   = gc->nextTime;
		c->payTime    = gc->payTime;
		c->createTime = gc->createTime;
		c->visibleC   = gc->visibleC;
		memcpy(c->guardian, gc->guardian, sizeof(c->guardian));

		if(c->guild_id) {
			if(i != ev)
				guild_request_info(c->guild_id);
			else
				guild_npc_request_info(c->guild_id, "::OnAgitInit");
		}
	}
	if(ev < 0)
		npc_event_doall("OnAgitInit");

	return;
}

/*==========================================
 * シーズ開始（OnAgitStart）
 *------------------------------------------
 */
void guild_agit_start(void)
{
	int c = npc_event_doall("OnAgitStart");

	printf("NPC_Event:[OnAgitStart] Run (%d) Events by @AgitStart.\n",c);
	if(battle_config.allow_guild_skill_in_gvgtime_only)
		battle_config.guild_skill_available = 1;

	return;
}

/*==========================================
 * シーズ終了（OnAgitEnd）
 *------------------------------------------
 */
void guild_agit_end(void)
{
	int c = npc_event_doall("OnAgitEnd");

	printf("NPC_Event:[OnAgitEnd] Run (%d) Events by @AgitEnd.\n",c);
	if(battle_config.allow_guild_skill_in_gvgtime_only)
		battle_config.guild_skill_available = 0;

	return;
}

/*==========================================
 * 排除タイマー（OnAgitEliminate）
 *------------------------------------------
 */
static int guild_gvg_eliminate_timer(int tid,unsigned int tick,int id,void *data)
{
	char *evname = (char *)data;

	if(evname) {
		if(agit_flag) {
			int c = npc_event_do(evname);
			printf("NPC_Event:[%s] Run (%d) Events.\n",evname,c);
		}
		aFree(evname);
	}

	return 0;
}

/*==========================================
 * エンペ破壊（OnAgitBreak）
 *------------------------------------------
 */
void guild_agit_break(struct mob_data *md)
{
	size_t len;
	char *evname;
	unsigned int tick = gettick();

	nullpo_retv(md);

	if(!agit_flag)	// Agit already End
		return;

	len = strlen(md->npc_event);
	evname = (char *)aCalloc(len + 5, sizeof(char));
	memcpy(evname, md->npc_event, len - 5);
	strcat(evname, "Eliminate");

	add_timer2(tick+battle_config.gvg_eliminate_time,guild_gvg_eliminate_timer,md->bl.m,evname);

	return;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
static int guild_db_final(void *key,void *data,va_list ap)
{
	struct guild *g = (struct guild *)data;

	aFree(g);

	return 0;
}

static int guild_expcache_db_final(void *key,void *data,va_list ap)
{
	struct guild_expcache *c = (struct guild_expcache *)data;

	aFree(c);

	return 0;
}

static int guild_infoevent_db_final(void *key,void *data,va_list ap)
{
	struct eventlist *ev = (struct eventlist *)data;

	aFree(ev);

	return 0;
}

void do_final_guild(void)
{
	if(guild_db)
		numdb_final(guild_db,guild_db_final);
	if(guild_expcache_db)
		numdb_final(guild_expcache_db,guild_expcache_db_final);
	if(guild_infoevent_db)
		numdb_final(guild_infoevent_db,guild_infoevent_db_final);
	if(guild_castleinfoevent_db)
		numdb_final(guild_castleinfoevent_db,guild_infoevent_db_final);

	return;
}

/*==========================================
 * ギルド城データベース読み込み
 *------------------------------------------
 */
static void guild_read_castledb(void)
{
	FILE *fp;
	char line[1024];
	int j,ln=0;
	char *str[5],*p;
	const char *filename = "db/castle_db.txt";

	// デフォルトデータを作成
	memset(castle_db,0,sizeof(castle_db));
	for(j=0; j<MAX_GUILDCASTLE; j++) {
		castle_db[j].castle_id = j;
		castle_db[j].m         = -1;
	}

	if ((fp = fopen(filename, "r")) == NULL) {
		printf("guild_read_castledb: open [%s] failed !\n", filename);
		return;
	}

	while(fgets(line,1020,fp)){
		int id;
		size_t max;

		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0] == '/' && line[1] == '/')
			continue;
		max = strlen(line) - 1;
		if(line[max] == '\n')
			line[max] = 0;

		memset(str,0,sizeof(str));
		for(j=0,p=line;j<5 && p;j++){
			str[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		id = atoi(str[0]);
		if(id < 0 || id >= MAX_GUILDCASTLE)
			continue;

		memcpy(castle_db[id].map_name,str[1],24);
		memcpy(castle_db[id].area_name,str[2],24);
		memcpy(castle_db[id].castle_name,str[3],32);
		memcpy(castle_db[id].castle_event,str[4],24);

		// force \0 terminal
		castle_db[id].map_name[23]     = '\0';
		castle_db[id].area_name[23]    = '\0';
		castle_db[id].castle_name[31]  = '\0';
		castle_db[id].castle_event[23] = '\0';

		castle_db[id].m = map_mapname2mapid(castle_db[id].map_name);
		ln++;
	}
	fclose(fp);
	printf("read %s done (count=%d)\n", filename, ln);

	return;
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
void do_init_guild(void)
{
	unsigned int tick = gettick();

	guild_db = numdb_init();
	guild_expcache_db = numdb_init();
	guild_infoevent_db = numdb_init();
	guild_castleinfoevent_db = numdb_init();

	guild_read_castledb();

	add_timer_func_list(guild_gvg_eliminate_timer);
	add_timer_func_list(guild_payexp_timer);
	add_timer_func_list(guild_send_xy_timer);
	add_timer_interval(tick+GUILD_PAYEXP_INVERVAL,guild_payexp_timer,0,NULL,GUILD_PAYEXP_INVERVAL);
	add_timer_interval(tick+GUILD_SEND_XY_INVERVAL,guild_send_xy_timer,0,NULL,GUILD_SEND_XY_INVERVAL);

	return;
}
