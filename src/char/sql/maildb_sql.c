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

static struct dbt *mail_db = NULL;

/*==========================================
 * 設定ファイルの読込
 *------------------------------------------
 */
int maildb_sql_config_read_sub(const char *w1, const char *w2)
{
	return 0;
}

/*==========================================
 * メール本文の保存
 *------------------------------------------
 */
bool maildb_sql_store_mail(int char_id, struct mail_data *md)
{
	unsigned int i;
	char buf[3][256], body_data[1024];
	char *p = body_data;
	bool result = false;

	nullpo_retr(false, md);

	// SELECT HEX()
	for(i = 0; i< md->body_size; i++)
		p += sprintf(p, "%02X", (unsigned char)(md->body[i]));

	result = sqldbs_query(&mysql_handle,
		"INSERT INTO `" MAIL_DATA_TABLE "` (`char_id`, `number`, `read`, `send_name`, `receive_name`, `title`, "
		"`times`, `size`, `body`, `zeny`, "
		"`id`, `nameid`, `amount`, `equip`, `identify`, `refine`, `attribute`, "
		"`card0`, `card1`, `card2`, `card3`,"
		"`opt0id`, `opt0val`, `opt1id`, `opt1val`, `opt2id`, `opt2val`,"
		"`opt3id`, `opt3val`, `opt4id`, `opt4val`, `limit`) "
		"VALUES ('%d','%u','%d','%s','%s','%s','%u','%u','%s',"
		"'%d','%u','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d',"
		"'%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%u')",
		char_id, md->mail_num, md->read, strecpy(buf[0], md->char_name), strecpy(buf[1], md->receive_name), strecpy(buf[2], md->title),
		md->times, md->body_size, body_data,
		md->zeny, md->item.id, md->item.nameid, md->item.amount, md->item.equip, md->item.identify, md->item.refine, md->item.attribute,
		md->item.card[0], md->item.card[1], md->item.card[2], md->item.card[3],
		md->item.opt[0].id, md->item.opt[0].val, md->item.opt[1].id, md->item.opt[1].val, md->item.opt[2].id, md->item.opt[2].val,
		md->item.opt[3].id, md->item.opt[3].val, md->item.opt[4].id, md->item.opt[4].val, md->item.limit
	);

	return result;
}

/*==========================================
 * メールのセーブ
 *------------------------------------------
 */
bool maildb_sql_save_mail(int char_id, int i, int store, struct mail_data md[MAIL_STORE_MAX])
{
	bool result = false;

	nullpo_retr(false, md);

	if(i < 0 || i >= MAIL_STORE_MAX)
		return false;

	// readもしくはzeny,itemデータを更新するだけでよい
	result = sqldbs_query(&mysql_handle,
		"UPDATE `" MAIL_DATA_TABLE "` SET `read` = '%d', `zeny` = '%d', "
		"`id` = '%u', `nameid` = '%d', `amount` = '%d', `equip` = '%d', `identify` = '%d', `refine` = '%d', `attribute` = '%d', "
		"`card0` = '%d', `card1` = '%d', `card2` = '%d', `card3` = '%d', "
		"`opt0id` = '%d', `opt0val` = '%d', `opt1id` = '%d', `opt1val` = '%d', `opt2id` = '%d', `opt2val` = '%d', "
		"`opt3id` = '%d', `opt3val` = '%d', `opt4id` = '%d', `opt4val` = '%d', `limit` = '%u' "
		"WHERE `char_id` = '%d' AND `number` = '%u'",
		md[i].read, md[i].zeny,
		md[i].item.id, md[i].item.nameid, md[i].item.amount, md[i].item.equip, md[i].item.identify, md[i].item.refine, md[i].item.attribute,
		md[i].item.card[0], md[i].item.card[1], md[i].item.card[2], md[i].item.card[3],
		md[i].item.opt[0].id, md[i].item.opt[0].val, md[i].item.opt[1].id, md[i].item.opt[1].val, md[i].item.opt[2].id, md[i].item.opt[2].val,
		md[i].item.opt[3].id, md[i].item.opt[3].val, md[i].item.opt[4].id, md[i].item.opt[4].val, md[i].item.limit,
		char_id, md[i].mail_num
	);

	return result;
}

/*==========================================
 * メールの読み取り
 *------------------------------------------
 */
