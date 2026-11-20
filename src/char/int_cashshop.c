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

#include <limits.h>
#include "socket.h"
#include "char.h"
#include "int_cashshop.h"

/* マップから指定された販売枠だけを扱い、過去の全履歴は転送しない。 */
int inter_cashshop_parse_frommap(int fd)
{
	int cmd = RFIFOW(fd, 0), len, count, i, j, account, char_id, ok = 0;
	unsigned int token;
	struct cashshop_account_count rows[CASHSHOP_ACCOUNT_MAX];
	const struct mmo_chardata *cd;

	if(cmd != 0x3094 && cmd != 0x3095)
		return 0;
	len = RFIFOW(fd, 2);
	if(len < 16 || (len - 16) % (cmd == 0x3094 ? 4 : 8))
		return 1;
	count = (len - 16) / (cmd == 0x3094 ? 4 : 8);
	if(count < 1 || count > CASHSHOP_ACCOUNT_MAX)
		return 1;
	account = RFIFOL(fd, 4);
	char_id = RFIFOL(fd, 8);
	token = RFIFOL(fd, 12);
	for(i = 0; i < count; i++) {
		rows[i].sale_id = RFIFOL(fd, 16 + i * (cmd == 0x3094 ? 4 : 8));
		rows[i].purchased = cmd == 0x3095 ? RFIFOL(fd, 20 + i * 8) : 0;
		if(rows[i].sale_id <= 0 || rows[i].purchased > INT_MAX)
			return 1;
		for(j = 0; j < i; j++) {
			if(rows[j].sale_id == rows[i].sale_id)
				return 1;
		}
	}
	cd = account > 0 && char_id > 0 ? chardb_load(char_id) : NULL;
	if(cd && cd->st.account_id == account && token) {
		if(cmd == 0x3094)
			ok = cashshopdb_load(account, rows, count);
		else
			ok = cashshopdb_save(account, rows, count);
	}

	if(cmd == 0x3094) {
		int out = ok ? 17 + count * 8 : 17;
		WFIFOW(fd, 0) = 0x3894;
		WFIFOW(fd, 2) = out;
		WFIFOL(fd, 4) = account;
		WFIFOL(fd, 8) = char_id;
		WFIFOL(fd, 12) = token;
		WFIFOB(fd, 16) = ok;
		if(ok) {
			for(i = 0; i < count; i++) {
				WFIFOL(fd, 17 + i * 8) = rows[i].sale_id;
				WFIFOL(fd, 21 + i * 8) = rows[i].purchased;
			}
		}
		WFIFOSET(fd, out);
	} else {
		WFIFOW(fd, 0) = 0x3895;
		WFIFOL(fd, 2) = account;
		WFIFOL(fd, 6) = char_id;
		WFIFOL(fd, 10) = token;
		WFIFOB(fd, 14) = ok;
		WFIFOSET(fd, 15);
		if(!ok)
			printf("cashshop: failed to save account %d history\n", account);
	}
	return 1;
}
