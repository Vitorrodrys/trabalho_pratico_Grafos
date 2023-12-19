#ifndef REGIONS_H
#define REGIONS_H

#include "../../parser_file/parser_file.h"
#include "info_aeroports.h"
#include "../../generic_structs/hash_map/map/hash_map.h"

typedef struct Regions Regions;
//A TAD that assists the found information of a specified airport. Internally has a hasmap that store keys and values in format
// {"ABQ":InfoAirport}, InfoAirport is another TAD.


/**
 * create a new instance of the TAD from a parser
 * @param file: A parser with the information of a file
 * @return new instance of Regions
 */
Regions *create_regions(CurrentFile *file);



/**
 * clear the Regions of the memory
 * @param self: instance that want clean
 * @return NULL
 */
Regions *destroy_regions(Regions *self);


/**
 * retrieve the information of an airport that the nickname was received as parameter
 * @param self: instance of Regions where is stored the key alias
 * @param alias: nickname of airport that want retrieve
 * @return the complete information about an airport
 */
InfoAirport *re_get_info_aeroport(Regions *self, char *alias);
char *re_str(Regions *self);


/**
 * allow iteration by an instance of Regions, returned an iterator, that have
 * functions has ith_next, that can get the next element of the hashmap the each call
 * @param self: Instance of the Regions that want to iterate
 * @return an object that allow iteration by internally hashmap
 */
ItHash *re_create_iterator_regions(Regions *self);

#endif /* REGIONS_H */
