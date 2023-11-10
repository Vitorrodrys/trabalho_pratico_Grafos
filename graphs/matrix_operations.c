//
// Created by vitor on 09/11/23.
//

#include "matrix_operations.h"
#include "../memory/memory.h"
#include <stdio.h>

void *mop_create_matrix(size_t tam_type, int tam){

    void **matrix = me_memory_alloc(NULL, sizeof(void *)*tam);
    for (int i = 0; i < tam; ++i) {
        matrix[i] = me_memory_alloc(NULL, tam_type*tam);
    }
    return matrix;
}

void *mop_destroy_matrix(void **matrix, int tam){

    for (int i = 0; i < tam; ++i) {

        me_free_memory(matrix+i);
    }
    me_free_memory((void *)&matrix);
    return NULL;
}

char *mop_str_matrix_int(double **matrix, int tam_matrix){

    char *str_matrix = strdup("[\n");
    char *aux;
    char *aux2;
    for (int i = 0; i < tam_matrix; ++i) {

        aux = me_formatted_str("\t[ %4.2f,  ", matrix[i][0]);
        aux2 = str_matrix;
        str_matrix= me_concat_str(str_matrix, aux);
        me_free_memory((void*)&aux2);
        me_free_memory((void *)&aux);
        for (int j = 1; j < tam_matrix-1; ++j) {
            aux = me_formatted_str("%4.2f,  ", matrix[i][j]);
            aux2 = str_matrix;
            str_matrix = me_concat_str(str_matrix, aux);
            me_free_memory((void *)&aux2);
            me_free_memory((void *)&aux);
        }
        aux = me_formatted_str("%4.2f  ],\n\n",  matrix[i][tam_matrix-1]);
        aux2 = str_matrix;
        str_matrix= me_concat_str(str_matrix, aux);
        me_free_memory((void *)&aux2);
        me_free_memory((void *)&aux);
    }
    aux2 = str_matrix;
    str_matrix= me_concat_str(str_matrix, "]");
    me_free_memory((void *)&aux2);
    return str_matrix;
}

