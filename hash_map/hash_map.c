//
// Created by vitor on 07/11/23.
//

#include "hash_map.h"
#include "../list/list.h"
#include "../memory/memory.h"
#include "key_value.h"
#include <string.h>

typedef struct Map{

    List **vector;
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

int get_index_key(Map *self, char *key){
    return self->f_hash(key)%self->tam_vector;
}
Map *create_map(int tam_vector, int (*f_hash)(char *)){

    Map *new = memory_alloc(NULL, sizeof(Map));
    new->vector = memory_alloc(NULL, sizeof(List *)*tam_vector);
    for (int i = 0; i < tam_vector; ++i) {
        new->vector[i] = create_list();
    }
    new->tam_vector = tam_vector;
    new->f_hash = f_hash?f_hash: hash;
    return new;
}

void add_key(Map *self, char *key, void *value){

    int index = get_index_key(self, key);
    append(self->vector[index], create_key_value(key, value));

}
void* remove_key(Map *self, char *key){

    int index = get_index_key(self, key);

    if (is_void(self->vector[index]) ){
        return NULL;
    }

    KeyValue *element = create_key_value(key, NULL);
    int index_in_list = search_index_element(self->vector[index], element, (void *)is_this_element_kv);
    if ( index_in_list == -1 ){
        return NULL;
    }
    element=destroy_kv(element);
    element=remove_element(self->vector[index], index_in_list);
    void *value = get_value(element);
    element = destroy_kv(element);
    return value;

}

void *search_key(Map *self, char *key){

    int index = get_index_key(self, key);

    if (is_void(self->vector[index]) ){
        return NULL;
    }

    KeyValue *element = create_key_value(key, NULL);
    int index_in_list = search_index_element(self->vector[index], element, (void *)is_this_element_kv);
    if ( index_in_list == -1 ){
        element=destroy_kv(element);//this return NULL, only do this because this way the compilator don't discarted the value returned by the function
        return element;
    }
    element=destroy_kv(element);
    element=get_element_in_list(self->vector[index], index_in_list);
    void *value = get_value(element);
    return value;

}

