/*
 * error_operations.c
 *
 *  Created on: Feb 3, 2012
 *      Author: Prieto, Gaston
 */


#include "error.h"

#include <stdarg.h>
#include <stdio.h>

void error_show(t_string message, ...) {
	va_list arguments;
	va_start(arguments, message);

	t_string error_message = string_duplicate("[[ERROR]]");
	string_append(&error_message, message);

	vprintf(error_message, arguments);
	
	string_destroy(error_message);
	va_end(arguments);
}
