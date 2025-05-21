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

// =====================
// Platform
// ---------------------
#if defined(__ILP64__) || defined(__ILP64) || defined(_ILP64) || defined(ILP64)
#error "this specific 64bit architecture is not supported"
#endif

#if defined(_M_IA64) || defined(_M_X64) || defined(_WIN64) || defined(__LP64__) || defined(__LP64) || defined(_LP64) || defined(LP64) || defined(__ppc64__)
#define __64BIT__
#endif

#if (defined(__WIN32__) || defined(__WIN32) || defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(_MSC_VER) || defined(__BORLANDC__)) && !defined(WINDOWS)
#define WINDOWS
#endif


// =====================
// stdint.h
// ---------------------
typedef char  int8;
typedef short int16;
typedef int   int32;

typedef signed char  sint8;
typedef signed short sint16;
typedef signed int   sint32;

typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;

#if defined(_MSC_VER) || defined(__BORLANDC__)
typedef __int64          int64;
typedef signed __int64   sint64;
typedef unsigned __int64 uint64;
#else
typedef long long          int64;
typedef signed long long   sint64;
typedef unsigned long long uint64;
#endif

#ifdef __64BIT__
typedef uint64 uintptr;
typedef int64  intptr;
#else
typedef uint32 uintptr;
typedef int32  intptr;
#endif


// =====================
// �֐����}�N��
// ---------------------
#if __STDC_VERSION < 199901L
#	if __GNUC__ >= 2 || _MSC_VER >= 1300
#		define __func__ __FUNCTION__
#	else
#		define __func__ ""
#	endif
#endif


// =====================
// ���s�R�[�h
// ---------------------
#ifdef CYGWIN
#	define NEWLINE "\r\n"	// (CR/LF�FWindows�n)
#else
#	define NEWLINE "\n"	// (LF�FUnix�n�j
#endif


// =====================
// �傫�Ȑ����p�̌^
// ---------------------
#if defined(BIGNUMBER_DOUBLE) || defined(__BORLANDC__)
	typedef double atn_bignumber;
#else
	typedef int64 atn_bignumber;
#endif

// =====================
// �傫�Ȑ����p�̕ϊ��w��q
// ---------------------
#if defined(BIGNUMBER_DOUBLE) || defined(__BORLANDC__)
#	define BIGNUMCODE ".0f"
#elif defined(WINDOWS) && defined(_MSC_VER)
#	define BIGNUMCODE "I64d"
#else
#	define BIGNUMCODE "lld"
#endif

// =====================
// �傫�Ȑ����p�̕ϊ��w��q
// ---------------------
#if defined(BIGNUMBER_DOUBLE) || defined(__BORLANDC__)
#	define BIGNUMSCANCODE "lf"
#elif defined(WINDOWS) && defined(_MSC_VER)
#	define BIGNUMSCANCODE "I64d"
#else
#	define BIGNUMSCANCODE "lld"
#endif


// =====================
// strcmp �n�̃G�C���A�X
// ---------------------
#include <string.h>

#ifndef WINDOWS
#	ifndef strcmpi
#		define strcmpi  strcasecmp
#	endif
#	ifndef stricmp
#		define stricmp  strcasecmp
#	endif
#	ifndef strncmpi
#		define strncmpi strncasecmp
#	endif
#	ifndef strnicmp
#		define strnicmp strncasecmp
#	endif

#elif defined(_MSC_VER)
#	define strcmpi     _stricmp
#	define stricmp     _stricmp
#	define strcasecmp  _stricmp
#	define strncmpi    _strnicmp
#	define strnicmp    _strnicmp
#	define strncasecmp _strnicmp

#else
#	ifndef strcmpi
#		define strcmpi     stricmp
#	endif
#	ifndef strcasecmp
#		define strcasecmp  stricmp
#	endif
#	ifndef strncmpi
#		define strncmpi    strnicmp
#	endif
#	ifndef strncasecmp
#		define strncasecmp strnicmp
#	endif

