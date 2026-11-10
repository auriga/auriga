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

#define _INT_MAIL_C_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>

#include "socket.h"
#include "utils.h"
#include "timer.h"

#include "char.h"
#include "int_mail.h"
#include "int_achieve.h"

static int mail_system_expire_days;
static int mail_system_expire_action;
static int mail_return_days;
static int mail_delete_days;
static int mail_returned_expire_days;
static int mail_return_keep_attach = 1;
static int mail_expire_check_interval;

/*==========================================
 * メールの設定を読み込む
 *------------------------------------------
 */
int inter_mail_config_read(const char *key, const char *value)
{
	if(strcmpi(key, "mail_system_expire_days") == 0)
		mail_system_expire_days = atoi(value);
	else if(strcmpi(key, "mail_system_expire_action") == 0)
		mail_system_expire_action = atoi(value);
	else if(strcmpi(key, "mail_return_days") == 0)
		mail_return_days = atoi(value);
	else if(strcmpi(key, "mail_delete_days") == 0)
		mail_delete_days = atoi(value);
	else if(strcmpi(key, "mail_returned_expire_days") == 0)
		mail_returned_expire_days = atoi(value);
	else if(strcmpi(key, "mail_expire_check_interval") == 0)
		mail_expire_check_interval = atoi(value);
	else if(strcmpi(key, "mail_return_keep_attach") == 0)
		mail_return_keep_attach = atoi(value);
	else
		return 0;
	return 1;
}

//------------------------------------------------------------------------
int mapif_mail_res(const int fd,int account,int char_id,int flag,unsigned int token)
{
	WFIFOW(fd,0)=0x3848;
	WFIFOL(fd,2)=account;
	WFIFOB(fd,6)=flag;
	WFIFOL(fd,7)=char_id;
	WFIFOL(fd,11)=token;
	WFIFOSET(fd,15);
	return 0;
}

int mapif_send_mailbox(int fd,const char *char_name,int store,struct mail_data md[MAIL_STORE_MAX],int unread)
{
	int i,size = sizeof(struct mail_data);

	if(md == NULL)
		return 0;

	WFIFOW(fd,0)=0x3849;
	WFIFOL(fd,4)=store;
	memcpy(WFIFOP(fd,8),char_name,24);
	WFIFOL(fd,32) = unread ? 1 : 0;
	for(i=0;i<store;i++)
		memcpy(WFIFOP(fd,36+i*size),&md[i],size);
	WFIFOW(fd,2)=36+i*size;
	WFIFOSET(fd,WFIFOW(fd,2));
	return 0;
}

int mapif_mail_newmail(int fd,struct mail_data *md)
{
	unsigned char buf[4 + sizeof(struct mail_data)];

	(void)fd;
	WBUFW(buf,0) = 0x384a;
	WBUFW(buf,2) = sizeof(buf);
	memcpy(WBUFP(buf,4), md, sizeof(struct mail_data));
	mapif_sendall(buf, sizeof(buf));
	return 0;
}

int mapif_mail_readmail(int fd,struct mail_data *md)
{
	int size = sizeof(struct mail_data);

	WFIFOW(fd,0)=0x384b;
	WFIFOW(fd,2)=4+size;
	memcpy(WFIFOP(fd,4),md,size);
	WFIFOSET(fd,WFIFOW(fd,2));
	return 0;
}

int mapif_mail_delmail(int fd,int account,unsigned int mail_num,int flag)
{
	WFIFOW(fd,0)=0x384c;
	WFIFOL(fd,2)=account;
	WFIFOL(fd,6)=mail_num;
	WFIFOB(fd,10)=flag;
	WFIFOSET(fd,11);
	return 0;
}

int mapif_mail_returnres(int fd,int account,unsigned int mail_num,int flag)
{
	WFIFOW(fd,0)=0x3851;
	WFIFOL(fd,2)=account;
	WFIFOL(fd,6)=mail_num;
	WFIFOB(fd,10)=flag;
	WFIFOSET(fd,11);
	return 0;
}

