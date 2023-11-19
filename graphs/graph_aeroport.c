//
// Created by vitor on 11/11/23.
//

#include "graph_aeroport.h"
#include "../memory/memory.h"
#include "graph_routes//graph_routes.h"
#include "flights_digraph/flights_digraph.h"
#include "../generic_structs/list/list.h"
#include <math.h>

double calc_dist(int x, int y, int x_l, int y_l){

    int x_calc = x-x_l;
    int y_calc = y-y_l;

    return sqrt((double )(x_calc*x_calc+y_calc*y_calc));
}

typedef struct GraphAeroport{
    FlightsDigraph *fligths;
    GraphRoutes *routes;
    Alias *alias_aeroports;
    Regions *regions;
}GraphAeroport;


Alias *gpae_get_alias(GraphAeroport *self){
    return self->alias_aeroports;
}

void discovery_from_and_to_vertex(GraphAeroport *self, char *from, char *to, int *from_vertex, int *to_vertex){
    *from_vertex = alias_get_number_by_alias(self->alias_aeroports, from);
    *to_vertex = alias_get_number_by_alias(self->alias_aeroports, to);
}

void _generate_searchs(GraphAeroport *self){

    KeyValue *current_aeroport;
    ItHash *iterator = re_create_iterator_regions(self->regions);
    RespostSearch *respost_bfs;
    current_aeroport = ith_next(iterator);
    int from;
    while (current_aeroport){
        from = alias_get_number_by_alias(self->alias_aeroports, kv_get_key(current_aeroport));
        respost_bfs = grt_bfs(self->routes, from);
        ifa_set_bfs(kv_get_value(current_aeroport), respost_bfs);
        current_aeroport = ith_next(iterator);
    }
    iterator = destructor_iterator(iterator);
}

void _read_fligth_graph(GraphAeroport *self, CurrentFile *file){

    pf_advance_to_word(file, "!fligths");
    pf_get_next_char(file);
    pf_get_next_char(file);
    char *str = NULL;
    char *from = NULL;
    char *to = NULL;
    List *list_args = NULL;

    while (!pf_is_end_file(file)){
        str = pf_get_word_until_token(file, '\n');
        list_args = li_break_str_in_list(str, " ");
        from = li_get_element_in_list(list_args,2);
        to = li_get_element_in_list(list_args, 4);

        gpae_add_new_vertex(self, from);
        gpae_add_new_vertex(self, to);

        if (!strcmp(to, "ABQ") && !strcmp(from, "MSY") ){
#include <stdio.h>

            printf("oi");
        }

        gpae_add_new_fligth(
                self,
                from,
                to,
                atoi(li_get_element_in_list(list_args, 6)),
                atoi(li_get_element_in_list(list_args,1)),
                li_get_element_in_list(list_args, 3),
                li_get_element_in_list(list_args, 5)
        );

        list_args = destroy_list(list_args);
        pf_get_next_char(file);
        me_free(str);
    }
}

void _read_routes_graph(GraphAeroport *self, CurrentFile *file){

    pf_advance_to_word(file, "!routes");
    char *str = pf_get_word_until_token(file, '!');
    CurrentFile *routes = create_parser_with_txt(str);
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
        gpae_add_new_vertex(self, from);
        gpae_add_new_vertex(self, to);
        gpae_add_new_rote(self, from, to);
        list_aux = destroy_list(list_aux);
        pf_get_next_char(routes);
        pf_get_next_char(routes);


    }
    routes = destroy_parser(routes);

}


GraphAeroport *create_graph_aeroport(CurrentFile *file){

    GraphAeroport *new = me_memory_alloc(NULL, sizeof(GraphAeroport));
    *new = (GraphAeroport){
        .regions = create_regions(file),
        .alias_aeroports = create_alias(),
        .routes = create_graph_routes(),
        .fligths = create_flitghs_digraph()
    };

    _read_routes_graph(new, file);
    _generate_searchs(new);
    _read_fligth_graph(new, file);
    return new;
}

GraphAeroport *destroy_graph_aeroport(GraphAeroport *self){

    *self = (GraphAeroport){
        .alias_aeroports = destroy_alias(self->alias_aeroports),
        .fligths = destroy_fligths_digraph(self->fligths),
        .routes = destroy_grt(self->routes),
        .regions = destroy_regions(self->regions)
    };
    me_free(self);
    return NULL;
}

