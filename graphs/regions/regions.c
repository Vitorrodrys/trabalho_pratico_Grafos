//
// Created by vitor on 07/11/23.
//

#include "regions.h"
#include "../../generic_structs/hash_map/map/hash_map.h"
#include "../../memory/memory.h"
#include "../../generic_structs/list/list.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>

typedef struct InfoAeroports{
    int x_cord;
    int y_cord;
    char *name_city;
    char *region;
}InfoAeroports;

int ifa_get_x_cord(InfoAeroports *self){
    return self->x_cord;
}
int ifa_get_y_cord(InfoAeroports *self){
    return self->y_cord;
}
char *ifa_get_city(InfoAeroports *self){
    return self->name_city;
}
char *ifa_get_region(InfoAeroports *self){
    return self->region;
}

InfoAeroports *create_info_aeroport(char *str){

    List *list =  li_break_str_in_list(str, ",");
    char *cords = li_get_element_in_list(list,0);

    List *sublist = li_break_str_in_list(cords, " ");
    if ( li_get_tam(sublist) != 4 ){
        return NULL;
    }
    InfoAeroports *new = me_memory_alloc(NULL, sizeof(InfoAeroports));
    new->x_cord = atoi(li_get_element_in_list(sublist,1));
    new->y_cord = atoi(li_get_element_in_list(sublist, 2));
    new->name_city = strdup(li_get_element_in_list(sublist, 3));
    new->region = strdup(li_get_element_in_list(list, 1));
    //retired /r by prevent that when needed show the region in display, don't cause conflit with the console
    *strchr(new->region, '\r') = ' ';
    list = destroy_list(list);
    sublist=destroy_list(sublist);
    return new;
}
InfoAeroports *destroy_info_aeroports(InfoAeroports *self){
    me_free(self->name_city);
    me_free(self->region);
    *self = (InfoAeroports){
        .y_cord = 0,
        .x_cord = 0
    };
    me_free(self);
    return NULL;
}
char * info_aeroports_str(InfoAeroports *self){
    return me_formatted_str( " {\n\t\t\"x_cord\":%d,\n\t\t\"y_cord\":%d,\n\t\t\"name_city\":\"%s\",\n\t\t\"region\":\"%s\"\n\t\t}", self->x_cord, self->y_cord, self->name_city, self->region );
}
int info_aeroports_eq(InfoAeroports *self, InfoAeroports *other){

    return self->y_cord == other->y_cord && self->x_cord == other->x_cord && !strcmp(self->region, other->region) && !strcmp(self->name_city, other->name_city);
}
typedef struct Regions{


    Map *aeroports;
    int quantity_aeroports;
}Regions;

InfoAeroports *ifa_get_info_aeroport(Regions *self, char *alias){

    InfoAeroports *aeroport = map_get_value(self->aeroports, alias);
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

Regions *create_regions(CurrentFile *file){

    Regions *new = me_memory_alloc(NULL, sizeof(Regions));
    new->aeroports = create_map(13, NULL);
    new->quantity_aeroports=0;

    pf_advance_to_word(file, "!regions");
    char *str = pf_get_word_until_token(file, '!');
    CurrentFile *regions_str = create_parser_with_txt(str);
    BaseValue *new_value;
    char *alias_region;
    InfoAeroports *info;
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
                sizeof(InfoAeroports)
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
    char *regions_str = me_formatted_str("aeroport regions: %s,\nquantity aeroports:%d", aeroports_in_str, self->quantity_aeroports);
    me_free(aeroports_in_str);
    return regions_str;
}
Regions *destroy_regions(Regions *self){

    self->aeroports = destroy_map(self->aeroports);
    self->quantity_aeroports = 0;
    me_free(self);
    return NULL;
}
