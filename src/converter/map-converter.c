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

#include "malloc.h"
#include "sqldbs.h"

#include "converter.h"
#include "map-converter.h"

struct script_mapreg {
	char name[256];
	int index;
	union {
		int value;
		char *str;
	} u;
};

// 永続的マップ変数を文字列から変換
static int mapreg_fromstr(const char *line,struct script_mapreg *reg)
{
	char buf[256];
	int n,i;

	if( sscanf(line, "%255[^,],%d\t%n", buf, &i, &n) != 2 &&
	    (i=0, sscanf(line, "%[^\t]\t%n", buf, &n) != 1) )
		return 1;
	if(i < 0 || i >= 128)
		return 1;

	if(buf[strlen(buf)-1] == '$') {
		char buf2[1024];
		if(sscanf(line+n, "%[^\n\r]", buf2) != 1)
			return 1;
		reg->u.str = (char *)aStrdup(buf2);
	} else {
		int v;
		if(sscanf(line+n, "%d", &v) != 1)
			return 1;
		reg->u.value = v;
	}
	strncpy(reg->name, buf, 256);
	reg->index = i;

	return 0;
}

// 永続的マップ変数を書き込み
static int mapreg_tosql(struct script_mapreg *reg)
{
	char buf1[64], buf2[1024];
	char tmp_sql[65536];
	char *p = tmp_sql;

	p += sprintf(p, "INSERT INTO `mapreg` (`server_tag`,`reg`,`index`,`value`) VALUES ('%s','%s','%d',",
		strecpy(buf1,map_server_tag), strecpy(buf2,reg->name), reg->index);

	if(reg->name[strlen(reg->name)-1] == '$') {
		char buf3[4096];
		sprintf(p, "'%s')", strecpy(buf3,reg->u.str));
		aFree(reg->u.str);
	} else {
		sprintf(p, "'%d')", reg->u.value);
	}

	sqldbs_simplequery(&mysql_handle, tmp_sql);

	return 0;
}

int map_convert(void)
{
	char input, line[65536];
	int c = 0;
	FILE *fp;

	printf("\nDo you wish to convert your Mapreg to SQL? (y/n) : ");
	input = getchar();
	if(input == 'y' || input == 'Y') {
		struct script_mapreg reg;
		char buf[64];
		printf("\nConverting Mapreg in \"%s\"...\n", map_server_tag);
		fp = fopen(mapreg_txt,"r");
		if(fp == NULL) {
			printf("cant't read : %s\n",mapreg_txt);
			return 1;
		}
		sqldbs_query(&mysql_handle, "DELETE FROM `mapreg` WHERE `server_tag` = '%s'", strecpy(buf,map_server_tag));

		while(fgets(line, sizeof(line)-1, fp)) {
			c++;
			memset(&reg, 0, sizeof(reg));
			if(mapreg_fromstr(line, &reg) == 0) {
				mapreg_tosql(&reg);
			} else {
				printf("map_mapreg: broken data [%s] line %d\n", mapreg_txt, c);
			}
		}
		fclose(fp);
	}
	while(getchar() != '\n');

	return 0;
}
