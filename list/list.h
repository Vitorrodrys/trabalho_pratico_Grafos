#ifndef LIST_H
#define LIST_H

typedef struct List List;

List *create_list();
void li_append(List *self, void *element);
void* li_remove_element(List *self, int index);
int li_search_index_element(List *self, void *element, int (*is_this_element)(void *, void *));
void *li_pop(List *self);
void* li_dequeue(List *self);
void* destroy_list(List *self, int quantity_destructors, ...);
void *li_get_element_in_list(List *self, int index);
int li_is_void(List *self);
int li_get_tam(List *self);
List *li_break_str_in_list(char *str, char *tok);
#endif /* LIST_H */