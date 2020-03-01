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

// original : core.h 2003/03/14 11:55:25 Rev 1.4

#ifndef	_TIMER_H_
#define	_TIMER_H_

#define TIMER_ONCE_AUTODEL 0x01
#define TIMER_INTERVAL     0x02
#define TIMER_REMOVE_HEAP  0x10

#define DIFF_TICK(a,b) ((int)((a)-(b)))

// Struct declaration
struct TimerData {
	unsigned int tick;
	int (*func)(int,unsigned int,int,void*);
	int id;
	void *data;
	int interval;
	short type, free_flag;
};

// Function prototype declaration

unsigned int gettick_nocache(void);
unsigned int gettick(void);

int add_timer_real(unsigned int,int (*)(int,unsigned int,int,void*),int,void*,short);
#define add_timer(tick,func,id,data)  add_timer_real(tick,func,id,data,0)
#define add_timer2(tick,func,id,data) add_timer_real(tick,func,id,data,1)
int add_timer_interval(unsigned int,int (*)(int,unsigned int,int,void*),int,void*,int);
int delete_timer(int,int (*)(int,unsigned int,int,void*));

unsigned int addtick_timer(int tid,unsigned int tick);
struct TimerData *get_timer(int tid);

int do_timer(unsigned int tick);

int add_timer_func_list_real(int (*)(int,unsigned int,int,void*),const char*);
#define add_timer_func_list(x) add_timer_func_list_real(x, #x)

void do_final_timer(void);
const char* search_timer_func_list(int (*)(int,unsigned int,int,void*));

#endif	// _TIMER_H_
