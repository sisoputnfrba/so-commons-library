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

#include "list.h"

static void list_link_element(t_link_element* previous, t_link_element* next);
static t_link_element* list_create_element(void* data);
static t_link_element* list_get_element(t_list* self, int index);
static t_link_element* list_find_element(t_list *self, bool(*condition)(void*), int* index);

t_list *list_create() {
	t_list *list = malloc(sizeof(t_list));
	list->head = NULL;
	list->elements_count = 0;
	return list;
}

int list_add(t_list *self, void *data) {
	t_link_element *new_element = list_create_element(data);

	if (self->elements_count == 0) {
		self->head = new_element;
	} else {
		list_link_element(list_get_element(self, self->elements_count - 1), new_element);
	}
	self->elements_count++;
	return self->elements_count - 1;
}

void list_add_all(t_list* self, t_list* other) {
	void _add_in_list(void* element){
		list_add(self, element);
	}

	list_iterate(other, _add_in_list);
}

void* list_get(t_list *self, int index) {
	t_link_element* element_in_index = list_get_element(self, index);
	return element_in_index != NULL ? element_in_index->data : NULL;
}

void list_add_in_index(t_list *self, int index, void *data) {
	t_link_element* next = NULL;
	t_link_element* new_element = NULL;
	t_link_element* previous = NULL;

	if ((self->elements_count >= index) && (index >= 0)) {
		new_element = list_create_element(data);

		if (index == 0) {
			list_link_element(new_element, self->head);
			self->head = new_element;
		} else {
			next = list_get_element(self, index);
			previous = list_get_element(self, index - 1);

			list_link_element(previous, new_element);
			list_link_element(new_element, next);
		}
		self->elements_count++;
	}
}

void *list_replace(t_list *self, int index, void *data) {
	void *old_data = NULL;

	t_link_element *element = list_get_element(self, index);
	if (element != NULL) {
		old_data = element->data;
		element->data = data;
	}

	return old_data;
}

void list_replace_and_destroy_element(t_list *self, int num, void *data, void(*element_destroyer)(void*)) {
	void *old_data = list_replace(self, num, data);
	element_destroyer(old_data);
}

void* list_find(t_list *self, bool(*condition)(void*)) {
	t_link_element *element = list_find_element(self, condition, NULL);
	return element != NULL ? element->data : NULL;
}

void list_iterate(t_list* self, void(*closure)(void*)) {
	t_link_element *element = self->head;
	while (element != NULL) {
		closure(element->data);
		element = element->next;
	}
}

void *list_remove(t_list *self, int index) {
	void *data = NULL;
	t_link_element *aux_element = NULL;

	if (self->head == NULL) return NULL;

	aux_element = list_get_element(self, index);
	data = aux_element->data;

	if (index == 0) {
		self->head = aux_element->next;
	} else {
		t_link_element* previous = list_get_element(self, index - 1);
		list_link_element(previous, aux_element->next);
	}

	self->elements_count--;
	free(aux_element);
	return data;
}

void* list_remove_by_condition(t_list *self, bool(*condition)(void*)) {
	int index = 0;

	t_link_element* element = list_find_element(self, condition, &index);
	if (element != NULL) {
		return list_remove(self, index);
	}

	return NULL;
}

void list_remove_and_destroy_element(t_list *self, int index, void(*element_destroyer)(void*)) {
	void* data = list_remove(self, index);
	element_destroyer(data);
}

void list_remove_and_destroy_by_condition(t_list *self, bool(*condition)(void*), void(*element_destroyer)(void*)) {
	void* data = list_remove_by_condition(self, condition);
	if (data)
		element_destroyer(data);
}

int list_size(t_list *list) {
	return list->elements_count;
}

int list_is_empty(t_list *list) {
	return list_size(list) == 0;
}

void list_clean(t_list *self) {
	t_link_element* element;
	while (self->head != NULL) {
		element = self->head;
		self->head = self->head->next;
		free(element);
	}
	self->elements_count = 0;
}

