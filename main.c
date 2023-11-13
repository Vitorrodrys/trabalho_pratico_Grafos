#include <stdio.h>
#include "graphs/graph_aeroport.h"
#include "graphs/tests/test_atv_5.1.h"
int main() {


    CurrentFile *f = create_parser("../MalhaAereaUSA.txt");
    find_routes_from_all_to_all(f);
    pf_return_to_file_start(f);
    GraphAeroport *gp_ae = create_graph_aeroport(f);
    char *respost= gpae_get_route_from_to(gp_ae, "HOU", "BOS");
    printf("%s", respost);
    printf(gpae_str(gp_ae));
    gpae_remove_vertex(gp_ae, "HOU");
    printf(gpae_str(gp_ae));
    gp_ae = destroy_graph_aeroport(gp_ae);


    return 0;
}
