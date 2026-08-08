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
#include <time.h>
#include <math.h>

#include "db.h"
#include "timer.h"
#include "nullpo.h"
#include "malloc.h"
#include "mmo.h"
#include "utils.h"

#include "guild.h"
#include "skill.h"
#include "skill_internal.h"
#include "map.h"
#include "path.h"
#include "clif.h"
#include "pc.h"
#include "bonus.h"
#include "pet.h"
#include "mob.h"
#include "battle.h"
#include "party.h"
#include "itemdb.h"
#include "script.h"
#include "intif.h"
#include "status.h"
#include "date.h"
#include "unit.h"
#include "homun.h"
#include "msg.h"
#include "ranking.h"
#include "npc.h"
#include "merc.h"
#include "buyingstore.h"
#include "elem.h"

/* Split from skill.c (Issue #56) */
/*==========================================
 * スキル関係ファイル読み込み
 * skill_db.txt スキルデータ
 * skill_cast_db.txt スキルの詠唱時間とディレイデータ
 * produce_db.txt アイテム作成スキル用データ
 * create_arrow_db.txt 矢作成スキル用データ
 * abra_db.txt アブラカダブラ発動スキルデータ
 *------------------------------------------
 */
int skill_readdb(void)
{
	int i,j,k,m;
	FILE *fp;
	char line[1024],*p;
#ifdef PRE_RENEWAL
	const char *filename[] = {
		"db/skill_db.txt",         "db/pre/skill_db_pre.txt",         "db/addon/skill_db_add.txt",
		"db/skill_require_db.txt", "db/pre/skill_require_db_pre.txt", "db/addon/skill_require_db_add.txt",
		"db/skill_require_db2.txt","db/pre/skill_require_db2_pre.txt","db/addon/skill_require_db2_add.txt",
		"db/skill_cast_db.txt",    "db/pre/skill_cast_db_pre.txt",    "db/addon/skill_cast_db_add.txt",
		"db/skill_unit_db.txt",    "db/pre/skill_unit_db_pre.txt",    "db/addon/skill_unit_db_add.txt",
		"db/produce_db.txt",       "db/pre/produce_db_pre.txt",       "db/addon/produce_db_add.txt"
	};
	const int max = 3;
#else
	const char *filename[] = {
		"db/skill_db.txt",         "db/addon/skill_db_add.txt",
		"db/skill_require_db.txt", "db/addon/skill_require_db_add.txt",
		"db/skill_require_db2.txt","db/addon/skill_require_db2_add.txt",
		"db/skill_cast_db.txt",    "db/addon/skill_cast_db_add.txt",
		"db/skill_unit_db.txt",    "db/addon/skill_unit_db_add.txt",
		"db/produce_db.txt",       "db/addon/produce_db_add.txt"
	};
	const int max = 2;
#endif
	const char *filename2;

	memset(skill_db,0,sizeof(skill_db));

	/* スキルデータベース */
	for(m = 0; m < max; m++) {
		fp = fopen(filename[m], "r");
		if(fp == NULL) {
			if(m > 0)
				continue;
			printf("skill_readdb: open [%s] failed !\n", filename[m]);
			return 1;
		}
		k = 0;
		while(fgets(line,1020,fp)){
			char *split[50];
			if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
				continue;
			if(line[0]=='/' && line[1]=='/')
				continue;
			j = skill_split_str(line,split,17);
			if(split[16]==NULL || j<17)
				continue;

			i = skill_get_skilldb_id(atoi(split[0]));
			if(i == 0)
				continue;

			skill_db[i].id = atoi(split[0]);
			skill_split_atoi(split[1],skill_db[i].range,MAX_SKILL_LEVEL);
			skill_db[i].hit = atoi(split[2]);
			skill_db[i].inf = atoi(split[3]);
			skill_db[i].pl  = atoi(split[4]);
			skill_db[i].nk  = atoi(split[5]);

			skill_db[i].max = atoi(split[6]);
			if(skill_db[i].max > MAX_SKILL_LEVEL)
				skill_db[i].max = MAX_SKILL_LEVEL;

			skill_split_atoi(split[7],skill_db[i].num,MAX_SKILL_LEVEL);

			if(strcmpi(split[8],"yes") == 0)
				skill_db[i].castcancel = 1;
			else
				skill_db[i].castcancel = 0;
			skill_db[i].cast_def_rate = atoi(split[9]);
			skill_db[i].inf2          = (int)strtol(split[10], NULL, 0);
			skill_split_atoi(split[11],skill_db[i].maxcount,MAX_SKILL_LEVEL);
			if(strcmpi(split[12],"weapon") == 0)
				skill_db[i].skill_type = BF_WEAPON;
			else if(strcmpi(split[12],"magic") == 0)
				skill_db[i].skill_type = BF_MAGIC;
			else if(strcmpi(split[12],"misc") == 0)
				skill_db[i].skill_type = BF_MISC;
			else
				skill_db[i].skill_type = 0;
			skill_split_atoi(split[13],skill_db[i].blewcount,MAX_SKILL_LEVEL);
			skill_split_atoi(split[14],skill_db[i].area,MAX_SKILL_LEVEL);
			skill_split_atoi(split[15],skill_db[i].heal_ap,MAX_SKILL_LEVEL);
			memcpy(skill_db[i].name,split[16],31);
			skill_db[i].name[30] = '\0';	// froce \0 terminal
			strdb_insert(skillname_db,skill_db[i].name,&skill_db[i]);
			k++;
		}
		fclose(fp);
		printf("read %s done (count=%d)\n", filename[m], k);
	}

	/* スキルデータベース2 */
	filename2 = "db/skill_db2.txt";
	fp = fopen(filename2, "r");
	if(fp == NULL) {
		printf("skill_readdb: open [%s] failed !\n", filename2);
		return 1;
	}
	k = 0;
	while(fgets(line,1020,fp)){
		char *split[50];
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0]=='/' && line[1]=='/')
			continue;
		j = skill_split_str(line,split,9);
		if(split[8]==NULL || j<9)
			continue;

		i = skill_get_skilldb_id(atoi(split[0]));
		if(i == 0)
			continue;

		skill_db[i].cloneable = atoi(split[1]);
		skill_db[i].misfire   = atoi(split[2]);
		skill_db[i].zone      = atoi(split[3]);
		skill_split_atoi(split[4],skill_db[i].damage_rate,sizeof(skill_db[i].damage_rate)/sizeof(int));
		skill_db[i].range_type = atoi(split[5]);
		skill_db[i].amotion_delay = atoi(split[6]);
		skill_db[i].autoshadowspell = atoi(split[7]);
		k++;
	}
	fclose(fp);
	printf("read %s done (count=%d)\n", filename2, k);

	/* スキル要求データベース */
	for(m= max; m < max * 2; m++) {
		int n;
		fp = fopen(filename[m], "r");
		if(fp == NULL) {
			if(m > max)
				continue;
			printf("skill_readdb: open [%s] failed !\n", filename[m]);
			return 1;
		}
		k = 0;
		while(fgets(line,1020,fp)){
			char *split[50];
			if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
				continue;
			if(line[0]=='/' && line[1]=='/')
				continue;
			j = skill_split_str(line,split,33);
			if(split[32]==NULL || j<33)
				continue;

			i = skill_get_skilldb_id(atoi(split[0]));
			if(i == 0)
				continue;

			skill_split_atoi(split[1],skill_db[i].hp,MAX_SKILL_LEVEL);
			skill_split_atoi(split[2],skill_db[i].sp,MAX_SKILL_LEVEL);
			skill_split_atoi(split[3],skill_db[i].ap,MAX_SKILL_LEVEL);
			skill_split_atoi(split[4],skill_db[i].hp_rate,MAX_SKILL_LEVEL);
			skill_split_atoi(split[5],skill_db[i].sp_rate,MAX_SKILL_LEVEL);
			skill_split_atoi(split[6],skill_db[i].ap_rate,MAX_SKILL_LEVEL);
			skill_split_atoi(split[7],skill_db[i].zeny,MAX_SKILL_LEVEL);

			skill_db[i].weapon = 0;
			p = split[8];
			for(j=0;j<32;j++){
				n = atoi(p);
				if(n == WT_DOUBLE_MAX) {
					skill_db[i].weapon = 0xffffffff;
					break;
				} else {
					if(n >= WT_MAX) {
						n -= WT_DOUBLE_DD + WT_MAX;
					}
					skill_db[i].weapon |= 1<<n;
				}
				p=strchr(p,':');
				if(!p)
					break;
				p++;
			}

			if( strcmpi(split[9],"hiding") == 0 )                   skill_db[i].state = SST_HIDING;
			else if( strcmpi(split[9],"cloaking") == 0 )            skill_db[i].state = SST_CLOAKING;
			else if( strcmpi(split[9],"chasewalking") == 0 )        skill_db[i].state = SST_CHASEWALKING;
			else if( strcmpi(split[9],"hidden") == 0 )              skill_db[i].state = SST_HIDDEN;
			else if( strcmpi(split[9],"riding") == 0 )              skill_db[i].state = SST_RIDING;
			else if( strcmpi(split[9],"falcon") == 0 )              skill_db[i].state = SST_FALCON;
			else if( strcmpi(split[9],"cart") == 0 )                skill_db[i].state = SST_CART;
			else if( strcmpi(split[9],"shield") == 0 )              skill_db[i].state = SST_SHIELD;
			else if( strcmpi(split[9],"sight") == 0 )               skill_db[i].state = SST_SIGHT;
			else if( strcmpi(split[9],"explosionspirits") == 0 )    skill_db[i].state = SST_EXPLOSIONSPIRITS;
			else if( strcmpi(split[9],"cartboost") == 0 )           skill_db[i].state = SST_CARTBOOST;
			else if( strcmpi(split[9],"nen") == 0 )                 skill_db[i].state = SST_NEN;
			else if( strcmpi(split[9],"recover_weight_rate") == 0 ) skill_db[i].state = SST_RECOV_WEIGHT_RATE;
			else if( strcmpi(split[9],"move_enable") == 0 )         skill_db[i].state = SST_MOVE_ENABLE;
			else if( strcmpi(split[9],"water") == 0 )               skill_db[i].state = SST_WATER;
			else if( strcmpi(split[9],"dragon") == 0 )              skill_db[i].state = SST_DRAGON;
			else if( strcmpi(split[9],"wolf") == 0 )                skill_db[i].state = SST_WOLF;
			else if( strcmpi(split[9],"gear") == 0 )                skill_db[i].state = SST_GEAR;
			else                                                    skill_db[i].state = SST_NONE;

			skill_split_atoi(split[10],skill_db[i].spiritball,MAX_SKILL_LEVEL);
			skill_db[i].itemid[0] = atoi(split[11]);
			skill_db[i].amount[0] = atoi(split[12]);
			skill_db[i].itemid[1] = atoi(split[13]);
			skill_db[i].amount[1] = atoi(split[14]);
			skill_db[i].itemid[2] = atoi(split[15]);
			skill_db[i].amount[2] = atoi(split[16]);
			skill_db[i].itemid[3] = atoi(split[17]);
			skill_db[i].amount[3] = atoi(split[18]);
			skill_db[i].itemid[4] = atoi(split[19]);
			skill_db[i].amount[4] = atoi(split[20]);
			skill_db[i].itemid[5] = atoi(split[21]);
			skill_db[i].amount[5] = atoi(split[22]);
			skill_db[i].itemid[6] = atoi(split[23]);
			skill_db[i].amount[6] = atoi(split[24]);
			skill_db[i].itemid[7] = atoi(split[25]);
			skill_db[i].amount[7] = atoi(split[26]);
			skill_db[i].itemid[8] = atoi(split[27]);
			skill_db[i].amount[8] = atoi(split[28]);
			skill_db[i].itemid[9] = atoi(split[29]);
			skill_db[i].amount[9] = atoi(split[30]);
			skill_split_atoi(split[31],skill_db[i].lv_itemid,MAX_SKILL_LEVEL);
			skill_split_atoi(split[32],skill_db[i].lv_amount,MAX_SKILL_LEVEL);
			k++;
		}
		fclose(fp);
		printf("read %s done (count=%d)\n", filename[m], k);
	}

	/* スキル要求データベース2 */
	for(m = max * 2; m < max * 3; m++) {
		fp = fopen(filename[m], "r");
		if(fp == NULL) {
			if(m > max * 2)
				continue;
			printf("skill_readdb: open [%s] failed !\n", filename[m]);
			return 1;
		}
		k = 0;
		while(fgets(line,1020,fp)){
			char *split[50];
			if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
				continue;
			if(line[0]=='/' && line[1]=='/')
				continue;
			j = skill_split_str(line,split,6);
			if(split[5]==NULL || j<6)
				continue;

			i = skill_get_skilldb_id(atoi(split[0]));
			if(i == 0)
				continue;

			skill_split_atoi(split[1],skill_db[i].coin,MAX_SKILL_LEVEL);
			skill_db[i].arrow_type = atoi(split[2]);
			skill_split_atoi(split[3],skill_db[i].arrow_cost,MAX_SKILL_LEVEL);
			k++;
		}
		fclose(fp);
		printf("read %s done (count=%d)\n", filename[m], k);
	}

	/* キャスティングデータベース */
	for(m = max * 3; m < max * 4; m++) {
		fp = fopen(filename[m], "r");
		if(fp == NULL) {
			if(m > max * 3)
				continue;
			printf("skill_readdb: open [%s] failed !\n", filename[m]);
			return 1;
		}
		k = 0;
		while(fgets(line,1020,fp)){
			char *split[50];
			if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
				continue;
			if(line[0]=='/' && line[1]=='/')
				continue;
			j = skill_split_str(line,split,7);
			if(split[6]==NULL || j<7)
				continue;

			i = skill_get_skilldb_id(atoi(split[0]));
			if(i == 0)
				continue;

			skill_split_atoi(split[1],skill_db[i].cast,MAX_SKILL_LEVEL);
			skill_split_atoi(split[2],skill_db[i].fixedcast,MAX_SKILL_LEVEL);
			skill_split_atoi(split[3],skill_db[i].delay,MAX_SKILL_LEVEL);
			skill_split_atoi(split[4],skill_db[i].cooldown,MAX_SKILL_LEVEL);
			skill_split_atoi(split[5],skill_db[i].upkeep_time,MAX_SKILL_LEVEL);
			skill_split_atoi(split[6],skill_db[i].upkeep_time2,MAX_SKILL_LEVEL);
			k++;
		}
		fclose(fp);
		printf("read %s done (count=%d)\n", filename[m], k);
	}

	/* スキルユニットデータベース */
	for(m = max * 4; m < max * 5; m++) {
		fp = fopen(filename[m], "r");
		if(fp == NULL) {
			if(m > max * 4)
				continue;
			printf("skill_readdb: open [%s] failed !\n", filename[m]);
			return 1;
		}
		k = 0;
		while (fgets(line,1020,fp)) {
			char *split[50];
			if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
				continue;
			if (line[0]=='/' && line[1]=='/')
				continue;
			j = skill_split_str(line,split,8);
			if (split[7]==NULL || j<8)
				continue;

			i = skill_get_skilldb_id(atoi(split[0]));
			if(i == 0)
				continue;

			skill_db[i].unit_id[0] = strtol(split[1],NULL,16);
			skill_db[i].unit_id[1] = strtol(split[2],NULL,16);
			skill_split_atoi(split[3],skill_db[i].unit_layout_type,MAX_SKILL_LEVEL);
			skill_split_atoi(split[4],skill_db[i].unit_range,MAX_SKILL_LEVEL);
			skill_split_atoi(split[5],skill_db[i].unit_interval,MAX_SKILL_LEVEL);
			skill_db[i].unit_target   = strtol(split[6],NULL,16);
			skill_split_strtol(split[7],skill_db[i].unit_flag,MAX_SKILL_LEVEL,16);
			k++;
		}
		fclose(fp);
		printf("read %s done (count=%d)\n", filename[m], k);
	}
	skill_init_unit_layout();

	/* 製造系スキルデータベース */
	memset(skill_produce_db, 0, sizeof(skill_produce_db));

	for(m = max * 5; m < max * 6; m++) {
		int count = 0;
		fp = fopen(filename[m], "r");
		if(fp == NULL) {
			if(m > max * 5)
				continue;
			printf("skill_readdb: open [%s] failed !\n", filename[m]);
			return 1;
		}
		while(fgets(line,1020,fp)){
			char *split[6 + MAX_PRODUCE_RESOURCE * 2];
			int x,y;
			if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
				continue;
			if(line[0]=='/' && line[1]=='/')
				continue;
			memset(split,0,sizeof(split));
			for(j=0,p=line;j<6 + MAX_PRODUCE_RESOURCE * 2 && p;j++){
				split[j]=p;
				p=strchr(p,',');
				if(p) *p++=0;
			}
			if(split[0]==NULL)
				continue;
			i=atoi(split[0]);
			if(i<=0)
				continue;

			for(k=0; k<MAX_SKILL_PRODUCE_DB; k++) {
				if(skill_produce_db[k].nameid <= 0 || skill_produce_db[k].nameid == i)
					break;
			}
			if(k >= MAX_SKILL_PRODUCE_DB)
				break;

			skill_produce_db[k].nameid      = i;
			skill_produce_db[k].itemlv      = atoi(split[1]);
			skill_produce_db[k].req_skill   = atoi(split[2]);
			skill_produce_db[k].req_skilllv = atoi(split[3]);
			skill_produce_db[k].per         = atoi(split[4]);

			for(x=5,y=0; split[x] && split[x+1] && y<MAX_PRODUCE_RESOURCE; x+=2,y++){
				skill_produce_db[k].mat_id[y]     = atoi(split[x]);
				skill_produce_db[k].mat_amount[y] = atoi(split[x+1]);
			}
			count++;
		}
		fclose(fp);
		printf("read %s done (count=%d)\n", filename[m], count);
	}

	/* 矢作成データベース */
	memset(skill_arrow_db, 0, sizeof(skill_arrow_db));
	filename2 = "db/create_arrow_db.txt";
	fp = fopen(filename2, "r");
	if(fp == NULL) {
		printf("skill_readdb: open [%s] failed !\n", filename2);
		return 1;
	}
	k=0;
	while(fgets(line,1020,fp)){
		char *split[16];
		int x,y;
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0]=='/' && line[1]=='/')
			continue;
		memset(split,0,sizeof(split));
		for(j=0,p=line;j<13 && p;j++){
			split[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		if(split[0]==NULL)
			continue;
		i=atoi(split[0]);
		if(i<=0)
			continue;

		skill_arrow_db[k].nameid=i;

		for(x=1,y=0;split[x] && split[x+1] && y<5;x+=2,y++){
			skill_arrow_db[k].cre_id[y]     = atoi(split[x]);
			skill_arrow_db[k].cre_amount[y] = atoi(split[x+1]);
		}
		k++;
		if(k >= MAX_SKILL_ARROW_DB)
			break;
	}
	fclose(fp);
	printf("read %sdone (count=%d)\n", filename2, k);

	/* アブラカタブラデータベース */
	memset(skill_abra_db, 0, sizeof(skill_abra_db));
	filename2 = "db/abra_db.txt";
	fp = fopen(filename2, "r");
	if(fp == NULL) {
		printf("skill_readdb: open [%s] failed !\n", filename2);
		return 1;
	}
	k=0;
	while(fgets(line,1020,fp)){
		char *split[16];
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0]=='/' && line[1]=='/')
			continue;
		memset(split,0,sizeof(split));
		for(j=0,p=line;j<13 && p;j++){
			split[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		if(split[0]==NULL)
			continue;
		i=atoi(split[0]);
		if(i<=0)
			continue;
		i=atoi(split[3]);
		if(i<=0)
			continue;

		skill_abra_db[k].nameid = atoi(split[0]);
		skill_abra_db[k].req_lv = atoi(split[2]);
		skill_abra_db[k].per    = atoi(split[3]);

		k++;
		if(k >= MAX_SKILL_ABRA_DB)
			break;
	}
	fclose(fp);
	printf("read %s done (count=%d)\n", filename2, k);

	/* ランダム発動スキルデータベース */
	memset(skill_rand_db, 0, sizeof(skill_rand_db));
	filename2 = "db/skill_random.txt";
	fp = fopen(filename2, "r");
	if(fp == NULL) {
		printf("skill_readdb: open [%s] failed !\n", filename2);
		return 1;
	}
	k=0;
	while(fgets(line,1020,fp)){
		int randomid,skillid,range,c;
		char *split[16];
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0]=='/' && line[1]=='/')
			continue;
		memset(split,0,sizeof(split));
		for(j=0,p=line;j<13 && p;j++){
			split[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		if(split[0]==NULL)
			continue;

		randomid = atoi(split[0]) - 1;
		if(randomid < 0 || randomid >= MAX_SKILL_RAND_DB)
			continue;

		skillid = atoi(split[1]);
		if(skill_get_skilldb_id(skillid) == 0)
			continue;

		range = atoi(split[2]);
		if(range < 1 || range >= MAX_SKILL_RAND_RATE)
			continue;

		c = skill_rand_db[randomid].entry;
		if(c >= MAX_SKILL_RAND_ENTRY)
			break;
		if(c > 0)
			range += skill_rand_db[randomid].data[c-1].qty;

		skill_rand_db[randomid].data[c].nameid = skillid;
		skill_rand_db[randomid].data[c].qty = range;
		skill_rand_db[randomid].entry++;

		k++;
	}
	fclose(fp);
	printf("read %s done (count=%d)\n", filename2, k);

	/* チェンジマテリアルデータベース */
	memset(skill_material_db,0,sizeof(skill_material_db));
	filename2 = "db/changematerial_db.txt";
	fp = fopen(filename2, "r");
	if(fp == NULL) {
		printf("skill_readdb: open [%s] failed !\n", filename2);
		return 1;
	}
	k=0;
	while(fgets(line,1020,fp)){
		char *split[3 + MAX_PRODUCE_RESOURCE * 2];
		int x,y;

		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0] == '/' && line[1] == '/')
			continue;
		memset(split,0,sizeof(split));
		for(j = 0, p = line; j < 3 + MAX_PRODUCE_RESOURCE * 2 && p; j++){
			split[j] = p;
			p = strchr(p,',');
			if(p) *p++ = 0;
		}
		if(split[0] == NULL)
			continue;
		i = atoi(split[0]);
		if(i <= 0)
			continue;

		skill_material_db[k].nameid = i;
		skill_split_atoi(split[1],skill_material_db[k].amount,2);
		for(x = 2, y = 0; split[x] && split[x + 1] && y < MAX_PRODUCE_RESOURCE; x += 2, y++){
			skill_material_db[k].mat_id[y]     = atoi(split[x]);
			skill_material_db[k].mat_amount[y] = atoi(split[x + 1]);
		}

		k++;
		if(k >= MAX_SKILL_PRODUCE_DB)
			break;
	}
	fclose(fp);
	printf("read %s done (count=%d)\n", filename2, k);

	return 0;
}
