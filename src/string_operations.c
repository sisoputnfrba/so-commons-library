/*
 * string_operations.c
 *
 *  Created on: Feb 3, 2012
 *      Author: Prieto, Gaston
 */

#include "string_operations.h"

#include <stdlib.h>
#include <string.h>

t_string string_new(char* original_string) {
	t_string string = calloc(1, strlen(original_string) + 1);
	strcpy(string, original_string);
	return string;
}

void string_append(t_string* original, t_string string_to_add) {
	*original = realloc(*original, strlen(*original) + strlen(string_to_add) + 1);
	strcat(*original, string_to_add);
}

bool string_equals_ignore_case(t_string actual, t_string expected) {
	return strcasecmp(actual, expected);
}

void string_destroy(t_string string) {
	free(string);
}
