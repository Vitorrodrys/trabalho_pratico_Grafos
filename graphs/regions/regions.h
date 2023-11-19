#ifndef REGIONS_H
#define REGIONS_H

#include "../../parser_file/parser_file.h"
#include "info_aeroports.h"
#include "../../generic_structs/hash_map/map/hash_map.h"

typedef struct Regions Regions;
InfoAeroports *re_get_info_aeroport(Regions *self, char *alias);
Regions *create_regions(CurrentFile *file);
char *re_str(Regions *self);
ItHash *re_create_iterator_regions(Regions *self);
Regions *destroy_regions(Regions *self);
#endif /* REGIONS_H */
