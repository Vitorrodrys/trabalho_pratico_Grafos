//
// Created by vitor on 11/11/23.
//

#include "graph_airport.h"
#include "../memory/memory.h"
#include "graph_routes//graph_routes.h"
#include "flights_digraph/flights_digraph.h"
#include "../generic_structs/list/list.h"
#include <math.h>
#include "../string/string.h"

double calc_dist(int x, int y, int x_l, int y_l){
//usage by calc a distance from an airport to another airport
    int x_calc = x-x_l;
    int y_calc = y-y_l;

    return sqrt((double )(x_calc*x_calc+y_calc*y_calc));
}

typedef struct GraphAirport {
    FlightsDigraph *fligths;//is responsible for to control the flights graph
    GraphRoutes *routes;//is responsible for to control the routes graph
    Alias *alias_aeroports;//here is stored the alias of each airport linked with your vertex number corresponding, more good explained within of the implementation of the TAD
    Regions *regions;//here is stored the information about each airport, how geographic cordenates, etc
}GraphAirport;


Alias *gpae_get_alias(GraphAirport *self){
    return self->alias_aeroports;
}

void discovery_from_and_to_vertex(GraphAirport *self, char *from, char *to, int *from_vertex, int *to_vertex){
    //usage to get from_vertex and to_vertex in hash table of alias
    *from_vertex = alias_get_number_by_alias(self->alias_aeroports, from);
    *to_vertex = alias_get_number_by_alias(self->alias_aeroports, to);
}

void _read_fligth_graph(GraphAirport *self, CurrentFile *file){
    /*read flight chart from file
    * CurrentFile *file -> parser instance containing the file contents
     * */
    pf_advance_to_word(file, "!fligths");//jump to !fligths, where is the informations of the fligths graph
    pf_get_next_char(file);
    pf_get_next_char(file);
    char *str = NULL;
    char *from = NULL;
    char *to = NULL;
    List *list_args = NULL;
    int number_current_flight;
    while (!pf_is_end_file(file)){//while don't is the end of file
        str = pf_get_word_until_token(file, '\n');//get the current line from file

        list_args = li_break_str_in_list(str, " ");//break the line in space
        from = li_get_element_in_list(list_args,2);//get from and to
        to = li_get_element_in_list(list_args, 4);

        gpae_add_new_vertex(self, from);
        gpae_add_new_vertex(self, to);

        number_current_flight = fldgp_get_quantity_flights(self->fligths);//get the current quantity of flights to see the id of the new flight

        gpae_add_new_fligth(
                self,
                from,
                to,
                atoi(li_get_element_in_list(list_args, 6)),//index 6 is the number stops, convert this string in int
                number_current_flight,//get the current quantity of flights to see the id of the new flight
                li_get_element_in_list(list_args, 3),//index 3 is out time
                li_get_element_in_list(list_args, 5)//index 5 is arrived time
        );

        alias_add_flight(self->alias_aeroports, number_current_flight, from, to);
        list_args = destroy_list(list_args);
        from = NULL, to = NULL;
        pf_get_next_char(file);
        me_free(str);
    }
}

void _read_routes_graph(GraphAirport *self, CurrentFile *file){

    pf_advance_to_word(file, "!routes");//jump to routes, where is the information of routes
    char *str = pf_get_word_until_token(file, '!');//get of the current token until token !,
    // where is the end of the routes information
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
        gpae_add_new_route(self, from, to);
        list_aux = destroy_list(list_aux);
        pf_get_next_char(routes);
        pf_get_next_char(routes);

        me_free(sub_str);

    }
    routes = destroy_parser(routes);

}


GraphAirport *create_graph_aeroport(CurrentFile *file){

    GraphAirport *new = me_memory_alloc(NULL, sizeof(GraphAirport ));
    //starts the instances of each auxiliary TAD
    *new = (GraphAirport ){
        .regions = create_regions(file),
        .alias_aeroports = create_alias(),
        .routes = create_graph_routes(),
        .fligths = create_flitghs_digraph()
    };

    _read_routes_graph(new, file);
    _read_fligth_graph(new, file);
    return new;
}

GraphAirport *destroy_graph_aeroport(GraphAirport *self){

    *self = (GraphAirport ){
        .alias_aeroports = destroy_alias(self->alias_aeroports),
        .fligths = destroy_fligths_digraph(self->fligths),
        .routes = destroy_grt(self->routes),
        .regions = destroy_regions(self->regions)
    };
    me_free(self);
    return NULL;
}

