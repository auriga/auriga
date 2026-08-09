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
#include <ctype.h>
#include <time.h>

#include "db.h"
#include "socket.h"
#include "timer.h"
#include "malloc.h"
#include "mmo.h"
#include "nullpo.h"
#include "utils.h"
#include "sqldbs.h"

#include "map.h"
#include "clif.h"
#include "pc.h"
#include "npc.h"
#include "mob.h"
#include "itemdb.h"
#include "storage.h"
#include "skill.h"
#include "status.h"
#include "unit.h"
#include "atcommand.h"
#include "buyingstore.h"
#include "achieve.h"
#include "script.h"
#include "script_internal.h"

/* Split from script.c (Issue #61) */

/*==========================================
 * GetTimeTick(0: System Tick, 1: Time Second Tick)
 *------------------------------------------
 */
int buildin_gettimetick(struct script_state *st)	/* Asgard Version */
{
	int type;

	type=conv_num(st,& (st->stack->stack_data[st->start+2]));

	switch(type){
	case 0:
		// System Ticks
		push_val(st->stack,C_INT,gettick());
		break;
	case 1:
		// Second Ticks: 0-86399, 00:00:00-23:59:59
		{
			time_t timer;
			struct tm *t;
			time(&timer);
			t=localtime(&timer);
			push_val(st->stack,C_INT,((t->tm_hour)*3600+(t->tm_min)*60+t->tm_sec));
		}
		break;
	case 2:
		// Get the number of seconds elapsed since 00:00 hours, Jan 1, 1970 UTC from the system clock
		push_val(st->stack,C_INT,(int)time(NULL));
		break;
	default:
		push_val(st->stack,C_INT,0);
		break;
	}
	return 0;
}

/*==========================================
 * GetTime(Type);
 * 1: Sec	 2: Min	 3: Hour
 * 4: WeekDay	 5: MonthDay	 6: Month
 * 7: Year
 *------------------------------------------
 */
int buildin_gettime(struct script_state *st)	/* Asgard Version */
{
	int type;
	time_t timer;
	struct tm *t;

	type=conv_num(st,& (st->stack->stack_data[st->start+2]));

	time(&timer);
	t=localtime(&timer);

	switch(type){
	case 1:	// Sec(0~59)
		push_val(st->stack,C_INT,t->tm_sec);
		break;
	case 2:	// Min(0~59)
		push_val(st->stack,C_INT,t->tm_min);
		break;
	case 3:	// Hour(0~23)
		push_val(st->stack,C_INT,t->tm_hour);
		break;
	case 4:	// WeekDay(0~6)
		push_val(st->stack,C_INT,t->tm_wday);
		break;
	case 5:	// MonthDay(01~31)
		push_val(st->stack,C_INT,t->tm_mday);
		break;
	case 6:	// Month(01~12)
		push_val(st->stack,C_INT,t->tm_mon+1);
		break;
	case 7:	// Year(20xx)
		push_val(st->stack,C_INT,t->tm_year+1900);
		break;
	default:
		push_val(st->stack,C_INT,-1);
		break;
	}
	return 0;
}

/*==========================================
 * GetTimeStr("TimeFMT", Length);
 *------------------------------------------
 */
int buildin_gettimestr(struct script_state *st)
{
	char *tmpstr, *fmtstr;
	int maxlen;
	time_t now = time(NULL);

	fmtstr = conv_str(st,& (st->stack->stack_data[st->start+2]));
	maxlen = conv_num(st,& (st->stack->stack_data[st->start+3]));

	tmpstr = (char *)aCalloc(maxlen+1,sizeof(char));
	if( !strftime(tmpstr,maxlen+1,fmtstr,localtime(&now)) ) {
		printf("buildin_gettimestr: maxlen is too short!!\n");
	}
	tmpstr[maxlen] = '\0';

	push_str(st->stack,C_STR,tmpstr);
	return 0;
}

/*==========================================
 * カプラ倉庫を開く
 *------------------------------------------
 */
int buildin_openstorage(struct script_state *st)
{
	storage_storageopen(script_rid2sd(st));
	return 0;
}


/*==========================================
 * 存在チェック
 *------------------------------------------
 */
int buildin_isloggedin(struct script_state *st)
{
	int id = conv_num(st,& (st->stack->stack_data[st->start+2]));

	push_val(st->stack,C_INT,(map_id2sd(id) ? 1: 0));
	return 0;
}


