#ifndef _WIN32
#  define _POSIX_C_SOURCE 200809L
#endif

#include <fcntl.h>
#include <stdio.h>

#ifdef _WIN32
#  include <io.h>
#  define AURIGA_UT_DUP _dup
#  define AURIGA_UT_DUP2 _dup2
#  define AURIGA_UT_CLOSE _close
#  define AURIGA_UT_OPEN _open
#  ifndef O_WRONLY
#    define O_WRONLY _O_WRONLY
#  endif
#  define AURIGA_UT_STDOUT 1
#  define AURIGA_UT_DEVNULL "NUL"
#else
#  include <unistd.h>
#  define AURIGA_UT_DUP dup
#  define AURIGA_UT_DUP2 dup2
#  define AURIGA_UT_CLOSE close
#  define AURIGA_UT_OPEN open
#  define AURIGA_UT_STDOUT STDOUT_FILENO
#  define AURIGA_UT_DEVNULL "/dev/null"
#endif

#include "unity.h"
#include "nullpo.h"
#include "timer.h"
#include "utils.h"

void test_nullpo_chk_ok(void)
{
	int x = 1;

	TEST_ASSERT_EQUAL_INT(0, nullpo_chk(__FILE__, __LINE__, __func__, &x));
}

void test_nullpo_chk_null(void)
{
	int saved = -1;
	int nullfd = -1;
	int rc = -1;
	int silenced = 0;

	/*
	 * nullpo_chk(NULL) prints a banner. Silence stdout while calling it,
	 * then restore before any Unity assertions (so FAIL text is visible).
	 */
	fflush(stdout);
	saved = AURIGA_UT_DUP(AURIGA_UT_STDOUT);
	if (saved >= 0) {
		nullfd = AURIGA_UT_OPEN(AURIGA_UT_DEVNULL, O_WRONLY);
		if (nullfd >= 0 && AURIGA_UT_DUP2(nullfd, AURIGA_UT_STDOUT) == 0) {
			AURIGA_UT_CLOSE(nullfd);
			nullfd = -1;
			rc = nullpo_chk(__FILE__, __LINE__, __func__, NULL);
			fflush(stdout);
			silenced = 1;
		}
	}
	if (nullfd >= 0)
		AURIGA_UT_CLOSE(nullfd);
	if (saved >= 0) {
		AURIGA_UT_DUP2(saved, AURIGA_UT_STDOUT);
		AURIGA_UT_CLOSE(saved);
		clearerr(stdout);
	}

	TEST_ASSERT_TRUE(silenced);
	TEST_ASSERT_EQUAL_INT(1, rc);
}

void test_diff_tick_basic(void)
{
	TEST_ASSERT_EQUAL_INT(5, DIFF_TICK(10, 5));
	TEST_ASSERT_EQUAL_INT(-3, DIFF_TICK(2, 5));
}

void test_diff_tick_wraparound(void)
{
	unsigned int a = 2;
	unsigned int b = 0xfffffffeU;

	/* (int)(2 - 0xfffffffe) == 4 */
	TEST_ASSERT_EQUAL_INT(4, DIFF_TICK(a, b));
}

void test_ptr_int_cast_macros(void)
{
	void *p = INT2PTR(42);

	TEST_ASSERT_EQUAL_INT(42, PTR2INT(p));
	TEST_ASSERT_EQUAL_UINT(7u, PTR2UINT(UINT2PTR(7u)));
}
