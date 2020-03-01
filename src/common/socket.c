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

// $Id: socket.c,v 1.2 2004/09/15 00:17:17 running_pinata Exp $
// original : core.c 2003/02/26 18:03:12 Rev 1.7

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#ifdef WINDOWS
	#include <winsock.h>
	#include <windows.h>
	#pragma comment(lib,"ws2_32.lib")
#else
	#include <netdb.h>
	#include <sys/socket.h>
	#include <sys/select.h>
	#include <netinet/in.h>
	#include <netinet/tcp.h>
	#include <unistd.h>
	#include <sys/time.h>
	#include <arpa/inet.h>
#endif
#include <errno.h>
#include <fcntl.h>
#include <string.h>

#include "mmo.h"
#include "httpd.h"
#include "timer.h"
#include "socket.h"
#include "malloc.h"
#include "utils.h"

// socket.h でdefine されたcloseを置き換え
#ifdef WINDOWS
	#undef close
	#define close(id) do{ if(session[id]) closesocket(session[id]->socket); } while(0);
	#define sockfd(fd) (session[fd]->socket)
	static void SessionInsertSocket(const SOCKET elem, int pos2);
	static void SessionRemoveSocket(const SOCKET elem);
#else
	#undef close
	#define sockfd(fd) (fd)
#endif

fd_set readfds;
int fd_max;

#define RFIFO_SIZE (2*1024) /* a player that send more than 2k is probably a hacker without be parsed */
                            /* biggest known packet: S 0153 <len>.w <emblem data>.?B -> 24x24 256 color .bmp (0153 + len.w + 1618/1654/1756 bytes) and it's ziped packet! */
#define WFIFO_SIZE (64*1024)
#define RFIFOSIZE_HTTPD (32*1024)
#define WFIFOSIZE_HTTPD (64*1024)

unsigned long listen_ip = 0; // by default: any adresses are binded

struct socket_data *session[FD_SETSIZE];
static int null_parse(int fd);
static int (*default_func_parse)(int) = null_parse;
static int (*default_func_destruct)(int) = NULL;

static int httpd_enable = 1;
void socket_enable_httpd(int flag) { if (flag >= 0) httpd_enable = flag; }

static int socket_ctrl_panel_httpd = 1;
void socket_enable_ctrl_panel_httpd(int flag) { socket_ctrl_panel_httpd = flag; }
static char socket_ctrl_panel_url[256] = "/socketctrl";
const char* get_socket_ctrl_panel_url(void) { return socket_ctrl_panel_url; }

static int unauth_timeout = 10 * 1000;
static int auth_timeout   = 10 * 60 * 1000;

static int send_limit_buffer_size     = 128 * 1024;

static int recv_limit_rate_enable     = 1;
static int recv_limit_rate_period     = 500;
static int recv_limit_rate_bytes      = 1024;
static int recv_limit_rate_wait_max   = 2000;
static int recv_limit_rate_disconnect = 5000;

static int connect_check(unsigned long ip);

/*======================================
 *	CORE : Set function
 *--------------------------------------
 */
void set_defaultparse(int (*defaultparse)(int))
{
	default_func_parse = defaultparse;

	return;
}

void set_sock_destruct(int (*func_destruct)(int))
{
	default_func_destruct = func_destruct;

	return;
}

/*======================================
 *	CORE : Socket Sub Function
 *--------------------------------------
 */
static int recv_to_fifo(int fd)
{
	int len;
	unsigned int tick = gettick();
	struct socket_data* sd = session[fd];

	//printf("recv_to_fifo : %d %d\n", fd, sd->eof);

	if (sd->eof || (recv_limit_rate_enable && sd->auth >= 0 && DIFF_TICK(sd->rlr_tick, tick) > 0))	// 帯域制限中
		return -1;

	len = recv(sockfd(fd), sd->rdata_size, (int)RFIFOSPACE(fd), 0);
	//{ int i; printf("recv %d : ", fd); for(i = 0; i < len; i++) { printf("%02x ", sd->rdata_size[i]); } printf("\n"); }
	if (len > 0) {
		sd->rdata_size += len;

		// if not a player and not a http request (so if it's a server)
#ifdef NO_HTTPD
		if (sd->max_rdata - sd->rdata > RFIFO_SIZE) {
#else
		if (sd->max_rdata - sd->rdata > RFIFO_SIZE && sd->func_parse != httpd_parse) {
#endif
			if (sd->max_rdata == sd->rdata_size && (sd->rdata_pos - sd->rdata) < RFIFOSIZE_SERVERLINK) // read data is full and is used for less than step (RFIFOSIZE_SERVERLINK)
				realloc_fifo(fd, (sd->max_rdata - sd->rdata) + RFIFOSIZE_SERVERLINK, 0); // increase read buffer of 1 step for next time
		}

//		printf("rs: %d %d\n",len, session[fd]->auth );
		// 帯域制限用の計算
		if (sd->auth >= 0) {
			int tick_diff = DIFF_TICK(tick, sd->rlr_tick);
			sd->rlr_bytes += len;

			// 帯域の制限
			if (tick_diff >= recv_limit_rate_period) {
				int rate = sd->rlr_bytes * 1000 / tick_diff;
//				printf("rlr: %d %d\n", sd->rlr_bytes, rate);
				if (rate > recv_limit_rate_bytes) {
					int wait = (rate - recv_limit_rate_bytes) * tick_diff / recv_limit_rate_bytes;
					if (wait > recv_limit_rate_wait_max)
						wait = recv_limit_rate_wait_max;
					sd->rlr_tick += wait;
					if ((sd->rlr_disc += wait) > (unsigned int)recv_limit_rate_disconnect) {
						sd->eof = 1;
						return -1;
					}
//					printf("rlr: on! %d %d tick wait\a\n", (rate - recv_limit_rate_bytes) * tick_diff / recv_limit_rate_bytes, wait);
				} else {
					sd->rlr_tick = tick;
					sd->rlr_disc = 0;
				}

				sd->rlr_bytes = 0;
			}
		}

#ifdef WINDOWS
	} else if (len == 0 || len == SOCKET_ERROR) {
#else
	} else if (len <= 0) {
#endif
		// printf("set eof :%d\n", fd);
		sd->eof = 1;
	}

	return 0;
}

static int send_from_fifo(int fd)
{
	int len;
	struct socket_data *sd = session[fd];

	//printf("send_from_fifo : %d\n",fd);
	if (sd->eof || WFIFOREST(fd) == 0)
		return -1;

	len = send(sockfd(fd), sd->wdata_pos, (int)WFIFOREST(fd), 0);
	//{ int i; printf("send %d : ", fd); for(i = 0; i < len; i++) { printf("%02x ", session[fd]->wdata_pos[i]); } printf("\n"); }
	if (len > 0) {
		sd->wdata_pos += len;
		if (sd->wdata_pos == sd->wdata_size) {
			sd->wdata_size = sd->wdata;
			sd->wdata_pos  = sd->wdata;
		} else if ((sd->wdata_pos - sd->wdata) * 8 > (sd->max_wdata - sd->wdata)) {
			// クリアする間隔を減らしてみる
			memmove(sd->wdata, sd->wdata_pos, WFIFOREST(fd));
			sd->wdata_size = sd->wdata + WFIFOREST(fd);
			sd->wdata_pos  = sd->wdata;
		}
#ifdef WINDOWS
	} else if (len == 0 || len == SOCKET_ERROR) {
#else
	} else {
#endif
		// printf("set eof :%d\n", fd);
		sd->eof = 1;
	}

	return 0;
}

static int null_parse(int fd)
{
	printf("null_parse : session #%d\n", fd);
	RFIFOSKIP(fd,RFIFOREST(fd));

	return 0;
}

/*======================================
 *	CORE : Socket Function
 *--------------------------------------
 */
#ifdef WINDOWS
// not started, not use shutdown(fd, SD_BOTH);
#define socket_close(fd) closesocket((fd))
#else
#define socket_close(fd) close((fd))
#endif

static int connect_client(int listen_fd)
{
	int len, yes, pos;
	struct sockaddr_in client_address;
	unsigned int tick;
#ifdef WINDOWS
	SOCKET fd;
#else
	int fd;
#endif

	len = sizeof(client_address);

#ifdef WINDOWS
	fd = accept(session[listen_fd]->socket, (struct sockaddr*)&client_address, &len);
	if (fd == SOCKET_ERROR || fd == INVALID_SOCKET)
		return -1;
#else
	fd = accept(listen_fd, (struct sockaddr*)&client_address, &len);
	if (fd == -1)
		return -1;
#endif

	yes = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&yes, sizeof yes) != 0) {
		socket_close(fd);
		return -1;
	}
