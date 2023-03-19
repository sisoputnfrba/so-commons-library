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

	typedef struct {
		char *path;
		t_dictionary *properties;
	} t_config;

	/**
	 * @brief Crea una estructura t_config
	 *
	 * @param path ruta del archivo de configuracion
	 * @return     Retorna un puntero hacia la estructura creada o NULL en caso de
	 *             no encotrar el archivo en el path especificado.
	 */
	t_config *config_create(char *path);

	/**
	 * @param config puntero a la estructura t_config
	 * @param key    clave a buscar
	 * @return       Retorna true si key se encuentra en la configuracion.
	 */
	bool      config_has_property(t_config*, char* key);

	/**
	 * @param config puntero a la estructura t_config
	 * @param key    clave a buscar
	 * @return       Retorna un string con el valor asociado a la clave key
	 */
	char     *config_get_string_value(t_config*, char *key);

	/**
	 * @param config puntero a la estructura t_config
	 * @param key    clave a buscar
	 * @return       Retorna un entero con el valor asociado a la clave key
	 */
	int       config_get_int_value(t_config*, char *key);

	/**
	 * @param config puntero a la estructura t_config
	 * @param key    clave a buscar
	 * @return       Retorna un long con el valor asociado a la clave key
	 */
	long      config_get_long_value(t_config*, char *key);

	/**
	 * @param config puntero a la estructura t_config
	 * @param key    clave a buscar
	 * @return       Retorna un double con el valor asociado a la clave key
	 */
	double    config_get_double_value(t_config*, char *key);


	/**
	 * @param config puntero a la estructura t_config
	 * @param key    clave a buscar
	 * @return       Retorna un array de strings con los valores asociados a la
	 *               clave key
	 *
	 * @note El array debe ser liberado con string_array_destroy()
	 * @note En el archivo de configuracion un valor de este tipo debe ser
	 *       representado por una lista de valores separados por coma y entre
	 *       corchetes. Por ejemplo:
	 * @code
	 *  VALORES=[1,2,3,4,5]
	 * @endcode
	*/
	char**    config_get_array_value(t_config*, char* key);

	/**
	 * @param config puntero a la estructura t_config
	 * @return       Retorna la cantidad de claves en el archivo de configuracion
	 */
	int       config_keys_amount(t_config*);

	/**
	 * @brief Destruye la estructura config.
	 *
	 * @param config puntero a la estructura t_config
	 */
	void      config_destroy(t_config *config);

	/**
	 * @brief Setea el valor en el archivo de config, a la key asociada.
	 *
	 * @param config puntero a la estructura t_config
	 * @param key    clave a setear
	 * @param value  valor a setear
	 */
	void      config_set_value(t_config*, char *key, char *value);

	/**
	 * @brief Remueve la clave y su valor asociado del archivo de config.
	 *
	 * @param config puntero a la estructura t_config
	 * @param key    clave a remover
	 */
	void      config_remove_key(t_config*, char *key);

	/**
	 * @brief Reescribe el archivo de configuracion con los valores del config.
	 *
	 * @param config puntero a la estructura t_config
	 * @return       Retorna 0 si se pudo reescribir el archivo, -1 en caso
	 *               contrario.
	 */
	int       config_save(t_config*);

	/**
	 * @brief Escribe un archivo de configuracion en el path indicado con los
	 *        valores del config.
	 *
	 * @param config puntero a la estructura t_config
	 * @param path   ruta del archivo de configuracion a crear
	 * @return       Retorna 0 si se pudo crear el archivo, -1 en caso contrario.
	 */
	int       config_save_in_file(t_config*, char *path);

#endif /* CONFIG_H_ */
