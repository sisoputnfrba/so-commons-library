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
	 * @struct string
	 * @brief Funciones para manipulación de strings
	 * @include commons/string.h
	 */

	/**
	* @brief Crea un string vacio
	* @relates string
	*/
	char*   string_new();

	/**
	* @brief Crea un string a partir de un numero
	* @relates string
	*/
	char*   string_itoa(int number);

	/**
	* @brief Crea un nuevo string a partir de un formato especificado
	* @relates string
	*
	* @code
	* char* saludo = string_from_format("Hola %s", "mundo");
	*
	* => saludo = "Hola mundo"
	* @endcode
	*/
	char*   string_from_format(const char* format, ...) __attribute__((format(printf, 1, 2)));

	/**
	* @brief Crea un nuevo string a partir de un formato especificado
	*        pasando un va_list con los argumentos
	* @relates string
	*/
	char*   string_from_vformat(const char* format, va_list arguments);

	/**
	* @brief Crea un string de longitud 'count' con el mismo caracter.
	* @relates string
	*
	* @code
	* string_repeat('a', 5) = "aaaaa"
	* @endcode
	*/
	char*   string_repeat(char ch, int count);

	/**
	* @brief Agrega al primer string el segundo
	* @relates string
	*
	* @code
	* char *unaPalabra = string_new();
	* string_append(&unaPalabra, "HOLA ");
	* string_append(&unaPalabra, "PEPE");
	*
	* => unaPalabra = "HOLA PEPE"
	* @endcode
	*/
	void    string_append(char ** original, char * string_to_add);

	/**
	* @brief Agrega al primer string un máximo de n caracteres
	*        del segundo.
	* @relates string
	*
	* @code
	* char *unaPalabra = string_new();
	* string_n_append(&unaPalabra, "HOLA ", 10);
	* string_n_append(&unaPalabra, "PEPE", 3);
	*
	* => unaPalabra = "HOLA PEP"
	* @endcode
	*/
	void    string_n_append(char** original, char* string_to_add, int n);

	/**
	* @brief Concatena al primer string el resultado de aplicar los parametros
	*        al formato especificado
	* @relates string
	*
	* @code
	* char *saludo = "HOLA ";
	* char *nombre = "PEPE";
	*
	* string_append_with_format(&saludo, "%s!", nombre);
	*
	* => saludo = "HOLA PEPE!"
	* @endcode
	*/
	void    string_append_with_format(char **original, const char *format, ...) __attribute__((format(printf, 2, 3)));

	/**
	* @brief Retorna una copia del string pasado como argumento
	* @relates string
	*/
	char*   string_duplicate(char* original);

	/**
	* @brief Pone en mayuscula todos los caracteres de un string
	* @relates string
	*/
	void    string_to_upper(char * text);

	/**
	* @brief Pone en minuscula todos los caracteres de un string
	* @relates string
	*/
	void    string_to_lower(char * text);

	/**
	* @brief Capitaliza un string
	* @relates string
	*/
	void    string_capitalized(char * text);

	/**
	* @brief Remueve todos los caracteres vacios de la derecha y la izquierda
	* @relates string
	*/
	void    string_trim(char ** text);

	/**
	* @brief Remueve todos los caracteres vacios de la izquierda
	* @relates string
	*/
	void    string_trim_left(char ** text);

	/**
	* @brief Remueve todos los caracteres vacios de la derecha
	* @relates string
	*/
	void    string_trim_right(char ** text);

	/**
	* @brief Retorna la longitud del string
	* @relates string
	*/
	int     string_length(char * text);

	/**
	* @brief Retorna si un string es ""
	* @relates string
	*/
	bool    string_is_empty(char * text);

	/**
	* @brief Retorna un boolean que indica si un string comienza con el string
	*        pasado por parametro
	* @relates string
	*/
	bool    string_starts_with(char * text, char * begin);

	/**
	* @brief Retorna un boolean que indica si un string finaliza con el string
	*        pasado por parametro
	* @relates string
	*/
	bool    string_ends_with(char* text, char* end);

	/**
	* @brief Retorna si dos strings son iguales ignorando las mayusculas y
	*        minusculas
	* @relates string
	*/
	bool    string_equals_ignore_case(char * actual, char * expected);

	/**
	* @brief Separa un string dado un separador
	* @relates string
	*
	* @return Retorna un array con cada palabra y en la última posición un NULL
	*
	*
	* @code
	* string_split("hola, mundo", ",") => ["hola", " mundo", NULL]
	* @endcode
	*/
	char**  string_split(char * text, char * separator);


	/**
	 * @brief Separa un string tantas veces por su separador como n lo permita
	 * @relates string
	 *
	 *
	 * @code
	 * string_n_split("hola, mundo, bueno", 2, ",") => ["hola", " mundo, bueno", NULL]
	 * string_n_split("hola, mundo, bueno", 3, ",") => ["hola", " mundo", " bueno", NULL]
	 * string_n_split("hola, mundo, bueno", 10, ",") => ["hola", " mundo", " bueno", NULL]
	 * @endcode
	 */
	char**  string_n_split(char* text, int n, char* separator);

	/**
	* @brief Retorna los length caracteres de text empezando en start
	*        en un nuevo string
	* @relates string
	*/
	char*   string_substring(char* text, int start, int length);

	/**
	* @brief Retorna el substring de text desde el indice start hasta
	*        el último de la palabra
	* @relates string
	*/
	char*   string_substring_from(char *text, int start);

	/**
	* @brief Retorna los primeros length caracteres de text como un nuevo string
	* @relates string
	*/
	char*   string_substring_until(char *text, int length);

	/**
	* @brief Itera un array de strings aplicando
	*        el closure a cada string, hasta que encuentre un NULL
	* @relates string
	*/
	void    string_iterate_lines(char ** strings, void (*closure)(char *));

	/**
	* @brief Retorna una array separando los elementos
	*        de un string con formato de array
	* @relates string
	*
	*
	* @code
	* char* array_string = "[1,2,3,4]"
	* string_get_value_as_array(array_string) => ["1","2","3","4",NULL]
	* @endcode
	*/
	char**  string_get_string_as_array(char* text);

	/**
	 * @brief Retorna el texto invertido. No se maneja el caso de NULL,
	 *        si se pasa NULL su comportamiento no esta determinado.
	 * @relates string
	 *
	 *
	 * @code
	 * char* original = "boo";
	 * string_reverse(original) => "oob"
	 * @endcode
	 */
	char*   string_reverse(char* text);

	/**
	* @brief Retorna una copia de un string con todas las ocurrencias
	*        de un substring no vacío siendo reemplazadas por otro string.
	* @relates string
	*
	* @code
	* char* original = "hello";
	* string_replace(original, "ello", "ola") => "hola"
	* string_replace(original, "l", ""); => "heo"
	* string_replace(original, "not a substring", "yay!"); => "hello"
	* @endcode
	*/
	char*   string_replace(char* text, char* substring, char* replacement);

	/**
	 * @brief Retorna un boolean que indica si text contiene o no
	 *        a substring.
	 * @relates string
	 */
	bool    string_contains(char* text, char *substring);

	/**
	* @brief Crea un array de strings vacio
	* @relates string
	*/
	char**  string_array_new();

	/**
	* @brief Destruye un array con sus strings
	* @relates string
	*/
	void    string_array_destroy(char** array);

	/**
	* @brief Retorna la cantidad de líneas del array de strings
	* @relates string
	*/
	int     string_array_size(char** array);

	/**
	* @brief Verifica si el array de strings está vacío
	* @relates string
	*/
	bool    string_array_is_empty(char** array);

	/**
	* @brief Agrega un string al final del array
	* @relates string
	*/
	void    string_array_push(char*** array, char* text);

	/**
	* @brief Reemplaza un string en un array por otro, retornando
	* @relates string
	*        el anterior
	*/
	char*   string_array_replace(char** array, int pos, char* text);

	/**
	* @brief Quita el último string del array y lo retorna
	* @relates string
	*/
	char*   string_array_pop(char** array);

#endif /* STRING_UTILS_H_ */
