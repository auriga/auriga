#include <stdio.h>
#include <string.h>

#include "unity.h"
#include "utils.h"
#include "db.h"

void test_linkdb_insert_search_erase(void)
{
	struct linkdb_node *head = NULL;
	int key_a = 1, key_b = 2;
	int data_a = 10, data_b = 20;
	void *old;

	linkdb_insert(&head, &key_a, &data_a);
	linkdb_insert(&head, &key_b, &data_b);

	TEST_ASSERT_TRUE(linkdb_exists(&head, &key_a));
	TEST_ASSERT_TRUE(linkdb_exists(&head, &key_b));
	TEST_ASSERT_EQUAL_PTR(&data_a, linkdb_search(&head, &key_a));
	TEST_ASSERT_EQUAL_PTR(&data_b, linkdb_search(&head, &key_b));

	old = linkdb_erase(&head, &key_a);
	TEST_ASSERT_EQUAL_PTR(&data_a, old);
	TEST_ASSERT_FALSE(linkdb_exists(&head, &key_a));
	TEST_ASSERT_TRUE(linkdb_exists(&head, &key_b));

	linkdb_final(&head);
	TEST_ASSERT_NULL(head);
}

void test_linkdb_replace(void)
{
	struct linkdb_node *head = NULL;
	int key = 7;
	int data1 = 100, data2 = 200;
	void *old;

	linkdb_insert(&head, &key, &data1);
	old = linkdb_replace(&head, &key, &data2);
	TEST_ASSERT_EQUAL_PTR(&data1, old);
	TEST_ASSERT_EQUAL_PTR(&data2, linkdb_search(&head, &key));

	linkdb_final(&head);
}

void test_linkdb_replace_inserts_missing(void)
{
	struct linkdb_node *head = NULL;
	int key = 9;
	int data = 99;
	void *old;

	old = linkdb_replace(&head, &key, &data);
	TEST_ASSERT_NULL(old);
	TEST_ASSERT_TRUE(linkdb_exists(&head, &key));
	TEST_ASSERT_EQUAL_PTR(&data, linkdb_search(&head, &key));

	linkdb_final(&head);
}

static int foreach_count_cb(void *key, void *data, va_list ap)
{
	int *count = va_arg(ap, int *);

	(void)key;
	(void)data;
	(*count)++;
	return 1;
}

void test_numdb_crud(void)
{
	struct dbt *db = numdb_init();
	int data1 = 11, data2 = 22;
	void *old;
	int count = 0;

	TEST_ASSERT_NOT_NULL(db);
	TEST_ASSERT_NULL(numdb_search(db, 1));
	TEST_ASSERT_FALSE(numdb_exists(db, 1));

	TEST_ASSERT_NULL(numdb_insert(db, 1, &data1));
	TEST_ASSERT_NULL(numdb_insert(db, 2, &data2));
	TEST_ASSERT_TRUE(numdb_exists(db, 1));
	TEST_ASSERT_EQUAL_PTR(&data1, numdb_search(db, 1));
	TEST_ASSERT_EQUAL_PTR(&data2, numdb_search(db, 2));

	old = numdb_insert(db, 1, &data2);
	TEST_ASSERT_EQUAL_PTR(&data1, old);
	TEST_ASSERT_EQUAL_PTR(&data2, numdb_search(db, 1));

	count = 0;
	TEST_ASSERT_EQUAL_INT(2, numdb_foreach(db, foreach_count_cb, &count));
	TEST_ASSERT_EQUAL_INT(2, count);

	old = numdb_erase(db, 2);
	TEST_ASSERT_EQUAL_PTR(&data2, old);
	TEST_ASSERT_FALSE(numdb_exists(db, 2));

	numdb_final(db, NULL);
}

