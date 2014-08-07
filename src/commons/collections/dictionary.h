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

	typedef struct {
		t_hash_element **elements;
		int table_max_size;
		int table_current_size;
		int elements_amount;
	} t_dictionary;

	/**
	* @NAME: dictionary_create
	* @DESC: Crea el diccionario
	*/
	t_dictionary *dictionary_create();

	/**
	* @NAME: dictionary_put
	* @DESC: Inserta un nuevo par (key->data) al diccionario.
	*/
	void 		  dictionary_put(t_dictionary *, char *key, void *data);

	/**
	* @NAME: dictionary_get
	* @DESC: Obtiene la data asociada a key.
	*/
	void 		 *dictionary_get(t_dictionary *, char *key);

	/**
	* @NAME: dictionary_remove
	* @DESC: Remueve un elemento del diccionario y lo retorna.
	*/
	void 		 *dictionary_remove(t_dictionary *, char *key);

	/**
	* @NAME: dictionary_remove_and_destroy
	* @DESC: Remueve un elemento del diccionario y lo destruye.
	*/
	void 		  dictionary_remove_and_destroy(t_dictionary *, char *, void(*data_destroyer)(void*));

	/**
	* @NAME: dictionary_iterator
	* @DESC: Aplica closure a todos los elementos del diccionario.
	*
	* La función que se pasa por paremtro recibe (char* key, void* value)
	*/
	void 		  dictionary_iterator(t_dictionary *, void(*closure)(char*,void*));

	/**
	* @NAME: dictionary_clean
	* @DESC: Quita todos los elementos del diccionario
	*/
	void 		  dictionary_clean(t_dictionary *);

	/**
	* @NAME: dictionary_clean_and_destroy_elements
	* @DESC: Quita todos los elementos del diccionario y los destruye
	*/
	void 		  dictionary_clean_and_destroy_elements(t_dictionary *, void(*data_destroyer)(void*));

	/**
	* @NAME: dictionary_has_key
	* @DESC: Retorna true si key se encuentra en el diccionario
	*/
	bool 		  dictionary_has_key(t_dictionary *, char* key);

	/**
	* @NAME: dictionary_is_empty
	* @DESC: Retorna true si el diccionario está vacío
	*/
	bool 		  dictionary_is_empty(t_dictionary *);

	/**
	* @NAME: dictionary_size
	* @DESC: Retorna la cantidad de elementos del diccionario
	*/
	int 		  dictionary_size(t_dictionary *);

	/**
	* @NAME: dictionary_destroy
	* @DESC: Destruye el diccionario
	*/
	void 		  dictionary_destroy(t_dictionary *);

	/**
	* @NAME: dictionary_destroy_and_destroy_elements
	* @DESC: Destruye el diccionario y destruye sus elementos
	*/
	void 		  dictionary_destroy_and_destroy_elements(t_dictionary *, void(*data_destroyer)(void*));

#endif /* DICTIONARY_H_ */
