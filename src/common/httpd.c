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

#ifndef WINDOWS
#	include <unistd.h>
#	include <sys/time.h>
#	include <sys/wait.h>
#else
#	include <windows.h>
#endif

#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "mmo.h"
#include "version.h"
#include "db.h"
#include "httpd.h"
#include "socket.h"
#include "malloc.h"
#include "timer.h"
#include "md5calc.h"
#include "utils.h"


#define NONCE_LOG_SIZE				256		// Digest �F�؂� nonce ��ۑ��ł����
#define HTTPD_CGI_KILL_SIZE			128		// cgi �̒��f�p�̃f�[�^��ۑ��ł����
#define HTTPD_CGI_KILL_INVERVAL		250		// cgi �̒��f�����̃`�F�b�N���s���Ԋu(ms)


typedef void (*HttpdFunc)(struct httpd_session_data*,const char*);

static const char configfile[]="./conf/httpd.conf";	// ���ʃR���t�B�O

static char logfile[1024]="./log/httpd.log";	// ���O�t�@�C����
void httpd_set_logfile( const char *str ) { atn_strlcpy( logfile, str, sizeof(logfile) ); }

static int log_no_flush = 0;	// ���O���t���b�V�����Ȃ����ǂ���

static int tz = -1;	// �^�C���]�[��

static int auth_digest_period = 600*1000;	// Digest �F�؂ł� nonce �L������
void httpd_set_auth_digest_period( int i ) { auth_digest_period = i; }

static int max_persist_requests = 32;	// �����ʐM�ł̍ő僊�N�G�X�g��
void httpd_set_max_persist_requests( int i ) { max_persist_requests = i; }

static int request_timeout[] = { 2500, 60*1000 };	// �^�C���A�E�g(�ŏ��A����)
void httpd_set_request_timeout( int idx, int t ) { request_timeout[idx] = t; }

static char document_root[256]="./httpd/";	// �h�L�������g���[�g
void httpd_set_document_root( const char *str ) { atn_strlcpy( document_root, str, sizeof(document_root) ); }

static int bigfile_threshold = 256*1024;	// ����t�@�C���]�����[�h�ɓ���臒l
static int bigfile_splitsize = 256*1024;	// ����t�@�C���]�����[�h�� FIFO �T�C�Y(128KB�ȏ�)

static int max_uri_length = 255;	// URI �̒����𐧌�

static const char servername[] = "Auriga httpd";

static int server_max_requests_per_second = 10;		// �S�̂̕b�Ԃ̃��N�G�X�g������
static int server_max_requests_period = 5000;		// �S�̂̃��N�G�X�g�������̃`�F�b�N�Ԋu
static int server_max_requests_count = 0;
static unsigned int server_max_requests_tick = 0;


static int httpd_cgi_enable = 1;				// �O�� CGI �𗘗p����
static char httpd_cgi_temp_dir[256] = "./log/";	// CGI �̃e���|�����f�B���N�g��
static int httpd_cgi_timeout = 5000;			// CGI �^�C���A�E�g����(ms)
static int httpd_cgi_kill_timeout = 1000;		// CGI ���f�^�C���A�E�g����(ms)
static int httpd_max_cgi_process = 3;			// CGI �������s�\��
static char httpd_cgi_ext_list[256]=".cgi .exe .pl .php .rb ";	// CGI �Ƃ���g���q
static char httpd_cgi_server_name[256]="localhost";	// CGI �� SERVER_NAME �Ƃ��ēn���z�X�g��
//static char cgi_logfile[1024]="./log/httpd.log";	// CGI ���O�t�@�C����
//static FILE* cgi_logfp = NULL;

static HTTPD_AUTH_FUNC auth_func[8];	// �F�؊֐��̊֐��|�C���^
void httpd_set_auth_func( int func_id, HTTPD_AUTH_FUNC func ) { auth_func[func_id]=func; }

static int httpd_log_format = 1;	// ���O�t�H�[�}�b�g
static FILE *logfp=NULL;

static const char *weekdaymsg[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
static const char *monthmsg[] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };


enum HTTPD_STATUS {
	HTTPD_REQUEST_WAIT = 0,		// ���N�G�X�g�҂�
	HTTPD_REQUEST_WAIT_POST,	// ���N�G�X�g�҂�(post)
	HTTPD_REQUEST_OK,			// ���N�G�X�g���ߊ���
	HTTPD_SEND_HEADER,			// �w�b�_���M����
	HTTPD_SENDING_BIGFILE,		// ����t�@�C�����M��
	HTTPD_WAITING_CGI,			// cgi ���������҂����
	HTTPD_WAITING_SEND,			// �f�[�^�����M���I���܂ő҂��Ă�����
};


enum httpd_enum {
	HTTPD_ACCESS_ALWAYS      = 0,

	HTTPD_ACCESS_AUTH_NONE	 = 0,
	HTTPD_ACCESS_AUTH_BASIC	 = 1,
	HTTPD_ACCESS_AUTH_DIGEST = 2,
	HTTPD_ACCESS_AUTH_MASK	 = 3,

	HTTPD_ACCESS_IP_NONE	 = 0,
	HTTPD_ACCESS_IP_ALLOW	 = 4,
	HTTPD_ACCESS_IP_DENY	 = 8,
	HTTPD_ACCESS_IP_MUTUAL	 = 12,
	HTTPD_ACCESS_IP_MASK	 = 12,

	HTTPD_ACCESS_SAT_ANY	 = 16,
	HTTPD_ACCESS_SAT_ALL	 = 0,
	HTTPD_ACCESS_SAT_MASK	 = 16,

	HTTPD_USER_PASSWD_PLAIN  = 0,
	HTTPD_USER_PASSWD_MD5	 = 1,
	HTTPD_USER_PASSWD_DIGEST = 2,
	HTTPD_USER_PASSWD_MASK	 = 3,

	HTTPD_RESHEAD_LASTMOD	 = 1,
	HTTPD_RESHEAD_ACCRANGE	 = 2,

	HTTPD_PRECOND_NONE       = 0,
	HTTPD_PRECOND_IFMOD      = 1,
	HTTPD_PRECOND_IFUNMOD    = 2,
	HTTPD_PRECOND_IFRANGE    = 4,
};

// ���[�U�[�F�ؗp�̍\����
struct httpd_access_user {
	int type;
	unsigned char name[32];
	unsigned char passwd[36];
};

// �A�N�Z�X����f�[�^�̍\����
struct httpd_access {
	unsigned char url[256];
	int type;
	size_t urllen;

	int dip_count, aip_count, dip_max, aip_max;
	unsigned long *dip, *aip;

	int auth_func_id;
	unsigned char realm[256], privkey[32];
	int user_count, user_max;
	struct httpd_access_user *user;

	char cgi_ext_list[sizeof(httpd_cgi_ext_list)];
};
static int htaccess_count=0, htaccess_max=0;
static struct httpd_access ** htaccess=NULL;

// Digest �F�؂� nonce-count ���O�p�\����
struct httpd_auth_nonce {
	unsigned char nonce[48];
	unsigned nc : 31;
	unsigned access_flag: 1;
};
static struct httpd_auth_nonce nonce_log[NONCE_LOG_SIZE];
static int nonce_log_pos = 0;

// cgi �̃v���O�����̏I���p
struct httpd_cgi_kill {
	int state;
	unsigned int tick;
#ifdef WINDOWS
	HANDLE hProcess;
	DWORD dwProcessID;
#else
	pid_t pid;
#endif
};
#ifndef NO_HTTPD_CGI
static struct httpd_cgi_kill httpd_cgi_kill_list[HTTPD_CGI_KILL_SIZE];
static int httpd_cgi_kill_size;
int httpd_page_external_cgi_abort_timer( int tid, unsigned int tick, int id, void *data);
int httpd_get_external_cgi_process_count(void);
#endif

void httpd_page_external_cgi_disconnect( struct httpd_session_data* );
void httpd_page_external_cgi_final(void);


// ==========================================
// �^�C���]�[���ݒ�
// ------------------------------------------
void httpd_set_timezone( int tz3 )
{
	// �^�C���]�[�������߂�
	int tz2;
	time_t time_temp = time(&time_temp);
	time_t time_local = mktime(localtime(&time_temp));
	time_t time_global = mktime(gmtime(&time_temp));

	tz2 = (int)(time_local - time_global) / (-60);

	tz = tz3;
	if( tz==-1 )
		tz=tz2;
	else if( tz!=tz2 )
		printf("*notice* : user defined timezone[%d(%d)] != system timezone[%d(%d)]\n", -tz/60, tz, -tz2/60, tz2);
}

// ==========================================
// �A�N�Z�X���O�̓f���o��
// ------------------------------------------
void httpd_log( struct httpd_session_data *sd, int status, int len )
{
	char timestr[256], lenstr[16];
	unsigned char *ip;
	static const char sign[]={'-','+'};

	// ���O�t�@�C�����J��
	if( !logfp && (logfp = fopen(logfile, "a") ) == NULL )
	{
		printf("*WARNING* : can't open log file [%s]\n", logfile);
		return;
	}

	// ���ԕ���������߂�
	{
		size_t len;
		time_t time_;
		time(&time_);
        len = strftime(timestr,sizeof(timestr),"%d/%b/%Y:%H:%M:%S",localtime(&time_) );
        snprintf(timestr+len, sizeof(timestr) - (size_t)len, " %c%02d%02d", sign[(tz<0)?1:0], abs(tz)/60, abs(tz)%60 );
	}

	ip = (unsigned char*) &session[sd->fd]->client_addr.sin_addr;

	// �T�C�Y
	if( len<0 )
	{
		lenstr[0]='-';
		lenstr[1]='\0';
	}
	else
	{
		sprintf(lenstr,"%d",len );
	}

	// ���O���o��
	if( httpd_log_format )
	{
		// combined log
		fprintf( logfp,"%d.%d.%d.%d - %s [%s] \"%s\" %d %s \"%s\" \"%s\"" NEWLINE,
			ip[0],ip[1],ip[2],ip[3], ((*sd->user)? (char*)sd->user: "-") ,
			timestr, sd->request_line, status, lenstr,
			(( sd->referer && *sd->referer )? (char*)sd->referer: "-"),
			(( sd->user_agent && *sd->user_agent )? (char*)sd->user_agent: "-") );
	}
	else
	{
		// common log
		fprintf( logfp,"%d.%d.%d.%d - %s [%s] \"%s\" %d %s" NEWLINE,
			ip[0],ip[1],ip[2],ip[3], ((*sd->user)? (char*)sd->user: "-") ,
			timestr, sd->request_line, status, lenstr );
	}

	// ���O�̃t���b�V��
	if( !log_no_flush )
	{
		// ���� close ���Ȃ��� logrotate �Ƃ������܂������Ȃ��C������H
		fclose( logfp );
		logfp = NULL;
		// fflush( logfp );
	}
}

// httpd �ɓ����Ă���y�[�W�ƁA�Ăяo���R�[���o�b�N�֐��̈ꗗ
static struct dbt* httpd_files = NULL;

// ==========================================
// httpd_files �̊J������
// ------------------------------------------
static int httpd_db_final(void *key,void *data,va_list ap)
{
	char *url = (char *)key;

	aFree(url);

	return 0;
}

// ==========================================
// httpd �I������
// ------------------------------------------
static void do_final_httpd(void)
{
	int i;

	db_final(httpd_files,httpd_db_final);

	httpd_page_external_cgi_final();

	for( i=0; i<htaccess_count; i++ )
	{
		if(htaccess[i]->user) aFree( htaccess[i]->user );
		if(htaccess[i]->aip)  aFree( htaccess[i]->aip );
		if(htaccess[i]->dip)  aFree( htaccess[i]->dip );
		aFree( htaccess[i] );
	}
	aFree( htaccess );
	htaccess = NULL;
	htaccess_count = htaccess_max = 0;
}

// ==========================================
// httpd ����������
// ------------------------------------------
void do_init_httpd(void)
{
//	httpd_config_read(configfile);	// �����������̊֌W�ŁAsocket_config_read2() ����Ă΂��

	httpd_files = strdb_init(0);
	httpd_pages( get_socket_ctrl_panel_url(), socket_httpd_page );
	atexit(do_final_httpd);

	server_max_requests_tick = gettick();

#ifndef NO_HTTPD_CGI
	add_timer_func_list( httpd_page_external_cgi_abort_timer );
	add_timer_interval( gettick()+HTTPD_CGI_KILL_INVERVAL, httpd_page_external_cgi_abort_timer, 0, NULL, HTTPD_CGI_KILL_INVERVAL );
#endif
}

// ==========================================
// httpd �Ƀy�[�W��ǉ�
//  for �ȂǂŃy�[�W���������ł���悤�ɁAkey ��strdup()�������̂��g��
// ------------------------------------------
void httpd_pages(const char* url,HttpdFunc httpd_func)
{
	if( !httpd_files )
		return;

	if(strdb_search(httpd_files,url+1)) {
		httpd_erase_pages(url);
	}
	strdb_insert(httpd_files,aStrdup(url+1),httpd_func);
}

// ==========================================
// httpd �̃y�[�W���폜
// ------------------------------------------
static int httpd_erase_pages_sub(void *key,void *data,va_list ap)
{
	char *url = va_arg(ap, char*);

	if( strcmp((char *)key, url) == 0 ) {
		strdb_erase( httpd_files, key );
		aFree( key );
	}
	return 0;
}

void httpd_erase_pages(const char* url)
{
	if( httpd_files )
		strdb_foreach( httpd_files, httpd_erase_pages_sub, url+1);
}

static void(*httpd_default)(struct httpd_session_data* sd,const char* url);

// ==========================================
// �f�t�H���g�̃y�[�W�����֐���ݒ�
// ------------------------------------------
void httpd_default_page(void(*httpd_func)(struct httpd_session_data* sd,const char* url))
{
	httpd_default = httpd_func;
}

// ==========================================
// �X�e�[�^�X�R�[�h�����b�Z�[�W�ɕϊ�
// ------------------------------------------
const char *httpd_get_error( struct httpd_session_data* sd, int* status )
{
	const char* msg;

	// httpd �̃X�e�[�^�X�����߂�
	switch(*status) {
	case 200: msg = "OK";              break;
	case 206: msg = "Partial Content"; break;
	case 304: msg = "Not Modified";    break;
	case 400: msg = "Bad Request";     break;
	case 401: msg = "Unauthorized";    break;
	case 403: msg = "Forbidden";       break;
	case 404: msg = "Not Found";       break;
	case 408: msg = "Request Timedout";         break;
	case 411: msg = "Length Required";          break;
	case 412: msg = "Precondition failed";      break;
	case 413: msg = "Request Entity Too Large"; break;
	case 414: msg = "Request-URI Too Long";     break;
	case 416: msg = "Requested Range Not Satisfiable"; break;
	case 503: msg = "Service Unavailable";      break;
	default:
		*status = 500; msg = "Internal Server Error"; break;
	}
	return msg;
}

// ==========================================
// ���t�̉�͗p�i Date �w�b�_�Ȃǁj
// ------------------------------------------
int httpd_get_date( const char *str, time_t *date )
{
	char wday[8],month[8];
	int mday, year, hour, minute, second;
	int i;
	struct tm t;

	if( sscanf( str, "%3s, %02d %3s %04d %02d:%02d:%02d GMT", wday, &mday, month, &year, &hour, &minute, &second )!=7 &&
	    sscanf( str, "%6s, %02d-%3s-%02d %02d:%02d:%02d GMT", wday, &mday, month, &year, &hour, &minute, &second )!=7 &&
	    sscanf( str, "%3s %3s %2d %02d:%02d:%02d %04d",       wday, month, &mday, &hour, &minute, &second, &year )!=7 )
		return 0;

	for( i=0; i<12; i++ )
	{
		if( strncasecmp( monthmsg[i], month, 3 )==0 )
			break;
	}
	if( i==12 )
		return 0;
	t.tm_mon = i;

	for( i=0; i<7; i++ )
	{
		if( strncasecmp( weekdaymsg[i], wday, 3 )==0 )
			break;
	}
	if( i==7 )
		return 0;
	t.tm_wday  = i;

	t.tm_sec  = second;
	t.tm_min  = minute;
	t.tm_hour = hour;
	t.tm_mday = mday;
	t.tm_year = (year>=1900)? year-1900 : year;
	t.tm_isdst= 0;

	*date = mktime( &t ) - tz*60;

	return 1;
}

