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

#ifndef LIST_H_
#define LIST_H_

	#include "node.h"
	#include <stdbool.h>

	typedef struct {
		t_link_element *head;
		int elements_count;
	} t_list;

	/**
	* @NAME: list_create
	* @DESC: Crea una lista
	*/
	t_list * list_create();

	/**
	* @NAME: list_destroy
	* @DESC: Destruye una lista sin liberar
	* los elementos contenidos en los nodos
	*/
	void list_destroy(t_list *);

	/**
	* @NAME: list_destroy_and_destroy_elements
	* @DESC: Destruye una lista y sus elementos
	*/
	void list_destroy_and_destroy_elements(t_list*, void(*element_destroyer)(void*));

	/**
	* @NAME: list_add
	* @DESC: Agrega un elemento al final de la lista
	*/
	int list_add(t_list *, void *element);

	/**
	* @NAME: list_add_in_index
	* @DESC: Agrega un elemento en una posicion determinada de la lista
	*/
	void list_add_in_index(t_list *, int index, void *element);

	/**
	* @NAME: list_add_all
	* @DESC: Agrega todos los elementos de
	* la segunda lista en la primera
	*/
	void list_add_all(t_list*, t_list* other);

	/**
	* @NAME: list_get
	* @DESC: Retorna el contenido de una posicion determianda de la lista
	*/
	void *list_get(t_list *, int index);

	/**
	* @NAME: list_take
	* @DESC: Retorna una nueva lista con
	* los primeros n elementos
	*/
	t_list* list_take(t_list*, int count);

	/**
	* @NAME: list_take_and_remove
	* @DESC: Retorna una nueva lista con
	* los primeros n elementos, eliminando
	* del origen estos elementos
	*/
	t_list* list_take_and_remove(t_list*, int count);

	/**
	* @NAME: list_filter
	* @DESC: Retorna una nueva lista con los
	* elementos que cumplen la condicion
	*/
	t_list* list_filter(t_list*, bool(*condition)(void*));

	/**
	* @NAME: list_map
	* @DESC: Retorna una nueva lista con los
	* con los elementos transformados
	*/
	t_list* list_map(t_list*, void*(*transformer)(void*));

	/**
	* @NAME: list_replace
	* @DESC: Coloca un elemento en una de la posiciones
	* de la lista retornando el valor anterior
	*/
	void *list_replace(t_list*, int index, void* element);

	/**
	* @NAME: list_replace_and_destroy_element
	* @DESC: Coloca un valor en una de la posiciones
	* de la lista liberando el valor anterior
	*/
	void list_replace_and_destroy_element(t_list*, int index, void* element, void(*element_destroyer)(void*));

	/**
	* @NAME: list_remove
	* @DESC: Remueve un elemento de la lista de
	* una determinada posicion y lo retorna.
	*/
	void *list_remove(t_list *, int index);

	/**
	* @NAME: list_remove_and_destroy_element
	* @DESC: Remueve un elemento de la lista de una
	* determinada posicion y libera la memoria.
	*/
	void list_remove_and_destroy_element(t_list *, int index, void(*element_destroyer)(void*));

	/**
	* @NAME: list_remove_by_condition
	* @DESC: Remueve el primer elemento de la lista
	* que haga que condition devuelva != 0.
	*/
	void *list_remove_by_condition(t_list *, bool(*condition)(void*));

	/**
	* @NAME: list_remove_and_destroy_by_condition
	* @DESC: Remueve y destruye el primer elemento de
	* la lista que hagan que condition devuelva != 0.
	*/
	void list_remove_and_destroy_by_condition(t_list *, bool(*condition)(void*), void(*element_destroyer)(void*));

	/**
	* @NAME: list_clean
	* @DESC: Quita todos los elementos de la lista.
	*/
	void list_clean(t_list *);

	/**
	* @NAME: list_clean
	* @DESC: Quita y destruye todos los elementos de la lista
	*/
	void list_clean_and_destroy_elements(t_list *self, void(*element_destroyer)(void*));

	/**
	* @NAME: list_iterate
	* @DESC: Itera la lista llamando al closure por cada elemento
	*/
	void list_iterate(t_list *, void(*closure)(void*));

	/**
	* @NAME: list_find
	* @DESC: Retorna el primer valor encontrado, el cual haga que condition devuelva != 0
	*/
	void *list_find(t_list *, bool(*closure)(void*));

	/**
	* @NAME: list_size
	* @DESC: Retorna el tamaño de la lista
	*/
	int list_size(t_list *);

	/**
	* @NAME: list_is_empty
	* @DESC: Verifica si la lista esta vacia
	*/
	int list_is_empty(t_list *);

	/**
	* @NAME: list_sort
	* @DESC: Ordena la lista segun el comparador
	* El comparador devuelve si el primer parametro debe aparecer antes que el
	* segundo en la lista
	*/
	void list_sort(t_list *, bool (*comparator)(void *, void *));

	/**
	* @NAME: list_count_satisfying
	* @DESC: Cuenta la cantidad de elementos de
	* la lista que cumplen una condición
	*/
	int list_count_satisfying(t_list* self, bool(*condition)(void*));

	/**
	* @NAME: list_any_satisfy
	* @DESC: Determina si algún elemento
	* de la lista cumple una condición
	*/
	bool list_any_satisfy(t_list* self, bool(*condition)(void*));

	/**
	* @NAME: list_any_satisfy
	* @DESC: Determina si todos los elementos
	* de la lista cumplen una condición
	*/
	bool list_all_satisfy(t_list* self, bool(*condition)(void*));

#endif /*LIST_H_*/
