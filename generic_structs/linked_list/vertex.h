//
// Created by vitor on 08/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_VERTEX_H
#define TRABALHO_PRATICO_GRAFOS_VERTEX_H

#include "../base_value/base_value.h"
typedef struct Vertex{
    BaseValue *data;
    struct Vertex *next;
}Vertex;
Vertex *create_vertex(BaseValue *data, Vertex *next);
Vertex *destroy_vertex(Vertex *self);
Vertex *vt_get_next(Vertex *self);
int vt_find_element(Vertex *self, BaseValue *data);
void *vt_get_data(Vertex *self, int index);
void vt_remove_element_lk(Vertex **self, int index);
Vertex *vt_add_element(Vertex *self, BaseValue *data, int index);

#endif //TRABALHO_PRATICO_GRAFOS_VERTEX_H
