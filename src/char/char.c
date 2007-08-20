
#define _CHAR_C_

#define DUMP_UNKNOWN_PACKET	1

#include <sys/types.h>
#ifndef _WIN32
	#include <sys/socket.h>
	#include <sys/ioctl.h>
	#include <unistd.h>
	#include <signal.h>
	#include <fcntl.h>
	#include <netdb.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <sys/time.h>
#else
	#include <winsock.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core.h"
#include "socket.h"
#include "timer.h"
#include "db.h"
#include "mmo.h"
#include "version.h"
#include "lock.h"
#include "nullpo.h"
#include "malloc.h"
#include "httpd.h"
#include "graph.h"
#include "journal.h"
#include "md5calc.h"
#include "utils.h"

#include "char.h"
#include "inter.h"
#include "int_pet.h"
#include "int_homun.h"
#include "int_guild.h"
#include "int_party.h"
#include "int_storage.h"
#include "int_mail.h"
#include "int_status.h"

#ifdef MEMWATCH
#include "memwatch.h"
#endif

static struct mmo_map_server server[MAX_MAP_SERVERS];
static int server_fd[MAX_MAP_SERVERS];

static int login_fd = -1;
static int char_fd  = -1;
static int char_sfd = -1;
char userid[24] = "";
char passwd[24] = "";
char server_name[20] = "Auriga";
char login_ip_str[16] = "";
unsigned long login_ip;
unsigned short login_port = 6900;
char char_ip_str[16] = "";
unsigned long char_ip;
unsigned short char_port = 6121;
char char_sip_str[16];
unsigned long char_sip = 0;
unsigned short char_sport = 0;
static int char_loginaccess_autorestart;
static int char_maintenance;
static int char_new;

char char_conf_filename[256]  = "conf/char_auriga.conf";
char inter_conf_filename[256] = "conf/inter_auriga.conf";

char unknown_char_name[24] = "Unknown";
char char_log_filename[1024] = "log/char.log";
char GM_account_filename[1024] = "conf/GM_account.txt";
char default_map_name[16] = "prontera.gat";
int  default_map_type = 0;
static int max_char_slot = 9;	// キャラクタースロットの最大数

static int char_log(char *fmt,...);
int parse_char(int fd);

#ifdef TXT_JOURNAL
static int char_journal_enable = 1;
static struct journal char_journal;
static char char_journal_file[1024] = "./save/auriga.journal";
static int char_journal_cache = 1000;
#endif

// online DB
static struct dbt *char_online_db;

#define CHAR_STATE_WAITAUTH 0
#define CHAR_STATE_AUTHOK 1

static struct {
	int account_id, char_id;
	int login_id1, login_id2;
	unsigned long ip;
	unsigned int tick;
	int delflag, sex;
} auth_fifo[AUTH_FIFO_SIZE];

static int auth_fifo_pos = 0;

static int max_connect_user = 0;
int autosave_interval = DEFAULT_AUTOSAVE_INTERVAL_CS;

static int start_zeny   = 500;
static int start_weapon = 1201;		/* Knife */
static int start_armor  = 2301;		/* Cotton Shirt */

static struct Ranking_Data ranking_data[MAX_RANKING][MAX_RANKER];
const char ranking_reg[MAX_RANKING][32] = {
	"PC_BLACKSMITH_POINT",
	"PC_ALCHEMIST_POINT",
	"PC_TAEKWON_POINT",
	"PC_PK_POINT",
	//"PC_PVP_POINT",
};

// 初期位置（confファイルから再設定可能）
static struct point start_point = { "new_1-1.gat", 53, 111 };

#ifdef TXT_ONLY

static struct mmo_chardata *char_dat = NULL;
static int  char_num,char_max;
static char char_txt[1024] = "save/auriga.txt";
static int  char_id_count = 150000;

// キャラIDからchar_datのインデックスを返す
static int char_id2idx(int char_id)
{
	int min = -1;
	int max = char_num;

	// binary search
	while(max - min > 1) {
		int mid = (min + max) / 2;
		if(char_dat[mid].st.char_id == char_id)
			return mid;

		if(char_dat[mid].st.char_id > char_id)
			max = mid;
		else
			min = mid;
	}
	return -1;
}

static int mmo_char_tostr(char *str,struct mmo_chardata *p)
{
	int i;
	char *str_p = str;
	unsigned short sk_lv;

	nullpo_retr(-1, p);

	str_p += sprintf(str_p,"%d\t%d,%d\t%s\t%d,%d,%d\t%d,%d,%d\t%d,%d,%d,%d\t%d,%d,%d,%d,%d,%d\t%d,%d"
		"\t%u,%d,%d,%d\t%d,%d,%d,%d\t%d,%d,%d\t%d,%d,%d,%d,%d"
		"\t%s,%d,%d\t%s,%d,%d,%d,%d,%d,%d\t",
		p->st.char_id,p->st.account_id,p->st.char_num,p->st.name,
		p->st.class_,p->st.base_level,p->st.job_level,
		p->st.base_exp,p->st.job_exp,p->st.zeny,
		p->st.hp,p->st.max_hp,p->st.sp,p->st.max_sp,
		p->st.str,p->st.agi,p->st.vit,p->st.int_,p->st.dex,p->st.luk,
		p->st.status_point,p->st.skill_point,
		p->st.option,p->st.karma,p->st.manner,p->st.die_counter,
		p->st.party_id,p->st.guild_id,p->st.pet_id,p->st.homun_id,
		p->st.hair,p->st.hair_color,p->st.clothes_color,
		p->st.weapon,p->st.shield,p->st.head_top,p->st.head_mid,p->st.head_bottom,
		p->st.last_point.map,p->st.last_point.x,p->st.last_point.y,
		p->st.save_point.map,p->st.save_point.x,p->st.save_point.y,
		p->st.partner_id,p->st.parent_id[0],p->st.parent_id[1],p->st.baby_id
	);
	for(i = 0; i < MAX_PORTAL_MEMO; i++) {
		if(p->st.memo_point[i].map[0])
			str_p += sprintf(str_p,"%s,%d,%d ",p->st.memo_point[i].map,p->st.memo_point[i].x,p->st.memo_point[i].y);
	}
	*(str_p++)='\t';

	for(i=0;i<MAX_INVENTORY;i++) {
		if(p->st.inventory[i].nameid) {
			str_p += sprintf(str_p,"%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d ",
			p->st.inventory[i].id,p->st.inventory[i].nameid,p->st.inventory[i].amount,p->st.inventory[i].equip,
			p->st.inventory[i].identify,p->st.inventory[i].refine,p->st.inventory[i].attribute,
			p->st.inventory[i].card[0],p->st.inventory[i].card[1],p->st.inventory[i].card[2],p->st.inventory[i].card[3]);
		}
	}
	*(str_p++)='\t';

	for(i=0;i<MAX_CART;i++) {
		if(p->st.cart[i].nameid) {
			str_p += sprintf(str_p,"%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d ",
			p->st.cart[i].id,p->st.cart[i].nameid,p->st.cart[i].amount,p->st.cart[i].equip,
			p->st.cart[i].identify,p->st.cart[i].refine,p->st.cart[i].attribute,
			p->st.cart[i].card[0],p->st.cart[i].card[1],p->st.cart[i].card[2],p->st.cart[i].card[3]);
		}
	}
	*(str_p++)='\t';

	for(i=0;i<MAX_SKILL;i++) {
		if(p->st.skill[i].id && p->st.skill[i].flag!=1){
			sk_lv = (p->st.skill[i].flag==0)? p->st.skill[i].lv: p->st.skill[i].flag-2;
			str_p += sprintf(str_p,"%d,%d ",p->st.skill[i].id,sk_lv);
		}
	}
	*(str_p++)='\t';

	for(i=0;i<p->reg.global_num;i++) {
		if(p->reg.global[i].str[0] && p->reg.global[i].value != 0)
			str_p += sprintf(str_p,"%s,%d ",p->reg.global[i].str,p->reg.global[i].value);
	}
	*(str_p++)='\t';

	for(i=0;i<p->st.friend_num;i++) {
		str_p += sprintf(str_p,"%d,%d ",p->st.friend_data[i].account_id, p->st.friend_data[i].char_id );
	}
	*(str_p++)='\t';

	for(i = 0; i < 3; i++) {
		if(p->st.feel_map[i][0])
			str_p += sprintf(str_p,"%s,%d ",p->st.feel_map[i],i);
	}
	*(str_p++)='\t';

	for(i = 0; i < MAX_HOTKEYS; i++) {
		if(p->st.hotkey[i].id > 0)
			str_p += sprintf(str_p,"%d,%d,%d,%d ",i,p->st.hotkey[i].type,p->st.hotkey[i].id,p->st.hotkey[i].lv);
	}
	*(str_p++)='\t';

	*str_p='\0';

	return 0;
}

static int mmo_char_fromstr(char *str,struct mmo_chardata *p)
{
	char tmp_str[3][256];
	int tmp_int[45];
	int set,next,len,i,n;

	nullpo_retr(0, p);

	// Auriga-089以降の形式
	set=sscanf(str,"%d\t%d,%d\t%255[^\t]\t%d,%d,%d\t%d,%d,%d\t%d,%d,%d,%d\t%d,%d,%d,%d,%d,%d\t%d,%d"
		"\t%u,%d,%d,%d\t%d,%d,%d,%d\t%d,%d,%d\t%d,%d,%d,%d,%d"
		"\t%255[^,],%d,%d\t%255[^,],%d,%d,%d,%d,%d,%d%n",
		&tmp_int[0],&tmp_int[1],&tmp_int[2],tmp_str[0],
		&tmp_int[3],&tmp_int[4],&tmp_int[5],
		&tmp_int[6],&tmp_int[7],&tmp_int[8],
		&tmp_int[9],&tmp_int[10],&tmp_int[11],&tmp_int[12],
		&tmp_int[13],&tmp_int[14],&tmp_int[15],&tmp_int[16],&tmp_int[17],&tmp_int[18],
		&tmp_int[19],&tmp_int[20],
		&tmp_int[21],&tmp_int[22],&tmp_int[23],&tmp_int[24],
		&tmp_int[25],&tmp_int[26],&tmp_int[27],&tmp_int[28],
		&tmp_int[29],&tmp_int[30],&tmp_int[31],
		&tmp_int[32],&tmp_int[33],&tmp_int[34],&tmp_int[35],&tmp_int[36],
		tmp_str[1],&tmp_int[37],&tmp_int[38],
		tmp_str[2],&tmp_int[39],&tmp_int[40],&tmp_int[41],&tmp_int[42],&tmp_int[43],&tmp_int[44],&next
	);

	if(set != 48) {
		tmp_int[24] = 0;	// die_counter
		set=sscanf(str,"%d\t%d,%d\t%255[^\t]\t%d,%d,%d\t%d,%d,%d\t%d,%d,%d,%d\t%d,%d,%d,%d,%d,%d\t%d,%d"
			"\t%u,%d,%d\t%d,%d,%d,%d\t%d,%d,%d\t%d,%d,%d,%d,%d"
			"\t%255[^,],%d,%d\t%255[^,],%d,%d,%d,%d,%d,%d%n",
			&tmp_int[0],&tmp_int[1],&tmp_int[2],tmp_str[0],
			&tmp_int[3],&tmp_int[4],&tmp_int[5],
			&tmp_int[6],&tmp_int[7],&tmp_int[8],
			&tmp_int[9],&tmp_int[10],&tmp_int[11],&tmp_int[12],
			&tmp_int[13],&tmp_int[14],&tmp_int[15],&tmp_int[16],&tmp_int[17],&tmp_int[18],
			&tmp_int[19],&tmp_int[20],
			&tmp_int[21],&tmp_int[22],&tmp_int[23],
			&tmp_int[25],&tmp_int[26],&tmp_int[27],&tmp_int[28],
			&tmp_int[29],&tmp_int[30],&tmp_int[31],
			&tmp_int[32],&tmp_int[33],&tmp_int[34],&tmp_int[35],&tmp_int[36],
			tmp_str[1],&tmp_int[37],&tmp_int[38],
			tmp_str[2],&tmp_int[39],&tmp_int[40],&tmp_int[41],&tmp_int[42],&tmp_int[43],&tmp_int[44],&next
		);

		if(set != 47)
			return 0;	// Athena1881以前の古い形式はサポートしない
	}

	strncpy(p->st.name, tmp_str[0], 24);
	strncpy(p->st.last_point.map, tmp_str[1], 24);
	strncpy(p->st.save_point.map, tmp_str[2], 24);

	// force \0 terminal
	p->st.name[23]           = '\0';
	p->st.last_point.map[23] = '\0';
	p->st.save_point.map[23] = '\0';

	p->st.char_id       = tmp_int[0];
	p->st.account_id    = tmp_int[1];
	p->st.char_num      = tmp_int[2];
	p->st.class_        = tmp_int[3];
	p->st.base_level    = tmp_int[4];
	p->st.job_level     = tmp_int[5];
	p->st.base_exp      = tmp_int[6];
	p->st.job_exp       = tmp_int[7];
	p->st.zeny          = tmp_int[8];
	p->st.hp            = tmp_int[9];
	p->st.max_hp        = tmp_int[10];
	p->st.sp            = tmp_int[11];
	p->st.max_sp        = tmp_int[12];
	p->st.str           = tmp_int[13];
	p->st.agi           = tmp_int[14];
	p->st.vit           = tmp_int[15];
	p->st.int_          = tmp_int[16];
	p->st.dex           = tmp_int[17];
	p->st.luk           = tmp_int[18];
	p->st.status_point  = tmp_int[19];
	p->st.skill_point   = tmp_int[20];
	p->st.option        = (unsigned int)tmp_int[21];
	p->st.karma         = tmp_int[22];
	p->st.manner        = tmp_int[23];
	p->st.die_counter   = tmp_int[24];
	p->st.party_id      = tmp_int[25];
	p->st.guild_id      = tmp_int[26];
	p->st.pet_id        = tmp_int[27];
	p->st.homun_id      = tmp_int[28];
	p->st.hair          = tmp_int[29];
	p->st.hair_color    = tmp_int[30];
	p->st.clothes_color = tmp_int[31];
	p->st.weapon        = tmp_int[32];
	p->st.shield        = tmp_int[33];
	p->st.head_top      = tmp_int[34];
	p->st.head_mid      = tmp_int[35];
	p->st.head_bottom   = tmp_int[36];
	p->st.last_point.x  = tmp_int[37];
	p->st.last_point.y  = tmp_int[38];
	p->st.save_point.x  = tmp_int[39];
	p->st.save_point.y  = tmp_int[40];
	p->st.partner_id    = tmp_int[41];
	p->st.parent_id[0]  = tmp_int[42];
	p->st.parent_id[1]  = tmp_int[43];
	p->st.baby_id       = tmp_int[44];

	if(str[next]=='\n' || str[next]=='\r')
		return 1;	// 新規データ
	next++;
	for(i = 0; str[next] && str[next] != '\t'; i++) {
		set=sscanf(str+next,"%255[^,],%d,%d%n",tmp_str[0],&tmp_int[0],&tmp_int[1],&len);
		if(set!=3)
			return 0;
		if(i < MAX_PORTAL_MEMO) {
			strncpy(p->st.memo_point[i].map, tmp_str[0], 24);
			p->st.memo_point[i].map[23] = '\0';	// force \0 terminal
			p->st.memo_point[i].x       = tmp_int[0];
			p->st.memo_point[i].y       = tmp_int[1];
		}
		next+=len;
		if(str[next]==' ')
			next++;
	}
	next++;
	for(i=0;str[next] && str[next]!='\t';i++){
		set=sscanf(str+next,"%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d%n",
			&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],
			&tmp_int[4],&tmp_int[5],&tmp_int[6],
			&tmp_int[7],&tmp_int[8],&tmp_int[9],&tmp_int[10],&len);
		if(set!=11)
			return 0;
		if(i < MAX_INVENTORY) {
			p->st.inventory[i].id        = (unsigned int)tmp_int[0];
			p->st.inventory[i].nameid    = tmp_int[1];
			p->st.inventory[i].amount    = tmp_int[2];
			p->st.inventory[i].equip     = tmp_int[3];
			p->st.inventory[i].identify  = tmp_int[4];
			p->st.inventory[i].refine    = tmp_int[5];
			p->st.inventory[i].attribute = tmp_int[6];
			p->st.inventory[i].card[0]   = tmp_int[7];
			p->st.inventory[i].card[1]   = tmp_int[8];
			p->st.inventory[i].card[2]   = tmp_int[9];
			p->st.inventory[i].card[3]   = tmp_int[10];
		}
		next+=len;
		if(str[next]==' ')
			next++;
	}
	next++;
	for(i=0;str[next] && str[next]!='\t';i++){
		set=sscanf(str+next,"%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d%n",
			&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],
			&tmp_int[4],&tmp_int[5],&tmp_int[6],
			&tmp_int[7],&tmp_int[8],&tmp_int[9],&tmp_int[10],&len);
		if(set!=11)
			return 0;
		if(i < MAX_CART) {
			p->st.cart[i].id        = (unsigned int)tmp_int[0];
			p->st.cart[i].nameid    = tmp_int[1];
			p->st.cart[i].amount    = tmp_int[2];
			p->st.cart[i].equip     = tmp_int[3];
			p->st.cart[i].identify  = tmp_int[4];
			p->st.cart[i].refine    = tmp_int[5];
			p->st.cart[i].attribute = tmp_int[6];
			p->st.cart[i].card[0]   = tmp_int[7];
			p->st.cart[i].card[1]   = tmp_int[8];
			p->st.cart[i].card[2]   = tmp_int[9];
			p->st.cart[i].card[3]   = tmp_int[10];
		}
		next+=len;
		if(str[next]==' ')
			next++;
	}
	next++;
	for(i=0;str[next] && str[next]!='\t';i++){
		set=sscanf(str+next,"%d,%d%n",&tmp_int[0],&tmp_int[1],&len);
		if(set!=2)
			return 0;
		n = tmp_int[0];
		if(n >= 0 && n < MAX_SKILL) {
			p->st.skill[n].id = tmp_int[0];
			p->st.skill[n].lv = tmp_int[1];
		}
		next+=len;
		if(str[next]==' ')
			next++;
	}
	next++;

	for(i=0;str[next] && str[next]!='\t';i++){
		set=sscanf(str+next,"%255[^,],%d%n",tmp_str[0],&tmp_int[0],&len);
		if(set!=2)
			return 0;
		if(i < GLOBAL_REG_NUM) {
			strncpy(p->reg.global[i].str, tmp_str[0], 32);
			p->reg.global[i].str[31] = '\0';	// force \0 terminal
			p->reg.global[i].value   = tmp_int[0];
		} else {
			printf("char_load %d: couldn't load %s (GLOBAL_REG_NUM = %d)\a\n", p->st.char_id, tmp_str[0], GLOBAL_REG_NUM);
		}
		next+=len;
		if(str[next]==' ')
			next++;
	}
	p->reg.global_num = (i < GLOBAL_REG_NUM)? i: GLOBAL_REG_NUM;
	next++;

	for(i=0;str[next] && str[next]!='\t';i++){
		set=sscanf(str+next,"%d,%d%n",&tmp_int[0],&tmp_int[1],&len); // name は後で解決する
		if(set!=2)
			return 0;
		if(i < MAX_FRIEND) {
			p->st.friend_data[i].account_id = tmp_int[0];
			p->st.friend_data[i].char_id    = tmp_int[1];
		}
		next+=len;
		if(str[next]==' ')
			next++;
	}
	p->st.friend_num = (i < MAX_FRIEND)? i: MAX_FRIEND;
	next++;

	for(i = 0; str[next] && str[next] != '\t' && str[next] != '\n' && str[next] != '\r'; i++) {
		set=sscanf(str+next,"%255[^,],%d%n",tmp_str[0],&tmp_int[0],&len);
		if(set!=2)
			return 0;
		n = tmp_int[0];
		if(n >= 0 && n < 3) {
			strncpy(p->st.feel_map[n], tmp_str[0], 24);
			p->st.feel_map[n][23] = '\0';	// force \0 terminal
		}
		next+=len;
		if(str[next]==' ')
			next++;
	}
	next++;

	for(i = 0; str[next] && str[next] != '\t' && str[next] != '\n' && str[next] != '\r'; i++) {
		set=sscanf(str+next,"%d,%d,%d,%d%n",&tmp_int[0],&tmp_int[1],&tmp_int[2],&tmp_int[3],&len);
		if(set!=4)
			return 0;
		n = tmp_int[0];
		if(n >= 0 && n < MAX_HOTKEYS) {
			p->st.hotkey[n].type = (char)tmp_int[1];
			p->st.hotkey[n].id   = tmp_int[2];
			p->st.hotkey[n].lv   = (unsigned short)tmp_int[3];
		}
		next+=len;
		if(str[next]==' ')
			next++;
	}

	return 1;
}

