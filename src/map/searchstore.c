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
#include <string.h>
#include <time.h>

#include "malloc.h"
#include "nullpo.h"
#include "utils.h"

#include "map.h"
#include "battle.h"
#include "clif.h"
#include "itemdb.h"
#include "pc.h"
#include "unit.h"
#include "vending.h"
#include "buyingstore.h"
#include "searchstore.h"

static int searchstore_hasstore(struct map_session_data *sd, unsigned char type)
{
	if(type == SEARCHTYPE_VENDING)
		return (sd->state.store == STORE_TYPE_VENDING);
	if(type == SEARCHTYPE_BUYING_STORE)
		return (sd->state.store == STORE_TYPE_BUYINGSTORE);
	return 0;
}

static unsigned int searchstore_getstoreid(struct map_session_data *sd, unsigned char type)
{
	if(type == SEARCHTYPE_VENDING)
		return sd->vender_id;
	if(type == SEARCHTYPE_BUYING_STORE)
		return sd->buyer_id;
	return 0;
}

static int searchstore_match_cards(const struct item *it, const int *cardlist, int card_count)
{
	int c, cidx;

	if(card_count <= 0)
		return 1;
	if(itemdb_isspecial(it->card[0]))
		return 0;

	for(c = 0; c < 4; c++) {
		for(cidx = 0; cidx < card_count; cidx++) {
			if(cardlist[cidx] == it->card[c])
				return 1;
		}
	}
	return 0;
}

static int searchstore_append(struct map_session_data *sd, struct map_session_data *pl_sd,
	unsigned int store_id, int nameid, unsigned short amount, unsigned int price,
	const struct item *it)
{
	struct s_search_store_info_item *dst;
	int max = battle_config.searchstore_maxresults;
	int capacity;

	if(max < 1)
		max = 1;
	if(max > INT_MAX / (int)sizeof(*dst))
		max = INT_MAX / (int)sizeof(*dst);
	if(sd->searchstore.count >= max)
		return 0;

	/* ページ単位で確保し、検索結果の上限を超えて拡張しない。 */
	if(sd->searchstore.count == sd->searchstore.capacity) {
		capacity = sd->searchstore.capacity + SEARCHSTORE_RESULTS_PER_PAGE;
		if(capacity > max)
			capacity = max;
		sd->searchstore.items = (struct s_search_store_info_item *)aRealloc(
			sd->searchstore.items, sizeof(*dst) * capacity);
		sd->searchstore.capacity = capacity;
	}
	dst = &sd->searchstore.items[sd->searchstore.count];
	memset(dst, 0, sizeof(*dst));
	dst->store_id = store_id;
	dst->account_id = pl_sd->status.account_id;
	strncpy(dst->store_name, pl_sd->message, SEARCHSTORE_SHOPNAME_SIZE - 1);
	dst->nameid = nameid;
	dst->amount = amount;
	dst->price = price;
	if(it) {
		int j;
		dst->refine = (unsigned char)it->refine;
		for(j = 0; j < 4; j++)
			dst->card[j] = it->card[j];
		for(j = 0; j < 5; j++) {
			dst->opt[j].id  = it->opt[j].id;
			dst->opt[j].val = it->opt[j].val;
		}
	}
	sd->searchstore.count++;
	return 1;
}

/* 検索後に精錬・カード・オプションが変わった商品は別の商品として扱う。 */
static int searchstore_same_item(const struct item *it, const struct s_search_store_info_item *row)
{
	int j;

	nullpo_retr(0, it);
	nullpo_retr(0, row);

	if((unsigned char)it->refine != row->refine)
		return 0;
	for(j = 0; j < 4; j++) {
		if(it->card[j] != row->card[j])
			return 0;
	}
	for(j = 0; j < 5; j++) {
		if(it->opt[j].id != row->opt[j].id || it->opt[j].val != row->opt[j].val)
			return 0;
	}
	return 1;
}

static int searchstore_vending_live(struct map_session_data *pl_sd, const struct s_search_store_info_item *row)
{
	int i;

	nullpo_retr(0, pl_sd);
	nullpo_retr(0, row);

	if(pl_sd->state.store != STORE_TYPE_VENDING)
		return 0;

	for(i = 0; i < pl_sd->vend_num; i++) {
		short cidx = pl_sd->vending[i].index;
		struct item *it;

		if(cidx < 0 || cidx >= MAX_CART)
			continue;
		if(pl_sd->vending[i].amount <= 0)
			continue;
		if((unsigned int)pl_sd->vending[i].value != row->price)
			continue;
		it = &pl_sd->status.cart[cidx];
		if(it->nameid != row->nameid || it->amount <= 0)
			continue;
		if(!searchstore_same_item(it, row))
			continue;
		return 1;
	}
	return 0;
}

