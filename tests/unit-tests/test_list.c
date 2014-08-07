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
#include <commons/collections/list.h>
#include <commons/string.h>
#include <cspecs/cspec.h>

// ------------------ HELP FUNCTION'S ---------------------

typedef struct {
	char *name;
	unsigned char age;
} t_person;

static  t_person *persona_create(char *name, unsigned char age){
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

static void assert_person_in_list(t_list *list, int index, char* name, int age) {
    assert_person(list_get(list, index), name, age);
}

t_person *ayudantes[5];

// --------------------------------------------------------

context (test_list) {

    describe ("List") {

        t_person *ayudantes[5];
        t_list *list;

        before {
            ayudantes[0] = persona_create("Matias", 24);
            ayudantes[1] = persona_create("Gaston", 25);
            ayudantes[2] = persona_create("Sebastian", 21);
            ayudantes[3] = persona_create("Daniela", 19);
            ayudantes[4] = persona_create("Facundo", 25);
            list = list_create();
        } end

        after {
            int i; for (i = 0; i < 5; i++) {
                persona_destroy(ayudantes[i]);
            }
            list_destroy_and_destroy_elements(list, (void*) persona_destroy);
        } end


        it ("add") {
            list_add(list, persona_create("Matias", 24));
            list_add(list, persona_create("Gaston", 25));

            assert_person_in_list(list, 0, "Matias", 24);
            assert_person_in_list(list, 1, "Gaston", 25);

            should_int(list_size(list)) be equal to(2);
        } end

        it ("add in index") {
            list_add(list, persona_create("Matias", 24));
            list_add(list, persona_create("Gaston", 25));
            list_add(list, persona_create("Facundo", 25));
            list_add_in_index(list, 1, persona_create("Sebastian", 21));

            assert_person_in_list(list, 0, "Matias", 24);
            assert_person_in_list(list, 1, "Sebastian", 21);
            assert_person_in_list(list, 2, "Gaston", 25);

            int index_last_element = list_size(list);
            list_add_in_index(list, index_last_element, persona_create("Dani", 21));

            t_person *aux = list_get(list, index_last_element);
            should_bool(aux) not be null;
            should_string(aux->name) be equal to("Dani");
            should_int(aux->age) be equal to(21);

            should_int(list_size(list)) be equal to(5);
        } end

        it("find") {

            list_add(list, persona_create("Matias", 24));
            list_add(list, persona_create("Gaston", 25));
            list_add(list, persona_create("Sebastian", 21));
            list_add(list, persona_create("Daniela", 19));
            list_add(list, persona_create("Facundo", 25));

            int _is_daniela(t_person *p) {
                return string_equals_ignore_case(p->name, "Daniela");
            }

            assert_person(list_find(list, (void*) _is_daniela), "Daniela", 19);

            int _is_chuck_norris(t_person *p) {
                return string_equals_ignore_case(p->name, "Chuck Norris");
            }
            t_person *aux = list_find(list, (void*) _is_chuck_norris);
            should_ptr(aux) be null;

            should_int(list_size(list)) be equal to(5);

        } end


        it("replace") {
            list_add(list, persona_create("Matias", 24));
            list_add(list, persona_create("Gaston", 25));
            list_add(list, persona_create("Sebastian", 21));
            list_add(list, persona_create("Ezequiel", 25));
            list_add(list, persona_create("Facundo", 25));

            t_person *aux = list_replace(list, 3, persona_create("Daniela", 19));
            assert_person(aux, "Ezequiel", 25);

            persona_destroy(aux);

            aux = list_get(list, 3);
            assert_person(aux, "Daniela", 19);

            should_int(list_size(list)) be equal to(5);
        } end

        it("remove") {
            list_add(list, persona_create("Matias", 24));
            list_add(list, persona_create("Gaston", 25));

            t_person *aux = list_remove(list, 0);
            assert_person(aux, "Matias", 24);
            persona_destroy(aux);

            should_int(list_size(list)) be equal to(1);

            assert_person_in_list(list, 0, "Gaston", 25);
        } end

        it("remove and destroy") {
            list_add(list, persona_create("Matias", 24));
            list_add(list, persona_create("Gaston", 25));

            list_remove_and_destroy_element(list, 0, (void*) persona_destroy);

            should_int(list_size(list)) be equal to(1);

            assert_person_in_list(list, 0, "Gaston", 25);
        } end

        it("remove by closure") {
            list_add(list, persona_create("Matias", 24));
            list_add(list, persona_create("Gaston", 25));
            list_add(list, persona_create("Sebastian", 21));
            list_add(list, persona_create("Daniela", 19));
            list_add(list, persona_create("Facundo", 25));

            bool _is_daniela(t_person *p) {
                return string_equals_ignore_case(p->name, "Daniela");
            }

            t_person *aux = list_remove_by_condition(list, (void*) _is_daniela);
            assert_person(aux, "Daniela", 19);
            persona_destroy(aux);

            should_int(list_size(list)) be equal to(4);
        } end

        it("iterate") {

            t_list * list = list_create();

            list_add(list, ayudantes[0]);
            list_add(list, ayudantes[1]);
            list_add(list, ayudantes[2]);
            list_add(list, ayudantes[3]);
            list_add(list, ayudantes[4]);

            int index = 0;

            void _list_elements(t_person *p) {
                should_ptr(p) not be null;
                should_string(ayudantes[index++]->name) be equal to(p->name);
            }

            list_iterate(list, (void*) _list_elements);

            list_destroy(list);
        } end

        it("clean") {
            list_add(list, persona_create("Matias", 24));
            list_add(list, persona_create("Gaston", 25));
            list_clean_and_destroy_elements(list, (void*) persona_destroy);

            should_int(list_size(list)) be equal to(0);
            should_bool(list_is_empty(list)) be truthy;

            t_person *aux = list_get(list, 0);
            should_ptr(aux) be null;

            aux = list_get(list, 1);
            should_ptr(aux) be null;
        } end

        it("take") {
            t_list* list = list_create();
            list_add(list, ayudantes[0]);
            list_add(list, ayudantes[1]);
            list_add(list, ayudantes[2]);
            list_add(list, ayudantes[3]);
            list_add(list, ayudantes[4]);

            t_list* sublist = list_take(list, 3);
            should_ptr(sublist) not be null;
            should_int(list_size(list)) be equal to(5);
            should_int(list_size(sublist)) be equal to(3);

            t_person* element = list_get(sublist, 0);
            should_string(element->name) be equal to(ayudantes[0]->name);

            element = list_get(sublist, 1);
            should_string(element->name) be equal to(ayudantes[1]->name);

            element = list_get(sublist, 2);
            should_string(element->name) be equal to(ayudantes[2]->name);

            list_destroy(sublist);
            list_destroy(list);
        } end

        it("take and remove") {
            t_list* list = list_create();
            list_add(list, ayudantes[0]);
            list_add(list, ayudantes[1]);
            list_add(list, ayudantes[2]);
            list_add(list, ayudantes[3]);
            list_add(list, ayudantes[4]);

            t_list* sublist = list_take_and_remove(list, 3);
            should_ptr(sublist) not be null;
            should_int(list_size(list)) be equal to(2);
            should_int(list_size(sublist)) be equal to(3);

            int i; for(i = 0; i < 3; i ++) {
                t_person* element = list_get(sublist, i);
                should_string(element->name) be equal to(ayudantes[i]->name);
            }

            for(i = 0; i < 2; i ++) {
                t_person* element = list_get(list, i);
                should_string(element->name) be equal to(ayudantes[i + 3]->name);
            }

            list_destroy(sublist);
            list_destroy(list);
        } end

        it("filter") {
            t_list* list = list_create();
            list_add(list, ayudantes[0]);
            list_add(list, ayudantes[1]);
            list_add(list, ayudantes[2]);
            list_add(list, ayudantes[3]);
            list_add(list, ayudantes[4]);

            bool _is_young(t_person* person) {
                return person->age <= 21;
            }

            t_list* filtered = list_filter(list, (void*) _is_young);
            should_ptr(filtered) not be null;
            should_int(list_size(list)) be equal to(5);
            should_int(list_size(filtered)) be equal to(2);
            list_destroy(filtered);

            list_destroy(list);
        } end

        it("map") {
            t_list *list = list_create();
            list_add(list, ayudantes[0]);
            list_add(list, ayudantes[1]);
            list_add(list, ayudantes[2]);
            list_add(list, ayudantes[3]);
            list_add(list, ayudantes[4]);

            char* _map_to_name(t_person* person) {
                return string_duplicate(person->name);
            }

            t_list* names = list_map(list, (void*) _map_to_name);
            should_ptr(names) not be null;
            should_int(list_size(names)) be equal to(5);

            int i = 0;
            void _verify_name(char* name) {
                should_string(name) be equal to(ayudantes[i++]->name);
            }
            list_iterate(names, (void*) _verify_name);
            list_destroy_and_destroy_elements(names, free);

            list_destroy(list);
        } end

        it("add_all") {
            t_list* principal = list_create();
            t_list* other = list_create();

            list_add(principal, ayudantes[0]);
            list_add(principal, ayudantes[1]);
            list_add(principal, ayudantes[2]);
            list_add(other, ayudantes[3]);
            list_add(other, ayudantes[4]);

            list_add_all(principal, other);

            should_int(list_size(principal)) be equal to(5);
            should_ptr(list_get(principal, 0)) be equal to(ayudantes[0]);
            should_ptr(list_get(principal, 1)) be equal to(ayudantes[1]);
            should_ptr(list_get(principal, 2)) be equal to(ayudantes[2]);
            should_ptr(list_get(principal, 3)) be equal to(ayudantes[3]);
            should_ptr(list_get(principal, 4)) be equal to(ayudantes[4]);

            list_destroy(principal);
            list_destroy(other);
        } end

        it("sort empty") {
            t_list *list = list_create();

            list_sort(list, NULL);

            should_bool(list_is_empty(list)) be truthy;

            list_destroy(list);
        } end

        it("sort unique") {
            t_list *list = list_create();

            list_add(list, ayudantes[0]);
            list_add(list, ayudantes[1]);
            list_add(list, ayudantes[2]);
            list_add(list, ayudantes[3]);

            bool _ayudantes_menor(t_person *joven, t_person *menos_joven) {
                return joven->age < menos_joven->age;
            }

            list_sort(list, (void*) _ayudantes_menor);

            should_ptr(list_get(list, 0)) be equal to(ayudantes[3]);
            should_ptr(list_get(list, 1)) be equal to(ayudantes[2]);
            should_ptr(list_get(list, 2)) be equal to(ayudantes[0]);
            should_ptr(list_get(list, 3)) be equal to(ayudantes[1]);

            list_destroy(list);
        } end

        it("sort duplicates") {
            t_list *list = list_create();

            list_add(list, ayudantes[0]);
            list_add(list, ayudantes[1]);
            list_add(list, ayudantes[2]);
            list_add(list, ayudantes[3]);
            list_add(list, ayudantes[2]);

            bool _ayudantes_menor(t_person *joven, t_person *menos_joven) {
                return joven->age < menos_joven->age;
            }

            list_sort(list, (void*) _ayudantes_menor);

            should_ptr(list_get(list, 0)) be equal to(ayudantes[3]);
            should_ptr(list_get(list, 1)) be equal to(ayudantes[2]);
            should_ptr(list_get(list, 2)) be equal to(ayudantes[2]);
            should_ptr(list_get(list, 3)) be equal to(ayudantes[0]);
            should_ptr(list_get(list, 4)) be equal to(ayudantes[1]);

            list_destroy(list);
        } end

        it("count satisfying") {
            t_list *list = list_create();

            bool _ayudante_menor_a_20(void *ayudante) {
                return ((t_person *)ayudante)->age < 20;
            }

            should_int(list_count_satisfying(list, _ayudante_menor_a_20)) be equal to(0);

            list_add(list, ayudantes[0]);

            should_int(list_count_satisfying(list, _ayudante_menor_a_20)) be equal to(0);

            list_add(list, ayudantes[1]);
            list_add(list, ayudantes[2]);

            should_int(list_count_satisfying(list, _ayudante_menor_a_20)) be equal to(0);

            list_add(list, ayudantes[3]);

            should_int(list_count_satisfying(list, _ayudante_menor_a_20)) be equal to(1);

            list_add(list, ayudantes[2]);

            should_int(list_count_satisfying(list, _ayudante_menor_a_20)) be equal to(1);

            list_add(list, ayudantes[3]);

            should_int(list_count_satisfying(list, _ayudante_menor_a_20)) be equal to(2);

            list_clean(list);

            should_int(list_count_satisfying(list, _ayudante_menor_a_20)) be equal to(0);

            list_destroy(list);
        } end

        it("any satisfy empty") {
            t_list *list = list_create();

            should_bool(list_any_satisfy(list, NULL)) be falsey;

            list_destroy(list);
        } end

        it("any satisfy satisfying") {
            t_list *list = list_create();

            list_add(list, ayudantes[0]);
            list_add(list, ayudantes[1]);
            list_add(list, ayudantes[2]);
            list_add(list, ayudantes[3]);
            list_add(list, ayudantes[2]);

            bool _ayudante_menor_a_20(t_person *ayudante) {
                return ayudante->age < 20;
            }

            should_bool(list_any_satisfy(list, (void*)_ayudante_menor_a_20)) be truthy;

            list_destroy(list);
        } end

        it("any satisfy not satisfying") {
            t_list *list = list_create();

            list_add(list, ayudantes[0]);
            list_add(list, ayudantes[1]);
            list_add(list, ayudantes[2]);
            list_add(list, ayudantes[3]);
            list_add(list, ayudantes[2]);

            bool _ayudante_menor_a_15(t_person *ayudante) {
                return ayudante->age < 15;
            }

            should_bool(list_any_satisfy(list, (void*)_ayudante_menor_a_15)) be falsey;

            list_destroy(list);
        } end

        it("all satisfy empty") {
            t_list *list = list_create();

            should_bool(list_all_satisfy(list, NULL)) be truthy;

            list_destroy(list);
        } end

        it("all satisfy satisfying") {
            t_list *list = list_create();

            list_add(list, ayudantes[0]);
            list_add(list, ayudantes[1]);
            list_add(list, ayudantes[2]);
            list_add(list, ayudantes[3]);
            list_add(list, ayudantes[2]);

            bool _ayudante_menor_a_30(t_person *ayudante) {
                return ayudante->age < 30;
            }

            should_bool(list_all_satisfy(list, (void*)_ayudante_menor_a_30)) be truthy;

            list_destroy(list);
        } end

        it("all satisfy not satisfying") {
            t_list *list = list_create();

            list_add(list, ayudantes[0]);
            list_add(list, ayudantes[1]);
            list_add(list, ayudantes[2]);
            list_add(list, ayudantes[3]);
            list_add(list, ayudantes[2]);

            bool _ayudante_menor_a_20(t_person *ayudante) {
                return ayudante->age < 20;
            }

            should_bool(list_all_satisfy(list, (void*)_ayudante_menor_a_20)) be falsey;

            list_destroy(list);
        } end

    } end

}