/*==========================================
 * PCのスキル情報読み取り
 *------------------------------------------
 */
int buildin_getskilllist(struct script_state *st)
{
	struct map_session_data *sd=script_rid2sd(st);
	int i,j=0,k=0;

	if(!sd)
		return 0;
	for(i=0;i<MAX_PCSKILL;i++){
		if(sd->status.skill[i].id <= 0 || sd->status.skill[i].lv <= 0)
			continue;
		if(j >= 128) {
			j=0;
			k++;
		}
		if(k == 0) {
			pc_setreg(sd,add_str("@skilllist_id")+(j<<24),sd->status.skill[i].id);
			pc_setreg(sd,add_str("@skilllist_lv")+(j<<24),sd->status.skill[i].lv);
			pc_setreg(sd,add_str("@skilllist_flag")+(j<<24),sd->status.skill[i].flag);
		} else {
			char buf[32];
			sprintf(buf,"@skilllist_id[%d]",k);
			pc_setreg(sd,add_str(buf)+(j<<24),sd->status.skill[i].id);
			sprintf(buf,"@skilllist_lv[%d]",k);
			pc_setreg(sd,add_str(buf)+(j<<24),sd->status.skill[i].lv);
			sprintf(buf,"@skilllist_flag[%d]",k);
			pc_setreg(sd,add_str(buf)+(j<<24),sd->status.skill[i].flag);
		}
		j++;
	}
	pc_setreg(sd,add_str("@skilllist_count"),k*128+j);
	return 0;
}

/*==========================================
 * gmcommand
 * suggested on the forums...
 *------------------------------------------
 */
int buildin_gmcommand(struct script_state *st)
{
	char *str;

	str = conv_str(st,& (st->stack->stack_data[st->start+2]));

	if(st->rid) {
		struct map_session_data *sd = map_id2sd(st->rid);
		if(sd) {
			is_atcommand_sub(sd->fd, sd, str, 99);
			return 0;
		}
	}
	if(st->oid) {
		// 人が居ないイベント系NPCで使った場合のためのダミーmap_session_data
		struct map_session_data dummy_sd;
		struct block_list *bl = map_id2bl(st->oid);

		if(bl) {
			memset(&dummy_sd, 0, sizeof(struct map_session_data));
			memcpy(&dummy_sd.bl, bl, sizeof(struct block_list));
			dummy_sd.fd = 0;
			dummy_sd.bl.prev = NULL;
			dummy_sd.bl.next = NULL;
			if(bl->type == BL_NPC) {
				char *p;
				strncpy(dummy_sd.status.name, ((struct npc_data *)bl)->name, 24);
				if((p = strchr(dummy_sd.status.name,'#')) != NULL)
					*p = 0;
			} else {
				strncpy(dummy_sd.status.name, "dummy", 24);
			}
			is_atcommand_sub(dummy_sd.fd, &dummy_sd, str, 99);
			return 0;
		}
	}

	return 0;
}

/*==========================================
 * 指定キャラの居るマップ名取得
 *------------------------------------------
 */
int buildin_getmapname(struct script_state *st)
{
	struct map_session_data *sd;
	char *char_name = conv_str(st,& (st->stack->stack_data[st->start+2]));

	if( strlen(char_name) >= 4 )
		sd = map_nick2sd(char_name);
	else
		sd = script_rid2sd(st);

	if(sd)
		push_str(st->stack,C_STR,(unsigned char *)aStrdup(sd->mapname));
	else
		push_str(st->stack,C_CONSTSTR,"");

	return 0;
}


/*==========================================
 * 指定オブジェクトの位置を取得
 *------------------------------------------
 */
