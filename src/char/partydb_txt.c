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

#include "mmo.h"
#include "db.h"
#include "lock.h"
#include "malloc.h"
#include "journal.h"
#include "utils.h"

#include "int_party.h"
#include "chardb_txt.h"
#include "partydb_txt.h"

static struct dbt *party_db = NULL;

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
			cd = chardb_nick2chardata(tmp_str);
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
int partydb_txt_sync(void);
#endif

// パーティデータのロード
bool partydb_txt_init(void)
{
	char line[8192];
	struct party *p;
	FILE *fp;
	int c=0;

	party_db=numdb_init();

	if( (fp=fopen(party_txt,"r"))==NULL )
		return false;
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
			partydb_txt_sync();
		}
		else
		{
			// ジャーナルを新規作成する
			journal_final( &party_journal );
			journal_create( &party_journal, sizeof(struct party), party_journal_cache, party_journal_file );
		}
	}
#endif

	return true;
}

// パーティーデータのセーブ用
static int partydb_txt_sync_sub(void *key,void *data,va_list ap)
{
	char line[8192];
	FILE *fp;

	party_tostr(line,(struct party *)data);
	fp=va_arg(ap,FILE *);
	fprintf(fp,"%s" RETCODE,line);
	return 0;
}

int partydb_txt_sync(void)
{
	FILE *fp;
	int  lock;

	if( !party_db )
		return 1;

	if( (fp=lock_fopen(party_txt,&lock))==NULL ){
		printf("int_party: cant write [%s] !!! data is lost !!!\n",party_txt);
		return 1;
	}
	numdb_foreach(party_db,partydb_txt_sync_sub,fp);
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
const struct party* partydb_txt_load_str(char *str)
{
	struct party *p=NULL;

	numdb_foreach(party_db,party_txt_load_name_sub,str,&p);

	return p;
}

const struct party* partydb_txt_load_num(int party_id)
{
	return (const struct party *)numdb_search(party_db,party_id);
}

bool partydb_txt_save(struct party* p2)
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
	return true;
}

bool partydb_txt_delete(int party_id)
{
	struct party *p = (struct party *)numdb_search(party_db,party_id);

	if(p) {
		numdb_erase(party_db,p->party_id);
		aFree(p);
#ifdef TXT_JOURNAL
		if( party_journal_enable )
			journal_write( &party_journal, party_id, NULL );
#endif
		return true;
	}
	return true;
}

int partydb_txt_config_read_sub(const char *w1,const char *w2)
{
	if( strcmpi(w1,"party_txt") == 0 )
		strncpy(party_txt, w2, sizeof(party_txt) - 1);
#ifdef TXT_JOURNAL
	else if( strcmpi(w1,"party_journal_enable") == 0 )
		party_journal_enable = atoi( w2 );
	else if( strcmpi(w1,"party_journal_file") == 0 )
		strncpy( party_journal_file, w2, sizeof(party_journal_file) - 1 );
	else if( strcmpi(w1,"party_journal_cache_interval") == 0 )
		party_journal_cache = atoi( w2 );
#endif
	else
		return 0;

	return 1;
}

bool partydb_txt_new(struct party *p)
{
	p->party_id = party_newid++;
	numdb_insert(party_db,p->party_id,p);
#ifdef TXT_JOURNAL
	if( party_journal_enable )
		journal_write( &party_journal, p->party_id, p );
#endif
	return true;
}

static int partydb_txt_final_sub(void *key,void *data,va_list ap)
{
	struct party *p = (struct party *)data;

	aFree(p);

	return 0;
}

void partydb_txt_final(void)
{
	if(party_db)
		numdb_final(party_db,partydb_txt_final_sub);

#ifdef TXT_JOURNAL
	if( party_journal_enable )
	{
		journal_final( &party_journal );
	}
#endif
}
