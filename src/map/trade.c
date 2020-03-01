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

#include "nullpo.h"

#include "clif.h"
#include "itemdb.h"
#include "map.h"
#include "trade.h"
#include "pc.h"
#include "npc.h"
#include "battle.h"
#include "chrif.h"
#include "unit.h"

/*==========================================
 * 取引要請を相手に送る
 *------------------------------------------
 */
void trade_traderequest(struct map_session_data *sd,int target_id)
{
	// clif_tradestart flag: 0: You are too far away from the person to trade., 1: This Character is not currently online or does not exist, 2: The person is in another trade., 3: (trade ok->open the trade window)., 4: The deal has been rejected.
	struct map_session_data *target_sd;

	nullpo_retv(sd);

	if(sd->npc_id)
		npc_event_dequeue(sd);

	target_sd = map_id2sd(target_id);
	if(target_sd && target_sd->bl.prev && sd != target_sd) { // check same player to avoid hack
		if(target_sd->state.storage_flag) {
			clif_tradestart(sd, 5);
			return;
		}
		if(target_sd->state.store || target_sd->state.mail_appending) {
			clif_tradestart(sd, 4);
			return;
		}
		if(!battle_config.invite_request_check) {
			if(target_sd->guild_invite > 0 || target_sd->party_invite > 0 || target_sd->adopt_invite) {
				clif_tradestart(sd,2);	// 相手はPT要請中かGuild要請中か養子要請中
				return;
			}
		}
		if(target_sd->trade.partner != 0) {
			clif_tradestart(sd, 2);
		} else if(sd->bl.m != target_sd->bl.m || unit_distance(&sd->bl, &target_sd->bl) > 2) {
			clif_tradestart(sd, 0);
		} else if(battle_config.gvg_trade_request_refused && map[sd->bl.m].flag.gvg &&
		          target_sd->status.guild_id > 0 && sd->status.guild_id != target_sd->status.guild_id) {
				// if on a gvg map and not in same guild (that can block other player when WoE)
				clif_tradestart(sd, 4);
		} else if(battle_config.pvp_trade_request_refused && map[sd->bl.m].flag.pvp) {
			// Same on PVP map
			clif_tradestart(sd, 4);
		} else {
			target_sd->trade.partner = sd->status.account_id;
			sd->trade.partner = target_sd->status.account_id;
			clif_traderequest(target_sd,sd->status.name);
		}
	} else {
		clif_tradestart(sd, 1);
	}

	return;
}

/*==========================================
 * 取引要請
 *------------------------------------------
 */
void trade_tradeack(struct map_session_data *sd, unsigned char type)
{
	struct map_session_data *target_sd;

	nullpo_retv(sd);

	// possible types: 3: trade ok., 4: trade canceled.
	if (type != 3 && type != 4)
		return;

	if(sd->npc_id != 0)
		npc_event_dequeue(sd);

	target_sd = map_id2sd(sd->trade.partner);
	if(target_sd && target_sd->bl.prev) {
		if(sd->bl.m != target_sd->bl.m || unit_distance(&sd->bl, &target_sd->bl) > 2) {
			trade_tradecancel(sd);
			return;
		}
		if(sd->state.storage_flag || target_sd->state.storage_flag) {
			trade_tradecancel(target_sd);
			trade_tradecancel(sd);
			return;
		}
		clif_tradestart(target_sd,type);
		clif_tradestart(sd,type);
		if(type == 4) {	// Cancel
			sd->state.deal_locked = 0;
			sd->state.deal_mode   = 0;
			sd->trade.partner     = 0;
			target_sd->state.deal_locked = 0;
			target_sd->state.deal_mode   = 0;
			target_sd->trade.partner     = 0;
		} else {
			sd->state.deal_mode        = 1;
			target_sd->state.deal_mode = 1;
		}
	}

	return;
}

/*==========================================
 * アイテム追加
 *------------------------------------------
 */
