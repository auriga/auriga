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

#include "mmo.h"
#include "socket.h"
#include "db.h"
#include "lock.h"
#include "malloc.h"
#include "utils.h"
#include "nullpo.h"

#include "petdb_txt.h"
#include "maildb_txt.h"

static struct dbt *mail_db = NULL;

static char mail_dir[1024] = "save/mail_data/";
static char mail_txt[1024] = "save/mail.txt";

/*==========================================
 * 設定ファイルの読み込み
 *------------------------------------------
 */
int maildb_txt_config_read_sub(const char *w1, const char *w2)
{
	if(strcmpi(w1,"mail_txt")==0) {
		strncpy(mail_txt, w2, sizeof(mail_txt) - 1);
	}
	else if(strcmpi(w1,"mail_dir")==0) {
		strncpy(mail_dir, w2, sizeof(mail_dir) - 1);
	}
	else {
		return 0;
	}

	return 1;
}

/*==========================================
 * メール本文の保存
 *------------------------------------------
 */
bool maildb_txt_store_mail(int char_id, struct mail_data *md)
{
	char filename[1056];
	FILE *fp;
	unsigned int i;

	nullpo_retr(false, md);

	sprintf(filename, "%s%d.txt", mail_dir, char_id);

	fp = fopen(filename, "a");
	if(fp == NULL)
	{
		printf("maildb_txt_store_mail: can't write [%s] !!! data is lost !!!\n", filename);
		return false;
	}

	fprintf(fp, "%u,%d\t%s\t%s\t%s\t%d\t%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u\t%u\t%u\t",
		md->mail_num, md->read, md->char_name, md->receive_name, md->title, md->zeny,
		md->item.id, md->item.nameid, md->item.amount, md->item.equip,
		md->item.identify, md->item.refine, md->item.attribute,
		md->item.card[0], md->item.card[1], md->item.card[2], md->item.card[3],
		md->item.opt[0].id, md->item.opt[0].val, md->item.opt[1].id, md->item.opt[1].val, md->item.opt[2].id, md->item.opt[2].val,
		md->item.opt[3].id, md->item.opt[3].val, md->item.opt[4].id, md->item.opt[4].val, md->item.limit,
		md->times, md->body_size);

	for(i = 0; i < md->body_size; i++) {
		fprintf(fp, "%02X", (unsigned char)(md->body[i]));
	}
	fprintf(fp, NEWLINE);
	fclose(fp);

	return true;
}

/*==========================================
 * メールのセーブ
 *------------------------------------------
 */
bool maildb_txt_save_mail(int char_id, int i, int store, struct mail_data md[MAIL_STORE_MAX])
{
	char filename[1056];
	FILE *fp;
	unsigned int j;
	int n = 0, lock;

	nullpo_retr(false, md);

	sprintf(filename, "%s%d.txt", mail_dir, char_id);

	fp = lock_fopen(filename, &lock);
	if(fp == NULL)
	{
		printf("maildb_txt_save_mail: can't write [%s] !!! data is lost !!!\n", filename);
		return false;
	}

	while(n < store)
	{
		fprintf(fp, "%u,%d\t%s\t%s\t%s\t%d\t%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u\t%u\t%u\t",
			md[n].mail_num, md[n].read, md[n].char_name, md[n].receive_name, md[n].title, md[n].zeny,
			md[n].item.id, md[n].item.nameid, md[n].item.amount, md[n].item.equip,
			md[n].item.identify, md[n].item.refine, md[n].item.attribute,
			md[n].item.card[0], md[n].item.card[1], md[n].item.card[2], md[n].item.card[3],
			md[n].item.opt[0].id, md[n].item.opt[0].val, md[n].item.opt[1].id, md[n].item.opt[1].val, md[n].item.opt[2].id, md[n].item.opt[2].val,
			md[n].item.opt[3].id, md[n].item.opt[3].val, md[n].item.opt[4].id, md[n].item.opt[4].val, md[n].item.limit,
			md[n].times, md[n].body_size);

		for(j = 0; j < md[n].body_size; j++) {
			fprintf(fp, "%02X", (unsigned char)(md[n].body[j]));
		}
		fprintf(fp, NEWLINE);
		n++;
	}
	lock_fclose(fp, filename, &lock);

	return true;
}

/*==========================================
 * メールデータの読み込み
 *------------------------------------------
 */
