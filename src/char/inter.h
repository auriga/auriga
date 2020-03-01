/*
 * Copyright (C) 2002-2020  Auriga
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

#ifndef _INTER_H_
#define _INTER_H_

struct accreg {
	int account_id,reg_num;
	struct global_reg reg[ACCOUNT_REG_NUM];
};

int inter_init(const char *file);
int inter_sync(void);
int inter_parse_frommap(int fd);
int inter_mapif_init(int fd);

void do_final_inter(void);

#ifdef TXT_ONLY
	#include "txt/accregdb_txt.h"
	#include "txt/interlog_txt.h"
#else
	#include "sql/accregdb_sql.h"
	#include "sql/interlog_sql.h"
#endif

#endif /* _INTER_H_ */
