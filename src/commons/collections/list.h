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

#ifndef LIST_H_
#define LIST_H_


	#include "collections.h"

	typedef struct{
		t_link_element *head;
		int elements_count;
	}t_list;

	t_list     *list_create();
	int     	list_add( t_list *list, void *data );
	void       *list_get( t_list *list, int num );
	void		list_put( t_list *list, int num, void *data );
	void	   *list_switch( t_list* list, int num, void* data );
	void 		list_set( t_list* list, int num, void* data, void (*data_destroyer)(void*));
	void	   *list_find( t_list *list, int (*closure)(void*) );
	void		list_iterator( t_list *list, void (*closure)(void*) );
	void   	   *list_remove( t_list *list, int num );
	void        list_removeAndDestroy( t_list *list, int num, void (*data_destroyer)(void*) );
	void    	list_removeByPointer( t_list *list, void *data, void (*data_destroyer)(void*) );
	void    	list_removeByClosure( t_list *list, int (*closure)(void*), void (*data_destroyer)(void*) );
	void	   *list_removeByClosure2( t_list *list, int (*closure)(void*) );
	int     	list_size( t_list *list );
	int     	list_isEmpty( t_list *list );
	void 		list_clean( t_list *list, void (*data_destroyer)(void*) );
	void 		list_destroy( t_list *list, void (*data_destroyer)(void*) );

#endif /*LIST_H_*/

