#ifndef _NPC_H_
#define _NPC_H_

#define WARP_CLASS 45
#define WARP_DEBUG_CLASS 722
#define INVISIBLE_CLASS 32767

int npc_event_dequeue(struct map_session_data *sd);
int npc_event(struct map_session_data *sd,const char *npcname);
int npc_touch_areanpc(struct map_session_data *,int,int,int);
void npc_click(struct map_session_data *sd, int id);
void npc_scriptcont(struct map_session_data *sd, int id);
void npc_buysellsel(struct map_session_data *sd, int id, unsigned char type);
int npc_buylist(struct map_session_data *,int,unsigned short *);
int npc_selllist(struct map_session_data *,int,unsigned short *);
int npc_set_mapflag(int m,char *w3,char *w4);
int npc_set_mapflag_sub(int m,char *str,short flag);
int npc_globalmessage(const char *name,char *mes);

int npc_enable(const char *name,int flag);
struct npc_data* npc_name2id(const char *name);

int npc_get_new_npc_id(void);

void npc_addsrcfile(const char *);
void npc_delsrcfile(const char *);
int do_final_npc(void);
int do_init_npc(void);
int npc_event_do_oninit(void);

int npc_event_doall(const char *name);
int npc_event_doall_id(const char *name,int rid,int m);
int npc_event_do(const char *name);

int npc_timerevent_start(struct npc_data *nd);
int npc_timerevent_stop(struct npc_data *nd);
int npc_gettimerevent_tick(struct npc_data *nd);
int npc_settimerevent_tick(struct npc_data *nd,int newtimer);

#endif
