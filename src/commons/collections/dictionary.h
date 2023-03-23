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

	typedef struct {
		t_hash_element **elements;
		int table_max_size;
		int table_current_size;
		int elements_amount;
	} t_dictionary;

	/**
	* @fn    dictionary_create
	* @brief Crea el diccionario
	*/
	t_dictionary *dictionary_create();

	/**
	* @fn    dictionary_put
	* @brief Inserta un nuevo par (key->element) al diccionario, en caso de ya existir la key actualiza el elemento.
	*
	* @warning Tener en cuenta que esto no va a liberar la memoria del `element` original.
	*/
	void 		  dictionary_put(t_dictionary *, char *key, void *element);

	/**
	* @fn    dictionary_get
	* @brief Obtiene el elemento asociado a la key.
	*/
	void 		 *dictionary_get(t_dictionary *, char *key);

	/**
	* @fn    dictionary_remove
	* @brief Remueve un elemento del diccionario y lo retorna.
	*/
	void 		 *dictionary_remove(t_dictionary *, char *key);

	/**
	* @fn    dictionary_remove_and_destroy
	* @brief Remueve un elemento del diccionario y lo destruye.
	*/
	void 		  dictionary_remove_and_destroy(t_dictionary *, char *, void(*element_destroyer)(void*));

	/**
	* @fn    dictionary_iterator
	* @brief Aplica closure a todos los elementos del diccionario.
	*/
	void 		  dictionary_iterator(t_dictionary *, void(*closure)(char* key, void* element));

	/**
	* @fn    dictionary_clean
	* @brief Quita todos los elementos del diccionario
	*/
	void 		  dictionary_clean(t_dictionary *);

	/**
	* @fn    dictionary_clean_and_destroy_elements
	* @brief Quita todos los elementos del diccionario y los destruye
	*/
	void 		  dictionary_clean_and_destroy_elements(t_dictionary *, void(*element_destroyer)(void*));

	/**
	* @fn    dictionary_has_key
	* @brief Retorna true si key se encuentra en el diccionario
	*/
	bool 		  dictionary_has_key(t_dictionary *, char* key);

	/**
	* @fn    dictionary_is_empty
	* @brief Retorna true si el diccionario está vacío
	*/
	bool 		  dictionary_is_empty(t_dictionary *);

	/**
	* @fn    dictionary_size
	* @brief Retorna la cantidad de elementos del diccionario
	*/
	int 		  dictionary_size(t_dictionary *);

	/**
	* @fn    dictionary_keys
	* @brief Retorna todas las keys en una lista
	*/
	t_list 		  *dictionary_keys(t_dictionary *self);

	/**
	* @fn    dictionary_elements
	* @brief Retorna todos los elementos en una lista
	*/
	t_list 		  *dictionary_elements(t_dictionary *self);

	/**
	* @fn    dictionary_destroy
	* @brief Destruye el diccionario
	*/
	void 		  dictionary_destroy(t_dictionary *);

	/**
	* @fn    dictionary_destroy_and_destroy_elements
	* @brief Destruye el diccionario y destruye sus elementos
	*/
	void 		  dictionary_destroy_and_destroy_elements(t_dictionary *, void(*element_destroyer)(void*));

#endif /* DICTIONARY_H_ */
