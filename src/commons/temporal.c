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
#include "temporal.h"
#include "error.h"
#include "string.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h>
#include <string.h>

char *temporal_get_string_time(const char* format) {
	char* str_time = malloc(strlen(format) + 1);
	char* strftime_format = strdup(format);
	struct tm *log_tm = malloc(sizeof(struct tm));

	//time
	time_t log_time = time(NULL);
	if(log_time == -1) {
		error_show("Error getting time!");
		return NULL;
	}

	//miliseconds
	struct timeb tmili;
	if(ftime(&tmili)) {
		error_show("Error getting miliseconds!");
		return NULL;
	}

	//parse
	char* aux = strftime_format;
	while((aux = strstr(aux, "%MS"))) {
		sprintf(aux, "%03hu", tmili.millitm);
		strftime_format[strlen(strftime_format)] = format[strlen(strftime_format)];
		aux = aux + 3;
	}

	localtime_r(&log_time, log_tm);
	strftime(str_time, strlen(format)+1, strftime_format, log_tm);

	free(log_tm);
	free(strftime_format);

	return str_time;
}
