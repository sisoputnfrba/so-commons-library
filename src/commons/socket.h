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

#ifndef SOCKET_H_
#define SOCKET_H_

	#include <stdint.h>
	#include "serialization.h"

	/**
	 * @file
	 * @brief `#include <commons/socket.h>`
	 */

	/**
	 * @brief Envia exactamente `size` bytes por socket.
	 * @return 0 si pudo enviar todos los bytes, -1 ante error o cierre de conexion.
	 */
	int socket_send_all(int socket_fd, const void *data, uint32_t size);

	/**
	 * @brief Recibe exactamente `size` bytes desde un socket.
	 * @return 0 si pudo recibir todos los bytes, -1 ante error o cierre de conexion.
	 */
	int socket_recv_all(int socket_fd, void *data, uint32_t size);

	/**
	 * @brief Envia un buffer completo por socket como `uint32_t size + payload`.
	 * @return 0 si pudo enviar todo el frame, -1 ante error o cierre de conexion.
	 */
	int socket_send_buffer(int socket_fd, t_buffer *buffer);

	/**
	 * @brief Recibe un frame `uint32_t size + payload` desde un socket.
	 * @return Un buffer liberable con `buffer_destroy()`, o NULL ante error o cierre.
	 */
	t_buffer *socket_recv_buffer(int socket_fd);

#endif /* SOCKET_H_ */
