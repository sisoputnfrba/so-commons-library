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
	 * @file
	 * @brief `#include <commons/string.h>`
	 */

	/**
	 * @brief Crea un string vacio
	 * @return El string retornado debe ser liberado con `free()`
	 */
	char*   string_new(void);

	/**
	 * @brief Crea un string en formato decimal a partir de un número
	 * @param[in] number: Número entero a convertir
	 * @return El string retornado debe ser liberado con `free()`
	 *
	 * @code
	 * char* numero = string_itoa(123);
	 *
	 * => numero = "123"
	 * @endcode
	 */
	char*   string_itoa(int number);

	/**
	 * @brief Crea un nuevo string a partir de un formato especificado
	 * @param[in] format: Formato a aplicar, igual que en `printf()`
	 * @return El string retornado debe ser liberado con `free()`
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
	 *        pasando un `va_list` con los argumentos
	 * @param[in] format: Formato a aplicar, igual que en `vprintf()`
	 * @param[in] arguments: Lista de argumentos a aplicar, igual que en `vprintf()`
	 * @return Retorna un string que debe ser liberado con `free()`
	 */
	char*   string_from_vformat(const char* format, va_list arguments);

	/**
	 * @brief Crea un string de longitud `count` con el mismo caracter.
	 * @param[in] ch: Caracter a repetir
	 * @param[in] count: Cantidad de veces a repetir el caracter
	 * @return El string retornado debe ser liberado con `free()`
	 *
	 * @code
	 * string_repeat('a', 5) = "aaaaa"
	 * @endcode
	 */
	char*   string_repeat(char ch, int count);

	/**
	 * @brief Agrega al primer string el segundo
	 * @param[in,out] original: Puntero al string al que se le va a concatenar el
	 *                          segundo. Debe apuntar a un puntero liberable con `free()`
	 * @param[in] string_to_add: String a concatenar. Admite todo tipo de strings
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
	 * @brief Agrega al primer string un máximo de n caracteres del segundo.
	 * @param[in,out] original: Puntero al string a modificar. Debe apuntar a un
	 *                          string liberable con `free()`
	 * @param[in] string_to_add: String a concatenar. Admite todo tipo de strings
	 * @param[in] n: Cantidad máxima de caracteres a concatenar
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
	 * @param[in,out] original: Puntero al string a modificar. Debe apuntar a un
	 *                          string liberable con `free()`
	 * @param[in] format: Formato a aplicar, igual que en `printf()`
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
	* @param[in] original: String a duplicar. Admite todo tipo de strings
	* @return El string retornado debe ser liberado con `free()`
	*
	* @code
	* char* copia = string_duplicate("hola");
	* @endcode
	*/
	char*   string_duplicate(char* original);

	/**
	* @brief Pone en mayuscula todos los caracteres de un string
	* @param[in,out] text: String a modificar. Debe apuntar a cualquier porción de
	*                      memoria modificable (en el stack o en el heap)
	*
	* @code
	* char* heap_string = string_duplicate("hola");
	* string_to_upper(heap_string); => "HOLA"
	*
	* char[] stack_string = "hola";
	* string_to_upper(stack_string); => "HOLA"
	*
	* char* literal_string = "hola";
	* string_to_upper(literal_string); => Error!
	* @endcode
	*/
	void    string_to_upper(char * text);

	/**
	* @brief Pone en minuscula todos los caracteres de un string
	* @param[in,out] text: String a modificar. Debe apuntar a cualquier porción de
	*                      memoria modificable (en el stack o en el heap)
	*
	* @code
	* char* heap_string = string_duplicate("HOLA");
	* string_to_lower(heap_string); => "hola"
	*
	* char[] stack_string = "HOLA";
	* string_to_lower(stack_string); => "hola"
	*
	* char* literal_string = "HOLA";
	* string_to_lower(literal_string); => Error!
	* @endcode
	*/
	void    string_to_lower(char * text);

	/**
	* @brief Capitaliza un string
	* @param[in,out] text: String a modificar. Debe apuntar a cualquier porción de
	*                      memoria modificable (en el stack o en el heap)
	*
	* @code
	* char* heap_string = string_duplicate("hola");
	* string_capitalized(heap_string); => "Hola"
	*
	* char[] stack_string = "hola";
	* string_capitalized(stack_string); => "Hola"
	*
	* char* literal_string = "hola";
	* string_capitalized(literal_string); => Error!
	* @endcode
	*/
	void    string_capitalized(char * text);

	/**
	* @brief Remueve todos los caracteres vacios de la derecha y la izquierda
	* @param[in,out] text: Puntero al string a modificar. Debe apuntar a un string
	*                      liberable con `free()`
	*
	* @code
	* char* heap_string = string_duplicate("  hola  ");
	* string_trim(&heap_string); => "hola"
	*
	* char[] stack_string = "  mundo  ";
	* string_trim(&stack_string); => Error!
	* @endcode
	*/
	void    string_trim(char ** text);

	/**
	* @brief Remueve todos los caracteres vacios de la izquierda
	* @param[in,out] text: Puntero al string a modificar. Debe apuntar a un string
	*                      liberable con `free()`
	*
	* @code
	* char* heap_string = string_duplicate("  hola");
	* string_trim_left(&heap_string); => "hola"
	*
	* char[] stack_string = "  mundo";
	* string_trim_left(&stack_string); => Error!
	* @endcode
	*/
	void    string_trim_left(char ** text);

	/**
	* @brief Remueve todos los caracteres vacios de la derecha
	* @param[in,out] text: Puntero al string a modificar. Debe apuntar a un string
	*                      liberable con `free()`
	*
	* @code
	* char* heap_string = string_duplicate("hola  ");
	* string_trim_right(&heap_string); => "hola"
	*
	* char[] stack_string = "mundo  ";
	* string_trim_right(&stack_string); => Error!
	* @endcode
	*/
	void    string_trim_right(char ** text);

	/**
	* @brief Retorna la longitud del string
	* @param[in] text: String a medir. Admite todo tipo de strings
	*
	* @code
	* string_length("hola") => 4
	* @endcode
	*/
	int     string_length(char * text);

	/**
	* @brief Retorna si un string es ""
	* @param[in] text: String a evaluar. Admite todo tipo de strings
	*
	* @code
	* string_is_empty("hola") => false
	* string_is_empty("") => true
	* @endcode
	*/
	bool    string_is_empty(char * text);

	/**
	* @brief Retorna un boolean que indica si el string `text` comienza con el
	*        string `begin` pasado por parametro
	* @param[in] text: String a evaluar. Admite todo tipo de strings
	* @param[in] begin: String a buscar. Admite todo tipo de strings
	*
	* @code
	* string_starts_with("hola mundo", "hola") => true
	* string_starts_with("hola", "hola mundo") => false
	* @endcode
	*/
	bool    string_starts_with(char * text, char * begin);

	/**
	* @brief Retorna un boolean que indica si el string `text` finaliza con el
	*        string `end` pasado por parametro
	* @param[in] text: String a evaluar. Admite todo tipo de strings
	* @param[in] end: String a buscar. Admite todo tipo de strings
	*
	* @code
	* string_ends_with("hola mundo", "mundo") => true
	* string_ends_with("mundo", "hola mundo") => false
	* @endcode
	*/
	bool    string_ends_with(char* text, char* end);

	/**
	* @brief Retorna si dos strings son iguales ignorando las mayusculas y
	*        minusculas
	* @param[in] actual: String a comparar. Admite todo tipo de strings
	* @param[in] expected: String a comparar. Admite todo tipo de strings
	*
	* @code
	* string_equals_ignore_case("hola", "hola") => true
	* string_equals_ignore_case("hola", "HOLA") => true
	* string_equals_ignore_case("hola", "mundo") => false
	* @endcode
	*/
	bool    string_equals_ignore_case(char * actual, char * expected);

	/**
	* @brief Separa un string dado un separador
	* @param[in] text: String a separar. Admite todo tipo de strings
	* @param[in] separator: Separador a utilizar. Admite todo tipo de strings
	* @return Retorna un array con cada palabra y en la última posición un NULL.
	*         Debe ser liberado con `string_array_destroy()`
	*
	* @code
	* string_split("hola, mundo", ",") => {"hola", " mundo", NULL}
	* @endcode
	*/
	char**  string_split(char * text, char * separator);

	/**
	 * @brief Separa un string tantas veces por su separador como n lo permita
	 * @param[in] text: String a separar. Admite todo tipo de strings
	 * @param[in] n: Cantidad máxima de veces que se puede separar
	 * @param[in] separator: String separador a utilizar. Admite todo tipo de strings
	 * @return Retorna un array de copias de los caracteres en text y en la última
	 *         posición un NULL. Debe ser liberado con `string_array_destroy()`
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
	 * @param[in] text: String a partir del cual se obtiene el substring. Admite todo
	 *                  tipo de strings
	 * @param[in] start: Indice desde el cual se obtiene el substring
	 * @param[in] length: Cantidad de caracteres a obtener
	 * @return Retorna un nuevo string que debe ser liberado con `free()`
	 *
	 * @code
	 * string_substring("hola, mundo, bueno", 0, 4) => "hola"
	 * string_substring("hola, mundo, bueno", 7, 5) => "mundo"
	 * string_n_split("hola, mundo, bueno", 1, 3) => "ola"
	 * @endcode
	 */
	char*   string_substring(char* text, int start, int length);

	/**
	 * @brief Retorna el substring de text desde el indice start hasta
	 *        el último de la palabra
	 * @param[in] text: String a partir del cual se obtiene el substring. Admite todo
	 *                  tipo de strings
	 * @param[in] start: Indice desde el cual se obtiene el substring
	 * @return Retorna un nuevo string que debe ser liberado con `free()`
	 */
	char*   string_substring_from(char *text, int start);

	/**
	 * @brief Retorna los primeros length caracteres de text como un nuevo string
	 * @param[in] text: String a partir del cual se obtiene el substring. Admite todo
	 *                  tipo de strings
	 * @param[in] length: Cantidad de caracteres a obtener
	 * @return Retorna un nuevo string que debe ser liberado con `free()`
	 */
	char*   string_substring_until(char *text, int length);

	/**
	 * @brief Itera un array de strings y aplica la función closure a cada uno
	 * @param[in] strings: Array de strings a iterar
	 * @param[in] closure: Función a aplicar a cada string
	 */
	void    string_iterate_lines(char ** strings, void (*closure)(char *));

	/**
	 * @brief Retorna un array de strings a partir de un string formateado como array
	 * @param[in] text: String a convertir. Admite todo tipo de strings
	 * @return Retorna un array de copias de los caracteres en text y en la última
	 *         posición un NULL. Debe ser liberado con `string_array_destroy()`
	 *
	 * @code
	 * char* array_string = "[1,2,3,4]"
	 * string_get_value_as_array(array_string) => {"1", "2", "3", "4", NULL}
	 * @endcode
	 */
	char**  string_get_string_as_array(char* text);

	/**
	 * @brief Retorna el texto invertido. No se maneja el caso de NULL,
	 *        si se pasa NULL su comportamiento no esta determinado.
	 * @param[in] text: String a invertir. Admite todo tipo de strings
	 * @return Retorna un nuevo string que debe ser liberado con `free()`
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
		* @param[in] text: String a modificar. Admite todo tipo de strings
		* @param[in] substring: Substring a reemplazar. Admite todo tipo de strings
		* @param[in] replacement: String a insertar. Admite todo tipo de strings
		* @return Retorna un nuevo string que debe ser liberado con `free()`
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
	 * @brief Retorna un boolean que indica si text contiene o no a substring.
	 * @param[in] text: String a evaluar. Admite todo tipo de strings
	 * @param[in] substring: Substring a buscar. Admite todo tipo de strings
	 */
	bool    string_contains(char* text, char *substring);

	/**
	* @brief Crea un array de strings vacio
	* @return El array retornado debe ser liberado con `string_array_destroy()`
	*/
	char**  string_array_new(void);

	/**
	* @brief Destruye un array con sus strings
	* @param[in,out] array: Puntero al array a destruir. Debe apuntar a un array
	*                       de strings liberables con free() y terminado en NULL
	*/
	void    string_array_destroy(char** array);

	/**
	* @brief Retorna la cantidad de líneas del array de strings
	* @param[in] array: Array de strings terminado en NULL
	*/
	int     string_array_size(char** array);

	/**
	* @brief Verifica si el array de strings está vacío
	* @param[in] array: Array de strings terminado en NULL
	*/
	bool    string_array_is_empty(char** array);

	/**
	* @brief Agrega un string al final del array
	* @param[in,out] array: Puntero al array a modificar. Debe apuntar a un array
	*                       de strings modificable y terminado en NULL
	* @param[in] text: String a agregar. Debe ser liberable con free(), pero pasa
	*                  a formar parte del array, por lo que no debe ser liberado
		*
	* @code
	* char** array = string_array_new(); => {NULL}
	* string_array_push(&array, "hola"); => {"hola", NULL}
	* string_array_push(&array, "mundo"); => {"hola", "mundo", NULL}
	* @endcode
	*/
	void    string_array_push(char*** array, char* text);

	/**
	* @brief Reemplaza un string en un array por otro
	* @param[in,out] array: Array a modificar. Debe apuntar a un array de strings
	*                       terminado en NULL
	* @param[in] pos: Posición del string a reemplazar
	* @param[in] text: Nuevo string a insertar. Debe ser liberable con free(), pero
	*                  pasa a formar parte del array, por lo que no debe ser liberado
	* @return El string reemplazado. Debe ser liberado con `free()`
	*/
	char*   string_array_replace(char** array, int pos, char* text);

	/**
	* @brief Quita el último string del array y lo retorna
	* @param[in,out] array: Array a modificar. Debe apuntar a un array de strings
	*                       terminado en NULL
	* @return El string quitado. Deja de pertenecer al array, por lo que debe ser
	*         liberado con `free()`
	*/
	char*   string_array_pop(char** array);

#endif /* STRING_UTILS_H_ */
