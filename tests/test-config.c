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
	t_dictionary* config = config_read_from_file("resources/config.cfg");

	CU_ASSERT_PTR_NOT_NULL_FATAL(dictionary_get(config, "IP"));
	CU_ASSERT_STRING_EQUAL(dictionary_get(config, "IP"), "127.0.0.1");

	CU_ASSERT_PTR_NOT_NULL_FATAL(dictionary_get(config, "PORT"));
	CU_ASSERT_STRING_EQUAL(dictionary_get(config, "PORT"), "8080");

	CU_ASSERT_PTR_NOT_NULL_FATAL(dictionary_get(config, "PROCESS_NAME"));
	CU_ASSERT_STRING_EQUAL(dictionary_get(config, "PROCESS_NAME"), "TEST");

	dictionary_destroy(config);
}

void test_write_config() {
	t_dictionary* config = dictionary_create(NULL);
	dictionary_put(config, string_duplicate("IP"), "192.168.1.1");
	dictionary_put(config, string_duplicate("PORT"), "25");
	dictionary_put(config, string_duplicate("PATH"), "/home/gaston");

	config_write_in_file("resources/write.cfg", config);
	dictionary_destroy(config);
}

/**********************************************************************************************
 *  							Building the test for CUnit
 *********************************************************************************************/

static CU_TestInfo tests[] = {
		{ "Test read config", test_read_config },
		{ "Test write config", test_write_config },
		CU_TEST_INFO_NULL };

CUNIT_MAKE_SUITE(config, "Test Dictionary TAD", init_suite, clean_suite, tests)

