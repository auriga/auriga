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

#ifndef _INT_MAIL_H_
#define _INT_MAIL_H_

int mapif_mail_res(const int fd,int char_id,int flag);
int inter_mail_parse_frommap(int fd);

#ifdef TXT_ONLY

int mail_txt_save_mail(int char_id,int i,int store,struct mail_data md[MAIL_STORE_MAX]);
int mail_txt_read_mail(int char_id,const struct mail *m,struct mail_data md[MAIL_STORE_MAX]);
int mail_txt_init(void);
int mail_txt_sync(void);
int mail_txt_delete(int char_id);
const struct mail* mail_txt_load(int char_id);
int mail_txt_save(struct mail* m2);
void mail_txt_final(void);
void mail_txt_config_read_sub(const char *w1,const char *w2);

#ifndef _INT_MAIL_C_
	#define mail_save_mail       mail_txt_save_mail
	#define mail_read_mail       mail_txt_read_mail
	#define mail_init            mail_txt_init
	#define mail_sync            mail_txt_sync
	#define mail_delete          mail_txt_delete
	#define mail_load            mail_txt_load
	#define mail_save            mail_txt_save
	#define mail_final           mail_txt_final
	#define mail_config_read_sub mail_txt_config_read_sub
#endif /* _INT_MAIL_C_ */

#else /* TXT_ONLY */

int mail_sql_save_mail(int char_id,int i,int store,struct mail_data md[MAIL_STORE_MAX]);
int mail_sql_read_mail(int char_id,const struct mail *m,struct mail_data md[MAIL_STORE_MAX]);
int mail_sql_init(void);
int mail_sql_sync(void);
int mail_sql_delete(int char_id);
const struct mail* mail_sql_load(int char_id);
int mail_sql_save(struct mail* m2);
void mail_sql_final(void);
void mail_sql_config_read_sub(const char *w1,const char *w2);

#ifndef _INT_MAIL_C_
	#define mail_save_mail       mail_sql_save_mail
	#define mail_read_mail       mail_sql_read_mail
	#define mail_init            mail_sql_init
	#define mail_sync            mail_sql_sync
	#define mail_delete          mail_sql_delete
	#define mail_load            mail_sql_load
	#define mail_save            mail_sql_save
	#define mail_final           mail_sql_final
	#define mail_config_read_sub mail_sql_config_read_sub
#endif /* _INT_MAIL_C_ */

#endif /* TXT_ONLY */

#endif /* _INT_MAIL_H_ */
