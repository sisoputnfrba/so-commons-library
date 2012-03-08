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

	typedef struct {
		char *str;
		int	len;
	} t_string;

	t_string 	*string_new(char *original_text);
	void 		string_destroy(t_string *string);

	t_string 	*string_duplicate(t_string*);

	void 		string_append(t_string*, t_string *string_to_add);
	void 		string_append_literal(t_string* , char *string_to_add);

	void 		string_to_upper(t_string *);
	void 		string_to_lower(t_string *);
	void 		string_capitalized(t_string *);
	void 		string_trim(t_string *);
	void 		string_trim_left(t_string *);
	void 		string_trim_right(t_string *);

	int 		string_length(t_string *);
	bool 		string_is_empty(t_string *);
	bool 		string_starts_with(t_string *, t_string *begin);
	bool 		string_starts_with_literal(t_string *, char *begin);
	bool 		string_equals_ignore_case(t_string *, t_string *expected);
	bool 		string_equals_literal_ignore_case(t_string *, char *expected);
	t_string** 	string_split(t_string *text, t_string *regex);

	void 		string_iterate_lines(t_string** strings, void (*closure)(t_string*));

#endif /* STRING_H_ */
