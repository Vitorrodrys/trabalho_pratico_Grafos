//
// Created by vitor on 07/11/23.
//

#include "regions.h"
#include "../hash_map/hash_map.h"
#include "../memory/memory.h"
#include "../list/list.h"
#include <string.h>
#include <ctype.h>


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

    List *list =  break_str_in_list(str, ",");
    char *cords = get_element_in_list(list,0);

    List *sublist = break_str_in_list(cords, " ");
    if ( get_tam(sublist) != 4 ){
        return NULL;
    }
    InfoAeroports *new = me_memory_alloc(NULL, sizeof(InfoAeroports));
    new->x_cord = atoi(get_element_in_list(sublist,1));
    new->y_cord = atoi(get_element_in_list(sublist, 2));
    new->name_city = strdup(get_element_in_list(sublist, 3));
    new->region = strdup(get_element_in_list(list, 1));
    list = destroy_list(list, 2, NULL, NULL);
    sublist=destroy_list(sublist, 4, NULL, NULL, NULL, NULL);
    return new;
}
InfoAeroports *destroy_info_aeroports(InfoAeroports *self){
    me_free_memory((void *)&self->name_city);
    me_free_memory((void *)&self->region);
    *self = (InfoAeroports){
        .y_cord = 0,
        .x_cord = 0
    };
    me_free_memory((void *)&self);
    return NULL;
}

typedef struct regions{


    Map *aeroports;
    int quantity_aeroports;
}regions;

InfoAeroports *ifa_get_info_aeroport(regions *self, char *alias){

    InfoAeroports *aeroport = map_search_key(self->aeroports, alias);
    return aeroport;
}

char *_get_alias_region(current_file *file){

    char *str = me_memory_alloc(NULL, sizeof(char)*4);
    char current_char = get_next_char(file);
    while ( !isalpha(current_char) ) {
        current_char = get_next_char(file);
    }
    str[0] = current_char;
    for (int i = 1; i < 3; ++i) {
        str[i] = get_next_char(file);
    }
    str[3] = '\0';
    return str;
}

regions *create_regions(current_file *file){

    regions *new = me_memory_alloc(NULL, sizeof(regions));
    new->aeroports = create_map(13, NULL);
    new->quantity_aeroports=0;

    advance_to_word(file, "!regions");
    char *str = get_word_until_token(file, '!');
    current_file *regions_str = create_parser_with_txt(str);

    char *alias_region;
    InfoAeroports *info;
    while (!is_end_file(regions_str)){
        alias_region = _get_alias_region(regions_str);
        str = get_word_until_token(regions_str, '\n');
        info = create_info_aeroport(str);
        me_free_memory((void *)&str);

        map_add_key(new->aeroports, alias_region, info);
        new->quantity_aeroports++;

    }

    return new;
}
