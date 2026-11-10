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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mmo.h"
#include "socket.h"
#include "db.h"
#include "malloc.h"
#include "sqldbs.h"
#include "nullpo.h"

#include "petdb_sql.h"
#include "maildb_sql.h"
#include "item_sql.h"

static struct dbt *mail_db = NULL;

/* 主キー順に一件ずつ走査し、末尾で先頭に戻る。 */
bool maildb_sql_next(int *char_id)
{
	static int cursor = 0;
	char **row;
	bool found = false;

	if(!sqldbs_query(&mysql_handle, "SELECT `char_id` FROM `" MAIL_TABLE "` WHERE `char_id` > '%d' ORDER BY `char_id` LIMIT 1", cursor))
		return false;
	row = sqldbs_fetch(&mysql_handle);
	if(row) {
		cursor = atoi(row[0]);
		*char_id = cursor;
		found = true;
	} else {
		cursor = 0;
	}
	sqldbs_free_result(&mysql_handle);
	return found;
}

/*==========================================
 * 設定ファイルの読込
 *------------------------------------------
 */
int maildb_sql_config_read_sub(const char *w1, const char *w2)
{
	return 0;
}

static bool maildb_sql_save_attachments(int char_id, unsigned int mail_num, const struct mail_data *md)
{
	int i;
	bool result;

	result = sqldbs_query(&mysql_handle,
		"DELETE FROM `" MAIL_ATTACHMENT_TABLE "` WHERE `char_id`='%d' AND `number`='%u'",
		char_id, mail_num);
	if(result == false)
		return false;

	/* 添付はすべてmail_attachmentに保存する */
	for(i = 0; i < MAIL_MAX_ITEM; i++) {
		const struct item *it = &md->item[i];
		if(it->nameid <= 0 || it->amount <= 0)
			continue;
		result = sqldbs_query(&mysql_handle,
			"INSERT INTO `" MAIL_ATTACHMENT_TABLE "` (`char_id`,`number`,`idx`,"
			"`id`,`nameid`,`amount`,`equip`,`identify`,`refine`,`attribute`,"
			"`card0`,`card1`,`card2`,`card3`,"
			"`opt0id`,`opt0val`,`opt1id`,`opt1val`,`opt2id`,`opt2val`,"
			"`opt3id`,`opt3val`,`opt4id`,`opt4val`,`limit`) VALUES ("
			"'%d','%u','%d',"
			"'%u','%d','%d','%u','%d','%d','%d',"
			"'%d','%d','%d','%d',"
			"'%d','%d','%d','%d','%d','%d',"
			"'%d','%d','%d','%d','%u')",
			char_id, mail_num, i,
			it->id, it->nameid, it->amount, it->equip, it->identify, it->refine, it->attribute,
			it->card[0], it->card[1], it->card[2], it->card[3],
			it->opt[0].id, it->opt[0].val, it->opt[1].id, it->opt[1].val, it->opt[2].id, it->opt[2].val,
			it->opt[3].id, it->opt[3].val, it->opt[4].id, it->opt[4].val, it->limit);
		if(result == false)
			return false;
	}
	return true;
}

static bool maildb_sql_load_attachments(int char_id, struct mail_data *md, int store)
{
	int i = 0;
	char **sql_row;
	bool result;

	result = sqldbs_query(&mysql_handle,
		"SELECT `number`, `idx`, " ITEM_SQL_COLUMNS
		" FROM `" MAIL_ATTACHMENT_TABLE "` WHERE `char_id`='%d' ORDER BY `number`,`idx`",
		char_id);
	if(result == false)
		return false;

	while((sql_row = sqldbs_fetch(&mysql_handle)) != NULL) {
		unsigned int number = (unsigned int)atoi(sql_row[0]);
		int idx = atoi(sql_row[1]);
		if(idx < 0 || idx >= MAIL_MAX_ITEM)
			continue;
		while(i < store && md[i].mail_num < number)
			i++;
		if(i < store && md[i].mail_num == number)
			item_sql_loadrow(&md[i].item[idx], &sql_row[2], 0);
	}
	sqldbs_free_result(&mysql_handle);
	return true;
}

/*==========================================
 * メール本文の保存
 *------------------------------------------
 */
