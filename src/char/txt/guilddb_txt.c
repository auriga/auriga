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
#include "lock.h"
#include "malloc.h"
#include "journal.h"
#include "utils.h"
#include "nullpo.h"

#include "../int_guild.h"
#include "storagedb_txt.h"
#include "guilddb_txt.h"

static int guildcastle_txt_sync(void);

static int guild_newid=10000;
static char guild_txt[1024]  = "save/guild.txt";
static char castle_txt[1024] = "save/castle.txt";

#ifdef TXT_JOURNAL
static int guild_journal_enable = 1;
static struct journal guild_journal;
static char guild_journal_file[1024] = "./save/guild.journal";
static int guild_journal_cache = 1000;

int guildcastle_journal_enable = 1;
struct journal guildcastle_journal;
static char guildcastle_journal_file[1024] = "./save/castle.journal";
static int guildcastle_journal_cache = 1000;

#endif

/*==========================================
 * 設定ファイル読込
 *------------------------------------------
 */
int guilddb_txt_config_read_sub(const char* w1,const char *w2)
{
	if(strcmpi(w1,"guild_txt")==0){
		strncpy(guild_txt,w2,sizeof(guild_txt) - 1);
	}
	else if(strcmpi(w1,"castle_txt")==0){
		strncpy(castle_txt,w2,sizeof(castle_txt) - 1);
	}
#ifdef TXT_JOURNAL
	else if(strcmpi(w1,"guild_journal_enable")==0){
		guild_journal_enable = atoi( w2 );
	}
	else if(strcmpi(w1,"guild_journal_file")==0){
		strncpy( guild_journal_file, w2, sizeof(guild_journal_file) - 1 );
	}
	else if(strcmpi(w1,"guild_journal_cache_interval")==0){
		guild_journal_cache = atoi( w2 );
	}
	else if(strcmpi(w1,"castle_journal_enable")==0){
		guildcastle_journal_enable = atoi( w2 );
	}
	else if(strcmpi(w1,"castle_journal_file")==0){
		strncpy( guildcastle_journal_file, w2, sizeof(guildcastle_journal_file) - 1 );
	}
	else if(strcmpi(w1,"castle_journal_cache_interval")==0){
		guildcastle_journal_cache = atoi( w2 );
	}
#endif
	else {
		return 0;
	}

	return 1;
}

/*==========================================
 * ギルドデータを文字列へ変換
 *------------------------------------------
 */
static int guild_tostr(char *str, struct guild *g)
{
	int i, c, len;

	nullpo_retr(1, g);

	// 基本データ
	len = sprintf(str, "%d\t%s\t%s\t%d,%d,%d,%d\t%s#\t%s#\t",
		g->guild_id, g->name, g->master,
		g->guild_lv, g->max_member, g->exp, g->skill_point, g->mes1, g->mes2);

	// メンバー
	for(i = 0; i < g->max_member; i++) {
		struct guild_member *m = &g->member[i];
		len += sprintf(str + len, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\t%s\t",
			m->account_id,m->char_id,
			m->hair,m->hair_color,m->gender,
			m->class_,m->lv,m->exp,m->exp_payper,m->position,
			((m->account_id > 0)? m->name: "-"));
	}

	// 役職
	for(i = 0; i < MAX_GUILDPOSITION; i++) {
		struct guild_position *p = &g->position[i];
		len += sprintf(str + len, "%d,%d\t%s#\t", p->mode, p->exp_mode, p->name);
	}

	// エンブレム
	len += sprintf(str + len, "%d,%d,", g->emblem_len, g->emblem_id);
	for(i = 0; i < g->emblem_len; i++) {
		len += sprintf(str + len, "%02x", (unsigned char)(g->emblem_data[i]));
	}
	len += sprintf(str + len, "$\t");

	// 同盟/敵対リスト
	for(i = 0, c = 0; i < MAX_GUILDALLIANCE; i++) {
		if(g->alliance[i].guild_id > 0)
			c++;
	}
	len += sprintf(str + len, "%d\t", c);
	for(i = 0; i < MAX_GUILDALLIANCE; i++) {
		struct guild_alliance *a = &g->alliance[i];
		if(a->guild_id > 0)
			len += sprintf(str + len, "%d,%d\t%s\t", a->guild_id, a->opposition, a->name);
	}

	// 追放リスト
	for(i = 0, c = 0; i < MAX_GUILDEXPLUSION; i++) {
		if(g->explusion[i].account_id > 0)
			c++;
	}
	len += sprintf(str + len, "%d\t", c);
	for(i = 0; i < MAX_GUILDEXPLUSION; i++) {
		struct guild_explusion *e = &g->explusion[i];
		if(e->account_id > 0)
			len += sprintf(str + len, "%d\t%s\t%s#\t", e->account_id, e->name, e->mes);
	}

	// ギルドスキル
	for(i = 0; i < MAX_GUILDSKILL; i++) {
		len += sprintf(str + len, "%d,%d ", g->skill[i].id, g->skill[i].lv);
	}
	len += sprintf(str + len, "\t");

	return 0;
}

