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

#ifndef TXT_H_
#define TXT_H_

#include <stdio.h>

/**
 * @file
 * @brief `#include <commons/txt.h>`
 */

/**
* @brief Abre un archivo para agregarle contenido al final
* @note El mismo se debe cerrar con `txt_close_file()`
*/
FILE* txt_open_for_append(char* path);

/**
* @brief Agrega contenido al final del archivo
*/
void txt_write_in_file(FILE* file, char* string);

/**
* @brief Imprime un mensaje en la salida estandar
*/
void txt_write_in_stdout(char* string);

/**
* @brief Cierra el archivo
*/
void txt_close_file(FILE* file);

#endif /* TXT_H_ */
