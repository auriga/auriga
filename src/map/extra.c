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
#include <time.h>

#include "timer.h"
#include "nullpo.h"
#include "malloc.h"
#include "lock.h"
#include "utils.h"

#include "map.h"
#include "extra.h"
#include "battle.h"
#include "pc.h"
#include "itemdb.h"
#include "msg.h"
#include "clif.h"
#include "intif.h"

static char extra_file_txt[1024] = "save/map_extra.txt"; // managed by software - must not be modified manually
static int extra_num = 0;

static struct extra {
	int item_id; // -1: zeny, other: id item
	int quantity; // quantity of items or zeny
	char name[24]; // player name
} *extra_dat = NULL;


/*==========================================
 * extra system
 *------------------------------------------
 */
static int extra_timer(int tid, unsigned int tick, int id, void *data)
{
	FILE *fp;
	static int extra_file_readed = 0;
	int change_flag = 0; // must we rewrite extra file? (0: no, 1: yes)
	int lock, i;
	char line[1024], name[1024];
	int item_id, quantity;
	struct map_session_data *pl_sd;
	struct item_data *item_data;

	// do we use extra system?
	if (!battle_config.extra_system_flag)
		return 0;

	// if extra file not read, read it at first
	if (extra_file_readed == 0) {
		extra_file_readed = 1; // file readed.
		if ((fp = fopen(extra_file_txt, "r")) != NULL) {
			while(fgets(line, sizeof(line) - 1, fp) != NULL) {
				if ((line[0] == '/' && line[1] == '/') || line[0] == '\0' || line[0] == '\n' || line[0] == '\r')
					continue;
				// if line is valid
				if ((sscanf(line, "%d,%d,%1023[^\r\n]", &item_id, &quantity, name) == 3 ||
				    sscanf(line, "%d\t%d\t%1023[^\r\n]", &item_id, &quantity, name) == 3) &&
				    (item_id == -1 || (itemdb_exists(item_id) && (!battle_config.item_check || itemdb_available(item_id)))) && // zeny or valid items
				    quantity != 0 && // quantity
				    strlen(name) >= 4 && strlen(name) < 24) { // name
					// manage max quantity
					if (item_id == -1) {
						if (quantity > MAX_ZENY) {
							quantity = MAX_ZENY;
							// Invalid quantity -> file must be rewriten
							change_flag = 1;
						} else if (quantity < -(MAX_ZENY)) {
							quantity = -(MAX_ZENY);
							// Invalid quantity -> file must be rewriten
							change_flag = 1;
						}
					} else {
						if (quantity > MAX_AMOUNT) {
							quantity = MAX_AMOUNT;
							// Invalid quantity -> file must be rewriten
							change_flag = 1;
						} else if (quantity < -(MAX_AMOUNT)) {
							quantity = -(MAX_AMOUNT);
							// Invalid quantity -> file must be rewriten
							change_flag = 1;
						}
					}
					// add an index
					if (extra_num == 0) {
						extra_dat = (struct extra*)aCalloc(1, sizeof(struct extra));
					} else {
						extra_dat = (struct extra*)aRealloc(extra_dat, sizeof(struct extra) * (extra_num + 1));
						memset(&extra_dat[extra_num], 0, sizeof(struct extra));
					}
					extra_dat[extra_num].item_id = item_id;
					extra_dat[extra_num].quantity = quantity;
					strncpy(extra_dat[extra_num].name, name, 24);
					extra_num++;
				} else { // Invalid line -> file must be rewriten
					change_flag = 1;
				}
			}
			fclose(fp);
		} else {
			// file doesn't exist. Create it for explanation -> file must be rewriten
			change_flag = 1;
		}
	}

	// if extra_add_file can be readed and exists
	if ((fp = fopen(extra_add_file_txt, "r")) != NULL) {
		while(fgets(line, sizeof(line) - 1, fp) != NULL) {
			if ((line[0] == '/' && line[1] == '/') || line[0] == '\0' || line[0] == '\n' || line[0] == '\r')
				continue;
			// if line is valid
			if ((sscanf(line, "%d,%d,%1023[^\r\n]", &item_id, &quantity, name) == 3 ||
			    sscanf(line, "%d\t%d\t%1023[^\r\n]", &item_id, &quantity, name) == 3) &&
			    (item_id == -1 || (itemdb_exists(item_id) && (!battle_config.item_check || itemdb_available(item_id)))) && // zeny or valid items
			    quantity != 0 && // quantity
			    strlen(name) >= 4 && strlen(name) < 24) { // name
				// manage max quantity
				if (item_id == -1) {
					if (quantity > MAX_ZENY)
						quantity = MAX_ZENY;
					else if (quantity < -(MAX_ZENY))
						quantity = -(MAX_ZENY);
				} else {
					if (quantity > MAX_AMOUNT)
						quantity = MAX_AMOUNT;
					else if (quantity < -(MAX_AMOUNT))
						quantity = -(MAX_AMOUNT);
				}
				// add an index
				if (extra_num == 0) {
					extra_dat = (struct extra*)aCalloc(1, sizeof(struct extra));
				} else {
					extra_dat = (struct extra*)aRealloc(extra_dat, sizeof(struct extra) * (extra_num + 1));
					memset(&extra_dat[extra_num], 0, sizeof(struct extra));
				}
				extra_dat[extra_num].item_id = item_id;
				extra_dat[extra_num].quantity = quantity;
				strncpy(extra_dat[extra_num].name, name, 24);
				extra_num++;
				// new line -> files must be rewriten
				change_flag = 1;
			}
		}
		fclose(fp);
		// erase file
		remove(extra_add_file_txt);
	}

	// check players to give zenys or items
	for (i = 0; i < extra_num; i++) {
		if ((pl_sd = map_nick2sd(extra_dat[i].name)) != NULL) {
			item_id = extra_dat[i].item_id;
			quantity = extra_dat[i].quantity;

			// work on zenys
			if (item_id == -1) {
				// substract
				if (quantity < 0) {
					if (pl_sd->status.zeny < -quantity)
						quantity = -pl_sd->status.zeny;
					if (quantity < 0) {
						msg_output(pl_sd->fd, msg_txt(149), -quantity); // Server (special action): you lost %ld zenys.
						pl_sd->status.zeny += quantity;
						clif_updatestatus(pl_sd, SP_ZENY);
						// line changed -> file must be rewriten
						extra_dat[i].quantity -= quantity;
						change_flag = 1;
					}
				// add
				} else {
					if (quantity > MAX_ZENY - pl_sd->status.zeny)
						quantity = MAX_ZENY - pl_sd->status.zeny;
					if (quantity > 0) {
						msg_output(pl_sd->fd, msg_txt(150), quantity); // Server (special action): you gain %ld zenys.
						pl_sd->status.zeny += quantity;
						clif_updatestatus(pl_sd, SP_ZENY);
						// line changed -> file must be rewriten
						extra_dat[i].quantity -= quantity;
						change_flag = 1;
					}
				}

			// items -> check against item_id, because database can be reloaded.
			} else if ((item_data = itemdb_exists(item_id)) && (!battle_config.item_check || itemdb_available(item_id))) {
				int j;
				if (quantity < 0) { // remove items
					for (j = 0; j < MAX_INVENTORY; j++) {
						if (pl_sd->status.inventory[j].nameid == item_id && pl_sd->status.inventory[j].equip == LOC_NOTHING) {
							if (pl_sd->status.inventory[j].amount < -quantity)
								quantity = -pl_sd->status.inventory[j].amount;
							if (quantity < 0) {
								if (pl_sd->status.inventory[i].card[0] == (short)0xff00)
									intif_delete_petdata(*((int *)(&pl_sd->status.inventory[i].card[1])));
								pc_delitem(pl_sd, j, -quantity, 0, 0);
								msg_output(pl_sd->fd, msg_txt(151), -quantity, item_data->jname); // Server (special action): you lost %ld %s.
								// line changed -> file must be rewriten
								extra_dat[i].quantity -= quantity;
								quantity = extra_dat[i].quantity; // to continue loop
								change_flag = 1;
							}
						}
					}
				} else { // add items
					int loop;
					struct item item_tmp;
					if (item_data->weight * quantity > pl_sd->max_weight - pl_sd->weight) {
						quantity = (pl_sd->max_weight - pl_sd->weight) / item_data->weight;
						if (quantity <= 0)
							continue;
					}
					loop = 1;
					if (itemdb_isarmor(item_data->nameid) || itemdb_isweapon(item_data->nameid) ||
					    item_data->flag.pet_egg || item_data->flag.pet_acce) {
						loop = quantity;
						quantity = 1;
					}
					for(j = 0; j < loop; j++) {
						memset(&item_tmp, 0, sizeof(item_tmp));
						item_tmp.nameid = item_id;
						item_tmp.identify = 1;
						if (pc_additem(pl_sd, &item_tmp, quantity) == 0) { // item added
							msg_output(pl_sd->fd, msg_txt(152), quantity, item_data->jname); // Server (special action): you obtain %ld %s.
							// line changed -> file must be rewriten
							extra_dat[i].quantity -= quantity;
							change_flag = 1;
						}
					}
				}

			} else {
				// invalid item_id -> file must be rewriten
				extra_dat[i].quantity = 0;
				change_flag = 1;
			}
		}
	}

	// If file changed?
	if (change_flag) {
		// remove void lines
		for (i = 0; i < extra_num; i++) {
			if (extra_dat[i].quantity == 0) {
				if (extra_num == 1) {
					aFree(extra_dat);
					extra_dat = NULL;
					extra_num--;
				} else {
					if (i != (extra_num - 1))
						memcpy(&extra_dat[i], &extra_dat[extra_num - 1], sizeof(struct extra));
					extra_num--;
					extra_dat = (struct extra*)aRealloc(extra_dat, sizeof(struct extra) * extra_num);
				}
				i--; // redo same index
			}
		}
		// write file
		if ((fp = lock_fopen(extra_file_txt, &lock)) != NULL) {
			fprintf(fp, "// このファイルの内容は変更しないでください！" NEWLINE
			            "// MAPサーバによって自動的に管理されています" NEWLINE
			            "// 追加したい場合は「%s」を利用してください" NEWLINE
			            "//" NEWLINE, extra_add_file_txt);
			for (i = 0; i < extra_num; i++)
				fprintf(fp,"%d,%d,%s" NEWLINE, extra_dat[i].item_id, extra_dat[i].quantity, extra_dat[i].name);
			lock_fclose(fp, extra_file_txt, &lock);
		}
	}

	return 0;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
int do_final_extra(void)
{
	if (extra_num > 0) {
		aFree(extra_dat);
		extra_dat = NULL;
		extra_num = 0;
	}

	return 0;
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
int do_init_extra(void)
{
	if(extra_check_interval > 0) {
		add_timer_func_list(extra_timer);
		add_timer_interval(gettick() + 10000, extra_timer, 0, NULL, extra_check_interval);

		printf("enable extra system, cheking file [%s] and [%s].\n", extra_file_txt, extra_add_file_txt);
	}

	return 0;
}
