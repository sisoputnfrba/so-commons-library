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

/*
 * @NAME: config_create
 * @DESC: Crea y devuelve un puntero a una estructura t_config
 * @PARAMS:
 * 		path - path del archivo de configuracion
 */
t_config *config_create(char *path) {
	t_config *config = malloc(sizeof(t_config));

	config->path = strdup(path);
	config->properties = dictionary_create();

	struct stat stat_file;
	stat(path, &stat_file);
	FILE* file = NULL;

	file = fopen(path, "r");

	if (file != NULL) {
		char* buffer = calloc(1, stat_file.st_size + 1);
		fread(buffer, stat_file.st_size, 1, file);

		char** lines = string_split(buffer, "\n");

		void add_cofiguration(char *line) {
			if (!string_starts_with(line, "#")) {
				char** keyAndValue = string_split(line, "=");
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
	}

	return config;
}

/*
 * @NAME: config_has_property
 * @DESC: Retorna true si key se encuentra en la configuracion.
*/
bool config_has_property(t_config *self, char* key) {
	return dictionary_has_key(self->properties, key);
}


/*
 * @NAME: config_get_string_value
 * @DESC: Retorna un string con el valor asociado a key.
*/
char *config_get_string_value(t_config *self, char *key) {
	return dictionary_get(self->properties, key);
}

/*
 * @NAME: config_get_int_value
 * @DESC:Retorna un int con el valor asociado a key.
*/
int config_get_int_value(t_config *self, char *key) {
	char *value = config_get_string_value(self, key);
	return atoi(value);
}
/*
 * @NAME: config_get_long_value
 * @DESC:Retorna un long con el valor asociado a key.
*/
long config_get_long_value(t_config *self, char *key) {
	char *value = config_get_string_value(self, key);
	return atol(value);
}

/*
 * @NAME: config_get_double_value
 * @DESC:Retorna un double con el valor asociado a key.
*/
double config_get_double_value(t_config *self, char *key) {
	char *value = config_get_string_value(self, key);
	return atof(value);
}

/*
 * @NAME: config_get_array_value
 * @DESC: Retorna un array con los valores asociados a la key especificada.
 * En el archivo de configuracion un valor de este tipo debería ser representado
 * de la siguiente forma [lista_valores_separados_por_coma]
 * Ejemplo:
 * VALORES=[1,2,3,4,5]
*/
char** config_get_array_value(t_config* self, char* key) {
	char* value_in_dictionary = config_get_string_value(self, key);
	return string_get_string_as_array(value_in_dictionary);
}

/*
 * @NAME: config_key_amount
 * @DESC: Retorna la cantidad de keys.
*/
int config_keys_amount(t_config *self) {
	return dictionary_size(self->properties);
}

/*
 * @NAME: config_destroy
 * @DESC: Destruye la estructura config.
*/
void config_destroy(t_config *config) {
	dictionary_destroy_and_destroy_elements(config->properties, free);
	free(config->path);
	free(config);
}