// ==========================================
// �G���[�̑��M
// ------------------------------------------
void httpd_send_error(struct httpd_session_data* sd,int status)
{
	const char* msg = httpd_get_error( sd, &status );

	httpd_send(sd,status,"text/plain",(int)strlen(msg),msg);
}

// ==========================================
// ���t�̕�����쐬
// ------------------------------------------
int httpd_make_date( char* dst, time_t date )
{
	const struct tm *t = gmtime( &date );

    return snprintf( dst, 128,
		"%s, %02d %s %04d %02d:%02d:%02d GMT\r\n",
		weekdaymsg[t->tm_wday], t->tm_mday, monthmsg[t->tm_mon], (t->tm_year<1900)? t->tm_year+1900: t->tm_year,
		t->tm_hour, t->tm_min, t->tm_sec );
}

// ==========================================
// ���X�|���X�w�b�_���M
// ------------------------------------------
void httpd_send_head(struct httpd_session_data* sd,int status,const char *content_type,int content_len)
{
    char head[1024];
    int  len = 0;
	const char* msg;

	if(sd->status != HTTPD_REQUEST_OK) return;
	msg = httpd_get_error( sd, &status );

	// �F�؊֘A�̃f�[�^���Ȃ񂩂�������
	if( status==401 && ( !sd->access || !(sd->access->type & HTTPD_ACCESS_AUTH_MASK) ) )
		status = 500;

	if( (status != 200 && status != 304  && status != 401 && status != 412 ) || ++sd->request_count >= max_persist_requests ) {
		// �����ؒf����(status ��200�A304�A401�A412 �ȊO or ���N�G�X�g���E����)
		sd->persist = 0;
	}

    len += snprintf( head + len, sizeof(head) - (size_t)len,
        "HTTP/1.%d %d %s\r\nServer: %s/revision%d\r\n",
        sd->http_ver, status, msg, servername, AURIGA_REVISION );

	if( content_type )	// �R���e���g�^�C�v
	{
        len += snprintf( head + len, sizeof(head) - (size_t)len, "Content-Type: %s\r\n", content_type );
	}

	if( content_len == -1 )		// ������������Ȃ�
	{
		if( status!=304 )
			sd->persist = 0;
	} else {
        len += snprintf(head + len, sizeof(head) - (size_t)len, "Content-Length: %d\r\n", content_len);
	}

	if( status==206 )	// Content-Range �ʒm
	{
        len += snprintf(head + len, sizeof(head) - (size_t)len, "Content-Range: bytes %d-%d/%d\r\n", sd->range_start, sd->range_end, sd->inst_len );
	}

	if( sd->persist==0 )	// ���������ǂ���
	{
        len += snprintf(head + len, sizeof(head) - (size_t)len, "Connection: close\r\n");
	}
	else if( sd->http_ver==0 ) // HTTP/1.0 �Ȃ� Keep-Alive �ʒm
	{
        len += snprintf(head + len, sizeof(head) - (size_t)len, "Connection: Keep-Alive\r\n");
	}

	if( status==401 )	// �F�؂��K�v
	{
		if( (sd->access->type & HTTPD_ACCESS_AUTH_MASK) == HTTPD_ACCESS_AUTH_DIGEST )
		{
			static const char *stale[]={"false","true"};
			char nonce[128];

			// nonce �쐬
			{
				char buf[128];
				int i;
                snprintf( buf, sizeof(buf), "%08x:%s", gettick(), sd->access->privkey );
                snprintf( nonce, sizeof(nonce), "%08x", gettick() );
				MD5_String( buf, nonce+8 );

				for( i=0; nonce_log[ nonce_log_pos ].access_flag && i<NONCE_LOG_SIZE; i++ )
				{
					nonce_log[ nonce_log_pos ].access_flag = 0;
					nonce_log_pos = ( nonce_log_pos + 1 ) % NONCE_LOG_SIZE;
				}

				nonce_log[ nonce_log_pos ].access_flag = 1;
				nonce_log[ nonce_log_pos ].nc = 1;
				strcpy( nonce_log[ nonce_log_pos ].nonce, nonce );
				nonce_log_pos = ( nonce_log_pos + 1 ) % NONCE_LOG_SIZE;
			}
            len += snprintf( head+len, sizeof(head) - (size_t)len,
                "WWW-Authenticate: Digest realm=\"%s\", nonce=\"%s\", algorithm=MD5, qop=\"auth\", stale=%s\r\n",
                sd->access->realm, nonce, stale[sd->auth_digest_stale] );
		}
		else
		{
            len += snprintf( head+len, sizeof(head) - (size_t)len,
                "WWW-Authenticate: Basic realm=\"%s\"\r\n", sd->access->realm );
		}
	}

	if( status==503 )	// Retry-after �ʒm
	{
        len += snprintf( head + len, sizeof(head) - (size_t)len, "Retry-After: %d\r\n", (server_max_requests_period+999)/1000 );
	}

	if( sd->reshead_flag & HTTPD_RESHEAD_ACCRANGE )	// Accept-Ranges �ʒm
	{
        len += snprintf( head + len, sizeof(head) - (size_t)len, "Accept-Ranges: bytes\r\n" );
	}

	if( sd->date && (sd->reshead_flag & HTTPD_RESHEAD_LASTMOD))	// Last-modified �̒ʒm
	{
        len += snprintf( head+len, sizeof(head) - (size_t)len, "Last-Modified: " );
		len += httpd_make_date( head+len, sd->date );
	}

	if( status!=500 )	// Date �̒ʒm
	{
		time_t tmp = time( &tmp );
        len += snprintf( head+len, sizeof(head) - (size_t)len, "Date: " );
		len += httpd_make_date( head+len, tmp );
	}

	httpd_log( sd, status, content_len );	// ���O�ɋL�^

    len += snprintf( head+len, sizeof(head) - (size_t)len, "\r\n" );
	memcpy(WFIFOP(sd->fd,0),head,len);
	WFIFOSET(sd->fd,len);
	sd->status   = HTTPD_SEND_HEADER;
	sd->data_len = content_len;
}

// ==========================================
// �f�[�^���M
// ------------------------------------------
void httpd_send_data(struct httpd_session_data* sd,int content_len,const void *data)
{
	const char* msg = (const char*)data;

	if(sd->status == HTTPD_REQUEST_OK) {
		// �w�b�_�̑��M�Y��Ă���̂ŁA�K���ɕ₤
		httpd_send_head(sd,200,"application/octet-stream",-1);
	} else if(sd->status != HTTPD_SEND_HEADER && sd->status != HTTPD_WAITING_SEND) {
		return;
	}
	sd->data_len -= content_len;

	// ����ȃT�C�Y�̃t�@�C�������M�o����悤�ɕ������đ���
	while(content_len > 0) {
		int send_byte = content_len;
		if(send_byte > 12*1024) send_byte = 12*1024;
		memcpy(WFIFOP(sd->fd,0),msg,send_byte);
		WFIFOSET(sd->fd,send_byte);
		msg += send_byte;
		content_len -= send_byte;
	}
	sd->status = HTTPD_WAITING_SEND;
}

// ==========================================
// �w�b�_�ƃf�[�^�̈ꊇ���M
// ------------------------------------------
void httpd_send(struct httpd_session_data* sd,int status,const char *content_type,int content_len,const void *data)
{
	httpd_send_head(sd,status,content_type,content_len);
	httpd_send_data(sd,content_len,data);
}

// ==========================================
// �ؒf�҂�
// ------------------------------------------
int httpd_disconnect(int fd)
{
	struct httpd_session_data* sd = (struct httpd_session_data*)session[fd]->session_data2;

	// CGI �̒��f
	if( sd->cgi_state )
	{
		sd->cgi_state = 0;
		httpd_page_external_cgi_disconnect( sd );
	}

	return 0;
}

int  httpd_parse_header(struct httpd_session_data* sd);
void httpd_parse_request_ok(struct httpd_session_data *sd);
void httpd_send_bigfile( struct httpd_session_data* sd );
void httpd_page_external_cgi( struct httpd_session_data* sd );

// ==========================================
// httpd �Z�b�V�����̃��Z�b�g
// ------------------------------------------
void httpd_session_reset( struct httpd_session_data* sd )
{
	// �ێ����ׂ����̂̃o�b�N�A�b�v
	int fd       = sd->fd;
	int http_ver = sd->http_ver;
	int persist  = sd->persist;

	// �[���N���A
	memset( sd, 0, sizeof(struct httpd_session_data) );

	// �o�b�N�A�b�v����̕��A
	sd->fd          = fd;
	sd->http_ver    = http_ver;
	sd->persist     = persist;

	// 0 �ȊO�̏����l�ݒ�
	sd->status      = HTTPD_REQUEST_WAIT;
	sd->tick        = gettick();
	sd->range_end   = -1;
}

// ==========================================
// httpd �̃p�P�b�g���
// ------------------------------------------

int httpd_parse(int fd)
{
	struct httpd_session_data *sd = (struct httpd_session_data*)session[fd]->session_data2;

	if(sd == NULL) {
		sd = (struct httpd_session_data*)aCalloc(sizeof(struct httpd_session_data),1);
		httpd_session_reset(sd);
		sd->fd  = fd;
		session[fd]->func_destruct = httpd_disconnect;
		session[fd]->session_data2  = sd;
	}

	// ��x�̃��N�G�X�g�� 32KB �ȏ㑗�M�����Ɛؒf����
	if( RFIFOREST(fd) > 32768 )
	{
		session[fd]->eof = 1;
		return 0;
	}

	switch(sd->status) {
	case HTTPD_REQUEST_WAIT:
		// ���N�G�X�g�҂�
		if(RFIFOREST(fd) > 1024) {
			// ���N�G�X�g����������̂ŁA�G���[��������
			sd->status = HTTPD_REQUEST_OK;
			httpd_send_error(sd,400); // Bad Request
		}
		else if( (int)( gettick() - sd->tick ) > request_timeout[sd->persist] )
		{
			// ���N�G�X�g�Ɏ��Ԃ������肷���Ă���̂ŁA�G���[��������
			sd->status = HTTPD_REQUEST_OK;
			httpd_send_error(sd,408); // Request Timeout
		}
		else if(sd->header_len == RFIFOREST(fd))
		{
			// ��Ԃ��ȑO�Ɠ����Ȃ̂ŁA���N�G�X�g���ĉ�͂���K�v�͖���
			break;
		}
		else
		{
			int limit = (int)RFIFOREST(fd);
			unsigned char *req = RFIFOP(fd,0);

			// �b�ԏ����������̃`�F�b�N
			if( server_max_requests_count >= server_max_requests_per_second*server_max_requests_period/1000 )
			{
				unsigned int tick = gettick();
				if( DIFF_TICK( server_max_requests_tick + server_max_requests_period, tick ) < 0 )
				{
					server_max_requests_count = 0;
					server_max_requests_tick = tick;
				}
				else
				{
					// �T�[�o�[�̏����������z���Ă���
					sd->status = HTTPD_REQUEST_OK;
					httpd_send_error(sd,503); // Service Unavailable
					break;
				}
			}

			// ���N�G�X�g�̉��
			sd->header_len = (int)RFIFOREST(fd);
			do {
				if(*req == '\n' && limit > 0) {
					limit--; req++;
					if(*req == '\r' && limit > 0) { limit--; req++; }
					if(*req == '\n') {
						int status;
						// HTTP�w�b�_�̏I�_��������
						*req   = 0;
						sd->header_len = (int)(req - RFIFOP(fd,0) + 1);
						status = httpd_parse_header(sd);
						if(sd->status == HTTPD_REQUEST_WAIT) {
							sd->status = HTTPD_REQUEST_OK;
							httpd_send_error(sd,status);
						}
						server_max_requests_count++;
						break;
					}
				}
			} while(req++,--limit > 0);
		}
		break;

	case HTTPD_REQUEST_WAIT_POST:
		// POST ���\�b�h�ł̃G���e�B�e�B��M�҂�
		if( (int)( gettick() - sd->tick ) > request_timeout[sd->persist] ) {
			// ���N�G�X�g�Ɏ��Ԃ������肷���Ă���̂ŁA�G���[��������
		} else
		if(RFIFOREST(sd->fd) >= sd->header_len) {
			unsigned char temp = RFIFOB(sd->fd,sd->header_len);
			RFIFOB(sd->fd,sd->header_len) = 0;
			httpd_parse_request_ok(sd);
			RFIFOB(sd->fd,sd->header_len) = temp;
		}
		break;

	case HTTPD_REQUEST_OK:
	case HTTPD_SEND_HEADER:
		// ���N�G�X�g���I������܂܉������M����Ă��Ȃ���ԂȂ̂ŁA
		// �����ؒf
		session[fd]->eof = 1;
		break;

	case HTTPD_SENDING_BIGFILE:
		// ����t�@�C�����M��
		httpd_send_bigfile(sd);
		break;

	case HTTPD_WAITING_CGI:
		// cgi �����I���҂�
		httpd_page_external_cgi(sd);
		break;

	case HTTPD_WAITING_SEND:
		// �f�[�^�̑��M���I���܂őҋ@
		if(session[fd]->wdata_size == session[fd]->wdata_pos) {
			// HTTP/1.0�͎蓮�ؒf
//			if(sd->http_ver == 0) {
			if(sd->persist == 0) {
				session[fd]->eof = 1;
			}
			// RFIFO ���烊�N�G�X�g�f�[�^�̏����ƍ\���̂̏�����
			RFIFOSKIP(fd,sd->header_len);
			httpd_session_reset(sd);
			// printf("httpd_parse: [% 3d] request sended RFIFOREST:%d\n",fd,RFIFOREST(fd));
		}
		break;
	}
	return 0;
}

// ==========================================
// URL �̃f�R�[�h
// ------------------------------------------
int httpd_decode_url( char *url )
{
	int s=0, d=0;

	// url �f�R�[�h
	while( url[s]!='\0' && url[s]!='?' )
	{
		if( url[s]=='%' )
		{
			#define HEX2INT(a) ( ( a>='0' && a<='9' )? a-'0' : (a>='A' && a<='F' )? a-'A'+10 : (a>='a' && a<='f' )? a-'a'+10 : -1 )
			int a1 = HEX2INT(url[s+1]), a2 = HEX2INT(url[s+2]);
			#undef HEX2INT
			if( a1>=2 && a2>=0)	// 0x20?
			{
				s+=3;
				url[ d++ ] = (a1<<4) + a2;
			}
			else if( a1>=0 && a1<2 )	// url �ɐ��䕶�������悤�Ƃ���
			{
				return 0;
			}
			continue;
		}
		else if( url[s]=='+' )
		{
			url[ d++ ]= ' ';
			s++;
			continue;
		}
		url[ d++ ] = url[ s++ ];
	}
	url[d] = '\0';

	// sjis ���Ɛ���ɂ͂����Ȃ����Ƃ�����
	s=d=0;
	while( url[s]!='\0' && url[s]!='?' )
	{
		int c0 = url[s], c1 = url[s+1], c2 = url[s+2], c3 = url[s+3];

		/*
		if( url[s]=='\\' )	// �o�b�N�N�H�[�g���܂܂�Ă���ƒ����ɃG���[
		{
			return 0;
		}
		*/

		// �֎~�����`�F�b�N
		if( url[s]=='|' || url[s]=='<' || url[s]=='>' || url[s]=='?'  || url[s]=='*' )
			return 0;

		if( c0=='/' && (c1=='/' || c1=='\\') )	// �A�������X���b�V���F�Ӗ��������̂ō폜
		{
			s++;
			url[s]='/';
			continue;
		}
		else if( (c0=='/' || c0=='\\') && c1=='.' && (c2=='/' || c2=='\\') )	// �J�����g�f�B���N�g���F�Ӗ����Ȃ��̂ō폜
		{
			s+=2;
			url[s]='/';
			continue;
		}
		else if( (c0=='/' || c0=='\\') && c1=='.' && c2=='.' && (c3=='/' || c3=='\\') )	// �e�f�B���N�g���F�W�J�܂��̓G���[
		{
			int r;
			if( d<=0 )
				return 0;
			for( r=d-1; r>=0 && url[r]!='/'; r-- );
			if( r<0 )
				return 0;
			s+=3;
			d = r;
			url[s]='/';
			continue;
		}
		url[ d++ ] = url[ s++ ];
	}
	url[d] = '\0';

	return 1;
}