static int searchstore_buying_live(struct map_session_data *pl_sd, const struct s_search_store_info_item *row)
{
	int i;

	nullpo_retr(0, pl_sd);
	nullpo_retr(0, row);

	if(pl_sd->state.store != STORE_TYPE_BUYINGSTORE)
		return 0;

	for(i = 0; i < pl_sd->buyingstore.count; i++) {
		if(pl_sd->buyingstore.item[i].nameid != row->nameid)
			continue;
		if(pl_sd->buyingstore.item[i].amount <= 0)
			continue;
		if((unsigned int)pl_sd->buyingstore.item[i].value != row->price)
			continue;
		return 1;
	}
	return 0;
}

static int searchstore_match_id(int nameid, const int *ids, int count)
{
	int i;
	for(i = 0; i < count; i++) {
		if(ids[i] == nameid)
			return 1;
	}
	return 0;
}

/* 商品行を一度ずつ調べ、同じ検索IDが複数指定されても結果を重複させない。 */
static int searchstore_vending_searchall(struct map_session_data *pl_sd, struct map_session_data *sd,
	unsigned int min_price, unsigned int max_price, const int *itemlist, int item_count,
	const int *cardlist, int card_count)
{
	int i;

	if(pl_sd->state.store != STORE_TYPE_VENDING)
		return 1;

	for(i = 0; i < pl_sd->vend_num; i++) {
		short cidx = pl_sd->vending[i].index;
		struct item *it;
		unsigned int price;

		if(cidx < 0 || cidx >= MAX_CART || pl_sd->vending[i].amount <= 0)
			continue;
		it = &pl_sd->status.cart[cidx];
		if(it->amount <= 0 || !searchstore_match_id(it->nameid, itemlist, item_count))
			continue;
		price = (unsigned int)pl_sd->vending[i].value;
		if((min_price && price < min_price) || (max_price && price > max_price))
			continue;
		if(!searchstore_match_cards(it, cardlist, card_count))
			continue;
		if(!searchstore_append(sd, pl_sd, pl_sd->vender_id, it->nameid,
			(unsigned short)pl_sd->vending[i].amount, price, it))
			return 0;
	}
	return 1;
}

static int searchstore_buying_searchall(struct map_session_data *pl_sd, struct map_session_data *sd,
	unsigned int min_price, unsigned int max_price, const int *itemlist, int item_count,
	const int *cardlist, int card_count)
{
	int i;

	/* 買取露店はカード付きの品物を買い取れない。 */
	if(pl_sd->state.store != STORE_TYPE_BUYINGSTORE || card_count > 0)
		return 1;

	for(i = 0; i < pl_sd->buyingstore.count; i++) {
		unsigned int price = (unsigned int)pl_sd->buyingstore.item[i].value;
		int nameid = pl_sd->buyingstore.item[i].nameid;

		if(pl_sd->buyingstore.item[i].amount <= 0 || !searchstore_match_id(nameid, itemlist, item_count))
			continue;
		if((min_price && price < min_price) || (max_price && price > max_price))
			continue;
		if(!searchstore_append(sd, pl_sd, pl_sd->buyer_id, nameid,
			(unsigned short)pl_sd->buyingstore.item[i].amount, price, NULL))
			return 0;
	}
	return 1;
}

/* 露店検索は取引画面を併用するため、排他UIとは別に開閉状態を持つ。 */
static int searchstore_can_use(struct map_session_data *sd)
{
	return battle_config.feature_search_stores && !unit_isdead(&sd->bl) &&
	       !pc_ui_blocks(sd, PC_UI_BLOCK_OTHER_UI) && !sd->state.store &&
	       !sd->state.deal_mode && !sd->state.storage_flag;
}

int searchstore_open(struct map_session_data *sd, unsigned short uses, unsigned char effect, short mapid)
{
	nullpo_retr(0, sd);
	if(!searchstore_can_use(sd) || sd->searchstore.open || uses < 1 || uses > 255 ||
	   effect > SEARCHSTORE_EFFECT_REMOTE || mapid < -1 || mapid >= map_num)
		return 0;

	sd->searchstore.open = 1;
	sd->searchstore.uses = uses;
	sd->searchstore.effect = effect;
	sd->searchstore.mapid = mapid;
	sd->searchstore.nextquerytime = 0;
	if(!clif_open_search_store_info(sd)) {
		searchstore_close(sd);
		return 0;
	}
	return 1;
}

