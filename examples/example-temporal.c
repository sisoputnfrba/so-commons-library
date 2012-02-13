/*
 * example-temporal.c
 *
 *  Created on: Feb 5, 2012
 *      Author: Prieto, Gaston
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <commons/temporal.h>

int main(int argc, char **argv) {
	int i = 0;
	t_string time;

	for (i = 0; i < 100; ++i) {
		time = temporal_get_string_time();
		puts(time);
		string_destroy(time);
		usleep(500);
	}
	return EXIT_SUCCESS;
}
