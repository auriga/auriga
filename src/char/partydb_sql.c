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

#ifndef TXT_ONLY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mmo.h"
#include "db.h"
#include "malloc.h"
#include "sqldbs.h"
#include "utils.h"

#include "partydb.h"
#include "int_party.h"

static struct dbt *party_db = NULL;

bool partydb_sql_init(void)
{
	party_db = numdb_init();
	return true;
}

int partydb_sql_sync(void)
{
	// nothing to do
	return 0;
}

const struct party* partydb_sql_load_str(char *str)
{
	int  id_num = -1;
	char buf[256];
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;

	sqldbs_query(&mysql_handle, "SELECT `party_id` FROM `" PARTY_TABLE "` WHERE `name` = '%s'", strecpy(buf,str));

	sql_res = sqldbs_store_result(&mysql_handle);
	if (sql_res) {
		sql_row = sqldbs_fetch(sql_res);
		if(sql_row) {
			id_num = atoi(sql_row[0]);
		}
		sqldbs_free_result(sql_res);
	}
	if(id_num >= 0) {
		return partydb_sql_load_num(id_num);
	}
	return NULL;
}

const struct party* partydb_sql_load_num(int party_id)
{
	int leader_id=0;
	bool is_success;
	struct party *p = (struct party *)numdb_search(party_db,party_id);
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;

	if(p && p->party_id == party_id) {
		return p;
	}
	if(p == NULL) {
		p = (struct party *)aMalloc(sizeof(struct party));
		numdb_insert(party_db,party_id,p);
	}
	memset(p, 0, sizeof(struct party));

	is_success = sqldbs_query(&mysql_handle, "SELECT `name`,`exp`,`item`,`leader_id` FROM `" PARTY_TABLE "` WHERE `party_id`='%d'", party_id);
	if(!is_success) {
		p->party_id = -1;
		return NULL;
	}

	sql_res = sqldbs_store_result(&mysql_handle);
	if (sql_res!=NULL && sqldbs_num_rows(sql_res)>0) {
		sql_row     = sqldbs_fetch(sql_res);
		p->party_id = party_id;
		strncpy(p->name, sql_row[0], 24);
		p->name[23] = '\0';	// force \0 terminal
		p->exp      = atoi(sql_row[1]);
		p->item     = atoi(sql_row[2]);
		leader_id   = atoi(sql_row[3]);
	} else {
		sqldbs_free_result(sql_res);
		p->party_id = -1;
		return NULL;
	}
	sqldbs_free_result(sql_res);

	// Load members
	is_success = sqldbs_query(&mysql_handle, "SELECT `account_id`,`char_id`,`name` FROM `" CHAR_TABLE "` WHERE `party_id`='%d'", party_id);
	if(!is_success) {
		p->party_id = -1;
		return NULL;
	}
	sql_res = sqldbs_store_result(&mysql_handle);
	if (sql_res) {
		int i;
		for(i=0;(sql_row = sqldbs_fetch(sql_res));i++){
			struct party_member *m = &p->member[i];
			m->account_id = atoi(sql_row[0]);
			m->char_id    = atoi(sql_row[1]);
			m->leader     = (m->account_id == leader_id) ? 1 : 0;
			strncpy(m->name,sql_row[2],24);
			m->name[23] = '\0';	// force \0 terminal
		}
	}
	sqldbs_free_result(sql_res);

	return p;
}

bool partydb_sql_save(struct party* p2)
{
	const struct party *p1 = partydb_sql_load_num(p2->party_id);
	char t_name[64];

	if(p1 == NULL) return 0;

	if(strcmp(p1->name,p2->name) || p1->exp != p2->exp || p1->item != p2->item) {
		sqldbs_query(
			&mysql_handle,
			"UPDATE `" PARTY_TABLE "` SET `name`='%s', `exp`='%d', `item`='%d' WHERE `party_id`='%d'",
			strecpy(t_name,p2->name),p2->exp,p2->item,p2->party_id
		);
	}

	{
		struct party *p3 = (struct party *)numdb_search(party_db,p2->party_id);
		if(p3)
			memcpy(p3,p2,sizeof(struct party));
	}
	return true;
}

bool partydb_sql_delete(int party_id)
{
	struct party *p = (struct party *)numdb_search(party_db,party_id);

	if(p) {
		numdb_erase(party_db,p->party_id);
		aFree(p);
	}

	sqldbs_query(&mysql_handle, "DELETE FROM `" PARTY_TABLE "` WHERE `party_id`='%d'", party_id);

	return true;
}

int partydb_sql_config_read_sub(const char *w1,const char *w2)
{
	return 0;
}

bool partydb_sql_new(struct party *p)
{
	int i = 0;
	bool is_success;
	int leader_id = -1;
	char t_name[64];
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;

	for(i = 0; i < MAX_PARTY; i++) {
		if(p->member[i].account_id > 0 && p->member[i].leader) {
			leader_id = p->member[i].account_id;
			break;
		}
	}
	if ( leader_id == -1 ) { return 0; }
	// パーティIDを読み出す
	is_success = sqldbs_query(&mysql_handle, "SELECT MAX(`party_id`) FROM `" PARTY_TABLE "`");
	if(!is_success)
		return false;

	sql_res = sqldbs_store_result(&mysql_handle);
	if(!sql_res)
		return false;

	sql_row = sqldbs_fetch(sql_res);
	if(sql_row[0]) {
		p->party_id = atoi(sql_row[0]) + 1;
	} else {
		p->party_id = 100;
	}
	sqldbs_free_result(sql_res);

	// DBに挿入
	sqldbs_query(
		&mysql_handle,
		"INSERT INTO `" PARTY_TABLE "` (`party_id`, `name`, `exp`, `item`, `leader_id`) "
		"VALUES ('%d','%s', '%d', '%d', '%d')",
		p->party_id, strecpy(t_name,p->name), p->exp, p->item,leader_id
	);

	numdb_insert(party_db,p->party_id,p);
	return true;
}

static int partydb_sql_final_sub(void *key,void *data,va_list ap)
{
	struct party *p = (struct party *)data;

	aFree(p);

	return 0;
}

void partydb_sql_final(void)
{
	numdb_final(party_db,partydb_sql_final_sub);
}

#endif
