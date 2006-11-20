#ifndef _MAIL_H_
#define _MAIL_H_

int mail_setitem(struct map_session_data *sd,int index,int amount);
int mail_removeitem(struct map_session_data *sd);
int mail_checkappend(struct map_session_data *sd,struct mail_data *md);
time_t mail_calctimes(void);

#endif

