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
#include "party.h"
#include "guild.h"
#include "npc.h"
#include "intif.h"
#include "storage.h"
#include "battle.h"
#include "status.h"
#include "unit.h"
#include "skill.h"

/* Split from script.c (Issue #61) */

/*==========================================
 * キャラ関係のID取得
 *------------------------------------------
 */
int buildin_getcharid(struct script_state *st)
{
	int num, id = -1;
	struct map_session_data *sd;

	num = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if(st->end > st->start+3)
		sd = map_nick2sd(conv_str(st,& (st->stack->stack_data[st->start+3])));
	else
		sd = script_rid2sd(st);

	if(sd) {
		switch(num) {
			case 0: id = sd->status.char_id;    break;
			case 1: id = sd->status.party_id;   break;
			case 2: id = sd->status.guild_id;   break;
			case 3: id = sd->status.account_id; break;
		}
	}
	push_val(st->stack,C_INT,id);

	return 0;
}


/*==========================================
 * 指定IDのPT名取得
 *------------------------------------------
 */
static char *buildin_getpartyname_sub(int party_id)
{
	struct party *p = party_search(party_id);

	if(p!=NULL){
		return (char *)aStrdup(p->name);
	}
	return NULL;
}

int buildin_getpartyname(struct script_state *st)
{
	char *name;
	int party_id;

	party_id=conv_num(st,& (st->stack->stack_data[st->start+2]));
	name=buildin_getpartyname_sub(party_id);
	if(name)
		push_str(st->stack,C_STR,name);
	else
		push_str(st->stack,C_CONSTSTR,"");

	return 0;
}

/*==========================================
 * 指定IDのキャラクタ名取得
 *------------------------------------------
 */
static char *buildin_getcharname_sub(int char_id)
{
	struct charid2nick *c = char_search(char_id);

	if(c!=NULL){
		return (char *)aStrdup(c->nick);
	}
	return NULL;
}

int buildin_getcharname(struct script_state *st)
{
	char *name;
	int char_id;

	char_id=conv_num(st,& (st->stack->stack_data[st->start+2]));
	name=buildin_getcharname_sub(char_id);

	if(name)
		push_str(st->stack,C_STR,name);
	else
		push_str(st->stack,C_CONSTSTR,"");

	return 0;
}

/*==========================================
 * 指定IDのPT人数とメンバーID取得
 *------------------------------------------
 */
int buildin_getpartymember(struct script_state *st)
{
	int j = 0;
	struct party *p = NULL;

	p = party_search(conv_num(st,& (st->stack->stack_data[st->start+2])));

	if(p) {
		int i,num;
		num = add_str("$@partymembername$");
		for(i=0; i<MAX_PARTY && j<128; i++) {
			if(p->member[i].account_id) {
				mapreg_setregstr(num+(j<<24),p->member[i].name,0);
				j++;
			}
		}
	}
	mapreg_setreg(add_str("$@partymembercount"),j,0);

	return 0;
}

/*==========================================
 * 指定IDのギルド名取得
 *------------------------------------------
 */
static char *buildin_getguildname_sub(int guild_id)
{
	struct guild *g = guild_search(guild_id);

	if(g!=NULL){
		return (char *)aStrdup(g->name);
	}
	return NULL;
}

int buildin_getguildname(struct script_state *st)
{
	char *name;
	int guild_id=conv_num(st,& (st->stack->stack_data[st->start+2]));

	name=buildin_getguildname_sub(guild_id);
	if(name)
		push_str(st->stack,C_STR,name);
	else
		push_str(st->stack,C_CONSTSTR,"");

	return 0;
}

/*==========================================
 * 指定IDのGuildMaster名取得
 *------------------------------------------
 */
int buildin_getguildmaster(struct script_state *st)
{
	int guild_id = conv_num(st,& (st->stack->stack_data[st->start+2]));

	if(guild_id > 0) {
		struct guild *g = guild_search(guild_id);
		if(g) {
			push_str(st->stack,C_STR,(unsigned char *)aStrdup(g->master));
			return 0;
		}
	}
	push_str(st->stack,C_CONSTSTR,"");
	return 0;
}

int buildin_getguildmasterid(struct script_state *st)
{
	int guild_id = conv_num(st,& (st->stack->stack_data[st->start+2]));

	if(guild_id > 0) {
		struct guild *g = guild_search(guild_id);
		if(g) {
			struct map_session_data *sd = map_nick2sd(g->master);
			if(sd) {
				push_val(st->stack,C_INT,sd->status.char_id);
				return 0;
			}
		}
	}
	push_val(st->stack,C_INT,0);
	return 0;
}

