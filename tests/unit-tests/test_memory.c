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
        char *memory = "SisopCommonsLibrary";

        char *plain_format = "5369736f70436f6d6d6f6e734c696272617279";

        char *dumped_format =
            "\n0x00000000: 53 69 73 6f 70 43 6f 6d  6d 6f 6e 73 4c 69 62 72  |SisopCommonsLibr|"
            "\n0x00000010: 61 72 79 00                                       |ary.............|";

        it ("return a string with plain hexdump format") {
            char *result = mem_hexstring_plain(memory, strlen(memory));

            should_string( result ) be equal to(plain_format);

            free(result);
        } end

        it ("return a string with canonical hex+ASCII hexdump format") {
            char *result = mem_hexstring(memory, strlen(memory) + 1);

            should_string( result ) be equal to(dumped_format);

            free(result);
        } end

    } end

    describe ("Stream Hexstring") {
        unsigned char stream[] = {
            5, 0, 0, 0, // integer 5 in little-endian
            'H', 'e', 'x', 'd', 'u', 'm', 'p', // "Hexdump" string
            120, 0, 0, 0 // integer 120 in little-endian
        };

        char *plain_format = "0500000048657864756d7078000000";
        char *dumped_format = "\n0x00000000: 05 00 00 00 48 65 78 64  75 6d 70 78 00 00 00     |....Hexdumpx....|";

        it ("return a string with plain hexdump format") {
            char *result = mem_hexstring_plain(stream, sizeof stream);

            should_string( result ) be equal to(plain_format);

            free(result);
        } end

        it ("return a string with canonical hex+ASCII hexdump format") {
            char *result = mem_hexstring(stream, sizeof stream);

            should_string( result ) be equal to(dumped_format);

            free(result);
        } end

    } end
}
