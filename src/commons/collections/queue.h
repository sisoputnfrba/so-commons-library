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

#ifndef QUEUE_H_
#define QUEUE_H_

	#include "list.h"

	/**
	 * @file
	 * @brief `#include <commons/collections/queue.h>`
	 */

	/**
	 * @struct t_queue
	 * @brief Estructura que representa una cola. Inicializar con `queue_create()`
	 */
	typedef struct {
		t_list* elements;
	} t_queue;

	/**
	* @brief Crea una cola
	* @return Retorna un puntero a la cola creada, liberable con:
 *         - `queue_destroy()` si se quiere liberar la cola pero no
 *           los elementos que contiene.
 *         - `queue_destroy_and_destroy_elements()` si se quiere liberar
 *           la cola con los elementos que contiene.
	*/
	t_queue *queue_create(void);

	/**
	* @brief Destruye una cola sin liberar los elementos que contiene
	*/
	void queue_destroy(t_queue *);

	/**
	* @brief Destruye una cola, recibiendo como argumento el metodo encargado de
	*        liberar cada elemento de la cola.
	*/
	void queue_destroy_and_destroy_elements(t_queue*, void(*element_destroyer)(void*));

	/**
	* @brief Agrega un elemento al final de la cola
	* @param element Elemento a agregar. Este elemento pasará a pertenecer
	*                a la cola, por lo que no debe ser liberado por fuera de ésta.
	*/
	void queue_push(t_queue *, void *element);

	/**
	* @brief quita el primer elemento de la cola
	* @return El elemento extraído de la cola. Este elemento debe ser liberado
	*         una vez que se deje de usar.
	*/
	void *queue_pop(t_queue *);

	/**
	* @brief Devuelve el primer elemento de la cola sin extraerlo
	* @return El primer elemento de la cola. Este elemento no debe ser liberado
	*         ya que seguirá perteneciendo a la cola.
	*/
	void *queue_peek(t_queue *);

	/**
	* @brief Quita todos los elementos de la cola sin liberarlos
	*/
	void queue_clean(t_queue *);

	/**
	* @brief Quita y libera todos los elementos de la cola.
	*/
	void queue_clean_and_destroy_elements(t_queue *, void(*element_destroyer)(void*));

	/**
	* @brief Devuelve la cantidad de elementos de la cola
	*/
	int queue_size(t_queue *);

	/**
	* @brief Verifica si la cola esta vacía
	*/
	bool queue_is_empty(t_queue *);

#endif /*QUEUE_H_*/