int buildin_getmapxy(struct script_state *st)
{
	struct map_session_data *sd = NULL;
	struct npc_data         *nd = NULL;
	struct mob_data         *md = NULL;
	struct pet_data         *pd = NULL;
	struct homun_data       *hd = NULL;
	int num;
	char *name;
	char prefix, postfix;
	int x,y,type;
	char mapname[24];
	void *v;

	if( st->stack->stack_data[st->start+2].type != C_NAME ||
	    st->stack->stack_data[st->start+3].type != C_NAME ||
	    st->stack->stack_data[st->start+4].type != C_NAME )
	{
		printf("buildin_getmapxy: param not name\n");
		push_val(st->stack,C_INT,-1);
		return 0;
	}

	type=conv_num(st,& (st->stack->stack_data[st->start+5]));

	memset(mapname, 0, sizeof(mapname));
	switch (type){
		case 0:		// Get Character Position
			if( st->end>st->start+6 )
				sd=map_nick2sd(conv_str(st,& (st->stack->stack_data[st->start+6])));
			else
				sd=script_rid2sd(st);

			if ( sd==NULL ) {	// wrong char name or char offline
				push_val(st->stack,C_INT,-1);
				return 0;
			}
			x=sd->bl.x;
			y=sd->bl.y;
			memcpy(mapname,sd->mapname,24);
			break;
		case 1:		// Get NPC Position
			if( st->end > st->start+6 )
				nd = npc_name2id(conv_str(st,& (st->stack->stack_data[st->start+6])));
			else
				nd = map_id2nd(st->oid);
			if ( nd==NULL ) {	// wrong npc name
				push_val(st->stack,C_INT,-1);
				return 0;
			}
			x=nd->bl.x;
			y=nd->bl.y;
			if(nd->bl.m == -1)
				mapname[0] = '-';	// マップに配置されないNPC
			else
				memcpy(mapname,map[nd->bl.m].name,24);
			break;
		case 2:		// Get Pet Position
			if( st->end>st->start+6 )
				sd=map_nick2sd(conv_str(st,& (st->stack->stack_data[st->start+6])));
			else
				sd=script_rid2sd(st);
			if ( sd==NULL ) {	// wrong char name or char offline
				push_val(st->stack,C_INT,-1);
				return 0;
			}
			pd=sd->pd;
			if ( pd==NULL ){	// pet data not found
				push_val(st->stack,C_INT,-1);
				return 0;
			}
			x=pd->bl.x;
			y=pd->bl.y;
			memcpy(mapname,map[pd->bl.m].name,24);
			break;
		case 3:		// Get Mob Position
			if( st->end > st->start+6 )
				md = map_id2md(conv_num(st,& (st->stack->stack_data[st->start+6])));
			if( md==NULL || md->bl.prev == NULL ) {	// wrong mob id
				push_val(st->stack,C_INT,-1);
				return 0;
			}
			x=md->bl.x;
			y=md->bl.y;
			memcpy(mapname,map[md->bl.m].name,24);
			break;
		case 4:		// Get Homun Position
			if( st->end>st->start+6 )
				sd=map_nick2sd(conv_str(st,& (st->stack->stack_data[st->start+6])));
			else
				sd=script_rid2sd(st);
			if ( sd==NULL ) {	// wrong char name or char offline
				push_val(st->stack,C_INT,-1);
				return 0;
			}
			hd=sd->hd;
			if ( hd==NULL ){	// homun data not found
				push_val(st->stack,C_INT,-1);
				return 0;
			}
			x=hd->bl.x;
			y=hd->bl.y;
			memcpy(mapname,map[hd->bl.m].name,24);
			break;
		default:	// Wrong type parameter
			push_val(st->stack,C_INT,-1);
			return 0;
	}

	// Set MapName$
	num     = st->stack->stack_data[st->start+2].u.num;
	name    = get_str(num&0x00ffffff);
	prefix  = *name;
	postfix = name[strlen(name)-1];

	sd = (prefix != '$' && prefix != '\'')? script_rid2sd(st): NULL;
	if(postfix == '$') {
		v = (void*)mapname;
	} else {
		v = INT2PTR(atoi(mapname));
	}
	set_reg(st,sd,num,name,v,st->stack->stack_data[st->start+2].ref);

	// Set MapX
	num     = st->stack->stack_data[st->start+3].u.num;
	name    = get_str(num&0x00ffffff);
	prefix  = *name;
	postfix = name[strlen(name)-1];

	sd = (prefix != '$' && prefix != '\'')? script_rid2sd(st): NULL;
	if(postfix == '$') {
		char str[16];
		sprintf(str, "%d", x);
		v = (void*)str;
	} else {
		v = INT2PTR(x);
	}
	set_reg(st,sd,num,name,v,st->stack->stack_data[st->start+3].ref);

	// Set MapY
	num     = st->stack->stack_data[st->start+4].u.num;
	name    = get_str(num&0x00ffffff);
	prefix  = *name;
	postfix = name[strlen(name)-1];

	sd = (prefix != '$' && prefix != '\'')? script_rid2sd(st): NULL;
	if(postfix == '$') {
		char str[16];
		sprintf(str, "%d", y);
		v = (void*)str;
	} else {
		v = INT2PTR(y);
	}
	set_reg(st,sd,num,name,v,st->stack->stack_data[st->start+4].ref);

	// Return Success value
	push_val(st->stack,C_INT,0);
	return 0;
}


