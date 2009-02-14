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

#define _INT_PARTY_C_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mmo.h"
#include "socket.h"
#include "db.h"
#include "lock.h"
#include "malloc.h"
#include "journal.h"
#include "sqldbs.h"

#include "char.h"
#include "inter.h"
#include "int_party.h"

static int party_share_level = 10;
static struct dbt *party_db = NULL;

static int party_check_empty(const struct party *p);

#ifdef TXT_ONLY

static char party_txt[1024]="save/party.txt";
static int party_newid=100;

#ifdef TXT_JOURNAL
static int party_journal_enable = 1;
static struct journal party_journal;
static char party_journal_file[1024]="./save/party.journal";
static int party_journal_cache = 1000;
#endif

// パーティデータの文字列への変換
static int party_tostr(char *str,struct party *p)
{
	int i,len;

	len=sprintf(str,"%d\t%s\t%d,%d\t",
		p->party_id,p->name,p->exp,p->item);
	for(i=0;i<MAX_PARTY;i++){
		struct party_member *m = &p->member[i];
		len+=sprintf(str+len,"%d,%d,%d\t%s\t",
			m->account_id,m->char_id,m->leader,
			((m->account_id>0)? m->name: "NoMember"));
	}
	return 0;
}

// パーティデータの文字列からの変換
static int party_fromstr(char *str,struct party *p)
{
	int i,j,s;
	int tmp_int[3];
	char tmp_str[256];

	memset(p,0,sizeof(struct party));

	s=sscanf(str,"%d\t%255[^\t]\t%d,%d\t",
		&tmp_int[0],tmp_str,&tmp_int[1],&tmp_int[2]);
	if(s!=4)
		return 1;

	p->party_id = tmp_int[0];
	strncpy(p->name,tmp_str,24);
	p->name[23] = '\0';	// force \0 terminal
	p->exp  = tmp_int[1];
	p->item = tmp_int[2];

	for(j=0;j<3 && str!=NULL;j++)
		str=strchr(str+1,'\t');

	for(i=0;i<MAX_PARTY;i++){
		struct party_member *m = &p->member[i];
		if(str==NULL)
			return 1;
		// Auriga-0482以降の形式
		s=sscanf(str+1,"%d,%d,%d\t%255[^\t]\t",
			&tmp_int[0],&tmp_int[1],&tmp_int[2],tmp_str);
		if(s!=4) {
			const struct mmo_chardata *cd;
			s=sscanf(str+1,"%d,%d\t%255[^\t]\t",
				&tmp_int[0],&tmp_int[2],tmp_str);
			if(s!=3)
				return 1;
			cd = char_nick2chardata(tmp_str);
			tmp_int[1] = (cd)? cd->st.char_id: 0;
		}

		m->account_id = tmp_int[0];
		m->char_id    = tmp_int[1];
		m->leader     = tmp_int[2];
		strncpy(m->name,tmp_str,24);
		m->name[23] = '\0';	// force \0 terminal

		for(j=0;j<2 && str!=NULL;j++)
			str=strchr(str+1,'\t');
	}
	return 0;
}

#ifdef TXT_JOURNAL
// ==========================================
// パーティーのジャーナルのロールフォワード用コールバック関数
// ------------------------------------------
int party_journal_rollforward( int key, void* buf, int flag )
{
	struct party* p = (struct party *)numdb_search( party_db, key );

	// 念のためチェック
	if( flag == JOURNAL_FLAG_WRITE && key != ((struct party*)buf)->party_id )
	{
		printf("int_party: journal: key != party_id !\n");
		return 0;
	}

	// データの置き換え
	if( p )
	{
		if( flag == JOURNAL_FLAG_DELETE ) {
			numdb_erase( party_db, key );
			aFree( p );
		} else {
			memcpy( p, buf, sizeof(struct party) );
		}
		return 1;
	}

	// 追加
	if( flag != JOURNAL_FLAG_DELETE )
	{
		p = (struct party*) aCalloc( 1, sizeof( struct party ) );
		memcpy( p, buf, sizeof(struct party) );
		numdb_insert( party_db, key, p );
		if( p->party_id >= party_newid)
			party_newid=p->party_id+1;
		return 1;
	}

	return 0;
}
int party_txt_sync(void);
#endif