bool maildb_sql_store_mail(int char_id, struct mail_data *md)
{
	unsigned int i;
	char buf[3][256], body_data[1024] = "";
	char *p = body_data;
	bool result = false;

	nullpo_retr(false, md);

	// SELECT HEX()
	for(i = 0; i< md->body_size; i++)
		p += sprintf(p, "%02X", (unsigned char)(md->body[i]));

	if(sqldbs_transaction_start(&mysql_handle) == false)
		return false;

	result = false;
	do {
		if(sqldbs_query(&mysql_handle,
			"INSERT INTO `" MAIL_DATA_TABLE "` (`char_id`, `number`, `read`, `send_id`, `send_name`, `receive_name`, `title`, "
			"`times`, `size`, `body`, `zeny`) "
			"VALUES ('%d','%u','%d','%d','%s','%s','%s','%u','%u','%s','%d')",
			char_id, md->mail_num, md->read, md->char_id, strecpy(buf[0], md->char_name), strecpy(buf[1], md->receive_name), strecpy(buf[2], md->title),
			md->times, md->body_size, body_data, md->zeny
		) == false)
			break;
		if(maildb_sql_save_attachments(char_id, md->mail_num, md) == false)
			break;
		result = true;
	} while(0);

	if(!sqldbs_transaction_end(&mysql_handle, result))
		return false;
	return result;
}

/*==========================================
 * メールのセーブ
 *------------------------------------------
 */
bool maildb_sql_save_mail(int char_id, int i, int store, struct mail_data *md)
{
	bool result = false;

	nullpo_retr(false, md);

	if(i < 0 || i >= store)
		return false;

	/* メール情報と添付をそれぞれ更新する */
	if(sqldbs_transaction_start(&mysql_handle) == false)
		return false;

	result = false;
	do {
		if(sqldbs_query(&mysql_handle,
			"UPDATE `" MAIL_DATA_TABLE "` SET `read` = '%d', `send_id` = '%d', `zeny` = '%d' "
			"WHERE `char_id` = '%d' AND `number` = '%u'",
			md[i].read, md[i].char_id, md[i].zeny,
			char_id, md[i].mail_num
		) == false)
			break;
		if(maildb_sql_save_attachments(char_id, md[i].mail_num, &md[i]) == false)
			break;
		result = true;
	} while(0);

	if(!sqldbs_transaction_end(&mysql_handle, result))
		return false;
	return result;
}

/*==========================================
 * メールの読み取り
 *------------------------------------------
 */
bool maildb_sql_read_mail(int char_id, const struct mail *m, struct mail_data *md, int capacity)
{
	int i;
	char **sql_row;
	bool result = false;

	nullpo_retr(false, md);
	if(capacity <= 0 || m == NULL || m->store > capacity)
		return false;

	result = sqldbs_query(&mysql_handle,
		"SELECT `number`, `read`, `send_id`, `send_name`, `receive_name`, `title`, `times`, `size`, `body`, `zeny` "
		"FROM `" MAIL_DATA_TABLE "` WHERE `char_id` = '%d' ORDER BY `number`", char_id
	);
	if(result == false)
		return false;

	for(i = 0; (sql_row = sqldbs_fetch(&mysql_handle)) && i < capacity; i++) {
		unsigned int n;
		char *p;

		memset(&md[i], 0, sizeof(md[i]));
		md[i].mail_num = (unsigned int)atoi(sql_row[0]);
		md[i].read     = atoi(sql_row[1]);
		md[i].char_id  = atoi(sql_row[2]);
		strncpy(md[i].char_name, sql_row[3] ,24);
		strncpy(md[i].receive_name, sql_row[4], 24);
		strncpy(md[i].title, sql_row[5], 40);
		md[i].times     = (unsigned int)atoi(sql_row[6]);
		md[i].body_size = (unsigned int)atoi(sql_row[7]);

		if(md[i].body_size > sizeof(md[i].body)) {
			printf("mail_read_mail: %d invalid body size %d!!\n", char_id, md[i].body_size);
			md[i].body_size = sizeof(md[i].body);
		}

		// SELECT UNHEX()
		for(n = 0, p = sql_row[8]; n < md[i].body_size && p[0] && p[1]; n++, p += 2) {
			int c = 0;
			sscanf(p, "%02x", &c);
			md[i].body[n] = c;
		}
		md[i].body_size = n;

		md[i].zeny = atoi(sql_row[9]);
	}
	sqldbs_free_result(&mysql_handle);

	if(i > 0 && maildb_sql_load_attachments(char_id, md, i) == false) {
		printf("mail_read_mail: %d attachment load failed\n", char_id);
		return false;
	}

	if(i != m->store && m->store <= capacity) {	// 数に相違あり？
		struct mail m2;
		printf("mail_read_mail: %d stored number mismatch!! (%d != %d)\n", char_id, i, m->store);
		memcpy(&m2, m, sizeof(struct mail));
		if(i > 0 && m2.rates < md[i-1].mail_num) {
			m2.rates = md[i-1].mail_num;
		}
		m2.store = i;
		maildb_sql_save(&m2);
	}
	return true;
}

