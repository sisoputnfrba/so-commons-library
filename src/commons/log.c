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


#define LOG_ENUM_SIZE 5

static char *enum_names[LOG_ENUM_SIZE] = {"TRACE", "DEBUG", "INFO", "WARNING", "ERROR"};
static char *log_colors[LOG_ENUM_SIZE] = {"\x1b[36m", "\x1b[32m", "", "\x1b[33m", "\x1b[31m" };
static char *reset_color = "\x1b[0m";

/**
 * Private Functions
 */
static void _log_write_in_level(t_log* logger, t_log_level level, const char* message_template, va_list arguments);
static bool _is_level_enabled(t_log* logger, t_log_level level);

/**
 * Public Functions
 */


t_log* log_create(char* file, char *program_name, bool is_active_console, t_log_level detail) {
	t_log* logger = malloc(sizeof(t_log));

	if (logger == NULL) {
		error_show("Cannot create logger");
		return NULL;
	}

	FILE *file_opened = NULL;

	if (file != NULL) {
		if (!string_ends_with(file, ".log")) {
			error_show("Log file must have .log extension");
			free(logger);
			return NULL;
		}
		file_opened = txt_open_for_append(file);

		if (file_opened == NULL) {
			error_show("Cannot create/open log file");
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

void log_trace(t_log* logger, const char* message_template, ...) {
	va_list arguments;
	va_start(arguments, message_template);
	_log_write_in_level(logger, LOG_LEVEL_TRACE, message_template, arguments);
	va_end(arguments);
}

void log_debug(t_log* logger, const char* message_template, ...) {
	va_list arguments;
	va_start(arguments, message_template);
	_log_write_in_level(logger, LOG_LEVEL_DEBUG, message_template, arguments);
	va_end(arguments);
}

void log_info(t_log* logger, const char* message_template, ...) {
	va_list arguments;
	va_start(arguments, message_template);
	_log_write_in_level(logger, LOG_LEVEL_INFO, message_template, arguments);
	va_end(arguments);
}

void log_warning(t_log* logger, const char* message_template, ...) {
	va_list arguments;
	va_start(arguments, message_template);
	_log_write_in_level(logger, LOG_LEVEL_WARNING, message_template, arguments);
	va_end(arguments);
}

void log_error(t_log* logger, const char* message_template, ...) {
	va_list arguments;
	va_start(arguments, message_template);
	_log_write_in_level(logger, LOG_LEVEL_ERROR, message_template, arguments);
	va_end(arguments);
}

char *log_level_as_string(t_log_level level) {
	return enum_names[level];
}

char *log_level_color(t_log_level level) {
	return log_colors[level];
}

t_log_level log_level_from_string(char *level) {
	for (int i = 0; i < LOG_ENUM_SIZE; i++) {
		if (string_equals_ignore_case(level, enum_names[i])){
			return i;
		}
	}

	return -1;
}

/** PRIVATE FUNCTIONS **/

static void _log_write_in_level(t_log* logger, t_log_level level, const char* message_template, va_list list_arguments) {
	if (!_is_level_enabled(logger, level)) {
		return;
	}

	char *message = string_from_vformat(message_template, list_arguments);
	char *time = temporal_get_string_time("%H:%M:%S:%MS");
	unsigned int thread_id = process_get_thread_id();

	char *buffer = string_from_format("[%s] %s %s/(%d:%d): %s\n",
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
		char *console_buffer = string_from_format("%s%s%s",
			log_level_color(level),
			buffer,
			reset_color);
		txt_write_in_stdout(console_buffer);
		free(console_buffer);
	}

	free(time);
	free(message);
	free(buffer);
}

static bool _is_level_enabled(t_log* logger, t_log_level level) {
	return level >= logger->detail;
}
