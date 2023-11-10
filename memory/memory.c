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
char *me_int_to_str(int number){
    return me_formatted_str("%d\n", number);
}

char *me_concat_str(char *str, char *other){

    char *new_str = me_memory_alloc(NULL, sizeof(char)* strlen(str) + sizeof (char)* strlen(other) + sizeof (char));
    strcpy(new_str, str);
    strcat(new_str, other);
    return new_str;
}

int _count_quantity_token(char *str, char tk){

    int quantity = 0;
    while (strchr(str, tk)){
        str = strchr(str, tk)+1;
        quantity++;
    }
    return quantity;
}
char *me_formatted_str(char *control_str, ...){

    int quantity_paramaters =_count_quantity_token(control_str, '%');
    va_list p;
    va_start(p, quantity_paramaters);
    va_list p_cp;
    va_copy(p_cp, p);
    int size = vsnprintf(NULL, 0, control_str, p);
    char aux[size];
    vsnprintf(aux, size, control_str, p_cp);
    va_end(p);
    va_end(p_cp);
    return strdup(aux);
}

