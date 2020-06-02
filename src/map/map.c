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

// $Id: map.c,v 1.3 2004/09/15 00:20:52 running_pinata Exp $

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/stat.h>

#include "core.h"
#include "timer.h"
#include "db.h"
#include "grfio.h"
#include "nullpo.h"
#include "malloc.h"
#include "version.h"
#include "httpd.h"
#include "graph.h"
#include "socket.h"
#include "utils.h"
#include "sqldbs.h"

#include "map.h"
#include "path.h"
#include "msg.h"
#include "chrif.h"
#include "clif.h"
#include "intif.h"
#include "npc.h"
#include "pc.h"
#include "bonus.h"
#include "mob.h"
#include "chat.h"
#include "itemdb.h"
#include "storage.h"
#include "skill.h"
#include "trade.h"
#include "party.h"
#include "battle.h"
#include "script.h"
#include "guild.h"
#include "pet.h"
#include "atcommand.h"
#include "status.h"
#include "friend.h"
#include "unit.h"
#include "homun.h"
#include "ranking.h"
#include "merc.h"
#include "quest.h"
#include "booking.h"
#include "achieve.h"
#include "elem.h"
#include "memorial.h"
#include "extra.h"
#include "luascript.h"

// 極力 staticでローカルに収める
static struct dbt *id_db        = NULL;
static struct dbt *map_db       = NULL;
static struct dbt *nick_db      = NULL;
static struct dbt *charid_db    = NULL;
static struct dbt *freeblock_db = NULL;

static int users;
static struct block_list *object[MAX_FLOORITEM];

static int block_free_lock = 0;

#define BLOCK_LIST_MAX (256*1024)
static struct block_list *bl_list[BLOCK_LIST_MAX];
static int bl_list_count = 0;

static struct delay_item_drop2 *delayitem_head = NULL, *delayitem_tail = NULL;

struct map_data *map = NULL;
int map_num = 0;
static int map_max = 0;
static int map_mdmap_start = 0;

int autosave_interval = DEFAULT_AUTOSAVE_INTERVAL;
int autosave_gvg_rate = 100;
int extra_check_interval = 60;
int agit_flag = 0;
static int map_pk_server_flag = 0;
static int map_pk_nightmaredrop_flag = 0;
static int map_pk_noteleport_flag = 0;

extern int packet_parse_time;

// マップキャッシュ利用フラグ(map_athana.conf内のread_map_from_cacheで指定)
// 0:利用しない 1:非圧縮保存 2:圧縮保存
static int map_read_flag = 0;

char map_conf_filename[256]       = "conf/map_auriga.conf";
char battle_conf_filename[256]    = "conf/battle_auriga.conf";
char atcommand_conf_filename[256] = "conf/atcommand_auriga.conf";
char script_conf_filename[256]    = "conf/script_auriga.conf";
char msg_conf_filename[256]       = "conf/msg_auriga.conf";
char luascript_conf_filename[256] = "conf/lua_auriga.conf";

char map_server_tag[MAPSERVER_TAGNAME] = "map01";	// マップサーバタグ名
char motd_txt[256]           = "conf/motd.txt";
char help_txt[256]           = "conf/help.txt";
char extra_add_file_txt[256] = "map_extra_add.txt"; // to add items from external software (use append to add a line)

static char map_cache_file[256]   = "map.info";	// マップキャッシュファイル名
static char grf_path_txt[256]     = "conf/grf-files.txt";
static char water_height_txt[256] = "conf/water_height.txt";

/*==========================================
 * 全map鯖総計での接続数設定
 * (char鯖から送られてくる)
 *------------------------------------------
 */
void map_setusers(int n)
{
	users = n;
}

/*==========================================
 * 全map鯖総計での接続数取得 (/wへの応答用)
 *------------------------------------------
 */
int map_getusers(void)
{
	return users;
}

//
// block削除の安全性確保処理
//

/*==========================================
 * blockをfreeするときfreeの変わりに呼ぶ
 * ロックされているときはバッファにためる
 *------------------------------------------
 */
int map_freeblock(void *bl)
{
	if(block_free_lock == 0) {
		aFree(bl);
		bl = NULL;
	} else {
		numdb_insert(freeblock_db, bl, bl);
	}

	return block_free_lock;
}

/*==========================================
 * blockのfreeを一時的に禁止する
 *------------------------------------------
 */
int map_freeblock_lock(void)
{
	return ++block_free_lock;
}

/*==========================================
 * blockのfreeのロックを解除する
 * このとき、ロックが完全になくなると
 * バッファにたまっていたblockを全部削除
 *------------------------------------------
 */
static int freeblock_db_final(void *key, void *data, va_list ap)
{
	aFree(data);
	return 0;
}

int map_freeblock_unlock(void)
{
	if((--block_free_lock) == 0) {
		numdb_clear(freeblock_db, freeblock_db_final);
	} else if(block_free_lock < 0) {
		if(battle_config.error_log)
			printf("map_freeblock_unlock: lock count < 0 !\n");
		block_free_lock = 0;	// 次回以降のロックに支障が出てくるのでリセット
	}
	return block_free_lock;
}

/*==========================================
 * 定期的にblock_free_lockをリセット
 *------------------------------------------
 */
static int map_freeblock_timer(int tid,unsigned int tick,int id,void *data)
{
	if(block_free_lock > 0) {
		printf("map_freeblock_timer: block_free_lock(%d) is invalid.\n",block_free_lock);
		block_free_lock = 1;
		map_freeblock_unlock();
	}
	return 0;
}

//
// block化処理
//

/*==========================================
 * map[]のblock_listから繋がっている場合に
 * bl->prevにbl_headのアドレスを入れておく
 *------------------------------------------
 */
static struct block_list bl_head;

/*==========================================
 * map[]のblock_listに追加
 * mobは数が多いので別リスト
 *
 * 既にlink済みかの確認が無い。危険かも
 *------------------------------------------
 */
int map_addblock(struct block_list *bl)
{
	int m, x, y;
	int b;

	nullpo_retr(0, bl);

	if(bl->prev != NULL) {
		if(battle_config.error_log)
			printf("map_addblock error : bl->prev!=NULL\n");
		return 0;
	}

	m = bl->m;
	x = bl->x;
	y = bl->y;
	if(m < 0 || m >= map_num ||
	   x < 0 || x >= map[m].xs ||
	   y < 0 || y >= map[m].ys)
		return 1;

	b = x / BLOCK_SIZE + (y / BLOCK_SIZE) * map[m].bxs;

	if(bl->type == BL_MOB) {
		bl->next = map[m].block_mob[b];
		bl->prev = &bl_head;
		if(bl->next)
			bl->next->prev = bl;
		map[m].block_mob[b] = bl;
	} else {
		bl->next = map[m].block[b];
		bl->prev = &bl_head;
		if(bl->next)
			bl->next->prev = bl;
		map[m].block[b] = bl;
		if(bl->type == BL_PC)
			map[m].users++;
	}

	return 0;
}

/*==========================================
 * map[]のblock_listから外す
 * prevがNULLの場合listに繋がってない
 *------------------------------------------
 */
int map_delblock(struct block_list *bl)
{
	int b;

	nullpo_retr(0, bl);

	// 既にblocklistから抜けている
	if(bl->prev == NULL) {
		if(bl->next != NULL) {
			// prevがNULLでnextがNULLでないのは有ってはならない
			if(battle_config.error_log)
				printf("map_delblock error : bl->next!=NULL\n");
		}
		return 0;
	}

	b = bl->x / BLOCK_SIZE + (bl->y / BLOCK_SIZE) * map[bl->m].bxs;

	if(bl->type == BL_PC)
		map[bl->m].users--;
	if(bl->next)
		bl->next->prev = bl->prev;

	if(bl->prev == &bl_head) {
		// リストの頭なので、map[]のblock_listを更新する
		if(bl->type == BL_MOB) {
			map[bl->m].block_mob[b] = bl->next;
		} else {
			map[bl->m].block[b] = bl->next;
		}
	} else {
		bl->prev->next = bl->next;
	}
	bl->next = NULL;
	bl->prev = NULL;

	return 0;
}

/*==========================================
 * 周囲のPC人数を数える (現在未使用)
 *------------------------------------------
 */
/*
int map_countnearpc(int m,int x,int y)
{
	int bx, by, c = 0;
	struct block_list *bl;

	if(map[m].users == 0)
		return 0;

	by = y / BLOCK_SIZE - AREA_SIZE / BLOCK_SIZE - 1;
	for( ; by <= y / BLOCK_SIZE + AREA_SIZE / BLOCK_SIZE + 1; by++) {
		if(by < 0 || by >= map[m].bys)
			continue;
		bx = x / BLOCK_SIZE - AREA_SIZE / BLOCK_SIZE - 1;
		for( ; bx <= x / BLOCK_SIZE + AREA_SIZE / BLOCK_SIZE + 1; bx++) {
			if(bx < 0 || bx >= map[m].bxs)
				continue;
			bl = map[m].block[bx+by*map[m].bxs];
			for( ; bl; bl = bl->next) {
				if(bl->type == BL_PC)
					c++;
			}
		}
	}
	return c;
}*/

/*==========================================
 * セル上のPCとMOBの数を数える (汎用)
 *------------------------------------------
 */
int map_count_oncell(int m,int x,int y,int type)
{
	int bx, by;
	struct block_list *bl;
	int count = 0;

	if(x < 0 || y < 0 || x >= map[m].xs || y >= map[m].ys)
		return 1;

	bx = x / BLOCK_SIZE;
	by = y / BLOCK_SIZE;

	if(type & ~BL_MOB) {
		bl = map[m].block[bx+by*map[m].bxs];
		for( ; bl; bl = bl->next) {
			if((bl->type & type) && bl->x == x && bl->y == y)
				count++;
		}
	}
	if(type & BL_MOB) {
		bl = map[m].block_mob[bx+by*map[m].bxs];
		for( ; bl; bl = bl->next) {
			if(bl->x == x && bl->y == y)
				count++;
		}
	}
	return count;
}

/*==========================================
 * セル上の最初に見つけたスキルユニットを返す
 *   out_unit: 検索対象外とするユニット
 *------------------------------------------
 */
struct skill_unit *map_find_skill_unit_oncell(struct block_list *target,int x,int y,int skill_id,struct skill_unit *out_unit)
{
	int m, bx, by;
	struct block_list *bl;
	struct skill_unit *unit;

	nullpo_retr(0, target);

	m = target->m;

	if(x < 0 || y < 0 || x >= map[m].xs || y >= map[m].ys)
		return NULL;

	bx = x / BLOCK_SIZE;
	by = y / BLOCK_SIZE;

	bl = map[m].block[bx+by*map[m].bxs];
	for( ; bl; bl = bl->next) {
		if(bl->type != BL_SKILL || bl->x != x || bl->y != y)
			continue;
		unit = (struct skill_unit *)bl;
		if(unit == out_unit || !unit->alive || !unit->group || unit->group->skill_id != skill_id)
			continue;
		if(battle_check_target(&unit->bl,target,unit->group->target_flag) > 0)
			return unit;
	}
	return NULL;
}

/*==========================================
 * map m (x0,y0)-(x1,y1)内の全objに対して
 * funcを呼ぶ
 * type!=0 ならその種類のみ
 *------------------------------------------
 */
