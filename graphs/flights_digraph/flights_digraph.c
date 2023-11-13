//
// Created by vitor on 09/11/23.
//

#include "flights_digraph.h"
#include "../alias/alias.h"
#include "info_fligth.h"
#include "../../memory/memory.h"
#include "../regions/regions.h"
#include "../../generic_structs/list/list.h"
#include <stdio.h>
#include "../matrix_operations/matrix_operations.h"

double calc_dist(int x, int y, int x_l, int y_l);

typedef struct FlightsDigraph{
    int size_graph;
    InfoFligth ***graph;
    int quantity_edge;
}FlightsDigraph;

char *_get_str_info_fligth(InfoFligth *what){

    if ( what ){
        return if_str(what);
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
            if (self->graph[i][j])
                self->graph[i][j] = destroy_info_fligth(self->graph[i][j]);
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
    self->graph = me_memory_alloc(self->graph, sizeof(InfoFligth **) * self->size_graph);
    self->graph[self->size_graph - 1] = NULL;
    for (int i = 0; i < self->size_graph; ++i) {
        self->graph[i] = me_memory_alloc(self->graph[i], sizeof(InfoFligth *) * self->size_graph);
        self->graph[i][self->size_graph - 1] = NULL;
    }
    memset(self->graph[self->size_graph-1], 0, sizeof(InfoFligth *)*self->size_graph);
}
void fldgp_del_vertex(FlightsDigraph *self, int vertex){

    InfoFligth ***temp = mop_create_matrix(sizeof(InfoFligth *), self->size_graph-1);

    int i_temp = 0;
    int j_temp;
    for (int i = 0; i < self->size_graph; ++i) {
        if (i == vertex) {
            self->quantity_edge-= count_number_of_edges(self->graph[i], self->size_graph, sizeof(InfoFligth*));
            for (int j_r = 0; j_r < self->size_graph; ++j_r) {
                if (self->graph[i][j_r]) {
                    self->graph[i][j_r] = destroy_info_fligth(self->graph[i][j_r]);
                }
            }
            continue;
        }
        j_temp = 0;
        for (int j = 0; j <self->size_graph; ++j) {

            if(j==vertex) {
                self->quantity_edge--;
                if (self->graph[i][j]) {
                    self->graph[i][j] = destroy_info_fligth(self->graph[i][j]);
                }
                continue;
            }
            temp[i_temp][j_temp] = self->graph[i][j];
            j_temp++;
        }
        i_temp++;

    }
    self->size_graph--;
    self->graph = mop_destroy_matrix((void *)self->graph, self->size_graph);
    self->graph = temp;
}
void fldgp_add_new_arest(FlightsDigraph *self, int from, int to, InfoFligth *value_arest){
    self->graph[from][to] = value_arest;
    self->quantity_edge++;
}
void fldgp_remove_one_arest(FlightsDigraph *self, int from, int to){
    self->graph[from][to] = destroy_info_fligth(self->graph[from][to]);
    self->quantity_edge--;
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

    LinkedList *respost = create_linked_list();
    BaseValue *current_value;
    for (int i = 0; i < self->size_graph; ++i) {
        if (self->graph[from][i]) {
            current_value = create_base_value(
                    create_int(i),
                    (void *)destroy_int,
                    (void *)me_int_to_str,
                    (void *) me_eq_int,
                    sizeof(int)
                    );
            lkl_append(respost, current_value);

            current_value = create_base_value(
                    if_create_cp(self->graph[from][i]),
                    (void *)destroy_info_fligth,
                    (void *)if_str,
                    (void *)if_eq,
                    if_get_tam()
            );
            lkl_append(respost, current_value);
        }
    }
    return respost;

}


