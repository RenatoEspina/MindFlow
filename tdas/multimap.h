#ifndef MULTIMAP_H
#define MULTIMAP_H
#include "map.h"
#include "list.h"
#include <stdlib.h>

// MultiMap es un alias de Map, pero los valores son List*
typedef Map MultiMap;

// Crea un multimap usando la función de igualdad y la función de hash
MultiMap *multimap_create(int (*is_equal)(void *key1, void *key2), unsigned (*hash)(void *key)) {
    return map_create(is_equal, hash);
}

// Inserta un valor asociado a una clave (múltiples valores por clave)
void multimap_insert(MultiMap *map, void *key, void *value) {
    List *values = (List *)map_get(map, key);

    if (values == NULL) {
        values = list_create();
        list_pushBack(values, value);
        map_insert(map, key, values);
    } else {
        list_pushBack(values, value);
    }
}

// Devuelve la lista de valores asociados a una clave
List *multimap_get(MultiMap *map, void *key) {
    return (List *)map_get(map, key);
}

// Elimina todos los valores asociados a una clave y devuelve la lista eliminada
List *multimap_remove(MultiMap *map, void *key) {
    MapPair *removed_pair = map_remove(map, key);
    if (removed_pair == NULL) return NULL;
    return (List *)removed_pair->value;
}

// Busca la clave en el multimap y devuelve el par clave/lista
MapPair *multimap_search(MultiMap *map, void *key) {
    return map_search(map, key);
}

// Iteradores
MapPair *multimap_first(MultiMap *map) {
    return map_first(map);
}

MapPair *multimap_next(MultiMap *map) {
    return map_next(map);
}

// Limpia completamente el multimap (incluyendo las listas internas)
void multimap_clean(MultiMap *map) {
    MapPair *pair = map_first(map);
    while (pair != NULL) {
        List *values = (List *)pair->value;
        list_clean(values);
        free(values);
        pair = map_next(map);
    }
    map_clean(map);
}

#endif /* MULTIMAP_H */
