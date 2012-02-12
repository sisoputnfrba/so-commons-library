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
t_queue *queue_create(){
	t_queue* queue = malloc( sizeof(t_queue) );
	queue->head = NULL;
	queue->tail = NULL;
	queue->elements_count = 0;
	return queue;
}

/*
 * @NAME: queue_clean
 * @DESC: Elimina todos los elementos de la cola.
 */
void queue_clean( t_queue *queue, void (*data_destroyer)(void*) ){
	t_link_element* element;

	while(queue->head != NULL){
		element = queue->head;
		queue->head = queue->head->next;
		data_destroyer(element->data);
		free(element);
	}
	queue->elements_count = 0;
}

/*
 * @NAME: queue_destroy
 * @DESC: Destruye una cola, reciviendo como argumento el metodo encargado de liberar cada
 * 		elemento de la cola.
 */
void queue_destroy( t_queue *queue, void (*data_destroyer)(void*) ){
	queue_clean(queue, data_destroyer);
	free(queue);
}

/*
 * @NAME: queue_push
 * @DESC: Agrega un elemento al final de la cola
 */
void queue_push( t_queue *queue, void *element ){
	if( element != NULL ){
		t_link_element *auxelement = malloc( sizeof(t_link_element) );
		auxelement->data = element;
		auxelement->next = NULL;
		if( queue->tail != NULL ){
			queue->tail->next = auxelement;
			queue->tail = queue->tail->next;
		}else{
			queue->head = auxelement;
			queue->tail = auxelement;
		}
		queue->elements_count++;
	}
}

/*
 * @NAME: queue_pop
 * @DESC: Saca un elemento del principio de la cola
 */
void* queue_pop( t_queue *queue ){
	void* data = NULL;
	if( queue->head != NULL ){
		t_link_element *element = queue->head;
		queue->head = queue->head->next;
		if( queue->head == NULL ){
			queue->tail = NULL;
		}
		data = element->data;
		free(element);
		queue->elements_count--;
	}
	return data;
}

/*
 * @NAME: queue_size
 * @DESC: Devuelve la cantidad de elementos de la cola
 */
int queue_size( t_queue* queue ){
	return queue->elements_count;
}

/*
 * @NAME: queue_isEmpty
 * @DESC: Verifica si la cola esta vacia
 */
int queue_is_empty( t_queue *queue ){
	return queue_size(queue) == 0;
}

