
#define _INT_GUILD_C_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "mmo.h"
#include "socket.h"
#include "db.h"
#include "lock.h"
#include "malloc.h"
#include "journal.h"
#include "utils.h"

#include "char.h"
#include "inter.h"
#include "int_guild.h"
#include "int_storage.h"

static int guild_exp[MAX_GUILDLEVEL];

static int guild_join_limit = 0;
static int guild_extension_increment = 4;

static struct dbt *guild_db = NULL;
static struct guild_castle castle_db[MAX_GUILDCASTLE];

int mapif_guild_broken(int guild_id,int flag);
int guild_check_empty(const struct guild *g);
int guild_calcinfo(struct guild *g);
int mapif_guild_info(int fd,const struct guild *g);

// ギルド関連データベース読み込み
static int guild_readdb(void)
{
	int i;
	FILE *fp;
	char line[256];

	fp=fopen("db/exp_guild.txt","r");
	if(fp==NULL){
		printf("can't read db/exp_guild.txt\n");
		return 1;
	}
	i=0;
	while(fgets(line,255,fp) && i<MAX_GUILDLEVEL){
		if(line[0]=='/' && line[1]=='/')
			continue;
		guild_exp[i]=atoi(line);
		i++;
	}
	fclose(fp);

	return 0;
}

#ifdef TXT_ONLY

static int guildcastle_txt_init(void);
static int guildcastle_txt_sync(void);

static int guild_newid=10000;
static char guild_txt[1024]  = "save/guild.txt";
static char castle_txt[1024] = "save/castle.txt";


#ifdef TXT_JOURNAL
static int guild_journal_enable = 1;
static struct journal guild_journal;
static char guild_journal_file[1024]="./save/guild.journal";
static int guild_journal_cache = 1000;

static int guildcastle_journal_enable = 1;
static struct journal guildcastle_journal;
static char guildcastle_journal_file[1024]="./save/castle.journal";
static int guildcastle_journal_cache = 1000;

#endif

void guild_txt_delete(int guild_id);

// ギルドデータの文字列への変換
static int guild_tostr(char *str,struct guild *g)
{
	int i,c,len;

	// 基本データ
	len=sprintf(str,"%d\t%s\t%s\t%d,%d,%d,%d\t%s#\t%s#\t",
		g->guild_id,g->name,g->master,
		g->guild_lv,g->max_member,g->exp,g->skill_point,
		g->mes1,g->mes2);

	// メンバー
	for(i=0;i<g->max_member;i++){
		struct guild_member *m = &g->member[i];
		len+=sprintf(str+len,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\t%s\t",
			m->account_id,m->char_id,
			m->hair,m->hair_color,m->gender,
			m->class_,m->lv,m->exp,m->exp_payper,m->position,
			((m->account_id>0)? m->name: "-"));
	}

	// 役職
	for(i=0;i<MAX_GUILDPOSITION;i++){
		struct guild_position *p = &g->position[i];
		len+=sprintf(str+len,"%d,%d\t%s#\t",
			p->mode,p->exp_mode,p->name);
	}

	// エンブレム
	len+=sprintf(str+len,"%d,%d,",g->emblem_len,g->emblem_id);
	for(i=0;i<g->emblem_len;i++){
		len+=sprintf(str+len,"%02x",(unsigned char)(g->emblem_data[i]));
	}
	len+=sprintf(str+len,"$\t");

	// 同盟リスト
	for(i=0,c=0;i<MAX_GUILDALLIANCE;i++) {
		if(g->alliance[i].guild_id>0)
			c++;
	}
	len+=sprintf(str+len,"%d\t",c);
	for(i=0;i<MAX_GUILDALLIANCE;i++){
		struct guild_alliance *a=&g->alliance[i];
		if(a->guild_id>0)
			len+=sprintf(str+len,"%d,%d\t%s\t",
				a->guild_id,a->opposition,a->name);
	}

	// 追放リスト
	for(i=0,c=0;i<MAX_GUILDEXPLUSION;i++) {
		if(g->explusion[i].account_id>0)
			c++;
	}
	len+=sprintf(str+len,"%d\t",c);
	for(i=0;i<MAX_GUILDEXPLUSION;i++){
		struct guild_explusion *e=&g->explusion[i];
		if(e->account_id>0)
			len+=sprintf(str+len,"%d\t%s\t%s#\t",
				e->account_id,e->name,e->mes );
	}

	// ギルドスキル
	for(i=0;i<MAX_GUILDSKILL;i++){
		len+=sprintf(str+len,"%d,%d ",g->skill[i].id,g->skill[i].lv);
	}
	len+=sprintf(str+len,"\t");
	return 0;
}

// ギルドデータの文字列からの変換
static int guild_fromstr(char *str,struct guild *g)
{
	int i,j,c;
	int tmp_int[10];
	char tmp_str[4][256];
	char tmp_str2[4097];	// binary data + 1
	char *pstr;

	// 基本データ
	memset(g,0,sizeof(struct guild));

	if( sscanf(str,"%d\t%255[^\t]\t%255[^\t]\t%d,%d,%d,%d,%d\t%255[^\t]\t%255[^\t]\t",
		&tmp_int[0],tmp_str[0],tmp_str[1],
		&tmp_int[1],&tmp_int[2],&tmp_int[3],&tmp_int[4],&tmp_int[5],
		tmp_str[2],tmp_str[3]) != 10)
	{
		// Auriga-0177以降の形式
		if( sscanf(str,"%d\t%255[^\t]\t%255[^\t]\t%d,%d,%d,%d\t%255[^\t]\t%255[^\t]\t",
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
	strncpy(g->name,tmp_str[0],24);
	strncpy(g->master,tmp_str[1],24);
	strncpy(g->mes1,tmp_str[2],60);
	strncpy(g->mes2,tmp_str[3],120);

	// force \0 terminal
	g->name[23]   = '\0';
	g->master[23] = '\0';
	g->mes1[59]   = '\0';
	g->mes2[119]  = '\0';

	for(j=0;j<6 && str!=NULL;j++)	// 位置スキップ
		str=strchr(str+1,'\t');
	//printf("GuildBaseInfo OK\n");

	// メンバー
	for(i=0;i<g->max_member && i<MAX_GUILD;i++){
		struct guild_member *m = &g->member[i];
		if( sscanf(str+1,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\t%255[^\t]\t",
			&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],&tmp_int[4],
			&tmp_int[5],&tmp_int[6],&tmp_int[7],&tmp_int[8],&tmp_int[9],
			tmp_str[0]) <11)
			return 1;
		m->account_id=tmp_int[0];
		m->char_id=tmp_int[1];
		m->hair=tmp_int[2];
		m->hair_color=tmp_int[3];
		m->gender=tmp_int[4];
		m->class_=tmp_int[5];
		m->lv=tmp_int[6];
		m->exp=tmp_int[7];
		m->exp_payper=tmp_int[8];
		m->position=tmp_int[9];
		strncpy(m->name,tmp_str[0],24);
		m->name[23] = '\0';	// force \0 terminal

		for(j=0;j<2 && str!=NULL;j++)	// 位置スキップ
			str=strchr(str+1,'\t');
	}
	if(g->max_member != i) {
		printf("int_guild: max guild member changed %d -> %d\n", g->max_member, i);
		g->max_member = i;
	}
	//printf("GuildMemberInfo OK\n");

	// 役職
	for(i=0;i<MAX_GUILDPOSITION;i++){
		struct guild_position *p = &g->position[i];
		if( sscanf(str+1,"%d,%d\t%255[^\t]\t",
			&tmp_int[0],&tmp_int[1],tmp_str[0]) < 3)
			return 1;
		p->mode     = tmp_int[0];
		p->exp_mode = tmp_int[1];
		strncpy(p->name,tmp_str[0],24);
		p->name[23] = '\0';	// force \0 terminal

		for(j=0;j<2 && str!=NULL;j++)	// 位置スキップ
			str=strchr(str+1,'\t');
	}
	//printf("GuildPositionInfo OK\n");

	// エンブレム
	tmp_int[1]=0;
	if( sscanf(str+1,"%d,%d,%4096[^\t]\t",&tmp_int[0],&tmp_int[1],tmp_str2) < 3 )
		return 1;
	g->emblem_len = tmp_int[0];
	g->emblem_id  = tmp_int[1];
	if(g->emblem_len > sizeof(tmp_str2) / 2) {
		// エンブレムのデータ長が大きすぎる
		return 1;
	}
	for(i=0,pstr=tmp_str2;i<g->emblem_len;i++,pstr+=2){
		int c1=pstr[0],c2=pstr[1],x1=0,x2=0;
		if(c1>='0' && c1<='9')x1=c1-'0';
		if(c1>='a' && c1<='f')x1=c1-'a'+10;
		if(c1>='A' && c1<='F')x1=c1-'A'+10;
		if(c2>='0' && c2<='9')x2=c2-'0';
		if(c2>='a' && c2<='f')x2=c2-'a'+10;
		if(c2>='A' && c2<='F')x2=c2-'A'+10;
		g->emblem_data[i]=(x1<<4)|x2;
	}
	//printf("GuildEmblemInfo OK\n");
	str=strchr(str+1,'\t');	// 位置スキップ

	// 同盟リスト
	if( sscanf(str+1,"%d\t",&c)< 1)
		return 1;
	str=strchr(str+1,'\t');	// 位置スキップ
	for(i=0;i<c && i<MAX_GUILDALLIANCE;i++){
		struct guild_alliance *a = &g->alliance[i];
		if( sscanf(str+1,"%d,%d\t%255[^\t]\t",
			&tmp_int[0],&tmp_int[1],tmp_str[0]) < 3)
			return 1;
		a->guild_id   = tmp_int[0];
		a->opposition = tmp_int[1];
		strncpy(a->name,tmp_str[0],24);
		a->name[23] = '\0';	// force \0 terminal

		for(j=0;j<2 && str!=NULL;j++)	// 位置スキップ
			str=strchr(str+1,'\t');
	}
	//printf("GuildAllianceInfo OK\n");

	// 追放リスト
	if( sscanf(str+1,"%d\t",&c)< 1)
		return 1;
	str=strchr(str+1,'\t');	// 位置スキップ
	for(i=0;i<c && i<MAX_GUILDEXPLUSION;i++){
		struct guild_explusion *e = &g->explusion[i];
		int ret,step;

		ret = sscanf(str+1,"%d,%d,%d,%d\t%255[^\t]\t%255[^\t]\t%255[^\t]\t",
			&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],
			tmp_str[0],tmp_str[2],tmp_str[1]);
		if(ret != 7) {
			// Auriga-0142以降の形式
			ret = sscanf(str+1,"%d\t%255[^\t]\t%255[^\t]\t",
				&tmp_int[0],tmp_str[0],tmp_str[1]);
			if(ret != 3)
				return 1;
			step = 3;
		} else {
			step = 4;
		}
		e->account_id = tmp_int[0];
		strncpy(e->name,tmp_str[0],24);
		strncpy(e->mes,tmp_str[1],40);

		// force \0 terminal
		e->name[23] = '\0';
		e->mes[39]  = '\0';

		for(j=0;j<step && str!=NULL;j++)	// 位置スキップ
			str=strchr(str+1,'\t');
	}
	//printf("GuildExplusionInfo OK\n");

	// ギルドスキル
	for(i=0;i<MAX_GUILDSKILL;i++){
		int n;
		if( sscanf(str+1,"%d,%d ",&tmp_int[0],&tmp_int[1]) <2)
			break;
		n = tmp_int[0] - GUILD_SKILLID;
		if(n >= 0 && n < MAX_GUILDSKILL) {
			g->skill[n].id = tmp_int[0];
			g->skill[n].lv = tmp_int[1];
		}
		str=strchr(str+1,' ');
	}

	// 新ギルドスキルへ移行
	for(i=0;i<MAX_GUILDSKILL;i++)
		g->skill[i].id=GUILD_SKILLID+i;

	str=strchr(str+1,'\t');
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
			guild_newid=g->guild_id+1;
		return 1;
	}

	return 0;
}
int guild_txt_sync(void);
#endif

