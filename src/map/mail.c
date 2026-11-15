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
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>

#include "nullpo.h"
#include "malloc.h"
#include "utils.h"

#include "map.h"
#include "mail.h"
#include "clif.h"
#include "intif.h"
#include "chrif.h"
#include "itemdb.h"
#include "pc.h"
#include "battle.h"
#include "pet.h"

/*==========================================
 * アイテムやZenyを添付
 *------------------------------------------
 */
/* 添付重量はクライアント表示単位で計算する */
static int64 mail_append_total_weight(struct map_session_data *sd)
{
	int i;
	int64 weight = 0;

	nullpo_retr(0, sd);
	for(i = 0; i < sd->mail_append.count; i++) {
		int idx = sd->mail_append.index[i];
		if(idx >= 0 && idx < MAX_INVENTORY && sd->inventory_data[idx])
			weight += (int64)(sd->inventory_data[idx]->weight / 10) * sd->mail_append.amount[i];
	}
	return weight;
}

/* 送金手数料と添付種類ごとの料金を合算する */
static int mail_calc_fee(int zeny, int item_count)
{
	int64 fee = 0;

	if(zeny > 0 && battle_config.mail_zeny_fee > 0)
		fee += (int64)zeny * battle_config.mail_zeny_fee / 100;
	if(item_count > 0 && battle_config.mail_attachment_price > 0)
		fee += (int64)item_count * battle_config.mail_attachment_price;
	return fee > MAX_ZENY ? -1 : (int)fee;
}

int mail_append_weight(struct map_session_data *sd)
{
	int64 weight = mail_append_total_weight(sd);
	return (weight > 65535) ? 65535 : (int)weight;
}

void mail_setitem(struct map_session_data *sd, int idx, int amount)
{
	int i, limit;

	nullpo_retv(sd);
	if(sd->mail_preflight_token || sd->mail_pending_flag || sd->state.storage_flag || sd->state.deal_mode || sd->state.store ||
	   sd->npc_id || !pc_ui_can_open(sd, PC_UI_RODEX) || sd->chatID || sd->inventory_expansion_confirmation) {
		clif_res_sendmail_setappend(sd->fd, idx - 2, 1);
		return;
	}
	idx -= 2;
	if(!battle_config.mail_player_attach || amount <= 0) {
		clif_res_sendmail_setappend(sd->fd, idx, 1);
		return;
	}
	if(idx == -2) {
		if(amount > sd->status.zeny)
			amount = sd->status.zeny;
		sd->mail_append.zeny = amount;
	} else {
		if(idx < 0 || idx >= MAX_INVENTORY || sd->status.inventory[idx].nameid <= 0 ||
		   sd->inventory_data[idx] == NULL || pet_is_hatched_egg(&sd->status.inventory[idx]) || sd->status.inventory[idx].amount < amount ||
		   !itemdb_isdropable(sd->status.inventory[idx].nameid)) {
			clif_res_sendmail_setappend(sd->fd, idx, 1);
			return;
		}
		if(battle_config.mail_attachment_weight > 0 &&
		   mail_append_total_weight(sd) + (int64)(sd->inventory_data[idx]->weight / 10) * amount > battle_config.mail_attachment_weight) {
			clif_res_sendmail_setappend(sd->fd, idx, 1);
			return;
		}
#if PACKETVER >= 20150513
		limit = MAIL_MAX_ITEM;
#else
		limit = 1;
#endif
		for(i = 0; i < sd->mail_append.count; i++) {
			if(sd->mail_append.index[i] == idx)
				break;
		}
		if(i == sd->mail_append.count) {
			if(i >= limit || amount > sd->status.inventory[idx].amount) {
				clif_res_sendmail_setappend(sd->fd, idx, 1);
				return;
			}
			sd->mail_append.index[i] = idx;
			sd->mail_append.amount[i] = 0;
			sd->mail_append.count++;
		} else if(amount > sd->status.inventory[idx].amount - sd->mail_append.amount[i]) {
			clif_res_sendmail_setappend(sd->fd, idx, 1);
			return;
		}
		sd->mail_append.amount[i] += amount;
	}
	sd->state.mail_appending = 1;
	clif_res_sendmail_setappend(sd->fd, idx, 0);
}

