#include "map.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 103  // Número primo para menor colisión

struct Map {
    List **buckets;
    int capacity;
    int size;
    int (*is_equal)(void *, void *);
    unsigned (*hash)(void *);
    int current_bucket;
    void *current_node;
};

Map *map_create(int (*is_equal)(void *, void *), unsigned (*hash)(void *)) {
    Map *map = malloc(sizeof(Map));
    map->capacity = INITIAL_CAPACITY;
    map->size = 0;
    map->is_equal = is_equal;
    map->hash = hash;
    map->buckets = malloc(sizeof(List *) * map->capacity);
    for (int i = 0; i < map->capacity; i++)
        map->buckets[i] = list_create();
    map->current_bucket = -1;
    map->current_node = NULL;
    return map;
}

unsigned get_index(Map *map, void *key) {
    return map->hash(key) % map->capacity;
}

MapPair *map_search(Map *map, void *key) {
    unsigned idx = get_index(map, key);
    List *bucket = map->buckets[idx];
    for (MapPair *pair = list_first(bucket); pair != NULL; pair = list_next(bucket)) {
        if (map->is_equal(pair->key, key))
            return pair;
    }
    return NULL;
}

void map_insert(Map *map, void *key, void *value) {
    if (map_search(map, key) != NULL)
        return;

    unsigned idx = get_index(map, key);
    MapPair *pair = malloc(sizeof(MapPair));
    pair->key = key;
    pair->value = value;
    list_pushBack(map->buckets[idx], pair);
    map->size++;
}

void *map_get(Map *map, void *key) {
    MapPair *pair = map_search(map, key);
    return pair ? pair->value : NULL;
}

MapPair *map_remove(Map *map, void *key) {
    unsigned idx = get_index(map, key);
    List *bucket = map->buckets[idx];
    for (MapPair *pair = list_first(bucket); pair != NULL; pair = list_next(bucket)) {
        if (map->is_equal(pair->key, key)) {
            list_popCurrent(bucket);
            map->size--;
            return pair;
        }
    }
    return NULL;
}

void map_clean(Map *map) {
    for (int i = 0; i < map->capacity; i++) {
        list_clean(map->buckets[i]);
    }
    map->size = 0;
    map->current_bucket = -1;
    map->current_node = NULL;
}

MapPair *map_first(Map *map) {
    // Recorremos los buckets hasta encontrar el primero que no esté vacío
    for (int i = 0; i < map->capacity; i++) {
        // Si el bucket no es NULL y contiene elementos
        if (map->buckets[i] != NULL) {
            // Obtener el primer elemento del bucket (lista)
            MapPair *pair = list_first(map->buckets[i]);
            if (pair) {
                map->current_bucket = i;  // Guardamos el índice del bucket actual
                return pair;
            }
        }
    }
    return NULL; // Si no se encuentra ningún par, se devuelve NULL
}


MapPair *map_next(Map *map) {
    // Si no hay un bucket actual, no hay más elementos
    if (map->current_bucket == -1) {
        return NULL;
    }

    // Intentar obtener el siguiente par en el bucket actual
    MapPair *pair = list_next(map->buckets[map->current_bucket]);
    if (pair) {
        return pair; // Si se encuentra un siguiente par en el mismo bucket, lo devolvemos
    }

    // Si no hay más elementos en el bucket actual, pasar al siguiente bucket
    for (int i = map->current_bucket + 1; i < map->capacity; i++) {
        if (map->buckets[i] != NULL) {
            // Obtener el primer elemento del siguiente bucket
            pair = list_first(map->buckets[i]);
            if (pair) {
                map->current_bucket = i;  // Actualizamos al siguiente bucket
                return pair;
            }
        }
    }
    return NULL;  // Si no hay más elementos en ningún bucket
}



unsigned int_hash(void *key) {
    // Suponemos que la clave es un puntero a int
    int val = *(int *)key;
    return (unsigned)val;
}

unsigned string_hash(void *key) {
    char *str = (char *)key;
    unsigned hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c

    return hash;
}

void map_destroy(Map *map, void (*free_value)(void *)) {

    for (int i = 0; i < map->capacity; i++) {
        MapPair *pair = list_first(map->buckets[i]);
        int liberados = 0;

        while (pair != NULL) {
            if (free_value) {
                free_value(pair->value);
            }
            pair = list_next(map->buckets[i]);
            liberados++;
        }

        list_clean(map->buckets[i]);
        free(map->buckets[i]);
    }

    free(map->buckets);
    free(map);

}