/*==========================================
 * 料理用
 *------------------------------------------
 */
int buildin_making(struct script_state *st)
{
	struct map_session_data *sd;
	int makeid=conv_num(st,& (st->stack->stack_data[st->start+2]));

	sd = script_rid2sd(st);
	if(sd && sd->skill_menu.id == 0){
		int rate = conv_num(st,& (st->stack->stack_data[st->start+3]));
		clif_making_list(sd,makeid,1,rate,1);
	}
	return 0;
}

/*==========================================
 * 指定マップのpvp,gvgフラグを調べる
 *------------------------------------------
 */
int buildin_getpkflag(struct script_state *st)
{
	char *str;
	int m,count=0;

	str = conv_str(st,& (st->stack->stack_data[st->start+2]));

	m = script_mapname2mapid(st,str);
	if(m < 0) {
		push_val(st->stack,C_INT,-1);
		return 0;
	}

	if(map[m].flag.pvp)
		count += 1;
	if(map[m].flag.gvg)
		count += 2;

	push_val(st->stack,C_INT,count);
	return 0;
}


/*==========================================
 * 見た目サイズの変更
 * type1=PC type2=PET type3=HOM type4=NPC
 * 小 size=-1 大 size=1
 *------------------------------------------
 */
int buildin_changeviewsize(struct script_state *st)
{
	struct block_list *bl = NULL;
	struct map_session_data *sd;
	int type=conv_num(st,& (st->stack->stack_data[st->start+2]));
	int size=conv_num(st,& (st->stack->stack_data[st->start+3]));

	sd = map_id2sd(st->rid);
	if(sd == NULL && type != 4)
		return 1;

	size = (size<0)? -1: (size>0)? 1: 0;

	switch (type) {
		case 1:
			bl = &sd->bl;
			break;
		case 2:
			if(sd->pd)
				bl = &sd->pd->bl;
			break;
		case 3:
			if(sd->hd)
				bl = &sd->hd->bl;
			break;
		case 4:
			bl = map_id2bl(st->oid);
			break;
		default:
			break;
	}
	if(bl)
		unit_changeviewsize(bl,size);

	return 0;
}


/*==========================================
 * 文字列長を返す
 *------------------------------------------
 */
int buildin_getstrlen(struct script_state *st)
{
	char *str = conv_str(st,& (st->stack->stack_data[st->start+2]));

	push_val(st->stack,C_INT,(int)strlen(str));

	return 0;
}

/*==========================================
 * 文字列の任意の部分を取得する
 *------------------------------------------
 */
int buildin_substr(struct script_state *st)
{
	char *str;
	int len, offset, count;

	str    = conv_str(st,& (st->stack->stack_data[st->start+2]));
	offset = conv_num(st,& (st->stack->stack_data[st->start+3]));

	len = (int)strlen(str);
	if(offset < 0)		// 開始位置が負なので末尾から位置を計算
		offset += len;
	if(offset < 0 || offset >= len) {
		push_str(st->stack,C_CONSTSTR,"");
		return 0;
	}

	if(st->end > st->start+4) {
		count = conv_num(st,& (st->stack->stack_data[st->start+4]));
		if(count > 0 && offset + count > len)
			count = len - offset;		// 文字列長を超えるので補正
		else if(count < 0)
			count = len - offset + count;	// 個数が負なので末尾から個数分削る
	} else {
		count = len - offset;			// 引数省略時は最後まで
	}

	if(count > 0) {
		char *buf = (char *)aCalloc(count+1, sizeof(char));
		memcpy(buf, str+offset, count);
		push_str(st->stack,C_STR,buf);
	} else {
		push_str(st->stack,C_CONSTSTR,"");
	}
	return 0;
}

/*==========================================
 * 文字列中に指定文字が含まれているかどうか
 *------------------------------------------
 */