// パーティデータのロード
int party_txt_init(void)
{
	char line[8192];
	struct party *p;
	FILE *fp;
	int c=0;

	party_db=numdb_init();

	if( (fp=fopen(party_txt,"r"))==NULL )
		return 1;
	while(fgets(line,sizeof(line),fp)){
		p=(struct party *)aCalloc(1,sizeof(struct party));
		if(party_fromstr(line,p)==0 && p->party_id>0){
			if( p->party_id >= party_newid)
				party_newid=p->party_id+1;
			if(party_check_empty(p)) {
				// 空パーティ
				aFree(p);
			} else {
				numdb_insert(party_db,p->party_id,p);
			}
		} else{
			printf("int_party: broken data [%s] line %d\n",party_txt,c+1);
			aFree(p);
		}
		c++;
	}
	fclose(fp);

#ifdef TXT_JOURNAL
	if( party_journal_enable )
	{
		// ジャーナルデータのロールフォワード
		if( journal_load( &party_journal, sizeof(struct party), party_journal_file ) )
		{
			int c = journal_rollforward( &party_journal, party_journal_rollforward );

			printf("int_party: journal: roll-forward (%d)\n", c );

			// ロールフォワードしたので、txt データを保存する ( journal も新規作成される)
			party_txt_sync();
		}
		else
		{
			// ジャーナルを新規作成する
			journal_final( &party_journal );
			journal_create( &party_journal, sizeof(struct party), party_journal_cache, party_journal_file );
		}
	}
#endif

	return 0;
}

// パーティーデータのセーブ用
static int party_txt_sync_sub(void *key,void *data,va_list ap)
{
	char line[8192];
	FILE *fp;

	party_tostr(line,(struct party *)data);
	fp=va_arg(ap,FILE *);
	fprintf(fp,"%s" RETCODE,line);
	return 0;
}

// パーティーデータのセーブ
int party_txt_sync(void)
{
	FILE *fp;
	int  lock;

	if( !party_db )
		return 1;

	if( (fp=lock_fopen(party_txt,&lock))==NULL ){
		printf("int_party: cant write [%s] !!! data is lost !!!\n",party_txt);
		return 1;
	}
	numdb_foreach(party_db,party_txt_sync_sub,fp);
	lock_fclose(fp,party_txt,&lock);

#ifdef TXT_JOURNAL
	if( party_journal_enable )
	{
		// コミットしたのでジャーナルを新規作成する
		journal_final( &party_journal );
		journal_create( &party_journal, sizeof(struct party), party_journal_cache, party_journal_file );
	}
#endif

	return 0;
}

// パーティ名検索用
static int party_txt_load_name_sub(void *key,void *data,va_list ap)
{
	struct party *p, **dst;
	char *str;

	p   = (struct party *)data;
	str = va_arg(ap,char *);
	dst = va_arg(ap,struct party **);

	if(*dst == NULL) {
		if(strcmp(p->name,str) == 0)
			*dst = p;
	}
	return 0;
}

// パーティ名検索
const struct party* party_txt_load_str(char *str)
{
	struct party *p=NULL;

	numdb_foreach(party_db,party_txt_load_name_sub,str,&p);

	return p;
}

const struct party* party_txt_load_num(int party_id)
{
	return (const struct party *)numdb_search(party_db,party_id);
}

int party_txt_save(struct party* p2)
{
	struct party *p1 = (struct party *)numdb_search(party_db,p2->party_id);

	if(p1 == NULL) {
		p1 = (struct party *)aMalloc(sizeof(struct party));
		numdb_insert(party_db,p2->party_id,p1);
	}
	memcpy(p1,p2,sizeof(struct party));
#ifdef TXT_JOURNAL
	if( party_journal_enable )
		journal_write( &party_journal, p1->party_id, p1 );
#endif
	return 1;
}

