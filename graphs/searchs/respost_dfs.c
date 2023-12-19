//
// Created by vitor on 20/11/23.
//

#include "respost_dfs.h"
#include "../../memory/memory.h"
#include <float.h>
#include "../../string/string.h"
#include "stdio.h"

typedef struct RespostSearchDFS{
    int which_vertex;//origin vertex of the BFS
    int quantity_vertex;//quantity of vertex of the graph that will be realized the BFS
    double *dists;//the vector can show the distance of a vertex X to origin, the position X 'dists[X]' represents the distance
    int *pass_by;//This vector can indicate the predecessor vertex of another vertex; pass_by[other_vertex] will have this information
    LinkedList *stack; //stack of elements that are being visiting
    LinkedList *path_traveled;//list that stored a path that pass by all vertexes
    double dist_path_traveld_by_dfs;//distance of path that pass by all vertexes
    short *already_visited;//vector that can indicate if a vertex already visited by dfs or don't
    int ignored_vertex;//vertex that will be ignored by search
}RespostSearchDFS;

RespostSearchDFS *create_respost_dfs(int which_vertex, int quantity_vertex_graph, int ignored_vertex){

    RespostSearchDFS *new = me_memory_alloc(NULL, sizeof(RespostSearchDFS));

    *new = (RespostSearchDFS){
        .which_vertex = which_vertex,//define the origin of the search
        .quantity_vertex = quantity_vertex_graph,//set the quantity of vertex of the graph
        .dists = me_memory_alloc(NULL, sizeof(double)*quantity_vertex_graph),//allocate the distance vector
        .pass_by = me_memory_alloc(NULL, sizeof(int)*quantity_vertex_graph),//allocate the vector of precedents
        .stack = create_linked_list(),//create the stack to help in the walking process
        .already_visited = me_memory_alloc(NULL, sizeof(short)*quantity_vertex_graph),//allocate the boolean vector that speak if one vertex was visited or not
        .path_traveled = create_linked_list(),//create the list that will store the path that the DFS walking
        .ignored_vertex = ignored_vertex
    };
    //the stack starts with one element, will be this element the vertex of the origin
    lkl_append(
            new->stack,
            create_base_value(
                    create_int(which_vertex),
                    (void *)destroy_int,
                    (void *) me_int_to_str,
                    (void *)me_eq_int,
                    sizeof(int)
                    )
            );
    //for each vertex of the graph
    for (int i = 0; i < quantity_vertex_graph; ++i) {
        new->dists[i] = DBL_MAX;//set the distance as infinity
        new->pass_by[i] = -1;//put the precedent this how undefined
        new->already_visited[i] = 0;//put that don't was visited
    }

    new->dists[which_vertex] = 0;//define the distance by origin how 0
    new->pass_by[which_vertex] = which_vertex;//define that the precedent of the origin is itself
    new->already_visited[which_vertex] = 1;//define that the origin was already visited
    //insert the origin in the path traveled by DFS
    lkl_append(
            new->path_traveled,
            create_base_value(
                    create_int(which_vertex),
                    (void *)destroy_int,
                    (void *)me_int_to_str,
                    (void *)me_eq_int,
                    sizeof(int)
                    )
            );
    new->dist_path_traveld_by_dfs = 0;//the final distance that was make by DFS is starts with 0
    return new;
}
RespostSearchDFS *destroy_respost_dfs(RespostSearchDFS *self){

    me_free_several_objects(3, &self->dists, &self->already_visited, &self->pass_by);
    *self = (RespostSearchDFS){
        .stack = destroy_lkl(self->stack),
        .which_vertex = 0,
        .quantity_vertex = 0,
        .path_traveled = destroy_lkl(self->path_traveled),
        .dist_path_traveld_by_dfs = 0,
        .ignored_vertex = 0
    };
    me_free(self);
    return NULL;
}

int resdfs_get_last_vertex_stack(RespostSearchDFS *self){
    int last_vertex = *(int *)lkl_get_data(self->stack, lkl_get_tam(self->stack)-1);
    return last_vertex;
}
double resdfs_get_dist_traveled(RespostSearchDFS *self){
    return self->dist_path_traveld_by_dfs;
}

int resdfs_get_tam_stack(RespostSearchDFS *self){
    return lkl_get_tam(self->stack);
}

LinkedList *resdfs_get_path_traveled(RespostSearchDFS *self){

    int size_path = lkl_get_tam(self->path_traveled);
    LinkedList *path = create_linked_list();

    int current_element;
    for (int i = 0; i < size_path; ++i) {

        current_element = *(int *)lkl_get_data(self->path_traveled, i);
        lkl_append(
                path,
                create_base_value(
                        create_int(current_element),
                        (void *)destroy_int,
                        (void *)me_int_to_str,
                        (void *)me_eq_int,
                        sizeof(int)
                        )
                );

    }
    return path;
}

