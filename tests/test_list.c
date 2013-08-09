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
#include <CUnit/CUnit.h>

#include "cunit_tools.h"

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

t_person *ayudantes[5];

// --------------------------------------------------------

static int init_suite() {
	ayudantes[0] = persona_create("Matias", 24);
	ayudantes[1] = persona_create("Gaston", 25);
	ayudantes[2] = persona_create("Sebastian", 21);
	ayudantes[3] = persona_create("Daniela", 19);
	ayudantes[4] = persona_create("Facundo", 25);
	return 0;
}

static int clean_suite() {
	persona_destroy(ayudantes[0]);
	persona_destroy(ayudantes[1]);
	persona_destroy(ayudantes[2]);
	persona_destroy(ayudantes[3]);
	persona_destroy(ayudantes[4]);
	return 0;
}

static void test_list_add() {
	t_list * list = list_create();

	t_person *p1 = persona_create("Matias", 24);

	list_add(list, p1);
	list_add(list, persona_create("Gaston", 25));

	t_person *aux = list_get(list, 0);
	CU_ASSERT_PTR_NOT_NULL(aux);
	CU_ASSERT_STRING_EQUAL(aux->name, "Matias");
	CU_ASSERT_EQUAL(aux->age, 24);

	aux = list_get(list, 1);
	CU_ASSERT_PTR_NOT_NULL(aux);
	CU_ASSERT_STRING_EQUAL(aux->name, "Gaston");
	CU_ASSERT_EQUAL(aux->age, 25);

	CU_ASSERT_EQUAL(list_size(list), 2);

	list_destroy_and_destroy_elements(list, (void*) persona_destroy);
}

static void test_list_add_in_index() {
	// El (void*) delante del persona_destroy es para evitar errores de casteo
	t_list * list = list_create();

	list_add(list, persona_create("Matias", 24));
	list_add(list, persona_create("Gaston", 25));
	list_add(list, persona_create("Facundo", 25));

	list_add_in_index(list, 1, persona_create("Sebastian", 21));

	t_person *aux = list_get(list, 0);
	CU_ASSERT_PTR_NOT_NULL( aux);
	CU_ASSERT_STRING_EQUAL( aux->name, "Matias");
	CU_ASSERT_EQUAL( aux->age, 24);

	aux = list_get(list, 1);
	CU_ASSERT_PTR_NOT_NULL( aux);
	CU_ASSERT_STRING_EQUAL( aux->name, "Sebastian");
	CU_ASSERT_EQUAL( aux->age, 21);

	aux = list_get(list, 2);
	CU_ASSERT_PTR_NOT_NULL( aux);
	CU_ASSERT_STRING_EQUAL( aux->name, "Gaston");
	CU_ASSERT_EQUAL( aux->age, 25);

	int index_last_element = list_size(list);
	list_add_in_index(list, index_last_element, persona_create("Dani", 21));

	aux = list_get(list, index_last_element);
	CU_ASSERT_PTR_NOT_NULL( aux);
	CU_ASSERT_STRING_EQUAL( aux->name, "Dani");
	CU_ASSERT_EQUAL( aux->age, 21);

	CU_ASSERT_EQUAL(list_size(list), 5);

	list_destroy_and_destroy_elements(list, (void*) persona_destroy);
}

static void test_list_find() {
	t_list * list = list_create();

	list_add(list, persona_create("Matias", 24));
	list_add(list, persona_create("Gaston", 25));
	list_add(list, persona_create("Sebastian", 21));
	list_add(list, persona_create("Daniela", 19));
	list_add(list, persona_create("Facundo", 25));

	int _is_daniela(t_person *p) {
		return string_equals_ignore_case(p->name, "Daniela");
	}

	// Usamos (void*) para inferir el tipo, y que el compilador no tire error de casteo
	t_person *aux = list_find(list, (void*) _is_daniela);
	CU_ASSERT_PTR_NOT_NULL( aux);
	CU_ASSERT_STRING_EQUAL( aux->name, "Daniela");
	CU_ASSERT_EQUAL( aux->age, 19);

	int _is_chuck_norris(t_person *p) {
		return string_equals_ignore_case(p->name, "Chuck Norris");
	}
	aux = list_find(list, (void*) _is_chuck_norris);
	CU_ASSERT_PTR_NULL(aux);
	// it knows you cannot finds Chuck Norris, he finds you.

	CU_ASSERT_EQUAL(list_size(list), 5);

	list_destroy_and_destroy_elements(list, (void*) persona_destroy);
}

