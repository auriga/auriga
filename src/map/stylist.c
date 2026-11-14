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
#include <string.h>
#include <limits.h>

#include "utils.h"
#include "battle.h"
#include "itemdb.h"
#include "pc.h"
#include "pet.h"
#include "mail.h"
#include "chrif.h"
#include "stylist.h"
#include "unit.h"

#define MAX_STYLIST_ENTRIES 512

struct stylist_entry {
	int action, index, value, zeny, item, box, species, job, coloring;
};

static struct stylist_entry stylist_db[MAX_STYLIST_ENTRIES];
static int stylist_count;

void stylist_clear(void)
{
	stylist_count = 0;
	memset(stylist_db, 0, sizeof(stylist_db));
}

int stylist_insert(int action, int index, int value, int zeny, int item, int box, int species, int job, int coloring)
{
	struct stylist_entry *entry;
	int i;

	if((action < 0 || action > 6) && action != 9)
		return 0;
	if(index <= 0 || index > SHRT_MAX || value < 0 ||
	   ((action < 3 || action == 6 || action == 9) && value > SHRT_MAX) || zeny < 0 ||
	   item < 0 || box < 0 || species < 0 || species > 2 || job < 0 || stylist_count >= MAX_STYLIST_ENTRIES)
		return 0;
	for(i = 0; i < stylist_count; i++) {
		entry = &stylist_db[i];
		if(entry->action == action && entry->index == index &&
		   (entry->species == species || entry->species == 2 || species == 2))
			return 0;
	}
	entry = &stylist_db[stylist_count++];
	entry->action = action;
	entry->index = index;
	entry->value = value;
	entry->zeny = zeny;
	entry->item = item;
	entry->box = box;
	entry->species = species;
	entry->job = job;
	entry->coloring = coloring != 0;
	return 1;
}

static const struct stylist_entry *stylist_find(struct map_session_data *sd, int action, int index)
{
	int i, species = pc_isdoram(sd) ? 1 : 0;

	for(i = 0; i < stylist_count; i++) {
		const struct stylist_entry *entry = &stylist_db[i];
		if(entry->action == action && entry->index == index &&
		   (entry->species == species || entry->species == 2) &&
		   (entry->job == 0 || entry->job == sd->status.class_))
			return entry;
	}
	return NULL;
}

/* 全選択の料金・素材を検証し終えるまで、外見や所持品を変更しない。 */
int stylist_buy(struct map_session_data *sd, const int *selection)
{
	const struct stylist_entry *entries[7] = { NULL };
	struct item rewards[3];
	int need[MAX_INVENTORY] = { 0 };
	atn_bignumber zeny = 0;
	int i, j, k, slots, reward_count = 0;
	static const int looks[] = { LOOK_HAIR_COLOR, LOOK_HAIR, LOOK_CLOTHES_COLOR };

	if(!sd || !selection || !battle_config.feature_stylist || !pc_ui_is(sd, PC_UI_STYLIST) ||
	   sd->npc_shopid || sd->state.store || sd->state.deal_mode || sd->state.storage_flag ||
	   sd->chatID || sd->state.mail_appending || sd->status.manner < 0 || unit_isdead(&sd->bl))
		return 0;
	// ドラムは選択後の髪型で染色できるか、クライアントと同じ設定を確認する。
	if(pc_isdoram(sd) && selection[0]) {
		const struct stylist_entry *hair = NULL;
		if(selection[1]) {
			hair = stylist_find(sd, 1, selection[1]);
		} else {
			for(i = 0; i < stylist_count; i++) {
				if(stylist_db[i].action == 1 && stylist_db[i].species == 1 &&
				   stylist_db[i].value == sd->status.hair) {
					hair = &stylist_db[i];
					break;
				}
			}
		}
		if(!hair || !hair->coloring)
			return 0;
	}
	slots = pc_inventory_slots(sd);
	memset(rewards, 0, sizeof(rewards));
	for(i = 0; i < 7; i++) {
		const struct stylist_entry *entry;
		int action = i;

		if(selection[i] == 0)
			continue;
#if PACKETVER >= 20231220
		if(i == 6)
			action = 9;
#endif
		entry = stylist_find(sd, action, selection[i]);
		if(entry == NULL)
			return 0;
		if((i == 0 && entry->value >= MAX_HAIR_COLOR) ||
		   (i == 1 && entry->value >= MAX_HAIR_STYLE) ||
		   (i == 2 && entry->value >= MAX_CLOTH_COLOR))
			return 0;
		if(i == 6) {
#if PACKETVER < 20231220
			if(entry->value > 1 || !pc_is3rdclass(sd) || pc_is4thclass(sd) || pc_isdoram(sd) ||
			   mmo_body_style(sd->status.class_, 1) == sd->status.class_)
				return 0;
#else
			if(entry->job == 0 || entry->value == 0)
				return 0;
#endif
		}
		// 選択番号と外見値は一致しない。既に同じ外見なら消費しない。
		if((i == 0 && entry->value == sd->status.hair_color) ||
		   (i == 1 && entry->value == sd->status.hair) ||
		   (i == 2 && entry->value == sd->status.clothes_color) ||
		   (i == 6 && entry->value == pc_getbodystyle(sd)))
			continue;
		entries[i] = entry;
		zeny += entry->zeny;
		if(zeny > sd->status.zeny)
			return 0;
		if(i >= 3 && i <= 5) {
			if(!battle_config.romail || itemdb_exists(entry->value) == NULL)
				return 0;
			rewards[reward_count].nameid = entry->value;
			rewards[reward_count].amount = 1;
			rewards[reward_count++].identify = 1;
		}
		if(entry->item == 0 && entry->box == 0)
			continue;
		// チケットを優先し、足りなければ箱を1個消費する。
		for(k = 0; k < 2; k++) {
			int nameid = k == 0 ? entry->item : entry->box;
			if(nameid <= 0 || itemdb_exists(nameid) == NULL)
				continue;
			for(j = 0; j < slots; j++) {
				struct item *it = &sd->status.inventory[j];
				if(it->nameid == nameid && it->amount > need[j] && !it->equip && !pet_is_hatched_egg(it))
					break;
			}
			if(j < slots) {
				need[j]++;
				break;
			}
		}
		if(k == 2)
			return 0;
	}

	// 衣装は既存のシステムメール経路にまとめて渡す。送信不可なら消費しない。
	if(reward_count && mail_send_system_items(sd->status.name, "StylingShop",
	   "<MSG>2949</MSG>", "<MSG>2950</MSG>", (int)strlen("<MSG>2950</MSG>"),
	   0, rewards, reward_count) != 0)
		return 0;
	for(j = 0; j < slots; j++) {
		if(need[j])
			pc_delitem(sd, j, need[j], 0, 0);
	}
	if(zeny > 0)
		pc_payzeny(sd, BIGNUM2INT(zeny));
	for(i = 0; i < 3; i++) {
		if(entries[i])
			pc_changelook(sd, looks[i], entries[i]->value);
	}
	if(entries[6])
		pc_changelook(sd, LOOK_BODY2, entries[6]->value);
	chrif_save(sd, 0);
	return 1;
}
