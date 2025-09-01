/*
 * Copyright (C) 2025 Sistemas Operativos - UTN FRBA. All rights reserved.
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

#ifndef CRYPTO_H_
#define CRYPTO_H_

	#include <openssl/evp.h>
	#include "memory.h"

	/**
	 * @file
	 * @brief `#include <commons/crypto.h>`
	 */

	/**
	 * @brief Dada una porción de memoria, calcula su hash MD5 y lo devuelve como
	 *        una cadena de caracteres ASCII.
	 *
	 * @return El hash MD5 en formato hexadecimal, o NULL en caso de error.
	 *         Debe ser liberado con `free()`.
	 *
	 * @code
	 * char *digest = crypto_md5("Hello World", 12);
	 *
	 * => "b10a8db164e0754105b7a99be72e3fe5"
	 * @endcode
	 */
	char *crypto_md5(void *source, size_t length);

#endif /* CRYPTO_H_ */
