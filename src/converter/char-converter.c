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

// $Id: char-converter.c,v 1.1 2005/03/21 12:00:14 aboon Exp $
// original : char2.c 2003/03/14 11:58:35 Rev.1.5

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mmo.h"
#include "db.h"
#include "malloc.h"
#include "sqldbs.h"

#include "converter.h"
#include "char-converter.h"


static int char_sql_saveitem(struct item *item, int max, int id, int tableswitch)
{
	int i;
	const char *tablename;
	const char *selectoption;
	char *p, tmp_sql[65536 * 2];
	char sep = ' ';

	switch (tableswitch) {
	case TABLE_INVENTORY:
		tablename    = "inventory";
		selectoption = "char_id";
		break;
	case TABLE_CART:
		tablename    = "cart_inventory";
		selectoption = "char_id";
		break;
	case TABLE_STORAGE:
		tablename    = "storage";
		selectoption = "account_id";
		break;
	case TABLE_GUILD_STORAGE:
		tablename    = "guild_storage";
		selectoption = "guild_id";
		break;
	default:
		printf("Invalid table name!\n");
		return 1;
	}

	// delete
	sqldbs_query(&mysql_handle, "DELETE FROM `%s` WHERE `%s`='%d'", tablename, selectoption, id);

	p  = tmp_sql;
	p += sprintf(
		p,"INSERT INTO `%s`(`id`, `%s`, `nameid`, `amount`, `equip`, `identify`, `refine`, "
		"`attribute`, `card0`, `card1`, `card2`, `card3`, `limit`, `private`) VALUES",tablename,selectoption
	);

	for(i = 0 ; i < max ; i++) {
		if(item[i].nameid) {
			p += sprintf(
				p,"%c('%u','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%u','%d')",
				sep,item[i].id,id,item[i].nameid,item[i].amount,item[i].equip,item[i].identify,
				item[i].refine,item[i].attribute,item[i].card[0],item[i].card[1],
				item[i].card[2],item[i].card[3],item[i].limit,item[i].private_
			);
			sep = ',';
		}
	}
	if(sep == ',') {
		sqldbs_simplequery(&mysql_handle, tmp_sql);
	}

	return 0;
}

