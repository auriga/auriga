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

// $Id: path.c,v 1.6 2003/06/29 05:52:56 lemit Exp $

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"
#include "path.h"
#include "battle.h"
#include "nullpo.h"

#define MAX_BLOWNPOS 20
#define MAX_HEAP 150

struct tmp_path {
	short x,y,dist,before,cost,flag;
};

#define calc_index(x,y) (((x)+(y)*MAX_WALKPATH) & (MAX_WALKPATH*MAX_WALKPATH-1))

// 向き計算用
const int dirx[8] = { 0,-1,-1,-1, 0, 1, 1, 1 };
const int diry[8] = { 1, 1, 0,-1,-1,-1, 0, 1 };

static const unsigned char walk_choice[3][3] =
{
	{ 1, 0, 7 },
	{ 2, 8, 6 },
	{ 3, 4, 5 },
};

/*==========================================
 * 経路探索補助heap push
 *------------------------------------------
 */
static void push_heap_path(int *heap,struct tmp_path *tp,int idx)
{
	int i, h = heap[0];

	heap[0]++;

	for(i = (h-1)/2; h > 0 && tp[idx].cost < tp[heap[i+1]].cost; i = (h-1)/2) {
		heap[h+1] = heap[i+1];
		h = i;
	}
	heap[h+1] = idx;
}

/*==========================================
 * 経路探索補助heap update
 * costが減ったので根の方へ移動
 *------------------------------------------
 */
static void update_heap_path(int *heap,struct tmp_path *tp,int idx)
{
	int i, h;

	for(h = 0; h < heap[0]; h++) {
		if(heap[h+1] == idx)
			break;
	}
	if(h == heap[0]) {
		fprintf(stderr,"update_heap_path bug\n");
		exit(1);
	}
	for(i = (h-1)/2; h > 0 && tp[idx].cost < tp[heap[i+1]].cost; i = (h-1)/2) {
		heap[h+1] = heap[i+1];
		h = i;
	}
	heap[h+1] = idx;
}

/*==========================================
 * 経路探索補助heap pop
 *------------------------------------------
 */
static int pop_heap_path(int *heap,struct tmp_path *tp)
{
	int i, k, h = 0;
	int ret, last;

	if(heap[0] <= 0)
		return -1;

	ret  = heap[1];
	last = heap[heap[0]];
	heap[0]--;

	for(k = 2; k < heap[0]; k = k*2+2) {
		if(tp[heap[k+1]].cost > tp[heap[k]].cost)
			k--;
		heap[h+1] = heap[k+1];
		h = k;
	}
	if(k == heap[0]) {
		heap[h+1] = heap[k];
		h = k-1;
	}

	for(i = (h-1)/2; h > 0 && tp[heap[i+1]].cost > tp[last].cost; i = (h-1)/2) {
		heap[h+1] = heap[i+1];
		h = i;
	}
	heap[h+1] = last;

	return ret;
}

/*==========================================
 * 現在の点のcost計算
 *------------------------------------------
 */
static int calc_cost(struct tmp_path *p,int x1,int y1)
{
	int xd = abs(x1 - p->x);
	int yd = abs(y1 - p->y);

	return (xd + yd) * 10 + p->dist;
}

/*==========================================
 * 必要ならpathを追加/修正する
 *------------------------------------------
 */
static int add_path(int *heap,struct tmp_path *tp,int x,int y,int dist,int before,int cost)
{
	int i;

	i = calc_index(x,y);

	if(tp[i].x == x && tp[i].y == y) {
		if(tp[i].dist > dist) {
			tp[i].dist   = dist;
			tp[i].before = before;
			tp[i].cost   = cost;
			if(tp[i].flag)
				push_heap_path(heap,tp,i);
			else
				update_heap_path(heap,tp,i);
			tp[i].flag = 0;
		}
		return 0;
	}

	if(tp[i].x || tp[i].y)
		return 1;

	tp[i].x      = x;
	tp[i].y      = y;
	tp[i].dist   = dist;
	tp[i].before = before;
	tp[i].cost   = cost;
	tp[i].flag   = 0;
	push_heap_path(heap,tp,i);

	return 0;
}

/*==========================================
 * (x,y)が移動不可能地帯かどうか
 * flag 0x10000 遠距離攻撃判定
 *------------------------------------------
 */
