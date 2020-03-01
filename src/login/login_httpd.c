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
#include <ctype.h>

#include "core.h"
#include "socket.h"
#include "httpd.h"
#include "graph.h"
#include "utils.h"
#include "malloc.h"

#include "login.h"
#include "login_httpd.h"

static bool httpd_new_account_flag = false;

#ifndef NO_HTTPD

static double login_httpd_users(void)
{
	int i;
	int users = 0;

	for(i=0;i<MAX_CHAR_SERVERS;i++) {
		if(server_fd[i] > 0) {
			users += server[i].users;
		}
	}

	return (double)users;
}

static void login_httpd_account(struct httpd_session_data *sd,const char* url)
{
	char* userid     = httpd_get_value(sd,"userid");
	int   userid_len = (int)strlen(userid);
	char* passwd     = httpd_get_value(sd,"passwd");
	int   passwd_len = (int)strlen(passwd);
	char* gender     = httpd_get_value(sd,"gender");
	char* check      = httpd_get_value(sd,"check");
	const char* msg  = "";
	int   i;

	do {
		if(httpd_get_method(sd) != HTTPD_METHOD_POST) {
			// POST以外お断り
			msg = "Illegal request."; break;
		}
		if(!httpd_new_account_flag) {
			msg = "Now stopping to create accounts on httpd."; break;
		}
		if(userid_len < 4 || userid_len > 23) {
			msg = "Please input UserID 4-23 bytes."; break;
		}
		for(i = 0; i < userid_len; i++) {
			if(!isalnum((unsigned char)userid[i])) break;
		}
		if(i != userid_len) {
			msg = "Illegal character found in UserID."; break;
		}

		if(check[0]) {	// ID のチェックは userid だけでいい
			if(account_load_str(userid) == NULL) {
				msg = "OK : You can use UserID.";
			} else {
				msg = "NG : UserID is already used.";
			}
			break;
		}

		if(passwd_len < 4 || passwd_len > 23) {
			msg = "Please input Password 4-23 bytes."; break;
		}
		for(i = 0; i < passwd_len; i++) {
			if(!isalnum((unsigned char)passwd[i])) break;
		}
		if(i != passwd_len) {
			msg = "Illegal character found in Password."; break;
		}
		if(gender[0] != 'M' && gender[0] != 'F') {
			msg = "Gender error."; break;
		}

		if(!check[0]) {
			struct mmo_account ma;
			char   buf[32];
			memset(&ma,0,sizeof(ma));
			strncpy(ma.userid,userid,24);
			strncpy(ma.pass  ,passwd,24);
			ma.sex = gender[0];
			strncpy(ma.mail  ,"@"     ,40); // 暫定
			strncpy(ma.birth ,"000000", 7);
			sprintf(buf,"( httpd %08lx )",httpd_get_ip(sd));
			if( !account_new(&ma,buf) ) {
				msg = "Account creation failed.";
			} else {
				msg = "Account successfully created.";
			}
		}
	} while(0);

	// HTTP/1.1で返すとアカウントを連続して作成する馬鹿がいそうなので、
	// あえてHTTP/1.0扱いしている。
	httpd_send_head(sd,200,"text/plain",-1);
	httpd_send_data(sd,(int)strlen(msg),msg);

	aFree(userid);
	aFree(passwd);
	aFree(gender);
	aFree(check);

	return;
}

static void login_httpd_socket_ctrl_panel_func(int fd,char* usage,char* user,char* status)
{
	struct socket_data *sd = session[fd];
	struct login_session_data *ld = (struct login_session_data *)sd->session_data;

	strcpy( usage,
		( sd->func_parse == parse_login )? "login user" :
		( sd->func_parse == parse_admin )? "administration" :
		( sd->func_parse == parse_fromchar)? "char server" : "unknown" );

	if( sd->func_parse == parse_fromchar && sd->auth )
	{
		int id;
		for(id=0;id<MAX_CHAR_SERVERS;id++)
			if(server_fd[id]==fd)
				break;
		if( id<MAX_CHAR_SERVERS )
			sprintf( user, "%s (%s)", ld->userid, server[id].name );
	}
	else if( sd->func_parse == parse_login && sd->auth )
	{
		sprintf( user, "%s (%d)", ld->userid, ld->account_id );
	}
}

static int login_httpd_auth_func( struct httpd_access* a, struct httpd_session_data* sd, const char *userid, char *passwd )
{
	const struct mmo_account *acc;
	const char *p;

	p = (const char *)memchr(userid, '\0', 24);
	if( p == NULL )	// 24文字以上はありえない
		return 0;

	acc = account_load_str( userid );
	if( !acc )
		return 0;

	strcpy( passwd, acc->pass );
	return 1;
}

#endif

int login_httpd_config_read(const char *w1, const char *w2)
{
	char w3[1026];

	memcpy(w3, w2, sizeof(w3));

	if( strcmpi(w1, "httpd_enable") == 0 )
		socket_enable_httpd(atoi(w3));
	else if ( strcmpi(w1, "httpd_document_root") == 0 )
		httpd_set_document_root(w3);
	else if ( strcmpi(w1, "httpd_new_account") == 0 )
		httpd_new_account_flag = (atoi(w3) ? true : false);
	else if (strcmpi(w1, "httpd_log_filename") == 0 )
		httpd_set_logfile(w3);
	else if (strcmpi(w1, "httpd_config") == 0 )
		httpd_config_read(w3);
	else
		return 0;

	return 1;
}

void login_httpd_init(void)
{
#ifndef NO_HTTPD
	socket_set_httpd_page_connection_func( login_httpd_socket_ctrl_panel_func );
	do_init_httpd();
	do_init_graph();
	graph_add_sensor( "Login Users",  60 * 1000, login_httpd_users );
	graph_add_sensor( "Uptime(days)", 60 * 1000, uptime );
	graph_add_sensor( "Memory Usage(KB)", 60 * 1000, memmgr_usage );
	httpd_pages( "/account", login_httpd_account );
	httpd_default_page( httpd_send_file );
	httpd_set_auth_func( 1, login_httpd_auth_func );
#endif

	return;
}