// ギルドデータの読み込み
int guild_txt_init(void)
{
	char line[16384];
	struct guild *g;
	FILE *fp;
	int c=0;

	guild_readdb();

	guild_db=numdb_init();

	if( (fp=fopen(guild_txt,"r"))==NULL )
		return 1;
	while(fgets(line,sizeof(line),fp)){
		g=(struct guild *)aCalloc(1,sizeof(struct guild));
		if(guild_fromstr(line,g)==0 && g->guild_id>0){
			if(g->guild_id >= guild_newid)
				guild_newid=g->guild_id+1;
			numdb_insert(guild_db,g->guild_id,g);
			guild_calcinfo(g);
		}else{
			printf("int_guild: broken data [%s] line %d\n",guild_txt,c);
			aFree(g);
		}
		c++;
	}
	fclose(fp);
	//printf("int_guild: %s read done (%d guilds)\n",guild_txt,c);

#ifdef TXT_JOURNAL
	if( guild_journal_enable )
	{
		// ジャーナルデータのロールフォワード
		if( journal_load( &guild_journal, sizeof(struct guild), guild_journal_file ) )
		{
			int c = journal_rollforward( &guild_journal, guild_journal_rollforward );

			printf("int_guild: guild_journal: roll-forward (%d)\n", c );

			// ロールフォワードしたので、txt データを保存する ( journal も新規作成される)
			guild_txt_sync();
		}
		else
		{
			// ジャーナルを新規作成する
			journal_final( &guild_journal );
			journal_create( &guild_journal, sizeof(struct guild), guild_journal_cache, guild_journal_file );
		}
	}
#endif

	guildcastle_txt_init();
	return 0;
}

const struct guild *guild_txt_load_num(int guild_id)
{
	struct guild *g = (struct guild *)numdb_search(guild_db,guild_id);

	if(g)
		guild_calcinfo(g);

	return g;
}

// ギルドデータのセーブ用
static int guild_txt_sync_sub(void *key,void *data,va_list ap)
{
	char line[16384];
	FILE *fp;

	guild_tostr(line,(struct guild *)data);
	fp=va_arg(ap,FILE *);
	fprintf(fp,"%s" RETCODE,line);
	return 0;
}

// ギルドデータのセーブ
int guild_txt_sync(void)
{
	FILE *fp;
	int lock;

	if( !guild_db )
		return 1;

	if( (fp=lock_fopen(guild_txt,&lock))==NULL ){
		printf("int_guild: cant write [%s] !!! data is lost !!!\n",guild_txt);
		return 1;
	}
	numdb_foreach(guild_db,guild_txt_sync_sub,fp);
	lock_fclose(fp,guild_txt,&lock);

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

// ギルド名検索用
static int guild_txt_load_str_sub(void *key,void *data,va_list ap)
{
	struct guild *g, **dst;
	char *str;

	g   = (struct guild *)data;
	str = va_arg(ap,char *);
	dst = va_arg(ap,struct guild **);

	if(*dst == NULL) {
		if(strcmp(g->name,str) == 0)
			*dst = g;
	}
	return 0;
}

// ギルド名検索
const struct guild* guild_txt_load_str(char *str)
{
	struct guild *g=NULL;

	numdb_foreach(guild_db,guild_txt_load_str_sub,str,&g);
	return g;
}

// ギルド解散処理用（同盟/敵対を解除）
static int guild_txt_delete_sub(void *key,void *data,va_list ap)
{
	struct guild *g=(struct guild *)data;
	int guild_id=va_arg(ap,int);
	int i;

	for(i=0;i<MAX_GUILDALLIANCE;i++){
		if(g->alliance[i].guild_id==guild_id)
		{
			g->alliance[i].guild_id=0;
#ifdef TXT_JOURNAL
			if( guild_journal_enable )
				journal_write( &guild_journal, g->guild_id, g );
#endif
		}
	}
	return 0;
}

void guild_txt_delete(int guild_id)
{
	struct guild *g = (struct guild *)numdb_search(guild_db,guild_id);

	if(g) {
		numdb_foreach(guild_db,guild_txt_delete_sub,g->guild_id);
		numdb_erase(guild_db,g->guild_id);
		gstorage_delete(g->guild_id);
		mapif_guild_broken(g->guild_id,0);
		aFree(g);

#ifdef TXT_JOURNAL
		if( guild_journal_enable )
			journal_write( &guild_journal, guild_id, NULL );
#endif
	}
}

void guild_txt_new(struct guild *g2)
{
	struct guild* g1 = (struct guild *)aMalloc(sizeof(struct guild));

	g2->guild_id = guild_newid++;
	memcpy(g1,g2,sizeof(struct guild));
	numdb_insert(guild_db,g2->guild_id,g1);
#ifdef TXT_JOURNAL
	if( guild_journal_enable )
		journal_write( &guild_journal, g1->guild_id, g1 );
#endif
}

void guild_txt_config_read_sub(const char* w1,const char *w2)
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
}

static int guild_txt_db_final(void *key,void *data,va_list ap)
{
	struct guild *g = (struct guild *)data;

	aFree(g);

	return 0;
}

