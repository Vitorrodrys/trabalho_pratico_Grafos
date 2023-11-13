//
// Created by vitor on 08/11/23.
//

#include "alias.h"
#include "../../generic_structs/hash_map/map/hash_map.h"
#include "../../memory/memory.h"
#include "../../parser_file/parser_file.h"
#include "../../generic_structs/list/list.h"
#include "../../generic_structs/base_value/base_value.h"
#include <stdio.h>
typedef struct Alias{

    Map *alias_name_to_number;
    Map *alias_number_to_name;
    int quantity_alias;
}Alias;

Alias *create_alias(){

    Alias *new = me_memory_alloc(NULL, sizeof(Alias));
    new->alias_name_to_number = create_map(DEFAULT_SIZE_VECTOR_COLISION, NULL);
    new->alias_number_to_name = create_map(DEFAULT_SIZE_VECTOR_COLISION, NULL);
    new->quantity_alias = 0;
    return new;

}
Alias *destroy_alias(Alias *self){

    self->alias_name_to_number = destroy_map(self->alias_name_to_number);
    self->alias_number_to_name = destroy_map(self->alias_number_to_name);
    self->quantity_alias = 0;
    me_free(self);
    return NULL;
}
void alias_add_alias(Alias *self, char *name_alias){

    BaseValue *new_element = create_base_value(create_int(self->quantity_alias), (void *)destroy_int, (void *) me_int_to_str, (void *) me_eq_int, sizeof(int));
    KeyValue *kv = create_key_value( name_alias, new_element);
    if( map_get_value(self->alias_name_to_number, name_alias) ){
        return;
    }
    map_add_key(self->alias_name_to_number, kv);
    char *number_in_str= me_convert_int_to_str(self->quantity_alias);
    new_element = create_base_value(strdup(name_alias), (void *) destroy_str, (void *)me_str_str, (void *)strcmp, sizeof(char));
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
    char *number_return_str = me_convert_int_to_str(number_return);
    map_remove_key(self->alias_number_to_name, number_return_str);
    me_free(number_return_str);
    self->quantity_alias--;
    return number_return;
}
int alias_get_number_by_alias(Alias *self, char *name_alias){

    int *ptr = (int *)map_get_value(self->alias_name_to_number, name_alias);
    return ptr?*ptr:-1;
}
char *alias_get_alias_by_number(Alias *self, int number){

    char *int_in_str = me_convert_int_to_str(number);
    char *value = map_get_value(self->alias_number_to_name, int_in_str);
    me_free(int_in_str);
    return value;
}
ItHash *alias_create_iterator_alias(Alias *self){
    return create_iterator(self->alias_name_to_number);
}

char* alias_str(Alias *self){
    int size;
    char *str_name_to_number = map_str(self->alias_name_to_number);
    char *str_number_to_name = map_str(self->alias_number_to_name);
    return me_formatted_str(
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




