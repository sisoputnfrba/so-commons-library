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
#include <string.h>
#include <cspecs/cspec.h>

/**
 * TODO: This tests are 8-BIT dependant. We should think of a way to abstract them.
 * TODO: Can we abstract the LSB and MSB tests so they get unified?
 */
context (test_memory) {

    describe ("Memory Hexstring") {

        char *memory = "Hexdump";
        char *dumped_format = "0x00000000 48 65 78 64 75 6d 70 00  00 00 00 00 00 00 00 00 00  |Hexdump.........|"

        it ("return a string with hexdump format") {
            should( mem_hexstring(memory, strlen(memory)) ) be_string equal(dumpled_format);
        } end

    } end

}