#endif


// =====================
// VC �ł̒ǉ�����
// ---------------------
#if defined(WINDOWS) && defined(_MSC_VER)

#	define snprintf  _snprintf
#	define vsnprintf _vsnprintf

#endif	// if VC


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
// atn_rand() ��`
// ---------------------
#ifndef WINDOWS
#	define RANDOMSTD2X

#elif defined(_MSC_VER)
	// random �̐��x�ƃr�b�g�����グ��
#	define RANDOM64

#elif defined(__BORLANDC__)
	// random �̃r�b�g�����グ��
#	define RANDOM32

#else
#	define RANDOMSTD

#endif


// =====================
// atn_rand() �̃G�C���A�X
// ---------------------

#ifdef RANDOM32				// 32�r�b�g���x���`�����@
	void atn_int24_srandom32( int seed );
	int atn_int24_random32(void);
#	define atn_rand()	atn_int24_random32()
#	define atn_srand(x)	atn_int24_srandom32(x)
#	define ATN_RAND_MAX	0x00ffffff

#elif defined(RANDOM64)		// 64�r�b�g���x���`�����@
	void atn_int31_srandom64( int seed );
	int atn_int31_random64(void);
#	define atn_rand()	atn_int31_random64()
#	define atn_srand(x)	atn_int31_srandom64(x)
#	define ATN_RAND_MAX	0x7fffffff

#elif defined(RANDOM32X)	// 32�r�b�g���x���`�����@(���ʃr�b�g�̎����グ��)
	void atn_int24_srandom32( int seed );
	int atn_int24_random32(void);
#	define atn_rand()	( atn_int24_random32() ^ (atn_int24_random32()>>12) )
#	define atn_srand(x)	atn_int24_srandom32(x)
#	define ATN_RAND_MAX	0x00ffffff

#elif defined(RANDOM64X)	// 64�r�b�g���x���`�����@(���ʃr�b�g�̎����グ��)
	void atn_int31_srandom64( int seed );
	int atn_int31_random64(void);
#	define atn_rand()	( atn_int31_random64() ^ (atn_int31_random64()>>16) )
#	define atn_srand(x)	atn_int31_srandom64(x)
#	define ATN_RAND_MAX	0x7fffffff

#elif defined(RANDOMMT)		// �����Z���k�c�C�X�^�[
	void atn_srandommt( unsigned long seed );
	int atn_int31_randommt(void);
#	define atn_rand()	atn_int31_randommt()
#	define atn_srand(x)	atn_srandommt(x)
#	define ATN_RAND_MAX	0x7fffffff

#elif defined(RANDOMSTD2)	// rand() 2��(BCC/VC �ŗL���r�b�g�����グ��)
#	define atn_rand()	( ( (rand()<<15) + rand() ) & 0x3fffffff )
#	define atn_srand(x)	srand(x)
#	define ATN_RAND_MAX	0x3fffffff

#elif defined(RANDOMSTD2X)	// rand() 2��(gcc �ŉ��ʃr�b�g�̎����グ��)
#	define atn_rand()	(  rand() ^ (rand()>>8) )
#	define atn_srand(x)	srand(x)
#	define ATN_RAND_MAX RAND_MAX

#elif defined(RANDOMSTD3X)	// rand() 3��(BCC/VC �ŗL���r�b�g�����グ�違���ʃr�b�g�̎����グ��)
#	define atn_rand()	( ( (rand()<<15) + rand() ^ (rand()>>8) ) & 0x3fffffff )
#	define atn_srand(x)	srand(x)
#	define ATN_RAND_MAX	0x3fffffff

#else						// �ʏ�̃����_��
#	define atn_rand()	rand()
#	define atn_srand(x)	srand(x)
#	define ATN_RAND_MAX	RAND_MAX
#endif


// =====================
// �|�C���^�E���l�L���X�g
// ---------------------

// x64 gcc �̌x�� "warning: cast to/from pointer from/to integer of different size" �̗}���̂���
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
