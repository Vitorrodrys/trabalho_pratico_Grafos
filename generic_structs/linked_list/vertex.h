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
Vertex *destroy_vertex_without_destroy_value(Vertex *self);
Vertex *vt_get_next(Vertex *self);
int vt_find_element(Vertex *self, BaseValue *data);
void *vt_get_data(Vertex *self, int index);
void vt_remove_element_lk(Vertex **self, Vertex **last, int index, Vertex *(*destroyer)(Vertex *self));
Vertex *vt_add_element(Vertex *self, BaseValue *data, int index);
BaseValue *vt_get_base_value(Vertex *self);
int vt_eq(Vertex *self, Vertex *other);
char *vt_str(Vertex *self);
#endif //TRABALHO_PRATICO_GRAFOS_VERTEX_H
