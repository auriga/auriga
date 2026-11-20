/* Common journal regression tests; built separately with TXT_JOURNAL. */
#if !defined(_WIN32) && !defined(_POSIX_C_SOURCE)
#define _POSIX_C_SOURCE 200809L
#endif
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "unity.h"
#include "utils.h"
#include "journal.h"
#include "timer.h"
#include "grfio.h"
#include "lock.h"
#ifdef _WIN32
#include <windows.h>
#include <io.h>
#endif
#ifndef _WIN32
#include <unistd.h>
#include <sys/stat.h>
#ifdef __linux__
#include <sys/xattr.h>
#endif
#endif

static const char *test_file = "journal_test.tmp";
static struct journal current;
static unsigned int test_tick;
static int recovered, recovered_flag, calls;
#ifndef _WIN32
static int symlink_target_owned;
#ifdef __linux__
static int acl_parent_owned;
#endif
#endif
static int fail_flush, fail_write_after, write_calls, fail_close;
static time_t test_time = 100;
static int fail_tell, early_eof;
size_t journal_test_read(void *buf, size_t size, size_t count, FILE *fp)
{
	if(early_eof && ftell(fp) >= 4096) return 0;
	return fread(buf, size, count, fp);
}
long long journal_test_tell(FILE *fp)
{
	if(fail_tell) return -1;
#ifdef _WIN32
	return _ftelli64(fp);
#else
	return ftell(fp);
#endif
}

time_t journal_test_time(time_t *out)
{
	if(out) *out = test_time;
	return test_time;
}
int journal_test_fclose(FILE *fp)
{
	int result = fclose(fp);
	return fail_close ? EOF : result;
}

size_t journal_test_fwrite(const void *buf, size_t size, size_t count, FILE *fp)
{
	if(fail_write_after && ++write_calls >= fail_write_after) {
		fwrite(buf, 1, size / 2, fp);
		return 0;
	}
	return fwrite(buf, size, count, fp);
}

int journal_test_fflush(FILE *fp)
{
	return fail_flush ? EOF : fflush(fp);
}

unsigned int gettick(void) { return test_tick; }
int add_timer_func_list_real(int (*func)(int,unsigned int,int,void*), const char *name) { return 0; }
int add_timer_interval(unsigned int tick, int (*func)(int,unsigned int,int,void*), int id, void *data, int interval) { return 1; }
int delete_timer(int id, int (*func)(int,unsigned int,int,void*)) { return 0; }
void grfio_load_zlib(void) { }
unsigned long grfio_crc32(const unsigned char *p, unsigned int n)
{
	unsigned int crc = 0xffffffffU, i, k;
	for(i = 0; i < n; i++) {
		crc ^= p[i];
		for(k = 0; k < 8; k++)
			crc = (crc >> 1) ^ (0xedb88320U & (0U - (crc & 1)));
	}
	return crc ^ 0xffffffffU;
}

void cashshop_journal_test_cleanup(void);
void journal_test_fail_flush(int fail) { fail_flush = fail; }
void journal_test_fail_write(int after) { fail_write_after = after; write_calls = 0; }
void test_cashshop_journal_retains_past_catalog_history(void);
void test_cashshop_journal_missing_base_rejected(void);
void test_cashshop_journal_disabled_save_failure(void);
void test_cashshop_journal_restart_composite_keys(void);
void test_cashshop_journal_checkpoint_and_generation(void);
void test_cashshop_journal_legacy_txt_monotonic(void);
void test_cashshop_journal_disabled_recovers_pending(void);
void test_cashshop_journal_flush_failure_holds_latest(void);
void test_cashshop_journal_corruption_preserves_txt(void);
void test_cashshop_journal_rejects_identity_mismatch(void);
void test_cashshop_journal_rejects_duplicate_composite(void);