// ==========================================
// IP �`�F�b�N
// ------------------------------------------
static int httpd_check_access_ip( struct httpd_access *a, struct httpd_session_data *sd )
{
	int i;
	int fa=0, fd=0;
	int order = a->type & HTTPD_ACCESS_IP_MASK;
	unsigned long ip = (unsigned long)session[sd->fd]->client_addr.sin_addr.s_addr;

	for( i=0; i<a->aip_count; i+=2 )
	{
		if( (ip & a->aip[i+1]) == a->aip[i] )
			fa=1;
	}
	for( i=0; i<a->dip_count; i+=2 )
	{
		if( (ip & a->dip[i+1]) == a->dip[i] )
			fd=1;
	}

	return	( order == HTTPD_ACCESS_IP_DENY  )? (fd ? fa : 1)  :
			( order == HTTPD_ACCESS_IP_ALLOW )? (fa ? !fd : 0) :
			( order == HTTPD_ACCESS_IP_MUTUAL)? (fa & !fd )    : 0;
}

// ==========================================
// ���[�U�[�F��(�_�C�W�F�X�g�F��)
// ------------------------------------------
int httpd_check_access_user_digest( struct httpd_access *a, struct httpd_session_data *sd )
{
	char buf[1024];
	char response[33]="",nonce[128]="",uri[1024]="",passwd[33]="";
	char username[33]="",realm[256]="",cnonce[256]="",nc[9]="";
	struct httpd_access_user *au=NULL;
	int i = 7 ,n;

	sd->auth_digest_stale = 0;

	if( !sd->auth || strncasecmp( sd->auth, "Digest ", 7 )!=0 )
		return 0;

	// �w�b�_�̉��
	while( sd->auth[i] )
	{
		if( strncasecmp( sd->auth+i, "username=\"", 10 )==0 )		// ���[�U�[��
		{
			if( sscanf(sd->auth+i+10,"%1023[^\"]%n", buf, &n )==1 )
			{
				if( n>=sizeof(username) )
					return 0;
				strcpy( username, buf );
				i += 11 + n;
			}
			else
				return 0;
		}
		if( strncasecmp( sd->auth+i, "realm=\"", 7 )==0 )		// �̈於
		{
			if( sscanf(sd->auth+i+7,"%1023[^\"]%n", buf, &n )==1 )
			{
				if( n>=sizeof(realm) || strcmp(buf,a->realm)!=0 )
					return 0;
				strcpy( realm, buf );
				i += 8 + n;
			}
			else
				return 0;
		}
		if( strncasecmp( sd->auth+i, "nonce=\"", 7 )==0 )		// nonce
		{
			if( sscanf(sd->auth+i+7,"%1023[^\"]%n", buf, &n )==1 )
			{
				if( n>=sizeof(nonce) || n<40  )
					return 0;
				strcpy( nonce, buf );
				i += 8 + n;
			}
			else
				return 0;
		}
		if( strncasecmp( sd->auth+i, "uri=\"", 5)==0 )		// URI
		{
			if( sscanf(sd->auth+i+5,"%1023[^\"]%n", uri, &n )==1 )
			{
				i += 6 + n;
			}
			else
				return 0;
		}
		if( strncasecmp( sd->auth+i, "algorithm=", 10) ==0 )	// �A���S���Y���iMD5�Œ�j
		{
			if( strncasecmp(sd->auth+i+10, "MD5", 3)==0 )
				i += 14;
			else if( strncasecmp(sd->auth+i+10, "\"MD5\"", 5)==0 )	// ie �̃o�O���z��
				i += 16;
			else
				return 0;
		}
		if( strncasecmp( sd->auth+i, "qop=", 4) ==0 )			// qop�iauth�Œ�j
		{
			if( strncasecmp(sd->auth+i+4, "auth", 4)==0 )
				i += 8;
			else if( strncasecmp(sd->auth+i+4, "\"auth\"", 6)==0 )	// ie �̃o�O���z��
				i +=10;
			else
				return 0;
		}
		if( strncasecmp( sd->auth+i, "cnonce=\"", 8 )==0 )	// cnonce
		{
			if( sscanf(sd->auth+i+8,"%1023[^\"]%n", buf, &n )==1 )
			{
				if( n>=sizeof(cnonce))
					return 0;
				strcpy( cnonce, buf );
				i+= 9 + n;
			}
			else
				return 0;
		}
		if( strncasecmp( sd->auth+i, "nc=", 3 )==0 )			// nonce count
		{
			if( sscanf(sd->auth+i+3,"%1023[^, ]%n", buf, &n)==1 )
			{
				if( n!=8 )
					return 0;
				strcpy( nc, buf );
				i += 11;
			}
			else
				return 0;
		}
		if( strncasecmp( sd->auth+i, "response=\"", 10 )==0 )	// response
		{
			if( sscanf(sd->auth+i+10,"%1023[^\"]%n", buf, &n)==1 )
			{
				if( n!=32 )
					return 0;
				strcpy( response, buf );
				i += 43;
			}
			else
				return 0;
		}
		if( strncasecmp( sd->auth+i, "auth_param=", 11 )==0 )	// auth_param
		{
			int c=',';
			i += 11;
			if( sd->auth[i]=='\"' ) c='\"';
			while( sd->auth[i] && sd->auth[i]!=c )
				i++;
			i++;
		}

		if( sd->auth[i]!=' ' && sd->auth[i]!=',' && sd->auth[i] )
			return 0;

		while( sd->auth[i]==' ' || sd->auth[i]==',' )
		{
			i++;
		}
	}

//	printf("response=[%s]\nnonce=[%s]\nusername=[%s]\nrealm=[%s]\ncnonce=[%s]\nnc=[%s]\nuri=[%s]\n",
//		response,nonce,username,realm,cnonce,nc,uri);

	// ���[�U�[���̊m�F�ƃp�X���[�h�̎擾�i�o�^���ꂽ�F�؊֐����g���j
	if( !auth_func[a->auth_func_id] || !auth_func[a->auth_func_id]( a, sd, username, passwd ) )
	{
		passwd[0]=0;
	}

	// ���[�U�[���̊m�F�iauthuser �œo�^���ꂽ���́j
	for( i=0; i<a->user_count; i++ )
	{
		if( a->user[i].type != HTTPD_USER_PASSWD_MD5 &&
			strcmp( a->user[i].name, username ) == 0 )
		{
			au = &a->user[i];
			break;
		}
	}
	if( i==a->user_count && !passwd[0] )	// �o�^���[�U�[����Ȃ��̂ł����ŏ����ł��؂�
		return 0;

	// uri �̑Ó�������
	{
		char req_uri[1024];
		const char *line = sd->request_line;
		while( *line && *line!=' ' ) line++;
		line++;
		i = 0;
		while( *line && *line!=' ' )
			req_uri[i++] = *(line++);
		req_uri[i]='\0';

		if( strcasecmp( req_uri, uri )!=0 )
		{
			// ie �̃o�O�z��
			for( i=0; req_uri[i] && req_uri[i]!='?'; i++ );
			if( req_uri[i]!='?' )
				return 0;
			req_uri[i]='\0';
			if( strcasecmp( req_uri, uri )!=0 )	// uri ������Ȃ�
				return 0;
		}
	}

	// nonce �̑Ó�������
	{
		char buf2[33];
		unsigned int tick;
		if( sscanf(nonce,"%08x",&tick)!=1 )	// tick ���Ȃ�
			return 0;

		sprintf( buf, "%08x:%s", tick, a->privkey );
		MD5_String( buf, buf2 );
		if( strcasecmp( nonce+8, buf2 )!=0 )	// �v�Z���@���Ⴄ
			return 0;

		if( DIFF_TICK( gettick(), tick ) > auth_digest_period )	// �L���������؂ꂽ�̂� stale �t���O�ݒ�
		{
			sd->auth_digest_stale = 1;
			return 0;
		}
	}

	// nc �̑Ó�������
	{
		unsigned int nci;

		if( sscanf(nc,"%08x",&nci )!=1 )	// nc ���Ȃ�
			return 0;

		if( nci == 0 )
			return 0;

		for( i=0; i<NONCE_LOG_SIZE; i++ )
		{
			if( strcasecmp( nonce_log[i].nonce, nonce )==0 )
			{
				if( nonce_log[i].nc != nci )		// nc ������Ȃ�
					return 0;
				break;
			}
		}
		if( i==NONCE_LOG_SIZE )	// nonce ���O�ɖ����̂� stale �t���O�ݒ�
		{
			sd->auth_digest_stale = 1;
			return 0;
		}
		nonce_log[i].nc++;
		nonce_log[i].access_flag = 1;
	}
	// rensponse �̑Ó�������
	{
		const char *method[]={"","GET","POST"};
		char a1[33],a2[33],res[33];

		// A1 �v�Z
		if( passwd[0] )								// �F�؊֐��ɂ��
		{
			sprintf( buf, "%s:%s:%s", username, realm, passwd );
			MD5_String( buf, a1 );
		}
		else if( au->type == HTTPD_USER_PASSWD_PLAIN )	// �v���[���p�X���[�h
		{
			sprintf( buf, "%s:%s:%s", username, realm, au->passwd );
			MD5_String( buf, a1 );
		}
		else if( au->type == HTTPD_USER_PASSWD_DIGEST )	// �v�Z�ς�
		{
			strcpy( a1, au->passwd );
		}
		else
			return 0;

		// A2 �v�Z
		sprintf( buf,"%s:%s", method[sd->method], uri );
		MD5_String( buf, a2 );

		// response �v�Z
		sprintf( buf,"%s:%s:%s:%s:%s:%s", a1, nonce, nc, cnonce, "auth", a2 );
		MD5_String( buf, res );

		if( strcasecmp( res, response )==0 )
		{
			strcpy( sd->user, username );
			return 1;
		}
	}
	return 0;
}

// ==========================================
// ���[�U�[�F��(�x�[�V�b�N�F��)
// ------------------------------------------
int httpd_check_access_user_basic( struct httpd_access *a, struct httpd_session_data *sd )
{
	// ���[�U�[�`�F�b�N
	char buf[1024], name[1024], passwd[1024];

	if( !sd->auth || strncasecmp( sd->auth, "Basic ", 6 )!=0 )
		return 0;

	if( httpd_decode_base64( buf, sd->auth+6 ) && sscanf(buf,"%1023[^:]:%1023[^\r]",name,passwd) == 2 )
	{
		const char *apass[4];
		char passwd2[33];
		int i;

		// �o�^���ꂽ�F�؊֐�������΂�����g���Ĕ�r����
		if( auth_func[a->auth_func_id] && auth_func[a->auth_func_id]( a, sd, name, passwd2 ) && strcmp(passwd, passwd2)==0 )
		{
			strcpy( sd->user, name );
			return 1;
		}

		apass[0] = passwd;
		apass[1] = buf;
		apass[2] = buf+64;
		apass[3] = "";

		sprintf( buf+128, "%s:%s", name, passwd );
		MD5_String( buf+128, buf );
		sprintf( buf+128, "%s:%s:%s", name, a->realm, passwd );
		MD5_String( buf+128, buf+64 );

		// authuser �Őݒ肳�ꂽ�A�J�E���g�𒲂ׂ�
		for( i=0; i<a->user_count; i++ )
		{
			if( strcmp( a->user[i].name, name ) == 0 &&
				strcmp( a->user[i].passwd, apass[a->user[i].type & HTTPD_USER_PASSWD_MASK] )==0 )
			{
				strcpy( sd->user, name );
				return 1;
			}
		}
	}
	return 0;
}

// ==========================================
// �A�N�Z�X�����̃`�F�b�N
// ------------------------------------------
int httpd_check_access( struct httpd_session_data *sd, int *st )
{
	int i;
	int n=-1;
	size_t len=0;
	struct httpd_access *a;

	// ��Ԓ����}�b�`���������T��
	for( i=0; i<htaccess_count; i++ )
	{
		a = htaccess[i];
		if( a->urllen > len && strncasecmp( a->url, sd->url-1, a->urllen )==0 ) {
			n=i; len = a->urllen;
		}
	}
	if( n<0 )
		return 1;

	sd->access = a = htaccess[n];

	// IP �`�F�b�N
	if( a->type & HTTPD_ACCESS_IP_MASK )
	{
		int f = httpd_check_access_ip( a, sd );

		if( f && (a->type & HTTPD_ACCESS_SAT_ANY || !(a->type & HTTPD_ACCESS_AUTH_MASK) ) )
			return 1;
		else if( !f && ( !(a->type & HTTPD_ACCESS_SAT_ANY) || !(a->type & HTTPD_ACCESS_AUTH_MASK) ) )
		{
			*st=403;
			return 0;
		}
	}

	// ���[�U�[�F��
	if( a->type & HTTPD_ACCESS_AUTH_MASK )
	{
		int f = ( (a->type & HTTPD_ACCESS_AUTH_MASK) == HTTPD_ACCESS_AUTH_BASIC )?
				httpd_check_access_user_basic( a, sd ) : httpd_check_access_user_digest( a, sd );

		if( !f )
		{
			*st=401;
			return 0;
		}
		return 1;
	}

	*st = 403;
	return 0;
}

