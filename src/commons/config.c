/*
 * config.c
 *
 *  Created on: Feb 18, 2012
 *      Author: shinichi
 */


#include "config.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <sys/stat.h>

t_dictionary* config_read_from_file(t_string path) {
	t_dictionary* config = dictionary_create(free);

	struct stat stat_file;
	stat(path, &stat_file);
	FILE* file = fopen(path, "r");

	char* buffer = calloc(1, stat_file.st_size + 1);
	fread(buffer, stat_file.st_size, 1, file);
	t_string* lines = string_split(buffer, "\n");

	void add_cofiguration(t_string line) {
		t_string* keyAndValue = string_split(line, "=");
		dictionary_put(config, keyAndValue[0], keyAndValue[1]);
		free(keyAndValue);
	}
	string_iterate_lines(lines, add_cofiguration);

	string_iterate_lines(lines, (void*)(char*)free);
	free(lines);
	free(buffer);
	fclose(file);

	return config;
}

void config_write_in_file(t_string path, t_dictionary* dictionary) {
	FILE* file = fopen(path, "w");
	void writeProperty(void* hash_element) {
		t_hash_element *element = hash_element;
		fprintf(file, "%s=%s\n", element->key, element->data);
	}

	dictionary_iterator(dictionary, writeProperty);

	fclose(file);
}