// キャラクターデータを文字列から変換
static int mmo_char_fromstr(char *str, struct mmo_chardata *p)
{
	char tmp_str[3][256];
	int tmp_int[52];
	int set,next,len,i,n;

	set=sscanf(str,"%d\t%d,%d\t%255[^\t]\t%d,%d,%d\t%d,%d,%d\t%d,%d,%d,%d\t%d,%d,%d,%d,%d,%d\t%d,%d"
		"\t%u,%d,%d,%d\t%d,%d,%d,%d,%d,%d\t%d,%d,%d\t%d,%d,%d,%d,%d,%d"
		"\t%255[^,],%d,%d\t%255[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d%n",
		&tmp_int[0],&tmp_int[1],&tmp_int[2],tmp_str[0],
		&tmp_int[3],&tmp_int[4],&tmp_int[5],
		&tmp_int[6],&tmp_int[7],&tmp_int[8],
		&tmp_int[9],&tmp_int[10],&tmp_int[11],&tmp_int[12],
		&tmp_int[13],&tmp_int[14],&tmp_int[15],&tmp_int[16],&tmp_int[17],&tmp_int[18],
		&tmp_int[19],&tmp_int[20],
		&tmp_int[21],&tmp_int[22],&tmp_int[23],&tmp_int[24],
		&tmp_int[25],&tmp_int[26],&tmp_int[27],&tmp_int[28],&tmp_int[29],&tmp_int[30],
		&tmp_int[31],&tmp_int[32],&tmp_int[33],
		&tmp_int[34],&tmp_int[35],&tmp_int[36],&tmp_int[37],&tmp_int[38],&tmp_int[39],
		tmp_str[1],&tmp_int[40],&tmp_int[41],
		tmp_str[2],&tmp_int[42],&tmp_int[43],&tmp_int[44],&tmp_int[45],&tmp_int[46],&tmp_int[47],&tmp_int[48],
		&tmp_int[49],&tmp_int[50],&tmp_int[51],&next
	);
	if(set != 55)
		return 1;

	strncpy(p->st.name, tmp_str[0], 24);
	strncpy(p->st.last_point.map, tmp_str[1], 24);
	strncpy(p->st.save_point.map, tmp_str[2], 24);

	// force \0 terminal
	p->st.name[23]           = '\0';
	p->st.last_point.map[23] = '\0';
	p->st.save_point.map[23] = '\0';

	p->st.char_id             = tmp_int[0];
	p->st.account_id          = tmp_int[1];
	p->st.char_num            = tmp_int[2];
	p->st.class_              = tmp_int[3];
	p->st.base_level          = tmp_int[4];
	p->st.job_level           = tmp_int[5];
	p->st.base_exp            = tmp_int[6];
	p->st.job_exp             = tmp_int[7];
	p->st.zeny                = tmp_int[8];
	p->st.hp                  = tmp_int[9];
	p->st.max_hp              = tmp_int[10];
	p->st.sp                  = tmp_int[11];
	p->st.max_sp              = tmp_int[12];
	p->st.str                 = tmp_int[13];
	p->st.agi                 = tmp_int[14];
	p->st.vit                 = tmp_int[15];
	p->st.int_                = tmp_int[16];
	p->st.dex                 = tmp_int[17];
	p->st.luk                 = tmp_int[18];
	p->st.status_point        = tmp_int[19];
	p->st.skill_point         = tmp_int[20];
	p->st.option              = (unsigned int)tmp_int[21];
	p->st.karma               = tmp_int[22];
	p->st.manner              = tmp_int[23];
	p->st.die_counter         = tmp_int[24];
	p->st.party_id            = tmp_int[25];
	p->st.guild_id            = tmp_int[26];
	p->st.pet_id              = tmp_int[27];
	p->st.homun_id            = tmp_int[28];
	p->st.merc_id             = tmp_int[29];
	p->st.elem_id             = tmp_int[30];
	p->st.hair                = tmp_int[31];
	p->st.hair_color          = tmp_int[32];
	p->st.clothes_color       = tmp_int[33];
	p->st.weapon              = tmp_int[34];
	p->st.shield              = tmp_int[35];
	p->st.robe                = tmp_int[36];
	p->st.head_top            = tmp_int[37];
	p->st.head_mid            = tmp_int[38];
	p->st.head_bottom         = tmp_int[39];
	p->st.last_point.x        = tmp_int[40];
	p->st.last_point.y        = tmp_int[41];
	p->st.save_point.x        = tmp_int[42];
	p->st.save_point.y        = tmp_int[43];
	p->st.partner_id          = tmp_int[44];
	p->st.parent_id[0]        = tmp_int[45];
	p->st.parent_id[1]        = tmp_int[46];
	p->st.baby_id             = tmp_int[47];
	p->st.delete_date         = (unsigned int)tmp_int[48];
	p->st.refuse_partyinvite  = tmp_int[49];
	p->st.show_equip          = tmp_int[50];
	p->st.font                = tmp_int[51];

	if(str[next]=='\n' || str[next]=='\r')
		return 0;	// 新規データ

	next++;
	for(i = 0; str[next] && str[next] != '\t'; i++) {
		next+=2;
		set=sscanf(str+next,"%255[^,],%d,%d%n",tmp_str[0],&tmp_int[0],&tmp_int[1],&len);
		if(set!=3)
			return 1;
		if(i < MAX_PORTAL_MEMO) {
			strncpy(p->st.memo_point[i].map, tmp_str[0], 24);
			p->st.memo_point[i].map[23] = '\0';	// force \0 terminal
			p->st.memo_point[i].x       = tmp_int[0];
			p->st.memo_point[i].y       = tmp_int[1];
		}
		next+=len;
		if(str[next]==' ')
			next++;
	}
	next++;
	for(i=0;str[next] && str[next]!='\t';i++){
		set=sscanf(str+next,"%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u,%d%n",
			&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],
			&tmp_int[4],&tmp_int[5],&tmp_int[6],
			&tmp_int[7],&tmp_int[8],&tmp_int[9],&tmp_int[10],&tmp_int[11],
			&tmp_int[12],&len);
		if(set!=13)
			return 1;
		if(i < MAX_INVENTORY) {
			p->st.inventory[i].id        = (unsigned int)tmp_int[0];
			p->st.inventory[i].nameid    = tmp_int[1];
			p->st.inventory[i].amount    = tmp_int[2];
			p->st.inventory[i].equip     = (unsigned int)tmp_int[3];
			p->st.inventory[i].identify  = tmp_int[4];
			p->st.inventory[i].refine    = tmp_int[5];
			p->st.inventory[i].attribute = tmp_int[6];
			p->st.inventory[i].card[0]   = tmp_int[7];
			p->st.inventory[i].card[1]   = tmp_int[8];
			p->st.inventory[i].card[2]   = tmp_int[9];
			p->st.inventory[i].card[3]   = tmp_int[10];
			p->st.inventory[i].limit     = (unsigned int)tmp_int[11];
			p->st.inventory[i].private_  = tmp_int[12];
		}
		next+=len;
		if(str[next]==' ')
			next++;
	}
	next++;
	for(i=0;str[next] && str[next]!='\t';i++){
		set=sscanf(str+next,"%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u,%d%n",
			&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],
			&tmp_int[4],&tmp_int[5],&tmp_int[6],
			&tmp_int[7],&tmp_int[8],&tmp_int[9],&tmp_int[10],&tmp_int[11],
			&tmp_int[12],&len);
		if(set!=13)
			return 1;
		if(i < MAX_CART) {
			p->st.cart[i].id        = (unsigned int)tmp_int[0];
			p->st.cart[i].nameid    = tmp_int[1];
			p->st.cart[i].amount    = tmp_int[2];
			p->st.cart[i].equip     = (unsigned int)tmp_int[3];
			p->st.cart[i].identify  = tmp_int[4];
			p->st.cart[i].refine    = tmp_int[5];
			p->st.cart[i].attribute = tmp_int[6];
			p->st.cart[i].card[0]   = tmp_int[7];
			p->st.cart[i].card[1]   = tmp_int[8];
			p->st.cart[i].card[2]   = tmp_int[9];
			p->st.cart[i].card[3]   = tmp_int[10];
			p->st.cart[i].limit     = (unsigned int)tmp_int[11];
			p->st.cart[i].private_  = tmp_int[12];
		}
		next+=len;
		if(str[next]==' ')
			next++;
	}
	next++;
	for(i=0;str[next] && str[next]!='\t';i++){
		set=sscanf(str+next,"%d,%d%n",&tmp_int[0],&tmp_int[1],&len);
		if(set!=2)
			return 1;
		n = tmp_int[0];
		if(n >= 0 && n < MAX_PCSKILL) {
			p->st.skill[n].id = tmp_int[0];
			p->st.skill[n].lv = tmp_int[1];
		}
		next+=len;
		if(str[next]==' ')
			next++;
	}
	next++;
	for(i=0;str[next] && str[next]!='\t';i++){
		set=sscanf(str+next,"%255[^,],%d%n",tmp_str[0],&tmp_int[0],&len);
		if(set!=2)
			return 1;
		if(i < GLOBAL_REG_NUM) {
			strncpy(p->reg.global[i].str, tmp_str[0], 32);
			p->reg.global[i].str[31] = '\0';	// force \0 terminal
			p->reg.global[i].value   = tmp_int[0];
		} else {
			printf("char_load %d: couldn't load %s (GLOBAL_REG_NUM = %d)\a\n", p->st.char_id, tmp_str[0], GLOBAL_REG_NUM);
		}
		next+=len;
		if(str[next]==' ')
			next++;
	}
	p->reg.global_num = (i < GLOBAL_REG_NUM)? i: GLOBAL_REG_NUM;
	next++;
	for(i=0;str[next] && str[next]!='\t';i++){
		set=sscanf(str+next,"%d,%d%n",&tmp_int[0],&tmp_int[1],&len); // name は後で解決する
		if(set!=2)
			return 1;
		if(i < MAX_FRIEND) {
			p->st.friend_data[i].account_id = tmp_int[0];
			p->st.friend_data[i].char_id    = tmp_int[1];
		}
		next+=len;
		if(str[next]==' ')
			next++;
	}
	p->st.friend_num = (i < MAX_FRIEND)? i: MAX_FRIEND;
	next++;
	for(i = 0; str[next] && str[next] != '\t' && str[next] != '\n' && str[next] != '\r'; i++) {
		set=sscanf(str+next,"%255[^,],%d%n",tmp_str[0],&tmp_int[0],&len);
		if(set!=2)
			return 1;
		n = tmp_int[0];
		if(n >= 0 && n < 3) {
			strncpy(p->st.feel_map[n], tmp_str[0], 24);
			p->st.feel_map[n][23] = '\0';	// force \0 terminal
		}
		next+=len;
		if(str[next]==' ')
			next++;
	}
	next++;

	for(i = 0; str[next] && str[next] != '\t' && str[next] != '\n' && str[next] != '\r'; i++) {
		set=sscanf(str+next,"%d,%d,%d,%d%n",&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],&len);
		if(set!=4)
			return 0;
		n = tmp_int[0];
		if(n >= 0 && n < MAX_HOTKEYS) {
			p->st.hotkey[n].type = (char)tmp_int[1];
			p->st.hotkey[n].id   = tmp_int[2];
			p->st.hotkey[n].lv   = (unsigned short)tmp_int[3];
		}
		next+=len;
		if(str[next]==' ')
			next++;
	}

	for(i = 0; str[next] && str[next] != '\t' && str[next] != '\n' && str[next] != '\r'; i++) {
		set=sscanf(str+next,"%d,%d,%d%n",&tmp_int[0],&tmp_int[1],&tmp_int[2],&len);
		if(set!=3) {
			return 1;
		}
		n = tmp_int[0];
		if(n >= 0 && n < MAX_MERC_TYPE) {
			p->st.merc_fame[n] = tmp_int[1];
			p->st.merc_call[n] = tmp_int[2];
		}
		next+=len;
		if(str[next]==' ')
			next++;
	}

	return 0;
}