// ==========================================
// ���N�G�X�g�w�b�_�̉��
// ------------------------------------------
int httpd_parse_header(struct httpd_session_data* sd)
{
	int i;
	int content_len    = -1;
	int persist        = -1;
	unsigned char* req = RFIFOP(sd->fd,0);
	int c;
	int status;
	int ri = 0;

	memset( sd->req_head, 0, sizeof(sd->req_head) );

	// �܂��w�b�_�̉��s������null�����ɒu�������A�擪�s�ȊO�̉�͂�����
	while(*req) {
		if(*req == '\r' || *req == '\n') {
			*req = 0;

			if( req[1] == '\n' )
				req++;

			// �s�擪�̕ۑ�
			if( ri<sizeof(sd->req_head)/sizeof(sd->req_head[0]) )
				sd->req_head[ri++] = req+1;

			// Content-Length: �̒���
			if(!strncasecmp(req+1,"Content-Length: ",16)) {
				content_len = atoi(req + 17);
			}
			// Connection: �̒���
			if(!strncasecmp(req+1,"Connection: ",12)) {
				if( strncasecmp(req+13,"close",5)==0)
					persist = 0;
				if( strncasecmp(req+13,"Keep-Alive",10)==0)
					persist = 1;
			}
			// Authorization: �̒���
			if(!strncasecmp(req+1,"Authorization: ",15)) {
				sd->auth = req+16;
			}
			// Range: �̒���
			if(!strncasecmp(req+1,"Range: ", 7)){
				if( strncasecmp(req+8,"bytes=",6 ))	// �o�C�g�����W����Ȃ�
					return 416;
				sd->range_start = atoi( req+14 );
				req += 15;
				while( *req>='0' && *req<='9' ) req++;
				if( *req!='-' && sd->range_start>=0 )	// �J�n�ʒu��������Ȃ��̂Ƀn�C�t��������
					return 400;

				if( *req=='-' )
				{
					req++;
					if( *req>='0' && *req<='9' )
					{
						sd->range_end = atoi( req );
						if( sd->range_end < sd->range_start )	// �T�C�Y���}�C�i�X�ɂȂ�
							return 416;
						while( *req>='0' && *req<='9' ) req++;
					}
				}
				if( *req!='\r' && *req!='\n' )	// range-set ���������邩�s��
					return 400;
				req--;
			}
			// If-Modified-Since �̒���
			if( !strncasecmp(req+1,"If-Modified-Since: ",19) && httpd_get_date( req+20, &sd->date ) ) {
				if( sd->precond )
					return 400;
				sd->precond |= HTTPD_PRECOND_IFMOD;
			}
			// If-Unmodified-Since �̒���
			if( !strncasecmp(req+1,"If-Unmodified-Since: ",21) && httpd_get_date( req+22, &sd->date ) ) {
				if( sd->precond )
					return 400;
				sd->precond |= HTTPD_PRECOND_IFUNMOD;
			}
			// If-Range �̒���
			if(!strncasecmp(req+1,"If-Range: ",10) ) {
				if( sd->precond || !httpd_get_date( req+11, &sd->date ) )
					return 400;
				sd->precond |= HTTPD_PRECOND_IFRANGE;
			}
			// Content-type �̒���
			if(!strncasecmp(req+1,"Content-Type: ",14)) {
				sd->content_type = req + 15;
			}
			// Referer �̒���
			if(!strncasecmp(req+1,"Referer: ",9)) {
				sd->referer = req + 10;
			}
			// User-Agent �̒���
			if(!strncasecmp(req+1,"User-Agent: ",12)) {
				sd->user_agent = req + 13;
			}
			// Cookie �̒���
			if(!strncasecmp(req+1,"Cookie: ",8)) {
				sd->cookie = req + 9;
			}
		}
		req++;
	}
	req = RFIFOP(sd->fd,0);
	strncpy( sd->request_line, req, sizeof(sd->request_line) );

	if(!strncmp(req,"GET /",5)) {		// GET ���N�G�X�g
		req += 5;
		for(i = 0;req[i]; i++) {
			c = req[i];
			if(c == ' ' || c == '?') break;
			if(!isalnum(c) && c != '.' && c != '_' && c != '-' && c !='/' && c != '%') break;
		}
		if(req[i] == ' ') {
			req[i]     = 0;
			sd->url    = req;
			sd->query  = NULL;
			sd->query_len = 0;
		} else if(req[i] == '?') {
			req[i]    = 0;
			sd->query = &req[++i];
			for(;req[i];i++) {
				c = req[i];
				if(c == ' ') break;
				if(!isalnum(c) && c != '+' && c == '%' && c == '&' && c == '=') break;
			}
			if(req[i] != ' ') return 400; // Bad Request
			req[i]     = 0;
			sd->url    = req;
			sd->query_len = (int)(req + i - sd->query);
		} else {
			return 400; // Bad Request
		}

		// URI ����������
		if( i > max_uri_length )
		{
			sd->request_line[ max_uri_length+5 ]='\0';
			return 414;		// Request-URI Too Long
		}

		// �w�b�_���
		if(!strncmp(&req[i+1] ,"HTTP/1.1",8)) {
			sd->http_ver = 1;
			sd->persist  = (persist == -1 ? 1 : persist);
		} else {
			sd->http_ver = 0;
			sd->persist  = (persist == -1 ? 0 : persist);
		}
		sd->method = HTTPD_METHOD_GET;

		// URL �f�R�[�h
		if( !httpd_decode_url( req - 1 ) ) return 400; // Bad Request

		// �A�N�Z�X����̃`�F�b�N
		if( !httpd_check_access( sd, &status ) )
			return status;

		// printf("httpd: request %s %s\n",sd->url,sd->query);
		httpd_parse_request_ok(sd);
	} else if(!strncmp(req,"POST /",6)) {	// POST ���N�G�X�g
		req += 6;
		for(i = 0;req[i]; i++) {
			c = req[i];
			if(c == ' ') break;
			if(	!isalnum(c) && c != '.' && c != '_' && c != '-' && c !='/' && c != '%' ) break;
		}
		if(req[i] != ' ') return 400; // Bad Request
		req[i]     = 0;
		sd->url    = req;

		// URI ����������
		if( i > max_uri_length )
		{
			sd->request_line[ max_uri_length+6 ]='\0';
			return 414;		// Request-URI Too Long
		}

		// �w�b�_���
		if(!strncmp(&req[i+1] ,"HTTP/1.1",8)) {
			sd->http_ver = 1;
			if(sd->persist == -1) sd->persist  = 1;
		} else {
			sd->http_ver = 0;
			if(sd->persist == -1) sd->persist  = 0;
		}
		sd->method = HTTPD_METHOD_POST;

		// URL �f�R�[�h
		if( !httpd_decode_url( req - 1 ) ) return 400; // Bad Request

		if(content_len <= 0 || content_len >= 32*1024) {
			// �Ƃ肠����32KB�ȏ�̃��N�G�X�g�͕s������
			return ( content_len==0 )? 411 : ( content_len >= 32*1024 )? 413 : 400;
		}
		// �A�N�Z�X����̃`�F�b�N
		if( !httpd_check_access( sd, &status ) )
			return status;

		sd->query     = RFIFOP(sd->fd,sd->header_len);
		sd->query_len = content_len;
		sd->header_len += content_len;
		if(RFIFOREST(sd->fd) >= sd->header_len) {
			unsigned char temp = RFIFOB(sd->fd,sd->header_len);
			RFIFOB(sd->fd,sd->header_len) = 0;
			httpd_parse_request_ok(sd);
			RFIFOB(sd->fd,sd->header_len) = temp;
		} else {
			// POST�̃f�[�^�������Ă���̂�҂�
			sd->status = HTTPD_REQUEST_WAIT_POST;
		}
	} else {
		return 400; // Bad Request
	}
	return 200; // Ok
}

// ==========================================
// ���N�G�X�g�̉�͊������y�[�W����������
// ------------------------------------------
void httpd_parse_request_ok(struct httpd_session_data *sd)
{
	HttpdFunc httpd_parse_func;

	sd->status = HTTPD_REQUEST_OK;

	// �t�@�C���������܂����̂ŁA�y�[�W����������������
	// printf("httpd_parse: [% 3d] request /%s\n",fd,req);
	httpd_parse_func = (HttpdFunc)strdb_search(httpd_files,sd->url);
	if(httpd_parse_func == NULL) {
		httpd_parse_func = httpd_default;
	}
	if(httpd_parse_func == NULL) {
		httpd_send_error(sd,404); // Not Found
	} else {
		httpd_parse_func(sd,sd->url);
		if(sd->status == HTTPD_REQUEST_OK) {
			httpd_send_error(sd,404); // Not Found
		}
	}
	if(sd->persist == 1 && sd->data_len && sd->status!=HTTPD_SENDING_BIGFILE && sd->status!=HTTPD_WAITING_CGI ) {
		// �������ςȃf�[�^(����Ȃ̑���Ȃ�c)
		printf("httpd_parse: send size mismatch when parsing /%s\n",sd->url);
		session[sd->fd]->eof = 1;
	}
	if(sd->status == HTTPD_REQUEST_OK) {
		httpd_send_error(sd,404);
	}
}

// ==========================================
// CGI �N�G���̒l�擾
// ------------------------------------------
char* httpd_get_value(struct httpd_session_data* sd,const char* val)
{
	size_t src_len = strlen(val);
	const unsigned char* src_p = sd->query;

	if(src_p == NULL) return (char *)aStrdup("");

	do {
		if(!memcmp(src_p,val,src_len) && src_p[src_len] == '=') {
			break;
		}
		src_p = strchr(src_p + 1,'&');
		if(src_p) src_p++;
	} while(src_p);

	if(src_p != NULL) {
		// �ړI�̕������������
		const unsigned char* p2;
		int   dest_len;
		char* dest_p;
		src_p += src_len + 1;
		p2     = strchr(src_p,'&');
		if(p2 == NULL) {
			src_len = strlen(src_p);
		} else {
			src_len = (p2 - src_p);
		}
		dest_p   = (char *)aMalloc(src_len + 1);
		dest_len = 0;
		while(src_len > 0) {
			if(*src_p == '%' && src_len > 2) {
				int c1 = 0,c2 = 0;
				if(src_p[1] >= '0' && src_p[1] <= '9') c1 = src_p[1] - '0';
				if(src_p[1] >= 'A' && src_p[1] <= 'F') c1 = src_p[1] - 'A' + 10;
				if(src_p[1] >= 'a' && src_p[1] <= 'f') c1 = src_p[1] - 'a' + 10;
				if(src_p[2] >= '0' && src_p[2] <= '9') c2 = src_p[2] - '0';
				if(src_p[2] >= 'A' && src_p[2] <= 'F') c2 = src_p[2] - 'A' + 10;
				if(src_p[2] >= 'a' && src_p[2] <= 'f') c2 = src_p[2] - 'a' + 10;
				dest_p[dest_len++] = (c1 << 4) | c2;
				src_p += 3; src_len -= 3;
			} else if(*src_p == '+') {
				dest_p[dest_len++] = ' ';
				src_p++; src_len--;
			} else {
				dest_p[dest_len++] = *(src_p++); src_len--;
			}
		}
		dest_p[dest_len] = 0;
		return dest_p;
	}
	return (char *)aStrdup("");
}

// ==========================================
// ���\�b�h��Ԃ�
// ------------------------------------------
int httpd_get_method(struct httpd_session_data* sd)
{
	return sd->method;
}

// ==========================================
// IP �A�h���X��Ԃ�
// ------------------------------------------
unsigned long httpd_get_ip(struct httpd_session_data *sd)
{
	return (unsigned long)session[sd->fd]->client_addr.sin_addr.s_addr;
}

// ==========================================
// MIME�^�C�v����
//  ��v�Ȃ��̂������肵�āA�c���application/octet-stream
// ------------------------------------------
static const char* httpd_mimetype(const char* url)
{
	char *ext = strrchr(url,'.');

	if(ext) {
		if(!strcmp(ext,".html")) return "text/html";
		if(!strcmp(ext,".htm"))  return "text/html";
		if(!strcmp(ext,".css"))  return "text/css";
		if(!strcmp(ext,".js"))   return "text/javascript";
		if(!strcmp(ext,".txt"))  return "text/plain";
		if(!strcmp(ext,".gif"))  return "image/gif";
		if(!strcmp(ext,".jpg"))  return "image/jpeg";
		if(!strcmp(ext,".jpeg")) return "image/jpeg";
		if(!strcmp(ext,".png"))  return "image/png";
		if(!strcmp(ext,".xbm"))  return "image/xbm";
		if(!strcmp(ext,".zip"))  return "application/zip";
	}
	return "application/octet-stream";
}

// ==========================================
// URL �� �t�@�C�����⊮
// ------------------------------------------
const char* httpd_complement_file( const char* url, char* buf )
{
	char file_buf[2048];
	const char* cfile = "index.html";	// �f�t�H���g

	// URL �Ȃ��Ȃ�f�t�H���g
	if( url[0] == '\0' )
		return cfile;

	// �X���b�V���ŏI����Ă�����f�t�H���g��ǉ�
	if( url[strlen(url)-1] == '/' )
	{
        snprintf( buf, sizeof(buf), "%s%s", url, cfile );
		return buf;
	}

	// url �̍ő咷�͖� 1010 �o�C�g�ȓ��Ȃ̂ŃI�[�o�[�t���[���Ȃ�
    snprintf(file_buf, sizeof(file_buf), "%s%s", document_root, url);

	// �f�B���N�g����������f�t�H���g��ǉ�
	{
		struct stat st;
		if( stat( file_buf, &st ) == 0 )
		{
			if( st.st_mode & S_IFDIR )
			{
                snprintf( buf, sizeof(buf), "%s/%s", url, cfile );
				return buf;
			}
		}
	}

	// ������ɂ��Y�����Ȃ��̂ł��̂܂�
	return url;
}

// ==========================================
// �y�[�W���� - �ʏ�̃t�@�C�����M
// ------------------------------------------
void httpd_send_file(struct httpd_session_data* sd,const char* url)
{
	FILE *fp;
	int  file_size = 0;
	char file_buf[8192];
	char url_buf[1536];

	if(sd->status != HTTPD_REQUEST_OK) return;

	// URL �̕⊮
	url = httpd_complement_file( url, url_buf );

	// url �̍ő咷�͕⊮����Ă� 1536 �o�C�g�ȓ��Ȃ̂ŃI�[�o�[�t���[���Ȃ�
    snprintf(file_buf, sizeof(file_buf), "%s%s", document_root, url);

#ifndef NO_HTTPD_CGI
	if( httpd_cgi_enable )
	{
		// �O�� CGI �̊g���q���ǂ�������
		const char* ext_list = sd->access ? sd->access->cgi_ext_list : httpd_cgi_ext_list;
		const char* p = strrchr( url, '.' ), *p2;
		if( p && (p2 = strstr( ext_list, p ) ) != NULL && p2[strlen(p)]==' ' )
		{
			if( httpd_get_external_cgi_process_count() < httpd_max_cgi_process )
			{
				httpd_page_external_cgi(sd);
			}
			else
			{
				httpd_send_error( sd, 503 );
			}
			return;
		}
	}
#endif

	// ���W���[���\(Accept-Ranges �̒ʒm)
	sd->reshead_flag |= HTTPD_RESHEAD_ACCRANGE;

	// ���t�E�t�@�C���T�C�Y�m�F
	{
		time_t date = 0;
		struct stat st;

		if( stat( file_buf, &st ) == 0 ) {
			date      = st.st_mtime;
			file_size = st.st_size;
		}

		if( date!=0 && sd->precond == HTTPD_PRECOND_IFMOD   && date == sd->date )	// If-Modified-Since �̏���
		{
			httpd_send_head( sd, 304, NULL, -1);	// 304 �̓G���e�B�e�B�������Ȃ�
			sd->data_len = 0;
			sd->status = HTTPD_WAITING_SEND;
			return;
		}

		if( sd->precond == HTTPD_PRECOND_IFUNMOD && (date != sd->date || date==0) )	// If-Unmodified-Since �̏���
		{
			httpd_send_error( sd, 412 );
			return;
		}

		if( sd->precond == HTTPD_PRECOND_IFRANGE && (date != sd->date || date==0) )	// If-Range �̏���
		{
			sd->range_start = 0;
			sd->range_end   = -1;
		}

		sd->reshead_flag |= HTTPD_RESHEAD_LASTMOD;
		sd->date = date;

	} // end ���t�m�F

	// �t�@�C���̑��M
	fp = fopen(file_buf,"rb");
	if(fp == NULL) {
		httpd_send_error(sd, sd->date ? 403 : 404 );
	} else {
		int status = 200;
		if( sd->range_start!=0 )	// Range �̊J�n�ʒu�`�F�b�N
		{
			if( sd->range_start<0 ) sd->range_start += file_size;
			if( sd->range_start<0 )	// �J�n�n�_����
			{
				httpd_send_error( sd,416 );
				fclose(fp);
				return;
			}
			status = 206;
		}
		if( sd->range_end==-1 )		// Range �̏I���ʒu�C��
			sd->range_end += file_size;
		else
		{
			status = 206;
			if( sd->range_end>file_size )
				sd->range_end = file_size-1;
		}

		sd->inst_len = file_size;
		file_size = sd->range_end - sd->range_start + 1;	// content-lenth �v�Z

		if( file_size<0 )	// �T�C�Y����
		{
			httpd_send_error( sd,416 );
			fclose(fp);
			return;
		}


		if( file_size > bigfile_threshold )		// �傫�ȃt�@�C���͕����]��
		{
			fclose( fp );
			realloc_fifo( sd->fd, 0, bigfile_splitsize );
			httpd_send_head(sd,status,httpd_mimetype(url),file_size);
			sd->status = HTTPD_SENDING_BIGFILE;
			sd->file_pos = sd->range_start;
			httpd_send_bigfile( sd );
		}
		else		// �����ȃt�@�C���� FIFO �Ɉ�C�ɑ���
		{
			realloc_fifo( sd->fd, 0, file_size + 32768 );
			httpd_send_head(sd,status,httpd_mimetype(url),file_size);
			fseek( fp, sd->range_start, SEEK_SET );
			while(file_size > 0) {
				int read_byte = file_size;
				if(file_size > 8192) read_byte = 8192;
				if( fread(file_buf,1,read_byte,fp) != read_byte )
				{
					session[sd->fd]->eof = 1;	// �ǂݍ��݃G���[���N�����̂Őؒf
					return;
				}
				httpd_send_data(sd,read_byte,file_buf);
				file_size -= read_byte;
			}
			fclose(fp);
		}
	}
}

