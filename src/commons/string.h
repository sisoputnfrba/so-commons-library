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
void string_append(t_string* original, t_string string_to_add);
bool string_equals_ignore_case(t_string actual, t_string expected);

#endif /* STRING_OPERATIONS_H_ */
