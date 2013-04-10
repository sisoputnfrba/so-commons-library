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

#include "string.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdarg.h>

static void _string_do(char *text, void (*closure)(char*));
static void _string_lower_element(char* ch);
static void _string_upper_element(char* ch);
void _string_append_with_format_list(const char* format, char** original, va_list arguments);

/**
 * @NAME: string_repeat
 * @DESC: Crea un string de longitud 'count' con el mismo caracter.
 *
 * Ejemplo:
 * string_repeat('a', 5) = "aaaaa"
 *
 */
char *string_repeat(char character, int count) {
	char *text = calloc(count + 1, 1);
	int i = 0;
	for (i = 0; i < count; ++i) {
		text[i] = character;
	}
	return text;
}

/**
 * @NAME: string_duplicate
 * @DESC: Retorna una copia del string pasado
 * como argumento
 */
char* string_duplicate(char* original) {
	return strdup(original);
}

/**
 * @NAME: string_append
 * @DESC: Agrega al primer string el segundo
 *
 * Ejemplo:
 * char *unaPalabra = "HOLA ";
 * char *otraPalabra = "PEPE";
 *
 * string_append(&unaPalabra, otraPalabra);
 *
 * => unaPalabra = "HOLA PEPE"
 */
void string_append(char** original, char* string_to_add) {
	*original = realloc(*original, strlen(*original) + strlen(string_to_add) + 1);
	strcat(*original, string_to_add);
}

/**
 * @NAME: string_new
 * @DESC: Crea un string vacio
 */
char* string_new() {
	return string_duplicate("");
}

/**
 * @NAME: string_from_format
 * @DESC: Crea un nuevo string a partir de un formato especificado
 *
 * Ejemplo:
 * char* saludo = string_from_format("Hola %s", "mundo");
 *
 * => saludo = "Hola mundo"
 */
char* string_from_format(const char* format, ...) {
	char* nuevo;
	va_list arguments;
	va_start(arguments, format);
	nuevo = string_from_vformat(format, arguments);
	va_end(arguments);
	return nuevo;
}

/**
 * @NAME: string_from_vformat
 * @DESC: Crea un nuevo string a partir de un formato especificado
 * pasando un va_list con los argumentos
 */
char* string_from_vformat(const char* format, va_list arguments) {
	char* nuevo = string_new();
	_string_append_with_format_list(format, &nuevo, arguments);
	return nuevo;
}

/**
 * @NAME: string_append_with_format
 * @DESC: Concatena al primer string el resultado de aplicar los parametros al
 * formato especificado
 *
 * Ejemplo:
 * char *saludo = "HOLA ";
 * char *nombre = "PEPE";
 *
 * string_append_with_format(&saludo, "%s!", nombre);
 *
 * => saludo = "HOLA PEPE!"
 */
void string_append_with_format(char **original, const char *format, ...) {
	va_list arguments;
	va_start(arguments, format);
	_string_append_with_format_list(format, original, arguments);
	va_end(arguments);
}

/**
 * @NAME: string_to_upper
 * @DESC: Pone en mayuscula todos los caracteres de un string
 */
void string_to_upper(char *text) {
	_string_do(text, &_string_upper_element);
}

/**
 * @NAME: string_to_lower
 * @DESC: Pone en minuscula todos los caracteres de un string
 */
void string_to_lower(char *text) {
	_string_do(text, &_string_lower_element);
}

/**
 * @NAME: string_capitalized
 * @DESC: Capitaliza un string
 */
void string_capitalized(char *text) {
	if (!string_is_empty(text)) {
		_string_upper_element(text);
		if (strlen(text) >= 2){
			string_to_lower(&text[1]);
		}
	}
}

/**
 * @NAME: string_trim
 * @DESC: Remueve todos los caracteres
 * vacios de la derecha y la izquierda
 */
void string_trim(char** text) {
	string_trim_left(text);
	string_trim_right(text);
}

/**
 * @NAME: string_trim_left
 * @DESC: Remueve todos los caracteres
 * vacios de la izquierda
 */
void string_trim_left(char** text) {
	char *string_without_blank = *text;

	while (isblank(*string_without_blank)) {
		string_without_blank++;
	}

	char *new_string = string_duplicate(string_without_blank);

	free(*text);
	*text = new_string;
}

/**
 * @NAME: string_trim_right
 * @DESC: Remueve todos los caracteres
 * vacios de la derecha
 */
void string_trim_right(char** text) {
	char *string_without_blank = *text;
	int i = strlen(*text) - 1;
	while (i >= 0 && isspace(string_without_blank[i])){
		string_without_blank[i] = '\0';
		i--;
	}
	*text = realloc(*text, strlen(string_without_blank) + 1);
}