#ifdef TXT_JOURNAL
// ==========================================
// キャラクターデータのジャーナルのロールフォワード用コールバック関数
// ------------------------------------------
static int char_journal_rollforward( int key, void* buf, int flag )
{
	int idx = char_id2idx( key );

	// 念のためチェック
	if( flag == JOURNAL_FLAG_WRITE && key != ((struct mmo_chardata*)buf)->st.char_id )
	{
		printf("char_journal: key != char_id !\n");
		return 0;
	}

	// データの置き換え
	if( idx >= 0 )
	{
		if( flag == JOURNAL_FLAG_DELETE ) {
			memset( &char_dat[idx], 0, sizeof(struct mmo_chardata) );
		} else {
			memcpy( &char_dat[idx], buf, sizeof(struct mmo_chardata) );
		}
		return 1;
	}

	// 追加
	if( flag != JOURNAL_FLAG_DELETE )
	{
		if(char_num>=char_max)
		{
			// メモリが足りないなら拡張
			char_max+=256;
			char_dat=(struct mmo_chardata *)aRealloc(char_dat,sizeof(char_dat[0])*char_max);
			memset(char_dat + (char_max - 256), '\0', 256 * sizeof(char_dat[0]));
		}

		memcpy( &char_dat[char_num], buf, sizeof(struct mmo_chardata) );
		if(char_dat[char_num].st.char_id>=char_id_count)
			char_id_count=char_dat[char_num].st.char_id+1;
		char_num++;
		return 1;
	}

	return 0;
}

static void char_txt_sync(void);
#endif

static int char_txt_init(void)
{
	char line[65536];
	int ret, i, j;
	FILE *fp;

	fp=fopen(char_txt,"r");
	char_dat=(struct mmo_chardata *)aCalloc(256,sizeof(char_dat[0]));
	char_max=256;
	if(fp==NULL)
		return 0;
	while(fgets(line,65535,fp)){
		j = -1;
		if( sscanf(line,"%d\t%%newid%%%n",&i,&j)==1 && j > 0 && (line[j]=='\n' || line[j]=='\r') ){
			if(char_id_count<i)
				char_id_count=i;
			continue;
		}

		if(char_num>=char_max){
			char_max+=256;
			char_dat=(struct mmo_chardata *)aRealloc(char_dat,sizeof(char_dat[0])*char_max);
			memset(char_dat + (char_max - 256), '\0', 256 * sizeof(char_dat[0]));
		}

		ret=mmo_char_fromstr(line,&char_dat[char_num]);
		if(ret){
			int char_id = char_dat[char_num].st.char_id;
			if(char_id >= char_id_count)
				char_id_count = char_id+1;

			if(char_num > 0 && char_id < char_dat[char_num-1].st.char_id) {
				struct mmo_chardata tmp;
				int k = char_num;

				// 何故かキャラIDの昇順に並んでない場合は挿入ソートする
				while(k > 0 && char_id < char_dat[k-1].st.char_id) {
					k--;
				}
				memcpy(&tmp, &char_dat[char_num], sizeof(char_dat[0]));
				memmove(&char_dat[k+1], &char_dat[k], (char_num-k)*sizeof(char_dat[0]));
				memcpy(&char_dat[k], &tmp, sizeof(char_dat[0]));
			}
			char_num++;
		}
	}
	fclose(fp);

#ifdef TXT_JOURNAL
	if( char_journal_enable )
	{
		// ジャーナルデータのロールフォワード
		if( journal_load( &char_journal, sizeof(struct mmo_chardata), char_journal_file ) )
		{
			int c = journal_rollforward( &char_journal, char_journal_rollforward );

			printf("char: journal: roll-forward (%d)\n", c );

			// ロールフォワードしたので、txt データを保存する ( journal も新規作成される)
			char_txt_sync();
		}
		else
		{
			// ジャーナルを新規作成する
			journal_final( &char_journal );
			journal_create( &char_journal, sizeof(struct mmo_chardata), char_journal_cache, char_journal_file );
		}
	}
#endif

	// 友達リストの名前を解決
	for( i=0; i<char_num; i++ )
	{
		for( j=0; j<char_dat[i].st.friend_num; j++ )
		{
			struct friend_data* frd = char_dat[i].st.friend_data;
			const struct mmo_chardata* p = char_txt_load(frd[j].char_id);
			if( p ) {
				memcpy( frd[j].name, p->st.name, 24 );
			} else {
				char_dat[i].st.friend_num--;
				memmove( &frd[j], &frd[j+1], sizeof(frd[0])*( char_dat[i].st.friend_num - j ) );
				j--;
			}
		}
	}

	return 0;
}

static void char_txt_sync(void)
{
	char line[65536];
	int i,lock;
	FILE *fp;

	if( !char_dat )
		return;

	fp=lock_fopen(char_txt,&lock);
	if(fp==NULL)
		return;
	for(i=0;i<char_num;i++){
		if(char_dat[i].st.char_id > 0) {
			mmo_char_tostr(line,&char_dat[i]);
			fprintf(fp,"%s" RETCODE,line);
		}
	}
	fprintf(fp,"%d\t%%newid%%" RETCODE,char_id_count);
	lock_fclose(fp,char_txt,&lock);

#ifdef TXT_JOURNAL
	if( char_journal_enable )
	{
		// コミットしたのでジャーナルを新規作成する
		journal_final( &char_journal );
		journal_create( &char_journal, sizeof(struct mmo_chardata), char_journal_cache, char_journal_file );
	}
#endif
}

void char_txt_final(void)
{
	//char_txt_sync(); // do_final で呼んでるはず
	aFree(char_dat);

#ifdef TXT_JOURNAL
	if( char_journal_enable )
	{
		journal_final( &char_journal );
	}
#endif
}

const struct mmo_chardata *char_txt_make(struct char_session_data *sd,unsigned char *dat,int *flag)
{
	int i,j;
	char name[24];

	memset(name, 0, sizeof(name));
	for(i=0;i<24 && dat[i];i++){
		if(dat[i]<0x20 || dat[i]==0x7f)
			return NULL;
		name[i] = dat[i];
	}
	name[23] = '\0';	// force \0 terminal

	for(i = 24;i<=29;i++) {
		if(dat[i] > 9) return NULL;
	}
	if(dat[30] >= max_char_slot){
		*flag = 0x02;
		printf("make new char over slot!! (%d / %d)\n",dat[30]+1,max_char_slot);
		return NULL;
	}
	if(dat[24]+dat[25]+dat[26]+dat[27]+dat[28]+dat[29]>5*6 || dat[30]>=9 || dat[33]==0 || dat[33]>=24 || dat[31]>=9)
	{
		char_log(
			"make new char error %d %s %d,%d,%d,%d,%d,%d %d,%d",
			dat[30],name,dat[24],dat[25],dat[26],dat[27],dat[28],dat[29],dat[33],dat[31]
		);
		return NULL;
	}
	char_log("make new char %d %s",dat[30],name);

	for(i=0;i<char_num;i++){
		if(strcmp(char_dat[i].st.name,name)==0 || (char_dat[i].st.account_id==sd->account_id && char_dat[i].st.char_num==dat[30]))
			return NULL;
	}

	if(char_num>=char_max) {
		// realloc() するとchar_datの位置が変わるので、session のデータを見て
		// 強制的に置き換える処理をしないとダメ。
		int i,j;
		struct mmo_chardata *char_dat_old = char_dat;
		struct mmo_chardata *char_dat_new = (struct mmo_chardata *)aMalloc(sizeof(struct mmo_chardata) * (char_max + 256));
		memcpy(char_dat_new,char_dat_old,sizeof(struct mmo_chardata) * char_max);
		memset(char_dat_new + char_max,0,256 * sizeof(struct mmo_chardata));
		char_max += 256;
		for(i = 0; i <= fd_max; i++) {
			struct char_session_data *sd;
			if(session[i] && session[i]->func_parse == parse_char && (sd = (struct char_session_data *)session[i]->session_data)) {
				for(j = 0; j < max_char_slot; j++) {
					if(sd->found_char[j]) {
						sd->found_char[j] = char_dat_new + (sd->found_char[j] - char_dat_old);
					}
				}
			}
		}
		char_dat = char_dat_new;
		aFree(char_dat_old);
	}
	memset(&char_dat[i],0,sizeof(char_dat[0]));

	char_dat[i].st.char_id       = char_id_count++;
	char_dat[i].st.account_id    = sd->account_id;
	char_dat[i].st.char_num      = dat[30];
	strncpy(char_dat[i].st.name,name,24);
	char_dat[i].st.class_        = 0;
	char_dat[i].st.base_level    = 1;
	char_dat[i].st.job_level     = 1;
	char_dat[i].st.base_exp      = 0;
	char_dat[i].st.job_exp       = 0;
	char_dat[i].st.zeny          = start_zeny;
	char_dat[i].st.str           = dat[24];
	char_dat[i].st.agi           = dat[25];
	char_dat[i].st.vit           = dat[26];
	char_dat[i].st.int_          = dat[27];
	char_dat[i].st.dex           = dat[28];
	char_dat[i].st.luk           = dat[29];
	char_dat[i].st.max_hp        = 40 * (100 + char_dat[i].st.vit) / 100;
	char_dat[i].st.max_sp        = 11 * (100 + char_dat[i].st.int_) / 100;
	char_dat[i].st.hp            = char_dat[i].st.max_hp;
	char_dat[i].st.sp            = char_dat[i].st.max_sp;
	char_dat[i].st.status_point  = 0;
	char_dat[i].st.skill_point   = 0;
	char_dat[i].st.option        = 0;
	char_dat[i].st.karma         = 0;
	char_dat[i].st.manner        = 0;
	char_dat[i].st.die_counter   = 0;
	char_dat[i].st.party_id      = 0;
	char_dat[i].st.guild_id      = 0;
	char_dat[i].st.hair          = dat[33];
	char_dat[i].st.hair_color    = dat[31];
	char_dat[i].st.clothes_color = 0;

	j = 0;
	if(start_weapon > 0) {
		char_dat[i].st.inventory[j].id       = 1;
		char_dat[i].st.inventory[j].nameid   = start_weapon;
		char_dat[i].st.inventory[j].amount   = 1;
		char_dat[i].st.inventory[j].equip    = 0x02;
		char_dat[i].st.inventory[j].identify = 1;
		char_dat[i].st.weapon = 1;
		j++;
	}
	if(start_armor > 0) {
		char_dat[i].st.inventory[j].id       = 2;
		char_dat[i].st.inventory[j].nameid   = start_armor;
		char_dat[i].st.inventory[j].amount   = 1;
		char_dat[i].st.inventory[j].equip    = 0x10;
		char_dat[i].st.inventory[j].identify = 1;
	}
	char_dat[i].st.shield      = 0;
	char_dat[i].st.head_top    = 0;
	char_dat[i].st.head_mid    = 0;
	char_dat[i].st.head_bottom = 0;
	memcpy(&char_dat[i].st.last_point,&start_point,sizeof(start_point));
	memcpy(&char_dat[i].st.save_point,&start_point,sizeof(start_point));
	char_num++;

#ifdef TXT_JOURNAL
	if( char_journal_enable )
		journal_write( &char_journal, char_dat[i].st.char_id, &char_dat[i] );
#endif

	return &char_dat[i];
}

int char_txt_load_all(struct char_session_data* sd,int account_id)
{
	int i;
	int found_num = 0;

	for(i=0 ; i < char_num ; i++){
		if(char_dat[i].st.account_id == account_id && char_dat[i].st.char_num < max_char_slot){
			sd->found_char[found_num++] = &char_dat[i];
			if(found_num == max_char_slot)
				break;
		}
	}
	for(i = found_num; i < max_char_slot ; i++) {
		sd->found_char[i] = NULL;
	}

	return found_num;
}

const struct mmo_chardata* char_txt_load(int char_id)
{
	int idx = char_id2idx(char_id);

	return (idx >= 0) ? &char_dat[idx] : NULL;
}

int char_txt_save_reg(int account_id,int char_id,int num,struct global_reg *reg)
{
	int idx = char_id2idx(char_id);

	if(idx >= 0) {
		if(char_dat[idx].st.account_id == account_id) {
			memcpy(&char_dat[idx].reg.global,reg,sizeof(char_dat[idx].reg.global));
			char_dat[idx].reg.global_num = num;
#ifdef TXT_JOURNAL
			if( char_journal_enable )
				journal_write( &char_journal, char_id, &char_dat[idx] );
#endif
			return 1;
		}
	}

	return 0;
}

int char_txt_save(struct mmo_charstatus *st)
{
	int idx = char_id2idx(st->char_id);

	if(idx >= 0) {
		if(char_dat[idx].st.account_id == st->account_id) {
			memcpy(&char_dat[idx].st,st,sizeof(struct mmo_charstatus));
#ifdef TXT_JOURNAL
			if( char_journal_enable )
				journal_write( &char_journal, st->char_id, &char_dat[idx] );
#endif
			return 1;
		}
	}
	return 0;
}

int char_txt_delete_sub(int char_id)
{
	int idx = char_id2idx(char_id);

	if(idx >= 0) {
		memset(&char_dat[idx],0,sizeof(char_dat[0]));
#ifdef TXT_JOURNAL
		if( char_journal_enable )
			journal_write( &char_journal, char_id, NULL );
#endif
		return 1;
	}
	return 0;
}

int char_txt_config_read_sub(const char* w1,const char* w2)
{
	if(strcmpi(w1,"char_txt")==0){
		strncpy(char_txt,w2,sizeof(char_txt) - 1);
	}
	else if(strcmpi(w1,"gm_account_filename")==0){
		strncpy(GM_account_filename,w2,sizeof(GM_account_filename) - 1);
	}
#ifdef TXT_JOURNAL
	else if(strcmpi(w1,"char_journal_enable")==0){
		char_journal_enable = atoi( w2 );
	}
	else if(strcmpi(w1,"char_journal_file")==0){
		strncpy( char_journal_file, w2, sizeof(char_journal_file) - 1 );
	}
	else if(strcmpi(w1,"char_journal_cache_interval")==0){
		char_journal_cache = atoi( w2 );
	}
#endif

	return 0;
}

const struct mmo_chardata* char_txt_nick2chardata(const char *char_name)
{
	int i;

	for(i=0;i<char_num;i++){
		if(strcmp(char_dat[i].st.name,char_name)==0) {
			return &char_dat[i];
		}
	}

	return NULL;
}

int char_txt_set_online(int char_id,int online)
{
	// nothing to do
	return 0;
}

static int compare_ranking_data(const void *a,const void *b);

static int char_txt_build_ranking(void)
{
	int i,j,k;
	int count[MAX_RANKING];
	struct Ranking_Data *rd[MAX_RANKING];

	if(char_num <= 0)
		return 0;

	memset(&ranking_data, 0, sizeof(ranking_data));
	memset(&count, 0, sizeof(count));

	for(i=0; i<MAX_RANKING; i++)
		rd[i] = (struct Ranking_Data *)aCalloc(char_num, sizeof(struct Ranking_Data));

	for(i=0; i<char_num; i++) {
		for(j=0; j<char_dat[i].reg.global_num; j++) {
			for(k=0; k<MAX_RANKING; k++) {
				if(strcmp(char_dat[i].reg.global[j].str, ranking_reg[k]) == 0 && char_dat[i].reg.global[j].value > 0) {
					strncpy(rd[k][count[k]].name, char_dat[i].st.name, 24);
					rd[k][count[k]].point   = char_dat[i].reg.global[j].value;
					rd[k][count[k]].char_id = char_dat[i].st.char_id;
					count[k]++;
				}
			}
		}
	}

	for(k=0; k<MAX_RANKING; k++) {
		if(count[k] > 0) {
			int max = (char_num < MAX_RANKER)? char_num: MAX_RANKER;
			qsort(rd[k], char_num, sizeof(struct Ranking_Data), compare_ranking_data);
			memcpy(&ranking_data[k], rd[k], max * sizeof(struct Ranking_Data));
		}
		aFree(rd[k]);
	}

	return 0;
}

#define char_make            char_txt_make
#define char_init            char_txt_init
#define char_sync            char_txt_sync
#define char_load            char_txt_load
#define char_save_reg        char_txt_save_reg
#define char_save            char_txt_save
#define char_final           char_txt_final
#define char_load_all        char_txt_load_all
#define char_delete_sub      char_txt_delete_sub
#define char_build_ranking   char_txt_build_ranking
#define char_config_read_sub char_txt_config_read_sub
#define char_set_online(id)  char_txt_set_online(id,1)
#define char_set_offline(id) char_txt_set_online(id,0)

#else /* TXT_ONLY */

static struct dbt *char_db_;
static unsigned short char_server_port = 3306;
static char char_server_ip[32]      = "127.0.0.1";
static char char_server_id[32]      = "ragnarok";
static char char_server_pw[32]      = "ragnarok";
static char char_server_db[32]      = "ragnarok";
static char char_server_charset[32] = "";

char char_db[256]                   = "char";
char reg_db[256]                    = "global_reg_value";
char friend_db[256]                 = "friend";
static char cart_db[256]            = "cart_inventory";
static char inventory_db[256]       = "inventory";
static char charlog_db[256]         = "charlog";
static char skill_db[256]           = "skill";
static char memo_db[256]            = "memo";
static char feel_db[256]            = "feel_info";
static char hotkey_db[256]          = "hotkey";

int char_sql_loaditem(struct item *item, int max, int id, int tableswitch)
{
	int i = 0;
	const char *tablename;
	const char *selectoption;
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;

	memset(item,0,sizeof(struct item) * max);

	switch (tableswitch) {
	case TABLE_INVENTORY:
		tablename    = inventory_db;
		selectoption = "char_id";
		break;
	case TABLE_CART:
		tablename    = cart_db;
		selectoption = "char_id";
		break;
	case TABLE_STORAGE:
		tablename    = storage_db_;
		selectoption = "account_id";
		break;
	case TABLE_GUILD_STORAGE:
		tablename    = guild_storage_db_;
		selectoption = "guild_id";
		break;
	default:
		printf("Invalid table name!\n");
		return 1;
	}

	sprintf(
		tmp_sql,"SELECT `id`, `nameid`, `amount`, `equip`, `identify`, `refine`, `attribute`, "
		"`card0`, `card1`, `card2`, `card3` FROM `%s` WHERE `%s`='%d'", tablename, selectoption, id
	);

	if (mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (select `%s`)- %s\n", tablename, mysql_error(&mysql_handle));
	}

	sql_res = mysql_store_result(&mysql_handle);
	if (sql_res) {
		for(i=0;(sql_row = mysql_fetch_row(sql_res)) && i < max;i++){
			item[i].id        = (unsigned int)atoi(sql_row[0]);
			item[i].nameid    = atoi(sql_row[1]);
			item[i].amount    = atoi(sql_row[2]);
			item[i].equip     = atoi(sql_row[3]);
			item[i].identify  = atoi(sql_row[4]);
			item[i].refine    = atoi(sql_row[5]);
			item[i].attribute = atoi(sql_row[6]);
			item[i].card[0]   = atoi(sql_row[7]);
			item[i].card[1]   = atoi(sql_row[8]);
			item[i].card[2]   = atoi(sql_row[9]);
			item[i].card[3]   = atoi(sql_row[10]);
		}
		mysql_free_result(sql_res);
	}

	return i;
}

int char_sql_saveitem(struct item *item, int max, int id, int tableswitch)
{
	int i;
	const char *tablename;
	const char *selectoption;
	char *p;
	char sep = ' ';

	switch (tableswitch) {
	case TABLE_INVENTORY:
		tablename    = inventory_db;
		selectoption = "char_id";
		break;
	case TABLE_CART:
		tablename    = cart_db;
		selectoption = "char_id";
		break;
	case TABLE_STORAGE:
		tablename    = storage_db_;
		selectoption = "account_id";
		break;
	case TABLE_GUILD_STORAGE:
		tablename    = guild_storage_db_;
		selectoption = "guild_id";
		break;
	default:
		printf("Invalid table name!\n");
		return 1;
	}

	// delete
	sprintf(tmp_sql,"DELETE FROM `%s` WHERE `%s`='%d'",tablename,selectoption,id);
	if(mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (DELETE `%s`)- %s\n", tablename, mysql_error(&mysql_handle));
	}

	p  = tmp_sql;
	p += sprintf(
		p,"INSERT INTO `%s`(`id`, `%s`, `nameid`, `amount`, `equip`, `identify`, `refine`, "
		"`attribute`, `card0`, `card1`, `card2`, `card3` ) VALUES",tablename,selectoption
	);

	for(i = 0 ; i < max ; i++) {
		if(item[i].nameid) {
			p += sprintf(
				p,"%c('%u','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d')",
				sep,item[i].id,id,item[i].nameid,item[i].amount,item[i].equip,item[i].identify,
				item[i].refine,item[i].attribute,item[i].card[0],item[i].card[1],
				item[i].card[2],item[i].card[3]
			);
			sep = ',';
		}
	}
	if(sep == ',') {
		if(mysql_query(&mysql_handle, tmp_sql)) {
			printf("DB server Error (INSERT `%s`)- %s\n", tablename, mysql_error(&mysql_handle));
		}
	}

	return 0;
}

