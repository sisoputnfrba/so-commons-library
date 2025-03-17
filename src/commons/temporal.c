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
#include <string.h>

static int64_t calculate_delta_ms(t_temporal* temporal);

char *temporal_get_string_time(const char* format) {
	char* str_time = strdup(format);

	struct timespec log_timespec;
	struct tm log_tm;
	char* milisec;

	if (clock_gettime(CLOCK_REALTIME, &log_timespec) == -1) {
		error_show("Error getting date!");
		free(str_time);
		return NULL;
	}
	milisec = string_from_format("%03ld", log_timespec.tv_nsec / 1000000);

	for (char* ms = strstr(str_time, "%MS"); ms != NULL; ms = strstr(ms + 3, "%MS")) {
		memcpy(ms, milisec, 3);
	}

	localtime_r(&log_timespec.tv_sec, &log_tm);
	strftime(str_time, strlen(format) + 1, str_time, &log_tm);

	free(milisec);

	return str_time;
}

t_temporal* temporal_create(void) {
	t_temporal* self = malloc(sizeof(t_temporal));

	self->elapsed_ms = 0;
	self->status = TEMPORAL_STATUS_RUNNING;

	if (clock_gettime(CLOCK_MONOTONIC_RAW, &self->current) == -1) {
		error_show("Error getting time!");
		free(self);
		return NULL;
	}

	return self;
}

void temporal_destroy(t_temporal* temporal) {
	free(temporal);
}

int64_t temporal_gettime(t_temporal* temporal) {
	if (temporal->status == TEMPORAL_STATUS_STOPPED) {
		return temporal->elapsed_ms;
	}

	int64_t delta_ms = calculate_delta_ms(temporal);

	return delta_ms + temporal->elapsed_ms;
}

void temporal_stop(t_temporal* temporal) {
	if (temporal->status == TEMPORAL_STATUS_STOPPED) {
		return;
	}

	temporal->elapsed_ms += calculate_delta_ms(temporal);
	temporal->status = TEMPORAL_STATUS_STOPPED;
}

void temporal_resume(t_temporal* temporal) {
	if (temporal->status == TEMPORAL_STATUS_RUNNING) {
		return;
	}

	temporal->status = TEMPORAL_STATUS_RUNNING;

	if (clock_gettime(CLOCK_MONOTONIC_RAW, &temporal->current) == -1) {
		error_show("Error getting time!");
	}
}

int64_t temporal_diff(t_temporal* temporal_1, t_temporal* temporal_2) {
	return temporal_gettime(temporal_1) - temporal_gettime(temporal_2);
}

static int64_t calculate_delta_ms(t_temporal* temporal) {
	struct timespec now;
	if (clock_gettime(CLOCK_MONOTONIC_RAW, &now) == -1) {
		error_show("Error getting time!");
		return 0;
	}

	return (now.tv_sec - temporal->current.tv_sec) * 1000
		+ (now.tv_nsec - temporal->current.tv_nsec) / 1000000;
}