void test_cashshop_journal_detects_header_key_collision(void);
void test_cashshop_journal_ignores_damaged_tick_for_count(void);
void test_cashshop_journal_rejects_same_path(void);
void test_cashshop_journal_creation_failure_nonfatal(void);
void test_cashshop_journal_short_alias_rejected(void);
void test_cashshop_journal_header_rotation_failure_recovers(void);
void test_cashshop_journal_disabled_missing_parent(void);
void setUp(void) { memset(&current, 0, sizeof(current)); current.cache_timer = -1; calls = 0; fail_flush = 0; fail_write_after = 0; write_calls = 0; fail_close = 0; test_time = 100; test_tick = 0; fail_tell = 0; early_eof = 0; }
void tearDown(void)
{
	cashshop_journal_test_cleanup();
	journal_final(&current);
	remove(test_file);
#ifndef _WIN32
	if(symlink_target_owned) {
		remove("journal_symlink_target_test.tmp");
		symlink_target_owned = 0;
	}
#ifdef __linux__
	if(acl_parent_owned) {
		remove("journal_acl_parent_test/history.journal");
		rmdir("journal_acl_parent_test");
		acl_parent_owned = 0;
	}
#endif
#endif
}
static int replay(int key, void *buf, int flag)
{
	TEST_ASSERT_EQUAL_INT(7, key);
	recovered = *(int *)buf;
	recovered_flag = flag;
	calls++;
	return 1;
}
static void retain_file(void)
{
	current.mode = 1; /* Simulate restart while preserving written records. */
	journal_final(&current);
}
static void create_record(void)
{
	int value = 11;
	journal_create(&current, sizeof(value), 0, test_file);
	TEST_ASSERT_EQUAL_INT(1, journal_write(&current, 7, &value));
}
static void test_immediate_write_and_delete(void)
{
	create_record();
	TEST_ASSERT_EQUAL_INT(0, journal_flush(&current));
	TEST_ASSERT_EQUAL_INT(1, journal_write(&current, 7, NULL));
	retain_file();
	TEST_ASSERT_EQUAL_INT(1, journal_load_checked(&current, sizeof(int), test_file));
	TEST_ASSERT_EQUAL_INT(1, journal_rollforward(&current, replay));
	TEST_ASSERT_EQUAL_INT(JOURNAL_FLAG_DELETE, recovered_flag);
}
static void test_cached_write_and_same_second_recovery(void)
{
	int value = 22;
	create_record();
	current.cache_timer = 1;
	TEST_ASSERT_EQUAL_INT(1, journal_write(&current, 7, &value));
	TEST_ASSERT_NOT_NULL(((struct journal_data *)numdb_search(current.db, 7))->buf);
	TEST_ASSERT_EQUAL_INT(0, journal_flush(&current));
	TEST_ASSERT_NULL(((struct journal_data *)numdb_search(current.db, 7))->buf);
	retain_file();
	TEST_ASSERT_EQUAL_INT(1, journal_load_checked(&current, sizeof(int), test_file));
	TEST_ASSERT_EQUAL_INT(1, journal_rollforward(&current, replay));
	TEST_ASSERT_EQUAL_INT(22, recovered);
	TEST_ASSERT_EQUAL_INT(0, journal_checkpoint(&current));
}
static void test_write_failure_preserves_file_and_cache(void)
{
	int value = 33;
	FILE *fp;
	create_record();
	TEST_ASSERT_NOT_NULL(freopen(test_file, "rb", current.fp));
	TEST_ASSERT_EQUAL_INT(0, journal_write(&current, 7, &value));
	TEST_ASSERT_EQUAL_INT(-1, journal_flush(&current));
	TEST_ASSERT_EQUAL_INT(-1, journal_checkpoint(&current));
	{
		struct journal_config cfg = { 1, "journal_test.tmp", 0 };
		journal_recreate(&current, &cfg, sizeof(int));
		TEST_ASSERT_EQUAL_INT(1, current.io_error);
	}
	TEST_ASSERT_NOT_NULL(((struct journal_data *)numdb_search(current.db, 7))->buf);
	journal_final(&current);
	fp = fopen(test_file, "rb");
	TEST_ASSERT_NOT_NULL(fp);
	fclose(fp);
	TEST_ASSERT_EQUAL_INT(1, journal_load_checked(&current, sizeof(int), test_file));
	TEST_ASSERT_EQUAL_INT(1, journal_rollforward(&current, replay));
	TEST_ASSERT_EQUAL_INT(11, recovered);
}
static void test_flush_failure_retains_old_chunk(void)
{
	int value = 44, old_idx;
	struct journal_data *data;
	FILE *fp;
	create_record();
	data = (struct journal_data *)numdb_search(current.db, 7);
	old_idx = data->idx;
	fail_flush = 1;
	TEST_ASSERT_EQUAL_INT(0, journal_write(&current, 7, &value));
	TEST_ASSERT_EQUAL_INT(1, current.io_error);
	TEST_ASSERT_EQUAL_INT(old_idx, data->idx);
	TEST_ASSERT_NOT_NULL(data->buf);
	TEST_ASSERT_EQUAL_INT(value, *(int *)data->buf);
	TEST_ASSERT_NOT_EQUAL(old_idx, data->pending_idx);
	TEST_ASSERT_EQUAL_INT(-1, journal_checkpoint(&current));
	fail_flush = 0;
	journal_final(&current);
	fp = fopen(test_file, "rb");
	TEST_ASSERT_NOT_NULL(fp);
	fclose(fp);
}

