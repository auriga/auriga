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

//#define DEBUG_FUNCIN
//#define DEBUG_DISP

// コンバートされた中間言語を表示
//#define DEBUG_DISASM

// 実行過程を表示
//#define DEBUG_RUN

// ハッシュの計算結果を出力
//#define DEBUG_HASH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#ifndef WINDOWS
	#include <sys/time.h>
#endif
#include <time.h>
#include <math.h>
#include <setjmp.h>

#include "db.h"
#include "socket.h"
#include "timer.h"
#include "malloc.h"
#include "mmo.h"
#include "nullpo.h"
#include "utils.h"
#include "sqldbs.h"

#include "map.h"
#include "guild.h"
#include "clif.h"
#include "chrif.h"
#include "itemdb.h"
#include "pc.h"
#include "bonus.h"
#include "script.h"
#include "script_internal.h"
#include "storage.h"
#include "mob.h"
#include "npc.h"
#include "pet.h"
#include "intif.h"
#include "skill.h"
#include "chat.h"
#include "battle.h"
#include "party.h"
#include "path.h"
#include "atcommand.h"
#include "status.h"
#include "itemdb.h"
#include "unit.h"
#include "homun.h"
#include "merc.h"
#include "quest.h"
#include "buyingstore.h"
#include "memorial.h"
#include "achieve.h"

#define SCRIPT_BLOCK_SIZE 512

enum { LABEL_NEXTLINE = 1, LABEL_START };

static unsigned char * script_buf = NULL;
static int script_pos,script_size;

static struct script_str_data {
	int type;
	size_t str;
	int backpatch;
	int label;
	int (*func)(struct script_state *st);
	union {
		int val;
		char *str;
	} u;
	int next;
} *str_data;

static char *str_buf;
static int str_num = LABEL_START, str_data_size;

#define SCRIPT_HASH_SIZE 1571
int str_hash[SCRIPT_HASH_SIZE];

#define MAPREG_AUTOSAVE_INTERVAL	(300*1000)
static int mapreg_autosave_interval = MAPREG_AUTOSAVE_INTERVAL;

struct linkdb_node *scriptlabel_db = NULL;
static struct dbt *userfunc_db = NULL;

char refine_posword[EQUIP_INDEX_MAX + 1][32] = {
	"頭", "体", "左手", "右手", "ローブ", "靴", "アクセサリー1", "アクセサリー2", "頭2", "頭3",	"矢",
	"コスチューム上段", "コスチューム中段", "コスチューム下段", "コスチューム肩", "コスチュームFloor",
	"アーマーシャドウ", "ウェポンシャドウ", "シールドシャドウ", "シューズシャドウ", "アクセサリ右シャドウ", "アクセサリ左シャドウ",
	"装着していない"
};

static char error_marker_start[16] = "";
static char error_marker_end[16]   = "";

#ifndef TXT_ONLY

struct sqldbs_handle mysql_handle_script;
static bool sql_is_connect = false;

static unsigned short script_server_port = 3306;
static char script_server_ip[32]      = "127.0.0.1";
static char script_server_id[32]      = "ragnarok";
static char script_server_pw[32]      = "ragnarok";
static char script_server_db[32]      = "ragnarok";
static char script_server_charset[32] = "";
static int  script_server_keepalive   = 0;

#endif /* TXT_ONLY */

static struct Script_Config {
	int warn_func_no_comma;
	int warn_cmd_no_comma;
	int warn_func_mismatch_paramnum;
	int warn_cmd_mismatch_paramnum;
	int check_cmdcount;
	int check_gotocount;
	int debug_vars;
	int debug_mode_log;
	int error_log;
	int sql_script_enable;
} script_config;

static int parse_cmd;

// エラー処理
static jmp_buf error_jump;
static char*   error_msg;
static char*   error_pos;
static struct script_code error_code;	// エラー時のダミーデータ

// if , switch の実装
enum {
	TYPE_NULL = 0,
	TYPE_IF,
	TYPE_SWITCH,
	TYPE_WHILE,
	TYPE_FOR,
	TYPE_DO,
	TYPE_USERFUNC
};

static struct {
	struct {
		int type;
		int index;
		int count;
		int flag;
		struct linkdb_node *case_label;
	} curly[256];		// 右カッコの情報
	int curly_count;	// 右カッコの数
	int index;			// スクリプト内で使用した構文の数
} syntax;

static int parse_syntax_for_flag = 0;

static int vars_count = 0;
static struct dbt* vars_db = NULL;

struct vars_info {
	int use_count;
	char *file;
	int   line;
};

struct script_function {
	int (*func)(struct script_state *st);
	const char *name;
	const char *arg;
} buildin_func[];

struct linkdb_node *sleep_db = NULL;


/*==========================================
 * ローカルプロトタイプ宣言 (必要な物のみ)
 *------------------------------------------
 */
static unsigned char* parse_curly_close(unsigned char *p);
static unsigned char* parse_syntax_close(unsigned char *p);
static unsigned char* parse_syntax(unsigned char *p);

static unsigned char* parse_subexpr(unsigned char *,int);
static int get_com(unsigned char *script,int *pos);
static int get_num(unsigned char *script,int *pos);


/*==========================================
 * ユーザー定義関数の取得
 *------------------------------------------
 */
struct script_code* script_get_userfunc(const char *name)
{
	if(!userfunc_db) {
		userfunc_db = strdb_init(50);
		return NULL;
	}

	return (struct script_code *)strdb_search(userfunc_db, name);
}

/*==========================================
 * ユーザー定義関数の登録
 *------------------------------------------
 */
struct script_code* script_set_userfunc(const char *name, struct script_code *code)
{
	if(!userfunc_db)
		userfunc_db = strdb_init(50);

	return (struct script_code *)strdb_insert(userfunc_db, name, code);
}

/*==========================================
 * エラーメッセージ出力
 *------------------------------------------
 */
static void disp_error_message(const char *mes,unsigned char *pos)
{
	error_msg = (char *)aStrdup(mes);
	error_pos = (char *)pos;
	longjmp( error_jump, 1 );
}

/*==========================================
 * 文字列のハッシュを計算
 *------------------------------------------
 */
static unsigned int calc_hash(const unsigned char *p)
{
	unsigned int h=0;

	// SDBM Algorithm
	while(*p){
		h=(h<<6)+(h<<16)-h;
		h+=(unsigned char)tolower(*p++);
	}
	return h % SCRIPT_HASH_SIZE;
}

/*==========================================
 * str_dataの中に名前があるか検索する
 * 既存のであれば番号、無ければ-1
 *------------------------------------------
 */
static int search_str(const unsigned char *p)
{
	int i = str_hash[calc_hash(p)];

	while(i){
		if(strcmpi(str_buf+str_data[i].str,p)==0){
			return i;
		}
		i=str_data[i].next;
	}
	return -1;
}

/*==========================================
 * str_dataに名前を登録
 * 既存のであれば番号、無ければ登録して新規番号
 *------------------------------------------
 */
int add_str(const unsigned char *p)
{
	static size_t str_pos=0,str_size=0;
	size_t len;
	int i;

	i=calc_hash(p);
	if(str_hash[i]==0){
		str_hash[i]=str_num;
	} else {
		i=str_hash[i];
		for(;;){
			if(strcmpi(str_buf+str_data[i].str,p)==0){
				return i;
			}
			if(str_data[i].next==0)
				break;
			i=str_data[i].next;
		}
		str_data[i].next=str_num;
	}
	if(str_num >= str_data_size){
		str_data_size += 512;
		str_data = (struct script_str_data *)aRealloc(str_data,sizeof(str_data[0])*str_data_size);
		memset(str_data + (str_data_size - 512), '\0', 512);
	}
	len = strlen(p) + 1;
	while(str_pos + len >= str_size) {
		str_size += 4096;
		str_buf = (char *)aRealloc(str_buf,str_size);
		memset(str_buf + (str_size - 4096), '\0', 4096);
	}
	memcpy(str_buf + str_pos, p, len);
	str_data[str_num].type      = C_NOP;
	str_data[str_num].str       = str_pos;
	str_data[str_num].next      = 0;
	str_data[str_num].func      = NULL;
	str_data[str_num].backpatch = -1;
	str_data[str_num].label     = -1;
	str_pos += len;

	return str_num++;
}

/*==========================================
 * str_dataから名前を取得
 *------------------------------------------
 */
char* get_str(int num)
{
	return str_buf+str_data[num&0x00ffffff].str;
}

/*==========================================
 * スクリプトバッファサイズの拡張
 *------------------------------------------
 */
static void expand_script_buf(void)
{
	script_size+=SCRIPT_BLOCK_SIZE;
	script_buf=(unsigned char *)aRealloc(script_buf,script_size);
}

/*==========================================
 * スクリプトバッファに１バイト書き込む
 *------------------------------------------
 */
#define add_scriptb(a) { if( script_pos+1>=script_size ) expand_script_buf(); script_buf[script_pos++]=(a); }

/*==========================================
 * スクリプトバッファにデータタイプを書き込む
 *------------------------------------------
 */
static void add_scriptc(int a)
{
	while(a>=0x40){
		add_scriptb((a&0x3f)|0x40);
		a=(a-0x40)>>6;
	}
	add_scriptb(a&0x3f);
}

/*==========================================
 * スクリプトバッファに整数を書き込む
 *------------------------------------------
 */
static void add_scripti(int a)
{
	while(a>=0x40){
		add_scriptb(a|0xc0);
		a=(a-0x40)>>6;
	}
	add_scriptb(a|0x80);
}

/*==========================================
 * スクリプトバッファにラベル/変数/関数を書き込む
 *------------------------------------------
 */
// 最大16Mまで
static void add_scriptl(int l)
{
	switch(str_data[l].type) {
	case C_POS:
	case C_USERFUNC_POS:
		add_scriptc(C_POS);
		add_scriptb(str_data[l].label);
		add_scriptb(str_data[l].label>>8);
		add_scriptb(str_data[l].label>>16);
		break;
	case C_NOP:
	case C_USERFUNC:
		// ラベルの可能性があるのでbackpatch用データ埋め込み
		{
			int backpatch = str_data[l].backpatch;
			add_scriptc(C_NAME);
			str_data[l].backpatch=script_pos;
			add_scriptb(backpatch);
			add_scriptb(backpatch>>8);
			add_scriptb(backpatch>>16);
		}
		break;
	case C_INT:
		add_scripti(abs(str_data[l].u.val));
		if(str_data[l].u.val < 0)
			add_scriptc(C_NEG);
		break;
	case C_STR:
		{
			char *p = str_data[l].u.str;
			add_scriptc(C_STR);
			while(p && *p) {
				add_scriptb(*p++);
			}
			add_scriptb(0);
		}
		break;
	default:
		// もう他の用途と確定してるので数字をそのまま
		add_scriptc(C_NAME);
		add_scriptb(l);
		add_scriptb(l>>8);
		add_scriptb(l>>16);
		break;
	}
}

/*==========================================
 * ラベルを解決する
 *------------------------------------------
 */
static void set_label(int l,int pos,unsigned char *p)
{
	int i, next;

	if(str_data[l].label != -1) {
		disp_error_message("dup label",p);
	}
	str_data[l].type  = (str_data[l].type == C_USERFUNC) ? C_USERFUNC_POS : C_POS;
	str_data[l].label = pos;

	i = str_data[l].backpatch;
	while(i >= 0 && i != 0x00ffffff) {
		next = (*(int*)(script_buf+i)) & 0x00ffffff;
		script_buf[i-1] = C_POS;
		script_buf[i]   = pos;
		script_buf[i+1] = pos>>8;
		script_buf[i+2] = pos>>16;
		i = next;
	}
}

/*==========================================
 * スペース/コメント読み飛ばし
 *------------------------------------------
 */
static unsigned char *skip_space(unsigned char *p)
{
	while(1){
		while(isspace(*p))
			p++;
		if(p[0]=='/' && p[1]=='/'){
			while(*p && *p!='\n')
				p++;
		} else if(p[0]=='/' && p[1]=='*'){
			p++;
			while(*p && (p[-1]!='*' || p[0]!='/'))
				p++;
			if(*p) p++;
		} else {
			break;
		}
	}
	return p;
}

/*==========================================
 * １単語スキップ
 *------------------------------------------
 */
static unsigned char *skip_word(unsigned char *p)
{
	// prefix
	if(*p=='.')  p++;	// MD依存変数
	if(*p=='\'') p++;	// スクリプト依存変数
	if(*p=='$')  p++;	// MAP鯖内共有変数用
	if(*p=='@')  p++;	// 一時的変数用(like weiss)
	if(*p=='#')  p++;	// account変数用
	if(*p=='#')  p++;	// ワールドaccount変数用

	while(isalnum(*p) || *p=='_' || *p>=0x81) {
		if(*p>=0x81 && p[1])
			p+=2;
		else
			p++;
	}
	// postfix
	if(*p=='$') p++;	// 文字列変数

	return p;
}

/*==========================================
 * 制御コード書き込み
 *------------------------------------------
 */
static int set_control_code(unsigned char p)
{
	switch(p) {
		case 'n':
			add_scriptb('\r');
			add_scriptb('\n');
			break;
		case 'r':
			add_scriptb('\r');
			break;
		case 't':
			add_scriptb('\t');
			break;
		case 'a':
			add_scriptb('\a');
			break;
		case 'b':
			add_scriptb('\b');
			break;
		default:
			return 0;
	}
	return 1;
}

static void parse_variable_sub_push(int l, unsigned char *p2)
{
	if( p2 ) {
		// array( name[i][j] => getelementofarray(name,i,j) )
		add_scriptl(search_str("getelementofarray"));
		add_scriptc(C_ARG);
		add_scriptl(l);
		while(*p2 == '[') {
			p2 = parse_subexpr(p2 + 1,-1);
			p2 = skip_space(p2);
			if((*p2++) != ']') {
				disp_error_message("unmatch ']'",p2 - 1);
			}
		}
		add_scriptc(C_FUNC);
	} else {
		// No array index, simply push the variable or value onto the stack
		add_scriptl(l);
	}
}

static unsigned char* parse_variable(unsigned char *p)
{
	int c,l;
	int op = C_NOP;
	unsigned char *p2;
	unsigned char *var = NULL;

	nullpo_retr(NULL, p);

	if( ( p[0] == '+' && p[1] == '+' && (op = C_ADD_PRE) ) // pre ++
	 || ( p[0] == '-' && p[1] == '-' && (op = C_SUB_PRE) ) // pre --
	) {
		p=skip_space(p+2);
	}

	p2 = skip_word(p);
	// label , register , function etc
	if(p2 == NULL) {
		// end of the line or invalid buffer
		return NULL;
	}
	if(p2 == p) {
		// end of the line or invalid buffer
		return NULL;
	}

	c = *p2;
	*p2 = 0;
	l = add_str(p);	// 名前をadd_strする

	*p2 = c;

	if(*p2 == '[') {
		int i, j;
		// array variable so process the array as appropriate
		for(var = p2, i = 0, j = 1; p2; ++ i) {
			if( *p2 ++ == ']' && --(j) == 0 ) break;
			if( *p2 == '[' ) ++ j;
		}

		if( !(p2 = skip_space(p2)) ) {
			// end of line or invalid characters remaining
			disp_error_message("Missing right expression or closing bracket for variable.", p);
		}
	}

	p2 = skip_space(p2);

	if( op == C_NOP &&
	!( ( p2[0] == '=' && p2[1] != '=' && (op = C_EQ) ) // =
	|| ( p2[0] == '+' && p2[1] == '=' && (op = C_ADD) ) // +=
	|| ( p2[0] == '-' && p2[1] == '=' && (op = C_SUB) ) // -=
	|| ( p2[0] == '^' && p2[1] == '=' && (op = C_XOR) ) // ^=
	|| ( p2[0] == '|' && p2[1] == '=' && (op = C_OR) ) // |=
	|| ( p2[0] == '&' && p2[1] == '=' && (op = C_AND) ) // &=
	|| ( p2[0] == '*' && p2[1] == '=' && (op = C_MUL) ) // *=
	|| ( p2[0] == '*' && p2[1] == '*' && p2[2] == '=' && (op = C_POW) ) // **=
	|| ( p2[0] == '/' && p2[1] == '=' && (op = C_DIV) ) // /=
	|| ( p2[0] == '%' && p2[1] == '=' && (op = C_MOD) ) // %=
	|| ( p2[0] == '+' && p2[1] == '+' && (op = C_ADD_POST) ) // post ++
	|| ( p2[0] == '-' && p2[1] == '-' && (op = C_SUB_POST) ) // post --
	|| ( p2[0] == '<' && p2[1] == '<' && p2[2] == '=' && (op = C_L_SHIFT) ) // <<=
	|| ( p2[0] == '>' && p2[1] == '>' && p2[2] == '=' && (op = C_R_SHIFT) ) // >>=
	) )
	{// failed to find a matching operator combination so invalid
		return NULL;
	}

	switch( op ) {
		case C_ADD_PRE: // pre ++
		case C_SUB_PRE: // pre --
			// (nothing more to skip)
			break;

		case C_EQ: // =
			p2 = skip_space( p2 + 1 );
			break;

		case C_L_SHIFT: // <<=
		case C_R_SHIFT: // >>=
		case C_POW: // **=
			p2 = skip_space( p2 + 3 );
			break;

		default: // everything else
			p2 = skip_space( p2 + 2 );
	}

	if( p2 == NULL ) {
		// end of line or invalid buffer
		return NULL;
	}

	add_scriptl(search_str("set"));
	add_scriptc(C_ARG);

	if( str_data[l].type == C_FUNC
	 || str_data[l].type == C_USERFUNC
	 || str_data[l].type == C_USERFUNC_POS
	) {
		// cannot assign a variable which exists as a function or label
		disp_error_message("Cannot modify a variable which has the same name as a function or label.", p);
	}

	parse_variable_sub_push(l, var);

	if( op != C_EQ ) {
		parse_variable_sub_push(l, var);
	}

	if( op == C_ADD_POST || op == C_SUB_POST ) { // post ++ / --
		add_scripti(1);
		add_scriptc(op == C_ADD_POST ? C_ADD : C_SUB);

		parse_variable_sub_push(l, var);
	} else if( op == C_ADD_PRE || op == C_SUB_PRE ) { // pre ++ / --
		add_scripti(1);
		add_scriptc(op == C_ADD_PRE ? C_ADD : C_SUB);
	} else {
		// process the value as an expression
		p2 = parse_subexpr(p2, -1);

		if( op != C_EQ ) {
			// push the type of modifier onto the stack
			add_scriptc(op);
		}
	}
	add_scriptc(C_FUNC);
	return p2;
}

/*==========================================
 * 項の解析
 *------------------------------------------
 */
static unsigned char* parse_simpleexpr(unsigned char *p)
{
	p=skip_space(p);

#ifdef DEBUG_FUNCIN
	if(script_config.debug_mode_log)
		printf("parse_simpleexpr:start %s\n",p);
#endif
	if(*p==';' || *p==','){
		disp_error_message("unexpected expr end",p);
	}
	if(*p=='('){
		p=parse_subexpr(p+1,-1);
		p=skip_space(p);
		if((*p++)!=')'){
			disp_error_message("unmatch ')'",p-1);
		}
	} else if(isdigit(*p) || ((*p=='-' || *p=='+') && isdigit(p[1]))){
		char *np;
		int i = strtobxl(p,&np,0);
		add_scripti(i);
		p=np;
	} else if(*p=='"'){
		unsigned char *p2;
		add_scriptc(C_STR);
		while(1) {
			p++;
			while(*p && *p!='"'){
				if(*p=='\n'){
					disp_error_message("unexpected newline @ string",p);
				}
				if(p[-1]<=0x7e && *p=='\\') {
					p++;
					if(set_control_code(*p)) {
						p++;
						continue;
					}
				}
				add_scriptb(*p++);
			}
			if(!*p){
				disp_error_message("unexpected eof @ string",p);
			}
			p2 = skip_space(p+1);
			if(*p2 != '"')
				break;
			p = p2;
		}
		add_scriptb(0);
		p++;	// '"'
	} else {
		int c,l;
		unsigned char *p2 = skip_word(p);
		// label , register , function etc
		if(p2 == p) {
			disp_error_message("unexpected character",p);
		}
		c = *p2;
		*p2 = 0;
		l = add_str(p);	// 名前をadd_strする

		parse_cmd = l;	// warn_*_mismatch_paramnumのために必要

		*p2 = c;
		p = p2;

		if(str_data[l].type == C_USERFUNC || str_data[l].type == C_USERFUNC_POS) {
			add_scriptl(search_str("callsub"));
			add_scriptc(C_ARG);
			add_scriptl(l);
		} else if(str_data[l].type != C_FUNC && c == '[') {
			// array( name[i][j] => getelementofarray(name,i,j) )
			add_scriptl(search_str("getelementofarray"));
			add_scriptc(C_ARG);
			add_scriptl(l);
			while(*p == '[') {
				p = parse_subexpr(p+1,-1);
				p = skip_space(p);
				if((*p++) != ']') {
					disp_error_message("unmatch ']'",p-1);
				}
			}
			add_scriptc(C_FUNC);
		} else {
			add_scriptl(l);
		}
	}

#ifdef DEBUG_FUNCIN
	if(script_config.debug_mode_log)
		printf("parse_simpleexpr:end %s\n",p);
#endif
	return p;
}

/*==========================================
 * 式の解析
 *------------------------------------------
 */
static unsigned char* parse_subexpr(unsigned char *p,int limit)
{
	int op;

#ifdef DEBUG_FUNCIN
	if(script_config.debug_mode_log)
		printf("parse_subexpr:start(%d) %s\n", limit, p);
#endif
	p = skip_space(p);

	if(*p == '-') {
		unsigned char *tmpp = skip_space(p+1);
		if(*tmpp == ';' || *tmpp == ',') {
			add_scriptl(LABEL_NEXTLINE);
			return p + 1;
		}
	}

	switch(*p) {
		case '-': op = C_NEG;  break;
		case '!': op = C_LNOT; break;
		case '~': op = C_NOT;  break;
		default:  op = C_NOP;  break;
	}
	if(op == C_NOP) {
		p = parse_simpleexpr(p);
	} else {
		p = parse_subexpr(p+1, 10);
		add_scriptc(op);
	}
	p = skip_space(p);

	while(1) {
		int priority = 0, len = 0;
		switch(*p) {
			case '(': op = C_FUNC; priority = 13; len = 1; break;
			case '/': op = C_DIV;  priority =  9; len = 1; break;
			case '%': op = C_MOD;  priority =  9; len = 1; break;
			case '+': op = C_ADD;  priority =  8; len = 1; break;
			case '-': op = C_SUB;  priority =  8; len = 1; break;
			case '^': op = C_XOR;  priority =  4; len = 1; break;
			case '?': op = C_OP3;  priority =  0; len = 1; break;
			case '*':
				if(p[1] == '*') {
					op = C_POW;  priority = 12; len = 2; break;
				} else {
					op = C_MUL;  priority =  9; len = 1; break;
				}
				break;
			case '&':
				if(p[1] == '&') {
					op = C_LAND; priority = 2; len = 2;
				} else {
					op = C_AND;  priority = 6; len = 1;
				}
				break;
			case '|':
				if(p[1] == '|') {
					op = C_LOR; priority = 1; len = 2;
				} else {
					op = C_OR;  priority = 5; len = 1;
				}
				break;
			case '=':
				if(p[1] == '=') {
					op = C_EQ; priority = 3; len = 2;
				} else {
					op = C_NOP;
				}
				break;
			case '!':
				if(p[1] == '=') {
					op = C_NE; priority = 3; len = 2;
				} else {
					op = C_NOP;
				}
				break;
			case '>':
				if(p[1] == '>') {
					op = C_R_SHIFT; priority = 7; len = 2;
				} else if(p[1] == '=') {
					op = C_GE; priority = 3; len = 2;
				} else {
					op = C_GT; priority = 3; len = 1;
				}
				break;
			case '<':
				if(p[1] == '<') {
					op = C_L_SHIFT; priority = 7; len = 2;
				} else if(p[1] == '=') {
					op = C_LE; priority = 3; len = 2;
				} else {
					op = C_LT; priority = 3; len = 1;
				}
				break;
			default:
				op = C_NOP;
				break;
		}
		if(op == C_NOP || priority <= limit)
			break;

		p += len;
		if(op == C_FUNC) {
			int i = 0, j = 0;
			char *plist[128];
			const char *arg = NULL;

			if(str_data[parse_cmd].type == C_FUNC) {
				// 通常の関数
				add_scriptc(C_ARG);
			} else if(str_data[parse_cmd].type == C_USERFUNC || str_data[parse_cmd].type == C_USERFUNC_POS) {
				// ユーザー定義関数呼び出し
				parse_cmd = search_str("callsub");
				i++;
			} else {
				disp_error_message("expect command, missing function name or calling undeclared function", p);
			}
			p = skip_space(p);

			// 関数の持つ引数の数をチェック
			if(str_data[parse_cmd].type == C_FUNC && script_config.warn_cmd_mismatch_paramnum) {
				arg = buildin_func[str_data[parse_cmd].u.val].arg;
				for(j = 0; arg[j]; j++) {
					if(arg[j] == '*')
						break;
				}
			}

			while(*p && *p != ')' && i < 128) {
				plist[i] = p;
				p = parse_subexpr(p,-1);
				p = skip_space(p);
				// 引数区切りの,処理
				if(*p == ',') {
					if(arg == NULL || arg[j] == '*' || i+1 < j)	// 次も引数をとるならカンマをスキップ
						p++;
				}
				else if(*p != ')' && script_config.warn_func_no_comma) {
					disp_error_message("expect ',' or ')' at func params", p);
				}
				p = skip_space(p);
				i++;
			}
			plist[i] = p;
			if(*(p++) != ')') {
				disp_error_message("func request '(' ')'",p-1);
			}
			if(arg) {
				if( (arg[j] == '\0' && i != j) || (arg[j] == '*' && i < j) )
					disp_error_message("illegal number of parameters", plist[(i < j)? i: j]);
			}
		} else if(op == C_OP3) {
			p = parse_subexpr(p,-1);
			p = skip_space(p);
			if(*(p++) != ':') {
				disp_error_message("need ':'", p-1);
			}
			p = parse_subexpr(p,-1);
		} else if(op == C_POW) {
			p = parse_subexpr(p, 11);	// 右結合のため順位を1つ下げる
		} else {
			p = parse_subexpr(p, priority);
		}
		add_scriptc(op);
		p = skip_space(p);
	}
#ifdef DEBUG_FUNCIN
	if(script_config.debug_mode_log)
		printf("parse_subexpr:end(%d) %s\n", limit, p);
#endif
	return p;
}

