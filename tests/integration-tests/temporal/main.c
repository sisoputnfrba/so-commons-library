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
#include <commons/string.h>
#include <pthread.h>

static void print_time() {
    char* date = temporal_get_string_time("day/month/year -- %d/%m/%y\n");
    char* time = temporal_get_string_time("hour:min:sec:milisec -- %H:%M:%S:%MS\n");

    txt_write_in_stdout(date);
    txt_write_in_stdout(time);

    free(date);
    free(time);
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
    
    return (EXIT_SUCCESS);
}