#define can_place(m,x,y,flag) ( map_getcellp(m,x,y,CELL_CHKPASS) || ((flag & 0x10000) && map_getcellp(m,x,y,CELL_CHKGROUND)) )

/*==========================================
 * (x0,y0)から(x1,y1)へ1歩で移動可能か計算
 *------------------------------------------
 */
static int can_move(struct map_data *m,int x0,int y0,int x1,int y1,int flag)
{
	if(x1 < 0 || y1 < 0 || x1 >= m->xs || y1 >= m->ys)
		return 0;
	if(!can_place(m,x0,y0,flag))
		return 0;
	if(!can_place(m,x1,y1,flag))
		return 0;
	if(x0 == x1 || y0 == y1)
		return 1;
	if(!can_place(m,x0,y1,flag) || !can_place(m,x1,y0,flag))
		return 0;

	return 1;
}

/*==========================================
 * (x0,y0)から(dx,dy)方向へcountセル分
 * 吹き飛ばしたあとの座標を取得
 *	flag = 0: 壁補正あり、1: 壁補正なし
 *------------------------------------------
 */
int path_blownpos(int m,int x0,int y0,int dx,int dy,int count,int flag)
{
	struct map_data *md = &map[m];

	if(!map[m].gat)
		return -1;

	if(count > MAX_BLOWNPOS) {
		if(battle_config.error_log)
			printf("path_blownpos: count too many %d !\n",count);
		count = MAX_BLOWNPOS;
	}
	if(dx > 1 || dx < -1 || dy > 1 || dy < -1) {
		if(battle_config.error_log)
			printf("path_blownpos: illegal dx=%d or dy=%d !\n",dx,dy);
		dx = (dx >= 0)? 1: ((dx < 0)? -1: 0);
		dy = (dy >= 0)? 1: ((dy < 0)? -1: 0);
	}

	while( (count--) > 0 && (dx || dy) ) {
		if( !can_move(md,x0,y0,x0+dx,y0+dy,0) ) {
			int fx, fy;
			if( flag )
				break;
			fx = (dx != 0 && can_move(md,x0,y0,x0+dx,y0,0));
			fy = (dy != 0 && can_move(md,x0,y0,x0,y0+dy,0));
			if( fx && fy ) {
				if(atn_rand()&1) dx = 0;
				else             dy = 0;
			}
			if( !fx ) dx = 0;
			if( !fy ) dy = 0;
		}
		x0 += dx;
		y0 += dy;
	}
	return (x0<<16)|y0;
}

/*==========================================
 * 遠距離攻撃が可能かどうかを返す
 *------------------------------------------
 */
#define swap(x,y) { int t; t = x; x = y; y = t; }

int path_search_long_real(struct shootpath_data *spd,int m,int x0,int y0,int x1,int y1,cell_t flag)
{
	int dx, dy;
	int wx = 0, wy = 0;
	int weight;
	struct map_data *md = &map[m];

	if(!map[m].gat)
		return 0;

	dx = (x1 - x0);
	if(dx < 0) {
		swap(x0, x1);
		swap(y0, y1);
		dx = -dx;
	}
	dy = (y1 - y0);

	if(spd) {
		spd->rx   = spd->ry = 0;
		spd->len  = 1;
		spd->x[0] = x0;
		spd->y[0] = y0;
	}

	if(map_getcellp(md,x1,y1,flag))
		return 0;

	if(dx > abs(dy)) {
		weight = dx;
		if (spd)
			spd->ry = 1;
	} else {
		weight = abs(y1 - y0);
		if (spd)
			spd->rx = 1;
	}

	while(x0 != x1 || y0 != y1) {
		if(map_getcellp(md,x0,y0,flag))
			return 0;
		wx += dx;
		wy += dy;
		if(wx >= weight) {
			wx -= weight;
			x0 ++;
		}
		if(wy >= weight) {
			wy -= weight;
			y0 ++;
		} else if(wy < 0) {
			wy += weight;
			y0 --;
		}
		if(spd && spd->len < MAX_WALKPATH) {
			spd->x[spd->len] = x0;
			spd->y[spd->len] = y0;
			spd->len++;
		}
	}

	return 1;
}

/*==========================================
 * path探索 (x0,y0)->(x1,y1)
 *------------------------------------------
 */