/*==========================================
 * ギルドデータを文字列から変換
 *------------------------------------------
 */
static int guild_fromstr(char *str, struct guild *g)
{
	int i, j, c;
	int tmp_int[10];
	char tmp_str[4][256];
	char tmp_str2[4097];	// binary data + 1

	nullpo_retr(1, g);

	// 基本データ
	memset(g, 0, sizeof(struct guild));

	if( sscanf(str, "%d\t%255[^\t]\t%255[^\t]\t%d,%d,%d,%d,%d\t%255[^\t]\t%255[^\t]\t",
		&tmp_int[0],tmp_str[0],tmp_str[1],
		&tmp_int[1],&tmp_int[2],&tmp_int[3],&tmp_int[4],&tmp_int[5],
		tmp_str[2],tmp_str[3]) != 10)
	{
		// Auriga-0177以降の形式
		if( sscanf(str, "%d\t%255[^\t]\t%255[^\t]\t%d,%d,%d,%d\t%255[^\t]\t%255[^\t]\t",
			&tmp_int[0],tmp_str[0],tmp_str[1],
			&tmp_int[1],&tmp_int[2],&tmp_int[3],&tmp_int[4],
			tmp_str[2],tmp_str[3]) != 9)
			return 1;
	}

	g->guild_id    = tmp_int[0];
	g->guild_lv    = tmp_int[1];
	g->max_member  = tmp_int[2];
	g->exp         = tmp_int[3];
	g->skill_point = tmp_int[4];
	strncpy(g->name, tmp_str[0], 24);
	strncpy(g->master, tmp_str[1], 24);
	tmp_str[2][strlen(tmp_str[2]) - 1] = 0;
	strncpy(g->mes1, tmp_str[2], 60);
	tmp_str[3][strlen(tmp_str[3]) - 1] = 0;
	strncpy(g->mes2, tmp_str[3], 120);

	// force \0 terminal
	g->name[23]   = '\0';
	g->master[23] = '\0';
	g->mes1[59]   = '\0';
	g->mes2[119]  = '\0';

	for(j = 0; j < 6 && str != NULL; j++)	// 位置スキップ
		str = strchr(str + 1, '\t');
	//printf("GuildBaseInfo OK\n");

	// メンバー
	for(i = 0; i < g->max_member && i < MAX_GUILD; i++) {
		struct guild_member *m = &g->member[i];
		if( sscanf(str+1, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\t%255[^\t]\t",
			&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],&tmp_int[4],
			&tmp_int[5],&tmp_int[6],&tmp_int[7],&tmp_int[8],&tmp_int[9],
			tmp_str[0]) < 11)
			return 1;

		m->account_id = tmp_int[0];
		m->char_id    = tmp_int[1];
		m->hair       = tmp_int[2];
		m->hair_color = tmp_int[3];
		m->gender     = tmp_int[4];
		m->class_     = tmp_int[5];
		m->lv         = tmp_int[6];
		m->exp        = tmp_int[7];
		m->exp_payper = tmp_int[8];
		m->position   = tmp_int[9];
		strncpy(m->name, tmp_str[0], 24);
		m->name[23] = '\0';	// force \0 terminal

		for(j = 0; j < 2 && str != NULL; j++)	// 位置スキップ
			str = strchr(str + 1, '\t');
	}
	if(g->max_member != i) {
		printf("int_guild: max guild member changed %d -> %d\n", g->max_member, i);
		g->max_member = i;
	}

	// 役職
	for(i = 0; i < MAX_GUILDPOSITION; i++) {
		struct guild_position *p = &g->position[i];
		if( sscanf(str + 1, "%d,%d\t%255[^\t]\t",
			&tmp_int[0], &tmp_int[1], tmp_str[0]) < 3)
			return 1;

		p->mode     = tmp_int[0];
		p->exp_mode = tmp_int[1];
		tmp_str[0][strlen(tmp_str[0])-1] = 0;
		strncpy(p->name, tmp_str[0], 24);
		p->name[23] = '\0';	// force \0 terminal

		for(j = 0; j < 2 && str != NULL; j++)	// 位置スキップ
			str = strchr(str + 1, '\t');
	}

	// エンブレム
	tmp_int[1] = 0;
	if( sscanf(str + 1, "%d,%d,%4096[^\t]\t", &tmp_int[0], &tmp_int[1], tmp_str2) < 3 )
		return 1;

	g->emblem_len = tmp_int[0];
	g->emblem_id  = tmp_int[1];
	if(g->emblem_len > sizeof(tmp_str2) / 2) {
		// エンブレムのデータ長が大きすぎる
		return 1;
	}
	guild_decode_emblem(g->emblem_data, tmp_str2, g->emblem_len);

	//printf("GuildEmblemInfo OK\n");
	str = strchr(str + 1, '\t');	// 位置スキップ

	// 同盟/敵対リスト
	if( sscanf(str + 1, "%d\t", &c)< 1)
		return 1;

	str = strchr(str + 1, '\t');	// 位置スキップ
	for(i = 0; i < c && i < MAX_GUILDALLIANCE; i++) {
		struct guild_alliance *a = &g->alliance[i];
		if( sscanf(str + 1, "%d,%d\t%255[^\t]\t",
			&tmp_int[0], &tmp_int[1], tmp_str[0]) < 3)
			return 1;

		a->guild_id   = tmp_int[0];
		a->opposition = tmp_int[1];
		strncpy(a->name, tmp_str[0], 24);
		a->name[23] = '\0';	// force \0 terminal

		for(j = 0; j < 2 && str != NULL; j++)	// 位置スキップ
			str = strchr(str + 1, '\t');
	}
	//printf("GuildAllianceInfo OK\n");

	// 追放リスト
	if( sscanf(str + 1, "%d\t", &c) < 1)
		return 1;

	str = strchr(str + 1, '\t');	// 位置スキップ
	for(i = 0; i < c && i < MAX_GUILDEXPLUSION; i++) {
		struct guild_explusion *e = &g->explusion[i];
		int ret, step;

		ret = sscanf(str + 1, "%d,%d,%d,%d\t%255[^\t]\t%255[^\t]\t%255[^\t]\t",
			&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],
			tmp_str[0],tmp_str[2],tmp_str[1]);
		if(ret != 7) {
			// Auriga-0142以降の形式
			ret = sscanf(str + 1, "%d\t%255[^\t]\t%255[^\t]\t",
				&tmp_int[0],tmp_str[0],tmp_str[1]);
			if(ret != 3)
				return 1;
			step = 3;
		} else {
			step = 4;
		}
		e->account_id = tmp_int[0];
		strncpy(e->name, tmp_str[0], 24);
		tmp_str[1][strlen(tmp_str[1]) - 1] = 0;
		strncpy(e->mes, tmp_str[1], 40);

		// force \0 terminal
		e->name[23] = '\0';
		e->mes[39]  = '\0';

		for(j = 0; j < step && str != NULL; j++)	// 位置スキップ
			str = strchr(str + 1, '\t');
	}
	//printf("GuildExplusionInfo OK\n");

	// ギルドスキル
	for(i = 0; i < MAX_GUILDSKILL; i++) {
		int n;
		if( sscanf(str+1, "%d,%d ", &tmp_int[0], &tmp_int[1]) < 2)
			break;
		n = tmp_int[0] - GUILD_SKILLID;
		if(n >= 0 && n < MAX_GUILDSKILL) {
			g->skill[n].id = tmp_int[0];
			g->skill[n].lv = tmp_int[1];
		}
		str = strchr(str + 1, ' ');
	}

	// スキルツリー情報は初期化
	for(i = 0; i < MAX_GUILDSKILL; i++)
		g->skill[i].id = 0;

	//str = strchr(str + 1, '\t');
	//printf("GuildSkillInfo OK\n");

	return 0;
}

