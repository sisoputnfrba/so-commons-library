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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char *temporal_get_string_time(const char* format) {
	char* str_time = strdup(format);

	struct timespec* log_timespec = malloc(sizeof(struct timespec));
	struct tm* log_tm = malloc(sizeof(struct tm));
	char* milisec;

	if(clock_gettime(CLOCK_REALTIME, log_timespec) == -1) {
		return NULL;
	}
	milisec = string_from_format("%03d", log_timespec->tv_nsec / 1000000);

	for(char* ms = strstr(str_time, "%MS"); ms != NULL; ms = strstr(ms + 3, "%MS")) {
		memcpy(ms, milisec, 3);
	}

	localtime_r(&log_timespec->tv_sec, log_tm);
	strftime(str_time, strlen(format) + 1, str_time, log_tm);

	free(milisec);
	free(log_tm);
	free(log_timespec);

	return str_time;
}
