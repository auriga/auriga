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

#ifndef _VERSION_H_
#define _VERSION_H_

#define AURIGA_MAJOR_VERSION	0	// Major Version
#define AURIGA_MINOR_VERSION	0	// Minor Version
#define AURIGA_REVISION			1129	// Revision

#define AURIGA_RELEASE_FLAG		1	// 1=Develop,0=Stable
#define AURIGA_OFFICIAL_FLAG	0	// 1=Mod,0=Official

#define AURIGA_SERVER_LOGIN		1	// login server
#define AURIGA_SERVER_CHAR		2	// char server
#define AURIGA_SERVER_INTER		4	// inter server
#define AURIGA_SERVER_MAP		8	// map server

// AURIGA_MOD_VERSIONÇÕñ¢íËã`Ç≈Ç∑
// Revisionî‘çÜÇçXêVÇµÇƒÇ≠ÇæÇ≥Ç¢
#define AURIGA_MOD_VERSION	0	// mod version

int get_current_version(void);

#endif
