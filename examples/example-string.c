/*
 * example-string-operactions.c
 *
 *  Created on: Feb 3, 2012
 *      Author: shinichi
 */

#include <stdio.h>
#include <stdlib.h>
#include <commons/string.h>


int main(int argc, char **argv) {
	t_string string = string_new("");
	string_append(&string, "hola");
	string_append(&string, " ");
	string_append(&string, "Mundo!");
	puts(string);
	printf("Is equal: %s\n",
			string_equals_ignore_case(string, "HOLA MUNDO!") ? "True" : "False");
	string_destroy(string);

	string = string_duplicate("Holas como va ?");
	string_to_upper(string);
	puts(string);
	string_to_lower(string);
	puts(string);
	string_capitalized(string);
	puts(string);
	string_destroy(string);

	string = string_duplicate("   LALALALA   ");
	string_trim(&string);
	printf("|%s|\n", string);
	string_destroy(string);

	string = string_duplicate("   LALALALA   ");
	string_trim_left(&string);
	printf("|%s|\n", string);
	string_destroy(string);

	string = string_duplicate("   LALALALA   ");
	string_trim_right(&string);
	printf("|%s|\n", string);
	string_destroy(string);

	return EXIT_SUCCESS;
}

