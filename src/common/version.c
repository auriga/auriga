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

#include "version.h"


/*==========================================
 * バージョンの取得
 *------------------------------------------
 */
int get_current_version(void)
{
	static int auriga_version = 0;

	if(auriga_version == 0) {
		FILE *fp;
		char filename[256];

		if(AURIGA_REVISION < 100)
			sprintf(filename, "Readme%03d", AURIGA_REVISION);
		else
			sprintf(filename, "Readme%04d", AURIGA_REVISION);

		fp = fopen(filename, "r");
		if(fp) {
			char line[1024];
			int ver;

			while(fgets(line, sizeof(line), fp)) {
				if(sscanf(line, "//%d [%*d/%*d/%*d] by", &ver) == 1) {
					auriga_version = ver;
					break;
				}
			}
			fclose(fp);
		}
		if(auriga_version == 0)
			auriga_version = AURIGA_REVISION;
	}

	return auriga_version;
}
