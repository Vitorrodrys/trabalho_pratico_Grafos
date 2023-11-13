//
// Created by vitor on 08/11/23.
//

#include "linked_list.h"
#include "vertex.h"
#include "../../memory/memory.h"
typedef struct LinkedList{

    Vertex *first;
    Vertex *last;
    int quantity;
}LinkedList;

LinkedList *create_linked_list(){

    LinkedList *new = me_memory_alloc(NULL, sizeof(LinkedList));
    *new = (LinkedList){
      .quantity = 0,
      .first = NULL,
      .last = NULL
    };
    return new;
}

LinkedList *destroy_lkl(LinkedList *self){


    int cp_quantity = self->quantity;
    for (int i = 0; i <cp_quantity; ++i) {
         lkl_rm_element(self, 0);
    }
    self->first = NULL;
    self->last = NULL;
    self->quantity = 0;
    me_free(self);
    return NULL;
}

int lkl_insert_element(LinkedList *self, BaseValue *data, int index){

    if ( index >= self->quantity){
        return 0;
    }
    self->first = vt_add_element(self->first, data, index);
    self->quantity++;

    if ( !self->quantity ){
        self->last = self->first;
        return 1;
    }
    if ( !self->quantity-2 == index ){
        self->last = vt_get_next(self->last);
    }
    return 1;
}
void lkl_rm_element(LinkedList *self, int index){

    if (  index >= self->quantity ){
        return;
    }

    vt_remove_element_lk(&self->first, &self->last,index, destroy_vertex);
    if ( !self->first ){
        self->last = NULL;
    }
    self->quantity--;
}
void *lkl_get_data(LinkedList *self, int index){
    if ( index >= self->quantity ){
        return NULL;
    }
    return vt_get_data(self->first, index);
}
void lkl_set_element(LinkedList *self, int index, BaseValue *value){

    if ( index >= self->quantity ){
        return;
    }
    vt_remove_element_lk(&self->first, &self->last,index, destroy_vertex);
    self->first= vt_add_element(self->first, value, index);
}
void lkl_append(LinkedList *self, BaseValue *data){

    if (!self->quantity){
        self->first = create_vertex(data, NULL);
        self->last = self->first;
        self->quantity++;
        return;
    }
    vt_add_element(self->last, data, 1);
    self->last = vt_get_next(self->last);
    self->quantity++;

}
BaseValue *lkl_pop(LinkedList *self){
    BaseValue *data = vt_get_base_value(self->last);
    vt_remove_element_lk(&self->first, &self->last,self->quantity-1, destroy_vertex_without_destroy_value);
    if ( self->first == NULL ){
        self->last = NULL;
    }
    self->quantity--;
    return data;

}
int lkl_is_void(LinkedList *self){
    return !self->quantity;
}
int lkl_get_index_element(LinkedList *self, BaseValue *data){
    return vt_find_element(self->first, data);
}
int lkl_get_tam(LinkedList *self){
    return self->quantity;
}