#ifdef SO_REUSEPORT
	yes = 1; // set again value. it can be changed by previous call
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, (char *)&yes, sizeof yes) != 0) {
		socket_close(fd);
		return -1;
	}
#endif
	yes = 1; // set again value. it can be changed by previous call
	if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (char *)&yes, sizeof yes) != 0) {
		socket_close(fd);
		return -1;
	}

#ifdef WINDOWS
	{
		// Set the socket I/O mode: In this case FIONBIO
		// enables or disables the blocking mode for the
		// socket based on the numerical value of iMode.
		// If iMode = 0, blocking is enabled;
		// If iMode != 0, non-blocking mode is enabled.
		unsigned long iMode = 1;
		if (ioctlsocket(fd, FIONBIO, &iMode) != 0) { // http://msdn.microsoft.com/library/default.asp?url=/library/en-us/winsock/winsock/ioctlsocket_2.asp
			closesocket(fd); // not started, not use shutdown(fd, SD_BOTH);
			return -1;
		}
	}
#else
	if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1) {
		close(fd);
		return -1;
	}
#endif

#ifdef WINDOWS
	// Don't use the SO_LINGER option that destroy unsent socket's data immediately if closesocket() is called. [Eoe]
	// A problem exists on http that closes immediatly the connection.
	// SO_LINGER option -> http://msdn.microsoft.com/library/default.asp?url=/library/en-us/winsock/winsock/closesocket_2.asp
	// setsockopt(fd, SOL_SOCKET, SO_LINGER, (char*)&opt, sizeof(opt));
#endif

	if (!connect_check((unsigned long)client_address.sin_addr.s_addr)) {
		socket_close(fd);
		return -1;
	}

#ifndef WINDOWS
	// check array (in win32, the macro FD_CLR, FD_ISSET, FD_SET and FD_ZERO don't use array based on FD_SETSIZE [Eoe])
	if (fd < 1 || fd >= FD_SETSIZE) { // don't check fd = 0, keyboard
		close(fd);
		return -1;
	}
#endif
	FD_SET(fd, &readfds);

#ifdef WINDOWS
	pos = 2;
	while(session[pos] != NULL && pos < fd_max)
		pos++;
	SessionInsertSocket(fd, pos);
#else
	pos = fd;
#endif

	tick = gettick();

	session[pos] = (struct socket_data *)aCalloc(1, sizeof(*session[pos]));
	session[pos]->func_recv   = recv_to_fifo;
	session[pos]->func_send   = send_from_fifo;
	session[pos]->func_parse  = default_func_parse;
	session[pos]->client_addr = client_address;
#ifdef WINDOWS
	session[pos]->socket      = fd;
#endif
	session[pos]->tick        = tick;
	session[pos]->auth        = 0;
	session[pos]->rlr_tick    = tick;
	session[pos]->rlr_bytes   = 0;
	session[pos]->rlr_disc    = 0;
	session[pos]->server_port = session[listen_fd]->server_port;

	session[pos]->func_destruct = default_func_destruct;
	realloc_fifo(pos, RFIFO_SIZE, WFIFO_SIZE);

	if (fd_max <= pos)
		fd_max = pos + 1;

	return pos;
}

int make_listen_port(unsigned short port, unsigned long sip)
{
	struct sockaddr_in server_address;
	int yes, pos;
	unsigned long result;
#ifdef WINDOWS
	SOCKET fd;
#else
	int fd;
#endif

	fd = socket(AF_INET, SOCK_STREAM, 0); // under winsock: SOCKET type is unsigned (http://msdn.microsoft.com/library/default.asp?url=/library/en-us/winsock/winsock/porting_socket_applications_to_winsock.asp)
#ifdef WINDOWS
	if (fd == INVALID_SOCKET) {
#else
	if (fd == -1) {
#endif
		perror("make_listen_port: socket error: Unable to open socket (socket.c).");
		exit(1);
	}

	yes = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&yes, sizeof yes) != 0) {
		perror("make_listen_port: setsockopt (SO_REUSEADDR) error (socket.c).");
		socket_close(fd);
		exit(1);
	}
#ifdef SO_REUSEPORT
	yes = 1; // set again value. it can be changed by previous call
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, (char *)&yes, sizeof yes) != 0) {
		perror("make_listen_port: setsockopt (SO_REUSEPORT) error (socket.c).");
		socket_close(fd);
		exit(1);
	}
#endif
	yes = 1; // set again value. it can be changed by previous call
	if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (char *)&yes, sizeof yes) != 0) {
		perror("make_listen_port: setsockopt (TCP_NODELAY) error (socket.c).");
		socket_close(fd);
		exit(1);
	}

#ifdef WINDOWS
	{
		// Set the socket I/O mode: In this case FIONBIO
		// enables or disables the blocking mode for the
		// socket based on the numerical value of iMode.
		// If iMode = 0, blocking is enabled;
		// If iMode != 0, non-blocking mode is enabled.
		unsigned long iMode = 1;
		if (ioctlsocket(fd, FIONBIO, &iMode) != 0) { // http://msdn.microsoft.com/library/default.asp?url=/library/en-us/winsock/winsock/ioctlsocket_2.asp
			perror("make_listen_port: ioctlsocket error (socket.c).");
			closesocket(fd); // not started, not use shutdown(fd, SD_BOTH);
			exit(1);
		}
	}
#else
	if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1) {
		perror("make_listen_port: fcntl error (socket.c).");
		close(fd);
		exit(1);
	}
#endif

#ifdef WINDOWS
	// Don't use the SO_LINGER option that destroy unsent socket's data immediately if closesocket() is called. [Eoe]
	// A problem exists on http that closes immediatly the connection.
	// SO_LINGER option -> http://msdn.microsoft.com/library/default.asp?url=/library/en-us/winsock/winsock/closesocket_2.asp
	// setsockopt(fd, SOL_SOCKET, SO_LINGER, (char*)&opt, sizeof(opt));
#endif

	server_address.sin_family      = AF_INET;
	server_address.sin_addr.s_addr = sip;		// 1710:INADDR_ANYから変更
	server_address.sin_port        = htons(port);

	result = bind(fd, (struct sockaddr*)&server_address, sizeof(server_address));
	if (result != 0) { // error when not 0 (can be -1 or any other value)
		perror("make_listen_port: bind error (socket.c).");
		socket_close(fd);
		exit(1);
	}

	result = listen(fd, 5);
	if (result != 0) { // error when not 0 (can be -1 or any other value)
		perror("make_listen_port: listen error (socket.c).");
		socket_close(fd);
		exit(1);
	}

