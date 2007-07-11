#ifndef _MAIL_H_
#define _MAIL_H_

int mail_setitem(struct map_session_data *sd,int index,int amount);
int mail_removeitem(struct map_session_data *sd);
int mail_checkmail(struct map_session_data *sd,char *name,char *title,char *body,int len);
int mail_sendmail(struct map_session_data *sd,struct mail_data *md);
int mail_getappend(int account_id,int zeny,struct item *item);

#endif
