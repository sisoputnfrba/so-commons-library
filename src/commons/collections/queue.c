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

static void queue_data_destroy(t_queue *self, void *data);

/*
 * @NAME: queue_create
 * @DESC: Crea y devuelve un puntero a una cola
 */
t_queue *queue_create(void(*data_destroyer)(void*)) {
	t_queue* self = malloc(sizeof(t_queue));
	self->head = NULL;
	self->tail = NULL;
	self->data_destroyer = data_destroyer;
	self->elements_count = 0;
	return self;
}

/*
 * @NAME: queue_clean
 * @DESC: Elimina todos los elementos de la cola.
 */
void queue_clean(t_queue *self) {
	t_link_element* element;

	while (self->head != NULL) {
		element = self->head;
		self->head = self->head->next;
		queue_data_destroy(self, element->data);
		free(element);
	}
	self->elements_count = 0;
}

/*
 * @NAME: queue_destroy
 * @DESC: Destruye una cola, reciviendo como argumento el metodo encargado de liberar cada
 * 		elemento de la cola.
 */
void queue_destroy(t_queue *self) {
	queue_clean(self);
	free(self);
}

/*
 * @NAME: queue_push
 * @DESC: Agrega un elemento al final de la cola
 */
void queue_push(t_queue *self, void *element) {
	if (element != NULL) {
		t_link_element *auxelement = malloc(sizeof(t_link_element));
		auxelement->data = element;
		auxelement->next = NULL;
		if (self->tail != NULL) {
			self->tail->next = auxelement;
			self->tail = self->tail->next;
		} else {
			self->head = auxelement;
			self->tail = auxelement;
		}
		self->elements_count++;
	}
}

/*
 * @NAME: queue_pop
 * @DESC: Saca un elemento del principio de la cola
 */
void* queue_pop(t_queue *self) {
	void* data = NULL;
	if (self->head != NULL) {
		t_link_element *element = self->head;
		self->head = self->head->next;
		if (self->head == NULL) {
			self->tail = NULL;
		}
		data = element->data;
		free(element);
		self->elements_count--;
	}
	return data;
}

/*
 * @NAME: queue_peek
 * @DESC: Devuelve el primer elemento de la cola sin extraerlo
 */
void *queue_peek(t_queue *self){
	void* data = NULL;
	if (self->head != NULL) {
		data = self->head->data;
	}
	return data;
}

/*
 * @NAME: queue_size
 * @DESC: Devuelve la cantidad de elementos de la cola
 */
int queue_size(t_queue* self) {
	return self->elements_count;
}

/*
 * @NAME: queue_isEmpty
 * @DESC: Verifica si la cola esta vacia
 */
int queue_is_empty(t_queue *self) {
	return queue_size(self) == 0;
}

/*
 * @NAME: queue_data_destroy
 * @DESC: Destruye el contenido de un nodo de la cola
 */
static void queue_data_destroy(t_queue *self, void *data) {
	if (self->data_destroyer != NULL) {
		self->data_destroyer(data);
	}
}