int buildin_strstr(struct script_state *st)
{
	const char *str;
	const char *cmpstr;
	int len, offset = 0;
	int pos = 0;

	str    = conv_str(st,& (st->stack->stack_data[st->start+2]));
	cmpstr = conv_str(st,& (st->stack->stack_data[st->start+3]));

	len = (int)strlen(str);

	do {
		if(*str != *cmpstr && offset) {
			cmpstr -= offset;
			pos += offset;
			offset = 0;
		}

		if(*str == *cmpstr) {
			cmpstr++;
			if(*cmpstr == 0)
				break;
			offset++;
		}
		else {
			pos++;
		}
	} while(*str++);

	if(pos < len)
		push_val(st->stack,C_INT,1);
	else
		push_val(st->stack,C_INT,0);

	return 0;
}

/*==========================================
 * PCとNPC間の距離を返す
 *------------------------------------------
 */
int buildin_distance(struct script_state *st)
{
	struct map_session_data *sd;
	struct npc_data *nd;

	sd = map_id2sd(conv_num(st,& (st->stack->stack_data[st->start+2])));
	if(st->end > st->start+3)
		nd = npc_name2id(conv_str(st,& (st->stack->stack_data[st->start+3])));
	else
		nd = map_id2nd(st->oid);

	if(sd && nd && sd->bl.m == nd->bl.m)
		push_val(st->stack,C_INT,unit_distance(&sd->bl,&nd->bl));
	else
		push_val(st->stack,C_INT,-1);
	return 0;
}


/*==========================================
 * SQLクエリ発行
 *------------------------------------------
 */
int buildin_sqlquery(struct script_state *st)
{
#ifndef TXT_ONLY
	int count = -1;
	char *query;
	struct sqldbs_handle *handle = &mysql_handle_script;

	query = conv_str(st,& (st->stack->stack_data[st->start+2]));

	// SQLクエリ利用不可ならエラー
	if(!script_sql_enabled()) {
		push_val(st->stack,C_INT,-1);
		return 0;
	}
	if(sqldbs_simplequery(handle, query) == false) {
		push_val(st->stack,C_INT,-1);
		return 0;
	}

	if(sqldbs_has_result(handle) == false) {
		// SELECT以外はここで完了
		count = sqldbs_affected_rows(&mysql_handle_script);
		push_val(st->stack,C_INT,count);
		return 0;
	}

	do {
		int num, len, elem, max;
		char *name, *var, *p;
		char prefix, postfix;
		struct map_session_data *sd = NULL;
		char **sql_row;

		if(st->end <= st->start+3 || st->stack->stack_data[st->start+3].type != C_NAME) {
			printf("buildin_sqlquery: param not name\n");
			break;
		}
		num     = st->stack->stack_data[st->start+3].u.num;
		name    = get_str(num&0x00ffffff);
		prefix  = *name;
		postfix = name[strlen(name)-1];

		if( prefix != '$' && prefix != '@' && prefix != '\'' ) {
			printf("buildin_sqlquery: illegal scope !\n");
			break;
		}
		if( prefix != '$' && prefix != '\'' ) {
			sd = script_rid2sd(st);
			if(sd == NULL)
				break;
		}

		var = (char *)aCalloc(strlen(name) + 6, sizeof(char));	// [xxx] + \0 = 6文字
		strcpy(var, name);

		if((p = strrchr(var,'[')) != NULL) {
			elem = atoi(p+1);	// 配列の二次元目の要素を取得
			len  = (int)(p - var);
		} else {
			elem = 0;
			len = (int)strlen(var);
			if(postfix == '$')
				len--;
		}

		max = sqldbs_num_fields(handle);
		if(max + (num >> 24) > 128) {
			max = 128 - (num>>24);
		}

		for(count = 0; elem < 128 && (sql_row = sqldbs_fetch(handle)); count++) {
			int i, tmp_num;

			if(count > 0) {	// 結果セットが複数行あるので変数名を合成する
				sprintf(var + len, "[%d]%s", elem, (postfix == '$')? "$": "");
				tmp_num = add_str(var) + (num&0xff000000);
			} else {
				tmp_num = num;
			}
			for(i = 0; i < max; i++) {
				void *v = (postfix == '$')? sql_row[i]: INT2PTR(atoi(sql_row[i]));
				set_reg(st, sd, tmp_num + (i<<24), var, v, st->stack->stack_data[st->start+3].ref);
			}
			elem++;
		}
		aFree(var);
	} while(0);

	sqldbs_free_result(handle);
	push_val(st->stack,C_INT,count);
#else
	// TXTは何もしない
	push_val(st->stack,C_INT,-1);
#endif
	return 0;
}

/*==========================================
 * SQL用の文字列エスケープ
 *------------------------------------------
 */
