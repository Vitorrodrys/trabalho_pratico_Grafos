//
// Created by vitor on 09/11/23.
//

#include "flights_digraph.h"
#include "info_fligth.h"
#include "../../memory/memory.h"
#include <stdio.h>
#include "../matrix_operations/matrix_operations.h"
#include "../searchs/min_heap/min_heap.h"

typedef struct FlightsDigraph{
    int size_graph;
    MinHeap ***graph;
    int quantity_edge;
}FlightsDigraph;

char *_get_str_info_fligth(MinHeap *what){

    if ( mh_get_quantity_elements(what) ){
        return mh_str(what);
    }
    return strdup(" don't has fligths! ");
}

FlightsDigraph *create_flitghs_digraph(){
    FlightsDigraph *new = me_memory_alloc(NULL, sizeof(FlightsDigraph));
    new->graph = NULL;
    new->size_graph= 0,
    new->quantity_edge = 0;
    return new;
}
FlightsDigraph *destroy_fligths_digraph(FlightsDigraph *self){

    for (int i = 0; i < self->size_graph; ++i) {
        for (int j = 0; j < self->size_graph; ++j) {
            self->graph[i][j] = destroy_min_heap(self->graph[i][j]);
        }
        me_free(self->graph[i]);
    }
    me_free(self->graph);
    memset(self, 0, sizeof(FlightsDigraph));
    me_free(self);
    return NULL;

}

void fldgp_add_new_vertex(FlightsDigraph *self){

    self->size_graph++;
    self->graph = me_memory_alloc(self->graph, sizeof(MinHeap **) * self->size_graph);
    self->graph[self->size_graph - 1] = NULL;
    for (int i = 0; i < self->size_graph-1; ++i) {
        self->graph[i] = me_memory_alloc(self->graph[i], sizeof(MinHeap *) * self->size_graph);
        self->graph[i][self->size_graph - 1] = create_min_heap();
    }
    self->graph[self->size_graph-1] = me_memory_alloc(self->graph[self->size_graph-1], sizeof(MinHeap*)*self->size_graph);
    for (int i = 0; i < self->size_graph; ++i) {

        self->graph[self->size_graph-1][i] = create_min_heap();
    }
}
void fldgp_del_vertex(FlightsDigraph *self, int vertex){

    for (int i = 0; i < self->size_graph; ++i) {
        if (i != vertex) {
            self->graph[i][vertex] = destroy_min_heap(self->graph[i][vertex]);
            self->graph[i] = mop_remove_a_vertex((void *) self->graph[i], vertex, self->size_graph);
            self->quantity_edge--;
        }
    }
    for (int i = 0; i < self->size_graph; ++i) {
        self->quantity_edge -= count_number_of_edges(self->graph[vertex], self->size_graph, sizeof(void *));
        self->graph[vertex][i] = destroy_min_heap(self->graph[vertex][i]);
    }
    me_free(self->graph[vertex]);
    self->graph = mop_remove_a_vertex((void *)self->graph, vertex, self->size_graph);
    self->size_graph--;

}
void fldgp_add_new_arest(FlightsDigraph *self, int from, int to, InfoFligth *value_arest){
    mh_append_element(self->graph[from][to], value_arest);
    self->quantity_edge++;
}
void fldgp_remove_one_arest(FlightsDigraph *self, int from, int to){
    self->quantity_edge-= mh_get_quantity_elements(self->graph[from][to]);
    self->graph[from][to] = destroy_min_heap(self->graph[from][to]);

}
char *fldgp_str(FlightsDigraph *self){


    char *str_result = me_formatted_str("fligths by each region:\nquantity regions:%d\nquantity fligths:%d\nfligths:\n", self->size_graph, self->size_graph);
    char *aux;
    char *info_arest_str;
    for (int i = 0; i < self->size_graph; ++i) {

        info_arest_str = _get_str_info_fligth(self->graph[i][0]);
        aux = str_result;
        str_result = me_formatted_str("%s\n| %s |", str_result, info_arest_str);
        me_free(aux);
        me_free(info_arest_str);
        for (int j = 1; j < self->size_graph-1; ++j) {

            info_arest_str = _get_str_info_fligth(self->graph[i][j]);
            aux = str_result;
            str_result = me_formatted_str("%s %s |", str_result, info_arest_str);
            me_free(aux);
            me_free(info_arest_str);
        }
        info_arest_str = _get_str_info_fligth(self->graph[i][self->size_graph-1]);
        aux = str_result;
        str_result = me_formatted_str("%s %s |\n", str_result, info_arest_str);
        me_free(aux);
        me_free(info_arest_str);
    }
    return str_result;
}

LinkedList *fldgp_get_direct_fligths_from(FlightsDigraph *self, int from){

    LinkedList *direct_fligths = create_linked_list();
    LinkedList *fligths_direct_to_vertex;
    InfoFligth *current_fligth;
    for (int i = 0; i < self->size_graph; ++i) {

        fligths_direct_to_vertex = create_linked_list();

        for (int j = 0; j < mh_get_quantity_elements(self->graph[from][i]); ++j) {

            current_fligth = mh_get_element(self->graph[from][i], j);
            lkl_append(
                    fligths_direct_to_vertex,
                    create_base_value(
                            current_fligth,
                            (void *)destroy_info_fligth,
                            (void *)if_str,
                            (void *)if_eq,
                            if_get_tam()
                            )
                    );
        }
        lkl_append(
                direct_fligths,
                create_base_value(
                        fligths_direct_to_vertex,
                        (void *)destroy_lkl,
                        NULL,
                        NULL,
                        lkl_get_size()
                        )
                );

    }
    return direct_fligths;
}

Dijkstra * generate_dijkstra(FlightsDigraph *self, int which_vertex, int (*if_compare_less)(InfoFligth *self, InfoFligth *other)){

    Dijkstra *dj = create_dijkstra(self->size_graph, which_vertex, if_compare_less);
    int less_vertex;
    InfoFligth *less_arest;
    while( dij_there_are_open_vertex(dj) ){

        less_vertex = dij_find_less_vertex(dj);
        dij_close_this_vertex(dj, less_vertex);

        for (int i = 0; i < self->size_graph; ++i) {

            if ( mh_get_quantity_elements(self->graph[less_vertex][i]) > 0 ){
                less_arest = mh_extract_min(self->graph[less_vertex][i]);
                dij_add_value_arest(dj, i, less_vertex, less_arest);
            }
        }

    }
    return dj;

}

Dijkstra *fldgp_dijkstra_find_less_distance(FlightsDigraph *self, int which_vertex){
    return generate_dijkstra(self, which_vertex, if_less_then_in_dist);
}
Dijkstra *fldgp_dijkstra_find_less_duration(FlightsDigraph *self, int which_vertex){
    return generate_dijkstra(self, which_vertex, if_less_then_in_duration);
}



