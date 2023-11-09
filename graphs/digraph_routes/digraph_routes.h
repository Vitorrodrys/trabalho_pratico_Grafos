//
// Created by vitor on 08/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_DIGRAPH_ROUTES_H
#define TRABALHO_PRATICO_GRAFOS_DIGRAPH_ROUTES_H
#include "../../parser_file/parser_file.h"
#include "../../regions/regions.h"

typedef struct DigraphRoutes DigraphRoutes;


DigraphRoutes *create_graph_routes(current_file *file, Regions *aeroports);
void dgrt_create_vertex(DigraphRoutes *self, char *name_alias);
void dgrt_del_vertex(DigraphRoutes *self, char *name_alias);
void dgrt_add_edge(DigraphRoutes *self, char *from, char *to, Regions *aeroports);
void dgrt_remove_edge(DigraphRoutes *self, int from, int to);
#endif //TRABALHO_PRATICO_GRAFOS_DIGRAPH_ROUTES_H