static int map_foreachinarea_sub(int (*func)(struct block_list*,va_list),int m,int x0,int y0,int x1,int y1,int type,va_list ap)
{
	int bx, by;
	struct block_list *bl;
	int i, blockcount = bl_list_count;
	int ret = 0;

	if(x0 < 0) x0 = 0;
	if(y0 < 0) y0 = 0;
	if(x1 >= map[m].xs) x1 = map[m].xs-1;
	if(y1 >= map[m].ys) y1 = map[m].ys-1;

	if(type & ~BL_MOB) {
		for(by = y0 / BLOCK_SIZE; by <= y1 / BLOCK_SIZE; by++) {
			for(bx = x0 / BLOCK_SIZE; bx <= x1 / BLOCK_SIZE; bx++) {
				bl = map[m].block[bx+by*map[m].bxs];
				for( ; bl; bl = bl->next) {
					if((bl->type & type) && bl->x >= x0 && bl->x <= x1 && bl->y >= y0 && bl->y <= y1) {
						if(bl_list_count >= BLOCK_LIST_MAX)
							break;
						bl_list[bl_list_count++] = bl;
					}
				}
			}
		}
	}
	if(type & BL_MOB) {
		for(by = y0 / BLOCK_SIZE; by <= y1 / BLOCK_SIZE; by++) {
			for(bx = x0 / BLOCK_SIZE; bx <= x1 / BLOCK_SIZE; bx++) {
				bl = map[m].block_mob[bx+by*map[m].bxs];
				for( ; bl; bl = bl->next) {
					if(bl->x >= x0 && bl->x <= x1 && bl->y >= y0 && bl->y <= y1) {
						if(bl_list_count >= BLOCK_LIST_MAX)
							break;
						bl_list[bl_list_count++] = bl;
					}
				}
			}
		}
	}

	if(bl_list_count >= BLOCK_LIST_MAX) {
		if(battle_config.error_log)
			printf("map_foreachinarea: *WARNING* block count too many!\n");
	}

	map_freeblock_lock();	// メモリからの解放を禁止する

	for(i = blockcount; i < bl_list_count; i++) {
		if(bl_list[i]->prev) {	// 有効かどうかチェック
			va_list apcopy;
			va_copy(apcopy, ap);
			ret += func(bl_list[i],apcopy);
			va_end(apcopy);
		}
	}

	map_freeblock_unlock();	// 解放を許可する

	bl_list_count = blockcount;

	return ret;
}

int map_foreachinarea(int (*func)(struct block_list*,va_list),int m,int x0,int y0,int x1,int y1,int type,...)
{
	int ret;
	va_list ap;

	if(m < 0) {
		printf("map_foreachinarea: invalid map index!! func = 0x%p\n", func);
		return 0;
	}

	va_start(ap,type);
	ret = map_foreachinarea_sub(func, m, x0, y0, x1, y1, type, ap);
	va_end(ap);

	return ret;
}

/*==========================================
 * (x0,y0)からdx,dy方向へ射線の通る範囲
 * (矩形か斜方五角形)内のobjに対してfuncを呼ぶ
 *
 * dx,dyは-1,0,1のみとする
 *------------------------------------------
 */
#define swap(x,y) { int t; t = x; x = y; y = t; }

int map_foreachinshootpath(int (*func)(struct block_list*,va_list),
	int m,int x0,int y0,int dx,int dy,int range,int width,int type,...)
{
	int x1, y1, x2, y2, x3, y3, bx, by;
	int i, blockcount = bl_list_count;
	int ret = 0;
	struct block_list *bl;

	x1 = x0;
	y1 = y0;

	if(dx == 0 || dy == 0) {
		// 矩形領域の場合
		// map_foreachinarea + path_search_long

		// 射線上に壁があるかチェック、壁のセルは射程に含まない
		for(i = 0; i < range; i++) {
			if(map_getcell(m,x1+dx,y1+dy,CELL_CHKWALL))
				break;
			x1 += dx;
			y1 += dy;
		}

		if(dx == 0) {
			x2 = x0 - width;
			y2 = y0;
			x3 = x1 + width;
			y3 = y1;
		} else {
			x2 = x0;
			y2 = y0 - width;
			x3 = x1;
			y3 = y1 + width;
		}

		if(x2 > x3) {
			swap(x2,x3);
		}
		if(y2 > y3) {
			swap(y2,y3);
		}
		if(x2 < 0) x2 = 0;
		if(y2 < 0) y2 = 0;
		if(x3 >= map[m].xs) x3 = map[m].xs-1;
		if(y3 >= map[m].ys) y3 = map[m].ys-1;

		if(type & ~BL_MOB) {
			for(by = y2 / BLOCK_SIZE; by <= y3 / BLOCK_SIZE; by++) {
				for(bx = x2 / BLOCK_SIZE; bx <= x3 / BLOCK_SIZE; bx++) {
					bl = map[m].block[bx+by*map[m].bxs];
					for( ; bl; bl = bl->next) {
						if((bl->type & type) && bl->x >= x2 && bl->x <= x3 && bl->y >= y2 && bl->y <= y3 &&
						   path_search_long(NULL,m,x0,y0,bl->x,bl->y))
						{
							if(bl_list_count >= BLOCK_LIST_MAX)
								break;
							bl_list[bl_list_count++] = bl;
						}
					}
				}
			}
		}
		if(type & BL_MOB) {
			for(by = y2 / BLOCK_SIZE; by <= y3 / BLOCK_SIZE; by++) {
				for(bx = x2 / BLOCK_SIZE; bx <= x3 / BLOCK_SIZE; bx++) {
					bl = map[m].block_mob[bx+by*map[m].bxs];
					for( ; bl; bl = bl->next) {
						if(bl->x >= x2 && bl->x <= x3 && bl->y >= y2 && bl->y <= y3 &&
						   path_search_long(NULL,m,x0,y0,bl->x,bl->y))
						{
							if(bl_list_count >= BLOCK_LIST_MAX)
								break;
							bl_list[bl_list_count++] = bl;
						}
					}
				}
			}
		}
	} else {
		// 斜方五角形領域の場合
		// (x0,y0) を原点、射線方向のベクトルをxu軸、これに対する法線ベクトルをyu軸とした
		// 座標系に変換して領域チェックを行う
		// 対象オブジェクトの座標 (x,y) は平行移動と回転移動によって (xu,yu) に変換できる
		//   xu = (x-x0) * cos@ - (y-y0) * sin@
		//   yu = (x-x0) * sin@ + (y-y0) * cos@
		// xu軸がx軸に重なるまで回転して正規化する、例えばdx=1,dy=1なら @ = -45度
		// このときxuは距離（range）、yuは幅（width）に相当する
		// ただし浮動小数点演算を避けるため 1/sqrt(2) を座標単位としている

		int xu, yu;

		// 射線上に壁があるかチェック、壁のセルは射程に含む
		for(i = 0; i < range; i++) {
			if(map_getcell(m,x1,y1,CELL_CHKWALL))
				break;
			x1 += dx;
			y1 += dy;
		}

		x2 = x0 - dx * width;
		y2 = y0 - dy * width;
		x3 = x1 + dx * width;
		y3 = y1 + dy * width;

		if(x2 > x3) {
			swap(x2,x3);
		}
		if(y2 > y3) {
			swap(y2,y3);
		}
		if(x2 < 0) x2 = 0;
		if(y2 < 0) y2 = 0;
		if(x3 >= map[m].xs) x3 = map[m].xs-1;
		if(y3 >= map[m].ys) y3 = map[m].ys-1;

		if(type & ~BL_MOB) {
			for(by = y2 / BLOCK_SIZE; by <= y3 / BLOCK_SIZE; by++) {
				for(bx = x2 / BLOCK_SIZE; bx <= x3 / BLOCK_SIZE; bx++) {
					bl = map[m].block[bx+by*map[m].bxs];
					for( ; bl; bl = bl->next) {
						if(!(bl->type & type) || (bl->x - x1) * dx > 0 || (bl->y - y1) * dy > 0)
							continue;
						xu =  (bl->x - x0) * dx + (bl->y - y0) * dy;
						yu = -(bl->x - x0) * dy + (bl->y - y0) * dx;
						if(xu >= 0 && xu <= range*2 && abs(yu) <= width*2 &&
						   path_search_long(NULL,m,x0,y0,bl->x,bl->y))
						{
							if(bl_list_count >= BLOCK_LIST_MAX)
								break;
							bl_list[bl_list_count++] = bl;
						}
					}
				}
			}
		}
		if(type & BL_MOB) {
			for(by = y2 / BLOCK_SIZE; by <= y3 / BLOCK_SIZE; by++) {
				for(bx = x2 / BLOCK_SIZE; bx <= x3 / BLOCK_SIZE; bx++) {
					bl = map[m].block_mob[bx+by*map[m].bxs];
					for( ; bl; bl = bl->next) {
						if((bl->x - x1) * dx > 0 || (bl->y - y1) * dy > 0)
							continue;
						xu =  (bl->x - x0) * dx + (bl->y - y0) * dy;
						yu = -(bl->x - x0) * dy + (bl->y - y0) * dx;
						if(xu >= 0 && xu <= range*2 && abs(yu) <= width*2 &&
						   path_search_long(NULL,m,x0,y0,bl->x,bl->y))
						{
							if(bl_list_count >= BLOCK_LIST_MAX)
								break;
							bl_list[bl_list_count++] = bl;
						}
					}
				}
			}
		}
	}

	if(bl_list_count >= BLOCK_LIST_MAX) {
		if(battle_config.error_log)
			printf("map_foreachinpath: *WARNING* block count too many!\n");
	}

	map_freeblock_lock();	// メモリからの解放を禁止する

	for(i = blockcount; i < bl_list_count; i++) {
		if(bl_list[i]->prev) {	// 有効かどうかチェック
			va_list ap;
			va_start(ap, type);
			ret += func(bl_list[i],ap);
			va_end(ap);
		}
	}

	map_freeblock_unlock();	// 解放を許可する

	bl_list_count = blockcount;

	return ret;
}

/*==========================================
 * 矩形(x0,y0)-(x1,y1)が(dx,dy)移動した時の
 * 領域外になる領域(矩形かL字形)内のobjに
 * 対してfuncを呼ぶ
 *------------------------------------------
 */
