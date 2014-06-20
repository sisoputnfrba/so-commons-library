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

#include <stdlib.h>
#include "bitarray.h"

t_bitarray *bitarray_create(char *bitarray, size_t size) {
	t_bitarray *self = malloc(sizeof(t_bitarray));

	self->bitarray = bitarray;
	self->size = size;

	return self;
}

bool bitarray_test_bit(t_bitarray *self, off_t bit_index) {
	return((self->bitarray[BIT_CHAR(bit_index)] & BIT_IN_CHAR(bit_index)) != 0);
}

void bitarray_set_bit(t_bitarray *self, off_t bit_index) {
	self->bitarray[BIT_CHAR(bit_index)] |= BIT_IN_CHAR(bit_index);
}

void bitarray_clean_bit(t_bitarray *self, off_t bit_index){
    unsigned char mask;

    /* create a mask to zero out desired bit */
    mask =  BIT_IN_CHAR(bit_index);
    mask = ~mask;

    self->bitarray[BIT_CHAR(bit_index)] &= mask;
}

size_t bitarray_get_max_bit(t_bitarray *self) {
	return self->size * CHAR_BIT;
}

void bitarray_destroy(t_bitarray *self) {
	free(self);
}
