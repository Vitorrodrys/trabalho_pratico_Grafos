//
// Created by vitor on 09/11/23.
//

#include "matrix_operations.h"
#include "../../memory/memory.h"
#include "../../string/string.h"

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

    char *str_matrix = str_multiply_str("▬", tam_matrix*9-1);
    char *aux = str_matrix;
    str_matrix = str_concat_multiplies(3, "\n█", str_matrix, "█\n");
    me_free(aux);
    char *aux2;
    for (int i = 0; i < tam_matrix; ++i) {

        aux = str_formatted("█ %06.2f █", matrix[i][0]);
        aux2 = str_matrix;
        str_matrix= str_concat(str_matrix, aux);
        me_free(aux2);
        me_free(aux);
        for (int j = 1; j < tam_matrix-1; ++j) {
            aux = str_formatted(" %06.2f █", matrix[i][j]);
            aux2 = str_matrix;
            str_matrix = str_concat(str_matrix, aux);
            me_free(aux2);
            me_free(aux);
        }
        aux = str_formatted(" %06.2f █\n",  matrix[i][tam_matrix-1]);
        aux2 = str_matrix;
        str_matrix= str_concat(str_matrix, aux);
        me_free(aux2);
        me_free(aux);
    }
    aux = str_multiply_str("▬", tam_matrix*9-1);
    aux2 = str_matrix;
    str_matrix= str_concat_multiplies(4, str_matrix, "█",aux, "█");
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

void *mop_remove_a_vertex(void **vector, int index, int tam){

    for (int i = index+1; i < tam; ++i) {
        vector[i-1] = vector[i];
    }
    return me_memory_alloc(vector, sizeof(void *)*(tam-1));
}