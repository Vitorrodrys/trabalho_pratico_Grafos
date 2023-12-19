//
// Created by vitor on 07/11/23.
//

#include "regions.h"
#include "../../memory/memory.h"
#include "../../string/string.h"
#include <ctype.h>
#include "info_aeroports.h"
typedef struct Regions{
    Map *aeroports;
    int quantity_aeroports;
}Regions;

InfoAirport *re_get_info_aeroport(Regions *self, char *alias){

    InfoAirport *aeroport = map_get_value(self->aeroports, alias);
    return aeroport;
}

char *_get_alias_region_in_file(CurrentFile *file){

    char *str = me_memory_alloc(NULL, sizeof(char)*4);
    char current_char = pf_get_next_char(file);
    while ( !isalpha(current_char) ) {
        current_char = pf_get_next_char(file);
    }
    str[0] = current_char;
    for (int i = 1; i < 3; ++i) {
        str[i] = pf_get_next_char(file);
    }
    str[3] = '\0';
    return str;
}

ItHash *re_create_iterator_regions(Regions *self){
    return create_iterator(self->aeroports);
}

Regions *create_regions(CurrentFile *file){

    Regions *new = me_memory_alloc(NULL, sizeof(Regions));
    new->aeroports = create_map(DEFAULT_SIZE_VECTOR_COLISION, NULL);
    new->quantity_aeroports=0;

    pf_advance_to_word(file, "!regions");
    char *str = pf_get_word_until_token(file, '!');
    CurrentFile *regions_str = create_parser_with_txt(str);
    BaseValue *new_value;
    char *alias_region;
    InfoAirport *info;
    while (!pf_is_end_file(regions_str)){
        alias_region = _get_alias_region_in_file(regions_str);
        str = pf_get_word_until_token(regions_str, '\n');
        info = create_info_aeroport(str);
        me_free(str);
        new_value = create_base_value(
                info,
                (void *)destroy_info_aeroports,
                (void *)info_aeroports_str,
                (void *)info_aeroports_eq,
                ifa_get_tam()
                );
        map_add_key(
                new->aeroports,
                create_key_value(alias_region, new_value )
        );
        new->quantity_aeroports++;
        pf_get_next_char(regions_str);

    }

    return new;
}
char *re_str(Regions *self){
    char *aeroports_in_str = map_str(self->aeroports);
    char *regions_str = str_formatted("aeroport regions: %s,\nquantity aeroports:%d", aeroports_in_str, self->quantity_aeroports);
    me_free(aeroports_in_str);
    return regions_str;
}
Regions *destroy_regions(Regions *self){
    self->aeroports = destroy_map(self->aeroports);
    self->quantity_aeroports = 0;
    me_free(self);
    return NULL;
}
