//
// Created by vitor on 12/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_REPOST_SEARCH_H
#define TRABALHO_PRATICO_GRAFOS_REPOST_SEARCH_H
#include "../../generic_structs/linked_list/linked_list.h"

typedef struct RespostSearch RespostSearch;

RespostSearch *create_respost(int tam_graph, int which_vertex);
RespostSearch *destroy_respost(RespostSearch *self);
int res_to_visite_element(RespostSearch *self, int from, int to, double dist);
int res_get_next_vertex_queue(RespostSearch *self);
int res_queue_is_void(RespostSearch *self);
int res_elem_still_not_visited(RespostSearch *self, int elem);
char *res_str(RespostSearch *self);
LinkedList *res_mount_way_by_vertex(RespostSearch *self, int what_vertex);
#endif //TRABALHO_PRATICO_GRAFOS_REPOST_SEARCH_H
