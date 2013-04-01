/*
 * test_array.c
 *
 *  Created on: 20/03/2013
 *      Author: federico
 */
#include <commons/collections/array.h>
#include <CUnit/CUnit.h>
#include <stdlib.h>

#include "cunit_tools.h"

#define ELEMENT_COUNT 5

static int* numbers[ELEMENT_COUNT];
static size_t element_size;


int init_suite(void){

	element_size = sizeof(int);

	for(int position = 0; position < 5; position++) numbers[position] = malloc(element_size);
	*(numbers[0]) = 1;
	*(numbers[1]) = 7;
	*(numbers[2]) = 5;
	*(numbers[3]) = 3;
	*(numbers[4]) = 11;

	return 0;
}

int clean_suite(void){

	element_size = 0;

	for(int position = 0; position < ELEMENT_COUNT; position++) free( numbers[position] );

	return 0;
}

/*---------------------Funciones Auxiliares------------------------*/

t_array* load_array_numbers(t_array* array, int *numbers[ELEMENT_COUNT]) {
	for (int element = 0; element < ELEMENT_COUNT; element++) {
		array_add(array, numbers[element]);
	}
	return array;
}

/*---------------------Funciones Auxiliares------------------------*/

void test_array_create(){
	t_array *array = array_create( element_size );

	CU_ASSERT_PTR_NULL(array->first_element);

	CU_ASSERT(array->element_count == 0);

	array_destroy(array);
}

void test_array_add_single_element(){
	t_array *array = array_create( element_size );

	array_add(array, numbers[0]);

	CU_ASSERT_PTR_NOT_NULL(array->first_element);
	CU_ASSERT(array->element_count == 1);

	int *element = array_get(array, 0);
	CU_ASSERT_EQUAL( element, numbers[0] );

	array_destroy(array);
}

void test_array_add_null_element(){
	t_array *array = array_create( element_size );

	array_add(array, NULL);

	CU_ASSERT_PTR_NOT_NULL(array->first_element);
	CU_ASSERT(array->element_count == 1);

	int *element = array_get(array, 0);
	CU_ASSERT_EQUAL(element, NULL);

	array_destroy(array);
}

void test_array_add_some_elements(){
	t_array *array = array_create( element_size );

	load_array_numbers(array, numbers);

	CU_ASSERT_PTR_NOT_NULL(array->first_element);
	CU_ASSERT(array->element_count == 5);

	for (int element = 0; element < ELEMENT_COUNT; element++)
		CU_ASSERT_EQUAL( *(int*)(array_get(array, element)), *(numbers[element]) );

	array_destroy(array);
}

void test_array_remove_element(){
	t_array *array = array_create( element_size );
	int elements[] = {1,7,3,11};

	load_array_numbers(array, numbers);

	int *element = array_remove(array, 2);

	CU_ASSERT_EQUAL(*element, 5);
	CU_ASSERT_EQUAL(array_size(array), 4);

	for(int position = 0 ; position < 4; position++){
		element = array_get(array, position);
		CU_ASSERT_EQUAL(*element, elements[position]);
	}

	array_destroy(array);
}


/**********************************************************************************************
 *  							Building the test for CUnit
 *********************************************************************************************/

static CU_TestInfo tests[] = {
		{ "Test create a simple instance of array", test_array_create},
		{ "Test add single element to array", test_array_add_single_element},
		{ "Test add some elements to array", test_array_add_some_elements},
		{ "Test add null element to array", test_array_add_null_element},
		{ "Test remove element to array", test_array_remove_element},
		CU_TEST_INFO_NULL,
};

CUNIT_MAKE_SUITE(array, "Test Array ADT", init_suite, clean_suite, tests)

