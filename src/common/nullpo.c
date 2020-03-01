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
#include <stdarg.h>
#include <string.h>

#include "nullpo.h"

static void nullpo_info_core(const char *file, int line, const char *func, const char *fmt, va_list ap);

/*======================================
 * Nullチェック 及び 情報出力
 *--------------------------------------
 */
int nullpo_chk_f(const char *file, int line, const char *func, const void *target, const char *fmt, ...)
{
	va_list ap;

	if (target != NULL)
		return 0;

	va_start(ap, fmt);
	nullpo_info_core(file, line, func, fmt, ap);
	va_end(ap);
	return 1;
}

int nullpo_chk(const char *file, int line, const char *func, const void *target)
{
	if (target != NULL)
		return 0;

	nullpo_info_core(file, line, func, NULL, NULL);
	return 1;
}

/*======================================
 * nullpo情報出力(外部呼出し向けラッパ)
 *--------------------------------------
 */
void nullpo_info_f(const char *file, int line, const char *func, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	nullpo_info_core(file, line, func, fmt, ap);
	va_end(ap);
}

void nullpo_info(const char *file, int line, const char *func)
{
	nullpo_info_core(file, line, func, NULL, NULL);
}

/*======================================
 * nullpo情報出力(Main)
 *--------------------------------------
 */
static void nullpo_info_core(const char *file, int line, const char *func, const char *fmt, va_list ap)
{
	if (file == NULL)
		file = "??";

	func =
		func == NULL    ? "unknown":
		func[0] == '\0' ? "unknown":
		                  func;

	printf("--- nullpo info --------------------------------------------\n");
	printf("%s:%d: in func `%s'\n", file, line, func);
	if (fmt != NULL)
	{
		if (fmt[0] != '\0')
		{
			vprintf(fmt, ap);

			// 最後に改行したか確認
			if (fmt[strlen(fmt)-1] != '\n')
				printf("\n");
		}
	}
	printf("--- end nullpo info ----------------------------------------\n");

	// ここらでnullpoログをファイルに書き出せたら
	// まとめて提出できるなと思っていたり。
}
