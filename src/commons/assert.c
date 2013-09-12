/* 
 * File:   assert.c
 * Author: shinichi
 *
 * Created on September 12, 2013, 8:15 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "./assert.h"
#include "./string.h"
#include <assert.h>


void assert_is_true(bool result_expression) {
    if (!result_expression) printf("[ASSERT_FAILED] assert_is_true: failed");
    assert(result_expression);
}

void assert_is_false(bool result_expression) {
    if (result_expression) printf("[ASSERT_FAILED] assert_is_false: failed");
    assert(!result_expression);
}

void assert_equals_by_reference(void* expected, void* value) {
    bool result_expression = expected == value;
    if (!result_expression) {
        printf("[ASSERT_FAILED] Los punteros [%p] y [%p] no apuntan a lo mismo\n", expected, value);
    }
    assert(result_expression);
}

void assert_string_equals(char* expected, char* value) {
    bool result_expression = string_equals(value, expected);
    if (!result_expression) {
        printf("[ASSERT_FAILED] Se esperaba un [%s] y es un [%s]\n", expected, value);
    }
    assert(result_expression);
}

void assert_n_string_equals(char* expected, int length, char* value) {
    bool result_expression = string_n_equals(expected, value, value);
    if (!result_expression) {
        printf("[ASSERT_FAILED] Se esperaba un [%s] y es un [%s]\n", expected, value);
    }
    assert(result_expression);
}

void assert_equals_ignore_case(char* expected, int length, char* value) {
    bool result_expression = string_equals_ignore_case(expected, value, value);
    if (!result_expression) {
        printf("[ASSERT_FAILED] Se esperaba un [%s] y es un [%s]\n", expected, value);    
    }
    assert(result_expression);
}

void assert_is_null(void* value) {
    bool result_expression = value == NULL;
    if (!result_expression) {
        printf("[ASSERT_FAILED] El valor en la posicion [%p] no es null\n", value);
    }
    assert(result_expression);
}

void assert_is_not_null(void* value) {
    bool result_expression = value != NULL;
    if (!result_expression) {
        printf("[ASSERT_FAILED] El valor en la posicion [%p] es null\n", value);    
    }
    assert(result_expression);
}

