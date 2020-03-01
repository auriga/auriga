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
			sqldbs_query(&mysql_handle,
				"INSERT INTO `accountreg` (`account_id`, `reg`, `value`) VALUES ('%d','%s','%d')",
				reg->account_id, strecpy(temp_str,reg->reg[j].str), reg->reg[j].value
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

// メールデータの削除
static int mail_delete_fromsql(int char_id)
{
	sqldbs_query(&mysql_handle, "DELETE FROM `mail` WHERE `char_id` = '%d'", char_id);

	return 0;
}

// メールデータを書き込み
static int mail_tosql(struct mail* m)
{
	mail_delete_fromsql(m->char_id);

	// `mail` (`char_id`, `account_id`, `rates`, `store`)
	sqldbs_query(&mysql_handle,
		"INSERT INTO `mail` (`char_id`, `account_id`, `rates`, `store`) VALUES ('%d','%d','%u','%d')",
		m->char_id, m->account_id, m->rates, m->store
	);

	return 0;
}

// 個人メールBOXを文字列から変換
static int mailbox_fromstr(char *str,struct mail_data *md,char *body_data)
{
	int n;
	int tmp_int[17];
	char tmp_str[3][1024];

	n=sscanf(str,"%u,%d\t%1023[^\t]\t%1023[^\t]\t%1023[^\t]\t%d\t%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u\t%u\t%u\t%1023[^\r\n]",
		&tmp_int[0],&tmp_int[1],tmp_str[0],tmp_str[1],tmp_str[2],&tmp_int[2],
		&tmp_int[3],&tmp_int[4],&tmp_int[5],&tmp_int[6],&tmp_int[7],&tmp_int[8],&tmp_int[9],&tmp_int[10],&tmp_int[11],&tmp_int[12],&tmp_int[13],
		&tmp_int[14],&tmp_int[15],&tmp_int[16],body_data);
	if(n!=21) {
		// 一度も開かれてないメールBOXはAuriga-0300より古い形式のままの可能性がある
		tmp_int[14] = 0;
		n=sscanf(str,"%u,%d\t%1023[^\t]\t%1023[^\t]\t%1023[^\t]\t%d\t%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\t%u\t%u\t%1023[^\r\n]",
			&tmp_int[0],&tmp_int[1],tmp_str[0],tmp_str[1],tmp_str[2],&tmp_int[2],
			&tmp_int[3],&tmp_int[4],&tmp_int[5],&tmp_int[6],&tmp_int[7],&tmp_int[8],&tmp_int[9],&tmp_int[10],&tmp_int[11],&tmp_int[12],&tmp_int[13],
			&tmp_int[15],&tmp_int[16],body_data);
		if(n!=20)
			return 1;
	}
	md->mail_num = (unsigned int)tmp_int[0];
	md->read     = tmp_int[1];
	memcpy(md->char_name,tmp_str[0],24);
	memcpy(md->receive_name,tmp_str[1],24);
	memcpy(md->title,tmp_str[2],40);
	md->zeny           = tmp_int[2];
	md->item.id        = (unsigned int)tmp_int[3];
	md->item.nameid    = tmp_int[4];
	md->item.amount    = tmp_int[5];
	md->item.equip     = (unsigned int)tmp_int[6];
	md->item.identify  = tmp_int[7];
	md->item.refine    = tmp_int[8];
	md->item.attribute = tmp_int[9];
	md->item.card[0]   = tmp_int[10];
	md->item.card[1]   = tmp_int[11];
	md->item.card[2]   = tmp_int[12];
	md->item.card[3]   = tmp_int[13];
	md->item.limit     = (unsigned int)tmp_int[14];
	md->times          = (unsigned int)tmp_int[15];
	md->body_size      = (unsigned int)tmp_int[16];

	// force \0 terminal
	md->char_name[23]    = '\0';
	md->receive_name[23] = '\0';
	md->title[39]        = '\0';

	// md->bodyは使わない

	return 0;
}

// 個人メールBOXを書き込み
static int mailbox_tosql(struct mail_data *md,const char *body_data)
{
	char buf[3][256];

	sqldbs_query(&mysql_handle, "DELETE FROM `mail_data` WHERE `char_id` = '%d' AND `number` = '%d'", md->char_id, md->mail_num);

	sqldbs_query(&mysql_handle,
		"INSERT INTO `mail_data` (`char_id`, `number`, `read`, `send_name`, `receive_name`, `title`, "
		"`times`, `size`, `body`, `zeny`, "
		"`id`, `nameid`, `amount`, `equip`, `identify`, `refine`, `attribute`, "
		"`card0`, `card1`, `card2`, `card3`, `limit`) "
		"VALUES ('%d','%u','%d','%s','%s','%s','%u','%u','%s','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%u')",
		md->char_id, md->mail_num, md->read, strecpy(buf[0],md->char_name), strecpy(buf[1],md->receive_name), strecpy(buf[2],md->title),
		md->times, md->body_size, body_data, md->zeny,
		md->item.id, md->item.nameid, md->item.amount, md->item.equip, md->item.identify, md->item.refine, md->item.attribute,
		md->item.card[0], md->item.card[1], md->item.card[2], md->item.card[3], md->item.limit
	);

	return 0;
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
		int *charid_list;

		printf("\nConverting Mail Data...\n");

		// mail.txt
		fp = fopen(mail_txt,"r");
		if(fp == NULL) {
			printf("cant't read : %s\n",mail_txt);
			return 1;
		}
		list_size = 256;
		charid_list = (int *)aCalloc(list_size, sizeof(int));
		while(fgets(line, sizeof(line)-1, fp)) {
			c++;
			memset(&m, 0, sizeof(m));
			if(mail_fromstr(line, &m) == 0) {
				mail_tosql(&m);
				if(list_num >= list_size) {
					list_size += 256;
					charid_list = (int *)aRealloc(charid_list, list_size*sizeof(int));
					memset(charid_list+(list_size-256), 0, 256*sizeof(int));
				}
				charid_list[list_num++] = m.char_id;	// キャラIDをリストに保存
			} else {
				printf("mail: broken data [%s] line %d\n", mail_txt, c);
			}
		}
		fclose(fp);

		// mail_data
		for(i=0; i<list_num; i++) {
			char filename[1056];
			sprintf(filename,"%s%d.txt",mail_dir,charid_list[i]);
			fp = fopen(filename,"r");
			if(fp == NULL) {
				printf("cant't read : %s\n",filename);
				mail_delete_fromsql(charid_list[i]);	// 整合性が取れないので `mail` から削除
				continue;
			}
			c = 0;
			while(fgets(line, sizeof(line), fp)) {
				char body_data[1024];	// bodyはバイナリデータのままSQLに流し込むのでUNHEXしない
				c++;
				memset(&md, 0, sizeof(md));
				if(mailbox_fromstr(line, &md, body_data) == 0) {
					md.char_id = charid_list[i];
					mailbox_tosql(&md, body_data);
				} else {
					printf("mailbox: broken data [%s] line %d\n", filename, c);
				}
			}
			fclose(fp);
		}
		aFree(charid_list);
	}
	while(getchar() != '\n');

	return 0;
}
