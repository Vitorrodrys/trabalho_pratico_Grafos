
//
// Created by vitor on 25/10/23.
//

#include "respost_bfs.h"
#include "../../memory/memory.h"
#include "../../string/string.h"


typedef enum MarkVisiteds{
    already_visited, no_visited, visiting
}MarkVisiteds;


char *mark_visiteds_to_str(MarkVisiteds mark){
    switch (mark) {

        case already_visited:
            return str_formatted("%s", "visited");
        case no_visited:
            return str_formatted("%s", "no visited");
        case visiting:
            return str_formatted("%s", "visiting");
    }
}

typedef struct RespostSearchBFS{
    int tam_graph;//quantity of vertex of the graph
    int which_vertex;//vertex of origin of the search
    double *dists;//vector of distances for each vertex of the graph
    int *pass_by;// vector that indicates the predecessors of each vertex
    MarkVisiteds *visiteds;//Vector that indicates whether the vertex has already been visited by BFS or not
    LinkedList *queue_vertex;//Queue of vertices that determines the sequence that BFS will visit
}RespostSearchBFS;

RespostSearchBFS * create_respost(int tam_graph, int which_vertex){

    RespostSearchBFS *new = me_memory_alloc(NULL, sizeof(RespostSearchBFS));

    new->tam_graph = tam_graph;
    new->which_vertex = which_vertex;

    //allocate dists, mark all dist for all vertex as 0
    new->dists = me_memory_alloc(NULL, sizeof(double)*tam_graph);
    memset(new->dists, 0, sizeof (double)*tam_graph);

    new->pass_by = me_memory_alloc(NULL, sizeof (int)*tam_graph);
    memset(new->pass_by, -1, sizeof (int)*tam_graph);
    //define that the precedent of the origin is the own origin
    new->pass_by[which_vertex] = which_vertex;


    //define that all vertex don't was visited
    new->visiteds = me_memory_alloc(NULL, sizeof (MarkVisiteds)*tam_graph);
    for (int i = 0; i < tam_graph; ++i) {
        new->visiteds[i] = no_visited;
    }
    //define that the own origin is being visiting
    new->visiteds[which_vertex] = visiting;

    //create the queue
    new->queue_vertex = create_linked_list();
    BaseValue *first_element = create_base_value(
            create_int(which_vertex), (void *)destroy_int,
            (void *) convert_int_to_str, (void *)me_eq_int, sizeof(int));
    lkl_append(new->queue_vertex, first_element);

    return new;
}

RespostSearchBFS *destroy_respost(RespostSearchBFS *self){

    me_free_several_objects(3, &self->dists, &self->visiteds, &self->pass_by);
    self->queue_vertex = destroy_lkl(self->queue_vertex);
    self->tam_graph = 0;
    self->which_vertex = 0;
    me_free(self);
    return NULL;
}

int resbfs_to_visite_element(RespostSearchBFS *self, int from, int to, double dist){

    if ( from >= self->tam_graph  || to >= self->tam_graph ){
        return 0;
    }

    self->pass_by[to] = from;
    self->visiteds[to] = visiting;
    self->dists[to] = self->dists[from] + dist;
    BaseValue *new_element = create_base_value(
            create_int(to), (void *)destroy_int,
            (void *) convert_int_to_str, (void *)me_eq_int, sizeof(int)
            );
    lkl_append(self->queue_vertex, new_element);
    return 1;
}

int resbfs_get_next_vertex_queue(RespostSearchBFS *self){

    int elem = *(int *)lkl_get_data(self->queue_vertex,0);
    lkl_rm_element(self->queue_vertex, 0);
    self->visiteds[elem] = already_visited;
    return elem;
}

int resbfs_queue_is_void(RespostSearchBFS *self){
    return lkl_is_void(self->queue_vertex);
}
int resbfs_elem_still_not_visited(RespostSearchBFS *self, int elem){
    return self->visiteds[elem] == no_visited;
}
char* resbfs_str(RespostSearchBFS *self){

    char *result;
    char *aux;
    result = str_formatted("by %d vertex: \narray of dists:\n\t", self->which_vertex);
    for (int i = 0; i < self->tam_graph-1; ++i) {
        aux = result;
        result = str_formatted("%s%d, ", result, self->dists[i]);
        me_free(aux);
    }
    aux = result;
    result = str_formatted("%s%d.\npass by:\n\t", result, self->dists[self->tam_graph-1]);
    me_free(aux);
    for (int i = 0; i < self->tam_graph-1; ++i) {
        aux = result;
        result = str_formatted("%s%d, ", result, self->pass_by[i]);
        me_free(aux);
    }
    aux = result;
    result = str_formatted("%s%d. \n", result, self->pass_by[self->tam_graph-1]);
    aux = result;
    result = str_formatted("%svisiteds:\n\t", result);
    me_free(aux);
    for (int i = 0; i < self->tam_graph-1; ++i) {

        aux = result;
        result = str_formatted("%s%s, ", mark_visiteds_to_str(self->visiteds[i]));
        me_free(aux);
    }
    aux = result;
    result = str_formatted("%s%s\n", mark_visiteds_to_str(self->visiteds[self->tam_graph-1]));
    return result;
}

LinkedList *resbfs_mount_way_to_vertex(RespostSearchBFS *self, int what_vertex){

    double dist = self->dists[what_vertex];
    LinkedList *way = create_linked_list();
    BaseValue *current_stacked_value = create_base_value(
            create_int(what_vertex), (void *)destroy_int, (void *) me_int_to_str,
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
    current_stacked_value = create_base_value(create_double(dist), (void *)destroy_double, (void *)double_to_str, NULL, sizeof(double));
    lkl_append(way, current_stacked_value);
    return way;
}
int resbfs_exist_a_way_to_vertex(RespostSearchBFS *self, int vertex){
    return self->visiteds[vertex] == already_visited;
}
