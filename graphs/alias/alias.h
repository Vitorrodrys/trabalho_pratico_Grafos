//
// Created by vitor on 08/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_ALIAS_H
#define TRABALHO_PRATICO_GRAFOS_ALIAS_H
#include "../../parser_file/parser_file.h"
#include "../../generic_structs/hash_map/iterator/iterator_hash.h"
#include "../../generic_structs/linked_list/linked_list.h"
typedef struct Alias Alias;
/**
 * a TAD that has within three hashmaps, one hashmap that stores as keys the nickname and as value the number of the vertex within of the graphs,
 * other hashmap that store the numbers as key and nicknames as value, and other hashmap that store the number flight as key and one list with origin and destiny as value
 *
 */


/**
 * create an instance of TAD of alias
 * @return
 */
Alias *create_alias();



/**
 * clear of the memory an instance of Alias
 * @param self: instance of Alias that want clear
 * @return NULL
 */
Alias *destroy_alias(Alias *self);


/**
 * add a new nickname within of the alias, the number that this nickname will referenced will be
 * generated incrementally, using how reference the quantity of nicknames current, in other words, if when
 * the method was called has 10 nicknames, the current nickname will be saved in the hashmaps how the following:
 * name_alias: 10.
 *
 * in hashmap of numbers to nicks, will be stored how the following:
 *
 * 10: name_alias.
 *
 *
 * @param self: instance of Alias
 * @param name_alias: current nickname that wants add
 */
void alias_add_alias(Alias *self, char *name_alias);


/**
 * add new key and value in hashmap of flights, of the number_flight to one list with from and to, in the following formatted:
 *
 * "number_flight":[from, to] -> this list will be an instance of LinkedList
 *
 * if already exist one key equality the number_flight, return false
 *
 * if from or to don't exist in hashmap of nicknames to vertex, return false
 *
 * in otherwise, return true
 * @param self: instance of alias
 * @param number_flight:number of a flight
 * @param from: nick of the airport that the flight leaving
 * @param to: nick of the destiny airport of the flight
 * @return boolean
 */
int alias_add_flight(Alias *self, int number_flight, char *from, char *to);

/**
 * return the list of origin and destiny of a flight
 * @param self: instance of Alias
 * @param number_flight: number of the flight that want consulting
 * @return one LinkedList
 */
LinkedList *alias_get_from_to_of_a_flight(Alias *self, int number_flight);

/**
 * Remove a nickname from the hashmap of nicknames to vertices, and also remove the corresponding key
 * in the hashmap of vertices to nicknames.
 *
 * @param self: Instance of Alias
 * @param name_alias: Nickname to be removed
 * @return The number of the vertex that was removed if successful, otherwise, -1
 */
int alias_remove_alias(Alias *self, char *name_alias);

/**
 * get the corresponding vertex of a nickname of airport, example:
 * alias_get_number_by_alias(alias, "ABQ") -> 1
 * @param self: instance of Alias
 * @param name_alias: nickname of the airport that want retrieve the corresponding vertex
 * @return -1 if the nickname doesn't have a corresponding vertex, and the value of the corresponding vertex otherwise
 */
int alias_get_number_by_alias(Alias *self, const char *name_alias);

/**
 * get the corresponding nickname of a vertex, example:
 * alias_get_alias_by_number(alias, 1) -> "ABQ"
 * @param self: instance of Alias
 * @param number: number of vertex that want retrieve the corresponding nickname
 * @return a string that contains the nickname of the airport corresponding if have corresponding, NULL in otherwise
 */
char *alias_get_alias_by_number(Alias *self, int number);
char* alias_str(Alias *self);
ItHash *alias_create_iterator_alias(Alias *self);


/**
 * check if don't has nickname registered
 * @param self: instance of Alias
 * @return true if doesn't has nicknames registered in hashmaps, false in otherwise
 */
int alias_is_void(Alias *self);
#endif //TRABALHO_PRATICO_GRAFOS_ALIAS_H
