# Commons Library For C

[![Build Status](https://github.com/sisoputnfrba/so-commons-library/actions/workflows/unit-tests.yml/badge.svg)](https://github.com/sisoputnfrba/so-commons-library/actions/workflows/unit-tests.yml)

Biblioteca con TADs útiles para el desarrollo de aplicaciones hechas con el lenguaje C

Provee los siguientes TADs:

* Logging (commons/log.h)
* Manipulación de Strings (commons/string.h)
* Manipulación de archivos de configuración (commons/config.h)
* Funciones de fechas (commons/temporal.h)
* Manejo de array de bits (commons/bitarray.h)
* Manejo de timestamps (commons/temporal.h)
* Información de procesos (commons/process.h)
* Manejo simple de archivos de texto (commons/txt.h)
* Conjunto de elementos
  * List (commons/collections/list.h)
  * Dictionary (commons/collections/dictionary.h)
  * Queue (commons/collections/queue.h)

## Notas

Algunas de las consideraciones a tener a la hora de su uso:

* Ninguna de las implementaciones utiliza semáforos, por lo que el uso concurrente debe ser implementado por el usuario de estas.
* Ninguna de las funciones implementadas posee validaciones para manejo de errores.

## Guía de Instalación

Esta biblioteca utiliza CSpec para testear todas las funcionalidades, más información en: https://github.com/mumuki/cspec

Instrucciones de instalación:

- Clonar el repositorio desde git (no usar el link de **Download ZIP** que provee GitHub).

- `make install` -> instala la biblioteca en el sistema

- `make uninstall` -> desinstala la biblioteca

## Guía para el uso

1. Linkear con `-lcommons`

2. Para usarla en un .c/.h deberá incluirse de la siguiente forma: `commons/<Nombre_TAD>`

Por ejemplo:

```c
#include <commons/log.h>
#include <commons/collections/list.h>
```

### Desde Eclipse

1. Ir a las Properties del proyecto (en el Project Explorer - la columna de la izquierda - la opción aparece dándole click derecho al proyecto), y dentro de la categoría `C/C++ Build` entrar a `Settings`, y ahí a `Tool Settings`.
2. Buscar `GCC Linker` > `Libraries` > `Libraries`. Notar que entre paréntesis dice `-l`, el parámetro de `gcc` que estamos buscando.
3. Darle click en el botón de `+`, y poner el nombre de la biblioteca sin el `-l` (en este caso, `commons`).
4. Aceptar y buildear el proyecto.
