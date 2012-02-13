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

int main(int argc, char **argv) {
	t_list * list = list_create();

	char *val1 = malloc( sizeof("Hola") );
	strcpy(val1, "Hola");

	char *val2 = malloc( sizeof("Mundo") );
	strcpy(val2, "Mundo");

	list_add(list, val1);
	list_add(list, val2);

	char * val = list_get(list, 0);

	assert( strcmp("Hola", val) == 0 );

	val = list_get(list, 1);

	assert( strcmp("Mundo", val) == 0 );


	void print_element(char *val){
		printf("%s\n", val);
	}

	// print_element es casteado a void* solo para que el compilador no tire
	// warning con el tipo de dato
	list_iterator(list, (void*)print_element);

	list_destroy(list, free);

	return EXIT_SUCCESS;
}
