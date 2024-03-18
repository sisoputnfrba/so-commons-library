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
	 * @fn    log_create
	 * @brief Crea una instancia de logger
	 *
	 * @param file              La ruta hacia el archivo donde se van a generar los logs
	 * @param process_name      El nombre a ser mostrado en los logs
	 * @param is_active_console Si lo que se loguea debe mostrarse por consola
	 * @param level             El nivel de detalle mínimo a loguear (ver definición de t_log_level)
	 *
	 * @note si file ya existe, se escribirá al final del archivo
	 * @note si file no existe, se creará un nuevo archivo en el directorio indicado
	 * @note si el directorio hacia file no existe, se producirá un error
	 *
	 * @example si level es LOG_LEVEL_INFO, se loguearán los mensajes de nivel INFO, WARNING y ERROR
	 *          y se ignorarán los mensajes de nivel DEBUG y TRACE
	 *
	 * @return Retorna una instancia de logger, o NULL en caso de error
	 */
	t_log* 		log_create(char* file, char *process_name, bool is_active_console, t_log_level level);

	/**
	* @fn    log_destroy
	* @brief Destruye una instancia de logger
	*/
	void 		log_destroy(t_log* logger);

	/**
	* @fn    log_trace
	* @brief Loguea un mensaje con el siguiente formato
	*        [TRACE] hh:mm:ss:mmmm PROCESS_NAME/(PID:TID): MESSAGE
	*
	*/
	void 		log_trace(t_log* logger, const char* message, ...) __attribute__((format(printf, 2, 3)));

	/**
	* @fn    log_debug
	* @brief Loguea un mensaje con el siguiente formato
	*        [DEBUG] hh:mm:ss:mmmm PROCESS_NAME/(PID:TID): MESSAGE
	*
	*/
	void 		log_debug(t_log* logger, const char* message, ...) __attribute__((format(printf, 2, 3)));

	/**
	* @fn    log_info
	* @brief Loguea un mensaje con el siguiente formato
	*        [INFO] hh:mm:ss:mmmm PROCESS_NAME/(PID:TID): MESSAGE
	*
	*/
	void 		log_info(t_log* logger, const char* message, ...) __attribute__((format(printf, 2, 3)));

	/**
	* @fn    log_warning
	* @brief Loguea un mensaje con el siguiente formato
	*        [WARNING] hh:mm:ss:mmmm PROCESS_NAME/(PID:TID): MESSAGE
	*
	*/
	void 		log_warning(t_log* logger, const char* message, ...) __attribute__((format(printf, 2, 3)));

	/**
	* @fn    log_error
	* @brief Loguea un mensaje con el siguiente formato
	*        [ERROR] hh:mm:ss:mmmm PROCESS_NAME/(PID:TID): MESSAGE
	*
	*/
	void 		log_error(t_log* logger, const char* message, ...) __attribute__((format(printf, 2, 3)));

	/**
	* @fn    log_level_as_string
	* @brief Convierte un t_log_level a su representacion en string
	*/
	char 		*log_level_as_string(t_log_level level);

	/**
	* @fn    log_level_from_string
	* @brief Convierte un string a su representacion en t_log_level
	*/
	t_log_level log_level_from_string(char *level);

#endif /* LOG_H_ */
