---------------------------------------
# Commons Library For C #

Biblioteca con TADs útiles para el desarrollo de una aplicación en C

Provee los siguientes TADs:

* Logging (commons/log.h)
* Manipulación de Strings (commons/string.h)
* Conjunto de elementos
  * List (commons/collections/list.h)
  * Dictionary (commons/collections/dictionary.h)
  * Queue (commons/collections/queue.h)
* Manipulación de archivos de configuración (commons/config.h)
* Funciones de fechas (commons/temporal.h)
* BitArray (commons/bitarray.h)

## Notas: ##

Algunas de las consideraciones a tener a la hora de su uso:

* Ninguna de las implementaciones utiliza semaforos, por lo que el uso concurrente debe ser implementado por el usuario de estas.
* Ninguna de las funciones implementadas posee validaciones para manejo de errores.

---------------------------------------

## Guia de Instalacion: ##

Estas Bibliotecas utilizan CUnit para testear todas las funcionalidades, por lo que es necesario tenerlo instalado en el sistema.
Para su utilizacion con eclipse coloque commons-library dentro del workspace, luego desde el eclipse cree un proyecto de biblioteca dinamica y coloque como nombre de esta commons-library. Esto va a hacer que eclipse cree la configuracion para utilizar este proyecto como una biblioteca dinamica.
Si requiere que un proyecto utilice a este, siga los pasos pasos para configurar la biblioteca compartida como parte de este y como path de los includes coloque el contenido de la carpeta src. Por lo que los includes quedarian como:

	#include <commons/log.h>
	#include <commons/string.h>