int mail_removeitem(struct map_session_data *sd, int flag)
{
	int i;
	nullpo_retr(0, sd);
	sd->mail_preflight_token = 0;
	if(!(flag & 2)) {
		for(i = 0; i < sd->mail_append.count; i++) {
#if PACKETVER < 20150513
			clif_additem(sd, sd->mail_append.index[i], sd->mail_append.amount[i], 0);
#endif
			sd->mail_append.index[i] = -1;
			sd->mail_append.amount[i] = 0;
		}
		sd->mail_append.count = 0;
	}
	if(!(flag & 1) && sd->mail_append.zeny > 0) {
		clif_updatestatus(sd, SP_ZENY);
		sd->mail_append.zeny = 0;
	}
	if(sd->mail_append.count == 0 && sd->mail_append.zeny == 0)
		sd->state.mail_appending = 0;
	return 0;
}

int mail_removeitem_index(struct map_session_data *sd, int client_idx, int *out_amount)
{
	int i, j, idx = client_idx - 2;
	nullpo_retr(0, sd);
	if(sd->mail_preflight_token)
		return 0;
	for(i = 0; i < sd->mail_append.count; i++) {
		if(sd->mail_append.index[i] != idx)
			continue;
		if(out_amount == NULL || *out_amount <= 0 || *out_amount > sd->mail_append.amount[i])
			return 0;
#if PACKETVER < 20150513
		clif_additem(sd, idx, *out_amount, 0);
#endif
		sd->mail_append.amount[i] -= *out_amount;
		if(sd->mail_append.amount[i] > 0)
			return 1;
		for(j = i; j + 1 < sd->mail_append.count; j++) {
			sd->mail_append.index[j] = sd->mail_append.index[j+1];
			sd->mail_append.amount[j] = sd->mail_append.amount[j+1];
		}
		sd->mail_append.count--;
		sd->mail_append.index[sd->mail_append.count] = -1;
		sd->mail_append.amount[sd->mail_append.count] = 0;
		if(sd->mail_append.count == 0 && sd->mail_append.zeny == 0)
			sd->state.mail_appending = 0;
		return 1;
	}
	return 0;
}

static int mail_checkappend(struct map_session_data *sd, struct mail_data *md)
{
	int i;
	nullpo_retr(1, sd);
	nullpo_retr(1, md);
	if(!battle_config.mail_player_attach)
		mail_removeitem(sd, 0);
	if(sd->mail_append.zeny < 0 || sd->mail_append.zeny > sd->status.zeny)
		return 1;
	md->zeny = sd->mail_append.zeny;
	memset(md->item, 0, sizeof(md->item));
	for(i = 0; i < sd->mail_append.count; i++) {
		int idx = sd->mail_append.index[i], amount = sd->mail_append.amount[i];
		if(idx < 0 || idx >= MAX_INVENTORY || amount <= 0 ||
		   sd->status.inventory[idx].nameid <= 0 || sd->status.inventory[idx].amount < amount ||
		   sd->inventory_data[idx] == NULL || !itemdb_isdropable(sd->status.inventory[idx].nameid))
			return 1;
		memcpy(&md->item[i], &sd->status.inventory[idx], sizeof(struct item));
		md->item[i].amount = amount;
	}
	if(battle_config.mail_attachment_weight > 0 &&
	   mail_append_total_weight(sd) > battle_config.mail_attachment_weight)
		return 1;
	md->send_fee = mail_calc_fee(md->zeny, sd->mail_append.count);
	if(md->send_fee < 0 || (int64)md->zeny + md->send_fee > sd->status.zeny)
		return 1;
	for(i = 0; i < sd->mail_append.count; i++) {
#if PACKETVER >= 20150513
		pc_delitem(sd, sd->mail_append.index[i], sd->mail_append.amount[i], 0, 0);
#else
		pc_delitem(sd, sd->mail_append.index[i], sd->mail_append.amount[i], 1, 0);
#endif
	}
	sd->status.zeny -= md->zeny + md->send_fee;
	clif_updatestatus(sd, SP_ZENY);
	return 0;
}

/*==========================================
 * 送信前チェック
 *------------------------------------------
 */
/* アカウントごとの送信回数をサーバーのローカル日付で管理する */
static int mail_daily_consume(struct map_session_data *sd)
{
	time_t now = time(NULL);
	struct tm *local = localtime(&now);
	int64 day, packed;
	int previous, count;

	if(!sd->state.accountreg_ready || !chrif_isconnect() || local == NULL)
		return 2;
	day = (int64)local->tm_year * 512 + local->tm_yday;
	packed = day * 128;
	if(day <= 0 || packed > INT_MAX - 100)
		return 2;
	previous = pc_readaccountreg(sd, "#PC_RODEX_DAILY");
	count = (previous > 0 && previous / 128 == day) ? previous % 128 : 0;
	if(count >= 100)
		return 1;
	if(pc_setaccountreg(sd, "#PC_RODEX_DAILY", (int)packed + count + 1) != 0)
		return 2;
	return 0;
}

