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
#include <assert.h>
#include <string.h>
#include <commons/collections/dictionary.h>
#include <cspecs/cspec.h>

// ------------------ HELP FUNCTION'S ---------------------

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

static void assert_person(t_person *person, char* name, int age) {
    should_ptr(person) not be null;
    should_string(person->name) be equal to(name);
    should_int(person->age) be equal to(age);
}

context (test_dictionary) {

    describe ("Dictionary") {

        t_dictionary *dictionary;

        before {
            dictionary = dictionary_create();
        } end

        after {
            dictionary_destroy_and_destroy_elements(dictionary, (void*) persona_destroy);
        } end

        it("put and get") {
            t_person *p1 = persona_create("Matias", 24);
            dictionary_put(dictionary, p1->name, p1);

            t_person *p2 = persona_create("Gaston", 25);
            dictionary_put(dictionary, p2->name, p2);

            should_int(dictionary_size(dictionary)) be equal to(2);
            should_bool(dictionary_is_empty(dictionary)) be falsey;

            t_person *aux = dictionary_get(dictionary, "Matias");
            assert_person(aux, "Matias", 24);

            aux = dictionary_get(dictionary, "Gaston");
            assert_person(aux, "Gaston", 25);

            should_int(dictionary_size(dictionary)) be equal to(2);
        } end

        it("remove") {
            t_person *p1 = persona_create("Matias", 24);
            dictionary_put(dictionary, p1->name, p1);

            t_person *p2 = persona_create("Gaston", 25);
            dictionary_put(dictionary, p2->name, p2);

            should_int(dictionary_size(dictionary)) be equal to(2);
            should_bool(dictionary_is_empty(dictionary)) be falsey;

            t_person *aux = dictionary_remove(dictionary, "Matias");
            assert_person(aux, "Matias", 24);
            persona_destroy(aux);

            should_int(dictionary_size(dictionary)) be equal to(1);

            aux = dictionary_remove(dictionary, "Gaston");
            assert_person(aux, "Gaston", 25);
            persona_destroy(aux);

            should_int(dictionary_size(dictionary)) be equal to(0);
            should_bool(dictionary_is_empty(dictionary)) be truthy;
        } end

        it("remove and destroy") {
            t_person *p1 = persona_create("Matias", 24);
            dictionary_put(dictionary, p1->name, p1);

            t_person *p2 = persona_create("Gaston", 25);
            dictionary_put(dictionary, p2->name, p2);

            should_int(dictionary_size(dictionary)) be equal to(2);
            should_bool(dictionary_is_empty(dictionary)) be falsey;

            dictionary_remove_and_destroy(dictionary, "Matias", (void*) persona_destroy);

            should_int(dictionary_size(dictionary)) be equal to(1);

            should_ptr( dictionary_get(dictionary, "Matias")) be null;

            dictionary_remove_and_destroy(dictionary, "Gaston", (void*) persona_destroy);

            should_ptr(dictionary_get(dictionary, "Gaston")) be null;

            should_int(dictionary_size(dictionary)) be equal to(0);
        } end

        it("clean") {
            int cont;
            for (cont = 0; cont < 100; cont++) {
                char *key = malloc(5); sprintf(key, "%d", cont);
                dictionary_put(dictionary, "Key", malloc(20));
                free(key);
            }

            should_int(dictionary_size(dictionary)) be equal to(100);
            should_bool(dictionary_is_empty(dictionary)) be falsey;

            dictionary_clean_and_destroy_elements(dictionary, free);

            should_int(dictionary_size(dictionary)) be equal to(0);
            should_bool(dictionary_is_empty(dictionary)) be truthy;
        } end

        it("iterate") {
            t_person* persons[4] = {
                persona_create("Matias", 24),
                persona_create("Gaston", 25),
                persona_create("Dani", 20),
                persona_create("Marco", 21)
            };

            dictionary_put(dictionary, persons[0]->name, persons[0]);
            dictionary_put(dictionary, persons[1]->name, persons[1]);
            dictionary_put(dictionary, persons[2]->name, persons[2]);
            dictionary_put(dictionary, persons[3]->name, persons[3]);

            should_int(dictionary_size(dictionary)) be equal to(4);

            void _assertion(char* key, t_person* person) {
                should_string(key) be equal to(person->name);
            }

            dictionary_iterator(dictionary, (void*) _assertion);
        } end

        it("overload entry") {
            t_dictionary *dictionary = dictionary_create(free);

            char *key = "aKey";

            dictionary_put(dictionary, key, persona_create("Matias", 24));
            dictionary_put(dictionary, key, persona_create("Gaston", 25));

            void _persona_iterating_destroy(char *key, t_person *person) {
                persona_destroy(person);
            }

            dictionary_iterator(dictionary, (void*) _persona_iterating_destroy);

            dictionary_destroy(dictionary);
        } end

    } end

}
