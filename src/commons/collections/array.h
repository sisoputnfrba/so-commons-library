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
		void *first_element; //Inicio del array
		unsigned int element_count;
		size_t element_size;
	}t_array;

	t_array *array_create(size_t element_size);

	void array_add(t_array *self, void *element);

	void array_insert(t_array *self, void *element, unsigned int index);

	void *array_get(t_array *self, unsigned int index);

	void array_destroy(t_array * self);

#endif /* ARRAY_H_ */
