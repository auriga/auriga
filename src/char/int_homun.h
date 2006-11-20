#ifndef _INT_HOM_H_
#define _INT_HOM_H_

#ifdef TXT_ONLY

int  homun_txt_init(void);
int  homun_txt_sync(void);
int  homun_txt_delete(int homun_id);
const struct mmo_homunstatus* homun_txt_load(int homun_id);
int  homun_txt_save(struct mmo_homunstatus* p2);
int  homun_txt_new(struct mmo_homunstatus *p2,int account_id,int char_id);
void homun_txt_final(void);
void homun_txt_config_read_sub(const char* w1,const char *w2);

#ifndef _INT_HOM_C_
	#define homun_init   homun_txt_init
	#define homun_sync   homun_txt_sync
	#define homun_delete homun_txt_delete
	#define homun_load   homun_txt_load
	#define homun_save   homun_txt_save
	#define homun_new    homun_txt_new
	#define homun_final  homun_txt_final
	#define homun_config_read_sub homun_txt_config_read_sub
#endif /* _INT_HOM_C_ */

#else /* TXT_ONLY */

int  homun_sql_init(void);
int  homun_sql_sync(void);
int  homun_sql_delete(int homun_id);
const struct mmo_homunstatus* homun_sql_load(int homun_id);
int  homun_sql_save(struct mmo_homunstatus* p2);
int  homun_sql_new(struct mmo_homunstatus *p2,int account_id,int char_id);
void homun_sql_final(void);
void homun_sql_config_read_sub(const char* w1,const char *w2);

#ifndef _INT_HOM_C_
	#define homun_init   homun_sql_init
	#define homun_sync   homun_sql_sync
	#define homun_delete homun_sql_delete
	#define homun_load   homun_sql_load
	#define homun_save   homun_sql_save
	#define homun_new    homun_sql_new
	#define homun_final  homun_sql_final
	#define homun_config_read_sub homun_sql_config_read_sub
#endif /* _INT_HOM_C_ */

#endif

int inter_hom_parse_frommap(int fd);

#endif
