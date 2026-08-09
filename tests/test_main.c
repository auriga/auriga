#include "unity.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_md5_string_empty(void);
void test_md5_string_abc(void);
void test_md5_binary_abc(void);

void test_auriga_strlcpy_full_copy(void);
void test_auriga_strlcpy_truncates(void);
void test_auriga_strlcat_appends(void);
void test_auriga_strlcat_truncates(void);
void test_strtobxul_binary_prefix(void);

int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_md5_string_empty);
	RUN_TEST(test_md5_string_abc);
	RUN_TEST(test_md5_binary_abc);

	RUN_TEST(test_auriga_strlcpy_full_copy);
	RUN_TEST(test_auriga_strlcpy_truncates);
	RUN_TEST(test_auriga_strlcat_appends);
	RUN_TEST(test_auriga_strlcat_truncates);
	RUN_TEST(test_strtobxul_binary_prefix);

	return UNITY_END();
}
