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

static void list_link_element(t_list* self, t_link_element* previous, t_link_element* element, int index);
static void list_unlink_element(t_list* self, t_link_element* previous,	t_link_element* element, int index);
static t_link_element* list_create_element(void* data);
static t_link_element* list_find_element(t_list *self, bool(*condition)(void*, int));
static int list_add_element(t_list* self, t_link_element* element, bool(*condition)(void*, int));
static t_link_element* list_remove_element(t_list *self, bool(*condition)(void*, int));
static void list_add_to_sublist(t_list* sublist, t_list *self, bool(*condition)(void*, int), void* (*transformer)(void*));

t_list *list_create() {
	t_list *list = malloc(sizeof(t_list));
	list->head = NULL;
	list->elements_count = 0;
	return list;
}

int list_add(t_list *self, void *data) {
	t_link_element *new_element = list_create_element(data);

	bool _add_as_last(void* element_data, int i) {
		return false;
	}
	return list_add_element(self, new_element, _add_as_last);
}

void list_add_all(t_list* self, t_list* other) {
	bool _add_all_elements(void* element_data, int index) {
		return true;
	}
	list_add_to_sublist(self, other, _add_all_elements, NULL);
}

void* list_get(t_list *self, int index) {
	t_link_element* element_in_index;
	bool _find_element_in_index(void* element_data, int i) {
		return i == index;
	}
	element_in_index = list_find_element(self, _find_element_in_index);

	return element_in_index != NULL ? element_in_index->data : NULL;
}

void list_add_in_index(t_list *self, int index, void *data) {
	if ((self->elements_count >= index) && (index >= 0)) {
		t_link_element* new_element = list_create_element(data);

		bool _add_element_at_index(void* element_data, int i) {
			return i == index;
		}
		list_add_element(self, new_element, _add_element_at_index);
	}
}

void *list_replace(t_list *self, int index, void *data) {
	void *old_data = NULL;
	t_link_element* element;

	bool _find_element_at_index(void* element_data, int i) {
		return i == index;
	}
	element = list_find_element(self, _find_element_at_index);

	if (element != NULL) {
		old_data = element->data;
		element->data = data;
	}

	return old_data;
}

void list_replace_and_destroy_element(t_list *self, int num, void *data, void(*element_destroyer)(void*)) {
	void *old_data = list_replace(self, num, data);
	if(old_data != NULL) {
		element_destroyer(old_data);
	}
}

void* list_find(t_list *self, bool(*condition)(void*)) {
	t_link_element* element;
	bool _find_by_condition(void* element_data, int i) {
		return condition(element_data);
	}
	element = list_find_element(self, _find_by_condition);

	return element != NULL ? element->data : NULL;
}

void list_iterate(t_list* self, void(*closure)(void*)) {
	t_link_element *element = self->head;
	t_link_element *aux = NULL;
	while (element != NULL) {
		aux = element->next;
		closure(element->data);
		element = aux;
	}
}

void *list_remove(t_list *self, int index) {
	void *data = NULL;
	t_link_element *element = NULL;

	bool _remove_at_index(void* element_data, int i) {
		return (i == index);
	}
	element = list_remove_element(self, _remove_at_index);

	if(element != NULL) {
		data = element->data;
		free(element);
	}

	return data;
}

void* list_remove_by_condition(t_list *self, bool(*condition)(void*)) {
	t_link_element *element = NULL;
	void *data = NULL;

	bool _remove_by_condition(void* element_data, int i) {
		return condition(element_data);
	}
	element = list_remove_element(self, _remove_by_condition);

	if(element != NULL) {
		data = element->data;
		free(element);
	}

	return data;
}

void list_remove_and_destroy_element(t_list *self, int index, void(*element_destroyer)(void*)) {
	void* data = list_remove(self, index);
	if(data != NULL) {
		element_destroyer(data);
	}
}

void list_remove_and_destroy_by_condition(t_list *self, bool(*condition)(void*), void(*element_destroyer)(void*)) {
	void* data = list_remove_by_condition(self, condition);
	if(data != NULL) {
		element_destroyer(data);
	}
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

	bool _take_count_elements(void* element_data, int index) {
		return index < count;
	}
	list_add_to_sublist(sublist, self, _take_count_elements, NULL);

	return sublist;
}

t_list* list_take_and_remove(t_list* self, int count) {
	t_list* sublist = list_create();
	if(count > 0) {
		sublist->head = self->head;
		if(count < self->elements_count) {
			t_link_element* last = self->head;
			for(int i = 0; i < count - 1; i++) {
				last = last->next;
			}

			self->head = last->next;
			last->next = NULL;
			sublist->elements_count = count;
			self->elements_count -= count;
		} else {
			self->head = NULL;
			sublist->elements_count = self->elements_count;
			self->elements_count = 0;
		}
	}
	return sublist;
}

t_list* list_filter(t_list* self, bool(*condition)(void*)){
	t_list* filtered = list_create();

	bool _add_if_condition(void* element_data, int index) {
		return condition(element_data);
	}
	list_add_to_sublist(filtered, self, _add_if_condition, NULL);

	return filtered;
}

