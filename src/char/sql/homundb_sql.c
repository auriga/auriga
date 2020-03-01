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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "db.h"
#include "malloc.h"
#include "sqldbs.h"
#include "utils.h"
#include "nullpo.h"

#include "homundb_sql.h"

static struct dbt *homun_db = NULL;

/*==========================================
 * 設定ファイルの読込
 *------------------------------------------
 */
int homundb_sql_config_read_sub(const char* w1,const char *w2)
{
	return 0;
}

/*==========================================
 * 同期
 *------------------------------------------
 */
int homundb_sql_sync(void)
{
	// nothing to do
	return 0;
}

/*==========================================
 * ホム削除
 *------------------------------------------
 */
bool homundb_sql_delete(int homun_id)
{
	bool result = false;

	if( sqldbs_transaction_start(&mysql_handle) == false )
		return result;

	// try
	do
	{
		// delete homun
		if( sqldbs_query(&mysql_handle, "DELETE FROM `" HOMUN_TABLE "` WHERE `homun_id`='%d'", homun_id) == false )
			break;

		// delete homun skill
		if( sqldbs_query(&mysql_handle, "DELETE FROM `" HOMUN_SKILL_TABLE "` WHERE `homun_id`='%d'", homun_id) == false )
			break;

		// success
		result = true;

		{
			// cache delete
			struct mmo_homunstatus *p = (struct mmo_homunstatus *)numdb_erase(homun_db, homun_id);
			if(p) {
				aFree(p);
			}
		}
	} while(0);

	sqldbs_transaction_end(&mysql_handle, result);

	return result;
}

/*==========================================
 * ホムIDからホムデータのロード
 *------------------------------------------
 */
const struct mmo_homunstatus* homundb_sql_load(int homun_id)
{
	int i;
	char **sql_row;
	bool result = false;
	struct mmo_homunstatus *p = (struct mmo_homunstatus *)numdb_search(homun_db, homun_id);

	if(p && p->homun_id == homun_id) {
		return p;
	}
	if(p == NULL) {
		p = (struct mmo_homunstatus *)aMalloc(sizeof(struct mmo_homunstatus));
		numdb_insert(homun_db, homun_id, p);
	}
	memset(p, 0, sizeof(struct mmo_homunstatus));

	result = sqldbs_query(&mysql_handle,
		"SELECT `class`,`name`,`account_id`,`char_id`,`base_level`,`base_exp`,"
		"`max_hp`,`hp`,`max_sp`,`sp`,`str`,`agi`,`vit`,`int`,`dex`,`luk`,"
		"`f_str`,`f_agi`,`f_vit`,`f_int`,`f_dex`,`f_luk`,"
		"`status_point`,`skill_point`,`equip`,`intimate`,`hungry`,`rename_flag`,`incubate` "
		"FROM `" HOMUN_TABLE "` WHERE `homun_id`='%d'",
		homun_id
	);
	if(result == false) {
		p->homun_id = -1;
		return NULL;
	}

	if((sql_row = sqldbs_fetch(&mysql_handle)) != NULL) {
		p->homun_id     = homun_id;
		p->class_       = atoi(sql_row[0]);
		strncpy(p->name, sql_row[1], 24);
		p->name[23] = '\0';	// force \0 terminal
		p->account_id   = atoi(sql_row[2]);
		p->char_id      = atoi(sql_row[3]);
		p->base_level   = atoi(sql_row[4]);
		p->base_exp     = atoi(sql_row[5]);
		p->max_hp       = atoi(sql_row[6]);
		p->hp           = atoi(sql_row[7]);
		p->max_sp       = atoi(sql_row[8]);
		p->sp           = atoi(sql_row[9]);
		p->str          = atoi(sql_row[10]);
		p->agi          = atoi(sql_row[11]);
		p->vit          = atoi(sql_row[12]);
		p->int_         = atoi(sql_row[13]);
		p->dex          = atoi(sql_row[14]);
		p->luk          = atoi(sql_row[15]);
		p->f_str        = atoi(sql_row[16]);
		p->f_agi        = atoi(sql_row[17]);
		p->f_vit        = atoi(sql_row[18]);
		p->f_int        = atoi(sql_row[19]);
		p->f_dex        = atoi(sql_row[20]);
		p->f_luk        = atoi(sql_row[21]);
		p->status_point = atoi(sql_row[22]);
		p->skill_point  = atoi(sql_row[23]);
		p->equip        = atoi(sql_row[24]);
		p->intimate     = atoi(sql_row[25]);
		p->hungry       = atoi(sql_row[26]);
		p->rename_flag  = atoi(sql_row[27]);
		p->incubate     = atoi(sql_row[28]);
	} else {
		p->homun_id = -1;
		sqldbs_free_result(&mysql_handle);
		return NULL;
	}
	sqldbs_free_result(&mysql_handle);

	result = sqldbs_query(&mysql_handle, "SELECT `id`,`lv` FROM `" HOMUN_SKILL_TABLE "` WHERE `homun_id`='%d'", homun_id);
	if(result == false) {
		p->homun_id = -1;
		return NULL;
	}

	for(i = 0; (sql_row = sqldbs_fetch(&mysql_handle)) && i < MAX_HOMSKILL; i++) {
		int id = atoi(sql_row[0]);
		if(id < HOM_SKILLID || id >= MAX_HOM_SKILLID) {
			// DB操作して変なスキルを覚えさせられる可能性があるのでチェック
			printf("homundb_sql_load: invaild skill id: %d\n", id);
		} else {
			p->skill[id-HOM_SKILLID].id = id;
			p->skill[id-HOM_SKILLID].lv = atoi(sql_row[1]);
		}
	}
	sqldbs_free_result(&mysql_handle);

	p->option = 0;
	if(p->hungry < 0)
		p->hungry = 0;
	else if(p->hungry > 100)
		p->hungry = 100;
	if(p->intimate < 0)
		p->intimate = 0;
	else if(p->intimate > 100000)
		p->intimate = 100000;

	return p;
}

