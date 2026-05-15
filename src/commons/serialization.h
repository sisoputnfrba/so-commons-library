/*
 * Copyright (C) 2026 Sistemas Operativos - UTN FRBA. All rights reserved.
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

#ifndef SERIALIZATION_H_
#define SERIALIZATION_H_

	#include <stdbool.h>
	#include <stdint.h>
	#include <stdlib.h>
	#include "collections/list.h"

	/**
	 * @file
	 * @brief `#include <commons/serialization.h>`
	 */

	/**
	 * @struct t_buffer
	 * @brief Buffer de bytes con cursor de lectura/escritura para serializar datos.
	 *
	 * Los tipos numericos de mas de un byte se serializan en network byte order.
	 *
	 * `stream` y la estructura deben ser liberados con `buffer_destroy()`.
	 */
	typedef struct {
		void *stream;
		uint32_t size;
		uint32_t offset;
	} t_buffer;

	typedef void (*t_buffer_element_serializer)(t_buffer*, void*);
	typedef void* (*t_buffer_element_deserializer)(t_buffer*);

	/**
	 * @brief Crea un buffer vacio.
	 */
	t_buffer *buffer_create(void);

	/**
	 * @brief Crea un buffer con memoria reservada de `size` bytes.
	 *
	 * @note Pensado para buffers recibidos desde un transporte externo.
	 */
	t_buffer *buffer_create_with_size(uint32_t size);

	/**
	 * @brief Libera un buffer y su stream.
	 */
	void buffer_destroy(t_buffer *buffer);

	/**
	 * @brief Reinicia el cursor del buffer al inicio.
	 */
	void buffer_reset(t_buffer *buffer);

	/**
	 * @brief Agrega una porcion de memoria al final del buffer.
	 */
	void buffer_write(t_buffer *buffer, const void *data, uint32_t size);

	void buffer_write_uint8(t_buffer *buffer, uint8_t value);
	void buffer_write_uint16(t_buffer *buffer, uint16_t value);
	void buffer_write_uint32(t_buffer *buffer, uint32_t value);
	void buffer_write_int32(t_buffer *buffer, int32_t value);
	void buffer_write_bool(t_buffer *buffer, bool value);

	/**
	 * @brief Agrega un string como `uint32_t length + bytes`, incluyendo el `\0`.
	 */
	void buffer_write_string(t_buffer *buffer, const char *value);

	/**
	 * @brief Agrega bytes arbitrarios como `uint32_t length + bytes`.
	 */
	void buffer_write_bytes(t_buffer *buffer, const void *data, uint32_t size);

	/**
	 * @brief Serializa una lista como `uint32_t count + elementos`.
	 */
	void buffer_write_list(t_buffer *buffer, t_list *list, t_buffer_element_serializer serializer);

	/**
	 * @brief Lee una porcion de memoria desde la posicion actual del buffer.
	 */
	void buffer_read(t_buffer *buffer, void *destination, uint32_t size);

	uint8_t buffer_read_uint8(t_buffer *buffer);
	uint16_t buffer_read_uint16(t_buffer *buffer);
	uint32_t buffer_read_uint32(t_buffer *buffer);
	int32_t buffer_read_int32(t_buffer *buffer);
	bool buffer_read_bool(t_buffer *buffer);

	/**
	 * @brief Lee un string reservado con `malloc()`. Debe liberarse con `free()`.
	 */
	char *buffer_read_string(t_buffer *buffer);

	/**
	 * @brief Lee bytes arbitrarios reservados con `malloc()`. Deben liberarse con `free()`.
	 */
	void *buffer_read_bytes(t_buffer *buffer, uint32_t *size);

	/**
	 * @brief Deserializa una lista creada con `list_create()`.
	 */
	t_list *buffer_read_list(t_buffer *buffer, t_buffer_element_deserializer deserializer);

#endif /* SERIALIZATION_H_ */
