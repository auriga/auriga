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
#include "lock.h"

#include "mapreg_txt.h"
#include "../script.h"

static struct dbt *mapreg_db;
static struct dbt *mapregstr_db;
int mapreg_dirty = 0;

char mapreg_txt[256] = "save/mapreg.txt";

/*==========================================
 * 設定ファイル読み込み
 *------------------------------------------
 */
int mapreg_txt_config_read_sub(const char *w1, const char *w2)
{
	if(strcmpi(w1,"mapreg_txt") == 0) {
		strncpy(mapreg_txt, w2, sizeof(mapreg_txt) - 1);
		mapreg_txt[sizeof(mapreg_txt) - 1] = '\0';

		return 1;
	}

	return 0;
}

/*==========================================
 * マップ変数の取得
 *------------------------------------------
 */
int mapreg_txt_getreg(int num)
{
	return PTR2INT(numdb_search(mapreg_db, num));
}

/*==========================================
 * マップ変数の変更
 *------------------------------------------
 */
int mapreg_txt_setreg(int num, int val, int eternal)
{
	if(val != 0)
		numdb_insert(mapreg_db, num, INT2PTR(val));
	else
		numdb_erase(mapreg_db, num);

	if(eternal)
		mapreg_dirty = 1;

	return 0;
}

/*==========================================
 * 文字列型マップ変数の取得
 *------------------------------------------
 */
char* mapreg_txt_getregstr(int num)
{
	return (char *)numdb_search(mapregstr_db, num);
}

/*==========================================
 * 文字列型マップ変数の変更
 *------------------------------------------
 */
int mapreg_txt_setregstr(int num, const char *str, int eternal)
{
	char *old_str = NULL;

	if(str && *str)
		old_str = (char *)numdb_insert(mapregstr_db, num, aStrdup(str));
	else
		old_str = (char *)numdb_erase(mapregstr_db, num);

	if(old_str)
		aFree(old_str);

	if(eternal)
		mapreg_dirty = 1;

	return 0;
}

/*==========================================
 * 永続的マップ変数の読み込み
 *------------------------------------------
 */
int mapreg_txt_load(void)
{
	FILE *fp;
	char line[2048];

	if( (fp=fopen(mapreg_txt,"rt"))==NULL )
		return -1;

	while(fgets(line,sizeof(line),fp)){
		char buf[256];
		int n,v,s,i;
		if( sscanf(line,"%255[^,],%d\t%n",buf,&i,&n)!=2 &&
		    (i=0,sscanf(line,"%255[^\t]\t%n",buf,&n)!=1) )
			continue;
		if(i < 0 || i >= 128) {
			printf("%s: %s broken data !\n",mapreg_txt,buf);
			continue;
		}
		if( buf[strlen(buf)-1]=='$' ){
			char buf2[2048];
			if( sscanf(line+n,"%[^\n\r]",buf2)!=1 ){
				printf("%s: %s broken data !\n",mapreg_txt,buf);
				continue;
			}
			s=script_add_str(buf);
			mapreg_setregstr((i<<24)|s, aStrdup(buf2), 0);
		}else{
			if( sscanf(line+n,"%d",&v)!=1 ){
				printf("%s: %s broken data !\n",mapreg_txt,buf);
				continue;
			}
			s=script_add_str(buf);
			mapreg_setreg((i<<24)|s, v, 0);
		}
	}
	fclose(fp);
	return 0;
}

/*==========================================
 * 永続的マップ変数の書き込み
 *------------------------------------------
 */
static int mapreg_txt_save_intsub(void *key, void *data, va_list ap)
{
	FILE *fp = va_arg(ap,FILE*);
	int num = PTR2INT(key)&0x00ffffff, i = PTR2INT(key)>>24;
	char *name = script_get_str(num);

	if(name[0] && name[1] != '@') {
		if(i == 0)
			fprintf(fp,"%s\t%d" RETCODE, name, PTR2INT(data));
		else
			fprintf(fp,"%s,%d\t%d" RETCODE, name, i, PTR2INT(data));
	}
	return 0;
}

static int mapreg_txt_save_strsub(void *key, void *data, va_list ap)
{
	FILE *fp = va_arg(ap,FILE*);
	int num = PTR2INT(key)&0x00ffffff, i = PTR2INT(key)>>24;
	const char *name = script_get_str(num);

	if(name[0] && name[1] != '@') {
		if(i == 0)
			fprintf(fp,"%s\t%s" RETCODE, name, (char *)data);
		else
			fprintf(fp,"%s,%d\t%s" RETCODE, name, i, (char *)data);
	}
	return 0;
}

static int mapreg_txt_save(void)
{
	FILE *fp;
	int lock;

	if( (fp = lock_fopen(mapreg_txt, &lock)) == NULL )
		return -1;

	numdb_foreach(mapreg_db, mapreg_txt_save_intsub, fp);
	numdb_foreach(mapregstr_db, mapreg_txt_save_strsub, fp);

	lock_fclose(fp, mapreg_txt, &lock);
	mapreg_dirty = 0;

	return 0;
}

/*==========================================
 * 永続的マップ変数の自動セーブ
 *------------------------------------------
 */
int mapreg_txt_autosave(void)
{
	if(mapreg_dirty)
		mapreg_txt_save();

	return 0;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
static int mapreg_txt_strdb_final(void *key, void *data, va_list ap)
{
	aFree(data);

	return 0;
}

int mapreg_txt_final(void)
{
	if(mapreg_dirty)
		mapreg_txt_save();

	if(mapreg_db)
		numdb_final(mapreg_db,NULL);
	if(mapregstr_db)
		strdb_final(mapregstr_db,mapreg_txt_strdb_final);

	return 0;
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
int mapreg_txt_init(void)
{
	mapreg_db    = numdb_init();
	mapregstr_db = numdb_init();
	mapreg_load();

	return 1;
}
