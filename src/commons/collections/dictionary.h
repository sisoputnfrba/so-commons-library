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

	t_dictionary *dictionary_create();
	void 		  dictionary_put(t_dictionary *, char *key, void *data);
	void 		 *dictionary_get(t_dictionary *, char *key);
	void 		 *dictionary_remove(t_dictionary *, char *key);
	void 		  dictionary_remove_and_destroy(t_dictionary *, char *, void(*data_destroyer)(void*));
	void 		  dictionary_iterator(t_dictionary *, void(*closure)(char*,void*));
	void 		  dictionary_clean(t_dictionary *);
	void 		  dictionary_clean_and_destroy_elements(t_dictionary *, void(*data_destroyer)(void*));
	bool 		  dictionary_has_key(t_dictionary *, char* key);
	bool 		  dictionary_is_empty(t_dictionary *);
	int 		  dictionary_size(t_dictionary *);
	void 		  dictionary_destroy(t_dictionary *);
	void 		  dictionary_destroy_and_destroy_elements(t_dictionary *, void(*data_destroyer)(void*));

#endif /* DICTIONARY_H_ */

