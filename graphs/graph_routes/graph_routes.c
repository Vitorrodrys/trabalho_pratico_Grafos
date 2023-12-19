//
// Created by vitor on 08/11/23.
//

#include "graph_routes.h"
#include "../../memory/memory.h"
#include "../../string/string.h"
#include "../matrix_operations/matrix_operations.h"
#include "../searchs/respost_dfs.h"
#include "../searchs/color.h"

//functions that only should be public by graph_routes

    //DFS functions that only should be public by graph_routes
    /**
     * create a instance of RespostSearchDFS
     * @param which_vertex the vertex that the search will starts
     * @param quantity_vertex_graph the quantity of vertex in a graph
     * @param ignored_vertex: a vertex that should be ignored by the search, pass NOT_IGNORE_ANY_VERTICES to ignore no vertices
     * @return a new instance of RespostSearchDFS
     */
    RespostSearchDFS *create_respost_dfs(int which_vertex, int quantity_vertex_graph, int ignored_vertex);


//end


typedef struct GraphRoutes{

    int size_graph;
    double **graph;
    int quantity_edge;

}GraphRoutes;



GraphRoutes *create_graph_routes(){

    GraphRoutes *new = me_memory_alloc(NULL, sizeof(GraphRoutes));
    *new = (GraphRoutes){
        .graph = NULL,
        .size_graph = 0,
        .quantity_edge=0
    };
    return new;
}

GraphRoutes *destroy_grt(GraphRoutes *self){

    self->graph = mop_destroy_matrix((void **)self->graph, self->size_graph);
    self->quantity_edge = 0;
    self->size_graph = 0;
    me_free(self);
    return NULL;
}

void grt_create_vertex(GraphRoutes *self){
    self->size_graph++;
    self->graph = me_memory_alloc(self->graph, sizeof(double *)*self->size_graph);
    self->graph[self->size_graph-1]=NULL;
    for (int i = 0; i < self->size_graph; ++i) {
        self->graph[i] = me_memory_alloc(self->graph[i], sizeof (double)*self->size_graph);
        self->graph[i][self->size_graph-1] = 0.0;
    }
    memset(self->graph[self->size_graph-1], 0, sizeof(double)*self->size_graph);

}

void grt_del_vertex(GraphRoutes *self, int index_delete){
    double **temp_graph = mop_create_matrix(sizeof(double), self->size_graph-1);
    int i_tmp = 0;
    int j_tmp;
    for (int i = 0; i < self->size_graph; ++i) {
        j_tmp = 0;
        if ( i == index_delete){
            self->quantity_edge -= count_number_of_edges(self->graph[i], self->size_graph,sizeof(double));
            continue;
        }
        for (int j = 0; j < self->size_graph; ++j) {
            if (j == index_delete) {
                self->quantity_edge--;
                continue;
            }else{
                temp_graph[i_tmp][j_tmp] = self->graph[i][j];
                j_tmp++;
            }
        }
        i_tmp++;
    }

    self->graph = mop_destroy_matrix((void **)self->graph, self->size_graph);
    self->graph = temp_graph;
    temp_graph = NULL;
    self->size_graph--;
}
void grt_add_edge(GraphRoutes *self, int to, int from, double dist){
    self->graph[from][to] = dist;
    self->graph[to][from] = dist;
    self->quantity_edge++;
}

void grt_remove_edge(GraphRoutes *self, int from, int to){

    self->graph[from][to] = 0;
    self->graph[to][from] = 0;
    self->quantity_edge--;
}
int grt_exist_this_edge(GraphRoutes *self, int from, int to){
    return (int)self->graph[from][to];
}
char* grt_str(GraphRoutes *self){
    return mop_str_matrix_int(self->graph, self->size_graph);
}

RespostSearchBFS *grt_bfs(GraphRoutes *self, int from){

    if ( from >= self->size_graph ){
        return NULL;
    }
    RespostSearchBFS *respost = create_respost(self->size_graph, from);

    while ( !resbfs_queue_is_void(respost) ){

        from = resbfs_get_next_vertex_queue(respost);

        for (int i = 0; i < self->size_graph; ++i) {
            if ( !self->graph[from][i] ){
                continue;
            }

            if (resbfs_elem_still_not_visited(respost, i) ){
                resbfs_to_visite_element(respost, from, i, self->graph[from][i]);
            }
        }
    }
    return respost;

}

