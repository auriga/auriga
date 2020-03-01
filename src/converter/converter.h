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

#ifndef _CONVERTER_H_
#define _CONVERTER_H_

extern char converter_conf_filename[];

extern unsigned short db_server_port;
extern char db_server_ip[16];
extern char db_server_id[32];
extern char db_server_pw[32];
extern char db_server_logindb[32];

extern char login_db[1024];
extern char login_db_account_id[1024];
extern char login_db_userid[1024];
extern char login_db_user_pass[1024];
extern char login_db_level[1024];

extern char map_server_tag[16];

extern char account_filename[1024];
extern char char_txt[1024];
extern char GM_account_filename[1024];
extern char pet_txt[1024];
extern char storage_txt[1024];
extern char party_txt[1024];
extern char guild_txt[1024];
extern char guild_storage_txt[1024];
extern char castle_txt[1024];
extern char homun_txt[1024];
extern char account_reg_txt[1024];
extern char scdata_txt[1024];
extern char mail_txt[1024];
extern char mail_dir[1024];
extern char mapreg_txt[1024];

#endif
