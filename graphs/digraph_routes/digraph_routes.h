//
// Created by vitor on 08/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_DIGRAPH_ROUTES_H
#define TRABALHO_PRATICO_GRAFOS_DIGRAPH_ROUTES_H
#include "../../parser_file/parser_file.h"
#include "../regions/regions.h"
#include "../alias/alias.h"
typedef struct DigraphRoutes DigraphRoutes;
DigraphRoutes *destroy_dgrt(DigraphRoutes *self);
DigraphRoutes *create_graph_routes(Alias *alias_aeroports, Regions *aeroports, CurrentFile *file);
void dgrt_create_vertex(DigraphRoutes *self, char *name_alias);
void dgrt_del_vertex(DigraphRoutes *self, char *name_alias);
void dgrt_add_edge(DigraphRoutes *self, char *from, char *to, Regions *aeroports);
void dgrt_remove_edge(DigraphRoutes *self, int from, int to);
char* dgrt_str(DigraphRoutes *self);
#endif //TRABALHO_PRATICO_GRAFOS_DIGRAPH_ROUTES_H