int party_txt_delete(int party_id)
{
	struct party *p = (struct party *)numdb_search(party_db,party_id);

	if(p) {
		numdb_erase(party_db,p->party_id);
		aFree(p);
#ifdef TXT_JOURNAL
		if( party_journal_enable )
			journal_write( &party_journal, party_id, NULL );
#endif
		return 1;
	}
	return 0;
}

int party_txt_config_read_sub(const char *w1,const char *w2)
{
	if(strcmpi(w1,"party_txt")==0){
		strncpy(party_txt, w2, sizeof(party_txt) - 1);
	}
#ifdef TXT_JOURNAL
	else if(strcmpi(w1,"party_journal_enable")==0){
		party_journal_enable = atoi( w2 );
	}
	else if(strcmpi(w1,"party_journal_file")==0){
		strncpy( party_journal_file, w2, sizeof(party_journal_file) - 1 );
	}
	else if(strcmpi(w1,"party_journal_cache_interval")==0){
		party_journal_cache = atoi( w2 );
	}
#endif
	return 0;
}

int party_txt_new(struct party *p)
{
	p->party_id = party_newid++;
	numdb_insert(party_db,p->party_id,p);
#ifdef TXT_JOURNAL
	if( party_journal_enable )
		journal_write( &party_journal, p->party_id, p );
#endif
	return 1;
}

static int party_txt_final_sub(void *key,void *data,va_list ap)
{
	struct party *p = (struct party *)data;

	aFree(p);

	return 0;
}

void party_txt_final(void)
{
	if(party_db)
		numdb_final(party_db,party_txt_final_sub);

#ifdef TXT_JOURNAL
	if( party_journal_enable )
	{
		journal_final( &party_journal );
	}
#endif
}

#define party_new      party_txt_new
#define party_init     party_txt_init
#define party_sync     party_txt_sync
#define party_save     party_txt_save
#define party_delete   party_txt_delete
#define party_load_str party_txt_load_str
#define party_load_num party_txt_load_num
#define party_config_read_sub party_txt_config_read_sub

#else /* TXT_ONLY */

int party_sql_init(void)
{
	party_db = numdb_init();
	return 0;
}

int party_sql_sync(void)
{
	// nothing to do
	return 0;
}

const struct party* party_sql_load_str(char *str)
{
	int  id_num = -1;
	char buf[256];
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;

	sqldbs_query(&mysql_handle, "SELECT `party_id` FROM `" PARTY_TABLE "` WHERE `name` = '%s'", strecpy(buf,str));

	sql_res = sqldbs_store_result(&mysql_handle);
	if (sql_res) {
		sql_row = sqldbs_fetch(sql_res);
		if(sql_row) {
			id_num = atoi(sql_row[0]);
		}
		sqldbs_free_result(sql_res);
	}
	if(id_num >= 0) {
		return party_sql_load_num(id_num);
	}
	return NULL;
}