#ifdef TXT_JOURNAL
// ==========================================
// ギルドデータのジャーナルのロールフォワード用コールバック関数
// ------------------------------------------
int guild_journal_rollforward( int key, void* buf, int flag )
{
	struct guild* g = (struct guild *)numdb_search( guild_db, key );

	// 念のためチェック
	if( flag == JOURNAL_FLAG_WRITE && key != ((struct guild*)buf)->guild_id )
	{
		printf("int_guild: journal: key != guild_id !\n");
		return 0;
	}

	// データの置き換え
	if( g )
	{
		if(flag == JOURNAL_FLAG_DELETE) {
			numdb_erase( guild_db, key );
			aFree(g);
		} else {
			memcpy( g, buf, sizeof(struct guild) );
		}
		return 1;
	}

	// 追加
	if( flag != JOURNAL_FLAG_DELETE )
	{
		g = (struct guild*) aCalloc( 1, sizeof( struct guild ) );
		memcpy( g, buf, sizeof(struct guild) );
		numdb_insert( guild_db, key, g );
		if( g->guild_id >= guild_newid)
			guild_newid = g->guild_id + 1;
		return 1;
	}

	return 0;
}
#endif

/*==========================================
 * ギルドデータファイルの読み込み
 *------------------------------------------
 */
