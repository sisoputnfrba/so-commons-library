/*
 * example-string-operactions.c
 *
 *  Created on: Feb 3, 2012
 *      Author: shinichi
 */

#include <commons/string_operations.h>

#include <stdio.h>

int main(int argc, char **argv) {
	t_string string = string_new("hola");
	string_append(&string, " ");
	string_append(&string, "Mundo!");
	puts(string);
	printf("Is equal: %s",
			string_equals_ignore_case(string, "HOLA MUNDO!") ? "True" : "False");
	string_destroy(string);
	return 0;
}

