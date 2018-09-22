/*
 * Copyright (C) 2018 Sistemas Operativos - UTN FRBA. All rights reserved.
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

#include <commons/memory.h>
#include <stdlib.h>
#include <string.h>
#include <cspecs/cspec.h>

/**
 * TODO: This tests are 8-BIT dependant. We should think of a way to abstract them.
 * TODO: Can we abstract the LSB and MSB tests so they get unified?
 */
context (test_memory) {

    describe ("Stringified Hexstring") {

        char *memory = "Hexdump";
        char *dumped_format = "\n0x00000000: 48 65 78 64 75 6d 70 00  00 00 00 00 00 00 00 00  |Hexdump.........|";

        it ("return a string with hexdump format") {
            char *result = mem_hexstring(memory, strlen(memory));

            should_string( result ) be equal to(dumped_format);

            free(result);
        } end

    } end

    describe ("Stream Hexstring") {

        char *dumped_format = "\n0x00000000: 05 00 00 00 48 65 78 64  75 6d 70 78 00 00 00 00  |....Hexdumpx....|";

        it ("return a string with hexdump format") {
            int first_data = 5; // Como "05 00 00 00" Debido al endianess
            char *string = "Hexdump";
            int second_data = 120; // As "78 00 00 00 00" -> 78 == 'x'
            int total_size = sizeof(int) + strlen(string) + sizeof(int);
            char *stream = calloc(sizeof(char), total_size);

            memcpy(stream, &first_data, sizeof(int));
            memcpy(stream + sizeof(int), string, strlen(string));
            memcpy(stream + sizeof(int) + strlen(string), &second_data, sizeof(int));

            char *result = mem_hexstring(stream, total_size);

            should_string( result ) be equal to(dumped_format);

            free(stream);
            free(result);
        } end

    } end
}
