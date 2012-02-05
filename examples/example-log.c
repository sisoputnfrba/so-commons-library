/*
 * log.c
 *
 *  Created on: Feb 3, 2012
 *      Author: Prieto, Gaston
 */

#include <log.h>

int main(int argc, char **argv) {
	t_logger logger = log_create("log.txt", "EXAMPLE", true, INFO);

	log_trace(logger, "Mensaje de tipo %s", "TRACE");
	log_debug(logger, "Mensaje de tipo %s", "DEBUG");
	log_info(logger, "Mensaje de tipo %s", "INFO");
	log_warning(logger, "Mensaje de tipo %s", "WARNING");
	log_error(logger, "Mensaje de tipo %s", "ERROR");

	log_destroy(logger);

	return 0;
}
