#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "unity.h"
#include "utils.h"
#include "battle.h"
#include "cashshop.h"
#include "pc.h"
#include "../src/char/txt/cashshopdb_txt.h"

extern struct Battle_Config battle_config;
static struct map_session_data customer;
static int connected = 1, requests, saves, lists;

int chrif_isconnect(void) { return connected; }
int intif_cashshop_account_request(struct map_session_data *sd) { requests++; return connected; }
int intif_cashshop_account_save(struct map_session_data *sd) { saves++; return connected; }
void clif_cashshop_account_list(struct map_session_data *sd) { lists++; }

static void setup_account(void)
{
	cashshop_account_close(&customer);
	memset(&customer, 0, sizeof(customer));
	cashshop_clear();
	customer.state.open_ui = PC_UI_CASHSHOP;
	customer.shop_point = 1000;
	customer.max_weight = 1000;
	battle_config.feature_cashshop = 1;
	connected = 1;
	requests = saves = lists = 0;
	TEST_ASSERT_TRUE(cashshop_account_insert(1, 501, 100, 3,
		(unsigned int)time(NULL) - 10, (unsigned int)time(NULL) + 600));
}

static void load_count(unsigned int used)
{
	struct cashshop_account_count history = {1, 0};
	history.purchased = used;
	cashshop_account_request(&customer);
	TEST_ASSERT_EQUAL_INT(1, requests);
	cashshop_account_receive(&customer, customer.cashshop_account_token, 1, &history, 1);
	TEST_ASSERT_TRUE(customer.cashshop_account_loaded);
}

static void request_row(unsigned char *p, unsigned int item, unsigned int amount, unsigned short tab)
{
	memcpy(p, &item, 4);
	memcpy(p + 4, &amount, 4);
	memcpy(p + 8, &tab, 2);
}

void test_account_cashshop_catalog(void)
{
	unsigned int now = (unsigned int)time(NULL);
	setup_account();
	TEST_ASSERT_FALSE(cashshop_insert(8, 1201, 1, 0, 0));
	TEST_ASSERT_TRUE(cashshop_insert(0, 501, 100, 0, 0));
	TEST_ASSERT_FALSE(cashshop_account_insert(2, 501, 1, 2, now, now + 10));
	TEST_ASSERT_FALSE(cashshop_account_insert(1, 1201, 1, 2, now, now + 10));
	TEST_ASSERT_FALSE(cashshop_account_insert(2, 1201, 1, 0, now, now + 10));
	TEST_ASSERT_FALSE(cashshop_account_insert(2, 1201, 1, UINT_MAX, now, now + 10));
	TEST_ASSERT_FALSE(cashshop_account_insert(2, 1201, 1, 1, now, now));
	TEST_ASSERT_EQUAL_INT(-1, cashshop_account_remaining(&customer, 1));
	cashshop_account_close(&customer);
}

void test_account_cashshop_limit_and_duplicate_rows(void)
{
	unsigned char data[20];
	setup_account();
	load_count(0);
	request_row(data, 501, 2, 8);
	request_row(data + 10, 501, 2, 8);
	TEST_ASSERT_EQUAL_INT(CASHSHOP_RESULT_ERROR_UNKNOWN_ITEM, cashshop_buy(&customer, 0, 2, data));
	TEST_ASSERT_EQUAL_INT(1000, customer.shop_point);
	TEST_ASSERT_EQUAL_INT(3, cashshop_account_remaining(&customer, 1));
	TEST_ASSERT_EQUAL_INT(0, saves);
	TEST_ASSERT_EQUAL_INT(CASHSHOP_RESULT_SUCCESS, cashshop_buy(&customer, 0, 1, data));
	TEST_ASSERT_EQUAL_INT(800, customer.shop_point);
	TEST_ASSERT_EQUAL_INT(1, cashshop_account_remaining(&customer, 1));
	{
		struct cashshop_account_count stale = {1, 0};
		cashshop_account_receive(&customer, customer.cashshop_account_token, 1, &stale, 1);
		TEST_ASSERT_EQUAL_INT(1, cashshop_account_remaining(&customer, 1));
	}
	TEST_ASSERT_EQUAL_INT(CASHSHOP_RESULT_ERROR_UNKNOWN_ITEM, cashshop_buy(&customer, 0, 1, data));
	request_row(data, 501, 1, 8);
	TEST_ASSERT_EQUAL_INT(CASHSHOP_RESULT_SUCCESS, cashshop_buy(&customer, 0, 1, data));
	TEST_ASSERT_EQUAL_INT(0, cashshop_account_remaining(&customer, 1));
	TEST_ASSERT_EQUAL_INT(2, saves);
	cashshop_account_close(&customer);
}

