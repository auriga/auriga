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
#include <string.h>

#include "malloc.h"
#include "nullpo.h"

#include "msg.h"
#include "battle.h"
#include "clif.h"

#define MSG_NUMBER 256
static char *msg_table[MSG_NUMBER]; /* Server messages */
static char *motd = NULL;

/*==========================================
 * Return the message string of the specified number
 *------------------------------------------
 */
const char * msg_txt(int msg_number)
{
	if (msg_number < 0 || msg_number >= MSG_NUMBER) {
		if (battle_config.error_log)
			printf("Message text error: Invalid message number: %d.\n", msg_number);
	} else if (msg_table[msg_number] != NULL && msg_table[msg_number][0] != '\0') {
		return msg_table[msg_number];
	}

	return "<no message>";
}

/*==========================================
 * フォーマット付きメッセージ出力
 *------------------------------------------
 */
void msg_output(const int fd, const char *format, ...)
{
	char output[256];
	va_list ap;

	va_start(ap, format);
	vsnprintf(output, sizeof(output), format, ap);
	va_end(ap);

	clif_displaymessage(fd, output);

	return;
}

/*==========================================
 * Message of the Dayの送信
 *------------------------------------------
 */
void msg_send_motd(struct map_session_data *sd)
{
	char *p = motd;

	nullpo_retv(sd);

	if(p) {
		do {
			clif_displaymessage(sd->fd, p);
			p += strlen(p) + 1;
		} while(*p);
	}

	return;
}

/*==========================================
 * Read Message Data
 *------------------------------------------
 */
int msg_config_read(const char *cfgName)
{
	static int msg_config_read_done = 0; /* for multiple configuration reading */
	int msg_number;
	char line[1024], w1[1024], w2[1024];
	FILE *fp;

	// init table
	if (msg_config_read_done == 0) {
		memset(&msg_table[0], 0, sizeof(msg_table[0]) * MSG_NUMBER);
		msg_config_read_done = 1;
	}

	fp = fopen(cfgName, "r");
	if (fp == NULL) {
		printf("msg_config_read: open [%s] failed !\n", cfgName);
		return 1;
	}

	line[sizeof(line)-1] = '\0';
	while (fgets(line, sizeof(line)-1, fp)) {
		if ((line[0] == '/' && line[1] == '/') || line[0] == '\0' || line[0] == '\n' || line[0] == '\r')
			continue;
		if (sscanf(line,"%d: %1023[^\r\n]",&msg_number,w2) != 2) {
			if (sscanf(line,"%1023[^:]: %1023[^\r\n]",w1,w2) != 2)
				continue;
			if (strcmpi(w1,"import") == 0) {
				msg_config_read(w2);
			}
			continue;
		}

		if (msg_number >= 0 && msg_number < MSG_NUMBER) {
			if (msg_table[msg_number]) {
				aFree(msg_table[msg_number]);
			}
			msg_table[msg_number] = (char *)aStrdup(w2);
		} else if (battle_config.error_log) {
			printf("file [%s]: Invalid message number: %d.\n", cfgName, msg_number);
		}
	}
	fclose(fp);

	return 0;
}

/*==========================================
 * Message of the Dayの読み込み
 *------------------------------------------
 */
int msg_read_motd(void)
{
	int i;
	size_t len, size = 0, pos = 0;
	char buf[256];
	FILE *fp;

	if(motd) {
		aFree(motd);
		motd = NULL;
	}

	if((fp = fopen(motd_txt, "r")) == NULL) {
		// not error
		return 0;
	}

	while(fgets(buf, sizeof(buf)-1, fp) != NULL) {
		for(i = 0; buf[i]; i++) {
			if(buf[i] == '\r' || buf[i] == '\n') {
				if(i == 0) {
					buf[i++] = ' ';
				}
				buf[i] = '\0';
				break;
			}
		}

		len = strlen(buf) + 1;
		if(pos + len >= size) {
			size += sizeof(buf);
			motd = (char *)aRealloc(motd, size);
		}
		memcpy(motd + pos, buf, len);
		pos += len;
	}

	if(size > 0) {
		motd = (char *)aRealloc(motd, pos + 1);	// 縮小処理
		motd[pos] = '\0';	// 末尾に \0 を2つ続ける
	}

	fclose(fp);

	return 0;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
void do_final_msg(void)
{
	int msg_number;

	for (msg_number = 0; msg_number < MSG_NUMBER; msg_number++) {
		if (msg_table[msg_number]) {
			aFree(msg_table[msg_number]);
		}
	}

	if (motd) {
		aFree(motd);
		motd = NULL;
	}

	return;
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
int do_init_msg(void)
{
	msg_read_motd();

	return 0;
}