void guild_txt_final(void)
{
	if(guild_db)
		numdb_final(guild_db,guild_txt_db_final);

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

int guild_txt_save(struct guild* g2)
{
	struct guild *g1 = (struct guild *)numdb_search(guild_db,g2->guild_id);

	if(g1 == NULL) {
		g1 = (struct guild *)aMalloc(sizeof(struct guild));
		numdb_insert(guild_db,g2->guild_id,g1);
	}
	memcpy(g1,g2,sizeof(struct guild));
#ifdef TXT_JOURNAL
	if( guild_journal_enable )
		journal_write( &guild_journal, g1->guild_id, g1 );
#endif
	return 1;
}

// ギルド城データの文字列への変換
static int guildcastle_tostr(char *str,struct guild_castle *gc)
{
	sprintf(str,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
		gc->castle_id,gc->guild_id,gc->economy,gc->defense,gc->triggerE,
		gc->triggerD,gc->nextTime,gc->payTime,gc->createTime,gc->visibleC,
		gc->visibleG0,gc->visibleG1,gc->visibleG2,gc->visibleG3,gc->visibleG4,
		gc->visibleG5,gc->visibleG6,gc->visibleG7);

	return 0;
}

// ギルド城データの文字列からの変換
static int guildcastle_fromstr(char *str,struct guild_castle *gc)
{
	int tmp_int[18];

	memset(gc,0,sizeof(struct guild_castle));
	if( sscanf(str,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
		&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],&tmp_int[4],&tmp_int[5],&tmp_int[6],
		&tmp_int[7],&tmp_int[8],&tmp_int[9],&tmp_int[10],&tmp_int[11],&tmp_int[12],&tmp_int[13],
		&tmp_int[14],&tmp_int[15],&tmp_int[16],&tmp_int[17]) <18 )
		return 1;
	gc->castle_id  = tmp_int[0];
	gc->guild_id   = tmp_int[1];
	gc->economy    = tmp_int[2];
	gc->defense    = tmp_int[3];
	gc->triggerE   = tmp_int[4];
	gc->triggerD   = tmp_int[5];
	gc->nextTime   = tmp_int[6];
	gc->payTime    = tmp_int[7];
	gc->createTime = tmp_int[8];
	gc->visibleC   = tmp_int[9];
	gc->visibleG0  = tmp_int[10];
	gc->visibleG1  = tmp_int[11];
	gc->visibleG2  = tmp_int[12];
	gc->visibleG3  = tmp_int[13];
	gc->visibleG4  = tmp_int[14];
	gc->visibleG5  = tmp_int[15];
	gc->visibleG6  = tmp_int[16];
	gc->visibleG7  = tmp_int[17];

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

static int guildcastle_txt_init(void)
{
	char line[1024];
	struct guild_castle gc;
	FILE *fp;
	int i,c=0;

	// デフォルトデータを作成
	memset(castle_db,0,sizeof(castle_db));
	for(i=0; i<MAX_GUILDCASTLE; i++)
		castle_db[i].castle_id = i;

	if( (fp=fopen(castle_txt,"r"))==NULL ){
		return 1;
	}

	while(fgets(line,sizeof(line),fp)){
		if(guildcastle_fromstr(line,&gc)==0 && gc.castle_id >= 0 && gc.castle_id < MAX_GUILDCASTLE) {
			memcpy(&castle_db[gc.castle_id], &gc, sizeof(gc));
		} else {
			printf("int_guild: broken data [%s] line %d\n",castle_txt,c);
		}
		c++;
	}
	fclose(fp);

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
	return 0;
}

// ギルド城データのセーブ用
static int guildcastle_txt_sync(void)
{
	FILE *fp;
	int i,lock;
	char line[1024];

	if( (fp=lock_fopen(castle_txt,&lock))==NULL ){
		printf("int_guild: cant write [%s] !!! data is lost !!!\n",castle_txt);
		return 1;
	}

	for(i=0; i<MAX_GUILDCASTLE; i++) {
		guildcastle_tostr(line,&castle_db[i]);
		fprintf(fp,"%s" RETCODE,line);
	}
	lock_fclose(fp,castle_txt,&lock);

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

#define guild_new      guild_txt_new
#define guild_fin      guild_txt_fin
#define guild_init     guild_txt_init
#define guild_save     guild_txt_save
#define guild_sync     guild_txt_sync
#define guild_load_num guild_txt_load_num
#define guild_load_str guild_txt_load_str
#define guild_delete   guild_txt_delete
#define guild_config_read_sub guild_txt_config_read_sub

#else /* TXT_ONLY */

int guildcastle_sql_init(void);
int guildcastle_tosql(int castle_id);

static char guild_db_[256]          = "guild";
static char guild_alliance_db[256]  = "guild_alliance";
static char guild_castle_db[256]    = "guild_castle";
static char guild_expulsion_db[256] = "guild_expulsion";
static char guild_member_db[256]    = "guild_member";
static char guild_position_db[256]  = "guild_position";
static char guild_skill_db[256]     = "guild_skill";

int guild_sql_init(void)
{
	guild_readdb();
	guildcastle_sql_init();
	guild_db=numdb_init();
	return 0;
}

int guildcastle_sql_init(void)
{
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;
	struct guild_castle *gc;
	int i,id;

	// デフォルトデータを作成
	memset(castle_db,0,sizeof(castle_db));
	for(i=0; i<MAX_GUILDCASTLE; i++)
		castle_db[i].castle_id = i;

	sprintf(tmp_sql ,"SELECT * FROM `%s` ORDER BY `castle_id`", guild_castle_db);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (select `%s`)- %s\n", guild_castle_db, mysql_error(&mysql_handle) );
	}
	sql_res = mysql_store_result(&mysql_handle);

	if(sql_res) {
		for(i=0; (sql_row = mysql_fetch_row(sql_res)); i++)
		{
			id = atoi(sql_row[0]);
			if(id < 0 || id >= MAX_GUILDCASTLE)
				continue;
			gc = &castle_db[id];

			gc->guild_id   = atoi(sql_row[1]);
			gc->economy    = atoi(sql_row[2]);
			gc->defense    = atoi(sql_row[3]);
			gc->triggerE   = atoi(sql_row[4]);
			gc->triggerD   = atoi(sql_row[5]);
			gc->nextTime   = atoi(sql_row[6]);
			gc->payTime    = atoi(sql_row[7]);
			gc->createTime = atoi(sql_row[8]);
			gc->visibleC   = atoi(sql_row[9]);
			gc->visibleG0  = atoi(sql_row[10]);
			gc->visibleG1  = atoi(sql_row[11]);
			gc->visibleG2  = atoi(sql_row[12]);
			gc->visibleG3  = atoi(sql_row[13]);
			gc->visibleG4  = atoi(sql_row[14]);
			gc->visibleG5  = atoi(sql_row[15]);
			gc->visibleG6  = atoi(sql_row[16]);
			gc->visibleG7  = atoi(sql_row[17]);
		}
		mysql_free_result(sql_res);
	}
	return 0;
}

static int guildcastle_tosql(int castle_id)
{
	struct guild_castle *gc = &castle_db[castle_id];

	//printf("Request save guild castle ....");
	sprintf(tmp_sql,"UPDATE %s SET guild_id = %d,economy = %d,"
		"defense = %d,triggerE = %d,"
		"triggerD = %d,nextTime = %d,"
		"payTime = %d,createTime = %d,"
		"visibleC = %d,visibleG0 = %d,"
		"visibleG1 = %d,visibleG2 = %d,"
		"visibleG3 = %d,visibleG4 = %d,"
		"visibleG5 = %d,visibleG6 = %d,"
		"visibleG7 = %d WHERE castle_id = %d;",
		guild_castle_db,
		gc->guild_id,
		gc->economy,gc->defense,
		gc->triggerE,gc->triggerD,
		gc->nextTime,gc->payTime,
		gc->createTime,gc->visibleC,
		gc->visibleG0,gc->visibleG1,
		gc->visibleG2,gc->visibleG3,
		gc->visibleG4,gc->visibleG5,
		gc->visibleG6,gc->visibleG7,
		gc->castle_id
	);

	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error in Save guild castle: %s\n", mysql_error(&mysql_handle) );
		return 1;
	}

	return 0;
}

static int guild_guildcastle_save(void)
{
	int i;

	for(i=0;i<MAX_GUILDCASTLE;i++)
		guildcastle_tosql(i);
	return 0;
}

int guild_sql_sync(void)
{
	guild_guildcastle_save();
	return 0;
}

const struct guild *guild_sql_load_num(int guild_id)
{
	int i;
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

	// printf("Request load guild(% 6d)[",guild_id);
	sprintf(
		tmp_sql,
		"SELECT `name`,`master`,`guild_lv`,`connect_member`,`max_member`,"
		"`average_lv`,`exp`,`next_exp`,`skill_point`,`mes1`,`mes2`,`emblem_len`,"
		"`emblem_id`,`emblem_data` FROM `%s` WHERE `guild_id`='%d'",guild_db_, guild_id
	);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (select `%s`)- %s\n", guild_db_, mysql_error(&mysql_handle) );
		g->guild_id = -1;
		return NULL;
	}

	sql_res = mysql_store_result(&mysql_handle);
	if (sql_res!=NULL && mysql_num_rows(sql_res)>0) {
		sql_row = mysql_fetch_row(sql_res);
		if (sql_row==NULL) {
			mysql_free_result(sql_res);
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
		if( sql_res ) mysql_free_result(sql_res);
		g->guild_id = -1;
		return NULL;
	}
	mysql_free_result(sql_res);
	// printf("basic ");

	//printf("- Read guild_member %d from sql \n",guild_id);
	sprintf(
		tmp_sql,
		"SELECT `account_id`,`char_id`,`hair`,`hair_color`,`gender`,`class`,`lv`,"
		"`exp`,`exp_payper`,`online`,`position`,`name` FROM `%s` "
		"WHERE `guild_id`='%d' ORDER BY `position`", guild_member_db, guild_id
	);
	//printf("  %s\n",tmp_sql);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (select `%s`)- %s\n", guild_member_db, mysql_error(&mysql_handle) );
		g->guild_id = -1;
		return NULL;
	}
	sql_res = mysql_store_result(&mysql_handle);
	if (sql_res!=NULL && mysql_num_rows(sql_res)>0) {
		int i;
		for(i=0; (sql_row = mysql_fetch_row(sql_res)) && i<MAX_GUILD ;i++){
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
	mysql_free_result(sql_res);
	// printf("member ");

	//printf("- Read guild_position %d from sql \n",guild_id);
	sprintf(tmp_sql,"SELECT `position`,`name`,`mode`,`exp_mode` FROM `%s` WHERE `guild_id`='%d'",guild_position_db, guild_id);
	//printf("  %s\n",tmp_sql);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (select `%s`)- %s\n", guild_position_db, mysql_error(&mysql_handle) );
		g->guild_id = -1;
		return NULL;
	}
	sql_res = mysql_store_result(&mysql_handle);
	if (sql_res!=NULL && mysql_num_rows(sql_res)>0) {
		int i;
		for(i=0;((sql_row = mysql_fetch_row(sql_res))&&i<MAX_GUILDPOSITION);i++){
			int position = atoi(sql_row[0]);
			struct guild_position *p = &g->position[position];
			strncpy(p->name,sql_row[1],24);
			p->name[23] = '\0';	// force \0 terminal
			p->mode     = atoi(sql_row[2]);
			p->exp_mode = atoi(sql_row[3]);
		}
	}
	mysql_free_result(sql_res);
	// printf("position ");

	//printf("- Read guild_alliance %d from sql \n",guild_id);
	sprintf(
		tmp_sql,
		"SELECT `opposition`,`alliance_id`,`name` FROM `%s` WHERE `guild_id`='%d'",
		guild_alliance_db, guild_id
	);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (select `%s`)- %s\n", guild_alliance_db, mysql_error(&mysql_handle) );
		g->guild_id = -1;
		return NULL;
	}
	sql_res = mysql_store_result(&mysql_handle);
	if (sql_res!=NULL && mysql_num_rows(sql_res)>0) {
		int i;
		for(i=0;((sql_row = mysql_fetch_row(sql_res))&&i<MAX_GUILDALLIANCE);i++){
			struct guild_alliance *a = &g->alliance[i];
			a->opposition = atoi(sql_row[0]);
			a->guild_id   = atoi(sql_row[1]);
			strncpy(a->name,sql_row[2],24);
			a->name[23] = '\0';	// force \0 terminal
		}
	}
	mysql_free_result(sql_res);
	// printf("alliance ");

	//printf("- Read guild_expulsion %d from sql \n",guild_id);
	sprintf(tmp_sql,"SELECT `name`,`mes`,`account_id` FROM `%s` WHERE `guild_id`='%d'",guild_expulsion_db, guild_id);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (select `%s`)- %s\n", guild_expulsion_db, mysql_error(&mysql_handle) );
		g->guild_id = -1;
		return NULL;
	}
	sql_res = mysql_store_result(&mysql_handle);
	if (sql_res!=NULL && mysql_num_rows(sql_res)>0) {
		int i;
		for(i=0;((sql_row = mysql_fetch_row(sql_res))&&i<MAX_GUILDEXPLUSION);i++){
			struct guild_explusion *e = &g->explusion[i];
			strncpy(e->name,sql_row[0],24);
			strncpy(e->mes,sql_row[1],40);
			e->account_id = atoi(sql_row[2]);

			// force \0 terminal
			e->name[23] = '\0';
			e->mes[39]  = '\0';
		}
	}
	mysql_free_result(sql_res);
	// printf("expulsion ");

	//printf("- Read guild_skill %d from sql \n",guild_id);
	sprintf(tmp_sql,"SELECT `id`,`lv` FROM `%s` WHERE `guild_id`='%d' ORDER BY `id`",guild_skill_db, guild_id);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (select `%s`)- %s\n", guild_skill_db, mysql_error(&mysql_handle) );
		g->guild_id = -1;
		return NULL;
	}
	sql_res = mysql_store_result(&mysql_handle);
	if (sql_res!=NULL && mysql_num_rows(sql_res)>0) {
		int i,n;
		for(i=0;((sql_row = mysql_fetch_row(sql_res))&&i<MAX_GUILDSKILL);i++){
			n = atoi(sql_row[0]) - GUILD_SKILLID;
			if(n >= 0 && n < MAX_GUILDSKILL) {
				g->skill[n].id = atoi(sql_row[0]);
				g->skill[n].lv = atoi(sql_row[1]);
			}
		}

		// 移行用
		for(i = 0; i< MAX_GUILDSKILL;i++)
			g->skill[i].id=GUILD_SKILLID+i;
	}
	mysql_free_result(sql_res);
	// printf("skill ");
	// printf("]\n");

	// この関数内部でメモリ内部のギルドデータが書き換えられるが、
	// 渡すデータが同じなら帰ってくるデータも同じになるので、
	// 放置することにする
	guild_calcinfo(g);

	return g;
}