/*==========================================
 * キャラクタの名前
 *------------------------------------------
 */
int buildin_strcharinfo(struct script_state *st)
{
	struct map_session_data *sd;
	int num;

	sd  = script_rid2sd(st);
	num = conv_num(st,& (st->stack->stack_data[st->start+2]));

	if(sd) {
		char *buf;

		switch (num) {
		case 0:
			push_str(st->stack,C_STR,(unsigned char *)aStrdup(sd->status.name));
			return 0;
		case 1:
			buf=buildin_getpartyname_sub(sd->status.party_id);
			if(buf)
				push_str(st->stack,C_STR,buf);
			else
				push_str(st->stack,C_CONSTSTR,"");
			return 0;
		case 2:
			buf=buildin_getguildname_sub(sd->status.guild_id);
			if(buf)
				push_str(st->stack,C_STR,buf);
			else
				push_str(st->stack,C_CONSTSTR,"");
			return 0;
		}
	}
	push_str(st->stack,C_CONSTSTR,"");
	return 0;
}

/*==========================================
 * ギルドスキル取得
 *------------------------------------------
 */
int buildin_guildskill(struct script_state *st)
{
	int id,level,flag=1;
	struct map_session_data *sd = script_rid2sd(st);

	id    = conv_num(st,& (st->stack->stack_data[st->start+2]));
	level = conv_num(st,& (st->stack->stack_data[st->start+3]));
	if(st->end > st->start+4)
		flag = conv_num(st,& (st->stack->stack_data[st->start+4]));

	if(level <= 0)
		level = -1;

	guild_skillup(sd,id,level,flag);

	return 0;
}

/*==========================================
 * ギルド倉庫を開く
 *------------------------------------------
 */
int buildin_guildopenstorage(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);

	if(sd == NULL) {
		st->state = END;
		return 0;
	}

	if(sd->state.menu_or_input == 0) {
		if(sd->status.guild_id <= 0) {	// ギルド未所属
			push_val(st->stack,C_INT,2);
			return 0;
		}
		if(sd->state.gstorage_lockreq != 0) {
			push_val(st->stack,C_INT,3);
			return 0;
		}
		st->state = RERUNLINE;
		sd->state.menu_or_input = 1;
		sd->state.gstorage_lockreq = 1;	// script経由フラグ
		intif_trylock_guild_storage(sd,st->oid);
	} else {
		sd->state.menu_or_input = 0;

		if(sd->npc_menu) {	// ロック取得成功
			if(sd->npc_menu == 2) {
				// キャッシュを削除してリロード
				storage_guild_delete(sd->status.guild_id);
			}
			sd->npc_menu = 0;
			push_val(st->stack,C_INT,storage_guild_storageopen(sd));
		} else {		// ロック取得失敗
			push_val(st->stack,C_INT,1);
		}
	}

	return 0;
}

/*==========================================
 * 攻城戦開始
 *------------------------------------------
 */
int buildin_agitstart(struct script_state *st)
{
	if(!agit_flag) {
		agit_flag = 1;
		guild_agit_start();
	}
	return 0;
}

/*==========================================
 * 攻城戦終了
 *------------------------------------------
 */
int buildin_agitend(struct script_state *st)
{
	if(agit_flag) {
		agit_flag = 0;
		guild_agit_end();
	}
	return 0;
}

/*==========================================
 * 攻城戦中かどうか
 *------------------------------------------
 */
int buildin_agitcheck(struct script_state *st)
{
	push_val(st->stack,C_INT,agit_flag);
	return 0;
}

/*==========================================
 * NPCのギルドエンブレム変更
 *------------------------------------------
 */
int buildin_flagemblem(struct script_state *st)
{
	int g_id = conv_num(st,& (st->stack->stack_data[st->start+2]));
	struct npc_data *nd = map_id2nd(st->oid);

	if(nd && g_id > 0)
		nd->u.scr.guild_id = g_id;

	return 0;
}

/*==========================================
 * アジト城の名前を返す
 *------------------------------------------
 */
int buildin_getcastlename(struct script_state *st)
{
	char *mapname = conv_str(st,& (st->stack->stack_data[st->start+2]));
	struct guild_castle *gc = NULL;
	int type = 0;

	if(st->end>st->start+3)
		type = conv_num(st,& (st->stack->stack_data[st->start+3]));

	if(strcmp(mapname,"this") == 0) {
		int m = script_mapname2mapid(st,mapname);
		if(m < 0) {
			push_str(st->stack,C_CONSTSTR,"");
			return 0;
		}
		gc = guild_mapid2gc(m);
	} else {
		gc = guild_mapname2gc(mapname);
	}

	if(gc) {
		push_str(st->stack,C_STR,(unsigned char *)aStrdup(type? gc->castle_name: gc->area_name));
		return 0;
	}
	push_str(st->stack,C_CONSTSTR,"");

	return 0;
}

