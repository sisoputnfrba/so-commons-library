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
#include <commons/collections/queue.h>
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

context (test_queue) {

    describe ("Queue") {

        t_queue * queue;

        before {
            queue = queue_create();
        } end

        after {
            queue_destroy_and_destroy_elements(queue, (void*) persona_destroy);
        } end

        it("push and pop") {
            queue_push(queue, persona_create("Matias", 24));
            queue_push(queue, persona_create("Gaston", 25));

            should_int(queue_size(queue)) be equal to(2);
            should_bool(queue_is_empty(queue)) be falsey;

            t_person *aux = queue_pop(queue);
            assert_person(aux, "Matias", 24);
            persona_destroy(aux);

            should_int(queue_size(queue)) be equal to(1);
            should_bool(queue_is_empty(queue)) be falsey;

            aux = queue_pop(queue);
            assert_person(aux, "Gaston", 25);
            persona_destroy(aux);

            should_int(queue_size(queue)) be equal to(0);
            should_bool(queue_is_empty(queue)) be truthy;

            aux = queue_pop(queue);
            should_ptr(aux) be null;
        } end

        it("peek") {
            queue_push(queue, persona_create("Matias", 24));
            queue_push(queue, persona_create("Gaston", 25));

            should_int(queue_size(queue)) be equal to(2);
            should_bool(queue_is_empty(queue)) be falsey;

            t_person *aux = queue_peek(queue);
            assert_person(aux, "Matias", 24);

            should_int(queue_size(queue)) be equal to(2);

            aux = queue_peek(queue);
            assert_person(aux, "Matias", 24);

            should_int(queue_size(queue)) be equal to(2);
        } end

        it("clean") {
            queue_push(queue, persona_create("Matias", 24));
            queue_push(queue, persona_create("Gaston", 25));

            should_int(queue_size(queue)) be equal to(2);
            should_bool(queue_is_empty(queue)) be falsey;

            queue_clean_and_destroy_elements(queue, (void*) persona_destroy);

            should_int(queue_size(queue)) be equal to(0);
            should_bool(queue_is_empty(queue)) be truthy;
        } end

    } end

}

