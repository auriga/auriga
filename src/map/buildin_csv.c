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
#include <stdarg.h>
#include <ctype.h>

#include "db.h"
#include "socket.h"
#include "timer.h"
#include "malloc.h"
#include "mmo.h"
#include "nullpo.h"
#include "utils.h"

#include "map.h"
#include "pc.h"
#include "script.h"
#include "script_internal.h"

/* Split from script.c (Issue #61) */

#ifndef NO_CSVDB_SCRIPT
/*==========================================
 * CSVアクセス命令/関数群
 *------------------------------------------
 */
static struct dbt* script_csvdb;

int script_csvinit(void)
{
	script_csvdb = strdb_init(0);
	return 0;
}

static int script_csvfinal_sub(void *key, void *data, va_list ap)
{
	struct csvdb_data *csv = (struct csvdb_data *)data;

	csvdb_close( csv );
	return 0;
}

int script_csvfinal(void)
{
	strdb_final( script_csvdb, script_csvfinal_sub );
	return 0;
}

// ファイル名が妥当なものかチェックする
static int script_csvfilename_check(const char *file, const char *func)
{
	const unsigned char *p = file;

	while(*p) {
		if( !isalnum(*p) && *p != '/' && *p != '_' ) {
			printf("%s: invalid file name %s\n", func, file);
			return 0;
		}
		p++;
	}
	return 1;
}

static struct csvdb_data* script_csvload(const char *file)
{
	struct csvdb_data *csv = (struct csvdb_data *)strdb_search(script_csvdb, file);

	if( csv == NULL ) {
		// ファイル名に変なものが入っていないか確認
		int i;
		for(i = 0; file[i]; i++) {
			switch(file[i]) {
			case '.':
				if(file[i+1] != '.') break;
				// fall through
			case '<':
			case '>':
			case '|':
				printf("script_csvload: invalid file name %s\n", file);
				return NULL;
			}
		}
		csv = csvdb_open( file, 0 );
		if( csv ) {
			printf("script_csvload: %s load successfully\n", file);
			strdb_insert( script_csvdb, csv->file, csv );
		}
	}
	return csv;
}

int buildin_csvgetrows(struct script_state *st)
{
	char *file = conv_str(st,& (st->stack->stack_data[st->start+2]));
	struct csvdb_data *csv = script_csvload( file );

	if( csv == NULL ) {
		push_val(st->stack,C_INT,-1);
	} else {
		push_val(st->stack,C_INT,csvdb_get_rows(csv));
	}
	return 0;
}

int buildin_csvgetcols(struct script_state *st)
{
	char *file = conv_str(st,& (st->stack->stack_data[st->start+2]));
	int  row   = conv_num(st,& (st->stack->stack_data[st->start+3]));
	struct csvdb_data *csv = script_csvload( file );

	if( csv == NULL ) {
		push_val(st->stack,C_INT,-1);
	} else {
		push_val(st->stack,C_INT,csvdb_get_columns(csv, row));
	}
	return 0;
}

// csvread <file>, <row>, <cow>
int buildin_csvread(struct script_state *st)
{
	char *file = conv_str(st,& (st->stack->stack_data[st->start+2]));
	int  row   = conv_num(st,& (st->stack->stack_data[st->start+3]));
	int  col   = conv_num(st,& (st->stack->stack_data[st->start+4]));
	const char *v;
	struct csvdb_data *csv = script_csvload( file );

	v = (csv ? csvdb_get_str(csv, row, col) : NULL);

	if( v ) {
		push_str(st->stack,C_STR,(unsigned char *)aStrdup(v));
	} else {
		push_str(st->stack,C_CONSTSTR,"");
	}
	return 0;
}

// csvreadarray <file>, <row>, <array>
int buildin_csvreadarray(struct script_state *st)
{
	int i;
	struct map_session_data *sd = NULL;
	char *file = conv_str(st,& (st->stack->stack_data[st->start+2]));
	int  row   = conv_num(st,& (st->stack->stack_data[st->start+3]));
	int  num;
	char *name;
	char prefix, postfix;
	struct csvdb_data* csv = script_csvload( file );

	if( st->stack->stack_data[st->start+4].type != C_NAME ) {
		printf("buildin_csvreadarray: param not name\n");
		return 0;
	}
	num     = st->stack->stack_data[st->start+4].u.num;
	name    = get_str(num&0x00ffffff);
	prefix  = *name;
	postfix = name[strlen(name)-1];

	if( prefix != '$' && prefix != '@' && prefix != '\'' && prefix != '.' ) {
		printf("buildin_csvreadarray: illegal scope !\n");
		return 0;
	}
	if( prefix != '$' && prefix != '\'' && prefix != '.' ) {
		sd = script_rid2sd(st);
		if(sd == NULL)
			return 0;
	}

	// clear array
	for(i = getarraysize(st,num,postfix,st->stack->stack_data[st->start+4].ref) - (num >> 24) - 1;i >= 0;i--) {
		set_reg(st,sd,num+(i<<24),name,(postfix == '$')? "": 0,st->stack->stack_data[st->start+4].ref);
	}

	if( csv ) {
		const void *v;
		int max = csvdb_get_columns( csv, row );
		if( max + (num >> 24) > 128 ) {
			max = 128 - (num>>24);
		}
		for( i = 0; i < max; i++ ) {
			if( postfix == '$' )
				v = (const void *)csvdb_get_str(csv, row, i);
			else
				v = INT2PTR(csvdb_get_num(csv, row, i));
			set_reg(st,sd,num+(i<<24),name,v,st->stack->stack_data[st->start+4].ref);
		}
	}
	return 0;
}

