#ifndef _UTILS_H_
#define _UTILS_H_

// =====================
// strcmp 系のエイリアス
// ---------------------
#ifndef strcmpi
#	define strcmpi strcasecmp
#endif

#ifndef stricmp
#	define stricmp strcasecmp
#endif

#ifndef strncmpi
#	define strncmpi strncasecmp
#endif

#ifndef strnicmp
#	define strnicmp strncasecmp
#endif


// =====================
// BCC での追加処理
// ---------------------
#if defined(_WIN32) && defined(__BORLANDC__)

	int strcasecmp(const char *s1, const char *s2);

	// random のビット数を上げる
#	if !defined(RANDOM32) && !defined(RANDOM64) && !defined(RANDOM32X) && !defined(RANDOM64X) && !defined(RANDOMMT) && !defined(RANDOMSTD) && !defined(RANDOMSTD2) && !defined(RANDOMSTD2X) && !defined(RANDOMSTD3X)
#		define RANDOM32
#	endif

#endif	// if BCC

#define RANDOMSTD2X

// =====================
// VC での追加処理
// ---------------------
#if defined(_WIN32) && defined(_MSC_VER)

#	define strcasecmp _stricmp
#	define snprintf _snprintf
#	define vsnprintf _vsnprintf

	// random の精度とビット数を上げる
#	if !defined(RANDOM32) && !defined(RANDOM64) && !defined(RANDOM32X) && !defined(RANDOM64X) && !defined(RANDOMMT) && !defined(RANDOMSTD) && !defined(RANDOMSTD2) && !defined(RANDOMSTD2X) && !defined(RANDOMSTD3X)
#		define RANDOM64
#	endif


#endif	// if VC


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
	long atn_int31_randommt(void);
#	define atn_rand()	atn_int31_randommt()
#	define atn_srand(x)	atn_srandommt(x)
#	define ATN_RAND_MAX	0x7fffffff

#elif defined(RANDOMSTD2)	// rand() 2回(BCC/VC で有効ビット数を上げる)
#	define atn_rand()	( ( (rand()<<15) + rand() ) & 0x3fffffff )
#	define atn_srand(x)	srand(x)
#	define ATN_RAND_MAX 0x3fffffff

#elif defined(RANDOMSTD2X)	// rand() 2回(gcc で下位ビットの質を上げる)
#	define atn_rand()	(  rand() ^ (rand()>>8) )
#	define atn_srand(x)	srand(x)
#	define ATN_RAND_MAX RAND_MAX

#elif defined(RANDOMSTD3X)	// rand() 3回(BCC/VC で有効ビット数を上げる＆下位ビットの質を上げる)
#	define atn_rand()	( ( (rand()<<15) + rand() ^ (rand()>>8) ) & 0x3fffffff )
#	define atn_srand(x)	srand(x)
#	define ATN_RAND_MAX 0x3fffffff

#else						// 通常のランダム
#	define atn_rand()	rand()
#	define atn_srand(x)	srand(x)
#	define ATN_RAND_MAX	RAND_MAX
#endif

#endif	// _UTILS_H_