int mail_checkmail(struct map_session_data *sd, const char *name, const char *title, const char *body, int len)
{
	static unsigned int next_preflight_token;
	struct map_session_data *rd;
	struct mail_data md;

	nullpo_retr(0, sd);

	// 旧メールパケットからも、別の排他画面を利用中の送信を受け付けない。
	if(!pc_ui_can_open(sd, PC_UI_RODEX)) {
		clif_res_sendmail(sd->fd, 1);
		return 0;
	}

	{
		int daily = mail_daily_consume(sd);
		if(daily != 0) {
			if(daily == 1)
				clif_displaymessage(sd->fd, "メールは1日100通まで送信できます。");
			clif_res_sendmail(sd->fd, 1);
			mail_removeitem(sd, 0);
			return 0;
		}
	}

	if(sd->mail_preflight_token || sd->mail_pending_flag) {
		clif_res_sendmail(sd->fd, 1);
		return 0;
	}

	rd = map_nick2sd(name);

	// 本文の長さが不正、または送信相手が自分ならダメ
	if(len <= 0 || len > sizeof(md.body) || rd == sd) {
		clif_res_sendmail(sd->fd,1);
		mail_removeitem(sd,0);
		return 0;
	}

	memset(&md, 0, sizeof(md));

	strncpy(md.char_name, sd->status.name, 24);
	md.char_id = sd->status.char_id;

	strncpy(md.receive_name, name, sizeof(md.receive_name)-1);
	md.receive_name[23] = '\0';	// force \0 terminal
	strncpy(md.title, title, sizeof(md.title));
	md.title[sizeof(md.title)-1] = '\0';

	memcpy(md.body, body, len);
	md.body_size = len;

	if(++next_preflight_token == 0)
		++next_preflight_token;
	md.send_token = next_preflight_token;
	sd->mail_preflight_token = next_preflight_token;
	if(intif_mail_checkmail(sd->status.account_id,&md) < 0) {
		sd->mail_preflight_token = 0;
		// 宛先確認を送れなかった場合は送信を中止する
		clif_res_sendmail(sd->fd,1);
		mail_removeitem(sd,0);
	}

	return 0;
}

/*==========================================
 * 送信→Interへ
 *------------------------------------------
 */
int mail_sendmail(struct map_session_data *sd, struct mail_data *md)
{
	static unsigned int next_token = 0;
	nullpo_retr(0, sd);
	nullpo_retr(0, md);

	if(sd->mail_pending_flag || md->char_id != sd->status.char_id) {
		clif_res_sendmail(sd->fd, 1);
		return 0;
	}

	// 日付の保存
	md->times = (unsigned int)time(NULL);
	// アイテム・Zenyチェック
	if(mail_checkappend(sd,md) == 0) {
		if(++next_token == 0)
			++next_token;
		md->send_token = next_token;
		memcpy(&sd->mail_pending, md, sizeof(struct mail_data));
		sd->mail_pending_flag = 1;
		if(intif_sendmail(md) < 0) {
			mail_refund_pending(sd);
			clif_res_sendmail(sd->fd, 1);
		}
	} else {
		mail_removeitem(sd, 0);
		clif_res_sendmail(sd->fd, 1);
	}

	sd->mail_append.count    = 0;
	sd->mail_append.zeny     = 0;
	sd->state.mail_appending = 0;

	return 0;
}

/*==========================================
 * 添付アイテムやZenyの返送
 *------------------------------------------
 */
void mail_refund_pending(struct map_session_data *sd)
{
	nullpo_retv(sd);
	if(!sd->mail_pending_flag)
		return;

	if(sd->mail_pending.zeny > 0 || sd->mail_pending.send_fee > 0) {
		int refund = sd->mail_pending.zeny + sd->mail_pending.send_fee;
		sd->status.zeny += (refund < MAX_ZENY - sd->status.zeny) ? refund : MAX_ZENY - sd->status.zeny;
		clif_updatestatus(sd, SP_ZENY);
	}
	{
		int i;
		for(i = 0; i < MAIL_MAX_ITEM; i++) {
			if(sd->mail_pending.item[i].nameid > 0 && sd->mail_pending.item[i].amount > 0)
				pc_additem(sd, &sd->mail_pending.item[i], sd->mail_pending.item[i].amount, false);
		}
	}

	memset(&sd->mail_pending, 0, sizeof(sd->mail_pending));
	sd->mail_pending_flag = 0;
}

/*==========================================
 * 添付アイテムやZenyを取得
 *------------------------------------------
 */
