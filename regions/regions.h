#ifndef REGIONS_H
#define REGIONS_H

#include "../parser_file/parser_file.h"


typedef struct InfoAeroports InfoAeroports;
int ifa_get_x_cord(InfoAeroports *self);
int ifa_get_y_cord(InfoAeroports *self);
char *ifa_get_city(InfoAeroports *self);
char *ifa_get_region(InfoAeroports *self);
InfoAeroports *destroy_info_aeroports(InfoAeroports *self);

typedef struct Regions Regions;
InfoAeroports *ifa_get_info_aeroport(Regions *self, char *alias);
Regions *create_regions(current_file *file);

#endif /* REGIONS_H */
