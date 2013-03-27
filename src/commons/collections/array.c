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

#include <stdlib.h>
#include <string.h>

#include "array.h"

/*------------------- INTERNAL FUNCTIONS -------------------------*/

/*
 * @NAME: array_get_for_index
 * @DESC: Devuelve un puntero al elemento en una determinada posición
 */
static void *pointer_for_index(t_array* self, unsigned int index) {
	return (self->first_element) + (self->element_size * index);
}

/*
 * @NAME: set_element_in
 * @DESC: Setea un elemento en una determinada posición dentro del array
 */
static void set_element_in(t_array* self, void* element, unsigned int index) {
	if(self->first_element)
		memcpy(pointer_for_index(self, index), element, self->element_size);
}

unsigned int following_last_index(t_array* self) {
	return (self->element_count - 1) + 1; //Sirve para visualizar
}
/*------------------- INTERNAL FUNCTIONS -------------------------*/

/*
 * @NAME: init_array
 * @DESC: Inicializa la estructura T_ARRAY
 */
static void init_array(t_array* array, size_t element_size) {
	array->first_element = NULL;
	array->element_count = 0;
	array->element_size = element_size;
}

/*
 * @NAME: array_create
 * @DESC: Crea una instancia valida de TDA Array
 */
t_array *array_create(size_t element_size){
	t_array *array = malloc( sizeof(t_array) );
	init_array(array, element_size);
	return array;
}

/*
 * @NAME: add_space
 * @DESC: Agrega espacio en el array
 */
static bool add_space(t_array* self, unsigned int index) {
	if( (realloc(self->first_element, self->element_size * (index + 1))) ){
		self->element_count = index + 1;
		return true;
	}
	return false;
}

/*
 * @NAME: add_element_in
 * @DESC: Setea un elemento en una determinada posición dentro del array
 */
static void add_element_in(t_array* self, void* element, unsigned int index) {
	bool have_space = true; //Por si no se puede asignar espacio

	if( index > self->element_count )
		have_space = add_space(self, index);

	if( self->first_element && have_space )
		set_element_in(self, element, index);
}

/*
 * @NAME: array_add
 * @DESC: Agrega un elemento al final del array
 */
void array_add(t_array *self, void *element){
	add_element_in(self, element, array_size(self) );
}

/*
 * @NAME: array_add
 * @DESC: Agrega un elemento al final del array
 */
void list_add_in_index(t_array *self, unsigned int index, void *element){
	add_element_in(self, element, index);
}


/*
 * @NAME: array_destroy
 * @DESC: Libera los recursos utilizados por la instancia
 */
void array_destroy(t_array *self){
	if( self->first_element ) free(self->first_element);
	free(self);
}

/*
 * @NAME: array_get_element
 * @DESC: Devuelve un puntero a la posición del elemento, caso de no existir, retorna NULO
 */
void *array_get(t_array *self, unsigned int index){
	if(index < self->element_count)
		return pointer_for_index(self, index);
	return NULL;
}
