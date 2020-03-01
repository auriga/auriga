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
#include "db.h"
#include "lock.h"
#include "malloc.h"
#include "journal.h"
#include "utils.h"
#include "nullpo.h"

#include "../login.h"
#include "account_txt.h"

#ifdef TXT_JOURNAL
static int login_journal_enable = 1;
static struct journal login_journal;
static char login_journal_file[1024]="./save/account.journal";
static int login_journal_cache = 1000;
#endif

static char account_filename[1024] = "save/account.txt";
static int  auth_num=0,auth_max=0;
static int  account_id_count = START_ACCOUNT_NUM;
static struct mmo_account *auth_dat = NULL;

/*==========================================
 * 設定ファイルのデフォルト設定
 *------------------------------------------
 */
void account_txt_set_default_configvalue(void)
{
	// nothing to do
}

/*==========================================
 * 設定ファイル読込
 *------------------------------------------
 */
int account_txt_config_read_sub(const char* w1,const char* w2)
{
	if( strcmpi(w1, "account_filename") == 0 )
		strncpy(account_filename, w2, sizeof(account_filename) - 1);
#ifdef TXT_JOURNAL
	else if( strcmpi(w1, "account_journal_enable") == 0 )
		login_journal_enable = atoi(w2);
	else if( strcmpi(w1, "account_journal_file") == 0 )
		strncpy( login_journal_file, w2, sizeof(login_journal_file) - 1 );
	else if( strcmpi(w1, "account_journal_cache_interval") == 0 )
		login_journal_cache = atoi(w2);
#endif
	else
		return 0;

	return 1;
}

/*==========================================
 * 設定ファイルの警告
 *------------------------------------------
 */
void display_conf_warnings_txt(void)
{
	// nothing to do
}

/*==========================================
 * アカウントIDからauth_datのIndexを返す
 *------------------------------------------
 */
static int login_id2idx(int account_id)
{
	int min = -1;
	int max = auth_num;

	// binary search
	while(max - min > 1) {
		int mid = (min + max) / 2;
		if(auth_dat[mid].account_id == account_id)
			return (auth_dat[mid].userid[0])? mid: -1;

		if(auth_dat[mid].account_id > account_id)
			max = mid;
		else
			min = mid;
	}
	return -1;
}

#ifdef TXT_JOURNAL
// ==========================================
// アカウントデータのジャーナルのロールフォワード用コールバック関数
// ------------------------------------------
static int login_journal_rollforward( int key, void* buf, int flag )
{
	int idx = login_id2idx( key );

	// 念のためチェック
	if( flag == JOURNAL_FLAG_WRITE && key != ((struct mmo_account*)buf)->account_id )
	{
		printf("login_journal: key != account_id !\n");
		return 0;
	}

	// データの置き換え
	if( idx >= 0 )
	{
		if( flag == JOURNAL_FLAG_DELETE ) {
			memset( &auth_dat[idx], 0, sizeof(struct mmo_account) );
			auth_dat[idx].account_id = -1;
		} else {
			memcpy( &auth_dat[idx], buf, sizeof(struct mmo_account) );
		}
		return 1;
	}

	// 追加
	if( flag != JOURNAL_FLAG_DELETE )
	{
		if(auth_num>=auth_max)
		{
			// メモリが足りないなら拡張
			auth_max += 256;
			auth_dat = (struct mmo_account *)aRealloc(auth_dat, sizeof(auth_dat[0]) * auth_max);
			memset(auth_dat + (auth_max - 256), '\0', 256 * sizeof(auth_dat[0]));
		}

		memcpy( &auth_dat[auth_num], buf, sizeof(struct mmo_account) );
		if(auth_dat[auth_num].account_id >= account_id_count)
			account_id_count = auth_dat[auth_num].account_id + 1;
		auth_num++;
		return 1;
	}

	return 0;
}

void account_txt_sync(void);
#endif

/*==========================================
 * アカウントデータファイルの読み込み
 *------------------------------------------
 */