// キャラクターデータを書き込み
static int mmo_char_tosql(int char_id, struct mmo_charstatus *st)
{
	char sep = ' ';
	char buf[256];
	char *p, tmp_sql[65536];
	int i;

	sqldbs_query(&mysql_handle, "DELETE FROM `char_data` WHERE `char_id`='%d'", char_id);

	sqldbs_query(&mysql_handle,
		"INSERT INTO `char_data` SET `char_id` = '%d', `account_id` = '%d', `char_num` = '%d', `name` = '%s', `class` = '%d', `base_level` = '%d', `job_level` = '%d',"
		"`base_exp` = '%d', `job_exp` = '%d', `zeny` = '%d',"
		"`max_hp` = '%d', `hp` = '%d', `max_sp` = '%d', `sp` = '%d', `status_point` = '%d', `skill_point` = '%d',"
		"`str` = '%d', `agi` = '%d', `vit` = '%d', `int` = '%d', `dex` = '%d', `luk` = '%d',"
		"`option` = '%u', `karma` = '%d', `manner` = '%d', `die_counter` = '%d', `party_id` = '%d', `guild_id` = '%d', `pet_id` = '%d', `homun_id` = '%d', `merc_id` = '%d', `elem_id` = '%d',"
		"`hair` = '%d', `hair_color` = '%d', `clothes_color` = '%d', `weapon` = '%d', `shield` = '%d', `robe` = '%d', `head_top` = '%d', `head_mid` = '%d', `head_bottom` = '%d',"
		"`last_map` = '%s', `last_x` = '%d', `last_y` = '%d', `save_map` = '%s', `save_x` = '%d', `save_y` = '%d',"
		"`partner_id` = '%d', `parent_id` = '%d', `parent_id2` = '%d', `baby_id` = '%d', `delete_date` = '%d', `refuse_partyinvite` = '%d', `show_equip` = '%d', `font` = '%d'",
		char_id, st->account_id, st->char_num, strecpy(buf,st->name), st->class_ , st->base_level, st->job_level,
		st->base_exp, st->job_exp, st->zeny,
		st->max_hp, st->hp, st->max_sp, st->sp, st->status_point, st->skill_point,
		st->str, st->agi, st->vit, st->int_, st->dex, st->luk,
		st->option, st->karma, st->manner, st->die_counter, st->party_id, st->guild_id, st->pet_id, st->homun_id, st->merc_id, st->elem_id,
		st->hair, st->hair_color, st->clothes_color,
		st->weapon, st->shield, st->robe, st->head_top, st->head_mid, st->head_bottom,
		st->last_point.map, st->last_point.x, st->last_point.y,
		st->save_point.map, st->save_point.x, st->save_point.y,
		st->partner_id, st->parent_id[0], st->parent_id[1], st->baby_id,
		st->delete_date, st->refuse_partyinvite, st->show_equip, st->font
	);

	// memo
	sqldbs_query(&mysql_handle, "DELETE FROM `memo` WHERE `char_id`='%d'", char_id);

	for(i = 0; i < MAX_PORTAL_MEMO; i++) {
		if(st->memo_point[i].map[0]) {
			sqldbs_query(&mysql_handle,
				"INSERT INTO `memo`(`char_id`,`index`,`map`,`x`,`y`) VALUES ('%d', '%d', '%s', '%d', '%d')",
				char_id, i, strecpy(buf,st->memo_point[i].map), st->memo_point[i].x, st->memo_point[i].y
			);
		}
	}

	// inventory
	char_sql_saveitem(st->inventory, MAX_INVENTORY, st->char_id, TABLE_INVENTORY);

	// cart
	char_sql_saveitem(st->cart, MAX_CART, st->char_id, TABLE_CART);

	// skill
	sqldbs_query(&mysql_handle, "DELETE FROM `skill` WHERE `char_id`='%d'", char_id);

	p  = tmp_sql;
	p += sprintf(p,"INSERT INTO `skill` (`char_id`, `id`, `lv`) VALUES");
	sep = ' ';
	for(i=0;i<MAX_PCSKILL;i++){
		int sk_lv = (st->skill[i].flag==0)? st->skill[i].lv: st->skill[i].flag-2;
		if(st->skill[i].id && st->skill[i].flag!=1){
			p += sprintf(p,"%c('%d','%d','%d')", sep, char_id, st->skill[i].id, sk_lv);
			sep = ',';
		}
	}
	if(sep == ',') {
		sqldbs_simplequery(&mysql_handle, tmp_sql);
	}

	// feel_info
	sqldbs_query(&mysql_handle, "DELETE FROM `feel_info` WHERE `char_id`='%d'", char_id);

	for(i = 0; i < 3; i++) {
		if(st->feel_map[i][0]) {
			sqldbs_query(&mysql_handle,
				"INSERT INTO `feel_info`(`char_id`,`map`,`lv`) VALUES ('%d', '%s', '%d')",
				char_id, strecpy(buf,st->feel_map[i]), i
			);
		}
	}

	// hotkey
	sqldbs_query(&mysql_handle, "DELETE FROM `hotkey` WHERE `char_id`='%d'", char_id);

	for(i = 0; i < MAX_HOTKEYS; i++) {
		if(st->hotkey[i].id > 0) {
			sqldbs_query(&mysql_handle,
				"INSERT INTO `hotkey`(`char_id`,`key`,`type`,`id`,`lv`) VALUES ('%d', '%d', '%d', '%d', '%d')",
				char_id, i, st->hotkey[i].type, st->hotkey[i].id, st->hotkey[i].lv
			);
		}
	}

	// mercenary
	sqldbs_query(&mysql_handle, "DELETE FROM `mercenary` WHERE `char_id`='%d'", char_id);

	for(i = 0; i < MAX_MERC_TYPE; i++) {
		if(st->merc_fame[i] > 0 || st->merc_call[i] > 0) {
			sqldbs_query(&mysql_handle,
				"INSERT INTO `mercenary`(`char_id`,`type`,`fame`,`call`) VALUES ('%d', '%d', '%d', '%d')",
				char_id, i, st->merc_fame[i], st->merc_call[i]
			);
		}
	}

	return 0;
}

// キャラクター永続変数を書き込み
static int mmo_char_reg_tosql(int char_id, int num, struct global_reg *reg)
{
	char buf[256];
	int i;

	sqldbs_query(&mysql_handle, "DELETE FROM `globalreg` WHERE `char_id`='%d'", char_id);

	for(i=0;i<num;i++){
		if(reg[i].str[0] && reg[i].value != 0) {
			sqldbs_query(&mysql_handle,
				"INSERT INTO `globalreg` (`char_id`, `reg`, `value`) VALUES ('%d', '%s', '%d')",
				char_id, strecpy(buf,reg[i].str), reg[i].value
			);
		}
	}

	return 0;
}

// 友達登録
static int mmo_friend_tosql(int char_id, struct mmo_charstatus *st)
{
	int i;

	sqldbs_query(&mysql_handle, "DELETE FROM `friend` WHERE `char_id`='%d'", char_id);

	for(i=0; i < st->friend_num; i++) {
		sqldbs_query(&mysql_handle,
			"INSERT INTO `friend` (`char_id`, `friend_account`, `friend_id`) VALUES ('%d', '%d', '%d')",
			st->char_id, st->friend_data[i].account_id, st->friend_data[i].char_id
		);
	}

	return 0;
}

