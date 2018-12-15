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

#include "db.h"
#include "malloc.h"
#include "utils.h"
#include "sqldbs.h"
#include "nullpo.h"

#include "../char.h"
#include "chardb_sql.h"

static struct dbt *char_db_;
static unsigned short char_server_port = 3306;
static char char_server_ip[32]      = "127.0.0.1";
static char char_server_id[32]      = "ragnarok";
static char char_server_pw[32]      = "ragnarok";
static char char_server_db[32]      = "ragnarok";
static char char_server_charset[32] = "";
static int  char_server_keepalive   = 0;

/*==========================================
 * 設定ファイル読込
 *------------------------------------------
 */
int chardb_sql_config_read_sub(const char* w1,const char* w2)
{
	if( strcmpi(w1,"char_server_ip") == 0 )
		strncpy(char_server_ip, w2, sizeof(char_server_ip) - 1);
	else if( strcmpi(w1,"char_server_port") == 0 )
		char_server_port = (unsigned short)atoi(w2);
	else if( strcmpi(w1,"char_server_id") == 0 )
		strncpy(char_server_id, w2, sizeof(char_server_id) - 1);
	else if( strcmpi(w1,"char_server_pw") == 0 )
		strncpy(char_server_pw, w2, sizeof(char_server_pw) - 1);
	else if( strcmpi(w1,"char_server_db") == 0 )
		strncpy(char_server_db, w2, sizeof(char_server_db) - 1);
	else if( strcmpi(w1,"char_server_charset") == 0 )
		strncpy(char_server_charset, w2, sizeof(char_server_charset) - 1);
	else if( strcmpi(w1,"char_server_keepalive") ==0 )
		char_server_keepalive = atoi(w2);
	else
		return 0;

	return 1;
}

/*==========================================
 * アイテムのロードの共通関数
 *------------------------------------------
 */
int chardb_sql_loaditem(struct item *item, int max, int id, int tableswitch)
{
	int i = 0;
	const char *tablename;
	const char *selectoption;
	char **sql_row;
	bool result = false;

	nullpo_retr(-1, item);

	memset(item, 0, sizeof(struct item) * max);

	switch (tableswitch) {
	case TABLE_NUM_INVENTORY:
		tablename    = INVENTORY_TABLE;
		selectoption = "char_id";
		break;
	case TABLE_NUM_CART:
		tablename    = CART_TABLE;
		selectoption = "char_id";
		break;
	case TABLE_NUM_STORAGE:
		tablename    = STORAGE_TABLE;
		selectoption = "account_id";
		break;
	case TABLE_NUM_GUILD_STORAGE:
		tablename    = GUILD_STORAGE_TABLE;
		selectoption = "guild_id";
		break;
	default:
		printf("Invalid table name!\n");
		return -1;
	}

	result = sqldbs_query(&mysql_handle,
		"SELECT `id`, `nameid`, `amount`, `equip`, `identify`, `refine`, `attribute`, "
		"`card0`, `card1`, `card2`, `card3`, `opt0id`, `opt0val`, `opt1id`, `opt1val`, `opt2id`, `opt2val`, "
		"`opt3id`, `opt3val`, `opt4id`, `opt4val`, `limit`, `private` FROM `%s` WHERE `%s`='%d'",
		tablename, selectoption, id
	);
	if(result == false)
		return -1;

	for(i = 0; (sql_row = sqldbs_fetch(&mysql_handle)) && i < max; i++) {
		item[i].id         = (unsigned int)atoi(sql_row[0]);
		item[i].nameid     = atoi(sql_row[1]);
		item[i].amount     = atoi(sql_row[2]);
		item[i].equip      = (unsigned int)atoi(sql_row[3]);
		item[i].identify   = atoi(sql_row[4]);
		item[i].refine     = atoi(sql_row[5]);
		item[i].attribute  = atoi(sql_row[6]);
		item[i].card[0]    = atoi(sql_row[7]);
		item[i].card[1]    = atoi(sql_row[8]);
		item[i].card[2]    = atoi(sql_row[9]);
		item[i].card[3]    = atoi(sql_row[10]);
		item[i].opt[0].id  = atoi(sql_row[11]);
		item[i].opt[0].val = atoi(sql_row[12]);
		item[i].opt[1].id  = atoi(sql_row[13]);
		item[i].opt[1].val = atoi(sql_row[14]);
		item[i].opt[2].id  = atoi(sql_row[15]);
		item[i].opt[2].val = atoi(sql_row[16]);
		item[i].opt[3].id  = atoi(sql_row[17]);
		item[i].opt[3].val = atoi(sql_row[18]);
		item[i].opt[4].id  = atoi(sql_row[19]);
		item[i].opt[4].val = atoi(sql_row[20]);
		item[i].limit      = (unsigned int)atoi(sql_row[21]);
		item[i].private_   = atoi(sql_row[22]);
	}
	sqldbs_free_result(&mysql_handle);

	return i;
}

/*==========================================
 * アイテムのセーブの共通関数
 *------------------------------------------
 */
