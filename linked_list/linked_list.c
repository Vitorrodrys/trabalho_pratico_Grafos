//
// Created by vitor on 08/11/23.
//

#include "linked_list.h"
#include "vertex.h"
#include "../memory/memory.h"
#include "../list/list.h"
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

    for (int i = self->quantity-1; i >=0; --i) {

         lkl_rm_element(self, i);
    }
}

int lkl_insert_element(LinkedList *self, void *data, int index){

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
void* lkl_rm_element(LinkedList *self, int index){

    if (  index >= self->quantity ){
        return NULL;
    }

    void *dado = vt_remove_element_lk(&self->first, index);
    if ( !self->first ){
        self->last = NULL;
    }
    self->quantity--;
    return dado;
}
void *lkl_get_data(LinkedList *self, int index){
    if ( index >= self->quantity ){
        return NULL;
    }
    return vt_get_data(self->first, index);
}
void* lkl_set_element(LinkedList *self, int index, void *value){

    if ( index >= self->quantity ){
        return NULL;
    }
    void *aux = vt_remove_element_lk(&self->first, index);
    self->first= vt_add_element(self->first, value, index);
    return aux;
}
void lkl_append(LinkedList *self, void *data){

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
int lkl_is_void(LinkedList *self){
    return !self->quantity;
}
int lkl_get_index_element(LinkedList *self, void *data, int (*eq)(void *, void *)){
    return vt_find_element(self->first, data, eq);
}
int lkl_get_tam(LinkedList *self){
    return self->quantity;
}