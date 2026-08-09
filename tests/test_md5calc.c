#include "unity.h"
#include "md5calc.h"

void test_md5_string_empty(void)
{
	char out[33];

	MD5_String("", out);
	TEST_ASSERT_EQUAL_STRING("d41d8cd98f00b204e9800998ecf8427e", out);
}

void test_md5_string_abc(void)
{
	char out[33];

	MD5_String("abc", out);
	TEST_ASSERT_EQUAL_STRING("900150983cd24fb0d6963f7d28e17f72", out);
}

void test_md5_binary_abc(void)
{
	unsigned char out[16];
	const unsigned char expected[16] = {
		0x90, 0x01, 0x50, 0x98, 0x3c, 0xd2, 0x4f, 0xb0,
		0xd6, 0x96, 0x3f, 0x7d, 0x28, 0xe1, 0x7f, 0x72
	};

	MD5_Binary("abc", 3, (char *)out);
	TEST_ASSERT_EQUAL_MEMORY(expected, out, 16);
}
