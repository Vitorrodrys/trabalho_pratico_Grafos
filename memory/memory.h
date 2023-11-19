//
// Created by vitor on 07/11/23.
//

#ifndef UNTITLED70_MEMORY_H
#define UNTITLED70_MEMORY_H
#include <stdlib.h>
#include <string.h>
#define me_free(pointer) \
me_free_memory((void **)&(pointer))


void me_free_several_objects(int quantity, ...);
void me_free_memory(void **ptr);
void *me_memory_alloc(void *ptr, size_t tam);
char *me_concat_str(char *str, char *other);
char *me_concat_multiplies_str(int quantitys, ...);
char *me_formatted_str(char *control_str, ...);
void *simple_destructor(void *data);
char *me_multiply_str(char *string, int times);
char* me_convert_int_to_str(int number);
void me_swap(void *value, void *other_value, size_t size_bytes);
double *create_double(double data);
char *me_double_to_str(double *ptr);
double *destroy_double(double *ptr);


int *create_int(int number);
void *destroy_int(int *number);
char* me_int_to_str(const int*ptr);
int me_eq_int(int *ptr, int *ptr2);
char *create_str(char *str);
void *destroy_str(char *str);
char* me_str_str(char *str);


#endif //UNTITLED70_MEMORY_H
