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
#ifndef TEMPORAL_H_
#define TEMPORAL_H_

	#include <stdint.h>
	#include <time.h>

	/**
	* @brief Estado de una variable temporal.
	*/
	typedef enum {
		TEMPORAL_STATUS_STOPPED,
		TEMPORAL_STATUS_RUNNING
	} t_temporal_status;

	/**
	* @brief Estructura de una Variable temporal.
	*/
	typedef struct {
		struct timespec current;
		int64_t elapsed_ms;
		t_temporal_status status;
	} t_temporal;

	/**
	* @fn    temporal_get_string_time
	* @brief Retorna un string con la hora actual, con el formato recibido por
	*        parámetro.
	*
	* @example
	* @code
	* temporal_get_string_time("%d/%m/%y") => "30/09/20"
	* temporal_get_string_time("%H:%M:%S:%MS") => "12:51:59:331"
	* temporal_get_string_time("%d/%m/%y %H:%M:%S") => "30/09/20 12:51:59"
	* @endcode
	*/
	char *temporal_get_string_time(const char* format);

	/**
	* @fn    temporal_create
	* @brief Crea una variable temporal e inicia su cronómetro.
	*/
	t_temporal* temporal_create(void);

	/**
	* @fn    temporal_destroy
	* @brief Destruye una variable temporal.
	*
	* @param temporal Variable temporal a destruir.
	*/
	void temporal_destroy(t_temporal* temporal);

	/**
	* @fn    temporal_gettime
	* @brief Retorna el tiempo total transcurrido mientras el cronómetro estuvo
	*        activo en milisegundos.
	*
	* @param temporal Variable temporal.
	*/
	int64_t temporal_gettime(t_temporal* temporal);

	/**
	* @fn    temporal_stop
	* @brief Detiene el cronómetro de una variable temporal.
	*
	* @param temporal Variable temporal a frenar.
	*/
	void temporal_stop(t_temporal* temporal);

	/**
	* @fn    temporal_resume
	* @brief Reanuda el cronómetro de una variable temporal.
	*
	* @param temporal Variable temporal a reanudar.
	*/
	void temporal_resume(t_temporal* temporal);

	/**
	* @fn    temporal_diff
	* @brief Retorna la diferencia del tiempo total transcurrido entre dos
	*        variables temporales en milisegundos
	*
	* @param temporal_1 Primera variable temporal.
	* @param temporal_2 Segunda variable temporal.
	*/
	int64_t temporal_diff(t_temporal* temporal_1, t_temporal* temporal_2);
	
#endif /* TEMPORAL_H_ */
