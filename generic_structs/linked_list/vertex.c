//
// Created by vitor on 08/11/23.
//

#include "vertex.h"
#include "../../memory/memory.h"
#include "../../string/string.h"

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
Vertex *destroy_vertex_without_destroy_value(Vertex *self){
    self->next = NULL;
    self->data = NULL;
    me_free(self);
    return NULL;
}
Vertex *vt_get_next(Vertex *self){
    return self->next;
}

BaseValue *vt_get_base_value(Vertex *self){
    return self->data;
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
BaseValue *_get_bv(Vertex *self, int index){
    for (int i = 0; i < index; ++i) {
        self = vt_get_next(self);
    }
    return self->data;
}
void *vt_get_data(Vertex *self, int index){
    return bv_get_data(_get_bv(self, index));
}
void vt_remove_element_lk(Vertex **self, Vertex **last,int index, Vertex *(*destroyer)(Vertex *self)){

    Vertex *aux = *self;
    Vertex *element_removed;
    if ( index == 0 ){
        element_removed = *self;
        *self = vt_get_next(*self);
        element_removed = destroyer(element_removed);
        return;

    }
    for (int i = 0; i < index-1; ++i) {
        aux = vt_get_next(aux);
    }

    element_removed = vt_get_next(aux);
    if ( element_removed == *last ){
        *last = aux;
    }
    aux->next = vt_get_next(aux->next);
    element_removed = destroyer(element_removed);
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
int vt_eq(Vertex *self, Vertex *other){

    BaseValue *current_self;
    BaseValue *current_other;

    while (self != NULL){
        current_self = self->data;
        current_other = other->data;

        if ( !bv_equals(current_self, current_other) ){
            return 0;
        }
        self = vt_get_next(self);
        other = vt_get_next(other);

    }
    if ( self != other ){
        //if self and other don't was equals to NULL, then the lists are of size differents
        return 0;
    }
    return 1;
}

char *vt_str(Vertex *self){

    char *bv_str = bv_in_str(self->data);
    char *string = str_formatted("[ %s", bv_str);
    char *aux;
    me_free(bv_str);
    self = vt_get_next(self);
    if ( self == NULL ){
        aux = string;
        string = str_formatted("%s ]", string);
        me_free(aux);
        return string;
    }
    while ( self->next ){

        bv_str = bv_in_str(self->data);
        aux = string;
        string = str_formatted("%s, %s", string, bv_str);
        me_free_several_objects(2, &bv_str, &aux);
        self = vt_get_next(self);
    }
    bv_str = bv_in_str(self->data);
    aux = string;
    string = str_formatted("%s, %s ]", string, bv_str);
    me_free_several_objects(2, &bv_str, &aux);
    return string;
}
