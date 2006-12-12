// $Id: char-converter.c,v 1.1 2005/03/21 12:00:14 aboon Exp $
// original : char2.c 2003/03/14 11:58:35 Rev.1.5

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "converter.h"
#include "char-converter.h"
#include "../common/mmo.h"
#include "../common/db.h"
#include "../common/malloc.h"

#ifdef MEMWATCH
#include "memwatch.h"
#endif


int char_sql_saveitem(struct item *item, int max, int id, int tableswitch) {
	int i;
	const char *tablename;
	const char *selectoption;
	char *p;
	char sep = ' ';

	switch (tableswitch) {
	case TABLE_INVENTORY:
		tablename    = "inventory"; // no need for sprintf here as *_db are char*.
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
	sprintf(tmp_sql,"DELETE FROM `%s` WHERE `%s`='%d'",tablename,selectoption,id);
	if(mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (delete `%s`)- %s\n",tablename,mysql_error(&mysql_handle));
	}

	p  = tmp_sql;
	p += sprintf(
		p,"INSERT INTO `%s`(`%s`, `nameid`, `amount`, `equip`, `identify`, `refine`, "
		"`attribute`, `card0`, `card1`, `card2`, `card3` ) VALUES",tablename,selectoption
	);

	for(i = 0 ; i < max ; i++) {
		if(item[i].nameid) {
			p += sprintf(
				p,"%c('%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d')",
				sep,id,item[i].nameid,item[i].amount,item[i].equip,item[i].identify,
				item[i].refine,item[i].attribute,item[i].card[0],item[i].card[1],
				item[i].card[2],item[i].card[3]
			);
			sep = ',';
		}
	}
	if(sep == ',') {
		if(mysql_query(&mysql_handle, tmp_sql)) {
			printf("DB server Error (INSERT `%s`)- %s\n", tablename, mysql_error(&mysql_handle));
		}
	}

	return 0;
}

int inter_pet_fromstr(char *str, struct s_pet *p)
{
	int s;
	int tmp_int[16];
	char tmp_str[256];

	s=sscanf(str,"%d, %d,%[^\t]\t%d, %d, %d, %d, %d, %d, %d, %d, %d", &tmp_int[0], &tmp_int[1], tmp_str, &tmp_int[2],
		&tmp_int[3], &tmp_int[4], &tmp_int[5], &tmp_int[6], &tmp_int[7], &tmp_int[8], &tmp_int[9], &tmp_int[10]);

	if(s!=12)
		return 1;

	p->pet_id = tmp_int[0];
	p->class  = tmp_int[1];
	memcpy(p->name, tmp_str, 24);
	p->account_id = tmp_int[2];
	p->char_id = tmp_int[3];
	p->level = tmp_int[4];
	p->egg_id = tmp_int[5];
	p->equip = tmp_int[6];
	p->intimate = tmp_int[7];
	p->hungry = tmp_int[8];
	p->rename_flag = tmp_int[9];
	p->incubate = tmp_int[10];

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
//---------------------------------------------------------
int inter_pet_tosql(int pet_id, struct s_pet *p) {
	//`pet` (`pet_id`, `class`,`name`,`account_id`,`char_id`,`level`,`egg_id`,`equip`,`intimate`,`hungry`,`rename_flag`,`incubate`)

	char tmp_sql[65535];
	char t_name[256];
	MYSQL_RES* 	sql_res ;
	MYSQL_ROW	sql_row ;

	strecpy (t_name, p->name);
	if(p->hungry < 0)
		p->hungry = 0;
	else if(p->hungry > 100)
		p->hungry = 100;
	if(p->intimate < 0)
		p->intimate = 0;
	else if(p->intimate > 1000)
		p->intimate = 1000;
	sprintf(tmp_sql,"SELECT * FROM `pet` WHERE `pet_id`='%d'",pet_id);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
			printf("DB server Error - %s\n", mysql_error(&mysql_handle) );
	}
	sql_res = mysql_store_result(&mysql_handle) ;
	sql_row = mysql_fetch_row(sql_res);	//row fetching
	if (!sql_row) //no row -> insert
		sprintf(tmp_sql,"INSERT INTO `pet` (`pet_id`, `class`,`name`,`account_id`,`char_id`,`level`,`egg_id`,`equip`,`intimate`,`hungry`,`rename_flag`,`incubate`) VALUES ('%d', '%d', '%s', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d')",
			p->pet_id, p->class, t_name, p->account_id, p->char_id, p->level, p->egg_id,
			p->equip, p->intimate, p->hungry, p->rename_flag, p->incubate);
	else //row reside -> updating
		sprintf(tmp_sql, "UPDATE `pet` SET `class`='%d',`name`='%s',`account_id`='%d',`char_id`='%d',`level`='%d',`egg_id`='%d',`equip`='%d',`intimate`='%d',`hungry`='%d',`rename_flag`='%d',`incubate`='%d' WHERE `pet_id`='%d'",
			p->class,  t_name, p->account_id, p->char_id, p->level, p->egg_id,
			p->equip, p->intimate, p->hungry, p->rename_flag, p->incubate, p->pet_id);
	mysql_free_result(sql_res) ; //resource free
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error - %s\n", mysql_error(&mysql_handle) );
	}

	return 0;
}

// char to storage
int storage_fromstr(char *str, struct storage *p)
{
	int tmp_int[256];
	int set, next, len, i;

	set=sscanf(str,"%d, %d%n", &tmp_int[0], &tmp_int[1], &next);
	p->storage_amount=tmp_int[1];

	if(set!=2)
		return 0;
	if(str[next]=='\n' || str[next]=='\r')
		return 1;
	next++;
	for(i=0;str[next] && str[next]!='\t';i++){
		if(sscanf(str + next, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d%n",
		      &tmp_int[0], &tmp_int[1], &tmp_int[2], &tmp_int[3],
		      &tmp_int[4], &tmp_int[5], &tmp_int[6],
		      &tmp_int[7], &tmp_int[8], &tmp_int[9], &tmp_int[10], &len) == 11) {

			if(i < MAX_STORAGE) {
				p->storage[i].id = tmp_int[0];
				p->storage[i].nameid = tmp_int[1];
				p->storage[i].amount = tmp_int[2];
				p->storage[i].equip = tmp_int[3];
				p->storage[i].identify = tmp_int[4];
				p->storage[i].refine = tmp_int[5];
				p->storage[i].attribute = tmp_int[6];
				p->storage[i].card[0] = tmp_int[7];
				p->storage[i].card[1] = tmp_int[8];
				p->storage[i].card[2] = tmp_int[9];
				p->storage[i].card[3] = tmp_int[10];
			}
			next += len;
			if (str[next] == ' ')
				next++;
		}

		else return 0;
	}
	return 1;
}

