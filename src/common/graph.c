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

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "timer.h"
#include "httpd.h"
#include "graph.h"
#include "grfio.h"
#include "malloc.h"

#define GRP_WIDTH    (640-48)				// グラフの幅
#define GRP_HEIGHT   (240-20)				// グラフの高さ
#define graph_rgb(r,g,b) (((r) << 16) | ((g) << 8) | (b))
#define GRP_COLOR    graph_rgb(0,0,255)		// グラフの色

/* フォント類(8*16pixel)。みっともないので、誰か書き直しキボンヌ */
static const char *graph_fonts[16] = {
/* 0123456789. */
	"xxxxxxx      xx xxxxxxx xxxxxxx xx   xx xxxxxxx xxxxxxx xxxxxxx xxxxxxx xxxxxxx         ",
	"xxxxxxx      xx xxxxxxx xxxxxxx xx   xx xxxxxxx xxxxxxx xxxxxxx xxxxxxx xxxxxxx         ",
	"xx   xx      xx      xx      xx xx   xx xx      xx      xx   xx xx   xx xx   xx         ",
	"xx   xx      xx      xx      xx xx   xx xx      xx      xx   xx xx   xx xx   xx         ",
	"xx   xx      xx      xx      xx xx   xx xx      xx      xx   xx xx   xx xx   xx         ",
	"xx   xx      xx xxxxxxx xxxxxxx xxxxxxx xxxxxxx xxxxxxx xx   xx xxxxxxx xxxxxxx         ",
	"xx   xx      xx xxxxxxx xxxxxxx xxxxxxx xxxxxxx xxxxxxx xx   xx xxxxxxx xxxxxxx         ",
	"xx   xx      xx xx           xx      xx      xx xx   xx      xx xx   xx      xx         ",
	"xx   xx      xx xx           xx      xx      xx xx   xx      xx xx   xx      xx         ",
	"xx   xx      xx xx           xx      xx      xx xx   xx      xx xx   xx      xx xxxx    ",
	"xx   xx      xx xx           xx      xx      xx xx   xx      xx xx   xx      xx xxxx    ",
	"xxxxxxx      xx xxxxxxx xxxxxxx      xx xxxxxxx xxxxxxx      xx xxxxxxx xxxxxxx xxxx    ",
	"xxxxxxx      xx xxxxxxx xxxxxxx      xx xxxxxxx xxxxxxx      xx xxxxxxx xxxxxxx xxxx    ",
	"                                                                                        ",
	"                                                                                        ",
	"                                                                                        "
};

struct graph {
	int   width;
	int   height;
	int   pallet_count;
	int   png_len;
	int   png_dirty;
	unsigned char* raw_data;
	unsigned char* png_data;
	double       * graph_value;
	double         graph_max;
	double         graph_max_value;
	int  line_count;
	int *line_pos;
};

static void graph_write_dword(unsigned char* p,unsigned int v)
{
	p[0] = (unsigned char)((v >> 24) & 0xFF);
	p[1] = (unsigned char)((v >> 16) & 0xFF);
	p[2] = (unsigned char)((v >>  8) & 0xFF);
	p[3] = (unsigned char)(v         & 0xFF);
}

static struct graph* graph_create(unsigned int x, unsigned int y)
{
	struct graph *g = (struct graph*)aCalloc(sizeof(struct graph),1);

	if(g == NULL) return NULL;
	// 256 * 3   : パレットデータ
	// x * y * 2 : イメージのバッファ
	// 256       : チャンクデータなどの予備
	g->png_data = (unsigned char *)aMalloc(4 * 256 + (x + 1) * y * 2);
	g->raw_data = (unsigned char *)aCalloc( (x + 1) * y , sizeof(unsigned char));
	memcpy(
		g->png_data,
		"\x89\x50\x4E\x47\x0D\x0A\x1A\x0A\x00\x00\x00\x0D\x49\x48\x44\x52"
		"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\x08\x03\x00\x00\x00\xFF\xFF\xFF"
		"\xFF\x00\x00\x00\x03\x50\x4C\x54\x45\xFF\xFF\xFF\xA7\xC4\x1B\xC8",0x30
	);
	graph_write_dword(g->png_data + 0x10,x);
	graph_write_dword(g->png_data + 0x14,y);
	graph_write_dword(g->png_data + 0x1D,(unsigned int)grfio_crc32(g->png_data+0x0C,0x11));
	g->pallet_count = 1;
	g->width        = x;
	g->height       = y;
	g->png_dirty    = 1;
	g->line_pos     = NULL;
	g->line_count   = 0;
	g->graph_value  = (double *)aCalloc(x,sizeof(double));
	g->graph_max    = 0;
	g->graph_max_value = 0;

