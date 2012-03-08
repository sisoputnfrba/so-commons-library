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

	char 	*string_utils_repeat(char ch, int count);
	void 	string_utils_append(char ** original, char * string_utils_to_add);

	void 	string_utils_to_upper(char * text);
	void 	string_utils_to_lower(char * text);
	void 	string_utils_capitalized(char * text);
	void 	string_utils_trim(char ** text);
	void 	string_utils_trim_left(char ** text);
	void 	string_utils_trim_right(char ** text);

	int 	string_utils_length(char * text);
	bool 	string_utils_is_empty(char * text);
	bool 	string_utils_starts_with(char * text, char * begin);
	bool 	string_utils_equals_ignore_case(char * actual, char * expected);
	char 	**string_utils_split(char * text, char * regex);

	void 	string_utils_iterate_lines(char ** strings, void (*closure)(char *));

#endif /* STRING_UTILS_H_ */
