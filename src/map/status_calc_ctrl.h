/*
 * Copyright (C) 2002-2026  Auriga
 *
 * This file is part of Auriga.
 *
 * Pure control helpers for status_calc_pc reentry (Issue #57 / L_RECALC).
 * No map types - safe to link from Unity unit tests.
 */

#ifndef _STATUS_CALC_CTRL_H_
#define _STATUS_CALC_CTRL_H_

#ifdef __cplusplus
extern "C" {
#endif

/* status_calc_pc_ctrl_begin() results */
enum status_calc_pc_ctrl_begin_result {
	STATUS_CALC_PC_CTRL_RUN = 0,     /* proceed with calculation */
	STATUS_CALC_PC_CTRL_DELAYED = 1, /* stop_status_calc_pc active; deferred */
	STATUS_CALC_PC_CTRL_BUSY = 2     /* already inside status_calc_pc; skip */
};

/*
 * Enter status_calc_pc.
 * stop / call_while_stopping / process are the matching short fields on sd.
 *
 * Contract:
 * - stop > 0  -> increment call_while_stopping, return DELAYED
 * - else clear call_while_stopping; post-increment process;
 *   if previous process was non-zero return BUSY, else RUN
 */
int status_calc_pc_ctrl_begin(short *stop, short *call_while_stopping, short *process);

/*
 * After one calc body pass.
 * If process > 1 and calclimit can be decremented: set process=1, return 1 (recalc).
 * If process > 1 but calclimit exhausted: set process=0, return -1 (infinity).
 * Otherwise set process=0, return 0 (done).
 */
int status_calc_pc_ctrl_finish(short *process, int *calclimit);

/* stop_begin: nest++ */
void status_calc_pc_ctrl_stop_begin(short *stop);

/*
 * stop_end: nest--.
 * Returns 1 if caller should invoke status_calc_pc(sd,0),
 * -1 if stop went negative (underflow), 0 otherwise.
 */
int status_calc_pc_ctrl_stop_end(short *stop, short *call_while_stopping);

/* Initial calclimit: first pass runs use-script (calclimit==2). */
#define STATUS_CALC_PC_CALCLIMIT_INIT 2

#ifdef __cplusplus
}
#endif

#endif /* _STATUS_CALC_CTRL_H_ */
