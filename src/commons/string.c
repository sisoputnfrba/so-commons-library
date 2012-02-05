/*
 * string_operations.c
 *
 *  Created on: Feb 3, 2012
 *      Author: Prieto, Gaston
 */

#include "string.h"

#include <stdlib.h>
#include <string.h>

t_string string_new(){
	return calloc(1, 255 + 1);
}

t_string string_duplicate(char* original_string) {
	return strdup(original_string);
}

void string_append(t_string* original, t_string string_to_add) {
	*original = realloc(*original, strlen(*original) + strlen(string_to_add) + 1);
	strcat(*original, string_to_add);
}

bool string_equals_ignore_case(t_string actual, t_string expected) {
	return strcasecmp(actual, expected) == 0;
}

void string_destroy(t_string string) {
	free(string);
}
