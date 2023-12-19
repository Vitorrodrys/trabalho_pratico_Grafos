//
// Created by vitor on 11/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_GRAPH_AIRPORT_H
#define TRABALHO_PRATICO_GRAFOS_GRAPH_AIRPORT_H
#include "../parser_file/parser_file.h"
#include "searchs/dijkstra.h"
#include "searchs/color.h"

typedef struct Alias Alias;//struct that encapsulating a hash map for stored the nicknames of the airports

/**
 * Define the main TAD of the current file, providing operations to control the graph of flights and routes.
 */
typedef struct GraphAirport GraphAirport;

/**
 * create the graph that representing the routes and fligths
 * @param file: a parser that contains all data of fligths, routes, and information of the aiport
 * @return
 */
GraphAirport *create_graph_aeroport(CurrentFile *file);
/**
 * destroy a TAD GraphAirport
 * @param self: instance of the TAD that should be cleared of the memory
 * @return
 */
GraphAirport *destroy_graph_aeroport(GraphAirport *self);



/**
 * create a new vertex within of the two graph (routes and fligths), this vertex will be associeted internally with a nickname received as parameter,
 * this nick name will be saved in hashmap of alias in formatted {"name_alias":id_generated}. The id is generated in the order of arrival
 * @param self
 * @param name_alias
 */
void gpae_add_new_vertex(GraphAirport *self, char *name_alias);


//TODO:Check if these functions should be included here or not.
void gpae_remove_vertex(GraphAirport *self, char *name_alias);
int gpae_remove_route(GraphAirport *self, char *from, char *to);
int gpae_remove_fligth(GraphAirport *self, char *from, char *to);

/**
 * adds a new route to the route graph, receives the two alias of the airports that should be includes in route
 * @param self: instance of the GraphAirport that should be included the route
 * @param from: first alias of where the route begins
 * @param to: second alias, where the route ends
 * @return
 */
int gpae_add_new_route(GraphAirport *self, char *from, char *to);

/**
 * Adds a new flight to the flights directed graph. The route of the fligth is calculating using bfs from the routes graph,
 * the route found by BFS is used for the flight.
 * @param self: Instance of the GraphAirport that should be included the fligth
 * @param from: Departure point alias for the flight.
 * @param to: arrival point alias for the flight
 * @param number_stops: stop number that the flight will make
 * @param number_fligth: number of the flight
 * @param departure_time: Time of departure for the flight in the format '958A'
 * @param arrival_time: Time of arrival fot the flight in the format '1200A'
 * @return true  was possible to add the flight, false otherwise. If either 'from' or 'to' alias doesn't exist in the hashmap, then the flight don't is added, and
 * will be return false
 */
int gpae_add_new_fligth(GraphAirport *self, char *from, char *to, int number_stops, int number_fligth, char *departure_time, char *arrival_time);

/**
 * generate a string that representing the instance of the GraphAirport
 * @param self: instance of the GraphAirport
 * @return str
 */
char *gpae_str(GraphAirport *self);


/**
 * get all direct fligths that leaving from an airport
 * @param self: an instance of the an GraphAirport
 * @param name_alias: nickname of the airport
 * @return the string ready to show the user which flights leave this airport
 */
char *gpae_get_alls_direct_fligths_from(GraphAirport *self, char *name_alias);

/**
 * run a bfs in routes graph to get the route of an airport by other airport
 * @param self: instance of the GraphAirport
 * @param alias_from: nickname of the first airport
 * @param alias_to: nickname of the second airport
 * @return the string ready to show the user, abouch the route calculated from an airport to other
 */
char *gpae_get_route_from_to(GraphAirport *self, char *alias_from, char *alias_to);

/**
 * get the internal hashmap of nicknames
 * @param self: instance of the graph airport
 * @return an instance of Alias, which is composed of a hashmap of names to vertex of the graph, other of vertex of the graph to names,
 * and other of numbers of the flights to a list of origen and destiny
 */
Alias *gpae_get_alias(GraphAirport *self);


/**
* get the distance between two airports of the graph of routes that has direct connection
* @param self: Instance of the GraphAirport
* @param from: nickname of the first airport
* @param to: nickname of the second airport
* @return the distance between two airports, if they don't have a connection, then return 0
*/
double gpae_get_distance_betwen_aeports(GraphAirport *self, char *from, char *to);


/**
 * make a bfs to discovery all vertex that are not reachable from vertex received as parameter,
 * if is possible reached in all, then try discovery with a DFS what vertex that if removed will make the that
 * don't be more possible this vertex reach all vertex
 *
 *
 * @param self: Instance of GraphAirport
 * @param from: nickname of the starting vertex of the bfs
 * @return A string containing the names of airports that cannot be reached leaving from 'from'
 */
char *gpae_get_aeroports_that_do_not_has_path(GraphAirport *self, char *from);



/**
 * run a dikstra to discovery the paths with a less distance leaving of a vertex, but get only the information about the less way from.
 * The dijkstra is runned in fligths digraph.
 * a airport received as parameters by other
 * @param self: an instance of graph Airport
 * @param from: nickname of the origin airport
 * @param to: nickname of the destiny airport
 * @return a string that speak the shortest distance in terms of time and distance
 */
char *gpae_find_less_fligth_betwen_aeroports(GraphAirport *self, char *from, char *to);


/**
 * get the description of each airport in json format, in following formmated:
 * "JFK": {
		"x_cord":565,
		"y_cord":130,
		"name_city":"New_York",
		"region":" Kennedy "
		},
 * @param self: instance of GraphAirport
 * @return string
 */
char *gpae_get_regions_in_str(GraphAirport *self);

/**
 * Use DFS to find a path that passes through all airports and returns to the origin
 * @param self: Instance of GraphAirport
 * @param alias_origin: airport of origin of the DFS
 * @return a string that show the path
 */
char *gpae_get_path_that_include_all(GraphAirport *self, char *alias_origin);



/**
 * Display the route used by a flight. Internally, the distance calculation for a flight, e.g., from ABQ to BOS, is performed by executing
 * a BFS on the routes graph. The path found by the search between the two airports is then used to obtain only the distance, stored in the
 * flights graph. To view information about the actual route taken, call this method.
 * @param self: Instance of GraphAirport
 * @param number_flight: Number of the flight for which you want to see the route
 * @return string
 */
char *gpae_get_route_of_a_flight(GraphAirport *self, int number_flight);


char * gpae_coloring_routes_graph(GraphAirport *self, char **name_colors);

void gpae_prim(GraphAirport *self);
#endif //TRABALHO_PRATICO_GRAFOS_GRAPH_AIRPORT_H
