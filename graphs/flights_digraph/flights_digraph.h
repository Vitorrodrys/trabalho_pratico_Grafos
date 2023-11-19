//
// Created by vitor on 09/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_FLIGHTS_DIGRAPH_H
#define TRABALHO_PRATICO_GRAFOS_FLIGHTS_DIGRAPH_H
#include "../../parser_file/parser_file.h"
#include "info_fligth.h"
#include "../searchs/dijkstra.h"
#include "../../generic_structs/linked_list/linked_list.h"


typedef struct FlightsDigraph FlightsDigraph;

FlightsDigraph *create_flitghs_digraph();
FlightsDigraph *destroy_fligths_digraph(FlightsDigraph *self);
void fldgp_add_new_vertex(FlightsDigraph *self);
void fldgp_del_vertex(FlightsDigraph *self, int vertex);
void fldgp_add_new_arest(FlightsDigraph *self, int from, int to, InfoFligth *value_arest);
void fldgp_remove_one_arest(FlightsDigraph *self, int from, int to);
char *fldgp_str(FlightsDigraph *self);
LinkedList *fldgp_get_direct_fligths_from(FlightsDigraph *self, int from);
size_t lkl_get_size();
Dijkstra *fldgp_dijkstra_find_less_distance(FlightsDigraph *self, int which_vertex);
Dijkstra *fldgp_dijkstra_find_less_duration(FlightsDigraph *self, int which_vertex);
#endif //TRABALHO_PRATICO_GRAFOS_FLIGHTS_DIGRAPH_H
