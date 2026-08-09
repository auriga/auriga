#include "unity.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_md5_string_empty(void);
void test_md5_string_abc(void);
void test_md5_string_message_digest(void);
void test_md5_binary_abc(void);
void test_md5_string2binary_abc(void);
void test_hmac_md5_rfc_hi_there(void);
void test_hmac_md5_rfc_jefe(void);
void test_hmac_md5_rfc_aa_dd(void);

void test_auriga_strlcpy_full_copy(void);
void test_auriga_strlcpy_truncates(void);
void test_auriga_strlcat_appends(void);
void test_auriga_strlcat_truncates(void);
void test_strtobxul_binary_prefix(void);
void test_strtobxul_leading_space(void);
void test_strtobxul_hex_via_strtoul(void);
void test_strtobxul_decimal_base10(void);
void test_bignum2int_clamps(void);

void test_linkdb_insert_search_erase(void);
void test_linkdb_replace(void);
void test_linkdb_replace_inserts_missing(void);
void test_numdb_crud(void);
void test_strdb_crud(void);
void test_csvdb_memory_ops(void);
void test_csvdb_open_parse_file(void);
void test_arr_find(void);

void test_nullpo_chk_ok(void);
void test_nullpo_chk_null(void);
void test_diff_tick_basic(void);
void test_diff_tick_wraparound(void);
void test_ptr_int_cast_macros(void);

void test_status_calc_ctrl_begin_run(void);
void test_status_calc_ctrl_begin_delayed(void);
void test_status_calc_ctrl_begin_busy(void);
void test_status_calc_ctrl_finish_done(void);
void test_status_calc_ctrl_finish_recalc(void);
void test_status_calc_ctrl_finish_infinity(void);
void test_status_calc_ctrl_recalc_then_done(void);
void test_status_calc_ctrl_stop_nesting(void);
void test_status_calc_ctrl_stop_underflow(void);

int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_md5_string_empty);
	RUN_TEST(test_md5_string_abc);
	RUN_TEST(test_md5_string_message_digest);
	RUN_TEST(test_md5_binary_abc);
	RUN_TEST(test_md5_string2binary_abc);
	RUN_TEST(test_hmac_md5_rfc_hi_there);
	RUN_TEST(test_hmac_md5_rfc_jefe);
	RUN_TEST(test_hmac_md5_rfc_aa_dd);

	RUN_TEST(test_auriga_strlcpy_full_copy);
	RUN_TEST(test_auriga_strlcpy_truncates);
	RUN_TEST(test_auriga_strlcat_appends);
	RUN_TEST(test_auriga_strlcat_truncates);
	RUN_TEST(test_strtobxul_binary_prefix);
	RUN_TEST(test_strtobxul_leading_space);
	RUN_TEST(test_strtobxul_hex_via_strtoul);
	RUN_TEST(test_strtobxul_decimal_base10);
	RUN_TEST(test_bignum2int_clamps);

	RUN_TEST(test_linkdb_insert_search_erase);
	RUN_TEST(test_linkdb_replace);
	RUN_TEST(test_linkdb_replace_inserts_missing);
	RUN_TEST(test_numdb_crud);
	RUN_TEST(test_strdb_crud);
	RUN_TEST(test_csvdb_memory_ops);
	RUN_TEST(test_csvdb_open_parse_file);
	RUN_TEST(test_arr_find);

	RUN_TEST(test_nullpo_chk_ok);
	RUN_TEST(test_nullpo_chk_null);
	RUN_TEST(test_diff_tick_basic);
	RUN_TEST(test_diff_tick_wraparound);
	RUN_TEST(test_ptr_int_cast_macros);

	RUN_TEST(test_status_calc_ctrl_begin_run);
	RUN_TEST(test_status_calc_ctrl_begin_delayed);
	RUN_TEST(test_status_calc_ctrl_begin_busy);
	RUN_TEST(test_status_calc_ctrl_finish_done);
	RUN_TEST(test_status_calc_ctrl_finish_recalc);
	RUN_TEST(test_status_calc_ctrl_finish_infinity);
	RUN_TEST(test_status_calc_ctrl_recalc_then_done);
	RUN_TEST(test_status_calc_ctrl_stop_nesting);
	RUN_TEST(test_status_calc_ctrl_stop_underflow);

	return UNITY_END();
}
