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

#include "cunit_tools.h"

static int init_suite() {
	return 0;
}

static int clean_suite() {
	return 0;
}

void test_read_config() {
	t_config* config = config_create("/home/gaston/commons-library/tests/resources/config.cfg");

	CU_ASSERT_EQUAL(config_keys_amount(config), 4);

	CU_ASSERT_TRUE(config_has_property(config, "IP"));
	CU_ASSERT_STRING_EQUAL(config_get_string_value(config, "IP"), "127.0.0.1");

	CU_ASSERT_TRUE(config_has_property(config, "PORT"));
	CU_ASSERT_EQUAL(config_get_int_value(config, "PORT"), 8080);

	CU_ASSERT_TRUE(config_has_property(config, "LOAD"));
	CU_ASSERT_EQUAL(config_get_double_value(config, "LOAD"), 0.5);

	config_destroy(config);
}

/**********************************************************************************************
 *  							Building the test for CUnit
 *********************************************************************************************/

static CU_TestInfo tests[] = {
		{ "Test read config", test_read_config },
		CU_TEST_INFO_NULL };

CUNIT_MAKE_SUITE(config, "Test Config TAD", init_suite, clean_suite, tests)