// ==========================================
// �y�[�W���� - ����t�@�C�����M
// ------------------------------------------
void httpd_send_bigfile( struct httpd_session_data* sd )
{
	char file_buf[2048];
	char url_buf[1536];
	const char* url = sd->url;
	FILE *fp;

	if( WFIFOSPACE( sd->fd ) < 64*1024 )	// �o�b�t�@�̋󂫂����Ȃ��̂ŋA��
		return;

	// URL �̕⊮
	url = httpd_complement_file( url, url_buf );

	// url �̍ő咷�͕⊮����Ă� 1536 �o�C�g�ȓ��Ȃ̂ŃI�[�o�[�t���[���Ȃ�
    snprintf(file_buf, sizeof(file_buf), "%s%s", document_root, url);

	// ���t�m�F
	if( sd->date )
	{
		time_t date = 0;
		struct stat st;
		if( stat( file_buf, &st ) == 0 )
			date = st.st_mtime;

		if( date != sd->date )	// �]�����Ƀt�@�C�����X�V���ꂽ�̂Őؒf
		{
			session[sd->fd]->eof = 1;
			return;
		}
	}

	// �t�@�C���̑��M
	fp = fopen(file_buf,"rb");
	if(fp == NULL) {
		session[sd->fd]->eof = 1;
		return;
	} else {
		int send_size = (int)(WFIFOSPACE( sd->fd ) - 32768);
		if( send_size > sd->data_len )
			send_size = sd->data_len;

		fseek( fp, sd->file_pos, SEEK_SET );
		if( fread( WFIFOP(sd->fd,0), 1, send_size, fp)!= send_size )
		{
			session[sd->fd]->eof = 1;	// �t�@�C���ǂݍ��݂ŃG���[�����������̂Őؒf
			return;
		}
		WFIFOSET( sd->fd, send_size );
		sd->data_len -= send_size;
		sd->file_pos = ftell( fp );
		fclose(fp);
	}
	if( sd->data_len==0 )
		sd->status = HTTPD_WAITING_SEND;
}


// ******************************************
// �O�� cgi ���� ��������
// ******************************************


struct httpd_cgi_kill* httpd_page_external_cgi_abort_insert( struct httpd_session_data *sd );
int httpd_page_external_cgi_abort( struct httpd_cgi_kill* p );

void httpd_page_cgi_calc_document_root( struct httpd_session_data *sd, char* path, size_t pathsize, int c1, int c2 );
void httpd_page_cgi_setenv( struct httpd_session_data *sd, char* env, size_t envsize, char** envp2, size_t envpsize, const char* path );
unsigned int httpd_page_cgi_process_header( struct httpd_session_data *sd, char* buf, size_t bytes, int* pstatus );

void httpd_cgi_log( struct httpd_session_data *sd, const char* str );


#ifndef NO_HTTPD_CGI

#ifdef WINDOWS

// �w���p�}�N����`
#	define SAFE_CLOSEHANDLE(h)	if( h != INVALID_HANDLE_VALUE ) { CloseHandle(h); h = INVALID_HANDLE_VALUE; }
#	define CLOSEHANDLES()	{ \
			SAFE_CLOSEHANDLE( sd->cgi_hProcess );	\
			SAFE_CLOSEHANDLE( sd->cgi_hCIn );	\
			SAFE_CLOSEHANDLE( sd->cgi_hPIn );	\
			SAFE_CLOSEHANDLE( sd->cgi_hOut );	\
			SAFE_CLOSEHANDLE( sd->cgi_hErr );	\
		}

// ==========================================
// VC/BCC : �O�� cgi ���� / �q�v���Z�X�N��
// ------------------------------------------
void httpd_page_external_cgi_fork( struct httpd_session_data* sd )
{
	SECURITY_ATTRIBUTES sa;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	char szEnv[4096];
	char szCwd[512];
	char szPath[1024];
	char szCmd[2048];
	BOOL bPost = (httpd_get_method(sd) == HTTPD_METHOD_POST);

	// ------------
	// �n���h�����̏�����
	// ------------
	sd->cgi_hCIn = INVALID_HANDLE_VALUE;	sd->cgi_hPIn = INVALID_HANDLE_VALUE;
	sd->cgi_hOut = INVALID_HANDLE_VALUE;	sd->cgi_hErr = INVALID_HANDLE_VALUE;
	sd->cgi_hProcess = INVALID_HANDLE_VALUE;
	sd->cgi_state = 1;

	// ------------
	// �n���h�������L���邽�߂̍\���̂�ݒ�
	// ------------
	ZeroMemory( &sa, sizeof(sa) );
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	// ------------
	// POST �Ȃ�N�G���𑗂�
	// ------------
	if( bPost )
	{
		DWORD dwWritten;

		// POST �̏ꍇ�A�O�� cgi �ƒʐM���邽�߂̃p�C�v���J��
		if( !CreatePipe( &sd->cgi_hCIn , &sd->cgi_hPIn , &sa, sd->query_len+16 ) )
		{
			// �p�C�v�����Ȃ�
			CLOSEHANDLES();
			printf("httpd_page_external_cgi: CreatePipe: failed.\n");
			httpd_send_error(sd,500);
			return;
		}

		if( !WriteFile( sd->cgi_hPIn, sd->query, sd->query_len, &dwWritten, NULL ) || dwWritten < (DWORD)sd->query_len )
		{
			// POST �̑��M�ŃG���[���N����
			CLOSEHANDLES();
			printf("httpd_page_external_cgi: CreatePipe: failed.\n");
			httpd_send_error(sd,500);
			return;
		}
		SAFE_CLOSEHANDLE( sd->cgi_hPIn );
	}

	// ------------
	// ���O�Ȃ��p�C�v���񓯊����[�h���T�|�[�g���ĂȂ������̑��̐��񂪂���̂Ŏd���Ȃ��c
	// �o�͗p�̃e���|�����t�@�C�����J��
	// ------------
	{
		int i = atn_rand() ^ gettick();
		char tmp_out[256], tmp_err[256];
        snprintf( tmp_out, sizeof(tmp_out), "%sauriga_httpd_out%04x%08x.tmp", httpd_cgi_temp_dir, sd->fd, i );
        snprintf( tmp_err, sizeof(tmp_err), "%sauriga_httpd_err%04x%08x.tmp", httpd_cgi_temp_dir, sd->fd, i );
		sd->cgi_hOut = CreateFile( tmp_out, GENERIC_READ | GENERIC_WRITE, 0, &sa, CREATE_ALWAYS,
									FILE_ATTRIBUTE_TEMPORARY | FILE_FLAG_DELETE_ON_CLOSE, NULL );
		sd->cgi_hErr = CreateFile( tmp_err, GENERIC_READ | GENERIC_WRITE, 0, &sa, CREATE_ALWAYS,
									FILE_ATTRIBUTE_TEMPORARY | FILE_FLAG_DELETE_ON_CLOSE, NULL );

		if( sd->cgi_hOut == INVALID_HANDLE_VALUE || sd->cgi_hErr == INVALID_HANDLE_VALUE )
		{
			// �e���|�����t�@�C�����쐬�ł��Ȃ�����
			CLOSEHANDLES();
			printf("httpd_page_external_cgi: CreateFile: failed.\n");
			httpd_send_error(sd,500);
			return;
		}
	}

	// ------------
	// �q�v���Z�X�Ăяo���̂��߂̐ݒ�
	// ------------
	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	si.hStdInput  = sd->cgi_hCIn;
	si.hStdOutput = sd->cgi_hOut;
	si.hStdError  = sd->cgi_hErr;
	si.dwFlags = STARTF_USESTDHANDLES;

	// ------------
	// �h�L�������g���[�g�̌v�Z
	// ------------
	httpd_page_cgi_calc_document_root( sd, szPath, sizeof(szPath), '\\', '/' );

	// ------------
	// ���ϐ��̐ݒ�
	// ------------
	httpd_page_cgi_setenv( sd, szEnv, sizeof(szEnv), NULL, 0, szPath );

	// ------------
	// �J�����g�f�B���N�g���ƃR�}���h���o
	// ------------
	{
		size_t i, x;
		int j, y;
        snprintf( szCwd, sizeof(szCwd), "%s\\", szPath );
		for( j=y=0, x=i=strlen(szCwd); sd->url[j]; j++,i++ )
		{
			szCwd[i] = ( sd->url[j] == '/' )? '\\' : sd->url[j];
			if( szCwd[i] == '\\' ) {
				x=i;
				y=j;
			}
		}
		szCwd[x]='\0';
		szCmd[0]='.'; szCmd[1]='\\';
		strcpy( szCmd+2, sd->url+y );
	}

	// ------------
	// �R�}���h���C���̐���
	// ------------
	{
		FILE *fp;
		char buf[256], cmd2[2048];
        snprintf( cmd2, sizeof(cmd2), "%s%s", document_root, sd->url );
		if( (fp = fopen( cmd2, "rb" )) ==NULL )
		{
			// ���s
			CLOSEHANDLES();
			printf("httpd_page_external_cgi: no such script [%s]\n", sd->url);
			httpd_send_error(sd,404);
			return;
		}
		buf[ fread( buf, 1, sizeof(buf)-1, fp ) ] = '\0';
		fclose( fp );

		if( buf[0]=='#' && buf[1]=='!' )
		{
			// �擪�s�� #! �Ŏn�܂��Ă�̂ŃX�N���v�g���ۂ�
			int i, k=2;
			for( i=2; buf[i]==' ' || buf[i]=='\t'; i++ )
				;
			for( i=2; buf[i] && buf[i]!='\r' && buf[i]!='\n'; i++ )
			{
				if( buf[i]==' ' ) break;
				if( buf[i]=='/' ) k=i+1;
			}
			buf[i]='\0';

			strcpy( cmd2, szCmd );
            snprintf( szCmd, sizeof(szCmd), "%s %s", buf+k, cmd2 );
		}
	}

	// ------------
	// �q�v���Z�X�Ăяo��
	// ------------
	if( !CreateProcess( NULL, szCmd, NULL, NULL, TRUE,
						CREATE_NEW_PROCESS_GROUP | BELOW_NORMAL_PRIORITY_CLASS,
						szEnv, szCwd, &si, &pi ) )
	{
		// ���s
		CLOSEHANDLES();
		printf("httpd_page_external_cgi: CreateProcess: failed.\n");
		httpd_send_error(sd,500);
		return;
	}

	// ------------
	// ����Ȃ��n���h�������
	// ------------
	CloseHandle( pi.hThread );
	SAFE_CLOSEHANDLE( sd->cgi_hCIn  );

	// ------------
	// �ϐ��̐ݒ�
	// ------------
	sd->tick = gettick();
	sd->status = HTTPD_WAITING_CGI;
	sd->cgi_hProcess = pi.hProcess;
	sd->cgi_dwProcessID = pi.dwProcessId;

}

// ==========================================
// VC/BCC : �O�� cgi ���� / ���`�Ƒ��M
// ------------------------------------------
void httpd_page_external_cgi_send( struct httpd_session_data* sd )
{
	char szBuf[8192];
	DWORD dwRead;
	unsigned int i;
	int status;

	// ------------
	// �W���G���[�o�͂𒲂ׂ�
	// ------------
	if( GetFileSize( sd->cgi_hErr, NULL ) != 0 )
	{
		// cgi �ŃG���[���������炵��
		ReadFile( sd->cgi_hErr, szBuf, sizeof(szBuf)-16, &dwRead, NULL );
		szBuf[dwRead] = '\0';
		printf("error --\n%s\n---\n", szBuf );

		// todo: �G���[���O�ɏo��
		printf("httpd_page_external_cgi: cgi error ?\n");
	}
	SAFE_CLOSEHANDLE( sd->cgi_hErr );


	// ------------
	// �w�b�_�̓ǂݍ���
	// ------------
	SetFilePointer( sd->cgi_hOut, 0, NULL, FILE_BEGIN );
	ZeroMemory( szBuf, sizeof(szBuf) );
	if( !ReadFile( sd->cgi_hOut, szBuf, sizeof(szBuf)-64, &dwRead, NULL ) || dwRead == 0 )
	{
		// ���炩�̃G���[���A�f�[�^����
		CLOSEHANDLES();
		printf("httpd_page_external_cgi: ReadFile : failed.\n");
		sd->status = HTTPD_REQUEST_OK;
		httpd_send_error(sd,500);
		return;
	}

	// ------------
	// �w�b�_�̏������f�[�^�̍ŏ����M
	// ------------
	if( ( i = httpd_page_cgi_process_header( sd, szBuf, dwRead, &status ) ) == 0 )
	{
		// �w�b�_���� Content-type �� Location ���Ȃ�
		CLOSEHANDLES();
		printf("httpd_page_external_cgi: Content-type or Location not found.\n");
		sd->status = HTTPD_REQUEST_OK;
		httpd_send_error(sd,500);
		return;
	}

	// ------------
	// ���O�̏o��
	// ------------
	httpd_log( sd, status, GetFileSize( sd->cgi_hOut, NULL ) - i );

	// ------------
	// �f�[�^�̏o��(�c��)
	// ------------
	while( ReadFile( sd->cgi_hOut, szBuf, sizeof(szBuf), &dwRead, NULL ) && dwRead > 0 )
	{
		WFIFORESERVE( sd->fd, dwRead );
		memcpy( WFIFOP( sd->fd, 0 ), szBuf, dwRead );
		WFIFOSET( sd->fd, dwRead );
	}

	sd->status   = HTTPD_WAITING_SEND;
	sd->data_len = 0;
	sd->cgi_state= 0;

	// �n���h���̃N���[�Y
	CLOSEHANDLES();
}

// ==========================================
// VC/BCC : �O�� cgi ���� / ���C��
// ------------------------------------------
void httpd_page_external_cgi( struct httpd_session_data* sd )
{
	BOOL bRunning;

	// ------------
	// ����Ȃ� CGI �N��
	// ------------
	if( sd->status != HTTPD_WAITING_CGI )
	{
		httpd_page_external_cgi_fork(sd);
		return;
	}

	// ------------
	// cgi �v���Z�X�̃`�F�b�N
	// ------------
	bRunning = ( WaitForSingleObject( sd->cgi_hProcess, 0 ) != WAIT_OBJECT_0 );

	if( bRunning )
	{
		// cgi �̏������I����ĂȂ�
		if( DIFF_TICK( gettick(), sd->tick ) > httpd_cgi_timeout )
		{
			// �^�C���A�E�g���Ă���̂� CGI �𒆒f����
			printf("httpd_page_external_cgi: cgi timed out\n");
			httpd_page_external_cgi_disconnect( sd );
			sd->status = HTTPD_REQUEST_OK;
			httpd_send_error(sd,500);
		}
		return;
	}

	// ------------
	// cgi �͏I�����Ă���̂ŏo�͏���������
	// ------------
	httpd_page_external_cgi_send(sd);
	return;
}

