/*
 * Copyright (C) 2002-2020  Auriga
 *
 * This file is part of Auriga.
 *
 * Internal declarations shared by script*.c / buildin_*.c
 * (not part of public script.h API).
 * Introduced for Issue #61 file split.
 */

#ifndef _SCRIPT_INTERNAL_H_
#define _SCRIPT_INTERNAL_H_

#include "script.h"

/* script bytecode / stack data types */
enum {
	C_NOP = 0,
	C_POS,
	C_INT,
	C_PARAM,
	C_FUNC,
	C_STR,
	C_CONSTSTR,
	C_PTR,
	C_ARG,
	C_NAME,
	C_EOL,
	C_RETINFO,

	/* user-defined functions */
	C_USERFUNC,
	C_USERFUNC_POS,

	/* operators */
	C_OP3,
	C_LOR,
	C_LAND,
	C_LE,
	C_LT,
	C_GE,
	C_GT,
	C_EQ,
	C_NE,
	C_XOR,
	C_OR,
	C_AND,
	C_ADD,
	C_SUB,
	C_MUL,
	C_DIV,
	C_MOD,
	C_POW,
	C_NEG,
	C_LNOT,
	C_NOT,
	C_R_SHIFT,
	C_L_SHIFT,
	C_ADD_PRE,
	C_SUB_PRE,
	C_ADD_POST,
	C_SUB_POST,
};

/* script execution state */
enum {
	RUN = 0,
	STOP,
	END,
	RERUNLINE,
	GOTO,
	RETFUNC
};

struct map_session_data *script_rid2sd(struct script_state *st);
int script_getmemorialid(struct script_state *st);

void get_val(struct script_state *st, struct script_data *data);
void *get_val2(struct script_state *st, int num, struct linkdb_node **ref);
int set_reg(struct script_state *st, struct map_session_data *sd, int num, const char *name, const void *v, struct linkdb_node **ref);

char *conv_str(struct script_state *st, struct script_data *data);
int conv_num(struct script_state *st, struct script_data *data);

void push_val(struct script_stack *stack, int type, int val);
void push_val2(struct script_stack *stack, int type, int val, struct linkdb_node **ref);
void push_str(struct script_stack *stack, int type, unsigned char *str);
void push_ptr(struct script_stack *stack, int type, void *ptr);
void push_copy(struct script_stack *stack, int pos);
void pop_stack(struct script_stack *stack, int start, int end);

int isstr(struct script_data *c);
int script_mapname2mapid(struct script_state *st, const char *mapname);

int script_warp(struct map_session_data *sd, const char *mapname, int x, int y);

#endif /* _SCRIPT_INTERNAL_H_ */