static int multi_values[2], multi_flags[2];
static int replay_multi(int key, void *buf, int flag)
{
	TEST_ASSERT_TRUE(key == 7 || key == 8);
	multi_values[key - 7] = *(int *)buf;
	multi_flags[key - 7] = flag;
	return 1;
}
static void test_partial_batch_retry_update_and_delete(void)
{
	int value = 10;
	create_record();
	TEST_ASSERT_EQUAL_INT(1, journal_write(&current, 8, &value));
	current.cache_timer = 1;
	value = 20;
	TEST_ASSERT_EQUAL_INT(1, journal_write(&current, 7, &value));
	TEST_ASSERT_EQUAL_INT(1, journal_write(&current, 8, &value));
	fail_write_after = 4;
	TEST_ASSERT_EQUAL_INT(-1, journal_flush(&current));
	value = 30;
	TEST_ASSERT_EQUAL_INT(0, journal_write(&current, 7, &value));
	TEST_ASSERT_EQUAL_INT(0, journal_write(&current, 8, NULL));
	fail_write_after = 0;
	TEST_ASSERT_EQUAL_INT(0, journal_checkpoint(&current));
	retain_file();
	TEST_ASSERT_EQUAL_INT(2, journal_load_checked(&current, sizeof(int), test_file));
	TEST_ASSERT_EQUAL_INT(2, journal_rollforward(&current, replay_multi));
	TEST_ASSERT_EQUAL_INT(30, multi_values[0]);
	TEST_ASSERT_EQUAL_INT(JOURNAL_FLAG_WRITE, multi_flags[0]);
	TEST_ASSERT_EQUAL_INT(JOURNAL_FLAG_DELETE, multi_flags[1]);
}
static void test_checked_txt_replacement_and_final_retention(void)
{
	FILE *fp;
	int lock, value;
	struct journal_config cfg = { 1, "journal_test.tmp", 0 };
	create_record();
	journal_final(&current);
	TEST_ASSERT_EQUAL_INT(-1, journal_checkpoint(&current));
	TEST_ASSERT_EQUAL_INT(1, journal_load_checked(&current, sizeof(int), test_file));
	TEST_ASSERT_EQUAL_INT(1, journal_rollforward(&current, replay));
	TEST_ASSERT_EQUAL_INT(11, recovered);
	journal_final(&current);
	fp = lock_fopen(test_file, &lock);
	TEST_ASSERT_NOT_NULL(fp);
	fputs("99", fp);
	{
		char temporary[128];
		snprintf(temporary, sizeof(temporary), "%s_%04d.tmp", test_file, lock);
		TEST_ASSERT_NOT_NULL(freopen(temporary, "rb", fp));
		TEST_ASSERT_EQUAL_INT(EOF, fputc('x', fp));
	}
	TEST_ASSERT_EQUAL_INT(1, lock_fclose_checked(fp, test_file, &lock));
	TEST_ASSERT_EQUAL_INT(1, journal_load_checked(&current, sizeof(int), test_file));
	journal_final(&current);
	fp = lock_fopen(test_file, &lock);
	TEST_ASSERT_NOT_NULL(fp);
	fputs("99", fp);
	TEST_ASSERT_EQUAL_INT(0, lock_fclose_checked(fp, test_file, &lock));
	fp = fopen(test_file, "rb");
	TEST_ASSERT_NOT_NULL(fp);
	TEST_ASSERT_EQUAL_INT(1, fscanf(fp, "%d", &value));
	TEST_ASSERT_EQUAL_INT(99, value);
	fclose(fp);
	/* A completed TXT checkpoint may retire its journal generation. */
	journal_create(&current, sizeof(int), 0, test_file);
	value = 88;
	TEST_ASSERT_EQUAL_INT(1, journal_write(&current, 7, &value));
	journal_recreate(&current, &cfg, sizeof(int));
	TEST_ASSERT_EQUAL_INT(0, current.needs_sync);
	journal_final(&current);
	TEST_ASSERT_NULL(fopen(test_file, "rb"));
}