#define UPDATE_NUM(val,sql) \
	if(p1->val != p2->val) {\
		p += sprintf(p,"%c`"sql"` = '%d'",sep,p2->val); sep = ',';\
	}
#define UPDATE_STR(val,sql) \
	if(strcmp(p1->val,p2->val)) {\
		p += sprintf(p,"%c`"sql"` = '%s'",sep,strecpy(buf,p2->val)); sep = ',';\
	}

/*==========================================
 * セーブ
 *------------------------------------------
 */
bool homundb_sql_save(struct mmo_homunstatus *p2)
{
	const struct mmo_homunstatus *p1;
	char buf[64], tmp_sql[65536];
	char sep = ' ';
	char *p = tmp_sql;
	bool result = false;

	nullpo_retr(false, p2);

	p1 = homundb_sql_load(p2->homun_id);
	if(p1 == NULL)
		return 0;

	strcpy(p, "UPDATE `" HOMUN_TABLE "` SET");
	p += strlen(p);

	UPDATE_NUM(class_      ,"class");
	UPDATE_STR(name        ,"name");
	UPDATE_NUM(account_id  ,"account_id");
	UPDATE_NUM(char_id     ,"char_id");
	UPDATE_NUM(base_level  ,"base_level");
	UPDATE_NUM(base_exp    ,"base_exp");
	UPDATE_NUM(max_hp      ,"max_hp");
	UPDATE_NUM(hp          ,"hp");
	UPDATE_NUM(max_sp      ,"max_sp");
	UPDATE_NUM(sp          ,"sp");
	UPDATE_NUM(str         ,"str");
	UPDATE_NUM(agi         ,"agi");
	UPDATE_NUM(vit         ,"vit");
	UPDATE_NUM(int_        ,"int");
	UPDATE_NUM(dex         ,"dex");
	UPDATE_NUM(luk         ,"luk");
	UPDATE_NUM(f_str       ,"f_str");
	UPDATE_NUM(f_agi       ,"f_agi");
	UPDATE_NUM(f_vit       ,"f_vit");
	UPDATE_NUM(f_int       ,"f_int");
	UPDATE_NUM(f_dex       ,"f_dex");
	UPDATE_NUM(f_luk       ,"f_luk");
	UPDATE_NUM(status_point,"status_point");
	UPDATE_NUM(skill_point ,"skill_point");
	UPDATE_NUM(equip       ,"equip");
	UPDATE_NUM(intimate    ,"intimate");
	UPDATE_NUM(hungry      ,"hungry");
	UPDATE_NUM(rename_flag ,"rename_flag");
	UPDATE_NUM(incubate    ,"incubate");

	if( sqldbs_transaction_start(&mysql_handle) == false )
		return false;

	// try
	do {
		if(sep == ',') {
			sprintf(p, " WHERE `homun_id` = '%d'", p2->homun_id);
			if( sqldbs_simplequery(&mysql_handle, tmp_sql) == false )
				break;
		}

		if(memcmp(p1->skill, p2->skill, sizeof(p1->skill)) ) {
			int i;

			if( sqldbs_query(&mysql_handle, "DELETE FROM `" HOMUN_SKILL_TABLE "` WHERE `homun_id`='%d'", p2->homun_id) == false )
				break;

			for(i = 0; i < MAX_HOMSKILL; i++) {
				if(p2->skill[i].id && p2->skill[i].flag != 1) {
					int lv = (p2->skill[i].flag == 0)? p2->skill[i].lv: p2->skill[i].flag - 2;
					if( sqldbs_query(&mysql_handle,
						"INSERT INTO `" HOMUN_SKILL_TABLE "` (`homun_id`,`id`,`lv`) VALUES ('%d','%d','%d')",
						p2->homun_id, p2->skill[i].id, lv
					) == false )
						break;
				}
			}
			if(i != MAX_HOMSKILL)
				break;
		}

		// success
		result = true;

		{
			// cache copy
			struct mmo_homunstatus *p3 = (struct mmo_homunstatus *)numdb_search(homun_db, p2->homun_id);
			if(p3)
				memcpy(p3, p2, sizeof(struct mmo_homunstatus));
		}
	} while(0);

	sqldbs_transaction_end(&mysql_handle, result);

	return result;
}

