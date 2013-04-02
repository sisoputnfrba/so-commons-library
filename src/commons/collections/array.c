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

#define ELEMENT_SIZE sizeof(void**)

static void *pointer_for_index(t_array* self, unsigned int index);
static void *pointer_for_element(t_array* self, unsigned int index);

/*
 * @NAME: init_array
 * @DESC: Inicializa la estructura T_ARRAY
 */
static void init_array(t_array* array, size_t element_size) {
	array->first_element = NULL;
	array->element_count = 0;
//	array->element_size = element_size;
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
	if( (self->first_element = realloc(self->first_element, ELEMENT_SIZE * (index + 1))) ){
		self->element_count = index + 1;
		return true;
	}
	return false;
}

/*
 * @NAME: set_element_in
 * @DESC: Setea un elemento en una determinada posición dentro del array
 */
static void set_element_in(t_array* self, void* element, unsigned int index) {
	if(index < self->element_count)
		*(self->first_element + index ) = element;
}

/*
 * @NAME: add_element_in
 * @DESC: Setea un elemento en una determinada posición dentro del array
 */
static void add_element_in(t_array* self, void* element, unsigned int index) {
	bool have_space = true; //Por si no se puede asignar espacio

	if( index >= self->element_count )
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
void array_add_in_index(t_array *self, unsigned int index, void *element){
	add_element_in(self, element, index);
}

/*
 * @NAME: pointer_for_index
 * @DESC: Devuelve un puntero al indice en una determinada posición
 */
static void *pointer_for_index(t_array* self, unsigned int index) {
	return (self->first_element + index);
}

/*
 * @NAME: element_for_index
 * @DESC: Devuelve un puntero al elemento en una determinada posición
 */
static void *pointer_for_element(t_array* self, unsigned int index){
	void **pointer_for =  pointer_for_index(self, index);
	return *pointer_for;
}

/*
 * @NAME: array_get
 * @DESC: Devuelve un puntero al elemento, caso de no existir, retorna NULO
 */
void *array_get(t_array *self, unsigned int index){
	void *element = NULL;
	if(index < self->element_count){
		element = pointer_for_element(self, index);
	}
	return element;
}

/*
 * @NAME: array_generate
 * @DESC: Crea una nueva instancia de TAD Array, a partir de una existente, basandose en algunos elementos
 */
t_array *array_generate(t_array *origin, unsigned int index_origin, unsigned int element_count){
	t_array * array = array_create(0);
	unsigned int position, index = index_origin;
	for( position = 0 ;  index < element_count; position++, index++)
		add_element_in(array, array_get(origin, index), position);
	return array;
}

/*
 * @NAME: array_union
 * @DESC: Une dos instancia de TAD Array sobre una instancia exitente
 */
t_array *array_union(t_array *dest, t_array *head, t_array *tail){
	unsigned int element_count = array_size(head) + array_size(tail);
	void **buffer = malloc( element_count * ELEMENT_SIZE);
	if(buffer){
		memcpy(buffer, head->first_element, array_size(head) * ELEMENT_SIZE);
		memcpy(buffer + array_size(head), tail->first_element, array_size(tail)  * ELEMENT_SIZE);

		free(dest->first_element);
		dest->first_element = buffer;
		dest->element_count = element_count;
	}
	return dest;
}

/*
 * @NAME: array_remove
 * @DESC: Elimina el elemento del array
 */
void *array_remove(t_array *self, unsigned int index){
	void *element = NULL;

	if(index < array_size(self)){

		element = pointer_for_element(self, index);

		t_array *head = array_generate(self, 0, index );
		t_array *tail = array_generate(self, index + 1, array_size(self));

		array_union(self, head, tail);
	}

	return element;
}

/*
 * @NAME: array_size
 * @DESC: Retorna la cantidad de elementos que tiene el array
 */
size_t array_size(t_array *self){
	return self->element_count;
}


/*
 * @NAME: array_iterate
 * @DESC: Itera sobre cada elemento aplicando una clausura
 */
void array_iterate(t_array *self, void(*closure)(void*)){
		unsigned int position;
		for( position = 0; position < self->element_count; position++)
			closure( pointer_for_index(self, position) );
}

/*
 * @NAME: array_map
 * @DESC: Retorna un nuevo array con los elementos transformados
 */
t_array *array_map(t_array* self, void *(*transformer)(void*)){
	t_array *array_transformed = array_create( array_size(self) );
	unsigned int position;
	for(position = 0; position < self->element_count; position++)
		add_element_in(array_transformed, transformer( pointer_for_index(self, position) ), position);

	return array_transformed;
}

/*
 * @NAME: array_destroy
 * @DESC: Destruye los elementos y libera los recursos utilizados por la instancia
 */
void array_destroy_and_destroy_elements(t_array* self, void(*element_destroyer)(void*)){
	array_iterate(self, element_destroyer);
	array_destroy(self);
}

/*
 * @NAME: array_destroy
 * @DESC: Libera los recursos utilizados por la instancia
 */
void array_destroy(t_array *self){
	if( self->first_element ) free(self->first_element);
	free(self);
}