static void test_write_failure_retry_saves_latest_value(void)
{
	int value = 33;
	size_t next;
	create_record();
	TEST_ASSERT_NOT_NULL(freopen(test_file, "rb", current.fp));
	TEST_ASSERT_EQUAL_INT(0, journal_write(&current, 7, &value));
	next = current.nextchunk;
	TEST_ASSERT_NOT_NULL(freopen(test_file, "r+b", current.fp));
	value = 55;
	TEST_ASSERT_EQUAL_INT(1, journal_write(&current, 7, &value));
	TEST_ASSERT_EQUAL_INT(0, current.io_error);
	TEST_ASSERT_EQUAL_UINT(next, current.nextchunk);
	TEST_ASSERT_EQUAL_INT(0, journal_checkpoint(&current));
	retain_file();
	TEST_ASSERT_EQUAL_INT(1, journal_load_checked(&current, sizeof(int), test_file));
	TEST_ASSERT_EQUAL_INT(1, journal_rollforward(&current, replay));
	TEST_ASSERT_EQUAL_INT(55, recovered);
}
static void test_timer_retry_of_failed_new_key(void)
{
	int value = 66;
	journal_create(&current, sizeof(int), 1000, test_file);
	fail_flush = 1;
	TEST_ASSERT_EQUAL_INT(1, journal_write(&current, 7, &value));
	TEST_ASSERT_EQUAL_INT(-1, journal_flush(&current));
	value = 77;
	TEST_ASSERT_EQUAL_INT(0, journal_write(&current, 7, &value));
	fail_flush = 0;
	TEST_ASSERT_EQUAL_INT(0, journal_flush(&current));
	TEST_ASSERT_EQUAL_INT(0, current.io_error);
	retain_file();
	TEST_ASSERT_EQUAL_INT(1, journal_load_checked(&current, sizeof(int), test_file));
	TEST_ASSERT_EQUAL_INT(1, journal_rollforward(&current, replay));
	TEST_ASSERT_EQUAL_INT(77, recovered);
}
static void write_old_record(FILE *fp, int index, size_t chunk, int value, time_t timestamp, unsigned int tick)
{
	struct journal_header header;
	memset(&header, 0, sizeof(header));
	header.key = 7;
	header.timestamp = timestamp;
	header.tick = tick;
	header.crc32 = grfio_crc32((unsigned char *)&value, sizeof(value));
	TEST_ASSERT_EQUAL_INT(0, fseek(fp, (long)(index * chunk), SEEK_SET));
	TEST_ASSERT_EQUAL_UINT(1, fwrite(&header, sizeof(header), 1, fp));
	TEST_ASSERT_EQUAL_UINT(1, fwrite(&value, sizeof(value), 1, fp));
}
static void test_legacy_clock_rollback_both_physical_orders(void)
{
	int order;
	for(order = 0; order < 2; order++) {
		FILE *fp;
		size_t chunk;
		create_record();
		chunk = current.chunksize;
		retain_file();
		fp = fopen(test_file, "r+b");
		TEST_ASSERT_NOT_NULL(fp);
		write_old_record(fp, order ? 2 : 1, chunk, 30, 99, 300);
		write_old_record(fp, order ? 1 : 2, chunk, 20, 100, 200);
		fclose(fp);
		TEST_ASSERT_EQUAL_INT(1, journal_load_checked(&current, sizeof(int), test_file));
		TEST_ASSERT_EQUAL_INT(1, journal_rollforward(&current, replay));
		TEST_ASSERT_EQUAL_INT(30, recovered);
		journal_final(&current);
		remove(test_file);
	}
}

static void test_corruption_strict_and_legacy(void)
{
	FILE *fp;
	long offset;
	create_record();
	offset = (long)(current.chunksize + sizeof(struct journal_header));
	retain_file();
	fp = fopen(test_file, "r+b");
	TEST_ASSERT_NOT_NULL(fp);
	fseek(fp, offset, SEEK_SET);
	fputc(0xff, fp);
	fclose(fp);
	TEST_ASSERT_EQUAL_INT(-1, journal_load_checked(&current, sizeof(int), test_file));
	TEST_ASSERT_EQUAL_INT(-1, journal_rollforward(&current, replay));
	TEST_ASSERT_EQUAL_INT(0, calls);
	journal_final(&current);
	TEST_ASSERT_EQUAL_INT(0, journal_load(&current, sizeof(int), test_file));
	TEST_ASSERT_EQUAL_INT(0, journal_rollforward(&current, replay));
}
static void test_missing_empty_and_truncated_header(void)
{
	FILE *fp;
	TEST_ASSERT_EQUAL_INT(0, journal_load_checked(&current, sizeof(int), test_file));
	journal_final(&current);
	journal_create(&current, sizeof(int), 0, test_file);
	retain_file();
	TEST_ASSERT_EQUAL_INT(0, journal_load_checked(&current, sizeof(int), test_file));
	journal_final(&current);
	fp = fopen(test_file, "wb");
	TEST_ASSERT_NOT_NULL(fp);
	fputc('A', fp);
	fclose(fp);
	TEST_ASSERT_EQUAL_INT(-1, journal_load_checked(&current, sizeof(int), test_file));
}
static void test_incompatible_layout_preserved(void)
{
	struct journal_config cfg = { 1, "journal_test.tmp", 0 };
	FILE *fp;
	create_record();
	retain_file();
	TEST_ASSERT_EQUAL_INT(-1, journal_load_checked(&current, sizeof(int) * 2, test_file));
	journal_recreate(&current, &cfg, sizeof(int));
	TEST_ASSERT_EQUAL_INT(1, current.load_error);
	journal_final(&current);
	fp = fopen(test_file, "rb");
	TEST_ASSERT_NOT_NULL(fp);
	fclose(fp);
	TEST_ASSERT_EQUAL_INT(1, journal_load_checked(&current, sizeof(int), test_file));
	TEST_ASSERT_EQUAL_INT(1, journal_rollforward(&current, replay));
	TEST_ASSERT_EQUAL_INT(11, recovered);
}
static void test_second_boundary_preserves_latest_tick(void)
{
	int value;
	test_tick = 100;
	journal_create(&current, sizeof(int), 0, test_file);
	for(value = 1; value <= 3; value++)
		TEST_ASSERT_EQUAL_INT(1, journal_write(&current, 7, &value));
	TEST_ASSERT_EQUAL_INT(100, ((struct journal_data *)numdb_search(current.db, 7))->timestamp);
	test_time = 101;
	test_tick = 101;
	value = 4;
	TEST_ASSERT_EQUAL_INT(1, journal_write(&current, 7, &value));
	TEST_ASSERT_EQUAL_INT(101, ((struct journal_data *)numdb_search(current.db, 7))->timestamp);
	retain_file();
	TEST_ASSERT_EQUAL_INT(1, journal_load_checked(&current, sizeof(int), test_file));
	TEST_ASSERT_EQUAL_INT(1, journal_rollforward(&current, replay));
	TEST_ASSERT_EQUAL_INT(4, recovered);
}
static void test_recreate_after_close_failure(void)
{
	struct journal_config cfg = { 1, "journal_test.tmp", 0 };
	int value = 55;
	create_record();
	fail_close = 1;
	journal_recreate(&current, &cfg, sizeof(int));
	fail_close = 0;
	TEST_ASSERT_EQUAL_INT(0, current.io_error);
	TEST_ASSERT_EQUAL_INT(0, current.mode);
	journal_require_ready(&current, &cfg);
	TEST_ASSERT_EQUAL_INT(1, journal_write(&current, 7, &value));
	retain_file();
	TEST_ASSERT_EQUAL_INT(1, journal_load_checked(&current, sizeof(int), test_file));
	TEST_ASSERT_EQUAL_INT(1, journal_rollforward(&current, replay));
	TEST_ASSERT_EQUAL_INT(55, recovered);
}
static void test_empty_header_with_trailing_byte(void)
{
	FILE *fp;
	journal_create(&current, sizeof(int), 0, test_file);
	retain_file();
	fp = fopen(test_file, "ab");
	TEST_ASSERT_NOT_NULL(fp);
	fputc(1, fp);
	fclose(fp);
	TEST_ASSERT_EQUAL_INT(-1, journal_load_checked(&current, sizeof(int), test_file));
}
static void test_write_flag_corrupted_to_delete(void)
{
	FILE *fp;
	struct journal_header header;
	long offset;
	create_record();
	offset = (long)current.chunksize;
	retain_file();
	fp = fopen(test_file, "r+b");
	TEST_ASSERT_NOT_NULL(fp);
	fseek(fp, offset, SEEK_SET);
	TEST_ASSERT_EQUAL_UINT(1, fread(&header, sizeof(header), 1, fp));
	header.flag = JOURNAL_FLAG_DELETE;
	fseek(fp, offset, SEEK_SET);
	TEST_ASSERT_EQUAL_UINT(1, fwrite(&header, sizeof(header), 1, fp));
	fclose(fp);
	TEST_ASSERT_EQUAL_INT(-1, journal_load_checked(&current, sizeof(int), test_file));
	TEST_ASSERT_EQUAL_INT(-1, journal_rollforward(&current, replay));
}

