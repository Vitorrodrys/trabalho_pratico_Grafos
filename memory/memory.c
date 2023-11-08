//
// Created by vitor on 07/11/23.
//

#include "memory.h"
#include "../list/list.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void *memory_alloc(void *ptr, size_t tam){

    void *ptr_reall = realloc(ptr, tam);;

    if ( !ptr_reall && tam ){
        fprintf(stderr, "ERRO, failed in aloc memory!");
        exit(1);
    }
    return ptr_reall;
}

void free_memory(void **ptr){


    free(*ptr);
    *ptr=NULL;
}

void free_several_objects(int quantity, ...){

    va_list p;
    va_start(p, quantity);
    void *ptr;
    for (int i = 0; i < quantity; ++i) {
        ptr = va_arg(p, void *);
        free_memory(ptr);

    }
    ptr = NULL;
    va_end(p);
}

List *break_str_in_list(char *str, char *tok){

    List *list = create_list();

    char *token = strtok(str, tok);

    while (token){
        append(list, strdup(token));
        token = strtok(NULL, tok);
    }
    return list;
}
