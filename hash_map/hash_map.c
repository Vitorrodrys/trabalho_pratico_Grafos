//
// Created by vitor on 07/11/23.
//

#include "hash_map.h"
#include "../linked_list/linked_list.h"
#include "../memory/memory.h"
#include "key_value.h"
#include <string.h>

typedef struct Map{

    LinkedList **vector;
    int tam_vector;
    int (*f_hash)(char *);
}Map;

int hash(char *string){
    int sum = 0;
    int tam_str = strlen(string);
    for (int i = 0; i < tam_str; ++i) {
        sum += string[i]*tam_str+string[i%tam_str+1];
    }
    return sum;
}

int map_get_index_key(Map *self, char *key){
    return self->f_hash(key)%self->tam_vector;
}
Map *create_map(int tam_vector, int (*f_hash)(char *)){

    Map *new = me_memory_alloc(NULL, sizeof(Map));
    new->vector = me_memory_alloc(NULL, sizeof(LinkedList *)*tam_vector);
    for (int i = 0; i < tam_vector; ++i) {
        new->vector[i] = create_linked_list();
    }
    new->tam_vector = tam_vector;
    new->f_hash = f_hash?f_hash: hash;
    return new;
}

void map_add_key(Map *self, char *key, void *value){

    int index = map_get_index_key(self, key);
    lkl_append(self->vector[index], create_key_value(key, value));

}
void* map_remove_key(Map *self, char *key){

    int index = map_get_index_key(self, key);

    if (lkl_is_void(self->vector[index]) ){
        return NULL;
    }

    KeyValue *element = create_key_value(key, NULL);
    int index_in_list = lkl_get_index_element(self->vector[index], element, (void *) kv_is_this_element);
    if ( index_in_list == -1 ){
        return NULL;
    }
    element=destroy_kv(element);
    element= lkl_rm_element(self->vector[index], index_in_list);
    void *value = kv_get_value(element);
    element = destroy_kv(element);
    return value;

}

void *map_search_key(Map *self, char *key){

    int index = map_get_index_key(self, key);

    if (lkl_is_void(self->vector[index]) ){
        return NULL;
    }

    KeyValue *element = create_key_value(key, NULL);
    int index_in_list = lkl_get_index_element(self->vector[index], element, (void *) kv_is_this_element);
    if ( index_in_list == -1 ){
        element=destroy_kv(element);//this return NULL, only do this because this way the compilator don't discarted the value returned by the function
        return element;
    }
    element=destroy_kv(element);
    element=lkl_get_data(self->vector[index], index_in_list);
    void *value = kv_get_value(element);
    return value;

}


