#ifndef _INT_MERC_H_
#define _INT_MERC_H_

#ifdef TXT_ONLY

int  merc_txt_init(void);
int  merc_txt_sync(void);
int  merc_txt_delete(int merc_id);
const struct mmo_mercstatus* merc_txt_load(int merc_id);
int  merc_txt_save(struct mmo_mercstatus* p2);
int  merc_txt_new(struct mmo_mercstatus *p);
void merc_txt_final(void);
void merc_txt_config_read_sub(const char* w1,const char *w2);

#ifndef _INT_MERC_C_
	#define merc_init   merc_txt_init
	#define merc_sync   merc_txt_sync
	#define merc_delete merc_txt_delete
	#define merc_load   merc_txt_load
	#define merc_save   merc_txt_save
	#define merc_new    merc_txt_new
	#define merc_final  merc_txt_final
	#define merc_config_read_sub merc_txt_config_read_sub
#endif /* _INT_MERC_C_ */

#else /* TXT_ONLY */

int  merc_sql_init(void);
int  merc_sql_sync(void);
int  merc_sql_delete(int merc_id);
const struct mmo_mercstatus* merc_sql_load(int merc_id);
int  merc_sql_save(struct mmo_mercstatus* p2);
int  merc_sql_new(struct mmo_mercstatus *p2);
void merc_sql_final(void);
void merc_sql_config_read_sub(const char* w1,const char *w2);

#ifndef _INT_MERC_C_
	#define merc_init   merc_sql_init
	#define merc_sync   merc_sql_sync
	#define merc_delete merc_sql_delete
	#define merc_load   merc_sql_load
	#define merc_save   merc_sql_save
	#define merc_new    merc_sql_new
	#define merc_final  merc_sql_final
	#define merc_config_read_sub merc_sql_config_read_sub
#endif /* _INT_MERC_C_ */

#endif

int inter_merc_parse_frommap(int fd);

#endif
