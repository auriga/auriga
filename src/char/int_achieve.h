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

#ifndef _INT_ACHIEVE_H_
#define _INT_ACHIEVE_H_

struct achieve {
	int account_id;
	int char_id;
	short count;
	struct {
		int nameid;
		int count[MAX_ACHIEVE_CONTENT];
		unsigned int comp_date;
		char reward;
	} data[MAX_ACHIEVELIST];
};

int inter_achieve_parse_frommap(int fd);

#ifdef TXT_ONLY
	#include "txt/achievedb_txt.h"
#else
	#include "sql/achievedb_sql.h"
#endif

#endif /* _INT_ACHIEVE_H_ */
