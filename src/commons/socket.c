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

#include "socket.h"

#include <arpa/inet.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>

static int _socket_send_flags(void);

int socket_send_all(int socket_fd, const void *data, uint32_t size) {
	uint32_t bytes_sent = 0;

	while (bytes_sent < size) {
		ssize_t result = send(socket_fd, (char*) data + bytes_sent, size - bytes_sent, _socket_send_flags());

		if (result == -1 && errno == EINTR) {
			continue;
		}

		if (result <= 0) {
			return -1;
		}

		bytes_sent += result;
	}

	return 0;
}

int socket_recv_all(int socket_fd, void *data, uint32_t size) {
	uint32_t bytes_received = 0;

	while (bytes_received < size) {
		ssize_t result = recv(socket_fd, (char*) data + bytes_received, size - bytes_received, 0);

		if (result == -1 && errno == EINTR) {
			continue;
		}

		if (result <= 0) {
			return -1;
		}

		bytes_received += result;
	}

	return 0;
}

int socket_send_buffer(int socket_fd, t_buffer *buffer) {
	uint32_t network_size = htonl(buffer->size);

	if (socket_send_all(socket_fd, &network_size, sizeof(network_size)) == -1) {
		return -1;
	}

	return socket_send_all(socket_fd, buffer->stream, buffer->size);
}

t_buffer *socket_recv_buffer(int socket_fd) {
	uint32_t network_size;

	if (socket_recv_all(socket_fd, &network_size, sizeof(network_size)) == -1) {
		return NULL;
	}

	uint32_t size = ntohl(network_size);
	t_buffer *buffer = buffer_create_with_size(size);

	if (socket_recv_all(socket_fd, buffer->stream, size) == -1) {
		buffer_destroy(buffer);
		return NULL;
	}

	return buffer;
}

static int _socket_send_flags(void) {
#ifdef MSG_NOSIGNAL
	return MSG_NOSIGNAL;
#else
	return 0;
#endif
}
