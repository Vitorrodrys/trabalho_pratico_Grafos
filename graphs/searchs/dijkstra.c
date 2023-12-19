//
// Created by vitor on 13/11/23.
//

#include "dijkstra.h"
#include "../../memory/memory.h"
#include <float.h>
#include "limits.h"
#include <stdio.h>
#include "../../string/string.h"

typedef enum StateVertex{
    undefined, closed, opened
}StateVertex;

typedef struct Dijkstra {
    InfoFligth **dists;
    // Vector of edges that store the distance for each vertex.
    StateVertex *vertex_closeds;
    // Vector that represents the current state of the vertex, i.e., whether the calculated distance for it is the final distance or not.
    int *precedents;
    // Vector to store which vertex was passed before arriving at another vertex.
    int which_vertex;
    int quantity_vertex;
    int quantity_vertex_opened;
    int quantity_vertex_closeds;
    int quantity_vertex_undefined;
    // Pointer to a function that allows comparison to determine if one edge is smaller than another.
    // Pass a different pointer to this function when generating an instance of the TAD with 'create_dijkstra'
    // can allow changing the behavior of Dijkstra. It can find the shortest path in terms of duration at one moment,
    // and in terms of distance at another moment.
    int (*compare_less_fligth)(InfoFligth *self, InfoFligth *other);
} Dijkstra;


Dijkstra *create_dijkstra(int quantity_vertex, int which_vertex, int (*compare_less_fligth)(InfoFligth *self, InfoFligth*other)){

    Dijkstra *new = me_memory_alloc(NULL, sizeof(Dijkstra));
    *new = (Dijkstra){
        .dists = me_memory_alloc(NULL, sizeof(InfoFligth*)*quantity_vertex),//allocate the distance vectors of each vertex
        .vertex_closeds = me_memory_alloc(NULL, sizeof(StateVertex)*quantity_vertex),//allocate the vector that speak the state of the vertex
        .precedents = me_memory_alloc(NULL, sizeof(int)*quantity_vertex),//allocate the vector that speak the precedence of each vertex
        .which_vertex = which_vertex,//origin of the search
        .compare_less_fligth = compare_less_fligth,//function pointer that determine if the search will be in terms of duration or distance
        .quantity_vertex = quantity_vertex,//quantity vertex of the graph
        .quantity_vertex_opened = 1,//starts the quantity of opened vertex as 1, because the origin already is considered a vertex open
        .quantity_vertex_closeds = 0,//starts the quantity of closed vertex as 0, because a vertex only is closed when is changed how the less distance current
        .quantity_vertex_undefined = quantity_vertex-1//how only the origin current is opened, then all others are undefined
    };
    for (int i = 0; i < quantity_vertex; ++i) {
        //for each vertex, set that it don't have precedent
        new->precedents[i] = -1;
        //set the distance how NULL for this vertex
        new->dists[i] = NULL;
    }
    //define that the precedent of the origin is itself
    new->precedents[which_vertex] = which_vertex;

    //The following two lines of instruction create a flight with a distance of 0 from the origin to the origin.
    // The creation of an empty list was necessary because at some point Dijkstra will need to add the distance
    // from the origin with another distance. In these cases, the methods of the InfoFlight will attempt to
    // concatenate two lists. If 'null' were used, these methods would try to manipulate the NULL value, resulting in a segmentation fault.
    LinkedList *void_list = create_linked_list();
    new->dists[which_vertex] = create_info_fligth_with_time_duration(void_list,0,0, create_time_hour_with_seconds(0));

    //define all the vertex with the state undefined
    memset(new->vertex_closeds, undefined, sizeof(StateVertex) * quantity_vertex);
    //define only the origin with opened
    new->vertex_closeds[which_vertex] = opened;

    return new;
}

