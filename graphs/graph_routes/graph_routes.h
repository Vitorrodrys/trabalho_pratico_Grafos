//
// Created by vitor on 08/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_GRAPH_ROUTES_H
#define TRABALHO_PRATICO_GRAFOS_GRAPH_ROUTES_H
#include "../../parser_file/parser_file.h"
#include "../regions/regions.h"
#include "../alias/alias.h"
#include "../searchs/repost_search.h"
typedef struct GraphRoutes GraphRoutes;
GraphRoutes *destroy_grt(GraphRoutes *self);
GraphRoutes *create_graph_routes();
void grt_create_vertex(GraphRoutes *self);
void grt_del_vertex(GraphRoutes *self, int index_delete);
void grt_add_edge(GraphRoutes *self, int from, int to, double dist);
void grt_remove_edge(GraphRoutes *self, int from, int to);
char* grt_str(GraphRoutes *self);
RespostSearch *grt_bfs(GraphRoutes *self, int from);
#endif //TRABALHO_PRATICO_GRAFOS_GRAPH_ROUTES_H
