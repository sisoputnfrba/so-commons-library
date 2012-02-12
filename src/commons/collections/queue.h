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

#ifndef QUEUE_H_
#define QUEUE_H_


#include "node.h"

typedef struct{
	t_link_element* head;
	t_link_element* tail;
	int elements_count;
}t_queue;

t_queue		*queue_create();
void 		queue_destroy( t_queue *queue, void (*data_destroyer)(void*) );

void 		queue_push( t_queue *queue, void *element  );
void		*queue_pop( t_queue *queue );
void 		queu_clean( t_queue *queue, void (*data_destroyer)(void*) );

int 		queue_size( t_queue *queue );
int 		queue_is_empty( t_queue *queue );

#endif /*OLD_QUEUE_H_*/
