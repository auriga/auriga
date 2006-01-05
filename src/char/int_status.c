
#define _INT_STAUTS_C_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mmo.h"
#include "socket.h"
#include "db.h"
#include "lock.h"
#include "malloc.h"
#include "journal.h"
#include "utils.h"

#include "char.h"
#include "inter.h"
#include "int_status.h"

#ifdef NO_SCDATA_SAVING
// ダミー関数群
int status_dummy_init(void) { return 0; }
int status_dummy_sync(void) { return 0; }
int status_dummy_delete(int char_id) { return 0; }
struct status_change_data *status_dummy_load(int char_id) { return NULL; }
int status_dummy_save(struct status_change_data *sc2) { return 0; }
void status_dummy_final(void) { return; }
void status_dummy_config_read_sub(const char *w1,const char *w2) { return; }
#else /* NO_SCDATA_SAVING */

static struct dbt *scdata_db;

#ifdef TXT_ONLY

static char scdata_txt[1024]="save/scdata.txt";

#ifdef TXT_JOURNAL
static int status_journal_enable = 1;
static struct journal status_journal;
static char status_journal_file[1024]="./save/scdata.journal";
static int status_journal_cache = 1000;
#endif

static int status_tostr(char *str, struct status_change_data *sc)
{
	int i;
	char *str_p = str;

	str_p += sprintf(str,"%d,%d\t",sc->char_id,sc->account_id);

	for(i=0; i<sc->count; i++) {
		str_p += sprintf(str_p,"%d,%d,%d,%d,%d,%d ",
			sc->data[i].type,sc->data[i].val1,sc->data[i].val2,sc->data[i].val3,sc->data[i].val4,sc->data[i].tick);
	}
	*(str_p++) = '\t';

	*str_p='\0';
	return 0;
}

static int status_fromstr(char *str, struct status_change_data *sc)
{
	int i,next,set,len;
	int tmp_int[6];

	if(sscanf(str,"%d,%d%n",&sc->char_id,&sc->account_id,&next) != 2)
		return 1;

	if(sc->account_id <= 0 || sc->char_id <= 0)
		return 1;

	if(str[next] == '\n' || str[next] == '\r')
		return 1;	// account_idとchar_idだけの行は有り得ない
	next++;

	for(i=0; str[next] && str[next] != '\t'; i++) {
		set = sscanf(str+next,"%d,%d,%d,%d,%d,%d%n",
			&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],&tmp_int[4],&tmp_int[5],&len);
		if(set != 6)
			return 1;
		if(i < MAX_STATUSCHANGE && tmp_int[0] >= 0 && tmp_int[0] < MAX_STATUSCHANGE) {
			sc->data[i].type = (short)tmp_int[0];
			sc->data[i].val1 = tmp_int[1];
			sc->data[i].val2 = tmp_int[2];
			sc->data[i].val3 = tmp_int[3];
			sc->data[i].val4 = tmp_int[4];
			sc->data[i].tick = tmp_int[5];
		}
		next+=len;
		if(str[next] == ' ')
			next++;
	}
	sc->count = (i < MAX_STATUSCHANGE)? i: MAX_STATUSCHANGE;

	return 0;
}

#ifdef TXT_JOURNAL
// ==========================================
// ステータス異常データのジャーナルのロールフォワード用コールバック関数
// ------------------------------------------
int status_journal_rollforward( int key, void* buf, int flag )
{
	struct status_change_data *sc = (struct status_change_data *)numdb_search( scdata_db, key );

	// 念のためチェック
	if( flag == JOURNAL_FLAG_WRITE && key != ((struct status_change_data *)buf)->char_id )
	{
		printf("int_status: journal: key != char_id !\n");
		return 0;
	}

	// データの置き換え
	if( sc )
	{
		if( flag == JOURNAL_FLAG_DELETE ) {
			numdb_erase(scdata_db, key);
			aFree(sc);
		} else {
			memcpy( sc, buf, sizeof(struct status_change_data) );
		}
		return 1;
	}

	// 追加
	if( flag != JOURNAL_FLAG_DELETE )
	{
		sc = (struct status_change_data *)aCalloc( 1, sizeof( struct status_change_data ) );
		memcpy( sc, buf, sizeof(struct status_change_data) );
		numdb_insert( scdata_db, key, sc );
		return 1;
	}

	return 0;
}
int status_txt_sync(void);
#endif

