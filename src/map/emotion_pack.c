/*
 * Copyright (C) 2002-2026  Auriga
 *
 * Cash emotion packs: catalog from db/emotion_pack.lua.
 * Permanent packs share #EMOTION_PACKS. Rentals store expiry in #EMO_P<id>.
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "emotion_pack.h"
#include "battle.h"
#include "clif.h"
#include "intif.h"
#include "pet.h"
#include "nullpo.h"
#include "pc.h"
#include "skill.h"

static struct emotion_pack_data emotion_pack_db[EMOTION_PACK_MAX];
static int emotion_pack_num = 0;


const struct emotion_pack_data *emotion_pack_search(int id)
{
	int i;

	if(id <= 0)
		return NULL;
	for(i = 0; i < emotion_pack_num; i++) {
		if(emotion_pack_db[i].id == id)
			return &emotion_pack_db[i];
	}
	return NULL;
}

static void emotion_pack_regname(char *buf, size_t sz, int pack_id)
{
	snprintf(buf, sz, "#EMO_P%d", pack_id);
}

static int emotion_pack_set_state(struct map_session_data *sd, int pack_id, int value)
{
	char name[32];

	nullpo_retr(-1, sd);
	if(!sd->state.accountreg_ready || pack_id < 1 || pack_id > EMOTION_PACK_ID_MAX)
		return -1;
	emotion_pack_regname(name, sizeof(name), pack_id);

	if(value == 1) {
		unsigned int mask = (unsigned int)pc_readaccountreg(sd, EMOTION_PACK_REG_MASK);
		unsigned int bit = 1u << (pack_id - 1);

		if(!mask && sd->save_reg.account_num >= ACCOUNT_REG_NUM) {
			int i;

			for(i = 0; i < sd->save_reg.account_num; i++) {
				struct global_reg *reg = &sd->save_reg.account[i];
				int old_pack = pack_id;
				int j;

				if(strcmpi(reg->str, name) != 0) {
					if(reg->value != 1)
						continue;
					for(j = 1; j <= EMOTION_PACK_ID_MAX; j++) {
						char old_name[32];

						emotion_pack_regname(old_name, sizeof(old_name), j);
						if(strcmpi(reg->str, old_name) == 0)
							break;
					}
					if(j > EMOTION_PACK_ID_MAX)
						continue;
					old_pack = j;
				}

				strcpy(reg->str, EMOTION_PACK_REG_MASK);
				reg->value = (int)(bit | (1u << (old_pack - 1)));
				intif_saveaccountreg(sd);
				pc_setaccountreg(sd, name, 0);
				return 0;
			}
		}

		if(pc_setaccountreg(sd, EMOTION_PACK_REG_MASK, (int)(mask | bit)) != 0)
			return -1;
		pc_setaccountreg(sd, name, 0);
		return 0;
	}
	return pc_setaccountreg(sd, name, value);
}

static int emotion_pack_get_state(struct map_session_data *sd, int pack_id)
{
	char name[32];
	unsigned int mask;
	int value;

	nullpo_retr(0, sd);
	if(!sd->state.accountreg_ready || pack_id < 1 || pack_id > EMOTION_PACK_ID_MAX)
		return 0;

	mask = (unsigned int)pc_readaccountreg(sd, EMOTION_PACK_REG_MASK);
	if(mask & (1u << (pack_id - 1)))
		return 1;

	emotion_pack_regname(name, sizeof(name), pack_id);
	value = pc_readaccountreg(sd, name);
	if(value == 1)
		emotion_pack_set_state(sd, pack_id, 1);
	return value;
}

unsigned int emotion_pack_expire(struct map_session_data *sd, int pack_id)
{
	int v;

	nullpo_retr(0, sd);
	if(pack_id <= 0)
		return 0;
	v = emotion_pack_get_state(sd, pack_id);
	if(v <= 1)
		return 0;	/* none or permanent */
	return (unsigned int)v;
}

int emotion_pack_owned(struct map_session_data *sd, int pack_id)
{
	int v;
	time_t now;

	nullpo_retr(0, sd);
	if(pack_id <= 0)
		return 1;	/* free / basic group */
	v = emotion_pack_get_state(sd, pack_id);
	if(v == 1)
		return 1;
	if(v <= 0)
		return 0;
	now = time(NULL);
	if((time_t)v > now)
		return 1;
	/* expired rental — clear */
	emotion_pack_set_state(sd, pack_id, 0);
	return 0;
}

int emotion_pack_unlock(struct map_session_data *sd, int pack_id)
{
	nullpo_retr(-1, sd);
	if(pack_id <= 0 || pack_id > EMOTION_PACK_ID_MAX)
		return -1;
	if(emotion_pack_search(pack_id) == NULL)
		return -1;
	return emotion_pack_set_state(sd, pack_id, 1);
}