bool maildb_txt_read_mail(int char_id, const struct mail *m, struct mail_data md[MAIL_STORE_MAX])
{
	char filename[1056];
	FILE *fp;
	bool ret = true;

	nullpo_retr(false, md);

	sprintf(filename, "%s%d.txt", mail_dir, char_id);
	if((fp = fopen(filename, "r")) == NULL) {
		printf("maildb_txt_read_mail: open [%s] failed !\n", filename);
		ret = false;
	} else {
		int s, i = 0, lines = 0;
		int tmp_int[27];
		char tmp_str[4][1024];
		char line[65536];

		while(fgets(line,sizeof(line),fp) && i < MAIL_STORE_MAX) {
			unsigned int n;
			char *p;
			lines++;

			// Auriga-1369以降の形式
			s = sscanf(line, "%u,%d\t%1023[^\t]\t%1023[^\t]\t%1023[^\t]\t%d\t%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u\t%u\t%u\t%1023[^\r\n]",
				&tmp_int[0],&tmp_int[1],tmp_str[0],tmp_str[1],tmp_str[2],&tmp_int[2],
				&tmp_int[3],&tmp_int[4],&tmp_int[5],&tmp_int[6],&tmp_int[7],&tmp_int[8],&tmp_int[9],&tmp_int[10],&tmp_int[11],&tmp_int[12],&tmp_int[13],
				&tmp_int[14],&tmp_int[15],&tmp_int[16],&tmp_int[17],&tmp_int[18],&tmp_int[19],&tmp_int[20],&tmp_int[21],&tmp_int[22],&tmp_int[23],
				&tmp_int[24],&tmp_int[25],&tmp_int[26],tmp_str[3]);
			if(s != 31) {
				// Auriga-0300以降の形式
				tmp_int[14] = 0;	// opt[0].id
				tmp_int[15] = 0;	// opt[0].val
				tmp_int[16] = 0;	// opt[1].id
				tmp_int[17] = 0;	// opt[1].val
				tmp_int[18] = 0;	// opt[2].id
				tmp_int[19] = 0;	// opt[2].val
				tmp_int[20] = 0;	// opt[3].id
				tmp_int[21] = 0;	// opt[3].val
				tmp_int[22] = 0;	// opt[4].id
				tmp_int[23] = 0;	// opt[4].val
				s = sscanf(line, "%u,%d\t%1023[^\t]\t%1023[^\t]\t%1023[^\t]\t%d\t%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u\t%u\t%u\t%1023[^\r\n]",
					&tmp_int[0],&tmp_int[1],tmp_str[0],tmp_str[1],tmp_str[2],&tmp_int[2],
					&tmp_int[3],&tmp_int[4],&tmp_int[5],&tmp_int[6],&tmp_int[7],&tmp_int[8],&tmp_int[9],&tmp_int[10],&tmp_int[11],&tmp_int[12],&tmp_int[13],
					&tmp_int[24],&tmp_int[25],&tmp_int[26],tmp_str[3]);
				if(s != 21) {
					tmp_int[24] = 0;	// limit
					s = sscanf(line, "%u,%d\t%1023[^\t]\t%1023[^\t]\t%1023[^\t]\t%d\t%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\t%u\t%u\t%1023[^\r\n]",
						&tmp_int[0],&tmp_int[1],tmp_str[0],tmp_str[1],tmp_str[2],&tmp_int[2],
						&tmp_int[3],&tmp_int[4],&tmp_int[5],&tmp_int[6],&tmp_int[7],&tmp_int[8],&tmp_int[9],&tmp_int[10],&tmp_int[11],&tmp_int[12],&tmp_int[13],
						&tmp_int[25],&tmp_int[26],tmp_str[3]);
					if(s != 20) {
						printf("mail_data broken %d line %d\n", char_id, lines);
						continue;
					}
				}
			}
			md[i].mail_num = (unsigned int)tmp_int[0];
			md[i].read     = tmp_int[1];
			memcpy(md[i].char_name, tmp_str[0], 24);
			memcpy(md[i].receive_name, tmp_str[1], 24);
			memcpy(md[i].title, tmp_str[2], 40);
			md[i].zeny            = tmp_int[2];
			md[i].item.id         = (unsigned int)tmp_int[3];
			md[i].item.nameid     = tmp_int[4];
			md[i].item.amount     = tmp_int[5];
			md[i].item.equip      = (unsigned int)tmp_int[6];
			md[i].item.identify   = tmp_int[7];
			md[i].item.refine     = tmp_int[8];
			md[i].item.attribute  = tmp_int[9];
			md[i].item.card[0]    = tmp_int[10];
			md[i].item.card[1]    = tmp_int[11];
			md[i].item.card[2]    = tmp_int[12];
			md[i].item.card[3]    = tmp_int[13];
			md[i].item.opt[0].id  = tmp_int[14];
			md[i].item.opt[0].val = tmp_int[15];
			md[i].item.opt[1].id  = tmp_int[16];
			md[i].item.opt[1].val = tmp_int[17];
			md[i].item.opt[2].id  = tmp_int[18];
			md[i].item.opt[2].val = tmp_int[19];
			md[i].item.opt[3].id  = tmp_int[20];
			md[i].item.opt[3].val = tmp_int[21];
			md[i].item.opt[4].id  = tmp_int[22];
			md[i].item.opt[4].val = tmp_int[23];
			md[i].item.limit      = (unsigned int)tmp_int[24];
			md[i].times           = (unsigned int)tmp_int[25];
			md[i].body_size       = (unsigned int)tmp_int[26];

			// force \0 terminal
			md[i].char_name[23]    = '\0';
			md[i].receive_name[23] = '\0';
			md[i].title[39]        = '\0';

			if(md[i].body_size > sizeof(md[i].body)) {
				printf("mail_read_mail: %d invalid body size %d line %d\n", char_id, md[i].body_size, lines);
				md[i].body_size = sizeof(md[i].body);
			}
			for(n = 0, p = tmp_str[3]; n < md[i].body_size && p[0] && p[1]; n++, p += 2) {
				int c = 0;
				sscanf(p, "%2x", &c);
				md[i].body[n] = c;
			}
			md[i].body_size = n;
			i++;
		}
		fclose(fp);

		if(i != m->store) {	// 数に相違あり？
			struct mail m2;
			printf("mail_read_mail: %d stored number mismatch!! (%d != %d)\n", char_id, i, m->store);
			memcpy(&m2,m,sizeof(struct mail));
			if(i > 0 && m2.rates < md[i-1].mail_num) {
				m2.rates = md[i-1].mail_num;
			}
			m2.store = i;
			maildb_txt_save(&m2);
		}
	}

	return ret;
}

