Guía de Instalación
===================

Esta biblioteca utiliza CSpec para testear todas las funcionalidades, más información en: https://github.com/mumuki/cspec


Instrucciones de instalación
----------------------------

- Clonar el repositorio desde git (no usar el link de **Download ZIP** que provee GitHub).
   - ``make install`` instala la biblioteca en el sistema
   - ``make uninstall`` desinstala la biblioteca

Guía para el uso
----------------

1. Linkear con ``-lcommons``

2. Para usarla en un .c/.h deberá incluirse de la siguiente forma: ``commons/<Nombre_TAD>``

Por ejemplo:

.. code-block:: c

  #include <commons/log.h>
  #include <commons/collections/list.h>

Desde Eclipse
~~~~~~~~~~~~~

1. Ir a las Properties del proyecto (en el Project Explorer - la columna de la izquierda - la opción aparece dándole click derecho al proyecto), y dentro de la categoría `C/C++ Build` entrar a `Settings`, y ahí a `Tool Settings`.
2. Buscar `GCC Linker` > `Libraries` > `Libraries`. Notar que entre paréntesis dice ``-l``, el parámetro de ``gcc`` que estamos buscando.
3. Darle click en el botón de `+`, y poner el nombre de la biblioteca sin el ``-l`` (en este caso, ``commons``).
4. Aceptar y buildear el proyecto.