int map_foreachinmovearea(int (*func)(struct block_list*,va_list),int m,int x0,int y0,int x1,int y1,int dx,int dy,int type,...)
{
	int bx, by, x2, y2, x3, y3;
	struct block_list *bl;
	int i, blockcount = bl_list_count;
	int ret = 0;

	if(dx == 0 || dy == 0) {
		// 矩形領域の場合
		if(dx == 0) {
			if(dy < 0) {
				y0 = y1 + dy + 1;
			} else {
				y1 = y0 + dy - 1;
			}
		} else if(dy == 0) {
			if(dx < 0) {
				x0 = x1 + dx + 1;
			} else {
				x1 = x0 + dx - 1;
			}
		}
		// if(x0 < 0) x0 = 0;
		// if(y0 < 0) y0 = 0;
		// if(x1 >= map[m].xs) x1 = map[m].xs-1;
		// if(y1 >= map[m].ys) y1 = map[m].ys-1;

		// ここで座標補正すると、map 隅のオブジェクトに対して関数が正しく機能しない。
		// (-10, 0) - (10, 10) が (10, 0) 移動した時範囲外になる領域と、補正後の
		// (  0, 0) - (10, 10) が (10, 0) 移動した時範囲外になる領域は別物になる。
		// 補正後は (0, 0) - (10, 10) にいるオブジェクトに対しても、この関数が
		// 呼び出されることになる。

		x2 = (x0 < 0) ? 0 : x0 / BLOCK_SIZE;
		y2 = (y0 < 0) ? 0 : y0 / BLOCK_SIZE;
		x3 = (x1 >= map[m].xs) ? map[m].bxs-1 : x1 / BLOCK_SIZE;
		y3 = (y1 >= map[m].ys) ? map[m].bys-1 : y1 / BLOCK_SIZE;

		if(type & ~BL_MOB) {
			for(by = y2; by <= y3; by++) {
				for(bx = x2; bx <= x3; bx++) {
					bl = map[m].block[bx+by*map[m].bxs];
					for( ; bl; bl = bl->next) {
						if((bl->type & type) && bl->x >= x0 && bl->x <= x1 && bl->y >= y0 && bl->y <= y1) {
							if(bl_list_count >= BLOCK_LIST_MAX)
								break;
							bl_list[bl_list_count++] = bl;
						}
					}
				}
			}
		}
		if(type & BL_MOB) {
			for(by = y2; by <= y3; by++) {
				for(bx = x2; bx <= x3; bx++) {
					bl = map[m].block_mob[bx+by*map[m].bxs];
					for( ; bl; bl = bl->next) {
						if(bl->x >= x0 && bl->x <= x1 && bl->y >= y0 && bl->y <= y1) {
							if(bl_list_count >= BLOCK_LIST_MAX)
								break;
							bl_list[bl_list_count++] = bl;
						}
					}
				}
			}
		}
	} else {
		// L字領域の場合

		// if(x0 < 0) x0 = 0;
		// if(y0 < 0) y0 = 0;
		// if(x1 >= map[m].xs) x1 = map[m].xs-1;
		// if(y1 >= map[m].ys) y1 = map[m].ys-1;

		// ここで座標補正すると、map 隅のオブジェクトに対して関数が正しく機能しない。
		// (-10, -10) - (10, 10) が (10, 10) 移動した時範囲外になる領域と、補正後の
		// (  0,   0) - (10, 10) が (10, 10) 移動した時範囲外になる領域は別物になる。
		// 補正後は (0, 0) - (10, 10) にいるオブジェクトに対しても、この関数が
		// 呼び出されることになる。

		x2 = (x0 < 0) ? 0 : x0 / BLOCK_SIZE;
		y2 = (y0 < 0) ? 0 : y0 / BLOCK_SIZE;
		x3 = (x1 >= map[m].xs) ? map[m].bxs-1 : x1 / BLOCK_SIZE;
		y3 = (y1 >= map[m].ys) ? map[m].bys-1 : y1 / BLOCK_SIZE;

		if(type & ~BL_MOB) {
			for(by = y2; by <= y3; by++) {
				for(bx = x2; bx <= x3; bx++) {
					bl = map[m].block[bx+by*map[m].bxs];
					for( ; bl; bl = bl->next) {
						if(!(bl->type & type) || !(bl->x >= x0 && bl->x <= x1 && bl->y >= y0 && bl->y <= y1))
							continue;
						if((dx > 0 && bl->x < x0 + dx) || (dx < 0 && bl->x > x1 + dx) ||
						   (dy > 0 && bl->y < y0 + dy) || (dy < 0 && bl->y > y1 + dy))
						{
							if(bl_list_count >= BLOCK_LIST_MAX)
								break;
							bl_list[bl_list_count++] = bl;
						}
					}
				}
			}
		}
		if(type & BL_MOB) {
			for(by = y2; by <= y3; by++) {
				for(bx = x2; bx <= x3; bx++) {
					bl = map[m].block_mob[bx+by*map[m].bxs];
					for( ; bl; bl = bl->next) {
						if(!(bl->x >= x0 && bl->x <= x1 && bl->y >= y0 && bl->y <= y1))
							continue;
						if((dx > 0 && bl->x < x0 + dx) || (dx < 0 && bl->x > x1 + dx) ||
						   (dy > 0 && bl->y < y0 + dy) || (dy < 0 && bl->y > y1 + dy))
						{
							if(bl_list_count >= BLOCK_LIST_MAX)
								break;
							bl_list[bl_list_count++] = bl;
						}
					}
				}
			}
		}

	}

	if(bl_list_count >= BLOCK_LIST_MAX) {
		if(battle_config.error_log)
			printf("map_foreachinmovearea: *WARNING* block count too many!\n");
	}

	map_freeblock_lock();	// メモリからの解放を禁止する

	for(i = blockcount; i < bl_list_count; i++) {
		if(bl_list[i]->prev) {	// 有効かどうかチェック
			va_list ap;
			va_start(ap, type);
			ret += func(bl_list[i],ap);
			va_end(ap);
		}
	}

	map_freeblock_unlock();	// 解放を許可する

	bl_list_count = blockcount;

	return ret;
}


/*==========================================
 * 矩形(x[0],y[0])-(x[1],y[1])と矩形(x[2],y[2])-(x[3],y[3])の
 * 共通部分に対してfuncを呼ぶ。ただし、x[0] < x[1], y[0] < y[1],
 * x[2] < x[3], y[2] < y[3]を仮定している
 *------------------------------------------
 */

// 正方形の中に点(x,y) が含まれているかを調べる
#define map_square_in(p, _x, _y) (x[p+0] <= (_x) && x[p+1] >= (_x) && y[p+0] <= (_y) && y[p+1] >= (_y))

int map_foreachcommonarea(int (*func)(struct block_list*,va_list),int m,int x[4],int y[4],int type,...)
{
	int flag = 0, i, j, ret = 0;
	int x0 = 0x7fffffff, x1 = -0x7fffffff;
	int y0 = 0x7fffffff, y1 = -0x7fffffff;

	for(i = 0; i < 4; i++) {
		for(j = 0; j < 4; j++) {
			if( map_square_in( 0, x[i], y[j] ) && map_square_in( 2, x[i], y[j] ) ) {
				if( x0 > x[i]) { x0 = x[i]; flag = 1; }
				if( x1 < x[i]) { x1 = x[i]; flag = 1; }
				if( y0 > y[j]) { y0 = y[j]; flag = 1; }
				if( y1 < y[j]) { y1 = y[j]; flag = 1; }
			}
		}
	}
	if( flag ) {
		va_list ap;
		va_start(ap,type);
		ret = map_foreachinarea_sub(func, m, x0, y0, x1, y1, type, ap);
		va_end(ap);
	}

	return ret;
}

/*==========================================
 * 床アイテムやエフェクト用の一時obj割り当て
 * object[]への保存
 *------------------------------------------
 */
int map_addobject(struct block_list *bl)
{
	static int last_object_id = MIN_FLOORITEM - 1;
	int i;

	nullpo_retr(0, bl);

	for(i = last_object_id + 1; i != last_object_id; i++) {
		if(i == MAX_FLOORITEM)
			i = MIN_FLOORITEM;

		if(object[i] == NULL)
			break;
	}
	if(i == last_object_id) {
		if(battle_config.error_log)
			printf("no free object id\n");
		return 0;
	}
	last_object_id = i;
	object[i] = bl;

	return i;
}

/*==========================================
 * 一時objectの解放
 *	map_delobjectのfreeしないバージョン
 *------------------------------------------
 */
int map_delobjectnofree(int id)
{
	if(object[id] == NULL)
		return 0;

	map_delblock(object[id]);
	object[id] = NULL;

	return 0;
}

/*==========================================
 * 一時objectの解放
 * block_listからの削除、id_dbからの削除
 * object dataのfree、object[]へのNULL代入
 *
 * addとの対称性が無いのが気になる
 *------------------------------------------
 */
int map_delobject(int id)
{
	struct block_list *obj = object[id];

	if(obj == NULL)
		return 0;

	map_delobjectnofree(id);
	map_freeblock(obj);

	return 0;
}

/*==========================================
 * 全一時obj相手にfuncを呼ぶ
 *------------------------------------------
 */
int map_foreachobject(int (*func)(struct block_list*,va_list),int type,...)
{
	int i, blockcount = bl_list_count;
	int ret = 0;

	for(i = MIN_FLOORITEM; i < MAX_FLOORITEM; i++) {
		if(object[i]) {
			if(!(object[i]->type & type))
				continue;
			if(bl_list_count >= BLOCK_LIST_MAX) {
				if(battle_config.error_log)
					printf("map_foreachobject: too many block !\n");
				break;
			}
			bl_list[bl_list_count++] = object[i];
		}
	}

	map_freeblock_lock();

	for(i = blockcount; i < bl_list_count; i++) {
		if( bl_list[i]->prev || bl_list[i]->next ) {
			va_list ap;
			va_start(ap, type);
			ret += func(bl_list[i],ap);
			va_end(ap);
		}
	}

	map_freeblock_unlock();

	bl_list_count = blockcount;

	return ret;
}

/*==========================================
 * 床アイテムを消す
 *
 * data==0の時はtimerで消えた時
 * data==1の時は拾う等で消えた時として動作
 * data==2の時はサーバ停止時
 *
 * data==1は、map_clearflooritem(id)へ
 * map.h内で#defineしてある
 *------------------------------------------
 */
int map_clearflooritem_timer(int tid,unsigned int tick,int id,void *data)
{
	struct block_list *bl = object[id];
	struct flooritem_data *fitem = NULL;
	int flag = PTR2INT(data);

	if(bl && bl->type == BL_ITEM)
		fitem = (struct flooritem_data *)bl;

	if(fitem == NULL || (flag == 0 && fitem->cleartimer != tid)) {
		if(battle_config.error_log)
			printf("map_clearflooritem_timer : error\n");
		return 1;
	}
	if(flag == 1)
		delete_timer(fitem->cleartimer,map_clearflooritem_timer);
	else if(fitem->item_data.card[0] == (short)0xff00)
		intif_delete_petdata(*((int *)(&fitem->item_data.card[1])));
	clif_clearflooritem(fitem,-1);
	map_delobject(fitem->bl.id);

	return 0;
}

/*==========================================
 * (x0,y0)から(x1,y1)の空き(=侵入可能)
 * cellをリストに格納してその数を返す
 *------------------------------------------
 */
int map_searchfreecell(struct cell_xy *list,int m,int x0,int y0,int x1,int y1)
{
	int i, j, count = 0;

	for(i = x0; i <= x1; i++) {
		for(j = y0; j <= y1; j++) {
			if(map_getcell(m,i,j,CELL_CHKNOPASS))
				continue;
			if(list) {
				list[count].x = i;
				list[count].y = j;
			}
			count++;
		}
	}
	return count;
}

/*==========================================
 * (m,x,y)を中心に3x3以内に床アイテム設置
 *
 * item_dataはamount以外をcopyする
 *------------------------------------------
 */
int map_addflooritem(struct item *item_data,int amount,int m,int x,int y,int first_id,int second_id,int third_id,int type)
{
	struct cell_xy free_cell[3*3];
	int count;

	nullpo_retr(0, item_data);

	if((count = map_searchfreecell(free_cell,m,x-1,y-1,x+1,y+1)) > 0) {
		struct flooritem_data *fitem = (struct flooritem_data *)aCalloc(1,sizeof(*fitem));
		int idx = atn_rand()%count;

		fitem->bl.type = BL_ITEM;
		fitem->bl.prev = NULL;
		fitem->bl.next = NULL;
		fitem->bl.m    = m;
		fitem->bl.x    = free_cell[idx].x;
		fitem->bl.y    = free_cell[idx].y;
		fitem->first_get_id    = 0;
		fitem->first_get_tick  = 0;
		fitem->second_get_id   = 0;
		fitem->second_get_tick = 0;
		fitem->third_get_id    = 0;
		fitem->third_get_tick  = 0;

		fitem->bl.id = map_addobject(&fitem->bl);

		if(fitem->bl.id > 0) {
			int r = atn_rand();
			unsigned int tick = gettick();

			if(first_id > 0) {
				fitem->first_get_id = first_id;
				if(type)
					fitem->first_get_tick = tick + battle_config.mvp_item_first_get_time;
				else
					fitem->first_get_tick = tick + battle_config.item_first_get_time;
			}
			if(second_id > 0) {
				fitem->second_get_id = second_id;
				if(type)
					fitem->second_get_tick = tick + battle_config.mvp_item_first_get_time + battle_config.mvp_item_second_get_time;
				else
					fitem->second_get_tick = tick + battle_config.item_first_get_time + battle_config.item_second_get_time;
			}
			if(third_id > 0) {
				fitem->third_get_id = third_id;
				if(type)
					fitem->third_get_tick = tick + battle_config.mvp_item_first_get_time + battle_config.mvp_item_second_get_time + battle_config.mvp_item_third_get_time;
				else
					fitem->third_get_tick = tick + battle_config.item_first_get_time + battle_config.item_second_get_time + battle_config.item_third_get_time;
			}

			memcpy(&fitem->item_data,item_data,sizeof(*item_data));
			fitem->item_data.amount = amount;
			fitem->subx = (r&3)*3+3;
			fitem->suby = ((r>>2)&3)*3+3;
			fitem->cleartimer = add_timer(tick+battle_config.flooritem_lifetime,map_clearflooritem_timer,fitem->bl.id,(void*)0);

			map_addblock(&fitem->bl);
			clif_dropflooritem(fitem);

			return fitem->bl.id;
		}
		aFree(fitem);
	}

	if(item_data->card[0] == (short)0xff00)
		intif_delete_petdata(*((int *)(&item_data->card[1])));

	return 0;
}

