# Commons Library For C

[![Build Status](https://github.com/sisoputnfrba/so-commons-library/actions/workflows/unit-tests.yml/badge.svg)](https://github.com/sisoputnfrba/so-commons-library/actions/workflows/unit-tests.yml)

Biblioteca con TADs útiles para el desarrollo de aplicaciones hechas con el lenguaje C

Provee los siguientes TADs:

* Logging (commons/log.h)
* Manipulación de Strings (commons/string.h)
* Manipulación de archivos de configuración (commons/config.h)
* Colecciones de elementos
  * List (commons/collections/list.h)
  * Dictionary (commons/collections/dictionary.h)
  * Queue (commons/collections/queue.h)
* Manejo de array de bits (commons/bitarray.h)
* Manejo de fechas y timestamps (commons/temporal.h)
* Información de procesos (commons/process.h)
* Impresión de dumps de memoria (commons/memory.h)
* Impresión de errores (commons/error.h)
* Manejo simple de archivos de texto (commons/txt.h)
* Funciones de criptografía (commons/crypto.h)

## Notas

Algunas de las consideraciones a tener a la hora de su uso:

* Ninguna de las implementaciones utiliza semáforos, por lo que el uso concurrente debe ser implementado por el usuario de éstas.
* Ninguna de las funciones implementadas posee validaciones para manejo de errores.

## Dependencias

Esta biblioteca depende de las siguientes bibliotecas:

* OpenSSL para funciones de criptografía: https://packages.debian.org/sid/libssl-dev
* CSpec para pruebas unitarias: https://github.com/mumuki/cspec

## Guía de Instalación

- Clonar el repositorio desde git (no usar el link de **Download ZIP** que provee GitHub).

- `make install` -> instala la biblioteca en el sistema

- `make uninstall` -> desinstala la biblioteca

> Nota: Es posible que en un momento de la instalación aparezca una pantalla con un menú a raiz de la instalación del paquete de `libssl-dev`, simplemente con apretar Enter alcanza para continuar con la instalación.

## Guía para el uso

1. Linkear con `-lcommons` y `-lcrypto`

2. Para usarla en un .c/.h deberá incluirse de la siguiente forma: `commons/<Nombre_TAD>`

Por ejemplo:

```c
#include <commons/log.h>
#include <commons/collections/list.h>
```

### Desde Eclipse

1. Ir a las Properties del proyecto (en el Project Explorer - la columna de la izquierda - la opción aparece dándole click derecho al proyecto), y dentro de la categoría `C/C++ Build` entrar a `Settings`, y ahí a `Tool Settings`.
2. Buscar `GCC Linker` > `Libraries` > `Libraries`. Notar que entre paréntesis dice `-l`, el parámetro de `gcc` que estamos buscando.
3. Darle click en el botón de `+`, y poner el nombre de la biblioteca sin el `-l` (en este caso, `commons` y `crypto`).
4. Aceptar y buildear el proyecto.