void searchstore_clear(struct map_session_data *sd)
{
	nullpo_retv(sd);

	searchstore_clearremote(sd);
	if(sd->searchstore.items) {
		aFree(sd->searchstore.items);
		sd->searchstore.items = NULL;
	}
	sd->searchstore.count = 0;
	sd->searchstore.capacity = 0;
	sd->searchstore.pages = 0;
}

void searchstore_clearremote(struct map_session_data *sd)
{
	nullpo_retv(sd);
	sd->searchstore.remote_id = 0;
	sd->searchstore.remote_store_id = 0;
}

void searchstore_close(struct map_session_data *sd)
{
	nullpo_retv(sd);

	searchstore_clear(sd);
	sd->searchstore.uses = 0;
	sd->searchstore.open = 0;
}

int searchstore_querynext(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	if(sd->searchstore.count <= 0)
		return 0;
	if((sd->searchstore.count - 1) / SEARCHSTORE_RESULTS_PER_PAGE > sd->searchstore.pages)
		return 1;
	return 0;
}

void searchstore_next(struct map_session_data *sd)
{
	nullpo_retv(sd);

	if(!searchstore_can_use(sd) || !sd->searchstore.open)
		return;
	if(sd->searchstore.count <= sd->searchstore.pages * SEARCHSTORE_RESULTS_PER_PAGE)
		return;

	clif_search_store_info_ack(sd);
	sd->searchstore.pages++;
}

struct searchstore_request {
	struct map_session_data *sd;
	unsigned int min_price, max_price;
	const int *itemlist, *cardlist;
	int item_count, card_count;
	int overflow;
};

static int searchstore_query_sub(struct map_session_data *pl_sd, va_list ap)
{
	struct searchstore_request *q = va_arg(ap, struct searchstore_request *);
	struct map_session_data *sd = q->sd;
	int ok;

	if(q->overflow || pl_sd == sd || !pl_sd->bl.prev ||
	   (sd->searchstore.mapid >= 0 && pl_sd->bl.m != sd->searchstore.mapid))
		return 0;
	if(sd->searchstore.type == SEARCHTYPE_VENDING)
		ok = searchstore_vending_searchall(pl_sd, sd, q->min_price, q->max_price,
			q->itemlist, q->item_count, q->cardlist, q->card_count);
	else
		ok = searchstore_buying_searchall(pl_sd, sd, q->min_price, q->max_price,
			q->itemlist, q->item_count, q->cardlist, q->card_count);
	if(!ok)
		q->overflow = 1;
	return 0;
}

/*==========================================
 * 検索条件の検証と結果の作成
 *------------------------------------------
 */
void searchstore_query(struct map_session_data *sd, unsigned char type, unsigned int min_price, unsigned int max_price,
	const int *itemlist, int item_count, const int *cardlist, int card_count)
{
	int i;
	time_t now;
	struct searchstore_request q;

	nullpo_retv(sd);

	if(!battle_config.feature_search_stores)
		return;
	if(!searchstore_can_use(sd) || !sd->searchstore.open)
		return;
	if(type != SEARCHTYPE_VENDING && type != SEARCHTYPE_BUYING_STORE)
		return;
	if(!itemlist || item_count <= 0 || item_count > 255 || card_count < 0 ||
	   card_count > 255 || (card_count > 0 && !cardlist)) {
		clif_search_store_info_failed(sd, SSI_FAILED_NOTHING_SEARCH_ITEM);
		return;
	}

	now = time(NULL);
	if(sd->searchstore.nextquerytime > now) {
		clif_search_store_info_failed(sd, SSI_FAILED_LIMIT_SEARCH_TIME);
		return;
	}
	if(sd->searchstore.uses == 0) {
		clif_search_store_info_failed(sd, SSI_FAILED_SEARCH_CNT);
		return;
	}

	sd->searchstore.uses--;
	sd->searchstore.type = type;
	sd->searchstore.nextquerytime = now + ((battle_config.searchstore_querydelay > 0) ? battle_config.searchstore_querydelay : 0);
	searchstore_clear(sd);

	for(i = 0; i < item_count; i++) {
		if(itemdb_exists(itemlist[i]) == NULL) {
			clif_search_store_info_failed(sd, SSI_FAILED_NOTHING_SEARCH_ITEM);
			clif_search_store_info_ack(sd);
			return;
		}
	}
	for(i = 0; i < card_count; i++) {
		if(itemdb_exists(cardlist[i]) == NULL) {
			clif_search_store_info_failed(sd, SSI_FAILED_NOTHING_SEARCH_ITEM);
			clif_search_store_info_ack(sd);
			return;
		}
	}

	if(max_price && min_price && max_price < min_price) {
		unsigned int tmp = min_price;
		min_price = max_price;
		max_price = tmp;
	}

	memset(&q, 0, sizeof(q));
	q.sd = sd;
	q.min_price = min_price;
	q.max_price = max_price;
	q.itemlist = itemlist;
	q.cardlist = cardlist;
	q.item_count = item_count;
	q.card_count = card_count;
	clif_foreachclient(searchstore_query_sub, &q);
	if(q.overflow)
		clif_search_store_info_failed(sd, SSI_FAILED_OVER_MAXCOUNT);

	if(sd->searchstore.count > 0) {
		clif_search_store_info_ack(sd);
		sd->searchstore.pages++;
	} else {
		searchstore_clear(sd);
		clif_search_store_info_failed(sd, SSI_FAILED_NOTHING_SEARCH_ITEM);
		clif_search_store_info_ack(sd);
	}
}