static int char_sql_init(void)
{
	char_db_ = numdb_init();

	// DB connection initialized
	mysql_init(&mysql_handle);
	printf("Connect Character DB server");
	if(char_server_charset[0]) {
		printf(" (charset: %s)",char_server_charset);
	}
	printf("...\n");

	if(!mysql_real_connect(&mysql_handle, char_server_ip, char_server_id, char_server_pw,
		char_server_db, char_server_port, (char *)NULL, 0)
	) {
		printf("%s\n",mysql_error(&mysql_handle));
		exit(1);
	} else {
		printf("Connect Success! (Character Server)\n");
	}
	if(char_server_charset[0]) {
		sprintf(tmp_sql,"SET NAMES %s",char_server_charset);
		if (mysql_query(&mysql_handle, tmp_sql)) {
			printf("DB server Error (charset)- %s\n", mysql_error(&mysql_handle));
		}
	}

	return 1;
}

static void char_sql_sync(void)
{
	// nothing to do
}

const struct mmo_chardata* char_sql_load(int char_id)
{
	int i, n;
	struct mmo_chardata *p;
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;

	p = (struct mmo_chardata*)numdb_search(char_db_,char_id);
	if (p && p->st.char_id == char_id) {
		// 既にキャッシュが存在する
		return p;
	}

	// printf("Request load char (%6d)[",char_id);

	sprintf(tmp_sql, "SELECT * FROM `%s` WHERE `char_id` = '%d'",char_db, char_id);

	if (mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (select `%s`)- %s\n", char_db, mysql_error(&mysql_handle));
	}

	sql_res = mysql_store_result(&mysql_handle);

	if (sql_res) {
		// 0       1          2        3    4      5          6         7        8       9
		// char_id account_id char_num name class_ base_level job_level base_exp job_exp zeny
		// 10  11  12  13  14  15  16     17 18     19 20           21
		// str agi vit int dex luk max_hp hp max_sp sp status_point skill_point
		// 22     23    24     25          26       27       28     29   30         31
		// option karma manner die_counter party_id guild_id pet_id hair hair_color clothes_color
		// 32     33     34       35       36          37       38     39     40       41     42
		// weapon shield head_top head_mid head_bottom last_map last_x last_y save_map save_x save_y
		// 43         44           45           46      47     48
		// partner_id parent_id[0] parent_id[1] baby_id online homun_id

		sql_row = mysql_fetch_row(sql_res);
		if(sql_row == NULL) {
			// 見つからなくても正常
			mysql_free_result(sql_res);
			return NULL;
		}
		if(mysql_num_fields(sql_res) < 49) {
			// フィールド数が少ない場合はエラー
			printf("char_load: invalid number of fields!!\n");
			mysql_free_result(sql_res);
			exit(1);
		}
		if(p == NULL) {
			p = (struct mmo_chardata *)aMalloc(sizeof(struct mmo_chardata));
			numdb_insert(char_db_,char_id,p);
		}
		memset(p,0,sizeof(struct mmo_chardata));

		p->st.char_id       = char_id;
		p->st.account_id    = atoi(sql_row[ 1]);
		p->st.char_num      = atoi(sql_row[ 2]);
		strncpy(p->st.name, sql_row[3], 24);
		p->st.class_        = atoi(sql_row[ 4]);
		p->st.base_level    = atoi(sql_row[ 5]);
		p->st.job_level     = atoi(sql_row[ 6]);
		p->st.base_exp      = atoi(sql_row[ 7]);
		p->st.job_exp       = atoi(sql_row[ 8]);
		p->st.zeny          = atoi(sql_row[ 9]);
		p->st.str           = atoi(sql_row[10]);
		p->st.agi           = atoi(sql_row[11]);
		p->st.vit           = atoi(sql_row[12]);
		p->st.int_          = atoi(sql_row[13]);
		p->st.dex           = atoi(sql_row[14]);
		p->st.luk           = atoi(sql_row[15]);
		p->st.max_hp        = atoi(sql_row[16]);
		p->st.hp            = atoi(sql_row[17]);
		p->st.max_sp        = atoi(sql_row[18]);
		p->st.sp            = atoi(sql_row[19]);
		p->st.status_point  = atoi(sql_row[20]);
		p->st.skill_point   = atoi(sql_row[21]);
		p->st.option        = (unsigned int)atoi(sql_row[22]);
		p->st.karma         = atoi(sql_row[23]);
		p->st.manner        = atoi(sql_row[24]);
		p->st.die_counter   = atoi(sql_row[25]);
		p->st.party_id      = atoi(sql_row[26]);
		p->st.guild_id      = atoi(sql_row[27]);
		p->st.pet_id        = atoi(sql_row[28]);
		p->st.homun_id      = atoi(sql_row[48]);
		p->st.hair          = atoi(sql_row[29]);
		p->st.hair_color    = atoi(sql_row[30]);
		p->st.clothes_color = atoi(sql_row[31]);
		p->st.weapon        = atoi(sql_row[32]);
		p->st.shield        = atoi(sql_row[33]);
		p->st.head_top      = atoi(sql_row[34]);
		p->st.head_mid      = atoi(sql_row[35]);
		p->st.head_bottom   = atoi(sql_row[36]);
		strncpy(p->st.last_point.map,sql_row[37],24);
		p->st.last_point.x  = atoi(sql_row[38]);
		p->st.last_point.y  = atoi(sql_row[39]);
		strncpy(p->st.save_point.map,sql_row[40],24);
		p->st.save_point.x  = atoi(sql_row[41]);
		p->st.save_point.y  = atoi(sql_row[42]);
		p->st.partner_id    = atoi(sql_row[43]);
		p->st.parent_id[0]  = atoi(sql_row[44]);
		p->st.parent_id[1]  = atoi(sql_row[45]);
		p->st.baby_id       = atoi(sql_row[46]);

		// force \0 terminal
		p->st.name[23]           = '\0';
		p->st.last_point.map[23] = '\0';
		p->st.save_point.map[23] = '\0';

		// free mysql result.
		mysql_free_result(sql_res);
	} else {
		printf("char - failed\n");	// Error?! ERRRRRR WHAT THAT SAY!?
		return NULL;
	}
	// printf("char ");

	// read memo data
	// `memo` (`memo_id`,`char_id`,`map`,`x`,`y`)
	sprintf(tmp_sql, "SELECT `map`,`x`,`y` FROM `%s` WHERE `char_id`='%d'",memo_db, char_id); // TBR
	if (mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (select `%s`)- %s\n", memo_db, mysql_error(&mysql_handle));
	}
	sql_res = mysql_store_result(&mysql_handle);

	if (sql_res) {
		for(i = 0; i < MAX_PORTAL_MEMO && (sql_row = mysql_fetch_row(sql_res)); i++) {
			strncpy(p->st.memo_point[i].map, sql_row[0], 24);
			p->st.memo_point[i].map[23] = '\0';	// force \0 terminal
			p->st.memo_point[i].x       = atoi(sql_row[1]);
			p->st.memo_point[i].y       = atoi(sql_row[2]);
		}
		mysql_free_result(sql_res);
	}
	// printf("memo ");

	// read inventory
	char_sql_loaditem(p->st.inventory,MAX_INVENTORY,p->st.char_id,TABLE_INVENTORY);
	// printf("inventory ");

	// read cart.
	char_sql_loaditem(p->st.cart,MAX_CART,p->st.char_id,TABLE_CART);
	// printf("cart ");

	// read skill
	// `skill` (`char_id`, `id`, `lv`)
	sprintf(tmp_sql, "SELECT `id`, `lv` FROM `%s` WHERE `char_id`='%d'",skill_db, char_id); // TBR
	if (mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (select `%s`)- %s\n", skill_db, mysql_error(&mysql_handle));
	}
	sql_res = mysql_store_result(&mysql_handle);
	if (sql_res) {
		for(i=0;(sql_row = mysql_fetch_row(sql_res));i++){
			n = atoi(sql_row[0]);
			if(n >= 0 && n < MAX_SKILL) {
				p->st.skill[n].id = n;
				p->st.skill[n].lv = atoi(sql_row[1]);
			}
		}
		mysql_free_result(sql_res);
	}
	// printf("skill ");

	// global_reg
	// `global_reg_value` (`char_id`, `str`, `value`)
	sprintf(tmp_sql, "SELECT `str`, `value` FROM `%s` WHERE `type`=3 AND `char_id`='%d'",reg_db, char_id); // TBR
	if (mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (select `%s`)- %s\n", reg_db, mysql_error(&mysql_handle));
	}
	i = 0;
	sql_res = mysql_store_result(&mysql_handle);
	if (sql_res) {
		for(i=0; (sql_row = mysql_fetch_row(sql_res));i++){
			if(i < GLOBAL_REG_NUM) {
				strncpy(p->reg.global[i].str, sql_row[0], 32);
				p->reg.global[i].str[31] = '\0';	// force \0 terminal
				p->reg.global[i].value   = atoi(sql_row[1]);
			} else {
				printf("char_load %d: couldn't load %s (GLOBAL_REG_NUM = %d)\a\n", p->st.char_id, sql_row[0], GLOBAL_REG_NUM);
			}
		}
		mysql_free_result(sql_res);
	}
	p->reg.global_num = (i < GLOBAL_REG_NUM)? i: GLOBAL_REG_NUM;
	// printf("global_reg ");

	// friend list
	p->st.friend_num = 0;
	sprintf( tmp_sql, "SELECT `id1`, `id2`, `name` FROM `%s` WHERE `char_id`='%d'", friend_db, char_id );
	if (mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (select `%s`)- %s\n", friend_db, mysql_error(&mysql_handle));
	}
	sql_res = mysql_store_result( &mysql_handle );
	if( sql_res )
	{
		for( i=0; i < MAX_FRIEND && (sql_row = mysql_fetch_row(sql_res)); i++ )
		{
			p->st.friend_data[i].account_id = atoi( sql_row[0] );
			p->st.friend_data[i].char_id = atoi( sql_row[1] );
			strncpy( p->st.friend_data[i].name, sql_row[2], 24 );
			p->st.friend_data[i].name[23] = '\0';	// force \0 terminal
		}
		mysql_free_result( sql_res );
		p->st.friend_num = (i < MAX_FRIEND)? i: MAX_FRIEND;
	}
	// friend list のチェックと訂正
	for(i=0; i<p->st.friend_num; i++ )
	{
		sprintf( tmp_sql, "SELECT `id1`, `name` FROM `%s` WHERE `char_id`='%d' AND `id2`='%d'", friend_db, p->st.friend_data[i].char_id, p->st.char_id );
		if (mysql_query(&mysql_handle, tmp_sql)) {
			printf("DB server Error (select `%s` / check )- %s\n", friend_db, mysql_error(&mysql_handle));
		}
		sql_res = mysql_store_result( &mysql_handle );
		if( !sql_res ) {
			// 相手に存在しないので、友達リストから削除する
			sprintf( tmp_sql, "DELETE FROM `%s` WHERE `char_id`='%d' AND `id2`='%d'", friend_db, p->st.char_id, p->st.friend_data[i].char_id );
			if (mysql_query(&mysql_handle, tmp_sql)) {
				printf("DB server Error (delete `%s` / correct)- %s\n", friend_db, mysql_error(&mysql_handle));
			}
			p->st.friend_num--;
			memmove( &p->st.friend_data[i], &p->st.friend_data[i+1], sizeof(p->st.friend_data[0])* (p->st.friend_num - i ) );
			i--;
			printf("*friend_data_correct*\n");
		} else {
			mysql_free_result( sql_res );
		}
	}
	// printf("friend ");

	// feel_info
	// `feel_info` (`feel_id`,`char_id`,`map`,`lv`)
	sprintf(tmp_sql, "SELECT `map`,`lv` FROM `%s` WHERE `char_id`='%d'",feel_db, char_id);
	if (mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (select `%s`)- %s\n", feel_db, mysql_error(&mysql_handle));
	}
	sql_res = mysql_store_result(&mysql_handle);

	if (sql_res) {
		for(i = 0; (sql_row = mysql_fetch_row(sql_res)); i++) {
			n = atoi(sql_row[1]);
			if(n >= 0 && n < 3) {
				strncpy(p->st.feel_map[n], sql_row[0], 24);
				p->st.feel_map[n][23] = '\0';	// force \0 terminal
			}
		}
		mysql_free_result(sql_res);
	}

	// hotkey
	// `hotkey` (`char_id`,`key`,`type`,`id`,`lv`)
	sprintf(tmp_sql, "SELECT `key`, `type`, `id`, `lv` FROM `%s` WHERE `char_id`='%d'", hotkey_db, char_id);
	if (mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (select `%s`)- %s\n", hotkey_db, mysql_error(&mysql_handle));
	}
	sql_res = mysql_store_result(&mysql_handle);

	if (sql_res) {
		for(i = 0; (sql_row = mysql_fetch_row(sql_res)); i++) {
			n = atoi(sql_row[0]);
			if(n >= 0 && n < MAX_HOTKEYS) {
				p->st.hotkey[n].type = (char)atoi(sql_row[1]);
				p->st.hotkey[n].id   = atoi(sql_row[2]);
				p->st.hotkey[n].lv   = (unsigned short)atoi(sql_row[3]);
			}
		}
		mysql_free_result(sql_res);
	}

	// printf("]\n");	// ok. all data load successfuly!

	return p;
}

int char_sql_save_reg(int account_id,int char_id,int num,struct global_reg *reg)
{
	const struct mmo_chardata *cd = char_sql_load(char_id);
	char buf[256];
	int i;

	if(cd == NULL || cd->st.account_id != account_id)
		return 0;

	//printf("- Save global_reg_value data to MySQL!\n");
	// `global_reg_value` (`char_id`, `str`, `value`)
	sprintf(tmp_sql,"DELETE FROM `%s` WHERE `type`=3 AND `char_id`='%d'",reg_db, char_id);
	if (mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (delete `%s`)- %s\n", reg_db, mysql_error(&mysql_handle));
	}

	// insert here.
	for(i=0;i<num;i++){
		if (reg[i].str[0] && reg[i].value != 0) {
			sprintf(
				tmp_sql,"INSERT INTO `%s` (`char_id`, `str`, `value`) VALUES ('%d', '%s', '%d')",
				reg_db, char_id, strecpy(buf,reg[i].str), reg[i].value
			);
			if(mysql_query(&mysql_handle, tmp_sql)) {
				printf("DB server Error (insert `%s`)- %s\n", reg_db, mysql_error(&mysql_handle));
			}
		}
	}

	{
		struct mmo_chardata *cd2 = (struct mmo_chardata *)numdb_search(char_db_,char_id);
		if(cd2) {
			memcpy(&cd2->reg.global,reg,sizeof(cd2->reg.global));
			cd2->reg.global_num = num;
		}
	}

	return 0;
}

#define UPDATE_NUM(val,sql) \
	if(st1->val != st2->val) {\
		p += sprintf(p,"%c`"sql"` = '%d'",sep,st2->val); sep = ',';\
	}
#define UPDATE_UNUM(val,sql) \
	if(st1->val != st2->val) {\
		p += sprintf(p,"%c`"sql"` = '%u'",sep,st2->val); sep = ',';\
	}
#define UPDATE_STR(val,sql) \
	if(strcmp(st1->val,st2->val)) {\
		p += sprintf(p,"%c`"sql"` = '%s'",sep,strecpy(buf,st2->val)); sep = ',';\
	}

int char_sql_save(struct mmo_charstatus *st2)
{
	const struct mmo_chardata *cd = char_sql_load(st2->char_id);
	const struct mmo_charstatus *st1;
	char sep = ' ';
	char buf[256];
	char *p = tmp_sql;
	int  i;

	if(cd == NULL)
		return 0;
	st1 = &cd->st;
	// printf("Request save char (%6d)[",st2->char_id);

	// basic information
	p += sprintf(p,"UPDATE `%s` SET",char_db);

	UPDATE_NUM(account_id    ,"account_id");
	UPDATE_NUM(char_num      ,"char_num");
	UPDATE_STR(name          ,"name");
	UPDATE_NUM(class_        ,"class");
	UPDATE_NUM(base_level    ,"base_level");
	UPDATE_NUM(job_level     ,"job_level");
	UPDATE_NUM(base_exp      ,"base_exp");
	UPDATE_NUM(job_exp       ,"job_exp");
	UPDATE_NUM(zeny          ,"zeny");
	UPDATE_NUM(str           ,"str");
	UPDATE_NUM(agi           ,"agi");
	UPDATE_NUM(vit           ,"vit");
	UPDATE_NUM(int_          ,"int");
	UPDATE_NUM(dex           ,"dex");
	UPDATE_NUM(luk           ,"luk");
	UPDATE_NUM(max_hp        ,"max_hp");
	UPDATE_NUM(hp            ,"hp");
	UPDATE_NUM(max_sp        ,"max_sp");
	UPDATE_NUM(sp            ,"sp");
	UPDATE_NUM(status_point  ,"status_point");
	UPDATE_NUM(skill_point   ,"skill_point");
	UPDATE_UNUM(option       ,"option");
	UPDATE_NUM(karma         ,"karma");
	UPDATE_NUM(manner        ,"manner");
	UPDATE_NUM(die_counter   ,"die_counter");
	UPDATE_NUM(party_id      ,"party_id");
	UPDATE_NUM(guild_id      ,"guild_id");
	UPDATE_NUM(pet_id        ,"pet_id");
	UPDATE_NUM(hair          ,"hair");
	UPDATE_NUM(hair_color    ,"hair_color");
	UPDATE_NUM(clothes_color ,"clothes_color");
	UPDATE_NUM(weapon        ,"weapon");
	UPDATE_NUM(shield        ,"shield");
	UPDATE_NUM(head_top      ,"head_top");
	UPDATE_NUM(head_mid      ,"head_mid");
	UPDATE_NUM(head_bottom   ,"head_bottom");
	UPDATE_STR(last_point.map,"last_map");
	UPDATE_NUM(last_point.x  ,"last_x");
	UPDATE_NUM(last_point.y  ,"last_y");
	UPDATE_STR(save_point.map,"save_map");
	UPDATE_NUM(save_point.x  ,"save_x");
	UPDATE_NUM(save_point.y  ,"save_y");
	UPDATE_NUM(partner_id    ,"partner_id");
	UPDATE_NUM(parent_id[0]  ,"parent_id");
	UPDATE_NUM(parent_id[1]  ,"parent_id2");
	UPDATE_NUM(baby_id       ,"baby_id");
	UPDATE_NUM(homun_id      ,"homun_id");

	if(sep == ',') {
		sprintf(p," WHERE `char_id` = '%d'",st2->char_id);
		if (mysql_query(&mysql_handle, tmp_sql)) {
			printf("DB server Error (update `%s`)- %s\n", char_db, mysql_error(&mysql_handle));
		}
		// printf("char ");
	}

	// memo
	if (memcmp(st1->memo_point,st2->memo_point,sizeof(st1->memo_point))) {
		// `memo` (`memo_id`,`char_id`,`map`,`x`,`y`)
		sprintf(tmp_sql,"DELETE FROM `%s` WHERE `char_id`='%d'",memo_db, st2->char_id);
		if(mysql_query(&mysql_handle, tmp_sql)) {
			printf("DB server Error (delete `%s`)- %s\n", memo_db, mysql_error(&mysql_handle));
		}

		// insert here.
		for(i = 0; i < MAX_PORTAL_MEMO; i++) {
			if(st2->memo_point[i].map[0]) {
				sprintf(
					tmp_sql,"INSERT INTO `%s`(`char_id`,`map`,`x`,`y`) VALUES ('%d', '%s', '%d', '%d')",
					memo_db, st2->char_id, strecpy(buf,st2->memo_point[i].map), st2->memo_point[i].x, st2->memo_point[i].y
				);
				if(mysql_query(&mysql_handle, tmp_sql))
					printf("DB server Error (insert `%s`)- %s\n", memo_db, mysql_error(&mysql_handle));
			}
		}
		// printf("memo ");
	}

	// inventory
	if (memcmp(st1->inventory, st2->inventory, sizeof(st1->inventory))) {
		char_sql_saveitem(st2->inventory,MAX_INVENTORY,st2->char_id,TABLE_INVENTORY);
		// printf("inventory ");
	}

	// cart
	if (memcmp(st1->cart, st2->cart, sizeof(st1->cart))) {
		char_sql_saveitem(st2->cart,MAX_CART,st2->char_id,TABLE_CART);
		// printf("cart ");
	}

	// skill
	if(memcmp(st1->skill,st2->skill,sizeof(st1->skill))) {
		unsigned short sk_lv;
		//printf("- Save skill data to MySQL!\n");
		// `skill` (`char_id`, `id`, `lv`)
		sprintf(tmp_sql,"DELETE FROM `%s` WHERE `char_id`='%d'",skill_db, st2->char_id);
		if(mysql_query(&mysql_handle, tmp_sql)) {
			printf("DB server Error (delete `%s`)- %s\n", skill_db, mysql_error(&mysql_handle));
		}
		//printf("- Insert skill \n");
		// insert here.
		p  = tmp_sql;
		p += sprintf(p,"INSERT INTO `%s`(`char_id`, `id`, `lv`) VALUES",skill_db);
		sep = ' ';
		for(i=0;i<MAX_SKILL;i++){
			sk_lv = (st2->skill[i].flag==0)? st2->skill[i].lv: st2->skill[i].flag-2;
			if(st2->skill[i].id && st2->skill[i].flag!=1){
				p += sprintf(p,"%c('%d','%d','%d')",sep,st2->char_id, st2->skill[i].id, sk_lv);
				sep = ',';
			}
		}
		if(sep == ',') {
			if(mysql_query(&mysql_handle, tmp_sql)) {
				printf("DB server Error (insert `%s`)- %s\n", skill_db, mysql_error(&mysql_handle));
			}
		}
		// printf("skill ");
	}

	// friend
	if( st1->friend_num != st2->friend_num ||
	    memcmp(st1->friend_data, st2->friend_data, sizeof(st1->friend_data)) != 0 )
	{
		sprintf( tmp_sql, "DELETE FROM `%s` WHERE `char_id`='%d'", friend_db, st2->char_id );
		if (mysql_query(&mysql_handle, tmp_sql)) {
			printf("DB server Error (delete `%s`)- %s\n", friend_db, mysql_error(&mysql_handle));
		}

		for( i=0; i<st2->friend_num; i++ )
		{
			sprintf( tmp_sql, "INSERT INTO `%s` (`char_id`, `id1`, `id2`, `name`) VALUES ('%d', '%d', '%d', '%s')",
				friend_db, st2->char_id, st2->friend_data[i].account_id, st2->friend_data[i].char_id,
				strecpy( buf, st2->friend_data[i].name ) );
			if(mysql_query(&mysql_handle, tmp_sql)) {
				printf("DB server Error (insert `%s`)- %s\n", friend_db, mysql_error(&mysql_handle));
			}
		}
		// printf("friend ");
	}

	// feel_info
	if (memcmp(st1->feel_map,st2->feel_map,sizeof(st1->feel_map))) {
		// `feel_info` (`feel_id`,`char_id`,`map`,`lv`)
		sprintf(tmp_sql,"DELETE FROM `%s` WHERE `char_id`='%d'",feel_db, st2->char_id);
		if(mysql_query(&mysql_handle, tmp_sql)) {
			printf("DB server Error (delete `%s`)- %s\n", feel_db, mysql_error(&mysql_handle));
		}

		// insert here.
		for(i = 0; i < 3; i++) {
			if(st2->feel_map[i][0]) {
				sprintf(
					tmp_sql,"INSERT INTO `%s`(`char_id`,`map`,`lv`) VALUES ('%d', '%s', '%d')",
					feel_db, st2->char_id, strecpy(buf,st2->feel_map[i]), i
				);
				if(mysql_query(&mysql_handle, tmp_sql))
					printf("DB server Error (insert `%s`)- %s\n", feel_db, mysql_error(&mysql_handle));
			}
		}
	}

	// hotkey
	if (memcmp(st1->hotkey,st2->hotkey,sizeof(st1->hotkey))) {
		// `hotkey` (`char_id`,`key`,`type`,`id`,`lv`)
		sprintf(tmp_sql,"DELETE FROM `%s` WHERE `char_id`='%d'",hotkey_db, st2->char_id);
		if(mysql_query(&mysql_handle, tmp_sql)) {
			printf("DB server Error (delete `%s`)- %s\n", hotkey_db, mysql_error(&mysql_handle));
		}

		// insert here.
		for(i = 0; i < MAX_HOTKEYS; i++) {
			if(st2->hotkey[i].id > 0) {
				sprintf(
					tmp_sql,"INSERT INTO `%s`(`char_id`,`key`,`type`,`id`,`lv`) VALUES ('%d', '%d', '%d', '%d', '%d')",
					hotkey_db, st2->char_id, i, st2->hotkey[i].type, st2->hotkey[i].id, st2->hotkey[i].lv
				);
				if(mysql_query(&mysql_handle, tmp_sql))
					printf("DB server Error (insert `%s`)- %s\n", hotkey_db, mysql_error(&mysql_handle));
			}
		}
	}

	// printf("]\n");
	{
		struct mmo_chardata *cd2 = (struct mmo_chardata *)numdb_search(char_db_,st2->char_id);
		if(cd2)
			memcpy(&cd2->st,st2,sizeof(struct mmo_charstatus));
	}

	return 0;
}

