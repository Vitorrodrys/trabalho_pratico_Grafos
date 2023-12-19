//
// Created by vitor on 21/11/23.
//

#include "string.h"
#include "../memory/memory.h"
#include <stdarg.h>
#include <stdio.h>

char *str_concat(char *str, char *other){

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
char *str_formatted(char *control_str, ...){

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

char *str_concat_multiplies(int quantitys, ...){

    va_list  p;
    va_start(p, quantitys);
    char *aux1 = va_arg(p, char *);
    void *aux2;
    char *result = str_concat("", aux1);
    for (int i =1; i < quantitys; ++i) {
        aux1 = va_arg(p, char *);
        aux2 = result;
        result = str_concat(result, aux1);
        me_free(aux2);
    }
    va_end(p);
    return result;
}

char* convert_int_to_str(int number){
    return str_formatted("%d", number);
}
char *str_multiply_str(char *string, int times){

    if (!times){
        return strdup("");
    }
    char *product = strdup(string);
    char *aux;
    for (int i = 1; i < times; ++i) {
        aux = product;
        product = str_concat(product, string);
        me_free(aux);
    }
    return product;

}
void *destroy_str(char *str){
    me_free(str);
    return NULL;
}
char* str_str(char *str){
    return str_formatted("\"%s\"", str);
}


