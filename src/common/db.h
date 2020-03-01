/*
 * Copyright (C) 2002-2020  Auriga
 *
 * This file is part of Auriga.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef _DB_H_
#define _DB_H_

#include <stdarg.h>

#define HASH_SIZE (256+27)

#define RED 0
#define BLACK 1

struct dbn {
	struct dbn *parent,*left,*right;
	void *key;
	void *data;
	char color;
	char deleted;	// 削除済みフラグ(db_foreach)
};

struct db_free {
	struct dbn *z;
	struct dbn **root;
};

struct dbt {
	int (*cmp)(struct dbt*,const void*,const void*);
	unsigned int (*hash)(struct dbt*,void*);
	int maxlen;
	struct dbn *ht[HASH_SIZE];
	int item_count; // 要素の数
	const char* alloc_file; // DBが初期化されたファイル
	int         alloc_line; // DBが初期化された行

	// db_foreach 内部でdb_erase される対策として、
	// db_foreach が終わるまでロックすることにする
	struct db_free *free_list;
	int free_count;
	int free_max;
	int free_lock;
};

#define strdb_search(t,k)   db_search((t),(void*)(k))
#define strdb_exists(t,k)   db_exists((t),(void*)(k))
#define strdb_insert(t,k,d) db_insert((t),(void*)(k),(void*)(d))
#define strdb_erase(t,k)    db_erase ((t),(void*)(k))
#define strdb_foreach       db_foreach
#define strdb_clear         db_clear
#define strdb_final         db_final
#define numdb_search(t,k)   db_search((t),(void*)(intptr)(k))
#define numdb_exists(t,k)   db_exists((t),(void*)(intptr)(k))
#define numdb_insert(t,k,d) db_insert((t),(void*)(intptr)(k),(void*)(d))
#define numdb_erase(t,k)    db_erase ((t),(void*)(intptr)(k))
#define numdb_foreach       db_foreach
#define numdb_clear         db_clear
#define numdb_final         db_final

#define strdb_init(a)       strdb_init_(a,__FILE__,__LINE__)
#define numdb_init()        numdb_init_(__FILE__,__LINE__)

struct dbt* strdb_init_(int maxlen,const char *file,int line);
struct dbt* numdb_init_(const char *file,int line);
void* db_search(struct dbt *table,void* key);
int   db_exists(struct dbt *table,void* key);
void* db_insert(struct dbt *table,void* key,void* data);
void* db_erase(struct dbt *table,void* key);
int db_foreach(struct dbt*,int(*)(void*,void*,va_list),...);
int db_foreach_sub(struct dbt*,int(*)(void*,void*,va_list), va_list ap);
int db_clear(struct dbt*,int(*)(void*,void*,va_list),...);
int db_final(struct dbt*,int(*)(void*,void*,va_list),...);
void exit_dbn(void);

// リンクリストDB -- treedb よりも規模が小さいやつ向けのデータベース
// 　・キーの重複チェックはreplace のみ
// 　・負荷対策のため、事前の初期化はheadにNULLを代入するだけ
// 　・linkdb_node は関数内で確保するため、利用側はポインタ１つを宣言するだけ

struct linkdb_node {
	struct linkdb_node *next;
	struct linkdb_node *prev;
	void               *key;
	void               *data;
};

void  linkdb_insert(struct linkdb_node** head, void *key, void* data); // 重複を考慮しない
void* linkdb_replace(struct linkdb_node** head, void *key, void* data); // 重複を考慮する
void* linkdb_search(struct linkdb_node** head, void *key);
int   linkdb_exists(struct linkdb_node** head, void *key);
void* linkdb_erase(struct linkdb_node** head, void *key);
void  linkdb_final(struct linkdb_node** head);

// csvdb -- csv ファイルの読み込み関数

// 最大列数
#define MAX_CSVCOL 128

struct csvdb_line {
	int   num;
	char *buf;
	char *data_p[MAX_CSVCOL];
	int   data_v[MAX_CSVCOL];
};

struct csvdb_data {
	struct csvdb_line *data;
	char *file;
	int  *index;
	int row_max;
	int row_count;
	int row_notempty;
	int dirty;
};

struct csvdb_data* csvdb_open(const char* file, int skip_comment);
int csvdb_get_rows(struct csvdb_data *csv);
int csvdb_get_columns(struct csvdb_data *csv, int row);
int csvdb_get_num(struct csvdb_data *csv, int row, int col);
const char* csvdb_get_str(struct csvdb_data *csv, int row, int col);
int csvdb_set_num(struct csvdb_data *csv, int row, int col, int num);
int csvdb_set_str(struct csvdb_data *csv, int row, int col, const char* str);
int csvdb_find_num(struct csvdb_data *csv, int col, int value);
int csvdb_find_str(struct csvdb_data *csv, int col, const char* value);
int csvdb_clear_row(struct csvdb_data *csv, int row);
int csvdb_sort(struct csvdb_data *csv, int key, int order);
int csvdb_delete_row(struct csvdb_data *csv, int row);
int csvdb_insert_row(struct csvdb_data *csv, int row);
int csvdb_flush(struct csvdb_data *csv);
void csvdb_close(struct csvdb_data *csv);
void csvdb_dump(struct csvdb_data* csv);

#endif
