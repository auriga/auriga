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
#include "db.h"
#include "lock.h"
#include "malloc.h"
#include "journal.h"
#include "utils.h"
#include "nullpo.h"

#include "petdb_txt.h"

static struct dbt *pet_db = NULL;

static char pet_txt[1024] = "save/pet.txt";
static int pet_newid = 100;

#ifdef TXT_JOURNAL
static int pet_journal_enable = 1;
static struct journal pet_journal;
static char pet_journal_file[1024] = "./save/pet.journal";
static int pet_journal_cache = 1000;
#endif

/*==========================================
 * �ݒ�t�@�C���Ǎ�
 *------------------------------------------
 */
int petdb_txt_config_read_sub(const char* w1,const char *w2)
{
	if(strcasecmp(w1,"pet_txt")==0){
		strncpy(pet_txt, w2, sizeof(pet_txt) - 1);
	}
#ifdef TXT_JOURNAL
	else if(strcasecmp(w1,"pet_journal_enable")==0){
		pet_journal_enable = atoi( w2 );
	}
	else if(strcasecmp(w1,"pet_journal_file")==0){
		strncpy( pet_journal_file, w2, sizeof(pet_journal_file) - 1 );
	}
	else if(strcasecmp(w1,"pet_journal_cache_interval")==0){
		pet_journal_cache = atoi( w2 );
	}
#endif
	else {
		return 0;
	}

	return 1;
}

/*==========================================
 * �y�b�g�f�[�^�𕶎���֕ϊ�
 *------------------------------------------
 */
static int pet_tostr(char *str, struct s_pet *p)
{
	nullpo_retr(1, p);

	if(p->hungry < 0)
		p->hungry = 0;
	else if(p->hungry > 100)
		p->hungry = 100;
	if(p->intimate < 0)
		p->intimate = 0;
	else if(p->intimate > 1000)
		p->intimate = 1000;

	sprintf(str, "%d,%d,%s\t%d,%d,%d,%d,%d,%d,%d,%d,%d",
		p->pet_id, p->class_, p->name,p->account_id, p->char_id, p->level, p->egg_id,
		p->equip, p->intimate, p->hungry, p->rename_flag, p->incubate);

	return 0;
}

/*==========================================
 * �y�b�g�f�[�^�𕶎��񂩂�ϊ�
 *------------------------------------------
 */
static int pet_fromstr(char *str, struct s_pet *p)
{
	int s;
	int tmp_int[11];
	char tmp_str[256];

	nullpo_retr(1, p);

	memset(p, 0, sizeof(struct s_pet));

	s = sscanf(str, "%d,%d,%255[^\t]\t%d,%d,%d,%d,%d,%d,%d,%d,%d",
		&tmp_int[0],&tmp_int[1],tmp_str,&tmp_int[2],
		&tmp_int[3],&tmp_int[4],&tmp_int[5],&tmp_int[6],&tmp_int[7],&tmp_int[8],&tmp_int[9],&tmp_int[10]);

	if(s != 12)
		return 1;

	p->pet_id      = tmp_int[0];
	p->class_      = tmp_int[1];
	memcpy(p->name, tmp_str, 24);
	p->name[23] = '\0';	// force \0 terminal
	p->account_id  = tmp_int[2];
	p->char_id     = tmp_int[3];
	p->level       = tmp_int[4];
	p->egg_id      = tmp_int[5];
	p->equip       = tmp_int[6];
	p->intimate    = tmp_int[7];
	p->hungry      = tmp_int[8];
	p->rename_flag = tmp_int[9];
	p->incubate    = tmp_int[10];

	if(p->hungry < 0)
		p->hungry = 0;
	else if(p->hungry > 100)
		p->hungry = 100;
	if(p->intimate < 0)
		p->intimate = 0;
	else if(p->intimate > 1000)
		p->intimate = 1000;

	return 0;
}

#ifdef TXT_JOURNAL
// ==========================================
// �y�b�g�f�[�^�̃W���[�i���̃��[���t�H���[�h�p�R�[���o�b�N�֐�
// ------------------------------------------
int pet_journal_rollforward( int key, void* buf, int flag )
{
	struct s_pet* p = (struct s_pet *)numdb_search( pet_db, key );

	// �O�̂��߃`�F�b�N
	if( flag == JOURNAL_FLAG_WRITE && key != ((struct s_pet*)buf)->pet_id )
	{
		printf("int_pet: journal: key != pet_id !\n");
		return 0;
	}

	// �f�[�^�̒u������
	if( p )
	{
		if( flag == JOURNAL_FLAG_DELETE ) {
			numdb_erase(pet_db, key);
			aFree(p);
		} else {
			memcpy( p, buf, sizeof(struct s_pet) );
		}
		return 1;
	}

	// �ǉ�
	if( flag != JOURNAL_FLAG_DELETE )
	{
		p = (struct s_pet*)aCalloc( 1, sizeof( struct s_pet ) );
		memcpy( p, buf, sizeof(struct s_pet) );
		numdb_insert( pet_db, key, p );
		if( p->pet_id >= pet_newid)
			pet_newid = p->pet_id + 1;
		return 1;
	}

	return 0;
}
#endif

/*==========================================
 * �y�b�g�f�[�^�t�@�C���̓ǂݍ���
 *------------------------------------------
 */
