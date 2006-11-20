#ifndef _GRAPH_H_
#define _GRAPH_H_

void do_init_graph(void);

// athenaの状態を調査するセンサーを追加する。
// string        : センサーの名称(Login Users など)
// inetrval      : センサーの値を所得する間隔(msec)
// callback_func : センサーの値を返す関数( unsigned int login_users(void); など) 

void graph_add_sensor(const char* string, int interval, double (*callback_func)(void));

#endif