void trade_tradeadditem(struct map_session_data *sd, int idx, int amount)
{
	struct map_session_data *target_sd;

	nullpo_retv(sd);

	target_sd = map_id2sd(sd->trade.partner);
	if (target_sd && target_sd->bl.prev && sd->state.deal_locked < 1) {
		if (idx < 2 || idx >= MAX_INVENTORY + 2) {
			if (idx == 0 && amount > 0 && amount <= sd->status.zeny) {
				if(
					target_sd->status.zeny - target_sd->trade.zeny + amount <= MAX_ZENY &&
					target_sd->status.zeny - target_sd->trade.zeny + amount >= 0 // overflow 対策
				) {
					sd->trade.zeny=amount;
					clif_tradeadditem(sd,target_sd,0,amount);
				} else {
					clif_tradeitemok(sd, idx, 1); //fail to add item
				}
			}
		} else if (amount <= sd->status.inventory[idx-2].amount && amount > 0 && itemdb_isdropable(sd->status.inventory[idx-2].nameid)) {
			int trade_i;
			int trade_weight = 0;

			for(trade_i = 0; trade_i < MAX_DEAL_ITEMS; trade_i++) {
				if(sd->trade.item_amount[trade_i] == 0){
					trade_weight += sd->inventory_data[idx-2]->weight * amount;
					if(target_sd->weight + trade_weight > target_sd->max_weight){
						clif_tradeitemok(sd, idx, 1); //fail to add item -- the player was over weighted.
					}else{
						// re-deal is check when trade is commited.
						sd->trade.item_index[trade_i]  = idx;
						sd->trade.item_amount[trade_i] = amount;
						clif_tradeitemok(sd, idx, 0); //success to add item
						clif_tradeadditem(sd, target_sd, idx, amount);
					}
					break;
				}else{
					trade_weight+=sd->inventory_data[sd->trade.item_index[trade_i]-2]->weight*sd->trade.item_amount[trade_i];
				}
			}
		} else {
			clif_tradeitemok(sd, idx, 1); //fail to add item
		}
	}

	return;
}

/*==========================================
 * アイテム追加完了(ok押し)
 *------------------------------------------
 */
void trade_tradeok(struct map_session_data *sd)
{
	struct map_session_data *target_sd;

	nullpo_retv(sd);

	target_sd = map_id2sd(sd->trade.partner);
	if(target_sd && target_sd->bl.prev) {
		if (sd->bl.m != target_sd->bl.m || unit_distance(&sd->bl, &target_sd->bl) > 2) {
			trade_tradecancel(sd);
			return;
		}
		sd->state.deal_locked = 1;
		clif_tradeitemok(sd,0,0);
		clif_tradedeal_lock(sd,0);
		clif_tradedeal_lock(target_sd,1);
	} else {
		trade_tradecancel(sd);
	}

	return;
}

/*==========================================
 * 取引キャンセル
 *------------------------------------------
 */
void trade_tradecancel(struct map_session_data *sd)
{
	struct map_session_data *target_sd;
	int trade_i;

	nullpo_retv(sd);

	target_sd = map_id2sd(sd->trade.partner);
	if(target_sd && target_sd->bl.prev) {
		for(trade_i = 0; trade_i < MAX_DEAL_ITEMS; trade_i++) { //give items back (only virtual)
			if(target_sd->trade.item_amount[trade_i] != 0) {
				clif_additem(target_sd,target_sd->trade.item_index[trade_i]-2,target_sd->trade.item_amount[trade_i],0);
				target_sd->trade.item_index[trade_i]  = 0;
				target_sd->trade.item_amount[trade_i] = 0;
			}
		}
		if(target_sd->trade.zeny) {
			clif_updatestatus(target_sd,SP_ZENY);
			target_sd->trade.zeny = 0;
		}
		target_sd->state.deal_locked = 0;
		target_sd->state.deal_mode   = 0;
		target_sd->trade.partner     = 0;
		clif_tradecancelled(target_sd);
	}

	for(trade_i = 0; trade_i < MAX_DEAL_ITEMS; trade_i++) { //give items back (only virtual)
		if (sd->trade.item_amount[trade_i] != 0) {
			clif_additem(sd, sd->trade.item_index[trade_i]-2, sd->trade.item_amount[trade_i], 0);
			sd->trade.item_index[trade_i]  = 0;
			sd->trade.item_amount[trade_i] = 0;
		}
	}
	if (sd->trade.zeny) {
		clif_updatestatus(sd, SP_ZENY);
		sd->trade.zeny = 0;
	}
	sd->state.deal_locked = 0;
	sd->state.deal_mode   = 0;
	sd->trade.partner     = 0;
	clif_tradecancelled(sd);

	return;
}

