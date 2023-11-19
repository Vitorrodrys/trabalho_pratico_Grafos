#ifndef LIST_H
#define LIST_H

#include "../base_value/base_value.h"

typedef struct List List;

List *create_list();
List* destroy_list(List *self);
void li_append(List *self, BaseValue *element);
BaseValue *li_remove_element(List *self, int index);
int li_search_index_element(List *self, BaseValue *element);
void *li_pop(List *self);
void* li_dequeue(List *self);
void *li_get_element_in_list(List *self, int index);
int li_is_void(List *self);
int li_get_tam(List *self);
List *li_break_str_in_list(char *str, char *tok);
void li_swap_elements(List *self, int index1, int index2);
void li_insert(List *self, BaseValue *value, int index);
#endif /* LIST_H */