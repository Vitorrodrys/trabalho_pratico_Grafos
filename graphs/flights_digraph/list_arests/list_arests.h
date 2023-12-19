//
// Created by vitor on 13/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_LIST_ARESTS_H
#define TRABALHO_PRATICO_GRAFOS_LIST_ARESTS_H
#include "../info_fligth.h"

typedef struct ListArests ListArests;


ListArests *create_list_arest();
ListArests *destroy_list_arest(ListArests *self);
void la_append(ListArests *self, InfoFligth *value);
void la_remove_arest(ListArests *self, int index);
InfoFligth *la_find_less_element_in_duration(ListArests *self);
InfoFligth *la_find_less_element_in_dist(ListArests *self);
int la_get_tam(ListArests *self);
char *la_str(ListArests *self);
InfoFligth *la_search_flight(ListArests *self, int number_flight);
InfoFligth *la_get_element(ListArests *self, int index);
#endif //TRABALHO_PRATICO_GRAFOS_LIST_ARESTS_H
