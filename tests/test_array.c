/*
 * test_array.c
 *
 *  Created on: 20/03/2013
 *      Author: federico
 */
#include <commons/collections/array.h>
#include <CUnit/CUnit.h>

#define ELEMENT_COUNT 5

static int numbers[ELEMENT_COUNT];
static size_t element_size;


int init_suite(void){

	element_size = sizeof(int);

	numbers[0] = 1;
	numbers[1] = 7;
	numbers[2] = 5;
	numbers[3] = 3;
	numbers[4] = 11;

	return 0;
}

int clean_suite(void){

	element_size = 0;

	for(int position = 0; position < ELEMENT_COUNT; position++) numbers[position] = 0;

	return 0;
}

/*---------------------Funciones Auxiliares------------------------*/

t_array* load_array_numbers(t_array* array, int numbers[ELEMENT_COUNT]) {
	for (int element = 0; element < ELEMENT_COUNT; element++) {
		array_add(array, &numbers[element]);
	}
	return array;
}

/*---------------------Funciones Auxiliares------------------------*/

void test_array_create(){
	t_array *array = array_create( element_size );

	CU_ASSERT_PTR_NULL(array->first_element);

	CU_ASSERT(array->element_count == 0);

	CU_ASSERT( array->element_size == element_size);

	array_destroy(array);
}

void test_array_add_single_element(){
	t_array *array = array_create( element_size );

	array_add(array, &numbers[0]);

	CU_ASSERT_PTR_NOT_NULL(array->first_element);
	CU_ASSERT(array->element_count == 1);
	CU_ASSERT( array->element_size == element_size);

	int *element = array_get(array, 0);
	CU_ASSERT_EQUAL(*element, numbers[0]);



	array_destroy(array);

}

void test_array_add_some_elements(){
	t_array *array = array_create( element_size );

	load_array_numbers(array, numbers);

	CU_ASSERT_PTR_NOT_NULL(array->first_element);
	CU_ASSERT(array->element_count == 5);
	CU_ASSERT( array->element_size == element_size);

	for (int element = 0; element < ELEMENT_COUNT; element++)
		CU_ASSERT_EQUAL( *(int*)(array_get(array, element)), numbers[element]);

	array_destroy(array);
}

/**********************************************************************************************
 *  							Building the test for CUnit
 *********************************************************************************************/

static CU_TestInfo tests[] = {
		{ "Test create a simple instance of array", test_array_create},
		{ "Test add single element to array", test_array_add_single_element},
		{ "Test add some elements to array", test_array_add_some_elements},
		CU_TEST_INFO_NULL,
};

CUNIT_MAKE_SUITE(string, "Test Array ADT", init_suite, clean_suite, tests)

