/*
 * Copyright (C) 2019 Sistemas Operativos - UTN FRBA. All rights reserved.
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

#include "vector.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void _vector_of_strings_free_fn(void* pstr)
{
    char** string = pstr;
    free(*string);
}

inline static void* _calculateOffset(void* array, size_t pos, size_t elemSize)
{
    return ((char*) array) + pos * elemSize;
}

inline static size_t _calculateGrowth(vector const* v, size_t newSize)
{
    size_t geometric = v->Capacity + v->Capacity / 2;
    if (geometric < newSize)
        return newSize;
    return geometric;
}

void vector_construct(vector* v, size_t elementSize, VectorFreeFn freeFn, size_t initialCapacity)
{
    v->Elements = NULL;
    v->ElemSize = elementSize;
    v->Size = 0;
    v->Capacity = initialCapacity;
    if (initialCapacity)
        v->Elements = malloc(initialCapacity * elementSize);
    v->FreeFn = freeFn;
}

size_t vector_size(vector const* v)
{
    return v->Size;
}

void vector_resize(vector* v, size_t n, void const* elem)
{
    size_t oldsize = v->Size;

    if (n < oldsize)
        vector_erase_range(v, n, v->Size);
    else if (n > oldsize)
    {
        vector_reserve(v, n);

        // fill rest with elem
        vector_insert_fill(v, oldsize, n - oldsize, elem);
    }
}

void vector_resize_zero(vector* v, size_t n)
{
    size_t oldsize = v->Size;
    if (n < oldsize)
        vector_erase_range(v, n, v->Size);
    else
    {
        vector_reserve(v, n);

        memset(_calculateOffset(v->Elements, oldsize, v->ElemSize), 0, (n - oldsize) * v->ElemSize);
        v->Size = n;
    }
}

size_t vector_capacity(vector const* v)
{
    return v->Capacity;
}

bool vector_empty(vector const* v)
{
    return !v->Size;
}

void vector_reserve(vector* v, size_t n)
{
    if (n <= v->Capacity)
        return;

    v->Elements = realloc(v->Elements, n * v->ElemSize);
    v->Capacity = n;
}

void vector_shrink_to_fit(vector* v)
{
    if (v->Capacity == v->Size)
        return;

    if (!v->Size)
    {
        free(v->Elements);
        v->Elements = NULL;
        v->Capacity = 0;
    }
    else
    {
        v->Elements = realloc(v->Elements, v->Size * v->ElemSize);
        v->Capacity = v->Size;
    }
}

void* vector_at(vector const* v, size_t i)
{
    assert(v->Elements && i < v->Size);
    return _calculateOffset(v->Elements, i, v->ElemSize);
}

void* vector_front(vector const* v)
{
    assert(v->Elements);
    return _calculateOffset(v->Elements, 0, v->ElemSize);
}

void* vector_back(vector const* v)
{
    assert(v->Elements && v->Size);
    return vector_at(v, v->Size - 1);
}

void* vector_data(vector const* v)
{
    return v->Elements;
}

void vector_push_back(vector* v, void const* elem)
{
    if (v->Capacity == v->Size)
        vector_reserve(v, _calculateGrowth(v, v->Size + 1));

    memcpy(_calculateOffset(v->Elements, v->Size, v->ElemSize), elem, v->ElemSize);
    ++v->Size;
}

void vector_pop_back(vector* v)
{
    assert(v->Size);
    vector_erase(v, v->Size - 1);
}

void vector_insert(vector* v, size_t pos, void const* elem)
{
    vector_insert_fill(v, pos, 1, elem);
}

void vector_insert_fill(vector* v, size_t pos, size_t n, void const* elem)
{
    assert(pos <= v->Size);
    if (n == 1 && pos == v->Size) // special case
    {
        vector_push_back(v, elem);
        return;
    }

    if (n > (v->Capacity - v->Size))
        vector_reserve(v, _calculateGrowth(v, v->Size + n));

    void* start = _calculateOffset(v->Elements, pos, v->ElemSize);
    void* end = _calculateOffset(v->Elements, pos + n, v->ElemSize);
    size_t const blockSize = (v->Size - pos) * v->ElemSize;

    memmove(end, start, blockSize);
    for (size_t i = 0; i < n; ++i)
        memcpy(_calculateOffset(start, i, v->ElemSize), elem, v->ElemSize);
    v->Size += n;
}

void vector_insert_range(vector* v, size_t pos, void* begin, void* end)
{
    assert(pos <= v->Size);
    if (begin == end)
        return;

    size_t n = ((char*)end - (char*)begin) / v->ElemSize;
    if (n == 1 && pos == v->Size) // special case
    {
        vector_push_back(v, begin);
        return;
    }

    if (n > (v->Capacity - v->Size))
        vector_reserve(v, _calculateGrowth(v, v->Size + n));

    void* shiftSrc = _calculateOffset(v->Elements, pos, v->ElemSize);
    void* shiftDst = _calculateOffset(v->Elements, pos + n, v->ElemSize);
    size_t const blockSize = (v->Size - pos) * v->ElemSize;

    if (blockSize)
        memmove(shiftDst, shiftSrc, blockSize);

    memcpy(shiftSrc, begin, n * v->ElemSize);
    v->Size += n;
}

void vector_erase(vector* v, size_t pos)
{
    assert(pos < v->Size);
    vector_erase_range(v, pos, pos + 1);
}

void vector_erase_range(vector* v, size_t begin, size_t end)
{
    assert(begin < v->Size);
    assert(end <= v->Size);

    size_t n = end - begin;
    if (v->FreeFn)
    {
        for (size_t i = begin; i < end; ++i)
            v->FreeFn(_calculateOffset(v->Elements, i, v->ElemSize));
    }

    // shift needed
    if (end < v->Size)
    {
        void* shiftSrc = _calculateOffset(v->Elements, end, v->ElemSize);
        void* shiftDst = _calculateOffset(v->Elements, begin, v->ElemSize);
        size_t const blockSize = (v->Size - end) * v->ElemSize;
        memmove(shiftDst, shiftSrc, blockSize);
    }

    v->Size -= n;
}

void vector_swap(vector* v, vector* other)
{
    //POD should copy
    vector me = *v;
    *v = *other;
    *other = me;
}

void vector_clear(vector* v)
{
    if (v->FreeFn)
        vector_iterate(v, v->FreeFn);
    v->Size = 0;
}

void vector_iterate(vector const* v, VectorClosureFn closureFn)
{
    for (size_t i = 0; i < v->Size; ++i)
        closureFn(_calculateOffset(v->Elements, i, v->ElemSize));
}

void vector_destruct(vector* v)
{
    if (v->FreeFn)
        vector_iterate(v, v->FreeFn);
    free(v->Elements);
}
