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

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <commons/string_utils.h>

#include <CUnit/CUnit.h>
#include "cunit_tools.h"

static int init_suite(){
	return 0;
}

static int clean_suite(){
	return 0;
}

static void test_string_utils_append() {
	char *string = strdup("");
	string_utils_append(&string, "Hello");
	string_utils_append(&string, " ");
	string_utils_append(&string, "world");

	CU_ASSERT_STRING_EQUAL(string, "Hello world");

	free(string);
}

static void test_string_utils_equals_ignore_case() {
	char *string = strdup("Hello WorLd");

	CU_ASSERT_TRUE(string_utils_equals_ignore_case(string, "hello world"));

	free(string);
}

static void test_string_utils_repeat() {
	char *string = string_utils_repeat('a', 10);

	CU_ASSERT_STRING_EQUAL(string, "aaaaaaaaaa");
	CU_ASSERT_EQUAL(strlen(string), 10);

	free(string);
}

static void test_string_utils_to_upper() {
	char *string = strdup("Hello World");
	string_utils_to_upper(string);

	CU_ASSERT_STRING_EQUAL(string, "HELLO WORLD");

	free(string);
}

static void test_string_utils_to_lower() {
	char *string = strdup("Hello World");
	string_utils_to_lower(string);

	CU_ASSERT_STRING_EQUAL(string, "hello world");

	free(string);
}

static void test_string_utils_capitalized() {
	char *string;

	string = strdup("hello world");
	string_utils_capitalized(string);
	CU_ASSERT_STRING_EQUAL(string, "Hello world");
	free(string);

	string = strdup("HELLO WORLD");
	string_utils_capitalized(string);
	CU_ASSERT_STRING_EQUAL(string, "Hello world");
	free(string);

	string = strdup("hi");
	string_utils_capitalized(string);
	CU_ASSERT_STRING_EQUAL(string, "Hi");
	free(string);

	string = strdup("h");
	string_utils_capitalized(string);
	CU_ASSERT_STRING_EQUAL(string, "H");
	free(string);
}


static void test_string_utils_trim_left() {
	char *string;

	string = strdup("Hola");
	string_utils_trim_left(&string);
	CU_ASSERT_STRING_EQUAL(string, "Hola");
	free(string);

	string = strdup("   Hola");
	string_utils_trim_left(&string);
	CU_ASSERT_STRING_EQUAL(string, "Hola");
	free(string);
}

static void test_string_utils_trim_right() {
	char *string;

	string = strdup("Hola");
	string_utils_trim_right(&string);
	CU_ASSERT_STRING_EQUAL(string, "Hola");
	free(string);

	string = strdup("Hola    ");
	string_utils_trim_right(&string);
	CU_ASSERT_STRING_EQUAL(string, "Hola");
	free(string);
}

static void test_string_utils_trim() {
	char *string;

	string = strdup("Hola");
	string_utils_trim(&string);
	CU_ASSERT_STRING_EQUAL(string, "Hola");
	free(string);

	string = strdup("    Hola");
	string_utils_trim(&string);
	CU_ASSERT_STRING_EQUAL(string, "Hola");
	free(string);

	string = strdup("Hola    ");
	string_utils_trim(&string);
	CU_ASSERT_STRING_EQUAL(string, "Hola");
	free(string);

	string = strdup("    Hola    ");
	string_utils_trim(&string);
	CU_ASSERT_STRING_EQUAL(string, "Hola");
	free(string);
}

static void test_string_utils_is_empty() {
	char *string = strdup("");
	CU_ASSERT_TRUE(string_utils_is_empty(string));
	free(string);
}

static void test_string_utils_split() {
	char *line = "Hola planeta tierra";
	char** substrings = string_utils_split(line, " ");

	CU_ASSERT_PTR_NOT_NULL(substrings);
	CU_ASSERT_STRING_EQUAL(substrings[0], "Hola");
	CU_ASSERT_STRING_EQUAL(substrings[1], "planeta");
	CU_ASSERT_STRING_EQUAL(substrings[2], "tierra");
	CU_ASSERT_PTR_NULL(substrings[3]);

	free(substrings[0]);
	free(substrings[1]);
	free(substrings[2]);
	free(substrings);
}

static void test_string_utils_starts_with() {
	CU_ASSERT_TRUE(string_utils_starts_with("#Comentario", "#"));
	CU_ASSERT_TRUE(string_utils_starts_with("Comentario", "Comen"));
	CU_ASSERT_FALSE(string_utils_starts_with("Comentario", "comen"));
	CU_ASSERT_FALSE(string_utils_starts_with("Comentario", "lala"));
	CU_ASSERT_FALSE(string_utils_starts_with("", "#"));
}


/**********************************************************************************************
 *  							Building the test for CUnit
 *********************************************************************************************/

static CU_TestInfo tests[] = {
		{ "Test append string to other string", test_string_utils_append},
		{ "Test a create string with repetitions", test_string_utils_repeat},
		{ "Test equals ignore case", test_string_utils_equals_ignore_case},
		{ "Test to upper", test_string_utils_to_upper},
		{ "Test to lower string", test_string_utils_to_lower},
		{ "Test capitalized string", test_string_utils_capitalized},
		{ "Test trim left", test_string_utils_trim_left},
		{ "Test trim right", test_string_utils_trim_right},
		{ "Test trim", test_string_utils_trim},
		{ "Test isEmpty a string", test_string_utils_is_empty},
		{ "Test split a string", test_string_utils_split},
		{ "Test string begin with", test_string_utils_starts_with},
		CU_TEST_INFO_NULL,
};

CUNIT_MAKE_SUITE(string_utils, "Test String Utils ADT", init_suite, clean_suite, tests)
