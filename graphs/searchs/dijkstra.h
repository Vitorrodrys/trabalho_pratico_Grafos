//
// Created by vitor on 13/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_DIJKSTRA_H
#define TRABALHO_PRATICO_GRAFOS_DIJKSTRA_H

#include "../flights_digraph/info_fligth.h"

typedef struct Dijkstra Dijkstra;

Dijkstra *create_dijkstra(int quantity_vertex, int which_vertex, int (*compare_less_fligth)(InfoFligth *self, InfoFligth*other));
int dij_find_less_vertex(Dijkstra *self);
int dij_there_are_open_vertex(Dijkstra *self);
void dij_close_this_vertex(Dijkstra *self, int vertex);
void dij_add_value_arest(Dijkstra *self, int which_vertex, int pass_by,InfoFligth *value_arest);
#endif //TRABALHO_PRATICO_GRAFOS_DIJKSTRA_H
