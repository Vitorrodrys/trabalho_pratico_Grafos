//
// Created by vitor on 07/11/23.
//

#ifndef UNTITLED70_MEMORY_H
#define UNTITLED70_MEMORY_H
#include <stdlib.h>
#include "../list/list.h"
void free_several_objects(int quantity, ...);
void free_memory(void **ptr);
void *memory_alloc(void *ptr, size_t tam);
List *break_str_in_list(char *str, char *tok);
#endif //UNTITLED70_MEMORY_H