/*==========================================
 * 式の評価
 *------------------------------------------
 */
static unsigned char* parse_expr(unsigned char *p)
{
#ifdef DEBUG_FUNCIN
	if(script_config.debug_mode_log)
		printf("parse_expr:start %s\n",p);
#endif
	switch(*p) {
		case ')':
		case ';':
		case ':':
		case '[':
		case ']':
		case '}':
			disp_error_message("unexpected char",p);
	}
	p=parse_subexpr(p,-1);
#ifdef DEBUG_FUNCIN
	if(script_config.debug_mode_log)
		printf("parse_expr:end %s\n",p);
#endif
	return p;
}

/*==========================================
 * 行の解析
 *------------------------------------------
 */
static unsigned char* parse_line(unsigned char *p)
{
	int i = 0, j = 0;
	unsigned char *plist[128];
	unsigned char *p2;
	unsigned char end;
	const char *arg = NULL;

	p = skip_space(p);
	if(*p == ';') {
		// if(); for(); while(); のために閉じ判定
		p = parse_syntax_close(p + 1);
		return p;
	}
	if(*p == ')' && parse_syntax_for_flag)
		return p + 1;

	p = skip_space(p);
	if(*p == '{') {
		syntax.curly[syntax.curly_count].type  = TYPE_NULL;
		syntax.curly[syntax.curly_count].count = -1;
		syntax.curly[syntax.curly_count].index = -1;
		syntax.curly_count++;
		return p + 1;
	} else if(*p == '}') {
		return parse_curly_close(p);
	}

	// 構文関連の処理
	p2 = parse_syntax(p);
	if(p2 != NULL)
		return p2;

	// 変数処理
	p2 = parse_variable(p);

	if(p2 != NULL) {
		// if, for, while の閉じ判定
		if(parse_syntax_for_flag) {
			if(*p2 != ')')
				disp_error_message("need ')'", p2);
		} else {
			if(*p2 != ';')
				disp_error_message("need ';'", p2);
		}
		return parse_syntax_close(p2 + 1);
	}

	// 最初は関数名
	p2 = p;
	p  = parse_simpleexpr(p);

	if(str_data[parse_cmd].type == C_FUNC) {
		// 通常の関数
		add_scriptc(C_ARG);
	} else if(str_data[parse_cmd].type == C_USERFUNC || str_data[parse_cmd].type == C_USERFUNC_POS) {
		// ユーザー定義関数呼び出し
		parse_cmd = search_str("callsub");
		i++;
	} else {
		disp_error_message("expect command, missing function name or calling undeclared function", p2);
	}

	if(parse_syntax_for_flag) {
		end = ')';
	} else {
		end = ';';
	}

	// 関数の持つ引数の数をチェック
	if(str_data[parse_cmd].type == C_FUNC && script_config.warn_cmd_mismatch_paramnum) {
		arg = buildin_func[str_data[parse_cmd].u.val].arg;
		for(j = 0; arg[j]; j++) {
			if(arg[j] == '*')
				break;
		}
	}

	p2 = p;
	p  = skip_space(p);

	while(p && *p && *p != end && i < 128) {
		plist[i] = p;
		if(p2 == p) {
			disp_error_message("expect space ' '", p);
		}
		p = parse_expr(p);
		p = skip_space(p);
		// 引数区切りの,処理
		if(*p == ',') {
			if(arg == NULL || arg[j] == '*' || i+1 < j)	// 次も引数をとるならカンマをスキップ
				p++;
		}
		else if(*p != end && script_config.warn_cmd_no_comma) {
			if(parse_syntax_for_flag) {
				disp_error_message("expect ',' or ')' at cmd params", p);
			} else {
				disp_error_message("expect ',' or ';' at cmd params", p);
			}
		}
		p = skip_space(p);
		i++;
	}
	plist[i] = p;
	if(!p || *p != end) {
		if(parse_syntax_for_flag) {
			disp_error_message("need ')'", p);
		} else {
			disp_error_message("need ';'", p);
		}
	}
	add_scriptc(C_FUNC);

	// if, for, while の閉じ判定
	p = parse_syntax_close(p + 1);

	if(arg) {
		if( (arg[j] == '\0' && i != j) || (arg[j] == '*' && i < j) )
			disp_error_message("illegal number of parameters", plist[(i < j)? i: j]);
	}
	return p;
}

/*==========================================
 * { ... } の閉じ処理
 *------------------------------------------
 */
static unsigned char* parse_curly_close(unsigned char *p)
{
	if(syntax.curly_count <= 0) {
		disp_error_message("unexpected string",p);
	}

	switch(syntax.curly[syntax.curly_count-1].type) {
	case TYPE_NULL:
		syntax.curly_count--;
		// if, for, while の閉じ判定
		p = parse_syntax_close(p + 1);
		break;
	case TYPE_SWITCH:
		{
			// switch() 閉じ判定
			int pos = syntax.curly_count - 1;
			char label[256];
			int l;

			// 一時変数を消す
			sprintf(label,"set $@__SW%x_VAL,0;",syntax.curly[pos].index);
			syntax.curly[syntax.curly_count++].type = TYPE_NULL;
			parse_line(label);
			syntax.curly_count--;

			// 無条件で終了ポインタに移動
			sprintf(label,"goto __SW%x_FIN;",syntax.curly[pos].index);
			syntax.curly[syntax.curly_count++].type = TYPE_NULL;
			parse_line(label);
			syntax.curly_count--;

			// 現在地のラベルを付ける
			sprintf(label,"__SW%x_%x",syntax.curly[pos].index,syntax.curly[pos].count);
			l=add_str(label);
			set_label(l,script_pos,p);

			if(syntax.curly[pos].flag) {
				// default が存在する
				sprintf(label,"goto __SW%x_DEF;",syntax.curly[pos].index);
				syntax.curly[syntax.curly_count++].type = TYPE_NULL;
				parse_line(label);
				syntax.curly_count--;
			}

			// 終了ラベルを付ける
			sprintf(label,"__SW%x_FIN",syntax.curly[pos].index);
			l=add_str(label);
			set_label(l,script_pos,p);

			linkdb_final(&syntax.curly[pos].case_label);	// caseラベルのリストを解放
			syntax.curly_count--;
			p++;
		}
		break;
	default:
		disp_error_message("unexpected string",p);
	}
	return p;
}

/*==========================================
 * 構文関連の処理
 *   break, case, continue, default, do, for,
 *   function, if, switch, while をこの内部で処理
 *------------------------------------------
 */
static unsigned char* parse_syntax(unsigned char *p)
{
	unsigned char *p2;

	switch(*p) {
	case 'b':
	case 'B':
		p2 = skip_word(p);
		if(p2 - p == 5 && !strncasecmp(p,"break",5)) {
			// break の処理
			char label[256];
			int pos = syntax.curly_count - 1;

			while(pos >= 0) {
				if(syntax.curly[pos].type == TYPE_DO) {
					sprintf(label,"goto __DO%x_FIN;",syntax.curly[pos].index);
					break;
				} else if(syntax.curly[pos].type == TYPE_FOR) {
					sprintf(label,"goto __FR%x_FIN;",syntax.curly[pos].index);
					break;
				} else if(syntax.curly[pos].type == TYPE_WHILE) {
					sprintf(label,"goto __WL%x_FIN;",syntax.curly[pos].index);
					break;
				} else if(syntax.curly[pos].type == TYPE_SWITCH) {
					sprintf(label,"goto __SW%x_FIN;",syntax.curly[pos].index);
					break;
				}
				pos--;
			}
			if(pos < 0) {
				disp_error_message("unexpected 'break'",p);
			}
			syntax.curly[syntax.curly_count++].type = TYPE_NULL;
			parse_line(label);
			syntax.curly_count--;
			p = skip_space(p2);
			if(*p != ';') {
				disp_error_message("need ';'",p);
			}
			// if, for, while の閉じ判定
			p = parse_syntax_close(p + 1);
			return p;
		}
		break;
	case 'c':
	case 'C':
		p2 = skip_word(p);
		if(p2 - p == 4 && !strncasecmp(p,"case",4)) {
			// case の処理
			char *np;
			char label[256];
			int l,v;
			int pos = syntax.curly_count-1;

			if(pos < 0 || syntax.curly[pos].type != TYPE_SWITCH) {
				disp_error_message("unexpected 'case'",p);
			}
			if(syntax.curly[pos].count != 1) {
				// FALLTHRU 用のジャンプ
				sprintf(label,"goto __SW%x_%xJ;",syntax.curly[pos].index,syntax.curly[pos].count);
				syntax.curly[syntax.curly_count++].type = TYPE_NULL;
				parse_line(label);
				syntax.curly_count--;

				// 現在地のラベルを付ける
				sprintf(label,"__SW%x_%x",syntax.curly[pos].index,syntax.curly[pos].count);
				l=add_str(label);
				set_label(l,script_pos,p);
			}
			// switch 判定文
			p = skip_space(p2);
			if(p == p2) {
				disp_error_message("expect space ' '",p);
			}
			p2 = p;

			// caseラベルが数値型定数であるかチェック
			v = strtobxl(p,&np,0);
			if((*p == '-' || *p == '+') && isdigit(p[1]))	// '-' はskip_word出来ないのであらかじめskipしておく
				p++;
			p = skip_word(p);
			if((unsigned char *)np == p2 || (unsigned char *)np != p) {	// 数値ではないようなので定数として検索してみる
				int i;
				unsigned char c = *p;

				*p = 0;
				i = search_str(p2);
				*p = c;
				if(i < 0 || str_data[i].type != C_INT) {
					disp_error_message("'case' label not integer",p2);
				}
				v = str_data[i].u.val;
			}
			p = skip_space(p);
			if(*p != ':') {
				disp_error_message("expect ':'",p);
			}

			// caseラベルが重複してないかチェック
			if(linkdb_exists(&syntax.curly[pos].case_label, INT2PTR(v))) {
				disp_error_message("dup 'case'",p);
			}
			linkdb_insert(&syntax.curly[pos].case_label, INT2PTR(v), INT2PTR(1));

			sprintf(label,"if(%d != $@__SW%x_VAL) goto __SW%x_%x;",
				v,syntax.curly[pos].index,syntax.curly[pos].index,syntax.curly[pos].count+1);
			syntax.curly[syntax.curly_count++].type = TYPE_NULL;
			// ２回parse しないとダメ
			p2 = parse_line(label);
			parse_line(p2);
			syntax.curly_count--;
			if(syntax.curly[pos].count != 1) {
				// FALLTHRU 終了後のラベル
				sprintf(label,"__SW%x_%xJ",syntax.curly[pos].index,syntax.curly[pos].count);
				l=add_str(label);
				set_label(l,script_pos,p);
			}
			// 一時変数を消す
			sprintf(label,"set $@__SW%x_VAL,0;",syntax.curly[pos].index);
			syntax.curly[syntax.curly_count++].type = TYPE_NULL;
			parse_line(label);
			syntax.curly_count--;
			syntax.curly[pos].count++;
			return p + 1;
		}
		else if(p2 - p == 8 && !strncasecmp(p,"continue",8)) {
			// continue の処理
			char label[256];
			int pos = syntax.curly_count - 1;

			while(pos >= 0) {
				if(syntax.curly[pos].type == TYPE_DO) {
					sprintf(label,"goto __DO%x_NXT;",syntax.curly[pos].index);
					syntax.curly[pos].flag = 1; // continue 用のリンク張るフラグ
					break;
				} else if(syntax.curly[pos].type == TYPE_FOR) {
					sprintf(label,"goto __FR%x_NXT;",syntax.curly[pos].index);
					break;
				} else if(syntax.curly[pos].type == TYPE_WHILE) {
					sprintf(label,"goto __WL%x_NXT;",syntax.curly[pos].index);
					break;
				}
				pos--;
			}
			if(pos < 0) {
				disp_error_message("unexpected 'continue'",p);
			}
			syntax.curly[syntax.curly_count++].type = TYPE_NULL;
			parse_line(label);
			syntax.curly_count--;
			p = skip_space(p2);
			if(*p != ';') {
				disp_error_message("need ';'",p);
			}
			// if, for, while の閉じ判定
			p = parse_syntax_close(p + 1);
			return p;
		}
		break;
	case 'd':
	case 'D':
		p2 = skip_word(p);
		if(p2 - p == 7 && !strncasecmp(p,"default",7)) {
			// switch - default の処理
			char label[256];
			int l;
			int pos = syntax.curly_count-1;

			if(pos < 0 || syntax.curly[pos].type != TYPE_SWITCH) {
				disp_error_message("unexpected 'default'",p);
			}
			if(syntax.curly[pos].flag) {
				disp_error_message("dup 'default'",p);
			}
			// 現在地のラベルを付ける
			p = skip_space(p2);
			if(*p != ':') {
				disp_error_message("need ':'",p);
			}
			sprintf(label,"__SW%x_%x",syntax.curly[pos].index,syntax.curly[pos].count);
			l=add_str(label);
			set_label(l,script_pos,p);

			// 無条件で次のリンクに飛ばす
			sprintf(label,"goto __SW%x_%x;",syntax.curly[pos].index,syntax.curly[pos].count+1);
			syntax.curly[syntax.curly_count++].type = TYPE_NULL;
			parse_line(label);
			syntax.curly_count--;

			// default のラベルを付ける
			sprintf(label,"__SW%x_DEF",syntax.curly[pos].index);
			l=add_str(label);
			set_label(l,script_pos,p);

			syntax.curly[syntax.curly_count - 1].flag = 1;
			syntax.curly[pos].count++;
			return p + 1;
		}
		else if(p2 - p == 2 && !strncasecmp(p,"do",2)) {
			char label[256];
			int l;

			p=skip_space(p2);
			syntax.curly[syntax.curly_count].type  = TYPE_DO;
			syntax.curly[syntax.curly_count].count = 1;
			syntax.curly[syntax.curly_count].index = syntax.index++;
			syntax.curly[syntax.curly_count].flag  = 0;
			// 現在地のラベル形成する
			sprintf(label,"__DO%x_BGN",syntax.curly[syntax.curly_count].index);
			l=add_str(label);
			set_label(l,script_pos,p);
			syntax.curly_count++;
			return p;
		}
		break;
	case 'f':
	case 'F':
		p2 = skip_word(p);
		if(p2 - p == 3 && !strncasecmp(p,"for",3)) {
			char label[256];
			int l;
			int pos = syntax.curly_count;

			syntax.curly[syntax.curly_count].type  = TYPE_FOR;
			syntax.curly[syntax.curly_count].count = 1;
			syntax.curly[syntax.curly_count].index = syntax.index++;
			syntax.curly[syntax.curly_count].flag  = 0;
			syntax.curly_count++;

			p=skip_space(p2);
			if(*p != '(') {
				disp_error_message("need '('",p);
			}
			p++;

			// 初期化文を実行する
			syntax.curly[syntax.curly_count++].type = TYPE_NULL;
			p=parse_line(p);
			syntax.curly_count--;

			// 条件判断開始のラベル形成する
			sprintf(label,"__FR%x_J",syntax.curly[pos].index);
			l=add_str(label);
			set_label(l,script_pos,p);

			p=skip_space(p);
			if(*p == ';') {
				// for(;;) のパターンなので必ず真
				;
			} else {
				// 条件が偽なら終了地点に飛ばす
				sprintf(label,"__FR%x_FIN",syntax.curly[pos].index);
				add_scriptl(search_str("jump_zero"));
				add_scriptc(C_ARG);
				p=parse_expr(p);
				p=skip_space(p);
				add_scriptl(add_str(label));
				add_scriptc(C_FUNC);
			}
			if(*p != ';') {
				disp_error_message("need ';'",p);
			}
			p++;

			// ループ開始に飛ばす
			sprintf(label,"goto __FR%x_BGN;",syntax.curly[pos].index);
			syntax.curly[syntax.curly_count++].type = TYPE_NULL;
			parse_line(label);
			syntax.curly_count--;

			// 次のループへのラベル形成する
			sprintf(label,"__FR%x_NXT",syntax.curly[pos].index);
			l=add_str(label);
			set_label(l,script_pos,p);

			// 次のループに入る時の処理
			// for 最後の ')' を ';' として扱うフラグ
			parse_syntax_for_flag = 1;
			syntax.curly[syntax.curly_count++].type = TYPE_NULL;
			p=parse_line(p);
			syntax.curly_count--;
			parse_syntax_for_flag = 0;

			// 条件判定処理に飛ばす
			sprintf(label,"goto __FR%x_J;",syntax.curly[pos].index);
			syntax.curly[syntax.curly_count++].type = TYPE_NULL;
			parse_line(label);
			syntax.curly_count--;

			// ループ開始のラベル付け
			sprintf(label,"__FR%x_BGN",syntax.curly[pos].index);
			l=add_str(label);
			set_label(l,script_pos,p);
			return p;
		}
		else if(p2 - p == 8 && !strncasecmp(p,"function",8)) {
			unsigned char *func_name;

			// function
			p=skip_space(p2);
			if(p == p2) {
				disp_error_message("expect space ' '",p);
			}
			// function - name
			func_name = p;
			p=skip_word(p);
			p2=skip_space(p);
			if(*p2 == ';') {
				// 関数の宣言 - 名前を登録して終わり
				unsigned char c = *p;
				int l;
				*p = 0;
				l=add_str(func_name);
				*p = c;
				if(str_data[l].type == C_INT || str_data[l].type == C_PARAM) {
					disp_error_message("invalid label name",p);
				}
				if(str_data[l].type == C_NOP)
					str_data[l].type = C_USERFUNC;

				// if, for, while の閉じ判定
				p = parse_syntax_close(p2 + 1);
			} else if(*p2 == '{') {
				// 関数の中身
				char label[256];
				unsigned char c = *p;
				int l;
				syntax.curly[syntax.curly_count].type  = TYPE_USERFUNC;
				syntax.curly[syntax.curly_count].count = 1;
				syntax.curly[syntax.curly_count].index = syntax.index++;
				syntax.curly[syntax.curly_count].flag  = 0;
				syntax.curly_count++;

				// 関数終了まで飛ばす
				sprintf(label,"goto __FN%x_FIN;",syntax.curly[syntax.curly_count-1].index);
				syntax.curly[syntax.curly_count++].type = TYPE_NULL;
				parse_line(label);
				syntax.curly_count--;

				// 関数名のラベルを付ける
				*p = 0;
				l=add_str(func_name);
				*p = c;
				if(str_data[l].type == C_INT || str_data[l].type == C_PARAM) {
					disp_error_message("invalid label name",p);
				}
				if(str_data[l].type == C_NOP)
					str_data[l].type = C_USERFUNC;
				set_label(l,script_pos,p);
				p = skip_space(p);
			} else {
				disp_error_message("expect ';' or '{' at function syntax",p);
			}
			return p;
		}
		break;
	case 'i':
	case 'I':
		p2 = skip_word(p);
		if(p2 - p == 2 && !strncasecmp(p,"if",2)) {
			// if() の処理
			char label[256];

			p=skip_space(p2);
			if(*p != '(') {
				disp_error_message("need '('",p);
			}
			syntax.curly[syntax.curly_count].type  = TYPE_IF;
			syntax.curly[syntax.curly_count].count = 1;
			syntax.curly[syntax.curly_count].index = syntax.index++;
			syntax.curly[syntax.curly_count].flag  = 0;
			sprintf(label,"__IF%x_%x",syntax.curly[syntax.curly_count].index,syntax.curly[syntax.curly_count].count);
			syntax.curly_count++;
			add_scriptl(search_str("jump_zero"));
			add_scriptc(C_ARG);
			p=parse_expr(p);
			p=skip_space(p);
			add_scriptl(add_str(label));
			add_scriptc(C_FUNC);
			return p;
		}
		break;
	case 's':
	case 'S':
		p2 = skip_word(p);
		if(p2 - p == 6 && !strncasecmp(p,"switch",6)) {
			// switch() の処理
			char label[256];

			p=skip_space(p2);
			if(*p != '(') {
				disp_error_message("need '('",p);
			}
			syntax.curly[syntax.curly_count].type  = TYPE_SWITCH;
			syntax.curly[syntax.curly_count].count = 1;
			syntax.curly[syntax.curly_count].index = syntax.index++;
			syntax.curly[syntax.curly_count].flag  = 0;
			sprintf(label,"$@__SW%x_VAL",syntax.curly[syntax.curly_count].index);
			syntax.curly_count++;
			add_scriptl(search_str("set"));
			add_scriptc(C_ARG);
			add_scriptl(add_str(label));
			p=parse_expr(p);
			p=skip_space(p);
			if(*p != '{') {
				disp_error_message("need '{'",p);
			}
			add_scriptc(C_FUNC);

			// switchの直後は } とcaseとdefaultのみ許可
			p = skip_space(p + 1);
			p2 = skip_word(p);
			if(*p2 == '}' || (p2 - p == 4 && !strncasecmp(p,"case",4)) || (p2 - p == 7 && !strncasecmp(p,"default",7))) {
				;
			} else {
				disp_error_message("not found '}' or 'case' or 'default'",p);
			}
			return p;
		}
		break;
	case 'w':
	case 'W':
		p2 = skip_word(p);
		if(p2 - p == 5 && !strncasecmp(p,"while",5)) {
			char label[256];
			int l;

			p=skip_space(p2);
			if(*p != '(') {
				disp_error_message("need '('",p);
			}
			syntax.curly[syntax.curly_count].type  = TYPE_WHILE;
			syntax.curly[syntax.curly_count].count = 1;
			syntax.curly[syntax.curly_count].index = syntax.index++;
			syntax.curly[syntax.curly_count].flag  = 0;
			// 条件判断開始のラベル形成する
			sprintf(label,"__WL%x_NXT",syntax.curly[syntax.curly_count].index);
			l=add_str(label);
			set_label(l,script_pos,p);

			// 条件が偽なら終了地点に飛ばす
			sprintf(label,"__WL%x_FIN",syntax.curly[syntax.curly_count].index);
			add_scriptl(search_str("jump_zero"));
			add_scriptc(C_ARG);
			p=parse_expr(p);
			p=skip_space(p);
			add_scriptl(add_str(label));
			add_scriptc(C_FUNC);
			syntax.curly_count++;
			return p;
		}
		break;
	}
	return NULL;
}

/*==========================================
 * if, for, while, do の閉じ判定
 *   flag == 1 : 閉じられた
 *   flag == 0 : 閉じられない
 *------------------------------------------
 */
static unsigned char* parse_syntax_close_sub(unsigned char *p,int *flag)
{
	char label[256];
	int l, pos;

	if(syntax.curly_count <= 0) {
		*flag = 0;
		return p;
	}
	pos = syntax.curly_count - 1;

	switch(syntax.curly[pos].type) {
	case TYPE_IF:
		{
			unsigned char *bp = p;
			unsigned char *p2;

			// if 最終場所へ飛ばす
			sprintf(label,"goto __IF%x_FIN;",syntax.curly[pos].index);
			syntax.curly[syntax.curly_count++].type = TYPE_NULL;
			parse_line(label);
			syntax.curly_count--;

			// 現在地のラベルを付ける
			sprintf(label,"__IF%x_%x",syntax.curly[pos].index,syntax.curly[pos].count);
			l=add_str(label);
			set_label(l,script_pos,p);

			syntax.curly[pos].count++;
			p = skip_space(p);
			p2 = skip_word(p);
			if(!syntax.curly[pos].flag && p2 - p == 4 && !strncasecmp(p,"else",4)) {
				// else  or else - if
				p = skip_space(p2);
				p2 = skip_word(p);
				if(p2 - p == 2 && !strncasecmp(p,"if",2)) {
					// else - if
					p=skip_space(p2);
					if(*p != '(') {
						disp_error_message("need '('",p);
					}
					sprintf(label,"__IF%x_%x",syntax.curly[pos].index,syntax.curly[pos].count);
					add_scriptl(search_str("jump_zero"));
					add_scriptc(C_ARG);
					p=parse_expr(p);
					p=skip_space(p);
					add_scriptl(add_str(label));
					add_scriptc(C_FUNC);
					*flag = 0;
					return p;
				} else {
					// else
					if(!syntax.curly[pos].flag) {
						syntax.curly[pos].flag = 1;
						*flag = 0;
						return p;
					}
				}
			}
			// 最終地のラベルを付ける
			sprintf(label,"__IF%x_FIN",syntax.curly[pos].index);
			l=add_str(label);
			set_label(l,script_pos,p);
			if(syntax.curly[pos].flag == 1) {
				// このifに対するelseじゃないのでポインタの位置は同じ
				p = bp;
			}
			syntax.curly_count--;
			*flag = 1;
		}
		break;
	case TYPE_DO:
		{
			unsigned char *p2;

			if(syntax.curly[pos].flag) {
				// 現在地のラベル形成する(continue でここに来る)
				sprintf(label,"__DO%x_NXT",syntax.curly[pos].index);
				l=add_str(label);
				set_label(l,script_pos,p);
			}

			// 条件が偽なら終了地点に飛ばす
			p = skip_space(p);
			p2 = skip_word(p);
			if(p2 - p != 5 || strncasecmp(p,"while",5)) {
				disp_error_message("need 'while'",p);
			}

			p = skip_space(p2);
			if(*p != '(') {
				disp_error_message("need '('",p);
			}
			sprintf(label,"__DO%x_FIN",syntax.curly[pos].index);
			add_scriptl(search_str("jump_zero"));
			add_scriptc(C_ARG);
			p=parse_expr(p);
			p=skip_space(p);
			add_scriptl(add_str(label));
			add_scriptc(C_FUNC);

			// 開始地点に飛ばす
			sprintf(label,"goto __DO%x_BGN;",syntax.curly[pos].index);
			syntax.curly[syntax.curly_count++].type = TYPE_NULL;
			parse_line(label);
			syntax.curly_count--;

			// 条件終了地点のラベル形成する
			sprintf(label,"__DO%x_FIN",syntax.curly[pos].index);
			l=add_str(label);
			set_label(l,script_pos,p);
			if(*p != ';') {
				disp_error_message("need ';'",p);
			}
			p++;
			syntax.curly_count--;
			*flag = 1;
		}
		break;
	case TYPE_FOR:
		// 次のループに飛ばす
		sprintf(label,"goto __FR%x_NXT;",syntax.curly[pos].index);
		syntax.curly[syntax.curly_count++].type = TYPE_NULL;
		parse_line(label);
		syntax.curly_count--;

		// for 終了のラベル付け
		sprintf(label,"__FR%x_FIN",syntax.curly[pos].index);
		l=add_str(label);
		set_label(l,script_pos,p);
		syntax.curly_count--;
		*flag = 1;
		break;
	case TYPE_WHILE:
		// while 条件判断へ飛ばす
		sprintf(label,"goto __WL%x_NXT;",syntax.curly[pos].index);
		syntax.curly[syntax.curly_count++].type = TYPE_NULL;
		parse_line(label);
		syntax.curly_count--;

		// while 終了のラベル付け
		sprintf(label,"__WL%x_FIN",syntax.curly[pos].index);
		l=add_str(label);
		set_label(l,script_pos,p);
		syntax.curly_count--;
		*flag = 1;
		break;
	case TYPE_USERFUNC:
		// 戻す
		add_scriptl(search_str("return"));
		add_scriptc(C_ARG);
		add_scriptc(C_FUNC);

		// 現在地のラベルを付ける
		sprintf(label,"__FN%x_FIN",syntax.curly[pos].index);
		l=add_str(label);
		set_label(l,script_pos,p);
		syntax.curly_count--;
		*flag = 1;
		break;
	default:
		*flag = 0;
		break;
	}
	return p;
}

