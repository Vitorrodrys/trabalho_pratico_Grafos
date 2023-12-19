
#include "test_atv_5.1.h"
#include "../graph_airport.h"
#include "../alias/alias.h"
#include "../../generic_structs/hash_map/map/hash_map.h"
#include <stdio.h>
void find_all_direct_fligths_from_all_to_all(GraphAirport *gp_ae){

    ItHash *it = alias_create_iterator_alias(gpae_get_alias(gp_ae));
    KeyValue *i_current_value = ith_next(it);
    while (i_current_value){
        printf("%s", gpae_get_alls_direct_fligths_from(gp_ae, (char *)kv_get_key(i_current_value)));
        i_current_value = ith_next(it);
        fgetc(stdin);

    }
}