// csvfind <file>, <col>, <val>
int buildin_csvfind(struct script_state *st)
{
	char *file = conv_str(st,& (st->stack->stack_data[st->start+2]));
	int   col  = conv_num(st,& (st->stack->stack_data[st->start+3]));
	struct csvdb_data *csv = script_csvload( file );

	if( !csv ) {
		push_val(st->stack,C_INT,-1);
	} else if( isstr(&st->stack->stack_data[st->start+4])) {
		char *str = conv_str(st,& (st->stack->stack_data[st->start+4]));
		push_val(st->stack,C_INT,csvdb_find_str(csv, col, str));
	} else {
		int  val  = conv_num(st,& (st->stack->stack_data[st->start+4]));
		push_val(st->stack,C_INT,csvdb_find_num(csv, col, val));
	}
	return 0;
}

// csvwrite <file>, <row>, <col>, <val>
int buildin_csvwrite(struct script_state *st)
{
	char *file = conv_str(st,& (st->stack->stack_data[st->start+2]));
	int  row   = conv_num(st,& (st->stack->stack_data[st->start+3]));
	int  col   = conv_num(st,& (st->stack->stack_data[st->start+4]));
	struct csvdb_data *csv;

	if( !script_csvfilename_check(file, "buildin_csvwrite") )
		return 0;
	csv = script_csvload( file );

	if( isstr(&st->stack->stack_data[st->start+5]) ) {
		char *str = conv_str(st,& (st->stack->stack_data[st->start+5]));
		csvdb_set_str(csv, row, col, str);
	} else {
		int   val = conv_num(st,& (st->stack->stack_data[st->start+5]));
		csvdb_set_num(csv, row, col, val);
	}
	return 0;
}

// csvwritearray <file>, <row>, <array>
int buildin_csvwritearray(struct script_state *st)
{
	char *file = conv_str(st,& (st->stack->stack_data[st->start+2]));
	int  row   = conv_num(st,& (st->stack->stack_data[st->start+3]));
	int  num;
	char *name;
	char prefix, postfix;
	struct csvdb_data* csv;

	if( st->stack->stack_data[st->start+4].type != C_NAME ) {
		printf("buildin_csvwritearray: param not name\n");
		return 0;
	}
	num     = st->stack->stack_data[st->start+4].u.num;
	name    = get_str(num&0x00ffffff);
	prefix  = *name;
	postfix = name[strlen(name)-1];

	if( prefix != '$' && prefix != '@' && prefix != '\'' && prefix != '.' ) {
		printf("buildin_csvwritearray: illegal scope !\n");
		return 0;
	}

	if( !script_csvfilename_check(file, "buildin_csvwritearray") )
		return 0;

	csv = script_csvload( file );
	if( csv ) {
		int max = getarraysize(st, num, postfix, st->stack->stack_data[st->start+4].ref) - (num >> 24);
		int i;

		csvdb_clear_row( csv, row );
		for( i = 0; i < max; i++ ) {
			if( postfix == '$' ) {
				csvdb_set_str(csv, row, i, (char*)get_val2(st, num+(i<<24),st->stack->stack_data[st->start+4].ref));
			} else {
				csvdb_set_num(csv, row, i, PTR2INT(get_val2(st, num+(i<<24),st->stack->stack_data[st->start+4].ref)));
			}
		}
	}
	return 0;
}

// csvreload <file>
int buildin_csvreload(struct script_state *st)
{
	char *file = conv_str(st,& (st->stack->stack_data[st->start+2]));
	struct csvdb_data *csv = (struct csvdb_data *)strdb_erase( script_csvdb, file );

	if( csv ) {
		csvdb_close( csv );
	}
	return 0;
}

// csvinsert <file>, <row>
int buildin_csvinsert(struct script_state *st)
{
	char *file = conv_str(st,& (st->stack->stack_data[st->start+2]));
	int   row  = conv_num(st,& (st->stack->stack_data[st->start+3]));
	struct csvdb_data *csv;

	if( !script_csvfilename_check(file, "buildin_csvinsert") )
		return 0;

	csv = script_csvload(file);
	if( csv ) {
		csvdb_insert_row(csv, row);
	}
	return 0;
}

// csvdelete <file>, <row>
int buildin_csvdelete(struct script_state *st)
{
	char *file = conv_str(st,& (st->stack->stack_data[st->start+2]));
	int   row  = conv_num(st,& (st->stack->stack_data[st->start+3]));
	struct csvdb_data *csv;

	if( !script_csvfilename_check(file, "buildin_csvdelete") )
		return 0;

	csv = script_csvload( file );
	if( csv ) {
		csvdb_delete_row(csv, row);
	}
	return 0;
}

// csvsort <file>, <col>, <order>
int buildin_csvsort(struct script_state *st)
{
	char *file  = conv_str(st,& (st->stack->stack_data[st->start+2]));
	int   col   = conv_num(st,& (st->stack->stack_data[st->start+3]));
	int   order = conv_num(st,& (st->stack->stack_data[st->start+4]));
	struct csvdb_data *csv;

	if( !script_csvfilename_check(file, "buildin_csvsort") )
		return 0;

	csv = script_csvload(file);
	if( csv ) {
		csvdb_sort(csv, col, order);
	}
	return 0;
}

// csvflush <file>
int buildin_csvflush(struct script_state *st)
{
	char *file = conv_str(st,& (st->stack->stack_data[st->start+2]));
	struct csvdb_data *csv;

	if( !script_csvfilename_check(file, "buildin_csvflush") )
		return 0;

	csv = (struct csvdb_data *)strdb_search( script_csvdb, file );
	if( csv ) {
		csvdb_flush( csv );
	}
	return 0;
}

#endif
