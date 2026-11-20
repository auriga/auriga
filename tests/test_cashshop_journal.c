/* 購入履歴と共通ジャーナルの結合テスト。 */
#include <stdio.h>
#include <string.h>
#include "unity.h"
#include "utils.h"
#include "journal.h"
#include "../src/char/txt/cashshopdb_txt.h"
#ifdef _WIN32
#include <windows.h>
#endif

static const char *txt_path = "cashshop_journal_test.txt";
static const char *journal_path = "cashshop_journal_test.journal";
static int owned;
#ifdef _WIN32
static int alias_owned;
static const char *alias_dir = "cashshop_long_directory_for_short_alias_test";
static char alias_txt[512];
#endif
void journal_test_fail_flush(int fail);
void journal_test_fail_write(int after);

static void prepare(void)
{
	FILE *fp = fopen(txt_path, "rb");
	if(fp) { fclose(fp); TEST_FAIL_MESSAGE("TXT test path already exists"); }
	fp = fopen(journal_path, "rb");
	if(fp) { fclose(fp); TEST_FAIL_MESSAGE("Journal test path already exists"); }
	owned = 1;
	cashshopdb_txt_config_read("cashshop_txt", txt_path);
	cashshopdb_txt_config_read("cashshop_journal_file", journal_path);
	cashshopdb_txt_config_read("cashshop_journal_enable", "1");
	cashshopdb_txt_config_read("cashshop_journal_cache_interval", "1000");
}

void cashshop_journal_test_cleanup(void)
{
	if(!owned) return;
	journal_test_fail_flush(0);
	journal_test_fail_write(0);
	cashshopdb_txt_final();
	remove(txt_path);
	remove(journal_path);
#ifdef _WIN32
	if(alias_owned) {
		remove(alias_txt);
		RemoveDirectoryA(alias_dir);
		alias_owned = 0;
	}
#endif
	owned = 0;
}

/* TXT確定前の停止を、保存先を一時的に利用不能にして再現する。 */
static void stop_before_txt_sync(void)
{
	cashshopdb_txt_config_read("cashshop_txt", "cashshop_nonexistent_dir/history.txt");
	cashshopdb_txt_final();
	cashshopdb_txt_config_read("cashshop_txt", txt_path);
}

static void assert_count(int account, int sale, unsigned int expected)
{
	struct cashshop_account_count row = {0};
	row.sale_id = sale;
	TEST_ASSERT_TRUE(cashshopdb_txt_load(account, &row, 1));
	TEST_ASSERT_EQUAL_UINT(expected, row.purchased);
}

void test_cashshop_journal_restart_composite_keys(void)
{
	struct cashshop_account_count a = {1, 3}, b = {100, 7};
	prepare();
	TEST_ASSERT_TRUE(cashshopdb_txt_init());
	TEST_ASSERT_TRUE(cashshopdb_txt_save(100, &a, 1));
	TEST_ASSERT_TRUE(cashshopdb_txt_save(1, &b, 1));
	stop_before_txt_sync();
	TEST_ASSERT_TRUE(cashshopdb_txt_init());
	assert_count(100, 1, 3);
	assert_count(1, 100, 7);
	assert_count(1, 1, 0);
}

void test_cashshop_journal_checkpoint_and_generation(void)
{
	struct cashshop_account_count rows[2] = {{1, 3}, {2, 5}};
	prepare();
	TEST_ASSERT_TRUE(cashshopdb_txt_init());
	TEST_ASSERT_TRUE(cashshopdb_txt_save(100, rows, 2));
	TEST_ASSERT_EQUAL_INT(0, cashshopdb_txt_sync());
	rows[0].purchased = 1;
	TEST_ASSERT_TRUE(cashshopdb_txt_save(100, rows, 2));
	rows[1].purchased = 8;
	TEST_ASSERT_TRUE(cashshopdb_txt_save(100, rows, 2));
	TEST_ASSERT_TRUE(cashshopdb_txt_save(101, rows, 2));
	stop_before_txt_sync();
	TEST_ASSERT_TRUE(cashshopdb_txt_init());
	assert_count(100, 1, 3);
	assert_count(100, 2, 8);
	assert_count(101, 1, 1);
	assert_count(101, 2, 8);
}

void test_cashshop_journal_legacy_txt_monotonic(void)
{
	struct cashshop_account_count row = {1, 2};
	FILE *fp;
	prepare();
	fp = fopen(txt_path, "wb");
	TEST_ASSERT_NOT_NULL(fp);
	fputs("100 1 5\n100 1 3\n", fp);
	fclose(fp);
	TEST_ASSERT_TRUE(cashshopdb_txt_init());
	assert_count(100, 1, 5);
	TEST_ASSERT_TRUE(cashshopdb_txt_save(100, &row, 1));
	row.purchased = 9;
	TEST_ASSERT_TRUE(cashshopdb_txt_save(100, &row, 1));
	stop_before_txt_sync();
	TEST_ASSERT_TRUE(cashshopdb_txt_init());
	assert_count(100, 1, 9);
}