	return g;
}

// パレットの設定
static void graph_pallet(struct graph* g, int idx, unsigned int c)
{
	if (g == NULL || c >= 256)
		return;

	if (g->pallet_count <= idx) {
		memset(g->png_data + 0x29 + 3 * g->pallet_count,0,(idx - g->pallet_count) * 3);
		g->pallet_count = idx + 1;
	}
	g->png_data[0x29 + idx * 3    ] = (unsigned char)((c >> 16) & 0xFF); // R
	g->png_data[0x29 + idx * 3 + 1] = (unsigned char)((c >>  8) & 0xFF); // G
	g->png_data[0x29 + idx * 3 + 2] = (unsigned char)( c        & 0xFF); // B
	graph_write_dword(g->png_data + 0x21,g->pallet_count * 3);
	graph_write_dword(
		g->png_data + 0x29 + g->pallet_count * 3,
		grfio_crc32(g->png_data + 0x25,g->pallet_count * 3 + 4)
	);
	g->png_dirty = 1;

	return;
}

// ピクセル色の設定
static void graph_setpixel(struct graph* g, int x, int y, int color)
{
	if(g == NULL || color >= 256)
		return;
	if(x < 0) x = 0;
	if(y < 0) y = 0;
	if(x >= g->width)  { x = g->width  - 1; }
	if(y >= g->height) { y = g->height - 1; }
	if(color >= g->pallet_count) { graph_pallet(g,color,graph_rgb(0,0,0)); }

	g->raw_data[y * (g->width + 1) + x + 1] = (unsigned char)color;
	g->png_dirty = 1;

	return;
}

// ピクセル色の取得
/* -- actually not used
static int graph_getpixel(struct graph* g, int x, int y)
{
	if(x < 0) x = 0;
	if(y < 0) y = 0;
	if(x >= g->width)  { x = g->width  - 1; }
	if(y >= g->height) { y = g->height - 1; }

	return g->raw_data[y * (g->width + 1) + x + 1];
}*/

static const unsigned char* graph_output(struct graph* g,int *len)
{
	unsigned long inflate_len;
	unsigned char *p;

	if(g == NULL) return NULL;

	if(g->png_dirty == 0) {
		*len = g->png_len;
		return g->png_data;
	}

	p = g->png_data + 0x2D + 3 * g->pallet_count;
	inflate_len = (g->width + 1) * g->height;
	memcpy(p + 4,"IDAT",4);
	encode_zip(p + 8,&inflate_len,g->raw_data,(g->width + 1) * g->height);
	graph_write_dword(p, (unsigned int)inflate_len);
	graph_write_dword(p + 8 + inflate_len,grfio_crc32(p + 4, (unsigned int)(inflate_len + 4)));

	p += 0x0C + inflate_len;
	memcpy(p,"\x00\x00\x00\x00\x49\x45\x4E\x44\xAE\x42\x60\x82",0x0C);
	p += 0x0C;
	g->png_len   = (int)(p - g->png_data);
	g->png_dirty = 0;
	*len = g->png_len;

	return g->png_data;
}

static void graph_free(struct graph* g)
{
	if(g != NULL) {
		aFree(g->png_data);
		aFree(g->raw_data);
		aFree(g->graph_value);
		aFree(g->line_pos);
		aFree(g);
	}

	return;
}

#define graph_raw_data(g,x,y) (&(g)->raw_data[(y) * ((g)->width+1)+(x)+1])

// 四角形の描画
static void graph_square(struct graph* g,int x,int y,int xe,int ye,int color)
{
	int i;

	if(g == NULL) return;

	if(x < 0) { x = 0; }
	if(y < 0) { y = 0; }
	if(xe >= g->width)  { xe = g->width  - 1; }
	if(ye >= g->height) { ye = g->height - 1; }
	graph_setpixel(g,x,y,color);
	for(i = y;i < ye ; i++) {
		memset(graph_raw_data(g,x,i),color,xe-x+1);
	}

	return;
}