void gpae_add_new_vertex(GraphAeroport *self, char *name_alias){

    if (alias_get_number_by_alias(self->alias_aeroports, name_alias) != -1 ){
        //vertex already existing in graphs
        return;
    }
    alias_add_alias(self->alias_aeroports, name_alias);
    grt_create_vertex(self->routes);
    fldgp_add_new_vertex(self->fligths);
}
void gpae_remove_vertex(GraphAeroport *self, char *name_alias){

    int number_vertex = alias_get_number_by_alias(self->alias_aeroports, name_alias);
    if ( number_vertex == -1 ){
        return;
    }
    grt_del_vertex(self->routes, number_vertex);
    fldgp_del_vertex(self->fligths, number_vertex);
}
int gpae_add_new_rote(GraphAeroport *self, char *from, char *to){

    int from_index = alias_get_number_by_alias(self->alias_aeroports, from);
    int to_index = alias_get_number_by_alias(self->alias_aeroports, to);
    InfoAeroports *from_info = re_get_info_aeroport(self->regions, from);
    InfoAeroports *to_info = re_get_info_aeroport(self->regions, to);

    if ( !from_info || !to_info ){
        return 0;
    }
    if ( from_index == -1 ){
        gpae_add_new_vertex(self, from);
        from_index = alias_get_number_by_alias(self->alias_aeroports, from);
    }
    if ( to_index == -1 ){
        gpae_add_new_vertex(self, to);
        to_index = alias_get_number_by_alias(self->alias_aeroports, to);
    }

    double dist = calc_dist(
            ifa_get_x_cord(from_info),
            ifa_get_y_cord(from_info),
            ifa_get_x_cord(to_info),
            ifa_get_y_cord(to_info)
            );

    grt_add_edge(self->routes, from_index, to_index, dist);
    return 1;
}

int gpae_add_new_fligth(GraphAeroport *self, char *from, char *to, int number_stops, int number_fligth, char *departure_time, char *arrival_time){



    int from_vertex = alias_get_number_by_alias(self->alias_aeroports, from);
    int to_vertex = alias_get_number_by_alias(self->alias_aeroports, to);

    if ( from_vertex == -1 ){
        gpae_add_new_vertex(self, from);
        from_vertex = alias_get_number_by_alias(self->alias_aeroports, from);
    }
    if ( to_vertex == -1){
        gpae_add_new_vertex(self, to);
        to_vertex = alias_get_number_by_alias(self->alias_aeroports, to);
    }
    InfoAeroports *from_info = re_get_info_aeroport(self->regions, from);
    InfoAeroports *to_info = re_get_info_aeroport(self->regions, to);

    if ( !from_info || !to_info ){
        return 0;
    }
    LinkedList *route_from_to = res_mount_way_by_vertex(ifa_get_result_bfs(from_info), to_vertex);

    if ( route_from_to == NULL ){
        return 0;
    }
    BaseValue *dist_kv = lkl_pop(route_from_to);
    double dist = *bv_get_data_convert(dist_kv, double*);

    InfoFligth *arest = create_info_fligth(
            number_fligth,
            dist,
            number_stops,
            departure_time,
            arrival_time
            );


    fldgp_add_new_arest(self->fligths, from_vertex, to_vertex, arest);
    return 1;
}
int gpae_remove_route(GraphAeroport *self, char *from, char *to){


    int from_vertex = alias_get_number_by_alias(self->alias_aeroports, from);
    int to_vertex = alias_get_number_by_alias(self->alias_aeroports, to);

    if ( from_vertex == -1 || to_vertex == -1 ){
        return 0;
    }
    grt_remove_edge(self->routes, from_vertex, to_vertex);
    return 1;
}

int gpae_remove_fligth(GraphAeroport *self, char *from, char *to){

    int from_vertex = alias_get_number_by_alias(self->alias_aeroports, from);
    int to_vertex = alias_get_number_by_alias(self->alias_aeroports, to);

    if ( from_vertex == -1 || to_vertex == -1 ){
        return 0;
    }
    fldgp_remove_one_arest(self->fligths, from_vertex, to_vertex);
    return 1;
}
char *gpae_str(GraphAeroport *self){

    char *regions_str = re_str(self->regions);
    char *alias_string = alias_str(self->alias_aeroports);
    char *routes_str = grt_str(self->routes);
    char *fligths_str = fldgp_str(self->fligths);
    char *result = me_formatted_str("%s\n%s\n%s\n%s", regions_str, alias_string, routes_str, fligths_str);
    me_free_several_objects(4, &regions_str, &alias_string, &routes_str, &fligths_str);
    return result;
}