static int replay_key7(int key, void *buf, int flag)
{
	if(key != 7) return 0;
	recovered = *(int *)buf;
	return 1;
}
static void test_initial_tick_above_signed_range(void)
{
	int key, value;
	journal_create(&current, sizeof(int), 0, test_file);
	test_tick = 0x80000001U;
	for(key = 8; key <= 10; key++) {
		value = 0;
		TEST_ASSERT_EQUAL_INT(1, journal_write(&current, key, &value));
		value = 1;
		TEST_ASSERT_EQUAL_INT(1, journal_write(&current, key, &value));
	}
	for(value = 1; value <= 4; value++)
		TEST_ASSERT_EQUAL_INT(1, journal_write(&current, 7, &value));
	retain_file();
	TEST_ASSERT_EQUAL_INT(4, journal_load_checked(&current, sizeof(int), test_file));
	TEST_ASSERT_EQUAL_INT(1, journal_rollforward(&current, replay_key7));
	TEST_ASSERT_EQUAL_INT(4, recovered);
}
static void test_legacy_long_interval_both_physical_orders(void)
{
	int order;
	for(order = 0; order < 2; order++) {
		FILE *fp;
		size_t chunk;
		create_record();
		chunk = current.chunksize;
		retain_file();
		fp = fopen(test_file, "r+b");
		TEST_ASSERT_NOT_NULL(fp);
		write_old_record(fp, order ? 2 : 1, chunk, 30, 100 + 25 * 86400, 200U + 25U * 86400000U);
		write_old_record(fp, order ? 1 : 2, chunk, 20, 100, 200);
		fclose(fp);
		TEST_ASSERT_EQUAL_INT(1, journal_load_checked(&current, sizeof(int), test_file));
		TEST_ASSERT_EQUAL_INT(1, journal_rollforward(&current, replay));
		TEST_ASSERT_EQUAL_INT(30, recovered);
		journal_final(&current);
		remove(test_file);
	}
}
static void test_file_size_failure_preserves_records(void)
{
	create_record();
	retain_file();
	fail_tell = 1;
	TEST_ASSERT_EQUAL_INT(-1, journal_load(&current, sizeof(int), test_file));
	journal_final(&current);
	fail_tell = 0;
	TEST_ASSERT_EQUAL_INT(1, journal_load_checked(&current, sizeof(int), test_file));
	TEST_ASSERT_EQUAL_INT(1, journal_rollforward(&current, replay));
	TEST_ASSERT_EQUAL_INT(11, recovered);
}

