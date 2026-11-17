#include <stdarg.h>
#include <string.h>
#include <time.h>

#include "unity.h"
#include "utils.h"
#include "pc.h"
#include "battle.h"
#include "clif.h"
#include "searchstore.h"

static struct map_session_data customer, seller;
static int ack_count, failure, opened_shop, marker_x, marker_y;
int map_num = 3;

struct map_session_data *map_id2sd(int id)
{
	return id == seller.bl.id ? &seller : NULL;
}

int clif_foreachclient(int (*func)(struct map_session_data *, va_list), ...)
{
	va_list ap;
	va_start(ap, func);
	func(&seller, ap);
	va_end(ap);
	return 0;
}

int clif_open_search_store_info(struct map_session_data *sd) { return 1; }
void clif_search_store_info_ack(struct map_session_data *sd) { ack_count++; }
void clif_search_store_info_failed(struct map_session_data *sd, unsigned char reason) { failure = reason; }
void clif_search_store_info_click_ack(struct map_session_data *sd, short x, short y)
{
	marker_x = x;
	marker_y = y;
}
void vending_vendinglistreq(struct map_session_data *sd, int id) { opened_shop = id; }
void buyingstore_itemlist(struct map_session_data *sd, int id) { opened_shop = id; }

static void setup_search(int effect, short mapid)
{
	searchstore_close(&customer);
	memset(&customer, 0, sizeof(customer));
	memset(&seller, 0, sizeof(seller));
	seller.bl.id = seller.status.account_id = 100;
	seller.bl.prev = &seller.bl;
	seller.bl.x = 10;
	seller.bl.y = 20;
	seller.state.store = STORE_TYPE_VENDING;
	seller.vender_id = 42;
	seller.vend_num = 1;
	seller.vending[0].amount = 2;
	seller.vending[0].value = 100;
	seller.status.cart[0].nameid = 501;
	seller.status.cart[0].amount = 2;
	seller.status.cart[0].refine = 7;
	battle_config.feature_search_stores = 1;
	battle_config.searchstore_maxresults = 30;
	battle_config.searchstore_querydelay = 0;
	ack_count = opened_shop = 0;
	failure = marker_x = marker_y = -1;
	TEST_ASSERT_TRUE(searchstore_open(&customer, 2, (unsigned char)effect, mapid));
}

static void search(unsigned char type)
{
	const int item = 501;
	searchstore_query(&customer, type, 0, 0, &item, 1, NULL, 0);
}

void test_searchstore_filters_and_map_zero(void)
{
	int items[] = {501, 501}, card = 1201;
	setup_search(SEARCHSTORE_EFFECT_NORMAL, 0);
	seller.status.cart[0].card[2] = card;
	searchstore_query(&customer, SEARCHTYPE_VENDING, 110, 90, items, 2, &card, 1);
	TEST_ASSERT_EQUAL_INT(1, customer.searchstore.count);
	TEST_ASSERT_EQUAL_INT(1, customer.searchstore.uses);
	TEST_ASSERT_EQUAL_INT(7, customer.searchstore.items[0].refine);
	TEST_ASSERT_EQUAL_INT(card, customer.searchstore.items[0].card[2]);
	seller.bl.m = 1;
	search(SEARCHTYPE_VENDING);
	TEST_ASSERT_EQUAL_INT(0, customer.searchstore.count);
	TEST_ASSERT_EQUAL_INT(SSI_FAILED_NOTHING_SEARCH_ITEM, failure);
	searchstore_close(&customer);
}

void test_searchstore_paging_and_overflow(void)
{
	int i;
	setup_search(SEARCHSTORE_EFFECT_NORMAL, -1);
	for(i = 0; i < 12; i++) {
		seller.vending[i] = seller.vending[0];
		seller.vending[i].index = i;
		seller.status.cart[i] = seller.status.cart[0];
	}
	seller.vend_num = 12;
	battle_config.searchstore_maxresults = 11;
	search(SEARCHTYPE_VENDING);
	TEST_ASSERT_EQUAL_INT(11, customer.searchstore.count);
	TEST_ASSERT_EQUAL_INT(11, customer.searchstore.capacity);
	TEST_ASSERT_EQUAL_INT(SSI_FAILED_OVER_MAXCOUNT, failure);
	TEST_ASSERT_EQUAL_INT(1, ack_count);
	searchstore_next(&customer);
	TEST_ASSERT_EQUAL_INT(2, ack_count);
	searchstore_next(&customer);
	TEST_ASSERT_EQUAL_INT(2, ack_count);
	TEST_ASSERT_EQUAL_INT(1, customer.searchstore.uses);
	searchstore_close(&customer);
	TEST_ASSERT_NULL(customer.searchstore.items);
	TEST_ASSERT_EQUAL_INT(0, customer.searchstore.capacity);
}