// 画像のスクロール（ただし、対象はグラフの部分のみ）
static void graph_scroll(struct graph* g,int n,int color)
{
	int y;

	if(g == NULL) return;

	for(y = 0; y <= g->height - 20; y++) {
		// 末端のピクセルは含まないので注意
		memmove(
			graph_raw_data(g,48  ,y),
			graph_raw_data(g,48+n,y),
			g->width - n - 48 - 1
		);
		memset(graph_raw_data(g,g->width - n - 1, y), color, n);
	}
	graph_setpixel(g,g->width-2,0,color);

	return;
}

// 直線の描画
static void graph_line(struct graph* g, int x0, int y0, int x1, int y1,int color)
{
	int i;

	if( x0 == x1 ) {
		for(i = y0; i <= y1; i++)
			graph_setpixel(g,x0,i,color);
	} else if( y0 == y1 ) {
		for(i = x0; i <= x1; i++)
			graph_setpixel(g,i,y0,color);
	} else {
		// 斜めの線は書かないのでとりあえず無視
	}

	return;
}

// 文字表示
static void graph_drawtext(struct graph *g, const char *str, int x, int y, int color)
{
	int i, j;
	const char *fonts = "0123456789.";

	while( *str ) {
		const char *p = strchr(fonts, *str);
		if( p ) {
			int fontno = (int)(p - fonts);
			for(i = 0; i < 16; i++) {
				for(j = 0; j < 8; j++) {
					if( graph_fonts[i][8*fontno+j] == 'x' ) {
						graph_setpixel(g, x+j, y+i, color);
					}
				}
			}
		}
		str++; x+=8;
	}

	return;
}

static void graph_data(struct graph* g,double value)
{
	int i, start;

	if(g == NULL) return;
	if(value <= 0) value = 0;
	memmove(&g->graph_value[0],&g->graph_value[1],sizeof(double) * (GRP_WIDTH - 1));
	g->graph_value[GRP_WIDTH - 1] = value;
	if(value > g->graph_max_value)
		g->graph_max_value = value;

	if(g->line_pos == NULL || value > g->graph_max) {
		int div_num, cutf = 0;
		double base;
		// 最大値が更新されたか最初の描画なので、一端画面を消去して
		// ゼロから書き直す

		graph_square(g,0,0,g->width,g->height,0);
		graph_line(g,47,0,47,g->height-20,1);
		graph_line(g,g->width-1,0,g->width-1,g->height-20,1);

		// 最上位桁を10の整数乗単位で切り捨て( 3 -> 1, 48 -> 10, 100 -> 100 )
		if( value < 0.04 ) {
			base = 0.01;
			div_num  = 4;
		} else {
			base = pow(10.0, floor(log10(value) ) );
			div_num  = (int)ceil(value / base);
		}
		// 分割数の調整( 3 - 5 )
		if( div_num <= 2 ) { div_num *= 2;  base /= 2;       }
		if( div_num <= 2 ) { div_num *= 2;  base /= 2;       }
		if( div_num >  5 ) { div_num = (div_num+1)/2; base *= 2; }
		aFree( g->line_pos );
		g->line_pos   = (int *)aMalloc( div_num < 0 ? 4 : (div_num+1) * sizeof(int) );
		g->line_count = div_num+1;
		g->graph_max  = div_num * base; // グラフ上の最大値

		// 軸上の目盛りを打つ
		for(i = div_num; i >= 0; i--) {
			char buf[256];
			int  ypos;
			// 目盛り上の横線の位置を計算
			ypos = (GRP_HEIGHT)*(div_num-i)/div_num;
			g->line_pos[i] = ypos;

			// 目盛りの文字を描画
			sprintf(buf, "%.2f", i * base );
			if( cutf || strlen(buf) > 6 ) {
				// 文字が長すぎるので、小数点以下を削る
				char *p = strchr(buf, '.');
				if( p ) *p = 0;
				cutf = 1;
			}
			if( strlen(buf) < 6 ) {
				// ６文字に満たないので先頭にスペースを付加する
				size_t len = 6 - strlen(buf);
				char buf2[256];
				memset(buf2, ' ', len);
				buf2[len] = 0;
				strcat(buf2, buf);
				strcpy(buf, buf2);
			} else {
				buf[6] = 0; // ６文字以降をカット
			}
			graph_drawtext(g,buf,0,ypos,1);
		}
		start = 48;
	} else {
		// スクロールしてポイント打つ
		graph_scroll(g,1,0);
		start = g->width - 2;
	}
	for(i = start; i < g->width - 1; i++) {
		int h0 = (int)(g->graph_value[(i==48?0:i-49)] * (GRP_HEIGHT) / g->graph_max);
		int h1 = (int)(g->graph_value[i-48]           * (GRP_HEIGHT) / g->graph_max);
		int h2 = (h0 < h1 ? 1 : -1);
		int j;

		for(j = 0; j < g->line_count; j++) {
			graph_setpixel(g,i,g->line_pos[j],1);
		}
		for(j = h0; j != h1; j += h2) {
			graph_setpixel(g,i,GRP_HEIGHT - j,2);
		}
		graph_setpixel(g,i,GRP_HEIGHT - h1,2);
	}

	return;
}