/*==========================================
 * if(...) for(...) hoge(); のように
 * １度閉じられたら再度閉じられるか確認する
 *------------------------------------------
 */
static unsigned char* parse_syntax_close(unsigned char *p)
{
	int flag;

	do {
		p = parse_syntax_close_sub(p,&flag);
	} while(flag);

	return p;
}

/*==========================================
 * 組み込み関数の追加
 *------------------------------------------
 */
static void add_buildin_func(void)
{
	int i,n;

	for(i=0;buildin_func[i].func;i++){
		n=add_str(buildin_func[i].name);
		str_data[n].type=C_FUNC;
		str_data[n].u.val=i;
		str_data[n].func=buildin_func[i].func;
	}
}

/*==========================================
 * 定数データベースの読み込み
 *------------------------------------------
 */
static void read_constdb(void)
{
	FILE *fp;
	char line[1024], name[1024], val[1024];
	int n, type;
	const char *filename = "db/const.txt";

	fp = fopen(filename, "r");
	if(fp == NULL) {
		printf("read_constdb: open [%s] failed !\n", filename);
		return;
	}
	while(fgets(line,1020,fp)) {
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0] == '/' && line[1] == '/')
			continue;
		type = 0;
		if(sscanf(line, "%1023[A-Za-z0-9_#],%1023[-0-9xXA-Fa-f],%d", name, val, &type) >= 2 ||
		   sscanf(line, "%1023[A-Za-z0-9_#] %1023[-0-9xXA-Fa-f] %d", name, val, &type) >= 2)
		{
			n = add_str(name);
			str_data[n].type  = (type == 0)? C_INT: C_PARAM;
			str_data[n].u.val = (int)strtobxl(val,NULL,0);
		} else {
			if(sscanf(line, "%1023[A-Za-z0-9_]$,%1023[^\r\n]", name, val) == 2 ||
			   sscanf(line, "%1023[A-Za-z0-9_]$ %1023[^\r\n]", name, val) == 2)
			{
				n = add_str(strcat(name, "$"));
				str_data[n].type  = C_STR;
				str_data[n].u.str = (char *)aStrdup(val);
			}
		}
	}
	fclose(fp);
}

/*==========================================
 * エラー表示
 *------------------------------------------
 */
static const char* script_print_line(const char *p, const char *mark, int line)
{
	int i;

	if(p == NULL || !p[0])
		return NULL;

	if(line < 0)
		printf("*% 5d : ", -line);
	else
		printf(" % 5d : ", line);

	for(i = 0; p[i] && p[i] != '\n'; i++) {
		if(p + i != mark)
			printf("%c", p[i]);
		else
			printf("%s%c%s", error_marker_start, p[i], error_marker_end);
	}
	printf("\n");

	return p + i + (p[i] == '\n' ? 1 : 0);
}

void script_error(const char *src, const char *file, int start_line, const char *msg, const char *pos)
{
	const char *linestart[5] = { NULL, NULL, NULL, NULL, NULL };
	const char *p;
	int j, line = start_line;

	// エラーが発生した行を求める
	for(p = src; p && *p; line++) {
		const char *lineend = strchr(p, '\n');
		if(lineend == NULL || pos <= lineend || *(lineend + 1) == '\0') {
			break;
		}
		for(j = 0; j < 4; j++) {
			linestart[j] = linestart[j+1];
		}
		linestart[4] = p;
		p = lineend + 1;
	}

	printf("\a\n");
	printf("script error on %s line %d\n", file, line);
	printf("    %s\n", msg);

	for(j = 0; j < 5; j++) {
		script_print_line(linestart[j], NULL, line + j - 5);
	}
	p = script_print_line(p, pos, -line);
	for(j = 0; j < 5; j++) {
		p = script_print_line(p, NULL, line + j + 1);
	}
}

/*==========================================
 * スクリプト行の閉じの解析
 *------------------------------------------
 */
char* parse_script_line_curly(unsigned char *p,int *curly_count,int line)
{
	size_t i = 0, len;
	int string_flag = 0;
	static int comment_flag = 0;

	if(p == NULL) {	// フラグを戻して終了
		comment_flag = 0;
		return NULL;
	}

	len = strlen(p);
	for(i = 0; i < len ; i++) {
		if(comment_flag) {
			if(p[i] == '*' && p[i+1] == '/') {
				// マルチラインコメント終了
				i++;
				(*curly_count)--;
				comment_flag = 0;
			}
		} else if(string_flag) {
			if(p[i] == '"') {
				string_flag = 0;
			} else if(p[i] == '\\' && p[i-1] <= 0x7e) {
				// エスケープ
				i++;
			}
		} else {
			if(p[i] == '"') {
				string_flag = 1;
			} else if(p[i] == '}') {
				(*curly_count)--;
				if(*curly_count == 0)
					break;
			} else if(p[i] == '{') {
				(*curly_count)++;
			} else if(p[i] == '/' && p[i+1] == '/') {
				// コメント
				i = len;
				break;
			} else if(p[i] == '/' && p[i+1] == '*') {
				// マルチラインコメント
				i++;
				(*curly_count)++;
				comment_flag = 1;
			}
		}
	}
	if(string_flag) {
		printf("Missing '\"' at line %d\a\n",line);
		return NULL;
	}

	return p + i;
}

/*==========================================
 * スクリプト行の終端の解析
 *------------------------------------------
 */
char* parse_script_line_end(unsigned char *src, const char *file, int line)
{
	int curly_count = 0;
	char *p;

	p = parse_script_line_curly(src, &curly_count, line);
	if(p && curly_count > 0) {
		script_error( src, file, line, "missing right curly", p );
		p = NULL;
	}
	parse_script_line_curly(NULL, 0, 0);

	return p;
}

/*==========================================
 * スクリプトの解析
 *------------------------------------------
 */
struct script_code* parse_script(unsigned char *src,const char *file,int line)
{
	unsigned char *p,*tmpp;
	int i;
	struct script_code *code;
	static int first=1;

	memset(&syntax,0,sizeof(syntax));
	if(first){
		add_buildin_func();
		read_constdb();
	}
	first=0;

	p=src;
	p=skip_space(p);
	if(*p!='{'){
		script_error(src,file,line,"not found '{'",p);
		return &error_code;
	}
	p++;
	p=skip_space(p);
	if(p && *p == '}') {
		// コードを持たないスクリプトは正常
		return NULL;
	}

	script_buf=(unsigned char *)aMalloc(SCRIPT_BLOCK_SIZE*sizeof(unsigned char));
	script_pos=0;
	script_size=SCRIPT_BLOCK_SIZE;
	str_data[LABEL_NEXTLINE].type=C_NOP;
	str_data[LABEL_NEXTLINE].backpatch=-1;
	str_data[LABEL_NEXTLINE].label=-1;
	for(i=LABEL_START;i<str_num;i++){
		if(
			str_data[i].type==C_POS || str_data[i].type==C_NAME ||
			str_data[i].type==C_USERFUNC || str_data[i].type == C_USERFUNC_POS
		){
			str_data[i].type=C_NOP;
			str_data[i].backpatch=-1;
			str_data[i].label=-1;
		}
	}

	// 外部用label dbの初期化
	linkdb_final(&scriptlabel_db);

	// 例外処理
	if( setjmp( error_jump ) != 0 ) {
		int j;
		script_error(src,file,line,error_msg,error_pos);
		// 後始末
		aFree( error_msg );
		aFree( script_buf );
		script_pos  = 0;
		script_size = 0;
		script_buf  = NULL;
		for(j=LABEL_START; j<str_num; j++) {
			if(str_data[j].type == C_NOP)
				str_data[j].type = C_NAME;
		}
		for(j=0; j<sizeof(syntax.curly)/sizeof(syntax.curly[0]); j++) {
			linkdb_final(&syntax.curly[j].case_label);
		}
		linkdb_final(&scriptlabel_db);
		return &error_code;
	}

	while (p && *p && (*p!='}' || syntax.curly_count != 0)) {
		p=skip_space(p);
		// labelだけ特殊処理
		tmpp=skip_space(skip_word(p));
		if(*tmpp==':' && !(!strncasecmp(p,"default:",8) && p + 7 == tmpp)){
			int l,c;
			unsigned char *p2 = skip_word(p);

			c = *p2;
			*p2 = 0;
			if(*p == 0) {
				*p2 = c;
				disp_error_message("label length 0",p);
			}
			l=add_str(p);
			*p2 = c;
			if(str_data[l].type == C_INT || str_data[l].type == C_PARAM) {
				disp_error_message("invalid label name",p);
			}
			set_label(l,script_pos,p);

			// エクスポートされるラベルならチェック
			*p2 = 0;
			if((p[0] == 'O' || p[0] == 'o') && (p[1] == 'N' || p[1] == 'n')) {
				for(i=2; p[i]; i++) {
					if(i >= 23 || (!isalnum(p[i]) && p[i] != '_')) {
						*p2 = c;
						disp_error_message("invalid label name",p);
					}
				}
				linkdb_insert(&scriptlabel_db,p,INT2PTR(script_pos));	// 外部用label db登録
			}
			*p2 = c;
			p=tmpp+1;
			continue;
		}

		// 他は全部一緒くた
		p=parse_line(p);
		p=skip_space(p);
		add_scriptc(C_EOL);

		set_label(LABEL_NEXTLINE,script_pos,p);
		str_data[LABEL_NEXTLINE].type=C_NOP;
		str_data[LABEL_NEXTLINE].backpatch=-1;
		str_data[LABEL_NEXTLINE].label=-1;
	}
	if(!p || !*p) {
		disp_error_message("missing right curly",p);
	}

	add_scriptc(C_NOP);
	script_size = script_pos;

	// 未解決のラベルを解決
	for(i=LABEL_START;i<str_num;i++){
		if(str_data[i].type==C_NOP){
			int j,next;
			str_data[i].type=C_NAME;
			str_data[i].label=i;

			if(vars_db) {
				if( str_data[i].backpatch != -1 ) {
					struct vars_info *v = (struct vars_info *)numdb_search(vars_db, i);
					if( v == NULL ) {
						v            = (struct vars_info *)aMalloc( sizeof( struct vars_info ) );
						v->file      = (char *)aStrdup( file );
						v->line      = line;
						v->use_count = 1;
						numdb_insert(vars_db, i, v);
						vars_count++;
					} else {
						v->use_count++;
					}
				}
			}
			for(j=str_data[i].backpatch;j>=0 && j!=0x00ffffff;){
				next=(*(int*)(script_buf+j)) & 0x00ffffff;
				script_buf[j]=i;
				script_buf[j+1]=i>>8;
				script_buf[j+2]=i>>16;
				j=next;
			}
		}
	}

#ifdef DEBUG_DISP
	for(i=0;i<script_pos;i++){
		if((i&15)==0) printf("%04x : ",i);
		printf("%02x ",script_buf[i]);
		if((i&15)==15) printf("\n");
	}
	printf("\n");
#endif

#ifdef DEBUG_DISASM
	printf("#DEBUG_DISASM: %s line %d\n", file, line);
	printf("------------------------------\n");
	i = 0;
	while(i < script_pos) {
		int j = i;
		printf("%06x ",i);

		switch(get_com(script_buf,&i)) {
		case C_EOL:	 printf("C_EOL"); break;
		case C_INT:	 printf("C_INT %d",get_num(script_buf,&i)); break;
		case C_POS:
			printf("C_POS 0x%06x",*(int*)(script_buf+i)&0xffffff);
			i += 3;
			break;
		case C_NAME:
			j = (*(int*)(script_buf+i)&0xffffff);
			printf("C_NAME %s",j == 0xffffff ? "?? unknown ??" : str_buf + str_data[j].str);
			i += 3;
			break;
		case C_ARG:     printf("C_ARG");     break;
		case C_FUNC:    printf("C_FUNC");    break;
		case C_ADD:     printf("C_ADD");     break;
		case C_SUB:     printf("C_SUB");     break;
		case C_MUL:     printf("C_MUL");     break;
		case C_DIV:     printf("C_DIV");     break;
		case C_MOD:     printf("C_MOD");     break;
		case C_POW:     printf("C_POW");     break;
		case C_EQ:      printf("C_EQ");      break;
		case C_NE:      printf("C_NE");      break;
		case C_GT:      printf("C_GT");      break;
		case C_GE:      printf("C_GE");      break;
		case C_LT:      printf("C_LT");      break;
		case C_LE:      printf("C_LE");      break;
		case C_AND:     printf("C_AND");     break;
		case C_OR:      printf("C_OR");      break;
		case C_XOR:     printf("C_XOR");     break;
		case C_LAND:    printf("C_LAND");    break;
		case C_LOR:     printf("C_LOR");     break;
		case C_R_SHIFT: printf("C_R_SHIFT"); break;
		case C_L_SHIFT: printf("C_L_SHIFT"); break;
		case C_NEG:     printf("C_NEG");     break;
		case C_NOT:     printf("C_NOT");     break;
		case C_LNOT:    printf("C_LNOT");    break;
		case C_NOP:     printf("C_NOP");     break;
		case C_OP3:     printf("C_OP3");     break;
		case C_STR:
			j = strlen(script_buf + i);
			printf("C_STR %s",script_buf + i);
			i += j+1;
			break;
		default:
			printf("unknown");
		}
		printf("\n");
	}
	printf("\n");
#endif

	code = (struct script_code *)aMalloc(sizeof(struct script_code) + script_size);
	code->script_vars = NULL;
	code->script_size = script_size;
	memcpy(code->script_buf, script_buf, script_size);
	aFree(script_buf);

	return code;
}

/*==========================================
 * エラー判定
 *------------------------------------------
 */
int script_is_error(struct script_code *code)
{
	return (code == &error_code)? 1: 0;
}

//
// 実行系
//

/*==========================================
 * ridからsdへの解決
 *------------------------------------------
 */
struct map_session_data *script_rid2sd(struct script_state *st)
{
	struct map_session_data *sd=map_id2sd(st->rid);

	if(!sd){
		printf("script_rid2sd: fatal error ! player not attached!\n");
	}
	return sd;
}

/*==========================================
 * script情報からメモリアルID取得
 *------------------------------------------
 */
int script_getmemorialid(struct script_state *st)
{
	struct npc_data *nd = map_id2nd(st->oid);
	int memorial_id = 0;

	// 実行NPCから取得
	if(nd && nd->bl.m >= 0) {
		memorial_id = map[nd->bl.m].memorial_id;
	}

	// 実行NPCがメモリアルダンジョン不在の場合はPCから取得
	if(memorial_id == 0) {
		struct map_session_data *sd = script_rid2sd(st);
		if(sd) {
			memorial_id = map[sd->bl.m].memorial_id;

			// PCがメモリアルダンジョン不在の場合はPTから取得
			if(memorial_id == 0) {
				struct party *pt = party_search(sd->status.party_id);
				if(pt) {
					memorial_id = pt->memorial_id;
				}
			}
		}
	}

	return memorial_id;
}

/*==========================================
 * 変数の読み取り
 *------------------------------------------
 */
void get_val(struct script_state *st,struct script_data *data)
{
	struct map_session_data *sd = NULL;
	char *name;
	char prefix, postfix;

	if(data->type != C_NAME)
		return;

	name    = str_buf+str_data[data->u.num&0x00ffffff].str;
	prefix  = *name;
	postfix = name[strlen(name)-1];

	if(postfix == '$') {
		// 文字列型
		data->type = C_CONSTSTR;
		if(str_data[data->u.num&0x00ffffff].type == C_STR) {
			data->u.str = str_data[data->u.num&0x00ffffff].u.str;
		} else {
			switch(prefix) {
			case '@':
				if((sd = script_rid2sd(st)) == NULL) {
					printf("get_val error name?: %s\n", name);
					data->u.str = "";
				} else {
					data->u.str = pc_readregstr(sd,data->u.num);
				}
				break;
			case '$':
				data->u.str = mapreg_getregstr(data->u.num);
				break;
			case '\'':
				{
					struct linkdb_node **n;
					if( data->ref ) {
						n = data->ref;
					} else if( name[1] == '@' ) {
						n = st->stack->var_function;
					} else {
						n = &st->script->script_vars;
					}
					data->u.str = (char *)linkdb_search(n, INT2PTR(data->u.num));
				}
				break;
			case '.':
				{
					int memorial_id = script_getmemorialid(st);
					struct memorial_data *md = memorial_search_data(memorial_id);

					if(md == NULL) {
						printf("get_val: illegal memorial_id string variable %s\n", name);
						data->u.str = "";
					}
					else {
						struct linkdb_node **n;
						n = &md->vars;
						data->u.str = (char *)linkdb_search(n, INT2PTR(data->u.num));
					}
				}
				break;
			default:
				printf("script: get_val: illegal scope string variable %s.\n", name);
				data->u.str = "!!ERROR!!";
				break;
			}
		}
		if(data->u.str == NULL) {
			data->u.str = "";
		}
	} else {
		// 数値型
		data->type = C_INT;
		if(str_data[data->u.num&0x00ffffff].type == C_INT) {
			data->u.num = str_data[data->u.num&0x00ffffff].u.val;
		} else if(str_data[data->u.num&0x00ffffff].type == C_PARAM) {
			if((sd = script_rid2sd(st)) == NULL) {
				printf("get_val error name?: %s\n", name);
				data->u.num = 0;
			} else {
				data->u.num = pc_readparam(sd,str_data[data->u.num&0x00ffffff].u.val);
			}
		} else {
			switch(prefix) {
			case '@':
				if((sd = script_rid2sd(st)) == NULL) {
					printf("get_val error name?: %s\n", name);
					data->u.num = 0;
				} else {
					data->u.num = pc_readreg(sd,data->u.num);
				}
				break;
			case '$':
				data->u.num = mapreg_getreg(data->u.num);
				break;
			case '#':
				if((sd = script_rid2sd(st)) == NULL) {
					printf("get_val error name?: %s\n", name);
					data->u.num = 0;
				} else {
					if(name[1] == '#')
						data->u.num = pc_readaccountreg2(sd,name);
					else
						data->u.num = pc_readaccountreg(sd,name);
				}
				break;
			case '\'':
				{
					struct linkdb_node **n;
					if( data->ref ) {
						n = data->ref;
					} else if( name[1] == '@' ) {
						n = st->stack->var_function;
					} else {
						n = &st->script->script_vars;
					}
					data->u.num = PTR2INT(linkdb_search(n, INT2PTR(data->u.num)));
				}
				break;
			case '.':
				{
					int memorial_id = script_getmemorialid(st);
					struct memorial_data *md = memorial_search_data(memorial_id);

					if(md == NULL) {
						printf("get_val: illegal memorial_id variable %s\n", name);
						data->u.num = 0;
					}
					else {
						struct linkdb_node **n;
						n = &md->vars;
						data->u.num = PTR2INT(linkdb_search(n, INT2PTR(data->u.num)));
					}
				}
				break;
			default:
				if((sd = script_rid2sd(st)) == NULL) {
					printf("get_val error name?: %s\n", name);
					data->u.num = 0;
				} else {
					data->u.num = pc_readglobalreg(sd,name);
				}
				break;
			}
		}
	}

	return;
}

/*==========================================
 * 変数の読み取り2
 *------------------------------------------
 */
void* get_val2(struct script_state *st,int num,struct linkdb_node **ref)
{
	struct script_data dat;

	dat.type  = C_NAME;
	dat.u.num = num;
	dat.ref   = ref;
	get_val(st,&dat);

	return (dat.type == C_INT)? INT2PTR(dat.u.num): (void*)dat.u.str;
}

/*==========================================
 * 変数設定用
 *------------------------------------------
 */
int set_reg(struct script_state *st,struct map_session_data *sd,int num,const char *name,const void *v,struct linkdb_node** ref)
{
	char prefix  = *name;
	char postfix = name[strlen(name)-1];

	if(postfix == '$') {
		// 文字列型
		const char *str = (const char *)v;
		switch(prefix) {
		case '@':
			pc_setregstr(sd,num,str);
			break;
		case '$':
			mapreg_setregstr(num,str,(name[1] == '@')? 0: 1);
			break;
		case '\'':
			{
				char *old_str;
				struct linkdb_node **n;
				if( ref ) {
					n = ref;
				} else if( name[1] == '@' ) {
					n = st->stack->var_function;
				} else {
					n = &st->script->script_vars;
				}
				if( str[0] ) {
					old_str = (char *)linkdb_replace(n, INT2PTR(num), aStrdup(str));
				} else {
					old_str = (char *)linkdb_erase(n, INT2PTR(num));
				}
				if(old_str)
					aFree(old_str);
			}
			break;
		case '.':
			{
				int memorial_id = script_getmemorialid(st);
				struct memorial_data *md = memorial_search_data(memorial_id);

				if(md == NULL) {
					printf("set_reg: illegal memorial_id string variable %s\n", name);
				}
				else {
					char *old_str;
					struct linkdb_node **n;

					n = &md->vars;
					if( str[0] ) {
						old_str = (char *)linkdb_replace(n, INT2PTR(num), aStrdup(str));
					} else {
						old_str = (char *)linkdb_erase(n, INT2PTR(num));
					}
					if(old_str)
						aFree(old_str);
				}
			}
			break;
		default:
			printf("script: set_reg: illegal scope string variable !\n");
			break;
		}
	} else {
		// 数値型
		int val = PTR2INT(v);
		if(str_data[num&0x00ffffff].type == C_PARAM) {
			pc_setparam(sd,str_data[num&0x00ffffff].u.val,val);
		} else {
			switch(prefix) {
			case '@':
				pc_setreg(sd,num,val);
				break;
			case '$':
				mapreg_setreg(num,val,(name[1] == '@')? 0: 1);
				break;
			case '#':
				if(name[1] == '#')
					pc_setaccountreg2(sd,name,val);
				else
					pc_setaccountreg(sd,name,val);
				break;
			case '\'':
				{
					struct linkdb_node **n;
					if( ref ) {
						n = ref;
					} else if( name[1] == '@' ) {
						n = st->stack->var_function;
					} else {
						n = &st->script->script_vars;
					}
					if( val != 0 ) {
						linkdb_replace(n, INT2PTR(num), INT2PTR(val));
					} else {
						linkdb_erase(n, INT2PTR(num));
					}
				}
				break;
			case '.':
				{
					int memorial_id = script_getmemorialid(st);
					struct memorial_data *md = memorial_search_data(memorial_id);

					if(md == NULL) {
						printf("set_reg: illegal memorial_id variable %s\n", name);
					}
					else {
						struct linkdb_node **n;

						n = &md->vars;
						if( val != 0 ) {
							linkdb_replace(n, INT2PTR(num), INT2PTR(val));
						} else {
							linkdb_erase(n, INT2PTR(num));
						}
					}
				}
				break;
			default:
				pc_setglobalreg(sd,name,val);
				break;
			}
		}
	}
	return 0;
}

/*==========================================
 * 文字列への変換
 *------------------------------------------
 */
char* conv_str(struct script_state *st,struct script_data *data)
{
	get_val(st,data);

	switch(data->type) {
	case C_INT:
		{
			char *buf = (char *)aCalloc(16, sizeof(char));
			sprintf(buf, "%d", data->u.num);
			data->type  = C_STR;
			data->u.str = buf;
		}
		break;
	case C_POS:
		// スクリプトのバグ（ラベルを引数に渡した場合）
		// 例: mes -;
		data->type  = C_CONSTSTR;
		data->u.str = "** SCRIPT ERROR **";
		printf("script: conv_str: label has used as argument !\n");
		break;
	case C_NAME:
		// テンポラリ。本来無いはず
		data->type  = C_CONSTSTR;
		data->u.str = str_buf+str_data[data->u.num].str;
		break;
	}
	return data->u.str;
}

/*==========================================
 * 数値へ変換
 *------------------------------------------
 */
int conv_num(struct script_state *st,struct script_data *data)
{
	get_val(st,data);
	if(data->type == C_STR || data->type == C_CONSTSTR) {
		char *p = data->u.str;
		data->u.num = (int)strtobxl(p, NULL, 0);
		if(data->type == C_STR) {
			aFree(p);
		}
		data->type = C_INT;
	}
	return data->u.num;
}

/*==========================================
 * スタックの拡張
 *------------------------------------------
 */
static void expand_stack(struct script_stack *stack)
{
	stack->sp_max += 64;
	stack->stack_data = (struct script_data *)aRealloc(stack->stack_data, sizeof(stack->stack_data[0]) * stack->sp_max);
}

/*==========================================
 * スタックへ数値をプッシュ
 *------------------------------------------
 */
void push_val(struct script_stack *stack,int type,int val)
{
	if(stack->sp >= stack->sp_max)
		expand_stack(stack);

	stack->stack_data[stack->sp].type  = type;
	stack->stack_data[stack->sp].u.num = val;
	stack->stack_data[stack->sp].ref   = NULL;
	stack->sp++;
}

/*==========================================
 * スタックへ数値＋リファレンスをプッシュ
 *------------------------------------------
 */
void push_val2(struct script_stack *stack,int type,int val,struct linkdb_node** ref)
{
	push_val(stack,type,val);
	stack->stack_data[stack->sp-1].ref = ref;
}

