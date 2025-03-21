/*
 * File:   main.c
 * Author: shinichi
 *
 * Created on April 5, 2013, 3:43 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <commons/log.h>
#include <commons/error.h>
#include <commons/string.h>
#include <pthread.h>

static void log_in_disk(char* temp_file) {
    t_log* logger = log_create(temp_file, "TEST", true, LOG_LEVEL_INFO);

    log_trace(logger, "LOG A NIVEL %s", "TRACE");
    log_debug(logger, "LOG A NIVEL %s", "DEBUG");
    log_info(logger, "LOG A NIVEL %s", "INFO");
    log_warning(logger, "LOG A NIVEL %s", "WARNING");
    log_error(logger, "LOG A NIVEL %s", "ERROR");
    error_show("ERROR DE PRUEBA");

    log_destroy(logger);
    free(temp_file);
}

int main(int argc, char** argv) {
    pthread_t th1, th2;

    char temp_file[] = "build/XXXXXX";

    close(mkstemp(temp_file));

    if (temp_file != NULL) {
        pthread_create(&th1, NULL, (void*) log_in_disk, string_from_format("%s.log", temp_file));
        pthread_create(&th2, NULL, (void*) log_in_disk, string_from_format("%s.log", temp_file));

        pthread_join(th1, NULL);
        pthread_join(th2, NULL);
        printf("\nRevisar el archivo de log que se creo en: %s.log\n", temp_file);
    } else {
        printf("No se pudo generar el archivo de log\n");
    }


    return (EXIT_SUCCESS);
}
