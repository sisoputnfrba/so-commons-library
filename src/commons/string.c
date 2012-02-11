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

static void string_do(t_string text, void (*closure)(char*));
static void string_lower_element(char* ch);
static void string_upper_element(char* ch);

t_string string_new() {
	return calloc(1, 1);
}

t_string string_duplicate(char* original_string) {
	return strdup(original_string);
}

t_string string_repeat(char character, int count) {
	t_string text = malloc(count + 1);
	int i = 0;
	for (i = 0; i < count; ++i) {
		text[i] = character;
	}
	return text;
}

void string_append(t_string* original, t_string string_to_add) {
	*original = realloc(*original, strlen(*original) + strlen(string_to_add) + 1);
	strcat(*original, string_to_add);
}


void string_to_upper(t_string text) {
	string_do(text, &string_upper_element);
}

void string_to_lower(t_string text) {
	string_do(text, &string_lower_element);
}

void string_capitalized(t_string text) {
	if (!string_is_empty(text)) {
		string_upper_element(text);
		if (string_length(text) >= 2){
			string_to_lower(&text[1]);
		}
	}
}

void string_trim(t_string* text) {
	string_trim_left(text);
	string_trim_right(text);
}

void string_trim_left(t_string* text) {
	t_string string_without_blank = *text;

	while (isblank(*string_without_blank)) {
		string_without_blank++;
	}

	t_string new_string = string_duplicate(string_without_blank);

	string_destroy(*text);
	*text = new_string;
}

void string_trim_right(t_string* text) {
	t_string string_without_blank = *text;
	int i = string_length(*text) - 1;
	while (i >= 0 && isspace(string_without_blank[i])){
		string_without_blank[i] = '\0';
		i--;
	}
	*text = realloc(*text, strlen(string_without_blank) + 1);
}

int string_length(t_string text) {
	return strlen(text);
}

bool string_is_empty(t_string text) {
	return string_length(text) == 0;
}

bool string_equals_ignore_case(t_string actual, t_string expected) {
	return strcasecmp(actual, expected) == 0;
}

void string_destroy(t_string string) {
	free(string);
}

static void string_upper_element(char* ch) {
	*ch = toupper(*ch);
}

static void string_lower_element(char* ch) {
	*ch = tolower(*ch);
}

static void string_do(t_string text, void (*closure)(char* c)){
	int i = 0;
	while (text[i] != '\0') {
		closure(&text[i]);
		i++;
	}
}
