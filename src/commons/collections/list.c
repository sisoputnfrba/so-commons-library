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

static void list_data_destroy(t_list *self, void *data);

/*
 * @NAME: list_create
 * @DESC: Crea una lista
 * @PARAM:
 * 		data_destroyer - Recibe el puntero a la funcion que sabe como liberar la memoria de cada elemento
 * 						 almacenado. Si recibe NULL nunca se eliminan los elemntos de la lista.
 */

t_list *list_create(void(*data_destroyer)(void*)) {
	t_list *list = malloc(sizeof(t_list));
	list->head = NULL;
	list->data_destroyer = data_destroyer;
	list->elements_count = 0;
	return list;
}

/*
 * @NAME: list_add
 * @DESC: Agrega un elemento al final de la lista
 */
int list_add(t_list *self, void *data) {
	t_link_element *new_element = malloc(sizeof(t_link_element));
	new_element->data = data;
	new_element->next = NULL;

	if (self->head == NULL) {
		new_element->next = self->head;
		self->head = new_element;
	} else {
		t_link_element* element = self->head;
		while (element->next != NULL) {
			element = element->next;
		}
		element->next = new_element;
	}
	self->elements_count++;
	return self->elements_count - 1;
}

/*
 * @NAME: list_get
 * @DESC: Retorna el contenido de una posicion determianda de la lista
 */
void* list_get(t_list *self, int num) {
	void* data = NULL;
	int cont;

	if ((self->elements_count > num) && (num >= 0)) {
		t_link_element *element = self->head;
		for (cont = 0; cont < num; element = element->next, cont++)
			;
		data = element->data;
	}
	return data;
}

/*
 * @NAME: list_put
 * @DESC: Agrega un elemento en una posicion determinada de la lista
 */
void list_put(t_list *self, int num, void *data) {
	t_link_element* element = NULL;
	t_link_element* new_element = NULL;
	int cont;
	if ((self->elements_count > num) && (num >= 0)) {
		new_element = malloc(sizeof(t_link_element));
		new_element->data = data;
		if (num == 0) {
			new_element->next = self->head;
			self->head = new_element;
		} else {
			element = self->head;
			for (cont = 0; cont < num; element = element->next, cont++)
				;
			new_element->next = element->next;
			element->next = new_element;
		}
		self->elements_count++;
	}
}

/*
 * @NAME: list_switch
 * @DESC: Coloca un valor en una de la posiciones de la lista retornando el valor anterior
 */
void *list_switch(t_list *self, int num, void *data) {
	void *old_data = NULL;
	int cont;

	if ((self->elements_count > num) && (num >= 0)) {
		t_link_element *element = self->head;
		for (cont = 0; cont < num; element = element->next, cont++)
			;
		old_data = element->data;
		element->data = data;
	}
	return old_data;
}

/*
 * @NAME: list_set
 * @DESC: Coloca un valor en una de la posiciones de la lista liberando el valor anterior
 */
void list_replace(t_list *self, int num, void *data) {
	void *old_data = list_switch(self, num, data);
	if (old_data != NULL) {
		list_data_destroy(self, old_data);
	}
}

/*
 * @NAME: list_find
 * @DESC: Retorna el primer valor encontrado, el cual haga que el closure devuelva != 0
 */
void* list_find(t_list *self, int(*closure)(void*)) {
	t_link_element *element = self->head;
	void *data = NULL;

	while (element != NULL) {
		if (closure(element->data)) {
			data = element->data;
			break;
		}
		element = element->next;
	}
	return data;
}

/*
 * @NAME: list_iterator
 * @DESC: Itera la lista llamando al closure por cada elemento
 */
void list_iterator(t_list* self, void(*closure)(void*)) {
	t_link_element *element = self->head;
	while (element != NULL) {
		closure(element->data);
		element = element->next;
	}
}

/*
 * @NAME: list_remove
 * @DESC: Remueve un elemento de la lista de una determinada posicion y lo retorna.
 */
