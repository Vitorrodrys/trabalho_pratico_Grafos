//
// Created by vitor on 13/11/23.
//

#include "list_arests.h"
#include "../../../memory/memory.h"
#include "../../../generic_structs/list/list.h"
#include "../../../string/string.h"

typedef struct ListArests{
    List *elements;
    int quantity_at;

}ListArests;


ListArests *create_list_arest(){

    ListArests *new = me_memory_alloc(NULL, sizeof(ListArests));
    new->elements = create_list();
    new->quantity_at = 0;
    return new;
}
ListArests *destroy_list_arest(ListArests *self){

    self->elements = destroy_list(self->elements);
    self->quantity_at = 0;
    me_free(self);
    return NULL;
}
int la_get_tam(ListArests *self){
    return self->quantity_at;
}
void la_append(ListArests *self, InfoFligth *value){

    li_append(
            self->elements,
            create_base_value(
                    value,
                    (void *)destroy_info_fligth,
                    (void *)if_str,
                    (void *)if_eq,
                    if_get_tam()
                    )
            );
    self->quantity_at++;
}

void la_remove_arest(ListArests *self, int index){
    BaseValue *removed = li_remove_element(self->elements, index);
    removed = destroy_base_value(removed);
    self->quantity_at--;
}
InfoFligth *la_get_element(ListArests *self, int index){

    if ( index >= self->quantity_at ){
        return NULL;
    }
    return li_get_element_in_list(self->elements,index);
}

InfoFligth *find_less_element(ListArests *self, int (*if_compare_less_element)(InfoFligth* self, InfoFligth* other)){

    InfoFligth *less = li_get_element_in_list(self->elements,0);
    InfoFligth *current_element;
    for (int i = 1; i < self->quantity_at; ++i) {

        current_element = li_get_element_in_list(self->elements, i);
        if ( if_compare_less_element(current_element, less) ){
            less = current_element;
        }
    }
    return less;
}
InfoFligth *la_find_less_element_in_duration(ListArests *self){
    return find_less_element(self, if_less_then_in_duration);
}
InfoFligth *la_find_less_element_in_dist(ListArests *self){
    return find_less_element(self, if_less_then_in_dist);
}
char *la_str(ListArests *self){

    if ( self->quantity_at == 0 ){
        return strdup("don't has flights!");
    }
    InfoFligth *current_element = li_get_element_in_list(self->elements, 0);
    char *result = if_str(current_element);
    char *aux = result;
    char *aux2;
    result = str_formatted("\tfligths:\n\t\t%s.", result);
    me_free(aux);
    for (int i = 1; i < self->quantity_at; ++i) {

        aux = result;
        current_element = li_get_element_in_list(self->elements, i);
        aux2 = if_str(current_element);
        result = str_formatted("%s\n\t\t%s", result, aux2);
        me_free_several_objects(2, &aux, &aux2);
    }
    return result;
}
InfoFligth *la_search_flight(ListArests *self, int number_flight){
    LinkedList *number_fligths;//in the matrix of flights, all the flights any have only one flight in list of flight number,
    //the representing with list only was needs in dijkstra, when make the sum of two InfoFlight, then the number of the instances of InfoFlight are concatenates
    for (int i = 0; i < li_get_tam(self->elements); ++i) {

        number_fligths = ifa_get_number_fligths(li_get_element_in_list(self->elements, i));
        if ( *(int *)lkl_get_data(number_fligths, 0) == number_flight ){
            return li_get_element_in_list(self->elements, i);
        }
    }
    return NULL;
}