void test_strdb_crud(void)
{
	struct dbt *db = strdb_init(0);
	int data_a = 1, data_b = 2;
	void *old;

	TEST_ASSERT_NOT_NULL(db);
	TEST_ASSERT_NULL(strdb_insert(db, "alpha", &data_a));
	TEST_ASSERT_NULL(strdb_insert(db, "beta", &data_b));
	TEST_ASSERT_TRUE(strdb_exists(db, "alpha"));
	TEST_ASSERT_EQUAL_PTR(&data_a, strdb_search(db, "alpha"));
	TEST_ASSERT_EQUAL_PTR(&data_b, strdb_search(db, "beta"));

	old = strdb_erase(db, "alpha");
	TEST_ASSERT_EQUAL_PTR(&data_a, old);
	TEST_ASSERT_FALSE(strdb_exists(db, "alpha"));

	strdb_final(db, NULL);
}

void test_csvdb_memory_ops(void)
{
	struct csvdb_data *csv;
	const char *path = "auriga_ut_csvdb_missing.csv";

	csv = csvdb_open(path, 0);
	TEST_ASSERT_NOT_NULL(csv);
	TEST_ASSERT_EQUAL_INT(0, csvdb_get_rows(csv));

	TEST_ASSERT_TRUE(csvdb_set_num(csv, 0, 0, 30));
	TEST_ASSERT_TRUE(csvdb_set_str(csv, 0, 1, "carol"));
	TEST_ASSERT_TRUE(csvdb_set_num(csv, 1, 0, 10));
	TEST_ASSERT_TRUE(csvdb_set_str(csv, 1, 1, "alice"));
	TEST_ASSERT_TRUE(csvdb_set_num(csv, 2, 0, 20));
	TEST_ASSERT_TRUE(csvdb_set_str(csv, 2, 1, "bob"));
	TEST_ASSERT_EQUAL_INT(3, csvdb_get_rows(csv));
	TEST_ASSERT_EQUAL_INT(2, csvdb_get_columns(csv, 0));

	TEST_ASSERT_EQUAL_INT(1, csvdb_find_num(csv, 0, 10));
	TEST_ASSERT_EQUAL_INT(2, csvdb_find_str(csv, 1, "bob"));
	TEST_ASSERT_EQUAL_STRING("carol", csvdb_get_str(csv, 0, 1));

	TEST_ASSERT_TRUE(csvdb_sort(csv, 0, 1));
	TEST_ASSERT_EQUAL_INT(10, csvdb_get_num(csv, 0, 0));
	TEST_ASSERT_EQUAL_INT(20, csvdb_get_num(csv, 1, 0));
	TEST_ASSERT_EQUAL_INT(30, csvdb_get_num(csv, 2, 0));

	TEST_ASSERT_TRUE(csvdb_delete_row(csv, 1));
	TEST_ASSERT_EQUAL_INT(2, csvdb_get_rows(csv));
	TEST_ASSERT_EQUAL_INT(-1, csvdb_find_num(csv, 0, 20));

	/* Avoid flush of a missing path on close. */
	csv->dirty = 0;
	csvdb_close(csv);
	remove(path);
}

void test_csvdb_open_parse_file(void)
{
	struct csvdb_data *csv;
	const char *path = "auriga_ut_csvdb_sample.csv";
	FILE *fp = fopen(path, "wb");

	TEST_ASSERT_NOT_NULL(fp);
	fputs("1,hello\n", fp);
	fputs("// comment\n", fp);
	fputs("2,world\n", fp);
	fclose(fp);

	csv = csvdb_open(path, 1);
	TEST_ASSERT_NOT_NULL(csv);
	TEST_ASSERT_EQUAL_INT(2, csvdb_get_rows(csv));
	TEST_ASSERT_EQUAL_INT(1, csvdb_get_num(csv, 0, 0));
	TEST_ASSERT_EQUAL_STRING("hello", csvdb_get_str(csv, 0, 1));
	TEST_ASSERT_EQUAL_INT(2, csvdb_get_num(csv, 1, 0));
	TEST_ASSERT_EQUAL_STRING("world", csvdb_get_str(csv, 1, 1));

	csvdb_close(csv);
	remove(path);
}

void test_arr_find(void)
{
	int list[] = { 3, 7, 9, 12 };
	int i = -1;

	ARR_FIND(0, 4, i, list[i] == 9);
	TEST_ASSERT_EQUAL_INT(2, i);

	ARR_FIND(0, 4, i, list[i] == 99);
	TEST_ASSERT_EQUAL_INT(4, i);
}