static void test_tick_half_cycle_both_physical_orders(void)
{
	int order;
	for(order = 0; order < 2; order++) {
		FILE *fp;
		size_t chunk;
		create_record();
		chunk = current.chunksize;
		retain_file();
		fp = fopen(test_file, "r+b");
		TEST_ASSERT_NOT_NULL(fp);
		write_old_record(fp, order ? 2 : 1, chunk, 30, 100 + 2147483, 200U + 0x80000000U);
		write_old_record(fp, order ? 1 : 2, chunk, 20, 100, 200);
		fclose(fp);
		TEST_ASSERT_EQUAL_INT(1, journal_load_checked(&current, sizeof(int), test_file));
		TEST_ASSERT_EQUAL_INT(1, journal_rollforward(&current, replay));
		TEST_ASSERT_EQUAL_INT(30, recovered);
		journal_final(&current);
		remove(test_file);
	}
}
static void test_eof_before_known_record(void)
{
	create_record();
	retain_file();
	early_eof = 1;
	TEST_ASSERT_EQUAL_INT(-1, journal_load_checked(&current, sizeof(int), test_file));
	TEST_ASSERT_EQUAL_INT(-1, journal_rollforward(&current, replay));
	journal_final(&current);
	early_eof = 0;
	TEST_ASSERT_EQUAL_INT(1, journal_load_checked(&current, sizeof(int), test_file));
	TEST_ASSERT_EQUAL_INT(1, journal_rollforward(&current, replay));
	TEST_ASSERT_EQUAL_INT(11, recovered);
}

static void test_partial_record_header(void)
{
	FILE *fp;
	long offset;
	create_record();
	offset = (long)(current.chunksize * 2);
	retain_file();
	fp = fopen(test_file, "r+b");
	TEST_ASSERT_NOT_NULL(fp);
	fseek(fp, offset, SEEK_SET);
	fputc(1, fp);
	fclose(fp);
	TEST_ASSERT_EQUAL_INT(-1, journal_load_checked(&current, sizeof(int), test_file));
	TEST_ASSERT_EQUAL_INT(-1, journal_rollforward(&current, replay));
	TEST_ASSERT_EQUAL_INT(0, calls);
	journal_final(&current);
	TEST_ASSERT_EQUAL_INT(1, journal_load(&current, sizeof(int), test_file));
	TEST_ASSERT_EQUAL_INT(1, journal_rollforward(&current, replay));
	TEST_ASSERT_EQUAL_INT(11, recovered);
}
static void test_checked_create_and_recreate_nonfatal(void)
{
	struct journal_config cfg = { 1, "journal_nonexistent_dir/history.journal", 0 };
	TEST_ASSERT_EQUAL_INT(0, journal_create_checked(&current, sizeof(int), 0, cfg.file));
	TEST_ASSERT_NULL(current.fp);
	TEST_ASSERT_EQUAL_INT(1, current.io_error);
	journal_final(&current);
	create_record();
	TEST_ASSERT_EQUAL_INT(0, journal_recreate_checked(&current, &cfg, sizeof(int)));
	TEST_ASSERT_NULL(current.fp);
	TEST_ASSERT_EQUAL_INT(1, current.io_error);
}

static void test_binary_generation_header_length(void)
{
	FILE *fp;
	TEST_ASSERT_EQUAL_INT(1, journal_create_checked(&current, 10, 0, test_file));
	retain_file();
	fp = fopen(test_file, "rb");
	TEST_ASSERT_NOT_NULL(fp);
	TEST_ASSERT_EQUAL_INT(0, fseek(fp, 0, SEEK_END));
	TEST_ASSERT_EQUAL_UINT(sizeof(struct journal_fileheader), ftell(fp));
	fclose(fp);
	TEST_ASSERT_EQUAL_INT(0, journal_load_checked(&current, 10, test_file));
}