int buildin_strescape(struct script_state *st)
{
	char *str = conv_str(st,& (st->stack->stack_data[st->start+2]));

#ifndef TXT_ONLY
	char *buf = (char *)aCalloc(strlen(str)*2+1,sizeof(char));

	strecpy_(&mysql_handle_script,buf,str);
	push_str(st->stack,C_STR,buf);
#else
	// TXTは何もしない
	push_str(st->stack,C_STR,(unsigned char *)aStrdup(str));
#endif
	return 0;
}


/*==========================================
 * 経験値取得
 *------------------------------------------
 */
int buildin_getexp(struct script_state *st)
{
	int base, job, quest = 1;
	struct map_session_data *sd = script_rid2sd(st);

	nullpo_retr(0, sd);

	base = conv_num(st,& (st->stack->stack_data[st->start+2]));
	job  = conv_num(st,& (st->stack->stack_data[st->start+3]));
	if(st->end > st->start+4)
		quest = conv_num(st,& (st->stack->stack_data[st->start+4]));

	if(base < 0 || job < 0)
		return 0;
	pc_gainexp(sd,NULL,base,job,quest);

	return 0;
}


/*==========================================
 * 読書ウィンドウの表示
 *------------------------------------------
 */
int buildin_openbook(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int nameid, page = 1;

	nullpo_retr(0, sd);

	nameid = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if(st->end>st->start+3)
		page = conv_num(st,& (st->stack->stack_data[st->start+3]));

	clif_openbook(sd,nameid,page);

	return 0;
}

/*==========================================
 * ノックバック
 *------------------------------------------
 */
int buildin_pushpc(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	struct block_list *bl = map_id2bl(st->oid);
	int dir, count;

	nullpo_retr(0, sd);

	if(bl == NULL || bl->type != BL_NPC)
		bl = &sd->bl;

	dir = conv_num(st,& (st->stack->stack_data[st->start+2]));
	count = conv_num(st,& (st->stack->stack_data[st->start+3]));

	skill_blown(bl,&sd->bl,count|(dir<<20)|SAB_NODAMAGE|SAB_NOPATHSTOP);

	return 0;
}

/*==========================================
 * 指定セルのタイプを変更
 *------------------------------------------
 */
int buildin_setcell(struct script_state *st)
{
	int m,x,y,type;
	int area = 1;
	char *str;

	str  = conv_str(st,& (st->stack->stack_data[st->start+2]));
	x    = conv_num(st,& (st->stack->stack_data[st->start+3]));
	y    = conv_num(st,& (st->stack->stack_data[st->start+4]));
	type = conv_num(st,& (st->stack->stack_data[st->start+5]));
	if(st->end>st->start+6)
		area = conv_num(st,& (st->stack->stack_data[st->start+6]));

	m = script_mapname2mapid(st,str);
	if(m < 0) {
		return 0;
	}
	map_setcell(m,x,y,type);
	clif_changemapcell(m,x,y,type,area);

	return 0;
}

/*==========================================
 * 指定範囲セルのタイプを変更
 *------------------------------------------
 */
int buildin_areasetcell(struct script_state *st)
{
	int m,x,y,x0,y0,x1,y1,type;
	int area = 1;
	char *str;

	str  = conv_str(st,& (st->stack->stack_data[st->start+2]));
	x0   = conv_num(st,& (st->stack->stack_data[st->start+3]));
	y0   = conv_num(st,& (st->stack->stack_data[st->start+4]));
	x1   = conv_num(st,& (st->stack->stack_data[st->start+5]));
	y1   = conv_num(st,& (st->stack->stack_data[st->start+6]));
	type = conv_num(st,& (st->stack->stack_data[st->start+7]));
	if(st->end>st->start+8)
		area = conv_num(st,& (st->stack->stack_data[st->start+8]));

	m = script_mapname2mapid(st,str);
	if(m < 0) {
		return 0;
	}

	for(y = y0; y <= y1; y++) {
		for(x = x0; x <= x1; x++) {
			map_setcell(m,x,y,type);
			clif_changemapcell(m,x,y,type,area);
		}
	}

	return 0;
}

/*==========================================
 * 前職業Class取得
 *------------------------------------------
 */
int buildin_getbaseclass(struct script_state *st)
{
	int class_, type = 0;

	class_ = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if(st->end>st->start+3)
		type = conv_num(st,& (st->stack->stack_data[st->start+3]));

	class_ = pc_get_base_class(class_, type);
	push_val(st->stack,C_INT,class_);

	return 0;
}