void test_cashshop_journal_disabled_recovers_pending(void)
{
	struct cashshop_account_count row = {1, 4};
	FILE *fp;
	prepare();
	TEST_ASSERT_TRUE(cashshopdb_txt_init());
	TEST_ASSERT_TRUE(cashshopdb_txt_save(100, &row, 1));
	stop_before_txt_sync();
	cashshopdb_txt_config_read("cashshop_journal_enable", "0");
	TEST_ASSERT_TRUE(cashshopdb_txt_init());
	assert_count(100, 1, 4);
	fp = fopen(journal_path, "rb");
	TEST_ASSERT_NULL(fp);
	row.purchased = 6;
	TEST_ASSERT_TRUE(cashshopdb_txt_save(100, &row, 1));
	cashshopdb_txt_final();
	TEST_ASSERT_TRUE(cashshopdb_txt_init());
	assert_count(100, 1, 6);
}

void test_cashshop_journal_flush_failure_holds_latest(void)
{
	int immediate;
	for(immediate = 0; immediate < 2; immediate++) {
		struct cashshop_account_count rows[2] = {{1, 3}, {2, 8}};
		prepare();
		cashshopdb_txt_config_read("cashshop_journal_cache_interval", immediate ? "0" : "1000");
		TEST_ASSERT_TRUE(cashshopdb_txt_init());
		journal_test_fail_flush(1);
		TEST_ASSERT_FALSE(cashshopdb_txt_save(100, rows, 2));
		TEST_ASSERT_FALSE(cashshopdb_txt_load(100, rows, 2));
		TEST_ASSERT_FALSE(cashshopdb_txt_save(100, rows, 2));
		journal_test_fail_flush(0);
		stop_before_txt_sync();
		TEST_ASSERT_TRUE(cashshopdb_txt_init());
		assert_count(100, 1, 3);
		assert_count(100, 2, 8);
		cashshop_journal_test_cleanup();
	}
}

void test_cashshop_journal_corruption_preserves_txt(void)
{
	struct cashshop_account_count row = {1, 5};
	FILE *fp;
	char line[64];
	prepare();
	fp = fopen(txt_path, "wb");
	TEST_ASSERT_NOT_NULL(fp);
	fputs("100 1 2\n", fp);
	fclose(fp);
	TEST_ASSERT_TRUE(cashshopdb_txt_init());
	TEST_ASSERT_TRUE(cashshopdb_txt_save(100, &row, 1));
	stop_before_txt_sync();
	fp = fopen(journal_path, "r+b");
	TEST_ASSERT_NOT_NULL(fp);
	fseek(fp, 4096 + (long)sizeof(struct journal_header), SEEK_SET);
	fputc(0xff, fp);
	fclose(fp);
	cashshopdb_txt_config_read("cashshop_journal_enable", "0");
	TEST_ASSERT_FALSE(cashshopdb_txt_init());
	TEST_ASSERT_FALSE(cashshopdb_txt_load(100, &row, 1));
	TEST_ASSERT_EQUAL_INT(1, cashshopdb_txt_sync());
	fp = fopen(txt_path, "rb");
	TEST_ASSERT_NOT_NULL(fp);
	TEST_ASSERT_NOT_NULL(fgets(line, sizeof(line), fp));
	fclose(fp);
	TEST_ASSERT_EQUAL_STRING("100 1 2\n", line);
}

void test_cashshop_journal_rejects_identity_mismatch(void)
{
	struct journal j;
	int record[4] = {2, 100, 1, 5};
	prepare();
	{
		FILE *fp = fopen(txt_path, "wb");
		TEST_ASSERT_NOT_NULL(fp);
		fclose(fp);
	}
	journal_create(&j, sizeof(record), 0, journal_path);
	TEST_ASSERT_EQUAL_INT(1, journal_write(&j, 1, record));
	j.mode = 1;
	journal_final(&j);
	TEST_ASSERT_FALSE(cashshopdb_txt_init());
}

void test_cashshop_journal_rejects_duplicate_composite(void)
{
	struct journal j;
	int record[4] = {1, 100, 1, 5};
	prepare();
	{
		FILE *fp = fopen(txt_path, "wb");
		TEST_ASSERT_NOT_NULL(fp);
		fclose(fp);
	}
	journal_create(&j, sizeof(record), 0, journal_path);
	TEST_ASSERT_EQUAL_INT(1, journal_write(&j, 1, record));
	record[0] = 2;
	record[3] = 7;
	TEST_ASSERT_EQUAL_INT(1, journal_write(&j, 2, record));
	j.mode = 1;
	journal_final(&j);
	TEST_ASSERT_FALSE(cashshopdb_txt_init());
}

