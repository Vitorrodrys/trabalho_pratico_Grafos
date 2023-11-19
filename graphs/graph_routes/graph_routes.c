//
// Created by vitor on 08/11/23.
//

#include "graph_routes.h"
#include "../regions/regions.h"
#include "../alias/alias.h"
#include "../../memory/memory.h"
#include "../../parser_file/parser_file.h"
#include "../../generic_structs/list/list.h"
#include <stdio.h>
#include "../matrix_operations/matrix_operations.h"

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

RespostSearch *grt_bfs(GraphRoutes *self, int from){

    if ( from >= self->size_graph ){
        return NULL;
    }
    RespostSearch *respost = create_respost(self->size_graph, from);

    while ( !res_queue_is_void(respost) ){

        from = res_get_next_vertex_queue(respost);

        for (int i = 0; i < self->size_graph; ++i) {
            if ( !self->graph[from][i] ){
                continue;
            }

            if (res_elem_still_not_visited(respost, i) ){
                res_to_visite_element(respost, from, i, self->graph[from][i]);
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
    RespostSearch *bfs_respost = grt_bfs(self, from);
    BaseValue *current_element_in_list;
    LinkedList *vertex_that_not_has_way = create_linked_list();
    for (int i = 0; i < self->size_graph; ++i) {

        if ( i != from ){
            if ( !res_exist_a_way_to_vertex(bfs_respost, i) ){

                current_element_in_list = create_base_value(
                        create_int(i),
                        (void *)destroy_int,
                        (void *)me_int_to_str,
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
LinkedList *grt_get_vertex_that_not_has_way_if_a_vertex_not_exist(GraphRoutes *self, int from, int vertex_that_not_exist){

    if (from > self->size_graph){
        return NULL;
    }
    RespostSearch *bfs_respost = grt_bfs(self, from);
    BaseValue *current_element_in_list;
    LinkedList *vertex_that_not_has_way = create_linked_list();
    for (int i = 0; i < self->size_graph; ++i) {

        if ( i != from ){
            //if before after a path and retired the vertex not has more path, then this is a vertex
            //that is affected by the retired of vertex
            if (
                    res_exist_a_way_to_vertex(bfs_respost, i) &&
                    res_check_if_middle_path_contains_vertex(bfs_respost, vertex_that_not_exist,i)
                    ){

                current_element_in_list = create_base_value(
                        create_int(i),
                        (void *)destroy_int,
                        (void *)me_int_to_str,
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
