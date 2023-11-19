//
// Created by vitor on 10/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_COLISION_LIST_H
#define TRABALHO_PRATICO_GRAFOS_COLISION_LIST_H
#include "../../base_value/base_value.h"
#include "../key_value/key_value.h"


typedef struct ColisionList ColisionList;
typedef struct LinkedList LinkedList; //TODO check if I really want don't show the implementation details of LinkedList

// create a list of colision
ColisionList *create_colision_list();

// destroy the list of the colision
ColisionList *destroy_colision_list(ColisionList *self);

// append a element in list of colision
void colist_append_colision(ColisionList *self, KeyValue *new_value);

// remove a element of the list with base a key
void colist_remove_key_value(ColisionList *self, char *key);

//get a element of the colisionlist with base in a key
KeyValue *colist_get_key_value(ColisionList *self, const char *key);

//check if the list of the colision is void, return 1 case yes, 0 if don't
int colist_is_void(ColisionList *self);

KeyValue *colist_get_element_by_index(ColisionList *self, int index);
#endif //TRABALHO_PRATICO_GRAFOS_COLISION_LIST_H
