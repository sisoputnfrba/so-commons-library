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

	typedef struct {
		t_list* elements;
	} t_queue;

	/**
	* @fn    queue_create
	* @brief Crea y devuelve un puntero a una cola
	*/
	t_queue *queue_create();

	/**
	* @fn    queue_destroy
	* @brief Destruye una cola.
	*/
	void queue_destroy(t_queue *);

	/**
	* @fn    queue_destroy_and_destroy_elements
	* @brief Destruye una cola, recibiendo como argumento el metodo encargado de
	*        liberar cada elemento de la cola.
	*/
	void queue_destroy_and_destroy_elements(t_queue*, void(*element_destroyer)(void*));

	/**
	* @fn    queue_push
	* @brief Agrega un elemento al final de la cola
	*/
	void queue_push(t_queue *, void *element);

	/**
	* @fn    queue_pop
	* @brief quita el primer elemento de la cola
	*/
	void *queue_pop(t_queue *);

	/**
	* @fn    queue_peek
	* @brief Devuelve el primer elemento de la cola sin extraerlo
	*/
	void *queue_peek(t_queue *);

	/**
	* @fn    queue_clean
	* @brief Elimina todos los elementos de la cola.
	*/
	void queue_clean(t_queue *);

	/**
	* @fn    queue_clean_and_destroy_elements
	* @brief Elimina y destruye todos los elementos de la cola.
	*/
	void queue_clean_and_destroy_elements(t_queue *, void(*element_destroyer)(void*));

	/**
	* @fn    queue_size
	* @brief Devuelve la cantidad de elementos de la cola
	*/
	int queue_size(t_queue *);

	/**
	* @fn    queue_is_empty
	* @brief Verifica si la cola esta vacía
	*/
	bool queue_is_empty(t_queue *);

#endif /*QUEUE_H_*/