static bool account_txt_read(void)
{
	FILE *fp;
	bool ret = true;

	if((fp = fopen(account_filename, "r")) == NULL) {
		printf("account_txt_read: open [%s] failed !\n", account_filename);
		ret = false;
	} else {
		int i, n, account_id, logincount, state;
		char userid[256], pass[256], lastlogin[256], sex;
		char line[65536];

		auth_max = 256;
		auth_dat = (struct mmo_account *)aCalloc(auth_max, sizeof(auth_dat[0]));

		while(fgets(line, sizeof(line) - 1, fp) != NULL) {
			char *p = line;
			n = -1;

			i = sscanf(
				line, "%d\t%255[^\t]\t%255[^\t]\t%255[^\t]\t%c\t%d\t%d\t%n",
				&account_id, userid,pass, lastlogin, &sex, &logincount, &state, &n
			);

			if(i < 5) {
				i = -1;
				if(sscanf(line, "%d\t%%newid%%%n", &account_id, &i) == 1 && i > 0 && (line[i] == '\n' || line[i] == '\r')) {
					if(account_id > END_ACCOUNT_NUM + 1) {	// newidは+1まで許可
						printf("reading %s error : invalid ID %d\n", account_filename, account_id);
						continue;
					}
					if(account_id > account_id_count)
						account_id_count = account_id;
				}
				continue;
			}

			if(account_id > END_ACCOUNT_NUM) {
				printf("reading %s error : invalid ID %d\n", account_filename, account_id);
				continue;
			}
			if(auth_num >= auth_max) {
				auth_max += 256;
				auth_dat = (struct mmo_account *)aRealloc(auth_dat, sizeof(auth_dat[0]) * auth_max);
				memset(auth_dat + (auth_max - 256), '\0', 256 * sizeof(auth_dat[0]));
			}
			auth_dat[auth_num].account_id = account_id;
			strncpy(auth_dat[auth_num].userid, userid, 24);
			strncpy(auth_dat[auth_num].pass, pass, 24);
			strncpy(auth_dat[auth_num].lastlogin, lastlogin, 24);
			auth_dat[auth_num].sex = sex;
			strncpy(auth_dat[auth_num].birth, "000000", 7);

			// force \0 terminal
			auth_dat[auth_num].userid[23]    = '\0';
			auth_dat[auth_num].pass[23]      = '\0';
			auth_dat[auth_num].lastlogin[23] = '\0';

			// データが足りないときの補完
			auth_dat[auth_num].logincount = (i >= 6)? logincount: 1;
			auth_dat[auth_num].state      = (i >= 7)? state: 0;

			// メールアドレスがあれば読み込む
			if(n > 0)
			{
				int n2 = 0;
				char mail[256] = "";
				if(sscanf(line + n, "%255[^\t]\t%n", mail, &n2) == 1 && strchr(mail, '@'))
				{
					if(strcmp(mail, "@") == 0) {
						auth_dat[auth_num].mail[0] = '\0';
					} else {
						strncpy(auth_dat[auth_num].mail, mail, 40);
						auth_dat[auth_num].mail[39] = '\0';	// force \0 terminal
					}
					n = (n2 > 0)? n + n2 : 0;
				}
			}

			// 誕生日があれば読み込む
			if(n > 0)
			{
				int n2 = 0;
				char birth[7] = "";
				if(sscanf(line + n, "%6[^\t]\t%n", birth, &n2) == 1 && !strchr(birth, '#'))
				{
					strncpy(auth_dat[auth_num].birth, birth, 6);
					auth_dat[auth_num].birth[6] = '\0';	// force \0 terminal
					n = (n2 > 0)? n + n2 : 0;
				}
			}

			// 全ワールド共有アカウント変数 ( ## 変数 ) 読み込み
			if(n > 0) {
				int j, v;
				char str[256];
				for(j = 0; j < ACCOUNT_REG2_NUM; j++) {
					p += n;
					if(sscanf(p, "%255[^\t,],%d%n", str, &v, &n) != 2)
						break;
					strncpy(auth_dat[auth_num].account_reg2[j].str, str, 32);
					auth_dat[auth_num].account_reg2[j].str[31] = '\0';	// force \0 terminal
					auth_dat[auth_num].account_reg2[j].value   = v;
					if(p[n] != ' ')
						break;
					n++;
				}
				auth_dat[auth_num].account_reg2_num = j;
			} else {
				auth_dat[auth_num].account_reg2_num = 0;
			}

			if(account_id >= account_id_count)
				account_id_count = account_id + 1;

			if(auth_num > 0 && account_id < auth_dat[auth_num-1].account_id) {
				struct mmo_account tmp;
				int k = auth_num;

				// 何故かアカウントIDの昇順に並んでない場合は挿入ソートする
				while(--k > 0 && account_id < auth_dat[k-1].account_id);

				memcpy(&tmp, &auth_dat[auth_num], sizeof(auth_dat[0]));
				memmove(&auth_dat[k+1], &auth_dat[k], (auth_num - k) * sizeof(auth_dat[0]));
				memcpy(&auth_dat[k], &tmp, sizeof(auth_dat[0]));
			}
			auth_num++;
		}
		fclose(fp);
	}

#ifdef TXT_JOURNAL
	if( login_journal_enable )
	{
		// ジャーナルデータのロールフォワード
		if( journal_load( &login_journal, sizeof(struct mmo_account), login_journal_file ) )
		{
			int c = journal_rollforward( &login_journal, login_journal_rollforward );

			printf("login_journal: roll-forward (%d)\n", c );

			// ロールフォワードしたので、txt データを保存する ( journal も新規作成される)
			account_txt_sync();
		}
		else
		{
			// ジャーナルを新規作成する
			journal_final( &login_journal );
			journal_create( &login_journal, sizeof(struct mmo_account), login_journal_cache, login_journal_file );
		}
	}
#endif

	return ret;
}

