//
// Created by vitor on 08/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_GRAPH_ROUTES_H
#define TRABALHO_PRATICO_GRAFOS_GRAPH_ROUTES_H
#include "../../parser_file/parser_file.h"
#include "../regions/regions.h"
#include "../alias/alias.h"
#include "../searchs/respost_bfs.h"
#include "../searchs/respost_dfs.h"
#include "../searchs/color.h"
#include "../searchs/Prim.h"
typedef struct GraphRoutes GraphRoutes;
GraphRoutes *destroy_grt(GraphRoutes *self);
GraphRoutes *create_graph_routes();
void grt_create_vertex(GraphRoutes *self);
void grt_del_vertex(GraphRoutes *self, int index_delete);
void grt_add_edge(GraphRoutes *self, int from, int to, double dist);
void grt_remove_edge(GraphRoutes *self, int from, int to);
char* grt_str(GraphRoutes *self);
RespostSearchBFS *grt_bfs(GraphRoutes *self, int from);
double grt_get_dist_betwen_aeroports(GraphRoutes *self, int from, int to);
int grt_exist_this_edge(GraphRoutes *self, int from, int to);
DistColors *grt_coloring(GraphRoutes *self);
LinkedList *grt_get_vertex_that_not_has_way(GraphRoutes *self, int from);
RespostSearchDFS *grt_dfs(GraphRoutes *self, int from, int ignored_vertex);
Prim* grt_prim(GraphRoutes *self);
int grt_get_tam(GraphRoutes *self);
#endif //TRABALHO_PRATICO_GRAFOS_GRAPH_ROUTES_H
