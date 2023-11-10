//
// Created by vitor on 10/11/23.
//

#include "colision_list.h"
#include "../../linked_list/linked_list.h"
#include "../../../memory/memory.h"
#include "../key_value/key_value.h"
typedef struct ColisionList{

    LinkedList *colision_list;


}ColisionList;

int _colist_find_index_element(ColisionList *self, char *key){
    KeyValue *aux = create_key_value(strdup(key), NULL);
    BaseValue *search_key = create_base_value(aux, (void *)destroy_kv, (void *)kv_str, (void *)kv_is_this_element, kv_get_tam());

    int index_element = lkl_get_index_element(self->colision_list, search_key);
    search_key = destroy_base_value(search_key);
    aux = NULL;//TODO check if really is clear
    return index_element;
}

ColisionList *create_colision_list(){

    ColisionList *new = me_memory_alloc(NULL, sizeof(ColisionList));
    new->colision_list = create_linked_list();
    return new;
}

ColisionList *destroy_colision_list(ColisionList *self){

    self->colision_list = destroy_lkl(self->colision_list);
    me_free_memory((void *)&self);
    return NULL;
}
void colist_append_colision(ColisionList *self, KeyValue *new_value){

    BaseValue *new_element_colision_list = create_base_value(
            new_value,
            (void *)destroy_kv,
            (void *)kv_str,
            (void *)kv_is_this_element,
            kv_get_tam()
            );
    lkl_append(self->colision_list,new_element_colision_list);
}
void colist_remove_key_value(ColisionList *self, char *key){

    int index_element = _colist_find_index_element(self, key);
    if ( index_element == -1 ){
        return;
    }
    lkl_rm_element(self->colision_list, index_element);

}
KeyValue *colist_get_key_value(ColisionList *self, char *key){

    int index_element = _colist_find_index_element(self, key);
    if (index_element == -1){
        return NULL;
    }
    return lkl_get_data(self->colision_list, index_element);
}

int colist_is_void(ColisionList *self){
    return lkl_is_void(self->colision_list);
}

KeyValue *colist_get_element_by_index(ColisionList *self, int index){
    return lkl_get_data(self->colision_list, index);
}