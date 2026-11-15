#include <limits.h>
#include <string.h>

#include "unity.h"
#include "utils.h"
#include "battle.h"
#include "cashshop.h"
#include "itemdb.h"
#include "pc.h"
#include "unit.h"

/* 保存とクライアント通知を分離し、購入処理を検証する。 */
struct Battle_Config battle_config;
static struct map_session_data sd;
static struct item_data items[2];
static unsigned char request[20];
static int slots, additions, received, saved_points;

struct item_data *itemdb_exists(int nameid)
{
	if(nameid == 501) return &items[0];
	if(nameid == 1201) return &items[1];
	return NULL;
}

int itemdb_isequip2(struct item_data *data) { return data->nameid == 1201; }
int pc_inventory_slots(struct map_session_data *session) { return slots; }
int unit_isdead(struct block_list *bl) { return 0; }

int pc_additem(struct map_session_data *session, struct item *item, int amount, bool flag)
{
	if(item->nameid == 1201)
		TEST_ASSERT_EQUAL_INT(1, amount);
	additions++;
	received += amount;
	return 0;
}

int pc_setregistry(struct map_session_data *session, const char *reg, int value, int type)
{
	TEST_ASSERT_EQUAL_STRING("PC_SHOP_POINT", reg);
	TEST_ASSERT_EQUAL_INT(3, type);
	saved_points = value;
	return 0;
}

static void setup_purchase(void)
{
	memset(&sd, 0, sizeof(sd));
	memset(items, 0, sizeof(items));
	memset(request, 0, sizeof(request));
	items[0].nameid = 501;
	items[0].weight = 10;
	items[1].nameid = 1201;
	items[1].weight = 20;
	sd.shop_point = 100;
	sd.max_weight = 1000;
	sd.state.open_ui = PC_UI_CASHSHOP;
	battle_config.feature_cashshop = 1;
	slots = 4;
	additions = received = 0;
	saved_points = -1;
	cashshop_clear();
	TEST_ASSERT_TRUE(cashshop_insert(0, 501, 10, 0, 0));
	TEST_ASSERT_TRUE(cashshop_insert(1, 1201, 20, 0, 0));
}

static void row(int index, unsigned int nameid, unsigned int amount, unsigned short tab)
{
	unsigned char *p = request + index * 10;
	memcpy(p, &nameid, sizeof(nameid));
	memcpy(p + 4, &amount, sizeof(amount));
	memcpy(p + 8, &tab, sizeof(tab));
}

void test_cashshop_equipment_quantity(void)
{
	setup_purchase();
	row(0, 1201, 3, 1);
	TEST_ASSERT_EQUAL_INT(CASHSHOP_RESULT_SUCCESS, cashshop_buy(&sd, 0, 1, request));
	TEST_ASSERT_EQUAL_INT(3, additions);
	TEST_ASSERT_EQUAL_INT(3, received);
	TEST_ASSERT_EQUAL_INT(40, sd.shop_point);
	TEST_ASSERT_EQUAL_INT(40, saved_points);
}

void test_cashshop_preflight_no_partial_purchase(void)
{
	setup_purchase();
	row(0, 501, 2, 0);
	row(1, 1201, 5, 1);
	TEST_ASSERT_EQUAL_INT(CASHSHOP_RESULT_ERROR_SHORTTAGE_CASH, cashshop_buy(&sd, 0, 2, request));
	TEST_ASSERT_EQUAL_INT(0, additions);
	TEST_ASSERT_EQUAL_INT(100, sd.shop_point);
	TEST_ASSERT_EQUAL_INT(-1, saved_points);
}

void test_cashshop_cumulative_inventory_limit(void)
{
	setup_purchase();
	sd.status.inventory[0].nameid = 501;
	sd.status.inventory[0].amount = MAX_AMOUNT - 3;
	row(0, 501, 2, 0);
	row(1, 501, 2, 0);
	TEST_ASSERT_EQUAL_INT(CASHSHOP_RESULT_ERROR_INVENTORY_ITEMCNT, cashshop_buy(&sd, 0, 2, request));
	TEST_ASSERT_EQUAL_INT(0, additions);
	slots = 1;
	memset(sd.status.inventory, 0, sizeof(sd.status.inventory));
	row(0, 1201, 2, 1);
	TEST_ASSERT_EQUAL_INT(CASHSHOP_RESULT_ERROR_INVENTORY_ITEMCNT, cashshop_buy(&sd, 0, 1, request));
	TEST_ASSERT_EQUAL_INT(0, additions);
}

void test_cashshop_arithmetic_limits(void)
{
	setup_purchase();
	cashshop_clear();
	TEST_ASSERT_TRUE(cashshop_insert(0, 501, INT_MAX, 0, 0));
	sd.shop_point = INT_MAX;
	row(0, 501, 2, 0);
	TEST_ASSERT_EQUAL_INT(CASHSHOP_RESULT_ERROR_SHORTTAGE_CASH, cashshop_buy(&sd, 0, 1, request));
	cashshop_clear();
	TEST_ASSERT_TRUE(cashshop_insert(0, 501, 0, 0, 0));
	items[0].weight = INT_MAX;
	TEST_ASSERT_EQUAL_INT(CASHSHOP_RESULT_ERROR_INVENTORY_WEIGHT, cashshop_buy(&sd, 0, 1, request));
	TEST_ASSERT_EQUAL_INT(0, additions);
}

void test_cashshop_catalog_validation(void)
{
	setup_purchase();
	TEST_ASSERT_FALSE(cashshop_insert(0, 501, 1, 0, 0));
	TEST_ASSERT_FALSE(cashshop_insert(2, 501, 1, 20260229, 0));
	TEST_ASSERT_FALSE(cashshop_insert(2, 501, 1, 20261131, 0));
	TEST_ASSERT_FALSE(cashshop_insert(2, 501, 1, 20261201, 20261101));
	TEST_ASSERT_TRUE(cashshop_insert(2, 501, 1, 20240229, 0));
	TEST_ASSERT_EQUAL_INT(-1, cashshop_find_price(1, 501));
	row(0, 501, 1, 1);
	TEST_ASSERT_EQUAL_INT(CASHSHOP_RESULT_ERROR_UNKNOWN_ITEM, cashshop_buy(&sd, 0, 1, request));
}

void test_cashshop_state_and_request_validation(void)
{
	setup_purchase();
	row(0, 501, 1, 0);
	TEST_ASSERT_EQUAL_INT(CASHSHOP_RESULT_ERROR_SHORTTAGE_CASH, cashshop_buy(&sd, 1, 1, request));
	sd.state.open_ui = PC_UI_RODEX;
	TEST_ASSERT_EQUAL_INT(CASHSHOP_RESULT_ERROR_PC_STATE, cashshop_buy(&sd, 0, 1, request));
	sd.state.open_ui = PC_UI_CASHSHOP;
	row(0, 501, UINT_MAX, 0);
	TEST_ASSERT_EQUAL_INT(CASHSHOP_RESULT_ERROR_UNKNOWN_ITEM, cashshop_buy(&sd, 0, 1, request));
	TEST_ASSERT_EQUAL_INT(CASHSHOP_RESULT_ERROR_SYSTEM, cashshop_buy(&sd, 0, CASHSHOP_ITEM_MAX + 1, request));
	TEST_ASSERT_EQUAL_INT(0, additions);
}
