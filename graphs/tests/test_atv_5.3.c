//
// Created by vitor on 19/11/23.
//

#include "test_atv_5.3.h"
#include "../graph_airport.h"
#include "../alias/alias.h"
#include "../../generic_structs/hash_map/map/hash_map.h"
#include <stdio.h>
void find_all_less_fligth_from_all_to_all(GraphAirport *gp_ae){

    ItHash *it = alias_create_iterator_alias(gpae_get_alias(gp_ae));
    ItHash *jt = alias_create_iterator_alias(gpae_get_alias(gp_ae));
    KeyValue *i_current_value = ith_next(it);
    KeyValue *j_current_value;
    while (i_current_value){

        j_current_value = ith_next(jt);
        while ( j_current_value ){
            printf("%s", gpae_find_less_fligth_betwen_aeroports(gp_ae, (char *)kv_get_key(i_current_value), (char *) kv_get_key(j_current_value)));
            j_current_value = ith_next(jt);
        }
        i_current_value = ith_next(it);

    }
}