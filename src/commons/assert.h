/* 
 * File:   assert.h
 * Author: shinichi
 *
 * Created on September 12, 2013, 8:14 PM
 */

#ifndef ASSERT_H
#define	ASSERT_H

#include <stdbool.h>

void assert_is_true(bool result_expression);
void assert_is_false(bool result_expression);
void assert_equals_by_reference(void* expected, void* value);
void assert_string_equals(char* expected, char* value);
void assert_n_string_equals(char* expected, int length, char* value);
void assert_is_null(void* value);
void assert_is_not_null(void* value);


#endif	/* ASSERT_H */

