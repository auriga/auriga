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
	TEST_ASSERT_EQUAL_INT(1, nullpo_chk(__FILE__, __LINE__, __func__, NULL));
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