const struct mmo_chardata* char_sql_make(struct char_session_data *sd,unsigned char *dat,int *flag)
{
	int  i;
	int  char_id;
	char name[24], buf[256];
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;

	memset(name, 0, sizeof(name));
	for(i=0;i<24 && dat[i];i++){
		if(dat[i]<0x20 || dat[i]==0x7f)
		// MySQLのバグをAuriga側で抑制
		//if(dat[i]<0x20 || dat[i]==0x7f || dat[i]>=0xfd)
			return NULL;
		name[i] = dat[i];
	}
	name[23] = '\0';	// force \0 terminal

	for(i=24;i<=29;i++) {
		if(dat[i] > 9) return NULL;
	}
	if(dat[30] >= max_char_slot){
		*flag = 0x02;
		printf("make new char over slot!! (%d / %d)\n",dat[30]+1,max_char_slot);
		return NULL;
	}
	if(dat[24]+dat[25]+dat[26]+dat[27]+dat[28]+dat[29]>5*6 || dat[30]>=9 || dat[33]==0 || dat[33]>=24 || dat[31]>=9)
	{
		char_log(
			"make new char error %d %s %d,%d,%d,%d,%d,%d %d,%d",
			dat[30],name,dat[24],dat[25],dat[26],dat[27],dat[28],dat[29],dat[33],dat[31]
		);
		return NULL;
	}
	char_log("make new char %d %s",dat[30],name);

	// 同一アカウントID、同一キャラスロットチェック
	sprintf(
		tmp_sql,
		"SELECT COUNT(*) FROM `%s` WHERE `account_id` = '%d' AND `char_num` = '%d'",
		char_db, sd->account_id, dat[30]
	);
	if (mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (select `%s`)- %s\n", char_db, mysql_error(&mysql_handle));
		return NULL;
	}
	sql_res = mysql_store_result(&mysql_handle);
	if (!sql_res) return NULL;
	sql_row = mysql_fetch_row(sql_res);
	i = atoi(sql_row[0]);
	mysql_free_result(sql_res);
	if(i) return NULL;

	// 同名チェック
	sprintf(tmp_sql, "SELECT `name` FROM `%s` WHERE `name` = '%s'", char_db, strecpy(buf,name));
	if (mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (select `%s`)- %s\n", char_db, mysql_error(&mysql_handle));
		return NULL;
	}
	sql_res = mysql_store_result(&mysql_handle);
	if(sql_res) {
		while( (sql_row = mysql_fetch_row(sql_res)) ) {
			if(strncmp(name, sql_row[0], 24) == 0) {
				mysql_free_result(sql_res);
				return NULL;
			}
		}
		mysql_free_result(sql_res);
	}

	// Insert the char to the 'chardb' ^^
	sprintf(
		tmp_sql,
		"INSERT INTO `%s` (`account_id`,`char_num`,`name`,`zeny`,`str`,`agi`,`vit`,`int`,"
		"`dex`,`luk`,`max_hp`,`hp`,`max_sp`,`sp`,`hair`,`hair_color`,`last_map`,`last_x`,"
		"`last_y`,`save_map`,`save_x`,`save_y`) VALUES ('%d','%d','%s','%d','%d','%d','%d',"
		"'%d','%d','%d','%d','%d','%d','%d','%d','%d','%s','%d','%d','%s','%d','%d')",
		char_db,sd->account_id,dat[30],strecpy(buf,name),start_zeny,dat[24],dat[25],dat[26],
		dat[27],dat[28],dat[29],40 * (100 + dat[26])/100,40 * (100 + dat[26])/100,
		11 * (100 + dat[27])/100,11 * (100 + dat[27])/100,dat[33],dat[31],start_point.map,
		start_point.x, start_point.y, start_point.map, start_point.x,start_point.y
	);
	if(mysql_query(&mysql_handle, tmp_sql)){
		printf("failed (insert in `%s`), SQL error: %s\n", char_db, mysql_error(&mysql_handle));
		return NULL; // No, stop the procedure!
	}

	// Now we need the charid from sql!
	char_id = (int)mysql_insert_id(&mysql_handle);

	// Give the char the default items
	// knife
	if(start_weapon > 0) {
		sprintf(
			tmp_sql,"INSERT INTO `%s` (`id`, `char_id`, `nameid`, `amount`, `equip`, `identify`) "
			"VALUES (1, '%d', '%d', '%d', '%d', '%d')",inventory_db, char_id, start_weapon,1,0x02,1
		);
		if (mysql_query(&mysql_handle, tmp_sql)){
			printf("fail (insert in inventory ID %d), SQL error: %s\n", start_weapon, mysql_error(&mysql_handle));
			return NULL;
		}
	}
	// cotton shirt
	if(start_armor > 0) {
		sprintf(tmp_sql,"INSERT INTO `%s` (`id`, `char_id`, `nameid`, `amount`, `equip`, `identify`) "
			"VALUES (2, '%d', '%d', '%d', '%d', '%d')", inventory_db, char_id, start_armor,1,0x10,1
		);
		if (mysql_query(&mysql_handle, tmp_sql)){
			printf("fail (insert in inventory ID %d), SQL error: %s\n", start_armor, mysql_error(&mysql_handle));
			return NULL; // end....
		}
	}

	printf("success, aid: %d, cid: %d, slot: %d, name: %s\n", sd->account_id, char_id, dat[30], name);

	return char_sql_load(char_id);
}

int char_sql_load_all(struct char_session_data* sd,int account_id)
{
	int i,j;
	int found_id[9];
	int found_num = 0;
	const struct mmo_chardata *cd;
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;

	memset(&found_id,0,sizeof(found_id));

	// search char.
	sprintf(tmp_sql, "SELECT `char_id` FROM `%s` WHERE `account_id` = '%d'",char_db, account_id);
	if (mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (select `%s`)- %s\n", char_db, mysql_error(&mysql_handle));
		return 0;
	}
	sql_res = mysql_store_result(&mysql_handle);
	if (sql_res) {
		while((sql_row = mysql_fetch_row(sql_res))) {
			found_id[found_num++] = atoi(sql_row[0]);
			if(found_num == sizeof(found_id)/sizeof(found_id[0]))
				break;
		}
		mysql_free_result(sql_res);
	}
	j = 0;
	for(i = 0;i < found_num ; i++) {
		cd = char_sql_load(found_id[i]);
		if(cd && cd->st.char_num < max_char_slot) {
			sd->found_char[j++] = cd;
			if(j == max_char_slot)
				break;
		}
	}
	for(i = j; i < max_char_slot; i++) {
		sd->found_char[i] = NULL;
	}

	return j;
}

int char_sql_delete_sub(int char_id)
{
	struct mmo_chardata *p = (struct mmo_chardata *)numdb_search(char_db_,char_id);

	if(p) {
		numdb_erase(char_db_,char_id);
		aFree(p);
	}

	// char
	sprintf(tmp_sql,"DELETE FROM `%s` WHERE `char_id`='%d'",char_db, char_id);
	if(mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (delete `%s`)- %s\n", char_db, mysql_error(&mysql_handle));
	}

	// memo
	sprintf(tmp_sql,"DELETE FROM `%s` WHERE `char_id`='%d'",memo_db, char_id);
	if(mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (delete `%s`)- %s\n", memo_db, mysql_error(&mysql_handle));
	}

	// inventory
	sprintf(tmp_sql,"DELETE FROM `%s` WHERE `char_id`='%d'",inventory_db, char_id);
	if(mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (delete `%s`)- %s\n", inventory_db, mysql_error(&mysql_handle));
	}

	// cart
	sprintf(tmp_sql,"DELETE FROM `%s` WHERE `char_id`='%d'",cart_db, char_id);
	if(mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (delete `%s`)- %s\n", cart_db, mysql_error(&mysql_handle));
	}

	// skill
	sprintf(tmp_sql,"DELETE FROM `%s` WHERE `char_id`='%d'",skill_db, char_id);
	if(mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (delete `%s`)- %s\n", skill_db, mysql_error(&mysql_handle));
	}

	// global_reg
	sprintf(tmp_sql,"DELETE FROM `%s` WHERE `type`=3 AND `char_id`='%d'",reg_db, char_id);
	if (mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (delete `%s`)- %s\n", reg_db, mysql_error(&mysql_handle));
	}

	// friend
	sprintf(tmp_sql, "DELETE FROM `%s` WHERE `char_id`='%d'", friend_db, char_id);
	if (mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (delete `%s`)- %s\n", friend_db, mysql_error(&mysql_handle));
	}

	// feel_info
	sprintf(tmp_sql,"DELETE FROM `%s` WHERE `char_id`='%d'",feel_db, char_id);
	if(mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (delete `%s`)- %s\n", feel_db, mysql_error(&mysql_handle));
	}

	return 1;
}

static int char_db_final(void *key,void *data,va_list ap)
{
	struct mmo_chardata *p = (struct mmo_chardata *)data;

	aFree(p);

	return 0;
}

void char_sql_final(void)
{
	mysql_close(&mysql_handle);
	printf("close DB connect....\n");

	numdb_final(char_db_,char_db_final);

	return;
}

int char_sql_config_read_sub(const char* w1,const char* w2)
{
	if(strcmpi(w1,"char_server_ip")==0){
		strncpy(char_server_ip, w2, sizeof(char_server_ip) - 1);
	}
	else if(strcmpi(w1,"char_server_port")==0){
		char_server_port = (unsigned short)atoi(w2);
	}
	else if(strcmpi(w1,"char_server_id")==0){
		strncpy(char_server_id, w2, sizeof(char_server_id) - 1);
	}
	else if(strcmpi(w1,"char_server_pw")==0){
		strncpy(char_server_pw, w2, sizeof(char_server_pw) - 1);
	}
	else if(strcmpi(w1,"char_server_db")==0){
		strncpy(char_server_db, w2, sizeof(char_server_db) - 1);
	}
	else if(strcmpi(w1,"char_server_charset")==0){
		strncpy(char_server_charset, w2, sizeof(char_server_charset) - 1);
	}

	return 0;
}

const struct mmo_chardata* char_sql_nick2chardata(const char *char_name)
{
	const struct mmo_chardata *cd = NULL;
	char buf[64];
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;

	sprintf(tmp_sql,"SELECT `char_id`,`name` FROM `%s` WHERE `name` = '%s'",char_db,strecpy(buf,char_name));
	if(mysql_query(&mysql_handle, tmp_sql)){
		printf("DB server Error (select `%s`) : %s\n", char_db, mysql_error(&mysql_handle));
	}
	sql_res = mysql_store_result(&mysql_handle);
	if(sql_res){
		while( (sql_row = mysql_fetch_row(sql_res)) ) {
			if(strcmp(char_name, sql_row[1]) == 0) {
				int char_id = atoi(sql_row[0]);
				if(char_id > 0) {
					cd = char_sql_load(char_id);
				}
				break;
			}
		}
		mysql_free_result(sql_res);
	}

	return cd;
}

int char_sql_set_online(int char_id,int online)
{
	char *p = tmp_sql;

	p += sprintf(p, "UPDATE `%s` SET `online` = '%d' WHERE ", char_db, online);
	if(char_id > 0)
		sprintf(p, "`char_id` = '%d'", char_id);
	else
		sprintf(p, "`online` = '%d'", online^1);

	if(mysql_query(&mysql_handle, tmp_sql)) {
		printf("DB server Error (update set_online)- %s\n", mysql_error(&mysql_handle));
	}
	return 0;
}

static int char_sql_build_ranking(void)
{
	int i,j,max;
	char buf[128];
	MYSQL_RES* sql_res;
	MYSQL_ROW  sql_row = NULL;

	memset(&ranking_data, 0, sizeof(ranking_data));

	for(i=0; i<MAX_RANKING; i++) {
		max = 0;
		sprintf(
			tmp_sql,
			"SELECT `value`,`char_id` FROM `%s` WHERE `type` = 3 AND `str` = '%s' AND `value` > 0 ORDER BY `value` DESC LIMIT 0,%d",
			reg_db, strecpy(buf,ranking_reg[i]), MAX_RANKER
		);
		if (mysql_query(&mysql_handle, tmp_sql)) {
			printf("DB server Error (select `%s`)- %s\n", reg_db, mysql_error(&mysql_handle));
		}
		sql_res = mysql_store_result(&mysql_handle);

		if(sql_res) {
			for(j=0; j<MAX_RANKER && (sql_row = mysql_fetch_row(sql_res)); j++) {
				ranking_data[i][j].point   = atoi(sql_row[0]);
				ranking_data[i][j].char_id = atoi(sql_row[1]);
			}
			mysql_free_result(sql_res);
			max = j;
		}

		// キャラ名の補完
		for(j=0; j<max; j++) {
			sprintf(tmp_sql, "SELECT `name` FROM `%s` WHERE `char_id` = '%d'", char_db, ranking_data[i][j].char_id);
			if (mysql_query(&mysql_handle, tmp_sql)) {
				printf("DB server Error (select `%s`)- %s\n", char_db, mysql_error(&mysql_handle));
			}
			sql_res = mysql_store_result(&mysql_handle);

			if(sql_res && (sql_row = mysql_fetch_row(sql_res))) {
				strncpy(ranking_data[i][j].name, sql_row[0], 24);
				ranking_data[i][j].name[23] = '\0';	// force \0 terminal
				mysql_free_result(sql_res);
			} else {
				printf("char_build_ranking: char_name not found in %s (ID = %d, Rank = %d)\n", ranking_reg[i], ranking_data[i][j].char_id, j+1);
				memcpy(ranking_data[i][j].name, unknown_char_name, 24);
				if(sql_res)
					mysql_free_result(sql_res);
			}
		}
	}

	return 0;
}

#define char_make            char_sql_make
#define char_init            char_sql_init
#define char_sync            char_sql_sync
#define char_load            char_sql_load
#define char_save_reg        char_sql_save_reg
#define char_save            char_sql_save
#define char_final           char_sql_final
#define char_load_all        char_sql_load_all
#define char_delete_sub      char_sql_delete_sub
#define char_build_ranking   char_sql_build_ranking
#define char_config_read_sub char_sql_config_read_sub
#define char_set_online(id)  char_sql_set_online(id,1)
#define char_set_offline(id) char_sql_set_online(id,0)

#endif /* TXT_ONLY */

static struct dbt *gm_account_db;

int isGM(int account_id)
{
	struct gm_account *p = (struct gm_account *)numdb_search(gm_account_db,account_id);

	if( p == NULL)
		return 0;

	return p->level;
}

static void read_gm_account(void)
{
	char line[8192];
	struct gm_account *p;
	FILE *fp;
	int c, l;
	int account_id, level;
	int i;
	int range, start_range, end_range;

	gm_account_db = numdb_init();

	if ((fp = fopen(GM_account_filename, "r")) == NULL) {
		printf("File not found: %s.\n", GM_account_filename);
		return;
	}

	line[sizeof(line)-1] = '\0';
	c = 0;
	l = 0;
	while(fgets(line, sizeof(line)-1, fp)) {
		l++;
		if ((line[0] == '/' && line[1] == '/') || line[0] == '\0' || line[0] == '\n' || line[0] == '\r')
			continue;

		if ((range = sscanf(line, "%d%*[-~]%d %d", &start_range, &end_range, &level)) == 3 ||
		    (range = sscanf(line, "%d%*[-~]%d:%d", &start_range, &end_range, &level)) == 3 ||
		    (range = sscanf(line, "%d %d", &start_range, &level)) == 2 ||
		    (range = sscanf(line, "%d:%d", &start_range, &level)) == 2 ||
		    (range = sscanf(line, "%d: %d", &start_range, &level)) == 2) {
			if (level <= 0) {
				printf("gm_account [%s]: invalid GM level [%ds] line %d\n", GM_account_filename, level, l);
			} else {
				if (level > 99)
					level = 99;
				if (range == 2) {
					end_range = start_range;
				} else if (end_range < start_range) {
					i = end_range;
					end_range = start_range;
					start_range = i;
				}
				for (account_id = start_range; account_id <= end_range; account_id++) {
					if ((p = (struct gm_account *)numdb_search(gm_account_db, account_id)) == NULL) {
						p = (struct gm_account *)aCalloc(1, sizeof(struct gm_account));
						numdb_insert(gm_account_db, account_id, p);
					}
					p->account_id = account_id;
					p->level = level;
					c++;
				}
			}
		} else {
			printf("gm_account: broken data [%s] line %d\n", GM_account_filename, l);
		}
	}
	fclose(fp);
	//printf("gm_account: %s read done (%d gm account ID)\n", GM_account_filename, c);

	return;
}

static int mmo_char_sync_timer(int tid,unsigned int tick,int id,int data)
{
	char_sync();
	inter_sync();

	return 0;
}

static int char_log(char *fmt,...)
{
#ifdef TXT_ONLY
	FILE *logfp;
	va_list ap;
	va_start(ap,fmt);

	logfp=fopen(char_log_filename,"a");
	if(logfp){
		vfprintf(logfp,fmt,ap);
		fprintf(logfp,RETCODE);
		fclose(logfp);
	}

	va_end(ap);
#else
	char log[256], buf[512];
	va_list ap;

	va_start(ap,fmt);

	(void) vsnprintf(log,256,fmt,ap);
	va_end(ap);

	sprintf(
		tmp_sql,"INSERT INTO `%s` (`time`,`log`) VALUES (NOW(),'%s')",
		charlog_db,strecpy(buf,log)
	);
	if(mysql_query(&mysql_handle, tmp_sql) ){
		printf("DB server Error (insert `%s`)- %s\n", charlog_db, mysql_error(&mysql_handle) );
	}
#endif
	return 0;
}

