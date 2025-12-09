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

#include <commons/crypto.h>
#include <stdlib.h>
#include <string.h>
#include <cspecs/cspec.h>

context (test_crypto) {

    describe ("Stringified md5") {
        char *memory = "SisopCommonsLibrary";

        it ("return an md5 hash string in ASCII format") {
            char *result = crypto_md5(memory, strlen(memory));

            should_string( result ) be equal to("ec3a8b7e4372dbaac40ef769f8c171ce");

            free(result);
        } end

    } end
}
