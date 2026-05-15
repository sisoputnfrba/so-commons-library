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

#include <commons/serialization.h>
#include <commons/socket.h>
#include <commons/string.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cspecs/cspec.h>

typedef struct {
	char *name;
	uint32_t age;
} t_serialized_person;

static t_serialized_person *serialized_person_create(char *name, uint32_t age) {
	t_serialized_person *person = malloc(sizeof(t_serialized_person));
	person->name = string_duplicate(name);
	person->age = age;
	return person;
}

static void serialized_person_destroy(void *element) {
	t_serialized_person *person = element;
	free(person->name);
	free(person);
}

static void serialized_person_serialize(t_buffer *buffer, void *element) {
	t_serialized_person *person = element;
	buffer_write_string(buffer, person->name);
	buffer_write_uint32(buffer, person->age);
}

static void *serialized_person_deserialize(t_buffer *buffer) {
	char *name = buffer_read_string(buffer);
	uint32_t age = buffer_read_uint32(buffer);
	t_serialized_person *person = serialized_person_create(name, age);
	free(name);
	return person;
}

context (test_serialization) {

	describe ("Serialization buffer") {

		it ("serializes fixed-size values in network byte order") {
			t_buffer *buffer = buffer_create();
			unsigned char expected[] = { 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc };

			buffer_write_uint16(buffer, 0x1234);
			buffer_write_uint32(buffer, 0x56789abc);

			should_int(buffer->size) be equal to((int) sizeof(expected));
			should_int(memcmp(buffer->stream, expected, sizeof(expected))) be equal to(0);

			buffer_destroy(buffer);
		} end

		it ("writes and reads primitive values") {
			t_buffer *buffer = buffer_create();

			buffer_write_uint8(buffer, 0xab);
			buffer_write_uint16(buffer, 0x1234);
			buffer_write_uint32(buffer, 0x12345678);
			buffer_write_int32(buffer, -42);
			buffer_write_bool(buffer, true);
			buffer_write_bool(buffer, false);

			buffer_reset(buffer);

			should_int(buffer_read_uint8(buffer)) be equal to(0xab);
			should_int(buffer_read_uint16(buffer)) be equal to(0x1234);
			should_int(buffer_read_uint32(buffer)) be equal to(0x12345678);
			should_int(buffer_read_int32(buffer)) be equal to(-42);
			should_bool(buffer_read_bool(buffer)) be truthy;
			should_bool(buffer_read_bool(buffer)) be falsey;

			buffer_destroy(buffer);
		} end

		it ("writes and reads strings") {
			t_buffer *buffer = buffer_create();

			buffer_write_string(buffer, "hola");
			buffer_reset(buffer);

			char *value = buffer_read_string(buffer);

			should_string(value) be equal to("hola");

			free(value);
			buffer_destroy(buffer);
		} end

		it ("writes and reads arbitrary bytes") {
			t_buffer *buffer = buffer_create();
			unsigned char payload[] = { 0x00, 0x01, 0x02, 0xff };

			buffer_write_bytes(buffer, payload, sizeof(payload));
			buffer_reset(buffer);

			uint32_t size;
			unsigned char *result = buffer_read_bytes(buffer, &size);

			should_int(size) be equal to((int) sizeof(payload));
			should_int(memcmp(result, payload, sizeof(payload))) be equal to(0);

			free(result);
			buffer_destroy(buffer);
		} end

		it ("serializes lists using callbacks") {
			t_list *people = list_create();
			list_add(people, serialized_person_create("Ada", 36));
			list_add(people, serialized_person_create("Linus", 55));

			t_buffer *buffer = buffer_create();
			buffer_write_list(buffer, people, serialized_person_serialize);
			buffer_reset(buffer);

			t_list *result = buffer_read_list(buffer, serialized_person_deserialize);
			t_serialized_person *first = list_get(result, 0);
			t_serialized_person *second = list_get(result, 1);

			should_int(list_size(result)) be equal to(2);
			should_string(first->name) be equal to("Ada");
			should_int(first->age) be equal to(36);
			should_string(second->name) be equal to("Linus");
			should_int(second->age) be equal to(55);

			list_destroy_and_destroy_elements(result, serialized_person_destroy);
			buffer_destroy(buffer);
			list_destroy_and_destroy_elements(people, serialized_person_destroy);
		} end
	} end

	describe ("Serialization socket helpers") {

		it ("sends and receives exact byte streams") {
			int sockets[2];
			should_int(socketpair(AF_UNIX, SOCK_STREAM, 0, sockets)) be equal to(0);

			unsigned char outgoing[] = { 0x10, 0x20, 0x30, 0xff };
			unsigned char incoming[sizeof(outgoing)];

			should_int(socket_send_all(sockets[0], outgoing, sizeof(outgoing))) be equal to(0);
			should_int(socket_recv_all(sockets[1], incoming, sizeof(incoming))) be equal to(0);
			should_int(memcmp(incoming, outgoing, sizeof(outgoing))) be equal to(0);

			close(sockets[0]);
			close(sockets[1]);
		} end

		it ("sends and receives a framed buffer") {
			int sockets[2];
			should_int(socketpair(AF_UNIX, SOCK_STREAM, 0, sockets)) be equal to(0);

			t_buffer *outgoing = buffer_create();
			buffer_write_string(outgoing, "socket");
			buffer_write_uint32(outgoing, 2026);

			should_int(socket_send_buffer(sockets[0], outgoing)) be equal to(0);

			t_buffer *incoming = socket_recv_buffer(sockets[1]);
			should_ptr(incoming) not be null;

			char *message = buffer_read_string(incoming);
			uint32_t year = buffer_read_uint32(incoming);

			should_string(message) be equal to("socket");
			should_int(year) be equal to(2026);

			free(message);
			buffer_destroy(incoming);
			buffer_destroy(outgoing);
			close(sockets[0]);
			close(sockets[1]);
		} end

		it ("sends and receives a list of people") {
			int sockets[2];
			should_int(socketpair(AF_UNIX, SOCK_STREAM, 0, sockets)) be equal to(0);

			t_list *people = list_create();
			list_add(people, serialized_person_create("Ada", 36));
			list_add(people, serialized_person_create("Linus", 55));
			list_add(people, serialized_person_create("Grace", 85));

			t_buffer *outgoing = buffer_create();
			buffer_write_list(outgoing, people, serialized_person_serialize);

			should_int(socket_send_buffer(sockets[0], outgoing)) be equal to(0);

			t_buffer *incoming = socket_recv_buffer(sockets[1]);
			should_ptr(incoming) not be null;

			t_list *received_people = buffer_read_list(incoming, serialized_person_deserialize);
			t_serialized_person *first = list_get(received_people, 0);
			t_serialized_person *second = list_get(received_people, 1);
			t_serialized_person *third = list_get(received_people, 2);

			should_int(list_size(received_people)) be equal to(3);
			should_string(first->name) be equal to("Ada");
			should_int(first->age) be equal to(36);
			should_string(second->name) be equal to("Linus");
			should_int(second->age) be equal to(55);
			should_string(third->name) be equal to("Grace");
			should_int(third->age) be equal to(85);

			list_destroy_and_destroy_elements(received_people, serialized_person_destroy);
			buffer_destroy(incoming);
			buffer_destroy(outgoing);
			list_destroy_and_destroy_elements(people, serialized_person_destroy);
			close(sockets[0]);
			close(sockets[1]);
		} end
	} end
}