/*==========================================
 * アジト城のデータを取得
 *------------------------------------------
 */
int buildin_getcastledata(struct script_state *st)
{
	char *mapname = conv_str(st,& (st->stack->stack_data[st->start+2]));
	int idx       = conv_num(st,& (st->stack->stack_data[st->start+3]));
	struct guild_castle *gc = NULL;
	int val = 0;

	if(strcmp(mapname,"this") == 0) {
		int m = script_mapname2mapid(st,mapname);
		if(m < 0) {
			push_val(st->stack,C_INT,0);
			return 0;
		}
		gc = guild_mapid2gc(m);
	} else {
		gc = guild_mapname2gc(mapname);
	}

	if(gc) {
		if(idx == 0) {
			int i;
			if(st->end > st->start+4) {
				char *event = conv_str(st,& (st->stack->stack_data[st->start+4]));
				guild_addcastleinfoevent(gc->castle_id, 17, event);
			}
			for(i = 1; i < 10; i++) {
				guild_castledataload(gc->castle_id, i);
			}
		} else {
			switch(idx) {
				case 1:  val = gc->guild_id;            break;
				case 2:  val = gc->economy;             break;
				case 3:  val = gc->defense;             break;
				case 4:  val = gc->triggerE;            break;
				case 5:  val = gc->triggerD;            break;
				case 6:  val = gc->nextTime;            break;
				case 7:  val = gc->payTime;             break;
				case 8:  val = gc->createTime;          break;
				case 9:  val = gc->visibleC;            break;
				case 10: val = gc->guardian[0].visible; break;
				case 11: val = gc->guardian[1].visible; break;
				case 12: val = gc->guardian[2].visible; break;
				case 13: val = gc->guardian[3].visible; break;
				case 14: val = gc->guardian[4].visible; break;
				case 15: val = gc->guardian[5].visible; break;
				case 16: val = gc->guardian[6].visible; break;
				case 17: val = gc->guardian[7].visible; break;
			}
		}
	}
	push_val(st->stack,C_INT,val);
	return 0;
}

/*==========================================
 * アジト城のデータを変更
 *------------------------------------------
 */
int buildin_setcastledata(struct script_state *st)
{
	char *mapname = conv_str(st,& (st->stack->stack_data[st->start+2]));
	int idx       = conv_num(st,& (st->stack->stack_data[st->start+3]));
	int value     = conv_num(st,& (st->stack->stack_data[st->start+4]));
	struct guild_castle *gc = NULL;

	if(strcmp(mapname,"this") == 0) {
		int m = script_mapname2mapid(st,mapname);
		if(m < 0)
			return 0;
		gc = guild_mapid2gc(m);
	} else {
		gc = guild_mapname2gc(mapname);
	}

	if(gc) {
		switch(idx) {
			case 1:  gc->guild_id            = value; break;
			case 2:  gc->economy             = value; break;
			case 3:  gc->defense             = value; break;
			case 4:  gc->triggerE            = value; break;
			case 5:  gc->triggerD            = value; break;
			case 6:  gc->nextTime            = value; break;
			case 7:  gc->payTime             = value; break;
			case 8:  gc->createTime          = value; break;
			case 9:  gc->visibleC            = value; break;
			case 10: gc->guardian[0].visible = value; break;
			case 11: gc->guardian[1].visible = value; break;
			case 12: gc->guardian[2].visible = value; break;
			case 13: gc->guardian[3].visible = value; break;
			case 14: gc->guardian[4].visible = value; break;
			case 15: gc->guardian[5].visible = value; break;
			case 16: gc->guardian[6].visible = value; break;
			case 17: gc->guardian[7].visible = value; break;
			default: return 0;
		}
		guild_castledatasave(gc->castle_id,idx,value);
	}

	return 0;
}

/*==========================================
 * ギルド情報を要求する
 *------------------------------------------
 */
int buildin_requestguildinfo(struct script_state *st)
{
	int guild_id=conv_num(st,& (st->stack->stack_data[st->start+2]));
	char *event=NULL;

	if( st->end>st->start+3 )
		event=conv_str(st,& (st->stack->stack_data[st->start+3]));

	if(guild_id>0)
		guild_npc_request_info(guild_id,event);
	return 0;
}


/*==========================================
 * 結婚処理
 *------------------------------------------
 */
