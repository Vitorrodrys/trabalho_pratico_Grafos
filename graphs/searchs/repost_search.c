
//
// Created by vitor on 25/10/23.
//

#include "repost_search.h"
#include "../../memory/memory.h"
#include "limits.h"
#include <stdio.h>


typedef enum MarkVisiteds{
    already_visited, no_visited, visiting
}MarkVisiteds;


char *mark_visiteds_to_str(MarkVisiteds mark){
    switch (mark) {

        case already_visited:
            return me_formatted_str("%s", "visited");
        case no_visited:
            return me_formatted_str("%s", "no visited");
        case visiting:
            return me_formatted_str("%s", "visiting");
    }
}

typedef struct RespostSearch{
    int tam_graph;
    int which_vertex;
    double *dists;
    int *pass_by;
    MarkVisiteds *visiteds;
    LinkedList *queue_vertex;
}RespostSearch;

RespostSearch * create_respost(int tam_graph, int which_vertex){

    RespostSearch *new = me_memory_alloc(NULL, sizeof(RespostSearch));

    new->tam_graph = tam_graph;
    new->which_vertex = which_vertex;

    //alocated dists, mark all dist for all vertex as infinity, and after mark the dist to it self how 0
    new->dists = me_memory_alloc(NULL, sizeof(double)*tam_graph);
    memset(new->dists, 0, sizeof (int)*tam_graph);
    new->dists[which_vertex] = 0;

    new->pass_by = me_memory_alloc(NULL, sizeof (int)*tam_graph);
    //define that I didn't go through any
    memset(new->pass_by, -1, sizeof (int)*tam_graph);
    new->pass_by[which_vertex] = which_vertex;


    //set that I don't visited any unless the I self
    new->visiteds = me_memory_alloc(NULL, sizeof (MarkVisiteds)*tam_graph);
    for (int i = 0; i < tam_graph; ++i) {
        new->visiteds[i] = no_visited;
    }
    new->visiteds[which_vertex] = visiting;

    //create the queue
    new->queue_vertex = create_linked_list();
    BaseValue *first_element = create_base_value(
            create_int(which_vertex), (void *)destroy_int,
            (void *) me_int_to_str, (void *)me_eq_int, sizeof(int));
    lkl_append(new->queue_vertex, first_element);

    return new;
}

RespostSearch *destroy_respost(RespostSearch *self){

    me_free_several_objects(3, &self->dists, &self->visiteds, &self->pass_by);
    self->queue_vertex = destroy_lkl(self->queue_vertex);
    self->tam_graph = 0;
    self->which_vertex = 0;
    me_free(self);
    return NULL;
}

int res_to_visite_element(RespostSearch *self, int from, int to, double dist){

    if ( from >= self->tam_graph  || to >= self->tam_graph ){
        return 0;
    }

    self->pass_by[to] = from;
    self->visiteds[to] = visiting;
    self->dists[to] = self->dists[from] + dist;
    BaseValue *new_element = create_base_value(
            create_int(to), (void *)destroy_int,
            (void *)me_int_to_str, (void *)me_eq_int, sizeof(int)
            );
    lkl_append(self->queue_vertex, new_element);
    return 1;
}

int res_get_next_vertex_queue(RespostSearch *self){

    int elem = *(int *)lkl_get_data(self->queue_vertex,0);
    lkl_rm_element(self->queue_vertex, 0);
    self->visiteds[elem] = already_visited;
    return elem;
}

int res_queue_is_void(RespostSearch *self){
    return lkl_is_void(self->queue_vertex);
}
int res_elem_still_not_visited(RespostSearch *self, int elem){
    return self->visiteds[elem] == no_visited;
}
char* res_str(RespostSearch *self){

    char *result;
    char *aux;
    result = me_formatted_str("by %d vertex: \narray of dists:\n\t", self->which_vertex);
    for (int i = 0; i < self->tam_graph-1; ++i) {
        aux = result;
        result = me_formatted_str("%s%d, ", result, self->dists[i]);
        me_free(aux);
    }
    aux = result;
    result = me_formatted_str("%s%d.\npass by:\n\t", result, self->dists[self->tam_graph-1]);
    me_free(aux);
    for (int i = 0; i < self->tam_graph-1; ++i) {
        aux = result;
        result = me_formatted_str("%s%d, ", result, self->pass_by[i]);
        me_free(aux);
    }
    aux = result;
    result = me_formatted_str("%s%d. \n", result, self->pass_by[self->tam_graph-1]);
    aux = result;
    result = me_formatted_str("%svisiteds:\n\t", result);
    me_free(aux);
    for (int i = 0; i < self->tam_graph-1; ++i) {

        aux = result;
        result = me_formatted_str("%s%s, ", mark_visiteds_to_str(self->visiteds[i]));
        me_free(aux);
    }
    aux = result;
    result = me_formatted_str("%s%s\n", mark_visiteds_to_str(self->visiteds[self->tam_graph-1]));
    return result;
}

LinkedList *res_mount_way_by_vertex(RespostSearch *self, int what_vertex){

    double dist = self->dists[what_vertex];
    LinkedList *way = create_linked_list();
    BaseValue *current_stacked_value = create_base_value(
            create_int(what_vertex), (void *)destroy_int, (void *)me_int_to_str,
            (void *)me_eq_int, sizeof(int)
            );
    lkl_append(way, current_stacked_value);
    int current_vertex = self->pass_by[what_vertex];

    if ( current_vertex == -1 ){
        return NULL;
    }
    while ( current_vertex != self->which_vertex ){

        current_stacked_value = create_base_value(
                create_int(current_vertex), (void *)destroy_int, (void *) me_int_to_str,
                (void *) me_eq_int, sizeof(int)
                );

        lkl_append(way,current_stacked_value);

        current_vertex = self->pass_by[current_vertex];
    }

    current_stacked_value = create_base_value(create_double(dist), (void *)destroy_double, NULL, NULL, sizeof(double));
    lkl_append(way, current_stacked_value);
    return way;
}
int res_exist_a_way_to_vertex(RespostSearch *self, int vertex){
    return self->visiteds[vertex] == already_visited;
}
int res_check_if_middle_path_contains_vertex(RespostSearch *self, int half_vertex, int to){

    int current_vertex = self->pass_by[to];
    while (current_vertex != self->which_vertex){

        if ( current_vertex == half_vertex ){
            return 1;
        }
        current_vertex = self->pass_by[current_vertex];
    }
    return 0;
}