t_list* list_map(t_list* self, void*(*transformer)(void*)){
	t_list* mapped = list_create();

	bool _transform_all(void* element_data, int index) {
			return true;
	}
	list_add_to_sublist(mapped, self, _transform_all, transformer);

	return mapped;
}

int list_add_sorted(t_list *self, void* data, int (*comparator)(void*,void*)) {
	t_link_element* new_element = list_create_element(data);

	bool _insert_element_sorted(void* element_data, int i) {
		return (comparator(element_data, data) > 0);
	}
	return list_add_element(self, new_element, _insert_element_sorted);
}

void list_sort(t_list *self, int (*comparator)(void *, void *)) {
	if(self->elements_count > 1) {
		t_list* sorted = list_create();
		t_link_element* removed = NULL;

		while(self->elements_count > 0) {
			bool _remove_first_element(void* element_data, int index) {
				return true;
			}
			removed = list_remove_element(self,_remove_first_element);

			bool _insert_element_sorted(void* element_data, int index) {
				return comparator(element_data, removed->data) > 0;
			}
			list_add_element(sorted, removed, _insert_element_sorted);
		}

		self->head = sorted->head;
		self->elements_count = sorted->elements_count;
		free(sorted);
	}
}

t_list* list_sorted(t_list* self, int (*comparator)(void *, void *)) {
	t_list* duplicated = list_duplicate(self);
	list_sort(duplicated, comparator);
	return duplicated;
}

int list_count_satisfying(t_list* self, bool(*condition)(void*)){
	int result = 0;
	void _count_satisfying(void* element_data) {
		if(condition(element_data)) {
			result++;
		}
	}
	list_iterate(self, _count_satisfying);
	return result;
}

bool list_any_satisfy(t_list* self, bool(*condition)(void*)){
	return list_count_satisfying(self, condition) > 0;
}

bool list_all_satisfy(t_list* self, bool(*condition)(void*)){
	return list_count_satisfying(self, condition) == self->elements_count;
}

t_list* list_duplicate(t_list* self) {
	t_list* duplicated = list_create();
	list_add_all(duplicated, self);
	return duplicated;
}

void* list_fold(t_list* self, void* seed, void*(*operation)(void*, void*))
{
	t_link_element* element = self->head;
	void* result = seed;

	while(element != NULL)
	{
		result = operation(result, element->data);
		element = element->next;
	}

	return result;
}

/********* PRIVATE FUNCTIONS **************/

static void list_link_element(t_list* self, t_link_element* previous, t_link_element* element, int index) {
	if (index == 0) {
		element->next = self->head;
		self->head = element;
	} else {
		element->next = previous->next;
		previous->next = element;
	}
	self->elements_count++;
}

static void list_unlink_element(t_list* self, t_link_element* previous,	t_link_element* element, int index) {
	if (element != NULL) {
		if (index == 0) {
			self->head = element->next;
		} else {
			previous->next = element->next;
		}
		element->next = NULL;
		self->elements_count--;
	}
}

static t_link_element* list_create_element(void* data) {
	t_link_element* element = malloc(sizeof(t_link_element));
	element->data = data;
	element->next = NULL;
	return element;
}

static t_link_element* list_find_element(t_list *self, bool(*condition)(void*, int)) {
	t_link_element* element = self->head;
	int index = 0;

	while(element != NULL && !(condition(element->data, index))) {
		element = element->next;
		index++;
	}

	return element;
}

static int list_add_element(t_list* self, t_link_element* element, bool(*condition)(void*, int)) {
	t_link_element *previous = NULL;
	t_link_element *aux = self->head;
	int index = 0;

	while(aux != NULL && !condition(aux->data, index)) {
		previous = aux;
		aux = aux->next;
		index++;
	}
	list_link_element(self, previous, element, index);

	return index;
}

static t_link_element* list_remove_element(t_list *self, bool(*condition)(void*, int)) {
	t_link_element *previous = NULL;
	t_link_element *element = self->head;
	int index = 0;

	while(element != NULL && !condition(element->data, index)) {
		previous = element;
		element = element->next;
		index++;
	}
	list_unlink_element(self, previous, element, index);

	return element;
}

static void list_add_to_sublist(t_list* sublist, t_list *self, bool(*condition)(void*, int), void* (*transformer)(void*)) {
	bool _find_last_element(void* element_data, int i) {
		return (i == sublist->elements_count - 1);
	}
	t_link_element* last_element = list_find_element(sublist, _find_last_element);
	t_link_element* aux = self->head;
	int index = 0;

	while(aux != NULL) {
		if(condition(aux->data, index)) {
			t_link_element* new_element;
			if(transformer == NULL) {
				new_element = list_create_element(aux->data);
			} else {
				new_element = list_create_element(transformer(aux->data));
			}
			list_link_element(sublist, last_element, new_element, sublist->elements_count);
			last_element = new_element;
		}
		index++;
		aux = aux->next;
	}
}