void test_searchstore_remote_identity_and_stale_result(void)
{
	setup_search(SEARCHSTORE_EFFECT_REMOTE, -1);
	search(SEARCHTYPE_VENDING);
	searchstore_click(&customer, seller.bl.id, seller.vender_id, 501);
	TEST_ASSERT_EQUAL_INT(seller.bl.id, opened_shop);
	TEST_ASSERT_TRUE(searchstore_queryremote(&customer, &seller, SEARCHTYPE_VENDING));
	TEST_ASSERT_FALSE(searchstore_queryremote(&customer, &seller, SEARCHTYPE_BUYING_STORE));
	seller.vender_id++;
	TEST_ASSERT_FALSE(searchstore_queryremote(&customer, &seller, SEARCHTYPE_VENDING));
	seller.vender_id--;
	seller.status.cart[0].refine++;
	opened_shop = 0;
	searchstore_click(&customer, seller.bl.id, seller.vender_id, 501);
	TEST_ASSERT_EQUAL_INT(0, opened_shop);
	TEST_ASSERT_EQUAL_INT(SSI_FAILED_SSILIST_CLICK_TO_OPEN_STORE, failure);
	TEST_ASSERT_FALSE(searchstore_queryremote(&customer, &seller, SEARCHTYPE_VENDING));
	searchstore_close(&customer);
}

void test_searchstore_buying_and_coordinate_effect(void)
{
	setup_search(SEARCHSTORE_EFFECT_NORMAL, -1);
	search(SEARCHTYPE_VENDING);
	searchstore_click(&customer, seller.bl.id, seller.vender_id, 501);
	TEST_ASSERT_EQUAL_INT(10, marker_x);
	TEST_ASSERT_EQUAL_INT(20, marker_y);
	TEST_ASSERT_FALSE(searchstore_queryremote(&customer, &seller, SEARCHTYPE_VENDING));
	seller.bl.m = 1;
	searchstore_click(&customer, seller.bl.id, seller.vender_id, 501);
	TEST_ASSERT_EQUAL_INT(-1, marker_x);
	setup_search(SEARCHSTORE_EFFECT_REMOTE, -1);
	seller.state.store = STORE_TYPE_BUYINGSTORE;
	seller.buyer_id = 43;
	seller.buyingstore.count = 1;
	seller.buyingstore.item[0].nameid = 501;
	seller.buyingstore.item[0].amount = 3;
	seller.buyingstore.item[0].value = 100;
	search(SEARCHTYPE_BUYING_STORE);
	searchstore_click(&customer, seller.bl.id, seller.buyer_id, 501);
	TEST_ASSERT_TRUE(searchstore_queryremote(&customer, &seller, SEARCHTYPE_BUYING_STORE));
	searchstore_clearremote(&customer);
	TEST_ASSERT_FALSE(searchstore_queryremote(&customer, &seller, SEARCHTYPE_BUYING_STORE));
	searchstore_close(&customer);
}

void test_searchstore_throttle_uses_and_ui(void)
{
	setup_search(SEARCHSTORE_EFFECT_REMOTE, -1);
	TEST_ASSERT_FALSE(searchstore_open(&customer, 255, SEARCHSTORE_EFFECT_REMOTE, -1));
	customer.state.open_ui = PC_UI_REFINE;
	search(SEARCHTYPE_VENDING);
	TEST_ASSERT_EQUAL_INT(2, customer.searchstore.uses);
	customer.state.open_ui = PC_UI_NONE;
	customer.searchstore.nextquerytime = time(NULL) + 60;
	search(SEARCHTYPE_VENDING);
	TEST_ASSERT_EQUAL_INT(SSI_FAILED_LIMIT_SEARCH_TIME, failure);
	TEST_ASSERT_EQUAL_INT(2, customer.searchstore.uses);
	customer.searchstore.nextquerytime = 0;
	search(SEARCHTYPE_VENDING);
	search(SEARCHTYPE_VENDING);
	search(SEARCHTYPE_VENDING);
	TEST_ASSERT_EQUAL_INT(SSI_FAILED_SEARCH_CNT, failure);
	TEST_ASSERT_EQUAL_INT(0, customer.searchstore.uses);
	searchstore_close(&customer);
}