/////////////////////////////////
int mmo_char_fromstr(char *str, struct mmo_chardata *p) {
	char tmp_str[256];
	int tmp_int[256];
	int set, next, len, i;

	// 1882以降の形式読み込み
	set=sscanf(str,"%d\t%d,%d\t%[^\t]\t%d,%d,%d\t%d,%d,%d\t%d,%d,%d,%d\t%d,%d,%d,%d,%d,%d\t%d,%d"
		"\t%d,%d,%d\t%d,%d,%d,%d\t%d,%d,%d\t%d,%d,%d,%d,%d"
		"\t%[^,],%d,%d\t%[^,],%d,%d,%d,%d,%d,%d%n",
		&tmp_int[0],&tmp_int[1],&tmp_int[2],p->st.name, //
		&tmp_int[3],&tmp_int[4],&tmp_int[5],
		&tmp_int[6],&tmp_int[7],&tmp_int[8],
		&tmp_int[9],&tmp_int[10],&tmp_int[11],&tmp_int[12],
		&tmp_int[13],&tmp_int[14],&tmp_int[15],&tmp_int[16],&tmp_int[17],&tmp_int[18],
		&tmp_int[19],&tmp_int[20],
		&tmp_int[21],&tmp_int[22],&tmp_int[23], //
		&tmp_int[24],&tmp_int[25],&tmp_int[26],&tmp_int[43],
		&tmp_int[27],&tmp_int[28],&tmp_int[29],
		&tmp_int[30],&tmp_int[31],&tmp_int[32],&tmp_int[33],&tmp_int[34],
		p->st.last_point.map,&tmp_int[35],&tmp_int[36], //
		p->st.save_point.map,&tmp_int[37],&tmp_int[38],&tmp_int[39],&tmp_int[40],&tmp_int[41],&tmp_int[42],&next
		);

	if (set != 47)
		return 0;	// 1881以前の古い形式はサポートしない

	p->st.char_id = tmp_int[0];
	p->st.account_id = tmp_int[1];
	p->st.char_num = tmp_int[2];
	p->st.class    = tmp_int[3];
	p->st.base_level = tmp_int[4];
	p->st.job_level = tmp_int[5];
	p->st.base_exp = tmp_int[6];
	p->st.job_exp = tmp_int[7];
	p->st.zeny = tmp_int[8];
	p->st.hp = tmp_int[9];
	p->st.max_hp = tmp_int[10];
	p->st.sp = tmp_int[11];
	p->st.max_sp = tmp_int[12];
	p->st.str = tmp_int[13];
	p->st.agi = tmp_int[14];
	p->st.vit = tmp_int[15];
	p->st.int_ = tmp_int[16];
	p->st.dex = tmp_int[17];
	p->st.luk = tmp_int[18];
	p->st.status_point = tmp_int[19];
	p->st.skill_point = tmp_int[20];
	p->st.option = tmp_int[21];
	p->st.karma = tmp_int[22];
	p->st.manner = tmp_int[23];
	p->st.party_id = tmp_int[24];
	p->st.guild_id = tmp_int[25];
	p->st.pet_id = tmp_int[26];
	p->st.hair = tmp_int[27];
	p->st.hair_color = tmp_int[28];
	p->st.clothes_color = tmp_int[29];
	p->st.weapon = tmp_int[30];
	p->st.shield = tmp_int[31];
	p->st.head_top = tmp_int[32];
	p->st.head_mid = tmp_int[33];
	p->st.head_bottom = tmp_int[34];
	p->st.last_point.x = tmp_int[35];
	p->st.last_point.y = tmp_int[36];
	p->st.save_point.x = tmp_int[37];
	p->st.save_point.y = tmp_int[38];
	p->st.partner_id 	= tmp_int[39];
	p->st.parent_id[0] = tmp_int[40];
	p->st.parent_id[1] = tmp_int[41];
	p->st.baby_id 		= tmp_int[42];
	p->st.homun_id     = tmp_int[43];

	if (str[next] == '\n' || str[next] == '\r')
		return 1;	// 新規データ

	next++;

	for(i = 0; str[next] && str[next] != '\t'; i++) {
		set=sscanf(str+next,"%[^,],%d,%d%n",tmp_str,&tmp_int[0],&tmp_int[1],&len);
		if(set!=3)
			return 0;
		if(i < MAX_PORTAL_MEMO) {
			strncpy(p->st.memo_point[i].map, tmp_str, 24);
			p->st.memo_point[i].x=tmp_int[0];
			p->st.memo_point[i].y=tmp_int[1];
		}
		next+=len;
		if(str[next]==' ')
			next++;
	}

	next++;

	for(i = 0; str[next] && str[next] != '\t'; i++) {
		if(sscanf(str + next, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d%n",
		          &tmp_int[0], &tmp_int[1], &tmp_int[2], &tmp_int[3],
		          &tmp_int[4], &tmp_int[5], &tmp_int[6],
		          &tmp_int[7], &tmp_int[8], &tmp_int[9], &tmp_int[10], &len) == 11) {
			tmp_int[11] = 0; // broken doesn't exist in this version -> 0
		} else // invalid structure
			return 0;
		if(i < MAX_INVENTORY) {
			p->st.inventory[i].id = tmp_int[0];
			p->st.inventory[i].nameid = tmp_int[1];
			p->st.inventory[i].amount = tmp_int[2];
			p->st.inventory[i].equip = tmp_int[3];
			p->st.inventory[i].identify = tmp_int[4];
			p->st.inventory[i].refine = tmp_int[5];
			p->st.inventory[i].attribute = tmp_int[6];
			p->st.inventory[i].card[0] = tmp_int[7];
			p->st.inventory[i].card[1] = tmp_int[8];
			p->st.inventory[i].card[2] = tmp_int[9];
			p->st.inventory[i].card[3] = tmp_int[10];
		}
		next += len;
		if (str[next] == ' ')
			next++;
	}

	next++;

	for(i = 0; str[next] && str[next] != '\t'; i++) {
		if (sscanf(str + next, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d%n",
		           &tmp_int[0], &tmp_int[1], &tmp_int[2], &tmp_int[3],
		           &tmp_int[4], &tmp_int[5], &tmp_int[6],
		           &tmp_int[7], &tmp_int[8], &tmp_int[9], &tmp_int[10], &len) == 11) {
			tmp_int[11] = 0; // broken doesn't exist in this version -> 0
		} else // invalid structure
			return 0;
		if(i < MAX_CART) {
			p->st.cart[i].id = tmp_int[0];
			p->st.cart[i].nameid = tmp_int[1];
			p->st.cart[i].amount = tmp_int[2];
			p->st.cart[i].equip = tmp_int[3];
			p->st.cart[i].identify = tmp_int[4];
			p->st.cart[i].refine = tmp_int[5];
			p->st.cart[i].attribute = tmp_int[6];
			p->st.cart[i].card[0] = tmp_int[7];
			p->st.cart[i].card[1] = tmp_int[8];
			p->st.cart[i].card[2] = tmp_int[9];
			p->st.cart[i].card[3] = tmp_int[10];
		}
		next += len;
		if (str[next] == ' ')
			next++;
	}

	next++;

	for(i = 0; str[next] && str[next] != '\t'; i++) {
		set = sscanf(str + next, "%d,%d%n", &tmp_int[0], &tmp_int[1], &len);
		if (set != 2)
			return 0;
		if(tmp_int[0] >= 0 && tmp_int[0] < MAX_SKILL) {
			p->st.skill[tmp_int[0]].id = tmp_int[0];
			p->st.skill[tmp_int[0]].lv = tmp_int[1];
		}
		next += len;
		if (str[next] == ' ')
			next++;
	}

	next++;

	for(i=0;str[next] && str[next]!='\t';i++){
		set=sscanf(str+next,"%[^,],%d%n",tmp_str,&tmp_int[0],&len);
		if(set!=2) {
			// because some scripts are not correct, the str can be "". So, we must check that.
			// If it's, we must not refuse the character, but just this REG value.
			// Character line will have something like: nov_2nd_cos,9 ,9 nov_1_2_cos_c,1 (here, ,9 is not good)
			if (str[next] == ',' && sscanf(str + next, ",%d%n", &p->reg.global[i].value, &len) == 1)
				i--;
			else
				return 0;
		}
		if(i < GLOBAL_REG_NUM) {
			strncpy(p->reg.global[i].str, tmp_str, 32);
			p->reg.global[i].value = tmp_int[0];
		}
		next+=len;
		if(str[next]==' ')
			next++;
	}
	p->reg.global_num = (i < GLOBAL_REG_NUM)? i: GLOBAL_REG_NUM;
	next++;

	for(i=0;str[next] && str[next]!='\t' && str[next]!='\n' && str[next]!='\r';i++){ //friend実装以前のathena.txt互換のため一応'\n'チェック
		set=sscanf(str+next,"%d,%d%n",&tmp_int[0],&tmp_int[1],&len); // name は後で解決する
		if(set!=2)
			return 0;
		if(i < MAX_FRIEND) {
			p->st.friend_data[i].account_id = tmp_int[0];
			p->st.friend_data[i].char_id = tmp_int[1];
		}
		next+=len;
		if(str[next]==' ')
			next++;
	}
	p->st.friend_num = (i < MAX_FRIEND)? i: MAX_FRIEND;
	next++;

	for(i = 0; str[next] && str[next] != '\t' && str[next] != '\n' && str[next] != '\r'; i++) {
		set=sscanf(str+next,"%[^,],%d%n",tmp_str,&tmp_int[0],&len);
		if(set!=2)
			return 0;
		if(tmp_int[0] >= 0 && tmp_int[0] < 3)
			strncpy(p->st.feel_map[tmp_int[0]], tmp_str, 24);
		next+=len;
		if(str[next]==' ')
			next++;
	}

	return 1;
}

