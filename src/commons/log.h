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
		LOG_LEVEL_TRACE, //!< Loguea todos los mensajes
		LOG_LEVEL_DEBUG, //!< Loguea solo mensajes de log_debug en adelante
		LOG_LEVEL_INFO, //!< Loguea solo mensajes de log_info en adelante
		LOG_LEVEL_WARNING, //!< Loguea solo mensajes de log_warning en adelante
		LOG_LEVEL_ERROR //!< Loguea solo mensajes de log_error
	} t_log_level;

	/**
	 * @struct t_log
	 * @brief  Manejo de logs
	 */
	typedef struct {
		FILE* file;
		bool is_active_console;
		t_log_level detail;
		char *program_name;
		pid_t pid;
	}t_log;

	/**
	 * @brief   Crea una instancia de logger
	 * @relates t_log
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
	 * @return Retorna una instancia de logger, o NULL en caso de error
	 */
	t_log* 		log_create(char* file, char *process_name, bool is_active_console, t_log_level level);

	/**
	* @brief   Destruye una instancia de logger
	* @relates t_log
	*/
	void 		log_destroy(t_log* logger);

	/**
	* @brief   Loguea un mensaje con el siguiente formato
	* @relates t_log
	*        [TRACE] hh:mm:ss:mmmm PROCESS_NAME/(PID:TID): MESSAGE
	*
	*/
	void 		log_trace(t_log* logger, const char* message, ...) __attribute__((format(printf, 2, 3)));

	/**
	* @brief   Loguea un mensaje con el siguiente formato
	* @relates t_log
	*        [DEBUG] hh:mm:ss:mmmm PROCESS_NAME/(PID:TID): MESSAGE
	*
	*/
	void 		log_debug(t_log* logger, const char* message, ...) __attribute__((format(printf, 2, 3)));

	/**
	* @brief   Loguea un mensaje con el siguiente formato
	* @relates t_log
	*        [INFO] hh:mm:ss:mmmm PROCESS_NAME/(PID:TID): MESSAGE
	*
	*/
	void 		log_info(t_log* logger, const char* message, ...) __attribute__((format(printf, 2, 3)));

	/**
	* @brief   Loguea un mensaje con el siguiente formato
	* @relates t_log
	*        [WARNING] hh:mm:ss:mmmm PROCESS_NAME/(PID:TID): MESSAGE
	*
	*/
	void 		log_warning(t_log* logger, const char* message, ...) __attribute__((format(printf, 2, 3)));

	/**
	* @brief   Loguea un mensaje con el siguiente formato
	* @relates t_log
	*        [ERROR] hh:mm:ss:mmmm PROCESS_NAME/(PID:TID): MESSAGE
	*
	*/
	void 		log_error(t_log* logger, const char* message, ...) __attribute__((format(printf, 2, 3)));

	/**
	* @brief   Convierte un t_log_level a su representacion en string
	* @relates t_log
	*/
	char 		*log_level_as_string(t_log_level level);

	/**
	* @brief   Convierte un string a su representacion en t_log_level
	* @relates t_log
	*/
	t_log_level log_level_from_string(char *level);

#endif /* LOG_H_ */
