#ifndef _PARTY_H_
#define _PARTY_H_

#include <stdarg.h>
#include "mmo.h"

struct party;
struct map_session_data;
struct mob_data;
struct block_list;

void do_init_party(void);
void do_final_party(void);
struct party *party_search(int party_id);
struct party* party_searchname(char *str);

void party_create(struct map_session_data *sd, char *name);
void party_created(int account_id, unsigned char fail, int party_id, char *name);
void party_request_info(int party_id);
void party_invite(struct map_session_data *sd, int account_id);
void party_recv_noinfo(int party_id);
void party_recv_info(struct party *sp);
void party_reply_invite(struct map_session_data *sd, int account_id, int flag);
void party_member_added(int party_id, int account_id, unsigned char flag, const char* name);
void party_removemember(struct map_session_data *sd, int account_id, char *name);
void party_leave(struct map_session_data *sd);
void party_member_leaved(int party_id, int account_id, char *name);
void party_broken(int party_id);
void party_changeoption(struct map_session_data *sd, unsigned short exp, unsigned short item);
void party_optionchanged(int party_id, int account_id, int exp, int item, int flag);
void party_recv_movemap(int party_id, int account_id, char *map, int online, int lv, const char* name);

void party_send_movemap(struct map_session_data *sd);
void party_send_logout(struct map_session_data *sd);

int party_check_same_map_member_count(struct map_session_data *sd);

void party_send_message(struct map_session_data *sd, char *mes, int len);
void party_recv_message(int party_id, int account_id, char *mes, int len);

int party_send_hp_check(struct block_list *bl,va_list ap);

void party_exp_share(struct party *p, struct mob_data *md, atn_bignumber base_exp, atn_bignumber job_exp);

void party_foreachsamemap(int (*func)(struct block_list *,va_list),struct map_session_data *sd,int type,...);

#endif
