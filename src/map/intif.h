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

#ifndef _INTIF_H_
#define _INFIF_H_

#include "utils.h"

int intif_parse(int fd);

// メッセージ送信関連
void intif_GMmessage(const char* mes, size_t len, int flag);
int intif_announce(const char* mes,size_t len,unsigned int color,int type,int size,int align,int pos_y);
void intif_wis_message(struct map_session_data *sd, const char *nick, const char *mes, size_t mes_len);

// アカウント変数関連
int intif_saveaccountreg(struct map_session_data *sd);
int intif_request_accountreg(struct map_session_data *sd);

// 倉庫関連
int intif_request_storage(int account_id);
int intif_send_storage(struct storage *stor);
int intif_request_guild_storage(int account_id,int guild_id);
int intif_send_guild_storage(int account_id,struct guild_storage *gstor);
int intif_trylock_guild_storage(struct map_session_data *sd,int npc_id);
int intif_unlock_guild_storage(int guild_id);
int intif_deadlock_guild_storage(int guild_id);

// パーティー関連
void intif_create_party(struct map_session_data *sd, const char *name, int item, int item2);
int intif_request_partyinfo(int party_id);
void intif_party_addmember(struct map_session_data *sd);
void intif_party_changeoption(int party_id, int account_id, int baby_id, int exp, int item);
void intif_party_leave(int party_id, int account_id, int char_id);
void intif_party_changemap(struct map_session_data *sd, unsigned char online);
int intif_break_party(int party_id);
int intif_party_message(int party_id,int account_id,const char *mes,size_t len);
int intif_party_checkconflict(int party_id,int account_id,int char_id);
int intif_party_leaderchange(int party_id,int account_id,int char_id);

// ギルド関連
void intif_guild_create(const char *name, const struct guild_member *master);
void intif_guild_request_info(int guild_id);
int intif_guild_addmember(int guild_id,struct guild_member *m);
int intif_guild_leave(int guild_id,int account_id,int char_id,int flag,const char *mes);
void intif_guild_memberinfoshort(int guild_id, int account_id, int char_id, unsigned char online, int lv, int class_);
int intif_guild_break(int guild_id);
int intif_guild_message(int guild_id,int account_id,const char *mes,size_t len);
int intif_guild_checkconflict(int guild_id,int account_id,int char_id);
int intif_guild_change_basicinfo(int guild_id,int type,const void *data,int len);
int intif_guild_change_memberinfo(int guild_id,int account_id,int char_id,int type,const void *data,int len);
void intif_guild_position(int guild_id, int idx, struct guild_position *p);
int intif_guild_skillup(int guild_id,int skill_num,int account_id,int level,unsigned char flag);
int intif_guild_alliance(int guild_id1,int guild_id2,int account_id1,int account_id2,int flag);
void intif_guild_notice(int guild_id, const char *mes1, const char *mes2);
void intif_guild_emblem(int guild_id, unsigned short len, const char *data);
int intif_guild_castle_dataload(int castle_id,int index);
int intif_guild_castle_datasave(int castle_id,int index, int value);

// ペット関連
void intif_create_pet(int account_id, int char_id, short pet_type, short pet_lv, short pet_egg_id,
	short pet_equip, short intimate, short hungry, char rename_flag, char incubate, const char *pet_name);
void intif_request_petdata(int account_id, int char_id, int pet_id);
void intif_save_petdata(int account_id, struct s_pet *p);
void intif_delete_petdata(int pet_id);

// ホムンクルス関連
void intif_create_hom(int account_id, int char_id, struct mmo_homunstatus *h);
void intif_request_homdata(int account_id, int char_id, int homun_id);
void intif_save_homdata(int account_id, struct mmo_homunstatus *h);
void intif_delete_homdata(int account_id, int char_id, int homun_id);

// 傭兵関連
void intif_create_merc(int account_id, int char_id, struct mmo_mercstatus *m);
void intif_request_mercdata(int account_id, int char_id, int merc_id);
void intif_save_mercdata(int account_id, struct mmo_mercstatus *m);
void intif_delete_mercdata(int account_id, int char_id, int merc_id);

// 精霊関連
void intif_create_elem(int account_id, int char_id, struct mmo_elemstatus *e);
void intif_request_elemdata(int account_id, int char_id, int elem_id);
void intif_save_elemdata(int account_id, struct mmo_elemstatus *e);
void intif_delete_elemdata(int account_id, int char_id, int elem_id);

// メール関連
int intif_mailbox(int char_id);
int intif_sendmail(struct mail_data *md);
int intif_deletemail(int char_id, int mail_num);
int intif_readmail(int char_id, int mail_num);
int intif_mail_getappend(int char_id, int mail_num);
int intif_mail_checkmail(int accound_id, struct mail_data *md);
int intif_mail_deleteappend(int char_id, int mail_num);

// 状態異常関連
int intif_request_scdata(int account_id,int char_id);
int intif_save_scdata(struct map_session_data *sd);

// クエストリスト関連
int intif_request_quest(int account_id,int char_id);
int intif_save_quest(struct map_session_data *sd);

// 実績関連
int intif_request_achieve(int account_id,int char_id);
int intif_save_achieve(struct map_session_data *sd);

// その他
int intif_jumpto(int account_id,const char *name);
int intif_where(int account_id,const char *name);
int intif_charmovereq(struct map_session_data *sd,const char *name,int flag);
int intif_charmovereq2(struct map_session_data *sd,const char *name,const char *mapname,short x, short y,int flag);
int intif_displaymessage(int account_id, const char* mes);
int intif_char_connect_limit(int limit);

#endif
