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
#include <errno.h>
#include <limits.h>
#include <ctype.h>

#include "mmo.h"
#include "malloc.h"
#include "sqldbs.h"

#include "converter.h"
#include "inter-converter.h"


struct accreg {
	int account_id;
	int reg_num;
	struct global_reg reg[ACCOUNT_REG_NUM];
};

struct scdata {
	int account_id;
	int char_id;
	short count;
	struct {
		short type;
		int val1,val2,val3,val4,tick;
	} data[MAX_STATUSCHANGE];
};

// アカウント変数を文字列から変換
static int accreg_fromstr(const char *str,struct accreg *reg)
{
	int j,v,n;
	char buf[256];
	const char *p = str;

	if( sscanf(p,"%d\t%n",&reg->account_id,&n) != 1 || reg->account_id <= 0 )
		return 1;

	for(j=0,p+=n; j<ACCOUNT_REG_NUM; j++,p+=n) {
		if( sscanf(p,"%255[^,],%d%n",buf,&v,&n) != 2 )
			break;
		strncpy(reg->reg[j].str,buf,32);
		reg->reg[j].str[31] = '\0';	// force \0 terminal
		reg->reg[j].value   = v;
		if(p[n] != ' ')
			break;
		n++;
	}
	reg->reg_num = j;

	return 0;
}

// アカウント変数を書き込み
static int accreg_tosql(struct accreg *reg)
{
	int j;
	char temp_str[128];

	sqldbs_query(&mysql_handle, "DELETE FROM `accountreg` WHERE `account_id`='%d'", reg->account_id);

	for(j=0; j<reg->reg_num; j++) {
		if(reg->reg[j].str[0] && reg->reg[j].value != 0) {
			auriga_strlcpy(temp_str, reg->reg[j].str, sizeof(temp_str));
			sqldbs_query(&mysql_handle,
				"INSERT INTO `accountreg` (`account_id`, `reg`, `value`) VALUES ('%d','%s','%d')",
				reg->account_id, temp_str, reg->reg[j].value
			);
		}
	}

	return 0;
}

// ステータス異常データを文字列から変換
static int status_fromstr(char *str, struct scdata *sc)
{
	int i,next,set,len;
	int tmp_int[6];

	if(sscanf(str,"%d,%d%n",&sc->char_id,&sc->account_id,&next) != 2)
		return 1;

	if(sc->account_id <= 0 || sc->char_id <= 0)
		return 1;

	if(str[next] == '\n' || str[next] == '\r')
		return 1;	// account_idとchar_idだけの行は有り得ない
	next++;

	for(i=0; str[next] && str[next] != '\t'; i++) {
		set = sscanf(str+next,"%d,%d,%d,%d,%d,%d%n",
			&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],&tmp_int[4],&tmp_int[5],&len);
		if(set != 6)
			return 1;
		if(i < MAX_STATUSCHANGE && tmp_int[0] >= 0 && tmp_int[0] < MAX_STATUSCHANGE) {
			sc->data[i].type = (short)tmp_int[0];
			sc->data[i].val1 = tmp_int[1];
			sc->data[i].val2 = tmp_int[2];
			sc->data[i].val3 = tmp_int[3];
			sc->data[i].val4 = tmp_int[4];
			sc->data[i].tick = tmp_int[5];
		}
		next+=len;
		if(str[next] == ' ')
			next++;
	}
	sc->count = (i < MAX_STATUSCHANGE)? i: MAX_STATUSCHANGE;

	return 0;
}

// ステータス異常データを書き込み
static int status_tosql(struct scdata *sc)
{
	int i;

	sqldbs_query(&mysql_handle, "DELETE FROM `status_change` WHERE `char_id`='%d'", sc->char_id);

	for(i=0; i<sc->count; i++) {
		sqldbs_query(&mysql_handle,
			"INSERT INTO `status_change` (`char_id`, `account_id`, `type`, `val1`, `val2`, `val3`, `val4`, `tick`) "
			"VALUES ('%d','%d','%d','%d','%d','%d','%d','%d')",
			sc->char_id, sc->account_id, sc->data[i].type,
			sc->data[i].val1, sc->data[i].val2, sc->data[i].val3, sc->data[i].val4, sc->data[i].tick
		);
	}

	return 0;
}

// メールデータを文字列から変換
static int mail_fromstr(char *str,struct mail *m)
{
	int s;
	int tmp_int[4];

	s=sscanf(str,"%d,%d,%u,%d",&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3]);

	if(s!=4)
		return 1;

	m->char_id    = tmp_int[0];
	m->account_id = tmp_int[1];
	m->rates      = (unsigned int)tmp_int[2];
	m->store      = tmp_int[3];

	return 0;
}