const struct party* party_sql_load_num(int party_id)
{
	int leader_id=0, rc;
	struct party *p = (struct party *)numdb_search(party_db,party_id);
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;

	if(p && p->party_id == party_id) {
		return p;
	}
	if(p == NULL) {
		p = (struct party *)aMalloc(sizeof(struct party));
		numdb_insert(party_db,party_id,p);
	}
	memset(p, 0, sizeof(struct party));

	rc = sqldbs_query(&mysql_handle, "SELECT `name`,`exp`,`item`,`leader_id` FROM `" PARTY_TABLE "` WHERE `party_id`='%d'", party_id);
	if(rc) {
		p->party_id = -1;
		return NULL;
	}

	sql_res = sqldbs_store_result(&mysql_handle);
	if (sql_res!=NULL && sqldbs_num_rows(sql_res)>0) {
		sql_row     = sqldbs_fetch(sql_res);
		p->party_id = party_id;
		strncpy(p->name, sql_row[0], 24);
		p->name[23] = '\0';	// force \0 terminal
		p->exp      = atoi(sql_row[1]);
		p->item     = atoi(sql_row[2]);
		leader_id   = atoi(sql_row[3]);
	} else {
		sqldbs_free_result(sql_res);
		p->party_id = -1;
		return NULL;
	}
	sqldbs_free_result(sql_res);

	// Load members
	rc = sqldbs_query(&mysql_handle, "SELECT `account_id`,`char_id`,`name` FROM `" CHAR_TABLE "` WHERE `party_id`='%d'", party_id);
	if(rc) {
		p->party_id = -1;
		return NULL;
	}
	sql_res = sqldbs_store_result(&mysql_handle);
	if (sql_res) {
		int i;
		for(i=0;(sql_row = sqldbs_fetch(sql_res));i++){
			struct party_member *m = &p->member[i];
			m->account_id = atoi(sql_row[0]);
			m->char_id    = atoi(sql_row[1]);
			m->leader     = (m->account_id == leader_id) ? 1 : 0;
			strncpy(m->name,sql_row[2],24);
			m->name[23] = '\0';	// force \0 terminal
		}
	}
	sqldbs_free_result(sql_res);

	return p;
}

int party_sql_save(struct party* p2)
{
	const struct party *p1 = party_sql_load_num(p2->party_id);
	char t_name[64];

	if(p1 == NULL) return 0;

	if(strcmp(p1->name,p2->name) || p1->exp != p2->exp || p1->item != p2->item) {
		sqldbs_query(
			&mysql_handle,
			"UPDATE `" PARTY_TABLE "` SET `name`='%s', `exp`='%d', `item`='%d' WHERE `party_id`='%d'",
			strecpy(t_name,p2->name),p2->exp,p2->item,p2->party_id
		);
	}

	{
		struct party *p3 = (struct party *)numdb_search(party_db,p2->party_id);
		if(p3)
			memcpy(p3,p2,sizeof(struct party));
	}
	return 0;
}

int party_sql_delete(int party_id)
{
	struct party *p = (struct party *)numdb_search(party_db,party_id);

	if(p) {
		numdb_erase(party_db,p->party_id);
		aFree(p);
	}

	sqldbs_query(&mysql_handle, "DELETE FROM `" PARTY_TABLE "` WHERE `party_id`='%d'", party_id);

	return 0;
}

int party_sql_config_read_sub(const char *w1,const char *w2)
{
	// nothing to do
	return 0;
}

int party_sql_new(struct party *p)
{
	int i = 0, rc;
	int leader_id = -1;
	char t_name[64];
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;

	for(i = 0; i < MAX_PARTY; i++) {
		if(p->member[i].account_id > 0 && p->member[i].leader) {
			leader_id = p->member[i].account_id;
			break;
		}
	}
	if ( leader_id == -1 ) { return 0; }
	// パーティIDを読み出す
	rc = sqldbs_query(&mysql_handle, "SELECT MAX(`party_id`) FROM `" PARTY_TABLE "`");
	if(rc)
		return 0;

	sql_res = sqldbs_store_result(&mysql_handle);
	if(!sql_res)
		return 0;

	sql_row = sqldbs_fetch(sql_res);
	if(sql_row[0]) {
		p->party_id = atoi(sql_row[0]) + 1;
	} else {
		p->party_id = 100;
	}
	sqldbs_free_result(sql_res);

	// DBに挿入
	sqldbs_query(
		&mysql_handle,
		"INSERT INTO `" PARTY_TABLE "` (`party_id`, `name`, `exp`, `item`, `leader_id`) "
		"VALUES ('%d','%s', '%d', '%d', '%d')",
		p->party_id, strecpy(t_name,p->name), p->exp, p->item,leader_id
	);

	numdb_insert(party_db,p->party_id,p);
	return 1;
}

static int party_sql_final_sub(void *key,void *data,va_list ap)
{
	struct party *p = (struct party *)data;

	aFree(p);

	return 0;
}

