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

static int init_suite(){
	return 0;
}


static int clean_suite(){
	return 0;
}

static void test_list_add() {
	t_list * list = list_create(free);

	char *val1 = malloc( sizeof("Hola") );
	strcpy(val1, "Hola");

	char *val2 = malloc( sizeof("Mundo") );
	strcpy(val2, "Mundo");

	list_add(list, val1);
	list_add(list, val2);

	char * val = list_get(list, 0);

	CU_ASSERT_STRING_EQUAL( val, "Hola");

	val = list_get(list, 1);

	CU_ASSERT_STRING_EQUAL( val, "Mundo");

	list_destroy(list);
	free(val1);
	free(val2);
}

/**********************************************************************************************
 *  							Building the test for CUnit
 *********************************************************************************************/



static CU_TestInfo tests[] = {
  { "Test Add List Element", test_list_add },
  CU_TEST_INFO_NULL,
};

CUNIT_MAKE_SUITE(list, "Test Add List Element", init_suite, clean_suite, tests)