// 上の関数群を利用して、自動的にグラフを作成するタイマー群

struct graph_sensor {
	struct graph* graph;
	char* str;
	int   tid;
	int   interval;
	double (*func)(void);
};

static struct graph_sensor *sensor = NULL;
static int                  sensor_max = 0;

static int graph_timer(int tid,unsigned int tick,int id,void *data)
{
	if(id >= 0 && id < sensor_max)
		graph_data(sensor[id].graph,sensor[id].func());

	return 0;
}

void graph_add_sensor(const char* string, int interval, double (*callback_func)(void))
{
	struct graph *g = graph_create(GRP_WIDTH+48,GRP_HEIGHT+20);
	unsigned int tick = gettick();

	if (g == NULL) {
		printf("graph_add_sensor: Unable to add sensor for graph '%s'.\n", string);
		return;
	}

	graph_pallet(g,1,graph_rgb(0,0,0));
	graph_pallet(g,2,GRP_COLOR);

	sensor = (struct graph_sensor *)aRealloc(sensor, sizeof(struct graph_sensor) * (sensor_max + 1));
	sensor[sensor_max].graph    = g;
	sensor[sensor_max].str      = (char *)aStrdup(string);
	sensor[sensor_max].func     = callback_func;
	sensor[sensor_max].tid      = add_timer_interval(tick,graph_timer,sensor_max,NULL,interval);
	sensor[sensor_max].interval = interval;
	sensor_max++;

	return;
}

static void graph_parse_httpd(struct httpd_session_data *sd,const char* url)
{
	char *graph_no = httpd_get_value(sd,"id");
	int  id        = atoi(graph_no);

	if(id > 0 && id <= sensor_max) {
		// output graph
		int len = 0;
		const char* data = graph_output(sensor[id-1].graph,&len);
		if(data)
			httpd_send(sd,200,"image/png",len,data);
	} else {
		// output html
		char buf[8192];
		char *p = buf;
		int  i;
		p += sprintf(p,"<html><head><title>Auriga Sensors</title></head>\n\n<body>\n");
		p += sprintf(p,"<h1>Auriga Sensors</h1>\n\n");
		for(i = 0; i < sensor_max; i++) {
			struct graph *g = sensor[i].graph;
			p += sprintf(p,"<h2>%s</h2>\n\n",sensor[i].str);
			p += sprintf(
				p,"<p><img src=\"/graph?id=%d\" width=\"%d\" height=\"%d\"></p>\n",
				i + 1,GRP_WIDTH+48,GRP_HEIGHT+20
			);
			p += sprintf(
				p,"<p>Now: %.2f Max: %.2f Interval: %d sec</p>\n\n",
				g->graph_value[GRP_WIDTH - 1],g->graph_max_value,sensor[i].interval / 1000
			);
		}
		p += sprintf(p,"</body></html>\n");
		httpd_send(sd,200,"text/html",(int)(p - buf),buf);
	}
	aFree(graph_no);

	return;
}

static void do_final_graph(void)
{
	int i;

	for(i = 0; i < sensor_max; i++) {
		graph_free(sensor[i].graph);
		aFree(sensor[i].str);
		delete_timer(sensor[i].tid,graph_timer);
	}
	aFree(sensor);
	sensor_max = 0;

	return;
}

void do_init_graph(void)
{
	grfio_load_zlib();
	httpd_pages("/graph",graph_parse_httpd);
	add_timer_func_list(graph_timer);
	atexit(do_final_graph);

	return;
}