/*==========================================
 * メール削除
 *------------------------------------------
 */
bool maildb_sql_deletemail(int char_id, unsigned int mail_num, const struct mail *m)
{
	struct mail m2;
	bool result = false;

	nullpo_retr(false, m);
	if(m->store <= 0)
		return false;

	if(!sqldbs_transaction_start(&mysql_handle))
		return false;

	result = false;
	do {
		if(!sqldbs_query(&mysql_handle, "DELETE FROM `" MAIL_ATTACHMENT_TABLE "` WHERE `char_id` = '%d' AND `number` = '%u'", char_id, mail_num))
			break;
		if(!sqldbs_query(&mysql_handle, "DELETE FROM `" MAIL_DATA_TABLE "` WHERE `char_id` = '%d' AND `number` = '%u'", char_id, mail_num))
			break;
		if(sqldbs_affected_rows(&mysql_handle) <= 0)
			break;
		memcpy(&m2, m, sizeof(struct mail));
		m2.store--;
		if(!sqldbs_query(&mysql_handle, "UPDATE `" MAIL_TABLE "` SET `store` = '%d' WHERE `char_id` = '%d'", m2.store, char_id))
			break;
		result = true;
	} while(0);

	if(!sqldbs_transaction_end(&mysql_handle, result) || !result)
		return false;
	{
		struct mail *cached = (struct mail *)numdb_search(mail_db, char_id);
		if(cached)
			memcpy(cached, &m2, sizeof(struct mail));
	}

	return true;
}

/*==========================================
 * 同期
 *------------------------------------------
 */
int maildb_sql_sync(void)
{
	// nothing to do
	return 0;
}

/*==========================================
 * キャラ削除によるメール削除
 *------------------------------------------
 */
bool maildb_sql_delete(int char_id)
{
	struct mail *m = (struct mail *)numdb_search(mail_db, char_id);
	bool result = false;

	if(!sqldbs_transaction_start(&mysql_handle))
		return false;
	do {
		if(m) {
			int i, j;
			struct mail_data *md = NULL;
			if(m->store < 0)
				break;
			if(m->store > 0) {
				int capacity = m->store;
				md = (struct mail_data *)calloc((size_t)capacity, sizeof(*md));
				if(md == NULL)
					break;
				if(!maildb_sql_read_mail(char_id, m, md, capacity)) {
					free(md);
					break;
				}
			}
			for(i = 0; i < m->store; i++) {
				for(j = 0; j < MAIL_MAX_ITEM; j++) {
					if(md[i].item[j].card[0] == (int)0xff00 &&
					   !petdb_delete(*((int *)(&md[i].item[j].card[1]))))
						break;
				}
				if(j < MAIL_MAX_ITEM)
					break;
			}
			free(md);
			if(i < m->store)
				break;
		}
		if(!sqldbs_query(&mysql_handle, "DELETE FROM `" MAIL_ATTACHMENT_TABLE "` WHERE `char_id` = '%d'", char_id))
			break;
		if(!sqldbs_query(&mysql_handle, "DELETE FROM `" MAIL_DATA_TABLE "` WHERE `char_id` = '%d'", char_id))
			break;
		if(!sqldbs_query(&mysql_handle, "DELETE FROM `" MAIL_TABLE "` WHERE `char_id` = '%d'", char_id))
			break;
		result = true;
	} while(0);
	if(!sqldbs_transaction_end(&mysql_handle, result) || !result)
		return false;
	if(m && m->char_id == char_id) {
		numdb_erase(mail_db, char_id);
		aFree(m);
	}
	return true;
}

