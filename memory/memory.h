//
// Created by vitor on 07/11/23.
//

#ifndef UNTITLED70_MEMORY_H
#define UNTITLED70_MEMORY_H
#include <stdlib.h>

void me_free_several_objects(int quantity, ...);
void me_free_memory(void **ptr);
void *me_memory_alloc(void *ptr, size_t tam);

#endif //UNTITLED70_MEMORY_H
