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

#ifndef BITARRAY_H_
#define BITARRAY_H_

	#include <stdbool.h>
	#include <limits.h>
	#include <unistd.h>

	/* position of bit within character */
	#define BIT_CHAR(bit)         ((bit) / CHAR_BIT)

	/* array index for character containing bit */
	#define BIT_IN_CHAR(bit)      (0x80 >> (CHAR_BIT - 1 - ((bit)  % CHAR_BIT)))


	typedef struct {
		char *bitarray;
		size_t size;
	} t_bitarray;

	/**
	* @NAME: bitarray_create
	* @DESC: Crea y devuelve un puntero a una estructura t_bitarray
	* @PARAMS:
	* 		bitarray
	*		size - Tamaño en bytes del bit array
	*/
	t_bitarray 	*bitarray_create(char *bitarray, size_t size);

	/**
	* @NAME: bitarray_test_bit
	* @DESC: Devuelve el valor del bit de la posicion indicada
	*/
	bool 		 bitarray_test_bit(t_bitarray*, off_t bit_index);

	/**
	* @NAME: bitarray_set_bit
	* @DESC: Setea el valor del bit de la posicion indicada
	*/
	void		 bitarray_set_bit(t_bitarray*, off_t bit_index);

	/**
	* @NAME: bitarray_clean_bit
	* @DESC: Limpia el valor del bit de la posicion indicada
	*/
	void		 bitarray_clean_bit(t_bitarray*, off_t bit_index);

	/**
	* @NAME: bitarray_get_max_bit
	* @DESC: Devuelve la cantidad de bits en el bitarray
	*/
	size_t		 bitarray_get_max_bit(t_bitarray*);

	/**
	* @NAME: bitarray_destroy
	* @DESC: Destruye el bit array
	*/
	void 		 bitarray_destroy(t_bitarray*);

#endif /* BITARRAY_H_ */
