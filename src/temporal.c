/*
 * temporal.c
 *
 *  Created on: Feb 3, 2012
 *      Author: Prieto, Gaston
 */

#include "temporal.h"
#include "error_operations.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h>
#include <string.h>

t_string temporal_get_string_time() {
	time_t log_time;
	struct tm *log_tm;
	struct timeb tmili;
	t_string str_time = string_duplicate("hh:mm:ss:mmmm");

	if ((log_time = time(NULL)) == -1) {
		error_show("Error getting date!");
		return 0;
	}

	log_tm = localtime(&log_time);

	if (ftime(&tmili)) {
		error_show("Error getting time!");
		return 0;
	}

	t_string partial_time = string_duplicate("hh:mm:ss");
	strftime(partial_time, 127, "%H:%M:%S", log_tm);
	sprintf(str_time, "%s:%hu", partial_time, tmili.millitm);
	string_destroy(partial_time);

	return str_time;
}