static void test_posix_generation_permissions(void)
{
#ifndef _WIN32
	struct stat info;
	struct journal_config cfg = { 1, "journal_test.tmp", 0 };
	mode_t old_mask;
	int result;
	FILE *fp;
	int lock;
	old_mask = umask(022);
	fp = lock_fopen_binary(test_file, &lock);
	umask(old_mask);
	TEST_ASSERT_NOT_NULL(fp);
	TEST_ASSERT_EQUAL_INT(0, fstat(fileno(fp), &info));
	TEST_ASSERT_EQUAL_UINT(0600, info.st_mode & 0777);
	TEST_ASSERT_EQUAL_INT(0, lock_fclose_checked(fp, test_file, &lock));
	journal_create(&current, sizeof(int), 0, test_file);
	TEST_ASSERT_EQUAL_INT(0, stat(test_file, &info));
	TEST_ASSERT_EQUAL_UINT(0600, info.st_mode & 0777);
	TEST_ASSERT_EQUAL_INT(0, chmod(test_file, 0640));
	old_mask = umask(022);
	result = journal_recreate_checked(&current, &cfg, sizeof(int));
	umask(old_mask);
	TEST_ASSERT_EQUAL_INT(1, result);
	TEST_ASSERT_EQUAL_INT(0, stat(test_file, &info));
	TEST_ASSERT_EQUAL_UINT(0640, info.st_mode & 0777);
#else
	TEST_IGNORE_MESSAGE("POSIX journal permission test");
#endif
}
static void test_posix_file_symlink_rejected(void)
{
#ifndef _WIN32
	struct stat info;
	const char *target = "journal_symlink_target_test.tmp";
	FILE *fp = fopen(target, "rb");
	if(fp) { fclose(fp); TEST_FAIL_MESSAGE("Symlink target already exists"); }
	journal_create(&current, sizeof(int), 0, target);
	symlink_target_owned = 1;
	retain_file();
	TEST_ASSERT_EQUAL_INT(0, symlink(target, test_file));
	TEST_ASSERT_EQUAL_INT(-1, journal_load_checked(&current, sizeof(int), test_file));
	journal_final(&current);
	TEST_ASSERT_EQUAL_INT(0, lstat(test_file, &info));
	TEST_ASSERT_TRUE(S_ISLNK(info.st_mode));
	TEST_ASSERT_EQUAL_INT(0, journal_create_checked(&current, sizeof(int), 0, test_file));
	journal_final(&current);
	TEST_ASSERT_EQUAL_INT(0, lstat(test_file, &info));
	TEST_ASSERT_TRUE(S_ISLNK(info.st_mode));
	TEST_ASSERT_EQUAL_INT(0, stat(target, &info));
	/* ]—ˆAPI‚ÍƒŠƒ“ƒNæ‚ð’¼ÚŠJ‚­•ûŽ®‚ðˆÛŽ‚·‚éB */
	journal_create(&current, sizeof(int), 0, test_file);
	TEST_ASSERT_EQUAL_INT(0, lstat(test_file, &info));
	TEST_ASSERT_TRUE(S_ISLNK(info.st_mode));
	retain_file();
	TEST_ASSERT_EQUAL_INT(0, unlink(test_file));
	TEST_ASSERT_EQUAL_INT(0, remove(target));
	symlink_target_owned = 0;
#else
	TEST_IGNORE_MESSAGE("POSIX journal symlink test");
#endif
}

#ifdef __linux__
static void make_linux_acl(unsigned char *acl, int owner, int named, int mask)
{
	int i, k;
	unsigned int uid = (unsigned int)getuid();
	const int tags[5] = {1, 2, 4, 16, 32};
	memset(acl, 0, 44);
	acl[0] = 2;
	for(i = 0; i < 5; i++) {
		acl[4 + i * 8] = (unsigned char)tags[i];
		for(k = 0; k < 4; k++)
			acl[8 + i * 8 + k] = i == 1 ? (unsigned char)(uid >> (k * 8)) : 0xff;
	}
	acl[6] = (unsigned char)owner;
	acl[14] = (unsigned char)named;
	acl[30] = (unsigned char)mask;
}
#endif
static void test_linux_extended_acl_preserved(void)
{
#ifdef __linux__
	unsigned char acl[44], actual[128];
	struct journal_config cfg = { 1, "journal_test.tmp", 0 };
	create_record();
	make_linux_acl(acl, 6, 4, 4);
	if(setxattr(test_file, "system.posix_acl_access", acl, sizeof(acl), 0) != 0) {
		if(errno == ENOTSUP) TEST_IGNORE_MESSAGE("Filesystem ACL unsupported");
		TEST_FAIL_MESSAGE("Cannot set ACL fixture");
	}
	TEST_ASSERT_EQUAL_INT(1, journal_recreate_checked(&current, &cfg, sizeof(int)));
	TEST_ASSERT_EQUAL_INT(sizeof(acl), getxattr(test_file, "system.posix_acl_access", actual, sizeof(actual)));
	TEST_ASSERT_EQUAL_MEMORY(acl, actual, sizeof(acl));
#else
	TEST_IGNORE_MESSAGE("Linux POSIX ACL test");
#endif
}
static void test_linux_inherited_acl_removed(void)
{
#ifdef __linux__
	unsigned char acl[44], actual[128];
	TEST_ASSERT_EQUAL_INT(0, mkdir("journal_acl_parent_test", 0700));
	acl_parent_owned = 1;
	make_linux_acl(acl, 7, 5, 5);
	if(setxattr("journal_acl_parent_test", "system.posix_acl_default", acl, sizeof(acl), 0) != 0) {
		if(errno == ENOTSUP) TEST_IGNORE_MESSAGE("Filesystem default ACL unsupported");
		TEST_FAIL_MESSAGE("Cannot set inherited ACL fixture");
	}
	TEST_ASSERT_EQUAL_INT(1, journal_create_checked(&current, sizeof(int), 0, "journal_acl_parent_test/history.journal"));
	TEST_ASSERT_EQUAL_INT(-1, getxattr("journal_acl_parent_test/history.journal", "system.posix_acl_access", actual, sizeof(actual)));
	TEST_ASSERT_EQUAL_INT(ENODATA, errno);
#else
	TEST_IGNORE_MESSAGE("Linux inherited ACL test");
#endif
}

