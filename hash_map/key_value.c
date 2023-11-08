//
// Created by vitor on 07/11/23.
//

#include "key_value.h"
#include "../memory/memory.h"
#include <string.h>

typedef struct KeyValue{

    void *value;
    char *key;
}KeyValue;

KeyValue *create_key_value(char *key, void *value){

    KeyValue *new = memory_alloc(NULL, sizeof(KeyValue));
    new->key = key;
    new->value = value;
    return new;
}

const char *get_key(KeyValue *self){
    return self->key;
}
void *get_value(KeyValue *self){
    return self->value;
}
void set_key(KeyValue *self, void *value){
    self->value = value;
}
int is_this_element_kv(KeyValue *self, KeyValue *other){
    return !strcmp(self->key, other->key);
}
void *destroy_kv(KeyValue *self){

    free_memory((void *)&self);
    return NULL;
}