void party_sql_final(void)
{
	numdb_final(party_db,party_sql_final_sub);
}

#define party_new      party_sql_new
#define party_init     party_sql_init
#define party_sync     party_sql_sync
#define party_save     party_sql_save
#define party_delete   party_sql_delete
#define party_load_str party_sql_load_str
#define party_load_num party_sql_load_num
#define party_config_read_sub party_sql_config_read_sub

#endif

// EXP公平分配できるかチェック
static int party_check_exp_share(struct party *p,int baby_id)
{
	int i;
	int maxlv=0, minlv=0x7fffffff;

	for(i=0; i<MAX_PARTY; i++) {
		int lv = p->member[i].lv;
		if( p->member[i].online ) {
			if( lv < minlv ) minlv = lv;
			if( maxlv < lv ) maxlv = lv;
		}
	}
	if(maxlv == 0 || maxlv - minlv <= party_share_level)
		return 1;

	if(baby_id > 0) {
		// 家族公平の可能性があるのでチェックする
		const struct mmo_chardata *b, *p1, *p2;

		if((b = char_load(baby_id)) == NULL)
			return 0;

		p1 = char_load(b->st.parent_id[0]);
		p2 = char_load(b->st.parent_id[1]);

		if(p1 && p2) {
			if( p1->st.party_id == b->st.party_id && p1->st.baby_id == baby_id && p1->st.base_level >= 70 &&
			    p2->st.party_id == b->st.party_id && p2->st.baby_id == baby_id && p2->st.base_level >= 70 &&
			    p1->st.partner_id == p2->st.char_id && p2->st.partner_id == p1->st.char_id ) {
				return 1;
			}
		}
	}
	return 0;
}

// パーティが空かどうかチェック
static int party_check_empty(const struct party *p)
{
	int i;

	for(i=0;i<MAX_PARTY;i++){
		if(p->member[i].account_id>0){
			return 0;
		}
	}
	return 1;
}

//-------------------------------------------------------------------
// map serverへの通信

// パーティ作成可否
int mapif_party_created(int fd,int account_id,struct party *p)
{
	WFIFOW(fd,0)=0x3820;
	WFIFOL(fd,2)=account_id;
	if(p!=NULL){
		WFIFOB(fd,6)=0;
		WFIFOL(fd,7)=p->party_id;
		memcpy(WFIFOP(fd,11),p->name,24);
		printf("int_party: created! %d %s\n",p->party_id,p->name);
	} else {
		WFIFOB(fd,6)=1;
		WFIFOL(fd,7)=0;
	}
	WFIFOSET(fd,35);
	return 0;
}

// パーティ情報見つからず
int mapif_party_noinfo(int fd,int party_id)
{
	WFIFOW(fd,0)=0x3821;
	WFIFOW(fd,2)=8;
	WFIFOL(fd,4)=party_id;
	WFIFOSET(fd,8);
	printf("int_party: info not found %d\n",party_id);
	return 0;
}

// パーティ情報まとめ送り
int mapif_party_info(int fd,const struct party *p)
{
	size_t size = sizeof(struct party);
	unsigned char *buf = (unsigned char *)aMalloc(size+4);

	WBUFW(buf,0)=0x3821;
	WBUFW(buf,2)=(unsigned short)(size+4);
	memcpy(WBUFP(buf,4),p,size);
	if(fd<0)
		mapif_sendall(buf,WBUFW(buf,2));
	else
		mapif_send(fd,buf,WBUFW(buf,2));

	aFree(buf);
	return 0;
}

// パーティメンバ追加可否
void mapif_party_memberadded(int fd, int party_id, int account_id, int char_id, const char *name, unsigned char flag)
{
	WFIFOW(fd,0)=0x3822;
	WFIFOL(fd,2)=party_id;
	WFIFOL(fd,6)=account_id;
	WFIFOL(fd,10)=char_id;
	WFIFOB(fd,14)=flag;
	strncpy(WFIFOP(fd,15), name, 24);
	WFIFOSET(fd,39);

	return;
}