int path_search_real(struct walkpath_data *wpd,int m,int x0,int y0,int x1,int y1,int easy,cell_t flag)
{
	int x, y, i = 0;
	int dx, dy;
	struct map_data *md = &map[m];

	if(!map[m].gat)
		return -1;

	// path_search2() の場合map_getcellp() の返り値は常に0
	if(x0 < 0 || x0 >= md->xs || y0 < 0 || y0 >= md->ys || map_getcellp(md,x0,y0,flag))
		return -1;
	if(x1 < 0 || x1 >= md->xs || y1 < 0 || y1 >= md->ys || map_getcellp(md,x1,y1,flag))
		return -1;

	// easy
	// この内部では、0 <= x+dx < sx, 0 <= y+dy < sy は保証されている
	dx = (x1 - x0 < 0) ? -1 : 1;
	dy = (y1 - y0 < 0) ? -1 : 1;

	x = x0;
	y = y0;
	while(x != x1 || y != y1) {
		if(i >= MAX_WALKPATH)
			return -1;
		if(x != x1 && y != y1) {
			if(map_getcellp(md,x+dx,y   ,flag))
				break;
			if(map_getcellp(md,x   ,y+dy,flag))
				break;
			if(map_getcellp(md,x+dx,y+dy,flag))
				break;
			x += dx;
			y += dy;
			if(wpd)
				wpd->path[i++] = walk_choice[-dy+1][dx+1];
		} else if(x != x1) {
			if(map_getcellp(md,x+dx,y,flag))
				break;
			x += dx;
			if(wpd)
				wpd->path[i++] = walk_choice[1][dx+1];
		} else { // y!=y1
			if(map_getcellp(md,x,y+dy,flag))
				break;
			y += dy;
			if(wpd)
				wpd->path[i++] = walk_choice[-dy+1][1];
		}
		if(x == x1 && y == y1) {
			if(wpd) {
				wpd->path_len = i;
				wpd->path_pos = 0;
			}
			return 0;
		}
	}

	if(!easy) {
		int xs, ys, rp;
		int len, j;
		int heap[MAX_HEAP+1];
		struct tmp_path tp[MAX_WALKPATH * MAX_WALKPATH];

		memset(tp, 0, sizeof(tp));

		i            = calc_index(x0,y0);
		tp[i].x      = x0;
		tp[i].y      = y0;
		tp[i].dist   = 0;
		tp[i].before = 0;
		tp[i].cost   = calc_cost(&tp[i],x1,y1);
		tp[i].flag   = 0;
		heap[0]      = 0;
		push_heap_path(heap,tp,calc_index(x0,y0));

		// あらかじめ１減算しておく
		xs = md->xs - 1;
		ys = md->ys - 1;

		while(1) {
			int e = 0, f = 0;
			int dist, cost;
			int dc[4] = { 0, 0, 0, 0 };

			if(heap[0] == 0)
				return -1;

			rp = pop_heap_path(heap,tp);
			x  = tp[rp].x;
			y  = tp[rp].y;
			if(x == x1 && y == y1)
				break;

			dist = tp[rp].dist + 10;
			cost = tp[rp].cost;

			// dc[0] : y++ の時のコスト増分
			// dc[1] : x-- の時のコスト増分
			// dc[2] : y-- の時のコスト増分
			// dc[3] : x++ の時のコスト増分

			if(y < ys && !map_getcellp(md,x  ,y+1,flag)) {
				f |= 1;
				dc[0] = (y >= y1 ? 20 : 0);
				e += add_path(heap,tp,x  ,y+1,dist,rp,cost+dc[0]);	// (x,   y+1)
			}
			if(x > 0  && !map_getcellp(md,x-1,y  ,flag)) {
				f |= 2;
				dc[1] = (x <= x1 ? 20 : 0);
				e += add_path(heap,tp,x-1,y  ,dist,rp,cost+dc[1]);	// (x-1, y  )
			}
			if(y > 0  && !map_getcellp(md,x  ,y-1,flag)) {
				f |= 4;
				dc[2] = (y <= y1 ? 20 : 0);
				e += add_path(heap,tp,x  ,y-1,dist,rp,cost+dc[2]);	// (x  , y-1)
			}
			if(x < xs && !map_getcellp(md,x+1,y  ,flag)) {
				f |= 8;
				dc[3] = (x >= x1 ? 20 : 0);
				e += add_path(heap,tp,x+1,y  ,dist,rp,cost+dc[3]);	// (x+1, y  )
			}
			if( (f & (2+1)) == (2+1) && !map_getcellp(md,x-1,y+1,flag))
				e += add_path(heap,tp,x-1,y+1,dist+4,rp,cost+dc[1]+dc[0]-6);	// (x-1, y+1)
			if( (f & (2+4)) == (2+4) && !map_getcellp(md,x-1,y-1,flag))
				e += add_path(heap,tp,x-1,y-1,dist+4,rp,cost+dc[1]+dc[2]-6);	// (x-1, y-1)
			if( (f & (8+4)) == (8+4) && !map_getcellp(md,x+1,y-1,flag))
				e += add_path(heap,tp,x+1,y-1,dist+4,rp,cost+dc[3]+dc[2]-6);	// (x+1, y-1)
			if( (f & (8+1)) == (8+1) && !map_getcellp(md,x+1,y+1,flag))
				e += add_path(heap,tp,x+1,y+1,dist+4,rp,cost+dc[3]+dc[0]-6);	// (x+1, y+1)

			tp[rp].flag = 1;
			if(e || heap[0] >= MAX_HEAP - 5)
				return -1;
		}

		for(len = 0, i = rp; len < MAX_WALKPATH && i != calc_index(x0,y0); i = tp[i].before, len++);
		if(len >= MAX_WALKPATH)
			return -1;

		if(wpd == NULL)
			return 0;

		wpd->path_len = len;
		wpd->path_pos = 0;
		for(i = rp, j = len-1; j >= 0; i = tp[i].before, j--) {
			int tx = tp[i].x - tp[tp[i].before].x;
			int ty = tp[i].y - tp[tp[i].before].y;
			wpd->path[j] = walk_choice[-ty+1][tx+1];
		}
#if 0
		// test
		{
			x = x0; y = y0;
			for(i = 0; i < wpd->path_len; i++) {
				x += dirx[ wpd->path[i] ];
				y += diry[ wpd->path[i] ];
				if( map_getcellp(md,x,y,flag) ) {
					printf("path_search_real: cannot move(%d, %d)\n", x, y);
					return -1;
				}
			}
			if( x != x1 || y != y1 ) {
				printf("path_search_real: dest position is wrong. ok:(%d, %d) ng:(%d,%d)\n", x1, y1, x, y);
				return -1;
			}
		}
#endif
		return 0;
	}

	return -1;
}

