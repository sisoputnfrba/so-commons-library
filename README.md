## Commons Library For C ##

[![Build Status](https://drone.io/github.com/sisoputnfrba/so-commons-library/status.png)](https://drone.io/github.com/sisoputnfrba/so-commons-library/latest)

Biblioteca con TADs útiles para el desarrollo de aplicaciones hechas con el lenguaje C

Provee los siguientes TADs:

* Logging (commons/log.h)
* Manipulación de Strings (commons/string.h)
* Manipulación de archivos de configuración (commons/config.h)
* Funciones de fechas (commons/temporal.h)
* Manejo de array de bits (commons/bitarray.h)
* Manejo de fechas (commons/temporal.h)
* Información de procesos (commons/process.h)
* Manejo simple de archivos de texto (commons/txt.h)
* Conjunto de elementos
  * List (commons/collections/list.h)
  * Dictionary (commons/collections/dictionary.h)
  * Queue (commons/collections/queue.h)

## Notas: ##

Algunas de las consideraciones a tener a la hora de su uso:

* Ninguna de las implementaciones utiliza semáforos, por lo que el uso concurrente debe ser implementado por el usuario de estas.
* Ninguna de las funciones implementadas posee validaciones para manejo de errores.

## Guía de Instalación: ##

Estas Bibliotecas utilizan CUnit para testear todas las funcionalidades, por lo que es necesario tenerlo instalado en el sistema si se quieren correr los test.

Instrucciones de instalación: https://asciinema.org/a/8680

`sudo apt-get install libcunit1-dev` -> Instala cunit en el sistema

`sudo make install` -> instala la biblioteca en el sistema

`sudo make uninstall` -> desinstala la biblioteca

## Guía para el uso: ##

Linkear con `-lcommons`

Para usarla en un .c/.h debería incluirse de la siguiente forma: `commons/<Nombre_TAD>`

Por ejemplo:

```c
#include <commons/log.h>
#include <commons/collections/list.h>
```
