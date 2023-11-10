#ifndef HASH_MAP_H
#define HASH_MAP_H
#include "key_value.h"
#include "iterator_hash.h"
typedef struct Map Map;

int map_get_index_key(Map *self, const char *key);
Map *create_map(int tam_vector, int (*f_hash)(const char *));
void map_add_key(Map *self, KeyValue*key_value);
void map_remove_key(Map *self, char *key);
void *map_get_key(Map *self, char *key);
void map_att_key(Map *self, KeyValue *new_kv);
char* map_str(Map *self);
KeyValue *map_next(Map *self, ItHash *iterator);
#endif /* HASH_MAP_H */
