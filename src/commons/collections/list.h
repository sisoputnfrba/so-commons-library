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

	typedef struct {
		t_list *list;
		t_link_element **actual;
		t_link_element **next;
		int index;
	} t_list_iterator;

	/**
	* @fn    list_create
	* @brief Crea una lista
	*/
	t_list * list_create();

	/**
	* @fn    list_destroy
	* @brief Destruye una lista sin liberar
	*        los elementos contenidos en los nodos
	*/
	void list_destroy(t_list *);

	/**
	* @fn    list_destroy_and_destroy_elements
	* @brief Destruye una lista y sus elementos
	*/
	void list_destroy_and_destroy_elements(t_list*, void(*element_destroyer)(void*));

	/**
	* @fn    list_add
	* @brief Agrega un elemento al final de la lista
	*/
	int list_add(t_list *, void *element);

	/**
	* @fn    list_add_in_index
	* @brief Agrega un elemento en una posicion determinada de la lista
	*/
	void list_add_in_index(t_list *, int index, void *element);

	/**
	* @fn    list_add_sorted
	* @brief Agrega un elemento a una lista ordenada, manteniendo el
	*        orden definido por el comparador
	*
	* @note El comparador devuelve true si el primer parametro debe aparecer
	*       antes que el segundo en la lista
	*/
	int list_add_sorted(t_list *self, void* data, bool (*comparator)(void*,void*));

	/**
	* @fn    list_add_all
	* @brief Agrega todos los elementos de la segunda lista en la primera
	*/
	void list_add_all(t_list*, t_list* other);

	/**
	* @fn    list_get
	* @brief Retorna el contenido de una posicion determinada de la lista
	*/
	void *list_get(t_list *, int index);

	/**
	* @fn    list_get_minimum
	* @brief Retorna el minimo de la lista según el comparador
	*
	* @note El comparador devuelve cuál es el mínimo de dos valores
	*/
	void *list_get_minimum(t_list* self, void* (*minimum)(void*, void*));

	/**
	* @fn    list_get_maximum
	* @brief Retorna el maximo de la lista según el comparador
	*
	* @note El comparador devuelve cuál es el máximo de dos valores
	*/
	void *list_get_maximum(t_list* self, void* (*maximum)(void*, void*));

	/**
	* @fn    list_take
	* @brief Retorna una nueva lista con los primeros n elementos.
	*/
	t_list* list_take(t_list*, int count);

	/**
	* @fn    list_slice
	* @brief Retorna una nueva lista con los primeros n elementos partiendo
	*        desde el índice indicado.
	*/
	t_list* list_slice(t_list* self, int start, int count);

	/**
	* @fn    list_take_and_remove
	* @brief Retorna una nueva lista con los primeros n elementos, eliminando
	*        del origen estos elementos.
	*/
	t_list* list_take_and_remove(t_list*, int count);

	/**
	* @fn    list_slice_and_remove
	* @brief Retorna una nueva lista con los primeros n elementos partiendo
	*        desde el índice indicado, eliminando del origen estos elementos.
	*/
	t_list* list_slice_and_remove(t_list* self, int start, int count);

	/**
	* @fn    list_filter
	* @brief Retorna una nueva lista con los elementos que cumplen la condicion
	*/
	t_list* list_filter(t_list*, bool(*condition)(void*));

	/**
	* @fn    list_map
	* @brief Retorna una nueva lista con los elementos transformados
	*/
	t_list* list_map(t_list*, void*(*transformer)(void*));

	/**
	 * @fn    list_flatten
	 * @brief Retorna una nueva lista con los elementos de la lista de listas
	 *        recibida
	 */
	t_list* list_flatten(t_list* self);

	/**
	* @fn    list_replace
	* @brief Coloca un elemento en una de la posiciones de la lista retornando
	*       el valor anterior
	*/
	void *list_replace(t_list*, int index, void* element);

	/**
	* @fn    list_replace_by_condition
	* @brief Coloca un elemento en la posición de la lista
	*        en donde se encuentra el primer valor que haga que
	*        condition sea != 0, retornando el valor anterior.
	*
	* @note En caso de no encontrar ningún valor, no realiza el
	*       reemplazo y retorna NULL.
	*/
	void *list_replace_by_condition(t_list*, bool(*condition)(void*), void* element);

	/**
	* @fn    list_replace_and_destroy_element
	* @brief Coloca un valor en una de la posiciones de la lista liberando el
	*        valor anterior
	*/
	void list_replace_and_destroy_element(t_list*, int index, void* element, void(*element_destroyer)(void*));

	/**
	* @fn    list_remove
	* @brief Remueve un elemento de la lista de una determinada posicion y lo
	*        retorna.
	*/
	void *list_remove(t_list *, int index);

	/**
	* @fn    list_remove_element
	* @brief Remueve al elemento de la lista recibido por parámetro. Devuelve
	*        false en caso de no haberlo encontrado.
	*/
	bool list_remove_element(t_list* self, void* element);

	/**
	* @fn    list_remove_and_destroy_element
	* @brief Remueve un elemento de la lista de una determinada posicion y
	*        libera la memoria.
	*/
	void list_remove_and_destroy_element(t_list *, int index, void(*element_destroyer)(void*));

	/**
	* @fn    list_remove_by_condition
	* @brief Remueve el primer elemento de la lista que haga que condition
	*        devuelva != 0.
	*/
	void *list_remove_by_condition(t_list *, bool(*condition)(void*));

	/**
	* @fn    list_remove_and_destroy_by_condition
	* @brief Remueve y destruye el primer elemento de la lista que haga que
	*        condition devuelva != 0.
	*/
	void list_remove_and_destroy_by_condition(t_list *, bool(*condition)(void*), void(*element_destroyer)(void*));

	/**
	* @fn    list_remove_and_destroy_all_by_condition
	* @brief Remueve y destruye todos los elementos de la lista que hagan que
	*        condition devuelva != 0.
	*/
	void list_remove_and_destroy_all_by_condition(t_list *self, bool(*condition)(void*), void(*element_destroyer)(void*));

	/**
	* @fn    list_clean
	* @brief Quita todos los elementos de la lista.
	*/
	void list_clean(t_list *);

	/**
	* @fn    list_clean
	* @brief Quita y destruye todos los elementos de la lista
	*/
	void list_clean_and_destroy_elements(t_list *self, void(*element_destroyer)(void*));

	/**
	* @fn    list_iterate
	* @brief Itera la lista llamando al closure por cada elemento
	*/
	void list_iterate(t_list *, void(*closure)(void*));

	/**
	* @fn    list_find
	* @brief Retorna el primer valor encontrado, el cual haga que condition
	*        devuelva != 0
	*/
	void *list_find(t_list *, bool(*closure)(void*));

	/**
	* @fn    list_size
	* @brief Retorna el tamaño de la lista
	*/
	int list_size(t_list *);

	/**
	* @fn    list_is_empty
	* @brief Verifica si la lista esta vacia
	*/
	bool list_is_empty(t_list *);

	/**
	* @fn    list_sort
	* @brief Ordena la lista segun el comparador
	*
	* @note El comparador devuelve si el primer parametro debe aparecer antes
	*       que el segundo en la lista
	*/
	void list_sort(t_list *, bool (*comparator)(void *, void *));

	/**
	* @fn    list_sorted
	* @brief Retorna una lista nueva ordenada segun el comparador
	*
	* @note El comparador devuelve si el primer parametro debe aparecer antes
	*       que el segundo en la lista
	*/
	t_list* list_sorted(t_list *, bool (*comparator)(void *, void *));

	/**
	* @fn    list_count_satisfying
	* @brief Cuenta la cantidad de elementos de la lista que cumplen una
	*        condición
	*/
	int list_count_satisfying(t_list* self, bool(*condition)(void*));

	/**
	* @fn    list_any_satisfy
	* @brief Determina si algún elemento de la lista cumple una condición
	*/
	bool list_any_satisfy(t_list* self, bool(*condition)(void*));

	/**
	* @fn    list_any_satisfy
	* @brief Determina si todos los elementos de la lista cumplen una condición
	*/
	bool list_all_satisfy(t_list* self, bool(*condition)(void*));

	/**
	* @fn    list_duplicate
	* @brief Crea una lista nueva con los mismos elementos que la original.
	**/
	t_list* list_duplicate(t_list* self);

	/**
	 * @fn    list_fold1
	 * @brief Devuelve un valor que resulta de aplicar la operacion entre todos
	 *        los elementos de la lista, tomando al primero como semilla y
	 *        partiendo desde el segundo (si existe).
	 *
	 * @note La funcion 'operation' debe recibir dos valores del tipo de los
	 *       elementos de la lista.
	 */
	void* list_fold1(t_list* self, void* (*operation)(void*, void*));

	/**
	 * @fn    list_fold
	 * @brief Devuelve un valor que resulta de aplicar la operacion entre todos
	 *        los elementos de la lista, partiendo desde el primero.
	 *
	 * @note La funcion 'operation' debe recibir dos valores: uno del tipo del
	 *       valor initial (seed) y otro del tipo de los elementos de la lista.
	 */
	void* list_fold(t_list* self, void* seed, void*(*operation)(void*, void*));

	/**
	 * @fn    list_iterator_create
	 * @brief Inicializa una iteración externa de la lista
	 */
	t_list_iterator* list_iterator_create(t_list* list);

	/**
	 * @fn    list_iterator_has_next
	 * @brief Devuelve true si quedan elementos de la lista por recorrer
	 */
	bool list_iterator_has_next(t_list_iterator* iterator);

	/**
	 * @fn    list_iterator_next
	 * @brief Avanza hacia el siguiente elemento a iterar de la lista y
	 *        lo devuelve
	 */
	void* list_iterator_next(t_list_iterator* iterator);

	/**
	 * @fn    list_iterator_index
	 * @brief Devuelve el índice del elemento actual de la iteración
	 */
	int list_iterator_index(t_list_iterator* iterator);

	/**
	 * @fn    list_iterator_add
	 * @brief Agrega a la lista un elemento delante del actual y detrás
	 *        del siguiente. Luego, avanza hacia el elemento agregado.
	*/
	void list_iterator_add(t_list_iterator* iterator, void *data);

	/**
	 * @fn    list_iterator_remove
	 * @brief Remueve de la lista al elemento actual de la iteración
	 */
	void list_iterator_remove(t_list_iterator* iterator);

	/**
	 * @fn    list_iterator_destroy
	 * @brief Finaliza la instancia de iteración externa liberando sus
	 *        recursos
	 */
	void list_iterator_destroy(t_list_iterator* iterator);

#endif /*LIST_H_*/
