// original : core.h 2003/03/14 11:55:25 Rev 1.4

#ifndef	_TIMER_H_
#define	_TIMER_H_

#define BASE_TICK 5

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
	int type;
	int interval;
	int heap_pos;
	unsigned short free_flag;
};

// Function prototype declaration

unsigned int gettick_nocache(void);
unsigned int gettick(void);

int add_timer_sub(unsigned int,int (*)(int,unsigned int,int,int),int,int,unsigned short);
#define add_timer(tick,func,id,data)       add_timer_sub(tick,func,id,data,0)
#define add_timer2(tick,func,id,data,flag) add_timer_sub(tick,func,id,data,flag)
int add_timer_interval(unsigned int,int (*)(int,unsigned int,int,int),int,int,int);
int delete_timer(int,int (*)(int,unsigned int,int,int));

int addtick_timer(int tid,unsigned int tick);
struct TimerData *get_timer(int tid);

int do_timer(unsigned int tick);

int add_timer_func_list(int (*)(int,unsigned int,int,int),char*);
void do_final_timer(void);
char* search_timer_func_list(int (*)(int,unsigned int,int,int));

#endif	// _TIMER_H_
