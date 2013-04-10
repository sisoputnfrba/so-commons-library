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

#ifndef STRING_UTILS_H_
#define STRING_UTILS_H_

	#include <stdbool.h>
	#include <stdarg.h>

	char*   string_new();
	char*   string_from_format(const char* format, ...);
        char*   string_from_vformat(const char* format, va_list arguments);
	char*   string_repeat(char ch, int count);
	void 	string_append(char ** original, char * string_to_add);
	void    string_append_with_format(char **original, const char *format, ...);
	char*	string_duplicate(char* original);

	void 	string_to_upper(char * text);
	void 	string_to_lower(char * text);
	void 	string_capitalized(char * text);
	void 	string_trim(char ** text);
	void 	string_trim_left(char ** text);
	void 	string_trim_right(char ** text);

	int 	string_length(char * text);
	bool 	string_is_empty(char * text);
	bool 	string_starts_with(char * text, char * begin);
	bool	string_ends_with(char* text, char* end);
	bool 	string_equals_ignore_case(char * actual, char * expected);
	char**  string_split(char * text, char * separator);
	char*   string_substring(char* text, int start, int length);
	char*   string_substring_from(char *text, int start);
	char*   string_substring_until(char *text, int length);


	void 	string_iterate_lines(char ** strings, void (*closure)(char *));
	char**  string_get_string_as_array(char* text);

#endif /* STRING_UTILS_H_ */
