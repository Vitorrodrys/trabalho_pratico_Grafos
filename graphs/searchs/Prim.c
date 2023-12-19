//
// Created by vitor on 05/12/23.
//

#include "Prim.h"

#include "../../memory/memory.h"

#include <float.h>

typedef struct Prim{

    int size_graph;
    double *edge_sizes;
    int *vertex_linked;
    int *parent;
    int *vertex_closeds;


}Prim;

Prim *create_prim(int size_graph, int origin){

    Prim *new_prim = me_memory_alloc(NULL, sizeof(Prim));

    new_prim->size_graph = size_graph;

    new_prim->edge_sizes = me_memory_alloc(NULL, sizeof(double)*size_graph);
    new_prim->vertex_linked = me_memory_alloc(NULL, sizeof(int)*size_graph);
    new_prim->parent = me_memory_alloc(NULL, sizeof(int)*size_graph);
    new_prim->vertex_closeds = me_memory_alloc(NULL, sizeof(int)*size_graph);

    for (int i = 0; i<size_graph; i++){

        new_prim->edge_sizes[i] = FLT_MAX;
        new_prim->vertex_linked[i] = 0;
        new_prim->parent[i] = -1;
        new_prim->vertex_closeds[i] = 0;

    }
    new_prim->edge_sizes[origin] = 0;
    new_prim->vertex_linked[origin] = 1;
    new_prim->parent[origin] = origin;
    return new_prim;

}

int prim_vertice_in_mst(Prim *self, int vertex){
    return self->vertex_linked[vertex] != -1;
}

int prim_this_edge_is_smallest(Prim *self, double edge, int vertex){

    return edge < self->edge_sizes[vertex];
}

void prim_swap_value_edge(Prim *self,int neighbor, int current_vertex, double edge){

    self->parent[neighbor] = current_vertex;
    self->vertex_linked[neighbor] = 1;
    self->edge_sizes[neighbor] = edge;
}

int prim_get_vertex_connect_with_smallest_edge(Prim *self){

    double smallest = FLT_MAX;
    int index_smallest = -1;

    for (int i = 0; i < self->size_graph; ++i) {
        if ( self->edge_sizes[i] < smallest && !self->vertex_closeds[i] ){
            index_smallest = i;
        }
    }
    self->vertex_closeds[index_smallest] =1;
    return index_smallest;
}

int prim_mst_is_complete(Prim *self){

    for (int i = 0; i < self->size_graph; ++i) {
        if ( self->vertex_linked[i] == 0 ){
            return 0;
        }
    }
    return 1;
}

Prim *destroy_prim(Prim *self){

    me_free_several_objects(3,&self->edge_sizes, &self->vertex_linked, &self->parent);
    me_free(self);
    return NULL;
}