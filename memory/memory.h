//
// Created by vitor on 07/11/23.
//

#ifndef UNTITLED70_MEMORY_H
#define UNTITLED70_MEMORY_H
#include <stdlib.h>
#include <string.h>
#define me_free(pointer) \
me_free_memory((void **)&(pointer))


/**
 * function that can clear most objects
 * @param quantity: the quantity of the pointers that will be passed for be clean
 * @param ... pointers
 */
void me_free_several_objects(int quantity, ...);


/**
 * function that clear a memory region allocated by malloc, and put NULL in pointer that points to it
 * @param ptr: pointer to pointer that points to memory region
 */
void me_free_memory(void **ptr);

/**
 * create a new allocating memory with malloc, and check if the allocating was do with sucess
 * @param ptr: pointer to the before allocating, if passed NULL, then allocated a new region of the memory, if don't trying reallocated the region
 * @param tam size of the allocating
 * @return the pointer to allocating
 */
void *me_memory_alloc(void *ptr, size_t tam);

/**
 * swap the data of the two memory
 * @param value: first memory region
 * @param other_value: second memory region
 * @param size_bytes: size of the bytes of the two memory regions
 */
void me_swap(void *value, void *other_value, size_t size_bytes);


/**
 *Create a new double dynamically allocated; this function is used to create a base_value containing a double to be stored within a generic data structure (such as a hashmap, linked list, or list)."
 * @param data: number
 * @return the double stored in dynamically allocating
 */
double *create_double(double data);

/**
 * To destroy a double created by 'create_double,' this function is utilized in the process of constructing a base_value.
 * This is essential because the base_value requires a function pointer to specify how the generic data stored within it should be destructed.
 * @param ptr
 * @return
 */
double *destroy_double(double *ptr);
char *double_to_str(double *data);
char *me_int_to_str(int *ptr);

int *create_int(int number);
void *destroy_int(int *number);
int me_eq_int(int *ptr, int *ptr2);
void *destroy_str(char *str);


#endif //UNTITLED70_MEMORY_H
