//
// Created by vitor on 15/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_INFO_AEROPORTS_H
#define TRABALHO_PRATICO_GRAFOS_INFO_AEROPORTS_H

#include "../searchs/respost_bfs.h"

typedef struct InfoAirport InfoAirport;
//TAD that stored all complete information about an airport









/**
 * parser a string and create a new instance of InfoAirport
 * @param str: string that should be parsed
 * @return new instance of InfoAirport
 */
InfoAirport *create_info_aeroport(char *str);
InfoAirport *destroy_info_aeroports(InfoAirport *self);

/**
 * retrieve the geographic cord X of the airport
 * @param self: Instance of InfoAeroport that want get X cord
 * @return the number that representing the X cord of this airport
 */
int ifa_get_x_cord(InfoAirport *self);




/**
 * retrieve the geographic cord Y of the airport
 * @param self: Instance of InfoAeroport that want get Y cord
 * @return the number that representing the Y cord of this airport
 */
int ifa_get_y_cord(InfoAirport *self);
char *ifa_get_city(InfoAirport *self);
char *ifa_get_region(InfoAirport *self);

char * info_aeroports_str(InfoAirport *self);
int info_aeroports_eq(InfoAirport *self, InfoAirport *other);
size_t ifa_get_tam();
#endif //TRABALHO_PRATICO_GRAFOS_INFO_AEROPORTS_H
