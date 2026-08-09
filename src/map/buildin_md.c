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
#include "party.h"
#include "memorial.h"
#include "script.h"
#include "script_internal.h"

/* Split from script.c (Issue #61) */

/*==========================================
 * メモリアルダンジョン作成
 *------------------------------------------
 */
int buildin_mdcreate(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	char *memorial_name;
	int party_id, ret;

	nullpo_retr(0, sd);

	memorial_name = conv_str(st,& (st->stack->stack_data[st->start+2]));

	if(st->end>st->start+3)
		party_id = conv_num(st,&(st->stack->stack_data[st->start+3]));
	else
		party_id = sd->status.party_id;

	ret = memorial_create(memorial_name, party_id);
	switch(ret) {
		case MDCREATE_EXISTS:		// 既に生成済み
			clif_msgstringtable2(sd, 0x52a, memorial_name);	// メモリアルダンジョン「%s」の予約が重複生成要請により失敗しました。
			break;
		case MDCREATE_PERMISSION:	// 権限がない
			clif_msgstringtable2(sd, 0x529, memorial_name);	// メモリアルダンジョン「%s」の予約が権限問題により失敗しました。
			break;
		case MDCREATE_RESERVED:		// 既に予約済み
			clif_msgstringtable2(sd, 0x528, memorial_name);	// メモリアルダンジョン「%s」の予約が予約重複により失敗しました。
			break;
		case MDCREATE_ERROR:		// その他エラー
			clif_msgstringtable2(sd, 0x527, memorial_name);	// メモリアルダンジョン「%s」の予約に失敗しました。
			break;
	}

	return 0;
}

/*==========================================
 * メモリアルダンジョン削除
 *------------------------------------------
 */
int buildin_mddelete(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int party_id = 0;

	if(st->end>st->start+2)
		party_id = conv_num(st,&(st->stack->stack_data[st->start+2]));
	else if(sd)
		party_id = sd->status.party_id;

	if(party_id > 0) {
		struct party *pt = party_search(party_id);
		if(pt)
			memorial_delete(pt->memorial_id);
	}

	return 0;
}

/*==========================================
 * メモリアルダンジョン入場
 *------------------------------------------
 */
int buildin_mdenter(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int ret = MDENTER_ERROR;
	char *name = conv_str(st,& (st->stack->stack_data[st->start+2]));

	if(sd) {
		ret = memorial_enter(sd, name);
	}

	push_val(st->stack,C_INT,ret);

	return 0;
}

/*==========================================
 * メモリアルダンジョン状態
 *------------------------------------------
 */
int buildin_mdopenstate(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int ret = -1;
	char *name = conv_str(st,& (st->stack->stack_data[st->start+2]));

	if(sd) {
		ret = memorial_openstate(sd, name);
	}

	push_val(st->stack,C_INT,ret);

	return 0;
}

/*==========================================
 * メモリアルダンジョンMAP名取得
 *------------------------------------------
 */
int buildin_getmdmapname(struct script_state *st)
{
	char *str = conv_str(st,& (st->stack->stack_data[st->start+2]));
	int id = script_getmemorialid(st);
	int m = memorial_mapname2mapid(str, id);

	if(m < 0)
		push_str(st->stack,C_CONSTSTR,"");
	else
		push_str(st->stack,C_STR,(unsigned char *)aStrdup(map[m].name));

	return 0;
}
