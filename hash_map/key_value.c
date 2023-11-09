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

    KeyValue *new = me_memory_alloc(NULL, sizeof(KeyValue));
    new->key = strdup(key);
    new->value = value;
    return new;
}

const char *kv_get_key(KeyValue *self){
    return self->key;
}
void *kv_get_value(KeyValue *self){
    return self->value;
}
void kv_set_key(KeyValue *self, void *value){
    self->value = value;
}
int kv_is_this_element(KeyValue *self, KeyValue *other){
    return !strcmp(self->key, other->key);
}
void *destroy_kv(KeyValue *self){

    me_free_memory((void *)&self);
    return NULL;
}


