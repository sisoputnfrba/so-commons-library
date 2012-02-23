/*
 * config.h
 *
 *  Created on: Feb 18, 2012
 *      Ex-Author: shinichi
 *      New-Author: fviale
 */

#ifndef CONFIG_H_
#define CONFIG_H_

	#include "collections/dictionary.h"

	typedef struct {
		char *path;
		t_dictionary *properties;
	} t_config;

	t_config *config_create(char *path);
	char 	 *config_get_string_value(t_config*, char *key);
	int 	  config_get_int_value(t_config*, char *key);
	long	  config_get_long_value(t_config*, char *key);
	double 	  config_get_double_value(t_config*, char *key);
	void 	  config_destroy(t_config *config);

#endif /* CONFIG_H_ */