/*==========================================
 * スタックへ文字列をプッシュ
 *------------------------------------------
 */
void push_str(struct script_stack *stack,int type,unsigned char *str)
{
	if(stack->sp >= stack->sp_max)
		expand_stack(stack);

	stack->stack_data[stack->sp].type  = type;
	stack->stack_data[stack->sp].u.str = str;
	stack->stack_data[stack->sp].ref   = NULL;
	stack->sp++;
}

/*==========================================
 * スタックへポインタをプッシュ
 *------------------------------------------
 */
void push_ptr(struct script_stack *stack,int type,void *ptr)
{
	if(stack->sp >= stack->sp_max)
		expand_stack(stack);

	stack->stack_data[stack->sp].type  = type;
	stack->stack_data[stack->sp].u.ptr = ptr;
	stack->stack_data[stack->sp].ref   = NULL;
	stack->sp++;
}

/*==========================================
 * スタックへ複製をプッシュ
 *------------------------------------------
 */
void push_copy(struct script_stack *stack,int pos)
{
	switch(stack->stack_data[pos].type){
	case C_CONSTSTR:
		push_str(stack,C_CONSTSTR,stack->stack_data[pos].u.str);
		break;
	case C_STR:
		push_str(stack,C_STR,(unsigned char *)aStrdup(stack->stack_data[pos].u.str));
		break;
	case C_PTR:
		push_ptr(stack,C_PTR,stack->stack_data[pos].u.ptr);
		break;
	default:
		push_val2(
			stack,stack->stack_data[pos].type,stack->stack_data[pos].u.num,
			stack->stack_data[pos].ref
		);
		break;
	}
}

/*==========================================
 * スタックからポップ
 *------------------------------------------
 */
void pop_stack(struct script_stack* stack,int start,int end)
{
	int i;

	for(i=start;i<end;i++){
		if(stack->stack_data[i].type==C_STR){
			aFree(stack->stack_data[i].u.str);
		}
	}
	if(stack->sp>end){
		memmove(&stack->stack_data[start],&stack->stack_data[end],sizeof(stack->stack_data[0])*(stack->sp-end));
	}
	stack->sp-=end-start;
}

/*==========================================
 * スクリプト依存変数、関数依存変数の解放
 *------------------------------------------
 */
void script_free_vars(struct linkdb_node **node)
{
	struct linkdb_node *n = *node;

	while(n) {
		char *name   = str_buf + str_data[PTR2INT(n->key)&0x00ffffff].str;
		char postfix = name[strlen(name)-1];
		if( postfix == '$' ) {
			// 文字型変数なので、データ削除
			aFree(n->data);
		}
		n = n->next;
	}
	linkdb_final( node );
}

/*==========================================
 * スタックの解放
 *------------------------------------------
 */
void script_free_stack(struct script_stack *stack)
{
	int i;

	for(i = 0; i < stack->sp; i++) {
		if( stack->stack_data[i].type == C_STR ) {
			aFree( stack->stack_data[i].u.str );
		} else if( i > 0 && stack->stack_data[i].type == C_RETINFO ) {
			struct linkdb_node** n = (struct linkdb_node**)stack->stack_data[i-1].u.ptr;
			script_free_vars( n );
			aFree( n );
		}
	}
	script_free_vars( stack->var_function );
	aFree(stack->var_function);
	aFree(stack->stack_data);
	aFree(stack);
}

/*==========================================
 * スクリプトコードの解放
 *------------------------------------------
 */
void script_free_code(struct script_code* code)
{
	script_free_vars( &code->script_vars );
	aFree( code );
}

//
// 実行部main
//
/*==========================================
 * コマンドの読み取り
 *------------------------------------------
 */
static int unget_com_data = -1;

static int get_com(unsigned char *script,int *pos)
{
	int i,j;

	if(unget_com_data>=0){
		i=unget_com_data;
		unget_com_data=-1;
		return i;
	}
	if(script[*pos]>=0x80){
		return C_INT;
	}
	i=0; j=0;
	while(script[*pos]>=0x40){
		i=script[(*pos)++]<<j;
		j+=6;
	}
	return i+(script[(*pos)++]<<j);
}

/*==========================================
 * コマンドのプッシュバック（未使用）
 *------------------------------------------
 */
/*
static void unget_com(int c)
{
	if(unget_com_data!=-1){
		if(script_config.error_log)
			printf("unget_com can back only 1 data\n");
	}
	unget_com_data=c;
}
*/

/*==========================================
 * 数値の取得
 *------------------------------------------
 */
static int get_num(unsigned char *script,int *pos)
{
	int i=0,j=0;

	while(script[*pos]>=0xc0){
		i+=(script[(*pos)++]&0x7f)<<j;
		j+=6;
	}
	return i+((script[(*pos)++]&0x7f)<<j);
}

/*==========================================
 * スタックから値を取り出す
 *------------------------------------------
 */
static int pop_val(struct script_state* st)
{
	if(st->stack->sp<=0)
		return 0;
	st->stack->sp--;
	get_val(st,&(st->stack->stack_data[st->stack->sp]));
	if(st->stack->stack_data[st->stack->sp].type==C_INT)
		return st->stack->stack_data[st->stack->sp].u.num;
	return 0;
}

/*==========================================
 * 文字列型かどうか判定
 *------------------------------------------
 */
int isstr(struct script_data *c)
{
	if( c->type == C_STR || c->type == C_CONSTSTR )
		return 1;
	if( c->type == C_NAME ) {
		char *p = str_buf + str_data[c->u.num & 0xffffff].str;
		char postfix = p[strlen(p)-1];
		return (postfix == '$');
	}
	return 0;
}

/*==========================================
 * 加算演算子
 *------------------------------------------
 */
static void op_add(struct script_state* st)
{
	struct script_data *s1, *s2;

	st->stack->sp--;
	s1 = &st->stack->stack_data[st->stack->sp-1];
	s2 = &st->stack->stack_data[st->stack->sp];

	get_val(st,s1);
	get_val(st,s2);

	if(isstr(s1) || isstr(s2)) {
		conv_str(st,s1);
		conv_str(st,s2);
	}
	if(s2->type == C_INT) { // ii
		int *i1 = &s1->u.num;
		int *i2 = &s2->u.num;
		int ret = *i1 + *i2;
		atn_bignumber ret_bignum = (atn_bignumber)*i1 + (atn_bignumber)*i2;
		if(ret_bignum > 0x7FFFFFFF || ret_bignum < -1 * 0x7FFFFFFF) {
			printf("script::op_add overflow detected op:%d rid:%d\n",C_ADD,st->rid);
			ret = (ret_bignum > 0x7FFFFFFF ? 0x7FFFFFFF : -1 * 0x7FFFFFFF);
		}
		*i1 = ret;
	} else { // ssの予定
		char *buf = (char *)aCalloc(strlen(s1->u.str) + strlen(s2->u.str) + 1, sizeof(char));
		strcpy(buf,s1->u.str);
		strcat(buf,s2->u.str);
		if(s1->type == C_STR)
			aFree(s1->u.str);
		if(s2->type == C_STR)
			aFree(s2->u.str);
		s1->type  = C_STR;
		s1->u.str = buf;
	}
	s1->ref = NULL;
}

/*==========================================
 * 三項演算子
 *------------------------------------------
 */
static void op_3(struct script_state *st)
{
	int flag = 0;

	if( isstr(&st->stack->stack_data[st->stack->sp-3])) {
		char *str = conv_str(st,& (st->stack->stack_data[st->stack->sp-3]));
		flag = str[0];
	} else {
		flag = conv_num(st,& (st->stack->stack_data[st->stack->sp-3]));
	}
	if( flag ) {
		push_copy(st->stack, st->stack->sp-2 );
	} else {
		push_copy(st->stack, st->stack->sp-1 );
	}
	pop_stack(st->stack,st->stack->sp-4,st->stack->sp-1);
}

/*==========================================
 * 二項演算子(文字列)
 *------------------------------------------
 */
static void op_2str(struct script_state *st,int op,int sp1,int sp2)
{
	char *s1=st->stack->stack_data[sp1].u.str;
	char *s2=st->stack->stack_data[sp2].u.str;
	int a=0;

	switch(op){
	case C_EQ:
		a= (strcmp(s1,s2)==0);
		break;
	case C_NE:
		a= (strcmp(s1,s2)!=0);
		break;
	case C_GT:
		a= (strcmp(s1,s2)> 0);
		break;
	case C_GE:
		a= (strcmp(s1,s2)>=0);
		break;
	case C_LT:
		a= (strcmp(s1,s2)< 0);
		break;
	case C_LE:
		a= (strcmp(s1,s2)<=0);
		break;
	default:
		printf("Illegal string operator\n");
		break;
	}
	if(st->stack->stack_data[sp1].type==C_STR)
		aFree(s1);
	if(st->stack->stack_data[sp2].type==C_STR)
		aFree(s2);

	push_val(st->stack,C_INT,a);
}

/*==========================================
 * 二項演算子(数値)
 *------------------------------------------
 */
static void op_2num(struct script_state *st,int op,int i1,int i2)
{
	int ret = 0;
	atn_bignumber ret_bignum = 0;

	switch(op) {
	case C_MOD:     ret = i1 % i2;    break;
	case C_AND:     ret = i1 & i2;    break;
	case C_OR:      ret = i1 | i2;    break;
	case C_XOR:     ret = i1 ^ i2;    break;
	case C_LAND:    ret = (i1 && i2); break;
	case C_LOR:     ret = (i1 || i2); break;
	case C_EQ:      ret = (i1 == i2); break;
	case C_NE:      ret = (i1 != i2); break;
	case C_GT:      ret = (i1 >  i2); break;
	case C_GE:      ret = (i1 >= i2); break;
	case C_LT:      ret = (i1 <  i2); break;
	case C_LE:      ret = (i1 <= i2); break;
	case C_R_SHIFT: ret = i1>>i2;     break;
	case C_L_SHIFT: ret = i1<<i2;     break;
	default:
		switch(op) {
		case C_SUB:
			ret = i1 - i2;
			ret_bignum = (atn_bignumber)i1 - (atn_bignumber)i2;
			break;
		case C_MUL:
			ret = i1 * i2;
			ret_bignum = (atn_bignumber)i1 * (atn_bignumber)i2;
			break;
		case C_DIV:
			if(i2 == 0) {
				printf("script::op_2num division by zero.\n");
				ret = 0x7FFFFFFF;
				ret_bignum = 0;	// オーバーフロー対策を飛ばす
			} else {
				ret = i1 / i2;
				ret_bignum = (atn_bignumber)i1 / (atn_bignumber)i2;
			}
			break;
		case C_POW:
			if(i1 == 0 && i2 < 0) {
				printf("script::op_2num pow by zero and minus.\n");
				ret = 0;
				ret_bignum = 0;	// オーバーフロー対策を飛ばす
			} else {
				ret = (int)pow((double)i1, (double)i2);
				ret_bignum = (atn_bignumber)pow((double)i1, (double)i2);
			}
			break;
		}
		if(ret_bignum > 0x7FFFFFFF || ret_bignum < -1 * 0x7FFFFFFF) {
			printf("script::op_2num overflow detected op:%d rid:%d\n",op,st->rid);
			ret = (ret_bignum > 0x7FFFFFFF ? 0x7FFFFFFF : -1 * 0x7FFFFFFF);
		}
	}
	push_val(st->stack,C_INT,ret);
}

/*==========================================
 * 二項演算子
 *------------------------------------------
 */
static void op_2(struct script_state *st,int op)
{
	int i1,i2;
	char *s1=NULL,*s2=NULL;

	i2=pop_val(st);
	if( isstr(&st->stack->stack_data[st->stack->sp]) )
		s2=st->stack->stack_data[st->stack->sp].u.str;

	i1=pop_val(st);
	if( isstr(&st->stack->stack_data[st->stack->sp]) )
		s1=st->stack->stack_data[st->stack->sp].u.str;

	if( s1!=NULL && s2!=NULL ){
		// ss => op_2str
		op_2str(st,op,st->stack->sp,st->stack->sp+1);
	}else if( s1==NULL && s2==NULL ){
		// ii => op_2num
		op_2num(st,op,i1,i2);
	}else{
		// si,is => error
		printf("script: op_2: int&str, str&int not allow.\n");
		if(s1 && st->stack->stack_data[st->stack->sp].type == C_STR)
			aFree(s1);
		if(s2 && st->stack->stack_data[st->stack->sp+1].type == C_STR)
			aFree(s2);
		push_val(st->stack,C_INT,0);
	}
}

/*==========================================
 * 単項演算子
 *------------------------------------------
 */
static void op_1num(struct script_state *st,int op)
{
	int i1;

	i1=pop_val(st);
	switch(op){
	case C_NEG:
		i1=-i1;
		break;
	case C_NOT:
		i1=~i1;
		break;
	case C_LNOT:
		i1=!i1;
		break;
	}
	push_val(st->stack,C_INT,i1);
}

/*==========================================
 * 関数の実行
 *------------------------------------------
 */
static int run_func(struct script_state *st)
{
	int i,start_sp,end_sp,func;

	end_sp=st->stack->sp;

#ifdef DEBUG_RUN
	if(script_config.debug_mode_log) {
		printf("stack dump :");
		for(i=0;i<end_sp;i++){
			switch(st->stack->stack_data[i].type){
			case C_INT:
				printf(" int(%d)",st->stack->stack_data[i].u.num);
				break;
			case C_NAME:
				printf(" name(%s)",str_buf+str_data[st->stack->stack_data[i].u.num & 0xffffff].str);
				break;
			case C_ARG:
				printf(" arg");
				break;
			case C_POS:
				printf(" pos(0x%x)",st->stack->stack_data[i].u.num);
				break;
			case C_STR:
				printf(" str(%s)",st->stack->stack_data[i].u.str);
				break;
			case C_CONSTSTR:
				printf(" cstr(%s)",st->stack->stack_data[i].u.str);
				break;
			case C_RETINFO:
				printf(" retinfo(0x%x)",st->stack->stack_data[i].u.num);
				break;
			default:
				printf(" etc(%d,%d)",st->stack->stack_data[i].type,st->stack->stack_data[i].u.num);
				break;
			}
		}
		printf("\n");
	}
#endif
	for(i=end_sp-1;i>=0 && st->stack->stack_data[i].type!=C_ARG;i--);
	if(i<=0) {
		if(script_config.error_log)
			printf("function not found\n");
		st->state=END;
		return 0;
	}
	start_sp=i-1;
	st->start=i-1;
	st->end=end_sp;

	func=st->stack->stack_data[st->start].u.num;
	if(str_data[func].type!=C_FUNC ){
		printf("run_func: not function and command! (func_no : %d, func_type : %d)\n", func, str_data[func].type);
		st->state=END;
		return 0;
	}
#ifdef DEBUG_RUN
	printf("run_func : %s (func_no : %d, func_type : %d, pos : 0x%x)\n",
		str_buf+str_data[func].str,func,str_data[func].type,st->pos-1
	);
#endif
	if(str_data[func].func) {
		str_data[func].func(st);
	} else {
		if(script_config.error_log)
			printf("run_func : %s? (%d(%d))\n",str_buf+str_data[func].str,func,str_data[func].type);
		push_val(st->stack,C_INT,0);
	}

	if(st->state != RERUNLINE) {
		pop_stack(st->stack,start_sp,end_sp);
	}

	if(st->state==RETFUNC) {
		// ユーザー定義関数からの復帰
		int olddefsp=st->stack->defsp;
		int j;

		pop_stack(st->stack,st->stack->defsp,start_sp);	// 復帰に邪魔なスタック削除
		if(st->stack->defsp<5 || st->stack->stack_data[st->stack->defsp-1].type!=C_RETINFO){
			printf("script:run_func(return) return without callfunc or callsub!\n");
			st->state=END;
			return 0;
		}
		// 関数依存変数の削除
		script_free_vars( st->stack->var_function );
		aFree(st->stack->var_function);

		j = conv_num(st,& (st->stack->stack_data[st->stack->defsp-5]));									// 引数の数取得
		st->pos = conv_num(st,& (st->stack->stack_data[st->stack->defsp-1]));								// スクリプト位置の復元
		st->script = (struct script_code*)st->stack->stack_data[st->stack->defsp-3].u.ptr;		// スクリプトを復元
		st->stack->var_function = (struct linkdb_node**)st->stack->stack_data[st->stack->defsp-2].u.ptr; // 関数依存変数

		st->stack->defsp=conv_num(st,& (st->stack->stack_data[st->stack->defsp-4]));	// 基準スタックポインタを復元
		pop_stack(st->stack,olddefsp-5-j,olddefsp);		// 要らなくなったスタック(引数と復帰用データ)削除

		st->state=GOTO;
	}

	return 0;
}

/*==========================================
 * スクリプトの実行
 *------------------------------------------
 */
static void run_script_main(struct script_state *st);
void run_script_awake(struct script_state *st);

void run_script(struct script_code *rootscript,int pos,int rid,int oid)
{
	struct script_state *st;
	struct map_session_data *sd = NULL;

	if(rootscript == NULL || pos < 0)
		return;

	sd = map_id2sd(rid);
	st = (struct script_state *)aCalloc(1, sizeof(struct script_state));

	if(sd && sd->stack && sd->npc_scriptroot == rootscript) {
		// 前回のスタックを復帰
		st->script = sd->npc_script;
		st->stack  = sd->stack;
		st->state  = sd->npc_scriptstate;
		sd->stack           = NULL; // プレイヤーがデタッチされても良いようにクリア
		sd->npc_script	    = NULL;
		sd->npc_scriptroot  = NULL;
		sd->npc_scriptstate = 0;
	} else {
		// スタック初期化
		st->stack = (struct script_stack *)aMalloc(sizeof(struct script_stack));
		st->stack->sp     = 0;
		st->stack->defsp  = 0;
		st->stack->sp_max = 64;
		st->stack->stack_data   = (struct script_data *)aCalloc(st->stack->sp_max,sizeof(st->stack->stack_data[0]));
		st->stack->var_function = (struct linkdb_node **)aCalloc(1, sizeof(struct linkdb_node*));
		st->state  = RUN;
		st->script = rootscript;
	}
	st->pos = pos;
	st->rid = rid;
	st->oid = oid;
	st->scriptroot = rootscript;
	st->sleep.timer = -1;
	if(sd) {
		npc_timeout_start(sd);
		if(sd->npc_dynamic_id == sd->npc_id)
			npc_dynamicnpc_start(sd);
	}
	run_script_main(st);	// stのfreeも含めてこの内部で処理する
}

/*==========================================
 * 指定ノードをsleep_dbから削除
 *------------------------------------------
 */
struct linkdb_node* script_erase_sleepdb(struct linkdb_node *n)
{
	struct linkdb_node *retnode;

	if( n == NULL)
		return NULL;
	if( n->prev == NULL )
		sleep_db = n->next;
	else
		n->prev->next = n->next;
	if( n->next )
		n->next->prev = n->prev;
	retnode = n->next;
	aFree( n );
	return retnode;		// 次のノードを返す
}

/*==========================================
 * sleep用タイマー関数
 *------------------------------------------
 */
int run_script_timer(int tid, unsigned int tick, int id, void *data)
{
	struct script_state *st = (struct script_state *)data;

	if(st->sleep.timer != -1) {
		struct linkdb_node *node = sleep_db;
		while( node ) {
			if( PTR2INT(node->key) == st->oid && ((struct script_state *)node->data)->sleep.timer == st->sleep.timer ) {
				script_erase_sleepdb(node);
				break;
			}
			node = node->next;
		}
	}
	run_script_awake(st);
	return 0;
}

/*==========================================
 * sleep復帰処理
 *------------------------------------------
 */
void run_script_awake(struct script_state *st)
{
	struct map_session_data *sd = map_id2sd(st->rid);
	struct mob_data *md = map_id2md(st->rid);

	if( (sd && sd->npc_sleep != &st->sleep) || (st->rid != 0 && !sd && !md) ) {
		st->rid = 0;
	}

	if(st->state != RERUNLINE) {
		st->state = END;
		st->sleep.tick = 0;
	}
	st->sleep.timer = -1;
	if(sd) {
		npc_timeout_start(sd);
		if(sd->npc_dynamic_id == sd->npc_id)
			npc_dynamicnpc_start(sd);
	}

	run_script_main(st);
	return;
}

/*==========================================
 * sleep破棄処理
 *------------------------------------------
 */
void script_erase_sleeptimer(int id)
{
	struct linkdb_node *node = (struct linkdb_node *)sleep_db;

	while(node) {
		if(PTR2INT(node->key) == id) {
			struct script_state *st = (struct script_state *)node->data;

			if(st->sleep.timer != -1) {
				delete_timer(st->sleep.timer, run_script_timer);
				node = script_erase_sleepdb(node);

				st->pos = -1;
				script_free_stack(st->stack);
				aFree(st);
				break;
			}
		}
		node = node->next;
	}
	return;
}

/*==========================================
 * スクリプトの実行メイン部分
 *------------------------------------------
 */
static void run_script_main(struct script_state *st)
{
	int c;
	int cmdcount  = script_config.check_cmdcount;
	int gotocount = script_config.check_gotocount;
	struct map_session_data *sd;

	if(st->state == RERUNLINE) {
		st->state = RUN;
		run_func(st);
		if(st->state == GOTO) {
			st->state = RUN;
		}
	} else if(st->state != END) {
		st->state = RUN;
	}

	while(st->state == RUN) {
		switch(c = get_com(st->script->script_buf,&st->pos)) {
		case C_EOL:
			if(st->stack->sp != st->stack->defsp) {
				if(script_config.error_log)
					printf("stack.sp(%d) != default(%d)\n",st->stack->sp,st->stack->defsp);
				pop_stack(st->stack, st->stack->defsp, st->stack->sp);
			}
			break;
		case C_INT:
			push_val(st->stack,C_INT,get_num(st->script->script_buf,&st->pos));
			break;
		case C_POS:
		case C_NAME:
			push_val(st->stack,c,(*(int*)(st->script->script_buf+st->pos))&0xffffff);
			st->pos += 3;
			break;
		case C_ARG:
			push_val(st->stack,c,0);
			break;
		case C_STR:
			push_str(st->stack,C_CONSTSTR,st->script->script_buf+st->pos);
			while(st->script->script_buf[st->pos++]);
			break;
		case C_FUNC:
			run_func(st);
			if(st->state == GOTO) {
				st->state = RUN;
				if(gotocount > 0 && (--gotocount) <= 0) {
					printf("run_script: infinity loop ! gotocount %d\n", script_config.check_gotocount);
					st->state = END;
				}
			}
			break;
		case C_ADD:
			op_add(st);
			break;
		case C_SUB:
		case C_MUL:
		case C_DIV:
		case C_MOD:
		case C_POW:
		case C_EQ:
		case C_NE:
		case C_GT:
		case C_GE:
		case C_LT:
		case C_LE:
		case C_AND:
		case C_OR:
		case C_XOR:
		case C_LAND:
		case C_LOR:
		case C_R_SHIFT:
		case C_L_SHIFT:
			op_2(st,c);
			break;
		case C_NEG:
		case C_NOT:
		case C_LNOT:
			op_1num(st,c);
			break;
		case C_OP3:
			op_3(st);
			break;
		case C_NOP:
			st->state = END;
			break;
		default:
			if(script_config.error_log)
				printf("unknown command : %d @ 0x%06x\n",c,st->pos);
			st->state = END;
			break;
		}
		if(cmdcount > 0 && (--cmdcount) <= 0) {
			printf("run_script: infinity loop ! cmdcount %d\n", script_config.check_cmdcount);
			st->state = END;
		}
	}

	sd = map_id2sd(st->rid);
	if(st->sleep.tick > 0) {
		// スタック情報をsleep_dbに保存
		if(sd) {
			// デタッチされたかどうかの判定用
			sd->npc_sleep = &st->sleep;
			npc_timeout_stop(sd);
		}
		st->sleep.timer = add_timer(gettick() + st->sleep.tick, run_script_timer, 0, st);
		linkdb_insert(&sleep_db, INT2PTR(st->oid), st);
		return;
	}

	if(st->state != END && sd) {
		if(sd->stack) {
			// 元のスタック情報を破棄
			script_free_stack(sd->stack);
			sd->state.menu_or_input = 0;
			sd->progressbar.npc_id = 0;
			sd->progressbar.tick = 0;
		}
		if(sd->progressbar.tick > 0) {
			npc_timeout_stop(sd);
		}

		// 再開するためにスタック情報を保存
		sd->npc_script      = st->script;
		sd->npc_scriptroot  = st->scriptroot;
		sd->npc_scriptstate = st->state;
		sd->stack           = st->stack;
		sd->npc_id          = st->oid;
		sd->npc_pos         = st->pos;
	} else {
		// 実行が終わった or 続行不可能なのでスタッククリア
		if(sd) {
			npc_timeout_stop(sd);
			if(st->oid == sd->npc_id)
				npc_event_dequeue(sd);
		}
		st->pos = -1;
		script_free_stack(st->stack);
	}
	aFree(st);

	return;
}

/*==========================================
 * 永続的マップ変数の自動セーブ
 *------------------------------------------
 */
static int script_autosave_mapreg(int tid,unsigned int tick,int id,void *data)
{
	mapreg_autosave();

	return 0;
}

/*==========================================
 * poswordの設定
 *------------------------------------------
 */
static void set_posword(const char *p)
{
	const char *np;
	int i;
	size_t len, max = sizeof(refine_posword[0])/sizeof(refine_posword[0][0]);

	for(i = 0; i < EQUIP_INDEX_MAX + 1; i++) {
		if((np = strchr(p,',')) != NULL) {
			len = np - p;
			if(len >= max)
				len = max - 1;
		} else {
			len = strlen(p);
		}
		strncpy(refine_posword[i], p, len);
		refine_posword[i][len] = '\0';	// force \0 terminal

		if(np == NULL)
			break;
		p = np + 1;
	}
}

/*==========================================
 * config読み込み
 *------------------------------------------
 */