// パーティ設定変更通知
int mapif_party_optionchanged(int fd,struct party *p,int account_id,int flag)
{
	unsigned char buf[16];

	WBUFW(buf,0)=0x3823;
	WBUFL(buf,2)=p->party_id;
	WBUFL(buf,6)=account_id;
	WBUFB(buf,10)=p->exp;
	WBUFB(buf,11)=p->item;
	WBUFB(buf,12)=flag;
	if(flag==0)
		mapif_sendall(buf,13);
	else
		mapif_send(fd,buf,13);
	printf("int_party: option changed %d %d %d %d %d\n",p->party_id,account_id,p->exp,p->item,flag);
	return 0;
}

// パーティ脱退通知
int mapif_party_leaved(int party_id,int account_id,int char_id,const char *name)
{
	unsigned char buf[64];

	WBUFW(buf,0)=0x3824;
	WBUFL(buf,2)=party_id;
	WBUFL(buf,6)=account_id;
	WBUFL(buf,10)=char_id;
	strncpy(WBUFP(buf,14),name,24);
	mapif_sendall(buf,38);
	printf("int_party: party leaved %d %d %s\n",party_id,account_id,name);
	return 0;
}

// パーティマップ更新通知
static void mapif_party_membermoved(int party_id, struct party_member *m)
{
	unsigned char buf[36];

	WBUFW(buf,0)=0x3825;
	WBUFL(buf,2)=party_id;
	WBUFL(buf,6)=m->account_id;
	WBUFL(buf,10)=m->char_id;
	memcpy(WBUFP(buf,14),m->map,16);
	WBUFB(buf,30)=m->online;
	WBUFW(buf,31)=m->lv;
	mapif_sendall(buf,33);

	return;
}

// パーティ解散通知
int mapif_party_broken(int party_id,int flag)
{
	unsigned char buf[16];

	WBUFW(buf,0)=0x3826;
	WBUFL(buf,2)=party_id;
	WBUFB(buf,6)=flag;
	mapif_sendall(buf,7);
	printf("int_party: broken %d\n",party_id);
	return 0;
}

// パーティ内発言
int mapif_party_message(int party_id,int account_id,char *mes,int len)
{
	unsigned char buf[512];

	WBUFW(buf,0)=0x3827;
	WBUFW(buf,2)=len+12;
	WBUFL(buf,4)=party_id;
	WBUFL(buf,8)=account_id;
	memcpy(WBUFP(buf,12),mes,len);
	mapif_sendall(buf,len+12);
	return 0;
}

//-------------------------------------------------------------------
// map serverからの通信


// パーティ
int mapif_parse_CreateParty(int fd, int account_id, int char_id, char *name,
	unsigned char item, unsigned char item2, char *nick, char *map, unsigned short lv)
{
	struct party *p;
	int i;

	for(i=0; i<24 && name[i]; i++) {
		if(!(name[i]&0xe0) || name[i]==0x7f) {
			printf("int_party: illegal party name [%s]\n",name);
			mapif_party_created(fd,account_id,NULL);
			return 0;
		}
	}
	if(party_load_str(name) != NULL) {
		printf("int_party: same name party exists [%s]\n",name);
		mapif_party_created(fd,account_id,NULL);
		return 0;
	}

	p = (struct party *)aCalloc(1,sizeof(struct party));
	memcpy(p->name,name,24);
	p->exp  = 0;
	p->item = (item? 1: 0) | (item2? 2: 0);
	p->member[0].account_id = account_id;
	p->member[0].char_id    = char_id;
	memcpy(p->member[0].name,nick,24);
	memcpy(p->member[0].map,map,16);
	p->member[0].map[15] = '\0';	// force \0 terminal
	p->member[0].leader = 1;
	p->member[0].online = 1;
	p->member[0].lv     = lv;

	if(party_new(p)) {
		// 成功
		mapif_party_created(fd,account_id,p);
		mapif_party_info(fd,p);
	} else {
		// 失敗
		mapif_party_created(fd,account_id,NULL);
	}

	return 0;
}

