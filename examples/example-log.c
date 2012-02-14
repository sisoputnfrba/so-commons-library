/*
 * log.c
 *
 *  Created on: Feb 3, 2012
 *      Author: Prieto, Gaston
 */

#include <stdlib.h>
#include <commons/log.h>
#include <CUnit/CUnit.h>

#include "test_tools.h"

static int init_suite(){
	return 0;
}


static int clean_suite(){
	return 0;
}

static void test_log() {
	t_logger logger = log_create(NULL, "EXAMPLE", true, LOG_LEVEL_INFO);

	log_destroy(logger);
}

/**********************************************************************************************
 *  							Building the test for CUnit
 *********************************************************************************************/

static CU_TestInfo tests[] = {
  { "Test Log Functions", test_log },
  CU_TEST_INFO_NULL,
};

CU_SuiteInfo log_suite = { "Log TAD Suite", init_suite, clean_suite, tests };

TEST_TOOLS_ADD_SUITE(log_suite)


