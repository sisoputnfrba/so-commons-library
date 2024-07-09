.. so-commons-library documentation master file, created by
   sphinx-quickstart on Mon Jul  8 22:10:32 2024.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Commons Library For C
==============================================

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

Notas
-----

Algunas de las consideraciones a tener a la hora de su uso:

* Ninguna de las implementaciones utiliza semáforos, por lo que el uso concurrente debe ser implementado por el usuario de estas.
* Ninguna de las funciones implementadas posee validaciones para manejo de errores.

.. toctree::
   :maxdepth: 3
   :caption: Documentación

   install
   build/exhale/library_root

* :ref:`genindex`

Consultas
---------

Para consultas, podés subir un issue al foro de la materia:
`sisoputnfrba/foro <https://github.com/sisoputnfrba/foro>`_.


Aportes
-------

Si querés aportar a la biblioteca, podés hacerlo a través de un pull request en el repositorio de GitHub:
`sisoputnfrba/so-commons-library <https://github.com/sisoputnfrba/so-commons-library>`_.