static bool guilddb_txt_read(void)
{
	FILE *fp;
	bool ret = true;

	guild_readdb();

	guild_db = numdb_init();

	if((fp = fopen(guild_txt, "r")) == NULL) {
		printf("guilddb_txt_read: open [%s] failed !\n", guild_txt);
		ret = false;
	} else {
		int count = 0;
		char line[16384];

		while(fgets(line, sizeof(line), fp)) {
			struct guild *g = (struct guild *)aCalloc(1, sizeof(struct guild));
			if(guild_fromstr(line, g) == 0 && g->guild_id > 0) {
				if(g->guild_id >= guild_newid)
					guild_newid = g->guild_id + 1;
				numdb_insert(guild_db, g->guild_id, g);
				guild_calc_skilltree(g);
				guild_calcinfo(g);
			} else {
				printf("int_guild: broken data [%s] line %d\n", guild_txt, count);
				aFree(g);
			}
			count++;
		}
		fclose(fp);
		//printf("int_guild: %s read done (%d guilds)\n",guild_txt,c);
	}

#ifdef TXT_JOURNAL
	if( guild_journal_enable )
	{
		// ジャーナルデータのロールフォワード
		if( journal_load( &guild_journal, sizeof(struct guild), guild_journal_file ) )
		{
			int c = journal_rollforward( &guild_journal, guild_journal_rollforward );

			printf("int_guild: guild_journal: roll-forward (%d)\n", c );

			// ロールフォワードしたので、txt データを保存する ( journal も新規作成される)
			guilddb_txt_sync();
		}
		else
		{
			// ジャーナルを新規作成する
			journal_final( &guild_journal );
			journal_create( &guild_journal, sizeof(struct guild), guild_journal_cache, guild_journal_file );
		}
	}
#endif

	return ret;
}

