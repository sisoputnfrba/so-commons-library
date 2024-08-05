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

	/**
	 * @struct t_list
	 * @brief  Estructura de una lista enlazada
	 */
	typedef struct {
		t_link_element *head;
		int elements_count;
	} t_list;

	/**
	 * @brief Iterador de listas
	 */
	typedef struct {
		t_list *list;
		t_link_element **actual;
		t_link_element **next;
		int index;
	} t_list_iterator;

	/**
	* @brief   Crea una lista
	* @relates t_list
	*/
	t_list * list_create();

	/**
	* @brief   Destruye una lista sin liberar
	*          los elementos contenidos en los nodos
	* @relates t_list
	*/
	void list_destroy(t_list* self);

	/**
	* @brief   Destruye una lista y sus elementos
	* @relates t_list
	*/
	void list_destroy_and_destroy_elements(t_list* self, void(*element_destroyer)(void*));

	/**
	* @brief   Agrega un elemento al final de la lista
	* @relates t_list
	*/
	int list_add(t_list* self, void *element);

	/**
	* @brief   Agrega un elemento en una posicion determinada de la lista
	* @relates t_list
	*/
	void list_add_in_index(t_list* self, int index, void *element);

	/**
	* @brief   Agrega un elemento a una lista ordenada, manteniendo el
	*          orden definido por el comparador
	* @relates t_list
	*
	* @note El comparador devuelve true si el primer parametro debe aparecer
	*       antes que el segundo en la lista
	*/
	int list_add_sorted(t_list *self, void* data, bool (*comparator)(void*,void*));

	/**
	* @brief   Agrega todos los elementos de la segunda lista en la primera
	* @relates t_list
	*/
	void list_add_all(t_list* self, t_list* other);

	/**
	* @brief   Retorna el contenido de una posicion determinada de la lista
	* @relates t_list
	*/
	void *list_get(t_list* self, int index);

	/**
	* @brief   Retorna el minimo de la lista según el comparador
	* @relates t_list
	*/
	void *list_get_minimum(t_list* self, void* (*minimum)(void*, void*));

	/**
	* @brief   Retorna el maximo de la lista según el comparador
	* @relates t_list
	*/
	void *list_get_maximum(t_list* self, void* (*maximum)(void*, void*));

	/**
	* @brief   Retorna una nueva lista con los primeros n elementos.
	* @relates t_list
	*/
	t_list* list_take(t_list* self, int count);

	/**
	* @brief   Retorna una nueva lista con los primeros n elementos partiendo
	*          desde el índice indicado.
	* @relates t_list
	*/
	t_list* list_slice(t_list* self, int start, int count);

	/**
	* @brief   Retorna una nueva lista con los primeros n elementos, eliminando
	*          del origen estos elementos.
	* @relates t_list
	*/
	t_list* list_take_and_remove(t_list* self, int count);

	/**
	* @brief   Retorna una nueva lista con los primeros n elementos partiendo
	*          desde el índice indicado, eliminando del origen estos elementos.
	* @relates t_list
	*/
	t_list* list_slice_and_remove(t_list* self, int start, int count);

	/**
	* @brief   Retorna una nueva lista con los elementos que cumplen la condicion
	* @relates t_list
	*/
	t_list* list_filter(t_list* self, bool(*condition)(void*));

	/**
	* @brief   Retorna una nueva lista con los elementos transformados
	* @relates t_list
	*/
	t_list* list_map(t_list* self, void*(*transformer)(void*));

	/**
	 * @brief   Retorna una nueva lista con los elementos de la lista de listas
	 *          recibida
	 * @relates t_list
	 */
	t_list* list_flatten(t_list* self);

	/**
	* @brief   Coloca un elemento en una de la posiciones de la lista retornando
	*         el valor anterior
	* @relates t_list
	*/
	void *list_replace(t_list* self, int index, void* element);

	/**
	* @brief   Coloca un elemento en la posición de la lista
	*          en donde se encuentra el primer valor que haga que
	*        condition sea != 0, retornando el valor anterior.
	* @relates t_list
	*
	* @note En caso de no encontrar ningún valor, no realiza el
	*       reemplazo y retorna NULL.
	*/
	void *list_replace_by_condition(t_list* self, bool(*condition)(void*), void* element);

	/**
	* @brief   Coloca un valor en una de la posiciones de la lista liberando el
	*          valor anterior
	* @relates t_list
	*/
	void list_replace_and_destroy_element(t_list* self, int index, void* element, void(*element_destroyer)(void*));

	/**
	* @brief   Remueve un elemento de la lista de una determinada posicion y lo
	*          retorna.
	* @relates t_list
	*/
	void *list_remove(t_list* self, int index);

	/**
	* @brief   Remueve al elemento de la lista recibido por parámetro. Devuelve
	*          false en caso de no haberlo encontrado.
	* @relates t_list
	*/
	bool list_remove_element(t_list* self, void* element);

	/**
	* @brief   Remueve un elemento de la lista de una determinada posicion y
	*          libera la memoria.
	* @relates t_list
	*/
	void list_remove_and_destroy_element(t_list* self, int index, void(*element_destroyer)(void*));

	/**
	* @brief   Remueve el primer elemento de la lista que haga que condition
	*          devuelva != 0.
	* @relates t_list
	*/
	void *list_remove_by_condition(t_list* self, bool(*condition)(void*));

	/**
	* @brief   Remueve y destruye el primer elemento de la lista que haga que
	*          condition devuelva != 0.
	* @relates t_list
	*/
	void list_remove_and_destroy_by_condition(t_list* self, bool(*condition)(void*), void(*element_destroyer)(void*));

	/**
	* @brief   Remueve y destruye todos los elementos de la lista que hagan que
	*          condition devuelva != 0.
	* @relates t_list
	*/
	void list_remove_and_destroy_all_by_condition(t_list *self, bool(*condition)(void*), void(*element_destroyer)(void*));

	/**
	* @brief   Quita todos los elementos de la lista.
	* @relates t_list
	*/
	void list_clean(t_list* self);

	/**
	* @brief   Quita y destruye todos los elementos de la lista
	* @relates t_list
	*/
	void list_clean_and_destroy_elements(t_list *self, void(*element_destroyer)(void*));

	/**
	* @brief   Itera la lista llamando al closure por cada elemento
	* @relates t_list
	*/
	void list_iterate(t_list* self, void(*closure)(void*));

	/**
	* @brief   Retorna el primer valor encontrado, el cual haga que condition
	*          devuelva != 0
	* @relates t_list
	*/
	void *list_find(t_list* self, bool(*closure)(void*));

	/**
	* @brief   Retorna el tamaño de la lista
	* @relates t_list
	*/
	int list_size(t_list* self);

	/**
	* @brief   Verifica si la lista esta vacia
	* @relates t_list
	*/
	bool list_is_empty(t_list* self);

	/**
	* @brief   Ordena la lista segun el comparador
	* @relates t_list
	*
	* @note El comparador devuelve si el primer parametro debe aparecer antes
	*       que el segundo en la lista
	*/
	void list_sort(t_list* self, bool (*comparator)(void *, void *));

	/**
	* @brief   Retorna una lista nueva ordenada segun el comparador
	* @relates t_list
	*
	* @note El comparador devuelve si el primer parametro debe aparecer antes
	*       que el segundo en la lista
	*/
	t_list* list_sorted(t_list* self, bool (*comparator)(void *, void *));

	/**
	* @brief   Cuenta la cantidad de elementos de la lista que cumplen una
	*          condición
	* @relates t_list
	*/
	int list_count_satisfying(t_list* self, bool(*condition)(void*));

	/**
	* @brief   Determina si algún elemento de la lista cumple una condición
	* @relates t_list
	*/
	bool list_any_satisfy(t_list* self, bool(*condition)(void*));

	/**
	* @brief   Determina si todos los elementos de la lista cumplen una condición
	* @relates t_list
	*/
	bool list_all_satisfy(t_list* self, bool(*condition)(void*));

	/**
	* @brief   Crea una lista nueva con los mismos elementos que la original.
	* @relates t_list
	**/
	t_list* list_duplicate(t_list* self);

	/**
	 * @brief   Devuelve un valor que resulta de aplicar la operacion entre todos
	 *          los elementos de la lista, tomando al primero como semilla y
	 *        partiendo desde el segundo (si existe).
	 * @relates t_list
	 *
	 * @note La funcion 'operation' debe recibir dos valores del tipo de los
	 *       elementos de la lista.
	 */
	void* list_fold1(t_list* self, void* (*operation)(void*, void*));

	/**
	 * @brief   Devuelve un valor que resulta de aplicar la operacion entre todos
	 *          los elementos de la lista, partiendo desde el primero.
	 * @relates t_list
	 *
	 * @note La funcion 'operation' debe recibir dos valores: uno del tipo del
	 *       valor initial (seed) y otro del tipo de los elementos de la lista.
	 */
	void* list_fold(t_list* self, void* seed, void*(*operation)(void*, void*));

	/**
	 * @brief   Inicializa una iteración externa de la lista
	 * @relates t_list_iterator
	 */
	t_list_iterator* list_iterator_create(t_list* list);

	/**
	 * @brief   Devuelve true si quedan elementos de la lista por recorrer
	 * @relates t_list_iterator
	 */
	bool list_iterator_has_next(t_list_iterator* iterator);

	/**
	 * @brief   Avanza hacia el siguiente elemento a iterar de la lista y
	 *          lo devuelve
	 * @relates t_list_iterator
	 */
	void* list_iterator_next(t_list_iterator* iterator);

	/**
	 * @brief   Devuelve el índice del elemento actual de la iteración
	 * @relates t_list_iterator
	 */
	int list_iterator_index(t_list_iterator* iterator);

	/**
	 * @brief   Agrega a la lista un elemento delante del actual y detrás
	 *          del siguiente. Luego, avanza hacia el elemento agregado.
	 * @relates t_list_iterator
	*/
	void list_iterator_add(t_list_iterator* iterator, void *data);

	/**
	 * @brief   Remueve de la lista al elemento actual de la iteración
	 * @relates t_list_iterator
	 */
	void list_iterator_remove(t_list_iterator* iterator);

	/**
	 * @brief   Finaliza la instancia de iteración externa liberando sus
	 *          recursos
	 * @relates t_list_iterator
	 */
	void list_iterator_destroy(t_list_iterator* iterator);

#endif /*LIST_H_*/
