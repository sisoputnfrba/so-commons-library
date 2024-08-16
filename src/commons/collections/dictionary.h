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

#ifndef DICTIONARY_H_
#define DICTIONARY_H_

	#define DEFAULT_DICTIONARY_INITIAL_SIZE 20

	#include "node.h"
	#include <stdbool.h>
	#include "list.h"

	/**
	 * @file
	 * @brief `#include <commons/collections/dictionary.h>`
	 */

	/**
	 * @struct t_dictionary
	 * @brief Estructura de un diccionario que contiene pares string->puntero.
	 *        Inicializar con `dictionary_create()`.
	 */
	typedef struct {
		t_hash_element **elements;
		int table_max_size;
		int table_current_size;
		int elements_amount;
	} t_dictionary;

	/**
	 * @brief Crea el diccionario
	 * @return Devuelve un puntero al diccionario creado, liberable con:
	 *         - `dictionary_destroy()` si se quiere liberar el diccionario pero no
	 *           los elementos que contiene.
	 *         - `dictionary_destroy_and_destroy_elements()` si se quieren liberar
	 *           el diccionario con los elementos que contiene.
	 */
	t_dictionary *dictionary_create(void);

	/**
	 * @brief Inserta un nuevo par (key->element) al diccionario, en caso de ya
	 *        existir la key actualiza el elemento.
	 * @param[in] key La clave del elemento. Una copia de la clave será almacenada
	 *                en el diccionario, por lo que no se afectará a la original.
	 * @param[in] element El elemento a insertar. Este elemento pasará a pertenecer
	 *            al diccionario, por lo que no debe ser liberado por fuera de éste.
	 *
	 * @warning Tener en cuenta que esto no va a liberar la memoria del `element` original.
	 */
	void          dictionary_put(t_dictionary *, char *key, void *element);

	/**
	 * @brief Obtiene el elemento asociado a la key.
	 * @return Devuelve un puntero perteneciente al diccionario, o NULL si no existe.
	 *         Este puntero no debe ser liberado por fuera del diccionario.
	 */
	void         *dictionary_get(t_dictionary *, char *key);

	/**
	 * @brief Remueve un elemento del diccionario y lo retorna.
	 * @return Devuelve un puntero al elemento removido, o NULL si no existe.
	 *         Al haberse removido, debe ser liberado por fuera del diccionario en
	 *         caso de ser necesario.
	 */
	void         *dictionary_remove(t_dictionary *, char *key);

	/**
	 * @brief Remueve un elemento del diccionario y lo destruye llamando a la función
	 *        `element_destroyer` pasada por parámetro.
	 */
	void          dictionary_remove_and_destroy(t_dictionary *, char *, void(*element_destroyer)(void*));

	/**
	 * @brief Aplica `closure` a todos los elementos del diccionario.
	 */
	void          dictionary_iterator(t_dictionary *, void(*closure)(char* key, void* element));

	/**
	 * @brief Quita todos los elementos del diccionario sin liberarlos, dejando el
	 *        diccionario vacío.
	 */
	void          dictionary_clean(t_dictionary *);

	/**
	 * @brief Quita todos los elementos del diccionario y los destruye, dejando el
	 *        diccionario vacío.
	 */
	void          dictionary_clean_and_destroy_elements(t_dictionary *, void(*element_destroyer)(void*));

	/**
	 * @brief Retorna true si `key` se encuentra en el diccionario
	 */
	bool          dictionary_has_key(t_dictionary *, char* key);

	/**
	 * @brief Retorna true si el diccionario está vacío
	 */
	bool          dictionary_is_empty(t_dictionary *);

	/**
	 * @brief Retorna la cantidad de elementos del diccionario
	 */
	int           dictionary_size(t_dictionary *);

	/**
	 * @brief Retorna todas las keys en una lista
	 */
	t_list       *dictionary_keys(t_dictionary *self);

	/**
	 * @brief Retorna todos los elementos en una lista
	 */
	t_list       *dictionary_elements(t_dictionary *self);

	/**
	 * @brief Destruye el diccionario
	 */
	void          dictionary_destroy(t_dictionary *);

	/**
	 * @brief Destruye el diccionario y destruye sus elementos
	 * @note En caso de recibir un diccionario vacío, se comporta como `dictionary_destroy()`
	 */
	void          dictionary_destroy_and_destroy_elements(t_dictionary *, void(*element_destroyer)(void*));

#endif /* DICTIONARY_H_ */