const struct guild* guild_sql_load_str(char *str)
{
	int  id_num = -1;
	char buf[256];
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;

	sprintf(
		tmp_sql,"SELECT `guild_id`,`name` FROM `%s` WHERE `name` = '%s'",
		guild_db_,strecpy(buf,str)
	);
	if (mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (select `%s`)- %s\n", guild_db_, mysql_error(&mysql_handle));
	}
	sql_res = mysql_store_result(&mysql_handle);
	if (sql_res) {
		while( (sql_row = mysql_fetch_row(sql_res)) ) {
			if(strcmp(str, sql_row[1]) == 0) {
				id_num = atoi(sql_row[0]);
				break;
			}
		}
		mysql_free_result(sql_res);
	}
	if(id_num >= 0) {
		return guild_sql_load_num(id_num);
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

int guild_sql_save(struct guild* g2)
{
	int  i;
	char buf[256],buf2[256];
	char sep;
	char *p;
	const struct guild* g1 = guild_sql_load_num(g2->guild_id);

	if (g1 == NULL)
		return 0;

	// printf("Request save guild(% 6d)[",g2->guild_id);

	sep = ' ';
	// basic information
	p =  tmp_sql;
	p += sprintf(p,"UPDATE `%s` SET",guild_db_);
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
		if (mysql_query(&mysql_handle, tmp_sql)) {
			printf("DB server Error (update `%s`)- %s\n", guild_db_, mysql_error(&mysql_handle));
		}
		// printf("basic ");
	}

	if(memcmp(g1->member,g2->member,sizeof(g1->member))) {
		sprintf(tmp_sql, "DELETE FROM `%s` WHERE `guild_id`='%d'",guild_member_db,g2->guild_id);
		if(mysql_query(&mysql_handle, tmp_sql) ) {
			printf("DB server Error (delete `%s`)- %s\n", guild_member_db, mysql_error(&mysql_handle) );
		}

		p  = tmp_sql;
		p += sprintf(
			tmp_sql,
			"INSERT INTO `%s` (`guild_id`,`account_id`,`char_id`,`hair`,`hair_color`,`gender`,"
			"`class`,`lv`,`exp`,`exp_payper`,`online`,`position`,`name`) VALUES",
			guild_member_db
		);
		sep = ' ';

		// printf("- Insert guild %d to guild_member\n",g2->guild_id);
		for(i=0;i < g2->max_member;i++) {
			if (g2->member[i].account_id>0){
				struct guild_member *m = &g2->member[i];
				p += sprintf(
					p,
					"%c('%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%s')",
					sep,g2->guild_id,m->account_id,m->char_id,m->hair,m->hair_color,m->gender,
					m->class_,m->lv,m->exp,m->exp_payper,(int)m->online,m->position,strecpy(buf,m->name)
				);
				sep = ',';
			}
		}
		if(sep == ',') {
			if(mysql_query(&mysql_handle,tmp_sql)) {
				printf("DB server Error (insert `%s`)- %s\n", guild_member_db, mysql_error(&mysql_handle) );
			}
		}
		// printf("member ");
	}

	//printf("- Insert guild %d to guild_position\n",g2->guild_id);
	if(memcmp(g1->position,g2->position,sizeof(g1->position))) {
		//printf("- Delete guild %d from guild_position\n",g2->guild_id);
		sprintf(tmp_sql, "DELETE FROM `%s` WHERE `guild_id`='%d'",guild_position_db, g2->guild_id);
		if(mysql_query(&mysql_handle, tmp_sql) ) {
			printf("DB server Error (delete `%s`)- %s\n", guild_position_db, mysql_error(&mysql_handle) );
		}

		p  = tmp_sql;
		p += sprintf(
			tmp_sql,
			"INSERT INTO `%s` (`guild_id`,`position`,`name`,`mode`,`exp_mode`) VALUES",
			guild_position_db
		);
		sep = ' ';
		for(i=0;i<MAX_GUILDPOSITION;i++){
			struct guild_position *pos = &g2->position[i];
			p += sprintf(
				p,"%c('%d','%d','%s','%d','%d')",
				sep, g2->guild_id,i,strecpy(buf,pos->name),pos->mode,pos->exp_mode
			);
			sep = ',';
			//printf(" %s\n",tmp_sql);
		}
		if(sep == ',') {
			if(mysql_query(&mysql_handle, tmp_sql) ) {
				printf("DB server Error (insert `%s`)- %s\n", guild_position_db, mysql_error(&mysql_handle) );
			}
		}
		// printf("position ");
	}

	//printf("- Insert guild %d to guild_alliance\n",g2->guild_id);
	if(memcmp(g1->alliance,g2->alliance,sizeof(g1->alliance))) {
		sprintf(
			tmp_sql,
			"DELETE FROM `%s` WHERE `guild_id`='%d'",guild_alliance_db,g2->guild_id
		);
		if(mysql_query(&mysql_handle, tmp_sql) ) {
			printf("DB server Error (delete `%s`)- %s\n", guild_alliance_db, mysql_error(&mysql_handle) );
		}

		p  = tmp_sql;
		p += sprintf(
			tmp_sql,
			"INSERT INTO `%s` (`guild_id`,`opposition`,`alliance_id`,`name`) VALUES",
			guild_alliance_db
		);
		sep = ' ';
		for(i=0;i<MAX_GUILDALLIANCE;i++){
			struct guild_alliance *a = &g2->alliance[i];
			if(a->guild_id>0){
				p += sprintf(
					p,
					"%c('%d','%d','%d','%s')",
					sep,g2->guild_id,a->opposition,a->guild_id,strecpy(buf,a->name)
				);
				sep = ',';
			}
		}
		//printf(" %s\n",tmp_sql);
		if(sep == ',') {
			if(mysql_query(&mysql_handle, tmp_sql) ) {
				printf("DB server Error (insert `%s`)- %s\n", guild_alliance_db, mysql_error(&mysql_handle) );
			}
		}
		// printf("alliance ");
	}

	//printf("- Insert guild %d to guild_expulsion\n",g2->guild_id);
	if(memcmp(g1->explusion,g2->explusion,sizeof(g1->explusion))) {
		sprintf(tmp_sql, "DELETE FROM `%s` WHERE `guild_id`='%d'",guild_expulsion_db, g2->guild_id);
		if(mysql_query(&mysql_handle, tmp_sql) ) {
			printf("DB server Error (delete `%s`)- %s\n", guild_expulsion_db, mysql_error(&mysql_handle) );
		}
		p  = tmp_sql;
		p += sprintf(
			tmp_sql,
			"INSERT INTO `%s` (`guild_id`,`name`,`mes`,`account_id`) VALUES",
			guild_expulsion_db
		);
		sep = ' ';
		for(i=0;i<MAX_GUILDEXPLUSION;i++) {
			struct guild_explusion *e = &g2->explusion[i];
			if(e->account_id>0) {
				p += sprintf(
					p,"%c('%d','%s','%s','%d')",
					sep,g2->guild_id,strecpy(buf,e->name),strecpy(buf2,e->mes),e->account_id
				);
				sep = ',';
			}
		}
		if(sep == ',') {
			if(mysql_query(&mysql_handle, tmp_sql) ) {
				printf("DB server Error (insert `%s`)- %s\n", guild_expulsion_db, mysql_error(&mysql_handle) );
			}
		}
		// printf("expulsion ");
	}

	if(memcmp(g1->skill,g2->skill,sizeof(g1->skill))) {
		sprintf(tmp_sql,"DELETE FROM `%s` WHERE `guild_id`='%d'",guild_skill_db,g2->guild_id);
		if(mysql_query(&mysql_handle, tmp_sql) ) {
			printf("DB server Error (delete `%s`)- %s\n", guild_skill_db, mysql_error(&mysql_handle) );
		}
		p  = tmp_sql;
		p += sprintf(
			tmp_sql,
			"INSERT INTO `%s` (`guild_id`,`id`,`lv`) VALUES",
			guild_skill_db
		);
		sep = ' ';
		for(i=0;i<MAX_GUILDSKILL;i++) {
			if (g2->skill[i].id > 0) {
				p += sprintf(
					p,"%c('%d','%d','%d')",
					sep,g2->guild_id,g2->skill[i].id,g2->skill[i].lv
				);
				sep = ',';
			}
		}
		if(sep == ',') {
			if(mysql_query(&mysql_handle, tmp_sql) ) {
				printf("DB server Error (insert `%s`)- %s\n", guild_skill_db, mysql_error(&mysql_handle) );
			}
		}
		// printf("skill ");
	}
	// printf("]\n");
	{
		struct guild* g3 = (struct guild *)numdb_search(guild_db,g2->guild_id);
		if(g3)
			memcpy(g3,g2,sizeof(struct guild));
	}
	guild_guildcastle_save();
	return 1;
}

// ギルド解散処理用（同盟/敵対を解除）
// SQL 上から消すなら、メモリ上のギルドデータも消さないといけない
static int guild_sql_delete_sub(void *key,void *data,va_list ap)
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

void guild_sql_delete(int guild_id)
{
	int i;
	struct guild* g = (struct guild *)numdb_search(guild_db,guild_id);
	// printf("Request del  guild(%06d)[",guild_id);

	if(g) {
		numdb_erase(guild_db,g->guild_id);
		aFree(g);
	}
	numdb_foreach(guild_db,guild_sql_delete_sub,guild_id);
	gstorage_delete(guild_id);
	mapif_guild_broken(guild_id,0);

	sprintf(tmp_sql, "DELETE FROM `%s` WHERE `guild_id`='%d'",guild_db_, guild_id);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (delete `%s`)- %s\n", guild_db_, mysql_error(&mysql_handle) );
	}
	// printf("basic ");

	sprintf(tmp_sql, "DELETE FROM `%s` WHERE `guild_id`='%d'",guild_member_db, guild_id);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (delete `%s`)- %s\n", guild_member_db, mysql_error(&mysql_handle) );
	}
	// printf("member ");

	sprintf(tmp_sql, "DELETE FROM `%s` WHERE `guild_id`='%d'",guild_position_db, guild_id);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (delete `%s`)- %s\n", guild_position_db, mysql_error(&mysql_handle) );
	}
	// printf("position ");

	sprintf(tmp_sql, "DELETE FROM `%s` WHERE `guild_id`='%d' OR `alliance_id`='%d'",guild_alliance_db, guild_id,guild_id);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (delete `%s`)- %s\n", guild_alliance_db, mysql_error(&mysql_handle) );
	}
	// printf("alliance ");

	sprintf(tmp_sql, "DELETE FROM `%s` WHERE `guild_id`='%d'",guild_expulsion_db, guild_id);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (delete `%s`)- %s\n", guild_expulsion_db, mysql_error(&mysql_handle) );
	}
	// printf("expulsion ");

	sprintf(tmp_sql, "DELETE FROM `%s` WHERE `guild_id`='%d'",guild_skill_db, guild_id);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (delete `%s`)- %s\n", guild_skill_db, mysql_error(&mysql_handle) );
	}
	// printf("skill ");

	for(i=0;i<MAX_GUILDCASTLE;i++) {
		if(castle_db[i].guild_id == guild_id) {
			memset(&castle_db[i],0,sizeof(castle_db[0]));
			castle_db[i].castle_id = i;
		}
	}
	// printf("]\n");
}

