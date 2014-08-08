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

context (test_queue) {

    void assert_person(t_person *person, char* name, int age) {
        should_ptr(person) not be null;
        should_string(person->name) be equal to(name);
        should_int(person->age) be equal to(age);
    }

    describe ("Queue") {

        t_queue * queue;

        before {
            queue = queue_create();
        } end

        after {
            queue_destroy_and_destroy_elements(queue, (void*) persona_destroy);
        } end

        it("should return the value at top of queue without change the queue") {
            queue_push(queue, persona_create("Matias", 24));
            queue_push(queue, persona_create("Gaston", 25));
            should_int(queue_size(queue)) be equal to(2);

            assert_person(queue_peek(queue), "Matias", 24);
            should_int(queue_size(queue)) be equal to(2);

            assert_person(queue_peek(queue), "Matias", 24);
            should_int(queue_size(queue)) be equal to(2);
        } end

        it("should clean the queue and leave it empty") {
            queue_push(queue, persona_create("Matias", 24));
            queue_push(queue, persona_create("Gaston", 25));

            should_int(queue_size(queue)) be equal to(2);

            queue_clean_and_destroy_elements(queue, (void*) persona_destroy);
            should_bool(queue_is_empty(queue)) be truthy;
        } end

        describe ("Push and pop") {

            it("should push some values") {
                should_int(queue_size(queue)) be equal to(0);
                queue_push(queue, persona_create("Matias", 24));
                should_int(queue_size(queue)) be equal to(1);
                queue_push(queue, persona_create("Gaston", 25));
                should_int(queue_size(queue)) be equal to(2);
            } end

            it ("should pop some values") {
                queue_push(queue, persona_create("Matias", 24));
                queue_push(queue, persona_create("Gaston", 25));

                void pop_assert_and_destroy(t_queue *queue, char* name, int age) {
                    t_person *aux = queue_pop(queue);
                    assert_person(aux, name, age);
                    persona_destroy(aux);
                }

                should_int(queue_size(queue)) be equal to(2);

                pop_assert_and_destroy(queue, "Matias", 24);
                should_int(queue_size(queue)) be equal to(1);

                pop_assert_and_destroy(queue, "Gaston", 25);
                should_int(queue_size(queue)) be equal to(0);
            } end

        } end

    } end

}