#ifdef WINDOWS
	// check array (in win32, the macro FD_CLR, FD_ISSET, FD_SET and FD_ZERO don't use array based on FD_SETSIZE [Eoe])
	if (fd < 1 || fd >= FD_SETSIZE) { // don't check fd = 0, keyboard
		perror("make_listen_port: fd < 1 || fd >= FD_SETSIZE error (socket.c).");
		close(fd);
		exit(1);
	}
#endif

	FD_SET(fd, &readfds);

#ifdef WINDOWS
	pos = 2;
	while(session[pos] != NULL && pos < fd_max)
		pos++;
	SessionInsertSocket(fd, pos);
#else
	pos = fd;
#endif

	session[pos]              = (struct socket_data *)aCalloc(1, sizeof(*session[pos]));
	session[pos]->func_recv   = connect_client;
	session[pos]->auth        = -1;
	session[pos]->server_port = port;
#ifdef WINDOWS
	session[pos]->socket      = fd;
#endif

	if (fd_max <= pos)
		fd_max = pos + 1;

	return pos;
}


int make_connection(unsigned long ip, unsigned short port)
{
	struct sockaddr_in server_address;
	int yes, pos;
	unsigned long result;
	unsigned int tick;
#ifdef WINDOWS
	SOCKET fd;
#else
	int fd;
#endif

	fd = socket(AF_INET, SOCK_STREAM, 0); // under winsock: SOCKET type is unsigned (http://msdn.microsoft.com/library/default.asp?url=/library/en-us/winsock/winsock/porting_socket_applications_to_winsock.asp)
#ifdef WINDOWS
	if (fd == INVALID_SOCKET) {
#else
	if (fd == -1) {
#endif
		perror("make_connection : socket error (socket.c).");
		return -1;
	}

	yes = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&yes, sizeof yes) != 0) {
		perror("make_connection: setsockopt (SO_REUSEADDR) error (socket.c).");
		socket_close(fd);
		return -1;
	}
#ifdef SO_REUSEPORT
	yes = 1; // set again value. it can be changed by previous call
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, (char *)&yes, sizeof yes) != 0) {
		perror("make_connection: setsockopt (SO_REUSEPORT) error (socket.c).");
		socket_close(fd);
		return -1;
	}
#endif
	yes = 1; // set again value. it can be changed by previous call
	if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (char *)&yes, sizeof yes) != 0) {
		perror("make_connection: setsockopt (TCP_NODELAY) error (socket.c).");
		socket_close(fd);
		return -1;
	}

#ifdef WINDOWS
	{
		// Set the socket I/O mode: In this case FIONBIO
		// enables or disables the blocking mode for the
		// socket based on the numerical value of iMode.
		// If iMode = 0, blocking is enabled;
		// If iMode != 0, non-blocking mode is enabled.
		unsigned long iMode = 1;
		if (ioctlsocket(fd, FIONBIO, &iMode) != 0) { // http://msdn.microsoft.com/library/default.asp?url=/library/en-us/winsock/winsock/ioctlsocket_2.asp
			perror("make_connection: ioctlsocket error (socket.c).");
			closesocket(fd); // not started, not use shutdown(fd, SD_BOTH);
			return -1;
		}
	}
#else
	if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1) {
		perror("make_connection: fcntl error (socket.c).");
		close(fd);
		return -1;
	}
#endif

#ifdef WINDOWS
	// Don't use the SO_LINGER option that destroy unsent socket's data immediately if closesocket() is called. [Eoe]
	// A problem exists on http that closes immediatly the connection.
	// SO_LINGER option -> http://msdn.microsoft.com/library/default.asp?url=/library/en-us/winsock/winsock/closesocket_2.asp
	// setsockopt(fd, SOL_SOCKET, SO_LINGER, (char*)&opt, sizeof(opt));
#endif

	server_address.sin_family      = AF_INET;
	server_address.sin_addr.s_addr = ip;
	server_address.sin_port        = htons(port);

	result = connect(fd, (struct sockaddr *)(&server_address), sizeof(struct sockaddr_in));
	if (result != 0) {
		// 接続失敗
#ifdef WINDOWS
		if (WSAGetLastError() != WSAEWOULDBLOCK) {
			printf("make_connection: connect error (socket.c) %08x:%d\n", (int)ip, port);
			closesocket(fd); // not started, not use shutdown(fd, SD_BOTH);
			return -1;
		}
#else
		if (errno != EINPROGRESS) {
			printf("make_connection: connect error (socket.c) %08x:%d\n", (int)ip, port);
			close(fd);
			return -1;
		}
#endif
	}

#ifdef WINDOWS
	// check array (in win32, the macro FD_CLR, FD_ISSET, FD_SET and FD_ZERO don't use array based on FD_SETSIZE [Eoe])
	if (fd < 1 || fd >= FD_SETSIZE) { //don't check fd = 0, keyboard
		perror("make_connection: fd < 1 || fd >= FD_SETSIZE error (socket.c).");
		close(fd);
		return -1;
	}
#endif

	FD_SET(fd, &readfds);

#ifdef WINDOWS
	pos = 2;
	while(session[pos] != NULL && pos < fd_max)
		pos++;
	SessionInsertSocket(fd, pos);
#else
	pos = fd;
#endif

	tick = gettick();

	session[pos] = (struct socket_data *)aCalloc(1, sizeof(*session[pos]));
	session[pos]->func_recv     = recv_to_fifo;
	session[pos]->func_send     = send_from_fifo;
	session[pos]->func_parse    = default_func_parse;
#ifdef WINDOWS
	session[pos]->socket        = fd;
#endif
	session[pos]->func_destruct = default_func_destruct;
	session[pos]->tick          = tick;
	session[pos]->auth          = 0;
	session[pos]->rlr_tick      = tick;
	session[pos]->rlr_bytes     = 0;
	session[pos]->rlr_disc      = 0;
	realloc_fifo(pos, RFIFO_SIZE, WFIFO_SIZE);
	if (fd_max <= pos)
		fd_max = pos + 1;

	return pos;
}

void delete_session(int fd)
{
	if (fd <= 0 || fd >= FD_SETSIZE)
		return;

	if (session[fd]) {
		// ２重呼び出しの防止
		if (session[fd]->flag_destruct)
			return;

		session[fd]->flag_destruct = 1;
		// デストラクタを呼び出す
		if (session[fd]->func_destruct)
			session[fd]->func_destruct(fd);
		close(fd);
		FD_CLR(sockfd(fd), &readfds);
#ifdef WINDOWS
		SessionRemoveSocket(sockfd(fd));
#endif
		if (session[fd]->rdata)
			aFree(session[fd]->rdata);
		if (session[fd]->wdata)
			aFree(session[fd]->wdata);
		if (session[fd]->session_data)
			aFree(session[fd]->session_data);
		if (session[fd]->session_data2)
			aFree(session[fd]->session_data2);
		aFree(session[fd]);
	}
	session[fd] = NULL;
	//printf("delete_session:%d\n", fd);

	return;
}