/* 0: 保存成功、1: 保存失敗、2: 実績報酬受取済み */
int mapif_sysmail_res(int fd, struct mail_data *md, int flag)
{
	int size = sizeof(struct mail_data);

	if(!md)
		return 1;
	WFIFOW(fd,0) = 0x3852;
	WFIFOW(fd,2) = 5 + size;
	WFIFOB(fd,4) = (unsigned char)flag;
	memcpy(WFIFOP(fd,5), md, size);
	WFIFOSET(fd, WFIFOW(fd,2));
	return 0;
}

int mapif_mail_getappend(int fd, int account, int char_id, enum mail_attachment_type type, struct mail_data *md)
{
	int i, size = sizeof(md->item);

	if(!md)
		return 1;
	if(type == MAIL_ATTACH_ALL && md->zeny <= 0) {
		for(i = 0; i < MAIL_MAX_ITEM; i++) {
			if(md->item[i].nameid > 0 && md->item[i].amount > 0)
				break;
		}
		if(i == MAIL_MAX_ITEM)
			return 1;
	}

	WFIFOW(fd,0)=0x384d;
	WFIFOW(fd,2)=21+size;
	WFIFOL(fd,4)=account;
	WFIFOL(fd,8)=(md->zeny <= 0)? 0: md->zeny;
	WFIFOL(fd,12)=md->mail_num;
	WFIFOL(fd,16)=char_id;
	WFIFOB(fd,20)=type;
	memcpy(WFIFOP(fd,21),md->item,size);
	WFIFOSET(fd,WFIFOW(fd,2));

	return 0;
}

int mapif_mail_checkok(int fd,int account,struct mail_data *md)
{
	int size = sizeof(struct mail_data);

	if(!md)
		return 1;

	WFIFOW(fd,0) = 0x384e;
	WFIFOW(fd,2) = 8+size;
	WFIFOL(fd,4) = account;
	memcpy(WFIFOP(fd,8),md,size);
	WFIFOSET(fd,WFIFOW(fd,2));
	return 0;
}

//--------------------------------------------------------
static int mail_append_to_box(const struct mmo_chardata *rd, struct mail_data *md)
{
	const struct mail *m;

	if(rd == NULL || md == NULL)
		return 0;

	// テキスト形式のメールデータで区切り文字になる文字を拒否する
	if(strpbrk(md->char_name, "\t\r\n") || strpbrk(md->receive_name, "\t\r\n") ||
	   strpbrk(md->title, "\t\r\n"))
		return 0;

	m = maildb_load(rd->st.char_id);
	if(m) {
		struct mail m2;
		if(m->store < 0 || m->store == INT_MAX || m->rates == UINT_MAX)
			return 0;
		memcpy(&m2, m, sizeof(struct mail));
		m2.rates++;
		m2.store++;
		if(!maildb_save(&m2))
			return 0;
		md->mail_num = m2.rates;
	} else {
		if(!maildb_new(rd->st.account_id, rd->st.char_id))
			return 0;
		md->mail_num = 1;
	}
	if(md->times == 0)
		md->times = (unsigned int)time(NULL);
	if(!maildb_store_mail(rd->st.char_id, md)) {
		m = maildb_load(rd->st.char_id);
		if(m && m->store > 0) {
			struct mail m2 = *m;
			m2.store--;
			maildb_save(&m2);
		}
		return 0;
	}
	return 1;
}

