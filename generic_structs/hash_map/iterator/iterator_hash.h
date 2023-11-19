//
// Created by vitor on 09/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_ITERATOR_HASH_H
#define TRABALHO_PRATICO_GRAFOS_ITERATOR_HASH_H
#include <stdint.h>
typedef struct Map Map;
typedef struct KeyValue KeyValue;
typedef struct ItHash ItHash;
ItHash *create_iterator(Map *hash_map);
ItHash *destructor_iterator(ItHash *self);
KeyValue *ith_next(ItHash *self);
uint64_t ith_get_current_index_vector(ItHash *self);
void ith_set_current_index_vector(ItHash *self, uint64_t index);
int ith_get_current_index_sublist(ItHash *self);
void ith_set_current_index_sublist(ItHash *self, int index);


#endif //TRABALHO_PRATICO_GRAFOS_ITERATOR_HASH_H