void test_account_cashshop_preflight_and_normal_purchase(void)
{
	unsigned char data[20];
	setup_account();
	TEST_ASSERT_TRUE(cashshop_insert(0, 1201, 2000, 0, 0));
	TEST_ASSERT_TRUE(cashshop_insert(0, 501, 10, 0, 0));
	load_count(1);
	request_row(data, 501, 1, 8);
	request_row(data + 10, 1201, 1, 0);
	TEST_ASSERT_EQUAL_INT(CASHSHOP_RESULT_ERROR_SHORTTAGE_CASH, cashshop_buy(&customer, 0, 2, data));
	TEST_ASSERT_EQUAL_INT(1000, customer.shop_point);
	TEST_ASSERT_EQUAL_INT(2, cashshop_account_remaining(&customer, 1));
	request_row(data, 501, 1, 0);
	TEST_ASSERT_EQUAL_INT(CASHSHOP_RESULT_SUCCESS, cashshop_buy(&customer, 0, 1, data));
	TEST_ASSERT_EQUAL_INT(990, customer.shop_point);
	TEST_ASSERT_EQUAL_INT(2, cashshop_account_remaining(&customer, 1));
	TEST_ASSERT_EQUAL_INT(0, saves);
	cashshop_account_close(&customer);
}

void test_account_cashshop_stale_reply_and_catalog_reload(void)
{
	struct cashshop_account_count history = {1, 2};
	unsigned int old_token;
	unsigned char data[10];
	setup_account();
	cashshop_account_request(&customer);
	old_token = customer.cashshop_account_token;
	cashshop_account_close(&customer);
	cashshop_account_request(&customer);
	TEST_ASSERT_NOT_EQUAL(old_token, customer.cashshop_account_token);
	cashshop_account_receive(&customer, old_token, 1, &history, 1);
	TEST_ASSERT_FALSE(customer.cashshop_account_loaded);
	cashshop_account_receive(&customer, customer.cashshop_account_token, 1, &history, 1);
	TEST_ASSERT_EQUAL_INT(1, cashshop_account_remaining(&customer, 1));
	cashshop_clear();
	TEST_ASSERT_TRUE(cashshop_account_insert(1, 501, 100, 3,
		(unsigned int)time(NULL) - 10, (unsigned int)time(NULL) + 600));
	request_row(data, 501, 1, 8);
	TEST_ASSERT_EQUAL_INT(CASHSHOP_RESULT_ERROR_UNKNOWN_ITEM, cashshop_buy(&customer, 0, 1, data));
	TEST_ASSERT_EQUAL_INT(1000, customer.shop_point);
	cashshop_account_close(&customer);
}

void test_account_cashshop_load_failure_and_disconnect(void)
{
	unsigned char data[10];
	setup_account();
	cashshop_account_request(&customer);
	cashshop_account_receive(&customer, customer.cashshop_account_token, 0, NULL, 0);
	TEST_ASSERT_FALSE(customer.cashshop_account_loaded);
	TEST_ASSERT_NULL(customer.cashshop_account_history);
	connected = 0;
	cashshop_account_request(&customer);
	request_row(data, 501, 1, 8);
	TEST_ASSERT_EQUAL_INT(CASHSHOP_RESULT_ERROR_UNKNOWN_ITEM, cashshop_buy(&customer, 0, 1, data));
	TEST_ASSERT_EQUAL_INT(1000, customer.shop_point);
	connected = 1;
	cashshop_account_close(&customer);
}

