//
// Created by vitor on 13/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_MIN_HEAP_H
#define TRABALHO_PRATICO_GRAFOS_MIN_HEAP_H
#include "../../flights_digraph/info_fligth.h"

typedef struct MinHeap MinHeap;

MinHeap *create_min_heap();
MinHeap *destroy_min_heap(MinHeap *self);
int mh_is_void(MinHeap *self);
char *mh_str(MinHeap *self);
InfoFligth *mh_get_element(MinHeap *self, int index);
int mh_get_quantity_elements(MinHeap *self);
void mh_append_element(MinHeap *self, InfoFligth *new_element);
InfoFligth *mh_extract_min(MinHeap *self);

#endif //TRABALHO_PRATICO_GRAFOS_MIN_HEAP_H
