/* 
 * File:   main.c
 * Author: RaniAgus
 *
 * Created on March 24, 2020, 21:11 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <commons/txt.h>
#include <commons/temporal.h>
#include <pthread.h>
#include <unistd.h>

static void print_time() {
	char* date = temporal_get_string_time("day/month/year -- %d/%m/%y\n");
	char* time = temporal_get_string_time("hour:min:sec:milisec -- %H:%M:%S:%MS\n");

	txt_write_in_stdout(date);
	txt_write_in_stdout(time);

	free(date);
	free(time);
}

void test_temporal_gettime() {
	/**
	* @brief El tiempo que se obtiene es correcto.
	*/
	t_temporal *temporal = temporal_create();
	sleep(2);
	
	printf("\ntest_temporal_gettime: %ldms (expected: ~2000ms)\n\n", temporal_gettime(temporal));

	temporal_destroy(temporal);
}

void test_temporal_stop() {
	/**
	* @brief Al detener el temporal, deja de sumar tiempo.
	*/
	t_temporal *temporal = temporal_create();
	sleep(1);
	temporal_stop(temporal);
	sleep(2);

	printf("test_temporal_stop: %ldms (expected: ~1000ms)\n\n", temporal_gettime(temporal));

	temporal_destroy(temporal);
}

void test_temporal_resume() {
	/**
	* @brief Al detener y reanudar el temporal varias veces, el tiempo que este
	*        suma es correcto.
	*/
	t_temporal* temporal = temporal_create();

	temporal_stop(temporal);
	sleep(3); // +0

	printf("test_temporal_resume: %ldms (expected: ~0ms)\n", temporal_gettime(temporal));

	temporal_resume(temporal);
	sleep(2);  // +2
	temporal_stop(temporal);

	printf("test_temporal_resume: %ldms (expected: ~2000ms)\n", temporal_gettime(temporal));
	
	temporal_resume(temporal);
	sleep(2); // +2

	printf("test_temporal_resume: %ldms (expected: ~4000ms)\n", temporal_gettime(temporal));

	temporal_stop(temporal);
	sleep(2); // +0
	temporal_resume(temporal);
	sleep(1); // +1

	printf("test_temporal_resume: %ldms (expected: ~5000ms)\n\n", temporal_gettime(temporal));

	temporal_destroy(temporal);
}

void test_temporal_diff() {
	/**
	* @brief Comparar dos variables temporales.
	*/

	t_temporal* temporal1 = temporal_create();
	t_temporal* temporal2 = temporal_create();

	sleep(1);
	temporal_stop(temporal2);
	sleep(1);

	t_temporal* temporal3 = temporal_create();

	printf("test_temporal_diff: %ldms (expected: ~1000ms)\n", temporal_diff(temporal1, temporal2));
	printf("test_temporal_diff: %ldms (expected: ~2000ms)\n", temporal_diff(temporal1, temporal3));
	printf("test_temporal_diff: %ldms (expected: ~1000ms)\n", temporal_diff(temporal2, temporal3));
	printf("test_temporal_diff: %ldms (expected: ~-1000ms)\n\n", temporal_diff(temporal3, temporal2));

	temporal_destroy(temporal1);
	temporal_destroy(temporal2);
	temporal_destroy(temporal3);
}

void test_temporal_status() {
	/**
	* @brief Verificar el comportamiento del temporal en sus diferentes estados.
	*
	* @note En este test se verifica que no ocurra ningún error al usar el
	*       temporal de cualquier forma.
	*/

	t_temporal* temporal1 = temporal_create();
	temporal_destroy(temporal1);

	t_temporal* temporal2 = temporal_create();
	temporal_stop(temporal2);
	temporal_destroy(temporal2);

	t_temporal* temporal3 = temporal_create();
	temporal_resume(temporal3);
	temporal_resume(temporal3);
	temporal_stop(temporal3);
	temporal_stop(temporal3);
	sleep(1);
	temporal_resume(temporal3);
	sleep(1);

	printf("test_temporal_status: %lums (expected: ~1000ms)\n\n", temporal_gettime(temporal3));

	temporal_destroy(temporal3);
}

int main(int argc, char** argv) {
	pthread_t th1, th2, th3, th4, th5, th6;

	printf("Verificar que fecha y hora sean correctas: \n");

	pthread_create(&th1, NULL, (void*) print_time, NULL);
	pthread_create(&th2, NULL, (void*) print_time, NULL);
	pthread_create(&th3, NULL, (void*) print_time, NULL);
	pthread_create(&th4, NULL, (void*) print_time, NULL);
	pthread_create(&th5, NULL, (void*) print_time, NULL);
	pthread_create(&th6, NULL, (void*) print_time, NULL);

	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	pthread_join(th3, NULL);
	pthread_join(th4, NULL);
	pthread_join(th5, NULL);
	pthread_join(th6, NULL);

	test_temporal_gettime();
	test_temporal_stop();
	test_temporal_resume();
	test_temporal_diff();
	test_temporal_status();
	
	return (EXIT_SUCCESS);
}