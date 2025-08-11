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

#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

// =====================
// Platform
// ---------------------
#if defined(__ILP64__) || defined(__ILP64) || defined(_ILP64) || defined(ILP64)
#error "this specific 64bit architecture is not supported"
#endif

#if defined(_M_IA64) || defined(_M_X64) || defined(_WIN64) || defined(__LP64__) || defined(__LP64) || defined(_LP64) || defined(LP64) || defined(__ppc64__)
#define __64BIT__
#endif

#if (defined(__WIN32__) || defined(__WIN32) || defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(_MSC_VER)) && !defined(WINDOWS)
#define WINDOWS
#endif


// =====================
// Fixed width integer aliases (C11 stdint)
// ---------------------
typedef int8_t   int8;
typedef int16_t  int16;
typedef int32_t  int32;

typedef int8_t   sint8;
typedef int16_t  sint16;
typedef int32_t  sint32;

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;

typedef int64_t   int64;
typedef int64_t   sint64;
typedef uint64_t  uint64;

typedef uintptr_t uintptr;
typedef intptr_t  intptr;


// =====================
// 関数名マクロ
// ---------------------
#if __STDC_VERSION < 199901L
#	if __GNUC__ >= 2 || _MSC_VER >= 1300
#		define __func__ __FUNCTION__
#	else
#		define __func__ ""
#	endif
#endif


// =====================
// 改行コード
// ---------------------
#ifdef CYGWIN
#	define NEWLINE "\r\n"	// (CR/LF：Windows系)
#else
#	define NEWLINE "\n"	// (LF：Unix系）
#endif


// =====================
// 大きな数字用の型
// ---------------------
#if defined(BIGNUMBER_DOUBLE)
	typedef double atn_bignumber;
#else
	typedef int64 atn_bignumber;
#endif

// =====================
// 大きな数字用の変換指定子
// ---------------------
#if defined(BIGNUMBER_DOUBLE)
#	define BIGNUMCODE ".0f"
#elif defined(WINDOWS) && defined(_MSC_VER)
#	define BIGNUMCODE "I64d"
#else
#	define BIGNUMCODE "lld"
#endif

// =====================
// 大きな数字用の変換指定子
// ---------------------
#if defined(BIGNUMBER_DOUBLE)
#	define BIGNUMSCANCODE "lf"
#elif defined(WINDOWS) && defined(_MSC_VER)
#	define BIGNUMSCANCODE "I64d"
#else
#	define BIGNUMSCANCODE "lld"
#endif


// =====================
// strcmp 系のエイリアス（標準APIへ集約）
// ---------------------
#include <string.h>
#ifndef WINDOWS
#	include <strings.h>
#endif

#if defined(_MSC_VER)
#	define strcasecmp  _stricmp
#	define strncasecmp _strnicmp
#endif


// =====================
// VC での追加処理
// ---------------------
#if defined(WINDOWS) && defined(_MSC_VER) && (_MSC_VER < 1900)
// VS2015(1900) 未満は C の snprintf/vsnprintf が未実装
#	define snprintf  _snprintf
#	define vsnprintf _vsnprintf
#endif

// =====================
// Compile-time size checks (C11 static assert)
// ---------------------
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
#	define ATN_STATIC_ASSERT(cond, msg) _Static_assert(cond, msg)
#else
#	define ATN_STATIC_ASSERT(cond, msg) typedef char atn_static_assert_##__LINE__[(cond)?1:-1]
#endif

ATN_STATIC_ASSERT(sizeof(int8)  == 1,  "int8 must be 1 byte");
ATN_STATIC_ASSERT(sizeof(uint8) == 1,  "uint8 must be 1 byte");
ATN_STATIC_ASSERT(sizeof(int16) == 2,  "int16 must be 2 bytes");
ATN_STATIC_ASSERT(sizeof(uint16)== 2,  "uint16 must be 2 bytes");
ATN_STATIC_ASSERT(sizeof(int32) == 4,  "int32 must be 4 bytes");
ATN_STATIC_ASSERT(sizeof(uint32)== 4,  "uint32 must be 4 bytes");
ATN_STATIC_ASSERT(sizeof(int64) == 8,  "int64 must be 8 bytes");
ATN_STATIC_ASSERT(sizeof(uint64)== 8,  "uint64 must be 8 bytes");


// =====================
// va_copy
// ---------------------
#ifndef va_copy
#	ifdef __va_copy
#		define va_copy __va_copy
#	else
#		define va_copy(dst, src) memcpy(&(dst), &(src), sizeof(va_list))
#	endif
#endif


// =====================
// Safe append snprintf helper
// ---------------------
static inline int atn_appendf(char *dst, size_t capacity, int *length, const char *fmt, ...)
{
    size_t available = 0;
    int written;
    va_list ap;

    if (dst == NULL || length == NULL || capacity == 0) {
        return -1;
    }

    if ((size_t)(*length) < capacity) {
        available = capacity - (size_t)(*length);
    } else {
        return -1;
    }

    va_start(ap, fmt);
    written = vsnprintf(dst + *length, available, fmt, ap);
    va_end(ap);

    if (written < 0) {
        return -1;
    }
    if ((size_t)written >= available) {
        *length = (int)(capacity - 1);
        return -1;
    }

    *length += written;
    return written;
}


