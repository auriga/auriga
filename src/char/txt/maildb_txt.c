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
		auriga_strlcpy(mail_txt, w2, sizeof(mail_txt));
	}
	else if(strcmpi(w1,"mail_dir")==0) {
		auriga_strlcpy(mail_dir, w2, sizeof(mail_dir));
	}
	else {
		return 0;
	}

	return 1;
}

/* 添付アイテムのCSV形式（22項目） */
#define MAIL_TXT_ITEM_FMT "%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u"

static void mail_txt_write_item(FILE *fp, const struct item *it)
{
	fprintf(fp, MAIL_TXT_ITEM_FMT,
		it->id, it->nameid, it->amount, it->equip,
		it->identify, it->refine, it->attribute,
		it->card[0], it->card[1], it->card[2], it->card[3],
		it->opt[0].id, it->opt[0].val, it->opt[1].id, it->opt[1].val,
		it->opt[2].id, it->opt[2].val, it->opt[3].id, it->opt[3].val,
		it->opt[4].id, it->opt[4].val, it->limit);
}

static void mail_txt_write_md(FILE *fp, const struct mail_data *md)
{
	int i, n = 0;
	unsigned int j;

	for(i = 0; i < MAIL_MAX_ITEM; i++) {
		if(md->item[i].nameid > 0 && md->item[i].amount > 0)
			n = i + 1;
	}

	fprintf(fp, "%u,%d,%d\t%s\t%s\t%s\t%d\t%d\t",
		md->mail_num, md->read, md->char_id, md->char_name, md->receive_name, md->title, md->zeny, n);
	for(i = 0; i < n; i++) {
		mail_txt_write_item(fp, &md->item[i]);
		fputc('\t', fp);
	}
	fprintf(fp, "%u\t%u\t", md->times, md->body_size);
	for(j = 0; j < md->body_size; j++)
		fprintf(fp, "%02X", (unsigned char)(md->body[j]));
	fprintf(fp, NEWLINE);
}

static int mail_txt_load_item_vals(struct item *it, const int *v)
{
	it->id = (unsigned int)v[0];
	it->nameid = v[1];
	it->amount = v[2];
	it->equip = (unsigned int)v[3];
	it->identify = v[4];
	it->refine = v[5];
	it->attribute = v[6];
	it->card[0] = v[7]; it->card[1] = v[8]; it->card[2] = v[9]; it->card[3] = v[10];
	it->opt[0].id = v[11]; it->opt[0].val = v[12];
	it->opt[1].id = v[13]; it->opt[1].val = v[14];
	it->opt[2].id = v[15]; it->opt[2].val = v[16];
	it->opt[3].id = v[17]; it->opt[3].val = v[18];
	it->opt[4].id = v[19]; it->opt[4].val = v[20];
	it->limit = (unsigned int)v[21];
	return 0;
}

/*==========================================
 * メール本文の保存
 *------------------------------------------
 */
bool maildb_txt_store_mail(int char_id, struct mail_data *md)
{
	char filename[1056];
	FILE *fp;

	nullpo_retr(false, md);

	snprintf(filename, sizeof(filename), "%s%d.txt", mail_dir, char_id);
	fp = fopen(filename, "a");
	if(fp == NULL)
	{
		printf("maildb_txt_store_mail: can't write [%s] !!! data is lost !!!\n", filename);
		return false;
	}
	mail_txt_write_md(fp, md);
	fclose(fp);
	return true;
}

/*==========================================
 * メールのセーブ
 *------------------------------------------
 */
bool maildb_txt_save_mail(int char_id, int i, int store, struct mail_data *md)
{
	char filename[1056];
	FILE *fp;
	int n = 0, lock;

	nullpo_retr(false, md);
	(void)i;

	snprintf(filename, sizeof(filename), "%s%d.txt", mail_dir, char_id);
	fp = lock_fopen(filename, &lock);
	if(fp == NULL)
	{
		printf("maildb_txt_save_mail: can't write [%s] !!! data is lost !!!\n", filename);
		return false;
	}
	while(n < store) {
		mail_txt_write_md(fp, &md[n]);
		n++;
	}
	if(lock_fclose(fp, filename, &lock) != 0)
		return false;
	return true;
}

/*==========================================
 * メールデータの読み込み
 *------------------------------------------
 */
