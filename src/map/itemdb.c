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

// $Id: itemdb.c,v 1.1.1.1 2005/05/10 05:59:00 running_pinata Exp $

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "db.h"
#include "grfio.h"
#include "nullpo.h"
#include "malloc.h"
#include "utils.h"

#include "map.h"
#include "battle.h"
#include "itemdb.h"
#include "script.h"
#include "pc.h"

// ** ITEMDB_OVERRIDE_NAME_VERBOSE **
//   定義すると、itemdb.txtとgrfで名前が異なる場合、表示します.
//#define ITEMDB_OVERRIDE_NAME_VERBOSE	1

static struct dbt* item_db = NULL;
static struct random_item_data random_item[MAX_RAND_ITEM_TYPE];

/*==========================================
 * 名前で検索
 *------------------------------------------
 */
static int itemdb_searchname_sub(void *key,void *data,va_list ap)
{
	struct item_data *item, **dst;
	char *str;

	item = (struct item_data *)data;
	str  = va_arg(ap,char *);
	dst  = va_arg(ap,struct item_data **);

	if(*dst)
		return 0;

	if( strcmpi(item->name,str) == 0 || strcmp(item->jname,str) == 0 )
		*dst = item;

	return 0;
}

struct item_data* itemdb_searchname(const char *str)
{
	struct item_data *item = NULL;

	numdb_foreach(item_db,itemdb_searchname_sub,str,&item);
	return item;
}

/*==========================================
 * @idsearch
 *------------------------------------------
 */
int itemdb_idsearch(const int fd, const char *str, int (*func)(void*, void*, va_list))
{
	return numdb_foreach(item_db, func, str, fd);
}

/*==========================================
 * ランダム系アイテム検索
 *------------------------------------------
 */
int itemdb_searchrandomid(int type)
{
	int c;

	// typeは1以上なのでデクリメントする
	type--;
	if(type < 0 || type >= MAX_RAND_ITEM_TYPE)
		return 0;

	c = random_item[type].entry;
	if(c > 0 && random_item[type].data[c-1].qty > 0) {
		int i, num = atn_rand() % random_item[type].data[c-1].qty;
		for(i=0; i < c && num >= random_item[type].data[i].qty; i++);

		return random_item[type].data[i].nameid;
	}
	return 0;
}

/*==========================================
 * DBの存在確認
 *------------------------------------------
 */
struct item_data* itemdb_exists(int nameid)
{
	return (struct item_data *)numdb_search(item_db,nameid);
}

/*==========================================
 * DBの検索
 *------------------------------------------
 */
struct item_data* itemdb_search(int nameid)
{
	struct item_data *id;

	id = (struct item_data *)numdb_search(item_db,nameid);
	if(id)
		return id;

	id = (struct item_data *)aCalloc(1,sizeof(struct item_data));
	numdb_insert(item_db,nameid,id);

	id->nameid     = nameid;
	id->value_buy  = 10;
	id->value_sell = id->value_buy/2;
	id->weight     = 10;
	id->sex        = SEX_SERVER;
	id->elv        = 0;
	id->class_     = 0xffffffff;

	if(nameid > 500 && nameid < 600)
		id->type = ITEMTYPE_HEAL;   // heal item
	else if(nameid > 600 && nameid < 700)
		id->type = ITEMTYPE_SPECIAL;   // use item
	else if((nameid > 700 && nameid < 1100) || (nameid > 7000 && nameid < 8000))
		id->type = ITEMTYPE_EVENT;   // correction
	else if((nameid >= 1750 && nameid < 1771) || (nameid >= 13200 && nameid < 13300))
		id->type = ITEMTYPE_ARROW;  // arrow
	else if((nameid > 1100 && nameid < 2000) || (nameid >= 13000 && nameid < 13350))
		id->type = ITEMTYPE_WEAPON;   // weapon
	else if((nameid > 2100 && nameid < 3000) || (nameid > 5000 && nameid < 6000))
		id->type = ITEMTYPE_ARMOR;   // armor
	else if(nameid > 4000 && nameid < 5000)
		id->type = ITEMTYPE_CARD;   // card
	else if(nameid > 9000 && nameid < 10000)
		id->flag.pet_egg = 1;   // egg
	else if(nameid > 10000)
		id->flag.pet_acce = 1;   // petequip

