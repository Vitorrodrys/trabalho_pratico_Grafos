//
// Created by vitor on 15/11/23.
//

#include "info_aeroports.h"
#include "../../memory/memory.h"
#include "../../generic_structs/list/list.h"
#include "../../string/string.h"

typedef struct InfoAirport{
    int x_cord;
    int y_cord;
    char *name_city;
    char *region;
}InfoAirport;

size_t ifa_get_tam(){
    return sizeof(InfoAirport);
}

int ifa_get_x_cord(InfoAirport *self){
    return self->x_cord;
}
int ifa_get_y_cord(InfoAirport *self){
    return self->y_cord;
}
char *ifa_get_city(InfoAirport *self){
    return self->name_city;
}
char *ifa_get_region(InfoAirport *self){
    return self->region;
}

InfoAirport *create_info_aeroport(char *str){

    List *list =  li_break_str_in_list(str, ",");
    char *cords = li_get_element_in_list(list,0);

    List *sublist = li_break_str_in_list(cords, " ");
    if ( li_get_tam(sublist) != 4 ){
        return NULL;
    }
    InfoAirport *new = me_memory_alloc(NULL, sizeof(InfoAirport));
    new->x_cord = atoi(li_get_element_in_list(sublist,1));
    new->y_cord = atoi(li_get_element_in_list(sublist, 2));
    new->name_city = strdup(li_get_element_in_list(sublist, 3));
    new->region = strdup(li_get_element_in_list(list, 1));
    //retired /r to prevent that when needs showed the region in display, don't cause conflicts with the console
    *strchr(new->region, '\r') = ' ';
    list = destroy_list(list);
    sublist=destroy_list(sublist);
    return new;
}
InfoAirport *destroy_info_aeroports(InfoAirport *self){
    me_free(self->name_city);
    me_free(self->region);
    *self = (InfoAirport){
            .y_cord = 0,
            .x_cord = 0,
    };
    me_free(self);
    return NULL;
}
char * info_aeroports_str(InfoAirport *self){
    return str_formatted( " {\n\t\t\"x_cord\":%d,\n\t\t\"y_cord\":%d,\n\t\t\"name_city\":\"%s\",\n\t\t\"region\":\"%s\"\n\t\t}", self->x_cord, self->y_cord, self->name_city, self->region );
}
int info_aeroports_eq(InfoAirport *self, InfoAirport *other){

    return self->y_cord == other->y_cord && self->x_cord == other->x_cord && !strcmp(self->region, other->region) && !strcmp(self->name_city, other->name_city);
}