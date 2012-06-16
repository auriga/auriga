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
#include <time.h>

#include "db.h"
#include "timer.h"
#include "socket.h"
#include "nullpo.h"
#include "malloc.h"
#include "utils.h"
#include "mmo.h"

#include "memorial.h"
#include "pc.h"

/*==========================================
 * 名称からメモリアルDBのデータを検索
 *------------------------------------------
 */
static struct memorial_db *memorial_search_db(const char *memorial_name)
{
	int i;

	for(i=0; i < MAX_MEMORIAL_DB; i++) {
		if(strcmp(memorial_db[i].name, memorial_name) == 0)
			return &memorial_db[i];
	}

	return NULL;
}

/*==========================================
 * メモリアルダンジョン生成
 *------------------------------------------
 */
int memorial_create(const char *memorial_name, int party_id)
{

	return MDERR_ERROR;
}

/*==========================================
 * メモリアルダンジョン入場
 *------------------------------------------
 */
int memorial_enter(struct map_session_data *sd, const char *memorial_name)
{
	struct memorial_db *db = memorial_search_db(memorial_name);

	nullpo_retr(0, sd);
	nullpo_retr(0, db);

	pc_setpos(sd, db->enter.mapname, db->enter.x, db->enter.y, 0);

	return MDERR_NOERROR;
}

//
// 初期化物
//
/*==========================================
 * メモリアルダンジョン基本データ読み込み
 *------------------------------------------
 */
static int read_memorial_db(void)
{
	int i = 0, j, k;
	FILE *fp;
	char line[1024],*p;

	memset(&memorial_db, 0, sizeof(memorial_db));

	fp=fopen("db/memorial_db.txt","r");
	if(fp==NULL){
		printf("can't read db/memorial_db.txt\n");
		return 1;
	}
	while(fgets(line,1020,fp)){
		char *split[16];
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0]=='/' && line[1]=='/')
			continue;
		memset(split,0,sizeof(split));
		for(j=0,p=line;j<16 && p;j++){
			split[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		if(j < 16)
			continue;

		memorial_db[i].memorial_id = (short)atoi(split[0]);
		strncpy(memorial_db[i].name,split[1],61);
		memorial_db[i].limit = atoi(split[2]);
		strncpy(memorial_db[i].enter.mapname,split[3],24);
		memorial_db[i].enter.x = (short)atoi(split[4]);
		memorial_db[i].enter.y = (short)atoi(split[5]);

		for(k = 0; k < MAX_MEMORIAL_SEGMAP; k++) {
			strncpy(memorial_db[i].mapname[k],split[6+k],24);
			memorial_db[i].mapname[k][23] = '\0';
		}

		// force \0 terminal
		memorial_db[i].name[60] = '\0';
		memorial_db[i].enter.mapname[23] = '\0';

		if(++i >= MAX_MEMORIAL_DB)
			break;
	}
	fclose(fp);
	printf("read db/memorial_db.txt done (count=%d)\n",i);

	return 0;
}

/*==========================================
 * 初期化処理
 *------------------------------------------
 */
int do_init_memorial(void)
{
	read_memorial_db();

	return 0;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
int do_final_memorial(void)
{

	return 0;
}