	return id;
}

/*==========================================
 *
 *------------------------------------------
 */
int itemdb_isequip(int nameid)
{
	int type = itemdb_type(nameid);
	int result;

	switch(type) {
		case ITEMTYPE_HEAL:
		case ITEMTYPE_SPECIAL:
		case ITEMTYPE_EVENT:
		case ITEMTYPE_CARD:
		case ITEMTYPE_ARROW:
		case ITEMTYPE_AMMO:
		case ITEMTYPE_THROWWEAPON:
		case ITEMTYPE_CASH_POINT_ITEM:
		case ITEMTYPE_CANNONBALL:
			result = 0;
			break;
		default:
			result = 1;
			break;
	}

	return result;
}

/*==========================================
 *
 *------------------------------------------
 */
int itemdb_isequip2(struct item_data *data)
{
	int result=0;

	if(data) {
		switch(data->type) {
			case ITEMTYPE_HEAL:
			case ITEMTYPE_SPECIAL:
			case ITEMTYPE_EVENT:
			case ITEMTYPE_CARD:
			case ITEMTYPE_ARROW:
			case ITEMTYPE_AMMO:
			case ITEMTYPE_THROWWEAPON:
			case ITEMTYPE_CASH_POINT_ITEM:
			case ITEMTYPE_CANNONBALL:
				break;
			default:
				result = 1;
				break;
		}
	}

	return result;
}

/*==========================================
 *
 *------------------------------------------
 */
int itemdb_isequip3(int nameid)
{
	int type = itemdb_type(nameid);
	int result;

	switch(type) {
		case ITEMTYPE_ARMOR:
		case ITEMTYPE_WEAPON:
		case ITEMTYPE_BOW:
		case ITEMTYPE_BOTHHAND:
		case ITEMTYPE_ARMORTM:
		case ITEMTYPE_ARMORTB:
		case ITEMTYPE_ARMORMB:
		case ITEMTYPE_ARMORTMB:
		case ITEMTYPE_GUN:
		case ITEMTYPE_COSTUME:
			result = 1;
			break;
		default:
			result = 0;
			break;
	}

	return result;
}

/*==========================================
 *
 *------------------------------------------
 */
int itemdb_isweapon(int nameid)
{
	int type = itemdb_type(nameid);
	int result;

	switch(type) {
		case ITEMTYPE_WEAPON:
		case ITEMTYPE_BOW:
		case ITEMTYPE_BOTHHAND:
		case ITEMTYPE_GUN:
			result = 1;
			break;
		default:
			result = 0;
			break;
	}

	return result;
}

/*==========================================
 *
 *------------------------------------------
 */
int itemdb_isarmor(int nameid)
{
	int type = itemdb_type(nameid);
	int result;

	switch(type) {
		case ITEMTYPE_ARMOR:
		case ITEMTYPE_ARMORTM:
		case ITEMTYPE_ARMORTB:
		case ITEMTYPE_ARMORMB:
		case ITEMTYPE_ARMORTMB:
		case ITEMTYPE_COSTUME:
			result = 1;
			break;
		default:
			result = 0;
			break;
	}

	return result;
}

/*==========================================
 * 倉庫に入れられるアイテムは1、そうでないアイテムは0
 *------------------------------------------
 */
int itemdb_isstorageable(int nameid)
{
	struct item_data *id = itemdb_exists(nameid);

	if(id && !id->flag.storageable)
		return 1;

	return 0;
}

/*==========================================
 * 倉庫からカートに出せるアイテムは1、そうでないアイテムは0
 *------------------------------------------
 */
int itemdb_iscartable(int nameid)
{
	struct item_data *id = itemdb_exists(nameid);

	if(id && !id->flag.cartable)
		return 1;

	return 0;
}

/*==========================================
 * 捨てられるアイテムは1、そうでないアイテムは0
 *------------------------------------------
 */
int itemdb_isdropable(int nameid)
{
	struct item_data *id = itemdb_exists(nameid);

	if(id && !id->flag.dropable)
		return 1;

	return 0;
}

