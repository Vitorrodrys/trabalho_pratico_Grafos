//
// Created by vitor on 08/11/23.
//

#include "digraph_routes.h"
#include "../../regions/regions.h"
#include "../alias/alias.h"
#include "../../memory/memory.h"
#include "../../parser_file/parser_file.h"
#include "../../list/list.h"

#include <math.h>
#include "../matrix_operations.h"

typedef struct DigraphRoutes{

    Alias *aeroports_alias;
    int next_id;
    int size_graph;
    int **graph;
    int quantity_edge;


}DigraphRoutes;


DigraphRoutes *create_graph_routes(current_file *file, Regions *aeroports){

    DigraphRoutes *new = me_memory_alloc(NULL, sizeof(DigraphRoutes));
    *new = (DigraphRoutes){
        .aeroports_alias = create_alias(),
        .next_id = 0,
        .graph = NULL,
        .size_graph = 0
    };

    pf_advance_to_word(file, "!routes");
    char *str = pf_get_word_until_token(file, '!');
    current_file *routes = create_parser_with_txt(str);
    pf_get_next_char(routes);
    pf_get_next_char(routes);
    char *sub_str;
    List *list_aux;
    char *from;
    char *to;
    while ( !pf_is_end_file(routes) ){

        sub_str = pf_get_word_until_token(routes, '\r');
        list_aux = li_break_str_in_list(sub_str, " ");

        from = li_get_element_in_list(list_aux,0);
        to = li_get_element_in_list(list_aux, 1);
        dgrt_create_vertex(new, from);
        dgrt_create_vertex(new, to);

        dgrt_add_edge(new, from, to, aeroports);

        destroy_list(list_aux, 2, NULL, NULL);
        pf_get_next_char(routes);
        pf_get_next_char(routes);


    }

    return new;
}

void dgrt_create_vertex(DigraphRoutes *self, char *name_alias){

    if (alias_get_number_by_alias(self->aeroports_alias, name_alias) != -1 ){
        //already exist alias
        return;
    }
    alias_add_alias(self->aeroports_alias,name_alias,self->next_id);
    self->next_id++;
    self->size_graph++;
    self->graph = me_memory_alloc(self->graph, sizeof(int *)*self->size_graph);
    self->graph[self->size_graph-1]=NULL;
    for (int i = 0; i < self->size_graph; ++i) {
        self->graph[i] = me_memory_alloc(self->graph[i], sizeof (int)*self->size_graph);
    }
    memset(self->graph[self->size_graph-1], 0, sizeof(int)*self->size_graph);

}

void dgrt_del_vertex(DigraphRoutes *self, char *name_alias){
    int index = alias_get_number_by_alias(self->aeroports_alias, name_alias);
    if ( index == -1 ){
        //vertex don't exist
        return;
    }

    alias_remove_alias(self->aeroports_alias, name_alias);

    int **temp_graph = mop_create_matrix(sizeof(int), self->size_graph-1);
    int i_or = 0;
    int j_or;
    for (int i = 0; i < self->size_graph; ++i) {
        j_or = 0;
        if (i != index) {

            for (int j = 0; j < self->size_graph; ++j) {

                if (j != index) {
                    temp_graph[i_or][j_or] = self->graph[i][j];
                    j_or++;
                }
            }
            i_or++;
        }
    }

    self->graph = mop_destroy_matrix((void **)self->graph, self->size_graph);
    self->graph = temp_graph;
    temp_graph = NULL;
    self->size_graph--;
}

int calc_dist(int x, int y, int x_l, int y_l){

    int x_calc = x-x_l;
    int y_calc = y-y_l;

    return (int)sqrt((double )(x_calc*x_calc+y_calc*y_calc));


}
void dgrt_add_edge(DigraphRoutes *self, char *from, char *to, Regions *aeroports){

    InfoAeroports *info = ifa_get_info_aeroport(aeroports, from);
    InfoAeroports *other_info = ifa_get_info_aeroport(aeroports, to);

    int dist = calc_dist(
            ifa_get_x_cord(info),
            ifa_get_y_cord(info),
            ifa_get_x_cord(other_info),
            ifa_get_y_cord(other_info)
    );

    int index_vertex = alias_get_number_by_alias(self->aeroports_alias, from);
    int index_other_vertex = alias_get_number_by_alias(self->aeroports_alias, to);

    self->graph[index_vertex][index_other_vertex] = dist;
    self->graph[index_other_vertex][index_vertex] = dist;
    self->quantity_edge++;

}

void dgrt_remove_edge(DigraphRoutes *self, int from, int to){

    self->graph[from][to] = 0;
    self->graph[to][from] = 0;
    self->quantity_edge--;
}
