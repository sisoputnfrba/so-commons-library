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
	 * @struct t_dictionary
	 * @brief  Estructura de un diccionario que contiene pares string->puntero
	 */
	typedef struct {
		t_hash_element **elements;
		int table_max_size;
		int table_current_size;
		int elements_amount;
	} t_dictionary;

	/**
	* @brief   Crea el diccionario
	* @relates t_dictionary
	*/
	t_dictionary *dictionary_create();

	/**
	* @brief   Inserta un nuevo par (key->element) al diccionario, en caso de ya existir la key actualiza el elemento.
	* @relates t_dictionary
	*
	* @warning Tener en cuenta que esto no va a liberar la memoria del `element` original.
	*/
	void 		  dictionary_put(t_dictionary *, char *key, void *element);

	/**
	* @brief   Obtiene el elemento asociado a la key.
	* @relates t_dictionary
	*/
	void 		 *dictionary_get(t_dictionary *, char *key);

	/**
	* @brief   Remueve un elemento del diccionario y lo retorna.
	* @relates t_dictionary
	*/
	void 		 *dictionary_remove(t_dictionary *, char *key);

	/**
	* @brief   Remueve un elemento del diccionario y lo destruye.
	* @relates t_dictionary
	*/
	void 		  dictionary_remove_and_destroy(t_dictionary *, char *, void(*element_destroyer)(void*));

	/**
	* @brief   Aplica closure a todos los elementos del diccionario.
	* @relates t_dictionary
	*/
	void 		  dictionary_iterator(t_dictionary *, void(*closure)(char* key, void* element));

	/**
	* @brief   Quita todos los elementos del diccionario
	* @relates t_dictionary
	*/
	void 		  dictionary_clean(t_dictionary *);

	/**
	* @brief   Quita todos los elementos del diccionario y los destruye
	* @relates t_dictionary
	*/
	void 		  dictionary_clean_and_destroy_elements(t_dictionary *, void(*element_destroyer)(void*));

	/**
	* @brief   Retorna true si key se encuentra en el diccionario
	* @relates t_dictionary
	*/
	bool 		  dictionary_has_key(t_dictionary *, char* key);

	/**
	* @brief   Retorna true si el diccionario está vacío
	* @relates t_dictionary
	*/
	bool 		  dictionary_is_empty(t_dictionary *);

	/**
	* @brief   Retorna la cantidad de elementos del diccionario
	* @relates t_dictionary
	*/
	int 		  dictionary_size(t_dictionary *);

	/**
	* @brief   Retorna todas las keys en una lista
	* @relates t_dictionary
	*/
	t_list 		  *dictionary_keys(t_dictionary *self);

	/**
	* @brief   Retorna todos los elementos en una lista
	* @relates t_dictionary
	*/
	t_list 		  *dictionary_elements(t_dictionary *self);

	/**
	* @brief   Destruye el diccionario
	* @relates t_dictionary
	*/
	void 		  dictionary_destroy(t_dictionary *);

	/**
	* @brief   Destruye el diccionario y destruye sus elementos
	* @relates t_dictionary
	*/
	void 		  dictionary_destroy_and_destroy_elements(t_dictionary *, void(*element_destroyer)(void*));

#endif /* DICTIONARY_H_ */
