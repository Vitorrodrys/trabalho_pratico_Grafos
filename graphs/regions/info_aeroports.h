//
// Created by vitor on 15/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_INFO_AEROPORTS_H
#define TRABALHO_PRATICO_GRAFOS_INFO_AEROPORTS_H

#include "../searchs/repost_search.h"

typedef struct InfoAeroports InfoAeroports;
int ifa_get_x_cord(InfoAeroports *self);
int ifa_get_y_cord(InfoAeroports *self);
char *ifa_get_city(InfoAeroports *self);
char *ifa_get_region(InfoAeroports *self);
InfoAeroports *destroy_info_aeroports(InfoAeroports *self);
RespostSearch *ifa_get_result_bfs(InfoAeroports *self);
InfoAeroports *create_info_aeroport(char *str);
char * info_aeroports_str(InfoAeroports *self);
int info_aeroports_eq(InfoAeroports *self, InfoAeroports *other);
size_t ifa_get_tam();
void ifa_set_bfs(InfoAeroports *self, RespostSearch *new_bfs);
#endif //TRABALHO_PRATICO_GRAFOS_INFO_AEROPORTS_H
