//
// Created by vitor on 09/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_FLIGHTS_DIGRAPH_H
#define TRABALHO_PRATICO_GRAFOS_FLIGHTS_DIGRAPH_H
#include "../../parser_file/parser_file.h"
#include "info_fligth.h"
#include "../searchs/dijkstra.h"
#include "../../generic_structs/linked_list/linked_list.h"


typedef struct FlightsDigraph FlightsDigraph;//TAD that helping the handling the flights

/**
 * create a new instance of a matrix of flights
 * @return instance of FLigthsDigraph
 */
FlightsDigraph *create_flitghs_digraph();


/**
 * clear of the memory an instance of flights digraph
 * @param self: instance of the object that want cleaned
 * @return NULL
 */
FlightsDigraph *destroy_fligths_digraph(FlightsDigraph *self);

/**
 * add new column and line within of matrix, for representing a new vertex
 * @param self: instance of the matrix that want add a new vertex
 */
void fldgp_add_new_vertex(FlightsDigraph *self);



/**
 * add new edge in matrix, that representing a flight, within of the object, your matrix is a matrix of lists to can representing the multiples edges of the graph,
 * then when called this method, will adding a new edge within of the list in adjacency self->graph[from][to]
 *
 * @param self: instance of the FlightsDigraph
 * @param from: vertex of origin
 * @param to: vertex of destiny
 * @param value_arest: edge that representing the flight
 */
void fldgp_add_new_arest(FlightsDigraph *self, int from, int to, InfoFligth *value_arest);


/**
 * represents the flights graph how a string
 * @param self:instance of the FlightsDigraph
 * @return string
 */
char *fldgp_str(FlightsDigraph *self);

/**
 * given an origin and destiny and the number flight, get the flight corresponding
 * @param self: instance of the FlightsDigraph
 * @param from: origin
 * @param to: destiny
 * @param number_flight: number of the flight that want get the corresponding flight
 * @return the information about the flight
 */
InfoFligth *fldgp_get_one_flight(FlightsDigraph *self, int from, int to, int number_flight);


/**
 * get the quantity of the edges
 * @param self: instance of the FlightsDigraph
 * @return quantity of the edges
 */
int fldgp_get_quantity_flights(FlightsDigraph *self);

/**
 * create a list of list to stored the direct flights that leaving of from, how the following:
 * [ [{distance, duration, number_flight}, {distance, duration, number_flight}], [{distance, duration, number_flight}]]
 *
 * Internally, each list stores a copy of an edge rather than a reference, ensuring that it is not possible to update the matrix
 * values by reference.
 * @param self: instance of the FlightsDigraph
 * @param from: vertex that must catch all flights leaving it
 * @return LinkedList that contains LinkedList
 */
LinkedList *fldgp_get_direct_fligths_from(FlightsDigraph *self, int from);


/**
 * run dikjstra to find the less flight in terms of distance for each vertex
 * @param self: instance of the FlightsDigraph
 * @param which_vertex: origin vertex
 * @return an instance of Dijkstra that representing a answer for the search
 */
Dijkstra *fldgp_dijkstra_find_less_distance(FlightsDigraph *self, int which_vertex);

/**
 * run dikjstra to find the less flight in terms of duration for each vertex
 * @param self: instance of the FlightsDigraph
 * @param which_vertex: origin vertex
 * @return an instance of Dijkstra that representing a answer for the search
 */
Dijkstra *fldgp_dijkstra_find_less_duration(FlightsDigraph *self, int which_vertex);


void fldgp_del_vertex(FlightsDigraph *self, int vertex);
void fldgp_remove_one_arest(FlightsDigraph *self, int from, int to);
#endif //TRABALHO_PRATICO_GRAFOS_FLIGHTS_DIGRAPH_H