int guild_sql_new(struct guild *g)
{
	// Add new guild
	char t_name[64];
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;

	// ギルドIDを読み出す
	// printf("Request make guild(------)[");
	sprintf(tmp_sql,"SELECT MAX(`guild_id`) FROM `%s`",guild_db_);
	if(mysql_query(&mysql_handle, tmp_sql)){
		printf("failed (get party_id), SQL error: %s\n", mysql_error(&mysql_handle));
		return 0;
	}

	// query ok -> get the data!
	sql_res = mysql_store_result(&mysql_handle);
	if(!sql_res){
		printf("failed (get party_id), SQL error: %s\n", mysql_error(&mysql_handle));
		return 0;
	}
	sql_row = mysql_fetch_row(sql_res);
	if(sql_row[0]) {
		g->guild_id = atoi(sql_row[0]) + 1;
	} else {
		g->guild_id = 10000;
	}
	mysql_free_result(sql_res);

	// DBに挿入
	sprintf(
		tmp_sql,
		"INSERT INTO `%s` (`guild_id`,`name`,`guild_lv`,`max_member`,`emblem_data`) VALUES ('%d','%s','1','%d','')",
		guild_db_,g->guild_id,strecpy(t_name,g->name),g->max_member
	);
	if(mysql_query(&mysql_handle, tmp_sql) ) {
		printf("DB server Error (insert `%s`)- %s\n", guild_db_, mysql_error(&mysql_handle) );
		return 0;
	}
	// printf("]\n");
	guild_sql_save(g);
	return 1;
}

void guild_sql_config_read_sub(const char *w1,const char* w2)
{
	// nothing to do
}

static int guild_sql_db_final(void *key,void *data,va_list ap)
{
	struct guild *g = (struct guild *)data;

	aFree(g);
	return 0;
}

void guild_sql_final(void)
{
	if(guild_db)
		numdb_final(guild_db,guild_sql_db_final);
}

#define guild_fin      guild_sql_fin
#define guild_new      guild_sql_new
#define guild_save     guild_sql_save
#define guild_init     guild_sql_init
#define guild_sync     guild_sql_sync
#define guild_load_num guild_sql_load_num
#define guild_load_str guild_sql_load_str
#define guild_delete   guild_sql_delete
#define guild_config_read_sub guild_sql_config_read_sub

#endif /* TXT_ONLY */


// ギルドが空かどうかチェック
int guild_check_empty(const struct guild *g)
{
	int i;

	for(i=0;i<g->max_member;i++){
		if(g->member[i].account_id>0){
			return 0;
		}
	}
	return 1;
}

// キャラの競合がないかチェック
// とりあえず省略
int guild_check_conflict(int guild_id,int account_id,int char_id)
{
	return 0;
}

int guild_nextexp(int level)
{
	if(level == 0) return 1;

	if(level < MAX_GUILDLEVEL && level > 0)
		return guild_exp[level-1];

	return 0;
}

// ギルドスキルがあるか確認
int guild_checkskill(const struct guild *g,int id)
{
	int idx = id - GUILD_SKILLID;

	if (idx < 0 || idx >= MAX_GUILDSKILL)
		return 0;
	return g->skill[idx].lv;
}

// ギルドの情報の再計算
int guild_calcinfo(struct guild *g)
{
	int i,c,nextexp;
	struct guild before=*g;

	// スキルIDの設定
	for(i=0;i<MAX_GUILDSKILL;i++)
		g->skill[i].id=i+GUILD_SKILLID;

	// ギルドレベル
	if(g->guild_lv <= 0)
		g->guild_lv = 1;
	if(g->guild_lv > MAX_GUILDLEVEL)
		g->guild_lv = MAX_GUILDLEVEL;
	nextexp = guild_nextexp(g->guild_lv);

	while(nextexp > 0 && g->exp >= nextexp){	// レベルアップ処理
		g->exp-=nextexp;
		g->guild_lv++;
		g->skill_point++;
		nextexp = guild_nextexp(g->guild_lv);
	}

	// ギルドの次の経験値
	g->next_exp = nextexp;

	// メンバ上限（ギルド拡張適用）
	g->max_member = 16 + guild_checkskill(g, GD_EXTENSION) * guild_extension_increment;
	if(g->max_member > MAX_GUILD)
		g->max_member = MAX_GUILD;

	// 平均レベルとオンライン人数
	g->average_lv=0;
	g->connect_member=0;
	for(i=c=0;i<g->max_member;i++){
		if(g->member[i].account_id>0){
			g->average_lv+=g->member[i].lv;
			c++;

			if(g->member[i].online>0)
				g->connect_member++;
		}
	}
	if(c != 0) {
		g->average_lv /= c;
	}

	// 全データを送る必要がありそう
	if( g->max_member!=before.max_member ||
	    g->guild_lv!=before.guild_lv ||
	    g->skill_point!=before.skill_point )
	{
		mapif_guild_info(-1,g);
		return 1;
	}

	return 0;
}

//-------------------------------------------------------------------
// map serverへの通信

// ギルド作成可否
int mapif_guild_created(int fd,int account_id,const struct guild *g)
{
	WFIFOW(fd,0)=0x3830;
	WFIFOL(fd,2)=account_id;
	if(g!=NULL){
		WFIFOL(fd,6)=g->guild_id;
		printf("int_guild: created! %d %s\n",g->guild_id,g->name);
	}else{
		WFIFOL(fd,6)=0;
	}
	WFIFOSET(fd,10);
	return 0;
}

// ギルド情報見つからず
int mapif_guild_noinfo(int fd,int guild_id)
{
	WFIFOW(fd,0)=0x3831;
	WFIFOW(fd,2)=8;
	WFIFOL(fd,4)=guild_id;
	WFIFOSET(fd,8);
	printf("int_guild: info not found %d\n",guild_id);
	return 0;
}

