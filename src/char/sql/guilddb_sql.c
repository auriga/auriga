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

#include "../int_guild.h"
#include "storagedb_sql.h"
#include "guilddb_sql.h"

static int guildcastle_sql_init(void);

bool guilddb_sql_init(void)
{
	guild_readdb();
	guildcastle_sql_init();
	guild_db=numdb_init();

	return true;
}

static int guildcastle_sql_init(void)
{
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;
	struct guild_castle *gc;
	int i,id;

	// デフォルトデータを作成
	memset(castle_db,0,sizeof(castle_db));
	for(i=0; i<MAX_GUILDCASTLE; i++) {
		castle_db[i].castle_id = i;
		castle_db[i].economy   = 1;
		castle_db[i].defense   = 1;
	}

	sqldbs_query(&mysql_handle, "SELECT "
		"`castle_id`, `guild_id`, `economy`, `defense`, `triggerE`, `triggerD`, `nextTime`, `payTime`, `createTime`,"
		"`visibleC`, `visibleG0`, `visibleG1`, `visibleG2`, `visibleG3`, `visibleG4`, `visibleG5`, `visibleG6`, `visibleG7`"
		" FROM `" GUILD_CASTLE_TABLE "`"
	);

	sql_res = sqldbs_store_result(&mysql_handle);

	if(sql_res) {
		for(i=0; (sql_row = sqldbs_fetch(sql_res)); i++)
		{
			id = atoi(sql_row[0]);
			if(id < 0 || id >= MAX_GUILDCASTLE)
				continue;
			gc = &castle_db[id];

			gc->guild_id            = atoi(sql_row[1]);
			gc->economy             = atoi(sql_row[2]);
			gc->defense             = atoi(sql_row[3]);
			gc->triggerE            = atoi(sql_row[4]);
			gc->triggerD            = atoi(sql_row[5]);
			gc->nextTime            = atoi(sql_row[6]);
			gc->payTime             = atoi(sql_row[7]);
			gc->createTime          = atoi(sql_row[8]);
			gc->visibleC            = atoi(sql_row[9]);
			gc->guardian[0].visible = atoi(sql_row[10]);
			gc->guardian[1].visible = atoi(sql_row[11]);
			gc->guardian[2].visible = atoi(sql_row[12]);
			gc->guardian[3].visible = atoi(sql_row[13]);
			gc->guardian[4].visible = atoi(sql_row[14]);
			gc->guardian[5].visible = atoi(sql_row[15]);
			gc->guardian[6].visible = atoi(sql_row[16]);
			gc->guardian[7].visible = atoi(sql_row[17]);
		}
		sqldbs_free_result(sql_res);
	}
	return 0;
}

static bool guildcastle_tosql(int castle_id)
{
	bool is_success;
	struct guild_castle *gc = &castle_db[castle_id];

	is_success = sqldbs_query(&mysql_handle,
		"INSERT INTO `" GUILD_CASTLE_TABLE "` "
		"(`castle_id`, `guild_id`, `economy`, `defense`, `triggerE`, `triggerD`, `nextTime`, `payTime`, `createTime`, "
		"`visibleC`, `visibleG0`, `visibleG1`, `visibleG2`, `visibleG3`, `visibleG4`, "
		"`visibleG5`, `visibleG6`, `visibleG7`) VALUES "
		"('%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', "
		"'%d', '%d', '%d', '%d', '%d', '%d', "
		"'%d', '%d', '%d') ON DUPLICATE KEY UPDATE "
		"`guild_id` = '%d', `economy` = '%d', `defense` = '%d', `triggerE` = '%d', `triggerD` = '%d', `nextTime` = '%d', "
		"`payTime` = '%d', `createTime` = '%d', `visibleC` = '%d', "
		"`visibleG0` = '%d', `visibleG1` = '%d', `visibleG2` = '%d', `visibleG3` = '%d', "
		"`visibleG4` = '%d', `visibleG5` = '%d', `visibleG6` = '%d', `visibleG7` = '%d' ",
		gc->castle_id, gc->guild_id, gc->economy, gc->defense, gc->triggerE, gc->triggerD, gc->nextTime, gc->payTime, gc->createTime,
		gc->visibleC, gc->guardian[0].visible, gc->guardian[1].visible, gc->guardian[2].visible, gc->guardian[3].visible, gc->guardian[4].visible,
		gc->guardian[5].visible, gc->guardian[6].visible, gc->guardian[7].visible,
		gc->guild_id, gc->economy, gc->defense, gc->triggerE, gc->triggerD, gc->nextTime,
		gc->payTime, gc->createTime, gc->visibleC,
		gc->guardian[0].visible, gc->guardian[1].visible, gc->guardian[2].visible, gc->guardian[3].visible,
		gc->guardian[4].visible, gc->guardian[5].visible, gc->guardian[6].visible, gc->guardian[7].visible
	);

	return is_success;
}

