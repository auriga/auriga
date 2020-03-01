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

#ifndef _GRAPH_H_
#define _GRAPH_H_

void do_init_graph(void);

// aurigaの状態を調査するセンサーを追加する。
// string        : センサーの名称(Login Users など)
// inetrval      : センサーの値を取得する間隔(msec)
// callback_func : センサーの値を返す関数( unsigned int login_users(void); など)

void graph_add_sensor(const char* string, int interval, double (*callback_func)(void));

#endif

