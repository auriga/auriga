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

void test_md5_string2binary_abc(void)
{
	unsigned char out[16];
	const unsigned char expected[16] = {
		0x90, 0x01, 0x50, 0x98, 0x3c, 0xd2, 0x4f, 0xb0,
		0xd6, 0x96, 0x3f, 0x7d, 0x28, 0xe1, 0x7f, 0x72
	};

	MD5_String2binary("abc", (char *)out);
	TEST_ASSERT_EQUAL_MEMORY(expected, out, 16);
}

/* RFC 2104 / RFC 2202 HMAC-MD5 test vectors */
void test_hmac_md5_rfc_hi_there(void)
{
	unsigned char key[16];
	unsigned char out[16];
	const unsigned char expected[16] = {
		0x92, 0x94, 0x72, 0x7a, 0x36, 0x38, 0xbb, 0x1c,
		0x13, 0xf4, 0x8e, 0xf8, 0x15, 0x8b, 0xfc, 0x9d
	};
	int i;

	for (i = 0; i < 16; i++)
		key[i] = 0x0b;

	HMAC_MD5_Binary((const char *)key, 16, "Hi There", 8, (char *)out);
	TEST_ASSERT_EQUAL_MEMORY(expected, out, 16);
}

void test_hmac_md5_rfc_jefe(void)
{
	unsigned char out[16];
	const unsigned char expected[16] = {
		0x75, 0x0c, 0x78, 0x3e, 0x6a, 0xb0, 0xb5, 0x03,
		0xea, 0xa8, 0x6e, 0x31, 0x0a, 0x5d, 0xb7, 0x38
	};
	const char *data = "what do ya want for nothing?";

	HMAC_MD5_Binary("Jefe", 4, data, 28, (char *)out);
	TEST_ASSERT_EQUAL_MEMORY(expected, out, 16);
}