static int count_users(void)
{
	int i, users = 0;

	if (login_fd >= 0 && session[login_fd]) {
		for(i = 0; i < MAX_MAP_SERVERS; i++) {
			if (server_fd[i] >= 0)
				users += server[i].users;
		}
	}

	return users;
}

static int mmo_char_send006b(int fd,struct char_session_data *sd)
{
	int i,found_num;
	const struct mmo_charstatus *st;
#ifdef NEW_006b
	int offset=24;
#else
	int offset=4;
#endif

#if PACKETVER >= 8
	int len = 108;
#else
	int len = 106;
#endif

	session[fd]->auth = 1; // 認証終了を socket.c に伝える

	sd->state = CHAR_STATE_AUTHOK;
	found_num = char_load_all(sd,sd->account_id);

	memset(WFIFOP(fd,0),0,offset+found_num*len);
	WFIFOW(fd,0)=0x6b;
	WFIFOW(fd,2)=offset+found_num*len;

	for( i = 0; i < max_char_slot ; i++ ) {
		if(sd->found_char[i] == NULL)
			continue;
		st = &sd->found_char[i]->st;
		WFIFOL(fd,offset+(i*len)    ) = st->char_id;
		WFIFOL(fd,offset+(i*len)+  4) = st->base_exp;
		WFIFOL(fd,offset+(i*len)+  8) = st->zeny;
		WFIFOL(fd,offset+(i*len)+ 12) = st->job_exp;
		WFIFOL(fd,offset+(i*len)+ 16) = st->job_level;
		WFIFOL(fd,offset+(i*len)+ 20) = 0;
		WFIFOL(fd,offset+(i*len)+ 24) = 0;
		WFIFOL(fd,offset+(i*len)+ 28) = st->option;
		WFIFOL(fd,offset+(i*len)+ 32) = st->karma;
		WFIFOL(fd,offset+(i*len)+ 36) = st->manner;
		WFIFOW(fd,offset+(i*len)+ 40) = st->status_point;
		WFIFOW(fd,offset+(i*len)+ 42) = (st->hp     > 0x7fff) ? 0x7fff : st->hp;
		WFIFOW(fd,offset+(i*len)+ 44) = (st->max_hp > 0x7fff) ? 0x7fff : st->max_hp;
		WFIFOW(fd,offset+(i*len)+ 46) = (st->sp     > 0x7fff) ? 0x7fff : st->sp;
		WFIFOW(fd,offset+(i*len)+ 48) = (st->max_sp > 0x7fff) ? 0x7fff : st->max_sp;
		WFIFOW(fd,offset+(i*len)+ 50) = DEFAULT_WALK_SPEED; // char_dat[j].st.speed;
		if(st->class_ == PC_CLASS_GS || st->class_ == PC_CLASS_NJ)
			WFIFOW(fd,offset+(i*len)+ 52) = st->class_-4;
		else
			WFIFOW(fd,offset+(i*len)+ 52) = st->class_;
		WFIFOW(fd,offset+(i*len)+ 54) = st->hair;
		WFIFOW(fd,offset+(i*len)+ 56) = st->weapon;
		WFIFOW(fd,offset+(i*len)+ 58) = st->base_level;
		WFIFOW(fd,offset+(i*len)+ 60) = st->skill_point;
		WFIFOW(fd,offset+(i*len)+ 62) = st->head_bottom;
		WFIFOW(fd,offset+(i*len)+ 64) = st->shield;
		WFIFOW(fd,offset+(i*len)+ 66) = st->head_top;
		WFIFOW(fd,offset+(i*len)+ 68) = st->head_mid;
		WFIFOW(fd,offset+(i*len)+ 70) = st->hair_color;
		WFIFOW(fd,offset+(i*len)+ 72) = st->clothes_color;
		memcpy( WFIFOP(fd,offset+(i*len)+74), st->name, 24 );
		WFIFOB(fd,offset+(i*len)+ 98) = (st->str > 255)  ? 255: st->str;
		WFIFOB(fd,offset+(i*len)+ 99) = (st->agi > 255)  ? 255: st->agi;
		WFIFOB(fd,offset+(i*len)+100) = (st->vit > 255)  ? 255: st->vit;
		WFIFOB(fd,offset+(i*len)+101) = (st->int_ > 255) ? 255: st->int_;
		WFIFOB(fd,offset+(i*len)+102) = (st->dex > 255)  ? 255: st->dex;
		WFIFOB(fd,offset+(i*len)+103) = (st->luk > 255)  ? 255: st->luk;
		WFIFOW(fd,offset+(i*len)+104) = st->char_num;
		if(len >= 108)
			WFIFOW(fd,offset+(i*len)+106) = 1;	// キャラ名の変更が可能な状態かどうか(0でON 1でOFF)

		// ロードナイト/パラディンのログイン時のエラー対策
		if (st->option == 32)
			WFIFOL(fd,offset+(i*len)+28) = 0;
		else
			WFIFOL(fd,offset+(i*len)+28) = st->option;
	}
	WFIFOSET(fd,WFIFOW(fd,2));

	return 0;
}

// ##変数の保存
static int set_account_reg2(int acc,int num,struct global_reg *reg)
{
	int i;
	struct char_session_data sd;
	struct mmo_chardata *cd;
	int max = char_load_all(&sd,acc);

	for(i=0;i<max;i++) {
		// ##変数は利用される可能性が低いので、手抜きとしてconst外して強引にここで書き換える
		cd = (struct mmo_chardata *)&(*sd.found_char[i]);
		if(cd) {
			memcpy(&cd->reg.account2, reg, sizeof(cd->reg.account2));
			cd->reg.account2_num = num;
		}
	}

	return max;
}

// ##変数の取得
static int get_account_reg2(struct char_session_data *sd,struct global_reg *reg)
{
	int i;

	if(sd == NULL)
		return 0;

	for(i=0;i<max_char_slot;i++) {
		const struct mmo_chardata *cd = sd->found_char[i];
		if(cd) {
			if(cd->reg.account2_num > 0) {
				memcpy(reg, &cd->reg.account2, sizeof(cd->reg.account2));
				return cd->reg.account2_num;
			}
		}
	}
	return 0;
}

// 離婚
static int char_divorce(const struct mmo_charstatus *st)
{
	if(st == NULL)
		return 0;

	if(st->partner_id){
		int i;
		struct mmo_charstatus s1;
		memcpy(&s1,st,sizeof(struct mmo_charstatus));

		// 離婚
		s1.partner_id = 0;

		// 結婚指輪を剥奪
		for(i=0;i<MAX_INVENTORY;i++){
			if(s1.inventory[i].nameid == WEDDING_RING_M || s1.inventory[i].nameid == WEDDING_RING_F){
				memset(&s1.inventory[i],0,sizeof(s1.inventory[0]));
			}
		}
		char_save(&s1);
		return 1;
	}

	return 0;
}

// 養子解体
static int char_break_adoption(const struct mmo_charstatus *st)
{
	if(st == NULL)
		return 0;
	if(st->baby_id > 0 || st->parent_id[0] > 0 || st->parent_id[1] > 0) {
		struct mmo_charstatus s1;
		memcpy(&s1,st,sizeof(struct mmo_charstatus));
		// 養子であれば元の職に戻す
		if(s1.class_ >= PC_CLASS_NV3 && s1.class_ <= PC_CLASS_SNV3) {
			if(s1.class_ == PC_CLASS_SNV3)
				s1.class_ = PC_CLASS_SNV;
			else
				s1.class_ -= PC_CLASS_BASE3;
		}
		s1.baby_id = 0;
		s1.parent_id[0] = 0;
		s1.parent_id[1] = 0;
		char_save(&s1);
		return 1;
	}

	return 0;
}

// ランキングデータ送信セット
static int char_set_ranking_send(int ranking_id,unsigned char *buf)
{
	WBUFW(buf,0) = 0x2b30;
	WBUFW(buf,2) = 6+sizeof(ranking_data[0]);
	WBUFW(buf,4) = ranking_id;
	memcpy(WBUFP(buf,6), &ranking_data[ranking_id], sizeof(ranking_data[0]));

	return (int)WBUFW(buf,2);
}

// ランキングデータ更新
static int compare_ranking_data(const void *a,const void *b)
{
	struct Ranking_Data *p1 = (struct Ranking_Data *)a;
	struct Ranking_Data *p2 = (struct Ranking_Data *)b;

	if(p1->point < p2->point)
		return 1;
	if(p1->point > p2->point)
		return -1;

	return 0;
}

static int char_ranking_update(int ranking_id,int rank,struct Ranking_Data *rd)
{
	if(rd == NULL)
		return 0;
	if(ranking_id < 0 || ranking_id >= MAX_RANKING)
		return 0;

	if(rank >= 0 && rank < MAX_RANKER) {
		// ランカーのポイント更新
		if(ranking_data[ranking_id][rank].char_id == rd->char_id) {
			ranking_data[ranking_id][rank].point = rd->point;
		} else {
			// 順位が変更されている可能性があるので該当キャラを探す
			int i;
			for(i=0; i<MAX_RANKER; i++) {
				if(ranking_data[ranking_id][i].char_id == rd->char_id) {
					ranking_data[ranking_id][i].point = rd->point;
					rank = i;
					break;
				}
			}
			if(i >= MAX_RANKER)	// 見つからない場合もある
				return 0;
		}
	} else if(rank == MAX_RANKER) {
		// 新規ランクイン
		if(ranking_data[ranking_id][MAX_RANKER-1].point < rd->point)
		{
			int i;
			for(i=MAX_RANKER; i>0 && ranking_data[ranking_id][i-1].char_id <= 0; i--);
			if(i == MAX_RANKER)
				i--;
			strncpy(ranking_data[ranking_id][i].name, rd->name, 24);
			ranking_data[ranking_id][i].point   = rd->point;
			ranking_data[ranking_id][i].char_id = rd->char_id;
			rank = i;
		} else {
			return 0;	// ランクインできない場合もある
		}
	} else {
		printf("char_ranking_update: invalid rank %d !!\n",rank);
		return 0;
	}

	// 順位が変動するならソート
	if( (rank > 0 && ranking_data[ranking_id][rank-1].point < rd->point) ||
	    (rank < MAX_RANKER-1 && ranking_data[ranking_id][rank+1].point > rd->point) )
	{
		qsort(ranking_data[ranking_id], MAX_RANKER, sizeof(struct Ranking_Data), compare_ranking_data);
	}

	return 0;
}

// ランキングデータ削除
static int char_ranking_delete(int char_id)
{
	int i,j;

	for(i=0; i<MAX_RANKING; i++) {
		for(j=0; j<MAX_RANKER; j++) {
			if(ranking_data[i][j].char_id == char_id) {
				strncpy(ranking_data[i][j].name, unknown_char_name, 24);
				ranking_data[i][j].point   = 0;
				ranking_data[i][j].char_id = 0;
				break;
			}
		}
		if(j < MAX_RANKER) {
			int len;
			char buf[6+32*MAX_RANKER];

			// ランキングの再構築はしない
			qsort(ranking_data[i], MAX_RANKER, sizeof(struct Ranking_Data), compare_ranking_data);
			len = char_set_ranking_send(i,buf);
			mapif_sendall(buf,len);
		}
	}
	return 0;
}

// キャラ削除に伴うデータ削除
static int char_delete(const struct mmo_chardata *cd)
{
	int j;
	unsigned char buf[8];

	nullpo_retr(-1,cd);

	printf("char_delete: %s\n",cd->st.name);
	// キャラが接続しているかもしれないのでmapに切断要求
	WBUFW(buf,0)=0x2b19;
	WBUFL(buf,2)=cd->st.account_id;
	mapif_sendall(buf,6);

	// ステータス異常削除
	status_delete(cd->st.char_id);

	// ROメール削除
	mail_delete(cd->st.char_id);

	// ランキング削除
	char_ranking_delete(cd->st.char_id);

	// ペット削除
	if(cd->st.pet_id)
		pet_delete(cd->st.pet_id);
	for(j=0;j<MAX_INVENTORY;j++) {
		if(cd->st.inventory[j].card[0] == (short)0xff00)
			pet_delete(*((long *)(&cd->st.inventory[j].card[1])));
	}
	for(j=0;j<MAX_CART;j++) {
		if(cd->st.cart[j].card[0] == (short)0xff00)
			pet_delete(*((long *)(&cd->st.cart[j].card[1])));
	}
	// ホムンクルス削除
	if(cd->st.homun_id)
		homun_delete(cd->st.homun_id);
	// ギルド脱退
	if(cd->st.guild_id)
		inter_guild_leave(cd->st.guild_id,cd->st.account_id,cd->st.char_id);
	// パーティー脱退
	if(cd->st.party_id)
		inter_party_leave(cd->st.party_id, cd->st.account_id, cd->st.name);
	// 離婚
	if(cd->st.partner_id){
		const struct mmo_chardata *p_cd = char_load(cd->st.partner_id);
		if(p_cd && cd->st.partner_id == p_cd->st.char_id && p_cd->st.partner_id == cd->st.char_id) {
			// 相方が自分と結婚している場合
			// 相方の離婚情報をmapに通知
			WBUFW(buf,0)=0x2b12;
			WBUFL(buf,2)=p_cd->st.char_id;
			mapif_sendall(buf,6);

			// 相方の離婚処理
			char_divorce(&p_cd->st);
		}

		// 自分の離婚処理
		char_divorce(&cd->st);
	}
	char_delete_sub(cd->st.char_id);

	return 0;
}

// authfifoの比較
static int cmp_authfifo(int i,int account_id,int login_id1,int login_id2,unsigned long ip)
{
	if( auth_fifo[i].account_id == account_id && auth_fifo[i].login_id1 == login_id1 )
		return 1;

#ifdef CMP_AUTHFIFO_LOGIN2
	//printf("cmp_authfifo: id2 check %d %x %x = %08x %08x %08x\n",i,auth_fifo[i].login_id2,login_id2,
	//	auth_fifo[i].account_id,auth_fifo[i].login_id1,auth_fifo[i].login_id2);
	if( auth_fifo[i].login_id2 == login_id2 && login_id2 != 0 )
		return 1;
#endif

#ifdef CMP_AUTHFIFO_IP
	//printf("cmp_authfifo: ip check %d %x %x = %08x %08x %08x\n",i,auth_fifo[i].ip,ip,
	//	auth_fifo[i].account_id,auth_fifo[i].login_id1,auth_fifo[i].login_id2);
	if( auth_fifo[i].ip == ip && ip != 0 && ip != 0xffffffff )
		return 1;
#endif
	return 0;
}

// ソケットのデストラクタ
int parse_login_disconnect(int fd)
{
	if (fd == login_fd)
		login_fd = -1;

	return 0;
}

int parse_tologin(int fd)
{
	int i,fdc;
	struct char_session_data *sd;

	//printf("parse_tologin : %d %d %d\n",fd,RFIFOREST(fd),RFIFOW(fd,0));
	sd = (struct char_session_data *)session[fd]->session_data;

	while(RFIFOREST(fd)>=2){
		switch(RFIFOW(fd,0)){
		case 0x2711:
			if(RFIFOREST(fd)<3)
				return 0;
			if(RFIFOB(fd,2)){
				printf("connect login server error : %d\n",RFIFOB(fd,2));
				exit(1);
			}
			RFIFOSKIP(fd,3);
			session[fd]->auth = -1; // 認証終了を socket.c に伝える
			break;

		case 0x2713:
			if(RFIFOREST(fd)<15)
				return 0;
			for(i=0;i<fd_max;i++){
				if(session[i] && (sd = (struct char_session_data *)session[i]->session_data)){
					if(sd->account_id==RFIFOL(fd,2))
						break;
				}
			}
			fdc=i;
			if(fdc==fd_max){
				RFIFOSKIP(fd,15);
				break;
			}
			//printf("parse_tologin 2713 : %d\n",RFIFOB(fd,6));
			if(RFIFOB(fd,6)!=0){
				WFIFOW(fdc,0)=0x6c;
				WFIFOB(fdc,2)=0x42;
				WFIFOSET(fdc,3);
				RFIFOSKIP(fd,15);
				break;
			}
			sd->account_id=RFIFOL(fd,7);
			sd->login_id1=RFIFOL(fd,11);

			if(char_maintenance && isGM(sd->account_id)==0){
				close(fd);
				session[fd]->eof=1;
				return 0;
			}
			if(max_connect_user > 0) {
				if(count_users() < max_connect_user  || isGM(sd->account_id) > 0) {
					mmo_char_send006b(fdc,sd);
				} else {
					WFIFOW(fdc,0)=0x6c;
					WFIFOW(fdc,2)=0;
					WFIFOSET(fdc,3);
				}
			} else {
				mmo_char_send006b(fdc,sd);
			}
			RFIFOSKIP(fd,15);
			break;

		// キャラ削除(メールアドレス確認後)
		case 0x2716:
			if(RFIFOREST(fd)<11)
				return 0;
			{
				int ch;
				for(i=0;i<fd_max;i++){
					if(session[i] && (sd = (struct char_session_data *)session[i]->session_data)){
						if(sd->account_id==RFIFOL(fd,2))
							break;
					}
				}
				fdc=i;
				if(fdc==fd_max){
					RFIFOSKIP(fd,15);
					break;
				}
				if(RFIFOB(fd,10)!=0){
					WFIFOW(fdc,0)=0x70;
					WFIFOB(fdc,2)=1;
					WFIFOSET(fdc,3);
				}else{
					for(i=0;i<max_char_slot;i++){
						const struct mmo_chardata *cd = sd->found_char[i];
						if(cd && cd->st.char_id == RFIFOL(fd,6)){
							char_delete(cd);
							for(ch=i;ch<max_char_slot-1;ch++)
								sd->found_char[ch]=sd->found_char[ch+1];
							sd->found_char[max_char_slot-1] = NULL;
							break;
						}
					}
					if( i==max_char_slot ){
						WFIFOW(fdc,0)=0x70;
						WFIFOB(fdc,2)=0;
						WFIFOSET(fdc,3);
					} else {
						WFIFOW(fdc,0)=0x6f;
						WFIFOSET(fdc,2);
					}
				}
				RFIFOSKIP(fd,11);
			}
			break;

		// gm reply
		case 0x2721:
			{
				// SQL 化が面倒くさいので保留
				unsigned char buf[16];
				if(RFIFOREST(fd)<10)
					return 0;
				RFIFOSKIP(fd,10);
				WBUFW(buf,0)=0x2b0b;
				WBUFL(buf,2)=RFIFOL(fd,2);
				WBUFL(buf,6)=RFIFOL(fd,6);
				mapif_sendall(buf,10);
			}
			break;

		// changesex reply
		case 0x2723:
			if(RFIFOREST(fd)<7)
				return 0;
			{
				int i,j,sex = RFIFOB(fd,6);
				unsigned char buf[8];
				struct char_session_data sd;
				struct mmo_charstatus    st;
				int found_char = char_load_all(&sd,RFIFOL(fd,2));
				for(i=0;i<found_char;i++){
					int flag = 0;
					memcpy(&st,&sd.found_char[i]->st,sizeof(struct mmo_charstatus));
					// 雷鳥は職も変更
					if(st.class_ == 19 || st.class_ == 20){
						flag = 1; st.class_ = (sex ? 19 : 20);
					} else if(st.class_ == 19 + PC_CLASS_BASE2 || st.class_ == 20 + PC_CLASS_BASE2) {
						flag = 1; st.class_ = (sex ? 19 : 20) + PC_CLASS_BASE2;
					} else if(st.class_ == 19 + PC_CLASS_BASE3 || st.class_ == 20 + PC_CLASS_BASE3) {
						flag = 1; st.class_ = (sex ? 19 : 20) + PC_CLASS_BASE3;
					}
					if(flag) {
						// 雷鳥装備外し
						for(j=0;j<MAX_INVENTORY;j++) {
							if(st.inventory[j].equip) st.inventory[j].equip=0;
						}
						// 雷鳥スキルリセット
						for(j=0;j<MAX_SKILL;j++) {
							if(st.skill[j].id>0 && !st.skill[j].flag){
								st.skill_point += st.skill[j].lv;
								st.skill[j].lv = 0;
							}
						}
						char_save(&st);	// キャラデータ変更のセーブ
					}
				}
				WBUFW(buf,0)=0x2b0d;
				WBUFL(buf,2)=RFIFOL(fd,2);
				WBUFB(buf,6)=RFIFOB(fd,6);
				mapif_sendall(buf,7);
				RFIFOSKIP(fd,7);
			}
			break;

		// account_reg2変更通知
		case 0x2729:
			{
				struct global_reg reg[ACCOUNT_REG2_NUM];
				unsigned char buf[ACCOUNT_REG2_NUM*36+16];
				int j,p,acc;
				if(RFIFOREST(fd)<4)
					return 0;
				if(RFIFOREST(fd)<RFIFOW(fd,2))
					return 0;
				acc=RFIFOL(fd,4);
				memset(&reg, 0, sizeof(reg));
				for(p=8,j=0;p<RFIFOW(fd,2) && j<ACCOUNT_REG2_NUM;p+=36,j++){
					strncpy(reg[j].str,RFIFOP(fd,p),32);
					reg[j].str[31] = '\0';	// force \0 terminal
					reg[j].value   = RFIFOL(fd,p+32);
				}
				set_account_reg2(acc,j,reg);
				// 同垢ログインを禁止していれば送る必要は無い
				memcpy(buf,RFIFOP(fd,0),RFIFOW(fd,2));
				WBUFW(buf,0)=0x2b11;
				mapif_sendall(buf,WBUFW(buf,2));
				RFIFOSKIP(fd,RFIFOW(fd,2));
				//printf("char: save_account_reg_reply\n");
			}
			break;

		// アカウント削除通知
		case 0x272a:
			{
				// 該当キャラクターの削除
				int i;
				struct char_session_data sd;
				int max = char_load_all(&sd,RFIFOL(fd,2));
				for(i=0;i<max;i++) {
					char_delete(sd.found_char[i]);
				}
				// 倉庫の削除
				storage_delete(RFIFOL(fd,2));
				RFIFOSKIP(fd,6);
			}
			break;

		// charメンテナンス状態変更応答
		case 0x272c:
			{
				unsigned char buf[4];
				if(RFIFOREST(fd)<3)
					return 0;
				WBUFW(buf,0)=0x2b15;
				WBUFB(buf,2)=RFIFOB(fd,2);
				mapif_sendall(buf,3);

				RFIFOSKIP(fd,3);
			}
			break;

		// 暗号化ログインのチャレンジ返答
		case 0x272e:
			{
				if(RFIFOREST(fd)<4 || RFIFOREST(fd)<RFIFOW(fd,2))
					return 0;
				if( RFIFOW(fd,2)>192 || RFIFOW(fd,2)<10 )
				{
					close(fd);
					session[fd]->eof=1;
					return 0;
				}
				// 暗号化ログイン
				WFIFOW(login_fd,0)=0x272f;
				memcpy(WFIFOP(login_fd,2),userid,24);
				HMAC_MD5_Binary( passwd, strlen(passwd), RFIFOP(login_fd,4), RFIFOW(login_fd,2)-4, WFIFOP(login_fd,26) );
				WFIFOL(login_fd,42)=0;
				WFIFOL(login_fd,46)=4;	// 暗号化に HMAC-MD5 を使う
				WFIFOL(login_fd,50)=0;
				WFIFOL(login_fd,54)=char_ip;
				WFIFOW(login_fd,58)=char_port;
				memcpy(WFIFOP(login_fd,60),server_name,20);
				WFIFOW(login_fd,80)=char_maintenance;
				WFIFOW(login_fd,82)=char_new;
				WFIFOSET(login_fd,84);

				RFIFOSKIP(login_fd,RFIFOW(fd,2));
			}
			break;

		// 新規ログインのため同一アカウントを切断
		case 0x2730:
			if(RFIFOREST(fd)<6)
				return 0;
			{
				int account_id = RFIFOL(fd,2);
				for(i=0; i<fd_max; i++) {
					if(session[i] && (sd = (struct char_session_data *)session[i]->session_data) && sd->account_id == account_id) {
						WFIFOW(i,0) = 0x81;
						WFIFOB(i,2) = 2;
						WFIFOSET(i,3);
						session[i]->auth = 0;	// 認証取消し
					}
				}

				// 同一アカウントの未認証データを全て破棄しておく
				for(i=0; i<AUTH_FIFO_SIZE; i++) {
					if(auth_fifo[i].account_id == account_id && !auth_fifo[i].delflag) {
						auth_fifo[i].delflag = 1;
					}
				}
				if(numdb_search(char_online_db,account_id)) {
					// 全mapサーバに切断要求
					unsigned char buf[8];
					WBUFW(buf,0) = 0x2b1a;
					WBUFL(buf,2) = account_id;
					mapif_sendall(buf,6);
				}
				RFIFOSKIP(fd,6);
			}
			break;

		default:
			close(fd);
			session[fd]->eof=1;
			return 0;
		}
	}

	return 0;
}