void test_account_cashshop_txt_restart_and_monotonic_counts(void)
{
	const char *path = "account_cashshop_test.tmp";
	struct cashshop_account_count rows[2] = {{1, 3}, {2, 1}};
	FILE *fp = fopen(path, "r");
	TEST_ASSERT_NULL(fp);
	cashshopdb_txt_config_read("cashshop_txt", path);
	TEST_ASSERT_TRUE(cashshopdb_txt_init());
	TEST_ASSERT_TRUE(cashshopdb_txt_save(100, rows, 2));
	rows[0].purchased = 1;
	TEST_ASSERT_TRUE(cashshopdb_txt_save(100, rows, 2));
	TEST_ASSERT_TRUE(cashshopdb_txt_load(100, rows, 2));
	TEST_ASSERT_EQUAL_UINT(3, rows[0].purchased);
	TEST_ASSERT_EQUAL_INT(0, cashshopdb_txt_sync());
	cashshopdb_txt_final();
	TEST_ASSERT_TRUE(cashshopdb_txt_init());
	rows[0].purchased = 0;
	TEST_ASSERT_TRUE(cashshopdb_txt_load(100, rows, 2));
	TEST_ASSERT_EQUAL_UINT(3, rows[0].purchased);
	TEST_ASSERT_TRUE(cashshopdb_txt_load(101, rows, 2));
	TEST_ASSERT_EQUAL_UINT(0, rows[0].purchased);
	cashshopdb_txt_final();
	fp = fopen(path, "a");
	TEST_ASSERT_NOT_NULL(fp);
	fputs("100 3", fp);
	fclose(fp);
	TEST_ASSERT_FALSE(cashshopdb_txt_init());
	TEST_ASSERT_FALSE(cashshopdb_txt_load(100, rows, 2));
	cashshopdb_txt_final();
	TEST_ASSERT_EQUAL_INT(0, remove(path));
}

void test_account_cashshop_period_and_ui_close(void)
{
	unsigned int now = (unsigned int)time(NULL);
	setup_account();
	load_count(1);
	TEST_ASSERT_TRUE(pc_ui_end(&customer, PC_UI_CASHSHOP));
	TEST_ASSERT_NULL(customer.cashshop_account_history);
	TEST_ASSERT_EQUAL_INT(0, customer.cashshop_account_token);
	cashshop_clear();
	TEST_ASSERT_TRUE(cashshop_account_insert(1, 501, 0, 1, now - 60, now));
	TEST_ASSERT_FALSE(cashshop_account_available(cashshop_account_item_at(0)));
	cashshop_clear();
	TEST_ASSERT_TRUE(cashshop_account_insert(1, 501, 0, 1, now, now + 600));
	TEST_ASSERT_TRUE(cashshop_account_available(cashshop_account_item_at(0)));
	cashshop_clear();
	TEST_ASSERT_TRUE(cashshop_account_insert(1, 501, 0, 1, now + 600, now + 1200));
	TEST_ASSERT_FALSE(cashshop_account_available(cashshop_account_item_at(0)));
}

void test_account_cashshop_txt_rejects_unread_journal(void)
{
	const char *txt = "cashshop_nojournal_test.txt";
	const char *journal = "cashshop_nojournal_test.journal";
	FILE *fp = fopen(txt, "rb");
	if(fp) { fclose(fp); TEST_FAIL_MESSAGE("TXT test path already exists"); }
	fp = fopen(journal, "rb");
	if(fp) { fclose(fp); TEST_FAIL_MESSAGE("Journal test path already exists"); }
	cashshopdb_txt_config_read("cashshop_txt", txt);
	cashshopdb_txt_config_read("cashshop_journal_file", journal);
	fp = fopen(journal, "wb");
	TEST_ASSERT_NOT_NULL(fp);
	fputs("pending", fp);
	fclose(fp);
	TEST_ASSERT_FALSE(cashshopdb_txt_init());
	cashshopdb_txt_final();
	TEST_ASSERT_EQUAL_INT(0, remove(journal));
	TEST_ASSERT_TRUE(cashshopdb_txt_init());
	cashshopdb_txt_final();
	TEST_ASSERT_EQUAL_INT(0, remove(txt));
}