/*==========================================
 * ホム作成
 *------------------------------------------
 */
bool homundb_sql_new(struct mmo_homunstatus *p)
{
	bool result = false;

	nullpo_retr(false, p);

	if( sqldbs_transaction_start(&mysql_handle) == false )
		return false;

	// try
	do {
		int i;
		char t_name[64];

		if( sqldbs_query(&mysql_handle,
			"INSERT INTO `" HOMUN_TABLE "` (`class`,`name`,`account_id`,`char_id`,`base_level`,`base_exp`,"
			"`max_hp`,`hp`,`max_sp`,`sp`,`str`,`agi`,`vit`,`int`,`dex`,`luk`,"
			"`f_str`,`f_agi`,`f_vit`,`f_int`,`f_dex`,`f_luk`,"
			"`status_point`,`skill_point`,`equip`,`intimate`,`hungry`,`rename_flag`,`incubate`) "
			"VALUES ('%d', '%s', '%d', '%d',"
			"'%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d',"
			"'%d', '%d', '%d', '%d', '%d', '%d',"
			"'%d', '%d', '%d', '%d', '%d', '%d', '%d')",
			p->class_, strecpy(t_name, p->name), p->account_id, p->char_id, p->base_level,
			p->base_exp, p->max_hp, p->hp, p->max_sp, p->sp, p->str, p->agi, p->vit, p->int_, p->dex, p->luk,
			p->f_str, p->f_agi, p->f_vit, p->f_int, p->f_dex, p->f_luk,
			p->status_point, p->skill_point, p->equip, p->intimate,
			p->hungry, p->rename_flag, p->incubate
		) == false ) {
			p->homun_id = -1;
			break;
		}

		p->homun_id = (int)sqldbs_insert_id(&mysql_handle);

		for(i = 0; i < MAX_HOMSKILL; i++) {
			if(p->skill[i].id && p->skill[i].flag != 1) {
				int lv = (p->skill[i].flag == 0)? p->skill[i].lv: p->skill[i].flag - 2;
				if( sqldbs_query(&mysql_handle,
					"INSERT INTO `" HOMUN_SKILL_TABLE "` (`homun_id`,`id`,`lv`) VALUES ('%d','%d','%d')",
					p->homun_id, p->skill[i].id, lv
				) == false )
					break;
			}
		}
		if(i != MAX_HOMSKILL)
			break;

		// success
		result = true;

		{
			// cache copy
			struct mmo_homunstatus *p2 = (struct mmo_homunstatus*)aMalloc(sizeof(struct mmo_homunstatus));
			memcpy(p2, p, sizeof(struct mmo_homunstatus));
			numdb_insert(homun_db, p->homun_id, p2);
		}
	} while(0);

	sqldbs_transaction_end(&mysql_handle, result);

	return true;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
static int homundb_sql_final_sub(void *key, void *data, va_list ap)
{
	struct mmo_homunstatus *p = (struct mmo_homunstatus *)data;

	aFree(p);

	return 0;
}

void homundb_sql_final(void)
{
	if(homun_db)
		numdb_final(homun_db, homundb_sql_final_sub);
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
bool homundb_sql_init(void)
{
	homun_db = numdb_init();
	return true;
}