/*==========================================
 * ドロップディレイキューへpush
 *------------------------------------------
 */
void map_push_delayitem_que(struct delay_item_drop2 *ditem)
{
	nullpo_retv(ditem);

	if(delayitem_head == NULL && delayitem_tail == NULL) {
		// 最初のキュー
		delayitem_head = ditem;
		delayitem_tail = ditem;
	} else if(delayitem_tail) {
		// 最後尾に連結
		delayitem_tail->next = ditem;
		delayitem_tail       = ditem;
	} else {
		// 有り得ないエラー
		printf("map_push_delayitem_que: delayitem_tail is NULL !!");
		map_clear_delayitem_que();
		map_push_delayitem_que(ditem);
	}
	ditem->next = NULL;

	return;
}

/*==========================================
 * ドロップディレイキューからpop
 *------------------------------------------
 */
struct delay_item_drop2 *map_pop_delayitem_que(void)
{
	struct delay_item_drop2 *node = delayitem_head;

	if(node) {
		delayitem_head = node->next;
		if(delayitem_head == NULL)
			delayitem_tail = NULL;
	}
	return node;
}

/*==========================================
 * ドロップディレイキューのクリア
 *------------------------------------------
 */
void map_clear_delayitem_que(void)
{
	struct delay_item_drop2 *node, *node2;

	node = delayitem_head;
	while(node) {
		node2 = node->next;
		intif_delete_petdata(*((int *)(&node->item_data.card[1])));
		aFree(node);
		node = node2;
	}
	delayitem_head = NULL;
	delayitem_tail = NULL;

	return;
}

/*==========================================
 * charid_dbのキャラデータを検索
 *------------------------------------------
 */
struct charid2nick *char_search(int char_id)
{
	struct charid2nick *p;

	p = (struct charid2nick *)numdb_search(charid_db,char_id);
	if(p == NULL) {	// データベースにない
		chrif_searchcharid(char_id);
	}

	return p;
}

/*==========================================
 * charid_dbへ追加(返信待ちがあれば返信)
 *------------------------------------------
 */
void map_addchariddb(int charid, const char *name, int account_id, unsigned long ip, unsigned short port)
{
	struct charid2nick *p;
	struct linkdb_node *head;

	if(account_id <= 0)
		return;

	p = (struct charid2nick *)numdb_search(charid_db,charid);
	if(p == NULL) {	// データベースにない
		p = (struct charid2nick *)aCalloc(1,sizeof(struct charid2nick));
		p->req = NULL;
		numdb_insert(charid_db,charid,p);
	}

	head = p->req;
	memcpy(p->nick, name, 24);
	p->account_id = account_id;
	p->ip         = ip;
	p->port       = port;
	p->req        = NULL;

	if(head) {	// 返信待ちがあれば全員に返信
		struct linkdb_node *node = head;
		while(node) {
			struct map_session_data *sd = map_id2sd(PTR2INT(node->key));
			if(sd) {
				int type = PTR2INT(node->data);
				if(type&1)
					clif_solved_charname(sd,charid);
				if(type&2)
					clif_update_temper(sd);
			}
			node = node->next;
		}
		linkdb_final(&head);
	}
	return;
}

/*==========================================
 * charid_dbから削除
 *------------------------------------------
 */
void map_delchariddb(int charid)
{
	struct charid2nick *p;

	p = (struct charid2nick *)numdb_search(charid_db,charid);
	if(p) {
		// 実際に削除すると武器の名前とか取れなくなるのでmap-serverのIPとPortだけ削除
		p->ip   = 0;
		p->port = 0;
	}

	return;
}

/*==========================================
 * charid_dbへ追加（返信要求のみ）
 * 新規追加時は1、それ以外は0を返す
 *------------------------------------------
 */
int map_reqchariddb(struct map_session_data *sd, int charid, int type)
{
	struct charid2nick *p;

	nullpo_retr(0, sd);

	p = (struct charid2nick *)numdb_search(charid_db,charid);
	if(p != NULL) {	// データベースにすでにある
		if(p->req) {
			// 返信待ち状態なのでリスト更新
			int data = PTR2INT(linkdb_search(&p->req, INT2PTR(sd->bl.id)));
			linkdb_replace(&p->req, INT2PTR(sd->bl.id), INT2PTR(data | type));
		}
		return 0;
	}

	p = (struct charid2nick *)aCalloc(1,sizeof(struct charid2nick));
	linkdb_insert(&p->req, INT2PTR(sd->bl.id), INT2PTR(type));
	numdb_insert(charid_db,charid,p);

	return 1;
}

/*==========================================
 * id_dbへblを追加
 *------------------------------------------
 */
void map_addiddb(struct block_list *bl)
{
	nullpo_retv(bl);

	numdb_insert(id_db,bl->id,bl);
}

/*==========================================
 * id_dbからblを削除
 *------------------------------------------
 */
void map_deliddb(struct block_list *bl)
{
	nullpo_retv(bl);

	numdb_erase(id_db,bl->id);
}

/*==========================================
 * nick_dbへsdを追加
 *------------------------------------------
 */
void map_addnickdb(struct map_session_data *sd)
{
	nullpo_retv(sd);

	strdb_insert(nick_db,sd->status.name,sd);
}

/*==========================================
 * PCのquit処理 map.c内分
 *
 * quit処理の主体が違うような気もしてきた
 *------------------------------------------
 */
int map_quit(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	if(!sd->state.waitingdisconnect && sd->new_fd != -1) {
		if(sd->pd) {
			pet_lootitem_drop(sd->pd,sd);
			unit_free( &sd->pd->bl, 0);
		}
		if(sd->hd) {
			unit_free( &sd->hd->bl, 0);
		}
		if(sd->mcd) {
			unit_free( &sd->mcd->bl, 0);
		}
		if(sd->eld) {
			unit_free( &sd->eld->bl, 0);
		}
		unit_free(&sd->bl, 2);
		chrif_save(sd, 1);
		sd->state.waitingdisconnect = 1;
	}

	if(sd->stack) {
		script_free_stack( sd->stack );
		sd->stack = NULL;
	}

#ifdef DYNAMIC_SC_DATA
	status_free_sc_data(&sd->sc);
#endif

	// ２重ログイン時、後にログインしたキャラのid_dbは削除しない
	if(sd->new_fd != -1)
		numdb_erase(id_db,sd->bl.id);

	strdb_erase(nick_db,sd->status.name);
	map_delchariddb(sd->status.char_id);

	aFree(sd->reg);
	aFree(sd->regstr);

	return 0;
}

/*==========================================
 * id番号のPCを探す。居なければNULL
 *------------------------------------------
 */
struct map_session_data * map_id2sd(int id)
{
	struct block_list *bl;

	if(id > 0) {
		bl = (struct block_list *)numdb_search(id_db,id);
		if(bl && bl->type == BL_PC)
			return (struct map_session_data *)bl;
	}
	return NULL;
}

/*==========================================
 * id番号のMOBを探す。居なければNULL
 *------------------------------------------
 */
struct mob_data * map_id2md(int id)
{
	struct block_list *bl;

	if(id > 0) {
		bl = (struct block_list *)numdb_search(id_db,id);
		if(bl && bl->type == BL_MOB)
			return (struct mob_data *)bl;
	}
	return NULL;
}

/*==========================================
 * id番号のHOMを探す。居なければNULL
 *------------------------------------------
 */
struct homun_data * map_id2hd(int id)
{
	struct block_list *bl;

	if(id > 0) {
		bl = (struct block_list *)numdb_search(id_db,id);
		if(bl && bl->type == BL_HOM)
			return (struct homun_data *)bl;
	}
	return NULL;
}

/*==========================================
 * id番号のMERCを探す。居なければNULL
 *------------------------------------------
 */
struct merc_data * map_id2mcd(int id)
{
	struct block_list *bl;

	if(id > 0) {
		bl = (struct block_list *)numdb_search(id_db,id);
		if(bl && bl->type == BL_MERC)
			return (struct merc_data *)bl;
	}
	return NULL;
}

/*==========================================
 * id番号のELEMを探す。居なければNULL
 *------------------------------------------
 */
struct elem_data * map_id2eld(int id)
{
	struct block_list *bl;

	if(id > 0) {
		bl = (struct block_list *)numdb_search(id_db,id);
		if(bl && bl->type == BL_ELEM)
			return (struct elem_data *)bl;
	}
	return NULL;
}

/*==========================================
 * id番号のNPCを探す。居なければNULL
 *------------------------------------------
 */
struct npc_data * map_id2nd(int id)
{
	struct block_list *bl;

	if(id > 0) {
		bl = (struct block_list *)numdb_search(id_db,id);
		if(bl && bl->type == BL_NPC)
			return (struct npc_data *)bl;
	}
	return NULL;
}

/*==========================================
 * id番号のCHATを探す。居なければNULL
 *------------------------------------------
 */
struct chat_data * map_id2cd(int id)
{
	struct block_list *bl;

	// チャットは一時object
	if(id > 0 && id < MAX_FLOORITEM) {
		bl = object[id];
		if(bl && bl->type == BL_CHAT) {
			if(id != bl->id)
				printf("map_id2cd : block id mismatch !!\n");
			else
				return (struct chat_data *)bl;
		}
	}
	return NULL;
}

/*==========================================
 * id番号のSKILLを探す。居なければNULL
 *------------------------------------------
 */
struct skill_unit * map_id2su(int id)
{
	struct block_list *bl;

	// スキルユニットは一時object
	if(id > 0 && id < MAX_FLOORITEM) {
		bl = object[id];
		if(bl && bl->type == BL_SKILL) {
			if(id != bl->id)
				printf("map_id2su : block id mismatch !!\n");
			else
				return (struct skill_unit *)bl;
		}
	}
	return NULL;
}

/*==========================================
 * id番号のGRPを探す。居なければNULL
 *------------------------------------------
 */
struct skill_unit_group * map_id2sg(int id)
{
	struct block_list *bl;

	// スキルユニットグループは一時object
	if(id > 0 && id < MAX_FLOORITEM) {
		bl = object[id];
		if(bl && bl->type == BL_GRP) {
			if(id != bl->id)
				printf("map_id2sg : block id mismatch !!\n");
			else
				return (struct skill_unit_group *)bl;
		}
	}
	return NULL;
}

/*==========================================
 * id番号の物を探す
 * 一時objectの場合は配列を引くのみ
 *------------------------------------------
 */
struct block_list * map_id2bl(int id)
{
	if(id > 0) {
		if(id < MAX_FLOORITEM)
			return object[id];
		else
			return (struct block_list *)numdb_search(id_db,id);
	}
	return NULL;
}

/*==========================================
 * char_id番号の名前を探す
 *------------------------------------------
 */
char * map_charid2nick(int id)
{
	struct charid2nick *p = (struct charid2nick *)numdb_search(charid_db,id);

	if(p == NULL || p->req)
		return NULL;

	return p->nick;
}

/*==========================================
 * char_id番号のPCを探す
 *------------------------------------------
 */
struct map_session_data * map_charid2sd(int id)
{
	struct charid2nick *p = (struct charid2nick *)numdb_search(charid_db,id);

	if(p == NULL || p->req)
		return NULL;

	return map_id2sd(p->account_id);
}

/*==========================================
 * 名前がnickのPCを探す。居なければNULL
 *------------------------------------------
 */
struct map_session_data * map_nick2sd(const char *nick)
{
	if(nick == NULL)
		return NULL;

	return (struct map_session_data *)strdb_search(nick_db,nick);
}

/*==========================================
 * マスターのsdを探す。居なければNULL
 *------------------------------------------
 */
struct map_session_data * map_bl2msd(struct block_list *bl)
{
	if(bl) {
		switch(bl->type) {
			case BL_PC:
				return (struct map_session_data *)bl;
			case BL_PET:
				return ((struct pet_data *)bl)->msd;
			case BL_HOM:
				return ((struct homun_data *)bl)->msd;
			case BL_MERC:
				return ((struct merc_data *)bl)->msd;
			case BL_ELEM:
				return ((struct elem_data *)bl)->msd;
		}
	}

	return NULL;
}

/*==========================================
 * id_db内の全てにfuncを実行
 *------------------------------------------
 */
