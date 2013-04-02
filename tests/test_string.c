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

static void test_string_from_format(){
	char* newString = string_from_format("%s %s %d", "Hello", "world", 23);
	CU_ASSERT_STRING_EQUAL(newString, "Hello world 23");
	free(newString);
}

static void test_string_append() {
	char *string = string_new();
	string_append(&string, "Hello");
	string_append(&string, " ");
	string_append(&string, "world");

	CU_ASSERT_STRING_EQUAL(string, "Hello world");

	free(string);
}

static void test_string_append_with_format() {
	char *string = string_new();

	string_append_with_format(&string, "%s %s %d", "Hello", "world", 23);
	CU_ASSERT_STRING_EQUAL(string, "Hello world 23");

	free(string);
}

static void test_string_equals_ignore_case() {
	char *string = string_duplicate("Hello WorLd");

	CU_ASSERT_TRUE(string_equals_ignore_case(string, "hello world"));

	free(string);
}

static void test_string_repeat() {
	char *string = string_repeat('a', 10);

	CU_ASSERT_STRING_EQUAL(string, "aaaaaaaaaa");
	CU_ASSERT_EQUAL(strlen(string), 10);

	free(string);
}

static void test_string_to_upper() {
	char *string = string_duplicate("Hello World");
	string_to_upper(string);

	CU_ASSERT_STRING_EQUAL(string, "HELLO WORLD");

	free(string);
}

static void test_string_to_lower() {
	char *string = string_duplicate("Hello World");
	string_to_lower(string);

	CU_ASSERT_STRING_EQUAL(string, "hello world");

	free(string);
}

static void test_string_capitalized() {
	char *string;

	string = string_duplicate("hello world");
	string_capitalized(string);
	CU_ASSERT_STRING_EQUAL(string, "Hello world");
	free(string);

	string = string_duplicate("HELLO WORLD");
	string_capitalized(string);
	CU_ASSERT_STRING_EQUAL(string, "Hello world");
	free(string);

	string = string_duplicate("hi");
	string_capitalized(string);
	CU_ASSERT_STRING_EQUAL(string, "Hi");
	free(string);

	string = string_duplicate("h");
	string_capitalized(string);
	CU_ASSERT_STRING_EQUAL(string, "H");
	free(string);
}


static void test_string_trim_left() {
	char *string;

	string = string_duplicate("Hola");
	string_trim_left(&string);
	CU_ASSERT_STRING_EQUAL(string, "Hola");
	free(string);

	string = string_duplicate("   Hola");
	string_trim_left(&string);
	CU_ASSERT_STRING_EQUAL(string, "Hola");
	free(string);
}

static void test_string_trim_right() {
	char *string;

	string = string_duplicate("Hola");
	string_trim_right(&string);
	CU_ASSERT_STRING_EQUAL(string, "Hola");
	free(string);

	string = string_duplicate("Hola    ");
	string_trim_right(&string);
	CU_ASSERT_STRING_EQUAL(string, "Hola");
	free(string);
}

static void test_string_trim() {
	char *string;

	string = string_duplicate("Hola");
	string_trim(&string);
	CU_ASSERT_STRING_EQUAL(string, "Hola");
	free(string);

	string = string_duplicate("    Hola");
	string_trim(&string);
	CU_ASSERT_STRING_EQUAL(string, "Hola");
	free(string);

	string = string_duplicate("Hola    ");
	string_trim(&string);
	CU_ASSERT_STRING_EQUAL(string, "Hola");
	free(string);

	string = string_duplicate("    Hola    ");
	string_trim(&string);
	CU_ASSERT_STRING_EQUAL(string, "Hola");
	free(string);
}

static void test_string_is_empty() {
	char *string = string_new();
	CU_ASSERT_TRUE(string_is_empty(string));
	free(string);
}

static void test_string_split() {
	char *line = "Hola planeta tierra";
	char** substrings = string_split(line, " ");

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

static void test_string_starts_with() {
	CU_ASSERT_TRUE(string_starts_with("#Comentario", "#"));
	CU_ASSERT_TRUE(string_starts_with("Comentario", "Comen"));
	CU_ASSERT_FALSE(string_starts_with("Comentario", "comen"));
	CU_ASSERT_FALSE(string_starts_with("Comentario", "lala"));
	CU_ASSERT_FALSE(string_starts_with("", "#"));
}

static void test_string_ends_with() {
	CU_ASSERT_TRUE(string_ends_with("MiArchivo.txt", "txt"));
	CU_ASSERT_TRUE(string_ends_with("MiArchivo.txt", "MiArchivo.txt"));
	CU_ASSERT_FALSE(string_ends_with("MiArchivo.doc", "txt"));
	CU_ASSERT_FALSE(string_ends_with("MiDoc", "txt"));
	CU_ASSERT_FALSE(string_ends_with("", "txt"));
}

static void test_string_substring_empty() {
	char* original_word = "";
	char* substring = string_substring(original_word, 3);
	CU_ASSERT_STRING_EQUAL(substring, original_word);
	CU_ASSERT_PTR_NOT_EQUAL(substring, original_word);
	free(substring);
}

static void test_string_substring_with_short_string() {
	char* original_word = "hola";
	char* substring = string_substring(original_word, 14);
	CU_ASSERT_STRING_EQUAL(substring, original_word);
	CU_ASSERT_PTR_NOT_EQUAL(substring, original_word);
	free(substring);
}

static void test_string_substring_with_large_string() {
	char* original_word = "hola mundo c!";
	char* substring = string_substring(original_word, 4);
	CU_ASSERT_STRING_EQUAL(substring, "hola");
	CU_ASSERT_PTR_NOT_EQUAL(substring, original_word);
	free(substring);
}

static void test_string_substring_with_equal_large() {
	char* original_word = "hola";
	char* substring = string_substring(original_word, 4);
	CU_ASSERT_STRING_EQUAL(substring, original_word);
	CU_ASSERT_PTR_NOT_EQUAL(substring, original_word);
	free(substring);
}

/**********************************************************************************************
 *  							Building the test for CUnit
 *********************************************************************************************/

static CU_TestInfo tests[] = {
		{ "Test create string from a format", test_string_from_format},
		{ "Test append string to other string", test_string_append},
		{ "Test append string to other string with a format specified", test_string_append_with_format},
		{ "Test a create string with repetitions", test_string_repeat},
		{ "Test equals ignore case", test_string_equals_ignore_case},
		{ "Test to upper", test_string_to_upper},
		{ "Test to lower string", test_string_to_lower},
		{ "Test capitalized string", test_string_capitalized},
		{ "Test trim left", test_string_trim_left},
		{ "Test trim right", test_string_trim_right},
		{ "Test trim", test_string_trim},
		{ "Test isEmpty a string", test_string_is_empty},
		{ "Test split a string", test_string_split},
		{ "Test string begin with", test_string_starts_with},
		{ "Test string ends with", test_string_ends_with},
		{ "Test string substring with a empty string", test_string_substring_empty},
		{ "Test string substring with a short string", test_string_substring_with_short_string},
		{ "Test string substring with a large string", test_string_substring_with_large_string},
		{ "Test string substring with a equal size", test_string_substring_with_equal_large},
		CU_TEST_INFO_NULL,
};

CUNIT_MAKE_SUITE(string, "Test String ADT", init_suite, clean_suite, tests)