void realloc_fifo(int fd, size_t new_rfifo_size, size_t new_wfifo_size)
{
	struct socket_data *s;

	if (fd < 0)
		return;

	s = session[fd];
	if (new_rfifo_size > 0 &&
	    (size_t)(s->max_rdata  - s->rdata) != new_rfifo_size &&
	    (size_t)(s->rdata_size - s->rdata) < new_rfifo_size)
	{
		unsigned char * p = s->rdata;
		s->rdata      = (unsigned char *)aRealloc(s->rdata, new_rfifo_size);
		s->rdata_pos  = s->rdata + (s->rdata_pos  - p);
		s->rdata_size = s->rdata + (s->rdata_size - p);
		s->max_rdata  = s->rdata + new_rfifo_size;
	}
	if (new_wfifo_size > 0 &&
	    (size_t)(s->max_wdata  - s->wdata) != new_wfifo_size &&
	    (size_t)(s->wdata_size - s->wdata) < new_wfifo_size)
	{
		unsigned char * p = s->wdata;
		s->wdata      = (unsigned char *)aRealloc(s->wdata, new_wfifo_size);
		s->wdata_pos  = s->wdata + (s->wdata_pos  - p);
		s->wdata_size = s->wdata + (s->wdata_size - p);
		s->max_wdata  = s->wdata + new_wfifo_size;
	}

	return;
}

void WFIFORESERVE(int fd, size_t len)
{
	struct socket_data *s = session[fd];

	while(len + SOCKET_EMPTY_SIZE > (size_t)(s->max_wdata - s->wdata)) {
		size_t new_size = (size_t)(s->max_wdata - s->wdata) << 1;

		// 送信バッファの制限サイズ超過チェック
		if (s->auth >= 0 && new_size > (size_t)send_limit_buffer_size) {
			printf("socket: session #%d wdata (%lu) exceed limited size.\n", fd, (unsigned long)new_size);
			s->wdata_pos  = s->wdata;	// データを消してとりあえず空きを作る
			s->wdata_size = s->wdata;
			// 空きスペースが足りないかもしれないので、再確保
			realloc_fifo(fd, 0, len);
			s->eof = 1;
			return;
		}

		realloc_fifo(fd, 0, new_size);
		printf("socket: session #%d wdata expanded to %lu bytes.\n", fd, (unsigned long)(s->max_wdata - s->wdata));
	}

	return;
}

void WFIFOSET(int fd, size_t len)
{
	struct socket_data *s = session[fd];

	if (fd <= 0 || s->eof)
		return;

	if (s->wdata_size + len <= s->max_wdata) {
		s->wdata_size += len;
	} else {
		printf(
			"socket: %d wdata lost !! packet 0x%x length %ld is over %ld\n",
			fd, *((unsigned short*)s->wdata_size), (long)len, (long)(s->max_wdata - s->wdata_size)
		);
		s->wdata_pos  = s->wdata;
		s->wdata_size = s->wdata;
		s->eof = 1;
		exit(1);	// アクセス違反しているはずなのでサーバを落とす
	}
	WFIFORESERVE(fd, s->wdata_size - s->wdata);

	return;
}

#ifdef WINDOWS

// the windows fd_set structures are simple
// typedef struct fd_set {
//        u_int  fd_count;             /* how many are SET? */
//        SOCKET fd_array[FD_SETSIZE]; /* an array of SOCKETs */
// } fd_set;
//
// the select sets the correct fd_count and the array
// so just access the signaled sockets one by one

// this could be realized also with an additional element in the session data
// or an array with "struct {socket_data*, SOCKET}[]"
// anyway it is working that way better because of less changes
// otherwise it might be necessary to change access from extern structs
// and it might be a bit slower to access then

struct {
	SOCKET sock; // array of corrosponding sockets
	int    pos;
} sessionsockets[FD_SETSIZE];
int sessioncount = 0;

/////////////////////////////////////////////////////////////////
// binary search implementation
// might be not that efficient in this implementation
// it first checks the boundaries so calls outside
// the list range are handles much faster
// at the expence of some extra code
// runtime behaviour much faster if often called for outside data
/////////////////////////////////////////////////////////////////
static int SessionFindSocket(const SOCKET elem, size_t *retpos)
{
	// do a binary search with smallest first
	// make some initial stuff
	int ret = 0;
	size_t a = 0, b = sessioncount - 1;
	size_t pos = 0;

	// just to be sure we have to do something
	if (sessioncount == 0) {
		ret = 0;
	} else if (elem < sessionsockets[a].sock) {
		// less than lower
		pos = a;
		ret = 0;
	} else if (elem > sessionsockets[b].sock) {
		// larger than upper
		pos = b + 1;
		ret = 0;
	} else if (elem == sessionsockets[a].sock) {
		// found at first position
		pos = a;
		ret = 1;
	} else if (elem == sessionsockets[b].sock) {
		// found at last position
		pos = b;
		ret = 1;
	} else {
		size_t c;

		// binary search
		// search between first and last
		do {
			c = (a + b) / 2;
			if (elem == sessionsockets[c].sock) {
				// found it
				b = c;
				ret = 1;
				break;
			} else if (elem < sessionsockets[c].sock)
				b = c;
			else
				a = c;
		} while((a + 1) < b);
		pos = b;
		// return the next larger element to the given
		// or the found element so we can insert a new element there
	}
	// just to make sure we call this with a valid pointer,
	// on c++ it would be a reference and you could omitt the NULL check
	if (retpos)
		*retpos = pos;

	return ret;
}

static void SessionInsertSocket(const SOCKET elem, int pos2)
{
	size_t pos;

	if (sessioncount < FD_SETSIZE) // max number of allowed sockets
		if (!SessionFindSocket(elem, &pos)) {
			if ((size_t)sessioncount != pos) // shift up one position
				memmove(sessionsockets + pos + 1, sessionsockets + pos, (sessioncount - pos) * sizeof(sessionsockets[0]));
			sessionsockets[pos].sock = elem;
			sessionsockets[pos].pos  = pos2;
			sessioncount++;
			return;
		}

	// otherwise the socket is already in the list
	return;
}

static void SessionRemoveSocket(const SOCKET elem)
{
	size_t pos;

	if (SessionFindSocket(elem, &pos)) {
		// shift down one position
		// and just overwrite the pointers here,
		// so clear the session pointer before calling this
		memmove(sessionsockets + pos, sessionsockets + pos + 1, (sessioncount - pos - 1) * sizeof(sessionsockets[0]));
		sessioncount--;
		return;
	}

	// otherwise the socket is not in the list
	return;
}

static void process_fdset(fd_set* rfd, fd_set* wfd)
{
	unsigned int i;
	size_t pos;
	int fd;

	for(i = 0; i < rfd->fd_count; i++) {
		if (SessionFindSocket(rfd->fd_array[i], &pos)) {
			fd = sessionsockets[pos].pos;
			if (session[fd] && session[fd]->func_recv)
				session[fd]->func_recv(fd);
		}
	}
	for(i = 0; i < wfd->fd_count; i++) {
		if (SessionFindSocket(wfd->fd_array[i], &pos)) {
			fd = sessionsockets[pos].pos;
			if (session[fd] && session[fd]->func_send)
				session[fd]->func_send(fd);
		}
	}

	return;
}

#else /* WINDOWS */

// some unix, might work on darwin as well

// unix uses a bit array where the socket number equals the
// position in the array, so finding sockets inside that array
// is not that easy exept the socket is knows before
// so this method here goes through the bit array
// and build the socket number from the position
// where a set bit was found.
// since we can skip 32 sockets all together when none is set
// we can travel quite fast through the array