/*==========================================
 * 購買露店に出せるアイテムは1、そうでないアイテムは0
 *------------------------------------------
 */
int itemdb_isbuyingable(int nameid)
{
	struct item_data *id = itemdb_exists(nameid);

	if(id && id->flag.buyingable)
		return 1;

	return 0;
}

/*==========================================
 * 使用しても消費しないアイテムは1、そうでないアイテムは0
 *------------------------------------------
 */
int itemdb_isnonconsume(int nameid)
{
	struct item_data *id = itemdb_exists(nameid);

	if(id && id->flag.nonconsume)
		return 1;

	return 0;
}


//
// 初期化
//
/*==========================================
 *
 *------------------------------------------
 */
static int itemdb_read_itemslottable(void)
{
	char *buf,*p;
	int s;

	buf = (char *)grfio_read("data\\itemslottable.txt");
	if(buf == NULL)
		return -1;
	s = grfio_size("data\\itemslottable.txt");

	buf[s] = 0;
	for(p=buf; p-buf<s; ) {
		int nameid,equip;
		sscanf(p,"%d#%d#",&nameid,&equip);
		itemdb_search(nameid)->equip = equip;
		p=strchr(p,'\n');
		if(!p) break;
		p++;
		p=strchr(p,'\n');
		if(!p) break;
		p++;
	}
	aFree(buf);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
static void itemdb_split_atoi(char *str, int *melee, int *magic)
{
	int i, val[2];

	for (i=0; i<2; i++) {
		if(str) {
			val[i] = atoi(str);
			str = strchr(str,':');
			if (str)
				*str++=0;
		} else {
			val[i] = 0;
		}
	}
	*melee = val[0];
	*magic = val[1];
	return;
}

/*==========================================
 * アイテムデータベースの読み込み
 *------------------------------------------
 */
static int itemdb_read_itemdb(void)
{
	FILE *fp;
	char line[4096];
	int ln=0,lines=0;
	int nameid,j;
	char *str[32],*p,*np;
	struct item_data *id;
	struct script_code *script = NULL;
	int i=0;
	const char *filename[] = { "db/item_db.txt","db/addon/item_db_add.txt" };

	for(i=0;i<2;i++){
		fp=fopen(filename[i],"r");
		if(fp==NULL){
			if(i>0)
				continue;
			printf("can't read %s\n",filename[i]);
			exit(1);
		}
		lines=ln=0;
		while(fgets(line,sizeof(line),fp)){
			lines++;
			if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
				continue;
			if(line[0]=='/' && line[1]=='/')
				continue;
			memset(str,0,sizeof(str));
			for(j=0,np=p=line;j<18 && p;j++){
				str[j]=p;
				p=strchr(p,',');
				if(p){ *p++=0; np=p; }
			}
			if(str[0] == NULL)
				continue;

			nameid = atoi(str[0]);
			if(nameid <= 0)
				continue;
			ln++;

			//ID,Name,Jname,Type,Price,Sell,Weight,ATK,DEF,Range,Slot,Job,Gender,Loc,wLV,eLV,View,Refine
			id = itemdb_search(nameid);
			strncpy(id->name,str[1],48);
			strncpy(id->jname,str[2],48);
			id->type = atoi(str[3]);
			// buy≠sell*2 は item_value_db.txt で指定してください。
			if(atoi(str[5])) {		// sell値を優先とする
				id->value_buy  = atoi(str[5])*2;
				id->value_sell = atoi(str[5]);
			} else {
				id->value_buy  = atoi(str[4]);
				id->value_sell = atoi(str[4])/2;
			}
			id->weight = atoi(str[6]);
			id->atk    = atoi(str[7]);
			itemdb_split_atoi(str[8],&id->def,&id->mdef);
			id->range  = atoi(str[9]);
			id->slot   = atoi(str[10]);
			id->class_ = (unsigned int)strtoul(str[11],NULL,0);
			id->sex    = atoi(str[12]);
			if(id->equip != atoi(str[13])) {
				id->equip = atoi(str[13]);
			}
			id->wlv = atoi(str[14]);
			if(id->wlv < 0 || id->wlv > MAX_WEAPON_LEVEL) {
				id->wlv = 0;
			}
			id->elv              = atoi(str[15]);
			id->look             = atoi(str[16]);
			id->refine           = atoi(str[17]);
			id->flag.available   = 1;
			id->flag.value_notdc = 0;
			id->flag.value_notoc = 0;
			id->flag.pet_egg     = 0;
			id->flag.pet_acce    = 0;
			id->view_id          = 0;
			id->group            = 0;
			id->delay            = 0;
			id->upper            = 0;
			id->zone             = 0;

			// force \0 terminal
			id->name[47]  = '\0';
			id->jname[47] = '\0';

			if((p = strchr(np,'{')) == NULL)
				continue;

			if(id->use_script)
				script_free_code(id->use_script);
			script = parse_script(p,filename[i],lines);

			id->use_script = (script != &error_code)? script: NULL;

			p++;
			while((p = strchr(p,'}')) != NULL) {
				p++;
				while(isspace((unsigned char)*p))
					p++;
				if(*p == ',')
					break;
			}
			if(p == NULL)
				continue;

			if(id->equip_script)
				script_free_code(id->equip_script);
			script = parse_script(p + 1,filename[i],lines);

			id->equip_script = (script != &error_code)? script: NULL;
		}
		fclose(fp);
		printf("read %s done (count=%d)\n",filename[i],ln);
	}

	fp=fopen("db/item_db2.txt","r");
	if(fp==NULL){
		printf("can't read db/item_db2.txt\n");
		return 0;
	}
	ln=0;
	while(fgets(line,sizeof(line),fp)){
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0]=='/' && line[1]=='/')
			continue;
		memset(str,0,sizeof(str));
		for(j=0,np=p=line;j<9 && p;j++){
			str[j]=p;
			p=strchr(p,',');
			if(p){ *p++=0; np=p; }
		}
		if(str[0] == NULL)
			continue;

		nameid = atoi(str[0]);
		if(nameid <= 0 || !(id = itemdb_exists(nameid)))
			continue;

		ln++;
		id->upper            = atoi(str[1]);
		id->zone             = atoi(str[2]);
		id->flag.dropable    = (atoi(str[3]) == 0)? 0: 1;
		id->flag.storageable = (atoi(str[4]) == 0)? 0: 1;
		id->flag.cartable    = (atoi(str[5]) == 0)? 0: 1;
		id->delay            = atoi(str[6]);
		id->flag.buyingable  = (atoi(str[7]) == 0)? 0: 1;
		id->flag.nonconsume  = (atoi(str[8]) == 0)? 0: 1;
	}
	fclose(fp);
	printf("read db/item_db2.txt done (count=%d)\n",ln);

	fp=fopen("db/item_arrowtype.txt","r");
	if(fp==NULL){
		printf("can't read db/item_arrowtype.txt\n");
		return 0;
	}
	while(fgets(line,sizeof(line),fp)){
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0]=='/' && line[1]=='/')
			continue;
		memset(str,0,sizeof(str));
		for(j=0,np=p=line;j<4 && p;j++){
			str[j]=p;
			p=strchr(p,',');
			if(p){ *p++=0; np=p; }
		}
		if(str[0] == NULL || str[3] == NULL)
			continue;

		nameid = atoi(str[0]);
		if(nameid <= 0 || !(id = itemdb_exists(nameid)))
			continue;
		//ID,Name,Jname,type
		id->arrow_type = atoi(str[3]);
	}
	fclose(fp);
	printf("read db/item_arrowtype.txt done\n");

	fp=fopen("db/item_group_db.txt","r");
	if(fp==NULL){
		printf("can't read db/item_group_db.txt\n");
		return 0;
	}
	while(fgets(line,sizeof(line),fp)){
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0]=='/' && line[1]=='/')
			continue;
		memset(str,0,sizeof(str));
		for(j=0,np=p=line;j<4 && p;j++){
			str[j]=p;
			p=strchr(p,',');
			if(p){ *p++=0; np=p; }
		}
		if(str[0] == NULL || str[3] == NULL)
			continue;

		nameid = atoi(str[0]);
		if(nameid <= 0 || !(id = itemdb_exists(nameid)))
			continue;
		//ID,Name,Jname,Group
		id->group = atoi(str[3]);
	}
	fclose(fp);
	printf("read db/item_group_db.txt done\n");
	return 0;
}

