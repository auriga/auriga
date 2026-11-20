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

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "sqldbs.h"
#include "cashshopdb_sql.h"

static int cashshop_ready;

bool cashshopdb_sql_init(void) { cashshop_ready = 1; return true; }
void cashshopdb_sql_final(void) { cashshop_ready = 0; }
int cashshopdb_sql_sync(void) { return 0; }
int cashshopdb_sql_config_read(const char *key, const char *value) { return 0; }

bool cashshopdb_sql_load(int account, struct cashshop_account_count *rows, int count)
{
	char query[4096], **row;
	int i, len;
	if(!cashshop_ready || account <= 0 || !rows || count < 1 || count > CASHSHOP_ACCOUNT_MAX)
		return false;
	len = snprintf(query, sizeof(query), "SELECT `sale_id`,`purchased` FROM `" ACCOUNT_CASHSHOP_TABLE "` WHERE `account_id`=%d AND `sale_id` IN (", account);
	for(i = 0; i < count; i++) {
		if(rows[i].sale_id <= 0)
			return false;
		rows[i].purchased = 0;
		len += snprintf(query + len, sizeof(query) - len, "%s%d", i ? "," : "", rows[i].sale_id);
	}
	snprintf(query + len, sizeof(query) - len, ")");
	if(!sqldbs_query(&mysql_handle, "%s", query)) {
		cashshop_ready = 0;
		return false;
	}
	while((row = sqldbs_fetch(&mysql_handle)) != NULL) {
		int sale = atoi(row[0]);
		unsigned long used = strtoul(row[1], NULL, 10);
		if(used > INT_MAX) {
			cashshop_ready = 0;
			break;
		}
		for(i = 0; i < count; i++) {
			if(rows[i].sale_id == sale)
				rows[i].purchased = (unsigned int)used;
		}
	}
	sqldbs_free_result(&mysql_handle);
	return cashshop_ready != 0;
}

bool cashshopdb_sql_save(int account, const struct cashshop_account_count *rows, int count)
{
	int i, ok = 1;
	if(!cashshop_ready || account <= 0 || !rows || count < 1 || count > CASHSHOP_ACCOUNT_MAX)
		return false;
	for(i = 0; i < count; i++) {
		if(rows[i].sale_id <= 0 || rows[i].purchased > INT_MAX)
			return false;
	}
	if(!sqldbs_transaction_start(&mysql_handle)) {
		cashshop_ready = 0;
		return false;
	}
	for(i = 0; i < count; i++) {
		if(!rows[i].purchased)
			continue;
		/* ’x‚ê‚Ä“ž’…‚µ‚½•Û‘¶—v‹‚Åw“üÏ‚Ý”‚ðŠª‚«–ß‚³‚È‚¢B */
		if(!sqldbs_query(&mysql_handle,
			"INSERT INTO `" ACCOUNT_CASHSHOP_TABLE "` (`account_id`,`sale_id`,`purchased`) VALUES (%d,%d,%u) ON DUPLICATE KEY UPDATE `purchased`=GREATEST(`purchased`,VALUES(`purchased`))",
			account, rows[i].sale_id, rows[i].purchased)) {
			ok = 0;
			break;
		}
	}
	if(!sqldbs_transaction_end(&mysql_handle, ok != 0))
		ok = 0;
	if(!ok)
		cashshop_ready = 0;
	return ok != 0;
}
