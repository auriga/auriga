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

#define DUMP_UNKNOWN_PACKET	1

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#ifndef WINDOWS
#include <sys/time.h>
#endif

#include "core.h"
#include "socket.h"
#include "mmo.h"
#include "version.h"
#include "db.h"
#include "malloc.h"
#include "timer.h"
#include "utils.h"

#include "login.h"
#include "login_httpd.h"

#ifdef PASSWORDENC
#include "md5calc.h"
#endif

// 性別コンバート
#define sex_num2str(num) ((num == SEX_FEMALE)? 'F' : (num == SEX_MALE) ? 'M' : 'S')
#define sex_str2num(str) ((str == 'F')? SEX_FEMALE : (str == 'M')? SEX_MALE : SEX_SERVER)

static int login_fd;
static int login_sfd;
struct mmo_char_server server[MAX_CHAR_SERVERS];
int server_fd[MAX_CHAR_SERVERS];

struct login_config {
	bool new_account_flag;
	bool detect_multiple_login;
	bool ristrict_admin_local;
	unsigned short login_port;
	unsigned short login_sport;
	unsigned long login_sip;
	char login_shost[256];
	char admin_pass[64];
	char ladmin_pass[64];
	char login_conf_filename[256];
	char GM_account_filename[1024];
	int login_autosave_time;
	int login_version;
	int login_type;
};

static struct {
	int account_id;
	int login_id1;
	int login_id2;
	unsigned long ip;
	bool delflag;
	char sex;
} auth_fifo[AUTH_FIFO_SIZE];
static int auth_fifo_pos = 0;

static struct login_config config;

static struct dbt *gm_account_db = NULL;

static int gm_account_db_final(void *key, void *data, va_list ap);

/*==========================================
 * GMアカウント読み込み
 *------------------------------------------
 */
static void read_gm_account(void)
{
	char line[8192];
	struct gm_account *p;
	FILE *fp;
	int i, c, l;
	int account_id, level;
	int range, start_range, end_range;

	gm_account_db = numdb_init();

	if ((fp = fopen(config.GM_account_filename, "r")) == NULL) {
		printf("read_gm_account: open [%s] failed !\n", config.GM_account_filename);
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
				printf("gm_account [%s]: invalid GM level [%ds] line %d\n", config.GM_account_filename, level, l);
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
			printf("gm_account: broken data [%s] line %d\n", config.GM_account_filename, l);
		}
	}
	fclose(fp);
	printf("gm_account: %s read done (%d gm account ID)\n", config.GM_account_filename, c);

	return;
}

/*==========================================
 * GMかどうか
 *------------------------------------------
 */
int isGM(int account_id)
{
	struct gm_account *p;

	if (gm_account_db == NULL)
		return 0;

	p = (struct gm_account *)numdb_search(gm_account_db, account_id);
	if (p == NULL)
		return 0;

	return p->level;
}

/*==========================================
 * authfifoの比較
 *------------------------------------------
 */
static bool cmp_authfifo(int i, int account_id, int login_id1, int login_id2, unsigned long ip)
{
	if( auth_fifo[i].account_id == account_id && auth_fifo[i].login_id1 == login_id1 )
		return true;

#ifdef CMP_AUTHFIFO_LOGIN2
	if( auth_fifo[i].login_id2 == login_id2 && login_id2 != 0 )
		return true;
#endif

#ifdef CMP_AUTHFIFO_IP
	if( auth_fifo[i].ip == ip && ip != 0 && ip != 0xffffffff )
		return true;
#endif

	return false;
}

/*==========================================
 * 自分以外の全てのcharサーバーにデータ送信
 * （送信したchar鯖の数を返す）
 *------------------------------------------
 */
static int charif_sendallwos(int sfd, unsigned char *buf, size_t len)
{
	int i,c;

	for( i = 0, c = 0; i < MAX_CHAR_SERVERS; i++ )
	{
		int fd;
		if( ( fd = server_fd[i] ) > 0 && fd != sfd )
		{
			memcpy(WFIFOP(fd,0),buf,len);
			WFIFOSET(fd,len);
			c++;
		}
	}

	return c;
}

/*==========================================
 * 認証
 *------------------------------------------
 */
static int mmo_auth(struct login_session_data *sd)
{
	char tmpstr[32];
	size_t len;
	bool newaccount  = false;
	const struct mmo_account *ac;

	if( sd == NULL )
		return 1;

#ifdef WINDOWS
	{
		time_t time_;
		time(&time_);
		len = strftime(tmpstr,sizeof(tmpstr),"%Y-%m-%d %H:%M:%S",localtime(&time_));
		sprintf(tmpstr+len,".%03d",0);
	}
#else
	{
		struct timeval tv;
		gettimeofday(&tv,NULL);
		len = strftime(tmpstr,sizeof(tmpstr),"%Y-%m-%d %H:%M:%S",localtime(&(tv.tv_sec)));
		sprintf(tmpstr+len,".%03d",(int)tv.tv_usec/1000);
	}
#endif

	len = strlen(sd->userid) - 2;

	// to avoid invalid length (min 4 char for account name, max 23 including _F/_M)
	if( config.new_account_flag == true && len >= 4 && len <= 21 && sd->passwdenc == 0 && sd->userid[len] == '_' && (sd->userid[len+1] == 'F' || sd->userid[len+1] == 'M') )
	{
		// 新規アカウント作成
		char *adm_pass = strchr(sd->pass,'@');
		if( adm_pass == NULL )
			adm_pass = sd->pass + strlen(sd->pass);
		else
			adm_pass++;
		if( strcmp(adm_pass, config.admin_pass) == 0 )
		{
			if(*adm_pass)
				*(adm_pass - 1) = 0;
			newaccount      = true;
			sd->userid[len] = 0;
		}
		else
			sd->userid[0] = 0;
	}

	// アカウントが見つからない
	if( (ac = account_load_str(sd->userid)) == NULL )
	{
		if( newaccount == false )	// 新規作成以外
			loginlog_log("auth failed no account %s %s %d %s", tmpstr, sd->userid, newaccount, (sd->passwdenc == 0)? sd->pass:"");
		else
		{
			// 新規作成
			struct mmo_account ac2;
			memset( &ac2, 0, sizeof(ac2) );
			strncpy(ac2.userid,sd->userid,24);
			strncpy(ac2.pass  ,sd->pass  ,24);
			ac2.sex = sd->userid[len+1];
			if( account_new(&ac2, tmpstr) == false )	// 作成失敗
				loginlog_log("auth new failed %s %s %d %s", tmpstr, sd->userid, newaccount, sd->pass);
		}
		return 0;
	}

	// パスワードチェック(MD5)
	if( sd->passwdenc > 0 )
	{
		bool encpasswdok = false;
		int enc = sd->passwdenc;
		char md5bin[32];

		if( !sd->md5keylen )
		{
			loginlog_log("md5key not created %s %s",tmpstr,sd->userid);
			return 1;
		}

		if( enc == 4 )
		{
			HMAC_MD5_Binary( ac->pass, (int)strlen(ac->pass), sd->md5key, sd->md5keylen, md5bin );
			encpasswdok = ( memcmp( sd->pass, md5bin, 16) == 0);
		}

		else if( enc <= 3 )
		{
			char md5str[192];
			if( enc > 2 )
				enc = 1;
			do
			{
				if( enc == 1 )
					snprintf(md5str, sizeof(md5str), "%s%s", sd->md5key, ac->pass);
				else if( enc == 2 )
					snprintf(md5str, sizeof(md5str), "%s%s", ac->pass, sd->md5key);
				else
					md5str[0] = 0;
				MD5_String2binary(md5str,md5bin);
				encpasswdok = ( memcmp( sd->pass, md5bin, 16) == 0);
			} while(enc < 2 && !encpasswdok && (enc++) != sd->passwdenc);
		}

		if( encpasswdok == false )
		{
			// 認証失敗
			char logbuf[1024],*p=logbuf;
			int j;
			p += sprintf(p, "auth failed pass error %s %s enc=%d recv[", tmpstr, sd->userid, sd->passwdenc);
			for( j = 0; j < 16; j++ )
				p += sprintf(p, "%02x", ((unsigned char *)sd->pass)[j]);
			p += sprintf(p, "] calc[");
			for( j = 0; j < 16; j++ )
				p += sprintf(p, "%02x", ((unsigned char *)md5bin)[j]);
			p += sprintf(p, "] keylen=%d newaccount=%d", sd->md5keylen, newaccount);
			loginlog_log(logbuf);

			return 1;
		}
	}
	else if( strcmp(sd->pass,ac->pass) || newaccount == true )
	{
		// 認証失敗
		loginlog_log("auth failed pass error %s %s %s %d", tmpstr, sd->userid, sd->pass, newaccount);
		return 1;
	}

	// BAN
	if( ac->state )
	{
		loginlog_log("auth banned account %s %s %s %d", tmpstr, sd->userid, ac->pass, ac->state);
		switch(ac->state)
		{
			case 1: return 2;
			case 2: return 3;
			case 3: return 4;
		}
		return 2;
	}

	// 認証成功
	loginlog_log("auth ok %s %s new=%d", tmpstr, ac->userid, newaccount);
	{
		struct mmo_account ac2;
		memcpy(&ac2,ac,sizeof(struct mmo_account));
		memcpy(ac2.lastlogin,tmpstr,24);
		ac2.logincount++;
		memcpy(ac2.lastip,sd->lastip,16);
		account_save(&ac2);

		// session data 初期化
		sd->account_id = ac->account_id;
		sd->login_id1  = atn_rand();
		sd->login_id2  = atn_rand();
		sd->sex        = ac->sex;
		memcpy(sd->lastlogin,tmpstr,24);
	}

	return -1;	// 認証OK
}