int buildin_marriage(struct script_state *st)
{
	char *partner=conv_str(st,& (st->stack->stack_data[st->start+2]));
	struct map_session_data *sd=script_rid2sd(st);
	struct map_session_data *p_sd=map_nick2sd(partner);

	if(sd==NULL || p_sd==NULL || pc_isbaby(sd) || pc_marriage(sd,p_sd) < 0)
		push_val(st->stack,C_INT,0);
	else
		push_val(st->stack,C_INT,sd->status.partner_id);
	return 0;
}

/*==========================================
 * 結婚式用のエフェクト
 *------------------------------------------
 */
int buildin_wedding_effect(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);

	if(sd)
		clif_wedding_effect(&sd->bl);
	return 0;
}

/*==========================================
 * 離婚処理
 *------------------------------------------
 */
int buildin_divorce(struct script_state *st)
{
	int num, partner_id;
	struct map_session_data *sd = script_rid2sd(st);

	if(sd == NULL) {
		push_val(st->stack,C_INT,0);
		return 0;
	}
	partner_id = sd->status.partner_id;

	num = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if(num == 0) {
		if(pc_divorce(sd) < 0) {
			push_val(st->stack,C_INT,0);
			return 0;
		}
	}
	push_val(st->stack,C_INT,partner_id);

	return 0;
}

/*==========================================
 * 養子処理
 *------------------------------------------
 */
int buildin_adoption(struct script_state *st)
{
	int ret;
	char *name = conv_str(st,& (st->stack->stack_data[st->start+2]));
	struct map_session_data *sd = script_rid2sd(st);
	struct map_session_data *p1 = map_nick2sd(name);

	if(st->end > st->start+3) {
		char *name2 = conv_str(st,& (st->stack->stack_data[st->start+3]));
		struct map_session_data *p2 = map_nick2sd(name2);
		ret = pc_adoption_sub(sd,p1,p2);
	} else {
		ret = pc_adoption(sd,p1);
	}
	push_val(st->stack,C_INT,ret);
	return 0;
}

/*==========================================
 * 養子解体
 *------------------------------------------
 */
int buildin_breakadoption(struct script_state *st)
{
	struct map_session_data *sd;

	if( st->end>st->start+2 ) {
		char *name = conv_str(st,& (st->stack->stack_data[st->start+2]));
		sd = map_nick2sd(name);
	} else {
		sd = script_rid2sd(st);
	}

	if(sd == NULL) {
		push_val(st->stack,C_INT,0);
		return 0;
	}

	push_val(st->stack,C_INT,pc_break_adoption(sd));
	return 0;
}

/*==========================================
 * ギルド同士の関係を調べる
 *------------------------------------------
 */
int buildin_getguildrelation(struct script_state *st)
{
	int gld1, gld2, result = 0;

	gld1 = conv_num(st,& (st->stack->stack_data[st->start+2]));

	if(gld1 <= 0 || guild_search(gld1) == NULL) {
		push_val(st->stack,C_INT,-1);
		return 0;
	}

	if(st->end > st->start+3) {
		gld2 = conv_num(st,& (st->stack->stack_data[st->start+3]));
	} else {
		struct map_session_data *sd = script_rid2sd(st);
		if(sd == NULL) {
			push_val(st->stack,C_INT,-1);
			return 0;
		}
		gld2 = sd->status.guild_id;
	}

	if(gld2 <= 0 || guild_search(gld2) == NULL) {
		push_val(st->stack,C_INT,-1);
		return 0;
	}

	if(gld1 == gld2)
		result += 1;
	if(guild_check_alliance(gld1, gld2, 0))
		result += 2;
	if(guild_check_alliance(gld1, gld2, 1))
		result += 4;
	if(guild_check_alliance(gld2, gld1, 1))
		result += 8;

	push_val(st->stack,C_INT,result);
	return 0;
}

/*==========================================
 * Gain guild exp [Celest]
 * guildgetexp <exp>
 *------------------------------------------
 */
int buildin_guildgetexp(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int exp;

	exp = conv_num(st,& (st->stack->stack_data[st->start+2]));

	// Expは負の値でも良い
	if(sd && sd->status.guild_id > 0)
		guild_getexp(sd, exp);

	return 0;
}

/*==========================================
 * flagname [Sapientia]
 *------------------------------------------
 */
int buildin_flagname(struct script_state *st)
{
	struct npc_data *nd = map_id2nd(st->oid);
	char *name;

	name = conv_str(st,& (st->stack->stack_data[st->start+2]));

	if(nd) {
		strncpy(nd->name, name, 24);
		nd->name[23] = '\0';
	}
	return 0;
}

