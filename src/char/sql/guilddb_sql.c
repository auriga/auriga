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

#include "db.h"
#include "malloc.h"
#include "utils.h"
#include "sqldbs.h"
#include "nullpo.h"

#include "../int_guild.h"
#include "storagedb_sql.h"
#include "guilddb_sql.h"

/*==========================================
 * 設定ファイル読込
 *------------------------------------------
 */
int guilddb_sql_config_read_sub(const char *w1,const char* w2)
{
	return 0;
}

/*==========================================
 * ギルド城データの読み込み
 *------------------------------------------
 */
static bool guildcastle_sql_read(void)
{
	int i;
	char **sql_row;
	bool result = false;

	// デフォルトデータを作成
	memset(castle_db, 0, sizeof(castle_db));
	for(i = 0; i < MAX_GUILDCASTLE; i++) {
		castle_db[i].castle_id = i;
		castle_db[i].economy   = 1;
		castle_db[i].defense   = 1;
	}

	result = sqldbs_query(&mysql_handle,
		"SELECT `castle_id`, `guild_id`, `economy`, `defense`, `triggerE`, `triggerD`, `nextTime`, `payTime`, `createTime`,"
		"`visibleC`, `visibleG0`, `visibleG1`, `visibleG2`, `visibleG3`, `visibleG4`, `visibleG5`, `visibleG6`, `visibleG7`"
		" FROM `" GUILD_CASTLE_TABLE "`"
	);
	if(result == false)
		return false;

	while((sql_row = sqldbs_fetch(&mysql_handle)) != NULL)
	{
		int id = atoi(sql_row[0]);
		struct guild_castle *gc;

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
	sqldbs_free_result(&mysql_handle);

	return 0;
}

/*==========================================
 * ギルド城データのセーブ
 *------------------------------------------
 */
static bool guild_guildcastle_save(void)
{
	static struct sqldbs_stmt *st = NULL;
	static struct guild_castle tmp_gc;
	bool result = false;

	if(st == NULL) {
		int i;

		st = sqldbs_stmt_init(&mysql_handle);
		if(st == NULL)
			return false;

		if( sqldbs_stmt_simpleprepare(st,
			"INSERT INTO `" GUILD_CASTLE_TABLE "` "
			"(`castle_id`, `guild_id`, `economy`, `defense`, `triggerE`, `triggerD`, `nextTime`, `payTime`, `createTime`, "
			"`visibleC`, `visibleG0`, `visibleG1`, `visibleG2`, `visibleG3`, `visibleG4`, `visibleG5`, `visibleG6`, `visibleG7`) "
			"VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?) "
			"ON DUPLICATE KEY UPDATE "
			"`guild_id` = ?, `economy` = ?, `defense` = ?, `triggerE` = ?, `triggerD` = ?, `nextTime` = ?, "
			"`payTime` = ?, `createTime` = ?, `visibleC` = ?, "
			"`visibleG0` = ?, `visibleG1` = ?, `visibleG2` = ?, `visibleG3` = ?, "
			"`visibleG4` = ?, `visibleG5` = ?, `visibleG6` = ?, `visibleG7` = ?"
		) == false ) {
			sqldbs_stmt_close(st);
			st = NULL;
			return false;
		}

		sqldbs_stmt_bind_param(st, 0, SQL_DATA_TYPE_INT, &tmp_gc.castle_id,  0);
		sqldbs_stmt_bind_param(st, 1, SQL_DATA_TYPE_INT, &tmp_gc.guild_id,   0);
		sqldbs_stmt_bind_param(st, 2, SQL_DATA_TYPE_INT, &tmp_gc.economy,    0);
		sqldbs_stmt_bind_param(st, 3, SQL_DATA_TYPE_INT, &tmp_gc.defense,    0);
		sqldbs_stmt_bind_param(st, 4, SQL_DATA_TYPE_INT, &tmp_gc.triggerE,   0);
		sqldbs_stmt_bind_param(st, 5, SQL_DATA_TYPE_INT, &tmp_gc.triggerD,   0);
		sqldbs_stmt_bind_param(st, 6, SQL_DATA_TYPE_INT, &tmp_gc.nextTime,   0);
		sqldbs_stmt_bind_param(st, 7, SQL_DATA_TYPE_INT, &tmp_gc.payTime,    0);
		sqldbs_stmt_bind_param(st, 8, SQL_DATA_TYPE_INT, &tmp_gc.createTime, 0);
		sqldbs_stmt_bind_param(st, 9, SQL_DATA_TYPE_INT, &tmp_gc.visibleC,   0);

		for(i = 0; i < 8; i++) {
			sqldbs_stmt_bind_param(st, i + 10, SQL_DATA_TYPE_INT, &tmp_gc.guardian[i].visible, 0);
		}

		sqldbs_stmt_bind_param(st, 18, SQL_DATA_TYPE_INT, &tmp_gc.guild_id,   0);
		sqldbs_stmt_bind_param(st, 19, SQL_DATA_TYPE_INT, &tmp_gc.economy,    0);
		sqldbs_stmt_bind_param(st, 20, SQL_DATA_TYPE_INT, &tmp_gc.defense,    0);
		sqldbs_stmt_bind_param(st, 21, SQL_DATA_TYPE_INT, &tmp_gc.triggerE,   0);
		sqldbs_stmt_bind_param(st, 22, SQL_DATA_TYPE_INT, &tmp_gc.triggerD,   0);
		sqldbs_stmt_bind_param(st, 23, SQL_DATA_TYPE_INT, &tmp_gc.nextTime,   0);
		sqldbs_stmt_bind_param(st, 24, SQL_DATA_TYPE_INT, &tmp_gc.payTime,    0);
		sqldbs_stmt_bind_param(st, 25, SQL_DATA_TYPE_INT, &tmp_gc.createTime, 0);
		sqldbs_stmt_bind_param(st, 26, SQL_DATA_TYPE_INT, &tmp_gc.visibleC,   0);

		for(i = 0; i < 8; i++) {
			sqldbs_stmt_bind_param(st, i + 27, SQL_DATA_TYPE_INT, &tmp_gc.guardian[i].visible, 0);
		}
	}

	if( sqldbs_transaction_start(&mysql_handle) == false )
		return false;

	// try
	do {
		int i;

		for(i = 0; i < MAX_GUILDCASTLE; i++) {
			memcpy(&tmp_gc, &castle_db[i], sizeof(tmp_gc));

			if( sqldbs_stmt_execute(st) == false )
				break;
		}
		if(i != MAX_GUILDCASTLE)
			break;

		// success
		result = true;
	} while(0);

	sqldbs_transaction_end(&mysql_handle, result);

	return result;
}

/*==========================================
 * 同期
 *------------------------------------------
 */
int guilddb_sql_sync(void)
{
	guild_guildcastle_save();
	return 0;
}

/*==========================================
 * ギルドIDからギルドデータをロード
 *------------------------------------------
 */
const struct guild *guilddb_sql_load_num(int guild_id)
{
	int i;
	char **sql_row;
	struct guild *g;
	bool result = false;

	g = (struct guild *)numdb_search(guild_db, guild_id);
	// キャッシュが存在
	if (g && g->guild_id == guild_id) {
		return g;
	}
	if (g == NULL) {
		g = (struct guild *)aMalloc(sizeof(struct guild));
		numdb_insert(guild_db, guild_id, g);
	}
	memset(g, 0, sizeof(struct guild));

	// 基本データ
	result = sqldbs_query(&mysql_handle,
		"SELECT `name`,`master`,`guild_lv`,`connect_member`,`max_member`,"
		"`average_lv`,`exp`,`next_exp`,`skill_point`,`mes1`,`mes2`,`emblem_len`,"
		"`emblem_id`,`emblem_data` FROM `" GUILD_TABLE "` WHERE `guild_id`='%d'", guild_id
	);
	if(result == false) {
		g->guild_id = -1;
		return NULL;
	}

	if((sql_row = sqldbs_fetch(&mysql_handle)) != NULL) {
		char emblem_data[4096];

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
		strncpy(g->mes1, sql_row[9], 60);
		strncpy(g->mes2, sql_row[10], 120);
		g->emblem_len = atoi(sql_row[11]);
		g->emblem_id  = atoi(sql_row[12]);
		strncpy(emblem_data, sql_row[13], 4096);

		guild_decode_emblem(g->emblem_data, emblem_data, g->emblem_len);

		// force \0 terminal
		g->name[23]   = '\0';
		g->master[23] = '\0';
		g->mes1[59]   = '\0';
		g->mes2[119]  = '\0';
	} else {
		sqldbs_free_result(&mysql_handle);
		g->guild_id = -1;
		return NULL;
	}
	sqldbs_free_result(&mysql_handle);

	// メンバー
	result = sqldbs_query(&mysql_handle,
		"SELECT `account_id`,`char_id`,`hair`,`hair_color`,`gender`,`class`,`lv`,"
		"`exp`,`exp_payper`,`online`,`position`,`name` FROM `" GUILD_MEMBER_TABLE "` "
		"WHERE `guild_id`='%d' ORDER BY `position`", guild_id
	);
	if(result == false) {
		g->guild_id = -1;
		return NULL;
	}

	for(i = 0; (sql_row = sqldbs_fetch(&mysql_handle)) && i < MAX_GUILD; i++) {
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
		strncpy(m->name, sql_row[11], 24);
		m->name[23] = '\0';	//  force \0 terminal
	}
	sqldbs_free_result(&mysql_handle);

	// 役職
	result = sqldbs_query(&mysql_handle,
		"SELECT `position`,`name`,`mode`,`exp_mode` FROM `" GUILD_POSITION_TABLE "` WHERE `guild_id`='%d'",
		guild_id
	);
	if(result == false) {
		g->guild_id = -1;
		return NULL;
	}

	for(i = 0; (sql_row = sqldbs_fetch(&mysql_handle)) && i < MAX_GUILDPOSITION; i++) {
		int position = atoi(sql_row[0]);
		struct guild_position *p = &g->position[position];
		strncpy(p->name, sql_row[1], 24);
		p->name[23] = '\0';	// force \0 terminal
		p->mode     = atoi(sql_row[2]);
		p->exp_mode = atoi(sql_row[3]);
	}
	sqldbs_free_result(&mysql_handle);

	// 同盟/敵対リスト
	result = sqldbs_query(&mysql_handle,
		"SELECT `opposition`,`alliance_id`,`name` FROM `" GUILD_ALLIANCE_TABLE "` WHERE `guild_id`='%d'",
		guild_id
	);
	if(result == false) {
		g->guild_id = -1;
		return NULL;
	}

	for(i = 0; (sql_row = sqldbs_fetch(&mysql_handle)) && i < MAX_GUILDALLIANCE; i++) {
		struct guild_alliance *a = &g->alliance[i];
		a->opposition = atoi(sql_row[0]);
		a->guild_id   = atoi(sql_row[1]);
		strncpy(a->name, sql_row[2], 24);
		a->name[23] = '\0';	// force \0 terminal
	}
	sqldbs_free_result(&mysql_handle);

	// 追放リスト
	result = sqldbs_query(&mysql_handle, "SELECT `name`,`mes`,`account_id` FROM `" GUILD_EXPULSION_TABLE "` WHERE `guild_id`='%d'", guild_id);
	if(result == false) {
		g->guild_id = -1;
		return NULL;
	}

	for(i = 0; (sql_row = sqldbs_fetch(&mysql_handle)) && i < MAX_GUILDEXPLUSION; i++) {
		struct guild_explusion *e = &g->explusion[i];
		strncpy(e->name, sql_row[0], 24);
		strncpy(e->mes, sql_row[1], 40);
		e->account_id = atoi(sql_row[2]);

		// force \0 terminal
		e->name[23] = '\0';
		e->mes[39]  = '\0';
	}
	sqldbs_free_result(&mysql_handle);

	// ギルドスキル
	result = sqldbs_query(&mysql_handle, "SELECT `id`,`lv` FROM `" GUILD_SKILL_TABLE "` WHERE `guild_id`='%d'", guild_id);
	if(result == false) {
		g->guild_id = -1;
		return NULL;
	}

	for(i = 0; (sql_row = sqldbs_fetch(&mysql_handle)) && i < MAX_GUILDSKILL; i++) {
		int n = atoi(sql_row[0]) - GUILD_SKILLID;
		if(n >= 0 && n < MAX_GUILDSKILL) {
			g->skill[n].id = atoi(sql_row[0]);
			g->skill[n].lv = atoi(sql_row[1]);
		}
	}
	sqldbs_free_result(&mysql_handle);

	// スキルツリー情報は初期化
	for(i = 0; i < MAX_GUILDSKILL; i++)
		g->skill[i].id = 0;

	// この関数内部でメモリ内部のギルドデータが書き換えられるが、
	// 渡すデータが同じなら帰ってくるデータも同じになるので、
	// 放置することにする
	guild_calc_skilltree(g);
	guild_calcinfo(g);

	return g;
}

/*==========================================
 * ギルド名からギルドデータをロード
 *------------------------------------------
 */
const struct guild* guilddb_sql_load_str(const char *str)
{
	char buf[256];

	if(sqldbs_query(&mysql_handle, "SELECT `guild_id` FROM `" GUILD_TABLE "` WHERE `name` = '%s'", strecpy(buf, str)))
	{
		int id_num = -1;
		char **sql_row = sqldbs_fetch(&mysql_handle);

		if(sql_row) {
			id_num = atoi(sql_row[0]);
		}
		sqldbs_free_result(&mysql_handle);

		if(id_num >= 0)
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

/*==========================================
 * セーブ
 *------------------------------------------
 */
bool guilddb_sql_save(struct guild *g2)
{
	const struct guild *g1;
	int i;
	char sep = ' ';
	char buf[256], tmp_sql[65536];
	char *p = tmp_sql;
	bool result = false;

	nullpo_retr(false, g2);

	g1 = guilddb_sql_load_num(g2->guild_id);
	if(g1 == NULL)
		return false;

	// 基本情報
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
	if(g1->emblem_len != g2->emblem_len || memcmp(g1->emblem_data, g2->emblem_data, g1->emblem_len)) {
		p += sprintf(p, "%c`emblem_data` = '", sep);
		for(i = 0; i < g2->emblem_len ; i++) {
			p += sprintf(p, "%02x", (unsigned char)g2->emblem_data[i]);
		}
		p += sprintf(p, "'");
		sep = ',';
	}

	if( sqldbs_transaction_start(&mysql_handle) == false )
		return false;

	// try
	do {
		if(sep == ',') {
			sprintf(p, " WHERE `guild_id` = '%d'", g2->guild_id);
			if( sqldbs_simplequery(&mysql_handle, tmp_sql) == false )
				break;
		}

		// メンバー
		if(memcmp(g1->member, g2->member, sizeof(g1->member))) {
			if( sqldbs_query(&mysql_handle, "DELETE FROM `" GUILD_MEMBER_TABLE "` WHERE `guild_id`='%d'", g2->guild_id) == false )
				break;

			for(i = 0; i < g2->max_member; i++) {
				if(g2->member[i].account_id > 0) {
					struct guild_member *m = &g2->member[i];
					if( sqldbs_query(&mysql_handle,
						"INSERT INTO `" GUILD_MEMBER_TABLE "` (`guild_id`,`account_id`,`char_id`,`hair`,`hair_color`,`gender`,"
						"`class`,`lv`,`exp`,`exp_payper`,`online`,`position`,`name`) VALUES "
						"('%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%s')",
						g2->guild_id, m->account_id, m->char_id, m->hair, m->hair_color, m->gender,
						m->class_, m->lv, m->exp, m->exp_payper, (int)m->online, m->position, strecpy(buf, m->name)
					) == false )
						break;
				}
			}
			if(i != g2->max_member)
				break;
		}

		// 役職
		if(memcmp(g1->position, g2->position, sizeof(g1->position))) {
			if( sqldbs_query(&mysql_handle, "DELETE FROM `" GUILD_POSITION_TABLE "` WHERE `guild_id`='%d'", g2->guild_id) == false )
				break;

			for(i = 0; i < MAX_GUILDPOSITION; i++) {
				struct guild_position *pos = &g2->position[i];
				if( sqldbs_query(&mysql_handle,
					"INSERT INTO `" GUILD_POSITION_TABLE "` (`guild_id`,`position`,`name`,`mode`,`exp_mode`) VALUES "
					"('%d','%d','%s','%d','%d')",
					g2->guild_id, i, strecpy(buf, pos->name), pos->mode, pos->exp_mode
				) == false )
					break;
			}
			if(i != MAX_GUILDPOSITION)
				break;
		}

		// 同盟/敵対リスト
		if(memcmp(g1->alliance, g2->alliance, sizeof(g1->alliance))) {
			if( sqldbs_query(&mysql_handle, "DELETE FROM `" GUILD_ALLIANCE_TABLE "` WHERE `guild_id`='%d'", g2->guild_id) == false )
				break;

			for(i = 0; i < MAX_GUILDALLIANCE; i++) {
				struct guild_alliance *a = &g2->alliance[i];
				if(a->guild_id > 0) {
					if( sqldbs_query(&mysql_handle,
						"INSERT INTO `" GUILD_ALLIANCE_TABLE "` (`guild_id`,`opposition`,`alliance_id`,`name`) VALUES "
						"('%d','%d','%d','%s')",
						g2->guild_id, a->opposition, a->guild_id, strecpy(buf, a->name)
					) == false )
						break;
				}
			}
			if(i != MAX_GUILDALLIANCE)
				break;
		}

		// 追放リスト
		if(memcmp(g1->explusion, g2->explusion, sizeof(g1->explusion))) {
			char buf2[256];

			if( sqldbs_query(&mysql_handle, "DELETE FROM `" GUILD_EXPULSION_TABLE "` WHERE `guild_id`='%d'", g2->guild_id) == false )
				break;

			for(i = 0; i < MAX_GUILDEXPLUSION; i++) {
				struct guild_explusion *e = &g2->explusion[i];
				if(e->account_id > 0) {
					if( sqldbs_query(&mysql_handle,
						"INSERT INTO `" GUILD_EXPULSION_TABLE "` (`guild_id`,`name`,`mes`,`account_id`) VALUES "
						"('%d','%s','%s','%d')",
						g2->guild_id, strecpy(buf, e->name), strecpy(buf2, e->mes), e->account_id
					) == false )
						break;
				}
			}
			if(i != MAX_GUILDEXPLUSION)
				break;
		}

		// ギルドスキル
		if(memcmp(g1->skill, g2->skill, sizeof(g1->skill))) {
			if( sqldbs_query(&mysql_handle, "DELETE FROM `" GUILD_SKILL_TABLE "` WHERE `guild_id`='%d'", g2->guild_id) == false )
				break;

			for(i = 0; i < MAX_GUILDSKILL; i++) {
				if(g2->skill[i].id > 0) {
					if( sqldbs_query(&mysql_handle,
						"INSERT INTO `" GUILD_SKILL_TABLE "` (`guild_id`,`id`,`lv`) VALUES "
						"('%d','%d','%d')",
						g2->guild_id, g2->skill[i].id, g2->skill[i].lv
					) == false )
						break;
				}
			}
			if(i != MAX_GUILDSKILL)
				break;
		}

		// success
		result = true;

		{
			// cache copy
			struct guild* g3 = (struct guild *)numdb_search(guild_db, g2->guild_id);
			if(g3)
				memcpy(g3, g2, sizeof(struct guild));
		}
	} while(0);

	sqldbs_transaction_end(&mysql_handle, result);

	return (guild_guildcastle_save() && result)? true: false;
}

/*==========================================
 * ギルド解散（同盟/敵対を解除）
 * SQL上から消すならメモリ上のギルドデータも
 * 消さないといけない
 *------------------------------------------
 */
static int guilddb_sql_delete_sub(void *key, void *data, va_list ap)
{
	struct guild *g = (struct guild *)data;
	int guild_id = va_arg(ap, int);
	int i;

	for(i = 0; i < MAX_GUILDALLIANCE; i++) {
		if(g->alliance[i].guild_id == guild_id)
			g->alliance[i].guild_id = 0;
	}
	return 0;
}

bool guilddb_sql_delete(int guild_id)
{
	bool result = false;

	if( sqldbs_transaction_start(&mysql_handle) == false )
		return false;

	// try
	do
	{
		int i;

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

		{
			// cache delete
			struct guild *g = (struct guild *)numdb_erase(guild_db, guild_id);
			if(g) {
				aFree(g);
			}
		}

		numdb_foreach(guild_db, guilddb_sql_delete_sub, guild_id);
		gstoragedb_delete(guild_id);
		mapif_guild_broken(guild_id, 0);

		for(i = 0; i < MAX_GUILDCASTLE; i++) {
			if(castle_db[i].guild_id == guild_id) {
				memset(&castle_db[i], 0, sizeof(castle_db[0]));
				castle_db[i].castle_id = i;
			}
		}
	} while(0);

	sqldbs_transaction_end(&mysql_handle, result);

	return result;
}

/*==========================================
 * ギルド作成
 *------------------------------------------
 */
bool guilddb_sql_new(struct guild *g)
{
	bool result = false;
	char t_name[64];
	char **sql_row;

	nullpo_retr(false, g);

	if( sqldbs_query(&mysql_handle, "SELECT MAX(`guild_id`) FROM `" GUILD_TABLE "`") == false )
		return false;

	sql_row = sqldbs_fetch(&mysql_handle);
	if(sql_row[0])
		g->guild_id = atoi(sql_row[0]) + 1;
	else
		g->guild_id = 10000;

	sqldbs_free_result(&mysql_handle);

	// DBに挿入
	result = sqldbs_query(
		&mysql_handle,
		"INSERT INTO `" GUILD_TABLE "` (`guild_id`,`name`,`guild_lv`,`max_member`,`emblem_data`) VALUES ('%d','%s','1','%d','')",
		g->guild_id, strecpy(t_name, g->name), g->max_member
	);
	if(result == false)
		return false;

	return guilddb_sql_save(g);
}

/*==========================================
 * 終了
 *------------------------------------------
 */
static int guild_sql_db_final(void *key, void *data, va_list ap)
{
	struct guild *g = (struct guild *)data;

	aFree(g);

	return 0;
}

void guilddb_sql_final(void)
{
	if(guild_db)
		numdb_final(guild_db, guild_sql_db_final);
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
bool guilddb_sql_init(void)
{
	bool result = false;

	guild_readdb();
	result = guildcastle_sql_read();

	guild_db = numdb_init();

	return result;
}
