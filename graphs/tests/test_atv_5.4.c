//
// Created by vitor on 19/11/23.
//

#include "../graph_airport.h"
#include "../alias/alias.h"
#include "../../generic_structs/hash_map/map/hash_map.h"
#include <stdio.h>

void test_if_is_possible_arrive_to_any_aeroport_from_any_aeroport(GraphAirport *gp){


    ItHash *it = alias_create_iterator_alias(gpae_get_alias(gp));

    KeyValue *i_value = ith_next(it);
    char *k_i;
    char *k_j;
    while ( i_value ){

        k_i = (char *)kv_get_key(i_value);
        printf("%s\n",gpae_get_aeroports_that_do_not_has_path(gp, k_i));

        i_value = ith_next(it);
    }
}