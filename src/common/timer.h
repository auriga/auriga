/*
 * Copyright (C) 2002-2007  Auriga
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

#define TIMER_ONCE_AUTODEL 1
#define TIMER_INTERVAL 2
#define TIMER_REMOVE_HEAP 16

#define DIFF_TICK(a,b) ((int)((a)-(b)))

enum {
	TIMER_FREE_ID   = 0x01,
	TIMER_FREE_DATA = 0x02
};

// Struct declaration
struct TimerData {
	unsigned int tick;
	int (*func)(int,unsigned int,int,int);
	int id;
	int data;
	int interval;
	short type;
	unsigned short free_flag;
};

// Function prototype declaration

unsigned int gettick_nocache(void);
unsigned int gettick(void);

int add_timer_real(unsigned int,int (*)(int,unsigned int,int,int),int,int,unsigned short);
#define add_timer(tick,func,id,data)       add_timer_real(tick,func,id,data,0)
#define add_timer2(tick,func,id,data,flag) add_timer_real(tick,func,id,data,flag)
int add_timer_interval(unsigned int,int (*)(int,unsigned int,int,int),int,int,int);
int delete_timer(int,int (*)(int,unsigned int,int,int));

unsigned int addtick_timer(int tid,unsigned int tick);
struct TimerData *get_timer(int tid);

int do_timer(unsigned int tick);

int add_timer_func_list(int (*)(int,unsigned int,int,int),const char*);
void do_final_timer(void);
const char* search_timer_func_list(int (*)(int,unsigned int,int,int));

#endif	// _TIMER_H_