/*==========================================
 * ギルドのメンバー数を取得(接続数ではなく登録数)
 *------------------------------------------
 */
int buildin_getguildmembers(struct script_state *st)
{
	int gid,i,n=0;
	struct guild *g=NULL;

	gid = conv_num(st,& (st->stack->stack_data[st->start+2]));
	g = guild_search(gid);
	if(g == NULL){
		push_val(st->stack,C_INT,-1);
		return 0;
	}
	for(i=0;i<g->max_member;i++) {
		if(g->member[i].account_id!=0)
			n++;
	}

	push_val(st->stack,C_INT,n);
	return 0;
}


/*==========================================
 * 指定PTのPTリーダーのキャラ名を返す
 *------------------------------------------
 */
int buildin_getpartyleader(struct script_state *st)
{
	int i,pt_id;
	struct party *p=NULL;

	pt_id=conv_num(st,& (st->stack->stack_data[st->start+2]));

	p=party_search(pt_id);
	if(p==NULL) {
		push_str(st->stack,C_CONSTSTR,"");
		return 0;
	}
	for(i=0;i<MAX_PARTY;i++){
		if(p->member[i].leader) {
			push_str(st->stack,C_STR,(unsigned char *)aStrdup(p->member[i].name));
			return 0;
		}
	}
	push_str(st->stack,C_CONSTSTR,"");	// リーダーが見つからない
	return 0;
}

/*==========================================
 * パーティーの接続人数取得
 *------------------------------------------
 */
int buildin_getonlinepartymember(struct script_state *st)
{
	int count = 0;
	struct party *pt = NULL;

	if(st->end>st->start+2) {
		pt = party_search(conv_num(st,&(st->stack->stack_data[st->start+2])));
	} else {
		struct map_session_data *sd = script_rid2sd(st);
		if(sd)
			pt = party_search(sd->status.party_id);
	}
	if(pt != NULL) {
		int i;
		for(i=0; i<MAX_PARTY; i++) {
			if(pt->member[i].online && pt->member[i].sd != NULL)
				count++;
		}
	}
	push_val(st->stack,C_INT,count);

	return 0;
}

/*==========================================
 * ギルドの接続人数取得
 *------------------------------------------
 */
int buildin_getonlineguildmember(struct script_state *st)
{
	struct guild *g = NULL;

	if(st->end>st->start+2) {
		g = guild_search(conv_num(st,&(st->stack->stack_data[st->start+2])));
	} else {
		struct map_session_data *sd = script_rid2sd(st);
		if(sd)
			g = guild_search(sd->status.guild_id);
	}
	push_val(st->stack,C_INT,((g != NULL)? g->connect_member: 0));

	return 0;
}

/*==========================================
 * パーティーメンバーへ変数設定
 *------------------------------------------
 */
int buildin_setpartyinmap(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int num,m;
	char *name;
	char prefix, postfix;
	struct party *pt = NULL;

	nullpo_retr(0, sd);

	if( st->stack->stack_data[st->start+2].type != C_NAME ) {
		printf("buildin_setpartyinmap: param not name\n");
		return 0;
	}
	num     = st->stack->stack_data[st->start+2].u.num;
	name    = get_str(num&0x00ffffff);
	prefix  = *name;
	postfix = name[strlen(name)-1];

	if( prefix == '$' || prefix == '\'' )
		return 0;

	m  = sd->bl.m;
	pt = party_search(sd->status.party_id);

	if(pt != NULL) {
		int i;
		for(i=0; i<MAX_PARTY; i++) {
			sd = pt->member[i].sd;
			if(sd != NULL && pt->member[i].online && sd->bl.m == m) {
				if( postfix == '$' ) {
					// 文字列
					char *str = conv_str(st,& (st->stack->stack_data[st->start+3]));
					set_reg(st,sd,num,name,(void*)str,st->stack->stack_data[st->start+2].ref);
				} else {
					// 数値
					int val = conv_num(st,& (st->stack->stack_data[st->start+3]));
					set_reg(st,sd,num,name,INT2PTR(val),st->stack->stack_data[st->start+2].ref);
				}
			}
		}
	} else {
		if( postfix == '$' ) {
			// 文字列
			char *str = conv_str(st,& (st->stack->stack_data[st->start+3]));
			set_reg(st,sd,num,name,(void*)str,st->stack->stack_data[st->start+2].ref);
		} else {
			// 数値
			int val = conv_num(st,& (st->stack->stack_data[st->start+3]));
			set_reg(st,sd,num,name,INT2PTR(val),st->stack->stack_data[st->start+2].ref);
		}
	}

	return 0;
}