/*==========================================
 * mapが含まれているmap-serverを探す
 *------------------------------------------
 */
static int search_mapserver(char *map)
{
	int i, j;
	char map_temp[16]; // 15 + NULL

	strncpy(map_temp, map, 16);
	map_temp[15] = '\0';
	if (strstr(map_temp, ".gat") == NULL && strlen(map_temp) < 12)
		strcat(map_temp, ".gat");

	for(i = 0; i < MAX_MAP_SERVERS; i++) {
		if (server_fd[i] < 0)
			continue;
		for(j = 0; j < server[i].map_num; j++) {
			if (!strcmp(server[i].map + (j * 16), map_temp))
				return i;
		}
	}

	return -1;
}

static int search_mapserver_char(char *map, struct mmo_charstatus *cd)
{
	int i;

	i = search_mapserver(map);
	if(i != -1) {
		//printf("search_mapserver %s : success -> %d\n", map, i);
		return i;
	}

	if (cd) {
		for(i = 0; i < MAX_MAP_SERVERS; i++) {
			if (server_fd[i] < 0)
				continue;
			if (server[i].map_num > 0) {
				memcpy(cd->last_point.map, server[i].map, 16);
				printf("search_mapserver %s : another map %s -> %d\n", map, server[i].map, i);
				return i;
			}
		}
	}

	printf("search_mapserver failed : %s\n", map);

	return -1;
}

int char_erasemap(int fd, int id)
{
	unsigned char buf[16 * 1024];

	if(server[id].map_num*16+12 > sizeof(buf)) {	// 1024MAP以上なら警告して終了
		printf("char_erasemap: buffer overflow!! %d (%d maps)\n", fd, server[id].map_num);
		exit(1);
	}

	WBUFW(buf, 0) = 0x2b16;
	WBUFW(buf, 2) = server[id].map_num * 16 + 12;
	WBUFL(buf, 4) = server[id].ip;
	WBUFW(buf, 8) = server[id].port;
	memcpy(WBUFP(buf,12), server[id].map, 16 * server[id].map_num);
	WBUFW(buf,10) = server[id].map_num;
	mapif_sendallwos(fd, buf, WBUFW(buf,2));

	printf("char: map erase: %d (%d maps)\n", id, server[id].map_num);

	aFree(server[id].map);
	server[id].map = NULL;
	server[id].map_num = 0;

	return 0;
}

static int parse_map_disconnect_sub(void *key,void *data,va_list ap)
{
	int fd = va_arg(ap,int);
	unsigned long ip    = (unsigned long)va_arg(ap,int);
	unsigned short port = (unsigned short)va_arg(ap,int);
	struct char_online *c = (struct char_online*)data;
	unsigned char buf[8];

	if(c->ip == ip && c->port == port) {
		// printf("char: mapdisconnect %s %08x:%d\n",c->name,ip,port);
		WBUFW(buf,0) = 0x2b17;
		WBUFL(buf,2) = c->char_id;
		mapif_sendallwos(fd,buf,6);
		numdb_erase(char_online_db,key);
		char_set_offline( c->char_id );
		aFree(c);
	}

	return 0;
}

int parse_map_disconnect(int fd)
{
	int id;

	for(id = 0; id < MAX_MAP_SERVERS; id++) {
		if (server_fd[id] == fd) {
			server_fd[id] = -1;
			char_erasemap(fd, id);
			// 残っていたキャラの切断を他map-serverに通知
			numdb_foreach(char_online_db, parse_map_disconnect_sub, fd, (int)server[id].ip, (int)server[id].port);
			close(fd);
		}
	}

	return 0;
}

int parse_frommap(int fd)
{
	int i, j;
	int id;

	for(id = 0; id < MAX_MAP_SERVERS; id++) {
		if (server_fd[id] == fd)
			break;
	}
	if (id == MAX_MAP_SERVERS)
		session[fd]->eof = 1;

	//printf("parse_frommap : %d %d %d\n",fd,RFIFOREST(fd),RFIFOW(fd,0));

	while(RFIFOREST(fd)>=2){
		switch(RFIFOW(fd,0)){
		// マップサーバーから担当マップ名を受信
		case 0x2afa:
			if (RFIFOREST(fd) < 4 || RFIFOREST(fd) < RFIFOW(fd,2))
				return 0;
			j = server[id].map_num; // get actual quantity of maps for the server
			for(i = 4; i < RFIFOW(fd,2); i += 16) {
				int k = search_mapserver(RFIFOP(fd,i));
				if (k == -1) { // the map isn't assigned to any server
					// 担当マップサーバーが決まっていないマップなら設定
					if (j == 0) {
						server[id].map = (char *)aCalloc(16, sizeof(char));
					} else {
						server[id].map = (char *)aRealloc(server[id].map, sizeof(char) * 16 * (j + 1));
					}
					memcpy(server[id].map + (j * 16), RFIFOP(fd,i), 16);
					server[id].map[j * 16 + 15] = '\0';
					j++;
				} else if (k != id) { // if same map-server, it's probably an error (duplicated packet)
					// printf("Error to fix: 2 map-servers have same map: %16s\n", RFIFOP(fd,i));
					// If 2 map-servers manage same mapX, a problem exists with players.
					// When a player change of map, map-server will search at first if it manages the map.
					// So, player1 on map-server1 go on a mapX managed by map-server1. Player1 stay on map-server1.
					// Player2 on map-server2 go on same mapX managed by map-server2 too. Player2 Stays on map-server2.
					// Conclusion: player1 and player2 on same map can not see them!

					// [Eoe]
					// Above case NEVER occures because jA system managed to assign duplicated
					// map entries to ONLY one server. If map server received 0x2b04 packet and
					// notice that loaded maps are assigned to other map server, map server marks
					// loaded maps to other server's map. And if recives other map server crashes
					// packet(0x2b16) and crashed map entries includes the map which is loaded but
					// not assigned, map server requests char server to try assign lacked maps.

					// This systems can create redundancy system by loading "prontera.gat" in
					// two or more servers. If one server encountered serious trouble which cannot
					// recover soon, all players, however, can login to other servers by this system.
				}
			}
			server[id].map_num = j;

			{
				unsigned char *p = (unsigned char *)&server[id].ip;
				printf("set map %d from %d.%d.%d.%d:%d (%d maps)\n", id, p[0], p[1], p[2], p[3], server[id].port, j);
			}

			RFIFOSKIP(fd,RFIFOW(fd,2));
			{
				unsigned char buf[16 * 1024];

				if(j*16+12 > sizeof(buf)) {	// 1024MAP以上なら警告して終了
					printf("parse_frommap 0x2afa: %d buffer overflow!! (%d maps)\n", fd, j);
					WFIFOW(fd,0) = 0x2afb;	// failed
					WFIFOW(fd,2) = 1;
					WFIFOSET(fd,3);
					break;
				}
				WFIFOW(fd,0) = 0x2afb;
				WFIFOW(fd,2) = 0; // ok
				WFIFOSET(fd,3);

				// 他のマップサーバーに担当マップ情報を送信
				// map 鯖はchar鯖からのこのパケットを受信して初めて、
				// 自分が担当するマップが分かる
				WBUFW(buf, 0) = 0x2b04;
				WBUFW(buf, 2) = j * 16 + 12;
				WBUFL(buf, 4) = server[id].ip;
				WBUFW(buf, 8) = server[id].port;
				WBUFW(buf,10) = j;
				memcpy(WBUFP(buf,12), server[id].map, 16 * j);
				mapif_sendall(buf, WBUFW(buf,2));

				// 他のマップサーバーの担当マップを送信
				for(i = 0; i < MAX_MAP_SERVERS; i++) {
					if (server_fd[i] >= 0 && i != id) {
						if (server[i].map_num > 0) {
							WFIFOW(fd, 0) = 0x2b04;
							WFIFOW(fd, 2) = server[i].map_num * 16 + 12;
							WFIFOL(fd, 4) = server[i].ip;
							WFIFOW(fd, 8) = server[i].port;
							WFIFOW(fd,10) = server[i].map_num;
							memcpy(WFIFOP(fd, 12), server[i].map, 16 * server[i].map_num);
							WFIFOSET(fd, WFIFOW(fd,2));
						}
					}
				}
			}
			break;

		// 認証要求
		case 0x2afc:
			if(RFIFOREST(fd)<23)
				return 0;
			//printf("auth_fifo search %08x %08x %08x %08x %08x\n",
			//	RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10),RFIFOL(fd,14),RFIFOL(fd,18));
			for(i=0; i<AUTH_FIFO_SIZE; i++) {
				if( cmp_authfifo(i,RFIFOL(fd,2),RFIFOL(fd,10),RFIFOL(fd,14),RFIFOL(fd,18)) &&
				    auth_fifo[i].char_id == RFIFOL(fd,6) &&
				    !auth_fifo[i].delflag )
				{
					auth_fifo[i].delflag = 1;
					break;
				}
			}
			if(i >= AUTH_FIFO_SIZE) {
				WFIFOW(fd,0)=0x2afe;
				WFIFOW(fd,2)=RFIFOL(fd,2);
				WFIFOB(fd,6)=0;
				WFIFOSET(fd,7);
				printf("auth_fifo search error! %d\n", RFIFOL(fd,6));
			} else {
				const struct mmo_chardata *cd = char_load(RFIFOL(fd,6));
				if(cd == NULL || auth_fifo[i].sex != RFIFOB(fd,22)) {
					WFIFOW(fd,0)=0x2afe;
					WFIFOW(fd,2)=RFIFOL(fd,2);
					WFIFOB(fd,6)=0;
					WFIFOSET(fd,7);
					printf("authorization failed! %d\n", RFIFOL(fd,6));
				} else {
					unsigned char buf[48];
					struct char_online *c;
					size_t s1 = sizeof(struct mmo_charstatus);
					size_t s2 = sizeof(struct registry);

					WFIFOW(fd,0) = 0x2afd;
					WFIFOW(fd,2) = 12 + s1 + s2;
					WFIFOL(fd,4) = RFIFOL(fd,2); // account id
					//WFIFOL(fd,8) = RFIFOL(fd,6);
					WFIFOL(fd,8) = auth_fifo[i].login_id2;
					memcpy(WFIFOP(fd,12   ), &cd->st , s1);
					memcpy(WFIFOP(fd,12+s1), &cd->reg, s2);
					WFIFOSET(fd,WFIFOW(fd,2));

					// オンラインdbに挿入
					c = (struct char_online *)numdb_search(char_online_db,RFIFOL(fd,2));
					if(c == NULL) {
						c = (struct char_online *)aCalloc(1,sizeof(struct char_online));
						numdb_insert(char_online_db,RFIFOL(fd,2),c);
					}
					c->ip         = server[id].ip;
					c->port       = server[id].port;
					c->account_id = cd->st.account_id;
					c->char_id    = cd->st.char_id;
					memcpy(c->name,cd->st.name,24);
					char_set_online( c->char_id );

					// このmap-server以外にログインしたことを通知する
					WBUFW(buf, 0) = 0x2b09;
					WBUFL(buf, 2) = cd->st.char_id;
					memcpy(WBUFP(buf,6),cd->st.name,24);
					WBUFL(buf,30) = cd->st.account_id;
					WBUFL(buf,34) = server[id].ip;
					WBUFW(buf,38) = server[id].port;
					mapif_sendallwos(fd,buf,40);
				}
			}
			RFIFOSKIP(fd,23);
			break;

		// MAPサーバー上のユーザー数受信
		case 0x2aff:
			if(RFIFOREST(fd)<6)
				return 0;
			server[id].users=RFIFOL(fd,2);
			RFIFOSKIP(fd,6);
			break;

		// キャラデータ保存
		case 0x2b01:
			if(RFIFOREST(fd)<4 || RFIFOREST(fd)<RFIFOW(fd,2))
				return 0;
			if( ((struct mmo_charstatus*)RFIFOP(fd,12))->char_id != RFIFOL(fd,8) ) {
				// キャラID違いのデータを送ってきたので強制切断
				unsigned char buf[8];
				WBUFW(buf,0) = 0x2b19;
				WBUFL(buf,2) = RFIFOL(fd,4);
				mapif_sendall(buf,6);
			} else {
				char_save((struct mmo_charstatus *)RFIFOP(fd,12));
			}
			RFIFOSKIP(fd,RFIFOW(fd,2));
			break;

		// キャラセレ要求
		case 0x2b02:
			if(RFIFOREST(fd)<19)
				return 0;

			if(auth_fifo_pos >= AUTH_FIFO_SIZE) {
				auth_fifo_pos = 0;
			}
			//printf("auth_fifo set 0x2b02 %d - %08x %08x %08x %08x\n",
			//	auth_fifo_pos,RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10),RFIFOL(fd,14));
			auth_fifo[auth_fifo_pos].account_id = RFIFOL(fd,2);
			auth_fifo[auth_fifo_pos].char_id    = 0;
			auth_fifo[auth_fifo_pos].login_id1  = RFIFOL(fd,6);
			auth_fifo[auth_fifo_pos].login_id2  = RFIFOL(fd,10);
			auth_fifo[auth_fifo_pos].delflag    = 2;
			auth_fifo[auth_fifo_pos].tick       = gettick();
			auth_fifo[auth_fifo_pos].ip         = RFIFOL(fd,14);
			auth_fifo[auth_fifo_pos].sex        = WFIFOB(fd,18);
			auth_fifo_pos++;

			WFIFOW(fd,0) = 0x2b03;
			WFIFOL(fd,2) = RFIFOL(fd,2);
			WFIFOB(fd,6) = 0;
			WFIFOSET(fd,7);
			RFIFOSKIP(fd,19);
			break;

		// マップサーバー間移動要求
		case 0x2b05:
			if(RFIFOREST(fd)<41)
				return 0;

			if(auth_fifo_pos >= AUTH_FIFO_SIZE) {
				auth_fifo_pos = 0;
			}
			memcpy(WFIFOP(fd,2),RFIFOP(fd,2),38);
			WFIFOW(fd,0)=0x2b06;

			//printf("auth_fifo set 0x2b05 %d - %08x %08x\n",auth_fifo_pos,RFIFOL(fd,2),RFIFOL(fd,6));
			auth_fifo[auth_fifo_pos].account_id = RFIFOL(fd,2);
			auth_fifo[auth_fifo_pos].char_id    = RFIFOL(fd,10);
			auth_fifo[auth_fifo_pos].login_id1  = RFIFOL(fd,6);
			auth_fifo[auth_fifo_pos].delflag    = 0;
			auth_fifo[auth_fifo_pos].sex        = RFIFOB(fd,40);
			auth_fifo[auth_fifo_pos].tick       = gettick();
			auth_fifo[auth_fifo_pos].ip         = session[fd]->client_addr.sin_addr.s_addr;
			auth_fifo_pos++;

			WFIFOL(fd,6)=0;
			WFIFOSET(fd,40);
			RFIFOSKIP(fd,41);
			break;

		// キャラ名検索
		case 0x2b08:
			if(RFIFOREST(fd)<6)
				return 0;
			{
				const struct mmo_chardata *cd = char_load(RFIFOL(fd,2));
				WFIFOW(fd,0) = 0x2b09;
				WFIFOL(fd,2) = RFIFOL(fd,2);
				if(cd){
					struct char_online* c = (struct char_online *)numdb_search(char_online_db,cd->st.account_id);
					memcpy(WFIFOP(fd,6),cd->st.name,24);
					WFIFOL(fd,30) = cd->st.account_id;
					WFIFOL(fd,34) = (c && c->char_id == cd->st.char_id ? c->ip   : 0);
					WFIFOW(fd,38) = (c && c->char_id == cd->st.char_id ? c->port : 0);
				} else {
					memcpy(WFIFOP(fd,6),unknown_char_name,24);
					WFIFOL(fd,30)=0;
					WFIFOL(fd,34)=0;
					WFIFOW(fd,38)=0;
				}
				WFIFOSET(fd,40);
				RFIFOSKIP(fd,6);
			}
			break;

		// GMになりたーい
		case 0x2b0a:
			if(RFIFOREST(fd)<4)
				return 0;
			if(RFIFOREST(fd)<RFIFOW(fd,2))
				return 0;
			if (login_fd >= 0 && session[login_fd])
			{
				memcpy(WFIFOP(login_fd,2),RFIFOP(fd,2),RFIFOW(fd,2)-2);
				WFIFOW(login_fd,0)=0x2720;
				WFIFOSET(login_fd,RFIFOW(fd,2));
			}
			//printf("char : change gm -> login %d %s %d\n",RFIFOL(fd,4),RFIFOP(fd,8),RFIFOW(fd,2));
			RFIFOSKIP(fd,RFIFOW(fd,2));
			break;

		// 性別変換要求
		case 0x2b0c:
			if(RFIFOREST(fd)<4)
				return 0;
			if(RFIFOREST(fd)<RFIFOW(fd,2))
				return 0;
			if (login_fd >= 0 && session[login_fd])
			{
				WFIFOW(login_fd,0) = 0x2722;
				WFIFOW(login_fd,2) = RFIFOW(fd,2);
				WFIFOL(login_fd,4) = RFIFOL(fd,4);
				WFIFOB(login_fd,8) = RFIFOB(fd,8);
				WFIFOSET(login_fd,RFIFOW(fd,2));
			}
			//printf("char : change sex -> login %d %d %d \n",RFIFOL(fd,4),RFIFOB(fd,8),RFIFOW(fd,2));
			RFIFOSKIP(fd,RFIFOW(fd,2));
			break;

		// account_reg保存要求
		case 0x2b10:
			{
				struct global_reg reg[ACCOUNT_REG2_NUM];
				int j,p,acc;
				if(RFIFOREST(fd)<4)
					return 0;
				if(RFIFOREST(fd)<RFIFOW(fd,2))
					return 0;
				acc=RFIFOL(fd,4);
				memset(&reg, 0, sizeof(reg));
				for(p=8,j=0;p<RFIFOW(fd,2) && j<ACCOUNT_REG2_NUM;p+=36,j++){
					strncpy(reg[j].str,RFIFOP(fd,p),32);
					reg[j].str[31] = '\0';	// force \0 terminal
					reg[j].value   = RFIFOL(fd,p+32);
				}
				set_account_reg2(acc,j,reg);
				// loginサーバーへ送る
				if (login_fd >= 0 && session[login_fd])
				{
					memcpy(WFIFOP(login_fd,0),RFIFOP(fd,0),RFIFOW(fd,2));
					WFIFOW(login_fd,0) = 0x2728;
					WFIFOSET(login_fd,WFIFOW(login_fd,2));
				}
				// ワールドへの同垢ログインがなければmapサーバーに送る必要はない
				//memcpy(buf,RFIFOP(fd,0),RFIFOW(fd,2));
				//WBUFW(buf,0)=0x2b11;
				//mapif_sendall(buf,WBUFW(buf,2));
				RFIFOSKIP(fd,RFIFOW(fd,2));
				//printf("char: save_account_reg (from map)\n");
			}
			break;

		// mapサーバ有効化
		case 0x2b13:
			if(RFIFOREST(fd)<3)
				return 0;
			server[id].active=RFIFOB(fd,2);
			printf("char: map_server_active: %d %d\n",id,server[id].active);
			RFIFOSKIP(fd,3);
			break;

		// charサーバメンテナンス状態に
		case 0x2b14:
			if(RFIFOREST(fd)<3)
				return 0;
			char_maintenance=RFIFOB(fd,2);
			printf("char: maintenance: %d\n",char_maintenance);
			// loginに通知
			if (login_fd >= 0 && session[login_fd])
			{
				WFIFOW(login_fd,0)=0x272b;
				WFIFOB(login_fd,2)=char_maintenance;
				WFIFOSET(login_fd,3);
			}
			RFIFOSKIP(fd,3);
			break;

		// キャラクター切断を他mapに通知
		case 0x2b18:
			if(RFIFOREST(fd)<10)
				return 0;
			{
				struct char_online *c = (struct char_online *)numdb_erase(char_online_db,RFIFOL(fd,2));
				if(c) {
					unsigned char buf[8];
					char_set_offline( c->char_id );
					aFree(c);
					WBUFW(buf,0) = 0x2b17;
					WBUFL(buf,2) = RFIFOL(fd,6);
					mapif_sendallwos(fd,buf,6);
				}
				RFIFOSKIP(fd,10);
			}
			break;

		// 離婚
		case 0x2b20:
			if(RFIFOREST(fd)<6)
				return 0;
			{
				const struct mmo_chardata *cd1 = char_load(RFIFOL(fd,2));
				if( cd1 && cd1->st.partner_id ) {
					unsigned char buf[8];
					// 離婚情報をmapに通知
					WBUFW(buf,0)=0x2b12;
					WBUFL(buf,2)=cd1->st.char_id;
					mapif_sendall(buf,6);
					char_divorce(&cd1->st);
				}
				RFIFOSKIP(fd,6);
			}
			break;

		// 友達リスト削除
		case 0x2b24:
			if( RFIFOREST(fd)<18 )
				return 0;
			{
				const struct mmo_chardata *cpcd = char_load(RFIFOL(fd,6));

				if(cpcd) {
					unsigned char buf[32];
					struct mmo_charstatus st = cpcd->st;
					int i;

					for( i=0; i<st.friend_num; i++ )
					{
						if( st.friend_data[i].account_id == RFIFOL(fd,10) &&
							st.friend_data[i].char_id == RFIFOL(fd,14) )
						{
							st.friend_num--;
							memmove( &st.friend_data[i], &st.friend_data[i+1], sizeof(st.friend_data[0])*(st.friend_num-i) );
							break;
						}
					}
					char_save(&st);

					memcpy( buf, RFIFOP(fd,0), 18 );
					WBUFW(buf,0) = 0x2b25;
					mapif_sendallwos(fd,buf,18);
				}
				RFIFOSKIP(fd,18);
			}
			break;

		// 友達リストオンライン通知
		case 0x2b26:
			if( RFIFOREST(fd)<4 || RFIFOREST(fd)<RFIFOW(fd,2) )
				return 0;
			if( RFIFOW(fd,2) <= MAX_FRIEND*8+16 )
			{
				unsigned char buf[MAX_FRIEND*8+32];
				memcpy( buf, RFIFOP(fd,0), RFIFOW(fd,2) );
				WBUFW(buf,0) = 0x2b27;
				mapif_sendallwos(fd,buf,RFIFOW(fd,2));
			}
			RFIFOSKIP(fd,RFIFOW(fd,2));
			break;

		// 養子解体
		case 0x2b28:
			if(RFIFOREST(fd)<30)
				return 0;
			{
				const struct mmo_chardata *cd1 = char_load(RFIFOL(fd,2));
				if( cd1 && (cd1->st.baby_id || cd1->st.parent_id[0] || cd1->st.parent_id[1]) ) {
					unsigned char buf[32];
					// 養子解体情報をmapに通知
					WBUFW(buf,0)=0x2b29;
					WBUFL(buf,2)=cd1->st.char_id;
					memcpy(WBUFP(buf,6), RFIFOP(fd,6), 24);
					mapif_sendall(buf,30);
					char_break_adoption(&cd1->st);
				}
				RFIFOSKIP(fd,30);
			}
			break;

		// キャラ永続変数の保存要求
		case 0x2b2d:
			{
				struct global_reg reg[GLOBAL_REG_NUM];
				int i,p,account_id,char_id;
				if(RFIFOREST(fd)<4)
					return 0;
				if(RFIFOREST(fd)<RFIFOW(fd,2))
					return 0;
				account_id = RFIFOL(fd,4);
				char_id    = RFIFOL(fd,8);
				memset(&reg, 0, sizeof(reg));
				for(i=0,p=12; p<RFIFOW(fd,2) && i<GLOBAL_REG_NUM ;i++,p+=36) {
					strncpy(reg[i].str,RFIFOP(fd,p),32);
					reg[i].str[31] = '\0';	// force \0 terminal
					reg[i].value   = RFIFOL(fd,p+32);
				}
				char_save_reg(account_id,char_id,i,reg);
				RFIFOSKIP(fd,RFIFOW(fd,2));
			}
			break;

		// ランキングデータ取得要求
		case 0x2b2e:
			if(RFIFOREST(fd) < 2)
				return 0;
			{
				int i;
				for(i=0; i<MAX_RANKING; i++) {
					int len = char_set_ranking_send(i,WFIFOP(fd,0));
					WFIFOSET(fd,len);
				}
				RFIFOSKIP(fd,2);
			}
			break;

		// ランキングデータ更新
		case 0x2b2f:
			if(RFIFOREST(fd) < 4 || RFIFOREST(fd) < RFIFOW(fd,2))
				return 0;
			{
				int len;
				int ranking_id = (int)RFIFOW(fd,4);
				char buf[6+MAX_RANKER*32];

				char_ranking_update(ranking_id,(int)RFIFOW(fd,6),(struct Ranking_Data *)RFIFOP(fd,8));

				// 全MAPサーバにデータをフラッシュ
				len = char_set_ranking_send(ranking_id,buf);
				mapif_sendall(buf,len);

				RFIFOSKIP(fd,RFIFOW(fd,2));
			}
			break;

		default:
			// inter server処理に渡す
			{
				int r=inter_parse_frommap(fd);
				if( r==1 )	break;		// 処理できた
				if( r==2 )	return 0;	// パケット長が足りない
			}

			// inter server処理でもない場合は切断
			printf("char: unknown packet %x! (from map)\n",RFIFOW(fd,0));
			close(fd);
			session[fd]->eof=1;
			return 0;
		}
	}

	return 0;
}

