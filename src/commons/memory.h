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

#ifndef MEMORY_H_
#define MEMORY_H_

	#include <stdlib.h>
	#include <stdio.h>
	#include <ctype.h>
	#include "string.h"

	/**
	 * @file
	 * @brief `#include <commons/memory.h>`
	 */

	/* amount of hex columns of dump */
	#define HEXDUMP_COLS 16
	/* amount of hex columns allow without a separator */
	#define HEXDUMP_COLS_SEP 8

	/**
	 * @brief Dada una porción de memoria, devuelve un dump hexadecimal en formato
	 *        string de tres columnas `offset: hexdump |ascii|`.
	 * @return Un string con el dump hexadecimal. Debe ser liberado con `free()`
	 *
	 * @code
	 * char *dump = mem_hexstring("Hello World", 12);
	 *
	 * => "
	 * 0x00000000: 48 65 6c 6c 6f 20 57 6f  72 6c 64 00              |Hello World.|"
	 * @endcode
	 *
	 * @note Este formato es similar al comando `hexdump -C` de Linux.
	 */
	char *mem_hexstring(void *source, size_t length);

	/**
	 * @brief Dada una porción de memoria, imprime un dump hexadecimal
	 *        de tres columnas `offset: hexdump |ascii|`, análogo a imprimir
	 *        el resultado de `mem_hexstring()`.
	 */
	void mem_hexdump(void *source, size_t length);

	/**
	 * @brief Convierte una porción de memoria en un string hexadecimal plano.
	 * @return Un string con el dump hexadecimal. Debe ser liberado con `free()`
	 *
	 * @code
	 * char *dump = mem_hexstring_plain("Hello World", 12);
	 *
	 * => "48656c6c6f20576f726c6400"
	 * @endcode
	 *
	 * @note Este formato es similar al comando `xxd -p` de Linux.
	 */
	char *mem_hexstring_plain(void *source, size_t length);

#endif /* MEMORY_H_ */