double grt_get_dist_betwen_aeroports(GraphRoutes *self, int from, int to){
    return self->graph[from][to];
}

LinkedList *grt_get_vertex_that_not_has_way(GraphRoutes *self, int from){

    if (from > self->size_graph){
        return NULL;
    }
    RespostSearchBFS *bfs_respost = grt_bfs(self, from);
    BaseValue *current_element_in_list;
    LinkedList *vertex_that_not_has_way = create_linked_list();
    for (int i = 0; i < self->size_graph; ++i) {

        if ( i != from ){
            if ( !resbfs_exist_a_way_to_vertex(bfs_respost, i) ){

                current_element_in_list = create_base_value(
                        create_int(i),
                        (void *)destroy_int,
                        (void *) me_int_to_str,
                        (void *)me_eq_int,
                        sizeof(int)
                        );
                lkl_append(vertex_that_not_has_way, current_element_in_list);
            }
        }
    }
    bfs_respost = destroy_respost(bfs_respost);
    return vertex_that_not_has_way;
}

RespostSearchDFS *grt_dfs(GraphRoutes *self, int from, int ignored_vertex) {


    RespostSearchDFS *dfs_search = create_respost_dfs(from, self->size_graph, ignored_vertex);

    int current_vertex;
    int before_current_vertex = -1;
    int i;
    while (!resdfs_stack_is_void(dfs_search)) {
        current_vertex = resdfs_get_last_vertex_stack(dfs_search);

        for (i = before_current_vertex + 1; i < self->size_graph; ++i) {

            if (self->graph[current_vertex][i] && !resdfs_exist_element_in_stack(dfs_search, i) && !resdfs_element_already_visited(dfs_search, i)) {
                resdfs_to_visite_vertex(dfs_search, i, current_vertex, self->graph[current_vertex][i]);
                before_current_vertex = -1;
                break;
            }

        }
        if (i >= self->size_graph)
            before_current_vertex = resdfs_pop_vertex(dfs_search);

    }
    return dfs_search;
}

/**
 * question corresponding the practice of coloring
 * @param self
 * @return Colors of filled in graph
 */
DistColors *grt_coloring(GraphRoutes *self){

    DistColors *dist_colors = create_dist_colors(self->size_graph);

    int color_that_will_use = 0;

    int *disponible_colors = NULL;
    for (int i = 0; i < self->size_graph; ++i) {
        color_that_will_use = 0;
        disponible_colors = dc_create_vector_of_avaible_colors(dist_colors);

        for (int j = 0; j < self->size_graph; ++j) {
            if ( self->graph[i][j] && dc_get_color_vertex(dist_colors, j) != -1 ){
               disponible_colors[dc_get_color_vertex(dist_colors, j)] = 0;
            }
        }
        while ( color_that_will_use < dc_get_quantity_colors_usage(dist_colors) && !disponible_colors[color_that_will_use] ){
            color_that_will_use++;
        }

        dc_set_color_vertex(dist_colors, i, color_that_will_use);
        me_free(disponible_colors);

    }
    return dist_colors;
}

Prim* grt_prim(GraphRoutes *self){

    Prim *prim = create_prim(self->size_graph, 0);

    int current_vertex;
    while ( !prim_mst_is_complete(prim) ){

        current_vertex = prim_get_vertex_connect_with_smallest_edge(prim);
        for (int i = 0; i < self->size_graph; ++i) {

            if ( self->graph[current_vertex][i] && prim_vertice_in_mst(prim, i) && prim_this_edge_is_smallest(prim, self->graph[current_vertex][i], i) ){
                prim_swap_value_edge(prim, i, current_vertex, self->graph[current_vertex][i]);

            }
        }

    }
    return prim;



}

int grt_get_tam(GraphRoutes *self){
    return self->size_graph;
}