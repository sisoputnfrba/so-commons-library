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


t_queue *queue_create() {
	t_queue* queue = malloc(sizeof(t_queue));
	t_list* elements = list_create();
	queue->elements = elements;
	return queue;
}

void queue_clean(t_queue *self) {
	list_clean(self->elements);
}

void queue_clean_and_destroy_elements(t_queue *self, void(*element_destroyer)(void*)) {
	list_clean_and_destroy_elements(self->elements, element_destroyer);
}

void queue_destroy(t_queue *self) {
	list_destroy(self->elements);
	free(self);
}

void queue_destroy_and_destroy_elements(t_queue *self, void(*element_destroyer)(void*)) {
	list_destroy_and_destroy_elements(self->elements, element_destroyer);
	free(self);
}

void queue_push(t_queue *self, void *element) {
	list_add(self->elements, element);
}

void *queue_pop(t_queue *self) {
	return list_remove(self->elements, 0);
}

void *queue_peek(t_queue *self) {
	return list_get(self->elements, 0);
}

int queue_size(t_queue* self) {
	return list_size(self->elements);
}

int queue_is_empty(t_queue *self) {
	return list_is_empty(self->elements);
}
