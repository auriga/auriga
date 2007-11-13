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

#ifndef _INT_HOM_H_
#define _INT_HOM_H_

#ifdef TXT_ONLY

int  homun_txt_init(void);
int  homun_txt_sync(void);
int  homun_txt_delete(int homun_id);
const struct mmo_homunstatus* homun_txt_load(int homun_id);
int  homun_txt_save(struct mmo_homunstatus* p2);
int  homun_txt_new(struct mmo_homunstatus *p);
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
int  homun_sql_new(struct mmo_homunstatus *p2);
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