int status_txt_init(void)
{
	char line[8192];
	struct status_change_data *sc;
	FILE *fp;
	int c=0;

	scdata_db = numdb_init();

	if( (fp=fopen(scdata_txt,"r")) == NULL )
		return 1;
	while(fgets(line,sizeof(line),fp)) {
		sc = (struct status_change_data *)aCalloc(1,sizeof(struct status_change_data));
		if(status_fromstr(line,sc) == 0) {
			numdb_insert(scdata_db,sc->char_id,sc);
		} else {
			printf("int_status: broken data [%s] line %d\n",scdata_txt,c);
			aFree(sc);
		}
		c++;
	}
	fclose(fp);
//	printf("int_status: %s read done (%d status)\n",scdata_txt,c);

#ifdef TXT_JOURNAL
	if( status_journal_enable )
	{
		// ジャーナルデータのロールフォワード
		if( journal_load( &status_journal, sizeof(struct status_change_data), status_journal_file ) )
		{
			int c = journal_rollforward( &status_journal, status_journal_rollforward );

			printf("int_status: journal: roll-forward (%d)\n", c );

			// ロールフォワードしたので、txt データを保存する ( journal も新規作成される)
			status_txt_sync();
		}
		else
		{
			// ジャーナルを新規作成する
			journal_final( &status_journal );
			journal_create( &status_journal, sizeof(struct status_change_data), status_journal_cache, status_journal_file );
		}
	}
#endif

	return 0;
}

static int status_txt_sync_sub(void *key, void *data, va_list ap)
{
	char line[8192];
	FILE *fp;
	struct status_change_data *sc = (struct status_change_data *)data;

	// countが0のときは書き込みしない
	if(sc->count > 0) {
		status_tostr(line,sc);
		fp = va_arg(ap,FILE *);
		fprintf(fp,"%s" RETCODE,line);
	}
	return 0;
}

int status_txt_sync(void)
{
	FILE *fp;
	int lock;

	if( !scdata_db )
		return 1;

	if( (fp=lock_fopen(scdata_txt,&lock)) == NULL ) {
		printf("int_status: cant write [%s] !!! data is lost !!!\n",scdata_txt);
		return 1;
	}
	numdb_foreach(scdata_db,status_txt_sync_sub,fp);
	lock_fclose(fp,scdata_txt,&lock);
//	printf("int_status: %s saved.\n",scdata_txt);

#ifdef TXT_JOURNAL
	if( status_journal_enable )
	{
		// コミットしたのでジャーナルを新規作成する
		journal_final( &status_journal );
		journal_create( &status_journal, sizeof(struct status_change_data), status_journal_cache, status_journal_file );
	}
#endif

	return 0;
}

int status_txt_delete(int char_id)
{
	struct status_change_data *sc = (struct status_change_data *)numdb_search(scdata_db,char_id);

	if(sc == NULL)
		return 1;

	numdb_erase(scdata_db,char_id);
	aFree(sc);

#ifdef TXT_JOURNAL
	if( status_journal_enable )
		journal_write( &status_journal, char_id, NULL );
#endif

	return 0;
}

/* 負荷軽減を優先してconstを付けない */
struct status_change_data *status_txt_load(int char_id)
{
	return (struct status_change_data *)numdb_search(scdata_db,char_id);
}

int status_txt_save(struct status_change_data *sc2)
{
	struct status_change_data *sc1 = (struct status_change_data *)numdb_search(scdata_db,sc2->char_id);

	if(sc1 == NULL) {
		sc1 = (struct status_change_data *)aCalloc(1,sizeof(struct status_change_data));
		numdb_insert(scdata_db,sc2->char_id,sc1);
		sc1->account_id = sc2->account_id;
		sc1->char_id    = sc2->char_id;
	}

	// データが共に0個ならコピーしない
	if(sc1->count > 0 || sc2->count > 0)
		memcpy(sc1,sc2,sizeof(struct status_change_data));

#ifdef TXT_JOURNAL
	if( status_journal_enable )
		journal_write( &status_journal, sc1->char_id, sc1 );
#endif
	return 1;
}

static int status_txt_final_sub(void *key, void *data, va_list ap)
{
	struct status_change_data *sc = (struct status_change_data *)data;

	aFree(sc);

	return 0;
}

void status_txt_final(void)
{
	if(scdata_db)
		numdb_final(scdata_db,status_txt_final_sub);

#ifdef TXT_JOURNAL
	if( status_journal_enable )
	{
		journal_final( &status_journal );
	}
#endif
}

void status_txt_config_read_sub(const char *w1, const char *w2)
{
	if(strcmpi(w1,"status_txt")==0) {
		strncpy(scdata_txt, w2, sizeof(scdata_txt));
	}
#ifdef TXT_JOURNAL
	else if(strcmpi(w1,"status_journal_enable")==0) {
		status_journal_enable = atoi(w2);
	}
	else if(strcmpi(w1,"status_journal_file")==0) {
		strncpy(status_journal_file, w2, sizeof(status_journal_file));
	}
	else if(strcmpi(w1,"status_journal_cache_interval")==0) {
		status_journal_cache = atoi(w2);
	}
#endif
}

