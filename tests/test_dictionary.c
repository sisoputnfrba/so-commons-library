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
#include <commons/collections/dictionary.h>
#include <CUnit/CUnit.h>

#include "cunit_tools.h"

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

// --------------------------------------------------------

static int init_suite() {
	return 0;
}

static int clean_suite() {
	return 0;
}

static void test_dictionary_put_and_get() {
	// El (void*) delante del persona_destroy es para evitar errores de casteo
	t_dictionary *dictionary = dictionary_create((void*) persona_destroy);

	t_person *p1 = persona_create("Matias", 24);
	dictionary_put(dictionary, strdup(p1->name), p1);

	t_person *p2 = persona_create("Gaston", 25);
	dictionary_put(dictionary, strdup(p2->name), p2);

	CU_ASSERT_EQUAL(dictionary_size(dictionary), 2);
	CU_ASSERT_FALSE(dictionary_is_empty(dictionary));

	t_person *aux = dictionary_get(dictionary, "Matias");
	CU_ASSERT_PTR_NOT_NULL( aux);
	CU_ASSERT_STRING_EQUAL( aux->name, "Matias");
	CU_ASSERT_EQUAL( aux->age, 24);

	aux = dictionary_get(dictionary, "Gaston");
	CU_ASSERT_PTR_NOT_NULL( aux);
	CU_ASSERT_STRING_EQUAL( aux->name, "Gaston");
	CU_ASSERT_EQUAL( aux->age, 25);

	CU_ASSERT_EQUAL(dictionary_size(dictionary), 2);

	dictionary_destroy(dictionary);
}

static void test_dictionary_remove() {
	// El (void*) delante del persona_destroy es para evitar errores de casteo
	t_dictionary *dictionary = dictionary_create((void*) persona_destroy);

	t_person *p1 = persona_create("Matias", 24);
	dictionary_put(dictionary, strdup(p1->name), p1);

	t_person *p2 = persona_create("Gaston", 25);
	dictionary_put(dictionary, strdup(p2->name), p2);

	CU_ASSERT_EQUAL(dictionary_size(dictionary), 2);
	CU_ASSERT_FALSE(dictionary_is_empty(dictionary));

	t_person *aux = dictionary_remove(dictionary, "Matias");
	CU_ASSERT_PTR_NOT_NULL( aux);
	CU_ASSERT_STRING_EQUAL( aux->name, "Matias");
	CU_ASSERT_EQUAL( aux->age, 24);
	persona_destroy(aux);

	CU_ASSERT_EQUAL(dictionary_size(dictionary), 1);

	aux = dictionary_remove(dictionary, "Gaston");
	CU_ASSERT_PTR_NOT_NULL( aux);
	CU_ASSERT_STRING_EQUAL( aux->name, "Gaston");
	CU_ASSERT_EQUAL( aux->age, 25);
	persona_destroy(aux);

	CU_ASSERT_EQUAL(dictionary_size(dictionary), 0);

	dictionary_destroy(dictionary);
}

static void test_dictionary_remove_and_destroy() {
	// El (void*) delante del persona_destroy es para evitar errores de casteo
	t_dictionary *dictionary = dictionary_create((void*) persona_destroy);

	t_person *p1 = persona_create("Matias", 24);
	dictionary_put(dictionary, strdup(p1->name), p1);

	t_person *p2 = persona_create("Gaston", 25);
	dictionary_put(dictionary, strdup(p2->name), p2);

	CU_ASSERT_EQUAL(dictionary_size(dictionary), 2);
	CU_ASSERT_FALSE(dictionary_is_empty(dictionary));

	dictionary_remove_and_destroy(dictionary, "Matias");

	CU_ASSERT_EQUAL(dictionary_size(dictionary), 1);

	CU_ASSERT_PTR_NULL( dictionary_get(dictionary, "Matias"));

	dictionary_remove_and_destroy(dictionary, "Gaston");

	CU_ASSERT_PTR_NULL( dictionary_get(dictionary, "Gaston"));

	CU_ASSERT_EQUAL(dictionary_size(dictionary), 0);

	dictionary_destroy(dictionary);
}

static void test_dictionary_clean() {
	// El (void*) delante del persona_destroy es para evitar errores de casteo
	t_dictionary *dictionary = dictionary_create(free);

	int cont;
	for (cont = 0; cont < 100; cont++) {
		char *key = malloc(5);
		char *value = malloc(20);

		sprintf(key, "%d", cont);
		sprintf(value, "%d%d%d", cont, cont, cont);

		dictionary_put(dictionary, key, value);

	}

	CU_ASSERT_EQUAL(dictionary_size(dictionary), 100);
	CU_ASSERT_FALSE(dictionary_is_empty(dictionary));

	dictionary_clean(dictionary);

	CU_ASSERT_EQUAL(dictionary_size(dictionary), 0);
	CU_ASSERT_TRUE(dictionary_is_empty(dictionary));

	dictionary_destroy(dictionary);
}


/**********************************************************************************************
 *  							Building the test for CUnit
 *********************************************************************************************/

static CU_TestInfo tests[] = {
		{ "Test Put And Get Dictionary Element", test_dictionary_put_and_get },
		{ "Test Clean Dictionary Elements", test_dictionary_clean },
		{ "Test Remove Dictionary Elements", test_dictionary_remove },
		{ "Test Remove And Destroy Dictionary Elements", test_dictionary_remove_and_destroy },
		CU_TEST_INFO_NULL, };

CUNIT_MAKE_SUITE(dictionary, "Test Dictionary TAD", init_suite, clean_suite, tests)
