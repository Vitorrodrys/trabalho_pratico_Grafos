//
// Created by vitor on 08/11/23.
//

#include "alias.h"
#include "../../generic_structs/hash_map/map/hash_map.h"
#include "../../memory/memory.h"
#include "../../string/string.h"
typedef struct Alias{
    Map *alias_name_to_number;//hashmap that store nicknames of airports as keys, and your corresponding vertex as values
    Map *alias_number_to_name;//hashmap that store vertex of the graph as keys, and your corresponding nicknames as values
    Map *alias_flight_vertex;//hashmap that store flight numbers as key, and one list of your corresponding origin and destiny as values
    int quantity_alias;//quantity of nicknames registered
}Alias;

Alias *create_alias(){

    Alias *new = me_memory_alloc(NULL, sizeof(Alias));
    new->alias_name_to_number = create_map(29, NULL);//the size of the colision list was changed as 26 because is approximately the quantity of airports
    new->alias_number_to_name = create_map(29, NULL);
    new->alias_flight_vertex = create_map(811, NULL);//the size of the colision list was changed as 800 because is approximately the quantity of flights
    new->quantity_alias = 0;
    return new;

}
Alias *destroy_alias(Alias *self){

    self->alias_name_to_number = destroy_map(self->alias_name_to_number);
    self->alias_number_to_name = destroy_map(self->alias_number_to_name);
    self->alias_flight_vertex = destroy_map(self->alias_flight_vertex);
    self->quantity_alias = 0;
    me_free(self);
    return NULL;
}
void alias_add_alias(Alias *self, char *name_alias){

    //create a BaseValue, with the data will be a pointer to int that
    //has the number of the vertex that corresponding at name_alias
    BaseValue *new_element = create_base_value(
            create_int(self->quantity_alias),
            (void *)destroy_int,
            (void *) me_int_to_str,
            (void *) me_eq_int,
            sizeof(int)
    );
    //create a keyvalue with a key as the namealias, and the value as new_element
    KeyValue *kv = create_key_value( name_alias, new_element);
    //if already exist one keyvalue with the same key and value, return without make nothing
    if( map_get_value(self->alias_name_to_number, name_alias) ){
        return;
    }
    //otherwise, add the key
    map_add_key(self->alias_name_to_number, kv);

    //do the same to store in hashmap of vertex to nicknames, but use the number as key
    char *number_in_str= convert_int_to_str(self->quantity_alias);
    new_element = create_base_value(strdup(name_alias), (void *) destroy_str, (void *)str_str, (void *)strcmp, sizeof(char));
    kv = create_key_value(number_in_str, new_element);
    map_add_key(self->alias_number_to_name, kv);
    self->quantity_alias++;
}


int alias_remove_alias(Alias *self, char *name_alias){

    int *number = map_get_value(self->alias_name_to_number, name_alias);

    if ( !number ){
        return -1;
    }
    int number_return = alias_get_number_by_alias(self, name_alias);
    map_remove_key(self->alias_name_to_number, name_alias);
    char *number_return_str = convert_int_to_str(number_return);
    map_remove_key(self->alias_number_to_name, number_return_str);
    me_free(number_return_str);
    self->quantity_alias--;
    return number_return;
}
int alias_add_flight(Alias *self, int number_flight, char *from, char *to){

    //convert the number received to string, because the keys of the hashmap
    //only can be strings
    char *number_flight_str = convert_int_to_str(number_flight);

    if ( map_get_value(self->alias_flight_vertex, number_flight_str) != NULL ){
        return 0;
    }
    int from_vertex = alias_get_number_by_alias(self, from);
    int to_vertex = alias_get_number_by_alias(self, to);

    if ( from_vertex == -1 || to_vertex == -1 ){
        return 0;
    }
    LinkedList *list_from_to = create_linked_list();
    //store the origin of the flight within of the list_from_to
    lkl_append(
            list_from_to,
            create_base_value(
                    create_int(from_vertex),
                    (void *)destroy_int,
                    (void *)me_int_to_str,
                    (void *)me_eq_int,
                    sizeof(int)
                )
    );
    //store of the destiny of the flight within of the list_from_to
    lkl_append(
            list_from_to,
            create_base_value(
                    create_int(to_vertex),
                    (void *)destroy_int,
                    (void *)me_int_to_str,
                    (void *)me_eq_int,
                    sizeof(int)
            )
    );
    //create one KeyValue that the key will be the number of the flight converted to str
    //and the value will be the list_from_to
    KeyValue *kv = create_key_value(
            number_flight_str,
            create_base_value(
                    list_from_to,
                    (void *)destroy_lkl,
                    (void *)lkl_str,
                    (void *)lkl_eq,
                    lkl_get_size()
                    )
            );
    //add this key_value within of the hashmap
    map_add_key(self->alias_flight_vertex, kv);
    me_free(number_flight_str);
    return 1;

}
LinkedList *alias_get_from_to_of_a_flight(Alias *self, int number_flight){

    //convert the number received to string, because the keys of the hashmap
    //only can be strings, then is needs pass a string for the hashmap consulting if exist this key
    char *number_flight_str = convert_int_to_str(number_flight);
    LinkedList *from_to = map_get_value(self->alias_flight_vertex, number_flight_str);
    me_free(number_flight_str);
    return from_to;

}
int alias_get_number_by_alias(Alias *self, const char *name_alias){

    //internally, the hashmap only store pointer as value of the keys, then is needed to receive the value
    //to a pointer to int
    int *ptr = (int *)map_get_value(self->alias_name_to_number, name_alias);
    return ptr?*ptr:-1;
}
char *alias_get_alias_by_number(Alias *self, int number){

    char *int_in_str = convert_int_to_str(number);//convert the number received to string, because the keys of the hashmap
    //only can be strings, then is needs pass a string for the hashmap consulting if exist this key

    char *value = map_get_value(self->alias_number_to_name, int_in_str);
    me_free(int_in_str);
    return value;
}
ItHash *alias_create_iterator_alias(Alias *self){
    return create_iterator(self->alias_name_to_number);
}

char* alias_str(Alias *self){
    char *str_name_to_number = map_str(self->alias_name_to_number);
    char *str_number_to_name = map_str(self->alias_number_to_name);
    return str_formatted(
            "\n\tquantity_alias: %d\n\tnames_to_number: %s,\n\tnumbers_to_names:%s\n",
            self->quantity_alias,
            str_name_to_number,
            str_number_to_name);

}

int alias_get_quantity_alias(Alias *self){
    return self->quantity_alias;
}

int alias_is_void(Alias *self){
    return map_is_void(self->alias_name_to_number) && map_is_void(self->alias_number_to_name);
}




