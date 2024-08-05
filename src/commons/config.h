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
	 * @struct t_config
	 * @brief  Manejo de archivos de configuracion
	 */
	typedef struct {
		char *path;
		t_dictionary *properties;
	} t_config;

	/**
	* @brief   Crea una estructura t_config
	* @relates t_config
	*
	* @param path Ruta hacia el archivo de configuracion
	* @return     Retorna un puntero hacia la estructura creada, o NULL
	*             en caso de no encontrar el archivo en el path especificado.
	*/
	t_config *config_create(char *path);

	/**
	* @brief   Retorna true si key se encuentra en la configuracion.
	* @relates t_config
	*/
	bool 	  config_has_property(t_config*, char* key);

	/**
	* @brief   Retorna un string con el valor asociado a key.
	* @relates t_config
	*/
	char 	 *config_get_string_value(t_config*, char *key);

	/**
	* @brief   Retorna un int con el valor asociado a key.
	* @relates t_config
	*/
	int 	  config_get_int_value(t_config*, char *key);

	/**
	* @brief   Retorna un long con el valor asociado a key.
	* @relates t_config
	*/
	long	  config_get_long_value(t_config*, char *key);

	/**
	* @brief   Retorna un double con el valor asociado a key.
	* @relates t_config
	*/
	double 	  config_get_double_value(t_config*, char *key);

	/**
	* @brief   Retorna un array con los valores asociados a la key especificada.
	* @relates t_config
	*
	* @note En el archivo de configuracion un valor de este tipo debería ser representado
	*       de la siguiente forma [lista_valores_separados_por_coma]. Ejemplo:
	*
	* @code
	* VALORES=[1,2,3,4,5]
	* @endcode
	*
	* @note    El array que devuelve termina en NULL
	*/
	char**    config_get_array_value(t_config*, char* key);

	/**
	* @brief   Retorna la cantidad de keys.
	* @relates t_config
	*/
	int 	  config_keys_amount(t_config*);

	/**
	* @brief   Destruye la estructura config.
	* @relates t_config
	*/
	void 	  config_destroy(t_config *config);

	/**
	* @brief   Setea el valor en el archivo de config, a la key asociada.
	* @relates t_config
	*/
	void      config_set_value(t_config*, char *key, char *value);

	/**
	* @brief   Remueve la clave y su valor asociado del archivo de config.
	* @relates t_config
	*/
	void      config_remove_key(t_config*, char *key);

	/**
	* @brief   Reescribe el archivo de configuracion con los valores del config.
	* @relates t_config
	*/
	int       config_save(t_config*);

	/**
	* @brief   Escribe un archivo de configuracion en el path indicado con los valores del config.
	* @relates t_config
	*/
	int       config_save_in_file(t_config*, char *path);

#endif /* CONFIG_H_ */
