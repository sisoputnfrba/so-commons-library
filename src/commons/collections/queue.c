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
#include "queue.h"


/*
 * @NAME: queue_create
 * @DESC: Crea y devuelve un puntero a una cola
 */
t_queue *queue_create() {
	t_queue* queue = malloc(sizeof(t_queue));
	t_list* elements = list_create();
	queue->elements = elements;
	return queue;
}

/*
 * @NAME: queue_clean
 * @DESC: Elimina todos los nodos de la cola.
 */
void queue_clean(t_queue *self) {
	list_clean(self->elements);
}

/*
 * @NAME: queue_clean_and_destroy_elements
 * @DESC: Elimina todos los elementos de la cola.
 */
void queue_clean_and_destroy_elements(t_queue *self, void(*element_destroyer)(void*)) {
	list_clean_and_destroy_elements(self->elements, element_destroyer);
}

/*
 * @NAME: queue_destroy
 * @DESC: Destruye una cola.
 */
void queue_destroy(t_queue *self) {
	list_destroy(self->elements);
	free(self);
}

/*
 * @NAME: queue_destroy_and_destroy_elements
 * @DESC: Destruye una cola, recibiendo como argumento el metodo encargado de liberar cada
 * 		elemento de la cola.
 */
void queue_destroy_and_destroy_elements(t_queue *self, void(*element_destroyer)(void*)) {
	list_destroy_and_destroy_elements(self->elements, element_destroyer);
	free(self);
}

/*
 * @NAME: queue_push
 * @DESC: Agrega un elemento al final de la cola
 */
void queue_push(t_queue *self, void *element) {
	list_add(self->elements, element);
}

/*
 * @NAME: queue_pop
 * @DESC: quita el primer elemento de la cola
 */
void *queue_pop(t_queue *self) {
	return list_remove(self->elements, 0);
}

/*
 * @NAME: queue_peek
 * @DESC: Devuelve el primer elemento de la cola sin extraerlo
 */
void *queue_peek(t_queue *self) {
	return list_get(self->elements, 0);
}

/*
 * @NAME: queue_size
 * @DESC: Devuelve la cantidad de elementos de la cola
 */
int queue_size(t_queue* self) {
	return list_size(self->elements);
}

/*
 * @NAME: queue_is_empty
 * @DESC: Verifica si la cola esta vacía
 */
int queue_is_empty(t_queue *self) {
	return list_is_empty(self->elements);
}