// =====================
// Safe string copy (null-terminating)
// ---------------------
static inline size_t atn_strlcpy(char *dst, const char *src, size_t size)
{
    size_t n = 0;
    if (size == 0) {
        return 0;
    }
    while (n + 1 < size && src[n]) {
        dst[n] = src[n];
        n++;
    }
    dst[n] = '\0';
    // Return the number of bytes copied (excluding terminator)
    return n;
}


// =====================
// atn_rand() 定義
// ---------------------
#ifndef WINDOWS
#	define RANDOMSTD2X


#elif defined(_MSC_VER)
	// random の精度とビット数を上げる
#	define RANDOM64

#else
#	define RANDOMSTD

#endif


// =====================
// atn_rand() のエイリアス
// ---------------------

#ifdef RANDOM32				// 32ビット精度線形合同法
	void atn_int24_srandom32( int seed );
	int atn_int24_random32(void);
#	define atn_rand()	atn_int24_random32()
#	define atn_srand(x)	atn_int24_srandom32(x)
#	define ATN_RAND_MAX	0x00ffffff

#elif defined(RANDOM64)		// 64ビット精度線形合同法
	void atn_int31_srandom64( int seed );
	int atn_int31_random64(void);
#	define atn_rand()	atn_int31_random64()
#	define atn_srand(x)	atn_int31_srandom64(x)
#	define ATN_RAND_MAX	0x7fffffff

#elif defined(RANDOM32X)	// 32ビット精度線形合同法(下位ビットの質を上げる)
	void atn_int24_srandom32( int seed );
	int atn_int24_random32(void);
#	define atn_rand()	( atn_int24_random32() ^ (atn_int24_random32()>>12) )
#	define atn_srand(x)	atn_int24_srandom32(x)
#	define ATN_RAND_MAX	0x00ffffff

#elif defined(RANDOM64X)	// 64ビット精度線形合同法(下位ビットの質を上げる)
	void atn_int31_srandom64( int seed );
	int atn_int31_random64(void);
#	define atn_rand()	( atn_int31_random64() ^ (atn_int31_random64()>>16) )
#	define atn_srand(x)	atn_int31_srandom64(x)
#	define ATN_RAND_MAX	0x7fffffff

#elif defined(RANDOMMT)		// メルセンヌツイスター
	void atn_srandommt( unsigned long seed );
	int atn_int31_randommt(void);
#	define atn_rand()	atn_int31_randommt()
#	define atn_srand(x)	atn_srandommt(x)
#	define ATN_RAND_MAX	0x7fffffff

#elif defined(RANDOMSTD2)	// rand() 2回(BCC/VC で有効ビット数を上げる)
#	define atn_rand()	( ( (rand()<<15) + rand() ) & 0x3fffffff )
#	define atn_srand(x)	srand(x)
#	define ATN_RAND_MAX	0x3fffffff

#elif defined(RANDOMSTD2X)	// rand() 2回(gcc で下位ビットの質を上げる)
#	define atn_rand()	(  rand() ^ (rand()>>8) )
#	define atn_srand(x)	srand(x)
#	define ATN_RAND_MAX RAND_MAX

#elif defined(RANDOMSTD3X)	// rand() 3回(BCC/VC で有効ビット数を上げる＆下位ビットの質を上げる)
#	define atn_rand()	( ( (rand()<<15) + rand() ^ (rand()>>8) ) & 0x3fffffff )
#	define atn_srand(x)	srand(x)
#	define ATN_RAND_MAX	0x3fffffff

#else						// 通常のランダム
#	define atn_rand()	rand()
#	define atn_srand(x)	srand(x)
#	define ATN_RAND_MAX	RAND_MAX
#endif


// =====================
// ポインタ・数値キャスト
// ---------------------

// x64 gcc の警告 "warning: cast to/from pointer from/to integer of different size" の抑制のため
#define INT2PTR(x)  ((void *)(intptr)(x))
#define UINT2PTR(x) ((void *)(uintptr)(x))
#define PTR2INT(x)  ((int)(intptr)(x))
#define PTR2UINT(x) ((unsigned int)(uintptr)(x))
#define BIGNUM2INT(x) (int)(((x) >= (int)(0x7fffffff)) ? (0x7fffffff) : ((x) <= (int)(0x80000000)) ? (0x80000000) : (x))

// =====================
// utils.c
// ---------------------
unsigned long strtobxul(const char *s, char **endptr, int base);
#define strtobxl(s, endptr, base) (long)strtobxul((s), (endptr), (base))

void hex_dump(FILE *fp, const unsigned char *buf, size_t len);

// =====================
// skill.c
// ---------------------

#ifndef WINDOWS
#define max(a,b) ({int _a = (a), _b = (b); _a > _b ? _a : _b;})
#endif

#endif	// _UTILS_H_
