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
