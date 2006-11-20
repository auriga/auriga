#ifndef _INT_STORAGE_H_
#define _INT_STORAGE_H_

#ifdef TXT_ONLY
const struct storage* storage_txt_load(int account_id);
int  storage_txt_save(struct storage *s2);
int  storage_txt_init(void);
int  storage_txt_sync(void);
int  storage_txt_delete(int account_id);
void storage_txt_final(void);

const struct guild_storage *gstorage_txt_load(int guild_id);
int  gstorage_txt_save(struct guild_storage *gs2);
int  gstorage_txt_sync(void);
int  gstorage_txt_delete(int guild_id);
void gstorage_txt_final(void);

void storage_txt_config_read_sub(const char* w1,const char* w2);

#ifndef _INT_STORAGE_C_
	#define storage_init   storage_txt_init
	#define storage_load   storage_txt_load
	#define storage_save   storage_txt_save
	#define storage_sync   storage_txt_sync
	#define storage_delete storage_txt_delete
	#define storage_final  storage_txt_final

	#define gstorage_load   gstorage_txt_load
	#define gstorage_save   gstorage_txt_save
	#define gstorage_sync   gstorage_txt_sync
	#define gstorage_delete gstorage_txt_delete
	#define gstorage_final  gstorage_txt_final
	#define storage_config_read_sub storage_txt_config_read_sub
#endif /* _INT_STORAGE_C_ */

#else /* TXT_ONLY */
	extern char storage_db_[256];
	extern char guild_storage_db_[256];
	const struct storage* storage_sql_load(int account_id);
	int  storage_sql_save(struct storage *s2);
	int  storage_sql_init(void);
	int  storage_sql_sync(void);
	int  storage_sql_delete(int account_id);
	void storage_sql_final(void);

	const struct guild_storage *gstorage_sql_load(int guild_id);
	int  gstorage_sql_save(struct guild_storage *gs2);
	int  gstorage_sql_sync(void);
	int  gstorage_sql_delete(int guild_id);
	void gstorage_sql_final(void);

	void storage_sql_config_read_sub(const char* w1,const char* w2);

#ifndef _INT_STORAGE_C_
	#define storage_init   storage_sql_init
	#define storage_load   storage_sql_load
	#define storage_save   storage_sql_save
	#define storage_sync   storage_sql_sync
	#define storage_delete storage_sql_delete
	#define storage_final  storage_sql_final

	#define gstorage_load   gstorage_sql_load
	#define gstorage_save   gstorage_sql_save
	#define gstorage_sync   gstorage_sql_sync
	#define gstorage_delete gstorage_sql_delete
	#define gstorage_final  gstorage_sql_final
	#define storage_config_read_sub storage_sql_config_read_sub
#endif /* _INT_STORAGE_C_ */

#endif /* TXT_ONLY */

int  inter_storage_parse_frommap(int fd);

#endif /* _INT_STORAGE_H_ */
