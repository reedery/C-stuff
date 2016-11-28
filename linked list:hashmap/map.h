// map.h  The specification of the Map API.

#ifndef MAP_H
#define MAP_H
#include "list.h"

typedef struct map Map;

//Create a new map, given the supplied equality and hash functions
Map Map_new(int (*equals)(void *key1, void *key2), int (*hash)(void *key));

//If the map contains an entry for the specified key, return its value.
//Otherwise, return NULL.
void *Map_get(Map m, void *key);

//Insert the (key,value) pair into the map.
//If an entry for the key already exists, overwrite its value.
void Map_put(Map m, void *key, void *value);

//Return a list containing each (key,value) pair in the map.
List Map_keys(Map m);

//Free the malloc'ed space in the map.
void Map_free(Map m);

#endif