/*==========================================
 * 購買露店ウインドウオープン
 *------------------------------------------
 */
int buildin_openbuyingstore(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int count;

	nullpo_retr(0, sd);

	count = conv_num(st,& (st->stack->stack_data[st->start+2]));

	buyingstore_openstorewindow(sd, count);

	return 0;
}

/*==========================================
 * フォントタイプのセット
 *------------------------------------------
 */
int buildin_setfont(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int type = conv_num(st,& (st->stack->stack_data[st->start+2]));

	nullpo_retr(0, sd);

	if(sd->status.font == type)
		sd->status.font = 0;
	else
		sd->status.font = type;

	clif_setfont(sd);

	return 0;
}

/*==========================================
 * ClassからJob変換
 *------------------------------------------
 */
int buildin_getclassjob(struct script_state *st)
{
	int class_, job = 0;

	class_ = conv_num(st,& (st->stack->stack_data[st->start+2]));

	job = pc_calc_job_class(class_);

	push_val(st->stack,C_INT,job);

	return 0;
}

/*==========================================
 * 発言表示
 *------------------------------------------
 */
int buildin_unittalk(struct script_state *st)
{
	struct block_list *bl;
	struct script_data *data;
	char *mes = NULL;
	int flag = 0;

	data = &(st->stack->stack_data[st->start+2]);
	get_val(st,data);
	if( isstr(data) ) {
		bl = map_id2bl(st->oid);
		mes = conv_str(st,data);
		if( st->end > st->start+3 )
			flag = conv_num(st,& (st->stack->stack_data[st->start+3]));
	} else {
		bl = map_id2bl(conv_num(st,data));

		data = &(st->stack->stack_data[st->start+3]);
		get_val(st,data);
		if( isstr(data) ) {
			mes = conv_str(st,data);
		}
		if( st->end > st->start+4 )
			flag = conv_num(st,& (st->stack->stack_data[st->start+4]));
	}

	if(bl == NULL || mes == NULL)
		return 0;

	if(bl->type == BL_PC) {	// グローバルメッセージ送信
		struct map_session_data *sd = (struct map_session_data *)bl;
		if(flag)
			clif_displaymessage(sd->fd, mes);
		else
			clif_disp_overhead(sd, mes);
	}
	else if(bl->m >= 0) {
		if(flag) {
			struct map_session_data *sd = script_rid2sd(st);
			if(sd)
				clif_GlobalMessage_id(&sd->bl, bl->id, mes, SELF);
		}
		else
			clif_GlobalMessage(bl, mes, WIDE_AREA);
	}

	return 0;
}

/*==========================================
 * プレイヤーの行動制限オンオフ
 *------------------------------------------
 */
int buildin_pcblockmove(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int flag;

	nullpo_retr(0, sd);

	flag = conv_num(st,& (st->stack->stack_data[st->start+2]));

	unit_stop_walking(&sd->bl,1);
	sd->state.blockedmove = flag > 0;

	return 0;
}


/*==========================================
 * リニューアルかどうか
 *------------------------------------------
 */
int buildin_checkre(struct script_state *st)
{
#ifdef PRE_RENEWAL
	push_val(st->stack,C_INT,0);
#else
	push_val(st->stack,C_INT,1);
#endif
	return 0;
}

/*==========================================
 * ドレスルームを開く
 *------------------------------------------
 */
int buildin_opendressroom(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int view = 1;

	nullpo_retr(0, sd);

	if( st->end > st->start+2 )
		view = conv_num(st,& (st->stack->stack_data[st->start+2]));
	clif_dressing_room(sd, view);
	return 0;
}

/*==========================================
 * Hat_effect
 *------------------------------------------
 */