Dijkstra *destroy_dijkstra(Dijkstra *self){
    //destroy the unique index of the array that was the own TAD that created, the others positions was received by graph
    self->dists[self->which_vertex] = destroy_info_fligth(self->dists[self->which_vertex]);
    me_free(self->dists);
    memset(self->vertex_closeds, undefined, sizeof(StateVertex)*self->quantity_vertex);
    me_free(self->vertex_closeds);
    me_free(self->precedents);
    self->quantity_vertex = 0;
    self->which_vertex=0;
    self->compare_less_fligth = NULL;
    self->quantity_vertex_opened = 0;
    self->quantity_vertex_closeds = 0;
    self->quantity_vertex_undefined = 0;
    me_free(self);
    return NULL;

}

int dijkstra_find_less_vertex(Dijkstra *self){

    LinkedList *void_list = create_linked_list();//create a void list only by be vinculed as the flights list of the temporary less_element
    InfoFligth *less_element = create_info_fligth_with_time_duration(void_list,DBL_MAX, 0, create_time_hour_with_seconds(LONG_MAX));
    int index_less_element = -1;
    InfoFligth *aux2 = less_element;
    for (int i = 0; i < self->quantity_vertex; ++i) {
        if ( self->vertex_closeds[i] == opened && self->dists[i] && self->compare_less_fligth(self->dists[i], less_element) ){
            less_element = self->dists[i];
            index_less_element = i;
        }
    }
    aux2 = destroy_info_fligth(aux2);
    return index_less_element;
}

void dijkstra_close_this_vertex(Dijkstra *self, int vertex){
    if ( self->dists[vertex] == NULL ){
        fprintf(stderr, "trying of closed a vertex that don't has final distance. vertex: %d", vertex);
        exit(1);
    }
    if ( self->precedents[vertex] == -1 ){
        fprintf(stderr, "trying of closed a vertex taht don't has a precedent. vertex: %d", vertex);
        exit(1);
    }
    if ( self->vertex_closeds[vertex] != opened ){
        fprintf(stderr, "trying of closed a vertex that don't is opened. vertex %d", vertex);
        exit(1);
    }
    self->vertex_closeds[vertex] = closed;
    self->quantity_vertex_closeds++;
    self->quantity_vertex_opened--;
}

void dijkstra_add_value_arest(Dijkstra *self, int which_vertex, int pass_by,InfoFligth *value_arest){

    InfoFligth *value_dist = if_sum_fligths(self->dists[pass_by], value_arest);
    InfoFligth *before_value_vertex = self->dists[which_vertex];

    if ( before_value_vertex == NULL ){
        self->dists[which_vertex] = value_dist;
        self->precedents[which_vertex] = pass_by;
        self->vertex_closeds[which_vertex] = opened;
        self->quantity_vertex_opened++;
        self->quantity_vertex_undefined--;
        return;
    }
    if ( self->compare_less_fligth(value_dist, before_value_vertex) ){
        self->dists[which_vertex] = value_dist;
        self->precedents[which_vertex] = pass_by;
        before_value_vertex = destroy_info_fligth(before_value_vertex);
        return;
    }
    value_dist = destroy_info_fligth(value_dist);

}
int dijkstra_there_are_open_vertex(Dijkstra *self){
    return self->quantity_vertex_opened > 0;
}

LinkedList *dijkstra_mount_less_fligth_from_to(Dijkstra *self, int to){

    if ( self->dists[to] == NULL ){
        return NULL;
    }

    InfoFligth *distance=self->dists[to];
    LinkedList *list_aeroports = create_linked_list();
    while ( to != self->which_vertex ){

        lkl_append(
                list_aeroports,
                create_base_value(
                        create_int(to),
                        (void *)destroy_int,
                        (void *) convert_int_to_str,
                        (void *)me_eq_int,
                        sizeof(int)
                        )
                );
        to = self->precedents[to];
    }
    lkl_append(
            list_aeroports,
            create_base_value(
                    create_int(self->which_vertex),
                    (void *)destroy_int,
                    (void *)convert_int_to_str,
                    (void *)me_eq_int,
                    sizeof(int)
                    )
            );
    lkl_append(
            list_aeroports,
            create_base_value(
                    distance,
                    (void *)destroy_info_fligth,
                    (void *)if_str,
                    (void *)if_eq,
                    if_get_tam()
                    )
            );
    return list_aeroports;
}

