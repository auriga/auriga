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

#if !defined(_WIN32) && !defined(_XOPEN_SOURCE)
#define _XOPEN_SOURCE 700
#endif
#include <errno.h>
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#endif
#include "db.h"
#include "lock.h"
#include "malloc.h"
#include "cashshopdb_txt.h"
#ifdef TXT_JOURNAL
#include "journal.h"
#endif

struct cashshop_txt_row {
	char key[32];
	int account_id;
	struct cashshop_account_count sale;
#ifdef TXT_JOURNAL
	int journal_id;
#endif
};

static struct dbt *cashshop_db;
static int cashshop_ready, cashshop_dirty, cashshop_valid;
static char cashshop_txt[1024] = "save/cashshop.txt";

#ifdef TXT_JOURNAL
/* IDは世代内だけで一意。TXT確定・世代更新時に割当をやり直す。 */
struct cashshop_journal_row {
	int id, account_id;
	struct cashshop_account_count sale;
};
static int cashshop_journal_next_id;
static struct dbt *cashshop_journal_ids;
static struct journal cashshop_journal;
static struct journal_config cashshop_journal_cfg = { 1, "./save/cashshop.journal", 1000 };
#define CASHSHOP_JOURNAL_FILE cashshop_journal_cfg.file
#else
static char cashshop_journal_file[1024] = "./save/cashshop.journal";
#define CASHSHOP_JOURNAL_FILE cashshop_journal_file
#endif

/* 相対指定・大小文字・存在する親ディレクトリの別名を正規化する。 */
static int cashshop_path(char *resolved, size_t capacity, const char *path)
{
#ifdef _WIN32
	return _fullpath(resolved, path, capacity) != NULL;
#else
	char parent[4096], base[4096], *slash, *absolute;
	int length;
	absolute = realpath(path, NULL);
	if(absolute) {
		size_t copied = auriga_strlcpy(resolved, absolute, capacity);
		free(absolute);
		return copied < capacity;
	}
	if(auriga_strlcpy(parent, path, sizeof(parent)) >= sizeof(parent))
		return 0;
	slash = strrchr(parent, '/');
	if(slash) {
		if(auriga_strlcpy(base, slash + 1, sizeof(base)) >= sizeof(base))
			return 0;
		if(slash == parent) slash[1] = '\0';
		else *slash = '\0';
	} else {
		auriga_strlcpy(base, parent, sizeof(base));
		auriga_strlcpy(parent, ".", sizeof(parent));
	}
	if(!base[0] || !(absolute = realpath(parent, NULL)))
		return 0;
	length = (int)auriga_strlcpy(resolved, absolute, capacity);
	free(absolute);
	if(length < 0 || (size_t)length >= capacity)
		return 0;
	return snprintf(resolved + length, capacity - length, "/%s", base) < (int)(capacity - length);
#endif
}