void gpae_add_new_vertex(GraphAirport *self, char *name_alias){

    if (alias_get_number_by_alias(self->alias_aeroports, name_alias) != -1 ){
        //vertex already existing in graphs
        return;
    }
    alias_add_alias(self->alias_aeroports, name_alias);
    grt_create_vertex(self->routes);
    fldgp_add_new_vertex(self->fligths);
}
void gpae_remove_vertex(GraphAirport *self, char *name_alias){

    int number_vertex = alias_get_number_by_alias(self->alias_aeroports, name_alias);
    if ( number_vertex == -1 ){
        return;
    }
    grt_del_vertex(self->routes, number_vertex);
    fldgp_del_vertex(self->fligths, number_vertex);
}

int gpae_add_new_route(GraphAirport *self, char *from, char *to){

    int from_index, to_index;
    discovery_from_and_to_vertex(self, from, to, &from_index, &to_index);
    InfoAirport *from_info = re_get_info_aeroport(self->regions, from);
    InfoAirport *to_info = re_get_info_aeroport(self->regions, to);

    if ( !from_info || !to_info ){
        //case doesn't have information about the airports, then this airport received doesn't exist
        return 0;
    }
    if ( from_index == -1 ){
        //case from_index don't have found, then create a new alias in hashmap of alias
        gpae_add_new_vertex(self, from);
        from_index = alias_get_number_by_alias(self->alias_aeroports, from);
    }
    if ( to_index == -1 ){
        //case to_index don't have found, then create a new alias in hashmap of alias
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

int gpae_add_new_fligth(GraphAirport *self, char *from, char *to, int number_stops, int number_fligth, char *departure_time, char *arrival_time){

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
    InfoAirport *from_info = re_get_info_aeroport(self->regions, from);
    InfoAirport *to_info = re_get_info_aeroport(self->regions, to);

    if ( !from_info || !to_info ){
        return 0;
    }
    RespostSearchBFS *bfs_search = grt_bfs(self->routes, from_vertex);
    //there is calculating the route usage the routes graph, from from_vertex to to_vertex, is returned a list
    //that in last position has a dist of 'from' to 'to', and the sequence of vertex with the route, but only is needed
    //the distance now
    LinkedList *route_from_to = resbfs_mount_way_to_vertex(bfs_search, to_vertex);
    bfs_search = destroy_respost(bfs_search);
    if ( route_from_to == NULL ){
        return 0;
    }
    BaseValue *dist_kv = lkl_pop(route_from_to);
    double dist = *bv_get_data_convert(dist_kv, double*);

    //create one edge with the datas received in parameters
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
int gpae_remove_route(GraphAirport *self, char *from, char *to){
    int from_vertex = alias_get_number_by_alias(self->alias_aeroports, from);
    int to_vertex = alias_get_number_by_alias(self->alias_aeroports, to);

    if ( from_vertex == -1 || to_vertex == -1 ){
        return 0;
    }
    grt_remove_edge(self->routes, from_vertex, to_vertex);
    return 1;
}

int gpae_remove_fligth(GraphAirport *self, char *from, char *to){

    int from_vertex = alias_get_number_by_alias(self->alias_aeroports, from);
    int to_vertex = alias_get_number_by_alias(self->alias_aeroports, to);

    if ( from_vertex == -1 || to_vertex == -1 ){
        return 0;
    }
    fldgp_remove_one_arest(self->fligths, from_vertex, to_vertex);
    return 1;
}
char *gpae_str(GraphAirport *self){

    char *regions_str = re_str(self->regions);
    char *alias_string = alias_str(self->alias_aeroports);
    char *routes_str = grt_str(self->routes);
    char *fligths_str = fldgp_str(self->fligths);
    char *result = str_formatted("%s\n%s\n%s\n%s", regions_str, alias_string, routes_str, fligths_str);
    me_free_several_objects(4, &regions_str, &alias_string, &routes_str, &fligths_str);
    return result;
}


/*
 *
 * Question 5.1:
 *
 * */
char *gpae_get_route_from_to(GraphAirport *self, char *alias_from, char *alias_to){


    int vertex_from, vertex_to;
    discovery_from_and_to_vertex(self, alias_from, alias_to, &vertex_from, &vertex_to);

    if ( vertex_from == -1 || vertex_to == -1 ){
        return str_formatted("aeroports %s or %s don't existing!\n", alias_from, alias_to);
    }
    RespostSearchBFS *respost_search = grt_bfs(self->routes, vertex_from);
    LinkedList *way_from_to = resbfs_mount_way_to_vertex(respost_search, vertex_to);
    int current_vertex;
    BaseValue *unstacked=lkl_pop(way_from_to);
    double dist = *bv_get_data_convert(unstacked, double*);
    unstacked = destroy_base_value(unstacked);
    char *respost = str_formatted("route: \ndist: %f\n%s -> ", dist,alias_get_alias_by_number(self->alias_aeroports, vertex_from));
    char *aux;
    respost_search = destroy_respost(respost_search);

    while (!lkl_is_void(way_from_to)){

        unstacked= lkl_pop(way_from_to);
        current_vertex = *bv_get_data_convert(unstacked, int*);
        unstacked = destroy_base_value(unstacked);
        aux = respost;
        respost = str_formatted(
                (lkl_get_tam(way_from_to)  == 0) ?"%s%s.\n":"%s%s -> ",
                respost,
                alias_get_alias_by_number(self->alias_aeroports, current_vertex));

        me_free(aux);
    }
    return respost;

}

/*
 *
 * End question 5.1
 *
 * */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 *
 * Question 5.2:
 *
 * */
char *gpae_get_alls_direct_fligths_from(GraphAirport *self, char *name_alias){

    int from_vertex = alias_get_number_by_alias(self->alias_aeroports, name_alias);
    if ( from_vertex == -1 ){
        return str_formatted("Don't was possible find fligths to %s!", name_alias);
    }
    LinkedList *list_result = fldgp_get_direct_fligths_from(self->fligths, from_vertex);
    LinkedList *list_fligths_vertex;
    InfoFligth *arest;
    char *respost = str_formatted("fligths leaving from %s:\n\n", name_alias);
    char *aux;
    for (int i = 0; i < lkl_get_tam(list_result); ++i) {
        list_fligths_vertex = lkl_get_data(list_result, i);
        if ( lkl_get_tam(list_fligths_vertex) > 0 ){
            aux = respost;
            respost = str_formatted("%s\tto %s:\n", respost, alias_get_alias_by_number(self->alias_aeroports, i));
            me_free(aux);
        }
        for (int j = 0; j < lkl_get_tam(list_fligths_vertex) ; ++j) {

            arest = lkl_get_data(list_fligths_vertex, j);
            aux = respost;
            respost = str_formatted("%s\t\t%s\n", respost,if_str(arest));
            me_free(aux);

        }
    }
    list_result = destroy_lkl(list_result);//TODO, problem, there is clear the addrees of the matrix
    return respost;
}
/*
 *
 * End question 5.2
 *
 * */


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*
 * Question 5.3:
 *
 * */
char *_mount_respost_less_fligth_from_to(GraphAirport *self, LinkedList *vertex_list, char *title_msg){

    BaseValue *current_element_list = lkl_pop(vertex_list);
    InfoFligth *dist = bv_get_data(current_element_list);
    char *respost = str_formatted("%s\n\tdist:\n\t\t%s\n\t\troute:\n\t\t\t", title_msg, if_str(dist));
    char *aux;
    int *current_vertex;

    while ( lkl_get_tam(vertex_list) > 1 ){

        current_element_list = lkl_pop(vertex_list);
        current_vertex=bv_get_data(current_element_list);
        aux = respost;
        respost = str_formatted("%s%s -> ", respost, alias_get_alias_by_number(self->alias_aeroports, *current_vertex));
        me_free(aux);
        current_element_list = destroy_base_value(current_element_list);
    }
    current_element_list = lkl_pop(vertex_list);
    current_vertex =bv_get_data(current_element_list);
    aux = respost;
    respost = str_formatted("%s%s.\n", respost, alias_get_alias_by_number(self->alias_aeroports, *current_vertex));
    current_element_list = destroy_base_value(current_element_list);
    me_free(aux);
    return respost;
}


char *gpae_find_less_fligth_betwen_aeroports(GraphAirport *self, char *from, char *to){

    int from_vertex, to_vertex;
    discovery_from_and_to_vertex(self, from, to, &from_vertex, &to_vertex);

    if ( from_vertex == -1 || to_vertex == -1 ){
        return str_formatted("airport %s or %s don't existing!", from, to);
    }
    Dijkstra *dj_distance = fldgp_dijkstra_find_less_distance(self->fligths, from_vertex);
    Dijkstra *dj_duration = fldgp_dijkstra_find_less_duration(self->fligths, from_vertex);
    LinkedList *list_distances = dijkstra_mount_less_fligth_from_to(dj_distance, to_vertex);
    LinkedList *list_durations = dijkstra_mount_less_fligth_from_to(dj_duration, to_vertex);

    char *title = str_formatted("less fligth %s to %s in distance:", from, to);
    char *dj_string_distance = _mount_respost_less_fligth_from_to(self, list_distances, title);
    me_free(title);
    title = str_formatted("less fligth %s to %s in duration:", from, to);
    char *dj_string_duration = _mount_respost_less_fligth_from_to(self, list_durations, title);
    me_free(title);

    char *respost = str_formatted("%s\n%s", dj_string_distance, dj_string_duration);
    list_durations = destroy_lkl(list_durations);
    list_distances = destroy_lkl(list_distances);
    dj_duration = destroy_dijkstra(dj_duration);
    dj_distance = destroy_dijkstra(dj_distance);
    me_free_several_objects(2, &dj_string_duration, &dj_string_distance);
    return respost;

}

/*
 *
 * End 5.3 question
 *
 * */






///////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/*
 * Question 5.4:
 * */
char *_get_critical_airports(GraphAirport *self, char *from){

    int from_vertex;

    from_vertex = alias_get_number_by_alias(self->alias_aeroports, from);

    if ( from_vertex == -1 ){
        return str_formatted("airport %s don't exist", from);
    }
    RespostSearchDFS *dfs_respost;
    char *respost = str_formatted("Airports that, if unavailable, would result in the airport %s having no path to all other airports:\n", from);
    char *aux;
    for(int i = 0; i< grt_get_tam(self->routes);i++){
        if ( from_vertex == i ){
            continue;
        }
        dfs_respost = grt_dfs(self->routes, from_vertex, i);
        if (resdfs_exist_vertex_not_visited(dfs_respost)){
            aux = respost;
            respost = (i%10 == 0)
                        ?str_formatted("%s\n\t%s,",respost, alias_get_alias_by_number(self->alias_aeroports, i))
                        :str_formatted("%s%s, ",respost, alias_get_alias_by_number(self->alias_aeroports, i));
            me_free(aux);
            dfs_respost = destroy_respost_dfs(dfs_respost);

        }

    }
    return respost;


}
char *gpae_get_aeroports_that_do_not_has_path(GraphAirport *self, char *from){

    int from_vertex = alias_get_number_by_alias(self->alias_aeroports, from);
    char *aux;
    char *respost;
    if ( from_vertex == -1 ){
        return NULL;
    }
    LinkedList *vertex_that_not_way = grt_get_vertex_that_not_has_way(self->routes, from_vertex);
    int tam_list = lkl_get_tam(vertex_that_not_way);
    if ( tam_list == 0 ){
        vertex_that_not_way = destroy_lkl(vertex_that_not_way);
        char *critical_airports = _get_critical_airports(self, from);
        respost = str_formatted("from airport %s is possible arrived to any airport", from);
        aux = respost;
        respost = str_formatted("%s\n%s\n", respost, critical_airports);
        me_free_several_objects(2, &aux, &critical_airports);
        return respost;
    }
    int current_value;
    respost = str_formatted("from airport %s don't is possible arrived in:\n", from);
    for (int i = 0; i < tam_list-1; ++i) {
        current_value = *(int *)lkl_get_data(vertex_that_not_way, i);
        aux = respost;
        respost = str_formatted("%s\t%s, ", respost, alias_get_alias_by_number(self->alias_aeroports, current_value));
        me_free(aux);
    }
    aux = respost;
    respost = str_formatted("%s, %s.", respost, alias_get_alias_by_number(self->alias_aeroports, tam_list-1));
    vertex_that_not_way = destroy_lkl(vertex_that_not_way);
    return respost;
}

/*
 * end question 5.4
 *
 * */

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 *
 * Question 5.5:
 *
 * */
char *gpae_is_hamiltoniano_cycle(GraphAirport *self, LinkedList *path){

    short vertex_already_passed[grt_get_tam(self->routes)];
    memset(vertex_already_passed, 0, sizeof(vertex_already_passed));
    int current_vertex;
    for (int i = 0; i< grt_get_tam(self->routes)-1; i++){
        current_vertex = *(int *)lkl_get_data(path, i);
        if ( vertex_already_passed[current_vertex]){
            return strdup("path generated don't is a hamiltoniano cycle");
        }
        vertex_already_passed[current_vertex] = 1;
    }
    int first = *(int *)lkl_get_data(path, 0);
    int last = *(int *) lkl_get_data(path, lkl_get_tam(path)-1);
    return  strdup((first == last)?"this path is a hamiltoniano cycle":"this path don't is a hamiltoniano path");
}
char *gpae_get_path_that_include_all(GraphAirport *self, char *alias_origin){

    int origin_vertex = alias_get_number_by_alias(self->alias_aeroports, alias_origin);
    if ( origin_vertex == -1 ){
        return str_formatted("Airport %s don't existing!", alias_origin);
    }
    RespostSearchDFS *dfs_result = grt_dfs(self->routes, origin_vertex, NOT_IGNORE_ANY_VERTICES);

    double dist_path = resdfs_get_dist_traveled(dfs_result);
    LinkedList *path = resdfs_get_path_traveled(dfs_result);

    char *respost = str_formatted("one path was finded:\n\tdist:%f\n\tpath:\n\t\t %s ->", dist_path,alias_origin);
    char *aux;
    int current_element;
    int count_break_line = 0;
    int size_list = lkl_get_tam(path);
    for (int i = 1; i < size_list-1; ++i) {

        aux = respost;
        current_element = *(int *) lkl_get_data(path, i);
        respost = str_formatted("%s %s ->", respost, alias_get_alias_by_number(self->alias_aeroports, current_element));
        me_free(aux);
        if (count_break_line >= 10){
            aux = respost;
            respost = str_concat(respost, "\n\t\t");
            me_free(aux);
            count_break_line = 0;
        }else
            count_break_line++;
    }

    char *is_hamiltoniano = gpae_is_hamiltoniano_cycle(self, path);
    aux = respost;
    respost = str_formatted("%s %s.\n%s", respost, alias_get_alias_by_number(self->alias_aeroports, *(int *) lkl_get_data(path, size_list-1)), is_hamiltoniano);
    dfs_result = destroy_respost_dfs(dfs_result);
    me_free_several_objects(2, &aux, &is_hamiltoniano);
    path = destroy_lkl(path);
    return respost;

}

/*
 *
 * End Question 5.5
 *
 * */

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 *
 * It may help to check the answers of the 5.3
 *
 * */
char *gpae_get_route_of_a_flight(GraphAirport *self, int number_flight) {

    LinkedList *from_to_flight = alias_get_from_to_of_a_flight(self->alias_aeroports, number_flight);
    if (from_to_flight == NULL) {
        return str_formatted("don't exist a flight with the number %d!", number_flight);
    }
    int from = *(int *) lkl_get_data(from_to_flight, 0);
    int to = *(int *) lkl_get_data(from_to_flight, 1);
    char *alias_from = alias_get_alias_by_number(self->alias_aeroports, from);
    char *alias_to = alias_get_alias_by_number(self->alias_aeroports, to);

    InfoFligth *edge_fligth = fldgp_get_one_flight(self->fligths, from, to, number_flight);

    char *flight_in_str = if_str(edge_fligth);
    char *route = gpae_get_route_from_to(self, alias_from, alias_to);

    char *respost = str_formatted("informations of the flight: \n%s\n\ninformations about the route: \n\n%s\n\n", flight_in_str, route);
    me_free_several_objects(2, &flight_in_str, &route);
    return respost;
}

/*
 *
 * supply the answer for the first topic of the menu
 *
 * */
char *gpae_get_regions_in_str(GraphAirport *self){
    return re_str(self->regions);
}

double gpae_get_distance_betwen_aeports(GraphAirport *self, char *from, char *to){

    int from_index, to_index;
    discovery_from_and_to_vertex(self, from, to, &from_index, &to_index);
    if ( from_index == -1 || to_index == -1 ){
        return 0.0;
    }
    return grt_get_dist_betwen_aeroports(self->routes, from_index, to_index);
}


/**
* pratic of coloring
*/
char * gpae_coloring_routes_graph(GraphAirport *self, char **name_colors){

    DistColors *colors = grt_coloring(self->routes);

    int size_graph = grt_get_tam(self->routes);
    char *respost = str_formatted("quantity of colors was usage: %d\ncolors graph:\n", dc_get_quantity_colors_usage(colors));
    char *aux;
    for (int i = 0; i< size_graph; i++){

        aux = respost;

        respost = str_formatted(
                "%s\t%s:color %s\n",
                respost,
                alias_get_alias_by_number(self->alias_aeroports, i),
                name_colors[dc_get_color_vertex(colors, i)]
                );
        me_free(aux);

    }
    return respost;
}

void gpae_prim(GraphAirport *self){
    typedef struct Prim{

        int size_graph;
        double *edge_sizes;
        int *vertex_linked;
        int *parent;


    }Prim;
    Prim *prim= grt_prim(self->routes);

#include <stdio.h>
    for (int i = 0; i < grt_get_tam(self->routes); ++i) {

        for (int j = 0; j < grt_get_tam(self->routes); ++j) {

            if (prim->parent[j] == i ){


                printf("%s, ", alias_get_alias_by_number(self->alias_aeroports, j));
            }
        }
        printf("\n");
    }
}