/*==========================================
 * 認証後の設定
 *------------------------------------------
 */
static void login_authok(struct login_session_data *sd, int fd)
{
	int server_num = 0;
	int i;
#if PACKETVER < 20170315
	int cmd = 0x69;
	int header = 47;
	int size = 32;
#else
	int cmd = 0xac4;
	int header = 64;
	int size = 160;
#endif

	if( config.detect_multiple_login == true )
	{
		unsigned char buf[8];
		int c = 0;

		// 全charサーバへ同一アカウントの切断要求
		WBUFW(buf,0) = 0x2730;
		WBUFL(buf,2) = sd->account_id;
		charif_sendallwos(-1,buf,6);

		for( i = 0; i < AUTH_FIFO_SIZE; i++ )
		{
			if( auth_fifo[i].account_id == sd->account_id && auth_fifo[i].delflag == false )
			{
				auth_fifo[i].delflag = true;
				c++;
			}
		}
		if( c > 0 )
		{
			// 二重ログインの可能性があるので認証失敗にする
			WFIFOW(fd,0) = 0x81;
			WFIFOB(fd,2) = 8;
			WFIFOSET(fd,3);
			return;
		}
	}

	for( i = 0; i < MAX_CHAR_SERVERS; i++ )
	{
		if( server_fd[i] >= 0 )
		{
			WFIFOL(fd,header+server_num*size)   = server[i].ip;
			WFIFOW(fd,header+server_num*size+4) = server[i].port;
			memcpy(WFIFOP(fd,header+server_num*size+6), server[i].name, 20);
			WFIFOW(fd,header+server_num*size+26) = server[i].users;
			WFIFOW(fd,header+server_num*size+28) = server[i].maintenance;
			WFIFOW(fd,header+server_num*size+30) = server[i].new_;
#if PACKETVER >= 20170315
			memset(WFIFOP(fd, header+server_num*size+32), 0, 128);
#endif
			server_num++;
		}
	}

	WFIFOW(fd, 0) = cmd;
	WFIFOW(fd, 2) = header+size*server_num;
	WFIFOL(fd, 4) = sd->login_id1;
	WFIFOL(fd, 8) = sd->account_id;
	WFIFOL(fd,12) = sd->login_id2;
	WFIFOL(fd,16) = 0;
	memcpy(WFIFOP(fd,20),sd->lastlogin,24);
	WFIFOB(fd,46) = sex_str2num(sd->sex);
#if PACKETVER >= 20170315
	memset(WFIFOP(fd,47),0,17);
#endif
	WFIFOSET(fd,header+size*server_num);

	for( i = 0; i < AUTH_FIFO_SIZE; i++ )
	{
		if( cmp_authfifo(i,sd->account_id,sd->login_id1,sd->login_id2,session[fd]->client_addr.sin_addr.s_addr) == true &&
		    auth_fifo[i].sex == sd->sex &&
		    auth_fifo[i].delflag == false )
		{
			auth_fifo[i].delflag = true;
			break;
		}
	}

	if( auth_fifo_pos >= AUTH_FIFO_SIZE )
		auth_fifo_pos = 0;

	auth_fifo[auth_fifo_pos].account_id = sd->account_id;
	auth_fifo[auth_fifo_pos].login_id1  = sd->login_id1;
	auth_fifo[auth_fifo_pos].login_id2  = sd->login_id2;
	auth_fifo[auth_fifo_pos].sex        = sd->sex;
	auth_fifo[auth_fifo_pos].delflag    = false;
	auth_fifo[auth_fifo_pos].ip         = session[fd]->client_addr.sin_addr.s_addr;
	auth_fifo_pos++;

	// 認証終了を socket.c に伝える
	session[fd]->auth = 1;

	return;
}

/*==========================================
 * キャラクタサーバのソケットデストラクタ
 *------------------------------------------
 */
static int parse_char_disconnect(int fd)
{
	int i;

	for( i = 0; i < MAX_CHAR_SERVERS; i++ )
	{
		if( server_fd[i] == fd )
			server_fd[i] = -1;
	}

	close(fd);
	delete_session(fd);

	return 0;
}

/*==========================================
 * キャラクタサーバからのパケット解析
 *------------------------------------------
 */
