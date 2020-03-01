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

#ifndef _BUYINGSTORE_H_
#define _BUYINGSTORE_H_

#include "utils.h"

bool buyingstore_openstorewindow(struct map_session_data *sd, unsigned char count);
void buyingstore_openstore(struct map_session_data *sd, int limit_zeny, bool result, const char *store_name, const unsigned char *data, int count);
void buyingstore_close(struct map_session_data *sd);
void buyingstore_itemlist(struct map_session_data* sd, int account_id);
void buyingstore_sell(struct map_session_data *sd, int account_id, unsigned int buyer_id, const unsigned char *data, int count);

#endif  // _BUYINGSTORE_H_
