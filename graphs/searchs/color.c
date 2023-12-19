//
// Created by vitor on 29/11/23.
//

#include "color.h"
#include "../../memory/memory.h"
#include <stdio.h>
typedef struct DistColors{

    int *colors_vertexs;
    int size_graph;
    int quantity_colors_usage;

}DistColors;

DistColors *create_dist_colors(int size_graph){

    DistColors *new = me_memory_alloc(NULL, sizeof(DistColors));

    *new = (DistColors){
        .colors_vertexs=me_memory_alloc(NULL, sizeof(int)*size_graph),
        .size_graph = size_graph,
        .quantity_colors_usage = 0
    };
    for (int i = 0; i < size_graph; ++i) {
        new->colors_vertexs[i] = -1;
    }
    return new;
}

DistColors *destroy_dist_colors(DistColors *self){
    me_free(self->colors_vertexs);
    me_free(self);
    return NULL;

}

int dc_get_color_vertex(DistColors *self, int vertex){
    return self->colors_vertexs[vertex];
}


void dc_set_color_vertex(DistColors *self, int vertex, int color){
    self->colors_vertexs[vertex] = color;
    self->quantity_colors_usage += (color < self->quantity_colors_usage)?0:1;
}

int *dc_create_vector_of_avaible_colors(DistColors *self){
    int *disponible_colors = me_memory_alloc(NULL, sizeof(int)* self->size_graph);
    for (int i = 0; i < self->size_graph; ++i) {
        disponible_colors[i] = 1;
    }
    return disponible_colors;
}

int dc_get_quantity_colors_usage(DistColors *self){
    return self->quantity_colors_usage;
}