bool chardb_sql_saveitem(struct item *item, int max, int id, int tableswitch)
{
	const char *tablename;
	const char *selectoption;
	char *p, tmp_sql[65536 * 2];
	char sep = ' ';
	bool result = false;

	nullpo_retr(false, item);

	switch (tableswitch) {
	case TABLE_NUM_INVENTORY:
		tablename    = INVENTORY_TABLE;
		selectoption = "char_id";
		break;
	case TABLE_NUM_CART:
		tablename    = CART_TABLE;
		selectoption = "char_id";
		break;
	case TABLE_NUM_STORAGE:
		tablename    = STORAGE_TABLE;
		selectoption = "account_id";
		break;
	case TABLE_NUM_GUILD_STORAGE:
		tablename    = GUILD_STORAGE_TABLE;
		selectoption = "guild_id";
		break;
	default:
		printf("Invalid table name!\n");
		return false;
	}

	if( sqldbs_transaction_start(&mysql_handle) == false )
		return false;

	// try
	do
	{
		int i;

		// delete
		if( sqldbs_query(&mysql_handle, "DELETE FROM `%s` WHERE `%s`='%d'", tablename, selectoption, id) == false)
			break;

		p  = tmp_sql;
		p += sprintf(
			p,"INSERT INTO `%s`(`id`, `%s`, `nameid`, `amount`, `equip`, `identify`, `refine`, "
			"`attribute`, `card0`, `card1`, `card2`, `card3`, `opt0id`, `opt0val`, `opt1id`, `opt1val`, `opt2id`, `opt2val`, "
			"`opt3id`, `opt3val`, `opt4id`, `opt4val`, `limit`, `private`) VALUES",tablename,selectoption
		);

		for(i = 0; i < max; i++) {
			if(item[i].nameid) {
				p += sprintf(
					p,"%c('%u','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%u',%d)",
					sep,item[i].id,id,item[i].nameid,item[i].amount,item[i].equip,item[i].identify,
					item[i].refine,item[i].attribute,item[i].card[0],item[i].card[1],item[i].card[2],item[i].card[3],
					item[i].opt[0].id,item[i].opt[0].val,item[i].opt[1].id,item[i].opt[1].val,item[i].opt[2].id,item[i].opt[2].val,
					item[i].opt[3].id,item[i].opt[3].val,item[i].opt[4].id,item[i].opt[4].val,item[i].limit,item[i].private_
				);
				sep = ',';
			}
		}

		if(sep == ',') {
			if( sqldbs_simplequery(&mysql_handle, tmp_sql) == false )
				break;
		}

		// success
		result = true;
	} while(0);

	sqldbs_transaction_end(&mysql_handle, result);

	return result;
}

/*==========================================
 * 同期
 *------------------------------------------
 */
void chardb_sql_sync(void)
{
	// nothing to do
}

/*==========================================
 * 友達リストのチェックと訂正
 *------------------------------------------
 */
static bool chardb_validate_friend(struct mmo_chardata *p)
{
	bool result = false;

	nullpo_retr(false, p);

	if( sqldbs_transaction_start(&mysql_handle) == false )
		return false;

	// try
	do {
		int i;

		for(i = 0; i < p->st.friend_num; i++)
		{
			int rows = 0;
			if( sqldbs_query(&mysql_handle, "SELECT 1 FROM `" FRIEND_TABLE "` WHERE `char_id`='%d' AND `friend_id`='%d'", p->st.friend_data[i].char_id, p->st.char_id) == false )
				break;

			rows = sqldbs_num_rows(&mysql_handle);
			sqldbs_free_result(&mysql_handle);

			if(rows <= 0) {
				// 相手に存在しないので、友達リストから削除する
				if( sqldbs_query(&mysql_handle,	"DELETE FROM `" FRIEND_TABLE "` WHERE `char_id`='%d' AND `friend_id`='%d'", p->st.char_id, p->st.friend_data[i].char_id) == false ) {
					// 続行
					continue;
				}
				p->st.friend_num--;
				memmove(&p->st.friend_data[i], &p->st.friend_data[i+1], sizeof(p->st.friend_data[0]) * (p->st.friend_num - i));
				i--;
				printf("*friend_data_correct*\n");
			}
		}
		if(i != p->st.friend_num)
			break;

		// success
		result = true;
	} while(0);

	sqldbs_transaction_end(&mysql_handle, result);

	return result;
}

/*==========================================
 * キャラIDからキャラデータのロード
 *------------------------------------------
 */
