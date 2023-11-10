//
// Created by vitor on 07/11/23.
//

#ifndef UNTITLED70_KEY_VALUE_H
#define UNTITLED70_KEY_VALUE_H
typedef struct KeyValue{
    void *value;
    char *key;
    char* (*value_str)(void *);
    void *(*destructor_value)(void *);
}KeyValue;
void kv_set_key(KeyValue *self, void *value);
void *kv_get_value(KeyValue *self);
const char *kv_get_key(KeyValue *self);
KeyValue *create_key_value(const char *key, void *value, char* (*value_str)(void *), void *(*destructor)(void *));
int kv_is_this_element(KeyValue *self, KeyValue *other);
void *destroy_kv(KeyValue *self);
char* kv_str(KeyValue *self);
#endif //UNTITLED70_KEY_VALUE_H
