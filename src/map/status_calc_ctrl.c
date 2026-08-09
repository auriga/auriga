/*
 * Copyright (C) 2002-2026  Auriga
 *
 * This file is part of Auriga.
 *
 * Pure control helpers for status_calc_pc reentry (Issue #57 / L_RECALC).
 */

#include "status_calc_ctrl.h"

int status_calc_pc_ctrl_begin(short *stop, short *call_while_stopping, short *process)
{
	if(*stop) {
		(*call_while_stopping)++;
		return STATUS_CALC_PC_CTRL_DELAYED;
	}

	*call_while_stopping = 0;

	/* Post-increment: non-zero previous value means nested/reentrant call. */
	if((*process)++)
		return STATUS_CALC_PC_CTRL_BUSY;

	return STATUS_CALC_PC_CTRL_RUN;
}

int status_calc_pc_ctrl_finish(short *process, int *calclimit)
{
	if(*process > 1) {
		if(--(*calclimit)) {
			*process = 1;
			return 1; /* recalc */
		}
		*process = 0;
		return -1; /* infinity loop */
	}

	*process = 0;
	return 0; /* done */
}

void status_calc_pc_ctrl_stop_begin(short *stop)
{
	(*stop)++;
}

int status_calc_pc_ctrl_stop_end(short *stop, short *call_while_stopping)
{
	(*stop)--;
	if(*stop == 0 && *call_while_stopping > 0)
		return 1;
	if(*stop < 0)
		return -1;
	return 0;
}