const struct mmo_chardata* chardb_sql_load(int char_id)
{
	int i, n;
	struct mmo_chardata *p;
	char **sql_row;
	bool result = false;

	p = (struct mmo_chardata*)numdb_search(char_db_, char_id);
	if (p && p->st.char_id == char_id) {
		// 既にキャッシュが存在する
		return p;
	}

	result = sqldbs_query(&mysql_handle,
		"SELECT `account_id`, `char_num`, `name`, `class`, `base_level`, `job_level`, `base_exp`, `job_exp`, `zeny`,"
		"`str`, `agi`, `vit`, `int`, `dex`, `luk`, `max_hp`, `hp`, `max_sp`, `sp`, `status_point`, `skill_point`,"
		"`option`, `karma`, `manner`, `die_counter`, `party_id`, `guild_id`, `pet_id`, `homun_id`, `merc_id`, `elem_id`,"
		"`hair`, `hair_color`, `clothes_color`, `weapon`, `shield`, `robe`, `head_top`, `head_mid`, `head_bottom`,"
		"`last_map`, `last_x`, `last_y`, `save_map`, `save_x`, `save_y`,"
		"`partner_id`, `parent_id`, `parent_id2`, `baby_id`, `delete_date`, `refuse_partyinvite`, `show_equip`, `font`, `style`, `sex`"
		" FROM `" CHAR_TABLE "` WHERE `char_id` = '%d'", char_id
	);
	if(result == false) {
		printf("char - failed\n");
		return NULL;
	}

	sql_row = sqldbs_fetch(&mysql_handle);
	if(sql_row == NULL) {
		// 見つからなくても正常
		sqldbs_free_result(&mysql_handle);
		return NULL;
	}
	if(p == NULL) {
		p = (struct mmo_chardata *)aMalloc(sizeof(struct mmo_chardata));
		numdb_insert(char_db_, char_id, p);
	}
	memset(p, 0, sizeof(struct mmo_chardata));

	p->st.char_id             = char_id;
	p->st.account_id          = atoi(sql_row[0]);
	p->st.char_num            = atoi(sql_row[1]);
	strncpy(p->st.name, sql_row[2], 24);
	p->st.class_              = atoi(sql_row[3]);
	p->st.base_level          = atoi(sql_row[4]);
	p->st.job_level           = atoi(sql_row[5]);
	p->st.base_exp            = atoi(sql_row[6]);
	p->st.job_exp             = atoi(sql_row[7]);
	p->st.zeny                = atoi(sql_row[8]);
	p->st.str                 = atoi(sql_row[9]);
	p->st.agi                 = atoi(sql_row[10]);
	p->st.vit                 = atoi(sql_row[11]);
	p->st.int_                = atoi(sql_row[12]);
	p->st.dex                 = atoi(sql_row[13]);
	p->st.luk                 = atoi(sql_row[14]);
	p->st.max_hp              = atoi(sql_row[15]);
	p->st.hp                  = atoi(sql_row[16]);
	p->st.max_sp              = atoi(sql_row[17]);
	p->st.sp                  = atoi(sql_row[18]);
	p->st.status_point        = atoi(sql_row[19]);
	p->st.skill_point         = atoi(sql_row[20]);
	p->st.option              = (unsigned int)atoi(sql_row[21]);
	p->st.karma               = atoi(sql_row[22]);
	p->st.manner              = atoi(sql_row[23]);
	p->st.die_counter         = atoi(sql_row[24]);
	p->st.party_id            = atoi(sql_row[25]);
	p->st.guild_id            = atoi(sql_row[26]);
	p->st.pet_id              = atoi(sql_row[27]);
	p->st.homun_id            = atoi(sql_row[28]);
	p->st.merc_id             = atoi(sql_row[29]);
	p->st.elem_id             = atoi(sql_row[30]);
	p->st.hair                = atoi(sql_row[31]);
	p->st.hair_color          = atoi(sql_row[32]);
	p->st.clothes_color       = atoi(sql_row[33]);
	p->st.weapon              = atoi(sql_row[34]);
	p->st.shield              = atoi(sql_row[35]);
	p->st.robe                = atoi(sql_row[36]);
	p->st.head_top            = atoi(sql_row[37]);
	p->st.head_mid            = atoi(sql_row[38]);
	p->st.head_bottom         = atoi(sql_row[39]);
	strncpy(p->st.last_point.map, sql_row[40], 24);
	p->st.last_point.x        = atoi(sql_row[41]);
	p->st.last_point.y        = atoi(sql_row[42]);
	strncpy(p->st.save_point.map, sql_row[43], 24);
	p->st.save_point.x        = atoi(sql_row[44]);
	p->st.save_point.y        = atoi(sql_row[45]);
	p->st.partner_id          = atoi(sql_row[46]);
	p->st.parent_id[0]        = atoi(sql_row[47]);
	p->st.parent_id[1]        = atoi(sql_row[48]);
	p->st.baby_id             = atoi(sql_row[49]);
	p->st.delete_date         = atoi(sql_row[50]);
	p->st.refuse_partyinvite  = atoi(sql_row[51]);
	p->st.show_equip          = atoi(sql_row[52]);
	p->st.font                = atoi(sql_row[53]);
	p->st.style               = atoi(sql_row[54]);
	p->st.sex                 = atoi(sql_row[55]);

	// force \0 terminal
	p->st.name[23]           = '\0';
	p->st.last_point.map[23] = '\0';
	p->st.save_point.map[23] = '\0';

	sqldbs_free_result(&mysql_handle);

	// read memo data
	if(sqldbs_query(&mysql_handle, "SELECT `index`,`map`,`x`,`y` FROM `" MEMO_TABLE "` WHERE `char_id`='%d'", char_id))
	{
		while((sql_row = sqldbs_fetch(&mysql_handle)) != NULL) {
			n = atoi(sql_row[0]);
			if(n >= 0 && n < MAX_PORTAL_MEMO) {
				strncpy(p->st.memo_point[n].map, sql_row[1], 24);
				p->st.memo_point[n].map[23] = '\0';	// force \0 terminal
				p->st.memo_point[n].x       = atoi(sql_row[2]);
				p->st.memo_point[n].y       = atoi(sql_row[3]);
			}
		}
		sqldbs_free_result(&mysql_handle);
	}

	// read inventory
	chardb_sql_loaditem(p->st.inventory, MAX_INVENTORY, p->st.char_id, TABLE_NUM_INVENTORY);

	// read cart
	chardb_sql_loaditem(p->st.cart, MAX_CART, p->st.char_id, TABLE_NUM_CART);

	// read skill
	if(sqldbs_query(&mysql_handle, "SELECT `id`, `lv` FROM `" SKILL_TABLE "` WHERE `char_id`='%d'", char_id))
	{
		while((sql_row = sqldbs_fetch(&mysql_handle)) != NULL) {
			n = atoi(sql_row[0]);
			if(n >= 0 && n < MAX_PCSKILL) {
				p->st.skill[n].id = n;
				p->st.skill[n].lv = atoi(sql_row[1]);
			}
		}
		sqldbs_free_result(&mysql_handle);
	}

	// global_reg
	i = 0;
	if(sqldbs_query(&mysql_handle, "SELECT `reg`, `value` FROM `" GLOBALREG_TABLE "` WHERE `char_id`='%d'", char_id))
	{
		for(i = 0; (sql_row = sqldbs_fetch(&mysql_handle)); i++) {
			if(i < GLOBAL_REG_NUM) {
				strncpy(p->reg.global[i].str, sql_row[0], 32);
				p->reg.global[i].str[31] = '\0';	// force \0 terminal
				p->reg.global[i].value   = atoi(sql_row[1]);
			} else {
				printf("char_load %d: couldn't load %s (GLOBAL_REG_NUM = %d)\a\n", p->st.char_id, sql_row[0], GLOBAL_REG_NUM);
			}
		}
		sqldbs_free_result(&mysql_handle);
	}
	p->reg.global_num = (i < GLOBAL_REG_NUM)? i: GLOBAL_REG_NUM;

	// friend list
	p->st.friend_num = 0;

	if(sqldbs_query(&mysql_handle,
		"SELECT t1.`friend_account`, t1.`friend_id`, t2.`name` FROM `" FRIEND_TABLE "` t1 LEFT JOIN `" CHAR_TABLE "` t2 "
		"ON t1.`friend_account` = t2.`account_id` AND t1.`friend_id` = t2.`char_id` WHERE t1.`char_id` = '%d'", char_id))
	{
		for(i = 0; i < MAX_FRIEND && (sql_row = sqldbs_fetch(&mysql_handle)); i++) {
			p->st.friend_data[i].account_id = atoi(sql_row[0]);
			p->st.friend_data[i].char_id    = atoi(sql_row[1]);
			if(sql_row[2]) {
				strncpy(p->st.friend_data[i].name, sql_row[2], 24);
				p->st.friend_data[i].name[23] = '\0';	// force \0 terminal
			} else {
				strncpy(p->st.friend_data[i].name, unknown_char_name, 24);
			}
		}
		sqldbs_free_result(&mysql_handle);
		p->st.friend_num = (i < MAX_FRIEND)? i: MAX_FRIEND;
	}

	// feel_info
	if(sqldbs_query(&mysql_handle, "SELECT `map`,`lv` FROM `" FEEL_TABLE "` WHERE `char_id`='%d'", char_id))
	{
		while((sql_row = sqldbs_fetch(&mysql_handle)) != NULL) {
			n = atoi(sql_row[1]);
			if(n >= 0 && n < 3) {
				strncpy(p->st.feel_map[n], sql_row[0], 24);
				p->st.feel_map[n][23] = '\0';	// force \0 terminal
			}
		}
		sqldbs_free_result(&mysql_handle);
	}

	// hotkey
	if(sqldbs_query(&mysql_handle, "SELECT `key`, `type`, `id`, `lv` FROM `" HOTKEY_TABLE "` WHERE `char_id`='%d'", char_id))
	{
		while((sql_row = sqldbs_fetch(&mysql_handle)) != NULL) {
			n = atoi(sql_row[0]);
			if(n >= 0 && n < MAX_HOTKEYS) {
				p->st.hotkey[n].type = (char)atoi(sql_row[1]);
				p->st.hotkey[n].id   = atoi(sql_row[2]);
				p->st.hotkey[n].lv   = (unsigned short)atoi(sql_row[3]);
			}
		}
		sqldbs_free_result(&mysql_handle);
	}

	// mercenary_employ
	if(sqldbs_query(&mysql_handle, "SELECT `type`, `fame`, `call` FROM `" MERC_EMPLOY_TABLE "` WHERE `char_id`='%d'", char_id))
	{
		while((sql_row = sqldbs_fetch(&mysql_handle)) != NULL) {
			n = atoi(sql_row[0]);
			if(n >= 0 && n < MAX_MERC_TYPE) {
				p->st.merc_fame[n] = atoi(sql_row[1]);
				p->st.merc_call[n] = atoi(sql_row[2]);
			}
		}
		sqldbs_free_result(&mysql_handle);
	}

	// validate friend list
	chardb_validate_friend(p);

	return p;
}