//==========================================================================================================
int mmo_char_tosql(int char_id, struct mmo_chardata *p){
	char buf[256];
	int i;

	//`char`( `char_id`,`account_id`,`char_num`,`name`,`class`,`base_level`,`job_level`,`base_exp`,`job_exp`,`zeny`, //9
	//`str`,`agi`,`vit`,`int`,`dex`,`luk`, //15
	//`max_hp`,`hp`,`max_sp`,`sp`,`status_point`,`skill_point`, //21
	//`option`,`karma`,`manner`,`party_id`,`guild_id`,`pet_id`, //27
	//`hair`,`hair_color`,`clothes_color`,`weapon`,`shield`,`head_top`,`head_mid`,`head_bottom`, //35
	//`last_map`,`last_x`,`last_y`,`save_map`,`save_x`,`save_y`,`partner_id`, `parent_id`,`parent_id2`,`baby_id`)

	sprintf(tmp_sql,"DELETE FROM `char` WHERE `char_id`='%d'",char_id);
	if(mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (delete `char`)- %s\n",mysql_error(&mysql_handle));
	}
	sprintf(tmp_sql ,"INSERT INTO `char` SET `char_id`='%d', `account_id`='%d', `char_num`='%d', `name`='%s', `class`='%d', `base_level`='%d', `job_level`='%d',"
		"`base_exp`='%d', `job_exp`='%d', `zeny`='%d',"
		"`max_hp`='%d',`hp`='%d',`max_sp`='%d',`sp`='%d',`status_point`='%d',`skill_point`='%d',"
		"`str`='%d',`agi`='%d',`vit`='%d',`int`='%d',`dex`='%d',`luk`='%d',"
		"`option`='%d',`karma`='%d',`manner`='%d',`party_id`='%d',`guild_id`='%d',`pet_id`='%d',"
		"`hair`='%d',`hair_color`='%d',`clothes_color`='%d',`weapon`='%d',`shield`='%d',`head_top`='%d',`head_mid`='%d',`head_bottom`='%d',"
		"`last_map`='%s',`last_x`='%d',`last_y`='%d',`save_map`='%s',`save_x`='%d',`save_y`='%d',"
		"`partner_id` = '%d', `parent_id` = '%d', `parent_id2` = '%d', `baby_id` = '%d', `homun_id` = '%d'",
		char_id,p->st.account_id,p->st.char_num,strecpy(buf,p->st.name),p->st.class , p->st.base_level, p->st.job_level,
		p->st.base_exp, p->st.job_exp, p->st.zeny,
		p->st.max_hp, p->st.hp, p->st.max_sp, p->st.sp, p->st.status_point, p->st.skill_point,
		p->st.str, p->st.agi, p->st.vit, p->st.int_, p->st.dex, p->st.luk,
		p->st.option, p->st.karma, p->st.manner, p->st.party_id, p->st.guild_id, p->st.pet_id,
		p->st.hair, p->st.hair_color, p->st.clothes_color,
		p->st.weapon, p->st.shield, p->st.head_top, p->st.head_mid, p->st.head_bottom,
		p->st.last_point.map, p->st.last_point.x, p->st.last_point.y,
		p->st.save_point.map, p->st.save_point.x, p->st.save_point.y,
		p->st.partner_id , p->st.parent_id[0] ,p->st.parent_id[1] , p->st.baby_id, p->st.homun_id
	);

	if(mysql_query(&mysql_handle, tmp_sql) ) {
			printf("DB server Error (update `char`)- %s\n", mysql_error(&mysql_handle) );
	}

	//`memo` (`memo_id`,`char_id`,`type`,`map`,`x`,`y`)
	sprintf(tmp_sql,"DELETE FROM `memo` WHERE `type`='W' && `char_id`='%d'",char_id);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
			printf("DB server Error (delete `memo`)- %s\n", mysql_error(&mysql_handle) );
	}

	//insert here.
	for(i = 0; i < MAX_PORTAL_MEMO; i++) {
		if(p->st.memo_point[i].map[0]){
			sprintf(tmp_sql,"INSERT INTO `memo`(`char_id`,`type`,`map`,`x`,`y`) VALUES ('%d', 'W', '%s', '%d', '%d')",
				char_id, strecpy(buf,p->st.memo_point[i].map), p->st.memo_point[i].x, p->st.memo_point[i].y);
			if(mysql_query(&mysql_handle, tmp_sql) )
				printf("DB server Error (insert `memo`)- %s\n", mysql_error(&mysql_handle) );
		}
	}

	char_sql_saveitem(p->st.inventory,MAX_INVENTORY,p->st.char_id,TABLE_INVENTORY);
	char_sql_saveitem(p->st.cart     ,MAX_CART     ,p->st.char_id,TABLE_CART);

	//`skill` (`char_id`, `id`, `lv`)
	sprintf(tmp_sql,"DELETE FROM `skill` WHERE `char_id`='%d'",char_id);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
			printf("DB server Error (delete `skill`)- %s\n", mysql_error(&mysql_handle) );
	}

	//insert here.
	for(i=0;i<MAX_SKILL;i++){
		if(p->st.skill[i].id){
			if (p->st.skill[i].id && p->st.skill[i].flag!=1) {
				sprintf(tmp_sql,"INSERT INTO `skill`(`char_id`,`id`, `lv`) VALUES ('%d', '%d', '%d')",
					char_id, p->st.skill[i].id, (p->st.skill[i].flag==0)?p->st.skill[i].lv:p->st.skill[i].flag-2);
				if(mysql_query(&mysql_handle, tmp_sql) ) {
					printf("DB server Error (insert `skill`)- %s\n", mysql_error(&mysql_handle) );
				}
			}
		}
	}
	//`global_reg_value` (`char_id`, `str`, `value`)
	sprintf(tmp_sql,"DELETE FROM `global_reg_value` WHERE `char_id`='%d'",char_id);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
			printf("DB server Error (delete `global_reg_value`)- %s\n", mysql_error(&mysql_handle) );
	}

	//insert here.
	for(i=0;i<p->reg.global_num;i++){
		if(p->reg.global[i].value !=0){
			sprintf(tmp_sql,"INSERT INTO `global_reg_value` (`char_id`, `str`, `value`) VALUES ('%d', '%s','%d')",
				char_id, strecpy(buf,p->reg.global[i].str), p->reg.global[i].value);
			if(mysql_query(&mysql_handle, tmp_sql) ) {
				printf("DB server Error (insert `global_reg_value`)- %s\n", mysql_error(&mysql_handle) );
			}
		}
	}

	// memo、拳聖の感情
	//`memo` (`memo_id`,`char_id`,`type`,`map`,`x`,`y`)
	sprintf(tmp_sql,"DELETE FROM `memo` WHERE `type`='F' AND `char_id`='%d'", char_id);
	if(mysql_query(&mysql_handle, tmp_sql)) {
			printf("DB server Error (delete `memo`)- %s\n", mysql_error(&mysql_handle));
	}

	//insert here.
	for(i = 0; i < 3; i++) {
		if(p->st.feel_map[i][0]) {
			sprintf(tmp_sql,"INSERT INTO `memo`(`char_id`,`type`,`map`,`x`) VALUES ('%d', 'F', '%s', '%d')",
				char_id, strecpy(buf,p->st.feel_map[i]), i );
			if(mysql_query(&mysql_handle, tmp_sql))
				printf("DB server Error (insert `memo`)- %s\n", mysql_error(&mysql_handle));
		}
	}

	return 0;
}

