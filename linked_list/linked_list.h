//
// Created by vitor on 08/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_LINKED_LIST_H
#define TRABALHO_PRATICO_GRAFOS_LINKED_LIST_H
typedef struct LinkedList LinkedList;

LinkedList *create_linked_list();
int lkl_insert_element(LinkedList *self, void *data, int index);
void *lkl_rm_element(LinkedList *self, int index);
void *lkl_get_data(LinkedList *self, int index);
void lkl_append(LinkedList *self, void *data);
void* lkl_set_element(LinkedList *self, int index, void *value);
int lkl_is_void(LinkedList *self);
int lkl_get_index_element(LinkedList *self, void *data, int (*eq)(void *, void *));
int lkl_get_tam(LinkedList *self);
#endif //TRABALHO_PRATICO_GRAFOS_LINKED_LIST_H
