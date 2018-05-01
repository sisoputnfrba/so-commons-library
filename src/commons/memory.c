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

#include "memory.h"

char *mem_hexstring(void *source, size_t length) {
  char *dump = string_new();
  // The dump_length should be the closes multiple of HEXDUMP_COLS after length
  unsigned int dump_length = length, mem_index = 0;
  if(length % HEXDUMP_COLS) {
    dump_length += HEXDUMP_COLS - length % HEXDUMP_COLS;
  }

  while(mem_index < dump_length)  {
    // Adds initial offset (0x00000: )
    if (mem_index % HEXDUMP_COLS == 0) {
      string_append_with_format(&dump, "\n0x%08x: ", mem_index);
    }
    // Adds hex data (00 00 00 00 00...)
    if (mem_index < length) {
      string_append_with_format(&dump, "%02x ", 0xFF & ((char *)source)[mem_index]);
    } else { // No more blocks to dump, so it adds 00
      string_append(&dump, "00 ");
    }
    // Adds an extra space if hex data is the last column of HEXDUMP_COLS_SEP
    if (mem_index % HEXDUMP_COLS_SEP == (HEXDUMP_COLS_SEP -1)) {
      string_append(&dump, " ");
    }
    // Adds ASCII dump if last column
    if (mem_index % HEXDUMP_COLS == (HEXDUMP_COLS - 1)) {
      unsigned int ascii_iterator = mem_index - (HEXDUMP_COLS - 1);
      string_append(&dump, "|");
      while(ascii_iterator <= mem_index) {
        if (ascii_iterator >= length) { // No more blocks to dump, so it adds .
          string_append(&dump, ".");
        } else if (isprint(((char *)source)[ascii_iterator])) { // Is printable char
          string_append_with_format(&dump, "%c", 0xFF & ((char *)source)[ascii_iterator]);
        }
        else { // Non printable chars
          string_append(&dump, ".");
        }
        ascii_iterator++;
      }
      string_append(&dump, "|");
    }
    mem_index++;
  }
  return dump;
}

void mem_hexdump(void *source, size_t length) {
  char *dump_string = mem_hexstring(source, length);
  printf("%s\n", dump_string);
  free(dump_string);
}