// char_mapifの初期化処理（現在はinter_mapif初期化のみ）
static int char_mapif_init(int fd)
{
	return inter_mapif_init(fd);
}

int parse_char_disconnect(int fd)
{
	if (fd == login_fd)
		login_fd = -1;

	return 0;
}

// 他マップにログインしているキャラクター情報を送信する
static int parse_char_sendonline(void *key,void *data,va_list ap)
{
	int fd = va_arg(ap,int);
	struct char_online *c = (struct char_online*)data;

	WFIFOW(fd, 0) = 0x2b09;
	WFIFOL(fd, 2) = c->char_id;
	memcpy(WFIFOP(fd,6),c->name,24);
	WFIFOL(fd,30) = c->account_id;
	WFIFOL(fd,34) = c->ip;
	WFIFOW(fd,38) = c->port;
	WFIFOSET(fd,40);

	return 0;
}

int parse_char(int fd)
{
	int i,ch;
	unsigned short cmd;
	struct char_session_data *sd;

	if (login_fd < 0) {
		session[fd]->eof = 1;
		return 0;
	}

	sd = (struct char_session_data *)session[fd]->session_data;

	while(RFIFOREST(fd)>=2){
		cmd = RFIFOW(fd,0);
		// crc32のスキップ用
		if( sd == NULL &&					// 未ログインor管理パケット
		    RFIFOREST(fd) >= 4 &&				// 最低バイト数制限 ＆ 0x7530,0x7532管理パケ除去
		    RFIFOREST(fd) <= 21 &&				// 最大バイト数制限 ＆ サーバーログイン除去
		    cmd != 0x20b &&					// md5通知パケット除去
		    cmd != 0x228 &&
		    cmd != 0x2b2a &&					// map鯖暗号化ログイン除去
		    (RFIFOREST(fd) < 6 || RFIFOW(fd,4) == 0x65) )	// 次に何かパケットが来てるなら、接続でないとだめ
		{
			RFIFOSKIP(fd,4);
			cmd = RFIFOW(fd,0);
			//printf("parse_char : %d crc32 skipped\n",fd);
			if(RFIFOREST(fd)==0)
				return 0;
		}

		//if(cmd<30000 && cmd!=0x187)
		//	printf("parse_char : %d %d %d\n",fd,RFIFOREST(fd),cmd);

		// 不正パケットの処理
		if( sd == NULL && cmd != 0x65 && cmd != 0x20b && cmd != 0x187 && cmd != 0x258 && cmd != 0x228 &&
		    cmd != 0x2af8 && cmd != 0x7530 && cmd != 0x7532 && cmd != 0x2b2a && cmd != 0x2b2c )
			cmd = 0xffff;	// パケットダンプを表示させる

		switch(cmd) {
		case 0x20b:		// 20040622暗号化ragexe対応
			if(RFIFOREST(fd)<19)
				return 0;
			RFIFOSKIP(fd,19);
			break;

		case 0x258:		// 20051214 nProtect関係 Part 1
			memset(WFIFOP(fd,0),0,18);
			WFIFOW(fd,0)=0x0227;
			WFIFOSET(fd,18);
			RFIFOSKIP(fd,2);
			break;

		case 0x228:		// 20051214 nProtect関係 Part 2
			if(RFIFOREST(fd)<18)
				return 0;
			WFIFOW(fd,0)=0x0259;
			WFIFOB(fd,2)=2;
			WFIFOSET(fd,3);
			RFIFOSKIP(fd,18);
			break;

		case 0x65:	// 接続要求
			if(RFIFOREST(fd)<17)
				return 0;
			if(sd == NULL) {
				session[fd]->session_data = aCalloc(1,sizeof(*sd));
				sd = (struct char_session_data *)session[fd]->session_data;
			}
			sd->account_id = RFIFOL(fd,2);
			sd->login_id1  = RFIFOL(fd,6);
			sd->login_id2  = RFIFOL(fd,10);
			sd->sex        = RFIFOB(fd,16);
			sd->state      = CHAR_STATE_WAITAUTH;

			WFIFOL(fd,0) = RFIFOL(fd,2);
			WFIFOSET(fd,4);

			for(i=0; i<AUTH_FIFO_SIZE; i++) {
				if( cmp_authfifo(i,sd->account_id,sd->login_id1,sd->login_id2,session[fd]->client_addr.sin_addr.s_addr) &&
				    auth_fifo[i].delflag == 2 )
				{
					auth_fifo[i].delflag = 1;
					sd->account_id       = auth_fifo[i].account_id;
					sd->login_id1        = auth_fifo[i].login_id1;
					sd->login_id2        = auth_fifo[i].login_id2;
					break;
				}
			}
			if(i >= AUTH_FIFO_SIZE) {
				if(login_fd >= 0 && session[login_fd])
				{
					WFIFOW(login_fd, 0)=0x2712;
					WFIFOL(login_fd, 2)=sd->account_id;
					WFIFOL(login_fd, 6)=sd->login_id1;
					WFIFOL(login_fd,10)=sd->login_id2;
					WFIFOB(login_fd,14)=sd->sex;
					WFIFOL(login_fd,15)=session[fd]->client_addr.sin_addr.s_addr;
					WFIFOL(login_fd,19)=sd->account_id;
					WFIFOSET(login_fd,23);
				}
			} else {
				if(char_maintenance && isGM(sd->account_id) == 0) {
					close(fd);
					session[fd]->eof = 1;
					return 0;
				}
				if(max_connect_user > 0) {
					if(count_users() < max_connect_user  || isGM(sd->account_id) > 0) {
						mmo_char_send006b(fd,sd);
					} else {
						WFIFOW(fd,0)=0x6c;
						WFIFOW(fd,2)=0;
						WFIFOSET(fd,3);
					}
				} else {
					mmo_char_send006b(fd,sd);
				}
			}
			RFIFOSKIP(fd,17);
			break;

		case 0x66:	// キャラ選択
			if(RFIFOREST(fd)<3)
				return 0;
			{
				struct char_online *c;
				struct mmo_charstatus st;

				for(ch=0; ch<max_char_slot; ch++) {
					if(sd->found_char[ch] && sd->found_char[ch]->st.char_num == RFIFOB(fd,2))
						break;
				}
				RFIFOSKIP(fd,3);
				if(ch == max_char_slot)
					break;

				char_log("char select %d-%d %s",sd->account_id,RFIFOB(fd,2),sd->found_char[ch]->st.name);
				memcpy(&st,&sd->found_char[ch]->st,sizeof(struct mmo_charstatus));

				i = search_mapserver_char(st.last_point.map, NULL);
				if(i < 0) {
					if(default_map_type & 1) {
						memcpy(st.last_point.map,default_map_name,16);
						i = search_mapserver_char(st.last_point.map,NULL);
					}
					if(default_map_type & 2 && i < 0) {
						i = search_mapserver_char(st.last_point.map,&st);
					}
					if(i >= 0) {
						// 現在地が書き換わったので上書き
						char_save(&st);
					}
				}
				if(strstr(st.last_point.map,".gat") == NULL) {
					strcat(st.last_point.map,".gat");
					char_save(&st);
				}
				if(i < 0 || server[i].active == 0) {
					WFIFOW(fd,0)=0x6c;
					WFIFOW(fd,2)=0;
					WFIFOSET(fd,3);
					break;
				}
				// ２重ログイン撃退（違うマップサーバの場合）
				// 同じマップサーバの場合は、マップサーバー内で処理される
				c = (struct char_online *)numdb_search(char_online_db,sd->found_char[ch]->st.account_id);
				if( c && (c->ip != server[i].ip || c->port != server[i].port) ) {
					// ２重ログイン検出
					// mapに切断要求
					unsigned char buf[8];
					WBUFW(buf,0) = 0x2b1a;
					WBUFL(buf,2) = sd->account_id;
					mapif_sendall(buf,6);

					// 接続失敗送信
					WFIFOW(fd,0) = 0x6c;
					WFIFOW(fd,2) = 0;
					WFIFOSET(fd,3);
					break;
				}

				WFIFOW(fd,0) = 0x71;
				WFIFOL(fd,2) = st.char_id;
				memcpy(WFIFOP(fd,6),st.last_point.map,16);
				WFIFOL(fd,22) = server[i].ip;
				WFIFOW(fd,26) = server[i].port;
				WFIFOSET(fd,28);

				// 同一アカウントの未認証データを全て破棄しておく
				for(i=0; i<AUTH_FIFO_SIZE; i++) {
					if(auth_fifo[i].account_id == sd->account_id && !auth_fifo[i].delflag) {
						auth_fifo[i].delflag = 1;
					}
				}
				if(auth_fifo_pos >= AUTH_FIFO_SIZE) {
					auth_fifo_pos = 0;
				}
				//printf("auth_fifo set 0x66 %d - %08x %08x %08x %08x\n",
				//	auth_fifo_pos,sd->account_id,st.char_id,sd->login_id1,sd->login_id2);
				auth_fifo[auth_fifo_pos].account_id = sd->account_id;
				auth_fifo[auth_fifo_pos].char_id    = st.char_id;
				auth_fifo[auth_fifo_pos].login_id1  = sd->login_id1;
				auth_fifo[auth_fifo_pos].login_id2  = sd->login_id2;
				auth_fifo[auth_fifo_pos].delflag    = 0;
				auth_fifo[auth_fifo_pos].sex        = sd->sex;
				auth_fifo_pos++;
			}
			break;

		case 0x67:	// 作成
			if(RFIFOREST(fd)<37)
				return 0;
			{
				int flag=0x00;
				const struct mmo_chardata *cd = char_make(sd,RFIFOP(fd,2),&flag);
				const struct mmo_charstatus *st;
				struct global_reg reg[ACCOUNT_REG2_NUM];
#if PACKETVER >= 8
				int len = 108;
#else
				int len = 106;
#endif
				if(cd == NULL){
					WFIFOW(fd,0)=0x6e;
					WFIFOB(fd,2)=flag;
					WFIFOSET(fd,3);
					RFIFOSKIP(fd,37);
					break;
				}

				st = &cd->st;
				memset(WFIFOP(fd,2),0x00,len);
				WFIFOW(fd,0)     = 0x6d;
				WFIFOL(fd,2    ) = st->char_id;
				WFIFOL(fd,2+  4) = st->base_exp;
				WFIFOL(fd,2+  8) = st->zeny;
				WFIFOL(fd,2+ 12) = st->job_exp;
				WFIFOL(fd,2+ 16) = st->job_level;
				WFIFOL(fd,2+ 28) = st->karma;
				WFIFOL(fd,2+ 32) = st->manner;
				WFIFOW(fd,2+ 40) = 0x30;
				WFIFOW(fd,2+ 42) = (st->hp     > 0x7fff) ? 0x7fff : st->hp;
				WFIFOW(fd,2+ 44) = (st->max_hp > 0x7fff) ? 0x7fff : st->max_hp;
				WFIFOW(fd,2+ 46) = (st->sp     > 0x7fff) ? 0x7fff : st->sp;
				WFIFOW(fd,2+ 48) = (st->max_sp > 0x7fff) ? 0x7fff : st->max_sp;
				WFIFOW(fd,2+ 50) = DEFAULT_WALK_SPEED; // char_dat[i].speed;
				WFIFOW(fd,2+ 52) = st->class_;
				WFIFOW(fd,2+ 54) = st->hair;
				WFIFOW(fd,2+ 58) = st->base_level;
				WFIFOW(fd,2+ 60) = st->skill_point;
				WFIFOW(fd,2+ 64) = st->shield;
				WFIFOW(fd,2+ 66) = st->head_top;
				WFIFOW(fd,2+ 68) = st->head_mid;
				WFIFOW(fd,2+ 70) = st->hair_color;
				memcpy( WFIFOP(fd,2+74), st->name, 24 );
				WFIFOB(fd,2+ 98) = (st->str  > 255) ? 255 : st->str;
				WFIFOB(fd,2+ 99) = (st->agi  > 255) ? 255 : st->agi;
				WFIFOB(fd,2+100) = (st->vit  > 255) ? 255 : st->vit;
				WFIFOB(fd,2+101) = (st->int_ > 255) ? 255 : st->int_;
				WFIFOB(fd,2+102) = (st->dex  > 255) ? 255 : st->dex;
				WFIFOB(fd,2+103) = (st->luk  > 255) ? 255 : st->luk;
				WFIFOW(fd,2+104) = st->char_num;
				if(len >= 108)
					WFIFOW(fd,2+106) = 1;
				WFIFOSET(fd,len+2);
				RFIFOSKIP(fd,37);

				for(ch=0;ch<max_char_slot;ch++) {
					if(sd->found_char[ch] == NULL) {
						sd->found_char[ch] = cd;
						break;
					}
				}
				// ##変数を再設定する
				i = get_account_reg2(sd,reg);
				if(i > 0)
					set_account_reg2(sd->account_id,i,reg);
			}

		case 0x68:	// 削除
			if(RFIFOREST(fd)<46)
				return 0;
			if (login_fd >= 0) {
				WFIFOW(login_fd,0)=0x2715;
				WFIFOL(login_fd,2)=sd->account_id;
				WFIFOL(login_fd,6)=RFIFOL(fd,2);
				memcpy(WFIFOP(login_fd,10), RFIFOP(fd,6), 40);
				WFIFOSET(login_fd,50);
			}
			RFIFOSKIP(fd,46);
			break;

		case 0x2b2a:	// マップサーバー暗号化ログインのチャレンジ要求
			RFIFOSKIP(fd, 2);
			if(sd) {
				printf("char: illegal md5key request.");
				close(fd);
				session[fd]->eof=1;
				return 0;
			} else {
				struct cram_session_data *csd=(struct cram_session_data *)(session[fd]->session_data=aCalloc(1,sizeof(struct cram_session_data)));

				// 暗号化用のチャレンジ生成
				csd->md5keylen = atn_rand()%(sizeof(csd->md5key)/4)+(sizeof(csd->md5key)-sizeof(csd->md5key)/4);
				for(i=0;i<csd->md5keylen;i++)
					csd->md5key[i]=atn_rand()%255+1;

				WFIFOW(fd,0)= 0x2b2b;
				WFIFOW(fd,2)=4+csd->md5keylen;
				memcpy(WFIFOP(fd,4),csd->md5key,csd->md5keylen);
				WFIFOSET(fd,WFIFOW(fd,2));
			}
			break;

		case 0x2af8:	// マップサーバーログイン (map-server connection)
		case 0x2b2c:	// マップサーバー暗号化ログイン
		{
			int authok=0;
			struct cram_session_data *csd=(struct cram_session_data *)(session[fd]->session_data);
			if (RFIFOREST(fd) < 60)
				return 0;
			if (char_sport != 0 && char_port != char_sport && session[fd]->server_port != char_sport) {
				printf("server login failed: connected port %d\n", session[fd]->server_port);
				session[fd]->eof = 1;
				RFIFOSKIP(fd,60);
				return 0;
			}
			// search an available place
			for(i = 0; i < MAX_MAP_SERVERS; i++) {
				if (server_fd[i] < 0)
					break;
			}
			// 暗号化ログイン
			if( RFIFOW(fd,0)==0x2b2c )
			{
				if( RFIFOW(fd,46) == 4 && csd && csd->md5keylen )	// HMAC-MD5
				{
					char md5bin[16];
					HMAC_MD5_Binary( passwd, strlen(passwd), csd->md5key, csd->md5keylen, md5bin );
					authok = ( memcmp( md5bin, RFIFOP(fd,26), 16 ) == 0 );
				}
			}
			else
			{
				authok = (strcmp(RFIFOP(fd,26), passwd) == 0 );
			}
			// いらないセッション情報は削除
			if( sd )
			{
				aFree( csd );
				session[fd]->session_data = NULL;
			}
			if (i == MAX_MAP_SERVERS || strcmp(RFIFOP(fd,2), userid) || !authok ) {
				WFIFOW(fd,0)=0x2af9;
				WFIFOB(fd,2)=3;
				WFIFOSET(fd,3);
				RFIFOSKIP(fd,60);
			} else {
				WFIFOW(fd,0)=0x2af9;
				WFIFOB(fd,2)=0;
				session[fd]->func_parse = parse_frommap;
				session[fd]->func_destruct = parse_map_disconnect;
				server_fd[i] = fd;
				server[i].ip = RFIFOL(fd,54);
				server[i].port = RFIFOW(fd,58);
				server[i].users = 0;
				server[i].map_num = 0;
				if (server[i].map != NULL) {
					aFree(server[i].map);
					server[i].map = NULL;
				}
				WFIFOSET(fd,3);
				numdb_foreach(char_online_db,parse_char_sendonline,fd);
				RFIFOSKIP(fd,60);
				session[fd]->auth = -1; // 認証終了を socket.c に伝える
				realloc_fifo(fd, RFIFOSIZE_SERVERLINK, WFIFOSIZE_SERVERLINK);
				char_mapif_init(fd);
				return 0;
			}
			break;
		}

		case 0x187:	// Alive信号？
			if (RFIFOREST(fd) < 6)
				return 0;
			WFIFOW(fd,0)=0x187;
			WFIFOL(fd,2)=sd->account_id;
			WFIFOSET(fd,6);
			RFIFOSKIP(fd, 6);
			break;

		case 0x7530:	// Auriga情報取得
			WFIFOW(fd,0)=0x7531;
			WFIFOB(fd,2)=AURIGA_MAJOR_VERSION;
			WFIFOB(fd,3)=AURIGA_MINOR_VERSION;
			WFIFOW(fd,4)=AURIGA_REVISION;
			WFIFOB(fd,6)=AURIGA_RELEASE_FLAG;
			WFIFOB(fd,7)=AURIGA_OFFICIAL_FLAG;
			WFIFOB(fd,8)=AURIGA_SERVER_INTER | AURIGA_SERVER_CHAR;
			WFIFOB(fd,9)=AURIGA_MOD_VERSION;
			WFIFOSET(fd,10);
			RFIFOSKIP(fd,2);
			return 0;
		case 0x7532:	// 接続の切断(defaultと処理は一緒だが明示的にするため)
			RFIFOSKIP(fd,2);
			close(fd);
			session[fd]->eof=1;
			return 0;

		default:
#ifdef DUMP_UNKNOWN_PACKET
			{
				int i;
				printf("---- 00-01-02-03-04-05-06-07-08-09-0A-0B-0C-0D-0E-0F");
				for(i=0;i<RFIFOREST(fd);i++){
					if((i&15)==0)
						printf("\n%04X ",i);
					printf("%02X ",RFIFOB(fd,i));
				}
				printf("\n");
			}
#endif
			close(fd);
			session[fd]->eof=1;
			return 0;
		}
	}

	return 0;
}