// ギルド情報まとめ送り
int mapif_guild_info(int fd,const struct guild *g)
{
	unsigned char *buf = (unsigned char *)aMalloc(4+sizeof(struct guild));

	WBUFW(buf,0)=0x3831;
	memcpy(buf+4,g,sizeof(struct guild));
	WBUFW(buf,2)=4+sizeof(struct guild);
	if(fd<0)
		mapif_sendall(buf,WBUFW(buf,2));
	else
		mapif_send(fd,buf,WBUFW(buf,2));
	aFree(buf);
	return 0;
}

// メンバ追加可否
int mapif_guild_memberadded(int fd,int guild_id,int account_id,int char_id,int flag)
{
	WFIFOW(fd,0)=0x3832;
	WFIFOL(fd,2)=guild_id;
	WFIFOL(fd,6)=account_id;
	WFIFOL(fd,10)=char_id;
	WFIFOB(fd,14)=flag;
	WFIFOSET(fd,15);
	return 0;
}

// 脱退/追放通知
int mapif_guild_leaved(int guild_id,int account_id,int char_id,int flag,const char *name,const char *mes)
{
	unsigned char buf[128];

	WBUFW(buf, 0)=0x3834;
	WBUFL(buf, 2)=guild_id;
	WBUFL(buf, 6)=account_id;
	WBUFL(buf,10)=char_id;
	WBUFB(buf,14)=flag;
	strncpy(WBUFP(buf,15),mes,40);
	strncpy(WBUFP(buf,55),name,24);
	mapif_sendall(buf,79);
	printf("int_guild: guild leaved %d %d %s %s\n",guild_id,account_id,name,mes);
	return 0;
}

// オンライン状態とLv更新通知
int mapif_guild_memberinfoshort(struct guild *g,int idx)
{
	unsigned char buf[32];

	WBUFW(buf, 0)=0x3835;
	WBUFL(buf, 2)=g->guild_id;
	WBUFL(buf, 6)=g->member[idx].account_id;
	WBUFL(buf,10)=g->member[idx].char_id;
	WBUFB(buf,14)=(unsigned char)g->member[idx].online;
	WBUFW(buf,15)=g->member[idx].lv;
	WBUFW(buf,17)=g->member[idx].class_;
	mapif_sendall(buf,19);
	return 0;
}

// 解散通知
int mapif_guild_broken(int guild_id,int flag)
{
	unsigned char buf[16];

	WBUFW(buf,0)=0x3836;
	WBUFL(buf,2)=guild_id;
	WBUFB(buf,6)=flag;
	mapif_sendall(buf,7);
	printf("int_guild: broken %d\n",guild_id);
	return 0;
}

// ギルド内発言
int mapif_guild_message(int guild_id,int account_id,char *mes,int len)
{
	unsigned char buf[512];

	WBUFW(buf,0)=0x3837;
	WBUFW(buf,2)=len+12;
	WBUFL(buf,4)=guild_id;
	WBUFL(buf,8)=account_id;
	memcpy(WBUFP(buf,12),mes,len);
	mapif_sendall(buf,len+12);
	return 0;
}

// ギルド基本情報変更通知
int mapif_guild_basicinfochanged(int guild_id,int type,const void *data,int len)
{
	unsigned char buf[2048];

	WBUFW(buf, 0)=0x3839;
	WBUFW(buf, 2)=len+10;
	WBUFL(buf, 4)=guild_id;
	WBUFW(buf, 8)=type;
	memcpy(WBUFP(buf,10),data,len);
	mapif_sendall(buf,len+10);
	return 0;
}

// ギルドメンバ情報変更通知
int mapif_guild_memberinfochanged(int guild_id,int account_id,int char_id,int type,const void *data,int len)
{
	unsigned char buf[2048];

	WBUFW(buf, 0)=0x383a;
	WBUFW(buf, 2)=len+18;
	WBUFL(buf, 4)=guild_id;
	WBUFL(buf, 8)=account_id;
	WBUFL(buf,12)=char_id;
	WBUFW(buf,16)=type;
	memcpy(WBUFP(buf,18),data,len);
	mapif_sendall(buf,len+18);
	return 0;
}

// ギルドスキルアップ通知
int mapif_guild_skillupack(int guild_id,int skill_num,int account_id)
{
	unsigned char buf[16];

	WBUFW(buf, 0)=0x383c;
	WBUFL(buf, 2)=guild_id;
	WBUFL(buf, 6)=skill_num;
	WBUFL(buf,10)=account_id;
	mapif_sendall(buf,14);
	return 0;
}

// ギルド同盟/敵対通知
int mapif_guild_alliance(int guild_id1,int guild_id2,int account_id1,int account_id2,
	int flag,const char *name1,const char *name2)
{
	unsigned char buf[128];

	WBUFW(buf, 0)=0x383d;
	WBUFL(buf, 2)=guild_id1;
	WBUFL(buf, 6)=guild_id2;
	WBUFL(buf,10)=account_id1;
	WBUFL(buf,14)=account_id2;
	WBUFB(buf,18)=flag;
	memcpy(WBUFP(buf,19),name1,24);
	memcpy(WBUFP(buf,43),name2,24);
	mapif_sendall(buf,67);
	return 0;
}

// ギルド役職変更通知
int mapif_guild_position(struct guild *g,int idx)
{
	unsigned char buf[128];

	WBUFW(buf,0)=0x383b;
	WBUFW(buf,2)=sizeof(struct guild_position)+12;
	WBUFL(buf,4)=g->guild_id;
	WBUFL(buf,8)=idx;
	memcpy(WBUFP(buf,12),&g->position[idx],sizeof(struct guild_position));
	mapif_sendall(buf,WBUFW(buf,2));
	return 0;
}

// ギルド告知変更通知
int mapif_guild_notice(struct guild *g)
{
	unsigned char buf[256];

	WBUFW(buf,0)=0x383e;
	WBUFL(buf,2)=g->guild_id;
	memcpy(WBUFP(buf,6),g->mes1,60);
	memcpy(WBUFP(buf,66),g->mes2,120);
	mapif_sendall(buf,186);
	return 0;
}

// ギルドエンブレム変更通知
int mapif_guild_emblem(struct guild *g)
{
	unsigned char buf[2048];

	WBUFW(buf,0)=0x383f;
	WBUFW(buf,2)=g->emblem_len+12;
	WBUFL(buf,4)=g->guild_id;
	WBUFL(buf,8)=g->emblem_id;
	memcpy(WBUFP(buf,12),g->emblem_data,g->emblem_len);
	mapif_sendall(buf,WBUFW(buf,2));
	return 0;
}

int mapif_guild_castle_dataload(int castle_id,int index,int value)
{
	unsigned char buf[16];

	WBUFW(buf, 0)=0x3840;
	WBUFW(buf, 2)=castle_id;
	WBUFB(buf, 4)=index;
	WBUFL(buf, 5)=value;
	mapif_sendall(buf,9);
	return 0;
}

int mapif_guild_castle_datasave(int castle_id,int index,int value)
{
	unsigned char buf[16];

	WBUFW(buf, 0)=0x3841;
	WBUFW(buf, 2)=castle_id;
	WBUFB(buf, 4)=index;
	WBUFL(buf, 5)=value;
	mapif_sendall(buf,9);
	return 0;
}

int mapif_guild_castle_alldataload(int fd)
{
	WFIFOW(fd,0)=0x3842;
	WFIFOW(fd,2)=4+sizeof(castle_db);
	memcpy(WFIFOP(fd,4), castle_db, sizeof(castle_db));
	WFIFOSET(fd,WFIFOW(fd,2));
	return 0;
}

//-------------------------------------------------------------------
// map serverからの通信


// ギルド作成要求
int mapif_parse_CreateGuild(int fd,int account_id,char *name,struct guild_member *master)
{
	struct guild g;
	int i;

	for(i=0;i<24 && name[i];i++){
		if( !(name[i]&0xe0) || name[i]==0x7f){
			printf("int_guild: illegal guild name [%s]\n",name);
			mapif_guild_created(fd,account_id,NULL);
			return 0;
		}
	}

	if(guild_load_str(name) !=NULL) {
		printf("int_guild: same name guild exists [%s]\n",name);
		mapif_guild_created(fd,account_id,NULL);
		return 0;
	}
	memset(&g,0,sizeof(struct guild));
	memcpy(g.name,name,24);
	memcpy(g.master,master->name,24);
	memcpy(&g.member[0],master,sizeof(struct guild_member));

	g.position[0].mode=0x11;

	strncpy(g.position[0].name,"GuildMaster",24);
	for(i=1;i<MAX_GUILDPOSITION-1;i++) {
		sprintf(g.position[i].name,"Position %d",i+1);
	}
	strncpy(g.position[MAX_GUILDPOSITION-1].name,"Newbie",24);

	// ここでギルド情報計算が必要と思われる
	g.max_member = (MAX_GUILD > 16)? 16: MAX_GUILD;
	g.average_lv = master->lv;
	g.guild_lv   = 1;
	for(i=0;i<MAX_GUILDSKILL;i++)
		g.skill[i].id=i+GUILD_SKILLID;

	guild_new(&g);

	mapif_guild_created(fd,account_id,&g);
	mapif_guild_info(-1,&g);

	inter_log("guild %s (id=%d) created by master %s (id=%d)",
		name, g.guild_id, master->name, master->account_id);

	return 0;
}

// ギルド情報要求
int mapif_parse_GuildInfo(int fd,int guild_id)
{
	const struct guild *g = guild_load_num(guild_id);

	if(g == NULL){
		// 存在しないギルド
		mapif_guild_noinfo(fd,guild_id);
	} else if(guild_check_empty(g)) {
		// メンバーがいないので解散扱い
		guild_delete(guild_id); // 残骸削除
		mapif_guild_noinfo(fd,guild_id);
		return 0;
	} else {
		// ギルド情報送信
		mapif_guild_info(fd,g);
	}
	return 0;
}