/*==========================================
 * ギルドIDからギルド情報をロード
 *------------------------------------------
 */
const struct guild *guilddb_txt_load_num(int guild_id)
{
	struct guild *g = (struct guild *)numdb_search(guild_db, guild_id);

	if(g)
		guild_calcinfo(g);

	return g;
}

/*==========================================
 * ギルドデータの同期
 *------------------------------------------
 */
static int guilddb_txt_sync_sub(void *key, void *data, va_list ap)
{
	char line[16384];
	FILE *fp;

	guild_tostr(line, (struct guild *)data);
	fp = va_arg(ap, FILE *);
	fprintf(fp, "%s" NEWLINE, line);
	return 0;
}

int guilddb_txt_sync(void)
{
	FILE *fp;
	int lock;

	if( !guild_db )
		return 1;

	if( (fp = lock_fopen(guild_txt, &lock)) == NULL ) {
		printf("guilddb_txt_sync: can't write [%s] !!! data is lost !!!\n", guild_txt);
		return 1;
	}
	numdb_foreach(guild_db, guilddb_txt_sync_sub, fp);
	lock_fclose(fp, guild_txt, &lock);

#ifdef TXT_JOURNAL
	if( guild_journal_enable )
	{
		// コミットしたのでジャーナルを新規作成する
		journal_final( &guild_journal );
		journal_create( &guild_journal, sizeof(struct guild), guild_journal_cache, guild_journal_file );
	}
#endif

	guildcastle_txt_sync();
	return 0;
}

/*==========================================
 * ギルド名からギルド情報をロード
 *------------------------------------------
 */
static int guilddb_txt_load_str_sub(void *key, void *data, va_list ap)
{
	struct guild *g, **dst;
	const char *str;

	g   = (struct guild *)data;
	str = va_arg(ap, const char *);
	dst = va_arg(ap, struct guild **);

	if(*dst == NULL) {
		if(strcmp(g->name, str) == 0)
			*dst = g;
	}
	return 0;
}

const struct guild* guilddb_txt_load_str(const char *str)
{
	struct guild *g = NULL;

	numdb_foreach(guild_db, guilddb_txt_load_str_sub, str, &g);
	return g;
}

/*==========================================
 * ギルド解散（同盟/敵対を解除）
 *------------------------------------------
 */
static int guilddb_txt_delete_sub(void *key, void *data, va_list ap)
{
	struct guild *g = (struct guild *)data;
	int guild_id = va_arg(ap, int);
	int i;

	for(i = 0; i < MAX_GUILDALLIANCE; i++) {
		if(g->alliance[i].guild_id == guild_id)
		{
			g->alliance[i].guild_id = 0;
#ifdef TXT_JOURNAL
			if( guild_journal_enable )
				journal_write( &guild_journal, g->guild_id, g );
#endif
		}
	}
	return 0;
}

bool guilddb_txt_delete(int guild_id)
{
	struct guild *g = (struct guild *)numdb_search(guild_db, guild_id);

	if(g) {
		numdb_foreach(guild_db, guilddb_txt_delete_sub, g->guild_id);
		numdb_erase(guild_db, g->guild_id);
		gstoragedb_delete(g->guild_id);
		mapif_guild_broken(g->guild_id, 0);
		aFree(g);

#ifdef TXT_JOURNAL
		if( guild_journal_enable )
			journal_write( &guild_journal, guild_id, NULL );
#endif
	}
	return true;
}

/*==========================================
 * ギルド作成
 *------------------------------------------
 */
bool guilddb_txt_new(struct guild *g2)
{
	struct guild *g1;

	nullpo_retr(false, g2);

	g1 = (struct guild *)aMalloc(sizeof(struct guild));
	g2->guild_id = guild_newid++;

	memcpy(g1, g2, sizeof(struct guild));
	numdb_insert(guild_db, g2->guild_id, g1);
#ifdef TXT_JOURNAL
	if( guild_journal_enable )
		journal_write( &guild_journal, g1->guild_id, g1 );
#endif

	return true;
}