/*==========================================
 * キャラ変数のセーブ
 *------------------------------------------
 */
bool chardb_sql_save_reg(int account_id, int char_id, int num, struct global_reg *reg)
{
	const struct mmo_chardata *cd;
	bool result = false;
	struct sqldbs_stmt *st;

	nullpo_retr(false, reg);

	cd = chardb_sql_load(char_id);
	if( cd == NULL || cd->st.account_id != account_id )
		return false;

	// init
	st = sqldbs_stmt_init(&mysql_handle);
	if(st == NULL)
		return false;

	if( sqldbs_transaction_start(&mysql_handle) == false )
		return false;

	// try
	do
	{
		int i = 0;

		// delete globalreg
		if( sqldbs_query(&mysql_handle, "DELETE FROM `" GLOBALREG_TABLE "` WHERE `char_id`='%d'", char_id) == false )
			break;

		// prepare
		if( sqldbs_stmt_prepare(st, "INSERT INTO `" GLOBALREG_TABLE "` (`char_id`, `reg`, `value`) VALUES ('%d', ? , ?)", char_id) == false )
			break;

		// insert val
		for(i = 0; i < num; i++) {
			if(reg[i].str[0] && reg[i].value != 0)
			{
				sqldbs_stmt_bind_param(st, 0, SQL_DATA_TYPE_VAR_STRING, reg[i].str, strlen(reg[i].str));
				sqldbs_stmt_bind_param(st, 1, SQL_DATA_TYPE_INT, &reg[i].value, 0);
				if( sqldbs_stmt_execute(st) == false )
					break;
			}
		}
		if(i != num)
			break;

		// success
		result = true;

		{
			// cache copy
			struct mmo_chardata *cd2 = (struct mmo_chardata *)numdb_search(char_db_, char_id);
			if(cd2) {
				memcpy(&cd2->reg.global, reg,sizeof(cd2->reg.global));
				cd2->reg.global_num = num;
			}
		}
	} while(0);

	sqldbs_stmt_close(st);
	sqldbs_transaction_end(&mysql_handle, result);

	return result;
}

#define UPDATE_NUM(val,sql) \
	if(st1->val != st2->val) {\
		p += sprintf(p,"%c`"sql"` = '%d'",sep,st2->val); sep = ',';\
	}
#define UPDATE_UNUM(val,sql) \
	if(st1->val != st2->val) {\
		p += sprintf(p,"%c`"sql"` = '%u'",sep,st2->val); sep = ',';\
	}
#define UPDATE_STR(val,sql) \
	if(strcmp(st1->val,st2->val)) {\
		p += sprintf(p,"%c`"sql"` = '%s'",sep,strecpy(buf,st2->val)); sep = ',';\
	}

/*==========================================
 * キャラデータのセーブ
 *------------------------------------------
 */