bool maildb_sql_read_mail(int char_id, const struct mail *m, struct mail_data md[MAIL_STORE_MAX])
{
	int i;
	char **sql_row;
	bool result = false;

	nullpo_retr(false, md);

	result = sqldbs_query(&mysql_handle,
		"SELECT `number`, `read`, `send_name`, `receive_name`, `title`, `times`, `size`, `body`, `zeny`, "
		"`id`, `nameid`, `amount`, `equip`, `identify`, `refine`, `attribute`, "
		"`card0`, `card1`, `card2`, `card3`, "
		"`opt0id`, `opt0val`, `opt1id`, `opt1val`, `opt2id`, `opt2val`, "
		"`opt3id`, `opt3val`, `opt4id`, `opt4val`, `limit`"
		" FROM `" MAIL_DATA_TABLE "` WHERE `char_id` = '%d' ORDER BY `number`", char_id
	);
	if(result == false)
		return false;

	for(i = 0; (sql_row = sqldbs_fetch(&mysql_handle)) && i < MAIL_STORE_MAX; i++) {
		unsigned int n;
		char *p;

		md[i].mail_num = (unsigned int)atoi(sql_row[0]);
		md[i].read     = atoi(sql_row[1]);
		strncpy(md[i].char_name, sql_row[2] ,24);
		strncpy(md[i].receive_name, sql_row[3], 24);
		strncpy(md[i].title, sql_row[4], 40);
		md[i].times     = (unsigned int)atoi(sql_row[5]);
		md[i].body_size = (unsigned int)atoi(sql_row[6]);

		if(md[i].body_size > sizeof(md[i].body)) {
			printf("mail_read_mail: %d invalid body size %d!!\n", char_id, md[i].body_size);
			md[i].body_size = sizeof(md[i].body);
		}

		// SELECT UNHEX()
		for(n = 0, p = sql_row[7]; n < md[i].body_size && p[0] && p[1]; n++, p += 2) {
			int c = 0;
			sscanf(p, "%02x", &c);
			md[i].body[n] = c;
		}
		md[i].body_size = n;

		md[i].zeny            = atoi(sql_row[8]);
		md[i].item.id         = (unsigned int)atoi(sql_row[9]);
		md[i].item.nameid     = atoi(sql_row[10]);
		md[i].item.amount     = atoi(sql_row[11]);
		md[i].item.equip      = (unsigned int)atoi(sql_row[12]);
		md[i].item.identify   = atoi(sql_row[13]);
		md[i].item.refine     = atoi(sql_row[14]);
		md[i].item.attribute  = atoi(sql_row[15]);
		md[i].item.card[0]    = atoi(sql_row[16]);
		md[i].item.card[1]    = atoi(sql_row[17]);
		md[i].item.card[2]    = atoi(sql_row[18]);
		md[i].item.card[3]    = atoi(sql_row[19]);
		md[i].item.opt[0].id  = atoi(sql_row[20]);
		md[i].item.opt[0].val = atoi(sql_row[21]);
		md[i].item.opt[1].id  = atoi(sql_row[22]);
		md[i].item.opt[1].val = atoi(sql_row[23]);
		md[i].item.opt[2].id  = atoi(sql_row[24]);
		md[i].item.opt[2].val = atoi(sql_row[25]);
		md[i].item.opt[3].id  = atoi(sql_row[26]);
		md[i].item.opt[3].val = atoi(sql_row[27]);
		md[i].item.opt[4].id  = atoi(sql_row[28]);
		md[i].item.opt[4].val = atoi(sql_row[29]);
		md[i].item.limit      = (unsigned int)atoi(sql_row[30]);
	}
	sqldbs_free_result(&mysql_handle);

	if(i != m->store) {	// 数に相違あり？
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
	struct mail_data md[MAIL_STORE_MAX];
	struct mail m2;
	int i;
	bool result = false;

	nullpo_retr(false, m);

	memset(md, 0, sizeof(md));
	maildb_sql_read_mail(char_id, m, md);

	for(i = 0; i < m->store; i++) {
		if(md[i].mail_num == mail_num)
			break;
	}
	if(i >= m->store)
		return false;

	result = sqldbs_query(&mysql_handle, "DELETE FROM `" MAIL_DATA_TABLE "` WHERE `char_id` = '%d' AND `number` = '%u'", char_id, mail_num);
	if(result == false)
		return false;

	if(sqldbs_affected_rows(&mysql_handle) <= 0)
	{
		// 削除失敗
		return false;
	}

	memcpy(&m2, m, sizeof(struct mail));
	m2.store--;
	maildb_sql_save(&m2);

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

	if( sqldbs_transaction_start(&mysql_handle) == false )
		return result;

	// try
	do
	{
		if(m) {
			int i;
			struct mail_data md[MAIL_STORE_MAX];

			memset(md, 0, sizeof(md));
			maildb_sql_read_mail(char_id, m, md);

			for(i = 0; i < m->store; i++) {
				// ペット削除
				if(md[i].item.card[0] == (short)0xff00) {
					if( petdb_delete(*((int *)(&md[i].item.card[1]))) == false )
						break;
				}
			}
			if(i != m->store)
				break;
		}

		// delete mail
		if( sqldbs_query(&mysql_handle, "DELETE FROM `" MAIL_TABLE "` WHERE `char_id` = '%d'", char_id) == false )
			break;

		// delete mail data
		if( sqldbs_query(&mysql_handle, "DELETE FROM `" MAIL_DATA_TABLE "` WHERE `char_id` = '%d'", char_id) == false )
			break;

		// success
		result = true;

		if(m && m->char_id == char_id)
		{
			// cache delete
			numdb_erase(mail_db, char_id);
			aFree(m);
		}
	} while(0);

	sqldbs_transaction_end(&mysql_handle, result);

	return false;
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

		if(m->store < 0 || m->store >= MAIL_STORE_MAX) {	// 値が異常なので補正する
			struct mail_data md[MAIL_STORE_MAX];
			memset(md, 0, sizeof(md));
			maildb_sql_read_mail(m->char_id, m, md);
		}
	} else {
		// 見つからなくても正常
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
