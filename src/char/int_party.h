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

#ifndef _INT_PARTY_H_
#define _INT_PARTY_H_

int party_check_empty(const struct party *p);
int inter_party_parse_frommap(int fd);
void inter_party_leave(int party_id, int account_id, int char_id);
int party_config_read(const char *w1,const char* w2);

#ifdef TXT_ONLY
	#include "txt/partydb_txt.h"
#else
	#include "sql/partydb_sql.h"
#endif

#endif /* _INT_PARTY_H_ */
