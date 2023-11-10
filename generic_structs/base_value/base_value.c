//
// Created by vitor on 10/11/23.
//

#include "base_value.h"
#include "../../memory/memory.h"


typedef struct BaseValue{
    void *data;
    void *(*destructor)(void *value);
    char *(*in_str)(void *value);
    int (*eq)(void *data, void *other);
    size_t size_data;
}BaseValue;


size_t bv_get_tam(){
    return sizeof(BaseValue);
}
BaseValue *create_base_value(void *data, void *(*destructor)(void *), char *(*in_str)(void *), int (*eq)(void *, void *), size_t size_data){

    BaseValue *new = me_memory_alloc(NULL, sizeof(BaseValue));
    *new = (BaseValue){
        .data = data,
        .destructor = destructor,
        .in_str = in_str,
        .eq = eq,
        .size_data = size_data
    };
    return new;
}
BaseValue *destroy_base_value(BaseValue *self){

    if ( self == NULL){
        return NULL;
    }
    if ( self->data)
        self->data = self->destructor(self->data);
    memset(self, 0, sizeof(BaseValue));
    me_free_memory((void *)&self);
    return NULL;
}
char *bv_in_str(BaseValue *self){
    return self->in_str(self->data);
}
void *bv_get_data(BaseValue *self){
    return self->data;
}
void bv_set_data(BaseValue *self, void *new_data){
    self->data = new_data;
}
int bv_equals(BaseValue *self, BaseValue *other){
    if ( self->size_data != other->size_data ){
        return 0;
    }
    if ( !self->eq ){
        return 0;
    }
    return self->eq(self->data, other->data);
}