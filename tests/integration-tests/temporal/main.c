/* 
 * File:   main.c
 * Author: RaniAgus
 *
 * Created on March 24, 2020, 21:11 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <commons/txt.h>
#include <commons/temporal.h>
#include <commons/string.h>
#include <pthread.h>

static void log_in_disk(char* temp_file) {
    FILE* file = txt_open_for_append(temp_file);

    char* day = temporal_get_string_time("day: %d\n");
    char* month = temporal_get_string_time("month: %m\n");
    char* year = temporal_get_string_time("year: %y\n");

    char* hour = temporal_get_string_time("hour: %H\n");
    char* min = temporal_get_string_time("min: %M\n");
    char* sec = temporal_get_string_time("sec: %S\n");
    char* milisec = temporal_get_string_time("milisec: %MS\n");

    txt_write_in_file(file, day);
    txt_write_in_file(file, month);
    txt_write_in_file(file, year);

    txt_write_in_file(file, hour);
    txt_write_in_file(file, min);
    txt_write_in_file(file, sec);
    txt_write_in_file(file, milisec);

    free(day);
    free(month);
    free(year);

    free(hour);
    free(min);
    free(sec);
    free(milisec);

    txt_close_file(file);
    free(temp_file);
}

int main(int argc, char** argv) {
    pthread_t th1, th2;
    
    char temp_file[] = "build/XXXXXX";

    close(mkstemp(temp_file));

    if (temp_file != NULL) {
        pthread_create(&th1, NULL, (void*) log_in_disk, string_duplicate(temp_file));
        pthread_create(&th2, NULL, (void*) log_in_disk, string_duplicate(temp_file));

        pthread_join(th1, NULL);
        pthread_join(th2, NULL);
        printf("\nRevisar el archivo de log que se creo en: %s\n", temp_file);
    } else {
        printf("No se pudo generar el archivo de log\n");
    }
    
    
    return (EXIT_SUCCESS);
}

