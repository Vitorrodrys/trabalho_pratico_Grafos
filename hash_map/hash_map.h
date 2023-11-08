#ifndef HASH_MAP_H
#define HASH_MAP_H

typedef struct Map Map;

int hash(char *string);
int map_get_index_key(Map *self, char *key);
Map *create_map(int tam_vector, int (*f_hash)(char *));
void map_add_key(Map *self, char *key, void *value);
void *map_remove_key(Map *self, char *key);
void *map_search_key(Map *self, char *key);

#endif /* HASH_MAP_H */
