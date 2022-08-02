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

#include "string.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdarg.h>

static void _string_do(char *text, void (*closure)(char*));
static void _string_lower_element(char* ch);
static void _string_upper_element(char* ch);
void _string_append_with_format_list(const char* format, char** original, va_list arguments);
char** _string_split(char* text, char* separator, bool(*is_last_token)(int));
static void _string_array_push(char*** array, char* text, int size);
static bool _string_match(char* text, char* pattern, char **where);

char *string_repeat(char character, int count) {
	char *text = calloc(count + 1, 1);
	int i = 0;
	for (i = 0; i < count; ++i) {
		text[i] = character;
	}
	return text;
}

char* string_duplicate(char* original) {
	return strdup(original);
}

void string_append(char** original, char* string_to_add) {
	*original = realloc(*original, strlen(*original) + strlen(string_to_add) + 1);
	strcat(*original, string_to_add);
}

void string_n_append(char** original, char* string_to_add, int n) {
	if(strlen(string_to_add) < n) {
		n = strlen(string_to_add);
	}
	*original = realloc(*original, strlen(*original) + n + 1);
	strncat(*original, string_to_add, n);
}

char* string_new() {
	return string_duplicate("");
}

char* string_from_format(const char* format, ...) {
	char* nuevo;
	va_list arguments;
	va_start(arguments, format);
	nuevo = string_from_vformat(format, arguments);
	va_end(arguments);
	return nuevo;
}

char* string_from_vformat(const char* format, va_list arguments) {
	char* nuevo = string_new();
	_string_append_with_format_list(format, &nuevo, arguments);
	return nuevo;
}

char* string_itoa(int number) {
	return string_from_format("%d", number);
}

void string_append_with_format(char **original, const char *format, ...) {
	va_list arguments;
	va_start(arguments, format);
	_string_append_with_format_list(format, original, arguments);
	va_end(arguments);
}

void string_to_upper(char *text) {
	_string_do(text, &_string_upper_element);
}

void string_to_lower(char *text) {
	_string_do(text, &_string_lower_element);
}

void string_capitalized(char *text) {
	if (!string_is_empty(text)) {
		_string_upper_element(text);
		if (strlen(text) >= 2){
			string_to_lower(&text[1]);
		}
	}
}

void string_trim(char** text) {
	string_trim_left(text);
	string_trim_right(text);
}

void string_trim_left(char** text) {
	char *string_without_blank = *text;

	while (isblank(*string_without_blank)) {
		string_without_blank++;
	}

	char *new_string = string_duplicate(string_without_blank);

	free(*text);
	*text = new_string;
}

void string_trim_right(char** text) {
	char *string_without_blank = *text;
	int i = strlen(*text) - 1;
	while (i >= 0 && isspace(string_without_blank[i])){
		string_without_blank[i] = '\0';
		i--;
	}
	*text = realloc(*text, strlen(string_without_blank) + 1);
}

bool string_is_empty(char *text) {
	return strlen(text) == 0;
}

bool string_starts_with(char *text, char *begin){
	return strncmp(text, begin, strlen(begin)) == 0;
}

bool string_ends_with(char* text, char* end) {
	if (strlen(text) < strlen(end)) {
		return false;
	}

	int index = strlen(text) - strlen(end);
	return strcmp(&text[index], end) == 0;
}

bool string_equals_ignore_case(char *actual, char *expected) {
	return strcasecmp(actual, expected) == 0;
}

char **string_split(char *text, char *separator) {
	bool _is_last_token(int _) {
		return false;
	}
	return _string_split(text, separator, _is_last_token);
}

char** string_n_split(char *text, int n, char* separator) {
	bool _is_last_token(int index) {
		return index == (n - 1);
	}
	return _string_split(text, separator, _is_last_token);
}

char**  string_get_string_as_array(char* text) {
	int length_value = strlen(text) - 2;
	if (length_value == 0) return calloc(1, sizeof(char*));

	char* value_without_brackets = string_substring(text, 1, length_value);
	char **array_values = string_split(value_without_brackets, ",");

	for (int i = 0; array_values[i] != NULL; i++) {
		string_trim(&(array_values[i]));
	}

	free(value_without_brackets);
	return array_values;
}

