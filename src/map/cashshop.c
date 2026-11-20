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
#include <string.h>
#include <limits.h>
#include <time.h>

#include "malloc.h"
#include "utils.h"
#include "nullpo.h"

#include "cashshop.h"
#include "battle.h"
#include "itemdb.h"
#include "pc.h"
#include "intif.h"
#include "chrif.h"
#include "clif.h"
#include "unit.h"

/* 商品数を制限し、一覧パケットと購入要求の処理量を一定範囲に収める。 */
static struct cashshop_item cashshop_db[CASHSHOP_ITEM_MAX];
static int cashshop_num = 0;
static struct cashshop_account_item cashshop_account_db[CASHSHOP_ACCOUNT_MAX];
static int cashshop_account_num;
static unsigned int cashshop_account_generation = 1, cashshop_account_token;


static unsigned int cashshop_today(void)
{
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);

	if(tm == NULL)
		return 0;
	return (unsigned int)((tm->tm_year + 1900) * 10000 + (tm->tm_mon + 1) * 100 + tm->tm_mday);
}

int cashshop_item_count(void)
{
	return cashshop_num;
}

const struct cashshop_item *cashshop_item_at(int index)
{
	if(index < 0 || index >= cashshop_num)
		return NULL;
	return &cashshop_db[index];
}

int cashshop_item_available(const struct cashshop_item *it)
{
	unsigned int today;

	if(it == NULL)
		return 0;
	today = cashshop_today();
	if(it->start_date > 0 && today < it->start_date)
		return 0;
	if(it->end_date > 0 && today > it->end_date)
		return 0;
	return 1;
}

void cashshop_clear(void)
{
	cashshop_num = 0;
	cashshop_account_num = 0;
	memset(cashshop_account_db, 0, sizeof(cashshop_account_db));
	if(++cashshop_account_generation == 0)
		cashshop_account_generation = 1;
	memset(cashshop_db, 0, sizeof(cashshop_db));
}

