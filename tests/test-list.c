/*
 * example-list.c
 *
 *  Created on: 13/02/2012
 *      Author: fviale
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <commons/collections/list.h>
#include <CUnit/CUnit.h>

#include "cunit_tools.h"

// ------------------ HELP FUNCTION'S ---------------------

typedef struct {
	char *name;
	unsigned char age;
} t_person;

t_person *persona_create(char *name, unsigned char age){
	t_person *new = malloc( sizeof(t_person) );
	new->name = strdup(name);
	new->age = age;
	return new;
}

void persona_destroy(t_person *self){
	free(self->name);
	free(self);
}

// --------------------------------------------------------

static int init_suite() {
	return 0;
}

static int clean_suite() {
	return 0;
}

static void test_list_add() {
	// El (void*) delante del persona_destroy es para evitar errores de casteo
	t_list * list = list_create((void*) persona_destroy);

	t_person *p1 = persona_create("Matias", 24);

	list_add(list, p1);
	list_add(list, persona_create("Gaston", 25));

	t_person *aux = list_get(list, 0);
	CU_ASSERT_PTR_NOT_NULL( aux);
	CU_ASSERT_STRING_EQUAL( aux->name, "Matias");
	CU_ASSERT_EQUAL( aux->age, 24);

	aux = list_get(list, 1);
	CU_ASSERT_PTR_NOT_NULL( aux);
	CU_ASSERT_STRING_EQUAL( aux->name, "Gaston");
	CU_ASSERT_EQUAL( aux->age, 25);

	CU_ASSERT_EQUAL(list_size(list), 2);

	list_destroy(list);
}

static void test_list_add_in_index() {
	// El (void*) delante del persona_destroy es para evitar errores de casteo
	t_list * list = list_create((void*) persona_destroy);

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

	CU_ASSERT_EQUAL(list_size(list), 4);

	list_destroy(list);
}

static void test_list_find() {
	t_list * list = list_create((void*) persona_destroy);

	list_add(list, persona_create("Matias", 24));
	list_add(list, persona_create("Gaston", 25));
	list_add(list, persona_create("Sebastian", 21));
	list_add(list, persona_create("Daniela", 19));
	list_add(list, persona_create("Facundo", 25));

	int _is_daniela(t_person *p) {
		return strcmp(p->name, "Daniela") == 0;
	}

	// Usamos (void*) para inferir el tipo, y que el compilador no tire error de casteo
	t_person *aux = list_find(list, (void*) _is_daniela);
	CU_ASSERT_PTR_NOT_NULL( aux);
	CU_ASSERT_STRING_EQUAL( aux->name, "Daniela");
	CU_ASSERT_EQUAL( aux->age, 19);

	int _is_chuck_norris(t_person *p) {
		return strcmp(p->name, "Chuck Norris") == 0;
	}
	aux = list_find(list, (void*) _is_chuck_norris);
	CU_ASSERT_PTR_NULL(aux);
	// it knows you cannot finds Chuck Norris, he finds you.

	CU_ASSERT_EQUAL(list_size(list), 5);

	list_destroy(list);
}

static void test_list_replace() {
	// El (void*) delante del persona_destroy es para evitar errores de casteo
	t_list * list = list_create((void*) persona_destroy);

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

	list_destroy(list);
}

static void test_list_remove() {
	t_list * list = list_create((void*) persona_destroy);

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

	list_destroy(list);
}

static void test_list_remove_and_destroy() {
	t_list * list = list_create((void*) persona_destroy);

	t_person *p1 = persona_create("Matias", 24);

	list_add(list, p1);
	list_add(list, persona_create("Gaston", 25));

	list_remove_and_destroy(list, 0);

	CU_ASSERT_EQUAL(list_size(list), 1);

	t_person *aux = list_get(list, 0);
	CU_ASSERT_PTR_NOT_NULL( aux);
	CU_ASSERT_STRING_EQUAL( aux->name, "Gaston");
	CU_ASSERT_EQUAL( aux->age, 25);

	list_destroy(list);
}

static void test_list_remove_by_closure() {
	t_list * list = list_create((void*) persona_destroy);

	list_add(list, persona_create("Matias", 24));
	list_add(list, persona_create("Gaston", 25));
	list_add(list, persona_create("Sebastian", 21));
	list_add(list, persona_create("Daniela", 19));
	list_add(list, persona_create("Facundo", 25));

	int _is_daniela(t_person *p) {
		return strcmp(p->name, "Daniela") == 0;
	}

	// Usamos (void*) para inferir el tipo, y que el compilador no tire error de casteo
	t_person *aux = list_remove_by_closure(list, (void*) _is_daniela);
	CU_ASSERT_PTR_NOT_NULL( aux);
	CU_ASSERT_STRING_EQUAL( aux->name, "Daniela");
	CU_ASSERT_EQUAL( aux->age, 19);

	CU_ASSERT_EQUAL(list_size(list), 4);

	list_destroy(list);
}

static void test_list_iterate() {

	t_person *ayudantes[] = {
			persona_create("Matias", 24),
			persona_create("Gaston", 25),
			persona_create("Sebastian", 21),
			persona_create("Daniela", 19),
			persona_create("Facundo", 25),
	};

	t_list * list = list_create((void*) persona_destroy);

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

	// Usamos (void*) para inferir el tipo, y que el compilador no tire error de casteo
	list_iterate(list, (void*) _list_elements);

	list_destroy(list);
}


static void test_list_clean() {
	t_list * list = list_create((void*) persona_destroy);

	list_add(list, persona_create("Matias", 24));
	list_add(list, persona_create("Gaston", 25));
	list_clean(list);

	CU_ASSERT_EQUAL(list_size(list), 0);
	CU_ASSERT_TRUE(list_is_empty(list));

	t_person *aux = list_get(list, 0);
	CU_ASSERT_PTR_NULL( aux);

	aux = list_get(list, 1);
	CU_ASSERT_PTR_NULL( aux);

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
		{ "Test Iterator List Element", test_list_iterate },
		{ "Test Clean List Element", test_list_clean },
		CU_TEST_INFO_NULL, };

CUNIT_MAKE_SUITE(list, "Test Add List Element", init_suite, clean_suite, tests)