void *list_remove(t_list *self, int num) {
	void *data = NULL;
	t_link_element *aux_element = NULL;

	if (self->head == NULL
		) return NULL;

	if (num == 0) {
		aux_element = self->head;
		data = self->head->data;
		self->head = self->head->next;
	} else if ((self->elements_count > num) && (num > 0)) {
		t_link_element *element = self->head;
		int cont;
		for (cont = 0; cont < (num - 1); element = element->next, cont++)
			;
		data = element->next->data;
		aux_element = element->next;
		element->next = element->next->next;
	}
	self->elements_count--;
	free(aux_element);
	return data;
}

/*
 * @NAME: list_remove_by_closure
 * @DESC: Remueve el primer elemento de la lista que haga que el closure devuelva != 0.
 */
void* list_remove_by_closure(t_list *self, int(*closure)(void*)) {
	t_link_element *element_aux, *element_ant, *element;
	void *data = NULL;

	element_ant = NULL;
	element = self->head;
	while (element != NULL) {
		if (closure(element->data)) {
			if (self->head->next == NULL) {
				element_aux = self->head;
				self->head = self->head->next;
				element = NULL;
			} else if (element_ant == NULL) {
				element_aux = element;
				self->head = self->head->next;
				element = self->head;
			} else {
				element_aux = element;
				element = element->next;
				element_ant->next = element;
			}
			data = element_aux->data;
			free(element_aux);
			self->elements_count--;
			break;
		} else {
			element_ant = element;
			element = element->next;
		}
	}
	return data;
}

/*
 * @NAME: list_delete
 * @DESC: Remueve un elemento de la lista de una determinada posicion y libera la memoria.
 */
void list_delete(t_list *self, int num) {
	void *data = NULL;
	t_link_element *aux_element = NULL;

	if (self->head == NULL)
		return;

	if (num == 0) {
		aux_element = self->head;
		data = self->head->data;
		self->head = self->head->next;
	} else if ((self->elements_count > num) && (num > 0)) {
		t_link_element *element = self->head;
		int cont;
		for (cont = 0; cont < (num - 1); element = element->next, cont++)
			;
		data = element->next->data;
		aux_element = element->next;
		element->next = element->next->next;
	}
	self->elements_count--;
	free(aux_element);
	list_data_destroy(self, data);
}

/*
 * @NAME: list_remove_by_closure
 * @DESC: Remueve y destruye los elementos de la lista que hagan que el closure devuelva != 0.
 */
void list_delete_by_closure(t_list *self, int(*closure)(void*)) {
	t_link_element *element_aux, *element_ant, *element;

	element_ant = NULL;
	element = self->head;
	while (element != NULL) {
		if (closure(element->data)) {
			if (self->head->next == NULL) {
				element_aux = self->head;
				self->head = self->head->next;
				element = NULL;
			} else if (element_ant == NULL) {
				element_aux = element;
				self->head = self->head->next;
				element = self->head;
			} else {
				element_aux = element;
				element = element->next;
				element_ant->next = element;
			}
			list_data_destroy(self, element->data);
			free(element_aux);
			self->elements_count--;
		} else {
			element_ant = element;
			element = element->next;
		}
	}
}

/*
 * @NAME: list_size
 * @DESC: Retorna el tamaño de la lista
 */
int list_size(t_list *list) {
	return list->elements_count;
}

/*
 * @NAME: list_isempty
 * @DESC: Verifica si la lista esta vacia
 */
int list_is_empty(t_list *list) {
	return list_size(list) == 0;
}

/*
 * @NAME: list_clean
 * @DESC: Elimina todos los elementos de la lista.
 */
void list_clean(t_list *self) {
	t_link_element* element;
	while (self->head != NULL) {
		element = self->head;
		self->head = self->head->next;
		list_data_destroy(self, element->data);
		free(element);
	}
	self->elements_count = 0;
}

/*
 * @NAME: list_destroy
 * @DESC: Destruye una lista, reciviendo como argumento el metodo encargado de liberar cada
 * 		elemento de la lista.
 */
void list_destroy(t_list *self) {
	list_clean(self);
	free(self);
}

/*
 * @NAME: list_data_destroy
 * @DESC: Destruye el contenido de un nodo de la lista
 */
static void list_data_destroy(t_list *self, void *data) {
	if (self->data_destroyer != NULL) {
		self->data_destroyer(data);
	}
}

