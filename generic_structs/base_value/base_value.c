//
// Created by vitor on 10/11/23.
//

#include "base_value.h"
#include "../../memory/memory.h"
#include <stdio.h>

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
    if ( self->data){
        self->data = self->destructor(self->data);
        if ( self->data != NULL ){
            fprintf(
                    stderr,
                    "pointer data don't was seted as null, was expected that function destructor saved in function pointer destructor clear the regi"
                          "on of the memory and returned NULL by pointer, however, it don't was doing this!"
            );
            exit(1);
        }
    }
    memset(self, 0, sizeof(BaseValue));
    me_free(self);
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