/*==========================================
 * Check here if we can add items in inventories (against full inventory)
 *------------------------------------------
 */
static int trade_check(struct map_session_data *sd, struct map_session_data *target_sd)
{
	struct item inventory[MAX_INVENTORY];
	struct item inventory2[MAX_INVENTORY];
	struct item_data *data;
	int trade_i, i, amount, idx;

	nullpo_retr(0, sd);
	nullpo_retr(0, target_sd);

	// get inventory of players
	memcpy(&inventory, &sd->status.inventory, sizeof(struct item) * MAX_INVENTORY);
	memcpy(&inventory2, &target_sd->status.inventory, sizeof(struct item) * MAX_INVENTORY);

	// check free slots in both inventories
	for(trade_i = 0; trade_i < MAX_DEAL_ITEMS; trade_i++) {
		amount = sd->trade.item_amount[trade_i];
		if (amount > 0) {
			idx = sd->trade.item_index[trade_i] - 2;
			if (itemdb_isdropable(inventory[idx].nameid)) {
				// check quantity
				if (amount > inventory[idx].amount) // player changes its inventory before to commit
					return 0;
				if (amount > 0) {
					// search if it's possible to add item (for full inventory)
					data = itemdb_search(inventory[idx].nameid);
					i = MAX_INVENTORY;
					// check for non-equipement items
					if (!itemdb_isequip2(data)) {
						for(i = 0; i < MAX_INVENTORY; i++)
							if (inventory2[i].nameid == inventory[idx].nameid &&
								inventory2[i].card[0] == inventory[idx].card[0] && inventory2[i].card[1] == inventory[idx].card[1] &&
								inventory2[i].card[2] == inventory[idx].card[2] && inventory2[i].card[3] == inventory[idx].card[3]) {
								if (inventory2[i].amount + amount > MAX_AMOUNT)
									return 0;
								inventory2[i].amount += amount;
								inventory[idx].amount -= amount;
								if (inventory[idx].amount <= 0)
									memset(&inventory[idx], 0, sizeof(struct item));
								break;
							}
					}
					// check for equipement
					if (i == MAX_INVENTORY) {
						for(i = 0; i < MAX_INVENTORY; i++) {
							if (inventory2[i].nameid == 0) {
								memcpy(&inventory2[i], &inventory[idx], sizeof(struct item));
								inventory2[i].amount = amount;
								inventory[idx].amount -= amount;
								if (inventory[idx].amount <= 0)
									memset(&inventory[idx], 0, sizeof(struct item));
								break;
							}
						}
						if (i == MAX_INVENTORY)
							return 0;
					}
				}
			}
		}
		amount = target_sd->trade.item_amount[trade_i];
		if (amount > 0) {
			idx = target_sd->trade.item_index[trade_i] - 2;
			if (itemdb_isdropable(inventory2[idx].nameid)) {
				// check quantity
				if (amount > inventory2[idx].amount) // player changes its inventory before to commit
					return 0;
				if (amount > 0) {
					// search if it's possible to add item (for full inventory)
					data = itemdb_search(inventory2[idx].nameid);
					i = MAX_INVENTORY;
					// check for non-equipement items
					if (!itemdb_isequip2(data)) {
						for(i = 0; i < MAX_INVENTORY; i++)
							if (inventory[i].nameid == inventory2[idx].nameid &&
								inventory[i].card[0] == inventory2[idx].card[0] && inventory[i].card[1] == inventory2[idx].card[1] &&
								inventory[i].card[2] == inventory2[idx].card[2] && inventory[i].card[3] == inventory2[idx].card[3]) {
								if (inventory[i].amount + amount > MAX_AMOUNT)
									return 0;
								inventory[i].amount += amount;
								inventory2[idx].amount -= amount;
								if (inventory2[idx].amount <= 0)
									memset(&inventory2[idx], 0, sizeof(struct item));
								break;
							}
					}
					// check for equipement
					if (i == MAX_INVENTORY) {
						for(i = 0; i < MAX_INVENTORY; i++) {
							if (inventory[i].nameid == 0) {
								memcpy(&inventory[i], &inventory2[idx], sizeof(struct item));
								inventory[i].amount = amount;
								inventory2[idx].amount -= amount;
								if (inventory2[idx].amount <= 0)
									memset(&inventory2[idx], 0, sizeof(struct item));
								break;
							}
						}
						if (i == MAX_INVENTORY)
							return 0;
					}
				}
			}
		}
	}

	return 1;
}

