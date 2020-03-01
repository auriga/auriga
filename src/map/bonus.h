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

#ifndef _BONUS_H_
#define _BONUS_H_

#include "map.h"

// 拡張オートスペル
enum {
	EAS_SHORT       = 0x00000001,	// 近距離物理
	EAS_LONG        = 0x00000002,	// 遠距離物理
	EAS_WEAPON      = 0x00000003,	// 物理
	EAS_MAGIC       = 0x00000004,	// 魔法
	EAS_MISC        = 0x00000008,	// misc（罠・鷹・火炎瓶等）
	EAS_TARGET      = 0x00000010,	// 自分に使う
	EAS_SELF        = 0x00000020,	// 自分に使う
	EAS_TARGET_RAND = 0x00000040,	// 自分か攻撃対象に使う
	//EAS_TARGET    = 0x00000080,	// 自分か攻撃対象に使う
	EAS_FLUCT       = 0x00000100,	// 旧AS用 1～3のあれ
	EAS_RANDOM      = 0x00000200,	// 1～指定までランダム
	EAS_USEMAX      = 0x00000400,	// MAXレベルがあればそれを
	EAS_USEBETTER   = 0x00000800,	// 指定以上のものがあればそれを(MAXじゃなくても可能)
	EAS_NOSP        = 0x00001000,	// SP0
	EAS_SPCOST1     = 0x00002000,	// SP2/3
	EAS_SPCOST2     = 0x00004000,	// SP1/2
	EAS_SPCOST3     = 0x00008000,	// SP1.5倍
	EAS_ATTACK      = 0x00010000,	// 攻撃
	EAS_REVENGE     = 0x00020000,	// 反撃
	EAS_NORMAL      = 0x00040000,	// 通常攻撃
	EAS_SKILL       = 0x00080000,	// スキル
	EAS_CONDITION   = 0x00100000,	// 使用条件
};

// カード効果のオートスペル
int bonus_autospell_start(struct block_list *src,struct block_list *bl,unsigned int mode,unsigned int tick,int flag);
int bonus_autospellskill_start(struct block_list *src,struct block_list *bl,int skillid,unsigned int tick,int flag);

int bonus_activeitem_start(struct map_session_data* sd,unsigned int mode,unsigned int tick);
int bonus_activeitemskill_start(struct map_session_data* sd,int skillid,unsigned int tick);

int bonus_param1(struct map_session_data *sd,int type,int val);
int bonus_param2(struct map_session_data *sd,int type,int type2,int val);
int bonus_param3(struct map_session_data *sd,int type,int type2,int type3,int val);
int bonus_param4(struct map_session_data *sd,int type,int type2,int type3,int type4,unsigned int val);
int bonus_randopt(struct map_session_data *sd,int id,int val);

int do_final_bonus(void);
int do_init_bonus(void);

#endif
