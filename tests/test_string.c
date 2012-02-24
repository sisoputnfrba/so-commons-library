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
#include <commons/string.h>

#include <CUnit/CUnit.h>
#include "cunit_tools.h"

static int init_suite(){
	return 0;
}

static int clean_suite(){
	return 0;
}

static void test_string_new() {
	t_string string = string_new();

	CU_ASSERT_PTR_NOT_NULL(string);
	CU_ASSERT_STRING_EQUAL(string, "");

	string_destroy(string);
}

static void test_string_append() {
	t_string string = string_new();
	string_append(&string, "Hello");
	string_append(&string, " ");
	string_append(&string, "world");

	CU_ASSERT_STRING_EQUAL(string, "Hello world");

	string_destroy(string);
}

static void test_string_equals_ignore_case() {
	t_string string = string_duplicate("Hello WorLd");

	CU_ASSERT_TRUE(string_equals_ignore_case(string, "hello world"));

	string_destroy(string);
}

static void test_string_duplicate() {
	t_string string = string_duplicate("Hello World!!");

	CU_ASSERT_STRING_EQUAL(string, "Hello World!!");
	CU_ASSERT_PTR_NOT_EQUAL(string, "Hello World!!");

	string_destroy(string);
}

static void test_string_repeat() {
	t_string string = string_repeat('a', 10);

	CU_ASSERT_STRING_EQUAL(string, "aaaaaaaaaa");
	CU_ASSERT_EQUAL(strlen(string), 10);

	string_destroy(string);
}

static void test_string_to_upper() {
	t_string string = string_duplicate("Hello World");
	string_to_upper(string);

	CU_ASSERT_STRING_EQUAL(string, "HELLO WORLD");

	string_destroy(string);
}

static void test_string_to_lower() {
	t_string string = string_duplicate("Hello World");
	string_to_lower(string);

	CU_ASSERT_STRING_EQUAL(string, "hello world");

	string_destroy(string);
}

static void test_string_capitalized() {
	t_string string;

	string = string_duplicate("hello world");
	string_capitalized(string);
	CU_ASSERT_STRING_EQUAL(string, "Hello world");
	string_destroy(string);

	string = string_duplicate("HELLO WORLD");
	string_capitalized(string);
	CU_ASSERT_STRING_EQUAL(string, "Hello world");
	string_destroy(string);

	string = string_duplicate("hi");
	string_capitalized(string);
	CU_ASSERT_STRING_EQUAL(string, "Hi");
	string_destroy(string);

	string = string_duplicate("h");
	string_capitalized(string);
	CU_ASSERT_STRING_EQUAL(string, "H");
	string_destroy(string);
}


static void test_string_trim_left() {
	t_string string;

	string = string_duplicate("Hola");
	string_trim_left(&string);
	CU_ASSERT_STRING_EQUAL(string, "Hola");
	string_destroy(string);

	string = string_duplicate("   Hola");
	string_trim_left(&string);
	CU_ASSERT_STRING_EQUAL(string, "Hola");
	string_destroy(string);
}

static void test_string_trim_right() {
	t_string string;

	string = string_duplicate("Hola");
	string_trim_right(&string);
	CU_ASSERT_STRING_EQUAL(string, "Hola");
	string_destroy(string);

	string = string_duplicate("Hola    ");
	string_trim_right(&string);
	CU_ASSERT_STRING_EQUAL(string, "Hola");
	string_destroy(string);
}

static void test_string_trim() {
	t_string string;

	string = string_duplicate("Hola");
	string_trim(&string);
	CU_ASSERT_STRING_EQUAL(string, "Hola");
	string_destroy(string);

	string = string_duplicate("    Hola");
	string_trim(&string);
	CU_ASSERT_STRING_EQUAL(string, "Hola");
	string_destroy(string);

	string = string_duplicate("Hola    ");
	string_trim(&string);
	CU_ASSERT_STRING_EQUAL(string, "Hola");
	string_destroy(string);

	string = string_duplicate("    Hola    ");
	string_trim(&string);
	CU_ASSERT_STRING_EQUAL(string, "Hola");
	string_destroy(string);
}

static void test_string_is_empty() {
	t_string string = string_new();
	CU_ASSERT_TRUE(string_is_empty(string));
	string_destroy(string);
}

static void test_string_length() {
	t_string string = string_new();
	CU_ASSERT_EQUAL(string_length(string), 0);

	string_append(&string, "HOLA");
	CU_ASSERT_EQUAL(string_length(string), 4);

	string_destroy(string);
}

static void test_string_split() {
	t_string line = "Hola planeta tierra";
	t_string* substrings = string_split(line, " ");

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

static void test_string_begin_with() {
	CU_ASSERT_TRUE(string_begin_with("#Comentario", "#"));
	CU_ASSERT_TRUE(string_begin_with("Comentario", "Comen"));
	CU_ASSERT_FALSE(string_begin_with("Comentario", "comen"));
	CU_ASSERT_FALSE(string_begin_with("Comentario", "lala"));
	CU_ASSERT_FALSE(string_begin_with("", "#"));
}


/**********************************************************************************************
 *  							Building the test for CUnit
 *********************************************************************************************/

static CU_TestInfo tests[] = {
		{ "Test create a new String", test_string_new },
		{ "Test append string to other string", test_string_append},
		{ "Test a create string with repetitions", test_string_repeat},
		{ "Test equals ignore case", test_string_equals_ignore_case},
		{ "Test duplicate string", test_string_duplicate},
		{ "Test to upper", test_string_to_upper},
		{ "Test to lower string", test_string_to_lower},
		{ "Test capitalized string", test_string_capitalized},
		{ "Test trim left", test_string_trim_left},
		{ "Test trim right", test_string_trim_right},
		{ "Test trim", test_string_trim},
		{ "Test isEmpty a string", test_string_is_empty},
		{ "Test length a string", test_string_length},
		{ "Test split a string", test_string_split},
		{ "Test string begin with", test_string_begin_with},
		CU_TEST_INFO_NULL,
};

CUNIT_MAKE_SUITE(string, "Test String ADT", init_suite, clean_suite, tests)