// ペットデータを文字列から変換
static int pet_fromstr(char *str, struct s_pet *p)
{
	int s;
	int tmp_int[11];
	char tmp_str[256];

	s=sscanf(str,"%d,%d,%255[^\t]\t%d,%d,%d,%d,%d,%d,%d,%d,%d",
		&tmp_int[0],&tmp_int[1],tmp_str,&tmp_int[2],
		&tmp_int[3],&tmp_int[4],&tmp_int[5],&tmp_int[6],&tmp_int[7],&tmp_int[8],&tmp_int[9],&tmp_int[10]);

	if(s!=12)
		return 1;

	p->pet_id      = tmp_int[0];
	p->class_      = tmp_int[1];
	memcpy(p->name,tmp_str,24);
	p->name[23] = '\0';	// force \0 terminal
	p->account_id  = tmp_int[2];
	p->char_id     = tmp_int[3];
	p->level       = tmp_int[4];
	p->egg_id      = tmp_int[5];
	p->equip       = tmp_int[6];
	p->intimate    = tmp_int[7];
	p->hungry      = tmp_int[8];
	p->rename_flag = tmp_int[9];
	p->incubate    = tmp_int[10];

	if(p->hungry < 0)
		p->hungry = 0;
	else if(p->hungry > 100)
		p->hungry = 100;
	if(p->intimate < 0)
		p->intimate = 0;
	else if(p->intimate > 1000)
		p->intimate = 1000;

	return 0;
}

// ペットデータを書き込み
static int pet_tosql(int pet_id, struct s_pet *p)
{
	char t_name[64];

	sqldbs_query(&mysql_handle, "DELETE FROM `pet` WHERE `pet_id` = '%d'", pet_id);

	sqldbs_query(&mysql_handle,
		"INSERT INTO `pet` (`pet_id`, `class`, `name`, `account_id`, `char_id`, `level`, `egg_id`, `equip`, `intimate`, `hungry`, `rename_flag`, `incubate`) "
		"VALUES ('%d', '%d', '%s', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d')",
		p->pet_id, p->class_, strecpy(t_name,p->name), p->account_id, p->char_id, p->level, p->egg_id,
		p->equip, p->intimate, p->hungry, p->rename_flag, p->incubate
	);

	return 0;
}

// 倉庫データを文字列から変換
static int storage_fromstr(char *str, struct storage *p)
{
	int tmp_int[12];
	int set,next,len,i;

	set=sscanf(str,"%d,%d%n",&tmp_int[0],&tmp_int[1],&next);
	p->storage_amount=tmp_int[1];

	if(set!=2)
		return 1;
	if(str[next]=='\n' || str[next]=='\r')
		return 0;
	next++;
	for(i=0;str[next] && str[next]!='\t';i++){
		set=sscanf(str+next,"%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u%n",
			&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],
			&tmp_int[4],&tmp_int[5],&tmp_int[6],
			&tmp_int[7],&tmp_int[8],&tmp_int[9],&tmp_int[10],&tmp_int[11],&len);
		if(set!=12)
			return 1;
		if(i < MAX_STORAGE) {
			p->store_item[i].id        = (unsigned int)tmp_int[0];
			p->store_item[i].nameid    = tmp_int[1];
			p->store_item[i].amount    = tmp_int[2];
			p->store_item[i].equip     = (unsigned int)tmp_int[3];
			p->store_item[i].identify  = tmp_int[4];
			p->store_item[i].refine    = tmp_int[5];
			p->store_item[i].attribute = tmp_int[6];
			p->store_item[i].card[0]   = tmp_int[7];
			p->store_item[i].card[1]   = tmp_int[8];
			p->store_item[i].card[2]   = tmp_int[9];
			p->store_item[i].card[3]   = tmp_int[10];
			p->store_item[i].limit     = (unsigned int)tmp_int[11];
		}
		next+=len;
		if(str[next]==' ')
			next++;
	}
	return 0;
}

// パーティデータを文字列から変換
static int party_fromstr(char *str,struct party *p)
{
	int i,j,s;
	int tmp_int[3];
	char tmp_str[256];

	s=sscanf(str,"%d\t%255[^\t]\t%d,%d\t",
		&tmp_int[0],tmp_str,&tmp_int[1],&tmp_int[2]);
	if(s!=4)
		return 1;

	p->party_id = tmp_int[0];
	strncpy(p->name,tmp_str,24);
	p->name[23] = '\0';	// force \0 terminal
	p->exp  = tmp_int[1];
	p->item = tmp_int[2];

	for(j=0;j<3 && str!=NULL;j++)
		str=strchr(str+1,'\t');

	for(i=0;i<MAX_PARTY;i++){
		struct party_member *m = &p->member[i];
		if(str==NULL)
			return 1;
		s=sscanf(str+1,"%d,%d\t%255[^\t]\t",
			&tmp_int[0],&tmp_int[1],tmp_str);
		if(s!=3)
			return 1;

		m->account_id = tmp_int[0];
		m->leader     = tmp_int[1];
		strncpy(m->name,tmp_str,24);
		m->name[23] = '\0';	// force \0 terminal

		for(j=0;j<2 && str!=NULL;j++)
			str=strchr(str+1,'\t');
	}
	return 0;
}

// パーティデータを書き込み
static int party_tosql(struct party *p)
{
	int i = 0;
	int leader_id = -1;
	char t_name[64];

	for(i = 0; i < MAX_PARTY; i++) {
		if(p->member[i].account_id > 0 && p->member[i].leader) {
			leader_id = p->member[i].account_id;
			break;
		}
	}

	sqldbs_query(&mysql_handle, "DELETE FROM `party` WHERE `party_id`='%d'", p->party_id);

	sqldbs_query(&mysql_handle,
		"INSERT INTO `party`  (`party_id`, `name`, `exp`, `item`, `leader_id`) "
		"VALUES ('%d','%s', '%d', '%d', '%d')",
		p->party_id,strecpy(t_name,p->name), p->exp, p->item, leader_id
	);

	return 0;
}

