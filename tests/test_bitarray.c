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

#include <commons/bitarray.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/CUnit.h>

#include "cunit_tools.h"

static int init_suite() {
	return 0;
}

static int clean_suite() {
	return 0;
}

void test_get_bit_value_bitarray() {
	char data[] = { 0b10000000, 0, 0b00000001 };
	t_bitarray *bitarray = bitarray_create(data, sizeof(data));


	CU_ASSERT_TRUE( bitarray_test_bit(bitarray, 7) );
	CU_ASSERT_FALSE( bitarray_test_bit(bitarray, 1) );
	CU_ASSERT_TRUE( bitarray_test_bit(bitarray, 8 + 8 + 0) );

	bitarray_destroy(bitarray);
}

void test_clean_bitarray() {
	char BASE_ARRAY[] = { 0, 0, 0 };
	char data[] = { 0, 0, 0b00000001 };
	t_bitarray *bitarray = bitarray_create(data, sizeof(data));

	bitarray_clean_bit(bitarray, 8 + 8 + 0);

	CU_ASSERT_EQUAL( memcmp(BASE_ARRAY, data, sizeof(data)), 0);

	bitarray_destroy(bitarray);
}

void test_set_bitarray() {
	char BASE_ARRAY[] = { 0b10000000, 0, 0 };
	char data[] = { 0, 0, 0 };
	t_bitarray *bitarray = bitarray_create(data, sizeof(data));

	bitarray_set_bit(bitarray, 7);

	CU_ASSERT_EQUAL( memcmp(BASE_ARRAY, data, sizeof(data)), 0);

	bitarray_destroy(bitarray);
}

void test_get_max_bits_bitarray() {
	char data[] = { 0, 0, 0 };
	t_bitarray *bitarray = bitarray_create(data, sizeof(data));

	CU_ASSERT_EQUAL( bitarray_get_max_bit(bitarray), 8 * 3);

	bitarray_destroy(bitarray);
}

/**********************************************************************************************
 *  							Building the test for CUnit
 *********************************************************************************************/

static CU_TestInfo tests[] = {
		{ "Test get bit value in bitarray", test_get_bit_value_bitarray },
		{ "Test clean bitarray", test_clean_bitarray },
		{ "Test set bitarray", test_set_bitarray },
		{ "Test get max bits in bitarray", test_get_max_bits_bitarray },
		CU_TEST_INFO_NULL };

CUNIT_MAKE_SUITE(bitarray, "Test BitArray TAD", init_suite, clean_suite, tests)