static void test_list_replace() {
	t_list * list = list_create();

	list_add(list, persona_create("Matias", 24));
	list_add(list, persona_create("Gaston", 25));
	list_add(list, persona_create("Sebastian", 21));
	list_add(list, persona_create("Ezequiel", 25));
	list_add(list, persona_create("Facundo", 25));

	t_person *aux = list_replace(list, 3, persona_create("Daniela", 19));
	CU_ASSERT_PTR_NOT_NULL( aux);
	CU_ASSERT_STRING_EQUAL( aux->name, "Ezequiel");
	CU_ASSERT_EQUAL( aux->age, 25);
	persona_destroy(aux);

	aux = list_get(list, 3);
	CU_ASSERT_PTR_NOT_NULL( aux);
	CU_ASSERT_STRING_EQUAL( aux->name, "Daniela");
	CU_ASSERT_EQUAL( aux->age, 19);

	CU_ASSERT_EQUAL(list_size(list), 5);

	list_destroy_and_destroy_elements(list, (void*) persona_destroy);
}

static void test_list_remove() {
	t_list * list = list_create();

	t_person *p1 = persona_create("Matias", 24);

	list_add(list, p1);
	list_add(list, persona_create("Gaston", 25));

	t_person *aux = list_remove(list, 0);
	CU_ASSERT_PTR_NOT_NULL( aux);
	CU_ASSERT_STRING_EQUAL( aux->name, "Matias");
	CU_ASSERT_EQUAL( aux->age, 24);
	persona_destroy(aux);

	CU_ASSERT_EQUAL(list_size(list), 1);

	aux = list_get(list, 0);
	CU_ASSERT_PTR_NOT_NULL( aux);
	CU_ASSERT_STRING_EQUAL( aux->name, "Gaston");
	CU_ASSERT_EQUAL( aux->age, 25);

	list_destroy_and_destroy_elements(list, (void*) persona_destroy);
}

static void test_list_remove_and_destroy() {
	t_list * list = list_create();

	t_person *p1 = persona_create("Matias", 24);

	list_add(list, p1);
	list_add(list, persona_create("Gaston", 25));

	list_remove_and_destroy_element(list, 0, (void*) persona_destroy);

	CU_ASSERT_EQUAL(list_size(list), 1);

	t_person *aux = list_get(list, 0);
	CU_ASSERT_PTR_NOT_NULL(aux);
	CU_ASSERT_STRING_EQUAL(aux->name, "Gaston");
	CU_ASSERT_EQUAL(aux->age, 25);
	persona_destroy(aux);

	list_destroy(list);
}

static void test_list_remove_by_closure() {
	t_list * list = list_create();

	list_add(list, persona_create("Matias", 24));
	list_add(list, persona_create("Gaston", 25));
	list_add(list, persona_create("Sebastian", 21));
	list_add(list, persona_create("Daniela", 19));
	list_add(list, persona_create("Facundo", 25));

	bool _is_daniela(t_person *p) {
		return string_equals_ignore_case(p->name, "Daniela");
	}

	t_person *aux = list_remove_by_condition(list, (void*) _is_daniela);
	CU_ASSERT_PTR_NOT_NULL(aux);
	CU_ASSERT_STRING_EQUAL(aux->name, "Daniela");
	CU_ASSERT_EQUAL(aux->age, 19);
	persona_destroy(aux);

	CU_ASSERT_EQUAL(list_size(list), 4);

	list_destroy_and_destroy_elements(list, (void*) persona_destroy);
}

static void test_list_iterate() {

	t_list * list = list_create();

	list_add(list, ayudantes[0]);
	list_add(list, ayudantes[1]);
	list_add(list, ayudantes[2]);
	list_add(list, ayudantes[3]);
	list_add(list, ayudantes[4]);

	int index = 0;

	void _list_elements(t_person *p) {
		CU_ASSERT_PTR_NOT_NULL( p);
		CU_ASSERT_STRING_EQUAL(ayudantes[index]->name, p->name);
		index++;
	}

	list_iterate(list, (void*) _list_elements);

	list_destroy(list);
}