/*==========================================
 * 同期
 *------------------------------------------
 */
void account_txt_sync(void)
{
	FILE *fp;
	int i, j, lock;

	if( !auth_dat )
		return;

	fp = lock_fopen(account_filename, &lock);
	if(fp == NULL) {
		printf("account_txt_sync: can't write [%s] !!! data is lost !!!\n", account_filename);
		return;
	}

	for(i = 0; i < auth_num; i++) {
		if(auth_dat[i].account_id < 0)
			continue;
		if(!auth_dat[i].userid[0]) {
			// 削除されている
			continue;
		}

		fprintf(fp, "%d\t%s\t%s\t%s\t%c\t%d\t%d\t%s\t%s\t", auth_dat[i].account_id,
			auth_dat[i].userid, auth_dat[i].pass, auth_dat[i].lastlogin, auth_dat[i].sex,
			auth_dat[i].logincount, auth_dat[i].state, ((auth_dat[i].mail[0])? auth_dat[i].mail: "@"), auth_dat[i].birth);

		for(j = 0; j < auth_dat[i].account_reg2_num; j++) {
			fprintf(fp, "%s,%d ", auth_dat[i].account_reg2[j].str, auth_dat[i].account_reg2[j].value);
		}
		fprintf(fp, NEWLINE);
	}
	fprintf(fp, "%d\t%%newid%%" NEWLINE, account_id_count);

	lock_fclose(fp, account_filename, &lock);

#ifdef TXT_JOURNAL
	if( login_journal_enable )
	{
		// コミットしたのでジャーナルを新規作成する
		journal_final( &login_journal );
		journal_create( &login_journal, sizeof(struct mmo_account), login_journal_cache, login_journal_file );
	}
#endif

}

/*==========================================
 * アカウントIDからアカウント情報をロード
 *------------------------------------------
 */
const struct mmo_account* account_txt_account_load_num(int account_id)
{
	int idx = login_id2idx(account_id);

	return (idx >= 0) ? &auth_dat[idx] : NULL;
}

/*==========================================
 * アカウント名からアカウント情報をロード
 *------------------------------------------
 */
const struct mmo_account* account_txt_account_load_str(const char *account_id)
{
	int x;

	if(!account_id[0])
		return NULL;

	for(x = 0; x < auth_num; x++) {
		if(auth_dat[x].userid[0] && !strncmp(auth_dat[x].userid, account_id, 24)) {
			return &auth_dat[x];
		}
	}
	return NULL;
}