static bool petdb_txt_read(void)
{
	FILE *fp;
	bool ret = true;

	pet_db = numdb_init();

	if((fp = fopen(pet_txt, "r")) == NULL) {
		printf("petdb_txt_read: open [%s] failed !\n", pet_txt);
		ret = false;
	} else {
		int count = 0;
		char line[8192];

		while(fgets(line, sizeof(line), fp)) {
			struct s_pet *p = (struct s_pet *)aCalloc(1, sizeof(struct s_pet));
			if(pet_fromstr(line, p) == 0 && p->pet_id > 0) {
				if(p->pet_id >= pet_newid)
					pet_newid = p->pet_id + 1;
				numdb_insert(pet_db, p->pet_id, p);
			} else {
				printf("int_pet: broken data [%s] line %d\n", pet_txt, count);
				aFree(p);
			}
			count++;
		}
		fclose(fp);
	}

#ifdef TXT_JOURNAL
	if( pet_journal_enable )
	{
		// �W���[�i���f�[�^�̃��[���t�H���[�h
		if( journal_load( &pet_journal, sizeof(struct s_pet), pet_journal_file ) )
		{
			int c = journal_rollforward( &pet_journal, pet_journal_rollforward );

			printf("int_pet: journal: roll-forward (%d)\n", c );

			// ���[���t�H���[�h�����̂ŁAtxt �f�[�^��ۑ����� ( journal ���V�K�쐬�����)
			petdb_txt_sync();
		}
		else
		{
			// �W���[�i����V�K�쐬����
			journal_final( &pet_journal );
			journal_create( &pet_journal, sizeof(struct s_pet), pet_journal_cache, pet_journal_file );
		}
	}
#endif

	return ret;
}

/*==========================================
 * ����
 *------------------------------------------
 */
static int petdb_txt_sync_sub(void *key, void *data, va_list ap)
{
	char line[8192];
	FILE *fp;

	pet_tostr(line, (struct s_pet *)data);
	fp = va_arg(ap, FILE *);
	fprintf(fp, "%s" NEWLINE, line);

	return 0;
}

int petdb_txt_sync(void)
{
	FILE *fp;
	int lock;

	if( !pet_db )
		return 1;

	if( (fp = lock_fopen(pet_txt, &lock)) == NULL ) {
		printf("petdb_txt_sync: can't write [%s] !!! data is lost !!!\n", pet_txt);
		return 1;
	}
	numdb_foreach(pet_db, petdb_txt_sync_sub, fp);
	lock_fclose(fp,pet_txt, &lock);

#ifdef TXT_JOURNAL
	if( pet_journal_enable )
	{
		// �R�~�b�g�����̂ŃW���[�i����V�K�쐬����
		journal_final( &pet_journal );
		journal_create( &pet_journal, sizeof(struct s_pet), pet_journal_cache, pet_journal_file );
	}
#endif

	return 0;
}

/*==========================================
 * �y�b�g�f�[�^�폜
 *------------------------------------------
 */
bool petdb_txt_delete(int pet_id)
{
	struct s_pet *p = (struct s_pet *)numdb_search(pet_db, pet_id);

	if(p == NULL)
		return false;

	numdb_erase(pet_db, pet_id);
	aFree(p);
	printf("pet_id: %d deleted\n", pet_id);

#ifdef TXT_JOURNAL
	if( pet_journal_enable )
		journal_write( &pet_journal, pet_id, NULL );
#endif

	return true;
}

/*==========================================
 * �y�b�gID����y�b�g�f�[�^�����[�h
 *------------------------------------------
 */
const struct s_pet* petdb_txt_load(int pet_id)
{
	return (const struct s_pet *)numdb_search(pet_db, pet_id);
}

/*==========================================
 * �Z�[�u
 *------------------------------------------
 */
bool petdb_txt_save(struct s_pet *p2)
{
	struct s_pet *p1;

	nullpo_retr(false, p2);

	p1 = (struct s_pet *)numdb_search(pet_db, p2->pet_id);
	if(p1 == NULL) {
		p1 = (struct s_pet *)aMalloc(sizeof(struct s_pet));
		numdb_insert(pet_db, p2->pet_id, p1);
	}
	memcpy(p1, p2, sizeof(struct s_pet));

#ifdef TXT_JOURNAL
	if( pet_journal_enable )
		journal_write( &pet_journal, p1->pet_id, p1 );
#endif
	return true;
}

/*==========================================
 * �y�b�g�쐬
 *------------------------------------------
 */
bool petdb_txt_new(struct s_pet *p)
{
	nullpo_retr(false, p);

	p->pet_id = pet_newid++;
	numdb_insert(pet_db, p->pet_id, p);

	return true;
}

/*==========================================
 * �I��
 *------------------------------------------
 */
static int petdb_txt_final_sub(void *key, void *data, va_list ap)
{
	struct s_pet *p = (struct s_pet *)data;

	aFree(p);

	return 0;
}

void petdb_txt_final(void)
{
	if(pet_db)
		numdb_final(pet_db, petdb_txt_final_sub);

#ifdef TXT_JOURNAL
	if( pet_journal_enable )
	{
		journal_final( &pet_journal );
	}
#endif
}

/*==========================================
 * ������
 *------------------------------------------
 */
bool petdb_txt_init(void)
{
	return petdb_txt_read();
}