/**
 * @NAME: string_is_empty
 * @DESC: Retorna si un string es ""
 */
bool string_is_empty(char *text) {
	return strlen(text) == 0;
}

/**
 * @NAME: string_starts_with
 * @DESC: Retorna un boolean que indica
 * si un string comienza con el
 * string pasado por parametro
 */
bool string_starts_with(char *text, char *begin){
	return strncmp(text, begin, strlen(begin)) == 0;
}

/**
 * @NAME: string_ends_with
 * @DESC: Retorna un boolean que indica
 * si un string finaliza con el
 * string pasado por parametro
 */
bool string_ends_with(char* text, char* end) {
	if (strlen(text) < strlen(end)) {
		return false;
	}

	int index = strlen(text) - strlen(end);
	return strcmp(&text[index], end) == 0;
}

/**
 * @NAME: string_equals_ignore_case
 * @DESC: Retorna si dos strings son iguales
 * ignorando las mayusculas y minusculas
 */
bool string_equals_ignore_case(char *actual, char *expected) {
	return strcasecmp(actual, expected) == 0;
}


/**
 * @NAME: string_split
 * @DESC: Separa un string dado un separador
 */
char **string_split(char *text, char *separator) {
	char **substrings = NULL;
	int size = 0;

	char *text_to_iterate = string_duplicate(text);
	char *token = NULL, *next = NULL;
	token = strtok_r(text_to_iterate, separator, &next);

	while (token != NULL) {
		size++;
		substrings = realloc(substrings, sizeof(char*) * size);
		substrings[size - 1] = string_duplicate(token);
		token = strtok_r(NULL, separator, &next);
	}

	size++;
	substrings = realloc(substrings, sizeof(char*) * size);
	substrings[size - 1] = NULL;

	free(text_to_iterate);
	return substrings;
}

/**
 * @NAME: string_get_string_as_array
 * @DESC: Retorna una array separando los elementos 
 * de un string con formato de array
 * 
 * Ejemplo:
 * char* array_string = "[1,2,3,4]"
 * string_get_value_as_array(array_string) => ["1","2","3","4"]
 */
char**  string_get_string_as_array(char* text) {
    int length_value = strlen(text) - 2;
    char* value_without_brackets = string_substring(text, 1, length_value);
    char **array_values = string_split(value_without_brackets, ",");

    int i = 0;
    while (array_values[i] != NULL) {
	    string_trim(&(array_values[i]));
	    i++;
    }

    free(value_without_brackets);
    return array_values;
}

/**
 * @NAME: string_substring
 * @DESC: Retorna los length caracteres de text empezando en start
 * en un nuevo string
 */
char*   string_substring(char* text, int start, int length) {
	char* new_string = calloc(1, length + 1);
	strncpy(new_string, text + start, length);
	return new_string;
}

/**
 * @NAME: string_substring_from
 * @DESC: Retorna el substring de text desde el caracter start hasta
 * el ultimo
 */
char *string_substring_from(char *text, int start) {
	return string_substring(text, start, strlen(text) - start);
}

/**
 * @NAME: string_substring_until
 * @DESC: Retorna los primeros length caracteres de text como un nuevo
 * string
 */
char *string_substring_until(char *text, int length) {
	return string_substring(text, 0, length);
}

/**
 * @NAME: string_iterate_lines
 * @DESC: Itera un array de strings aplicando
 * el closure a cada string
 */
void string_iterate_lines(char** strings, void (*closure)(char*)) {
	while (*strings != NULL) {
		closure(*strings);
		strings++;
	}
}


/** PRIVATE FUNCTIONS **/

static void _string_upper_element(char* ch) {
	*ch = toupper(*ch);
}

static void _string_lower_element(char* ch) {
	*ch = tolower(*ch);
}

static void _string_do(char *text, void (*closure)(char* c)){
	int i = 0;
	while (text[i] != '\0') {
		closure(&text[i]);
		i++;
	}
}


void _string_append_with_format_list(const char* format, char** original, va_list arguments) {
	va_list copy_arguments;
	va_copy(copy_arguments, arguments);
	size_t buffer_size = vsnprintf(NULL, 0, format, copy_arguments) + 1;
	va_end(copy_arguments);

	char* temporal = malloc(buffer_size);
	va_copy(copy_arguments, arguments);
	vsnprintf(temporal, buffer_size, format, arguments);
	va_end(copy_arguments);
	string_append(original, temporal);
	free(temporal);
}