/*==========================================
 * アイテム価格テーブルのオーバーライド
 *------------------------------------------
 */
static int itemdb_read_itemvaluedb(void)
{
	FILE *fp;
	char line[1024];
	int ln=0;
	int nameid,j;
	char *str[7],*p;
	struct item_data *id;

	if( (fp=fopen("db/item_value_db.txt","r"))==NULL){
		printf("can't read db/item_value_db.txt\n");
		return -1;
	}

	while(fgets(line,1020,fp)){
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0]=='/' && line[1]=='/')
			continue;
		memset(str,0,sizeof(str));
		for(j=0,p=line;j<7 && p;j++){
			str[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		if(str[0] == NULL)
			continue;

		nameid = atoi(str[0]);
		if(nameid <= 0 || !(id = itemdb_exists(nameid)))
			continue;

		ln++;
		// それぞれ記述した個所のみオーバーライト
		if(str[3] != NULL && *str[3]) {
			id->value_buy = atoi(str[3]);
		}
		if(str[4] != NULL && *str[4]) {
			id->value_sell = atoi(str[4]);
		}
		if(str[5] != NULL && *str[5]) {
			id->flag.value_notdc = (atoi(str[5]) == 0)? 0: 1;
		}
		if(str[6] != NULL && *str[6]) {
			id->flag.value_notoc = (atoi(str[6]) == 0)? 0: 1;
		}
	}
	fclose(fp);
	printf("read db/item_value_db.txt done (count=%d)\n",ln);
	return 0;
}

