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
	 * @file
	 * @brief `#include <commons/collections/list.h>`
	 */

	/**
	 * @struct t_list
	 * @brief Estructura de una lista enlazada. Inicializar con `list_create()`
	 */
	typedef struct {
		t_link_element *head;
		int elements_count;
	} t_list;

	/**
	 * @struct t_list_iterator
	 * @brief Iterador de listas. Inicializar con `list_iterator_create()`
	 */
	typedef struct {
		t_list *list;
		t_link_element **actual;
		t_link_element **next;
		int index;
	} t_list_iterator;

	/**
	 * @brief Crea una lista
	 * @return Retorna un puntero a la lista creada, liberable con:
	 *         - `list_destroy()` si se quiere liberar la lista pero no
	 *           los elementos que contiene.
	 *         - `list_destroy_and_destroy_elements()` si se quiere liberar
	 *           la lista con los elementos que contiene
	 *
	 * Ejemplo de uso:
	 * @code
	 * t_list* people = list_create();
	 *
	 * => people = []
	 * @endcode
	 */
	t_list * list_create(void);

	/**
	* @brief Agrega un elemento al final de la lista
	* @param element: El elemento a agregar. Este elemento pasará a pertenecer
	*                 a la lista, por lo que no debe ser liberado por fuera de ésta.
	* @return El índice en el que se agregó el elemento
	*
	* Ejemplo de uso:
	* @code
	* t_list* people = list_create();
	*
	* t_person* person_create(char* name, int age) {
	*     t_person* person = malloc(sizeof(t_person));
	*     person->name = string_duplicate(name);
	*     person->age = age;
	*     return person;
	* }
	* list_add(people, person_create("Lionel Messi", 33)); // 0x1234
	* list_add(people, person_create("Cristiano Ronaldo", 35)); // 0x5678
	* list_add(people, person_create("Neymar Jr.", 29)); // 0x9abc
	*
	* => people = [0x1234, 0x5678, 0x9abc]
	* @endcode
	*/
	int list_add(t_list* self, void *element);

	/**
	* @brief Destruye una lista sin liberar los elementos contenidos en los nodos
	*
	* Ejemplo de uso:
	* @code
	* t_person* messi = person_create("Lionel Messi", 33); // 0x1234
	* t_person* ronaldo = person_create("Cristiano Ronaldo", 35); // 0x5678
	* t_person* neymar = person_create("Neymar Jr.", 29); // 0x9abc
	*
	* t_list* people = list_create();
	* list_add(people, messi);
	* list_add(people, ronaldo);
	* list_add(people, neymar);
	*
	* list_destroy(people);
	*
	* => neymar = 0x9abc
	* => ronaldo = 0x5678
	* => messi = 0x1234
	* @endcode
	*/
	void list_destroy(t_list* self);

	/**
	* @brief Destruye una lista y sus elementos contenidos llamando a la función
	*        `element_destroyer` sobre cada uno de ellos.
	* @note En caso de recibir una lista vacía, se comporta como `list_destroy()`.
	*
	* Ejemplo de uso:
	* @code
	* t_list* people = list_create();
	* list_add(people, person_create("Lionel Messi", 33)); // 0x1234
	* list_add(people, person_create("Cristiano Ronaldo", 35)); // 0x5678
	* list_add(people, person_create("Neymar Jr.", 29)); // 0x9abc
	*
	* void person_destroy(void* ptr) {
	*     t_person* person = (t_person*) ptr;
	*     free(person->name);
	*     free(person);
	* }
	* list_destroy_and_destroy_elements(people, person_destroy);
	*
	* => **no hay punteros sin liberar**
	* @endcode
	*/
	void list_destroy_and_destroy_elements(t_list* self, void(*element_destroyer)(void*));

	/**
	* @brief Agrega un elemento en una posicion determinada de la lista
	* @param index: La posicion en la que se quiere agregar el elemento
	* @param element: El elemento a agregar. Este elemento pasará a pertenecer
	*                 a la lista, por lo que no debe ser liberado por fuera de ésta.
	*
	* Ejemplo de uso:
	* @code
	* t_list* people = list_create();
	* list_add(people, person_create("Lionel Messi", 33)); // 0x1234
	* list_add(people, person_create("Cristiano Ronaldo", 35)); // 0x5678
	* list_add(people, person_create("Neymar Jr.", 29)); // 0x9abc
	*
	* list_add_in_index(people, 1, person_create("Kylian Mbappé", 22)); // 0xdef0
	*
	* => people = [0x1234, 0xdef0, 0x5678, 0x9abc]
	* @endcode
	*/
	void list_add_in_index(t_list* self, int index, void *element);

	/**
	* @brief Agrega un elemento a una lista ordenada, manteniendo el
	*        orden definido por el comparador
	* @param data: El elemento a agregar. Este elemento pasará a pertenecer
	*              a la lista, por lo que no debe ser liberado por fuera de ésta.
	* @param comparator: Funcion que compara dos elementos. Debe devolver
	*                    true si el primer parametro debe aparecer antes que el
	*                    segundo en la lista
 	* @return El índice en el que se agregó el elemento
	*
	* Ejemplo de uso:
	* @code
	* t_list* people = list_create();
	* list_add(people, person_create("Kylian Mbappé", 22)); // 0x1234
	* list_add(people, person_create("Lionel Messi", 33)); // 0x5678
	* list_add(people, person_create("Cristiano Ronaldo", 35)); // 0x9abc
	*
	* bool _has_age_less_than(void* a, void* b) {
	*     t_person* person_a = (t_person*) a;
	*     t_person* person_b = (t_person*) b;
	*     return person_a->age <= person_b->age;
	* }
	* list_add_sorted(people, person_create("Neymar Jr.", 29), _has_age_less_than); // 0xdef0
	*
	* => people = [0x1234, 0xdef0, 0x5678, 0x9abc]
	* @endcode
	*/
	int list_add_sorted(t_list *self, void* data, bool (*comparator)(void*,void*));

	/**
	* @brief Agrega todos los elementos de la segunda lista al final de la primera.
	* @param self: La lista a la que se le agregarán los elementos.
	* @param other: La lista de la que se tomarán los elementos. Dichos elementos
	*        pasarán a pertenecer a ambas listas a la vez.
	*
	* Ejemplo de uso:
	* @code
	* t_list* people = list_create();
	* list_add(people, person_create("Lionel Messi", 33)); // 0x1234
	* list_add(people, person_create("Cristiano Ronaldo", 35)); // 0x5678
	*
	* t_list* other_people = list_create();
	* list_add(other_people, person_create("Neymar Jr.", 29)); // 0x9abc
	* list_add(other_people, person_create("Kylian Mbappé", 22)); // 0xdef0
	*
	* list_add_all(people, other_people);
	*
	* => people = [0x1234, 0x5678, 0x9abc, 0xdef0]
	* => other_people = [0x9abc, 0xdef0]
	* @endcode
	*/
	void list_add_all(t_list* self, t_list* other);

	/**
	* @brief Retorna el contenido de una posicion determinada de la lista
	* @return El elemento en la posición index. Este elemento seguirá
	*         perteneciendo a la lista, por lo que no debe ser liberado por fuera
	*         de ésta.
	*
	* Ejemplo de uso:
	* @code
	* t_list* people = list_create();
	* list_add(people, person_create("Lionel Messi", 33)); // 0x1234
	* list_add(people, person_create("Cristiano Ronaldo", 35)); // 0x5678
	* list_add(people, person_create("Neymar Jr.", 29)); // 0x9abc
	*
	* t_person* person = list_get(people, 1);
	*
	* => person = 0x5678
	* => people = [0x1234, 0x5678, 0x9abc]
	* @endcode
	*/
	void *list_get(t_list* self, int index);

	/**
	* @brief Retorna el minimo de la lista según el comparador
	* @param minimum: Funcion que compara dos elementos. Debe devolver
	*                 el menor de los dos
	* @return El elemento mínimo de la lista. Este elemento seguirá
	*         perteneciendo a la lista, por lo que no debe ser liberado por fuera
	*         de ésta.
	*
	* Ejemplo de uso:
	* @code
	* t_list* people = list_create();
	* list_add(people, person_create("Lionel Messi", 33)); // 0x1234
	* list_add(people, person_create("Cristiano Ronaldo", 35)); // 0x5678
	* list_add(people, person_create("Neymar Jr.", 29)); // 0x9abc
	*
	* void* _min_age(void* a, void* b) {
	*     t_person* person_a = (t_person*) a;
	*     t_person* person_b = (t_person*) b;
	*     return person_a->age <= person_b->age ? person_a : person_b;
	* }
	* t_person* youngest = list_get_minimum(people, _min_age);
	*
	* => youngest = 0x9abc
	* => people = [0x1234, 0x5678, 0x9abc]
	* @endcode
	*/
	void *list_get_minimum(t_list* self, void* (*minimum)(void*, void*));

	/**
	* @brief Retorna el maximo de la lista según el comparador
	* @param maximum: Funcion que compara dos elementos. Debe devolver
	*                 el mayor de los dos
	* @return El elemento máximo de la lista. Este elemento seguirá
	*         perteneciendo a la lista, por lo que no debe ser liberado por fuera
	*         de ésta.
	*
	* Ejemplo de uso:
	* @code
	* t_list* people = list_create();
	* list_add(people, person_create("Lionel Messi", 33)); // 0x1234
	* list_add(people, person_create("Cristiano Ronaldo", 35)); // 0x5678
	* list_add(people, person_create("Neymar Jr.", 29)); // 0x9abc
	*
	* void* _max_age(void* a, void* b) {
	*     t_person* person_a = (t_person*) a;
	*     t_person* person_b = (t_person*) b;
	*     return person_a->age >= person_b->age ? person_a : person_b;
	* }
	* t_person* oldest = list_get_maximum(people, _max_age);
	*
	* => oldest = 0x5678
	* => people = [0x1234, 0x5678, 0x9abc]
	* @endcode
	*/
	void *list_get_maximum(t_list* self, void* (*maximum)(void*, void*));

	/**
	* @brief Retorna una nueva lista con los primeros n elementos.
	* @param count: Cantidad máxima de elementos a tomar.
	* @return Una nueva lista con los elementos tomados. Seguirán perteneciendo
	*         a la lista original.
	*
	* Ejemplo de uso:
	* @code
	* t_list* people = list_create();
	* list_add(people, person_create("Lionel Messi", 33)); // 0x1234
	* list_add(people, person_create("Cristiano Ronaldo", 35)); // 0x5678
	* list_add(people, person_create("Neymar Jr.", 29)); // 0x9abc
	*
	* t_list* first_two = list_take(people, 2);
	*
	* => first_two = [0x1234, 0x5678]
	* => people = [0x1234, 0x5678, 0x9abc]
	* @endcode
	*/
	t_list* list_take(t_list* self, int count);

	/**
	* @brief Retorna una nueva lista con los primeros n elementos partiendo
	*        desde el índice indicado.
	* @param start: Índice desde el cual se tomarán los elementos.
	* @param count: Cantidad máxima de elementos a tomar.
	* @return Una nueva lista con los elementos tomados. Seguirán perteneciendo
	*         a la lista original.
	*
	* Ejemplo de uso:
	* @code
	* t_list* people = list_create();
	* list_add(people, person_create("Lionel Messi", 33)); // 0x1234
	* list_add(people, person_create("Cristiano Ronaldo", 35)); // 0x5678
	* list_add(people, person_create("Neymar Jr.", 29)); // 0x9abc
	*
	* t_list* last_two = list_slice(people, 1, 2);
	*
	* => last_two = [0x5678, 0x9abc]
	* => people = [0x1234, 0x5678, 0x9abc]
	* @endcode
	*/
	t_list* list_slice(t_list* self, int start, int count);

	/**
	* @brief Retorna una nueva lista con los primeros n elementos, eliminando
	*        del origen estos elementos.
	* @param count: Cantidad máxima de elementos a tomar.
	* @return Una nueva lista con los elementos tomados. Dichos elementos
	*         dejarán de pertenecer a la lista original.
	*
	* Ejemplo de uso:
	* @code
	* t_list* people = list_create();
	* list_add(people, person_create("Lionel Messi", 33)); // 0x1234
	* list_add(people, person_create("Cristiano Ronaldo", 35)); // 0x5678
	* list_add(people, person_create("Neymar Jr.", 29)); // 0x9abc
	*
	* t_list* first_two = list_take_and_remove(people, 2);
	*
	* => first_two = [0x1234, 0x5678]
	* => people = [0x9abc]
	* @endcode
	*/
	t_list* list_take_and_remove(t_list* self, int count);

	/**
	* @brief Retorna una nueva lista con los primeros n elementos partiendo
	*        desde el índice indicado, eliminando del origen estos elementos.
	* @param start: Índice desde el cual se tomarán los elementos.
	* @param count: Cantidad máxima de elementos a tomar.
	* @return Una nueva lista con los elementos tomados. Dichos elementos
	*         dejarán de pertenecer a la lista original.
	*
	* Ejemplo de uso:
	* @code
	* t_list* people = list_create();
	* list_add(people, person_create("Lionel Messi", 33)); // 0x1234
	* list_add(people, person_create("Cristiano Ronaldo", 35)); // 0x5678
	* list_add(people, person_create("Neymar Jr.", 29)); // 0x9abc
	*
	* t_list* last_two = list_slice_and_remove(people, 1, 2);
	*
	* => last_two = [0x5678, 0x9abc]
	* => people = [0x1234]
	* @endcode
	*/
	t_list* list_slice_and_remove(t_list* self, int start, int count);

	/**
	* @brief Retorna una nueva lista con los elementos que cumplen la condicion
	* @return Los elementos de la lista retornada seguirán perteneciendo a la lista original.
	*
	* Ejemplo de uso:
	* @code
	* t_list* people = list_create();
	* list_add(people, person_create("Lionel Messi", 33)); // 0x1234
	* list_add(people, person_create("Cristiano Ronaldo", 35)); // 0x5678
	* list_add(people, person_create("Neymar Jr.", 29)); // 0x9abc
	*
	* bool _has_e(void* ptr) {
	*     t_person* person = (t_person*) ptr;
	*     return string_contains(person->name, "e");
	* }
	* t_list* with_e = list_filter(people, _has_e);
	*
	* => with_e = [0x1234, 0x9abc]
	* => people = [0x1234, 0x5678, 0x9abc]
	* @endcode
	*/
	t_list* list_filter(t_list* self, bool(*condition)(void*));

	/**
	* @brief Retorna una nueva lista con los elementos transformados
	* @return Los punteros contenidos en la lista retornada serán los
	*         devueltos por `transformer`.
	*
	* Ejemplo de uso:
	* @code
	* t_list* people = list_create();
	* list_add(people, person_create("Lionel Messi", 33)); // 0x1234
	* list_add(people, person_create("Cristiano Ronaldo", 35)); // 0x5678
	* list_add(people, person_create("Neymar Jr.", 29)); // 0x9abc
	*
	* void* _get_name(void* ptr) {
	*     t_person* person = (t_person*) ptr;
	*     return string_duplicate(person->name);
	* }
	* t_list* names = list_map(people, _get_name);
	*
	* => names = ["Lionel Messi", "Cristiano Ronaldo", "Neymar Jr."]
	* => people = [0x1234, 0x5678, 0x9abc]
	* @endcode
	*/
	t_list* list_map(t_list* self, void*(*transformer)(void*));

	/**
	 * @brief Retorna una nueva lista con los elementos de la lista de listas
	 *        recibida.
	 * @return Los elementos de la lista retornada seguirán perteneciendo a las listas originales.
	 *
	 * Ejemplo de uso:
	 * @code
	 * t_list* america = list_create();
	 * list_add(america, person_create("Lionel Messi", 33)); // 0x1234
	 * list_add(america, person_create("Neymar Jr.", 29)); // 0x5678
	 *
	 * t_list* europe = list_create();
	 * list_add(europe, person_create("Cristiano Ronaldo", 35)); // 0x9abc
	 * list_add(europe, person_create("Kylian Mbappé", 22)); // 0xdef0
	 *
	 * t_list* continents = list_create();
	 * list_add(continents, america);
	 * list_add(continents, europe);
	 *
	 * t_list* people = list_flatten(continents);
	 *
	 * => people = [0x1234, 0x5678, 0x9abc, 0xdef0]
	 * => continents = [[0x1234, 0x5678], [0x9abc, 0xdef0]]
	 * @endcode
	 */
	t_list* list_flatten(t_list* self);

	/**
	* @brief Coloca un elemento en una de la posiciones de la lista retornando
	*        el valor anterior
	* @param index: La posicion en la que se quiere agregar el elemento
	* @param element: El elemento a agregar. Este elemento pasará a pertenecer
	*        a la lista, por lo que no debe ser liberado por fuera de ésta.
	* @return El valor ubicado en la posición index antes de ser reemplazado.
	*         Dejará de pertenecer a la lista, por lo que debe ser liberado
	*         una vez que no se lo necesite.
	*
	* Ejemplo de uso:
	* @code
	* t_list* people = list_create();
	* list_add(people, person_create("Lionel Messi", 33)); // 0x1234
	* list_add(people, person_create("Cristiano Ronaldo", 35)); // 0x5678
	* list_add(people, person_create("Neymar Jr.", 29)); // 0x9abc
	*
	* t_person* replaced = list_replace(
	*        people, 1, person_create("Kylian Mbappé", 22)); // 0xdef0
	*
	* => replaced = 0x5678
	* => people = [0x1234, 0xdef0, 0x9abc]
	* @endcode
	*/
	void *list_replace(t_list* self, int index, void* element);

	/**
	* @brief Coloca un elemento en la posición de la lista que cumpla con la
	*        condición, retornando el valor anterior
	* @param condition: Función que recibe un elemento y devuelve `true` si
	*        es el elemento a reemplazar.
	* @param element: El elemento a agregar. Este elemento pasará a pertenecer
	*        a la lista, por lo que no debe ser liberado por fuera de ésta.
	* @return El valor ubicado en la posición index antes de ser reemplazado, o NULL
	*         en caso de no encontrar ningún valor.
	*         Dejará de pertenecer a la lista, por lo que debe ser liberado
	*         una vez que no se lo necesite.
	*
	* Ejemplo de uso:
	* @code
	* t_list* people = list_create();
	* list_add(people, person_create("Lionel Messi", 33)); // 0x1234
	* list_add(people, person_create("Cristiano Ronaldo", 35)); // 0x5678
	* list_add(people, person_create("Neymar Jr.", 29)); // 0x9abc
	*
	* bool _has_age_more_than_30(void* ptr) {
	*     t_person* person = (t_person*) ptr;
	*     return person->age > 30;
	* }
	* t_person* replaced = list_replace_by_condition(
	*         people, _has_age_more_than_30, person_create("Kylian Mbappé", 22)); // 0xdef0
	*
	* => replaced = 0x1234
	* => people = [0xdef0, 0x5678, 0x9abc]
	* @endcode
	*/
	void *list_replace_by_condition(t_list* self, bool(*condition)(void*), void* element);

	/**
	* @brief Coloca un valor en una de la posiciones de la lista liberando el
	*        valor anterior
	* @param index: La posicion en la que se quiere agregar el elemento
	* @param element: El elemento a agregar. Este elemento pasará a pertenecer
	*        a la lista, por lo que no debe ser liberado por fuera de ésta.
	* @param element_destroyer: Función que se encargará de liberar el valor
	*                           reemplazado.
	*
	* Ejemplo de uso:
	* @code
	* t_list* people = list_create();
	* list_add(people, person_create("Lionel Messi", 33)); // 0x1234
	* list_add(people, person_create("Cristiano Ronaldo", 35)); // 0x5678
	* list_add(people, person_create("Neymar Jr.", 29)); // 0x9abc
	*
	* list_replace_and_destroy_element(
	*        people, 1, person_create("Kylian Mbappé", 22), person_destroy); // 0xdef0
	*
	* => people = [0x1234, 0xdef0, 0x9abc]
	* @endcode
	*/
	void list_replace_and_destroy_element(t_list* self, int index, void* element, void(*element_destroyer)(void*));

	/**
	* @brief Remueve un elemento de la lista de una determinada posicion y lo
	*        retorna.
	* @param index: La posicion del elemento a remover
	* @return El elemento removido. Dejará de pertenecer a la lista, por lo que
	*         debe ser liberado una vez que no se lo necesite.
	*
	* Ejemplo de uso:
	* @code
	* t_list* people = list_create();
	* list_add(people, person_create("Lionel Messi", 33)); // 0x1234
	* list_add(people, person_create("Cristiano Ronaldo", 35)); // 0x5678
	* list_add(people, person_create("Neymar Jr.", 29)); // 0x9abc
	*
	* t_person* removed = list_remove(people, 1);
	*
	* => removed = 0x5678
	* => people = [0x1234, 0x9abc]
	* @endcode
	*/
	void *list_remove(t_list* self, int index);

	/**
	* @brief Remueve al elemento de la lista recibido por parámetro.
	* @param element: El elemento a remover. Al ser removido, ya estaremos seguros
	*        de que no pertenece a la lista, por lo que debe ser liberado
	*        una vez que no se lo necesite.
	* @return `true` si el elemento fue removido, `false` en caso de no haber sido
	*         encontrado.
	*
	* Ejemplo de uso:
	* @code
	* t_list* people = list_create();
	* t_person* messi = person_create("Lionel Messi", 33); // 0x1234
	* list_add(people, messi);
	* list_add(people, person_create("Cristiano Ronaldo", 35)); // 0x5678
	* list_add(people, person_create("Neymar Jr.", 29)); // 0x9abc
	*
	* bool removed = list_remove_element(people, messi);
	*
	* => removed = true
	* => people = [0x5678, 0x9abc]
	* => messi = 0x1234
	* @endcode
	*/
	bool list_remove_element(t_list* self, void* element);

	/**
	* @brief Remueve un elemento de la lista de una determinada posicion y
	*        libera la memoria.
	* @param index: La posicion del elemento a remover
	* @param element_destroyer: Función que se encargará de liberar el valor
	*
	* Ejemplo de uso:
	* @code
	* t_list* people = list_create();
	* list_add(people, person_create("Lionel Messi", 33)); // 0x1234
	* list_add(people, person_create("Cristiano Ronaldo", 35)); // 0x5678
	* list_add(people, person_create("Neymar Jr.", 29)); // 0x9abc
	*
	* list_remove_and_destroy_element(people, 1, person_destroy);
	*
	* => people = [0x1234, 0x9abc]
	* @endcode
	*/
	void list_remove_and_destroy_element(t_list* self, int index, void(*element_destroyer)(void*));

	/**
	* @brief Remueve el primer elemento de la lista que haga que condition
	*        devuelva `true`.
	* @return El elemento removido. Dejará de pertenecer a la lista, por lo que
	*         debe ser liberado una vez que no se lo necesite.
	*
	* Ejemplo de uso:
	* @code
	* t_list* people = list_create();
	* list_add(people, person_create("Lionel Messi", 33)); // 0x1234
	* list_add(people, person_create("Cristiano Ronaldo", 35)); // 0x5678
	* list_add(people, person_create("Neymar Jr.", 29)); // 0x9abc
	*
	* bool _has_a(void* ptr) {
	*     t_person* person = (t_person*) ptr;
	*     return string_contains(person->name, "a");
	* }
	* t_person* removed = list_remove_by_condition(people, _has_a);
	*
	* => removed = 0x5678
	* => people = [0x1234, 0x9abc]
	* @endcode
	*/
	void *list_remove_by_condition(t_list* self, bool(*condition)(void*));

	/**
	* @brief Remueve y libera el primer elemento de la lista que haga que
	*        condition devuelva `true`.
	* @param element_destroyer: Función que se encargará de liberar el valor
	*
	* Ejemplo de uso:
	* @code
	* t_list* people = list_create();
	* list_add(people, person_create("Lionel Messi", 33)); // 0x1234
	* list_add(people, person_create("Cristiano Ronaldo", 35)); // 0x5678
	* list_add(people, person_create("Neymar Jr.", 29)); // 0x9abc
	*
	* bool _has_a(void* ptr) {
	*     t_person* person = (t_person*) ptr;
	*     return string_contains(person->name, "a");
	* }
	* list_remove_and_destroy_by_condition(people, _has_a, person_destroy);
	*
	* => people = [0x1234, 0x9abc]
	* @endcode
	*/
	void list_remove_and_destroy_by_condition(t_list* self, bool(*condition)(void*), void(*element_destroyer)(void*));

	/**
	* @brief Remueve y destruye todos los elementos de la lista que hagan que
	*        condition devuelva `true`.
	* @param element_destroyer: Función que se encargará de liberar cada valor
	*
	* Ejemplo de uso:
	* @code
	* t_list* people = list_create();
	* list_add(people, person_create("Lionel Messi", 33)); // 0x1234
	* list_add(people, person_create("Cristiano Ronaldo", 35)); // 0x5678
	* list_add(people, person_create("Neymar Jr.", 29)); // 0x9abc
	*
	* bool _has_a(void* ptr) {
	*     t_person* person = (t_person*) ptr;
	*     return string_contains(person->name, "a");
	* }
	* list_remove_and_destroy_all_by_condition(people, _has_a, person_destroy);
	*
	* => people = [0x1234]
	* @endcode
	*/
	void list_remove_and_destroy_all_by_condition(t_list *self, bool(*condition)(void*), void(*element_destroyer)(void*));

	/**
	* @brief Quita todos los elementos de la lista, sin liberarlos
	*
	* Ejemplo de uso:
	* @code
	* t_person* messi = person_create("Lionel Messi", 33); // 0x1234
	* t_person* ronaldo = person_create("Cristiano Ronaldo", 35); // 0x5678
	* t_person* neymar = person_create("Neymar Jr.", 29); // 0x9abc
	*
	* t_list* people = list_create();
	* list_add(people, messi);
	* list_add(people, ronaldo);
	* list_add(people, neymar);
	*
	* list_clean(people);
	*
	* => people = []
	* => neymar = 0x9abc
	* => ronaldo = 0x5678
	* => messi = 0x1234
	* @endcode
	*/
	void list_clean(t_list* self);

	/**
	* @brief Quita todos los elementos de la lista y los libera llamando a la
	*        función `element_destroyer` sobre cada uno de ellos
	* @note En caso de recibir una lista vacía, se comporta como `list_clean()`.
	*
	* Ejemplo de uso:
	* @code
	* t_list* people = list_create();
	* list_add(people, person_create("Lionel Messi", 33));
	* list_add(people, person_create("Cristiano Ronaldo", 35));
	* list_add(people, person_create("Neymar Jr.", 29));
	*
	* list_clean_and_destroy_elements(people, person_destroy);
	*
	* => people = []
	* @endcode
	*/
	void list_clean_and_destroy_elements(t_list *self, void(*element_destroyer)(void*));

	/**
	* @brief Itera la lista llamando al closure por cada elemento. En caso de
	*        querer modificar la lista durante la iteración, utilizar
	*        `list_iterator_create()` para recorrerla externamente.
	*
	* Ejemplo de uso:
	* @code
	* t_list* people = list_create();
	* list_add(people, person_create("Lionel Messi", 33));
	* list_add(people, person_create("Cristiano Ronaldo", 35));
	* list_add(people, person_create("Neymar Jr.", 29));
	*
	* void print_person(void* ptr) {
	*     t_person* person = (t_person*) ptr;
	*     printf("%s(%d)\n", person->name, person->age);
	* }
	* list_iterate(people, print_person);
	*
	* => Lionel Messi(33)
	*    Cristiano Ronaldo(35)
	*    Neymar Jr.(29)
	* @endcode
	*/
	void list_iterate(t_list* self, void(*closure)(void*));

	/**
	* @brief Retorna el primer valor encontrado, el cual haga que condition
	*        devuelva `true`, o NULL en caso de no encontrar ninguno.
 	* @return El elemento retornado seguirá perteneciendo a la lista, por
	*         lo que no debe ser liberado por fuera de ésta.
	*
	* Ejemplo de uso:
	* @code
	* t_person* find_by_name_contains(t_list* people, char* substring) {
	*     bool _name_contains(void* ptr) {
	*         t_person* person = (t_person*) ptr;
	*         return string_contains(person->name, substring);
	*     }
	*     return list_find(people, _name_contains);
	* }
	*
	* t_list* people = list_create();
	* list_add(people, person_create("Lionel Messi", 33)); // 0x1234
	* list_add(people, person_create("Cristiano Ronaldo", 35)); // 0x5678
	* list_add(people, person_create("Neymar Jr.", 29)); // 0x9abc
	*
	* t_person* a = find_by_name_contains(people, "a");
	* t_person* x = find_by_name_contains(people, "x");
	*
	* => a = 0x5678
	* => x = NULL
	* => people = [0x1234, 0x5678, 0x9abc]
	* @endcode
	*/
	void *list_find(t_list* self, bool(*closure)(void*));

	/**
	* @brief Retorna el tamaño de la lista
	*
	* Ejemplo de uso:
	* @code
	* t_list* people = list_create();
	* list_add(people, person_create("Lionel Messi", 33)); // 0x1234
	* list_add(people, person_create("Cristiano Ronaldo", 35)); // 0x5678
	* list_add(people, person_create("Neymar Jr.", 29)); // 0x9abc
	*
	* int size = list_size(people);
	*
	* => size = 3
	* => people = [0x1234, 0x5678, 0x9abc]
	* @endcode
	*/
	int list_size(t_list* self);

	/**
	* @brief Verifica si la lista esta vacia
	*
	* Ejemplo de uso:
	* @code
	* t_list* people = list_create();
	* bool is_empty = list_is_empty(people);
	*
	* => is_empty = true
	* => people = []
	* @endcode
	*/
	bool list_is_empty(t_list* self);

	/**
	* @brief Ordena la lista segun el comparador
	* @param comparator: Funcion que compara dos elementos. Debe devolver
	*                    true si el primer parametro debe aparecer antes que el
	*                    segundo en la lista
	*
	* Ejemplo de uso:
	* @code
	* t_list* people = list_create();
	* list_add(people, person_create("Lionel Messi", 33)); // 0x1234
	* list_add(people, person_create("Cristiano Ronaldo", 35)); // 0x5678
	* list_add(people, person_create("Neymar Jr.", 29)); // 0x9abc
	*
	* bool _has_age_less_than(void* a, void* b) {
	*     t_person* person_a = (t_person*) a;
	*     t_person* person_b = (t_person*) b;
	*     return person_a->age <= person_b->age;
	* }
	* list_sort(people, _has_age_less_than);
	*
	* => people = [0x9abc, 0x1234, 0x5678]
	* @endcode
	*/
	void list_sort(t_list* self, bool (*comparator)(void *, void *));

	/**
	* @brief Retorna una lista nueva ordenada segun el comparador
	* @param comparator: Funcion que compara dos elementos. Debe devolver
	*                    true si el primer parametro debe aparecer antes que el
	*                    segundo en la lista
	* @return La lista ordenada. Los elementos de la lista retornada seguirán
	*         perteneciendo a la lista original.
	*
	* Ejemplo de uso:
	* @code
	* t_list* people = list_create();
	* list_add(people, person_create("Lionel Messi", 33)); // 0x1234
	* list_add(people, person_create("Cristiano Ronaldo", 35)); // 0x5678
	* list_add(people, person_create("Neymar Jr.", 29)); // 0x9abc
	*
	* bool _has_age_less_than(void* a, void* b) {
	*     t_person* person_a = (t_person*) a;
	*     t_person* person_b = (t_person*) b;
	*     return person_a->age <= person_b->age;
	* }
	* t_list* sorted = list_sorted(people, _has_age_less_than);
	*
	* => sorted = [0x9abc, 0x1234, 0x5678]
	* => people = [0x1234, 0x5678, 0x9abc]
	* @endcode
	*/
	t_list* list_sorted(t_list* self, bool (*comparator)(void *, void *));

	/**
	* @brief Cuenta la cantidad de elementos de la lista que devuelven true
	*        al aplicarles la condición
	*
	* Ejemplo de uso:
	* @code
	* t_list* people = list_create();
	* list_add(people, person_create("Lionel Messi", 33)); // 0x1234
	* list_add(people, person_create("Cristiano Ronaldo", 35)); // 0x5678
	* list_add(people, person_create("Neymar Jr.", 29)); // 0x9abc
	*
	* bool _has_a(void* ptr) {
	*     t_person* person = (t_person*) ptr;
	*     return string_contains(person->name, "a");
	* }
	* int count = list_count_satisfying(people, _has_a);
	*
	* => count = 2
	* => people = [0x1234, 0x5678, 0x9abc]
	* @endcode
	*/
	int list_count_satisfying(t_list* self, bool(*condition)(void*));

	/**
	* @brief Determina si algún elemento de la lista devuelve true al aplicarle
	*        la condición
	*
	* Ejemplo de uso:
	* @code
	* bool people_any_contains(t_list* self, char* substring) {
	*     bool _contains_substring(void* ptr) {
	*         t_person* person = (t_person*) ptr;
	*         return string_contains(person->name, substring);
	*     }
	*     return list_any_satisfy(self, _contains_substring);
	* }

	* t_list* people = list_create();
	* list_add(people, person_create("Lionel Messi", 33)); // 0x1234
	* list_add(people, person_create("Cristiano Ronaldo", 35)); // 0x5678
	* list_add(people, person_create("Neymar Jr.", 29)); // 0x9abc
	*
	* bool has_a = people_any_contains(people, "a");
	* bool has_x = people_any_contains(people, "x");
	*
	* => has_a = true
	* => has_x = false
	* => people = [0x1234, 0x5678, 0x9abc]
	* @endcode
	*/
	bool list_any_satisfy(t_list* self, bool(*condition)(void*));

	/**
	* @brief Determina si todos los elementos de la lista devuelven true al
	*        aplicarles la condición
	*
	* Ejemplo de uso:
	* @code
	* bool people_all_have_age_greater_than(t_list* self, int age) {
	*     bool _has_age_greater_than(void* ptr) {
	*         t_person* person = (t_person*) ptr;
	*         return person->age > age;
	*     }
	*     return list_all_satisfy(self, _has_age_greater_than);
	* }
	*
	* t_list* people = list_create();
	* list_add(people, person_create("Lionel Messi", 33)); // 0x1234
	* list_add(people, person_create("Cristiano Ronaldo", 35)); // 0x5678
	* list_add(people, person_create("Neymar Jr.", 29)); // 0x9abc
	*
	* bool all_greater_than_25 = people_all_have_age_greater_than(people, 25);
	* bool all_greater_than_30 = people_all_have_age_greater_than(people, 30);
	*
	* => all_greater_than_25 = true
	* => all_greater_than_30 = false
	* => people = [0x1234, 0x5678, 0x9abc]
	* @endcode
	*/
	bool list_all_satisfy(t_list* self, bool(*condition)(void*));

	/**
	* @brief Crea una lista nueva con los mismos elementos que la original.
	* @return La lista duplicada. Los elementos de la lista retornada seguirán
	*         perteneciendo a la lista original.
	*
	* Ejemplo de uso:
	* @code
	* t_list* people = list_create();
	* list_add(people, person_create("Lionel Messi", 33)); // 0x1234
	* list_add(people, person_create("Cristiano Ronaldo", 35)); // 0x5678
	*
	* t_list* people_copy = list_duplicate(people);
	*
	* => people = [0x1234, 0x5678]
	* => people_copy = [0x1234, 0x5678]
	* @endcode
	*/
	t_list* list_duplicate(t_list* self);

	/**
	 * @brief Devuelve un valor que resulta de aplicar la operacion entre todos
	 *        los elementos de la lista, partiendo desde el primero.
	 * @param seed: Valor inicial para el primer parámetro de la operación.
	 * @param operation: Funcion que recibe dos valores:
	 *        El primero es el resultado de la operación anterior
	 *        y el segundo es el siguiente elemento de la lista.
	 *        Debe devolver un valor del mismo tipo que el inicial.
	 * @return El resultado de aplicar la operación al último elemento de la lista.
	 *
	 * Ejemplo de uso:
	 * @code
	 * t_list* people = list_create();
	 * list_add(people, person_create("Lionel Messi", 33)); // 0x1234
	 * list_add(people, person_create("Cristiano Ronaldo", 35)); // 0x5678
	 * list_add(people, person_create("Neymar Jr.", 29)); // 0x9abc
	 *
	 * void *_append_person(char* acc, void* ptr) {
	 *     t_person* person = (t_person*) ptr;
	 *     if (!string_is_empty(acc)) {
	 *         string_append(&acc, ", ");
	 *     }
	 *     string_append_with_format(&acc, "%s(%d)", person->name, person->age);
	 *     return acc;
	 * }
	 * char* str = list_fold(people, string_new(), _append_person);
	 *
	 * => str = "Lionel Messi(33), Cristiano Ronaldo(35), Neymar Jr.(29)"
	 * => people = [0x1234, 0x5678, 0x9abc]
	 * @endcode
	 */
	void* list_fold(t_list* self, void* seed, void*(*operation)(void*, void*));

	/**
	 * @brief Devuelve un valor que resulta de aplicar la operacion entre todos
	 *        los elementos de la lista, tomando al primero como semilla y
	 *        partiendo desde el segundo (si existe).
	 * @param operation: Funcion que recibe dos valores del tipo de los elementos
	 *        de la lista y devuelve otro valor del mismo tipo.
	 * @return El resultado de aplicar la operación al último elemento de la lista.
	 *
	 * Ejemplo de uso:
	 * @code
	 * t_list* names = list_create();
	 * list_add(names, string_duplicate("Lionel Messi")); // 0x1234
	 * list_add(names, string_duplicate("Cristiano Ronaldo")); // 0x5678
	 * list_add(names, string_duplicate("Neymar Jr.")); // 0x9abc
	 *
	 * void* _longest_name(void* ptr1, void* ptr2) {
	 *     char* name1 = (char*) ptr1;
	 *     char* name2 = (char*) ptr2;
	 *     return string_length(name1) > string_length(name2) ? name1 : name2;
	 * }
	 * char* longest_name = list_fold1(names, _longest_name);
	 *
	 * => longest_name = "Cristiano Ronaldo"
	 * => names = [0x1234, 0x5678, 0x9abc]
	 * @endcode
	 */
	void* list_fold1(t_list* self, void* (*operation)(void*, void*));

	/**
	 * @brief Inicializa una iteración externa de la lista. Permite recorrer
	 *        la lista y modificarla al mismo tiempo. En caso de
	 *        no querer modificar la lista ni romper la iteración, considerar
	 *        utilizar `list_iterate()`.
	 * @return Un puntero que debe ser liberado con `list_iterator_destroy()`
	 *         una vez finalizada la iteración.
	 *
	 * Ejemplo de uso:
	 * @code
	 * t_list_iterator* iterator = list_iterator_create(list);
	 * while(list_iterator_has_next(iterator)) {
	 *     void* element = list_iterator_next(iterator);
	 *     // Modificar la lista con list_iterator_add(), list_iterator_replace() o list_iterator_remove()
	 *     // y/o romper la iteración con un break o return
	 * }
	 * list_iterator_destroy(iterator);
	 * @endcode
	 */
	t_list_iterator* list_iterator_create(t_list* list);

	/**
	 * @brief Devuelve true si quedan elementos de la lista por recorrer
	 */
	bool list_iterator_has_next(t_list_iterator* iterator);

	/**
	 * @brief Avanza hacia el siguiente elemento a iterar de la lista y
	 *        lo devuelve
	 * @return El elemento actual de la iteración. Pertenecerá a la lista,
	 *         por lo que no debe ser liberado por fuera de ésta a menos que
	 *         se lo remueva con `list_iterator_remove()`.
  	 * @note Invocar esta función solo si `list_iterator_has_next()` es true.
	 */
	void* list_iterator_next(t_list_iterator* iterator);

	/**
	 * @brief Devuelve el índice del elemento actual de la iteración
	 */
	int list_iterator_index(t_list_iterator* iterator);

	/**
	 * @brief Agrega a la lista un elemento delante del actual y detrás
	 *        del siguiente. Luego, avanza hacia el elemento agregado.
	 * @param data: El elemento a agregar. Este elemento pasará a pertenecer
	 *        a la lista, por lo que no debe ser liberado por fuera de ésta.
  	 * @note Invocar esta función luego de obtener el elemento actual
	 *       con `list_iterator_next()`
	 */
	void list_iterator_add(t_list_iterator* iterator, void *data);

	/**
	 * @brief Remueve de la lista al elemento actual de la iteración
	 * @note Invocar esta función luego de obtener el elemento actual
	 *       con `list_iterator_next()`. El elemento removido es el último
	 *       devuelto por dicha función y dejará de pertenecer a la lista,
	 *       por lo que debe ser liberado una vez que no se lo necesite.
	 * @warning Solo se puede llamar a `list_iterator_remove()` una vez por cada
	 *          llamado a `list_iterator_next()`.
	 */
	void list_iterator_remove(t_list_iterator* iterator);

	/**
	 * @brief Reemplaza el elemento actual de la iteración por otro
	 * @param data: El elemento a agregar. Este elemento pasará a pertenecer
	 *        a la lista, por lo que no debe ser liberado por fuera de ésta.
	 * @note Invocar esta función luego de obtener el elemento actual
	 *       con `list_iterator_next()`. El elemento removido es el último
	 *       devuelto por dicha función y dejará de pertenecer a la lista,
	 *       por lo que debe ser liberado una vez que no se lo necesite.
	 */
	void list_iterator_replace(t_list_iterator* iterator, void *data);

	/**
	 * @brief Finaliza la instancia de iteración externa liberando sus recursos
	 * @note Esta operación no libera la lista ni sus elementos.
	 */
	void list_iterator_destroy(t_list_iterator* iterator);

#endif /*LIST_H_*/
