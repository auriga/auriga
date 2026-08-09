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
