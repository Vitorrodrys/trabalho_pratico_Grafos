//
// Created by vitor on 07/11/23.
//

#include "list.h"
#include <stdarg.h>
#include <stdio.h>
#include "../../memory/memory.h"
#include "../../string/string.h"

typedef struct List{
    BaseValue **data;
    int current_size;
}List;

List *create_list(){
    List *new = me_memory_alloc(NULL, sizeof(List));
    new->data = NULL;
    new->current_size = 0;
    return new;
}
List* destroy_list(List *self){

    for (int i = 0; i < self->current_size; ++i) {
        self->data[i] = destroy_base_value(self->data[i]);
    }
    self->current_size = 0;
    me_free(self);
    return NULL;
}

void li_append(List *self, BaseValue *element){
    self->current_size++;
    self->data = me_memory_alloc(self->data, sizeof(void *)*self->current_size);
    self->data[self->current_size-1] = element;
}
BaseValue *li_remove_element(List *self, int index){

    void *element_remove;
    if ( index >= self->current_size  ){
        return NULL;
    }
    element_remove = self->data[index];
    for (index=index+1;index<self->current_size; index++){
        self->data[index-1] = self->data[index];
    }
    self->current_size--;
    self->data = me_memory_alloc(self->data, sizeof (void *) *self->current_size);
    return element_remove;
}

int li_search_index_element(List *self, BaseValue *element){

    for (int i = 0; i < self->current_size; ++i) {
        if (bv_equals(self->data[i], element) ){
            return i;
        }
    }
    return -1;
}
void *li_pop(List *self){
    BaseValue *ptr = self->data[self->current_size-1];
    self->current_size--;
    self->data = me_memory_alloc(self->data, sizeof (void *)*self->current_size);
    return bv_get_data(ptr);
}

void* li_dequeue(List *self){

    void *data = li_remove_element(self, 0);
    return data;
}

void *li_get_element_in_list(List *self, int index){

    if ( index >= self->current_size ){
        return NULL;
    }
    return bv_get_data(self->data[index]);
}
int li_is_void(List *self){
    return !self->current_size;
}
int li_get_tam(List *self){
    return self->current_size;
}
List *li_break_str_in_list(char *str, char *tok){

    List *list = create_list();

    char *token = strtok(str, tok);
    BaseValue *aux;
    while (token){
        aux = create_base_value(strdup(token), (void *)destroy_str, (void *)str_str, (void *)strcmp, sizeof(char));
        li_append(list, aux);
        token = strtok(NULL, tok);
    }
    return list;
}
void li_swap_elements(List *self, int index1, int index2){

    if ( index1 >= self->current_size || index2 >= self->current_size ){
        return;
    }
    me_swap(self->data+index1, self->data+index2, sizeof(void *));
}

void li_insert(List *self, BaseValue *value, int index){
    self->current_size++;
    self->data = me_memory_alloc(self->data, sizeof(void *)*self->current_size);
    for (int i = index+1; i < self->current_size; ++i) {
        self->data[i] = self->data[i-1];
    }
    self->data[index] = value;
}

char *li_str(List *self){

    if ( self->current_size == 0){
        return strdup("[ ]");
    }
    char *str = strdup("[ ");
    char *aux;
    char *element_str;
    for (int i = 0; i < self->current_size-1; ++i) {
        aux = str;
        element_str = bv_in_str(self->data[i]);
        str = str_formatted("%s %s, ", str, element_str);
        me_free_several_objects(2, (void *)&aux, (void *)&element_str);
    }
    aux = str;
    element_str = bv_in_str(self->data[self->current_size-1]);
    str = str_formatted("%s %s ]", str, element_str);
    me_free_several_objects(2, &aux, &element_str);
    return str;
}