// 友達登録は名前解決が必要なので別処理
int mmo_friend_tosql(int char_id, struct mmo_charstatus *p)
{
	char buf[256];
	int i;

	//`friend` (`char_id`, `id1`, `id2`)
	sprintf(tmp_sql,"DELETE FROM `friend` WHERE `char_id`='%d'",char_id);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
			printf("DB server Error (delete `friend`)- %s\n", mysql_error(&mysql_handle) );
	}

	//insert here.
	for(i=0; i < p->friend_num; i++) {
		sprintf(tmp_sql, "INSERT INTO `friend` (`char_id`, `id1`, `id2`, `name`) VALUES ('%d', '%d', '%d', '%s')",
			p->char_id, p->friend_data[i].account_id, p->friend_data[i].char_id, strecpy(buf,p->friend_data[i].name) );
		if(mysql_query(&mysql_handle, tmp_sql)) {
			printf("DB server Error (insert `friend`)- %s\n", mysql_error(&mysql_handle));
		}
	}

	return 0;
}

//==========================================================================================================

// パーティデータの文字列からの変換
int party_fromstr(char *str,struct party *p)
{
	int i,j,s;
	int tmp_int[3];
	char tmp_str[256];

	s=sscanf(str,"%d\t%[^\t]\t%d,%d\t",&tmp_int[0],
		tmp_str,&tmp_int[1],&tmp_int[2]);
	if(s!=4)
		return 1;

	p->party_id=tmp_int[0];
	strncpy(p->name,tmp_str,24);
	p->exp=tmp_int[1];
	p->item=tmp_int[2];

	for(j=0;j<3 && str!=NULL;j++)
		str=strchr(str+1,'\t');

	for(i=0;i<MAX_PARTY;i++){
		struct party_member *m = &p->member[i];
		if(str==NULL)
			return 1;

		s=sscanf(str+1,"%d,%d\t%[^\t]\t",
			&tmp_int[0],&tmp_int[1],tmp_str);
		if(s!=3)
			return 1;

		m->account_id=tmp_int[0];
		m->leader=tmp_int[1];
		strncpy(m->name,tmp_str,sizeof(m->name));

		for(j=0;j<2 && str!=NULL;j++)
			str=strchr(str+1,'\t');
	}
	return 0;
}

int party_tosql(struct party *p) {
	int i = 0;
	int leader_id = -1;
	char t_name[64];

	for(i = 0; i < MAX_PARTY; i++) {
		if(p->member[i].account_id > 0 && p->member[i].leader) {
			leader_id = p->member[i].account_id;
			break;
		}
	}

	sprintf(tmp_sql,"DELETE FROM `party` WHERE `party_id`='%d'",p->party_id);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
			printf("DB server Error (delete `party`)- %s\n", mysql_error(&mysql_handle) );
	}
	// DBに挿入
	sprintf(
		tmp_sql,
		"INSERT INTO `%s`  (`party_id`, `name`, `exp`, `item`, `leader_id`) "
		"VALUES ('%d','%s', '%d', '%d', '%d')",
		"party",p->party_id,strecpy(t_name,p->name), p->exp, p->item,leader_id
	);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (inset `party`)- %s\n", mysql_error(&mysql_handle) );
		return 0;
	}
	return 1;
}