/* プレイヤーメールを返送する。成功は1、保存失敗時は-1を返す */
static int mail_return_one(int owner_char_id, struct mail_data *md, int fd_notify)
{
	const struct mmo_chardata *sd_sender;
	const struct mmo_chardata *sd_owner;
	const struct mail *m;
	struct mail_data ret;
	char owner_name[24];

	if(md == NULL)
		return 0;
	/* system mail: never return */
	if(md->read & MAIL_READ_SYSTEM)
		return 0;
	/* already returned */
	if(md->read & MAIL_READ_RETURNED)
		return 0;

	sd_sender = md->char_id > 0 ? chardb_load(md->char_id) : chardb_nick2chardata(md->char_name);
	if(sd_sender == NULL)
		return 0;

	sd_owner = chardb_load(owner_char_id);
	memset(owner_name, 0, sizeof(owner_name));
	if(sd_owner)
		strncpy(owner_name, sd_owner->st.name, 24);
	else {
		strncpy(owner_name, md->receive_name, 24);
		owner_name[23] = '\0';
	}

	memset(&ret, 0, sizeof(ret));
	ret.char_id = owner_char_id;
	strncpy(ret.char_name, owner_name, 24);
	strncpy(ret.receive_name, sd_sender->st.name, sizeof(ret.receive_name));
	ret.receive_name[23] = '\0';
	strncpy(ret.title, md->title, sizeof(ret.title));
	memcpy(ret.body, md->body, sizeof(ret.body));
	ret.body_size = md->body_size;
	ret.read = MAIL_READ_RETURNED; /* returned, not opened */
	ret.times = (unsigned int)time(NULL);

	if(mail_return_keep_attach) {
		ret.zeny = md->zeny;
		memcpy(ret.item, md->item, sizeof(ret.item));
	}

	if(!mail_append_to_box(sd_sender, &ret))
		return -1; /* 返送先への保存に失敗したため元メールを保持 */

	m = maildb_load(owner_char_id);
	if(m == NULL || !maildb_deletemail(owner_char_id, md->mail_num, m)) {
		/* original still present with attach -> drop duplicate on sender, hold original */
		maildb_deletemail(sd_sender->st.char_id, ret.mail_num, maildb_load(sd_sender->st.char_id));
		return -1;
	}
	if(fd_notify >= 0)
		mapif_mail_newmail(fd_notify, &ret);
	return 1;
}

static void mail_apply_lifecycle(int char_id, struct mail_data *md, int capacity, int fd_notify, int max_actions)
{
	const struct mail *m;
	unsigned int now;
	uint64 limit;
	int i;

	m = maildb_load(char_id);
	if(m == NULL || m->store <= 0)
		return;

	now = (unsigned int)time(NULL);

	for(i = 0; i < m->store; ) {
		int acted = 0;
		unsigned int age = 0;

		if(md[i].times != 0 && now >= md[i].times)
			age = now - md[i].times;

		/* 1) returned mails expire after mail_returned_expire_days */
		if((md[i].read & MAIL_READ_RETURNED) && mail_returned_expire_days > 0) {
			limit = (uint64)mail_returned_expire_days * 24u * 60u * 60u;
			if(age >= limit) {
				acted = maildb_deletemail(char_id, md[i].mail_num, m);
			}
		}
		/* 2) system mails: discard/hold per mail_system_expire_* (never return) */
		else if((md[i].read & MAIL_READ_SYSTEM) && mail_system_expire_days > 0 && mail_system_expire_action != 1) {
			limit = (uint64)mail_system_expire_days * 24u * 60u * 60u;
			if(age >= limit) {
				acted = maildb_deletemail(char_id, md[i].mail_num, m);
			}
		}
		/* 3) player mail unopened -> return (exclude returned/system) */
		else if(!(md[i].read & MAIL_READ_SYSTEM) && !(md[i].read & MAIL_READ_RETURNED)
			&& !(md[i].read & MAIL_READ_OPENED) && mail_return_days > 0) {
			limit = (uint64)mail_return_days * 24u * 60u * 60u;
			if(age >= limit) {
				int rr = mail_return_one(char_id, &md[i], fd_notify);
				if(rr > 0)
					acted = 1;
				else if(rr == 0) {
					/* sender missing or hard fail: delete */
					acted = maildb_deletemail(char_id, md[i].mail_num, m);
				}
				/* rr < 0: 返送に失敗したため元メールを保持 */
			}
		}
		/* 4) player mail opened -> delete after mail_delete_days */
		else if(!(md[i].read & MAIL_READ_SYSTEM) && !(md[i].read & MAIL_READ_RETURNED)
			&& (md[i].read & MAIL_READ_OPENED) && mail_delete_days > 0) {
			limit = (uint64)mail_delete_days * 24u * 60u * 60u;
			if(age >= limit) {
				acted = maildb_deletemail(char_id, md[i].mail_num, m);
			}
		}

		if(acted) {
			if(max_actions > 0 && --max_actions == 0)
				return;
			memset(md, 0, sizeof(struct mail_data) * capacity);
			m = maildb_load(char_id);
			if(m == NULL || m->store <= 0)
				return;
			if(!maildb_read_mail(char_id, m, md, capacity))
				return;
			i = 0;
			continue;
		}
		i++;
	}
}