// ==========================================
// VC/BCC : �O�� cgi ���� / ���f����
// ------------------------------------------
int httpd_page_external_cgi_abort( struct httpd_cgi_kill* p )
{
	BOOL bRunning;

	switch( p->state )
	{
	// ------------
	// CGI �̒��f
	// ------------
	case 1:
		GenerateConsoleCtrlEvent( CTRL_BREAK_EVENT, p->dwProcessID ); // CGI �v���Z�X�� BREAK �C�x���g�𑗂�
		printf("httpd_page_external_cgi: break process.\n");
		p->state = 2;
		return 0;

	// ------------
	// CGI �̒��f�҂�
	// ------------
	case 2:
		bRunning = ( WaitForSingleObject( p->hProcess, 0 ) != WAIT_OBJECT_0 );
		if( bRunning )
		{
			if( DIFF_TICK( gettick(), p->tick ) > httpd_cgi_kill_timeout )
			{
				// ���f���^�C���A�E�g�����̂ŋ����I��
				TerminateProcess( p->hProcess, 255 );
				printf("httpd_page_external_cgi: break fail / kill process.\n");
			}
			else
			{
				return 0;
			}
		}
		CloseHandle( p->hProcess );
		return 1;
	}

	printf("httpd_page_external_cgi_abort: not reachable !\a\n");
	return 1;
}

// ==========================================
// VC/BCC : �O�� cgi ���� / �f�X�g���N�^
// ------------------------------------------
void httpd_page_external_cgi_disconnect( struct httpd_session_data* sd )
{
	// CGI ���s���Ȃ璆�f�������K�v
	if( sd->cgi_hProcess != INVALID_HANDLE_VALUE )
	{
		struct httpd_cgi_kill* p = httpd_page_external_cgi_abort_insert( sd );
		if( p )
		{
			p->hProcess    = sd->cgi_hProcess;
			p->dwProcessID = sd->cgi_dwProcessID;
			sd->cgi_hProcess = INVALID_HANDLE_VALUE;	// �J�����Ȃ��ėǂ�
			httpd_page_external_cgi_abort( p );
		}
		else
		{
			TerminateProcess( sd->cgi_hProcess, 255 );
		}
	}

	// �n���h����S�ĕ���
	CLOSEHANDLES();
}

// ==========================================
// VC/BCC : �O�� cgi ���� / �I������
// ------------------------------------------
void httpd_page_external_cgi_final_sub( struct httpd_cgi_kill *p )
{
	CloseHandle( p->hProcess );
}

// �w���p�}�N���͂�������Ȃ�
#	undef	CLOSEHANDLES
#	undef	SAFE_CLOSEHANDLE

#else
// ==========================================
// gcc : �O�� cgi ����
// ------------------------------------------

#	define	DEF_CLOSEFD(fd)		(close)(fd);
#	define	SAFE_CLOSEFD(fd)	if( fd>=0 ) { DEF_CLOSEFD(fd); fd=-1; }
#	define	CLOSEFDS()	{	\
					SAFE_CLOSEFD( sd->cgi_in );		\
					SAFE_CLOSEFD( sd->cgi_out );	\
					SAFE_CLOSEFD( sd->cgi_err );	\
				}

// ==========================================
// gcc : �O�� cgi ���� / �q�v���Z�X�N��
// ------------------------------------------
void httpd_page_external_cgi_fork( struct httpd_session_data* sd )
{
	char env[4096];
	char* envp[128];
	char path[1024];
	char cmd[2048];
	char cwd[512];
	int cpid;

	// ------------
	// �f�B�X�N���v�^���̏�����
	// ------------
	sd->cgi_in = sd->cgi_out = sd->cgi_err = -1;
	sd->cgi_state = 1;

	// ------------
	// Cygwin �ł͔񓯊��p�C�v���T�|�[�g���ĂȂ�(�悤�Ɏv����?)�̂Ŏd���Ȃ��c
	// �e���|�����t�@�C�����J��
	// ------------
	{
		int i = atn_rand() ^ gettick();
		char tmp_in[256], tmp_out[256], tmp_err[256];
		// ���O�����
        snprintf( tmp_in,  sizeof(tmp_in),  "%sauriga_httpd_in%04x%08x.tmp",  httpd_cgi_temp_dir, sd->fd, i );
        snprintf( tmp_out, sizeof(tmp_out), "%sauriga_httpd_out%04x%08x.tmp", httpd_cgi_temp_dir, sd->fd, i );
        snprintf( tmp_err, sizeof(tmp_err), "%sauriga_httpd_err%04x%08x.tmp", httpd_cgi_temp_dir, sd->fd, i );

		// �J��
		sd->cgi_in  = open( tmp_in , O_RDWR | O_CREAT | O_TRUNC, 0644 );
		sd->cgi_out = open( tmp_out, O_RDWR | O_CREAT | O_TRUNC, 0644 );
		sd->cgi_err = open( tmp_err, O_RDWR | O_CREAT | O_TRUNC, 0644 );

		// �t�@�C���������폜����悤�Ɏw�����Ă���
		unlink( tmp_in );
		unlink( tmp_out );
		unlink( tmp_err );

		if( sd->cgi_in == -1 || sd->cgi_out == -1 || sd->cgi_err == -1 )
		{
			// �e���|�����t�@�C�����쐬�ł��Ȃ�����
			CLOSEFDS();
			printf("httpd_page_external_cgi: open: failed.\n");
			httpd_send_error(sd,500);
			return;
		}

	}

	// ------------
	// POST �Ȃ�N�G�����o�͂���
	// ------------
	if( httpd_get_method(sd) == HTTPD_METHOD_POST )
	{
		if( write( sd->cgi_in, sd->query, sd->query_len ) < sd->query_len )
		{
			// POST �̑��M�ŃG���[���N����
			CLOSEFDS();
			printf("httpd_page_external_cgi: write POST query: failed.\n");
			httpd_send_error(sd,500);
			return;
		}
	}

	// ------------
	// �h�L�������g���[�g�̌v�Z
	// ------------
	httpd_page_cgi_calc_document_root( sd, path, sizeof(path), '/', '\\' );

	// ------------
	// ���ϐ��̐ݒ�
	// ------------
	httpd_page_cgi_setenv( sd, env, sizeof(env), envp, sizeof(envp), path );

	// ------------
	// �J�����g�f�B���N�g���ƃR�}���h���o
	// ------------
	{
		int j, i, x, y;
        snprintf( cwd, sizeof(cwd), "%s/", path );
		for( j=y=0, x=i=strlen(cwd); sd->url[j]; j++,i++ )
		{
			cwd[i] = ( sd->url[j] == '\\' )? '/' : sd->url[j];
			if( cwd[i] == '/' ) {
				x=i;
				y=j;
			}
		}
		cwd[x]='\0';
		cmd[0]='.'; cmd[1]='/';
		strcpy( cmd+2, sd->url+y );
	}

	// ------------
	// �q�v���Z�X�� fork ����
	// ------------
	if( ( cpid = fork() )==-1 )
	{
		CLOSEFDS();
		printf("httpd_page_external_cgi: fork failed.\n");
		sd->status = HTTPD_REQUEST_OK;
		httpd_send_error(sd,500);
		return;
	}

	// ------------
	// �q�v���Z�X�Ȃ�v���O�����N��
	// ------------
	if( cpid==0 )
	{
		// �J�����g�f�B���N�g���ύX
		chdir( cwd );

		// �W�����o�͂̃��_�C���N�g
		dup2( sd->cgi_in , 0 ); DEF_CLOSEFD( sd->cgi_in  );
		dup2( sd->cgi_out, 1 ); DEF_CLOSEFD( sd->cgi_out );
		dup2( sd->cgi_err, 2 ); DEF_CLOSEFD( sd->cgi_err  );

		// CGI �v���O�����̋N��
		execle( cmd, cmd, NULL, envp );

		// �Ȃ�炩�̃G���[����
		printf("http_page_external_cgi: execle failed.\n");

		// do_final �n�������������ɏI��
		abort();
	}

	// ------------
	// �e�v���Z�X�Ȃ�ϐ���ݒ肷��
	// ------------
	sd->tick = gettick();
	sd->status = HTTPD_WAITING_CGI;
	sd->cgi_cpid = cpid;
	SAFE_CLOSEFD( sd->cgi_in );

	return;
}

// ==========================================
// gcc : �O�� cgi ���� / ���`�Ƒ��M
// ------------------------------------------
void httpd_page_external_cgi_send( struct httpd_session_data* sd )
{
	char buf[8192];
	int i, bytes, status;

	// ------------
	// �W���G���[�o�͂𒲂ׂ�
	// ------------
	if( lseek( sd->cgi_err, 0, SEEK_END ) != 0 )
	{
		// cgi �ŃG���[���������炵��
		// todo: �G���[���O�ɏo��
		printf("httpd_page_external_cgi: cgi error ?\n");
	}
	SAFE_CLOSEFD( sd->cgi_err );

	// ------------
	// �w�b�_�̓ǂݍ���
	// ------------
	lseek( sd->cgi_out, 0, SEEK_SET );
	memset( buf, 0, sizeof(buf) );
	if( ( bytes = read( sd->cgi_out, buf, sizeof(buf) ) ) <=0 )
	{
		// ���炩�̃G���[���A�f�[�^����
		CLOSEFDS();
		printf("httpd_page_external_cgi: read : failed.\n");
		sd->status = HTTPD_REQUEST_OK;
		httpd_send_error(sd,500);
		return;
	}

	// ------------
	// �w�b�_�̏������f�[�^�̍ŏ����M
	// ------------
	if( ( i = httpd_page_cgi_process_header( sd, buf, bytes, &status ) ) == 0 )
	{
		CLOSEFDS();
		printf("httpd_page_external_cgi: Content-type or Location not found.\n");
		sd->status = HTTPD_REQUEST_OK;
		httpd_send_error(sd,500);
		return;
	}

	// ------------
	// ���O�̏o��
	// ------------
	httpd_log( sd, status, lseek( sd->cgi_out, 0, SEEK_CUR ) - i );

	// ------------
	// �f�[�^�̏o��(�c��)
	// ------------
	while( (bytes = read( sd->cgi_out, buf, sizeof(buf) ) ) > 0 )
	{
		memcpy( WFIFOP( sd->fd, 0 ), buf, bytes );
		WFIFOSET( sd->fd, bytes );
	}

	sd->status   = HTTPD_WAITING_SEND;
	sd->data_len = 0;
	sd->cgi_state= 0;

	// �n���h���̃N���[�Y
	CLOSEFDS();
	return;
}

// ==========================================
// gcc : �O�� cgi ���� / ���C��
// ------------------------------------------
void httpd_page_external_cgi( struct httpd_session_data* sd )
{
	int status=0, running;

	// ------------
	// ����Ȃ� CGI �N��
	// ------------
	if( sd->status != HTTPD_WAITING_CGI )
	{
		httpd_page_external_cgi_fork(sd);
		return;
	}

	// ------------
	// cgi �v���Z�X�̃`�F�b�N
	// ------------
	running = (waitpid( sd->cgi_cpid, &status, WNOHANG ) ==0 || (!WIFEXITED(status) && !WIFSIGNALED(status)) );

	if( running )
	{
		// cgi �̏������I����ĂȂ��̂Ń^�C���A�E�g���ĂȂ������ׂ�
		if( DIFF_TICK( gettick(), sd->tick ) > httpd_cgi_timeout )
		{
			// �^�C���A�E�g���Ă���̂� CGI ���I�����ăG���[��ʒm
			printf("httpd_page_external_cgi: cgi timed out.\n");
			httpd_page_external_cgi_disconnect( sd );
			sd->status = HTTPD_REQUEST_OK;
			httpd_send_error(sd,500);
		}
		return;
	}

	// ------------
	// cgi �͏I�����Ă���̂ŏo�͏���������
	// ------------
	httpd_page_external_cgi_send(sd);
	return;
}

// ==========================================
// gcc : �O�� cgi ���� / ���f����
// ------------------------------------------
int httpd_page_external_cgi_abort( struct httpd_cgi_kill* p )
{
	unsigned int tick = gettick();
	int running, status;

	running = (waitpid( p->pid, &status, WNOHANG ) ==0 || (!WIFEXITED(status) && !WIFSIGNALED(status)) );

	switch( p->state )
	{
	// ------------
	// CGI �̏I��
	// ------------
	case 1:
		kill( p->pid, SIGTERM );	// CGI �� TERM �V�O�i���𑗂�
		printf("httpd_page_external_cgi: break process.\n");
		p->state=2;
		p->tick = gettick();
		return 0;

	// ------------
	// CGI �̒��f�҂�
	// ------------
	case 2:
		if( running )
		{
			if( DIFF_TICK( tick, p->tick ) > httpd_cgi_kill_timeout )
			{
				// ���f���^�C���A�E�g�����̂ŋ����I��
				kill( p->pid, SIGKILL );	// CGI �� KILL �V�O�i���𑗂�
				printf("httpd_page_external_cgi: break failed / kill process.\n");
				p->state=3;
			}
			return 0;
		}
		return 1;	// ���f����

	// ------------
	// CGI �̋����I���҂�
	// ------------
	case 3:
		if( running )	// KILL �������I�����ĂȂ� : �]���r�����邩������Ȃ�������ȏ�ʓ|���؂�Ȃ�
		{
			printf("httpd_page_external_cgi: kill failed.\n");
		}
		return 1;
	}

	printf("httpd_page_external_cgi_abort: not reachable !\a\n");
	return 1;
}

// ==========================================
// gcc : �O�� cgi ���� / �f�X�g���N�^
// ------------------------------------------
void httpd_page_external_cgi_disconnect( struct httpd_session_data* sd )
{
	CLOSEFDS();

	// CGI ���s���Ȃ璆�f�������K�v
	if( sd->cgi_cpid > 0 )
	{
		struct httpd_cgi_kill* p;
		if( ( p = httpd_page_external_cgi_abort_insert( sd ) ) != NULL )
		{
			p->pid = sd->cgi_cpid;
			httpd_page_external_cgi_abort( p );
		}
		else
		{
			kill( sd->cgi_cpid, SIGKILL );
			waitpid( sd->cgi_cpid, NULL, WNOHANG );
		}
	}
}

// ==========================================
// gcc : �O�� cgi ���� / �I������
// ------------------------------------------
void httpd_page_external_cgi_final_sub( struct httpd_cgi_kill *p )
{
	return;
}

#	undef	CLOSEFDS
#	undef	SAFE_CLOSEFD
#	undef	DEF_CLOSEFD

#endif

// ==========================================
// ���� : �O�� cgi ���� / ���f���X�g�ǉ�
// ------------------------------------------
struct httpd_cgi_kill* httpd_page_external_cgi_abort_insert( struct httpd_session_data *sd )
{
	struct httpd_cgi_kill* p = NULL;
	int i;

	for( i=0; i<HTTPD_CGI_KILL_SIZE; i++ )
	{
		if( ( p = &httpd_cgi_kill_list[i])->state == 0 )
			break;
	}

	if( p==NULL )
	{
		printf("httpd_page_external_cgi_abort_insert: not enouch entry !\n");
		return NULL;
	}

	p->state = 1;
	p->tick = gettick();
	httpd_cgi_kill_size++;
	return p;
}

// ==========================================
// ���� : �O�� cgi ���� / ���f���X�g�^�C�}����
// ------------------------------------------
int httpd_page_external_cgi_abort_timer( int tid, unsigned int tick, int id, void *data)
{
	int i, num = httpd_cgi_kill_size;

	for( i=0; i<HTTPD_CGI_KILL_SIZE && num>0 ; i++ )
	{
		struct httpd_cgi_kill* p = &httpd_cgi_kill_list[i];
		if( p->state == 0 )
			continue;

		if( httpd_page_external_cgi_abort( p ) )
		{
			p->state = 0;
			httpd_cgi_kill_size --;
		}
		num --;
	}

	return 0;
}

