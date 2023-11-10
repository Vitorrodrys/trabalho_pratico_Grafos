//
// Created by vitor on 07/11/23.
//

#ifndef UNTITLED70_MEMORY_H
#define UNTITLED70_MEMORY_H
#include <stdlib.h>
#include <string.h>
void me_free_several_objects(int quantity, ...);
void me_free_memory(void **ptr);
void *me_memory_alloc(void *ptr, size_t tam);
char *me_int_to_str(int number);
char *me_concat_str(char *str, char *other);
char *me_concat_multiplies_str(int quantitys, ...);
char *me_formatted_str(char *control_str, ...);
char *me_str_to_str(char *str);
void *simple_destructor(void *data);
char *multiply_str(char *string, int times);
char *me_formatted_str(char *control_str, ...);
#endif //UNTITLED70_MEMORY_H