int script_config_read(const char *cfgName)
{
	char line[1024], w1[1024], w2[1024];
	FILE *fp;
	static int count = 0;

	if(count++ == 0) {
		script_config.debug_vars = 0;
		script_config.warn_func_no_comma = 1;
		script_config.warn_cmd_no_comma  = 1;
		script_config.warn_func_mismatch_paramnum = 1;
		script_config.warn_cmd_mismatch_paramnum  = 1;
		script_config.check_cmdcount  = 65536;
		script_config.check_gotocount = 16384;
		script_config.debug_mode_log = 1;
		script_config.error_log = 1;
		script_config.sql_script_enable = 0;
	}

	fp = fopen(cfgName,"r");
	if(fp == NULL) {
		printf("script_config_read: open [%s] failed !\n", cfgName);
		return 1;
	}
	while(fgets(line, 1020, fp)) {
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0] == '/' && line[1] == '/')
			continue;
		if(sscanf(line, "%1023[^:]: %1023[^\r\n]", w1, w2) != 2)
			continue;

		if(strcmpi(w1, "debug_vars") == 0) {
			script_config.debug_vars = atoi(w2);
		}
		else if(strcmpi(w1, "refine_posword") == 0) {
			set_posword(w2);
		}
		else if(strcmpi(w1, "check_cmdcount") == 0) {
			script_config.check_cmdcount = atoi(w2);
		}
		else if(strcmpi(w1, "check_gotocount") == 0) {
			script_config.check_gotocount = atoi(w2);
		}
		else if(strcmpi(w1, "error_marker_start") == 0) {
			strncpy(error_marker_start, w2, 16);
			error_marker_start[15] = '\0';
		}
		else if(strcmpi(w1, "error_marker_end") == 0) {
			strncpy(error_marker_end, w2, 16);
			error_marker_end[15] = '\0';
		}
		else if(strcmpi(w1, "debug_mode_log") == 0) {
			script_config.debug_mode_log = atoi(w2);
		}
		else if(strcmpi(w1, "error_log") == 0) {
			script_config.error_log = atoi(w2);
		}
		else if (strcmpi(w1, "mapreg_autosave_time") == 0) {
			mapreg_autosave_interval = atoi(w2) * 1000;
			if (mapreg_autosave_interval <= 0) {
				printf("script_config_read: Invalid autosave_time value: %d. Set to %d (default).\n", mapreg_autosave_interval, (int)(MAPREG_AUTOSAVE_INTERVAL / 1000));
				mapreg_autosave_interval = MAPREG_AUTOSAVE_INTERVAL;
			}
		}
		if (strcmpi(w1, "sql_script_enable") == 0) {
			script_config.sql_script_enable = atoi(w2);
		}
#ifndef TXT_ONLY
		else if(strcmpi(w1,"script_server_ip") == 0) {
			strncpy(script_server_ip, w2, sizeof(script_server_ip) - 1);
		}
		else if(strcmpi(w1,"script_server_port") == 0) {
			script_server_port = (unsigned short)atoi(w2);
		}
		else if(strcmpi(w1,"script_server_id") == 0) {
			strncpy(script_server_id, w2, sizeof(script_server_id) - 1);
		}
		else if(strcmpi(w1,"script_server_pw") == 0) {
			strncpy(script_server_pw, w2, sizeof(script_server_pw) - 1);
		}
		else if(strcmpi(w1,"script_server_db") == 0) {
			strncpy(script_server_db, w2, sizeof(script_server_db) - 1);
		}
		else if(strcmpi(w1,"script_server_charset") == 0) {
			strncpy(script_server_charset, w2, sizeof(script_server_charset) - 1);
		}
		else if(strcmpi(w1,"script_server_keepalive") == 0) {
			script_server_keepalive = atoi(w2);
		}
#endif
		else if(strcmpi(w1,"import") == 0) {
			script_config_read(w2);
		}
	}
	fclose(fp);

	return 0;
}

/*==========================================
 * "this" を考慮してmap名からmap番号へ変換
 *------------------------------------------
 */
int script_mapname2mapid(struct script_state *st,const char *mapname)
{
	if(strcmp(mapname,"this")==0)
	{
		struct npc_data *nd = map_id2nd(st->oid);
		if(nd) {
			return nd->bl.m;
		} else {
			struct map_session_data *sd = script_rid2sd(st);
			return (sd != NULL)? sd->bl.m: -1;
		}
	}
	return map_mapname2mapid(mapname);
}

/*==========================================
 * @readvars, @writevars用関数
 *------------------------------------------
 */
int script_check_variable(const char *name,int array_flag,int read_only)
{
	int i = search_str(name);

	if(i < 0)
		return 0;

	switch(str_data[i].type) {
		case C_NAME:		// 変数は無条件で許可
			return 1;
		case C_PARAM:		// 埋め込み変数は[]がなければ許可
			if(!array_flag)
				return 1;
			break;
		case C_INT:		// 定数は[]がなくて読み取り時のみ許可
		case C_STR:
			if(!array_flag && read_only)
				return 1;
			break;
	}
	return 0;
}

void* script_read_vars(struct map_session_data *sd,const char *var,int elem,struct linkdb_node **ref)
{
	if(sd) {
		// プレイヤーにアタッチする必要があるならstを用意
		struct script_state st;

		memset(&st, 0, sizeof(st));
		st.rid = sd->bl.id;
		return get_val2(&st, (elem<<24) | add_str(var), ref);
	}

	return get_val2(NULL, (elem<<24) | add_str(var), ref);
}

void script_write_vars(struct map_session_data *sd,const char *var,int elem,void *v,struct linkdb_node **ref)
{
	set_reg(NULL, sd, (elem<<24) | add_str(var), var, v, ref);

	return;
}

/*==========================================
 * 使用された変数の一覧を出力
 *------------------------------------------
 */
static int varlist_sort1(void *key,void *data,va_list ap)
{
	int *count  = va_arg(ap, int*);
	int *v      = va_arg(ap, int*);

	v[(*count)++] = PTR2INT(key);
	return 0;
}

static int varlist_sort2(const void *a, const void *b)
{
	char *name1 = str_buf + str_data[*(const int*)a].str;
	char *name2 = str_buf + str_data[*(const int*)b].str;

	return strcmp(name1, name2);
}

static int varsdb_final(void *key,void *data,va_list ap)
{
	struct vars_info *v = (struct vars_info*)data;

	aFree( v->file );
	aFree( v );
	return 0;
}

static int varsdb_output(void)
{
	if( vars_db ) {
		FILE *fp = fopen("variables.txt", "wt");
		if( fp ) {
			int i;
			int *vlist = (int *)aMalloc( vars_count * sizeof(int) );
			int count  = 0;
			numdb_foreach(vars_db, varlist_sort1, &count, vlist);
			qsort( vlist, count, sizeof(int), varlist_sort2 );

			printf("do_final_script: enum used variables\n");
			for(i = 0; i < count; i++) {
				char *name = str_buf + str_data[ vlist[i] ].str;
				struct vars_info *v = (struct vars_info *)numdb_search( vars_db, INT2PTR(vlist[i]) );
				if( strncmp(name, "$@__", 4) != 0 ) {
					// switch の内部変数は除外
					fprintf(fp, "%-20s % 4d %s line %d" NEWLINE, name, v->use_count, v->file, v->line);
				}
			}
			aFree( vlist );
			fclose(fp);
		}
		numdb_final(vars_db, varsdb_final);
	}
	return 0;
}

/*==========================================
 * ハッシュ関連情報を出力
 *------------------------------------------
 */
#ifdef DEBUG_HASH

static int debug_hash_output(void)
{
	FILE *fp = fopen("hash_dump.txt", "wt");

	if(fp) {
		int i,count[SCRIPT_HASH_SIZE];
		int max=0;
		int *buckets;

		printf("do_final_script: dumping script str hash information\n");
		memset(count, 0, sizeof(count));

		fprintf(fp, "#1 dump all data" NEWLINE);
		fprintf(fp, "-------+--------+----------------------" NEWLINE);
		fprintf(fp, "  num  |  hash  | data_name"             NEWLINE);
		fprintf(fp, "-------+--------+----------------------" NEWLINE);
		for(i=LABEL_START; i<str_num; i++) {
			unsigned int h = calc_hash(str_buf+str_data[i].str);
			fprintf(fp, " %05d | %6u | %s" NEWLINE, i, h, str_buf+str_data[i].str);
			if(++count[h] > max)
				max = count[h];
		}
		fprintf(fp, "-------+--------+----------------------" NEWLINE);

		buckets = (int *)aCalloc((max+1),sizeof(int));

		fprintf(fp, "#2 how many data is there in one hash" NEWLINE);
		fprintf(fp, "--------+-------" NEWLINE);
		fprintf(fp, "  hash  | count"  NEWLINE);
		fprintf(fp, "--------+-------" NEWLINE);
		for(i=0; i<SCRIPT_HASH_SIZE; i++) {
			fprintf(fp, " %6d | %5d" NEWLINE, i, count[i]);
			buckets[count[i]]++;
		}
		fprintf(fp, "--------+-------" NEWLINE);

		fprintf(fp, "#3 distribution of hashed data" NEWLINE);
		fprintf(fp, "-------+---------+---------" NEWLINE);
		fprintf(fp, " items | buckets | percent"  NEWLINE);
		fprintf(fp, "-------+---------+---------" NEWLINE);
		for(i=0; i<=max; i++) {
			fprintf(fp, " %5d | %7d | %6.2lf%%" NEWLINE, i, buckets[i], (double)buckets[i]/SCRIPT_HASH_SIZE*100.);
		}
		aFree(buckets);
		fclose(fp);
	}
	return 0;
}

#endif

/*==========================================
 * 終了
 *------------------------------------------
 */
static int userfunc_db_final(void *key,void *data,va_list ap)
{
	aFree(key);
	script_free_code((struct script_code *)data);
	return 0;
}

