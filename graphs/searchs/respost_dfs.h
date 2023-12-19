//
// Created by vitor on 20/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_RESPOST_DFS_H
#define TRABALHO_PRATICO_GRAFOS_RESPOST_DFS_H
#include "../../generic_structs/linked_list/linked_list.h"
#define NOT_IGNORE_ANY_VERTICES -1


typedef struct  RespostSearchDFS RespostSearchDFS; // TAD that help the parsing the respost of a DFS within of a graph



/**
 * to construct an instance this TAD, call grt_dfs() of the graph_routes.h
 */


/**
 * clear a instance of RespostSearchDFS of the memory
 * @param self: instance of the object
 * @return NULL
 */
RespostSearchDFS *destroy_respost_dfs(RespostSearchDFS *self);


/**
 *
 * include a to_vertex how as visited, stack the to_vertex in stack of the TAD,
 * mark that for arrive in to_vertex is pass by 'pass_by', set that the distance of the origin
 * by to_vertex is the distance for 'pass_by' + 'dist', and append the to_vertex how more one vertex of the path that
 * include all
 * @param self: instance of the RespostSearchDFS
 * @param to_vertex: vertex that is being visited
 * @param pass_by: by what vertex that was needs pass for arrived the 'to_vertex'
 * @param dist: the distance of pass-by to 'to-vertex'
 */
void resdfs_to_visite_vertex(RespostSearchDFS *self, int to_vertex, int pass_by, double dist);

/**
 * to retire the last vertex on the stack, and store the path of the back in path_traveled
 * @param self: Instance of the RespostSearchDFS
 * @return the element unstacked
 */
int resdfs_pop_vertex(RespostSearchDFS *self);

/**
 * check if already exist one element in stack
 * @param self: Instance of the RespostSearchDFS
 * @param element: element that want check if already exist
 * @return true if the element exists, and false otherwise.
 */
int resdfs_exist_element_in_stack(RespostSearchDFS *self, int element);


/**
 * get the current size of the stack within of Instance of RespostSearchDFS
 * @param self: instance of RespostSearchDFS
 * @return the current size of the stack
 */
int resdfs_get_tam_stack(RespostSearchDFS *self);

/**
 * make a deep copy of the stack of the instance of RespostSearchDFS
 * @param self: Instance of RespostSearchDFS
 * @return a new instance of LinkedList with the same elements presents in stack of RespostSearchDFS
 */
LinkedList *resdfs_cp_stack(RespostSearchDFS *self);

/**
 * check if the stack within of the instance of RespostSearchDFS is empity
 * @param self: Instance of RespostSearchDFS
 * @return true if the stack is void, and false otherwise
 */
int resdfs_stack_is_void(RespostSearchDFS *self);


/**
 * only get the last vertex of the stack, without unstacked the element
 * @param self: instance of RespostSearchDFS
 * @return the element
 */
int resdfs_get_last_vertex_stack(RespostSearchDFS *self);


/**
 * check if one vertex already visited by DFS
 * @param self: instance of RespostSearchDFS
 * @param vertex: the vertex of needs be verificated
 * @return true if already visited, and false otherwise
 */
int resdfs_element_already_visited(RespostSearchDFS *self, int vertex);

/**
 * mount a way of the origin vertex to what_vertex, consulting the respost internally that
 * the DFS generated
 * @param self: instance of RespostSearchDFS
 * @param what_vertex: to what vertex that should be the path
 * @return A list that contains the sequence of vertices to be visited to go from the origin and reach 'what_vertex,' in reverse order.
 * In other words, starting from 'what_vertex' and going backward, the sequence would be what_vertex, x, y, z, origin_vertex.
 */
LinkedList *resdfs_mount_way_by_vertex(RespostSearchDFS *self, int what_vertex);


/**
 * Obtain the distance of the path that passes by all vertices
 * @param self: instance of RespostSearchDFS
 * @return double
 */
double resdfs_get_dist_traveled(RespostSearchDFS *self);

/**
 * get a copy of the List that contains the path that pass by all vertex
 * @param self: Instance of RespostSearchDFS
 * @return a new instance of the List that contains the same elements that the list within of self that store the path that include all vertex
 */
LinkedList *resdfs_get_path_traveled(RespostSearchDFS *self);

/**
 * check if exist some vertex that don't was visited by search
 * @param self:: instance of RespostSearchDFS
 * @return true if exist a vertex that don't was visited, false otherwise
 */
int resdfs_exist_vertex_not_visited(RespostSearchDFS *self);
#endif //TRABALHO_PRATICO_GRAFOS_RESPOST_DFS_H
