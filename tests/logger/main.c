/* 
 * File:   main.c
 * Author: shinichi
 *
 * Created on April 5, 2013, 3:43 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <commons/log.h>
#include <pthread.h>

static void log_in_disk() {
    t_log* logger;
    logger = log_create("$HOME/Desktop/trace.log", "TEST",true, LOG_LEVEL_INFO);
    
    log_trace(logger, "LOG A NIVEL %s", "TRACE");
    log_debug(logger, "LOG A NIVEL %s", "DEBUG");
    log_info(logger, "LOG A NIVEL %s", "INFO");
    log_warning(logger, "LOG A NIVEL %s", "WARNING");
    log_error(logger, "LOG A NIVEL %s", "ERROR");
    
    log_destroy(logger);
}

int main(int argc, char** argv) {
    pthread_t th1, th2;
    
    pthread_create(&th1, NULL, (void*) log_in_disk, NULL);
    pthread_create(&th2, NULL, (void*) log_in_disk, NULL);
    
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    
    return (EXIT_SUCCESS);
}