#ifndef howmany
	#define howmany(x,y) (((x)+((y)-1))/(y))
#endif

// Find the log base 2 of an N-bit integer in O(lg(N)) operations
// in this case for 32bit input it would be 11 operations

inline unsigned long socket_log2(unsigned long v)
{
	register unsigned long c = 0;

#ifdef __64BIT__
	// unsigned long is 64bit
	if (v & 0xFFFFFFFF00000000UL) { v >>= 0x20; c |= 0x20; }
#endif
	if (v & 0xFFFF0000UL) { v >>= 0x10; c |= 0x10; }
	if (v & 0x0000FF00UL) { v >>= 0x08; c |= 0x08; }
	if (v & 0x000000F0UL) { v >>= 0x04; c |= 0x04; }
	if (v & 0x0000000CUL) { v >>= 0x02; c |= 0x02; }
	if (v & 0x00000002UL) { v >>= 0x01; c |= 0x01; }

	return c;
}

static void process_fdset(fd_set* rfd, fd_set* wfd)
{
	unsigned long sock;
	unsigned long val;
	unsigned long bits;
	unsigned long nfd = 0;
	// usually go up to 'howmany(FD_SETSIZE, NFDBITS)'
	unsigned long max = howmany(fd_max, NFDBITS);

	while(nfd < max) {
		// while something is set in the ulong at position nfd
		bits = rfd->fds_bits[nfd];
		while(bits) {
			// calc the highest bit with log2
			// and clear it from the field
			// this method is especially fast
			// when only a few bits are set in the field
			// which usually happens on read events
			val = socket_log2(bits);
			bits ^= (1UL << val);
			// build the socket number
			sock = nfd * NFDBITS + val;

			// call the user function
			if (session[sock] && session[sock]->func_recv)
				session[sock]->func_recv(sock);
		}
		// go to next field position
		nfd++;
	}

	// vars are declared above already
	nfd = 0;
	while(nfd < max) {
		// while something is set in the ulong at position nfd
		bits = wfd->fds_bits[nfd];
		while(bits) {
			// calc the highest bit with log2
			// and clear it from the field
			// this method is especially fast
			// when only a few bits are set in the field
			// which usually happens on read events
			val = socket_log2(bits);
			bits ^= (1UL << val);
			// build the socket number
			sock = nfd * NFDBITS + val;

			// call the user function
			if (session[sock] && session[sock]->func_send)
				session[sock]->func_send(sock);
		}
		// go to next field position
		nfd++;
	}

	return;
}
#endif /* WINDOWS */

void do_sendrecv(int next)
{
	fd_set rfd,wfd;
	struct timeval timeout;
	int ret, i;
	unsigned int tick = gettick();

	// select するための準備
	memcpy(&rfd, &readfds, sizeof(fd_set));
	FD_ZERO(&wfd);
	for(i = 0; i < fd_max; i++) {
		struct socket_data *sd = session[i];
		if (sd) {
			// バッファにデータがあるなら送信可能かチェックする
			if (sd->wdata_size != sd->wdata_pos)
				FD_SET(sockfd(i), &wfd);

			// 受信帯域制限中ならこの socket は受信可能かチェックしない
			if (recv_limit_rate_enable && sd->auth >= 0 && DIFF_TICK(sd->rlr_tick, tick) > 0)
				FD_CLR(sockfd(i), &rfd);
		}
	}

	// タイムアウトの設定（最大1秒）
	if (next > 1000)
		next = 1000;
	timeout.tv_sec  = next / 1000;
	timeout.tv_usec = next % 1000 * 1000;

	// select で通信を待つ
	ret = select(fd_max, &rfd, &wfd, NULL, &timeout);
	if (ret <= 0)
		return;

	// select 結果にしたがって送受信する
	process_fdset(&rfd, &wfd);

	return;
}

void do_parsepacket(void)
{
	int i;
	unsigned int tick = gettick();

	for(i = 0; i < fd_max; i++) {
		struct socket_data *sd = session[i];

		if (!sd)
			continue;

		if (sd->eof ||
		    (sd->flag_destruct == 0 && sd->auth >= 0 &&
		     DIFF_TICK(tick, sd->tick) > ((sd->auth) ? auth_timeout : unauth_timeout))) {	// タイムアウト
			delete_session(i);

		} else {

			// パケットの解析
			if (sd->func_parse && sd->rdata_size != sd->rdata_pos) {
				size_t s = RFIFOREST(i);
#ifdef NO_HTTPD
				sd->func_parse(i);
#else
				if (!sd->flag_httpd && httpd_enable) {
					// httpd に回すどうかの判定がまだ行われてない
					// 先頭２バイトが GE or POならhttpd に回してみる
					if (sd->rdata_size - sd->rdata >= 2) {
						sd->flag_httpd = 1;
						if ((sd->rdata[0] == 'G' && sd->rdata[1] == 'E') ||
						    (sd->rdata[0] == 'P' && sd->rdata[1] == 'O')) {
							sd->func_parse = httpd_parse;
							realloc_fifo(i, RFIFOSIZE_HTTPD, WFIFOSIZE_HTTPD);
							sd->auth = -1;
						}
					}
				}
				if (sd->flag_httpd || !httpd_enable)
					sd->func_parse(i);
#endif
				// 認証が終了してるなら受信があれば tick を更新
				if (s != RFIFOREST(i)) {
					if (sd->auth)
						sd->tick = tick;
				// If RFIFO was not parsed, and pointer is at first position and full
				} else if (sd->rdata_pos == sd->rdata && sd->max_rdata == sd->rdata_size) { // (so, RFIFO could not be parsed)
					// probably a hacker or something like that (too big and not parsed packet)
					sd->eof = 1;
				}
			}

			// クリアする間隔を減らしてみる
			if (sd->rdata_pos == sd->rdata_size) { // all FIFO readed
				sd->rdata_size = sd->rdata;
				sd->rdata_pos  = sd->rdata;
			} else if ((sd->rdata_pos - sd->rdata) * 2 > (sd->max_rdata - sd->rdata)) { // if not enough place to read next packets (at least 50% of RFIFO must be free)
				// the previous check is done to reduce number of memmove -> reduction of CPU usage
				memmove(sd->rdata, sd->rdata_pos, RFIFOREST(i));
				sd->rdata_size = sd->rdata + RFIFOREST(i);
				sd->rdata_pos  = sd->rdata;
			}
		}
	}

	return;
}

void flush_fifo(int fd)
{
	if(fd >= 0 && session[fd] && session[fd]->func_send == send_from_fifo) {
		send_from_fifo(fd);
	}
	return;
}

unsigned long host2ip(const char *host, const char *mes)
{
	char ip[16];
	struct hostent *h = gethostbyname(host);

	if(h) {
		sprintf(ip, "%d.%d.%d.%d", (unsigned char)h->h_addr[0], (unsigned char)h->h_addr[1], (unsigned char)h->h_addr[2], (unsigned char)h->h_addr[3]);
		if(mes) {
			printf("%s : %s -> %s\n", mes, host, ip);
		}
	} else {
		memcpy(ip, host, sizeof(ip));
		ip[sizeof(ip)-1] = '\0';
	}
	return inet_addr(ip);
}

int parsepacket_timer(int tid, unsigned int tick, int id, void *data)
{
	do_parsepacket();

	return 0;
}

/* DDoS 攻撃対策 */

enum {
	ACO_DENY_ALLOW = 0,
	ACO_ALLOW_DENY,
	ACO_MUTUAL_FAILURE,
};

