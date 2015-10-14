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

context (test_config) {

    void _assert_equals_array(char** expected, char** actual, int size) {
        int i;
        for (i = 0; i < size; i++) {
            should_string(actual[i]) be equal to(expected[i]);
        }
        should_ptr(actual[i]) be null;
    }

    describe("Config") {

        describe ("Inexistent file") {

            it ("should return null when try to open a non-existent config file") {
            	t_config *config = config_create("this_doesnt_exist.really.dont.cfg");
                should_ptr(config) be null;
            } end

        } end

		describe ("Existent file") {

        	t_config* config;

            before {
                config = config_create("resources/config.cfg");
            } end

            after {
                config_destroy(config);
            } end

            it("should return true if has property") {
                should_bool(config_has_property(config, "NUMBERS")) be truthy;
            } end

            it("should return false if has not got property") {
                should_bool(config_has_property(config, "PROPERY_MISSING")) be falsey;
            } end

            it("should return the keys count") {
                should_int(config_keys_amount(config)) be equal to(7);
            } end

            describe("Get") {

                it ("should get int value") {
                    should_int(config_get_int_value(config, "PORT")) be equal to(8080);
                } end

                it ("should get string value") {
                    should_string(config_get_string_value(config, "IP")) be equal to("127.0.0.1");
                } end

                it ("should get string value with equals sign in value") {
                    should_string(config_get_string_value(config, "WITH_EQUALS")) be equal to("this=value");
                } end

                it ("should get double value") {
                    should_double(config_get_double_value(config, "LOAD")) be equal to (0.5);
                } end

                it ("should get an empty array value") {
                    should_string(config_get_string_value(config, "EMPTY_ARRAY")) be equal to("[]");
                    char** empty_array  = config_get_array_value(config, "EMPTY_ARRAY");

                    char* empty_array_expected[] = {NULL};
                    _assert_equals_array(empty_array_expected, empty_array, 0);
                    free(empty_array);
                } end

                it ("should get an array with values") {
                    char* numbers_expected[] = {"1", "2", "3", "4", "5", NULL};
                    should_string(config_get_string_value(config, "NUMBERS")) be equal to("[1, 2, 3, 4, 5]");

                    char** numbers = config_get_array_value(config, "NUMBERS");
                    _assert_equals_array(numbers_expected, numbers, 5);

                    string_iterate_lines(numbers, (void*) free);
                    free(numbers);
                } end

            } end

        } end

    } end

}