int parse_fromchar(int fd)
{
	int id;

	for( id = 0; id < MAX_CHAR_SERVERS; id++ )
	{
		if(server_fd[id] == fd)
			break;
	}
	if(id >= MAX_CHAR_SERVERS)
		session[fd]->eof = 1;

	while(RFIFOREST(fd) >= 2)
	{
		switch(RFIFOW(fd,0))
		{

		case 0x2712:	// キャラクター鯖へのログイン認証
			if( RFIFOREST(fd) < 19 )
				return 0;
			{
				int i;
				int account_id   = RFIFOL(fd,2);
				int login_id1    = RFIFOL(fd,6);
				int login_id2    = RFIFOL(fd,10);
				char sex         = sex_num2str(RFIFOB(fd,14));
				unsigned long ip = RFIFOL(fd,15);

				for( i = 0; i < AUTH_FIFO_SIZE; i++ )
				{
					if( cmp_authfifo(i,account_id,login_id1,login_id2,ip) == true &&
					    auth_fifo[i].sex == sex &&
					    auth_fifo[i].delflag == false )
					{
						auth_fifo[i].delflag = true;
						break;
					}
				}
				if( i < AUTH_FIFO_SIZE )
				{
					const struct mmo_account *ac = account_load_num(auth_fifo[i].account_id);

					// account_reg送信
					if(ac)
					{
						int p,j;

						WFIFOW(fd,0) = 0x2729;
						WFIFOL(fd,4) = ac->account_id;
						for( p = 8, j = 0; j < ac->account_reg2_num; p += 36, j++ )
						{
							memcpy(WFIFOP(fd,p),ac->account_reg2[j].str,32);
							WFIFOL(fd,p+32) = ac->account_reg2[j].value;
						}
						WFIFOW(fd,2) = p;
						WFIFOSET(fd,p);
					}

					WFIFOW(fd,0)=0x2713;
					WFIFOL(fd,2)=account_id;
					WFIFOB(fd,6)=0;
					WFIFOL(fd,7)=auth_fifo[i].account_id;
					WFIFOL(fd,11)=auth_fifo[i].login_id1;
					WFIFOSET(fd,15);
				}
				else
				{
					WFIFOW(fd,0)=0x2713;
					WFIFOL(fd,2)=account_id;
					WFIFOB(fd,6)=1;
					WFIFOSET(fd,15);
				}
				RFIFOSKIP(fd,19);
			}
			break;

		case 0x2714:	// ワールドのユーザー数通知
			if( RFIFOREST(fd) < 6 )
				return 0;

			server[id].users = RFIFOL(fd,2);
			RFIFOSKIP(fd,6);
			break;
		case 0x2715:	// メールアドレス認証
			if( RFIFOREST(fd) < 50 )
				return 0;
			{
#ifdef AC_MAIL
				const struct mmo_account *ac = account_load_num(RFIFOL(fd,2));
				WFIFOB(fd,10)=( ac && strcmp( ac->mail,RFIFOP(fd,10)) == 0 )? 0 : 1;
#else
				WFIFOB(fd,10)=0;
#endif
				WFIFOW(fd, 0)=0x2716;
				WFIFOL(fd, 2)=RFIFOL(fd,2);
				WFIFOL(fd, 6)=RFIFOL(fd,6);
				WFIFOSET(fd,11);
				RFIFOSKIP(fd,50);
			}
			return 0;
		case 0x2717:	// 誕生日認証
			if( RFIFOREST(fd) < 17 )
				return 0;
			{
#ifdef AC_BIRTHDATE
				const struct mmo_account *ac = account_load_num(RFIFOL(fd,2));
				WFIFOB(fd,10)=( ac && strcmp( ac->birth,RFIFOP(fd,10)) == 0 )? 0 : 1;
#else
				WFIFOB(fd,10)=0;
#endif
				WFIFOW(fd, 0)=0x2718;
				WFIFOL(fd, 2)=RFIFOL(fd,2);
				WFIFOL(fd, 6)=RFIFOL(fd,6);
				WFIFOSET(fd,11);
				RFIFOSKIP(fd,17);
			}
			return 0;

		case 0x2720:
			// GMになりたーい
			// SQL 化が面倒なのでとりあえず保留
			WFIFOW(fd,0)=0x2721;
			WFIFOL(fd,2)=RFIFOL(fd,4);
			WFIFOL(fd,6)=RFIFOL(fd,4);
			WFIFOSET(fd,10);
			RFIFOSKIP(fd,RFIFOW(fd,2));
			return 0;

		case 0x2722:	// changesex
			if( RFIFOREST(fd) < 4 || RFIFOREST(fd) < RFIFOW(fd,2) )
				return 0;

			{
				const struct mmo_account *ac = account_load_num(RFIFOL(fd,4));

				if(ac)
				{
					struct mmo_account ac2;
					memcpy(&ac2,ac,sizeof(struct mmo_account));
					ac2.sex = sex_num2str(RFIFOB(fd,8));
					account_save(&ac2);
				}

				WFIFOW(fd,0) = 0x2723;
				WFIFOL(fd,2) = RFIFOL(fd,4);
				WFIFOB(fd,6) = RFIFOB(fd,8);
				WFIFOSET(fd,7);
				RFIFOSKIP(fd,RFIFOW(fd,2));
			}
			return 0;

		case 0x2728:	// save account_reg
			if( RFIFOREST(fd) < 4 || RFIFOREST(fd) < RFIFOW(fd,2) )
				return 0;

			{
				const struct mmo_account *ac = account_load_num(RFIFOL(fd,4));

				if(ac)
				{
					int p,j;
					unsigned char buf[ACCOUNT_REG2_NUM*36+16];
					struct mmo_account ac2;
					memcpy(&ac2,ac,sizeof(struct mmo_account));
					for( p = 8, j = 0; p < RFIFOW(fd,2) && j < ACCOUNT_REG2_NUM; p += 36, j++ )
					{
						strncpy(ac2.account_reg2[j].str,RFIFOP(fd,p),32);
						ac2.account_reg2[j].str[31] = '\0';	// force \0 terminal
						ac2.account_reg2[j].value   = RFIFOL(fd,p+32);
					}
					ac2.account_reg2_num = j;
					account_save(&ac2);

					// 他のサーバーへポスト（同垢ログインがなければ送らなくていい）
					memcpy(WBUFP(buf,0),RFIFOP(fd,0),RFIFOW(fd,2));
					WBUFW(buf,0)=0x2729;
					charif_sendallwos(fd,buf,WBUFW(buf,2));
				}

				RFIFOSKIP(fd,RFIFOW(fd,2));
				//printf("login: save account_reg (from char)\n");
			}
			break;

		case 0x272b:	// charサーバメンテナンス状態
			if( RFIFOREST(fd) < 3 )
				return 0;

			server[id].maintenance=RFIFOB(fd,2);
			// charサーバに応答
			WFIFOW(fd,0)=0x272c;
			WFIFOB(fd,2)=server[id].maintenance;
			WFIFOSET(fd,3);

			RFIFOSKIP(fd,3);
			break;

		default:
			printf("parse_fromchar: unknown packet 0x%04x disconnect session #%d\n", RFIFOW(fd,0), fd);
#ifdef DUMP_UNKNOWN_PACKET
			hex_dump(stdout, RFIFOP(fd,0), RFIFOREST(fd));
			printf("\n");
#endif
			close(fd);
			session[fd]->eof=1;
			return 0;
		}
	}

	return 0;
}