bool chardb_sql_save(struct mmo_charstatus *st2)
{
	const struct mmo_chardata *cd;
	const struct mmo_charstatus *st1;
	char sep = ' ';
	char buf[256], tmp_sql[65536];
	char *p = tmp_sql;
	bool result = false;

	nullpo_retr(false, st2);

	cd = chardb_sql_load(st2->char_id);
	if(cd == NULL)
		return false;
	st1 = &cd->st;

	// basic information
	strcpy(p, "UPDATE `" CHAR_TABLE "` SET");
	p += strlen(p);

	UPDATE_NUM(account_id         ,"account_id");
	UPDATE_NUM(char_num           ,"char_num");
	UPDATE_STR(name               ,"name");
	UPDATE_NUM(class_             ,"class");
	UPDATE_NUM(base_level         ,"base_level");
	UPDATE_NUM(job_level          ,"job_level");
	UPDATE_NUM(base_exp           ,"base_exp");
	UPDATE_NUM(job_exp            ,"job_exp");
	UPDATE_NUM(zeny               ,"zeny");
	UPDATE_NUM(str                ,"str");
	UPDATE_NUM(agi                ,"agi");
	UPDATE_NUM(vit                ,"vit");
	UPDATE_NUM(int_               ,"int");
	UPDATE_NUM(dex                ,"dex");
	UPDATE_NUM(luk                ,"luk");
	UPDATE_NUM(max_hp             ,"max_hp");
	UPDATE_NUM(hp                 ,"hp");
	UPDATE_NUM(max_sp             ,"max_sp");
	UPDATE_NUM(sp                 ,"sp");
	UPDATE_NUM(status_point       ,"status_point");
	UPDATE_NUM(skill_point        ,"skill_point");
	UPDATE_UNUM(option            ,"option");
	UPDATE_NUM(karma              ,"karma");
	UPDATE_NUM(manner             ,"manner");
	UPDATE_NUM(die_counter        ,"die_counter");
	UPDATE_NUM(party_id           ,"party_id");
	UPDATE_NUM(guild_id           ,"guild_id");
	UPDATE_NUM(pet_id             ,"pet_id");
	UPDATE_NUM(homun_id           ,"homun_id");
	UPDATE_NUM(merc_id            ,"merc_id");
	UPDATE_NUM(elem_id            ,"elem_id");
	UPDATE_NUM(hair               ,"hair");
	UPDATE_NUM(hair_color         ,"hair_color");
	UPDATE_NUM(clothes_color      ,"clothes_color");
	UPDATE_NUM(weapon             ,"weapon");
	UPDATE_NUM(shield             ,"shield");
	UPDATE_NUM(robe               ,"robe");
	UPDATE_NUM(head_top           ,"head_top");
	UPDATE_NUM(head_mid           ,"head_mid");
	UPDATE_NUM(head_bottom        ,"head_bottom");
	UPDATE_STR(last_point.map     ,"last_map");
	UPDATE_NUM(last_point.x       ,"last_x");
	UPDATE_NUM(last_point.y       ,"last_y");
	UPDATE_STR(save_point.map     ,"save_map");
	UPDATE_NUM(save_point.x       ,"save_x");
	UPDATE_NUM(save_point.y       ,"save_y");
	UPDATE_NUM(partner_id         ,"partner_id");
	UPDATE_NUM(parent_id[0]       ,"parent_id");
	UPDATE_NUM(parent_id[1]       ,"parent_id2");
	UPDATE_NUM(baby_id            ,"baby_id");
	UPDATE_UNUM(delete_date       ,"delete_date");
	UPDATE_UNUM(refuse_partyinvite,"refuse_partyinvite");
	UPDATE_UNUM(show_equip        ,"show_equip");
	UPDATE_UNUM(font              ,"font");
	UPDATE_NUM(style              ,"style");
	UPDATE_NUM(sex                ,"sex");

	if( sqldbs_transaction_start(&mysql_handle) == false )
		return false;

	// try
	do {
		int i;

		if(sep == ',') {
			sprintf(p, " WHERE `char_id` = '%d'", st2->char_id);
			if( sqldbs_simplequery(&mysql_handle, tmp_sql) == false )
				break;
		}

		// memo
		if (memcmp(st1->memo_point, st2->memo_point, sizeof(st1->memo_point))) {
			if( sqldbs_query(&mysql_handle, "DELETE FROM `" MEMO_TABLE "` WHERE `char_id`='%d'", st2->char_id) == false )
				break;

			for(i = 0; i < MAX_PORTAL_MEMO; i++) {
				if(st2->memo_point[i].map[0]) {
					if( sqldbs_query(&mysql_handle,
						"INSERT INTO `" MEMO_TABLE "` (`char_id`,`index`,`map`,`x`,`y`) VALUES ('%d', '%d', '%s', '%d', '%d')",
						st2->char_id, i, strecpy(buf,st2->memo_point[i].map), st2->memo_point[i].x, st2->memo_point[i].y
					) == false )
						break;
				}
			}
			if(i != MAX_PORTAL_MEMO)
				break;
		}

		// inventory
		if (memcmp(st1->inventory, st2->inventory, sizeof(st1->inventory))) {
			if( chardb_sql_saveitem(st2->inventory,MAX_INVENTORY,st2->char_id,TABLE_NUM_INVENTORY) == false )
				break;
		}

		// cart
		if (memcmp(st1->cart, st2->cart, sizeof(st1->cart))) {
			if( chardb_sql_saveitem(st2->cart, MAX_CART, st2->char_id, TABLE_NUM_CART) == false )
				break;
		}

		// skill
		if(memcmp(st1->skill, st2->skill, sizeof(st1->skill))) {
			unsigned short sk_lv;

			if( sqldbs_query(&mysql_handle, "DELETE FROM `" SKILL_TABLE "` WHERE `char_id`='%d'", st2->char_id) == false )
				break;

			for(i = 0; i < MAX_PCSKILL; i++) {
				sk_lv = (st2->skill[i].flag == 0)? st2->skill[i].lv: st2->skill[i].flag - 2;
				if(st2->skill[i].id && st2->skill[i].flag != 1) {
					if( sqldbs_query(&mysql_handle,
						"INSERT INTO `" SKILL_TABLE "` (`char_id`, `id`, `lv`) VALUES ('%d','%d','%d')",
						st2->char_id, st2->skill[i].id, sk_lv
					) == false )
						break;
				}
			}
			if(i != MAX_PCSKILL)
				break;
		}

		// friend
		if( st1->friend_num != st2->friend_num ||
		    memcmp(st1->friend_data, st2->friend_data, sizeof(st1->friend_data)) != 0 )
		{
			if( sqldbs_query(&mysql_handle, "DELETE FROM `" FRIEND_TABLE "` WHERE `char_id`='%d'", st2->char_id) == false )
				break;

			for(i = 0; i < st2->friend_num; i++)
			{
				if( sqldbs_query(&mysql_handle,
					"INSERT INTO `" FRIEND_TABLE "` (`char_id`, `friend_account`, `friend_id`) VALUES ('%d', '%d', '%d')",
					st2->char_id, st2->friend_data[i].account_id, st2->friend_data[i].char_id
				) == false )
					break;
			}
			if(i != st2->friend_num)
				break;
		}

		// feel_info
		if (memcmp(st1->feel_map, st2->feel_map, sizeof(st1->feel_map))) {
			if( sqldbs_query(&mysql_handle, "DELETE FROM `" FEEL_TABLE "` WHERE `char_id`='%d'", st2->char_id) == false )
				break;

			for(i = 0; i < 3; i++) {
				if(st2->feel_map[i][0]) {
					if( sqldbs_query(&mysql_handle,
						"INSERT INTO `" FEEL_TABLE "` (`char_id`,`map`,`lv`) VALUES ('%d', '%s', '%d')",
						st2->char_id, strecpy(buf,st2->feel_map[i]), i
					) == false )
						break;
				}
			}
			if(i != 3)
				break;
		}

		// hotkey
		if (memcmp(st1->hotkey, st2->hotkey, sizeof(st1->hotkey))) {
			if( sqldbs_query(&mysql_handle, "DELETE FROM `" HOTKEY_TABLE "` WHERE `char_id`='%d'", st2->char_id) == false )
				break;

			for(i = 0; i < MAX_HOTKEYS; i++) {
				if(st2->hotkey[i].id > 0) {
					if( sqldbs_query(&mysql_handle,
						"INSERT INTO `" HOTKEY_TABLE "` (`char_id`,`key`,`type`,`id`,`lv`) VALUES ('%d', '%d', '%d', '%d', '%d')",
						st2->char_id, i, st2->hotkey[i].type, st2->hotkey[i].id, st2->hotkey[i].lv
					) == false )
						break;
				}
			}
			if(i != MAX_HOTKEYS)
				break;
		}

		// mercenary
		if (memcmp(st1->merc_fame, st2->merc_fame, sizeof(st1->merc_fame)) ||
		    memcmp(st1->merc_call, st2->merc_call, sizeof(st1->merc_call)))
		{
			if( sqldbs_query(&mysql_handle, "DELETE FROM `" MERC_EMPLOY_TABLE "` WHERE `char_id`='%d'", st2->char_id) == false )
				break;

			for(i = 0; i < MAX_MERC_TYPE; i++) {
				if(st2->merc_fame[i] > 0 || st2->merc_call[i] > 0) {
					if( sqldbs_query(&mysql_handle,
						"INSERT INTO `" MERC_EMPLOY_TABLE "` (`char_id`,`type`,`fame`,`call`) VALUES ('%d', '%d', '%d', '%d')",
						st2->char_id, i, st2->merc_fame[i], st2->merc_call[i]
					) == false )
						break;
				}
			}
			if(i != MAX_MERC_TYPE)
				break;
		}

		// success
		result = true;

		{
			// cache copy
			struct mmo_chardata *cd2 = (struct mmo_chardata *)numdb_search(char_db_, st2->char_id);
			if(cd2)
				memcpy(&cd2->st, st2, sizeof(struct mmo_charstatus));
		}
	} while(0);

	sqldbs_transaction_end(&mysql_handle, result);

	return result;
}

