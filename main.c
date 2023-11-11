#include <stdio.h>
#include "graphs/regions/regions.h"
#include "graphs/digraph_routes/digraph_routes.h"
#include "graphs/flights_graph/flights_graph.h"
int main() {


    CurrentFile *f = create_parser("../MalhaAereaUSA.txt");
    Regions *re = create_regions(f);
    Alias *alias_ae = create_alias();
    DigraphRoutes *graph = create_graph_routes(alias_ae,  re, f);
    FlightsGraph *fligth = create_flitghs_graph(alias_ae, re, f);
    printf(dgrt_str(graph));
    printf("%s", re_str(re));
    graph = destroy_dgrt(graph);
    destroy_regions(re);
    return 0;
}
