/*
 * log.h
 *
 *  Created on: Feb 3, 2012
 *      Author: Prieto, Gaston
 */

#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>
#include <sys/types.h>
#include "string.h"


typedef enum {
	TRACE,
	DEBUG,
	INFO,
	WARNING,
	ERROR
}t_log_level;

typedef struct {
	FILE* file;
	bool is_active_console;
	t_log_level detail;
	t_string program_name;
	pid_t pid;
}t_log_object;

typedef t_log_object* t_logger;

t_logger log_create(char* file, t_string program_name, bool is_active_console, t_log_level level);
void log_destroy(t_logger logger);

void log_trace(t_logger logger, const char* message, ...);
void log_debug(t_logger logger, const char* message, ...);
void log_info(t_logger logger, const char* message, ...);
void log_warning(t_logger logger, const char* message, ...);
void log_error(t_logger logger, const char* message, ...);

t_string log_level_as_string(t_log_level level);
t_log_level log_level_from_string(t_string level);

#endif /* LOG_H_ */
