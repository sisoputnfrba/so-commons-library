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

#ifndef ARRAY_H_
#define ARRAY_H_

	#include <stdint.h>
	#include <stdio.h>
	#include <stdbool.h>

	typedef struct{
		void **first_element; //Inicio del array
		unsigned int element_count;
	}t_array;

	t_array *array_create(size_t size_element);

	void array_add(t_array *self, void *element);

	void array_add_in_index(t_array *self, unsigned int index, void *element);

	void array_insert(t_array *self, void *element, unsigned int index);

	void array_iterate(t_array *self, void(*closure)(void*));

	t_array *array_map(t_array* self, void *(*transformer)(void*));

	void *array_get(t_array *self, unsigned int index);

	size_t array_size(t_array *self);

	void array_destroy_and_destroy_elements(t_array* self, void(*element_destroyer)(void*));

	void array_destroy(t_array * self);

#endif /* ARRAY_H_ */