// メールデータを書き込み
static int mail_tosql(struct mail* m)
{
	return sqldbs_query(&mysql_handle,
		"INSERT INTO `mail` (`char_id`, `account_id`, `rates`, `store`) VALUES ('%d','%d','%u','%d') "
		"ON DUPLICATE KEY UPDATE `account_id`=VALUES(`account_id`), `rates`=VALUES(`rates`), `store`=VALUES(`store`)",
		m->char_id, m->account_id, m->rates, m->store
	) ? 0 : 1;
}

// 添付アイテムをCSVから変換（旧形式・ランダムオプション形式）
static int mailbox_item_fromstr(char *str, struct item *item)
{
	long long v[22];
	char *p = str, *end;
	int count = 0, i;

	while(*p && count < 22) {
		errno = 0;
		v[count] = strtoll(p, &end, 10);
		if(end == p || errno == ERANGE)
			return 1;
		count++;
		if(*end == '\0') {
			p = end;
			break;
		}
		if(*end != ',')
			return 1;
		p = end + 1;
		if(!*p) return 1;
	}
	if(*p || (count != 11 && count != 12 && count != 22))
		return 1;
	for(i = 0; i < count; i++) {
		int is_unsigned = i == 0 || i == 3 || (i == count - 1 && count != 11);
		if((is_unsigned && (v[i] < 0 || v[i] > UINT_MAX)) ||
		   (!is_unsigned && (v[i] < INT_MIN || v[i] > INT_MAX)))
			return 1;
	}
	if(v[2] < SHRT_MIN || v[2] > SHRT_MAX ||
	   v[4] < CHAR_MIN || v[4] > CHAR_MAX || v[5] < CHAR_MIN || v[5] > CHAR_MAX ||
	   v[6] < CHAR_MIN || v[6] > CHAR_MAX)
		return 1;
	if(count == 22) {
		for(i = 11; i <= 20; i++)
			if(v[i] < SHRT_MIN || v[i] > SHRT_MAX) return 1;
	}
	memset(item, 0, sizeof(*item));
	item->id = (unsigned int)v[0];
	item->nameid = (int)v[1];
	item->amount = (short)v[2];
	item->equip = (unsigned int)v[3];
	item->identify = (char)v[4];
	item->refine = (char)v[5];
	item->attribute = (char)v[6];
	for(i = 0; i < 4; i++) item->card[i] = (int)v[7+i];
	if(count == 22) {
		for(i = 0; i < 5; i++) {
			item->opt[i].id = (short)v[11+i*2];
			item->opt[i].val = (short)v[12+i*2];
		}
		item->limit = (unsigned int)v[21];
	} else if(count == 12) {
		item->limit = (unsigned int)v[11];
	}
	return 0;
}

// 個人メールBOXを文字列から変換
static int mailbox_fromstr(char *str,struct mail_data *md,char *body_data)
{
	char *field[16], *p, *end;
	unsigned int number, times, body_size;
	int readf, send_id = 0, nfield = 0, nitem, i, header_len = 0;
	long value;
	char extra;

	str[strcspn(str, "\r\n")] = '\0';
	for(p = str; nfield < 16; ) {
		field[nfield++] = p;
		p = strchr(p, '\t');
		if(!p) break;
		*p++ = '\0';
	}
	if(nfield < 8 || sscanf(field[0], "%u,%d%n", &number, &readf, &header_len) != 2 || number == 0)
		return 1;
	if(field[0][header_len] == ',') {
		char extra;
		if(sscanf(field[0] + header_len, ",%d%c", &send_id, &extra) != 1)
			return 1;
	} else if(field[0][header_len] != '\0') {
		return 1;
	}
	md->mail_num = number;
	md->read = readf;
	md->char_id = send_id;
	auriga_strlcpy(md->char_name, field[1], sizeof(md->char_name));
	auriga_strlcpy(md->receive_name, field[2], sizeof(md->receive_name));
	auriga_strlcpy(md->title, field[3], sizeof(md->title));
	errno = 0;
	value = strtol(field[4], &end, 10);
	if(errno == ERANGE || end == field[4] || *end || value < INT_MIN || value > INT_MAX)
		return 1;
	md->zeny = (int)value;

	if(strchr(field[5], ',')) {
		if(nfield < 8 || mailbox_item_fromstr(field[5], &md->item[0]))
			return 1;
		i = 6;
	} else {
		errno = 0;
		value = strtol(field[5], &end, 10);
		if(errno == ERANGE || end == field[5] || *end || value < 0 || value > MAIL_MAX_ITEM)
			return 1;
		nitem = (int)value;
		if(nfield < 8 + nitem)
			return 1;
		for(i = 0; i < nitem; i++) {
			if(mailbox_item_fromstr(field[6+i], &md->item[i]))
				return 1;
		}
		i = 6 + nitem;
	}
	if(sscanf(field[i], "%u%c", &times, &extra) != 1 ||
	   sscanf(field[i+1], "%u%c", &body_size, &extra) != 1 || body_size > sizeof(md->body))
		return 1;
	md->times = times;
	md->body_size = body_size;
	body_data[0] = '\0';
	if(nfield == i + 3) {
		char *body = field[i+2];
		size_t len = strlen(body), j;
		if(len != (size_t)body_size * 2 || len >= 1024)
			return 1;
		for(j = 0; j < len; j++)
			if(!isxdigit((unsigned char)body[j])) return 1;
		memcpy(body_data, body, len);
		body_data[len] = '\0';
	} else if(nfield != i + 2 || body_size != 0) {
		return 1;
	}
	return 0;
}

