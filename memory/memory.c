//
// Created by vitor on 07/11/23.
//

#include "memory.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "../string/string.h"


void *me_memory_alloc(void *ptr, size_t tam){

    void *ptr_reall = realloc(ptr, tam);

    if ( !ptr_reall && tam ){
        fprintf(stderr, "ERRO, failed in aloc memory!");
        exit(1);
    }
    return ptr_reall;
}

void me_free_memory(void **ptr){
    free(*ptr);
    *ptr=NULL;
}

void me_free_several_objects(int quantity, ...){

    va_list p;
    va_start(p, quantity);
    void *ptr;
    for (int i = 0; i < quantity; ++i) {
        ptr = va_arg(p, void *);
        me_free_memory(ptr);

    }
    ptr = NULL;
    va_end(p);
}


int *create_int(int number){
    int *ptr = me_memory_alloc(NULL, sizeof(int));
    *ptr = number;
    return ptr;
}
void *destroy_int(int *number){
    *number = 0;
    me_free(number);
    return NULL;
}
int me_eq_int(int *ptr, int *ptr2){
    return *ptr == *ptr2;
}

char *me_int_to_str(int *ptr){
    return convert_int_to_str(*ptr);
}
double *create_double(double data){
    double *ptr= me_memory_alloc(NULL, sizeof(double ));
    *ptr = data;
    return ptr;
}
char *double_to_str(double *data){
    return str_formatted("%.2f", *data);
}
double *destroy_double(double *ptr){
    me_free(ptr);
    return NULL;
}

void me_swap(void *value, void *other_value, size_t size_bytes){
    char tmp[size_bytes];
    memmove(tmp, value, size_bytes);
    memmove(value, other_value, size_bytes);
    memmove(other_value, tmp, size_bytes);
}