// ギルドデータの文字列からの変換
int guild_fromstr(char *str,struct guild *g)
{
	int i,j,c;
	int tmp_int[16];
	char tmp_str[4][256];
	char tmp_str2[4096];
	char *pstr;

	// 基本データ
	if( sscanf(str,"%d\t%[^\t]\t%[^\t]\t%d,%d,%d,%d,%d\t%[^\t]\t%[^\t]\t",&tmp_int[0],
		tmp_str[0],tmp_str[1],
		&tmp_int[1],&tmp_int[2],&tmp_int[3],&tmp_int[4],&tmp_int[5],
		tmp_str[2],tmp_str[3]) <8)
		return 1;
	g->guild_id=tmp_int[0];
	g->guild_lv=tmp_int[1];
	g->max_member=tmp_int[2];
	g->exp=tmp_int[3];
	g->skill_point=tmp_int[4];
	g->castle_id=tmp_int[5];
	memcpy(g->name,tmp_str[0],24);
	memcpy(g->master,tmp_str[1],24);
	memcpy(g->mes1,tmp_str[2],60);
	memcpy(g->mes2,tmp_str[3],120);
	g->mes1[strlen(g->mes1)-1]=0;
	g->mes2[strlen(g->mes2)-1]=0;

	for(j=0;j<6 && str!=NULL;j++)	// 位置スキップ
		str=strchr(str+1,'\t');

	// メンバー
	for(i=0;i<g->max_member;i++){
		struct guild_member *m = &g->member[i];
		if( sscanf(str+1,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\t%[^\t]\t",
			&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],&tmp_int[4],
			&tmp_int[5],&tmp_int[6],&tmp_int[7],&tmp_int[8],&tmp_int[9],
			tmp_str[0]) <11)
			return 1;
		m->account_id=tmp_int[0];
		m->char_id=tmp_int[1];
		m->hair=tmp_int[2];
		m->hair_color=tmp_int[3];
		m->gender=tmp_int[4];
		m->class=tmp_int[5];
		m->lv=tmp_int[6];
		m->exp=tmp_int[7];
		m->exp_payper=tmp_int[8];
		m->position=tmp_int[9];
		memcpy(m->name,tmp_str[0],24);

		for(j=0;j<2 && str!=NULL;j++)	// 位置スキップ
			str=strchr(str+1,'\t');
	}

	// 役職
	for(i=0;i<MAX_GUILDPOSITION;i++){
		struct guild_position *p = &g->position[i];
		if( sscanf(str+1,"%d,%d\t%[^\t]\t",
			&tmp_int[0],&tmp_int[1],tmp_str[0]) < 3)
			return 1;
		p->mode=tmp_int[0];
		p->exp_mode=tmp_int[1];
		tmp_str[0][strlen(tmp_str[0])-1]=0;
		memcpy(p->name,tmp_str[0],24);

		for(j=0;j<2 && str!=NULL;j++)	// 位置スキップ
			str=strchr(str+1,'\t');
	}

	// エンブレム
	tmp_int[1]=0;
	if( sscanf(str+1,"%d,%d,%[^\t]\t",&tmp_int[0],&tmp_int[1],tmp_str2)< 3 &&
		sscanf(str+1,"%d,%[^\t]\t",&tmp_int[0],tmp_str2) < 2)
		return 1;
	g->emblem_len=tmp_int[0];
	g->emblem_id=tmp_int[1];
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
	for(i=0;i<c;i++){
		struct guild_alliance *a = &g->alliance[i];
		if( sscanf(str+1,"%d,%d\t%[^\t]\t",
			&tmp_int[0],&tmp_int[1],tmp_str[0]) < 3)
			return 1;
		a->guild_id=tmp_int[0];
		a->opposition=tmp_int[1];
		memcpy(a->name,tmp_str[0],24);

		for(j=0;j<2 && str!=NULL;j++)	// 位置スキップ
			str=strchr(str+1,'\t');
	}

	// 追放リスト
	if( sscanf(str+1,"%d\t",&c)< 1)
		return 1;
	str=strchr(str+1,'\t');	// 位置スキップ
	for(i=0;i<c;i++){
		struct guild_explusion *e = &g->explusion[i];
		if( sscanf(str+1,"%d,%d,%d,%d\t%[^\t]\t%[^\t]\t%[^\t]\t",
			&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],
			tmp_str[0],tmp_str[1],tmp_str[2]) < 6)
			return 1;
		e->account_id=tmp_int[0];
		e->rsv1=tmp_int[1];
		e->rsv2=tmp_int[2];
		e->rsv3=tmp_int[3];
		memcpy(e->name,tmp_str[0],24);
		memcpy(e->acc,tmp_str[1],24);
		tmp_str[2][strlen(tmp_str[2])-1]=0;
		memcpy(e->mes,tmp_str[2],40);

		for(j=0;j<4 && str!=NULL;j++)	// 位置スキップ
			str=strchr(str+1,'\t');
	}

	// ギルドスキル
	for(i=0;i<MAX_GUILDSKILL;i++){
		if( sscanf(str+1,"%d,%d ",&tmp_int[0],&tmp_int[1]) <2)
			break;
		g->skill[i].id=tmp_int[0];
		g->skill[i].lv=tmp_int[1];
		str=strchr(str+1,' ');
	}
	str=strchr(str+1,'\t');

	return 0;
}

