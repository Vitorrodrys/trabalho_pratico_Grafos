//
// Created by vitor on 07/11/23.
//

#ifndef UNTITLED70_KEY_VALUE_H
#define UNTITLED70_KEY_VALUE_H
#include "../../base_value/base_value.h"
typedef struct KeyValue{
    BaseValue *value;
    char *key;
}KeyValue;

size_t kv_get_tam();
void kv_set_key(KeyValue *self, void *value);
void *kv_get_value(KeyValue *self);
const char *kv_get_key(KeyValue *self);
KeyValue *create_key_value(const char *key, BaseValue *value);
int kv_is_this_element(KeyValue *self, KeyValue *other);
void *destroy_kv(KeyValue *self);
char* kv_str(KeyValue *self);
#endif //UNTITLED70_KEY_VALUE_H