void list_clean_and_destroy_elements(t_list *self, void(*element_destroyer)(void*)){
	list_iterate(self, element_destroyer);
	list_clean(self);
}

void list_destroy(t_list *self) {
	list_clean(self);
	free(self);
}

void list_destroy_and_destroy_elements(t_list *self, void(*element_destroyer)(void*)) {
	list_clean_and_destroy_elements(self, element_destroyer);
	free(self);
}

t_list* list_take(t_list* self, int count) {
	t_list* sublist = list_create();
	int i = 0;
	for (i = 0; i < count; ++i) {
		void* element = list_get(self, i);
		list_add(sublist, element);
	}
	return sublist;
}

t_list* list_take_and_remove(t_list* self, int count) {
	t_list* sublist = list_create();
	int i = 0;
	for (i = 0; i < count; ++i) {
		void* element = list_remove(self, 0);
		list_add(sublist, element);
	}
	return sublist;
}

t_list* list_filter(t_list* self, bool(*condition)(void*)){
	t_list* filtered = list_create();

	void _add_if_apply(void* element) {
		if (condition(element)) {
			list_add(filtered, element);
		}
	}

	list_iterate(self, _add_if_apply);
	return filtered;
}

t_list* list_map(t_list* self, void*(*transformer)(void*)){
	t_list* mapped = list_create();

	void _add_after_transform(void* element) {
		void* new_element = transformer(element);
		list_add(mapped, new_element);
	}

	list_iterate(self, _add_after_transform);
	return mapped;
}

void list_sort(t_list *self, bool (*comparator)(void *, void *)) {
	// TODO: optimizar (usar un algoritmo mas copado)
	int unsorted_elements = self->elements_count;
	if(unsorted_elements < 2) {
		return;
	}
	t_link_element *auxiliar = NULL;
	bool sorted = true;
	do {
		t_link_element *previous_element = self->head, *cursor = previous_element->next;
		sorted = true;
		int index = 0, last_changed = unsorted_elements;
		while(index < unsorted_elements && cursor != NULL) {
			if(!comparator(previous_element->data, cursor->data)) {
			   auxiliar = cursor->data;
			   cursor->data = previous_element->data;
			   previous_element->data = auxiliar;
			   last_changed = index;
			   sorted = false;
			}
			previous_element = cursor;
			cursor = cursor->next;
			index++;
		}
		unsorted_elements = last_changed;
	} while(!sorted);

}

int list_count_satisfying(t_list* self, bool(*condition)(void*)){
	t_list *satisfying = list_filter(self, condition);
	int result = satisfying->elements_count;
	list_destroy(satisfying);
	return result;
}

bool list_any_satisfy(t_list* self, bool(*condition)(void*)){
	return list_count_satisfying(self, condition) > 0;
}

bool list_all_satisfy(t_list* self, bool(*condition)(void*)){
	return list_count_satisfying(self, condition) == self->elements_count;
}

/********* PRIVATE FUNCTIONS **************/

static void list_link_element(t_link_element* previous, t_link_element* next) {
	if (previous != NULL) {
		previous->next = next;
	}
}

static t_link_element* list_create_element(void* data) {
	t_link_element* element = malloc(sizeof(t_link_element));
	element->data = data;
	element->next = NULL;
	return element;
}

static t_link_element* list_get_element(t_list* self, int index) {
	int cont = 0;

	if ((self->elements_count > index) && (index >= 0)) {
		t_link_element *element = self->head;
		while (cont < index) {
			element = element->next;
			cont++;
		}
		return element;
	}
	return NULL;
}

static t_link_element* list_find_element(t_list *self, bool(*condition)(void*), int* index) {
	t_link_element *element = self->head;
	int position = 0;

	while (element != NULL && !condition(element->data)) {
		element = element->next;
		position++;
	}

	if (index != NULL) {
		*index = position;
	}

	return element;
}
