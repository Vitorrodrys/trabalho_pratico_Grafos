//
// Created by vitor on 07/11/23.
//

#include "key_value.h"
#include "../memory/memory.h"
#include <string.h>
#include <stdio.h>

KeyValue *create_key_value(const char *key, void *value, char* (*value_str)(void *), void *(*destructor)(void *)){

    KeyValue *new = me_memory_alloc(NULL, sizeof(KeyValue));
    new->key = strdup(key);
    new->value = value;
    new->value_str = value_str;
    new->destructor_value = destructor;
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

    me_free_memory((void *)&self->key);
    if (self->destructor_value) {
        self->value = self->destructor_value(self->value);
    }
    self->value_str = NULL;
    me_free_memory((void *)&self);
    return NULL;
}
char* kv_str(KeyValue *self){

    char *string_v=self->value_str(self->value);
    return me_formatted_str("\"%s\":%s", self->key, string_v);
}