struct _access_control {
	unsigned long ip;
	unsigned long mask;
};

static struct _access_control *access_allow = NULL;
static struct _access_control *access_deny = NULL;
static int access_order    = ACO_DENY_ALLOW;
static int access_allownum = 0;
static int access_denynum  = 0;
static int access_debug;
static int ddos_count      = 10;
static int ddos_interval   = 3000;
static int ddos_autoreset  = 600 * 1000;

struct _connect_history {
	struct _connect_history *next;
	struct _connect_history *prev;
	int    status;
	int    count;
	unsigned long ip;
	unsigned int tick;
};
static struct _connect_history *connect_history[0x10000];
static int connect_check_(unsigned long ip);

// 接続できるかどうかの確認
//   false : 接続OK
//   true  : 接続NG
static int connect_check(unsigned long ip)
{
	int result = connect_check_(ip);

	if (access_debug)
		printf("connect_check: connection from %08lx %s\n", ip, result ? "allowed" : "denied");

	return result;
}

static int connect_check_(unsigned long ip)
{
	struct _connect_history *hist = connect_history[ip & 0xFFFF];
	struct _connect_history *hist_new;
	int i, is_allowip = 0, is_denyip = 0, connect_ok = 0;
	unsigned int tick = gettick();

	// allow , deny リストに入っているか確認
	for(i = 0; i < access_allownum; i++) {
		if ((ip & access_allow[i].mask) == (access_allow[i].ip & access_allow[i].mask)) {
			if (access_debug)
				printf("connect_check: match allow list from:%08lx ip:%08lx mask:%08lx\n",
				       ip, access_allow[i].ip, access_allow[i].mask);
			is_allowip = 1;
			break;
		}
	}
	for(i = 0; i < access_denynum; i++) {
		if ((ip & access_deny[i].mask) == (access_deny[i].ip & access_deny[i].mask)) {
			if (access_debug)
				printf("connect_check: match deny list  from:%08lx ip:%08lx mask:%08lx\n",
				       ip, access_deny[i].ip, access_deny[i].mask);
			is_denyip = 1;
			break;
		}
	}
	// コネクト出来るかどうか確認
	// connect_ok
	//   0 : 無条件に拒否
	//   1 : 田代砲チェックの結果次第
	//   2 : 無条件に許可
	switch(access_order) {
	case ACO_ALLOW_DENY:
		if (is_denyip)
			connect_ok = 0;
		else if (is_allowip)
			connect_ok = 2;
		else
			connect_ok = 1;
		break;
	case ACO_MUTUAL_FAILURE:
		if (is_allowip)
			connect_ok = 2;
		else
			connect_ok = 0;
		break;
	case ACO_DENY_ALLOW:
	default:
		if (is_allowip)
			connect_ok = 2;
		else if (is_denyip)
			connect_ok = 0;
		else
			connect_ok = 1;
		break;
	}

	// 接続履歴を調べる
	while(hist) {
		if (ip == hist->ip) {
			// 同じIP発見
			if (hist->status) {
				// ban フラグが立ってる
				return ((connect_ok == 2) ? 1 : 0);
			} else if (DIFF_TICK(tick,hist->tick) < ddos_interval) {
				// ddos_interval秒以内にリクエスト有り
				hist->tick = tick;
				if (hist->count++ >= ddos_count) {
					// ddos 攻撃を検出
					unsigned char *p = (unsigned char *)&ip;
					hist->status = 1;
					printf("connect_check: ddos attack detected (%d.%d.%d.%d)\n", p[0], p[1], p[2], p[3]);
					return ((connect_ok == 2) ? 1 : 0);
				} else
					return connect_ok;
			} else {
				// ddos_interval秒以内にリクエスト無いのでタイマークリア
				hist->tick  = tick;
				hist->count = 0;
				return connect_ok;
			}
		}
		hist = hist->next;
	}
	// IPリストに無いので新規作成
	hist_new = (struct _connect_history *)aCalloc(1, sizeof(struct _connect_history));
	hist_new->ip   = ip;
	hist_new->tick = tick;
	if (connect_history[ip & 0xFFFF] != NULL) {
		hist = connect_history[ip & 0xFFFF];
		hist->prev = hist_new;
		hist_new->next = hist;
	}
	connect_history[ip & 0xFFFF] = hist_new;

	return connect_ok;
}

static int connect_check_clear(int tid, unsigned int tick, int id, void *data)
{
	int i;
	int clear = 0;
	int list  = 0;
	struct _connect_history *hist, *hist2;

	for(i = 0; i < 0x10000; i++) {
		hist = connect_history[i];
		while(hist) {
			if ((DIFF_TICK(tick,hist->tick) > ddos_interval * 3 && !hist->status) ||
			    (DIFF_TICK(tick,hist->tick) > ddos_autoreset    &&  hist->status)) {
				// clear data
				hist2 = hist->next;
				if (hist->prev)
					hist->prev->next = hist->next;
				else
					connect_history[i] = hist->next;
				if (hist->next)
					hist->next->prev = hist->prev;
				aFree(hist);
				hist = hist2;
				clear++;
			} else {
				hist = hist->next;
				list++;
			}
		}
	}
	if (access_debug)
		printf("connect_check_clear: clear = %d list = %d\n", clear, list);

	return list;
}

// IPマスクチェック
static int access_ipmask(const char *str,struct _access_control* acc)
{
	unsigned int mask = 0, ip;

	if (!strcmp(str, "all")) {
		ip   = 0;
		mask = 0;
	} else {
		unsigned int i = 0, m, a0, a1, a2, a3;
		if (sscanf(str, "%u.%u.%u.%u%n", &a0, &a1, &a2, &a3, &i) != 4 || i == 0) {
			printf("access_ipmask: unknown format %s\n", str);
			return 0;
		}
		ip = (a3 << 24) | (a2 << 16) | (a1 << 8) | a0;

		if (sscanf(str + i, "/%u.%u.%u.%u", &a0, &a1, &a2, &a3) == 4) {
			mask = (a3 << 24) | (a2 << 16) | (a1 << 8) | a0;
		} else if (sscanf(str + i, "/%u", &m) == 1) {
			for(i = 0; i < m; i++) {
				mask = (mask >> 1) | 0x80000000;
			}
			mask = ntohl(mask);
		} else {
			mask = 0xFFFFFFFF;
		}
	}
	if (access_debug)
		printf("access_ipmask: ip:%08x mask:%08x %s\n", ip, mask, str);

	acc->ip   = ip;
	acc->mask = mask;

	return 1;
}