static int guild_guildcastle_save(void)
{
	int i;

	for(i=0;i<MAX_GUILDCASTLE;i++)
		guildcastle_tosql(i);
	return 0;
}

int guilddb_sql_sync(void)
{
	guild_guildcastle_save();
	return 0;
}

const struct guild *guilddb_sql_load_num(int guild_id)
{
	bool is_success;
	char emblem_data[4096];
	char *pstr;
	struct guild *g;
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;

	g = (struct guild*)numdb_search(guild_db,guild_id);
	// キャッシュが存在
	if (g && g->guild_id == guild_id) {
		return g;
	}
	if (g == NULL) {
		g = (struct guild *)aMalloc(sizeof(struct guild));
		numdb_insert(guild_db,guild_id,g);
	}
	memset(g,0,sizeof(struct guild));

	// 基本データ
	is_success = sqldbs_query(
		&mysql_handle,
		"SELECT `name`,`master`,`guild_lv`,`connect_member`,`max_member`,"
		"`average_lv`,`exp`,`next_exp`,`skill_point`,`mes1`,`mes2`,`emblem_len`,"
		"`emblem_id`,`emblem_data` FROM `" GUILD_TABLE "` WHERE `guild_id`='%d'", guild_id
	);
	if(!is_success) {
		g->guild_id = -1;
		return NULL;
	}

	sql_res = sqldbs_store_result(&mysql_handle);
	if (sql_res!=NULL && sqldbs_num_rows(sql_res)>0) {
		int i;
		sql_row = sqldbs_fetch(sql_res);
		if (sql_row==NULL) {
			sqldbs_free_result(sql_res);
			g->guild_id = -1;
			return NULL;
		}

		g->guild_id  = guild_id;
		strncpy(g->name,sql_row[0],24);
		strncpy(g->master,sql_row[1],24);
		g->guild_lv       = atoi(sql_row[2]);
		g->connect_member = atoi(sql_row[3]);
		if (atoi(sql_row[4]) > MAX_GUILD)
			g->max_member = MAX_GUILD;
		else
			g->max_member = atoi(sql_row[4]);
		g->average_lv  = atoi(sql_row[5]);
		g->exp         = atoi(sql_row[6]);
		g->next_exp    = atoi(sql_row[7]);
		g->skill_point = atoi(sql_row[8]);
		strncpy(g->mes1,sql_row[9],60);
		strncpy(g->mes2,sql_row[10],120);
		g->emblem_len = atoi(sql_row[11]);
		g->emblem_id  = atoi(sql_row[12]);
		strncpy(emblem_data,sql_row[13],4096);
		for(i=0,pstr=emblem_data;i<g->emblem_len;i++,pstr+=2){
			int c1=pstr[0],c2=pstr[1],x1=0,x2=0;
			if(c1>='0' && c1<='9')x1=c1-'0';
			if(c1>='a' && c1<='f')x1=c1-'a'+10;
			if(c1>='A' && c1<='F')x1=c1-'A'+10;
			if(c2>='0' && c2<='9')x2=c2-'0';
			if(c2>='a' && c2<='f')x2=c2-'a'+10;
			if(c2>='A' && c2<='F')x2=c2-'A'+10;
			g->emblem_data[i]=(x1<<4)|x2;
		}
		// force \0 terminal
		g->name[23]   = '\0';
		g->master[23] = '\0';
		g->mes1[59]   = '\0';
		g->mes2[119]  = '\0';
	} else {
		if( sql_res ) sqldbs_free_result(sql_res);
		g->guild_id = -1;
		return NULL;
	}
	sqldbs_free_result(sql_res);

	// メンバー
	is_success = sqldbs_query(
		&mysql_handle,
		"SELECT `account_id`,`char_id`,`hair`,`hair_color`,`gender`,`class`,`lv`,"
		"`exp`,`exp_payper`,`online`,`position`,`name` FROM `" GUILD_MEMBER_TABLE "` "
		"WHERE `guild_id`='%d' ORDER BY `position`", guild_id
	);
	if(!is_success) {
		g->guild_id = -1;
		return NULL;
	}
	sql_res = sqldbs_store_result(&mysql_handle);
	if (sql_res!=NULL && sqldbs_num_rows(sql_res)>0) {
		int i;
		for(i=0; (sql_row = sqldbs_fetch(sql_res)) && i<MAX_GUILD ;i++){
			struct guild_member *m = &g->member[i];
			m->account_id = atoi(sql_row[0]);
			m->char_id    = atoi(sql_row[1]);
			m->hair       = atoi(sql_row[2]);
			m->hair_color = atoi(sql_row[3]);
			m->gender     = atoi(sql_row[4]);
			m->class_     = atoi(sql_row[5]);
			m->lv         = atoi(sql_row[6]);
			m->exp        = atoi(sql_row[7]);
			m->exp_payper = atoi(sql_row[8]);
			m->online     = (unsigned char)atoi(sql_row[9]);
			if (atoi(sql_row[10]) >= MAX_GUILDPOSITION)
				m->position = MAX_GUILDPOSITION - 1;
			else
				m->position = atoi(sql_row[10]);
			strncpy(m->name,sql_row[11],24);
			m->name[23] = '\0';	//  force \0 terminal
		}
	}
	sqldbs_free_result(sql_res);

	// 役職
	is_success = sqldbs_query(
		&mysql_handle,
		"SELECT `position`,`name`,`mode`,`exp_mode` FROM `" GUILD_POSITION_TABLE "` WHERE `guild_id`='%d'",
		guild_id
	);
	if(!is_success) {
		g->guild_id = -1;
		return NULL;
	}
	sql_res = sqldbs_store_result(&mysql_handle);
	if (sql_res!=NULL && sqldbs_num_rows(sql_res)>0) {
		int i;
		for(i=0;((sql_row = sqldbs_fetch(sql_res))&&i<MAX_GUILDPOSITION);i++){
			int position = atoi(sql_row[0]);
			struct guild_position *p = &g->position[position];
			strncpy(p->name,sql_row[1],24);
			p->name[23] = '\0';	// force \0 terminal
			p->mode     = atoi(sql_row[2]);
			p->exp_mode = atoi(sql_row[3]);
		}
	}
	sqldbs_free_result(sql_res);

	// 同盟/敵対リスト
	is_success = sqldbs_query(
		&mysql_handle,
		"SELECT `opposition`,`alliance_id`,`name` FROM `" GUILD_ALLIANCE_TABLE "` WHERE `guild_id`='%d'",
		guild_id
	);
	if(!is_success) {
		g->guild_id = -1;
		return NULL;
	}
	sql_res = sqldbs_store_result(&mysql_handle);
	if (sql_res!=NULL && sqldbs_num_rows(sql_res)>0) {
		int i;
		for(i=0;((sql_row = sqldbs_fetch(sql_res))&&i<MAX_GUILDALLIANCE);i++){
			struct guild_alliance *a = &g->alliance[i];
			a->opposition = atoi(sql_row[0]);
			a->guild_id   = atoi(sql_row[1]);
			strncpy(a->name,sql_row[2],24);
			a->name[23] = '\0';	// force \0 terminal
		}
	}
	sqldbs_free_result(sql_res);

	// 追放リスト
	is_success = sqldbs_query(&mysql_handle, "SELECT `name`,`mes`,`account_id` FROM `" GUILD_EXPULSION_TABLE "` WHERE `guild_id`='%d'", guild_id);
	if(!is_success) {
		g->guild_id = -1;
		return NULL;
	}
	sql_res = sqldbs_store_result(&mysql_handle);
	if (sql_res!=NULL && sqldbs_num_rows(sql_res)>0) {
		int i;
		for(i=0;((sql_row = sqldbs_fetch(sql_res))&&i<MAX_GUILDEXPLUSION);i++){
			struct guild_explusion *e = &g->explusion[i];
			strncpy(e->name,sql_row[0],24);
			strncpy(e->mes,sql_row[1],40);
			e->account_id = atoi(sql_row[2]);

			// force \0 terminal
			e->name[23] = '\0';
			e->mes[39]  = '\0';
		}
	}
	sqldbs_free_result(sql_res);

	// ギルドスキル
	is_success = sqldbs_query(&mysql_handle, "SELECT `id`,`lv` FROM `" GUILD_SKILL_TABLE "` WHERE `guild_id`='%d'", guild_id);
	if(!is_success) {
		g->guild_id = -1;
		return NULL;
	}
	sql_res = sqldbs_store_result(&mysql_handle);
	if (sql_res!=NULL && sqldbs_num_rows(sql_res)>0) {
		int i,n;
		for(i=0;((sql_row = sqldbs_fetch(sql_res))&&i<MAX_GUILDSKILL);i++){
			n = atoi(sql_row[0]) - GUILD_SKILLID;
			if(n >= 0 && n < MAX_GUILDSKILL) {
				g->skill[n].id = atoi(sql_row[0]);
				g->skill[n].lv = atoi(sql_row[1]);
			}
		}

		// スキルツリー情報は初期化
		for(i = 0; i< MAX_GUILDSKILL;i++)
			g->skill[i].id = 0;
	}
	sqldbs_free_result(sql_res);

	// この関数内部でメモリ内部のギルドデータが書き換えられるが、
	// 渡すデータが同じなら帰ってくるデータも同じになるので、
	// 放置することにする
	guild_calc_skilltree(g);
	guild_calcinfo(g);

	return g;
}

