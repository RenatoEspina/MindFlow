#ifndef MAP_H
#define MAP_H
#include "list.h"
typedef struct MapPair {
    void *key;
    void *value;
} MapPair;

typedef struct {
    List **buckets;
    int capacity;
    int size;
    int (*is_equal)(void *, void *);
    unsigned (*hash)(void *);
    int current_bucket;
    void *current_node;
}Map;

Map *map_create(int (*is_equal)(void *, void *), unsigned (*hash)(void *));
void map_insert(Map *map, void *key, void *value);
void *map_get(Map *map, void *key);
MapPair *map_remove(Map *map, void *key);
MapPair *map_search(Map *map, void *key);
void map_clean(Map *map);
MapPair *map_first(Map *map);
MapPair *map_next(Map *map);
unsigned int_hash(void *key);
unsigned string_hash(void *key);
void map_destroy(Map *map, void (*free_value)(void *));
#endif
