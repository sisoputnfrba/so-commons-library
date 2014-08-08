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

#include <commons/bitarray.h>
#include <stdlib.h>
#include <string.h>
#include <cspecs/cspec.h>

context (test_bitarray) {

    describe ("Bitarray") {

        t_bitarray *bitarray;

        after {
            bitarray_destroy(bitarray);
        } end

        it ("should get the bit value at position") {
            char data[] = { 0b10000000, 0, 0b00000001 };
            bitarray = bitarray_create(data, sizeof(data));

            should_bool( bitarray_test_bit(bitarray, 7) ) be truthy;
            should_bool( bitarray_test_bit(bitarray, 1) ) be falsey;
            should_bool( bitarray_test_bit(bitarray, 8 + 8 + 0) ) be truthy;
        } end

        it ("should clean the bit value at position") {
            char BASE_ARRAY[] = { 0, 0, 0 };
            char data[] = { 0, 0, 0b00000001 };
            bitarray = bitarray_create(data, sizeof(data));

            bitarray_clean_bit(bitarray, 8 + 8 + 0);

            should_int( memcmp(BASE_ARRAY, data, sizeof(data)) ) be equal to(0);
        } end

        it ("should set the bit value at position") {
            char BASE_ARRAY[] = { 0b10000000, 0, 0 };
            char data[] = { 0, 0, 0 };
            bitarray = bitarray_create(data, sizeof(data));

            bitarray_set_bit(bitarray, 7);

            should_int( memcmp(BASE_ARRAY, data, sizeof(data))) be equal to(0);
        } end

        it ("should get the bits count") {
            char data[] = { 0, 0, 0 };
            bitarray = bitarray_create(data, sizeof(data));

            should_int( bitarray_get_max_bit(bitarray)) be equal to(8 * 3);
        } end

    } end

}
