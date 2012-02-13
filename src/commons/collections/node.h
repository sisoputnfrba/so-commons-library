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

#ifndef NODE_H_
#define NODE_H_


	struct link_element{
		void *data;
		struct link_element *next;
	};
	typedef struct link_element t_link_element;

	struct double_link_element{
		struct double_link_element *previous;
		void *data;
		struct double_link_element *next;
	};
	typedef struct double_link_element t_double_link_element;

	struct hash_element{
		char *key;
		unsigned int hashcode;
		void *data;
		struct hash_element *next;
	};
	typedef struct hash_element t_hash_element;

#endif /*NODE_H_*/
