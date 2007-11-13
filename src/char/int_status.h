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

#ifndef _INT_STATUS_H_
#define _INT_STATUS_H_

struct scdata {
	int account_id;
	int char_id;
	short count;
	struct {
		short type;
		int val1,val2,val3,val4,tick;
	} data[MAX_STATUSCHANGE];
};

int inter_status_parse_frommap(int fd);

#ifdef NO_SCDATA_SAVING

// ダミー関数に置き換え
int status_dummy_init(void);
int status_dummy_sync(void);
int status_dummy_delete(int char_id);
struct scdata *status_dummy_load(int char_id);
int status_dummy_save(struct scdata *sc2);
void status_dummy_final(void);
void status_dummy_config_read_sub(const char *w1,const char *w2);

	#define status_init   status_dummy_init
	#define status_sync   status_dummy_sync
	#define status_delete status_dummy_delete
	#define status_load   status_dummy_load
	#define status_save   status_dummy_save
	#define status_final  status_dummy_final
	#define status_config_read_sub status_dummy_config_read_sub

#else /* NO_SCDATA_SAVING */

#ifdef TXT_ONLY

int  status_txt_init(void);
int  status_txt_sync(void);
int  status_txt_delete(int char_id);
struct scdata *status_txt_load(int char_id);
int  status_txt_save(struct scdata *sc2);
void status_txt_final(void);
void status_txt_config_read_sub(const char *w1,const char *w2);

#ifndef _INT_STATUS_C_
	#define status_init   status_txt_init
	#define status_sync   status_txt_sync
	#define status_delete status_txt_delete
	#define status_load   status_txt_load
	#define status_save   status_txt_save
	#define status_final  status_txt_final
	#define status_config_read_sub status_txt_config_read_sub
#endif /* _INT_STATUS_C_ */

#else /* TXT_ONLY */

int  status_sql_init(void);
int  status_sql_sync(void);
int  status_sql_delete(int char_id);
struct scdata *status_sql_load(int char_id);
int  status_sql_save(struct scdata *sc2);
void status_sql_final(void);
void status_sql_config_read_sub(const char *w1,const char *w2);

#ifndef _INT_STATUS_C_
	#define status_init   status_sql_init
	#define status_sync   status_sql_sync
	#define status_delete status_sql_delete
	#define status_load   status_sql_load
	#define status_save   status_sql_save
	#define status_final  status_sql_final
	#define status_config_read_sub status_sql_config_read_sub
#endif /* _INT_STATUS_C_ */

#endif /* TXT_ONLY */

#endif /* NO_SCDATA_SAVING */

#endif /* _INT_STATUS_H_ */
