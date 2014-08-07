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
	* @NAME: queue_create
	* @DESC: Crea y devuelve un puntero a una cola
	*/
	t_queue *queue_create();

	/**
	* @NAME: queue_destroy
	* @DESC: Destruye una cola.
	*/
	void queue_destroy(t_queue *);

	/**
	* @NAME: queue_destroy_and_destroy_elements
	* @DESC: Destruye una cola, recibiendo como argumento el metodo encargado de liberar cada
	* 		elemento de la cola.
	*/
	void queue_destroy_and_destroy_elements(t_queue*, void(*element_destroyer)(void*));

	/**
	* @NAME: queue_push
	* @DESC: Agrega un elemento al final de la cola
	*/
	void queue_push(t_queue *, void *element);

	/**
	* @NAME: queue_pop
	* @DESC: quita el primer elemento de la cola
	*/
	void *queue_pop(t_queue *);

	/**
	* @NAME: queue_peek
	* @DESC: Devuelve el primer elemento de la cola sin extraerlo
	*/
	void *queue_peek(t_queue *);

	/**
	* @NAME: queue_clean
	* @DESC: Elimina todos los elementos de la cola.
	*/
	void queue_clean(t_queue *);

	/**
	* @NAME: queue_clean_and_destroy_elements
	* @DESC: Elimina y destruye todos los elementos de la cola.
	*/
	void queue_clean_and_destroy_elements(t_queue *, void(*element_destroyer)(void*));

	/**
	* @NAME: queue_size
	* @DESC: Devuelve la cantidad de elementos de la cola
	*/
	int queue_size(t_queue *);

	/**
	* @NAME: queue_is_empty
	* @DESC: Verifica si la cola esta vacía
	*/
	int queue_is_empty(t_queue *);

#endif /*QUEUE_H_*/
