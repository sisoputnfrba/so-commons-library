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

#include "log.h"

#include "temporal.h"
#include "error.h"
#include "string.h"
#include "txt.h"
#include "process.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

#define LOG_ENUM_SIZE 5

static char *enum_names[LOG_ENUM_SIZE] = {"TRACE", "DEBUG", "INFO", "WARNING", "ERROR"};

/**
 * Private Functions
 */
static void _log_write_in_level(t_log* logger, t_log_level level, const char* message_template, va_list arguments);
static bool _isEnableLevelInLogger(t_log* logger, t_log_level level);

#define log_impl_template(log_function, level_enum) 									\
		void log_function(t_log* logger, const char* message_template, ...) { 			\
			va_list arguments;															\
			va_start(arguments, message_template);										\
			_log_write_in_level(logger, level_enum, message_template, arguments);		\
			va_end(arguments);															\
		}																				\

/**
 * Public Functions
 */


t_log* log_create(char* file, char *program_name, bool is_active_console, t_log_level detail) {
	t_log* logger = malloc(sizeof(t_log));

	if (logger == NULL) {
		perror("Cannot create logger");
		return NULL;
	}

	FILE *file_opened = NULL;

	if (file != NULL) {
		file_opened = txt_open_for_append(file);

		if (file_opened == NULL) {
			perror("Cannot create/open log file");
			free(logger);
			return NULL;
		}
	}

	logger->file = file_opened;
	logger->is_active_console = is_active_console;
	logger->detail = detail;
	logger->pid = process_getpid();
	logger->program_name = string_duplicate(program_name);
	return logger;
}

void log_destroy(t_log* logger) {
	free(logger->program_name);
	txt_close_file(logger->file);
	free(logger);
}

log_impl_template(log_trace, LOG_LEVEL_TRACE);

log_impl_template(log_debug, LOG_LEVEL_DEBUG);

log_impl_template(log_info, LOG_LEVEL_INFO);

log_impl_template(log_warning, LOG_LEVEL_WARNING);

log_impl_template(log_error, LOG_LEVEL_ERROR);

char *log_level_as_string(t_log_level level) {
	return enum_names[level];
}

t_log_level log_level_from_string(char *level) {
	int i;

	for (i = 0; i < LOG_ENUM_SIZE; i++) {
		if (string_equals_ignore_case(level, enum_names[i])){
			return i;
		}
	}

	return -1;
}

/** PRIVATE FUNCTIONS **/

static void _log_write_in_level(t_log* logger, t_log_level level, const char* message_template, va_list list_arguments) {

	if (_isEnableLevelInLogger(logger, level)) {
		char *message, *time, *buffer;
		unsigned int thread_id;

                message = string_from_vformat(message_template, list_arguments);
		time = temporal_get_string_time();
		thread_id = process_get_thread_id();

		buffer = string_from_format("[%s] %s %s/(%d:%d): %s\n",
                                log_level_as_string(level),
                                time,
                                logger->program_name,
				logger->pid,
                                thread_id,
                                message);

		if (logger->file != NULL) {
			txt_write_in_file(logger->file, buffer);
		}

		if (logger->is_active_console) {
			txt_write_in_stdout(buffer);
		}

		free(time);
		free(message);
		free(buffer);
	}
}

static bool _isEnableLevelInLogger(t_log* logger, t_log_level level) {
	return level >= logger->detail;
}
