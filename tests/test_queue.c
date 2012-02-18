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
#include <commons/collections/queue.h>
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

static void test_queue_push_and_pop() {
	// El (void*) delante del persona_destroy es para evitar errores de casteo
	t_queue * queue = queue_create((void*) persona_destroy);

	t_person *p1 = persona_create("Matias", 24);

	queue_push(queue, p1);
	queue_push(queue, persona_create("Gaston", 25));

	CU_ASSERT_EQUAL(queue_size(queue), 2);
	CU_ASSERT_FALSE(queue_is_empty(queue));

	t_person *aux = queue_pop(queue);
	CU_ASSERT_PTR_NOT_NULL( aux);
	CU_ASSERT_STRING_EQUAL( aux->name, "Matias");
	CU_ASSERT_EQUAL( aux->age, 24);
	persona_destroy(aux);

	CU_ASSERT_EQUAL(queue_size(queue), 1);
	CU_ASSERT_FALSE(queue_is_empty(queue));

	aux = queue_pop(queue);
	CU_ASSERT_PTR_NOT_NULL( aux);
	CU_ASSERT_STRING_EQUAL( aux->name, "Gaston");
	CU_ASSERT_EQUAL( aux->age, 25);
	persona_destroy(aux);

	CU_ASSERT_EQUAL(queue_size(queue), 0);
	CU_ASSERT_TRUE(queue_is_empty(queue));

	aux = queue_pop(queue);
	CU_ASSERT_PTR_NULL( aux);

	queue_destroy(queue);
}

static void test_queue_peek() {
	// El (void*) delante del persona_destroy es para evitar errores de casteo
	t_queue * queue = queue_create((void*) persona_destroy);

	queue_push(queue, persona_create("Matias", 24));
	queue_push(queue, persona_create("Gaston", 25));

	CU_ASSERT_EQUAL(queue_size(queue), 2);
	CU_ASSERT_FALSE(queue_is_empty(queue));

	t_person *aux = queue_peek(queue);
	CU_ASSERT_PTR_NOT_NULL( aux);
	CU_ASSERT_STRING_EQUAL( aux->name, "Matias");
	CU_ASSERT_EQUAL( aux->age, 24);

	CU_ASSERT_EQUAL(queue_size(queue), 2);

	aux = queue_peek(queue);
	CU_ASSERT_PTR_NOT_NULL( aux);
	CU_ASSERT_STRING_EQUAL( aux->name, "Matias");
	CU_ASSERT_EQUAL( aux->age, 24);

	CU_ASSERT_EQUAL(queue_size(queue), 2);

	queue_destroy(queue);
}

static void test_queue_clean() {
	// El (void*) delante del persona_destroy es para evitar errores de casteo
	t_queue * queue = queue_create((void*) persona_destroy);

	queue_push(queue, persona_create("Matias", 24));
	queue_push(queue, persona_create("Gaston", 25));

	CU_ASSERT_EQUAL(queue_size(queue), 2);
	CU_ASSERT_FALSE(queue_is_empty(queue));

	queue_clean(queue);

	CU_ASSERT_EQUAL(queue_size(queue), 0);
	CU_ASSERT_TRUE(queue_is_empty(queue));

	queue_destroy(queue);
}


/**********************************************************************************************
 *  							Building the test for CUnit
 *********************************************************************************************/

static CU_TestInfo tests[] = {
		{ "Test Push And Pop Queue Element", test_queue_push_and_pop },
		{ "Test Peek Queue Element", test_queue_peek },
		{ "Test Clean Queue Elements", test_queue_clean },
		CU_TEST_INFO_NULL, };

CUNIT_MAKE_SUITE(queue, "Test Queue TAD", init_suite, clean_suite, tests)