const struct guild* guilddb_sql_load_str(char *str)
{
	int  id_num = -1;
	char buf[256];
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;

	sqldbs_query(
		&mysql_handle,
		"SELECT `guild_id` FROM `" GUILD_TABLE "` WHERE `name` = '%s'",
		strecpy(buf,str)
	);
	sql_res = sqldbs_store_result(&mysql_handle);
	if (sql_res) {
		sql_row = sqldbs_fetch(sql_res);
		if(sql_row) {
			id_num = atoi(sql_row[0]);
		}
		sqldbs_free_result(sql_res);
	}
	if(id_num >= 0) {
		return guilddb_sql_load_num(id_num);
	}
	return NULL;
}

#define UPDATE_NUM(val,sql) \
	if(g1->val != g2->val) {\
		p += sprintf(p,"%c`"sql"` = '%d'",sep,g2->val); sep = ',';\
	}
#define UPDATE_STR(val,sql) \
	if(strcmp(g1->val,g2->val)) {\
		p += sprintf(p,"%c`"sql"` = '%s'",sep,strecpy(buf,g2->val)); sep = ',';\
	}

bool guilddb_sql_save(struct guild* g2)
{
	int  i;
	char buf[256],buf2[256];
	char sep;
	char *p;
	const struct guild* g1 = guilddb_sql_load_num(g2->guild_id);

	if (g1 == NULL)
		return false;

	// 基本情報
	sep = ' ';
	p = tmp_sql;
	strcpy(p, "UPDATE `" GUILD_TABLE "` SET");
	p += strlen(p);

	UPDATE_STR(name          ,"name");
	UPDATE_STR(master        ,"master");
	UPDATE_NUM(guild_lv      ,"guild_lv");
	UPDATE_NUM(connect_member,"connect_member");
	UPDATE_NUM(max_member    ,"max_member");
	UPDATE_NUM(average_lv    ,"average_lv");
	UPDATE_NUM(exp           ,"exp");
	UPDATE_NUM(next_exp      ,"next_exp");
	UPDATE_NUM(skill_point   ,"skill_point");
	UPDATE_STR(mes1          ,"mes1");
	UPDATE_STR(mes2          ,"mes2");
	UPDATE_NUM(emblem_len    ,"emblem_len");
	UPDATE_NUM(emblem_id     ,"emblem_id");
	if(g1->emblem_len != g2->emblem_len || memcmp(g1->emblem_data,g2->emblem_data,g1->emblem_len)) {
		p += sprintf(p,"%c`emblem_data` = '",sep);
		for(i = 0; i < g2->emblem_len ; i++) {
			p += sprintf(p,"%02x",(unsigned char)g2->emblem_data[i]);
		}
		p += sprintf(p,"'");
		sep = ',';
	}

	if(sep == ',') {
		sprintf(p," WHERE `guild_id` = '%d'",g2->guild_id);
		sqldbs_query(&mysql_handle, tmp_sql);
	}

	// メンバー
	if(memcmp(g1->member,g2->member,sizeof(g1->member))) {
		sqldbs_query(&mysql_handle, "DELETE FROM `" GUILD_MEMBER_TABLE "` WHERE `guild_id`='%d'", g2->guild_id);

		for(i=0;i < g2->max_member;i++) {
			if (g2->member[i].account_id>0){
				struct guild_member *m = &g2->member[i];
				sqldbs_query(
					&mysql_handle,
					"INSERT INTO `" GUILD_MEMBER_TABLE "` (`guild_id`,`account_id`,`char_id`,`hair`,`hair_color`,`gender`,"
					"`class`,`lv`,`exp`,`exp_payper`,`online`,`position`,`name`) VALUES "
					"('%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%s')",
					g2->guild_id,m->account_id,m->char_id,m->hair,m->hair_color,m->gender,
					m->class_,m->lv,m->exp,m->exp_payper,(int)m->online,m->position,strecpy(buf,m->name)
				);
			}
		}
	}

	// 役職
	if(memcmp(g1->position,g2->position,sizeof(g1->position))) {
		sqldbs_query(&mysql_handle, "DELETE FROM `" GUILD_POSITION_TABLE "` WHERE `guild_id`='%d'", g2->guild_id);

		for(i=0;i<MAX_GUILDPOSITION;i++){
			struct guild_position *pos = &g2->position[i];
			sqldbs_query(
				&mysql_handle,
				"INSERT INTO `" GUILD_POSITION_TABLE "` (`guild_id`,`position`,`name`,`mode`,`exp_mode`) VALUES "
				"('%d','%d','%s','%d','%d')",
				g2->guild_id,i,strecpy(buf,pos->name),pos->mode,pos->exp_mode
			);
		}
	}

	// 同盟/敵対リスト
	if(memcmp(g1->alliance,g2->alliance,sizeof(g1->alliance))) {
		sqldbs_query(&mysql_handle, "DELETE FROM `" GUILD_ALLIANCE_TABLE "` WHERE `guild_id`='%d'", g2->guild_id);

		for(i=0;i<MAX_GUILDALLIANCE;i++){
			struct guild_alliance *a = &g2->alliance[i];
			if(a->guild_id>0){
				sqldbs_query(
					&mysql_handle,
					"INSERT INTO `" GUILD_ALLIANCE_TABLE "` (`guild_id`,`opposition`,`alliance_id`,`name`) VALUES "
					"('%d','%d','%d','%s')",
					g2->guild_id,a->opposition,a->guild_id,strecpy(buf,a->name)
				);
			}
		}
	}

	// 追放リスト
	if(memcmp(g1->explusion,g2->explusion,sizeof(g1->explusion))) {
		sqldbs_query(&mysql_handle, "DELETE FROM `" GUILD_EXPULSION_TABLE "` WHERE `guild_id`='%d'", g2->guild_id);

		for(i=0;i<MAX_GUILDEXPLUSION;i++) {
			struct guild_explusion *e = &g2->explusion[i];
			if(e->account_id>0) {
				sqldbs_query(
					&mysql_handle,
					"INSERT INTO `" GUILD_EXPULSION_TABLE "` (`guild_id`,`name`,`mes`,`account_id`) VALUES "
					"('%d','%s','%s','%d')",
					g2->guild_id,strecpy(buf,e->name),strecpy(buf2,e->mes),e->account_id
				);
			}
		}
	}

	// ギルドスキル
	if(memcmp(g1->skill,g2->skill,sizeof(g1->skill))) {
		sqldbs_query(&mysql_handle, "DELETE FROM `" GUILD_SKILL_TABLE "` WHERE `guild_id`='%d'", g2->guild_id);

		for(i=0;i<MAX_GUILDSKILL;i++) {
			if (g2->skill[i].id > 0) {
				sqldbs_query(
					&mysql_handle,
					"INSERT INTO `" GUILD_SKILL_TABLE "` (`guild_id`,`id`,`lv`) VALUES "
					"('%d','%d','%d')",
					g2->guild_id,g2->skill[i].id,g2->skill[i].lv
				);
			}
		}
	}

	{
		struct guild* g3 = (struct guild *)numdb_search(guild_db,g2->guild_id);
		if(g3)
			memcpy(g3,g2,sizeof(struct guild));
	}
	guild_guildcastle_save();

	return true;
}

