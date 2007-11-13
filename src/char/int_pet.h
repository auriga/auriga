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

#ifndef _INT_PET_H_
#define _INT_PET_H_

#ifdef TXT_ONLY

int  pet_txt_init(void);
int  pet_txt_sync(void);
int  pet_txt_delete(int pet_id);
const struct s_pet* pet_txt_load(int pet_id);
int  pet_txt_save(struct s_pet* p2);
int  pet_txt_new(struct s_pet *p);
void pet_txt_final(void);
void pet_txt_config_read_sub(const char* w1,const char *w2);

#ifndef _INT_PET_C_
	#define pet_init   pet_txt_init
	#define pet_sync   pet_txt_sync
	#define pet_delete pet_txt_delete
	#define pet_load   pet_txt_load
	#define pet_save   pet_txt_save
	#define pet_new    pet_txt_new
	#define pet_final  pet_txt_final
	#define pet_config_read_sub pet_txt_config_read_sub
#endif /* _INT_PET_C_ */

#else /* TXT_ONLY */

int  pet_sql_init(void);
int  pet_sql_sync(void);
int  pet_sql_delete(int pet_id);
const struct s_pet* pet_sql_load(int pet_id);
int  pet_sql_save(struct s_pet* p2);
int  pet_sql_new(struct s_pet *p);
void pet_sql_final(void);
void pet_sql_config_read_sub(const char* w1,const char *w2);

#ifndef _INT_PET_C_
	#define pet_init   pet_sql_init
	#define pet_sync   pet_sql_sync
	#define pet_delete pet_sql_delete
	#define pet_load   pet_sql_load
	#define pet_save   pet_sql_save
	#define pet_new    pet_sql_new
	#define pet_final  pet_sql_final
	#define pet_config_read_sub pet_sql_config_read_sub
#endif /* _INT_PET_C_ */

#endif

int inter_pet_parse_frommap(int fd);

#endif