/* 0は期間指定なし。指定時は実在する日付のみ受け付ける。 */
static int cashshop_valid_date(unsigned int date)
{
	unsigned int year, month, day, days;
	static const unsigned int month_days[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	if(date == 0)
		return 1;
	year = date / 10000;
	month = date / 100 % 100;
	day = date % 100;
	if(year < 1900 || year > 9999 || month < 1 || month > 12)
		return 0;
	days = month_days[month - 1];
	if(month == 2 && year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
		days++;
	return day >= 1 && day <= days;
}

int cashshop_insert(int tab, int nameid, int price, unsigned int start_date, unsigned int end_date)
{
	struct cashshop_item *item;
	int i;

	if(tab < 0 || tab >= CASHSHOP_TAB_ACCOUNT || nameid <= 0 || price < 0)
		return 0;
	if(!cashshop_valid_date(start_date) || !cashshop_valid_date(end_date) ||
	   (start_date > 0 && end_date > 0 && start_date > end_date))
		return 0;
	if(itemdb_exists(nameid) == NULL) {
		printf("cashshop_insert: unknown item %d\n", nameid);
		return 0;
	}
	if(cashshop_num >= CASHSHOP_ITEM_MAX) {
		printf("cashshop_insert: list full\n");
		return 0;
	}

	for(i = 0; i < cashshop_num; i++) {
		if(cashshop_db[i].tab == tab && cashshop_db[i].nameid == nameid) {
			printf("cashshop_insert: duplicate tab %d item %d\n", tab, nameid);
			return 0;
		}
	}
	item = &cashshop_db[cashshop_num++];
	item->tab = (short)tab;
	item->nameid = nameid;
	item->price = price;
	item->start_date = start_date;
	item->end_date = end_date;
	return 1;
}

int cashshop_find_price(int tab, int nameid)
{
	int i;

	for(i = 0; i < cashshop_num; i++) {
		if(cashshop_db[i].tab == tab && cashshop_db[i].nameid == nameid &&
		   cashshop_item_available(&cashshop_db[i]))
			return cashshop_db[i].price;
	}
	return -1;
}

/*==========================================
 * アカウント限定商品と購入履歴
 *------------------------------------------
 */
int cashshop_account_insert(int sale_id, int nameid, int price, unsigned int limit,
	unsigned int start_time, unsigned int end_time)
{
	int i;
	struct cashshop_account_item *it;

	if(sale_id <= 0 || !itemdb_exists(nameid) || price < 0 || limit == 0 || limit > INT_MAX ||
	   start_time == 0 || end_time <= start_time || cashshop_account_num >= CASHSHOP_ACCOUNT_MAX)
		return 0;
	for(i = 0; i < cashshop_account_num; i++) {
		if(cashshop_account_db[i].sale_id == sale_id || cashshop_account_db[i].nameid == nameid)
			return 0;
	}
	it = &cashshop_account_db[cashshop_account_num++];
	it->sale_id = sale_id;
	it->nameid = nameid;
	it->price = price;
	it->limit = limit;
	it->start_time = start_time;
	it->end_time = end_time;
	return 1;
}

int cashshop_account_item_count(void) { return cashshop_account_num; }

const struct cashshop_account_item *cashshop_account_item_at(int index)
{
	return index >= 0 && index < cashshop_account_num ? &cashshop_account_db[index] : NULL;
}

int cashshop_account_available(const struct cashshop_account_item *it)
{
	time_t now = time(NULL);
	return it && now >= 0 && (uint64)now >= it->start_time && (uint64)now < it->end_time;
}

static int cashshop_account_history_index(const struct map_session_data *sd, int sale_id)
{
	int i;
	if(!sd || !sd->cashshop_account_loaded ||
	   sd->cashshop_account_generation != cashshop_account_generation)
		return -1;
	for(i = 0; i < sd->cashshop_account_count; i++) {
		if(sd->cashshop_account_history[i].sale_id == sale_id)
			return i;
	}
	return -1;
}

int cashshop_account_remaining(const struct map_session_data *sd, int sale_id)
{
	int i, index = cashshop_account_history_index(sd, sale_id);
	if(index < 0)
		return -1;
	for(i = 0; i < cashshop_account_num; i++) {
		if(cashshop_account_db[i].sale_id == sale_id) {
			unsigned int limit = cashshop_account_db[i].limit;
			unsigned int used = sd->cashshop_account_history[index].purchased;
			return used >= limit ? 0 : (int)(limit - used);
		}
	}
	return -1;
}

void cashshop_account_close(struct map_session_data *sd)
{
	if(!sd)
		return;
	aFree(sd->cashshop_account_history);
	sd->cashshop_account_history = NULL;
	sd->cashshop_account_count = 0;
	sd->cashshop_account_token = sd->cashshop_account_generation = 0;
	sd->cashshop_account_loaded = 0;
}

void cashshop_account_request(struct map_session_data *sd)
{
	int i, available = 0;

	nullpo_retv(sd);
	if(!pc_ui_is(sd, PC_UI_CASHSHOP))
		return;
	for(i = 0; i < cashshop_account_num; i++) {
		if(cashshop_account_available(&cashshop_account_db[i]))
			available = 1;
	}
	if(!battle_config.feature_cashshop || !available || !chrif_isconnect()) {
		cashshop_account_close(sd);
		clif_cashshop_account_list(sd);
		return;
	}
	/* 連打による履歴ロードを抑え、応答消失時は再要求できるようにする。 */
	if(sd->cashshop_account_token && !sd->cashshop_account_loaded &&
	   time(NULL) - sd->cashshop_account_query_time < 5)
		return;
	if(sd->cashshop_account_loaded && sd->cashshop_account_generation == cashshop_account_generation) {
		clif_cashshop_account_list(sd);
		return;
	}

	cashshop_account_close(sd);
	sd->cashshop_account_count = cashshop_account_num;
	sd->cashshop_account_history = (struct cashshop_account_count *)aCalloc(
		cashshop_account_num, sizeof(*sd->cashshop_account_history));
	for(i = 0; i < cashshop_account_num; i++)
		sd->cashshop_account_history[i].sale_id = cashshop_account_db[i].sale_id;
	if(++cashshop_account_token == 0)
		cashshop_account_token = 1;
	sd->cashshop_account_token = cashshop_account_token;
	sd->cashshop_account_generation = cashshop_account_generation;
	sd->cashshop_account_query_time = time(NULL);
	if(!intif_cashshop_account_request(sd)) {
		cashshop_account_close(sd);
		clif_cashshop_account_list(sd);
	}
}

void cashshop_account_receive(struct map_session_data *sd, unsigned int token, int ok,
	const struct cashshop_account_count *history, int count)
{
	int i;
	if(!sd || !pc_ui_is(sd, PC_UI_CASHSHOP) || sd->cashshop_account_loaded ||
	   !token || token != sd->cashshop_account_token ||
	   sd->cashshop_account_generation != cashshop_account_generation)
		return;
	if(!ok || !history || count != sd->cashshop_account_count)
		goto failed;
	for(i = 0; i < count; i++) {
		if(history[i].sale_id != sd->cashshop_account_history[i].sale_id || history[i].purchased > INT_MAX)
			goto failed;
	}
	memcpy(sd->cashshop_account_history, history, count * sizeof(*history));
	sd->cashshop_account_loaded = 1;
	clif_cashshop_account_list(sd);
	return;
failed:
	cashshop_account_close(sd);
	clif_cashshop_account_list(sd);
}

/* pc_additemと同じ規則で仮の所持欄に全商品を追加する。 */
static int cashshop_checkadd(struct item *inventory, int slots, struct item_data *data, int amount)
{
	int i, j, count = itemdb_isequip2(data) ? amount : 1;

	for(j = 0; j < count; j++) {
		if(!itemdb_isequip2(data)) {
			for(i = 0; i < slots; i++) {
				struct item *it = &inventory[i];
				if(it->nameid == data->nameid && it->limit == 0 &&
				   it->card[0] == 0 && it->card[1] == 0 && it->card[2] == 0 && it->card[3] == 0) {
					if(amount > MAX_AMOUNT - it->amount)
						return 2;
					it->amount += amount;
					break;
				}
			}
			if(i < slots)
				continue;
		}
		for(i = 0; i < slots && inventory[i].nameid; i++);
		if(i == slots)
			return 2;
		memset(&inventory[i], 0, sizeof(inventory[i]));
		inventory[i].nameid = data->nameid;
		inventory[i].amount = itemdb_isequip2(data) ? 1 : amount;
	}
	return 0;
}

int cashshop_buy(struct map_session_data *sd, unsigned int kafra_points, int count, const unsigned char *item_list)
{
	struct item *inventory;
	struct item_data *data[CASHSHOP_ITEM_MAX];
	int amount[CASHSHOP_ITEM_MAX], prices[CASHSHOP_ITEM_MAX];
	int history_index[CASHSHOP_ITEM_MAX], limited_changed = 0;
	atn_bignumber total = 0, weight;
	int i, j, slots, result = CASHSHOP_RESULT_SUCCESS;

	nullpo_retr(CASHSHOP_RESULT_ERROR_SYSTEM, sd);
	if(!battle_config.feature_cashshop || !item_list || count <= 0 || count > CASHSHOP_ITEM_MAX)
		return CASHSHOP_RESULT_ERROR_SYSTEM;
	// 既存のPC_SHOP_POINTのみを通貨とし、未対応の通貨指定は受け付けない。
	if(kafra_points != 0)
		return CASHSHOP_RESULT_ERROR_SHORTTAGE_CASH;
	if(!pc_ui_is(sd, PC_UI_CASHSHOP) || sd->npc_id || sd->npc_shopid ||
	   sd->state.deal_mode || sd->state.store || sd->state.storage_flag || sd->chatID ||
	   sd->state.mail_appending || sd->status.manner < 0 || unit_isdead(&sd->bl))
		return CASHSHOP_RESULT_ERROR_PC_STATE;

	slots = pc_inventory_slots(sd);
	inventory = (struct item *)aMalloc(sizeof(*inventory) * slots);
	memcpy(inventory, sd->status.inventory, sizeof(*inventory) * slots);
	weight = sd->weight;
	for(i = 0; i < count; i++) {
		const unsigned char *p = item_list + i * 10;
		unsigned int nameid, number;
		unsigned short tab;

		memcpy(&nameid, p, sizeof(nameid));
		memcpy(&number, p + 4, sizeof(number));
		memcpy(&tab, p + 8, sizeof(tab));

		history_index[i] = -1;
		prices[i] = -1;
		if(tab == CASHSHOP_TAB_ACCOUNT && nameid > 0 && nameid <= INT_MAX && chrif_isconnect()) {
			for(j = 0; j < cashshop_account_num; j++) {
				const struct cashshop_account_item *it = &cashshop_account_db[j];
				if(it->nameid == (int)nameid && cashshop_account_available(it)) {
					int k, remain = cashshop_account_remaining(sd, it->sale_id);
					/* 同一明細内の重複指定も合算して上限を確認する。 */
					for(k = 0; k < i; k++) {
						if(history_index[k] >= 0 && sd->cashshop_account_history[history_index[k]].sale_id == it->sale_id)
							remain -= amount[k];
					}
					if(remain < 0 || number > (unsigned int)remain)
						break;
					history_index[i] = cashshop_account_history_index(sd, it->sale_id);
					prices[i] = it->price;
					break;
				}
			}
		} else if(tab < CASHSHOP_TAB_ACCOUNT) {
			prices[i] = cashshop_find_price(tab, (int)nameid);
		}
		if(nameid == 0 || nameid > INT_MAX || number == 0 || number > MAX_AMOUNT ||
		   (data[i] = itemdb_exists((int)nameid)) == NULL || data[i]->weight < 0 || prices[i] < 0) {
			result = CASHSHOP_RESULT_ERROR_UNKNOWN_ITEM;
			break;
		}
		amount[i] = (int)number;
		total += (atn_bignumber)prices[i] * amount[i];
		weight += (atn_bignumber)data[i]->weight * amount[i];
		if(total > sd->shop_point) {
			result = CASHSHOP_RESULT_ERROR_SHORTTAGE_CASH;
			break;
		}
		if(weight > sd->max_weight) {
			result = CASHSHOP_RESULT_ERROR_INVENTORY_WEIGHT;
			break;
		}
		if(cashshop_checkadd(inventory, slots, data[i], amount[i])) {
			result = CASHSHOP_RESULT_ERROR_INVENTORY_ITEMCNT;
			break;
		}
	}
	aFree(inventory);
	if(result != CASHSHOP_RESULT_SUCCESS)
		return result;

	// 検証後はスクリプト等を実行せず、確定した個数と価格で付与する。
	for(i = 0; i < count; i++) {
		struct item it;
		int equip = itemdb_isequip2(data[i]);
		int number = equip ? 1 : amount[i];

		memset(&it, 0, sizeof(it));
		it.nameid = data[i]->nameid;
		it.identify = 1;
		for(j = 0; j < (equip ? amount[i] : 1); j++) {
			if(pc_additem(sd, &it, number, false)) {
				// 検証済みのため通常到達しない。未付与分は課金しない。
				printf("cashshop_buy: unexpected add failure, char %d item %d\n", sd->status.char_id, it.nameid);
				if(limited_changed)
					intif_cashshop_account_save(sd);
				return CASHSHOP_RESULT_ERROR_SYSTEM;
			}
			if(history_index[i] >= 0) {
				sd->cashshop_account_history[history_index[i]].purchased += number;
				limited_changed = 1;
			}
			sd->shop_point -= BIGNUM2INT((atn_bignumber)prices[i] * number);
			pc_setglobalreg(sd, "PC_SHOP_POINT", sd->shop_point);
		}
	}
	if(limited_changed) {
		intif_cashshop_account_save(sd);
		clif_cashshop_account_list(sd);
	}
	return CASHSHOP_RESULT_SUCCESS;
}

int do_init_cashshop(void)
{
	cashshop_clear();
	/* 商品は後続のLua読み込みで登録する。 */
	return 0;
}

void do_final_cashshop(void)
{
	cashshop_clear();
}