int guild_tosql(struct guild* g2) {
	int  i;
	char buf[256],buf2[256],buf3[256],buf4[256];
	char *p;
	int len=0;
	char emblem_data[8192];
	char sep;

	// basic information
	sprintf(tmp_sql, "DELETE FROM `%s` WHERE `guild_id`='%d'","guild", g2->guild_id);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (delete `guild`)- %s\n", mysql_error(&mysql_handle) );
	}
	for(i=0;i<g2->emblem_len;i++){
		len+=sprintf(emblem_data+len,"%02x",(unsigned char)(g2->emblem_data[i]));
	}
	emblem_data[len] = '\0';

	sprintf(
		tmp_sql,"INSERT INTO `%s` "
		"(`guild_id`, `name`,`master`,`guild_lv`,`connect_member`,`max_member`,`average_lv`,`exp`,"
		"`next_exp`,`skill_point`,`castle_id`,`mes1`,`mes2`,`emblem_len`,`emblem_id`,`emblem_data`) "
		"VALUES ('%d', '%s', '%s', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%s', '%s', '%d',"
		" '%d', '%s')","guild", g2->guild_id,strecpy(buf4,g2->name),strecpy(buf,g2->master),
		g2->guild_lv,g2->connect_member,g2->max_member,g2->average_lv,g2->exp,g2->next_exp,
		g2->skill_point,g2->castle_id,strecpy(buf2,g2->mes1),strecpy(buf3,g2->mes2),
		g2->emblem_len,g2->emblem_id,emblem_data
	);

	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (insert `guild`)- %s\n", mysql_error(&mysql_handle) );
	}

	sprintf(tmp_sql, "DELETE FROM `%s` WHERE `guild_id`='%d'","guild_member",g2->guild_id);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (delete `guild_member`)- %s\n", mysql_error(&mysql_handle) );
	}

	p  = tmp_sql;
	p += sprintf(
		tmp_sql,
		"INSERT INTO `%s` (`guild_id`,`account_id`,`char_id`,`hair`,`hair_color`,`gender`,"
		"`class`,`lv`,`exp`,`exp_payper`,`online`,`position`,`rsv1`,`rsv2`,`name`) VALUES",
		"guild_member"
	);
	sep = ' ';

	for(i=0;i < g2->max_member;i++) {
		if (g2->member[i].account_id>0){
			struct guild_member *m = &g2->member[i];
			p += sprintf(
				p,
				"%c('%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%s')",
				sep,g2->guild_id,m->account_id,m->char_id,m->hair,m->hair_color,m->gender,
				m->class,m->lv,m->exp,m->exp_payper,(int)m->online,m->position,0,0,
				strecpy(buf,m->name)
			);
			sep = ',';
		}
	}
	if(sep == ',') {
		if(mysql_query(&mysql_handle,tmp_sql)) {
			printf("DB server Error - %s\n", mysql_error(&mysql_handle) );
		}
	}

	sprintf(tmp_sql, "DELETE FROM `%s` WHERE `guild_id`='%d'","guild_position", g2->guild_id);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (delete `guild_position`)- %s\n", mysql_error(&mysql_handle) );
	}

	p  = tmp_sql;
	p += sprintf(
		tmp_sql,
		"INSERT INTO `%s` (`guild_id`,`position`,`name`,`mode`,`exp_mode`) VALUES",
		"guild_position"
	);
	sep = ' ';
	for(i=0;i<MAX_GUILDPOSITION;i++){
		struct guild_position *pos = &g2->position[i];
		p += sprintf(
			p,"%c('%d','%d','%s','%d','%d')",
			sep, g2->guild_id,i,strecpy(buf,pos->name),pos->mode,pos->exp_mode
		);
		sep = ',';
	}
	if(sep == ',') {
		if(mysql_query(&mysql_handle, tmp_sql) ) {
			printf("DB server Error (insert `guild_position`)- %s\n", mysql_error(&mysql_handle) );
		}
	}

	sprintf(
		tmp_sql,
		"DELETE FROM `%s` WHERE `guild_id`='%d'","guild_alliance",g2->guild_id
	);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (delete `guild_alliance`)- %s\n", mysql_error(&mysql_handle) );
	}

	p  = tmp_sql;
	p += sprintf(
		tmp_sql,
		"INSERT INTO `%s` (`guild_id`,`opposition`,`alliance_id`,`name`) VALUES",
		"guild_alliance"
	);
	sep = ' ';
	for(i=0;i<MAX_GUILDALLIANCE;i++){
		struct guild_alliance *a = &g2->alliance[i];
		if(a->guild_id>0){
			p += sprintf(
				p,
				"%c('%d','%d','%d','%s')",
				sep,g2->guild_id,a->opposition,a->guild_id,strecpy(buf,a->name)
			);
			sep = ',';
		}
	}

	if(sep == ',') {
		if(mysql_query(&mysql_handle, tmp_sql) ) {
			printf("DB server Error (insert `guild_alliance`)- %s\n", mysql_error(&mysql_handle) );
		}
	}

	sprintf(tmp_sql, "DELETE FROM `%s` WHERE `guild_id`='%d'","guild_expulsion", g2->guild_id);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (delete `guild_expulsion`)- %s\n", mysql_error(&mysql_handle) );
	}
	p  = tmp_sql;
	p += sprintf(
		tmp_sql,
		"INSERT INTO `%s` (`guild_id`,`name`,`mes`,`acc`,`account_id`,`rsv1`,`rsv2`,`rsv3`) VALUES",
		"guild_expulsion"
	);
	sep = ' ';
	for(i=0;i<MAX_GUILDEXPLUSION;i++) {
		struct guild_explusion *e = &g2->explusion[i];
		if(e->account_id>0) {
			p += sprintf(
				p,"%c('%d','%s','%s','%s','%d','%d','%d','%d')",
				sep,g2->guild_id,strecpy(buf,e->name),strecpy(buf2,e->mes),e->acc,e->account_id,
				e->rsv1,e->rsv2,e->rsv3
			);
			sep = ',';
		}
	}
	if(sep == ',') {
		if(mysql_query(&mysql_handle, tmp_sql) ) {
			printf("DB server Error (insert `guild_expulsion`)- %s\n", mysql_error(&mysql_handle) );
		}
	}

	sprintf(tmp_sql,"DELETE FROM `%s` WHERE `guild_id`='%d'","guild_skill",g2->guild_id);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (delete `guild_skill`)- %s\n", mysql_error(&mysql_handle) );
	}
	p  = tmp_sql;
	p += sprintf(
		tmp_sql,
		"INSERT INTO `%s` (`guild_id`,`id`,`lv`) VALUES",
		"guild_skill"
	);
	sep = ' ';
	for(i=0;i<MAX_GUILDSKILL;i++) {
		if (g2->skill[i].id > 0) {
			p += sprintf(
				p,"%c('%d','%d','%d')",
				sep,g2->guild_id,g2->skill[i].id,g2->skill[i].lv
			);
			sep = ',';
		}
	}
	if(sep == ',') {
		if(mysql_query(&mysql_handle, tmp_sql) ) {
			printf("DB server Error (insert `guild_skill`)- %s\n", mysql_error(&mysql_handle) );
		}
	}

	return 1;
}

