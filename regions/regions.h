#ifndef REGIONS_H
#define REGIONS_H

#include "../parser_file/parser_file.h"


typedef struct InfoAeroports InfoAeroports;
int get_x_cord(InfoAeroports *self);
int get_y_cord(InfoAeroports *self);
char *get_city(InfoAeroports *self);
char *get_region(InfoAeroports *self);
InfoAeroports *destroy_info_aeroports(InfoAeroports *self);

typedef struct regions regions;
InfoAeroports *get_info_aeroport(regions *self, char *alias);
regions *create_regions(current_file *file);

#endif /* REGIONS_H */