int map_foreachiddb(int (*func)(void*,void*,va_list),...)
{
	int ret;
	va_list ap;

	va_start(ap,func);
	ret = db_foreach_sub(id_db,func,ap);
	va_end(ap);

	return ret;
}

/*==========================================
 * map.npcへ追加 (warp等の領域持ちのみ)
 *------------------------------------------
 */
int map_addnpc(int m,struct npc_data *nd)
{
	int i;

	nullpo_retr(0, nd);

	if(m < 0 || m >= map_num)
		return -1;

	for(i = 0; i < map[m].npc_num && i < MAX_NPC_PER_MAP; i++) {
		if(map[m].npc[i] == NULL)
			break;
	}
	if(i == MAX_NPC_PER_MAP) {
		if(battle_config.error_log)
			printf("too many NPCs in one map %s\n",map[m].name);
		return -1;
	}
	if(i == map[m].npc_num) {
		map[m].npc_num++;
	}

	map[m].npc[i] = nd;
	numdb_insert(id_db,nd->bl.id,nd);

	return i;
}

/*==========================================
 * メモリアルダンジョンmap追加
 *------------------------------------------
 */
int map_addmdmap(const char *name, int id)
{
	int src_m = map_mapname2mapid(name);
	int dst_m = -1, i;
	size_t size;

	if(src_m < 0)
		return -1;

	if(strlen(name) > 20) {
		// against buffer overflow
		printf("map_addmdmap: can't add long map name \"%s\"\n", name);
		return -1;
	}

	for(i = map_mdmap_start; i < map_max; i++) {
		if(!map[i].name[0])
			break;
	}
	if(i < map_num) {
		// 旧メモリアルダンジョン削除済み領域を流用する
		dst_m = i;
	}
	else if(i < map_max) {
		// map_numをインクリメント
		dst_m = map_num++;
	}
	else {
		// 追加余裕なし
		printf("map_addmdmap failed. map_num(%d) > map_max(%d)\n",map_num, map_max);
		return -1;
	}

	// マップ情報複製
	memcpy(&map[dst_m], &map[src_m], sizeof(struct map_data));

	// マップ情報編集
	snprintf(map[dst_m].name, sizeof(map[dst_m].name), "%03d%s", id, name);
	map[dst_m].name[23] = '\0';

	map[dst_m].m = dst_m;
	map[dst_m].memorial_id = id;
	map[dst_m].users = 0;

	memset(map[dst_m].npc, 0, sizeof(map[dst_m].npc));
	map[dst_m].npc_num = 0;
	map[dst_m].mvpboss = NULL;

	size = map[dst_m].bxs * map[dst_m].bys * sizeof(struct block_list*);
	map[dst_m].block = (struct block_list **)aCalloc(1,size);
	map[dst_m].block_mob = (struct block_list **)aCalloc(1,size);

	strdb_insert(map_db,map[dst_m].name,&map[dst_m]);

	return dst_m;
}

/*==========================================
 * メモリアルダンジョンPC離脱
 *------------------------------------------
 */
static int map_mdmap_leave(struct block_list *bl, va_list ap)
{
	struct map_session_data* sd;

	nullpo_retr(0, bl);
	nullpo_retr(0, sd = (struct map_session_data *)bl);

	pc_setpos(sd, sd->status.save_point.map, sd->status.save_point.x, sd->status.save_point.y, 3);

	return 1;
}

/*==========================================
 * メモリアルダンジョンblock関連削除
 *------------------------------------------
 */
static int map_mdmap_clean(struct block_list *bl, va_list ap)
{
	nullpo_retr(0, bl);

	switch(bl->type) {
	case BL_PC:
		map_quit((struct map_session_data *)bl);
		break;
	case BL_MOB:
		unit_remove_map(bl,3,0);
	case BL_PET:
	case BL_HOM:
	case BL_MERC:
		break;
	case BL_ITEM:
		map_clearflooritem(bl->id);
		break;
	case BL_SKILL:
		skill_delunit((struct skill_unit *)bl);
		break;
	case BL_NPC:
		{
			struct npc_data *nd = (struct npc_data *)bl;
			if(nd) {
				if(nd->subtype == SCRIPT) {
					npc_timerevent_stop(nd);
					script_erase_sleeptimer(nd);
				}
				npc_free(nd);
			}
		}
		break;
	}

	return 1;
}

/*==========================================
 * メモリアルダンジョンmap削除
 *------------------------------------------
 */
int map_delmdmap(int m)
{
	if(m < 0)
		return 0;
	if(map[m].memorial_id == 0)
		return 0;

	// マップ内のPC離脱
	map_foreachinarea(map_mdmap_leave, m, 0, 0, map[m].xs, map[m].ys, BL_PC);

	// マップ内のblocklist解放
	map_foreachinarea(map_mdmap_clean, m, 0, 0, map[m].xs, map[m].ys, BL_ALL);

	// マップ情報初期化
	if(map[m].block)
		aFree(map[m].block);
	if(map[m].block_mob)
		aFree(map[m].block_mob);

	strdb_erase(map_db,map[m].name);
	memset(&map[m], 0, sizeof(map[0]));

	return 1;
}

/*==========================================
 * mapタイプ取得
 *------------------------------------------
 */
int map_getmaptype(int m)
{
	int type = 0;

	if(m < 0)
		return 0;

	if(map[m].flag.pvp_nightmaredrop)
		type = 5;
	else if(map[m].flag.pvp && map[m].flag.pvp_nocalcrank)
		type = 12;
	else if(map[m].flag.pvp)
		type = 6;
	else if(map[m].flag.gvg)	// FE
		type = 8;
//	else if(map[m].flag.gvg)	// SE
//		type = 18;
//	else if(map[m].flag.gvg)	// TE
//		type = 25;
	else if(map[m].flag.gvg_noparty)
		type = 9;
	else if(map[m].flag.noskill)
		type = 13;
	else if(map[m].memorial_id)
		type = 20;
	else if(map[m].flag.noteleport)
		type = 10;
	else if(map[m].flag.town)
		type = 0;
	else if(!map[m].flag.nomemo)
		type = 2;
	else
		type = 3;

	return type;
}

/*==========================================
 * map名からmap番号へ変換
 *------------------------------------------
 */
int map_mapname2mapid(const char *name)
{
	struct map_data *md;

	md = (struct map_data *)strdb_search(map_db,name);
	if(md == NULL || md->gat == NULL)
		return -1;
	return md->m;
}

/*==========================================
 * 他鯖map名からip,port変換
 *------------------------------------------
 */
int map_mapname2ipport(const char *name,unsigned long *ip,unsigned short *port)
{
	struct map_data_other_server *mdos;

	mdos = (struct map_data_other_server *)strdb_search(map_db,name);
	if(mdos == NULL || mdos->gat)
		return -1;

	*ip   = mdos->ip;
	*port = mdos->port;
	return 0;
}

// gat系
/*==========================================
 * (m,x,y)の状態を調べる
 *------------------------------------------
 */
int map_getcell(int m,int x,int y,cell_t cellchk)
{
	return (m < 0 || m >= map_num) ? 0 : map_getcellp(&map[m], x, y, cellchk);
}

int map_getcellp(struct map_data* m,int x,int y,cell_t cellchk)
{
	int type;

	nullpo_ret(m);

	if(x < 0 || x >= m->xs - 1 || y < 0 || y >= m->ys - 1) {
		return (cellchk == CELL_CHKNOPASS);
	}

	type = m->gat[x+y*m->xs];
	if(cellchk >= CELL_CHKWALL && cellchk < CELL_CHKNPC)
		type &= CELL_MASK;

	switch(cellchk)
	{
		case CELL_CHKNONE:
			return 0;
		case CELL_CHKPASS:
			return (type != 1 && type != 5);
		case CELL_CHKNOPASS:
			return (type == 1 || type == 5);
		case CELL_CHKWALL:
			return (type == 1);
		case CELL_CHKWATER:
			return (type == 3);
		case CELL_CHKGROUND:
			return (type == 5);
		case CELL_GETTYPE:
			return type;
		case CELL_CHKNPC:
			return (type & CELL_NPC);
		case CELL_CHKBASILICA:
			return (type & CELL_BASILICA);
	}
	return 0;
}

/*==========================================
 * (m,x,y)の状態を設定する
 *------------------------------------------
 */
void map_setcell(int m,int x,int y,int cell)
{
	int j;

	if(x < 0 || x >= map[m].xs || y < 0 || y >= map[m].ys)
		return;

	j = x + y * map[m].xs;

	switch (cell) {
		case CELL_SETNPC:
			map[m].gat[j] |= CELL_NPC;
			break;
		case CELL_SETBASILICA:
			map[m].gat[j] |= CELL_BASILICA;
			break;
		case CELL_CLRBASILICA:
			map[m].gat[j] &= ~CELL_BASILICA;
			break;
		default:
			map[m].gat[j] = (map[m].gat[j]&~CELL_MASK) + cell;
			break;
	}
}

/*==========================================
 * ランダムにマップの有効セル位置を返す
 *------------------------------------------
 */
int map_random_freecell(int m,int *x,int *y)
{
	int posx, posy;
	int i = 0;

	do {
		posx = atn_rand()%(map[m].xs-2)+1;
		posy = atn_rand()%(map[m].ys-2)+1;
	} while( map_getcell(m,posx,posy,CELL_CHKNOPASS) && (i++) < 1000 );

	if(i < 1000) {
		*x = posx;
		*y = posy;
		return 1;
	}

	return 0;
}

/*==========================================
 * 他鯖管理のマップをdbに追加
 *------------------------------------------
 */
int map_setipport(const char *name,unsigned long ip,unsigned short port)
{
	struct map_data *md;
	struct map_data_other_server *mdos;

	md = (struct map_data *)strdb_search(map_db,name);
	if(md == NULL) {
		// 存在しないデータ
		mdos = (struct map_data_other_server *)aCalloc(1,sizeof(struct map_data_other_server));
		memcpy(mdos->name,name,24);
		mdos->name[23] = '\0';	// force \0 terminal
		mdos->gat  = NULL;
		mdos->ip   = ip;
		mdos->port = port;
		mdos->map  = NULL;
		strdb_insert(map_db,mdos->name,mdos);
	} else if(md->gat) {
		if(ip != clif_getip() || port != clif_getport()) {
			// 読み込んでいたけど、担当外になったマップ
			mdos = (struct map_data_other_server *)aCalloc(1,sizeof(struct map_data_other_server));
			memcpy(mdos->name,name,24);
			mdos->name[23] = '\0';	// force \0 terminal
			mdos->gat  = NULL;
			mdos->ip   = ip;
			mdos->port = port;
			mdos->map  = md;
			strdb_insert(map_db,mdos->name,mdos);
		} else {
			// 読み込んでいて、担当になったマップ（何もしない）
			;
		}
	} else {
		mdos = (struct map_data_other_server *)md;
		if(ip == clif_getip() && port == clif_getport()) {
			// 自分の担当になったマップ
			if(mdos->map == NULL) {
				// 読み込んでいないので終了する
				printf("map_setipport : %s is not loaded.\n",name);
				exit(1);
			} else {
				// 読み込んでいるので置き換える
				md = mdos->map;
				strdb_insert(map_db,md->name,md);
				aFree(mdos);
			}
		} else {
			// 他の鯖の担当マップなので置き換えるだけ
			mdos->ip   = ip;
			mdos->port = port;
		}
	}
	return 0;
}

/*==========================================
 * 他鯖管理のマップを全て削除
 *------------------------------------------
 */
static int map_eraseallipport_sub(void *key,void *data,va_list va)
{
	struct map_data_other_server *mdos = (struct map_data_other_server*)data;

	if(mdos->gat == NULL) {
		strdb_erase(map_db,key);
		aFree(mdos);
	}
	return 0;
}

void map_eraseallipport(void)
{
	strdb_foreach(map_db,map_eraseallipport_sub);
}

/*==========================================
 * 他鯖管理のマップをdbから削除
 *------------------------------------------
 */
