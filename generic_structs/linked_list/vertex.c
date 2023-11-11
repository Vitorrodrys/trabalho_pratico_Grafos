//
// Created by vitor on 08/11/23.
//

#include "vertex.h"
#include "../../memory/memory.h"

Vertex *create_vertex(BaseValue *dado, Vertex *next){

    Vertex *new = me_memory_alloc(NULL, sizeof(Vertex));
    new->data = dado;
    new->next = next;
    return new;
}

Vertex *destroy_vertex(Vertex *self){
    self->next = NULL;
    self->data = destroy_base_value(self->data);
    me_free(self);
    return NULL;
}
Vertex *vt_get_next(Vertex *self){
    return self->next;
}

int vt_find_element(Vertex *self, BaseValue *data){

    int index = 0;
    while (self){
        if (bv_equals(self->data, data) ){
            return index;
        }
        index++;
        self = vt_get_next(self);
    }
    return -1;
}
void *vt_get_data(Vertex *self, int index){
    for (int i = 0; i < index; ++i) {
        self = vt_get_next(self);
    }
    return bv_get_data(self->data);
}
void vt_remove_element_lk(Vertex **self, int index){

    Vertex *aux = *self;
    Vertex *element_removed;
    if ( index == 0 ){
        element_removed = *self;
        *self = vt_get_next(*self);
        element_removed = destroy_vertex(element_removed);
        return;

    }
    for (int i = 0; i < index-1; ++i) {
        aux = vt_get_next(aux);
    }

    element_removed = vt_get_next(aux);
    aux->next = vt_get_next(aux->next);
    element_removed = destroy_vertex(element_removed);
}

Vertex *vt_add_element(Vertex *self, BaseValue *data, int index){

    void *self_cp = self;

    if ( index == 0 ){
        return create_vertex(data, self->next);
    }

    for (int i = 0; i < index-1; ++i) {
        self = vt_get_next(self);
    }
    self->next = create_vertex(data, self->next);
    return self_cp;
}

