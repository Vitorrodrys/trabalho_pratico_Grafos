//
// Created by vitor on 08/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_ALIAS_H
#define TRABALHO_PRATICO_GRAFOS_ALIAS_H
#include "../../parser_file/parser_file.h"
#include "../../generic_structs/hash_map/iterator/iterator_hash.h"

typedef struct Alias Alias;


int *create_int(int number);
Alias *create_alias();
Alias *destroy_alias(Alias *self);
void alias_add_alias(Alias *self, char *name_alias);
int alias_remove_alias(Alias *self, char *name_alias);
int alias_get_number_by_alias(Alias *self, char *name_alias);
char *alias_get_alias_by_number(Alias *self, int number);
char* alias_str(Alias *self);
ItHash *alias_create_iterator_alias(Alias *self);
int alias_is_void(Alias *self);
#endif //TRABALHO_PRATICO_GRAFOS_ALIAS_H