// ギルドデータを文字列から変換
static int guild_fromstr(char *str,struct guild *g)
{
	int i,j,c;
	int tmp_int[10];
	char tmp_str[4][256];
	char tmp_str2[4097];	// binary data + 1
	char *pstr;

	// 基本データ
	if( sscanf(str,"%d\t%255[^\t]\t%255[^\t]\t%d,%d,%d,%d\t%255[^\t]\t%255[^\t]\t",
		&tmp_int[0],tmp_str[0],tmp_str[1],
		&tmp_int[1],&tmp_int[2],&tmp_int[3],&tmp_int[4],
		tmp_str[2],tmp_str[3]) != 9)
		return 1;

	g->guild_id    = tmp_int[0];
	g->guild_lv    = tmp_int[1];
	g->max_member  = tmp_int[2];
	g->exp         = tmp_int[3];
	g->skill_point = tmp_int[4];
	strncpy(g->name,tmp_str[0],24);
	strncpy(g->master,tmp_str[1],24);
	tmp_str[2][strlen(tmp_str[2])-1] = 0;
	strncpy(g->mes1,tmp_str[2],60);
	tmp_str[3][strlen(tmp_str[3])-1] = 0;
	strncpy(g->mes2,tmp_str[3],120);

	// force \0 terminal
	g->name[23]   = '\0';
	g->master[23] = '\0';
	g->mes1[59]   = '\0';
	g->mes2[119]  = '\0';

	for(j=0;j<6 && str!=NULL;j++)	// 位置スキップ
		str=strchr(str+1,'\t');

	// メンバー
	for(i=0;i<g->max_member && i<MAX_GUILD;i++){
		struct guild_member *m = &g->member[i];
		if( sscanf(str+1,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\t%255[^\t]\t",
			&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],&tmp_int[4],
			&tmp_int[5],&tmp_int[6],&tmp_int[7],&tmp_int[8],&tmp_int[9],
			tmp_str[0]) <11)
			return 1;
		m->account_id=tmp_int[0];
		m->char_id=tmp_int[1];
		m->hair=tmp_int[2];
		m->hair_color=tmp_int[3];
		m->gender=tmp_int[4];
		m->class_=tmp_int[5];
		m->lv=tmp_int[6];
		m->exp=tmp_int[7];
		m->exp_payper=tmp_int[8];
		m->position=tmp_int[9];
		strncpy(m->name,tmp_str[0],24);
		m->name[23] = '\0';	// force \0 terminal

		for(j=0;j<2 && str!=NULL;j++)	// 位置スキップ
			str=strchr(str+1,'\t');
	}

	// 役職
	for(i=0;i<MAX_GUILDPOSITION;i++){
		struct guild_position *p = &g->position[i];
		if( sscanf(str+1,"%d,%d\t%255[^\t]\t",
			&tmp_int[0],&tmp_int[1],tmp_str[0]) < 3)
			return 1;
		p->mode     = tmp_int[0];
		p->exp_mode = tmp_int[1];
		tmp_str[0][strlen(tmp_str[0])-1] = 0;
		strncpy(p->name,tmp_str[0],24);
		p->name[23] = '\0';	// force \0 terminal

		for(j=0;j<2 && str!=NULL;j++)	// 位置スキップ
			str=strchr(str+1,'\t');
	}

	// エンブレム
	tmp_int[1]=0;
	if( sscanf(str+1,"%d,%d,%4096[^\t]\t",&tmp_int[0],&tmp_int[1],tmp_str2) < 3 )
		return 1;
	g->emblem_len = tmp_int[0];
	g->emblem_id  = tmp_int[1];
	if(g->emblem_len > sizeof(tmp_str2) / 2) {
		// エンブレムのデータ長が大きすぎる
		return 1;
	}
	for(i=0,pstr=tmp_str2;i<g->emblem_len;i++,pstr+=2){
		int c1=pstr[0],c2=pstr[1],x1=0,x2=0;
		if(c1>='0' && c1<='9')x1=c1-'0';
		if(c1>='a' && c1<='f')x1=c1-'a'+10;
		if(c1>='A' && c1<='F')x1=c1-'A'+10;
		if(c2>='0' && c2<='9')x2=c2-'0';
		if(c2>='a' && c2<='f')x2=c2-'a'+10;
		if(c2>='A' && c2<='F')x2=c2-'A'+10;
		g->emblem_data[i]=(x1<<4)|x2;
	}
	str=strchr(str+1,'\t');	// 位置スキップ

	// 同盟リスト
	if( sscanf(str+1,"%d\t",&c)< 1)
		return 1;
	str=strchr(str+1,'\t');	// 位置スキップ
	for(i=0;i<c && i<MAX_GUILDALLIANCE;i++){
		struct guild_alliance *a = &g->alliance[i];
		if( sscanf(str+1,"%d,%d\t%255[^\t]\t",
			&tmp_int[0],&tmp_int[1],tmp_str[0]) < 3)
			return 1;
		a->guild_id   = tmp_int[0];
		a->opposition = tmp_int[1];
		strncpy(a->name,tmp_str[0],24);
		a->name[23] = '\0';	// force \0 terminal

		for(j=0;j<2 && str!=NULL;j++)	// 位置スキップ
			str=strchr(str+1,'\t');
	}

	// 追放リスト
	if( sscanf(str+1,"%d\t",&c)< 1)
		return 1;
	str=strchr(str+1,'\t');	// 位置スキップ
	for(i=0;i<c && i<MAX_GUILDEXPLUSION;i++){
		struct guild_explusion *e = &g->explusion[i];
		if( sscanf(str+1,"%d\t%255[^\t]\t%255[^\t]\t",
			&tmp_int[0],tmp_str[0],tmp_str[1]) != 3 )
			return 1;
		e->account_id = tmp_int[0];
		strncpy(e->name,tmp_str[0],24);
		tmp_str[1][strlen(tmp_str[1])-1] = 0;
		strncpy(e->mes,tmp_str[1],40);

		// force \0 terminal
		e->name[23] = '\0';
		e->mes[39]  = '\0';

		for(j=0;j<3 && str!=NULL;j++)	// 位置スキップ
			str=strchr(str+1,'\t');
	}

	// ギルドスキル
	for(i=0;i<MAX_GUILDSKILL;i++){
		int n;
		if( sscanf(str+1,"%d,%d ",&tmp_int[0],&tmp_int[1]) <2)
			break;
		n = tmp_int[0] - GUILD_SKILLID;
		if(n >= 0 && n < MAX_GUILDSKILL) {
			g->skill[n].id = tmp_int[0];
			g->skill[n].lv = tmp_int[1];
		}
		str=strchr(str+1,' ');
	}

	// 新ギルドスキルへ移行
	for(i=0;i<MAX_GUILDSKILL;i++)
		g->skill[i].id=GUILD_SKILLID+i;

	str=strchr(str+1,'\t');

	return 0;
}