/*==========================================
 * アドミンのソケットデストラクタ
 *------------------------------------------
 */
static int parse_admin_disconnect(int fd)
{
	int i;

	for( i = 0; i < MAX_CHAR_SERVERS; i++ )
	{
		if( server_fd[i] == fd )
			server_fd[i] = -1;
	}
	close(fd);
	delete_session(fd);

	return 0;
}

/*==========================================
 * アドミンのパケット解析
 *------------------------------------------
 */
int parse_admin(int fd)
{
	int i;

	while( RFIFOREST(fd) >= 2 )
	{
		switch(RFIFOW(fd,0))
		{
			case 0x7530:	// Auriga情報取得
				WFIFOW(fd,0)=0x7531;
				WFIFOB(fd,2)=AURIGA_MAJOR_VERSION;
				WFIFOB(fd,3)=AURIGA_MINOR_VERSION;
				WFIFOW(fd,4)=AURIGA_REVISION;
				WFIFOB(fd,6)=AURIGA_RELEASE_FLAG;
				WFIFOB(fd,7)=AURIGA_OFFICIAL_FLAG;
				WFIFOB(fd,8)=AURIGA_SERVER_LOGIN;
				WFIFOW(fd,9)=get_current_version();
				WFIFOSET(fd,11);
				RFIFOSKIP(fd,2);
				break;

			case 0x7532:	// 接続の切断(defaultと処理は一緒だが明示的にするため)
				RFIFOSKIP(fd,2);
				close(fd);
				session[fd]->eof=1;
				return 0;

			case 0x7920:
				if( RFIFOREST(fd) < 11 )
					return 0;
				{
					// アカウントリスト
					int st  = RFIFOL(fd,2);
					int ed  = RFIFOL(fd,6);
					int len = 4;
					const struct mmo_account* ac;

					if( st < 0 )
						st = 0;
					if( ed > END_ACCOUNT_NUM || ed < st || ed <= 0 )
						ed = END_ACCOUNT_NUM;

					i = 0;
					do
					{
						WFIFOW(fd,0)=0x7921;
						len = 4;
						while( (ac = account_load_idx(i++) ) && len <= 65000 )
						{
							WFIFORESERVE(fd,len+61);
							if( ac->account_id >= st && ac->account_id <= ed )
							{
								WFIFOL(fd,len   ) = ac->account_id;
								memcpy(WFIFOP(fd,len+4),ac->userid,24);
								WFIFOB(fd,len+28) = sex_str2num(ac->sex);
								WFIFOL(fd,len+53) = ac->logincount;
								WFIFOL(fd,len+57) = ac->state;
								len+=61;
							}
						}
						WFIFOW(fd,2)=len;
						WFIFOSET(fd,len);
					} while( len > 65000 );

					RFIFOSKIP(fd,11);
				}
				break;

			case 0x7930:	// アカウント作成要求
				if( RFIFOREST(fd) < 98 )
					return 0;
				{
					// アカウント作成
					struct mmo_account ma;
					memset( &ma, 0, sizeof(ma) );
					memcpy(ma.userid,RFIFOP(fd, 2),24);
					memcpy(ma.pass,RFIFOP(fd,26),24);
					ma.sex = RFIFOB(fd,50);
					memcpy(ma.mail,RFIFOP(fd,51),40);
					memcpy(ma.birth,RFIFOP(fd,91),7);

					// アカウント作成結果通知
					WFIFOW(fd,0) = 0x7931;
					WFIFOW(fd,2) = 0;
					memcpy(WFIFOP(fd,4),RFIFOP(fd,2),24);
					if( account_new(&ma,"( ladmin )") == false )
						WFIFOW(fd,2)=1;
					WFIFOSET(fd,28);
					RFIFOSKIP(fd,98);
				}
				break;

			case 0x7932:
				// アカウント削除
				if( RFIFOREST(fd) < 26 )
					return 0;
				{
					char userid[24];
					const struct mmo_account *ac;

					memcpy(userid, RFIFOP(fd,2), 24);
					userid[23] = '\0';	// force \0 terminal
					ac = account_load_str(userid);
					WFIFOW(fd,0) = 0x7933;
					WFIFOW(fd,2) = 1;
					memcpy(WFIFOP(fd,4),RFIFOP(fd,2),24);
					if(ac)
					{
						// キャラサーバーへ削除通知
						unsigned char buf[8];
						WBUFW(buf,0) = 0x272a;
						WBUFL(buf,2) = ac->account_id;
						charif_sendallwos(-1,buf,6);
						WFIFOW(fd,2) = 0;
						account_delete(ac->account_id);
					}
					WFIFOSET(fd,28);
					RFIFOSKIP(fd,26);
				}
				break;

			case 0x7934:
				// パスワード変更
				if( RFIFOREST(fd) < 50 )
					return 0;

				{
					char userid[24];
					const struct mmo_account *ac;
					memcpy(userid, RFIFOP(fd,2), 24);
					userid[23] = '\0';	// force \0 terminal
					ac = account_load_str(userid);
					WFIFOW(fd,0)=0x7935;
					WFIFOW(fd,2)=1;
					memcpy(WFIFOP(fd,4),RFIFOP(fd,2),24);
					if(ac)
					{
						struct mmo_account ac2;
						memcpy(&ac2,ac,sizeof(struct mmo_account));
						strncpy(ac2.pass,RFIFOP(fd,26),24);
						ac2.pass[23] = '\0';	// force \0 terminal
						account_save(&ac2);
						WFIFOW(fd,2)=0;
					}
					WFIFOSET(fd,28);
					RFIFOSKIP(fd,50);
				}
				break;

			case 0x7936:
				// バン状態変更
				if( RFIFOREST(fd) < 30 )
					return 0;
				{
					char userid[24];
					const struct mmo_account *ac;
					memcpy(userid, RFIFOP(fd,2), 24);
					userid[23] = '\0';	// force \0 terminal
					ac = account_load_str(userid);
					WFIFOW(fd, 0) = 0x7937;
					WFIFOW(fd, 2) = 1;
					WFIFOL(fd,28) = 0;
					memcpy(WFIFOP(fd,4),RFIFOP(fd,2),24);
					if(ac)
					{
						struct mmo_account ac2;
						memcpy(&ac2,ac,sizeof(struct mmo_account));
						ac2.state=RFIFOL(fd,26);
						account_save(&ac2);
						WFIFOW(fd, 2) = 0;
						WFIFOL(fd,28) = ac2.state;
					}
					WFIFOSET(fd,32);
					RFIFOSKIP(fd,30);
				}
				break;

			case 0x7938:
				// information about servers
				{
					int server_num = 0;
					for( i = 0; i < MAX_CHAR_SERVERS; i++ ) // max number of char-servers (and account_id values: 0 to max-1)
					{
						if( server_fd[i] >= 0 )
						{
							WFIFOL(fd,4 + server_num * 32     ) = server[i].ip;
							WFIFOW(fd,4 + server_num * 32 +  4) = server[i].port;
							strncpy(WFIFOP(fd,4 + server_num * 32 + 6), server[i].name, 20);
							WFIFOW(fd,4 + server_num * 32 + 26) = server[i].users;
							WFIFOW(fd,4 + server_num * 32 + 28) = server[i].maintenance;
							WFIFOW(fd,4 + server_num * 32 + 30) = server[i].new_;
							server_num++;
						}
					}
					WFIFOW(fd,0) = 0x7939;
					WFIFOW(fd,2) = 4 + 32 * server_num;
					WFIFOSET(fd, 4 + 32 * server_num);
					RFIFOSKIP(fd,2);
				}
				break;

			case 0x793a:
				// request to test a password
				if( RFIFOREST(fd) < 50 )
					return 0;
				{
					char userid[24];
					const struct mmo_account *ac;
					memcpy(userid, RFIFOP(fd,2), 24);
					userid[23] = '\0';	// force \0 terminal
					ac = account_load_str(userid);
					WFIFOW(fd, 0) = 0x793b;
					WFIFOW(fd, 2) = 1;
					memcpy(WFIFOP(fd,4), RFIFOP(fd,2), 24);
					if(ac)
					{
						if(memcmp(ac->pass, RFIFOP(fd,26), 24) == 0)
							WFIFOW(fd, 2) = 0;
					}
					WFIFOSET(fd,28);
					RFIFOSKIP(fd,50);
				}
				break;

			case 0x793c:
				// request to obtain complete information about an account. (by name)
				if( RFIFOREST(fd) < 26 )
					return 0;
				{
					char userid[24];
					const struct mmo_account *ac;
					memcpy(userid, RFIFOP(fd,2), 24);
					userid[23] = '\0';	// force \0 terminal
					ac = account_load_str(userid);
					memset(WFIFOP(fd,0), 0, 120);
					WFIFOW(fd, 0) = 0x793e;
					WFIFOW(fd, 2) = 1;
					memcpy(WFIFOP(fd,9), RFIFOP(fd,2), 24);
					if(ac)
					{
						WFIFOW(fd, 2) = 0;
						WFIFOL(fd, 4) = ac->account_id;
						WFIFOB(fd, 8) = isGM(ac->account_id);
						//memcpy(WFIFOP(fd, 9), ac->userid, 24);
						WFIFOB(fd,33) = sex_str2num(ac->sex);
						WFIFOL(fd,34) = ac->logincount;
						WFIFOW(fd,38) = ac->state;
						memcpy(WFIFOP(fd,40), ac->lastip, 16);
						memcpy(WFIFOP(fd,56), ac->lastlogin, 24);
						memcpy(WFIFOP(fd,80), ac->mail, 40);
					}
					WFIFOSET(fd,120);
					RFIFOSKIP(fd,26);
				}
				break;

			case 0x793d:
				// request to obtain complete information about an account. (by id)
				if( RFIFOREST(fd) < 6 )
					return 0;
				{
					const struct mmo_account *ac = account_load_num(RFIFOL(fd,2));
					memset(WFIFOP(fd,0), 0, 120);
					WFIFOW(fd, 0) = 0x793e;
					WFIFOW(fd, 2) = 1;
					WFIFOL(fd, 4) = RFIFOL(fd,2);
					if(ac)
					{
						WFIFOW(fd, 2) = 0;
						//WFIFOL(fd, 4) = ac->account_id;
						WFIFOB(fd, 8) = isGM(ac->account_id);
						memcpy(WFIFOP(fd, 9), ac->userid, 24);
						WFIFOB(fd,33) = sex_str2num(ac->sex);
						WFIFOL(fd,34) = ac->logincount;
						WFIFOW(fd,38) = ac->state;
						memcpy(WFIFOP(fd,40), ac->lastip, 16);
						memcpy(WFIFOP(fd,56), ac->lastlogin, 24);
						memcpy(WFIFOP(fd,80), ac->mail, 40);
					}
					WFIFOSET(fd,120);
					RFIFOSKIP(fd,6);
				}
				break;

			default:
				printf("parse_admin: unknown packet 0x%04x disconnect session #%d\n", RFIFOW(fd,0), fd);
#ifdef DUMP_UNKNOWN_PACKET
				hex_dump(stdout, RFIFOP(fd,0), RFIFOREST(fd));
				printf("\n");
#endif
				close(fd);
				session[fd]->eof=1;
				return 0;
		}
	}

	return 0;
}

