#include "unity.h"
#include "../src/map/status_calc_ctrl.h"

void test_status_calc_ctrl_begin_run(void)
{
	short stop = 0;
	short call_while = 5;
	short process = 0;

	TEST_ASSERT_EQUAL_INT(STATUS_CALC_PC_CTRL_RUN,
		status_calc_pc_ctrl_begin(&stop, &call_while, &process));
	TEST_ASSERT_EQUAL_INT(0, call_while);
	TEST_ASSERT_EQUAL_INT(1, process);
}

void test_status_calc_ctrl_begin_delayed(void)
{
	short stop = 2;
	short call_while = 0;
	short process = 0;

	TEST_ASSERT_EQUAL_INT(STATUS_CALC_PC_CTRL_DELAYED,
		status_calc_pc_ctrl_begin(&stop, &call_while, &process));
	TEST_ASSERT_EQUAL_INT(1, call_while);
	TEST_ASSERT_EQUAL_INT(0, process);
}

void test_status_calc_ctrl_begin_busy(void)
{
	short stop = 0;
	short call_while = 0;
	short process = 1;

	TEST_ASSERT_EQUAL_INT(STATUS_CALC_PC_CTRL_BUSY,
		status_calc_pc_ctrl_begin(&stop, &call_while, &process));
	TEST_ASSERT_EQUAL_INT(2, process);
}

void test_status_calc_ctrl_finish_done(void)
{
	short process = 1;
	int calclimit = STATUS_CALC_PC_CALCLIMIT_INIT;

	TEST_ASSERT_EQUAL_INT(0, status_calc_pc_ctrl_finish(&process, &calclimit));
	TEST_ASSERT_EQUAL_INT(0, process);
	TEST_ASSERT_EQUAL_INT(STATUS_CALC_PC_CALCLIMIT_INIT, calclimit);
}

void test_status_calc_ctrl_finish_recalc(void)
{
	short process = 2;
	int calclimit = STATUS_CALC_PC_CALCLIMIT_INIT;

	TEST_ASSERT_EQUAL_INT(1, status_calc_pc_ctrl_finish(&process, &calclimit));
	TEST_ASSERT_EQUAL_INT(1, process);
	TEST_ASSERT_EQUAL_INT(1, calclimit);
}

void test_status_calc_ctrl_finish_infinity(void)
{
	short process = 3;
	int calclimit = 1;

	TEST_ASSERT_EQUAL_INT(-1, status_calc_pc_ctrl_finish(&process, &calclimit));
	TEST_ASSERT_EQUAL_INT(0, process);
	TEST_ASSERT_EQUAL_INT(0, calclimit);
}

void test_status_calc_ctrl_recalc_then_done(void)
{
	short process = 2;
	int calclimit = STATUS_CALC_PC_CALCLIMIT_INIT;

	TEST_ASSERT_EQUAL_INT(1, status_calc_pc_ctrl_finish(&process, &calclimit));
	/* second body pass without further reentry */
	process = 1;
	TEST_ASSERT_EQUAL_INT(0, status_calc_pc_ctrl_finish(&process, &calclimit));
	TEST_ASSERT_EQUAL_INT(0, process);
}

void test_status_calc_ctrl_stop_nesting(void)
{
	short stop = 0;
	short call_while = 0;

	status_calc_pc_ctrl_stop_begin(&stop);
	status_calc_pc_ctrl_stop_begin(&stop);
	TEST_ASSERT_EQUAL_INT(2, stop);

	TEST_ASSERT_EQUAL_INT(0, status_calc_pc_ctrl_stop_end(&stop, &call_while));
	TEST_ASSERT_EQUAL_INT(1, stop);

	call_while = 3;
	TEST_ASSERT_EQUAL_INT(1, status_calc_pc_ctrl_stop_end(&stop, &call_while));
	TEST_ASSERT_EQUAL_INT(0, stop);
}

void test_status_calc_ctrl_stop_underflow(void)
{
	short stop = 0;
	short call_while = 0;

	TEST_ASSERT_EQUAL_INT(-1, status_calc_pc_ctrl_stop_end(&stop, &call_while));
	TEST_ASSERT_EQUAL_INT(-1, stop);
}
