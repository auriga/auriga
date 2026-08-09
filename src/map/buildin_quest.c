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
#include <time.h>

#include "db.h"
#include "socket.h"
#include "timer.h"
#include "malloc.h"
#include "mmo.h"
#include "nullpo.h"
#include "utils.h"

#include "map.h"
#include "pc.h"
#include "script.h"
#include "script_internal.h"
#include "quest.h"

/* Split from script.c (Issue #61) */

/*==========================================
 * クエストリスト追加
 *------------------------------------------
 */
int buildin_setquest(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int quest_id;

	nullpo_retr(0, sd);

	quest_id = conv_num(st,& (st->stack->stack_data[st->start+2]));

	quest_addlist(sd, quest_id);

	return 0;
}

/*==========================================
 * クエストリスト更新
 *------------------------------------------
 */
int buildin_chgquest(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int old_id, new_id;

	nullpo_retr(0, sd);

	old_id = conv_num(st,& (st->stack->stack_data[st->start+2]));
	new_id = conv_num(st,& (st->stack->stack_data[st->start+3]));

	quest_updatelist(sd, old_id, new_id);

	return 0;
}

/*==========================================
 * クエストリスト削除
 *------------------------------------------
 */
int buildin_delquest(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int quest_id;

	nullpo_retr(0, sd);

	quest_id = conv_num(st,& (st->stack->stack_data[st->start+2]));

	quest_dellist(sd, quest_id);

	return 0;
}

/*==========================================
 * クエストリスト達成
 *------------------------------------------
 */
int buildin_compquest(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int quest_id;

	nullpo_retr(0, sd);

	quest_id = conv_num(st,& (st->stack->stack_data[st->start+2]));

	quest_update_status(sd, quest_id, 2);

	return 0;
}

/*==========================================
 * クエストリスト情報取得
 *------------------------------------------
 */
int buildin_checkquest(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	struct quest_data *qd;
	int quest_id, ret = 0;

	quest_id = conv_num(st,& (st->stack->stack_data[st->start+2]));

	qd = quest_get_data(sd, quest_id);
	if(qd) {
		if(qd->state == 2) {
			ret |= 0x08;	// クエスト達成済み
		} else {
			int i;

			ret |= 0x05;	// クエスト受注済み+討伐数クリア
			if(qd->limit < (unsigned int)time(NULL))
				ret |= 0x02;	// 時間制限クリア

			for(i = 0; i < 3; i++) {
				if(qd->mob[i].count < qd->mob[i].max) {
					ret &= ~0x04;	// 討伐数未クリア
					break;
				}
			}
		}
	}
	push_val(st->stack,C_INT, ret);

	return 0;
}

/*==========================================
 * クエストリスト制限時間取得
 *------------------------------------------
 */
int buildin_getquestlimit(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	struct quest_data *qd;
	int quest_id;

	quest_id = conv_num(st,& (st->stack->stack_data[st->start+2]));

	qd = quest_get_data(sd, quest_id);

	push_val(st->stack,C_INT,(qd)? qd->limit: 0);

	return 0;
}

/*==========================================
 * クエストリスト討伐数取得
 *------------------------------------------
 */
int buildin_getquestcount(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	struct quest_data *qd;
	int quest_id, idx = 0, ret = 0;

	quest_id = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if(st->end>st->start+3)
		idx = conv_num(st,& (st->stack->stack_data[st->start+3]));

	qd = quest_get_data(sd, quest_id);
	if(qd) {
		if(idx < 0 || idx >= 3)
			idx = 0;
		ret = qd->mob[idx].count;
	}
	push_val(st->stack,C_INT, ret);

	return 0;
}

/*==========================================
 * クエストリスト討伐最大数取得
 *------------------------------------------
 */
int buildin_getquestmaxcount(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	struct quest_data *qd;
	int quest_id, idx = 0, ret = 0;

	quest_id = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if(st->end>st->start+3)
		idx = conv_num(st,& (st->stack->stack_data[st->start+3]));

	qd = quest_get_data(sd, quest_id);
	if(qd) {
		if(idx < 0 || idx >= 3)
			idx = 0;
		ret = qd->mob[idx].max;
	}
	push_val(st->stack,C_INT, ret);

	return 0;
}

