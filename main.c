#include <stdio.h>
#include "regions/regions.h"
#include "graphs/digraph_routes/digraph_routes.h"
int main() {

    CurrentFile *f = create_parser("../MalhaAereaUSA.txt");
    Regions *re = create_regions(f);
    Alias *alias_ae = create_alias();
    DigraphRoutes *graph = create_graph_routes(alias_ae,  re, f);
    printf(dgrt_str(graph));

    graph = destroy_dgrt(graph);
    return 0;
}