/*==========================================
 * ランダムアイテム出現データの読み込み
 *------------------------------------------
 */
static int itemdb_read_randomitem(void)
{
	FILE *fp;
	char line[1024];
	int randomid,nameid,range,i,c;
	char *str[3],*p;

	// 読み込む度、初期化
	memset(&random_item, 0, sizeof(random_item));

	if((fp = fopen("db/item_random.txt","r")) == NULL) {
		printf("can't read db/item_random.txt\n");
		return 0;
	}

	while(fgets(line,sizeof(line),fp)) {
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0] == '/' && line[1] == '/')
			continue;
		memset(str,0,sizeof(str));
		for(i=0,p=line; i<3 && p; i++) {
			str[i]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		if(str[0] == NULL || str[1] == NULL || str[2] == NULL)
			continue;

		randomid = atoi(str[0]) - 1;
		if(randomid < 0 || randomid >= MAX_RAND_ITEM_TYPE)
			continue;
		nameid = atoi(str[1]);
		if(nameid < 0 || !itemdb_exists(nameid))
			continue;
		range = atoi(str[2]);
		if(range < 1 || range >= MAX_RAND_ITEM_AMOUNT)
			continue;

		c = random_item[randomid].entry;
		if(c >= MAX_RAND_ITEM_ENTRY)
			continue;
		if(c > 0)
			range += random_item[randomid].data[c-1].qty;

		if(range >= MAX_RAND_ITEM_AMOUNT)
			continue;

		random_item[randomid].data[c].nameid   = nameid;
		random_item[randomid].data[c].qty = range;
		random_item[randomid].entry++;
	}
	fclose(fp);
	printf("read db/item_random.txt done\n");

	return 0;
}

/*==========================================
 * アイテム使用可能フラグのオーバーライド
 *------------------------------------------
 */
static int itemdb_read_itemavail(void)
{
	FILE *fp;
	char line[1024];
	int ln=0;
	int nameid,j,k;
	char *str[2],*p;

	if( (fp=fopen("db/item_avail.txt","r"))==NULL ){
		printf("can't read db/item_avail.txt\n");
		return -1;
	}

	while(fgets(line,1020,fp)){
		struct item_data *id=NULL;
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0]=='/' && line[1]=='/')
			continue;
		memset(str,0,sizeof(str));
		for(j=0,p=line;j<2 && p;j++){
			str[j]=p;
			p=strchr(p,',');
			if(p) *p++=0;
		}
		if(str[0] == NULL || str[1] == NULL)
			continue;

		nameid = atoi(str[0]);
		if(nameid < 0 || !(id = itemdb_exists(nameid)))
			continue;
		k = atoi(str[1]);
		if(k > 0) {
			id->flag.available = 1;
			id->view_id = k;
		} else {
			id->flag.available = 0;
		}
		ln++;
	}
	fclose(fp);
	printf("read db/item_avail.txt done (count=%d)\n",ln);
	return 0;
}

