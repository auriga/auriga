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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "msg.h"
#include "malloc.h"
#include "battle.h"
#include "clif.h"

#define MSG_NUMBER 256
static char *msg_table[MSG_NUMBER]; /* Server messages */

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
		printf("File not found: %s.\n", cfgName);
		return 1;
	}

	line[sizeof(line)-1] = '\0';
	while (fgets(line, sizeof(line)-1, fp)) {
		if ((line[0] == '/' && line[1] == '/') || line[0] == '\0' || line[0] == '\n' || line[0] == '\r')
			continue;
		if (sscanf(line,"%d: %[^\r\n]",&msg_number,w2) != 2) {
			if (sscanf(line,"%[^:]: %[^\r\n]",w1,w2) != 2)
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
 * Free Message Data
 *------------------------------------------
 */
void do_final_msg_config(void)
{
	int msg_number;

	for (msg_number = 0; msg_number < MSG_NUMBER; msg_number++) {
		if (msg_table[msg_number]) {
			aFree(msg_table[msg_number]);
		}
	}

	return;
}