// ==========================================
// ���� : �O�� cgi ���� / �I������
// ------------------------------------------
void httpd_page_external_cgi_final(void)
{
	int i;

	for( i=0; i<HTTPD_CGI_KILL_SIZE; i++ )
	{
		if( httpd_cgi_kill_list[i].state != 0 )
		{
			httpd_page_external_cgi_final_sub( &httpd_cgi_kill_list[i] );
		}
	}
	httpd_cgi_kill_size = 0;
}


// ==========================================
// ���ʁF cgi �̃v���Z�X����Ԃ�
// ------------------------------------------
int httpd_get_external_cgi_process_count(void)
{
	int i,c = 0;
	struct httpd_session_data *sd;

	for( i=0; i<fd_max; i++ )
	{
		if(	session[i] && session[i]->func_parse == httpd_parse &&
			(sd = (struct httpd_session_data*)session[i]->session_data2) &&
			sd->cgi_state )
		{
			c++;
		}
	}
	return c;
}

// ==========================================
// ���ʁF cgi �h�L�������g���[�g�v�Z
// ------------------------------------------
void httpd_page_cgi_calc_document_root( struct httpd_session_data *sd, char* path, size_t pathsize, int c1, int c2 )
{
	int i,j;

	i=j=0;
	if( document_root[0]!='/' && document_root[1]!=':' )	// �K�v�Ȃ�J�����g�f�B���N�g���ƌ���
	{
#ifdef WINDOWS
		i = GetCurrentDirectory( (DWORD)pathsize, path );
#else
		getcwd( path, pathsize );
		i = strlen( path );
#endif
		if( path[ i-1 ] != c1 ) {
			path[i++] = c1;
		}

		while( document_root[j]=='.' )
		{
			if( document_root[j+1]==c1 || document_root[j+1]==c2 )	// �J�����g
			{
				j+=2;
			}
			if( document_root[j+1]=='.' && (document_root[j+2]==c1 || document_root[j+2]==c2) )	// �e
			{
				j+=3;
				i--;
				while( i>0 && path[i]!=c1 && path[i]!=c2 )
				{
					i--;
				}
				i++;
			}
		}
	}
	while( document_root[j] )
	{
		path[i++]=(document_root[j] == c2 )? c1 : document_root[j];
		j++;
	}
	if( path[ i-1 ]==c1 ) {
		path[--i]='\0';
	}
}