/*==========================================
 * アイテムの名前テーブルを読み込む
 *------------------------------------------
 */
static int itemdb_read_itemnametable(void)
{
	char *buf,*p;
	int s;

	buf = (char *)grfio_reads("data\\idnum2itemdisplaynametable.txt",&s);

	if(buf == NULL)
		return -1;

	buf[s] = 0;
	for(p=buf; p-buf<s; ) {
		int nameid;
		char buf2[64];

		if(sscanf(p,"%d#%63[^#]#",&nameid,buf2) == 2) {
			char *jname = itemdb_jname(nameid);
			buf2[47] = '\0';	// force \0 terminal

#ifdef ITEMDB_OVERRIDE_NAME_VERBOSE
			if(itemdb_exists(nameid) && strcmp(jname, buf2) != 0) {
				printf("[override] %d %s => %s\n", nameid, jname, buf2);
			}
#endif
			memcpy(jname,buf2,48);
		}

		p=strchr(p,'\n');
		if(!p) break;
		p++;
	}
	aFree(buf);
	printf("read data\\idnum2itemdisplaynametable.txt done.\n");

	return 0;
}

/*==========================================
 * カードイラストのリソース名前テーブルを読み込む
 *------------------------------------------
 */
static int itemdb_read_cardillustnametable(void)
{
	char *buf,*p;
	int s;

	buf = (char *)grfio_reads("data\\num2cardillustnametable.txt",&s);

	if(buf == NULL)
		return -1;

	buf[s] = 0;
	for(p=buf; p-buf<s; ) {
		int nameid;
		char buf2[128];

		if(sscanf(p,"%d#%127[^#]#",&nameid,buf2) == 2) {
			buf2[59] = '\0';	// force \0
			strcat(buf2,".bmp");
			memcpy(itemdb_search(nameid)->cardillustname,buf2,64);
		}

		p=strchr(p,'\n');
		if(!p) break;
		p++;
	}
	aFree(buf);
	printf("read data\\num2cardillustnametable.txt done.\n");

	return 0;
}

/*==========================================
 * デバッガ
 *------------------------------------------
 */
#if 0
static int itemdb_debug_sub(void *key,void *data,va_list ap)
{
	struct item_data *id = (struct item_data *)data;
	FILE *fp = va_arg(ap,FILE *);

	fprintf(fp,"%6d : %s" RETCODE,(int)key,id->jname);
	return 0;
}

void itemdb_debug_txt(void)
{
	FILE *fp = fopen("itemdebug.txt","wt");

	if(fp) {
		numdb_foreach(item_db,itemdb_debug_sub,fp);
		fclose(fp);
	}
}
#endif

/*==========================================
 *
 *------------------------------------------
 */
static int itemdb_final(void *key,void *data,va_list ap)
{
	struct item_data *id;

	nullpo_retr(0, id = (struct item_data *)data);

	if(id->use_script)
		script_free_code(id->use_script);
	if(id->equip_script)
		script_free_code(id->equip_script);
	aFree(id);

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
void do_final_itemdb(void)
{
	if(item_db) {
		numdb_final(item_db,itemdb_final);
		item_db = NULL;
	}
}

/*==========================================
 *
 *------------------------------------------
 */
static void itemdb_read(void)
{
	itemdb_read_itemslottable();
	itemdb_read_itemdb();
	itemdb_read_itemvaluedb();
	itemdb_read_randomitem();
	itemdb_read_itemavail();

	if(battle_config.item_name_override_grffile)
		itemdb_read_itemnametable();
	itemdb_read_cardillustnametable();
}

/*==========================================
 *
 *------------------------------------------
 */
void itemdb_reload(void)
{
	itemdb_read();
}

/*==========================================
 *
 *------------------------------------------
 */
int do_init_itemdb(void)
{
	item_db = numdb_init();
	itemdb_read();

	return 0;
}