// ギルドメンバ追加要求
int mapif_parse_GuildAddMember(int fd,int guild_id,struct guild_member *m)
{
	const struct guild *g1 = guild_load_num(guild_id);
	struct guild g2;
	int i;

	if(g1 == NULL){
		mapif_guild_memberadded(fd,guild_id,m->account_id,m->char_id,1);
		return 0;
	}

	memcpy(&g2,g1,sizeof(struct guild));
	for(i=0;i<g2.max_member;i++){
		if(guild_join_limit && g2.member[i].account_id==m->account_id)
			break;
		if(g2.member[i].account_id==0){
			memcpy(&g2.member[i],m,sizeof(struct guild_member));
			mapif_guild_memberadded(fd,guild_id,m->account_id,m->char_id,0);
			guild_calcinfo(&g2);
			mapif_guild_info(-1,&g2);
			guild_save(&g2);
			return 0;
		}
	}
	mapif_guild_memberadded(fd,guild_id,m->account_id,m->char_id,1);
	return 0;
}

// ギルド脱退/追放要求
int mapif_parse_GuildLeave(int fd,int guild_id,int account_id,int char_id,int flag,const char *mes)
{
	const struct guild *g1 = guild_load_num(guild_id);
	struct guild g2;
	int i;

	if(g1 == NULL)
		return 0;

	memcpy(&g2,g1,sizeof(struct guild));
	for(i=0;i<MAX_GUILD;i++){
		if(g2.member[i].account_id==account_id && g2.member[i].char_id==char_id){
			if(flag){	// 追放の場合追放リストに入れる
				int j;
				for(j=0;j<MAX_GUILDEXPLUSION;j++){
					if(g2.explusion[j].account_id==0)
						break;
				}
				if(j>=MAX_GUILDEXPLUSION) {	// 一杯なので古いのを消す
					j=MAX_GUILDEXPLUSION-1;
					memmove(&g2.explusion[0],&g2.explusion[1],j*sizeof(g2.explusion[0]));
				}
				g2.explusion[j].account_id=account_id;
				strncpy(g2.explusion[j].name,g2.member[i].name,24);
				strncpy(g2.explusion[j].mes,mes,40);
			}

			mapif_guild_leaved(guild_id,account_id,char_id,flag,g2.member[i].name,mes);
			memset(&g2.member[i],0,sizeof(struct guild_member));

			if( guild_check_empty(&g2) ) {
				// 空データ
				guild_delete(g2.guild_id);
			} else {
				guild_save(&g2);
				mapif_guild_info(-1,&g2);	// まだ人がいるのでデータ送信
			}
			return 0;
		}
	}

	return 0;
}

// オンライン/Lv更新
static int mapif_parse_GuildChangeMemberInfoShort(int fd,int guild_id,int account_id,int char_id,unsigned char online,int lv,int class_)
{
	const struct guild *g1 = guild_load_num(guild_id);
	int i,alv,c;
	struct guild g2;

	if(g1 == NULL){
		return 0;
	}
	memcpy(&g2,g1,sizeof(struct guild));

	g2.connect_member=0;

	for(i=0,alv=0,c=0;i<MAX_GUILD;i++){
		if( g2.member[i].account_id==account_id && g2.member[i].char_id==char_id ) {
			g2.member[i].online=online;
			g2.member[i].lv=lv;
			g2.member[i].class_=class_;
			mapif_guild_memberinfoshort(&g2,i);
		}
		if( g2.member[i].account_id>0 ){
			alv+=g2.member[i].lv;
			c++;
		}
		if( g2.member[i].online )
			g2.connect_member++;
	}
	// 平均レベル
	if(c != 0) {
		g2.average_lv=alv/c;
	}
	guild_save(&g2);
	return 0;
}

// ギルド解散要求
int mapif_parse_BreakGuild(int fd,int guild_id)
{
	guild_delete(guild_id);
	inter_log("guild (id=%d) broken",guild_id);
	return 0;
}

// ギルドメッセージ送信
int mapif_parse_GuildMessage(int fd,int guild_id,int account_id,char *mes,int len)
{
	return mapif_guild_message(guild_id,account_id,mes,len);
}

// ギルド基本データ変更要求
int mapif_parse_GuildBasicInfoChange(int fd,int guild_id,int type,const char *data,int len)
{
	const struct guild *g1 = guild_load_num(guild_id);
	short dw = *((short *)data);

	if(g1 == NULL){
		return 0;
	}
	if(type == GBI_GUILDLV) {
		struct guild g2;
		memcpy(&g2,g1,sizeof(struct guild));
		if(dw > 0 && g2.guild_lv + dw <= MAX_GUILDLEVEL) {
			g2.guild_lv    += dw;
			g2.skill_point += dw;
		} else if(dw < 0 && g2.guild_lv + dw >= 1) {
			g2.guild_lv += dw;
		}
		mapif_guild_info(-1,&g2);
		guild_save(&g2);
	} else {
		printf("int_guild: GuildBasicInfoChange: Unknown type %d\n",type);
		mapif_guild_basicinfochanged(guild_id,type,data,len);
	}

	return 0;
}

// ギルドメンバデータ変更要求
int mapif_parse_GuildMemberInfoChange(int fd,int guild_id,int account_id,int char_id,int type,const char *data,int len)
{
	int i;
	const struct guild *g1 = guild_load_num(guild_id);
	struct guild g2;
	const void *p = NULL;

	if(g1 == NULL){
		return 0;
	}
	memcpy(&g2,g1,sizeof(struct guild));
	for(i=0;i<g2.max_member;i++) {
		if(g2.member[i].account_id==account_id && g2.member[i].char_id==char_id)
			break;
	}
	if(i == g2.max_member){
		printf("int_guild: GuildMemberChange: Not found %d,%d in %d[%s]\n",
			account_id,char_id,guild_id,g2.name);
		return 0;
	}
	switch(type){
	case GMI_POSITION:	// 役職
		g2.member[i].position=*((int *)data);
		break;
	case GMI_EXP:
		{	// EXP
			atn_bignumber tmp;
			int exp = *((int *)data);

			tmp = (atn_bignumber)g2.member[i].exp + exp;
			g2.member[i].exp = (tmp > 0x7fffffff)? 0x7fffffff: (tmp < 0)? 0: (int)tmp;

			tmp = (atn_bignumber)g2.exp + exp;
			g2.exp = (tmp > 0x7fffffff)? 0x7fffffff: (tmp < 0)? 0: (int)tmp;

			guild_calcinfo(&g2);	// Lvアップ判断
			mapif_guild_basicinfochanged(guild_id,GBI_EXP,&g2.exp,4);
			p = &g2.member[i].exp;
		}
		break;
	default:
		printf("int_guild: GuildMemberInfoChange: Unknown type %d\n",type);
		break;
	}
	mapif_guild_memberinfochanged(guild_id,account_id,char_id,type,(p == NULL)? data: p,len);
	guild_save(&g2);
	return 0;
}

// ギルド役職名変更要求
int mapif_parse_GuildPosition(int fd,int guild_id,int idx,struct guild_position *p)
{
	const struct guild *g1 = guild_load_num(guild_id);
	struct guild g2;

	if(g1 == NULL || idx<0 || idx>=MAX_GUILDPOSITION){
		return 0;
	}
	memcpy(&g2,g1,sizeof(struct guild));
	memcpy(&g2.position[idx],p,sizeof(struct guild_position));
	{
		unsigned char *p2 = g2.position[idx].name;
		int limit = sizeof(g2.position[0].name);
		while(*p2 && --limit) {
			if(*p2 < 0x20) *p2 = '.';
			p2++;
		}
	}
	mapif_guild_position(&g2,idx);
	guild_save(&g2);
	printf("int_guild: position changed %d\n",idx);
	return 0;
}

// ギルドスキルアップ要求
int mapif_parse_GuildSkillUp(int fd,int guild_id,int skill_num,int account_id,int flag)
{
	const struct guild *g1 = guild_load_num(guild_id);
	struct guild g2;
	int idx = skill_num - GUILD_SKILLID;

	if (g1 == NULL || idx < 0 || idx >= MAX_GUILDSKILL)
		return 0;
	memcpy(&g2,g1,sizeof(struct guild));
	if( g2.skill_point>0 || flag&1 ) {
		g2.skill[idx].lv++;
		if(!(flag&1)) g2.skill_point--;
		if(guild_calcinfo(&g2)==0)
			mapif_guild_info(-1,&g2);
		mapif_guild_skillupack(guild_id,skill_num,account_id);
		guild_save(&g2);
		printf("int_guild: skill %d up\n",skill_num);
	}
	return 0;
}

// ギルド同盟要求
int mapif_parse_GuildAlliance(int fd,int guild_id1,int guild_id2,int account_id1,int account_id2,int flag)
{
	const struct guild *g1[2];
	struct guild g2[2];
	int j,i;

	g1[0] = guild_load_num(guild_id1);
	g1[1] = guild_load_num(guild_id2);
	if(g1[0]==NULL || g1[1]==NULL) return 0;

	memcpy(&g2[0],g1[0],sizeof(struct guild));
	memcpy(&g2[1],g1[1],sizeof(struct guild));

	if(!(flag&0x8)){
		for(i=0;i<2-(flag&1);i++){
			for(j=0;j<MAX_GUILDALLIANCE;j++) {
				if(g2[i].alliance[j].guild_id==0) {
					g2[i].alliance[j].guild_id = g2[1-i].guild_id;
					memcpy(g2[i].alliance[j].name,g2[1-i].name,24);
					g2[i].alliance[j].opposition = flag&1;
					break;
				}
			}
		}
	} else {	// 関係解消
		for(i=0;i<2-(flag&1);i++){
			for(j=0;j<MAX_GUILDALLIANCE;j++) {
				if( g2[i].alliance[j].guild_id == g2[1-i].guild_id &&
				    g2[i].alliance[j].opposition == (flag&1))
				{
					g2[i].alliance[j].guild_id=0;
					break;
				}
			}
		}
	}
	mapif_guild_alliance(guild_id1,guild_id2,account_id1,account_id2,flag,g2[0].name,g2[1].name);
	guild_save(&g2[0]);
	guild_save(&g2[1]);
	return 0;
}

