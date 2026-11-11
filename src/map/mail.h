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

#ifndef _MAIL_H_
#define _MAIL_H_

void mail_setitem(struct map_session_data *sd, int index, int amount);
int mail_removeitem(struct map_session_data *sd, int flag);
int mail_removeitem_index(struct map_session_data *sd, int client_idx, int *out_amount);
int mail_append_weight(struct map_session_data *sd);
int mail_checkmail(struct map_session_data *sd, const char *name, const char *title,const char *body, int len);
int mail_sendmail(struct map_session_data *sd, struct mail_data *md);
void mail_getappend(int account_id, int char_id, int zeny, unsigned int mail_num, enum mail_attachment_type type, struct item *item);
void mail_refund_pending(struct map_session_data *sd);
int mail_send_system(const char *dest_name, const char *sender_name,
	const char *title, const char *body, int body_len,
	int zeny, const struct item *item);
int mail_send_achievement(const char *dest_name, const char *sender_name,
	const char *title, const char *body, int body_len,
	const struct item *item, int char_id, unsigned int achievement_id);
#define mail_is_system(md) ((md) && ((md)->read & MAIL_READ_SYSTEM))

#endif
