/*
 * log.h
 *
 *  Created on: Feb 3, 2012
 *      Author: Prieto, Gaston
 */

#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>

typedef enum {
	ACTIVE,
	INACTIVE
}t_console_mode;

typedef enum {
	TRACE,
	DEBUG,
	INFO,
	WARNING,
	ERROR
}t_log_level;

typedef struct {
	FILE* file;
	t_console_mode mode;
	t_log_level detail;
}t_log;

t_log* log_create(char* file, t_console_mode console_mode, t_log_level detail);
void log_destroy(t_log* logger);

void log_trace(t_log* logger, const char* message, ...);
void log_debug(t_log* logger, const char* message, ...);
void log_info(t_log* logger, const char* message, ...);
void log_warning(t_log* logger, const char* message, ...);
void log_error(t_log* logger, const char* message, ...);


#endif /* LOG_H_ */