static void socket_config_read2(const char *filename)
{
	int i;
	char line[1024], w1[1024], w2[1024];
	FILE *fp;
	const struct {
		const char *name;
		int *ptr;
	} list[] = {
		{ "debug",                      &access_debug               },
		{ "socket_ctrl_panel",          &socket_ctrl_panel_httpd    },
		{ "ddos_interval",              &ddos_interval              },
		{ "ddos_count",                 &ddos_count                 },
		{ "ddos_autoreset",             &ddos_autoreset             },
		{ "recv_limit_rate_enable",     &recv_limit_rate_enable     },
		{ "recv_limit_rate_period",     &recv_limit_rate_period     },
		{ "recv_limit_rate_bytes",      &recv_limit_rate_bytes      },
		{ "recv_limit_rate_wait_max",   &recv_limit_rate_wait_max   },
		{ "recv_limit_rate_disconnect", &recv_limit_rate_disconnect },
		{ "send_limit_buffer_size",     &send_limit_buffer_size     },
	};

	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("socket_config_read2: open [%s] failed !\n", filename);
		return;
	}

	while(fgets(line, sizeof(line) - 1, fp)) {
		if (line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if (line[0] == '/' && line[1] == '/')
			continue;
		if (sscanf(line, "%1023[^:]: %1023[^\r\n]", w1, w2) != 2)
			continue;

		if (strcmpi(w1, "order") == 0) {
			if (strcmpi(w2, "deny,allow")          == 0) access_order = ACO_DENY_ALLOW;
			else if (strcmpi(w2, "allow,deny")     == 0) access_order = ACO_ALLOW_DENY;
			else if (strcmpi(w2, "mutual-failure") == 0) access_order = ACO_MUTUAL_FAILURE;
			else                                         access_order = atoi(w2);

		} else if (strcmpi(w1, "allow") == 0) {
			if (strcmpi(w2, "clear") == 0) {
				if (access_allow != NULL) {
					aFree(access_allow);
					access_allow = NULL;
				}
				access_allownum = 0;
			} else {
				access_allow = (struct _access_control *)aRealloc(access_allow, (access_allownum + 1) * sizeof(struct _access_control));
				if (access_ipmask(w2, &access_allow[access_allownum]))
					access_allownum++;
			}

		} else if (strcmpi(w1, "deny") == 0) {
			if (strcmpi(w2, "clear") == 0) {
				if (access_deny != NULL) {
					aFree(access_deny);
					access_deny = NULL;
				}
				access_denynum = 0;
			} else {
				access_deny = (struct _access_control *)aRealloc(access_deny, (access_denynum + 1) * sizeof(struct _access_control));
				if (access_ipmask(w2, &access_deny[access_denynum]))
					access_denynum++;
			}

		} else if (strcmpi(w1, "httpd_config") == 0) {
			httpd_config_read(w2);

		} else if (strcmpi(w1, "socket_ctrl_panel_url") == 0) {
			strncpy(socket_ctrl_panel_url, w2, sizeof(socket_ctrl_panel_url) - 1);

		} else if (strcmpi(w1, "import") == 0) {
			socket_config_read2(w2);

		} else {
			for(i = 0; i < sizeof(list) / sizeof(list[0]); i++) {
				if (strcmpi(w1, list[i].name) == 0) {
					*list[i].ptr = atoi(w2);
					break;
				}
			}

			if (i == sizeof(list) / sizeof(list[0]))
				printf("socket_config_read [%s]: unknown config: %s", filename, line);
		}
	}
	fclose(fp);

	return;
}

static void socket_config_read(void)
{
	socket_config_read2("conf/socket.conf");

	return;
}

static void do_final_socket(void)
{
	int i;
	struct _connect_history *hist, *hist2;

	for(i = 0; i < fd_max; i++) {
		if (session[i])
			delete_session(i);
	}
	for(i = 0; i < 0x10000; i++) {
		hist = connect_history[i];
		while(hist) {
			hist2 = hist->next;
			aFree(hist);
			hist = hist2;
		}
	}
	aFree(access_allow);
	aFree(access_deny);

	// session[0] のダミーデータを削除
	aFree(session[0]->rdata);
	aFree(session[0]->wdata);
	aFree(session[0]);

	return;
}

void do_socket(void)
{
	unsigned int tick = gettick();

	FD_ZERO(&readfds);

#ifdef WINDOWS
	{
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
			if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
				printf("error: winsock not available.\n");
				MessageBox(NULL, "Winsock Dll Load Error", "socket.c", MB_OK);
				exit(1);
			}
			printf("status: winsock 1.1 succesfully loaded.\n");
		} else {
			printf("status: winsock 2.0 succesfully loaded.\n");
		}
	}
#endif

	atexit(do_final_socket);
	socket_config_read();

	// session[0] にダミーデータを確保する
	session[0] = (struct socket_data *)aCalloc(1, sizeof(*session[0]));
	session[0]->auth = -1;
	realloc_fifo(0, RFIFO_SIZE, WFIFO_SIZE);

	// とりあえず５分ごとに不要なデータを削除する
	add_timer_func_list(connect_check_clear);
	add_timer_interval(tick + 1000, connect_check_clear, 0, NULL, 300 * 1000);

	return;
}


// ==========================================
// 出力
// ------------------------------------------
static void socket_httpd_page_send(int fd, const char *str)
{
	size_t len = strlen(str);

	memcpy(WFIFOP(fd,0), str, len);
	WFIFOSET(fd,len);

	return;
}

// ==========================================
// ヘッダ部分
// ------------------------------------------
static void socket_httpd_page_header(struct httpd_session_data *sd)
{
	httpd_send_head(sd, 200, "text/html", -1);

	socket_httpd_page_send(sd->fd,
	   "<html>\n<head>\n<title>Socket Control Panel</title>\n</head>\n<body>\n"
	   "<h1>Socket control panel</h1>\n\n" );

	return;
}

// ==========================================
// フッタ部分
// ------------------------------------------
static void socket_httpd_page_footer(int fd)
{
	int len;

	len = sprintf(WFIFOP(fd,0),
	      "<p><a href=\"/\">[site top]</a>"
	      "<a href=\"%s\">[socket control panel top]</a></p>\n"
	      "</body>\n</html>\n", socket_ctrl_panel_url);
	WFIFOSET(fd, len);

	return;
}

// ==========================================
// アクセス制御の設定確認
// ------------------------------------------
static void socket_httpd_page_access_settings(struct httpd_session_data *sd, const char *url)
{
	int i, len, fd = sd->fd;

	socket_httpd_page_header(sd);

	len = sprintf(WFIFOP(fd,0),
	      "<h2>View Access Control Settings</h2>\n"
	      "<table border=1><tr><th>Order</th><td>%s</td></tr>\n"
	      "<tr><th>allow</th><th>deny</th></tr>\n"
	      "<tr><td>\n",
	      (access_order == ACO_DENY_ALLOW) ? "deny, allow" :
	      (access_order == ACO_ALLOW_DENY) ? "allow, deny" :
	      (access_order == ACO_MUTUAL_FAILURE) ? "mutual-failure" : "?");
	WFIFOSET(fd, len);

	for(i = 0; i < access_allownum; i++ ) {
		unsigned char *ip = (unsigned char*)(&access_allow[i].ip);
		unsigned char *mask = (unsigned char*)(&access_allow[i].mask);
		len = sprintf(WFIFOP(fd,0), "%d.%d.%d.%d/%d.%d.%d.%d<br>\n",
		      ip[0], ip[1], ip[2], ip[3], mask[0], mask[1], mask[2], mask[3]);
		WFIFOSET(fd, len);
	}
	socket_httpd_page_send(sd->fd, "</td><td>\n");
	for(i = 0; i< access_denynum; i++) {
		unsigned char *ip = (unsigned char*)(&access_deny[i].ip);
		unsigned char *mask = (unsigned char*)(&access_deny[i].mask);
		len = sprintf(WFIFOP(fd,0), "%d.%d.%d.%d/%d.%d.%d.%d\n",
		      ip[0], ip[1], ip[2], ip[3], mask[0], mask[1], mask[2], mask[3]);
		WFIFOSET(fd, len);
	}
	socket_httpd_page_send(sd->fd, "</td></tr></table>");

	socket_httpd_page_footer(sd->fd);

	return;
}