// 個人メールBOXを書き込み
static int mailbox_tosql(int char_id, struct mail_data *md,const char *body_data)
{
	char buf[3][256];
	int i;
	bool ok = false;

	if(!sqldbs_transaction_start(&mysql_handle))
		return 1;
	do {
		if(!sqldbs_query(&mysql_handle, "DELETE FROM `mail_attachment` WHERE `char_id` = '%d' AND `number` = '%u'", char_id, md->mail_num) ||
		   !sqldbs_query(&mysql_handle, "DELETE FROM `mail_data` WHERE `char_id` = '%d' AND `number` = '%u'", char_id, md->mail_num))
			break;
		if(!sqldbs_query(&mysql_handle,
			"INSERT INTO `mail_data` (`char_id`,`number`,`read`,`send_id`,`send_name`,`receive_name`,`title`,`times`,`size`,`body`,`zeny`) "
			"VALUES ('%d','%u','%d','%d','%s','%s','%s','%u','%u','%s','%d')",
			char_id, md->mail_num, md->read, md->char_id, strecpy(buf[0],md->char_name), strecpy(buf[1],md->receive_name),
			strecpy(buf[2],md->title), md->times, md->body_size, body_data, md->zeny))
			break;
		for(i = 0; i < MAIL_MAX_ITEM; i++) {
			struct item *it = &md->item[i];
			if(it->nameid <= 0 || it->amount <= 0) continue;
			if(!sqldbs_query(&mysql_handle,
				"INSERT INTO `mail_attachment` (`char_id`,`number`,`idx`,`id`,`nameid`,`amount`,`equip`,`identify`,`refine`,`attribute`,"
				"`card0`,`card1`,`card2`,`card3`,`opt0id`,`opt0val`,`opt1id`,`opt1val`,`opt2id`,`opt2val`,`opt3id`,`opt3val`,`opt4id`,`opt4val`,`limit`) "
				"VALUES ('%d','%u','%d','%u','%d','%d','%u','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%u')",
				char_id,md->mail_num,i,it->id,it->nameid,it->amount,it->equip,it->identify,it->refine,it->attribute,
				it->card[0],it->card[1],it->card[2],it->card[3],it->opt[0].id,it->opt[0].val,it->opt[1].id,it->opt[1].val,
				it->opt[2].id,it->opt[2].val,it->opt[3].id,it->opt[3].val,it->opt[4].id,it->opt[4].val,it->limit))
				break;
		}
		if(i == MAIL_MAX_ITEM) ok = true;
	} while(0);
	if(!sqldbs_transaction_end(&mysql_handle, ok)) return 1;
	return ok ? 0 : 1;
}