/*==========================================
 * キャラ作成
 *------------------------------------------
 */
const struct mmo_chardata* chardb_sql_make(int account_id, const unsigned char *name, short str, short agi, short vit, short int_, short dex, short luk, short hair_color, short hair, short job, char sex, unsigned char slot, int *flag)
{
	int char_id = 0;
	char buf[256];
	char **sql_row;
	struct sqldbs_stmt *st;
	bool result = false;

	// 同一アカウントID、同一キャラスロット、同名チェック
	if( sqldbs_query(&mysql_handle,
			"SELECT 1 FROM `" CHAR_TABLE "` WHERE `account_id` = '%d' AND `char_num` = '%d' "
			"UNION ALL "
			"SELECT 2 FROM `" CHAR_TABLE "` WHERE `name` = '%s'",
			account_id, slot, strecpy(buf, name)
		) == false )
		return NULL;

	while((sql_row = sqldbs_fetch(&mysql_handle)) != NULL) {
		int num = atoi(sql_row[0]);
		if(num == 2) {
			// 同名重複
			*flag = 0x00;
		}
		return NULL;
	}

	charlog_log("make new char %d %d %s", account_id, slot, name);

	// init
	st = sqldbs_stmt_init(&mysql_handle);
	if(st == NULL)
		return NULL;

	if( sqldbs_transaction_start(&mysql_handle) == false )
		return NULL;

	// try
	do
	{
		struct point start_point;
		int start_weapon = human_start_weapon;
		int start_armor  = human_start_armor;
		int start_zeny   = human_start_zeny;

		int max_hp = 40 * (100 + vit) / 100;
		int hp = 40 * (100 + vit) / 100;
		int max_sp = 11 * (100 + int_) / 100;
		int sp = 11 * (100 + int_) / 100;
#if PACKETVER < 20120307
		int status_point = 0;
#else
		int status_point = 48;
		str = agi = vit = int_ = dex = luk = 1;
#endif

		memcpy(&start_point, &human_start_point, sizeof(human_start_point));

		// ドラム族用初期設定
		if(job == PC_CLASS_SUM) {
			start_weapon       = doram_start_weapon;
			start_armor        = doram_start_armor;
			start_zeny         = doram_start_zeny;
			memcpy(&start_point, &doram_start_point, sizeof(doram_start_point));
		}

		// prepare
		if( sqldbs_stmt_prepare(st,
			"INSERT INTO `" CHAR_TABLE "` (`account_id`,`char_num`,`name`,`zeny`,`str`,`agi`,`vit`,`int`,"
			"`dex`,`luk`,`max_hp`,`hp`,`max_sp`,`sp`,`status_point`,`hair`,`hair_color`,`class`,`sex`,`last_map`,`last_x`,"
			"`last_y`,`save_map`,`save_x`,`save_y`) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)"
		) == false )
			break;

		// bind
		sqldbs_stmt_bind_param(st,  0, SQL_DATA_TYPE_INT,        &account_id,     0                      );
		sqldbs_stmt_bind_param(st,  1, SQL_DATA_TYPE_UCHAR,      &slot,           0                      );
		sqldbs_stmt_bind_param(st,  2, SQL_DATA_TYPE_VAR_STRING, (void *)name,    strlen(name)           );
		sqldbs_stmt_bind_param(st,  3, SQL_DATA_TYPE_INT,        &start_zeny,     0                      );
		sqldbs_stmt_bind_param(st,  4, SQL_DATA_TYPE_SHORT,      &str,            0                      );
		sqldbs_stmt_bind_param(st,  5, SQL_DATA_TYPE_SHORT,      &agi,            0                      );
		sqldbs_stmt_bind_param(st,  6, SQL_DATA_TYPE_SHORT,      &vit,            0                      );
		sqldbs_stmt_bind_param(st,  7, SQL_DATA_TYPE_SHORT,      &int_,           0                      );
		sqldbs_stmt_bind_param(st,  8, SQL_DATA_TYPE_SHORT,      &dex,            0                      );
		sqldbs_stmt_bind_param(st,  9, SQL_DATA_TYPE_SHORT,      &luk,            0                      );
		sqldbs_stmt_bind_param(st, 10, SQL_DATA_TYPE_INT,        &max_hp,         0                      );
		sqldbs_stmt_bind_param(st, 11, SQL_DATA_TYPE_INT,        &hp,             0                      );
		sqldbs_stmt_bind_param(st, 12, SQL_DATA_TYPE_INT,        &max_sp,         0                      );
		sqldbs_stmt_bind_param(st, 13, SQL_DATA_TYPE_INT,        &sp,             0                      );
		sqldbs_stmt_bind_param(st, 14, SQL_DATA_TYPE_SHORT,      &status_point,   0                      );
		sqldbs_stmt_bind_param(st, 15, SQL_DATA_TYPE_SHORT,      &hair,           0                      );
		sqldbs_stmt_bind_param(st, 16, SQL_DATA_TYPE_SHORT,      &hair_color,     0                      );
		sqldbs_stmt_bind_param(st, 17, SQL_DATA_TYPE_SHORT,      &job,            0                      );
		sqldbs_stmt_bind_param(st, 18, SQL_DATA_TYPE_UCHAR,      &sex,            0                      );
		sqldbs_stmt_bind_param(st, 19, SQL_DATA_TYPE_VAR_STRING, start_point.map, strlen(start_point.map));
		sqldbs_stmt_bind_param(st, 20, SQL_DATA_TYPE_SHORT,      &start_point.x,  0                      );
		sqldbs_stmt_bind_param(st, 21, SQL_DATA_TYPE_SHORT,      &start_point.y,  0                      );
		sqldbs_stmt_bind_param(st, 22, SQL_DATA_TYPE_VAR_STRING, start_point.map, strlen(start_point.map));
		sqldbs_stmt_bind_param(st, 23, SQL_DATA_TYPE_SHORT,      &start_point.x,  0                      );
		sqldbs_stmt_bind_param(st, 24, SQL_DATA_TYPE_SHORT,      &start_point.y,  0                      );

		// execute
		if( sqldbs_stmt_execute(st) == false )
			break;

		// キャラIDの取得
		char_id = (int)sqldbs_insert_id(&mysql_handle);

		// デフォルト装備(武器)
		if(start_weapon > 0)
		{
			if( sqldbs_query(&mysql_handle,
				"INSERT INTO `" INVENTORY_TABLE "` (`id`, `char_id`, `nameid`, `amount`, `equip`, `identify`) "
				"VALUES (1, '%d', '%d', '%d', '%d', '%d')",
				char_id, start_weapon, 1, LOC_RARM, 1
			) == false )
				break;
		}

		// デフォルト装備(防具)
		if(start_armor > 0)
		{
			if( sqldbs_query(&mysql_handle,
				"INSERT INTO `" INVENTORY_TABLE "` (`id`, `char_id`, `nameid`, `amount`, `equip`, `identify`) "
				"VALUES (2, '%d', '%d', '%d', '%d', '%d')",
				char_id, start_armor, 1, LOC_BODY, 1
			) == false )
				break;
		}

		// success
		result = true;
		printf("success, aid: %d, cid: %d, slot: %d, name: %s\n", account_id, char_id, slot, name);
	} while(0);

	sqldbs_stmt_close(st);
	sqldbs_transaction_end(&mysql_handle, result);

	return ( result == true )? chardb_sql_load(char_id) : NULL;
}

