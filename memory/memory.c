//
// Created by vitor on 07/11/23.
//

#include "memory.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

void *me_memory_alloc(void *ptr, size_t tam){

    void *ptr_reall = realloc(ptr, tam);;

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

