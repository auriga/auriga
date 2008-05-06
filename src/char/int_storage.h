/*
 * Copyright (C) 2002-2007  Auriga
 *
 * This file is part of Auriga.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

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
int  gstorage_txt_save(struct guild_storage *gs2, int easy);
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
	const struct storage* storage_sql_load(int account_id);
	int  storage_sql_save(struct storage *s2);
	int  storage_sql_init(void);
	int  storage_sql_sync(void);
	int  storage_sql_delete(int account_id);
	void storage_sql_final(void);

	const struct guild_storage *gstorage_sql_load(int guild_id);
	int  gstorage_sql_save(struct guild_storage *gs2, int easy);
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

int inter_storage_parse_frommap(int fd);
int inter_storage_init(void);

#endif /* _INT_STORAGE_H_ */