/*==========================================
 * アカウントIDの全キャラデータをロード
 *------------------------------------------
 */
int chardb_sql_load_all(struct char_session_data* sd, int account_id)
{
	int i, j, found_num = 0;
	int found_id[MAX_CHAR_SLOT];
	char **sql_row;
	const struct mmo_chardata *cd;

	nullpo_retr(-1, sd);

	memset(found_id, 0, sizeof(found_id));

	// search char.
	if( sqldbs_query(&mysql_handle, "SELECT `char_id` FROM `" CHAR_TABLE "` WHERE `account_id` = '%d'", account_id) == false )
		return -1;

	while((sql_row = sqldbs_fetch(&mysql_handle))) {
		found_id[found_num++] = atoi(sql_row[0]);
		if(found_num == sizeof(found_id)/sizeof(found_id[0]))
			break;
	}
	sqldbs_free_result(&mysql_handle);

	j = 0;
	for(i = 0; i < found_num ; i++) {
		cd = chardb_sql_load(found_id[i]);
		if(cd && cd->st.char_num < max_char_slot) {
			sd->found_char[j++] = cd;
			if(j == max_char_slot)
				break;
		}
	}
	for(i = j; i < max_char_slot; i++) {
		sd->found_char[i] = NULL;
	}

	return j;
}

/*==========================================
 * キャラ削除
 *------------------------------------------
 */
