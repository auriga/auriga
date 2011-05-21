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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mmo.h"
#include "db.h"
#include "malloc.h"
#include "sqldbs.h"
#include "utils.h"

#include "petdb_sql.h"

static struct dbt *pet_db = NULL;

bool petdb_sql_init(void)
{
	pet_db = numdb_init();
	return true;
}

int petdb_sql_sync(void)
{
	// nothing to do
	return 0;
}

bool petdb_sql_delete(int pet_id)
{
	struct s_pet *p;

	sqldbs_query(&mysql_handle, "DELETE FROM `" PET_TABLE "` WHERE `pet_id`='%d'", pet_id);

	p = (struct s_pet *)numdb_search(pet_db,pet_id);
	if(p) {
		numdb_erase(pet_db,p->pet_id);
		aFree(p);
	} else {
		if(sqldbs_affected_rows(&mysql_handle) <= 0)
			return false;	// SQLから削除できないときだけfail
	}

	printf("pet_id: %d deleted\n",pet_id);

	return true;
}

const struct s_pet* petdb_sql_load(int pet_id)
{
	bool is_success;
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;
	struct s_pet *p = (struct s_pet *)numdb_search(pet_db,pet_id);

	if(p && p->pet_id == pet_id) {
		return p;
	}
	if(p == NULL) {
		p = (struct s_pet *)aMalloc(sizeof(struct s_pet));
		numdb_insert(pet_db,pet_id,p);
	}
	memset(p, 0, sizeof(struct s_pet));

	is_success = sqldbs_query(
		&mysql_handle,
		"SELECT `class`,`name`,`account_id`,`char_id`,`level`,`egg_id`,`equip`,"
		"`intimate`,`hungry`,`rename_flag`,`incubate` FROM `" PET_TABLE "` WHERE `pet_id`='%d'",
		pet_id
	);
	if(!is_success) {
		p->pet_id = -1;
		return NULL;
	}

	sql_res = sqldbs_store_result(&mysql_handle);
	if (sql_res!=NULL && sqldbs_num_rows(sql_res)>0) {
		sql_row = sqldbs_fetch(sql_res);

		p->pet_id      = pet_id;
		p->class_      = atoi(sql_row[0]);
		strncpy(p->name, sql_row[1], 24);
		p->name[23] = '\0';	// force \0 terminal
		p->account_id  = atoi(sql_row[2]);
		p->char_id     = atoi(sql_row[3]);
		p->level       = atoi(sql_row[4]);
		p->egg_id      = atoi(sql_row[5]);
		p->equip       = atoi(sql_row[6]);
		p->intimate    = atoi(sql_row[7]);
		p->hungry      = atoi(sql_row[8]);
		p->rename_flag = atoi(sql_row[9]);
		p->incubate    = atoi(sql_row[10]);
	} else {
		p->pet_id = -1;
		if( sql_res ) sqldbs_free_result(sql_res);
		return NULL;
	}
	if(p->hungry < 0)
		p->hungry = 0;
	else if(p->hungry > 100)
		p->hungry = 100;
	if(p->intimate < 0)
		p->intimate = 0;
	else if(p->intimate > 1000)
		p->intimate = 1000;

	sqldbs_free_result(sql_res);

	return p;
}

bool petdb_sql_save(struct s_pet* p2)
{
	char t_name[64];
	const struct s_pet *p1 = petdb_sql_load(p2->pet_id);

	if(p1 == NULL)
		return false;

	if(memcmp(p1,p2,sizeof(struct s_pet))) {
		sqldbs_query(
			&mysql_handle,
			"UPDATE `" PET_TABLE "` SET `class`='%d',`name`='%s',`account_id`='%d',`char_id`='%d',`level`='%d',`egg_id`='%d',"
			"`equip`='%d',`intimate`='%d',`hungry`='%d',`rename_flag`='%d',`incubate`='%d' WHERE `pet_id`='%d'",
			p2->class_, strecpy(t_name, p2->name), p2->account_id, p2->char_id, p2->level, p2->egg_id,
			p2->equip, p2->intimate, p2->hungry, p2->rename_flag, p2->incubate, p2->pet_id
		);
	}

	{
		struct s_pet *p3 = (struct s_pet *)numdb_search(pet_db,p2->pet_id);
		if(p3)
			memcpy(p3,p2,sizeof(struct s_pet));
	}
	return true;
}

bool petdb_sql_new(struct s_pet *p)
{
	// ペットIDを読み出す
	bool is_success;
	char t_name[64];

	is_success = sqldbs_query(
		&mysql_handle,
		"INSERT INTO `" PET_TABLE "` (`class`,`name`,`account_id`,`char_id`,`level`,`egg_id`,"
		"`equip`,`intimate`,`hungry`,`rename_flag`,`incubate`) VALUES ('%d', '%s', '%d',"
		"'%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d')",
		p->class_, strecpy(t_name, p->name), p->account_id, p->char_id, p->level, p->egg_id,
		p->equip, p->intimate, p->hungry, p->rename_flag, p->incubate
	);
	if(!is_success){
		p->pet_id = -1;
		return false;
	}

	p->pet_id = (int)sqldbs_insert_id(&mysql_handle);

	numdb_insert(pet_db,p->pet_id,p);
	return true;
}

static int petdb_sql_final_sub(void *key,void *data,va_list ap)
{
	struct s_pet *p = (struct s_pet *)data;

	aFree(p);

	return 0;
}

void petdb_sql_final(void)
{
	if(pet_db)
		numdb_final(pet_db,petdb_sql_final_sub);
}

int petdb_sql_config_read_sub(const char* w1,const char *w2)
{
	return 0;
}
