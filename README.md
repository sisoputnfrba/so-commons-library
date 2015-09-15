## Commons Library For C ##

[![Build Status](https://travis-ci.org/sisoputnfrba/so-commons-library.svg?branch=master)](https://travis-ci.org/sisoputnfrba/so-commons-library)

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

Estas Bibliotecas utilizan CSpec para testear todas las funcionalidades, mas informacion en: https://github.com/pepita-remembrance/cspec

Instrucciones de instalación:

- Clonar el repositorio desde git (no usar el link de **Download ZIP** que provee GitHub).

- `sudo make install` -> instala la biblioteca en el sistema

- `sudo make uninstall` -> desinstala la biblioteca

[![asciicast](https://asciinema.org/a/17x56e36koqybtq1jx8p3kfnp.png)](https://asciinema.org/a/17x56e36koqybtq1jx8p3kfnp)

## Guía para el uso: ##

Linkear con `-lcommons`

Para usarla en un .c/.h debería incluirse de la siguiente forma: `commons/<Nombre_TAD>`

Por ejemplo:

```c
#include <commons/log.h>
#include <commons/collections/list.h>
```

### Desde eclipse

1. Ir a las Properties del proyecto (en el Project Explorer - la columna de la izquierda - la opción aparece dándole click derecho al proyecto), y dentro de la categoría `C/C++ Build` entrar a `Settings`, y ahí a `Tool Settings`.
2. Buscar `GCC Linker` > `Libraries` > `Libraries`. Notar que entre paréntesis dice `-l`, el parámetro de `gcc` que estamos buscando.
3. Darle click en el botón de `+`, y poner el nombre de la biblioteca sin el `-l` (en este caso, `commons`).
4. Aceptar y buildear el proyecto.
