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

#ifndef _PC_UI_H_
#define _PC_UI_H_

/* クライアントへ送るUI番号とは別に、排他管理する画面だけを定義する。 */
enum pc_ui_type {
	PC_UI_NONE,
	PC_UI_REFINE,
	PC_UI_RODEX,
	PC_UI_RODEX_WRITE,
	PC_UI_BARTER,
	PC_UI_EXBARTER,
	PC_UI_MAX
};

enum pc_ui_block {
	PC_UI_BLOCK_MOVE     = 1 << 0,
	PC_UI_BLOCK_ACTION   = 1 << 1,
	PC_UI_BLOCK_SKILL    = 1 << 2,
	PC_UI_BLOCK_ITEM     = 1 << 3,
	PC_UI_BLOCK_INTERACT = 1 << 4,
	PC_UI_BLOCK_TRADE    = 1 << 5,
	PC_UI_BLOCK_OTHER_UI = 1 << 6
};

struct map_session_data;

int pc_ui_is(const struct map_session_data *sd, enum pc_ui_type type);
/* UI間の排他だけを判定する。PACKETVER・機能条件は呼び出し側で確認する。 */
int pc_ui_can_open(const struct map_session_data *sd, enum pc_ui_type type);
int pc_ui_begin(struct map_session_data *sd, enum pc_ui_type type);
int pc_ui_end(struct map_session_data *sd, enum pc_ui_type type);
int pc_ui_blocks(const struct map_session_data *sd, unsigned int mask);
void pc_ui_on_warp(struct map_session_data *sd);

#endif
