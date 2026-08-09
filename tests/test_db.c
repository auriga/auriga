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
