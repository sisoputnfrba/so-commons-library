/*
 * test-config.c
 *
 *  Created on: Feb 18, 2012
 *      Author: shinichi
 */

#include <commons/config.h>
#include <stdlib.h>
#include <CUnit/CUnit.h>

#include "cunit_tools.h"

static int init_suite() {
	return 0;
}

static int clean_suite() {
	return 0;
}

void test_read_config() {
	t_config* config = config_create("tests/resources/config.cfg");

	CU_ASSERT_EQUAL_FATAL(config_keys_amount(config), 4);

	CU_ASSERT_TRUE_FATAL(config_has_property(config, "IP"));
	CU_ASSERT_STRING_EQUAL(config_get_string_value(config, "IP"), "127.0.0.1");

	CU_ASSERT_TRUE_FATAL(config_has_property(config, "PORT"));
	CU_ASSERT_EQUAL_FATAL(config_get_int_value(config, "PORT"), 8080);

	CU_ASSERT_TRUE_FATAL(config_has_property(config, "LOAD"));
	CU_ASSERT_EQUAL_FATAL(config_get_double_value(config, "LOAD"), 0.5);

	config_destroy(config);
}

/**********************************************************************************************
 *  							Building the test for CUnit
 *********************************************************************************************/

static CU_TestInfo tests[] = {
		{ "Test read config", test_read_config },
		CU_TEST_INFO_NULL };

CUNIT_MAKE_SUITE(config, "Test Config TAD", init_suite, clean_suite, tests)