/*==========================================
 * ログインサーバのソケットデストラクタ
 *------------------------------------------
 */
static int parse_login_disconnect(int fd)
{
	int i;

	for( i = 0; i < MAX_CHAR_SERVERS; i++ )
	{
		if(server_fd[i] == fd)
			server_fd[i] = -1;
	}
	close(fd);
	delete_session(fd);

	return 0;
}

/*==========================================
 * ログインサーバのパケット解析
 *------------------------------------------
 */
int parse_login(int fd)
{
	struct login_session_data *sd;

	if( session[fd]->session_data == NULL )
		session[fd]->session_data = aCalloc(1,sizeof(struct login_session_data));
	sd = (struct login_session_data *)session[fd]->session_data;

	while( RFIFOREST(fd) >= 2 )
	{
		int cmd = RFIFOW(fd,0);
		switch(cmd)
		{
			case 0x64:
			case 0x01dd:
			case 0x01fa:
			case 0x027c:
			case 0x0277:
			case 0x02b0:
				printf("parse_login : session #%d %3ld 0x%04x %-24s\n",fd,(long)RFIFOREST(fd),cmd,(char*)RFIFOP(fd,6));
				break;
			case 0x0825:
				printf("parse_login : session #%d %3ld 0x%04x %-24s\n",fd,(long)RFIFOREST(fd),cmd,(char*)RFIFOP(fd,9));
				break;
			default:
				if( cmd < 0x7530 )
					printf("parse_login : session #%d %3ld 0x%04x\n",fd,(long)RFIFOREST(fd),cmd);
				break;
		}

		switch(cmd)
		{
		case 0x200:		// クライアントでaccountオプション使用時の謎パケットへの対応
			if( RFIFOREST(fd) < 26 )
				return 0;
			RFIFOSKIP(fd,26);
			break;
		case 0x204:		// 2004-06-22暗号化ragexe対応
			if( RFIFOREST(fd) < 18 )
				return 0;
			RFIFOSKIP(fd,18);
			break;
		case 0x258:		// 2005-12-14 nProtect関係 Part 1
			memset(WFIFOP(fd,0),0,18);
			WFIFOW(fd,0)=0x0227;
			WFIFOSET(fd,18);
			RFIFOSKIP(fd,2);
			break;
		case 0x228:		// 2005-12-14 nProtect関係 Part 2
			if( RFIFOREST(fd) < 18 )
				return 0;
			WFIFOW(fd,0)=0x0259;
			WFIFOB(fd,2)=1;
			WFIFOSET(fd,3);
			RFIFOSKIP(fd,18);
			break;

		case 0x0064:	// クライアントログイン要求
		case 0x01dd:	// 暗号化ログイン要求
		case 0x01fa:	// 暗号化ログイン要求（langtype=5）
		case 0x0277:	// クライアントログイン要求？
		case 0x027c:	// 暗号化ログイン要求
		case 0x02b0:	// クライアントログイン要求（langtype=0）
		case 0x0825:	// シングルサインオンログイン要求（langtype=0）
		{
			int result = -1;
			bool enc_flag;
			int version;
			int clienttype;

			switch(cmd)
			{
				case 0x0064:
					if(RFIFOREST(fd) < 55)
						return 0;
					break;
				case 0x01dd:
					if(RFIFOREST(fd) < 47)
						return 0;
					break;
				case 0x01fa:
					if(RFIFOREST(fd) < 48)
						return 0;
					break;
				case 0x0277:
					if(RFIFOREST(fd) < 84)
						return 0;
					break;
				case 0x027c:
					if(RFIFOREST(fd) < 60)
						return 0;
					break;
				case 0x02b0:
					if(RFIFOREST(fd) < 85)
						return 0;
					break;
				case 0x0825:
					if(RFIFOREST(fd) < 4 || RFIFOREST(fd) < RFIFOW(fd, 2))
						return 0;
					break;
			}

			enc_flag = (cmd == 0x1dd || cmd == 0x1fa || cmd == 0x27c);

			if(cmd == 0x0825) {
				char *token = (char *)RFIFOP(fd,0x5c);
				size_t len = RFIFOREST(fd) - 0x5c;

				version = RFIFOL(fd,4);
				clienttype = RFIFOB(fd,8);
				memcpy(sd->userid,RFIFOP(fd,9),24);
				sd->userid[23] = '\0';

				if(len > 0 && len < 24) {
					memcpy(sd->pass,token,len+1);
					sd->pass[len+1] = '\0';
				}
			} else {
				version = RFIFOL(fd,2);
				memcpy(sd->userid,RFIFOP(fd,6),24);
				sd->userid[23] = '\0';

				if(enc_flag)
				{
					memcpy(sd->pass, RFIFOP(fd,30), 16);
					sd->pass[16] = '\0';	// binary data
					clienttype = RFIFOB(fd,46);
				}
				else
				{
					memcpy(sd->pass, RFIFOP(fd,30), 24);
					sd->pass[23] = '\0';
					clienttype = RFIFOB(fd,54);
				}
			}

			{
				unsigned char *p = (unsigned char *)&session[fd]->client_addr.sin_addr;
				sprintf(sd->lastip,"%d.%d.%d.%d",p[0],p[1],p[2],p[3]);
				loginlog_log("client connection request %s from %s", sd->userid, sd->lastip);
			}

			if( config.login_version > 0 && config.login_version != version )	// 規定外のバージョンからの接続を拒否
				result = 5;
			if( config.login_type > 0 && config.login_type != clienttype )	// 規定外のタイプからの接続を拒否
				result = 5;
			if( strlen(sd->userid) < 4 )	// IDが4字未満を拒否
				result = 3;
			if( !enc_flag && strlen(sd->pass) < 4 ) // 暗号化PASSはmd5符号なので \0 が含まれる可能性有り
				result = 3;
#ifdef PASSWORDENC
			sd->passwdenc = (enc_flag)? PASSWORDENC: 0;
#else
			sd->passwdenc = 0;
#endif
			if( result == -1 )
				result = mmo_auth(sd);
			if( result == -1 )
				login_authok(sd,fd);
			else
			{
#if PACKETVER < 20100615
				memset(WFIFOP(fd,0),0,23);	// TODO: BlockDate
				WFIFOW(fd,0) = 0x6a;
				WFIFOB(fd,2) = result;
				WFIFOSET(fd,23);
#else
				memset(WFIFOP(fd,0),0,26);	// TODO: BlockDate
				WFIFOW(fd,0) = 0x83e;
				WFIFOL(fd,2) = result;
				WFIFOSET(fd,26);
#endif
			}
			RFIFOSKIP(fd,RFIFOREST(fd));
		}
		break;

		case 0x01db:	// 暗号化Key送信要求
		case 0x272d:	// Charの暗号化ログイン要求
		case 0x791a:	// 管理パケットで暗号化key要求
		{
			int i;

			RFIFOSKIP(fd, 2);
			if(sd->md5keylen)
			{
				printf("login: illegal md5key request.");
				close(fd);
				session[fd]->eof=1;
				return 0;
			}
			// 暗号化用のチャレンジ生成
			sd->md5keylen = atn_rand()%(sizeof(sd->md5key)/4)+(sizeof(sd->md5key)-sizeof(sd->md5key)/4);
			for( i = 0; i < sd->md5keylen; i++ )
				sd->md5key[i] = atn_rand()%255+1;
			sd->md5key[i] = 0;

			WFIFOW(fd,0)= (cmd == 0x272d) ? 0x272e : 0x01dc;
			WFIFOW(fd,2)=4+sd->md5keylen;
			memcpy(WFIFOP(fd,4),sd->md5key,sd->md5keylen);
			WFIFOSET(fd,WFIFOW(fd,2));
			break;
		}

		case 0x2710:	// Charサーバー接続要求
		case 0x272f:	// Charサーバー接続要求(暗号化ログイン)
			if( RFIFOREST(fd) < 84 )
				break;
			if( config.login_sport != 0 && config.login_port != config.login_sport && session[fd]->server_port != config.login_sport )
			{
				printf("server login failed: connected port %d\n", session[fd]->server_port);
				RFIFOSKIP(fd,84);
				session[fd]->eof = 1;
				break;
			}

			{
				unsigned char *p = (unsigned char *)&session[fd]->client_addr.sin_addr;
				sprintf(sd->lastip,"%d.%d.%d.%d",p[0],p[1],p[2],p[3]);
				loginlog_log(
					"server connection request %s @ %d.%d.%d.%d:%d (%s)",
					RFIFOP(fd,60),RFIFOB(fd,54),RFIFOB(fd,55),RFIFOB(fd,56),RFIFOB(fd,57),
					RFIFOW(fd,58),sd->lastip);
			}
			memcpy( sd->userid, RFIFOP(fd, 2), 24 );
			memcpy( sd->pass, RFIFOP(fd, 26), sd->md5keylen ? 16 : 24 );
			sd->passwdenc = sd->md5keylen ? RFIFOL(fd,46) : 0;

			if( mmo_auth(sd) == -1 && sd->sex == 'S' && sd->account_id < MAX_CHAR_SERVERS && server_fd[sd->account_id] < 0 )
			{
				server[sd->account_id].ip=RFIFOL(fd,54);
				server[sd->account_id].port=RFIFOW(fd,58);
				memcpy(server[sd->account_id].name,RFIFOP(fd,60),20);
				server[sd->account_id].users=0;
				server[sd->account_id].maintenance=RFIFOW(fd,80);
				server[sd->account_id].new_=RFIFOW(fd,82);
				server_fd[sd->account_id]=fd;
				WFIFOW(fd,0)=0x2711;
				WFIFOB(fd,2)=0;
				WFIFOSET(fd,3);
				session[fd]->func_parse    = parse_fromchar;
				session[fd]->func_destruct = parse_char_disconnect;
				realloc_fifo(fd, RFIFOSIZE_SERVERLINK, WFIFOSIZE_SERVERLINK);
				session[fd]->auth = -1; // 認証終了を socket.c に伝える
			}
			else
			{
				WFIFOW(fd,0)=0x2711;
				WFIFOB(fd,2)=3;
				WFIFOSET(fd,3);
			}
			RFIFOSKIP(fd,84);
			break;

		case 0x7530:	// Auriga情報取得
			WFIFOW(fd,0)=0x7531;
			WFIFOB(fd,2)=AURIGA_MAJOR_VERSION;
			WFIFOB(fd,3)=AURIGA_MINOR_VERSION;
			WFIFOW(fd,4)=AURIGA_REVISION;
			WFIFOB(fd,6)=AURIGA_RELEASE_FLAG;
			WFIFOB(fd,7)=AURIGA_OFFICIAL_FLAG;
			WFIFOB(fd,8)=AURIGA_SERVER_LOGIN;
			WFIFOW(fd,9)=get_current_version();
			WFIFOSET(fd,11);
			RFIFOSKIP(fd,2);
			break;
		case 0x7532:	// 接続の切断(defaultと処理は一緒だが明示的にするため)
			RFIFOSKIP(fd,2);
			close(fd);
			session[fd]->eof=1;
			return 0;

		case 0x7918:	// 管理モードログイン
			if( RFIFOREST(fd) < 4 )
				break;
			if( config.ristrict_admin_local == true )
			{
				unsigned long ip = (unsigned long)session[fd]->client_addr.sin_addr.s_addr;
				if(ip != host2ip("127.0.0.1", NULL))
				{
					// ローカルホスト以外は失敗
					printf("parse_admin failed: source ip address is not localhost: %lu\n", ip);
					break;
				}
			}
			if( RFIFOREST(fd) < 6 || RFIFOREST(fd)<RFIFOW(fd,2) || RFIFOREST(fd) < ((RFIFOW(fd,4) == 0) ? 30 : 22) )
				break;
			if(RFIFOW(fd,2) != ((RFIFOW(fd,4) == 0) ? 30 : 22) )
			{
				printf("server login failed: invalid length %d\n", (int)RFIFOW(fd,2));
				session[fd]->eof = 1;
				break;
			}
			if( config.login_sport != 0 && config.login_port != config.login_sport && session[fd]->server_port != config.login_sport )
			{
				printf("server login failed: connected port %d\n", session[fd]->server_port);
				RFIFOSKIP(fd,RFIFOW(fd,2));
				session[fd]->eof = 1;
				break;
			}
			WFIFOW(fd,0)=0x7919;
			WFIFOB(fd,2)=1;

			if(RFIFOW(fd,4) == 0)
			{	// プレーン
				if( strcmp(RFIFOP(fd,6),config.ladmin_pass) == 0 )
				{
					WFIFOB(fd,2)=0;
					session[fd]->func_parse=parse_admin;
					session[fd]->func_destruct = parse_admin_disconnect;
					session[fd]->auth = -1; // 認証終了を socket.c に伝える
				}
			}
			else
			{					// 暗号化
				struct login_session_data *ld = (struct login_session_data *)session[fd]->session_data;
				if(!ld)
					printf("login: md5key not created for admin login\n");
				else
				{
					char md5str[192]="",md5bin[32];
					if(RFIFOW(fd,4)==1){
						strncpy(md5str,ld->md5key,sizeof(md5str)-sizeof(config.ladmin_pass)-1);
						strcat(md5str,config.ladmin_pass);
					}else if(RFIFOW(fd,4)==2){
						strncpy(md5str,config.ladmin_pass,sizeof(md5str)-sizeof(ld->md5key)-1);
						strcat(md5str,ld->md5key);
					};
					MD5_String2binary(md5str,md5bin);
					if(memcmp(md5bin,RFIFOP(fd,6),16)==0){
						WFIFOB(fd,2)=0;
						session[fd]->func_parse=parse_admin;
						session[fd]->func_destruct = parse_admin_disconnect;
						session[fd]->auth = -1; // 認証終了を socket.c に伝える
					}
				}
			}
			WFIFOSET(fd,3);
			RFIFOSKIP(fd,RFIFOW(fd,2));
			break;

		default:
			printf("parse_login: unknown packet 0x%04x disconnect session #%d\n", RFIFOW(fd,0), fd);
#ifdef DUMP_UNKNOWN_PACKET
			hex_dump(stdout, RFIFOP(fd,0), RFIFOREST(fd));
			printf("\n");
#endif
			close(fd);
			session[fd]->eof=1;
			return 0;
		}
	}

	return 0;
}

