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

static t_link_element *list_create_element(void* data);
static void list_link_element(t_list* self, t_link_element** indirect, t_link_element* element);
static t_link_element *list_unlink_element(t_list* self, t_link_element** indirect);
static t_link_element **list_get_indirect_in_index(t_list *self, int index);
static t_link_element **list_get_indirect_by_condition(t_list *self, bool(*condition)(void*));
static void list_add_element(t_list *self, t_link_element **indirect, void *data);
static void *list_replace_indirect(t_link_element **indirect, void *data);
static void *list_remove_indirect(t_list *self, t_link_element **indirect);
static void list_iterate_indirects(t_list* self, int start, int count, bool (*removed)(t_link_element**));
static int list_add_element_sorted(t_list *self, t_link_element* element, bool (*comparator)(void*,void*));
static void* list_fold_elements(t_link_element* element, void* seed, void*(*operation)(void*, void*));

t_list *list_create() {
	t_list *list = malloc(sizeof(t_list));
	list->head = NULL;
	list->elements_count = 0;
	return list;
}

int list_add(t_list *self, void *data) {
	t_link_element **indirect = list_get_indirect_in_index(self, list_size(self));
	list_add_element(self, indirect, data);
	return list_size(self) - 1;
}

void list_add_all(t_list* self, t_list* other) {
	t_link_element **indirect = list_get_indirect_in_index(self, list_size(self));
	void _add_data(void *data) {
		list_add_element(self, indirect, data);
		indirect = &(*indirect)->next;
	}
	list_iterate(other, _add_data);
}

void* list_get(t_list *self, int index) {
	t_link_element **indirect = list_get_indirect_in_index(self, index);
	return (*indirect)->data;
}

void list_add_in_index(t_list *self, int index, void *data) {
	t_link_element **indirect = list_get_indirect_in_index(self, index);
	list_add_element(self, indirect, data);
}

void *list_replace(t_list *self, int index, void *data) {
	t_link_element **indirect = list_get_indirect_in_index(self, index);
	return list_replace_indirect(indirect, data);
}

void *list_replace_by_condition(t_list* self, bool(*condition)(void*), void* element) {
	t_link_element **indirect = list_get_indirect_by_condition(self, condition);
	return (*indirect) != NULL ? list_replace_indirect(indirect, element) : NULL;
}

void list_replace_and_destroy_element(t_list *self, int index, void *data, void(*element_destroyer)(void*)) {
	void *old_data = list_replace(self, index, data);
	element_destroyer(old_data);
}

void* list_find(t_list *self, bool(*condition)(void*)) {
	t_link_element **indirect = list_get_indirect_by_condition(self, condition);
	return (*indirect) != NULL ? (*indirect)->data : NULL;
}

void list_iterate(t_list* self, void(*closure)(void*)) {
	t_link_element **indirect = &self->head;
	while ((*indirect) != NULL) {
		closure((*indirect)->data);
		indirect = &(*indirect)->next;
	}
}

void *list_remove(t_list *self, int index) {
	t_link_element **indirect = list_get_indirect_in_index(self, index);
	return list_remove_indirect(self, indirect);
}

bool list_remove_element(t_list *self, void *element) {
	bool _is_the_element(void *data) {
		return element == data;
	}
	return list_remove_by_condition(self, _is_the_element) != NULL;
}

void* list_remove_by_condition(t_list *self, bool(*condition)(void*)) {
	t_link_element **indirect = list_get_indirect_by_condition(self, condition);
	return (*indirect) != NULL ? list_remove_indirect(self, indirect) : NULL;
}

void list_remove_and_destroy_element(t_list *self, int index, void(*element_destroyer)(void*)) {
	void* data = list_remove(self, index);
	element_destroyer(data);
}

void list_remove_and_destroy_by_condition(t_list *self, bool(*condition)(void*), void(*element_destroyer)(void*)) {
	void* data = list_remove_by_condition(self, condition);
	if (data != NULL) {
		element_destroyer(data);
	}
}