int map_eraseipport(const char *name,unsigned long ip,unsigned short port)
{
	struct map_data *md;
	struct map_data_other_server *mdos;

	md = (struct map_data *)strdb_search(map_db,name);
	if(md) {
		if(md->gat) // local -> check data
			return 0;
		mdos = (struct map_data_other_server *)md;
		if(mdos->ip == ip && mdos->port == port) {
			if(mdos->map) {
				// このマップ鯖でも読み込んでいるので移動できる
				return 1; // 呼び出し元で chrif_sendmap() をする
			}
			strdb_erase(map_db,name);
			aFree(mdos);

			//if(battle_config.etc_log) {
			//	unsigned char *p = (unsigned char *)&ip;
			//	printf("erase map %s %d.%d.%d.%d:%d\n",name,p[0],p[1],p[2],p[3],port);
			//}
		}
	}
	return 0;
}

// 初期化周り
/*==========================================
 * 水場高さ設定
 *------------------------------------------
 */
static struct waterlist {
	char mapname[16];
	int waterheight;
} *waterlist = NULL;

static int waterlist_num = 0;
static int waterlist_max = 0;

#define NO_WATER  0x7fffffff
#define ALL_WATER 0x80000000

static int map_search_waterheight(const char *mapname)
{
	int i;

	for(i = 0; i < waterlist_num; i++) {
		if(strncmp(waterlist[i].mapname, mapname, 16) == 0)
			return i;
	}

	return -1;
}

static int map_waterheight(const char *mapname)
{
	int wh, idx;

	idx = map_search_waterheight(mapname);
	if(idx >= 0) {
		// water_height.txtを優先する
		wh = waterlist[idx].waterheight;
	} else {
		char fn[32];
		char *rsw;

		// rswファイルから読み込み
		sprintf(fn, "data\\%s", mapname);
		memcpy(fn + strlen(fn) - 4, ".rsw", 4);
		rsw = (char *)grfio_read(fn);

		if(rsw) {
			wh = (int)(*(float*)(rsw + 166));
			aFree(rsw);
		} else {
			wh = NO_WATER;
		}
	}

	return wh;
}

static void map_readwater(void)
{
	char line[1024], w1[1024];
	FILE *fp;

	fp = fopen(water_height_txt, "r");
	if(fp == NULL)
		return;

	while(fgets(line, sizeof(line), fp)) {
		struct waterlist *p = NULL;
		int idx, wh, count;

		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if(line[0] == '/' && line[1] == '/')
			continue;
		if((count = sscanf(line, "%1023s%d", w1, &wh)) < 1) {
			continue;
		}

		idx = map_search_waterheight(w1);
		if(idx >= 0) {
			p = &waterlist[idx];
		} else {
			if(waterlist_num >= waterlist_max) {
				waterlist_max += 16;
				waterlist = (struct waterlist *)aRealloc(waterlist, sizeof(struct waterlist) * waterlist_max);
			}
			p = &waterlist[waterlist_num];
		}
		strncpy(p->mapname, w1, 16);
		p->mapname[15] = '\0';
		p->waterheight = (count >= 2)? wh: ALL_WATER;
		waterlist_num++;
	}
	fclose(fp);

	printf("File '%s' readed ('%d' entrie%s).\n", water_height_txt, waterlist_num, (waterlist_num > 1) ? "s" : "");

	return;
}

/*==========================================
 * マップキャッシュに追加する
 *------------------------------------------
 */
// マップキャッシュの最大値
#define MAX_MAP_CACHE 768

// 各マップごとの最小限情報を入れるもの、READ_FROM_BITMAP用
struct map_cache_info {
	char fn[32];		// ファイル名
	int xs,ys;		// 幅と高さ
	int water_height;
	int pos;  		// データが入れてある場所
	int compressed;		// zilb通せるようにする為の予約
	unsigned int compressed_len;	// zilb通せるようにする為の予約
}; // 56 byte

struct map_cache_head {
	unsigned int sizeof_header;
	unsigned int sizeof_map;
	// 上の２つ改変不可
	int nmaps; // マップの個数
	int filesize;
};

static struct {
	struct map_cache_head head;
	struct map_cache_info *map;
	FILE *fp;
	int dirty;
} map_cache;

static void map_cache_close(void)
{
	if(!map_cache.fp)
		return;

	if(map_cache.dirty) {
		fseek(map_cache.fp,0,SEEK_SET);
		fwrite(&map_cache.head,1,sizeof(struct map_cache_head),map_cache.fp);
		fwrite(map_cache.map,map_cache.head.nmaps,sizeof(struct map_cache_info),map_cache.fp);
	}
	fclose(map_cache.fp);
	aFree(map_cache.map);
	map_cache.fp = NULL;
	return;
}

static int map_cache_open(const char *fn)
{
	struct stat st;
	int size = 0;

	atexit(map_cache_close);

	if(stat(fn, &st) == 0)
		size = st.st_size;

	if(map_cache.fp) {
		map_cache_close();
	}
	map_cache.fp = fopen(fn,"r+b");
	if(map_cache.fp) {
		fread(&map_cache.head,1,sizeof(struct map_cache_head),map_cache.fp);
		if(
			map_cache.head.sizeof_header == sizeof(struct map_cache_head) &&
			map_cache.head.sizeof_map    == sizeof(struct map_cache_info) &&
			map_cache.head.filesize      == size
		) {
			// キャッシュ読み込み成功
			map_cache.map = (struct map_cache_info *)aMalloc(sizeof(struct map_cache_info) * map_cache.head.nmaps);
			fseek(map_cache.fp,sizeof(struct map_cache_head),SEEK_SET);
			fread(map_cache.map,sizeof(struct map_cache_info),map_cache.head.nmaps,map_cache.fp);
			return 1;
		}
		fclose(map_cache.fp);
	}
	// 読み込みに失敗したので新規に作成する
	map_cache.fp = fopen(fn,"wb");
	if(map_cache.fp) {
		memset(&map_cache.head,0,sizeof(struct map_cache_head));
		map_cache.map = (struct map_cache_info *)aCalloc(sizeof(struct map_cache_info),MAX_MAP_CACHE);
		map_cache.head.nmaps         = MAX_MAP_CACHE;
		map_cache.head.sizeof_header = sizeof(struct map_cache_head);
		map_cache.head.sizeof_map    = sizeof(struct map_cache_info);
		map_cache.head.filesize      = sizeof(struct map_cache_head) + sizeof(struct map_cache_info) * map_cache.head.nmaps;

		map_cache.dirty = 1;
		return 1;
	}
	return 0;
}

static int map_cache_read(struct map_data *m)
{
	int i;

	if(!map_cache.fp)
		return 0;

	for(i = 0; i < map_cache.head.nmaps ; i++) {
		if(!strcmp(m->name,map_cache.map[i].fn)) {
			int idx = map_search_waterheight(m->name);
			if(idx >= 0 && map_cache.map[i].water_height != waterlist[idx].waterheight) {
				// water_hegiht.txtの水場の高さと違うので読み直し
				return 0;
			}
			if(map_cache.map[i].compressed == 0) {
				// 非圧縮ファイル
				size_t size = map_cache.map[i].xs * map_cache.map[i].ys;
				m->xs = map_cache.map[i].xs;
				m->ys = map_cache.map[i].ys;
				m->gat = (unsigned char *)aCalloc(m->xs * m->ys,sizeof(unsigned char));
				fseek(map_cache.fp,map_cache.map[i].pos,SEEK_SET);
				if(fread(m->gat,1,size,map_cache.fp) == size) {
					// 成功
					return 1;
				}
				// なぜかファイル後半が欠けてるので読み直し
				m->xs = 0;
				m->ys = 0;
				aFree(m->gat);
				m->gat = NULL;
				return 0;
			}
			if(map_cache.map[i].compressed == 1) {
				// 圧縮フラグ=1 : zlib
				unsigned char *buf;
				unsigned long dest_len;
				unsigned int size_compress = map_cache.map[i].compressed_len;
				m->xs = map_cache.map[i].xs;
				m->ys = map_cache.map[i].ys;
				m->gat = (unsigned char *)aMalloc(m->xs * m->ys * sizeof(unsigned char));
				buf = (unsigned char*)aMalloc(size_compress);
				fseek(map_cache.fp,map_cache.map[i].pos,SEEK_SET);
				if(fread(buf,1,size_compress,map_cache.fp) != size_compress) {
					// なぜかファイル後半が欠けてるので読み直し
					printf("fread error\n");
					m->xs = 0;
					m->ys = 0;
					aFree(m->gat);
					m->gat = NULL;
					aFree(buf);
					return 0;
				}
				dest_len = m->xs * m->ys;
				decode_zip(m->gat,&dest_len,buf,size_compress);
				if(dest_len != map_cache.map[i].xs * map_cache.map[i].ys) {
					// 正常に解凍が出来てない
					m->xs = 0;
					m->ys = 0;
					aFree(m->gat);
					m->gat = NULL;
					aFree(buf);
					return 0;
				}
				aFree(buf);
				return 1;
			}
		}
	}
	return 0;
}

static int map_cache_write(struct map_data *m)
{
	int i;
	unsigned long len_new, len_old;
	char *write_buf;

	if(!map_cache.fp)
		return 0;

	for(i = 0; i < map_cache.head.nmaps ; i++) {
		if(!strcmp(m->name,map_cache.map[i].fn)) {
			// 同じエントリーがあれば上書き
			if(map_cache.map[i].compressed == 0) {
				len_old = map_cache.map[i].xs * map_cache.map[i].ys;
			} else if(map_cache.map[i].compressed == 1) {
				len_old = map_cache.map[i].compressed_len;
			} else {
				// サポートされてない形式なので長さ０
				len_old = 0;
			}
			if(map_read_flag == 2) {
				// 圧縮保存
				// さすがに２倍に膨れる事はないという事で
				write_buf = (char *)aMalloc(m->xs * m->ys * 2);
				len_new = m->xs * m->ys * 2;
				encode_zip(write_buf,&len_new,m->gat,m->xs * m->ys);
				map_cache.map[i].compressed     = 1;
				map_cache.map[i].compressed_len = (unsigned int)len_new;
			} else {
				len_new = m->xs * m->ys;
				write_buf = m->gat;
				map_cache.map[i].compressed     = 0;
				map_cache.map[i].compressed_len = 0;
			}
			if(len_new <= len_old) {
				// サイズが同じか小さくなったので場所は変わらない
				fseek(map_cache.fp,map_cache.map[i].pos,SEEK_SET);
				fwrite(write_buf,1,len_new,map_cache.fp);
			} else {
				// 新しい場所に登録
				fseek(map_cache.fp,map_cache.head.filesize,SEEK_SET);
				fwrite(write_buf,1,len_new,map_cache.fp);
				map_cache.map[i].pos = map_cache.head.filesize;
				map_cache.head.filesize += len_new;
			}
			map_cache.map[i].xs  = m->xs;
			map_cache.map[i].ys  = m->ys;
			map_cache.map[i].water_height = map_waterheight(m->name);
			map_cache.dirty = 1;
			if(map_read_flag == 2) {
				aFree(write_buf);
			}
			return 0;
		}
	}
	// 同じエントリが無ければ書き込める場所を探す
	for(i = 0; i < map_cache.head.nmaps ; i++) {
		if(map_cache.map[i].fn[0] == 0) {
			// 新しい場所に登録
			if(map_read_flag == 2) {
				write_buf = (char *)aMalloc(m->xs * m->ys * 2);
				len_new = m->xs * m->ys * 2;
				encode_zip(write_buf,&len_new,m->gat,m->xs * m->ys);
				map_cache.map[i].compressed     = 1;
				map_cache.map[i].compressed_len = (unsigned int)len_new;
			} else {
				len_new = m->xs * m->ys;
				write_buf = m->gat;
				map_cache.map[i].compressed     = 0;
				map_cache.map[i].compressed_len = 0;
			}
			strncpy(map_cache.map[i].fn,m->name,sizeof(map_cache.map[0].fn));
			fseek(map_cache.fp,map_cache.head.filesize,SEEK_SET);
			fwrite(write_buf,1,len_new,map_cache.fp);
			map_cache.map[i].pos = map_cache.head.filesize;
			map_cache.map[i].xs  = m->xs;
			map_cache.map[i].ys  = m->ys;
			map_cache.map[i].water_height = map_waterheight(m->name);
			map_cache.head.filesize += len_new;
			map_cache.dirty = 1;
			if(map_read_flag == 2) {
				aFree(write_buf);
			}
			return 0;
		}
	}
	// 書き込めなかった
	return 1;
}

