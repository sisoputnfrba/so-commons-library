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
	t_queue * queue = queue_create();

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
	t_queue * queue = queue_create();

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

	queue_destroy_and_destroy_elements(queue, (void*) persona_destroy);
}

static void test_queue_clean() {
	t_queue * queue = queue_create();

	queue_push(queue, persona_create("Matias", 24));
	queue_push(queue, persona_create("Gaston", 25));

	CU_ASSERT_EQUAL(queue_size(queue), 2);
	CU_ASSERT_FALSE(queue_is_empty(queue));

	queue_clean_and_destroy_elements(queue, (void*) persona_destroy);

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
		CU_TEST_INFO_NULL};

CUNIT_MAKE_SUITE(queue, "Test Queue TAD", init_suite, clean_suite, tests)
