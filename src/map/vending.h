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

#ifndef	_VENDING_H_
#define	_VENDING_H_

#include "map.h"
#include "utils.h"

void vending_closevending(struct map_session_data *sd);
void vending_openvending(struct map_session_data *sd, short count, const char *shop_title, bool is_open, const unsigned char *data);
void vending_vendinglistreq(struct map_session_data *sd,int id);
void vending_purchasereq(struct map_session_data *sd, short count, int account_id, unsigned int vender_id, const unsigned char *data);

#endif	// _VENDING_H_
