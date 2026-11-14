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
#include <ctype.h>

#include "utils.h"
#include "mmo.h"
#include "malloc.h"


/*==========================================
 * 0b -> 2進数変換対応型strtoul
 *------------------------------------------
 */
unsigned long strtobxul(const char *s, char **endptr, int base)
{
	unsigned long ret;
	int i = 0;

	while(isspace(s[i])) {
		i++;
	}

	if(s[i] == '-' || s[i] == '+') {
		i++;
	}
	if(s[i] == '0' && (s[i+1] == 'b' || s[i+1] == 'B')) {
		// 2進数処理
		char *buf = (char *)aStrdup(s);
		buf[i+1] = '0';	// 0b を 00 にする
		ret = strtoul(buf, endptr, 2);
		if(endptr) {
			*endptr = (char *)&s[*endptr - buf];
		}
		aFree(buf);
	} else {
		ret = strtoul(s, endptr, base);
	}

	return ret;
}

/*==========================================
 * Hex Dump
 *  標準出力の表示をスムーズにするため
 *  自前で完全バッファリングする
 *------------------------------------------
 */
void hex_dump(FILE *fp, const unsigned char *buf, size_t len)
{
	size_t i, j;
	char *output, *p;

	{
		const size_t output_size = (3 + (len ? ((len - 1) / 16) : 0)) * 96;
		output = (char *)aCalloc(output_size, sizeof(char));	// 1行あたり96文字として計算

		auriga_strlcpy(output, "      00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F   0123456789ABCDEF" NEWLINE, output_size);
		auriga_strlcat(output, "----  -----------------------------------------------   ----------------", output_size);

		p = output + strlen(output);
	for(i = 0; i < len; i += 16) {
		p += snprintf(p, (output + output_size) - p, NEWLINE "%04lX  ", (unsigned long)i);
		for(j = i; j < i + 16; j++) {
			if(j < len) {
				p += snprintf(p, (output + output_size) - p, "%02x ", buf[j]);
			} else {
				p += snprintf(p, (output + output_size) - p, "   ");
			}
		}
		*p++ = ' ';
		*p++ = ' ';

		for(j = i; j < i + 16; j++) {
			if(j < len)
				*p++ = (buf[j] < 0x20) ? '.' : buf[j];
			else
				*p++ = ' ';
		}
	}
	auriga_strlcat(p, NEWLINE, (output + output_size) - p);
	}

	fputs(output, fp);
	fflush(fp);

	aFree(output);
}

/*==========================================
 * 安全な文字列ユーティリティ
 *------------------------------------------
 */
size_t auriga_strlcpy(char *dst, const char *src, size_t siz)
{
    size_t src_len = strlen(src);
    if (siz != 0) {
        size_t copy_len = (src_len >= siz) ? (siz - 1) : src_len;
        if (copy_len > 0) {
            memcpy(dst, src, copy_len);
        }
        dst[copy_len] = '\0';
    }
    return src_len;
}

size_t auriga_strlcat(char *dst, const char *src, size_t siz)
{
    size_t dst_len = strlen(dst);
    size_t src_len = strlen(src);
    if (dst_len < siz) {
        size_t space = siz - dst_len - 1;
        size_t copy_len = (src_len > space) ? space : src_len;
        if (copy_len > 0) {
            memcpy(dst + dst_len, src, copy_len);
            dst[dst_len + copy_len] = '\0';
        } else {
            dst[dst_len] = '\0';
        }
    }
    return dst_len + src_len;
}

/*==========================================
 * 32bit線形合同法(戻り値は24ビット有効)
 *------------------------------------------
 */
#ifdef RANDOM32
static int seed32 = 1;

void atn_int24_srandom32( int seed )
{
	seed32 = seed;
}
int atn_int24_random32(void)
{
	seed32 = seed32 * 1103515245 + 12345;
	return ( seed32 >> 8 )&0x00ffffff;
}
#endif	// ifdef RANDOM32

/*==========================================
 * 64bit線形合同法(戻り値は31ビット有効)
 *------------------------------------------
 */
#ifdef RANDOM64
static int64 seed64 = 0x1234ABCD330E;

void atn_int31_srandom64( int seed )
{
	seed64 = seed;
	seed64 = (seed64<<16)+0x330E;
}
int atn_int31_random64(void)
{
	seed64 = seed64 * 0x5DEECE66D + 0xB;
	return (int)( seed64>>17 )&0x7FFFFFFF;
}
#endif	// ifdef RANDOM64

/*==========================================
 * メルセンヌツイスター
 *------------------------------------------
 */
// http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/mt.html
#ifdef RANDOMMT

/* Period parameters */
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

static unsigned long mt[N]; /* the array for the state vector  */
static int mti=N+1; /* mti==N+1 means mt[N] is not initialized */

/* initializes mt[N] with a seed */
void atn_srandommt(unsigned long s)
{
	mt[0]= s & 0xffffffffUL;
	for (mti=1; mti<N; mti++) {
		mt[mti] = (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti);

		/* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
		/* In the previous versions, MSBs of the seed affect   */
		/* only MSBs of the array mt[].                        */
		/* 2002/01/09 modified by Makoto Matsumoto             */
		mt[mti] &= 0xffffffffUL;
		/* for >32 bit machines */
	}
}

