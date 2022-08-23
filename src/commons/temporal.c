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

#include <unistd.h>
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
	milisec = string_from_format("%03ld", log_timespec->tv_nsec / 1000000);

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

t_temporal* temporal_create(void) {
    t_temporal* self = malloc(sizeof(t_temporal));
    struct timespec* current = malloc(sizeof(struct timespec));
    
    self -> elapsed_ms = 0;
    self -> state = RUNNING;
    self -> current = current;
    
    clock_gettime(CLOCK_MONOTONIC_RAW, current);
    
    return self;
}

void temporal_destroy(t_temporal* temporal) {
    if (temporal -> current) {
		free(temporal -> current);
	}

    free(temporal);
}

int64_t temporal_gettime(t_temporal* temporal) {
    if (temporal -> state == STOPPED) {
        return temporal -> elapsed_ms;
    }

    t_temporal* now = temporal_create();

    int64_t delta_ms = (now -> current -> tv_sec - temporal -> current -> tv_sec) * 1000 
                        + (now -> current -> tv_nsec - temporal -> current -> tv_nsec) / 1000000;
    
    temporal_destroy(now);

    return delta_ms + temporal -> elapsed_ms;
}

int64_t temporal_gettime_since_running(t_temporal* temporal) {
	if (temporal -> state == STOPPED) {
        return 0;
    }

    t_temporal* now = temporal_create();

    int64_t delta_ms = (now -> current -> tv_sec - temporal -> current -> tv_sec) * 1000 
                        + (now -> current -> tv_nsec - temporal -> current -> tv_nsec) / 1000000;
    
    temporal_destroy(now);

    return delta_ms;
}

void temporal_stop(t_temporal* temporal) {
    temporal -> elapsed_ms += temporal_gettime_since_running(temporal);
    temporal -> state = STOPPED;
    
    free(temporal -> current);
    temporal -> current = NULL;
}

void temporal_resume(t_temporal* temporal) {
    if (temporal -> state == RUNNING) {
        return;
    }
    
    temporal -> state = RUNNING;
    temporal -> current = malloc(sizeof(struct timespec));
    
    clock_gettime(CLOCK_MONOTONIC_RAW, temporal -> current);
}

int64_t temporal_diff(t_temporal* start, t_temporal* end) {
    return temporal_gettime(start) - temporal_gettime(end);
}
