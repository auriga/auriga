#ifndef _CHAT_H_
#define _CHAT_H_

#include "map.h"

void chat_createchat(struct map_session_data *sd, unsigned short limit, unsigned char pub, char* pass, char* title, int titlelen);
void chat_joinchat(struct map_session_data *sd, int chatid, char* pass);
int chat_leavechat(struct map_session_data *sd, unsigned char flag);
void chat_changechatowner(struct map_session_data *sd, char *nextownername);
void chat_changechatstatus(struct map_session_data *sd, unsigned short limit, unsigned char pub, char* pass, char* title, int titlelen);
void chat_kickchat(struct map_session_data *sd, char *kickusername);

int chat_createnpcchat(
	struct npc_data *nd,int limit,int pub,int trigger,char* title,int titlelen,const char *ev,
	int zeny,int lowlv,int highlv,unsigned int job,int upper);
int chat_deletenpcchat(struct npc_data *nd);
int chat_enableevent(struct chat_data *cd);
int chat_disableevent(struct chat_data *cd);
int chat_npckickall(struct chat_data *cd);

int do_final_chat(void);

#endif
