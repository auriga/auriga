#ifndef _INT_GUILD_H_
#define _INT_GUILD_H_

#ifdef TXT_ONLY

int  guild_txt_init(void);
int  guild_txt_sync(void);
void guild_txt_delete(int guild_id);
const struct guild *guild_txt_load_num(int guild_id);
const struct guild* guild_txt_load_str(char *str);
void guild_txt_config_read_sub(const char* w1,const char *w2);
void guild_txt_final(void);

#ifndef _INT_GUILD_C_
	#define guild_init     guild_txt_init
	#define guild_sync     guild_txt_sync
	#define guild_final    guild_txt_final
	#define guild_load_num guild_txt_load_num
	#define guild_load_str guild_txt_load_str
	#define guild_delete   guild_txt_delete
	#define guild_config_read_sub guild_txt_config_read_sub
#endif

#else /* TXT_ONLY */


int guild_sql_init(void);
int guild_sql_sync(void);
const struct guild *guild_sql_load_num(int guild_id);
const struct guild* guild_sql_load_str(char *str);
void guild_sql_config_read_sub(const char* w1,const char *w2);
void guild_sql_final(void);

#ifndef _INT_GUILD_C_
	#define guild_init     guild_sql_init
	#define guild_sync     guild_sql_sync
	#define guild_final    guild_sql_final
	#define guild_load_num guild_sql_load_num
	#define guild_load_str guild_sql_load_str
	#define guild_delete   guild_sql_delete
	#define guild_config_read_sub guild_sql_config_read_sub
#endif

#endif

void guild_config_read(const char *w1,const char* w2);

int inter_guild_parse_frommap(int fd);
int inter_guild_mapif_init(int fd);
int inter_guild_leave(int guild_id,int account_id,int char_id);

#endif
