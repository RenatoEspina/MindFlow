#ifndef SET_H
#define SET_H

#include "map.h"
#include <stdio.h>
#include <stdlib.h>

// Un Set se implementa como un Map sin valores reales
typedef Map Set;

// Crea un set usando la función de igualdad y hash
Set *set_create(int (*is_equal)(void *key1, void *key2), unsigned (*hash)(void *key)) {
  return map_create(is_equal, hash);
}

// Inserta un valor en el set
void set_insert(Set *set, void *value) {
  map_insert(set, value, NULL); // El valor puede ser NULL, ya que solo importa la clave
}

// Elimina un valor del set, y devuelve el valor eliminado (clave)
void *set_remove(Set *set, void *value) {
  MapPair *removed = map_remove(set, value);
  return removed ? removed->key : NULL;
}

// Busca un valor en el set (devuelve el valor si está, NULL si no)
void *set_search(Set *set, void *value) {
  MapPair *found = map_search(set, value);
  return found ? found->key : NULL;
}

// Limpia el set completo
void set_clean(Set *set) {
  map_clean(set);
}

// Iteradores
void *set_first(Set *set) {
  MapPair *pair = map_first(set);
  return pair ? pair->key : NULL;
}

void *set_next(Set *set) {
  MapPair *pair = map_next(set);
  return pair ? pair->key : NULL;
}

#endif /* SET_H */