// ギルドデータを書き込み
static int guild_tosql(struct guild* g)
{
	int  i;
	char buf[256],buf2[256],buf3[256],buf4[256];
	char tmp_sql[65536];
	char *p = tmp_sql;
	char sep;

	// 基本データ
	sqldbs_query(&mysql_handle, "DELETE FROM `guild` WHERE `guild_id`='%d'", g->guild_id);

	p += sprintf(
		tmp_sql,"INSERT INTO `guild` "
		"(`guild_id`, `name`, `master`, `guild_lv`, `connect_member`, `max_member`, `average_lv`, `exp`,"
		"`next_exp`, `skill_point`, `mes1`, `mes2`, `emblem_len`, `emblem_id`, `emblem_data`) "
		"VALUES ('%d', '%s', '%s', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%s', '%s', '%d', '%d', '",
		g->guild_id, strecpy(buf,g->name), strecpy(buf2,g->master),
		g->guild_lv, g->connect_member, g->max_member, g->average_lv, g->exp,
		g->next_exp, g->skill_point, strecpy(buf3,g->mes1), strecpy(buf4,g->mes2), g->emblem_len, g->emblem_id
	);
	for(i=0; i<g->emblem_len; i++) {
		p += sprintf(p,"%02x",(unsigned char)(g->emblem_data[i]));
	}
	p += sprintf(p,"')");

	sqldbs_simplequery(&mysql_handle, tmp_sql);

	// メンバー
	sqldbs_query(&mysql_handle, "DELETE FROM `guild_member` WHERE `guild_id`='%d'", g->guild_id);

	p  = tmp_sql;
	p += sprintf(
		tmp_sql,
		"INSERT INTO `guild_member` (`guild_id`,`account_id`,`char_id`,`hair`,`hair_color`,`gender`,"
		"`class`,`lv`,`exp`,`exp_payper`,`online`,`position`,`name`) VALUES"
	);
	sep = ' ';

	for(i=0;i < g->max_member;i++) {
		if (g->member[i].account_id>0){
			struct guild_member *m = &g->member[i];
			p += sprintf(
				p,
				"%c('%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%s')",
				sep,g->guild_id,m->account_id,m->char_id,m->hair,m->hair_color,m->gender,
				m->class_,m->lv,m->exp,m->exp_payper,(int)m->online,m->position,strecpy(buf,m->name)
			);
			sep = ',';
		}
	}
	if(sep == ',') {
		sqldbs_simplequery(&mysql_handle, tmp_sql);
	}

	// 役職
	sqldbs_query(&mysql_handle, "DELETE FROM `guild_position` WHERE `guild_id`='%d'", g->guild_id);

	p  = tmp_sql;
	p += sprintf(
		tmp_sql,
		"INSERT INTO `guild_position` (`guild_id`,`position`,`name`,`mode`,`exp_mode`) VALUES"
	);
	sep = ' ';
	for(i=0;i<MAX_GUILDPOSITION;i++){
		struct guild_position *pos = &g->position[i];
		p += sprintf(
			p,"%c('%d','%d','%s','%d','%d')",
			sep, g->guild_id,i,strecpy(buf,pos->name),pos->mode,pos->exp_mode
		);
		sep = ',';
	}
	if(sep == ',') {
		sqldbs_simplequery(&mysql_handle, tmp_sql);
	}

	// 同盟リスト
	sqldbs_query(&mysql_handle, "DELETE FROM `guild_alliance` WHERE `guild_id`='%d'", g->guild_id);

	p  = tmp_sql;
	p += sprintf(
		tmp_sql,
		"INSERT INTO `guild_alliance` (`guild_id`,`opposition`,`alliance_id`,`name`) VALUES"
	);
	sep = ' ';
	for(i=0;i<MAX_GUILDALLIANCE;i++){
		struct guild_alliance *a = &g->alliance[i];
		if(a->guild_id>0){
			p += sprintf(
				p,
				"%c('%d','%d','%d','%s')",
				sep,g->guild_id,a->opposition,a->guild_id,strecpy(buf,a->name)
			);
			sep = ',';
		}
	}
	if(sep == ',') {
		sqldbs_simplequery(&mysql_handle, tmp_sql);
	}

	// 追放リスト
	sqldbs_query(&mysql_handle, "DELETE FROM `guild_expulsion` WHERE `guild_id`='%d'", g->guild_id);

	p  = tmp_sql;
	p += sprintf(
		tmp_sql,
		"INSERT INTO `guild_expulsion` (`guild_id`,`name`,`mes`,`account_id`) VALUES"
	);
	sep = ' ';
	for(i=0;i<MAX_GUILDEXPLUSION;i++) {
		struct guild_explusion *e = &g->explusion[i];
		if(e->account_id>0) {
			p += sprintf(
				p,"%c('%d','%s','%s','%d')",
				sep,g->guild_id,strecpy(buf,e->name),strecpy(buf2,e->mes),e->account_id
			);
			sep = ',';
		}
	}
	if(sep == ',') {
		sqldbs_simplequery(&mysql_handle, tmp_sql);
	}

	// ギルドスキル
	sqldbs_query(&mysql_handle, "DELETE FROM `guild_skill` WHERE `guild_id`='%d'", g->guild_id);

	p  = tmp_sql;
	p += sprintf(
		tmp_sql,
		"INSERT INTO `guild_skill` (`guild_id`,`id`,`lv`) VALUES"
	);
	sep = ' ';
	for(i=0;i<MAX_GUILDSKILL;i++) {
		if (g->skill[i].id > 0) {
			p += sprintf(
				p,"%c('%d','%d','%d')",
				sep,g->guild_id,g->skill[i].id,g->skill[i].lv
			);
			sep = ',';
		}
	}
	if(sep == ',') {
		sqldbs_simplequery(&mysql_handle, tmp_sql);
	}

	return 0;
}

// ギルド城データを文字列から変換
static int guildcastle_fromstr(char *str,struct guild_castle *gc)
{
	int tmp_int[18];

	if( sscanf(str,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
		&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],&tmp_int[4],&tmp_int[5],&tmp_int[6],
		&tmp_int[7],&tmp_int[8],&tmp_int[9],&tmp_int[10],&tmp_int[11],&tmp_int[12],&tmp_int[13],
		&tmp_int[14],&tmp_int[15],&tmp_int[16],&tmp_int[17]) <18 )
		return 1;
	gc->castle_id           = tmp_int[0];
	gc->guild_id            = tmp_int[1];
	gc->economy             = tmp_int[2];
	gc->defense             = tmp_int[3];
	gc->triggerE            = tmp_int[4];
	gc->triggerD            = tmp_int[5];
	gc->nextTime            = tmp_int[6];
	gc->payTime             = tmp_int[7];
	gc->createTime          = tmp_int[8];
	gc->visibleC            = tmp_int[9];
	gc->guardian[0].visible = tmp_int[10];
	gc->guardian[1].visible = tmp_int[11];
	gc->guardian[2].visible = tmp_int[12];
	gc->guardian[3].visible = tmp_int[13];
	gc->guardian[4].visible = tmp_int[14];
	gc->guardian[5].visible = tmp_int[15];
	gc->guardian[6].visible = tmp_int[16];
	gc->guardian[7].visible = tmp_int[17];

	return 0;
}

// ギルド城データを書き込み
static int guildcastle_tosql(struct guild_castle *gc)
{
	sqldbs_query(&mysql_handle, "DELETE FROM `guild_castle` WHERE `castle_id` = '%d'", gc->castle_id);

	sqldbs_query(&mysql_handle,
		"INSERT INTO `guild_castle` (`castle_id`, `guild_id`, `economy`, `defense`, `triggerE`, `triggerD`, `nextTime`, `payTime`, `createTime`, "
		"`visibleC`, `visibleG0`, `visibleG1`, `visibleG2`, `visibleG3`, `visibleG4`, `visibleG5`, `visibleG6`, `visibleG7`) "
		"VALUES ('%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d')",
		gc->castle_id, gc->guild_id, gc->economy, gc->defense, gc->triggerE, gc->triggerD, gc->nextTime, gc->payTime, gc->createTime,
		gc->visibleC, gc->guardian[0].visible, gc->guardian[1].visible, gc->guardian[2].visible, gc->guardian[3].visible, gc->guardian[4].visible, gc->guardian[5].visible, gc->guardian[6].visible, gc->guardian[7].visible
	);

	return 0;
}

// ギルド倉庫データを文字列から変換
static int gstorage_fromstr(char *str,struct guild_storage *p)
{
	int tmp_int[12];
	int set,next,len,i;

	set=sscanf(str,"%d,%d%n",&tmp_int[0],&tmp_int[1],&next);
	p->storage_amount=tmp_int[1];

	if(set!=2)
		return 1;
	if(str[next]=='\n' || str[next]=='\r')
		return 0;
	next++;
	for(i=0;str[next] && str[next]!='\t';i++){
		set=sscanf(str+next,"%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u%n",
			&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],
			&tmp_int[4],&tmp_int[5],&tmp_int[6],
			&tmp_int[7],&tmp_int[8],&tmp_int[9],&tmp_int[10],&tmp_int[11],&len);
		if(set!=12)
			return 1;
		if(i < MAX_GUILD_STORAGE) {
			p->store_item[i].id        = (unsigned int)tmp_int[0];
			p->store_item[i].nameid    = tmp_int[1];
			p->store_item[i].amount    = tmp_int[2];
			p->store_item[i].equip     = (unsigned int)tmp_int[3];
			p->store_item[i].identify  = tmp_int[4];
			p->store_item[i].refine    = tmp_int[5];
			p->store_item[i].attribute = tmp_int[6];
			p->store_item[i].card[0]   = tmp_int[7];
			p->store_item[i].card[1]   = tmp_int[8];
			p->store_item[i].card[2]   = tmp_int[9];
			p->store_item[i].card[3]   = tmp_int[10];
			p->store_item[i].limit     = (unsigned int)tmp_int[11];
		}
		next+=len;
		if(str[next]==' ')
			next++;
	}
	return 0;
}

