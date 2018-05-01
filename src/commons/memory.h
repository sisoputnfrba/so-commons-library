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

  /* amount of hex columns of dump */
  #define HEXDUMP_COLS 16
  /* amount of hex columns allow without a separator */
  #define HEXDUMP_COLS_SEP 8
  /**
    * @NAME: mem_hexstring
    * @DESC: Devuelve un dump hexadecimal en formato string de una porción de memoria dada
    */
  char *mem_hexstring(void *source, size_t length);

  /**
    * @NAME: mem_hexdump
    * @DESC: Imprime un dump hexadecimal por pantalla de una porción de memoria dada
    */
  void mem_hexdump(void *source, size_t length);

#endif /* MEMORY_H_ */