/*==========================================
 * 設定ファイルのデフォルトセット
 *------------------------------------------
 */
static void login_config_set_defaultvalue(void)
{
	config.new_account_flag = false;
	config.detect_multiple_login = true;
	config.ristrict_admin_local = true;
	config.login_port = 6900;
	config.login_sport = 0;
	config.login_sip = 0;
	strncpy(config.login_shost,"",sizeof(config.login_shost));
	strncpy(config.admin_pass,"",sizeof(config.admin_pass));
	strncpy(config.ladmin_pass,"",sizeof(config.ladmin_pass));
	strncpy(config.login_conf_filename,"conf/login_auriga.conf",sizeof(config.login_conf_filename));
	strncpy(config.GM_account_filename,"conf/GM_account.txt",sizeof(config.GM_account_filename));
	config.login_autosave_time = 600;
	config.login_version = 0;
	config.login_type = 0;

	return;
}

/*==========================================
 * 設定ファイルの読み込み
 *------------------------------------------
 */
static void login_config_read(const char *cfgName)
{
	char line[1024], w1[1024], w2[1024];
	FILE *fp;

	fp = fopen(cfgName, "r");
	if(fp == NULL)
	{
		printf("login_config_read: open [%s] failed !\n", cfgName);
		return;
	}

	while( fgets(line, sizeof(line) - 1, fp) )
	{
		if( line[0] == '\0' || line[0] == '\r' || line[0] == '\n' )
			continue;
		if( line[0] == '/' && line[1] == '/' )
			continue;
		if( sscanf(line, "%1023[^:]: %1023[^\r\n]", w1, w2) != 2 )
			continue;

		if( strcmpi(w1, "admin_pass") == 0 )
		{
			strncpy(config.admin_pass, w2, sizeof(config.admin_pass) -1);
			config.admin_pass[sizeof(config.admin_pass) - 1] = '\0';
		}
		else if( strcmpi(w1, "new_account") == 0 )
			config.new_account_flag = ( atoi(w2) != 0 )? true : false;
		else if( strcmpi(w1, "gm_account_filename") == 0 )
		{
			strncpy(config.GM_account_filename, w2, sizeof(config.GM_account_filename) - 1);
			config.GM_account_filename[sizeof(config.GM_account_filename) - 1] = '\0';
		}
		else if (strcmpi(w1, "login_port") == 0)
		{
			int n = atoi(w2);
			if( n < 1024 || n > 65535 )
			{
				printf("Warning: Invalid login_port value: %d. Set to 6900 (default).\n", n);
				config.login_port = 6900; // default
			}
			else
				config.login_port = (unsigned short)n;
		}
		else if( strcmpi(w1, "listen_ip") == 0 )
		{
			unsigned long ip_result = host2ip(w2, NULL);
			if (ip_result == INADDR_NONE) // not always -1
				printf("login_config_read: Invalid listen_ip value: %s.\n", w2);
			else
				listen_ip = ip_result;
		}
		else if( strcmpi(w1, "login_sip") == 0 )
		{
			memcpy(config.login_shost, w2, sizeof(config.login_shost));
			config.login_shost[sizeof(config.login_shost)-1] = '\0';	// force \0 terminal
		}
		else if( strcmpi(w1, "login_sport") == 0 )
		{
			int n = atoi(w2);
			if( n < 1024 || n > 65535 )
			{
				printf("Warning: Invalid login_sport value: %d. Set to 0 (default=disable).\n", n);
				config.login_sport = 0; // default
			}
			else
				config.login_sport = (unsigned short)n;
		}
		else if( strcmpi(w1, "login_version") == 0 )
			config.login_version = atoi(w2);
		else if( strcmpi(w1, "login_type") == 0 )
			config.login_type = atoi(w2);
		else if( strcmpi(w1, "autosave_time") == 0 )
			config.login_autosave_time = atoi(w2);
		else if( strcmpi(w1, "ladmin_pass") == 0 )
		{
			strncpy(config.ladmin_pass, w2, sizeof(config.ladmin_pass) -1);
			config.ladmin_pass[sizeof(config.ladmin_pass) - 1] = '\0';
		}
		else if( strcmpi(w1, "detect_multiple_login") == 0 )
			config.detect_multiple_login = ( atoi(w2) != 0)? true : false;
		else if( strcmpi(w1, "ristrict_admin_local") == 0 )
			config.ristrict_admin_local = ( atoi(w2) != 0 )? true : false;
		else if( strcmpi(w1, "import") == 0 )
			login_config_read(w2);
		else
		{
			if(loginlog_config_read(w1, w2))
				continue;
			if(login_config_read_sub(w1, w2))
				continue;
			if(login_httpd_config_read(w1, w2))
				continue;
		}
	}
	fclose(fp);

	return;
}

