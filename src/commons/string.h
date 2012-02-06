/*
 * string_operations.h
 *
 *  Created on: Feb 3, 2012
 *      Author: Prieto, Gaston
 */

#ifndef STRING_OPERATIONS_H_
#define STRING_OPERATIONS_H_

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
bool string_equals_ignore_case(t_string actual, t_string expected);

#endif /* STRING_OPERATIONS_H_ */