/* 期限処理は一度に一つの受信箱から最大一通ずつ進める。 */
static int inter_mail_expire_timer(int tid, unsigned int tick, int id, void *data)
{
	int char_id, capacity;
	const struct mail *m;
	struct mail_data *md;

	if(!mail_system_expire_days && !mail_return_days && !mail_delete_days && !mail_returned_expire_days)
		return 0;
	if(!maildb_next(&char_id))
		return 0;
	m = maildb_load(char_id);
	if(m == NULL || m->store <= 0)
		return 0;
	capacity = m->store;
	md = (struct mail_data *)calloc((size_t)capacity, sizeof(*md));
	if(md == NULL)
		return 0;
	if(maildb_read_mail(char_id, m, md, capacity))
		mail_apply_lifecycle(char_id, md, capacity, 0, 1);
	free(md);
	return 0;
}

int inter_mail_init(void)
{
	int interval;

	if(mail_expire_check_interval <= 0 ||
	   (!mail_system_expire_days && !mail_return_days && !mail_delete_days && !mail_returned_expire_days))
		return 0;
	if(mail_expire_check_interval > INT_MAX / 1000)
		mail_expire_check_interval = INT_MAX / 1000;
	interval = mail_expire_check_interval * 1000;
	maildb_scan_enable();
	add_timer_func_list(inter_mail_expire_timer);
	add_timer_interval(gettick() + interval, inter_mail_expire_timer, 0, NULL, interval);
	return 0;
}

/* 全メールの未読状態を調べる */
static int mail_has_unread(const struct mail_data *md, int count)
{
	int i;
	for(i = 0; i < count; i++) {
		if(!(md[i].read & MAIL_READ_OPENED))
			return 1;
	}
	return 0;
}

int mapif_parse_OpenMailBox(int fd)
{
	int char_id = RFIFOL(fd,2), capacity, count;
	const struct mmo_chardata *rd = chardb_load(char_id);
	const struct mail *m;
	struct mail_data *md, empty;

	if(rd == NULL)
		return 0;
	memset(&empty, 0, sizeof(empty));
	m = maildb_load(char_id);
	if(m == NULL || m->store == 0) {
		mapif_send_mailbox(fd, rd->st.name, 0, &empty, 0);
		return 0;
	}
	if(m->store < 0)
		return 0;
	capacity = m->store;
	md = (struct mail_data *)calloc((size_t)capacity, sizeof(*md));
	if(md == NULL)
		return 0;
	if(!maildb_read_mail(char_id, m, md, capacity)) {
		free(md);
		return 0;
	}
	if(mail_system_expire_days || mail_return_days || mail_delete_days || mail_returned_expire_days) {
		mail_apply_lifecycle(char_id, md, capacity, fd, 0);
		m = maildb_load(char_id);
		if(m == NULL || m->store == 0) {
			mapif_send_mailbox(fd, rd->st.name, 0, &empty, 0);
			free(md);
			return 0;
		}
		if(m->store < 0 || m->store > capacity) {
			free(md);
			return 0;
		}
		memset(md, 0, sizeof(*md) * capacity);
		if(!maildb_read_mail(char_id, m, md, capacity)) {
			free(md);
			return 0;
		}
	}
	count = m->store < MAIL_STORE_MAX ? m->store : MAIL_STORE_MAX;
	mapif_send_mailbox(fd, rd->st.name, count, md + m->store - count, mail_has_unread(md, m->store));
	free(md);
	return 0;
}

