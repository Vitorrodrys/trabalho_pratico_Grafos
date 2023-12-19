//
// Created by vitor on 09/11/23.
//

#include "flights_digraph.h"
#include "info_fligth.h"
#include "../../memory/memory.h"
#include "../matrix_operations/matrix_operations.h"
#include "list_arests/list_arests.h"
#include "../../string/string.h"



//functions that should be public only within this code

    //functions of the module of Dijkstra
    Dijkstra *create_dijkstra(int quantity_vertex, int which_vertex, int (*compare_less_fligth)(InfoFligth *self, InfoFligth*other));

//end




typedef struct FlightsDigraph{
    int size_graph;
    ListArests ***graph;
    int quantity_edge;
}FlightsDigraph;


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
            self->graph[i][j] = destroy_list_arest(self->graph[i][j]);
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
    self->graph = me_memory_alloc(self->graph, sizeof(ListArests **) * self->size_graph);
    self->graph[self->size_graph - 1] = NULL;
    for (int i = 0; i < self->size_graph-1; ++i) {
        self->graph[i] = me_memory_alloc(self->graph[i], sizeof(ListArests *) * self->size_graph);
        self->graph[i][self->size_graph - 1] = create_list_arest();
    }
    self->graph[self->size_graph-1] = me_memory_alloc(self->graph[self->size_graph-1], sizeof(ListArests*)*self->size_graph);
    for (int i = 0; i < self->size_graph; ++i) {

        self->graph[self->size_graph-1][i] = create_list_arest();
    }
}
void fldgp_del_vertex(FlightsDigraph *self, int vertex){

    for (int i = 0; i < self->size_graph; ++i) {
        if (i != vertex) {
            self->graph[i][vertex] = destroy_list_arest(self->graph[i][vertex]);
            self->graph[i] = mop_remove_a_vertex((void *) self->graph[i], vertex, self->size_graph);
            self->quantity_edge--;
        }
    }
    for (int i = 0; i < self->size_graph; ++i) {
        self->quantity_edge -= count_number_of_edges(self->graph[vertex], self->size_graph, sizeof(void *));
        self->graph[vertex][i] = destroy_list_arest(self->graph[vertex][i]);
    }
    me_free(self->graph[vertex]);
    self->graph = mop_remove_a_vertex((void *)self->graph, vertex, self->size_graph);
    self->size_graph--;

}
void fldgp_add_new_arest(FlightsDigraph *self, int from, int to, InfoFligth *value_arest){
    la_append(self->graph[from][to], value_arest);
    self->quantity_edge++;
}
void fldgp_remove_one_arest(FlightsDigraph *self, int from, int to){
    self->quantity_edge-= la_get_tam(self->graph[from][to]);
    self->graph[from][to] = destroy_list_arest(self->graph[from][to]);

}

int fldgp_get_quantity_flights(FlightsDigraph *self){
    return self->quantity_edge;
}
char *fldgp_str(FlightsDigraph *self){


    char *str_result = str_formatted("fligths by each region:\nquantity regions:%d\nquantity fligths:%d\nfligths:\n", self->size_graph, self->size_graph);
    char *aux;
    char *info_arest_str;
    for (int i = 0; i < self->size_graph; ++i) {

        info_arest_str = la_str(self->graph[i][0]);
        aux = str_result;
        str_result = str_formatted("%s\n| %s |", str_result, info_arest_str);
        me_free(aux);
        me_free(info_arest_str);
        for (int j = 1; j < self->size_graph-1; ++j) {

            info_arest_str = la_str(self->graph[i][j]);
            aux = str_result;
            str_result = str_formatted("%s %s |", str_result, info_arest_str);
            me_free(aux);
            me_free(info_arest_str);
        }
        info_arest_str = la_str(self->graph[i][self->size_graph-1]);
        aux = str_result;
        str_result = str_formatted("%s %s |\n", str_result, info_arest_str);
        me_free(aux);
        me_free(info_arest_str);
    }
    return str_result;
}




/*
 *
 *      this is within of the resolution of the 5.2
 * */
LinkedList *fldgp_get_direct_fligths_from(FlightsDigraph *self, int from){

    LinkedList *direct_fligths = create_linked_list();//list that contains other lists of vertex
    LinkedList *fligths_direct_to_vertex;//current list of vertex that stores the flights to current vertex
    InfoFligth *current_fligth;
    for (int i = 0; i < self->size_graph; ++i) {

        fligths_direct_to_vertex = create_linked_list();//create an instance of linked list to store a copy of the original list of edges

        for (int j = 0; j < la_get_tam(self->graph[from][i]); ++j) {

            //do a copy of each flight within of the original list of edges
            current_fligth = la_get_element(self->graph[from][i], j);
            lkl_append(
                    fligths_direct_to_vertex,
                    create_base_value(
                            if_create_cp(current_fligth),//create a copy of the edge for don't pass the same address of the edge in matrix
                            (void *)destroy_info_fligth,
                            (void *)if_str,
                            (void *)if_eq,
                            if_get_tam()
                            )
                    );
        }


        // Add the current list 'fligths_direct_to_vertex', which contains a copy of each flight within the last list of edges explored, to direct_flights.

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






/*
 *      this part was implemented operations related to dijkstra
 */

Dijkstra* generate_dijkstra(
    FlightsDigraph *self,
    int from_vertex,
    int (*if_is_less_then)(InfoFligth *arest_fligth, InfoFligth *other_arest_fligth),
    InfoFligth* (*la_find_less_arest)(ListArests *list_arest)
){

    Dijkstra *dj = create_dijkstra(self->size_graph, from_vertex, if_is_less_then);
    int current_less_vertex;
    InfoFligth *to_arest;
    while( dijkstra_there_are_open_vertex(dj) ){

        current_less_vertex = dijkstra_find_less_vertex(dj);
        dijkstra_close_this_vertex(dj, current_less_vertex);

        for (int to_vertex = 0; to_vertex < self->size_graph; ++to_vertex) {

            if ( to_vertex!=from_vertex && to_vertex!=current_less_vertex && la_get_tam(self->graph[current_less_vertex][to_vertex]) > 0 ){
                to_arest = la_find_less_arest(self->graph[current_less_vertex][to_vertex]);
                dijkstra_add_value_arest(dj, to_vertex, current_less_vertex, to_arest);
            }
        }

    }
    return dj;

}

Dijkstra *fldgp_dijkstra_find_less_distance(FlightsDigraph *self, int which_vertex){
    return generate_dijkstra(self, which_vertex, if_less_then_in_dist, la_find_less_element_in_dist);
}
Dijkstra *fldgp_dijkstra_find_less_duration(FlightsDigraph *self, int which_vertex){
    return generate_dijkstra(self, which_vertex, if_less_then_in_duration, la_find_less_element_in_duration);
}

InfoFligth *fldgp_get_one_flight(FlightsDigraph *self, int from, int to, int number_flight){
    return la_search_flight(self->graph[from][to], number_flight);
}