static void test_list_clean() {
	t_list * list = list_create();

	list_add(list, persona_create("Matias", 24));
	list_add(list, persona_create("Gaston", 25));
	list_clean_and_destroy_elements(list, (void*) persona_destroy);

	CU_ASSERT_EQUAL(list_size(list), 0);
	CU_ASSERT_TRUE(list_is_empty(list));

	t_person *aux = list_get(list, 0);
	CU_ASSERT_PTR_NULL( aux);

	aux = list_get(list, 1);
	CU_ASSERT_PTR_NULL( aux);

	list_destroy(list);
}

static void test_list_take() {
	t_list* list = list_create();
	list_add(list, ayudantes[0]);
	list_add(list, ayudantes[1]);
	list_add(list, ayudantes[2]);
	list_add(list, ayudantes[3]);
	list_add(list, ayudantes[4]);

	t_list* sublist = list_take(list, 3);
	CU_ASSERT_PTR_NOT_NULL(sublist);
	CU_ASSERT_EQUAL(list_size(list), 5);
	CU_ASSERT_EQUAL(list_size(sublist), 3);

	t_person* element = list_get(sublist, 0);
	CU_ASSERT_STRING_EQUAL(element->name, ayudantes[0]->name);

	element = list_get(sublist, 1);
	CU_ASSERT_STRING_EQUAL(element->name, ayudantes[1]->name);

	element = list_get(sublist, 2);
	CU_ASSERT_STRING_EQUAL(element->name, ayudantes[2]->name);

	list_destroy(sublist);
	list_destroy(list);
}

static void test_list_take_and_remove() {
	t_list* list = list_create();
	list_add(list, ayudantes[0]);
	list_add(list, ayudantes[1]);
	list_add(list, ayudantes[2]);
	list_add(list, ayudantes[3]);
	list_add(list, ayudantes[4]);

	t_list* sublist = list_take_and_remove(list, 3);
	CU_ASSERT_PTR_NOT_NULL(sublist);
	CU_ASSERT_EQUAL(list_size(list), 2);
	CU_ASSERT_EQUAL(list_size(sublist), 3);

	t_person* element = list_get(sublist, 0);
	CU_ASSERT_STRING_EQUAL(element->name, ayudantes[0]->name);

	element = list_get(sublist, 1);
	CU_ASSERT_STRING_EQUAL(element->name, ayudantes[1]->name);

	element = list_get(sublist, 2);
	CU_ASSERT_STRING_EQUAL(element->name, ayudantes[2]->name);

	element = list_get(list, 0);
	CU_ASSERT_STRING_EQUAL(element->name, ayudantes[3]->name);

	element = list_get(list, 1);
	CU_ASSERT_STRING_EQUAL(element->name, ayudantes[4]->name);

	list_destroy(sublist);
	list_destroy(list);
}

static void test_list_filter() {
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
	CU_ASSERT_PTR_NOT_NULL(filtered);
	CU_ASSERT_EQUAL(list_size(list), 5);
	CU_ASSERT_EQUAL(list_size(filtered), 2);
	list_destroy(filtered);

	bool _is_old(t_person* person) {
		return person->age > 80;
	}

	filtered = list_filter(list, (void*) _is_old);
	CU_ASSERT_PTR_NOT_NULL(filtered);
	CU_ASSERT_EQUAL(list_size(list), 5);
	CU_ASSERT_EQUAL(list_size(filtered), 0);
	list_destroy(filtered);

	list_destroy(list);
}

static void test_list_map() {
	t_list* list = list_create();
	list_add(list, ayudantes[0]);
	list_add(list, ayudantes[1]);
	list_add(list, ayudantes[2]);
	list_add(list, ayudantes[3]);
	list_add(list, ayudantes[4]);

	char* _map_to_name(t_person* person) {
		return string_duplicate(person->name);
	}

	t_list* names = list_map(list, (void*) _map_to_name);
	CU_ASSERT_PTR_NOT_NULL(names);
	CU_ASSERT_EQUAL(list_size(names), 5);

	int i = 0;
	void _verify_name(char* name) {
		CU_ASSERT_STRING_EQUAL(name, ayudantes[i]->name);
		i++;
	}
	list_iterate(names, (void*) _verify_name);
	list_destroy_and_destroy_elements(names, free);

	list_destroy(list);
}

