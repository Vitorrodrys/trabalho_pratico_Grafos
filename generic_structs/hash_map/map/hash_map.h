#ifndef HASH_MAP_H
#define HASH_MAP_H
#include "../key_value/key_value.h"
#include "../iterator/iterator_hash.h"

#define DEFAULT_SIZE_VECTOR_COLISION 449
#include <stdint.h>

typedef struct Map Map;

Map *create_map(uint64_t tam_vector, uint64_t (*f_hash)(const char *));
void map_add_key(Map *self, KeyValue*key_value);
void map_remove_key(Map *self, char *key);
void *map_get_value(Map *self, const char *key);
int map_eq(Map *self, Map *other);
void map_att_key(Map *self, KeyValue *new_kv);
char* map_str(Map *self);
KeyValue *map_next(Map *self, ItHash *iterator);
Map *destroy_map(Map *self);
int map_is_void(Map *self);
#endif /* HASH_MAP_H */
