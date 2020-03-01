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

#ifndef _HTTPD_H_
#define _HTTPD_H_

// 注意
//   1.Auriga内蔵のhttpd で大きなファイルを送信することはお勧めしません。
//     200KB を超えるようなファイルは、別のソフトを利用することを勧めます。
//   2.ファイル名に使える文字は、[A-Za-z0-9-_\.] です。他の文字を使うと、
//     BAD REQUEST で弾かれます。

#include <time.h>

#ifdef WINDOWS
#	include <windows.h>
#else
#	include <sys/types.h>
#endif

enum {
	HTTPD_METHOD_UNKNOWN = 0, HTTPD_METHOD_GET , HTTPD_METHOD_POST
};

struct httpd_access;

struct httpd_session_data {
	int fd;
	int status;
	int http_ver;
	int header_len;
	int data_len;
	int method;
	int persist;
	int request_count;
	unsigned int tick;
	unsigned char* url;
	unsigned char* query;
	unsigned char* content_type;
	unsigned char* referer;
	unsigned char* user_agent;
	unsigned char* cookie;
	int query_len;
	unsigned char* auth;
	unsigned char user[33];
	unsigned char request_line[1024];
	unsigned char* req_head[32];
	struct httpd_access *access;
	int auth_digest_stale;
	unsigned int precond;
	int reshead_flag;
	time_t date;
	int file_pos;
	unsigned char* filename;
	int range_start, range_end, inst_len;	// 範囲開始位置、終了位置、エンティティ全体のサイズ

	int cgi_state;
#ifdef WINDOWS
	HANDLE	cgi_hCIn, cgi_hPIn, cgi_hOut, cgi_hErr, cgi_hProcess;
	DWORD cgi_dwProcessID;
#else
	int cgi_in, cgi_out, cgi_err;
	pid_t cgi_cpid;
#endif
};

void httpd_pages(const char* url,void(*httpd_func)(struct httpd_session_data* sd,const char* url));

// 指定されたURL に対するコールバック関数を設定する。この関数は、以下のように
// 実装する必要がある。
//
// 1. URL は、先頭のスラッシュが省かれたファイル名です。例えば、"GET / HTTP/1.0"
//    という風にリクエストされた時、URL には""(空文字)が入り、"GET /hoge HTTP/1.0"
//    の時には、"hoge"が入ります。
// 2. リクエストされたページが見つかったら、httpd_send() または、httpd_send_head()
//    とhttpd_send_data() の組を呼び出し、データを出力する。
// 3. httpd_send_file を指定すると、httpd/ 以下にあるファイルを出力する。ファイルに
//    空文字が指定された時は、index.htmlが指定されたものとみなされる。

void httpd_erase_pages(const char* url);
// 指定されたURL に対するコールバック関数を削除する

char* httpd_get_value(struct httpd_session_data* sd,const char* val);

// リクエストされたアドレスに渡されたフォームデータのうち、該当する文字列を返す。
// 例えば、"GET /status/graph?image=users HTTP/1.0"というリクエストの場合、
// httpd_get_value(sd,"image"); は、 "users"を返す。この関数の戻り値は、呼び出し元が
// 解放しなければならない。また、該当する文字列が無い時は、空の文字列を返す。

int httpd_get_method(struct httpd_session_data* sd);

// リクエスト形式を返す。
//
//     GET  : HTTPD_METHOD_GET
//     POST : HTTPD_METHOD_POST

unsigned long httpd_get_ip(struct httpd_session_data *sd);

// クライアントのIPを返す。


void httpd_default_page(void(*httpd_func)(struct httpd_session_data* sd,const char* url));

// 指定されたURL が登録されていない時に呼び出す関数を設定する。この関数を呼び出さないか、
// 関数の引数にNULLを指定すると、404 Not Found を返す。




void httpd_send(struct httpd_session_data* sd,int status,const char *content_type,int content_len,const void *data);

