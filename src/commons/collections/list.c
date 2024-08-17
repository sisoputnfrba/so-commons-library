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

static t_link_element* list_create_element(void* data);
static void            list_link_element(t_list* self, t_link_element** indirect, t_link_element* element);
static t_link_element* list_unlink_element(t_list* self, t_link_element** indirect);
static t_list_iterator list_iterator_init(t_list* list);
static void            list_iterator_advance(t_list_iterator *iterator);
static void            list_iterator_rewind(t_list_iterator *iterator);
static void            list_iterator_advance_to_index(t_list_iterator* iterator, int index);
static bool            list_iterator_advance_to_condition(t_list_iterator* iterator, bool(*condition)(void*));
static void            list_iterator_apply_in_range(t_list *self, int start, int count, void (*callback)(t_list_iterator*));
static int             list_iterator_add_sorted(t_list_iterator *iterator, void *data, bool (*comparator)(void*,void*));
static void*           list_iterator_fold(t_list_iterator* iterator, void* seed, void*(*operation)(void*, void*));

t_list *list_create() {
	t_list *list = malloc(sizeof(t_list));
	list->head = NULL;
	list->elements_count = 0;
	return list;
}

int list_add(t_list *self, void *data) {
	t_list_iterator self_iterator = list_iterator_init(self);
	list_iterator_advance_to_index(&self_iterator, list_size(self));

	list_iterator_add(&self_iterator, data);
	return list_iterator_index(&self_iterator);
}

void list_add_all(t_list* self, t_list* other) {
	t_list_iterator self_iterator = list_iterator_init(self);
	list_iterator_advance_to_index(&self_iterator, list_size(self));

	t_list_iterator other_iterator = list_iterator_init(other);
	while (list_iterator_has_next(&other_iterator)) {
		list_iterator_add(&self_iterator, list_iterator_next(&other_iterator));
	}
}

void* list_get(t_list *self, int index) {
	t_list_iterator self_iterator = list_iterator_init(self);
	list_iterator_advance_to_index(&self_iterator, index);

	return list_iterator_next(&self_iterator);
}

void list_add_in_index(t_list *self, int index, void *data) {
	t_list_iterator self_iterator = list_iterator_init(self);
	list_iterator_advance_to_index(&self_iterator, index);

	list_iterator_add(&self_iterator, data);
}

void *list_replace(t_list *self, int index, void *data) {
	t_list_iterator self_iterator = list_iterator_init(self);
	list_iterator_advance_to_index(&self_iterator, index);

	void *old_data = list_iterator_next(&self_iterator);
	list_iterator_replace(&self_iterator, data);
	return old_data;
}

void *list_replace_by_condition(t_list* self, bool(*condition)(void*), void* element) {
	t_list_iterator self_iterator = list_iterator_init(self);
	if (list_iterator_advance_to_condition(&self_iterator, condition)) {
		void *old_data = list_iterator_next(&self_iterator);
		list_iterator_replace(&self_iterator, element);
		return old_data;
	}
	return NULL;
}

void list_replace_and_destroy_element(t_list *self, int index, void *data, void(*element_destroyer)(void*)) {
	void *old_data = list_replace(self, index, data);
	element_destroyer(old_data);
}

void* list_find(t_list *self, bool(*condition)(void*)) {
	t_list_iterator self_iterator = list_iterator_init(self);
	if (list_iterator_advance_to_condition(&self_iterator, condition)) {
		return list_iterator_next(&self_iterator);
	}
	return NULL;
}

void list_iterate(t_list* self, void(*closure)(void*)) {
	t_list_iterator self_iterator = list_iterator_init(self);
	while (list_iterator_has_next(&self_iterator)) {
		closure(list_iterator_next(&self_iterator));
	}
}

void *list_remove(t_list *self, int index) {
	t_list_iterator self_iterator = list_iterator_init(self);
	list_iterator_advance_to_index(&self_iterator, index);
	void *data = list_iterator_next(&self_iterator);
	list_iterator_remove(&self_iterator);
	return data;
}

