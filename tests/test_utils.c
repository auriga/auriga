#include <string.h>

#include "unity.h"
#include "utils.h"

void test_auriga_strlcpy_full_copy(void)
{
	char dst[16];
	size_t n;

	n = auriga_strlcpy(dst, "hello", sizeof(dst));
	TEST_ASSERT_EQUAL_UINT(5, n);
	TEST_ASSERT_EQUAL_STRING("hello", dst);
}

void test_auriga_strlcpy_truncates(void)
{
	char dst[4];
	size_t n;

	n = auriga_strlcpy(dst, "hello", sizeof(dst));
	TEST_ASSERT_EQUAL_UINT(5, n);
	TEST_ASSERT_EQUAL_STRING("hel", dst);
}

void test_auriga_strlcat_appends(void)
{
	char dst[16] = "foo";
	size_t n;

	n = auriga_strlcat(dst, "bar", sizeof(dst));
	TEST_ASSERT_EQUAL_UINT(6, n);
	TEST_ASSERT_EQUAL_STRING("foobar", dst);
}

void test_auriga_strlcat_truncates(void)
{
	char dst[6] = "foo";
	size_t n;

	n = auriga_strlcat(dst, "bar", sizeof(dst));
	TEST_ASSERT_EQUAL_UINT(6, n);
	TEST_ASSERT_EQUAL_STRING("fooba", dst);
}

void test_strtobxul_binary_prefix(void)
{
	char *end = NULL;
	unsigned long v;

	v = strtobxul("0b1010", &end, 0);
	TEST_ASSERT_EQUAL_UINT(10, v);
	TEST_ASSERT_NOT_NULL(end);
	TEST_ASSERT_EQUAL_CHAR('\0', *end);
}

void test_strtobxul_leading_space(void)
{
	char *end = NULL;
	unsigned long v;

	v = strtobxul("  0b11", &end, 0);
	TEST_ASSERT_EQUAL_UINT(3, v);
	TEST_ASSERT_NOT_NULL(end);
	TEST_ASSERT_EQUAL_CHAR('\0', *end);
}

void test_strtobxul_hex_via_strtoul(void)
{
	char *end = NULL;
	unsigned long v;

	v = strtobxul("0xff", &end, 0);
	TEST_ASSERT_EQUAL_UINT(255, v);
	TEST_ASSERT_NOT_NULL(end);
	TEST_ASSERT_EQUAL_CHAR('\0', *end);
}

void test_strtobxul_decimal_base10(void)
{
	char *end = NULL;
	unsigned long v;

	v = strtobxul("42xyz", &end, 10);
	TEST_ASSERT_EQUAL_UINT(42, v);
	TEST_ASSERT_NOT_NULL(end);
	TEST_ASSERT_EQUAL_CHAR('x', *end);
}

void test_bignum2int_clamps(void)
{
	TEST_ASSERT_EQUAL_INT(0x7fffffff, BIGNUM2INT(0x7fffffffLL + 1));
	TEST_ASSERT_EQUAL_INT((int)0x80000000, BIGNUM2INT(-0x80000000LL - 1));
	TEST_ASSERT_EQUAL_INT(123, BIGNUM2INT(123));
}
