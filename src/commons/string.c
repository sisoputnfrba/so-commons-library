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

static void string_do(t_string *text, void (*closure)(char*));
static void string_lower_element(char* ch);
static void string_upper_element(char* ch);

/**
 * @NAME: string_new
 * @DESC: Crea un string a partir de una cadena
 */
t_string *string_new(char *original_text) {
	t_string *string = malloc( sizeof(t_string) );

	if( original_text == NULL ){
		string->str = calloc(1, 1);
		string->len = 0;
	} else {
		string->str = strdup(original_text);
		string->len = strlen(original_text);
	}

	return string;
}

/**
 * @NAME: string_duplicate
 * @DESC: Crea una copia del string
 */
t_string *string_duplicate(t_string *self){
	return string_new(self->str);
}

/**
 * @NAME: string_append
 * @DESC: Agrega al primer string el segundo
 *
 * Ejemplo:
 * t_string *unaPalabra = string_new("HOLA ");
 * t_string *otraPalabra = string_new("PEPE");
 *
 * string_append(unaPalabra, otraPalabra);
 *
 * => unaPalabra = "HOLA PEPE"
 */
void string_append(t_string* self, t_string *string_to_add) {
	self->str = realloc(self->str, self->len + string_to_add->len + 1);
	strcat(self->str, string_to_add->str);
	self->len += string_to_add->len;
}

/**
 * @NAME: string_append_literal
 * @DESC: Agrega al primer string el segundo
 *
 * Ejemplo:
 * t_string *unaPalabra = string_new("HOLA ");
 * char *otraPalabra = "PEPE";
 *
 * string_append_literal(unaPalabra, otraPalabra);
 *
 * => unaPalabra = "HOLA PEPE"
 */
void string_append_literal(t_string* self, char *string_to_add) {
	int string_to_add_len = strlen(string_to_add);
	self->str = realloc(self->str, self->len + string_to_add_len + 1);
	strcat(self->str, string_to_add);
	self->len += string_to_add_len;
}



/**
 * @NAME: string_to_upper
 * @DESC: Pone en mayuscula todos los caracteres de un string
 */
void string_to_upper(t_string *text) {
	string_do(text, &string_upper_element);
}

/**
 * @NAME: string_to_lower
 * @DESC: Pone en minuscula todos los caracteres de un string
 */
void string_to_lower(t_string *text) {
	string_do(text, &string_lower_element);
}

/**
 * @NAME: string_capitalized
 * @DESC: Capitaliza un string
 */
void string_capitalized(t_string *self) {
	if (!string_is_empty(self)) {
		if (string_length(self) >= 2){
			string_to_lower(self);
		}
		string_upper_element(&self->str[0]);
	}
}

/**
 * @NAME: string_trim
 * @DESC: Remueve todos los caracteres
 * vacios de la derecha y la izquierda
 */
void string_trim(t_string *self) {
	string_trim_left(self);
	string_trim_right(self);
}

/**
 * @NAME: string_trim_left
 * @DESC: Remueve todos los caracteres
 * vacios de la izquierda
 */
void string_trim_left(t_string *self) {
	char *string_without_blank = self->str;

	while (isblank(*string_without_blank)) {
		string_without_blank++;
	}

	char *new_string = strdup(string_without_blank);

	free(self->str);
	self->str = new_string;
	self->len = strlen(new_string);
}

/**
 * @NAME: string_trim_right
 * @DESC: Remueve todos los caracteres
 * vacios de la derecha
 */
void string_trim_right(t_string* self) {
	char *string_without_blank = self->str;
	int i = self->len - 1;
	while (i >= 0 && isspace(string_without_blank[i])){
		string_without_blank[i] = '\0';
		i--;
	}
	self->str = realloc(self->str, strlen(string_without_blank) + 1);
	self->len = strlen(self->str);
}

/**
 * @NAME: string_length
 * @DESC: Retorna la longitud de un string
 */
int string_length(t_string *self) {
	return self->len;
}

/**
 * @NAME: string_is_empty
 * @DESC: Retorna si un string es ""
 */
bool string_is_empty(t_string *self) {
	return string_length(self) == 0;
}

/**
 * @NAME: string_starts_with
 * @DESC: Retorna si un string comienza con el
 * string pasado por parametro
 */
bool string_starts_with(t_string *self, t_string *begin){
	return strncmp(self->str, begin->str, string_length(begin)) == 0;
}

/**
 * @NAME: string_starts_with_literal
 * @DESC: Retorna si un string comienza con la cadena pasado por parametro
 */
bool string_starts_with_literal(t_string *self, char *begin){
	return strncmp(self->str, begin, strlen(begin)) == 0;
}

/**
 * @NAME: string_equals_ignore_case
 * @DESC: Retorna si dos strings son iguales
 * ignorando las mayusculas y minusculas
 */
bool string_equals_ignore_case(t_string *self, t_string *expected) {
	return strcasecmp(self->str, expected->str) == 0;
}

/**
 * @NAME: string_equals_ignore_case
 * @DESC: Retorna si un string es igual a una cadena ignorando las mayusculas y minusculas
 */
bool string_equals_literal_ignore_case(t_string *self, char *expected){
	return strcasecmp(self->str, expected) == 0;
}

/**
 * @NAME: string_destroy
 * @DESC: Libera la memoria utilizada por un string
 */
void string_destroy(t_string *self) {
	free(self->str);
	free(self);
}

/**
 * @NAME: string_split
 * @DESC: Separa un string dado un separador
 */
t_string** string_split(t_string *self, t_string *regex) {
	t_string **substrings = NULL;
	int size = 0;

	char *text_to_iterate = strdup(self->str);
	char *token = NULL, *next = NULL;
	for (token = strtok_r(text_to_iterate, regex->str, &next) ; token ; token = strtok_r(NULL, regex->str, &next)) {
		size++;
		substrings = realloc(substrings, sizeof(t_string*) * size);
		substrings[size - 1] = string_new(token);
	}

	size++;
	substrings = realloc(substrings, sizeof(t_string*) * size);
	substrings[size - 1] = NULL;

	free(text_to_iterate);
	return substrings;
}

/**
 * @NAME: string_iterate_lines
 * @DESC: Itera un array de strings aplicando
 * el closure a cada string
 */
void string_iterate_lines(t_string** strings, void (*closure)(t_string*)) {
	while (*strings != NULL) {
		closure(*strings);
		strings++;
	}
}


/** PRIVATE FUNCTIONS **/

static void string_upper_element(char* ch) {
	*ch = toupper(ch[0]);
}

static void string_lower_element(char* ch) {
	*ch = tolower(ch[0]);
}

static void string_do(t_string *self, void (*closure)(char* c)){
	int i = 0;
	while (self->str[i] != '\0') {
		closure(&self->str[i]);
		i++;
	}
}