// パーティ情報要求
int mapif_parse_PartyInfo(int fd,int party_id)
{
	const struct party *p = party_load_num(party_id);

	if(p!=NULL)
		mapif_party_info(fd,p);
	else
		mapif_party_noinfo(fd,party_id);
	return 0;
}

// パーティ追加要求
int mapif_parse_PartyAddMember(int fd,int party_id,int account_id,int char_id,char *nick,char *map,int lv)
{
	const struct party *p1 = party_load_num(party_id);
	struct party p2;
	int i;

	if(p1 == NULL){
		mapif_party_memberadded(fd, party_id, account_id, char_id, nick, 1);
		return 0;
	}
	memcpy(&p2,p1,sizeof(struct party));

	for(i=0;i<MAX_PARTY;i++){
		if(p2.member[i].account_id == account_id && p2.member[i].char_id == char_id)
			break;
		if(p2.member[i].account_id == 0) {
			p2.member[i].account_id = account_id;
			p2.member[i].char_id    = char_id;
			memcpy(p2.member[i].name,nick,24);
			memcpy(p2.member[i].map,map,16);
			p2.member[i].map[15] = '\0';	// force \0 terminal
			p2.member[i].leader  = 0;
			p2.member[i].online  = 1;
			p2.member[i].lv=lv;
			mapif_party_memberadded(fd, party_id, account_id, char_id, nick, 0);
			mapif_party_info(-1,&p2);

			if( p2.exp>0 && !party_check_exp_share(&p2,0) ){
				p2.exp=0;
				mapif_party_optionchanged(fd,&p2,0,0);
			}
			party_save(&p2);
			return 0;
		}
	}
	mapif_party_memberadded(fd, party_id, account_id, char_id, nick, 1);
	party_save(&p2);
	return 0;
}

// パーティー設定変更要求
int mapif_parse_PartyChangeOption(int fd,int party_id,int account_id,int baby_id,unsigned char exp,unsigned char item)
{
	const struct party *p1 = party_load_num(party_id);
	struct party p2;
	int flag=0;

	if(p1 == NULL){
		return 0;
	}
	memcpy(&p2,p1,sizeof(struct party));

	p2.exp = exp;
	if( exp>0 && !party_check_exp_share(&p2,baby_id) ){
		flag|=0x01;
		p2.exp=0;
	}
	p2.item = item;

	mapif_party_optionchanged(fd,&p2,account_id,flag);
	party_save(&p2);
	return 0;
}

// パーティ脱退要求
void mapif_parse_PartyLeave(int fd, int party_id, int account_id, int char_id)
{
	const struct party *p1 = party_load_num(party_id);
	struct party p2;
	int i;

	if(p1 == NULL)
		return;

	memcpy(&p2,p1,sizeof(struct party));
	for(i=0;i<MAX_PARTY;i++){
		if(p2.member[i].account_id == account_id && p2.member[i].char_id == char_id)
		{
			mapif_party_leaved(party_id,account_id,p2.member[i].char_id,p2.member[i].name);
			memset(&p2.member[i],0,sizeof(struct party_member));

			if(fd >= 0) {
				// キャラ削除でない場合はパーティIDを0に初期化
				const struct mmo_chardata *cd = char_load(char_id);
				if(cd) {
					struct mmo_charstatus st;
					memcpy(&st, &cd->st, sizeof(st));
					st.party_id = 0;
					char_save(&st);
				}
			}

			if( party_check_empty(&p2) ) {
				// 空になったので解散
				mapif_party_broken(p2.party_id,0);
				party_delete(p2.party_id);
			} else {
				// まだ人がいるのでデータ送信
				mapif_party_info(-1,&p2);

				if( p2.exp>0 && !party_check_exp_share(&p2,0) ){
					p2.exp=0;
					mapif_party_optionchanged(fd,&p2,0,0);
				}
				party_save(&p2);
			}
			return;
		}
	}

	return;
}