/*==========================================
 * メール削除
 *------------------------------------------
 */
bool maildb_txt_deletemail(int char_id, unsigned int mail_num, const struct mail *m)
{
	struct mail m2;
	struct mail_data md[MAIL_STORE_MAX];
	int i;

	nullpo_retr(false, m);

	memset(md, 0, sizeof(md));
	maildb_txt_read_mail(char_id, m, md);

	for(i = 0; i < m->store; i++) {
		if(md[i].mail_num == mail_num)
			break;
	}
	if(i >= m->store)
		return false;

	if(i + 1 < m->store) {
		memmove(&md[i], &md[i + 1], sizeof(struct mail_data) * (m->store - i - 1));
	}
	maildb_txt_save_mail(char_id, -1, m->store - 1, md);

	memcpy(&m2, m, sizeof(struct mail));
	m2.store--;
	maildb_txt_save(&m2);

	return true;
}

/*==========================================
 * メールデータを文字列へ変換
 *------------------------------------------
 */
static int mail_tostr(char *str, struct mail *m)
{
	nullpo_retr(1, m);

	sprintf(str, "%d,%d,%u,%d",
		m->char_id, m->account_id, m->rates,m->store);

	return 0;
}

/*==========================================
 * メールデータを文字列から変換
 *------------------------------------------
 */
static int mail_fromstr(char *str, struct mail *m)
{
	int s;
	int tmp_int[4];

	s = sscanf(str, "%d,%d,%u,%d", &tmp_int[0], &tmp_int[1], &tmp_int[2], &tmp_int[3]);

	if(s != 4) {
		memset(m, 0, sizeof(struct mail));
		return 1;
	}

	m->char_id    = tmp_int[0];
	m->account_id = tmp_int[1];
	m->rates      = (unsigned int)tmp_int[2];
	m->store      = tmp_int[3];

	return 0;
}

/*==========================================
 * メールデータファイルの読み込み
 *------------------------------------------
 */