/*==========================================
 * セーブ
 *------------------------------------------
 */
bool guilddb_txt_save(struct guild* g2)
{
	struct guild *g1;

	nullpo_retr(false, g2);

	g1 = (struct guild *)numdb_search(guild_db, g2->guild_id);
	if(g1 == NULL) {
		g1 = (struct guild *)aMalloc(sizeof(struct guild));
		numdb_insert(guild_db, g2->guild_id,g1);
	}
	memcpy(g1, g2, sizeof(struct guild));
#ifdef TXT_JOURNAL
	if( guild_journal_enable )
		journal_write( &guild_journal, g1->guild_id, g1 );
#endif
	return true;
}

/*==========================================
 * ギルド城データを文字列へ変換
 *------------------------------------------
 */
static int guildcastle_tostr(char *str, struct guild_castle *gc)
{
	nullpo_retr(1, gc);

	sprintf(str, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
		gc->castle_id,gc->guild_id,gc->economy,gc->defense,gc->triggerE,
		gc->triggerD,gc->nextTime,gc->payTime,gc->createTime,gc->visibleC,
		gc->guardian[0].visible,gc->guardian[1].visible,gc->guardian[2].visible,gc->guardian[3].visible,gc->guardian[4].visible,
		gc->guardian[5].visible,gc->guardian[6].visible,gc->guardian[7].visible);

	return 0;
}

/*==========================================
 * ギルド城データを文字列から変換
 *------------------------------------------
 */
static int guildcastle_fromstr(char *str, struct guild_castle *gc)
{
	int tmp_int[18];

	nullpo_retr(1, gc);

	memset(gc, 0, sizeof(struct guild_castle));
	if( sscanf(str, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
		&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],&tmp_int[4],&tmp_int[5],&tmp_int[6],
		&tmp_int[7],&tmp_int[8],&tmp_int[9],&tmp_int[10],&tmp_int[11],&tmp_int[12],&tmp_int[13],
		&tmp_int[14],&tmp_int[15],&tmp_int[16],&tmp_int[17]) <18 )
		return 1;

	gc->castle_id           = tmp_int[0];
	gc->guild_id            = tmp_int[1];
	gc->economy             = tmp_int[2];
	gc->defense             = tmp_int[3];
	gc->triggerE            = tmp_int[4];
	gc->triggerD            = tmp_int[5];
	gc->nextTime            = tmp_int[6];
	gc->payTime             = tmp_int[7];
	gc->createTime          = tmp_int[8];
	gc->visibleC            = tmp_int[9];
	gc->guardian[0].visible = tmp_int[10];
	gc->guardian[1].visible = tmp_int[11];
	gc->guardian[2].visible = tmp_int[12];
	gc->guardian[3].visible = tmp_int[13];
	gc->guardian[4].visible = tmp_int[14];
	gc->guardian[5].visible = tmp_int[15];
	gc->guardian[6].visible = tmp_int[16];
	gc->guardian[7].visible = tmp_int[17];

	return 0;
}

#ifdef TXT_JOURNAL
// ==========================================
// ギルド城データのジャーナルのロールフォワード用コールバック関数
// ------------------------------------------
int guildcastle_journal_rollforward( int key, void* buf, int flag )
{
	// 念のためチェック
	if( flag == JOURNAL_FLAG_WRITE && key != ((struct guild_castle*)buf)->castle_id )
	{
		printf("int_guild: castle_journal: key != castle_id !\n");
		return 0;
	}

	// データの置き換え
	if( key >= 0 && key < MAX_GUILDCASTLE )
	{
		if( flag == JOURNAL_FLAG_DELETE ) {
			memset( &castle_db[key], 0, sizeof(castle_db[0]) );
			castle_db[key].castle_id = key;
		} else {
			memcpy( &castle_db[key], buf, sizeof(castle_db[0]) );
		}
		return 1;
	}

	// 追加
	if( flag != JOURNAL_FLAG_DELETE )
	{
		memcpy( &castle_db[key], buf, sizeof(castle_db[0]) );
		return 1;
	}

	return 0;
}
#endif