/* 送信できなかった添付はシステムメールで送信者に返す */
static void mapif_mail_send_failed(int fd, const struct mmo_chardata *sender, const struct mail_data *md)
{
	struct mail_data returned;
	int i, result = 1;
	bool has_attachment = md->zeny > 0 || md->send_fee > 0;

	for(i = 0; i < MAIL_MAX_ITEM; i++) {
		if(md->item[i].nameid > 0 && md->item[i].amount > 0) {
			has_attachment = true;
			break;
		}
	}
	if(has_attachment && md->send_fee >= 0 && md->zeny >= 0 && md->send_fee <= MAX_ZENY - md->zeny) {
		returned = *md;
		returned.zeny += returned.send_fee;
		returned.send_fee = 0;
		returned.char_id = 0;
		returned.send_token = 0;
		returned.mail_num = 0;
		returned.read = MAIL_READ_SYSTEM;
		returned.times = 0;
		auriga_strlcpy(returned.char_name, "System", sizeof(returned.char_name));
		auriga_strlcpy(returned.receive_name, sender->st.name, sizeof(returned.receive_name));
		auriga_strlcpy(returned.title, "送信失敗による添付の返却", sizeof(returned.title));
		auriga_strlcpy(returned.body, "メールを送信できなかったため、添付を返却しました。", sizeof(returned.body));
		returned.body_size = (unsigned int)strlen(returned.body);
		if(mail_append_to_box(sender, &returned))
			result = 2;
	}
	mapif_mail_res(fd, sender->st.account_id, md->char_id, result, md->send_token);
	if(result == 2)
		mapif_mail_newmail(fd, &returned);
}

int mapif_parse_SendMail(int fd)
{
	const struct mmo_chardata *sd, *rd;
	struct mail_data md;

	if(RFIFOW(fd,2) != 4 + sizeof(md))
		return 0;

	memcpy(&md,RFIFOP(fd,4),sizeof(struct mail_data));
	md.read = 0;
	if(md.body_size > sizeof(md.body))
		return 0;

	md.char_name[sizeof(md.char_name)-1] = '\0';
	md.receive_name[sizeof(md.receive_name)-1] = '\0';
	md.title[sizeof(md.title)-1] = '\0';
	sd = chardb_load(md.char_id);
	if(sd == NULL)
		return 0;

	rd = chardb_nick2chardata(md.receive_name);

	// 受け取る人が存在しません
	if(rd == NULL)
	{
		mapif_mail_send_failed(fd, sd, &md);
		return 0;
	}

	// 同じアカウントには送れない
	if(sd->st.account_id == rd->st.account_id)
	{
		mapif_mail_send_failed(fd, sd, &md);
		return 0;
	}

	if(!mail_append_to_box(rd, &md))
	{
		mapif_mail_send_failed(fd, sd, &md);
		return 0;
	}

	mapif_mail_res(fd,sd->st.account_id,md.char_id,0,md.send_token);
	mapif_mail_newmail(fd,&md);
	return 0;
}