/*==========================================
 * 設定ファイルの警告表示
 *------------------------------------------
 */
static void display_conf_warnings(void)
{
	if( config.login_autosave_time < 10 )
	{
		printf("Warning: Invalid login_autosave_time value: %d. Set to 600 (default).\n", config.login_autosave_time);
		config.login_autosave_time = 600;
	}
	if( config.login_version < 0 && config.login_version != -1 ) // conserv -1 for old configuration
	{
		printf("Warning: Invalid login_version value %d. Set to 0 (default=disable).\n", config.login_version);
		config.login_version = 0;
	}
	if( config.login_type < 0 && config.login_type != -1 ) // conserv -1 for old configuration
	{
		printf("Warning: Invalid login_type value %d. Set to 0 (default=disable).\n", config.login_type);
		config.login_type = 0;
	}
	if( config.new_account_flag == true )
	{
		if( config.admin_pass[0] == '\0' )
		{
			printf("Information: admin_pass is not defined (void)\n");
			printf("-> creation of accounts is possible with _F and _M without password.\n");
		}
		else if( strcmp(config.admin_pass, "admin") == 0 )
			printf("SECURITY warning: using default admin_pass ('%s').\n", config.admin_pass);
	}

	if( config.ladmin_pass[0] == '\0' )
		printf("SECURITY warning: ladmin_pass is not defined (void).\n");
	else if( strcmp(config.ladmin_pass, "admin") == 0 )
		printf("SECURITY warning: using default ladmin_pass ('%s').\n", config.ladmin_pass);

	return;
}

