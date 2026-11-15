#include <string.h>
#include <limits.h>

#include "unity.h"
#include "pc.h"
#include "battle.h"
#include "stylist.h"

static struct map_session_data player;
static int consumed, paid, mailed, saved, mail_error;

/* 全選択の検証が完了するまで、消費や外見変更が起きないことを確認する。 */
int pet_is_hatched_egg(const struct item *item) { return 0; }
int pc_getbodystyle(struct map_session_data *sd) { return sd->status.style; }

void pc_delitem(struct map_session_data *sd, int index, int amount, int type, short dtype)
{
	TEST_ASSERT_TRUE(sd->status.inventory[index].amount >= amount);
	sd->status.inventory[index].amount -= amount;
	consumed += amount;
}

int pc_payzeny(struct map_session_data *sd, int zeny)
{
	TEST_ASSERT_TRUE(sd->status.zeny >= zeny);
	sd->status.zeny -= zeny;
	paid += zeny;
	return 0;
}

int pc_changelook(struct map_session_data *sd, int look, int value)
{
	if(look == LOOK_HAIR) sd->status.hair = value;
	if(look == LOOK_HAIR_COLOR) sd->status.hair_color = value;
	if(look == LOOK_CLOTHES_COLOR) sd->status.clothes_color = value;
	if(look == LOOK_BODY2) sd->status.style = value;
	return 0;
}

int chrif_save(struct map_session_data *sd, int final) { saved++; return 0; }

int mail_send_system_items(const char *dest, const char *sender, const char *title,
	const char *body, int len, int zeny, const struct item *items, int count)
{
	TEST_ASSERT_EQUAL_INT(0, zeny);
	mailed = count;
	return mail_error;
}

static void setup_stylist(void)
{
	memset(&player, 0, sizeof(player));
	player.state.open_ui = PC_UI_STYLIST;
	player.status.zeny = 100;
	player.status.inventory[0].nameid = 501;
	player.status.inventory[0].amount = 1;
	battle_config.feature_stylist = 1;
	battle_config.romail = 1;
	consumed = paid = mailed = saved = mail_error = 0;
	stylist_clear();
}

void test_stylist_shared_material_preflight(void)
{
	int selection[7] = { 1, 1, 0, 0, 0, 0, 0 };
	setup_stylist();
	TEST_ASSERT_TRUE(stylist_insert(0, 1, 1, 0, 501, 0, 0, 0, 1));
	TEST_ASSERT_TRUE(stylist_insert(1, 1, 2, 0, 501, 0, 0, 0, 1));
	TEST_ASSERT_FALSE(stylist_buy(&player, selection));
	TEST_ASSERT_EQUAL_INT(0, consumed);
	TEST_ASSERT_EQUAL_INT(0, player.status.hair_color);
	player.status.inventory[0].amount = 2;
	TEST_ASSERT_TRUE(stylist_buy(&player, selection));
	TEST_ASSERT_EQUAL_INT(2, consumed);
	TEST_ASSERT_EQUAL_INT(2, player.status.hair);
}

void test_stylist_index_mapping_and_noop(void)
{
	int selection[7] = { 0, 0, 1, 0, 0, 0, 0 };
	setup_stylist();
	player.status.clothes_color = 2;
	TEST_ASSERT_TRUE(stylist_insert(2, 1, 0, 5, 501, 0, 0, 0, 1));
	TEST_ASSERT_TRUE(stylist_buy(&player, selection));
	TEST_ASSERT_EQUAL_INT(0, player.status.clothes_color);
	TEST_ASSERT_EQUAL_INT(1, consumed);
	TEST_ASSERT_EQUAL_INT(5, paid);
	TEST_ASSERT_TRUE(stylist_buy(&player, selection));
	TEST_ASSERT_EQUAL_INT(1, consumed);
	TEST_ASSERT_EQUAL_INT(5, paid);
}

void test_stylist_accessory_mail_and_failure(void)
{
	int selection[7] = { 0, 0, 0, 1, 1, 0, 0 };
	setup_stylist();
	TEST_ASSERT_TRUE(stylist_insert(3, 1, 1201, 10, 501, 0, 2, 0, 1));
	TEST_ASSERT_TRUE(stylist_insert(4, 1, 1201, 20, 0, 0, 2, 0, 1));
	mail_error = -1;
	TEST_ASSERT_FALSE(stylist_buy(&player, selection));
	TEST_ASSERT_EQUAL_INT(0, consumed);
	TEST_ASSERT_EQUAL_INT(0, paid);
	mail_error = 0;
	battle_config.romail = 0;
	TEST_ASSERT_FALSE(stylist_buy(&player, selection));
	TEST_ASSERT_EQUAL_INT(0, consumed);
	battle_config.romail = 1;
	TEST_ASSERT_TRUE(stylist_buy(&player, selection));
	TEST_ASSERT_EQUAL_INT(2, mailed);
	TEST_ASSERT_EQUAL_INT(30, paid);
	TEST_ASSERT_EQUAL_INT(1, consumed);
}