int mapif_parse_SendSysMail(int fd)
{
	const struct mmo_chardata *rd;
	struct mail_data md;
	int reward_char_id, reward_state;

	if(RFIFOW(fd,2) != 4 + sizeof(md))
		return 0;

	memcpy(&md, RFIFOP(fd,4), sizeof(struct mail_data));
	reward_char_id = md.char_id;
	md.char_id = 0;
	md.read = MAIL_READ_SYSTEM;
	md.char_name[sizeof(md.char_name)-1] = '\0';
	md.receive_name[sizeof(md.receive_name)-1] = '\0';
	md.title[sizeof(md.title)-1] = '\0';
	if(md.body_size > sizeof(md.body))
		return 0;

	rd = chardb_nick2chardata(md.receive_name);
	if(rd == NULL) {
		md.char_id = reward_char_id;
		mapif_sysmail_res(fd, &md, 1);
		return 0;
	}

	if(md.send_token != 0) {
		if(reward_char_id <= 0 || rd->st.char_id != reward_char_id) {
			md.char_id = reward_char_id;
			mapif_sysmail_res(fd, &md, 1);
			return 0;
		}
		reward_state = achievement_mail_state(reward_char_id, md.send_token);
		if(reward_state != ACH_REWARD_UNCLAIMED) {
			md.char_id = reward_char_id;
			mapif_sysmail_res(fd, &md, reward_state == ACH_REWARD_CLAIMED ? 2 : 1);
			return 0;
		}
	}
	if(!mail_append_to_box(rd, &md)) {
		md.char_id = reward_char_id;
		mapif_sysmail_res(fd, &md, 1);
		return 0;
	}
	if(md.send_token != 0 && !achievement_mail_saved(reward_char_id, md.send_token)) {
		const struct mail *m = maildb_load(reward_char_id);
		if(m && !maildb_deletemail(reward_char_id, md.mail_num, m))
			printf("achievement mail: rollback failed for character %d\n", reward_char_id);
		md.char_id = reward_char_id;
		mapif_sysmail_res(fd, &md, 1);
		return 0;
	}
	mapif_mail_newmail(fd, &md);
	md.char_id = reward_char_id;
	mapif_sysmail_res(fd, &md, 0);
	return 0;
}

static struct mail_data *mail_read_all(int char_id, const struct mail *m)
{
	struct mail_data *md;
	int capacity;

	if(m == NULL || m->store <= 0)
		return NULL;
	capacity = m->store;
	md = (struct mail_data *)calloc((size_t)capacity, sizeof(*md));
	if(md == NULL)
		return NULL;
	if(!maildb_read_mail(char_id, m, md, capacity)) {
		free(md);
		return NULL;
	}
	return md;
}

static void mapif_send_mailbox_latest(int fd, const char *name, const struct mail *m, struct mail_data *md)
{
	int count = m->store < MAIL_STORE_MAX ? m->store : MAIL_STORE_MAX;
	mapif_send_mailbox(fd, name, count, md + m->store - count, mail_has_unread(md, m->store));
}

int mapif_parse_DeleteMail(int fd)
{
	const struct mail *m = maildb_load(RFIFOL(fd,2));
	int flag;

	if(!m)
		return 0;

	flag = 0;
	if(m->store > 0) {
		struct mail_data *md;
		unsigned int mail_num = RFIFOL(fd,6);
		int i, j;
		md = mail_read_all(m->char_id, m);
		if(md) {
			for(i = 0; i < m->store; i++) {
				if(md[i].mail_num != mail_num)
					continue;
				for(j = 0; j < MAIL_MAX_ITEM; j++) {
					if(md[i].item[j].nameid > 0 && md[i].item[j].amount > 0)
						break;
				}
				if(j == MAIL_MAX_ITEM && md[i].zeny <= 0)
					flag = maildb_deletemail(m->char_id, mail_num, m);
				break;
			}
		}
		free(md);
	}
	mapif_mail_delmail(fd,m->account_id,RFIFOL(fd,6),!flag);	// 結果送信

	return 0;
}

int mapif_parse_ReadMail(int fd)
{
	const struct mail *m;
	const struct mmo_chardata *cd;
	int char_id = RFIFOL(fd,2);
	unsigned int mail_num = RFIFOL(fd,6);

	if((m = maildb_load(char_id)) == NULL)
		return 0;

	cd = chardb_load(char_id);

	if(m->store > 0)
	{
		struct mail_data *md;
		int i;

		md = mail_read_all(char_id, m);
		if(md == NULL)
			return 0;

		for( i = 0; i < m->store; i++ )
		{
			if(md[i].mail_num == mail_num)
			{
				mapif_mail_readmail(fd,&md[i]);
				if(!(md[i].read & MAIL_READ_OPENED))
				{
					md[i].read |= MAIL_READ_OPENED;
					maildb_save_mail(char_id,i,m->store,md);
					mapif_send_mailbox_latest(fd, cd ? cd->st.name : md[i].receive_name, m, md);
				}
				break;
			}
		}
		free(md);
	}

	return 0;
}

