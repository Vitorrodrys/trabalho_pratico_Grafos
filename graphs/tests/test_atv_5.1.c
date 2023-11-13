//
// Created by vitor on 12/11/23.
//

#include "test_atv_5.1.h"
#include "../graph_aeroport.h"
#include "../alias/alias.h"
#include "../../generic_structs/hash_map/map/hash_map.h"
#include <stdio.h>
void find_routes_from_all_to_all(CurrentFile *file){

    GraphAeroport *gp_ae = create_graph_aeroport(file);
    ItHash *it = alias_create_iterator_alias(gpae_get_alias(gp_ae));
    ItHash *jt;
    KeyValue *i_current_value = ith_next(it);
    KeyValue *j_current_value;
    char *respost;
    while (i_current_value){

        jt = alias_create_iterator_alias(gpae_get_alias(gp_ae));
        j_current_value = ith_next(jt);
        while (j_current_value){

            respost = gpae_get_route_from_to(gp_ae, kv_get_key(i_current_value), kv_get_key(j_current_value));
            printf(respost);
            j_current_value = ith_next(jt);

        }
        i_current_value = ith_next(it);
    }
}