void test_stylist_job_and_species_validation(void)
{
	int selection[7] = { 0, 1, 0, 0, 0, 0, 0 };
	setup_stylist();
	TEST_ASSERT_TRUE(stylist_insert(1, 1, 2, 10, 0, 0, 1, 0, 1));
	TEST_ASSERT_FALSE(stylist_buy(&player, selection));
	TEST_ASSERT_EQUAL_INT(0, paid);
	stylist_clear();
	TEST_ASSERT_TRUE(stylist_insert(1, 1, 2, 10, 0, 0, 0, 4252, 1));
	TEST_ASSERT_FALSE(stylist_buy(&player, selection));
	player.status.class_ = 4252;
	TEST_ASSERT_TRUE(stylist_buy(&player, selection));
	TEST_ASSERT_EQUAL_INT(2, player.status.hair);
}

void test_body_style_legacy_and_explicit_values(void)
{
	TEST_ASSERT_EQUAL_INT(PC_CLASS_RK_H, mmo_body_style(PC_CLASS_RK_H, 0));
	TEST_ASSERT_EQUAL_INT(PC_CLASS_RK_2ND, mmo_body_style(PC_CLASS_RK_H, 1));
	TEST_ASSERT_EQUAL_INT(PC_CLASS_RK_2ND, mmo_body_style(PC_CLASS_RK_H, PC_CLASS_RK_2ND));
	TEST_ASSERT_EQUAL_INT(PC_CLASS_WL_H, mmo_body_style(4255, PC_CLASS_WL_H));
}


void test_stylist_costume_selection(void)
{
	int selection[7] = { 0, 0, 0, 0, 0, 0, 1 };
	setup_stylist();
#if PACKETVER >= 20231220
	player.status.class_ = 4252;
	TEST_ASSERT_TRUE(stylist_insert(9, 1, PC_CLASS_RK_H, 0, 501, 0, 2, 4252, 1));
	TEST_ASSERT_TRUE(stylist_buy(&player, selection));
	TEST_ASSERT_EQUAL_INT(PC_CLASS_RK_H, player.status.style);
#else
	player.status.class_ = PC_CLASS_RK_H;
	player.s_class.job = PC_JOB_RK;
	TEST_ASSERT_TRUE(stylist_insert(6, 1, 1, 0, 501, 0, 0, 0, 1));
	TEST_ASSERT_TRUE(stylist_buy(&player, selection));
	TEST_ASSERT_EQUAL_INT(1, player.status.style);
#endif
	TEST_ASSERT_EQUAL_INT(1, consumed);
}

void test_stylist_doram_coloring(void)
{
	int selection[7] = { 1, 1, 0, 0, 0, 0, 0 };
	setup_stylist();
	player.s_class.job = PC_JOB_SUM;
	TEST_ASSERT_TRUE(stylist_insert(0, 1, 1, 0, 0, 0, 2, 0, 1));
	TEST_ASSERT_TRUE(stylist_insert(1, 1, 2, 0, 501, 0, 1, 0, 0));
	TEST_ASSERT_FALSE(stylist_buy(&player, selection));
	TEST_ASSERT_EQUAL_INT(0, consumed);
	TEST_ASSERT_EQUAL_INT(0, player.status.hair_color);
	selection[0] = 0;
	TEST_ASSERT_TRUE(stylist_buy(&player, selection));
	TEST_ASSERT_EQUAL_INT(2, player.status.hair);
}

void test_stylist_box_fallback_and_total_price(void)
{
	int selection[7] = { 1, 1, 0, 0, 0, 0, 0 };
	setup_stylist();
	player.status.zeny = INT_MAX;
	TEST_ASSERT_TRUE(stylist_insert(0, 1, 1, INT_MAX, 0, 0, 0, 0, 1));
	TEST_ASSERT_TRUE(stylist_insert(1, 1, 2, INT_MAX, 0, 0, 0, 0, 1));
	TEST_ASSERT_FALSE(stylist_buy(&player, selection));
	TEST_ASSERT_EQUAL_INT(0, paid);
	stylist_clear();
	selection[1] = 0;
	TEST_ASSERT_TRUE(stylist_insert(0, 1, 1, 10, 1201, 501, 0, 0, 1));
	TEST_ASSERT_TRUE(stylist_buy(&player, selection));
	TEST_ASSERT_EQUAL_INT(1, consumed);
	TEST_ASSERT_EQUAL_INT(10, paid);
}