char* string_substring(char* text, int start, int length) {
	char* new_string = calloc(1, length + 1);
	strncpy(new_string, text + start, length);
	return new_string;
}

char *string_substring_from(char *text, int start) {
	return string_substring(text, start, strlen(text) - start);
}

char *string_substring_until(char *text, int length) {
	return string_substring(text, 0, length);
}

void string_iterate_lines(char** strings, void (*closure)(char*)) {
	while (*strings != NULL) {
		closure(*strings);
		strings++;
	}
}

int string_length(char* text) {
	return strlen(text);
}

char* string_reverse(char* palabra) {
	char* resultado = calloc(1, string_length(palabra) + 1);

	int i = string_length(palabra) - 1, j = 0;
	while (i >= 0){
	resultado[j] = palabra[i];
		i--;
		j++;
	}

	return resultado;
}

char* string_replace(char* text, char* substring, char* replacement) {
	char *result = string_new();

	char *start = text;
	char *end;

	while (_string_match(start, substring, &end)) {
		string_n_append(&result, start, end - start);
		string_append(&result, replacement);
		start = end + string_length(substring);
	}

	string_append(&result, start);
	return result;
}

bool string_contains(char* text, char *substring) {
	return strstr(text, substring) != NULL;
}

char** string_array_new() {
	char** array = malloc(sizeof(char*));
	array[0] = NULL;

	return array;
}

void string_array_destroy(char** array) {
	string_iterate_lines(array, (void*) free);
	free(array);
}

int string_array_size(char** array) {
	int size = 0;
	void _count_lines(char* _) {
		size++;
	}
	string_iterate_lines(array, _count_lines);

	return size;
}

bool string_array_is_empty(char** array) {
	return array[0] == NULL;
}

void string_array_push(char*** array, char* text) {
	_string_array_push(array, text, string_array_size(*array));
}

char* string_array_replace(char** array, int pos, char* text) {
	char* old_text = array[pos];
	array[pos] = text;

	return old_text;
}

char* string_array_pop(char** array) {
	return string_array_replace(array, string_array_size(array) - 1, NULL);
}

/** PRIVATE FUNCTIONS **/

static void _string_upper_element(char* ch) {
	*ch = toupper(*ch);
}

static void _string_lower_element(char* ch) {
	*ch = tolower(*ch);
}

static void _string_do(char *text, void (*closure)(char* c)){
	int i = 0;
	while (text[i] != '\0') {
		closure(&text[i]);
		i++;
	}
}


void _string_append_with_format_list(const char* format, char** original, va_list arguments) {
	va_list copy_arguments;
	va_copy(copy_arguments, arguments);
	size_t buffer_size = vsnprintf(NULL, 0, format, copy_arguments) + 1;
	va_end(copy_arguments);

	char* temporal = malloc(buffer_size);
	va_copy(copy_arguments, arguments);
	vsnprintf(temporal, buffer_size, format, copy_arguments);
	va_end(copy_arguments);
	string_append(original, temporal);
	free(temporal);
}

char** _string_split(char* text, char* separator, bool(*is_last_token)(int)) {
	char **substrings = string_array_new();
	int index = 0;

	char *start = text;
	char *end;

	while (_string_match(start, separator, &end) && !is_last_token(index)) {
		_string_array_push(&substrings, string_substring_until(start, end - start), index++);
		start = end + string_length(separator);
	}

	_string_array_push(&substrings, string_duplicate(start), index);
	return substrings;
}

static void _string_array_push(char*** array, char* text, int size) {
	*array = realloc(*array, sizeof(char*) * (size + 2));
	(*array)[size] = text;
	(*array)[size + 1] = NULL;
}

static bool _string_match(char* text, char* pattern, char **where) {
	if (string_is_empty(text) || pattern == NULL || !string_contains(text, pattern)) {
		return false;
	}

	*where = string_is_empty(pattern) ? text + 1 : strstr(text, pattern);
	return !string_is_empty(*where);
}
