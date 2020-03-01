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
	// ダミープロトタイプ宣言
	bool status_dummy_init(void);
	int status_dummy_sync(void);
	bool status_dummy_delete(int char_id);
	struct scdata *status_dummy_load(int char_id);
	bool status_dummy_save(struct scdata *sc2);
	void status_dummy_final(void);
	int status_dummy_config_read_sub(const char *w1,const char *w2);

	// ダミーエイリアス
	#define statusdb_init   status_dummy_init
	#define statusdb_sync   status_dummy_sync
	#define statusdb_delete status_dummy_delete
	#define statusdb_load   status_dummy_load
	#define statusdb_save   status_dummy_save
	#define statusdb_final  status_dummy_final
	#define statusdb_config_read_sub status_dummy_config_read_sub
#elif defined TXT_ONLY
	#include "txt/statusdb_txt.h"
#else
	#include "sql/statusdb_sql.h"
#endif

#endif /* _INT_STATUS_H_ */
