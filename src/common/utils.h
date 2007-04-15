#ifndef _UTILS_H_
#define _UTILS_H_


// =====================
// 関数名マクロ
// ---------------------
#if __STDC_VERSION < 199901L
  #if __GNUC__ >= 2 || _MSC_VER >= 1300
    #define __func__ __FUNCTION__
  #else
    #define __func__ ""
  #endif
#endif


// =====================
// 改行コード
// ---------------------
#ifdef CYGWIN
#	define RETCODE "\r\n"	// (CR/LF：Windows系)
#else
#	define RETCODE "\n"	// (LF：Unix系）
#endif


// =====================
// longlong 型定義
// ---------------------
#if defined(_WIN32) && ( defined(__BORLANDC__) || defined(_MSC_VER) )
	typedef __int64 atn_int64;
#else
	typedef long long int atn_int64;
#endif

// =====================
// 大きな数字用の型
// ---------------------
#if defined(BIGNUMBER_DOUBLE)
	typedef double atn_bignumber;
#else
	typedef atn_int64 atn_bignumber;
#endif

// =====================
// 大きな数字用の変換指定子
// ---------------------
#if defined(BIGNUMBER_DOUBLE)
#	define BIGNUMCODE ".0f"
#elif defined(_WIN32) && ( defined(__BORLANDC__) || defined(_MSC_VER) )
#	define BIGNUMCODE "I64d"
#else
#	define BIGNUMCODE "lld"
#endif


// =====================
// strcmp 系のエイリアス
// ---------------------
#include <string.h>

#ifndef _WIN32
	#ifndef strcmpi
		#define strcmpi  strcasecmp
	#endif
	#ifndef stricmp
		#define stricmp  strcasecmp
	#endif
	#ifndef strncmpi
		#define strncmpi strncasecmp
	#endif
	#ifndef strnicmp
		#define strnicmp strncasecmp
	#endif
#else
	#if defined(_MSC_VER)
		#define strcmpi     _stricmp
		#define stricmp     _stricmp
		#define strcasecmp  _stricmp
		#define strncmpi    _strnicmp
		#define strnicmp    _strnicmp
		#define strncasecmp _strnicmp
	#else
		#ifndef strcmpi
			#define strcmpi     stricmp
		#endif
		#ifndef strcasecmp
			#define strcasecmp  stricmp
		#endif
		#ifndef strncmpi
			#define strncmpi    strnicmp
		#endif
		#ifndef strncasecmp
			#define strncasecmp strnicmp
		#endif
	#endif
#endif


// =====================
// BCC での追加処理
// ---------------------
#if defined(_WIN32) && defined(__BORLANDC__)

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

#	define snprintf  _snprintf
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


// =====================
// MySQL
// ---------------------
#ifndef TXT_ONLY

#ifdef _WIN32
	#include <winsock.h>
#else
	#include <sys/socket.h>
	#include <netinet/in.h>
#endif

#include <mysql.h>

extern MYSQL mysql_handle;
extern char tmp_sql[65535];
char* strecpy(char* pt,const char* spt);

#	ifdef _MSC_VER
#		pragma comment(lib,"libmysql.lib")
#	endif

#endif	// if TXT

#endif	// _UTILS_H_
