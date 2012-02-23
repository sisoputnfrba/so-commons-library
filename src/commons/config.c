/*
 * config.c
 *
 *  Created on: Feb 18, 2012
 *      Ex-Author: shinichi
 *      New-Author: fviale
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include "config.h"
#include "string.h"
#include "collections/dictionary.h"

t_config *config_create(char *path) {
	t_config *config = malloc(sizeof(t_config));

	config->path = strdup(path);
	config->properties = dictionary_create(free);

	struct stat stat_file;
	stat(path, &stat_file);
	FILE* file = fopen(path, "r");

	char* buffer = calloc(1, stat_file.st_size + 1);
	fread(buffer, stat_file.st_size, 1, file);

	t_string* lines = string_split(buffer, "\n");

	void add_cofiguration(t_string line) {
		t_string* keyAndValue = string_split(line, "=");
		dictionary_put(config->properties, keyAndValue[0], keyAndValue[1]);
		free(keyAndValue);
	}
	string_iterate_lines(lines, add_cofiguration);
	string_iterate_lines(lines, (void*) free);

	free(lines);
	free(buffer);
	fclose(file);

	return config;
}

char *config_get_string_value(t_config *self, char *key) {
	return dictionary_get(self->properties, key);
}

int config_get_int_value(t_config *self, char *key) {
	char *value = config_get_string_value(self, key);
	if (value != NULL) {
		return atoi(value);
	}
	return 0;
}

long config_get_long_value(t_config *self, char *key) {
	char *value = config_get_string_value(self, key);
	if (value != NULL) {
		return atol(value);
	}
	return 0;
}

double config_get_double_value(t_config *self, char *key) {
	char *value = config_get_string_value(self, key);
	if (value != NULL) {
		return atof(value);
	}
	return 0;
}

void config_destroy(t_config *config) {
	free(config->path);
	dictionary_destroy(config->properties);
	free(config);
}
