#include <string.h>
#include "unity.h"
#include "../src/map/map.h"
#include "../src/map/pc_ui.h"

static struct map_session_data sd;

void test_pc_ui_exclusive_pairs(void)
{
	int current, next;
	for(current = PC_UI_NONE; current < PC_UI_MAX; current++) {
		for(next = PC_UI_REFINE; next < PC_UI_MAX; next++) {
			int mail_pair = (current == PC_UI_RODEX || current == PC_UI_RODEX_WRITE) &&
			                (next == PC_UI_RODEX || next == PC_UI_RODEX_WRITE);
			memset(&sd, 0, sizeof(sd));
			if(current != PC_UI_NONE)
				TEST_ASSERT_TRUE(pc_ui_begin(&sd, (enum pc_ui_type)current));
			TEST_ASSERT_EQUAL_INT(current == PC_UI_NONE || current == next || mail_pair,
				pc_ui_begin(&sd, (enum pc_ui_type)next));
			if(current != PC_UI_NONE && current != next && !mail_pair)
				TEST_ASSERT_TRUE(pc_ui_is(&sd, (enum pc_ui_type)current));
		}
	}
}

void test_pc_ui_end_wrong_type(void)
{
	memset(&sd, 0, sizeof(sd));
	pc_ui_begin(&sd, PC_UI_BARTER);
	sd.npc_shopid = 123;
	TEST_ASSERT_FALSE(pc_ui_end(&sd, PC_UI_RODEX));
	TEST_ASSERT_EQUAL_INT(123, sd.npc_shopid);
	TEST_ASSERT_TRUE(pc_ui_is(&sd, PC_UI_BARTER));
	TEST_ASSERT_TRUE(pc_ui_end(&sd, PC_UI_BARTER));
	TEST_ASSERT_EQUAL_INT(0, sd.npc_shopid);
	TEST_ASSERT_TRUE(pc_ui_is(&sd, PC_UI_NONE));
}

void test_pc_ui_preserves_mail_transaction(void)
{
	memset(&sd, 0, sizeof(sd));
	pc_ui_begin(&sd, PC_UI_RODEX);
	sd.mail_preflight_token = 123;
	sd.mail_pending_flag = 1;
	sd.state.mail_appending = 1;
	sd.state.mail_writing = 1;
	TEST_ASSERT_TRUE(pc_ui_end(&sd, PC_UI_RODEX));
	TEST_ASSERT_EQUAL_UINT(123, sd.mail_preflight_token);
	TEST_ASSERT_EQUAL_INT(1, sd.mail_pending_flag);
	TEST_ASSERT_EQUAL_INT(1, sd.state.mail_appending);
	TEST_ASSERT_EQUAL_INT(1, sd.state.mail_writing);
}

void test_pc_ui_mail_compose_lifecycle(void)
{
	memset(&sd, 0, sizeof(sd));
	TEST_ASSERT_TRUE(pc_ui_begin(&sd, PC_UI_RODEX_WRITE));
	TEST_ASSERT_FALSE(pc_ui_is(&sd, PC_UI_RODEX));
	TEST_ASSERT_TRUE(pc_ui_end(&sd, PC_UI_RODEX_WRITE));
	TEST_ASSERT_TRUE(pc_ui_is(&sd, PC_UI_NONE));
	pc_ui_begin(&sd, PC_UI_RODEX);
	TEST_ASSERT_TRUE(pc_ui_begin(&sd, PC_UI_RODEX_WRITE));
	TEST_ASSERT_FALSE(pc_ui_end(&sd, PC_UI_RODEX_WRITE));
	TEST_ASSERT_TRUE(pc_ui_is(&sd, PC_UI_RODEX));
	pc_ui_end(&sd, PC_UI_RODEX);
	pc_ui_begin(&sd, PC_UI_RODEX_WRITE);
	TEST_ASSERT_TRUE(pc_ui_begin(&sd, PC_UI_RODEX));
	TEST_ASSERT_TRUE(pc_ui_is(&sd, PC_UI_RODEX));
}

void test_pc_ui_policy_preserves_actions(void)
{
	int type;
	unsigned int action;
	memset(&sd, 0, sizeof(sd));
	TEST_ASSERT_FALSE(pc_ui_blocks(&sd, 0x7f));
	for(type = PC_UI_REFINE; type < PC_UI_MAX; type++) {
		sd.state.open_ui = (enum pc_ui_type)type;
		TEST_ASSERT_TRUE(pc_ui_blocks(&sd, PC_UI_BLOCK_OTHER_UI));
		for(action = PC_UI_BLOCK_MOVE; action <= PC_UI_BLOCK_TRADE; action <<= 1)
			TEST_ASSERT_EQUAL_INT(type == PC_UI_REFINE, pc_ui_blocks(&sd, action));
	}
}

void test_pc_ui_warp_policy(void)
{
	int type;
	for(type = PC_UI_REFINE; type < PC_UI_MAX; type++) {
		int keep = type == PC_UI_RODEX || type == PC_UI_RODEX_WRITE;
		memset(&sd, 0, sizeof(sd));
		pc_ui_begin(&sd, (enum pc_ui_type)type);
		sd.mail_preflight_token = 321;
		pc_ui_on_warp(&sd);
		TEST_ASSERT_EQUAL_INT(keep ? type : PC_UI_NONE, sd.state.open_ui);
		TEST_ASSERT_EQUAL_UINT(321, sd.mail_preflight_token);
	}
}

void test_pc_ui_invalid_state(void)
{
	memset(&sd, 0, sizeof(sd));
	TEST_ASSERT_FALSE(pc_ui_begin(&sd, PC_UI_NONE));
	TEST_ASSERT_FALSE(pc_ui_begin(&sd, PC_UI_MAX));
	TEST_ASSERT_FALSE(pc_ui_begin(NULL, PC_UI_REFINE));
	TEST_ASSERT_FALSE(pc_ui_end(&sd, PC_UI_NONE));
	sd.state.open_ui = PC_UI_MAX;
	TEST_ASSERT_FALSE(pc_ui_can_open(&sd, PC_UI_REFINE));
	TEST_ASSERT_TRUE(pc_ui_blocks(&sd, PC_UI_BLOCK_OTHER_UI));
	sd.state.open_ui = (enum pc_ui_type)-1;
	TEST_ASSERT_TRUE(pc_ui_blocks(&sd, PC_UI_BLOCK_MOVE));
}