// 全てのMAPサーバーにデータ送信（送信したmap鯖の数を返す）
int mapif_sendall(unsigned char *buf,unsigned int len)
{
	int i, c = 0;

	for(i = 0; i < MAX_MAP_SERVERS; i++) {
		int fd;
		if ((fd = server_fd[i]) >= 0) {
			memcpy(WFIFOP(fd,0), buf, len);
			WFIFOSET(fd, len);
			c++;
		}
	}

	return c;
}

// 自分以外の全てのMAPサーバーにデータ送信（送信したmap鯖の数を返す）
int mapif_sendallwos(int sfd,unsigned char *buf,unsigned int len)
{
	int i, c = 0;

	for(i = 0; i < MAX_MAP_SERVERS; i++) {
		int fd;
		if ((fd = server_fd[i]) >= 0 && fd != sfd) {
			memcpy(WFIFOP(fd,0), buf, len);
			WFIFOSET(fd, len);
			c++;
		}
	}

	return c;
}

// MAPサーバーにデータ送信（map鯖生存確認有り）
int mapif_send(int fd,unsigned char *buf,unsigned int len)
{
	int i;

	for(i = 0; i < MAX_MAP_SERVERS; i++) {
		if (fd == server_fd[i]) {
			memcpy(WFIFOP(fd,0), buf, len);
			WFIFOSET(fd, len);
			return 1;
		}
	}

	return 0;
}

void mapif_parse_CharConnectLimit(int fd)
{
	int limit = RFIFOL(fd,2);

	if (limit < 0)
		limit = 0;
	printf("char:max_connect_user change %d->%d\n", max_connect_user, limit);
	max_connect_user = limit;

	return;
}

int send_users_tologin(int tid,unsigned int tick,int id,int data)
{
	if (login_fd >= 0 && session[login_fd] && session[login_fd]->auth) {
		int i, users = 0;

		for(i = 0; i < MAX_MAP_SERVERS; i++) {
			if (server_fd[i] >= 0)
				users += server[i].users;
		}

		WFIFOW(login_fd,0) = 0x2714;
		WFIFOL(login_fd,2) = users;
		WFIFOSET(login_fd,6);

		for(i = 0; i < MAX_MAP_SERVERS; i++) {
			int fd;
			if ((fd = server_fd[i]) >= 0) {
				WFIFOW(fd,0) = 0x2b00;
				WFIFOL(fd,2) = users;
				WFIFOSET(fd,6);
			}
		}
	}

	return 0;
}

static int check_connect_login_server(int tid,unsigned int tick,int id,int data)
{
	if (login_fd < 0 || session[login_fd] == NULL) {
		login_fd = make_connection(login_ip, login_port);
		if (login_fd < 0) {
			if (char_loginaccess_autorestart >= 1)
				exit(1);
			return 0;
		}
		session[login_fd]->func_parse=parse_tologin;
		session[login_fd]->func_destruct = parse_login_disconnect;
		realloc_fifo(login_fd, RFIFOSIZE_SERVERLINK, WFIFOSIZE_SERVERLINK);

		// 暗号化ログインのチャレンジ要求
		WFIFOW(login_fd,0)=0x272d;
		WFIFOSET(login_fd,2);

		/* プレーンなログインは現在廃止 */
		//WFIFOW(login_fd,0)=0x2710;
		//memcpy(WFIFOP(login_fd,2),userid,24);
		//memcpy(WFIFOP(login_fd,26),passwd,24);
		//WFIFOL(login_fd,50)=0;
		//WFIFOL(login_fd,54)=char_ip;
		//WFIFOW(login_fd,58)=char_port;
		//memcpy(WFIFOP(login_fd,60),server_name,20);
		//WFIFOW(login_fd,80)=char_maintenance;
		//WFIFOW(login_fd,82)=char_new;
		//WFIFOSET(login_fd,84);
	}

	return 0;
}

static void char_config_read(const char *cfgName)
{
	struct hostent *h = NULL;
	char line[1024], w1[1024], w2[1024];
	FILE *fp;

	fp = fopen(cfgName, "r");
	if (fp == NULL) {
		printf("file not found: %s\n", cfgName);
		return;
	}

	while(fgets(line, sizeof(line) - 1, fp)) {
		if (line[0] == '/' && line[1] == '/')
			continue;

		if (sscanf(line,"%[^:]: %[^\r\n]", w1, w2) != 2)
			continue;

		if (strcmpi(w1, "userid") == 0) {
			memcpy(userid, w2, 24);
			userid[23] = '\0';
		} else if (strcmpi(w1, "passwd") == 0) {
			memcpy(passwd ,w2, 24);
			passwd[23] = '\0';
		} else if (strcmpi(w1, "server_name") == 0) {
			memcpy(server_name, w2, 20);
			server_name[19] = '\0';
		} else if (strcmpi(w1, "login_ip") == 0) {
			h = gethostbyname(w2);
			if (h != NULL) {
				sprintf(login_ip_str, "%d.%d.%d.%d", (unsigned char)h->h_addr[0], (unsigned char)h->h_addr[1], (unsigned char)h->h_addr[2], (unsigned char)h->h_addr[3]);
				printf("Login server IP address : %s -> %s\n", w2, login_ip_str);
			} else {
				memcpy(login_ip_str, w2, 16);
				login_ip_str[15] = '\0';
			}
		} else if (strcmpi(w1, "login_port") == 0) {
			int n = atoi(w2);
			if (n < 0 || n > 65535) {
				printf("char_config_read: Invalid login_port value: %d. Set to 6900 (default).\n", n);
				login_port = 6900; // default
			} else {
				login_port = (unsigned short)n;
			}
		} else if (strcmpi(w1, "char_ip") == 0) {
			h = gethostbyname(w2);
			if (h != NULL) {
				sprintf(char_ip_str, "%d.%d.%d.%d", (unsigned char)h->h_addr[0], (unsigned char)h->h_addr[1], (unsigned char)h->h_addr[2], (unsigned char)h->h_addr[3]);
				printf("Character server IP address : %s -> %s\n", w2, char_ip_str);
			} else {
				memcpy(char_ip_str, w2, 16);
				char_ip_str[15] = '\0';
			}
		} else if (strcmpi(w1, "char_port") == 0) {
			int n = atoi(w2);
			if (n < 0 || n > 65535) {
				printf("char_config_read: Invalid char_port value: %d. Set to 6121 (default).\n", n);
				char_port = 6121; // default
			} else {
				char_port = (unsigned short)n;
			}
		} else if (strcmpi(w1, "listen_ip") == 0) {
			unsigned long ip_result;
			h = gethostbyname(w2);
			if (h != NULL)
				sprintf(w2, "%d.%d.%d.%d", (unsigned char)h->h_addr[0], (unsigned char)h->h_addr[1], (unsigned char)h->h_addr[2], (unsigned char)h->h_addr[3]);
			if ((ip_result = inet_addr(w2)) == INADDR_NONE) // not always -1
				printf("char_config_read: Invalid listen_ip value: %s.\n", w2);
			else
				listen_ip = ip_result;
		} else if (strcmpi(w1, "char_sip") == 0) {
			h = gethostbyname(w2);
			if (h != NULL) {
				sprintf(char_sip_str, "%d.%d.%d.%d", (unsigned char)h->h_addr[0], (unsigned char)h->h_addr[1], (unsigned char)h->h_addr[2], (unsigned char)h->h_addr[3]);
				printf("Character server sIP address : %s -> %s\n", w2, char_sip_str);
			} else {
				memcpy(char_sip_str, w2, 16);
				char_sip_str[15] = '\0';
			}
			char_sip = inet_addr(char_sip_str);
		} else if (strcmpi(w1, "char_sport") == 0) {
			int n = atoi(w2);
			if (n< 0 || n > 65535) {
				printf("char_config_read: Invalid char_sport value: %d. Set to 0 (default).\n", n);
				char_sport = 0;
			} else {
				char_sport = (unsigned short)n;
			}
		} else if (strcmpi(w1, "char_maintenance") == 0) {
			char_maintenance = atoi(w2);
		} else if (strcmpi(w1, "char_loginaccess_autorestart") == 0) {
			char_loginaccess_autorestart = atoi(w2);
		} else if (strcmpi(w1, "char_new")==0){
			char_new = atoi(w2);
		} else if (strcmpi(w1, "max_connect_user") == 0) {
			max_connect_user = atoi(w2);
			if (max_connect_user < 0) {
				printf("char_config_read: Invalid max_connect_user value: %d. Set to 0 (default).\n", max_connect_user);
				max_connect_user = 0;
			}
		} else if (strcmpi(w1, "autosave_time") == 0) {
			autosave_interval = atoi(w2) * 1000;
			if (autosave_interval <= 0)
				autosave_interval = DEFAULT_AUTOSAVE_INTERVAL_CS;
		} else if (strcmpi(w1, "start_point") == 0) {
			char map[1024];
			int x, y;
			if (sscanf(w2, "%[^,],%d,%d", map, &x, &y) < 3)
				continue;
			memcpy(start_point.map, map, 16);
			start_point.map[15] = '\0';
			start_point.x       = x;
			start_point.y       = y;
		} else if (strcmpi(w1, "start_zeny") == 0) {
			start_zeny = atoi(w2);
			if (start_zeny < 0) {
				printf("char_config_read: Invalid start_zeny value: %d. Set to 0 (default).\n", start_zeny);
				start_zeny = 0;
			}
		} else if (strcmpi(w1, "start_weapon") == 0) {
			start_weapon = atoi(w2);
		} else if (strcmpi(w1, "start_armor") == 0) {
			start_armor = atoi(w2);
		} else if (strcmpi(w1, "unknown_char_name") == 0) {
			strncpy(unknown_char_name, w2, 24);
			unknown_char_name[23] = '\0';
		} else if (strcmpi(w1, "char_log_filename") == 0) {
			strncpy(char_log_filename, w2, sizeof(char_log_filename) -1);
			char_log_filename[sizeof(char_log_filename) -1] = '\0';
		} else if (strcmpi(w1, "default_map_type") == 0) {
			default_map_type = atoi(w2);
		} else if (strcmpi(w1, "default_map_name") == 0) {
			strncpy(default_map_name, w2, 16);
			default_map_name[15] = '\0';
		} else if (strcmpi(w1, "max_char_slot") == 0) {
			max_char_slot = atoi(w2);
			if (max_char_slot <= 0 || max_char_slot > 9) {
				printf("char_config_read: Invalid max_char_slot value: %d. Set to 9 (default).\n", max_char_slot);
				max_char_slot = 9;
			}
		} else if (strcmpi(w1, "httpd_enable") == 0) {
			socket_enable_httpd(atoi(w2));
		} else if (strcmpi(w1, "httpd_document_root") == 0) {
			httpd_set_document_root(w2);
		} else if (strcmpi(w1, "httpd_log_filename") == 0) {
			httpd_set_logfile(w2);
		} else if (strcmpi(w1, "httpd_config") == 0) {
			httpd_config_read(w2);
		} else if (strcmpi(w1, "import") == 0) {
			char_config_read(w2);
		} else {
			char_config_read_sub(w1, w2);
		}
	}
	fclose(fp);

	return;
}

static void char_socket_ctrl_panel_func(int fd,char* usage,char* user,char* status)
{
	struct socket_data *sd = session[fd];
	struct char_session_data *cd = (struct char_session_data *)sd->session_data;

	strcpy( usage,
		( sd->func_parse == parse_char )? "char user" :
		( sd->func_parse == parse_tologin )? "login server" :
		( sd->func_parse == parse_frommap)? "map server" : "unknown" );

	if( sd->func_parse == parse_tologin )
	{
		strcpy( user, userid );
	}
	else if( sd->func_parse == parse_char && sd->auth )
	{
		sprintf( user, "%d", cd->account_id );
	}

	return;
}

static int gm_account_db_final(void *key,void *data,va_list ap)
{
	struct gm_account *p = (struct gm_account *)data;

	aFree(p);

	return 0;
}

static int char_online_db_final(void *key,void *data,va_list ap)
{
	struct char_online *p = (struct char_online *)data;

	aFree(p);

	return 0;
}

void do_pre_final(void)
{
	// nothing to do
	return;
}

void do_final(void)
{
	int i;

	char_set_offline(-1);

	char_sync();
	inter_sync();
	do_final_inter();
	pet_final();
	homun_final();
	guild_final();
	party_final();
	storage_final();
	gstorage_final();
	mail_final();
	status_final();
	if(gm_account_db)
		numdb_final(gm_account_db,gm_account_db_final);
	delete_session(login_fd);
	delete_session(char_fd);
	if(char_sport != 0 && char_port != char_sport)
		delete_session(char_sfd);
	for(i = 0; i < MAX_MAP_SERVERS; i++) {
		if (server_fd[i] >= 0)
			delete_session(server_fd[i]);
	}
	numdb_final(char_online_db,char_online_db_final);
	char_final();
	exit_dbn();
	do_final_timer();

	return;
}

int do_init(int argc,char **argv)
{
	int i;

	printf("Auriga Char Server [%s] v%d.%d.%d mod%d\n",
#ifdef TXT_ONLY
		"TXT",
#else
		"SQL",
#endif
		AURIGA_MAJOR_VERSION,AURIGA_MINOR_VERSION,AURIGA_REVISION,
		AURIGA_MOD_VERSION
	);

	for(i = 1; i < argc - 1; i += 2) {
		if(strcmp(argv[i], "--char_config") == 0 || strcmp(argv[i], "--char-config") == 0) {
			strncpy(char_conf_filename, argv[i+1], sizeof(char_conf_filename));
			char_conf_filename[sizeof(char_conf_filename)-1] = '\0';
		}
		else if(strcmp(argv[i], "--inter_config") == 0 || strcmp(argv[i], "--inter-config") == 0) {
			strncpy(inter_conf_filename, argv[i+1], sizeof(inter_conf_filename));
			inter_conf_filename[sizeof(inter_conf_filename)-1] = '\0';
		}
		else {
			printf("illegal command line argument %s !!\n", argv[i]);
			exit(1);
		}
	}

	char_config_read(char_conf_filename);

	login_ip = inet_addr(login_ip_str);
	char_ip  = inet_addr(char_ip_str);

	for(i = 0; i < MAX_MAP_SERVERS; i++) {
		server_fd[i] = -1;
		memset(&server[i], 0, sizeof(struct mmo_map_server));
	}
	char_online_db = numdb_init();
	char_init();
	char_build_ranking();
	read_gm_account();
	inter_init(inter_conf_filename);	// inter server 初期化

	set_defaultparse(parse_char);
	set_sock_destruct(parse_char_disconnect);
	socket_set_httpd_page_connection_func( char_socket_ctrl_panel_func );

	char_fd = make_listen_port(char_port, listen_ip);
	if (char_sport != 0 && char_port != char_sport)
		char_sfd = make_listen_port(char_sport, char_sip);

	add_timer_func_list(check_connect_login_server,"check_connect_login_server");
	add_timer_func_list(send_users_tologin,"send_users_tologin");
	add_timer_func_list(mmo_char_sync_timer,"mmo_char_sync_timer");

	add_timer_interval(gettick()+1000,check_connect_login_server,0,0,10*1000);
	add_timer_interval(gettick()+1000,send_users_tologin,0,0,5*1000);
	add_timer_interval(gettick()+autosave_interval,mmo_char_sync_timer,0,0,autosave_interval);

	// for httpd support
	do_init_httpd();
	do_init_graph();
	graph_add_sensor("Uptime(days)",60*1000,uptime);
	graph_add_sensor("Memory Usage(KB)",60*1000,memmgr_usage);
	httpd_default_page(httpd_send_file);

	char_set_offline(-1);

	return 0;
}
