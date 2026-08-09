/*
 * Copyright (C) 2002-2026  Auriga
 *
 * This file is part of Auriga.
 *
 * Internal declarations shared by status*.c (not part of public status.h API).
 * Introduced for Issue #57 file split.
 */

#ifndef _STATUS_INTERNAL_H_
#define _STATUS_INTERNAL_H_

#include "status.h"

/* Weapon ATK size fix table (size_fix.txt) - defined in status.c */
extern int atkmods[MAX_SIZE_FIX][WT_MAX];

/* Refine bonus / success table (refine_db.txt) - defined in status.c */
struct refine_db {
	int safety_bonus[MAX_REFINE];
	int over_bonus;
	int limit;
	int per[MAX_REFINE];
};
extern struct refine_db refine_db[MAX_WEAPON_LEVEL+1];

/* Status icon SI_* table - defined in status.c */
extern int StatusIconChangeTable[MAX_STATUSCHANGE];


/* Return codes for start/end body handlers */
#define STATUS_CHANGE_HANDLER_OK     0  /* handled; skip fallback switch */
#define STATUS_CHANGE_HANDLER_ABORT  1  /* abort status_change_start/end (return 0) */

struct status_change_start_ctx {
	struct block_list *bl;
	struct map_session_data *sd;
	struct mob_data *md;
	struct homun_data *hd;
	struct merc_data *mcd;
	struct elem_data *eld;
	struct status_change *sc;
	struct unit_data *ud;
	int type;
	int *val1, *val2, *val3, *val4;
	int *tick;
	int flag;
	int *calc_flag;
	int *icon_tick, *icon_val1, *icon_val2, *icon_val3;
	int *opt_flag;
};

struct status_change_end_ctx {
	struct block_list *bl;
	struct map_session_data *sd;
	struct homun_data *hd;
	struct merc_data *mcd;
	struct elem_data *eld;
	struct status_change *sc;
	struct unit_data *ud;
	int type;
	int tid;
	int *calc_flag;
	int *opt_flag;
};

typedef int (*status_change_start_fn)(struct status_change_start_ctx *ctx);
typedef int (*status_change_end_fn)(struct status_change_end_ctx *ctx);

struct status_change_handler {
	status_change_start_fn start; /* NULL = use fallback switch */
	status_change_end_fn end;
};

extern struct status_change_handler status_change_handlers[MAX_STATUSCHANGE];
void status_change_handlers_init(void);

#endif /* _STATUS_INTERNAL_H_ */