void mail_getappend(int account_id, int char_id, int zeny, unsigned int mail_num, enum mail_attachment_type type, struct item *item)
{
	struct map_session_data *sd;
	bool result = true, delivered = false, has_item = false;
	int i, flag = 0;

	nullpo_retv(item);
	sd = map_id2sd(account_id);
	if(sd == NULL || sd->status.char_id != char_id) {
		if(char_id > 0)
			intif_mail_restoreappend(char_id, mail_num, zeny, item);
		return;
	}

	for(i = 0; i < MAIL_MAX_ITEM; i++) {
		if(item[i].nameid > 0 && item[i].amount > 0)
			has_item = true;
	}
	if(zeny > 0 && sd->status.zeny > MAX_ZENY - zeny) {
		result = false;
		flag = 1;
	}
	if(result) {
		for(i = 0; i < MAIL_MAX_ITEM; i++) {
			if(item[i].nameid <= 0 || item[i].amount <= 0)
				continue;
			if(pc_additem(sd, &item[i], item[i].amount, false) != 0) {
				result = false;
				flag = 1;
				continue;
			}
			memset(&item[i], 0, sizeof(item[i]));
			delivered = true;
		}
		if(result && zeny > 0) {
			sd->status.zeny += zeny;
			clif_updatestatus(sd, SP_ZENY);
			zeny = 0;
			delivered = true;
		}
	}
	if(!result)
		intif_mail_restoreappend(char_id, mail_num, zeny, item);
	if(delivered)
		chrif_save(sd, 0);

#if PACKETVER >= 20150513
	if(type != MAIL_ATTACH_ALL) {
		if(!delivered && result) {
			result = false;
			flag = 1;
		}
		clif_rodex_getappend_ack(sd, mail_num, type, result ? 0 : flag);
		if(result)
			intif_mailbox(sd->status.char_id);
		return;
	}
#endif
	if(has_item)
		clif_mail_getappend(sd->fd, result ? 0 : flag);
}

static int mail_send_system_sub(const char *dest_name, const char *sender_name,
	const char *title, const char *body, int body_len,
	int zeny, const struct item *item, int item_count, int reward_char_id, unsigned int reward_id)
{
	struct mail_data md;
	int i;

	if(item_count < 0 || item_count > MAIL_MAX_ITEM || (item_count && !item))
		return -1;
	if(dest_name == NULL || dest_name[0] == '\0')
		return -1;
	if(body_len < 0 || body_len > (int)sizeof(md.body))
		return -1;

	memset(&md, 0, sizeof(md));
	md.char_id = reward_char_id;
	md.send_token = reward_id;
	if(sender_name && sender_name[0])
		strncpy(md.char_name, sender_name, sizeof(md.char_name)-1);
	else
		strncpy(md.char_name, "Server", sizeof(md.char_name)-1);

	strncpy(md.receive_name, dest_name, sizeof(md.receive_name)-1);
	md.receive_name[sizeof(md.receive_name)-1] = '\0';

	if(title)
		strncpy(md.title, title, sizeof(md.title)-1);

	if(body && body_len > 0) {
		memcpy(md.body, body, body_len);
		md.body_size = body_len;
	} else {
		md.body[0] = '\0';
		md.body_size = 0;
	}

	md.zeny = (zeny > 0) ? zeny : 0;
	for(i = 0; i < item_count; i++) {
		if(item[i].nameid <= 0 || item[i].amount <= 0)
			return -1;
		memcpy(&md.item[i], &item[i], sizeof(struct item));
	}

	md.times = (unsigned int)time(NULL);
	md.read = MAIL_READ_SYSTEM;

	return intif_send_sysmail(&md);
}

int mail_send_system(const char *dest_name, const char *sender_name,
	const char *title, const char *body, int body_len,
	int zeny, const struct item *item)
{
	return mail_send_system_sub(dest_name, sender_name, title, body, body_len, zeny, item, (item && item->nameid > 0 && item->amount > 0) ? 1 : 0, 0, 0);
}

int mail_send_achievement(const char *dest_name, const char *sender_name,
	const char *title, const char *body, int body_len,
	const struct item *item, int char_id, unsigned int achievement_id)
{
	return mail_send_system_sub(dest_name, sender_name, title, body, body_len, 0, item, (item && item->nameid > 0 && item->amount > 0) ? 1 : 0, char_id, achievement_id);
}

/* システムメール1通に複数の商品をまとめて添付する。 */
int mail_send_system_items(const char *dest_name, const char *sender_name,
	const char *title, const char *body, int body_len,
	int zeny, const struct item *items, int count)
{
	return mail_send_system_sub(dest_name, sender_name, title, body, body_len, zeny, items, count, 0, 0);
}
