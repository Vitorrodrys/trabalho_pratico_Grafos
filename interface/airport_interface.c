//
// Created by vitor on 21/11/23.
//

#include "airport_interface.h"
#include <stdio.h>
#include "stdlib.h"
#include <stdarg.h>
#include "../parser_file/parser_file.h"
#include "input.h"
#include "../string/string.h"
#include "../memory/memory.h"
#include "../graphs/graph_airport.h"
#include "../graphs/searchs/Prim.h"

void menu(int quantity_of_sentences, char *title, char *border_color, char *title_color,...){

    printf(border_color);
    char *border = str_multiply_str("▬", 80);
    printf("%s\n", border);
    printf(title_color);
    printf("\t\t\t\t\t%s\n\n", title);

    printf(COLOR_WHITE);

    char *current_sentence;
    va_list sentences;
    va_start(sentences, quantity_of_sentences);
    for (int i = 0; i < quantity_of_sentences; ++i) {
        current_sentence = va_arg(sentences, char *);
        printf("\t\t%dº: %s.\n", i+1, current_sentence);
    }
    printf("\n");
    printf(border_color);
    printf("%s\n", border);
    me_free(border);
    printf(COLOR_WHITE);

}




int  airport_interface_main(const char *name_file){


    CurrentFile *file = create_parser(name_file);
    if ( file == NULL ){
        fprintf(stderr, "file %s don't exist in file system!", name_file);
        return 1;
    }
    GraphAirport *aiport_graph = create_graph_aeroport(file);
    file = destroy_parser(file);
    int choice = 0;


   gpae_prim(aiport_graph);



    while (choice != 10){

        menu(10, "menu airport", COLOR_GREEN, COLOR_BLUE,
             "show all aiport alias",
             "show path between airports",
             "show all direct flights from a airport",
             "show the flight with less cost flight from one aeroport by other",
             "check if from an airport is possible to arrive in any other",
             "create a circular path from an airport",
             "show a route of a flight",
             "show distance between two airports",
             "coloring routes graph",
             "logout"
             );

        get_number("%d", &choice);

        switch (choice) {

            case 1: {
                char *respost =gpae_get_regions_in_str(aiport_graph);
                printf("\n\n%s\n\n", respost);
                me_free(respost);
                break;
            }

            case 2:{
                char *alias_aiport1;
                char *alias_aiport2;
                char *respost;
                printf("type the alias from first airport: ");
                alias_aiport1 = get_text('\n');
                printf("type the alias from second airport: ");
                alias_aiport2 = get_text('\n');

                respost = gpae_get_route_from_to(aiport_graph, alias_aiport1, alias_aiport2);

                printf("%s", respost);
                me_free_several_objects(3, &respost, &alias_aiport1, &alias_aiport2);
                break;
            }

            case 3:{
                char *alias_aiport;
                char *respost;
                printf("Enter the airport name that you want to see all direct flights by it: ");
                alias_aiport = get_text('\n');

                respost = gpae_get_alls_direct_fligths_from(aiport_graph, alias_aiport);
                printf("%s", respost);
                me_free(alias_aiport);
                me_free(respost);
                break;
            }

            case 4:{

                char *aiport_origen;
                char *aiport_to;
                char *flight_with_less_cost;
                printf("Enter the name of the origin aiport: ");
                aiport_origen = get_text('\n');
                printf("Enter the name of the destin aiport: ");
                aiport_to = get_text('\n');

                flight_with_less_cost = gpae_find_less_fligth_betwen_aeroports(aiport_graph, aiport_origen, aiport_to);
                printf("%s\n", flight_with_less_cost);
                me_free_several_objects(3, &aiport_origen, &aiport_to, &flight_with_less_cost);
                break;

            }

            case 5:{

                printf("Enter with the name of the airport: ");
                char *from_airport = get_text('\n');
                char *respost = gpae_get_aeroports_that_do_not_has_path(aiport_graph, from_airport);
                printf("%s\n", respost);
                me_free(respost);
                me_free(from_airport);
                break;

            }

            case 6:{
                printf("Enter with the name of the airport that should be the origin and destiny of the circular path: ");
                char *what_aeroport = get_text('\n');
                char *respost = gpae_get_path_that_include_all(aiport_graph, what_aeroport);
                printf("%s\n", respost);
                me_free(respost);
                break;
            }
            case 7:{
                int number_flight;
                printf("Enter with number of the flight: ");
                get_number("%d", &number_flight);
                char *respost = gpae_get_route_of_a_flight(aiport_graph, number_flight);
                printf("%s\n", respost);
                me_free(respost);
                break;
            }
            case 8:{
                char *airport_from;
                char *airport_to;
                printf("Enter with the first airport: ");
                airport_from = get_text('\n');
                printf("Enter with the second airport: ");
                airport_to = get_text('\n');
                double dist = gpae_get_distance_betwen_aeports(aiport_graph, airport_from, airport_to);
                if ( dist == 0.0 ){
                    printf("airport %s and %s has don't have a direct connection! "
                           "If you still want to see the distance\nbetween them, access the second topic of the menu\n", airport_from, airport_to);
                    break;
                }
                printf("the distance between %s to %s is %.2f\n", airport_from, airport_to, dist);
                break;
            }
            case 9: {

                char *colors[4] = {
                        "blue",
                        "red",
                        "yellow",
                        "pink"
                };
                char *graph_color = gpae_coloring_routes_graph(aiport_graph, colors);

                printf("%s", graph_color);
                me_free(graph_color);
                break;
            }
            case 10: {
                aiport_graph = destroy_graph_aeroport(aiport_graph);
                break;
            };
            default:
                printf("invalid choice!\n");
        }
    }
    return 0;
}