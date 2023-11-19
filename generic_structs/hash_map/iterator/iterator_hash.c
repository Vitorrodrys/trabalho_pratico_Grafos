//
// Created by vitor on 09/11/23.
//

#include "iterator_hash.h"
#include "../../../memory/memory.h"
#include "../map/hash_map.h"
typedef struct ItHash{

    uint64_t current_index_vector;
    int current_index_sublist;
    Map *map;
}ItHash;

ItHash *create_iterator(Map *hash_map){

    ItHash *new = me_memory_alloc(NULL, sizeof(ItHash));
    *new = (ItHash){
        .current_index_sublist = 0,
        .current_index_vector=0,
        .map = hash_map
    };
    return new;
}
ItHash *destructor_iterator(ItHash *self){
    memset(self, 0, sizeof(ItHash));
    me_free(self);
    return NULL;
}
KeyValue *ith_next(ItHash *self){
    return map_next(self->map, self);
}

uint64_t ith_get_current_index_vector(ItHash *self){
    return self->current_index_vector;
}
int ith_get_current_index_sublist(ItHash *self){
    return self->current_index_sublist;
}
void ith_set_current_index_vector(ItHash *self, uint64_t index){
    self->current_index_vector = index;
}
void ith_set_current_index_sublist(ItHash *self, int index){
    self->current_index_sublist = index;
}