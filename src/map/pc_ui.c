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

#include "map.h"
#include "pc_ui.h"

struct pc_ui_policy {
	unsigned int blocks;
	int close_on_warp;
};

/* 閲覧中の移動など、既存の画面別の制限を維持する。 */
static const struct pc_ui_policy pc_ui_policies[] = {
	{ 0, 0 },
	{ PC_UI_BLOCK_MOVE | PC_UI_BLOCK_ACTION | PC_UI_BLOCK_SKILL |
	  PC_UI_BLOCK_ITEM | PC_UI_BLOCK_INTERACT | PC_UI_BLOCK_TRADE | PC_UI_BLOCK_OTHER_UI, 1 },
	{ PC_UI_BLOCK_OTHER_UI, 0 },
	{ PC_UI_BLOCK_OTHER_UI, 0 },
	{ PC_UI_BLOCK_OTHER_UI, 1 },
	{ PC_UI_BLOCK_OTHER_UI, 1 },
	{ PC_UI_BLOCK_OTHER_UI, 1 },
	{ PC_UI_BLOCK_OTHER_UI, 1 }
};

/* enumを増やした際にポリシーの追加漏れを検出する。 */
typedef char pc_ui_policy_count[(sizeof(pc_ui_policies) / sizeof(pc_ui_policies[0]) == PC_UI_MAX) ? 1 : -1];

int pc_ui_is(const struct map_session_data *sd, enum pc_ui_type type)
{
	return sd && type >= PC_UI_NONE && type < PC_UI_MAX && sd->state.open_ui == type;
}

int pc_ui_can_open(const struct map_session_data *sd, enum pc_ui_type type)
{
	if(!sd || type <= PC_UI_NONE || type >= PC_UI_MAX)
		return 0;
	return sd->state.open_ui == PC_UI_NONE || sd->state.open_ui == type ||
	       ((type == PC_UI_RODEX || type == PC_UI_RODEX_WRITE) &&
	        (sd->state.open_ui == PC_UI_RODEX || sd->state.open_ui == PC_UI_RODEX_WRITE));
}

int pc_ui_begin(struct map_session_data *sd, enum pc_ui_type type)
{
	if(!pc_ui_can_open(sd, type))
		return 0;
	// 受信箱からの作成中は、作成終了後も受信箱を維持する。
	if(type != PC_UI_RODEX_WRITE || sd->state.open_ui != PC_UI_RODEX)
		sd->state.open_ui = type;
	return 1;
}

int pc_ui_end(struct map_session_data *sd, enum pc_ui_type type)
{
	if(type == PC_UI_NONE || !pc_ui_is(sd, type))
		return 0;
	if(type == PC_UI_BARTER || type == PC_UI_EXBARTER)
		sd->npc_shopid = 0;
	sd->state.open_ui = PC_UI_NONE;
	return 1;
}

int pc_ui_blocks(const struct map_session_data *sd, unsigned int mask)
{
	enum pc_ui_type type;

	if(!sd)
		return 1;
	type = sd->state.open_ui;
	if(type < PC_UI_NONE || type >= PC_UI_MAX)
		return 1;
	return (pc_ui_policies[type].blocks & mask) != 0;
}

void pc_ui_on_warp(struct map_session_data *sd)
{
	enum pc_ui_type type;

	if(!sd)
		return;
	type = sd->state.open_ui;
	if(type > PC_UI_NONE && type < PC_UI_MAX && pc_ui_policies[type].close_on_warp)
		pc_ui_end(sd, type);
}
