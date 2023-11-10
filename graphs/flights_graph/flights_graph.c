//
// Created by vitor on 09/11/23.
//

#include "../alias/alias.h"
typedef struct FlightsGraph{


    Alias *aeroports_alias;
    int size_graph;
    double **graph;
    int quantity_edge;

}FlightsGraph;