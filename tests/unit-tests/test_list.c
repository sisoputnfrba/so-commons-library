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

static bool _ayudantes_menor(t_person *joven, t_person *menos_joven) {
    return joven->age <= menos_joven->age;
}

static bool _ayudantes_alfabetico(t_person *primero, t_person *segundo) {
    return strcmp(primero->name, segundo->name) <= 0;
}

static void* _ayudantes_minimo_edad(t_person* person1, t_person* person2) {
    return person1->age <= person2->age ? person1 : person2;
}

static void* _ayudantes_maximo_edad(t_person* person1, t_person* person2) {
    return person1->age >= person2->age ? person1 : person2;
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

            it ("should add a value in sorted list") {
                list_add(list, persona_create("Sebastian", 21));
                list_add(list, persona_create("Matias"   , 24));
                list_add(list, persona_create("Gaston"   , 25));

                should_int(list_size(list)) be equal to(3);
                list_add_sorted(list, persona_create("Daniela", 19), (void*) _ayudantes_menor);
                list_add_sorted(list, persona_create("Agustin", 26), (void*) _ayudantes_menor);
                list_add_sorted(list, persona_create("Ezequiel", 25), (void*) _ayudantes_menor);
                should_int(list_size(list)) be equal to(6);

                assert_person_in_list(list, 0, "Daniela"  , 19);
                assert_person_in_list(list, 1, "Sebastian", 21);
                assert_person_in_list(list, 2, "Matias"   , 24);
                assert_person_in_list(list, 3, "Gaston"   , 25);
                assert_person_in_list(list, 4, "Ezequiel" , 25);
                assert_person_in_list(list, 5, "Agustin"  , 26);
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

        describe ("Duplicate") {

            it("should add all elements in a new list") {
                list_add(list, persona_create("Juan", 22));
                list_add(list, persona_create("Diana", 22));

                t_list* duplicated = list_duplicate(list);
                should_int(list_size(duplicated)) be equal to(2);

                should_ptr(duplicated) not be equal to(list);
                assert_person_in_list(duplicated, 0, "Juan", 22);
                assert_person_in_list(duplicated, 1, "Diana", 22);

                list_destroy(duplicated);
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

            it("should find the first value that satisfies a condition") {
                t_person *find_someone_by_name(char *name) {
                    int _is_the_one(t_person *p) {
                        return string_equals_ignore_case(p->name, name);
                    }

                    return list_find(list, (void*) _is_the_one);
                }

                assert_person(find_someone_by_name("Ezequiel"), "Ezequiel", 25);
                assert_person(find_someone_by_name("Sebastian"), "Sebastian", 21);
                should_ptr(find_someone_by_name("Chuck Norris")) be null;
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


        describe ("Sort a list") {

            describe ("Sorting a empty list") {

                it("should sort and empty list") {
                    list_sort(list, (void*) _ayudantes_menor);

                    should_bool(list_is_empty(list)) be truthy;

                } end

            } end

            describe ("Sorting a list with elements") {

                void _verify_a_sort_without_duplicates(t_list* (*sorted_list_generator)()) {
                    t_list* a_sorted_list = sorted_list_generator();

                    assert_person_in_list(a_sorted_list, 0, "Daniela"  , 19);
                    assert_person_in_list(a_sorted_list, 1, "Sebastian", 21);
                    assert_person_in_list(a_sorted_list, 2, "Matias"   , 24);
                    assert_person_in_list(a_sorted_list, 3, "Gaston"   , 25);
                }

                void _verify_a_sort_with_duplicates(t_list* (*sorted_list_generator)()) {
                    list_add(list, persona_create("Ezequiel", 25));

                    t_list* a_sorted_list = sorted_list_generator();
                    assert_person_in_list(a_sorted_list, 0, "Daniela"  , 19);
                    assert_person_in_list(a_sorted_list, 1, "Sebastian", 21);
                    assert_person_in_list(a_sorted_list, 2, "Matias"   , 24);
                    assert_person_in_list(a_sorted_list, 3, "Gaston"   , 25);
                    assert_person_in_list(a_sorted_list, 4, "Ezequiel" , 25);
                }

                void _verify_a_sort_with_multiple_comparators(t_list* (*sorted_list_generator)()) {
                	list_add(list, persona_create("Ezequiel", 25));
                    list_add(list, persona_create("Julian"  , 25));
                    list_add(list, persona_create("Facundo" , 25));
                    list_sort(list, (void*) _ayudantes_alfabetico);

                    t_list* a_sorted_list = sorted_list_generator();

                    assert_person_in_list(a_sorted_list, 0, "Daniela"  , 19);
                    assert_person_in_list(a_sorted_list, 1, "Sebastian", 21);
                    assert_person_in_list(a_sorted_list, 2, "Matias"   , 24);
                    assert_person_in_list(a_sorted_list, 3, "Ezequiel" , 25);
                    assert_person_in_list(a_sorted_list, 4, "Facundo"  , 25);
                    assert_person_in_list(a_sorted_list, 5, "Gaston"   , 25);
                    assert_person_in_list(a_sorted_list, 6, "Julian"   , 25);
                }

                before {
                    list_add(list, persona_create("Matias"   , 24));
                    list_add(list, persona_create("Gaston"   , 25));
                    list_add(list, persona_create("Sebastian", 21));
                    list_add(list, persona_create("Daniela"  , 19));
                } end

                describe ("Sort - with side effect") {

                    t_list* __sorted_list() {
                        list_sort(list, (void*) _ayudantes_menor);
                        return list;
                    }


                    it("should sort a list without duplicated values") {
                        _verify_a_sort_without_duplicates(__sorted_list);
                    } end

                    it("should sort a list with duplicated values") {
                        _verify_a_sort_with_duplicates(__sorted_list);
                    } end

                    it("should sort a list with multiple comparators") {
                        _verify_a_sort_with_multiple_comparators(__sorted_list);
                    } end

                } end

                describe ("Sorted - without side effect") {

                    t_list* new_list = NULL;

                    t_list* __sorted_list() {
                        new_list = list_sorted(list, (void*) _ayudantes_menor);
                        return new_list;
                    }

                    after {
                        list_destroy(new_list);
                    } end

                    it("should sort a list without duplicated values") {
                        _verify_a_sort_without_duplicates(__sorted_list);
                    } end

                    it("should sort a list with duplicated values") {
                        _verify_a_sort_with_duplicates(__sorted_list);
                    } end

                    it("should sort a list with multiple comparators") {
                        _verify_a_sort_with_multiple_comparators(__sorted_list);
                    } end

                } end

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

        describe("Fold1") {
            before {
                list_add(list, persona_create("Nicolas", 6));
                list_add(list, persona_create("Matias", 70));
                list_add(list, persona_create("Juan", 124));
                list_add(list, persona_create("Juan Manuel", 1));
                list_add(list, persona_create("Sebastian", 8));
                list_add(list, persona_create("Rodrigo", 40));
            } end

            it("should fold all values into a single one, starting with first element") {
                t_person* get_oldest_person(t_person* person1, t_person* person2) {
                    return person1->age >= person2->age ? person1 : person2;
                }

                t_person* oldestPerson = (t_person*) list_fold1(list, (void*) get_oldest_person);

                assert_person(oldestPerson, "Juan", 124);
            } end

            it("should get minimum") {
                t_person* youngestPerson = (t_person*) list_get_minimum(list, (void*)_ayudantes_minimo_edad);

                assert_person(youngestPerson, "Juan Manuel", 1);
            } end

            it("should get maximum") {
                t_person* oldestPerson = (t_person*) list_get_maximum(list, (void*)_ayudantes_maximo_edad);

                assert_person(oldestPerson, "Juan", 124);
            } end

        } end

        describe ("Fold") {

            before {
                list_add(list, persona_create("Jorge", 24));
                list_add(list, persona_create("Matias", 70));
                list_add(list, persona_create("Juan", 124));
                list_add(list, persona_create("Nicolas", 6));
                list_add(list, persona_create("Juan Manuel", 1));
                list_add(list, persona_create("Sebastian", 8));
                list_add(list, persona_create("Rodrigo", 40));
            } end

            it("should fold all list values into a single one, depending on what the given function does") {

                t_person* seedPerson = persona_create("Maximiliano", 150);

                t_person* get_oldest_person(t_person* person1, t_person* person2) {
                    return person1->age >= person2->age ? person1 : person2;
                }

                t_person* oldestPerson = (t_person*) list_fold(list, seedPerson, (void*) get_oldest_person);

                should_int(oldestPerson->age) be equal to(150);

                persona_destroy(seedPerson);
            } end


            it("should fold all values using a intial value with different type") {
                int add_age(int accum, t_person* person) {
                    return accum + person->age;
                }

                int sum = (int)list_fold(list, 0, (void*) add_age);
                should_int(sum) be equal to(273);
            } end

        } end

        describe("Iterator") {
            before {
                list_add(list, persona_create("Juan", 124));
                list_add(list, persona_create("Nicolas", 6));
                list_add(list, persona_create("Matias", 70));
                list_add(list, persona_create("Juan Manuel", 1));
                list_add(list, persona_create("Sebastian", 8));
                list_add(list, persona_create("Rodrigo", 40));
                list_add(list, persona_create("Agustin", 21));
                list_add(list, persona_create("Juan Pablo", 33));
            } end

            it("Should iterate all elements") {
                char* names[] = {"Juan", "Nicolas", "Matias", "Juan Manuel", "Sebastian", "Rodrigo", "Agustin", "Juan Pablo"};

                t_list_iterator* list_iterator = list_iterator_create(list);
                while(list_iterator_has_next(list_iterator)) {
                    t_person* person = list_iterator_next(list_iterator);
                    should_string(person->name) be equal to (names[list_iterator->index]);
                }
                list_iterator_destroy(list_iterator);
            } end

            it("Should iterate an empty list") {
                t_list* empty_list = list_create();
                t_list_iterator* list_iterator = list_iterator_create(empty_list);
                while(list_iterator_has_next(list_iterator)) {
                    t_person* person = list_iterator_next(list_iterator);
                    should_bool (true) be falsey;
                }
                list_iterator_destroy(list_iterator);
                list_destroy(empty_list);
            } end

            it("Should remove an element") {
                char* names[] = {"Nicolas", "Matias", "Sebastian", "Rodrigo", "Agustin"};
                t_list_iterator* list_iterator = list_iterator_create(list);
                while(list_iterator_has_next(list_iterator)) {
                    t_person* person = list_iterator_next(list_iterator);
                    if(string_contains(person->name, "Juan")) {
                        list_iterator_remove(list_iterator);
                        persona_destroy(person);
                        continue;
                    }
                    should_string(person->name) be equal to (names[list_iterator->index]);
                }
                list_iterator_destroy(list_iterator);
                should_int(list->elements_count) be equal to (5);
                assert_person_in_list(list, 0, "Nicolas"  ,  6);
                assert_person_in_list(list, 1, "Matias"   , 70);
                assert_person_in_list(list, 2, "Sebastian",  8);
                assert_person_in_list(list, 3, "Rodrigo"  , 40);
                assert_person_in_list(list, 4, "Agustin"  , 21);
            } end
        } end

    } end

}
