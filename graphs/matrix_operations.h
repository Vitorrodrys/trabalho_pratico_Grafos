//
// Created by vitor on 09/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_MATRIX_OPERATIONS_H
#define TRABALHO_PRATICO_GRAFOS_MATRIX_OPERATIONS_H
#include <stdlib.h>
char *me_concat_multiplies_str(int quantitys, ...);
char *mop_str_matrix_int(double **matrix, int tam_matrix);
void *mop_create_matrix(size_t tam_type, int tam);
void *mop_destroy_matrix(void **matrix, int tam);
#endif //TRABALHO_PRATICO_GRAFOS_MATRIX_OPERATIONS_H