//	HTTPヘッダ、データを組にして送信する。この関数を呼び出した後に、httpd_send_data を
//  呼び出してはならない。
//
//		sd           : httpd_set_parse_func() に渡されたものをそのまま渡すこと。
//		status       : HTTPヘッダに加えるstatus。通常は200。
//		content_type : 送信するデータのタイプ。text/html , image/jpeg など。
//		content_len  : 送信するデータの長さ。
//		data         : 送信するデータへのポインタ



void httpd_send_head(struct httpd_session_data* sd,int status,const char *content_type,int content_len);

//	HTTPヘッダを送信する。
//
//		sd           : 同上
//		status       : 同上
//		content_type : 同上
//      content_len  : content_lenを-1に指定することで、この関数が呼ばれた時点で
//                     長さが分からないデータを送信することができる。この場合は
//                     強制的にHTTP/1.0 接続となり、オーバーヘッドが大きくなるので、
//                     あまりお勧めはしない。




void httpd_send_data(struct httpd_session_data* sd,int content_len,const void *data);

// データを送信する。この関数を、httpd_send_head() を呼び出す前に呼び出された場合、
// content_type = application/octet-stream, content_len = -1 としてヘッダが送信される。
//		sd           : 同上
//      content_len  : 送信するデータのdata長さを指定する。
//      data         : 送信するデータ



void httpd_send_file(struct httpd_session_data* sd,const char* url);

// ファイルを送信する。この関数は、httpd_send_head() を呼び出す前に呼び出さなければ
// ならない。ファイルに空文字が指定されたときは、index.htmlが指定されたと見なされる。



void httpd_send_error(struct httpd_session_data* sd,int status);

// HTTPエラーメッセージを送信する。status はHTTPのエラーコードと同じ。
// 	400 Bad Request, 404 Not Found, 500 Internal Server Error など。

int  httpd_parse(int fd);


// 認証関数の関数ポインタの typedef
struct httpd_access;
typedef int(*HTTPD_AUTH_FUNC)( struct httpd_access* a, struct httpd_session_data* sd, const char *userid, char *passwd );
// * この関数ポインタの先の関数が行うべきこと *
// userid に対応するプレーンパスワードを passwd (33バイトまで) に設定して返す
//  戻り値: 0 でエラー, 1 で成功
//  sd     = httpd のセッションデータへのポインタ
//  a      = 認証情報へのポインタ
//  userid = 認証のユーザーIDへのポインタ
//  passwd = パスワードを返すためのポインタ（ここに strcpy する）


// 認証関数の設定（func_id は httpd.conf の authfunc の番号）
void httpd_set_auth_func( int func_id, HTTPD_AUTH_FUNC func );

// 初期化処理
void do_init_httpd(void);

// ドキュメントルート設定
void httpd_set_document_root( const char *str );

// タイムアウト時間設定
void httpd_set_request_timeout( int idx, int time );

// 持続通信でのリクエスト最大数設定
void httpd_set_max_persist_requests( int count );

// ログファイル名設定
void httpd_set_logfile( const char *str );

// 設定ファイル読み込み
int httpd_config_read(const char *cfgName);


// メタ文字( < , > , & , " ) をエスケープした文字列を返す。
// XSS (クロスサイトスクリプティング)に対処するため、ユーザーが入力した
// 文字をそのまま出力する時は、この関数を通じてエスケープした文字を出力
// するべきです。この関数の戻り値は、呼び出し側が解放しなければならない。
char* httpd_quote_meta(const char* p1);

// 与えられた文字列を %xx の形にエンコードした文字列を返す。
// URL の中に日本語が混じるとUFT-8化して送信するブラウザがあるので、
// マルチバイト文字を <a href=""> の中に入れる時に使用してください。
// この関数の戻り値は、呼び出し側が解放しなければならない。
char* httpd_binary_encode(const char* val);

// base64 をデコードする。
// dest には十分なサイズ( [src の長さ] / 4 * 3 )の、メモリ確保して
// おく必要がある。 成功すると 1, 失敗すると 0 が返る
int httpd_decode_base64( char *dest, const char *src);

#endif
