/*
 * Copyright (C) 2012 Sistemas Operativos - UTN FRBA. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include "config.h"
#include "string.h"
#include "collections/dictionary.h"

t_config *config_create(char *path) {
	FILE* file = fopen(path, "r");

	if (file == NULL) {
		return NULL;
	}

	struct stat stat_file;
	stat(path, &stat_file);

	t_config *config = malloc(sizeof(t_config));

	config->path = strdup(path);
	config->properties = dictionary_create();

	char* buffer = calloc(1, stat_file.st_size + 1);
	fread(buffer, stat_file.st_size, 1, file);

	if (strstr(buffer, "\r\n")) {
		printf("\n\nconfig_create - WARNING: the file %s contains a \\r\\n sequence "
		 "- the Windows new line sequence. The \\r characters will remain as part "
		 "of the value, as Unix newlines consist of a single \\n. You can install "
		 "and use `dos2unix` program to convert your files to Unix style.\n\n", path);
	}

	char** lines = string_split(buffer, "\n");

	void add_cofiguration(char *line) {
		if (!string_is_empty(line) && !string_starts_with(line, "#")) {
			char** keyAndValue = string_n_split(line, 2, "=");
			dictionary_put(config->properties, keyAndValue[0], keyAndValue[1]);
			free(keyAndValue[0]);
			free(keyAndValue);
		}
	}
	string_iterate_lines(lines, add_cofiguration);
	string_iterate_lines(lines, (void*) free);

	free(lines);
	free(buffer);
	fclose(file);

	return config;
}

bool config_has_property(t_config *self, char* key) {
	return dictionary_has_key(self->properties, key);
}

char *config_get_string_value(t_config *self, char *key) {
	return dictionary_get(self->properties, key);
}

int config_get_int_value(t_config *self, char *key) {
	char *value = config_get_string_value(self, key);
	return atoi(value);
}

long config_get_long_value(t_config *self, char *key) {
	char *value = config_get_string_value(self, key);
	return atol(value);
}

double config_get_double_value(t_config *self, char *key) {
	char *value = config_get_string_value(self, key);
	return atof(value);
}

char** config_get_array_value(t_config* self, char* key) {
	char* value_in_dictionary = config_get_string_value(self, key);
	return string_get_string_as_array(value_in_dictionary);
}

int config_keys_amount(t_config *self) {
	return dictionary_size(self->properties);
}

void config_destroy(t_config *config) {
	dictionary_destroy_and_destroy_elements(config->properties, free);
	free(config->path);
	free(config);
}

void config_set_value(t_config *self, char *key, char *value) {
	config_remove_key(self, key);

	char* duplicate_value = string_duplicate(value);

	dictionary_put(self->properties, key, (void*)duplicate_value);
}

void config_remove_key(t_config *self, char *key) {
	t_dictionary* dictionary = self->properties;

	if(dictionary_has_key(dictionary, key)) {
		dictionary_remove_and_destroy(dictionary, key, free);
	}
}

int config_save(t_config *self) {
	return config_save_in_file(self, self->path);
}

int config_save_in_file(t_config *self, char* path) {
	FILE* file = fopen(path, "wb+");

	if (file == NULL) {
			return -1;
	}

	char* lines = string_new();
	void add_line(char* key, void* value) {
		string_append_with_format(&lines, "%s=%s\n", key, value);
	}

	dictionary_iterator(self->properties, add_line);
	int result = fwrite(lines, strlen(lines), 1, file);
	fclose(file);
	free(lines);
	return result;
}
