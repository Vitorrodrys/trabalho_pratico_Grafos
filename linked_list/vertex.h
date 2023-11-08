//
// Created by vitor on 08/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_VERTEX_H
#define TRABALHO_PRATICO_GRAFOS_VERTEX_H


typedef struct Vertex{
    void *data;
    struct Vertex *next;
}Vertex;
Vertex *create_vertex(void *data, Vertex *next);
Vertex *destroy_vertex(Vertex *self);
Vertex *vt_get_next(Vertex *self);
int vt_find_element(Vertex *self, void *data, int (*eq)(void *, void *));
void *vt_get_data(Vertex *self, int index);
void *vt_remove_element_lk(Vertex **self, int index);
Vertex *vt_add_element(Vertex *self, void *data, int index);

#endif //TRABALHO_PRATICO_GRAFOS_VERTEX_H
