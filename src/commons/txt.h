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
* @NAME: txt_open_for_append
* @DESC: Abre un archivo para agregarle contenido al final
*/
FILE* txt_open_for_append(char* path);

/**
* @NAME: txt_write_in_file
* @DESC: Agrega contenido al final del archivo
*/
void txt_write_in_file(FILE* file, char* string);

/**
* @NAME: txt_write_in_stdout
* @DESC: Imprime un mensaje en la salida estandar
*/
void txt_write_in_stdout(char* string);

/**
* @NAME: txt_close_file
* @DESC: Cierra el archivo
*/
void txt_close_file(FILE* file);

#endif /* TXT_H_ */