// ホムンクルスデータを文字列から変換
static int homun_fromstr(char *str,struct mmo_homunstatus *h)
{
	int i,s,next,set,len;
	int tmp_int[29];
	char tmp_str[256], buf[64];;

	s=sscanf(str,"%d,%d,%255[^\t]\t%d,%d\t%d,%d,%d,%d,%d,%d\t%d,%d,%d,%d,%d,%d\t%d,%d,%d,%d,%d,%d\t%d,%d\t%d,%d,%d,%d,%d%n",
		&tmp_int[0],&tmp_int[1],tmp_str,
		&tmp_int[2],&tmp_int[3],
		&tmp_int[4],&tmp_int[5],&tmp_int[6],&tmp_int[7],&tmp_int[8],&tmp_int[9],
		&tmp_int[10],&tmp_int[11],&tmp_int[12],&tmp_int[13],&tmp_int[14],&tmp_int[15],
		&tmp_int[16],&tmp_int[17],&tmp_int[18],&tmp_int[19],&tmp_int[20],&tmp_int[21],
		&tmp_int[22],&tmp_int[23],
		&tmp_int[24],&tmp_int[25],&tmp_int[26],&tmp_int[27],&tmp_int[28],&next);

	if(s!=30) {
		tmp_int[16] = 0;	// f_str
		tmp_int[17] = 0;	// f_agi
		tmp_int[18] = 0;	// f_vit
		tmp_int[19] = 0;	// f_int
		tmp_int[20] = 0;	// f_dex
		tmp_int[21] = 0;	// f_luk
		s=sscanf(str,"%d,%d,%255[^\t]\t%d,%d\t%d,%d,%d,%d,%d,%d\t%d,%d,%d,%d,%d,%d\t%d,%d\t%d,%d,%d,%d,%d%n",
			&tmp_int[0],&tmp_int[1],tmp_str,
			&tmp_int[2],&tmp_int[3],
			&tmp_int[4],&tmp_int[5],&tmp_int[6],&tmp_int[7],&tmp_int[8],&tmp_int[9],
			&tmp_int[10],&tmp_int[11],&tmp_int[12],&tmp_int[13],&tmp_int[14],&tmp_int[15],
			&tmp_int[22],&tmp_int[23],
			&tmp_int[24],&tmp_int[25],&tmp_int[26],&tmp_int[27],&tmp_int[28],&next
		);

		if(s!=24)
			return 1;
	}

	h->homun_id     = tmp_int[0];
	h->class_       = tmp_int[1];
	strncpy(h->name,tmp_str,24);
	h->name[23] = '\0';	// force \0 terminal
	h->account_id   = tmp_int[2];
	h->char_id      = tmp_int[3];
	h->base_level   = tmp_int[4];
	h->base_exp     = tmp_int[5];
	h->max_hp       = tmp_int[6];
	h->hp           = tmp_int[7];
	h->max_sp       = tmp_int[8];
	h->sp           = tmp_int[9];
	h->str          = tmp_int[10];
	h->agi          = tmp_int[11];
	h->vit          = tmp_int[12];
	h->int_         = tmp_int[13];
	h->dex          = tmp_int[14];
	h->luk          = tmp_int[15];
	h->f_str        = tmp_int[16];
	h->f_agi        = tmp_int[17];
	h->f_vit        = tmp_int[18];
	h->f_int        = tmp_int[19];
	h->f_dex        = tmp_int[20];
	h->f_luk        = tmp_int[21];
	h->status_point = tmp_int[22];
	h->skill_point  = tmp_int[23];
	h->equip        = tmp_int[24];
	h->intimate     = tmp_int[25];
	h->hungry       = tmp_int[26];
	h->rename_flag  = tmp_int[27];
	h->incubate     = tmp_int[28];
	h->option       = 0;
	strecpy(buf,h->name);
	if(h->hungry < 0)
		h->hungry = 0;
	else if(h->hungry > 100)
		h->hungry = 100;
	if(h->intimate < 0)
		h->intimate = 0;
	else if(h->intimate > 100000)
		h->intimate = 100000;

	if(str[next]=='\n' || str[next]=='\r')
		return 0;	// スキル情報なし

	next++;
	for(i=0;str[next] && str[next]!='\t';i++){
		int n;
		set=sscanf(str+next,"%d,%d%n",
			&tmp_int[0],&tmp_int[1],&len);
		if(set!=2)
			return 1;
		n = tmp_int[0]-HOM_SKILLID;
		if(n >= 0 && n < MAX_HOMSKILL) {
			h->skill[n].id = tmp_int[0];
			h->skill[n].lv = tmp_int[1];
		}
		next+=len;
		if(str[next]==' ')
			next++;
	}
	return 0;
}

// ホムンクルスデータを書き込み
static int homun_tosql(int homun_id, struct mmo_homunstatus *h)
{
	int i;
	char sep, *p, buf[64];
	char tmp_sql[65536];

	sqldbs_query(&mysql_handle, "DELETE FROM `homunculus` WHERE `homun_id`='%d'", homun_id);

	sqldbs_query(&mysql_handle,
		"INSERT INTO `homunculus` SET `homun_id` = '%d', `class` = '%d', `name` = '%s', `account_id` = '%d', `char_id` = '%d', `base_level` = '%d', `base_exp` = '%d',"
		"`max_hp` = '%d', `hp` = '%d', `max_sp` = '%d', `sp` = '%d', `str` = '%d', `agi` = '%d',`vit` = '%d',`int` = '%d',`dex` = '%d',`luk` = '%d',"
		"`f_str` = '%d', `f_agi` = '%d',`f_vit` = '%d',`f_int` = '%d',`f_dex` = '%d',`f_luk` = '%d',"
		"`status_point` = '%d', `skill_point` = '%d', `equip` = '%d', `intimate` = '%d', `hungry` = '%d', `rename_flag` = '%d', `incubate` = '%d'",
		homun_id, h->class_, strecpy(buf,h->name), h->account_id , h->char_id, h->base_level, h->base_exp,
		h->max_hp, h->hp, h->max_sp, h->sp, h->str, h->agi, h->vit, h->int_, h->dex, h->luk,
		h->f_str, h->f_agi, h->f_vit, h->f_int, h->f_dex, h->f_luk,
		h->status_point, h->skill_point, h->equip, h->intimate, h->hungry, h->rename_flag, h->incubate
	);

	sqldbs_query(&mysql_handle, "DELETE FROM `homunculus_skill` WHERE `homun_id`='%d'", homun_id);

	p  = tmp_sql;
	p += sprintf(tmp_sql, "INSERT INTO `homunculus_skill` (`homun_id`,`id`,`lv`) VALUES");
	sep = ' ';
	for(i=0;i<MAX_HOMSKILL;i++) {
		if(h->skill[i].id && h->skill[i].flag!=1){
			int lv = (h->skill[i].flag==0)? h->skill[i].lv: h->skill[i].flag-2;
			p += sprintf(p,"%c('%d','%d','%d')", sep,homun_id,h->skill[i].id,lv);
			sep = ',';
		}
	}
	if(sep == ',') {
		sqldbs_simplequery(&mysql_handle, tmp_sql);
	}

	return 0;
}