static void test_list_add_all() {
	t_list* principal = list_create();
	t_list* other = list_create();

	list_add(principal, ayudantes[0]);
	list_add(principal, ayudantes[1]);
	list_add(principal, ayudantes[2]);
	list_add(other, ayudantes[3]);
	list_add(other, ayudantes[4]);

	list_add_all(principal, other);

	CU_ASSERT_EQUAL(list_size(principal), 5);
	CU_ASSERT_PTR_EQUAL(list_get(principal, 0), ayudantes[0]);
	CU_ASSERT_PTR_EQUAL(list_get(principal, 1), ayudantes[1]);
	CU_ASSERT_PTR_EQUAL(list_get(principal, 2), ayudantes[2]);
	CU_ASSERT_PTR_EQUAL(list_get(principal, 3), ayudantes[3]);
	CU_ASSERT_PTR_EQUAL(list_get(principal, 4), ayudantes[4]);

	list_destroy(principal);
	list_destroy(other);
}

static void test_list_sort_empty() {
	t_list *list = list_create();

	list_sort(list, NULL);

	CU_ASSERT(list_is_empty(list));

	list_destroy(list);
}

static void test_list_sort_unique() {
	t_list *list = list_create();

	list_add(list, ayudantes[0]);
	list_add(list, ayudantes[1]);
	list_add(list, ayudantes[2]);
	list_add(list, ayudantes[3]);

	bool _ayudantes_menor(t_person *joven, t_person *menos_joven) {
		return joven->age < menos_joven->age;
	}

	list_sort(list, (void*) _ayudantes_menor);

	CU_ASSERT_PTR_EQUAL(list_get(list, 0), ayudantes[3]);
	CU_ASSERT_PTR_EQUAL(list_get(list, 1), ayudantes[2]);
	CU_ASSERT_PTR_EQUAL(list_get(list, 2), ayudantes[0]);
	CU_ASSERT_PTR_EQUAL(list_get(list, 3), ayudantes[1]);

	list_destroy(list);
}

static void test_list_sort_duplicates() {
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

	CU_ASSERT_PTR_EQUAL(list_get(list, 0), ayudantes[3]);
	CU_ASSERT_PTR_EQUAL(list_get(list, 1), ayudantes[2]);
	CU_ASSERT_PTR_EQUAL(list_get(list, 2), ayudantes[2]);
	CU_ASSERT_PTR_EQUAL(list_get(list, 3), ayudantes[0]);
	CU_ASSERT_PTR_EQUAL(list_get(list, 4), ayudantes[1]);

	list_destroy(list);
}

static void test_list_count_satisfying() {
	t_list *list = list_create();

	bool _ayudante_menor_a_20(void *ayudante) {
		return ((t_person *)ayudante)->age < 20;
	}
	
	CU_ASSERT_EQUAL(list_count_satisfying(list, _ayudante_menor_a_20), 0);
	
	list_add(list, ayudantes[0]);
	
	CU_ASSERT_EQUAL(list_count_satisfying(list, _ayudante_menor_a_20), 0);
	
	list_add(list, ayudantes[1]);
	list_add(list, ayudantes[2]);
	
	CU_ASSERT_EQUAL(list_count_satisfying(list, _ayudante_menor_a_20), 0);
	
	list_add(list, ayudantes[3]);
	
	CU_ASSERT_EQUAL(list_count_satisfying(list, _ayudante_menor_a_20), 1);
	
	list_add(list, ayudantes[2]);
	
	CU_ASSERT_EQUAL(list_count_satisfying(list, _ayudante_menor_a_20), 1);
	
	list_add(list, ayudantes[3]);
	
	CU_ASSERT_EQUAL(list_count_satisfying(list, _ayudante_menor_a_20), 2);
	
	list_clean(list);
	
	CU_ASSERT_EQUAL(list_count_satisfying(list, _ayudante_menor_a_20), 0);

	list_destroy(list);
}

static void test_list_any_satisfy_empty() {
	t_list *list = list_create();
	
	CU_ASSERT_FALSE(list_any_satisfy(list, NULL));

	list_destroy(list);
}