// パーティマップ更新要求
static void mapif_parse_PartyChangeMap(int fd, int party_id, int account_id, int char_id, char *map, unsigned char online, unsigned short lv)
{
	const struct party *p1 = party_load_num(party_id);
	struct party p2;
	int i;

	if(p1 == NULL)
		return;

	memcpy(&p2,p1,sizeof(struct party));
	for(i=0;i<MAX_PARTY;i++){
		if(p2.member[i].account_id == account_id && p2.member[i].char_id == char_id) {
			memcpy(p2.member[i].map,map,16);
			p2.member[i].map[15] = '\0';	// force \0 terminal
			p2.member[i].online  = online;
			p2.member[i].lv      = lv;
			mapif_party_membermoved(party_id, &p2.member[i]);

			if( p2.exp>0 && !party_check_exp_share(&p2,0) ){
				p2.exp=0;
				mapif_party_optionchanged(fd,&p2,0,0);
			}
			break;
		}
	}
	party_save(&p2);

	return;
}

// パーティ解散要求
int mapif_parse_BreakParty(int fd,int party_id)
{
	const struct party *p = party_load_num(party_id);

	if(p==NULL){
		return 0;
	}
	party_delete(party_id);
	mapif_party_broken(fd,party_id);
	return 0;
}

// パーティメッセージ送信
int mapif_parse_PartyMessage(int fd,int party_id,int account_id,char *mes,int len)
{
	return mapif_party_message(party_id,account_id,mes,len);
}

// パーティチェック要求
int mapif_parse_PartyCheck(int fd,int party_id,int account_id,int char_id)
{
	// とりあえず無視
	return 0;
}

// map server からの通信
// ・１パケットのみ解析すること
// ・パケット長データはinter.cにセットしておくこと
// ・パケット長チェックや、RFIFOSKIPは呼び出し元で行われるので行ってはならない
// ・エラーなら0(false)、そうでないなら1(true)をかえさなければならない
int inter_party_parse_frommap(int fd)
{
	switch(RFIFOW(fd,0)){
	case 0x3020: mapif_parse_CreateParty(fd,RFIFOL(fd,2),RFIFOL(fd,6),RFIFOP(fd,10),RFIFOB(fd,34),RFIFOB(fd,35),RFIFOP(fd,36),RFIFOP(fd,60),RFIFOW(fd,76)); break;
	case 0x3021: mapif_parse_PartyInfo(fd,RFIFOL(fd,2)); break;
	case 0x3022: mapif_parse_PartyAddMember(fd,RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10),RFIFOP(fd,14),RFIFOP(fd,38),RFIFOW(fd,54)); break;
	case 0x3023: mapif_parse_PartyChangeOption(fd,RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10),RFIFOB(fd,14),RFIFOB(fd,15)); break;
	case 0x3024: mapif_parse_PartyLeave(fd,RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10)); break;
	case 0x3025: mapif_parse_PartyChangeMap(fd,RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10),RFIFOP(fd,14),RFIFOB(fd,30),RFIFOW(fd,31)); break;
	case 0x3026: mapif_parse_BreakParty(fd,RFIFOL(fd,2)); break;
	case 0x3027: mapif_parse_PartyMessage(fd,RFIFOL(fd,4),RFIFOL(fd,8),RFIFOP(fd,12),RFIFOW(fd,2)-12); break;
	case 0x3028: mapif_parse_PartyCheck(fd,RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10)); break;
	default:
		return 0;
	}
	return 1;
}

// サーバーから脱退要求（キャラ削除用）
void inter_party_leave(int party_id, int account_id, int char_id)
{
	mapif_parse_PartyLeave(-1, party_id, account_id, char_id);

	return;
}

// パーティー設定読み込み
void party_config_read(const char *w1,const char* w2)
{
	if(strcmpi(w1,"party_share_level")==0) {
		party_share_level = atoi(w2);
		if(party_share_level < 0)
			party_share_level = 0;
	}
	else
	{
		party_config_read_sub(w1,w2);
	}
}