int char_convert(void)
{
	char input, line[65536];
	int tmp_int[2], c;
	FILE *fp;

	c = 0;
	printf("\nDo you wish to convert your Character Database to SQL? (y/n) : ");
	input = getchar();
	if(input == 'y' || input == 'Y') {
		int i, j;
		struct mmo_chardata cd;

		printf("\nConverting Character Database...\n");
		fp = fopen(char_txt,"r");
		if(fp == NULL) {
			printf("cant't read : %s\n",char_txt);
			return 1;
		}

		while(fgets(line, sizeof(line)-1, fp)) {
			c++;
			j = -1;
			if(sscanf(line,"%d\t%%newid%%%n",&i,&j) == 1 && j > 0 && (line[j] == '\n' || line[j] == '\r'))
				continue;

			memset(&cd, 0, sizeof(cd));
			if(mmo_char_fromstr(line, &cd) == 0) {
				int char_id = cd.st.char_id;
				mmo_char_tosql(char_id , &cd.st);
				mmo_char_reg_tosql(char_id, cd.reg.global_num, cd.reg.global);
				mmo_friend_tosql(char_id, &cd.st);
			} else {
				printf("mmo_char: broken data [%s] line %d\n", char_txt, c);
			}
		}
		fclose(fp);
	}
	while(getchar() != '\n');

	c = 0;
	printf("\nDo you wish to convert your Storage Database to SQL? (y/n) : ");
	input = getchar();
	if(input == 'y' || input == 'Y') {
		struct storage s;
		printf("\nConverting Storage Database...\n");
		fp = fopen(storage_txt,"r");
		if(fp == NULL) {
			printf("cant't read : %s\n",storage_txt);
			return 1;
		}
		while(fgets(line, sizeof(line)-1, fp)) {
			c++;
			memset(&s,0,sizeof(s));
			if(sscanf(line,"%d,%d",&tmp_int[0],&tmp_int[1]) == 2) {
				s.account_id = tmp_int[0];
			}
			if(s.account_id > 0 && storage_fromstr(line,&s) == 0) {
				char_sql_saveitem(s.store_item,MAX_STORAGE,s.account_id,TABLE_STORAGE);
			} else {
				printf("storage: broken data [%s] line %d\n",storage_txt,c);
			}
		}
		fclose(fp);
	}
	while(getchar() != '\n');

	c = 0;
	printf("\nDo you wish to convert your Pet Database to SQL? (y/n) : ");
	input = getchar();
	if(input == 'y' || input == 'Y') {
		struct s_pet p;
		printf("\nConverting Pet Database...\n");
		fp = fopen(pet_txt,"r");
		if(fp == NULL) {
			printf("cant't read : %s\n",pet_txt);
			return 1;
		}
		while(fgets(line, sizeof(line)-1, fp)) {
			c++;
			memset(&p, 0, sizeof(p));
			if(pet_fromstr(line, &p) == 0 && p.pet_id > 0) {
				pet_tosql(p.pet_id,&p);
			} else {
				printf("pet: broken data [%s] line %d\n", pet_txt, c);
			}
		}
		fclose(fp);
	}
	while(getchar() != '\n');

	c = 0;
	printf("\nDo you wish to convert your Party Database to SQL? (y/n) : ");
	input = getchar();
	if(input == 'y' || input == 'Y') {
		struct party p;
		printf("\nConverting Party Database...\n");
		fp = fopen(party_txt,"r");
		if(fp == NULL) {
			printf("cant't read : %s\n",party_txt);
			return 1;
		}
		while(fgets(line, sizeof(line)-1, fp)) {
			c++;
			memset(&p, 0, sizeof(p));
			if(party_fromstr(line,&p) == 0 && p.party_id > 0) {
				party_tosql(&p);
			} else {
				printf("party: broken data [%s] line %d\n",party_txt,c);
			}
		}
		fclose(fp);
	}
	while(getchar() != '\n');

	c = 0;
	printf("\nDo you wish to convert your Guild Database to SQL? (y/n) : ");
	input = getchar();
	if(input == 'y' || input == 'Y') {
		struct guild g;
		printf("\nConverting Guild Database...\n");
		fp = fopen(guild_txt,"r");
		if(fp == NULL) {
			printf("cant't read : %s\n",guild_txt);
			return 1;
		}
		while(fgets(line, sizeof(line)-1, fp)) {
			c++;
			memset(&g, 0, sizeof(g));
			if(guild_fromstr(line,&g) == 0 && g.guild_id > 0) {
				guild_tosql(&g);
			} else {
				printf("guild: broken data [%s] line %d\n",guild_txt,c);
			}
		}
		fclose(fp);
	}
	while(getchar() != '\n');

	c = 0;
	printf("\nDo you wish to convert your Guild Castle Database to SQL? (y/n) : ");
	input = getchar();
	if(input == 'y' || input == 'Y') {
		struct guild_castle gc;
		printf("\nConverting Guild Castle Database...\n");
		fp = fopen(castle_txt,"r");
		if(fp == NULL) {
			printf("cant't read : %s\n",castle_txt);
			return 1;
		}
		while(fgets(line, sizeof(line)-1, fp)) {
			c++;
			memset(&gc, 0, sizeof(gc));
			if(guildcastle_fromstr(line,&gc) == 0) {
				guildcastle_tosql(&gc);
			} else {
				printf("guildcastle: broken data [%s] line %d\n",castle_txt,c);
			}
		}
		fclose(fp);
	}
	while(getchar() != '\n');

	c = 0;
	printf("\nDo you wish to convert your Guild Storage Database to SQL? (y/n) : ");
	input = getchar();
	if(input == 'y' || input == 'Y') {
		struct guild_storage gs;
		printf("\nConverting Guild Storage Database...\n");
		fp = fopen(guild_storage_txt,"r");
		if(fp == NULL) {
			printf("cant't read : %s\n",guild_storage_txt);
			return 1;
		}
		while(fgets(line, sizeof(line)-1, fp)) {
			c++;
			memset(&gs, 0, sizeof(gs));
			if(sscanf(line,"%d,%d",&tmp_int[0],&tmp_int[1]) == 2)
				gs.guild_id = tmp_int[0];
			if(gs.guild_id > 0 && gstorage_fromstr(line,&gs) == 0) {
				char_sql_saveitem(gs.store_item,MAX_GUILD_STORAGE,gs.guild_id,TABLE_GUILD_STORAGE);
			} else {
				printf("gstorage: broken data [%s] line %d\n",guild_storage_txt,c);
			}
		}
		fclose(fp);
	}
	while(getchar() != '\n');

	c = 0;
	printf("\nDo you wish to convert your Homunculus Database to SQL? (y/n) : ");
	input = getchar();
	if(input == 'y' || input == 'Y') {
		struct mmo_homunstatus h;
		printf("\nConverting Homunculus Database...\n");
		fp = fopen(homun_txt,"r");
		if(fp == NULL) {
			printf("cant't read : %s\n",homun_txt);
			return 1;
		}
		while(fgets(line, sizeof(line)-1, fp)) {
			c++;
			memset(&h, 0, sizeof(h));
			if(homun_fromstr(line, &h) == 0 && h.homun_id > 0) {
				homun_tosql(h.homun_id,&h);
			} else {
				printf("homun: broken data [%s] line %d\n", homun_txt, c);
			}
		}
		fclose(fp);
	}
	while(getchar() != '\n');

	return 0;
}
