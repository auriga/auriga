#ifndef _INTER_H_
#define _INTER_H_

int inter_init(const char *file);
int inter_sync(void);
int inter_parse_frommap(int fd);
int inter_mapif_init(int fd);

int inter_log(char *fmt,...);

void do_final_inter(void);

#endif
