#include "graphs/tests/test_atv_5.1.h"
#include "graphs/tests/test_atv_5.2.h"
#include "graphs/tests/test_atv_5.3.h"
#include "graphs/tests/test_atv_5.4.h"
#include "interface/airport_interface.h"
#include "graphs/graph_airport.h"

void run_tests(){
    CurrentFile *file = create_parser("MalhaAereaUSA.txt");
    GraphAirport *gp = create_graph_aeroport(file);
    pf_return_to_file_start(file);
    find_routes_from_all_to_all(file);
    find_all_direct_fligths_from_all_to_all(gp);
    find_all_less_fligth_from_all_to_all(gp);
    test_if_is_possible_arrive_to_any_aeroport_from_any_aeroport(gp);
}

int main() {

    return airport_interface_main("../MalhaAereaUSA.txt");
}