bool list_remove_element(t_list *self, void *element) {
	t_list_iterator self_iterator = list_iterator_init(self);
	bool _is_the_element(void *data) {
		return element == data;
	}
	if (list_iterator_advance_to_condition(&self_iterator, _is_the_element)) {
		list_iterator_advance(&self_iterator);
		list_iterator_remove(&self_iterator);
		return true;
	}
	return false;
}

void* list_remove_by_condition(t_list *self, bool(*condition)(void*)) {
	t_list_iterator self_iterator = list_iterator_init(self);
	if (list_iterator_advance_to_condition(&self_iterator, condition)) {
		void *data = list_iterator_next(&self_iterator);
		list_iterator_remove(&self_iterator);
		return data;
	}
	return NULL;
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
	t_list_iterator self_iterator = list_iterator_init(self);
	while (list_iterator_has_next(&self_iterator)) {
		void* data = list_iterator_next(&self_iterator);
		if (condition(data)) {
			list_iterator_remove(&self_iterator);
			element_destroyer(data);
		}
	}
}

int list_size(t_list *list) {
	return list->elements_count;
}

bool list_is_empty(t_list *list) {
	return list_size(list) == 0;
}

void list_clean(t_list *self) {
	t_list_iterator self_iterator = list_iterator_init(self);
	while (list_iterator_has_next(&self_iterator)) {
		list_iterator_advance(&self_iterator);
		list_iterator_remove(&self_iterator);
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
	t_list_iterator sublist_iterator = list_iterator_init(list_create());

	void _add_to_sublist(t_list_iterator* self_iterator) {
		list_iterator_add(&sublist_iterator, list_iterator_next(self_iterator));
	}
	list_iterator_apply_in_range(self, start, count, _add_to_sublist);

	return sublist_iterator.list;
}

t_list* list_slice_and_remove(t_list* self, int start, int count) {
	t_list_iterator sublist_iterator = list_iterator_init(list_create());

	void _move_from_self_to_sublist(t_list_iterator* self_iterator) {
		list_iterator_add(&sublist_iterator, list_iterator_next(self_iterator));
		list_iterator_remove(self_iterator);
	}
	list_iterator_apply_in_range(self, start, count, _move_from_self_to_sublist);

	return sublist_iterator.list;
}

t_list* list_take_and_remove(t_list* self, int count) {
	return list_slice_and_remove(self, 0, count);
}

t_list* list_filter(t_list* self, bool(*condition)(void*)) {
	t_list_iterator sublist_iterator = list_iterator_init(list_create());

	void _add_by_condition(void* data) {
		if (condition(data)) {
			list_iterator_add(&sublist_iterator, data);
		}
	}
	list_iterate(self, _add_by_condition);

	return sublist_iterator.list;
}

t_list* list_map(t_list* self, void*(*transformer)(void*)){
	t_list_iterator transformed_iterator = list_iterator_init(list_create());

	void _map_data(void* data) {
		list_iterator_add(&transformed_iterator, transformer(data));
	}
	list_iterate(self, _map_data);

	return transformed_iterator.list;
}

t_list* list_flatten(t_list* self) {
	t_list_iterator flattened_iterator = list_iterator_init(list_create());

	void _flatten_data(t_list* list) {
		void _add_data(void* data) {
			list_iterator_add(&flattened_iterator, data);
		}
		list_iterate(list, (void*) _add_data);
	}
	list_iterate(self, (void*) _flatten_data);

	return flattened_iterator.list;
}

int list_add_sorted(t_list *self, void* data, bool (*comparator)(void*,void*)) {
	t_list_iterator self_iterator = list_iterator_init(self);
	return list_iterator_add_sorted(&self_iterator, data, comparator);
}

void list_sort(t_list *right, bool (*comparator)(void *, void *)) {
	if (list_size(right) < 2) {
		return;
	}

	t_list *left = list_take_and_remove(right, list_size(right) / 2);

	list_sort(left, comparator);
	list_sort(right, comparator);

	t_list_iterator right_iterator = list_iterator_init(right);
	void _add_sorted_to_right(void *data) {
		list_iterator_add_sorted(&right_iterator, data, comparator);
	}
	list_iterate(left, _add_sorted_to_right);

	list_destroy(left);
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

bool list_any_satisfy(t_list* self, bool(*condition)(void*)) {
	t_list_iterator self_iterator = list_iterator_init(self);
	return list_iterator_advance_to_condition(&self_iterator, condition);
}

bool list_all_satisfy(t_list* self, bool(*condition)(void*)) {
	return list_count_satisfying(self, condition) == list_size(self);
}

t_list* list_duplicate(t_list* self) {
	t_list* duplicated = list_create();
	list_add_all(duplicated, self);
	return duplicated;
}

void* list_fold1(t_list* self, void* (*operation)(void*, void*)) {
	t_list_iterator self_iterator = list_iterator_init(self);
	return list_iterator_fold(&self_iterator, list_iterator_next(&self_iterator), operation);
}

void* list_fold(t_list* self, void* seed, void*(*operation)(void*, void*)) {
	t_list_iterator self_iterator = list_iterator_init(self);
	return list_iterator_fold(&self_iterator, seed, operation);
}

void* list_get_minimum(t_list* self, void* (*minimum)(void*, void*)) {
	return list_fold1(self, minimum);
}

void* list_get_maximum(t_list* self, void* (*maximum)(void*, void*)) {
	return list_fold1(self, maximum);
}

t_list_iterator* list_iterator_create(t_list* list) {
	t_list_iterator* new = malloc(sizeof(t_list_iterator));
	*new = list_iterator_init(list);
	return new;
}

bool list_iterator_has_next(t_list_iterator* iterator) {
	return (*iterator->next) != NULL;
}

void* list_iterator_next(t_list_iterator* iterator) {
	list_iterator_advance(iterator);
	return (*iterator->actual)->data;
}

int list_iterator_index(t_list_iterator* iterator) {
	return iterator->index;
}

void list_iterator_add(t_list_iterator* iterator, void *data) {
	list_link_element(iterator->list, iterator->next, list_create_element(data));
	list_iterator_advance(iterator);
}

void list_iterator_remove(t_list_iterator* iterator) {
	list_iterator_rewind(iterator);
	free(list_unlink_element(iterator->list, iterator->next));
}

void list_iterator_replace(t_list_iterator* iterator, void *data) {
	(*iterator->actual)->data = data;
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

static t_list_iterator list_iterator_init(t_list* list) {
	return (t_list_iterator) {
		.list = list,
		.actual = NULL,
		.next = &list->head,
		.index = -1
	};
}

static void list_iterator_advance(t_list_iterator *iterator) {
	iterator->actual = iterator->next;
	iterator->index++;
	iterator->next = &(*iterator->actual)->next;
}

static void list_iterator_rewind(t_list_iterator *iterator) {
	iterator->next = iterator->actual;
	iterator->actual = NULL;
	iterator->index--;
}

static void list_iterator_advance_to_index(t_list_iterator *iterator, int index) {
	while (list_iterator_index(iterator) < index - 1) {
		list_iterator_advance(iterator);
	}
}

static bool list_iterator_advance_to_condition(t_list_iterator *iterator, bool(*condition)(void*)) {
	while (list_iterator_has_next(iterator)) {
		if (condition((*iterator->next)->data)) {
			return true;
		}
		list_iterator_advance(iterator);
	}
	return false;
}

static void list_iterator_apply_in_range(t_list *self, int start, int count, void (*callback)(t_list_iterator*)) {
	t_list_iterator self_iterator = list_iterator_init(self);
	list_iterator_advance_to_index(&self_iterator, start);
	for (int i = 0; i < count && list_iterator_has_next(&self_iterator); ++i) {
		callback(&self_iterator);
	}
}

static int list_iterator_add_sorted(t_list_iterator *iterator, void *data, bool (*comparator)(void*,void*)) {
	bool _should_be_after_data(void *element_data) {
		return comparator(data, element_data);
	}
	list_iterator_advance_to_condition(iterator, _should_be_after_data);
	list_iterator_add(iterator, data);
	return list_iterator_index(iterator);
}

static void *list_iterator_fold(t_list_iterator* iterator, void* seed, void*(*operation)(void*, void*)) {
	void *result = seed;
	while (list_iterator_has_next(iterator)) {
		result = operation(result, list_iterator_next(iterator));
	}
	return result;
}