bool maildb_txt_read_mail(int char_id, const struct mail *m, struct mail_data *md, int capacity)
{
	char filename[1056];
	FILE *fp;
	bool ret = true;

	nullpo_retr(false, md);
	if(capacity <= 0 || m == NULL || m->store > capacity)
		return false;

	snprintf(filename, sizeof(filename), "%s%d.txt", mail_dir, char_id);
	if((fp = fopen(filename, "r")) == NULL) {
		printf("maildb_txt_read_mail: open [%s] failed !\n", filename);
		ret = false;
	} else {
		int s, i = 0, lines = 0;
		int tmp_int[27];
		char tmp_str[4][1024];
		char line[65536];

		while(fgets(line,sizeof(line),fp) && i < capacity) {
			unsigned int n;
			char *p;
			lines++;

			// 本文が空の場合も読み込めるようにする
			tmp_str[3][0] = '\0';

			/* RoDEXの複数添付形式 */
			{
				unsigned int mail_num = 0;
				int readf = 0, send_id = 0, zeny = 0, nitem = 0;
				char s0[1024], s1[1024], s2[1024];
				char *p = line;
				int consumed = 0, hdr = 0;
				int matched = 0;
				/* readの次がカンマなら送信者IDあり、タブなら旧形式 */
				if(sscanf(p, "%u,%d%n", &mail_num, &readf, &hdr) >= 2 && hdr > 0) {
					if(p[hdr] == ',') {
						if(sscanf(p + hdr, ",%d\t%1023[^\t]\t%1023[^\t]\t%1023[^\t]\t%d\t%d\t%n",
							&send_id, s0, s1, s2, &zeny, &nitem, &consumed) >= 6 && consumed > 0 &&
							nitem >= 0 && nitem <= MAIL_MAX_ITEM) {
							consumed += hdr;
							matched = 1;
						}
					} else if(p[hdr] == '\t') {
						send_id = 0;
						if(sscanf(p + hdr, "\t%1023[^\t]\t%1023[^\t]\t%1023[^\t]\t%d\t%d\t%n",
							s0, s1, s2, &zeny, &nitem, &consumed) >= 5 && consumed > 0 &&
							nitem >= 0 && nitem <= MAIL_MAX_ITEM) {
							consumed += hdr;
							matched = 1;
						}
					}
				}
				if(matched) {
					int k, ok = 1;
					p += consumed;
					memset(&md[i], 0, sizeof(md[i]));
					md[i].mail_num = mail_num;
					md[i].read = readf;
					md[i].char_id = send_id;
					auriga_strlcpy(md[i].char_name, s0, sizeof(md[i].char_name));
					auriga_strlcpy(md[i].receive_name, s1, sizeof(md[i].receive_name));
					auriga_strlcpy(md[i].title, s2, sizeof(md[i].title));
					md[i].char_name[23] = md[i].receive_name[23] = '\0';
					md[i].title[39] = '\0';
					md[i].zeny = zeny;
					for(k = 0; k < nitem; k++) {
						int iv[22];
						int c2 = 0;
						if(sscanf(p, "%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u\t%n",
							&iv[0],&iv[1],&iv[2],&iv[3],&iv[4],&iv[5],&iv[6],&iv[7],&iv[8],&iv[9],&iv[10],
							&iv[11],&iv[12],&iv[13],&iv[14],&iv[15],&iv[16],&iv[17],&iv[18],&iv[19],&iv[20],&iv[21], &c2) < 22) {
							ok = 0; break;
						}
						mail_txt_load_item_vals(&md[i].item[k], iv);
						p += c2;
					}
					if(ok) {
						unsigned int times = 0, body_size = 0;
						char bodyhex[1024] = "";
						if(sscanf(p, "%u\t%u\t%1023[^\r\n]", &times, &body_size, bodyhex) >= 2) {
							unsigned int n; char *bp;
							md[i].times = times;
							md[i].body_size = body_size;
							if(md[i].body_size > sizeof(md[i].body))
								md[i].body_size = sizeof(md[i].body);
							for(n = 0, bp = bodyhex; n < md[i].body_size && bp[0] && bp[1]; n++, bp += 2) {
								int c = 0; sscanf(bp, "%2x", &c); md[i].body[n] = c;
							}
							md[i].body_size = n;
							i++;
							continue;
						}
					}
				}
			}

			// Auriga-1369以降の形式
			s = sscanf(line, "%u,%d\t%1023[^\t]\t%1023[^\t]\t%1023[^\t]\t%d\t%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u\t%u\t%u\t%1023[^\r\n]",
				&tmp_int[0],&tmp_int[1],tmp_str[0],tmp_str[1],tmp_str[2],&tmp_int[2],
				&tmp_int[3],&tmp_int[4],&tmp_int[5],&tmp_int[6],&tmp_int[7],&tmp_int[8],&tmp_int[9],&tmp_int[10],&tmp_int[11],&tmp_int[12],&tmp_int[13],
				&tmp_int[14],&tmp_int[15],&tmp_int[16],&tmp_int[17],&tmp_int[18],&tmp_int[19],&tmp_int[20],&tmp_int[21],&tmp_int[22],&tmp_int[23],
				&tmp_int[24],&tmp_int[25],&tmp_int[26],tmp_str[3]);
			if(s != 31 && !(s == 30 && tmp_int[26] == 0)) {
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
				if(s != 21 && !(s == 20 && tmp_int[26] == 0)) {
					tmp_int[24] = 0;	// limit
					s = sscanf(line, "%u,%d\t%1023[^\t]\t%1023[^\t]\t%1023[^\t]\t%d\t%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\t%u\t%u\t%1023[^\r\n]",
						&tmp_int[0],&tmp_int[1],tmp_str[0],tmp_str[1],tmp_str[2],&tmp_int[2],
						&tmp_int[3],&tmp_int[4],&tmp_int[5],&tmp_int[6],&tmp_int[7],&tmp_int[8],&tmp_int[9],&tmp_int[10],&tmp_int[11],&tmp_int[12],&tmp_int[13],
						&tmp_int[25],&tmp_int[26],tmp_str[3]);
					if(s != 20 && !(s == 19 && tmp_int[26] == 0)) {
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
			md[i].item[0].id         = (unsigned int)tmp_int[3];
			md[i].item[0].nameid     = tmp_int[4];
			md[i].item[0].amount     = tmp_int[5];
			md[i].item[0].equip      = (unsigned int)tmp_int[6];
			md[i].item[0].identify   = tmp_int[7];
			md[i].item[0].refine     = tmp_int[8];
			md[i].item[0].attribute  = tmp_int[9];
			md[i].item[0].card[0]    = tmp_int[10];
			md[i].item[0].card[1]    = tmp_int[11];
			md[i].item[0].card[2]    = tmp_int[12];
			md[i].item[0].card[3]    = tmp_int[13];
			md[i].item[0].opt[0].id  = tmp_int[14];
			md[i].item[0].opt[0].val = tmp_int[15];
			md[i].item[0].opt[1].id  = tmp_int[16];
			md[i].item[0].opt[1].val = tmp_int[17];
			md[i].item[0].opt[2].id  = tmp_int[18];
			md[i].item[0].opt[2].val = tmp_int[19];
			md[i].item[0].opt[3].id  = tmp_int[20];
			md[i].item[0].opt[3].val = tmp_int[21];
			md[i].item[0].opt[4].id  = tmp_int[22];
			md[i].item[0].opt[4].val = tmp_int[23];
			md[i].item[0].limit      = (unsigned int)tmp_int[24];
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

		if(i != m->store && m->store <= capacity) {	// 数に相違あり？
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
	struct mail_data *md;
	int i, capacity;
	bool result;

	nullpo_retr(false, m);
	if(m->store <= 0)
		return false;
	capacity = m->store;
	md = (struct mail_data *)calloc((size_t)capacity, sizeof(*md));
	if(md == NULL)
		return false;
	if(!maildb_txt_read_mail(char_id, m, md, capacity)) {
		free(md);
		return false;
	}
	for(i = 0; i < m->store; i++) {
		if(md[i].mail_num == mail_num)
			break;
	}
	if(i >= m->store) {
		free(md);
		return false;
	}
	if(i + 1 < m->store)
		memmove(&md[i], &md[i + 1], sizeof(*md) * (m->store - i - 1));
	result = maildb_txt_save_mail(char_id, -1, m->store - 1, md);
	free(md);
	if(!result)
		return false;
	memcpy(&m2, m, sizeof(m2));
	m2.store--;
	return maildb_txt_save(&m2);
}

/*==========================================
 * メールデータを文字列へ変換
 *------------------------------------------
 */
static int mail_tostr(char *str, struct mail *m)
{
	nullpo_retr(1, m);

	snprintf(str, 64, "%d,%d,%u,%d",
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
			if(mail_fromstr(line, m) == 0 && m->char_id > 0 && m->store >= 0) {
				numdb_insert(mail_db, m->char_id, m);
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
		struct mail_data *md = NULL;
		int i, j;

		if(m->store < 0)
			return false;
		if(m->store > 0) {
			int capacity = m->store;
			md = (struct mail_data *)calloc((size_t)capacity, sizeof(*md));
			if(md == NULL)
				return false;
			if(!maildb_txt_read_mail(char_id, m, md, capacity)) {
				free(md);
				return false;
			}
		}

		for(i = 0; i < m->store; i++) {
			for(j = 0; j < MAIL_MAX_ITEM; j++) {
				if(md[i].item[j].card[0] == (int)0xff00)
					petdb_delete(*((int *)(&md[i].item[j].card[1])));
			}
		}

		free(md);

		if(m->char_id == char_id) {
			numdb_erase(mail_db, char_id);
			aFree(m);
		}
	}
	snprintf(filename, sizeof(filename), "%s%d.txt", mail_dir, char_id);
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
