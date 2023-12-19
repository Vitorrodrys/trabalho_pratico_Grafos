//
// Created by vitor on 08/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_LINKED_LIST_H
#define TRABALHO_PRATICO_GRAFOS_LINKED_LIST_H
#include "../base_value/base_value.h"

typedef struct LinkedList LinkedList;


size_t lkl_get_size();
LinkedList *create_linked_list();
LinkedList *destroy_lkl(LinkedList *self);
int lkl_insert_element(LinkedList *self, BaseValue *data, int index);
void lkl_rm_element(LinkedList *self, int index);
void *lkl_get_data(LinkedList *self, int index);
void lkl_append(LinkedList *self, BaseValue *data);
void lkl_set_element(LinkedList *self, int index, BaseValue *value);
int lkl_is_void(LinkedList *self);
int lkl_get_index_element(LinkedList *self, BaseValue *data);
int lkl_get_tam(LinkedList *self);
BaseValue *lkl_pop(LinkedList *self);
LinkedList *lkl_concat_lists(LinkedList *self, LinkedList *other);
int lkl_eq(LinkedList *self, LinkedList *other);
char *lkl_str(LinkedList *self);
#endif //TRABALHO_PRATICO_GRAFOS_LINKED_LIST_H
