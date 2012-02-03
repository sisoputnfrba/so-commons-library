/*
 * log.c
 *
 *  Created on: Feb 3, 2012
 *      Author: Prieto, Gaston
 */

#include "log.h"

#include "string_operations.h"
#include "temporal.h"
#include "error_operations.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <pthread.h>


#ifndef LOG_MAX_LENGTH_MESSAGE
#define LOG_MAX_LENGTH_MESSAGE 1024
#endif

#define LOG_MAX_LENGTH_BUFFER LOG_MAX_LENGTH_MESSAGE + 100
#define LOG_ENUM_SIZE 5

char *enum_names[LOG_ENUM_SIZE] = {"TRACE", "DEBUG", "INFO", "WARNING", "ERROR"};

/**
 * Private Functions
 */
void log_write_in_level(t_logger logger, t_log_level level, const char* message_template, va_list arguments);
bool isEnableLevelInLogger(t_logger logger, t_log_level level);
bool isEnableConsole(t_logger logger);

/**
 * Public Functions
 */

t_logger log_create(char* file, t_string program_name, t_console_mode console_mode, t_log_level detail) {
	t_logger logger = malloc(sizeof(t_log_object));

	if (logger == NULL) {
		perror("Cannot create logger");
		return NULL;
	}

	FILE *file_opened = fopen(file, "a");

	if (file_opened == NULL) {
		perror("Cannot create/open log file");
		free(logger);
		return NULL;
	}

	logger->file = file_opened;
	logger->mode = console_mode;
	logger->detail = detail;
	logger->pid = getpid();
	logger->program_name = string_new(program_name);
	return logger;
}

void log_destroy(t_logger logger) {
	free(logger->program_name);
	free(logger);
}

void log_trace(t_logger logger, const char* message_template, ...) {
	va_list arguments;
	va_start(arguments, message_template);
	log_write_in_level(logger, TRACE, message_template, arguments);
	va_end(arguments);
}

void log_debug(t_logger logger, const char* message_template, ...) {
	va_list arguments;
	va_start(arguments, message_template);
	log_write_in_level(logger, DEBUG, message_template, arguments);
	va_end(arguments);
}

void log_info(t_logger logger, const char* message_template, ...) {
	va_list arguments;
	va_start(arguments, message_template);
	log_write_in_level(logger, INFO, message_template, arguments);
	va_end(arguments);
}

void log_warning(t_logger logger, const char* message_template, ...) {
	va_list arguments;
	va_start(arguments, message_template);
	log_write_in_level(logger, WARNING, message_template, arguments);
	va_end(arguments);
}

void log_error(t_logger logger, const char* message_template, ...) {
	va_list arguments;
	va_start(arguments, message_template);
	log_write_in_level(logger, ERROR, message_template, arguments);
	va_end(arguments);
}

void log_write_in_level(t_logger logger, t_log_level level, const char* message_template, va_list list_arguments) {

	if (isEnableLevelInLogger(logger, level)) {
		t_string message, time;
		unsigned int thread_id;

		message = malloc(LOG_MAX_LENGTH_MESSAGE + 1);
		vsprintf(message, message_template, list_arguments);
		time = temporal_get_string_time();
		thread_id = pthread_self();

		t_string buffer = malloc(LOG_MAX_LENGTH_BUFFER + 1);
		sprintf(buffer, "%s %s/%d:%d [%s]: %s\n",
				time, logger->program_name, logger->pid, thread_id,
				log_level_as_string(logger->detail), message);

		fprintf(logger->file, "%s", buffer);
		fflush(logger->file);
		if (isEnableConsole(logger)) {
			printf("%s", buffer);
			fflush(stdout);
		}
	}
}

t_string log_level_as_string(t_log_level level) {
	return enum_names[level];
}

t_log_level log_level_from_string(t_string level) {
	int i;

	for (i = 0; i < LOG_ENUM_SIZE; i++) {
		if (string_equals_ignore_case(level, enum_names[i])){
			return i;
		}
	}

	error_show("Invalid value level (%s) to map a enum", level);

	return -1;
}


bool isEnableConsole(t_logger logger) {
	return logger->mode == ACTIVE;
}

bool isEnableLevelInLogger(t_logger logger, t_log_level level) {
	return level >= logger->detail;
}