int do_final_script(void)
{
	int i;

	mapreg_final();

	if(userfunc_db)
		strdb_final(userfunc_db,userfunc_db_final);
	if(scriptlabel_db)
		linkdb_final(&scriptlabel_db);
	if(sleep_db) {
		struct linkdb_node *n = sleep_db;
		while(n) {
			struct script_state *st = (struct script_state *)n->data;
			script_free_stack(st->stack);
			aFree(st);
			n = n->next;
		}
		linkdb_final(&sleep_db);
	}
	varsdb_output();

#ifdef DEBUG_HASH
	debug_hash_output();
#endif

#ifndef NO_CSVDB_SCRIPT
	script_csvfinal();
#endif

	for(i = LABEL_START; i < str_num; i++) {
		if(str_data[i].type == C_STR)
			aFree(str_data[i].u.str);
	}
	aFree(str_buf);
	aFree(str_data);

#ifndef TXT_ONLY
	if(sql_is_connect)
		sqldbs_close(&mysql_handle_script);
#endif

	return 0;
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
int do_init_script(void)
{
	unsigned int tick = gettick();

#ifndef TXT_ONLY
	// DB connection initialized
	if( script_config.sql_script_enable )
	{
		sql_is_connect = sqldbs_connect(&mysql_handle_script, script_server_ip, script_server_id, script_server_pw, script_server_db, script_server_port, script_server_charset, script_server_keepalive, "SCRIPT");
		if( sql_is_connect == false ) {
			printf("FATAL ERROR: do_init_script() failed !!\n");
			exit(1);
		}
	}
#endif

	add_timer_func_list(run_script_timer);
	add_timer_func_list(script_autosave_mapreg);

	add_timer_interval(tick + mapreg_autosave_interval, script_autosave_mapreg, 0, NULL, mapreg_autosave_interval);

#ifndef NO_CSVDB_SCRIPT
	script_csvinit();
#endif

	if(script_config.debug_vars)
		vars_db = numdb_init();

	if( mapreg_init() == false ) {
		printf("FATAL ERROR: mapreg_init() failed !!\n");
		exit(1);
	}

	return 0;
}

//
// 埋め込み関数
//

int buildin_mes(struct script_state *st);
int buildin_messize(struct script_state *st);
int buildin_mespos(struct script_state *st);
int buildin_mesalign(struct script_state *st);
int buildin_goto(struct script_state *st);
int buildin_callsub(struct script_state *st);
int buildin_callfunc(struct script_state *st);
int buildin_return(struct script_state *st);
int buildin_getarg(struct script_state *st);
int buildin_getargcount(struct script_state *st);
int buildin_next(struct script_state *st);
int buildin_close(struct script_state *st);
int buildin_close2(struct script_state *st);
int buildin_clear(struct script_state *st);
int buildin_menu(struct script_state *st);
int buildin_rand(struct script_state *st);
int buildin_warp(struct script_state *st);
int buildin_mapwarp(struct script_state *st);
int buildin_areawarp(struct script_state *st);
int buildin_heal(struct script_state *st);
int buildin_itemheal(struct script_state *st);
int buildin_percentheal(struct script_state *st);
int buildin_jobchange(struct script_state *st);
int buildin_input(struct script_state *st);
int buildin_setlook(struct script_state *st);
int buildin_getlook(struct script_state *st);
int buildin_set(struct script_state *st);
int buildin_setarray(struct script_state *st);
int buildin_cleararray(struct script_state *st);
int buildin_copyarray(struct script_state *st);
int buildin_getarraysize(struct script_state *st);
int buildin_deletearray(struct script_state *st);
int buildin_printarray(struct script_state *st);
int buildin_getelementofarray(struct script_state *st);
int buildin_getitem(struct script_state *st);
int buildin_getitem2(struct script_state *st);
int buildin_getoptitem(struct script_state *st);
int buildin_itempreview(struct script_state *st);
int buildin_delitem(struct script_state *st);
int buildin_delcartitem(struct script_state *st);
int buildin_delitem2(struct script_state *st);
int buildin_delcartitem2(struct script_state *st);
int buildin_viewpoint(struct script_state *st);
int buildin_countitem(struct script_state *st);
int buildin_countcartitem(struct script_state *st);
int buildin_checkweight(struct script_state *st);
int buildin_checkitemblank(struct script_state *st);
int buildin_readparam(struct script_state *st);
int buildin_getcharid(struct script_state *st);
int buildin_getnpcid(struct script_state *st);
int buildin_getcharname(struct script_state *st);
int buildin_getpartyname(struct script_state *st);
int buildin_getpartymember(struct script_state *st);
int buildin_getguildname(struct script_state *st);
int buildin_getguildmaster(struct script_state *st);
int buildin_getguildmasterid(struct script_state *st);
int buildin_strcharinfo(struct script_state *st);
int buildin_getequipid(struct script_state *st);
int buildin_getequipname(struct script_state *st);
int buildin_getequipisequiped(struct script_state *st);
int buildin_getequipisenableref(struct script_state *st);
int buildin_getequipisidentify(struct script_state *st);
int buildin_getequiprefinerycnt(struct script_state *st);
int buildin_getequipweaponlv(struct script_state *st);
int buildin_getequippercentrefinery(struct script_state *st);
int buildin_delequip(struct script_state *st);
int buildin_successrefitem(struct script_state *st);
int buildin_failedrefitem(struct script_state *st);
int buildin_downrefitem(struct script_state *st);
int buildin_getequippos(struct script_state *st);
int buildin_cutin(struct script_state *st);
int buildin_cutincard(struct script_state *st);
int buildin_statusup(struct script_state *st);
int buildin_statusup2(struct script_state *st);
int buildin_bonus(struct script_state *st);
int buildin_bonus2(struct script_state *st);
int buildin_bonus3(struct script_state *st);
int buildin_bonus4(struct script_state *st);
int buildin_skill(struct script_state *st);
int buildin_guildskill(struct script_state *st);
int buildin_getskilllv(struct script_state *st);
int buildin_getgdskilllv(struct script_state *st);
int buildin_basicskillcheck(struct script_state *st);
int buildin_getgmlevel(struct script_state *st);
int buildin_end(struct script_state *st);
int buildin_checkoption(struct script_state *st);
int buildin_setoption(struct script_state *st);
int buildin_setcart(struct script_state *st);
int buildin_setfalcon(struct script_state *st);
int buildin_setriding(struct script_state *st);
int buildin_setdragon(struct script_state *st);
int buildin_setgear(struct script_state *st);
int buildin_sit(struct script_state *st);
int buildin_stand(struct script_state *st);
int buildin_savepoint(struct script_state *st);
int buildin_gettimetick(struct script_state *st);
int buildin_gettime(struct script_state *st);
int buildin_gettimestr(struct script_state *st);
int buildin_openstorage(struct script_state *st);
int buildin_guildopenstorage(struct script_state *st);
int buildin_itemskill(struct script_state *st);
int buildin_produce(struct script_state *st);
int buildin_monster(struct script_state *st);
int buildin_areamonster(struct script_state *st);
int buildin_killmonster(struct script_state *st);
int buildin_killmonsterall(struct script_state *st);
int buildin_areakillmonster(struct script_state *st);
int buildin_doevent(struct script_state *st);
int buildin_donpcevent(struct script_state *st);
int buildin_addtimer(struct script_state *st);
int buildin_deltimer(struct script_state *st);
int buildin_addtimercount(struct script_state *st);
int buildin_gettimerdiff(struct script_state *st);
int buildin_initnpctimer(struct script_state *st);
int buildin_stopnpctimer(struct script_state *st);
int buildin_startnpctimer(struct script_state *st);
int buildin_setnpctimer(struct script_state *st);
int buildin_getnpctimer(struct script_state *st);
int buildin_announce(struct script_state *st);
int buildin_mapannounce(struct script_state *st);
int buildin_areaannounce(struct script_state *st);
int buildin_getusers(struct script_state *st);
int buildin_getmapusers(struct script_state *st);
int buildin_getareausers(struct script_state *st);
int buildin_getareadropitem(struct script_state *st);
int buildin_enablenpc(struct script_state *st);
int buildin_disablenpc(struct script_state *st);
int buildin_hideoffnpc(struct script_state *st);
int buildin_hideonnpc(struct script_state *st);
int buildin_cloakoffnpc(struct script_state *st);
int buildin_cloakonnpc(struct script_state *st);
int buildin_sc_start(struct script_state *st);
int buildin_sc_start2(struct script_state *st);
int buildin_sc_starte(struct script_state *st);
int buildin_sc_start3(struct script_state *st);
int buildin_sc_end(struct script_state *st);
int buildin_sc_ison(struct script_state *st);
int buildin_getscrate(struct script_state *st);
int buildin_debugmes(struct script_state *st);
int buildin_catchpet(struct script_state *st);
int buildin_birthpet(struct script_state *st);
int buildin_resetstatus(struct script_state *st);
int buildin_resetskill(struct script_state *st);
int buildin_changebase(struct script_state *st);
int buildin_changesex(struct script_state *st);
int buildin_waitingroom(struct script_state *st);
int buildin_delwaitingroom(struct script_state *st);
int buildin_kickwaitingroom(struct script_state *st);
int buildin_kickwaitingroomall(struct script_state *st);
int buildin_enablewaitingroomevent(struct script_state *st);
int buildin_disablewaitingroomevent(struct script_state *st);
int buildin_getwaitingroomstate(struct script_state *st);
int buildin_warpwaitingpc(struct script_state *st);
int buildin_getwaitingpcid(struct script_state *st);
int buildin_attachrid(struct script_state *st);
int buildin_detachrid(struct script_state *st);
int buildin_isloggedin(struct script_state *st);
int buildin_setmapflag(struct script_state *st);
int buildin_removemapflag(struct script_state *st);
int buildin_checkmapflag(struct script_state *st);
int buildin_pvpon(struct script_state *st);
int buildin_pvpoff(struct script_state *st);
int buildin_gvgon(struct script_state *st);
int buildin_gvgoff(struct script_state *st);
int buildin_emotion(struct script_state *st);
int buildin_maprespawnguildid(struct script_state *st);
int buildin_agitstart(struct script_state *st);
int buildin_agitend(struct script_state *st);
int buildin_agitcheck(struct script_state *st);
int buildin_flagemblem(struct script_state *st);
int buildin_getcastlename(struct script_state *st);
int buildin_getcastledata(struct script_state *st);
int buildin_setcastledata(struct script_state *st);
int buildin_requestguildinfo(struct script_state *st);
int buildin_getequipcardcnt(struct script_state *st);
int buildin_successremovecards(struct script_state *st);
int buildin_failedremovecards(struct script_state *st);
int buildin_marriage(struct script_state *st);
int buildin_wedding_effect(struct script_state *st);
int buildin_divorce(struct script_state *st);
int buildin_getitemname(struct script_state *st);
int buildin_makepet(struct script_state *st);
int buildin_getinventorylist(struct script_state *st);
int buildin_getcartlist(struct script_state *st);
int buildin_getskilllist(struct script_state *st);
int buildin_clearitem(struct script_state *st);
int buildin_clearcartitem(struct script_state *st);
int buildin_getrepairableitemcount(struct script_state *st);
int buildin_repairitem(struct script_state *st);
int buildin_classchange(struct script_state *st);
int buildin_setnpcdisplay(struct script_state *st);
int buildin_misceffect(struct script_state *st);
int buildin_areamisceffect(struct script_state *st);
int buildin_soundeffect(struct script_state *st);
int buildin_areasoundeffect(struct script_state *st);
int buildin_delmisceffect(struct script_state *st);
int buildin_gmcommand(struct script_state *st);
int buildin_getusersname(struct script_state *st);
int buildin_dispbottom(struct script_state *st);
int buildin_recovery(struct script_state *st);
int buildin_getpetinfo(struct script_state *st);
int buildin_gethomuninfo(struct script_state *st);
int buildin_checkequipedcard(struct script_state *st);
int buildin_globalmes(struct script_state *st);
int buildin_jump_zero(struct script_state *st);
int buildin_select(struct script_state *st);
int buildin_getmapmobs(struct script_state *st);
int buildin_getareamobs(struct script_state *st);
int buildin_getmapmoblist(struct script_state *st);
int buildin_getguildrelation(struct script_state *st);
int buildin_unequip(struct script_state *st);
int buildin_allowuseitem(struct script_state *st);
int buildin_equippeditem(struct script_state *st);
int buildin_getmapname(struct script_state *st);
int buildin_summon(struct script_state *st);
int buildin_getmapxy(struct script_state *st);
int buildin_checkcart(struct script_state *st);
int buildin_checkfalcon(struct script_state *st);
int buildin_checkriding(struct script_state *st);
int buildin_checkdragon(struct script_state *st);
int buildin_checkgear(struct script_state *st);
int buildin_checkwolf(struct script_state *st);
int buildin_checksit(struct script_state *st);
int buildin_checkdead(struct script_state *st);
int buildin_checkcasting(struct script_state *st);
int buildin_adoption(struct script_state *st);
int buildin_breakadoption(struct script_state *st);
int buildin_petskillattack(struct script_state *st);
int buildin_petskillsupport(struct script_state *st);
int buildin_changepettype(struct script_state *st);
int buildin_making(struct script_state *st);
int buildin_getpkflag(struct script_state *st);
int buildin_guildgetexp(struct script_state *st);
int buildin_flagname(struct script_state *st);
int buildin_getnpcposition(struct script_state *st);
#ifndef NO_CSVDB_SCRIPT
int buildin_csvgetrows(struct script_state *st);
int buildin_csvgetcols(struct script_state *st);
int buildin_csvread(struct script_state *st);
int buildin_csvreadarray(struct script_state *st);
int buildin_csvfind(struct script_state *st);
int buildin_csvwrite(struct script_state *st);
int buildin_csvwritearray(struct script_state *st);
int buildin_csvreload(struct script_state *st);
int buildin_csvinsert(struct script_state *st);
int buildin_csvdelete(struct script_state *st);
int buildin_csvsort(struct script_state *st);
int buildin_csvflush(struct script_state *st);
#endif
int buildin_sleep(struct script_state *st);
int buildin_sleep2(struct script_state *st);
int buildin_awake(struct script_state *st);
int buildin_getvariableofnpc(struct script_state *st);
int buildin_changeviewsize(struct script_state *st);
int buildin_usediteminfo(struct script_state *st);
int buildin_getitemid(struct script_state *st);
int buildin_getguildmembers(struct script_state *st);
int buildin_npcskillattack(struct script_state *st);
int buildin_npcskillsupport(struct script_state *st);
int buildin_npcskillpos(struct script_state *st);
int buildin_strnpcinfo(struct script_state *st);
int buildin_getpartyleader(struct script_state *st);
int buildin_getstrlen(struct script_state *st);
int buildin_substr(struct script_state *st);
int buildin_strstr(struct script_state *st);
int buildin_distance(struct script_state *st);
int buildin_homundel(struct script_state *st);
int buildin_homunrename(struct script_state *st);
int buildin_homunevolution(struct script_state *st);
int buildin_morphembryo(struct script_state *st);
int buildin_homunmutation(struct script_state *st);
int buildin_recalcstatus(struct script_state *st);
int buildin_sqlquery(struct script_state *st);
int buildin_strescape(struct script_state *st);
int buildin_dropitem(struct script_state *st);
int buildin_dropitem2(struct script_state *st);
int buildin_getexp(struct script_state *st);
int buildin_getiteminfo(struct script_state *st);
int buildin_getonlinepartymember(struct script_state *st);
int buildin_getonlineguildmember(struct script_state *st);
int buildin_makemerc(struct script_state *st);
int buildin_delmerc(struct script_state *st);
int buildin_openbook(struct script_state *st);
int buildin_pushpc(struct script_state *st);
int buildin_setcell(struct script_state *st);
int buildin_areasetcell(struct script_state *st);
int buildin_callguardian(struct script_state *st);
int buildin_getguardianinfo(struct script_state *st);
int buildin_getmobname(struct script_state *st);
int buildin_checkactiveitem(struct script_state *st);
int buildin_showevent(struct script_state *st);
int buildin_musiceffect(struct script_state *st);
int buildin_areamusiceffect(struct script_state *st);
int buildin_getbaseclass(struct script_state *st);
int buildin_setquest(struct script_state *st);
int buildin_chgquest(struct script_state *st);
int buildin_delquest(struct script_state *st);
int buildin_compquest(struct script_state *st);
int buildin_checkquest(struct script_state *st);
int buildin_getquestlimit(struct script_state *st);
int buildin_getquestcount(struct script_state *st);
int buildin_getquestmaxcount(struct script_state *st);
int buildin_openbuyingstore(struct script_state *st);
int buildin_setfont(struct script_state *st);
int buildin_callshop(struct script_state *st);
int buildin_npcshopitem(struct script_state *st);
int buildin_progressbar(struct script_state *st);
int buildin_getmercinfo(struct script_state *st);
int buildin_mercheal(struct script_state *st);
int buildin_mercsc_start(struct script_state *st);
int buildin_mdcreate(struct script_state *st);
int buildin_mddelete(struct script_state *st);
int buildin_mdenter(struct script_state *st);
int buildin_getmdmapname(struct script_state *st);
int buildin_getmdnpcname(struct script_state *st);
int buildin_active_montransform(struct script_state *st);
int buildin_callmonster(struct script_state *st);
int buildin_areacallmonster(struct script_state *st);
int buildin_removemonster(struct script_state *st);
int buildin_mobuseskill(struct script_state *st);
int buildin_mobuseskillpos(struct script_state *st);
int buildin_areamobuseskill(struct script_state *st);
int buildin_getequipcardid(struct script_state *st);
int buildin_setequipcardid(struct script_state *st);
int buildin_setpartyinmap(struct script_state *st);
int buildin_getclassjob(struct script_state *st);
int buildin_unittalk(struct script_state *st);
int buildin_pcblockmove(struct script_state *st);
int buildin_showmessage(struct script_state *st);
int buildin_getmobhp(struct script_state *st);
int buildin_setmobhp(struct script_state *st);
int buildin_sc_onparam(struct script_state *st);
int buildin_showdigit(struct script_state *st);
int buildin_checkre(struct script_state *st);
int buildin_opendressroom(struct script_state *st);
int buildin_hateffect(struct script_state *st);
int buildin_getrandombox(struct script_state *st);
int buildin_getrandommob(struct script_state *st);
int buildin_achievement(struct script_state *st);
int buildin_achievement2(struct script_state *st);
int buildin_dynamicnpc(struct script_state *st);
int buildin_mdopenstate(struct script_state *st);
int buildin_openupgrade(struct script_state *st);
int buildin_npcwalkto(struct script_state *st);
int buildin_npcwalkwait(struct script_state *st);
int buildin_setnpcspeed(struct script_state *st);
int buildin_npcclickable(struct script_state *st);
int buildin_setnpcgroup(struct script_state *st);
int buildin_setunitgroup(struct script_state *st);
int buildin_setnpctitle(struct script_state *st);
int buildin_setunittitle(struct script_state *st);

struct script_function buildin_func[] = {
	{buildin_mes,"mes","s"},
	{buildin_messize,"messize","ii"},
	{buildin_mespos,"mespos","ii"},
	{buildin_mesalign,"mesalign","i"},
	{buildin_next,"next",""},
	{buildin_close,"close",""},
	{buildin_close2,"close2",""},
	{buildin_clear,"clear",""},
	{buildin_menu,"menu","*"},
	{buildin_goto,"goto","l"},
	{buildin_callsub,"callsub","i*"},
	{buildin_callfunc,"callfunc","s*"},
	{buildin_return,"return","*"},
	{buildin_getarg,"getarg","i"},
	{buildin_getargcount,"getargcount",""},
	{buildin_jobchange,"jobchange","i*"},
	{buildin_input,"input","s"},
	{buildin_warp,"warp","sii"},
	{buildin_mapwarp,"mapwarp","ssii"},
	{buildin_areawarp,"areawarp","siiiisii"},
	{buildin_setlook,"setlook","ii"},
	{buildin_getlook,"getlook","i"},
	{buildin_set,"set","ii"},
	{buildin_setarray,"setarray","ii*"},
	{buildin_cleararray,"cleararray","iii"},
	{buildin_copyarray,"copyarray","iii"},
	{buildin_getarraysize,"getarraysize","i"},
	{buildin_deletearray,"deletearray","ii"},
	{buildin_printarray,"printarray","s*"},
	{buildin_getelementofarray,"getelementofarray","ii*"},
	{buildin_getitem,"getitem","ii**"},
	{buildin_getitem2,"getitem2","iiiiiiiii*"},
	{buildin_getoptitem,"getoptitem","iiiiiiiii*"},
	{buildin_itempreview,"itempreview","i"},
	{buildin_delitem,"delitem","ii*"},
	{buildin_delcartitem,"delcartitem","ii*"},
	{buildin_delitem2,"delitem2","ii*"},
	{buildin_delcartitem2,"delcartitem2","ii*"},
	{buildin_cutin,"cutin","si"},
	{buildin_cutincard,"cutincard","i"},
	{buildin_viewpoint,"viewpoint","iiiii"},
	{buildin_heal,"heal","ii"},
	{buildin_itemheal,"itemheal","ii"},
	{buildin_percentheal,"percentheal","ii"},
	{buildin_rand,"rand","i*"},
	{buildin_countitem,"countitem","i"},
	{buildin_countcartitem,"countcartitem","i"},
	{buildin_checkweight,"checkweight","ii"},
	{buildin_checkitemblank,"checkitemblank",""},
	{buildin_readparam,"readparam","i*"},
	{buildin_getcharid,"getcharid","i*"},
	{buildin_getnpcid,"getnpcid","i*"},
	{buildin_getcharname,"getcharname","i"},
	{buildin_getpartyname,"getpartyname","i"},
	{buildin_getpartymember,"getpartymember","i"},
	{buildin_getguildname,"getguildname","i"},
	{buildin_getguildmaster,"getguildmaster","i"},
	{buildin_getguildmasterid,"getguildmasterid","i"},
	{buildin_strcharinfo,"strcharinfo","i"},
	{buildin_getequipid,"getequipid","i"},
	{buildin_getequipname,"getequipname","i"},
	{buildin_getequipisequiped,"getequipisequiped","i"},
	{buildin_getequipisenableref,"getequipisenableref","i"},
	{buildin_getequipisidentify,"getequipisidentify","i"},
	{buildin_getequiprefinerycnt,"getequiprefinerycnt","*"},
	{buildin_getequipweaponlv,"getequipweaponlv","i"},
	{buildin_getequippercentrefinery,"getequippercentrefinery","i"},
	{buildin_delequip,"delequip","*"},
	{buildin_successrefitem,"successrefitem","i"},
	{buildin_failedrefitem,"failedrefitem","i"},
	{buildin_downrefitem,"downrefitem","i*"},
	{buildin_getequippos,"getequippos",""},
	{buildin_statusup,"statusup","i"},
	{buildin_statusup2,"statusup2","ii"},
	{buildin_bonus,"bonus","ii"},
	{buildin_bonus2,"bonus2","iii"},
	{buildin_bonus3,"bonus3","iiii"},
	{buildin_bonus4,"bonus4","iiiii"},
	{buildin_skill,"skill","ii*"},
	{buildin_guildskill,"guildskill","ii*"},
	{buildin_getskilllv,"getskilllv","i"},
	{buildin_getgdskilllv,"getgdskilllv","ii"},
	{buildin_basicskillcheck,"basicskillcheck",""},
	{buildin_getgmlevel,"getgmlevel",""},
	{buildin_end,"end",""},
	{buildin_checkoption,"checkoption","i"},
	{buildin_setoption,"setoption","i"},
	{buildin_setcart,"setcart",""},
	{buildin_setfalcon,"setfalcon",""},
	{buildin_setriding,"setriding",""},
	{buildin_setdragon,"setdragon","*"},
	{buildin_setgear,"setgear",""},
	{buildin_sit,"sit",""},
	{buildin_stand,"stand",""},
	{buildin_savepoint,"savepoint","sii"},
	{buildin_gettimetick,"gettimetick","i"},
	{buildin_gettime,"gettime","i"},
	{buildin_gettimestr,"gettimestr","si"},
	{buildin_openstorage,"openstorage",""},
	{buildin_guildopenstorage,"guildopenstorage",""},
	{buildin_itemskill,"itemskill","iis*"},
	{buildin_produce,"produce","i"},
	{buildin_monster,"monster","siissi*"},
	{buildin_areamonster,"areamonster","siiiissi*"},
	{buildin_killmonster,"killmonster","ss"},
	{buildin_killmonsterall,"killmonsterall","s"},
	{buildin_areakillmonster,"areakillmonster","siiii"},
	{buildin_doevent,"doevent","s"},
	{buildin_donpcevent,"donpcevent","s"},
	{buildin_addtimer,"addtimer","is"},
	{buildin_deltimer,"deltimer","s"},
	{buildin_addtimercount,"addtimercount","si"},
	{buildin_gettimerdiff,"gettimerdiff","s"},
	{buildin_initnpctimer,"initnpctimer","*"},
	{buildin_stopnpctimer,"stopnpctimer","*"},
	{buildin_startnpctimer,"startnpctimer","*"},
	{buildin_setnpctimer,"setnpctimer","*"},
	{buildin_getnpctimer,"getnpctimer","i*"},
	{buildin_announce,"announce","si*****"},
	{buildin_mapannounce,"mapannounce","ssi*****"},
	{buildin_areaannounce,"areaannounce","siiiisi*****"},
	{buildin_getusers,"getusers","i"},
	{buildin_getmapusers,"getmapusers","s"},
	{buildin_getareausers,"getareausers","siiii"},
	{buildin_getareadropitem,"getareadropitem","siiiii"},
	{buildin_enablenpc,"enablenpc","*"},
	{buildin_disablenpc,"disablenpc","*"},
	{buildin_hideoffnpc,"hideoffnpc","*"},
	{buildin_hideonnpc,"hideonnpc","*"},
	{buildin_cloakoffnpc,"cloakoffnpc","*"},
	{buildin_cloakonnpc,"cloakonnpc","*"},
	{buildin_sc_start,"sc_start","iii*"},
	{buildin_sc_start2,"sc_start2","iiii*"},
	{buildin_sc_starte,"sc_starte","iii*"},
	{buildin_sc_start3,"sc_start3","iiiiiii*"},
	{buildin_sc_end,"sc_end","i*"},
	{buildin_sc_ison,"sc_ison","i"},
	{buildin_getscrate,"getscrate","ii*"},
	{buildin_debugmes,"debugmes","s"},
	{buildin_catchpet,"pet","i"},
	{buildin_birthpet,"bpet",""},
	{buildin_resetstatus,"resetstatus","*"},
	{buildin_resetskill,"resetskill","*"},
	{buildin_changebase,"changebase","i*"},
	{buildin_changesex,"changesex",""},
	{buildin_waitingroom,"waitingroom","si*"},
	{buildin_delwaitingroom,"delwaitingroom","*"},
	{buildin_kickwaitingroom,"kickwaitingroom","i"},
	{buildin_kickwaitingroomall,"kickwaitingroomall","*"},
	{buildin_enablewaitingroomevent,"enablewaitingroomevent","*"},
	{buildin_disablewaitingroomevent,"disablewaitingroomevent","*"},
	{buildin_getwaitingroomstate,"getwaitingroomstate","i*"},
	{buildin_warpwaitingpc,"warpwaitingpc","sii*"},
	{buildin_getwaitingpcid,"getwaitingpcid","i*"},
	{buildin_attachrid,"attachrid","i"},
	{buildin_detachrid,"detachrid",""},
	{buildin_isloggedin,"isloggedin","i"},
	{buildin_setmapflag,"setmapflag","si*"},
	{buildin_removemapflag,"removemapflag","si"},
	{buildin_checkmapflag,"checkmapflag","si"},
	{buildin_pvpon,"pvpon","s"},
	{buildin_pvpoff,"pvpoff","s"},
	{buildin_gvgon,"gvgon","s"},
	{buildin_gvgoff,"gvgoff","s"},
	{buildin_emotion,"emotion","i*"},
	{buildin_maprespawnguildid,"maprespawnguildid","sii"},
	{buildin_agitstart,"agitstart",""},
	{buildin_agitend,"agitend",""},
	{buildin_agitcheck,"agitcheck",""},
	{buildin_flagemblem,"flagemblem","i"},
	{buildin_getcastlename,"getcastlename","s*"},
	{buildin_getcastledata,"getcastledata","si*"},
	{buildin_setcastledata,"setcastledata","sii"},
	{buildin_requestguildinfo,"requestguildinfo","i*"},
	{buildin_getequipcardcnt,"getequipcardcnt","i"},
	{buildin_successremovecards,"successremovecards","i*"},
	{buildin_failedremovecards,"failedremovecards","ii*"},
	{buildin_marriage,"marriage","s"},
	{buildin_wedding_effect,"wedding",""},
	{buildin_divorce,"divorce","i"},
	{buildin_getitemname,"getitemname","i"},
	{buildin_makepet,"makepet","i"},
	{buildin_getinventorylist,"getinventorylist",""},
	{buildin_getcartlist,"getcartlist",""},
	{buildin_getskilllist,"getskilllist",""},
	{buildin_clearitem,"clearitem",""},
	{buildin_clearcartitem,"clearcartitem",""},
	{buildin_getrepairableitemcount,"getrepairableitemcount",""},
	{buildin_repairitem,"repairitem",""},
	{buildin_classchange,"classchange","ii"},
	{buildin_setnpcdisplay,"setnpcdisplay","si*"},
	{buildin_misceffect,"misceffect","i*"},
	{buildin_areamisceffect,"areamisceffect","siiiii"},
	{buildin_soundeffect,"soundeffect","si*"},
	{buildin_areasoundeffect,"areasoundeffect","siiiisi*"},
	{buildin_delmisceffect,"delmisceffect","i*"},
	{buildin_gmcommand,"gmcommand","s"},
	{buildin_dispbottom,"dispbottom","s"},
	{buildin_getusersname,"getusersname",""},
	{buildin_recovery,"recovery",""},
	{buildin_getpetinfo,"getpetinfo","i"},
	{buildin_gethomuninfo,"gethomuninfo","i"},
	{buildin_checkequipedcard,"checkequipedcard","i"},
	{buildin_jump_zero,"jump_zero","ii"},
	{buildin_select,"select","*"},
	{buildin_globalmes,"globalmes","s*"},
	{buildin_getmapmobs,"getmapmobs","s*"},
	{buildin_getareamobs,"getareamobs","siiii*"},
	{buildin_getmapmoblist,"getmapmoblist","s*"},
	{buildin_getguildrelation,"getguildrelation","i*"},
	{buildin_unequip,"unequip","*"},
	{buildin_allowuseitem,"allowuseitem","*"},
	{buildin_equippeditem,"equippeditem","i*"},
	{buildin_getmapname,"getmapname","s"},
	{buildin_summon,"summon","si*"},
	{buildin_getmapxy,"getmapxy","siii*"},
	{buildin_checkcart,"checkcart",""},
	{buildin_checkfalcon,"checkfalcon",""},
	{buildin_checkriding,"checkriding",""},
	{buildin_checkdragon,"checkdragon",""},
	{buildin_checkgear,"checkgear",""},
	{buildin_checkwolf,"checkwolf","*"},
	{buildin_checksit,"checksit",""},
	{buildin_checkdead,"checkdead",""},
	{buildin_checkcasting,"checkcasting",""},
	{buildin_adoption,"adoption","s*"},
	{buildin_breakadoption,"breakadoption","*"},
	{buildin_petskillattack,"petskillattack","iiii"},
	{buildin_petskillsupport,"petskillsupport","iiiii"},
	{buildin_changepettype,"changepettype","i"},
	{buildin_making,"making","ii"},
	{buildin_getpkflag,"getpkflag","s"},
	{buildin_guildgetexp,"guildgetexp","i"},
	{buildin_flagname,"flagname","s"},
	{buildin_getnpcposition,"getnpcposition","s"},
	{buildin_homundel,"homundel",""},
	{buildin_homunrename,"homunrename","s*"},
	{buildin_homunevolution,"homunevolution",""},
	{buildin_morphembryo,"morphembryo",""},
	{buildin_homunmutation,"homunmutation","i"},
#ifndef NO_CSVDB_SCRIPT
	{buildin_csvgetrows,"csvgetrows","s"},
	{buildin_csvgetcols,"csvgetcols","si"},
	{buildin_csvread,"csvread","sii"},
	{buildin_csvreadarray,"csvreadarray","sii"},
	{buildin_csvfind,"csvfind","sii"},
	{buildin_csvwrite,"csvwrite","siis"},
	{buildin_csvwritearray,"csvwritearray","sii"},
	{buildin_csvreload,"csvreload","s"},
	{buildin_csvinsert,"csvinsert","si"},
	{buildin_csvdelete,"csvdelete","si"},
	{buildin_csvsort,"csvsort","sii"},
	{buildin_csvflush,"csvflush","s"},
#endif
	{buildin_sleep,"sleep","i"},
	{buildin_sleep2,"sleep2","i"},
	{buildin_awake,"awake","s"},
	{buildin_getvariableofnpc,"getvariableofnpc","is"},
	{buildin_changeviewsize,"changeviewsize","ii"},
	{buildin_usediteminfo,"usediteminfo","i"},
	{buildin_getitemid,"getitemid","s"},
	{buildin_getguildmembers,"getguildmembers","i"},
	{buildin_npcskillattack,"npcskillattack","iii"},
	{buildin_npcskillsupport,"npcskillsupport","ii*"},
	{buildin_npcskillpos,"npcskillpos","iiii"},
	{buildin_strnpcinfo,"strnpcinfo","i"},
	{buildin_getpartyleader,"getpartyleader","i"},
	{buildin_getstrlen,"getstrlen","s"},
	{buildin_substr,"substr","si*"},
	{buildin_strstr,"strstr","ss"},
	{buildin_distance,"distance","i*"},
	{buildin_recalcstatus,"recalcstatus","*"},
	{buildin_sqlquery,"sqlquery","s*"},
	{buildin_strescape,"strescape","s"},
	{buildin_dropitem,"dropitem","siiiii*"},
	{buildin_dropitem2,"dropitem2","siiiiiiiiiiii*"},
	{buildin_getexp,"getexp","ii*"},
	{buildin_getiteminfo,"getiteminfo","si"},
	{buildin_getonlinepartymember,"getonlinepartymember","*"},
	{buildin_getonlineguildmember,"getonlineguildmember","*"},
	{buildin_makemerc,"makemerc","ii"},
	{buildin_delmerc,"delmerc",""},
	{buildin_openbook,"openbook","i*"},
	{buildin_pushpc,"pushpc","ii"},
	{buildin_setcell,"setcell","siii*"},
	{buildin_areasetcell,"areasetcell","siiiii*"},
	{buildin_callguardian,"callguardian","siissi*"},
	{buildin_getguardianinfo,"getguardianinfo","sii"},
	{buildin_getmobname,"getmobname","i"},
	{buildin_checkactiveitem,"checkactiveitem","*"},
	{buildin_showevent,"showevent","i**"},
	{buildin_musiceffect,"musiceffect","s"},
	{buildin_areamusiceffect,"areamusiceffect","siiiis"},
	{buildin_getbaseclass,"getbaseclass","i*"},
	{buildin_setquest,"setquest","i"},
	{buildin_chgquest,"chgquest","ii"},
	{buildin_delquest,"delquest","i"},
	{buildin_compquest,"compquest","i"},
	{buildin_checkquest,"checkquest","i"},
	{buildin_getquestlimit,"getquestlimit","i"},
	{buildin_getquestcount,"getquestcount","i*"},
	{buildin_getquestmaxcount,"getquestmaxcount","i*"},
	{buildin_openbuyingstore,"openbuyingstore","i"},
	{buildin_setfont,"setfont","i"},
	{buildin_callshop,"callshop","s*"},
	{buildin_npcshopitem,"npcshopitem","s*"},
	{buildin_progressbar,"progressbar","i*"},
	{buildin_getmercinfo,"getmercinfo","i"},
	{buildin_mercheal,"mercheal","ii"},
	{buildin_mercsc_start,"mercsc_start","iii"},
	{buildin_mdcreate,"mdcreate","s*"},
	{buildin_mddelete,"mddelete","*"},
	{buildin_mdenter,"mdenter","s"},
	{buildin_mdopenstate,"mdopenstate","s"},
	{buildin_getmdmapname,"getmdmapname","s"},
	{buildin_getmdnpcname,"getmdnpcname","s"},
	{buildin_active_montransform,"active_montransform","i*"},
	{buildin_callmonster,"callmonster","siiss*"},
	{buildin_areacallmonster,"areacallmonster","siiiiss*"},
	{buildin_removemonster,"removemonster","i*"},
	{buildin_mobuseskill,"mobuseskill","iiiiiiii"},
	{buildin_mobuseskillpos,"mobuseskillpos","iiiiiii"},
	{buildin_areamobuseskill,"areamobuseskill","siiiiiiiiiiii"},
	{buildin_getequipcardid,"getequipcardid","ii"},
	{buildin_setequipcardid,"setequipcardid","iii*"},
	{buildin_setpartyinmap,"setpartyinmap","ii"},
	{buildin_getclassjob,"getclassjob","i"},
	{buildin_unittalk,"unittalk","*"},
	{buildin_pcblockmove,"pcblockmove","i"},
	{buildin_showmessage,"showmessage","s*"},
	{buildin_getmobhp,"getmobhp","i"},
	{buildin_setmobhp,"setmobhp","ii"},
	{buildin_sc_onparam,"sc_onparam","ii"},
	{buildin_showdigit,"showdigit","ii"},
	{buildin_checkre,"checkre",""},
	{buildin_opendressroom,"opendressroom","*"},
	{buildin_hateffect,"hateffect","ii"},
	{buildin_getrandombox,"getrandombox","i"},
	{buildin_getrandommob,"getrandommob","i*"},
	{buildin_achievement,"achievement","i"},
	{buildin_achievement2,"achievement2","iii"},
	{buildin_dynamicnpc,"dynamicnpc","ssiiii"},
	{buildin_openupgrade,"openupgrade","i"},
	{buildin_npcwalkto,"npcwalkto","ii*"},
	{buildin_npcwalkwait,"npcwalkwait","*"},
	{buildin_setnpcspeed,"setnpcspeed","i*"},
	{buildin_npcclickable,"npcclickable","i*"},
	{buildin_setnpcgroup,"setnpcgroup","i*"},
	{buildin_setunitgroup,"setunitgroup","ii"},
	{buildin_setnpctitle,"setnpctitle","s*"},
	{buildin_setunittitle,"setunittitle","si"},

	{NULL,NULL,NULL}
};


/*==========================================
 *
 *------------------------------------------
 */
int buildin_goto(struct script_state *st)
{
	if( st->stack->stack_data[st->start+2].type!=C_POS ){
		printf("buildin_goto: not label !\n");
		st->state=END;
		return 0;
	}

	st->pos = conv_num(st,& (st->stack->stack_data[st->start+2]));
	st->state = GOTO;
	return 0;
}

/*==========================================
 * ユーザー定義関数の呼び出し
 *------------------------------------------
 */
int buildin_callfunc(struct script_state *st)
{
	struct script_code *scr, *oldscr;
	char *str=conv_str(st,& (st->stack->stack_data[st->start+2]));

	if( (scr = script_get_userfunc(str)) ){
		int i,j;
		struct linkdb_node **oldval = st->stack->var_function;

		for(i=st->start+3,j=0;i<st->end;i++,j++) {
			push_copy(st->stack,i);
		}

		push_val(st->stack,C_INT,j);				// 引数の数をプッシュ
		push_val(st->stack,C_INT,st->stack->defsp);		// 現在の基準スタックポインタをプッシュ
		push_ptr(st->stack,C_PTR,st->script);		// 現在のスクリプトをプッシュ
		push_ptr(st->stack,C_PTR,st->stack->var_function);	// 現在の関数依存変数をプッシュ
		push_val(st->stack,C_RETINFO,st->pos);			// 現在のスクリプト位置をプッシュ

		oldscr = st->script;
		st->pos=0;
		st->script=scr;
		st->stack->defsp=st->start+5+j;
		st->state=GOTO;
		st->stack->var_function = (struct linkdb_node**)aCalloc(1, sizeof(struct linkdb_node*));

		// ' 変数の引き継ぎ
		for(i = 0; i < j; i++) {
			struct script_data *s = &st->stack->stack_data[st->stack->sp-6-i];
			if( s->type == C_NAME && !s->ref ) {
				char *name = str_buf+str_data[s->u.num&0x00ffffff].str;
				// '@ 変数の引き継ぎ
				if( name[0] == '\'' && name[1] == '@' ) {
					s->ref = oldval;
				} else if( name[0] == '\'' ) {
					s->ref = &oldscr->script_vars;
				}
			}
		}

	}else{
		printf("buildin_callfunc: function not found! [%s]\n",str);
		st->state=END;
	}
	return 0;
}

/*==========================================
 * サブルーティンの呼び出し
 *------------------------------------------
 */
int buildin_callsub(struct script_state *st)
{
	int pos = conv_num(st,& (st->stack->stack_data[st->start+2]));

	if(st->stack->stack_data[st->start+2].type != C_POS) {
		printf("buildin_callsub: not label !\n");
		st->state=END;
	} else {
		int i,j;
		struct linkdb_node **oldval = st->stack->var_function;

		for(i=st->start+3,j=0;i<st->end;i++,j++) {
			push_copy(st->stack,i);
		}

		push_val(st->stack,C_INT,j);				// 引数の数をプッシュ
		push_val(st->stack,C_INT,st->stack->defsp);		// 現在の基準スタックポインタをプッシュ
		push_ptr(st->stack,C_PTR,st->script);		// 現在のスクリプトをプッシュ
		push_ptr(st->stack,C_PTR,st->stack->var_function);	// 現在の関数依存変数をプッシュ
		push_val(st->stack,C_RETINFO,st->pos);			// 現在のスクリプト位置をプッシュ

		st->pos=pos;
		st->stack->defsp=st->start+5+j;
		st->state=GOTO;
		st->stack->var_function = (struct linkdb_node**)aCalloc(1, sizeof(struct linkdb_node*));

		// ' 変数の引き継ぎ
		for(i = 0; i < j; i++) {
			struct script_data *s = &st->stack->stack_data[st->stack->sp-6-i];
			if( s->type == C_NAME && !s->ref ) {
				char *name = str_buf+str_data[s->u.num&0x00ffffff].str;
				// '@ 変数の引き継ぎ
				if( name[0] == '\'' && name[1] == '@' ) {
					s->ref = oldval;
				}
			}
		}
	}
	return 0;
}

/*==========================================
 * 引数の取得
 *------------------------------------------
 */
int buildin_getarg(struct script_state *st)
{
	int num=conv_num(st,& (st->stack->stack_data[st->start+2]));
	int max,stsp;

	if( st->stack->defsp<5 || st->stack->stack_data[st->stack->defsp-1].type!=C_RETINFO ){
		printf("buildin_getarg: without callfunc or callsub!\n");
		st->state=END;
		return 0;
	}
	max=conv_num(st,& (st->stack->stack_data[st->stack->defsp-5]));
	stsp=st->stack->defsp - max - 5;
	if( num >= max ){
		printf("buildin_getarg: arg1(%d) out of range(%d) !\n",num,max);
		st->state=END;
		return 0;
	}
	push_copy(st->stack,stsp+num);
	return 0;
}

/*==========================================
 * 引数の総個数を取得
 *------------------------------------------
 */
int buildin_getargcount(struct script_state *st)
{
	int max;

	if( st->stack->defsp<5 || st->stack->stack_data[st->stack->defsp-1].type!=C_RETINFO ){
		printf("buildin_getargcount: without callfunc or callsub!\n");
		st->state=END;
		return 0;
	}
	max=conv_num(st,& (st->stack->stack_data[st->stack->defsp-5]));

	push_val(st->stack,C_INT,max);
	return 0;
}

/*==========================================
 * サブルーチン/ユーザー定義関数の終了
 *------------------------------------------
 */
int buildin_return(struct script_state *st)
{
	if(st->end>st->start+2){	// 戻り値有り
		struct script_data *sd;

		push_copy(st->stack,st->start+2);
		sd = &st->stack->stack_data[st->stack->sp-1];

		if(sd->type == C_NAME) {
			char *name = str_buf + str_data[sd->u.num&0x00ffffff].str;
			if( name[0] == '\'' ) {
				if( name[1] == '@' ) {
					// '@ 変数を参照渡しにすると危険なので値渡しにする
					get_val(st,sd);
					if(isstr(sd)) {		// 文字列の場合はaStrdupしないといけない
						sd->type  = C_STR;
						sd->u.str = (char *)aStrdup(sd->u.str);
					}
				} else if( !sd->ref ) {
					// ' 変数は参照渡しでも良いが、参照元が設定されていないと
					// 元のスクリプトの値を差してしまうので補正する
					sd->ref = &st->script->script_vars;
				}
			}
		}
	}
	st->state=RETFUNC;
	return 0;
}


/*==========================================
 *
 *------------------------------------------
 */
int buildin_rand(struct script_state *st)
{
	int range;

	if(st->end>st->start+3){
		int min=conv_num(st,& (st->stack->stack_data[st->start+2]));
		int max=conv_num(st,& (st->stack->stack_data[st->start+3]));
		if(max<min){
			int tmp;
			tmp=min;
			min=max;
			max=tmp;
		}
		range=max-min+1;
		push_val(st->stack,C_INT,atn_rand()%range+min);
	} else {
		range=conv_num(st,& (st->stack->stack_data[st->start+2]));
		if(range != 0)
			push_val(st->stack,C_INT,atn_rand()%range);
		else
			push_val(st->stack,C_INT,atn_rand());
	}
	return 0;
}


/*==========================================
 * 変数設定
 *------------------------------------------
 */
int buildin_set(struct script_state *st)
{
	struct map_session_data *sd = NULL;
	int num;
	char *name;
	char prefix, postfix;

	if( st->stack->stack_data[st->start+2].type != C_NAME ) {
		printf("buildin_set: param not name\n");
		return 0;
	}
	num     = st->stack->stack_data[st->start+2].u.num;
	name    = str_buf+str_data[num&0x00ffffff].str;
	prefix  = *name;
	postfix = name[strlen(name)-1];

	if( prefix != '$' && prefix != '\'' )
		sd = script_rid2sd(st);

	if( postfix == '$' ) {
		// 文字列
		char *str = conv_str(st,& (st->stack->stack_data[st->start+3]));
		set_reg(st,sd,num,name,(void*)str,st->stack->stack_data[st->start+2].ref);
	} else {
		// 数値
		int val = conv_num(st,& (st->stack->stack_data[st->start+3]));
		set_reg(st,sd,num,name,INT2PTR(val),st->stack->stack_data[st->start+2].ref);
	}

	return 0;
}

/*==========================================
 * 配列変数設定
 *------------------------------------------
 */
int buildin_setarray(struct script_state *st)
{
	struct map_session_data *sd = NULL;
	int num;
	char *name;
	char prefix, postfix;
	int i,j,max;

	if( st->stack->stack_data[st->start+2].type != C_NAME ) {
		printf("buildin_setarray: param not name\n");
		return 0;
	}
	num     = st->stack->stack_data[st->start+2].u.num;
	name    = str_buf+str_data[num&0x00ffffff].str;
	prefix  = *name;
	postfix = name[strlen(name)-1];

	if( prefix != '$' && prefix != '@' && prefix != '\'' && prefix != '.' ) {
		printf("buildin_setarray: illegal scope !\n");
		return 0;
	}
	if( prefix != '$' && prefix != '\'' && prefix != '.' )
		sd = script_rid2sd(st);

	max = 128 - (num>>24);
	for(j=0,i=st->start+3; i<st->end && j<max; i++,j++){
		void *v;
		if( postfix == '$' )
			v = (void*)conv_str(st,& (st->stack->stack_data[i]));
		else
			v = INT2PTR(conv_num(st,& (st->stack->stack_data[i])));
		set_reg( st, sd, num+(j<<24), name, v, st->stack->stack_data[st->start+2].ref);
	}
	return 0;
}

/*==========================================
 * 配列変数クリア
 *------------------------------------------
 */
int buildin_cleararray(struct script_state *st)
{
	struct map_session_data *sd = NULL;
	int num;
	char *name;
	char prefix, postfix;
	int i, sz;
	void *v;

	if( st->stack->stack_data[st->start+2].type != C_NAME ) {
		printf("buildin_cleararray: param not name\n");
		return 0;
	}
	num     = st->stack->stack_data[st->start+2].u.num;
	name    = str_buf+str_data[num&0x00ffffff].str;
	prefix  = *name;
	postfix = name[strlen(name)-1];

	if( prefix != '$' && prefix != '@' && prefix != '\'' && prefix != '.' ) {
		printf("buildin_cleararray: illegal scope !\n");
		return 0;
	}
	if( prefix != '$' && prefix != '\'' && prefix != '.' )
		sd = script_rid2sd(st);

	sz = conv_num(st,& (st->stack->stack_data[st->start+4]));
	if(sz > 128 - (num>>24))
		sz = 128 - (num>>24);

	if( postfix == '$' )
		v = (void*)conv_str(st,& (st->stack->stack_data[st->start+3]));
	else
		v = INT2PTR(conv_num(st,& (st->stack->stack_data[st->start+3])));

	for(i=0;i<sz;i++)
		set_reg(st,sd,num+(i<<24),name,v,st->stack->stack_data[st->start+2].ref);
	return 0;
}

/*==========================================
 * 配列変数コピー
 *------------------------------------------
 */
int buildin_copyarray(struct script_state *st)
{
	struct map_session_data *sd = NULL;
	int num, num2;
	char *name, *name2;
	char prefix, postfix, prefix2, postfix2;
	int i, sz;

	if( st->stack->stack_data[st->start+2].type != C_NAME ||
	    st->stack->stack_data[st->start+3].type != C_NAME )
	{
		printf("buildin_copyarray: param not name\n");
		return 0;
	}
	num      = st->stack->stack_data[st->start+2].u.num;
	name     = str_buf+str_data[num&0x00ffffff].str;
	prefix   = *name;
	postfix  = name[strlen(name)-1];
	num2     = st->stack->stack_data[st->start+3].u.num;
	name2    = str_buf+str_data[num2&0x00ffffff].str;
	prefix2  = *name2;
	postfix2 = name2[strlen(name2)-1];

	if( prefix != '$' && prefix != '@' && prefix != '\'' && prefix != '.' ) {
		printf("buildin_copyarray: illegal scope !\n");
		return 0;
	}
	if( prefix2 != '$' && prefix2 != '@' && prefix2 != '\'' && prefix2 != '.' ) {
		printf("buildin_copyarray: illegal scope !\n");
		return 0;
	}
	if( postfix != postfix2 && (postfix == '$' || postfix2 == '$') ) {
		printf("buildin_copyarray: type mismatch !\n");
		return 0;
	}
	if( (prefix != '$' && prefix != '\'' && prefix != '.') || (prefix2 != '$' && prefix2 != '\'' && prefix2 != '.') )
		sd = script_rid2sd(st);

	sz = conv_num(st,& (st->stack->stack_data[st->start+4]));
	if(sz > 128 - (num>>24))
		sz = 128 - (num>>24);

	if((num & 0x00FFFFFF) == (num2 & 0x00FFFFFF) && (num & 0xFF000000) > (num2 & 0xFF000000)) {
		// 同じ配列で、num > num2 の場合大きい方からコピーしないといけない
		for(i=sz-1; i>=0; i--)
			set_reg(
				st,sd,num+(i<<24),name,
				get_val2(st,num2+(i<<24),st->stack->stack_data[st->start+3].ref),
				st->stack->stack_data[st->start+2].ref
			);
	} else {
		for(i=0; i<sz; i++) {
			if((num2>>24)+i < 128) {
				set_reg(
					st,sd,num+(i<<24),name,
					get_val2(st,num2+(i<<24),st->stack->stack_data[st->start+3].ref),
					st->stack->stack_data[st->start+2].ref
				);
			} else {	// num2が配列上限を超えたら残りは0で埋める
				set_reg(
					st,sd,num+(i<<24),name,
					(postfix == '$')? "": 0,
					st->stack->stack_data[st->start+2].ref
				);
			}
		}
	}
	return 0;
}

/*==========================================
 * 配列変数のサイズ取得
 *------------------------------------------
 */
int getarraysize(struct script_state *st,int num,char postfix,struct linkdb_node** ref)
{
	int i = num>>24;
	int c = (i == 0)? -1: i;

	for(; i<128; i++) {
		void *v = get_val2(st,(num & 0x00FFFFFF)+(i<<24),ref);
		if( postfix == '$' && *((char*)v) )
			c = i;
		if( postfix != '$' && PTR2INT(v) )
			c = i;
	}
	return c+1;
}

int buildin_getarraysize(struct script_state *st)
{
	int num;
	char *name;
	char prefix, postfix;

	if( st->stack->stack_data[st->start+2].type != C_NAME ) {
		printf("buildin_getarraysize: param not name\n");
		push_val(st->stack,C_INT,0);
		return 0;
	}
	num     = st->stack->stack_data[st->start+2].u.num;
	name    = str_buf+str_data[num&0x00ffffff].str;
	prefix  = *name;
	postfix = name[strlen(name)-1];

	if( prefix != '$' && prefix != '@' && prefix != '\'' && prefix != '.' ) {
		printf("buildin_getarraysize: illegal scope !\n");
		push_val(st->stack,C_INT,0);
		return 0;
	}

	push_val(st->stack,C_INT,getarraysize(st,num,postfix,st->stack->stack_data[st->start+2].ref));
	return 0;
}

/*==========================================
 * 配列変数から要素削除
 *------------------------------------------
 */
int buildin_deletearray(struct script_state *st)
{
	struct map_session_data *sd = NULL;
	int num;
	char *name;
	char prefix, postfix;
	int i,j,count,sz;

	if( st->stack->stack_data[st->start+2].type != C_NAME ) {
		printf("buildin_deletearray: param not name\n");
		return 0;
	}
	num     = st->stack->stack_data[st->start+2].u.num;
	name    = str_buf+str_data[num&0x00ffffff].str;
	prefix  = *name;
	postfix = name[strlen(name)-1];

	if( prefix != '$' && prefix != '@' && prefix != '\'' && prefix != '.' ) {
		printf("buildin_deletearray: illegal scope !\n");
		return 0;
	}
	if( prefix != '$' && prefix != '\'' && prefix != '.' )
		sd = script_rid2sd(st);

	count = conv_num(st,& (st->stack->stack_data[st->start+3]));
	sz = getarraysize(st,num,postfix,st->stack->stack_data[st->start+2].ref)-(num>>24)-count;

	for(i=0;i<sz;i++){
		set_reg(
			st,sd,num+(i<<24),name,
			get_val2(st,num+((i+count)<<24),st->stack->stack_data[st->start+2].ref),
			st->stack->stack_data[st->start+2].ref
		);
	}
	if(count > 128 - (num>>24))
		count = 128 - (num>>24);
	for(j=0;j<count;j++){
		set_reg(st,sd,num+((i+j)<<24),name, (postfix == '$')? "": 0, st->stack->stack_data[st->start+2].ref);
	}
	return 0;
}

/*==========================================
 * 配列を文字列として出力
 *------------------------------------------
 */
int buildin_printarray(struct script_state *st)
{
	int num;
	char *name;
	char prefix, postfix;
	int i, count = 0;
	size_t len = 0;
	char *buf;
	const char *delimiter = ":";
	void *list[128];

	if( st->stack->stack_data[st->start+2].type != C_NAME ) {
		printf("buildin_printarray: param not name\n");
		return 0;
	}
	num     = st->stack->stack_data[st->start+2].u.num;
	name    = str_buf+str_data[num&0x00ffffff].str;
	prefix  = *name;
	postfix = name[strlen(name)-1];

	if( prefix != '$' && prefix != '@' && prefix != '\'' && prefix != '.' ) {
		printf("buildin_printarray: illegal scope !\n");
		return 0;
	}

	if(st->end > st->start+3)
		delimiter = conv_str(st,& (st->stack->stack_data[st->start+3]));

	// getarraysize
	for(i = 0; i < 128 - (num>>24); i++) {
		void *v = get_val2(st, num+(i<<24), st->stack->stack_data[st->start+2].ref);

		list[i] = v;
		if( postfix == '$' && *(char*)v ) {
			len += strlen((char*)v);
			count = i + 1;
		}
		if( postfix != '$' && PTR2INT(v) ) {
			len += 16;
			count = i + 1;
		}
	}

	if(count > 0) {
		len += (count - 1) * strlen(delimiter);
	}
	buf = (char *)aCalloc(len + 1, sizeof(char));

	for(i = 0; i < count; i++) {
		if(i > 0) {
			strcat(buf, delimiter);
		}
		if( postfix == '$' ) {
			strcat(buf, (char*)list[i]);
		} else {
			char val[16];
			sprintf(val, "%d", PTR2INT(list[i]));
			strcat(buf, val);
		}
	}

	push_str(st->stack, C_STR, buf);
	return 0;
}

/*==========================================
 * 指定要素を表す値(キー)を取得する
 *------------------------------------------
 */
int buildin_getelementofarray(struct script_state *st)
{
	int i,j=0,count=0;
	int list[128];

	if( st->stack->stack_data[st->start+2].type != C_NAME ) {
		printf("buildin_getelementofarray: (operator[]) param1 not name !\n");
		push_val(st->stack,C_INT,0);
		return 0;
	}

	for(i=st->start+3; i<st->end && count < 128; i++) {
		j = conv_num(st,& (st->stack->stack_data[i]));
		if(j < 0 || j >= 128) {
			printf("buildin_getelementofarray: (operator[]) param illegal number %d\n",j);
			push_val(st->stack,C_INT,0);
			return 0;
		}
		if(j == 0 && count == 0)	// @hoge[0][1] は @hoge[1] として登録するための処理
			continue;

		if(i < st->end-1)
			list[count++] = j;
	}

	if(count == 0) {
		push_val2(st->stack,C_NAME,
			(j<<24) | (st->stack->stack_data[st->start+2].u.num&0x00ffffff),
			st->stack->stack_data[st->start+2].ref);
	} else {
		int num      = st->stack->stack_data[st->start+2].u.num;
		char *name   = str_buf+str_data[num&0x00ffffff].str;
		size_t len   = strlen(name);
		char postfix = name[len-1];
		char *var    = (char *)aCalloc(1+len+count*5, sizeof(char));	// 1つ当たり最大で [xxx] の5文字
		char *p;

		// postfixと[]を削った変数名そのものにする
		strcpy(var,name);
		if(postfix == '$')
			var[len-1] = 0;
		if((p = strchr(var,'[')) != NULL)
			*p = 0;

		p = var + strlen(var);
		for(i=0; i<count; i++) {
			p += sprintf(p,"[%d]",list[i]);
		}
		if(postfix == '$')
			strcat(var,"$");

		push_val2(st->stack,C_NAME,(j<<24) | add_str(var),st->stack->stack_data[st->start+2].ref);
		aFree(var);
	}
	return 0;
}


/*==========================================
 * GetTimeTick(0: System Tick, 1: Time Second Tick)
 *------------------------------------------
 */
int buildin_gettimetick(struct script_state *st)	/* Asgard Version */
{
	int type;

	type=conv_num(st,& (st->stack->stack_data[st->start+2]));

	switch(type){
	case 0:
		// System Ticks
		push_val(st->stack,C_INT,gettick());
		break;
	case 1:
		// Second Ticks: 0-86399, 00:00:00-23:59:59
		{
			time_t timer;
			struct tm *t;
			time(&timer);
			t=localtime(&timer);
			push_val(st->stack,C_INT,((t->tm_hour)*3600+(t->tm_min)*60+t->tm_sec));
		}
		break;
	case 2:
		// Get the number of seconds elapsed since 00:00 hours, Jan 1, 1970 UTC from the system clock
		push_val(st->stack,C_INT,(int)time(NULL));
		break;
	default:
		push_val(st->stack,C_INT,0);
		break;
	}
	return 0;
}

/*==========================================
 * GetTime(Type);
 * 1: Sec	 2: Min	 3: Hour
 * 4: WeekDay	 5: MonthDay	 6: Month
 * 7: Year
 *------------------------------------------
 */
int buildin_gettime(struct script_state *st)	/* Asgard Version */
{
	int type;
	time_t timer;
	struct tm *t;

	type=conv_num(st,& (st->stack->stack_data[st->start+2]));

	time(&timer);
	t=localtime(&timer);

	switch(type){
	case 1:	// Sec(0~59)
		push_val(st->stack,C_INT,t->tm_sec);
		break;
	case 2:	// Min(0~59)
		push_val(st->stack,C_INT,t->tm_min);
		break;
	case 3:	// Hour(0~23)
		push_val(st->stack,C_INT,t->tm_hour);
		break;
	case 4:	// WeekDay(0~6)
		push_val(st->stack,C_INT,t->tm_wday);
		break;
	case 5:	// MonthDay(01~31)
		push_val(st->stack,C_INT,t->tm_mday);
		break;
	case 6:	// Month(01~12)
		push_val(st->stack,C_INT,t->tm_mon+1);
		break;
	case 7:	// Year(20xx)
		push_val(st->stack,C_INT,t->tm_year+1900);
		break;
	default:
		push_val(st->stack,C_INT,-1);
		break;
	}
	return 0;
}

/*==========================================
 * GetTimeStr("TimeFMT", Length);
 *------------------------------------------
 */
int buildin_gettimestr(struct script_state *st)
{
	char *tmpstr, *fmtstr;
	int maxlen;
	time_t now = time(NULL);

	fmtstr = conv_str(st,& (st->stack->stack_data[st->start+2]));
	maxlen = conv_num(st,& (st->stack->stack_data[st->start+3]));

	tmpstr = (char *)aCalloc(maxlen+1,sizeof(char));
	if( !strftime(tmpstr,maxlen+1,fmtstr,localtime(&now)) ) {
		printf("buildin_gettimestr: maxlen is too short!!\n");
	}
	tmpstr[maxlen] = '\0';

	push_str(st->stack,C_STR,tmpstr);
	return 0;
}

/*==========================================
 * カプラ倉庫を開く
 *------------------------------------------
 */
int buildin_openstorage(struct script_state *st)
{
	storage_storageopen(script_rid2sd(st));
	return 0;
}


/*==========================================
 * 存在チェック
 *------------------------------------------
 */
int buildin_isloggedin(struct script_state *st)
{
	int id = conv_num(st,& (st->stack->stack_data[st->start+2]));

	push_val(st->stack,C_INT,(map_id2sd(id) ? 1: 0));
	return 0;
}


/*==========================================
 * PCのスキル情報読み取り
 *------------------------------------------
 */
int buildin_getskilllist(struct script_state *st)
{
	struct map_session_data *sd=script_rid2sd(st);
	int i,j=0,k=0;

	if(!sd)
		return 0;
	for(i=0;i<MAX_PCSKILL;i++){
		if(sd->status.skill[i].id <= 0 || sd->status.skill[i].lv <= 0)
			continue;
		if(j >= 128) {
			j=0;
			k++;
		}
		if(k == 0) {
			pc_setreg(sd,add_str("@skilllist_id")+(j<<24),sd->status.skill[i].id);
			pc_setreg(sd,add_str("@skilllist_lv")+(j<<24),sd->status.skill[i].lv);
			pc_setreg(sd,add_str("@skilllist_flag")+(j<<24),sd->status.skill[i].flag);
		} else {
			char buf[32];
			sprintf(buf,"@skilllist_id[%d]",k);
			pc_setreg(sd,add_str(buf)+(j<<24),sd->status.skill[i].id);
			sprintf(buf,"@skilllist_lv[%d]",k);
			pc_setreg(sd,add_str(buf)+(j<<24),sd->status.skill[i].lv);
			sprintf(buf,"@skilllist_flag[%d]",k);
			pc_setreg(sd,add_str(buf)+(j<<24),sd->status.skill[i].flag);
		}
		j++;
	}
	pc_setreg(sd,add_str("@skilllist_count"),k*128+j);
	return 0;
}


/*==========================================
 * gmcommand
 * suggested on the forums...
 *------------------------------------------
 */
int buildin_gmcommand(struct script_state *st)
{
	char *str;

	str = conv_str(st,& (st->stack->stack_data[st->start+2]));

	if(st->rid) {
		struct map_session_data *sd = map_id2sd(st->rid);
		if(sd) {
			is_atcommand_sub(sd->fd, sd, str, 99);
			return 0;
		}
	}
	if(st->oid) {
		// 人が居ないイベント系NPCで使った場合のためのダミーmap_session_data
		struct map_session_data dummy_sd;
		struct block_list *bl = map_id2bl(st->oid);

		if(bl) {
			memset(&dummy_sd, 0, sizeof(struct map_session_data));
			memcpy(&dummy_sd.bl, bl, sizeof(struct block_list));
			dummy_sd.fd = 0;
			dummy_sd.bl.prev = NULL;
			dummy_sd.bl.next = NULL;
			if(bl->type == BL_NPC) {
				char *p;
				strncpy(dummy_sd.status.name, ((struct npc_data *)bl)->name, 24);
				if((p = strchr(dummy_sd.status.name,'#')) != NULL)
					*p = 0;
			} else {
				strncpy(dummy_sd.status.name, "dummy", 24);
			}
			is_atcommand_sub(dummy_sd.fd, &dummy_sd, str, 99);
			return 0;
		}
	}

	return 0;
}


/*==========================================
 *
 *------------------------------------------
 */
int buildin_jump_zero(struct script_state *st)
{
	int sel = conv_num(st,& (st->stack->stack_data[st->start+2]));

	if(!sel) {
		if(st->stack->stack_data[st->start+3].type != C_POS) {
			printf("buildin_jump_zero: not label !\n");
			st->state = END;
			return 0;
		}
		st->pos = conv_num(st,& (st->stack->stack_data[st->start+3]));
		st->state = GOTO;
	}
	return 0;
}


/*==========================================
 * 指定キャラの居るマップ名取得
 *------------------------------------------
 */
int buildin_getmapname(struct script_state *st)
{
	struct map_session_data *sd;
	char *char_name = conv_str(st,& (st->stack->stack_data[st->start+2]));

	if( strlen(char_name) >= 4 )
		sd = map_nick2sd(char_name);
	else
		sd = script_rid2sd(st);

	if(sd)
		push_str(st->stack,C_STR,(unsigned char *)aStrdup(sd->mapname));
	else
		push_str(st->stack,C_CONSTSTR,"");

	return 0;
}


/*==========================================
 * 指定オブジェクトの位置を取得
 *------------------------------------------
 */
int buildin_getmapxy(struct script_state *st)
{
	struct map_session_data *sd = NULL;
	struct npc_data         *nd = NULL;
	struct mob_data         *md = NULL;
	struct pet_data         *pd = NULL;
	struct homun_data       *hd = NULL;
	int num;
	char *name;
	char prefix, postfix;
	int x,y,type;
	char mapname[24];
	void *v;

	if( st->stack->stack_data[st->start+2].type != C_NAME ||
	    st->stack->stack_data[st->start+3].type != C_NAME ||
	    st->stack->stack_data[st->start+4].type != C_NAME )
	{
		printf("buildin_getmapxy: param not name\n");
		push_val(st->stack,C_INT,-1);
		return 0;
	}

	type=conv_num(st,& (st->stack->stack_data[st->start+5]));

	memset(mapname, 0, sizeof(mapname));
	switch (type){
		case 0:		// Get Character Position
			if( st->end>st->start+6 )
				sd=map_nick2sd(conv_str(st,& (st->stack->stack_data[st->start+6])));
			else
				sd=script_rid2sd(st);

			if ( sd==NULL ) {	// wrong char name or char offline
				push_val(st->stack,C_INT,-1);
				return 0;
			}
			x=sd->bl.x;
			y=sd->bl.y;
			memcpy(mapname,sd->mapname,24);
			break;
		case 1:		// Get NPC Position
			if( st->end > st->start+6 )
				nd = npc_name2id(conv_str(st,& (st->stack->stack_data[st->start+6])));
			else
				nd = map_id2nd(st->oid);
			if ( nd==NULL ) {	// wrong npc name
				push_val(st->stack,C_INT,-1);
				return 0;
			}
			x=nd->bl.x;
			y=nd->bl.y;
			if(nd->bl.m == -1)
				mapname[0] = '-';	// マップに配置されないNPC
			else
				memcpy(mapname,map[nd->bl.m].name,24);
			break;
		case 2:		// Get Pet Position
			if( st->end>st->start+6 )
				sd=map_nick2sd(conv_str(st,& (st->stack->stack_data[st->start+6])));
			else
				sd=script_rid2sd(st);
			if ( sd==NULL ) {	// wrong char name or char offline
				push_val(st->stack,C_INT,-1);
				return 0;
			}
			pd=sd->pd;
			if ( pd==NULL ){	// pet data not found
				push_val(st->stack,C_INT,-1);
				return 0;
			}
			x=pd->bl.x;
			y=pd->bl.y;
			memcpy(mapname,map[pd->bl.m].name,24);
			break;
		case 3:		// Get Mob Position
			if( st->end > st->start+6 )
				md = map_id2md(conv_num(st,& (st->stack->stack_data[st->start+6])));
			if( md==NULL || md->bl.prev == NULL ) {	// wrong mob id
				push_val(st->stack,C_INT,-1);
				return 0;
			}
			x=md->bl.x;
			y=md->bl.y;
			memcpy(mapname,map[md->bl.m].name,24);
			break;
		case 4:		// Get Homun Position
			if( st->end>st->start+6 )
				sd=map_nick2sd(conv_str(st,& (st->stack->stack_data[st->start+6])));
			else
				sd=script_rid2sd(st);
			if ( sd==NULL ) {	// wrong char name or char offline
				push_val(st->stack,C_INT,-1);
				return 0;
			}
			hd=sd->hd;
			if ( hd==NULL ){	// homun data not found
				push_val(st->stack,C_INT,-1);
				return 0;
			}
			x=hd->bl.x;
			y=hd->bl.y;
			memcpy(mapname,map[hd->bl.m].name,24);
			break;
		default:	// Wrong type parameter
			push_val(st->stack,C_INT,-1);
			return 0;
	}

	// Set MapName$
	num     = st->stack->stack_data[st->start+2].u.num;
	name    = str_buf+str_data[num&0x00ffffff].str;
	prefix  = *name;
	postfix = name[strlen(name)-1];

	sd = (prefix != '$' && prefix != '\'')? script_rid2sd(st): NULL;
	if(postfix == '$') {
		v = (void*)mapname;
	} else {
		v = INT2PTR(atoi(mapname));
	}
	set_reg(st,sd,num,name,v,st->stack->stack_data[st->start+2].ref);

	// Set MapX
	num     = st->stack->stack_data[st->start+3].u.num;
	name    = str_buf+str_data[num&0x00ffffff].str;
	prefix  = *name;
	postfix = name[strlen(name)-1];

	sd = (prefix != '$' && prefix != '\'')? script_rid2sd(st): NULL;
	if(postfix == '$') {
		char str[16];
		sprintf(str, "%d", x);
		v = (void*)str;
	} else {
		v = INT2PTR(x);
	}
	set_reg(st,sd,num,name,v,st->stack->stack_data[st->start+3].ref);

	// Set MapY
	num     = st->stack->stack_data[st->start+4].u.num;
	name    = str_buf+str_data[num&0x00ffffff].str;
	prefix  = *name;
	postfix = name[strlen(name)-1];

	sd = (prefix != '$' && prefix != '\'')? script_rid2sd(st): NULL;
	if(postfix == '$') {
		char str[16];
		sprintf(str, "%d", y);
		v = (void*)str;
	} else {
		v = INT2PTR(y);
	}
	set_reg(st,sd,num,name,v,st->stack->stack_data[st->start+4].ref);

	// Return Success value
	push_val(st->stack,C_INT,0);
	return 0;
}


/*==========================================
 * 料理用
 *------------------------------------------
 */
int buildin_making(struct script_state *st)
{
	struct map_session_data *sd;
	int makeid=conv_num(st,& (st->stack->stack_data[st->start+2]));

	sd = script_rid2sd(st);
	if(sd && sd->skill_menu.id == 0){
		int rate = conv_num(st,& (st->stack->stack_data[st->start+3]));
		clif_making_list(sd,makeid,1,rate,1);
	}
	return 0;
}

/*==========================================
 * 指定マップのpvp,gvgフラグを調べる
 *------------------------------------------
 */
int buildin_getpkflag(struct script_state *st)
{
	char *str;
	int m,count=0;

	str = conv_str(st,& (st->stack->stack_data[st->start+2]));

	m = script_mapname2mapid(st,str);
	if(m < 0) {
		push_val(st->stack,C_INT,-1);
		return 0;
	}

	if(map[m].flag.pvp)
		count += 1;
	if(map[m].flag.gvg)
		count += 2;

	push_val(st->stack,C_INT,count);
	return 0;
}


/*==========================================
 * 見た目サイズの変更
 * type1=PC type2=PET type3=HOM type4=NPC
 * 小 size=-1 大 size=1
 *------------------------------------------
 */
int buildin_changeviewsize(struct script_state *st)
{
	struct block_list *bl = NULL;
	struct map_session_data *sd;
	int type=conv_num(st,& (st->stack->stack_data[st->start+2]));
	int size=conv_num(st,& (st->stack->stack_data[st->start+3]));

	sd = map_id2sd(st->rid);
	if(sd == NULL && type != 4)
		return 1;

	size = (size<0)? -1: (size>0)? 1: 0;

	switch (type) {
		case 1:
			bl = &sd->bl;
			break;
		case 2:
			if(sd->pd)
				bl = &sd->pd->bl;
			break;
		case 3:
			if(sd->hd)
				bl = &sd->hd->bl;
			break;
		case 4:
			bl = map_id2bl(st->oid);
			break;
		default:
			break;
	}
	if(bl)
		unit_changeviewsize(bl,size);

	return 0;
}


/*==========================================
 * 文字列長を返す
 *------------------------------------------
 */
int buildin_getstrlen(struct script_state *st)
{
	char *str = conv_str(st,& (st->stack->stack_data[st->start+2]));

	push_val(st->stack,C_INT,(int)strlen(str));

	return 0;
}

/*==========================================
 * 文字列の任意の部分を取得する
 *------------------------------------------
 */
int buildin_substr(struct script_state *st)
{
	char *str;
	int len, offset, count;

	str    = conv_str(st,& (st->stack->stack_data[st->start+2]));
	offset = conv_num(st,& (st->stack->stack_data[st->start+3]));

	len = (int)strlen(str);
	if(offset < 0)		// 開始位置が負なので末尾から位置を計算
		offset += len;
	if(offset < 0 || offset >= len) {
		push_str(st->stack,C_CONSTSTR,"");
		return 0;
	}

	if(st->end > st->start+4) {
		count = conv_num(st,& (st->stack->stack_data[st->start+4]));
		if(count > 0 && offset + count > len)
			count = len - offset;		// 文字列長を超えるので補正
		else if(count < 0)
			count = len - offset + count;	// 個数が負なので末尾から個数分削る
	} else {
		count = len - offset;			// 引数省略時は最後まで
	}

	if(count > 0) {
		char *buf = (char *)aCalloc(count+1, sizeof(char));
		memcpy(buf, str+offset, count);
		push_str(st->stack,C_STR,buf);
	} else {
		push_str(st->stack,C_CONSTSTR,"");
	}
	return 0;
}

/*==========================================
 * 文字列中に指定文字が含まれているかどうか
 *------------------------------------------
 */
int buildin_strstr(struct script_state *st)
{
	const char *str;
	const char *cmpstr;
	int len, offset = 0;
	int pos = 0;

	str    = conv_str(st,& (st->stack->stack_data[st->start+2]));
	cmpstr = conv_str(st,& (st->stack->stack_data[st->start+3]));

	len = (int)strlen(str);

	do {
		if(*str != *cmpstr && offset) {
			cmpstr -= offset;
			pos += offset;
			offset = 0;
		}

		if(*str == *cmpstr) {
			cmpstr++;
			if(*cmpstr == 0)
				break;
			offset++;
		}
		else {
			pos++;
		}
	} while(*str++);

	if(pos < len)
		push_val(st->stack,C_INT,1);
	else
		push_val(st->stack,C_INT,0);

	return 0;
}

/*==========================================
 * PCとNPC間の距離を返す
 *------------------------------------------
 */
int buildin_distance(struct script_state *st)
{
	struct map_session_data *sd;
	struct npc_data *nd;

	sd = map_id2sd(conv_num(st,& (st->stack->stack_data[st->start+2])));
	if(st->end > st->start+3)
		nd = npc_name2id(conv_str(st,& (st->stack->stack_data[st->start+3])));
	else
		nd = map_id2nd(st->oid);

	if(sd && nd && sd->bl.m == nd->bl.m)
		push_val(st->stack,C_INT,unit_distance(&sd->bl,&nd->bl));
	else
		push_val(st->stack,C_INT,-1);
	return 0;
}


/*==========================================
 * SQLクエリ発行
 *------------------------------------------
 */
int buildin_sqlquery(struct script_state *st)
{
#ifndef TXT_ONLY
	int count = -1;
	char *query;
	struct sqldbs_handle *handle = &mysql_handle_script;

	query = conv_str(st,& (st->stack->stack_data[st->start+2]));

	// SQLクエリ利用不可ならエラー
	if(!script_config.sql_script_enable) {
		push_val(st->stack,C_INT,-1);
		return 0;
	}
	if(sqldbs_simplequery(handle, query) == false) {
		push_val(st->stack,C_INT,-1);
		return 0;
	}

	if(sqldbs_has_result(handle) == false) {
		// SELECT以外はここで完了
		count = sqldbs_affected_rows(&mysql_handle_script);
		push_val(st->stack,C_INT,count);
		return 0;
	}

	do {
		int num, len, elem, max;
		char *name, *var, *p;
		char prefix, postfix;
		struct map_session_data *sd = NULL;
		char **sql_row;

		if(st->end <= st->start+3 || st->stack->stack_data[st->start+3].type != C_NAME) {
			printf("buildin_sqlquery: param not name\n");
			break;
		}
		num     = st->stack->stack_data[st->start+3].u.num;
		name    = str_buf+str_data[num&0x00ffffff].str;
		prefix  = *name;
		postfix = name[strlen(name)-1];

		if( prefix != '$' && prefix != '@' && prefix != '\'' ) {
			printf("buildin_sqlquery: illegal scope !\n");
			break;
		}
		if( prefix != '$' && prefix != '\'' ) {
			sd = script_rid2sd(st);
			if(sd == NULL)
				break;
		}

		var = (char *)aCalloc(strlen(name) + 6, sizeof(char));	// [xxx] + \0 = 6文字
		strcpy(var, name);

		if((p = strrchr(var,'[')) != NULL) {
			elem = atoi(p+1);	// 配列の二次元目の要素を取得
			len  = (int)(p - var);
		} else {
			elem = 0;
			len = (int)strlen(var);
			if(postfix == '$')
				len--;
		}

		max = sqldbs_num_fields(handle);
		if(max + (num >> 24) > 128) {
			max = 128 - (num>>24);
		}

		for(count = 0; elem < 128 && (sql_row = sqldbs_fetch(handle)); count++) {
			int i, tmp_num;

			if(count > 0) {	// 結果セットが複数行あるので変数名を合成する
				sprintf(var + len, "[%d]%s", elem, (postfix == '$')? "$": "");
				tmp_num = add_str(var) + (num&0xff000000);
			} else {
				tmp_num = num;
			}
			for(i = 0; i < max; i++) {
				void *v = (postfix == '$')? sql_row[i]: INT2PTR(atoi(sql_row[i]));
				set_reg(st, sd, tmp_num + (i<<24), var, v, st->stack->stack_data[st->start+3].ref);
			}
			elem++;
		}
		aFree(var);
	} while(0);

	sqldbs_free_result(handle);
	push_val(st->stack,C_INT,count);
#else
	// TXTは何もしない
	push_val(st->stack,C_INT,-1);
#endif
	return 0;
}

/*==========================================
 * SQL用の文字列エスケープ
 *------------------------------------------
 */
int buildin_strescape(struct script_state *st)
{
	char *str = conv_str(st,& (st->stack->stack_data[st->start+2]));

#ifndef TXT_ONLY
	char *buf = (char *)aCalloc(strlen(str)*2+1,sizeof(char));

	strecpy_(&mysql_handle_script,buf,str);
	push_str(st->stack,C_STR,buf);
#else
	// TXTは何もしない
	push_str(st->stack,C_STR,(unsigned char *)aStrdup(str));
#endif
	return 0;
}


/*==========================================
 * 経験値取得
 *------------------------------------------
 */
int buildin_getexp(struct script_state *st)
{
	int base, job, quest = 1;
	struct map_session_data *sd = script_rid2sd(st);

	nullpo_retr(0, sd);

	base = conv_num(st,& (st->stack->stack_data[st->start+2]));
	job  = conv_num(st,& (st->stack->stack_data[st->start+3]));
	if(st->end > st->start+4)
		quest = conv_num(st,& (st->stack->stack_data[st->start+4]));

	if(base < 0 || job < 0)
		return 0;
	pc_gainexp(sd,NULL,base,job,quest);

	return 0;
}


/*==========================================
 * 読書ウィンドウの表示
 *------------------------------------------
 */
int buildin_openbook(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int nameid, page = 1;

	nullpo_retr(0, sd);

	nameid = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if(st->end>st->start+3)
		page = conv_num(st,& (st->stack->stack_data[st->start+3]));

	clif_openbook(sd,nameid,page);

	return 0;
}

/*==========================================
 * ノックバック
 *------------------------------------------
 */
int buildin_pushpc(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	struct block_list *bl = map_id2bl(st->oid);
	int dir, count;

	nullpo_retr(0, sd);

	if(bl == NULL || bl->type != BL_NPC)
		bl = &sd->bl;

	dir = conv_num(st,& (st->stack->stack_data[st->start+2]));
	count = conv_num(st,& (st->stack->stack_data[st->start+3]));

	skill_blown(bl,&sd->bl,count|(dir<<20)|SAB_NODAMAGE|SAB_NOPATHSTOP);

	return 0;
}

/*==========================================
 * 指定セルのタイプを変更
 *------------------------------------------
 */
int buildin_setcell(struct script_state *st)
{
	int m,x,y,type;
	int area = 1;
	char *str;

	str  = conv_str(st,& (st->stack->stack_data[st->start+2]));
	x    = conv_num(st,& (st->stack->stack_data[st->start+3]));
	y    = conv_num(st,& (st->stack->stack_data[st->start+4]));
	type = conv_num(st,& (st->stack->stack_data[st->start+5]));
	if(st->end>st->start+6)
		area = conv_num(st,& (st->stack->stack_data[st->start+6]));

	m = script_mapname2mapid(st,str);
	if(m < 0) {
		return 0;
	}
	map_setcell(m,x,y,type);
	clif_changemapcell(m,x,y,type,area);

	return 0;
}

/*==========================================
 * 指定範囲セルのタイプを変更
 *------------------------------------------
 */
int buildin_areasetcell(struct script_state *st)
{
	int m,x,y,x0,y0,x1,y1,type;
	int area = 1;
	char *str;

	str  = conv_str(st,& (st->stack->stack_data[st->start+2]));
	x0   = conv_num(st,& (st->stack->stack_data[st->start+3]));
	y0   = conv_num(st,& (st->stack->stack_data[st->start+4]));
	x1   = conv_num(st,& (st->stack->stack_data[st->start+5]));
	y1   = conv_num(st,& (st->stack->stack_data[st->start+6]));
	type = conv_num(st,& (st->stack->stack_data[st->start+7]));
	if(st->end>st->start+8)
		area = conv_num(st,& (st->stack->stack_data[st->start+8]));

	m = script_mapname2mapid(st,str);
	if(m < 0) {
		return 0;
	}

	for(y = y0; y <= y1; y++) {
		for(x = x0; x <= x1; x++) {
			map_setcell(m,x,y,type);
			clif_changemapcell(m,x,y,type,area);
		}
	}

	return 0;
}


/*==========================================
 * 前職業Class取得
 *------------------------------------------
 */
int buildin_getbaseclass(struct script_state *st)
{
	int class_, type = 0;

	class_ = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if(st->end>st->start+3)
		type = conv_num(st,& (st->stack->stack_data[st->start+3]));

	class_ = pc_get_base_class(class_, type);
	push_val(st->stack,C_INT,class_);

	return 0;
}


/*==========================================
 * 購買露店ウインドウオープン
 *------------------------------------------
 */
int buildin_openbuyingstore(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int count;

	nullpo_retr(0, sd);

	count = conv_num(st,& (st->stack->stack_data[st->start+2]));

	buyingstore_openstorewindow(sd, count);

	return 0;
}

/*==========================================
 * フォントタイプのセット
 *------------------------------------------
 */
int buildin_setfont(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int type = conv_num(st,& (st->stack->stack_data[st->start+2]));

	nullpo_retr(0, sd);

	if(sd->status.font == type)
		sd->status.font = 0;
	else
		sd->status.font = type;

	clif_setfont(sd);

	return 0;
}


/*==========================================
 * メモリアルダンジョン作成
 *------------------------------------------
 */
int buildin_mdcreate(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	char *memorial_name;
	int party_id, ret;

	nullpo_retr(0, sd);

	memorial_name = conv_str(st,& (st->stack->stack_data[st->start+2]));

	if(st->end>st->start+3)
		party_id = conv_num(st,&(st->stack->stack_data[st->start+3]));
	else
		party_id = sd->status.party_id;

	ret = memorial_create(memorial_name, party_id);
	switch(ret) {
		case MDCREATE_EXISTS:		// 既に生成済み
			clif_msgstringtable2(sd, 0x52a, memorial_name);	// メモリアルダンジョン「%s」の予約が重複生成要請により失敗しました。
			break;
		case MDCREATE_PERMISSION:	// 権限がない
			clif_msgstringtable2(sd, 0x529, memorial_name);	// メモリアルダンジョン「%s」の予約が権限問題により失敗しました。
			break;
		case MDCREATE_RESERVED:		// 既に予約済み
			clif_msgstringtable2(sd, 0x528, memorial_name);	// メモリアルダンジョン「%s」の予約が予約重複により失敗しました。
			break;
		case MDCREATE_ERROR:		// その他エラー
			clif_msgstringtable2(sd, 0x527, memorial_name);	// メモリアルダンジョン「%s」の予約に失敗しました。
			break;
	}

	return 0;
}

/*==========================================
 * メモリアルダンジョン削除
 *------------------------------------------
 */
int buildin_mddelete(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int party_id = 0;

	if(st->end>st->start+2)
		party_id = conv_num(st,&(st->stack->stack_data[st->start+2]));
	else if(sd)
		party_id = sd->status.party_id;

	if(party_id > 0) {
		struct party *pt = party_search(party_id);
		if(pt)
			memorial_delete(pt->memorial_id);
	}

	return 0;
}

/*==========================================
 * メモリアルダンジョン入場
 *------------------------------------------
 */
int buildin_mdenter(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int ret = MDENTER_ERROR;
	char *name = conv_str(st,& (st->stack->stack_data[st->start+2]));

	if(sd) {
		ret = memorial_enter(sd, name);
	}

	push_val(st->stack,C_INT,ret);

	return 0;
}

/*==========================================
 * メモリアルダンジョン状態
 *------------------------------------------
 */
int buildin_mdopenstate(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int ret = -1;
	char *name = conv_str(st,& (st->stack->stack_data[st->start+2]));

	if(sd) {
		ret = memorial_openstate(sd, name);
	}

	push_val(st->stack,C_INT,ret);

	return 0;
}

/*==========================================
 * メモリアルダンジョンMAP名取得
 *------------------------------------------
 */
int buildin_getmdmapname(struct script_state *st)
{
	char *str = conv_str(st,& (st->stack->stack_data[st->start+2]));
	int id = script_getmemorialid(st);
	int m = memorial_mapname2mapid(str, id);

	if(m < 0)
		push_str(st->stack,C_CONSTSTR,"");
	else
		push_str(st->stack,C_STR,(unsigned char *)aStrdup(map[m].name));

	return 0;
}


/*==========================================
 * ClassからJob変換
 *------------------------------------------
 */
int buildin_getclassjob(struct script_state *st)
{
	int class_, job = 0;

	class_ = conv_num(st,& (st->stack->stack_data[st->start+2]));

	job = pc_calc_job_class(class_);

	push_val(st->stack,C_INT,job);

	return 0;
}

/*==========================================
 * 発言表示
 *------------------------------------------
 */
int buildin_unittalk(struct script_state *st)
{
	struct block_list *bl;
	struct script_data *data;
	char *mes = NULL;
	int flag = 0;

	data = &(st->stack->stack_data[st->start+2]);
	get_val(st,data);
	if( isstr(data) ) {
		bl = map_id2bl(st->oid);
		mes = conv_str(st,data);
		if( st->end > st->start+3 )
			flag = conv_num(st,& (st->stack->stack_data[st->start+3]));
	} else {
		bl = map_id2bl(conv_num(st,data));

		data = &(st->stack->stack_data[st->start+3]);
		get_val(st,data);
		if( isstr(data) ) {
			mes = conv_str(st,data);
		}
		if( st->end > st->start+4 )
			flag = conv_num(st,& (st->stack->stack_data[st->start+4]));
	}

	if(bl == NULL || mes == NULL)
		return 0;

	if(bl->type == BL_PC) {	// グローバルメッセージ送信
		struct map_session_data *sd = (struct map_session_data *)bl;
		if(flag)
			clif_displaymessage(sd->fd, mes);
		else
			clif_disp_overhead(sd, mes);
	}
	else if(bl->m >= 0) {
		if(flag) {
			struct map_session_data *sd = script_rid2sd(st);
			if(sd)
				clif_GlobalMessage_id(&sd->bl, bl->id, mes, SELF);
		}
		else
			clif_GlobalMessage(bl, mes, WIDE_AREA);
	}

	return 0;
}

/*==========================================
 * プレイヤーの行動制限オンオフ
 *------------------------------------------
 */
int buildin_pcblockmove(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int flag;

	nullpo_retr(0, sd);

	flag = conv_num(st,& (st->stack->stack_data[st->start+2]));

	unit_stop_walking(&sd->bl,1);
	sd->state.blockedmove = flag > 0;

	return 0;
}


/*==========================================
 * リニューアルかどうか
 *------------------------------------------
 */
int buildin_checkre(struct script_state *st)
{
#ifdef PRE_RENEWAL
	push_val(st->stack,C_INT,0);
#else
	push_val(st->stack,C_INT,1);
#endif
	return 0;
}

/*==========================================
 * ドレスルームを開く
 *------------------------------------------
 */
int buildin_opendressroom(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int view = 1;

	nullpo_retr(0, sd);

	if( st->end > st->start+2 )
		view = conv_num(st,& (st->stack->stack_data[st->start+2]));
	clif_dressing_room(sd, view);
	return 0;
}

/*==========================================
 * Hat_effect
 *------------------------------------------
 */
int buildin_hateffect(struct script_state *st)
{
#if PACKETVER >= 20150513
	struct map_session_data *sd = script_rid2sd(st);
	bool enable;
	int i, effectID;

	nullpo_retr(0, sd);

	effectID = conv_num(st,& (st->stack->stack_data[st->start+2]));
	enable = conv_num(st,& (st->stack->stack_data[st->start+3])) ? true : false;

	if( effectID <= HAT_EF_MIN || effectID >= HAT_EF_MAX ) {
		printf( "buildin_hateffect: unsupported hat effect id: %d\n", effectID );
		return 1;
	}

	for(i = 0; i < sd->hatEffect.count; i++) {
		if(sd->hatEffect.id[i] == effectID)
			break;
	}

	if( enable ) {
		if( i < sd->hatEffect.count ) {
			return 0;
		}

		sd->hatEffect.id[sd->hatEffect.count] = effectID;
		sd->hatEffect.count++;
	}
	else {
		if( i == sd->hatEffect.count ) {
			return 0;
		}

		for( ; i < sd->hatEffect.count - 1; i++ ) {
			sd->hatEffect.id[i] = sd->hatEffect.id[i+1];
		}

		sd->hatEffect.count--;

		if( !sd->hatEffect.count )
			sd->hatEffect.count = 0;

	}

	if( !sd->state.connect_new ) {
		clif_hat_effect_single( sd, effectID, enable );
	}
#endif
	return 0;
}

/*==========================================
 * ランダム系アイテムのID取得
 *------------------------------------------
 */
int buildin_getrandombox(struct script_state *st)
{
	int nameid = conv_num(st,& (st->stack->stack_data[st->start+2]));

	push_val(st->stack,C_INT,itemdb_searchrandomid(-nameid));
	return 0;
}


/*==========================================
 * クエスト実績獲得
 *------------------------------------------
 */
int buildin_achievement(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int nameid = conv_num(st,& (st->stack->stack_data[st->start+2]));

	if(sd)
		achieve_update_content(sd, ACH_ADVENTURE, nameid, 1);
	return 0;
}

/*==========================================
 * 実績獲得
 *------------------------------------------
 */
int buildin_achievement2(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int type = conv_num(st,& (st->stack->stack_data[st->start+2]));
	int nameid = conv_num(st,& (st->stack->stack_data[st->start+3]));
	int num = conv_num(st,& (st->stack->stack_data[st->start+4]));

	if(type <= ACH_NONE || type >= ACH_MAX) {
		printf("buildin_achievement2: unsupported arg1, type=%d\n", type);
		return 1;
	}

	switch(type) {
	case ACH_LEVEL:
		if(nameid != SP_BASELEVEL && nameid != SP_JOBLEVEL) {
			printf("buildin_achievement2: unsupported arg2, type=%d, id=%d\n", type, nameid);
			return 1;
		}
		break;
	case ACH_STATUS:
		if(nameid < SP_STR || nameid > SP_LUK) {
			printf("buildin_achievement2: unsupported arg2, type=%d, id=%d\n", type, nameid);
			return 1;
		}
		break;
	case ACH_SPEND_ZENY:
	case ACH_GET_ZENY:
		if(nameid != SP_ZENY) {
			printf("buildin_achievement2: unsupported arg2, type=%d, id=%d\n", type, nameid);
			return 1;
		}
		break;
	case ACH_ACHIEVE:
	case ACH_QUEST:
		// 対象の存在チェックはしないよ！
		break;
	}

	if(sd)
		achieve_update_content(sd, type, nameid, num);
	return 0;
}


/*==========================================
 * アップグレードウィンドウ表示
 *------------------------------------------
 */
int buildin_openupgrade(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int nameid;

	nullpo_retr(0, sd);

	nameid = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if(nameid <= 0)
		return 0;

	clif_openlapineupgrade(sd, nameid);

	return 0;
}

/*==========================================
 * ユニットにGroup_id設定
 *------------------------------------------
 */
int buildin_setunitgroup(struct script_state *st)
{
	struct block_list *bl;
	int id;

	id = conv_num(st,& (st->stack->stack_data[st->start+2]));
	bl = map_id2bl(conv_num(st,& (st->stack->stack_data[st->start+3])));

	if(id < 0)
		return 0;
	if(bl == NULL || bl->type != BL_MOB)
		return 0;

	((struct mob_data*)bl)->group_id  = id;

	return 0;
}


/*==========================================
 * ユニットにTitle設定
 *------------------------------------------
 */
int buildin_setunittitle(struct script_state *st)
{
	struct block_list *bl;
	char *str;

	str = conv_str(st,& (st->stack->stack_data[st->start+2]));
	bl = map_id2bl(conv_num(st,& (st->stack->stack_data[st->start+3])));

	if(bl == NULL || bl->type != BL_MOB)
		return 0;

	strncpy(((struct mob_data*)bl)->title, str, 24);
	((struct mob_data*)bl)->title[23] = '\0';

	return 0;
}