/*==========================================
 * 読み込むmapを追加する
 *------------------------------------------
 */
static void map_addmap(const char *mapname)
{
	int i;
	size_t len;

	if(strcmpi(mapname, "clear") == 0) {
		if(map != NULL) {
			aFree(map);
			map = NULL;
		}
		map_num = 0;
		map_max = 0;
		return;
	}

	len = strlen(mapname);
	if(len < 4 || strcasecmp(mapname + len - 4, ".gat") != 0)
		return;

	for(i = 0; i < map_num; i++) {
		if(strcmp(map[i].name, mapname) == 0)
			return;		// 既に追加済みのMAP
	}

	if(map_num + MAX_MEMORIAL_MAP >= map_max) {
		map_max += 128;
		map = (struct map_data *)aRealloc(map, sizeof(struct map_data) * map_max);
	}
	memcpy(map[map_num].name, mapname, 24);
	map[map_num].name[23] = '\0';	// force \0 terminal
	map_num++;

	return;
}

/*==========================================
 * 読み込むmapを削除する
 *------------------------------------------
 */
static void map_delmap(const char *mapname)
{
	int i;

	if(strcmpi(mapname, "all") == 0) {
		map_num = 0;
		map_max = 0;
		if(map != NULL) {
			aFree(map);
			map = NULL;
		}
		return;
	}

	for(i = 0; i < map_num; i++) {
		if(strcmp(map[i].name, mapname) == 0) {
			map_num--;
			memmove(map + i, map + i + 1, sizeof(struct map_data) * (map_num - i));
			memset(map + map_num, 0, sizeof(struct map_data));
		}
	}

	return;
}

/*==========================================
 * マップ1枚読み込み
 *------------------------------------------
 */
static int map_readmap(int m,const char *fn,int *cache)
{
	size_t size;

	printf("map reading %s[%d/%d] %-20s  \r", (map_read_flag ? "with cache " : ""), m+1, map_num, fn);
	fflush(stdout);

	if(map_cache_read(&map[m])) {
		// キャッシュから読み込めた
		(*cache)++;
	} else {
		int wh;
		int x,y,xs,ys;
		unsigned char *gat;
		struct gat_1cell {
			float high[4];
			int type;
		} *p;

		// read & convert fn
		gat = (unsigned char *)grfio_read(fn);
		if(gat == NULL) {
			// さすがにマップが読めないのはまずいので終了する
			printf("Map '%s' not found: removed from maplist.\n", fn);
			return -1;
		}

		xs = *(int*)(gat + 6);
		ys = *(int*)(gat + 10);
		if (xs == 0 || ys == 0) { // ?? but possible
			printf("Invalid size for map '%s' (xs,ys: %d,%d): removed from maplist.\n", fn, xs, ys);
			return -1;
		}
		map[m].xs = xs;
		map[m].ys = ys;
		map[m].gat = (unsigned char *)aCalloc(map[m].xs * map[m].ys,sizeof(unsigned char));
		wh = map_waterheight(map[m].name);

		for(y = 0; y < ys; y++) {
			p = (struct gat_1cell*)(gat + y * xs * 20 + 14);
			for(x = 0; x < xs; x++) {
				if(wh != NO_WATER && p->type == 0) {
					// 水場判定
					map[m].gat[x+y*xs] = (wh == ALL_WATER || p->high[0] > wh || p->high[1] > wh || p->high[2] > wh || p->high[3] > wh) ? 3 : 0;
				} else {
					map[m].gat[x+y*xs] = p->type;
				}
				p++;
			}
		}
		map_cache_write(&map[m]);
		aFree(gat);
	}
	map[m].m       = m;
	map[m].npc_num = 0;
	map[m].users   = 0;
	memset(&map[m].flag,0,sizeof(map[m].flag));
	memset(&map[m].drop_list,0,sizeof(map[m].drop_list));
	map[m].bxs = (map[m].xs + BLOCK_SIZE - 1) / BLOCK_SIZE;
	map[m].bys = (map[m].ys + BLOCK_SIZE - 1) / BLOCK_SIZE;
	size = map[m].bxs * map[m].bys * sizeof(struct block_list*);
	map[m].block     = (struct block_list **)aCalloc(1,size);
	map[m].block_mob = (struct block_list **)aCalloc(1,size);
	strdb_insert(map_db,map[m].name,&map[m]);

	return 0;
}

/*==========================================
 * 全てのmapデータを読み込む
 *------------------------------------------
 */
static void map_readallmap(void)
{
	int i;
	int cache = 0;
	int maps_removed = 0;

	// マップキャッシュを開く
	if(map_read_flag) {
		map_cache_open(map_cache_file);
	}

	map_readwater();

	// リサイズ
	map_max = map_num + MAX_MEMORIAL_MAP;
	map = (struct map_data *)aRealloc(map, sizeof(struct map_data) * map_max);

	for(i = 0; i < map_num; i++) {
		char fn[32];
		sprintf(fn, "data\\%s", map[i].name);
		if(map_readmap(i, fn, &cache) == -1) {
			map_delmap(map[i].name);
			maps_removed++;
			i--;
		}
	}

	if(waterlist_num > 0) {
		aFree(waterlist);
		waterlist_num = 0;
		waterlist_max = 0;
	}
	if(maps_removed) {
		printf("%d maps in configuration file. %d map%s removed.\n", map_num + maps_removed, maps_removed, (maps_removed > 1) ? "s" : "");
	}
	printf("Map read done (%d map%s, %d map%s in cache). %24s\n", map_num, (map_num > 1) ? "s" : "", cache, (cache > 1) ? "s" : "", "");

	// メモリアルダンジョンマップ生成開始インデックスを設定
	map_mdmap_start = map_num;

	// マップキャッシュを閉じる
	map_cache_close();

	if(map_num <= 0) {
		printf("ERROR: no map found.\n");
		//exit(1);
	}

	return;
}

/*==========================================
 * @whoのDB版
 *------------------------------------------
 */
static int map_who_sub(void *key,void *data,va_list ap)
{
	struct charid2nick *p;
	int fd;

	nullpo_retr(-1, ap);
	nullpo_retr(-1, data);
	nullpo_retr(-1, p = (struct charid2nick *)data);

	fd = va_arg(ap,int);

	if( p->ip != 0 && p->port != 0 && !(battle_config.hide_GM_session && pc_numisGM(p->account_id)) )
		clif_displaymessage(fd, p->nick);

	return 0;
}

int map_who(int fd)
{
	numdb_foreach(charid_db, map_who_sub, fd);
	return 0;
}

/*==========================================
 * PKサーバーに一括変更
 *------------------------------------------
 */
static int map_pk_server(int flag)
{
	int i, count = 0;

	if(!flag)
		return 0;

	printf("server setting: pk map");
	for(i = 0; i < map_num; i++) {
		if(map[i].flag.gvg || map[i].flag.pvp)
			continue;
		if(map[i].flag.nopenalty)
			continue;
		if(map[i].flag.gvg_noparty)
			continue;
		if(!map[i].flag.nomemo)
			continue;
		map[i].flag.pk = 1;
		count++;
	}
	printf(" (count:%d/%d)\n",count,map_num);
	return 1;
}

/*==========================================
 * PKフィールドのアイテムドロップを一括変更
 *------------------------------------------
 */
static int map_pk_nightmaredrop(int flag)
{
	int m, i, count = 0;

	if(!flag)
		return 0;

	printf("server setting: pk nightmaredrop");
	for(m = 0; m < map_num; m++) {
		if(!map[m].flag.pk)
			continue;
		for(i = 0; i < MAX_DROP_PER_MAP; i++) {
			if(map[m].drop_list[i].drop_id == 0) {
				map[m].drop_list[i].drop_id   = -1;			// random
				map[m].drop_list[i].drop_type = 2;			// equip
				map[m].drop_list[i].drop_per  = 1000;			// 10%
				map[m].drop_list[i].drop_flag = MF_PK_NIGHTMAREDROP;	// PK
				break;
			}
		}
		if(i >= MAX_DROP_PER_MAP) {	// 空きがない場合はマップフラグをセットしない
			printf("\nmap_pk_nightmaredrop: drop list is full (%s, size = %d)\a", map[m].name, i);
			continue;
		}
		map[m].flag.pk_nightmaredrop = 1;
		count++;
	}
	printf(" (count: %d/%d)\n", count, map_num);
	return 1;
}

/*==========================================
 * PKフィールドのテレポート不可を一括変更
 *------------------------------------------
 */
static int map_pk_noteleport(int flag)
{
	int m, count = 0;

	if(!flag)
		return 0;

	printf("server setting: pk noteleport");
	for(m = 0; m < map_num; m++) {
		if(!map[m].flag.pk)
			continue;
		map[m].flag.noteleport = 1;
		count++;
	}
	printf(" (count: %d/%d)\n", count, map_num);
	return 1;
}

/*==========================================
 * 設定ファイルを読み込む
 *------------------------------------------
 */