/*==========================================
 *
 *------------------------------------------
 */
int path_check_dir(int s_dir,int t_dir)
{
	if( s_dir == t_dir || s_dir == ((t_dir-1)&0x07) || s_dir == ((t_dir+1)&0x07) )
		return 0;

	return 1;
}

/*==========================================
 * 彼我の方向を計算
 *------------------------------------------
 */
int path_calc_dir(struct block_list *src,int x,int y)
{
	int dir = 0;
	int dx, dy;

	nullpo_retr(0, src);

	dx = x - src->x;
	dy = y - src->y;

	if(dx == 0 && dy == 0) {
		// 彼我の場所一致
		dir = 0;	// 上
	}
	else if(dx >= 0 && dy >= 0) {
		// 方向的に右上
		if(dx * 3 - 1 < dy)   dir = 0;	// 上
		else if(dx > dy * 3)  dir = 6;	// 右
		else                  dir = 7;	// 右上
	}
	else if(dx >= 0 && dy <= 0) {
		// 方向的に右下
		if(dx * 3 - 1 < -dy)  dir = 4;	// 下
		else if(dx > -dy * 3) dir = 6;	// 右
		else                  dir = 5;	// 右下
	}
	else if(dx <= 0 && dy <= 0) {
		// 方向的に左下
		if(dx * 3 + 1 > dy)   dir = 4;	// 下
		else if(dx < dy * 3)  dir = 2;	// 左
		else                  dir = 3;	// 左下
	}
	else {
		// 方向的に左上
		if(-dx * 3 - 1 < dy)  dir = 0;	// 上
		else if(-dx > dy * 3) dir = 2;	// 左
		else                  dir = 1;	// 左上
	}
	return dir;
}

/*==========================================
 * 二点間の距離を返す
 * 戻りは整数で0以上
 *------------------------------------------
 */
int path_distance(int x0,int y0,int x1,int y1)
{
	int dx,dy;

	dx = abs(x0 - x1);
	dy = abs(y0 - y1);

	return (dx > dy) ? dx : dy;
}