/* 8.3短名・ハードリンク等も、存在する実ファイルのIDで照合する。 */
static int cashshop_files_conflict(int *journal_exists)
{
#ifdef _WIN32
	HANDLE txt, journal;
	BY_HANDLE_FILE_INFORMATION tinfo, jinfo;
	DWORD terror, jerror;
	int result = 0;
	txt = CreateFileA(cashshop_txt, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	terror = txt == INVALID_HANDLE_VALUE ? GetLastError() : ERROR_SUCCESS;
	journal = CreateFileA(CASHSHOP_JOURNAL_FILE, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	jerror = journal == INVALID_HANDLE_VALUE ? GetLastError() : ERROR_SUCCESS;
	*journal_exists = journal != INVALID_HANDLE_VALUE;
	if((terror && terror != ERROR_FILE_NOT_FOUND && terror != ERROR_PATH_NOT_FOUND) ||
	   (jerror && jerror != ERROR_FILE_NOT_FOUND && jerror != ERROR_PATH_NOT_FOUND))
		result = -1;
	if(txt != INVALID_HANDLE_VALUE && journal != INVALID_HANDLE_VALUE) {
		if(!GetFileInformationByHandle(txt, &tinfo) || !GetFileInformationByHandle(journal, &jinfo))
			result = -1;
		else if(tinfo.dwVolumeSerialNumber == jinfo.dwVolumeSerialNumber &&
		        tinfo.nFileIndexHigh == jinfo.nFileIndexHigh && tinfo.nFileIndexLow == jinfo.nFileIndexLow)
			result = 1;
	}
	if(txt != INVALID_HANDLE_VALUE) CloseHandle(txt);
	if(journal != INVALID_HANDLE_VALUE) CloseHandle(journal);
	return result;
#else
	struct stat txt, journal;
	int tresult = stat(cashshop_txt, &txt), terror = errno;
	int jresult = stat(CASHSHOP_JOURNAL_FILE, &journal), jerror = errno;
	*journal_exists = jresult == 0;
	if((tresult != 0 && terror != ENOENT) || (jresult != 0 && jerror != ENOENT))
		return -1;
	return tresult == 0 && jresult == 0 && txt.st_dev == journal.st_dev && txt.st_ino == journal.st_ino;
#endif
}

static struct cashshop_txt_row *cashshop_get(int account, int sale)
{
	char key[32];
	snprintf(key, sizeof(key), "%d:%d", account, sale);
	return (struct cashshop_txt_row *)strdb_search(cashshop_db, key);
}

static struct cashshop_txt_row *cashshop_set(int account, int sale, unsigned int purchased)
{
	struct cashshop_txt_row *row = cashshop_get(account, sale);
	if(!row) {
		row = (struct cashshop_txt_row *)aCalloc(1, sizeof(*row));
		row->account_id = account;
		row->sale.sale_id = sale;
		snprintf(row->key, sizeof(row->key), "%d:%d", account, sale);
		strdb_insert(cashshop_db, row->key, row);
	}
	if(purchased > row->sale.purchased)
		row->sale.purchased = purchased;
	return row;
}

int cashshopdb_txt_config_read(const char *key, const char *value)
{
	if(strcmpi(key, "cashshop_txt") == 0) {
		auriga_strlcpy(cashshop_txt, value, sizeof(cashshop_txt));
		return 1;
	}
#ifdef TXT_JOURNAL
	return journal_config_read(&cashshop_journal_cfg, "cashshop_journal", key, value);
#else
	/* 無効ビルドでも残存ジャーナルの場所を確認する。 */
	if(strcmpi(key, "cashshop_journal_file") == 0) {
		auriga_strlcpy(cashshop_journal_file, value, sizeof(cashshop_journal_file));
		return 1;
	}
	return strcmpi(key, "cashshop_journal_enable") == 0 ||
	       strcmpi(key, "cashshop_journal_cache_interval") == 0;
#endif
}

/* 桁あふれを破損と扱い、別の販売枠や小さな購入数に読み替えない。 */
static int cashshop_parse_row(char *line, int *account, int *sale, int *purchased)
{
	int i;
	long value[3];
	char *p = line, *end;
	for(i = 0; i < 3; i++) {
		errno = 0;
		value[i] = strtol(p, &end, 10);
		if(p == end || errno || value[i] < (i == 2 ? 0 : 1) || value[i] > INT_MAX ||
		   (i < 2 && !isspace((unsigned char)*end)))
			return 0;
		p = end;
	}
	while(isspace((unsigned char)*p))
		p++;
	if(*p)
		return 0;
	*account = (int)value[0];
	*sale = (int)value[1];
	*purchased = (int)value[2];
	return 1;
}

#ifdef TXT_JOURNAL
static int cashshop_journal_restore(int key, void *data, int flag)
{
	const struct cashshop_journal_row *record = (const struct cashshop_journal_row *)data;
	struct cashshop_txt_row *row, *existing;
	if(flag != JOURNAL_FLAG_WRITE || key <= 0 || record->id != key ||
	   record->account_id <= 0 || record->sale.sale_id <= 0 || record->sale.purchased > INT_MAX) {
		cashshop_ready = 0;
		return 0;
	}
	existing = (struct cashshop_txt_row *)numdb_search(cashshop_journal_ids, key);
	if(existing && (existing->account_id != record->account_id || existing->sale.sale_id != record->sale.sale_id)) {
		cashshop_ready = 0;
		return 0;
	}
	row = cashshop_get(record->account_id, record->sale.sale_id);
	if(row && row->journal_id && row->journal_id != key) {
		cashshop_ready = 0;
		return 0;
	}
	row = cashshop_set(record->account_id, record->sale.sale_id, record->sale.purchased);
	row->journal_id = key;
	if(!existing) numdb_insert(cashshop_journal_ids, key, row);
	cashshop_dirty = 1;
	return 1;
}

/* 最新候補への集約前に全レコードを検証し、累積値の最大値を回収する。 */
static void cashshop_journal_scan(struct journal_header *header, void *data)
{
	if(!cashshop_journal_restore(header->key, data, header->flag))
		cashshop_ready = cashshop_valid = 0;
}

static int cashshop_journal_reset_id(void *key, void *data, va_list ap)
{
	((struct cashshop_txt_row *)data)->journal_id = 0;
	return 0;
}
#endif

bool cashshopdb_txt_init(void)
{
	FILE *fp;
	char line[128], txt_path[4096], journal_path[4096];
	int account, sale, purchased, missing_txt = 0, journal_exists, journal_enabled = 0;
#ifdef TXT_JOURNAL
	int loaded, had_file;
	journal_enabled = cashshop_journal_cfg.enable;
	cashshop_journal_next_id = 0;
	cashshop_journal_ids = numdb_init();
#endif
	cashshop_db = strdb_init(32);
	cashshop_ready = 1;
	cashshop_dirty = cashshop_valid = 0;
	if(cashshop_files_conflict(&journal_exists) != 0 ||
	   !cashshop_path(txt_path, sizeof(txt_path), cashshop_txt))
		goto unavailable;
	if(!cashshop_path(journal_path, sizeof(journal_path), CASHSHOP_JOURNAL_FILE)) {
		/* 無効時は、存在しない保存先を新規作成できる必要はない。 */
		if(journal_enabled || journal_exists || errno != ENOENT)
			goto unavailable;
	} else {
#ifdef _WIN32
		if(strcmpi(txt_path, journal_path) == 0)
#else
		if(strcmp(txt_path, journal_path) == 0)
#endif
			goto unavailable;
	}
	fp = fopen(cashshop_txt, "r");
	if(!fp) {
		if(errno != ENOENT)
			goto unavailable;
		missing_txt = 1;
	} else {
		while(fgets(line, sizeof(line), fp)) {
			if(line[0] == '\n' || line[0] == '\r' || line[0] == '/' || line[0] == '#')
				continue;
			if(!strchr(line, '\n') || !cashshop_parse_row(line, &account, &sale, &purchased)) {
				cashshop_ready = 0;
				break;
			}
			cashshop_set(account, sale, (unsigned int)purchased);
		}
		if(ferror(fp))
			cashshop_ready = 0;
		if(fclose(fp) != 0)
			cashshop_ready = 0;
		if(!cashshop_ready)
			goto unavailable;
	}
#ifdef TXT_JOURNAL
	/* enable:0でも未反映の既存履歴は先に回収する。 */
	loaded = journal_load_checked_with_convert(&cashshop_journal, sizeof(struct cashshop_journal_row),
		CASHSHOP_JOURNAL_FILE, cashshop_journal_scan);
	if(loaded < 0 || !cashshop_ready)
		goto unavailable;
	had_file = cashshop_journal.fp != NULL;
	/* 差分だけでは消えた基底TXTの全履歴を復元できない。 */
	if(missing_txt && had_file)
		goto unavailable;
	cashshop_valid = 1;
	if(loaded > 0) {
		if(cashshopdb_txt_sync() != 0)
			goto unavailable;
	}
	if(missing_txt) {
		/* 最初の書込み世代を作る前に、空の基底TXTを確定する。 */
		cashshop_dirty = 1;
		if(cashshopdb_txt_sync() != 0)
			goto unavailable;
	}
	if(cashshop_journal_cfg.enable) {
		if(cashshop_journal.mode != 0 || !cashshop_journal.fp) {
			journal_final(&cashshop_journal);
			if(!journal_create_checked(&cashshop_journal, sizeof(struct cashshop_journal_row),
				cashshop_journal_cfg.cache, CASHSHOP_JOURNAL_FILE))
				goto unavailable;
		}
		if(cashshop_journal.io_error)
			goto unavailable;
	} else {
		journal_final(&cashshop_journal);
		if(cashshop_journal.io_error || (had_file && remove(CASHSHOP_JOURNAL_FILE) != 0))
			goto unavailable;
	}
#else
	/* 復旧できないビルドでは残存履歴を無視して販売を再開しない。 */
	fp = fopen(CASHSHOP_JOURNAL_FILE, "rb");
	if(fp) {
		fclose(fp);
		goto unavailable;
	}
	if(errno != ENOENT)
		goto unavailable;
	cashshop_valid = 1;
	if(missing_txt) {
		cashshop_dirty = 1;
		if(cashshopdb_txt_sync() != 0)
			goto unavailable;
	}
#endif
#ifdef TXT_JOURNAL
	if(cashshop_journal_ids) numdb_final(cashshop_journal_ids, NULL);
	cashshop_journal_ids = NULL;
#endif
	return true;

unavailable:
#ifdef TXT_JOURNAL
	if(cashshop_journal_ids) numdb_final(cashshop_journal_ids, NULL);
	cashshop_journal_ids = NULL;
	/* 復旧拒否後はファイルを閉じ、稼働中にも退避・修復できるようにする。 */
	if(cashshop_journal.db && cashshop_journal.mode == 1)
		journal_final(&cashshop_journal);
#endif
	cashshop_ready = 0;
	printf("cashshop: purchase history unavailable; account sales disabled\n");
	return false;
}

bool cashshopdb_txt_load(int account, struct cashshop_account_count *rows, int count)
{
	int i;
	if(!cashshop_ready || account <= 0 || !rows || count < 1 || count > CASHSHOP_ACCOUNT_MAX)
		return false;
	for(i = 0; i < count; i++) {
		struct cashshop_txt_row *row;
		if(rows[i].sale_id <= 0)
			return false;
		row = cashshop_get(account, rows[i].sale_id);
		rows[i].purchased = row ? row->sale.purchased : 0;
	}
	return true;
}

bool cashshopdb_txt_save(int account, const struct cashshop_account_count *rows, int count)
{
	int i, changed = 0;
#ifdef TXT_JOURNAL
	int ok = 1;
#endif
	if(!cashshop_ready || account <= 0 || !rows || count < 1 || count > CASHSHOP_ACCOUNT_MAX)
		return false;
	for(i = 0; i < count; i++) {
		if(rows[i].sale_id <= 0 || rows[i].purchased > INT_MAX)
			return false;
	}
	for(i = 0; i < count; i++) {
		struct cashshop_txt_row *row = cashshop_get(account, rows[i].sale_id);
		if(rows[i].purchased <= (row ? row->sale.purchased : 0))
			continue;
		row = cashshop_set(account, rows[i].sale_id, rows[i].purchased);
		cashshop_dirty = changed = 1;
#ifdef TXT_JOURNAL
		if(cashshop_journal_cfg.enable) {
			struct cashshop_journal_row record;
			if(!row->journal_id) {
				if(cashshop_journal_next_id == INT_MAX) {
					ok = 0;
					continue;
				}
				row->journal_id = ++cashshop_journal_next_id;
			}
			record.id = row->journal_id;
			record.account_id = account;
			record.sale = row->sale;
			/* 一部失敗時も残りの最新値をキャッシュに取り込む。 */
			if(!journal_write(&cashshop_journal, record.id, &record))
				ok = 0;
		}
#endif
	}
	if(!changed)
		return true;
#ifdef TXT_JOURNAL
	if(cashshop_journal_cfg.enable) {
		/* キャッシュ間隔にかかわらず、保存応答前に全件のflushを確認する。 */
		if(journal_flush(&cashshop_journal) != 0 || !ok)
			goto unavailable;
		return true;
	}
#endif
	/* ジャーナル無効時も、成功応答前にTXT全体を確定する。 */
	if(cashshopdb_txt_sync() == 0)
		return true;
#ifdef TXT_JOURNAL
unavailable:
#endif
	cashshop_ready = 0;
	printf("cashshop: purchase history save failed; account sales disabled\n");
	return false;
}

static int cashshop_sync_row(void *key, void *data, va_list ap)
{
	const struct cashshop_txt_row *row = (const struct cashshop_txt_row *)data;
	FILE *fp = va_arg(ap, FILE *);
	fprintf(fp, "%d %d %u\n", row->account_id, row->sale.sale_id, row->sale.purchased);
	return 0;
}

int cashshopdb_txt_sync(void)
{
	FILE *fp;
	int lock, journal_exists;
	if(!cashshop_valid)
		return 1;
	if(!cashshop_dirty)
		return 0;
	if(cashshop_files_conflict(&journal_exists) != 0) {
		cashshop_ready = 0;
		return 1;
	}
#ifdef TXT_JOURNAL
	if(cashshop_journal_cfg.enable && journal_checkpoint(&cashshop_journal) != 0)
		return 1;
#endif
	fp = lock_fopen(cashshop_txt, &lock);
	if(!fp)
		return 1;
	strdb_foreach(cashshop_db, cashshop_sync_row, fp);
	if(lock_fclose_checked(fp, cashshop_txt, &lock) != 0)
		return 1;
	/* 初回TXT作成で初めて現れる短名・別名も、切詰め前に拒否する。 */
	if(cashshop_files_conflict(&journal_exists) != 0) {
		cashshop_ready = 0;
		return 1;
	}
#ifdef TXT_JOURNAL
	if(cashshop_journal_cfg.enable) {
		if(!journal_recreate_checked(&cashshop_journal, &cashshop_journal_cfg, sizeof(struct cashshop_journal_row))) {
			cashshop_ready = 0;
			return 1;
		}
		if(!cashshop_journal.fp || cashshop_journal.mode != 0 || cashshop_journal.io_error)
			return 1;
		strdb_foreach(cashshop_db, cashshop_journal_reset_id);
		cashshop_journal_next_id = 0;
	}
#endif
	cashshop_dirty = 0;
	return 0;
}

static int cashshop_free_row(void *key, void *data, va_list ap)
{
	aFree(data);
	return 0;
}

void cashshopdb_txt_final(void)
{
	/* 販売停止後も、有効なDBに残した最新値の保存を再試行する。 */
	if(cashshop_valid && cashshop_dirty)
		cashshopdb_txt_sync();
#ifdef TXT_JOURNAL
	if(cashshop_journal.db)
		journal_final(&cashshop_journal);
#endif
	if(cashshop_db)
		strdb_final(cashshop_db, cashshop_free_row);
	cashshop_db = NULL;
	cashshop_ready = cashshop_valid = cashshop_dirty = 0;
}