int mapif_parse_GetAppend(int fd)
{
	const struct mail *m;
	int char_id = RFIFOL(fd,2);
	unsigned int mail_num = RFIFOL(fd,6);
	enum mail_attachment_type type = RFIFOB(fd,10);

	if(type > MAIL_ATTACH_ITEM)
		return 0;

	if((m = maildb_load(char_id)) == NULL)
		return 0;

	if(m->store > 0)
	{
		struct mail_data *md;
		int i;

		md = mail_read_all(char_id, m);
		if(md == NULL)
			return 0;

		for( i = 0; i < m->store; i++ )
		{
			if(md[i].mail_num == mail_num)
			{
				struct mail_data snap = md[i];
				// 要求された添付だけを取り出す
				if(type == MAIL_ATTACH_ZENY)
					memset(snap.item, 0, sizeof(snap.item));
				else if(type == MAIL_ATTACH_ITEM)
					snap.zeny = 0;
				if(type != MAIL_ATTACH_ZENY || snap.zeny > 0) {
					if(type != MAIL_ATTACH_ZENY)
						memset(md[i].item, 0, sizeof(md[i].item));
					if(type != MAIL_ATTACH_ITEM)
						md[i].zeny = 0;
					if(!maildb_save_mail(char_id, i, m->store, md))
						break;
				}
				if(!mapif_mail_getappend(fd, m->account_id, char_id, type, &snap))
					mapif_mail_readmail(fd, &md[i]);
				break;
			}
		}
		free(md);
	}

	return 0;
}

int mapif_parse_CheckMail(int fd)
{
	int send_id = RFIFOL(fd,4);
	struct mail_data *md = (struct mail_data *)RFIFOP(fd,8);
	const struct mmo_chardata *rd;

	if(md == NULL)
		return 0;

	rd = chardb_nick2chardata(md->receive_name);

	// 受け取る人が存在しません
	if(rd == NULL || rd->st.account_id == send_id)
		mapif_mail_res(fd,send_id,md->char_id,1,md->send_token);
	else
		mapif_mail_checkok(fd,send_id,md);

	return 0;
}

int mapif_parse_ReturnMail(int fd)
{
	int char_id = RFIFOL(fd,2);
	unsigned int mail_num = RFIFOL(fd,6);
	const struct mail *m;
	const struct mmo_chardata *cd;
	struct mail_data *md;
	int i, ok = 0;
	int account_id = 0;

	cd = chardb_load(char_id);
	if(cd)
		account_id = cd->st.account_id;

	m = maildb_load(char_id);
	if(m == NULL || m->store <= 0) {
		mapif_mail_returnres(fd, account_id, mail_num, 1);
		return 0;
	}

	md = mail_read_all(char_id, m);
	if(md == NULL) {
		mapif_mail_returnres(fd, account_id, mail_num, 1);
		return 0;
	}
	for(i = 0; i < m->store; i++) {
		if(md[i].mail_num != mail_num)
			continue;
		if(md[i].read & MAIL_READ_SYSTEM) {
			ok = 0;
			break;
		}
		ok = (mail_return_one(char_id, &md[i], fd) > 0) ? 1 : 0;
		break;
	}
	free(md);
	mapif_mail_returnres(fd, account_id, mail_num, ok ? 0 : 1);
	return 0;
}

