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

#include "serialization.h"

#include <arpa/inet.h>
#include <string.h>

t_buffer *buffer_create(void) {
	return buffer_create_with_size(0);
}

t_buffer *buffer_create_with_size(uint32_t size) {
	t_buffer *buffer = malloc(sizeof(t_buffer));
	buffer->stream = size > 0 ? calloc(1, size) : NULL;
	buffer->size = size;
	buffer->offset = 0;
	return buffer;
}

void buffer_destroy(t_buffer *buffer) {
	if (buffer == NULL) {
		return;
	}

	free(buffer->stream);
	free(buffer);
}

void buffer_reset(t_buffer *buffer) {
	buffer->offset = 0;
}

void buffer_write(t_buffer *buffer, const void *data, uint32_t size) {
	if (size == 0) {
		return;
	}

	buffer->stream = realloc(buffer->stream, buffer->size + size);
	memcpy((char*) buffer->stream + buffer->size, data, size);
	buffer->size += size;
}

void buffer_write_uint8(t_buffer *buffer, uint8_t value) {
	buffer_write(buffer, &value, sizeof(value));
}

void buffer_write_uint16(t_buffer *buffer, uint16_t value) {
	uint16_t network_value = htons(value);
	buffer_write(buffer, &network_value, sizeof(network_value));
}

void buffer_write_uint32(t_buffer *buffer, uint32_t value) {
	uint32_t network_value = htonl(value);
	buffer_write(buffer, &network_value, sizeof(network_value));
}

void buffer_write_int32(t_buffer *buffer, int32_t value) {
	uint32_t raw_value;
	memcpy(&raw_value, &value, sizeof(raw_value));
	buffer_write_uint32(buffer, raw_value);
}

void buffer_write_bool(t_buffer *buffer, bool value) {
	buffer_write_uint8(buffer, value ? 1 : 0);
}

void buffer_write_string(t_buffer *buffer, const char *value) {
	uint32_t length = strlen(value) + 1;
	buffer_write_uint32(buffer, length);
	buffer_write(buffer, value, length);
}

void buffer_write_bytes(t_buffer *buffer, const void *data, uint32_t size) {
	buffer_write_uint32(buffer, size);
	buffer_write(buffer, data, size);
}

void buffer_write_list(t_buffer *buffer, t_list *list, t_buffer_element_serializer serializer) {
	int elements_count = list_size(list);
	buffer_write_uint32(buffer, elements_count);

	for (int index = 0; index < elements_count; index++) {
		serializer(buffer, list_get(list, index));
	}
}

void buffer_read(t_buffer *buffer, void *destination, uint32_t size) {
	if (size == 0) {
		return;
	}

	memcpy(destination, (char*) buffer->stream + buffer->offset, size);
	buffer->offset += size;
}

uint8_t buffer_read_uint8(t_buffer *buffer) {
	uint8_t value;
	buffer_read(buffer, &value, sizeof(value));
	return value;
}

uint16_t buffer_read_uint16(t_buffer *buffer) {
	uint16_t network_value;
	buffer_read(buffer, &network_value, sizeof(network_value));
	return ntohs(network_value);
}

uint32_t buffer_read_uint32(t_buffer *buffer) {
	uint32_t network_value;
	buffer_read(buffer, &network_value, sizeof(network_value));
	return ntohl(network_value);
}

int32_t buffer_read_int32(t_buffer *buffer) {
	uint32_t raw_value = buffer_read_uint32(buffer);
	int32_t value;
	memcpy(&value, &raw_value, sizeof(value));
	return value;
}

bool buffer_read_bool(t_buffer *buffer) {
	return buffer_read_uint8(buffer) != 0;
}

char *buffer_read_string(t_buffer *buffer) {
	uint32_t length = buffer_read_uint32(buffer);

	if (length == 0) {
		return NULL;
	}

	char *value = calloc(1, length + 1);
	buffer_read(buffer, value, length);
	return value;
}

void *buffer_read_bytes(t_buffer *buffer, uint32_t *size) {
	uint32_t length = buffer_read_uint32(buffer);

	if (size != NULL) {
		*size = length;
	}

	if (length == 0) {
		return NULL;
	}

	void *data = malloc(length);
	buffer_read(buffer, data, length);
	return data;
}

t_list *buffer_read_list(t_buffer *buffer, t_buffer_element_deserializer deserializer) {
	uint32_t elements_count = buffer_read_uint32(buffer);
	t_list *list = list_create();

	for (uint32_t index = 0; index < elements_count; index++) {
		list_add(list, deserializer(buffer));
	}

	return list;
}