// ==========================================
// DoS アタックの状況確認
// ------------------------------------------
static void socket_httpd_page_dos_attack(struct httpd_session_data *sd, const char *url)
{
	int i, n, len, fd = sd->fd;
	unsigned int tick = gettick();
	char *p;

	// DoS ブロック解除
	p = httpd_get_value(sd, "dosdelete");
	if (*p) {
		for(i = 0; i < 100; i++) {
			char buf[32];
			unsigned int ip;
			char* p2;
			sprintf(buf, "dosdelete%02x", i);
			p2 = httpd_get_value(sd, buf);
			if (sscanf(p, "%08x", &ip) == 1) {
				struct _connect_history *hist = connect_history[ip & 0xffff];
				while(hist) {
					if (hist->ip == ip)
						hist->status = 0;
					hist = hist->next;
				}
			}
			aFree(p2);
		}
	}
	aFree(p);

	socket_httpd_page_header(sd);

	// DoS アタックのブロックリスト
	len = sprintf(WFIFOP(fd,0 ),
	      "<h2>Anti-DoS Attack : blocking IP address list</h2>\n"
	      "<form action=\"%s\" method=\"post\">\n"
	      "<input type=\"hidden\" name=\"mode\" value=\"dosattack\">\n"
	      "<input type=\"hidden\" name=\"dosdelete\" value=\"1\">\n"
	      "<table border=1><tr><th>IP address</th><th>remain(sec.)</th>"
	      "<th><input type=\"submit\" value=\"delete\"></th></tr>\n", socket_ctrl_panel_url);
	WFIFOSET(fd, len);

	n = 0;
	for(i = 0; i < 0x10000; i++) {
		struct _connect_history *hist = connect_history[i];
		while(hist) {
			int remain = DIFF_TICK(hist->tick + ddos_autoreset, tick);
			if (hist->status && remain > 0) {
				unsigned char *ip = (unsigned char *)(&hist->ip);
				if (n < 100) {
					len = sprintf(WFIFOP(fd,0),
					      "<tr><th>%d.%d.%d.%d</th><td>%d</td>"
					      "<td><input type=\"checkbox\" name=\"dosdelete%02x\" value=\"%08lx\"></td></tr>\n",
					      ip[0], ip[1], ip[2], ip[3], remain / 1000, n, hist->ip);
					WFIFOSET(fd, len);
				}
				n++;
			}
			hist = hist->next;
		}
	}
	len = sprintf(WFIFOP(fd,0), "</table>\nblocking %d ip(s) ... </form>\n", n);
	WFIFOSET(fd, len);

	socket_httpd_page_footer(sd->fd);

	return;
}

void (*socket_httpd_page_connection_func)(int fd,char*,char*,char*);
void socket_set_httpd_page_connection_func(void (*func)(int fd,char*,char*,char*)){ socket_httpd_page_connection_func = func; }

// ==========================================
// 接続状況確認
// ------------------------------------------
static void socket_httpd_page_connection(struct httpd_session_data *hsd, const char *url)
{
	int i, n, len;
	int fd = hsd->fd;
	char *p;

	// 強制切断
	p = httpd_get_value(hsd, "disconnect");
	if (*p) {
		for(i = 1; i < fd_max; i++) {
			char buf[32];
			char* p2;
			sprintf(buf, "discon%04x", i);
			p2 = httpd_get_value(hsd, buf);
			if (*p2 && session[i]->func_recv != connect_client)
				session[i]->eof = 1;
			aFree(p2);
		}
	}
	aFree(p);

	socket_httpd_page_header(hsd);

	len = sprintf(WFIFOP(fd,0),
	      "<h2>Connection list</h2>\n"
	      "<form action=\"%s\" method=\"post\">"
	      "<input type=\"hidden\" name=\"mode\" value=\"connection\">\n"
	      "<input type=\"hidden\" name=\"disconnect\" value=\"1\">\n"
	      "<table border=1>\n"
	      "<tr><th>IP</th><th>usage</th><th>user</th><th>status</th>"
	      "<th><input type=\"submit\" value=\"disconnect\"></th></tr>\n", socket_ctrl_panel_url);
	WFIFOSET(fd, len);

	n = 0;
	for(i = 1; i < fd_max; i++) {
		struct socket_data *sd = session[i];
		unsigned char* ip;
		int type = 0;
		char usage[256] = "", user[256] = "", status[256] = "";
		char *qusage, *quser, *qstatus;

		if (!sd || sd->eof)
			continue;

		ip = (unsigned char *)(&sd->client_addr.sin_addr);

		strcpy(usage,
		       (sd->func_recv == connect_client) ? "server" :
		       (sd->func_parse == httpd_parse) ? ((type = 1), "httpd") : ((type = 2), "unknown"));
		strcpy(status,
		       (sd->func_recv == connect_client) ? "listen" :
		       (sd->auth == 1) ? "authorized" :
		       (sd->auth == 0) ? "unauthorized" : "permanent connection");

		if (type == 1)
			strcpy(user, ((struct httpd_session_data*)session[fd]->session_data2)->user);
		else if (type == 2 && socket_httpd_page_connection_func != NULL)
			socket_httpd_page_connection_func(i, usage, user, status);

		qusage  = httpd_quote_meta(usage);
		quser   = httpd_quote_meta(user);
		qstatus = httpd_quote_meta(status);

		len = sprintf(WFIFOP(fd,0),
		      "<th>%d.%d.%d.%d</th><td>%s</td><td>%s</td><td>%s</td>"
		      "<td><input type=\"checkbox\" name=\"discon%04x\" value=\"1\"></td></tr>",
		      ip[0], ip[1], ip[2], ip[3], qusage, quser, qstatus, i);
		WFIFOSET(fd, len);
		n++;

		aFree(qstatus);
		aFree(quser);
		aFree(qusage);
	}

	len = sprintf(WFIFOP(fd,0), "</table>\n%d connection(s) found.\n", n);
	WFIFOSET(fd, len);

	socket_httpd_page_footer(hsd->fd);

	return;
}

// socket コントロールパネル（do_init_httpd で httpd に登録される）
void socket_httpd_page(struct httpd_session_data* sd, const char* url)
{
	int i, len;
	char *p;

	static const struct {
		const char *mode;
		void (*func)(struct httpd_session_data*, const char*);
	} pages[] = {
		{ "dosattack",  socket_httpd_page_dos_attack      },
		{ "access",     socket_httpd_page_access_settings },
		{ "connection", socket_httpd_page_connection      },
	};

	if (socket_ctrl_panel_httpd == 0) {
		httpd_send(sd, 403, "text/plain", 9, "Forbidden");
		return;
	}

	p = httpd_get_value(sd, "mode");
	for(i = 0; i < sizeof(pages) / sizeof(pages[0]); i++) {
		if (strcmp(p, pages[i].mode) == 0) {
			aFree(p);
			pages[i].func(sd, url);
			return;
		}
	}
	aFree(p);

	socket_httpd_page_header(sd);

	len = sprintf(WFIFOP(sd->fd, 0),
	      "<ul>\n"
	      "<li><a href=\"%s?mode=access\">View Access Control Settings</a>\n"
	      "<li><a href=\"%s?mode=dosattack\">Anti-DoS Attack Status</a>\n"
	      "<li><a href=\"%s?mode=connection\">Connection Status</a>\n"
	      "</ul>\n", socket_ctrl_panel_url, socket_ctrl_panel_url, socket_ctrl_panel_url);
	WFIFOSET(sd->fd, len);

	socket_httpd_page_footer(sd->fd);

	return;
}