int buildin_hateffect(struct script_state *st)
{
#if PACKETVER >= 20150513
	struct map_session_data *sd = script_rid2sd(st);
	bool enable;
	int i, effectID;

	nullpo_retr(0, sd);

	effectID = conv_num(st,& (st->stack->stack_data[st->start+2]));
	enable = conv_num(st,& (st->stack->stack_data[st->start+3])) ? true : false;

	if( effectID <= HAT_EF_MIN || effectID >= HAT_EF_MAX ) {
		printf( "buildin_hateffect: unsupported hat effect id: %d\n", effectID );
		return 1;
	}

	for(i = 0; i < sd->hatEffect.count; i++) {
		if(sd->hatEffect.id[i] == effectID)
			break;
	}

	if( enable ) {
		if( i < sd->hatEffect.count ) {
			return 0;
		}

		sd->hatEffect.id[sd->hatEffect.count] = effectID;
		sd->hatEffect.count++;
	}
	else {
		if( i == sd->hatEffect.count ) {
			return 0;
		}

		for( ; i < sd->hatEffect.count - 1; i++ ) {
			sd->hatEffect.id[i] = sd->hatEffect.id[i+1];
		}

		sd->hatEffect.count--;

		if( !sd->hatEffect.count )
			sd->hatEffect.count = 0;

	}

	if( !sd->state.connect_new ) {
		clif_hat_effect_single( sd, effectID, enable );
	}
#endif
	return 0;
}

/*==========================================
 * ランダム系アイテムのID取得
 *------------------------------------------
 */
int buildin_getrandombox(struct script_state *st)
{
	int nameid = conv_num(st,& (st->stack->stack_data[st->start+2]));

	push_val(st->stack,C_INT,itemdb_searchrandomid(-nameid));
	return 0;
}


/*==========================================
 * クエスト実績獲得
 *------------------------------------------
 */
int buildin_achievement(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int nameid = conv_num(st,& (st->stack->stack_data[st->start+2]));

	if(sd)
		achieve_update_content(sd, ACH_ADVENTURE, nameid, 1);
	return 0;
}

/*==========================================
 * 実績獲得
 *------------------------------------------
 */
int buildin_achievement2(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int type = conv_num(st,& (st->stack->stack_data[st->start+2]));
	int nameid = conv_num(st,& (st->stack->stack_data[st->start+3]));
	int num = conv_num(st,& (st->stack->stack_data[st->start+4]));

	if(type <= ACH_NONE || type >= ACH_MAX) {
		printf("buildin_achievement2: unsupported arg1, type=%d\n", type);
		return 1;
	}

	switch(type) {
	case ACH_LEVEL:
		if(nameid != SP_BASELEVEL && nameid != SP_JOBLEVEL) {
			printf("buildin_achievement2: unsupported arg2, type=%d, id=%d\n", type, nameid);
			return 1;
		}
		break;
	case ACH_STATUS:
		if(nameid < SP_STR || nameid > SP_LUK) {
			printf("buildin_achievement2: unsupported arg2, type=%d, id=%d\n", type, nameid);
			return 1;
		}
		break;
	case ACH_SPEND_ZENY:
	case ACH_GET_ZENY:
		if(nameid != SP_ZENY) {
			printf("buildin_achievement2: unsupported arg2, type=%d, id=%d\n", type, nameid);
			return 1;
		}
		break;
	case ACH_ACHIEVE:
	case ACH_QUEST:
		// 対象の存在チェックはしないよ！
		break;
	}

	if(sd)
		achieve_update_content(sd, type, nameid, num);
	return 0;
}


/*==========================================
 * アップグレードウィンドウ表示
 *------------------------------------------
 */
int buildin_openupgrade(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int nameid;

	nullpo_retr(0, sd);

	nameid = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if(nameid <= 0)
		return 0;

	clif_openlapineupgrade(sd, nameid);

	return 0;
}

/*==========================================
 * ユニットにGroup_id設定
 *------------------------------------------
 */
int buildin_setunitgroup(struct script_state *st)
{
	struct block_list *bl;
	int id;

	id = conv_num(st,& (st->stack->stack_data[st->start+2]));
	bl = map_id2bl(conv_num(st,& (st->stack->stack_data[st->start+3])));

	if(id < 0)
		return 0;
	if(bl == NULL || bl->type != BL_MOB)
		return 0;

	((struct mob_data*)bl)->group_id  = id;

	return 0;
}


/*==========================================
 * ユニットにTitle設定
 *------------------------------------------
 */
int buildin_setunittitle(struct script_state *st)
{
	struct block_list *bl;
	char *str;

	str = conv_str(st,& (st->stack->stack_data[st->start+2]));
	bl = map_id2bl(conv_num(st,& (st->stack->stack_data[st->start+3])));

	if(bl == NULL || bl->type != BL_MOB)
		return 0;

	strncpy(((struct mob_data*)bl)->title, str, 24);
	((struct mob_data*)bl)->title[23] = '\0';

	return 0;
}
