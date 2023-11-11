//
// Created by vitor on 07/11/23.
//

#include "hash_map.h"
#include "../colision_list/colision_list.h"
#include "../../../memory/memory.h"
#include "../iterator/iterator_hash.h"
#include <stdio.h>
#include <string.h>
#include "../../list/list.h"

typedef struct Map{

    ColisionList **vector;
    int tam_vector;
    int (*f_hash)(const char *);
}Map;

int hash(const char *string){
    int sum = 0;
    while (*string){
        sum += ((sum << 5) + sum) + *string;
        string++;
    }
    return sum;
}

int map_get_index_key(Map *self, const char *key){
    return self->f_hash(key) %self->tam_vector;
}
Map *create_map(int tam_vector, int (*f_hash)(const char *)){
    Map *new = me_memory_alloc(NULL, sizeof(Map));
    new->vector = me_memory_alloc(NULL, sizeof(ColisionList *)*tam_vector);
    for (int i = 0; i < tam_vector; ++i) {
        new->vector[i] = create_colision_list();
    }
    new->tam_vector = tam_vector;
    new->f_hash = f_hash?f_hash: hash;
    return new;
}
Map *destroy_map(Map *self){
    for (int i = 0; i < self->tam_vector; ++i) {
        self->vector[i] = destroy_colision_list(self->vector[i]);
    }
    me_free(self->vector);
    self->tam_vector = 0;
    self->f_hash = 0;
    me_free(self);
    return NULL;
}

void map_add_key(Map *self, KeyValue*key_value){
    int index = map_get_index_key(self, kv_get_key(key_value));
    colist_append_colision(self->vector[index], key_value);
}
void map_att_key(Map *self, KeyValue *new_kv){
    int index = map_get_index_key(self, kv_get_key(new_kv));
    KeyValue *kv = colist_get_key_value(self->vector[index], (char *)kv_get_key(new_kv));
    if ( kv == NULL ){
        map_add_key(self, new_kv);
        return;
    }
    colist_remove_key_value(self->vector[index], (char*)kv_get_key(kv));
    colist_append_colision(self->vector[index], new_kv);
}
void map_remove_key(Map *self, char *key){
    int index = map_get_index_key(self, key);
    if (colist_is_void(self->vector[index]) ){
        return;
    }
    colist_remove_key_value(self->vector[index], key);
}

void *map_get_value(Map *self, char *key){

    int index = map_get_index_key(self, key);

    if (colist_is_void(self->vector[index]) ){
        return NULL;
    }
    KeyValue *kv = colist_get_key_value(self->vector[index], key);
    if (kv == NULL){
        return NULL;
    }
    void *value = kv_get_value(kv);
    return value;

}

KeyValue *map_next(Map *self, ItHash *iterator){

    int current_index_vector = ith_get_current_index_vector(iterator);
    int current_index_sublist = ith_get_current_index_sublist(iterator);
    KeyValue *element = colist_get_element_by_index(self->vector[current_index_vector], current_index_sublist);
    if( element == NULL ){
        int index_vector = current_index_vector+1;
        ith_set_current_index_vector(iterator, index_vector);

        while ( index_vector < self->tam_vector && colist_is_void(self->vector[index_vector])){
            index_vector++;
        }
        if(index_vector >= self->tam_vector){
            return NULL;
        }
        ith_set_current_index_vector(iterator,index_vector);
        ith_set_current_index_sublist(iterator, 1);
        element = colist_get_element_by_index(self->vector[index_vector], 0);
        return element;
    }
    ith_set_current_index_sublist(iterator,current_index_sublist+1);
    return element;
}

char* map_str(Map *self){

    ItHash *iter = create_iterator(self);
    KeyValue *current_kv = ith_next(iter);;
    char *kv_string;

    char *string_kv = strdup("{\n\t\t");
    char *aux;
    char *aux2;
    do {

        kv_string = kv_str(current_kv);
        aux = string_kv;
        string_kv = me_concat_multiplies_str(3,string_kv, kv_string, "\n\t\t");
        me_free(kv_string);
        me_free(aux);

        current_kv = ith_next(iter);


    } while (current_kv);

    iter = destructor_iterator(iter);
    aux = string_kv;
    string_kv =me_concat_str(string_kv, "\n\t}");
    me_free(aux);
    return string_kv;

}

int map_is_void(Map *self){
    ItHash *it = create_iterator(self);
    return ith_next(it) == NULL;
}


