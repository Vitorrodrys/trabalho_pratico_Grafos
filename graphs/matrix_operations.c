//
// Created by vitor on 09/11/23.
//

#include "matrix_operations.h"
#include "../memory/memory.h"

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