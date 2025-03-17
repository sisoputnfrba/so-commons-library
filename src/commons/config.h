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

#ifndef CONFIG_H_
#define CONFIG_H_

	#include "collections/dictionary.h"

	/**
	 * @file
	 * @brief `#include <commons/config.h>`
	 */

	/**
	 * @struct t_config
	 * @brief Manejo de archivos de configuración. Inicializar con `config_create()`.
	 */
	typedef struct {
		char *path;
		t_dictionary *properties;
	} t_config;

	/**
	* @brief Crea una estructura t_config
	* @param path Ruta hacia el archivo de configuracion
	* @return Retorna un puntero hacia la estructura creada, o NULL
	*         en caso de no encontrar el archivo en el path especificado.
	*         Una vez que se deje de usar, se debe liberar con `config_destroy()`.
	*/
	t_config *config_create(char *path);

	/**
	* @brief Retorna true si key se encuentra en la configuracion.
	*/
	bool 	  config_has_property(t_config*, char* key);

	/**
	* @brief Retorna un string con el valor asociado a key.
	* @warning Devuelve un puntero perteneciente a la estructura t_config, por lo
	*          que no debe ser liberado por fuera de la misma.
	*/
	char 	 *config_get_string_value(t_config*, char *key);

	/**
	* @brief Retorna un int con el valor asociado a key.
	*/
	int 	  config_get_int_value(t_config*, char *key);

	/**
	* @brief Retorna un long con el valor asociado a key.
	*/
	long	  config_get_long_value(t_config*, char *key);

	/**
	* @brief Retorna un double con el valor asociado a key.
	*/
	double 	  config_get_double_value(t_config*, char *key);

	/**
	* @brief Retorna un array con los valores asociados a la key especificada.
	* @return Devuelve un array de strings terminado en NULL. Debe ser liberado
	*         con `string_array_destroy()` una vez que se deje de usar.
	*
	* @note En el archivo de configuracion un valor de este tipo debería ser representado
	*       de la siguiente forma [lista_valores_separados_por_coma]. Ejemplo:
	*
	* @code
	* VALORES=[1,2,3,4,5]
	* @endcode
	*/
	char**    config_get_array_value(t_config*, char* key);

	/**
	* @brief Retorna la cantidad de keys.
	*/
	int 	  config_keys_amount(t_config*);

	/**
	* @brief Destruye la estructura config.
	*/
	void 	  config_destroy(t_config *config);

	/**
	* @brief Setea el valor en el archivo de config, a la key asociada.
	*/
	void      config_set_value(t_config*, char *key, char *value);

	/**
	* @brief Remueve la clave y su valor asociado del archivo de config.
	*/
	void      config_remove_key(t_config*, char *key);

	/**
	* @brief Reescribe el archivo de configuracion con los valores del config.
	* @return Retorna mayor a 0 si se pudo guardar el archivo, -1 en caso de error.
	*/
	int       config_save(t_config*);

	/**
	* @brief Escribe un archivo de configuracion en el path indicado con los valores del config.
	* @return Retorna mayor a 0 si se pudo guardar el archivo, -1 en caso de error.
	*/
	int       config_save_in_file(t_config*, char *path);

#endif /* CONFIG_H_ */