/*==========================================
 * キャラIDからメールデータをロード
 *------------------------------------------
 */
const struct mail* maildb_sql_load(int char_id)
{
	bool result;
	char **sql_row;
	struct mail *m = (struct mail *)numdb_search(mail_db, char_id);

	// 既にキャッシュが存在する
	if(m && m->char_id == char_id)
		return m;

	// キャッシュの作成
	if(m == NULL)
	{
		m = (struct mail *)aMalloc(sizeof(struct mail));
		numdb_insert(mail_db, char_id, m);
	}
	memset(m, 0, sizeof(struct mail));

	m->char_id = char_id;

	result = sqldbs_query(&mysql_handle, "SELECT `account_id`, `rates`, `store` FROM `" MAIL_TABLE "` WHERE `char_id` = '%d'", char_id);
	if(result == false) {
		m->char_id = -1;
		return NULL;
	}

	if((sql_row = sqldbs_fetch(&mysql_handle)) != NULL) {
		m->account_id = atoi(sql_row[0]);
		m->rates      = (unsigned int)atoi(sql_row[1]);
		m->store      = atoi(sql_row[2]);

		if(m->store < 0) {
			m->char_id = -1;
			m = NULL;
		}
	} else {
		// 見つからなくても正常
		m->char_id = -1;
		m = NULL;
	}
	sqldbs_free_result(&mysql_handle);

	return m;
}

/*==========================================
 * セーブ
 *------------------------------------------
 */
bool maildb_sql_save(struct mail *m2)
{
	const struct mail *m1;
	bool result = false;

	nullpo_retr(false, m2);

	m1 = maildb_sql_load(m2->char_id);
	if(m1 == NULL || m1->char_id != m2->char_id)
		return false;

	if( sqldbs_transaction_start(&mysql_handle) == false )
		return false;

	// try
	do
	{
		// delete mail
		if( sqldbs_query(&mysql_handle, "DELETE FROM `" MAIL_TABLE "` WHERE `char_id`='%d'", m2->char_id) == false )
			break;

		// insert val
		if( sqldbs_query(&mysql_handle,"INSERT INTO `" MAIL_TABLE "` (`char_id`, `account_id`, `rates`, `store`) VALUES ('%d','%d','%u','%d')",m2->char_id, m2->account_id, m2->rates, m2->store) == false )
			break;

		// success
		result = true;

		{
			// cache copy
			struct mail *m3 = (struct mail *)numdb_search(mail_db, m2->char_id);
			if(m3)
				memcpy(m3, m2, sizeof(struct mail));
		}
	} while(0);

	sqldbs_transaction_end(&mysql_handle, result);

	return result;
}

/*==========================================
 * メール作成
 *------------------------------------------
 */
bool maildb_sql_new(int account_id, int char_id)
{
	bool result = false;
	struct mail *m = (struct mail *)numdb_search(mail_db, char_id);

	// mail_load() でmail_dbに登録したあと呼ばれるはずだが念のため
	if(m == NULL) {
		m = (struct mail *)aMalloc(sizeof(struct mail));
		numdb_insert(mail_db, char_id, m);
	}

	m->account_id = account_id;
	m->char_id = char_id;
	m->rates = 1;
	m->store = 1;

	result = sqldbs_query(&mysql_handle,
		"INSERT INTO `" MAIL_TABLE "` (`char_id`, `account_id`, `rates`, `store`) VALUES ('%d','%d','%u','%d')",
		m->char_id, m->account_id, m->rates, m->store
	);

	return result;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
static int maildb_sql_final_sub(void *key, void *data, va_list ap)
{
	struct mail *md = (struct mail *)data;

	aFree(md);

	return 0;
}

void maildb_sql_final(void)
{
	if(mail_db)
		numdb_final(mail_db,maildb_sql_final_sub);
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
bool maildb_sql_init(void)
{
	mail_db = numdb_init();
	return true;
}
