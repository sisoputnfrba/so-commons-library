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
#ifndef STRING_H_
#define STRING_H_

#include <stdbool.h>

typedef char* t_string;

t_string string_new();
void string_destroy(t_string string);

t_string string_duplicate(char *original_text);
t_string string_repeat(char ch, int count);
void string_append(t_string* original, t_string string_to_add);

void string_to_upper(t_string text);
void string_to_lower(t_string text);
void string_capitalized(t_string text);
void string_trim(t_string* text);
void string_trim_left(t_string* text);
void string_trim_right(t_string* text);

int string_length(t_string text);
bool string_is_empty(t_string text);
bool string_starts_with(t_string text, t_string begin);
bool string_equals_ignore_case(t_string actual, t_string expected);
t_string* string_split(t_string text, t_string regex);

void string_iterate_lines(t_string* strings, void (*closure)(t_string));

#endif /* STRING_H_ */