/* generates a random number on [0,0xffffffff]-interval */
static unsigned long atn_int32_randommt(void)
{
	unsigned long y;
	static unsigned long mag01[2]={0x0UL, MATRIX_A};

	/* mag01[x] = x * MATRIX_A  for x=0,1 */
	if (mti >= N) {		/* generate N words at one time */
		int kk;

		if (mti == N+1)		/* if init_genrand() has not been called, */
			atn_srandommt(5489UL);	/* a default initial seed is used */

		for (kk=0;kk<N-M;kk++) {
			y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
			mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
		}
		for (;kk<N-1;kk++) {
			y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
			mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
		}
		y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
		mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

		mti = 0;
	}

	y = mt[mti++];

	/* Tempering */
	y ^= (y >> 11);
	y ^= (y << 7) & 0x9d2c5680UL;
	y ^= (y << 15) & 0xefc60000UL;
	y ^= (y >> 18);

	return y;
}

int atn_int31_randommt(void)
{
	return (int)(atn_int32_randommt()>>1);
}

#endif	// ifdef RANDOMMT

/* 新形式の外見IDへ変換する。旧保存値0/1はそのまま利用できる。 */
int mmo_body_style(int class_, int style)
{
	if(style > 1)
		return style;
	if(style <= 0)
		return class_;
	switch(class_) {
	case PC_CLASS_RK:
	case PC_CLASS_RK_H:
	case PC_CLASS_RK2:
	case PC_CLASS_RK2_H:
	case PC_CLASS_RK3:
	case PC_CLASS_RK3_H:
	case PC_CLASS_RK4:
	case PC_CLASS_RK4_H:
	case PC_CLASS_RK5:
	case PC_CLASS_RK5_H:
	case PC_CLASS_RK6:
	case PC_CLASS_RK6_H:
	case PC_CLASS_RK_B:
	case PC_CLASS_RK2_B:
	case PC_CLASS_RK7:
	case PC_CLASS_RK7_B:
		return PC_CLASS_RK_2ND;
	case PC_CLASS_WL:
	case PC_CLASS_WL_H:
	case PC_CLASS_WL_B:
	case PC_CLASS_WL2:
	case PC_CLASS_WL2_B:
		return PC_CLASS_WL_2ND;
	case PC_CLASS_RA:
	case PC_CLASS_RA_H:
	case PC_CLASS_RA2:
	case PC_CLASS_RA2_H:
	case PC_CLASS_RA_B:
	case PC_CLASS_RA2_B:
	case PC_CLASS_RA3:
	case PC_CLASS_RA3_B:
		return PC_CLASS_RA_2ND;
	case PC_CLASS_AB:
	case PC_CLASS_AB_H:
	case PC_CLASS_AB_B:
	case PC_CLASS_AB2:
	case PC_CLASS_AB2_B:
		return PC_CLASS_AB_2ND;
	case PC_CLASS_NC:
	case PC_CLASS_NC_H:
	case PC_CLASS_NC2:
	case PC_CLASS_NC2_H:
	case PC_CLASS_NC_B:
	case PC_CLASS_NC2_B:
	case PC_CLASS_NC3:
	case PC_CLASS_NC3_B:
		return PC_CLASS_NC_2ND;
	case PC_CLASS_GC:
	case PC_CLASS_GC_H:
	case PC_CLASS_GC_B:
	case PC_CLASS_GC2:
	case PC_CLASS_GC2_B:
		return PC_CLASS_GC_2ND;
	case PC_CLASS_LG:
	case PC_CLASS_LG_H:
	case PC_CLASS_LG2:
	case PC_CLASS_LG2_H:
	case PC_CLASS_LG_B:
	case PC_CLASS_LG2_B:
	case PC_CLASS_LG3:
	case PC_CLASS_LG3_B:
		return PC_CLASS_LG_2ND;
	case PC_CLASS_SO:
	case PC_CLASS_SO_H:
	case PC_CLASS_SO_B:
	case PC_CLASS_SO2:
	case PC_CLASS_SO2_B:
		return PC_CLASS_SO_2ND;
	case PC_CLASS_MI:
	case PC_CLASS_MI_H:
	case PC_CLASS_MI_B:
	case PC_CLASS_MI2:
	case PC_CLASS_MI2_B:
		return PC_CLASS_MI_2ND;
	case PC_CLASS_WA:
	case PC_CLASS_WA_H:
	case PC_CLASS_WA_B:
	case PC_CLASS_WA2:
	case PC_CLASS_WA2_B:
		return PC_CLASS_WA_2ND;
	case PC_CLASS_SR:
	case PC_CLASS_SR_H:
	case PC_CLASS_SR_B:
	case PC_CLASS_SR2:
	case PC_CLASS_SR2_B:
		return PC_CLASS_SR_2ND;
	case PC_CLASS_GN:
	case PC_CLASS_GN_H:
	case PC_CLASS_GN_B:
	case PC_CLASS_GN2:
	case PC_CLASS_GN2_B:
		return PC_CLASS_GN_2ND;
	case PC_CLASS_SC:
	case PC_CLASS_SC_H:
	case PC_CLASS_SC_B:
		return PC_CLASS_SC_2ND;
	default:
		return class_;
	}
}