void list_remove_and_destroy_all_by_condition(t_list *self, bool(*condition)(void*), void(*element_destroyer)(void*)) {
	t_link_element **indirect = &self->head;
	while ((*indirect) != NULL) {
		if (condition((*indirect)->data)) {
			element_destroyer(list_remove_indirect(self, indirect));
			continue;
		}
		indirect = &(*indirect)->next;
	}
}

int list_size(t_list *list) {
	return list->elements_count;
}

bool list_is_empty(t_list *list) {
	return list_size(list) == 0;
}

void list_clean(t_list *self) {
	while (!list_is_empty(self)) {
		list_remove_indirect(self, &self->head);
	}
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
	return list_slice(self, 0, count);
}

t_list* list_slice(t_list* self, int start, int count) {
	t_list* sublist = list_create();
	t_link_element **sublist_indirect = &sublist->head;

	bool _add_to_sublist(t_link_element **self_indirect) {
		list_add_element(sublist, sublist_indirect, (*self_indirect)->data);
		sublist_indirect = &(*sublist_indirect)->next;
		return false;
	}
	list_iterate_indirects(self, start, count, _add_to_sublist);

	return sublist;
}

t_list* list_slice_and_remove(t_list* self, int start, int count) {
	t_list* sublist = list_create();
	t_link_element **sublist_indirect = &sublist->head;

	bool _move_from_self_to_sublist(t_link_element **self_indirect) {
		list_link_element(sublist, sublist_indirect, list_unlink_element(self, self_indirect));
		sublist_indirect = &(*sublist_indirect)->next;
		return true;
	}
	list_iterate_indirects(self, start, count, _move_from_self_to_sublist);

	return sublist;
}

t_list* list_take_and_remove(t_list* self, int count) {
	return list_slice_and_remove(self, 0, count);
}

t_list* list_filter(t_list* self, bool(*condition)(void*)){
	t_list *sublist = list_create();
	t_link_element **indirect = &sublist->head;

	void _add_by_condition(void* data) {
		if (condition(data)) {
			list_add_element(sublist, indirect, data);
			indirect = &(*indirect)->next;
		}
	}
	list_iterate(self, _add_by_condition);

	return sublist;
}

t_list* list_map(t_list* self, void*(*transformer)(void*)){
	t_list *sublist = list_create();
	t_link_element **indirect = &sublist->head;

	void _map_data(void* data) {
		list_add_element(sublist, indirect, transformer(data));
		indirect = &(*indirect)->next;
	}
	list_iterate(self, _map_data);

	return sublist;
}

t_list* list_flatten(t_list* self) {
	t_list *sublist = list_create();
	t_link_element **indirect = &sublist->head;

	void _flatten_data(t_list* list) {
		void _add_data(void* data) {
			list_add_element(sublist, indirect, data);
			indirect = &(*indirect)->next;
		}
		list_iterate(list, (void*) _add_data);
	}
	list_iterate(self, (void*) _flatten_data);

	return sublist;
}

int list_add_sorted(t_list *self, void* data, bool (*comparator)(void*,void*)) {
	return list_add_element_sorted(self, list_create_element(data), comparator);
}

void list_sort(t_list *self, bool (*comparator)(void *, void *)) {
	t_list *aux = list_create();
	while (!list_is_empty(self)) {
		list_add_element_sorted(aux, list_unlink_element(self, &self->head), comparator);
	}
	*self = *aux;
	free(aux);
}

t_list* list_sorted(t_list* self, bool (*comparator)(void *, void *)) {
	t_list *other = list_duplicate(self);
	list_sort(other, comparator);
	return other;
}