int mapif_parse_RestoreAppend(int fd)
{
	int char_id = RFIFOL(fd,4);
	unsigned int mail_num = RFIFOL(fd,8);
	int zeny = RFIFOL(fd,12);
	struct item *it = (struct item *)RFIFOP(fd,16);
	const struct mail *m = maildb_load(char_id);
	struct mail_data *md;
	int i;

	if(RFIFOW(fd,2) != 16 + sizeof(struct item) * MAIL_MAX_ITEM || !m || m->store <= 0)
		return 0;

	md = mail_read_all(char_id, m);
	if(md == NULL)
		return 0;
	for(i = 0; i < m->store; i++) {
		if(md[i].mail_num != mail_num)
			continue;
		// 受け取れなかった添付だけを戻す
		if(zeny > 0 && md[i].zeny == 0)
			md[i].zeny = zeny;
		{
			int j;
			for(j = 0; j < MAIL_MAX_ITEM; j++) {
				if(it[j].nameid > 0 && it[j].amount > 0 && md[i].item[j].nameid == 0)
					memcpy(&md[i].item[j], &it[j], sizeof(struct item));
			}
		}
		maildb_save_mail(char_id, i, m->store, md);
		break;
	}
	free(md);
	return 0;
}

int mapif_parse_DeleteAppend(int fd)
{
	int char_id = RFIFOL(fd,2);
	unsigned int mail_num = RFIFOL(fd,6);
	const struct mail *m = maildb_load(char_id);

	if( !m )
		return 0;

	if(m->store > 0)
	{
		struct mail_data *md;
		int i;

		md = mail_read_all(char_id, m);
		if(md == NULL)
			return 0;

		for( i = 0; i < m->store; i++ )
		{
			if( md[i].mail_num == mail_num )
			{
				// ここで添付アイテムとzenyを削除する
				memset(md[i].item, 0, sizeof(md[i].item));
				md[i].zeny = 0;
				maildb_save_mail(char_id, i, m->store, md);
				break;
			}
		}
		free(md);
	}

	return 0;
}

/*==========================================
 * RoDEXの宛先を照会する
 *------------------------------------------
 */
static void mapif_parse_MailRecipient(int fd)
{
	const struct mmo_chardata *cd;
	char name[24];

	memcpy(name, RFIFOP(fd,6), sizeof(name));
	name[sizeof(name)-1] = '\0';
	cd = chardb_nick2chardata(name);

	WFIFOW(fd,0) = 0x3853;
	WFIFOL(fd,2) = RFIFOL(fd,2);
	WFIFOL(fd,6) = cd ? cd->st.char_id : 0;
	WFIFOW(fd,10) = cd ? cd->st.class_ : 0;
	WFIFOW(fd,12) = cd ? cd->st.base_level : 0;
	memcpy(WFIFOP(fd,14), cd ? cd->st.name : name, sizeof(name));
	WFIFOSET(fd,38);
}

// map server からの通信
// ・１パケットのみ解析すること
// ・パケット長データはinter.cにセットしておくこと
// ・パケット長チェックや、RFIFOSKIPは呼び出し元で行われるので行ってはならない
// ・エラーなら0(false)、そうでないなら1(true)をかえさなければならない
int inter_mail_parse_frommap(int fd)
{
	switch(RFIFOW(fd,0)) {
	case 0x3049: mapif_parse_OpenMailBox(fd);    break;
	case 0x304a: mapif_parse_SendMail(fd);       break;
	case 0x304b: mapif_parse_DeleteMail(fd);     break;
	case 0x304c: mapif_parse_ReadMail(fd);       break;
	case 0x304d: mapif_parse_GetAppend(fd);      break;
	case 0x304e: mapif_parse_CheckMail(fd);      break;
	case 0x304f: mapif_parse_DeleteAppend(fd);   break;
	case 0x3050: mapif_parse_SendSysMail(fd);    break;
	case 0x3051: mapif_parse_ReturnMail(fd);     break;
	case 0x3052: mapif_parse_RestoreAppend(fd);  break;
	case 0x3053: mapif_parse_MailRecipient(fd);  break;
	default:
		return 0;
	}
	return 1;
}
