//
// Created by vitor on 13/11/23.
//

#include "dijkstra.h"
#include "../../memory/memory.h"
#include <float.h>
#include <time.h>
#include "limits.h"
#include <stdio.h>
typedef struct Dijkstra{
    InfoFligth **dists;
    short *vertex_closeds;
    int *precedents;
    int which_vertex;
    int quantity_vertex;
    int (*compare_less_fligth)(InfoFligth *self, InfoFligth*other);
}Dijkstra;


Dijkstra *create_dijkstra(int quantity_vertex, int which_vertex, int (*compare_less_fligth)(InfoFligth *self, InfoFligth*other)){

    Dijkstra *new = me_memory_alloc(NULL, sizeof(Dijkstra));
    *new = (Dijkstra){
        .dists = me_memory_alloc(NULL, sizeof(InfoFligth*)*quantity_vertex),
        .vertex_closeds = me_memory_alloc(NULL, sizeof(short)*quantity_vertex),
        .precedents = me_memory_alloc(NULL, sizeof(int)*quantity_vertex),
        .which_vertex = which_vertex,
        .compare_less_fligth = compare_less_fligth,
        .quantity_vertex = quantity_vertex
    };
    for (int i = 0; i < quantity_vertex; ++i) {
        new->precedents[i] = -1;
        new->dists[i] = NULL;
    }
    new->dists[which_vertex] = create_info_fligth_with_time_duration(0,0,0, create_time_hour_with_seconds(0));
    return new;
}

Dijkstra *destroy_dijkstra(Dijkstra *self){
    //destroy the unique index of the array that was the own TAD that created, the others positions was received by graph
    self->dists[self->which_vertex] = destroy_info_fligth(self->dists[self->which_vertex]);
    me_free(self->dists);
    me_free(self->vertex_closeds);
    me_free(self->precedents);
    self->quantity_vertex = 0;
    self->which_vertex=0;
    self->compare_less_fligth = NULL;
    me_free(self);
    return NULL;

}

int dij_find_less_vertex(Dijkstra *self){

    InfoFligth *less_element = create_info_fligth_with_time_duration(0,DBL_MAX, 0, create_time_hour_with_seconds(LONG_MAX));
    int index_less_element = -1;
    InfoFligth *aux2 = less_element;
    for (int i = 0; i < self->quantity_vertex; ++i) {
        if ( !self->vertex_closeds[i] && self->dists[i] && self->compare_less_fligth(self->dists[i], less_element) ){
            less_element = self->dists[i];
            index_less_element = i;
        }
    }
    aux2 = destroy_info_fligth(aux2);
    return index_less_element;
}

void dij_close_this_vertex(Dijkstra *self, int vertex){
    if ( self->dists[vertex] == NULL ){
        fprintf(stderr, "trying of closed a vertex that don't has final distance. vertex: %d", vertex);
        exit(1);
    }
    if ( self->precedents[vertex] == -1 ){
        fprintf(stderr, "trying of closed a vertex taht don't has a precedent. vertex: %d", vertex);
        exit(1);
    }
    self->vertex_closeds[vertex] = 1;
}

void dij_add_value_arest(Dijkstra *self, int which_vertex, int pass_by,InfoFligth *value_arest){

    InfoFligth *value_dist = if_sum_fligths(self->dists[pass_by], value_arest);
    InfoFligth *before_value_vertex = self->dists[which_vertex];

    if ( before_value_vertex == NULL ){
        self->dists[which_vertex] = value_dist;
        self->precedents[which_vertex] = pass_by;
        return;
    }
    if ( self->compare_less_fligth(value_dist, before_value_vertex) ){
        self->dists[which_vertex] = value_dist;
        self->precedents[pass_by] = which_vertex;
        before_value_vertex = destroy_info_fligth(before_value_vertex);
        return;
    }
    value_dist = destroy_info_fligth(value_dist);

}
int dij_there_are_open_vertex(Dijkstra *self){
    for (int i = 0; i < self->quantity_vertex; ++i) {
        if ( !self->vertex_closeds[i] ){
            return 1;
        }
    }
    return 0;
}