/*==========================================
 * アカウントIndexからアカウント情報をロード
 *------------------------------------------
 */
const struct mmo_account* account_txt_account_load_idx(int idx)
{
	return (idx >= 0 && idx < auth_num) ? &auth_dat[idx] : NULL;
}

/*==========================================
 * セーブ
 *------------------------------------------
 */
bool account_txt_account_save(struct mmo_account *account)
{
	int idx;

	nullpo_retr(false, account);

	idx = login_id2idx(account->account_id);
	if(idx >= 0) {
		memcpy(&auth_dat[idx], account, sizeof(struct mmo_account));
#ifdef TXT_JOURNAL
		if( login_journal_enable )
			journal_write( &login_journal, account->account_id, account );
#endif
		return false;
	}
	return true;
}

/*==========================================
 * アカウント削除
 *------------------------------------------
 */
bool account_txt_account_delete(int account_id)
{
	int idx = login_id2idx(account_id);

	if(idx >= 0) {
		memset(&auth_dat[idx], 0, sizeof(struct mmo_account));
		auth_dat[idx].account_id = account_id;	// アカウントIDは維持
#ifdef TXT_JOURNAL
		if( login_journal_enable )
			journal_write( &login_journal, account_id, NULL );
#endif
		return false;
	}
	return true;
}

/*==========================================
 * アカウント作成
 *------------------------------------------
 */
bool account_txt_account_new(struct mmo_account *account, const char *tmpstr)
{
	int i = auth_num, j, c;

	nullpo_retr(false, account);

	loginlog_log("auth new %s %s %s", tmpstr, account->userid, account->pass);

	if(!account->userid[0]) {
		// 空文字は弾く
		return false;
	}
	for(j = 0; j < 24 && (c = account->userid[j]); j++) {
		if(c < 0x20 || c == 0x7f)
			return false;
	}

	// force \0 terminal
	account->userid[23] = '\0';
	account->pass[23]   = '\0';
	account->mail[39]   = '\0';
	account->birth[6]   = '\0';

	if(account_txt_account_load_str(account->userid)) {
		// 同じアカウントが既に存在
		return false;
	}
	if(auth_num >= auth_max) {
		auth_max += 256;
		auth_dat = (struct mmo_account *)aRealloc(auth_dat, sizeof(auth_dat[0]) * auth_max);
		memset(auth_dat + (auth_max - 256), '\0', 256 * sizeof(auth_dat[0]));
	}
	while(isGM(account_id_count) > 0) {
		account_id_count++;
	}
	if(account_id_count > END_ACCOUNT_NUM) {
		// 利用可能なID上限を超えた
		printf("account_new : ID is over END_ACCOUNT_NUM %d\n", END_ACCOUNT_NUM);
		return false;
	}
	auth_dat[i].account_id = account_id_count++;
	auth_dat[i].sex        = account->sex;
	auth_dat[i].logincount = 0;
	auth_dat[i].state      = 0;
	strncpy(auth_dat[i].userid, account->userid, 24);
	strncpy(auth_dat[i].pass,   account->pass,   24);
	strncpy(auth_dat[i].mail,   account->mail,   40);
	strncpy(auth_dat[i].birth,  account->birth,   7);
	strcpy(auth_dat[i].lastlogin, "-");
	auth_dat[i].account_reg2_num = 0;
	auth_num++;
#ifdef TXT_JOURNAL
	if( login_journal_enable )
		journal_write( &login_journal, auth_dat[i].account_id, &auth_dat[i] );
#endif
	return true;
}

/*==========================================
 * 終了
 *------------------------------------------
 */
void account_txt_final(void)
{
	if(auth_dat)
		aFree(auth_dat);

#ifdef TXT_JOURNAL
	if( login_journal_enable )
	{
		journal_final( &login_journal );
	}
#endif
}

/*==========================================
 * 初期化
 *------------------------------------------
 */
bool account_txt_init(void)
{
	return account_txt_read();
}