/*==========================================
 * 選択時に露店と商品を再検証し、座標表示または遠隔取引へ進む
 *------------------------------------------
 */
void searchstore_click(struct map_session_data *sd, int account_id, unsigned int store_id, int nameid)
{
	int i;
	struct map_session_data *pl_sd;

	nullpo_retv(sd);

	if(!battle_config.feature_search_stores)
		return;
	if(!searchstore_can_use(sd) || !sd->searchstore.open || sd->searchstore.count <= 0)
		return;

	searchstore_clearremote(sd);

	pl_sd = map_id2sd(account_id);
	if(pl_sd == NULL || !pl_sd->bl.prev) {
		clif_search_store_info_failed(sd, SSI_FAILED_SSILIST_CLICK_TO_OPEN_STORE);
		return;
	}
	if(!searchstore_hasstore(pl_sd, sd->searchstore.type) ||
	   searchstore_getstoreid(pl_sd, sd->searchstore.type) != store_id) {
		clif_search_store_info_failed(sd, SSI_FAILED_SSILIST_CLICK_TO_OPEN_STORE);
		return;
	}

	/* 同 nameid が複数ある場合は、現時点でも有効な行を優先 */
	for(i = 0; i < sd->searchstore.count; i++) {
		const struct s_search_store_info_item *row = &sd->searchstore.items[i];
		int live;

		if(row->store_id != store_id || row->account_id != account_id || row->nameid != nameid)
			continue;
		if(sd->searchstore.type == SEARCHTYPE_VENDING)
			live = searchstore_vending_live(pl_sd, row);
		else
			live = searchstore_buying_live(pl_sd, row);
		if(live)
			break;
	}
	if(i >= sd->searchstore.count) {
		clif_search_store_info_failed(sd, SSI_FAILED_SSILIST_CLICK_TO_OPEN_STORE);
		return;
	}

	switch(sd->searchstore.effect) {
	case SEARCHSTORE_EFFECT_NORMAL:
		if(sd->bl.m != pl_sd->bl.m)
			clif_search_store_info_click_ack(sd, -1, -1);
		else
			clif_search_store_info_click_ack(sd, pl_sd->bl.x, pl_sd->bl.y);
		break;
	case SEARCHSTORE_EFFECT_REMOTE:
		sd->searchstore.remote_id = account_id;
		sd->searchstore.remote_store_id = store_id;
		if(sd->searchstore.type == SEARCHTYPE_VENDING)
			vending_vendinglistreq(sd, account_id);
		else
			buyingstore_itemlist(sd, account_id);
		break;
	default:
		break;
	}
}

/* アカウントだけでなく露店の開き直しと種別も区別する。 */
int searchstore_queryremote(struct map_session_data *sd, struct map_session_data *pl_sd, unsigned char type)
{
	return sd && pl_sd && searchstore_can_use(sd) && sd->searchstore.open &&
	       sd->searchstore.effect == SEARCHSTORE_EFFECT_REMOTE &&
	       sd->searchstore.type == type && sd->searchstore.remote_id == pl_sd->bl.id &&
	       sd->searchstore.remote_store_id != 0 && searchstore_hasstore(pl_sd, type) &&
	       sd->searchstore.remote_store_id == searchstore_getstoreid(pl_sd, type);
}