void test_cashshop_journal_missing_base_rejected(void)
{
	struct cashshop_account_count row = {1, 3};
	prepare();
	TEST_ASSERT_TRUE(cashshopdb_txt_init());
	TEST_ASSERT_TRUE(cashshopdb_txt_save(100, &row, 1));
	stop_before_txt_sync();
	TEST_ASSERT_EQUAL_INT(0, remove(txt_path));
	TEST_ASSERT_FALSE(cashshopdb_txt_init());
	TEST_ASSERT_FALSE(cashshopdb_txt_load(100, &row, 1));
	TEST_ASSERT_EQUAL_INT(1, cashshopdb_txt_sync());
}

void test_cashshop_journal_disabled_save_failure(void)
{
	struct cashshop_account_count row = {1, 3};
	prepare();
	cashshopdb_txt_config_read("cashshop_journal_enable", "0");
	TEST_ASSERT_TRUE(cashshopdb_txt_init());
	cashshopdb_txt_config_read("cashshop_txt", "cashshop_nonexistent_dir/history.txt");
	TEST_ASSERT_FALSE(cashshopdb_txt_save(100, &row, 1));
	TEST_ASSERT_FALSE(cashshopdb_txt_load(100, &row, 1));
	cashshopdb_txt_config_read("cashshop_txt", txt_path);
	TEST_ASSERT_EQUAL_INT(0, cashshopdb_txt_sync());
	TEST_ASSERT_FALSE(cashshopdb_txt_load(100, &row, 1));
	cashshopdb_txt_final();
	TEST_ASSERT_TRUE(cashshopdb_txt_init());
	assert_count(100, 1, 3);
}

void test_cashshop_journal_retains_past_catalog_history(void)
{
	struct cashshop_account_count rows[CASHSHOP_ACCOUNT_MAX];
	int i;
	prepare();
	TEST_ASSERT_TRUE(cashshopdb_txt_init());
	for(i = 0; i < CASHSHOP_ACCOUNT_MAX; i++) {
		rows[i].sale_id = i + 1;
		rows[i].purchased = 2;
	}
	TEST_ASSERT_TRUE(cashshopdb_txt_save(100, rows, CASHSHOP_ACCOUNT_MAX));
	TEST_ASSERT_EQUAL_INT(0, cashshopdb_txt_sync());
	for(i = 0; i < CASHSHOP_ACCOUNT_MAX; i++) {
		rows[i].sale_id += CASHSHOP_ACCOUNT_MAX;
		rows[i].purchased = 3;
	}
	TEST_ASSERT_TRUE(cashshopdb_txt_save(100, rows, CASHSHOP_ACCOUNT_MAX));
	stop_before_txt_sync();
	TEST_ASSERT_TRUE(cashshopdb_txt_init());
	assert_count(100, 1, 2);
	assert_count(100, CASHSHOP_ACCOUNT_MAX, 2);
	assert_count(100, CASHSHOP_ACCOUNT_MAX + 1, 3);
	assert_count(100, CASHSHOP_ACCOUNT_MAX * 2, 3);
	assert_count(101, CASHSHOP_ACCOUNT_MAX * 2, 0);
}

void test_cashshop_journal_detects_header_key_collision(void)
{
	struct cashshop_account_count rows[3] = {{1, 1}, {2, 2}, {3, 3}};
	struct journal_header header;
	FILE *fp;
	const char *moved = "cashshop_journal_test.moved";
	prepare();
	fp = fopen(moved, "rb");
	if(fp) { fclose(fp); TEST_FAIL_MESSAGE("Moved test path already exists"); }
	TEST_ASSERT_TRUE(cashshopdb_txt_init());
	TEST_ASSERT_TRUE(cashshopdb_txt_save(100, rows, 3));
	stop_before_txt_sync();
	fp = fopen(journal_path, "r+b");
	TEST_ASSERT_NOT_NULL(fp);
	fseek(fp, 4096, SEEK_SET);
	TEST_ASSERT_EQUAL_UINT(1, fread(&header, sizeof(header), 1, fp));
	header.key ^= 2;
	fseek(fp, 4096, SEEK_SET);
	TEST_ASSERT_EQUAL_UINT(1, fwrite(&header, sizeof(header), 1, fp));
	fclose(fp);
	TEST_ASSERT_FALSE(cashshopdb_txt_init());
	TEST_ASSERT_EQUAL_INT(0, rename(journal_path, moved));
	TEST_ASSERT_EQUAL_INT(0, rename(moved, journal_path));
}

