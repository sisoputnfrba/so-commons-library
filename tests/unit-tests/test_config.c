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

#include <commons/config.h>
#include <commons/string.h>
#include <cspecs/cspec.h>
#include <stdlib.h>
#include <string.h>

#define KEYS_AMOUNT 6
#define PATH_CONFIG "resources/config.cfg"

context (test_config) {

    void _assert_equals_array(char** expected, char** actual, int size) {
        int i;
        for (i = 0; i < size; i++) {
            should_string(actual[i]) be equal to(expected[i]);
        }
        should_ptr(actual[i]) be null;
    }

    describe("Config") {

        t_config* config;

        before {
            config = config_create(PATH_CONFIG);
        } end

        after {
            config_destroy(config);
        } end

        it("read") {

            should_int(config_keys_amount(config)) be equal to(KEYS_AMOUNT);

            should_bool(config_has_property(config, "IP")) be truthy;
            should_string(config_get_string_value(config, "IP")) be equal to("127.0.0.1");

            should_bool(config_has_property(config, "PORT")) be truthy;
            should_int(config_get_int_value(config, "PORT")) be equal to(8080);

            should_bool(config_has_property(config, "LOAD")) be truthy;
            should_double(config_get_double_value(config, "LOAD")) be equal to (0.5);

        } end

        it("read with empty array") {
            char* empty_array_expected[] = {NULL};

            should_int(config_keys_amount(config)) be equal to(KEYS_AMOUNT);

            should_bool(config_has_property(config, "EMPTY_ARRAY")) be truthy;
            should_string(config_get_string_value(config, "EMPTY_ARRAY")) be equal to("[]");

            char** empty_array  = config_get_array_value(config, "EMPTY_ARRAY");
            _assert_equals_array(empty_array_expected, empty_array, 0);

            free(empty_array);
        } end

        it("read array with values") {
            char* numbers_expected[] = {"1", "2", "3", "4", "5", NULL};

            should_int(config_keys_amount(config)) be equal to(KEYS_AMOUNT);

            should_bool(config_has_property(config, "NUMBERS")) be truthy;
            should_string(config_get_string_value(config, "NUMBERS")) be equal to("[1, 2, 3, 4, 5]");

            char** numbers = config_get_array_value(config, "NUMBERS");
            _assert_equals_array(numbers_expected, numbers, 5);

            string_iterate_lines(numbers, (void*) free);
            free(numbers);
        } end

    } end

}
