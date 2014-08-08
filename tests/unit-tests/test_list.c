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
#include <commons/collections/list.h>
#include <commons/string.h>
#include <cspecs/cspec.h>

typedef struct {
    char *name;
    unsigned char age;
} t_person;

static t_person *persona_create(char *name, unsigned char age) {
    t_person *new = malloc(sizeof(t_person));
    new->name = strdup(name);
    new->age = age;
    return new;
}

static void persona_destroy(t_person *self) {
    free(self->name);
    free(self);
}

context (test_list) {

    void assert_person(t_person *person, char* name, int age) {
        should_ptr(person) not be null;
        should_string(person->name) be equal to(name);
        should_int(person->age) be equal to(age);
    }

    void assert_person_in_list(t_list *list, int index, char* name, int age) {
        assert_person(list_get(list, index), name, age);
    }

    describe ("List") {

        t_person *ayudantes[5];
        t_list *list;

        before {
            list = list_create();
        } end

        after {
            list_destroy_and_destroy_elements(list, (void*) persona_destroy);
        } end

        describe("Add") {

            it ("should add a value") {
                list_add(list, persona_create("Matias", 24));
                assert_person_in_list(list, 0, "Matias", 24);

                list_add(list, persona_create("Gaston", 25));
                assert_person_in_list(list, 1, "Gaston", 25);

                should_int(list_size(list)) be equal to(2);
            } end

            it ("should add a value at index") {
                list_add(list, persona_create("Matias", 24));
                assert_person_in_list(list, 0, "Matias", 24);
                should_int(list_size(list)) be equal to(1);

                list_add_in_index(list, 0, persona_create("Gaston", 25));
                assert_person_in_list(list, 0, "Gaston", 25);
                assert_person_in_list(list, 1, "Matias", 24);
            } end

            it("should add all list into other list") {
                t_list* other = list_create();

                list_add(list, persona_create("Matias"   , 24));
                list_add(list, persona_create("Gaston"   , 25));
                list_add(list, persona_create("Sebastian", 21));
                list_add(other, persona_create("Daniela" , 19));
                list_add(other, persona_create("Facundo" , 25));

                should_int(list_size(list)) be equal to(3);
                list_add_all(list, other);
                should_int(list_size(list)) be equal to(5);

                assert_person_in_list(list, 0, "Matias"   , 24);
                assert_person_in_list(list, 1, "Gaston"   , 25);
                assert_person_in_list(list, 2, "Sebastian", 21);
                assert_person_in_list(list, 3, "Daniela"  , 19);
                assert_person_in_list(list, 4, "Facundo"  , 25);

                list_destroy(other);
            } end

        } end

        describe ("Replace, remove and destroy") {

            before {
                list_add(list, persona_create("Matias"   , 24));
                list_add(list, persona_create("Gaston"   , 25));
                list_add(list, persona_create("Sebastian", 21));
                list_add(list, persona_create("Ezequiel" , 25));
                list_add(list, persona_create("Facundo"  , 25));
            } end

            it("should replace a value at index with other value") {
                t_person *aux = list_replace(list, 3, persona_create("Daniela", 19));
                assert_person(aux, "Ezequiel", 25);

                persona_destroy(aux);

                aux = list_get(list, 3);
                assert_person(aux, "Daniela", 19);
            } end

            it("should remove a value at index") {
                should_int(list_size(list)) be equal to(5);

                t_person *aux = list_remove(list, 0);
                assert_person(aux, "Matias", 24);
                persona_destroy(aux);

                assert_person_in_list(list, 0, "Gaston", 25);
                should_int(list_size(list)) be equal to(4);
            } end

            it("should remove and destroy a value at index") {
                assert_person_in_list(list, 0, "Matias", 24);
                should_int(list_size(list)) be equal to(5);

                list_remove_and_destroy_element(list, 0, (void*)persona_destroy);

                assert_person_in_list(list, 0, "Gaston", 25);
                should_int(list_size(list)) be equal to(4);
            } end

            it("should remove the first value that satisfies a condition") {
                should_int(list_size(list)) be equal to(5);

                bool _is_gaston(t_person *p) {
                    return string_equals_ignore_case(p->name, "Gaston");
                }

                t_person *aux = list_remove_by_condition(list, (void*) _is_gaston);
                assert_person(aux, "Gaston", 25);
                persona_destroy(aux);

                should_int(list_size(list)) be equal to(4);
            } end

            it("should clean a list and leave it empty") {
                should_int(list_size(list)) be equal to(5);
                list_clean_and_destroy_elements(list, (void*) persona_destroy);
                should_bool(list_is_empty(list)) be truthy;
            } end

        } end

        describe ("Higher order functions") {

            before {
                list_add(list, persona_create("Matias"   , 24));
                list_add(list, persona_create("Gaston"   , 25));
                list_add(list, persona_create("Sebastian", 21));
                list_add(list, persona_create("Ezequiel" , 25));
                list_add(list, persona_create("Facundo"  , 25));
            } end

            it(" should find the first value that satisfies a condition") {
                int _is_ezequiel(t_person *p) {
                    return string_equals_ignore_case(p->name, "Ezequiel");
                }

                assert_person(list_find(list, (void*) _is_ezequiel), "Ezequiel", 25);

                int _is_chuck_norris(t_person *p) {
                    return string_equals_ignore_case(p->name, "Chuck Norris");
                }

                should_ptr(list_find(list, (void*) _is_chuck_norris)) be null;
                should_int(list_size(list)) be equal to(5);
            } end

            it("should filter a list with the values that satisfies a condition") {
                should_int(list_size(list)) be equal to(5);
                bool _is_young(t_person* person) {
                    return person->age <= 24;
                }
                t_list* filtered = list_filter(list, (void*) _is_young);
                should_int(list_size(filtered)) be equal to(2);
                assert_person_in_list(filtered, 0, "Matias", 24);
                assert_person_in_list(filtered, 1, "Sebastian", 21);
                list_destroy(filtered);
            } end

            it("should map a list with the function result") {
                char* names_array[] = { "Matias", "Gaston", "Sebastian", "Ezequiel", "Facundo" };
                char* _get_name(t_person* person) {
                    return person->name;
                }
                t_list* names = list_map(list, (void*) _get_name);
                int i; for (i = 0; i < 5; i++) {
                    should_string(list_get(names, i)) be equal to(names_array[i]);
                }
                list_destroy(names);
            } end

        } end

        describe ("Take") {

            before {
                list_add(list, persona_create("Matias"   , 24));
                list_add(list, persona_create("Gaston"   , 25));
                list_add(list, persona_create("Sebastian", 21));
                list_add(list, persona_create("Ezequiel" , 25));
                list_add(list, persona_create("Facundo"  , 25));
            } end

            it("should return a new list with the first \"N\" elements of a list") {
                t_list* sublist = list_take(list, 3);
                should_int(list_size(list)) be equal to(5);
                should_int(list_size(sublist)) be equal to(3);

                assert_person_in_list(sublist, 0, "Matias"   , 24);
                assert_person_in_list(sublist, 1, "Gaston"   , 25);
                assert_person_in_list(sublist, 2, "Sebastian", 21);

                list_destroy(sublist);
            } end

            it("should return a new list with the first \"N\" elements of a list and remove them from original list") {
                t_list* sublist = list_take_and_remove(list, 3);
                should_int(list_size(list)) be equal to(2);
                should_int(list_size(sublist)) be equal to(3);

                assert_person_in_list(sublist, 0, "Matias"   , 24);
                assert_person_in_list(sublist, 1, "Gaston"   , 25);
                assert_person_in_list(sublist, 2, "Sebastian", 21);

                list_destroy_and_destroy_elements(sublist, (void*)persona_destroy);
            } end

        } end


        describe ("Sort") {

            bool _ayudantes_menor(t_person *joven, t_person *menos_joven) {
                return joven->age < menos_joven->age;
            }

            before {
                list_add(list, persona_create("Matias"   , 24));
                list_add(list, persona_create("Gaston"   , 25));
                list_add(list, persona_create("Sebastian", 21));
                list_add(list, persona_create("Daniela"  , 19));
            } end

            it("should sort and empty list") {
                t_list *list = list_create();

                list_sort(list, NULL);

                should_bool(list_is_empty(list)) be truthy;

                list_destroy(list);
            } end

            it("should sort a list without duplicated values") {
                list_sort(list, (void*) _ayudantes_menor);

                assert_person_in_list(list, 0, "Daniela"  , 19);
                assert_person_in_list(list, 1, "Sebastian", 21);
                assert_person_in_list(list, 2, "Matias"   , 24);
                assert_person_in_list(list, 3, "Gaston"   , 25);
            } end

            it("sort duplicates a list with duplicated values") {
                list_add(list, persona_create("Ezequiel", 25));

                list_sort(list, (void*) _ayudantes_menor);

                assert_person_in_list(list, 0, "Daniela"  , 19);
                assert_person_in_list(list, 1, "Sebastian", 21);
                assert_person_in_list(list, 2, "Matias"   , 24);
                assert_person_in_list(list, 3, "Ezequiel" , 25);
                assert_person_in_list(list, 4, "Gaston"   , 25);
            } end

        } end

        describe ("Satisfying") {

            bool _ayudante_menor_o_igual_a_21(void *ayudante) {
                return ((t_person *)ayudante)->age <= 21;
            }

            before {
                list_add(list, persona_create("Matias"   , 24));
                list_add(list, persona_create("Gaston"   , 25));
                list_add(list, persona_create("Sebastian", 21));
                list_add(list, persona_create("Daniela"  , 19));
            } end

            describe ("Count") {

                it("should count the values that satisfies a condition") {
                    should_int(list_count_satisfying(list, _ayudante_menor_o_igual_a_21)) be equal to(2);
                } end

            } end

            describe ("Any") {

                it("should not satisfy an empty list") {
                    t_list *list = list_create();

                    should_bool(list_any_satisfy(list, (void*)_ayudante_menor_o_igual_a_21)) be falsey;

                    list_destroy(list);
                } end

                it("should satisfy a list with values if any of them satisfies the condition") {
                    should_bool(list_any_satisfy(list, (void*)_ayudante_menor_o_igual_a_21)) be truthy;
                } end

                it("should not satisfy a list with values if none of them satisfies the condition") {
                    bool _ayudante_menor_o_igual_a_16(void *ayudante) {
                        return ((t_person *)ayudante)->age <= 16;
                    }

                    should_bool(list_any_satisfy(list, (void*)_ayudante_menor_o_igual_a_16)) be falsey;
                } end

            } end

            describe ("All") {

                it("should satisfy an empty list") {
                    t_list *list = list_create();

                    should_bool(list_all_satisfy(list, (void*)_ayudante_menor_o_igual_a_21)) be truthy;

                    list_destroy(list);
                } end

                it("should satisfy a list with values if each of them satisfies the condition") {
                    bool _ayudante_mayor_a_16(void *ayudante) {
                        return ((t_person *)ayudante)->age > 16;
                    }

                    should_bool(list_all_satisfy(list, (void*)_ayudante_mayor_a_16)) be truthy;
                } end

                it("should not satisfy a list with values if any of them not satisfy the condition") {
                    should_bool(list_all_satisfy(list, (void*)_ayudante_menor_o_igual_a_21)) be falsey;
                } end

            } end

        } end

        describe ("Iterator") {

            it("should iterate all list values") {
                list_add(list, persona_create("Matias"   , 24));
                list_add(list, persona_create("Gaston"   , 25));
                list_add(list, persona_create("Sebastian", 21));
                list_add(list, persona_create("Daniela"  , 19));

                char* names_array[] = { "Matias", "Gaston", "Sebastian", "Daniela" };
                int index = 0;

                void _list_elements(t_person *p) {
                    should_ptr(p) not be null;
                    should_string(p->name) be equal to(names_array[index++]);
                }

                list_iterate(list, (void*) _list_elements);
                should_int(index) be equal to(4);
            } end

        } end

    } end

}

