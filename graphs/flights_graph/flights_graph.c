//
// Created by vitor on 09/11/23.
//

#include "flights_graph.h"
#include "../alias/alias.h"
#include "info_fligth.h"
#include "../../memory/memory.h"
#include "../regions/regions.h"
#include "../../generic_structs/list/list.h"
#include <stdio.h>
#include "../matrix_operations.h"

double calc_dist(int x, int y, int x_l, int y_l);

typedef struct FlightsGraph{
    Alias *aeroports_alias;
    int size_graph;
    InfoFligth ***graph;
    int quantity_edge;
}FlightsGraph;

FlightsGraph *create_flitghs_graph(Alias *alias_aeroports, Regions *aeroports, CurrentFile *file){
    FlightsGraph *new = me_memory_alloc(NULL, sizeof(FlightsGraph));
    new->graph = mop_create_matrix(sizeof(InfoFligth *), alias_get_quantity_alias(alias_aeroports));
    new->size_graph= alias_get_quantity_alias(alias_aeroports),
    new->quantity_edge = 0;
    new->aeroports_alias = alias_aeroports;

    pf_advance_to_word(file, "!fligths");
    pf_get_next_char(file);
    pf_get_next_char(file);
    char *str = NULL;
    InfoFligth *arest = NULL;
    char *from = NULL;
    char *to = NULL;
    InfoAeroports *from_aeroport = NULL;
    InfoAeroports *to_aeroport = NULL;
    List *list_args = NULL;

    while (!pf_is_end_file(file)){
        str = pf_get_word_until_token(file, '\n');
        list_args = li_break_str_in_list(str, " ");
        from = li_get_element_in_list(list_args,2);
        to = li_get_element_in_list(list_args, 4);

        from_aeroport = ifa_get_info_aeroport(aeroports, from);
        to_aeroport = ifa_get_info_aeroport(aeroports, to);
        arest = create_info_fligth(
                atoi(li_get_element_in_list(list_args,0)),
                calc_dist(
                        ifa_get_y_cord(from_aeroport),
                        ifa_get_x_cord(from_aeroport),
                        ifa_get_y_cord(to_aeroport),
                        ifa_get_x_cord(to_aeroport)
                        ),
                atoi(li_get_element_in_list(list_args, 6)),
                li_get_element_in_list(list_args, 3),
                li_get_element_in_list(list_args, 5)
        );

        flgp_add_new_vertex(new, from);
        flgp_add_new_vertex(new, to);
        flgp_add_new_arest(new, from, to, arest);

        list_args = destroy_list(list_args);

        pf_get_next_char(file);



    }
    return new;
}
FlightsGraph *destroy_fligths_graph(FlightsGraph *self){

    for (int i = 0; i < self->size_graph; ++i) {
        for (int j = 0; j < self->size_graph; ++j) {
            self->graph[i][j] = destroy_info_fligth(self->graph[i][j]);
        }
        me_free(self->graph[i]);
    }
    me_free(self->graph);
    memset(self, 0, sizeof(FlightsGraph));
    me_free(self);
    return NULL;

}

void flgp_add_new_vertex(FlightsGraph *self, char *name_alias){

    int vertex = alias_get_number_by_alias(self->aeroports_alias, name_alias);

    if ( vertex == -1 ) {
        alias_add_alias(self->aeroports_alias, name_alias);

        self->size_graph++;
        self->graph = me_memory_alloc(self->graph, sizeof(InfoFligth **) * self->size_graph);
        self->graph[self->size_graph - 1] = NULL;
        for (int i = 0; i < self->size_graph; ++i) {
            self->graph[i] = me_memory_alloc(self->graph[i], sizeof(InfoFligth *) * self->size_graph);
            self->graph[self->size_graph - 1] = NULL;
        }
    }
}
void flgp_del_vertex(FlightsGraph *self, char *name_alias){

    int vertex = alias_get_number_by_alias(self->aeroports_alias, name_alias);
    if ( vertex == -1 ){
        fprintf(stderr, "don't find number by alias %s\n", name_alias);
        exit(1);
    }

    InfoFligth ***temp = mop_create_matrix(sizeof(InfoFligth *), self->size_graph-1);

    int i_temp;
    int j_temp;
    for (int i = 0; i < self->size_graph; ++i) {
        i_temp = 0;
        if (i != vertex) {
            for (int j = 0; j <self->size_graph; ++j) {
                j_temp = 0;
                if(j!=vertex){
                    temp[i_temp][j_temp] = self->graph[i][j];
                    j_temp++;
                }else{
                    self->quantity_edge--;
                    self->graph[i][j] = destroy_info_fligth(self->graph[i][j]);
                }
            }
            i_temp++;
        }else{
            self->quantity_edge-= count_number_of_edges(self->graph[i], self->size_graph, sizeof(InfoFligth*));
            for (int j_r = 0; j_r < self->size_graph; ++j_r) {
                self->graph[i][j_r] = destroy_info_fligth(self->graph[i][j_r]);
            }
        }
    }
    self->size_graph--;
    self->graph = mop_destroy_matrix((void *)self->graph, self->size_graph);
    self->graph = temp;
}
void flgp_add_new_arest(FlightsGraph *self, char *from, char *to, InfoFligth *value_arest){

    int from_index = alias_get_number_by_alias(self->aeroports_alias, from );
    int to_index = alias_get_number_by_alias(self->aeroports_alias ,to);

    if ( from_index == -1 || to_index == -1){
        fprintf(stderr, "arest with value -1, in other words, don't was find a value by alias in hash map, from:{%s:%d}, to:{%s:%d}", from, from_index, to, to_index);
        exit(1);
    }
    self->graph[from_index][to_index] = value_arest;
    self->quantity_edge++;
}
void flgp_remove_one_arest(FlightsGraph *self, char *from, char *to){

    int vertex_from = alias_get_number_by_alias(self->aeroports_alias, from);
    int vertex_to = alias_get_number_by_alias(self->aeroports_alias, to);

    if ( vertex_to || vertex_from ){
        return;
    }
    self->graph[vertex_from][vertex_to] = destroy_info_fligth(self->graph[vertex_from][vertex_to]);
    self->quantity_edge--;
}
char *flgp_str(FlightsGraph *self){

    char *aep_alias_str = alias_str(self->aeroports_alias);


}