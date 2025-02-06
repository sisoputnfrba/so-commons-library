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

#ifndef vector_h__
#define vector_h__

#include <stdbool.h>
#include <stddef.h>

/*
 * Función de liberación de elemento (free o similar)
 */
typedef void (*VectorFreeFn)(void* element);

/*
 * Función que recorre elementos
 */
typedef void (*VectorClosureFn)(void* element);

typedef struct
{
    void* Elements;
    size_t ElemSize;
    size_t Size;
    size_t Capacity;
    VectorFreeFn FreeFn;
} vector;

/*
 * Inicializador estático (à la pthreads) para la muy utilizada abstracción "vector de strings"
 */
void _vector_of_strings_free_fn(void* pstr);

#define VECTOR_OF_STRINGS_INITIALIZER \
    { NULL, sizeof(char*), 0, 0, _vector_of_strings_free_fn }

/**
 * @NAME: vector_construct
 * @DESC: Construye un nuevo vector in-place
 * elementSize: tamaño de los elementos que guardara el vector normalmente sizeof(tipo-elemento)
 * freeFn: funcion llamada para destruir los elementos en sí, si es distinta a NULL 
 * initialCapacity: reserva inicial de memoria para guardar 'initialCapacity' elementos (puede ser 0)
 */
void vector_construct(vector* v, size_t elementSize, VectorFreeFn freeFn, size_t initialCapacity);

/**
 * @NAME: vector_destruct
 * @DESC: Libera la memoria reservada por las estructuras
 * destruyendo los elementos con la funcion pasada como parametro al construir, si no es NULL
 */
void vector_destruct(vector* v);

// C++ like interface

/**
 * @NAME: vector_size
 * @DESC: Devuelve tamaño del vector
 */
size_t vector_size(vector const* v);

/**
 * @NAME: vector_resize
 * @DESC: Cambia el tamaño del vector eliminando o insertando elementos
 * Los elementos insertados serán copias del elemento pasado por parámetro
 */
void vector_resize(vector* v, size_t n, void const* elem);

/**
 * @NAME: vector_resize_zero
 * @DESC: Cambia el tamaño del vector eliminando o insertando elementos
 * Los elementos insertados serán inicializados en 0
 */
void vector_resize_zero(vector* v, size_t n);

/**
 * @NAME: vector_capacity
 * @DESC: Devuelve capacidad actual de elementos
 */
size_t vector_capacity(vector const* v);

/**
 * @NAME: vector_empty
 * @DESC: Devuelve true ssi el vector está vacio
 */
bool vector_empty(vector const* v);

/**
 * @NAME: vector_reserve
 * @DESC: Se asegura que la capacidad alocada sea de al menos n elementos
 * No cambia ningún elemento actual
 */
void vector_reserve(vector* v, size_t n);

/**
 * @NAME: vector_shrink_to_fit
 * @DESC: Encoge la capacidad del vector de forma tal que sólo quepan
 * sus elementos actuales. A diferencia del estándar, siempre efectúa la operación
 * en caso de ser necesaria.
 */
void vector_shrink_to_fit(vector* v);

/**
 * @NAME: vector_at
 * @DESC: Devuelve el elemento en la posición i-ésima.
 */
void* vector_at(vector const* v, size_t i);

/**
 * @NAME: vector_front
 * @DESC: Devuelve el primer elemento
 */
void* vector_front(vector const* v);

/**
 * @NAME: vector_back
 * @DESC: Devuelve el último elemento
 */
void* vector_back(vector const* v);

/**
 * @NAME: vector_data
 * @DESC: Devuelve el arreglo de datos
 */
void* vector_data(vector const* v);

/**
 * @NAME: vector_push_back
 * @DESC: Inserta un elemento al final
 */
void vector_push_back(vector* v, void const* elem);

/**
 * @NAME: vector_pop_back
 * @DESC: Elimina el último elemento
 */
void vector_pop_back(vector* v);

/**
 * @NAME; vector_insert
 * @DESC: Inserta un único valor en la posición 'pos'
 */
void vector_insert(vector* v, size_t pos, void const* elem);

/**
 * @NAME: vector_insert_fill
 * @DESC: Inserta n copias del elemento elem a partir de la posición 'pos'
 */
void vector_insert_fill(vector* v, size_t pos, size_t n, void const* elem);

/**
 * @NAME: vector_insert_range
 * @DESC: Inserta valores desde un arreglo, entre la posicion begin, hasta la end exclusive
 * En otras palabras, rango cerrado abierto [begin, end)
 */
void vector_insert_range(vector* v, size_t pos, void* begin, void* end);

/**
 * @NAME: vector_erase
 * @DESC: Borra el elemento ubicado en 'pos'
 */
void vector_erase(vector* v, size_t pos);

/**
 * @NAME: vector_erase_range
 * @DESC: Borra los elementos en el rango de posiciones cerrado abierto [begin, end)
 */
void vector_erase_range(vector* v, size_t begin, size_t end);

/**
 * @NAME: vector_swap
 * @DESC: Intercambia contenidos con otro vector
 */
void vector_swap(vector* v, vector* other);

/**
 * @NAME: vector_clear
 * @DESC: Limpia los elementos
 */
void vector_clear(vector* v);

// Non-C++ interface
/**
 * @NAME: vector_iterate
 * @DESC: Itera los elementos con una función
 */
void vector_iterate(vector const* v, VectorClosureFn closureFn);

#endif //vector_h__
