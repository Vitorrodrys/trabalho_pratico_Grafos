#ifndef LIST_H
#define LIST_H

typedef struct List List;

List *create_list();
void append(List *self, void *element);
void *remove_element(List *self, int index);
int search_index_element(List *self, void *element, int (*is_this_element)(void *, void *));
void *pop(List *self);
void *dequeue(List *self);
int is_void(List *self);
void* destroy_list(List *self, int quantity_destructors, ...);
void *get_element_in_list(List *self, int index);
int get_tam(List *self);
List *break_str_in_list(char *str, char *tok);
#endif /* LIST_H */