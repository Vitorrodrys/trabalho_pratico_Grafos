//
// Created by vitor on 07/11/23.
//

#include "key_value.h"
#include "../../../memory/memory.h"
#include <string.h>
#include <stdio.h>

KeyValue *create_key_value(const char *key, BaseValue *value){

    KeyValue *new = me_memory_alloc(NULL, sizeof(KeyValue));
    new->key = strdup(key);
    new->value = value;
    return new;
}

size_t kv_get_tam(){
    return sizeof(KeyValue);
}

const char *kv_get_key(KeyValue *self){
    return self->key;
}
void *kv_get_value(KeyValue *self){
    return bv_get_data(self->value);
}
void kv_set_key(KeyValue *self, void *value){
    bv_set_data(self->value,value);
}
int kv_is_this_element(KeyValue *self, KeyValue *other){
    return !strcmp(self->key, other->key);
}
void *destroy_kv(KeyValue *self){
    me_free_memory((void *)&self->key);
    self->value = destroy_base_value(self->value);
    me_free_memory((void *)&self);
    return NULL;
}
char* kv_str(KeyValue *self){
    return me_formatted_str("\"%s\":%s", self->key,  bv_in_str(self->value));
}

