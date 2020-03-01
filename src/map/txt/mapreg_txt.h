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

#ifndef _MAPREG_TXT_H_
#define _MAPREG_TXT_H_

#include "utils.h"

// プロトタイプ宣言
int mapreg_txt_getreg(int num);
bool mapreg_txt_setreg(int num,int val,int eternal);
char* mapreg_txt_getregstr(int num);
bool mapreg_txt_setregstr(int num,const char *str,int eternal);
int mapreg_txt_autosave(void);
bool mapreg_txt_init(void);
int mapreg_txt_final(void);
int mapreg_txt_config_read_sub(const char *w1,const char *w2);

// エイリアス
#define mapreg_getreg          mapreg_txt_getreg
#define mapreg_setreg          mapreg_txt_setreg
#define mapreg_getregstr       mapreg_txt_getregstr
#define mapreg_setregstr       mapreg_txt_setregstr
#define mapreg_autosave        mapreg_txt_autosave
#define mapreg_init            mapreg_txt_init
#define mapreg_final           mapreg_txt_final
#define mapreg_config_read_sub mapreg_txt_config_read_sub

#endif	/* _MAPREG_TXT_H_ */