char *gpae_get_alls_fligths_from(GraphAeroport *self, char *name_alias){

    int from_vertex = alias_get_number_by_alias(self->alias_aeroports, name_alias);
    if ( from_vertex == -1 ){
        return me_formatted_str("Don't was possible find fligths to %s!", name_alias);
    }
    LinkedList *list_result = fldgp_get_direct_fligths_from(self->fligths, from_vertex);
    LinkedList *list_fligths_vertex;
    InfoFligth *arest;
    int *to;
    char *respost = me_formatted_str("fligths leaving from %s:\n\n", name_alias);
    char *aux;
    for (int i = 0; i < lkl_get_tam(list_result); ++i) {
        list_fligths_vertex = lkl_get_data(list_result, i);
        if ( lkl_get_tam(list_fligths_vertex) > 0 ){
            aux = respost;
            respost = me_formatted_str("%s\tto %s:\n", respost, alias_get_alias_by_number(self->alias_aeroports, i));
            me_free(aux);
        }
        for (int j = 0; j < lkl_get_tam(list_fligths_vertex) ; ++j) {

            arest = lkl_get_data(list_fligths_vertex, j);
            aux = respost;
            respost = me_formatted_str("%s\t\t%s\n", respost,if_str(arest));
            me_free(aux);

        }
    }
    list_result = destroy_lkl(list_result);
    return respost;
}

char *gpae_get_route_from_to(GraphAeroport *self, char *alias_from, char *alias_to){


    int vertex_from = alias_get_number_by_alias(self->alias_aeroports, alias_from);
    int vertex_to = alias_get_number_by_alias(self->alias_aeroports, alias_to);

    if ( vertex_from == -1 || vertex_to == -1 ){
        return me_formatted_str("aeroports %s or %s don't existing!\n", alias_from, alias_to);
    }
    RespostSearch *respost_search = grt_bfs(self->routes, vertex_from);
    LinkedList *way_from_to = res_mount_way_by_vertex(respost_search, vertex_to);
    int current_vertex;
    BaseValue *unstacked=lkl_pop(way_from_to);
    double dist = *bv_get_data_convert(unstacked, double*);
    unstacked = destroy_base_value(unstacked);
    char *respost = me_formatted_str("route: \ndist: %f\n%s -> ", dist,alias_get_alias_by_number(self->alias_aeroports, vertex_from));
    char *aux;
    respost_search = destroy_respost(respost_search);

    while (!lkl_is_void(way_from_to)){

        unstacked= lkl_pop(way_from_to);
        current_vertex = *bv_get_data_convert(unstacked, int*);
        unstacked = destroy_base_value(unstacked);
        aux = respost;
        respost = me_formatted_str(
                (lkl_get_tam(way_from_to)  == 0) ?"%s%s.\n":"%s%s -> ",
                respost,
                alias_get_alias_by_number(self->alias_aeroports, current_vertex));

        me_free(aux);
    }
    return respost;

}

double gpae_get_distance_betwen_aeports(GraphAeroport *self, char *from, char *to){

    int from_index = alias_get_number_by_alias(self->alias_aeroports, from);
    int to_index = alias_get_number_by_alias(self->alias_aeroports, to);

    if ( from_index == -1 || to_index == -1 ){
        return 0.0;
    }
    return grt_get_dist_betwen_aeroports(self->routes, from_index, to_index);
}

char *gpae_get_aeroports_that_do_not_has_path(GraphAeroport *self, char *from){

    int from_vertex = alias_get_number_by_alias(self->alias_aeroports, from);

    if ( from_vertex == -1 ){
        return NULL;
    }
    LinkedList *vertex_that_not_way = grt_get_vertex_that_not_has_way(self->routes, from_vertex);
    int tam_list = lkl_get_tam(vertex_that_not_way);
    int current_value;
    char *respost = me_formatted_str("from aeroport %s don't is possible arrived in:\n", from);
    char *aux;
    for (int i = 0; i < tam_list-1; ++i) {
        current_value = *(int *)lkl_get_data(vertex_that_not_way, i);
        aux = respost;
        respost = me_formatted_str("%s\t%s, ", respost, alias_get_alias_by_number(self->alias_aeroports, current_value));
        me_free(aux);
    }
    aux = respost;
    respost = me_formatted_str("%s, %s.", respost, alias_get_alias_by_number(self->alias_aeroports, tam_list-1));
    vertex_that_not_way = destroy_lkl(vertex_that_not_way);
    return respost;
}

char *gpae_find_less_fligth_betwen_aeroports(GraphAeroport *self, char *from, char *to){

    int from_vertex, to_vertex;
    discovery_from_and_to_vertex(self, from, to, &from_vertex, &to_vertex);

    Dijkstra *dj = fldgp_dijkstra_find_less_distance(self->fligths, from_vertex);

}