void test_cashshop_journal_ignores_damaged_tick_for_count(void)
{
	struct cashshop_account_count row = {1, 3};
	struct journal_header header;
	FILE *fp;
	prepare();
	TEST_ASSERT_TRUE(cashshopdb_txt_init());
	TEST_ASSERT_TRUE(cashshopdb_txt_save(100, &row, 1));
	row.purchased = 9;
	TEST_ASSERT_TRUE(cashshopdb_txt_save(100, &row, 1));
	stop_before_txt_sync();
	fp = fopen(journal_path, "r+b");
	TEST_ASSERT_NOT_NULL(fp);
	fseek(fp, 4096, SEEK_SET);
	TEST_ASSERT_EQUAL_UINT(1, fread(&header, sizeof(header), 1, fp));
	header.tick ^= 2;
	fseek(fp, 4096, SEEK_SET);
	TEST_ASSERT_EQUAL_UINT(1, fwrite(&header, sizeof(header), 1, fp));
	fclose(fp);
	TEST_ASSERT_TRUE(cashshopdb_txt_init());
	assert_count(100, 1, 9);
}

void test_cashshop_journal_rejects_same_path(void)
{
	prepare();
	cashshopdb_txt_config_read("cashshop_journal_file", "./cashshop_journal_test.txt");
	TEST_ASSERT_FALSE(cashshopdb_txt_init());
	TEST_ASSERT_NULL(fopen(txt_path, "rb"));
}

void test_cashshop_journal_creation_failure_nonfatal(void)
{
	FILE *fp;
	prepare();
	fp = fopen(txt_path, "wb");
	TEST_ASSERT_NOT_NULL(fp);
	fputs("100 1 3\n", fp);
	fclose(fp);
	cashshopdb_txt_config_read("cashshop_journal_file", "cashshop_nonexistent_dir/history.journal");
	TEST_ASSERT_FALSE(cashshopdb_txt_init());
	fp = fopen(txt_path, "rb");
	TEST_ASSERT_NOT_NULL(fp);
	fclose(fp);
}

void test_cashshop_journal_short_alias_rejected(void)
{
#ifdef _WIN32
	char short_dir[512], short_journal[600];
	DWORD length;
	int disabled;
	FILE *fp;
	for(disabled = 0; disabled < 2; disabled++) {
		prepare();
		cashshopdb_txt_config_read("cashshop_journal_enable", disabled ? "0" : "1");
		TEST_ASSERT_TRUE(CreateDirectoryA(alias_dir, NULL));
		alias_owned = 1;
		snprintf(alias_txt, sizeof(alias_txt), "%s/history.txt", alias_dir);
		length = GetShortPathNameA(alias_dir, short_dir, sizeof(short_dir));
		if(!length || length >= sizeof(short_dir) || strcmpi(alias_dir, short_dir) == 0)
			TEST_IGNORE_MESSAGE("8.3 short names unavailable");
		snprintf(short_journal, sizeof(short_journal), "%s/history.txt", short_dir);
		cashshopdb_txt_config_read("cashshop_txt", alias_txt);
		cashshopdb_txt_config_read("cashshop_journal_file", short_journal);
		TEST_ASSERT_FALSE(cashshopdb_txt_init());
		fp = fopen(alias_txt, "rb");
		if(fp) {
			TEST_ASSERT_EQUAL_INT(EOF, fgetc(fp));
			fclose(fp);
		}
		cashshop_journal_test_cleanup();
	}
#else
	TEST_IGNORE_MESSAGE("Windows 8.3 alias test");
#endif
}

void test_cashshop_journal_header_rotation_failure_recovers(void)
{
	struct cashshop_account_count row = {1, 9};
	prepare();
	TEST_ASSERT_TRUE(cashshopdb_txt_init());
	TEST_ASSERT_TRUE(cashshopdb_txt_save(100, &row, 1));
	journal_test_fail_write(1);
	TEST_ASSERT_EQUAL_INT(1, cashshopdb_txt_sync());
	TEST_ASSERT_FALSE(cashshopdb_txt_load(100, &row, 1));
	journal_test_fail_write(0);
	cashshopdb_txt_final();
	TEST_ASSERT_TRUE(cashshopdb_txt_init());
	assert_count(100, 1, 9);
}

void test_cashshop_journal_disabled_missing_parent(void)
{
	struct cashshop_account_count row = {1, 3};
	prepare();
	cashshopdb_txt_config_read("cashshop_journal_enable", "0");
	cashshopdb_txt_config_read("cashshop_journal_file", "cashshop_nonexistent_dir/history.journal");
	TEST_ASSERT_TRUE(cashshopdb_txt_init());
	TEST_ASSERT_TRUE(cashshopdb_txt_save(100, &row, 1));
	cashshopdb_txt_final();
	TEST_ASSERT_TRUE(cashshopdb_txt_init());
	assert_count(100, 1, 3);
}
