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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <commons/collections/dictionary.h>
#include <cspecs/cspec.h>

typedef struct {
	char *name;
	unsigned char age;
} t_person;

static t_person *persona_create(char *name, unsigned char age){
	t_person *new = malloc( sizeof(t_person) );
	new->name = strdup(name);
	new->age = age;
	return new;
}

static void persona_destroy(t_person *self){
	free(self->name);
	free(self);
}

context (test_dictionary) {

    void assert_person(t_person *person, char* name, int age) {
        should_ptr(person) not be null;
        should_string(person->name) be equal to(name);
        should_int(person->age) be equal to(age);
    }

    describe ("Dictionary") {

        t_dictionary *dictionary;

        before {
            dictionary = dictionary_create();
        } end

        after {
            dictionary_destroy_and_destroy_elements(dictionary, (void*) persona_destroy);
        } end

        describe ("Put and get") {

            it("should put a value at a key") {
                should_bool(dictionary_is_empty(dictionary)) be truthy;
                dictionary_put(dictionary, "Matias", persona_create("Matias", 24));
                should_int(dictionary_size(dictionary)) be equal to(1);
                dictionary_put(dictionary, "Gaston", persona_create("Gaston", 25));
                should_int(dictionary_size(dictionary)) be equal to(2);
            } end

            it("should get a value from a key") {
                dictionary_put(dictionary, "Matias", persona_create("Matias", 24));
                dictionary_put(dictionary, "Gaston", persona_create("Gaston", 25));
                should_int(dictionary_size(dictionary)) be equal to(2);
                assert_person(dictionary_get(dictionary, "Matias"), "Matias", 24);
                assert_person(dictionary_get(dictionary, "Gaston"), "Gaston", 25);
                should_int(dictionary_size(dictionary)) be equal to(2);
            } end

        } end

        describe ("Remove, destroy and clean") {

            before {
                dictionary_put(dictionary, "Matias", persona_create("Matias", 24));
                dictionary_put(dictionary, "Gaston", persona_create("Gaston", 25));
            } end

            it("should remove a value from a key") {
                should_int(dictionary_size(dictionary)) be equal to(2);

                t_person *aux = dictionary_remove(dictionary, "Matias");
                assert_person(aux, "Matias", 24);
                persona_destroy(aux);

                should_int(dictionary_size(dictionary)) be equal to(1);

                aux = dictionary_remove(dictionary, "Gaston");
                assert_person(aux, "Gaston", 25);
                persona_destroy(aux);

                should_bool(dictionary_is_empty(dictionary)) be truthy;
            } end

            it("should remove and destroy a value from a key") {
                should_int(dictionary_size(dictionary)) be equal to(2);

                dictionary_remove_and_destroy(dictionary, "Matias", (void*) persona_destroy);
                should_int(dictionary_size(dictionary)) be equal to(1);

                dictionary_remove_and_destroy(dictionary, "Gaston", (void*) persona_destroy);
                should_bool(dictionary_is_empty(dictionary)) be truthy;

                should_ptr(dictionary_get(dictionary, "Matias")) be null;
                should_ptr(dictionary_get(dictionary, "Gaston")) be null;
            } end

            it("should clean the dictionary") {
                should_int(dictionary_size(dictionary)) be equal to(2);
                dictionary_clean_and_destroy_elements(dictionary, (void*)persona_destroy);
                should_bool(dictionary_is_empty(dictionary)) be truthy;
            } end

        } end

        describe ("Iterate") {

            int iterator_count;
            void _assertion(char* ___, t_person* __) {
                iterator_count++;
            }

            before {
                iterator_count = 0;
            } end

            it("should iterate all entries") {
                dictionary_put(dictionary, "Matias" , persona_create("Matias" , 24));
                dictionary_put(dictionary, "Gaston" , persona_create("Gaston" , 25));
                dictionary_put(dictionary, "Daniela", persona_create("Daniela", 20));
                dictionary_put(dictionary, "Marco"  , persona_create("Marco"  , 21));

                dictionary_iterator(dictionary, (void*) _assertion);
                should_int(iterator_count) be equal to(4);
            } end

            it("should iterate all overloaded entries") {
                dictionary_put(dictionary, "key", persona_create("Matias", 24));
                dictionary_put(dictionary, "key", persona_create("Gaston", 25));

                dictionary_iterator(dictionary, (void*) _assertion);
                should_int(iterator_count) be equal to(2);
            } end

        } end

    } end

}
