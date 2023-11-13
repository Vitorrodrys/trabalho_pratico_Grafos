//
// Created by vitor on 11/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_GRAPH_AEROPORT_H
#define TRABALHO_PRATICO_GRAFOS_GRAPH_AEROPORT_H
#include "../parser_file/parser_file.h"
typedef struct Alias Alias;
typedef struct GraphAeroport GraphAeroport;
GraphAeroport *create_graph_aeroport(CurrentFile *file);
GraphAeroport *destroy_graph_aeroport(GraphAeroport *self);
void gpae_add_new_vertex(GraphAeroport *self, char *name_alias);
void gpae_remove_vertex(GraphAeroport *self, char *name_alias);
int gpae_add_new_rote(GraphAeroport *self, char *from, char *to);
int gpae_add_new_fligth(GraphAeroport *self, char *from, char *to, int number_stops, int number_fligth, char *departure_time, char *arrival_time);
int gpae_remove_route(GraphAeroport *self, char *from, char *to);
int gpae_remove_fligth(GraphAeroport *self, char *from, char *to);
char *gpae_str(GraphAeroport *self);
char *gpae_get_alls_fligths_from(GraphAeroport *self, char *name_alias);
char *gpae_get_route_from_to(GraphAeroport *self, char *alias_from, char *alias_to);
Alias *gpae_get_alias(GraphAeroport *self);

#endif //TRABALHO_PRATICO_GRAFOS_GRAPH_AEROPORT_H
