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

#ifndef STRING_UTILS_H_
#define STRING_UTILS_H_

	#include <stdbool.h>
	#include <stdarg.h>

	/**
	* @NAME: string_new
	* @DESC: Crea un string vacio
	*/
	char*   string_new();

	/**
	* @NAME: string_itoa
	* @DESC: Crea un string a partir de un numero
	*/
	char*   string_itoa(int number);

	/**
	* @NAME: string_from_format
	* @DESC: Crea un nuevo string a partir de un formato especificado
	*
	* Ejemplo:
	* char* saludo = string_from_format("Hola %s", "mundo");
	*
	* => saludo = "Hola mundo"
	*/
	char*   string_from_format(const char* format, ...);

	/**
	* @NAME: string_from_vformat
	* @DESC: Crea un nuevo string a partir de un formato especificado
	* pasando un va_list con los argumentos
	*/
	char*   string_from_vformat(const char* format, va_list arguments);

	/**
	* @NAME: string_repeat
	* @DESC: Crea un string de longitud 'count' con el mismo caracter.
	*
	* Ejemplo:
	* string_repeat('a', 5) = "aaaaa"
	*
	*/
	char*   string_repeat(char ch, int count);

	/**
	* @NAME: string_append
	* @DESC: Agrega al primer string el segundo
	*
	* Ejemplo:
	* char *unaPalabra = string_new();
	* string_append(&unaPalabra, "HOLA ");
	* string_append(&unaPalabra, "PEPE");
	*
	* => unaPalabra = "HOLA PEPE"
	*/
	void    string_append(char ** original, char * string_to_add);

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
	void    string_append_with_format(char **original, const char *format, ...);

	/**
	* @NAME: string_duplicate
	* @DESC: Retorna una copia del string pasado
	* como argumento
	*/
	char*   string_duplicate(char* original);

	/**
	* @NAME: string_to_upper
	* @DESC: Pone en mayuscula todos los caracteres de un string
	*/
	void    string_to_upper(char * text);

	/**
	* @NAME: string_to_lower
	* @DESC: Pone en minuscula todos los caracteres de un string
	*/
	void    string_to_lower(char * text);

	/**
	* @NAME: string_capitalized
	* @DESC: Capitaliza un string
	*/
	void    string_capitalized(char * text);

	/**
	* @NAME: string_trim
	* @DESC: Remueve todos los caracteres
	* vacios de la derecha y la izquierda
	*/
	void    string_trim(char ** text);

	/**
	* @NAME: string_trim_left
	* @DESC: Remueve todos los caracteres
	* vacios de la izquierda
	*/
	void    string_trim_left(char ** text);

	/**
	* @NAME: string_trim_right
	* @DESC: Remueve todos los caracteres
	* vacios de la derecha
	*/
	void    string_trim_right(char ** text);

	/**
	* @NAME: string_length
	* @DESC: Retorna la longitud del string
	*/
	int     string_length(char * text);

	/**
	* @NAME: string_is_empty
	* @DESC: Retorna si un string es ""
	*/
	bool    string_is_empty(char * text);

	/**
	* @NAME: string_starts_with
	* @DESC: Retorna un boolean que indica
	* si un string comienza con el
	* string pasado por parametro
	*/
	bool    string_starts_with(char * text, char * begin);

	/**
	* @NAME: string_ends_with
	* @DESC: Retorna un boolean que indica
	* si un string finaliza con el
	* string pasado por parametro
	*/
	bool    string_ends_with(char* text, char* end);

	/**
	* @NAME: string_equals_ignore_case
	* @DESC: Retorna si dos strings son iguales
	* ignorando las mayusculas y minusculas
	*/
	bool    string_equals_ignore_case(char * actual, char * expected);

	/**
	* @NAME: string_split
	* @DESC: Separa un string dado un separador
	*
	* @Return: Retorna un array con cada palabra y en la última posición un NULL
	*
	* Ejemplo:
	* string_split("hola, mundo", ",") => ["hola", " mundo", NULL]
	*/
	char**  string_split(char * text, char * separator);


	/**
	 * @NAME: string_n_split
	 * @DESC: Separa un string tantas veces por su separador como n lo permita
	 *
	 * Ejemplo:
	 * string_n_split("hola, mundo, bueno", 2, ",") => ["hola", " mundo, bueno", NULL]
	 * string_n_split("hola, mundo, bueno", 3, ",") => ["hola", " mundo", " bueno", NULL]
	 * string_n_split("hola, mundo, bueno", 10, ",") => ["hola", " mundo", " bueno", NULL]
	 *
	 */
	char**  string_n_split(char* text, int n, char* separator);

	/**
	* @NAME: string_substring
	* @DESC: Retorna los length caracteres de text empezando en start
	* en un nuevo string
	*/
	char*   string_substring(char* text, int start, int length);

	/**
	* @NAME: string_substring_from
	* @DESC: Retorna el substring de text desde el indice start hasta
	* el último de la palabra
	*/
	char*   string_substring_from(char *text, int start);

	/**
	* @NAME: string_substring_until
	* @DESC: Retorna los primeros length caracteres de text como un nuevo string
	*/
	char*   string_substring_until(char *text, int length);

	/**
	* @NAME: string_iterate_lines
	* @DESC: Itera un array de strings aplicando
	* el closure a cada string, hasta que encuentre un NULL
	*/
	void    string_iterate_lines(char ** strings, void (*closure)(char *));

	/**
	* @NAME: string_get_string_as_array
	* @DESC: Retorna una array separando los elementos
	* de un string con formato de array
	*
	* Ejemplo:
	* char* array_string = "[1,2,3,4]"
	* string_get_value_as_array(array_string) => ["1","2","3","4"]
	*/
	char**  string_get_string_as_array(char* text);

	/**
	 * @NAME: string_reverse
	 * @DESC: Retorna el texto invertido. No se maneja el caso de NULL,
	 * si se pasa NULL su comportamiento no esta determinado.
	 *
	 * Ejemplo:
	 * char* original = "boo";
	 * string_reverse(original) => "oob"
	 */
	char*   string_reverse(char* text);

	/**
	 * @NAME: string_contains
	 * @DESC: Retorna un boolean que indica si text contiene o no
	 * a substring.
	 */
	bool    string_contains(char* text, char *substring);

#endif /* STRING_UTILS_H_ */
