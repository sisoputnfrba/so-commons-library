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

	char 	*string_repeat(char ch, int count);
	void 	string_append(char ** original, char * string_to_add);
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
	char 	**string_split(char * text, char * separator);

	void 	string_iterate_lines(char ** strings, void (*closure)(char *));

#endif /* STRING_H_ */