static void test_legacy_create_keeps_existing_inode(void)
{
#ifndef _WIN32
	struct stat before, after;
	create_record();
	retain_file();
	TEST_ASSERT_EQUAL_INT(0, chmod(test_file, 0600));
	TEST_ASSERT_EQUAL_INT(0, stat(test_file, &before));
	journal_create(&current, sizeof(int), 0, test_file);
	TEST_ASSERT_EQUAL_INT(0, stat(test_file, &after));
	TEST_ASSERT_EQUAL_UINT(before.st_ino, after.st_ino);
	TEST_ASSERT_EQUAL_UINT(before.st_mode & 0777, after.st_mode & 0777);
#else
	BY_HANDLE_FILE_INFORMATION before, after;
	create_record();
	TEST_ASSERT_TRUE(GetFileInformationByHandle((HANDLE)_get_osfhandle(_fileno(current.fp)), &before));
	retain_file();
	create_record();
	TEST_ASSERT_TRUE(GetFileInformationByHandle((HANDLE)_get_osfhandle(_fileno(current.fp)), &after));
	TEST_ASSERT_EQUAL_UINT(before.dwVolumeSerialNumber, after.dwVolumeSerialNumber);
	TEST_ASSERT_EQUAL_UINT(before.nFileIndexHigh, after.nFileIndexHigh);
	TEST_ASSERT_EQUAL_UINT(before.nFileIndexLow, after.nFileIndexLow);
#endif
}

int main(void)
{
	FILE *fp = fopen(test_file, "rb");
	if(fp) { fclose(fp); return 1; }
	UNITY_BEGIN();
	RUN_TEST(test_immediate_write_and_delete);
	RUN_TEST(test_cached_write_and_same_second_recovery);
	RUN_TEST(test_write_failure_preserves_file_and_cache);
	RUN_TEST(test_flush_failure_retains_old_chunk);
	RUN_TEST(test_partial_batch_retry_update_and_delete);
	RUN_TEST(test_checked_txt_replacement_and_final_retention);
	RUN_TEST(test_write_failure_retry_saves_latest_value);
	RUN_TEST(test_timer_retry_of_failed_new_key);
	RUN_TEST(test_legacy_clock_rollback_both_physical_orders);
	RUN_TEST(test_corruption_strict_and_legacy);
	RUN_TEST(test_missing_empty_and_truncated_header);
	RUN_TEST(test_second_boundary_preserves_latest_tick);
	RUN_TEST(test_recreate_after_close_failure);
	RUN_TEST(test_empty_header_with_trailing_byte);
	RUN_TEST(test_write_flag_corrupted_to_delete);
	RUN_TEST(test_initial_tick_above_signed_range);
	RUN_TEST(test_legacy_long_interval_both_physical_orders);
	RUN_TEST(test_file_size_failure_preserves_records);
	RUN_TEST(test_tick_half_cycle_both_physical_orders);
	RUN_TEST(test_eof_before_known_record);
	RUN_TEST(test_partial_record_header);
	RUN_TEST(test_incompatible_layout_preserved);
	RUN_TEST(test_cashshop_journal_restart_composite_keys);
	RUN_TEST(test_cashshop_journal_checkpoint_and_generation);
	RUN_TEST(test_cashshop_journal_legacy_txt_monotonic);
	RUN_TEST(test_cashshop_journal_disabled_recovers_pending);
	RUN_TEST(test_cashshop_journal_flush_failure_holds_latest);
	RUN_TEST(test_cashshop_journal_corruption_preserves_txt);
	RUN_TEST(test_cashshop_journal_rejects_identity_mismatch);
	RUN_TEST(test_cashshop_journal_rejects_duplicate_composite);
	RUN_TEST(test_cashshop_journal_missing_base_rejected);
	RUN_TEST(test_cashshop_journal_disabled_save_failure);
	RUN_TEST(test_cashshop_journal_retains_past_catalog_history);
	RUN_TEST(test_cashshop_journal_detects_header_key_collision);
	RUN_TEST(test_cashshop_journal_ignores_damaged_tick_for_count);
	RUN_TEST(test_cashshop_journal_rejects_same_path);
	RUN_TEST(test_cashshop_journal_creation_failure_nonfatal);
	RUN_TEST(test_checked_create_and_recreate_nonfatal);
	RUN_TEST(test_cashshop_journal_short_alias_rejected);
	RUN_TEST(test_cashshop_journal_header_rotation_failure_recovers);
	RUN_TEST(test_cashshop_journal_disabled_missing_parent);
	RUN_TEST(test_binary_generation_header_length);
	RUN_TEST(test_posix_generation_permissions);
	RUN_TEST(test_posix_file_symlink_rejected);
	RUN_TEST(test_linux_extended_acl_preserved);
	RUN_TEST(test_linux_inherited_acl_removed);
	RUN_TEST(test_legacy_create_keeps_existing_inode);
	return UNITY_END();
}
