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

	/**
	 * @brief Define el orden bajo el cual se guardarán los bits a la hora de llenar los bytes.
	 * @note  La mayoría de las implementaciones de bitmap usan LSB_FIRST. Si no estás seguro
	 *        de cuál usar, probablemente quieras usar esta.
	 */
	typedef enum {
		/**
		 *  @brief   Completa los bits en un byte priorizando el bit menos significativo:
		 *  @example 00000001 00000000
		 */
		LSB_FIRST,
		/**
		 *  @brief   Completa los bits en un byte priorizando el bit más significativo:
		 *  @example 10000000 00000000
		 */
		MSB_FIRST
	} bit_numbering_t;

	typedef struct {
		char *bitarray;
		size_t size;
		bit_numbering_t mode;
	} t_bitarray;

	/**
	* @deprecated Esta función se encuentra en revisión y probablemente cambie en próximas versiones.
	*             Usar bitarray_create_with_mode.
	*
	* @fn    bitarray_create
	* @brief Crea y devuelve un puntero a una estructura t_bitarray con formato LSB_FIRST
	*
	* @param bitarray El bloque de memoria que contiene los bits a leer/escribir
	* @param size     La cantidad de bits del bitarray, expresada en bytes (1 byte = 8 bits)
	*
	* @example bitarray de 8 posiciones (bits),
	* @code
	* void* puntero_a_bits = //un byte de memoria, como por ejemplo malloc(1)
	* bitarray_create(puntero_a_bits, 1)
	* @endcode
	*/
	t_bitarray 	*bitarray_create(char *bitarray, size_t size) __attribute__((deprecated));

	/**
	* @fn    bitarray_create_with_mode
	* @brief Crea y devuelve un puntero a una estructura t_bitarray
	*
	* @param bitarray El bloque de memoria que contiene los bits a leer/escribir
	* @param size     La cantidad de bits del bitarray, expresada en bytes (1 byte = 8 bits)
	* @param mode     LSB_FIRST o MSB_FIRST @see bit_numbering_t
	*
	* @example bitarray de 8 posiciones (bits) con LSB_FIRST,
	* @code
	* void* puntero_a_bits = //un byte de memoria, como por ejemplo malloc(1)
	* bitarray_create_with_mode(puntero_a_bits, 1, LSB_FIRST)
	* @endcode
	*/
	t_bitarray	*bitarray_create_with_mode(char *bitarray, size_t size, bit_numbering_t mode);

	/**
	* @fn    bitarray_test_bit
	* @brief Devuelve el valor del bit de la posicion indicada
	*/
	bool 		 bitarray_test_bit(t_bitarray*, off_t bit_index);

	/**
	* @fn    bitarray_set_bit
	* @brief Setea el valor del bit de la posicion indicada
	*/
	void		 bitarray_set_bit(t_bitarray*, off_t bit_index);

	/**
	* @fn    bitarray_clean_bit
	* @brief Limpia el valor del bit de la posicion indicada
	*/
	void		 bitarray_clean_bit(t_bitarray*, off_t bit_index);

	/**
	* @fn    bitarray_get_max_bit
	* @brief Devuelve la cantidad de bits en el bitarray
	*/
	size_t		 bitarray_get_max_bit(t_bitarray*);

	/**
	* @fn    bitarray_destroy
	* @brief Destruye el bit array
	*/
	void 		 bitarray_destroy(t_bitarray*);

#endif /* BITARRAY_H_ */
