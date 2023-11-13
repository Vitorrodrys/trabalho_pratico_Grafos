//
// Created by vitor on 09/11/23.
//

#include "matrix_operations.h"
#include "../../memory/memory.h"
#include <stdio.h>

void *mop_create_matrix(size_t tam_type, int tam){

    void **matrix = me_memory_alloc(NULL, sizeof(void *)*tam);
    for (int i = 0; i < tam; ++i) {
        matrix[i] = me_memory_alloc(NULL, tam_type*tam);
        memset(matrix[i], 0, tam_type*tam);
    }
    return matrix;
}

void *mop_destroy_matrix(void **matrix, int tam){

    for (int i = 0; i < tam; ++i) {
        me_free(matrix[i]);
    }
    me_free(matrix);
    return NULL;
}

char *mop_str_matrix_int(double **matrix, int tam_matrix){

    char *str_matrix = me_multiply_str("▬", tam_matrix*9-1);
    char *aux = str_matrix;
    str_matrix = me_concat_multiplies_str(3, "\n█", str_matrix, "█\n");
    me_free(aux);
    char *aux2;
    for (int i = 0; i < tam_matrix; ++i) {

        aux = me_formatted_str("█ %06.2f █", matrix[i][0]);
        aux2 = str_matrix;
        str_matrix= me_concat_str(str_matrix, aux);
        me_free(aux2);
        me_free(aux);
        for (int j = 1; j < tam_matrix-1; ++j) {
            aux = me_formatted_str(" %06.2f █", matrix[i][j]);
            aux2 = str_matrix;
            str_matrix = me_concat_str(str_matrix, aux);
            me_free(aux2);
            me_free(aux);
        }
        aux = me_formatted_str(" %06.2f █\n",  matrix[i][tam_matrix-1]);
        aux2 = str_matrix;
        str_matrix= me_concat_str(str_matrix, aux);
        me_free(aux2);
        me_free(aux);
    }
    aux = me_multiply_str("▬", tam_matrix*9-1);
    aux2 = str_matrix;
    str_matrix= me_concat_multiplies_str(4, str_matrix, "█",aux, "█");
    me_free(aux);
    me_free(aux2);
    return str_matrix;
}

int count_number_of_edges(void *vector, int tam, size_t size_type){

    char zero_block[size_type];
    memset(zero_block, 0, size_type);
    int count = 0;
    for (int i = 0; i < tam; ++i) {
        if ( !strncmp(zero_block, vector, size_type) ){
            count++;
        }
    }
    return count;
}