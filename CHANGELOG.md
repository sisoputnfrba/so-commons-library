# Lib change log

### 2021-1C

#### Features

- La interfaz de `temporal_get_string_time()` cambió a `temporal_get_string_time(1)`,
recibiendo por parámetro el formato de fecha a devolver.
- Se añadió un iterador externo para `t_list` con sus operaciones básicas
`create()`, `has_next()`, `next()`, `remove()` y `destroy()`.
- Se añadió un insertar ordenado para `t_list`: `list_add_sorted(3)`.
- Se añadieron nuevos foldeos para `t_list`: `list_fold1(2)`, `list_get_minimum(2)` y
`list_get_maximum(2)`.

#### Bugs

- Se cambió la función deprecada que usaba `temporal_get_string_time()` por
otra más portable.
- Se corrigió un bug de `string_split()` por el cual no se creaban substrings
cuando estos eran el string vacío.
- Se corrigió un bug de `list_take()` y `list_take_and_remove()` que hacía que se
devolviera una lista inconsistente cuando el count recibido era mayor
al tamaño de la lista.
- Se corrigió el comportamiento de las funciones de `t_list` que recibían un index
y ocultaban el error en caso de que este no sea válido. Este comportamiento ya no 
pasa y el error queda expuesto.
