//
// Created by vitor on 07/11/23.
//

#include "list.h"
#include <stdarg.h>
#include <stdio.h>
#include "../memory/memory.h"

typedef struct List{

    void **data;
    int current_size;

}List;

List *create_list(){

    List *new = memory_alloc(NULL, sizeof(List));
    new->data = NULL;
    new->current_size = 0;
    return new;
}

void append(List *self, void *element){
    self->current_size++;
    self->data = memory_alloc(self->data, sizeof(void *)*self->current_size);
    self->data[self->current_size-1] = element;
}
void* remove_element(List *self, int index){

    void *element_remove;
    if ( index >= self->current_size  ){
        return NULL;
    }
    element_remove = self->data[index];
    for (index=index+1;index<self->current_size; index++){
        self->data[index-1] = self->data[index];
    }
    self->current_size--;
    self->data = memory_alloc(self->data, sizeof (void *) *self->current_size);
    return element_remove;
}

int search_index_element(List *self, void *element, int (*is_this_element)(void *, void *)){

    for (int i = 0; i < self->current_size; ++i) {
        if ( is_this_element( self->data[i], element ) ){
            return i;
        }
    }
    return -1;
}
void *pop(List *self){

    void *ptr = self->data[self->current_size-1];
    self->current_size--;
    self->data = memory_alloc(self->data, sizeof (void *)*self->current_size);
    return ptr;
}

void* dequeue(List *self){

    void *data = remove_element(self, 0);
    return data;
}

void* destroy_list(List *self, int quantity_destructors, ...){

    if ( self->current_size != quantity_destructors ){
        fprintf(stderr,"expected %d destructors, but received only %d!\n", self->current_size, quantity_destructors);
        exit(1);
    }

    va_list p;
    va_start(p, quantity_destructors);

    void* (* f_destructor)(void*);
    for (int i = 0; i < quantity_destructors; ++i) {
        f_destructor = va_arg(p, void *);
        if ( f_destructor == NULL ){
            free_memory(self->data+i);
        }else
            self->data[i] =  f_destructor(self->data[i]);

    }
    va_end(p);

    free_memory((void*)&self->data);
    self->current_size = 0;
    free_memory((void *)&self);
    return NULL;



}

void *get_element_in_list(List *self, int index){

    if ( index >= self->current_size ){
        return NULL;
    }
    return self->data[index];
}
int is_void(List *self){
    return !self->current_size;
}
int get_tam(List *self){
    return self->current_size;
}