#define status_init   status_txt_init
#define status_sync   status_txt_sync
#define status_delete status_txt_delete
#define status_load   status_txt_load
#define status_save   status_txt_save
#define status_final  status_txt_final

#else /* TXT_ONLY */

static char scdata_db_[256] = "status_change";

int status_sql_init(void)
{
	scdata_db = numdb_init();
	return 0;
}

int status_sql_sync(void)
{
	// nothing to do
	return 0;
}

int status_sql_delete(int char_id)
{
	struct status_change_data *sc = (struct status_change_data *)numdb_search(scdata_db,char_id);

	if(sc && sc->char_id == char_id) {
		numdb_erase(scdata_db,char_id);
		aFree(sc);
	}
	sprintf(tmp_sql,"DELETE FROM `%s` WHERE `char_id`='%d'",scdata_db_, char_id);
	if(mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (delete `%s`)- %s\n", scdata_db_, mysql_error(&mysql_handle));
	}
	return 0;
}

/* 負荷軽減を優先してconstを付けない */
struct status_change_data *status_sql_load(int char_id)
{
	int i=0;
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;
	struct status_change_data *sc = (struct status_change_data *)numdb_search(scdata_db,char_id);

	if(sc && sc->char_id == char_id) {
		// 既にキャッシュが存在する
		return sc;
	}
	if(sc == NULL) {
		sc = (struct status_change_data *)aMalloc(sizeof(struct status_change_data));
		numdb_insert(scdata_db,char_id,sc);
	}
	memset(sc, 0, sizeof(struct status_change_data));

	sc->char_id = char_id;

	//`status_change` (`char_id`, `account_id`, `type`, `val1`, `val2`, `val3`, `val4`, `tick`)
	sprintf(
		tmp_sql,
		"SELECT `char_id`, `account_id`, `type`, `val1`, `val2`, `val3`, `val4`, `tick` "
		"FROM `%s` WHERE `char_id`='%d'",
		scdata_db_, char_id
	);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (select `%s`)- %s\n", scdata_db_, mysql_error(&mysql_handle) );
		sc->char_id = -1;
		return NULL;
	}
	sql_res = mysql_store_result(&mysql_handle);

	if(sql_res && mysql_num_rows(sql_res) > 0) {
		for(i=0; (sql_row = mysql_fetch_row(sql_res)) && i<MAX_STATUSCHANGE; i++) {
			if(sc->account_id == 0) {
				sc->account_id = atoi(sql_row[1]);
			}
			sc->data[i].type = (short)atoi(sql_row[2]);
			sc->data[i].val1 = atoi(sql_row[3]);
			sc->data[i].val2 = atoi(sql_row[4]);
			sc->data[i].val3 = atoi(sql_row[5]);
			sc->data[i].val4 = atoi(sql_row[6]);
			sc->data[i].tick = atoi(sql_row[7]);
		}
		sc->count = (i < MAX_STATUSCHANGE)? i: MAX_STATUSCHANGE;

		mysql_free_result(sql_res);
	} else {
		// 見つからなくても正常
		if(sql_res)
			mysql_free_result(sql_res);
		return NULL;
	}

	return sc;
}

int status_sql_save(struct status_change_data *sc2)
{
	struct status_change_data *sc1 = status_sql_load(sc2->char_id);
	int i;

	if(sc1 != NULL && sc1->count <= 0) {
		if(sc2->count <= 0)	// データが共に0個なので何もしない
			return 0;
	} else {
		// データサーバ側にデータがあるときだけ削除クエリを発行
		sprintf(tmp_sql,"DELETE FROM `%s` WHERE `char_id`='%d'",scdata_db_, sc2->char_id);
		if(mysql_query(&mysql_handle, tmp_sql)) {
			printf("DB server Error (delete `%s`)- %s\n", scdata_db_, mysql_error(&mysql_handle));
		}
	}

	for(i=0; i<sc2->count; i++) {
		sprintf(
			tmp_sql,
			"INSERT INTO `%s` (`char_id`, `account_id`, `type`, `val1`, `val2`, `val3`, `val4`, `tick`) "
			"VALUES ('%d','%d','%d','%d','%d','%d','%d','%d')",
			scdata_db_, sc2->char_id, sc2->account_id, sc2->data[i].type,
			sc2->data[i].val1, sc2->data[i].val2, sc2->data[i].val3, sc2->data[i].val4, sc2->data[i].tick
		);
		if(mysql_query(&mysql_handle, tmp_sql)) {
			printf("DB server Error (insert `%s`)- %s\n", scdata_db_, mysql_error(&mysql_handle));
		}
	}

	if(sc1) {
		memcpy(sc1,sc2,sizeof(struct status_change_data));
	}

	return 0;
}

