#include <stdio.h>
#include "graphs/graph_aeroport.h"
#include "graphs/tests/test_atv_5.1.h"
#include "graphs/tests/test_atv_5.2.h"



int main() {


    CurrentFile *f = create_parser("../MalhaAereaUSA.txt");
    GraphAeroport *gp_ae = create_graph_aeroport(f);
    find_all_direct_fligths_from_all_to_all(gp_ae);
    gpae_find_less_fligth_betwen_aeroports(gp_ae, "ABQ", "MSY");

    gp_ae = destroy_graph_aeroport(gp_ae);


    return 0;
}
