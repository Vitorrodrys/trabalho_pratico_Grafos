//
// Created by vitor on 09/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_FLIGHTS_GRAPH_H
#define TRABALHO_PRATICO_GRAFOS_FLIGHTS_GRAPH_H
#include "../../parser_file/parser_file.h"
#include "info_fligth.h"


typedef struct Alias Alias;
typedef struct Regions Regions;



typedef struct FlightsGraph FlightsGraph;

FlightsGraph *create_flitghs_graph(Alias *alias_aeroports, Regions *aeroports, CurrentFile *file);
FlightsGraph *destrou_fligths_graph(FlightsGraph *self);
void flgp_add_new_vertex(FlightsGraph *self, char *name_alias);
void flgp_del_vertex(FlightsGraph *self, char *name_alias);
void flgp_add_new_arest(FlightsGraph *self, char *from, char *to, InfoFligth *value_arest);
int alias_get_quantity_alias(Alias *self);
#endif //TRABALHO_PRATICO_GRAFOS_FLIGHTS_GRAPH_H
