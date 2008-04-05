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

#ifndef _INT_PARTY_H_
#define _INT_PARTY_H_

int inter_party_parse_frommap(int fd);
void inter_party_leave(int party_id, int account_id, int char_id);
void party_config_read(const char *w1,const char* w2);

#ifdef TXT_ONLY

int  party_txt_init(void);
int  party_txt_sync(void);
const struct party* party_txt_load_str(char *str);
const struct party* party_txt_load_num(int party_id);
int  party_txt_save(struct party* p2);
int  party_txt_delete(int party_id);
int  party_txt_config_read_sub(const char *w1,const char *w2);
void party_txt_final(void);

#ifndef _INT_PARTY_C_
	#define party_init     party_txt_init
	#define party_sync     party_txt_sync
	#define party_save     party_txt_save
	#define party_final    party_txt_final
	#define party_delete   party_txt_delete
	#define party_load_str party_txt_load_str
	#define party_load_num party_txt_load_num
	#define party_config_read_sub party_txt_config_read_sub
#endif

#else /* TXT_ONLY */

int  party_sql_init(void);
int  party_sql_sync(void);
const struct party* party_sql_load_str(char *str);
const struct party* party_sql_load_num(int party_id);
int  party_sql_save(struct party* p2);
int  party_sql_delete(int party_id);
int  party_sql_config_read_sub(const char *w1,const char *w2);
void party_sql_final(void);

#ifndef _INT_PARTY_C_
	#define party_init     party_sql_init
	#define party_sync     party_sql_sync
	#define party_save     party_sql_save
	#define party_final    party_sql_final
	#define party_delete   party_sql_delete
	#define party_load_str party_sql_load_str
	#define party_load_num party_sql_load_num
	#define party_config_read_sub party_sql_config_read_sub
#endif

#endif /* TXT_ONLY */

#endif