// ギルド告知変更要求
int mapif_parse_GuildNotice(int fd,int guild_id,const char *mes1,const char *mes2)
{
	const struct guild *g1 = guild_load_num(guild_id);
	struct guild g2;
	unsigned char *p2;
	int limit;

	if(g1 == NULL)
		return 0;
	memcpy(&g2,g1,sizeof(struct guild));
	memcpy(g2.mes1,mes1,60);
	memcpy(g2.mes2,mes2,120);

	p2    = g2.mes1;
	limit = sizeof(g2.mes1);

	while(*p2 && --limit) {
		if(*p2 < 0x20) *p2 = '.';
		p2++;
	}
	p2 = g2.mes2;
	limit = sizeof(g2.mes2);
	while(*p2 && --limit) {
		if(*p2 < 0x20) *p2 = '.';
		p2++;
	}
	guild_save(&g2);
	return mapif_guild_notice(&g2);
}

// ギルドエンブレム変更要求
int mapif_parse_GuildEmblem(int fd,int len,int guild_id,int dummy,const char *data)
{
	const struct guild *g1 = guild_load_num(guild_id);
	struct guild g2;

	if(g1 == NULL)
		return 0;
	memcpy(&g2,g1,sizeof(struct guild));
	memcpy(g2.emblem_data,data,len);
	g2.emblem_len=len;
	g2.emblem_id++;
	guild_save(&g2);
	return mapif_guild_emblem(&g2);
}

int mapif_parse_GuildCastleDataLoad(int fd,int castle_id,int index)
{
	struct guild_castle *gc;

	if(castle_id < 0 || castle_id >= MAX_GUILDCASTLE) {
		return mapif_guild_castle_dataload(castle_id,0,0);
	}
	gc = &castle_db[castle_id];

	switch(index){
		case 1:  return mapif_guild_castle_dataload(gc->castle_id,index,gc->guild_id);   break;
		case 2:  return mapif_guild_castle_dataload(gc->castle_id,index,gc->economy);    break;
		case 3:  return mapif_guild_castle_dataload(gc->castle_id,index,gc->defense);    break;
		case 4:  return mapif_guild_castle_dataload(gc->castle_id,index,gc->triggerE);   break;
		case 5:  return mapif_guild_castle_dataload(gc->castle_id,index,gc->triggerD);   break;
		case 6:  return mapif_guild_castle_dataload(gc->castle_id,index,gc->nextTime);   break;
		case 7:  return mapif_guild_castle_dataload(gc->castle_id,index,gc->payTime);    break;
		case 8:  return mapif_guild_castle_dataload(gc->castle_id,index,gc->createTime); break;
		case 9:  return mapif_guild_castle_dataload(gc->castle_id,index,gc->visibleC);   break;
		case 10: return mapif_guild_castle_dataload(gc->castle_id,index,gc->visibleG0);  break;
		case 11: return mapif_guild_castle_dataload(gc->castle_id,index,gc->visibleG1);  break;
		case 12: return mapif_guild_castle_dataload(gc->castle_id,index,gc->visibleG2);  break;
		case 13: return mapif_guild_castle_dataload(gc->castle_id,index,gc->visibleG3);  break;
		case 14: return mapif_guild_castle_dataload(gc->castle_id,index,gc->visibleG4);  break;
		case 15: return mapif_guild_castle_dataload(gc->castle_id,index,gc->visibleG5);  break;
		case 16: return mapif_guild_castle_dataload(gc->castle_id,index,gc->visibleG6);  break;
		case 17: return mapif_guild_castle_dataload(gc->castle_id,index,gc->visibleG7);  break;
		default:
			printf("mapif_parse_GuildCastleDataLoad ERROR!! (Not found index=%d)\n", index);
			break;
	}
	return 0;
}

int mapif_parse_GuildCastleDataSave(int fd,int castle_id,int index,int value)
{
	struct guild_castle *gc;

	if(castle_id < 0 || castle_id >= MAX_GUILDCASTLE) {
		return mapif_guild_castle_datasave(castle_id,index,value);
	}
	gc = &castle_db[castle_id];

	switch(index){
		case 1:
			if( gc->guild_id != value ) {
				inter_log(
					"guild id=%d %s castle id=%d",
					((value)? value: gc->guild_id), ((value)? "occupy": "abandon"), index
				);
			}
			gc->guild_id = value;
			break;
		case 2:  gc->economy    = value; break;
		case 3:  gc->defense    = value; break;
		case 4:  gc->triggerE   = value; break;
		case 5:  gc->triggerD   = value; break;
		case 6:  gc->nextTime   = value; break;
		case 7:  gc->payTime    = value; break;
		case 8:  gc->createTime = value; break;
		case 9:  gc->visibleC   = value; break;
		case 10: gc->visibleG0  = value; break;
		case 11: gc->visibleG1  = value; break;
		case 12: gc->visibleG2  = value; break;
		case 13: gc->visibleG3  = value; break;
		case 14: gc->visibleG4  = value; break;
		case 15: gc->visibleG5  = value; break;
		case 16: gc->visibleG6  = value; break;
		case 17: gc->visibleG7  = value; break;
		default:
			printf("mapif_parse_GuildCastleDataSave ERROR!! (Not found index=%d)\n", index);
			return 0;
	}
#if defined(TXT_ONLY) && defined(TXT_JOURNAL)
	if( guildcastle_journal_enable )
		journal_write( &guildcastle_journal, gc->castle_id, gc );
#endif
	return mapif_guild_castle_datasave(gc->castle_id,index,value);
}

// ギルドチェック要求
int mapif_parse_GuildCheck(int fd,int guild_id,int account_id,int char_id)
{
	return guild_check_conflict(guild_id,account_id,char_id);
}


// map server からの通信
// ・１パケットのみ解析すること
// ・パケット長データはinter.cにセットしておくこと
// ・パケット長チェックや、RFIFOSKIPは呼び出し元で行われるので行ってはならない
// ・エラーなら0(false)、そうでないなら1(true)をかえさなければならない
int inter_guild_parse_frommap(int fd)
{
	switch(RFIFOW(fd,0)){
	case 0x3030: mapif_parse_CreateGuild(fd,RFIFOL(fd,4),RFIFOP(fd,8),(struct guild_member *)RFIFOP(fd,32)); break;
	case 0x3031: mapif_parse_GuildInfo(fd,RFIFOL(fd,2)); break;
	case 0x3032: mapif_parse_GuildAddMember(fd,RFIFOL(fd,4),(struct guild_member *)RFIFOP(fd,8)); break;
	case 0x3034: mapif_parse_GuildLeave(fd,RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10),RFIFOB(fd,14),RFIFOP(fd,15)); break;
	case 0x3035: mapif_parse_GuildChangeMemberInfoShort(fd,RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10),RFIFOB(fd,14),RFIFOW(fd,15),RFIFOW(fd,17)); break;
	case 0x3036: mapif_parse_BreakGuild(fd,RFIFOL(fd,2)); break;
	case 0x3037: mapif_parse_GuildMessage(fd,RFIFOL(fd,4),RFIFOL(fd,8),RFIFOP(fd,12),RFIFOW(fd,2)-12); break;
	case 0x3038: mapif_parse_GuildCheck(fd,RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10)); break;
	case 0x3039: mapif_parse_GuildBasicInfoChange(fd,RFIFOL(fd,4),RFIFOW(fd,8),RFIFOP(fd,10),RFIFOW(fd,2)-10); break;
	case 0x303A: mapif_parse_GuildMemberInfoChange(fd,RFIFOL(fd,4),RFIFOL(fd,8),RFIFOL(fd,12),RFIFOW(fd,16),RFIFOP(fd,18),RFIFOW(fd,2)-18); break;
	case 0x303B: mapif_parse_GuildPosition(fd,RFIFOL(fd,4),RFIFOL(fd,8),(struct guild_position *)RFIFOP(fd,12)); break;
	case 0x303C: mapif_parse_GuildSkillUp(fd,RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10),RFIFOL(fd,14)); break;
	case 0x303D: mapif_parse_GuildAlliance(fd,RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10),RFIFOL(fd,14),RFIFOB(fd,18)); break;
	case 0x303E: mapif_parse_GuildNotice(fd,RFIFOL(fd,2),RFIFOP(fd,6),RFIFOP(fd,66)); break;
	case 0x303F: mapif_parse_GuildEmblem(fd,RFIFOW(fd,2)-12,RFIFOL(fd,4),RFIFOL(fd,8),RFIFOP(fd,12)); break;
	case 0x3040: mapif_parse_GuildCastleDataLoad(fd,RFIFOW(fd,2),RFIFOB(fd,4)); break;
	case 0x3041: mapif_parse_GuildCastleDataSave(fd,RFIFOW(fd,2),RFIFOB(fd,4),RFIFOL(fd,5)); break;

	default:
		return 0;
	}
	return 1;
}

// マップサーバーの接続時処理
int inter_guild_mapif_init(int fd)
{
	return mapif_guild_castle_alldataload(fd);
}

// サーバーから脱退要求（キャラ削除用）
int inter_guild_leave(int guild_id,int account_id,int char_id)
{
	return mapif_parse_GuildLeave(-1,guild_id,account_id,char_id,0,"**サーバー命令**");
}

// ギルド設定読み込み
void guild_config_read(const char *w1,const char* w2)
{
	if(strcmpi(w1,"guild_extension_increment")==0)
	{
		guild_extension_increment = atoi(w2);
		if( guild_extension_increment<0 ) guild_extension_increment=0;
		if( guild_extension_increment>6 ) guild_extension_increment=6;
	}
	else if(strcmpi(w1,"guild_join_limit")==0)
	{
		guild_join_limit = atoi(w2);
	}
	else
	{
		guild_config_read_sub(w1,w2);
	}
}