int inter_convert(void)
{
	char input, line[65536];
	int c = 0;
	FILE *fp;

	printf("\nDo you wish to convert your Account Registered Variables to SQL? (y/n) : ");
	input = getchar();
	if(input == 'y' || input == 'Y') {
		struct accreg reg;
		printf("\nConverting Account Registered Variables...\n");
		fp = fopen(account_reg_txt,"r");
		if(fp == NULL) {
			printf("cant't read : %s\n",account_reg_txt);
			return 1;
		}
		while(fgets(line, sizeof(line)-1, fp)) {
			c++;
			memset(&reg, 0, sizeof(reg));
			if(accreg_fromstr(line, &reg) == 0 && reg.account_id > 0) {
				accreg_tosql(&reg);
			} else {
				printf("accreg: broken data [%s] line %d\n", account_reg_txt, c);
			}
		}
		fclose(fp);
	}
	while(getchar() != '\n');

	c = 0;
	printf("\nDo you wish to convert your Status Change Data to SQL? (y/n) : ");
	input = getchar();
	if(input == 'y' || input == 'Y') {
		struct scdata sc;
		printf("\nConverting Status Change Data...\n");
		fp = fopen(scdata_txt,"r");
		if(fp == NULL) {
			printf("cant't read : %s\n",scdata_txt);
			return 1;
		}
		while(fgets(line, sizeof(line)-1, fp)) {
			c++;
			memset(&sc, 0, sizeof(sc));
			if(status_fromstr(line, &sc) == 0) {
				status_tosql(&sc);
			} else {
				printf("status: broken data [%s] line %d\n", scdata_txt, c);
			}
		}
		fclose(fp);
	}
	while(getchar() != '\n');

	c = 0;
	printf("\nDo you wish to convert your Mail Data to SQL? (y/n) : ");
	input = getchar();
	if(input == 'y' || input == 'Y') {
		struct mail m;
		struct mail_data md;
		int list_num=0, list_size, i;
		int *charid_list, *store_list;

		printf("\nConverting Mail Data...\n");

		// mail.txt
		fp = fopen(mail_txt,"r");
		if(fp == NULL) {
			printf("cant't read : %s\n",mail_txt);
			return 1;
		}
		list_size = 256;
		charid_list = (int *)aCalloc(list_size, sizeof(int));
		store_list = (int *)aCalloc(list_size, sizeof(int));
		while(fgets(line, sizeof(line)-1, fp)) {
			c++;
			memset(&m, 0, sizeof(m));
			if(mail_fromstr(line, &m) == 0) {
				if(mail_tosql(&m) != 0) {
					fclose(fp);
					aFree(charid_list);
					aFree(store_list);
					return 1;
				}
				if(list_num >= list_size) {
					list_size += 256;
					charid_list = (int *)aRealloc(charid_list, list_size*sizeof(int));
					store_list = (int *)aRealloc(store_list, list_size*sizeof(int));
					memset(charid_list+(list_size-256), 0, 256*sizeof(int));
				}
				store_list[list_num] = m.store;
				charid_list[list_num++] = m.char_id;	// キャラIDをリストに保存
			} else {
				printf("mail: broken data [%s] line %d\n", mail_txt, c);
			}
		}
		fclose(fp);

		// mail_data
		for(i=0; i<list_num; i++) {
			char filename[1056];
			unsigned int last = 0;
			snprintf(filename, sizeof(filename), "%s%d.txt", mail_dir, charid_list[i]);
			fp = fopen(filename,"r");
			if(fp == NULL) {
				if(errno == ENOENT && store_list[i] == 0)
					continue;
				printf("cant't read : %s\n",filename);
				aFree(charid_list);
				aFree(store_list);
				return 1;
			}
			c = 0;
			while(fgets(line, sizeof(line), fp)) {
				char body_data[1024];	// bodyはバイナリデータのままSQLに流し込むのでUNHEXしない
				c++;
				memset(&md, 0, sizeof(md));
				if(mailbox_fromstr(line, &md, body_data) == 0) {
					if(mailbox_tosql(charid_list[i], &md, body_data) != 0) {
						printf("mailbox: SQL write failed [%s] line %d\n", filename, c);
						fclose(fp);
						aFree(charid_list);
						aFree(store_list);
						return 1;
					}
					if(md.mail_num > last)
						last = md.mail_num;
				} else {
					printf("mailbox: broken data [%s] line %d\n", filename, c);
					fclose(fp);
					aFree(charid_list);
					aFree(store_list);
					return 1;
				}
			}
			if(ferror(fp)) {
				fclose(fp);
				aFree(charid_list);
				aFree(store_list);
				return 1;
			}
			fclose(fp);
			if(!sqldbs_query(&mysql_handle, "UPDATE `mail` SET `store` = '%d', `rates` = GREATEST(`rates`, '%u') WHERE `char_id` = '%d'", c, last, charid_list[i])) {
				aFree(charid_list);
				aFree(store_list);
				return 1;
			}
		}
		aFree(charid_list);
		aFree(store_list);
	}
	while(getchar() != '\n');

	return 0;
}
