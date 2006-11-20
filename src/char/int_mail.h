#ifndef _INT_MAIL_H_
#define _INT_MAIL_H_


int mapif_mail_res(const int fd,int char_id,int flag);
int inter_mail_parse_frommap(int fd);

int mail_init(void);
int mail_sync(void);
void mail_final(void);

#endif
