//
// Created by vitor on 05/12/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_PRIM_H
#define TRABALHO_PRATICO_GRAFOS_PRIM_H

typedef struct Prim Prim;

// Funções do TAD Prim
Prim *create_prim(int size_graph, int origin);
int prim_mst_is_complete(Prim *self);
Prim *destroy_prim(Prim *self);
int prim_vertice_in_mst(Prim *self, int vertex);
int prim_this_edge_is_smallest(Prim *self, double edge, int vertex);
void prim_swap_value_edge(Prim *self, int neighbor, int current_vertex, double edge);
int prim_get_vertex_connect_with_smallest_edge(Prim *self);

#endif //TRABALHO_PRATICO_GRAFOS_PRIM_H