int gstorage_fromstr(char *str,struct guild_storage *p)
{
	int tmp_int[11];
	int set,next,len,i;

	set=sscanf(str,"%d,%d%n",&tmp_int[0],&tmp_int[1],&next);
	p->storage_amount=tmp_int[1];

	if(set!=2)
		return 1;
	if(str[next]=='\n' || str[next]=='\r')
		return 0;
	next++;
	for(i=0;str[next] && str[next]!='\t';i++){
		set=sscanf(str+next,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d%n",
		  &tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],
		  &tmp_int[4],&tmp_int[5],&tmp_int[6],
		  &tmp_int[7],&tmp_int[8],&tmp_int[9],&tmp_int[10],&len);
		if(set!=11)
			return 1;
		if(i < MAX_GUILD_STORAGE) {
			p->storage[i].id=tmp_int[0];
			p->storage[i].nameid=tmp_int[1];
			p->storage[i].amount=tmp_int[2];
			p->storage[i].equip=tmp_int[3];
			p->storage[i].identify=tmp_int[4];
			p->storage[i].refine=tmp_int[5];
			p->storage[i].attribute=tmp_int[6];
			p->storage[i].card[0]=tmp_int[7];
			p->storage[i].card[1]=tmp_int[8];
			p->storage[i].card[2]=tmp_int[9];
			p->storage[i].card[3]=tmp_int[10];
		}
		next+=len;
		if(str[next]==' ')
			next++;
	}
	return 0;
}

int homun_fromstr(char *str,struct mmo_homunstatus *h)
{
	int i,s,next,set,len;
	int tmp_int[23];
	char tmp_str[256];

	s=sscanf(str,"%d,%d,%[^\t]\t%d,%d\t%d,%d,%d,%d,%d,%d\t%d,%d,%d,%d,%d,%d\t%d,%d\t%d,%d,%d,%d,%d%n",
		&tmp_int[0],&tmp_int[1],tmp_str,
		&tmp_int[2],&tmp_int[3],
		&tmp_int[4],&tmp_int[5],&tmp_int[6],&tmp_int[7],&tmp_int[8],&tmp_int[9],
		&tmp_int[10],&tmp_int[11],&tmp_int[12],&tmp_int[13],&tmp_int[14],&tmp_int[15],
		&tmp_int[16],&tmp_int[17],
		&tmp_int[18],&tmp_int[19],&tmp_int[20],&tmp_int[21],&tmp_int[22],&next);

	if(s!=24)
		return 1;

	h->homun_id = tmp_int[0];
	h->class = tmp_int[1];
	memcpy(h->name,tmp_str,24);
	h->account_id = tmp_int[2];
	h->char_id = tmp_int[3];
	h->base_level = tmp_int[4];
	h->base_exp = tmp_int[5];
	h->max_hp = tmp_int[6];
	h->hp = tmp_int[7];
	h->max_sp = tmp_int[8];
	h->sp = tmp_int[9];
	h->str = tmp_int[10];
	h->agi = tmp_int[11];
	h->vit = tmp_int[12];
	h->int_= tmp_int[13];
	h->dex = tmp_int[14];
	h->luk = tmp_int[15];
	h->status_point = tmp_int[16];
	h->skill_point = tmp_int[17];
	h->equip = tmp_int[18];
	h->intimate = tmp_int[19];
	h->hungry = tmp_int[20];
	h->rename_flag = tmp_int[21];
	h->incubate = tmp_int[22];
	h->option = 0;

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
		set=sscanf(str+next,"%d,%d%n",
		&tmp_int[0],&tmp_int[1],&len);
		if(set!=2)
			return 0;
		tmp_int[2] = tmp_int[0]-HOM_SKILLID;
		if(tmp_int[2] >= 0 && tmp_int[2] < MAX_HOMSKILL) {
			h->skill[tmp_int[2]].id = tmp_int[0];
			h->skill[tmp_int[2]].lv = tmp_int[1];
		}
		next+=len;
		if(str[next]==' ')
			next++;
	}
	return 0;
}

int homun_tosql(int homun_id, struct mmo_homunstatus *h){
	char name[256];
	int i;

	//`homunculus` (`homun_id`, `class`,`name`,`account_id`,`char_id`,`base_level`,`base_exp`,
	//	`max_hp`,`hp`,`max_sp`,`sp`,`str`,`agi`,`vit`,`int`,`dex`,`luk`,
	//	`status_point`,`skill_point`,`equip`,`intimate`,`hungry`,`rename_flag`,`incubate`)

	sprintf(tmp_sql,"DELETE FROM `homunculus` WHERE `homun_id`='%d'",homun_id);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (delete `homunculus`)- %s\n",mysql_error(&mysql_handle) );
	}
	sprintf(tmp_sql ,"INSERT INTO `homunculus` SET `homun_id`='%d', `class`='%d', `name`='%s', `account_id`='%d', `char_id`='%d', `base_level`='%d', `base_exp`='%d',"
		"`max_hp`='%d', `hp`='%d', `max_sp`='%d', `sp`='%d', `str`='%d',`agi`='%d',`vit`='%d',`int`='%d',`dex`='%d',`luk`='%d',"
		"`status_point`='%d',`skill_point`='%d',`equip`='%d',`intimate`='%d',`hungry`='%d',`rename_flag`='%d',`incubate`='%d'",
		homun_id, h->class, strecpy(name,h->name), h->account_id , h->char_id, h->base_level, h->base_exp,
		h->max_hp, h->hp, h->max_sp, h->sp, h->str, h->agi, h->vit, h->int_, h->dex, h->luk,
		h->status_point, h->skill_point, h->equip, h->intimate, h->hungry, h->rename_flag, h->incubate
	);

	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (insert `homunculus`)- %s\n", mysql_error(&mysql_handle) );
	}

	//`homunculus_skill` (`homun_id`, `id`, `lv`)
	sprintf(tmp_sql,"DELETE FROM `homunculus_skill` WHERE `homun_id`='%d'",homun_id);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (delete `homunculus_skill`)- %s\n", mysql_error(&mysql_handle) );
	}

	//insert here.
	for(i=0;i<MAX_HOMSKILL;i++){
		if(h->skill[i].id){
			if (h->skill[i].id && h->skill[i].flag!=1) {
				sprintf(tmp_sql,"INSERT INTO `homunculus_skill`(`homun_id`,`id`, `lv`) VALUES ('%d', '%d', '%d')",
					homun_id, h->skill[i].id, (h->skill[i].flag==0)?h->skill[i].lv:h->skill[i].flag-2);
				if(mysql_query(&mysql_handle, tmp_sql) ) {
					printf("DB server Error (insert `homunculus_skill`)- %s\n", mysql_error(&mysql_handle) );
				}
			}
		}
	}
	return 0;
}

