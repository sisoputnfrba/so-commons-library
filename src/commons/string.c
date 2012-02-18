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

static void string_do(t_string text, void (*closure)(char*));
static void string_lower_element(char* ch);
static void string_upper_element(char* ch);

/**
 * @NAME: string_new
 * @DESC: Crea un string vacio ("")
 */
t_string string_new() {
	return calloc(1, 1);
}

/**
 * @NAME: string_duplicate
 * @DESC: Crea un string nuevo desde un string pasado por parametro
 */
t_string string_duplicate(char* original_string) {
	return strdup(original_string);
}

/**
 * @NAME: string_repeat
 * @DESC: Crea un string de longitud 'count' con el mismo caracter.
 *
 * Ejemplo:
 * string_repeat('a', 5) = "aaaaa"
 *
 */
t_string string_repeat(char character, int count) {
	t_string text = calloc(count + 1, 1);
	int i = 0;
	for (i = 0; i < count; ++i) {
		text[i] = character;
	}
	return text;
}

/**
 * @NAME: string_append
 * @DESC: Agrega al primer string el segundo
 *
 * Ejemplo:
 * t_string unaPalabra = "HOLA ";
 * t_string otraPalabra = "PEPE";
 *
 * string_append(&unaPalabra, otraPalabra);
 *
 * => unaPalabra = "HOLA PEPE"
 */
void string_append(t_string* original, t_string string_to_add) {
	*original = realloc(*original, strlen(*original) + strlen(string_to_add) + 1);
	strcat(*original, string_to_add);
}

/**
 * @NAME: string_to_upper
 * @DESC: Pone en mayuscula todos los caracteres de un string
 */
void string_to_upper(t_string text) {
	string_do(text, &string_upper_element);
}

/**
 * @NAME: string_to_lower
 * @DESC: Pone en minuscula todos los caracteres de un string
 */
void string_to_lower(t_string text) {
	string_do(text, &string_lower_element);
}

/**
 * @NAME: string_capitalized
 * @DESC: Capitaliza un string
 */
void string_capitalized(t_string text) {
	if (!string_is_empty(text)) {
		string_upper_element(text);
		if (string_length(text) >= 2){
			string_to_lower(&text[1]);
		}
	}
}

/**
 * @NAME: string_trim
 * @DESC: Remueve todos los caracteres
 * vacios de la derecha y la izquierda
 */
void string_trim(t_string* text) {
	string_trim_left(text);
	string_trim_right(text);
}

/**
 * @NAME: string_trim_left
 * @DESC: Remueve todos los caracteres
 * vacios de la izquierda
 */
void string_trim_left(t_string* text) {
	t_string string_without_blank = *text;

	while (isblank(*string_without_blank)) {
		string_without_blank++;
	}

	t_string new_string = string_duplicate(string_without_blank);

	string_destroy(*text);
	*text = new_string;
}

/**
 * @NAME: string_trim_right
 * @DESC: Remueve todos los caracteres
 * vacios de la derecha
 */
void string_trim_right(t_string* text) {
	t_string string_without_blank = *text;
	int i = string_length(*text) - 1;
	while (i >= 0 && isspace(string_without_blank[i])){
		string_without_blank[i] = '\0';
		i--;
	}
	*text = realloc(*text, strlen(string_without_blank) + 1);
}

/**
 * @NAME: string_length
 * @DESC: Retorna la longitud de un string
 */
int string_length(t_string text) {
	return strlen(text);
}

/**
 * @NAME: string_is_empty
 * @DESC: Retorna si un string es ""
 */
bool string_is_empty(t_string text) {
	return string_length(text) == 0;
}

/**
 * @NAME: string_equals_ignore_case
 * @DESC: Retorna si dos strings son iguales
 * ignorando las mayusculas y minusculas
 */
bool string_equals_ignore_case(t_string actual, t_string expected) {
	return strcasecmp(actual, expected) == 0;
}

/**
 * @NAME: string_destroy
 * @DESC: Libera la memoria utilizada por un string
 */
void string_destroy(t_string string) {
	free(string);
}

/**
 * @NAME: string_split
 * @DESC: Separa un string dado un separador
 */
t_string* string_split(t_string text, t_string regex) {
	t_string* substrings = NULL;
	int size = 0;

	t_string text_to_iterate = string_duplicate(text);
	t_string token = NULL, next = NULL;
	for (token = strtok_r(text_to_iterate, regex, &next) ;
		 token ;
		 token = strtok_r(NULL, regex, &next)) {

		size++;
		substrings = realloc(substrings, sizeof(t_string) * size);
		substrings[size - 1] = strdup(token);
	}

	size++;
	substrings = realloc(substrings, sizeof(t_string) * size);
	substrings[size - 1] = NULL;

	free(text_to_iterate);
	return substrings;
}

/**
 * @NAME: string_iterate_lines
 * @DESC: Itera un array de strings aplicando
 * el closure a cada string
 */
void string_iterate_lines(t_string* strings, void (*closure)(t_string)) {
	while (*strings != NULL) {
		closure(*strings);
		strings++;
	}
}


/** PRIVATE FUNCTIONS **/

static void string_upper_element(char* ch) {
	*ch = toupper(*ch);
}

static void string_lower_element(char* ch) {
	*ch = tolower(*ch);
}

static void string_do(t_string text, void (*closure)(char* c)){
	int i = 0;
	while (text[i] != '\0') {
		closure(&text[i]);
		i++;
	}
}
