//
// Created by vitor on 13/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_DIJKSTRA_H
#define TRABALHO_PRATICO_GRAFOS_DIJKSTRA_H

#include "../flights_digraph/info_fligth.h"
#include "../../generic_structs/linked_list/linked_list.h"
typedef struct Dijkstra Dijkstra;
//A TAD that assists in analyzing the response of a previously executed Dijkstra or can also assist in the process of constructing the Dijkstra response.


//to create one instance of this TAD, is needs call FlightsDigraph *create_flitghs_digraph() in flights_digraph.h

/**
 * clear of the memory an instance of Dijkstra
 * @param self: an instance of Dijkstra
 * @return NULL
 */
Dijkstra *destroy_dijkstra(Dijkstra *self);

/**
 *
 * Find the shortest distance for a vertex that is still open in the instance of Dijkstra. This distance can be in terms of distance or duration,
 * depending on the function pointer passed to the constructor.
 * @param self: Instance of Dijkstra
 * @return The vertex that can be reached with the smallest distance currently.
 */
int dijkstra_find_less_vertex(Dijkstra *self);

/**
 * check if there still exist open vertices
 * @param self: instance of Dijkstra
 * @return true if still exist opened vertex, false in otherwise
 */
int dijkstra_there_are_open_vertex(Dijkstra *self);


/**
 * close a vertex, indicating that it already was visited
 * @param self: instance of Dijkstra
 * @param vertex: vertex that want to close
 */
void dijkstra_close_this_vertex(Dijkstra *self, int vertex);


/**
 * sum the to arrive in 'pass_by' vertex with the 'value_arest', and check if the result is smaller then the old value to arrive in
 * 'which_vertex', if is less, then swap the value to arrive in 'which_vertex' by this value, if don't, then don't make nothing.
 *
 * if don't exist a value to arrive in 'which_vertex' before, then only set the value as the 'value_arest'
 * @param self: instance of Dijkstra
 * @param which_vertex: the vertex that should be added a new value, or updated
 * @param pass_by: by what vertex should pass to arrive in which_vertex
 * @param value_arest: the value of the edge of pass_by to which_vertex
 */
void dijkstra_add_value_arest(Dijkstra *self, int which_vertex, int pass_by,InfoFligth *value_arest);


/**
 * use a BFS ready to mount a way with the less distance of the origin to 'to' vertex
 * @param self: instance of Dijkstra
 * @param to: the vertex that should be the end of path
 * @return A list that contains the sequence of vertices to be visited to go from the origin and reach 'what_vertex,' in reverse order.
 * In other words, starting from 'what_vertex' and going backward, the sequence would be what_vertex, x, y, z, origin_vertex.
 */
LinkedList *dijkstra_mount_less_fligth_from_to(Dijkstra *self, int to);
#endif //TRABALHO_PRATICO_GRAFOS_DIJKSTRA_H
