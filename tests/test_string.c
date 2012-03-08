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
	t_string *string = string_new(NULL);

	CU_ASSERT_PTR_NOT_NULL(string);
	CU_ASSERT_STRING_EQUAL(string->str, "");

	string_destroy(string);
}

static void test_string_append() {
	t_string *string = string_new("Hello ");
	t_string *word_str = string_new("world");

	string_append(string, word_str);

	CU_ASSERT_STRING_EQUAL(string->str, "Hello world");

	string_destroy(word_str);
	string_destroy(string);
}

static void test_string_append_literal() {
	t_string *string = string_new(NULL);

	string_append_literal(string, "Hello");
	string_append_literal(string, " ");
	string_append_literal(string, "world");

	CU_ASSERT_STRING_EQUAL(string->str, "Hello world");

	string_destroy(string);
}

static void test_string_equals_ignore_case() {
	t_string *string1 = string_new("Hello WorLd");
	t_string *string2 = string_new("hello world");

	CU_ASSERT_TRUE(string_equals_ignore_case(string1, string2));

	string_destroy(string1);
	string_destroy(string2);
}

static void test_string_equals_literal_ignore_case() {
	t_string *string = string_new("Hello WorLd");

	CU_ASSERT_TRUE(string_equals_literal_ignore_case(string, "hello world"));

	string_destroy(string);
}

static void test_string_duplicate() {
	t_string *string = string_new("Hello World!!");

	CU_ASSERT_STRING_EQUAL(string->str, "Hello World!!");
	CU_ASSERT_PTR_NOT_EQUAL(string->str, "Hello World!!");

	string_destroy(string);
}

static void test_string_to_upper() {
	t_string *string = string_new("Hello World");
	string_to_upper(string);

	CU_ASSERT_STRING_EQUAL(string->str, "HELLO WORLD");

	string_destroy(string);
}

static void test_string_to_lower() {
	t_string *string = string_new("Hello World");
	string_to_lower(string);

	CU_ASSERT_STRING_EQUAL(string->str, "hello world");

	string_destroy(string);
}

static void test_string_capitalized() {
	t_string *string;

	string = string_new("hello world");
	string_capitalized(string);
	CU_ASSERT_STRING_EQUAL(string->str, "Hello world");
	string_destroy(string);

	string = string_new("HELLO WORLD");
	string_capitalized(string);
	CU_ASSERT_STRING_EQUAL(string->str, "Hello world");
	string_destroy(string);

	string = string_new("hi");
	string_capitalized(string);
	CU_ASSERT_STRING_EQUAL(string->str, "Hi");
	string_destroy(string);

	string = string_new("h");
	string_capitalized(string);
	CU_ASSERT_STRING_EQUAL(string->str, "H");
	string_destroy(string);
}


static void test_string_trim_left() {
	t_string *string;

	string = string_new("Hola");
	string_trim_left(string);
	CU_ASSERT_STRING_EQUAL(string->str, "Hola");
	string_destroy(string);

	string = string_new("   Hola");
	string_trim_left(string);
	CU_ASSERT_STRING_EQUAL(string->str, "Hola");
	string_destroy(string);
}

static void test_string_trim_right() {
	t_string *string;

	string = string_new("Hola");
	string_trim_right(string);
	CU_ASSERT_STRING_EQUAL(string->str, "Hola");
	string_destroy(string);

	string = string_new("Hola    ");
	string_trim_right(string);
	CU_ASSERT_STRING_EQUAL(string->str, "Hola");
	string_destroy(string);
}

static void test_string_trim() {
	t_string *string;

	string = string_new("Hola");
	string_trim(string);
	CU_ASSERT_STRING_EQUAL(string->str, "Hola");
	string_destroy(string);

	string = string_new("    Hola");
	string_trim(string);
	CU_ASSERT_STRING_EQUAL(string->str, "Hola");
	string_destroy(string);

	string = string_new("Hola    ");
	string_trim(string);
	CU_ASSERT_STRING_EQUAL(string->str, "Hola");
	string_destroy(string);

	string = string_new("    Hola    ");
	string_trim(string);
	CU_ASSERT_STRING_EQUAL(string->str, "Hola");
	string_destroy(string);
}

static void test_string_is_empty() {
	t_string *string = string_new(NULL);
	CU_ASSERT_TRUE(string_is_empty(string));
	string_destroy(string);
}

static void test_string_length() {
	t_string *string = string_new(NULL);
	CU_ASSERT_EQUAL(string_length(string), 0);

	string_append_literal(string, "HOLA");
	CU_ASSERT_EQUAL(string_length(string), 4);

	string_destroy(string);
}

static void test_string_split() {
	t_string *line = string_new("Hola planeta tierra");
	t_string *delimitor = string_new(" ");
	t_string **substrings = string_split(line, delimitor);

	CU_ASSERT_PTR_NOT_NULL(substrings);
	CU_ASSERT_STRING_EQUAL(substrings[0]->str, "Hola");
	CU_ASSERT_STRING_EQUAL(substrings[1]->str, "planeta");
	CU_ASSERT_STRING_EQUAL(substrings[2]->str, "tierra");
	CU_ASSERT_PTR_NULL(substrings[3]);

	string_destroy(substrings[0]);
	string_destroy(substrings[1]);
	string_destroy(substrings[2]);
	free(substrings);

	string_destroy(line);
	string_destroy(delimitor);
}

static void test_string_starts_with() {
	t_string *string1;
	t_string *string2;

	string1 = string_new("#Comentario");
	string2 = string_new("#");
	CU_ASSERT_TRUE(string_starts_with(string1, string2));
	string_destroy(string1);
	string_destroy(string2);

	string1 = string_new("Comentario");
	string2 = string_new("Comen");
	CU_ASSERT_TRUE(string_starts_with(string1, string2));
	string_destroy(string1);
	string_destroy(string2);

	string1 = string_new("Comentario");
	string2 = string_new("comen");
	CU_ASSERT_FALSE(string_starts_with(string1, string2));
	string_destroy(string1);
	string_destroy(string2);

	string1 = string_new(NULL);
	string2 = string_new("#");
	CU_ASSERT_FALSE(string_starts_with(string1, string2));
	string_destroy(string1);
	string_destroy(string2);
}

static void test_string_starts_with_literal() {
	t_string *string;

	string = string_new("#Comentario");
	CU_ASSERT_TRUE(string_starts_with_literal(string, "#"));
	string_destroy(string);

	string = string_new("Comentario");
	CU_ASSERT_TRUE(string_starts_with_literal(string, "Comen"));
	string_destroy(string);

	string = string_new("Comentario");
	CU_ASSERT_FALSE(string_starts_with_literal(string, "comen"));
	string_destroy(string);

	string = string_new(NULL);
	CU_ASSERT_FALSE(string_starts_with_literal(string, "#"));
	string_destroy(string);
}


/**********************************************************************************************
 *  							Building the test for CUnit
 *********************************************************************************************/

static CU_TestInfo tests[] = {
		{ "Test create a new String", test_string_new },
		{ "Test append string to other string", test_string_append},
		{ "Test append string literal to other string", test_string_append_literal},
		{ "Test equals ignore case", test_string_equals_ignore_case},
		{ "Test equals literal ignore case", test_string_equals_literal_ignore_case},
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
		{ "Test string begin with", test_string_starts_with},
		{ "Test string begin with literal", test_string_starts_with_literal},
		CU_TEST_INFO_NULL,
};

CUNIT_MAKE_SUITE(string, "Test String ADT", init_suite, clean_suite, tests)