// ギルド解散処理用（同盟/敵対を解除）
// SQL 上から消すなら、メモリ上のギルドデータも消さないといけない
static int guilddb_sql_delete_sub(void *key,void *data,va_list ap)
{
	struct guild *g=(struct guild *)data;
	int guild_id=va_arg(ap,int);
	int i;

	for(i=0;i<MAX_GUILDALLIANCE;i++){
		if(g->alliance[i].guild_id==guild_id)
			g->alliance[i].guild_id=0;
	}
	return 0;
}

void guilddb_sql_delete(int guild_id)
{
	int i;
	bool result = false;
	struct guild* g = (struct guild *)numdb_search(guild_db,guild_id);

	// start transaction
	if( sqldbs_simplequery(&mysql_handle, "START TRANSACTION") == false )
		return;

	// try
	do
	{
		// delete guild
		if( sqldbs_query(&mysql_handle, "DELETE FROM `" GUILD_TABLE "` WHERE `guild_id`='%d'", guild_id) == false )
			break;

		// delete guild member
		if( sqldbs_query(&mysql_handle, "DELETE FROM `" GUILD_MEMBER_TABLE "` WHERE `guild_id`='%d'", guild_id) == false )
			break;

		// delete guild position
		if( sqldbs_query(&mysql_handle, "DELETE FROM `" GUILD_POSITION_TABLE "` WHERE `guild_id`='%d'", guild_id) == false )
			break;

		// delete guild alliance
		if( sqldbs_query(&mysql_handle, "DELETE FROM `" GUILD_ALLIANCE_TABLE "` WHERE `guild_id`='%d' OR `alliance_id`='%d'", guild_id, guild_id) == false )
			break;

		// delete guild expulsion
		if( sqldbs_query(&mysql_handle, "DELETE FROM `" GUILD_EXPULSION_TABLE "` WHERE `guild_id`='%d'", guild_id) == false )
			break;

		// delete guild skill
		if( sqldbs_query(&mysql_handle, "DELETE FROM `" GUILD_SKILL_TABLE "` WHERE `guild_id`='%d'", guild_id) == false )
			break;

		// success
		result = true;

		// cache delete
		if( g )
		{
			numdb_erase(guild_db,g->guild_id);
			aFree(g);
		}
		numdb_foreach(guild_db,guilddb_sql_delete_sub,guild_id);
		gstoragedb_delete(guild_id);
		mapif_guild_broken(guild_id,0);

		for( i = 0; i < MAX_GUILDCASTLE; i++ )
		{
			if( castle_db[i].guild_id == guild_id )
			{
				memset(&castle_db[i],0,sizeof(castle_db[0]));
				castle_db[i].castle_id = i;
			}
		}
	}while(0);

	// end transaction
	sqldbs_simplequery(&mysql_handle, ( result == true )? "COMMIT" : "ROLLBACK");

	return;
}

