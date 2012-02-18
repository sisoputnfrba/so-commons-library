/*
 * config.h
 *
 *  Created on: Feb 18, 2012
 *      Author: shinichi
 */

#ifndef CONFIG_H_
#define CONFIG_H_

	#include "collections/dictionary.h"
	#include "string.h"

	#ifndef CONFIG_MAX_LINE
		#define CONFIG_MAX_LINE 1024
	#endif

	t_dictionary* 	config_read_from_file(t_string path);
	void 			config_write_in_file(t_string path, t_dictionary* dictionary);

#endif /* CONFIG_H_ */
