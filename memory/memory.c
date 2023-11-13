//
// Created by vitor on 07/11/23.
//

#include "memory.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

void *simple_destructor(void *data){
    me_free(data);
    return NULL;
}

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
    int size = vsnprintf(NULL, 0, control_str, p)+1;
    char aux[size];
    vsnprintf(aux, size, control_str, p_cp);
    va_end(p);
    va_end(p_cp);
    return strdup(aux);
}

char *me_concat_multiplies_str(int quantitys, ...){

    va_list  p;
    va_start(p, quantitys);
    char *aux1 = va_arg(p, char *);
    void *aux2;
    char *result = me_concat_str("", aux1);
    for (int i =1; i < quantitys; ++i) {
        aux1 = va_arg(p, char *);
        aux2 = result;
        result = me_concat_str(result, aux1);
        me_free(aux2);
    }
    va_end(p);
    return result;
}

char* me_convert_int_to_str(int number){
    return me_formatted_str("%d", number);
}
char *me_multiply_str(char *string, int times){

    if (!times){
        return strdup("");
    }
    char *product = strdup(string);
    char *aux;
    for (int i = 1; i < times; ++i) {
        aux = product;
        product = me_concat_str(product, string);
        me_free(aux);
    }
    return product;

}




int *create_int(int number){
    int *ptr = me_memory_alloc(NULL, sizeof(int));
    *ptr = number;
    return ptr;
}
void *destroy_int(int *number){
    me_free(number);
    return NULL;
}
char* me_int_to_str(const int*ptr){
    return me_formatted_str("\"%d\"",*ptr );
}
int me_eq_int(int *ptr, int *ptr2){
    return *ptr == *ptr2;
}

char *create_str(char *str){
    return strdup(str);
}
void *destroy_str(char *str){
    me_free(str);
    return NULL;
}
char* me_str_str(char *str){
    return me_formatted_str("\"%s\"", str);
}