/*==========================================
 * 取引許諾(trade押し)
 *------------------------------------------
 */
void trade_tradecommit(struct map_session_data *sd)
{
	struct map_session_data *target_sd;

	nullpo_retv(sd);

	target_sd = map_id2sd(sd->trade.partner);
	if(target_sd && target_sd->bl.prev) {
		if (sd->state.deal_locked >= 1 && target_sd->state.deal_locked >= 1) { // both have pressed 'ok'
			if (sd->state.deal_locked < 2) // set locked to 2
				sd->state.deal_locked = 2;
			if(target_sd->state.deal_locked == 2) { // the other one pressed 'trade' too
				int trade_i, idx, flag;

				// checks quantity of items
				if (!trade_check(sd, target_sd)) { // this function do like the real trade, but with virtual inventories
					trade_tradecancel(sd);
					return;
				}
				// check zenys
				if (sd->trade.zeny > sd->status.zeny ||
				    target_sd->trade.zeny > target_sd->status.zeny ||
				    sd->status.zeny - sd->trade.zeny + target_sd->trade.zeny > MAX_ZENY ||
				    target_sd->status.zeny - target_sd->trade.zeny + sd->trade.zeny > MAX_ZENY) {
					trade_tradecancel(sd);
					return;
				}
				// do trade
				// ---- of items
				for(trade_i = 0; trade_i < MAX_DEAL_ITEMS; trade_i++) {
					if(sd->trade.item_amount[trade_i] != 0) {
						idx = sd->trade.item_index[trade_i] - 2;
						if (itemdb_isdropable(sd->status.inventory[idx].nameid)) {
							flag = pc_additem(target_sd, &sd->status.inventory[idx], sd->trade.item_amount[trade_i]);
							if(flag==0)
								pc_delitem(sd, idx, sd->trade.item_amount[trade_i], 1, 0);
							else
								clif_additem(sd, idx, sd->trade.item_amount[trade_i], 0);
						}
						sd->trade.item_amount[trade_i] = 0;
					}
					sd->trade.item_index[trade_i] = 0;
					if(target_sd->trade.item_amount[trade_i] != 0) {
						idx = target_sd->trade.item_index[trade_i] - 2;
						if (itemdb_isdropable(target_sd->status.inventory[idx].nameid)) {
							flag = pc_additem(sd, &target_sd->status.inventory[idx], target_sd->trade.item_amount[trade_i]);
							if(flag==0)
								pc_delitem(target_sd, idx, target_sd->trade.item_amount[trade_i], 1, 0);
							else
								clif_additem(target_sd, idx, target_sd->trade.item_amount[trade_i], 0);
						}
						target_sd->trade.item_amount[trade_i] = 0;
					}
					target_sd->trade.item_index[trade_i] = 0;
				}
				// ---- of zenys
				if(sd->trade.zeny || target_sd->trade.zeny) {
					sd->status.zeny = sd->status.zeny - sd->trade.zeny + target_sd->trade.zeny;
					target_sd->status.zeny = target_sd->status.zeny - target_sd->trade.zeny + sd->trade.zeny;
					clif_updatestatus(sd, SP_ZENY);
					clif_updatestatus(target_sd, SP_ZENY);
				}
				sd->trade.zeny = 0;
				target_sd->trade.zeny = 0;
				// clean up variables
				sd->state.deal_locked = 0;
				sd->state.deal_mode   = 0;
				sd->trade.partner     = 0;
				target_sd->state.deal_locked = 0;
				target_sd->state.deal_mode   = 0;
				target_sd->trade.partner     = 0;
				clif_tradecompleted(sd,0);
				clif_tradecompleted(target_sd,0);
				// save both player to avoid crash: they always have no advantage/disadvantage between the 2 players
				chrif_save(sd,0);
				chrif_save(target_sd,0);
			}
		}
	} else {
		trade_tradecancel(sd);
	}

	return;
}