bool chardb_sql_delete_sub(int char_id)
{
	bool result = false;

	if( sqldbs_transaction_start(&mysql_handle) == false )
		return false;

	// try
	do
	{
		// delete char
		if( sqldbs_query(&mysql_handle, "DELETE FROM `" CHAR_TABLE "` WHERE `char_id`='%d'", char_id) == false )
			break;

		// delete memo
		if( sqldbs_query(&mysql_handle, "DELETE FROM `" MEMO_TABLE "` WHERE `char_id`='%d'", char_id) == false )
			break;

		// delete inventory
		if( sqldbs_query(&mysql_handle, "DELETE FROM `" INVENTORY_TABLE "` WHERE `char_id`='%d'", char_id) == false )
			break;

		// delete cart
		if( sqldbs_query(&mysql_handle, "DELETE FROM `" CART_TABLE "` WHERE `char_id`='%d'", char_id) == false )
			break;

		// delete skill
		if( sqldbs_query(&mysql_handle, "DELETE FROM `" SKILL_TABLE "` WHERE `char_id`='%d'", char_id) == false )
			break;

		// delete globalreg
		if( sqldbs_query(&mysql_handle, "DELETE FROM `" GLOBALREG_TABLE "` WHERE `char_id`='%d'", char_id) == false )
			break;

		// delete friend
		if( sqldbs_query(&mysql_handle, "DELETE FROM `" FRIEND_TABLE "` WHERE `char_id`='%d'", char_id) == false )
			break;

		// delete fell
		if( sqldbs_query(&mysql_handle, "DELETE FROM `" FEEL_TABLE "` WHERE `char_id`='%d'", char_id) == false )
			break;

		// delete hotkey
		if( sqldbs_query(&mysql_handle, "DELETE FROM `" HOTKEY_TABLE "` WHERE `char_id`='%d'", char_id) == false )

		// delete merc
		if( sqldbs_query(&mysql_handle, "DELETE FROM `" MERC_EMPLOY_TABLE "` WHERE `char_id`='%d'", char_id) == false )
			break;

		// success
		result = true;

		{
			// cache delete
			struct mmo_chardata *p = (struct mmo_chardata *)numdb_erase(char_db_, char_id);
			if(p) {
				aFree(p);
			}
		}
	} while(0);

	sqldbs_transaction_end(&mysql_handle, result);

	return result;
}

/*==========================================
 * キャラ名からキャラデータを取得
 *------------------------------------------
 */
const struct mmo_chardata* chardb_sql_nick2chardata(const char *char_name)
{
	const struct mmo_chardata *cd = NULL;
	char buf[64];
	char **sql_row;

	if( sqldbs_query(&mysql_handle, "SELECT `char_id` FROM `" CHAR_TABLE "` WHERE `name` = '%s'", strecpy(buf, char_name)) == false )
		return NULL;

	sql_row = sqldbs_fetch(&mysql_handle);
	if(sql_row) {
		cd = chardb_sql_load(atoi(sql_row[0]));
	}
	sqldbs_free_result(&mysql_handle);

	return cd;
}

/*==========================================
 * オンライン
 *------------------------------------------
 */
bool chardb_sql_set_online(int char_id, bool is_online)
{
	int flag = (is_online)? 1: 0;
	bool result = false;

	if(char_id > 0)
		result = sqldbs_query(&mysql_handle, "UPDATE `" CHAR_TABLE "` SET `online` = '%d' WHERE `char_id` = '%d'", flag, char_id);
	else
		result = sqldbs_query(&mysql_handle, "UPDATE `" CHAR_TABLE "` SET `online` = '%d' WHERE `online` = '%d'", flag, flag);

	return result;
}

/*==========================================
 * ランキングの構築
 *------------------------------------------
 */
bool chardb_sql_build_ranking(void)
{
	int i, j;
	char buf[128];
	char **sql_row;
	bool result = true;

	memset(&ranking_data, 0, sizeof(ranking_data));

	for(i = 0; i < MAX_RANKING; i++) {
		result = sqldbs_query(&mysql_handle,
			"SELECT t1.`char_id`, t1.`value`, t2.`name`  FROM `" GLOBALREG_TABLE "` t1 LEFT JOIN `" CHAR_TABLE "` t2 "
			"ON t1.`char_id` = t2.`char_id` WHERE t1.`reg` = '%s' AND t1.`value` > 0 "
			"ORDER BY t1.`value` DESC LIMIT 0,%d",
			strecpy(buf, ranking_reg[i]), MAX_RANKER
		);
		if(result == false)
			break;

		for(j = 0; j < MAX_RANKER && (sql_row = sqldbs_fetch(&mysql_handle)); j++) {
			struct Ranking_Data *r = &ranking_data[i][j];
			r->char_id = atoi(sql_row[0]);
			r->point   = atoi(sql_row[1]);
			if(sql_row[2]) {
				strncpy(r->name, sql_row[2], 24);
				r->name[23] = '\0';	// force \0 terminal
			} else {
				printf("char_build_ranking: char_name not found in %s (ID = %d, Rank = %d)\n", ranking_reg[i], r->char_id, j + 1);
				memcpy(ranking_data[i][j].name, unknown_char_name, 24);
			}
		}
		sqldbs_free_result(&mysql_handle);
	}

	if(result == false) {
		printf("char_build_ranking: can't build ranking !!\n");
		memset(&ranking_data, 0, sizeof(ranking_data));
	}

	return result;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
static int char_db_final(void *key, void *data, va_list ap)
{
	struct mmo_chardata *p = (struct mmo_chardata *)data;

	aFree(p);

	return 0;
}

void chardb_sql_final(void)
{
	numdb_final(char_db_,char_db_final);
	sqldbs_close(&mysql_handle);

	return;
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
bool chardb_sql_init(void)
{
	// DB connection initialized
	bool is_connect;

	is_connect = sqldbs_connect(&mysql_handle, char_server_ip, char_server_id, char_server_pw, char_server_db, char_server_port, char_server_charset, char_server_keepalive, "CHAR");
	if(is_connect == false)
		return false;

	char_db_ = numdb_init();

	return true;
}
