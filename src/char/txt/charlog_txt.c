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
#include <string.h>

#include "lock.h"
#include "utils.h"

#include "charlog_txt.h"

static char char_log_filename[1024] = "log/char.log";

/*==========================================
 * ログ記録
 *------------------------------------------
 */
int charlog_log_txt(const char *fmt, ...)
{
	FILE *logfp;
	va_list ap;

	va_start(ap, fmt);

	logfp = fopen(char_log_filename, "a");
	if(logfp) {
		vfprintf(logfp, fmt, ap);
		fprintf(logfp, NEWLINE);
		fclose(logfp);
	}
	va_end(ap);

	return 0;
}

/*==========================================
 * 設定ファイル読込
 *------------------------------------------
 */
int charlog_config_read_txt(const char *w1, const char *w2)
{
	if( strcmpi(w1, "char_log_filename") == 0 ) {
		strncpy(char_log_filename, w2, sizeof(char_log_filename) - 1);
		char_log_filename[sizeof(char_log_filename) - 1] = '\0';
	} else {
		return 0;
	}

	return 1;
}
