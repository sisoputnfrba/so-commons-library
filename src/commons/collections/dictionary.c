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

/*
 * dictionary.c
 *
 *  Created on: 17/02/2012
 *      Author: fviale
 */

#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

static unsigned int dictionary_hash(char *key, int key_len);
static void dictionary_resize(t_dictionary *, int new_max_size);

static t_hash_element *dictionary_create_element(char *key, unsigned int key_hash, void *data);
static t_hash_element *dictionary_get_element(t_dictionary *self, char *key);
static void *dictionary_remove_element(t_dictionary *self, char *key);
static void dictionary_destroy_element(t_dictionary *self, t_hash_element *element, void(*data_destroyer)(void*));
static void internal_dictionary_clean_and_destroy_elements(t_dictionary *self, void(*data_destroyer)(void*));

t_dictionary *dictionary_create() {
	t_dictionary *self = malloc(sizeof(t_dictionary));
	self->table_max_size = DEFAULT_DICTIONARY_INITIAL_SIZE;
	self->elements = calloc(self->table_max_size, sizeof(t_hash_element*));
	self->table_current_size = 0;
	self->elements_amount = 0;
	return self;
}

static unsigned int dictionary_hash(char *key, int key_len) {
	unsigned int hash = 0;
	int index;

	for (index = 0; index < key_len; index++) {
		unsigned char c = key[index];
		hash += c;
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);

	return hash;
}

void dictionary_put(t_dictionary *self, char *key, void *data) {
	unsigned int key_hash = dictionary_hash(key, strlen(key));
	int index = key_hash % self->table_max_size;
	t_hash_element * new_element = dictionary_create_element(strdup(key), key_hash, data);

	t_hash_element *element = self->elements[index];

	if (element == NULL) {
		self->elements[index] = new_element;
		self->table_current_size++;

		if (self->table_current_size >= self->table_max_size) {
			dictionary_resize(self, self->table_max_size * 2);
		}

	} else {

		while (element->next != NULL) {
			element = element->next;
		}

		element->next = new_element;
	}

	self->elements_amount++;
}

void *dictionary_get(t_dictionary *self, char *key) {
	t_hash_element *element = dictionary_get_element(self, key);
	return element != NULL ? element->data : NULL;
}

void *dictionary_remove(t_dictionary *self, char *key) {
	void *data = dictionary_remove_element(self, key);
	if( data != NULL){
		self->elements_amount--;
	}
	return data;
}

void dictionary_remove_and_destroy(t_dictionary *self, char *key, void(*data_destroyer)(void*)) {
	void *data = dictionary_remove_element(self, key);

	if( data != NULL){
		self->elements_amount--;
		data_destroyer(data);
	}
}

void dictionary_iterator(t_dictionary *self, void(*closure)(char*,void*)) {
	int table_index;
	for (table_index = 0; table_index < self->table_max_size; table_index++) {
		t_hash_element *element = self->elements[table_index];

		while (element != NULL) {
			closure(element->key, element->data);
			element = element->next;

		}
	}
}

void dictionary_clean(t_dictionary *self) {
	internal_dictionary_clean_and_destroy_elements(self, NULL);
}

void dictionary_clean_and_destroy_elements(t_dictionary *self, void(*data_destroyer)(void*)) {
	internal_dictionary_clean_and_destroy_elements(self, data_destroyer);
}

bool dictionary_has_key(t_dictionary *self, char* key) {
	return dictionary_get_element(self, key) != NULL;
}

bool dictionary_is_empty(t_dictionary *self) {
	return self->elements_amount == 0;
}

int dictionary_size(t_dictionary *self) {
	return self->elements_amount;
}

void dictionary_destroy(t_dictionary *self) {
	dictionary_clean(self);
	free(self->elements);
	free(self);
}

void dictionary_destroy_and_destroy_elements(t_dictionary *self, void(*data_destroyer)(void*)) {
	dictionary_clean_and_destroy_elements(self, data_destroyer);
	free(self->elements);
	free(self);
}

static void dictionary_resize(t_dictionary *self, int new_max_size) {
	t_hash_element **new_table = calloc(new_max_size, sizeof(t_hash_element*));
	t_hash_element **old_table = self->elements;

	self->table_current_size = 0;

	int table_index;
	for (table_index = 0; table_index < self->table_max_size; table_index++) {
		t_hash_element *old_element = old_table[table_index];
		t_hash_element *next_element;

		while( old_element != NULL) {
			// new position
			int new_index = old_element->hashcode % new_max_size;
			t_hash_element *new_element = new_table[new_index];

			if (new_element == NULL) {
				new_table[new_index] = old_element;
				self->table_current_size++;
			} else {

				while (new_element->next != NULL) {
					new_element = new_element->next;
				}

				new_element->next = old_element;
			}

			next_element = old_element->next;
			old_element->next = NULL;
			old_element = next_element;
		}
	}

	self->elements = new_table;
	self->table_max_size = new_max_size;
	free(old_table);
}

/*
 * @NAME: dictionary_clean
 * @DESC: Destruye todos los elementos del diccionario
*/
static void internal_dictionary_clean_and_destroy_elements(t_dictionary *self, void(*data_destroyer)(void*)) {
	int table_index;

	for (table_index = 0; table_index < self->table_max_size; table_index++) {
		t_hash_element *element = self->elements[table_index];
		t_hash_element *next_element = NULL;

		while (element != NULL) {

			next_element = element->next;

			dictionary_destroy_element(self, element, data_destroyer);

			element = next_element;
		}

		self->elements[table_index] = NULL;
	}

	self->table_current_size = 0;
	self->elements_amount = 0;
}

static t_hash_element *dictionary_create_element(char *key, unsigned int key_hash, void *data) {
	t_hash_element *element = malloc(sizeof(t_hash_element));

	element->key = key;
	element->data = data;
	element->hashcode = key_hash;
	element->next = NULL;

	return element;
}

static t_hash_element *dictionary_get_element(t_dictionary *self, char *key) {
	unsigned int key_hash = dictionary_hash(key, strlen(key));
	int index = key_hash % self->table_max_size;

	t_hash_element *element = self->elements[index];

	if (element == NULL) {
		return NULL;
	}

	do {

		if (element->hashcode == key_hash) {
			return element;
		}

	} while ((element = element->next) != NULL);

	return NULL;
}

static void *dictionary_remove_element(t_dictionary *self, char *key) {
	unsigned int key_hash = dictionary_hash(key, strlen(key));
	int index = key_hash % self->table_max_size;

	t_hash_element *element = self->elements[index];

	if (element == NULL) {
		return NULL;
	}

	if (element->hashcode == key_hash) {
		void *data = element->data;
		self->elements[index] = element->next;
		if (self->elements[index] == NULL) {
			self->table_current_size--;
		}
		free(element->key);
		free(element);
		return data;
	}

	while (element->next != NULL) {

		if (element->next->hashcode == key_hash) {
			void *data = element->next->data;
			t_hash_element *aux = element->next;
			element->next = element->next->next;
			free(aux->key);
			free(aux);
			return data;
		}

		element = element->next;
	}

	return NULL;
}

static void dictionary_destroy_element(t_dictionary *self, t_hash_element *element, void(*data_destroyer)(void*)) {
	if (data_destroyer != NULL) {
		data_destroyer(element->data);
	}
	free(element->key);
	free(element);
}