static int map_config_read(const char *cfgName)
{
	char line[1024], w1[1024], w2[1024];
	FILE *fp;

	fp = fopen(cfgName,"r");
	if (fp == NULL) {
		printf("map_config_read: open [%s] failed !\n", cfgName);
		return 1;
	}

	while(fgets(line, sizeof(line) - 1, fp)) {
		if(line[0] == '\0' || line[0] == '\r' || line[0] == '\n')
			continue;
		if (line[0] == '/' && line[1] == '/')
			continue;

		if (sscanf(line, "%1023[^:]: %1023[^\r\n]", w1, w2) != 2)
			continue;

		if (strcmpi(w1, "userid") == 0) {
			chrif_setuserid(w2);
		} else if (strcmpi(w1, "passwd") == 0) {
			chrif_setpasswd(w2);
		} else if (strcmpi(w1, "char_ip") == 0) {
			chrif_sethost(w2);
		} else if (strcmpi(w1, "char_port") == 0) {
			int n = atoi(w2);
			if (n < 0 || n > 65535) {
				printf("map_config_read: Invalid char_port value: %d. Set to 6121 (default).\n", n);
				n = 6121; // default
			}
			chrif_setport((unsigned short)n);
		} else if (strcmpi(w1, "map_ip") == 0) {
			clif_sethost(w2);
		} else if (strcmpi(w1, "map_port") == 0) {
			int n = atoi(w2);
			if (n < 0 || n > 65535) {
				printf("map_config_read: Invalid map_port value: %d. Set to 5121 (default).\n", n);
				n = 5121; // default
			}
			clif_setport((unsigned short)n);
		} else if (strcmpi(w1, "listen_ip") == 0) {
			unsigned long ip_result = host2ip(w2, NULL);
			if (ip_result == INADDR_NONE) // not always -1
				printf("map_config_read: Invalid listen_ip value: %s.\n", w2);
			else
				listen_ip = ip_result;
		} else if (strcmpi(w1, "map_server_tag") == 0) {
			strncpy(map_server_tag, w2, sizeof(map_server_tag) - 1);
			map_server_tag[sizeof(map_server_tag) - 1] = '\0';
		} else if (strcmpi(w1, "water_height") == 0) {
			strncpy(water_height_txt, w2, sizeof(water_height_txt) - 1);
			water_height_txt[sizeof(water_height_txt) - 1] = '\0';
		} else if (strcmpi(w1, "gm_account_filename") == 0) {
			pc_set_gm_account_fname(w2);
		} else if (strcmpi(w1, "grf_path_txt") == 0) {
			strncpy(grf_path_txt, w2, sizeof(grf_path_txt) - 1);
			grf_path_txt[sizeof(grf_path_txt) - 1] = '\0';
		} else if (strcmpi(w1, "map") == 0) {
			map_addmap(w2);
		} else if (strcmpi(w1, "delmap") == 0) {
			map_delmap(w2);
		} else if (strcmpi(w1, "npc") == 0) {
			npc_addsrcfile(w2);
		} else if (strcmpi(w1, "delnpc") == 0) {
			npc_delsrcfile(w2);
		} else if (strcmpi(w1, "packet_parse_time") == 0) {
			packet_parse_time = atoi(w2);
			if (packet_parse_time < 0) {
				printf("map_config_read: Invalid packet_parse_time value: %d. Set to 0 (default).\n", packet_parse_time);
				packet_parse_time = 0;
			}
		} else if (strcmpi(w1, "autosave_time") == 0) {
			autosave_interval = atoi(w2) * 1000;
			if (autosave_interval <= 0) {
				printf("map_config_read: Invalid autosave_time value: %d. Set to %d (default).\n", autosave_interval, (int)(DEFAULT_AUTOSAVE_INTERVAL / 1000));
				autosave_interval = DEFAULT_AUTOSAVE_INTERVAL;
			}
		} else if (strcmpi(w1, "autosave_gvg_rate") == 0) {
			autosave_gvg_rate = atoi(w2);
			if (autosave_gvg_rate < 100) {
				printf("map_config_read: Invalid autosave_gvg_rate value: %d. Set to 100 (minimum).\n", autosave_gvg_rate);
				autosave_gvg_rate = 100;
			}
		} else if (strcmpi(w1, "extra_check_interval") == 0) {
			extra_check_interval = atoi(w2);
		} else if (strcmpi(w1, "motd_txt") == 0) {
			strncpy(motd_txt, w2, sizeof(motd_txt) - 1);
			motd_txt[sizeof(motd_txt) - 1] = '\0';
		} else if (strcmpi(w1, "help_txt") == 0) {
			strncpy(help_txt, w2, sizeof(help_txt) - 1);
			help_txt[sizeof(help_txt) - 1] = '\0';
		} else if (strcmpi(w1, "extra_add_file_txt") == 0) {
			strncpy(extra_add_file_txt, w2, sizeof(extra_add_file_txt) - 1);
			extra_add_file_txt[sizeof(extra_add_file_txt) - 1] = '\0';
		} else if (strcmpi(w1, "read_map_from_cache") == 0) {
			map_read_flag = atoi(w2);
		} else if (strcmpi(w1, "map_cache_file") == 0) {
			strncpy(map_cache_file, w2, sizeof(map_cache_file) - 1);
			map_cache_file[sizeof(map_cache_file) - 1] = '\0';
		} else if (strcmpi(w1, "httpd_enable") == 0) {
			socket_enable_httpd(atoi(w2));
		} else if (strcmpi(w1, "httpd_document_root") == 0) {
			httpd_set_document_root(w2);
		} else if (strcmpi(w1, "httpd_log_filename") == 0) {
			httpd_set_logfile(w2);
		} else if (strcmpi(w1, "httpd_config") == 0) {
			httpd_config_read(w2);
		} else if (strcmpi(w1, "map_pk_server") == 0) {
			map_pk_server_flag = atoi(w2);
		} else if (strcmpi(w1, "map_pk_nightmaredrop") == 0) {
			map_pk_nightmaredrop_flag = atoi(w2);
		} else if (strcmpi(w1, "map_pk_noteleport") == 0) {
			map_pk_noteleport_flag = atoi(w2);
		} else if (strcmpi(w1, "import") == 0) {
			map_config_read(w2);
		} else {
			mapreg_config_read_sub(w1, w2);
		}
	}
	fclose(fp);

	return 0;
}

/*==========================================
 * マップが通常マップであるかを排他的に設定
 *------------------------------------------
 */
int map_field_setting(void)
{
	int m;

	for(m = 0; m < map_num; m++) {
		if(map[m].flag.pk || map[m].flag.pvp || map[m].flag.gvg)
			map[m].flag.normal = 0;
		else
			map[m].flag.normal = 1;
	}

	return 0;
}

/*==========================================
 * socket コントロールパネルから呼ばれる
 *------------------------------------------
 */
static void map_socket_ctrl_panel_func(int fd,char* usage,char* user,char* status)
{
	struct socket_data *sd = session[fd];

	strcpy( usage,
		( sd->func_parse == clif_parse )? "map user" :
		( sd->func_parse == chrif_parse )? "char server" : "unknown" );

	if( sd->func_parse == clif_parse && sd->auth )
	{
		struct map_session_data *sd2 = (struct map_session_data *)sd->session_data;
		sprintf( user, "%d %d(%s)", sd2->bl.id, sd2->char_id, sd2->status.name );
	}
}

/*==========================================
 * map鯖正常終了直前処理
 *------------------------------------------
 */
void do_pre_final(void)
{
	// OnFinalイベント実行
	printf("do_final: OnFinal Event done. (%d npc)\n", npc_event_doall("OnFinal"));

	return;
}

/*==========================================
 * map鯖終了時処理
 *------------------------------------------
 */
static int nick_db_final(void *key,void *data,va_list ap)
{
	char *nick;

	nullpo_retr(0, nick = (char *)data);

	aFree(nick);

	return 0;
}

static int charid_db_final(void *key,void *data,va_list ap)
{
	struct charid2nick *p;

	nullpo_retr(0, p = (struct charid2nick *)data);

	if(p->req)
		linkdb_final(&p->req);

	aFree(p);

	return 0;
}

void do_final(void)
{
	int i;
	unsigned int tick = gettick();

	chrif_mapactive(0);	// マップサーバー停止中

	guild_flush_expcache();				// ギルドExpをフラッシュ
	clif_foreachclient(chrif_disconnect_sub);	// ここで先にキャラを全て切断しておく
	chrif_flush_fifo();				// パケット送信

	do_final_extra();
	do_final_battle();
	do_final_memorial();
	do_final_npc();
	do_final_script();
	do_final_itemdb();
	do_final_storage();
	do_final_guild();
	do_final_clif();
	do_final_pc();
	do_final_bonus();
	do_final_party();
	do_final_booking();
	do_final_quest();
	do_final_pet();
	do_final_achieve();
	do_final_homun();
	do_final_merc();
	do_final_elem();
	do_final_friend();
	do_final_unit();
	do_final_mob();
	do_final_luascript();
	do_final_atcommand();

	for(i = 0; i < MAX_FLOORITEM; i++) {
		if(object[i] == NULL)
			continue;
		if(object[i]->type == BL_ITEM) {
			map_clearflooritem_timer(-1, tick, i, (void*)2);
		}
	}
	map_clear_delayitem_que();

	// 最後にこの内部でchar_fdを閉じる
	do_final_chrif();

	for(i = 0; i < map_num; i++) {
		if(map[i].gat) {
			aFree(map[i].gat);
			map[i].gat = NULL;
		}
		if(map[i].block)
			aFree(map[i].block);
		if(map[i].block_mob)
			aFree(map[i].block_mob);
	}

	if(map != NULL) {
		aFree(map);
		map = NULL;
	}
	map_num = 0;
	map_max = 0;
	map_mdmap_start = 0;

	if(waterlist) {
		aFree(waterlist);
		waterlist_num = 0;
		waterlist_max = 0;
	}

	if(freeblock_db)
		numdb_final(freeblock_db, freeblock_db_final);
	if(map_db)
		strdb_final(map_db, NULL);
	if(nick_db)
		strdb_final(nick_db, nick_db_final);
	if(charid_db)
		numdb_final(charid_db, charid_db_final);
	if(id_db)
		numdb_final(id_db, NULL);

	// メッセージの解放は一番最後
	do_final_msg();

	exit_dbn();
	do_final_timer();
}

/*==========================================
 * map鯖初期化の大元
 *------------------------------------------
 */
int do_init(int argc,char *argv[])
{
	int i;
	unsigned int tick = gettick();

	printf("Auriga Map Server [%s] v%d.%d.%d version %04d\n",
#ifdef TXT_ONLY
		"TXT",
#else
		"SQL",
#endif
		AURIGA_MAJOR_VERSION, AURIGA_MINOR_VERSION, AURIGA_REVISION,
		get_current_version()
	);

	for(i = 1; i < argc - 1; i += 2) {
		if(strcmp(argv[i], "--map_config") == 0 || strcmp(argv[i], "--map-config") == 0) {
			strncpy(map_conf_filename, argv[i+1], sizeof(map_conf_filename));
			map_conf_filename[sizeof(map_conf_filename)-1] = '\0';
		}
		else if(strcmp(argv[i], "--battle_config") == 0 || strcmp(argv[i], "--battle-config") == 0) {
			strncpy(battle_conf_filename, argv[i+1], sizeof(battle_conf_filename));
			battle_conf_filename[sizeof(battle_conf_filename)-1] = '\0';
		}
		else if(strcmp(argv[i], "--atcommand_config") == 0 || strcmp(argv[i], "--atcommand-config") == 0) {
			strncpy(atcommand_conf_filename, argv[i+1], sizeof(atcommand_conf_filename));
			atcommand_conf_filename[sizeof(atcommand_conf_filename)-1] = '\0';
		}
		else if(strcmp(argv[i], "--script_config") == 0 || strcmp(argv[i], "--script-config") == 0) {
			strncpy(script_conf_filename, argv[i+1], sizeof(script_conf_filename));
			script_conf_filename[sizeof(script_conf_filename)-1] = '\0';
		}
		else if(strcmp(argv[i], "--msg_config") == 0 || strcmp(argv[i], "--msg-config") == 0) {
			strncpy(msg_conf_filename, argv[i+1], sizeof(msg_conf_filename));
			msg_conf_filename[sizeof(msg_conf_filename)-1] = '\0';
		}
	}

	if(map_config_read(map_conf_filename)) {
		exit(1);
	}

	// メッセージの読み込みは一番最初
	msg_config_read(msg_conf_filename);

	chrif_setip();
	clif_setip();
	printf("MAP Server Tag: %s\n", map_server_tag);

	battle_config_read(battle_conf_filename);
	atcommand_config_read(atcommand_conf_filename);
	script_config_read(script_conf_filename);

	socket_set_httpd_page_connection_func(map_socket_ctrl_panel_func);

	id_db        = numdb_init();
	map_db       = strdb_init(16);
	nick_db      = strdb_init(24);
	charid_db    = numdb_init();
	freeblock_db = numdb_init();

	grfio_init(grf_path_txt);
	map_readallmap();

	add_timer_func_list(map_freeblock_timer);
	add_timer_func_list(map_clearflooritem_timer);
	add_timer_interval(tick+1000,map_freeblock_timer,0,NULL,600*1000);

	do_init_msg();
	do_init_atcommand();
	do_init_battle();
	do_init_chrif();
	do_init_luascript();
	do_init_clif();
	do_init_script();	// parse_script を呼び出す前にこれを呼ぶ
	do_init_skill();	// skill_dbを参照するのでpc,homun,merc,guild,npcより先
	do_init_itemdb();
	do_init_quest();
	do_init_mob();		// npcの初期化時内でmob_spawnして、mob_dbを参照するのでinit_npcより先
	do_init_npc();
	do_init_memorial();
	do_init_pc();
	do_init_bonus();
	do_init_party();
	do_init_booking();
	do_init_guild();
	do_init_storage();
	do_init_pet();
	do_init_homun();
	do_init_merc();
	do_init_elem();
	do_init_status();
	do_init_friend();
	do_init_ranking();
	do_init_unit();
	do_init_achieve();
	do_init_extra();

	luascript_config_read(luascript_conf_filename);
	map_pk_server(map_pk_server_flag);
	map_pk_nightmaredrop(map_pk_nightmaredrop_flag);
	map_pk_noteleport(map_pk_noteleport_flag);
	map_field_setting();
	npc_event_do_oninit();	// npcのOnInitイベント実行

	// for httpd support
	do_init_httpd();
	do_init_graph();
	graph_add_sensor("Uptime(days)",60*1000,uptime);
	graph_add_sensor("Memory Usage(KB)",60*1000,memmgr_usage);
	graph_add_sensor("Mob ai efficiency(%)",60*1000,mob_ai_hard_sensor);

	httpd_default_page(httpd_send_file);
	httpd_pages("/chat",clif_webchat);

	return 0;
}