/*==========================================
 * 同期
 *------------------------------------------
 */
static int login_sync_timer(int tid, unsigned int tick, int id, void *data)
{
	login_sync();

	return 0;
}

/*==========================================
 * 終了直前処理
 *------------------------------------------
 */
void do_pre_final(void)
{
	// nothing to do
	return;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
static int gm_account_db_final(void *key, void *data, va_list ap)
{
	struct gm_account *p = (struct gm_account *)data;

	aFree(p);

	return 0;
}

void do_final(void)
{
	int i;

	login_sync();
	login_final();

	if(gm_account_db) {
		numdb_final(gm_account_db, gm_account_db_final);
		gm_account_db = NULL;
	}
	exit_dbn();

	for( i = 0; i < MAX_CHAR_SERVERS; i++ )
	{
		int fd;
		if( ( fd = server_fd[i] ) > 0 )
			delete_session(fd);
	}
	delete_session(login_fd);
	if( config.login_sport != 0 && config.login_port != config.login_sport )
		delete_session(login_sfd);
	do_final_timer();

	return;
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
int do_init(int argc,char **argv)
{
	int i;
	unsigned int tick = gettick();

	printf("Auriga Login Server [%s] v%d.%d.%d version %04d\n",
#ifdef TXT_ONLY
		"TXT",
#else
		"SQL",
#endif
		AURIGA_MAJOR_VERSION, AURIGA_MINOR_VERSION, AURIGA_REVISION,
		get_current_version()
	);

	login_config_set_defaultvalue();
	login_config_set_defaultvalue_sub();
	for( i = 1; i < argc - 1; i += 2 )
	{
		if(strcmp(argv[i], "--login_config") == 0 || strcmp(argv[i], "--login-config") == 0)
		{
			strncpy(config.login_conf_filename, argv[i+1], sizeof(config.login_conf_filename));
			config.login_conf_filename[sizeof(config.login_conf_filename)-1] = '\0';
		}
	}

	login_config_read(config.login_conf_filename);
	display_conf_warnings();
	display_conf_warnings2();

	if(config.login_shost[0])
		config.login_sip = host2ip(config.login_shost, "Login server sIP address");

	for( i = 0 ; i < AUTH_FIFO_SIZE; i++ )
		auth_fifo[i].delflag = true;

	for( i = 0; i < MAX_CHAR_SERVERS; i++ )
		server_fd[i] = -1;

	login_fd = make_listen_port(config.login_port, listen_ip);
	if(config.login_sport != 0 && config.login_port != config.login_sport)
		login_sfd = make_listen_port(config.login_sport, config.login_sip);
	if(login_init() == false) {
		printf("FATAL ERROR: login_init() failed !!\n");
		exit(1);
	}

	read_gm_account();
	set_defaultparse(parse_login);
	set_sock_destruct(parse_login_disconnect);

	add_timer_func_list(login_sync_timer);
	add_timer_interval(tick+10*1000,login_sync_timer,0,NULL,config.login_autosave_time*1000);

	// for httpd support
	login_httpd_init();

	return 0;
}
