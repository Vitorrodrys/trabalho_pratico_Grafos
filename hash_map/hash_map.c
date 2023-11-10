//
// Created by vitor on 07/11/23.
//

#include "hash_map.h"
#include "../linked_list/linked_list.h"
#include "../memory/memory.h"
#include "iterator_hash.h"
#include <stdio.h>
#include <string.h>
#include "../list/list.h"

typedef struct Map{

    LinkedList **vector;
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
    return self->f_hash(key)%self->tam_vector;
}
Map *create_map(int tam_vector, int (*f_hash)(const char *)){

    Map *new = me_memory_alloc(NULL, sizeof(Map));
    new->vector = me_memory_alloc(NULL, sizeof(LinkedList *)*tam_vector);
    for (int i = 0; i < tam_vector; ++i) {
        new->vector[i] = create_linked_list();
    }
    new->tam_vector = tam_vector;
    new->f_hash = f_hash?f_hash: hash;
    return new;
}
Map *destroy_map(Map *self){

    ItHash *ith = create_iterator(self);
    KeyValue *next_elemen = ith_next(ith);

    while ( next_elemen ){
        next_elemen = destroy_kv(next_elemen);
        next_elemen = ith_next(ith);
    }
    for (int i = 0; i < self->tam_vector; ++i) {

        for (int j = 0; j< lkl_get_tam(self->vector[i]); j++){
            lkl_set_element(self->vector[i],j, NULL);
        }

    }
}

void map_add_key(Map *self, KeyValue*key_value){

    int index = map_get_index_key(self, kv_get_key(key_value));
    lkl_append(self->vector[index], key_value);

}
void map_att_key(Map *self, KeyValue *new_kv){

    int index = map_get_index_key(self, kv_get_key(new_kv));
    if ( lkl_is_void(self->vector[index]) ){
        map_add_key(self, new_kv);
        return;
    }

    KeyValue *element;
    int index_in_list = lkl_get_index_element(self->vector[index], new_kv, (void *) kv_is_this_element);

    if ( index_in_list == -1 ){
        map_add_key(self, new_kv);
        return;
    }
    element = lkl_set_element(self->vector[index], index_in_list, new_kv);
    destroy_kv(element);
}
void map_remove_key(Map *self, char *key){

    int index = map_get_index_key(self, key);

    if (lkl_is_void(self->vector[index]) ){
        return;
    }

    KeyValue *element = create_key_value(key, NULL, NULL, NULL);
    int index_in_list = lkl_get_index_element(self->vector[index], element, (void *) kv_is_this_element);
    if ( index_in_list == -1 ){
        return;
    }
    element=destroy_kv(element);
    element= lkl_rm_element(self->vector[index], index_in_list);
    void *value = kv_get_value(element);
    element = destroy_kv(element);


}

void *map_get_key(Map *self, char *key){

    int index = map_get_index_key(self, key);

    if (lkl_is_void(self->vector[index]) ){
        return NULL;
    }

    KeyValue *element = create_key_value(key, NULL, NULL, NULL);
    int index_in_list = lkl_get_index_element(self->vector[index], element, (void *) kv_is_this_element);
    if ( index_in_list == -1 ){
        element=destroy_kv(element);//this return NULL, only do this because this way the compilator don't discarted the value returned by the function, will return NULL
        return element;
    }
    element=destroy_kv(element);
    element=lkl_get_data(self->vector[index], index_in_list);
    void *value = kv_get_value(element);
    return value;

}

KeyValue *map_next(Map *self, ItHash *iterator){

    int current_index_vector = ith_get_current_index_vector(iterator);
    int current_index_sublist = ith_get_current_index_sublist(iterator);
    KeyValue *element = lkl_get_data(self->vector[current_index_vector], current_index_sublist);

    if( element == NULL ){
        int index_vector = current_index_vector+1;
        ith_set_current_index_vector(iterator, index_vector);

        while ( index_vector < self->tam_vector && lkl_is_void(self->vector[index_vector])){
            index_vector++;
        }
        if(index_vector >= self->tam_vector){
            return NULL;
        }
        ith_set_current_index_vector(iterator,index_vector);
        ith_set_current_index_sublist(iterator, 1);
        element = lkl_get_data(self->vector[index_vector], 0);
        return element;
    }
    ith_set_current_index_sublist(iterator,current_index_sublist+1);
    return element;
}

char* map_str(Map *self){

    ItHash *iter = create_iterator(self);
    KeyValue *current_kv = ith_next(iter);;
    char *key;
    char *value;

    int quantity_chars=0;
    char *string_kv = strdup("{\n\t\t");
    char *aux;
    char *aux2;
    do {

        key = (char *)kv_get_key(current_kv);
        value = current_kv->value_str(current_kv->value);

        aux = me_formatted_str("\"%s\": %s,\n", key, value);
        aux2=string_kv;
        string_kv = me_concat_str(string_kv, aux);
        me_free_memory((void *)&aux2);

        current_kv->value_str(current_kv->value);
        current_kv = ith_next(iter);


    } while (current_kv);

    iter = destructor_iterator(iter);
    aux = string_kv;
    string_kv =me_concat_str(string_kv, "\n\t}");
    me_free_memory((void *)&aux);
    return string_kv;


}