void resdfs_to_visite_vertex(RespostSearchDFS *self, int to_vertex, int pass_by, double dist){

    if ( self->quantity_vertex < to_vertex || self->quantity_vertex < pass_by ){
        fprintf(stderr, "Passed one vertex that is beyond the bounds of the index of the vertex. to:%d, pass_by:%d\n", to_vertex, pass_by);
        exit(1);
    }

    BaseValue *new_value = create_base_value(
            create_int(to_vertex),
            (void *)destroy_int,
            (void *) me_int_to_str,
            (void *)me_eq_int,
            sizeof(int)
            );

    lkl_append(self->stack, new_value);
    self->pass_by[to_vertex] = pass_by;
    self->dists[to_vertex] = dist + self->dists[pass_by];
    self->already_visited[to_vertex] = 1;
    lkl_append(
            self->path_traveled,
            create_base_value(
                    create_int(to_vertex),
                    (void *)destroy_int,
                    (void *)me_int_to_str,
                    (void *)me_eq_int,
                    sizeof(int)
            )
    );
    self->dist_path_traveld_by_dfs+=dist;
}
int resdfs_pop_vertex(RespostSearchDFS *self){
    BaseValue *last_element = lkl_pop(self->stack);
    int element = *bv_get_data_convert(last_element, int *);
    last_element = destroy_base_value(last_element);
    if ( self->pass_by[element] == element ) {
        //if pass_by[element] returned the own element, then the element is the origen, and return the element,
        // because don't is needed includes two times the vertex in path_traveled
        return element;
    }
    //How the last vertex was unstacked from the stack; this means that the recursion has backed up one vertex. Then, store the path of the back in path_traveled.
    lkl_append(
            self->path_traveled,
            create_base_value(
                    create_int(self->pass_by[element]),
                    (void *)destroy_int,
                    (void *)me_int_to_str,
                    (void *)me_eq_int,
                    sizeof(int)
                    )
            );
    //att the distance of the path that pass by all vertex
    self->dist_path_traveld_by_dfs+=(self->dists[element]-self->dists[self->pass_by[element]]);
    return element;
}

int resdfs_exist_element_in_stack(RespostSearchDFS *self, int element){

    if ( element >= self->quantity_vertex ){
        return 0;
    }

    BaseValue *new_value = create_base_value(
            create_int(element),
            (void *)destroy_int,
            (void *) convert_int_to_str,
            (void *)me_eq_int,
            sizeof(int)
    );
    int respost = lkl_get_index_element(self->stack, new_value);
    new_value = destroy_base_value( new_value);
    return respost != -1;
}
int resdfs_element_already_visited(RespostSearchDFS *self, int vertex){
    return self->already_visited[vertex] || vertex == self->ignored_vertex;
}


LinkedList *resdfs_cp_stack(RespostSearchDFS *self){

    LinkedList *cp_list = create_linked_list();
    int size_stack = lkl_get_tam(self->stack);
    int current_value;
    BaseValue *current_bv;
    for (int i = 0; i < size_stack; ++i) {
        current_value = *(int *)lkl_get_data(self->stack, i);
        current_bv = create_base_value(
                create_int(current_value),
                (void *)destroy_int,
                (void *) me_int_to_str,
                (void *)me_eq_int,
                sizeof(int)
                );

        lkl_append(cp_list, current_bv);
    }
    return cp_list;
}
int resdfs_stack_is_void(RespostSearchDFS *self){
    return lkl_is_void(self->stack);
}

int resdfs_exist_vertex_not_visited(RespostSearchDFS *self){

    for (int i = 0; i < self->quantity_vertex; ++i) {
        if ( self->already_visited[i] == 0 && i!=self->ignored_vertex){
            return 1;
        }
    }
    return 0;
}

LinkedList *resdfs_mount_way_by_vertex(RespostSearchDFS *self, int what_vertex){

    if ( what_vertex >= self->quantity_vertex ){
        return NULL;
    }

    double dist = self->dists[what_vertex];
    LinkedList *way = create_linked_list();
    BaseValue *current_stacked_value = create_base_value(
            create_int(what_vertex), (void *)destroy_int, (void *) convert_int_to_str,
            (void *)me_eq_int, sizeof(int)
    );
    lkl_append(way, current_stacked_value);
    int current_vertex = self->pass_by[what_vertex];

    if ( current_vertex == -1 ){
        return NULL;
    }
    while ( current_vertex != self->which_vertex ){

        current_stacked_value = create_base_value(
                create_int(current_vertex), (void *)destroy_int, (void *) convert_int_to_str,
                (void *) me_eq_int, sizeof(int)
        );

        lkl_append(way,current_stacked_value);

        current_vertex = self->pass_by[current_vertex];
    }

    current_stacked_value = create_base_value(create_double(dist), (void *)destroy_double, NULL, NULL, sizeof(double));
    lkl_append(way, current_stacked_value);
    return way;
}