static void test_list_any_satisfy_satisfying() {
	t_list *list = list_create();
	
	list_add(list, ayudantes[0]);
	list_add(list, ayudantes[1]);
	list_add(list, ayudantes[2]);
	list_add(list, ayudantes[3]);
	list_add(list, ayudantes[2]);

	bool _ayudante_menor_a_20(t_person *ayudante) {
		return ayudante->age < 20;
	}
	
	CU_ASSERT_TRUE(list_any_satisfy(list, (void*)_ayudante_menor_a_20));

	list_destroy(list);
}

static void test_list_any_satisfy_not_satisfying() {
	t_list *list = list_create();
	
	list_add(list, ayudantes[0]);
	list_add(list, ayudantes[1]);
	list_add(list, ayudantes[2]);
	list_add(list, ayudantes[3]);
	list_add(list, ayudantes[2]);

	bool _ayudante_menor_a_15(t_person *ayudante) {
		return ayudante->age < 15;
	}
	
	CU_ASSERT_FALSE(list_any_satisfy(list, (void*)_ayudante_menor_a_15));

	list_destroy(list);
}

static void test_list_all_satisfy_empty() {
	t_list *list = list_create();
	
	CU_ASSERT_TRUE(list_all_satisfy(list, NULL));

	list_destroy(list);
}

static void test_list_all_satisfy_satisfying() {
	t_list *list = list_create();
	
	list_add(list, ayudantes[0]);
	list_add(list, ayudantes[1]);
	list_add(list, ayudantes[2]);
	list_add(list, ayudantes[3]);
	list_add(list, ayudantes[2]);

	bool _ayudante_menor_a_30(t_person *ayudante) {
		return ayudante->age < 30;
	}
	
	CU_ASSERT_TRUE(list_all_satisfy(list, (void*)_ayudante_menor_a_30));

	list_destroy(list);
}

static void test_list_all_satisfy_not_satisfying() {
	t_list *list = list_create();
	
	list_add(list, ayudantes[0]);
	list_add(list, ayudantes[1]);
	list_add(list, ayudantes[2]);
	list_add(list, ayudantes[3]);
	list_add(list, ayudantes[2]);

	bool _ayudante_menor_a_20(t_person *ayudante) {
		return ayudante->age < 20;
	}
	
	CU_ASSERT_FALSE(list_all_satisfy(list, (void*)_ayudante_menor_a_20));

	list_destroy(list);
}

/**********************************************************************************************
 *  							Building the test for CUnit
 *********************************************************************************************/

static CU_TestInfo tests[] = {
		{ "Test Add List Element", test_list_add },
		{ "Test Add In Index List Element", test_list_add_in_index },
		{ "Test Find List Element", test_list_find },
		{ "Test Replace List Element", test_list_replace },
		{ "Test Remove List Element", test_list_remove },
		{ "Test Remove And Destroy List Element", test_list_remove_and_destroy },
		{ "Test Remove By Closure List Element", test_list_remove_by_closure },
		{ "Test Iterator List Elements", test_list_iterate },
		{ "Test Clean List Elements", test_list_clean },
		{ "Test take without remove elements", test_list_take},
		{ "Test take with remove elements", test_list_take_and_remove},
		{ "Test filter list", test_list_filter},
		{ "Test map list", test_list_map},
		{ "Test add all", test_list_add_all},
		{ "Test sorting empty list", test_list_sort_empty},
		{ "Test sorting unique elements", test_list_sort_unique},
		{ "Test sorting duplicated elements", test_list_sort_duplicates},
		{ "Test count satisfying", test_list_count_satisfying},
		{ "Test any satisfy empty list", test_list_any_satisfy_empty},
		{ "Test any satisfy satisfying", test_list_any_satisfy_satisfying},
		{ "Test any satisfy not satisfying", test_list_any_satisfy_not_satisfying},
		{ "Test all satisfy empty list", test_list_all_satisfy_empty},
		{ "Test all satisfy satisfying", test_list_all_satisfy_satisfying},
		{ "Test all satisfy not satisfying", test_list_all_satisfy_not_satisfying},
		CU_TEST_INFO_NULL, };

CUNIT_MAKE_SUITE(list, "Test List TAD", init_suite, clean_suite, tests)
