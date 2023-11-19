//
// Created by vitor on 13/11/23.
//

#include "min_heap.h"
#include "../../../memory/memory.h"
#include "../../../generic_structs/list/list.h"
#include "../../flights_digraph/info_fligth.h"

typedef struct MinHeap{

    List *elements;
    int quantity_at;

}MinHeap;

MinHeap *create_min_heap(){

    MinHeap *new = me_memory_alloc(NULL, sizeof(MinHeap));
    *new = (MinHeap){
        .elements = create_list(),
        .quantity_at = 0
    };
    return new;
}
MinHeap *destroy_min_heap(MinHeap *self){

    self->elements = destroy_list(self->elements);
    self->quantity_at = 0;
    me_free(self);
    return NULL;
}
void _heapify_down(MinHeap *self, int index){

    int parent_index;
    int index_left_children;
    int index_rigth_children;

    InfoFligth *left_children;
    InfoFligth *rigth_children;
    InfoFligth *parent;
    int smallest = index;

    do{
        parent_index = smallest;
        index_left_children = 2*parent_index+1;
        index_rigth_children = 2*parent_index+2;

        left_children = li_get_element_in_list(self->elements, index_left_children);
        rigth_children = li_get_element_in_list(self->elements, index_rigth_children);
        parent = li_get_element_in_list(self->elements, parent_index);

        if ( left_children && if_bigger_then(parent, left_children) ){
            smallest = index_left_children;
        }
        if ( rigth_children && if_bigger_then(parent, rigth_children) ){
            smallest = index_rigth_children;
        }
        if ( smallest != parent_index ){
            li_swap_elements(self->elements, parent_index, smallest);
        }
    }while ( smallest != parent_index );
}

void _heapify_up(MinHeap *self, int index){
    int parent_index = 0;
    InfoFligth *value;
    InfoFligth *other_value;
    while ( index > 0 ){

        parent_index = (index -1)/2;
        value = li_get_element_in_list(self->elements, index);
        other_value = li_get_element_in_list(self->elements, parent_index);

        if ( if_less_then(value, other_value) ){

            li_swap_elements(self->elements, index, parent_index);
            index = parent_index;
        }else{
            break;
        }
    }

}

char *mh_str(MinHeap *self){
    InfoFligth *if_fligth = li_get_element_in_list(self->elements, 0);
    char *str = if_str(if_fligth);
    char *aux;
    char *string_if;
    for (int i = 1; i < self->quantity_at; i++){
        if_fligth = li_get_element_in_list(self->elements, i);
        aux = str;
        string_if = if_str(if_fligth);
        str = me_formatted_str("%s, %s", str, string_if);
        me_free(aux);
        me_free(string_if);
    }
    return str;
}
int mh_get_quantity_elements(MinHeap *self){
    return self->quantity_at;
}
int mh_is_void(MinHeap *self){
    return li_is_void(self->elements);
}

void mh_append_element(MinHeap *self, InfoFligth *new_element){

    BaseValue *bv = create_base_value(new_element, (void *) destroy_info_fligth, (void *)if_str, (void *)if_eq, if_get_tam());
    li_append(self->elements, bv);
    self->quantity_at++;
    _heapify_up(self, self->quantity_at-1);
}

InfoFligth *mh_extract_min(MinHeap *self){

    if ( self->quantity_at == 0 ){
        return NULL;
    }

    BaseValue *bv_min_value = li_remove_element(self->elements, 0);
    InfoFligth *min_value = bv_get_data(bv_min_value);
    bv_min_value = destroy_base_value(bv_min_value);
    self->quantity_at--;
    _heapify_down(self, 0);
    return min_value;
}
InfoFligth *mh_get_element(MinHeap *self, int index){
    if ( index >= self->quantity_at ){
        return NULL;
    }
    return if_create_cp(li_get_element_in_list(self->elements,index));
}