// ==========================================
// ���ʁF cgi ���ϐ��̐ݒ�
// ------------------------------------------
void httpd_page_cgi_setenv( struct httpd_session_data *sd, char* env, size_t envsize, char** envp2, size_t envpsize, const char* path )
{
	static const unsigned char* method[] = { "UNKNOWN", "GET", "POST" };
	unsigned char* ip = (unsigned char *)( &session[sd->fd]->client_addr.sin_addr );
	unsigned short port = ntohs( session[sd->fd]->client_addr.sin_port );
	int i,x;
	unsigned int j=0;
	char* envp3[256];
	char** envp = envp2;

	if( !envp )
	{
		envp = envp3;
		envpsize = sizeof(envp3);
	}
	envsize /= sizeof(char*);

	// �K���ݒ肷�����
    i  = snprintf( envp[ j++ ] = env    , envsize - i, "REMOTE_ADDR=%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3] ) + 1;
    i += snprintf( envp[ j++ ] = env + i, envsize - i, "REMOTE_PORT=%d", port ) + 1;
    i += snprintf( envp[ j++ ] = env + i, envsize - i, "DOCUMENT_ROOT=%s", path ) + 1;
    i += snprintf( envp[ j++ ] = env + i, envsize - i, "SCRIPT_NAME=/%s", sd->url ) + 1;
    i += snprintf( envp[ j++ ] = env + i, envsize - i, "SERVER_SOFTWARE=%s/revision%d", servername, AURIGA_REVISION ) + 1;
    i += snprintf( envp[ j++ ] = env + i, envsize - i, "SERVER_PROTOCOL=HTTP/1.0" ) + 1;
    i += snprintf( envp[ j++ ] = env + i, envsize - i, "SERVER_NAME=%s", httpd_cgi_server_name ) + 1;
    i += snprintf( envp[ j++ ] = env + i, envsize - i, "SERVER_PORT=%d", session[sd->fd]->server_port ) + 1;
    i += snprintf( envp[ j++ ] = env + i, envsize - i, "REQUEST_METHOD=%s", method[ httpd_get_method(sd) ] ) + 1;
    i += snprintf( envp[ j++ ] = env + i, envsize - i, "GATEWAY_INTERFACE=CGI/1.1" ) + 1;

	if( httpd_get_method(sd) == HTTPD_METHOD_POST )		// POST �Ȃ�N�G���̒����� Content-type
	{
        i += snprintf( envp[ j++ ] = env + i, envsize - i, "CONTENT_LENGTH=%d", sd->query_len ) + 1;
        i += snprintf( envp[ j++ ] = env + i, envsize - i, "CONTENT_TYPE=%s",
                        sd->content_type ? (char*)sd->content_type : "application/x-www-form-urlencoded" ) + 1;
	}
	else if( httpd_get_method(sd) == HTTPD_METHOD_GET )	// GET �Ȃ�N�G���𒼐ږ��ߍ���
	{
        i += snprintf( envp[ j++ ] = env + i, envsize - i, "QUERY_STRING=%s", sd->query ? (char*)sd->query : "" ) + 1;
	}

	if( sd->user[0] )	// �F�؂��Ă�Ȃ烆�[�U�[���ƔF�ؕ��@
	{
		static const char *type[] = { "None", "Basic", "Digest", "Unknown" };
        i += snprintf( envp[ j++ ] = env + i, envsize - i, "REMOTE_USER=%s", sd->user ) + 1;
        i += snprintf( envp[ j++ ] = env + i, envsize - i, "AUTH_TYPE=%s", type[ sd->access->type & HTTPD_ACCESS_AUTH_MASK ] ) + 1;
	}

	// ���N�G�X�g�w�b�_����ݒ�
	for( x=0;	j<envpsize-1 &&
				x<sizeof(sd->req_head)/sizeof(sd->req_head[0]) &&
				sd->req_head[x] && *sd->req_head[x]
			; x++ )
	{
		char w1[1024], w2[1024];
		if( sscanf( sd->req_head[x], "%1023[^:]: %1023[^\r\n]", w1, w2 ) == 2 )
		{
			if( strcasecmp( w1, "Content-Type"   )!=0 &&
				strcasecmp( w1, "Content-Length" )!=0 )
			{
				int z;
				for( z=0; w1[z]; z++ )
				{
					if( w1[z]=='-' )	w1[z] = '_';
					else				w1[z] = toupper( w1[z] );
				}

				if( i + z + strlen(w2) + 16 > envsize )	// �o�b�t�@�I�[�o�[�t���[�΍�
					break;

                i += snprintf( envp[ j++ ] = env + i, envsize - i, "HTTP_%s=%s", w1, w2 ) + 1;
			}
		}
	}

	env[i] = '\0';
	envp[j] = NULL;
}

// ==========================================
// ���ʁF cgi �w�b�_����
// ------------------------------------------
unsigned int httpd_page_cgi_process_header( struct httpd_session_data *sd, char* buf, size_t bytes, int* pstatus )
{
	char status[256]="200 OK\r\n";
	size_t x = 0;

	if( strncasecmp( buf, "HTTP/1.", 7 )==0 && (buf[7]=='0' || buf[7]=='1') && buf[8]==' ')
	{
		// nph ����
		memcpy( WFIFOP( sd->fd, 0 ), buf, bytes );
		WFIFOSET( sd->fd, (int)bytes );
	}
	else
	{
		char out[8192];
		int i;
		int ctype_flag = 0;
		int status_flag = 0;
		unsigned int y = 0;

		// nph �ł͂Ȃ�
		while( buf[x] && buf[x]!='\r' && buf[x]!='\n' && bytes > x + 2 )	// �w�b�_���I���܂ŌJ��Ԃ�
		{
			if( strncasecmp( buf+x, "Status: ", 8 )==0 )	// Status
			{
				unsigned int z = 0;
				x+=8;
				while( buf[x] && buf[x]!='\r' && buf[x]!='\n' && bytes > x + 2 && sizeof(status) > z + 2 )
				{
					status[z++] = buf[x++];
				}
				if( ( status[z++] = buf[x++] ) == '\n' )
				{
					status[z-1] = '\r';
					status[z++] = '\n';
				}
				else
				{
					status[z++] = buf[x++];	// '\n'
				}
				status[z] = '\0';
				status_flag = 1;
			}

			if( strncasecmp( buf+x, "Content-type: ", 14 )==0 )	// Content-type
			{
				ctype_flag = 1;
			}
			if( strncasecmp( buf+x, "Location: ", 10 )==0 )	// Location
			{
				ctype_flag = 1;
				if( !status_flag )
				{
					strcpy( status,"302 Found\r\n" );
				}
			}

			while( buf[x] && buf[x]!='\r' && buf[x]!='\n' && bytes > x + 2 )	// �w�b�_�R�s�[
			{
				out[y++] = buf[x++];
			}
			if( ( out[y++] = buf[x++] ) == '\n' )
			{
				out[y-1] = '\r';
				out[y++] = '\n';
			}
			else
			{
				out[y++] = buf[x++];	// '\n'
			}
		}// end of �w�b�_��̓��[�v

		if( buf[x] && bytes > x + 2 )
		{
			// �Ō�̋�s�ǂݔ�΂�
			if( ( out[y++] = buf[x++] ) == '\n' )
			{
				out[y-1] = '\r';
				out[y++] = '\n';
			}
			else
			{
				out[y++] = buf[x++];	// '\n'
			}
		}

		if( !ctype_flag )
		{
			// �w�b�_���� Content-type �� Location ���Ȃ�
			return 0;
		}

		sd->http_ver= 0;
		sd->persist = 0;
		i = sprintf( WFIFOP( sd->fd, 0 ),
				"HTTP/1.0 %sServer: %s/revision%d\r\n", status, servername, AURIGA_REVISION );
		memcpy( WFIFOP( sd->fd, i ), out, y );
		i += y;
		memcpy( WFIFOP( sd->fd, i ), buf + x, bytes - x );
		i += (int)(bytes - x);
		WFIFOSET( sd->fd, i );
	}

	*pstatus = atoi( status );

	return (unsigned int)x;
}

/*
// ��肩���c�c
// access_log �ɔ�ׂ���A������ apache �݊��ɂ���K�v�Ȃ����Ȃ�

// ==========================================
// ���ʁF cgi �̃��O
// ------------------------------------------
void httpd_cgi_log( struct httpd_session_data *sd, const char* str )
{
	static int first = 1;
	char timestr[256];
	unsigned char *ip;
	static const char sign[]={'-','+'};

	// ����Ăяo�����͂��낢��Ƃ�邱�Ƃ�����
	if( first )
	{
		first = 0;

		// ���O�t�@�C�����J��
		if( (cgi_logfp = fopen(cgi_logfile, "a") ) == 0 )
		{
			printf("*WARNING* : can't open cgi log file [%s]\n", logfile);
		}
	}

	// ���O�t�@�C�����J���ĂȂ�
	if( !cgi_logfp )
		return;

	// ���ԕ���������߂�
	{
		size_t len;
		time_t time_;
		time(&time_);
        len = strftime(timestr,sizeof(timestr),"%d/%b/%Y:%H:%M:%S",localtime(&time_) );
        snprintf(timestr+len, sizeof(timestr) - (size_t)len, " %c%02d%02d", sign[(tz<0)?1:0], abs(tz)/60, abs(tz)%60 );
	}

	ip = sd ? (unsigned char*) &session[sd->fd]->client_addr.sin_addr : 0;

	fprintf( cgi_logfp, "%%%% [%s] %s\n%%%% %d %s" NEWLINE, timestr, sd->request_line, status, sd->url );

	fflush( cgi_logfp );
}
*/
#else	// ifndef NO_HTTPD_CGI

// ==========================================
// cgi �𗘗p���Ȃ�
// ------------------------------------------
void httpd_page_external_cgi( struct httpd_session_data* sd ) { return; }
void httpd_page_external_cgi_disconnect( struct httpd_session_data* sd ) { return; }
void httpd_page_external_cgi_final(void) { return; }

#endif

// ******************************************
// �O�� cgi ���� �����܂�
// ******************************************


// ==========================================
// URL �G���R�[�h
// ------------------------------------------
char* httpd_binary_encode(const char* val)
{
	char *buf = (char *)aMalloc(strlen(val) * 3 + 1);
	char *p   = buf;

	while(*val) {
		if(isalnum((unsigned char)*val)) {
			*(p++) = *(val++);
		} else {
			unsigned char c1 = *(val++);
			unsigned char c2 = (c1 >> 4);
			unsigned char c3 = (c1 & 0x0F);
			*(p++) = '%';
			*(p++) = c2 + (c2 >= 10 ? 'A'-10 : '0');
			*(p++) = c3 + (c3 >= 10 ? 'A'-10 : '0');
		}
	}
	*p = 0;
	return buf;
}

// ==========================================
// http �̃��^�����̃N�H�[�g
// ------------------------------------------
char* httpd_quote_meta(const char* p1)
{
	char *buf = (char *)aMalloc(strlen(p1) * 6 + 1);
	char *p2  = buf;

	while(*p1) {
		switch(*p1) {
		case '<': memcpy(p2,"&lt;",4);   p2 += 4; p1++; break;
		case '>': memcpy(p2,"&gt;",4);   p2 += 4; p1++; break;
		case '&': memcpy(p2,"&amp;",5);  p2 += 5; p1++; break;
		case '"': memcpy(p2,"&quot;",6); p2 += 6; p1++; break;
		default: *(p2++) = *(p1++);
		}
	}
	*p2 = 0;
	return buf;
}

// ==========================================
// �R���t�B�O - �F�؃��[�U�[�̒ǉ�
// ------------------------------------------
void httpd_config_read_add_authuser( struct httpd_access *a, const char *name, const char *passwd )
{
	struct httpd_access_user* au;
	int type;

	if( strlen(name) >= sizeof(a->user->name) )
	{
		printf("httpd_config_read: authuser: too long name [%s]\n", name);
		return;
	}

	if( memcmp( passwd, "$MD5$", 5 )==0 && strlen( passwd )==32+5 )		// MD5 �p�X���[�h
	{
		type = HTTPD_USER_PASSWD_MD5;
		passwd += 5;
	}
	else if( memcmp( passwd, "$Digest$", 8 )==0 && strlen( passwd )==32+8 )	// Digest �F�؂� A1
	{
		type = HTTPD_USER_PASSWD_DIGEST;
		passwd += 8;
	}
	else	// �v���[��
	{
		if( strlen( passwd ) >= sizeof( au->passwd ) )
		{
			printf("httpd_config_read: authuser: too long passwd (user[%s])\n", name);
			return;
		}

		type = HTTPD_USER_PASSWD_PLAIN;
	}

	// �K�v�Ȃ烁�������g��
	if( a->user_count == a->user_max )
	{
		a->user_max += 16;
		a->user = (struct httpd_access_user *)aRealloc( a->user, sizeof(struct httpd_access_user) * a->user_max );
	}

	// ���[�U�[�ǉ�
	au = a->user + (a->user_count++);
	strcpy( au->name, name );
	strcpy( au->passwd, passwd );
	au->type = type;

	// Digest �F�؃��[�h�ŁA�v���[���p�X���[�h�������ꍇ�A���炩���� A1 ���v�Z���Ă���
	if( (a->type & HTTPD_ACCESS_AUTH_MASK) == HTTPD_ACCESS_AUTH_DIGEST && au->type == HTTPD_USER_PASSWD_PLAIN )
	{
		char buf[512];
		au->type = HTTPD_USER_PASSWD_DIGEST;
		sprintf( buf, "%s:%s:%s", name, a->realm, passwd );
		MD5_String( buf, au->passwd );
	}
}

// ==========================================
// �R���t�B�O - ����/�֎~ IP �̒ǉ�
// ------------------------------------------
static void httpd_config_read_add_ip( unsigned long **list, int *count, int *max, const char *w2 )
{
	int i1,i2,i3,i4, m1,m2,m3,m4;
	unsigned long ip, mask;
	unsigned char *pip = (unsigned char *)&ip, *pmask = (unsigned char *)&mask;

	if( strcasecmp( w2,"clear" ) == 0 )	// clear
	{
		aFree( *list );
		*list = NULL;
		*count = *max = 0;
	}
	else if( strcasecmp( w2,"all") == 0 )	// all
	{
		ip = mask = 0;
	}
	else if( sscanf( w2, "%d.%d.%d.%d/%d.%d.%d.%d", &i1, &i2, &i3, &i4, &m1, &m2, &m3, &m4 )==8 )	// 192.168.0.0/255.255.255.0 �`��
	{
		pip[0] = i1;		pip[1] = i2;		pip[2] = i3;		pip[3] = i4;
		pmask[0] = m1;		pmask[1] = m2;		pmask[2] = m3;		pmask[3] = m4;
	}
	else if( sscanf( w2,"%d.%d.%d.%d/%d", &i1, &i2, &i3, &i4, &m1 )==5 )	// 192.168.0.0/24 �`��
	{
		int bit = 0xffffffff << (32-m1);
		pip[0] = i1;		pip[1] = i2;		pip[2] = i3;		pip[3] = i4;
		pmask[0] = (bit>>24);		pmask[1] = (bit>>16);
		pmask[2] = (bit>>8);		pmask[3] = bit;
	}
	else if( sscanf( w2,"%d.%d.%d.%d", &i1, &i2, &i3, &i4 )==4 )	// 192.168.0.1 �`�� (�T�u�l�b�g�}�X�N 255.255.255.255 )
	{
		pip[0] = i1;		pip[1] = i2;		pip[2] = i3;		pip[3] = i4;
		pmask[0] = 0xff;	pmask[1] = 0xff;	pmask[2] = 0xff;	pmask[3] = 0xff;
	}
	else if( sscanf( w2,"%d.%d.%d", &i1, &i2, &i3 )==3 )	// 192.168.0 �`���i�T�u�l�b�g�}�X�N 255.255.255.0�j
	{
		pip[0] = i1;		pip[1] = i2;		pip[2] = i3;		pip[3] = 0;
		pmask[0] = 0xff;	pmask[1] = 0xff;	pmask[2] = 0xff;	pmask[3] = 0;
	}
	else if( sscanf( w2,"%d.%d", &i1, &i2 )==2 )	// 192.168 �`���i�T�u�l�b�g�}�X�N 255.255.0.0�j
	{
		pip[0] = i1;		pip[1] = i2;		pip[2] = 0;			pip[3] = 0;
		pmask[0] = 0xff;	pmask[1] = 0xff;	pmask[2] = 0;		pmask[3] = 0;
	}
	else	// 192 �`���i�T�u�l�b�g�}�X�N 255.0.0.0 �j
	{
		pip[0] = i1;		pip[1] = 0;			pip[2] = 0;			pip[3] = 0;
		pmask[0] = 0xff;	pmask[1] = 0;		pmask[2] = 0;		pmask[3] = 0;
	}

	// �K�v�Ȃ烁�������g��
	if( *count == *max )
	{
		unsigned long *iplist = (unsigned long *)aMalloc( sizeof(unsigned long) * (*max + 16) );
		if( *list )
		{
			memcpy( iplist, *list, sizeof(unsigned long) * (*count) );
			aFree( *list );
		}
		*list = iplist;
		*max += 16;
	}

	// IP �ƃ}�X�N�ǉ�
	(*list)[ (*count)++ ] = ip&mask;
	(*list)[ (*count)++ ] = mask;
}

#define CHECK_ACCES_TARGET(msg)	if( !a ) { printf( msg ": no target url.\n" ); continue; }

// ==========================================
// �ݒ�t�@�C����ǂݍ���
// ------------------------------------------
int httpd_config_read(const char *cfgName)
{
	char line[1024],w1[1024],w2[1024];
	FILE *fp;
	struct httpd_access *a = NULL;

	fp=fopen(cfgName,"r");
	if(fp==NULL){
		printf("file not found: %s\n",cfgName);
		return 1;
	}
	while(fgets(line,1020,fp)){
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0] == '/' && line[1] == '/')
			continue;
		if(sscanf(line,"%1023[^:]: %1023[^\r\n]",w1,w2) != 2)
			continue;

		if(strcasecmp(w1,"enable")==0)
		{
			socket_enable_httpd( atoi(w2) );
		}
		else if(strcasecmp(w1,"log_filename")==0)
		{
			strncpy( logfile, w2, sizeof(logfile) - 1 );
		}
		else if(strcasecmp(w1,"request_timeout_first")==0)
		{
			httpd_set_request_timeout( 0, atoi(w2) );
		}
		else if(strcasecmp(w1,"request_timeout_persist")==0)
		{
			httpd_set_request_timeout( 1, atoi(w2) );
		}
		else if(strcasecmp(w1,"max_persist_requests")==0)
		{
			httpd_set_max_persist_requests( atoi(w2) );
		}
		else if(strcasecmp(w1,"timezone")==0)
		{
			if( strcasecmp(w2,"auto") == 0)
				httpd_set_timezone( -1 );
			else
				httpd_set_timezone( atoi(w2)*(-60) );
		}
		else if(strcasecmp(w1,"auth_digest_period")==0)
		{
			httpd_set_auth_digest_period( atoi(w2) );
		}
		else if(strcasecmp(w1,"log_no_flush")==0)
		{
			log_no_flush = atoi(w2);
		}
		else if(strcasecmp(w1,"max_uri_length")==0)
		{
			max_uri_length = atoi(w2);
		}
		else if(strcasecmp(w1,"server_max_requests_per_second")==0)
		{
			server_max_requests_per_second = atoi(w2);
		}
		else if(strcasecmp(w1,"server_max_requests_period")==0)
		{
			server_max_requests_period = atoi(w2);
		}
		else if(strcasecmp(w1,"cgi_enable")==0)
		{
			httpd_cgi_enable = atoi(w2);
		}
		else if(strcasecmp(w1,"max_cgi_process")==0)
		{
			httpd_max_cgi_process = atoi(w2);
		}
		else if(strcasecmp(w1,"cgi_process_timeout")==0)
		{
			httpd_cgi_timeout = atoi(w2);
		}
		else if(strcasecmp(w1,"cgi_kill_timeout")==0)
		{
			httpd_cgi_kill_timeout = atoi(w2);
		}
		else if(strcasecmp(w1,"cgi_temp_dir")==0)
		{
			strncpy( httpd_cgi_temp_dir, w2, sizeof(httpd_cgi_temp_dir) - 1 );
		}
		else if(strcasecmp(w1,"cgi_server_name")==0)
		{
			strncpy( httpd_cgi_server_name, w2, sizeof(httpd_cgi_server_name) - 1 );
		}
		else if(strcasecmp(w1,"log_format")==0)
		{
			httpd_log_format = atoi(w2);
		}
		else if(strcasecmp(w1,"document_root")==0)
		{
			httpd_set_document_root( w2 );
		}
		else if( strcasecmp(w1,"target")==0 )
		{
			if( strcasecmp( w2,"clear" )==0 )		// clear
			{
				int i;
				for( i=0; i<htaccess_count; i++ )
				{
					if(htaccess[i]->dip)  aFree( htaccess[i]->dip );
					if(htaccess[i]->aip)  aFree( htaccess[i]->aip );
					if(htaccess[i]->user) aFree( htaccess[i]->user );
					aFree( htaccess[i] );
				}
				aFree( htaccess );
				htaccess = NULL;
				htaccess_count = htaccess_max = 0;
				a = NULL;
			}
			else if( strcasecmp( w2,"none" )==0 ||  strcasecmp( w2,"end" )==0 )
			{
				a = NULL;
			}
			else if( *w2!='/' )		// '/' ����n�܂��Ă��Ȃ�
			{
				printf("httpd_config_read: target url must start root (/).\n");
			}
			else
			{
				// �����̃f�[�^�̕ύX���ǂ���������
				int i;
				for( i=0; i<htaccess_count; i++ )
				{
					if( strcmp( htaccess[i]->url, w2 ) == 0 )
					{
						a = htaccess[i];
						break;
					}
				}

				if( i==htaccess_count )				// �V�K�쐬
				{
					// �K�v�Ȃ烁�������g��
					int j;
					if( htaccess_count==htaccess_max )
					{
						htaccess_max += 16;
						htaccess = (struct httpd_access **)aRealloc( htaccess, sizeof(struct httpd_access*) * htaccess_max );
					}
					// �f�[�^�̒ǉ���������
					a = htaccess[ htaccess_count++ ] = (struct httpd_access *)aMalloc( sizeof( struct httpd_access ) );
					a->type = HTTPD_ACCESS_ALWAYS;
					a->aip_count = a->aip_max = 0;
					a->dip_count = a->dip_max = 0;
					a->user_count= a->user_max= 0;
					a->aip = a->dip = NULL;
					a->user = NULL;
					a->url[0]= '\0';
					a->urllen = 0;
					a->auth_func_id = 0;
					strcpy( a->realm, "Auriga Authorization" );
					if( strlen(w2)>=sizeof(a->url) )
						printf("httpd_config_read: too long target url [%s]\n", w2);
					else
					{
						strcpy( a->url, w2 );
						a->urllen = strlen(a->url);
					}

					// digest �F�ؗp�̃v���C�x�[�g�L�[�쐬
					for( j=0; j<atn_rand()%10+20; j++ )
					{
						a->privkey[j] = (atn_rand()%250)+1;
					}
					a->privkey[j]='\0';
				}
			}
		}
		else if(strcasecmp(w1,"satisfy")==0 )
		{
			int i = (strcasecmp(w2,"any")==0)? HTTPD_ACCESS_SAT_ANY : (strcasecmp(w2,"all")==0)? HTTPD_ACCESS_SAT_ALL : -1;
			CHECK_ACCES_TARGET("satisfy");
			if( i<0 )
				printf("httpd_config_read: satisfy: unknown satisfy option [%s]\n", w2);
			else
				a->type = (a->type & ~HTTPD_ACCESS_SAT_MASK) | i;
		}
		else if(strcasecmp(w1,"authtype")==0)
		{
			int i = (strcasecmp(w2,"basic")==0)? HTTPD_ACCESS_AUTH_BASIC :
					(strcasecmp(w2,"digest")==0)? HTTPD_ACCESS_AUTH_DIGEST :
					(strcasecmp(w2,"none")==0)? HTTPD_ACCESS_AUTH_NONE : -1;
			CHECK_ACCES_TARGET("authtype");
			if( i<0 )
				printf("httpd_config_read: authtype: unknown authtype [%s]\n", w2);
			else
				a->type = (a->type & ~HTTPD_ACCESS_AUTH_MASK) | i;
		}
		else if(strcasecmp(w1,"authfunc")==0)
		{
			int i = atoi(w2);
			CHECK_ACCES_TARGET("authfunc");
			if( i<0 || i>=sizeof(auth_func)/sizeof(auth_func[0]) )
				printf("httpd_config_read: authfunc: unknown func id [%d]\n", i);
			else
				a->auth_func_id = i;
		}
		else if(strcasecmp(w1,"authname")==0 || strcasecmp(w1,"authrealm")==0 )
		{
			CHECK_ACCES_TARGET("authname");
			if( strlen(w2)>=sizeof(a->realm) )
				printf("httpd_config_read: %s: too long realm [%s]\n", w1, w2);
			else
				strcpy( a->realm, w2 );
		}
		else if(strcasecmp(w1,"authuser")==0 )
		{
			char u[1024], p[1024];
			CHECK_ACCES_TARGET("authuser");
			if( sscanf(w2,"%1023[^:]:%1023s",u,p) == 2 )
			{
				httpd_config_read_add_authuser( a, u, p );
			}
			else if( strcasecmp(w2,"clear") == 2 )
			{
				aFree( a->user );
				a->user_count = a->user_max = 0;
			}
			else	// �O���t�@�C���ǂݍ��߂��肷��Ƃ�����������
			{
				printf("httpd_config_read: authuser: [user:pass] needed\n");
			}
		}
		else if(strcasecmp(w1,"order")==0 )
		{
			int i = (strcasecmp(w2,"deny,allow"    )==0)? HTTPD_ACCESS_IP_DENY   :
					(strcasecmp(w2,"allow,deny"    )==0)? HTTPD_ACCESS_IP_ALLOW  :
					(strcasecmp(w2,"mutual-failure")==0)? HTTPD_ACCESS_IP_MUTUAL :
					(strcasecmp(w2,"none"			)==0)? HTTPD_ACCESS_IP_NONE   : -1;
			CHECK_ACCES_TARGET("order");
			if( i<0 )
				printf("httpd_config_read: order: unknown order option [%s]\n", w2);
			else
				a->type = (a->type & ~HTTPD_ACCESS_IP_MASK) | i;
		}
		else if(strcasecmp(w1,"allow")==0 )
		{
			CHECK_ACCES_TARGET("allow");
			httpd_config_read_add_ip( &a->aip, &a->aip_count, &a->aip_max, w2 );
		}
		else if(strcasecmp(w1,"deny")==0 )
		{
			CHECK_ACCES_TARGET("deny");
			httpd_config_read_add_ip( &a->dip, &a->dip_count, &a->dip_max, w2 );
		}
		else if(strcasecmp(w1,"cgi_ext_list")==0 )
		{
			char* p = a ? a->cgi_ext_list : httpd_cgi_ext_list;
			if( strcasecmp(w2,"none") == 0 )
			{
				p[0]='\0';
			}
			else if( strlen(w2) > sizeof(httpd_cgi_ext_list)-2 )
			{
				printf("httpd_config_read: cgi_ext_list: too long extensions list [%s]\n", w2);
			}
			else
			{
				sprintf( p, "%s ", w2 );
			}
		}
		else if(strcasecmp(w1,"import")==0)
		{
			httpd_config_read(w2);
		}
		else
		{
			printf("httpd_config_read: unknown option [%s: %s]\n",w1,w2);
		}
	}
	fclose(fp);

	return 0;
}

// ==========================================
// Base64 �f�R�[�h�p�w���p
// ------------------------------------------
static int httpd_decode_base64_code2value(unsigned char c)
{
	if( (c >= 'A') && (c <= 'Z') ) {
		return c - 'A';
	}
	else if( (c >= 'a') && (c <= 'z') ) {
		return (c - 'a') +26;
	}
	else if( (c >= '0') && (c <= '9') ) {
		return (c - '0') +52;
	}
	else if( '+' == c ) {
		return 62;
	}
	else if( '/' == c ) {
		return 63;
	}
	else if( '=' == c ) {
		return 0;
	}
	else {
		return -1;
	}
}

// ==========================================
// Base64 �f�R�[�h
// ------------------------------------------
int httpd_decode_base64( char *dest, const char *src)
{
	int c=0;

	while( *src && *src>0x20 && c>=0 )
	{
		int j;
		int b=0;

		for( j=0; j<4; j++, src++ )
		{
			c=httpd_decode_base64_code2value( *src );
			b = ( b<<6 ) | ((c<0)?0:c);
		}
		*(dest++) = b>>16;
		*(dest++) = b>>8;
		*(dest++) = b;
	}
	*dest = '\0';
	return 1;
}

