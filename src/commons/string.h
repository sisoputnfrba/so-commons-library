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
	* @fn    string_new
	* @brief Crea un string vacio
	* @note Cuando se termina de usar, se debe liberar con free()
	*/
	char*   string_new();

	/**
	* @fn    string_itoa
	* @brief Crea un string a partir de un numero
	* @note Cuando se termina de usar, se debe liberar con free()
	*/
	char*   string_itoa(int number);

	/**
	* @fn    string_from_format
	* @brief Crea un nuevo string a partir de un formato especificado
	*
	* @example
	* @code
	* char* saludo = string_from_format("Hola %s", "mundo");
	*
	* => saludo = "Hola mundo"
	* @endcode
	* @note Cuando se termina de usar, se debe liberar con free()
	*/
	char*   string_from_format(const char* format, ...) __attribute__((format(printf, 1, 2)));

	/**
	* @fn    string_from_vformat
	* @brief Crea un nuevo string a partir de un formato especificado
	*        pasando un va_list con los argumentos
	* @note Cuando se termina de usar, se debe liberar con free()
	*/
	char*   string_from_vformat(const char* format, va_list arguments);

	/**
	* @fn    string_repeat
	* @brief Crea un string de longitud 'count' con el mismo caracter.
	*
	* @example
	* @code
	* string_repeat('a', 5) = "aaaaa"
	* @endcode
	* @note Cuando se termina de usar, se debe liberar con free()
	*/
	char*   string_repeat(char ch, int count);

	/**
	* @fn    string_append
	* @brief Agrega al primer string el segundo
	*
	* @example
	* @code
	* char *unaPalabra = string_new();
	* string_append(&unaPalabra, "HOLA ");
	* string_append(&unaPalabra, "PEPE");
	*
	* => unaPalabra = "HOLA PEPE"
	* @endcode
	* @note No devuelve una copia, esta modificando directamente el string original
	*/
	void    string_append(char ** original, char * string_to_add);

	/**
	* @fn    string_n_append
	* @brief Agrega al primer string un máximo de n caracteres
	*        del segundo.
	*
	* @example
	* @code
	* char *unaPalabra = string_new();
	* string_n_append(&unaPalabra, "HOLA ", 10);
	* string_n_append(&unaPalabra, "PEPE", 3);
	*
	* => unaPalabra = "HOLA PEP"
	* @endcode
	* @note No devuelve una copia, esta modificando directamente el string original
	*/
	void    string_n_append(char** original, char* string_to_add, int n);

	/**
	* @fn    string_append_with_format
	* @brief Concatena al primer string el resultado de aplicar los parametros
	*        al formato especificado
	*
	* @example
	* @code
	* char *saludo = "HOLA ";
	* char *nombre = "PEPE";
	*
	* string_append_with_format(&saludo, "%s!", nombre);
	*
	* => saludo = "HOLA PEPE!"
	* @endcode
	* @note No devuelve una copia, esta modificando directamente el string original
	*/
	void    string_append_with_format(char **original, const char *format, ...) __attribute__((format(printf, 2, 3)));

	/**
	* @fn    string_duplicate
	* @brief Retorna una copia del string pasado como argumento
	* @note Cuando se termina de usar, se debe liberar con free()
	*/
	char*   string_duplicate(char* original);

	/**
	* @fn    string_to_upper
	* @brief Pone en mayuscula todos los caracteres de un string
	* @note No devuelve una copia, esta modificando directamente el string original
	*/
	void    string_to_upper(char * text);

	/**
	* @fn    string_to_lower
	* @brief Pone en minuscula todos los caracteres de un string
	* @note No devuelve una copia, esta modificando directamente el string original
	*/
	void    string_to_lower(char * text);

	/**
	* @fn    string_capitalized
	* @brief Capitaliza un string
	* @note No devuelve una copia, esta modificando directamente el string original
	*/
	void    string_capitalized(char * text);

	/**
	* @fn    string_trim
	* @brief Remueve todos los caracteres vacios de la derecha y la izquierda
	* @note No devuelve una copia, esta modificando directamente el string original
	*/
	void    string_trim(char ** text);

	/**
	* @fn    string_trim_left
	* @brief Remueve todos los caracteres vacios de la izquierda
	* @note No devuelve una copia, esta modificando directamente el string original
	*/
	void    string_trim_left(char ** text);

	/**
	* @fn    string_trim_right
	* @brief Remueve todos los caracteres vacios de la derecha
	* @note No devuelve una copia, esta modificando directamente el string original
	*/
	void    string_trim_right(char ** text);

	/**
	* @fn    string_length
	* @brief Retorna la longitud del string
	*/
	int     string_length(char * text);

	/**
	* @fn    string_is_empty
	* @brief Retorna si un string es ""
	*/
	bool    string_is_empty(char * text);

	/**
	* @fn    string_starts_with
	* @brief Retorna un boolean que indica si un string comienza con el string
	*        pasado por parametro
	*/
	bool    string_starts_with(char * text, char * begin);

	/**
	* @fn    string_ends_with
	* @brief Retorna un boolean que indica si un string finaliza con el string
	*        pasado por parametro
	*/
	bool    string_ends_with(char* text, char* end);

	/**
	* @fn    string_equals_ignore_case
	* @brief Retorna si dos strings son iguales ignorando las mayusculas y
	*        minusculas
	*/
	bool    string_equals_ignore_case(char * actual, char * expected);

	/**
	* @fn    string_split
	* @brief Separa un string dado un separador
	*
	* @return Retorna un array con cada palabra y en la última posición un NULL
	*
	* @example
	* @code
	* string_split("hola, mundo", ",") => ["hola", " mundo", NULL]
	* @endcode
	* @note El array retornado contiene copias de los caracteres del string original, 
	*		este debe liberarse con string_array_destroy() cuando se deja de usar
	*/
	char **string_split(char * text, char * separator);


	/**
	* @fn    string_n_split
	* @brief Separa un string tantas veces por su separador como n lo permita
	* @return Retorna un array con cada palabra mientras n lo permita y en la última posición un NULL
	*
	* @example
	* @code
	* string_n_split("hola, mundo, bueno", 2, ",") => ["hola", " mundo, bueno", NULL]
	* string_n_split("hola, mundo, bueno", 3, ",") => ["hola", " mundo", " bueno", NULL]
	* string_n_split("hola, mundo, bueno", 10, ",") => ["hola", " mundo", " bueno", NULL]
	* @endcode
	* @note El array retornado contiene copias de los caracteres del string original, 
	*	    este debe liberarse con string_array_destroy() cuando se deja de usar
	*/
	char**  string_n_split(char* text, int n, char* separator);

	/**
	* @fn    string_substring
	* @brief Retorna los length caracteres de text empezando en start
	*        en un nuevo string
	*
	* @example
	* @code
	* string_substring("hola, mundo, bueno", 0, 4) => "hola"
	* string_substring("hola, mundo, bueno", 7, 5) => "mundo"
	* string_n_split("hola, mundo, bueno", 1, 3) => "ola"
	* @endcode
	* @note Cuando se termina de usar, se debe liberar con free()
	*/
	char*   string_substring(char* text, int start, int length);

	/**
	* @fn    string_substring_from
	* @brief Retorna el substring de text desde el indice start hasta
	*        el último de la palabra
	* @note Cuando se termina de usar, se debe liberar con free()
	*
	*/
	char*   string_substring_from(char *text, int start);

	/**
	* @fn    string_substring_until
	* @brief Retorna los primeros length caracteres de text como un nuevo string
	* @note Cuando se termina de usar, se debe liberar con free()
	*
	*/
	char*   string_substring_until(char *text, int length);

	/**
	* @fn    string_iterate_lines
	* @brief Itera un array de strings aplicando
	*        el closure a cada string, hasta que encuentre un NULL
	* @note No devuelve una copia, esta modificando directamente los strings del array directamente
	*/
	void    string_iterate_lines(char ** strings, void (*closure)(char *));

	/**
	* @fn    string_get_string_as_array
	* @brief Retorna una array separando los elementos
	*        de un string con formato de array
	*
	* @example
	* @code
	* char* array_string = "[1,2,3,4]"
	* string_get_value_as_array(array_string) => ["1","2","3","4",NULL]
	* @endcode
	* @note El array retornado contiene copias de los caracteres del string original, 
	*	    este debe liberarse con string_array_destroy() cuando se deja de usar
	*/
	char**  string_get_string_as_array(char* text);

	/**
	* @fn    string_reverse
	* @brief Retorna el texto invertido. No se maneja el caso de NULL,
	* si se pasa NULL su comportamiento no esta determinado.
	*
	* @example
	* @code
	* char* original = "boo";
	* string_reverse(original) => "oob"
	* @endcode
	* @note Cuando se termina de usar, se debe liberar con free()
	*/
	char*   string_reverse(char* text);

	/**
	* @fn    string_replace
	* @brief Retorna una copia de un string con todas las ocurrencias
	*        de un substring no vacío siendo reemplazadas por otro string.
	*
	* @example
	* @code
	* char* original = "hello";
	* string_replace(original, "ello", "ola") => "hola"
	* string_replace(original, "l", ""); => "heo"
	* string_replace(original, "not a substring", "yay!"); => "hello"
	* @endcode
	* @note Cuando se termina de usar, se debe liberar con free()
	*/
	char*   string_replace(char* text, char* substring, char* replacement);

	/**
	 * @fn    string_contains
	 * @brief Retorna un boolean que indica si text contiene o no
	 *        a substring.
	 */
	bool    string_contains(char* text, char *substring);

	/**
	* @fn    string_array_new
	* @brief Crea un array de strings vacio
	* @note Se libera con string_array_destroy()
	*/
	char**  string_array_new();

	/**
	* @fn    string_array_destroy
	* @brief Destruye un array con sus strings
	*/
	void    string_array_destroy(char** array);

	/**
	* @fn    string_array_size
	* @brief Retorna la cantidad de líneas del array de strings
	*/
	int     string_array_size(char** array);

	/**
	* @fn    string_array_is_empty
	* @brief Verifica si el array de strings está vacío
	*/
	bool    string_array_is_empty(char** array);

	/**
	* @fn    string_array_push
	* @brief Agrega un string al final del array
	* @note No genera una copia del string_array, solo lo modifica
	*/
	void    string_array_push(char*** array, char* text);

	/**
	* @fn    string_array_replace
	* @brief Reemplaza un string en un array por otro, retornando
	*        el anterior
	* @note No genera una copia del string_array, solo lo modifica
	*/
	char*   string_array_replace(char** array, int pos, char* text);

	/**
	* @fn    string_array_pop
	* @brief Quita el último string del array y lo retorna
	*
	* @note No genera una copia del string_array, solo lo modifica, 
	*       el elemento retornado no es una copia y debe liberarse con free() cuando se deja de usar
	*/
	char*   string_array_pop(char** array);

#endif /* STRING_UTILS_H_ */