int char_convert(void){
	char input, line[65536];
	int tmp_int[2], c;
	FILE *fp;

	c = 0;
	printf("\nDo you wish to convert your Character Database to SQL? (y/n) : ");
	input=getchar();
	if(input == 'y' || input == 'Y'){
		int char_max, char_num=0;
		int i,j;
		char buf[256];
		struct mmo_chardata *cd;
		struct linkdb_node *char_namedb;	// char.cのようにchar_txt_load() がなくて面倒なのでキャラ名リストを用意

		printf("\nConverting Character Database...\n");
		fp=fopen("save/athena.txt","r");
		if(fp==NULL)
			return 0;

		cd = (struct mmo_chardata *)aCalloc(256, sizeof(struct mmo_chardata));
		char_max = 256;
		while(fgets(line, 65535, fp)) {
			c++;
			if( sscanf(line,"%*d\t%[^,\t\n\r]",buf) == 1 && strcmp(buf,"%newid%") == 0)
				continue;
			if(char_num >= char_max) {
				char_max += 256;
				cd = (struct mmo_chardata *)aRealloc(cd, sizeof(struct mmo_chardata)*char_max);
				memset(cd + (char_max - 256), 0, 256 * sizeof(struct mmo_chardata));
			}
			if( mmo_char_fromstr(line, &cd[char_num]) ) {
				mmo_char_tosql(cd[char_num].st.char_id , &cd[char_num]);
				linkdb_replace(&char_namedb, (void*)cd[char_num].st.char_id, aStrdup(cd[char_num].st.name));
				char_num++;
			} else {
				printf("mmo_char: broken data [save/athena.txt] line %d\n",c);
			}
		}
		// 友達リストの名前を解決
		for(i=0; i<char_num; i++) {
			for(j=0; j<cd[i].st.friend_num; j++) {
				struct friend_data *frd = &cd[i].st.friend_data[j];
				const char *name = (char*)linkdb_search(&char_namedb, (void*)frd->char_id);
				if(name)
					strncpy(frd->name, name, 24);
				else
					strncpy(frd->name, "", 24);
				mmo_friend_tosql(cd[i].st.char_id, &cd[i].st);
			}
		}
		if(char_namedb) {	// 後始末
			struct linkdb_node *node = (struct linkdb_node *)char_namedb;
			while (node) {
				aFree(node->data);
				node = node->next;
			}
			linkdb_final(&char_namedb);
		}
		aFree(cd);
		printf("char data convert end\n");
		fclose(fp);
	}

	c = 0;
	while(getchar() != '\n');
	printf("\nDo you wish to convert your Storage Database to SQL? (y/n) : ");
	input=getchar();
	if(input == 'y' || input == 'Y') {
		struct storage p;
		printf("\nConverting Storage Database...\n");
		fp=fopen(storage_txt,"r");
		if(fp==NULL){
			printf("cant't read : %s\n",storage_txt);
			return 0;
		}
		while(fgets(line,65535,fp)){
			c++;
			if( sscanf(line,"%d,%d",&tmp_int[0],&tmp_int[1]) == 2 ) {
				memset(&p,0,sizeof(p));
				p.account_id=tmp_int[0];
				storage_fromstr(line,&p);
				char_sql_saveitem(p.storage,MAX_STORAGE,p.account_id,TABLE_STORAGE);
			}else{
				printf("int_storage: broken data [%s] line %d\n",storage_txt,c);
			}
		}
		fclose(fp);
	}

	c = 0;
	while(getchar() != '\n');
	printf("\nDo you wish to convert your Pet Database to SQL? (y/n) : ");
	input=getchar();
	if(input == 'y' || input == 'Y') {
		struct s_pet p;
		printf("\nConverting Pet Database...\n");
		if( (fp=fopen(pet_txt,"r")) ==NULL )
			return 1;
		while(fgets(line, sizeof(line), fp)){
			c++;
			memset(&p, 0, sizeof(p));
			if(inter_pet_fromstr(line, &p)==0 && p.pet_id>0){
				inter_pet_tosql(p.pet_id,&p);
			}else{
				printf("int_pet: broken data [%s] line %d\n", pet_txt, c);
			}
		}
		fclose(fp);
	}

	c = 0;
	while(getchar() != '\n');
	printf("\nDo you wish to convert your Party Database to SQL? (y/n) : ");
	input=getchar();
	if(input == 'y' || input == 'Y') {
		struct party p;
		printf("\nConverting Party Database...\n");
		if( (fp=fopen(party_txt,"r"))==NULL )
			return 1;
		while(fgets(line,sizeof(line),fp)){
			c++;
			memset(&p, 0, sizeof(p));
			if(party_fromstr(line,&p)==0 && p.party_id>0){
				party_tosql(&p);
			}else{
				printf("int_party: broken data [%s] line %d\n",party_txt,c);
			}
		}
		fclose(fp);
	}

	c = 0;
	while(getchar() != '\n');
	printf("\nDo you wish to convert your Guild Database to SQL? (y/n) : ");
	input=getchar();
	if(input == 'y' || input == 'Y') {
		struct guild g;
		printf("\nConverting Guild Database...\n");
		if( (fp=fopen(guild_txt,"r"))==NULL )
			return 1;
		while(fgets(line,sizeof(line),fp)){
			c++;
			memset(&g, 0, sizeof(g));
			if(guild_fromstr(line,&g)==0 && g.guild_id>0){
				guild_tosql(&g);
			}else{
				printf("int_guild: broken data [%s] line %d\n",guild_txt,c);
			}
		}
		fclose(fp);
	}

	c = 0;
	while(getchar() != '\n');
	printf("\nDo you wish to convert your Guild Storage Database to SQL? (y/n) : ");
	input=getchar();
	if(input == 'y' || input == 'Y') {
		struct guild_storage gs;
		printf("\nConverting Guild Storage Database...\n");
		fp=fopen(guild_storage_txt,"r");
		if(fp==NULL){
			printf("cant't read : %s\n",guild_storage_txt);
			return 1;
		}
		while(fgets(line,65535,fp)){
			c++;
			memset( &gs, 0, sizeof(gs) );
			if(sscanf(line,"%d",&tmp_int[0]) == 1)
				gs.guild_id=tmp_int[0];
			if(gs.guild_id > 0 && gstorage_fromstr(line,&gs) == 0) {
				char_sql_saveitem(gs.storage,MAX_GUILD_STORAGE,gs.guild_id,TABLE_GUILD_STORAGE);
			}
			else{
				printf("int_storage: broken data [%s] line %d\n",guild_storage_txt,c);
			}
		}
		fclose(fp);
	}

	c = 0;
	while(getchar() != '\n');
	printf("\nDo you wish to convert your Homunculus Database to SQL? (y/n) : ");
	input=getchar();
	if(input == 'y' || input == 'Y') {
		struct mmo_homunstatus h;
		printf("\nConverting Homunculus Database...\n");
		if( (fp=fopen(homun_txt,"r")) ==NULL )
			return 1;
		while(fgets(line, sizeof(line), fp)){
			c++;
			memset(&h, 0, sizeof(h));
			if(homun_fromstr(line, &h)==0 && h.homun_id>0){
				homun_tosql(h.homun_id,&h);
			}else{
				printf("int_homun: broken data [%s] line %d\n", homun_txt, c);
			}
		}
		fclose(fp);
	}
	while(getchar() != '\n');

	return 0;
}