int list_count_satisfying(t_list* self, bool(*condition)(void*)){
	int result = 0;
	void _count_by_condition(void* element_data) {
		if (condition(element_data)) {
			result++;
		}
	}
	list_iterate(self, _count_by_condition);
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

void* list_fold1(t_list* self, void* (*operation)(void*, void*)) {
	return list_fold_elements(self->head->next, self->head->data, operation);
}

void* list_fold(t_list* self, void* seed, void*(*operation)(void*, void*)) {
	return list_fold_elements(self->head, seed, operation);
}

void* list_get_minimum(t_list* self, void* (*minimum)(void*, void*)) {
	return list_fold1(self, minimum);
}

void* list_get_maximum(t_list* self, void* (*maximum)(void*, void*)) {
	return list_fold1(self, maximum);
}

t_list_iterator* list_iterator_create(t_list* list) {
	t_list_iterator* new = malloc(sizeof(t_list_iterator));
	new->list = list;
	new->actual = NULL;
	new->next = &list->head;
	new->index = -1;
	return new;
}

bool list_iterator_has_next(t_list_iterator* iterator) {
	return (*iterator->next) != NULL;
}

void* list_iterator_next(t_list_iterator* iterator) {
	iterator->actual = iterator->next;
	iterator->next = &(*iterator->next)->next;
	iterator->index++;
	return (*iterator->actual)->data;
}

int list_iterator_index(t_list_iterator* iterator) {
	return iterator->index;
}

void list_iterator_add(t_list_iterator* iterator, void *data) {
	iterator->actual = iterator->next;
	list_add_element(iterator->list, iterator->actual, data);
	iterator->next = &(*iterator->actual)->next;
	iterator->index++;
}

void list_iterator_remove(t_list_iterator* iterator) {
	list_remove_indirect(iterator->list, iterator->actual);
	iterator->next = iterator->actual;
	iterator->index--;
}

void list_iterator_destroy(t_list_iterator* iterator) {
	free(iterator);
}

/********* PRIVATE FUNCTIONS **************/

static t_link_element* list_create_element(void* data) {
	t_link_element* element = malloc(sizeof(t_link_element));
	element->data = data;
	element->next = NULL;
	return element;
}

static void list_link_element(t_list* self, t_link_element** indirect, t_link_element* element) {
	element->next = *indirect;
	*indirect = element;
	self->elements_count++;
}

static t_link_element* list_unlink_element(t_list* self, t_link_element** indirect) {
	t_link_element* element = *indirect;
	*indirect = element->next;
	self->elements_count--;
	return element;
}

static t_link_element **list_get_indirect_in_index(t_list *self, int index) {
	t_link_element **indirect = &self->head;
	for (int i = 0; i < index; ++i) {
		indirect = &(*indirect)->next;
	}
	return indirect;
}

static t_link_element **list_get_indirect_by_condition(t_list *self, bool(*condition)(void*)) {
	t_link_element** indirect = &self->head;
	while ((*indirect) != NULL && !condition((*indirect)->data)) {
		indirect = &(*indirect)->next;
	}
	return indirect;
}

static void list_add_element(t_list *self, t_link_element **indirect, void *data) {
	list_link_element(self, indirect, list_create_element(data));
}

static void *list_replace_indirect(t_link_element **indirect, void *data) {
	void *old_data = (*indirect)->data;
	(*indirect)->data = data;
	return old_data;
}

static void *list_remove_indirect(t_list *self, t_link_element **indirect) {
	t_link_element *element = list_unlink_element(self, indirect);
	void *data = element->data;
	free(element);
	return data;
}

static void list_iterate_indirects(t_list *self, int start, int count, bool (*removed)(t_link_element**)) {
	t_link_element **indirect = list_get_indirect_in_index(self, start);
	int i = 0;
	while ((i < count) && (*indirect) != NULL) {
		if (!removed(indirect)) {
			indirect = &(*indirect)->next;
		}
		++i;
	}
}

static int list_add_element_sorted(t_list *self, t_link_element* element, bool (*comparator)(void*,void*)) {
	t_link_element **indirect = &self->head;
	int index = 0;
	while ((*indirect) != NULL && comparator((*indirect)->data, element->data)) {
		indirect = &(*indirect)->next;
		index++;
	}
	list_link_element(self, indirect, element);

	return index;
}

static void* list_fold_elements(t_link_element* element, void* seed, void*(*operation)(void*, void*)) {
	void* result = seed;
	while (element != NULL) {
		result = operation(result, element->data);
		element = element->next;
	}

	return result;
}