static int status_sql_final_sub(void *key, void *data, va_list ap)
{
	struct status_change_data *sc = (struct status_change_data *)data;

	aFree(sc);

	return 0;
}

void status_sql_final(void)
{
	if(scdata_db)
		numdb_final(scdata_db,status_sql_final_sub);
}

void status_sql_config_read_sub(const char *w1, const char *w2)
{
	// nothing to do
	return;
}

#define status_init   status_sql_init
#define status_sync   status_sql_sync
#define status_delete status_sql_delete
#define status_load   status_sql_load
#define status_save   status_sql_save
#define status_final  status_sql_final

#endif /* TXT_ONLY */

#endif /* NO_SCDATA_SAVING */

int mapif_load_scdata(int fd,int account_id,int char_id)
{
	struct status_change_data *sc = status_load(char_id);

	if(sc) {
		if(sc->account_id <= 0) {	// アカウントIDがないのは困るので補完
			sc->account_id = account_id;
		}
		else if(sc->account_id != account_id) {
			printf("inter_status: data load error %d %d\n",account_id,char_id);
			return 0;
		}
	}

	WFIFOW(fd,0)=0x3878;
	WFIFOL(fd,4)=account_id;

	if(sc == NULL) {
		WFIFOW(fd,2)=8;
		WFIFOSET(fd,8);
	} else {
		int i,p;
		for(i=0,p=8; i<sc->count; i++,p+=22) {
			WFIFOW(fd,p)    = sc->data[i].type;
			WFIFOL(fd,p+2)  = sc->data[i].val1;
			WFIFOL(fd,p+6)  = sc->data[i].val2;
			WFIFOL(fd,p+10) = sc->data[i].val3;
			WFIFOL(fd,p+14) = sc->data[i].val4;
			WFIFOL(fd,p+18) = sc->data[i].tick;
		}
		WFIFOW(fd,2)=p;
		WFIFOSET(fd,p);
	}
	return 0;
}

static int mapif_save_scdata_ack(int fd,int account_id,int flag)
{
/*
	// 今のところ使い道がないのでコメントアウト
	WFIFOW(fd,0)=0x3879;
	WFIFOL(fd,2)=account_id;
	WFIFOB(fd,6)=flag;
	WFIFOSET(fd,7);
*/
	return 0;
}

//-------------------------------------------------------------------
// map serverからの通信

// ステータス異常データ要求受信
int mapif_parse_LoadStatusChange(int fd)
{
	mapif_load_scdata(fd,RFIFOL(fd,2),RFIFOL(fd,6));
	return 0;
}

// ステータス異常データ保存
int mapif_parse_SaveStatusChange(int fd)
{
	struct status_change_data sc;
	int i,p;
	short len = RFIFOW(fd,2);

	sc.account_id = RFIFOL(fd,4);
	sc.char_id    = RFIFOL(fd,8);

	for(i=0,p=12; p<len && i<MAX_STATUSCHANGE; i++,p+=22) {
		sc.data[i].type = RFIFOW(fd,p);
		sc.data[i].val1 = RFIFOL(fd,p+2);
		sc.data[i].val2 = RFIFOL(fd,p+6);
		sc.data[i].val3 = RFIFOL(fd,p+10);
		sc.data[i].val4 = RFIFOL(fd,p+14);
		sc.data[i].tick = RFIFOL(fd,p+18);
	}
	sc.count = i;

	status_save(&sc);
	mapif_save_scdata_ack(fd,sc.account_id,0);

	return 0;
}

//---------------------------------------------------------
// map server からの通信
// ・１パケットのみ解析すること
// ・パケット長データはinter.cにセットしておくこと
// ・パケット長チェックや、RFIFOSKIPは呼び出し元で行われるので行ってはならない
// ・エラーなら0(false)、そうでないなら1(true)をかえさなければならない
int inter_status_parse_frommap(int fd)
{
#ifndef NO_SCDATA_SAVING
	switch(RFIFOW(fd,0)){
	case 0x3078: mapif_parse_LoadStatusChange(fd); break;
	case 0x3079: mapif_parse_SaveStatusChange(fd); break;
	default:
		return 0;
	}
#endif
	return 1;
}
