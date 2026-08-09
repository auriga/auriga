/*
 * Copyright (C) 2002-2026  Auriga
 *
 * This file is part of Auriga.
 *
 * Status change start/end handler table (Issue #57 PR4).
 * NULL entries fall back to the large switch in status_change_start/end.c.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nullpo.h"
#include "timer.h"

#include "map.h"
#include "status.h"
#include "status_internal.h"
#include "unit.h"

struct status_change_handler status_change_handlers[MAX_STATUSCHANGE];

/* Shared: set calc_flag and continue (skip fallback switch). */
static int sc_start_set_calc_flag(struct status_change_start_ctx *ctx)
{
	*ctx->calc_flag = 1;
	return STATUS_CHANGE_HANDLER_OK;
}

static int sc_end_set_calc_flag(struct status_change_end_ctx *ctx)
{
	*ctx->calc_flag = 1;
	return STATUS_CHANGE_HANDLER_OK;
}

/*
 * Shared: calc_flag + movement speed recalc.
 *
 * When peeling SCs out of a fall-through group into handlers, verify:
 * - both start and end paths
 * - body matches former group mates (side effects beyond calc_flag)
 * - corresponding case labels removed from the fallback switch
 */
static int sc_start_set_calc_flag_speed(struct status_change_start_ctx *ctx)
{
	*ctx->calc_flag = 1;
	ctx->ud->state.change_speed = 1;
	return STATUS_CHANGE_HANDLER_OK;
}

static int sc_end_set_calc_flag_speed(struct status_change_end_ctx *ctx)
{
	*ctx->calc_flag = 1;
	ctx->ud->state.change_speed = 1;
	return STATUS_CHANGE_HANDLER_OK;
}

/* Named example: Provoke (calc_flag + autoberserk tick clamp). */
static int sc_start_provoke(struct status_change_start_ctx *ctx)
{
	*ctx->calc_flag = 1;
	if(*ctx->tick <= 0)
		*ctx->tick = 1000; /* (autoberserk) */
	return STATUS_CHANGE_HANDLER_OK;
}

/* Increase AGI: cancel Decrease AGI and recalc speed. */
static int sc_start_increaseagi(struct status_change_start_ctx *ctx)
{
	*ctx->calc_flag = 1;
	ctx->ud->state.change_speed = 1;
	if(ctx->sc->data[SC_DECREASEAGI].timer != -1)
		status_change_end(ctx->bl, SC_DECREASEAGI, -1);
	return STATUS_CHANGE_HANDLER_OK;
}

void status_change_handlers_init(void)
{
	memset(status_change_handlers, 0, sizeof(status_change_handlers));

	/* calc_flag only (start + end) */
	status_change_handlers[SC_ATKPOTION].start = sc_start_set_calc_flag;
	status_change_handlers[SC_ATKPOTION].end   = sc_end_set_calc_flag;
	status_change_handlers[SC_MATKPOTION].start = sc_start_set_calc_flag;
	status_change_handlers[SC_MATKPOTION].end   = sc_end_set_calc_flag;
	status_change_handlers[SC_ALMIGHTY].start = sc_start_set_calc_flag;
	status_change_handlers[SC_ALMIGHTY].end   = sc_end_set_calc_flag;
	status_change_handlers[SC_BLESSING].start = sc_start_set_calc_flag;
	status_change_handlers[SC_BLESSING].end   = sc_end_set_calc_flag;
	status_change_handlers[SC_IMPOSITIO].start = sc_start_set_calc_flag;
	status_change_handlers[SC_IMPOSITIO].end   = sc_end_set_calc_flag;
	status_change_handlers[SC_SUPPORT_HPSP].start = sc_start_set_calc_flag;
	/* SC_SUPPORT_HPSP end: not in end switch historically; leave fallback */

	/* Provoke: named start + calc_flag end */
	status_change_handlers[SC_PROVOKE].start = sc_start_provoke;
	status_change_handlers[SC_PROVOKE].end   = sc_end_set_calc_flag;

	/* Increase AGI: named start + speed end */
	status_change_handlers[SC_INCREASEAGI].start = sc_start_increaseagi;
	status_change_handlers[SC_INCREASEAGI].end   = sc_end_set_calc_flag_speed;

	/* Speed potions: calc_flag + change_speed both sides */
	status_change_handlers[SC_SPEEDUP0].start = sc_start_set_calc_flag_speed;
	status_change_handlers[SC_SPEEDUP0].end   = sc_end_set_calc_flag_speed;
	status_change_handlers[SC_SPEEDUP1].start = sc_start_set_calc_flag_speed;
	status_change_handlers[SC_SPEEDUP1].end   = sc_end_set_calc_flag_speed;
}