/*==========================================
 * ギルド城データファイルの読み込み
 *------------------------------------------
 */
static bool guildcastle_txt_read(void)
{
	FILE *fp;
	int i;
	bool ret = true;

	// デフォルトデータを作成
	memset(castle_db, 0, sizeof(castle_db));
	for(i = 0; i < MAX_GUILDCASTLE; i++) {
		castle_db[i].castle_id = i;
		castle_db[i].economy   = 1;
		castle_db[i].defense   = 1;
	}

	if((fp = fopen(castle_txt, "r")) == NULL) {
		printf("guildcastle_txt_read: open [%s] failed !\n", castle_txt);
		ret = false;
	} else {
		struct guild_castle gc;
		int count = 0;
		char line[1024];

		while(fgets(line, sizeof(line), fp)) {
			if(guildcastle_fromstr(line, &gc) == 0 && gc.castle_id >= 0 && gc.castle_id < MAX_GUILDCASTLE) {
				memcpy(&castle_db[gc.castle_id], &gc, sizeof(gc));
			} else {
				printf("int_guild: broken data [%s] line %d\n", castle_txt, count);
			}
			count++;
		}
		fclose(fp);
	}

#ifdef TXT_JOURNAL
	if( guildcastle_journal_enable )
	{
		// ジャーナルデータのロールフォワード
		if( journal_load( &guildcastle_journal, sizeof(struct guild_castle), guildcastle_journal_file ) )
		{
			int c = journal_rollforward( &guildcastle_journal, guildcastle_journal_rollforward );

			printf("int_guild: castle_journal: roll-forward (%d)\n", c );

			// ロールフォワードしたので、txt データを保存する ( journal も新規作成される)
			guildcastle_txt_sync();
		}
		else
		{
			// ジャーナルを新規作成する
			journal_final( &guildcastle_journal );
			journal_create( &guildcastle_journal, sizeof(struct guild_castle), guildcastle_journal_cache, guildcastle_journal_file );
		}
	}
#endif
	return ret;
}

/*==========================================
 * ギルド城データの同期
 *------------------------------------------
 */
static int guildcastle_txt_sync(void)
{
	FILE *fp;
	int i, lock;
	char line[1024];

	if( (fp = lock_fopen(castle_txt, &lock)) == NULL ) {
		printf("guildcastle_txt_sync: can't write [%s] !!! data is lost !!!\n", castle_txt);
		return 1;
	}

	for(i = 0; i < MAX_GUILDCASTLE; i++) {
		guildcastle_tostr(line, &castle_db[i]);
		fprintf(fp, "%s" NEWLINE, line);
	}
	lock_fclose(fp, castle_txt, &lock);

#ifdef TXT_JOURNAL
	if( guildcastle_journal_enable )
	{
		// コミットしたのでジャーナルを新規作成する
		journal_final( &guildcastle_journal );
		journal_create( &guildcastle_journal, sizeof(struct guild_castle), guildcastle_journal_cache, guildcastle_journal_file );
	}
#endif

	return 0;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
static int guild_txt_db_final(void *key, void *data, va_list ap)
{
	struct guild *g = (struct guild *)data;

	aFree(g);

	return 0;
}

void guilddb_txt_final(void)
{
	if(guild_db)
		numdb_final(guild_db, guild_txt_db_final);

#ifdef TXT_JOURNAL
	if( guild_journal_enable )
	{
		journal_final( &guild_journal );
	}
	if( guildcastle_journal_enable )
	{
		journal_final( &guildcastle_journal );
	}
#endif
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
bool guilddb_txt_init(void)
{
	bool ret = guilddb_txt_read();

	return (guildcastle_txt_read() && ret)? true: false;
}
