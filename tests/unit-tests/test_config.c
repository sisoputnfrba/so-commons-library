/*
 * Copyright (C) 2012 Sistemas Operativos - UTN FRBA. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <commons/config.h>
#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <commons/string.h>

#include "cunit_tools.h"


#define KEYS_AMOUNT 6
#define PATH_CONFIG "resources/config.cfg"

static int init_suite() {
	return 0;
}

static int clean_suite() {
	return 0;
}

static void _assert_equals_array(char** expected, char** actual, int size) {
	int i;
	for (i = 0; i < size; i++) {
		CU_ASSERT_STRING_EQUAL(actual[i], expected[i]);
	}
	CU_ASSERT_PTR_NULL(actual[i]);
}

static void test_read_config() {
	t_config* config = config_create(PATH_CONFIG);

	CU_ASSERT_EQUAL(config_keys_amount(config), KEYS_AMOUNT);

	CU_ASSERT_TRUE(config_has_property(config, "IP"));
	CU_ASSERT_STRING_EQUAL(config_get_string_value(config, "IP"), "127.0.0.1");

	CU_ASSERT_TRUE(config_has_property(config, "PORT"));
	CU_ASSERT_EQUAL(config_get_int_value(config, "PORT"), 8080);

	CU_ASSERT_TRUE(config_has_property(config, "LOAD"));
	CU_ASSERT_EQUAL(config_get_double_value(config, "LOAD"), 0.5);
	
	config_destroy(config);
}

void test_read_empty_array() {
	char* empty_array_expected[] = {NULL};
	t_config* config = config_create(PATH_CONFIG);

	CU_ASSERT_EQUAL(config_keys_amount(config), KEYS_AMOUNT);

	CU_ASSERT_TRUE(config_has_property(config, "EMPTY_ARRAY"));
	CU_ASSERT_STRING_EQUAL(config_get_string_value(config, "EMPTY_ARRAY"), "[]");

	char** empty_array  = config_get_array_value(config, "EMPTY_ARRAY");
	_assert_equals_array(empty_array_expected, empty_array, 0);

	free(empty_array);
	config_destroy(config);
}

void test_read_full_array() {
	char* numbers_expected[] = {"1", "2", "3", "4", "5", NULL};
	t_config* config = config_create(PATH_CONFIG);

	CU_ASSERT_EQUAL(config_keys_amount(config), KEYS_AMOUNT);

	CU_ASSERT_TRUE(config_has_property(config, "NUMBERS"));
	CU_ASSERT_STRING_EQUAL(config_get_string_value(config, "NUMBERS"), "[1, 2, 3, 4, 5]");

	char** numbers = config_get_array_value(config, "NUMBERS");
	_assert_equals_array(numbers_expected, numbers, 5);

	string_iterate_lines(numbers, (void*) free);
	free(numbers);
	config_destroy(config);
}

/**********************************************************************************************
 *  							Building the test for CUnit
 *********************************************************************************************/

static CU_TestInfo tests[] = {
		{ "Test read config", test_read_config },
		{ "Test read config - with empty array", test_read_empty_array },
		{ "Test read config - array with values", test_read_full_array },
		CU_TEST_INFO_NULL };

CUNIT_MAKE_SUITE(config, "Test Config TAD", init_suite, clean_suite, tests)

