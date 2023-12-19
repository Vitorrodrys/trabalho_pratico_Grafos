//
// Created by vitor on 29/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_COLOR_H
#define TRABALHO_PRATICO_GRAFOS_COLOR_H

typedef struct DistColors DistColors;


int dc_get_color_vertex(DistColors *self, int vertex);
DistColors *create_dist_colors(int size_graph);
int *dc_create_vector_of_avaible_colors(DistColors *self);
void dc_set_color_vertex(DistColors *self, int vertex, int color);
int dc_get_quantity_colors_usage(DistColors *self);
#endif //TRABALHO_PRATICO_GRAFOS_COLOR_H