static bool maildb_txt_read(void)
{
	FILE *fp;
	bool ret = true;

	mail_db = numdb_init();

	if((fp = fopen(mail_txt, "r")) == NULL) {
		printf("maildb_txt_read: open [%s] failed !\n", mail_txt);
		ret = false;
	} else {
		char line[8192];
		int c = 0;

		while(fgets(line, sizeof(line), fp)) {
			struct mail *m = (struct mail *)aCalloc(1, sizeof(struct mail));
			if(mail_fromstr(line, m) == 0 && m->char_id > 0) {
				numdb_insert(mail_db, m->char_id, m);
				if(m->store < 0 || m->store >= MAIL_STORE_MAX) {	// 値が異常なので補正する
					struct mail_data md[MAIL_STORE_MAX];
					memset(md, 0, sizeof(md));
					maildb_txt_read_mail(m->char_id, m, md);
				}
			} else {
				printf("maildb_txt_read: broken data [%s] line %d\n", mail_txt, c);
				aFree(m);
			}
			c++;
		}
		fclose(fp);
		printf("%s init %d\n", mail_txt, c);
	}

	return ret;
}

/*==========================================
 * 同期
 *------------------------------------------
 */
static int maildb_txt_sync_sub(void *key, void *data, va_list ap)
{
	char line[8192];
	FILE *fp;

	mail_tostr(line, (struct mail *)data);
	fp = va_arg(ap, FILE *);
	fprintf(fp, "%s" NEWLINE, line);

	return 0;
}

int maildb_txt_sync(void)
{
	FILE *fp;
	int lock;

	if( (fp = lock_fopen(mail_txt, &lock) ) == NULL ) {
		printf("maildb_txt_sync: can't write [%s] !!! data is lost !!!\n", mail_txt);
		return 1;
	}
	numdb_foreach(mail_db, maildb_txt_sync_sub, fp);
	lock_fclose(fp, mail_txt, &lock);

	return 0;
}

/*==========================================
 * キャラ削除によるメール削除
 *------------------------------------------
 */
bool maildb_txt_delete(int char_id)
{
	char filename[1056];
	struct mail *m = (struct mail *)numdb_search(mail_db, char_id);

	if(m)
	{
		struct mail_data md[MAIL_STORE_MAX];
		int i;

		memset(md, 0, sizeof(md));
		maildb_txt_read_mail(char_id, m, md);

		for(i = 0; i < m->store; i++) {
			// ペット削除
			if(md[i].item.card[0] == (short)0xff00)
				petdb_delete(*((int *)(&md[i].item.card[1])));
		}

		if(m->char_id == char_id) {
			numdb_erase(mail_db, char_id);
			aFree(m);
		}
	}
	sprintf(filename, "%s%d.txt", mail_dir, char_id);
	remove(filename);

	return false;
}

/*==========================================
 * キャラIDからメールデータをロード
 *------------------------------------------
 */
const struct mail* maildb_txt_load(int char_id)
{
	return (const struct mail *)numdb_search(mail_db, char_id);
}

/*==========================================
 * セーブ
 *------------------------------------------
 */
bool maildb_txt_save(struct mail *m2)
{
	struct mail *m1;

	nullpo_retr(false, m2);

	m1 = (struct mail *)numdb_search(mail_db, m2->char_id);
	if(m1 == NULL) {
		m1 = (struct mail *)aCalloc(1, sizeof(struct mail));
		numdb_insert(mail_db, m2->char_id, m1);
	}
	memcpy(m1, m2, sizeof(struct mail));

	return true;
}

/*==========================================
 * メール作成
 *------------------------------------------
 */
bool maildb_txt_new(int account_id, int char_id)
{
	struct mail *m = (struct mail *)aMalloc(sizeof(struct mail));

	m->account_id = account_id;
	m->char_id = char_id;
	m->rates = 1;
	m->store = 1;
	numdb_insert(mail_db, char_id, m);

	return true;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
static int maildb_txt_final_sub(void *key, void *data, va_list ap)
{
	struct mail *md = (struct mail *)data;

	aFree(md);

	return 0;
}

void maildb_txt_final(void)
{
	if(mail_db)
		numdb_final(mail_db, maildb_txt_final_sub);
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
bool maildb_txt_init(void)
{
	return maildb_txt_read();
}
