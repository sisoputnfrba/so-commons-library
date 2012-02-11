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

#ifndef COLLECTIONS_H_
#define COLLECTIONS_H_


	struct link_element{
		void *data;
		struct link_element *next;
	};
	typedef struct link_element t_link_element;

	struct dlink_element{
		struct dlink_element *previous;
		void *data;
		struct dlink_element *next;
	};
	typedef struct dlink_element t_dlink_element;

#endif /*COLLECTIONS_H_*/