static unsigned int emotion_pack_today(void)
{
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);

	if(tm == NULL)
		return 0;
	return (unsigned int)((tm->tm_year + 1900) * 10000 + (tm->tm_mon + 1) * 100 + tm->tm_mday);
}

int emotion_pack_has_emotion(int pack_id, int emotion_id)
{
	/* Client enum IDs for the three built-in packs. */
	static const unsigned char ids[][11] = {
		{ 1, 27, 29, 38, 52, 95, 255 },
		{ 0, 1, 2, 5, 10, 11, 12, 15, 33, 37, 255 },
		{ 4, 14, 37, 39, 40, 42, 43, 44, 47, 56, 255 },
	};
	int i;

	if(emotion_id < 0 || emotion_id >= 108)
		return 0;
	if(pack_id < 1 || pack_id > 3)
		return 1;
	for(i = 0; ids[pack_id - 1][i] != 255; i++) {
		if(ids[pack_id - 1][i] == emotion_id)
			return 1;
	}
	return 0;
}

int emotion_pack_can_use(struct map_session_data *sd, int pack_id)
{
	nullpo_retr(0, sd);
	if(pack_id <= 0)
		return 1;
	if(!battle_config.feature_emotion_cash)
		return 0;
	return emotion_pack_owned(sd, pack_id);
}

int emotion_pack_buy(struct map_session_data *sd, int pack_id)
{
	const struct emotion_pack_data *pack;
	unsigned int today;
	int i, need_amount, state;
	int consume[MAX_INVENTORY] = {0};
	time_t now;

	nullpo_retr(-1, sd);

	if(!battle_config.feature_emotion_cash)
		return 6;
	if(!sd->state.accountreg_ready)
		return 6;

	pack = emotion_pack_search(pack_id);
	if(pack == NULL)
		return 6;

	today = emotion_pack_today();
	if(pack->start_date > 0 && today < pack->start_date)
		return 5;
	if(pack->end_date > 0 && today > pack->end_date)
		return 1;

	if(emotion_pack_owned(sd, pack_id))
		return 2;

	if(battle_config.basic_skill_check != 0 &&
	   pc_checkskill(sd, NV_BASIC) < 2 && pc_checkskill(sd, SU_BASIC_SKILL) < 1)
		return 4;

	now = time(NULL);
	if(pack->duration > 0 && (now <= 1 || pack->duration > INT_MAX || now > INT_MAX - (int)pack->duration))
		return 6;
	state = pack->duration > 0 ? (int)(now + pack->duration) : 1;

	need_amount = pack->price;
	if(need_amount > 0) {
		if(pack->item_id > 0) {
			int remaining = need_amount;
			int slots = pc_inventory_slots(sd);

			for(i = 0; i < slots && remaining > 0; i++) {
				const struct item *it = &sd->status.inventory[i];
				if(it->nameid != pack->item_id || it->amount <= 0 ||
				   !sd->inventory_data[i] || pet_is_hatched_egg(it))
					continue;
				consume[i] = (it->amount < remaining) ? it->amount : remaining;
				remaining -= consume[i];
			}
			if(remaining > 0)
				return 0;
		} else if(sd->shop_point < need_amount) {
			return 0;
		}
	}

	if(emotion_pack_set_state(sd, pack_id, state) != 0)
		return 6;
	if(need_amount > 0) {
		if(pack->item_id > 0) {
			for(i = 0; i < pc_inventory_slots(sd); i++) {
				if(consume[i] > 0)
					pc_delitem(sd, i, consume[i], 0, 0);
			}
		} else {
			pc_setparam(sd, SP_SHOP_POINT, sd->shop_point - need_amount);
			clif_updatestatus(sd, SP_SHOP_POINT);
		}
	}
	return -1;	/* success */
}

void emotion_pack_clear(void)
{
	emotion_pack_num = 0;
	memset(emotion_pack_db, 0, sizeof(emotion_pack_db));
}

int emotion_pack_insert(int id, int price, int item_id,
	unsigned int start_date, unsigned int end_date, unsigned int duration)
{
	struct emotion_pack_data *pack;

	if(id <= 0 || id > EMOTION_PACK_ID_MAX || price < 0)
		return 0;
	if(start_date > 0 && end_date > 0 && start_date > end_date)
		return 0;
	if(emotion_pack_search(id) != NULL) {
		printf("emotion_pack_insert: duplicate id %d\n", id);
		return 0;
	}
	if(emotion_pack_num >= EMOTION_PACK_MAX) {
		printf("emotion_pack_insert: list full\n");
		return 0;
	}
	pack = &emotion_pack_db[emotion_pack_num++];
	memset(pack, 0, sizeof(*pack));
	pack->id = (short)id;
	pack->price = price;
	pack->item_id = item_id;
	pack->start_date = start_date;
	pack->end_date = end_date;
	pack->duration = duration;
	return 1;
}


int do_init_emotion_pack(void)
{
	emotion_pack_clear();
	return 0;
}

void do_final_emotion_pack(void)
{
	emotion_pack_clear();
}