bool guilddb_sql_new(struct guild *g)
{
	bool is_success;
	char t_name[64];
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;

	// ギルドIDを読み出す
	is_success = sqldbs_query(&mysql_handle, "SELECT MAX(`guild_id`) FROM `" GUILD_TABLE "`");
	if(!is_success)
		return false;

	sql_res = sqldbs_store_result(&mysql_handle);
	if(!sql_res)
		return false;

	sql_row = sqldbs_fetch(sql_res);
	if(sql_row[0])
		g->guild_id = atoi(sql_row[0]) + 1;
	else
		g->guild_id = 10000;

	sqldbs_free_result(sql_res);

	// DBに挿入
	sqldbs_query(
		&mysql_handle,
		"INSERT INTO `" GUILD_TABLE "` (`guild_id`,`name`,`guild_lv`,`max_member`,`emblem_data`) VALUES ('%d','%s','1','%d','')",
		g->guild_id,strecpy(t_name,g->name),g->max_member
	);

	guilddb_sql_save(g);
	return true;
}

int guilddb_sql_config_read_sub(const char *w1,const char* w2)
{
	return 0;
}

static int guild_sql_db_final(void *key,void *data,va_list ap)
{
	struct guild *g = (struct guild *)data;

	aFree(g);
	return 0;
}

void guilddb_sql_final(void)
{
	if(guild_db)
		numdb_final(guild_db,guild_sql_db_final);
}
