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
#ifndef LOG_H_
#define LOG_H_

	#include <stdio.h>
	#include <stdbool.h>
	#include <sys/types.h>


	typedef enum {
		LOG_LEVEL_TRACE,
		LOG_LEVEL_DEBUG,
		LOG_LEVEL_INFO,
		LOG_LEVEL_WARNING,
		LOG_LEVEL_ERROR
	}t_log_level;

	typedef struct {
		FILE* file;
		bool is_active_console;
		t_log_level detail;
		char *program_name;
		pid_t pid;
	}t_log;

	/**
	* @NAME: log_create
	* @DESC: Crea una instancia de logger, tomando por parametro
	* el nombre del programa, el nombre del archivo donde se van a generar los logs,
	* el nivel de detalle minimo a loguear y si además se muestra por pantalla lo que se loguea.
	*/
	t_log* 		log_create(char* file, char *program_name, bool is_active_console, t_log_level level);

	/**
	* @NAME: log_destroy
	* @DESC: Destruye una instancia de logger
	*/
	void 		log_destroy(t_log* logger);

	/**
	* @NAME: log_trace
	* @DESC: Loguea un mensaje con el siguiente formato
	*
	* [TRACE] hh:mm:ss:mmmm PROCESS_NAME/(PID:TID): MESSAGE
	*
	*/
	void 		log_trace(t_log* logger, const char* message, ...);

	/**
	* @NAME: log_debug
	* @DESC: Loguea un mensaje con el siguiente formato
	*
	* [DEBUG] hh:mm:ss:mmmm PROCESS_NAME/(PID:TID): MESSAGE
	*
	*/
	void 		log_debug(t_log* logger, const char* message, ...);

	/**
	* @NAME: log_info
	* @DESC: Loguea un mensaje con el siguiente formato
	*
	* [INFO] hh:mm:ss:mmmm PROCESS_NAME/(PID:TID): MESSAGE
	*
	*/
	void 		log_info(t_log* logger, const char* message, ...);

	/**
	* @NAME: log_warning
	* @DESC: Loguea un mensaje con el siguiente formato
	*
	* [WARNING] hh:mm:ss:mmmm PROCESS_NAME/(PID:TID): MESSAGE
	*
	*/
	void 		log_warning(t_log* logger, const char* message, ...);

	/**
	* @NAME: log_error
	* @DESC: Loguea un mensaje con el siguiente formato
	*
	* [ERROR] hh:mm:ss:mmmm PROCESS_NAME/(PID:TID): MESSAGE
	*
	*/
	void 		log_error(t_log* logger, const char* message, ...);

	/**
	* @NAME: log_level_as_string
	* @DESC: Convierte un t_log_level a su representacion en string
	*/
	char 		*log_level_as_string(t_log_level level);

	/**
	* @NAME: log_level_from_string
	* @DESC: Convierte un string a su representacion en t_log_level
	*/
	t_log_level log_level_from_string(char *level);

#endif /* LOG_H_ */
